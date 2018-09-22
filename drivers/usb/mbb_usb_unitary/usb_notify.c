


#include <linux/kernel.h>
#include <linux/export.h>
#include <linux/notifier.h>
#include <linux/usb.h>
#include <linux/mutex.h>
#include <linux/netlink.h>
#include "usb_notify.h"
#include "usb_debug.h"
static BLOCKING_NOTIFIER_HEAD(usb_otg_event_list);
/**
 * usb_register_otg_notify - register a notifier callback whenever a usb otg 
change happens
 * @nb: pointer to the notifier block for the callback events.
 *
 * These changes are either USB ID have been connected to GND or disconnect.
 */
USB_VOID usb_register_otg_notify(struct notifier_block *nb)
{
    //printk("---------------> usb_register_otg_notify \n");
    DBG_I(MBB_OTG_CHARGER,"---------------> usb_register_otg_notify \n");
    blocking_notifier_chain_register(&usb_otg_event_list, nb);
}
EXPORT_SYMBOL_GPL(usb_register_otg_notify);

/**
 * usb_unregister_otg_notify - unregister a notifier callback
 * @nb: pointer to the notifier block for the callback events.
 *
 * usb_register_notify() must have been previously called for this function
 * to work properly.
 */
USB_VOID usb_unregister_otg_notify(struct notifier_block *nb)
{
    blocking_notifier_chain_unregister(&usb_otg_event_list, nb);
}
EXPORT_SYMBOL_GPL(usb_unregister_otg_notify);

USB_VOID usb_notify_event(USB_ULONG val, USB_PVOID v)
{
    DBG_I(MBB_ALL,"---------------> usb_notify_event: val = %lu \n",val);
    blocking_notifier_call_chain(&usb_otg_event_list, val, v);
}
EXPORT_SYMBOL_GPL(usb_notify_event);


/*****************************************************************
Parameters    :  deviceid  : �豸ID    eventcode :  �¼�
Return        :    ��
Description   :  ��Ӧ�ò��ϱ�  USB   �¼�
*****************************************************************/
USB_VOID usb_notify_syswatch(USB_INT deviceid,USB_INT eventcode)
{
    DEVICE_EVENT stusbEvent = {0};
    stusbEvent.device_id = deviceid;
    stusbEvent.event_code = eventcode;
    stusbEvent.len = 0;         
    DBG_I(MBB_ALL,"U_EVENT: usb_notify_syswatch<%d,%d>\n",deviceid,eventcode);
    (void)device_event_report(&stusbEvent,sizeof(DEVICE_EVENT));
 
}


