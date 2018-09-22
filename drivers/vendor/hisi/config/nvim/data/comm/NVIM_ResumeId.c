/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: NVIM_ResumeId.c                                                 */
/*                                                                           */
/* Author: Jiang kaibo                                                       */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-06                                                             */
/*                                                                           */
/* Description: Def NV Resume ID list                                        */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2008-06                                                          */
/*    Author: Jiang kaibo                                                    */
/*    Modification: Create this file                                         */
/*                                                                           */
/*------------------------------���ⵥ�޸ļ�¼------------------------------------
  ���ⵥ��                �޸���      �޸�ʱ��      �޸�˵��                             
  DTS2013121105254       ������      2013-12-20   ����ڻָ��������û��ư������б�
  DTS2014021503311     ankang 00252937   2014-02-15   CAT3��CAT4���ݷ���
  DTS2014050602535     shiyuan 00216562  2014-05-12   ���屸�ݻָ��б�����Ӷ�wan��nv50410
  NA                    wanghaijie 00195735    2014-06-16            ����simlock 3.0 NV ��NV�ָ��б�
  DTS2014081305328      zhaoyongjie 00182327   2014-08-25            ���Telstra����NV���ݻָ��Ͱ������б�
  DTS2014091203795      w00249971           2014-09-18               MAC��ַ��һ��������
  DTS2014103103265         2014-10-31     jwx240957           ����VODAFONE���Ե�����AT����AT^SKU��AT^ACCOUNT
  DTS2014101508483      wangjing  wx225651    2014-11-20      ��E8372h-153�����������ָ��������ú�������ѡ��ʽ��Ϊ֮ǰ�޸ĵ���ʽ
  DTS2014120201317      lihong wx235260      2014-12-3        ��E5770s-923���ع����ߣ�����NV������
  DTS2016030704443      wwx314170            2016-3-15          USB��ȫ�˿ڷ����Ͽ�
  DTS2016070400554      wwx235254            2016-7-4         ��MS2172s-818��˫usb�л�����nv�Ͽ�
  DTS2016071501529      qwx379719            2016-07-15         SIMLOCK4.0��������
  DTS2016071409366      lwx223199            2016-07-15        MS2172s-818 ���ſ���Wi-Fi����ʵ��
  DTS2016112407108      lwx337763            2016-11-28       ��MS2172s-818�������ơ�������ע�� ���֡��޸�NV8302�еļ�Ȩ��ʽ���û���������ָ������󣬲鿴NV8302����ָ���ԭ��Ҫ��Ķ�����Ϣ
  DTS2016112902999      lwx337763            2016-11-29       ��MS2172s-818����V711�������⡿���屻�ָ��������ú���Ȼ����������ʷƵ�㣬��һ����������LTE BandĬ��˳���п�ǰBand���������µ�������޷�ע�ᵽ�źŽϺõ�Ƶ��
  DTS2017022206556      lwx337763            2017-02-28       ��V711�������⡿��WebUI_���֡���B20�漰������LTE��Ƶ�Σ��磺FDD800 only��,Ȼ��ָ��������ָ�����������ģʽΪauto����LTE����Ƶ����Ȼ��FDD800 only����ʱҳ����ʾΪauto��
  AR0008UB4R            ywx235257            2017-03-03       ��E5577s-324���ձ������������� ��LTEע��ʱ����APN��ѯattach
  DTS2017031510262      fwx245578            2017-03-15       ����607HW��Ʒ����������ˢ�±��ݻָ��ͻָ��������б�
  AR00099N0A            zwx241801            2017-5-18        ��E5577s-324���ձ�����,APN attach�·���
  DTS2017040709958      lwx337763            2017-06-27       ��3GƵ�� ���֡�����ˢ���°汾��3G������£��·�at^SYSCFGEX="02",400000,1,2,7fffffffffffffff,,����Ƶ�κ�Ȼ��ָ�������ʹ��at^SYSCFGEX���鿴��������3GƵ��
------------------------------------------------------------------------------*/

/*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "NVIM_ResumeId.h"
#include "NvIdList.h"
#include "drv_nvim.h"

#if (RAT_MODE != RAT_GU)
#include "LNvCommon.h"
#endif

/*BEGIN DTS2013092201594 yaozhanwei 2013-05-25 added for backup and recovery*/
#include "mbb_config.h"
#if (FEATURE_ON == MBB_COMMON)
#include "product_nv_id.h"
#endif
/*END DTS2013092201594 yaozhanwei 2013-05-25 added for backup and recovery*/

/* Manufacture ID need to restore */
unsigned short  g_ausNvResumeManufactureIdList[] =
{
    en_NV_Item_USB_Enum_Status,

    en_NV_Item_IMEI,
    en_NV_Auth_Code_ID,
    en_NV_Auth_Num_ID,
    en_NV_Item_Serial_Num,
    en_NV_Item_LiveTime,
    en_NV_Item_ManufactureInfo,
    en_NV_Item_BATT_TEMP_SENSOR_TABLE,
    en_NV_Item_CCA_TelePara,
    en_NV_Item_Factory_Info,
    en_NV_Item_BODY_SAR_PARA,
#if (FEATURE_ON == MBB_SMS_CTRL_WIFI)
    NV_SMS_CTRL_WIFI_INFO,
#endif
#if (FEATURE_ON == MBB_FEATURE_CAT_MODULE_SET)
    en_NV_Item_CATEGORY_VALUE,
#endif
#if (FEATURE_ON == MBB_TELSTRA_CUSTOMSIZE)
    en_NV_Item_RAT_PRIO_LIST,
#endif
/*BEGIN DTS2013123106578  w00228874 2013-12-30 added*/
#if ( FEATURE_ON == MBB_COMMON )
    /* �ɼ���־��Ϊ �������ݻָ��� */     
    en_NV_Item_CSOS_VALUE,
#endif
/*END DTS2013123106578  w00228874 2013-12-30 added*/
    en_NV_Item_BATTERY_ADC,
    en_NV_Item_WIFI_KEY,
    en_NV_Item_WIFI_MAC_ADDR,
    en_NV_Item_PRI_VERSION,
    en_NV_Item_WIFI_STATUS_SSID,
    en_NV_Item_WEB_ADMIN_PASSWORD,
    /*BEGIN DTS2013092201594 yaozhanwei 2013-05-25 added for backup and recovery*/
#if (FEATURE_ON == MBB_COMMON)
    NV_ID_WEB_SITE,
    NV_ID_WPS_PIN,
    NV_ID_WEB_USER_NAME,    
    NV_TELNET_SWITCH_I,
#endif
    /*END DTS2013092201594 yaozhanwei 2013-05-25 added for backup and recovery*/

#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
    NV_FTEN_USB_SWITCH_SEL,
#endif

/*BEGIN DTS2013093002669  l00212897 2013/09/30 modified*/
#if (MBB_CHARGE == FEATURE_ON)
    EN_NV_ID_BATT_CALIBRATION,
#endif
/*END DTS2013093002669  l00212897 2013/09/30 modified*/
#if (FEATURE_OFF == MBB_FEATURE_SBM_CUSTOMIZE)
    en_NV_Item_DSFLOW_REPORT,
#if (FEATURE_ON == MBB_COMMON)
    NV_ID_DSFLOW_REPORT_MUTI_WAN,
#endif
#endif/*FEATURE_OFF == MBB_FEATURE_SBM_CUSTOMIZE*/
    en_NV_Item_MULTI_WIFI_KEY,
    en_NV_Item_MULTI_WIFI_STATUS_SSID,

    en_NV_Item_XO_INIT_FREQUENCY,
    en_NV_Item_XO_DYNAMIC_FREQUENCY,
    en_NV_Item_DCXO_C_TRIM,
    en_NV_Item_DCXO_TEMP_COMP,
    en_NV_Item_DCXO_SEARCH_AFC_OFFSET,
    en_NV_Item_VSIM_HVSDH_INFO,
    en_NV_Item_XO_INIT_LOW_TEMP,
#if ((FEATURE_ON == MBB_SIMLOCK_THREE) || (FEATURE_ON == MBB_SIMLOCK_FOUR))
    NV_HUAWEI_OEMLOCK_I,  
    NV_HUAWEI_SIMLOCK_I,
#endif
#if (FEATURE_ON == MBB_COMMON)
    en_NV_Item_MAC_NUM,
#endif
/* BEGIN DTS2014120201317 lwx235260 2014-12-3 added */
    NV_HUAWEI_BATTERY_INFO_I,
/* END DTS2014120201317 lwx235260 2014-12-3 added */
#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
/*BEGIN DTS2015092800364  xianshijie 81004927 2015-9-28 added*/
    en_NV_Item_VSIM_SUPPORT_FLAG,
/*END DTS2015092800364  xianshijie 81004927 2015-9-28 added*/
/*BEGIN DTS2015090601556 xianshijie 81004927 2015-9-6 added*/
    en_NV_VSIM_PSIM_HVSDH_INFO,
    en_NV_VSIM_SSIM_HVSDH_INFO,
/*BEGIN DTS2015100803920 xianshijie 81004927 2015-10-8 added*/
    NV_VSIM_DEVICE_KEY_INFO,
    NV_VSIM_CONTENT_KEY_INFO,
    NV_Item_VSIM_Ue_Mode,
    NV_VSIM_DIEID_INFO,
/*END DTS2015100803920 xianshijie 81004927 2015-10-8 added*/
/*END DTS2015090601556 xianshijie 81004927 2015-9-6 added*/
#endif
/* BEGIN  DTS2014103103265 jWX240957  2014-10-31 added*/
#if(FEATURE_ON == MBB_OPERATOR_VDF)
    NV_ITEM_SKU_TYPE,                            /* 0xC4A0*/
    NV_ITEM_ACCOUNT_TYPE,                        /* 0xC4A1*/
#endif
/* END DTS2014103103265 jWX240957  2014-10-31 added*/

#if (FEATURE_ON == MBB_WPG_LTE_ATTACH_APN_LIST)
    NV_ID_LTE_ATTACH_PROFILE_0,                  /*50578*/
#endif
#if (FEATURE_ON == MBB_WPG_APNLIST_UPDATE_NVBAK)
    NV_ID_LTE_ATTACH_PROFILE_CONTROL,         /*50591*/
#endif

#if (FEATURE_ON == MBB_FEATURE_SBM_CUSTOMIZE)
    en_NV_Item_RAT_PRIO_LIST,
    en_NV_Item_SelPlmn_Mode,
    en_NV_Item_Taf_PdpPara_1,
    en_NV_Item_NDIS_Authdata_1,
#endif/*FEATURE_ON == MBB_FEATURE_SBM_CUSTOMIZE*/

    /* Gsm 850 */
    en_NV_Item_GSM850_RX_DCOFFSET,
    en_NV_Item_GSM850_RX_AGC_GAIN,
    en_NV_Item_GSM850_RX_AGC_FREQ_COMP,
    en_NV_Item_GSM850_TX_IQ_MISMATCH,
    en_NV_Item_GSM850_TX_POWER,
    en_NV_Item_GSM850_TX_DAC,
    en_NV_Item_EDGE850_TX_PA_GAIN,
    en_NV_Item_EDGE850_TX_RF_GAIN_ATTEN,
    en_NV_Item_EDGE850_TX_APC_CAL_TEMP,
    en_NV_Item_EDGE850_TX_APC_RFIC_CTRL,
    en_NV_Item_EDGE850_TX_APC_DBB_ATTEN,
    en_NV_Item_EDGE850_TX_RF_GAIN_STATE_INDEX,
    en_NV_Item_EDGE850_PA_VBIAS_COMP,
    en_NV_Item_GSM850_PA_PRECHG_VOLT,
    en_NV_Item_GSM850_LINEAR_PA_GAIN,
    en_NV_Item_GSM850_TX_LINEAR_RFIC_GAIN_CTRL,
    en_NV_Item_GSM850_TX_RF_GAIN_ATTEN,
    en_NV_Item_GSM850_LINEAR_DBB_ATTEN,
    en_NV_Item_EDGE850_LINEAR_PA_GAIN,
    en_NV_Item_GSM850_TX_LINEAR_APC_CAL_TEMP,
    en_NV_Item_GSM850_TX_GAIN0_FREQ_COMP,
    en_NV_Item_GSM850_TX_GAIN1_FREQ_COMP,
    en_NV_Item_GSM850_TX_GAIN2_FREQ_COMP,
    en_NV_Item_GSM850_TX_GAIN3_FREQ_COMP,
    en_NV_Item_EDGE850_TX_GAIN0_FREQ_COMP,
    en_NV_Item_EDGE850_TX_GAIN1_FREQ_COMP,
    en_NV_Item_EDGE850_TX_GAIN2_FREQ_COMP,
    en_NV_Item_EDGE850_TX_GAIN3_FREQ_COMP,
    
    /* Gsm 900 */
    en_NV_Item_GSM900_RX_DCOFFSET,
    en_NV_Item_GSM900_RX_AGC_GAIN,
    en_NV_Item_GSM900_RX_AGC_FREQ_COMP,
    en_NV_Item_GSM900_TX_IQ_MISMATCH,
    en_NV_Item_GSM900_TX_POWER,
    en_NV_Item_GSM900_TX_DAC,
    en_NV_Item_EDGE900_TX_PA_GAIN,
    en_NV_Item_EDGE900_TX_RF_GAIN_ATTEN,
    en_NV_Item_EDGE900_TX_APC_CAL_TEMP,
    en_NV_Item_EDGE900_TX_APC_RFIC_CTRL,
    en_NV_Item_EDGE900_TX_APC_DBB_ATTEN,
    en_NV_Item_EDGE900_TX_RF_GAIN_STATE_INDEX,
    en_NV_Item_EDGE900_PA_VBIAS_COMP,
    en_NV_Item_GSM900_PA_PRECHG_VOLT,
    en_NV_Item_GSM900_LINEAR_PA_GAIN,
    en_NV_Item_GSM900_TX_LINEAR_RFIC_GAIN_CTRL,
    en_NV_Item_GSM900_TX_RF_GAIN_ATTEN,
    en_NV_Item_GSM900_LINEAR_DBB_ATTEN,
    en_NV_Item_EDGE900_LINEAR_PA_GAIN,
    en_NV_Item_GSM900_TX_LINEAR_APC_CAL_TEMP,
    en_NV_Item_GSM900_TX_GAIN0_FREQ_COMP,
    en_NV_Item_GSM900_TX_GAIN1_FREQ_COMP,
    en_NV_Item_GSM900_TX_GAIN2_FREQ_COMP,
    en_NV_Item_GSM900_TX_GAIN3_FREQ_COMP,
    en_NV_Item_EDGE900_TX_GAIN0_FREQ_COMP,
    en_NV_Item_EDGE900_TX_GAIN1_FREQ_COMP,
    en_NV_Item_EDGE900_TX_GAIN2_FREQ_COMP,
    en_NV_Item_EDGE900_TX_GAIN3_FREQ_COMP,

    /* Gsm 1800 */
    en_NV_Item_DCS1800_RX_DCOFFSET,
    en_NV_Item_DCS1800_RX_AGC_GAIN,
    en_NV_Item_DCS1800_RX_AGC_FREQ_COMP,
    en_NV_Item_DCS1800_TX_IQ_MISMATCH,
    en_NV_Item_DCS1800_TX_POWER,
    en_NV_Item_DCS1800_TX_DAC,
    en_NV_Item_EDGE1800_TX_PA_GAIN,
    en_NV_Item_EDGE1800_TX_RF_GAIN_ATTEN,
    en_NV_Item_EDGE1800_TX_APC_CAL_TEMP,
    en_NV_Item_EDGE1800_TX_APC_RFIC_CTRL,
    en_NV_Item_EDGE1800_TX_APC_DBB_ATTEN,
    en_NV_Item_EDGE1800_TX_RF_GAIN_STATE_INDEX,
    en_NV_Item_EDGE1800_PA_VBIAS_COMP,
    en_NV_Item_DCS1800_PA_PRECHG_VOLT,
    en_NV_Item_DCS1800_LINEAR_PA_GAIN,
    en_NV_Item_DCS1800_TX_LINEAR_RFIC_GAIN_CTRL,
    en_NV_Item_DCS1800_TX_RF_GAIN_ATTEN,
    en_NV_Item_DCS1800_LINEAR_DBB_ATTEN,
    en_NV_Item_EDGE1800_LINEAR_PA_GAIN,
    en_NV_Item_DCS1800_TX_LINEAR_APC_CAL_TEMP,
    en_NV_Item_DCS1800_TX_GAIN0_FREQ_COMP,
    en_NV_Item_DCS1800_TX_GAIN1_FREQ_COMP,
    en_NV_Item_DCS1800_TX_GAIN2_FREQ_COMP,
    en_NV_Item_DCS1800_TX_GAIN3_FREQ_COMP,
    en_NV_Item_EDGE1800_TX_GAIN0_FREQ_COMP,
    en_NV_Item_EDGE1800_TX_GAIN1_FREQ_COMP,
    en_NV_Item_EDGE1800_TX_GAIN2_FREQ_COMP,
    en_NV_Item_EDGE1800_TX_GAIN3_FREQ_COMP,
     
    /* Gsm 1900 */
    en_NV_Item_PCS1900_RX_DCOFFSET,
    en_NV_Item_PCS1900_RX_AGC_GAIN,
    en_NV_Item_PCS1900_RX_AGC_FREQ_COMP,
    en_NV_Item_PCS1900_TX_IQ_MISMATCH,
    en_NV_Item_PCS1900_TX_POWER,
    en_NV_Item_PCS1900_TX_DAC,
    en_NV_Item_EDGE1900_TX_PA_GAIN,
    en_NV_Item_EDGE1900_TX_RF_GAIN_ATTEN,
    en_NV_Item_EDGE1900_TX_APC_CAL_TEMP,
    en_NV_Item_EDGE1900_TX_APC_RFIC_CTRL,
    en_NV_Item_EDGE1900_TX_APC_DBB_ATTEN,
    en_NV_Item_EDGE1900_TX_RF_GAIN_STATE_INDEX,
    en_NV_Item_EDGE1900_PA_VBIAS_COMP,
    en_NV_Item_PCS1900_PA_PRECHG_VOLT,
    en_NV_Item_PCS1900_LINEAR_PA_GAIN,
    en_NV_Item_PCS1900_TX_LINEAR_RFIC_GAIN_CTRL,
    en_NV_Item_PCS1900_TX_RF_GAIN_ATTEN,
    en_NV_Item_PCS1900_LINEAR_DBB_ATTEN,
    en_NV_Item_EDGE1900_LINEAR_PA_GAIN,
    en_NV_Item_PCS1900_TX_LINEAR_APC_CAL_TEMP,
    en_NV_Item_PCS1900_TX_GAIN0_FREQ_COMP,
    en_NV_Item_PCS1900_TX_GAIN1_FREQ_COMP,
    en_NV_Item_PCS1900_TX_GAIN2_FREQ_COMP,
    en_NV_Item_PCS1900_TX_GAIN3_FREQ_COMP,
    en_NV_Item_EDGE1900_TX_GAIN0_FREQ_COMP,
    en_NV_Item_EDGE1900_TX_GAIN1_FREQ_COMP,
    en_NV_Item_EDGE1900_TX_GAIN2_FREQ_COMP,
    en_NV_Item_EDGE1900_TX_GAIN3_FREQ_COMP,

    /* CMCC 1800 */
    en_NV_Item_CMCC1800_RX_DCOFFSET,
    en_NV_Item_CMCC1800_RX_AGC_GAIN,
    en_NV_Item_CMCC1800_RX_AGC_FREQ_COMP,

    /* wcdma band1 */
    en_NV_Item_W_RX_IP2_CAL_AT1_B1,
    en_NV_Item_W_RX_IP2_CAL_AT2_B1,
    en_NV_Item_W_RX_DCOFFSET_B1,
    en_NV_Item_W_RX_AGC_GAIN_B1,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT1_B1,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT2_B1,
    en_NV_Item_W_TX_IQ_MISMATCH_B1,
    en_NV_Item_W_TX_APC_TEMP_B1,
    en_NV_Item_W_TX_PA_GAIN_B1,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_B1,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_B1,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_B1,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_B1,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_B1,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_B1,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_B1,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_B1,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_B1,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_B1,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_B1,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_B1,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_HDET_VGA_B1,
    en_NV_Item_W_TX_HDET_DCOFFSET_B1,
    en_NV_Item_W_TX_HDET_POWER_B1,
    en_NV_Item_W_TX_HDET_HKADC_B1,
    en_NV_Item_W_TX_HDET_FREQ_COMP_B1,
    en_NV_Item_W_TX_HIGH_GAIN_FREQ_COMP_B1,
    en_NV_Item_W_TX_MID_GAIN_FREQ_COMP_B1,
    en_NV_Item_W_TX_LOW_GAIN_FREQ_COMP_B1,
    en_NV_Item_W_TX_HIGH_GAIN_APT_COMP_B1,
    en_NV_Item_W_TX_MID_GAIN_APT_COMP_B1,
    en_NV_Item_W_TX_LOW_GAIN_APT_COMP_B1,
    en_NV_Item_W_TX_PA_GAIN_VOICE_MODE_B1,
    en_NV_Item_W_TX_PA_APT_TABLE_HIGH_GAIN_B1,
    en_NV_Item_W_TX_PA_APT_TABLE_MID_GAIN_B1,
    en_NV_Item_W_TX_PA_APT_TABLE_LOW_GAIN_B1,


    /* wcdma band2 */
    en_NV_Item_W_RX_IP2_CAL_AT1_B2,
    en_NV_Item_W_RX_IP2_CAL_AT2_B2,
    en_NV_Item_W_RX_DCOFFSET_B2,
    en_NV_Item_W_RX_AGC_GAIN_B2,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT1_B2,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT2_B2,
    en_NV_Item_W_TX_IQ_MISMATCH_B2,
    en_NV_Item_W_TX_APC_TEMP_B2,
    en_NV_Item_W_TX_PA_GAIN_B2,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_B2,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_B2,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_B2,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_B2,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_B2,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_B2,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_B2,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_B2,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_B2,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_B2,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_B2,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_B2,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_HDET_VGA_B2,
    en_NV_Item_W_TX_HDET_DCOFFSET_B2,
    en_NV_Item_W_TX_HDET_POWER_B2,
    en_NV_Item_W_TX_HDET_HKADC_B2,
    en_NV_Item_W_TX_HDET_FREQ_COMP_B2,
    en_NV_Item_W_TX_HIGH_GAIN_FREQ_COMP_B2,
    en_NV_Item_W_TX_MID_GAIN_FREQ_COMP_B2,
    en_NV_Item_W_TX_LOW_GAIN_FREQ_COMP_B2,
    en_NV_Item_W_TX_HIGH_GAIN_APT_COMP_B2,
    en_NV_Item_W_TX_MID_GAIN_APT_COMP_B2,
    en_NV_Item_W_TX_LOW_GAIN_APT_COMP_B2,
    en_NV_Item_W_TX_PA_GAIN_VOICE_MODE_B2,
    en_NV_Item_W_TX_PA_APT_TABLE_HIGH_GAIN_B2,
    en_NV_Item_W_TX_PA_APT_TABLE_MID_GAIN_B2,
    en_NV_Item_W_TX_PA_APT_TABLE_LOW_GAIN_B2,


    /* wcdma band3 */
    en_NV_Item_W_RX_IP2_CAL_AT1_B3,
    en_NV_Item_W_RX_IP2_CAL_AT2_B3,
    en_NV_Item_W_RX_DCOFFSET_B3,
    en_NV_Item_W_RX_AGC_GAIN_B3,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT1_B3,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT2_B3,
    en_NV_Item_W_TX_IQ_MISMATCH_B3,
    en_NV_Item_W_TX_APC_TEMP_B3,
    en_NV_Item_W_TX_PA_GAIN_B3,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_B3,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_B3,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_B3,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_B3,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_B3,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_B3,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_B3,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_B3,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_B3,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_B3,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_B3,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_B3,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_HDET_VGA_B3,
    en_NV_Item_W_TX_HDET_DCOFFSET_B3,
    en_NV_Item_W_TX_HDET_POWER_B3,
    en_NV_Item_W_TX_HDET_HKADC_B3,
    en_NV_Item_W_TX_HDET_FREQ_COMP_B3,
    en_NV_Item_W_TX_HIGH_GAIN_FREQ_COMP_B3,
    en_NV_Item_W_TX_MID_GAIN_FREQ_COMP_B3,
    en_NV_Item_W_TX_LOW_GAIN_FREQ_COMP_B3,
    en_NV_Item_W_TX_HIGH_GAIN_APT_COMP_B3,
    en_NV_Item_W_TX_MID_GAIN_APT_COMP_B3,
    en_NV_Item_W_TX_LOW_GAIN_APT_COMP_B3,
    en_NV_Item_W_TX_PA_GAIN_VOICE_MODE_B3,
    en_NV_Item_W_TX_PA_APT_TABLE_HIGH_GAIN_B3,
    en_NV_Item_W_TX_PA_APT_TABLE_MID_GAIN_B3,
    en_NV_Item_W_TX_PA_APT_TABLE_LOW_GAIN_B3,


    /* wcdma band4 */
    en_NV_Item_W_RX_IP2_CAL_AT1_B4,
    en_NV_Item_W_RX_IP2_CAL_AT2_B4,
    en_NV_Item_W_RX_DCOFFSET_B4,
    en_NV_Item_W_RX_AGC_GAIN_B4,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT1_B4,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT2_B4,
    en_NV_Item_W_TX_IQ_MISMATCH_B4,
    en_NV_Item_W_TX_APC_TEMP_B4,
    en_NV_Item_W_TX_PA_GAIN_B4,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_B4,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_B4,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_B4,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_B4,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_B4,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_B4,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_B4,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_B4,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_B4,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_B4,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_B4,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_B4,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_HDET_VGA_B4,
    en_NV_Item_W_TX_HDET_DCOFFSET_B4,
    en_NV_Item_W_TX_HDET_POWER_B4,
    en_NV_Item_W_TX_HDET_HKADC_B4,
    en_NV_Item_W_TX_HDET_FREQ_COMP_B4,
    en_NV_Item_W_TX_HIGH_GAIN_FREQ_COMP_B4,
    en_NV_Item_W_TX_MID_GAIN_FREQ_COMP_B4,
    en_NV_Item_W_TX_LOW_GAIN_FREQ_COMP_B4,
    en_NV_Item_W_TX_HIGH_GAIN_APT_COMP_B4,
    en_NV_Item_W_TX_MID_GAIN_APT_COMP_B4,
    en_NV_Item_W_TX_LOW_GAIN_APT_COMP_B4,
    en_NV_Item_W_TX_PA_GAIN_VOICE_MODE_B4,
    en_NV_Item_W_TX_PA_APT_TABLE_HIGH_GAIN_B4,
    en_NV_Item_W_TX_PA_APT_TABLE_MID_GAIN_B4,
    en_NV_Item_W_TX_PA_APT_TABLE_LOW_GAIN_B4,

    /* wcdma band5 */
    en_NV_Item_W_RX_IP2_CAL_AT1_B5,
    en_NV_Item_W_RX_IP2_CAL_AT2_B5,
    en_NV_Item_W_RX_DCOFFSET_B5,
    en_NV_Item_W_RX_AGC_GAIN_B5,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT1_B5,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT2_B5,
    en_NV_Item_W_TX_IQ_MISMATCH_B5,
    en_NV_Item_W_TX_APC_TEMP_B5,
    en_NV_Item_W_TX_PA_GAIN_B5,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_B5,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_B5,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_B5,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_B5,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_B5,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_B5,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_B5,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_B5,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_B5,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_B5,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_B5,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_B5,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_HDET_VGA_B5,
    en_NV_Item_W_TX_HDET_DCOFFSET_B5,
    en_NV_Item_W_TX_HDET_POWER_B5,
    en_NV_Item_W_TX_HDET_HKADC_B5,
    en_NV_Item_W_TX_HDET_FREQ_COMP_B5,
    en_NV_Item_W_TX_HIGH_GAIN_FREQ_COMP_B5,
    en_NV_Item_W_TX_MID_GAIN_FREQ_COMP_B5,
    en_NV_Item_W_TX_LOW_GAIN_FREQ_COMP_B5,
    en_NV_Item_W_TX_HIGH_GAIN_APT_COMP_B5,
    en_NV_Item_W_TX_MID_GAIN_APT_COMP_B5,
    en_NV_Item_W_TX_LOW_GAIN_APT_COMP_B5,
    en_NV_Item_W_TX_PA_GAIN_VOICE_MODE_B5,
    en_NV_Item_W_TX_PA_APT_TABLE_HIGH_GAIN_B5,
    en_NV_Item_W_TX_PA_APT_TABLE_MID_GAIN_B5,
    en_NV_Item_W_TX_PA_APT_TABLE_LOW_GAIN_B5,


    /* wcdma band6 */
    en_NV_Item_W_RX_IP2_CAL_AT1_B6,
    en_NV_Item_W_RX_IP2_CAL_AT2_B6,
    en_NV_Item_W_RX_DCOFFSET_B6,
    en_NV_Item_W_RX_AGC_GAIN_B6,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT1_B6,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT2_B6,
    en_NV_Item_W_TX_IQ_MISMATCH_B6,
    en_NV_Item_W_TX_APC_TEMP_B6,
    en_NV_Item_W_TX_PA_GAIN_B6,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_B6,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_B6,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_B6,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_B6,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_B6,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_B6,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_B6,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_B6,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_B6,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_B6,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_B6,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_B6,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_HDET_VGA_B6,
    en_NV_Item_W_TX_HDET_DCOFFSET_B6,
    en_NV_Item_W_TX_HDET_POWER_B6,
    en_NV_Item_W_TX_HDET_HKADC_B6,
    en_NV_Item_W_TX_HDET_FREQ_COMP_B6,
    en_NV_Item_W_TX_HIGH_GAIN_FREQ_COMP_B6,
    en_NV_Item_W_TX_MID_GAIN_FREQ_COMP_B6,
    en_NV_Item_W_TX_LOW_GAIN_FREQ_COMP_B6,
    en_NV_Item_W_TX_HIGH_GAIN_APT_COMP_B6,
    en_NV_Item_W_TX_MID_GAIN_APT_COMP_B6,
    en_NV_Item_W_TX_LOW_GAIN_APT_COMP_B6,
    en_NV_Item_W_TX_PA_GAIN_VOICE_MODE_B6,
    en_NV_Item_W_TX_PA_APT_TABLE_HIGH_GAIN_B6,
    en_NV_Item_W_TX_PA_APT_TABLE_MID_GAIN_B6,
    en_NV_Item_W_TX_PA_APT_TABLE_LOW_GAIN_B6,


    /* wcdma band8 */
    en_NV_Item_W_RX_IP2_CAL_AT1_B8,
    en_NV_Item_W_RX_IP2_CAL_AT2_B8,
    en_NV_Item_W_RX_DCOFFSET_B8,
    en_NV_Item_W_RX_AGC_GAIN_B8,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT1_B8,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT2_B8,
    en_NV_Item_W_TX_IQ_MISMATCH_B8,
    en_NV_Item_W_TX_APC_TEMP_B8,
    en_NV_Item_W_TX_PA_GAIN_B8,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_B8,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_B8,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_B8,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_B8,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_B8,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_B8,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_B8,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_B8,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_B8,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_B8,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_B8,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_B8,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_HDET_VGA_B8,
    en_NV_Item_W_TX_HDET_DCOFFSET_B8,
    en_NV_Item_W_TX_HDET_POWER_B8,
    en_NV_Item_W_TX_HDET_HKADC_B8,
    en_NV_Item_W_TX_HDET_FREQ_COMP_B8,
    en_NV_Item_W_TX_HIGH_GAIN_FREQ_COMP_B8,
    en_NV_Item_W_TX_MID_GAIN_FREQ_COMP_B8,
    en_NV_Item_W_TX_LOW_GAIN_FREQ_COMP_B8,
    en_NV_Item_W_TX_HIGH_GAIN_APT_COMP_B8,
    en_NV_Item_W_TX_MID_GAIN_APT_COMP_B8,
    en_NV_Item_W_TX_LOW_GAIN_APT_COMP_B8,
    en_NV_Item_W_TX_PA_GAIN_VOICE_MODE_B8,
    en_NV_Item_W_TX_PA_APT_TABLE_HIGH_GAIN_B8,
    en_NV_Item_W_TX_PA_APT_TABLE_MID_GAIN_B8,
    en_NV_Item_W_TX_PA_APT_TABLE_LOW_GAIN_B8,

    /* wcdma band9 */
    en_NV_Item_W_RX_IP2_CAL_AT1_B9,
    en_NV_Item_W_RX_IP2_CAL_AT2_B9,
    en_NV_Item_W_RX_DCOFFSET_B9,
    en_NV_Item_W_RX_AGC_GAIN_B9,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT1_B9,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT2_B9,
    en_NV_Item_W_TX_IQ_MISMATCH_B9,
    en_NV_Item_W_TX_APC_TEMP_B9,
    en_NV_Item_W_TX_PA_GAIN_B9,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_B9,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_B9,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_B9,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_B9,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_B9,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_B9,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_B9,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_B9,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_B9,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_B9,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_B9,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_B9,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_HDET_VGA_B9,
    en_NV_Item_W_TX_HDET_DCOFFSET_B9,
    en_NV_Item_W_TX_HDET_POWER_B9,
    en_NV_Item_W_TX_HDET_HKADC_B9,
    en_NV_Item_W_TX_HDET_FREQ_COMP_B9,
    en_NV_Item_W_TX_HIGH_GAIN_FREQ_COMP_B9,
    en_NV_Item_W_TX_MID_GAIN_FREQ_COMP_B9,
    en_NV_Item_W_TX_LOW_GAIN_FREQ_COMP_B9,
    en_NV_Item_W_TX_HIGH_GAIN_APT_COMP_B9,
    en_NV_Item_W_TX_MID_GAIN_APT_COMP_B9,
    en_NV_Item_W_TX_LOW_GAIN_APT_COMP_B9,
    en_NV_Item_W_TX_PA_GAIN_VOICE_MODE_B9,
    en_NV_Item_W_TX_PA_APT_TABLE_HIGH_GAIN_B9,
    en_NV_Item_W_TX_PA_APT_TABLE_MID_GAIN_B9,
    en_NV_Item_W_TX_PA_APT_TABLE_LOW_GAIN_B9,


    /* wcdma band11 */
    en_NV_Item_W_RX_IP2_CAL_AT1_B11,
    en_NV_Item_W_RX_IP2_CAL_AT2_B11,
    en_NV_Item_W_RX_DCOFFSET_B11,
    en_NV_Item_W_RX_AGC_GAIN_B11,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT1_B11,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT2_B11,
    en_NV_Item_W_TX_IQ_MISMATCH_B11,
    en_NV_Item_W_TX_APC_TEMP_B11,
    en_NV_Item_W_TX_PA_GAIN_B11,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_B11,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_B11,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_B11,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_B11,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_B11,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_B11,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_B11,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_B11,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_B11,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_B11,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_B11,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_B11,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_HDET_VGA_B11,
    en_NV_Item_W_TX_HDET_DCOFFSET_B11,
    en_NV_Item_W_TX_HDET_POWER_B11,
    en_NV_Item_W_TX_HDET_HKADC_B11,
    en_NV_Item_W_TX_HDET_FREQ_COMP_B11,
    en_NV_Item_W_TX_HIGH_GAIN_FREQ_COMP_B11,
    en_NV_Item_W_TX_MID_GAIN_FREQ_COMP_B11,
    en_NV_Item_W_TX_LOW_GAIN_FREQ_COMP_B11,
    en_NV_Item_W_TX_HIGH_GAIN_APT_COMP_B11,
    en_NV_Item_W_TX_MID_GAIN_APT_COMP_B11,
    en_NV_Item_W_TX_LOW_GAIN_APT_COMP_B11,
    en_NV_Item_W_TX_PA_GAIN_VOICE_MODE_B11,
    en_NV_Item_W_TX_PA_APT_TABLE_HIGH_GAIN_B11,
    en_NV_Item_W_TX_PA_APT_TABLE_MID_GAIN_B11,
    en_NV_Item_W_TX_PA_APT_TABLE_LOW_GAIN_B11,


    /* wcdma band19 */
    en_NV_Item_W_RX_IP2_CAL_AT1_B19,
    en_NV_Item_W_RX_IP2_CAL_AT2_B19,
    en_NV_Item_W_RX_DCOFFSET_B19,
    en_NV_Item_W_RX_AGC_GAIN_B19,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT1_B19,
    en_NV_Item_W_RX_AGC_FREQ_COMP_AT2_B19,
    en_NV_Item_W_TX_IQ_MISMATCH_B19,
    en_NV_Item_W_TX_APC_TEMP_B19,
    en_NV_Item_W_TX_PA_GAIN_B19,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_B19,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_B19,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_B19,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_B19,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_B19,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_B19,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_B19,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_B19,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_B19,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_B19,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_B19,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_B19,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_HIGH_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_MID_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_RF_GAIN_ATTEN_LOW_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_HIGH_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_MID_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_RF_GAIN_STATE_INDEX_LOW_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_APC_RFIC_CTRL_HIGH_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_APC_RFIC_CTRL_MID_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_APC_RFIC_CTRL_LOW_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_APC_DBB_ATTEN_HIGH_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_APC_DBB_ATTEN_MID_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_APC_DBB_ATTEN_LOW_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_HDET_VGA_B19,
    en_NV_Item_W_TX_HDET_DCOFFSET_B19,
    en_NV_Item_W_TX_HDET_POWER_B19,
    en_NV_Item_W_TX_HDET_HKADC_B19,
    en_NV_Item_W_TX_HDET_FREQ_COMP_B19,
    en_NV_Item_W_TX_HIGH_GAIN_FREQ_COMP_B19,
    en_NV_Item_W_TX_MID_GAIN_FREQ_COMP_B19,
    en_NV_Item_W_TX_LOW_GAIN_FREQ_COMP_B19,
    en_NV_Item_W_TX_HIGH_GAIN_APT_COMP_B19,
    en_NV_Item_W_TX_MID_GAIN_APT_COMP_B19,
    en_NV_Item_W_TX_LOW_GAIN_APT_COMP_B19,
    en_NV_Item_W_TX_PA_GAIN_VOICE_MODE_B19,
    en_NV_Item_W_TX_PA_APT_TABLE_HIGH_GAIN_B19,
    en_NV_Item_W_TX_PA_APT_TABLE_MID_GAIN_B19,
    en_NV_Item_W_TX_PA_APT_TABLE_LOW_GAIN_B19,
#if (RAT_MODE != RAT_GU)
    EN_NV_ID_LTE_TCXO_INIT_FREQ                    /*0xe900*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B20        /*0xeb0d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B20        /*0xeb0e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B20      /*0xeb0f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B20      /*0xeb10*/,
    EN_NV_ID_LTE_IP2_CAL_B20                       /*0xeb11*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B20      /*0xeb12*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B20      /*0xeb13*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B20      /*0xeb14*/,
    EN_NV_ID_LTE_PA_POWER_B20                      /*0xeb15*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B20       /*0xeb16*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B20        /*0xeb17*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B20        /*0xeb18*/,
        /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B20,                    
    EN_NV_ID_RF_DCOC_CAL_ANT1_B20,                  
    EN_NV_ID_RF_DCOC_CAL_ANT2_B20 ,                 
    EN_NV_ID_TX_APC_GAIN_B20,                       
    EN_NV_ID_RF_TXIQ_CAL_B20,                       
    EN_NV_ID_PA_POWER_DIFFERENCE_B20,            
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B20,          
   EN_NV_ID_LTE_TX_PD_AUTO_CAL_B20,		
   EN_NV_ID_LTE_TX_PD_PWR_TABLE_B20, 		
   EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B20,		
   EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B20, 	
   EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B20,	
   EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B20,	
   EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B20,
   EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B20,

    
    /*band40*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B40         /*0xeb4D*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B40         /*0xeb4E*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B40       /*0xeb4F*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B40       /*0xeb50*/,
    EN_NV_ID_LTE_IP2_CAL_B40                        /*0xeb51*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B40      /*0xeb52*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B40       /*0xeb53*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B40       /*0xeb54*/,
    EN_NV_ID_LTE_PA_POWER_B40                       /*0xeb55*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B40        /*0xeb56*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B40         /*0xeb57*/,
    /*Begin DTS2013121609574 add by h00221013 20131216*/
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B40,
    /*Begin DTS2013121609574 add by h00221013 20131216*/

        /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B40                     /*0xeb59*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B40                   /*0xeb5a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B40                   /*0xeb5b*/,
    EN_NV_ID_TX_APC_GAIN_B40                        /*0xeb5c*/,
    EN_NV_ID_RF_TXIQ_CAL_B40                        /*0xeb5d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B40                /*0xeb5e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B40               /*0xeb5f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B40		    /* 0xeb60*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B40 		    /* 0xeb61*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B40		    /* 0xeb62*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B40 	    /* 0xeb63*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B40	    /* 0xeb64*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B40	    /* 0xeb66*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B40   /* 0xeb67*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B40   /* 0xeb68*/,
 


    
    /*bdan38*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B38         ,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B38         ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B38       ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B38       ,
    EN_NV_ID_LTE_IP2_CAL_B38                        ,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B38      ,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B38       ,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B38       ,
    EN_NV_ID_LTE_PA_POWER_B38                       ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B38        ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B38         ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B38         ,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B38                    ,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B38                  ,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B38                  ,
    EN_NV_ID_TX_APC_GAIN_B38                       ,
    EN_NV_ID_RF_TXIQ_CAL_B38                       ,
    EN_NV_ID_PA_POWER_DIFFERENCE_B38               ,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B38              ,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B38                ,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B38               ,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B38              ,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B38           ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B38         ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B38         ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B38       ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B38       ,
    
    /*band41*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B41         ,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B41         ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B41       ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B41       ,
    EN_NV_ID_LTE_IP2_CAL_B41                        ,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B41      ,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B41       ,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B41       ,
    EN_NV_ID_LTE_PA_POWER_B41                       ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B41        ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B41         ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B41         ,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B41                    ,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B41                  ,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B41                  ,
    EN_NV_ID_TX_APC_GAIN_B41                       ,
    EN_NV_ID_RF_TXIQ_CAL_B41                       ,
    EN_NV_ID_PA_POWER_DIFFERENCE_B41               ,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B41              ,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B41                ,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B41               ,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B41              ,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B41           ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B41    ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B41    ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B41  ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B41  ,
                                                                
    /*band7*/         
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B7          ,           
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B7          ,           
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B7        ,           
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B7        ,           
    EN_NV_ID_LTE_IP2_CAL_B7                         ,           
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B7       ,           
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B7        ,           
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B7        ,           
    EN_NV_ID_LTE_PA_POWER_B7                        ,           
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B7         ,           
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B7          ,           
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B7          ,           
    /*add for V9R1_6361 Begin*/                                 
    EN_NV_ID_IIP2_CAL_TABLE_B7                    ,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B7                  ,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B7                  ,
    EN_NV_ID_TX_APC_GAIN_B7                       ,
    EN_NV_ID_RF_TXIQ_CAL_B7                       ,
    EN_NV_ID_PA_POWER_DIFFERENCE_B7               ,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B7              ,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B7                ,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B7               ,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B7              ,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B7           ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B7    ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B7    ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B7  ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B7  ,
    
    /*band3*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B3          ,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B3          ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B3        ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B3        ,
    EN_NV_ID_LTE_IP2_CAL_B3                         ,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B3       ,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B3        ,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B3        ,
    EN_NV_ID_LTE_PA_POWER_B3                        ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B3         ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B3          ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B3          ,
     /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B3                    ,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B3                  ,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B3                  ,
    EN_NV_ID_TX_APC_GAIN_B3                       ,
    EN_NV_ID_RF_TXIQ_CAL_B3                       ,
    EN_NV_ID_PA_POWER_DIFFERENCE_B3               ,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B3              ,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B3                ,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B3               ,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B3              ,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B3           ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B3    ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B3    ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B3  ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B3  ,
    
    
    /*band1*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B1          ,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B1          ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B1        ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B1        ,
    EN_NV_ID_LTE_IP2_CAL_B1                         ,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B1       ,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B1        ,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B1        ,
    EN_NV_ID_LTE_PA_POWER_B1                        ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B1         ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B1          ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B1          ,
     /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B1                    ,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B1                  ,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B1                  ,
    EN_NV_ID_TX_APC_GAIN_B1                       ,
    EN_NV_ID_RF_TXIQ_CAL_B1                       ,
    EN_NV_ID_PA_POWER_DIFFERENCE_B1               ,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B1              ,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B1                ,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B1               ,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B1              ,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B1           ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B1    ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B1    ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B1  ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B1  ,
    
    
    /*band5*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B5          /*0xed8D*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B5          /*0xed8E*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B5        /*0xed8F*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B5        /*0xed90*/,
    EN_NV_ID_LTE_IP2_CAL_B5                         /*0xed91*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B5       /*0xed92*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B5        /*0xed93*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B5        /*0xed94*/,
    EN_NV_ID_LTE_PA_POWER_B5                        /*0xed95*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B5         /*0xed96*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B5          /*0xed97*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B5          /*0xed98*/,
    
         /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B5                    	/* 0xed99*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B5                 	/* 0xed9a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B5                 	/* 0xed9b*/,
    EN_NV_ID_TX_APC_GAIN_B5                      	/* 0xed9c*/,
    EN_NV_ID_RF_TXIQ_CAL_B5                       	/* 0xed9d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B5              	/* 0xed9e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B5              	/* 0xed9f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B5                	/* 0xedA5*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B5               	/* 0xedA6*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B5             	/* 0xedA7*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B5          	/* 0xedA8*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B5	  	/* 0xedA9*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B5	  	/* 0xedAa*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B5  	/* 0xedAb*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B5  	/* 0xedAc*/,
  
    
    /*band8*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B8          /*0xedcD*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B8          /*0xedcE*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B8        /*0xedcF*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B8        /*0xedd0*/,
    EN_NV_ID_LTE_IP2_CAL_B8                         /*0xedd1*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B8       /*0xedd2*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B8        /*0xedd3*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B8        /*0xedd4*/,
    EN_NV_ID_LTE_PA_POWER_B8                        /*0xedd5*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B8         /*0xedd6*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B8          /*0xedd7*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B8          /*0xedd8*/,
    
         /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B8                    /*0xedd9*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B8                  /*0xedda*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B8                  /*0xeddb*/,
    EN_NV_ID_TX_APC_GAIN_B8                       /*0xeddc*/,
    EN_NV_ID_RF_TXIQ_CAL_B8                       /*0xeddd*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B8               /*0xedde*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B8              /*0xeddf*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B8                /*0xede5*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B8               /*0xede6*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B8              /*0xede7*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B8           /*0xede8*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B8    /*0xede9*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B8    /*0xedea*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B8  /*0xedeb*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B8  /*0xedec*/,

    
    /*band19*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B19         ,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B19         ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B19       ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B19       ,
    EN_NV_ID_LTE_IP2_CAL_B19                        ,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B19      ,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B19       ,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B19       ,
    EN_NV_ID_LTE_PA_POWER_B19                       ,

    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B19        ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B19         ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B19         ,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B19                     ,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B19                   ,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B19                   ,
    EN_NV_ID_TX_APC_GAIN_B19                        ,
    EN_NV_ID_RF_TXIQ_CAL_B19                        ,
    EN_NV_ID_PA_POWER_DIFFERENCE_B19                ,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B19               ,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B19                  ,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B19                 ,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B19                ,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B19             ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B19      ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B19      ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B19    ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B19    ,
    
    /*band21*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B21         ,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B21         ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B21       ,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B21       ,
    EN_NV_ID_LTE_IP2_CAL_B21                        ,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B21      ,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B21       ,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B21       ,
    EN_NV_ID_LTE_PA_POWER_B21                       ,

    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B21        ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B21         ,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B21         ,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B21                     ,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B21                   ,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B21                   ,
    EN_NV_ID_TX_APC_GAIN_B21                        ,
    EN_NV_ID_RF_TXIQ_CAL_B21                        ,
    EN_NV_ID_PA_POWER_DIFFERENCE_B21                ,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B21               ,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B21                  ,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B21                 ,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B21                ,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B21             ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B21      ,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B21      ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B21    ,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B21    ,
    
    
    /*band2*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B2          /*0xEE8d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B2          /*0xEE8e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B2        /*0xEE8f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B2        /*0xEE90*/,
    EN_NV_ID_LTE_IP2_CAL_B2                         /*0xEE91*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B2       /*0xEE92*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B2        /*0xEE93*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B2        /*0xEE94*/,
    EN_NV_ID_LTE_PA_POWER_B2                        /*0xEE95*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B2         /*0xEE96*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B2          /*0xEE97*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B2          /*0xEE98*/,
    
        /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B2                     /*0xEE99*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B2                   /*0xEE9a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B2                   /*0xEE9b*/,
    EN_NV_ID_TX_APC_GAIN_B2                        /*0xEE9c*/,
    EN_NV_ID_RF_TXIQ_CAL_B2                        /*0xEE9d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B2                /*0xEE9e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B2               /*0xEE9f*/,	
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B2                 /*0xEEa0*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B2                /*0xEEa1*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B2               /*0xEEa2*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B2            /*0xEEa3*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B2	   /*0xEEa4*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B2	   /*0xEEa5*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B2   /*0xEEa6*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B2   /*0xEEa7*/,
    

    
    /*band4*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B4          /*0xEEcd*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B4          /*0xEEce*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B4        /*0xEEcf*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B4        /*0xEEd0*/,
    EN_NV_ID_LTE_IP2_CAL_B4                         /*0xEEd1*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B4       /*0xEEd2*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B4        /*0xEEd3*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B4        /*0xEEd4*/,
    EN_NV_ID_LTE_PA_POWER_B4                        /*0xEEd5*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B4         /*0xEEd6*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B4          /*0xEEd7*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B4          /*0xEEd8*/,
    
     /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B4                      /*0xEEd9*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B4                    /*0xEEda*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B4                    /*0xEEdb*/,
    EN_NV_ID_TX_APC_GAIN_B4                         /*0xEEdc*/,
    EN_NV_ID_RF_TXIQ_CAL_B4                         /*0xEEdd*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B4                 /*0xEEde*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B4                /*0xEEdf*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B4                  /*0xEEe0*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B4                 /*0xEEe1*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B4                /*0xEEe2*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B4             /*0xEEe3*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B4	    /*0xEEe4*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B4	    /*0xEEe5*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B4        /*0xEEe6*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B4        /*0xEEe7*/,
    
    
    /*band6*/
    
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B6         /*0xEf0d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B6          /*0xEf0e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B6        /*0xEf0f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B6       /*0xEf10*/,
    EN_NV_ID_LTE_IP2_CAL_B6                         /*0xEf11*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B6       /*0xEf12*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B6        /*0xEf13*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B6        /*0xEf14*/,
    EN_NV_ID_LTE_PA_POWER_B6                        /*0xEf15*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B6         /*0xEf16*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B6         /*0xEf17*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B6          /*0xEf18*/,
    
     /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B6                     /*0xEf19*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B6                   /*0xEf1a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B6                   /*0xEf1b*/,
    EN_NV_ID_TX_APC_GAIN_B6                        /*0xEf1c*/,
    EN_NV_ID_RF_TXIQ_CAL_B6                        /*0xEf1d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B6                /*0xEf1e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B6               /*0xEf1f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B6                 /*0xEf20*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B6                /*0xEf21*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B6               /*0xEf22*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B6            /*0xEf23*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B6	   /*0xEf24*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B6	   /*0xEf25*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B6   /*0xEf26*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B6   /*0xEf27*/,
    
    
    /*band9*/
    
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B9          /*0xEf4d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B9         /*0xEf4e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B9        /*0xEf4f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B9        /*0xEf50*/,
    EN_NV_ID_LTE_IP2_CAL_B9                        /*0xEf51*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B9       /*0xEf52*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B9        /*0xEf53*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B9       /*0xEf54*/,
    EN_NV_ID_LTE_PA_POWER_B9                        /*0xEf55*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B9         /*0xEf56*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B9          /*0xEf57*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B9          /*0xEf58*/,
    
     /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B9                     /* 0xEf59*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B9                   /* 0xEf5a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B9                   /* 0xEf5b*/,
    EN_NV_ID_TX_APC_GAIN_B9                        /* 0xEf5c*/,
    EN_NV_ID_RF_TXIQ_CAL_B9                        /* 0xEf5d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B9                /* 0xEf5e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B9               /* 0xEf5f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B9                 /* 0xEf60*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B9                /* 0xEf61*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B9               /* 0xEf62*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B9            /* 0xEf63*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B9	   /* 0xEf64*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B9	   /* 0xEf65*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B9   /* 0xEf66*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B9   /* 0xEf67*/,
    
    /*band10*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B10         /*0xEf8d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B10         /*0xEf8e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B10       /*0xEf8f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B10       /*0xEf90*/,
    EN_NV_ID_LTE_IP2_CAL_B10                        /*0xEf91*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B10      /*0xEf92*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B10       /*0xEf93*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B10       /*0xEf94*/,
    EN_NV_ID_LTE_PA_POWER_B10                       /*0xEf95*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B10        /*0xEf96*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B10         /*0xEf97*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B10         /*0xEf98*/,
    
     /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B10                    /* 0xEf99*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B10                  /* 0xEf9a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B10                  /* 0xEf9b*/,
    EN_NV_ID_TX_APC_GAIN_B10                       /* 0xEf9c*/,
    EN_NV_ID_RF_TXIQ_CAL_B10                       /* 0xEf9d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B10               /* 0xEf9e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B10              /* 0xEf9f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B10                /* 0xEfa0*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B10               /* 0xEfa1*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B10              /* 0xEfa2*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B10           /* 0xEfa3*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B10	   /* 0xEfa4*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B10	   /* 0xEfa5*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B10  /* 0xEfa6*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B10  /* 0xEfa7*/,

    
    /*band11*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B11         /*0xEfcd*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B11         /*0xEfce*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B11       /*0xEfcf*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B11       /*0xEfd0*/,
    EN_NV_ID_LTE_IP2_CAL_B11                        /*0xEfd1*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B11      /*0xEfd2*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B11       /*0xEfd3*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B11       /*0xEfd4*/,
    EN_NV_ID_LTE_PA_POWER_B11                       /*0xEfd5*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B11        /*0xEfd6*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B11         /*0xEfd7*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B11        /*0xEfd8*/,
    
      /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B11                    /*0xEfd9*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B11                  /*0xEfda*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B11                  /*0xEfdb*/,
    EN_NV_ID_TX_APC_GAIN_B11                       /*0xEfdc*/,
    EN_NV_ID_RF_TXIQ_CAL_B11                       /*0xEfdd*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B11               /*0xEfde*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B11              /*0xEfdf*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B11                /*0xEfe0*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B11               /*0xEfe1*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B11              /*0xEfe2*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B11           /*0xEfe3*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B11	   /*0xEfe4*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B11	   /*0xEfe5*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B11  /*0xEfe6*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B11  /*0xEfe7*/,
    
    /*band12*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B12        /*0xf00d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B12         /*0xf00e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B12       /*0xf00f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B12      /*0xf010*/,
    EN_NV_ID_LTE_IP2_CAL_B12                       /*0xf011*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B12      /*0xf012*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B12      /*0xf013*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B12      /*0xf014*/,
    EN_NV_ID_LTE_PA_POWER_B12                       /*0xf015*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B12        /*0xf016*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B12        /*0xf017*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B12        /*0xf018*/,
    
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B12                    /* 0xf019*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B12                  /* 0xf01a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B12                  /* 0xf01b*/,
    EN_NV_ID_TX_APC_GAIN_B12                       /* 0xf01c*/,
    EN_NV_ID_RF_TXIQ_CAL_B12                       /* 0xf01d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B12               /* 0xf01e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B12              /* 0xf01f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B12                /* 0xf020*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B12               /* 0xf021*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B12              /* 0xf022*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B12           /* 0xf023*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B12	   /* 0xf024*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B12	   /* 0xf025*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B12  /* 0xf026*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B12  /* 0xf027*/,
    
    /*band13*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B13         /*0xf04d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B13        /*0xf04e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B13      /*0xf04f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B13       /*0xf050*/,
    EN_NV_ID_LTE_IP2_CAL_B13                        /*0xf051*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B13     /*0xf052*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B13      /*0xf053*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B13      /*0xf054*/,
    EN_NV_ID_LTE_PA_POWER_B13                       /*0xf055*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B13       /*0xf056*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B13         /*0xf057*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B13        /*0xf058*/,
    
     /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B13                    /* 0xf059*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B13                  /* 0xf05a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B13                  /* 0xf05b*/,
    EN_NV_ID_TX_APC_GAIN_B13                       /* 0xf05c*/,
    EN_NV_ID_RF_TXIQ_CAL_B13                       /* 0xf05d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B13               /* 0xf05e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B13              /* 0xf05f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B13 		   /* 0xf060*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B13		   /* 0xf061*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B13		   /* 0xf062*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B13	   /* 0xf063*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B13    /* 0xf064*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B13    /* 0xf065*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B13  /* 0xf066*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B13  /* 0xf067*/,
    
    /*band14*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B14        /*0xf08d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B14        /*0xf08e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B14      /*0xf08f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B14      /*0xf090*/,
    EN_NV_ID_LTE_IP2_CAL_B14                       /*0xf091*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B14      /*0xf092*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B14       /*0xf093*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B14       /*0xf094*/,
    EN_NV_ID_LTE_PA_POWER_B14                      /*0xf095*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B14        /*0xf096*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B14         /*0xf097*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B14        /*0xf098*/,
    
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B14                    /* 0xf099*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B14                  /* 0xf09a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B14                  /* 0xf09b*/,
    EN_NV_ID_TX_APC_GAIN_B14                       /* 0xf09c*/,
    EN_NV_ID_RF_TXIQ_CAL_B14                       /* 0xf09d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B14               /* 0xf09e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B14              /* 0xf09f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B14 		   /* 0xf0a0*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B14		   /* 0xf0a1*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B14		   /* 0xf0a2*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B14	   /* 0xf0a3*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B14    /* 0xf0a4*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B14    /* 0xf0a5*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B14  /* 0xf0a6*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B14  /* 0xf0a7*/,
    
    
    /*band17*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B17         /*0xf0cd*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B17         /*0xf0ce*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B17       /*0xf0cf*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B17       /*0xf0d0*/,
    EN_NV_ID_LTE_IP2_CAL_B17                        /*0xf0d1*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B17      /*0xf0d2*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B17       /*0xf0d3*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B17       /*0xf0d4*/,
    EN_NV_ID_LTE_PA_POWER_B17                       /*0xf0d5*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B17        /*0xf0d6*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B17         /*0xf0d7*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B17         /*0xf0d8*/,
   
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B17                    /* 0xf0d9*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B17                  /* 0xf0da*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B17                  /* 0xf0db*/,
    EN_NV_ID_TX_APC_GAIN_B17                       /* 0xf0dc*/,
    EN_NV_ID_RF_TXIQ_CAL_B17                       /* 0xf0dd*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B17               /* 0xf0de*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B17              /* 0xf0df*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B17 		   /* 0xf0e0*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B17		   /* 0xf0e1*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B17		   /* 0xf0e2*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B17	   /* 0xf0e3*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B17    /* 0xf0e4*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B17    /* 0xf0e5*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B17  /* 0xf0e6*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B17  /* 0xf0e7*/, 
   
   /*band18*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B18         /* 0xf10d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B18         /* 0xf10e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B18       /* 0xf10f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B18       /* 0xf110*/,
    EN_NV_ID_LTE_IP2_CAL_B18                        /* 0xf111*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B18      /* 0xf112*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B18       /* 0xf113*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B18       /* 0xf114*/,
    EN_NV_ID_LTE_PA_POWER_B18                       /* 0xf115*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B18        /* 0xf116*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B18         /* 0xf117*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B18         /* 0xf118*/,
    /*add for V9R1_6361 Begin*/                       
    EN_NV_ID_IIP2_CAL_TABLE_B18                     /* 0xf119*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B18                   /* 0xf11a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B18                   /* 0xf11b*/,
    EN_NV_ID_TX_APC_GAIN_B18                        /* 0xf11c*/,
    EN_NV_ID_RF_TXIQ_CAL_B18                        /* 0xf11d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B18                /* 0xf11e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B18               /* 0xf11f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B18 		    /* 0xf120*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B18		    /* 0xf121*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B18		    /* 0xf122*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B18	    /* 0xf123*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B18     /* 0xf124*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B18     /* 0xf125*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B18   /* 0xf126*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B18   /* 0xf127*/,
   
    /*band22*/
    
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B22         /* 0xf14d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B22         /* 0xf14e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B22       /* 0xf14f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B22       /* 0xf150*/,
    EN_NV_ID_LTE_IP2_CAL_B22                        /* 0xf151*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B22      /* 0xf152*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B22       /* 0xf153*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B22       /* 0xf154*/,
    EN_NV_ID_LTE_PA_POWER_B22                       /* 0xf155*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B22        /* 0xf156*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B22         /* 0xf157*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B22         /* 0xf158*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B22                    /* 0xf159*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B22                  /* 0xf15a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B22                  /* 0xf15b*/,
    EN_NV_ID_TX_APC_GAIN_B22                       /* 0xf15c*/,
    EN_NV_ID_RF_TXIQ_CAL_B22                       /* 0xf15d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B22               /* 0xf15e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B22              /* 0xf15f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B22 		   /* 0xf160*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B22		   /* 0xf161*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B22		   /* 0xf162*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B22	   /* 0xf163*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B22    /* 0xf164*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B22    /* 0xf165*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B22  /* 0xf166*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B22  /* 0xf167*/,

/*band23*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B23         /* 0xf18d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B23         /* 0xf18e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B23       /* 0xf18f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B23       /* 0xf190*/,
    EN_NV_ID_LTE_IP2_CAL_B23                        /* 0xf191*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B23      /* 0xf192*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B23       /* 0xf193*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B23       /* 0xf194*/,
    EN_NV_ID_LTE_PA_POWER_B23                       /* 0xf195*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B23        /* 0xf196*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B23         /* 0xf197*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B23         /* 0xf198*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B23                     /* 0xf199*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B23                   /* 0xf19a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B23                   /* 0xf19b*/,
    EN_NV_ID_TX_APC_GAIN_B23                        /* 0xf19c*/,
    EN_NV_ID_RF_TXIQ_CAL_B23                        /* 0xf19d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B23                /* 0xf19e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B23               /* 0xf19f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B23 		    /* 0xf1a0*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B23		    /* 0xf1a1*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B23		    /* 0xf1a2*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B23	    /* 0xf1a3*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B23     /* 0xf1a4*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B23     /* 0xf1a5*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B23   /* 0xf1a6*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B23   /* 0xf1a7*/,
    


	

    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B24         /* 0xf1cd*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B24         /* 0xf1ce*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B24       /* 0xf1cf*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B24       /* 0xf1d0*/,
    EN_NV_ID_LTE_IP2_CAL_B24                        /* 0xf1d1*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B24      /* 0xf1d2*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B24       /* 0xf1d3*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B24       /* 0xf1d4*/,
    EN_NV_ID_LTE_PA_POWER_B24                       /* 0xf1d5*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B24        /* 0xf1d6*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B24         /* 0xf1d7*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B24         /* 0xf1d8*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B24                    /* 0xf1d9*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B24                  /* 0xf1da*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B24                  /* 0xf1db*/,
    EN_NV_ID_TX_APC_GAIN_B24                       /* 0xf1dc*/,
    EN_NV_ID_RF_TXIQ_CAL_B24                       /* 0xf1dd*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B24               /* 0xf1de*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B24              /* 0xf1df*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B24 		   /* 0xf1e0*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B24		   /* 0xf1e1*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B24		   /* 0xf1e2*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B24	   /* 0xf1e3*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B24    /* 0xf1e4*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B24    /* 0xf1e5*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B24  /* 0xf1e6*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B24  /* 0xf1e7*/,



	

    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B25         /* 0xf20d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B25         /* 0xf20e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B25       /* 0xf20f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B25       /* 0xf210*/,
    EN_NV_ID_LTE_IP2_CAL_B25                        /* 0xf211*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B25      /* 0xf212*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B25       /* 0xf213*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B25       /* 0xf214*/,
    EN_NV_ID_LTE_PA_POWER_B25                       /* 0xf215*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B25        /* 0xf216*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B25         /* 0xf217*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B25         /* 0xf218*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B25                    /* 0xf219*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B25                  /* 0xf21a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B25                  /* 0xf21b*/,
    EN_NV_ID_TX_APC_GAIN_B25                       /* 0xf21c*/,
    EN_NV_ID_RF_TXIQ_CAL_B25                       /* 0xf21d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B25               /* 0xf21e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B25              /* 0xf21f*/,
 	EN_NV_ID_LTE_TX_PD_AUTO_CAL_B25 	   /* 0xf220*/,
	EN_NV_ID_LTE_TX_PD_PWR_TABLE_B25	   /* 0xf221*/,
	EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B25	   /* 0xf222*/,
	EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B25	      /* 0xf223*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B25   /* 0xf224*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B25   /* 0xf225*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B25 /* 0xf226*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B25 /* 0xf227*/,



	

    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B33         /* 0xf24d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B33         /* 0xf24e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B33       /* 0xf24f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B33       /* 0xf250*/,
    EN_NV_ID_LTE_IP2_CAL_B33                        /* 0xf251*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B33      /* 0xf252*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B33       /* 0xf253*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B33       /* 0xf254*/,
    EN_NV_ID_LTE_PA_POWER_B33                       /* 0xf255*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B33        /* 0xf256*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B33         /* 0xf257*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B33         /* 0xf258*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B33                    /* 0xf259*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B33                  /* 0xf25a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B33                  /* 0xf25b*/,
    EN_NV_ID_TX_APC_GAIN_B33                       /* 0xf25c*/,
    EN_NV_ID_RF_TXIQ_CAL_B33                       /* 0xf25d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B33               /* 0xf25e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B33              /* 0xf25f*/,
 	EN_NV_ID_LTE_TX_PD_AUTO_CAL_B33 	   /* 0xf260*/,                
	EN_NV_ID_LTE_TX_PD_PWR_TABLE_B33			   /* 0xf261*/,
	EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B33			   /* 0xf262*/,
	EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B33		   /* 0xf263*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B33    /* 0xf264*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B33    /* 0xf265*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B33  /* 0xf266*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B33  /* 0xf267*/,



	

    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B34         /* 0xf28d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B34         /* 0xf28e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B34       /* 0xf28f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B34       /* 0xf290*/,
    EN_NV_ID_LTE_IP2_CAL_B34                        /* 0xf291*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B34      /* 0xf292*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B34       /* 0xf293*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B34       /* 0xf294*/,
    EN_NV_ID_LTE_PA_POWER_B34                       /* 0xf295*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B34        /* 0xf296*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B34         /* 0xf297*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B34         /* 0xf298*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B34                    /* 0xf299*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B34                  /* 0xf29a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B34                  /* 0xf29b*/,
    EN_NV_ID_TX_APC_GAIN_B34                       /* 0xf29c*/,
    EN_NV_ID_RF_TXIQ_CAL_B34                       /* 0xf29d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B34               /* 0xf29e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B34              /* 0xf29f*/,
  	EN_NV_ID_LTE_TX_PD_AUTO_CAL_B34 			   /* 0xf2a0*/,
	EN_NV_ID_LTE_TX_PD_PWR_TABLE_B34			   /* 0xf2a1*/,
	EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B34			   /* 0xf2a2*/,
	EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B34		   /*0xf2a3*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B34   /*0xf2a4*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B34   /*0xf2a5*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B34 /* 0xf2a6*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B34 /* 0xf2a7*/,



	

    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B35         /* 0xf2cd*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B35         /* 0xf2ce*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B35       /* 0xf2cf*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B35       /* 0xf2d0*/,
    EN_NV_ID_LTE_IP2_CAL_B35                        /* 0xf2d1*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B35      /* 0xf2d2*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B35       /* 0xf2d3*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B35       /* 0xf2d4*/,
    EN_NV_ID_LTE_PA_POWER_B35                       /* 0xf2d5*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B35        /* 0xf2d6*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B35         /* 0xf2d7*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B35         /* 0xf2d8*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B35                    /* 0xf2d9*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B35                  /* 0xf2da*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B35                  /* 0xf2db*/,
    EN_NV_ID_TX_APC_GAIN_B35                       /* 0xf2dc*/,
    EN_NV_ID_RF_TXIQ_CAL_B35                       /* 0xf2dd*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B35               /* 0xf2de*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B35              /* 0xf2df*/,
 	EN_NV_ID_LTE_TX_PD_AUTO_CAL_B35 			   /* 0xf2e0*/,
	EN_NV_ID_LTE_TX_PD_PWR_TABLE_B35			   /* 0xf2e1*/,
	EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B35			   /* 0xf2e2*/,
	EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B35		   /* 0xf2e3*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B35    /* 0xf2e4*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B35    /* 0xf2e5*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B35  /* 0xf2e6*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B35  /* 0xf2e7*/,



	

    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B36         /* 0xf30d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B36         /* 0xf30e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B36       /* 0xf30f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B36       /* 0xf310*/,
    EN_NV_ID_LTE_IP2_CAL_B36                        /* 0xf311*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B36      /* 0xf312*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B36       /* 0xf313*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B36       /* 0xf314*/,
    EN_NV_ID_LTE_PA_POWER_B36                       /* 0xf315*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B36        /* 0xf316*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B36         /* 0xf317*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B36         /* 0xf318*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B36                    /* 0xf319*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B36                  /* 0xf31a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B36                  /* 0xf31b*/,
    EN_NV_ID_TX_APC_GAIN_B36                       /* 0xf31c*/,
    EN_NV_ID_RF_TXIQ_CAL_B36                       /* 0xf31d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B36               /* 0xf31e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B36              /* 0xf31f*/,
	EN_NV_ID_LTE_TX_PD_AUTO_CAL_B36 			   /* 0xf320*/,
	EN_NV_ID_LTE_TX_PD_PWR_TABLE_B36			   /* 0xf321*/,
	EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B36			   /* 0xf322*/,
	EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B36		   /* 0xf323*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B36   /*0xf324*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B36   /*0xf325*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B36 /* 0xf326*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B36 /* 0xf327*/,



	

    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B37         /* 0xf34d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B37         /* 0xf34e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B37       /* 0xf34f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B37       /* 0xf350*/,
    EN_NV_ID_LTE_IP2_CAL_B37                        /* 0xf351*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B37      /* 0xf352*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B37       /* 0xf353*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B37       /* 0xf354*/,
    EN_NV_ID_LTE_PA_POWER_B37                       /* 0xf355*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B37        /* 0xf356*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B37         /* 0xf357*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B37         /* 0xf358*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B37                    /* 0xf359*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B37                  /* 0xf35a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B37                  /* 0xf35b*/,
    EN_NV_ID_TX_APC_GAIN_B37                       /* 0xf35c*/,
    EN_NV_ID_RF_TXIQ_CAL_B37                       /* 0xf35d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B37               /* 0xf35e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B37              /* 0xf35f*/,
 	EN_NV_ID_LTE_TX_PD_AUTO_CAL_B37 			   /* 0xf360*/,
	EN_NV_ID_LTE_TX_PD_PWR_TABLE_B37			   /* 0xf361*/,
	EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B37			   /* 0xf362*/,
	EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B37		   /*0xf363*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B37   /*0xf364*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B37   /*0xf365*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B37 /* 0xf366*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B37 /* 0xf367*/,



	


    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B42         /* 0xf38d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B42         /* 0xf38e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B42       /* 0xf38f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B42       /* 0xf390*/,
    EN_NV_ID_LTE_IP2_CAL_B42                        /* 0xf391*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B42      /* 0xf392*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B42       /* 0xf393*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B42       /* 0xf394*/,
    EN_NV_ID_LTE_PA_POWER_B42                       /* 0xf395*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B42        /* 0xf396*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B42         /* 0xf397*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B42         /* 0xf398*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B42                    /* 0xf399*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B42                  /* 0xf39a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B42                  /* 0xf39b*/,
    EN_NV_ID_TX_APC_GAIN_B42                       /* 0xf39c*/,
    EN_NV_ID_RF_TXIQ_CAL_B42                       /* 0xf39d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B42               /* 0xf39e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B42              /* 0xf39f*/,
	EN_NV_ID_LTE_TX_PD_AUTO_CAL_B42 			   /* 0xf3a0*/,
	EN_NV_ID_LTE_TX_PD_PWR_TABLE_B42			   /* 0xf3a1*/,
	EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B42			   /* 0xf3a2*/,
	EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B42		   /* 0xf3a3*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B42   /*0xf3a4*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B42   /*0xf3a5*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B42 /* 0xf3a6*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B42 /* 0xf3a7*/,



	

    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B43         /* 0xf3cd*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B43         /* 0xf3ce*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B43       /* 0xf3cf*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B43       /* 0xf3d0*/,
    EN_NV_ID_LTE_IP2_CAL_B43                        /* 0xf3d1*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B43      /* 0xf3d2*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B43       /* 0xf3d3*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B43       /* 0xf3d4*/,
    EN_NV_ID_LTE_PA_POWER_B43                       /* 0xf3d5*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B43        /* 0xf3d6*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B43         /* 0xf3d7*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B43         /* 0xf3d8*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B43                    /* 0xf3d9*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B43                  /* 0xf3da*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B43                  /* 0xf3db*/,
    EN_NV_ID_TX_APC_GAIN_B43                       /* 0xf3dc*/,
    EN_NV_ID_RF_TXIQ_CAL_B43                       /* 0xf3dd*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B43               /* 0xf3de*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B43              /* 0xf3df*/,
	EN_NV_ID_LTE_TX_PD_AUTO_CAL_B43 			   /* 0xf3e0*/,
	EN_NV_ID_LTE_TX_PD_PWR_TABLE_B43			   /* 0xf3e1*/,
	EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B43			   /* 0xf3e2*/,
	EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B43		   /* 0xf3e3*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B43   /*0xf3e4*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B43   /*0xf3e5*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B43 /* 0xf3e6*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B43 /* 0xf3e7*/,








    
    /*band39*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B39         /*0xf40d*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B39        /*0xf40e*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B39       /*0xf40f*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B39      /*0xf410*/,
    EN_NV_ID_LTE_IP2_CAL_B39                        /*0xf411*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B39      /*0xf412*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B39       /*0xf413*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B39      /*0xf414*/,
    EN_NV_ID_LTE_PA_POWER_B39                       /*0xf415*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B39        /*0xf416*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B39         /*0xf417*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B39         /*0xf418*/,
    
     /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B39                    /* 0xf419*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B39                  /* 0xf41a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B39                  /* 0xf41b*/,
    EN_NV_ID_TX_APC_GAIN_B39                       /* 0xf41c*/,
    EN_NV_ID_RF_TXIQ_CAL_B39                       /* 0xf41d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B39               /* 0xf41e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B39              /* 0xf41f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B39                /* 0xef420*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B39               /* 0xef421*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B39              /* 0xef422*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B39           /* 0xef423*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B39	  /* 0xef424*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B39	  /* 0xef425*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B39  /* 0xef426*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B39  /* 0xef427*/,
    
    
    
    
/*BAND28 ����NV*/
	EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B28			/* 0xf44D*/,
	EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B28			/* 0xf44E*/,
	EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B28		/* 0xf44F*/,
	EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B28		/* 0xf450*/,
	EN_NV_ID_LTE_IP2_CAL_B28 				/* 0xf451*/,
	EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B28		/* 0xf452*/,
	EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B28		/* 0xf453*/,
	EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B28		/* 0xf454*/,
	EN_NV_ID_LTE_PA_POWER_B28				/* 0xf455*/,
	EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B28 		/* 0xf456*/,
	EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B28			/* 0xf457*/,
	EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B28			/* 0xf458*/,
	/*add for V9R1_6361 Begin*/
	EN_NV_ID_IIP2_CAL_TABLE_B28				  /* 0xf459*/,
	EN_NV_ID_RF_DCOC_CAL_ANT1_B28				  /* 0xf45a*/,
	EN_NV_ID_RF_DCOC_CAL_ANT2_B28				  /* 0xf45b*/,
	EN_NV_ID_TX_APC_GAIN_B28 				  /* 0xf45c*/,
	EN_NV_ID_RF_TXIQ_CAL_B28 				  /* 0xf45d*/,
	EN_NV_ID_PA_POWER_DIFFERENCE_B28 			  /* 0xf45e*/,
	EN_NV_ID_TX_RF_FREQ_COMP_STRU_B28			  /* 0xf45f*/,
	EN_NV_ID_LTE_TX_PD_AUTO_CAL_B28				  /* 0xf465*/,
	EN_NV_ID_LTE_TX_PD_PWR_TABLE_B28 			  /* 0xf466*/,
	EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B28			  /* 0xf467*/,
	EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B28		  /* 0xf468*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B28	  /* 0xf469*/,
	EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B28	  /* 0xf46a*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B28  /* 0xf46b*/,
	EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B28  /* 0xf46c*/,

/*BAND128 ����NV*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B128         /* 0xf48D*/,
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B128         /* 0xf48E*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B128       /* 0xf48F*/,
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B128       /* 0xf490*/,
    EN_NV_ID_LTE_IP2_CAL_B128                /* 0xf491*/,
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B128      /* 0xf492*/,
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B128       /* 0xf493*/,
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B128       /* 0xf494*/,
    EN_NV_ID_LTE_PA_POWER_B128               /* 0xf495*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B128        /* 0xf496*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B128         /* 0xf497*/,
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B128         /* 0xf498*/,
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B128               /* 0xf499*/,
    EN_NV_ID_RF_DCOC_CAL_ANT1_B128                 /* 0xf49a*/,
    EN_NV_ID_RF_DCOC_CAL_ANT2_B128                 /* 0xf49b*/,
    EN_NV_ID_TX_APC_GAIN_B128                  /* 0xf49c*/,
    EN_NV_ID_RF_TXIQ_CAL_B128                  /* 0xf49d*/,
    EN_NV_ID_PA_POWER_DIFFERENCE_B128              /* 0xf49e*/,
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B128             /* 0xf49f*/,
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B128               /* 0xf4a5*/,
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B128              /* 0xf4a6*/,
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B128             /* 0xf4a7*/,
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B128          /* 0xf4a8*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B128   /* 0xf4a9*/,
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B128   /* 0xf4aa*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B128  /* 0xf4ab*/,
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B128  /* 0xf4ac*/,

        /*BAND26 ����NV*/
    EN_NV_ID_ANT_MODEM_LOSS_B26   ,                  /*0xf840*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT1_B26 ,        /* 0xf84d*/
    EN_NV_ID_LTE_AGC_BLK_FREQ_COMP_ANT2_B26 ,        /* 0xf84e*/
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT1_B26,       /* 0xf84f*/
    EN_NV_ID_LTE_AGC_NOBLK_FREQ_COMP_ANT2_B26 ,      /* 0xf850*/
    EN_NV_ID_LTE_IP2_CAL_B26 ,                       /* 0xf851*/
    EN_NV_ID_LTE_TX_APC_HIGHGAIN_FREQ_COMP_B26,      /* 0xf852*/
    EN_NV_ID_LTE_TX_APC_MIDGAIN_FREQ_COMP_B26 ,      /* 0xf853*/
    EN_NV_ID_LTE_TX_APC_LOWGAIN_FREQ_COMP_B26 ,      /* 0xf854*/
    EN_NV_ID_LTE_PA_POWER_B26 ,                      /* 0xf855*/
    EN_NV_ID_LTE_TX_APT_COMP_MC_HIGH_TBL_B26 ,       /*0xf856*/
    EN_NV_ID_LTE_TX_APT_COMP_MC_MID_TBL_B26 ,        /* 0xf857*/
    EN_NV_ID_LTE_TX_APT_COMP_MC_LOW_TBL_B26 ,        /* 0xf858*/
    /*add for V9R1_6361 Begin*/
    EN_NV_ID_IIP2_CAL_TABLE_B26   ,                /* 0xf859*/
    EN_NV_ID_RF_DCOC_CAL_ANT1_B26 ,                /* 0xf85a*/
    EN_NV_ID_RF_DCOC_CAL_ANT2_B26 ,                /* 0xf85b*/
    EN_NV_ID_TX_APC_GAIN_B26  ,                    /*0xf85c*/
    EN_NV_ID_RF_TXIQ_CAL_B26  ,                    /*0xf85d*/
    EN_NV_ID_PA_POWER_DIFFERENCE_B26  ,            /* 0xf85e*/
    EN_NV_ID_TX_RF_FREQ_COMP_STRU_B26 ,            /* 0xf85f*/
    EN_NV_ID_LTE_TX_PD_AUTO_CAL_B26   ,            /* 0xf865*/
    EN_NV_ID_LTE_TX_PD_PWR_TABLE_B26  ,            /* 0xf866*/
    EN_NV_ID_LTE_TX_PD_VOLT_TABLE_B26 ,            /* 0xf867*/
    EN_NV_ID_LTE_TX_PD_TEMPCMP_TABLE_B26  ,        /* 0xf868*/
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT1_B26,   /* 0xf869*/
    EN_NV_ID_LTE_AGC_SCC_BLK_FREQ_COMP_ANT2_B26 ,  /* 0xf86a*/
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT1_B26 , /* 0xf86b*/
    EN_NV_ID_LTE_AGC_SCC_NOBLK_FREQ_COMP_ANT2_B26,  /* 0xf86c*/

    EN_NV_ID_PA_POWER_0                              /*0xF8f0*/,
    EN_NV_ID_TX_APC_COMP_0                           /*0xF8f1*/,
    EN_NV_ID_TX_APC_FREQ_COMP_0                      /*0xF8f2*/,
    EN_NV_ID_RX_AGC_COMP_0                           /*0xF8f3*/,
    EN_NV_ID_RX_AGC_FREQ_COMP_0                      /*0xF8f4*/,
    EN_NV_ID_PA_POWER_1                             /*0xF8f5*/,
    EN_NV_ID_TX_APC_COMP_1                           /*0xF8f6*/,
    EN_NV_ID_TX_APC_FREQ_COMP_1                      /*0xF8f7*/,
    EN_NV_ID_RX_AGC_COMP_1                           /*0xF8f8*/,
    EN_NV_ID_RX_AGC_FREQ_COMP_1                      /*0xF8f9*/,
    EN_NV_ID_PA_POWER_2                              /*0xF8fa*/,
    EN_NV_ID_TX_APC_COMP_2                           /*0xF8fb*/,
    EN_NV_ID_TX_APC_FREQ_COMP_2                      /*0xF8fc*/,
    EN_NV_ID_RX_AGC_COMP_2                           /*0xF8fd*/,
    EN_NV_ID_RX_AGC_FREQ_COMP_2                      /*0xF8fe*/,

    /*TDS*/
    /*begin: add by l00213440 for V9R1 DSPNV*/
    /*Band34 ����nv*/
    EN_NV_ID_TDS_TX_FREQ_COMP_B34                    /*0xf8a0*/,
    EN_NV_ID_TDS_PA_POWER_DIFFERENCE_B34             /*0xf8a1*/,
    EN_NV_ID_TDS_TX_APC_GAIN_ITEM_B34                     /*0xf8a2*/,
    EN_NV_ID_TDS_AGC_FREQ_COMP_B34                     /*0xf8a3*/,
    EN_NV_ID_TDS_DCOC_CAL_B34                         /*0xf8a4*/,
    EN_NV_ID_TDS_RF_TXIQ_CAL_B34                     /*0xf8a5*/,
    EN_NV_ID_TDS_TX_APC_GAIN_B34                     /*0xf8a6*/,
    EN_NV_ID_TDS_TX_CAL_PA_GAIN_BB_B34               /*0xf8a7*/,
    EN_NV_ID_TDS_PA_MID_TX_FREQ_COMP_B34              /* 0xf8a8 */,
    EN_NV_ID_TDS_PA_LOW_TX_FREQ_COMP_B34	     /* 0xf8a9 */,
    /*Band39 ����nv*/
    EN_NV_ID_TDS_TX_FREQ_COMP_B39                     /*0xf8b0*/,
    EN_NV_ID_TDS_PA_POWER_DIFFERENCE_B39             /*0xf8b1*/,
    EN_NV_ID_TDS_TX_APC_GAIN_ITEM_B39                     /*0xf8b2*/,
    EN_NV_ID_TDS_AGC_FREQ_COMP_B39                     /*0xf8b3*/,
    EN_NV_ID_TDS_DCOC_CAL_B39                         /*0xf8b4*/,
    EN_NV_ID_TDS_RF_TXIQ_CAL_B39                     /*0xf8b5*/,
    EN_NV_ID_TDS_TX_APC_GAIN_B39                     /*0xf8b6*/,
    EN_NV_ID_TDS_TX_CAL_PA_GAIN_BB_B39               /*0xf8b7*/,
    EN_NV_ID_TDS_PA_MID_TX_FREQ_COMP_B39              /* 0xf8b8 */,
    EN_NV_ID_TDS_PA_LOW_TX_FREQ_COMP_B39	     /* 0xf8b9 */,

    /*Band40 ����nv*/
    EN_NV_ID_TDS_TX_FREQ_COMP_B40                     /*0xf8c0*/,
    EN_NV_ID_TDS_PA_POWER_DIFFERENCE_B40             /*0xf8c1*/,
    EN_NV_ID_TDS_TX_APC_GAIN_ITEM_B40                     /*0xf8c2*/,
    EN_NV_ID_TDS_AGC_FREQ_COMP_B40                     /*0xf8c3*/,
    EN_NV_ID_TDS_DCOC_CAL_B40                         /*0xf8c4*/,
    EN_NV_ID_TDS_RF_TXIQ_CAL_B40                     /*0xf8c5*/,
    EN_NV_ID_TDS_TX_APC_GAIN_B40                     /*0xf8c6*/,
    EN_NV_ID_TDS_TX_CAL_PA_GAIN_BB_B40               /*0xf8c7*/,
    EN_NV_ID_TDS_PA_MID_TX_FREQ_COMP_B40              /* 0xf8c8 */,
    EN_NV_ID_TDS_PA_LOW_TX_FREQ_COMP_B40	     /* 0xf8c9 */,

    /*Band_Reserved ����nv*/
    EN_NV_ID_TDS_TX_FREQ_COMP_BRESERVED             /*0xf8d0*/,
    EN_NV_ID_TDS_PA_POWER_DIFFERENCE_BRESERVED         /*0xf8d1*/,
    EN_NV_ID_TDS_TX_APC_GAIN_ITEM_BRESERVED                 /*0xf8d2*/,
    EN_NV_ID_TDS_AGC_FREQ_COMP_BRESERVED             /*0xf8d3*/,
    EN_NV_ID_TDS_DCOC_CAL_BRESERVED                 /*0xf8d4*/,
    EN_NV_ID_TDS_RF_TXIQ_CAL_BRESERVED                 /*0xf8d5*/,
    EN_NV_ID_TDS_TX_APC_GAIN_BRESERVED                 /*0xf8d6*/,
    EN_NV_ID_TDS_TX_CAL_PA_GAIN_BB_BRESERVED               /*0xf8d7*/,
    EN_NV_ID_TDS_PA_MID_TX_FREQ_COMP_BRESERVED              /* 0xf8d8 */,
    EN_NV_ID_TDS_PA_LOW_TX_FREQ_COMP_BRESERVED	      /* 0xf8d9 */,

    /*end: add by l00213440 for V9R1 DSPNV*/    
/* BEGIN DTS2014092901885 Y00230200 2014-10-09 Modified */    
/* ��Ҫ˵�����޸Ľ���PMD��֧��E5573s-606��E5573s-607��E5573s-320���޸ģ��������߿�*/
#ifndef BSP_CONFIG_RFNV_UNRESUME

    EN_NV_ID_ANT_MODEM_LOSS_B20                     /*0xeb00*/,
    EN_NV_ID_ANT_MODEM_LOSS_B40                     /*0xeb40*/,
    EN_NV_ID_ANT_MODEM_LOSS_B38                     ,
    EN_NV_ID_ANT_MODEM_LOSS_B41                     ,
    EN_NV_ID_ANT_MODEM_LOSS_B7                      ,           
    EN_NV_ID_ANT_MODEM_LOSS_B3                      ,
    EN_NV_ID_ANT_MODEM_LOSS_B1                      ,
    EN_NV_ID_ANT_MODEM_LOSS_B5                      /* 0xed80*/,
    EN_NV_ID_ANT_MODEM_LOSS_B8                      /*0xedc0*/,
    EN_NV_ID_ANT_MODEM_LOSS_B19                     ,
    EN_NV_ID_ANT_MODEM_LOSS_B21                     ,
    EN_NV_ID_ANT_MODEM_LOSS_B2                      /*0xEE80*/,
    EN_NV_ID_ANT_MODEM_LOSS_B4                      /* 0xEEc0*/,
    EN_NV_ID_ANT_MODEM_LOSS_B6                      /*0xEf00*/,
    EN_NV_ID_ANT_MODEM_LOSS_B9                      /*0xEf40*/,
    EN_NV_ID_ANT_MODEM_LOSS_B10                     /*0xEf80*/,
    EN_NV_ID_ANT_MODEM_LOSS_B11                     /*0xEfc0*/,
    EN_NV_ID_ANT_MODEM_LOSS_B12                     /*0xf000*/,
    EN_NV_ID_ANT_MODEM_LOSS_B13                     /*0xf040*/,
    EN_NV_ID_ANT_MODEM_LOSS_B14                     /*0xf080*/,
    EN_NV_ID_ANT_MODEM_LOSS_B17                     /*0xf0c0*/,
    EN_NV_ID_ANT_MODEM_LOSS_B18                     /* 0xf100*/,
    EN_NV_ID_ANT_MODEM_LOSS_B22                     /* 0xf140*/,
    EN_NV_ID_ANT_MODEM_LOSS_B23                     /* 0xf180*/,
    EN_NV_ID_ANT_MODEM_LOSS_B24                     /* 0xf1c0*/,
    EN_NV_ID_ANT_MODEM_LOSS_B25                     /* 0xf200*/,
    EN_NV_ID_ANT_MODEM_LOSS_B33                     /* 0xf240*/,
    EN_NV_ID_ANT_MODEM_LOSS_B34                     /* 0xf280*/,
    EN_NV_ID_ANT_MODEM_LOSS_B35                     /* 0xf2c0*/,
    EN_NV_ID_ANT_MODEM_LOSS_B36                     /* 0xf300*/,
    EN_NV_ID_ANT_MODEM_LOSS_B37                     /* 0xf340*/,
    EN_NV_ID_ANT_MODEM_LOSS_B42                     /* 0xf380*/,
    EN_NV_ID_ANT_MODEM_LOSS_B43                     /* 0xf3c0*/,
    EN_NV_ID_ANT_MODEM_LOSS_B39                     /*0xf400*/,
    EN_NV_ID_ANT_MODEM_LOSS_B28                     /* 0xf440*/,
    EN_NV_ID_ANT_MODEM_LOSS_B128                    /* 0xf480*/,
#endif
/* END DTS2014092901885 Y00230200 2014-10-09 Modified */
#endif
};

/* User ID need to restore */
unsigned short  g_ausNvResumeUserIdList[] =
{
    en_NV_Item_ScheduleWatchDog_Time
};


/* �Ǽ��ܰ汾��Ҫ���лָ��Ļ�Ҫ����NV�� */
unsigned short  g_ausNvResumeSecureIdList[] =
{
    en_NV_Item_CustomizeSimLockPlmnInfo,
    en_NV_Item_CardlockStatus,
    en_NV_Item_CustomizeSimLockMaxTimes
};


/* MBB ��Ʒ�߻ָ���������NV�б� ����Ʒ���ݶ���������Լ����*/
/*Begin DTS2014121006935 y00187523 20141211 modified*/
/* ��������������ָ��������������������в�Ʒ����MBB�ĸ������ */
unsigned short  g_ausNvResumeDefualtIdList[] =
{
#if (FEATURE_OFF == MBB_COMMON)
    en_NV_Item_IMEI 
#else
    /*�Ĵ����Ƕ��Ƴ����ָ��б�*/
    en_NV_Item_IMEI,
    en_NV_Item_WEBNAS_SD_WORKMODE,
    en_NV_Item_SelPlmn_Mode,
    en_NV_Item_RPlmnWithRat,
    en_NV_Item_RAT_PRIO_LIST,
    /*nv for profile*/
    en_NV_Item_Taf_PdpPara_0,
    en_NV_Item_Taf_PdpPara_1,
    en_NV_Item_Taf_PdpPara_2,
    en_NV_Item_Taf_PdpPara_3,
    en_NV_Item_Taf_PdpPara_4,
    en_NV_Item_Taf_PdpPara_5,
    en_NV_Item_Taf_PdpPara_6,
    en_NV_Item_Taf_PdpPara_7,
    en_NV_Item_Taf_PdpPara_8,
    en_NV_Item_Taf_PdpPara_9,
    en_NV_Item_Taf_PdpPara_10,
    en_NV_Item_Taf_PdpPara_11,
    en_NV_Item_USB_SECURITY_FLAG,
    en_NV_Item_User_Set_Freqbands,
#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
    NV_FTEN_USB_SWITCH_SEL,
#endif
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
    en_NV_Item_NDIS_Authdata_1,
#endif
#if (FEATURE_ON == MBB_CUS_LTE_BAND_CHANGE)
    en_NV_Item_USER_SET_LTEBANDS,
#endif /*FEATURE_ON == MBB_CUS_LTE_BAND_CHANGE*/
#if (FEATURE_ON == MBB_WPG_LTE_ATTACH_APN_LIST)
    NV_ID_LTE_ATTACH_PROFILE_0,                  /*50578*/
    NV_ID_LTE_ATTACH_PROFILE_CONTROL,         /*50591*/
#endif
#if (FEATURE_ON == MBB_FEATURE_SBM_CUSTOMIZE)
    en_NV_Item_NDIS_Authdata_1,
#endif/*FEATURE_ON == MBB_FEATURE_SBM_CUSTOMIZE*/
    /*GSM ��ʷƵ��*/
    en_NV_Item_GSM_Ba_Count,
    en_NV_Item_GSM_Ba_List,
    en_NV_Item_Prefer_GSM_PLMN_Count,
    en_NV_Item_Prefer_GSM_PLMN_List,
    /*WCDMA ��ʷƵ��*/
    en_NV_Item_NetWorkPara,
    en_NV_Item_WCDMA_PLMN_FREQ_PAIR_List,
    /*TDS ��ʷƵ��*/
    EN_NV_ID_TDS_BA_LIST,
    /*LTE ��ʷƵ��*/
    EN_NV_ID_BAND1_CAND_INFO  ,
    EN_NV_ID_BAND2_CAND_INFO  ,
    EN_NV_ID_BAND3_CAND_INFO  ,
    EN_NV_ID_BAND4_CAND_INFO  ,
    EN_NV_ID_BAND5_CAND_INFO  ,
    EN_NV_ID_BAND6_CAND_INFO  ,
    EN_NV_ID_BAND7_CAND_INFO  ,
    EN_NV_ID_BAND8_CAND_INFO  ,
    EN_NV_ID_BAND9_CAND_INFO  ,
    EN_NV_ID_BAND10_CAND_INFO ,
    EN_NV_ID_BAND11_CAND_INFO ,
    EN_NV_ID_BAND12_CAND_INFO ,
    EN_NV_ID_BAND13_CAND_INFO ,
    EN_NV_ID_BAND14_CAND_INFO ,
    EN_NV_ID_BAND15_CAND_INFO ,
    EN_NV_ID_BAND16_CAND_INFO ,
    EN_NV_ID_BAND17_CAND_INFO ,
    EN_NV_ID_BAND18_CAND_INFO ,
    EN_NV_ID_BAND19_CAND_INFO ,
    EN_NV_ID_BAND20_CAND_INFO ,
    EN_NV_ID_BAND21_CAND_INFO ,
    EN_NV_ID_BAND22_CAND_INFO ,
    EN_NV_ID_BAND23_CAND_INFO ,
    EN_NV_ID_BAND24_CAND_INFO ,
    EN_NV_ID_BAND25_CAND_INFO ,
    EN_NV_ID_BAND26_CAND_INFO ,
    EN_NV_ID_BAND27_CAND_INFO ,
    EN_NV_ID_BAND28_CAND_INFO ,
    EN_NV_ID_BAND29_CAND_INFO ,
    EN_NV_ID_BAND30_CAND_INFO ,
    EN_NV_ID_BAND31_CAND_INFO ,
    EN_NV_ID_BAND32_CAND_INFO ,
    EN_NV_ID_BAND33_CAND_INFO ,
    EN_NV_ID_BAND34_CAND_INFO ,
    EN_NV_ID_BAND35_CAND_INFO ,
    EN_NV_ID_BAND36_CAND_INFO ,
    EN_NV_ID_BAND37_CAND_INFO ,
    EN_NV_ID_BAND38_CAND_INFO ,
    EN_NV_ID_BAND39_CAND_INFO ,
    EN_NV_ID_BAND40_CAND_INFO ,
    EN_NV_ID_BAND41_CAND_INFO ,
    EN_NV_ID_BAND42_CAND_INFO ,
    EN_NV_ID_BAND43_CAND_INFO ,
    EN_NV_ID_BAND64_CAND_INFO ,
#endif
};
/*End DTS2014121006935 y00187523 20141211 modified*/
/*****************************************************************************
Function   : NV_GetResumeNvIdNum
Description: Return the number of resumed NV.
Input      : NV_RESUME_ITEM_ENUM_UINT32 - resumed NV's type.
Return     : Zero or others.
Other      :
*****************************************************************************/
unsigned long bsp_nvm_getRevertNum(unsigned long enNvItem)
{
    if (NV_MANUFACTURE_ITEM == enNvItem)
    {
        return sizeof(g_ausNvResumeManufactureIdList)/sizeof(g_ausNvResumeManufactureIdList[0]);
    }

    if (NV_USER_ITEM == enNvItem)
    {
        return sizeof(g_ausNvResumeUserIdList)/sizeof(g_ausNvResumeUserIdList[0]);
    }

    if (NV_SECURE_ITEM == enNvItem)
    {
        return sizeof(g_ausNvResumeSecureIdList)/sizeof(g_ausNvResumeSecureIdList[0]);
    }

    if(NV_MBB_DEFUALT_ITEM == enNvItem)
    {
        return sizeof(g_ausNvResumeDefualtIdList) / sizeof(g_ausNvResumeDefualtIdList[0]);
    }

    return 0;
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

