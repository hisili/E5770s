

#ifndef  _USB_NOTIFY_H
#define  _USB_NOTIFY_H
#include <linux/netlink.h>
#include "usb_platform_comm.h"

#ifndef     MBB_USB_UNITARY_Q 
/*�Ǹ�ͨƽ̨*/
#define    USB_ATTACH_NOTIFY    USB_ATTACH
#define    USB_REMOVE_NOTIFY    USB_REMOVE
#define    USB_ENABLE_NOTIFY    USB_ENABLE
#define    USB_DISABLE_NOTIFY    USB_DISABLE
#define    USB_INIT_NOTIFY    USB_INIT
#define    USB_HALT_NOTIFY    USB_HALT
#define    USB_RESET_NOTIFY    USB_RESET
#define    USB_SUSPEND_NOTIFY    USB_SUSPEND
#define    USB_RESUME_NOTIFY    USB_RESUME
#define    USB_CRADLE_UP_NOTIFY    USB_CRADLE_UP
#define    USB_CRADLE_DOWN_NOTIFY    USB_CRADLE_DOWN
#define    USB_SAMBA_PRINT_ATTACH_NOTIFY    USB_SAMBA_PRINT_ATTACH
#define    USB_SAMBA_PRINT_DETACH_NOTIFY    USB_SAMBA_PRINT_DETACH
#define    USB_CRADLE_ATTACH_NOTIFY    USB_CRADLE_ATTACH
#define    USB_CRADLE_REMOVE_NOTIFY    USB_CRADLE_REMOVE
#define    USB_CRADLE_PLUGIN_NOTIFY    USB_CRADLE_PLUGIN
#define    USB_CRADLE_UNPLUG_NOTIFY    USB_CRADLE_UNPLUG
#define    USB_EVENT_MAX_NOTIFY    USB_EVENT_MAX
#else
/*��ͨƽ̨*/

#define    USB_CRADLE_PLUGIN_NOTIFY    GPIO_USB_CRADLE_PLUGIN
#define    USB_CRADLE_UNPLUG_NOTIFY    GPIO_USB_CRADLE_UNPLUG
#endif


USB_VOID usb_notify_syswatch(USB_INT deviceid,USB_INT eventcode);
USB_VOID usb_notify_event(USB_ULONG val, USB_PVOID v);

USB_VOID usb_register_otg_notify(struct notifier_block *nb);
USB_VOID usb_unregister_otg_notify(struct notifier_block *nb);

#endif