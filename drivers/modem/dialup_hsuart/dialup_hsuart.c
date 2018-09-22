
/*lint -save -e537 -e64 -e124 -e413 -e613 -e533 -e713 -e718 -e732 -e737 -e730 -e529*/
/*lint -save -e550 -e438 -e527 -e716 -e958 -e718 -e746 -e650 -e734 -e545*/
#include <linux/kernel.h>       /*kmalloc,printk*/
#include <linux/module.h>
#include <linux/kthread.h>      
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/dma-mapping.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/platform_device.h>
#include <asm/irq.h>
#include "osl_malloc.h"
#include "osl_thread.h"
#include <bsp_edma.h>
#include <bsp_hardtimer.h>
#include "drv_udi.h"
#include "drv_acm.h"
#include "hi_uart.h"
#include "dialup_hsuart.h"
/*lint -save -e110 -e82*/
hsuart_ctx  m2m_hsuart_ctx = {
    .dev = {
        .irq = INT_LVL_HSUART,
        .clock = 48000000,
        .phy_addr_base = HI_HSUART_REGBASE_ADDR,
        .dma_req_rx = EDMA_HSUART_RX,
        .dma_req_tx = EDMA_HSUART_TX
    },
    .udi_device_id = UDI_HSUART_0_ID,
    .transfer_mode = DMA_TRANSFER,
};

static int typical_baud[] = {9600, 19200, 38400, 57600, 115200, 375000, 600000, 750000, 1000000, 3000000};/*�ο�оƬ����*/
static const char switch_cmd[] = "+++";

struct hsuart_ctrl g_hsuart_ctrl ={{0},{0},0};
struct hsuart_dma_ctrl g_dma_ctrl ={0};

extern struct clk *clk_get(char *dev, const char *con_id);
extern int clk_enable(struct clk * c);
extern void clk_disable(struct clk * c);
extern s32 dialup_hsuart_send(u8 * pucSrcAddr, u32 u32TransLength);


/*******************************************************************************
* �� �� ��  : hsuart_fifo_reset
* ��������  : ��λuart fifo
* �������  : uart_dev �豸ָ��
* �������  : NA
* �� �� ֵ  : NA
*******************************************************************************/
static inline void hsuart_fifo_reset(hsuart_dev *uart_dev)
{
    u32 val = 0;
    val = (UART_DEF_RT_ONEFOUR|UART_DEF_TET_ONETWO|UART_DEF_DMA_MODE|UART_TX_FIFO_RESET|UART_RX_FIFO_RESET|UART_FCR_FIFO_ENABLE);
    (void)writel(val, uart_dev->vir_addr_base + UART_REGOFF_FCR);
}
/*******************************************************************************
* �� �� ��  : hsuart_set_rts
* ��������  : ��������
* �������  : uart_dev �豸ָ��
* �������  : NA
* �� �� ֵ  : NA
*******************************************************************************/
static inline void hsuart_set_rts(hsuart_dev *uart_dev)
{
    u32 val = 0;
    hsuart_ctx *uart_ctx = NULL;
    
    uart_ctx = container_of(uart_dev, hsuart_ctx, dev);
    val = readl(uart_dev->vir_addr_base + UART_REG_OFFSET_MCR);
    val |= (UART_RTS_ENABLE|UART_AFCE_ENABLE);
    (void)writel(val, uart_dev->vir_addr_base + UART_REG_OFFSET_MCR); 
}
/*******************************************************************************
* �� �� ��  : hsuart_clear_rts
* ��������  : ����UART
* �������  : uart_dev �豸ָ��
* �������  : NA
* �� �� ֵ  : NA
*******************************************************************************/
static inline void hsuart_clear_rts(hsuart_dev *uart_dev)
{
    u32 val = 0;
    hsuart_ctx *uart_ctx = NULL;
    
    uart_ctx = container_of(uart_dev, hsuart_ctx, dev);
    val = readl(uart_dev->vir_addr_base + UART_REG_OFFSET_MCR);
	val &= (~(UART_RTS_ENABLE|UART_AFCE_ENABLE));
    (void)writel(val, uart_dev->vir_addr_base + UART_REG_OFFSET_MCR);
}
/*****************************************************************************
* �� �� ��  : hsuart_set_baud
* ��������  : UART ���ò����ʺ���
* �������  : uart_dev: �豸����ṹָ��
*             baud: ������ֵ
* �������  :
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
int hsuart_set_baud(hsuart_dev *uart_dev, int baud)
{
	u32 divisor = 0;
	u32 divisor_dll = 0;
    u32 divisor_dlh = 0;
	u32 val = 0;
	u32 u32Times = 0;
	u32 u32Discard = 0;
    hsuart_ctx *uart_ctx = NULL;

    if (NULL == uart_dev || baud < 0 || (unsigned int)baud > (uart_dev->clock >> 4))
    {
        hsuart_error("uart_dev:0x%x   baud:%d\n", (unsigned int)uart_dev, baud);
        return ERROR;
    }
    
    uart_ctx = container_of(uart_dev, hsuart_ctx, dev);
    if (0 == baud)
    {
        uart_ctx->baud_adapt = HSUART_TRUE;
        uart_ctx->baud_idx = (uart_ctx->baud_idx + 1) % (sizeof(typical_baud) / sizeof(int));
        baud = typical_baud[uart_ctx->baud_idx];
		bsp_softtimer_add(&g_hsuart_ctrl.adapt_timer);
        hsuart_debug("baud adapt start");
    }
    uart_ctx->feature.baud = baud;
	
    hsuart_debug("set baud: %d\n", baud);
    
	divisor =  uart_dev->clock/ (u32)(16 * baud);
	divisor_dll = divisor & 0xFF;
	divisor_dlh = (divisor & 0xFF00) >> 8;

	/* ��ȡUART ״̬�Ĵ�������UART�Ƿ���idle״̬*/
    u32Discard = readl(uart_dev->vir_addr_base + UART_REGOFF_USR);
    while((u32Discard & 0x01)&&(u32Times<1000))
    {
    	u32Discard = readl(uart_dev->vir_addr_base + UART_REGOFF_USR);
        u32Times++;
    }
    if(1000 == u32Times)
    {
		hsuart_error("UART BUSY\n");
		return ERROR;
    }	
	/* �� DLL/DHL */
	val = readl(uart_dev->vir_addr_base + UART_REGOFF_LCR);
    writel(UART_LCR_DLAB, uart_dev->vir_addr_base + UART_REGOFF_LCR);
    /* ����DLH ��DLL �Ĵ��������ô���ͨѶ�Ĳ�����*/
    writel(divisor_dll, uart_dev->vir_addr_base + UART_REGOFF_DLL);
    writel(divisor_dlh, uart_dev->vir_addr_base + UART_REGOFF_DLH);
    /*��ֹ DLL&DLH */
	val &= ~UART_LCR_DLAB;
    writel(val, uart_dev->vir_addr_base + UART_REGOFF_LCR); 
    return OK;
}
/*******************************************************************************
* �� �� ��  : set_next_adapt
* ��������  : ������
* �������  : uart_dev �豸ָ��
* �������  : NA
* �� �� ֵ  : NA
*******************************************************************************/
void set_next_adapt(u32 arg)
{
    hsuart_ctx *uart_ctx = (hsuart_ctx *)arg;
    hsuart_fifo_reset(&uart_ctx->dev);
    hsuart_set_baud(&uart_ctx->dev, 0);
}
/*****************************************************************************
* �� �� ��  : hsuart_set_wlen
* ��������  : UART ��������λ������
* �������  : uart_dev: �豸����ṹָ��
*             w_len: ����λ��
* �������  :
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
int hsuart_set_wlen(hsuart_dev *uart_dev, int w_len)
{
	u32 val = 0;
    u32 wlen = 0;
    
    hsuart_debug("set wlen: %d\n", w_len);    
    switch(w_len)
    {
        case WLEN_5_BITS:
            wlen = UART_LCR_DLS_5BITS;
            break;
        case WLEN_6_BITS:
            wlen = UART_LCR_DLS_6BITS;
            break;
        case WLEN_7_BITS:
            wlen = UART_LCR_DLS_7BITS;
            break;
        case WLEN_8_BITS:
            wlen = UART_LCR_DLS_8BITS;
            break;
        default:
            hsuart_debug("unsupport w_len:%d\n", w_len);
            return ERROR;
    }
 
    /*clear wlen bits*/
    val = readl(uart_dev->vir_addr_base + UART_REGOFF_LCR);
    val &= (~UART_LCR_DLS_MASK); 
    /*set new wlen*/
    val |= (unsigned int)wlen;
    (void)writel(val, uart_dev->vir_addr_base + UART_REGOFF_LCR);
    return OK;
}
/*****************************************************************************
* �� �� ��  : hsuart_set_stp2
* ��������  : UART ����ֹͣλ������
* �������  : uart_dev: �豸����ṹָ��
*             stp2: ����ֹͣλ����
* �������  :
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
int hsuart_set_stpbit(hsuart_dev *uart_dev, int stp2)
{
    u32 val = 0;  
    hsuart_debug("set stp2: %d\n", stp2);
	val = readl(uart_dev->vir_addr_base + UART_REGOFF_LCR);
    if(stp2 == STP2_OFF)
    {
		val &= ~UART_LCR_STOP_2BITS;
    }
   	else if(stp2 == STP2_ON)
   	{
        val |= UART_LCR_STOP_2BITS;
   	}
	else
	{
		hsuart_error("unsupport stp2:%d\n", stp2);
        return ERROR;
    }
	(void)writel(val, uart_dev->vir_addr_base + UART_REGOFF_LCR);
    return OK;
}
/*****************************************************************************
* �� �� ��  : hsuart_set_eps
* ��������  : UART ����У�鷽ʽ����
* �������  : uart_dev: �豸����ṹָ��
*             eps: У�鷽ʽ
* �������  :
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
int hsuart_set_eps(hsuart_dev *uart_dev, int eps)
{
    u32 val = 0;
	hsuart_debug("set eps: %d\n", eps);
	val = readl(uart_dev->vir_addr_base + UART_REGOFF_LCR);
    if(eps == PARITY_NO_CHECK)   	/*��У��λ*/
    {		
        val &= ~UART_LCR_PEN;
    }	
    else if(eps == PARITY_CHECK_ODD)  	/*��У��*/
    {
            val |= UART_LCR_PEN;
			val &= ~UART_LCR_EPS;
    }	
    else if(eps == PARITY_CHECK_EVEN)	/*żУ��*/
    {
		val |= (UART_LCR_PEN | UART_LCR_EPS);
    }		
	else
	{
		hsuart_error("unsupport eps:%d\n", eps);
        return ERROR;
    }
	(void)writel(val, uart_dev->vir_addr_base + UART_REGOFF_LCR);
    return OK;
}

/*****************************************************************************
* �� �� ��  : hsuart_alloc_skb
* ��������  :����SKB
* �������  : pMemNode ���ݽڵ�size �����С
* �������  : NA
* �� �� ֵ  : ʧ��/�ɹ�
*****************************************************************************/
s32 hsuart_alloc_skb(uart_mem_node* pMemNode, u32 size)
{
	pMemNode->pSkb = dev_alloc_skb(size);   
	if (NULL == pMemNode->pSkb)
    {
        hsuart_error("pMemNode buff alloc fail, size:%d\n", size);
        return ERROR;
    }
    pMemNode->mem.vaddr = (void*)pMemNode->pSkb->data;
  	pMemNode->mem.paddr = dma_map_single(NULL, pMemNode->mem.vaddr, size, DMA_FROM_DEVICE);
    (void)memset(pMemNode->mem.vaddr, 0, size);
    return OK;
}
/*****************************************************************************
* �� �� ��  : add_mem_to_freelist
* ��������  : UART UDI ��ӽڵ㵽 FreeList ��
* �������  : trans_info: ��д�ṹ��
*             pMemNode: ����ӵĽڵ�
* �������  : NA
* �� �� ֵ  : NA
*****************************************************************************/
void add_mem_to_freelist(hsuart_trans_info *trans_info, uart_mem_node* pMemNode)
{
    unsigned long flags = 0;   
    spin_lock_irqsave(&trans_info->list_lock, flags); 
    list_add_tail(&pMemNode->list_node, &(trans_info->free_list));
    /*ȥ��ʼ��pMemNode��Ա*/
    pMemNode->state = UART_MEM_IN_FREELIST;
    pMemNode->valid_size = 0;
    pMemNode->pSkb = NULL;
    pMemNode->mem.vaddr = (void*)NULL;
    pMemNode->mem.paddr = (phys_addr)NULL;  
    spin_unlock_irqrestore(&trans_info->list_lock, flags);
}
/*****************************************************************************
* �� �� ��  : get_mem_from_freelist
* ��������  : UART UDI ��FreeList ͷȡ��һ���ڵ�
* �������  : trans_info: ��д�ṹ��
* �������  : NA
* �� �� ֵ  : ���صĽڵ�ָ��
*****************************************************************************/
uart_mem_node* get_mem_from_freelist(hsuart_trans_info *trans_info)
{
    struct list_head *pListNode;
    uart_mem_node* pMemNode;
    unsigned long flags = 0;  
    spin_lock_irqsave(&trans_info->list_lock, flags);  
    if (list_empty(&(trans_info->free_list)))
    {
        pMemNode = NULL;
    }
    else
    {
        pListNode = trans_info->free_list.next;
        pMemNode = list_entry(pListNode, uart_mem_node, list_node);
        
        list_del_init(pListNode);
        pMemNode->state = UART_MEM_NOT_IN_LIST;
    }   
    spin_unlock_irqrestore(&trans_info->list_lock, flags);   
    return pMemNode;
}
/*****************************************************************************
* �� �� ��  : add_mem_to_donelist
* ��������  : UART UDI ��ӽڵ㵽 ������� ��
* �������  : trans_info: uart ��д�ṹ��ָ��
*             pMemNode: ����ӵĽڵ�
* �������  : NA
* �� �� ֵ  : NA
*****************************************************************************/
void add_mem_to_donelist(hsuart_trans_info *trans_info, uart_mem_node* pMemNode)
{
	unsigned long flags = 0;

    spin_lock_irqsave(&trans_info->list_lock, flags);
    list_add_tail(&pMemNode->list_node, &(trans_info->done_list));
    trans_info->done_cnt++;
    pMemNode->state = UART_MEM_IN_DONELIST;    
    spin_unlock_irqrestore(&trans_info->list_lock, flags);
}
/*****************************************************************************
* �� �� ��  : get_mem_from_donelist
* ��������  : UART UDI ��DoneList ͷȡ��һ���ڵ�
* �������  : trans_info: ��д�ṹ��
* �������  : NA
* �� �� ֵ  : ���صĽڵ�ָ��
*****************************************************************************/
uart_mem_node* get_mem_from_donelist(hsuart_trans_info *trans_info)
{
    struct list_head *pListNode = NULL;
    uart_mem_node* pMemNode = NULL;
    unsigned long flags = 0;

    spin_lock_irqsave(&trans_info->list_lock, flags);   
    if (list_empty(&(trans_info->done_list)))
    {
		//hsuart_error("pMemNode is null!\n");
		pMemNode = NULL;
    }
    else
    {    
        pListNode = trans_info->done_list.next;
        pMemNode = list_entry(pListNode, uart_mem_node, list_node);
        list_del_init(pListNode);
        trans_info->done_cnt--;
        pMemNode->state = UART_MEM_NOT_IN_LIST;
    }    
    spin_unlock_irqrestore(&trans_info->list_lock, flags); 
    return pMemNode;
}

/*****************************************************************************
* �� �� ��  : get_list_node_num
* ��������  : ��ȡ�����еĽڵ����
* �������  : pFreeHeader: Free Listͷ�ڵ�
* �������  : ���صĽڵ����
* �� �� ֵ  : �ڵ����
*****************************************************************************/
s32 get_list_node_num(struct list_head *pHeader)
{
    struct list_head* pCurPos = NULL;
    struct list_head* pNextPos = NULL;
    s32 s32Num = 0;
    list_for_each_safe(pCurPos, pNextPos, pHeader)
    {
        s32Num++;
    }  
    return s32Num;
}
/*****************************************************************************
* �� �� ��  : hsuart_uninit_list
* ��������  : ȥ��ʼ����д����
* �������  : trans_info: ��д�ṹ��
* �������  : NA
* �� �� ֵ  : NA
*****************************************************************************/
void hsuart_uninit_list(hsuart_trans_info *trans_info)
{
    u32 idx = 0;
    unsigned long flags = 0;

    if(NULL == trans_info)
	{
       hsuart_error("trans_info is NULL\n");
	   return;
	}
    spin_lock_irqsave(&trans_info->list_lock, flags);    
    INIT_LIST_HEAD(&(trans_info->free_list));
    INIT_LIST_HEAD(&(trans_info->done_list));
  
    if (trans_info->pmem_start)
    {
        for (idx = 0; idx < trans_info->node_num; idx++)
        {
            INIT_LIST_HEAD(&(trans_info->pmem_start[idx].list_node));
            trans_info->pmem_start[idx].state = UART_MEM_NOT_IN_LIST;
            trans_info->pmem_start[idx].mem.vaddr = (void*)NULL;
            trans_info->pmem_start[idx].mem.paddr = (phys_addr)NULL;
            trans_info->pmem_start[idx].valid_size = 0;
            if (trans_info->pmem_start[idx].pSkb)
            {
                dev_kfree_skb(trans_info->pmem_start[idx].pSkb);
                trans_info->pmem_start[idx].pSkb = NULL;
            }
        }

        kfree(trans_info->pmem_start);
        trans_info->pmem_start = NULL;
    }
    
    trans_info->pmem_end = NULL;
    trans_info->pcur_pos = NULL;
    trans_info->node_num = 0;
    trans_info->node_size = 0;
    trans_info->done_cnt = 0;
    trans_info->total_bytes = 0;
    spin_unlock_irqrestore(&trans_info->list_lock, flags);
}
/*****************************************************************************
* �� �� ��  : hsuart_init_list
* ��������  : ��ʼ����д����
* �������  : trans_info: ��д�ṹ��
* �������  : NA
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 hsuart_init_list(hsuart_trans_info *trans_info)
{
    u8* pMemHead = NULL;
    u32 idx = 0;
    s32 ret = OK;
    unsigned long flags = 0;
	struct list_head *pListNode = NULL;
	
    if(NULL == trans_info)
	{
       hsuart_error("trans_info is NULL\n");
	   return ERROR;
	}
    spin_lock_irqsave(&trans_info->list_lock, flags);//�����ź���
    INIT_LIST_HEAD(&(trans_info->free_list));
    INIT_LIST_HEAD(&(trans_info->done_list));
    
    pMemHead = osl_malloc(trans_info->node_num*sizeof(uart_mem_node));
    if (pMemHead)
    {
        (void)memset(pMemHead, 0, (trans_info->node_num*sizeof(uart_mem_node)));
        trans_info->pmem_start = (uart_mem_node*)pMemHead;
        trans_info->pmem_end = (uart_mem_node*)(pMemHead + (trans_info->node_num*sizeof(uart_mem_node)));
        trans_info->pcur_pos = NULL;
        trans_info->done_cnt = 0;
        trans_info->total_bytes = 0;

        /* ��ʼ��ʱ,���нڵ㶼��FreeList */
        for (idx = 0; idx < trans_info->node_num; idx++)
        {
            pListNode = &(trans_info->pmem_start[idx].list_node);
            list_add_tail(pListNode, &(trans_info->free_list));
            trans_info->pmem_start[idx].state = UART_MEM_IN_FREELIST;
            trans_info->pmem_start[idx].valid_size = 0;
            (void)memset(&(trans_info->pmem_start[idx].mem), 0, sizeof(mem_desc_t));
            trans_info->pmem_start[idx].pSkb = NULL;
        }
    }
    else
    {
        ret = ERROR;
    }
    spin_unlock_irqrestore(&trans_info->list_lock, flags);

    return ret;
}
/*****************************************************************************
* �� �� ��  : hsuart_buf_init
* ��������  :��ʼ����д�������
* �������  : uart_ctx ������
* �������  : NA
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 hsuart_buf_init(hsuart_ctx *uart_ctx)
{
    s32 ret = OK;	
    if(NULL == uart_ctx)
	{
       hsuart_error("uart_ctx is NULL\n");
	   return ERROR;
	}
    memset(&(uart_ctx->read_info), 0, sizeof(hsuart_trans_info));
    memset(&(uart_ctx->write_info), 0, sizeof(hsuart_trans_info));
    
    spin_lock_init(&(uart_ctx->read_info.list_lock));
    spin_lock_init(&(uart_ctx->write_info.list_lock));

    uart_ctx->read_info.node_num = UART_READ_BUF_NUM;   //���ڵ�����16
    uart_ctx->read_info.node_size = UART_READ_BUF_SIZE; //ÿ���ڵ��С1536�ֽ�
    uart_ctx->write_info.node_num = UART_WRITE_BUF_NUM; //д�ڵ�����64
    uart_ctx->write_info.node_size = 0;					//ÿ��д�ڵ��С0
	if (hsuart_init_list(&(uart_ctx->read_info)) || hsuart_init_list(&(uart_ctx->write_info)))
    {
        hsuart_error("hsuart_init_list error.\n");
        ret = ERROR;
    }
    return ret;
}
/*****************************************************************************
* �� �� ��  : gpio_dtr_irq
* ��������  : GPIO �жϴ���
* �������  : irq �жϺ� dev_id ����
* �������  : NA
* �� �� ֵ  : �ɹ�/ʧ��bcmsdh_register_oob_intr
*****************************************************************************/
static irqreturn_t gpio_dtr_irq(int irq, void *dev_id)
{
    hsuart_ctx* uart_ctx = (hsuart_ctx*)dev_id;
    MODEM_MSC_STRU modem_msc = {0};
	if(!gpio_int_state_get(HSUART_DTR))
	{
		hsuart_error("gpio_dtr_irq:%d\n", modem_msc.ucDtr);
		return IRQ_NONE;
	}
    gpio_int_mask_set(HSUART_DTR);
	
    memset(&modem_msc, 0, sizeof(MODEM_MSC_STRU));
    modem_msc.OP_Dtr = SIGNALCH;
    modem_msc.ucDtr = !(BSP_U8)gpio_get_value(HSUART_DTR);
    hsuart_debug("gpio_dtr_irq:%d\n", modem_msc.ucDtr);
	if (uart_ctx->cbs.msc_read_cb)
    {
        uart_ctx->cbs.msc_read_cb(&modem_msc);
    }
    else
    {
        hsuart_error("value:%d  msc_read_cb is NULL.\n", modem_msc.ucDtr);
    }
	
    if(gpio_get_value(HSUART_DTR))
    {
    	gpio_int_trigger_set(HSUART_DTR , IRQ_TYPE_EDGE_FALLING);
    }
    else
    {
     	gpio_int_trigger_set(HSUART_DTR , IRQ_TYPE_EDGE_RISING); 
    }

    gpio_int_state_clear(HSUART_DTR);
    gpio_int_unmask_set(HSUART_DTR);  
    
    return IRQ_HANDLED;
}
/*****************************************************************************
* �� �� ��  : hsuart_gpio_init
* ��������  : uart gpio ģ��ܽų�ʼ������
* �������  : uart_ctx ������
* �������  : NA
* �� �� ֵ  : �ɹ�/ʧ��bcmsdh_register_oob_intr
* ��	ע	:����gpio�����ֲ�ͨ������
*****************************************************************************/
s32 hsuart_gpio_init(hsuart_ctx *uart_ctx)
{
    s32 ret;
    s32 irq_id = 0;
	hsuart_debug("hsuart_gpio_init enter...!\n");

    if (gpio_request(HSUART_RING, "GPIO_RING"))
    {
        hsuart_error("gpio=%d is busy.\n", HSUART_RING);
        return ERROR;
    }

    if (gpio_request(HSUART_DSR, "GPIO_DSR"))
    {
        hsuart_error("gpio=%d is busy.\n", HSUART_DSR);
        return ERROR;
    }

    if (gpio_request(HSUART_DCD, "GPIO_DCD"))
    {
        hsuart_error("gpio=%d is busy.\n", HSUART_DCD);
        return ERROR;
    }
  
    gpio_direction_output(HSUART_RING, HIGHLEVEL); 
    gpio_direction_output(HSUART_DSR, HIGHLEVEL); 
    gpio_direction_output(HSUART_DCD, HIGHLEVEL); 
    
    if (gpio_request(HSUART_DTR, "GPIO_DTR"))
    {
        hsuart_error("gpio=%d is busy\n", HSUART_DTR);
        return ERROR;
    }
    
    gpio_direction_input(HSUART_DTR);     
    gpio_int_mask_set(HSUART_DTR);    
    gpio_int_state_clear(HSUART_DTR); 
	if(gpio_get_value(HSUART_DTR))
    {
    	gpio_int_trigger_set(HSUART_DTR , IRQ_TYPE_EDGE_FALLING);
    }
    else
    {
     	gpio_int_trigger_set(HSUART_DTR , IRQ_TYPE_EDGE_RISING); 
    }
	gpio_set_function(HSUART_DTR, GPIO_INTERRUPT);
    hsuart_error("GPIO: %d gpio_set_function done\n", HSUART_DTR);
    
	irq_id = gpio_to_irq(HSUART_DTR);
    ret = request_irq(irq_id, gpio_dtr_irq, IRQF_NO_SUSPEND | IRQF_SHARED,"HSUART_DTR", (void*)uart_ctx);
    if (ret != 0) 
	{
        hsuart_error("failed at register gpio-oob irq\n");
        return ERROR;
    }   
    gpio_int_state_clear(HSUART_DTR);
    gpio_int_unmask_set(HSUART_DTR);    
    return OK;
}
/*****************************************************************************
* �� �� ��  : hsuart_dma_tx_complete
* ��������  : UART DMA ģʽ������ɺ���
* �������  : arg: �豸����ṹָ��
*             int_status: �ж�״̬
* �������  :
* �� �� ֵ  : NA
*****************************************************************************/
void hsuart_dma_tx_complete(u32 arg, u32 int_status)
{
    hsuart_ctx *uart_ctx = (hsuart_ctx *)arg;
    up(&uart_ctx->dma_sema);
}
/*****************************************************************************
* �� �� ��  : hsuart_tx_dma
* ��������  : UART DMA ģʽ�������ݺ���
* �������  : uart_dev: �豸����ṹָ��
*             dma_handle: �������ݻ����ַ
*             length: �������ݳ���
* �������  :
* �� �� ֵ  : �������ݳ���
*****************************************************************************/
s32 hsuart_tx_dma(hsuart_dev *uart_dev, u32 dma_handle, u32 length)
{
    s32 ret_id = 0;
    hsuart_ctx *uart_ctx = NULL;

    uart_ctx = container_of(uart_dev, hsuart_ctx, dev);
    
	ret_id = bsp_edma_channel_init(uart_dev->dma_req_tx, hsuart_dma_tx_complete, (u32)uart_ctx, BALONG_DMA_INT_DONE);
	if (ret_id < 0)
    {
        hsuart_error("balong_dma_channel_init error ret_id = %d\n", ret_id);
        return ERROR;
    }
    if (bsp_edma_channel_set_config(ret_id, BALONG_DMA_M2P, EDMA_TRANS_WIDTH_32, EDMA_BUR_LEN_16))
    {
        hsuart_error("balong_dma_channel_set_config failed! ret_id = %d\n", ret_id);
        return ERROR;
    }
    if (bsp_edma_channel_async_start(ret_id, dma_handle, (u32)(uart_dev->phy_addr_base + UART_REGOFF_THR), length))
    {
        hsuart_error("balong_dma_channel_async_start transfer failed! ret_id = %d\n", ret_id);
        return ERROR;
    }
    return length;
}
/*******************************************************************************
* �� �� ��  : switch_stage_three
* ��������  : ģʽ�л������׶�
* �������  : arg ����
* �������  : NA
* �� �� ֵ  : NA
*******************************************************************************/
void switch_stage_three(u32 arg)
{
    hsuart_ctx *uart_ctx = (hsuart_ctx *)arg;
    uart_mem_node* pMemNode = NULL;
    
    pMemNode = uart_ctx->read_info.pcur_pos;
    pMemNode->valid_size = 0;
    uart_ctx->stage = DETECT_STAGE_1;
    
	if (uart_ctx->cbs.switch_mode_cb)
 	{
      	uart_ctx->cbs.switch_mode_cb();
		hsuart_debug("switch cmd mode.\n");
  	}
  	else
	{
        hsuart_error("switch_mode_cb is NULL.\n");
    }
}

/*****************************************************************************
* �� �� ��  : switch_mode_cmd_detect
* ��������  : ģʽ�л������⺯��
* �������  : uart_ctx ������ pMemNode ���ݽڵ�ָ��
* �������  : NA
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 switch_mode_cmd_detect(hsuart_ctx *uart_ctx, uart_mem_node* pMemNode)
{
    int result = 0;
    
    if (DETECT_STAGE_2 == uart_ctx->stage)
    {
		//hsuart_debug("switch_mode_cmd_detect\n"); 
        if (pMemNode)	/*�����ݽڵ�������Ϊ"+++"*/
        {
            result = !memcmp((void*)switch_cmd, (void*)pMemNode->mem.vaddr, strlen(switch_cmd));
        	if((*((char *)pMemNode->mem.vaddr + 3)) == '\r' || (*((char *)pMemNode->mem.vaddr + 3)) == '\n')
			{
				--pMemNode->valid_size;
				if ((*((char *)pMemNode->mem.vaddr + 4)) == '\n' || (*((char *)pMemNode->mem.vaddr + 4)) == '\r')
				{
					--pMemNode->valid_size;
		    	}
        	}
			result = result && (pMemNode->valid_size == strlen(switch_cmd));
			
        	if (result)
        	{
				uart_ctx->stage = DETECT_STAGE_3;
	            bsp_softtimer_add(&g_hsuart_ctrl.switch_state3_timer);
        	}
        	else
        	{
				//hsuart_debug("DETECT_STAGE_2 to DETECT_STAGE_1\n");    
	            uart_ctx->stage = DETECT_STAGE_1;
        	}
        }
    }
    else
    {
		uart_ctx->stage = DETECT_STAGE_1;
	}
    return result;
}
/*****************************************************************************
* �� �� ��  : wait_tx_fifo_empty
* ��������  : UART �ȴ��������
* �������  : ctx ����
* �������  : NA
* �� �� ֵ  : NA
*****************************************************************************/
void wait_tx_fifo_empty(hsuart_ctx *uart_ctx)
{
    u32 cnt = 0;
    u32 status;
    
    status = readl(uart_ctx->dev.vir_addr_base + UART_REGOFF_USR);
    while (0 == (status & UART_USR_FIFO_EMP))
    {
        msleep(1);
        if (10000 < cnt++)
        {
            hsuart_error("wait time out.\n");
            break;
        }
        status = readl(uart_ctx->dev.vir_addr_base + UART_REGOFF_USR);
    }
}
/*****************************************************************************
* �� �� ��  : set_hsuart_feature
* ��������  : uart ��������
* �������  : uart_ctx:uart������
* �������  : NA
* �� �� ֵ  : NA
*****************************************************************************/
void set_hsuart_feature(hsuart_ctx *uart_ctx)
{
    unsigned long flags = 0;
    
    if (uart_ctx->cbs.set_baud_cb || uart_ctx->cbs.set_wlen_cb || uart_ctx->cbs.set_stp2_cb || uart_ctx->cbs.set_eps_cb)
    {
        wait_tx_fifo_empty(uart_ctx);
        hsuart_fifo_reset(&uart_ctx->dev);
		spin_lock_irqsave(&(uart_ctx->dev.lock_irq), flags);
        if (uart_ctx->cbs.set_baud_cb)
        {
            uart_ctx->cbs.set_baud_cb(&uart_ctx->dev, uart_ctx->feature.baud);
            uart_ctx->cbs.set_baud_cb = NULL;
        }
        if (uart_ctx->cbs.set_wlen_cb)
        {
            uart_ctx->cbs.set_wlen_cb(&uart_ctx->dev, uart_ctx->feature.wlen);
            uart_ctx->cbs.set_wlen_cb = NULL;
        }
        if (uart_ctx->cbs.set_stp2_cb)
        {
            uart_ctx->cbs.set_stp2_cb(&uart_ctx->dev, uart_ctx->feature.stp2);
            uart_ctx->cbs.set_stp2_cb = NULL;
        }
        if (uart_ctx->cbs.set_eps_cb)
        {
            uart_ctx->cbs.set_eps_cb(&uart_ctx->dev, uart_ctx->feature.eps);
            uart_ctx->cbs.set_eps_cb = NULL;
        }
        spin_unlock_irqrestore(&(uart_ctx->dev.lock_irq), flags);
    }
}
/*******************************************************************************
* �� �� ��  : get_read_node
* ��������  : UART ��ȡ��ǰд��ַ
* �������  : uart_ctx ������
* �������  : NA
* �� �� ֵ  : д��ַ
*******************************************************************************/
uart_mem_node* get_read_node(hsuart_ctx *uart_ctx)
{
    uart_mem_node* pMemNode;
	
    if (NULL == uart_ctx->read_info.pcur_pos)
    {
        pMemNode = get_mem_from_freelist(&(uart_ctx->read_info));
        if (pMemNode)
        {
            if (!pMemNode->pSkb)
            {
                if (OK != hsuart_alloc_skb(pMemNode, uart_ctx->read_info.node_size))
                {
                    add_mem_to_freelist(&(uart_ctx->read_info), pMemNode);
                    pMemNode = NULL;
                    uart_ctx->stat.alloc_skb_fail++;
                }
            }
            uart_ctx->read_info.pcur_pos = pMemNode;
        }
    }
    else
    {
        pMemNode = uart_ctx->read_info.pcur_pos;        
    }
    
    return pMemNode;
}
/*******************************************************************************
* �� �� ��  : check_mem_to_donelist
* ��������  : �������ݼ��
* �������  : uart_ctx ������ pMemNode �ڴ�ڵ�
* �������  : NA
* �� �� ֵ  : NA
*******************************************************************************/
s32 check_mem_to_donelist(hsuart_ctx *uart_ctx, uart_mem_node* pMemNode)
{
    s32 ret = ERROR;
	u32 i =0;
	char *adap_addr =NULL;
    if (uart_ctx->baud_adapt)
    {
		bsp_softtimer_delete(&g_hsuart_ctrl.adapt_timer);
		/*��������AT �Ƿ�ɹ�*/
        if (memcmp("AT", pMemNode->mem.vaddr, 2) && memcmp("at", pMemNode->mem.vaddr, 2))
        {
            hsuart_debug("baud adapt fail!   idx:%d baud:%d\n", uart_ctx->baud_idx, typical_baud[uart_ctx->baud_idx]);
/*debug*/			
			adap_addr = (char *)pMemNode->mem.vaddr;
			for(i=0;i<pMemNode->valid_size;i++)
			{
				printk("adapt data 0x%x\n",*adap_addr);
				adap_addr++;
			}
           
/*debug*/			
            pMemNode->valid_size = 0;			
    		hsuart_fifo_reset(&uart_ctx->dev);
    		hsuart_set_baud(&uart_ctx->dev, 0);
        }
        else
        {
            hsuart_error("baud adapt success!   idx:%d baud:%d\n", uart_ctx->baud_idx, typical_baud[uart_ctx->baud_idx]);			
			uart_ctx->baud_adapt = HSUART_FALSE;
            add_mem_to_donelist(&uart_ctx->read_info, pMemNode);
            ret = OK;
        }
    }
    else
    {
        if (!switch_mode_cmd_detect(uart_ctx, pMemNode))
        {
            add_mem_to_donelist(&uart_ctx->read_info, pMemNode);
            ret = OK;
        }
    }
    return ret;
}
/*****************************************************************************
* �� �� ��  : hsuart_dma_tx_complete
* ��������  : UART DMA ģʽ������ɺ���
* �������  : arg: �豸����ṹָ��
*             int_status: �ж�״̬
* �������  :
* �� �� ֵ  : NA
*****************************************************************************/
void hsuart_dma_rx_complete(u32 arg, u32 int_status)
{
    //hsuart_ctx *uart_ctx = (hsuart_ctx *)arg;
  
    hsuart_debug("UART RX DMA transfer complete.\n");
    //uart_ctx->dma_info.rx_dma_done = HSUART_TRUE;
	g_dma_ctrl.rx_dma_done = HSUART_TRUE;
	g_dma_ctrl.dma_done_flag = HSUART_TRUE;
    up(&g_dma_ctrl.edma_rx_sem);
}
/*****************************************************************************
* �� �� ��  : hsuart_rx_dma
* ��������  : UART DMA ģʽ�������ݺ���
* �������  : uart_dev: �豸����ṹָ��
*             dma_handle: �������ݻ����ַ
*             length: �������ݳ���
* �������  :
* �� �� ֵ  : DMA channel id
*****************************************************************************/
s32 hsuart_rx_dma(hsuart_dev *uart_dev, u32 dma_handle, u32 length)
{
    s32 ret_id = 0;
    hsuart_ctx *uart_ctx = NULL;

    uart_ctx = container_of(uart_dev, hsuart_ctx, dev);
    
    ret_id = bsp_edma_channel_init(uart_dev->dma_req_rx, hsuart_dma_rx_complete, (u32)uart_ctx, BALONG_DMA_INT_DONE);
    if (ret_id < 0)
    {
        hsuart_error("balong_dma_channel_init error ret_id = %d\n", ret_id);
        return ERROR;
    }
    if (bsp_edma_channel_set_config(ret_id, BALONG_DMA_P2M, EDMA_TRANS_WIDTH_32, EDMA_BUR_LEN_16))
    {
        hsuart_error("balong_dma_channel_set_config failed! ret_id = %d\n", ret_id);
        return ERROR;
    }  
    if (bsp_edma_channel_async_start(ret_id, (u32)(uart_dev->phy_addr_base + UART_REGOFF_RBR), dma_handle, length))
    {
        hsuart_error("balong_dma_channel_async_start transfer failed! ret_id = %d\n", ret_id);
        return ERROR;
    } 
    return ret_id;
}
/*******************************************************************************
* �� �� ��  : hsuart_rx_complete
* ��������  : �������
* �������  : uart_ctx ������
* �������  : NA
* �� �� ֵ  : NA
*******************************************************************************/
void hsuart_rx_complete(hsuart_ctx *uart_ctx)
{
    uart_mem_node* pMemNode;
    
    pMemNode = uart_ctx->read_info.pcur_pos;
    if (!pMemNode)
    {
		hsuart_error("pMemNode is null!\n");
		return;
    }
    
   	if (uart_ctx->cbs.read_cb)
   	{
       	skb_put(pMemNode->pSkb, pMemNode->valid_size);		/*ʹ�ñ�׼��API���޸�len */
		if (OK == check_mem_to_donelist(uart_ctx, pMemNode))
        {
            uart_ctx->read_info.total_bytes += pMemNode->valid_size;
            uart_ctx->cbs.read_cb();
            uart_ctx->read_info.pcur_pos = NULL;
        }
    }
    else
    {
       hsuart_error("ReadCb is null.\n");
       pMemNode->valid_size = 0;
    }
}
/*****************************************************************************
* �� �� ��  : hsuart_burst_dma_transfer
* ��������  : UART dma���ݰ���
* �������  : uart_ctx ��pMemNode
* �������  : NA
* �� �� ֵ  : NA
*****************************************************************************/
void hsuart_burst_dma_transfer(hsuart_ctx *uart_ctx, uart_mem_node* pMemNode)
{
    u32 start_addr = 0;
	hsuart_dev *uart_dev;
	u32 switch_scurrent_time = 0;
	u32 switch_delta_time = 0;
	u32 switch_last_time = 0;
	uart_dev = &uart_ctx->dev;
    //uart_ctx->dma_info.rx_dma_done
	g_dma_ctrl.rx_dma_done = HSUART_FALSE;
	g_dma_ctrl.dma_done_flag = HSUART_FALSE;
	
	pMemNode->mem.paddr = dma_map_single(NULL, pMemNode->mem.vaddr , uart_ctx->read_info.node_size,DMA_FROM_DEVICE);
	
    start_addr = (u32)pMemNode->mem.paddr;
	
	g_dma_ctrl.pMemNode_startaddr = (u32)pMemNode->mem.paddr;
	g_dma_ctrl.pMemNode_viraddr = (u32)pMemNode->mem.vaddr;
	g_dma_ctrl.channel_id = hsuart_rx_dma(&uart_ctx->dev, start_addr, uart_ctx->read_info.node_size);
	g_dma_ctrl.dma_run_flag = HSUART_TRUE;
	
	switch_scurrent_time = bsp_get_slice_value();

	(void)writel(0x10,uart_dev->vir_addr_base+ UART_REGOFF_IER);
	down(&g_dma_ctrl.edma_rx_sem);
	writel(UART_IER_IRQ_DISABLE, uart_dev->vir_addr_base + UART_REGOFF_IER);
	switch_last_time = bsp_get_slice_value();
	switch_delta_time = get_timer_slice_delta(switch_scurrent_time ,switch_last_time);
	//hsuart_debug("switch_scurrent_time %d\n",switch_delta_time);
	switch_delta_time = (switch_delta_time/SYS_TICK_32K)*1000;
	if(switch_delta_time >= SWITCH_TIMER_LENGTH && uart_ctx->stage == DETECT_STAGE_1)
	{
		uart_ctx->stage = DETECT_STAGE_2;
		//hsuart_debug("uart_ctx->stage is DETECT_STAGE_2\n");
	}
	
	else if(switch_delta_time >= SWITCH_TWO_TIMER_LENGTH && uart_ctx->stage == DETECT_STAGE_2)
	{
		uart_ctx->stage = DETECT_STAGE_1;
		//hsuart_debug("uart_ctx->stage change DETECT_STAGE_1\n");
	}
    if (g_dma_ctrl.rx_dma_done)
    {
		hsuart_error("burst dma transfer done!\n");
		pMemNode->valid_size = uart_ctx->read_info.node_size;
        uart_ctx->stat.burst_dma_done++;
		return;
    }
	else
	{
		pMemNode->valid_size =  g_dma_ctrl.total_size;
	}

	//hsuart_debug("\nrecv data %s\n",(char *)pMemNode->mem.vaddr);
	g_dma_ctrl.dma_run_flag = HSUART_FALSE;
}
/*****************************************************************************
* �� �� ��  : hsuart_rx_thread
* ��������  : UART �ײ�����߳�
* �������  : ctx ����
* �������  : NA
* �� �� ֵ  : NA
*****************************************************************************/
s32 hsuart_rx_thread(void *ctx)
{
    hsuart_ctx *uart_ctx = (hsuart_ctx *)ctx;
    uart_mem_node* pMemNode = NULL;
    
    if(NULL == ctx)
	{
       hsuart_error("uart_ctx is NULL\n");
	   return ERROR;
	}
    while (1)
    {
		if (!uart_ctx->rts)
        {
            pMemNode = get_read_node(uart_ctx);
            if (pMemNode)
            {
                while (uart_ctx->read_info.pcur_pos)
                {
                    hsuart_burst_dma_transfer(uart_ctx, pMemNode);									
					bsp_softtimer_delete(&g_hsuart_ctrl.switch_state3_timer);
                    if (DETECT_STAGE_3 == uart_ctx->stage)
                    {
                        uart_ctx->stage = DETECT_STAGE_1;
                    }

                    if (pMemNode->valid_size)
                    {
                        hsuart_debug("valid_size:0x%x\n", (u32)pMemNode->valid_size);
                        hsuart_rx_complete(uart_ctx);
                    }
                }
				hsuart_debug("**********\n");
            }
            else
            {
                msleep(1);
				hsuart_error("pmemnode null\n");
            }
        }
        else
        {
            msleep(1);
			hsuart_error("rx thread idle\n");
        }   
  }
   
    return 0;
}
/*****************************************************************************
* �� �� ��  : hsuart_tx_thread
* ��������  : UART �ײ㷢���߳�
* �������  : ctx ����
* �������  : NA
* �� �� ֵ  : NA
*****************************************************************************/
s32 hsuart_tx_thread(void *ctx)
{
    hsuart_ctx *uart_ctx = (hsuart_ctx *)ctx;
	hsuart_dev *uart_dev = &uart_ctx->dev;    

    uart_mem_node* pMemNode = NULL;
    
	if(NULL == ctx)
	{
       hsuart_error("uart_ctx is NULL\n");
	   return ERROR;
	}
    while (1)
    {
        if (!uart_ctx->baud_adapt)		/* ����������Ӧ�ڼ䲻�ϱ���Ϣ*/
        {
           	//uart_ctx->tx_running = HSUART_FALSE;
            down(&(uart_ctx->tx_sema));
            //uart_ctx->tx_running = HSUART_TRUE;
            pMemNode = get_mem_from_donelist(&(uart_ctx->write_info));
            while (pMemNode)
            {
				hsuart_debug("enter. pSkb:0x%x, valid_size:0x%x\n", (unsigned int)pMemNode->pSkb, (unsigned int)pMemNode->valid_size);//debug
				hsuart_tx_dma(uart_dev, (u32)pMemNode->mem.paddr, pMemNode->valid_size); 				
				down(&uart_ctx->dma_sema);  

                if (uart_ctx->cbs.free_cb)
                {
                    uart_ctx->cbs.free_cb((char*)pMemNode->pSkb);
					if (pMemNode->pSkb)
					{
						pMemNode->pSkb = NULL;
					}
                }				
                else
                {
                    uart_ctx->stat.write_not_free_cnt++;
                    hsuart_error("no write free func register.\n");
                    kfree_skb(pMemNode->pSkb);
					pMemNode->pSkb = NULL;
                }
                add_mem_to_freelist(&(uart_ctx->write_info), pMemNode);
                pMemNode = get_mem_from_donelist(&(uart_ctx->write_info));
            }			
            set_hsuart_feature(uart_ctx);		/* NAS�յ�AT������ظ��Է�OK��ʼ����uart���� */
        }
        else
        {
            msleep(10);
        }
    }
    return 0;
}
/*****************************************************************************
* �� �� ��  : hsuart_irq
* ��������  : uart �жϷ������
* �������  : irq:�жϺ�
*             dev_id:����
* �������  : NA
* �� �� ֵ  : �жϷ���ֵ
*****************************************************************************/
irqreturn_t hsuart_irq(int irq, void *ctx)
{
   	u32 ulInt = 0;
	u32 ulCharNum = 0;
	u32 Data = 0;
	u32 i = 0;
    u32 cur_addr = 0;
	u8 *recvTemp = 0;
	u32 cur_transfered = 0;
	u32 recv_addr = 0;
	hsuart_dev *uart_dev = NULL;
	uart_dev = (hsuart_dev *)ctx;
	
    ulInt = readl(uart_dev->vir_addr_base+ UART_REGOFF_IIR);
    ulInt &= UART_FIFO_MASK;
	
    if(ulInt == UART_IIR_REV_TIMEOUT && g_dma_ctrl.dma_done_flag == HSUART_FALSE) //���ճ�ʱ�ж�
    {	
		hsuart_debug("irq\n");
		ulCharNum = readl(uart_dev->vir_addr_base + 0x84);
		if(ulCharNum == 0)
		{
			readl(uart_dev->vir_addr_base + UART_REGOFF_RBR);
			return (irqreturn_t)IRQ_NONE;
		}
		g_dma_ctrl.total_size = ulCharNum;
		cur_addr = bsp_edma_channel_stop(g_dma_ctrl.channel_id);
		cur_transfered = cur_addr - g_dma_ctrl.pMemNode_startaddr;
		recv_addr = (g_dma_ctrl.pMemNode_viraddr + cur_transfered);

		g_dma_ctrl.total_size += cur_transfered;
		while(ulCharNum)
		{
			if(ulCharNum >= 4)
			{
				Data = readl(uart_dev->vir_addr_base + UART_REGOFF_RBR);
				*(u32 *)recv_addr = Data;
				recv_addr += 4;
				ulCharNum = ulCharNum - 4;
			}
			else
			{	
				Data = readl(uart_dev->vir_addr_base + UART_REGOFF_RBR);
				recvTemp = (u8 *)&Data;
				for(i = 0; i <ulCharNum; i++)
				{		
					*(u8 *)recv_addr = recvTemp[i];
					recv_addr++;					
				}
				break;
			}	
		}
		up(&g_dma_ctrl.edma_rx_sem);
    }
	else
	{
		hsuart_error("rx edma running\n");
		if(ulCharNum == 0)
		{
			readl(uart_dev->vir_addr_base + UART_REGOFF_RBR);
			return (irqreturn_t)IRQ_NONE;
		}
	}
	//dma_ctrl.irq_flag = HSUART_TRUE;
	writel(UART_IER_IRQ_DISABLE, uart_dev->vir_addr_base + UART_REGOFF_IER);

	return (irqreturn_t)IRQ_HANDLED;
}

/*****************************************************************************
* �� �� ��  : hsuart_write_async
* ��������  : UART UDI �豸�첽дʵ��
* �������  : uart_ctx: ������
*             pWRInfo: �ڴ���Ϣ
* �������  : NA
* �� �� ֵ  : ����� �ɹ�/ʧ��
*****************************************************************************/
s32 hsuart_write_async(hsuart_ctx* uart_ctx, hsuart_wr_async_info* pWRInfo)
{
    struct sk_buff* tx_skb;
    uart_mem_node* pMemNode;

    if (NULL == pWRInfo)
    {
        hsuart_error("pWRInfo:0x%x\n", (unsigned int)pWRInfo);
        return ERROR;
    }
    tx_skb = (struct sk_buff*)pWRInfo->pBuffer;
    pMemNode = get_mem_from_freelist(&(uart_ctx->write_info));
    if (pMemNode)
    {
        pMemNode->pSkb = tx_skb;
        pMemNode->valid_size = pMemNode->pSkb->len;
        pMemNode->mem.vaddr = (void*)pMemNode->pSkb->data;
        pMemNode->mem.paddr = dma_map_single(NULL, pMemNode->mem.vaddr, pMemNode->valid_size, DMA_TO_DEVICE);
        add_mem_to_donelist(&(uart_ctx->write_info), pMemNode);
    }
    else
    {
        hsuart_error("no free node, tx_skb:0x%x.\n", (unsigned int)tx_skb);
        return ERROR;
    }  
    up(&(uart_ctx->tx_sema));  
    return OK;
}

/*****************************************************************************
* �� �� ��  : hsuart_get_read_buffer
* ��������  : �ϲ��ȡ����buf ����Ϣ
* �������  :  uart_ctx ������, 
* �������  :  pWRInfo ���ڴ���Ϣ
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 hsuart_get_read_buffer(hsuart_ctx* uart_ctx, hsuart_wr_async_info* pWRInfo)
{
    uart_mem_node* pMemNode = NULL;
    
    if (NULL == pWRInfo)
    {
        hsuart_error("pWRInfo:0x%x.\n", (unsigned int)pWRInfo);
        return ERROR;
    }
    
    /* ��ȡ��ɵ� buffer�ڵ� */
    pMemNode = get_mem_from_donelist(&(uart_ctx->read_info));
    if (pMemNode)
    {
        pWRInfo->pBuffer = (char *)pMemNode->pSkb;
        pWRInfo->u32Size = (u32)pMemNode->pSkb->len;
        pWRInfo->pDrvPriv = (void*)pMemNode->pSkb;      
        add_mem_to_freelist(&(uart_ctx->read_info), pMemNode);
        //(void)hsuart_alloc_skb(pMemNode, uart_ctx->read_info.node_size);
    }
    else
    {
        hsuart_error("no done mem node in list\n");
        return ERROR;
    }
    return OK;
}

/*****************************************************************************
* �� �� ��  : hsuart_return_read_buffer
* ��������  : �ϲ��ͷŽ���Buffer �Ľӿ�
* �������  : uart_ctx ������, pWRInfo �ڴ���Ϣ
* �������  :
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 hsuart_return_read_buffer(hsuart_ctx* uart_ctx, hsuart_wr_async_info* pWRInfo)
{
    if(NULL == pWRInfo)
	{
       hsuart_error("pWRInfo is NULL\n");
	   return ERROR;
	}
    dev_kfree_skb((struct sk_buff *)pWRInfo->pBuffer);
	pWRInfo->pBuffer = NULL;
    return OK;
}
/*****************************************************************************
* �� �� ��  : hsuart_modem_write_signal
* ��������  :дmodem �ܽ��ź�
* �������  :uart_dev �豸�ṹ��pModemMsc �ܽ���Ϣ
* �������  :
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 hsuart_modem_write_signal(hsuart_ctx *uart_ctx, MODEM_MSC_STRU* pModemMsc)
{    
	if(NULL == uart_ctx)
	{
       hsuart_error("uart_ctx is NULL\n");
	   return ERROR;
	}    
    if (uart_ctx->feature.rts)					/*����DCE rts �ܽ�*/
    {
        if (SIGNALCH == pModemMsc->OP_Cts)
        {
            if (LOWLEVEL == pModemMsc->ucCts)	/*����rts �ܽ�*/
            {
                uart_ctx->rts = HSUART_TRUE;
                hsuart_set_rts(&uart_ctx->dev);
                hsuart_debug("rts valued:%d\n", pModemMsc->ucCts);//DEBUG
            }
            else								/*����rts �ܽ�*/
            {               
                uart_ctx->rts = HSUART_FALSE;
                hsuart_clear_rts(&uart_ctx->dev);
                hsuart_debug("rts invalued:%d\n", pModemMsc->ucCts);//DEBUG
            }
        }
    }
#ifdef HSUART_4_LINE
#else
    if (SIGNALCH == pModemMsc->OP_Ri)		/*Ring SIGNAL CHANGE*/
    {
        gpio_direction_output(HSUART_RING, !pModemMsc->ucRi); 
        hsuart_error("Ring change:%d\n", !pModemMsc->ucRi);//DEBUG
    }   
    if (SIGNALCH == pModemMsc->OP_Dsr)		/*DSR SIGNAL CHANGE*/
    {
        gpio_direction_output(HSUART_DSR, !pModemMsc->ucDsr); 
        hsuart_error("dsr change:%d\n", !pModemMsc->ucDsr);//DEBUG
    }  
    if (SIGNALCH == pModemMsc->OP_Dcd)		/* DCD SIGNAL CHANGE*/
    {
        gpio_direction_output(HSUART_DCD, !pModemMsc->ucDcd); 
        hsuart_error("dcd change:%d\n", !pModemMsc->ucDcd);//DEBUG
    }
#endif
    return OK;
}

/*****************************************************************************
* �� �� ��  : hsuart_realloc_read_buf
* ��������  : ���·��������
* �������  : uart_ctx ������pReadBuffInfo �ڴ���Ϣ
* �������  :
* �� �� ֵ  :ʧ��/�ɹ�
*****************************************************************************/
s32 hsuart_realloc_read_buf(hsuart_ctx* uart_ctx, hsuart_read_buff_info* pReadBuffInfo)
{
    unsigned long flags = 0;

    if (NULL == uart_ctx || NULL == pReadBuffInfo)
    {
        hsuart_error("uart_ctx:0x%x   pReadBuffInfo:0x%x.\n", (unsigned int)uart_ctx, (unsigned int)pReadBuffInfo);
        return ERROR;
    }  
    if ((uart_ctx->read_info.node_num != pReadBuffInfo->u32BuffNum) || (uart_ctx->read_info.node_size != pReadBuffInfo->u32BuffSize))
    {
        hsuart_uninit_list(&(uart_ctx->read_info));
		spin_lock_irqsave(&(uart_ctx->dev.lock_irq), flags);
        uart_ctx->read_info.node_num = pReadBuffInfo->u32BuffNum;
        uart_ctx->read_info.node_size = pReadBuffInfo->u32BuffSize;
		spin_unlock_irqrestore(&(uart_ctx->dev.lock_irq), flags);
        if (hsuart_init_list(&(uart_ctx->read_info)))
        {
            hsuart_error("hsuart_init_rw_list error.\n");
            return ERROR;
        }       
    }
    return OK;
}

/*****************************************************************************
* �� �� ��  : hsuart_mode_switch_config
* ��������  : ģʽ�л�����
* �������  : uart_ctx ������s32Arg ���ò���
* �������  :
* �� �� ֵ  :NA
*****************************************************************************/
void hsuart_mode_switch_config(hsuart_ctx* uart_ctx, void* s32Arg)
{
    //unsigned long flags = 0;
    
    if (NULL == s32Arg)
    {
		bsp_softtimer_delete(&g_hsuart_ctrl.switch_state3_timer);
		
        uart_ctx->stage = NO_DETECT_STAGE;
		uart_ctx->cbs.switch_mode_cb= NULL;
        hsuart_debug("detect mode switch disable\n");
    }
    else
    {
        uart_ctx->stage = DETECT_STAGE_1;
		uart_ctx->cbs.switch_mode_cb = (hsuart_switch_mode_cb_t)s32Arg;
		hsuart_debug("detect mode switch enable\n");
    }
}

/*****************************************************************************
* �� �� ��  : hsuart_set_flow_ctrl
* ��������  : uart���ؿ���
* �������  : uart_ctx ������s32Arg ���ò���
* �������  :
* �� �� ֵ  :NA
*****************************************************************************/
void hsuart_set_flow_ctrl(hsuart_ctx* uart_ctx, uart_flow_ctrl_union* pParam)
{
	u32 val = 0;
    u32 mask = UART_AFCE_ENABLE | UART_RTS_ENABLE;
	u32 regval = 0;
    unsigned long flags = 0;
	if(pParam->reg.rtsen == 1)
	{
		regval |= (1<<14);
	}
	if(pParam->reg.ctsen == 1)
	{
		regval |= (1<<15);
	}
   	spin_lock_irqsave(&(uart_ctx->dev.lock_irq), flags);
   	val = readl(uart_ctx->dev.vir_addr_base + UART_REG_OFFSET_MCR);
    val &= regval | (~mask);
    val |= regval & mask;
	(void)writel(val, uart_ctx->dev.vir_addr_base + UART_REG_OFFSET_MCR);

    uart_ctx->feature.rts = pParam->reg.rtsen;
    uart_ctx->feature.afce = pParam->reg.ctsen;
    spin_unlock_irqrestore(&(uart_ctx->dev.lock_irq), flags);
}

/*****************************************************************************
* �� �� ��  : hsuart_udi_open
* ��������  : ��uart udi�豸
* �������  : param ����, handle ���
* �������  :
* �� �� ֵ  : �򿪽��
*****************************************************************************/
s32 hsuart_udi_open(UDI_OPEN_PARAM *param, UDI_HANDLE handle)
{
    hsuart_ctx *uart_ctx = &m2m_hsuart_ctx;
    uart_ctx->open = HSUART_TRUE;
    (void)BSP_UDI_SetPrivate(param->devid, (VOID*)uart_ctx);
    return OK;
}
/*****************************************************************************
* �� �� ��  : hsuart_udi_close
* ��������  : �ر�uart udi�豸
* �������  : handle
* �������  :
* �� �� ֵ  :ʧ��/�ɹ�
*****************************************************************************/
s32 hsuart_udi_close(BSP_S32 s32UartDevCtx)
{
    hsuart_ctx *pUartDevCtx = (hsuart_ctx *)s32UartDevCtx;   
    pUartDevCtx->open = HSUART_FALSE;
    return OK;
}

/*****************************************************************************
* �� �� ��  : hsuart_udi_write
* ��������  : uartУ׼ͬ�����ͽӿ�
* �������  : BSP_S32 s32UartDev, BSP_U8* pBuf, u32 u32Size
* �������  : ʵ��д�������
* �� �� ֵ  :ʧ��/ʵ�ʵ�����
*****************************************************************************/
s32 hsuart_udi_write(VOID* pPrivate, void* pMemObj, u32 u32Size)
{
    s32 num = 0;
	hsuart_ctx *uart_ctx = (hsuart_ctx *)pPrivate;

    if (NULL == uart_ctx || NULL == pMemObj || 0 == u32Size)
    {
        hsuart_error("Invalid params.\n");
        return ERROR;
    }
    if (!uart_ctx->open)
    {
        hsuart_error("uart is not open.\n");
        return ERROR;
    }    
    uart_ctx->stat.syn_write_cnt++;
    num = get_list_node_num(&uart_ctx->write_info.done_list);
    hsuart_debug("start addr:0x%x  len:%d  done list num:%d.\n", (unsigned int)pMemObj, u32Size, num);
    while (num)
    {
        msleep(1);
        num = get_list_node_num(&uart_ctx->write_info.done_list);
    }
    dialup_hsuart_send((u8 *)pMemObj, u32Size);  
    return OK;
}

/*****************************************************************************
* �� �� ��  : hsuart_udi_ioctl
* ��������  : UART ����ҵ����� ioctl ����
* �������  : s32UartDevId: �豸����ṹָ��
*             s32Cmd: ������
*             pParam: �������
* �������  :
* �� �� ֵ  : �ɹ�/ʧ�ܴ�����
*****************************************************************************/
s32 hsuart_udi_ioctl(VOID* pPrivate, u32 u32Cmd, VOID* pParam)
{
    s32 ret = OK;
    unsigned long flags = 0;
    hsuart_ctx* uart_ctx = (hsuart_ctx*)pPrivate;
    hsuart_dev *uart_dev = NULL;
	DRV_DIALUP_HSUART_STRU dialup_acshell_nv;

	if(NULL == uart_ctx)
	{
       hsuart_error("uart_ctx is NULL\n");
	   return ERROR;
	}
    hsuart_debug("cmd:0x%x  pParam:0x%x\n", u32Cmd, (unsigned int)pParam);
    
    if (!uart_ctx->open)
    {
        hsuart_error("uart is not open.\n");
        return ERROR;
    }  
    uart_dev = &uart_ctx->dev;
    switch(u32Cmd)
    {      
        case UART_IOCTL_WRITE_ASYNC:		/* �����첽д�ӿ�*/
        	ret = hsuart_write_async(uart_ctx, (hsuart_wr_async_info *)pParam);
        	break;
        case UART_IOCTL_SET_FREE_CB:		/* NASע����������buf �ͷź���*/
        	uart_ctx->cbs.free_cb = (hsuart_free_cb_t)pParam;
        	break;
        case UART_IOCTL_SET_READ_CB:		/* �յ����ݺ���ô�ע��ӿ�֪ͨ�ϲ����*/
        	uart_ctx->cbs.read_cb = (hsuart_read_cb_t)pParam;
        	break;        
        case UART_IOCTL_GET_RD_BUFF:		/* �ϲ���ô˽ӿڻ������buf ��ַ���ϲ������ǵ�read�ص���������ʵ�ֵ�*/
        	ret = hsuart_get_read_buffer(uart_ctx, (hsuart_wr_async_info*)pParam);
        	break;
        case UART_IOCTL_RETURN_BUFF:		/* �ϲ���ô˽ӿ��ͷ�����buf */
           	ret = hsuart_return_read_buffer(uart_ctx, (hsuart_wr_async_info*)pParam);
        	break;       
        case UART_IOCTL_RELLOC_READ_BUFF:	/* ���·��䵥��buffer��С����*/
        	ret = hsuart_realloc_read_buf(uart_ctx, (hsuart_read_buff_info*)pParam);
        	break;     
        case UART_IOCTL_SET_MSC_READ_CB:	/*ע��DTR�ܽű仯֪ͨ�ص�����ΪpMODEM_MSC_STRU ָ�򱾵�ȫ��*/
        	uart_ctx->cbs.msc_read_cb = (hsuart_msc_read_cb_t)pParam;
	        break;       
        case UART_IOCTL_MSC_WRITE_CMD:		 /*дmodem�ܽ��źţ�����ΪpMODEM_MSC_STRU*/
        	ret = hsuart_modem_write_signal(uart_ctx, (MODEM_MSC_STRU*)(pParam));
        	break;        
        case UART_IOCTL_SWITCH_MODE_CB:		/* +++�л�����ģʽ�ص�������NULL�رոù��� */
        	hsuart_mode_switch_config(uart_ctx, pParam);
        	break;            
        case UART_IOCTL_SET_BAUD:			/* ���ò����� */
            spin_lock_irqsave(&(uart_ctx->dev.lock_irq), flags);
            uart_ctx->cbs.set_baud_cb = hsuart_set_baud;
            uart_ctx->feature.baud = *(int*)pParam;
            spin_unlock_irqrestore(&(uart_ctx->dev.lock_irq), flags);
            hsuart_debug("set baud cb: %d\n", *(int*)pParam);
        	break;
        case UART_IOCTL_SET_WLEN:			/* �������ݳ��� */
            spin_lock_irqsave(&(uart_ctx->dev.lock_irq), flags);
            uart_ctx->cbs.set_wlen_cb = hsuart_set_wlen;
            uart_ctx->feature.wlen = *(int*)pParam;
            spin_unlock_irqrestore(&(uart_ctx->dev.lock_irq), flags);
            hsuart_debug("set wlen cb: %d\n", *(int*)pParam);
        	break;
        case UART_IOCTL_SET_STP2:			/* ����ֹͣλ */
            spin_lock_irqsave(&(uart_ctx->dev.lock_irq), flags);           
            uart_ctx->cbs.set_stp2_cb = hsuart_set_stpbit;
            uart_ctx->feature.stp2 = *(int*)pParam;            
            spin_unlock_irqrestore(&(uart_ctx->dev.lock_irq), flags);
            hsuart_debug("set stp2 cb: %d\n", *(int*)pParam);
        	break;
        case UART_IOCTL_SET_EPS:		 	/* ����У������ */
            spin_lock_irqsave(&(uart_ctx->dev.lock_irq), flags);
            uart_ctx->cbs.set_eps_cb = hsuart_set_eps;
           	uart_ctx->feature.eps = *(int*)pParam;
            spin_unlock_irqrestore(&(uart_ctx->dev.lock_irq), flags);
            hsuart_debug("set eps cb: %d\n", *(int*)pParam);
        	break;
        case UART_IOCTL_SET_FLOW_CONTROL:	/* �������� */
            hsuart_set_flow_ctrl(uart_ctx, (uart_flow_ctrl_union*)pParam);
        	break;
        case UART_IOCTL_SET_AC_SHELL:		 /*set A/C shell �ն����� debug*/
			dialup_acshell_nv.DialupACShellCFG = *(unsigned int*)pParam;
			dialup_acshell_nv.DialupEnableCFG  = HSUART_ENABLE;
			ret = bsp_nvm_write(NV_ID_DRV_DIALUP_ACSHELL, (u8 *)&dialup_acshell_nv, sizeof(DRV_DIALUP_HSUART_STRU));
			if (ret != OK)
   			{
        		hsuart_error("write %d NV ERROR\n",NV_ID_DRV_DIALUP_ACSHELL);
        		return ERROR;
    		}
            break;
        default:
            hsuart_error("unknow Cmd: 0x%x\n", u32Cmd);
            ret = ERROR;
            break;
    }
    return ret;
}

/*****************************************************************************
* �� �� ��  : hsuart_timer_init
* ��������  : 
* �������  : uart_ctx ������
* �������  : NA
* �� �� ֵ  : �ɹ�/ʧ��bcmsdh_register_oob_intr
*****************************************************************************/
int hsuart_timer_init(hsuart_ctx *uart_ctx)
{
	struct softtimer_list *statethree_timer = &g_hsuart_ctrl.switch_state3_timer;
	struct softtimer_list *baud_adapt_timer = &g_hsuart_ctrl.adapt_timer;
	
	statethree_timer->func = switch_stage_three;
	statethree_timer->para = (u32)&m2m_hsuart_ctx;
	statethree_timer->timeout = SWITCH_TIMER_LENGTH;
	statethree_timer->wake_type = SOFTTIMER_NOWAKE;

	baud_adapt_timer->func = set_next_adapt;
	baud_adapt_timer->para = (u32)&m2m_hsuart_ctx;
	baud_adapt_timer->timeout = ADAPT_TIMER_LENGTH;
	baud_adapt_timer->wake_type = SOFTTIMER_NOWAKE;

	if(OK != bsp_softtimer_create(statethree_timer))
	{
		hsuart_error("statethree_timer create fail...\n");
	}

	if(OK != bsp_softtimer_create(baud_adapt_timer))
	{
		hsuart_error("baud_adapt_timer create fail...\n");
		goto fail_adapt_timer;
	}

	return 0;
fail_adapt_timer:
	bsp_softtimer_free(statethree_timer);
	return ERROR;	
}

#ifdef CONFIG_PM
static s32 dialup_hsuart_suspend(struct device *dev)
{
	hsuart_ctx *uart_ctx = &m2m_hsuart_ctx;
	hsuart_dev *uart_dev = &uart_ctx->dev;
	hsuart_debug("dialup hsuart suspend\n");
	
	if(g_hsuart_ctrl.ACSHELL_FLAG == HSUART_FALSE)
	{
		bsp_edma_channel_stop(g_dma_ctrl.channel_id);
		bsp_edma_channel_stop(EDMA_CH_HSUART_TX);
		disable_irq(gpio_to_irq(HSUART_DTR));
		disable_irq((unsigned int)uart_dev->irq);
		uart_ctx->feature.lcr = readl(uart_dev->vir_addr_base+ UART_REGOFF_LCR);
		uart_ctx->feature.mcr = readl(uart_dev->vir_addr_base+ UART_REG_OFFSET_MCR);
	}
	return OK;
}
extern s32 hsuart_acshell_baud(hsuart_dev *uart_dev);

static s32 dialup_hsuart_resume(struct device *dev)
{
	u32 regval = 0;
	struct clk *hsuart_clk = NULL;
	hsuart_ctx *uart_ctx = &m2m_hsuart_ctx;
	hsuart_dev *uart_dev = &uart_ctx->dev;

	hsuart_debug("dialup hsuart resume\n");

	hsuart_clk = clk_get(NULL, "hs_uart_clk");
	if(hsuart_clk == NULL)
	{
		hsuart_error("hsuart get clk fail\n");
		return ERROR;
	}
	clk_enable(hsuart_clk);
	if(g_hsuart_ctrl.ACSHELL_FLAG == HSUART_FALSE)
	{
		if (DMA_TRANSFER == uart_ctx->transfer_mode)
		{
			regval = UART_DEF_RT_ONEFOUR|UART_DEF_TET_ONETWO|UART_DEF_DMA_MODE|UART_TX_FIFO_RESET|UART_RX_FIFO_RESET|UART_FCR_FIFO_ENABLE;
			writel(regval , uart_dev->vir_addr_base+ UART_REGOFF_FCR);		
		}
		else
		{
			regval = UART_DEF_RT_ONEFOUR|UART_DEF_TET_ONETWO|UART_DEF_NO_DMA_MODE|UART_TX_FIFO_RESET|UART_RX_FIFO_RESET|UART_FCR_FIFO_ENABLE;
			writel(regval , uart_dev->vir_addr_base+ UART_REGOFF_FCR);		
		}
		
		hsuart_set_baud(uart_dev, uart_ctx->feature.baud);	
		writel(uart_ctx->feature.lcr , uart_dev->vir_addr_base+ UART_REGOFF_LCR);
		writel(UART_DEF_TX_DEPTH, uart_dev->vir_addr_base +  UART_REG_OFFSET_TX_FF_DEPTH);
		writel(uart_ctx->feature.mcr ,uart_dev->vir_addr_base+ UART_REG_OFFSET_MCR);
		writel(UART_IER_IRQ_DISABLE, uart_dev->vir_addr_base + UART_REGOFF_IER);
		readl(uart_dev->vir_addr_base + UART_REGOFF_LSR);
		readl(uart_dev->vir_addr_base + UART_REGOFF_USR);
		readl(uart_dev->vir_addr_base + UART_REGOFF_RBR);
		readl(uart_dev->vir_addr_base + UART_REGOFF_IIR);

		enable_irq(gpio_to_irq(HSUART_DTR));
		enable_irq((unsigned int)uart_dev->irq);

		{
			if(g_dma_ctrl.dma_run_flag == HSUART_TRUE)
			{
				if (bsp_edma_channel_async_start(g_dma_ctrl.channel_id, (u32)(uart_dev->phy_addr_base + UART_REGOFF_RBR), g_dma_ctrl.pMemNode_startaddr, uart_ctx->read_info.node_size))
	    		{
	        		hsuart_error("balong_dma_channel_async_start transfer failed! ret_id = %d\n", g_dma_ctrl.channel_id);
	        		return ERROR;
	    		}
				(void)writel(0x10,  uart_dev->vir_addr_base+ UART_REGOFF_IER);
			}
		}	
	}
	else
	{
		hsuart_acshell_resume();
	}
	return OK;
}
static const struct dev_pm_ops dialup_hsuart_pm_ops ={
	.suspend = dialup_hsuart_suspend,
	.resume = dialup_hsuart_resume,
};
#define BALONG_DEV_PM_OPS (&dialup_hsuart_pm_ops)
#else
#define BALONG_DEV_PM_OPS NULL
#endif

#define DRIVER_NAME "dialup_hsuart_device"
static struct platform_driver dialup_hsuart_driver = {
	.probe = NULL,
	.remove = NULL,
	.driver = {
		.name = DRIVER_NAME,
		.owner  = THIS_MODULE,
		.pm     = BALONG_DEV_PM_OPS,
	},
};

static struct platform_device dialup_hsuart_device =
{
    .name = DRIVER_NAME,
    .id       = -1,
    .num_resources = 0,
};
/*****************************************************************************
* �� �� ��  : hsuart_drv_init
* ��������  : uart �ײ��ʼ������
* �������  : uart_ctx:uart������
* �������  : NA
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 hsuart_drv_init(hsuart_ctx *uart_ctx)
{
    s32 ret = ERROR;
	u32 regval = 0;
    hsuart_dev *uart_dev = NULL;

    if(NULL == uart_ctx)
	{
       hsuart_error("uart_ctx is NULL\n");
	   return ERROR;
	}
    uart_dev = &uart_ctx->dev;
    spin_lock_init(&uart_dev->lock_irq);
	
    uart_dev->vir_addr_base = ioremap(uart_dev->phy_addr_base,SIZE_4K);

	memset(&uart_ctx->cbs, 0, sizeof(hsuart_udi_cbs));
    memset(&uart_ctx->stat, 0, sizeof(hsuart_stat));
	
	uart_ctx->open = HSUART_TRUE;
    uart_ctx->baud_adapt = HSUART_FALSE;
    uart_ctx->baud_idx = DEFAULT_BAUD_IDX;
    uart_ctx->stage = DETECT_STAGE_1;
	uart_ctx->rts = HSUART_FALSE;
    uart_ctx->feature.baud = DEFAULT_BAUD;
	g_dma_ctrl.rx_dma_done = HSUART_FALSE;
    osl_sem_init(SEM_EMPTY,&(uart_ctx->tx_sema));
    osl_sem_init(SEM_EMPTY,&(uart_ctx->dma_sema));
    osl_sem_init(SEM_EMPTY,&g_dma_ctrl.edma_rx_sem);
    if (hsuart_buf_init(uart_ctx) != OK)
    {
        hsuart_error("hsuart_buf_init is error.\n");
        return ERROR;
    }

	if (DMA_TRANSFER == uart_ctx->transfer_mode)
	{
		regval = UART_DEF_RT_ONEFOUR|UART_DEF_TET_ONETWO|UART_DEF_DMA_MODE|UART_TX_FIFO_RESET|UART_RX_FIFO_RESET|UART_FCR_FIFO_ENABLE;
		writel(regval , uart_dev->vir_addr_base+ UART_REGOFF_FCR);		
	}
/*
	else
	{
		regval = UART_DEF_RT_ONEFOUR|UART_DEF_TET_ONETWO|UART_DEF_NO_DMA_MODE|UART_TX_FIFO_RESET|UART_RX_FIFO_RESET|UART_FCR_FIFO_ENABLE;
		writel(regval , uart_dev->vir_addr_base+ UART_REGOFF_FCR);
	}
*/
	/* ���ò����� */
    hsuart_set_baud(uart_dev, uart_ctx->feature.baud);	
	
    writel(UART_LCR_DLS_8BITS | UART_LCR_STOP_1BITS |UART_LCR_PEN_NONE, uart_dev->vir_addr_base + UART_REGOFF_LCR);
	writel(UART_AFCE_ENABLE|UART_RTS_ENABLE ,uart_dev->vir_addr_base + UART_REG_OFFSET_MCR);
    writel(UART_DEF_TX_DEPTH, uart_dev->vir_addr_base +  UART_REG_OFFSET_TX_FF_DEPTH);
	writel(UART_IER_IRQ_DISABLE, uart_dev->vir_addr_base + UART_REGOFF_IER);	
	readl(uart_dev->vir_addr_base + UART_REGOFF_LSR);
	readl(uart_dev->vir_addr_base + UART_REGOFF_RBR);
	readl(uart_dev->vir_addr_base + UART_REGOFF_IIR);
	readl(uart_dev->vir_addr_base + UART_REGOFF_USR);
	
	ret = request_irq((unsigned int)uart_dev->irq, (irq_handler_t)hsuart_irq,0,"HS UART ISR", &uart_ctx->dev);
	if (ret != OK)
	{
	   	hsuart_error("request_irq is failed!\n");
	    return ERROR;
	}	
    hsuart_gpio_init(uart_ctx);
	hsuart_timer_init(uart_ctx);	
    return OK;
}

static UDI_DRV_INTEFACE_TABLE hsuart_udi = {
    .udi_open_cb = (UDI_OPEN_CB_T)hsuart_udi_open,
    .udi_close_cb = (UDI_CLOSE_CB_T)hsuart_udi_close,
    .udi_write_cb = (UDI_WRITE_CB_T)hsuart_udi_write,
    .udi_read_cb = (UDI_READ_CB_T)NULL,
    .udi_ioctl_cb = (UDI_IOCTL_CB_T)hsuart_udi_ioctl,
};
/*****************************************************************************
* �� �� ��  : hsuart_udi_init
* ��������  : UART UDI ��ʼ���ӿ�
* �������  : NA
* �������  : NA
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
int hsuart_udi_init(void)
{
	s32 ret = ERROR;
	struct clk *hsuart_clk = NULL;
	hsuart_ctx *uart_ctx = &m2m_hsuart_ctx;
    DRV_DIALUP_HSUART_STRU dialup_acshell_nv;
  

    uart_ctx->init = HSUART_FALSE;
	memset(&dialup_acshell_nv,0,sizeof(DRV_DIALUP_HSUART_STRU));
	ret = bsp_nvm_read(NV_ID_DRV_DIALUP_ACSHELL, (u8 *)&dialup_acshell_nv, sizeof(DRV_DIALUP_HSUART_STRU));
	if (ret != OK)
	{
	   	hsuart_error("read %d NV ERROR\n",NV_ID_DRV_DIALUP_ACSHELL);
	   	return ERROR;
	}
	if(HSUART_ENABLE == dialup_acshell_nv.DialupEnableCFG)
	{
		hsuart_error("hsuart init enable\n");
		
		hsuart_clk = clk_get(NULL, "hs_uart_clk");
		if(hsuart_clk == NULL)
		{
			hsuart_error("hsuart get clk fail\n");
			return ERROR;
		}
		clk_enable(hsuart_clk);
		
		ret = platform_device_register(&dialup_hsuart_device);
		if(ret)
		{
			hsuart_error("Platform hsuart device register is failed!\n");
			clk_disable(hsuart_clk);
	        return ret;
		}
		ret = platform_driver_register(&dialup_hsuart_driver);
		if (ret)
		{
			hsuart_error("Platform hsuart deriver register is failed!\n");
			platform_device_unregister(&dialup_hsuart_device);
			clk_disable(hsuart_clk);
			return ret;
		}
	  	/* A/C shell�˿� */
		if((dialup_acshell_nv.DialupACShellCFG == UART_C_SHELL) || (dialup_acshell_nv.DialupACShellCFG == UART_A_SHELL))
		{
			g_hsuart_ctrl.ACSHELL_FLAG = HSUART_TRUE;
			ret = hsuart_shell_init(dialup_acshell_nv);
			if(ret != OK)
			{
				goto init_fail;
			}
			
			dialup_acshell_nv.DialupACShellCFG = 0;
			ret = bsp_nvm_write(NV_ID_DRV_DIALUP_ACSHELL, (u8 *)&dialup_acshell_nv, sizeof(DRV_DIALUP_HSUART_STRU));
			if (ret != OK)
	   		{
	        	hsuart_error("write %d NV ERROR\n",NV_ID_DRV_DIALUP_ACSHELL);
				goto init_fail;
	    	}
		}
		/* �����˿� */
		else
		{	
		    if (OK != hsuart_drv_init(uart_ctx))
		    {
		        hsuart_error("hsuart_drv_init create failed!\n");
				goto init_fail;
		    }
			if (ERROR == osl_task_init("uart_recv_thread",HSUART_RX_TASK_PRI,HSUART_RX_TASK_SIZE,(void *)hsuart_rx_thread,(void *)uart_ctx,
										&g_hsuart_ctrl.rx_task_id))
			{
			  	hsuart_error("uart rx thread create failed!\n");
				goto init_fail;
			}
			if (ERROR == osl_task_init("uart_send_thread",HSUART_TX_TASK_PRI,HSUART_TX_TASK_SIZE,(void *)hsuart_tx_thread,(void *)uart_ctx,
										&g_hsuart_ctrl.tx_task_id))
			{
			   	hsuart_error("uart tx thread create failed!\n");
				goto init_fail;
			}

			/* UDI��ĳ�ʼ�� */
	    	(void)BSP_UDI_SetCapability(uart_ctx->udi_device_id, 0);
	    	(void)BSP_UDI_SetInterfaceTable(uart_ctx->udi_device_id, &hsuart_udi);
			uart_ctx->init = HSUART_TRUE;
		}
	}
	return OK;

init_fail:
	platform_device_unregister(&dialup_hsuart_device);
	platform_driver_unregister(&dialup_hsuart_driver);
	clk_disable(hsuart_clk);
	return ERROR;
}

module_init(hsuart_udi_init);

void hsuart_set_loglevel(u32 temp)
{
	bsp_mod_level_set(BSP_MODU_HSUART , temp);
}


