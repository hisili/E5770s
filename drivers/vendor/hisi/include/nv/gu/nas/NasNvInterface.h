/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasNvInterface.h
  Description     : NasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __NASNVINTERFACE_H__
#define __NASNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

#include "PsTypeDef.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NAS_MMC_NV_ITEM_ACTIVE          (1)                                     /* NV��� */
#define NAS_MMC_NV_ITEM_DEACTIVE        (0)                                     /* NV��δ���� */

/* GPRS GEA �㷨֧�ֺ궨�� */
#define NAS_MMC_GPRS_GEA1_SUPPORT       (0x01)                                  /* ֧��GPRS GEA1�㷨 */
#define NAS_MMC_GPRS_GEA1_VALUE         (0x80)                                  /* ֧��GEA1ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA2_VALUE         (0x40)                                  /* ֧��GEA2ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA3_VALUE         (0x20)                                  /* ֧��GEA3ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA4_VALUE         (0x10)                                  /* ֧��GEA4ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA5_VALUE         (0x08)                                  /* ֧��GEA5ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA6_VALUE         (0x04)                                  /* ֧��GEA6ʱ����������ֵ */
#define NAS_MMC_GPRS_GEA7_VALUE         (0x02)                                  /* ֧��GEA7ʱ����������ֵ */

#define NAS_MMC_GPRS_GEA2_SUPPORT       (0x02)                                  /* ֧��GPRS GEA2�㷨 */
#define NAS_MMC_GPRS_GEA3_SUPPORT       (0x04)                                  /* ֧��GPRS GEA3�㷨 */
#define NAS_MMC_GPRS_GEA4_SUPPORT       (0x08)                                  /* ֧��GPRS GEA4�㷨 */
#define NAS_MMC_GPRS_GEA5_SUPPORT       (0x10)                                  /* ֧��GPRS GEA5�㷨 */
#define NAS_MMC_GPRS_GEA6_SUPPORT       (0x20)                                  /* ֧��GPRS GEA6�㷨 */
#define NAS_MMC_GPRS_GEA7_SUPPORT       (0x40)                                  /* ֧��GPRS GEA7�㷨 */
#define NAS_MMC_NVIM_MAX_EPLMN_NUM      (16)                                    /* en_NV_Item_EquivalentPlmn NV�е�Чplmn���� */
#define NAS_MMC_NVIM_MAX_MCC_SIZE       (3)                                     /* plmn��Mcc��󳤶� */
#define NAS_MMC_NVIM_MAX_MNC_SIZE       (3)                                     /* plmn��Mnc��󳤶� */
#define NAS_MMC_LOW_BYTE_MASK           (0x0f)

#define NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM                  (6)                 /* �û����õ�����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM                     (6)                 /* �û����õ�EHplmn�ĸ��� */
#define NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM            (8)                 /* ��ֹ���뼼����PLMN ID�������� */

#define NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN               (8)               /* �û����õ�OPLMN�汾����󳤶� */
#define NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM                  (6)               /* �û����õ�OPLMN����֧�ֵ�USIM/SIM���ĸ��� */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_NUM                   (256)             /* �û����õ�OPLMN�������� */
#define NAS_MMC_NVIM_OPLMN_WITH_RAT_UNIT_LEN                  (5)               /* �û����õĴ����뼼��OPLMN������Ԫ���ȣ���6F61�ļ��Ļ������ȵ�ԪΪ5 */
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN              (500)             /* �û�����OPLMN������ֽ���,����ǰֻ֧��500*/
#define NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN       (1280)            /* ��չ����û�����OPLMN������ֽ���*/

#define NAS_NVIM_MAX_OPER_SHORT_NAME_LEN                36
#define NAS_NVIM_MAX_OPER_LONG_NAME_LEN                 40

#define NAS_NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* ����IMSI�ĳ��� */
#define NAS_MML_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIM��PSLOCI�ļ��ĳ��� */
#define NAS_NVIM_PS_LOCI_SIM_FILE_LEN                    (14)                    /* USIM��PSLOCI�ļ��ĳ��� */

#define NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM          (6)                 /* ģʽ�Զ��л������Ŀ����ù�������� */
#define NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM       (6)                 /* ģʽ�Զ��л������Ŀ�����USIM/IMSI������Ÿ��� */
#define NAS_MML_MAX_DISABLED_RAT_PLMN_NUM               (8)                     /* ֹ���뼼����PLMN ID�������� */

#define NAS_SIM_FORMAT_PLMN_LEN                     (3)                     /* Sim����ʽ��Plmn���� */

#define NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM                 (16)                    /* ����������֧�ֵ�PLMN ID�������� */

#define NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM                 (16)                    /* ����������֧�ֵ�PLMN ID�������� */

#if(FEATURE_ON == MBB_WPG_COMMON)
#define NAS_MML_BG_SEARCH_REGARDLESS_MCC_NUMBER       (30)                  /* BG�Ѳ����ǹ�����Ĺ����������� */
#else
#define NAS_MML_BG_SEARCH_REGARDLESS_MCC_NUMBER         (10)                     /* BG�Ѳ����ǹ�����Ĺ����������� */
#endif
#define NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST      (5)                     /* ����ԭ��ֵ����б� */

#define NV_ITEM_NET_CAPABILITY_MAX_SIZE                     (10)

#define NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE            (2)                 /* ��ǰ֧�ֵ�Э��汾 */

#define NAS_MMC_NVIM_MAX_IMSI_LEN                           (9)                     /* ����IMSI�ĳ��� */

#define NVIM_MAX_EPLMN_NUM                                  (16)
#define NVIM_MAX_MCC_SIZE                                   (3)
#define NVIM_MAX_MNC_SIZE                                   (3)

#define NVIM_MAX_FDD_FREQ_BANDS_NUM                         (12)

/* Add by z60575 for multi_ssid, 2012-9-5 end */
/*+CGMI - ��ȡ����������*/

#define NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM         (16)
#define NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM          (8)    /* Ԥ����չ */
#define NAS_NVIM_MAX_SUPPORTED_FORBIDDEN_RAT_NUM     (2)

#define NAS_NVIM_FORBIDDEN_RAT_NUM_0                 (0)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_1                 (1)
#define NAS_NVIM_FORBIDDEN_RAT_NUM_2                 (2)


/* ��NVIDö�ٵ�ת����(PS_NV_ID_ENUM, SYS_NV_ID_ENUM, RF_NV_ID_ENUM) */
typedef VOS_UINT16  NV_ID_ENUM_U16;
#define NV_ITEM_IMEI_SIZE                      16
#define NV_ITEM_SELPLMN_MODE_SIZE              2
#define NV_ITEM_MMA_OPERATORNAME_SIZE          84
#define NV_ITEM_AT_PARA_SIZE                   100
#define NV_ITEM_HPLMN_FIRST_SEARCH_SIZE        1  /* ��һ��HPLMN������ʱ���� */
#define NVIM_ITEM_MAX_IMSI_LEN          (9)                     /* ����IMSI�ĳ��� */

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

enum NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM
{
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_PLMN_SELECTION                    = 0,            /* �������� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_NORMAL_CAMP_ON                    = 1,            /* ����פ�� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_OPTIONAL_PLMN_SELECTION           = 2,            /* ������ѡ���� */
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_LIMITED_CAMP_ON                   = 3,            /* ����פ�� */
    
    NAS_MMC_NVIM_SINGLE_DOMAIN_ROAMING_REG_FAIL_ACTION_PLMN_SELECTION            = 4,            /* ������������ע�ᷢ����������HOME�����ϲ���Ч */
    
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8;


enum NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_GPRS_SERV_NOT_ALLOW_IN_PLMN = 14,
    NAS_MMC_NVIM_REG_FAIL_CAUSE_TIMER_TIMEOUT               = 301,                                 /* �ȴ���������ʱ����ʱ */
    NAS_MMC_NVIM_REG_FAIL_CAUSE_BUTT
};
typedef VOS_UINT16 NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16;


enum NAS_MMC_NVIM_REG_DOMAIN_ENUM
{
    NAS_MMC_NVIM_REG_DOMAIN_CS = 1,
    NAS_MMC_NVIM_REG_DOMAIN_PS = 2,                                 /* �ȴ���������ʱ����ʱ */
    NAS_MMC_NVIM_REG_DOMAIN_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8;



enum NAS_MMC_UCS2_ENUM
{
    NAS_MMC_UCS2_HAS_PREFER                                = 0,
    NAS_MMC_UCS2_NO_PREFER                                 = 1,

    NAS_MMC_UCS2_BUTT
};

typedef VOS_UINT16 NAS_MMC_UCS2_ENUM_UINT16;


enum NV_MS_MODE_ENUM
{
    NV_MS_MODE_CS_ONLY,                                                 /* ��֧��CS�� */
    NV_MS_MODE_PS_ONLY,                                                 /* ��֧��PS�� */
    NV_MS_MODE_CS_PS,                                                   /* CS��PS��֧�� */

    NV_MS_MODE_ANY,                                                     /* ANY,�൱�ڽ�֧��CS�� */

    NV_MS_MODE_BUTT
};
typedef VOS_UINT8 NV_MS_MODE_ENUM_UINT8;
/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/

typedef struct
{
    VOS_UINT16 usManualSearchHplmnFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_MANUAL_SEARCH_HPLMN_FLG_STRU;


typedef struct
{
    VOS_UINT16 usAutoSearchHplmnFlg; /*Range:[0,3]*/
}NAS_MMC_NVIM_AUTO_SEARCH_HPLMN_FLG_STRU;


typedef struct
{
    VOS_UINT16 usEHPlmnSupportFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_EHPLMN_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT16 usStkSteeringOfRoamingSupportFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_STK_STEERING_OF_ROAMING_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;                        /* en_NV_Item_Scan_Ctrl_Para NV���Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucReserved;                             /* ���� */
}NVIM_SCAN_CTRL_STRU;


typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
}NAS_NVIM_PLMN_ID_STRU;


typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stOperatorPlmnId;
    VOS_UINT8                           aucOperatorNameShort[NAS_NVIM_MAX_OPER_SHORT_NAME_LEN];/* ��ǰפ��������Ӫ�̵Ķ����� */
    VOS_UINT8                           aucOperatorNameLong[NAS_NVIM_MAX_OPER_LONG_NAME_LEN];  /* ��ǰפ��������Ӫ�̵ĳ����� */
}NAS_MMC_NVIM_OPERATOR_NAME_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulBlackPlmnLockNum;                     /* ֧�ֺ������ĸ���,����Ϊ0ʱ��ʾ��֧�ֺ����� */
    NAS_NVIM_PLMN_ID_STRU               astBlackPlmnId[NAS_MML_NVIM_MAX_BLACK_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_BLACKPLMN_STRU;

typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* �������Ƿ�� */
    VOS_UINT8                           ucHighPrioRatType;                              /* ����֧�ֵĽ��뼼�� */
    VOS_UINT8                           aucReserve[2];
    NAS_NVIM_PLMN_ID_STRU               stHighPrioPlmnId;                       /* ����֧�ֵĸ����ȼ���PLMN ID ,��ʹפ����HPLMN��,��PLMNID�����ȼ�Ҳ�ϸ�*/
    NAS_NVIM_PLMN_ID_STRU               stSimHPlmnId;                           /* SIM����HPLMN ID */
}NAS_MMC_NVIM_AIS_ROAMING_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucAutoReselActiveFlg;                   /* �Ƿ�����LTE�������α��:VOS_TRUE ��ʾ����LTE�������� VOS_FALSE ��ʾ��ֹLTE�������� */
    VOS_UINT8                           ucReserve;
}NAS_MMC_NVIM_USER_AUTO_RESEL_CFG_STRU;


typedef struct
{
    VOS_UINT8                            ucStatus;        /* NV��Ч��־, 1: ��Ч��0����Ч */
	VOS_UINT8                            ucReserved;      /* ���ֽڶ��� */
    VOS_UINT16                           usPrioHplmnAct;      /*���Ƶ����Ƚ��뼼��*/
}NAS_MMC_NVIM_PRIO_HPLMNACT_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* available timer��ʱ����һ�ε�ʱ�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* available timer��ʱ����һ�εĴ��� */
    VOS_UINT32                          ulDeepSearchTimeLen;                    /* available timer��ʱ����˯��ʱ�� */
    VOS_UINT32                          ulDeepSearchTimeCount;
}NAS_MMC_NVIM_AVAIL_TIMER_CFG_STRU;


typedef struct
{
    VOS_UINT32                          ulWhitePlmnLockNum;                     /* ֧�ְ������ĸ���,����Ϊ0ʱ��ʾ��֧�ְ����� */
    NAS_NVIM_PLMN_ID_STRU               astWhitePlmnId[NAS_MML_NVIM_MAX_WHITE_LOCK_PLMN_NUM];
}NAS_MMC_NVIM_OPER_LOCK_WHITEPLMN_STRU;


typedef struct
{
    VOS_UINT16 usSupportFlg; /*Range:[0,1]*/
}NAS_MMC_NVIM_CPHS_SUPPORT_FLG_STRU;

/* Added by l60609 for B060 Project, 2012-2-20, Begin   */

typedef struct
{
    VOS_UINT8                               ucStatus;                               /*�Ƿ񼤻0�����1���� */
    VOS_UINT8                               ucActFlg;
}NAS_PREVENT_TEST_IMSI_REG_STRU;
/* Added by l60609 for B060 Project, 2012-2-20, End   */
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/


typedef struct
{
    VOS_UINT8   ucHplmnSearchPowerOn;
    VOS_UINT8   ucReserve;
}NAS_MMC_NVIM_HPLMN_SEARCH_POWERON_STRU;



typedef struct
{
    VOS_UINT8                           ucTinType;                              /* TIN���� */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT8                           aucImsi[NAS_NVIM_ITEM_MAX_IMSI_LEN];        /* �ϴα����IMSI������ */
}NAS_NVIM_TIN_INFO_STRU;


typedef struct
{
    VOS_UINT32 ulAutoStart;
}NAS_MMA_NVIM_AUTO_START_STRU;



typedef struct
{
    VOS_UINT8                           ucSingleDomainFailPlmnSrchFlag;         /* DT�������󣬵���ע�ᱻ�ܺ���Ҫ�������� */
    VOS_UINT8                           ucReserved;                             /* ����*/
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_CNT_STRU;


typedef struct
{
    VOS_UINT8  aucPsLocInfo[NAS_NVIM_PS_LOCI_SIM_FILE_LEN];
}NAS_NVIM_PS_LOCI_SIM_FILES_STRU;


typedef struct
{
    VOS_UINT8                          ucStatus;                                /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                          ucGeaSupportCtrl;                        /* �ն�����:GPRS GEA�㷨֧�ֿ��� */
}NAS_MMC_NVIM_GPRS_GEA_ALG_CTRL_STRU;


typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;    /* en_NV_Item_Lte_Cs_Service_Config NV���Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    VOS_UINT8                           ucLteCsServiceCfg;  /* LTE֧�ֵ� cs��ҵ������*/
}NAS_NVIM_LTE_CS_SERVICE_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucWaitSysinfoTimeLen;
}NAS_MMC_NVIM_HO_WAIT_SYSINFO_TIMER_CFG_STRU;




typedef struct
{
    VOS_UINT8                           ucLteRoamAllowedFlg;
    VOS_UINT8                           aucReserve[1];
    VOS_UINT8                           aucRoamEnabledMccList[20];/* �������εĹ������б� */
}NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucRoamRplmnflg;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                         aucRoamEnabledMccList[5];/* �������εĹ������б� */
}NAS_MMC_NVIM_ROAM_SEARCH_RPLMN_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucActFlg;
    VOS_UINT8                           aucReserved[3];
}NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucWcdmaPriorityGsmFlg;                  /* H3G��������W����������G*/

    VOS_UINT8                           ucSortAvailalePlmnListRatPrioFlg;    /* �Ƿ�syscfg���ý��뼼�����ȼ�����ߵ����������б��ʶ��1:��; 0:���Ǹ��������簴���������������粻����*/
}NAS_MMC_NVIM_WCDMA_PRIORITY_GSM_FLG_STRU;


typedef struct
{
    VOS_UINT8                           ucPsOnlyCsServiceSupportFlg;            /* ����������ΪPS ONLYʱ���Ƿ�֧��CS����źͺ���ҵ��(�������г���)*/
    VOS_UINT8                           ucReserved;                             /* ����*/
}NAS_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT8                           ucCcbsSupportFlg;                       /* CCBS(��æ�������)ҵ��*/
    VOS_UINT8                           ucReserved;                             /* ����*/
}NAS_NVIM_CCBS_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucCustomMccNum;
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          aulCustommMccList[10];                   /* �������εĹ������б� */
}NAS_MMC_NVIM_HPLMN_SEARCH_REGARDLESS_MCC_SUPPORT_STRU;



typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved;
}NVIM_ACTING_HPLMN_SUPPORT_FLAG_STRU;


typedef struct
{
    VOS_UINT8                           ucNvimActiveFlg;
    VOS_UINT8                           ucReserved;                             /* ����*/
}NAS_MMC_NVIM_REG_FAIL_NETWORK_FAILURE_CUSTOM_FLG_STRU;




typedef struct
{
    NAS_MMC_NVIM_REG_FAIL_CAUSE_ENUM_UINT16                 enRegCause;
    NAS_MMC_NVIM_REG_DOMAIN_ENUM_UINT8                      enDomain;
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_ENUM_UINT8   enAction;
}NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU;



typedef struct
{
    VOS_UINT8                                               ucActiveFlag;
    VOS_UINT8                                               ucCount;
    VOS_UINT8                                               auReserv[2];
    NAS_MMC_NVIM_SINGLE_DOMAIN_REG_FAIL_ACTION_STRU         astSingleDomainFailActionList[NAS_MML_SINGLE_DOMAIN_FAIL_ACTION_MAX_LIST];
}NAS_MMC_NVIM_SINGLE_DOMAIN_FAIL_ACTION_LIST_STRU;


typedef struct {
    VOS_UINT8                           aucSimPlmn[NAS_SIM_FORMAT_PLMN_LEN];
    VOS_UINT8                           aucReserve[1];
}NAS_SIM_FORMAT_PLMN_ID;


typedef struct
{
    VOS_UINT8                           ucUtranMode;                            /* ��ǰ֧�ֵ�UTRANģʽ */
    VOS_UINT8                           ucReserve;
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_STRU;


typedef struct
{
    VOS_UINT8                           ucUtranSwitchMode;                      /* 0��UTRANģʽΪFDD 1��UTRANģʽΪTDD 2:AUTO SWITCH */
    VOS_UINT8                           ucTdMccListNum;                         /* ֧��TD����Ĺ��ҺŸ��� */
    VOS_UINT8                           ucImsiPlmnListNum;                      /* ����IMS PLMN����UTRANģʽ�Ƿ�AUTO SWITCHʱ����ǰIMSI��PLMN�ڴ��б��еĶ�֧���Զ��л�������̶�ΪWģ */
    VOS_UINT8                           aucReserve[1];

    VOS_UINT32                          aulTdMccList[NAS_UTRANCTRL_MAX_NVIM_CFG_TD_MCC_LIST_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_UTRANCTRL_MAX_NVIM_CFG_IMSI_PLMN_LIST_NUM];
}NAS_UTRANCTRL_NVIM_UTRAN_MODE_AUTO_SWITCH_STRU;





typedef struct
{
    VOS_UINT8                           ucIsUtranTddCsSmcNeeded;                /* ������3G TDDģʽ���Ƿ���Ҫ����CS SMC��֤���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           ucIsUtranTddPsSmcNeeded;                /* ������3G TDDģʽ���Ƿ���Ҫ����PS SMC��֤���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           aucReserved[2];                         /* ���� */
}NAS_UTRANCTRL_NVIM_SMC_CTRL_FLAG_STRU;



typedef struct
{
    VOS_UINT8   ucAccBarPlmnSearchFlg;
    VOS_UINT8   aucReserve[3];
}NAS_MMC_NVIM_ACC_BAR_PLMN_SEARCH_FLG_STRU;



typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /* ������ʹ�ܱ�־ */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* �Ƿ���IMSI�б�İ�������0:����Ҫ 1:��Ҫ */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /* �������õİ汾�� */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           ucOplmnListNum;                                       /* �������õ�Oplmn�ĸ��� */
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_LEN];/* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}NAS_MMC_NVIM_USER_CFG_OPLMN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU
 �ṹ˵��  : NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU NVIM���е��û����õ�OPLMN
 1.��    ��   : 2013��11��26��
   �޸�����   : ��NV֧�ֵ����OPLMN������չ��256��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;                                          /* ������ʹ�ܱ�־ */
    VOS_UINT8                           ucImsiCheckFlg;                                       /* �Ƿ���IMSI�б�İ�������0:����Ҫ 1:��Ҫ */
    VOS_UINT8                           aucVersion[NAS_MMC_NVIM_MAX_USER_OPLMN_VERSION_LEN];  /* �������õİ汾�� */
    VOS_UINT16                          usOplmnListNum;                                       /* �������õ�Oplmn�ĸ��� */
    VOS_UINT8                           ucImsiPlmnListNum;                                    /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           aucReserve[3];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_OPLMN_IMSI_NUM];
    VOS_UINT8                           aucOPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_OPLMN_DATA_EXTEND_LEN];/* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}NAS_MMC_NVIM_USER_CFG_OPLMN_EXTEND_STRU;



typedef struct
{
    VOS_UINT8                           ucImsiPlmnListNum;                      /* ���Ƶ�IMSI�б���� */
    VOS_UINT8                           ucEhplmnListNum;                        /* �û����õ�EHplmn�ĸ��� */
    VOS_UINT8                           aucReserve[2];
    NAS_SIM_FORMAT_PLMN_ID              astImsiPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_IMSI_PLMN_NUM];
    NAS_SIM_FORMAT_PLMN_ID              astEhPlmnList[NAS_MMC_NVIM_MAX_USER_CFG_EHPLMN_NUM];
}NAS_MMC_NVIM_USER_CFG_EHPLMN_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulMcc;                                  /* MCC,3 bytes */
    VOS_UINT32                          ulMnc;                                  /* MNC,2 or 3 bytes */
    VOS_UINT8                           enRat;
    VOS_UINT8                           aucReserve[3];
}NAS_MMC_NVIM_PLMN_WITH_RAT_STRU;



typedef struct
{
    VOS_UINT32                          ulDisabledRatPlmnNum;                   /* ֧�ֽ�ֹ���뼼����PLMN����,����Ϊ0��ʾ��֧�ָ����� */
    NAS_MMC_NVIM_PLMN_WITH_RAT_STRU     astDisabledRatPlmnId[NAS_MML_MAX_DISABLED_RAT_PLMN_NUM];/* ��ֹ���뼼����PLMN��RAT��Ϣ */
}NAS_MMC_NVIM_DISABLED_RAT_PLMN_INFO_STRU;


enum NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_INACTIVE                   = 0,           /* ����δ���� */                     
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BLACK                      = 1,           /* �������������� */                 
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_WHITE                      = 2,           /* �������������� */ 
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8;


enum NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM
{
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_GERAN                   = 0,           /* GERAN */                     
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_UTRAN                   = 1,           /* UTRAN����WCDMA/TDS-CDMA */                 
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_EUTRAN                  = 2,           /* E-UTRAN */ 
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_BUTT
};
typedef VOS_UINT8 NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8;


typedef struct
{
    NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_SWITCH_FLAG_ENUM_UINT8  enSwitchFlag;                                         /*�����Ƿ���Ч�����ܵ�����  */
    VOS_UINT8                                               ucImsiListNum;                                        /*������Ч��SIM����Ŀ(������/������)  */
    VOS_UINT8                                               ucForbidRatNum;                                       /*��ֹRAT����Ŀ  */
    VOS_UINT8                                               aucReserve[1];
    NAS_SIM_FORMAT_PLMN_ID                                  astImsiList[NAS_NVIM_MAX_IMSI_FORBIDDEN_LIST_NUM];        /* SIM���б� (������/������) */
    NAS_MMC_NVIM_PLATFORM_SUPPORT_RAT_ENUM_UINT8            aenForbidRatList[NAS_NVIM_MAX_RAT_FORBIDDEN_LIST_NUM];    /*��ֹ�Ľ��뼼��  */
}NAS_MMC_NVIM_RAT_FORBIDDEN_LIST_STRU;


typedef struct
{
    VOS_UINT8                           ucCsfbEmgCallLaiChgLauFirstFlg;
    VOS_UINT8                           aucRserved[1];
}NAS_MMC_NVIM_CSFB_EMG_CALL_LAI_CHG_LAU_FIRST_CFG_STRU;

typedef struct
{
    VOS_UINT8                           ucPlmnExactlyCompareFlag;
    VOS_UINT8                           aucRsv[3];                         /* ����*/
}NAS_MMC_NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;


typedef struct
{
    VOS_UINT8                           ucHplmnRegisterCtrlFlg;                 /* HPLMNע����Ʊ�� */
    VOS_UINT8                           aucRsv[3];                              /* ���� */
}NAS_MMC_NVIM_HPLMN_REGISTER_CTRL_FLAG_STRU;

typedef struct
{
    VOS_UINT8                                               ucSignThreshold;    /* �źű仯����,��RSSI�仯������ֵ��
                                                                                  �������Ҫ�����ϱ��ź�������ȡֵ0��ʾ����㰴Ĭ��ֵ���� */
    VOS_UINT8                                               ucMinRptTimerInterval;     /* ����ϱ���ʱ��   */
} NAS_NVIM_CELL_SIGN_REPORT_CFG_STRU;


typedef struct
{
    VOS_UINT8                           ucH3gCtrlFlg;                           /* H3G���Ʊ�� */
    VOS_UINT8                           aucRsv[3];                              /* ���� */
}NAS_MMC_NVIM_H3G_CTRL_FLAG_STRU;


typedef struct
{
    VOS_UINT16  usUcs2Customization;
}NAS_MMC_NVIM_UCS2_CUSTOMIZATION_STRU;


typedef struct
{
    VOS_UINT16                          usTc1mLength;
    VOS_UINT16                          usTr1mLength;
    VOS_UINT16                          usTr2mLength;
    VOS_UINT16                          usTramLength;
}SMS_NVIM_TIMER_LENGTH_STRU;



typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucStatusRptGeneralControl;        /* ˽�������Ƿ�����״̬�ϱ� 0:���ϱ���1:�ϱ� */
}NVIM_PRIVATE_CMD_STATUS_RPT_STRU;


typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ����  */
    VOS_UINT8                           ucSpecialRoamFlg;                         /* Vplmn��Hplmn��ͬ������ʱ,�Ƿ�����ص�Hplmn,1:����0:������ */
}NAS_MMC_NVIM_SPECIAL_ROAM_STRU;


typedef struct
{
    VOS_UINT16 usEnhancedHplmnSrchFlg;
}NAS_MMC_NVIM_ENHANCED_HPLMN_SRCH_FLG_STRU;


typedef struct
{
    VOS_UINT8   ucCcbsSupportFlg;
    VOS_UINT8   ucReserve;
}NAS_CC_NVIM_CCBS_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT8   ucT305Len;
    VOS_UINT8   ucT308Len;
    VOS_UINT8   aucReserve[2];
}NAS_CC_NVIM_TIMER_LEN_STRU;


enum NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM
{
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_INACTIVE,      /* ���ܲ���Ч */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_PS,         /* �޸�CS+PS�ľܾ�ԭ��ֵ */                                         
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_CS_ONLY,       /* ���޸�CS��ľܾ�ԭ��ֵ */                                     
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_PS_ONLY,       /* ���޸�PS��ľܾ�ԭ��ֵ */
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_BUTT
};
typedef VOS_UINT8 NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8;


typedef struct
{
    NAS_NVIM_CHANGE_REG_REJ_CAUSE_TYPE_ENUM_UINT8           enChangeRegRejCauCfg;
    VOS_UINT8   ucPreferredRegRejCau_HPLMN_EHPLMN;             /* HPLMN/EHPLMNʱʹ�õľܾ�ԭ��ֵ */
    VOS_UINT8   ucPreferredRegRejCau_NOT_HPLMN_EHPLMN;         /* ��HPLMN/EHPLMNʱʹ�õľܾ�ԭ��ֵ */
    VOS_UINT8   aucReserve[1];
}NAS_NVIM_CHANGE_REG_REJECT_CAUSE_FLG_STRU;


typedef struct
{
   VOS_UINT8                           ucIgnoreAuthRejFlg;
   VOS_UINT8                           ucMaxAuthRejNo;
   VOS_UINT8                           aucReserved[2];
}NAS_MMC_NVIM_IGNORE_AUTH_REJ_CFG_STRU;


typedef struct
{
    VOS_UINT8 ucStatus;
    VOS_UINT8 ucReserved1;
    VOS_UINT8 aucE5GwMacAddr[18];
}NAS_NV_GWMAC_ADDR_STRU;


typedef struct
{
    VOS_UINT8 aucE5_RoamingWhiteList_Support_Flg[2];
}NAS_NVIM_E5_ROAMING_WHITE_LIST_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT32 ulNDIS_DIALUP_ADDRESS;
}NAS_NVIM_NDIS_DIALUP_ADDRESS_STRU;


typedef struct
{
    VOS_UINT8 ucBreOnTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreOffTime; /*Range:[0,7]*/
    VOS_UINT8 ucBreRiseTime; /*Range:[0,5]*/
    VOS_UINT8 ucBreFallTime; /*Range:[0,5]*/
}NAS_NVIM_NV_BREATH_LED_STR_STRU;


typedef struct
{
VOS_UINT8  aucwlAuthMode[16];
VOS_UINT8  aucBasicEncryptionModes[5];
VOS_UINT8  aucWPAEncryptionModes[5];
VOS_UINT8  aucwlKeys1[27];
VOS_UINT8  aucwlKeys2[27];
VOS_UINT8  aucwlKeys3[27];
VOS_UINT8  aucwlKeys4[27];
VOS_UINT32 ulwlKeyIndex;
VOS_UINT8  aucwlWpaPsk[65];
VOS_UINT8  ucwlWpsEnbl;
VOS_UINT8  ucwlWpsCfg;
VOS_UINT8  ucReserved;
}NAS_NVIM_NV_WIFI_KEY_STRU;


typedef struct
{
VOS_UINT8 aucPRIVersion[32];
VOS_UINT8 aucReserve[32];
}NAS_NVIM_NV_PRI_VERSION_STRU;


typedef struct
{
    VOS_UINT16     usSysAppConfigType;
}NAS_NVIM_SYSTEM_APP_CONFIG_STRU;


typedef struct
{
    VOS_UINT8 aucNetworkCapability[NV_ITEM_NET_CAPABILITY_MAX_SIZE];
}NAS_MMC_NVIM_NETWORK_CAPABILITY_STRU;


typedef struct
{
    VOS_UINT16 usAutoattachFlag;
}NAS_NVIM_AUTOATTACH_STRU;


typedef struct
{
    VOS_UINT16 usSelPlmnMode;
}NAS_NVIM_SELPLMN_MODE_STRU;


typedef struct
{
    VOS_UINT8   aucAccessMode[2];
}NAS_MMA_NVIM_ACCESS_MODE_STRU;


typedef struct
{
    VOS_UINT8   ucMsClass;
    VOS_UINT8   ucReserved;
}NAS_NVIM_MS_CLASS_STRU;


typedef struct
{
    VOS_UINT16  usRfAutoTestFlg;
}NAS_MMA_NVIM_RF_AUTO_TEST_FLAG_STRU;


typedef struct
{
    VOS_UINT8   ucHplmnTimerLen;
    VOS_UINT8   ucReserved;
}NAS_NVIM_HPLMN_FIRST_TIMER_STRU;


typedef struct
{
    VOS_UINT8   aucSupported3GppRelease[NAS_MMC_NVIM_SUPPORTED_3GPP_RELEASE_SIZE];
}NAS_MMC_NVIM_SUPPORT_3GPP_RELEASE_STRU;


typedef struct
{
    VOS_UINT8   ucValid;
    VOS_UINT8   aucImsi[NAS_MMC_NVIM_MAX_IMSI_LEN];
}NAS_MMC_NVIM_LAST_IMSI_STRU;


typedef struct
{
    VOS_UINT8   aucRoamingBroker[2];
}NAS_MMA_NVIM_ROAMING_BROKER_STRU;


typedef struct
{
    VOS_UINT16  usUseSingleRplmnFlag;
}NAS_MMC_NVIM_USE_SINGLE_RPLMN_STRU;

/* en_NV_Item_EquivalentPlmn 8215 */

typedef struct
{
    VOS_UINT8    ucMcc[NVIM_MAX_MCC_SIZE];
    VOS_UINT8    ucMnc[NVIM_MAX_MNC_SIZE];
}NVIM_PLMN_VALUE_STRU;


typedef struct
{
    VOS_UINT8             ucCount;
    NVIM_PLMN_VALUE_STRU  struPlmnList[NVIM_MAX_EPLMN_NUM];
    VOS_UINT8             aucReserve[3];   /*NV����صĽṹ�壬��4�ֽڷ�ʽ�£����ֶ�����ն�*/
}NVIM_EQUIVALENT_PLMN_LIST_STRU;

/*en_NV_Item_Support_Freqbands 8229*/
/*
NVIM_UE_SUPPORT_FREQ_BAND_STRU�ṹ˵��:
usWcdmaBand��usGsmBand��Bitλ��ʾ�û����õ�Ƶ�Σ�bit1����Ƶ��I,bit2����Ƶ��II,
��������,����λΪ1,��ʾ֧�ָ�Ƶ��.�±��Ǳ���λ��Ƶ�ζ�Ӧ��ϵ:
-------------------------------------------------------------------------------
        bit8       bit7      bit6     bit5    bit4     bit3      bit2     bit1
-------------------------------------------------------------------------------
WCDMA   900(VIII)  2600(VII) 800(VI)  850(V)  1700(IV) 1800(III) 1900(II) 2100(I) oct1
        spare      spare     spare    spare   spare    spare     spare   J1700(IX)oct2
-------------------------------------------------------------------------------
GSMƵ�� 1900(VIII) 1800(VII) E900(VI) R900(V) P900(IV) 850(III)  480(II)  450(I)  oct3
        spare      spare     spare    spare   spare    spare     spare    700(IX) oct4
-------------------------------------------------------------------------------
aucUeSupportWcdmaBand��aucUeSupportGsmBand�������ʾUE֧�ֵ�Ƶ��,���Դ洢˳���
�Ⱥ��ʾƵ������˳��,��0xff��ʾ��Ч.

����:
oct1-oct4�ֱ��ǣ�0x03,0x00,0x7B,0x00
   ������û�����Ƶ��Ϊ��W��WCDMA-I-2100, WCDMA-II-1900
                         G��850(III),P900(IV),R900(V),E900(VI),1800(VII)
oct5-oct16�ֱ���:2,5,1,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
   �����UE֧��WƵ��I,II,V,����˳����:II,V,I.
oct17-oct28�ֱ���:4,5,8,7,6,3,0xff,0xff,0xff,0xff,0xff,0xff
   �����UE֧��GƵ��III,IV,V,VI,VII,VIII,����˳����:IV,V,VIII,VII,VI,III.
*/

typedef struct
{
    VOS_UINT32                  ulWcdmaBand;
    VOS_UINT32                  ulGsmBand;
    VOS_UINT8                   aucUeSupportWcdmaBand[NVIM_MAX_FDD_FREQ_BANDS_NUM];
    VOS_UINT8                   aucUeSupportGsmBand[NVIM_MAX_FDD_FREQ_BANDS_NUM];
    VOS_UINT8                   aucReserved[24];        /* Ϊ��֤nv����һ�±��� */
}NVIM_UE_SUPPORT_FREQ_BAND_STRU;

/*en_NV_Item_Roam_Capa 8266*/

typedef struct
{
    VOS_UINT8                               ucRoamFeatureFlg;                   /*��¼���������Ƿ񼤻�,VOS_FALSE:������,VOS_TRUE:����*/
    VOS_UINT8                               ucRoamCapability;                   /*��¼�û����õ���������*/
}NAS_NVIM_ROAM_CFG_INFO_STRU;

/*en_NV_Item_CustomizeService 8271*/

typedef struct
{
    VOS_UINT32                          ulStatus;           /*�Ƿ񼤻0�����1���� */
    VOS_UINT32                          ulCustomizeService; /*�ն�˵������1��byte��Ϊ��û�пն��������4byte����3byte����*/
}NAS_NVIM_CUSTOMIZE_SERVICE_STRU;

/*en_NV_Item_RPlmnWithRat 8275*/

typedef struct
{
    NAS_NVIM_PLMN_ID_STRU               stGRplmn;                               /* G RPLMN��Ϣ */
    NAS_NVIM_PLMN_ID_STRU               stWRplmn;                               /* W RPLMN��Ϣ*/
    VOS_UINT8                           ucLastRplmnRat;                         /* �ϴιػ�ʱפ������Ľ��뼼��0:GSM;1:WCDMA;0xFF:��Чֵ */
    VOS_UINT8                           ucLastRplmnRatEnableFlg;                /* 0:NV δ����; 1:NV���� */
    VOS_UINT8                           aucReserved[2];                          /* ���� */
}NAS_NVIM_RPLMN_WITH_RAT_STRU;


typedef struct
{
    VOS_UINT8                            ucStatus;                              /* 0:NV δ����; 1:NV ���� */
    VOS_UINT8                            ucReserve;                             /* ����δ�� */
    VOS_UINT16                           usSrchHplmnTimerValue;                 /* VPLMN�·��״���HPLMNʱ��,��λ:���� */

}NAS_MMC_NVIM_SEARCH_HPLMN_TIMER_STRU;

/*en_NV_Item_EFust_Service_Cfg 8285*/

typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV���Ƿ񼤻�0��δ���1������ */
    VOS_UINT8                           ucForbidReg2GNetWork;                   /* 0��EFust GSM�����־������ȥʹ�ܡ��������������EFust 27��38������GSM���롣
                                                                                   �������ö�������UE����SIM���е�EFust 27��38λ��ȷ���Ƿ�����GSM���룬
                                                                                   ���EFUST�ļ���ֹ����λ��ͬʱ����Ϊ0�������ֹGSM����ע�ᣬ����GSM���Խ��롣
                                                                                   ע�⣺SIM���в�����EFust 27��38λ����˸ù��ܽ����USIM����Ч��1��EFust GSM�����־������ʹ�� */
    VOS_UINT8                           ucForbidSndMsg;                         /* 0��EFust���ŷ��ͱ�־������ȥʹ�ܡ��������������EFust 10��12������SMS���͡�
                                                                                   1��EFust���ŷ��ͱ�־������ʹ�ܡ�NV���ö�������UE����SIM����EFUST��10��12λ��
                                                                                   ȷ���Ƿ��ֹ���ŷ���,�����ֹ����λ��ͬʱ����Ϊ0�������ֹ����SMS�����򣬶��ſ��Է��͡�*/
    VOS_UINT8                           ucReserved[13];
}NAS_MMC_NVIM_EFUST_SERVICE_CFG_STRU;

/*en_NV_Item_UE_MSCR_VERSION 8289*/

typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucUeMscrVersion;                        /* �ն��ϱ���SGSN�汾 */
}NAS_MMC_NVIM_MSCR_VERSION_STRU;

/*en_NV_Item_UE_SGSNR_VERSION 8290*/

typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucUeSgsnrVersion;                       /* �ն��ϱ���SGSN�汾 */
}NAS_MMC_NVIM_SGSNR_VERSION_STRU;

/*en_NV_Item_SteeringofRoaming_SUPPORT_CTRL 8292*/

typedef struct
{
    VOS_UINT8                           ucStatus;                               /* NV�Ƿ񼤻��־, 0: �����1: ���� */
    VOS_UINT8                           ucCsRejSearchSupportFlg;                /* vodafone��������������,CS��ʧ���Ĵκ��·���������,VOS_FALSE:��֧��,VOS_TRUE:֧�� */
}NAS_MMC_NVIM_CS_REJ_SEARCH_SUPPORT_STRU;

/*en_NV_Item_Max_Forb_Roam_La 8320*/

typedef struct
{
    VOS_UINT8                           ucMaxForbRoamLaFlg;                     /* NV�����õ�����ֹLA�����Ƿ���Ч: VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucMaxForbRoamLaNum;                     /* NV�����õ�����ֹLA���� */
}NAS_MMC_NVIM_MAX_FORB_ROAM_LA_STRU;

/*en_NV_Item_Default_Max_Hplmn_Srch_Peri 8321*/

typedef struct
{
    VOS_UINT8                           ucDefaultMaxHplmnPeriFlg;               /* Ĭ������HPLMN���������Ƿ���Ч��־,VOS_TRUE:valid;VOS_FALSE:INVALID */
    VOS_UINT8                           ucDefaultMaxHplmnTim;                   /* �û����Զ���Ĭ�ϵ�����HPLMN�������� */
}NAS_MMC_NVIM_DEFAULT_MAX_HPLMN_PERIOD_STRU;

/*en_NV_Item_USSD_Apha_To_Ascii 8327*/
/*����USSDת���ַ���*/

typedef struct
{
    VOS_UINT8                       ucStatus;            /*�Ƿ񼤻0�����1���� */
    VOS_UINT8                       ucAlphaTransMode;    /* �ַ���ת��*/
}NAS_SSA_NVIM_ALPHA_to_ASCII_STRU;

/*en_NV_Item_Register_Fail_Cnt 8338*/

typedef struct
{
    VOS_UINT8                           ucNvActiveFlag;                         /* ��ǰNV���Ƿ񼤻� */
    VOS_UINT8                           ucRegFailCnt;                           /* NV�����õ�ע��ʧ�ܵĴ�����Ĭ��ֵΪ2����ע��ʧ�����κ��������� */
}NAS_MMC_NVIM_REG_FAIL_CNT_STRU;

/*en_NV_Item_CREG_CGREG_CI_Four_Byte_Rpt 8345*/
/* VDF����: CREG/CGREG����<CI>���Ƿ���4�ֽ��ϱ���NV����ƽṹ�� */

typedef struct
{
    VOS_UINT8   ucStatus;                        /* 1: NV��Ч��־λ��0����Ч */
    VOS_UINT8   ucCiBytesRpt;                    /* <CI>���ϱ��ֽ�����־��0��2�ֽ��ϱ�, 1��4�ֽ��ϱ� */
}NAS_NV_CREG_CGREG_CI_FOUR_BYTE_RPT_STRU;


typedef struct
{
    VOS_UINT8                           ucEnableFlg;                            /* ���ű����Ƿ�ʹ�� VOS-TRUE:���ű���֧�� VOS_FALSE:���ű��ܲ�֧�� */
    VOS_UINT8                           aucReserve[1];
}NAS_MMC_NVIM_DAIL_REJECT_CFG_STRU;

/* en_NV_Item_NDIS_DHCP_DEF_LEASE_TIME 8344 */
typedef struct
{
    VOS_UINT32                          ulDhcpLeaseHour;    /*Range:[0x1,0x2250]*/
}NDIS_NV_DHCP_LEASE_HOUR_STRU;

typedef struct
{
    VOS_UINT32                          ulIpv6Mtu;          /*Range:[1280,65535]*/
}NDIS_NV_IPV6_MTU_STRU;


typedef struct
{
    VOS_UINT8                           ucStatus;
    VOS_UINT8                           ucReserved;
}NAS_NVIM_CCALLSTATE_RPT_STATUS_STRU;


typedef struct
{
   VOS_UINT8                            ucPlmnExactlyCompareFlag;               /* PLMN�Ƚ��Ƿ���о�ȷ�Ƚϵķ�ʽ�ı�� */
   VOS_UINT8                            aucRsv[3];                              /* ����λ */
}NVIM_PLMN_EXACTLY_COMPARE_FLAG_STRU;


enum PLATFORM_RAT_TYPE_ENUM
{
    PLATFORM_RAT_GSM,                                                       /*GSM���뼼�� */
    PLATFORM_RAT_WCDMA,                                                     /* WCDMA���뼼�� */
    PLATFORM_RAT_LTE,                                                       /* LTE���뼼�� */
    PLATFORM_RAT_TDS,                                                       /* TDS���뼼�� */
    PLATFORM_RAT_BUTT
};
typedef VOS_UINT16 PLATFORM_RAT_TYPE_ENUM_UINT16;

#define PLATFORM_MAX_RAT_NUM            (7)                                    /* ���뼼�����ֵ */


typedef struct
{
    VOS_UINT16                           usRatNum;                              /* ���뼼������Ŀ*/
    PLATFORM_RAT_TYPE_ENUM_UINT16        aenRatList[PLATFORM_MAX_RAT_NUM];  /* ���뼼�� */
}PLATAFORM_RAT_CAPABILITY_STRU;

/*en_NV_Item_Rplmn 8216*/

typedef struct
{
    VOS_UINT8                           aucRplmnInfo[56];
}NAS_NVIM_RPLMN_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucSvlteSupportFlag;                     /* SVLTE�����Ƿ�֧��:0-��֧�֣�1-֧�� */
    VOS_UINT8                           aucReserved[3];                         /* ���� */
}SVLTE_SUPPORT_FLAG_STRU;



typedef struct
{
    VOS_UINT8                           ucNvimActiveFlag;                       /* 0: nv��δ���1:nv��� */
    VOS_UINT8                           ucCsPsMode1EnableLteTimerLen;           /* 1)cs ps mode1 L����ע��eps only�ɹ�cs����#16/#17/#22������������disable lteʱ����enable lte��ʱ��ʱ��
                                                                                   2)cs ps mode1 L����ע��cs eps��ʧ��ԭ��ֵother cause ������������disable lte����enable lte��ʱ��ʱ��,��λ:���ӣ� nv���ʱ���Ϊ0Ĭ��54���� */
    VOS_UINT8                           ucCsfbEmgCallEnableLteTimerLen;         /* L�½��������޷�����csfb��gu��ͨ��������gu����disable lte����enable lte��ʱ��ʱ������λ:���ӣ� nv���ʱ���Ϊ0Ĭ��5���� */
    VOS_UINT8                           ucReserved;
}NAS_MMC_NVIM_ENABLE_LTE_TIMER_LEN_STRU;



typedef struct
{
    VOS_UINT8                                               ucIsrSupport;       /* ISR ???? */
    VOS_UINT8                                               ucReserve1;
} NAS_NVIM_ISR_CFG_STRU;



typedef struct
{
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMtFlg;           /* Csfb mt�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           ucIsRauNeedFollowOnCsfbMoFlg;           /* Csfb mo�����У�RAU�Ƿ���Ҫ��follow on���:0-����Ҫ��1-��Ҫ */
    VOS_UINT8                           aucReserved[2];                         /* ���� */
}NAS_MMC_CSFB_RAU_FOLLOW_ON_FLAG_STRU;


typedef struct
{
   VOS_UINT16                           usSolutionMask;/*����ͨ������Modem����Ϣ��������ǿ�͵��������ԣ�Bitλ���Ƹ����������ԣ�bitn=0����n�����Թرգ�bitn=1����n�����Կ�����
                                                         Ŀǰֻ��bit0��bit1 ��Ч��
                                                         BIT0������˫Modem��ͨ����һModem��PLMN��Ϣ����FDD�����Ƿ������Ĳ����Ƿ�������
                                                         BIT1��ͨ��Modem1��GSM�ϱ���L��TDS������Ϣ, Modem0��֧��GSM������£�T/L�������ܹ����ݴ��ݵ�����Ƶ�����������TDS/LTE��
                                                               ���Modem1���ݹ�����������Ϣ�����ڵ�����£�Ҳ��ͨ����ʷƵ��֧��NCELL������������������Ƶ����ucSolution2NcellSearchTimer������
                                                         BIT2~BIT15:Ԥ��*/
   VOS_UINT8                            ucSolution2NcellQuickSearchTimer;       /*����Ƶ������������Ե�һ�׶�ʱ��������λ�룩��*/

   VOS_UINT8                            ucSolution2NcellQuickSearchTimer2;      /* ����Ƶ������������ԵĶ��׶�ʱ��������λ�룩��*/
   VOS_UINT8                            aucAdditonCfg[4];
}NV_DSDA_PLMN_SEARCH_ENHANCED_CFG_STRU;



typedef struct
{
    VOS_UINT8   ucRelFlg;
    VOS_UINT8   ucReserve;
}NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU;


typedef struct
{
    VOS_UINT32                          ulWband;                                /* ֧�ֵ�WCDMA����ͨ· */
    VOS_UINT32                          ulWbandExt;                             /* ֧�ֵ�WCDMA����ͨ·��չ�ֶ� */
    VOS_UINT32                          ulGband;                                /* ֧�ֵ�GSM����ͨ· */
}NAS_NVIM_WG_RF_MAIN_BAND_STRU;



typedef struct
{
    VOS_UINT8                           ucImsVoiceInterSysLauEnable;           /* ISR�������ϵͳ��L�任��GU��LAIδ�ı䣬�Ƿ���Ҫǿ��LAU */
    VOS_UINT8                           ucImsVoiceMMEnable;         /* IMS�ƶ��Թ��� NV */
    VOS_UINT8                           aucReserved[2];             /* ���� */
}NAS_MMC_IMS_VOICE_MOBILE_MANAGEMENT;


typedef struct
{
    VOS_UINT8                           ucLDisabledRauUseLInfoFlag;             /* l disabled��rau�Ƿ���Ҫ��l��ȡ��ȫ�����Ļ�gutiӳ����Ϣ��vos_true:��Ҫ��ȡ��vos_false:�����ȡ*/
    VOS_UINT8                           ucReserved[3];
}NAS_MMC_LTE_DISABLED_USE_LTE_INFO_FLAG_STRU;



typedef struct
{
    VOS_UINT8                           ucActiveFlg;                            /* �Ƿ񼤻�� */
    VOS_UINT8                           ucCsOnlyDataServiceSupportFlg;          /* PSע�ᱻ��ֹ����£��Ƿ���������ҵ�񴥷�ע��ı�־ */
}NAS_MML_CS_ONLY_DATA_SERVICE_SUPPORT_FLG_STRU;

typedef struct
{
    VOS_UINT8                           ucActiveFLg;                             /* �ö�ʱ���Ƿ�ʹ�� */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulFirstSearchTimeLen;                   /* high prio rat timer��ʱ����һ�ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulFirstSearchTimeCount;                 /* high prio rat timer��ʱ����һ��ʱ���������������� */
    VOS_UINT32                          ulNonFirstSearchTimeLen;                /* high prio rat timer��ʱ�����״ε�ʱ�� ��λ:�� */
    VOS_UINT32                          ulRetrySearchTimeLen;                   /* high prio rat �ѱ���ֹ���������������Ե�ʱ�� ��λ:��*/
}NAS_MMC_NVIM_HIGH_PRIO_RAT_HPLMN_TIMER_CFG_STRU;




typedef struct
{
    VOS_UINT8                           ucUltraFlashCsfbSupportFLg;                 /* �Ƿ�֧��ultra flash csfb */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_ULTRA_FLASH_CSFB_SUPPORT_FLG_STRU;


typedef struct
{
    VOS_UINT8                           uc3GPP2UplmnNotPrefFlg;                    /* �Ƿ���3GPP2 pref plmn */
    VOS_UINT8                           aucRsv[3];
}NAS_MMC_NVIM_3GPP2_UPLMN_NOT_PREF_STRU;


typedef struct
{
    VOS_UINT8                           ucHighPrioRatPlmnSrchFlg;                  /* �Ƿ��������ȼ����뼼������ */
    VOS_UINT8                           aucReserved1[3];
}NAS_MMC_NVIM_SYSCFG_TRIGGER_PLMN_SEARCH_CFG_STRU;



typedef struct
{
    VOS_UINT8                           ucHplmnInEplmnDisplayHomeFlg;
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    VOS_UINT8                           ucReserved3;
}NAS_MMC_NVIM_ROAM_DISPLAY_CFG_STRU;

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
