


#ifndef __SYSNVID_H__
#define __SYSNVID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "NvIddef.h"


/*typedef VOS_UINT16  SYS_NV_ID_ENUM_U16;
 */

enum SYS_NV_ID_ENUM
{
/*    0  */      en_NV_Item_IMEI = GU_SYS_NV_ID_MIN,
/*    1  */      en_NV_Auth_Code_ID = GU_SYS_NV_ID_MIN + 1,
/*    2  */      en_NV_Auth_Num_ID,
/*    3  */      en_NV_Ttl_ID,
/*    4  */      en_NV_Resume_Flag,
/*    5  */      en_NV_Calibrated_Time,
/*    6  */      en_NV_Item_Serial_Num,
/*    7  */      en_NV_Item_LED_CONFIG_Data,
/*    8  */      en_NV_Item_Om_LogFile_Size,
/*    9  */      en_NV_Item_WatchDog_Flag,
/*   10  */      en_NV_Item_MonitorDSp_Flag,
/*   11  */      en_NV_Item_KickDog_Time = 11,
/*   12  */      en_NV_Item_ScheduleWatchDog_Time,
/*   13  */      en_NV_Item_USIM_TEMP_SENSOR_TABLE,
/*   14  */      en_NV_Item_USIM_TEMP_PROTECT,
/*   15  */      en_NV_Item_UE_Point_Ctrl,
/*   16  */      en_NV_Item_AGING_TEST_TABLE,
/*   17  */      en_NV_Item_Exception_Record,
/*   18  */      en_NV_Item_TA_Stub,
/*   19  */      en_NV_Item_TA_RF_DELAY_VAL,
/*   20  */      en_NV_Item_Sys_Prt_Task,
/*   21  */      en_NV_Item_USB_Enum_Status,
/*   22  */      en_NV_Item_LiveTimeControl,
/*   23  */      en_NV_Item_LiveTime,
/*   24  */      en_NV_Item_MONITORCPU_CFG,
/*   27  */      en_NV_Item_COMMDEGBUG_CFG = 27,
/*   28  */      en_NV_Item_Max_Gsm_Reg_Cnt,
/*   29  */      en_NV_Item_DFS_Config=29,
/*   30  */      en_NV_Item_HW_VER,
/*   31  */      en_NV_Item_PID_Enable_Type,
/*   32  */      en_NV_Item_AT_DISLOG_PWD,
/*   33  */      en_NV_Item_AT_SHELL_OPEN_FLAG,
/*   34  */      en_NV_Item_AT_E5_RIGHT_FLAG,
/*   35  */      en_NV_Item_BATTERY_TEMP_ADC,
/*   36  */      en_NV_Item_SW_VERSION_FLAG,
/*   37  */      en_NV_Item_ERRORLOG_ENABLEFLAG = 37,
/*   38  */      en_NV_Item_ERRORLOG_FLUSHBUFINTERVAL = 38,
/*   39  */      en_NV_Item_ERRORLOG_RECORDPERIOD = 39,
/*   40  */      en_NV_Item_USIM_TEMP_PROTECT_NEW,
/*   41  */      en_NV_Item_DRV_CUSTOMIZE_TYPE = 41,        /*���NV�����ʹ��*/
/*   42  */      en_NV_Item_AT_DISSD_FLAG = 42,
/*   43  */      en_NV_Item_AT_DISSD_PWD = 43,
/*   44  */      en_NV_Item_WIFI_IP_ADDRESS,
/*   45  */      en_NV_Item_Om_Port_Type,
/*   46  */      en_NV_Item_Om_Printf_Port,
/*   47  */      en_NV_Item_Om_PsLog_Port,
/*   48  */      en_NV_Item_AT_DISLOG_PWD_NEW,
/*   49  */      en_NV_Item_OLED_TEMP_ADC,
/*   50  */      en_NV_Item_MODIFY_LINKINFO_FLAG,
/*   51  */      en_NV_Item_WEBNAS_SD_WORKMODE,
/*   52  */      en_NV_Item_HW_WDT_FLAG,
/*   53  */      en_NV_Item_DEFAULT_LINK_OF_UART = 53,
/*   54  */      en_NV_Item_POWER_LED_ENABLE = 54,
/*   55  */      en_NV_Item_HW_CONFIG = 55,
/*   59  */      en_NV_Item_M2_ENABLE_FLAG = 59,
/*   60  */      en_NV_Item_SVLTE_FLAG = 60,
/*   63  */      en_NV_Item_NPNP_CONFIG = 63,
/*   64  */      en_NV_Item_VSIM_SUPPORT_FLAG = 64,
/*   65  */      en_NV_Item_VSIM_HVSDH_INFO = 65,
/*   66  */      en_NV_Item_VSIM_Fplmn_Info = 66,
/*   67  */      en_NV_Item_VSIM_Loci_Info = 67,
/*   68  */      en_NV_Item_VSIM_PsLoci_Info = 68,
/*   69  */      en_NV_Item_Card_Status_Cb_Type = 69,
/*   70  */      en_NV_Item_LC_Ctrl_PARA = 70,
/*   71  */      en_NV_Item_Usimm_T1_Ctrl_PARA = 71,
/*   90  */      en_NV_Item_BATTERY_ADC = GU_SYS_NV_ID_MIN + 90,
/*   114 */      en_NV_Item_Factory_Info = GU_SYS_NV_ID_MIN + 114,
/*   115 */      en_NV_Item_AT_FACTORY_INFO = GU_SYS_NV_ID_MIN + 115,
/*   116 */      en_NV_Item_AT_MANUFACTURE_DATE = GU_SYS_NV_ID_MIN + 116,
/*   117 */      en_NV_Item_LOG_FILE_SAVE = GU_SYS_NV_ID_MIN + 117,
/*   118 */      en_NV_Item_USB_LOG_LEV = GU_SYS_NV_ID_MIN + 118,
/*   119 */      en_NV_Item_USB_MNTN_FLAG = GU_SYS_NV_ID_MIN + 119,
/*   120 */      en_NV_Item_OAM_Config = GU_SYS_NV_ID_MIN + 120,
/*   121 */      en_NV_Item_System_APP_Config = GU_SYS_NV_ID_MIN + 121,
/*   122 */      en_NV_Item_ZSP_LDF_CONFIG = GU_SYS_NV_ID_MIN + 122,
/*   123 */      en_NV_Item_HIFI_LDF_CONFIG = GU_SYS_NV_ID_MIN + 123,
/*   124 */      en_NV_Item_TTF_MEM_SOLUTION_ID = GU_SYS_NV_ID_MIN + 124,       /*δʹ��*/
/*   125 */      en_NV_Item_TTF_MEM_SOLUTION_CFG = GU_SYS_NV_ID_MIN + 125,
/*   126 */      en_NV_Item_PHY_SW_CFG = GU_SYS_NV_ID_MIN + 126,
/*   127 */      en_NV_Item_NV_PRIORITY_THRESHOLD = GU_SYS_NV_ID_MIN + 127,    /*FlashLess Phase II*/
/*   128 */      ev_NV_Item_SCI_DSDA_CFG = 128,
/*   129 */      en_NV_Item_Sim_ATR_Flag = GU_SYS_NV_ID_MIN + 129,
/*   130 */      en_NV_Item_TERMINAL_CAPABILITY = GU_SYS_NV_ID_MIN + 130,
/*   131 */      en_NV_Item_Write_Slice_Record_Flag = GU_SYS_NV_ID_MIN + 131,
                 en_NV_ID_SOCP_SDLOG_CFG = 132,
/*   133 */      en_NV_Item_CC_TimerLen  = 133,
/*   134 */      en_NV_Item_ErrLogCtrlInfo = 134,
/*   135 */      en_NV_Item_AlarmidRelationship = 135,
/*   136 */      en_NV_Item_FTMDetail = 136,
/*   137 */      en_NV_Item_RF_INTRUSION_CFG = GU_SYS_NV_ID_MIN + 137,
/*   138 */      en_NV_Item_GUMODE_CHAN_PARA = 138,
/*   139 */      en_NV_Item_RECORD_BASE_BORARD_ID = GU_SYS_NV_ID_MIN + 139,
/*   140 */      en_NV_Item_RECORD_CURRENT_BORARD_ID = GU_SYS_NV_ID_MIN + 140,
/*   141 */      en_NV_Item_UART_CFG = GU_SYS_NV_ID_MIN + 141,

/*   142 */      en_NV_Item_Usim_Support_Ims = GU_SYS_NV_ID_MIN + 142,
/*   143 */      en_NV_Item_FLASH_Log_Record_CFG = GU_SYS_NV_ID_MIN + 143,
/*   144 */      en_NV_Item_PORT_BUFF_CFG           = GU_SYS_NV_ID_MIN + 144,
/*   145 */      en_NV_Item_EVENT_RESEND_CFG = GU_SYS_NV_ID_MIN + 145,
/*   146 */      en_NV_Item_CBT_LOG_ENABLE = GU_SYS_NV_ID_MIN + 146,
/*   147 */      en_NV_Item_PS_TRANSFER_CFG = GU_SYS_NV_ID_MIN + 147,
/*   148 */      en_NV_Item_ProductTypeForLogDirectory = GU_SYS_NV_ID_MIN + 148,
/*   149 */      en_NV_Item_DRX_RESET_ENABLE_CFG = GU_SYS_NV_ID_MIN + 149,
/*   150 */      en_NV_Item_MTC_RF_LCD_CFG = GU_SYS_NV_ID_MIN + 150,
/*   151 */      en_NV_Item_MTC_RF_LCD_TIMER_INTERVAL_CFG = GU_SYS_NV_ID_MIN + 151,
/*   2049*/      en_NV_Item_OM_Port_Num = GU_SYS_NV_ID_MIN + 2049,
/*  2319 */     en_NV_Item_Roam_Display_Cfg = 2319,                /* ������ʾ���� */
 /* 3001 */      en_NV_Item_SBM_CUSTOM_DUAL_IMSI_NEW = 3001,

/* 3003 */      en_NV_Item_GAS_C1_Calc_Opt_White_Plmn_List = 3003,

/*   8250*/      en_NV_Item_GCF_TYPE_CONTENT_ID = 8250,
/*   8517*/      en_NV_Item_ENHANCE_SIMCARD_LOCK_STATUS = 8517,
/*   8518*/      en_NV_Item_GENHANCE_SIMCARD_REMAIN_TIMES = 8518,
/*   8524*/      en_NV_Item_TOTOLPC_PARA_CTRL = 8524,
/*   8525*/      en_NV_Item_Wcdma_OLPC_MapWeight_Para = 8525,
/*   9037*/      en_NV_Item_Flow_Ctrl_Config         = 9037,
/*   9040*/      en_NV_Item_WIFI_INFO                = 9040,
/*   9043 */     en_NV_Item_MED_CODEC_TYPE           = 9043,

/*  9046 */      en_NV_Item_Ho_Wait_Sysinfo_Timer_Config    = 9046,

/* Added by f62575 for C50_IPC Project, 2012/02/23, begin */
/*   9049 */     en_NV_Item_FDN_Info                 = 9049,
/* 9050  */      en_NV_Item_CSFB_PPAC_Para           = 9050,                  /* WAS����PPAC NV�� */
/* Added by f62575 for C50_IPC Project, 2012/02/23, end   */
/*   9051*/      en_NV_BREATH_TIME = 9051,
/* ����LTE�������ζ���NV */
/* 9052 */       en_NV_Item_Lte_Internation_Roam_Config     = 9052,

/* ���Ӳ��ű���11,12,13,15����NV */
/* 9053 */       en_NV_Item_Dail_Reject_Config              = 9053,

/* ���ӹرն��Ŷ���NV */
/* 9054 */       en_NV_Item_Close_SMS_Capability_Config     = 9054,

/*  9065 */      en_NV_Item_XO_DEFINE               = 9065,

/*  9041 */      en_NV_Item_SubPlatFormInfo      = 9041,
/*  9070 */      en_NV_Item_Eqver                        = 9070,
/*  9071 */      en_NV_Item_Csver                        = 9071,

/* 9066 */       en_NV_Item_Fastdorm_Enable_Flag         = 9066,
/*   9067 */     en_NV_Item_Report_Cell_Sign              = 9067,/* WAS����NV��ϱ�С���ź�ǿ�� */
                 en_NV_Item_ETWS_Service_Cfg_Para = 9068,                              /* ETWS ��������� */
/*   9069*/      en_NV_Item_WAS_Customized_Para        = 9069,       /* WAS����NV��洢����NV���� */
/* 9072 */       en_NV_Item_FC_ACPU_DRV_ASSEMBLE_PARA  = 9072, /* ��̬�����������������λ��Ϣ */

/* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-11, begin */
/* 9080 */       en_NV_Item_Scan_Ctrl_Para             = 9080,
/* 9081 */       en_NV_Item_Att_Ens_Ctrl_Para          = 9081,
/* 9082 */       en_NV_Item_Pdp_Act_Limit_Para         = 9082,
/* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-11, end */
/* 9083 */       en_NV_Item_REPORT_ECC_NUM_SUPPORT_FLAG = 9083,
/* 9084 */       en_NV_Item_CUSTOM_ECC_NUM_LIST         = 9084,
/* 9085 */       en_NV_Item_ACTING_PLMN_SUPPORT_FLAG    = 9085,
/* 9086 */       en_NV_Item_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT = 9086,
/* 9087 */       en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST      = 9087,
/* 9088 */       en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG = 9088,
/* 9089 */       en_NV_Item_REPORT_PLMN_SUPPORT_FLAG                 = 9089,

                 /* Added by h59254 for V7R1C50 AT&T, 2012-6-29, begin */
/* 9090 */       en_NV_Item_Usim_Support_Feature_Config              = 9090,
                 /* Added by h59254 for V7R1C50 AT&T, 2012-6-29, begin */

/* 9091 */       en_NV_Item_UTRAN_TDD_FREQ_BAND		   = 9091, /* ָʾTDS Band��Ϣ */

/* 9092 */       en_NV_Item_Utran_Mode                 = 9092,                  /* ָʾ��ǰUTRANģʽΪWCDMA����TD-SCDMA */
/* 9094  */      en_NV_Item_CALL_CallNotSupportedCause = 9094,

/* Added by L60609 for MUX��2012-08-08,  Begin */
/* 9100 */       en_NV_Item_Mux_Support_Flg            = 9100,
/* Added by L60609 for MUX��2012-08-08,  End */

/* 9102 */       en_NV_Item_User_Cfg_Ehplmn_Info       = 9102,                  /* �û����õ�EHplmn NVIM ID */
/* 9103 */       en_NV_Item_Utran_Mode_Auto_Switch     = 9103,                  /* �ڵ�ǰ��GUTL�汾��֧�����ó�GUL�汾,GTL�汾���Լ�GUTL�汾����NVIM ID */
/* 9104 */       en_NV_Item_Disabled_Rat_Plmn_Info     = 9104,                  /* ��ֹ�����뼼����PLMN��Ϣ */

/* Modify by z60575 for multi_ssid, 2012-9-25 begin */
/* 9110 */       en_NV_Item_MULTI_WIFI_KEY             = 9110,       /* ֧�ֶ���SSID��չ����WIKEY NV�� */
/* 9111 */       en_NV_Item_MULTI_WIFI_STATUS_SSID     = 9111,       /* ֧�ֶ���SSID��չ����SSID NV�� */
/* Modify by z60575 for multi_ssid, 2012-9-25 end */

/* 9112 */      en_NV_Item_UMTS_CODEC_TYPE              = 9112,

/* 9113 */       en_NV_Item_AT_ABORT_CMD_PARA          = 9113,
/* 9116 */       en_NV_Item_CCallState_Rpt_Status           = 9116,             /* ^CCALLSTATE���������ϱ�״̬ */
/* 9118 */       en_NV_Item_SMS_MT_CUSTOMIZE_INFO       = 9118,

 /* 9119  */     en_NV_Item_CS_Call_Redial_CFG = 9119,

 /* 9120  */     en_NV_Item_QSearch_Customization = 9120,

/* 9121 */       en_NV_Item_Gsm_Poor_RxQual_ThresHold = 9121,

/* 9122 */       en_NV_Item_Hplmn_Register_Ctrl_Flg = 9122,
/*9123*/        en_NV_Item_CELL_SIGN_REPORT_CFG        = 9123,
/* 9124 */       en_NV_Item_LOW_POWER_Cell_Resel_OffSet = 9124,
/* 9125 */       en_NV_Item_MUX_REPORT_CFG = 9125,
/* 9126 */       en_NV_Item_Usim_OpFile_Init_Cfg = 9126,
/* 9127 */       en_NV_Item_Sim_OpFile_Init_Cfg = 9127,
/* 9128 */       en_NV_Item_CIMI_PORT_CFG = 9128,
/* Added by h59254 2013/01/04, begin */
/* 9129 */       en_NV_Item_Test_Card_Cfg = 9129,
/* Added by h59254 2013/01/04, end */

/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, begin */
/* 9130 */       en_NV_Item_IPV6_BACKPROC_EXT_CAUSE = 9130,
/* Added by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-24, end */

                 en_NV_Item_SMS_TIMER_LENGTH = 9131,
                 en_NV_Item_SS_CUSTOMIZE_PARA = 9132,
/* 9133 */       en_NV_Item_UCS2_Customization = 9133,

/* 9134 */       en_NV_Item_Csfb_Customization = 9134,

/* 9200 */       en_NV_Item_WTTF_MACDL_WATERMARK_LEVEL_Config = 9200, /* BBP�����ж�ˮ�ߵȼ�������Ϣ */
/* 9201 */       en_NV_Item_WTTF_MACDL_BBPMST_TB_HEAD_Config  = 9201, /* BBPMSTͷ��TB����Ϣ */

/* Added by l60609 for DSDA Phase II, 2012-12-13, Begin */
/* 9202 */       en_NV_Item_AT_CLIENT_CONFIG    = 9202,                           /* ˫��˫ͨ����ATͨ�������ĸ�Modem��Ϣ */
/* Added by l60609 for DSDA Phase II, 2012-12-13, End */

/* 9203 */       en_NV_Item_Platform_RAT_CAP        = 9203,
/* 9205 */       en_NV_Item_BBP_DUMP_ENABLE             = 9205,  /* BBP ���ɿ��� */
/* 9206 */       en_NV_Item_SUPPORT_RATMODE_MASK    = 9206, /* ��֪�����ÿ��MODEM֧�ֵ�ģʽ */

/* 9207 */       en_NV_Item_Clvl_Volume         = 9207,

/* 9206 */       en_NV_Item_BODY_SAR_PARA               = 9208,

/* 9209 */       en_NV_Item_Ext_Tebs_Flag              = 9209, /* TTF BO��չ���� */
/* 9210 */       en_NV_Item_TCP_ACK_Delete_Flg         = 9210, /* TTF �ɵ�TCP ACKɾ������ */

/* 9211 */       en_NV_Item_H3g_Customization          = 9211,

/* 9212 */       en_NV_Item_TEMP_PROTECT_CONFIG = 9212,

/*9213*/         en_NV_Item_THERMAL_TSENSOR_CONFIG          = 9213, /* �±�tsensor����NV */
/*9214*/         en_NV_Item_THERMAL_BAT_CONFIG              = 9214, /* �±���ؿ���NV */
/*9215*/         en_NV_Item_THERMAL_HKADC_CONFIG            = 9215, /* �±�HKADCͨ������NV */
/*9216*/         en_NV_Item_HKADC_PHYTOLOGICAL_CONFIG       = 9216, /* �±������߼�ת������NV */
/*9217*/         en_NV_Item_NV_TCXO_CFG                     = 9217, /* TCXO���ò��� */

/*9218*/         en_NV_Item_SHARE_PDP_INFO                  = 9218, /* Share PDP���Կ���NV */
/*9219*/         en_NV_Item_DEACT_USIM_WHEN_POWEROFF        = 9219, /* AT+CFUN=0������ػ���ȥ����SIM�����ܿ���NV */
                en_NV_Item_Enable_Lte_Timer_Len = 9220,

/* Added by f62575 for VSIM FEATURE, 2013-8-29, begin */
                en_Item_NAS_VSIM_CTRL_FEATURE               = 9224,
/* Added by f62575 for VSIM FEATURE, 2013-8-29, end */

/*   9225  */   en_NV_Item_CSFB_RAU_FOLLOW_ON_FLAG = 9225,

/* 9227 */      en_NV_Item_ChangeRegRejectCause_Flg           = 9227,

/* 9228  */      en_NV_Item_ACC_BAR_PLMN_SEARCH_FLG = 9228,           /*���Ʒ�HPLMN��RPLMN�����ֹʱ�Ƿ���Ҫ���� */
/* 9229  */      en_NV_Item_USER_CFG_OPLMN_LIST = 9229,               /*�����û�Ԥ��OPLMN�б���SIM�����⣬���ȼ�����SIM�� */

/* 9230  */      en_NV_Item_Rat_Forbidden_List_Config = 9230,

/* 9231 */       en_NV_Item_SMC_Ctrl_Flg                    = 9231,             /* UTRAN SMC����NV */

/* 9233 */      en_NV_Item_Dfs_Dsflow_Rate_Config     = 9233,

/* 9234 */       en_NV_Item_DSDA_PLMN_SEARCH_ENHANCED_CFG = 9234,

/* 9235 */       en_NV_Item_VOICE_TEST_FLAG       = 9235,


/* 9236  */      en_NV_Item_USER_CFG_OPLMN_EXTEND_LIST = 9236,  /*�����û�Ԥ��OPLMN�б�(֧��256��OPLMN)����SIM�����⣬���ȼ�����SIM�� */

/* 9237  */      en_NV_Item_SMS_DOMAIN                         = 9237,

               en_NV_Item_3G_TO_2G_Config      = 9238,
/* 9239 */       en_NV_Item_UART_SWITCH_CFG = 9239,
                en_NV_Item_WAIT_IMS_VOICE_AVAIL_Timer_Len      = 9240,

                 en_NV_Item_REDIAL_IMS_TO_CS_DOMAIN          = 9241,
                 en_NV_Item_IMS_ROAMING_SUPPORT_FLG          = 9242,


                en_NV_Item_IMS_VOICE_MOBILE_MANAGEMENT       = 9243,
/* 9244 */       en_NV_MODEM_RF_SHARE_CFG          = 9244,
/* 9246  */      en_NV_Item_CS_ONLY_DATA_SERVICE_SUPPORT_FLG = 9246,            /* �û�����NV: PSע�ᱻ��ֹ����£��Ƿ���������ҵ�񴥷�ע��ı�־ */
/* 9247  */      en_NV_Item_Ignore_Auth_Rej_CFG = 9247,
/* 9248 */       en_NV_Item_GSM_C1_CUSTOMIZE = 9248,
/* 9249 */       en_NV_Item_HIGH_PRIO_RAT_HPLMN_TIMER_INFO = 9249,
/*9250*/         en_NV_Item_LTE_DISABLED_USE_LTE_INFO_FLAG = 9250,            /* L������֧��ʱgmm��rauʱ�Ƿ���Ҫ��l��ȡ��ȫ�����Ļ�gutiӳ����Ϣ��VOS_TRUE:L disable��rau��Ҫ��l��ȡ��Ϣ��VOS_FALSE:L disable��rau����Ҫ��l��ȡ��Ϣ */

/* 9251 */      en_NV_Item_SBM_CUSTOM_DUAL_IMSI        = 9251,       /* WAS����NV��洢����˫imsi�Ŀ����Ƿ�� */
/* 9252 */      en_NV_Item_Roam_Search_Rplmn_Config    = 9252,
/* 9254 */       en_NV_Item_IMS_USSD_SUPPORT_FLG      = 9254,

/* 9263 */       en_NV_Item_Multi_Dfs_Dsflow_Rate_CFG    = 9263,
                 en_NV_Item_GSM_TX_LPF_EN                                     = 9264,

/* 9255 */       en_NV_Item_Ultra_Flash_Csfb_Support_Flg    = 9266,

/* 9270 */       en_NV_Item_3GPP2_Uplmn_Not_Pref_Flg    = 9270,

/* 9282 */     en_NV_Item_Syscfg_Trigger_Plmn_Search_Cfg = 9282,

/* 50009 */      en_NV_Item_TRAFFIC_CLASS_Type = GU_CUSTOM_EXTEND_NV_ID_MIN + 9,
/* 50012 */      en_NV_Item_WIFI_KEY = GU_CUSTOM_EXTEND_NV_ID_MIN + 12,
/* 50014 */      en_NV_Item_WIFI_MAC_ADDR = 50014,
/* 50016 */      en_NV_Item_BATTERY_TEMP_PROTECT = 50016,
/* 50018 */      en_NV_Item_SW_VER = 50018,
/* 50023 */      en_NV_Item_PRI_VERSION = 50023,
/* 50024  */     en_NV_Item_HUAWEI_NW_OPL_NAME_CUSTOMIZED = 50024,
/* 50025  */     en_NV_Item_PRIVATE_CMD_STATUS_RPT = 50025,
/* 50027  */     en_NV_Item_DEFAULT_RATE = 50027,
/* 50029  */     en_NV_Item_HUAWEI_IRAN_OPEN_PAGE_I = 50029,
/* 50031  */     en_NV_Item_MEAN_THROUGHPUT = 50031,
/* 50032  */     en_NV_Item_HUAWEI_PCCW_HS_HSPA_BLUE = 50032,
/* 50036  */     en_NV_Item_HUAWEI_CARDLOCK_PERM_EXT      = 50036,
/* 50037  */     en_NV_Item_HUAWEI_CARDLOCK_OPERATOR_EXT  = 50037,
/* 50041  */     en_NV_Item_NV_HUAWEI_DOUBLE_IMSI_CFG_I   = 50041,
/* 50048 */      en_NV_Item_PRODUCT_ID = 50048,
/* 50050  */     en_NV_Item_APN_Customize = 50050,
/* 50051  */     en_NV_Item_VIDEO_CALL = 50051,
/* 50052  */     en_NV_Item_CUST_USSD_MODE = 50052,
/* 50054  */     en_NV_Item_Forbidden_Band = 50054,
/* 50055  */     en_NV_Item_Enhanced_Hplmn_Srch_Flg = 50055,
/* 50056  */     en_NV_Item_SMS_CLASS0_TAILOR = 50056,
/* 50060  */     en_NV_Item_2G_DISABLE_SPARE_BIT3 = 50060,
/* 50061  */     en_NV_Item_PPP_DIAL_ERR_CODE = 50061,
/* 50063  */     en_NV_Item_Special_Roam_Flag = 50063,
/* 50064  */     en_NV_Item_MultiSimCallConf = 50064,
/* 50071  */     en_NV_Item_Cust_PID_Type = 50071,
/* 50091  */     en_NV_Item_Huawei_Dynamic_PID_Type = 50091,
/* 50110  */     en_NV_Item_Protocol_Base_Type = 50110,
/* 50201  */     en_NV_Item_SEC_BOOT_FLAG = 50201,
/* 50443  */	 en_NV_Item_DDR_TEMP_SENSOR_TABLE = 50443,
/* 50444  */	 en_NV_Item_WIFI_PA_TEMP_SENSOR_TABLE = 50444,
/* 50451 */      en_NV_Item_BIP_FEATURE = 50451,
/* 50366  */     en_NV_Item_CSOS_VALUE = 50366,
#if (FEATURE_ON == MBB_COMMON)
/* 50458 */      en_NV_Item_CATEGORY_VALUE = 50458,
/* 50517 */      en_NV_Item_MAC_NUM        = 50517,
#endif
#if (FEATURE_ON == MBB_THERMAL_PROTECT_SAR)
/* 50520 */      en_NV_Item_TEMP_PROTECT_SAR_REDUCTION = 50520,
#endif
#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
/* 50547 */      en_NV_VSIM_PSIM_HVSDH_INFO = 50547,
/* 50548 */      en_NV_VSIM_SSIM_HVSDH_INFO = 50548,
#endif
/* 50577 */      en_NV_Item_USB_SECURITY_FLAG    = 50577,
/* 50607 */      en_NV_Item_FTEN_USB_SWITCH_SEL = 50607,
/* 52000 */      en_NV_Item_WIFI_STATUS_SSID = 52000,
/* 52001 */      en_NV_Item_WEB_ADMIN_PASSWORD = 52001,
/* 52002 */      en_NV_Item_AP_RPT_SRV_URL = 52002,
/* 52003 */      en_NV_Item_AP_XML_INFO_TYPE = 52003,
/* 52004 */      en_NV_Item_AP_XML_RPT_FLAG = 52004,
/* 52005 */      en_NV_Item_BATT_LOW_TEMP_PROTECT = 52005,
/* 52006 */      en_NV_Item_ISDB_DEFAULT_KEY = 52006,

/* 52008 */      en_NV_Item_REFRESH_TERMINAL_RESPONSE_CP_OR_AP = 52008,

                 en_NV_Item_SYS_Butt
};


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* __SYSNVID_H__ */


