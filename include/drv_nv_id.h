

#ifndef __DRV_NV_ID_H__
#define __DRV_NV_ID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*
 *  NV ID ����Ӱ���С��������
 */

typedef enum
{
    NV_ID_DRV_IMEI                         = 0,
    NV_ID_DRV_RESUME_FLAG                  = 4,
    NV_ID_DRV_LED_CONTROL                  = 7,
    NV_ID_DRV_UE_POINT_CTRL                = 15,    /*����δʹ��*/
    NV_ID_DRV_EXCEPTION_RECORD             = 17,
    NV_ID_DRV_SYS_PRTTASK                  = 20,
    NV_ID_DRV_USB_ENUM_STATUS              = 21,
    NV_ID_DRV_LIVE_TIME_CONTROL            = 22,
    NV_ID_DRV_LIVE_TIME                    = 23,
    NV_ID_DRV_CUSTOM_REWIND_DELAY_TIME_I   = 25,     /*����δʹ��*/
    NV_ID_DRV_USBSN_NV_INFO                = 26,
    NV_ID_DRV_HW_VER                       = 30,
    NV_ID_DRV_PID_ENABLE_TYPE              = 31,
    NV_ID_DRV_AT_SHELL_OPNE                = 33,
    NV_ID_DRV_VER_FLAG                     = 36,
    NV_ID_DRV_BATTERY_TEMP_HKADC           = 35,
    NV_ID_DRV_CUSTOMIZE_TYPE               = 41,
    NV_ID_DRV_OLED_TEMP_ADC                = 49,
    NV_ID_DRV_ITEM_MODIFY_LINKINFO_FLAG    = 50,
    NV_ID_DRV_WEBNAS_SD_WORK_MODE          = 51,
    NV_ID_DRV_HW_WDT_FLAG                  = 52,
    NV_ID_DRV_POWER_LED_ENABLE             = 54,
    NV_ID_DRV_NV_HW_CONFIG                 = 55,
    NV_ID_DRV_NV_KPD_CONFIG                = 56,
    NV_ID_DRV_WIFI_TARGET_ASSERT_ENABLE    = 57,
    NV_ID_DRV_HILINK_AUTORUN_FLAG          = 61,
    NV_ID_DRV_NV_BATTERY                   = 90,
    NV_ID_DRV_NV_FACTORY_INFO_I            = 114,
    NV_ID_DRV_NV_USB_LOG_SAVELEV           = 118,
    NV_ID_DRV_NV_USB_MNTN_FLAG             = 119,
	NV_ID_DRV_SCI_DSDA_SELECT          	   = 128,
    /* log2.0 2014-03-19 begin */
    NV_ID_DRV_SOCP_LOG_CFG                 = 132,
    /* log2.0 2014-03-19 End */
    NV_ID_DRV_GUMODE_CHAN_PARA             = 138,
#if (FEATURE_ON == MBB_COMMON)
    NV_ID_DRV_MULTI_WIFI_KEY               = 9110,
    NV_ID_DRV_MULTI_WIFI_STATUS_SSID       = 9111,
#endif
    NV_ID_DRV_NV_DRV_VERSION_REPLACE_I     = 50018,
    NV_ID_DRV_DEFAULT_RATE                 = 50027,
    NV_ID_DRV_PPP_DIAL_ERR_CODE            = 50061,
    NV_ID_DRV_CUST_PID_TYPE                = 50071,
    NV_ID_DRV_USB_DYNAMIC_PID_TYPE_PARAM   = 50091,
    NV_ID_DRV_PROTOCOL_BASE_TYPE           = 50110,
    NV_ID_DRV_SEC_BOOT_ENABLE_FLAG         = 50201,
#if (FEATURE_ON == MBB_COMMON)
    NV_ID_DRV_USB_MBIM_PARAM               = 50424,
    NV_ID_DRV_USB_SECURITY_FLAG            = 50577,
#endif
#if (FEATURE_ON == MBB_SMS_CTRL_WIFI)
    NV_ID_DRV_SMS_CTRL_WIFI                   =50609,
#endif
    NV_ID_DRV_WIFI_STATUS_SSID             = 52000,
    NV_ID_DRV_BATT_LOW_TEMP_PROTECT        = 52005,
    NV_ID_DRV_LED_PARA                       = 50455,
#if (FEATURE_ON == MBB_FEATURE_CAT_MODULE_SET)
    NV_ID_DRV_PLATFORM_CATEGORY_SET        = 50458,
#endif
#if (FEATURE_ON == MBB_COMMON)
    NV_ID_TELNET_SWITCH_I                  = 50501,
    NV_ID_DATA_LOCK_I                      = 50502,
    NV_ID_DRV_MAC_NUM                      = 50517,
#endif
    NV_ID_DRV_NV_WIFI_INFO                 = 9040,
#if (FEATURE_ON == MBB_THERMAL_PROTECT_SAR)
    NV_ID_TEMP_PROTECT_SAR_REDUCTION       = 50520,
#endif
#if (FEATURE_ON == MBB_COMMON)
    NV_ID_DRV_WPS_PIN                      = 0xCB8D,
#endif
    NV_ID_DRV_TLMODE_CHAN_PARA_STRU        = 0xD01b,
    NV_ID_DRV_PASTAR_BUCK2_SWITCH          = 0xd109,
    NV_ID_DRV_NV_TEMP_ADC                  = 0xd10a,
    NV_ID_DRV_NV_PWC_SWITCH                = 0xd10b,
    NV_ID_DRV_NV_DFS_SWITCH                = 0xd10c,
    NV_ID_DRV_NV_PMU_EXC_PRO               = 0xd10f,
    NV_ID_DRV_NETIF_INIT_PARAM             = 0xd110,
	NV_ID_DRV_DUMP						   = 0xd111,
    NV_ID_DRV_POWER_KEY_TIME               = 0xd112,
    NV_ID_DRV_BOOT_TRY_TIMES               = 0xd113,
    NV_ID_DRV_NV_PMU_INIT				   = 0xd114,
	NV_ID_DRV_NV_VERSION_INIT			   = 0xd115,
	NV_ID_DRV_NV_MIPI_0_CHN				   = 0xd116,
	NV_ID_DRV_NV_MIPI_1_CHN				   = 0xd117,
	NV_ID_DRV_MODULE_SUPPORT    		   = 0xd118,
    NV_ID_DRV_COUL_CALI                    = 0xd119,
	NV_ID_DRV_TEMP_HKADC_CONFIG            = 0xd120,
	NV_ID_DRV_TEMP_TSENS_CONFIG            = 0xd121,
	NV_ID_DRV_TEMP_BATTERY_CONFIG          = 0xd122,
	NV_ID_DRV_WIN7_FEATURE                 = 0xd123,
	NV_ID_DRV_SCI_GCF_STUB_FLAG            = 0xd125,
    NV_ID_DRV_TEMP_CHAN_MAP                = 0xd126,
	NV_ID_DRV_UART_SHELL_FLAG              = 0Xd127,
	NV_ID_DRV_PM                           = 0Xd128,
    NV_ID_DRV_TSENS_TABLE                  = 0xd129,
	NV_ID_DRV_PM_CLKINIT                   = 0xd12a,
    NV_ID_DRV_TCXO_SEL                 	   = 0xd12b,
	NV_ID_DRV_USB_DBG                 	   = 0xd12c,
    NV_ID_DRV_WDT_INIT_PARAM               = 0xd12d,
	NV_ID_DRV_RFPOWER_UNIT                 = 0xd12e,
	NV_ID_DRV_TSENSOR_TRIM                 = 0xd12f,
	NV_ID_DRV_AMON                         = 0xd130,
    NV_ID_RF_SWITCH_CFG                    = 0xd131,
	NV_ID_DRV_SOCP_ON_DEMAND               = 0xd132,
	NV_ID_DRV_DRX_DELAY                    = 0xd133,
	NV_ID_DRV_CCORE_RESET                  = 0xd134,
	NV_ID_DRV_DUAL_MODEM		   		   = 0xd135,
    NV_ID_DRV_PASTAR_SWITCH                = 0xd136,
	NV_ID_DRV_LDO_GPIO_CFG   		       = 0xd137,
	NV_ID_DRV_ANTEN_CFG  		   		   = 0xd138,
	NV_ID_RF_RSE_CFG  		   		       = 0xd139,
	NV_ID_DRV_PAPOWER_UNIT  		   	   = 0xd13A,
	NV_ID_DRV_ANTN_UNPD_FLAG               = 0xd13b,
	NV_ID_DRV_ANTN_UNPD_CFG                = 0xd13c,
	NV_ID_DRV_MMC_FEATURE	               = 0xd13d,
	NV_ID_DRV_PA_RF_SWITCH                 = 0xd13e,
	NV_ID_DRV_DIALUP_ACSHELL			   = 0xd13f,
    /*����С˳�����*/
    NV_ID_DRV_ID_MAX                       = 0xd1ff

}NV_ID_DRV_ENUM;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

