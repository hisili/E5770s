

#ifndef _USB_CHG_MANAGER_
#define _USB_CHG_MANAGER_

#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/utsname.h>
#include <linux/platform_device.h>
#include "usb_platform_comm.h"
typedef enum
{
    CHG_CHGR_UNKNOWN    = 0,
    CHG_WALL_CHGR       = 1,
    CHG_USB_HOST_PC     = 2,
    CHG_NONSTD_CHGR     = 3,
    CHG_WIRELESS_CHGR   = 4,
    CHG_EXGCHG_CHGR     = 5,
    CHG_500MA_WALL_CHGR = 6,
    CHG_USB_OTG_CRADLE  = 7,
    CHG_CHGR_INVALID    = 8,
    CHG_CHGR_TYPE_RSVD  = 0xFFFF /* */
} chg_chgr_type_t;
/**
*   CHARGER(�����)�����ϱ����¼�
*/
typedef enum _GPIO_CHARGER_EVENT
{
    GPIO_CHARGER_ATTATCH = 0,  /* �ڳ��������ʱ�ϱ�����ʾ�г�������� */
    GPIO_CHARGER_REMOVE = 1,       /* �ڳ�����γ�ʱ�ϱ�����ʾ��������γ� */
    GPIO_WIRELESS_ATTATCH = 2,     /* �����߳��������ʱ�ϱ�����ʾ�����߳�������� */
    GPIO_WIRELESS_REMOVE = 3,      /* �����߳������γ�ʱ�ϱ�����ʾ�����߳�����γ� */
    GPIO_CHARGER_EVENT_MAX     /* ����¼�ֵ��С�ڴ�ֵ����Ϊ�Ƿ��¼� */
} GPIO_CHARGER_EVENT;

typedef struct mbb_charger
{
    chg_chgr_type_t current_chg_type;  /* �������*/
    USB_BOOL  usb_chg_action_flag;       /*�����룬�γ�*/
    USB_INT usb_chg_work_mode;       /*��繤��ģʽ*/
    struct workqueue_struct* usb_chg_notify_wq;
    struct delayed_work usb_chg_notify_work;
} mbb_charger_st;


/*���ڵ�����ģʽ���� ����*/
enum usb_chg_mode
{
    USB_CHG_NON = 0, /* �����ģʽ */
    USB_CHG_LINE,       /*USB ���������ģʽ */
    USB_CHG_WIRELESS, /*���߳��ģʽ*/
    USB_CHG_EXTERN,     /* ������ģʽ */
};

/* ����������͵ķ���ʱ�䶨�� */
#define MSM_CHG_DET_DELAY_TIME      (1000 * HZ / 1000)

#define CHG_DETECT_OVERTIME (10 * 1000)   /* 10s */
/* ȫ�ֱ�����¼��ǰ�ĳ������ */

#define MBB_USB_CHARGER_TYPE_HUAWEI                  1
#define MBB_USB_CHARGER_TYPE_NOT_HUAWEI          2
#define MBB_USB_CHARGER_TYPE_PC                           3
#define MBB_USB_CHARGER_TYPE_INVALID                  0

#define MBB_USB_DEVICE_INSERT                         1
#define MBB_USB_DEVICE_IDEN                             2
#define MBB_USB_ENUM_DONE                               3
#define MBB_USB_DEVICE_REMOVE                        0
#if(FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
#define MBB_USB_HOST_INUSED_REMOVE                    8
#endif
USB_INT usb_charger_type_detect_event(struct notifier_block* nb, USB_ULONG val, USB_PVOID data);
USB_VOID usb_set_speed(USB_INT speed);
USB_VOID usb_charger_init(USB_VOID);
USB_VOID usb_charger_exit(USB_VOID);
USB_VOID usb_chg_set_work_mode(USB_INT chg_mode);
USB_BOOL usb_chg_check_current_mode(USB_INT chg_mode);
#if (MBB_CHG_WIRELESS == FEATURE_ON)
USB_BOOL usb_chg_wireless_detect(USB_VOID);
USB_BOOL usb_chg_wireless_remove(USB_VOID);
#else
static inline USB_BOOL usb_chg_wireless_detect(USB_VOID)
{
    return 0;
}
static inline USB_BOOL usb_chg_wireless_remove(USB_VOID)
{
    return 0;
}
#endif /*MBB_CHG_WIRELESS*/

#endif
