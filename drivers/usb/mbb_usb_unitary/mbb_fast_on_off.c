


#include <linux/usb/gadget.h>
#include <drv_fastOnOff.h>
#include <linux/notifier.h>
#include <linux/usb/composite.h>
#include <mbb_config.h>
#include <linux/usb/usb_interface_external.h>
#include "usb_debug.h"
#include "usb_platform_comm.h"
#include "usb_notify.h"
#include "hw_pnp.h"
#include "mbb_fast_on_off.h"

static USB_INT fast_off_status = false;

extern USB_VOID mass_storage_open(USB_VOID);
extern USB_VOID mass_storage_close(USB_VOID);
extern USB_VOID pnp_switch_autorun_port(USB_VOID);
/*****************************************************************
Parameters    : fastMode :�ٹػ�ģʽ
Return        :    ��
Description   :  �ٹػ�ģʽ����
*****************************************************************/
USB_INT usb_fast_on_off_mode_set( FASTONOFF_MODE fastMode)
{
    DBG_T(MBB_CHARGER, "%s Entery mode %d!\n", __func__, fastMode);
    switch (fastMode)
    {
            /*�˳��ٹػ�״̬*/
        case FASTONOFF_MODE_CLR:
            fast_off_status = false;
            DBG_T(MBB_CHARGER, "EXIT fast off status:fastMode:%d\n", fastMode);
#ifdef USB_CHARGE_EXT
            usb_notify_event(USB_OTG_ENABLE_ID_IRQ, NULL);
#endif
            break;
            /*����ٹػ�״̬*/
        case FASTONOFF_MODE_SET:
            fast_off_status = true;
            DBG_T(MBB_CHARGER, "enter fast off status:fastMode:%d\n", fastMode);
#ifdef USB_CHARGE_EXT
            usb_notify_event(USB_OTG_DISABLE_ID_IRQ, NULL);
#endif
            break;
        default:
            DBG_E(MBB_CHARGER, "defalut fast power off :fastMode:%d\n", fastMode);
            break;
    }

    pnp_switch_autorun_port();

    return 0;
}

/*****************************************************************
Parameters    :  ��
Return        :  1:�ٹػ�  0: �Ǽٹػ�
Description   :  ��ȡ�ٹػ�״̬
*****************************************************************/
USB_INT usb_fast_on_off_stat(USB_VOID)
{
    return fast_off_status ;
}

/*****************************************************************
Parameters    :
Return        :
Description   :
*****************************************************************/
static USB_INT usb_monitor_charger_event(struct notifier_block* nb,
        USB_ULONG val, USB_PVOID data)
{
    USB_INT ret = 0;

    DBG_I(MBB_CHARGER, "%s +++usb_monitor_charger_event+++ %ld \n", __func__, val);
    ret = usb_fast_on_off_mode_set(val);
    return ret;
}

static struct notifier_block usb_monitor_charger_block =
{
    .notifier_call = usb_monitor_charger_event
};

/*****************************************************************
Parameters    :  ��
Return        :    ��
Description   :  USB  ��һ���ٹػ�ģ���ʼ��
*****************************************************************/
USB_VOID fast_on_off_init(USB_VOID)
{
    blocking_notifier_chain_register(&g_fast_on_off_notifier_list,
                                     &usb_monitor_charger_block);

}

/*****************************************************************
Parameters    :  ��
Return        :    ��
Description   :  USB  ��һ���ٹػ�ģ���˳�
*****************************************************************/
USB_VOID fast_on_off_exit(USB_VOID)
{
    blocking_notifier_chain_unregister(&g_fast_on_off_notifier_list,
                                       &usb_monitor_charger_block);
}


