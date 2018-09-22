


#ifndef _DWC_OTG_EXTERN_CHARGE_H
#define _DWC_OTG_EXTERN_CHARGE_H

#include <linux/notifier.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/wakelock.h>
#include <linux/workqueue.h>

#include "usb_vendor.h"
#include "usb_platform_comm.h"

#if (YES == MBB_CHG_PLATFORM_9X25)
/*��ͨƽ̨GPIO�˿ں�*/
#define GPIO_OTG_ID_DET      GPIO_0_17
#define GPIO_OTG_ID_SET      GPIO_2_19
#define GPIO_DMDP_CONNECT    GPIO_2_20

#else   

/*balongƽ̨GPIO�˿ں�*/
#ifdef BSP_CONFIG_BOARD_E5_E5786
#define GPIO_OTG_ID_DET      GPIO_0_17
#define GPIO_OTG_ID_SET      GPIO_2_23
#define GPIO_DMDP_CONNECT    GPIO_2_31
#else
#define GPIO_OTG_ID_DET      GPIO_0_5
#define GPIO_OTG_ID_SET      GPIO_2_3
#define GPIO_DMDP_CONNECT    GPIO_2_5
#endif
#endif /* gpio define */

#define  GPIO_LOW    0
#define  GPIO_HIGH   1

typedef struct otg_charger
{
    struct wake_lock        otg_ec_wakelock;
    struct work_struct      otg_ec_id_work;
    struct notifier_block   otg_ec_notifier_block;

    /* val of id detect gpio, 0: ID pull in; 1: ID pull out */
    USB_INT     det_id_gpio_value;  
    USB_INT     last_det_id_gpio_value;

    USB_INT     sys_cmd;
    USB_INT     last_sys_cmd;

    USB_INT     is_host_mode;
} otg_charger_st;

USB_VOID usb_otg_extern_charge_init(USB_VOID);

USB_VOID usb_otg_extern_charge_remove(USB_VOID);

#endif

