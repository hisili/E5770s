

#ifndef __PRODUCT_NV_DEF_H__
#define __PRODUCT_NV_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define WEB_STR_LEN 36

#define MMA_HUAWEI_PLMN_MODIFY_MAX_SIZE                   (128)
#define TAF_NVIM_MAX_APN_LOCK_LEN                        (99)
#define TAF_NVIM_MAX_APN_LOCK_STR_LEN                    (TAF_NVIM_MAX_APN_LOCK_LEN + 1)
#define TAF_NVIM_HWLOCK_LEN                              (32)
/*��ο��ṹ������*/
typedef struct
{
    BSP_S32 reserved;  /*note */
}PRODUCT_MODULE_STRU;
/*NV50336�ṹ����*/
typedef struct
{
    UINT8 SKU_TYPE;    /*�Ϸ�ȡֵ 0��1��2 0��Voddafone Mobile WiFi;1:Vodafone Pocket WiFi;2:Enterprise None P&P*/
    UINT8 RESERVED;    /*Ԥ��*/
}NV_ITEM_SKU_STRU;

/*NV50337�ṹ����*/
typedef struct
{
    UINT8 ACCOUNT_TYPE;   /*�Ϸ�ȡֵ 0��1��0:Prepay first,contract second;1:Contract first,Prepay second*/
    UINT8 RESERVED;       /*Ԥ��*/
}NV_ITEM_ACCOUNT_STRU;
/*NV50364��ز������ݽṹ**/
typedef struct
{
    BSP_U8 no_battery_powerup_enable;        /*�ǹ���ģʽ�µ�ز���λ����ʹ�ܱ�־*/
    BSP_U8 exception_poweroff_poweron_enable;/*�쳣�ػ����´β����Դ���뿪��ģʽʹ�ܱ�־*/
    BSP_U8 low_battery_poweroff_disable;     /*�͵�ػ���ֹ��־*/
    BSP_U8 reserved;                         /*����*/
}POWERUP_MODE_TYPE;

/*���������¶Ȳ���NV 50385�ṹ����*/
typedef struct
{
    BSP_U32    ulChargeIsEnable;                    //����±���ʹ��    
    BSP_S32     overTempchgStopThreshold;           //�����±�������
    BSP_S32     subTempChgLimitCurrentThreshold;    //���³���������
    BSP_S32     lowTempChgStopThreshold;            //�����±�������
    BSP_S32     overTempChgResumeThreshold;         //�����»ָ��¶�����
    BSP_S32     lowTempChgResumeThreshold;          //�����»ָ��¶�����
    BSP_U32     chgTempProtectCheckTimes;           //���ͣ����ѯ����
    BSP_U32     chgTempResumeCheckTimes;            //��縴����ѯ����
    BSP_S32     exitWarmChgToNormalChgThreshold;    //�ɸ��³��ָ������³���¶�����
    BSP_S32     reserved2;                          //Ԥ��    
}CHG_SHUTOFF_TEMP_PROTECT_NV_TYPE;

/*���������¶Ȳ���NV50386�ṹ����*/
typedef struct
{
    BSP_S32         battVoltPowerOnThreshold;           //������ѹ����
    BSP_S32         battVoltPowerOffThreshold;          //�ػ���ѹ����
    BSP_S32         battOverVoltProtectThreshold;       //ƽ������ѹ��������(ƽ��ֵ)
    BSP_S32         battOverVoltProtectOneThreshold;    //���γ���ѹ��������(����ֵ)
    BSP_S32         battChgTempMaintThreshold;          //���ָ���ͣ�������ͣ����ж�����
    BSP_S32         battChgRechargeThreshold;           //�����θ�������
    BSP_S32         VbatLevelLow_MAX;                   //�͵���������
    BSP_S32         VbatLevel0_MAX;                     //0���ѹ��������
    BSP_S32         VbatLevel1_MAX;                     //1���ѹ��������
    BSP_S32         VbatLevel2_MAX;                     //2���ѹ��������
    BSP_S32         VbatLevel3_MAX;                     //3���ѹ�������� 
    BSP_S32         battChgFirstMaintThreshold;         //�״��ж��Ƿ�����
    BSP_S32         battNormalTempChgRechargeThreshold; //�������临������
}CHG_SHUTOFF_VOLT_PROTECT_NV_TYPE;


typedef struct 
{       
    BSP_U8     FileSysActiveProtectEnable;   /* �ļ�ϵͳ��������ʹ�� */     
    BSP_U8     BadImgResumFromOnlineEnable;   /* �����𻵺��Online�����ָ�ʹ��*/     
    BSP_U8     BootNotOperaFileSysEnable;      /*ϵͳ�������̲����ļ�ϵͳ����ʹ��*/     
    BSP_U8     FastOffFailTrueShutdownEnable;    /*�ٹػ�ʧ�ܽ�����ػ�����ʹ��*/      
    BSP_U8     SoftPowOffReliableEnable;          /*����ػ��ɿ��Թ���ʹ��*/      
    BSP_U8     ZoneWriteProtectEnable;          /*����дԽ�籣��ʹ��*/       
    BSP_U8     BadZoneReWriteEnable;            /* Flash��Σ���д����ʹ��*/       
    BSP_U8     BootCanFromkernelBEnable;  /*�������ƻ�����Դӱ��ݾ�������ʹ��*/
    BSP_U8     OnlineChangeNotUpgradEnable; /*Online�����仯��������������ʹ��*/
    /*Ԥ��*/
    BSP_U8     BadZoneScanEnable;   /* Flash��Σ��ɨ�蹦��ʹ��*/
    BSP_U8     reserved2;
    BSP_U8     reserved3;
    BSP_U8     reserved4;
    BSP_U8     reserved5;
    BSP_U8     reserved6;
    BSP_U8     MmcReliabilityEnable;            /*Э��MMC�ɿ��Ա���ʹ�ܿ���*/
    BSP_U32    MmcReliabilityBitmap;     /* ͨ��Э��Э��MMC�ɿ��Ա����������� */
    BSP_U32    DangerTime;                   /*Ƶ�����µ�Σ���ھ���ֵ ����λΪ��*/       
    BSP_U32    WaitTime;           /*Ӧ��֪ͨ������ٹػ��󣬶�ʱ��ֵ��λΪ��*/
    /*Ԥ��*/
    BSP_S32    reserved7; 
    BSP_S32    reserved8; 
    BSP_S32    reserved9; 
    BSP_S32    reserved10; 
    BSP_S32    reserved11;       
}SOFT_RELIABLE_CFG_STRU;


typedef struct
{
    VOS_UINT8 webSite[WEB_STR_LEN];
}WEB_SITE_STRU;

typedef struct
{
    VOS_UINT8 wpsPin[WEB_STR_LEN];
}WPS_PIN_STRU;

typedef struct
{
    VOS_UINT8 userName[WEB_STR_LEN];
}WEB_USER_NAME_STRU;

#define CUSTOM_MCC_LIST_NUM_MAX                 (30)
typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucCustomMccNum;
    VOS_UINT8                           aucReserve[2];    
    VOS_UINT32                          aulCustommMccList[CUSTOM_MCC_LIST_NUM_MAX];  /* �������εĹ������б� */    
}NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU_EX;


#define DISABLE_RPLMN_ACT_ON       (0)
#define DISABLE_RPLMN_ACT_OFF      (1)
typedef struct
{
    VOS_UINT8                       ucEnableFlag;/*0: Disable RPLMN ACT ���Թر�,1: Disable RPLMN���Դ�*/
    VOS_UINT8                       aucReserve[3];
}NAS_MCC_NVIM_RPLMN_DISABLE_ACT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : GID1_TYPE_STRU
 �ṹ˵��  : ���ڶ���GID1��������
 �ṹ ID   : 50083
*****************************************************************************/
typedef struct
{
    VOS_UINT8   bGID1Enable;                 /*GID1����ʹ��λ*/
    VOS_UINT8   ucLeagalValue;               /*�Ϸ�GID1ֵ*/
}GID1_TYPE_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NV_Vodafone_CPBS
 �ṹ˵��  : �¹� Vodafone CPBS����
 �ṹ ID   : 50429
*****************************************************************************/
typedef struct
{
   VOS_UINT16 Vodafone_CPBS;                 /*����ʹ��λ*/
   VOS_UINT16 Reserved;
}NAS_NV_Vodafone_CPBS;

/*****************************************************************************
 �ṹ��    : TAF_NV_CSIM_CUSTOMIZED
 �ṹ˵��  : AT+CSIM����
 �ṹ ID   : 50189
*****************************************************************************/
typedef struct 
{
     VOS_UINT8  ucNvActiveFlag;     /* NV�����־�ֶ�*/
     VOS_UINT8  ucReserved[3];         /* �����ֶ�*/
} TAF_NV_CSIM_CUSTOMIZED;


typedef struct
{
   VOS_UINT8    ucNvActiveFlag;
   VOS_UINT8    ucReserved[3];            /*�����ֶ�*/
   VOS_UINT32   ulBandGroup1Low32Bit;
   VOS_UINT32   ulBandGroup1High32Bit;
   VOS_UINT32   ulBandGroup2Low32Bit;
   VOS_UINT32   ulBandGroup2High32Bit;
   VOS_UINT32   ulReserved[4];            /*�����ֶΣ����ں�����չ*/
}NAS_NV_CUSTOMIZED_BAND_GROUP;


typedef struct
{
    VOS_UINT8 ucNvimActiveFlg;
    VOS_UINT8 aucReserved[3];                        /*�����ֶ�*/
}NV_ITEM_START_MANUAL_TO_AUTO_ST;


#define MMA_SPECIAL_HPLMN_ITEM_SIZE     (4)      /* ����PLMN�ռ��С*/
#define MMA_SPECIAL_HPLMN_LIST_SIZE     (30)     /* �����Դ洢30��PLMN*/

typedef struct
{
     VOS_UINT8            aucHPlmnId[MMA_SPECIAL_HPLMN_ITEM_SIZE];    /*4�ֽ������ʾһ��HPLMN*/
}MMA_SPEC_HPLMN_TYPE;

typedef struct
{
     VOS_UINT32           ulHPlmnCount;                               /*HPLMN����*/
     MMA_SPEC_HPLMN_TYPE  astHPlmnGroup[MMA_SPECIAL_HPLMN_LIST_SIZE]; /*HPLMN�б�*/
}TAF_MMA_SPEC_PLMN_NOT_ROAM_ST;


#define MMA_HUAWEI_PLMN_MODIFY_MAX_SIZE                   (128)

typedef struct
{
    VOS_UINT8 aucRcvPlmnData[MMA_HUAWEI_PLMN_MODIFY_MAX_SIZE];
}NAS_MMA_HUAWEI_PLMN_MODIFY_STRU;


typedef struct
{
    VOS_UINT8 ucCollected;
    VOS_UINT8 aucReserved;
}SALES_AGENT_RECORD_STRU;

typedef struct
{
     VOS_UINT8  ucNvActiveFlag;     /* NV�����־�ֶ�*/
     VOS_UINT8  ucReserved[3];         /* �����ֶ�*/
}HPLMN_Within_EPLMN_NotRoam;

/*****************************************************************************
 �ṹ��    : SI_PIH_IMSI_TIMER_CONFIG
 �ṹ˵��  : MMA����IMSI��ȡ���ڵ�NV�ṹ
 �ṹ ID    : 50426
*****************************************************************************/
typedef struct
{
    VOS_UINT8  ucNvActiveFlag;     /* NV�����־�ֶ�*/
    VOS_UINT8  ucReserved;         /* �����ֶ�*/
    VOS_UINT16  usTimerLen;        /* ��ȡIMSI����(��λΪ��)*/
}SI_PIH_IMSI_TIMER_CONFIG;
/*****************************************************************************
 �ṹ��    : TIM_CPIN_STRU
 �ṹ˵��  : AT+CPIN?����
 �ṹ ID   : 50450
*****************************************************************************/
typedef struct 
{
     VOS_UINT8  ucNvActiveFlag;     /* NV�����־�ֶ�*/
     VOS_UINT8  ucReserved[3];         /* �����ֶ�*/
} TIM_CPIN_STRU;

typedef struct
{
    VOS_UINT8   led_enable;        /* LED��ʹ�ܿ��� */
    VOS_UINT8   led_dr;            /* LED����ʹ�õ�DR */
    VOS_UINT8   led_mode;          /* LED��ģʽ��־ */
    VOS_UINT8   led_reserve;       /* �����ֶ� */
    VOS_UINT32  full_on;           /* LED�ƺ���ģʽ�ȶ����ĳ���ʱ�� */
    VOS_UINT32  full_off;          /* LED�ƺ���ģʽ�ȶ����ĳ���ʱ�� */
    VOS_UINT32  fade_on;           /* LED�ƺ���ģʽ�Ӱ������ĳ���ʱ�� */
    VOS_UINT32  fade_off;          /* LED�ƺ���ģʽ���������ĳ���ʱ�� */
    VOS_UINT32  delay_on;          /* LED����˸ģʽ����ʱ�� */
    VOS_UINT32  delay_period;     /* LED����˸ģʽ����˸����ʱ��*/
    VOS_UINT32  full_long_on;     /* LED�Ƴ����ĳ���ʱ�� */
    VOS_UINT32  full_long_off;    /* LED�Ƴ����ĳ���ʱ�� */
    VOS_UINT32  brightness;       /* LED�����ȵ���ֵ */
}NV_LED_PARA_STRU;

/*****************************************************************************
 �ṹ��    : SMS_AUTO_REG_STRU
 �ṹ˵��  : ������ע�ᶨ��
 �ṹ ID   : 50449
*****************************************************************************/
#define MAX_IMSI_LEN 15
typedef struct 
{
     VOS_UINT8  ucNvActiveFlag;                               /*NV�����־�ֶ�*/
     VOS_UINT8  ucSmsRegFlag;                                 /*ע���־λ*/
     VOS_UINT8  ucSmsRegImsi[MAX_IMSI_LEN];               /*��ע��IMSI��*/
     VOS_UINT8  ucReserved[3];                                /*�����ֶ�*/
} SMS_AUTO_REG_STRU;

/*****************************************************************************
 �ṹ��    : TATA_DEVICELOCK_STRU
 �ṹ˵��  : �豸��NV�Ľṹ
 �ṹ ID   : 50432
*****************************************************************************/
#define MAX_DLCK_ENCODE_LEN_MBB 32
typedef struct
{
    VOS_UINT32 ulStatus;                           /*�豸������״̬*/
    VOS_UINT8   aucLockCode[MAX_DLCK_ENCODE_LEN_MBB];    /*�豸��������*/
}TATA_DEVICELOCK_STRU;

/*****************************************************************************
 �ṹ��    : NAS_NV_HPLMN_FIRST_UMTS_TO_LTE
 �ṹ˵��  : YOTA���ƣ���3G��LTEʱ��������EHPLMN
 �ṹ ID   : 50432
*****************************************************************************/
typedef struct
{
    VOS_UINT8 ucNvActiveFlag; /* �Ƿ񼤻� YOTA ���ƹ��� */
    VOS_UINT8 aucReserved[3]; /* ���� */
}NAS_NV_HPLMN_FIRST_UMTS_TO_LTE;


typedef struct
{
    VOS_UINT8    ucNvActiveFlag;   /* �Ƿ񼤻� EE ��Ӫ����ʾ���ƹ��� */
    VOS_UINT8    aucReserved[3];   /* ���� */
}NAS_NV_EE_OPERATOR_NAME_DISPLAY;


#define MODE_LIST_MAX_LEN    (6)
#define MODE_LIST_MAX_NUM    (10)

typedef struct
{
    VOS_UINT8    ucListItemNum;
    VOS_UINT8    ucRestrict;
    VOS_UINT8    aucModeList[MODE_LIST_MAX_NUM][MODE_LIST_MAX_LEN];
}NAS_NV_SYSCFGEX_MODE_LIST;


/* ��APN���� */
typedef struct
{
    VOS_UINT8   ucStatus;       /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8   ucApnLength;
    VOS_UINT8   aucApn[TAF_NVIM_MAX_APN_LOCK_STR_LEN];       /* APN�Ӹ�����ĵ�һ���ֽڿ�ʼд�룬������'\0'��Ϊ��β */
    VOS_UINT8   aucRsv[2];
}APS_APN_LOCK_STRU;

/*****************************************************************************
 �ṹ��    : NV_WINBLUE_PROFILE_STRU
 �ṹ˵��  : Windows8.1 ���Կ���NV
 �ṹ ID   : 50424
*****************************************************************************/
typedef struct
{
    VOS_UINT8  InterfaceName[32];
    VOS_UINT8  MBIMEnable;
    VOS_UINT8  CdRom;
    VOS_UINT8  TCard;
    VOS_UINT8  MaxPDPSession;
    VOS_UINT16 IPV4MTU;
    VOS_UINT16 IPV6MTU;
    VOS_UINT32 Reserved1;
    VOS_UINT32 Reserved2;
}NV_WINBLUE_PROFILE_STRU;

/*50577*/
typedef struct
{
VOS_UINT8 nv_status;    /*��nv�Ƿ񼤻�*/
VOS_UINT8 diag_enable;  /*diag�˿��Ƿ�ʹ��*/
VOS_UINT8 shell_enable; /*shell�˿��Ƿ�ʹ��*/
VOS_UINT8 adb_enable;   /*adb�˿��Ƿ�ʹ��*/
VOS_UINT8 om_enable;   /*om�˿��Ƿ�ʹ��*/
VOS_UINT8 ucReserved_0; /*�����ֶ�*/
VOS_UINT8 ucReserved_1; /*�����ֶ�*/
VOS_UINT8 ucReserved_2; /*�����ֶ�*/
}HUAWEI_NV_USB_SECURITY_FLAG;

/*****************************************************************************
 �ṹ��    : NV_USB_CDC_NET_SPEED_STRU
 �ṹ˵��  : ��ȡ�����ٶ�Ĭ��ֵ��NV
 �ṹ ID   : 50456
*****************************************************************************/
typedef struct
{
    VOS_UINT32  nv_status;
    VOS_UINT32  net_speed;  
    VOS_UINT32  reserve1;
    VOS_UINT32  reserve2;
    VOS_UINT32  reserve3;
}NV_USB_CDC_NET_SPEED_STRU;

/*****************************************************************************
 �ṹ��    : ss_coul_nv_info
 �ṹ˵��  : ���ؼ�NV
 �ṹ ID   : 50462
*****************************************************************************/
/*add by zhouyunfei 20130916*/
#define COUL_MAX_TEMP_LEN 10
#define COUL_RESERVED_LEN 4
typedef struct
{
    BSP_S32 charge_cycles;
    BSP_S32 r_pcb; // uohm
    BSP_S32 v_offset_a;
    BSP_S32 v_offset_b;
    BSP_S32 c_offset_a;
    BSP_S32 c_offset_b;
    BSP_S16 temp[COUL_MAX_TEMP_LEN];
    BSP_S16 real_fcc[COUL_MAX_TEMP_LEN];
    BSP_S16 calc_ocv_reg_v;
    BSP_S16 calc_ocv_reg_c;
    BSP_S16 hkadc_batt_temp;
    BSP_S16 hkadc_batt_id_voltage;
    BSP_S32 start_cc;
    BSP_S32 ocv_temp;
    BSP_S32 limit_fcc;
    BSP_S32 reserved[COUL_RESERVED_LEN];
}ss_coul_nv_info;
#define BATTERY_SN_LEN  (32)
typedef struct
{
    BSP_U8  battery_sn[BATTERY_SN_LEN];
    BSP_U32  coul_firmware_update_status;
}nv_huawei_coul_firmware_update_info;

/*****************************************************************************
 �ṹ��    : NV_FTEN_USB_SWITCH_SEL_INFO
 �ṹ˵��  : ���÷���BOX ˫USB��ѡ��
 �ṹ ID   : 50607
*****************************************************************************/
typedef struct
{
    VOS_UINT8 nv_status;
    VOS_UINT8 usb_sel_flag;
    VOS_UINT8 reserve1;
    VOS_UINT8 reserve2;
} NV_FTEN_USB_SWITCH_SEL_INFO;
/*****************************************************************************
 �ṹ��    : NV_PLATFORM_CATEGORY_SET_STRU
 �ṹ˵��  : ���õ���CAT�ȼ�
 �ṹ ID   : 50458
*****************************************************************************/
typedef struct
{
    VOS_UINT32   nv_status;
    VOS_UINT32   cat_value;
    VOS_UINT32   reserve1;
    VOS_UINT32   reserve2;
    VOS_UINT32   reserve3;
}NV_PLATFORM_CATEGORY_SET_STRU;

/*****************************************************************************
 ��������  : WLAN_AT_WIINFO_CHANNELS_NVIM_STRU
 ��������  : ��ѯWiFi���ŵ��͹��ʽṹ�� 
 �ṹ ID   :      50468��50469
*****************************************************************************/
#define MAX_CHANNEL24G_SIZE     (32)                    /* ����洢24���ŵ���֮�䶺�ŵ�ASCII��ֵ */
#define MAX_CHANNEL5G_SIZE      (96)        
#define MAX_PWR_SIZE            (8)

typedef struct 
{
    VOS_UINT8   Channels24G[MAX_CHANNEL24G_SIZE];            /* 2.4G�¹������ŵ� */
    VOS_UINT8   Channels5G[MAX_CHANNEL5G_SIZE];             /* 5G�¹������ŵ� */
}WLAN_AT_WIINFO_CHANNELS_NVIM_STRU;
typedef struct 
{
    VOS_UINT8   bMode_24G_pwr[MAX_PWR_SIZE];                         /* 2.4G bģʽ�µ�Ŀ�깦�� */
    VOS_UINT8   gMode_24G_pwr[MAX_PWR_SIZE];                         /* 2.4G gģʽ�µ�Ŀ�깦�� */
    VOS_UINT8   nMode_24G_pwr[MAX_PWR_SIZE];                         /* 2.4G nģʽ�µ�Ŀ�깦�� */
    VOS_UINT8   aMode_5G_pwr[MAX_PWR_SIZE];                           /* 5G aģʽ�µ�Ŀ�깦�� */
    VOS_UINT8   nMode_5G_pwr[MAX_PWR_SIZE];                           /* 5G nģʽ�µ�Ŀ�깦�� */
    VOS_UINT8   acMode_5G_pwr[MAX_PWR_SIZE];                         /* 5G acģʽ�µ�Ŀ�깦�� */
    VOS_UINT8   reserve1[MAX_PWR_SIZE];                                      /*Ԥ��*/
    VOS_UINT8   reserve2[MAX_PWR_SIZE];                                      /*Ԥ��*/
}WLAN_WIINFO_POWER_NVIM_STRU;


typedef struct
{
    VOS_UINT32      ulDSLastLinkTime;                       /*DS���һ������ʱ��*/
    VOS_UINT32      ulDSTotalSendFluxLow;                   /*DS�ۼƷ����������ĸ��ֽ�*/
    VOS_UINT32      ulDSTotalSendFluxHigh;                  /*DS�ۼƷ����������ĸ��ֽ�*/
    VOS_UINT32      ulDSTotalLinkTime;                      /*DS�ۼ�����ʱ��*/
    VOS_UINT32      ulDSTotalReceiveFluxLow;                /*DS�ۼƽ����������ĸ��ֽ�*/
    VOS_UINT32      ulDSTotalReceiveFluxHigh;               /*DS�ۼƽ����������ĸ��ֽ�*/

} TAF_APS_DSFLOW_NV_STRU_EX;

typedef struct
{
    TAF_APS_DSFLOW_NV_STRU_EX    DsflowNvWan[5]; /*����Ŀǰ��ʹ���������NV�ṹ��֧����ౣ��5��WAN����*/
} TAF_APS_DSFLOW_NV_STRU_EXT;

/*****************************************************************************
 �ṹ��    : NV_HUAWEI_DYNAMIC_NAME
 �ṹ˵��  : ������Ӫ�̶��Ƶ���PC����ʾCDROM��SD �����ַ���
 �ṹ ID   : 50108
*****************************************************************************/
#define DYNAMIC_CD_NAME_CHAR_NUM (28)
#define reserved_num_32  (32)
typedef struct
{
    VOS_UINT32 nv_status;
    VOS_UINT8 huawei_cdrom_dynamic_name[DYNAMIC_CD_NAME_CHAR_NUM];
    VOS_UINT8 huawei_sd_dynamic_name[DYNAMIC_CD_NAME_CHAR_NUM];
    VOS_UINT8 reserved[reserved_num_32];
}HUAWEI_DYNAMIC_NAME_STRU;


/*****************************************************************************
 �ṹ��    : NV_HUAWEI_DYNAMIC_INFO_NAME
 �ṹ˵��  : ��NV��������Ӫ�̶��Ƶ���PC����ʾproduct manufacturer��configuration���ַ�����
 �ṹ ID   : 50109
*****************************************************************************/
#define DYNAMIC_INFO_NAME_CHAR_NUM (40)
#define reserved_num_8  (8)
typedef struct
{
    VOS_UINT32 nv_status;
    VOS_UINT8 huawei_product_dynamic_name[DYNAMIC_INFO_NAME_CHAR_NUM];
    VOS_UINT8 huawei_manufacturer_dynamic_name[DYNAMIC_INFO_NAME_CHAR_NUM];
    VOS_UINT8 huawei_configuration_dynamic_name[DYNAMIC_INFO_NAME_CHAR_NUM];
    VOS_UINT8 reserved[reserved_num_8];
}HUAWEI_DYNAMIC_INFO_NAME_STRU;

/*****************************************************************************
 �ṹ��    : CPE_TELNET_SWITCH_NVIM_STRU
 �ṹ˵��  : ��NV�����ڿ���CPE��Ʒtelnet�����Ƿ�򿪡�
 �ṹ ID   : 50501
*****************************************************************************/
typedef struct
{
    VOS_UINT8 nv_telnet_switch;
    VOS_UINT8 reserved;
}CPE_TELNET_SWITCH_NVIM_STRU;
typedef struct
{
    VOS_UINT8 InterfaceName[32];     /* �ӿ����� */
    VOS_UINT8  MBIMEnable;            /* �Ƿ�����MBIM,ȡֵ��Χ [0-1] */
    VOS_UINT8  CdRom;                 /* ����MBIM���Ƿ�ͬʱ�ϱ�����,ȡֵ��Χ [0-1] */
    VOS_UINT8  TCard;                 /* ����MBIM���Ƿ�ͬʱ�ϱ�T��,ȡֵ��Χ [0-1] */
    VOS_UINT8  MaxPDPSession;         /* ��PDP֧�ֵ����PDP����,ȡֵ��Χ [1-8] */
    VOS_UINT16 IPV4MTU;               /* IPV4 MTU��С,ȡֵ��Χ [296-1500] */
    VOS_UINT16 IPV6MTU;               /* IPV6 MTU��С,ȡֵ��Χ [1280-65535] */
    VOS_UINT32 Reserved1;             /* ���� */
    VOS_UINT32 Reserved2;             /* ���� */
}NAS_WINBLUE_PROFILE_TYPE_STRU;


typedef  struct
{
    BSP_U8 ucNvActiveFlag;    /*�Ƿ񼤻�BIP����*/
    BSP_U8 ucRoamingEnable;  /*����ʱ�Ƿ��������BIPҵ��*/
    BSP_U8 ucReserved[2];    /*���뱣��*/
}NV_BIP_FEATURE_STRU;

/*add by wanghaijie for simlock 3.0*/
typedef struct
{
    VOS_UINT8    nv_lock30[TAF_NVIM_HWLOCK_LEN];
    VOS_UINT8    nv_lock21[TAF_NVIM_HWLOCK_LEN];/*simlock 2.1 δʹ��*/
    VOS_UINT8    nv_lock20[TAF_NVIM_HWLOCK_LEN];/*simlock 2.0 δʹ��*/
    VOS_UINT8    reserved[TAF_NVIM_HWLOCK_LEN];
}NV_AUHT_OEMLOCK_STWICH_SRTU;

typedef struct
{
    VOS_UINT8    nv_lock30[TAF_NVIM_HWLOCK_LEN];
    VOS_UINT8    nv_lock21[TAF_NVIM_HWLOCK_LEN];
    VOS_UINT8    nv_lock20[TAF_NVIM_HWLOCK_LEN];
    VOS_UINT8    reserved[TAF_NVIM_HWLOCK_LEN];
}NV_AUHT_SIMLOCK_STWICH_STRU;

typedef  struct
{
    BSP_U8 ucSimRefreshIndFlag;    /*SIM��RESET�ϱ�ʹ��*/
    BSP_U8 ucReserv;             /* C31֮��Ļ��ߴ�λ����*/
    BSP_U8 ucReserv1;             /*���뱣��*/
    BSP_U8 ucReserv2;            /*���뱣��*/
}NV_SIM_CUST_FEATURE_STRU;


#define MMA_ROMA_WHITELIST_NV_SIZE                   (127)

typedef struct
{
    VOS_UINT8 ucNvActiveFlag;           /*�Ƿ񼤻����ΰ�������1��ʾ���0������*/
    VOS_UINT8 aucRoamWhiteListData[MMA_ROMA_WHITELIST_NV_SIZE]; /* NV���� */
} NV_ROAM_WHITELIST_DATA;

/*****************************************************************************
 �ṹ��    : nv_mac_num
 �ṹ˵��  :����ÿһ�����Ͷ�Ӧ���豸MAC��ַ����
 �ṹ ID   : 50517
*****************************************************************************/
typedef struct
{
    VOS_UINT8 lanmac_num;        /* LAN_MAC/Cradle MAC����*/
    VOS_UINT8 wifimac_num;       /* WIFI_MAC ����*/
    VOS_UINT8 btmac_num;        /* BLUETOOTH_MAC����*/
    VOS_UINT8 usbmac_num;       /* USB_MAC����*/
    VOS_UINT8 reserve[4];          /*Ԥ���ֶ�*/
} NV_MAC_NUM_STRU;

/*****************************************************************************
 �ṹ��    : SPY_TEMP_PROTECT_SAR_NV_STRU
 �ṹ˵��  : ��NV�����ڿ����¶ȱ�����SAR����
 �ṹ ID   : 50520
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulIsEnable;
    VOS_INT32   lReduceSARThreshold;
    VOS_INT32   lResumeSARThreshold;
    VOS_UINT32  ulTempOverCount;
    VOS_UINT32  ulTempResumeCount;
    VOS_INT32   lReserved_1;
} SPY_TEMP_PROTECT_SAR_NV_STRU;


#define  MMC_MAX_LEN  5
typedef struct
{
    VOS_UINT32                   aulRoamMCCList[MMC_MAX_LEN];/* �洢�����εĹ����� */
}NAS_MMC_NVIM_ROAM_MCC_CMP_STRU;

/********************************************************************************
  �ṹ��    : NV_LTE_TDD_PRIOR_STRU
  �ṹ˵��  : NV_LTE_TDD_PRIOR_STRU �ṹ
*****************************************************************************/
typedef  struct
{
    BSP_U8 ucActiveFlag;        /*LTE_TDD������������ʹ��*/
    BSP_U8 ucActNum;            /*���ò�����FDDƵ�εĸ���*/
    BSP_U8 ucReserved[2];       /*���뱣��*/
    BSP_U16 usBand[32];         /*���ò�����FDD��Ƶ�ε�NVID*/
}NV_LTE_TDD_PRIOR_STRU;

/********************************************************************************
  �ṹ��    : NAS_PLMN_ID_STRU
  �ṹ˵��  : NAS_PLMN_ID_STRU �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMcc;   /* MCC,3 bytes */
    VOS_UINT16                          usMnc;   /* MNC,2 or 3 bytes */
}NAS_PLMN_ID_STRU;

/********************************************************************************
  �ṹ��    : USER_SET_BAND_STRU
  �ṹ˵��  : USER_SET_BAND_STRU �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulBandLow; /*��32λ*/
    VOS_UINT32 ulBandHigh;/*��32λ*/
} USER_SET_BAND_STRU;

/********************************************************************************
  �ṹ��    : USER_SET_PLMN_BAND_STRU
  �ṹ˵��  : USER_SET_PLMN_BAND_STRU �ṹ
*****************************************************************************/
typedef struct
{
    NAS_PLMN_ID_STRU stPlmnId; /* PLMN*/
    USER_SET_BAND_STRU stLBand;/* Ƶ��*/
} USER_SET_PLMN_BAND_STRU;

/********************************************************************************
  �ṹ��    : NAS_NV_LTE_BANDLOCK_STRU
  �ṹ˵��  : NAS_NV_LTE_BANDLOCK_STRU �ṹ
*****************************************************************************/
typedef  struct
{
    VOS_UINT8    ucNvActiveFlag;               /* �Ƿ񼤻����Ƶ*/
    VOS_UINT8    ucPlmnNum;                    /*���õ�PLMN�ĸ���*/
    VOS_UINT8    ucReserved[2];                /*���뱣��*/
    USER_SET_PLMN_BAND_STRU  stPlmnBandId[10]; /*���õ�PLMN ID��band*/
}NAS_NV_LTE_BANDLOCK_STRU;



typedef struct
{
    VOS_UINT8                           enUeMode;       /*�����ͣ�1---����2---Ӳ��*/
    VOS_UINT8                           enMasterdata;   /*����Ԥ���������ݣ�enMasterdata��Ϊ1*/
    VOS_UINT8                           enHashflg;      /*���۸�У��flg TRUEʱ��ҪУ��*/
    VOS_UINT8                           aucRfu;         /*Ԥ��*/
}VSIM_UE_MODE_NV_STRU;

#define NV_VSIM_KEYLEN_MAX                   (256)         /*NV ��������ݵ���󳤶�*/
#define NV_VSIM_KEYHASH_MAX                  (32)         /*HASH 256 �32 byte*/

typedef struct
{
    VOS_UINT32                          ulHashLen;
    VOS_UINT8                           aucHash[NV_VSIM_KEYHASH_MAX];
}NV_VSIM_HASHDATA_STRU;

typedef struct
{
    VOS_UINT32                          ulKeyLen;
    VOS_UINT8                            aucKey[NV_VSIM_KEYLEN_MAX];
}NV_VSIM_KEYDATA_STRU;

typedef struct
{
    VOS_UINT32                             enAlgorithm;
    VOS_UINT32                             ulDHLen;         /* DH�㷨�������ӵĳ��� */
    NV_VSIM_KEYDATA_STRU                   stCPrivateKey;   /* �����˽Կ */
    NV_VSIM_KEYDATA_STRU                   stCPublicKey;    /* ����⹫Կ */
    NV_VSIM_KEYDATA_STRU                   stSPublicKey;    /* ��������Կ */
    NV_VSIM_HASHDATA_STRU                  stHashData;      /*���������Կƴ�Ӻ��HASH*/
}NV_VSIM_HVSDH_NV_STRU;


#define NV_VSIM_DIEID_MAXLEN                   (64)/*���Ϊ32λ���������HUK���ܺ󲻻ᳬ��64*/
#define NV_VSIM_DIEID_HASHLEN                  (32)
typedef struct
{
    VOS_UINT32                           ulNumLen;
    VOS_UINT8                            aucNum[NV_VSIM_DIEID_MAXLEN];
    VOS_UINT32                           ulHashLen;
    VOS_UINT8                            aucHash[NV_VSIM_DIEID_HASHLEN];
}NV_VSIM_DIEID_STRU;


typedef struct
{
    VOS_UINT8    wifi_enable; 
    VOS_UINT8    ucReserved1;
    VOS_UINT8    ucReserved2;
    VOS_UINT8    ucReserved3;
}NV_SMS_CTRL_WIFI_STRU;

/* NV50578~NV50583 */
#define MAX_LTE_APN_IMSI_PREFIX_SUPPORT          10
#define MIN_LTE_APN_IMSI_PREFIX_SUPPORT          5  /* AT����ʱ�����ٱ�����mcc,mnc */
#define MAX_LTE_APN_IMSI_PREFIX_BCD_SUPPORT      (MAX_LTE_APN_IMSI_PREFIX_SUPPORT / 2)
#define MAX_LTE_ATTACH_APN_NAME_LEN              32
#define MAX_LTE_ATTACH_APN_USERNAME_LEN          32
#define MAX_LTE_ATTACH_APN_USERPWD_LEN           32
#define MAX_LTE_ATTACH_PROFILE_NAME_LEN          19

typedef struct
{
    VOS_UINT8 ucActiveFlag;
    VOS_UINT8 ucPdpType;
    VOS_UINT8 ucAuthType;
    VOS_UINT8 ucImsiPrefixLen;
    VOS_UINT8 aucImsiPrefixBcd[MAX_LTE_APN_IMSI_PREFIX_BCD_SUPPORT]; /*ƥ���IMSIǰ׺��BCD��*/
    VOS_UINT8 ucApnLen;
    VOS_UINT8 aucApn[MAX_LTE_ATTACH_APN_NAME_LEN]; /*ƥ���APN*/
    VOS_UINT8 ucUserNameLen;
    VOS_UINT8 aucUserName[MAX_LTE_ATTACH_APN_USERNAME_LEN]; /*ƥ���APN�û���*/
    VOS_UINT8 ucPwdLen;
    VOS_UINT8 aucPwd[MAX_LTE_ATTACH_APN_USERPWD_LEN]; /*ƥ���APN����*/
    VOS_UINT8 ucProfileNameLen;
    VOS_UINT8 aucProfileName[MAX_LTE_ATTACH_PROFILE_NAME_LEN]; /* Profile������ */
}NV_LTE_ATTACH_PROFILE_STRU;

typedef struct{
    VOS_UINT8 ucActiveFlag;
    VOS_UINT8 ucPrefer0;            /* ����APN��NV8451(�������)���ȼ���0:NV8451���ȣ� 1:�������� */
    VOS_UINT8 aucReservd[6];        /* Ԥ�������ڽ�����չ */
}NV_LTE_ATTACH_PROFILE_CTRL;
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


