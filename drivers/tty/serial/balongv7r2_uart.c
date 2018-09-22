/*
 * balongv7r2_uart.c -- balong uart driver in linux
 *
 * Copyright (C) 2012 Huawei Corporation
 *
 *
 */


/*******************************************************************/
/*                                              ͷ�ļ�                                              */
/*******************************************************************/

#include <linux/module.h>
#include <linux/ioport.h>
#include <linux/console.h>
#include <linux/sysrq.h>
#include <linux/device.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/serial_core.h>
#include <linux/amba/bus.h>
#include <linux/amba/serial.h>
#include <linux/slab.h>
#include <linux/dmaengine.h>
#include <linux/dma-mapping.h>
#include <asm-generic/sizes.h>

#include <bsp_shared_ddr.h>
#include <hi_uart.h>
#include <osl_irq.h>

/*lint --e{18, 64, 102, 123, 160, 516, 522, 527, 529, 530, 550, 571, 629, 666, 681, 958, 959, 737, 730, 740,  } */
/*******************************************************************/
/*                                              �궨��                                              */
/*******************************************************************/
#define UART_NR			        4       /* Number of uart supported */
#define SERIAL_BALONG_MAJOR	    204
#define SERIAL_BALONG_MINOR	    64
#define UARTV7R2_LCRH		    0x2c	/*Offset of  Line control register. */
#define UARTV7R2_IFLS_RX4_8	    (2 << 3)
#define UARTV7R2_IFLS_TX4_8	    (2 << 0)
#define DW_ISR_PASS_LIMIT       16


/*******************************************************************/
/*                                             ��������                                          */
/*******************************************************************/
/* There is by now at least one vendor with differing details, so handle it */
struct vendor_data
{
	unsigned int		ifls;
	unsigned int		fifosize;
	unsigned int		lcrh_tx;
	unsigned int		lcrh_rx;
	bool			    oversampling;
	bool			    dma_threshold;
};


static struct vendor_data vendor_hisilicon =
{
	.ifls			= UARTV7R2_IFLS_RX4_8 | UARTV7R2_IFLS_TX4_8,
	.fifosize		= UART_FIFO_SIZE,
	.lcrh_tx		= UARTV7R2_LCRH,
	.lcrh_rx		= UARTV7R2_LCRH,
	.oversampling	= false,
	.dma_threshold	= false,
};

/*
 * We wrap our port structure around the generic uart_port.
 */
struct balongv7r2_uart_port
{
	struct uart_port	port;
	struct clk		    *clk;
	const struct vendor_data *vendor;
	unsigned int		dmacr;		    /* dma control reg */
	unsigned int		im;		        /* interrupt mask */
	unsigned int		old_status;
	unsigned int		fifosize;	    /* vendor-specific */
	unsigned int		lcrh_tx;	    /* vendor-specific */
	unsigned int		lcrh_rx;	    /* vendor-specific */
	bool			    autorts;
	char			    type[12];
};


/*******************************************************************/
/*                                             ����ʵ��                                          */
/*******************************************************************/

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_stop_tx
*
* ��������  :  ֹͣ����
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_stop_tx(struct uart_port *port)
{
    struct balongv7r2_uart_port *uap = (struct balongv7r2_uart_port *)port;

    uap->im &= ~(PTIME | UART_IER_TX_IRQ_ENABLE);
    writel(uap->im, uap->port.membase + UART_REGOFF_IER);
}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_start_tx
*
* ��������  :  ��ʼ���ʹ�������
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_start_tx(struct uart_port *port)
{
    struct balongv7r2_uart_port *uap = (struct balongv7r2_uart_port *)port;

    uap->im |= UART_IER_TX_IRQ_ENABLE;

    writel(uap->im, uap->port.membase + UART_REGOFF_IER);
}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_stop_rx
*
* ��������  :  ֹͣ���մ�������
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_stop_rx(struct uart_port *port)
{
    struct balongv7r2_uart_port *uap = (struct balongv7r2_uart_port *)port;

    uap->im &= ~(UART_IER_LS_IRQ_ENABLE | UART_IER_RX_IRQ_ENABLE);

    writel(uap->im, uap->port.membase + UART_REGOFF_IER);
}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_enable_ms
*
* ��������  :  ����modem status(�˴�Ϊ��)
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_enable_ms(struct uart_port *port)
{
    return;
}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_wait_idle
*
* ��������  :  �ȴ����ڴ������
*
* �������  :  uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/

static inline void balongv7r2_uart_wait_idle(struct uart_port *port)
{
	while(readl(port->membase + UART_REGOFF_USR) & UART_USR_UART_BUSY)
	{
		if(readl(port->membase + UART_REGOFF_LSR) & UART_LSR_DR)
		{
			readl(port->membase + UART_REGOFF_RBR);
		}
	}
}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_rx_int_proc
*
* ��������  :  ���ڽ����жϴ������
*
* �������  :  balongv7r2_uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_rx_int_proc(struct balongv7r2_uart_port *uap)
{
    struct tty_struct *tty = uap->port.state->port.tty;
    unsigned int status;
    unsigned int ch;
    unsigned int flag;
    unsigned int rsr;
    unsigned int max_count = DW_ISR_PASS_LIMIT;

    status = readl(uap->port.membase + UART_REGOFF_LSR);

    while ((status & UART_LSR_DR) && max_count--)
    {
        ch = readl(uap->port.membase + UART_REGOFF_RBR);
        flag = TTY_NORMAL;
        uap->port.icount.rx++;

        rsr = status;

        /* Handle recive error first */
        if (unlikely(rsr & UART_LSR_ERR_ANY))
        {
            if (rsr & UART_LSR_BI)
            {
                rsr &= ~(UART_LSR_FE|UART_LSR_PE);
                uap->port.icount.brk++;
                if (uart_handle_break(&uap->port))
                {
                	status = readl(uap->port.membase + UART_REGOFF_LSR);
                	continue;
                }
            }
            else if (rsr & UART_LSR_PE)
            {
                uap->port.icount.parity++;
            }
            else if (rsr & UART_LSR_FE)
            {
                uap->port.icount.frame++;
            }
            else if (rsr & UART_LSR_OE)
            {
                uap->port.icount.overrun++;
            }

            rsr &= uap->port.read_status_mask;

            if (rsr & UART_LSR_BI)
                flag = TTY_BREAK;
            else if (rsr & UART_LSR_PE)
                flag = TTY_PARITY;
            else if (rsr & UART_LSR_FE)
                flag = TTY_FRAME;
        }

        /* Handle sys char */
        if (uart_handle_sysrq_char(&uap->port, ch))
        {
            status = readl(uap->port.membase + UART_REGOFF_LSR);
            continue;
        }
#if (!defined(BSP_CONFIG_BOARD_STICK)) || (FEATURE_ON == MBB_BUILD_DEBUG)
        /* Insert char to tty flip buffer */
        uart_insert_char(&uap->port, rsr, UART_LSR_OE, ch, flag);
#endif
        status = readl(uap->port.membase + UART_REGOFF_LSR);
    }

    /* Flush tty flip buffer */
    tty_flip_buffer_push(tty);

    return;
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_tx_int_proc
*
* ��������  : �����жϴ�����
*
* �������  :  balongv7r2_uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_tx_int_proc(struct balongv7r2_uart_port *uap)
{
	struct circ_buf *xmit = &uap->port.state->xmit;
    int count = 0;
	unsigned int reg_usr;

    if (uap->port.x_char)
	{
		reg_usr = readl(uap->port.membase + UART_REGOFF_USR);
		if(reg_usr & UART_USR_FIFO_NOT_FULL)
		{
        	writel(uap->port.x_char, uap->port.membase + UART_REGOFF_THR);
        	uap->port.icount.tx++;
        	uap->port.x_char = 0;
		}
        return;
    }

    if (uart_circ_empty(xmit) || uart_tx_stopped(&uap->port)) {
        balongv7r2_uart_stop_tx(&uap->port);
        return;
    }

    count = (int)uap->port.fifosize;
    do
    {
		reg_usr = readl(uap->port.membase + UART_REGOFF_USR);
		if(reg_usr & UART_USR_FIFO_NOT_FULL)
		{
        	/* write data to xmit buffer */
        	writel(xmit->buf[xmit->tail], uap->port.membase + UART_REGOFF_THR);
        	xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
        	uap->port.icount.tx++;
		}
		else
		{
			break;
		}

        if (uart_circ_empty(xmit))
        {
            break;
        }
    } while (--count > 0);

    if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
        uart_write_wakeup(&uap->port);

    /* If buffer is empty ,stop transmit */
    if (uart_circ_empty(xmit))
        balongv7r2_uart_stop_tx(&uap->port);
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_modem_status
*
* ��������  :  ����modem status
*
* �������  :  balongv7r2_uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_modem_status(struct balongv7r2_uart_port *uap)
{
    return;
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_irq_handler
*
* ��������  :  �����ж��ܵ���Ӧ����
*
* �������  : irq :�жϺ� dev_id:�豸ID

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static irqreturn_t balongv7r2_uart_irq_handler(int irq, void *dev_id)
{
    struct balongv7r2_uart_port *uap = dev_id;
    unsigned int interrupt_id;
    int handled = 0;

    spin_lock(&uap->port.lock);

    interrupt_id = readl(uap->port.membase + UART_REGOFF_IIR);
    interrupt_id = 0x0F & interrupt_id;

    if(interrupt_id != UART_IIR_NO_INTERRUPT)
    {
        if ((UART_IIR_REV_VALID == interrupt_id) ||
            (UART_IIR_REV_TIMEOUT == interrupt_id) ||
            (UART_IIR_REV_STA == interrupt_id))
        {
            balongv7r2_uart_rx_int_proc(uap);    /* Handle irq from receive */
        }
        else if (UART_IIR_MODEM_INTERRUPT == interrupt_id)
        {
            balongv7r2_uart_modem_status(uap);
        }
        else if (UART_IIR_THR_EMPTY == interrupt_id)
        {
            balongv7r2_uart_tx_int_proc(uap);   /* Handle irq from transmit */
        }
		else /* transe busy intr*/
		{
			(void)readl(uap->port.membase + UART_REGOFF_LSR);
		}
        handled = 1;
    }

    spin_unlock(&uap->port.lock);

    return (irqreturn_t)IRQ_RETVAL(handled);
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_tx_empty
*
* ��������  :  �����Ƿ����
*
* �������  :  uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static unsigned int balongv7r2_uart_tx_empty(struct uart_port *port)
{
    struct balongv7r2_uart_port *uap = (struct balongv7r2_uart_port *)port;

    unsigned int status = readl(uap->port.membase + UART_REGOFF_LSR);

    if(status & UART_LSR_TEMT)
    {
        return TIOCSER_TEMT;
    }

    return 0;
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_get_mctrl
*
* ��������  :  ��ȡmodem���Ʒ�ʽ
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/

static unsigned int balongv7r2_uart_get_mctrl(struct uart_port *port)
{
    unsigned int result = 0;
    return result;
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_set_mctrl
*
* ��������  :  ����modem���Ʒ�ʽ
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/

static void balongv7r2_uart_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
    return ;
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_break_ctl
*
* ��������  :  ����break signals
*
* �������  :  uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_break_ctl(struct uart_port *port, int break_state)
{
    struct balongv7r2_uart_port *uap = (struct balongv7r2_uart_port *)port;
    unsigned long flags;
    unsigned int lcr_h;

    spin_lock_irqsave(&uap->port.lock, flags);


    /* Wait until transmit done */
	balongv7r2_uart_wait_idle(port);

    /* Read data in LCR */
    lcr_h = readl(uap->port.membase + UART_REGOFF_LCR);
    if (break_state)
    {
        lcr_h |= UART_LCR_BREAK;/* [false alarm]:�� */
    }
    else
    {
        lcr_h &= ~UART_LCR_BREAK;/* [false alarm]:�� */
    }

    /* Write data to break bit in LCR */
    writel(lcr_h, uap->port.membase + UART_REGOFF_LCR);

    spin_unlock_irqrestore(&uap->port.lock, flags);
}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_startup
*
* ��������  :  �������ڶ˿ڣ��ڴ򿪸��豸�ǻ���ã������жϵȹ���
*
* �������  :  uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static int balongv7r2_uart_startup(struct uart_port *port)
{

    struct balongv7r2_uart_port *uap = (struct balongv7r2_uart_port *)port;
    int retval;
	unsigned long interrupt_flg;

	/* disable FIFO and interrupt */
    writel(UART_IER_IRQ_DISABLE, uap->port.membase + UART_REGOFF_IER);
	writel(UART_FCR_FIFO_DISABLE, uap->port.membase + UART_REGOFF_FCR);

	/*
	 * Allocate the IRQ
	 */
	retval = request_irq(uap->port.irq, balongv7r2_uart_irq_handler, 0, "BalongV7R2 Uart", uap);
	if (retval)
	{
        return retval;

    }
	/* enable FIFO */
    writel(UART_FCR_DEF_SET, uap->port.membase + UART_REGOFF_FCR);

	/* clear interrupt status */
    readl(uap->port.membase + UART_REGOFF_LSR);
    readl(uap->port.membase + UART_REGOFF_IIR);
    readl(uap->port.membase + UART_REGOFF_USR);
    readl(uap->port.membase + UART_REGOFF_RBR);
	/*
     * Finally, enable interrupts
     */
    spin_lock_irqsave(&uap->port.lock, interrupt_flg);

    uap->im = (UART_IER_RX_IRQ_ENABLE);
    writel(uap->im, uap->port.membase + UART_REGOFF_IER);

    spin_unlock_irqrestore(&uap->port.lock, interrupt_flg);

	return 0;

}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_shutdown
*
* ��������  :  �رմ��ڣ��ڹرո��豸ʱ���ã��ͷ��жϵ�
*
* �������  :  uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_shutdown(struct uart_port *port)
{
    struct balongv7r2_uart_port *uap = (struct balongv7r2_uart_port *)port;
    unsigned long val;
	unsigned long interrup_flg;

    spin_lock_irqsave(&uap->port.lock, interrup_flg);

    /*
        * disable/clear all interrupts
      */
    uap->im = 0;
    writel(uap->im, uap->port.membase + UART_REGOFF_IER);
    readl( uap->port.membase + UART_REGOFF_LSR);

    spin_unlock_irqrestore(&uap->port.lock, interrup_flg);

    /*
        * Free the interrupt
      */
    free_irq(uap->port.irq, uap);

	balongv7r2_uart_wait_idle(port);
    val = readl(uap->port.membase + UART_REGOFF_LCR);
    val &= ~(UART_LCR_BREAK);/* [false alarm]:�� */
    writel(val, uap->port.membase + UART_REGOFF_LCR);

    /* disable fifo*/
    writel(UART_FCR_FIFO_DISABLE, uap->port.membase + UART_REGOFF_FCR);

}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_set_data_len
*
* ��������  :  ���ô������ݳ��ȵĲ���
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static u32 balongv7r2_uart_set_data_len(struct ktermios *termios)
{
    u32 data_len = 0;
    switch (termios->c_cflag & CSIZE)
    {
        case CS5:
            data_len = UART_LCR_DLS_5BITS;
            break;
        case CS6:
            data_len = UART_LCR_DLS_6BITS;
            break;
        case CS7:
            data_len = UART_LCR_DLS_7BITS;
            break;
        case CS8:
            data_len = UART_LCR_DLS_8BITS;
            break;
        default: // CS8
            data_len = UART_LCR_DLS_8BITS;
            break;
    }
    return data_len;
}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_set_termios
*
* ��������  :  ���ô��ڲ���
*
* �������  :  uart_port

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_set_termios(struct uart_port *port,struct ktermios *termios, struct ktermios *old)
{
    unsigned int lcr_h, old_cr;
    unsigned long flags;
    unsigned int baud, quot;

    /*
        * Ask the core to calculate the divisor for us.
      */
    baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk/16);
    quot = port->uartclk / (16 * baud);/* [false alarm]:�� */

    lcr_h = balongv7r2_uart_set_data_len(termios);

    if (termios->c_cflag & CSTOPB)
    {
        lcr_h |= UART_LCR_STOP_2BITS;
    }

    if (termios->c_cflag & PARENB)
    {
        lcr_h |= UART_LCR_PEN;

    }

    if (!(termios->c_cflag & PARODD))
    {
        lcr_h |= UART_LCR_EPS;/* [false alarm]:�� */
    }
    spin_lock_irqsave(&port->lock, flags);

    /*
      * Update the per-port timeout.
      */
    uart_update_timeout(port, termios->c_cflag, baud);

    port->read_status_mask = UART_LSR_OE;

    if (termios->c_iflag & INPCK)
    {
        port->read_status_mask |= UART_LSR_FE | UART_LSR_PE;
    }
    if (termios->c_iflag & (BRKINT | PARMRK))
    {
        port->read_status_mask |= UART_LSR_BI;
    }

    /*
      * Characters to ignore
      */
    port->ignore_status_mask = 0;
    if (termios->c_iflag & IGNPAR)
    {
        port->ignore_status_mask |= UART_LSR_FE | UART_LSR_PE;
    }
    if (termios->c_iflag & IGNBRK)
    {
        port->ignore_status_mask |= UART_LSR_BI;
      /*
         * If we're ignoring parity and break indicators,
         * ignore overruns too (for real raw support).
         */
        if (termios->c_iflag & IGNPAR)
        {
            port->ignore_status_mask |= UART_LSR_OE;
        }
    }

    /*
     * Ignore all characters if CREAD is not set.
     */
    #define UART_DUMMY_RSR_RX	256
    if ((termios->c_cflag & CREAD) == 0)
    {
        port->ignore_status_mask |= (UART_DUMMY_RSR_RX);
    }

    if (UART_ENABLE_MS(port, termios->c_cflag))
    {
        balongv7r2_uart_enable_ms(port);
    }

	balongv7r2_uart_wait_idle(port);

	/* Enable DLL and DLH */
    old_cr = readl(port->membase + UART_REGOFF_LCR);
    old_cr |= UART_LCR_DLAB;
    writel(old_cr,port->membase + UART_REGOFF_LCR);

    /* Set baud rate */
    writel(((quot&0xFF00)>>8), port->membase + UART_REGOFF_DLH);
    writel((quot & 0xFF), port->membase + UART_REGOFF_DLL);

    old_cr &= ~UART_LCR_DLAB;/* [false alarm]:�� */
    writel(old_cr,port->membase + UART_REGOFF_LCR);

    writel(lcr_h, port->membase + UART_REGOFF_LCR);

    spin_unlock_irqrestore(&port->lock, flags);
}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_type
*
* ��������  :  ��ȡ�����豸
*
* �������  :  uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static const char * balongv7r2_uart_type(struct uart_port *port)
{
	struct balongv7r2_uart_port *uap = (struct balongv7r2_uart_port *)port;

	return uap->port.type == PORT_AMBA ? uap->type : NULL;
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_port_release_port
*
* ��������  :  �ͷŴ���ռ�õ��ڴ�ռ�
*
* �������  :  uart_port:��ǰ�˿�

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_port_release_port(struct uart_port *port)
{
	release_mem_region(port->mapbase, SZ_4K);
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_port_request_port
*
* ��������  : Ϊ��������ռ�(4K)
*
* �������  :  AMBA_UART_CHAN  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static int balongv7r2_uart_port_request_port(struct uart_port *port)
{
	return request_mem_region(port->mapbase, SZ_4K, "uart-balong") != NULL ? 0 : -EBUSY;
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_port_config_port
*
* ��������  :  ��������,���ö˿����ͣ�����ռ�
*
* �������  :  AMBA_UART_CHAN  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_port_config_port(struct uart_port *port, int flags)
{
	if (flags & UART_CONFIG_TYPE)
    {
		port->type = PORT_AMBA;
		balongv7r2_uart_port_request_port(port);
	}
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_init
*
* ��������  :  ��ʼ������
*
* �������  :  AMBA_UART_CHAN  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static int balongv7r2_uart_port_verify_port(struct uart_port *port, struct serial_struct *ser)
{
    int ret = 0;
    if (ser->type != PORT_UNKNOWN && ser->type != PORT_AMBA)
        ret = -EINVAL;
    if (ser->irq < 0 || ser->irq >= NR_IRQS)
        ret = -EINVAL;
    if (ser->baud_base < 9600)
        ret = -EINVAL;
    return ret;
}

static struct uart_ops amba_balongv7r2_uart_pops = {
	.tx_empty	    = balongv7r2_uart_tx_empty,     /* transmit busy?          */
	.set_mctrl	    = balongv7r2_uart_set_mctrl,    /* set modem control    */
	.get_mctrl	    = balongv7r2_uart_get_mctrl,    /* get modem control    */
	.stop_tx	    = balongv7r2_uart_stop_tx,      /* stop transmit           */
	.start_tx	    = balongv7r2_uart_start_tx,     /* start transmit           */
	.stop_rx	    = balongv7r2_uart_stop_rx,      /* stop  receive            */
	.enable_ms	    = balongv7r2_uart_enable_ms,    /* enable modem status signals            */
	.break_ctl	    = balongv7r2_uart_break_ctl,    /* enable break signals            */
	.startup	    = balongv7r2_uart_startup,      /* start uart receive/transmit    */
	.shutdown	    = balongv7r2_uart_shutdown,     /* shut down uart           */
	.set_termios	= balongv7r2_uart_set_termios,  /* set termios            */
	.type		    = balongv7r2_uart_type,         /* get uart type            */
	.release_port	= balongv7r2_uart_port_release_port,
	.request_port	= balongv7r2_uart_port_request_port,
	.config_port	= balongv7r2_uart_port_config_port,
	.verify_port	= balongv7r2_uart_port_verify_port,
};

static struct balongv7r2_uart_port *amba_ports[UART_NR];

struct uart_port* bsp_get_amba_ports(void)
{
        return (struct uart_port*)(&amba_ports[0]);
}


#ifdef CONFIG_SERIAL_BALONGV7R2_UART_CONSOLE
/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_console_putchar
*
* ��������  :  ����̨���
*
* �������  :  uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_console_putchar(struct uart_port *port, int ch)
{
    unsigned int status;

    /* Wait until send empty */
    do
    {
        status = readl(port->membase + UART_REGOFF_LSR);
    } while ((status & UART_LSR_THRE) != UART_LSR_THRE);

    writel(ch, port->membase + UART_REGOFF_THR);
}
/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_console_write
*
* ��������  :  ���ڿ���̨д
*
* �������  :  AMBA_UART_CHAN  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void balongv7r2_uart_console_write(struct console *co, const char *s, unsigned int count)
{
	struct balongv7r2_uart_port *uap = amba_ports[co->index];

    /* Write a console messge to serial port thougth function balongv7r2_uart_console_putchar */
	uart_console_write(&uap->port, s, count, balongv7r2_uart_console_putchar);
}
/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_console_get_options
*
* ��������  :  ��ȡ��ǰ����
*
* �������  :  balongv7r2_uart_port  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void __init balongv7r2_uart_console_get_options(struct balongv7r2_uart_port *uap, int *baud,int *parity, int *bits)
{
    unsigned int lcr_h, brd;
    unsigned long flags;
    unsigned char lbrd,hbrd;

    lcr_h = readl(uap->port.membase + UART_REGOFF_LCR);

    *parity = 'n';
    if (lcr_h & UART_LCR_PEN) {
        if (lcr_h & UART_LCR_EPS)
            *parity = 'e';
        else
            *parity = 'o';
    }

    if ((lcr_h & UART_LCR_DLS_MASK) == UART_LCR_DLS_5BITS)
        *bits = 5;
    else if((lcr_h & UART_LCR_DLS_MASK) == UART_LCR_DLS_6BITS)
        *bits = 6;
    else if((lcr_h & UART_LCR_DLS_MASK) == UART_LCR_DLS_7BITS)
        *bits = 7;
    else
        *bits = 8;


    spin_lock_irqsave(&uap->port.lock, flags);

    lbrd = readl(uap->port.membase + UART_REGOFF_DLL);
    hbrd = readl(uap->port.membase + UART_REGOFF_DLH);

    spin_unlock_irqrestore(&uap->port.lock, flags);

    brd = (hbrd << 8) + lbrd;

    *baud = uap->port.uartclk / (16 * brd);
}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_console_setup
*
* ��������  :  ����CONSOLE�����������ʵ���Ϣ
*
* �������  :  AMBA_UART_CHAN  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static int __init balongv7r2_uart_console_setup(struct console *co, char *options)
{
	struct balongv7r2_uart_port *uap;
	int baud = 38400;
	int bits = 8;
	int parity = 'n';
	int flow = 'n';

	/*
	 * Check whether an invalid uart number has been specified, and
	 * if so, search for the first available port that does have
	 * console support.
	 */
	if (co->index >= UART_NR)
		co->index = 0;
	uap = amba_ports[co->index];
	if (!uap)
		return -ENODEV;

	uap->port.uartclk = clk_get_rate(uap->clk);

	if (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	else
		balongv7r2_uart_console_get_options(uap, &baud, &parity, &bits);

	return uart_set_options(&uap->port, co, baud, parity, bits, flow);
}

static struct uart_driver amba_reg;
static struct console amba_console = {
	.name		= "ttyAMA",
	.write		= balongv7r2_uart_console_write,
	.device		= uart_console_device,
	.setup		= balongv7r2_uart_console_setup,
	.flags		= CON_PRINTBUFFER,
	.index		= -1,
	.data		= &amba_reg,
};

#define AMBA_CONSOLE	(&amba_console)
#else
#define AMBA_CONSOLE	NULL
#endif  /* End of  CONFIG_SERIAL_BALONGV7R2_UART_CONSOLE */

static struct uart_driver amba_reg = {
	.owner			= THIS_MODULE,
	.driver_name	= "ttyAMA",
	.dev_name		= "ttyAMA",
	.major			= SERIAL_BALONG_MAJOR,
	.minor			= SERIAL_BALONG_MINOR,
	.nr			    = UART_NR,
	.cons			= AMBA_CONSOLE,
};

/*****************************************************************************
* �� �� ��     :  bsp_get_uart_console
*
* ��������  :  ��ȡconsole
*
* �������  :  void

* �������  :  ��ǰconsole
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
struct console* bsp_get_uart_console(void)
{
	struct console* uart_console = amba_reg.cons;
	return uart_console;
}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_probe
*
* ��������  :  ��ʼ������
*
* �������  :  AMBA_UART_CHAN  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static int balongv7r2_uart_probe(struct amba_device *dev, const struct amba_id *id)
{
	struct balongv7r2_uart_port *uap;
	struct vendor_data *vendor = id->data;
	void __iomem *base;
	int i, ret;

	for (i = 0; i < (int)ARRAY_SIZE(amba_ports); i++)
		if (amba_ports[i] == NULL)
			break;

	if (i == ARRAY_SIZE(amba_ports))
    {
		ret = -EBUSY;
		goto out;
	}

	uap = kzalloc(sizeof(struct balongv7r2_uart_port), GFP_KERNEL);
	if (uap == NULL)
    {
		ret = -ENOMEM;
		goto out;
	}

	base = ioremap(dev->res.start, resource_size(&dev->res));
	if (!base)
    {
		ret = -ENOMEM;
		goto free;
	}

	uap->clk = clk_get(&dev->dev, "uart0_clk");
	if (IS_ERR(uap->clk))
    {
		ret = PTR_ERR(uap->clk);
		goto unmap;
	}

	uap->vendor     = vendor;
	uap->lcrh_rx    = vendor->lcrh_rx;
	uap->lcrh_tx    = vendor->lcrh_tx;
	uap->fifosize   = vendor->fifosize;
	uap->port.dev   = &dev->dev;
	uap->port.mapbase   = dev->res.start;
	uap->port.membase   = base;
	uap->port.iotype    = UPIO_MEM;
	uap->port.irq       = dev->irq[0];
	uap->port.fifosize  = uap->fifosize;
	uap->port.ops   = &amba_balongv7r2_uart_pops;
	uap->port.flags = UPF_BOOT_AUTOCONF;
	uap->port.line  = (unsigned int)i;

	snprintf(uap->type, sizeof(uap->type), "Balong rev%u", amba_rev(dev));

	amba_ports[i] = uap;

	amba_set_drvdata(dev, uap);

    /* Add one port ,it will register console if we have already config console */
	ret = uart_add_one_port(&amba_reg, &uap->port);
	if (ret)
    {
		amba_set_drvdata(dev, NULL);
		amba_ports[i] = NULL;
		clk_put(uap->clk);
 unmap:
		iounmap(base);
 free:
		kfree(uap);
    }
 out:
	return ret;
}


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_remove
*
* ��������  :  �Ƴ�һ���˿ڣ�����ȥע��ʱ����
*
* �������  :  AMBA_UART_CHAN  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static int balongv7r2_uart_remove(struct amba_device *dev)
{
	struct balongv7r2_uart_port *uap = amba_get_drvdata(dev);
	int i;

	amba_set_drvdata(dev, NULL);

    /* Remove the port */
	uart_remove_one_port(&amba_reg, &uap->port);

	for (i = 0; i < (int)ARRAY_SIZE(amba_ports); i++)
    {
		if (amba_ports[i] == uap)
        {
			amba_ports[i] = NULL;
        }
    }

	iounmap(uap->port.membase);
	clk_put(uap->clk);
	kfree(uap);
	return 0;
}

//#ifdef CONFIG_PM
/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_suspend
*
* ��������  :  ���ڹ���
*
* �������  :  amba_device

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static int balongv7r2_uart_suspend(struct amba_device *dev, pm_message_t state)
{
	struct balongv7r2_uart_port *uap = amba_get_drvdata(dev);

	if (!uap)
		return -EINVAL;

	return uart_suspend_port(&amba_reg, &uap->port);
}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_resume
*
* ��������  :  ���ڻָ�
*
* �������  :  AMBA_UART_CHAN  :��Ӧͨ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static int balongv7r2_uart_resume(struct amba_device *dev)
{
	struct balongv7r2_uart_port *uap = amba_get_drvdata(dev);

	if (!uap)
		return -EINVAL;

	return uart_resume_port(&amba_reg, &uap->port);
}
//#endif

static struct amba_id balongv7r2_uart_ids[] = {
	{
		.id	    = UART_BALONG_ID,
		.mask	= UART_BALONG_ID_MASK,
		.data	= &vendor_hisilicon,
	},
	{ 0, 0 },
};

MODULE_DEVICE_TABLE(amba, balongv7r2_uart_ids);

static struct amba_driver balongv7r2_uart_driver = {
	.drv = {
		.name	= "uart-BlongV7R2",
	},
	.id_table	= balongv7r2_uart_ids,
	.probe		= balongv7r2_uart_probe,
	.remove		= balongv7r2_uart_remove,
//#ifdef CONFIG_PM
	.suspend	= balongv7r2_uart_suspend,
	.resume		= balongv7r2_uart_resume,
//#endif
};


/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_init
*
* ��������  :  ��ʼ�����ڣ���������ע��
*
* �������  :  ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static int __init balongv7r2_uart_init(void)
{

	int ret = 0;

	//use at uart, so return directly
  	if(AT_UART_USE_FLAG == (*(u32 *)SHM_MEM_AT_FLAG_ADDR))
		return 0;

	printk(KERN_INFO "Serial: BalongV7R2 UART driver\n");

	ret = uart_register_driver(&amba_reg);
	if (ret == 0) {
		ret = amba_driver_register(&balongv7r2_uart_driver);
		if (ret)
			uart_unregister_driver(&amba_reg);
	}

	return ret;

}

/*****************************************************************************
* �� �� ��     :  balongv7r2_uart_exit
*
* ��������  :  �����˳�
*
* �������  :  ��

* �������  :  ��
*
* �� �� ֵ     :  ��
*
* �޸ļ�¼  :
*****************************************************************************/
static void __exit balongv7r2_uart_exit(void)
{
	amba_driver_unregister(&balongv7r2_uart_driver);
	uart_unregister_driver(&amba_reg);
}

arch_initcall(balongv7r2_uart_init);
/*lint -save -e19 */
module_exit(balongv7r2_uart_exit);
/*lint -restore */

MODULE_AUTHOR("ARM Ltd/Deep Blue Solutions Ltd");
MODULE_DESCRIPTION("ARM AMBA serial port driver");
MODULE_LICENSE("GPL");
