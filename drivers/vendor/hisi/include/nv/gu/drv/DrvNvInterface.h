/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : DrvNvInterface.h
  Description     : DrvNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __DRVNVINTERFACE_H__
#define __DRVNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
/*#include "MODULE_H/drv_global.h"*/

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define DYN_MAX_PORT_CNT          (17)

/* �豸ö�����˿ڸ��� */
//#define DYNAMIC_PID_MAX_PORT_NUM  (17)

#define NV_HW_CFG_LENTH           (0x40)

#ifndef VER_MAX_LENGTH
#define VER_MAX_LENGTH                  30
#endif
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/


/*****************************************************************************
 �ṹ��    : NV_WDT_TIMEOUT_STRU
 �ṹ˵��  : NV_WDT_TIMEOUT�ṹ ID=11
*****************************************************************************/
typedef struct
{
    BSP_U32   ulWdtTimeOut;
}NV_WDT_TIMEOUT_STRU;


/*****************************************************************************
 �ṹ��    : USIM_TEMP_SENSOR_TABLE
 �ṹ˵��  : USIM_TEMP_SENSOR_TABLE�ṹ
*****************************************************************************/
typedef struct
{
    BSP_S16   Temperature;
    BSP_U16   Voltage;
}USIM_TEMP_SENSOR_TABLE;

/*****************************************************************************
 �ṹ��    : USIM_TEMP_SENSOR_TABLE_STRU
 �ṹ˵��  : USIM_TEMP_SENSOR_TABLE�ṹ
*****************************************************************************/
typedef struct
{
    USIM_TEMP_SENSOR_TABLE UsimTempSensorTable[19];
}USIM_TEMP_SENSOR_TABLE_STRU;



/*****************************************************************************
 �ṹ��    : CHG_TEMP_ADC_TYPE
 �ṹ˵��  : CHG_TEMP_ADC_TYPE�ṹ
*****************************************************************************/
typedef struct 
{
    BSP_S16   temperature;
    BSP_U16   voltage;
}CHG_TEMP_ADC_TYPE;

/*****************************************************************************
 �ṹ��    : FACTORY_MODE_TYPE
 �ṹ˵��  : FACTORY_MODE_TYPE�ṹ 
             ����ģʽnv��,0 : ����ģʽ 1: �ǹ���ģʽ 36
*****************************************************************************/
typedef struct
{
    BSP_U32 factory_mode;
}FACTORY_MODE_TYPE;



/*****************************************************************************
 �ṹ��    : NV_BREATH_LED_STR
 �ṹ˵��  : NV_BREATH_LED�ṹ     ID=9051
*****************************************************************************/
typedef struct
{
    BSP_U8 ucBreathOnTime;
    BSP_U8 ucBreathOffTime;
    BSP_U8 ucBreathRiseTime;
    BSP_U8 ucBreathFallTime;
}NV_BREATH_LED_STR;

/*****************************************************************************
 �ṹ��    : CHG_BATTERY_TEMP_PROTECT_NV_TYPE
 �ṹ˵��  : CHG_BATTERY_TEMP_PROTECT_NV_TYPE�ṹ     ID=50016
*****************************************************************************/
typedef struct 
{
    BSP_U32  ulIsEnable;
    BSP_S32  lCloseAdcThreshold;
    BSP_U32  ulTempOverCount;
}CHG_BATTERY_TEMP_PROTECT_NV_TYPE;


/*****************************************************************************
 �ṹ��    : PROIDNvInfo
 �ṹ˵��  : PROIDNvInfo�ṹ     ID=50018,ID=50048
*****************************************************************************/
typedef struct _productIDNvInfo
{
    BSP_U32   NvStatus;
    BSP_U8    ucCompVer[VER_MAX_LENGTH];
} PROIDNvInfo;

/*****************************************************************************
 �ṹ��    : NV_HUAWEI_PCCW_HS_HSPA_BLUE_STRU
 �ṹ˵��  : NV_HUAWEI_PCCW_HS_HSPA_BLUE�ṹ ID=50032
*****************************************************************************/
typedef struct
{
    BSP_U32  NVhspa_hs_blue; /*Range:[0,3]*/
}NV_HUAWEI_PCCW_HS_HSPA_BLUE_STRU;




/*****************************************************************************
 �ṹ��    : nv_huawei_dynamic_pid_type
 �ṹ˵��  : nv_huawei_dynamic_pid_type�ṹ ID=50091 �˿���̬
*****************************************************************************/
typedef struct PACKED_POST
{
    BSP_U32 nv_status;
    BSP_U8  first_port_style[DYNAMIC_PID_MAX_PORT_NUM];
    BSP_U8  rewind_port_style[DYNAMIC_PID_MAX_PORT_NUM];
    BSP_U8  reserved[22];
} nv_huawei_dynamic_pid_type;


/*****************************************************************************
 �ṹ��    : USB_NV_SN_INFO_T
 �ṹ˵��  : USB_NV_SN_INFO_T�ṹ
*****************************************************************************/
typedef struct tagUSB_NV_SN_INFO_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
    BSP_U32 u32USBNvResult;
} USB_NV_SN_INFO_T;

/*****************************************************************************
 �ṹ��    : USB_NV_DEV_INFO_T
 �ṹ˵��  : USB_NV_DEV_INFO_T�ṹ
*****************************************************************************/
typedef struct tagUSB_NV_DEV_INFO_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBDevTypeIdx;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
/*    BSP_U32 u32USBNvResult;*/
} USB_NV_DEV_INFO_T;

/*****************************************************************************
 �ṹ��    : USB_NV_SERIAL_NUM_T
 �ṹ˵��  : USB_NV_SERIAL_NUM_T�ṹ
*****************************************************************************/
typedef struct tagUSB_NV_SERIAL_NUM_T
{
    BSP_U32 u32USBSerialNumSupp;
    BSP_U32 u32USBReserved1;
    BSP_U32 u32USBReserved2;
    BSP_U32 u32USBNvResult;
} USB_NV_SERIAL_NUM_T;

/*****************************************************************************
 �ṹ��    : USB_NV_NEW_PID_INFO_T
 �ṹ˵��  : USB_NV_NEW_PID_INFO_T�ṹ
*****************************************************************************/
typedef struct tagUSB_NV_NEW_PID_INFO_T
{
    BSP_U32 u32USBNewPidSupp;
} USB_NV_NEW_PID_INFO_T;

/*****************************************************************************
 �ṹ��    : USB_NV_PID_UNION_T
 �ṹ˵��  : USB_NV_PID_UNION_T�ṹ
*****************************************************************************/
typedef struct tagUSB_NV_PID_UNION_T
{
    BSP_U32 u32USBNvState;
    BSP_U32 u32USBProtOfs;   /* change from "u32USBVDFCust" to "u32USBProtOfs" */
    BSP_U32 u32USBCdromPid;
    BSP_U32 u32USBUniquePid;
} USB_NV_PID_UNION_T;

/*****************************************************************************
 �ṹ��    : USB_NV_DEV_PROFILE_T
 �ṹ˵��  : USB_NV_DEV_PROFILE_T�ṹ
*****************************************************************************/
typedef struct tagUSB_NV_DEV_PROFILE_T
{
    BSP_U32 u32USBNvState;
    BSP_U8  u8USBFirstPortSeq[DYN_MAX_PORT_CNT];
    BSP_U8  u8USBMultiPortSeq[DYN_MAX_PORT_CNT];
    BSP_U8  u8USBPortReserved[2];
} USB_NV_DEV_PROFILE_T;


/*****************************************************************************
 �ṹ��    : NV_GCF_TYPE_CONTENT_STRU
 �ṹ˵��  : NV_GCF_TYPE_CONTENT�ṹ ID=8250
*****************************************************************************/
typedef struct
{
    BSP_U8 GCFTypeContent[4];
}NV_GCF_TYPE_CONTENT_STRU;



/*****************************************************************************
 �ṹ��    : TEM_VOLT_TABLE
 �ṹ˵��  : TEM_VOLT_TABLE�ṹ
*****************************************************************************/
typedef struct tem_volt_table
{
    BSP_S16   temperature;
    BSP_U16   voltage;
}TEM_VOLT_TABLE;



/*****************************************************************************
 �ṹ��    : NV_TCXO_CFG_STRU
 �ṹ˵��  : NV_TCXO_CFG�ṹ ID=9217
*****************************************************************************/
typedef struct
{
    BSP_U32 tcxo_cfg;
}NV_TCXO_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG_STRU
 �ṹ˵��  : NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG�ṹ ID=9216
*****************************************************************************/
typedef struct
{
    BSP_U16 hkadc[14];
}NV_KADC_PHYTOLOGICAL_CONFIGTCXO_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NV_THERMAL_HKADC_CONFIG
 �ṹ˵��  : NV_THERMAL_HKADC_CONFIG�ṹ ID=9215
*****************************************************************************/
typedef struct
{
    BSP_U16 hkadc[32];
}NV_KADC_CHANNEL_CFG_STRU;
typedef struct
{
    BSP_U32   outconfig;       
    BSP_U16   outperiod;   
    BSP_U16   convertlistlen;  
    BSP_U32   reserved[2];    
}NV_THERMAL_HKADC_CONFIG;

/*****************************************************************************
 �ṹ��    : NV_THERMAL_HKADC_CONFIG_STRU
 �ṹ˵��  : NV_THERMAL_HKADC_CONFIG�ṹ ID=9215
*****************************************************************************/
typedef struct
{
    NV_THERMAL_HKADC_CONFIG   hkadcCfg[14];    
}NV_THERMAL_HKADC_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : NV_THERMAL_BAT_CONFIG_STRU
 �ṹ˵��  : NV_THERMAL_BAT_CONFIG�ṹ ID=9214
*****************************************************************************/
typedef struct
{
    BSP_U16       enable;       
    BSP_U16       hkadcid;      
    BSP_S16       highthres;        
    BSP_U16       highcount;     
    BSP_S16       lowthres;             
    BSP_U16       lowcount;    
    BSP_U32       reserved[2]; 
  
}NV_THERMAL_BAT_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : NV_THERMAL_TSENSOR_CONFIG_STRU
 �ṹ˵��  : NV_THERMAL_TSENSOR_CONFIG�ṹ ID=9213
*****************************************************************************/
typedef struct
{
    BSP_U32       enable;          
    BSP_U32       lagvalue0;
    BSP_U32       lagvalue1;
    BSP_U32       thresvalue0;
    BSP_U32       thresvalue1;
    BSP_U32       rstthresvalue0;
    BSP_U32       rstthresvalue1;
    BSP_U32       alarmcount1;
    BSP_U32       alarmcount2;
    BSP_U32       resumecount;
    BSP_U32       acpumaxfreq;
    BSP_U32       gpumaxfreq;
    BSP_U32       ddrmaxfreq;
    BSP_U32       reserved[4]; 
}NV_THERMAL_TSENSOR_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : NV_TUNER_MIPI_INIT_CONFIG_STRU
 �ṹ˵��  : NV_TUNER_MIPI_INIT_CONFIG_STRU�ṹ ID=10046
*****************************************************************************/
#define TUNER_USER_DATA_MAX_NUM (9)
#define TUNER_MAX_NUM           (2)
typedef struct
{
    BSP_U8 mipiChan;
    BSP_U8 validNum;
    BSP_U16 cmdFrame[TUNER_USER_DATA_MAX_NUM];
    BSP_U16 dataFrame[TUNER_USER_DATA_MAX_NUM];
}NV_TUNER_MIPI_FRAME_CONFIG_STRU;

typedef struct
{
    NV_TUNER_MIPI_FRAME_CONFIG_STRU RFInitReg[TUNER_MAX_NUM];
}NV_GU_RF_FEND_MIPI_INIT_CONFIG_STRU;
/*****************************************************************************
 �ṹ��    : WG_DRX_RESUME_TIME_STRU
 �ṹ˵��  : WG_DRX_RESUME_TIME_STRU�ṹ ID=10031
*****************************************************************************/
typedef struct
{
    unsigned long ulAbbPwrRsmTime;
    unsigned long ulRfPwrRsmTime;
    unsigned long ulAntSwitchPwrRsmTime;
    unsigned long ulAbbWpllRsmTime;
    unsigned long ulAbbGpllRsmTime;
    unsigned long ulBbpPllRsmTime;
    unsigned long ulPaStarRsmTime;
    unsigned long ulSysProtectTime;
    unsigned long ulTcxoRsmTime;
    unsigned long ulDcxoRsmTime;
    unsigned long ulSlowToMcpuRsmTime;
    unsigned long ulWphyRsmTime;
    unsigned long ulGphyRsmTime;
    unsigned long ulTaskSwitchRsmTime;
    unsigned long ulPaPwrRsmTime;
}WG_DRX_RESUME_TIME_STRU;

/*****************************************************************************
 �ṹ��    : NV_NPNP_CONFIG_INFO
 �ṹ˵��  : NV_NPNP_CONFIG_INFO
*****************************************************************************/
typedef struct
{
    BSP_U32 npnp_open_flag;                           /* NPNP ����һ��NV����, 0Ϊδ����������ʹ��, 1Ϊ��������ʹ�� */
    BSP_U32 npnp_enable_flag;                         /* NPNP ���Զ���NV��, 0Ϊ����δʹ��, 1Ϊ����ʹ��             */
}NV_NPNP_CONFIG_INFO;
/*****************************************************************************
 �ṹ��    : NV_RF_GPIO_CFG_STRU
 �ṹ˵��  : RF_GPIO�������ɿ��Ը���ΪDRV_GPIO
             ��һЩ��Ƶ���ܳ�����Ҫ�ı���ЩRF_GPIO���ŵĸ��ù��ܼ����״̬
             ͨ����NV���� ID=10047
*****************************************************************************/
typedef struct
{
    BSP_U16 is_used;    /*Range:[0,1]*/
	BSP_U16 gpio_level; /*Range:[0,1]*/
}RF_MODEM_CONTROL;
typedef struct
{
    BSP_U32 rf_gpio_num;
    RF_MODEM_CONTROL modem_inside;
    RF_MODEM_CONTROL modem_outside;
}RF_GPIO_CFG;
typedef struct
{
    RF_GPIO_CFG rf_switch_cfg[16];
}NV_RF_SWITCH_CFG_STRU;
/*****************************************************************************
 �ṹ��    : NV_RF_ANT_OTG_CFG_STRU
 �ṹ˵��  : ���������������Ȱβ幦����Ҫ���ݲ�ͬ�Ĳ�Ʒ��̬�����Ƿ�򿪣��ܹ�
             ͨ����NV���ã�����ͨ����NV����ʹ����һ��GPIO������Ϊ�ж�����
             ID=10051
*****************************************************************************/
typedef struct
{
    BSP_U16 ANT0_GPIO_NUM;
    BSP_U16 ANT1_GPIO_NUM;
}NV_RF_ANT_OTG_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY
 �ṹ˵��  : NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY ID=148
*****************************************************************************/
typedef struct
{
    BSP_U16         usProductType;/*0:MBB V3R3 stick/E5,etc.; 1:V3R3 M2M & V7R2; 2:V9R1 phone; 3:K3V3&V8R1;*/
    BSP_U16         usRsv;
}NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of DrvNvInterface.h */
