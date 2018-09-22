

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/utsname.h>
#include <linux/platform_device.h>

#include <linux/usb/ch9.h>
#include <linux/usb/composite.h>
#include <linux/usb/gadget.h>

#include "usb_charger_manager.h"
#include <product_config.h>
#include "gadget_chips.h"
#include <linux/netlink.h>
#include <linux/notifier.h>
#include "usb_notify.h"
#include "usb_debug.h"
/*����ӿ�*/
#include <linux/usb/usb_interface_external.h>

/*�����ⲿ�ӿ�*/
#include "mbb_usb_adp.h"

#if (MBB_CHG_WIRELESS == FEATURE_ON)
#include <bsp_hkadc.h>
#include <bsp_sram.h>
#define VBUS_JUDGEMENT_THRESHOLD 700 //���߳��adc�ж�����ֵ��
#endif /* MBB_CHG_WIRELESS */
enum usb_chg_action
{
    CHG_PULL_OUT,
    CHG_PLUG_IN,
};

static usb_adp_ctx_t* usb_adp_cb = NULL;
static mbb_charger_st  g_mbb_charger =
{
    .current_chg_type = CHG_CHGR_INVALID,
    .usb_chg_action_flag = CHG_PULL_OUT,
    .usb_chg_work_mode = USB_CHG_NON,
};

/* ���ö�ʱ�����ڲ���PC�ͷǱ������Ժ�����10s��ʱ������Ƿ�ö�ٳɹ� */
static struct timer_list chg_nonstd_det_timer ;

static USB_INT first_report_chg_type = 1;

#if ( FEATURE_ON == MBB_CHG_PLATFORM_9X25 )
extern  struct wake_lock g_charger_wake_lock;
#endif
/*****************************************************************
Parameters    :  chg_mode ��ǰ���ģʽ
Return        :    ��
Description   :  �����ģʽ����Ϊ��ǰģʽ���Ի�������ģʽ
*****************************************************************/
USB_VOID usb_chg_set_work_mode(USB_INT chg_mode)
{
    g_mbb_charger.usb_chg_work_mode = chg_mode;
    DBG_I(MBB_CHARGER, "set charger_work_mode = %d \n",
          g_mbb_charger.usb_chg_work_mode);
}
/*****************************************************************
Parameters    :  chg_mode ��ǰ���ģʽ
Return        :    1���ɽ��뵱ǰ���ģʽ�� 0������ִ�е�ǰģʽ
Description   :  �жϱ����ģʽ�Ƿ��ִ��
*****************************************************************/
USB_BOOL usb_chg_check_current_mode(USB_INT chg_mode)
{
    if ((USB_CHG_NON == g_mbb_charger.usb_chg_work_mode)  ||
        chg_mode == g_mbb_charger.usb_chg_work_mode)
    {
        return   1;
    }
    else
    {
        return  0;
    }
}
/*****************************************************************
Parameters    :  chg_type �������
Return        :    ��
Description   :  ���������ת��Ϊ�ַ�
*****************************************************************/
static const char* chg_type_to_string(chg_chgr_type_t chg_type)
{
    switch (chg_type)
    {
        case CHG_CHGR_UNKNOWN:
            return "CHG_CHGR_UNKNOWN";
        case CHG_WALL_CHGR:
            return "CHG_WALL_CHGR";
        case CHG_USB_HOST_PC:
            return "CHG_USB_HOST_PC";
        case CHG_NONSTD_CHGR:
            return "CHG_NONSTD_CHGR";
        case CHG_WIRELESS_CHGR:
            return "CHG_WIRELESS_CHGR";
        case CHG_EXGCHG_CHGR:
            return "CHG_EXGCHG_CHGR";
        case CHG_CHGR_INVALID:
            return "CHG_CHGR_INVALID";
        default:
            return "CHG_CHGR_INVALID";
    }
}

/*****************************************************************
Parameters    :
Return        :
Description   :
*****************************************************************/
/* �β���Ҫ����unsigned long data���������־���1 */
static USB_VOID detect_chg_carkit_timer_handler( USB_ULONG data )
{
    mbb_charger_st* mbb_chg = ( mbb_charger_st*)data;

    if (CHG_CHGR_UNKNOWN == g_mbb_charger.current_chg_type)
    {
        g_mbb_charger.current_chg_type = CHG_NONSTD_CHGR;
        g_mbb_charger.usb_chg_action_flag = CHG_PLUG_IN;
        queue_delayed_work(g_mbb_charger.usb_chg_notify_wq,
                           &mbb_chg->usb_chg_notify_work, 0);
        usb_notify_syswatch(DEVICE_ID_CHARGER, GPIO_CHARGER_ATTATCH);
    }
}

/*****************************************************************
Parameters    :
Return        :
Description   :  �����ģ���ϱ�����¼�
*****************************************************************/
static USB_VOID usb_chg_det_notify_work( struct work_struct* w )
{
    mbb_charger_st* mbb_chg = container_of(w, mbb_charger_st, usb_chg_notify_work.work);

    DBG_I(MBB_CHARGER, "%s:current_chg_type:%s\n", __func__,
          chg_type_to_string(g_mbb_charger.current_chg_type));

    if (first_report_chg_type)
    {
        usb_adp_cb->stm_set_chg_type_cb(g_mbb_charger.current_chg_type);
        first_report_chg_type = 0;
    }
    usb_adp_cb->battery_notifier_call_chain_cb(g_mbb_charger.usb_chg_action_flag,
            g_mbb_charger.current_chg_type);

}

#define DELTA_TIME_AND_REMOVE_INSERT 200
USB_ULONG wall_chg_insert_time = 0;
USB_ULONG wall_chg_remove_time = 0;
USB_INT dp_dm_connected = 0;

/*****************************************************************
Parameters    :  nb:    val :USB�豸����״̬   data:��䡢�Ǳ������ֵ
Return        :    0
Description   :  ������ͼ��
*****************************************************************/
USB_INT usb_charger_type_detect_event(struct notifier_block* nb, USB_ULONG val, USB_PVOID data)
{
    USB_INT ret = 0;
    USB_INT charger_type = *( (USB_INT*)data);
    USB_ULONG delta_wall_chg_time = 0;

    DBG_E(MBB_CHARGER, "%s -val: %ld ,charger_type:%d\n",
          __func__, val, charger_type);
    /*�жϵ�ǰ���ģʽ�Ƿ񻥳�*/
    if (!usb_chg_check_current_mode(USB_CHG_LINE))
    {
        DBG_E(MBB_CHARGER, "charge mode is mutually exclusive\n");
        return ret;
    }


    if ( MBB_USB_DEVICE_IDEN == val)
    {
        /*
        * note: the function will sleep in long time !!!
        * 0:INVALID , 1:huawei charger, 2:NOT_HUAWEI  3:PC_charger
        */
        g_mbb_charger.usb_chg_action_flag = CHG_PLUG_IN;
        switch (charger_type)
        {
            case MBB_USB_CHARGER_TYPE_HUAWEI:
#if (FEATURE_ON == MBB_CHG_PLATFORM_9X25  )
                /*���������������õ�������*/
                wake_lock(&g_charger_wake_lock);
                DBG_I(MBB_CHARGER, " charger plug in locked!\n");
#endif
                delta_wall_chg_time = wall_chg_insert_time - wall_chg_remove_time;
                DBG_I(MBB_CHARGER, "delta_wall_chg_time 0x%lx!\nwall_chg_insert_time 0x%lx!\nwall_chg_remove_time 0x%lx!\n",
                      delta_wall_chg_time,
                      wall_chg_insert_time,
                      wall_chg_remove_time);
                if ((DELTA_TIME_AND_REMOVE_INSERT > delta_wall_chg_time)
                    && (1 == dp_dm_connected))
                {
                    DBG_I(MBB_CHARGER, "CHG_500MA_WALL_CHGR detected!\n");
                    g_mbb_charger.current_chg_type = CHG_500MA_WALL_CHGR;
                }
                else
                {
                    DBG_I(MBB_CHARGER, "CHG_WALL_CHGR detected!\n");
                    g_mbb_charger.current_chg_type = CHG_WALL_CHGR;
                }

                queue_delayed_work(g_mbb_charger.usb_chg_notify_wq,
                                   &g_mbb_charger.usb_chg_notify_work, 0);

                break;
            case MBB_USB_CHARGER_TYPE_NOT_HUAWEI:
                g_mbb_charger.current_chg_type = CHG_CHGR_UNKNOWN;
                /* ���� 10s �Ǳ��������ͼ�� */
                mod_timer(&chg_nonstd_det_timer, jiffies
                          + msecs_to_jiffies(CHG_DETECT_OVERTIME));

                break;
            case  MBB_USB_CHARGER_TYPE_PC:
                g_mbb_charger.current_chg_type = CHG_USB_HOST_PC;
                DBG_E(MBB_CHARGER, "current_chg_type %d",
                      g_mbb_charger.current_chg_type);
                queue_delayed_work(g_mbb_charger.usb_chg_notify_wq,
                                   &g_mbb_charger.usb_chg_notify_work, 0);

                break;
            case MBB_USB_CHARGER_TYPE_INVALID:
                g_mbb_charger.current_chg_type = CHG_CHGR_INVALID;
                DBG_E(MBB_CHARGER, "invalid charger %s!\n", __func__);
                queue_delayed_work(g_mbb_charger.usb_chg_notify_wq,
                                   &g_mbb_charger.usb_chg_notify_work, 0);
                break;
            default:
                queue_delayed_work(g_mbb_charger.usb_chg_notify_wq,
                                   &g_mbb_charger.usb_chg_notify_work, 0);

                break;
        }
    }
    else if (MBB_USB_DEVICE_INSERT == val)
    {
        usb_chg_set_work_mode(USB_CHG_LINE);
        g_mbb_charger.current_chg_type = CHG_CHGR_UNKNOWN;
        g_mbb_charger.usb_chg_action_flag = CHG_PLUG_IN;
        usb_notify_syswatch(DEVICE_ID_CHARGER, GPIO_CHARGER_ATTATCH);
        queue_delayed_work(g_mbb_charger.usb_chg_notify_wq,
                           &g_mbb_charger.usb_chg_notify_work, 0);
    }
#if(FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
    else if ( MBB_USB_DEVICE_REMOVE == val || MBB_USB_HOST_INUSED_REMOVE == val )
#else
    else if ( MBB_USB_DEVICE_REMOVE == val )
#endif
    {
        g_mbb_charger.usb_chg_action_flag = CHG_PULL_OUT;

        DBG_E(MBB_CHARGER, "CHARGER pull out!\n");
        usb_notify_syswatch(DEVICE_ID_CHARGER, GPIO_CHARGER_REMOVE);
        queue_delayed_work(g_mbb_charger.usb_chg_notify_wq,
                           &g_mbb_charger.usb_chg_notify_work, 0);
#if (FEATURE_ON == MBB_CHG_PLATFORM_9X25  )
        /*������Ƴ��ͷ���*/
        if ((CHG_WALL_CHGR == g_mbb_charger.current_chg_type) ||
            (CHG_500MA_WALL_CHGR == g_mbb_charger.current_chg_type))
        {
            wake_unlock(&g_charger_wake_lock);
            DBG_E(MBB_CHARGER, "charger plug out unlocked!\n");
        }
#endif
        g_mbb_charger.current_chg_type = CHG_CHGR_INVALID;
        usb_chg_set_work_mode(USB_CHG_NON);
    }
    return ret;
}

static struct notifier_block usb_charger_type_detect_block =
{
    .notifier_call = usb_charger_type_detect_event
};

#if (MBB_CHG_WIRELESS == FEATURE_ON)
/*****************************************************************
Parameters    :  ��
Return        :    1: �����߳�� 0: û�����߳���¼�
Description   :  ���߳���⼰��Ϣ�ϱ�
*****************************************************************/
USB_BOOL usb_chg_wireless_detect(USB_VOID)
{
    USB_INT16 adc_voltage = 0;
    USB_INT ret = 0;

    /*�жϵ�ǰ���ģʽ�Ƿ񻥳�*/
    if (!usb_chg_check_current_mode(USB_CHG_WIRELESS))
    {
        DBG_E(MBB_CHARGER, "%s:charge mode is mutually exclusive\n", __func__);
        return  0;
    }

#if (FEATURE_ON == MBB_DLOAD)
    huawei_smem_info* smem_data = NULL;
    smem_data = (huawei_smem_info*)SRAM_DLOAD_ADDR;

    /*��������������������ʱ���ж����߳��*/
    adc_voltage = VBUS_JUDGEMENT_THRESHOLD;
    if (SMEM_DLOAD_FLAG_NUM != smem_data->smem_dload_flag)
    {
        ret = bsp_hkadc_convert(HKADC_CHANNEL_8, &adc_voltage);
    }
    else
    {
        return 0;
    }
#else
    ret = bsp_hkadc_convert(HKADC_CHANNEL_8, &adc_voltage);
#endif /*MBB_DLOAD*/
    DBG_I(MBB_CHARGER, "bsp_hkadc_convert ret = %d, bsp_hkadc_convert = %d.\n",
          ret, adc_voltage);
    if ((0 == ret) && (adc_voltage < VBUS_JUDGEMENT_THRESHOLD))
    {
        DBG_E(MBB_CHARGER, "CHG_WIRELESS_CHGR detected!\n");
        usb_chg_set_work_mode(USB_CHG_WIRELESS);
        g_mbb_charger.current_chg_type = CHG_WIRELESS_CHGR;
        usb_adp_cb->stm_set_chg_type_cb(g_mbb_charger.current_chg_type);
        usb_adp_cb->battery_notifier_call_chain_cb(1, g_mbb_charger.current_chg_type);
        return 1;
    }
    else
    {
        return 0;
    }
}

USB_BOOL usb_chg_wireless_remove(USB_VOID)
{
    /*�жϵ�ǰ���ģʽ�Ƿ񻥳�*/
    if (!usb_chg_check_current_mode(USB_CHG_WIRELESS))
    {
        DBG_E(MBB_CHARGER, "%s:charge mode is mutually exclusive\n", __func__);
        return  0;
    }

    if ( CHG_WIRELESS_CHGR == g_mbb_charger.current_chg_type)
    {
        DBG_E(MBB_CHARGER, "CHG_WIRELESS_CHGR pull out!\n");
        usb_adp_cb->battery_notifier_call_chain_cb(0,
                g_mbb_charger.current_chg_type);
        g_mbb_charger.current_chg_type = CHG_CHGR_INVALID;
        usb_chg_set_work_mode(USB_CHG_NON);
        return 1;
    }
    else
    {
        return 0;
    }
}
#endif /* MBB_CHG_WIRELESS */


/*****************************************************************
Parameters    :  ��
Return        :    ��
Description   :  ���ģ���ʼ��
*****************************************************************/
USB_VOID usb_charger_init(USB_VOID)
{
    usb_adp_cb = usb_get_adp_ctx();/*��ȡ�������ⲿ�ӿ�*/
    g_mbb_charger.usb_chg_notify_wq = create_singlethread_workqueue("usb_chg_notify");
    INIT_DELAYED_WORK(&g_mbb_charger.usb_chg_notify_work,
                      usb_chg_det_notify_work);
    setup_timer(&chg_nonstd_det_timer, detect_chg_carkit_timer_handler,
                (USB_ULONG)&g_mbb_charger);
    usb_adp_cb->usb_register_notify_cb(&usb_charger_type_detect_block);
}

/*****************************************************************
Parameters    :  ��
Return        :    ��
Description   :  ���ģ���˳�
*****************************************************************/
USB_VOID usb_charger_exit(USB_VOID)
{
    cancel_delayed_work_sync(&g_mbb_charger.usb_chg_notify_work);
    del_timer(&chg_nonstd_det_timer); /* delete timer */
    usb_adp_cb->usb_unregister_notify_cb(&usb_charger_type_detect_block);
}

