/*
 * cshell.c -- balong cshell driver
 *
 * Copyright (C) 2012 Huawei Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

/*******************************************************************/
/*                                              ͷ�ļ�                                              */
/*******************************************************************/
#include <linux/module.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/kallsyms.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/vmalloc.h>
#include <osl_spinlock.h>
#include <osl_bio.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <bsp_nvim.h>
#include <bsp_shared_ddr.h>
#include <bsp_reset.h>
#include <osl_sem.h>
#include "cshell.h"
#include "bsp_acm.h"
#include "drv_acm.h"
#include "bsp_usb.h"
#include "bsp_icc.h"
#include "hi_uart.h"
#include "cshell_logger.h"

#if (FEATURE_ON == MBB_USB_SECURITY)
#include "comm_nv_def.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern s32 dialup_hsuart_send(u8 * pucSrcAddr, u32 u32TransLength);
int send_cmd_ccore(char* func_name, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6);
int cshell_get_bit(int num_from_zero);
/*******************************************************************************/
/*                                                       ��������              */
/*******************************************************************************/
cshell_ctx_t             g_cshell_ctx        = {0};
struct cshell_debug_log  cshell_log          = {0};

/*******************************************************************************/
/*                                                       ��������              */
/*******************************************************************************/
/*lint --e{119, 527, 629, 716} */


int cshell_debug_show(void)
{
	printk("cshell open status: %X\n", g_cshell_ctx.acshell_permit);
	printk("cshell suspend: %X\n", g_cshell_ctx.ccshell_work_flg);
	printk("cshell bluetooth enable:%d\n", cshell_get_bit(USB_CSHELL));
	printk("cshell file_node enable:%d\n", cshell_get_bit(FILE_CSHELL));
	printk("cshell auart enable:%d\n", cshell_get_bit(AUART_CSHELL));
	printk("cshell icc_chan_opened:%d\n", g_cshell_ctx.icc_chan_opened);
	printk("cshell icc_channel_id:%d\n", g_cshell_ctx.icc_channel_id);
	printk("cshell acm_channel_id:%d\n", g_cshell_ctx.acm_channel_id);
	printk("cshell cshell_acm_fd:%d\n", g_cshell_ctx.cshell_acm_fd);
	printk("cshell cshell_send_index:%d\n", g_cshell_ctx.cshell_send_index);
	printk("cshell usb_send_buf_r:%d\n", g_cshell_ctx.usb_send_buf_r);
	printk("cshell usb_send_buf_w:%d\n", g_cshell_ctx.usb_send_buf_w);
	printk("cshell send_mem_drop_times:%d\n", cshell_log.send_mem_drop_times);
	printk("cshell usb_buf_drop_times:%d\n", cshell_log.usb_buf_drop_times);
	printk("cshell bluetooth_send_cmd_times:%d\n", cshell_log.bluetooth_send_cmd_times);
	printk("cshell auart_send_cmd_times:%d\n", cshell_log.auart_send_cmd_times);
	return 0;
}

int cshell_recv_from_dial(u8 *buf, u32 len)
{
	int ret = 0;

	if(!buf || !len)
		return -1;
	ret = bsp_icc_send((u32)ICC_CPU_MODEM, (g_cshell_ctx.icc_channel_id << 16), (u8*)buf, (u32)len);
	return ret;
}

int cshell_enable(int val)
{
	int ret = 0;
	
	if(val >= (int)INVAL_CSHELL || val < 0)
	{
		printk("<cshell>:input param err. %d:USB_CSHELL, %d:FILE_CSHELL, %d:AUART_CSHELL\n",
			(int)USB_CSHELL,(int)FILE_CSHELL,(int)AUART_CSHELL);
		return -1;
	}
	(void)cshell_set_bit(val);

	if(!g_cshell_ctx.ccshell_work_flg)
	{
		printk("<cshell>: modem is being reseting\n");
		return 0;
	}

	ret = bsp_icc_send((u32)ICC_CPU_MODEM, (ICC_CHN_IFC << 16)|IFC_RECV_FUNC_CSHELL,
		&g_cshell_ctx.acshell_permit, sizeof(g_cshell_ctx.acshell_permit));
	if(ret != (int)sizeof(g_cshell_ctx.acshell_permit))
	{
		printk("<cshell>: fail to send permit flag to cp.\n");
		return ret;
	}
	return 0;
}

int cshell_disable(int val)
{
	int ret = 0;
	
	if(val >= (int)INVAL_CSHELL || val < 0)
	{
		printk("<cshell>:input param err. %d:USB_CSHELL, %d:FILE_CSHELL, %d:AUART_CSHELL\n",
			(int)USB_CSHELL,(int)FILE_CSHELL,(int)AUART_CSHELL);
		return -1;
	}
	(void)cshell_clear_bit(val);

	if(!g_cshell_ctx.ccshell_work_flg)
	{
		printk("<cshell>: modem is being reseting\n");
		return 0;
	}

	ret = bsp_icc_send((u32)ICC_CPU_MODEM, (ICC_CHN_IFC << 16)|IFC_RECV_FUNC_CSHELL,
		&g_cshell_ctx.acshell_permit, sizeof(g_cshell_ctx.acshell_permit));
	if(ret != (int)sizeof(g_cshell_ctx.acshell_permit))
	{
		printk("<cshell>: fail to send permit flag to cp.\n");
		return ret;
	}
	return 0;
}

int cshell_get_bit(int num_from_zero)
{
	return (0x1U << num_from_zero) & g_cshell_ctx.acshell_permit ? 1 : 0;
}

int cshell_set_bit(int num_from_zero)
{
	unsigned long flg = 0;

	if(num_from_zero >= CHAR_BIT_NUM)
	{
		printk("num_from_zero exceeds %d\n", CHAR_BIT_NUM);
		return -1;
	}
	spin_lock_irqsave(&g_cshell_ctx.cshell_spin_loc_permit, flg);
	g_cshell_ctx.acshell_permit |= (u8)(1U << num_from_zero);
	spin_unlock_irqrestore(&g_cshell_ctx.cshell_spin_loc_permit, flg);
	return 0;
}

int cshell_clear_bit(int num_from_zero)
{
	unsigned long flg = 0;

	if(num_from_zero >= CHAR_BIT_NUM)
	{
		printk("num_from_zero exceeds %d\n", CHAR_BIT_NUM);
		return -1;
	}
	spin_lock_irqsave(&g_cshell_ctx.cshell_spin_loc_permit, flg);
	g_cshell_ctx.acshell_permit &= ~(1U << num_from_zero);
	spin_unlock_irqrestore(&g_cshell_ctx.cshell_spin_loc_permit, flg);
	return 0;
}

int send_cmd_ccore(char* func_name, int arg1, int arg2, int arg3, int arg4, int arg5, int arg6)
{
	char* cptr           = (char*)&g_cshell_ctx.recv_cmd_str[0];
	int   ret            = 0;

	if((0 == cshell_get_bit(AUART_CSHELL)) || !g_cshell_ctx.ccshell_work_flg || (0 == g_cshell_ctx.valid))
	{
		printk("AUART_CSHELL %d  ccshell_work_flg :%d\n", g_cshell_ctx.acshell_permit, g_cshell_ctx.ccshell_work_flg);
		return CSHELL_ERROR;
	}
	if((strlen(func_name) - 1) >  (RECV_CMD_STR_LEN - 6 * 9 - 1 - 2))
	{
		printk("[ACSHELL] func_name is too long\n");
		return CSHELL_ERROR;
	}
	snprintf(cptr, RECV_CMD_STR_LEN, "%s 0x%X,0x%X,0x%X,0x%X,0x%X,0x%X\r\n", func_name + 1, arg1, arg2, arg3, arg4, arg5, arg6);
	ret = bsp_icc_send((u32)ICC_CPU_MODEM, (g_cshell_ctx.icc_channel_id << 16), (u8*)cptr, (u32)strlen(cptr));
	cshell_log.auart_send_cmd_times += 1;

	return ret;
}

int cshell_mode_reset_cb(DRV_RESET_CALLCBFUN_MOMENT eparam, int usrdata)
{
	int ret = 0;
	
	switch(eparam)
	{
		case DRV_RESET_CALLCBFUN_RESET_BEFORE:
			g_cshell_ctx.ccshell_work_flg = 0;
			break;
		case DRV_RESET_CALLCBFUN_RESET_AFTER:
			g_cshell_ctx.ccshell_work_flg = 1;
			if(g_cshell_ctx.acshell_permit)
			{
				ret = bsp_icc_send((u32)ICC_CPU_MODEM, (ICC_CHN_IFC << 16)|IFC_RECV_FUNC_CSHELL, &g_cshell_ctx.acshell_permit, 1);
				if(ret <= 0)
				{
					printk("<cshell> fail to send permit flg\n");
					g_cshell_ctx.reset_infor_fail_times++;
				}
				else
				{
					ret = 0;
				}
			}
			break;
		default:
			break;
	}
	return ret;
}
/*******************************************************************************
* �� �� ��      : cshell_icc_uninit
*
* ��������  : cshell iccͨ��ȥ��ʼ���ӿ�
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ      : ��
*
*******************************************************************************/
static void cshell_icc_uninit(void)
{
    cshell_ctx_t *cshell_ctx = &g_cshell_ctx;
    u32 i = 0;

    printk("A:cshell_icc_uninit...\n");

    for (i = 0; i < CSHELL_SEND_BUFFER_NUM; i++)
    {
        if (cshell_ctx->send_mem[i].buf)
        {
            kfree(cshell_ctx->send_mem[i].buf);
            cshell_ctx->send_mem[i].buf = NULL;
        }
    }

    if (cshell_ctx->recv_mem.buf)
    {
        kfree(cshell_ctx->recv_mem.buf);
        cshell_ctx->recv_mem.buf = NULL;
    }

    if (cshell_ctx->send_buf)
    {
        kfree(cshell_ctx->send_buf);
        cshell_ctx->send_buf = NULL;
    }

    if (cshell_ctx->recv_buf)
    {
        kfree(cshell_ctx->recv_buf);
        cshell_ctx->recv_buf = NULL;
    }

    if (cshell_ctx->icc_chan_opened)
    {
        cshell_ctx->icc_chan_opened = 0;
    }

    cshell_ctx->icc_channel_id = 0xFFFF;
    cshell_ctx->icc_chan_opened = 0;
}

/*******************************************************************************
* �� �� ��      : cshell_icc_init
*
* ��������  : cshell iccͨ����ʼ���ӿ�
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ      : CSHELL_ERROR-��ʼ��ʧ�ܣ�BSP_OK-��ʼ���ɹ�
*
*******************************************************************************/
static int cshell_icc_init(void)
{
    int i = 0;
    cshell_ctx_t *cshell_ctx = &g_cshell_ctx;


    printk("A:cshell_icc_init start \n");

    for (i = 0; i < CSHELL_SEND_BUFFER_NUM; i++)
    {
        /* ��ʼ��Send Buffer */
        cshell_ctx->send_mem[i].buf_size  = 0;
        cshell_ctx->send_mem[i].buf_valid = 1;
        cshell_ctx->send_mem[i].index     = (u32)i;
        cshell_ctx->send_mem[i].buf       = (uint8_t *)kmalloc(CSHELL_BUFFER_SIZE, GFP_KERNEL);

        if (!cshell_ctx->send_mem[i].buf)
        {
            printk("A:cshell_icc_init malloc send mem fail \n");
            goto error;
        }

        memset(cshell_ctx->send_mem[i].buf, 0, CSHELL_BUFFER_SIZE);
        cshell_ctx->send_mem[i].next = &cshell_ctx->send_mem[(i + 1) % CSHELL_SEND_BUFFER_NUM];
    }

    cshell_ctx->send_buf = (uint8_t *)kmalloc(CSHELL_BUFFER_SIZE, GFP_KERNEL);
    if (!cshell_ctx->send_buf)
    {
        printk("A:cshell_icc_init malloc send_buf fail \n");
        goto error;
    }
    memset(cshell_ctx->send_buf, 0, CSHELL_BUFFER_SIZE);

    cshell_ctx->cshell_send_index = 0;

    /* ��ʼ��Recv Buffer */
    cshell_ctx->recv_mem.buf_size  = 0;
    cshell_ctx->recv_mem.buf_valid = 1;
    cshell_ctx->recv_mem.index     = 0;
    cshell_ctx->recv_mem.next      = NULL;
    cshell_ctx->recv_mem.buf = (uint8_t *)kmalloc(CSHELL_BUFFER_SIZE, GFP_KERNEL);
    if (!cshell_ctx->recv_mem.buf)
    {
        printk("A:cshell_icc_init malloc recv_mem fail \n");
        goto error;
    }
    memset(cshell_ctx->recv_mem.buf, 0, CSHELL_BUFFER_SIZE);

    cshell_ctx->recv_buf = (uint8_t *)kmalloc(CSHELL_BUFFER_SIZE, GFP_KERNEL);
    if (!cshell_ctx->recv_buf)
    {
        printk("A:cshell_icc_init malloc recv buf fail \n");
        goto error;
    }
    memset(cshell_ctx->recv_buf, 0, CSHELL_BUFFER_SIZE);

    printk("A:cshell_icc_init Open icc channel[%d]\n", CSHELL_ICC_CHANNEL_ID);

    cshell_ctx->icc_chan_opened = 1;
    cshell_ctx->icc_channel_id  = ICC_CHN_CSHELL;
    cshell_ctx->acm_channel_id  = ACM_CHN_CSHELL;

    printk("A:cshell_icc_init ok\n");
    return CSHELL_OK;

error:
    cshell_icc_uninit();
    printk("A:cshell_icc_init fail...\n");
    return CSHELL_ERROR;
}

/*******************************************************************************
* �� �� ��      : cshell_uninit
*
* ��������  : cshellȥ��ʼ���ӿ�
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ      : ��
*
*******************************************************************************/
static void cshell_uninit(void)
{
    cshell_ctx_t *cshell_ctx = &g_cshell_ctx;

    printk("A:cshell_uninit...\n");

    if (!IS_ERR(cshell_ctx->send_task))
    {
        kthread_stop(cshell_ctx->send_task);
    }

    if (!IS_ERR(cshell_ctx->recv_task))
    {
        kthread_stop(cshell_ctx->recv_task);
    }
    kfree(cshell_ctx->usb_send_buf);
    cshell_ctx->usb_send_buf = NULL;
    if (!IS_ERR(cshell_ctx->send_task_usb))
    {
        kthread_stop(cshell_ctx->send_task_usb);
    }

    (void)bsp_acm_ioctl(cshell_ctx->cshell_acm_fd, ACM_IOCTL_SET_READ_CB, NULL);
    (void)bsp_acm_close(cshell_ctx->cshell_acm_fd);

    cshell_icc_uninit();

    cshell_ctx->valid = 0;

}

/*******************************************************************************
* �� �� ��      : cshell_recv_thread
*
* ��������  : ���մ�USB�������������ݣ����� A����C�˷����߳�
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ      : ��
*
*******************************************************************************/
/*lint --e{713}*/
static int cshell_recv_thread(void *arg)
{
    cshell_ctx_t *cshell_ctx = &g_cshell_ctx;

    u32 write_size      = 0;
    u32 free_buf_size   = 0;
    int acm_ret         = -1;
    int icc_ret         = CSHELL_OK;
    ACM_WR_ASYNC_INFO acm_wt_info = {0};

    printk("A:cshell_recv_thread enter\n");

    /* coverity[no_escape] */
    while (1)
    {
        /* �ȴ��ź����ͷ�*/
        osl_sem_down(&(cshell_ctx->cshell_recv_sem));

        /* ��buffer�������ݻ��߷���buffer����ʣ������ */
        while (((acm_ret = bsp_acm_ioctl(cshell_ctx->cshell_acm_fd, (u32)ACM_IOCTL_GET_RD_BUFF, &acm_wt_info)) == 0) ||
               (cshell_ctx->recv_mem.buf_size))
        {
            if (0 == acm_ret)
            {
                /* ��ȡʣ��buffer���� */
                free_buf_size = CSHELL_BUFFER_SIZE - cshell_ctx->recv_mem.buf_size;

                /* ��ȡ��д��buffer�����ݳ��ȣ����ಿ�ֶ��� */
                if (free_buf_size < (u32)acm_wt_info.u32Size)
                {
                    write_size = free_buf_size;
                }
                else
                {
                    write_size = acm_wt_info.u32Size;
                }

                /* �����ݿ���������buffer������buffer���� */
                memcpy(cshell_ctx->recv_mem.buf + cshell_ctx->recv_mem.buf_size, acm_wt_info.pBuffer, write_size);

                cshell_ctx->recv_mem.buf_size += write_size;
            }

            if ((!cshell_ctx->icc_chan_opened) || (0 == g_cshell_ctx.ccshell_work_flg) || !cshell_get_bit(USB_CSHELL))
            {
                printk("A:icc channel is [%d], ccshell_work_flg is [%d]  cshell_get_bit(USB_CSHELL):%d\n",
                    cshell_ctx->icc_chan_opened, g_cshell_ctx.ccshell_work_flg, cshell_get_bit(USB_CSHELL));
                if (0 == acm_ret)
                {
                    (void)bsp_acm_ioctl(cshell_ctx->cshell_acm_fd, ACM_IOCTL_RETURN_BUFF, &acm_wt_info);
                }
                break;
            }

            /* ������ͨ��ICC ����C�� */
            icc_ret = (int)bsp_icc_send((u32)ICC_CPU_MODEM, (cshell_ctx->icc_channel_id<<16), cshell_ctx->recv_mem.buf, cshell_ctx->recv_mem.buf_size);

            if((icc_ret > (int)cshell_ctx->recv_mem.buf_size) || (icc_ret < 0))
            {
                printk("A:icc send data to c-core fail with channel id [%d]\n", cshell_ctx->icc_channel_id);
            }
            else if(icc_ret < (int)cshell_ctx->recv_mem.buf_size)
            {
                cshell_ctx->recv_mem.buf_size -= (u32)icc_ret;
                memcpy(cshell_ctx->recv_buf, cshell_ctx->recv_mem.buf+icc_ret,(cshell_ctx->recv_mem.buf_size));
                memcpy(cshell_ctx->recv_mem.buf, cshell_ctx->recv_buf, (cshell_ctx->recv_mem.buf_size));
            }
            else
            {
                cshell_ctx->recv_mem.buf_size -= (u32)icc_ret;
            }

            if (0 == acm_ret)
            {
                (void)bsp_acm_ioctl(cshell_ctx->cshell_acm_fd, ACM_IOCTL_RETURN_BUFF, &acm_wt_info);
            }
			cshell_log.bluetooth_send_cmd_times += 1;
        }
    }
    return 0;
}

int cshell_usb_send_thread(void *arg)
{
    cshell_ctx_t*        cshell_ctx      = &g_cshell_ctx;
    s32                  ret             = CSHELL_OK;
    u32                  r_pos           = 0;
    u32                  w_pos           = 0;

    printk("A:cshell_usb_send_thread enter\n");

    /* coverity[no_escape] */
    while (1)
    {
        osl_sem_down(&(cshell_ctx->cshell_usb_send_sem));

        while ((cshell_ctx->usb_send_buf_r != cshell_ctx->usb_send_buf_w) && cshell_ctx->cshell_acm_fd)
        {
            r_pos = cshell_ctx->usb_send_buf_r;
            w_pos = cshell_ctx->usb_send_buf_w;
            ret = bsp_acm_write(cshell_ctx->cshell_acm_fd, (uint8_t *)cshell_ctx->usb_send_buf + r_pos,
                r_pos < w_pos ? w_pos - r_pos : cshell_ctx->usb_send_buf_size - r_pos);
            if(ret >= 0)
            {
                cshell_ctx->usb_send_buf_r += (u32)ret;
                cshell_ctx->usb_send_buf_r %= cshell_ctx->usb_send_buf_size;
            }else{
                printk("A: cshell_send_thread send data to acm fail ret [%d]\n", ret);
                break;
            }
        }
    }
    return 0;
}

void write_data_usb_buf(cshell_mem_handle_t* cshell_send_mem)
{
	cshell_ctx_t*    cshell_ctx      = &g_cshell_ctx;
	u32              r_pos           = cshell_ctx->usb_send_buf_r;
	u32              w_pos           = cshell_ctx->usb_send_buf_w;
	u32              remaining_space = 0;
	u32              min_size        = 0;
	u32              log_len         = cshell_send_mem->buf_size;

	if(r_pos == w_pos)
	{
		remaining_space = cshell_ctx->usb_send_buf_size - 1;
	}else{
		remaining_space = (r_pos - w_pos + cshell_ctx->usb_send_buf_size) % cshell_ctx->usb_send_buf_size - 1;
	}
	if(remaining_space < log_len)
	{
		up(&(cshell_ctx->cshell_usb_send_sem));
		cshell_log.usb_buf_drop_times += 1;
		return;
	}
	if(r_pos > w_pos)
	{
		memcpy(cshell_ctx->usb_send_buf + w_pos, cshell_send_mem->buf, log_len);
	}else{
		min_size = log_len < (cshell_ctx->usb_send_buf_size - w_pos) ? log_len : (cshell_ctx->usb_send_buf_size - w_pos);
		memcpy(cshell_ctx->usb_send_buf + w_pos, cshell_send_mem->buf, min_size);
		log_len -= min_size;
		memcpy(cshell_ctx->usb_send_buf, cshell_send_mem->buf + min_size, log_len);
	}
	cshell_ctx->usb_send_buf_w += cshell_send_mem->buf_size;
	cshell_ctx->usb_send_buf_w %= cshell_ctx->usb_send_buf_size;

	up(&(cshell_ctx->cshell_usb_send_sem));
}

void print_to_auart(cshell_mem_handle_t* cshell_send_mem)
{
    int                  print_off       = 0;
    int                  ln_pos          = 0;

    while(print_off < (int)cshell_send_mem->buf_size)
    {
        ln_pos = 0;
        while(((print_off + ln_pos) < (int)cshell_send_mem->buf_size) && ('\n' != cshell_send_mem->buf[print_off + ln_pos]))
        {
            ln_pos++;
        }
        cshell_send_mem->buf[print_off + ln_pos] = 0;
        printk("[C]%s\n", (char*)(cshell_send_mem->buf + print_off));
        print_off += ln_pos + 1;
    }
}

/*******************************************************************************
* �� �� ��      : cshell_send_thread
*
* ��������  : cshell A����PC�˷����߳�
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��
*
*******************************************************************************/
int cshell_send_thread(void *arg)
{
    cshell_ctx_t*        cshell_ctx      = &g_cshell_ctx;
    cshell_mem_handle_t* cshell_send_mem = &cshell_ctx->send_mem[0];
    int                  ret             = (int) CSHELL_OK;


    printk("A:cshell_send_thread enter\n");

    /* coverity[no_escape] */
    while (1)
    {
        osl_sem_down(&(cshell_ctx->cshell_send_sem));
        /* ��buffer�������ݻ��߷���buffer����ʣ������ */
        while ((cshell_send_mem->buf_valid) && (cshell_send_mem->buf_size))
        {
            cshell_send_mem->buf_valid = 0;

            /* ���ݸ��Ƶ�USB��ӡbuffer�� */
            if(cshell_get_bit(USB_CSHELL) && (cshell_ctx->cshell_acm_fd != 0))
            {
                write_data_usb_buf(cshell_send_mem);
            }
            (void)a_cshell_write((int)(cshell_send_mem->buf_size), cshell_send_mem->buf,(int)(cshell_send_mem->buf_size), 1);
            if(cshell_get_bit(AUART_CSHELL))
            {
                print_to_auart(cshell_send_mem);
            }
			if(cshell_get_bit(DIAL_CSHELL))
			{
				(void)dialup_hsuart_send(cshell_send_mem->buf, (u32)cshell_send_mem->buf_size);/* ��ӡ���� */
			}

            ret = (int)cshell_send_mem->buf_size;
            if(ret >= 0)
            {
                /* ��ǰ�����bufferΪ����д��buffer����ʼʹ����һ��buffer */
                if (cshell_ctx->cshell_send_index == cshell_send_mem->index)
                {
                    /* �����ڴ˼������� */
                    cshell_ctx->cshell_send_index = cshell_send_mem->next->index;
                }
                cshell_send_mem->buf_size = 0;
                cshell_send_mem->buf_valid = 1;
                cshell_send_mem = cshell_send_mem->next;
            }
            else
            {
                cshell_send_mem->buf_valid = 1;
            }
        }
    }
}
/*******************************************************************************
* �� �� ��      : cshell_shell_recv_cb
*
* ��������  : ����shell�ڽ��ջص��ӿڣ�֪ͨ�����߳���C��д����
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��
*
*******************************************************************************/
void cshell_shell_recv_cb(void)
{
    cshell_ctx_t *cshell_ctx = &g_cshell_ctx;

    if ((cshell_ctx->valid))
    {
        up(&(cshell_ctx->cshell_recv_sem));
    }
}


/*******************************************************************************
* �� �� ��  : cshell_buf_valid_check
*
* ��������  : ����ڴ���Ƿ�����ʹ����
*
* �������  : cshell_mem: �������ڴ�
*             len:���ݴ�С
*
* �������  : ��
*
* �� �� ֵ  : 1-δʹ�ã�0-��ʹ��
*
*******************************************************************************/
u32 cshell_buf_valid_check(cshell_mem_handle_t *cshell_mem, u32 len)
{
    u32 free_buf_size = 0;

    if (!cshell_mem->buf_valid)
    {
        return 0;
    }

    free_buf_size = CSHELL_BUFFER_SIZE - cshell_mem->buf_size;
    if (free_buf_size < len)
    {
        return 0;
    }

    return 1;
}


/*******************************************************************************
* �� �� ��      : cshell_event_cb
*
* ��������  : cshell�¼��ص����ݲ�����
*
* �������  : id        : iccͨ��
*                           event   :�¼�����
*                           Param   :���ݵĲ���
*
* �������  : ��
*
* �� �� ֵ      : 0
*
*******************************************************************************/
u32 cshell_event_cb(u32 id, u32 event, void *Param)
{
    printk("A:chan[%d], event:%d\n", id, event);
    return 0;
}

/*******************************************************************************
* �� �� ��      : cshell_write_cb
*
* ��������  : cshellд�ص�������֪ͨд�߳̿�ʼ��C��д����
*
* �������  : id: iccͨ��
*
* �������  : ��
*
* �� �� ֵ      : 0
*
*******************************************************************************/
u32 cshell_write_cb(u32 id)
{
    cshell_ctx_t *cshell_ctx = &g_cshell_ctx;

    printk("A:chan[%d]\n", id);

    if ((cshell_ctx->valid))
    {
        up(&(cshell_ctx->cshell_recv_sem));
    }

    return 0;
}

/*******************************************************************************
* �� �� ��      :   cshell_read_cb
*
* ��������  :   cshell���ص������ڴ�C�˶�ȡ����
*
* �������  :   id: iccͨ��
*                           len:���ݴ�С
*
* �������  : ��
*
* �� �� ֵ      : 1-��ʧ�ܣ�0-���ɹ�
*
*******************************************************************************/
static int cshell_read_cb(u32 channel_id , u32 len, void* context)
{
    cshell_ctx_t *cshell_ctx = &g_cshell_ctx;

    cshell_mem_handle_t *cshell_send_mem = NULL;
    int read_size = 0;

    if (!cshell_ctx->valid)
    {
        printk("A: [Warning] cshell send_buf has not allocated\n");
        return CSHELL_ERROR;
    }

    memset(cshell_ctx->send_buf, 0, CSHELL_BUFFER_SIZE);

    read_size = (int)bsp_icc_read((cshell_ctx->icc_channel_id << 16), cshell_ctx->send_buf, len);
    if((read_size > (s32)len) || (read_size < 0))
    {
        printk("A:cshell_read_cb read icc len[%d] data from c-core chan[0x%x] fail\n", read_size, channel_id);
        return CSHELL_ERROR;
    }

    cshell_send_mem = &cshell_ctx->send_mem[cshell_ctx->cshell_send_index];

    if (!cshell_buf_valid_check(cshell_send_mem, (u32)read_size))
    {
        cshell_send_mem = cshell_send_mem->next;
        if (!cshell_buf_valid_check(cshell_send_mem, (u32)read_size))
        {
            //printk("A:cshell buffer full\n");
            cshell_log.send_mem_drop_times += 1;
            return CSHELL_ERROR;
        }
    }

    memcpy(cshell_send_mem->buf + cshell_send_mem->buf_size, cshell_ctx->send_buf, (u32)read_size);
    cshell_send_mem->buf_size += (u32)read_size;
    cshell_ctx->cshell_send_index = cshell_send_mem->index;

    if (cshell_ctx->valid)
    {
        up(&(cshell_ctx->cshell_send_sem));
    }

    return CSHELL_OK;
}

/*******************************************************************************
* �� �� ��      : cshell_udi_open_cb
*
* ��������  : USB����֪ͨ�ص�
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ      : ��
*
*******************************************************************************/
void cshell_udi_open_cb(void)
{
    /*lint --e{550} */
    cshell_ctx_t *cshell_ctx = &g_cshell_ctx;
    s32 cshell_udi_handle ;
    int  ret = 0;

    printk("A:cshell_udi_open_cb acm plugin: [0x%x]\n", cshell_ctx->cshell_acm_fd);

    /* ע��, cshell_acm_fd ��ָ��, �������� */
    if (cshell_ctx->cshell_acm_fd > 0)
    {
        printk("A:cshell_udi_open_cb acm is already opened:[0x%x]\n", cshell_ctx->cshell_acm_fd);
        return;
    }

    cshell_udi_handle = bsp_acm_open(UDI_USB_ACM_SHELL);
    if (cshell_udi_handle == 0)
    {
        printk("A:cshell_udi_open_cb acm open fail: [0x%x]\n", cshell_udi_handle);
        return;
    }
    cshell_ctx->cshell_acm_fd = (s32)cshell_udi_handle;

    ret = bsp_acm_ioctl(cshell_ctx->cshell_acm_fd, ACM_IOCTL_SET_READ_CB, cshell_shell_recv_cb);
    if (CSHELL_OK != ret)
    {
        printk("A:cshell_udi_open_cb cb register fail: [0x%x]\n", ret);
        return;
    }
    printk("A:cshell_udi_open_cb cb register success: [0x%x],fd[0x%x]\n", ret, cshell_ctx->cshell_acm_fd);

    (void)cshell_set_bit(USB_CSHELL);
    if(g_cshell_ctx.ccshell_work_flg)
    {
        ret = (int)bsp_icc_send((u32)ICC_CPU_MODEM, (ICC_CHN_IFC << 16)|IFC_RECV_FUNC_CSHELL, &cshell_ctx->acshell_permit, 1);
        if(ret <= 0)
        {
            printk("A:fail to send open flag to c-core\n");
            return;
        }
    }else{
        printk("[ACSHELL] modem is being reset\n");
    }
}

/*******************************************************************************
* �� �� ��  : cshell_udi_close_cb
*
* ��������  : USB�γ�֪ͨ�ص�
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��
*
*******************************************************************************/
void cshell_udi_close_cb(void)
{
    /*lint --e{550} */
    cshell_ctx_t *cshell_ctx = &g_cshell_ctx;
    int ret = 0;

    printk("A:cshell_udi_close_cb acm unplug: [0x%x]\n", cshell_ctx->cshell_acm_fd);

    /* ע��, cshell_acm_fd ��ָ��, �������� */
    if (cshell_ctx->cshell_acm_fd)
    {
        bsp_acm_ioctl(cshell_ctx->cshell_acm_fd, ACM_IOCTL_SET_READ_CB, NULL);

        ret = bsp_acm_close(cshell_ctx->cshell_acm_fd);
        if (CSHELL_OK != ret)
        {
            printk("A:cshell_init cb register fail: [0x%x]\n", ret);
            return;
        }
        cshell_ctx->cshell_acm_fd = 0;
    }
    (void)cshell_clear_bit(USB_CSHELL);
    if(g_cshell_ctx.ccshell_work_flg)
    {
        ret = (int)bsp_icc_send((u32)ICC_CPU_MODEM, (ICC_CHN_IFC << 16)|IFC_RECV_FUNC_CSHELL, &cshell_ctx->acshell_permit, 1);
        if(ret <= 0)
        {
            printk("A:fail to send close flag to c-core\n");
            return;
        }
    }else{
        printk("[ACSHELL] modem is being reset\n");
    }
}


/*******************************************************************************
* �� �� ��      : cshell_init
*
* ��������  : cshell��ʼ���ӿ�
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ      : CSHELL_ERROR-��ʼ��ʧ�ܣ�CSHELL_OK-��ʼ���ɹ�
*
*******************************************************************************/
int cshell_init(void)
{
    cshell_ctx_t *cshell_ctx = &g_cshell_ctx;
    DRV_UART_SHELL_FLAG uartcshell_nv = {.extendedbits = 0};
    u32 channel_id = 0;

#if (FEATURE_ON == MBB_USB_SECURITY)
    NV_HUAWEI_USB_SECURITY_SHELL usb_security = {0};
    int ret = 1;
    /* ��ȡshell����NV����ǰSHELL�ĳ�ʼ����USB֮ǰ�����NV�Ķ�ȡ��cshellģ������� */
    ret = NVM_Read(NV_ID_DRV_USB_SECURITY_FLAG, &usb_security, sizeof(NV_HUAWEI_USB_SECURITY_SHELL));
    if(0 != ret)
    {
        /* NV��ȡʧ�ܣ�Ĭ�Ϲر� */
        usb_security.shell_enable = 0;
        pr_err("cshell read nv fail\n");
    }
    if(1 != usb_security.shell_enable)
    {
        pr_err("cshell cann't be init for security\n");
        return CSHELL_ERROR;
    }
#endif /*MBB_USB_SECURITY*/

    printk("A:cshell_init start \n");

    cshell_ctx->ccshell_work_flg = 1;
    cshell_ctx->cshell_acm_fd = 0;
    cshell_ctx->usb_send_buf = (u8*)kmalloc(CSHELL_BUFFER_SIZE, GFP_KERNEL);
    if(!cshell_ctx->usb_send_buf)
    {
        printk("[ACSHELL]kmalloc fails line:%d", __LINE__);
        goto error;
    }
    cshell_ctx->usb_send_buf_size = CSHELL_BUFFER_SIZE;
    cshell_ctx->usb_send_buf_r = 0;
    cshell_ctx->usb_send_buf_w = 0;

    cshell_icc_init();

    sema_init(&(cshell_ctx->cshell_send_sem), 0);
    sema_init(&(cshell_ctx->cshell_recv_sem), 0);
    sema_init(&(cshell_ctx->cshell_usb_send_sem), 0);
    spin_lock_init(&g_cshell_ctx.cshell_spin_loc_permit);

    if(bsp_nvm_read(NV_ID_DRV_UART_SHELL_FLAG, (u8 *)&uartcshell_nv, sizeof(DRV_UART_SHELL_FLAG)))
    {
        printk("[A:CSHELL]:bsp_nvm_read fails  line:%d uartcshell_nv.cshell_to_auart:%d\n", __LINE__, uartcshell_nv.extendedbits);
    }
    if(uartcshell_nv.extendedbits & 0x1U)
    {
        cshell_set_bit(AUART_CSHELL);
    }else{
        cshell_clear_bit(AUART_CSHELL);
    }

    printk("A :icc channel[%d] open sucess \n", ICC_CHN_CSHELL);

    channel_id = cshell_ctx->icc_channel_id << 16;
    if(bsp_icc_event_register(channel_id ,cshell_read_cb, NULL, NULL, NULL))
        printk(KERN_ERR "A:CSHELL bsp_icc_event_register fail");

    cshell_ctx->send_task = kthread_run(cshell_send_thread, NULL, "cshell_send_thread");
    if (IS_ERR(cshell_ctx->send_task))
    {
        printk("A:cshell_init send thread create fail\n");
        goto error;
    }
    cshell_ctx->recv_task = kthread_run(cshell_recv_thread, NULL, "cshell_recv_thread");
    if (IS_ERR(cshell_ctx->recv_task))
    {
        printk("A:cshell_init recv thread create fail\n");
        goto error;
    }
    cshell_ctx->send_task_usb = kthread_run(cshell_usb_send_thread, NULL, "cshell_usb_send_thread");
    if (IS_ERR(cshell_ctx->recv_task))
    {
        printk("[ACSHELL] fail to create cshell_usb_send_thread\n");
        goto error;
    }

    printk("A:cshell_init udi cb register\n");

    /* ע��USB����ص�����*/
    bsp_usb_register_enablecb(cshell_udi_open_cb);
    bsp_usb_register_disablecb(cshell_udi_close_cb);

    cshell_ctx->valid = 1;

    printk("A:cshell_init ok\n");
    return CSHELL_OK;

error:
    cshell_uninit();
    printk("A:cshell_init fail...\n");
    return CSHELL_ERROR;
}

//#ifndef OS_ANDROID_USE_K3V3_KERNEL
module_init(cshell_init);
//#endif

#ifdef __cplusplus
}
#endif


