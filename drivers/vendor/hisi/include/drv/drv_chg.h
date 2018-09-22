


#ifndef __DRV_CHG_H__
#define __DRV_CHG_H__

#include "drv_comm.h"
#include "product_config.h"

/*************************CHGģ��START********************************/

/*****************************************************************************
 �� �� ��  : BSP_CHG_GetCbcState
 ��������  : ���ص��״̬�͵���
 �������  :pusBcs 0:����ڹ��� 1:�������ӵ��δ���� 2:û����������
                          pucBcl  0:���������û����������
 �������  : pusBcs 0:����ڹ��� 1:�������ӵ��δ���� 2:û����������
                          pucBcl  0:���������û����������
 ����ֵ��   0 �����ɹ�
                         -1����ʧ��

*****************************************************************************/
extern int BSP_CHG_GetCbcState(unsigned char *pusBcs,unsigned char *pucBcl);
extern int DRV_CHG_GET_CBC_STATE(unsigned char *pusBcs,unsigned char *pucBcl);

typedef enum CHARGING_STATE_ENUM_tag
{
        CHARGING_INIT = -1,
        NO_CHARGING_UP = 0,  /*����δ���*/
        CHARGING_UP ,              /*���������*/
        NO_CHARGING_DOWN ,  /*�ػ�δ���*/
        CHARGING_DOWN         /*�ػ�δ���*/
}CHARGING_STATE_ENUM;

typedef enum BATT_LEVEL_ENUM_tag
{
        BATT_INIT = -2,
        BATT_LOW_POWER =-1,    /*��ص͵�*/
        BATT_LEVEL_0,                 /*0���ص���*/
        BATT_LEVEL_1,                  /*1���ص���*/
        BATT_LEVEL_2,                   /*2���ص���*/
        BATT_LEVEL_3,                    /*3���ص���*/
        BATT_LEVEL_4,                    /*4���ص���*/
        BATT_LEVEL_MAX
}BATT_LEVEL_ENUM;

/*��ظ����ϱ��¼�*/
#if (MBB_CHARGE == FEATURE_ON)
typedef enum _TEMP_EVENT
{
   TEMP_BATT_LOW,    /* ��ص����¼� */
   TEMP_BATT_HIGH,   /* ��ظ����¼� */
   TEMP_BATT_NORMAL, /* ��ظ��½���¼� */
   TEMP_BATT_MAX     /* ����¼�ֵ��С�ڴ�ֵ����Ϊ�Ƿ��¼�*/
}TEMP_EVENT;
#endif
typedef struct BATT_STATE_tag
{
    CHARGING_STATE_ENUM  charging_state;
    BATT_LEVEL_ENUM           battery_level;
#if (MBB_CHARGE == FEATURE_ON)
    TEMP_EVENT      batt_temp_state;
#endif
}BATT_STATE_T;
/**********Charge Module Return Code Macros**********/
#define CHG_OK                 0
#define CHG_ERROR              (-1)
#if (MBB_CHARGE == FEATURE_OFF)
/*AT ����ö������*/
typedef enum
{
    CHG_AT_BATTERY_CHECK,        /* BatteryУ׼*/
    CHG_AT_BATTERY_LEVEL,        /* Battery���� */
    CHG_AT_BATTERY_ADC,          /* Battery Temperature����*/
    CHG_AT_BATTERY_CAPACITY,     /* Battery Capacity*/
    CHG_AT_BATTERY_INVALID
} ENUM_CHG_ATCM_TYPE;
#endif
typedef enum ENUM_POWER_ON_MODE_tag
{
    POWER_ON_INVALID = 0,          	/* ��Ч����ģʽ*/
    POWER_ON_NORMAL,       	 	/* ��������ģʽ*/
    POWER_ON_CHARGING,       	/* �ػ����ģʽ*/
    POWER_ON_MAX
} ENUM_POWER_ON_MODE;
/**********************************************************************
�� �� ��  :chg_get_batt_level
��������  : ��ȡ��ǰ��ص��������Ľӿں���
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : ��ص�������
ע������  : �ޡ�
***********************************************************************/
#if (MBB_CHARGE == FEATURE_ON)
extern BATT_LEVEL_ENUM chg_get_batt_level(void);
unsigned char chg_is_powdown_charging (void);
#endif


#define  NV_BATT_VOLT_CALI_I           (58639)
#define  TBAT_CHECK_INVALID            (0xFFFF)
#if (MBB_CHARGE == FEATURE_ON)
/*���У׼�������ݽṹ*/
typedef struct
{
    unsigned short min_value;
    unsigned short max_value;
}VBAT_CALIBRATION_TYPE;
/*AT�����ȡ��ص�ѹö������*/
typedef enum
{
    CHG_AT_BATTERY_LEVEL,        /* Battery Voltage after Calibration*/
    CHG_AT_BATTERY_ADC,          /* Battery Voltage before Calibration*/
    CHG_AT_BATTERY_CAPACITY,     /* Battery Capacity*/
    CHG_AT_BATTERY_CHECK,        /* Battery Calibration*/
    CHG_AT_BATTERY_INVALID
} ENUM_CHG_ATCM_TYPE;
typedef enum
{
    CHG_AT_CHARGE_DISALBE,        /* disable charge*/
    CHG_AT_CHARGE_ENABLE,         /* enable charge*/
    CHG_AT_DISCHARGE_DISALBE,     /* disable discharge*/
    CHG_AT_DISCHARGE_ENABLE,      /* enable discharge*/
    CHG_AT_START_CHARGE_SPLY,     /* start charge supply*/
    CHG_AT_CHARGE_MODE_INVALID
} ENUM_CHG_MODE_TYPE;
typedef enum 
{
    NO_BATT_MODE = 0,          /*�޵��*/
    KNOCK_DOWN_BATT_MODE = 1,  /*�ɲ�ж���*/
    FIX_BATT_MODE = 2,         /*һ�廯���*/  
    INVALID_BATT_MODE  
    }BATT_FIX_MODE;
/*��ѯ���״̬��ģʽ*/
typedef struct
{
    int chg_state;
    int chg_mode;
}CHG_TCHRENABLE_TYPE;

int app_get_battery_state(BATT_STATE_T *battery_state);
/**********************************************************************
�� �� ��  : chg_tbat_read
��������  : AT���ӿ�
�������  : ������ʽ:��(У׼ǰ/��)��ص������Ƕ���ѹУ׼ֵ
�������  : ��ص���/��ص�ѹУ׼ֵ
�� �� ֵ  : �Ƿ�����ɹ�
ע������  : 
***********************************************************************/
int chg_tbat_read(ENUM_CHG_ATCM_TYPE atID, void *pItem);
/**********************************************************************
�� �� ��  : chg_tbat_write
��������  : ATд�ӿ�:���õ�ص���У׼ֵ
�������  : 4.2V��3.4V��Ӧ��ADC����ֵ
�������  : ��
�� �� ֵ  : �Ƿ�����ɹ�
ע������  : ��
***********************************************************************/
int chg_tbat_write(ENUM_CHG_ATCM_TYPE atID, void *pItem);
/**********************************************************************
�� �� ��  : chg_tbat_charge_mode_set
��������  : ���õ�س����߷ŵ�
�������  : �������
�������  : none
�� �� ֵ  : CHG_OK:success,CHG_ERROR:fail
ע������  : 
***********************************************************************/
int chg_tbat_charge_mode_set(ENUM_CHG_MODE_TYPE cmd, unsigned int arg);
/**********************************************************************
�� �� ��  :  chg_tbat_status_get
��������  :  TBAT AT^TCHRENABLE?�Ƿ���Ҫ����
�������  : ��
�������  : ��
�� �� ֵ      : 1:��Ҫ����
			    0:����Ҫ����
ע������  : ��
***********************************************************************/
int chg_tbat_is_batt_status_ok(void);
/**********************************************************************
�� �� ��  : chg_tbat_get_charging_status
��������  : ��ѯ��ǰ���״̬
�������  : none
�������  : none
�� �� ֵ  : 1:charging,0:no
ע������  : 
***********************************************************************/
int chg_tbat_get_charging_status(void);
/**********************************************************************
�� �� ��  : chg_tbat_get_charging_status
��������  : ��ѯ��ǰ���ģʽ
�������  : none
�������  : none
�� �� ֵ  : 0:�ǳ�磻1��丳䣻2�����
ע������  : 
***********************************************************************/
int chg_tbat_get_charging_mode(void);
/**********************************************************************
�� �� ��  : chg_tbat_get_discharging_status
��������  : ��ѯ��ǰ�Ƿ���suspendģʽ
�������  : none
�������  : none
�� �� ֵ  : 1:yes,0:no
ע������  : 
***********************************************************************/
int chg_tbat_get_discharging_status(void);
/**********************************************************************
�� �� ��  : chg_tbat_sfeature_inquiry_extchg
��������  : ��ѯ�Ƿ�֧�ֶ�����
�������  : none
�������  : none
�� �� ֵ  : 1:yes,0:no
ע������  : 
***********************************************************************/
int chg_tbat_sfeature_inquiry_extchg(void);
/**********************************************************************
�� �� ��  : chg_tbat_sfeature_inquiry_wireless
��������  : ��ѯ�Ƿ�֧�����߳��
�������  : none
�������  : none
�� �� ֵ  : 1:yes,0:no
ע������  : 
***********************************************************************/
int chg_tbat_sfeature_inquiry_wireless(void);
/*****************************************************************************
 �� �� ��  : get_coul_support
 ��������  : ��Ʒ�Ƿ�֧�ֿ��ؼ�
 �������  : none
 �������  : none
 �� �� ֵ  : TRUE:֧�� FALSE:��֧��
 ע������  :
*****************************************************************************/
int get_coul_support(void);
/*****************************************************************************
 �� �� ��  : hw_sys_shut_down
 ��������  : ����GPIO_2-16,ʵ��Ӳ���ػ�
 �������  : none
 �������  : none
 �� �� ֵ  : �ɹ�: 0
             ʧ��: -1
*****************************************************************************/
int hw_sys_shut_down(void);
/**********************************************************************
�� �� ��  : chg_tbat_sfeature_inquiry_battery
��������  : ��ѯ��ص�ѹ����ֵ
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_tbat_sfeature_inquiry_battery(void);
/**********************************************************************
�� �� ��  : chg_MNTN_get_batt_state
��������  : AT���ӿ�
�������  : ��ѯ�Ƿ��ǿɲ�ж���
�������  : none
�� �� ֵ  : 1:�ɲ�ж��2�����ɲ�ж
ע������  : 
***********************************************************************/
int chg_MNTN_get_batt_state(void);
/**********************************************************************
�� �� ��  : chg_wireless_mmi_test
��������  : AT���ӿڣ����߳���·���
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_wireless_mmi_test(void);
/**********************************************************************
�� �� ��  : chg_extchg_mmi_test
��������  : AT���ӿڣ��������·���
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_extchg_mmi_test(void);
/**********************************************************************
�� �� ��  : chg_extchg_mmi_test
��������  : AT���ӿڣ���ȡAT^TCHRENABLE���õĽ��
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_tbat_get_tchrenable_status(CHG_TCHRENABLE_TYPE *tchrenable_state);
/************************************************************************  
�� �� ��  : chg_getCbcState
��������  : ��������AT^CBC
         pucBcs
            0: ����ڹ���
            1: �������ӵ��δ����
            2: û����������
         pucBcl
            0:���������û����������
             100: ʣ������ٷֱ�
�������  : none
�������  : pucBcs��pucBcl
�� �� ֵ  : 
ע������  : 0 Success, -1 failed  
 ***********************************************************************/
int chg_getCbcState(unsigned char  *pucBcs ,unsigned char   *pucBcl);
#else

typedef enum
{
    CHG_AT_CHARGE_MODE_INVALID
} ENUM_CHG_MODE_TYPE;

/*��ѯ���״̬��ģʽ*/
typedef struct
{
    int chg_state;
    int chg_mode;
}CHG_TCHRENABLE_TYPE;

static INLINE int app_get_battery_state(BATT_STATE_T *battery_state)
{
    return 0;
}
/*****************************************************************************
 �� �� ��  : get_coul_support
 ��������  : ��Ʒ�Ƿ�֧�ֿ��ؼ�
 �������  : none
 �������  : none
 �� �� ֵ  : TRUE:֧�� FALSE:��֧��
 ע������  :
*****************************************************************************/
static INLINE int get_coul_support(void)
{
    return 0;
}
/*****************************************************************************
 �� �� ��  : hw_sys_shut_down
 ��������  : ����GPIO_2-16,ʵ��Ӳ���ػ�
 �������  : none
 �������  : none
 �� �� ֵ  : �ɹ�: 0
             ʧ��: -1
*****************************************************************************/
static INLINE int hw_sys_shut_down(void)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_tbat_read
��������  : AT���ӿ�
�������  : ������ʽ:��(У׼ǰ/��)��ص������Ƕ���ѹУ׼ֵ
�������  : ��ص���/��ص�ѹУ׼ֵ
�� �� ֵ  : �Ƿ�����ɹ�
ע������  : 
***********************************************************************/
static INLINE int chg_tbat_read(ENUM_CHG_ATCM_TYPE atID, void *pItem)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_tbat_write
��������  : ATд�ӿ�:���õ�ص���У׼ֵ
�������  : 4.2V��3.4V��Ӧ��ADC����ֵ
�������  : ��
�� �� ֵ  : �Ƿ�����ɹ�
ע������  : ��
***********************************************************************/
static INLINE int chg_tbat_write(ENUM_CHG_ATCM_TYPE atID, void *pItem)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_tbat_charge_mode_set
��������  : ���õ�س����߷ŵ�
�������  : �������
�������  : none
�� �� ֵ  : CHG_OK:success,CHG_ERROR:fail
ע������  : 
***********************************************************************/
static INLINE int chg_tbat_charge_mode_set(ENUM_CHG_MODE_TYPE cmd, unsigned int arg)
{
    return 0;
}
/**********************************************************************
�� �� ��  :  chg_tbat_status_get
��������  :  TBAT AT^TCHRENABLE?�Ƿ���Ҫ����
�������  : ��
�������  : ��
�� �� ֵ      : 1:��Ҫ����
			    0:����Ҫ����
ע������  : ��
***********************************************************************/
static INLINE int chg_tbat_is_batt_status_ok(void)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_tbat_get_charging_status
��������  : ��ѯ��ǰ���״̬
�������  : none
�������  : none
�� �� ֵ  : 1:charging,0:no
ע������  : 
***********************************************************************/
static INLINE int chg_tbat_get_charging_status(void)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_tbat_get_charging_status
��������  : ��ѯ��ǰ���ģʽ
�������  : none
�������  : none
�� �� ֵ  : 0:�ǳ�磻1��丳䣻2�����
ע������  : 
***********************************************************************/
static INLINE int chg_tbat_get_charging_mode(void)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_tbat_get_discharging_status
��������  : ��ѯ��ǰ�Ƿ���suspendģʽ
�������  : none
�������  : none
�� �� ֵ  : 1:yes,0:no
ע������  : 
***********************************************************************/
static INLINE int chg_tbat_get_discharging_status(void)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_tbat_sfeature_inquiry_extchg
��������  : ��ѯ�Ƿ�֧�ֶ�����
�������  : none
�������  : none
�� �� ֵ  : 1:yes,0:no
ע������  : 
***********************************************************************/
static INLINE int chg_tbat_sfeature_inquiry_extchg(void)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_tbat_sfeature_inquiry_wireless
��������  : ��ѯ�Ƿ�֧�����߳��
�������  : none
�������  : none
�� �� ֵ  : 1:yes,0:no
ע������  : 
***********************************************************************/
static INLINE int chg_tbat_sfeature_inquiry_wireless(void)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_tbat_sfeature_inquiry_battery
��������  : ��ѯ��ص�ѹ����ֵ
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
static INLINE int chg_tbat_sfeature_inquiry_battery(void)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_MNTN_get_batt_state
��������  : AT���ӿ�
�������  : ��ѯ�Ƿ��ǿɲ�ж���
�������  : none
�� �� ֵ  : 1:�ɲ�ж��2�����ɲ�ж
ע������  : 
***********************************************************************/
static INLINE int chg_MNTN_get_batt_state(void)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_wireless_mmi_test
��������  : AT���ӿڣ����߳���·���
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
static INLINE int chg_wireless_mmi_test(void)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_extchg_mmi_test
��������  : AT���ӿڣ��������·���
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
static INLINE int chg_extchg_mmi_test(void)
{
    return 0;
}
/**********************************************************************
�� �� ��  : chg_extchg_mmi_test
��������  : AT���ӿڣ���ȡAT^TCHRENABLE���õĽ��
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
static INLINE int chg_tbat_get_tchrenable_status(CHG_TCHRENABLE_TYPE *tchrenable_state)
{
    return 0;
}
/************************************************************************  
�� �� ��  : chg_getCbcState
��������  : ��������AT^CBC
         pucBcs
            0: ����ڹ���
            1: �������ӵ��δ����
            2: û����������
         pucBcl
            0:���������û����������
             100: ʣ������ٷֱ�
�������  : none
�������  : pucBcs��pucBcl
�� �� ֵ  : 
ע������  : 0 Success, -1 failed  
 ***********************************************************************/
static INLINE int chg_getCbcState(unsigned char  *pucBcs ,unsigned char   *pucBcl)
{
    return 0;
}
#endif
/*****************************************************************************
 �� �� ��  : BSP_CHG_GetBatteryState
 ��������  :��ȡ�ײ���״̬��Ϣ
 �������  :battery_state ������Ϣ
 �������  :battery_state ������Ϣ
 ����ֵ��   0 �����ɹ�
                         -1����ʧ��

*****************************************************************************/
extern int BSP_CHG_GetBatteryState(BATT_STATE_T *battery_state);
extern int DRV_CHG_GET_BATTERY_STATE(BATT_STATE_T *battery_state);

/*****************************************************************************
 �� �� ��  : BSP_CHG_ChargingStatus
 ��������  :��ѯĿǰ�Ƿ����ڳ����
 �������  :��
 �������  :��
 ����ֵ��   0 δ���
                          1 �����
*****************************************************************************/
extern int BSP_CHG_ChargingStatus(void);
extern int DRV_CHG_GET_CHARGING_STATUS(void);

/*****************************************************************************
 �� �� ��  : BSP_CHG_StateSet
 ��������  :ʹ�ܻ��߽�ֹ���
 �������  :ulState      0:��ֹ���
 						1:ʹ�ܳ��
 �������  :��
 ����ֵ��    ��
*****************************************************************************/
extern void DRV_CHG_STATE_SET(unsigned long ulState);

/*****************************************************************************
 �� �� ��  : BSP_CHG_StateGet
 ��������  :��ѯ
 �������  :
 �������  :��
 ����ֵ��    ��
*****************************************************************************/
extern BSP_S32 BSP_CHG_StateGet(void);
#define DRV_CHG_STATE_GET()    BSP_CHG_StateGet()

/*****************************************************************************
 �� �� ��  : BSP_CHG_Sply
 ��������  :��ѯ
 �������  :
 �������  :��
 ����ֵ��    ��
*****************************************************************************/
extern BSP_S32 BSP_CHG_Sply(void);
#define DRV_CHG_BATT_SPLY()    BSP_CHG_Sply()


/*****************************************************************************
* �� �� ��  : BSP_TBAT_Read
* ��������  :
* �������  :
* �������  :
* �� �� ֵ  :
* �޸ļ�¼  :
*****************************************************************************/
extern BSP_S32 BSP_TBAT_Read(ENUM_CHG_ATCM_TYPE atID, void *pItem);

/*****************************************************************************
* �� �� ��  : BSP_TBAT_Write
* ��������  :
* �������  :
* �������  :
* �� �� ֵ  :
*****************************************************************************/
extern BSP_S32 BSP_TBAT_Write(ENUM_CHG_ATCM_TYPE atID, void *pItem);

/**********************************************************************
�� �� ��      : BSP_TBAT_CHRStGet
��������  :  TBAT AT^TCHRENABLE?�Ƿ���Ҫ����

�������  : ��
�������  : ��
�� �� ֵ      : 1:��Ҫ����
			      0:����Ҫ����
ע������  : ��
***********************************************************************/
extern BSP_S32 BSP_TBAT_CHRStGet(void);

/**********************************************************************
�� �� ��      : BSP_TBAT_CHRSuply
��������  :  TBAT AT^TCHRENABLE=4����ʵ��
            			��Ҫ�ṩ����ɹ�LCD��ʾͼ��
�������  : ��
�������  : ��
�� �� ֵ      :
ע������  : ��
***********************************************************************/
extern BSP_S32 BSP_TBAT_CHRSply(void);

/**********************************************************************
�� �� ��      : BSP_ONOFF_StartupModeGet
��������  :  A���жϿ��ػ�ģʽ

�������  : ��
�������  : ��
�� �� ֵ      :
ע������  : ��
***********************************************************************/
ENUM_POWER_ON_MODE BSP_ONOFF_StartupModeGet( void );
/*****************************************************************************
* �� �� ��  : BSP_PMU_BattCali
*
* ��������  : ���У׼ǰ��С��������ӿڣ���AT����
*
* �������  :
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
extern void BSP_PMU_BattCali(void);



static INLINE BSP_S32 BSP_MNTN_GetBattState(void)
{
	return 0;
}
#define DRV_MNTN_GET_BATT_STATE() BSP_MNTN_GetBattState()


/*************************CHGģ�� END*********************************/

#endif

