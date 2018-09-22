
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

void hsuart_udi_test_01 (void)
{
	UDI_OPEN_PARAM hsuart_udi_id;
	UDI_HANDLE udi_handle = 0;
	hsuart_udi_id.devid = UDI_HSUART_0_ID;
	udi_handle = udi_open(&hsuart_udi_id);
	if(udi_handle <0)
	{
		printk("open hsuart udi failed\n");
	}
}

void hsuart_udi_test_08 (void)
{
	UDI_OPEN_PARAM hsuart_udi_id;
	UDI_HANDLE udi_handle = 0;
	hsuart_udi_id.devid = UDI_HSUART_0_ID;
	udi_handle = udi_open(&hsuart_udi_id);
	udi_close(udi_handle);
	if(udi_handle <0)
	{
		printk("close hsuart udi failed\n");
	}
}
void hsuart_udi_test_02(void)
{
    hsuart_wr_async_info WRInfo;
	
	UDI_OPEN_PARAM hsuart_udi_id;
	UDI_HANDLE udi_handle = 0;
	hsuart_udi_id.devid = UDI_HSUART_0_ID;
	udi_handle = udi_open(&hsuart_udi_id);
	if(udi_handle <0)
	{
		printk("open hsuart udi failed\n");
	}
    udi_ioctl(udi_handle, UART_IOCTL_GET_RD_BUFF, &WRInfo);
    udi_ioctl(udi_handle, UART_IOCTL_WRITE_ASYNC, &WRInfo);
}

void hsuart_udi_test_03(u8 val)
{
    hsuart_ctx *uart_ctx = &m2m_hsuart_ctx;
    static hsuart_read_cb_t bak;

    if (val)
    {
        bak = uart_ctx->cbs.read_cb;
        uart_ctx->cbs.read_cb = hsuart_udi_test_02;
    }
    else
    {
        uart_ctx->cbs.read_cb = bak;
    }
}

void hsuart_udi_test_04(u32 baud)
{
    int Param;	
	UDI_OPEN_PARAM hsuart_udi_id;
	UDI_HANDLE udi_handle = 0;
	Param = baud;
	hsuart_udi_id.devid = UDI_HSUART_0_ID;
	udi_handle = udi_open(&hsuart_udi_id);
	if(udi_handle <0)
	{
		printk("open hsuart udi failed\n");
	}
    
    udi_ioctl(udi_handle, UART_IOCTL_SET_BAUD, &Param);
}
void hsuart_udi_test_05(u32 rts, u32 afce)
{
    uart_flow_ctrl_union Param;
	UDI_OPEN_PARAM hsuart_udi_id;
	UDI_HANDLE udi_handle = 0;
    Param.reg.rtsen = rts;
    Param.reg.ctsen = afce;
	hsuart_udi_id.devid = UDI_HSUART_0_ID;
	udi_handle = udi_open(&hsuart_udi_id);
	if(udi_handle <0)
	{
		printk("open hsuart udi failed\n");
	}
    udi_ioctl(udi_handle, UART_IOCTL_SET_FLOW_CONTROL, &Param);
}

void hsuart_udi_test_06(u32 gpio_sel,u32 gpio_value)
{
	MODEM_MSC_STRU Param;
	UDI_OPEN_PARAM hsuart_udi_id;
	UDI_HANDLE udi_handle = 0;
	hsuart_udi_id.devid = UDI_HSUART_0_ID;
	udi_handle = udi_open(&hsuart_udi_id);
	if(udi_handle <0)
	{
		printk("open hsuart udi failed\n");
	}
	Param.OP_Ri = gpio_sel & 0x01;
	Param.OP_Dcd = (gpio_sel & 0x02)>>1;
	Param.OP_Dsr = (gpio_sel & 0x03)>>2;
	Param.ucRi = gpio_value & 0x01;
	Param.ucDcd = (gpio_value& 0x02)>>1;
	Param.ucDsr = (gpio_value& 0x03)>>2;
    udi_ioctl(udi_handle,UART_IOCTL_MSC_WRITE_CMD,&Param);
}
void hsuart_udi_test_07(char data)
{
	u32 regval = 0;
	u32 i = 0;
	for(i = 0;i < 10000;i++)
	{
		regval = readl(0xc2000000 + UART_REGOFF_USR);
    	if (0 != (regval & 0x02))
    	{		
			*(UINT8 *)(0xc2000000 + UART_REGOFF_THR) = data;
		}
		msleep(5);
	}
}

void hsuart_udi_test_send(char *string)
{
    u32 regval;
    while(1)
    {
		if(*string == '\0')
            break;
        regval = *(volatile UINT32 *)(0xc2000000 + UART_REGOFF_USR);
        if (0 != (regval & 0x02))
        {
            *(UINT8 *)(0xc2000000 + UART_REGOFF_THR) = *string++;
        }
        else
        {
            printk("Tx FIFO full\r\n");
        }
    }
}
void t_adapt_test(void)
{
	static char adapt_str[]={"AT"};
	u8 i =0;
	
	for(i=0;i<20;i++)
	{
		hsuart_udi_test_send(adapt_str);
		msleep(1000);
	}
}
void hsuart_test_data(void)
{
	unsigned int i;
    unsigned char str1[] = {"   :ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    static unsigned char str2[10*1024] = {0};
    u32 offset = 0;
    u32 len;

	for(i = 0; i < 300; i++)
    {
		str1[0] = i/100 + 0x30;
        str1[1] = (i/10)%10 + 0x30;
        str1[2] = (i%10) + 0x30;
        len = (i == 299)?31:30;
        memcpy(str2 + offset ,str1, len);      
        offset += 30;
    }
	hsuart_udi_test_send(str2);
}
void hsuart_read_reg(u32 offset)
{
    u32 status;	
    status = readl(0xc2000000 + offset);
    hsuart_error("offset:0x%x   value:0x%x !\n", offset, status);
}

void hsuart_write_reg(u32 offset, u32 value)
{
    (void)writel(value, 0xc2000000 + offset);   
    hsuart_error("write offset:0x%x   value:0x%x !\n", offset, value);
}
extern s32 get_list_node_num(struct list_head * pHeader);
/*****************************************************************************
* �� �� ��  : show_hsuart_info
*
* ��������  : UART ��ά�ɲ�ӿ�
*
* �������  : NA
* �������  : NA
*
* �� �� ֵ  : NA
*
*****************************************************************************/
void show_hsuart_info(void)
{
    hsuart_ctx *uart_ctx = &m2m_hsuart_ctx;
    u32 idx = 0;
    unsigned long flags = 0;
    
    if (uart_ctx->read_info.pcur_pos)
    {
        printk("current memnode valid size: %d \n", uart_ctx->read_info.pcur_pos->valid_size);
    }
	printk("pcur_pos: %x \n", (u32)uart_ctx->read_info.pcur_pos);
    printk("baud adapt status: %d \n", uart_ctx->baud_adapt);
    //printk("tx_running: %d \n", uart_ctx->tx_running);
    printk("total_bytes: %d \n", uart_ctx->read_info.total_bytes);
    
    printk("current detect stage: %d \n", uart_ctx->stage);
    printk("current baud: %d \n", uart_ctx->feature.baud);
    printk("current wlen: %d \n", uart_ctx->feature.wlen);
    printk("current stp2: %d \n", uart_ctx->feature.stp2);
    printk("current eps: %d \n", uart_ctx->feature.eps);
    
    printk("not free write data cnt: %d \n", uart_ctx->stat.write_not_free_cnt);
    printk("lost data cnt: %d \n", uart_ctx->stat.lost_data_cnt);
    printk("synchronization write cnt: %d \n", uart_ctx->stat.syn_write_cnt);
    printk("alloc_skb_fail: %d \n", uart_ctx->stat.alloc_skb_fail);
    printk("sleep_delay_cnt: %d \n", uart_ctx->stat.sleep_delay_cnt);

    /* ģ��δ��ʼ���������¿�ָ��*/
    if (uart_ctx->init)
    {
        spin_lock_irqsave(&uart_ctx->read_info.list_lock, flags);
        printk("read free node num: %d \n", get_list_node_num(&uart_ctx->read_info.free_list));
        printk("read done node num: %d \n", get_list_node_num(&uart_ctx->read_info.done_list));
        printk("read node num: %d \n", uart_ctx->read_info.node_num);
        printk("read node size: %d \n", uart_ctx->read_info.node_size);
        printk("read done cnt: %d \n", uart_ctx->read_info.done_cnt);
        for (idx = 0; idx < uart_ctx->read_info.node_num; idx++)
        {
            printk("node state: %d \n", uart_ctx->read_info.pmem_start[idx].state);
            printk("node size: %d \n", uart_ctx->read_info.pmem_start[idx].valid_size);
        }
        spin_unlock_irqrestore(&uart_ctx->read_info.list_lock, flags); 
        
        spin_lock_irqsave(&uart_ctx->write_info.list_lock, flags);
        printk("write free node num: %d \n", get_list_node_num(&uart_ctx->write_info.free_list));
        printk("write done node num: %d \n", get_list_node_num(&uart_ctx->write_info.done_list));
        printk("write node num: %d \n", uart_ctx->write_info.node_num);
        printk("write node size: %d \n", uart_ctx->write_info.node_size);
        printk("write done cnt: %d \n", uart_ctx->write_info.done_cnt);
        for (idx = 0; idx < uart_ctx->write_info.node_num; idx++)
        {
            printk("node state: %d \n", uart_ctx->write_info.pmem_start[idx].state);
            printk("node size: %d \n", uart_ctx->write_info.pmem_start[idx].valid_size);
        }
        spin_unlock_irqrestore(&uart_ctx->write_info.list_lock, flags);
    }
}