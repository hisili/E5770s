/*
 * u_cdev.c - utilities for USB gadget "serial port"/TTY support
 *
 */


/* #define VERBOSE_DEBUG */

#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/slab.h>
#include <linux/export.h>
#include <linux/uaccess.h>
#include <bsp_usb.h>
#include <linux/uaccess.h>

#include "u_serial.h"
#include "f_acm.h"
#include "drv_acm.h"
#include "drv_udi.h"
#include "usb_debug.h"
#include "u_cdev.h"
#include "usb_vendor.h"
#include "drv_usb.h"
#include "usb_nv_get.h"

extern struct class *tty_class;

/* cdev driver */
struct u_cdev_driver {
	struct kref kref;           /* Reference management */
	struct cdev cdev;
    dev_t dev_no;
    struct module *owner;
	USB_PCHAR driver_name;
	USB_PCHAR name;
	USB_INT	name_base;              /* offset of printed name */
	USB_INT	major;                  /* major device number */
	USB_INT	minor_start;            /* start of minor device number */
	USB_INT	num;                    /* number of devices allocated */

    struct workqueue_struct *acm_work_queue;

};

/*
 * The port structure holds info for each port, one for each minor number
 * (and thus for each /dev/ node).
 */
struct gs_acm_cdev_port {
	spinlock_t port_lock;               /* guard port_* access */

	struct gserial *port_usb;

	USB_UINT open_count;
	bool openclose;	                    /* open/close in progress */
    bool is_do_copy;
    bool is_dma_tx;
	USB_UINT8 port_num;
	wait_queue_head_t close_wait;       /* wait for last close */
    ACM_EVENT_CB_T event_notify_cb;
    USB_UINT16 line_state_on;
    USB_UINT16 line_state_change;
    USB_INT is_suspend;
    USB_INT sr_change;                      /* suspend/resume state change */
    USB_PCHAR in_name;
    USB_PCHAR out_name;

    USB_CHAR read_domain[4];
	struct list_head read_pool;         /* free read req list */
    struct list_head read_done_queue;        /* done read req list */
    struct list_head read_using_queue;  /* req in using list */
    struct list_head read_queue_in_usb;
	USB_INT read_started;
	USB_INT read_allocated;
    USB_INT read_req_enqueued;
    USB_INT read_completed;
    USB_UINT read_req_num;
    USB_UINT read_buf_size;
    USB_UINT reading_pos;
    struct usb_request	*reading_req;
    USB_INT read_blocked;
    wait_queue_head_t read_wait;
    struct mutex read_lock;
    ACM_READ_DONE_CB_T read_done_cb;

    USB_CHAR write_domain[4];
	struct list_head write_pool;        /* free write req list */
    struct list_head write_queue;       /* done write req list */
    USB_UINT write_req_num;
	USB_INT write_started;
	USB_INT write_allocated;
    USB_INT write_blocked;
    USB_INT write_block_status;
    USB_INT write_completed;
    USB_INT write_no_req;
    struct mutex write_lock;
    wait_queue_head_t write_wait;
    ACM_WRITE_DONE_CB_T write_done_cb;
    ACM_FREE_CB_T write_done_free_cb;

	struct delayed_work	rw_work;
	struct usb_cdc_line_coding port_line_coding;	/* 8-N-1 etc */
    USB_UINT is_realloc;
    wait_queue_head_t realloc_wait;

    USB_CHAR debug_tx_domain[4];
    USB_UINT stat_write_async_call;
    USB_UINT stat_write_param_err;
    USB_UINT stat_sync_tx_submit;
    USB_UINT stat_sync_tx_done;
    USB_UINT stat_sync_tx_fail;
    USB_UINT stat_sync_tx_wait_fail;
    USB_UINT stat_tx_submit;
    USB_UINT stat_tx_submit_fail;
    USB_UINT stat_tx_submit_bytes;
    USB_UINT stat_tx_done;
    USB_UINT stat_tx_done_fail;
    USB_UINT stat_tx_done_bytes;
    USB_UINT stat_tx_done_schdule;
    USB_UINT stat_tx_done_disconnect;
    USB_UINT stat_tx_wakeup_block;
    USB_UINT stat_tx_callback;
    USB_UINT stat_tx_no_req;
    USB_UINT stat_tx_suspend;
    USB_UINT stat_tx_copy_fail;
    USB_UINT stat_tx_alloc_fail;
    USB_UINT stat_tx_disconnect;

    USB_CHAR debug_rx_domain[4];
    USB_UINT stat_read_call;
    USB_UINT stat_get_buf_call;
    USB_UINT stat_ret_buf_call;
    USB_UINT stat_read_param_err;
    USB_UINT stat_sync_rx_submit;
    USB_UINT stat_sync_rx_done;
    USB_UINT stat_sync_rx_done_fail;
    USB_UINT stat_sync_rx_done_bytes;
    USB_UINT stat_sync_rx_copy_fail;
    USB_UINT stat_sync_rx_disconnect;
    USB_UINT stat_sync_rx_wait_fail;
    USB_UINT stat_rx_submit;
    USB_UINT stat_rx_submit_fail;
    USB_UINT stat_rx_disconnect;
    USB_UINT stat_rx_no_req;
    USB_UINT stat_rx_done;
    USB_UINT stat_rx_done_fail;
    USB_UINT stat_rx_done_bytes;
    USB_UINT stat_rx_done_disconnect;
    USB_UINT stat_rx_done_schdule;
    USB_UINT stat_rx_wakeup_block;
    USB_UINT stat_discon_wakeup_block;
    USB_UINT stat_rx_wakeup_realloc;
    USB_UINT stat_rx_callback;
    USB_UINT stat_rx_cb_not_start;
    USB_UINT stat_rx_dequeue;

    USB_CHAR debug_port_domain[4];
    USB_UINT stat_port_is_connect;
    USB_UINT stat_port_connect;
    USB_UINT stat_port_disconnect;
    USB_UINT stat_enable_in_fail;
    USB_UINT stat_enable_out_fail;
    USB_UINT stat_notify_sched;
    USB_UINT stat_notify_on_cnt;
    USB_UINT stat_notify_off_cnt;

    USB_UINT stat_rx_blocked;
    USB_UINT stat_tx_blocked;

};

struct gs_acm_cdev_rw_priv {
    struct list_head list;
    bool is_sync;
    bool is_copy;
    USB_INT copy_pos;
    struct usb_request *req;
    struct kiocb *iocb;
};


static acm_ctx_t* acm_ctx =NULL;

static struct acm_cdev_port_manager {
    char name_domain[4];
	struct mutex	open_close_lock;			/* protect open/close */
	struct gs_acm_cdev_port	*port;
    struct device	*cdev;
    ACM_EVENT_CB_T event_cb;                    /* when usb is remove */
} gs_acm_cdev_ports[ACM_CDEV_COUNT];
static struct notifier_block gs_acm_nb;
static struct notifier_block *gs_acm_nb_ptr = NULL;

static USB_UINT	gs_acm_cdev_n_ports;
static USB_UINT gs_stat_drv_invalid;
static USB_UINT gs_stat_port_num_err;
static USB_UINT gs_pc_voice_mode = 0;

static struct gs_acm_evt_manage gs_acm_write_evt_manage;
static struct gs_acm_evt_manage gs_acm_read_evt_manage;
static struct gs_acm_evt_manage gs_acm_sig_stat_evt_manage;


static struct u_cdev_driver *gs_cdev_driver;

static USB_VOID gs_acm_cdev_free_request(struct usb_ep *ep, struct usb_request	*req);
static struct usb_request* gs_acm_cdev_alloc_request(struct usb_ep *ep, USB_UINT buf_size);
static USB_VOID gs_acm_cdev_free_requests(struct usb_ep *ep, struct list_head *head,\
							 USB_INT *allocated);
static USB_VOID gs_acm_cdev_write_complete(struct usb_ep *ep, struct usb_request *req);
static USB_VOID gs_acm_cdev_read_complete(struct usb_ep *ep, struct usb_request *req);

/*-------------------------------------------------------------------------*/
static USB_UINT gs_acm_cdev_get_tx_buf_num(USB_UINT index)
{
    
    switch (acm_ctx->cdev_name_type_var[index].type) {
    /* AT need more req buffers */
    case USB_IF_PROTOCOL_PCUI:
        return ACM_CDEV_AT_WT_REQ_NUM;
    default:
        break;
    }
    return ACM_CDEV_DFT_WT_REQ_NUM;
}

/*****************************************************************************
��������   gs_acm_cdev_is_port_block
��������:  ��acm_3g_diag�ں���������ȫ�˿�û��ʹ���ҹر���������ʱ����ֹacm_3g_diag��
�շ�����
��������� struct gs_acm_cdev_port *port �˿���Ϣ
����ֵ��   1��ʾ��ֹacm_3g_diag���շ����� 0��ʾ�ſ�acm_3g_diag���շ�����
*****************************************************************************/
static USB_INT gs_acm_cdev_is_port_block(struct gs_acm_cdev_port *port)
{
#if (FEATURE_ON == MBB_PCVOICE)
    mbb_usb_nv_info_st *nv_ctx = usb_nv_get_ctx();
    if (NULL == port)
    {
        return 0;
    }

    if (ACM_CDEV_COUNT > port->port_num)
    {
        if ((0 == gs_pc_voice_mode)
            && (0 == strcmp("acm_3g_diag", acm_ctx->cdev_name_type_var[port->port_num].name))
            && (0 == nv_ctx->usb_security_flag.om_enable))
        {
            return 1;
        }
    }
#endif
    return 0;
}

/*****************************************************************************
��������   BSP_USB_SetSwitchPcVoice
��������:  �ṩ���ϲ��Ƿ����������ܵĽӿ�
��������� 1��ʾ������������ 0��ʾ�ر���������
�������:  ��
����ֵ��   ��
*****************************************************************************/
void BSP_USB_SetSwitchPcVoice(unsigned mode)
{
    DBG_T(MBB_ACM, "Switch PC Voice to mode %u\n", mode);
    gs_pc_voice_mode = mode;
}

/*
 * gs_acm_cdev_start_tx
 *
 * This function finds available write requests, calls
 * usb_ep_queue to send the data.
 *
 */
static USB_INT gs_acm_cdev_start_tx(struct gs_acm_cdev_port *port,
                                USB_PCHAR buf, USB_UINT len, bool is_sync)
{
	struct list_head *pool = &port->write_pool;
	USB_INT status = 0;
    struct usb_request *req;
	bool is_do_copy = port->is_do_copy;
    struct gs_acm_cdev_rw_priv *write_priv;
    USB_ULONG flags;

    spin_lock_irqsave(&port->port_lock, flags);

    if (unlikely(list_empty(pool))) {
        spin_unlock_irqrestore(&port->port_lock, flags);

        DBG_I(MBB_ACM, "%s: tx req list empty, no_req flag=%d\n", __FUNCTION__, port->write_no_req);
        
        if (0 == port->write_no_req)
        {
            msleep(USB_NUM_100);        
            spin_lock_irqsave(&port->port_lock, flags);
            if (unlikely(list_empty(pool)))
            {
                spin_unlock_irqrestore(&port->port_lock, flags);
                DBG_I(MBB_ACM, "%s: still no req after sleep\n", __FUNCTION__);
                port->write_no_req = 1;
                port->stat_tx_no_req++;
                return -EAGAIN;
            }
        }
        else
        {
            port->stat_tx_no_req++;
            return -EAGAIN;            
        }
    }
    port->write_no_req = 0;

    if (port->is_suspend) {
        spin_unlock_irqrestore(&port->port_lock, flags);
        port->stat_tx_suspend++;
        return -ESHUTDOWN;
    }

    /* get a write req from the write pool */
    req = list_entry(pool->next, struct usb_request, list);
    list_del_init(&req->list);
    port->write_started++;
    spin_unlock_irqrestore(&port->port_lock, flags);

    /* check whether copy the data */
    if (is_do_copy) {
        /* alloc a new buffer first time or the room is not enough */
        if (0 == req->length || req->length < len) {
            if (req->buf){
                kfree(req->buf);
                req->buf = NULL;
                req->dma = (dma_addr_t)NULL;
                req->length = 0;
            }
            req->buf = kmalloc(len, GFP_KERNEL);
            if (NULL == req->buf) {
                port->stat_tx_alloc_fail++;
                return -ENOMEM;
            }
        }
        /* we don't need to free req->buf, if fail */
        if (copy_from_user (req->buf, buf, len)) {
            port->stat_tx_copy_fail++;
    		return -ENOMEM;
    	}
    }
    else {
        req->buf = buf;
    }

    req->length = len;
    write_priv = (struct gs_acm_cdev_rw_priv *)req->context;
    write_priv->is_sync = is_sync;
    write_priv->is_copy = is_do_copy;

    spin_lock_irqsave(&port->port_lock, flags);
    if (!port->port_usb) {
        status = -ENODEV;
        port->stat_tx_disconnect++;
        goto tx_fail_restore;
    }
    if (is_sync) {
        /* wait the write req complete */
        port->write_blocked = 1;
    }

    if (len%port->port_usb->in->maxpacket == 0)
        req->zero = 1;

    spin_unlock_irqrestore(&port->port_lock, flags);

	status = usb_ep_queue(port->port_usb->in, req, GFP_ATOMIC);
    if (status) {
		port->stat_tx_submit_fail++;
		goto tx_fail_restore;
	}
    port->stat_tx_submit_bytes += len;
    port->stat_tx_submit++;

    return 0;

tx_fail_restore:
	list_add_tail(&req->list, pool);
    port->write_started--;
    port->write_blocked = 0;
    spin_unlock_irqrestore(&port->port_lock, flags);
	return status;
}

/*
 * Context: caller owns port_lock, and port_usb is set
 */
static USB_INT gs_acm_cdev_start_rx(struct gs_acm_cdev_port *port)
{
	struct list_head	*pool = &port->read_pool;
	struct usb_ep		*out = NULL;
    struct usb_request	*req;
    struct gs_acm_cdev_rw_priv *rw_priv;

	/* abort immediately after disconnect */
	if (!port->port_usb) {
        port->stat_rx_disconnect++;
		goto start_rx_ret;
    }

    out = port->port_usb->out;
    
start_rx_beg:
	while (!list_empty(pool)) {
		int status;

        /* revise the pool length to smaller */
		if (port->read_started >= port->read_req_num) {
                
            DBG_I(MBB_ACM,"try to shrink the read buff num to %d at port %d\n",
                    port->read_req_num,port->port_num);
            gs_acm_cdev_free_requests(out, pool, &port->read_allocated);
			break;
		}

		req = list_entry(pool->next, struct usb_request, list);
		list_del_init(&req->list);
        port->read_started++;

        if (req->length < port->read_buf_size) {
            gs_acm_cdev_free_request(out, req);
            req = gs_acm_cdev_alloc_request(out, port->read_buf_size);
            if (!req) {
                goto start_rx_ret;
            }
            req->complete = gs_acm_cdev_read_complete;
        }

		/* drop lock while we call out; the controller driver
		 * may need to call us back (e.g. for disconnect)
		 */
		spin_unlock(&port->port_lock);
		status = usb_ep_queue(out, req, GFP_ATOMIC);
		spin_lock(&port->port_lock);

		if (status) {
			list_add(&req->list, pool);
            port->read_started--;
            port->stat_rx_submit_fail++;
			goto start_rx_ret;
		}

        rw_priv = (struct gs_acm_cdev_rw_priv *)req->context;
        list_add_tail(&rw_priv->list, &port->read_queue_in_usb);
        port->read_req_enqueued++;
        port->stat_rx_submit++;

		/* abort immediately after disconnect */
		if (!port->port_usb) {
            port->stat_rx_disconnect++;
			goto start_rx_ret;
        }
	}

    /* if there are no read req in usb core,
     * get the read done req and submit to usb core
     */
    if (port->port_usb && 0 == port->read_req_enqueued) {
        struct list_head *queue = &port->read_done_queue;

        if (!list_empty(queue)) {
            req = list_entry(queue->prev, struct usb_request, list);
            list_move(&req->list, pool);
            port->read_started--;

            /* go to beginning of the function,
             * re-submit the read req
             */
            port->stat_rx_no_req++;
            goto start_rx_beg;
        }
    }

start_rx_ret:
	return port->read_started;
}

/*
 * Context: caller owns port_lock, and port_usb is set
 */
static USB_VOID gs_acm_cdev_stop_rx(struct gs_acm_cdev_port *port)
{
    struct list_head* cur = NULL;
    struct list_head* next = NULL;
    struct gs_acm_cdev_rw_priv *rw_priv;
    struct usb_ep *out = port->port_usb->out;

    list_for_each_safe(cur, next, &port->read_queue_in_usb) {
        rw_priv = list_entry(cur, struct gs_acm_cdev_rw_priv, list);
        port->stat_rx_dequeue++;
        spin_unlock(&port->port_lock);
        usb_ep_dequeue(out, rw_priv->req);
        spin_lock(&port->port_lock);
    }
}

static USB_INT gs_acm_cdev_get_read_buf(struct gs_acm_cdev_port *port,
                                    ACM_WR_ASYNC_INFO *read_info)
{
    struct list_head *queue = &port->read_done_queue;
    struct usb_request	*req = NULL;
    USB_INT status;
    USB_ULONG flags;

    mutex_lock(&port->read_lock);
    spin_lock_irqsave(&port->port_lock, flags);
    if (!list_empty(queue)) {
        req = list_first_entry(queue, struct usb_request, list);
        list_move_tail(&req->list, &port->read_using_queue);
    }
    spin_unlock_irqrestore(&port->port_lock, flags);

    if (NULL == req) {
        read_info->pBuffer = NULL;
        read_info->u32Size = 0;
        status = -EAGAIN;
    }
    else {
        read_info->pBuffer = (char*)req->buf;
        read_info->u32Size = req->actual;
        status = 0;
    }
    mutex_unlock(&port->read_lock);
    return status;
}

static USB_INT gs_acm_cdev_ret_read_buf(struct gs_acm_cdev_port *port,
                                    ACM_WR_ASYNC_INFO *read_info)
{
    struct usb_request* cur_req = NULL;
    struct usb_request* next_req = NULL;
    USB_ULONG flags;

    spin_lock_irqsave(&port->port_lock, flags);
    list_for_each_entry_safe(cur_req, next_req, &port->read_using_queue, list) {
        if ((unsigned)cur_req->buf == (unsigned)read_info->pBuffer) {
            list_move(&cur_req->list, &port->read_pool);
            port->read_started--;
            spin_unlock_irqrestore(&port->port_lock, flags);

            return 0;
        }
    }
    spin_unlock_irqrestore(&port->port_lock, flags);

    return -EFAULT;
}

static USB_VOID gs_acm_cdev_notify_cb(struct gs_acm_cdev_port *port)
{
    ACM_EVENT_CB_T event_cb = NULL;
    USB_UINT16 line_state = 0;
    USB_ULONG flags;

    spin_lock_irqsave(&port->port_lock, flags);
    if (port->line_state_change) {
        event_cb = port->event_notify_cb;
        line_state = port->line_state_on;
        port->line_state_change = 0;
    }
    if (port->sr_change) {
        event_cb = port->event_notify_cb;
        if (port->is_suspend)
            line_state = ACM_EVT_DEV_SUSPEND;
        else
            line_state = ACM_EVT_DEV_READY;
        port->sr_change = 0;
    }
    spin_unlock_irqrestore(&port->port_lock, flags);

    if (event_cb) {
        if (line_state) {
            port->stat_notify_on_cnt++;
        }
        else {
            port->stat_notify_off_cnt++;
        }
        event_cb((ACM_EVT_E)line_state);
    }
    return;
}


static USB_VOID gs_acm_cdev_read_cb(struct gs_acm_cdev_port *port)
{
    struct list_head *queue = &port->read_done_queue;
    struct usb_request	*req = NULL;
    ACM_READ_DONE_CB_T read_cb = NULL;
    USB_ULONG flags;
    USB_INT status = 0;

    for (;;) {
        spin_lock_irqsave(&port->port_lock, flags);
        if (port->read_completed <= 0) {
            spin_unlock_irqrestore(&port->port_lock, flags);
            return;
        }
        port->read_completed--;

        if (!list_empty(queue)) {
            req = list_first_entry(queue, struct usb_request, list);
            status= req->status;

            /* if there are data in queue, prepare the read callback */
            if (!req->status && port->open_count) {
                read_cb = port->read_done_cb;
            }
            else {
                list_move(&req->list, &port->read_pool);
                port->read_started--;
            }
        }

        /* submit the next read req */
        if (-ESHUTDOWN != status && port->port_usb) {
		    gs_acm_cdev_start_rx(port);
        }
        else {
            port->stat_rx_cb_not_start++;
        }
        spin_unlock_irqrestore(&port->port_lock, flags);

        if (NULL != read_cb) {
            port->stat_rx_callback++;
            read_cb();
        }
    }
}

static USB_VOID gs_acm_cdev_write_cb(struct gs_acm_cdev_port *port)
{
    struct usb_request	*req = NULL;
    struct list_head	*queue = &port->write_queue;
    USB_PCHAR buf;
    USB_INT actual_size;
    ACM_WRITE_DONE_CB_T write_cb = NULL;
    USB_ULONG flags;

    for (;;) {
        spin_lock_irqsave(&port->port_lock, flags);
        if (port->write_completed <= 0) {
            spin_unlock_irqrestore(&port->port_lock, flags);
            return;
        }
        write_cb = port->write_done_cb;
        actual_size = 0;
        buf = NULL;
        port->write_completed--;

        if (!list_empty(queue)) {
            req = list_first_entry(queue, struct usb_request, list);

            /* if there is data in queue, prepare the write callback */
            buf = req->buf;
            actual_size = (!req->status) ? (int)req->actual : (int)req->status;
            list_move(&req->list, &port->write_pool);
            port->write_started--;
        }
        spin_unlock_irqrestore(&port->port_lock, flags);

        if (NULL != write_cb) {
            port->stat_tx_callback++;
            write_cb(buf, actual_size);
        }
    }
}

/*
 * rw workqueue takes data out of the RX queue and hands it up to the TTY
 * layer until it refuses to take any more data (or is throttled back).
 * Then it issues reads for any further data.
 */
static USB_VOID gs_acm_cdev_rw_push(struct work_struct *work)
{
	struct gs_acm_cdev_port *port;

    /* notify callback */
    while (NULL != (port = gs_acm_evt_get(&gs_acm_sig_stat_evt_manage))) {
        gs_acm_cdev_notify_cb(port);
    }

    /* read callback */
    while (NULL != (port = gs_acm_evt_get(&gs_acm_read_evt_manage))) {
        gs_acm_cdev_read_cb(port);
    }

    /* write callback */
    while (NULL != (port = gs_acm_evt_get(&gs_acm_write_evt_manage))) {
        gs_acm_cdev_write_cb(port);
    }

    /* other callback ... */

    return;
}

static USB_VOID gs_acm_cdev_read_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct gs_acm_cdev_port	*port = ep->driver_data;
    struct gs_acm_cdev_rw_priv *rw_priv;

    if (0 != gs_acm_cdev_is_port_block(port))
    {
        req->status = -EIO;
        port->stat_rx_blocked++;
    }

	/* Queue all received data until the tty layer is ready for it. */
	spin_lock(&port->port_lock);

    if (!req->status) {
        port->stat_rx_done++;
        port->stat_rx_done_bytes += req->actual;
    }
    else {
        port->stat_rx_done_fail++;
    }

    rw_priv = (struct gs_acm_cdev_rw_priv *)req->context;
    list_del_init(&rw_priv->list);
    port->read_req_enqueued--;

    if (port->port_usb && !port->is_realloc && req->actual) {
    	list_add_tail(&req->list, &port->read_done_queue);
        port->stat_rx_done_schdule++;
        port->read_completed++;
        gs_acm_evt_push(port, &gs_acm_read_evt_manage);
        queue_delayed_work(gs_cdev_driver->acm_work_queue, &port->rw_work, 0);
    }
    else {
        list_add_tail(&req->list, &port->read_pool);
        port->read_started--;
        port->stat_rx_done_disconnect++;
    }
	spin_unlock(&port->port_lock);

    /* if there is blocked read, wake up it */
    if (port->read_blocked) {
        port->read_blocked = 0;
        port->stat_rx_wakeup_block++;
        wake_up_interruptible(&port->read_wait);
    }

    /* if clean up all read reqs, wake up the realloc task */
    if (port->is_realloc && !port->read_started) {
        port->stat_rx_wakeup_realloc++;
        wake_up(&port->realloc_wait);
    }
}

static USB_VOID gs_acm_cdev_write_complete(struct usb_ep *ep, struct usb_request *req)
{
	struct gs_acm_cdev_port	*port = ep->driver_data;
    struct gs_acm_cdev_rw_priv *write_priv;

	spin_lock(&port->port_lock);
    write_priv = (struct gs_acm_cdev_rw_priv *)req->context;

    if (!req->status) {
        port->stat_tx_done++;
        port->stat_tx_done_bytes += req->actual;
    }
    else {
        port->stat_tx_done_fail++;
    }

    /* sync read wake up the blocked task*/
    if (write_priv->is_sync) {
        list_add_tail(&req->list, &port->write_pool);
        port->write_started--;
        port->write_block_status = req->status;
        port->write_blocked = 0;
        write_priv->is_sync = 0;
        port->stat_tx_wakeup_block++;
        wake_up_interruptible(&port->write_wait);
    }
    /* async read schedule the workqueue to call the callback */
    else {
        if (port->port_usb) {
            list_add_tail(&req->list, &port->write_queue);
            port->stat_tx_done_schdule++;
            port->write_completed++;
            gs_acm_evt_push(port, &gs_acm_write_evt_manage);
            queue_delayed_work(gs_cdev_driver->acm_work_queue, &port->rw_work, 0);
        }
        else {
            list_add_tail(&req->list, &port->write_pool);
            port->write_started--;
            port->stat_tx_done_disconnect++;
        }
    }
	spin_unlock(&port->port_lock);
}

static USB_VOID gs_acm_cdev_free_request(struct usb_ep *ep, struct usb_request	*req)
{
    struct gs_acm_cdev_rw_priv *write_priv;
    write_priv = (struct gs_acm_cdev_rw_priv *)req->context;

    /* if copy_data flag is ture,
     * the data buffer is belong to usr, don't free it
     */
    if (req->context) 
    {
        if (!write_priv->is_copy) 
        {
            req->buf = NULL;
        }
        kfree(req->context);
        req->context = NULL;
    }
	gs_free_req(ep, req);
}

static USB_VOID gs_acm_cdev_free_requests(struct usb_ep *ep, struct list_head *head,
							 int *allocated)
{
	struct usb_request	*req;

	while (!list_empty(head)) {
		req = list_entry(head->next, struct usb_request, list);
		list_del_init(&req->list);
        gs_acm_cdev_free_request(ep, req);
		if (allocated)
			(*allocated)--;
	}
}

static struct usb_request*
gs_acm_cdev_alloc_request(struct usb_ep *ep, USB_UINT buf_size)
{
    struct gs_acm_cdev_rw_priv *rw_priv;
    struct usb_request	*req;

    req = gs_alloc_req(ep, buf_size, GFP_ATOMIC);

    if (!req) {
        DBG_E(MBB_ACM,"=================== gs_alloc_req fail\n");

	  return NULL;
    }

    rw_priv = (struct gs_acm_cdev_rw_priv *)
              kzalloc(sizeof(struct gs_acm_cdev_rw_priv), GFP_ATOMIC);
    if (!rw_priv) {
        DBG_E(MBB_ACM,"==================== kzalloc fail\n");
        gs_free_req(ep, req);
        return NULL;
    }
    req->context = (void*)rw_priv;
    rw_priv->req = req;
    if (buf_size) {
        rw_priv->is_copy = 1;
    }
    INIT_LIST_HEAD(&rw_priv->list);

    return req;
}

static USB_INT gs_acm_cdev_alloc_requests(struct usb_ep *ep, struct list_head *head,
		USB_VOID (*fn)(struct usb_ep *, struct usb_request *),
		USB_INT *allocated, USB_UINT buf_size, USB_UINT buf_num)
{
	USB_INT			i;
	struct usb_request	*req;

	USB_INT n = allocated ? buf_num - *allocated : buf_num;

	for (i = 0; i < n; i++) {

        req = gs_acm_cdev_alloc_request(ep, buf_size);
        if (!req)
            return list_empty(head) ? -ENOMEM : 0;
		req->complete = fn;
		list_add_tail(&req->list, head);
		if (allocated)
			(*allocated)++;
	}
	return 0;
}

/*
 * Context: holding port_lock;
 */
static USB_INT gs_acm_cdev_prepare_io(struct gs_acm_cdev_port *port)
{
    struct list_head	*head = &port->read_pool;
	struct usb_ep		*ep = port->port_usb->out;
	USB_INT			status;

    status = gs_acm_cdev_alloc_requests(ep, head, gs_acm_cdev_read_complete,
		&port->read_allocated, port->read_buf_size, port->read_req_num);
	if (status)
		return status;

	status = gs_acm_cdev_alloc_requests(port->port_usb->in, &port->write_pool,
			gs_acm_cdev_write_complete, &port->write_allocated, 0, port->write_req_num);
	if (status) {
		gs_acm_cdev_free_requests(ep, head, &port->read_allocated);
		return status;
	}

    return 0;
}

/*-------------------------------------------------------------------------*/

static inline USB_INT gs_acm_cdev_get_port_num(struct inode *inode)
{
    USB_INT		port_num;

    if (!gs_cdev_driver || !inode) {
        gs_stat_drv_invalid++;
		return -ENXIO;
    }

    port_num = inode->i_rdev - gs_cdev_driver->dev_no;

    if (port_num >= gs_acm_cdev_n_ports) {
        gs_stat_port_num_err++;
		return -ENXIO;
    }

    return port_num;
}

static USB_INT gs_acm_cdev_open(struct inode *inode, struct file *filp)
{
	USB_INT	port_num;
	struct gs_acm_cdev_port	*port;
	USB_INT	status;
    USB_ULONG flags;

    port_num = gs_acm_cdev_get_port_num(inode);
    if (port_num < 0) {
        return port_num;
    }

	do {
		mutex_lock(&gs_acm_cdev_ports[port_num].open_close_lock);
		port = gs_acm_cdev_ports[port_num].port;
		if (!port)
			status = -ENODEV;
		else {
			spin_lock_irqsave(&port->port_lock, flags);

			/* already open?  Great. */
			if (port->open_count) {
				status = 0;
				port->open_count++;

			/* currently opening/closing? wait ... */
			} else if (port->openclose) {
				status = -EBUSY;

			/* ... else we do the work */
			} else {
				status = -EAGAIN;
				port->openclose = true;
			}
			spin_unlock_irqrestore(&port->port_lock, flags);
		}
		mutex_unlock(&gs_acm_cdev_ports[port_num].open_close_lock);

		switch (status) {
		default:
			/* fully handled */
			return status;
		case -EAGAIN:
			/* must do the work */
			break;
		case -EBUSY:
			/* wait for EAGAIN task to finish */
			msleep(10);
			/* REVISIT could have a waitchannel here, if
			 * concurrent open performance is important
			 */
			break;
		}
	} while (status != -EAGAIN);

    spin_lock_irqsave(&port->port_lock, flags);
	port->open_count = 1;
	port->openclose = false;

#if ACM_CDEV_SUPPORT_NOTIFY
    /* if connected, start the I/O stream */
	if (port->port_usb) {
        struct gserial	*gser = port->port_usb;
		if (gser->connect)
			gser->connect(gser);
	}
#endif
    spin_unlock_irqrestore(&port->port_lock, flags);

	return 0;
}

static USB_INT gs_acm_cdev_close(struct inode *inode, struct file *file)
{
	struct gs_acm_cdev_port *port;
    USB_ULONG flags;
    USB_INT status;

    status = gs_acm_cdev_get_port_num(inode);
    if (status < 0)
        return status;
    port = gs_acm_cdev_ports[status].port;

	spin_lock_irqsave(&port->port_lock, flags);

	if (port->open_count != 1) {
		if (port->open_count == 0) {
			WARN_ON(1);
            return -EBADF;
        }
		else {
			--port->open_count;
        }
		goto exit;
	}

	/* mark port as closing but in use; we can drop port lock
	 * and sleep if necessary
	 */
	port->openclose = true;
	port->open_count = 0;
	port->line_state_on = 0;
	port->line_state_change = 0;

#if ACM_CDEV_SUPPORT_NOTIFY
    {
        struct gserial	*gser;
    	gser = port->port_usb;
    	if (gser && gser->disconnect)
    		gser->disconnect(gser);
    }
#endif

	port->openclose = false;

	wake_up_interruptible(&port->close_wait);
exit:
	spin_unlock_irqrestore(&port->port_lock, flags);
    return 0;
}

static USB_INT gs_acm_cdev_write_base(struct gs_acm_cdev_port *port,
                                  USB_PCHAR buf, USB_UINT len, bool is_sync)
{
	USB_INT status = 0;

    if (len==0) {
        DBG_E(MBB_ACM,"gs_acm_cdev_write_base: zero length packet to send\n");
        return status;
    }

    if (0 != gs_acm_cdev_is_port_block(port))
    {
        port->stat_tx_blocked++;
        return -EIO;
    }

    /* we must check buf addr if don't use copy_from_user */
    if (!port->is_do_copy && !virt_addr_valid(buf)) {
        DBG_E(MBB_ACM,"gs_acm_cdev_write_base inval buf:%p\n", buf);
        return -EINVAL;
    }

    mutex_lock(&port->write_lock);

    status = gs_acm_cdev_start_tx(port, buf, len, is_sync);
    if (status) {
        goto write_mutex_exit;
    }

    /* async write don't need to wait write complete */
    if (!is_sync){
        goto write_mutex_exit;
    }

    status = wait_event_interruptible(port->write_wait, (port->write_blocked == 0));
    if (status) {
        port->stat_sync_tx_wait_fail++;
        goto write_mutex_exit;
    }

    /* check status */
    if (port->write_block_status) {
        status = port->write_block_status;
        port->write_block_status = 0;
    }
    else {
        status = (int)len;
    }

write_mutex_exit:
    mutex_unlock(&port->write_lock);
	return status;
}

/**
 *	gs_acm_cdev_write		-	write method for tty device file
 *	@file: acm file pointer
 *	@buf: user data to write
 *	@count: bytes to write
 *	@ppos: unused
 *
 *	Write data to a acm device.
 *
 */
static ssize_t gs_acm_cdev_write(struct file *file, const char __user *buf,
						         USB_SIZE_T count, loff_t *ppos)
{
    struct inode *inode = file->f_path.dentry->d_inode;
    USB_INT		port_num;
	struct gs_acm_cdev_port	*port;
    USB_UINT len = (USB_UINT)count;
    USB_INT status;

    if (unlikely(NULL == buf || 0 == count)) {
        DBG_E(MBB_ACM," invalid param buf:%p, count:%d\n", buf, count);
        return -EFAULT;
    }

    port_num = gs_acm_cdev_get_port_num(inode);
    if (port_num < 0)
        return port_num;

    port = gs_acm_cdev_ports[port_num].port;

    port->stat_sync_tx_submit++;
    status = gs_acm_cdev_write_base(port, (char*)buf, len, true);
    if (status > 0)
        port->stat_sync_tx_done++;
    else
        port->stat_sync_tx_fail++;

    return (ssize_t)status;
}

static struct usb_request *
gs_acm_cdev_get_reading_req(struct gs_acm_cdev_port *port)
{
    struct usb_request *reading_req;

    if (NULL == port->reading_req) {
        if (list_empty(&port->read_done_queue))
            reading_req = NULL;
        else {
            reading_req =
                list_first_entry(&port->read_done_queue, struct usb_request, list);
            list_del_init(&reading_req->list);
        }
    }
    else {
        reading_req = port->reading_req;
    }
    return reading_req;
}

static USB_VOID
gs_acm_cdev_ret_reading_req(struct gs_acm_cdev_port *port, struct usb_request *req)
{
    USB_ULONG flags;

    spin_lock_irqsave(&port->port_lock, flags);
    list_add_tail(&req->list, &port->read_pool);
    port->read_started--;
    spin_unlock_irqrestore(&port->port_lock, flags);
    return;
}

/**
 *	gs_acm_cdev_read		-	read method for cdev device file
 *	@file: acm file pointer
 *	@buf: user data to read
 *	@count: bytes to read
 *	@ppos: unused
 *
 *	read data form a acm device.
 *
 */
static ssize_t gs_acm_cdev_read(struct file *file, char __user *buf,
						        USB_SIZE_T count, loff_t *ppos)
{
    struct inode *inode = file->f_path.dentry->d_inode;
    USB_INT	port_num;
	struct gs_acm_cdev_port	*port;
    struct usb_request *reading_req;
     USB_ULONG flags;
    struct gs_acm_cdev_rw_priv *read_priv;
    USB_UINT need_size = (USB_UINT)count;
    USB_UINT copy_size;
    USB_UINT left_size;
    USB_PCHAR  copy_addr;
    USB_INT	status = 0;

    port_num = gs_acm_cdev_get_port_num(inode);
    if (port_num < 0)
        return port_num;
    port = gs_acm_cdev_ports[port_num].port;

    port->stat_read_call++;
    if (unlikely(NULL == buf || 0 == count)) {
        port->stat_read_param_err++;
        return -EFAULT;
    }

    mutex_lock(&port->read_lock);
    do {
        spin_lock_irqsave(&port->port_lock, flags);
        if (!port->port_usb || port->is_suspend) {
            port->stat_sync_rx_disconnect++;
            spin_unlock_irqrestore(&port->port_lock, flags);
            goto read_exit;
        }
        reading_req = gs_acm_cdev_get_reading_req(port);

        if (NULL == reading_req) {
            /* if no req, wait for reading complete */
            port->read_blocked = 1;
            spin_unlock_irqrestore(&port->port_lock, flags);
            status = wait_event_interruptible
                        (port->read_wait, (port->read_blocked == 0));
            if (status) {
                port->stat_sync_rx_wait_fail++;
                goto read_exit;
            }
        }
        else {
            spin_unlock_irqrestore(&port->port_lock, flags);
        }
    }while(NULL == reading_req);

    if (reading_req->status) {
        port->stat_sync_rx_done_fail++;
        goto read_drop_data;
    }

    /* prepare copy address and copy size */
    read_priv = (struct gs_acm_cdev_rw_priv *)reading_req->context;
    copy_addr = (char*)reading_req->buf + read_priv->copy_pos;
    left_size = reading_req->actual - read_priv->copy_pos;
	if (left_size > need_size)
	{
		copy_size = need_size;
		read_priv->copy_pos += copy_size;
        port->reading_req = reading_req;
	}
	else
	{
		copy_size = left_size;
		read_priv->copy_pos = 0;
		port->reading_req = NULL;
	}

    /* copy data to usr buffer */
    if (copy_to_user((void*)buf, (void*)copy_addr, copy_size)) {
	    status = -EFAULT;
        port->stat_sync_rx_copy_fail++;
        goto read_drop_data;
    }
    status = (int)copy_size;

    if (NULL == port->reading_req)
    {
        gs_acm_cdev_ret_reading_req(port, reading_req);
    }
    port->stat_sync_rx_done++;
    port->stat_sync_rx_done_bytes += copy_size;

    goto read_exit;

read_drop_data:
    port->reading_req = NULL;
    gs_acm_cdev_ret_reading_req(port, reading_req);
read_exit:
    mutex_unlock(&port->read_lock);
	return (ssize_t)status;
}

static USB_INT gs_acm_cdev_realloc_read_buf(struct gs_acm_cdev_port *port,
                                        ACM_READ_BUFF_INFO *buf_info)
{
    USB_INT status = 0;
    struct usb_ep *out;
    struct list_head *head = &port->read_pool;
    USB_ULONG flags = 0;

    /* get the read lock to stop usr use the read interface */
    mutex_lock(&port->read_lock);

    /* 1. dequeue all read req in usb core */
    spin_lock_irqsave(&port->port_lock, flags);
    if (unlikely(!port->port_usb)) {
        status = -ENODEV;
        goto realloc_exit;
    }
    port->is_realloc = 1;

    out = port->port_usb->out;
    gs_acm_cdev_stop_rx(port);
    spin_unlock_irqrestore(&port->port_lock, flags);

    /* 2. wait for all read req complete */
    (void)wait_event_timeout(port->realloc_wait, (!port->read_started), 300);

    spin_lock_irqsave(&port->port_lock, flags);

    /* make sure the read reqs have been clean up */

    /* 3. free the old req pool */
    gs_acm_cdev_free_requests(out, head, &port->read_allocated);


    /* 4. alloc the new req pool */
    port->read_req_num = buf_info->u32BuffNum;
    port->read_buf_size = buf_info->u32BuffSize;

    status = gs_acm_cdev_alloc_requests(out, head, gs_acm_cdev_read_complete,
		&port->read_allocated, port->read_buf_size, port->read_req_num);

    /* 5. restart the rx */
    gs_acm_cdev_start_rx(port);

realloc_exit:
    port->is_realloc = 0;
    spin_unlock_irqrestore(&port->port_lock, flags);
    mutex_unlock(&port->read_lock);

    return status;
}

static USB_LONG gs_acm_cdev_ioctl(struct file *file, USB_UINT cmd, USB_ULONG arg)
{
    struct inode *inode = file->f_path.dentry->d_inode;
    ACM_WR_ASYNC_INFO *rw_info;
    struct gs_acm_cdev_port	*port;
    USB_INT	status;

    DBG_I(MBB_ACM,"%s: entry!\n" ,__func__);

    if (get_fs() != KERNEL_DS) {
        DBG_E(MBB_ACM,"can't support in usr space\n");
        return -ENOTSUPP;
    }
    
    status = gs_acm_cdev_get_port_num(inode);
    if (status < 0) {
        DBG_E(MBB_ACM,"gs_acm_cdev_get_port_num err, status=%d\n",status);
        return status;
    }

    port = gs_acm_cdev_ports[status].port;

    /* init the return status */
    status = 0;
    switch (cmd) {
	case ACM_IOCTL_SET_READ_CB:
	case UDI_IOCTL_SET_READ_CB:
	    port->read_done_cb = (ACM_READ_DONE_CB_T)arg;
	    break;

	case ACM_IOCTL_SET_WRITE_CB:
	case UDI_IOCTL_SET_WRITE_CB:
	    port->write_done_cb = (ACM_WRITE_DONE_CB_T)arg;
	    break;

	case ACM_IOCTL_SET_EVT_CB:
        port->event_notify_cb = (ACM_EVENT_CB_T)arg;
        if (port->port_num < ACM_CDEV_COUNT)
            gs_acm_cdev_ports[port->port_num].event_cb = (ACM_EVENT_CB_T)arg;
	    break;

	case ACM_IOCTL_SET_FREE_CB:
	    port->write_done_free_cb = (ACM_FREE_CB_T)arg;
	    break;

	case ACM_IOCTL_WRITE_ASYNC:
		if (0 == arg) {
			DBG_E(MBB_ACM,"gs_acm_cdev_ioctl ACM_IOCTL_WRITE_ASYNC invalid param\n");
			return -EFAULT;
		}
		rw_info = (ACM_WR_ASYNC_INFO *)arg;
		port->stat_write_async_call++;
		status = gs_acm_cdev_write_base(port, rw_info->pBuffer, rw_info->u32Size, false);
	    break;

	case ACM_IOCTL_GET_RD_BUFF:
		if (0 == arg) {
		    DBG_E(MBB_ACM,"gs_acm_cdev_ioctl ACM_IOCTL_GET_RD_BUFF invalid param\n");
		    return -EFAULT;
		}
		port->stat_get_buf_call++;
		status = gs_acm_cdev_get_read_buf(port, (ACM_WR_ASYNC_INFO*)arg);
	    break;

	case ACM_IOCTL_RETURN_BUFF:
		if (0 == arg) {
		    DBG_E(MBB_ACM,"gs_acm_cdev_ioctl ACM_IOCTL_RETURN_BUFF invalid param\n");
		    return -EFAULT;
		}
		port->stat_ret_buf_call++;
		status = gs_acm_cdev_ret_read_buf(port, (ACM_WR_ASYNC_INFO*)arg);
	    break;

	case ACM_IOCTL_RELLOC_READ_BUFF:
		if (0 == arg) {
		    DBG_E(MBB_ACM,"gs_acm_cdev_ioctl ACM_IOCTL_RELLOC_READ_BUFF invalid param\n");
		    return -EFAULT;
		}
		status = gs_acm_cdev_realloc_read_buf(port, (ACM_READ_BUFF_INFO*)arg);
	    break;

	case ACM_IOCTL_SEND_BUFF_CAN_DMA:
        port->is_dma_tx = true;
	    break;

    case ACM_IOCTL_WRITE_DO_COPY:
        port->is_do_copy = (bool)arg;
        break;

	default:
        status = -1;
        break;
	}

    return status;
}

static const struct file_operations gs_acm_cdev_fops = {
	.llseek		= no_llseek,

	.read		=       gs_acm_cdev_read,
	.write		=       gs_acm_cdev_write,
	.unlocked_ioctl	=   gs_acm_cdev_ioctl,
	.open		=       gs_acm_cdev_open,
	.release	=       gs_acm_cdev_close,
};

/*-------------------------------------------------------------------------*/

static USB_INT gs_acm_cdev_port_alloc(USB_UINT port_num, struct usb_cdc_line_coding *coding)
{
	struct gs_acm_cdev_port	*port;

	port = kzalloc(sizeof(struct gs_acm_cdev_port), GFP_KERNEL);
	if (port == NULL)
		return -ENOMEM;

	spin_lock_init(&port->port_lock);
	init_waitqueue_head(&port->close_wait);

    INIT_DELAYED_WORK(&port->rw_work, gs_acm_cdev_rw_push);

	INIT_LIST_HEAD(&port->read_pool);
	INIT_LIST_HEAD(&port->read_done_queue);
    INIT_LIST_HEAD(&port->read_using_queue);
    INIT_LIST_HEAD(&port->read_queue_in_usb);
	INIT_LIST_HEAD(&port->write_pool);
    INIT_LIST_HEAD(&port->write_queue);

    init_waitqueue_head(&port->write_wait);
    init_waitqueue_head(&port->read_wait);
    init_waitqueue_head(&port->realloc_wait);

    mutex_init(&port->write_lock);
    mutex_init(&port->read_lock);

	port->port_num = port_num;
	port->port_line_coding = *coding;

    port->read_buf_size = ACM_CDEV_DFT_RD_BUF_SIZE;
    port->read_req_num = ACM_CDEV_DFT_RD_REQ_NUM;
    port->write_req_num = gs_acm_cdev_get_tx_buf_num(port_num);
    port->is_do_copy = 1;

	gs_acm_cdev_ports[port_num].port = port;

    /* mark the asic string for debug */
    snprintf(gs_acm_cdev_ports[port_num].name_domain, 4, "acm%d", port_num);
    snprintf(port->read_domain, 4, "%d_rd", port_num);
    snprintf(port->write_domain, 4, "%d_wt", port_num);
    snprintf(port->debug_tx_domain, 4, "dtx%d", port_num);
    snprintf(port->debug_rx_domain, 4, "drx%d", port_num);
    snprintf(port->debug_port_domain, 4, "dpt%d", port_num);

	return 0;
}

static struct u_cdev_driver *gs_acm_cdev_alloc_driver(USB_INT lines)
{
	struct u_cdev_driver *driver;

	driver = kzalloc(sizeof(struct u_cdev_driver), GFP_KERNEL);
	if (driver) {
		kref_init(&driver->kref);
		driver->num = lines;
	}
	return driver;
}

static USB_INT gs_acm_cdev_register_driver(struct u_cdev_driver *driver)
{
    USB_INT error;
    dev_t dev;

    error = alloc_chrdev_region(&dev, driver->minor_start,
						driver->num, driver->name);
    if (error < 0) {
		return error;
	}
	driver->major = MAJOR(dev);
	driver->minor_start = MINOR(dev);

    cdev_init(&driver->cdev, &gs_acm_cdev_fops);
    driver->cdev.owner = driver->owner;
    error = cdev_add(&driver->cdev, dev, driver->num);
    if (error) {
		unregister_chrdev_region(dev, driver->num);
		return error;
	}
    driver->dev_no = dev;

    return 0;
}

static USB_VOID gs_acm_cdev_unregister_driver(struct u_cdev_driver *driver)
{
    cdev_del(&driver->cdev);
    return unregister_chrdev_region(gs_cdev_driver->dev_no, gs_cdev_driver->num);
}

static struct device *gs_acm_cdev_register_device(struct u_cdev_driver *driver,
                        USB_UINT index, struct device *device)
{
	USB_CHAR name[ACM_CDEV_NAME_MAX];
	dev_t dev = MKDEV(driver->major, driver->minor_start) + index;

	if (index >= driver->num) {
		DBG_E(MBB_ACM,"Attempt to register invalid tty line number (%d).\n", index);
		return ERR_PTR(-EINVAL);
	}
    snprintf(name, ACM_CDEV_NAME_MAX, "%s",acm_ctx->cdev_name_type_var[index].name);
    
    return device_create(tty_class, device, dev, NULL, name);
}

static USB_VOID gs_acm_cdev_unregister_device(struct u_cdev_driver *driver,
                                          USB_UINT index)
{
	device_destroy(tty_class,
		MKDEV(driver->major, driver->minor_start) + index);
}

static USB_INT gs_acm_usb_notifier_cb(struct notifier_block *nb,
            USB_ULONG event, USB_PVOID priv)
{
    USB_INT i;

    /*  event <= 0 means:
     *  USB_BALONG_DEVICE_DISABLE or USB_BALONG_DEVICE_REMOVE
     */
    if (USB_BALONG_DEVICE_DISABLE == event ||
        USB_BALONG_DEVICE_REMOVE == event) {

        for (i = 0; i < ACM_CDEV_COUNT; i++) {
            if (gs_acm_cdev_ports[i].event_cb) {
                gs_acm_cdev_ports[i].event_cb(ACM_EVT_DEV_SUSPEND);
            }
        }
    }
    return 0;
}

/**
 * gacm_cdev_setup - initialize cdev driver for one or more gs_acm_cdev_ports
 * @g: gadget to associate with these gs_acm_cdev_ports
 * @count: how many gs_acm_cdev_ports to support
 * Context: may sleep
 *
 * Returns negative errno or zero.
 */
USB_INT gacm_cdev_setup(struct usb_gadget *g, USB_UINT count)
{
	USB_UINT			i;
	struct usb_cdc_line_coding	coding;
	USB_INT				status;

	if (count == 0 || count > ACM_CDEV_COUNT)
		return -EINVAL;

	gs_cdev_driver = gs_acm_cdev_alloc_driver(count);
	if (!gs_cdev_driver)
		return -ENOMEM;

    gs_cdev_driver->owner = THIS_MODULE;
	gs_cdev_driver->driver_name = ACM_CDEV_DRV_NAME;
	gs_cdev_driver->name = ACM_CDEV_PREFIX;

	gs_acm_evt_init(&gs_acm_write_evt_manage, "write_evt");
	gs_acm_evt_init(&gs_acm_read_evt_manage, "read_evt");
	gs_acm_evt_init(&gs_acm_sig_stat_evt_manage, "sig_stat_evt");

	coding.dwDTERate = cpu_to_le32(115200);
	coding.bCharFormat = 8;
	coding.bParityType = USB_CDC_NO_PARITY;
	coding.bDataBits = USB_CDC_1_STOP_BITS;

	/* alloc and init each port */
	for (i = 0; i < count; i++) {
		mutex_init(&gs_acm_cdev_ports[i].open_close_lock);
		status = gs_acm_cdev_port_alloc(i, &coding);
		if (status) {
			count = i;
			goto setup_fail;
		}
	}
	gs_acm_cdev_n_ports = count;

	/* register the driver ... */
	status = gs_acm_cdev_register_driver(gs_cdev_driver);
	if (status) {
		DBG_E(MBB_ACM," cannot register, err %d\n",status);
        
		goto setup_fail;
	}

	/* register devices ... */
	for (i = 0; i < count; i++) {
		struct device	*cdev;

		cdev = gs_acm_cdev_register_device(gs_cdev_driver, i, &g->dev);
		if (IS_ERR(cdev)){
			DBG_W(MBB_ACM," no classdev for port %d, err %ld\n",
				 i, PTR_ERR(cdev));
            goto setup_fail;
        }
        gs_acm_cdev_ports[i].cdev = cdev;
	}

    gs_cdev_driver->acm_work_queue = create_singlethread_workqueue("acm_cdev");
    if (!gs_cdev_driver->acm_work_queue)
    {
        status = -ENOMEM;
        goto setup_fail;
    }

    /* we just regist once, and don't unregist any more */
    if (!gs_acm_nb_ptr) {
        gs_acm_nb_ptr = &gs_acm_nb;
        gs_acm_nb.priority = 0;
        gs_acm_nb.notifier_call = gs_acm_usb_notifier_cb;
        bsp_usb_register_notify(gs_acm_nb_ptr);
    }

	return status;

setup_fail:
    if (gs_cdev_driver->acm_work_queue)
        destroy_workqueue(gs_cdev_driver->acm_work_queue);
		
    if(count >= ACM_CDEV_COUNT)
    {
		DBG_E(MBB_ACM,"count is too big %d\n",count);
        count = ACM_CDEV_COUNT - 1;
    }
	
	while (count)
    {
        if (gs_acm_cdev_ports[count].port)
        {
            kfree(gs_acm_cdev_ports[count].port);
        }

        if (gs_acm_cdev_ports[count].cdev)
        {
            gs_acm_cdev_unregister_device(gs_cdev_driver, count);
        }
        
        count--;
    }
    
    gs_acm_cdev_unregister_driver(gs_cdev_driver);

    if (gs_cdev_driver){
        kfree(gs_cdev_driver);
	    gs_cdev_driver = NULL;
    }
	return status;
}

static USB_INT gs_acm_cdev_closed(struct gs_acm_cdev_port *port)
{
	USB_INT cond;
    unsigned long flags;

	spin_lock_irqsave(&port->port_lock, flags);
	cond = (port->open_count == 0) && !port->openclose;
	spin_unlock_irqrestore(&port->port_lock, flags);
	return cond;
}

/**
 * gacm_cdev_cleanup - remove cdev-over-USB driver and devices
 * Context: may sleep
 *
 * This is called to free all resources allocated by @gserial_setup().
 * Accordingly, it may need to wait until some open /dev/ files have
 * closed.
 *
 * The caller must have issued @gserial_disconnect() for any gs_acm_cdev_ports
 * that had previously been connected, so that there is never any
 * I/O pending when it's called.
 */
USB_VOID gacm_cdev_cleanup(USB_VOID)
{
	USB_UINT i;
	struct gs_acm_cdev_port	*port;

	if (!gs_cdev_driver)
		return;

	/* start sysfs and /dev/ttyGS* node removal */
	for (i = 0; i < gs_acm_cdev_n_ports; i++)
		gs_acm_cdev_unregister_device(gs_cdev_driver, i);

	for (i = 0; i < gs_acm_cdev_n_ports; i++) {
		/* prevent new opens */
		mutex_lock(&gs_acm_cdev_ports[i].open_close_lock);
		port = gs_acm_cdev_ports[i].port;
		gs_acm_cdev_ports[i].port = NULL;

		mutex_unlock(&gs_acm_cdev_ports[i].open_close_lock);

		/* wait for old opens to finish */
		wait_event(port->close_wait, gs_acm_cdev_closed(port));

		WARN_ON(port->port_usb != NULL);
		mutex_destroy(&port->write_lock);
        mutex_destroy(&port->read_lock);
		
        cancel_delayed_work_sync(&port->rw_work);
		kfree(port);
	}
	gs_acm_cdev_n_ports = 0;

	gs_acm_cdev_unregister_driver(gs_cdev_driver);

    if (gs_cdev_driver->acm_work_queue) {
        flush_workqueue(gs_cdev_driver->acm_work_queue);
        destroy_workqueue(gs_cdev_driver->acm_work_queue);
        gs_cdev_driver->acm_work_queue = NULL;
    }

    if (gs_cdev_driver){
        kfree(gs_cdev_driver);
	    gs_cdev_driver = NULL;
    }
}

USB_INT gacm_cdev_line_state(struct gserial *gser, USB_UINT32 state)
{
    struct gs_acm_cdev_port	*port = gser->ioport;
    USB_ULONG flags;
    USB_UINT16 line_state;

    if (!port) {
        return -ESHUTDOWN;
    }

	spin_lock_irqsave(&port->port_lock, flags);
	line_state = port->line_state_on;

	/* if line state is change notify the callback */
	if (line_state != (u16)(state & U_ACM_CTRL_DTR)) {
        port->line_state_on = (u16)(state & U_ACM_CTRL_DTR);
        port->line_state_change = 1;
    }
	spin_unlock_irqrestore(&port->port_lock, flags);

    /* host may change the state in a short time, delay it, use the last state */
	if (port->line_state_change) {
	    gs_acm_evt_push(port, &gs_acm_sig_stat_evt_manage);
	    queue_delayed_work(gs_cdev_driver->acm_work_queue, &port->rw_work, 50);
	    port->stat_notify_sched++;
	}
	return 0;
}

USB_INT gacm_cdev_suspend(struct gserial *gser)
{
    struct gs_acm_cdev_port	*port = gser->ioport;
    USB_ULONG flags;

    if (!port) {
        DBG_W(MBB_ACM," port is null\n");
        return -ESHUTDOWN;
    }

	spin_lock_irqsave(&port->port_lock, flags);
	port->is_suspend = 1;
	port->sr_change = 1;
	spin_unlock_irqrestore(&port->port_lock, flags);

	if (port->sr_change) {
	    gs_acm_evt_push(port, &gs_acm_sig_stat_evt_manage);
	    queue_delayed_work(gs_cdev_driver->acm_work_queue, &port->rw_work, 0);
	    port->stat_notify_sched++;
	}

	return 0;
}

USB_INT gacm_cdev_resume(struct gserial *gser)
{
    struct gs_acm_cdev_port	*port = gser->ioport;
    USB_ULONG flags;

    if (!port) {
        DBG_W(MBB_ACM," port is null\n");
        return -ESHUTDOWN;
    }

    /* start read requests */
    spin_lock_irqsave(&port->port_lock, flags);
    port->is_suspend = 0;
    gs_acm_cdev_start_rx(port);
    spin_unlock_irqrestore(&port->port_lock, flags);

    return 0;
}


/**
 * gacm_cdev_connect - notify TTY I/O glue that USB link is active
 * @gser: the function, set up with endpoints and descriptors
 * @port_num: which port is active
 * Context: any (usually from irq)
 *
 * This is called activate endpoints and let the TTY layer know that
 * the connection is active ... not unlike "carrier detect".  It won't
 * necessarily start I/O queues; unless the TTY is held open by any
 * task, there would be no point.  However, the endpoints will be
 * activated so the USB host can perform I/O, subject to basic USB
 * hardware flow control.
 *
 * Caller needs to have set up the endpoints and USB function in @dev
 * before calling this, as well as the appropriate (speed-specific)
 * endpoint descriptors, and also have set up the TTY driver by calling
 * @gserial_setup().
 *
 * Returns negative errno or zero.
 * On success, ep->driver_data will be overwritten.
 */
USB_INT gacm_cdev_connect(struct gserial *gser, USB_UINT8 port_num)
{
	struct gs_acm_cdev_port	*port;
	USB_ULONG	flags;
	USB_INT		status;

	if (!gs_cdev_driver || port_num >= gs_acm_cdev_n_ports) {
        DBG_E(MBB_ACM,"gacm_cdev_connect fail drv:%p, port_num:%d, n_ports:%d\n",
                 gs_cdev_driver, port_num, gs_acm_cdev_n_ports);
        BUG();
		return -ENXIO;
    }

	/* we "know" gserial_cleanup() hasn't been called */
	port = gs_acm_cdev_ports[port_num].port;

    /* mask the not ready interrupt for usb netcard class function driver */
    gser->out->enable_xfer_in_progress = 1;

	/* activate the endpoints */
	status = usb_ep_enable(gser->in);
	if (status < 0) {
        port->stat_enable_in_fail++;
		return status;
    }

	status = usb_ep_enable(gser->out);
	if (status < 0) {
        port->stat_enable_out_fail++;
		goto fail_out;
    }

	/* then tell the tty glue that I/O can work */
	spin_lock_irqsave(&port->port_lock, flags);
    gser->in->driver_data = port;
    gser->out->driver_data = port;
	gser->ioport = (void*)port;
	port->port_usb = gser;

	/* REVISIT unclear how best to handle this state...
	 * we don't really couple it with the Linux TTY.
	 */
	gser->port_line_coding = port->port_line_coding;

    /* prepare requests */
    gs_acm_cdev_prepare_io(port);

	/* if it's already open, start I/O ... and notify the serial
	 * protocol about open/close status (connect/disconnect).
	 * don't need to notify host now ...
	 */
#if ACM_CDEV_SUPPORT_NOTIFY
	if (port->open_count) {
		if (gser->connect)
			gser->connect(gser);
	} else {
		if (gser->disconnect)
			gser->disconnect(gser);
	}
#endif

    /* start read requests */
    gs_acm_cdev_start_rx(port);

	spin_unlock_irqrestore(&port->port_lock, flags);
	port->in_name = (char*)gser->in->name;
	port->out_name = (char*)gser->out->name;
    port->stat_port_connect++;
    port->stat_port_is_connect = 1;
	return status;

fail_out:
	usb_ep_disable(gser->in);
	gser->in->driver_data = NULL;
	port->stat_port_is_connect = 0;
	return status;
}

/**
 * gacm_cdev_disconnect - notify TTY I/O glue that USB link is inactive
 * @gser: the function, on which gserial_connect() was called
 * Context: any (usually from irq)
 *
 * This is called to deactivate endpoints and let the TTY layer know
 * that the connection went inactive ... not unlike "hangup".
 *
 * On return, the state is as if gserial_connect() had never been called;
 * there is no active USB I/O on these endpoints.
 */
USB_VOID gacm_cdev_disconnect(struct gserial *gser)
{
	struct gs_acm_cdev_port	*port = gser->ioport;
	USB_ULONG	flags;

       DBG_I(MBB_ACM," entry!\n");
	if (!port) {
        BUG();
		return;
    }

	/* disable endpoints, aborting down any active I/O */
	usb_ep_disable(gser->out);
	usb_ep_disable(gser->in);

    spin_lock_irqsave(&port->port_lock, flags);

    port->port_usb = NULL;
	gser->ioport = NULL;
    gser->out->driver_data = NULL;
    gser->in->driver_data = NULL;

	gs_acm_cdev_free_requests(gser->out, &port->read_pool, NULL);
	gs_acm_cdev_free_requests(gser->out, &port->read_done_queue, NULL);
	gs_acm_cdev_free_requests(gser->out, &port->read_using_queue, NULL);
	gs_acm_cdev_free_requests(gser->in, &port->write_pool, NULL);
    gs_acm_cdev_free_requests(gser->in, &port->write_queue, NULL);
    port->read_allocated = 0;
    port->write_allocated = 0;

    /* if there are read blocked, wake up in disconnect */
    if (port->read_blocked) {
        port->read_blocked = 0;
        port->stat_discon_wakeup_block++;
        wake_up_interruptible(&port->read_wait);
    }

	spin_unlock_irqrestore(&port->port_lock, flags);
    port->stat_port_disconnect++;
    port->stat_port_is_connect = 0;
    port->is_suspend = 0;
    port->sr_change = 0;
}


USB_VOID usb_cdev_init(USB_VOID)
{
    DBG_I(MBB_ACM," %s:entry!\n",__func__);
    acm_ctx = acm_get_ctx();
    return;
}

USB_VOID usb_cdev_exit(USB_VOID)
{
    return;
}

#define ACM_PRINT_IOCTL(cmd) DBG_E(MBB_ACM,"cmd:%s\t\t\t\tcode:0x%x\n", #cmd, cmd);
void acm_cdev_ioctl_dump(void)
{
    ACM_PRINT_IOCTL(ACM_IOCTL_SET_WRITE_CB);
    ACM_PRINT_IOCTL(ACM_IOCTL_SET_READ_CB);
    ACM_PRINT_IOCTL(ACM_IOCTL_SET_EVT_CB);
    ACM_PRINT_IOCTL(ACM_IOCTL_SET_FREE_CB);
    ACM_PRINT_IOCTL(ACM_IOCTL_WRITE_DO_COPY);
    ACM_PRINT_IOCTL(ACM_IOCTL_WRITE_ASYNC);
    ACM_PRINT_IOCTL(ACM_IOCTL_GET_RD_BUFF);
    ACM_PRINT_IOCTL(ACM_IOCTL_RETURN_BUFF);
    ACM_PRINT_IOCTL(ACM_IOCTL_RELLOC_READ_BUFF);
    ACM_PRINT_IOCTL(ACM_IOCTL_SEND_BUFF_CAN_DMA);
    return;
}

#define ACM_PRINT_ERRNO(err) DBG_E(MBB_ACM,"%s\t\t\t\t%d\t0x%08x\n", #err, -err, -err);
void acm_cdev_errno_dump(void)
{
    ACM_PRINT_ERRNO(EAGAIN);
    ACM_PRINT_ERRNO(ENOMEM);
    ACM_PRINT_ERRNO(ENODEV);
    ACM_PRINT_ERRNO(EFAULT);
    ACM_PRINT_ERRNO(ESHUTDOWN);
    ACM_PRINT_ERRNO(ENXIO);
    ACM_PRINT_ERRNO(EBUSY);
    ACM_PRINT_ERRNO(EBADF);
    ACM_PRINT_ERRNO(EINVAL);
    return;
}

static USB_VOID acm_cdev_dump_ep_info(struct gs_acm_cdev_port *port)
{
    USB_PCHAR find;
    USB_UINT ep_num;

    if (port->stat_port_is_connect) {
        DBG_I(MBB_ACM,"in ep name:\t\t <%s>\n", port->in_name);
        find = strstr(port->in_name, "ep");
        if (find) {
            /* skip "ep" */
            find += 2;
            ep_num = simple_strtoul(find, NULL, 0);
            DBG_I(MBB_ACM,"in ep num:\t\t <%d>\n", ep_num * 2 + 1);
        }
        DBG_I(MBB_ACM,"out ep name:\t\t <%s>\n", port->out_name);
        find = strstr(port->out_name, "ep");
        if (find) {
            /* skip "ep" */
            find += 2;
            ep_num = simple_strtoul(find, NULL, 0);
            DBG_I(MBB_ACM,"out ep num:\t\t <%d>\n", ep_num * 2);
        }
    }
    else {
        DBG_I(MBB_ACM,"the acm dev is not connect\n");
    }
}

USB_VOID acm_cdev_dump(USB_INT port_num)
{
    struct gs_acm_cdev_port	*port;

    if (!gs_cdev_driver || port_num >= gs_acm_cdev_n_ports) {
        DBG_E(MBB_ACM,"gacm_dump fail drv:%p, port_num:%d, n_ports:%d\n",
                 gs_cdev_driver, port_num, gs_acm_cdev_n_ports);
		return;
    }

	port = gs_acm_cdev_ports[port_num].port;

    DBG_E(MBB_ACM,"=== dump stat dev ctx info ===\n");
    DBG_E(MBB_ACM,"build version:            %s\n", __VERSION__);
    DBG_E(MBB_ACM,"build date:               %s\n", __DATE__);
    DBG_E(MBB_ACM,"build time:               %s\n", __TIME__);
    DBG_E(MBB_ACM,"dev name                  %s\n", 
            acm_ctx->cdev_name_type_var[port_num].name);
    DBG_E(MBB_ACM,"gs_stat_drv_invalid       %d\n", gs_stat_drv_invalid);
    DBG_E(MBB_ACM,"gs_stat_port_num_err      %d\n", gs_stat_port_num_err);
    if(NULL == port )
    {
        DBG_E(MBB_ACM,"port is NULL \n");
        return;
    }
    DBG_E(MBB_ACM,"open_count                %d\n", port->open_count);
    DBG_E(MBB_ACM,"openclose                 %d\n", port->openclose);
    DBG_E(MBB_ACM,"is_do_copy                %d\n", port->is_do_copy);
    DBG_E(MBB_ACM,"is_dma_tx                 %d\n", port->is_dma_tx);
    DBG_E(MBB_ACM,"port_num                  %d\n", port->port_num);
    DBG_E(MBB_ACM,"line_state_on             %d\n", port->line_state_on);
    DBG_E(MBB_ACM,"line_state_change         %d\n", port->line_state_change);
    DBG_E(MBB_ACM,"sr_change                 %d\n", port->sr_change);
    DBG_E(MBB_ACM,"is_suspend                %d\n", port->is_suspend);
    DBG_E(MBB_ACM,"port_usb                  0x%x\n", (unsigned int)port->port_usb);
    DBG_E(MBB_ACM,"stat_port_is_connect      %d\n", port->stat_port_is_connect);
    DBG_E(MBB_ACM,"stat_discon_wakeup_block  %d\n", port->stat_discon_wakeup_block);
    acm_cdev_dump_ep_info(port);

    mdelay(10);
    DBG_E(MBB_ACM,"\n=== dump stat read info ===\n");
    DBG_E(MBB_ACM,"read_started              %d\n", port->read_started);
    DBG_E(MBB_ACM,"read_allocated            %d\n", port->read_allocated);
    DBG_E(MBB_ACM,"read_req_enqueued         %d\n", port->read_req_enqueued);
    DBG_E(MBB_ACM,"read_req_num              %d\n", port->read_req_num);
    DBG_E(MBB_ACM,"read_buf_size             %d\n", port->read_buf_size);
    DBG_E(MBB_ACM,"read_completed            %d\n", port->read_completed);
    DBG_E(MBB_ACM,"reading_pos               %d\n", port->reading_pos);

    DBG_E(MBB_ACM,"\n=== dump rx status info ===\n");
    DBG_E(MBB_ACM,"stat_read_call            %d\n", port->stat_read_call);
    DBG_E(MBB_ACM,"stat_get_buf_call         %d\n", port->stat_get_buf_call);
    DBG_E(MBB_ACM,"stat_ret_buf_call         %d\n", port->stat_ret_buf_call);
    DBG_E(MBB_ACM,"stat_read_param_err       %d\n", port->stat_read_param_err);
    DBG_E(MBB_ACM,"read_blocked              %d\n", port->read_blocked);
    DBG_E(MBB_ACM,"stat_sync_rx_submit       %d\n", port->stat_sync_rx_submit);
    DBG_E(MBB_ACM,"stat_sync_rx_done         %d\n", port->stat_sync_rx_done);
    DBG_E(MBB_ACM,"stat_sync_rx_done_fail    %d\n", port->stat_sync_rx_done_fail);
    DBG_E(MBB_ACM,"stat_sync_rx_done_bytes   %d\n", port->stat_sync_rx_done_bytes);
    DBG_E(MBB_ACM,"stat_sync_rx_copy_fail    %d\n", port->stat_sync_rx_copy_fail);
    DBG_E(MBB_ACM,"stat_sync_rx_disconnect   %d\n", port->stat_sync_rx_disconnect);
    DBG_E(MBB_ACM,"stat_sync_rx_wait_fail    %d\n", port->stat_sync_rx_wait_fail);
    DBG_E(MBB_ACM,"stat_rx_submit            %d\n", port->stat_rx_submit);
    DBG_E(MBB_ACM,"stat_rx_submit_fail       %d\n", port->stat_rx_submit_fail);
    DBG_E(MBB_ACM,"stat_rx_disconnect        %d\n", port->stat_rx_disconnect);
    DBG_E(MBB_ACM,"stat_rx_no_req            %d\n", port->stat_rx_no_req);
    DBG_E(MBB_ACM,"stat_rx_done              %d\n", port->stat_rx_done);
    DBG_E(MBB_ACM,"stat_rx_done_fail         %d\n", port->stat_rx_done_fail);
    DBG_E(MBB_ACM,"stat_rx_done_bytes        %d\n", port->stat_rx_done_bytes);
    DBG_E(MBB_ACM,"stat_rx_done_disconnect   %d\n", port->stat_rx_done_disconnect);
    DBG_E(MBB_ACM,"stat_rx_done_schdule      %d\n", port->stat_rx_done_schdule);
    DBG_E(MBB_ACM,"stat_rx_wakeup_block      %d\n", port->stat_rx_wakeup_block);
    DBG_E(MBB_ACM,"stat_rx_wakeup_realloc    %d\n", port->stat_rx_wakeup_realloc);
    DBG_E(MBB_ACM,"stat_rx_callback          %d\n", port->stat_rx_callback);
    DBG_E(MBB_ACM,"stat_rx_cb_not_start      %d\n", port->stat_rx_cb_not_start);
    DBG_E(MBB_ACM,"stat_rx_dequeue           %d\n", port->stat_rx_dequeue);

    mdelay(10);
    DBG_E(MBB_ACM,"\n=== dump stat write info ===\n");
    DBG_E(MBB_ACM,"write_req_num             %d\n", port->write_req_num);
    DBG_E(MBB_ACM,"write_started             %d\n", port->write_started);
    DBG_E(MBB_ACM,"write_completed           %d\n", port->write_completed);
    DBG_E(MBB_ACM,"write_allocated           %d\n", port->write_allocated);
    DBG_E(MBB_ACM,"write_blocked             %d\n", port->write_blocked);
    DBG_E(MBB_ACM,"write_block_status        %d\n", port->write_block_status);

    DBG_E(MBB_ACM,"\n=== dump tx status info ===\n");
    DBG_E(MBB_ACM,"stat_write_async_call     %d\n", port->stat_write_async_call);
    DBG_E(MBB_ACM,"stat_write_param_err      %d\n", port->stat_write_param_err);
    DBG_E(MBB_ACM,"stat_sync_tx_submit       %d\n", port->stat_sync_tx_submit);
    DBG_E(MBB_ACM,"stat_sync_tx_done         %d\n", port->stat_sync_tx_done);
    DBG_E(MBB_ACM,"stat_sync_tx_fail         %d\n", port->stat_sync_tx_fail);
   DBG_E(MBB_ACM,"stat_sync_tx_wait_fail    %d\n", port->stat_sync_tx_wait_fail);
    DBG_E(MBB_ACM,"stat_tx_submit            %d\n", port->stat_tx_submit);
    DBG_E(MBB_ACM,"stat_tx_submit_fail       %d\n", port->stat_tx_submit_fail);
    DBG_E(MBB_ACM,"stat_tx_submit_bytes      %d\n", port->stat_tx_submit_bytes);
    DBG_E(MBB_ACM,"stat_tx_done              %d\n", port->stat_tx_done);
    DBG_E(MBB_ACM,"stat_tx_done_fail         %d\n", port->stat_tx_done_fail);
    DBG_E(MBB_ACM,"stat_tx_done_bytes        %d\n", port->stat_tx_done_bytes);
    DBG_E(MBB_ACM,"stat_tx_done_schdule      %d\n", port->stat_tx_done_schdule);
    DBG_E(MBB_ACM,"stat_tx_done_disconnect   %d\n", port->stat_tx_done_disconnect);
    DBG_E(MBB_ACM,"stat_tx_wakeup_block      %d\n", port->stat_tx_wakeup_block);
    DBG_E(MBB_ACM,"stat_tx_callback          %d\n", port->stat_tx_callback);
    DBG_E(MBB_ACM,"stat_tx_no_req            %d\n", port->stat_tx_no_req);
    DBG_E(MBB_ACM,"stat_tx_copy_fail         %d\n", port->stat_tx_copy_fail);
    DBG_E(MBB_ACM,"stat_tx_alloc_fail        %d\n", port->stat_tx_alloc_fail);
    DBG_E(MBB_ACM,"stat_tx_suspend           %d\n", port->stat_tx_suspend);
    DBG_E(MBB_ACM,"stat_tx_disconnect        %d\n", port->stat_tx_disconnect);

    mdelay(10);
    DBG_E(MBB_ACM,"\n=== dump port status info ===\n");
    DBG_E(MBB_ACM,"stat_port_connect         %d\n", port->stat_port_connect);
    DBG_E(MBB_ACM,"stat_port_disconnect      %d\n", port->stat_port_disconnect);
    DBG_E(MBB_ACM,"stat_enable_in_fail       %d\n", port->stat_enable_in_fail);
    DBG_E(MBB_ACM,"stat_enable_out_fail      %d\n", port->stat_enable_out_fail);
    DBG_E(MBB_ACM,"stat_notify_sched         %d\n", port->stat_notify_sched);
    DBG_E(MBB_ACM,"stat_notify_on_cnt        %d\n", port->stat_notify_on_cnt);
    DBG_E(MBB_ACM,"stat_notify_off_cnt       %d\n", port->stat_notify_off_cnt);
    DBG_E(MBB_ACM,"stat_rx_blocked           %d\n", port->stat_rx_blocked);
    DBG_E(MBB_ACM,"stat_tx_blocked           %d\n", port->stat_tx_blocked);

}

USB_INT acm_cdev_mem_dump(USB_PCHAR buffer, USB_UINT buf_size)
{
    USB_UINT need_size;
    struct gs_acm_cdev_port	*port;
    USB_INT i;
    USB_PCHAR cur = buffer;

    /* no devs exist */
    if (0 == gs_acm_cdev_n_ports) {
        return 0;
    }

    need_size = gs_acm_cdev_n_ports * sizeof(struct gs_acm_cdev_port) + sizeof(USB_INT);
    /* no room left */
    if (need_size > buf_size) {
        return -1;
    }

    /* record port num */
    *((USB_INT*)cur) = gs_acm_cdev_n_ports;
    cur += sizeof(USB_INT);

    for (i = 0; i < gs_acm_cdev_n_ports; i++) {
        port = gs_acm_cdev_ports[i].port;
        if (port) {
            memcpy(cur, port, sizeof(struct gs_acm_cdev_port));
            cur += sizeof(struct gs_acm_cdev_port);
        }
    }

    return (USB_INT)need_size;
}

USB_VOID acm_cdev_dump_evt(USB_VOID)
{
    gs_acm_evt_dump_info(&gs_acm_write_evt_manage);
    gs_acm_evt_dump_info(&gs_acm_read_evt_manage);
    gs_acm_evt_dump_info(&gs_acm_sig_stat_evt_manage);
}

USB_INT32 acm_cdev_write_test(USB_UINT32 port_num, USB_UINT32 buf_size)
{
    struct sk_buff *skb_tx = NULL;
    struct gs_acm_cdev_port *port = NULL;
    USB_INT ret = 0;
    USB_PCHAR buf = NULL;

    if (port_num >= gs_acm_cdev_n_ports)
    {
        DBG_E(MBB_ACM, "invalid port num %u\n", port_num);
        return -1;    
    }
    
    port = gs_acm_cdev_ports[port_num].port;
    if ((NULL == port) || (USB_TEST_PKT_LEN_MIN > buf_size) || (USB_TEST_PKT_LEN_MAX < buf_size))
    {
        DBG_E(MBB_ACM, "wrong param\n");
        return -1;
    }
    
    buf = kmalloc(buf_size, GFP_KERNEL);
    if (NULL == buf)
    {
        DBG_E(MBB_ACM, "alloc buf failed\n");
        return -1;
    }
    memset(buf, USB_NUM_BB, buf_size);  

    ret = gs_acm_cdev_write_base(port, buf, buf_size, true);

    kfree(buf);    

    return ret;
}

