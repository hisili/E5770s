
/*lint --e{537}*/
#include <linux/semaphore.h>    /*����mutex�����ͷ�ļ�*/
#include <linux/kthread.h>      /*�����߳�*/
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <bsp_memmap.h>
#include <osl_types.h>
#include <bsp_om.h>
#include <bsp_shared_ddr.h>
#include <soc_interrupts.h>
#include <bsp_pm.h>
#include <osl_spinlock.h>
#include "at_uart_balong.h"

/*lint --e{63, 527, 550, 681, 958} */
struct uart_at_mng g_uart_at_infor = {1, 0, {0}, {0}, NULL};

/*****************************************************************************
* �� �� ��  : uart_at_open
* ��������  : ��uart�豸
* �������  : dev_id  �豸����ṹָ��
* �������  : flag
            : mode
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
static s32 uart_at_open(s32 dev_id, s32 flag, s32 mode)
{
	UART_CTX_S* uart_dev_ctx = (UART_CTX_S*)dev_id;

	if (NULL == uart_dev_ctx)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AT_UART, "[AT UART ERROR]:\n\t\t\t <func>: %s;  <line>: %d; dev_id is null\n\n", (int)__FUNCTION__, (int)__LINE__);
		return BSP_ERROR;
	}
	if (uart_dev_ctx->bOpen)
	{
		bsp_trace(BSP_LOG_LEVEL_WARNING, BSP_MODU_AT_UART, "[AT UART ERROR]:\n\t\t\t <func>: %s;  <line>: %d; UartDevCtx is opened\n\n", (int)__FUNCTION__, (int)__LINE__);
		return BSP_ERROR;
	}
	uart_dev_ctx->bOpen = TRUE;
	/*��Ϊ�ڳ�ʼ����ʱ���Ѿ������ˣ�just ���phy���CTX������*/
	if(BSP_OK != get_uart_port((u32)uart_dev_ctx))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AT_UART, "[AT UART ERROR]:\n\t\t\t <func>: %s;  <line>: %d; uart_at_open is failed\n\n", (int)__FUNCTION__, (int)__LINE__);
		return BSP_ERROR;
	}
	return ((s32)uart_dev_ctx);
}

/*****************************************************************************
* �� �� ��  : udi_uart_at_open
* ��������  : ��uart�豸
* �������  : UDI_OPEN_PARAM *param, UDI_HANDLE handle
* �������  :
* �� �� ֵ  : �����ļ����
*
*****************************************************************************/
static s32 bsp_uart_at_open(UDI_OPEN_PARAM *param, UDI_HANDLE handle)
{
	s32 fd = 0;

	fd = uart_at_open((s32)(&g_uart_at_infor.UartCtx), 0, 0);
	if (fd == -1)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AT_UART, "[AT UART ERROR]:\n\t\t\t <func>: %s;  <line>: %d; BSP_MODU_UDI open fail\n\n", (int)__FUNCTION__, (int)__LINE__);
		return BSP_ERROR;
	}
	(void)BSP_UDI_SetPrivate(param->devid, (void*)fd);
	return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : bsp_uart_at_write
*
* ��������  : uart���ͽӿ�
*
* �������  : s32 s32UartDev, u8* pBuf, u32 u32Size
* �������  : ʵ��д�������

*
* �� �� ֵ  : ʧ��/ʵ�ʵ�����
*
*****************************************************************************/
s32 bsp_uart_at_write(s32 uart_dev_ctx, unsigned char * buffer, u32 size)
{
	UART_CTX_S* p_uart_dev_ctx = (UART_CTX_S*) uart_dev_ctx;
	s32 ret;

	/*�ػ�����*/
#ifdef MSP_IF_IOCTL_TEST
	int i = 0;
	(void)printk("\n#########DL DATA ##########\n");
	for(i = 0; i< (s32)size;i++)
	{
		(void)printk("%x ",(u8)buffer[i]);
	}
	(void)printk("\n");
#endif

	if(TRUE != p_uart_dev_ctx->bOpen )
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AT_UART,
			"[AT UART ERROR]:\n\t\t\t <func>: %s;  <line>: %d; uart at is not opend\n\n",
			(int)__FUNCTION__, (int)__LINE__);
		return BSP_ERROR;
	}
	down(&g_uart_at_infor.UartCtx.MSP_Tx_Sem);
	/*����UartCtx*/
	ret = uart_send((s32)p_uart_dev_ctx,buffer,size);
	if (ret == (s32)size)
	{
		/*����UART����ҪDMA�ڴ棬�����Ļ������ͳɹ�Ҳ����ҪDRV�ͷ�*/
	}
	else
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AT_UART, "[AT UART ERROR]:\n\t\t\t <func>: %s;  <line>: %d; uart_send failed\n\n", (int)__FUNCTION__, (int)__LINE__);
		return BSP_ERROR;
	}
	up(&g_uart_at_infor.UartCtx.MSP_Tx_Sem);
	return (ret);
}/*lint !e529*/
/*****************************************************************************
* �� �� ��  : bsp_uart_at_close
* ��������  : �ر�uart�豸
* �������  : handle
* �������  :
* �� �� ֵ  :ʧ��/�ɹ�
*****************************************************************************/
s32 bsp_uart_at_close(s32 uart_dev_ctx)
{
	UART_CTX_S *p_uart_dev_ctx = (UART_CTX_S *)uart_dev_ctx;
	p_uart_dev_ctx->bOpen = FALSE;
	return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : bsp_uart_at_ioctrl
* ��������  : UART ҵ����� ioctl ����
* �������  : uart_dev_id: �豸����ṹָ��
*             s32Cmd: ������
*             s32Arg: �������
* �������  :
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 bsp_uart_at_ioctrl(s32 uart_dev_id, s32 cmd, s32 arg)
{
	UART_CTX_S* p_uart_ctx = (UART_CTX_S*)uart_dev_id;
	s32 ret = BSP_OK;

	if (NULL == p_uart_ctx || !p_uart_ctx->bOpen)
	{
		(void)printk("THE PARAM IS ERROR\n");
		return BSP_ERROR;
	}
	switch(cmd)
	{
		/* 1ע�����е�buf�ͷź���OK */
		case UART_IOCTL_SET_WRITE_CB:
		p_uart_ctx->MSP_WriteCb = (UART_WRITE_DONE_CB_T)arg;
		break;
		/*3MSP���û������buf�ĵ�ַ�����������ǵ�read�ص������������õ�*/
		case UART_IOCTL_GET_RD_BUFF:
		{
			if (0 == arg)
			{
				(void)printk("write UART_IOCTL_WRITE_ASYNC invalid args\n");
				return BSP_ERROR;
			}
			ret = uart_at_get_read_buffer(uart_dev_id, (UART_WR_ASYNC_INFO*)arg);
		}
		break;
		/*4���ǽ�����buf��ַ����MSP����MSP�����ô˽ӿڽ����ͷ�*/
		case UART_IOCTL_RETURN_BUFF:
		{
			if (0 == arg)
			{
				(void)printk("write UART_IOCTL_RETURN_BUFF invalid args\n");
				return BSP_ERROR;
			}
			ret = uart_at_return_read_buffer(uart_dev_id, (UART_WR_ASYNC_INFO*)arg);
		}
		break;
		/*6MSP�Ľ��շ��ͺ����������յ����ݺ󣬻������ô˽ӿ�OK*/
		case UART_IOCTL_SET_READ_CB:
		{
			p_uart_ctx->MSP_ReadCb = (UART_READ_DONE_CB_T)arg;
			if(g_uart_at_infor.printkflag == 1)
			{
				(void)printk("p_uart_ctx->MSP_ReadCb ==  0X%x\n",(u32)p_uart_ctx->MSP_ReadCb);
			}
		}
		break;
		default:
		(void)printk("error cmd \n");
		break;
	}
	return ret;
}

/*****************************************************************************
* �� �� ��  : uart_at_init
* ��������  : UART ���õĳ�ʼ���ӿ�
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR
*****************************************************************************/
s32  uart_at_init(void)
{
	UDI_DRV_INTEFACE_TABLE* pDrvInterface = NULL;
	s32 ret = 0;

 	if(AT_UART_USE_FLAG != (*(u32 *)SHM_MEM_AT_FLAG_ADDR))
		return 0;

	pm_enable_wake_src(DRV_WAKE_SRC_UART0);
	spin_lock_init(&g_uart_at_infor.uart_port0.lock_irq);
	g_uart_at_infor.uart_port0.irq    = INT_LVL_UART0;
	g_uart_at_infor.uart_port0.vir_addr_base= (unsigned char *)HI_UART0_REGBASE_ADDR_VIRT;
	/*��ʼ�������ź���*/
	sema_init(&(g_uart_at_infor.uart_port0.uart_rx_sem), SEM_EMPTY);
	/*���������߳�*/
	if (!g_uart_at_infor.pstUartReadThread)
	{
		g_uart_at_infor.pstUartReadThread = kthread_run(uart_recv_thread, NULL, "UART_RX_KTHREAD");
		ret = IS_ERR(g_uart_at_infor.pstUartReadThread) ? PTR_ERR(g_uart_at_infor.pstUartReadThread) : 0;
		if (ret)
		{
			(void)printk("kthread_run is failed!\n");
			g_uart_at_infor.pstUartReadThread = NULL;
			return BSP_ERROR;
		}
	}
	if(uart_at_reg_init() != OK)
	{
		(void)printk("uart_at_reg_init is error\n");
		return BSP_ERROR;
	}
	if(uart_rx_buf_init() != OK)
	{
		(void)printk("uart_rx_buf_init is error\n");
		return BSP_ERROR;
	}
	sema_init(&(g_uart_at_infor.UartCtx.MSP_Tx_Sem), SEM_FULL);
	pDrvInterface = kmalloc(sizeof(UDI_DRV_INTEFACE_TABLE), GFP_KERNEL);
	if (NULL == pDrvInterface)
	{
		(void)printk("BSP_MODU_UDI NO Mem, line:%d\n", __LINE__);
		return BSP_ERROR;
	}
	memset((VOID*)pDrvInterface, 0, sizeof(UDI_DRV_INTEFACE_TABLE));
	/* ֻ������Ҫʵ�ֵļ����ӿ� */
	pDrvInterface->udi_open_cb = bsp_uart_at_open;
	pDrvInterface->udi_close_cb = (UDI_CLOSE_CB_T)bsp_uart_at_close;
	pDrvInterface->udi_write_cb = (UDI_WRITE_CB_T)bsp_uart_at_write;
	pDrvInterface->udi_ioctl_cb = (UDI_IOCTL_CB_T)bsp_uart_at_ioctrl;
	(BSP_VOID)BSP_UDI_SetCapability((UDI_DEVICE_ID)UDI_BUILD_DEV_ID(UDI_DEV_UART, 0), 0);
	(void)printk("UDI_BUILD_DEV_ID is 0x%x\n",UDI_BUILD_DEV_ID(UDI_DEV_UART, 0));
	(BSP_VOID)BSP_UDI_SetInterfaceTable((UDI_DEVICE_ID)UDI_BUILD_DEV_ID(UDI_DEV_UART, 0), pDrvInterface);
	g_uart_at_infor.UartCtx.bOpen = FALSE;
	return BSP_OK;
}
/*****************************************************************************
* �� �� ��  : uart_at_uninit
* ��������  : UART ���õĳ�ʼ���ӿ�
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR
*****************************************************************************/
void uart_at_uninit(void)
{
	uart_rx_buf_uinit();
	uart_at_reg_uninit();
}

/*****************************************************************************
* �� �� ��  : uart_find_mem_from_queue
* ��������  : �ҵ�push��MSP�ý��սڵ�
* �������  : s32 uart_dev_id, u8 *buf
* �������  :
* �� �� ֵ  :ʧ��/�ɹ�
*****************************************************************************/
s32 uart_realloc_read_buf(UART_CTX_S* p_uart_ctx, UART_READ_BUFF_INFO* pstReadBuffInfo)
{
	return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : creat_queue
* ��������  :���� ���ջ������
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR
*****************************************************************************/
s32 creat_queue(UART_RX_BUF_S *p_head,unsigned char *p_data_buf)
{
	int i = 1;
	int j = 0;
	int k = 0;
	UART_RX_BUF_S *p_temp = p_head;

	(void)printk("p_temp is 0x%x\n",(u32)p_temp);
	/*��������ѭ������*/
	for(k = 0; k < (int)RX_NUM; k++)
	{
		/*����data����*/
		p_temp->buf = (unsigned char*)&(p_data_buf[RX_SIZE*(u32)(j++)]);
		p_temp->ulSize = 0;
		/*������Ϣͷ*/
		p_temp->pstNext = (struct tagUART_RX_BUF_S *)(&p_head[(i++)%((int)RX_NUM)]);
		p_temp = p_temp->pstNext;
	}
	p_temp = NULL;
	if(g_uart_at_infor.printkflag == 1)
	{
		(void)printk("i is : %d\n",i);
		(void)printk("pTemp is 0x%x ?= pHead 0x%x\n",(u32)p_temp, (u32)p_head);
		(void)printk("out func creat_queue line is %d\n",__LINE__);
	}
	return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : uart_rx_buf_init
* ��������  :��ʼ�����ջ������
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR
*****************************************************************************/
s32 uart_rx_buf_init(void)
{
	/*malloc��Ϣͷ�ռ�*/
	g_uart_at_infor.UartCtx.pHead_RxQueue = (UART_RX_BUF_S*)kmalloc(sizeof(UART_RX_BUF_S)*RX_NUM, GFP_KERNEL);
	if(NULL == g_uart_at_infor.UartCtx.pHead_RxQueue)
	{
		(void)printk("kmalloc is failed\n");
		return BSP_ERROR;
	}
	/*�������ݵ�buf*/
	g_uart_at_infor.UartCtx.pDataBuf = (unsigned char *)kmalloc(RX_SIZE * RX_NUM ,GFP_KERNEL);
	if(NULL == g_uart_at_infor.UartCtx.pDataBuf)
	{
		(void)printk("kmalloc is failed\n");
		(void)kfree(g_uart_at_infor.UartCtx.pHead_RxQueue);
		g_uart_at_infor.UartCtx.pHead_RxQueue = NULL;
		return BSP_ERROR;
    }
	/*��������buf*/
	if (creat_queue(g_uart_at_infor.UartCtx.pHead_RxQueue,g_uart_at_infor.UartCtx.pDataBuf) != BSP_OK)
	{
		(void)printk("craet_queue is failed\n");
		(void)kfree(g_uart_at_infor.UartCtx.pHead_RxQueue);
		(void)kfree(g_uart_at_infor.UartCtx.pDataBuf);
		g_uart_at_infor.UartCtx.pHead_RxQueue = NULL;
		g_uart_at_infor.UartCtx.pDataBuf      = NULL;
		return BSP_ERROR;
	}
	/*���õ�ǰ��дָ��ָ��*/
	g_uart_at_infor.UartCtx.pstCurrRead  = g_uart_at_infor.UartCtx.pHead_RxQueue;
	g_uart_at_infor.UartCtx.pstCurrWrite = g_uart_at_infor.UartCtx.pHead_RxQueue;
	return BSP_OK;
}
/*****************************************************************************
* �� �� ��  : get_uart_port0
* ��������  : UART ���õĳ�ʼ���ӿ�
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR/OK
*****************************************************************************/
void uart_rx_buf_uinit(void)
{
	/*�ͷ��ڴ�*/
	(void)kfree(g_uart_at_infor.UartCtx.pHead_RxQueue);
	(void)kfree(g_uart_at_infor.UartCtx.pDataBuf);
	g_uart_at_infor.UartCtx.pHead_RxQueue = NULL;
	g_uart_at_infor.UartCtx.pDataBuf      = NULL;
	g_uart_at_infor.UartCtx.pstCurrRead   = NULL;
	g_uart_at_infor.UartCtx.pstCurrWrite  = NULL;
	return;
}

/*****************************************************************************
* �� �� ��  : get_uart_port0
* ��������  : UART ���õĳ�ʼ���ӿ�
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR/OK
*****************************************************************************/
s32 get_uart_port(u32 uart_dev_id)
{
	UART_CTX_S *p_uart_dev_ctx = (UART_CTX_S *) uart_dev_id;

	if(NULL == p_uart_dev_ctx)
	{
		(void)printk("the p_uart_dev_ctx is NULL line is %d\n",__LINE__);
		 return BSP_ERROR;
	}
	p_uart_dev_ctx->port = (UART_PORT_S*)(&g_uart_at_infor.uart_port0);
	return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : uart_at_return_read_buffer
* ��������  : MSP�ͷ�RX buf�Ľӿ�
* �������  : s32 uart_dev_id, ACM_WR_ASYNC_INFO* pWRInfo
* �������  :
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 uart_at_return_read_buffer(s32 uart_dev_id, ACM_WR_ASYNC_INFO* p_wr_info)
{
	UART_CTX_S* p_uart_ctx = (UART_CTX_S*)uart_dev_id;
	UART_RX_BUF_S* pMemInfo = NULL;

	if (NULL == p_uart_ctx || !p_uart_ctx->bOpen)
	{
		(void)printk("p_uart_ctx & p_uart_ctx->bOpen is error\n");
		return BSP_ERROR;
	}
	pMemInfo = p_wr_info->pDrvPriv;
	pMemInfo->ulSize = 0;/*�������ǹ黹�ڴ�*/
	return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : uart_at_get_read_buffer
* ��������  : MSP ��ȡ����buf����Ϣ
* �������  : s32 uart_dev_id, ACM_WR_ASYNC_INFO* pWRInfo
* �������  :
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 uart_at_get_read_buffer(s32 uart_dev_id, ACM_WR_ASYNC_INFO* p_wr_info)
{
	UART_CTX_S* p_uart_ctx = (UART_CTX_S*)uart_dev_id;
	UART_RX_BUF_S* pMemInfo = NULL;
	if (NULL == p_uart_ctx || !p_uart_ctx->bOpen)
	{
		(void)printk("p_uart_ctx & p_uart_ctx->bOpen is error\n");
		return BSP_ERROR;
	}
	/* ��ȡ��ɵ� buffer�ڵ� */
	pMemInfo = p_uart_ctx->pstCurrRead;
	p_wr_info->pBuffer = (BSP_CHAR *)pMemInfo->buf; /*������ָ�������*/
	p_wr_info->u32Size = (u32)pMemInfo->ulSize; /*���ݵĴ�С*/
	p_wr_info->pDrvPriv = (void*)pMemInfo;          /*��ǰ��Ϣͷָ��*/
	return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : uart_at_rx_chars
* ��������  : UART�ײ���պ���
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR
*****************************************************************************/
static void uart_at_rx_chars(void)
{
	u32 status;
	u8 ch;
	s8 max_count = RX_SIZE;/*һ�����ݿ�Ĵ�С*/
	u8 *writebuf = g_uart_at_infor.UartCtx.pstCurrWrite->buf;

	status = readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_LSR);
	while ((max_count > 0) && (status & 0x01))
	{
		ch = (u8)readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_RBR);
		*writebuf++ = ch;
		/*UartCtx.pstCurrWrite->ulSize��ʼֵΪ0*/
		g_uart_at_infor.UartCtx.pstCurrWrite->ulSize++;
		status = readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_LSR);
		max_count--;
	}
	if((g_uart_at_infor.UartCtx.pstCurrWrite->pstNext == g_uart_at_infor.UartCtx.pstCurrRead) ||
		(g_uart_at_infor.UartCtx.pstCurrWrite->pstNext->ulSize !=0))
	{
		(void)printk("buf is full\n");
	}
	else
	{
		g_uart_at_infor.UartCtx.pstCurrWrite = g_uart_at_infor.UartCtx.pstCurrWrite->pstNext;
	}
	up(&g_uart_at_infor.uart_port0.uart_rx_sem);
	return;
}

/*****************************************************************************
* �� �� ��  : uart_recv_thread
* ��������  : UART�ײ�����߳�
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR
*****************************************************************************/
/*�ݽ����ϲ�֮����bufΪ������MSP������*/
static int uart_recv_thread(void *data)
{
    UNUSED(data);
	/* coverity[no_escape] */
	for(;;)
	{
		down(&g_uart_at_infor.uart_port0.uart_rx_sem);
		while(g_uart_at_infor.UartCtx.pstCurrRead->ulSize != 0)
		{
			if(g_uart_at_infor.UartCtx.MSP_ReadCb)
			{
#ifdef MSP_IF_IOCTL_TEST
				if(g_uart_at_infor.printkflag == 1)
				{
					ACM_WR_ASYNC_INFO pWRinfo;
					int i = 0;
					(void)printk("UartCtx.MSP_ReadCb =0X%x",g_uart_at_infor.UartCtx.MSP_ReadCb);
					(void)printk("UartCtx.pstCurrRead:%x\n",g_uart_at_infor.UartCtx.pstCurrRead);
					if(BSP_OK == uart_at_get_read_buffer((s32)(&g_uart_at_infor.UartCtx),&pWRinfo))
					{
						(void)printk("#####pWRinfo->u32Size==%d\n",pWRinfo.u32Size);
						for(i = 0;i < (s32)pWRinfo.u32Size; i++)
						{
							(void)printk("%x ",(u8)(pWRinfo.pBuffer)[i]);
						}
					}
				}
#endif
				g_uart_at_infor.UartCtx.MSP_ReadCb();
				g_uart_at_infor.UartCtx.pstCurrRead->ulSize = 0;//��������MSP��"�ͷ�"�����ڴ棬����DRV������0
			}
			else /*һ�������Ѿ�ע���֮�󣬾Ͳ����������֧��*/
			{
				if(g_uart_at_infor.buf_look == 0)
				{
					(void)uart_send((s32)(&g_uart_at_infor.UartCtx),g_uart_at_infor.UartCtx.pstCurrRead->buf,g_uart_at_infor.UartCtx.pstCurrRead->ulSize);
				}
				g_uart_at_infor.UartCtx.pstCurrRead->ulSize = 0;
			}
			/*һ��buf�������֮��,ָ���Ƶ���һ��buf*/
			if(g_uart_at_infor.UartCtx.pstCurrRead != g_uart_at_infor.UartCtx.pstCurrWrite)
			{
				g_uart_at_infor.UartCtx.pstCurrRead = g_uart_at_infor.UartCtx.pstCurrRead->pstNext;
			}
			else/*����û�������ˣ���ô�ͻ���������ѭ�����ȴ��ź����ĵ���*/
			{
				(void)printk("data is empty\n");
				break;
			}
		}
	}
    return 0;
}/*lint !e529*/

/*****************************************************************************
* �� �� ��  : uart_int
* ��������  : uart �жϷ������
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR
*****************************************************************************/
static irqreturn_t uart_int(void)
{
	u32 interrupt_id;
	u32 status;
	s32 handled = 0;
	unsigned long irq_flag = 0;

	spin_lock_irqsave(&(g_uart_at_infor.uart_port0.lock_irq), irq_flag);
    status = readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_IIR);
	interrupt_id = 0x0F&status;
	while ((interrupt_id != DW_NOINTERRUPT))
	{
		/*����������Ч*/
		if ((DW_RECEIVEAVA == interrupt_id) ||
			(DW_RECTIMEOUT == interrupt_id))    /*timeout interrupt*/
		{
			uart_at_rx_chars();
		}
		else
		{
			(void)readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_LSR);
			(void)readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_USR);
			handled = 1;
			break;
		}
		status = readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_IIR);
		interrupt_id = 0x0F&status;
		handled = 1;
	}
	spin_unlock_irqrestore(&(g_uart_at_infor.uart_port0.lock_irq), irq_flag);
	return IRQ_RETVAL(handled);/*lint !e64*/
}
/*****************************************************************************
* �� �� ��  : uart_at_tx_chars
* ��������  : uart �ײ㷢�ͺ���
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR
*****************************************************************************/
static int uart_at_tx_chars(u8 *p_uart_tx_buf,u32 size)
{
	s32 Cnt = (s32)size;
	u32 UsrValue = 0;

	/*����������Ա�֤�ܹ���MSP�����ݷ��͵�FIFO����ȥ*/
	do
	{
		UsrValue = readl(g_uart_at_infor.uart_port0.vir_addr_base + DW_UART_TFL);
		if (UsrValue < FIFO_TX_SIZE)
		{
			writel(*p_uart_tx_buf, g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_THR);
			p_uart_tx_buf++;
#ifdef MSP_IF_IOCTL_TEST
			if(g_uart_at_infor.printkflag == 1)
			{
				(void)printk("%x ",(u8)(*(p_uart_tx_buf-1)));
			}
#endif
			Cnt--;
		}
	}while (Cnt > 0);
	return BSP_OK;
}
/*****************************************************************************
* �� �� ��  : uart_send
* ��������  : uart �ײ㷢�ͺ���
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR
*****************************************************************************/
s32 uart_send(s32 s32uart_dev_id, u8 *pbuf, u32 size)
{
	UART_CTX_S *p_uart_ctx = (UART_CTX_S *)s32uart_dev_id;
	u8 *p_uart_tx_buf  = (u8 *)pbuf;

	if (NULL == p_uart_tx_buf || NULL == p_uart_ctx)
	{
		(void)printk("the parm is error\n");
		return BSP_ERROR;
	}
	if(uart_at_tx_chars(p_uart_tx_buf,size)!= BSP_OK)
	{
		(void)printk("uart_at_tx_chars is FAILED,line is %d\n",__LINE__);
		return BSP_ERROR;
	}
	return ((s32)size);
}
/*****************************************************************************
* �� �� ��  : uart_at_reg_init
* ��������  : uart �ײ��ʼ������
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR
*****************************************************************************/
s32 uart_at_reg_init(void)
{
	u32 lcr_reg   = 0;
	u32 lcr_value = 0;
	u32 enbaud    = 0;
	s32 ret       = 0;

	/* ʹ�� DLL �� DLH ��д���*/
	enbaud = enbaud | DW_UART_DLAB;
	(void)writel(enbaud,g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_LCR);
	/* ���ò����� */
	(void)writel( DLL_BUAD_PARA, g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_DLL);
	(void)writel( DLH_BUAD_PARA, g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_DLH);
	/*�ر�DLL��DLH�����*/
	enbaud &= ~DW_UART_DLAB;/* [false alarm]:�� */
	(void)writel(enbaud, g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_LCR);
	/*LCR����****���ݳ���8λ+   ֹͣ2λ  +  У��ʹ�� + żУ��*/
	lcr_reg = lcr_reg | DW_UART_8bit;/* [false alarm]:�� */
	(void)writel(lcr_reg, g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_LCR);
	lcr_value = readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_LCR);
	(void)printk("the lcr_reg is %x\n",lcr_value);
	/* ��ֹ FIFO���ж� */
	(void)writel(0,g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_IER);
	/* enable FIFO */
	(void)writel(0x1, g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_FCR);
	/*set fifo trigger level*/
	(void)writel(0xb1,g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_FCR);
	/*clear and reset fifo*/
	(void)writel(0xb7,g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_FCR);
	/* clear line interrupt status */
	(void)readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_LSR);
	/*clear rcv interrupt*/
	(void)readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_RBR);
	/*clear iir reg*/
	(void)readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_IIR);
	/*clear line busy interrupt*/
	(void)readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_USR);
	/*����ʹ���жϴ���*/
	ret = request_irq((unsigned int)g_uart_at_infor.uart_port0.irq, (irq_handler_t)uart_int, 0, "BalongV?R? ISR", NULL);
	if (ret)
	{
		(void)printk("request_irq is failed\n");
		return (s32)BSP_ERROR;
	}
	/*ʹ�� FIFO */
	/*�����������ó�ʱ�жϣ�оƬ�������*/
	/*(void)writel(DW_FCR_PARA, HI_UART0_REGBASE_ADDR_VIRT+ DW_UART_FCR);*/
	(void)readl(g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_LSR);
	(void)writel(ABLE_RX_IER, g_uart_at_infor.uart_port0.vir_addr_base  + UART_REGOFF_IER);
	return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : uart_write
* ��������  : uart �ײ��ʼ������
* �������  : ��
* �������  : ��
* �� �� ֵ  : BSP_ERROR
*****************************************************************************/
void uart_at_reg_uninit(void)
{
	(void)writel(0x0, g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_IER);
	(void)writel(0x0, g_uart_at_infor.uart_port0.vir_addr_base + UART_REGOFF_FCR);
	free_irq((unsigned int)(g_uart_at_infor.uart_port0.irq), NULL);
}

subsys_initcall(uart_at_init);