

#ifndef _USB_OTG_DEV_DETECT
#define _USB_OTG_DEV_DETECT

#include <linux/workqueue.h>
#include <linux/gpio.h>
#include "usb_platform_comm.h"
#include <linux/wakelock.h>
#include "mbb_usb_adp.h"

#define GPIO_0_17                     (17)
#define GPIO_2_19                     (83)
#define GPIO_2_20                     (84)

#define GPIO_2_23                       (87)
#define GPIO_2_31	                  (95)


/*
#if (FEATURE_ON == MBB_CHG_PLATFORM_9X25)
#define GPIO_OTG_ID_DET      GPIO_0_17
#define GPIO_OTG_ID_SET      GPIO_2_19
#define GPIO_DMDP_CONNECT    GPIO_2_20
#endif
*/

#ifdef MBB_USB_UNITARY_Q
/*****9x30************/
#define GPIO_OTG_ID_DET   51
/*9x25*/
//#define GPIO_OTG_ID_DET      GPIO_0_17
//#define GPIO_OTG_ID_SET      GPIO_2_19
//#define GPIO_DMDP_CONNECT    GPIO_2_20
#else
/*�˴����� balong   GPIO */
#define GPIO_OTG_ID_DET      OTG_ID_DET_GPIO
#define GPIO_OTG_ID_SET      OTG_ID_SET_GPIO
#define GPIO_DMDP_CONNECT    DMDP_CONNECT_GPIO
#endif

#define INVALID_STATE  -1
#define USB_OTG_CONNECT_DP_DM    0x0001  /*�̽� D+,D-*/
#define USB_OTG_DISCONNECT_DP_DM 0x0002  /*ֱ������������HS_ID*/
#define USB_OTG_ID_PULL_OUT      0x0003  /*ֱ������������HS_ID*/
#define USB_OTG_FAST_OFF   0x0004        /*�ٹػ�*/
#define USB_OTG_FAST_ON    0x0005       /*�ٿ���*/

/*OTG �豸֧��*/
#define USB_OTG_FEATURE_NONE 0x00
#define USB_OTG_FEATURE_CRADLE 0x01
#define USB_OTG_FEATURE_EXTCHG 0x10
#define USB_OTG_FEATURE_CRADLE_EXTCHG 0x11
#define USB_OTG_FEATURE_CRADLE_MASK 0x0f
#define USB_OTG_FEATURE_EXTCHG_MASK 0xf0


#define GPIO_HIGH   1
#define GPIO_LOW    0

#define HOST_ON 0
#define HOST_OFF 1

#define ID_FLOAT 1
#define ID_GROUND 0

#define VBUS_UP   1
#define VBUS_DOWN 0

#define PLATFORM_QUALCOMM   0
#define PLATFORM_BALONG     1

#define OTG_INSERT 1
#define OTG_REMOVE 0

#define OTG_DEV_EVENT_PROC   MBB_USB_TRUE
#define OTG_DEV_EVENT_NONPROC MBB_USB_FALSE

#if(MBB_CHG_EXTCHG == FEATURE_ON)
#define OTG_DET_LONG_DELAY_TIME        HZ  /*OTG  ID �жϷ����жϼ����ʱ*/
#else
#define OTG_DET_LONG_DELAY_TIME        HZ/2/*USB  ID �жϷ����жϼ����ʱ*/
#endif

#define OTG_DET_SHORT_DELAY_TIME       HZ/20  /*��Ҫ���ӳ�*/

/*
 ��¼OTG �豸�γ����̣�
 ����γ�ʱ�����Ϣ�ظ��ϱ�
*/
enum otg_dev_remove_process
{
    OTG_DEV_INVALID_FLAG,
    OTG_DEV_REMOVE_PROC,    /*��ʼ����otg �豸�γ�����*/
    OTG_DEV_REMOVE_DONE     /*otg �豸�γ������vbus �µ�
                                                            ���������øı�־*/
};

typedef enum _otg_device
{
    OTG_DEVICE_UNDEFINED = 0,
    OTG_DEVICE_EXTCHAGER = 1,
    OTG_DEVICE_CRADLE = 2, /*���������ͣ�ʵ���������*/
    OTG_DEVICE_CRADLE_CHARGE = 3, /*��Ʒ��֧��cradle�������*/
    OTG_DEVICE_MAX,
} OTG_DEVICE_TYPE;
typedef enum _cradle_type
{
    CRADLE_NULL = 0,
    CRADLE_AF35 = 1
} OTG_CRADLE_TYPE;
struct otg_debug
{
    USB_UINT stat_usb_id_insert;                   /*����ǰ�������*/
    USB_UINT stat_usb_id_insert_proc;               /*������ ����ǰ�������*/
    USB_UINT stat_usb_id_insert_proc_end;          /*������ ����ɺ�������*/
    USB_UINT stat_usb_id_remove;                         /*����ǰ�γ�����*/
    USB_UINT stat_usb_id_remove_proc;               /*��������ǰ�γ�����*/
    USB_UINT stat_usb_id_remove_proc_end;        /*���������γ�����*/
    USB_UINT stat_usb_id_no_trigger;             /*ID ��ƽ�仯û�д����жϵļ���*/
    USB_UINT stat_usb_dpdm_connect;                    /*D+ D-ֱ��*/
    USB_UINT stat_usb_dpdm_disconnect;                /*D+ D-�Ͽ�*/
    USB_UINT stat_usb_id_remove_chain;                 /*ID �Ƴ�*/
    USB_UINT stat_usb_otg_fast_off;                      /*����ٹػ������ж�*/
    USB_UINT stat_usb_otg_fast_on;                       /*�˳��ٹػ�ʹ���ж�*/
    USB_UINT stat_usb_kick_timeout ;                        /*������jiffies*/
};
struct otg_dev
{
    OTG_DEVICE_TYPE dev_type;
    USB_INT status;
};
struct otg_dev_det
{
    USB_INT platform;                   /*ƽ̨����*/
    /*otg detect basic elements*/
    USB_INT id;                         /*USB ID״̬*/
    USB_INT old_id;
    USB_INT vbus;                       /*VUBS ״̬*/
    USB_INT host;                       /*�����Ƿ���host ģʽ*/
    USB_INT phy_id;                     /*����Ƿ�Ҫ�л���host*/

    USB_INT id_det_gpio;                /*���OTG �豸Ӳ���ж�*/
    USB_ULONG id_irqflags;              /*id �жϴ�����ʽ����*/
    USB_INT id_irq_shared;              /*id �жϺ��Ƿ���*/

    USB_INT notify_event;               /*�ϱ���Ӧ�õ��¼�*/
    USB_INT charge_type;
    USB_INT otg_remove_flag;         /*��¼otg �豸�γ���vbus �µ����*/
    // USB_INT phy_in_lpm;                 /*usb оƬ�Ƿ��ڵ͵�ģʽ*/
    struct wake_lock id_wake_lock;
    struct delayed_work otg_id_detect_work;   /*OTG �豸����ж��°벿*/


    /* protects detect process*/
    //spinlock_t            lock;
    //spinlock_t            notify_lock;
    //wait_queue_head_t wait_wq;

    struct otg_debug debug;
    USB_UINT32 otg_feature;
    struct otg_dev  dev;
    usb_adp_ctx_t* contex;
};

int otg_dev_id_state(void);
void usb_notify_event(unsigned long val, void* v);
void otg_dev_set_remove_flags(int remove_flag);
int otg_dev_get_remove_flags(void);

USB_INT usb_otg_device_detect_init(USB_VOID);
USB_VOID usb_otg_device_detect_exit(USB_VOID);
OTG_CRADLE_TYPE usb_otg_get_cradle_type();
OTG_DEVICE_TYPE usb_otg_get_device_type();
USB_VOID usb_otg_set_device_type();
USB_VOID usb_otg_pogopin_set();
USB_VOID usb_otg_pogopin_clean();
#endif

