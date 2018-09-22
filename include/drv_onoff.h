

#ifndef __DRV_ONOFF_H__
#define __DRV_ONOFF_H__

#include "product_config.h"
#include "drv_comm.h"

#ifdef __KERNEL__
#include <osl_list.h>

struct bsp_onoff_callback {
    struct list_head node;
    void (*fn)(void);
};

void bsp_reboot_callback_register(void (*hook)(void));
#endif

/* TAF��Ҫ��������ӿڣ�������������1 */
int  bsp_start_mode_get( void );
#define DRV_START_MODEGET(void) bsp_start_mode_get(void)
#if (MBB_CHARGE == FEATURE_OFF)
typedef enum
{
    DRV_START_MODE_CHARGING = 0, /* ��翪��ģʽ, ps ��ҵ������  */
    DRV_START_MODE_NORMAL ,     /* ��������ģʽ������ҵ������     */
    DRV_START_MODE_UPDATE,      /* ����ģʽ */
    DRV_START_MODE_BUILT
}DRV_START_MODE;
#else

typedef enum DRV_START_MODE_tag
{
     DRV_START_MODE_EXCEPTION,  /* �쳣����ģʽ����ʱ�󲿷�ҵ�񶼲�����, ����ʾ��Ϣ */
     DRV_START_MODE_NORMAL,   /*��������*/
     DRV_START_MODE_CHARGING,   /* ��翪��ģʽ, ps ��ҵ������  */
     DRV_START_MODE_NOAPP,      /*SD�������ڶ�������������APP*/
     DRV_START_MODE_BUTT
}DRV_START_MODE;
#define DRV_START_MODE_UPDATE    DRV_START_MODE_NOAPP
#define DRV_START_MODE_BUILT     DRV_START_MODE_BUTT
#endif

void bsp_drv_power_off(void);
#define DRV_POWER_OFF(void) bsp_drv_power_off(void)

void bsp_drv_power_reboot( void );
void bsp_drv_power_reboot_direct( void );
#if (FEATURE_ON == MBB_COMMON)
void power_on_wdt_cnt_set( void );
#endif

#if (MBB_CHARGE == FEATURE_OFF)
typedef enum DRV_SHUTDOWN_REASON_tag_s
{
    DRV_SHUTDOWN_POWER_KEY,             /* ���� Power ���ػ�          */
    DRV_SHUTDOWN_BATTERY_ERROR,         /* ����쳣                   */
    DRV_SHUTDOWN_LOW_BATTERY,           /* ��ص�����                 */
    DRV_SHUTDOWN_TEMPERATURE_PROTECT,   /* ���±����ػ�               */
    DRV_SHUTDOWN_CHARGE_REMOVE,         /* �ػ����ģʽ�£��γ������ */
    DRV_SHUTDOWN_UPDATE,                /* �ػ�����������ģʽ         */
    DRV_SHUTDOWN_RESET,                 /* ϵͳ��λ                 */
    DRV_SHUTDOWN_BUTT
}DRV_SHUTDOWN_REASON_ENUM;
#else

typedef enum DRV_SHUTDOWN_REASON_tag_s
{
    DRV_SHUTDOWN_LOW_BATTERY,           /* ��ص�����                 */
    DRV_SHUTDOWN_BATTERY_ERROR,         /* ����쳣                   */
    DRV_SHUTDOWN_POWER_KEY,             /* ���� Power ���ػ�          */
    DRV_SHUTDOWN_TEMPERATURE_PROTECT,   /* ���±����ػ�               */
    DRV_SHUTDOWN_LOW_TEMP_PROTECT,
    DRV_SHUTDOWN_RESET,                 /* ϵͳ��λ                 */
    DRV_SHUTDOWN_CHARGE_REMOVE,         /* �ػ����ģʽ�£��γ������ */
    DRV_SHUTDOWN_UPDATE,                /* �ػ�����������ģʽ         */
    DRV_SHUTDOWN_BUTT
}DRV_SHUTDOWN_REASON_ENUM;
#endif

#if (MBB_CHARGE == FEATURE_ON)
void bsp_drv_set_power_off_reason(DRV_SHUTDOWN_REASON_ENUM eReason);
#endif

typedef enum {
    DRV_START_REASON_CHARGE = 0,
    DRV_START_REASON_POWER_KEY ,
    DRV_START_REASON_WARM_RESET ,
    DRV_START_REASON_BUTT
}DRV_START_REASON;

/*****************************************************************************
 �� �� ��  : DRV_SHUT_DOWN
 ��������  : ����ػ�
 �������  : ��
 �������  : eReason��        �ػ�ԭ��
 �� �� ֵ  : ��
*****************************************************************************/
void drv_shut_down( DRV_SHUTDOWN_REASON_ENUM eReason );
#define DRV_SHUT_DOWN(eReason) drv_shut_down(eReason)
#define drvShutdown(eReason)   drv_shut_down(eReason)

typedef enum
{
    NORMAL_VERTYPE_FLAG = 0,       /* ��ǰ�汾Ϊ�����汾 */
    FACTORY_VERTYPE_FLAG,          /* ��ǰ�汾Ϊ�����汾 */
    INVALID_VERTYPE_FLAG
}DRV_SOFT_VER_TYPE;

typedef enum
{
    NORMAL_CHARGING_MODE = 0,          /* �������ģʽ */
    POWER_DOWN_CHARGING_MODE,         /* �ػ����ģʽ */
    INVALID_CHARGING_MODE
}DRV_CHARGING_MODE;

typedef enum
{
    NORMAL_RESET_FLAG = 0,         /* ������λ�汾 */
    ABNORMAL_RESET_FLAG,           /* �쳣��λ�汾 */
    INVALID_RESET_FLAG
}DRV_RESET_TYPE;

typedef enum
{
    RUN_MODE_NORMAL = 0,         /* �����汾 */
    RUN_MODE_RECOVERY,           /* RECOVERY */
    RUN_MODE_INVALID
}DRV_RUN_MODE;

#endif

