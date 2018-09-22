

#include <linux/kernel.h>       /*kmalloc,printk*/
#include <linux/kthread.h>      
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/console.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/serial_core.h>
#include <linux/amba/bus.h>
#include <linux/amba/serial.h>
#include <linux/delay.h>
#include "osl_malloc.h"
#include "dialup_acshell.h"

hsuart_ctx  acshell_hsuart_ctx = {
    .dev = {
        .irq = INT_LVL_HSUART,
        .clock = 48000000,
        .phy_addr_base = HI_HSUART_REGBASE_ADDR,
    },
};

static struct tty_driver *ghsuart_tty_driver = NULL;
static struct tty_struct *hsuart_tty;
s32 putincharsize = 0;

/*****************************************************************************
* �� �� ��  : hsUartSend
* ��������  : HS UART�������ݽӿں���
* �������  : UINT32  u32SrcAddr       �跢�͵����ݵ��׵�ַ
*             UINT32  u32TransLength   �跢�͵����ݵĳ���
* �������  : ��
* �� �� ֵ  : OK       �ɹ�
*             ERROR    ʧ��
*****************************************************************************/
void send4(u32 * pucSrcAddr ,u32 ulTimes)
{
    u32 regval;
    u32 *pu32Buffer;

    pu32Buffer = pucSrcAddr;

    while(ulTimes)
    {
        regval = readl(HSUART_BASE_VIRT_ADDR + UART_REGOFF_USR);
        if (0 != (regval & 0x02))
        {
            /* ���������е����ݷŵ����ݼĴ�����*/
            *(UINT32 *)(HSUART_BASE_VIRT_ADDR + UART_REGOFF_THR) = *pu32Buffer;
            pu32Buffer++;
        	ulTimes--;
        }
    }
    return;
}

void send2(u16 *pucSrcAddr ,u32 ulTimes)
{
    u32 regval;
    u16 *pu16Buffer;

    pu16Buffer = pucSrcAddr;

    while(ulTimes)
    {
        regval = readl(HSUART_BASE_VIRT_ADDR + UART_REGOFF_USR);
        if (0 != (regval & 0x02))
        {
            /* ���������е����ݷŵ����ݼĴ�����*/
            *(u16 *)(HSUART_BASE_VIRT_ADDR + UART_REGOFF_THR) = *pu16Buffer;
            pu16Buffer++;
        	ulTimes--;
        }
    }
    return;
}

void send1(u8 * pucSrcAddr ,u32 ulTimes)
{
    u32 regval;
    u8 * pu8Buffer;

    pu8Buffer = pucSrcAddr;

    while(ulTimes)
    {
        regval = readl(HSUART_BASE_VIRT_ADDR + UART_REGOFF_USR);
        if (0 != (regval & 0x02))
        {
            /* ���������е����ݷŵ����ݼĴ�����*/
            *(u8 *)(HSUART_BASE_VIRT_ADDR + UART_REGOFF_THR) = *pu8Buffer;
            pu8Buffer++;
        	ulTimes--;
        }
    }
    return;
}

/*****************************************************************************
* �� �� ��  : hsUartSend
* ��������  : HS UART�������ݽӿں���
* �������  : UINT32  u32SrcAddr       �跢�͵����ݵ��׵�ַ
*             UINT32  u32TransLength   �跢�͵����ݵĳ���
* �������  : ��
* �� �� ֵ  : OK       �ɹ�
*             ERROR    ʧ��
*****************************************************************************/
s32 dialup_hsuart_send(u8 * pucSrcAddr, u32 u32TransLength)
{
    u8 *pu8Buffer;
    u32 ulTimes;
    u32 ulLeft;

    /* ��������Ч�Լ�� */
    if(NULL == pucSrcAddr)
    {
		hsuart_error("param error\n");
		return ERROR;
    }
	if(acshell_recv_str.shell_flag == HSUART_TRUE)
	{
		pu8Buffer = acshell_recv_str.ptxbuff;
		memcpy(pu8Buffer,pucSrcAddr,u32TransLength);
	}
	else 
	{
		pu8Buffer = pucSrcAddr;
	}
	ulTimes = u32TransLength / 4;
    ulLeft = u32TransLength % 4;

    send4((u32 *)pu8Buffer, ulTimes);
    pu8Buffer = pu8Buffer + ulTimes * 4;

    if(ulLeft == 1)
    {
        send1(pu8Buffer, 1);
    }
    else if(ulLeft == 2)
    {
        send2((u16 *)pu8Buffer, 1);
    }
    else if(ulLeft == 3)
    {
        send2((u16 *)pu8Buffer, 1);
        pu8Buffer = pu8Buffer + 1*2;
        send1(pu8Buffer, 1);
    }
    return OK;
}

static int ghsuart_open(struct tty_struct *tty, struct file *file)
{		
		hsuart_tty = tty;
		return 0;
}

static void ghsuart_close(struct tty_struct *tty, struct file *file)
{
	tty->driver_data = NULL;
}

int hsuart_rx_tty_proc(u8 *buff,u32 lenth)
{
	struct tty_struct *tty;
	tty = hsuart_tty;
	
	tty_insert_flip_string(tty, buff, lenth);
	/* Flush tty flip buffer */
    tty_flip_buffer_push(tty);	
	
	return 0;
}

static int ghsuart_write(struct tty_struct *tty, const unsigned char *buf, int count)
{
	putincharsize = count;
	dialup_hsuart_send((u8 *)buf,(u32)count);
	return count;
}

static int ghsuart_put_char(struct tty_struct *tty, unsigned char ch)
{
	send1(&ch, 1);
	return 0;
}
static void ghsuart_flush_chars(struct tty_struct *tty)
{
	
}

static int ghsuart_write_room(struct tty_struct *tty)
{
	int	room = ACSHELL_TX_BUFF_SIZE - putincharsize;

	return room;
}

static int ghsuart_chars_in_buffer(struct tty_struct *tty)
{
	return putincharsize;
}

static const struct tty_operations ghsuart_ops = 
{
	.open =			ghsuart_open,
	.close =		ghsuart_close,
	.write =		ghsuart_write,
	.put_char =		ghsuart_put_char,
	.flush_chars =		ghsuart_flush_chars,
	.write_room =		ghsuart_write_room,
	.chars_in_buffer =	ghsuart_chars_in_buffer,
	.unthrottle =		NULL,
	.break_ctl =		NULL,
};

void hsuart_console_write(struct console *co, const char *s, unsigned int count)
{
	u8 *console_buff = NULL;
	
	u32 src_pos = 0;
    u32 dst_pos = 0;
	console_buff = acshell_recv_str.ptxbuff;
	
    while(src_pos < count) 
	{
        if (*((char *)s + src_pos) == '\n') 
		{
            *(console_buff + dst_pos) = '\r';
            *(console_buff + dst_pos + 1) = '\n';
            dst_pos += 2;
            src_pos++;
        }
        else 
		{
            *(console_buff + dst_pos) = *((u8 *)s + src_pos);
            src_pos++;
            dst_pos++;
        }
    }
	dialup_hsuart_send(console_buff,dst_pos);
}
int hsuart_console_setup(struct console *co, char *options)
{
     return 0;
}

static struct tty_driver *hsuart_console_device(struct console *co, int *index)
{
	struct tty_driver **p = (struct tty_driver **)co->data;

	if (!*p)
		return NULL;

	*index = co->index;
	return *p;
}

static struct console ghsuart_console = {
	.name		= "tty_hs",
	.write		= hsuart_console_write,
	.device		= hsuart_console_device,
	.setup		= hsuart_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &ghsuart_tty_driver,
};

/*****************************************************************************
* �� �� ��  : hsuart_acshell_irq
* ��������  : uart �жϷ������
* �������  : irq:�жϺ�
*             dev_id:����
* �������  : NA
* �� �� ֵ  : �жϷ���ֵ
*****************************************************************************/
static irqreturn_t hsuart_acshell_irq(int irq, void *ctx)
{
   	u32 ulInt = 0;
	u32 ulCharNum = 0;
	u32 Data = 0;
	u32 i = 0;
	u8 *recvTemp = 0;
	hsuart_dev *uart_dev = NULL;
	uart_dev = (hsuart_dev *)ctx;
	
    ulInt = readl((u32)uart_dev->vir_addr_base + UART_REGOFF_IIR);
    ulInt &= UART_FIFO_MASK;
	
    if(ulInt == UART_IIR_REV_TIMEOUT) //���ճ�ʱ�ж�
    {	
		ulCharNum = readl((u32)uart_dev->vir_addr_base + 0x84);
		
		/* ����4���ַ��Ĵ��� */
		while(ulCharNum >= 4)
		{
			Data = readl((u32)uart_dev->vir_addr_base + UART_REGOFF_RBR);
			recvTemp = (u8 *)&Data;
			memcpy((void *)&acshell_recv_str.uldata[acshell_recv_str.ulwrite], (void *)&recvTemp[i], 4);
			acshell_recv_str.ulwrite += 4;
			ulCharNum = ulCharNum - 4;
		}

		/* ʣ��С��4���ַ��Ĵ��� */
		if (ulCharNum > 0)
		{
			Data = readl((u32)uart_dev->vir_addr_base + UART_REGOFF_RBR);
			recvTemp = (u8 *)&Data;
			memcpy((void *)&acshell_recv_str.uldata[acshell_recv_str.ulwrite], (void *)&recvTemp[i], ulCharNum);
			acshell_recv_str.ulwrite += ulCharNum;
		}
/*
		while(ulCharNum)
		{
			if(ulCharNum >= 4)
			{
				Data = readl((u32)uart_dev->vir_addr_base + UART_REGOFF_RBR);			
				recvTemp = (u8 *)&Data;
                for(i=0;i<4;i++)
                {
                  	acshell_recv_str.uldata[acshell_recv_str.ulwrite] = recvTemp[i];
					acshell_recv_str.ulwrite++;
                }
                ulCharNum = ulCharNum - 4;
			}
			else
			{	
				Data = readl((u32)uart_dev->vir_addr_base + UART_REGOFF_RBR);
				recvTemp = (u8 *)&Data;
				for(i = 0; i <ulCharNum; i++)
				{		
					acshell_recv_str.uldata[acshell_recv_str.ulwrite] = recvTemp[i];
					acshell_recv_str.ulwrite++;			
				}
				break;
			}	
		}
*/
    }

	else if(ulInt == 0x4)
    {
		ulCharNum = readl((u32)uart_dev->vir_addr_base + UART_REGOFF_USR);
        while(ulCharNum & 0x8)
        {
            Data = readl((u32)uart_dev->vir_addr_base + UART_REGOFF_RBR);
            recvTemp = (u8*)&Data;
            for(i = 0;i < 4;i++)
            {
				acshell_recv_str.uldata[acshell_recv_str.ulwrite] = recvTemp[i];
				acshell_recv_str.ulwrite++;			
            }
            ulCharNum = readl((u32)uart_dev->vir_addr_base + UART_REGOFF_USR);
        }
    }
	hsuart_ops.shell_rx(acshell_recv_str.uldata, acshell_recv_str.ulwrite);
	acshell_recv_str.ulwrite = 0;
	return (irqreturn_t)IRQ_HANDLED;
}

s32 hsuart_acshell_baud(hsuart_dev *uart_dev)
{	
	u32 divisor = 0;
	u32 divisor_dll = 0;
    u32 divisor_dlh = 0;
	u32 val = 0;
	u32 u32Times = 0;
	u32 u32Discard = 0;
	u32 u32Fcr = 0;
	divisor =  uart_dev->clock/ (u32)(16 * 115200);
	divisor_dll = divisor & 0xFF;
	divisor_dlh = (divisor & 0xFF00) >> 8;

	u32Fcr = UART_DEF_RT_ONEFOUR|UART_DEF_TET_ONETWO|UART_DEF_NO_DMA_MODE|UART_TX_FIFO_RESET|UART_RX_FIFO_RESET|UART_FCR_FIFO_ENABLE;
	writel(u32Fcr, (u32)uart_dev->vir_addr_base + UART_REGOFF_FCR);	
	/* ��ȡUART ״̬�Ĵ�������UART�Ƿ���idle״̬*/
    u32Discard = readl((u32)uart_dev->vir_addr_base+ UART_REGOFF_USR);
    while((u32Discard & 0x01)&&(u32Times<1000))
    {
    	u32Discard = readl((u32)uart_dev->vir_addr_base + UART_REGOFF_USR);
        u32Times++;
    }
    if(1000 == u32Times)
    {
		hsuart_error("UART BUSY\n");
		return ERROR;
    }
	
	/* �� DLL/DHL */
	val = readl((u32)uart_dev->vir_addr_base + UART_REGOFF_LCR);
    writel(UART_LCR_DLAB, (u32)uart_dev->vir_addr_base + UART_REGOFF_LCR);

    /* ����DLH ��DLL �Ĵ��������ô���ͨѶ�Ĳ�����*/
    writel(divisor_dll, (u32)uart_dev->vir_addr_base+ UART_REGOFF_DLL);
    writel(divisor_dlh, (u32)uart_dev->vir_addr_base + UART_REGOFF_DLH);
 
    /*��ֹ DLL&DLH */
	val &= ~UART_LCR_DLAB;
    writel(val, (u32)uart_dev->vir_addr_base + UART_REGOFF_LCR);
	writel(UART_LCR_DLS_8BITS | UART_LCR_STOP_1BITS |UART_LCR_PEN_NONE, (u32)uart_dev->vir_addr_base+ UART_REGOFF_LCR);
	
	/* ���÷������ */
    writel(UART_DEF_TX_DEPTH, (u32)uart_dev->vir_addr_base +  UART_REG_OFFSET_TX_FF_DEPTH);

	/* ȥʹ�������ж� */
	writel(UART_IER_IRQ_DISABLE, (u32)uart_dev->vir_addr_base + UART_REGOFF_IER);		
	readl((u32)uart_dev->vir_addr_base + UART_REGOFF_LSR);
	readl((u32)uart_dev->vir_addr_base+ UART_REGOFF_RBR);	/* ��������ж� */
	readl((u32)uart_dev->vir_addr_base + UART_REGOFF_IIR);		/* ������Ϳ��ж� */
	readl((u32)uart_dev->vir_addr_base + UART_REGOFF_USR);		/* �����æ�ж� */
	
	/* ʹ�ܽ��պͳ�ʱ�ж� */
	(void)writel(UART_IER_RX_IRQ_ENABLE | 0x10,  (u32)uart_dev->vir_addr_base+ UART_REGOFF_IER);
	return OK;
}
/*lint -save -e438 -e550*/
s32 hsuart_acshell_init(hsuart_ctx *uart_ctx)
{
	hsuart_dev *uart_dev = NULL;
    if(NULL == uart_ctx)
	{
       hsuart_error("uart_ctx is NULL\n");
	   return ERROR;
	}
    uart_dev = &uart_ctx->dev;
	spin_lock_init(&uart_dev->lock_irq);
	
    uart_dev->vir_addr_base = ioremap(uart_dev->phy_addr_base,SIZE_4K);

	hsuart_acshell_baud(uart_dev);
	return OK;
}

s32 hsuart_ashell_console_init(void)
{
	int status = 0;
	struct device	*tty_dev;
    struct console* uart_console = NULL;

    /* alloc first tty driver for console */
	ghsuart_tty_driver = alloc_tty_driver(1);
	if (!ghsuart_tty_driver)
		return -ENOMEM;
	
	ghsuart_tty_driver->driver_name = "console_hs";
	ghsuart_tty_driver->name = "tty_hs";

	/* uses dynamically assigned dev_t values */
	ghsuart_tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
	ghsuart_tty_driver->subtype = SERIAL_TYPE_NORMAL;
	ghsuart_tty_driver->flags = TTY_DRIVER_REAL_RAW | TTY_DRIVER_DYNAMIC_DEV;
	ghsuart_tty_driver->init_termios = tty_std_termios;

	/* 9600-8-N-1 ... matches defaults expected by "usbser.sys" on
	 * MS-Windows.  Otherwise, most of these flags shouldn't affect
	 * anything unless we were to actually hook up to a serial line.
	 */
	ghsuart_tty_driver->init_termios.c_cflag = B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	ghsuart_tty_driver->init_termios.c_ispeed = 9600;
	ghsuart_tty_driver->init_termios.c_ospeed = 9600;
	ghsuart_tty_driver->num = 1;

	tty_set_operations(ghsuart_tty_driver, &ghsuart_ops);

	status = tty_register_driver(ghsuart_tty_driver);
	if (status) 
	{
		printk("cannot register, %d\n",status);
		goto console_init_fail;
	}
	tty_dev = tty_register_device(ghsuart_tty_driver, 0, NULL);

	uart_console = bsp_get_uart_console();
    if (uart_console) 
	{
          unregister_console(uart_console);
    }

    register_console(&ghsuart_console);
    console_start(&ghsuart_console);

    return 0;
console_init_fail:
    put_tty_driver(ghsuart_tty_driver);
    return ERROR;
}
/*lint +restore +e438 +e550*/

s32 hsuart_shell_init(DRV_DIALUP_HSUART_STRU acshell_nv_stru)
{
	s32 ret = 0;
	hsuart_ctx *uart_ctx = &acshell_hsuart_ctx;

	memset(&acshell_recv_str,0,sizeof(acshell_recv_str));
	acshell_recv_str.ptxbuff = (u8 *)osl_malloc(ACSHELL_TX_BUFF_SIZE);	
	if(acshell_recv_str.ptxbuff == NULL)	
	{
		hsuart_error("malloc failed\n");
		cshell_clear_bit(DIAL_HSUART_CSHELL_BIT);
		return ERROR;
	}
	memset(acshell_recv_str.ptxbuff,0,ACSHELL_TX_BUFF_SIZE);

	ret = hsuart_acshell_init(uart_ctx);	
	if(ret != OK)
	{		
		hsuart_error("hsuart acshell init error\n");
		osl_free(acshell_recv_str.ptxbuff);
		cshell_clear_bit(DIAL_HSUART_CSHELL_BIT);
		return ERROR;
	}
	
	if(acshell_nv_stru.DialupACShellCFG == UART_C_SHELL)
	{
		hsuart_error("dialup UART_C_SHELL init\n");
		hsuart_ops.shell_rx = cshell_recv_from_dial;
		acshell_recv_str.shell_flag = HSUART_TRUE;
		cshell_set_bit(DIAL_HSUART_CSHELL_BIT);		
	}		
	else if(acshell_nv_stru.DialupACShellCFG == UART_A_SHELL)
	{
		hsuart_error("dialup UART_A_SHELL init\n");
		hsuart_ops.shell_rx = hsuart_rx_tty_proc;
		ret = hsuart_ashell_console_init();
		if(ret != OK)
		{		
			hsuart_error("hsuart ashell init error\n");
			osl_free(acshell_recv_str.ptxbuff);
			return ERROR;
		}
	}
	ret = request_irq((unsigned int)uart_ctx->dev.irq, (irq_handler_t)hsuart_acshell_irq,0,"HS UART ISR", &uart_ctx->dev);
	if (ret)
	{
	    hsuart_error("request_irq is failed!\n");
		osl_free(acshell_recv_str.ptxbuff);
	    return ERROR;
	}
	return OK;
}

void hsuart_acshell_resume(void)
{
	hsuart_ctx *uart_ctx = &acshell_hsuart_ctx;
	hsuart_dev *uart_dev = NULL;

    uart_dev = &uart_ctx->dev;
	hsuart_acshell_baud(uart_dev);
}
