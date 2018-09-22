
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/module.h>
#include <linux/export.h>
#include <linux/delay.h>
#include <linux/fcntl.h>
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>
#include <linux/wakelock.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <asm/mach/irq.h>
#include <linux/wait.h>

#include "usb_config.h"
#include "usb_debug.h"
#ifdef MBB_USB_UNITARY_Q
#include "hw_pnp.h"
#include "hw_pnp_api.h"
#else
#include "usb_vendor.h"
#include "mbb_config.h"
#include "product_config.h"
#endif
#include "usb_charger_manager.h"
#include <linux/mlog_lib.h>


#include "usb_hotplug.h"

#include "usb_otg_dev_detect.h"

#if (FEATURE_ON == MBB_FEATURE_GATEWAY)
#ifdef CUSTOM_LIVEBOX_B2C
#include "bsp_sram.h"
#include "drv_om.h"
#endif
#endif

#define USB_DETECT_DELAY        200/*USB �жϷ����жϼ����ʱ*/
typedef  unsigned char      boolean;
extern USB_INT recv_vbus_on_intr;
/*�γ��������ƣ��γ�ʱ�ж��Ƿ����״̬��ѡ���Ƿ����*/
static struct timer_list g_wake_unlock_timer ;


#if(FEATURE_ON == MBB_CHG_BQ27510)
extern  void bq27510_sync_coulupdate_port_control(void);
#endif

/*wake unlock����ʱ����Ĭ��3s*/
static USB_INT g_wake_unlockt_loop = 3000;
#if(FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
#include "hi_gpio.h"
#include <linux/netlink.h>
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
extern int extchg_set_charge_enable(boolean enable);
extern int usb_direction_flag_set(boolean flag);
#endif
//#define GPIO_USB_SELECT  GPIO_SLEEP_4_10
//#define GPIO_USB_ID      GPIO_SLEEP_4_23
#if(FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
#if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
/*����������E5771S_852������GPIO_USB_SELECTΪ�ߵ�ƽʱ������A�ڣ�Ϊ�͵�ƽʱ������M��*/
#define GPIO_SWITCH_A_LEVEL       1  /*  USB���л�A�ں�M�ڵĹܽŵ�ƽ���������ɾ��U�̹��ܣ����Ʒ��͹ܽ�����ɾ�� */
#define GPIO_SWITCH_M_LEVEL       0
#else
/*������������GPIO_USB_SELECTΪ�͵�ƽʱ������A�ڣ�Ϊ�ߵ�ƽʱ������M��*/
#define GPIO_SWITCH_A_LEVEL       0
#define GPIO_SWITCH_M_LEVEL       1
#endif
#define GPIO_LOW                0
#endif
#define USB_SELECT_DELAY 300
#define CHECK_UDISK_TIME 12000
extern int detect_udisk_flags;
static struct timer_list dwc_check_udisk_timer;
static USB_INT switch_flags = 1;
#endif

/*
 * usb adapter for charger
 */
typedef struct usb_hotplug_datamodel
{
    USB_INT charger_type;                                          /*USB�������*/
    USB_INT usb_status;                                              /*USB��ǰ״̬*/
    USB_INT usb_old_status;                                       /*USB�ϴ�״̬*/

    USB_INT usb_host_status;
    USB_INT usb_host_old_status;
    USB_INT usb_cradle_pmu_status;
    USB_INT usb_cradle_pmu_old_status;

    USB_INT usb_hotplug_state;                                  /*��¼USB���״ֻ̬�в�ζ����Ż���´�״̬*/
    USB_UINT stat_usb_insert;                            /*����ǰ�������*/
    USB_UINT stat_usb_insert_proc;                   /*������ ����ǰ�������*/
    USB_UINT stat_usb_insert_proc_end;          /*������ ����ɺ�������*/
    USB_ULONG stat_usb_insert_timestamp;                   /*����ʱ���*/
    USB_UINT stat_usb_enum_done;                  /*����ǰö�ټ���*/
    USB_UINT stat_usb_enum_done_proc;         /*��������ǰö�ټ���*/
    USB_UINT stat_usb_enum_done_proc_end; /*���������ö�ټ���*/
    USB_UINT stat_usb_remove;                         /*����ǰ�γ�����*/
    USB_UINT stat_usb_remove_proc;               /*��������ǰ�γ�����*/
    USB_UINT stat_usb_remove_proc_end;        /*���������γ�����*/
    USB_ULONG stat_usb_remove_timestamp;      /*�γ�ʱ���*/
    USB_UINT stat_usb_disable;
    USB_UINT stat_usb_disable_proc;
    USB_UINT stat_usb_disable_proc_end;
    USB_UINT stat_usb_no_need_notify;             /*��������*/
    USB_UINT stat_usb_perip_insert;                   /*HOST����ǰ�������*/
    USB_UINT stat_usb_perip_insert_proc;           /*HOST����ǰ����ǰ�������*/
    USB_UINT stat_usb_perip_insert_proc_end;  /*HOST����ǰ�����������*/
    USB_UINT stat_usb_perip_remove;                 /*HOST����ǰ�γ�����*/
    USB_UINT stat_usb_perip_remove_proc;        /*HOST��������ǰ�γ�����*/
    USB_UINT stat_usb_perip_remove_proc_end; /*HOST���������γ�����*/
    USB_UINT stat_usb_poweroff_fail;                   /*�ϵ�ʧ�ܼ���*/
    USB_UINT stat_usb_poweron_fail;                   /*�µ�ʧ�ܼ���*/

    USB_UINT delta_time;

    //unsigned stat_wait_cdev_created;
    struct workqueue_struct* usb_notify_wq;       /*USB work queue*/
    struct delayed_work usb_notify_wk;               /*USB work */
    struct delayed_work usb_notify_host_wk;      /*USB work for ��Ϊ����ʱ���U�̴��� */
    struct delayed_work usb_cradle_pmu_wk;     /*USB work for����ģʽʱPMU �жϵĴ��� */
#if(FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
    struct delayed_work dwc_check_udisk_wk;
#endif
    void* private;                                                    /*USB˽������ָ��*/
    struct mutex mutex;
} usb_hotplug_datamodel_t;

BLOCKING_NOTIFIER_HEAD(usb_notifier_list);/*lint !e34 !e110 !e156 !e651 !e43*/
static usb_hotplug_datamodel_t  g_usb_notifier_h;
static struct wake_lock g_dwc_wakelock;


/**ע���ⲿ�ӿں���**/
#ifdef MBB_USB_UNITARY_Q
USB_INT hw_usb_entry(USB_VOID)
{
    pnp_probe();
    return 0;
}
USB_VOID hw_usb_exit(USB_VOID)
{
    pnp_remove();
}

static usb_hotplug_hanlder_t usb_hotplug_ctx =
{
    .usb_poweroff_cb =  0x00,
    .usb_poweron_cb = 0x00,
    .usb_entry_cb =       hw_usb_entry,
    .usb_exit_cb =          hw_usb_exit,
    .usbid_proc_cb = 0x00,
    .usb_wait_enumdone_cb = 0x00,
    .usb_check_wireless_chg_cb = 0x00,
    .usb_wireless_chg_remove_cb = 0x00,
    .usb_notify_wq_extern = 0x00,/*��init������ֵ�����ڴ˳�ʼ��������C��׼���������*/
};

#else
static usb_hotplug_hanlder_t usb_hotplug_ctx =
{
    .usb_poweron_cb =                          power_on_dwc3_usb,
    .usb_poweroff_cb =                          power_off_dwc3_usb,
    .usb_entry_cb =                                usb_balong_init,
    .usb_exit_cb =                                   usb_balong_exit,
    .usbid_proc_cb =                               bsp_usb_usbid_proc,
    .usb_wait_enumdone_cb =               bsp_usb_wait_cdev_created,
    .usb_clear_enumdone_cb  =              bsp_usb_clear_last_cdev_name,
    .usb_check_wireless_chg_cb =          usb_chg_wireless_detect,
    .usb_wireless_chg_remove_cb =       usb_chg_wireless_remove,
    .usb_notify_wq_extern = 0x00,
};
#endif

/*****************************************************************
Parameters    :  USB_INT loop ��ʱ��ʱ��
Return        :    ��
Description   :  ����wake unlock�Ķ�ʱ��ʱ��
*****************************************************************/
USB_VOID usb_set_wake_unlockt_loop( USB_INT loop)
{
    DBG_T(MBB_HOTPLUG, "set wake_unlockt_loop to : %d\n", loop);
    g_wake_unlockt_loop = loop;
}

/*****************************************************************
Parameters    :  USB_INT action ��ζ���
Return        :    ��
Description   :  ֪ͨUSB����¼�
*****************************************************************/
void usb_broadcast_event(USB_INT action)
{
    blocking_notifier_call_chain(&usb_notifier_list, action, (void*)&g_usb_notifier_h.charger_type);
}

/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ֹͣUSB�Ĺ�������
*****************************************************************/
void usb_stop_work(struct delayed_work* wk )
{
    /*cancel_work_sync��ȡ����Ӧ��work������������
    work�Ѿ���������ôcancel_work_sync��������ֱ��
    work��ɲ�ȡ����Ӧ��work  */
    if (NULL != wk && delayed_work_pending(wk))
    {
        cancel_delayed_work(wk);
    }

}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ����USB�Ĺ�������
*****************************************************************/
void  usb_start_work(struct delayed_work* wk, USB_INT timeout)
{
    if (NULL != usb_hotplug_ctx.usb_notify_wq_extern)
    {
        if (NULL  != wk)
        {
            queue_delayed_work(usb_hotplug_ctx.usb_notify_wq_extern, wk, msecs_to_jiffies(timeout));
        }

    }
    else
    {
        if (NULL  != wk)
        {
            queue_delayed_work(g_usb_notifier_h.usb_notify_wq, wk, msecs_to_jiffies(timeout));
        }
    }
}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  USB������
*****************************************************************/
void bsp_usb_status_change(USB_INT status)
{
    USB_ULONG timeout = 0;

    DBG_T(MBB_HOTPLUG, "status %d\n",   status);
    switch (status)
    {
        case USB_BALONG_DEVICE_INSERT:
            timeout = USB_DETECT_DELAY;
            usb_wake_lock();
            g_usb_notifier_h.stat_usb_insert++;
            g_usb_notifier_h.stat_usb_insert_timestamp = jiffies;
            break;
        case USB_BALONG_DEVICE_REMOVE :
            mod_timer(&g_wake_unlock_timer, jiffies + msecs_to_jiffies(g_wake_unlockt_loop));
            timeout = USB_DETECT_DELAY;
            g_usb_notifier_h.stat_usb_remove++;
            g_usb_notifier_h.stat_usb_remove_timestamp = jiffies;
            break;
        case USB_BALONG_DEVICE_DISABLE:
            g_usb_notifier_h.stat_usb_disable++;
            break;
        case USB_BALONG_ENUM_DONE :
            g_usb_notifier_h.stat_usb_enum_done++;
            break;
        case USB_BALONG_PERIP_INSERT:
            timeout = USB_DETECT_DELAY;
            usb_wake_lock();
            g_usb_notifier_h.stat_usb_perip_insert++;
            break;
        case USB_BALONG_PERIP_REMOVE :
            mod_timer(&g_wake_unlock_timer, jiffies + msecs_to_jiffies(g_wake_unlockt_loop));
            timeout = USB_DETECT_DELAY;
            g_usb_notifier_h.stat_usb_perip_remove++;
            break;
        default:
            DBG_T(MBB_HOTPLUG, "error status:%d\n",   status);
    }

    /*��������*/
    /*����Ϊ����work u�̺�pc�ֿ�*/
    /*pmu�ڵ����ʱ��150ms �����쳣��ε�bug 200ms������Ϊ����*/
    if (USB_BALONG_PERIP_INSERT == status || USB_BALONG_PERIP_REMOVE == status)
    {
        /*��Ϊ����ʱ*/
        usb_stop_work(&g_usb_notifier_h.usb_notify_host_wk);
        usb_start_work(&g_usb_notifier_h.usb_notify_host_wk, timeout);
    }
    else
    {
        /*��Ϊ�豸ʱ*/
        usb_stop_work(&g_usb_notifier_h.usb_notify_wk);
        usb_start_work(&g_usb_notifier_h.usb_notify_wk, timeout);

    }

    g_usb_notifier_h.usb_status = status;

}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ����ӿڣ�USBע��work.
*****************************************************************/
USB_INT adp_usb_queue_delay_work(struct delayed_work* dwork, USB_ULONG delay)
{
    USB_INT ret = 0;

    if (NULL != usb_hotplug_ctx.usb_notify_wq_extern)
    {
        ret = queue_delayed_work(usb_hotplug_ctx.usb_notify_wq_extern,
                                 dwork, msecs_to_jiffies(delay));
    }
    else
    {
        ret = queue_delayed_work(g_usb_notifier_h.usb_notify_wq,
                                 dwork, msecs_to_jiffies(delay));
    }

    return ret;

}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  USB��ϵͳ��
*****************************************************************/
void usb_wake_lock()
{
    /*��e5�಻�ü���*/
#ifdef  USB_E5
    USB_ULONG flags = 0;
    local_irq_save(flags);
    wake_lock(&g_dwc_wakelock);
    local_irq_restore(flags);
#endif
}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  USBϵͳ����
*****************************************************************/
void usb_wake_unlock()
{
#ifdef USB_E5
    USB_ULONG flags = 0;
    local_irq_save(flags);
    wake_unlock(&g_dwc_wakelock);
    local_irq_restore(flags);
#endif
}

/**
 * usb_register_notify - register a notifier callback whenever a usb change happens
 * @nb: pointer to the notifier block for the callback events.
 *
 * These changes are either USB devices or busses being added or removed.
 */
void bsp_usb_register_notify(struct notifier_block* nb)
{
    blocking_notifier_chain_register(&usb_notifier_list, nb);
}

/**
 * usb_unregister_notify - unregister a notifier callback
 * @nb: pointer to the notifier block for the callback events.
 *
 * usb_register_notify() must have been previously called for this function
 * to work properly.
 */
void bsp_usb_unregister_notify(struct notifier_block* nb)
{
    blocking_notifier_chain_unregister(&usb_notifier_list, nb);
}


/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ��ȡusb֪ͨ�����
*****************************************************************/
void* usb_get_notifier_handle()
{
    return &usb_notifier_list;
}

/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ��ȡUSB vbus �Ƿ���λ״̬
*****************************************************************/
USB_INT usb_get_vbus_status(void)
{
    return recv_vbus_on_intr;
}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ����USB vbus �Ƿ���λ״̬
*****************************************************************/
USB_INT usb_set_vbus_status(USB_INT value)
{
    recv_vbus_on_intr = value;
    return 0;
}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ��ȡUSB vbus �Ƿ���λ״̬
*****************************************************************/
USB_INT usb_get_hotplug_status()
{
    return g_usb_notifier_h.usb_status;
}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ��ȡhostģʽUSB����
*****************************************************************/
USB_INT usb_get_hotplug_old_status()
{

    return g_usb_notifier_h.usb_host_status;

}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ��ȡ����ʱ���
*****************************************************************/
USB_ULONG usb_get_insert_timestamp()
{
    return g_usb_notifier_h.stat_usb_insert_timestamp;
}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ��ȡ�γ�ʱ���
*****************************************************************/
USB_ULONG usb_get_remove_timestamp()
{
    return g_usb_notifier_h.stat_usb_remove_timestamp;
}

EXPORT_SYMBOL_GPL(bsp_usb_unregister_notify);
EXPORT_SYMBOL_GPL(bsp_usb_register_notify);
EXPORT_SYMBOL_GPL(bsp_usb_status_change);
EXPORT_SYMBOL_GPL(adp_usb_queue_delay_work);
EXPORT_SYMBOL_GPL(usb_wake_lock);
EXPORT_SYMBOL_GPL(usb_wake_unlock);
EXPORT_SYMBOL_GPL(usb_get_vbus_status);
EXPORT_SYMBOL_GPL(usb_set_vbus_status);
EXPORT_SYMBOL_GPL(usb_get_hotplug_status);
EXPORT_SYMBOL_GPL(usb_get_hotplug_old_status);
EXPORT_SYMBOL_GPL(usb_get_insert_timestamp);
EXPORT_SYMBOL_GPL(usb_get_remove_timestamp);



/*****************************************************************
Parameters    :
Return        :    ��
Description   :  USB���봦��
*****************************************************************/
static void bsp_usb_insert_process(void)
{
    USB_ULONG flags = 0;
    mutex_lock(&g_usb_notifier_h.mutex);
    /*maybe changed the HW status so need save the irq */
    local_irq_save(flags);
    g_usb_notifier_h.stat_usb_insert_proc++;
    mlog_print("USB", mlog_lv_info, "stat_usb_insert_proc:%d\n", g_usb_notifier_h.stat_usb_insert_proc);
    usb_broadcast_event(USB_BALONG_DEVICE_INSERT);
    /*USB�ϵ�*/
    if (NULL != usb_hotplug_ctx.usb_poweron_cb)
    {
        if (usb_hotplug_ctx.usb_poweron_cb())
        {
            DBG_E(MBB_HOTPLUG, "power on dwc3 usb failed!\n");
            g_usb_notifier_h.stat_usb_poweron_fail++;
            mutex_unlock(&g_usb_notifier_h.mutex);
            return;
        }

    }
    /*GPIO������ID*/
    if (NULL != usb_hotplug_ctx.usbid_proc_cb)
    {
        usb_hotplug_ctx.usbid_proc_cb();
    }
    local_irq_restore(flags);

    /* init the usb driver */
    if (NULL != usb_hotplug_ctx.usb_entry_cb)
    {
        (void)usb_hotplug_ctx.usb_entry_cb();
    }

    /*֪ͨ�������*/
    usb_broadcast_event(USB_BALONG_CHARGER_IDEN);

    g_usb_notifier_h.stat_usb_insert_proc_end++;
    mlog_print("USB", mlog_lv_info, "stat_usb_insert_proc_end:%d\n", g_usb_notifier_h.stat_usb_insert_proc_end);
    mutex_unlock(&g_usb_notifier_h.mutex);
    
    return;
}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  U�̲��봦��
*****************************************************************/
static void bsp_usb_perip_insert_process(void)
{
    USB_INT status = -1;

    mutex_lock(&g_usb_notifier_h.mutex);
    g_usb_notifier_h.stat_usb_perip_insert_proc++;
    mlog_print("USB", mlog_lv_info, "stat_usb_perip_insert_proc:%d\n", g_usb_notifier_h.stat_usb_perip_insert_proc);
    /* set usb notifier status in advance to evade unexpect pmu insert intr. */
    status = g_usb_notifier_h.usb_host_old_status;
    g_usb_notifier_h.usb_host_old_status = USB_BALONG_PERIP_INSERT;

    /*usb �ϵ�*/
    if (NULL !=  usb_hotplug_ctx.usb_poweron_cb)
    {
        if (usb_hotplug_ctx.usb_poweron_cb())
        {
            DBG_E(MBB_HOTPLUG, "power on dwc3 usb failed!\n");
            /* restore usb notifier status set in advance */
            g_usb_notifier_h.usb_host_old_status = status;
            g_usb_notifier_h.stat_usb_poweron_fail++;
			mutex_unlock(&g_usb_notifier_h.mutex);
            return;
        }
    }

    if (NULL !=  usb_hotplug_ctx.usbid_proc_cb)
    {
        (void)usb_hotplug_ctx.usbid_proc_cb();
    }

    /* init the usb driver */
    (void)usb_hotplug_ctx.usb_entry_cb();

    g_usb_notifier_h.stat_usb_perip_insert_proc_end++;
    mlog_print("USB", mlog_lv_info, "stat_usb_perip_insert_proc_end:%d\n"
               , g_usb_notifier_h.stat_usb_perip_insert_proc_end);


    mutex_unlock(&g_usb_notifier_h.mutex);
    
    return;
}


/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ö����ɴ���
*****************************************************************/
static void bsp_usb_enum_done_process(void)
{

    DBG_T(MBB_HOTPLUG, "balong usb enum done,it works well.\n");
    g_usb_notifier_h.stat_usb_enum_done_proc++;
    /*
     * wait for usb enum_done
     */
    if (NULL != usb_hotplug_ctx.usb_wait_enumdone_cb)
    {
        usb_hotplug_ctx.usb_wait_enumdone_cb();
    }
#if(FEATURE_ON == MBB_CHG_BQ27510)
    bq27510_sync_coulupdate_port_control();
#endif
    /* notify kernel notifier */
    usb_broadcast_event(USB_BALONG_ENUM_DONE);
    g_usb_notifier_h.stat_usb_enum_done_proc_end++;
}

/*****************************************************************
Parameters    :
Return        :    ��
Description   :  USB�豸�γ�����
*****************************************************************/
static void bsp_usb_remove_device_process(void)
{
    DBG_T(MBB_HOTPLUG, "balong usb remove.\n");


    mutex_lock(&g_usb_notifier_h.mutex);

    if (NULL != usb_hotplug_ctx.usb_clear_enumdone_cb)
    {
        usb_hotplug_ctx.usb_clear_enumdone_cb();
    }
    g_usb_notifier_h.stat_usb_remove_proc++;
    mlog_print("USB", mlog_lv_info, "stat_usb_remove_proc:%d\n", g_usb_notifier_h.stat_usb_remove_proc);
    /* notify kernel notifier,
     * we must call notifier list before disable callback,
     * there are something need to do before user
     */
#if(FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
    if(0 == switch_flags)
    {
        usb_notify_syswatch(DEVICE_ID_CHARGER, GPIO_CHARGER_REMOVE);
        g_usb_notifier_h.usb_status = USB_BALONG_DEVICE_REMOVE;
        g_usb_notifier_h.charger_type = USB_CHARGER_TYPE_INVALID;
        usb_broadcast_event(USB_BALONG_HOST_INUSED_REMOVE);
        usb_wake_unlock();
        g_usb_notifier_h.stat_usb_remove_proc_end++;
        mutex_unlock(&g_usb_notifier_h.mutex);
        return;
    }
#endif
    usb_broadcast_event(USB_BALONG_DEVICE_REMOVE);
    g_usb_notifier_h.charger_type = USB_CHARGER_TYPE_INVALID;

    /* exit the usb driver */
    if (NULL != usb_hotplug_ctx.usb_exit_cb)
    {
        (void)usb_hotplug_ctx.usb_exit_cb();
    }

    mlog_print("USB", mlog_lv_info, "stat_usb_remove_proc_end:%d\n", g_usb_notifier_h.stat_usb_remove_proc_end);

    if (NULL != usb_hotplug_ctx.usb_poweroff_cb)
    {
        if (usb_hotplug_ctx.usb_poweroff_cb())
        {
            DBG_E(MBB_HOTPLUG, KERN_ERR "fail to disable the dwc3 usb regulator\n");
            g_usb_notifier_h.stat_usb_poweroff_fail++;
        }
    }

    usb_wake_unlock();
    g_usb_notifier_h.stat_usb_remove_proc_end++;


    mutex_unlock(&g_usb_notifier_h.mutex);

#if (FEATURE_ON == MBB_FEATURE_GATEWAY) 
#ifdef CUSTOM_LIVEBOX_B2C
    if ( CONFIG_GATEWAY_NONE != GetGatewayWorkMode())
    {
        SetGatewayWorkMode(CONFIG_GATEWAY_NONE);
        pnp_set_ctl_app_flag(CTL_APP_START);
        BSP_OM_SoftReboot();
    }
#endif
#endif

    return;
}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  U�̵��豸�γ�����
*****************************************************************/
static void bsp_usb_remove_perip_process(void)
{
    DBG_T(MBB_HOTPLUG, "balong usb peripheral remove.\n");

    mutex_lock(&g_usb_notifier_h.mutex);
    
    g_usb_notifier_h.stat_usb_perip_remove_proc++;
    mlog_print("USB", mlog_lv_info, "stat_usb_perip_remove_proc:%d\n", g_usb_notifier_h.stat_usb_perip_remove_proc);
    usb_broadcast_event(USB_BALONG_PERIP_REMOVE);

    /* exit the usb driver */
    if (NULL != usb_hotplug_ctx.usb_exit_cb)
    {
        (void)usb_hotplug_ctx.usb_exit_cb();
    }

    /* power-off usb hardware */
    if (NULL != usb_hotplug_ctx.usb_poweroff_cb)
    {
        if (usb_hotplug_ctx.usb_poweroff_cb())
        {
            DBG_E(MBB_HOTPLUG, KERN_ERR "fail to disable the dwc3 usb regulator\n");
            g_usb_notifier_h.stat_usb_poweroff_fail++;
        }
    }

    //usb_wake_unlock();
    g_usb_notifier_h.stat_usb_perip_remove_proc_end++;

    g_usb_notifier_h.delta_time = 0;


    mlog_print("USB", mlog_lv_info, "stat_usb_perip_remove_proc_end:%d\n"
               , g_usb_notifier_h.stat_usb_perip_remove_proc_end);


    mutex_unlock(&g_usb_notifier_h.mutex);
    
    return;
}
static void usb_host_pmu_remove_process(void)
{
#if (MBB_CHG_EXTCHG == FEATURE_ON)
    OTG_CRADLE_TYPE usb_cradle = CRADLE_NULL;
    OTG_DEVICE_TYPE usb_device = OTG_DEVICE_UNDEFINED;
    usb_cradle =  usb_otg_get_cradle_type();
    usb_device = usb_otg_get_device_type();
    DBG_T(MBB_HOTPLUG, KERN_ERR "usb_host_pmu_remove_process%d,%d\n",usb_cradle,usb_device);
    if((CRADLE_AF35 == usb_cradle))
    {
         if(OTG_DEVICE_MAX == usb_device)
         {
               return;
          }
          usb_otg_pogopin_clean();
          usb_otg_set_device_type();
     }
#else
    DBG_T(MBB_HOTPLUG, KERN_ERR "MBB_CHG_EXTCHG OFF\n");
#endif
}

static void bsp_host_pmu_insert_process(void)
{
#if (MBB_CHG_EXTCHG == FEATURE_ON)
      OTG_CRADLE_TYPE usb_cradle = CRADLE_NULL;
      OTG_DEVICE_TYPE usb_device = OTG_DEVICE_UNDEFINED;
      usb_cradle =  usb_otg_get_cradle_type();
      usb_device = usb_otg_get_device_type();
      DBG_T(MBB_HOTPLUG, KERN_ERR "bsp_host_pmu_insert_process%d,%d\n",usb_cradle,usb_device);
      if(CRADLE_AF35 == usb_cradle)
      {
            if(OTG_DEVICE_UNDEFINED ==usb_device)
            {
                usb_otg_pogopin_set();
            }
       }
       return;
#else
    DBG_T(MBB_HOTPLUG, KERN_ERR "MBB_CHG_EXTCHG OFF\n");
#endif

}

/*****************************************************************
Parameters    :
Return        :    ��
Description   :  �豸���ô���
*****************************************************************/
static void bsp_usb_disable_device_process(void)
{

    DBG_T(MBB_HOTPLUG, "balong usb disable.\n");
    g_usb_notifier_h.stat_usb_disable_proc++;

    /*���ö����Ϣ*/
    if (NULL != usb_hotplug_ctx.usb_clear_enumdone_cb)
    {
        usb_hotplug_ctx.usb_clear_enumdone_cb();
    }

    /* notify kernel notifier */
    usb_broadcast_event( USB_BALONG_DEVICE_DISABLE);
    g_usb_notifier_h.charger_type = USB_CHARGER_TYPE_INVALID;

    g_usb_notifier_h.stat_usb_disable_proc_end++;


    return;
}

/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ���ó������
*****************************************************************/
USB_VOID bsp_usb_set_charger_type(USB_INT type)
{
    g_usb_notifier_h.charger_type = type;
    return;
}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ��ȡ�������
*****************************************************************/
int bsp_usb_get_charger_type(void)
{
    return g_usb_notifier_h.charger_type;
}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  ��ά�ɲ�β��豸��Ϣ
*****************************************************************/
void usb_hotplug_dump(void)
{
    if (USB_CHARGER_TYPE_HUAWEI == g_usb_notifier_h.charger_type)
    {
        DBG_T(MBB_HOTPLUG, "balong usb CHARGER_TYPE: HuaWei     :) \n");
    }
    else if (USB_CHARGER_TYPE_NOT_HUAWEI  == g_usb_notifier_h.charger_type)
    {
        DBG_T(MBB_HOTPLUG, "balong usb CHARGER_TYPE: Not HuaWei :( \n");
    }
    else
    {
        DBG_T(MBB_HOTPLUG, "balong usb CHARGER_TYPE: Invalid    +_+ \n");
    }
    DBG_T(MBB_HOTPLUG, "stat_usb_insert:            %d\n", g_usb_notifier_h.stat_usb_insert);
    DBG_T(MBB_HOTPLUG, "stat_usb_insert_proc:       %d\n", g_usb_notifier_h.stat_usb_insert_proc);
    DBG_T(MBB_HOTPLUG, "stat_usb_insert_proc_end:   %d\n", g_usb_notifier_h.stat_usb_insert_proc_end);
    DBG_T(MBB_HOTPLUG, "stat_usb_enum_done:         %d\n", g_usb_notifier_h.stat_usb_enum_done);
    DBG_T(MBB_HOTPLUG, "stat_usb_enum_done_proc:    %d\n", g_usb_notifier_h.stat_usb_enum_done_proc);
    DBG_T(MBB_HOTPLUG, "stat_usb_enum_done_proc_end:%d\n", g_usb_notifier_h.stat_usb_enum_done_proc_end);
    DBG_T(MBB_HOTPLUG, "stat_usb_remove:            %d\n", g_usb_notifier_h.stat_usb_remove);
    DBG_T(MBB_HOTPLUG, "stat_usb_remove_proc:       %d\n", g_usb_notifier_h.stat_usb_remove_proc);
    DBG_T(MBB_HOTPLUG, "stat_usb_remove_proc_end:   %d\n", g_usb_notifier_h.stat_usb_remove_proc_end);
    DBG_T(MBB_HOTPLUG, "stat_usb_disable:           %d\n", g_usb_notifier_h.stat_usb_disable);
    DBG_T(MBB_HOTPLUG, "stat_usb_disable_proc:      %d\n", g_usb_notifier_h.stat_usb_disable_proc);
    DBG_T(MBB_HOTPLUG, "stat_usb_disable_proc_end:  %d\n", g_usb_notifier_h.stat_usb_disable_proc_end);
    DBG_T(MBB_HOTPLUG, "usb_status:                 %d\n", g_usb_notifier_h.usb_status);
    DBG_T(MBB_HOTPLUG, "usb_old_status:             %d\n", g_usb_notifier_h.usb_old_status);
    DBG_T(MBB_HOTPLUG, "usb_hotplug_state:          %d\n", g_usb_notifier_h.usb_hotplug_state);
    DBG_T(MBB_HOTPLUG, "stat_usb_no_need_notify:    %d\n", g_usb_notifier_h.stat_usb_no_need_notify);
    DBG_T(MBB_HOTPLUG, "stat_usb_poweron_fail:    %d\n", g_usb_notifier_h.stat_usb_poweron_fail);
    DBG_T(MBB_HOTPLUG, "stat_usb_poweroff_fail:    %d\n", g_usb_notifier_h.stat_usb_poweroff_fail);

}
void set_id_delta_time(int mstime)
{
    g_usb_notifier_h.delta_time = mstime;
}
/*
 * usb charger adapter implement
 */
void bsp_usb_status_change_ex(int status)
{
    unsigned long timeout = USB_DETECT_DELAY;
    USB_DBG_VENDOR("%s:status %d\n", __FUNCTION__, status);

    if (USB_BALONG_PERIP_INSERT == status)
    {
        g_usb_notifier_h.stat_usb_perip_insert++;
    }
    else if (USB_BALONG_PERIP_REMOVE == status)
    {
        g_usb_notifier_h.stat_usb_perip_remove++;
    }
    else
    {
        USB_DBG_VENDOR("%s: error status:%d\n", __FUNCTION__, status);
    }

    g_usb_notifier_h.usb_host_status = status;

    if (USB_BALONG_PERIP_INSERT == status || USB_BALONG_PERIP_REMOVE == status)
    {
        if(delayed_work_pending(&g_usb_notifier_h.usb_notify_host_wk))
        {
            cancel_delayed_work(&g_usb_notifier_h.usb_notify_host_wk);
        }
        queue_delayed_work(g_usb_notifier_h.usb_notify_wq,
                           &g_usb_notifier_h.usb_notify_host_wk, msecs_to_jiffies(USB_DETECT_DELAY));

    }
}
void bsp_host_pmu_status_change(int status)
{
    unsigned long timeout = USB_DETECT_DELAY;
    DBG_T(MBB_HOTPLUG, "bsp_host_pmu_status_change %d \n", status);
    g_usb_notifier_h.usb_cradle_pmu_status = status;
    if (USB_BALONG_HOSTPMU_INSERT == status || USB_BALONG_HOSTPMU_REMOVE == status)
    {
        if(delayed_work_pending(&g_usb_notifier_h.usb_cradle_pmu_wk))
        {
            cancel_delayed_work(&g_usb_notifier_h.usb_cradle_pmu_wk);
        }
        queue_delayed_work(g_usb_notifier_h.usb_notify_wq,
                           &g_usb_notifier_h.usb_cradle_pmu_wk, msecs_to_jiffies(USB_DETECT_DELAY));

    }
}
void bsp_host_pmu_status_update(int status)
{
    g_usb_notifier_h.usb_cradle_pmu_old_status = g_usb_notifier_h.usb_cradle_pmu_status;
    g_usb_notifier_h.usb_cradle_pmu_status = status;
}
void bsp_usb_status_update_ex(int status)
{
    g_usb_notifier_h.usb_host_status = status;
}
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  usb��ι�������
*****************************************************************/
static void usb_notify_handler(struct work_struct* work)
{
    USB_INT cur_status = g_usb_notifier_h.usb_old_status;
    USB_INT status = 0;
    USB_ULONG flags = 0;
    DBG_T(MBB_HOTPLUG, "old_status %d,status%d\n",
          g_usb_notifier_h.usb_old_status, g_usb_notifier_h.usb_status);

recheck:
    status =  g_usb_notifier_h.usb_status;
    if (g_usb_notifier_h.usb_old_status == status)
    {
        g_usb_notifier_h.stat_usb_no_need_notify++;
    }
    DBG_T(MBB_HOTPLUG, "task of cur_status %d status:%d:start.\n",   cur_status, status);

    if (status != cur_status)
    {
        local_irq_save(flags);
        cur_status = status;
        g_usb_notifier_h.usb_old_status = status;
        local_irq_restore( flags);
        switch (status)
        {
            case USB_BALONG_DEVICE_INSERT:

                /*�ж��Ƿ����߳�繦��*/
                if (NULL  != usb_hotplug_ctx.usb_check_wireless_chg_cb)
                {
                    if (1 == usb_hotplug_ctx.usb_check_wireless_chg_cb())
                    {
                        DBG_T(MBB_HOTPLUG, "wireless charger detected\n");
                        break;
                    }
                }
                if (USB_BALONG_HOTPLUG_INSERT
                    == g_usb_notifier_h.usb_hotplug_state)
                {
                    DBG_T(MBB_HOTPLUG, "task of %d cancel.\n",   cur_status);
                    return ;
                }
                g_usb_notifier_h.usb_hotplug_state = USB_BALONG_HOTPLUG_INSERT;
                //local_irq_save(flags);
                bsp_usb_insert_process();
                //local_irq_restore(flags);

                break;
            case USB_BALONG_PERIP_INSERT:
                local_irq_save(flags);
                bsp_usb_perip_insert_process();
                local_irq_restore(flags);
                break;
            case USB_BALONG_ENUM_DONE:
                bsp_usb_enum_done_process();
                break;
            case USB_BALONG_DEVICE_REMOVE:
                /*�ж��Ƿ����߳�繦��*/
                if (NULL  != usb_hotplug_ctx.usb_wireless_chg_remove_cb)
                {
                    if (1 == usb_hotplug_ctx.usb_wireless_chg_remove_cb())
                    {
                        DBG_T(MBB_HOTPLUG, "wireless charger remove\n");
                        break;
                    }
                }

                if (USB_BALONG_HOTPLUG_REMOVE
                    == g_usb_notifier_h.usb_hotplug_state)
                {
                    DBG_T(MBB_HOTPLUG, "task of %d cancel.\n",   cur_status);
                    return ;
                }
                g_usb_notifier_h.usb_hotplug_state = USB_BALONG_HOTPLUG_REMOVE;
                //local_irq_save(flags);
                bsp_usb_remove_device_process();
                //local_irq_restore(flags);

                break;
            case USB_BALONG_PERIP_REMOVE:
                local_irq_save(flags);
                bsp_usb_remove_perip_process();
                local_irq_restore(flags);
                break;
            case USB_BALONG_DEVICE_DISABLE:
                bsp_usb_disable_device_process();
                break;
            default:
                DBG_T(MBB_HOTPLUG, "invalid status:%d\n",
                      cur_status);
                return;
        }
        DBG_T(MBB_HOTPLUG, "recheck\n");
        goto recheck;
    }

    DBG_T(MBB_HOTPLUG, "task of %d end.\n",   cur_status);

    g_usb_notifier_h.usb_old_status = cur_status;
    return;
}

static void usb_notify_handler_ex(struct work_struct* work)
{
    USB_INT old_status = g_usb_notifier_h.usb_host_old_status;
    USB_INT cur_status = 0;

    USB_DBG_VENDOR("%s:old_status %d,cur_status%d\n",
                   __FUNCTION__, g_usb_notifier_h.usb_old_status, cur_status);

    if (g_usb_notifier_h.usb_host_old_status == cur_status)
    {
        g_usb_notifier_h.stat_usb_no_need_notify++;
    }

    USB_DBG_VENDOR("%s:task of %d start.\n", __FUNCTION__, cur_status);
recheck:
    cur_status = g_usb_notifier_h.usb_host_status;
    DBG_T(MBB_HOTPLUG, "udisk task of old_status %d cur_status:%d:start.\n",
            old_status, cur_status);
    if(cur_status !=  old_status)
    {
        old_status = cur_status;
        switch (cur_status)
        { 
            case USB_BALONG_PERIP_REMOVE:
                bsp_usb_remove_perip_process();
            break;
            case USB_BALONG_PERIP_INSERT:
                bsp_usb_perip_insert_process();
            break;
            default:
                USB_DBG_VENDOR("%s, invalid status:%d\n",
                               __FUNCTION__, cur_status);
                return;
        }
        DBG_T(MBB_HOTPLUG, "recheck\n");
        goto recheck;
    }

    USB_DBG_VENDOR("%s:task of %d end.\n", __FUNCTION__, cur_status);

    g_usb_notifier_h.usb_host_old_status = cur_status;
    return;
}

static void usb_cradle_pmu_handle(struct work_struct *work)
{
    USB_INT old_status = g_usb_notifier_h.usb_cradle_pmu_old_status;
    USB_INT cur_status = 0;
recheck:
    cur_status =  g_usb_notifier_h.usb_cradle_pmu_status;
    DBG_T(MBB_HOTPLUG, "task of old_status %d cur_status:%d:start.\n",   old_status, cur_status);
    if(cur_status !=  old_status)
    {
         old_status = cur_status;
        switch (cur_status)
        {
            case USB_BALONG_HOSTPMU_INSERT:
               bsp_host_pmu_insert_process();
               break;
            case USB_BALONG_HOSTPMU_REMOVE:
               usb_host_pmu_remove_process();
               break;
            default:
               USB_DBG_VENDOR("%s, invalid status:%d\n",
                                __FUNCTION__, cur_status);
               return;
        }
        DBG_T(MBB_HOTPLUG, "recheck\n");
        goto recheck;
     } 
    g_usb_notifier_h.usb_cradle_pmu_old_status = cur_status;
    return;
}

/*****************************************************************
Parameters    :
Return        :    ��
Description   :  USB hotplug��wakelock��
*****************************************************************/
USB_VOID wake_unlock_handler( USB_ULONG data )
{
    USB_ULONG flags = 0;

    local_irq_save(flags);
    DBG_T(MBB_HOTPLUG, "usb_status : %d.\n",   g_usb_notifier_h.usb_status);
    if ( USB_BALONG_DEVICE_REMOVE == g_usb_notifier_h.usb_status)
    {
        wake_unlock(&g_dwc_wakelock);
    }
    local_irq_restore(flags);
}
#if(FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
static void usb_switch_handle(struct work_struct* work)
{
    if(0 == detect_udisk_flags)
    {
        usb_set_switch_direction(1);
    }
}
USB_VOID usb_set_switch_to_mport(USB_ULONG data)
{
    int time = 0;
    usb_start_work(&g_usb_notifier_h.dwc_check_udisk_wk, time);
}
#endif
/*****************************************************************
Parameters    :
Return        :    ��
Description   :  USB hotplugģ���ʼ��
*****************************************************************/

USB_INT usb_hotplug_init(USB_VOID)
{
    USB_INT ret = 0;

    /*����֪ͨ*/
    /* init local ctx resource */
    /*c��׼��ȫ�ֱ���(external variable)�;�̬���� (static variable)�ĳ�ʼ��ʽ����Ϊ�������ʽ*/
    usb_hotplug_ctx.usb_notify_wq_extern = system_nrt_wq;
    g_usb_notifier_h.charger_type = USB_CHARGER_TYPE_INVALID;
    g_usb_notifier_h.usb_hotplug_state = USB_BALONG_HOTPLUG_REMOVE;
    mutex_init(&g_usb_notifier_h.mutex);
    g_usb_notifier_h.usb_notify_wq = create_singlethread_workqueue("usb_notify");
    if (!g_usb_notifier_h.usb_notify_wq)
    {
        DBG_T(MBB_HOTPLUG, "create_singlethread_workqueue fail\n");
        ret = -1;
    }
    INIT_DELAYED_WORK(&g_usb_notifier_h.usb_notify_wk, (void*)usb_notify_handler);
    INIT_DELAYED_WORK(&g_usb_notifier_h.usb_notify_host_wk, (void*)usb_notify_handler_ex);

    INIT_DELAYED_WORK(&g_usb_notifier_h.usb_cradle_pmu_wk, (void*)usb_cradle_pmu_handle);

    /*����usb ��wakelock��*/
    wake_lock_init(&g_dwc_wakelock, WAKE_LOCK_SUSPEND, "dwc3-wakelock");

    setup_timer(&g_wake_unlock_timer , wake_unlock_handler, (USB_ULONG)0);
#if(FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
    INIT_DELAYED_WORK(&g_usb_notifier_h.dwc_check_udisk_wk, (void*)usb_switch_handle);
    setup_timer(&dwc_check_udisk_timer , &usb_set_switch_to_mport, (USB_ULONG)0);
#endif
    /*��ʼ���ص�*/
    return ret;
}
#if(FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
USB_INT usb_get_switch_direction(USB_VOID)
{
    return switch_flags;
}
EXPORT_SYMBOL(usb_get_switch_direction);

USB_INT usb_set_switch_direction(USB_INT value)
{
    int error;

    DBG_T(MBB_HOTPLUG, "%d\n", value);
    if(0 == value)
    {
        if(0 == switch_flags)
        {
            return 0;
        }
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
        usb_direction_flag_set(TRUE);
        extchg_set_charge_enable(FALSE);
        msleep(600); /* power down delay 600ms */
#endif
        error = gpio_direction_output(GPIO_USB_SELECT,GPIO_SWITCH_A_LEVEL); //�л���A�ڹ���
        if (error < 0)
        {
            DBG_T(MBB_HOTPLUG, "%s:Failed to request GPIO error: %d.\n",
            __FUNCTION__, error);
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
            usb_direction_flag_set(FALSE);
            extchg_set_charge_enable(TRUE);
#endif
            return error;
        }
        error = gpio_direction_output(GPIO_USB_ID,GPIO_LOW);
        if (error < 0)
        {
            DBG_T(MBB_HOTPLUG, "%s:Failed to request GPIO error: %d.\n",
            __FUNCTION__, error);
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
            usb_direction_flag_set(FALSE);
            extchg_set_charge_enable(TRUE);
#endif
            return error;
        }
        switch_flags = value;
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
        usb_direction_flag_set(FALSE);
        extchg_set_charge_enable(TRUE);
#endif
        del_timer(&dwc_check_udisk_timer);
        msleep(USB_SELECT_DELAY);
        bsp_usb_status_change_ex(USB_BALONG_PERIP_INSERT);
        mod_timer(&dwc_check_udisk_timer, jiffies + msecs_to_jiffies(CHECK_UDISK_TIME));
    }
    else if (1 == value)
    {
        if(1 == switch_flags)
        {
            return 0;
        }
        error = gpio_direction_output(GPIO_USB_ID,GPIO_HIGH);
        if (error < 0)
        {
            DBG_T(MBB_HOTPLUG, "%s:Failed to request GPIO error: %d.\n",
            __FUNCTION__, error);
            return error;
        }
        error = gpio_direction_output(GPIO_USB_SELECT,GPIO_SWITCH_M_LEVEL);//�л���M�ڹ���
        if (error < 0)
        {
            DBG_T(MBB_HOTPLUG, "%s:Failed to request GPIO error: %d.\n",
            __FUNCTION__, error);
            return error;
        }
        switch_flags = value;
        bsp_usb_status_change_ex(USB_BALONG_PERIP_REMOVE);
        msleep(USB_SELECT_DELAY);
        if(1 == recv_vbus_on_intr)
        {
            g_usb_notifier_h.usb_old_status = 0;
            g_usb_notifier_h.usb_hotplug_state = 0;
            bsp_usb_status_change(USB_BALONG_DEVICE_INSERT);
        }
    }
    return 0;
}
EXPORT_SYMBOL(usb_set_switch_direction);
#endif

