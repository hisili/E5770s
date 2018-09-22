/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : GasNvInterface.h
  Description     : GasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __GASNVINTERFACE_H__
#define __GASNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(2)
#else
#pragma pack(push, 2)
#endif

#include "vos.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NVIM_ULTRA_CLASSMARK_LEN                            (24)
#define NVIM_BAND_PWR_LEN                                   (8)
#define NVIM_CLASSMARK1_LEN                                 (2)
#define NVIM_CLASSMARK2_LEN                                 (4)
#define NVIM_CLASSMARK3_LEN                                 (16)
#define NVIM_CLASSMARK3_R8_LEN                              (36)
#define NVIM_GCF_ITEM_LEN                                   (80)
#define NVIM_GSM_BA_MAX_SIZE                                (33)
#define NVIM_EGPRS_RA_CAPABILITY_DATA_LEN                   (53)
#define NVIM_PREFER_GSM_PLMN_LIST_LEN                       (976)
#define NVIM_GSM_DEC_FAIL_ARFCN_LIST_LEN                    (120)
#define NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM                    (64)
#define NVIM_TDS_MAX_SUPPORT_BANDS_NUM                      (8)
#define NVIM_EUTRA_CAPA_COMM_INFO_SIZE                      (260)
#define NVIM_CBS_MID_LIST_LEN                               (2004)
#define NVIM_CBS_MID_RANGE_LIST_LEN                         (2004)
#define NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_CNT_MAX        (20)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NVIM_TDS_FREQ_BAND_LIST_ENUM
{
    ID_NVIM_TDS_FREQ_BAND_A         = 0x01,         /* Ƶ�㷶Χ: 9504~9596  10054~10121 */
    ID_NVIM_TDS_FREQ_BAND_B         = 0x02,         /* Ƶ�㷶Χ: 9254~9546  9654~9946 */
    ID_NVIM_TDS_FREQ_BAND_C         = 0x04,         /* Ƶ�㷶Χ: 9554~9646 */
    ID_NVIM_TDS_FREQ_BAND_D         = 0x08,         /* Ƶ�㷶Χ: 12854~13096 */
    ID_NVIM_TDS_FREQ_BAND_E         = 0x10,         /* Ƶ�㷶Χ: 11504~11996 */
    ID_NVIM_TDS_FREQ_BAND_F         = 0x20,         /* Ƶ�㷶Χ: 9404~9596 */
    ID_NVIM_TDS_FREQ_BAND_BUTT
};
typedef VOS_UINT8  NVIM_TDS_FREQ_BAND_LIST_ENUM_UINT8;

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 �ṹ��    : NVIM_ULTRA_CLASSMARK_STRU
 �ṹ˵��  : en_NV_Item_Ultra_Classmark �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucUltraClassmark[NVIM_ULTRA_CLASSMARK_LEN];
}NVIM_ULTRA_CLASSMARK_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_MULTIRATE_FLAG_STRU
 �ṹ˵��  : en_NV_Item_Gas_MultiRateFlag �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMultiRateFlag;
}NVIM_GAS_MULTIRATE_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_BAND_PWR_STRU
 �ṹ˵��  : en_NV_Item_Band_Pwr �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucBandPwr[NVIM_BAND_PWR_LEN];
}NVIM_BAND_PWR_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_VGCS_FLAG_STRU
 �ṹ˵��  : en_NV_Item_Vgcs_Flag �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usVgcsFlag;
}NVIM_VGCS_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EGPRS_MULTI_SLOT_CLASS_STRU
 �ṹ˵��  : en_NV_Item_Egprs_Multi_Slot_Class �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEgprsMultiSlotClass;                  /* Range: [0,12] */
}NVIM_EGPRS_MULTI_SLOT_CLASS_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_CLASSMARK1_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Classmark1 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark1[NVIM_CLASSMARK1_LEN];
}NVIM_GSM_CLASSMARK1_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_CLASSMARK2_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Classmark2 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark2[NVIM_CLASSMARK2_LEN];
}NVIM_GSM_CLASSMARK2_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_CLASSMARK3_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Classmark3 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark3[NVIM_CLASSMARK3_LEN];
}NVIM_GSM_CLASSMARK3_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_IND_FREQ_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Ind_Freq �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmIndFreq;
}NVIM_GSM_IND_FREQ_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GCF_ITEM_STRU
 �ṹ˵��  : en_NV_Item_GCF_Item �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGcfItem[NVIM_GCF_ITEM_LEN];
}NVIM_GCF_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_G2W_RSSI_RSCP_OFFSET_STRU
 �ṹ˵��  : en_NV_Item_G2W_RSSI_RSCP_OFFSET �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usG2WRssiRscpOffset;
}NVIM_G2W_RSSI_RSCP_OFFSET_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_BA_COUNT_STRU
 �ṹ˵��  : en_NV_Item_GSM_Ba_Count �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmBaCount;
}NVIM_GSM_BA_COUNT_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_BA_LIST_STRU
 �ṹ˵��  : en_NV_Item_GSM_Ba_List �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          usArfcn[NVIM_GSM_BA_MAX_SIZE];
}NVIM_GSM_BA_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EGPRS_FLAG_STRU
 �ṹ˵��  : en_NV_Item_Egprs_Flag �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEgprsFlag;
}NVIM_EGPRS_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EGPRS_RA_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_EgprsRaCapability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucEgprsRaCapabilityData[NVIM_EGPRS_RA_CAPABILITY_DATA_LEN];
}NVIM_EGPRS_RA_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PREFER_GSM_PLMN_COUNT_STRU
 �ṹ˵��  : en_NV_Item_Prefer_GSM_PLMN_Count �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPreferGsmPlmnCount;
}NVIM_PREFER_GSM_PLMN_COUNT_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PREFER_GSM_PLMN_LIST_STRU
 �ṹ˵��  : en_NV_Item_Prefer_GSM_PLMN_List �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausPreferGsmPlmnListData[NVIM_PREFER_GSM_PLMN_LIST_LEN];
}NVIM_PREFER_GSM_PLMN_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_DEC_FAIL_ARFCN_COUNT_STRU
 �ṹ˵��  : en_NV_Item_GSM_DEC_FAIL_ARFCN_Count �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmDecFailArfcnCount;
}NVIM_GSM_DEC_FAIL_ARFCN_COUNT_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_DEC_FAIL_ARFCN_LIST_STRU
 �ṹ˵��  : en_NV_Item_GSM_DEC_FAIL_ARFCN_List �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmDecFailArfcnList[NVIM_GSM_DEC_FAIL_ARFCN_LIST_LEN];
}NVIM_GSM_DEC_FAIL_ARFCN_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PREFER_GSM_PLMN_SWITCH_STRU
 �ṹ˵��  : en_NV_Item_Prefer_GSM_PLMN_Switch �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPreferGsmPlmnSwitch;
}NVIM_PREFER_GSM_PLMN_SWITCH_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GERAN_FEATURE_PACKAGE1_STRU
 �ṹ˵��  : en_NV_Item_Geran_Feature_Package1 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGeranFeaturePackage1;                 /* Range: [0,1] */
}NVIM_GERAN_FEATURE_PACKAGE1_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_A5_STRU
 �ṹ˵��  : en_NV_Item_Gsm_A5 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmA5;                                /* Range: [0,7] */
}NVIM_GSM_A5_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_LOW_COST_EDGE_FLAG_STRU
 �ṹ˵��  : en_NV_Item_LowCostEdge_Flag �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLowCostEdgeFlag;                      /* Range: [0,1] */
}NVIM_LOW_COST_EDGE_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GPRS_ACTIVE_TIMER_LENGTH_STRU
 �ṹ˵��  : en_NV_Item_GPRS_ActiveTimerLength �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGprsActiveTimerLength;
}NVIM_GPRS_ACTIVE_TIMER_LENGTH_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GPRS_MULTI_SLOT_CLASS_STRU
 �ṹ˵��  : en_Nv_Item_Gprs_Multi_Slot_Class �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGprsMultiSlotClass;                   /* Range: [0,12] */
}NVIM_GPRS_MULTI_SLOT_CLASS_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_PLMN_SEARCH_ARFCN_MAX_NUM_STRU
 �ṹ˵��  : en_NV_Item_GSM_PLMN_SEARCH_ARFCN_MAX_NUM �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmPlmnSearchArfcmMaxNum;             /* Range: [0x1,0x8C] */
}NVIM_GSM_PLMN_SEARCH_ARFCN_MAX_NUM_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GCBS_CONF_STRU
 �ṹ˵��  : en_Nv_Item_GCBS_Conf �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usECBCHSwitch;              /* Range: [0,1] */
    VOS_UINT16                                      usDrxSwitch;                /* Range: [0,1] */
    VOS_UINT32                                      ulGCBSActiveTimerLength;
}NVIM_GCBS_CONF_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_REPEATED_ACCH_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_Repeated_Acch_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usRepeatedAcchCapability;
}NVIM_REPEATED_ACCH_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_ES_IND_STRU
 �ṹ˵��  : en_NV_Item_ES_IND �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usEsInd;                    /* Range: [0,1] */
}NVIM_ES_IND_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_GPRS_Extended_Dynamic_Allocation_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usGprsExtDynAllocCap;       /* Range: [0,1] */
}NVIM_GPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EGPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_EGPRS_Extended_Dynamic_Allocation_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usEGprsExtDynAllocCap;      /* Range: [0,1] */
}NVIM_EGPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_REVISION_LEVEL_INDICATOR_STRU
 �ṹ˵��  : en_NV_Item_Revision_Level_Indicator �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usRevLvlInd;                /* Range: [0,1] */
}NVIM_REVISION_LEVEL_INDICATOR_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_DOWNLINK_ADVANCED_RECEIVER_PERFORMANCE_STRU
 �ṹ˵��  : en_NV_Item_Downlink_Advanced_Receiver_Performance �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usDlAdvRcvPer;              /* Range: [0,1] */
}NVIM_DOWNLINK_ADVANCED_RECEIVER_PERFORMANCE_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EXT_RLC_MAC_CTRL_MSG_SEGMENT_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_Ext_RLC_MAC_Ctrl_Msg_Segment_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usExtRlcMacCtrlMsgSegCap;   /* Range: [0,1] */
}NVIM_EXT_RLC_MAC_CTRL_MSG_SEGMENT_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PS_HANDOVER_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_PS_Handover_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPsHandoverCapability;     /* Range: [0,1] */
}NVIM_PS_HANDOVER_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_WEAK_SIGNAL_THREHOLD_STRU
 �ṹ˵��  : en_NV_Item_GAS_Errorlog_Energy_Threshold �ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                                       sWeakSignalThreshold;
    VOS_UINT8                                       aucReserve[2];
}NVIM_GAS_WEAK_SIGNAL_THREHOLD_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_MULTIRATE_CAP_STRU
 �ṹ˵��  : en_NV_Item_GSM_Multirate_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucGsmMultirateCap;
    VOS_UINT8                                       aucRsv[3];
}NVIM_GSM_MULTIRATE_CAP_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_CLASSMARK3_R8_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Classmark3_R8 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       aucGsmClassMark3Data[NVIM_CLASSMARK3_R8_LEN];
}NVIM_GSM_CLASSMARK3_R8_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usLteMeasSupportedFlg;      /* Range: [0,1] */
}NVIM_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PRI_BASED_RESEL_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_PRI_BASED_RESEL_SUPPORT_FLG �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPriBasedReselSupportFlg;  /* Range: [0,1] */
}NVIM_PRI_BASED_RESEL_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE_STRU
 �ṹ˵��  : en_NV_Item_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usLteSupportInTransferMode; /* Range: [0,3] */
}NVIM_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU
 �ṹ˵��  : ��������һ�� LTE Ƶ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBandNo;
    VOS_UINT8                           ucDuplexModeFlg;
    VOS_UINT8                           aucReserve[2];
}NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU
 �ṹ˵��  : en_NV_Item_EUTRA_CAPA_COMM_INFO �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usBandCnt;
    VOS_UINT8                               aucReserved1[2];
    NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU       astCandBands[NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM];
}NVIM_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU
 �ṹ˵��  : en_NV_Item_GAS_High_Multislot_Class �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usHighMultislotClassFlg;
    VOS_UINT16                              usHighMultislotClass;
}NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GPRS_NON_DRX_TIMER_LENGTH_STRU
 �ṹ˵��  : en_NV_Item_GPRS_Non_Drx_Timer_Length �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usNonDrxTimerLen;                   /* Range: [0,7] */
}NVIM_GPRS_NON_DRX_TIMER_LENGTH_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU
 �ṹ˵��  : en_NV_Item_UTRAN_TDD_FREQ_BAND �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucBandCnt;                          /* Range: [0,6] */
    VOS_UINT8                               aucReserved[3];
    VOS_UINT8                               aucBandNo[NVIM_TDS_MAX_SUPPORT_BANDS_NUM];
}NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_QSEARCH_CUSTOMIZATION_STRU
 �ṹ˵��  : en_NV_Item_QSearch_Customization �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usQSearchCustomMode;
}NVIM_QSEARCH_CUSTOMIZATION_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_POOR_RXQUAL_THRESHOLD_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Poor_RxQual_ThresHold �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usRrPoorRxQualThresHold;
}NVIM_GSM_POOR_RXQUAL_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_CSFB_CUSTOMIZATION_STRU
 �ṹ˵��  : en_NV_Item_Csfb_Customization �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usCsfbCustomization;
}NVIM_CSFB_CUSTOMIZATION_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_CBS_MID_LIST_STRU
 �ṹ˵��  : en_NV_Item_CBS_MID_List �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucCbsMidList[NVIM_CBS_MID_LIST_LEN];
}NVIM_CBS_MID_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_CBS_MID_RANGE_LIST_STRU
 �ṹ˵��  : en_NV_Item_CBS_MID_Range_List �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucCbsMidRangeList[NVIM_CBS_MID_RANGE_LIST_LEN];
}NVIM_CBS_MID_RANGE_LIST_STRU;


typedef struct
{
   VOS_UINT8                            ucFrLteMeasFlag;                        /* �Ƿ���GSM�����ض���LTE��LTEƵ�������0: �ر�, 1: ������Ĭ��ֵΪ1 */       
   VOS_UINT8                            ucMaxSavedMeasTimes;                    /* ��󱣴�Ĳ���������Ĭ��ֵΪ8����Χ:[0,8] */  

   VOS_UINT8                            ucFrInvalidMeasFlag;                    /* �Ƿ����ò�������ж�GSM�����ض���LTE�Ƿ���Ч��0: �ر�, 1: ������Ĭ��ֵΪ1 */ 
   VOS_UINT8                            ucMaxInvalidMeasTimes;                  /* �����Ч���������������ж�Ƶ���Ƿ���Ч����������󱣴�Ĳ���������Ĭ��ֵΪ8����Χ:[0,8] */
}NVIM_GSM_AUTO_FR_LTE_MEAS_CONFIG_STRU;


typedef struct
{
   VOS_UINT8                            ucC1CustomizeSwitchFlag;          /* �Ƿ���·��C1���ƣ�0: �ر�, 1: ������Ĭ��ֵΪ0 */       
   VOS_UINT8                            ucRxlevAccessMin;                 /* ����·��C1���ƺ󣬶��Ƶ���С�����ƽ�ȼ���Ĭ�ϵȼ�Ϊ8����Χ:[0,63] */  
   VOS_UINT8                            ucC1ValueThreshold;               /* C1��ֵ */
   VOS_UINT8                            aucRsv[1];
}NVIM_GSM_C1_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_NFREQ_THRESHOLD_STRU
 �ṹ˵��  : en_NV_Item_Gsm_NFreq_Threshold �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucFirstNFreqThreshold;                 /* ��Ƶ���Ź������� */
    VOS_UINT8                            aucRsv[3];
}NVIM_GSM_NFREQ_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_W_NON_NCELL_MEAS_CTRL_STRU
 �ṹ˵��  : en_NV_Item_Gas_W_Non_NCell_Meas_Ctrl �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucIdleNonNCellMeasEnable;              /* ����̬���Ƿ��������������� */
    VOS_UINT8                            ucTransferNonNCellMeasEnable;          /* ����̬���Ƿ��������������� */
    VOS_INT16                            sRscpThreshold;                        /* ���������������� RSCP ���� */
    VOS_INT16                            sEcn0Threshold;                        /* ���������������� ECN0 ���� */
    VOS_INT16                            sRssiThreshold;                        /* ���������������� RSSI ���� */
}NVIM_GAS_W_NON_NCELL_MEAS_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_CELL_INFO_RPT_CFG_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Cell_Info_Rpt_Cfg �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucCellInfoRptFlg;      /* �Ƿ������ϱ�: 0:������; 1:���� */
    VOS_UINT8                            aucRsv[1];             /* ����λ */
    VOS_UINT16                           usRptInterval;         /* �ϱ����ڳ���, ��λ: ms */
}NVIM_GSM_CELL_INFO_RPT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_INDIVIDUAL_CUSTOMIZE_CFG_STRU
 �ṹ˵��  : en_NV_Item_Gas_Individual_Customize_Cfg �ṹ,�������÷Ǳ�����ⶨ����ص�����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAccFailNoPunishCfg;                   /* �Ƿ�ͷ��漴����ʧ�ܵ�С��:
                                                                                   bit0: 1: PSʧ�ܲ��ͷ�; 0: PSʧ�ܳͷ�
                                                                                   bit1: 1: CSʧ�ܲ��ͷ�; 0: CSʧ�ܳͷ� */
    VOS_INT8                            cFreqRxlevThreshold;                    /* ��ЧƵ����������,��Ҫ������������
                                                                                   ������ѡ Ŀ��С��ѡ��ʱҲ���õ� */

    VOS_UINT8                           ucAutoFrNonChanRelCase;                 /* û���յ� Channel Release ���쳣�������Ƿ����� FR:
                                                                                   bit0: 1: �����Ҷ�ʱ���� FR; 
                                                                                         0: �����Ҷ�ʱ������FR
                                                                                   bit1: 1: ������·ʧ������FR; 
                                                                                         0: ������·ʧ�ܲ�����FR */

    VOS_UINT8                           aucRsv[37];
}NVIM_GAS_INDIVIDUAL_CUSTOMIZE_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
}NVIM_GAS_PLMN_ID_STRU;

typedef struct
{
   VOS_UINT16                           usPlmnCnt;                                                  /* ��������PLMN���� */  
   VOS_UINT16                           usReserve;
   NVIM_GAS_PLMN_ID_STRU                astPlmn[NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_CNT_MAX];       /* Ԥ��λ��Ϊ�Ժ�KWKCԤ�� */
}NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_STRU;

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










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasNvInterface.h */
