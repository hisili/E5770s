


#ifndef _wlan_if_h_
#define _wlan_if_h_

#include <linux/signal.h>
#include "wlan_utils.h"
#include <linux/interrupt.h>
#if (FEATURE_ON == MBB_WIFI_CHIP_REGULAR)
#include "wlan_drv_if.h"
#endif

#if ((rtl8192 == MBB_WIFI_CHIP1) || (rtl8189 == MBB_WIFI_CHIP1))
#define    WLAN_CACHE_CFGFILE_SIZE         4
typedef struct wlan_mem_cache{
    void *recv;                                  /* �����н����ļ����� */
    void *cfgfile[WLAN_CACHE_CFGFILE_SIZE];      /* �����е�cfgfile���� */
}wlan_mem_cache_st;
#endif

#define    WLAN_TRACE_INFO(fmt, ...)    printk(fmt, ##__VA_ARGS__)
#define    WLAN_TRACE_ERROR(fmt, ...)    printk(fmt, ##__VA_ARGS__)

/* �ж��Ƿ����SDIO�ӿڵ�WiFiоƬ */
#define   IS_SDIO_CHIP(chip) ((chip == bcm43362) \
                            || (chip == bcm4354)   \
                            || (chip == rtl8189)   \
                            || (chip == rtl8192))  
#define  CONFIG_WIFI_SDIO (IS_SDIO_CHIP(MBB_WIFI_CHIP1) || IS_SDIO_CHIP(MBB_WIFI_CHIP2)) 

/* signal report */
typedef enum
{
    WIFI_SIGNAL_UPDATE_STA_LIST    = SIGIO,   /* WiFi STA�б���� */
    WIFI_SIGNAL_AUTO_SHUTDOWN      = SIGUSR2,   /* WiFi�Զ��ر��ź� */
}WLAN_SIGNAL_EVENT_ENUM;

/* event report */
typedef enum _WLAN_EVENT_TYPE
{
    USER_WIFI_TIMEOUT_EVENT         = 1,         /* WiFi�Զ��ر���Ϣ */
    USER_WIFI_UPDATE_STA_LIST       = 2,         /* STA������������¼� */
    USER_WIFI_DATA_DEAD_EVENT       = 32,        /* ���Ƶ���FW�쳣�ϱ� */
    USER_WIFI_CTRL_DEAD_EVENT       = 33,        /* ��������FW�쳣�ϱ� */
    USER_WIFI_NULL_EVENT = ((unsigned int)-1),   /* ���¼� */
}WLAN_EVENT_TYPE;

typedef struct _wlan_user_event
{
    WLAN_EVENT_TYPE eventId;
    unsigned int eventVal;
} WLAN_USER_EVENT;

 /* WiFiоƬ״̬���ṹ��,DHD�л�����ͬ�ṹ��Ķ���*/
 typedef struct
 {
     unsigned int rxerror;
     unsigned int txerror;
     unsigned int cmderror;
 }WLAN_STATUS_STU;


 /*===========================================================================
 
                         ������������
 
 ===========================================================================*/

/*****************************************************************************
 ��������  : WLAN_RETURN_TYPE wlan_signal_report(WiFi_SIGNAL_EVENT_ENUM signal)
 ��������  : ��Ӧ�ò㷢���ź�
 �������  : NA
 �������  : NA
 �� �� ֵ  : ��ǰ����WiFi����ֵ
*****************************************************************************/
WLAN_RETURN_TYPE wlan_signal_report(WLAN_SIGNAL_EVENT_ENUM signal);

/*****************************************************************************
 ��������  : WLAN_RETURN_TYPE wlan_event_report(WLAN_USER_EVENT *event)
 ��������  : ��Ӧ�ò㷢���¼�
 �������  : NA
 �������  : NA
 �� �� ֵ  : ��ǰ����WiFi����ֵ
*****************************************************************************/
WLAN_RETURN_TYPE wlan_event_report(WLAN_USER_EVENT *event);

/*****************************************************************************
 ��������  : wlan_nv_read_pow
 ��������  : ͬƽ̨��ȡPOW��NV����
 �������  : pstPow: power�ṹ��uLen: �ṹ����
 �������  : pstPow: power�ṹ��Ϣ
 �� �� ֵ  : NA
*****************************************************************************/
int wlan_nv_read_pow(void * pstPow, unsigned uLen);
/* ����V7ƽ̨֧��ͨ��NV��ʽ����Power */
#define WLAN_NV_READ_POW(pstPow, uLen) wlan_nv_read_pow(pstPow, uLen)

/*****************************************************************************
 ��������  : wlan_request_wakeup_irq
 ��������  : WiFi����BB �ж�ע��ӿ�
 �������  : handler: �жϻص�������devname: �豸���ƣ�dev:�ж���Ӧ����
 �������  : NA
 �� �� ֵ  : int
*****************************************************************************/
unsigned int wlan_request_wakeup_irq(irq_handler_t handler, const char *devname, void *dev);

/*****************************************************************************
 ��������  : wlan_free_irq
 ��������  : WiFi����BB �ж��ͷŽӿ�
 �������  : irq: �ж�id
 �������  : NA
 �� �� ֵ  : int
*****************************************************************************/
void wlan_free_irq(unsigned int irq, void *dev);

/*****************************************************************************
 ��������  : wlan_set_driver_lock
 ��������  : WiFi drv ͶƱ�ӿ�
 �������  : locked: �Ƿ�����ϵͳ������������
 �������  : NA
 �� �� ֵ  : locked
*****************************************************************************/
void wlan_set_driver_lock(int locked);

#if (FEATURE_ON == MBB_WIFI_CHIP_REGULAR)
/**********************************************************************
�� �� ��  :bsp_get_product_wifi_chip_type
��������  : �б𵥰��WiFiоƬ����
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ     : WIFI_CHIP_TYPE ����
ע������  : �ޡ�
***********************************************************************/
WIFI_CHIP_TYPE wlan_get_product_wifi_chip_type();
/**********************************************************************
�� �� ��  :wlan_get_product_wifi_hw_id
��������  : ��ȡ�����Ӳ��id
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ     : Ӳ��id 
ע������  : �ޡ�
***********************************************************************/
u32   wlan_get_product_wifi_hw_id();
#endif
#endif


