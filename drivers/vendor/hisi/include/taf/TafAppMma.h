

#ifndef __TAF_APP_MMA_H__
#define __TAF_APP_MMA_H__

#include "TafTypeDef.h"
/*#include "NasCommDef.h" */
#include "UsimPsInterface.h"

#include  "AtMnInterface.h"
#include "TafNvInterface.h"

#include "AppVcApi.h"
#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
#include "siapppih.h"
#endif /*FEATURE_ON == MBB_FEATURE_VSIM_HUK*/

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define TAF_MMA_PNN_INFO_MAX_NUM                           (50)                /* ATģ��Ҫ��MMAһ���ϱ���PNN���� */

/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */
#define TAF_MMA_PLMN_MNC_TWO_BYTES                          (2)                 /* MNC����󳤶�Ϊ3λ��ʵ�ʳ���Ϊ2λ��3λ����ѡ */

#define TAF_MMA_COPN_PLMN_MAX_NUM                           (50)                /* ATģ��Ҫ��MMAһ���ϱ�����Ӫ�̸��� */

#define TAF_MMA_NET_SCAN_MAX_FREQ_NUM                       (20)

#define TAF_MMA_REG_MAX_PLMN_NUM                            (8)
#define TAF_MMA_REG_MAX_CELL_NUM                            (8)

/*****************************************************************************
 ö����    : TAF_MMA_PLMN_MNC_DIGIT_MASK_ENUM
 �ṹ˵��  : ��Ӫ����ϢPLMN�����ָ�ʽMNC���ֶε�����
             0: DRV_AGENT_TSELRF_SET_ERROR_NO_ERROR ���ò����ɹ���
             1: DRV_AGENT_TSELRF_SET_ERROR_LOADDSP  ���ò���ʧ�ܣ�
*****************************************************************************/
enum TAF_MMA_PLMN_MNC_DIGIT_MASK_ENUM
{
    TAF_MMA_PLMN_MNC_DIGIT1_MASK = 0x00f,
    TAF_MMA_PLMN_MNC_DIGIT2_MASK = 0x0f0,
    TAF_MMA_PLMN_MNC_DIGIT3_MASK = 0xf00,
    TAF_MMA_PLMN_MNC_DIGIT_MASK_BUTT
};

enum TAF_MMA_PLMN_MNC_DIGIT_OFFSET_ENUM
{
    TAF_MMA_PLMN_MNC_DIGIT1_OFFSET = 0,
    TAF_MMA_PLMN_MNC_DIGIT2_OFFSET = 4,
    TAF_MMA_PLMN_MNC_DIGIT3_OFFSET = 8,
    TAF_MMA_PLMN_MNC_DIGIT_OFFSET_BUTT
};

enum TAF_MMA_PLMN_MCC_DIGIT_MASK_ENUM
{
    TAF_MMA_PLMN_MCC_DIGIT1_MASK = 0x00f,
    TAF_MMA_PLMN_MCC_DIGIT2_MASK = 0x0f0,
    TAF_MMA_PLMN_MCC_DIGIT3_MASK = 0xf00,
    TAF_MMA_PLMN_MCC_DIGIT_MASK_BUTT
};

enum TAF_MMA_PLMN_MCC_DIGIT_OFFSET_ENUM
{
    TAF_MMA_PLMN_MCC_DIGIT1_OFFSET = 0,
    TAF_MMA_PLMN_MCC_DIGIT2_OFFSET = 4,
    TAF_MMA_PLMN_MCC_DIGIT3_OFFSET = 8,
    TAF_MMA_PLMN_MCC_DIGIT_OFFSET_BUTT
};
/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */

#define NAS_MM_INFO_IE_NULL             (0x00)
#define NAS_MM_INFO_IE_LTZ              0x01        /* Local time zone */
#define NAS_MM_INFO_IE_UTLTZ            0x02        /* Universal time and local time zone */
#define NAS_MM_INFO_IE_LSA              0x04        /* LSA Identity */
#define NAS_MM_INFO_IE_DST              0x08        /* Network Daylight Saving Time */
#define NAS_MM_INFO_IE_NETWORKFULLNAME  0x10        /* Full name for network */
#define NAS_MM_INFO_IE_NETWORKSHORTNAME 0x20        /* Short name for network */

/* ����IMSI���ȶ��� */
#define   NAS_MAX_IMSI_LENGTH           (9)

/* Added by f62575 for AT Project��2011-10-04,  Begin*/
/* +CSQLVL ��صĺ궨�� */
#define AT_CSQLVL_MAX_NUM               (3)
#define AT_CSQLVL_LEVEL_0               (0)
#define AT_CSQLVL_LEVEL_1               (20)
#define AT_CSQLVL_LEVEL_2               (40)
#define AT_CSQLVL_LEVEL_3               (60)
/* Added by f62575 for AT Project��2011-10-04,  End*/

#define DRVAGENT_GPIOPL_MAX_LEN          (20)
#define TAF_MAX_SIM_LOCK_RANGE_NUM      (20)

#define TAF_CDROM_VERSION_LEN         128

/*Ӳ���汾����󳤶�*/
#define DRV_AGENT_MAX_HARDWARE_LEN            (31)

#define TAF_MAX_REVISION_ID_LEN     (31)

#define TAF_MAX_MODEL_ID_LEN     (31)

#define TAF_MAX_HARDWARE_LEN            (31)


#define PRODUCTION_CARD_TYPE   "WCDMA"

#define TAF_UTRANCTRL_UTRAN_MODE_FDD    (0)
#define TAF_UTRANCTRL_UTRAN_MODE_TDD    (1)

/* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
/* Added by L60609 for AT Project��2011-10-05,  Begin*/
#define AT_HS_PARA_MAX_LENGTH           (9)
/* Added by L60609 for AT Project��2011-10-05,  End*/
/* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

#define TAF_MMA_UTRA_BLER_INVALID       (99)
#define TAF_MMA_RSSI_LOWER_LIMIT        (-114)
#define TAF_MMA_UTRA_RSCP_UNVALID       (-140)

#define TAF_MMA_RPT_CFG_MAX_SIZE         (8)

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
 ö����    : AT_MMA_MSG_TYPE_ENUM
 �ṹ˵��  : AT��MMA��Ϣ�ӿ�ö��
*****************************************************************************/
enum AT_MMA_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                      /*��ϢID*/      /* ��ע */
    /* AT����MMA����Ϣ */


    /* MMA����AT����Ϣ */
    AT_MMA_OM_MAINTAIN_INFO_IND         = 0x0001,
    AT_MMA_USIM_STATUS_IND              = 0x0003,
    AT_MMA_CRPN_QUERY_RSP               = 0x0005,
    AT_MMA_CMM_SET_CMD_RSP              = 0x0007,

    AT_MMA_CIPHER_INFO_QUERY_CNF        = 0x0009,
    AT_MMA_LOCATION_INFO_QUERY_CNF      = 0x000b,
/* Added by f62575 for B050 Project, 2012-2-3, Begin   */
    AT_MMA_SIMLOCK_STAUS_QUERY_CNF      = 0x000d,
/* Added by f62575 for B050 Project, 2012-2-3, End   */

    AT_MMA_AC_INFO_QUERY_CNF            = 0x000f,

    AT_MMA_CERSSI_INFO_QUERY_CNF        = 0x0010,

    /* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */
    AT_MMA_COPN_INFO_QUERY_CNF          = 0x0013,
    /* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */

    AT_MMA_SIM_INSERT_RSP          = 0x0015,
    AT_MMA_CPOL_INFO_QUERY_CNF          = 0x0017,

    AT_MMA_MSG_TYPE_BUTT,
};
typedef VOS_UINT32 AT_MMA_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : TAF_MMA_MSG_TYPE_ENUM
 �ṹ˵��  : MMA��Ϣ�ӿ�ö��
*****************************************************************************/
enum TAF_MMA_MSG_TYPE_ENUM
{
    ID_TAF_MMA_MSG_TYPE_BEGIN           = AT_MMA_MSG_TYPE_BUTT,
    ID_TAF_MMA_PHONE_MODE_SET_REQ       ,
    ID_TAF_MMA_PHONE_MODE_SET_CNF       ,
    ID_TAF_MMA_SYS_CFG_SET_REQ          ,
    ID_TAF_MMA_SYS_CFG_SET_CNF          ,
    ID_TAF_MMA_ACQ_BEST_NETWORK_REQ    ,
    ID_TAF_MMA_ACQ_BEST_NETWORK_CNF     ,
    ID_TAF_MMA_REG_REQ                  ,
    ID_TAF_MMA_REG_CNF                  ,
    ID_TAF_MMA_DETACH_REQ               ,
    ID_TAF_MMA_DETACH_CNF               ,
    ID_TAF_MMA_POWER_SAVE_REQ           ,
    ID_TAF_MMA_POWER_SAVE_CNF           ,
    ID_TAF_MMA_SERVICE_STATUS_IND       ,
    ID_TAF_MMA_ACQ_IND                  ,
    ID_TAF_MMA_SYS_INFO_IND             ,
    ID_TAF_MMA_SIM_STATUS_IND           ,
#if(FEATURE_ON == MBB_FEATURE_SBM_SLEEPMODE)
    ID_APS_NDSFLOW_REPORT_INFO_IND      ,
#endif/*MBB_FEATURE_SBM_SLEEPMODE*/
#if (FEATURE_ON == MBB_FEATURE_FAKE_ON_OFF)
    ID_TAF_MMA_CFUN_SIM_STATUS_IND,
#endif/*FEATURE_ON == MBB_FEATURE_FAKE_ON_OFF*/
    ID_TAF_MMA_MSG_TYPE_BUTT
};
typedef VOS_UINT32 TAF_MMA_MSG_TYPE_ENUM_UINT32;


enum TAF_PH_RAT_TYPE_ENUM
{
    TAF_PH_RAT_GSM,                                                             /* GSM���뼼�� */
    TAF_PH_RAT_WCDMA,                                                           /* WCDMA���뼼�� */
    TAF_PH_RAT_LTE,                                                             /* LTE���뼼�� */
    TAF_PH_RAT_BUTT
};
typedef VOS_UINT8 TAF_PH_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
/* Added by L60609 for AT Project��2011-10-05,  Begin*/
/* AT����MN_CALLBACK_CMD_CNF�¼�ʱ��ʹ�õ����ݽṹ */
typedef struct
{
    MN_CLIENT_ID_T              clientId;
    MN_OPERATION_ID_T           opId;
    TAF_UINT8                   ucRsv;
    TAF_UINT32                  ulErrorCode;
}AT_CMD_CNF_EVENT;
/* Added by L60609 for AT Project��2011-10-05,  End*/
/* Modified by l60609 for DSDA Phase III, 2013-3-4, End */


/*****************************************************************************
 ö����    : AT_MMA_USIM_STATUS_IND_STRU
 �ṹ˵��  : AT��MMA AT_MMA_USIM_STATUS_IND��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgName;
    USIMM_CARD_TYPE_ENUM_UINT32     enCardType;                     /* ������:SIM��USIM��ROM-SIM  */
    USIMM_CARD_SERVIC_ENUM_UINT32   enCardStatus;                   /* ��״̬*/
    VOS_UINT8                       aucIMSI[NAS_MAX_IMSI_LENGTH];   /* IMSI��*/
    VOS_UINT8                       ucIMSILen;                      /* IMSI���� */
    VOS_UINT8                       ucRsv[2];
}AT_MMA_USIM_STATUS_IND_STRU;

/* Added by f62575 for B050 Project, 2012-2-3, Begin   */
/*****************************************************************************
 ö����    : AT_MMA_SIMLOCK_STATUS_STRU
 �ṹ˵��  : AT��MMA AT_MMA_SIMLOCK_STATUS_STRU��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgName;
    AT_APPCTRL_STRU                 stAtAppCtrl;
    VOS_BOOL                        bSimlockEnableFlg;
}AT_MMA_SIMLOCK_STATUS_STRU;
/* Added by f62575 for B050 Project, 2012-2-3, end   */


enum  TAF_MMA_CELL_RESTRICTION_TYPE_ENUM
{
    TAF_MMA_CELL_RESTRICTION_TYPE_NONE                   = 0,                           /* ��ǰС���������κ�ҵ�� */
    TAF_MMA_CELL_RESTRICTION_TYPE_NORMAL_SERVICE         = 1,                           /* ��ǰС����������ҵ�� */
    TAF_MMA_CELL_RESTRICTION_TYPE_EMERGENCY_SERVICE      = 2,                           /* ��ǰС�����ƽ���ҵ�� */
    TAF_MMA_CELL_RESTRICTION_TYPE_ALL_SERVICE            = 3,                           /* ��ǰС����������ҵ��ͽ���ҵ�� */
    TAF_MMA_CELL_RESTRICTION_TYPE_BUTT
};
typedef VOS_UINT8   TAF_MMA_CELL_RESTRICTION_TYPE_ENUM_UINT8;


typedef struct
{
    TAF_UINT8                                   ucSrvDomain;                                    /* ������ 0:CS,1:ps */
    TAF_MMA_CELL_RESTRICTION_TYPE_ENUM_UINT8    enCellAcType;                                   /* С���������� */
    VOS_UINT8                                   ucRestrictRegister;                             /* �Ƿ�����ע�� */
    VOS_UINT8                                   ucRestrictPagingRsp;                            /* �Ƿ�������ӦѰ�� */
}TAF_MMA_CELL_AC_INFO_STRU;


typedef struct
{
    VOS_UINT8                           aucRsv[4];
}TAF_MMA_AC_INFO_QUERY_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                  ulMsgName;
    VOS_UINT32                                  ulRslt;                                 /* ��� */
    AT_APPCTRL_STRU                             stAtAppCtrl;
    TAF_MMA_CELL_AC_INFO_STRU                   stCellCsAcInfo;                         /* ��ǰС��CS��Ľ����ֹ��Ϣ */
    TAF_MMA_CELL_AC_INFO_STRU                   stCellPsAcInfo;                         /* ��ǰС��ps��Ľ����ֹ��Ϣ */
}TAF_MMA_AC_INFO_QUERY_CNF_STRU;

/*****************************************************************************
 ö����    : MN_PH_CSQLVLEXT_BER_VALUE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CSQLVLEXT����BER����ֵö���б�Ŀǰ�汾��֧��BER������ѯ��ֱ�ӷ���99
*****************************************************************************/
enum MN_PH_CSQLVLEXT_BER_VALUE_ENUM
{
    MN_PH_CSQLVLEXT_BER_VALUE_99        = 99,
    MN_PH_CSQLVLEXT_BER_VALUE_BUTT
};
typedef VOS_UINT8 MN_PH_CSQLVLEXT_BER_VALUE_ENUM_UINT8;


/*****************************************************************************
 ö����    : MN_PH_CSQLVLEXT_RSSILV_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CSQLVLEXT����RSSILV�źŸ�������ö���б�
*****************************************************************************/
enum MN_PH_CSQLVLEXT_RSSILV_ENUM
{
    MN_PH_CSQLVLEXT_RSSILV_0,
    MN_PH_CSQLVLEXT_RSSILV_1,
    MN_PH_CSQLVLEXT_RSSILV_2,
    MN_PH_CSQLVLEXT_RSSILV_3,
    MN_PH_CSQLVLEXT_RSSILV_4,
    MN_PH_CSQLVLEXT_RSSILV_5,
    MN_PH_CSQLVLEXT_RSSILV_BUTT
};
typedef VOS_UINT8 MN_PH_CSQLVLEXT_RSSILV_ENUM_UINT8;
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
enum MN_PH_MODE_ANTLEVEL_ENUM
{
    MN_PH_MODE_ANTLEVEL_0,
    MN_PH_MODE_ANTLEVEL_1,
    MN_PH_MODE_ANTLEVEL_2,
    MN_PH_MODE_ANTLEVEL_3,
    MN_PH_MODE_ANTLEVEL_4,
    MN_PH_MODE_ANTLEVEL_BUTT
};
typedef VOS_UINT8 MN_PH_MODE_ANTLEVEL_ENUM_UINT8;
#endif
/*****************************************************************************
 ö����    : MN_PH_CSQLVLEXT_RSSILV_VALUE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CSQLVLEXT����RSSILV�źŸ�������ö���б�
*****************************************************************************/
enum MN_PH_CSQLVLEXT_RSSILV_VALUE_ENUM
{
    MN_PH_CSQLVLEXT_RSSILV_VALUE_0      = 0,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_20     = 20,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_40     = 40,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_60     = 60,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_80     = 80,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_99     = 99,
    MN_PH_CSQLVLEXT_RSSILV_VALUE_BUTT
};
typedef VOS_UINT8 MN_PH_CSQLVLEXT_RSSILV_VALUE_ENUM_UINT8;


enum TAF_SYS_SUBMODE_ENUM
{
    TAF_SYS_SUBMODE_NONE                = 0,                /* �޷��� */
    TAF_SYS_SUBMODE_GSM                 = 1,                /* GSMģʽ */
    TAF_SYS_SUBMODE_GPRS                = 2,                /* GPRSģʽ */
    TAF_SYS_SUBMODE_EDGE                = 3,                /* EDGEģʽ */
    TAF_SYS_SUBMODE_WCDMA               = 4,                /* WCDMAģʽ */
    TAF_SYS_SUBMODE_HSDPA               = 5,                /* HSDPAģʽ */
    TAF_SYS_SUBMODE_HSUPA               = 6,                /* HSUPAģʽ */
    TAF_SYS_SUBMODE_HSDPA_HSUPA         = 7,                /* HSDPA+HSUPAģʽ */
    TAF_SYS_SUBMODE_TD_SCDMA            = 8,                /* TD_SCDMAģʽ */
    TAF_SYS_SUBMODE_HSPA_PLUS           = 9,                /* HSPA+ģʽ */
    TAF_SYS_SUBMODE_LTE                 = 10,               /* LTEģʽ */
    TAF_SYS_SUBMODE_DC_HSPA_PLUS        = 17,               /* DC-HSPA+ģʽ */
    TAF_SYS_SUBMODE_DC_MIMO             = 18,               /* MIMO-HSPA+ģʽ */
    TAF_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  TAF_SYS_SUBMODE_ENUM_UINT8;

/*ucSysModeExȡֵ���£�*/
enum MN_PH_SYS_MODE_EX_ENUM
{
    MN_PH_SYS_MODE_EX_NONE_RAT  ,                                               /*�޷���*/
    MN_PH_SYS_MODE_EX_GSM_RAT   ,                                               /*GSMģʽ*/
    MN_PH_SYS_MODE_EX_CDMA_RAT  ,                                               /*CDMAģʽ*/
    MN_PH_SYS_MODE_EX_WCDMA_RAT ,                                               /*WCDMAģʽ*/
    MN_PH_SYS_MODE_EX_TDCDMA_RAT,                                               /*TD-SCDMAģʽ*/
    MN_PH_SYS_MODE_EX_WIMAX_RAT ,                                               /*Wimaxģʽ*/
    MN_PH_SYS_MODE_EX_LTE_RAT   ,                                               /*LTEģʽ*/
    MN_PH_SYS_MODE_EX_BUTT_RAT
};
typedef VOS_UINT8  MN_PH_SYS_MODE_EX_ENUM_U8;

/*ucSubSysModeExȡֵ���£�*/
enum MN_PH_SUB_SYS_MODE_EX_ENUM
{
    MN_PH_SUB_SYS_MODE_EX_NONE_RAT              ,                               /*�޷���*/
    MN_PH_SUB_SYS_MODE_EX_GSM_RAT               ,                               /*GSMģʽ*/
    MN_PH_SUB_SYS_MODE_EX_GPRS_RAT              ,                               /*GPRSģʽ*/
    MN_PH_SUB_SYS_MODE_EX_EDGE_RAT              ,                               /*EDGEģʽ*/

    MN_PH_SUB_SYS_MODE_EX_IS95A_RAT     = 21    ,                               /*IS95Aģʽ*/
    MN_PH_SUB_SYS_MODE_EX_IS95B_RAT             ,                               /*IS95Bģʽ*/
    MN_PH_SUB_SYS_MODE_EX_CDMA20001X_RAT        ,                               /*CDMA20001Xģʽ*/
    MN_PH_SUB_SYS_MODE_EX_EVDOREL0_RAT          ,                               /*EVDORel0ģʽ*/
    MN_PH_SUB_SYS_MODE_EX_EVDORELA_RAT          ,                               /*EVDORelAģʽ*/
    MN_PH_SUB_SYS_MODE_EX_EVDORELB_RAT          ,                               /*EVDORelBģʽ*/
    MN_PH_SUB_SYS_MODE_EX_HYBIRD_CDMA20001X_RAT ,                               /*HYBIRD CDMA20001Xģʽ*/
    MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDOREL0_RAT   ,                               /*HYBIRD EVDORel0ģʽ*/
    MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDORELA_RAT   ,                               /*HYBIRD EVDORelAģʽ*/
    MN_PH_SUB_SYS_MODE_EX_HYBIRD_EVDORELB_RAT   ,                               /*HYBIRD EVDORelAģʽ*/

    MN_PH_SUB_SYS_MODE_EX_WCDMA_RAT     = 41    ,                               /*WCDMAģʽ*/
    MN_PH_SUB_SYS_MODE_EX_HSDPA_RAT     = 42    ,                               /*HSDPAģʽ*/
    MN_PH_SUB_SYS_MODE_EX_HSUPA_RAT     = 43    ,                               /*HSUPAģʽ*/
    MN_PH_SUB_SYS_MODE_EX_HSPA_RAT      = 44    ,                               /*HSPAģʽ*/
    MN_PH_SUB_SYS_MODE_EX_HSPA_PLUS_RAT = 45    ,                               /*HSPA+ģʽ*/
    MN_PH_SUB_SYS_MODE_EX_DCHSPA_PLUS_RAT = 46  ,                               /*DCHSPA+ģʽ*/

    MN_PH_SUB_SYS_MODE_EX_TDCDMA_RAT    = 61    ,                               /*TD-SCDMAģʽ*/

    MN_PH_SUB_SYS_MODE_EX_TD_HSDPA_RAT                      = 62,               /*HSDPAģʽ*/
    MN_PH_SUB_SYS_MODE_EX_TD_HSUPA_RAT                      = 63,               /*HSUPAģʽ*/
    MN_PH_SUB_SYS_MODE_EX_TD_HSPA_RAT                       = 64,               /*HSPAģʽ*/
    MN_PH_SUB_SYS_MODE_EX_TD_HSPA_PLUS_RAT                  = 65,               /*HSPA+ģʽ*/

    MN_PH_SUB_SYS_MODE_EX_LTE_RAT       = 101   ,                               /*LTEģʽ*/
    MN_PH_SUB_SYS_MODE_EX_BUTT_RAT
};
typedef VOS_UINT8  MN_PH_SUB_SYS_MODE_EX_ENUM_U8;

/*****************************************************************************
 ö����    : TAF_PH_ACCESS_TECH_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : פ������Ľ��뼼��ö�٣�����CREG/CGREG��ACT����
*****************************************************************************/
enum TAF_PH_ACCESS_TECH_ENUM
{
    TAF_PH_ACCESS_TECH_GSM              = 0,                /* GSM */
    TAF_PH_ACCESS_TECH_GSM_COMPACT      = 1,                /* GSM Compact,��֧�� */
    TAF_PH_ACCESS_TECH_UTRAN            = 2,                /* UTRAN */
    TAF_PH_ACCESS_TECH_EGPRS            = 3,                /* EGPRS */
    TAF_PH_ACCESS_TECH_HSDPA            = 4,                /* HSDPA */
    TAF_PH_ACCESS_TECH_HSUPA            = 5,                /* HSUPA */
    TAF_PH_ACCESS_TECH_HSDPA_HSUPA      = 6,                /* HSDPA+HSUPA */
    TAF_PH_ACCESS_TECH_E_UTRAN          = 7,                /* E-UTRAN*/
    TAF_PH_ACCESS_TECH_BUTT
};
typedef VOS_UINT8  TAF_PH_ACCESS_TECH_ENUM_UINT8;


/*****************************************************************************
 ö����    : TAF_SIM_INSERT_STATE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ָʾ��ǰSIM����״̬:������Ƴ�
*****************************************************************************/
enum TAF_SIM_INSERT_STATE_ENUM
{
    TAF_SIM_INSERT_STATE_REMOVE              = 0,                /* �Ƴ� */
    TAF_SIM_INSERT_STATE_INSERT              = 1,                /* ���� */
    TAF_SIM_INSERT_STATE_BUTT

};
typedef VOS_UINT32  TAF_SIM_INSERT_STATE_ENUM_UINT32;



enum TAF_MMA_PLMN_LIST_ABORT_PROC_ENUM
{
    TAF_MMA_PLMN_LIST_ABORT_PROCESSING_TIMEOUT                   = 0,           /* ���ڴ���ʱ����ʱ����б��� */
    TAF_MMA_PLMN_LIST_ABORT_PROCESSING_USER_ABORT                = 1,           /* ���ڴ����û�����б��� */
    TAF_MMA_PLMN_LIST_ABORT_BUTT
};
typedef VOS_UINT8  TAF_MMA_PLMN_LIST_ABORT_PROC_ENUM_UINT8;



enum TAF_MMA_ACQ_REASON_ENUM
{
    TAF_MMA_ACQ_REASON_POWER_UP         = 0,    /* ������ȡ���� */
    TAF_MMA_ACQ_REASON_OOS              = 1,    /* ����������ȡ���� */
    TAF_MMA_ACQ_REASON_HIGH_PRIO        = 2,    /* ��ȡ�������ȼ����� */
    TAF_MMA_ACQ_REASON_BUTT
};
typedef VOS_UINT8  TAF_MMA_ACQ_REASON_ENUM_UINT8;


enum TAF_MMA_EPS_ATTACH_REASON_ENUM
{
    TAF_MMA_ATTACH_REASON_INITIAL          = 0,    /* ��C->L��ѡʱ����д��ԭ�� */
    TAF_MMA_ATTACH_REASON_HANDOVER         = 1,    /* C->L��ѡʱ��д��ԭ�� */
    TAF_MMA_ATTACH_REASON_BUTT
};
typedef VOS_UINT8 TAF_MMA_EPS_ATTACH_REASON_ENUM_UINT8;


enum TAF_MMA_PLMN_PRIORITY_CLASS_ENUM
{
    TAF_MMA_PLMN_PRIORITY_HOME               = 0,/* home or ehome plmn */
    TAF_MMA_PLMN_PRIORITY_PREF               = 1,/* UPLMN or OPLMN */
    TAF_MMA_PLMN_PRIORITY_ANY                = 2,/* Acceptable PLMN */
    TAF_MMA_PLMN_PRIORITY_BUTT
};
typedef VOS_UINT8 TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8;


enum TAF_MMA_APP_OPER_RESULT_ENUM
{
    TAF_MMA_APP_OPER_RESULT_SUCCESS               = 0,/* �����ɹ� */
    TAF_MMA_APP_OPER_RESULT_FAILURE               = 1,/*  ����ʧ�� */
    TAF_MMA_APP_OPER_RESULT_ACQUIRED_FAIL         = 2,/* ACQʧ�� */
    TAF_MMA_APP_OPER_RESULT_REJECT                = 3,/* ��������иò��� */
    TAF_MMA_APP_OPER_RESULT_BUTT
};
typedef VOS_UINT32 TAF_MMA_APP_OPER_RESULT_ENUM_UINT32;


enum TAF_MMA_DETACH_CAUSE_ENUM
{
    TAF_MMA_DETACH_CAUSE_NORMAL               = 0,/* ����Detach */
    TAF_MMA_DETACH_CAUSE_3GPP2_ATTACHED       = 1,/* ��3GPP2�ϸ��ųɹ� */
    TAF_MMA_DETACH_CAUSE_BUTT
};
typedef VOS_UINT8 TAF_MMA_DETACH_CAUSE_ENUM_UINT8;



#define  TAF_INVALID_TAB_INDEX          0
/*TAF��ģ��ID*/
#ifndef SUBMOD_NULL
#define  SUBMOD_NULL                    0
#endif
#define  TAF_CCA                        1
#define  TAF_APS                        2
#define  TAF_SMA                        3
#define  TAF_SSA                        4
#define  TAF_MMA                        5
#define  TAF_ALL_SUBMODULE              0xFF    /*������ģ��*/
#define  TAF_TAFM                       0



/* IMEI��Ч���ݳ���: IMEI��Ϣ��IMEI(TAC8λ,SNR6λ)��У��λ���������*/
#define TAF_IMEI_DATA_LENGTH            (15)

typedef struct
{
    TAF_UINT32    Mcc;
    TAF_UINT32    Mnc;
}TAF_PLMN_ID_STRU;


typedef struct
{
    TAF_PLMN_ID_STRU    stHplmn;
    VOS_UINT8           ucHplmnMncLen;
    VOS_UINT8           aucReserved[3];
}TAF_HPLMN_WITH_MNC_LEN_STRU;


#define TAF_PH_RELEASEDATE_LEN            10
typedef struct
{

    TAF_UINT8     aucReleaseDate[TAF_PH_RELEASEDATE_LEN+1];         /*��������*/
}TAF_PH_RELEASE_DATE_STRU;

#define TAF_PH_RELEASETIME_LEN             8
typedef struct
{

    TAF_UINT8     aucReleaseTime[TAF_PH_RELEASETIME_LEN+1];         /*����ʱ��*/
}TAF_PH_RELEASE_TIME_STRU;


#define TAF_PH_CAPLITYCLASS1               1
#define TAF_PH_CAPLITYCLASS2               4
#define TAF_PH_CAPLITYCLASS3              16
#define TAF_PH_COMPLETECAPILITYLIST_LEN   16
#define TAF_PH_CAPILITYLIST_TYPE           3
typedef struct
{
/*�����Ĺ����б�*/
    TAF_UINT8       aucCompleteCapilityList[TAF_PH_CAPILITYLIST_TYPE][TAF_PH_COMPLETECAPILITYLIST_LEN];
}TAF_PH_COMPCAPLIST_STRU;

/*����HS����ö��*/
typedef enum
{
    TAF_PH_ONLINE,
    TAF_PH_OFFLINE,
    TAF_PH_MT_STA_BUTT
}TAF_PH_MT_STA_ENUM;


enum MN_MMA_CPAM_RAT_TYPE
{
    MN_MMA_CPAM_RAT_TYPE_WCDMA,          /* WCDMA��ģ**/
    MN_MMA_CPAM_RAT_TYPE_WCDMA_GSM,      /* WCDMA/GSM˫ģ */
    MN_MMA_CPAM_RAT_TYPE_GSM,            /* GSM��ģ */
    MN_MMA_CPAM_RAT_TYPE_NOCHANGE,       /* ���ı�*/
    MN_MMA_CPAM_RAT_TYPE_BUTT
};
typedef VOS_UINT8 MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8;

#define  TAF_PHONE_ACCESS_MODE_LEN        (2)

/*Taf_USIM_RAT*/
typedef TAF_UINT16 TAF_MMC_USIM_RAT;
#define TAF_MMC_USIM_UTRN_RAT             0x8000
#define TAF_MMC_USIM_GSM_RAT              0x0080
#define TAF_MMC_USIM_UTRN_GSM_RAT         0x8080
#define TAF_MMC_USIM_GSM_COMPACT_RAT      0x0040
#define TAF_MMC_USIM_NO_RAT               0x0000
#define TAF_MMC_USIM_E_UTRN_RAT            0x4000
#define MMC_MS_LTE                          2

typedef TAF_UINT8 TAF_PHONE_SERVICE_STATUS;

typedef TAF_UINT8 TAF_PHONE_CHANGED_SERVICE_STATUS;                      /* ����״̬�仯�����ϱ�(^SRVST) */
#define TAF_REPORT_SRVSTA_NO_SERVICE                   0                        /* �޷���״̬       */
#define TAF_REPORT_SRVSTA_LIMITED_SERVICE              1                        /* ���Ʒ���״̬     */
#define TAF_REPORT_SRVSTA_NORMAL_SERVICE               2                        /* ��������״̬     */
#define TAF_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE     3                        /* �����Ƶ�������� */
#define TAF_REPORT_SRVSTA_DEEP_SLEEP                   4                        /* ʡ�����˯��״̬ */

typedef TAF_UINT16 TAF_PHONE_ERROR;

typedef struct
{
    TAF_PHONE_SERVICE_STATUS    CsSrvSta; /*CS����״̬*/
    TAF_PHONE_SERVICE_STATUS    PsSrvSta; /*PS����״̬*/
}TAF_PH_SRV_STA_STRU;

typedef TAF_UINT8 TAF_PH_PLMN_PRIO;
#define TAF_PLMN_PRIO_AUTO    0         /*�Զ�ѡ������*/
#define TAF_PLMN_GSM_PRIO     1         /*��ѡ2G����*/
#define TAF_PLMN_WCDMA_PRIO   2         /*��ѡ3G����*/
#define TAF_PLMN_PRIO_NOCHANGE  3

#define TAF_PLMN_PRIO_DIST_BTWN_CPAM_SYSCFG  1 /*CPAM��SYSCFG�Ľ������ȼ����õĲ�� 1 */

typedef TAF_UINT8 TAF_PH_MS_CLASS_TYPE;
#define TAF_PH_MS_CLASS_CC        0     /*ֻ֧��CS���ֻ���Ӧ��MMC��D_MMC_MODE_CC*/
#define TAF_PH_MS_CLASS_CG        1     /*ֻ֧��PS���ֻ���Ӧ��MMC��D_MMC_MODE_CG*/
#define TAF_PH_MS_CLASS_A         2

#define TAF_PH_MS_CLASS_ANY       3     /* �൱��ֻ֧��CS�� */

#define TAF_PH_MS_CLASS_NULL      5
#define TAF_PH_MS_CLASS_B         6     /*��Ӧ��GSM��B���ֻ�*/

typedef TAF_UINT8 TAF_PH_SERVICE_DOMAIN;
#define  TAF_PH_SERVICE_CS       0       /*��CSҵ��ʹ�� */
#define  TAF_PH_SERVICE_PS       1       /*��PSҵ��ʹ�� */
#define  TAF_PH_SERVICE_CS_PS    2       /*PS��CSҵ��ʹ�� */
#define  TAF_PH_SERVICE_ANY      3       /* ��Ч�� PS_CS */
#define  TAF_PH_SERVICE_NOCHANGE 4       /*���ı������ */
#define  TAF_PH_SERVICE_NULL     5       /*PS��CSҵ��û��ʹ��*/


typedef TAF_UINT8 TAF_PH_IMSI_LOCK_STATUS;
#define TAF_PH_IMSI_LOCK_ENABLED             1
#define TAF_PH_IMSI_LOCK_DISABLED            0

/* ��ȡ�˿���Ϣ*/
#define TAF_MAX_PORT_INFO_LEN     100
typedef struct
{
    TAF_UINT8 aucPortInfo[TAF_MAX_PORT_INFO_LEN + 1];
    TAF_UINT8 aucRsv[3];
}TAF_PH_PORT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TAF_PH_CREATION_TIME_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ϵͳ����ʱ��
*****************************************************************************/
#define TAF_MAX_CREATION_TIME_LEN       31
typedef struct
{
    TAF_UINT8 aucCreationTime[TAF_MAX_CREATION_TIME_LEN + 1];
}TAF_PH_CREATION_TIME_STRU;

#define TAF_CFG_VERSION                 (1004)

/*+CGMR - ��ȡģ������汾��*/
typedef struct
{
    TAF_UINT8 aucRevisionId[TAF_MAX_REVISION_ID_LEN + 1];
}TAF_PH_REVISION_ID_STRU;

/*****************************************************************************
 �ṹ��    : TAF_PH_HW_VER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Ӳ������
*****************************************************************************/
typedef struct
{
    TAF_UINT8 aucHwVer[TAF_MAX_HARDWARE_LEN+1];
}TAF_PH_HW_VER_STRU;

/*+CGMM - ��ȡģ���ʶ*/
typedef struct
{
    TAF_UINT8 aucModelId[TAF_MAX_MODEL_ID_LEN + 1];
}TAF_PH_MODEL_ID_STRU;

/*****************************************************************************
 �ṹ��    : TAF_PH_CDROM_VER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��̨����汾��
*****************************************************************************/


typedef struct
{
    TAF_UINT8 aucIsoInfo[TAF_CDROM_VERSION_LEN];
}TAF_PH_CDROM_VER_STRU;

/*+CGSN - ��ȡIMEI*/
typedef TAF_UINT8 TAF_PH_IMEI_TYPE;
#define TAF_PH_IMEI_LEN     16
#define TAF_PH_IMEIV_Mode   1
#define TAF_PH_IMEI_Mode    0

typedef struct
{
    TAF_PH_IMEI_TYPE ImeiMode;
    TAF_UINT8        aucImei[TAF_PH_IMEI_LEN + 1];
}TAF_PH_IMEI_STRU;


 /*+CIMI - ��ȡIMSI*/
#define TAF_PH_IMSI_LEN     15
typedef struct
{
    TAF_UINT8  aucImsi[TAF_PH_IMSI_LEN + 1];
}TAF_PH_IMSI_STRU;



/*+CREG - ��������ע��״̬�ϱ���ʽ*/
#define TAF_PH_LAC_LENGTH       4
#define TAF_PH_CI_LENGTH        4
#define TAF_PH_RAC_LENGTH       2


/*ע��״̬*/
typedef TAF_UINT8 TAF_PH_REG_STATE_TYPE;
#define TAF_PH_REG_NOT_REGISTERED_NOT_SEARCH   0 /*û��ע�ᣬMS���ڲ�û������ѰҪע����µ���Ӫ��*/
#define TAF_PH_REG_REGISTERED_HOME_NETWORK     1 /*ע���˱�������*/
#define TAF_PH_REG_NOT_REGISTERED_SEARCHING    2 /*û��ע�ᣬ��MS������ѰҪע����µ���Ӫ��*/
#define TAF_PH_REG_REGISTERED_DENIED           3 /*ע�ᱻ�ܾ�*/
#define TAF_PH_REG_UNKNOWN                     4 /*δ֪ԭ��*/
#define TAF_PH_REG_REGISTERED_ROAM             5 /*ע������������*/

/*����ATTACH��DETACH����*/
typedef TAF_UINT8  TAF_PH_ATTACH_TYPE;
typedef TAF_UINT8  TAF_PH_DETACH_TYPE;
#define TAF_PH_ATTACH_DETACH_NULL           0
#define TAF_PH_PS_OPERATE                   1  /*����PS����*/
#define TAF_PH_CS_OPERATE                   2  /*����CS����*/
#define TAF_PH_PS_CS_OPERATE                3  /*����PS��CS����*/

typedef TAF_UINT8  TAF_PH_CS_STATUS;
typedef TAF_UINT8  TAF_PH_PS_STATUS;
#define TAF_PH_ATTACHED                       1
#define TAF_PH_DETACHED                       0
#define TAF_MMC_NORMAL_SERVICE                0

#define TAF_MMC_LIMITED_SERVICE                 (1)                             /* ���Ʒ��� */
#define TAF_MMC_LIMITED_SERVICE_REGION          (2)                             /* ������������� */
#define TAF_MMC_NO_IMSI                         (3)                             /* ��imsi */
#define TAF_MMC_NO_SERVICE                      (4)                             /* �޷��� */



/*����ģʽ��������+CFUN  */
typedef TAF_UINT8 TAF_PH_MODE;
#define TAF_PH_MODE_MINI                0   /* minimum functionality*/
#define TAF_PH_MODE_FULL                1   /* full functionality */
#define TAF_PH_MODE_TXOFF               2   /* disable phone transmit RF circuits only */
#define TAF_PH_MODE_RXOFF               3   /* disable phone receive RF circuits only */
#define TAF_PH_MODE_RFOFF               4   /* disable phone both transmit and receive RF circuits */
#define TAF_PH_MODE_FT                  5   /* factory-test functionality */
#define TAF_PH_MODE_RESET               6   /* reset */
#define TAF_PH_MODE_VDFMINI             7   /* mini mode required by VDF*/
#define TAF_PH_MODE_POWEROFF            8   /* �ػ��µ�ģʽ */
#define TAF_PH_MODE_LOWPOWER            9
#if (FEATURE_ON == MBB_FEATURE_FAKE_ON_OFF)
#define TAF_PH_MODE_FAKEOFF             10
#define TAF_PH_MODE_FAKEON              11
#define TAF_PH_MODE_NUM_MAX             12
#else /*FEATURE_ON == MBB_FEATURE_FAKE_ON_OFF*/
#define TAF_PH_MODE_NUM_MAX             10
#endif /*FEATURE_ON == MBB_FEATURE_FAKE_ON_OFF*/
typedef TAF_UINT8   TAF_PH_RESET_FLG;
#define TAF_PH_OP_MODE_UNRESET       0
#define TAF_PH_OP_MODE_RESET         1

typedef TAF_UINT8   TAF_PH_CMD_TYPE;
#define TAF_PH_CMD_SET                  0   /* set cmd */
#define TAF_PH_CMD_QUERY                1   /* query cmd */

typedef struct
{
     TAF_PH_CMD_TYPE                    CmdType; /* �������� */
     TAF_PH_MODE                        PrePhMode;
     TAF_PH_MODE                        PhMode;  /* ģʽ */
     TAF_PH_RESET_FLG                   PhReset; /* �Ƿ���Ҫ���� */
}TAF_PH_OP_MODE_STRU;
typedef struct
{
     TAF_PH_CMD_TYPE                    CmdType; /* �������� */
     TAF_PH_MODE                        PhMode;  /* ģʽ */
}TAF_PH_OP_MODE_CNF_STRU;


typedef struct
{
    VOS_INT16                       sRscpValue;  /* С���ź���������3g��^cerssi�ϱ�ʹ��*/
    VOS_INT16                       sEcioValue;  /* С�����������3g��^cerssi�ϱ�ʹ��*/
} TAF_MMA_W_CELL_SIGN_INFO_STRU;


typedef struct
{
    VOS_INT16                       sRssiValue;   /* С���ź���������2g��^cerssi�ϱ�ʹ��,2gû��rscp�ĸ����õ���rssi */
    VOS_UINT8                       aucReserve1[2];
} TAF_MMA_G_CELL_SIGN_INFO_STRU;



/*RSSI��ѯ��������+CSQ*/
/*
  0       ����0��С�� -113 dBm
  1                -111 dBm
  2...30           -109...  -53 dBm
  31     ���ڻ���� -51 dBm
  99     δ֪�򲻿ɲ⡣
*/
#define TAF_PH_RSSIUNKNOW        99
#define TAF_PH_RSSIZERO          0

typedef struct
{
    TAF_UINT8        ucRssiValue;       /*��ת��Ϊ�ȼ���ʾ���ź�ǿ��*/
    TAF_UINT8        ucChannalQual;     /*������,ֻ������ҵ���ʱ�����,����
                                          Ч��99*/
    VOS_UINT8       aucReserved1[2];

    union
    {
        TAF_MMA_W_CELL_SIGN_INFO_STRU   stWCellSignInfo;
        TAF_MMA_G_CELL_SIGN_INFO_STRU   stGCellSignInfo;
    }u;


}TAF_PH_RSSI_VALUE_STRU;

#define TAF_PH_RSSI_MAX_NUM         8

typedef struct
{
    TAF_UINT8                           ucRssiNum;                    /*�ϱ��ź�ǿ��С���ĸ���*/

    TAF_PH_RAT_TYPE_ENUM_UINT8          enRatType;                    /* ����ģʽ0:G;1:W */
    VOS_UINT8                           ucCurrentUtranMode;
    VOS_UINT8                           aucReserv1;

    VOS_UINT16                          usCellDlFreq;                           /*С��Ƶ��(����)*/
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usCellUlFreq;                           /*��ǰƵ��(����)*/
    VOS_INT16                           sUeRfPower;                             /*���书��*/

    TAF_PH_RSSI_VALUE_STRU              aRssi[TAF_PH_RSSI_MAX_NUM];   /*ÿ��С�����ź�ǿ����������*/
}TAF_PH_RSSI_STRU;

typedef struct
{
    TAF_INT32        lRscpValue;
    TAF_INT32        lEcioValue;
    TAF_UINT8        ucRssiValue;       /*��ת��Ϊ�ȼ���ʾ���ź�ǿ��*/
    TAF_UINT8        ucAnlevelValue;
    TAF_UINT8        ucChannalQual;     /*������,ֻ������ҵ���ʱ�����,����Ч��99*/
}TAF_PH_ANLEVEL_VALUE_STRU;

#define TAF_PH_ANLEVEL_MAX_NUM         8

typedef struct
{
    TAF_UINT8                 ucAnlevelNum;                    /*�ϱ��ź�ǿ��С���ĸ���*/
    TAF_PH_ANLEVEL_VALUE_STRU    aAnlevel[TAF_PH_ANLEVEL_MAX_NUM];   /*ÿ��С�����ź�ǿ����������*/
}TAF_PH_ANLEVEL_STRU;

#define TAF_UE_RFPOWER_INVALID      0x1fff
#define TAF_FREQ_INVALID            0xffff
typedef struct
{
    TAF_UINT32  CellId;
    TAF_INT16   CellRSCP;
} TAF_PH_CELL_RSCP_ST;

typedef struct
{
    TAF_UINT16              CellNum;
    TAF_PH_CELL_RSCP_ST     CellRscp[TAF_PH_RSSI_MAX_NUM];
    TAF_UINT16              CellDlFreq;       /*С��Ƶ��(����)*/
} TAF_PH_CELL_RSSI_STRU;

typedef struct
{
    TAF_UINT16              CellUlFreq;       /*��ǰƵ��(����)*/
    TAF_INT16               UeRfPower;        /*���书��*/
} TAF_PH_UE_RFPOWER_FREQ_STRU;

/*��ǰ��ص���+CBC*/
 /*
 ״̬���ͣ�
 0 ������ڹ���
 1 �������ӣ����ǵ��δ����
 2 û����������
 3 ��Դ����, ͨ����ֹ
*/
#define TAF_PH_BATTERYCHARGING             0
#define TAF_PH_BATTERYNOSUPPLY             1
#define TAF_PH_NOBATTERYFIXED              2
#define TAF_PH_POWERSOURCEERROR            3
typedef TAF_UINT8 TAF_PH_BATTERYPOWER_STA;

/*
0��Դ�����û����������
1...100 Ŀǰʣ��������ٷֱ�
*/
typedef TAF_UINT8 TAF_PH_BATTERY_REMAINS;
typedef struct
{

   TAF_PH_BATTERYPOWER_STA         BatteryPowerStatus;
   TAF_PH_BATTERY_REMAINS          BatteryRemains;
}TAF_PH_BATTERYPOWER_STRU;


typedef TAF_UINT8 TAF_ME_PERSONALISATION_CMD_TYPE;
#define TAF_ME_PERSONALISATION_SET             0x01   /*�ƶ��豸˽����������*/
#define TAF_ME_PERSONALISATION_VERIFY          0x02   /*�ƶ��豸˽������У��*/
#define TAF_ME_PERSONALISATION_PWD_CHANGE      0x03   /*�����ƶ��豸˽������*/
#define TAF_ME_PERSONALISATION_ACTIVE          0x04   /*�����ƶ��豸˽�й���*/
#define TAF_ME_PERSONALISATION_DEACTIVE        0x05   /*ȥ�����ƶ��豸˽�й���*/
#define TAF_ME_PERSONALISATION_RETRIEVE        0x06   /*��ȡ��ǰ�ƶ��豸˽�������б�*/
#define TAF_ME_PERSONALISATION_QUERY           0x07   /*��ѯ��ǰ�ƶ��豸˽������״̬*/

/*��ǰֻ֧�ֶ������Ĳ���*/
typedef TAF_UINT8 TAF_ME_PERSONALISATION_TYPE;
#define TAF_SIM_PERSONALISATION                 0x01   /*����*/
#define TAF_NETWORK_PERSONALISATION             0x02   /*������*/
#define TAF_NETWORK_SUBSET_PERSONALISATION      0x03   /*�������Ӽ�*/
#define TAF_SERVICE_PROVIDE_PERSONALISATION     0x04   /*��ҵ��Ӧ��*/
#define TAF_CORPORATE_PERSONALISATION           0x05   /*����˾**/
#define TAF_OPERATOR_PERSONALISATION            0x06   /*�Զ���:������,�����ն�����ʵ�� */

/*���嵱ǰ����״̬*/
typedef TAF_UINT8 TAF_ME_PERSONALISATION_STATUS_FLAG;
#define TAF_ME_PERSONALISATION_ACTIVE_STATUS       0
#define TAF_ME_PERSONALISATION_DEACTIVE_STATUS     1

/*�Զ���:���嵱ǰ����Ӫ�̼���״̬ */
#define TAF_OPERATOR_LOCK_STATUS_NOT_UNLOCK        TAF_ME_PERSONALISATION_ACTIVE_STATUS
#define TAF_OPERATOR_LOCK_STATUS_UNLOCKED          TAF_ME_PERSONALISATION_DEACTIVE_STATUS

/* �ϱ�������Ӫ��״̬*/
typedef enum
{
    TAF_OPERATOR_LOCK_NEED_UNLOCK_CODE             = 1,/* ��Ҫ��������� */
    TAF_OPERATOR_LOCK_NONEED_UNLOCK_CODE           = 2,/* ����Ҫ��������� */
    TAF_OPERATOR_LOCK_LOCKED                       = 3,/* ��������״̬ */
    TAF_OPERATOR_LOCK_BUTT
}TAF_OPERATOR_LOCK_STATUS_ENUM;
typedef TAF_UINT32 TAF_OPERATOR_LOCK_STATUS_ENUM_U32;

#define TAF_OPERATOR_UNLOCK_TIMES_MAX                   10  /* ��Ӫ���������������ֵ */
#define TAF_OPERATOR_UNLOCK_TIMES_MIN                   0   /* ��Ӫ��������������Сֵ */
#define TAF_PH_ME_LOCK_OPER_LEN_MAX                     15  /* ��Ӫ�����ṩ������Ӫ������󳤶� */
#define TAF_PH_ME_LOCK_OPER_LEN_MIN                     5   /* ��Ӫ�����ṩ������Ӫ������С���� */

typedef struct
{
    TAF_UINT32                          RemainTimes;
    TAF_OPERATOR_LOCK_STATUS_ENUM_U32   OperatorLockStatus;
    TAF_UINT8                           OperatorLen;
    TAF_UINT8                           Operator[TAF_PH_ME_LOCK_OPER_LEN_MAX];
}TAF_OPERATOR_LOCK_INFO_STRU;

#define TAF_MAX_IMSI_LEN                        15
typedef struct
{
    TAF_UINT8   DataLen;
    TAF_UINT8   aucSimPersonalisationStr[TAF_MAX_IMSI_LEN];       /* �趨����������   */
}TAF_SIM_PERSIONALISATION_STR_STRU;

typedef union
{
    /*�����ִ�,CmdTypeΪTAF_ME_PERSONALISATION_RETRIEVE��MePersonalTypeΪTAF_SIM_PERSONALISATIONʱ��Ч*/
    TAF_SIM_PERSIONALISATION_STR_STRU  SimPersionalisationStr;
}TAF_ME_PERSONALISATION_SET_UN;

#if(FEATURE_ON == MBB_WPG_COMMON)
/*�豸��״̬��Ϣ*/
typedef struct
{
    VOS_UINT32  ulDeviceLockStatusFlg;    /*�豸������״̬*/
    VOS_UINT32  ulDeviceUnlockFlg;        /*�豸������״̬*/
}TAF_OPERATOR_TATA_DEVICELOCK_STRU;

typedef union
{
    /*�����ִ�,CmdTypeΪTAF_ME_PERSONALISATION_RETRIEVE��MePersonalTypeΪTAF_SIM_PERSONALISATIONʱ��Ч*/
    TAF_SIM_PERSIONALISATION_STR_STRU  SimPersionalisationStr;
    /*��Ӫ������Ϣ,CmdTypeΪTAF_ME_PERSONALISATION_QUERY��MePersonalTypeΪTAF_OPERATOR_PERSONALISATIONʱ��Ч*/
    TAF_OPERATOR_LOCK_INFO_STRU        OperatorLockInfo;
    TAF_OPERATOR_TATA_DEVICELOCK_STRU  TataLockInfo;    /*������Ա���豸��״̬��Ϣ*/
}TAF_ME_PERSONALISATION_REPORT_CONTENT_UN;
#else
typedef union
{
    /*�����ִ�,CmdTypeΪTAF_ME_PERSONALISATION_RETRIEVE��MePersonalTypeΪTAF_SIM_PERSONALISATIONʱ��Ч*/
    TAF_SIM_PERSIONALISATION_STR_STRU  SimPersionalisationStr;

    /*��Ӫ������Ϣ,CmdTypeΪTAF_ME_PERSONALISATION_QUERY��MePersonalTypeΪTAF_OPERATOR_PERSONALISATIONʱ��Ч*/
    TAF_OPERATOR_LOCK_INFO_STRU        OperatorLockInfo;
}TAF_ME_PERSONALISATION_REPORT_CONTENT_UN;
#endif

#if (FEATURE_ON == MBB_SIMLOCK_FOUR)
#define TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX   (16)
#else
#define TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX   (8)
#endif /*MBB_SIMLOCK_FOUR*/

typedef struct
{
    TAF_ME_PERSONALISATION_CMD_TYPE     CmdType;
    TAF_ME_PERSONALISATION_TYPE         MePersonalType;
    TAF_UINT8                           aucOldPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];
    TAF_UINT8                           aucNewPwd[TAF_PH_ME_PERSONALISATION_PWD_LEN_MAX +1];
    TAF_ME_PERSONALISATION_SET_UN       unMePersonalisationSet;
#if(FEATURE_ON == MBB_WPG_COMMON)
    TAF_UINT32                          aucmode;    /*������Ա���豸����������*/
#endif
}TAF_ME_PERSONALISATION_DATA_STRU;

typedef TAF_UINT8   TAF_OP_ME_PERSONALISATION_RESULT;
#define TAF_PH_ME_PERSONALISATION_OK                    0
#define TAF_PH_ME_PERSONALISATION_IMST_STR_NOT_EXIST    1
#define TAF_PH_ME_PERSONALISATION_ERROR                 2
#define TAF_PH_ME_PERSONALISATION_WRONG_PARA            3
#define TAF_PH_ME_PERSONALISATION_WRONG_PWD             4
#define TAF_PH_ME_PERSONALISATION_LOCK_PHONE_TO_SIM     5
#define TAF_PH_ME_PERSONALISATION_NO_SIM                6
#define TAF_PH_ME_PERSONALISATION_OP_NOT_ALLOW          7

#define TAF_PH_CARDLOCK_DEFAULT_MAXTIME    10

typedef struct
{
    TAF_OP_ME_PERSONALISATION_RESULT                    OpRslt;                 /*�ƶ��豸˽�в������*/
    TAF_ME_PERSONALISATION_CMD_TYPE                     CmdType;                /*�ƶ��豸˽�в�����������*/
    TAF_ME_PERSONALISATION_STATUS_FLAG                  ActiveStatus;           /*�ƶ��豸˽�в�������״̬ */
    TAF_ME_PERSONALISATION_TYPE                         MePersonalisatonType;   /*�ƶ��豸˽������*/
    TAF_ME_PERSONALISATION_REPORT_CONTENT_UN            unReportContent;        /*�ƶ��豸˽�в����ϱ�����*/
}TAF_PH_ME_PERSONLISATION_CNF_STRU;


typedef struct
{
   TAF_UINT8     ucLen;
   TAF_UINT8     ucSW1;
   TAF_UINT8     ucSW2;
   TAF_UINT8     aucContent[USIMM_T0_APDU_MAX_LEN];
} TAF_PH_RESTRICTED_ACCESS_CNF_STRU;
/*PIN�����������+CPIN,+CPWD,+CLCK*/
/*
�ײ�API�ṩ�ĺ������õ����ݽṹ
TAF_UINT8 ucCmdType, TAF_UINT8 ucPINType, TAF_UINT8 *pucOldPIN, TAF_UINT8 *pucNewPIN
*/

#define TAF_PH_PINCODELENMAX     8
#define TAF_PH_PINCODELENMIN     4
#define TAF_PH_UNLOCKCODELEN     16

#define TAF_SIM_PIN              0      /*PIN1*/
#define TAF_SIM_PUK              1      /*PUK1*/
#define TAF_SIM_PIN2             6      /*PIN2*/
#define TAF_SIM_PUK2             7      /*PUK2*/
/* Modified by L47619 for AP-Modem Personalisation Project, 2012/04/11, begin */
#define TAF_PHSIM_PIN            8      /*PH-SIM PIN*/
#define TAF_PHNET_PIN            9      /*PH-NET PIN*/
#define TAF_PHNET_PUK            10     /*PH-NET PUK*/
#define TAF_PHNETSUB_PIN         11     /*PH-NETSUB PIN*/
#define TAF_PHNETSUB_PUK         12     /*PH-NETSUB PUK*/
#define TAF_PHSP_PIN             13     /*PH-SP PIN*/
#define TAF_PHSP_PUK             14     /*PH-SP PUK*/
/* Modified by L47619 for AP-Modem Personalisation Project, 2012/04/11, end */
#define TAF_SIM_NON              255    /*��ȷ������PIN������ʱ�����ֵ*/
typedef TAF_UINT8 TAF_PH_PIN_TYPE;


typedef TAF_UINT8 TAF_PH_PIN_CMD_TYPE;
#define TAF_PIN_VERIFY          0x20   /*У��PIN��*/
#define TAF_PIN_CHANGE          0x24   /*����PIN�������*/
#define TAF_PIN_DISABLE         0x26   /*��ֹʹ��PIN��*/
#define TAF_PIN_ENABLE          0x28   /*ʹ��PIN��*/
#define TAF_PIN_UNBLOCK         0x2c   /*�����ֹPIN��*/

/*����PIN���ѯ����*/
#define TAF_PIN_QUERY           0x30   /*��ѯPIN��״̬*/
#define TAF_PIN_RemainTime      0x31
/* Added by L47619 for AP-Modem Personalisation Project, 2012/04/12, begin */
#define TAF_PIN2_QUERY          0x32   /*��ѯPIN2��״̬*/
/* Added by L47619 for AP-Modem Personalisation Project, 2012/04/12, end */
#define TAF_PIN_CMD_NULL        0x00

typedef struct
{
    TAF_PH_PIN_CMD_TYPE               CmdType;
    TAF_PH_PIN_TYPE                   PinType;
    TAF_UINT8                         aucOldPin[TAF_PH_PINCODELENMAX +1];
    TAF_UINT8                         aucNewPin[TAF_PH_PINCODELENMAX +1];
}TAF_PH_PIN_DATA_STRU;


/*��Ϊ��ѯʱ,PIN���صĽ������Ҫ�Ľṹ��*/
typedef TAF_UINT8 TAF_PH_USIMM_NEED_TYPE;

#define TAF_PH_USIMM_NONEED     0   /*����Ҫ��֤*/
#define TAF_PH_USIMM_NEED       1   /*��Ҫ��֤*/
#define TAF_PH_USIMM_PUK        2   /* need verifer puk */
#define TAF_PH_USIMM_ADM        3   /* puk block */

typedef TAF_UINT8 TAF_PH_USIMM_ENABLE_FLG;
#define TAF_PH_USIMM_ENABLE     1   /*�Ѿ�ʹ��*/
#define TAF_PH_USIMM_UNENABLE   0   /*δʹ��*/

/*��ѯUSIM״̬API�������*/
/*��ѯ�����PIN���*/
typedef TAF_UINT8   TAF_OP_PIN_RESULT;
#define TAF_PH_OP_PIN_OK    0
#define TAF_PH_PIN_ERROR                    1
#define TAF_PH_QUERY_USIMM_WRONG_PARA       2
#define TAF_PH_QUERY_USIMM_NOAPP            3
#define TAF_PH_QUERY_USIMM_NOINITIAL        4
#define TAF_PH_QUERY_USIMM_ALLOCMEM_FAILED  5
#define TAF_PH_QUERY_USIMM_SENDMSG_FAILED   6
#define TAF_PH_OP_PIN_NEED_PIN1             7
#define TAF_PH_OP_PIN_NEED_PUK1             8
#define TAF_PH_OP_PIN_NEED_PIN2             9
#define TAF_PH_OP_PIN_NEED_PUK2             10
#define TAF_PH_OP_PIN_INCORRECT_PASSWORD    11
#define TAF_PH_OP_PIN_OPERATION_NOT_ALLOW   12
#define TAF_PH_OP_PIN_SIM_FAIL              13


typedef struct
{
    TAF_PH_USIMM_NEED_TYPE      UsimmNeedType;
    TAF_PH_USIMM_ENABLE_FLG     UsimmEnableFlg;
}TAF_PH_PIN_QUERY_CNF_STRU;

typedef struct
{
    TAF_UINT8                   ucResult;
}TAF_PH_PIN_OPERATION_CNF_STRU;

typedef struct
{
    TAF_UINT8 ucPin1RemainTime;    /* PIN1��ʣ����� */
    TAF_UINT8 ucPin2RemainTime;    /* PIN2��ʣ����� */
    TAF_UINT8 ucPuk1RemainTime;    /* PUK1��ʣ����� */
    TAF_UINT8 ucPuk2RemainTime;    /* PUK2��ʣ����� */
}TAF_PH_PIN_REMAIN;
/*������δ��ʼ���ǣ�Ϊ255*/
#define MMA_PIN_REMAINS_UNINIT             255

typedef struct
{
    TAF_OP_PIN_RESULT               OpPinResult;  /*PIN�����Ľ��*/
    TAF_PH_PIN_CMD_TYPE             CmdType;      /*��PIN�Ķ�������*/
    TAF_PH_PIN_TYPE                 PinType;      /*��ѯ�����PIN����*/
    TAF_UINT8                       ucRemain;     /*��PIN����ʣ�����*/
    TAF_PH_PIN_QUERY_CNF_STRU       QueryResult;  /*��ѯPIN���ؽ��*/
    TAF_PH_PIN_REMAIN               RemainTime;   /*����PIN���ʣ�����*/
}TAF_PH_PIN_CNF_STRU;

typedef struct
{
    TAF_OP_PIN_RESULT               OpPinResult;  /*PIN�����Ľ��*/
    TAF_PH_PIN_CMD_TYPE             CmdType;      /*��PIN�Ķ�������*/
    TAF_PH_PIN_TYPE                 PinType;              /*��ѯ�����PIN����*/
    TAF_UINT8                       ucPIN1Remain;     /*��PIN����ʣ�����*/
    TAF_UINT8                       ucPUK1Remain;
    TAF_UINT8                       ucPIN2Remain;
    TAF_UINT8                       ucPUK2Remain;
    TAF_PH_PIN_QUERY_CNF_STRU       QueryResult;  /*��ѯPIN���ؽ��*/
}TAF_PH_PIN_TIMECNF_STRU;


typedef TAF_UINT32   TAF_FPLMN_OPERATE_TYPE;
#define TAF_PH_FPLMN_QUREY      0
#define TAF_PH_FPLMN_DEL_ALL    1
#define TAF_PH_FPLMN_DEL_ONE    2
#define TAF_PH_FPLMN_ADD_ONE    3

typedef struct
{
    TAF_FPLMN_OPERATE_TYPE  ulCmdType;
    TAF_PLMN_ID_STRU        stPlmn;
}TAF_PH_FPLMN_OPERATE_STRU;

/*
USIM״̬�ṹ��
AT��ʱδ��MMA��ȡUSIM״̬��
��MMA����Ҳ��ҪUSIM״̬
*/
/*
0��     USIM��״̬��Ч
1:      USIM��״̬��Ч
2��     USIM��CS����Ч
3��     USIM��PS����Ч
4��     USIM��PS+CS�¾���Ч
255��   USIM��������
*/
typedef TAF_UINT8 TAF_USIM_STATUS;
#define TAF_PH_USIM_STATUS_UNAVAIL         0
#define TAF_PH_USIM_STATUS_AVAIL           1


#define TAF_PH_USIM_STATUS_CS_UNVAIL      2
#define TAF_PH_USIM_STATUS_PS_UNVAIL      3
#define TAF_PH_USIM_STATUS_CSPS_UNVAIL    4

#define TAF_PH_USIM_ROMSIM                240
#define TAF_PH_USIM_NON                   255
typedef struct
{
    /* Added by z40661 for V7R1 phase I , 2011-04-17, begin */
    VOS_UINT8                           aucImsi[NAS_MAX_IMSI_LENGTH];
    VOS_UINT8                           aucReserve[3];
    /* Added by z40661 for V7R1 phase I , 2011-04-17, end */
}TAF_USIM_STATUS_ST;


/*��ȡ��Ӫ����Ϣ���ɻ���AT�����COPS��*/
typedef TAF_UINT8 TAF_PH_NETWORKNAME_FORMAT;
#define TAF_PH_NETWORKNAME_LONG          0
#define TAF_PH_NETWORKNAME_SHORT         1
#define TAF_PH_NETWORKNAME_NUMBER        2
#define TAF_PH_NETWORKNAME_ALL           4
/*
��ǰע������״̬��ʶ
  0:δ֪��
  1:���õ�
  2:��ǰע��
  3:��ֹ
*/
typedef TAF_UINT8 TAF_PH_NETWORK_STATUS_FLAG;
#define TAF_PH_NETWORK_STATUS_UNKNOW       0
#define TAF_PH_NETWORK_STATUS_AVAILIBLE    1
#define TAF_PH_NETWORK_STATUS_CURRENT      2
#define TAF_PH_NETWORK_STATUS_FORBIDDEN    3


typedef TAF_UINT8 TAF_PH_RA_MODE;           /*����ģʽ*/
#define TAF_PH_RA_GSM                      0
#define TAF_PH_RA_WCDMA                    1
#define TAF_PH_RA_LTE                      2
#define TAF_PH_RA_MODE_DEFAULT             3
#define TAF_NAMELENGTH_MAX                 32

/* STK���� Access Technology Change Event ��غ궨�� */
#define TAF_STK_ACC_TECH_GSM               0
#define TAF_STK_ACC_TECH_TIA_EIA_553       1
#define TAF_STK_ACC_TECH_TIA_EIA_136       2
#define TAF_STK_ACC_TECH_UTRAN             3
#define TAF_STK_ACC_TECH_TETRA             4
#define TAF_STK_ACC_TECH_TIA_EIA_95        5
#define TAF_STK_ACC_TECH_TIA_EIA_IS_2000   6

/* NV���Ƿ񼤻�ָʾ */
#define NV_ITEM_DEACTIVE           0
#define NV_ITEM_ACTIVE             1



/*��ȡ������PLMN�б��ϱ�*/
#define TAF_PH_OPER_NAME_LONG                   40
#define TAF_PH_OPER_NAME_SHORT                  36
#define TAF_PH_PLMN_LIST_MAX                    32
/*#define TAF_PH_OPER_NAME_PLMN_ID_LENGTH         8*/
#define TAF_PH_STORED_OPER_NAME_NUM_IN_NVIM     3
typedef struct
{
    TAF_PLMN_ID_STRU            PlmnId;
    TAF_CHAR                    aucOperatorNameShort[TAF_PH_OPER_NAME_SHORT ];
    TAF_CHAR                    aucOperatorNameLong[TAF_PH_OPER_NAME_LONG ];
}TAF_PH_OPERATOR_NAME_STRU;


typedef TAF_UINT8    TAF_PH_GET_OPERATOR_INFO_OP;
#define TAF_PH_OPER_NAME_PLMN2ALPHANUMERICNAME         0
#define TAF_PH_OPER_NAME_SHORTNAME2OTHERS              1
#define TAF_PH_OPER_NAME_LONGNAME2OTERS                2
#define TAF_PH_OPER_NAME_ERROROP                       3

typedef struct
{
    TAF_PH_OPERATOR_NAME_STRU             OperName;
    TAF_PH_GET_OPERATOR_INFO_OP           ListOp;
}TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU;

typedef TAF_UINT8 TAF_PH_PLMN_SEL_MODE;               /*PLMN selection mode     */
#define TAF_PH_PLMN_SEL_MODE_AUTO                   0   /*automatic selection mode*/
#define TAF_PH_PLMN_SEL_MODE_MANUAL                 1   /*manual selection mode   */
#define TAF_PH_PLMN_SEL_MODE_BUTT                   (0xFF)


typedef struct
{
    TAF_PH_OPERATOR_NAME_STRU       Name;
    TAF_PH_NETWORKNAME_FORMAT       NameFormat;  /*������Ӫ�����ָ�ʽ*/
    TAF_PH_RA_MODE                  RaMode;      /*���߽���ģʽ,3G/2G*/
    TAF_PH_PLMN_SEL_MODE            PlmnSelMode; /*PLMN selection mode*/
}TAF_PH_NETWORKNAME_STRU;

typedef struct
{
    TAF_PH_NETWORK_STATUS_FLAG   Status;
    TAF_PLMN_ID_STRU             Plmn;
    TAF_PH_RA_MODE               RaMode;
}TAF_PLMN_INFO_STRU;

/*�ϱ���ǰС������PLMN�б���״̬*/
typedef struct
{
    TAF_UINT8                     ucOperatorNums;
    TAF_PH_OPERATOR_NAME_STRU     aOperatorInfo[TAF_PH_PLMN_LIST_MAX];
}TAF_PH_OPERATORS_INFO_LIST_STRU;

/*��ȡbandֵ����MS��RACIEZ�л��*/
/*
  80��CM_BAND_PREF_GSM_DCS_1800��              GSM DCS systems
  100��CM_BAND_PREF_GSM_EGSM_900��             Extended GSM 900
  200��CM_BAND_PREF_GSM_PGSM_900��             Primary GSM 900
  100000��CM_BAND_PREF_GSM_RGSM_900��          GSM Railway GSM 900
  200000��CM_BAND_PREF_GSM_PCS_1900��          GSM PCS
  400000��CM_BAND_PREF_WCDMA_I_IMT_2000��      WCDMA IMT 2000
  3FFFFFFF��CM_BAND_PREF_ANY��                 �κ�Ƶ��
  40000000��CM_BAND_PREF_NO_CHANGE��           Ƶ�����仯
*/
typedef struct
{
    TAF_UINT32 ulBandLow; /*��32λ*/
    TAF_UINT32 ulBandHigh;/*��32λ*/
} TAF_USER_SET_PREF_BAND64;

typedef TAF_UINT32 TAF_PH_PREF_BAND;

#define TAF_PH_BAND_GSM_DCS_1800                             0x00000080
#define TAF_PH_BAND_GSM_EGSM_900                             0x00000100
#define TAF_PH_BAND_GSM_PGSM_900                             0x00000200
#define TAF_PH_BAND_WCDMA_VII_2600                           0x00010000
#define TAF_PH_BAND_WCDMA_VIII_900                           0x00020000
#define TAF_PH_BAND_WCDMA_IX_1700                            0x00040000
#define TAF_PH_BAND_GSM_850                                  0x00080000
#define TAF_PH_BAND_GSM_RGSM_900                             0x00100000
#define TAF_PH_BAND_GSM_PCS_1900                             0x00200000
#define TAF_PH_BAND_WCDMA_I_IMT_2100                         0x00400000
#define TAF_PH_BAND_WCDMA_II_PCS_1900                        0x00800000
#define TAF_PH_BAND_WCDMA_III_1800                           0x01000000
#define TAF_PH_BAND_WCDMA_IV_1700                            0x02000000
#define TAF_PH_BAND_WCDMA_V_850                              0x04000000
#define TAF_PH_BAND_WCDMA_VI_800                             0x08000000
#define TAF_PH_BAND_WCDMA_XI_1500                            0x20000000
/* ���Ӷ�BAND19��֧�� */
#define TAF_PH_BAND_WCDMA_XIX_850                            0x10000000
#define TAF_PH_BAND_ANY                                      0x3FFFFFFF
#define TAF_PH_BAND_NO_CHANGE                                0x40000000

#define MN_MMA_LTE_HIGH_BAND_ANY        (0x7FFFFFFF)
#define MN_MMA_LTE_LOW_BAND_ANY         (0xFFFFFFFF)

#if (FEATURE_OFF == MBB_WPG_COMMON)
#define MN_MMA_LTE_EUTRAN_BAND1         (0x1)
#define MN_MMA_LTE_EUTRAN_BAND7         (0x40)
#define MN_MMA_LTE_EUTRAN_BAND13        (0x1000)
#define MN_MMA_LTE_EUTRAN_BAND17        (0x10000)
#define MN_MMA_LTE_EUTRAN_BAND40        (0x80)

#define MN_MMA_LTE_LOW_BAND_ALL         (MN_MMA_LTE_EUTRAN_BAND1 | MN_MMA_LTE_EUTRAN_BAND7 \
                                         | MN_MMA_LTE_EUTRAN_BAND13 | MN_MMA_LTE_EUTRAN_BAND17)

#define MN_MMA_LTE_HIGH_BAND_ALL        (MN_MMA_LTE_EUTRAN_BAND40)
#endif

/* ����BAND6,BAND19��֧�� */
#define TAF_PH_BAND_WCDMA_BAND_ALL           ( TAF_PH_BAND_WCDMA_I_IMT_2100 \
                                              | TAF_PH_BAND_WCDMA_II_PCS_1900 | TAF_PH_BAND_WCDMA_IV_1700 \
                                              | TAF_PH_BAND_WCDMA_V_850 | TAF_PH_BAND_WCDMA_VI_800 \
											  | TAF_PH_BAND_WCDMA_VIII_900 | TAF_PH_BAND_WCDMA_XI_1500 \
											  | TAF_PH_BAND_WCDMA_XIX_850)
#define TAF_PH_BAND_GSM_BAND_ALL             ( TAF_PH_BAND_GSM_DCS_1800  | TAF_PH_BAND_GSM_EGSM_900  \
                                               |TAF_PH_BAND_GSM_PGSM_900 | TAF_PH_BAND_GSM_850       \
                                               | TAF_PH_BAND_GSM_PCS_1900 )

#define TAF_PH_BAND_ALL                       (TAF_PH_BAND_WCDMA_BAND_ALL | TAF_PH_BAND_GSM_BAND_ALL)



/*���ڷ���SYSCFG=?��Ƶ�η���1�ķ�Χ*/

#define TAF_PH_BAND_GSM_900   ( TAF_PH_BAND_GSM_EGSM_900 | TAF_PH_BAND_GSM_PGSM_900 )

/* ���Ӷ�BAND19��֧�� */
#define TAF_PH_BAND_GROUP1_FOR_SYSCFG    ( TAF_PH_BAND_WCDMA_I_IMT_2100 | TAF_PH_BAND_WCDMA_VIII_900 \
                                          | TAF_PH_BAND_WCDMA_IX_1700 | TAF_PH_BAND_WCDMA_VI_800     \
                                          | TAF_PH_BAND_GSM_DCS_1800 | TAF_PH_BAND_GSM_EGSM_900      \
                                          | TAF_PH_BAND_GSM_PGSM_900 | TAF_PH_BAND_WCDMA_XI_1500 	 \
										  | TAF_PH_BAND_WCDMA_XIX_850 )
/*���ڷ���SYSCFG=?��Ƶ�η���2�ķ�Χ*/
#define TAF_PH_BAND_GROUP2_FOR_SYSCFG    ( TAF_PH_BAND_WCDMA_II_PCS_1900  \
                                          | TAF_PH_BAND_WCDMA_IV_1700 | TAF_PH_BAND_WCDMA_V_850 \
                                          | TAF_PH_BAND_GSM_PCS_1900 | TAF_PH_BAND_GSM_850 )

/* ��Ҫ��64λ��32λת����Ƶ�� */
#define TAF_PH_BAND_NEED_CHANGE_TO_64BIT    ( TAF_PH_BAND_WCDMA_VIII_900 | TAF_PH_BAND_WCDMA_IX_1700 | TAF_PH_BAND_WCDMA_XI_1500 | TAF_PH_BAND_WCDMA_XIX_850)
typedef struct
{
     TAF_PH_PREF_BAND                             BandMask;             /*Ƶ������*/
     TAF_CHAR*                                    BandStr;              /*Ƶ���ַ���*/
}TAF_PH_BAND_NAME_STRU;

#define TAF_DEVICE_AT_MAX_W_BAND_NUM   9  /*��ǰ�û������õ�WƵ�η�Χ��*/

/*����֧��ѡ��0��1��ʹ�ã�ֻʹ��δ�仯��2��*/
typedef TAF_UINT8 TAF_PH_ROAM_MODE;
#define TAF_PH_ROAM_NATIONAL_ON_INTERNATIONAL_ON        0
#define TAF_PH_ROAM_NATIONAL_ON_INTERNATIONAL_OFF       1
#define TAF_PH_ROAM_NATIONAL_OFF_INTERNATIONAL_ON       2
#define TAF_PH_ROAM_NATIONAL_OFF_INTERNATIONAL_OFF      3
#define TAF_PH_ROAM_UNCHANGE          4


enum MN_MMA_ROAM_MODE_ENUM
{
    MN_MMA_ROAM_NATIONAL_ON_INTERNATIONAL_ON,                                   /* �������ڹ������� */
    MN_MMA_ROAM_NATIONAL_ON_INTERNATIONAL_OFF,                                  /* �����������Σ��رչ������� */
    MN_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON,                                  /* �رչ������Σ������������� */
    MN_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_OFF,                                 /* �رչ��ڹ������� */
    MN_MMA_ROAM_UNCHANGE,                                                       /* ��������δ�ı� */
    MN_MMA_ROAM_BUTT
};
typedef VOS_UINT8 MN_MMA_ROAM_MODE_ENUM_UINT8;

/*����״̬*/
typedef TAF_UINT8 TAF_PH_ROAM_STA;
#define TAF_PH_ROAMING               0
#define TAF_PH_NO_ROAM               1
#define TAF_PH_ROAM_UNKNOW           2

#if(FEATURE_ON == MBB_FEATURE_CELLROAM)
#define TAF_PH_DOMESTIC_CUST         1
#define TAF_PH_FOREIGN_CUST          2
#define TAF_PH_ROAM_UNKNOW_CUST      0
typedef struct
{
    TAF_PH_RA_MODE                  RaMode;                                     /*���߽���ģʽ,3G/2G*/
    TAF_PH_ROAM_STA                 RoamMode;                                   /*ROAM mode*/
}TAF_PH_CELLROAM_STRU;
#endif/*MBB_FEATURE_CELLROAM*/



/*------------    ��״̬��־��     ------------*/
/*��״̬��־��������*/
/*
  0��    �޷���
  1��    ��CS����
  2��    ��PS����
  3��    PS+CS����
  4��    CS��PS��δע�ᣬ����������״̬
*/
typedef TAF_UINT8 TAF_PH_DOMAIN_FLAG;

typedef struct
{
     TAF_PH_PREF_BAND                             PhBand;              /*Ƶ������*/
     TAF_PH_DOMAIN_FLAG                           DomainFlag;           /*��״̬��־*/
     TAF_PH_ROAM_MODE                             RoamMode;             /*����ѡ��*/
     /*ֻ��,����д,��ȡ��ǰ����״̬*/
     TAF_PH_ROAM_STA                              RoamSta;
}TAF_PH_SYSTEM_MODE_STRU;

/*��USIM��spn�ļ��л�ȡ����Ϣ�ṹ��*/
typedef TAF_UINT8 TAF_PH_SPN_TYPE;
#define TAF_PH_GSM_SPN          0
#define TAF_PH_USIM_SPN         1
#define TAF_PH_SPN_TYPE_UNKNOW  2

typedef TAF_UINT8 TAF_PH_SPN_DISP_MODE;

typedef TAF_UINT8 TAF_PH_SPN_CODING;
#define TAF_PH_GSM_7BIT_DEFAULT       0
#define TAF_PH_RAW_MODE               1
#define TAF_PH_SPN_CODING_UNKNOW      255


#define TAF_PH_SPN_NAME_MAXLEN        16
/*������AT�����ȡSPN�ļ���Ӧ*/
typedef struct
{
          TAF_PH_SPN_TYPE                   SpnType;
          TAF_PH_SPN_DISP_MODE              DispRplmnMode;
          TAF_PH_SPN_CODING                 SpnCoding;
          TAF_UINT8                         aucSpnName[TAF_PH_SPN_NAME_MAXLEN + 1];
}TAF_PH_USIM_SPN_STRU;

/*USIM��SPN�ļ�����*/
typedef struct
{
    TAF_UINT8         ucDispRplmnMode;
    TAF_UINT8         aucSpnName[TAF_PH_SPN_NAME_MAXLEN];
}TAF_PH_USIM_SPN_CNF_STRU;

/* �ϱ���Ӧ�ò��SPN��Ϣ */
typedef struct
{
    TAF_PH_SPN_DISP_MODE DispRplmnMode;
    TAF_PH_ROAM_STA   PhRoam;
    TAF_UINT8         aucSpnName[TAF_PH_SPN_NAME_MAXLEN];
}TAF_PH_SPN_INFO_STRU;

#define FULL_NAME_IEI       0x43
#define SHORT_NAME_IEI      0x45
#define PLMN_ADDITIONAL_INFO_IEI      0x80

typedef struct
{
    VOS_BOOL                bCPHSOperNameValid;
    VOS_UINT8               aucCPHSOperNameStr[TAF_PH_OPER_NAME_LONG + 1];
}TAF_PH_SIM_CPHS_OPER_NAME_STRU;


typedef struct
{
    TAF_UINT8       PNN[80];
}TAF_PH_USIM_PNN_RECORD;

typedef TAF_UINT8 TAF_PH_ICC_TYPE;
#define TAF_PH_ICC_UNKNOW   0
#define TAF_PH_ICC_SIM      1
#define TAF_PH_ICC_USIM     2

typedef struct
{
    TAF_UINT32              CardType;
    TAF_UINT32              TotalRecordNum;
    TAF_UINT32              RecordLen;
    VOS_UINT16              usPnnCurrIndex; /* ��ѯPNN����ʼλ�� */
    TAF_PH_ICC_TYPE         Icctype;
    VOS_UINT8               aucReserve[1];
    TAF_PH_USIM_PNN_RECORD  PNNRecord[1];
}TAF_PH_USIM_PNN_CNF_STRU;

typedef struct
{
    TAF_UINT16              PlmnLen;
    TAF_UINT8               PLMN[6];
    TAF_UINT16              LACLow;
    TAF_UINT16              LACHigh;
    TAF_UINT16              PNNIndex;
}TAF_PH_USIM_OPL_RECORD;

typedef struct
{
    TAF_UINT32              CardType;
    TAF_UINT32              TotalRecordNum;
    TAF_UINT32              RecordLen;
    TAF_PH_USIM_OPL_RECORD  OPLRecord[1];
}TAF_PH_USIM_OPL_CNF_STRU;

typedef struct
{
    TAF_PH_USIM_PNN_CNF_STRU *pstPnnCnf;
    TAF_PH_USIM_OPL_CNF_STRU *pstOplCnf;
}TAF_PH_USIM_CPNN_CNF_STRU;


/*С����Ϣ*/
#define TAFMMA_CELL_MAX_NUM    8
typedef struct
{
    TAF_UINT8    ucCellNum;
    TAF_UINT32   aulCellId[TAFMMA_CELL_MAX_NUM];
}TAF_CELL_INFO_STRU;

typedef struct
{
    TAF_UINT32                          OP_CsRegState      : 1;
    TAF_UINT32                          OP_PsRegState      : 1;
    TAF_UINT32                          OP_ucAct           : 1;
    TAF_UINT32                          OP_Lac             : 1;
    TAF_UINT32                          OP_CellId          : 1;
    TAF_UINT32                          OP_Rac             : 1;
    TAF_UINT32                          OP_Plmn            : 1;
    TAF_UINT32                          OP_Spare           : 25;

    TAF_PH_REG_STATE_TYPE               RegState;               /*MMע��״̬*/
    TAF_PH_REG_STATE_TYPE               ucPsRegState;           /*PSע��״̬*/
    TAF_PH_ACCESS_TECH_ENUM_UINT8       ucAct;                  /*��ǰפ������Ľ��뼼��*/
    TAF_UINT16                          usLac;                  /*λ������Ϣ*/
    TAF_CELL_INFO_STRU                  CellId;                 /*С��ID*/
    TAF_UINT8                           ucRac;                  /*RAC*/
    TAF_PLMN_ID_STRU                    Plmn;                   /*�ṩPLMN��Ϣ����ǰδ������*/
}TAF_PH_REG_STATE_STRU;

/*����Ϣ��������NVIM����ȡ*/
typedef struct
{
    TAF_PH_IMEI_STRU                ImeisV;                 /*IMEISV*/
    TAF_PH_FMR_ID_STRU              FmrId;                  /*�ֻ����쳧����Ϣ*/
    TAF_PH_PRODUCT_NAME_STRU        ProductName;            /*��Ʒ����*/
    TAF_PH_MODEL_ID_STRU            ModelId;                /*�ֻ�Ӳ���汾��Ϣ*/
    TAF_PH_REVISION_ID_STRU         SoftVersion;            /*�ֻ�����汾��*/
    TAF_PH_RELEASE_DATE_STRU        ReleaseDate;            /*��������*/
    TAF_PH_RELEASE_TIME_STRU        ReleaseTime;            /*����ʱ��*/
    TAF_PH_COMPCAPLIST_STRU         CompleteCapitiyList;    /*���������б�*/
    TAF_PH_COMPCAPLIST_STRU         GsmCompleteCapitiyList; /*���������б�*/
}TAF_PH_MEINFO_STRU;

#define TAF_PH_SYSCFG_GROUP_BAND_LEN                256

typedef struct
{
    TAF_CHAR  strSysCfgBandGroup[TAF_PH_SYSCFG_GROUP_BAND_LEN];

}TAF_PH_SYSCFG_BAND_STR;


typedef struct
{
    TAF_PH_PRODUCT_NAME_STRU        ProductName;            /*���ݿ�����*/
    TAF_PH_FMR_ID_STRU              FmrId;                  /*�ֻ����쳧����Ϣ*/
    TAF_PH_PORT_INFO_STRU           PortId;                 /*���ݿ��˿ڷ�����Ϣ*/
}TAF_PH_PORT_STRU;


typedef struct
{
    TAF_PH_MT_STA_ENUM                enPhStat;             /*���^HS�����ʼ����ͱ���Ϊ����*/
    TAF_PH_PLMN_PRIO                  PlmnPrio;             /*ע�����ȼ�*/
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8   enAccessMode;           /*���õĽ���ģʽ*/
    TAF_PH_SRV_STA_STRU               PhSrvSta;           /*��ǰ�ֻ�����״̬*/
    TAF_PH_RSSI_STRU                  RssiValue;          /*�ź�ǿ�Ⱥ��ŵ�����*/
    TAF_PH_OP_MODE_STRU               PhOpMode;           /*�ֻ���ǰ����״̬*/
    TAF_PH_REG_STATE_STRU             PhRegSta;           /*�ֻ���ǰע��״̬*/
    TAF_PH_SYSTEM_MODE_STRU           PhSystemMode;       /*�ֻ�ϵͳģʽ��Ƶ�ʣ��������ã�����״̬�ȣ�*/
    TAF_PH_BATTERYPOWER_STRU          PhBatteryStatus;    /*�ֻ���Դ״̬*/
}TAF_PH_MS_STAT_STRU;

/*����Ϣ����������USIM��أ���USIM������ʱ��Ҫ��Ϊ��Чֵ*/
typedef struct
{
    TAF_USIM_STATUS_ST                UsimStatus;                               /*USIM״̬*/
    TAF_PH_USIM_SPN_STRU              UsimSpnInfo;                              /*USIM��SPN�ļ�����*/
    TAF_PH_USIM_SPN_STRU              SimSpnInfo;
    TAF_PH_SIM_CPHS_OPER_NAME_STRU    stSimCPHSOperName;
}TAF_USIM_INFO_STRU;

typedef struct
{
    TAF_PH_MEINFO_STRU           MeInfo;          /*�ն���Ϣ*/
    TAF_PH_MS_STAT_STRU          MsStatus;        /*�ֻ���ǰ����״̬*/
    TAF_USIM_INFO_STRU           UsimInfo;        /*USIM�����Ϣ*/
}TAF_AT_DATA_STRU;

/*Taf_PhoneNetworkOperate*/
typedef TAF_UINT8 TAF_AVAIL_PLMN_LIST_TYPE;
#define TAF_PLMN_LIST        0       /*��������PLMN����*/
#define TAF_PLMN_LIST_ABORT  1       /*��ֹ����PLMN����*/


typedef TAF_UINT8 TAF_PLMN_RESEL_MODE_TYPE;
#define TAF_PLMN_RESELETION_AUTO        0     /*PLMN��ѡ���Զ�*/
#define TAF_PLMN_RESELETION_MANUAL      1     /*PLMN��ѡ���ֹ�*/
#if( FEATURE_ON == MBB_WPG_COMMON )
#define TAF_PLMN_RESELETION_MANUAL_AUTO      4     /*PLMN��ѡ���ֹ�-�Զ�*/
#endif

typedef struct
{
    TAF_PH_NETWORK_STATUS_FLAG         PlmnStatus;
    TAF_PH_RA_MODE                     RaMode;      /*���߽���ģʽ,3G/2G*/
}TAF_PLMN_STATUS_STRU;

typedef TAF_UINT8 AT_COPS_FORMAT_TYPE;
#define AT_COPS_LONG_ALPH_TYPE            0
#define AT_COPS_SHORT_ALPH_TYPE           1
#define AT_COPS_NUMERIC_TYPE              2


typedef struct
{
    AT_COPS_FORMAT_TYPE         ucFormatType;
    TAF_PH_RA_MODE              ucAccessMode;
    VOS_UINT16                  usOperNameLen;
    VOS_CHAR                    ucOperName[TAF_PH_OPER_NAME_LONG];
#if( FEATURE_ON == MBB_WPG_COMMON )
    TAF_PLMN_RESEL_MODE_TYPE    ucReselMode;
#endif
}TAF_PLMN_USER_SEL_STRU;


typedef struct
{
    VOS_UINT8           ucDomain;
    TAF_PH_CS_STATUS    ucCsState;
    TAF_PH_PS_STATUS    ucPsState;
    VOS_UINT8           aucReserved[1];
}TAF_DOMAIN_ATTACH_STATE_STRU;


/*����һ��PLMN NAME��������������100�ֽ����ң����˼�ͨ�Ż������Ϊ4K������ֻ�ܴ��36������PLMN NAME*/
#define MAX_PLMN_NAME_LIST   37
typedef struct
{
    TAF_UINT32                  ulPlmnNum;
    VOS_BOOL                    bPlmnSelFlg;
    TAF_PH_OPERATOR_NAME_STRU   astPlmnName[MAX_PLMN_NAME_LIST];
    TAF_MMC_USIM_RAT            ausPlmnRat[MAX_PLMN_NAME_LIST];
}TAF_PLMN_NAME_LIST_STRU;


#define TAF_MAX_PLMN_NUM       37
typedef struct
{
    TAF_UINT8          ucPlmnNum;
    TAF_PLMN_ID_STRU   Plmn[TAF_MAX_PLMN_NUM];
    TAF_PLMN_STATUS_STRU PlmnInfo[TAF_MAX_PLMN_NUM];
}TAF_PLMN_LIST_STRU;

/*   ȡMMC_MAX_OPLMN_NUM  NAS_MMC_MAX_UPLMN_NUM MMC_MAX_SELPLMN_NUM
     MMC_MAX_HPLMN_WITH_ACT_NUM                           �е����ֵ */
#define TAF_USER_MAX_PLMN_NUM        256
typedef struct
{
    TAF_UINT16           usPlmnNum;
    TAF_UINT8            aucReserved[2];
    TAF_PLMN_ID_STRU     Plmn[TAF_USER_MAX_PLMN_NUM];
    TAF_MMC_USIM_RAT     PlmnRat[TAF_USER_MAX_PLMN_NUM];
}TAF_USER_PLMN_LIST_STRU;

typedef struct
{
    TAF_UINT8            ucIndex;
    TAF_PLMN_ID_STRU     Plmn;
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8      PlmnRat;
}TAF_USER_PLMN_INFO_STRU;



typedef struct
{
    TAF_UINT8       ucLen;
    TAF_UINT8       aucCommand[USIMM_T0_APDU_MAX_LEN];
}TAF_PH_USIM_COMMAND_STRU;


/* ucActionType��ȡֵ */
#define TAF_START_EVENT_INFO_FOREVER    0   /* ָʾ�����ϱ����� */
#define TAF_START_EVENT_INFO_ONCE       1   /* ָʾ�ϱ����һ�� */
#define TAF_START_EVENT_INFO_STOP       2   /* ָʾֹͣ�ϱ� */

/* ucMsgType��ȡֵ */
#define TAF_EVENT_INFO_CELL_SIGN        1   /* ��ʾ��ȡС���ź�ǿ�� */
#define TAF_EVENT_INFO_CELL_ID          2   /* ��ʾ��ȡС��ID */
#define TAF_EVENT_INFO_CELL_BLER        4   /* ��ʾ��ȡ�ŵ������� */

/* �����¼������ϱ���Ϣ�Ľṹ�� */
typedef struct
{
    TAF_UINT8              ucActionType;
    TAF_UINT8              ucRrcMsgType;

    VOS_UINT8              ucSignThreshold;    /* 1:rssi�仯����1db�����ϱ�^cerssi; 2:rssi�仯����2db�����ϱ�
                                        3:rssi�仯����3db�����ϱ���4:rssi�仯����4db�����ϱ���5:rssi�仯����5db�����ϱ�;*/
    VOS_UINT8              ucMinRptTimerInterval;   /*�ϱ��ļ��ʱ��(1-20)S*/
}TAF_START_INFO_IND_STRU;


/*������ѯ����ϱ��ص�����*/
typedef struct
{
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     AccessMode;
    TAF_PH_PLMN_PRIO                    PlmnPrio;
}TAF_ACCESS_MODE_QUERY_PARA_STRU;

typedef struct
{
    TAF_UINT16    usHighFreq;
    TAF_UINT16    usLowFreq;
}TAF_PH_FREQ_INFO_STRU;

/*Ƶ����Ϣ�ṹ��*/
typedef struct
{
    TAF_UINT32              ulGsmFreq;
    TAF_PH_FREQ_INFO_STRU   WcdmaFrq;
}TAF_PH_FRQ_STRU;

#define TAF_PH_ICC_ID_MAX 10
typedef struct
{
    TAF_UINT8 ucLen;
    TAF_UINT8 aucIccId[TAF_PH_ICC_ID_MAX + 1];
}TAF_PH_ICC_ID_STRU;

/*    ucSrvStatusȡֵ���£� */
#define  TAF_PH_INFO_NO_SERV            0/*�޷���*/
#define  TAF_PH_INFO_LIMT_SERV          1/*�����Ʒ���*/
#define  TAF_PH_INFO_NOMRL_SERV         2/*������Ч*/
#define  TAF_PH_INFO_LIMT_REGON_SERV    3/*�����Ƶ��������*/
#define  TAF_PH_INFO_DEEP_SLEEP         4/*ʡ�����˯״̬*/
/*    ucSrvDomainȡֵ���£�*/
#define  TAF_PH_INFO_NO_DOMAIN          0/*�޷���*/
#define  TAF_PH_INFO_ONLY_CS            1/*��CS����*/
#define  TAF_PH_INFO_ONLY_PS            2/*��PS����*/
#define  TAF_PH_INFO_DUAL_DOMAIN        3/*PS+CS����*/
#define  TAF_PH_INFO_SEARCH_DOMAIN      4/*CS��PS��δע�ᣬ����������״̬  */
/*    ucRoamStatusȡֵ���£�*/
#define  TAF_PH_INFO_NONE_ROMAING       0/*������״̬*/
#define  TAF_PH_INFO_ROMAING            1/*����״̬*/
#define  TAF_PH_INFO_ROAM_UNKNOW        2/*δ֪״̬*/

typedef TAF_UINT8 TAF_PH_INFO_RAT_TYPE;
/*ucSysModeȡֵ���£�*/
#define  TAF_PH_INFO_NONE_RAT           0/*�޷���*/
#define  TAF_PH_INFO_GSM_RAT            3/*GSM/GPRSģʽ*/
#define  TAF_PH_INFO_WCDMA_RAT          5/*WCDMAģʽ*/
#define  TAF_PH_INFO_LTE_RAT            7/*LTEģʽ*/

#define  TAF_PH_INFO_TD_SCDMA_RAT       15/*TD-SCDMAģʽ*/


/*    ucSimStatusȡֵ���� */
#define  TAF_PH_INFO_USIM_PIN_INVAILD   0/*USIM��״̬��Ч����PIN��û��У������*/
#define  TAF_PH_INFO_USIM_VAILD         1/*USIM��״̬��Ч*/
#define  TAF_PH_INFO_USIM_CS_INVAILD    2/*USIM��CS����Ч*/
#define  TAF_PH_INFO_USIM_PS_INVAILD    3/*USIM��PS����Ч*/
#define  TAF_PH_INFO_USIM_INVAILD       4/*USIM��PS+CS�¾���Ч*/
#define  TAF_PH_INFO_USIM_ABSENT        255/*USIM��������*/

typedef struct
{
    TAF_UINT8                 ucSrvStatus;        /*����״̬����֧��ȡֵ0,1,2*/
    TAF_UINT8                 ucSrvDomain;        /*������*/
    TAF_UINT8                 ucRoamStatus;       /*����״̬��������PLMN ID��ͬ����*/
    TAF_UINT8                 ucSysMode;          /*ϵͳģʽ*/
    TAF_UINT8                 ucSimStatus;        /*SIM��״̬*/
    TAF_UINT8                 ucSysSubMode;       /*ϵͳ��ģʽ*/
    TAF_UINT8                 ucSimLockStatus;    /*SIM����LOCK״̬*/
}TAF_PH_SYSINFO_STRU;

typedef struct
{
    TAF_UINT8            RatType;
    TAF_UINT8            GsmBand;
    TAF_UINT16           IndFreq;
}TAF_IND_FREQ_STRU;

#define TAF_MAX_USIM_RSP_LEN    255
typedef struct
{
    TAF_UINT8  ucLen;
    TAF_UINT8  aucResponse[TAF_MAX_USIM_RSP_LEN];
}TAF_PH_USIM_RESPONSE_STRU;

/* ϵͳ�������ݽṹ */
typedef struct
{
    TAF_PH_CMD_TYPE                     CmdType;
    MN_MMA_CPAM_RAT_TYPE_ENUM_UINT8     AccessMode;
    TAF_PH_PLMN_PRIO                    PlmnPrio;
    TAF_PH_ROAM_MODE                    Roam;
    TAF_PH_PREF_BAND                    Band;
    TAF_PH_SERVICE_DOMAIN               SrvDomain;
    TAF_USER_SET_PREF_BAND64            stOrigUserSetBand;
}TAF_PH_SYS_CFG_STRU;


typedef TAF_UINT8 TAF_PH_PIN_STATUS;
#define TAF_PH_PIN_ENABLE   0
#define TAF_PH_PIN_DISABLE  1

typedef TAF_UINT8 TAF_PH_PIN_VERIFY_STATUS;
#define TAF_PH_PIN_NEED     0
#define TAF_PH_PIN_NONEED   1
#define TAF_PH_PIN_PUK      2
typedef TAF_UINT8 TAF_PH_ME_LOCK_STATUS;
#define TAF_PH_ME_SIM_UNLOCK    0
#define TAF_PH_ME_SIM_LOCK      1
#define TAF_PH_ME_NO_SIM        2

typedef struct
{
    TAF_PH_ICC_TYPE           MmaIccType;
    TAF_PH_PIN_STATUS         MmaIccPinStatus;
    TAF_PH_PIN_VERIFY_STATUS  MmaIccPinVerifyStatus;
    TAF_UINT8                 ucRemainTimes;
}TAF_PH_UICC_TYPE;

typedef enum
{
    MN_PH_PREF_PLMN_UPLMN,
    MN_PH_PREF_PLMN_OPLMN,
    MN_PH_PREF_PLMN_HPLMN
}MN_PH_PREF_PLMN_ID_ENUM;
typedef VOS_UINT8 MN_PH_PREF_PLMN_TYPE_ENUM_U8;

typedef enum
{
    MN_PH_PrefPLMN_QUREY,
    MN_PH_PrefPLMN_DEL_ONE,
    MN_PH_PrefPLMN_ADD_ONE,
    MN_PH_PrefPLMN_MODIFY_ONE
} MN_PH_PrefPLMN_OPERATE_TYPE;
typedef VOS_UINT8 MN_PH_PrefPLMN_OPERATE_TYPE_U8;

typedef struct
{
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType;
    MN_PH_PrefPLMN_OPERATE_TYPE_U8      enPrefPlmnOperType;
    TAF_MMC_USIM_RAT                    usRat;                                  /* USIM��ʽ�� ���뼼�� */
    VOS_UINT32                          ulIndex;
    TAF_PLMN_ID_STRU                    stPlmn;
} TAF_PH_PREF_PLMN_OPERATE_STRU;


typedef struct
{
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType;                     /* ѡ�е����ȼ������б�����*/
    VOS_UINT8                           ucAtParaIndex;                      /* �������� */
    VOS_UINT16                          usIndexLen;                         /* ���������ĳ���*/
    VOS_UINT16                          usFormatLen;                        /* ���������͵ĳ���*/
    VOS_UINT16                          usOperNameLen;                      /* ��Ӫ�����ֵĳ���*/
    VOS_UINT16                          usGsmRatLen;                        /* GSM���뼼���ĳ���*/
    VOS_UINT16                          usGsmCompactRatLen;                 /* GSM COMPACT���뼼���ĳ���*/
    VOS_UINT16                          usUtrnLen;                          /* UTRN���뼼���ĳ��� */
    VOS_UINT16                          usReserve;                          /* �����ֶ�*/
    VOS_UINT32                          usIndex;                            /* ����ֵ*/
    VOS_UINT32                          usFormat;                           /* ��������ֵ*/
    VOS_CHAR                            ucOperName[TAF_PH_OPER_NAME_LONG];  /* ��Ӫ����*/
    VOS_UINT32                          usGsmRat;                           /* GSM���뼼��ֵ*/
    VOS_UINT32                          usGsmCompactRat;                    /* GSM COMPACK���뼼��ֵ*/
    VOS_UINT32                          usUtrn;                             /* UTRN���뼼��ֵ*/
    VOS_UINT16                          usEutrnLen;                         /* E-UTRN���뼼���ĳ��� */
    VOS_UINT32                          usEutrn;                            /* E-UTRN���뼼��ֵ*/
} TAF_PH_SET_PREFPLMN_STRU;


typedef struct
{
    VOS_UINT8   aucPara0[TAF_PH_UNLOCKCODELEN];         /* �������ý������Ĳ����ַ��� */
    VOS_UINT16  usPara0Len;                             /* ������ʶ�����ַ������� */
    VOS_UINT8   aucPara1[TAF_PH_PINCODELENMAX];         /* �������ý������Ĳ����ַ��� */
    VOS_UINT16  usPara1Len;                             /* ������ʶ�����ַ������� */
}MN_PH_SET_CPIN_REQ_STRU;

typedef enum
{
    TAF_PH_PNN_FILE,
    TAF_PH_OPL_FILE,
    TAF_PH_MAX_FILE
}TAF_PH_USIM_FILE_ENUM;
typedef VOS_UINT16 TAF_PH_USIM_FILE_ENUM_U16;

#define TAF_PH_INVALID_USIM_REC             0xFFFFFFFF


typedef struct
{
    VOS_UINT16                          usPnnCurrIndex; /* ��ѯPNN����ʼλ�� */
    VOS_UINT16                          usPnnNum;       /* ��ѯPNN�ĸ���������A�˺�C��ͨѶ����Ϣ��С�����ƣ����һ������ѯ10����¼ */
}TAF_MMA_PNN_INFO_QUERY_REQ_INDEX_STRU;

typedef struct
{
    TAF_PH_ICC_TYPE                     Icctype;
    VOS_UINT8                           ucReserved;
    TAF_PH_USIM_FILE_ENUM_U16           enEfId;
    TAF_UINT32                          ulRecNum;
    TAF_MMA_PNN_INFO_QUERY_REQ_INDEX_STRU stPnnQryIndex;
}TAF_PH_QRY_USIM_INFO_STRU;

typedef struct
{
    TAF_PH_ICC_TYPE                     Icctype;
    VOS_UINT8                           aucReserved[3];
    VOS_BOOL                            bFileExist;
    TAF_UINT32                          ulTotalRecNum;
    TAF_UINT32                          ulRecordLen;
}TAF_PH_USIM_INFO_STRU;

typedef struct
{
    TAF_PH_USIM_INFO_STRU               stUsimInfo;
    TAF_PH_USIM_INFO_STRU               stSimInfo;
}TAF_PH_QRY_USIM_RANGE_INFO_STRU;

typedef TAF_UINT8 TAF_PH_ICC_STATUS;
#define TAF_PH_ICC_INVALID      0
#define TAF_PH_ICC_VALID        1
#define TAF_PH_ICC_CSINVALID    2
#define TAF_PH_ICC_PSINVALID    3
#define TAF_PH_ICC_CSPSINVALID  4
#define TAF_PH_ICC_NOTEXIT      255

/*PHONE�¼�����*/
typedef TAF_UINT8 TAF_PHONE_EVENT;
#define TAF_PH_EVT_ERR                      0   /*�¼�ͨ�ô���*/
#define TAF_PH_EVT_PLMN_LIST_ABORT_CNF      1   /*��ȡ����PLMN�б���ֹȷ����Ϣ*/
#define TAF_PH_EVT_PLMN_LIST_IND            2   /*PLMN�б������ϱ�ָʾ*/
#define TAF_PH_EVT_OPER_MODE_CNF            3  /* ����ģʽ */
#define TAF_PH_EVT_SYS_CFG_CNF              4  /* ϵͳ���� */
#define TAF_PH_EVT_PLMN_LIST_CNF            5   /*APP�����ȡPLMN�б�ȷ���¼�*/
#define TAF_PH_EVT_PLMN_LIST_REJ            6   /*�ܾ������ȡPLMN�б����*/
#define TAF_PH_EVT_PLMN_SEL_CNF             7   /*APPָ��PLMNѡ��ȷ����Ϣ*/
#define TAF_PH_EVT_PLMN_RESEL_CNF           8   /*APP�����PLMN��ѡȷ����Ϣ*/
#define TAF_PH_EVT_SERVICE_STATUS_IND       9   /*�����ϱ��²�ķ���״̬*/
#define TAF_PH_EVT_ATTACH_CNF               10  /*ͬʱ����������ʱ���ص�ȷ���¼�*/
#define TAF_PH_EVT_PS_ATTACH_CNF            11  /*����PS�򷵻ص�ȷ����Ϣ*/
#define TAF_PH_EVT_CS_ATTACH_CNF            12  /*����CS�򷵻ص�ȷ����Ϣ*/
#define TAF_PH_EVT_DETACH_CNF               13  /*ͬʱȥ���������򷵻ص�ȷ����Ϣ*/
#define TAF_PH_EVT_PS_DETACH_CNF            14  /*ȥ����PS�򷵻ص�ȷ����Ϣ*/
#define TAF_PH_EVT_CS_DETACH_CNF            15  /*ȥ����PS�򷵻ص�ȷ����Ϣ*/
#define TAF_PH_EVT_RSSI_CHANGE_IND          16  /*�ź�ǿ�ȱ仯ָʾ*/
#define TAF_PH_EVT_POWER_STA_IND            17  /*��Դ״ָ̬ʾ*/
#define TAF_PH_EVT_OP_PIN_CNF               18  /*����PIN�뷵�ؽ��*/
#define TAF_PH_EVT_SYSTEM_INFO_IND          19  /*ϵͳ��Ϣָʾ*/
#define TAF_PH_EVT_SETUP_SYSTEM_INFO_RSP    20  /*����ϵͳ��Ϣ�ϱ���־*/
#define TAF_PH_EVT_USIM_RESPONSE            21  /*��ȡ����USIM*/
#define TAF_PH_EVT_USIM_INFO_IND            22  /*��״̬��Ϣָʾ*/
#define TAF_PH_EVT_OP_PINREMAIN_CNF         23
#define TAF_PH_EVT_ME_PERSONALISATION_CNF   24  /*�ƶ��豸˽�в������ؽ��*/
#define TAF_PH_EVT_RESTRICTED_ACCESS_CNF    25  /*�����Ƶ�SIM���������ݷ���*/
#define TAF_PH_EVT_OPER_MODE_IND            26  /* ����ģʽ�仯�����ϱ� */
#define TAF_PH_EVT_MM_INFO_IND              27  /* MM INFO��Ϣ�ϱ� */
#define TAF_PH_EVT_MODE_CHANGE_IND          28  /* ^MODE��Ϣ�ϱ� */
#define MN_PH_EVT_SIMLOCKED_IND             29  /* SIMLOCK�ϱ� */
#define MN_PH_EVT_ROAMING_IND               30  /* ROAMING�ϱ� */
#define TAF_PH_EVT_GET_CURRENT_ATTACH_STATUS_CNF  31 /*��ȡ��ǰע��״̬�ظ���Ϣ*/
#define TAF_PH_EVT_MT_POWER_DOWN_CNF        32  /*MT�µ�����ظ���Ϣ*/
#define TAF_PH_EVT_SET_PREF_PLMN_CNF        33  /*�������ȼ������б��ļ��ظ���Ϣ*/
#define TAF_PH_EVT_SET_PREF_PLMN_TYPE_CNF   34  /*�������ȼ������б��ļ��ظ���Ϣ*/
#define TAF_PH_EVT_TEST_PREF_PLMN_CNF       35  /*�������ȼ������б�ظ���Ϣ*/
#define TAF_PH_EVT_TEST_SYSCFG_CNF          36  /*����syscfg�ظ���Ϣ*/

/* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, begin */
/* MMA��AT�ϱ��¼���������ʾ+PACSP1����+PACSP0*/
#define TAF_PH_EVT_NSM_STATUS_IND           (37)
/* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, end */

#define TAF_PH_EVT_PLMN_CHANGE_IND          (38)  /* ^PLMN��Ϣ�ϱ� */

#define TAF_MMA_EVT_AC_INFO_CHANGE_IND       (39) /* С����ֹ���뼼����Ϣ�ϱ� */

#define TAF_MMA_EVT_REG_REJ_INFO_IND       (40) /* ����ܾ�ԭ��ֵ�ϱ� */

#define TAF_MMA_EVT_PLMN_SELECTION_INFO_IND       (41) /* ��������ϱ� */

#define TAF_MMA_EVT_USER_CFG_OPLMN_QRY_CNF          (42) /* ��ѯ����PLMN�б����ϱ� */
#define TAF_MMA_EVT_USER_CFG_OPLMN_SET_CNF          (43) /* ���ñ���PLMN�б����ϱ� */

#define TAF_MMA_EVT_NET_SCAN_CNF                            (44)

#define TAF_MMA_EVT_PS_INIT_RESULT_IND        (45)  /* Э��ջ��ʼ�����ָʾ��Ϣ */
#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
#define TAF_MMA_EVT_MASTER_KEY_HUK_INFO_IND    (46)
#define TAF_MMA_EVT_DIE_ID_HUK_INFO_IND        (47)
#define TAF_MMA_EVT_GET_DIE_ID_INFO_IND        (48)
#endif /*FEATURE_ON == MBB_FEATURE_VSIM_HUK*/

#define TAF_PH_MAX_GUL_RAT_NUM                              (3)                 /*AT^syscfgex��acqorder����Ľ��뼼������ */
#define TAF_PH_MAX_GU_RAT_NUM                               (2)                 /*AT^syscfgex��acqorder����Ľ��뼼������ */
#define TAF_PH_MAX_LU_RAT_NUM                               (2)                 /*AT^syscfgex��acqorder����Ľ��뼼������ */



typedef struct
{
    VOS_UINT8                           ucRatOrderNum;                          /* syscfgex�����õ�acqoder�е�ָʾ���� */
    TAF_PH_RAT_TYPE_ENUM_UINT8          aenRatOrder[TAF_PH_MAX_GUL_RAT_NUM];    /* at^syscfgex�����õ�acqoder��˳�� */
}TAF_PH_RAT_ORDER_STRU;



enum TAF_MMA_USER_SET_PRIO_RAT_ENUM
{
    TAF_MMA_USER_SET_PRIO_AUTO,
    TAF_MMA_USER_SET_PRIO_GSM_PREFER,
    TAF_MMA_USER_SET_PRIO_WCDMA_PREFER,
    TAF_MMA_USER_SET_PRIO_NOCHANGE,
    TAF_MMA_USER_SET_PRIO_BUTT
};
typedef VOS_UINT8 TAF_MMA_USER_SET_PRIO_RAT_ENUM_U8;



enum TAF_PH_USER_SET_RAT_TYPE_ENUM
{
    TAF_PH_USER_SET_RAT_WCDMA,
    TAF_PH_USER_SET_RAT_WCDMA_GSM,
    TAF_PH_USER_SET_RAT_GSM,
    TAF_PH_USER_SET_RAT_BUTT
};
typedef VOS_UINT8 TAF_PH_USER_SET_RAT_TYPE_ENUM_U8;





typedef struct
{
    TAF_PH_ROAM_MODE                           ucRoam;                          /* ����������0���������ڹ������Σ�1�������������Σ��رչ������Σ�2���رչ������Σ������������Σ�3���رչ��ڹ������� */
    TAF_PH_SERVICE_DOMAIN                      ucSrvDomain;                     /* ������0��CS ONLY; 1:PS ONLY; 2:CS_PS; 3:any��ͬ��CS ONLY��4�����ı������*/
    TAF_MMA_USER_SET_PRIO_RAT_ENUM_U8          enUserPrio;
    VOS_UINT8                                  aucReserve[1];
    TAF_PH_RAT_ORDER_STRU                      stRatOrder;                      /* ��¼����ģʽ���������ȼ� */
    TAF_USER_SET_PREF_BAND64                   stGuBand;                        /* ��¼GUƵ�� */
    TAF_USER_SET_PREF_BAND64                   stLBand;                         /* ��¼LƵ�� */
}TAF_MMA_SYS_CFG_PARA_STRU;


#if (FEATURE_ON == MBB_WPG_COMMON)
typedef TAF_UINT8 TAF_PH_RAT_TDS_FLAG;
typedef TAF_MMA_SYS_CFG_PARA_STRU TAF_PH_NW_SCAN_EX_STRU;
typedef struct
{
    TAF_PH_RAT_TDS_FLAG          ucUtranMode;
    TAF_UINT8                           ucBandSwitch;
    TAF_UINT16                         usChannelId;    
    /* ���ݽṹ�������洢�ϴ�SYSCFGEX���õĲ��� */
    TAF_PH_NW_SCAN_EX_STRU   stNwScanExPara;
}TAF_PH_NW_SCAN_STRU;
#endif

#define TAF_MAX_GROUP_CFG_OPLMN_NUM                  (50)            /* �����������õ�OPLMN�������� */
#define TAF_MAX_USER_CFG_OPLMN_GROUP_INDEX           (5)             /* �������õ������Index,֧������(0-5)��6�� */
#define TAF_MAX_USER_CFG_OPLMN_VERSION_LEN           (8)             /* �û����õ�OPLMN�汾����󳤶� */
#define TAF_MAX_GROUP_CFG_OPLMN_DATA_LEN             (250)           /* ������������OPLMN������ֽ���������SIM���ļ���ʽ��5���ֽڱ�ʾ1�������뼼����OPLMN*/
#define TAF_MAX_USER_CFG_OPLMN_DATA_LEN              (1280)          /* �û��������õ��ܵ�OPLMN����ֽ���������SIM���ļ���ʽ��5���ֽڱ�ʾ1�������뼼����OPLMN*/
#define TAF_SIM_PLMN_WITH_RAT_LEN                    (5)             /* SIM�������뼼��PLMN�ֽ���*/
#define TAF_AT_PLMN_WITH_RAT_LEN                     (10)            /* AT�����·��Ĵ����뼼��PLMN�ֽ���*/
#define TAF_AT_EOPLMN_PARA_NUM                       (4)             /* ^EOPLMN������������ĸ��� */



typedef struct
{
    TAF_UINT8                           aucVersion[TAF_MAX_USER_CFG_OPLMN_VERSION_LEN];    /* OPLMN List�汾�� */
    TAF_UINT8                           ucIndex;                                /* ��ǰ���õ���Index */
    TAF_UINT8                           ucOPlmnCount;                           /* ����ʵ������OPLMN�ĸ��� */
    TAF_UINT8                           aucOPlmnWithRat[TAF_MAX_GROUP_CFG_OPLMN_DATA_LEN];  /* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}TAF_MMA_SET_EOPLMN_LIST_STRU;


typedef struct
{
    TAF_PHONE_EVENT                     PhoneEvent;
    MN_OPERATION_ID_T                   OpId;
    MN_CLIENT_ID_T                      ClientId;

    VOS_UINT32                          ulResult;
}TAF_PHONE_EVENT_EOPLMN_SET_CNF_STRU;


typedef struct
{
    TAF_PHONE_EVENT                     PhoneEvent;
    MN_OPERATION_ID_T                   OpId;
    MN_CLIENT_ID_T                      ClientId;

    VOS_UINT32                          ulResult;
    VOS_UINT8                           aucVersion[TAF_MAX_USER_CFG_OPLMN_VERSION_LEN];       /* OPLMN List�汾�� */
    TAF_UINT16                          usOPlmnNum;                                           /* OPLMN���� */
    TAF_UINT8                           aucReserved[2];
    TAF_UINT8                           aucOPlmnList[TAF_MAX_USER_CFG_OPLMN_DATA_LEN];        /* OPLMN��PDU���ݣ���EFOplmn�ļ�һ�� */
}TAF_PHONE_EVENT_EOPLMN_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT16                          usCellNum;                              /* ��Ҫɨ����������޵�С������ */
    VOS_INT16                           sCellPow;                               /* С������ֵ */
    TAF_PH_RAT_TYPE_ENUM_UINT8          ucRat;                                  /* ��Ҫɨ��Ľ���ģʽ */
    VOS_UINT8                           aucReserve[3];
    TAF_USER_SET_PREF_BAND64            stBand;                                 /* ��¼Ƶ��*/
}TAF_MMA_NET_SCAN_REQ_STRU;


typedef struct
{
    VOS_UINT16                          usArfcn;                                /* Ƶ�� */
    VOS_UINT16                          usC1;                                   /* ����GSMС����ѡ��C1ֵ(�ݲ�֧��) */
    VOS_UINT16                          usC2;                                   /* ����GSMС����ѡ��C2ֵ(�ݲ�֧��) */
    VOS_UINT16                          usLac;                                  /* λ������ */
    VOS_UINT32                          ulMcc;                                  /* PLMN������ */
    VOS_UINT32                          ulMnc;                                  /* PLMN������ */
    VOS_UINT16                          usBsic;                                 /* GSMС����վ�� */
    VOS_INT16                           sRxlev;                                 /* ���յ����ź�ǿ�� */
    VOS_INT16                           sRssi;                                  /* GSM��BCCH�ŵ���RSSI��WCDMA��RSCP */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulCellId;                               /* С��ID */
    TAF_USER_SET_PREF_BAND64            stBand;                               /* ����ȡֵͬ�ӿ�RRMM_SYS_CFG_REQ_STRU��Ƶ�β��� */
}TAF_MMA_NET_SCAN_INFO_STRU;

/*****************************************************************************
 ö����    : TAF_MMA_NET_SCAN_RESULT_ENUM
 �ṹ˵��  : TAF_MMA_NET_SCAN_CNF_STRU��Ϣ�е�enResult;
*****************************************************************************/
enum TAF_MMA_NET_SCAN_RESULT_ENUM
{
    TAF_MMA_NET_SCAN_RESULT_SUCCESS     = 0,
    TAF_MMA_NET_SCAN_RESULT_FAILURE     = 1,
    TAF_MMA_NET_SCAN_RESULT_BUTT
};
typedef VOS_UINT8  TAF_MMA_NET_SCAN_RESULT_ENUM_UINT8;


enum TAF_MMA_NET_SCAN_CAUSE_ENUM
{
    TAF_MMA_NET_SCAN_CAUSE_SIGNAL_EXIST        = 0,                /* ������������ */
    TAF_MMA_NET_SCAN_CAUSE_STATE_NOT_ALLOWED   = 1,                /* ��ǰδפ�� */
    TAF_MMA_NET_SCAN_CAUSE_FREQ_LOCK           = 2,                /* ��ǰ��Ƶ״̬ */
    TAF_MMA_NET_SCAN_CAUSE_PARA_ERROR          = 3,                /* �������󣬰������뼼����֧�֣�Ƶ�β�֧�֣�Ƶ������������޴��� */
    TAF_MMA_NET_SCAN_CAUSE_CONFLICT            = 4,                /* ����ԭ��ֵ��ͻ */
    TAF_MMA_NET_SCAN_CAUSE_SERVICE_EXIST       = 5,
    TAF_MMA_NET_SCAN_CAUSE_NOT_CAMPED          = 6,
    TAF_MMA_NET_SCAN_CAUSE_TIMER_EXPIRED       = 7,
    TAF_MMA_NET_SCAN_CAUSE_RAT_TYPE_ERROR      = 8,
    TAF_MMA_NET_SCAN_CAUSE_MMA_STATE_DISABLE   = 9,

    TAF_MMA_NET_SCAN_CAUSE_BUTT
};
typedef VOS_UINT8 TAF_MMA_NET_SCAN_CAUSE_ENUM_UINT8;


typedef struct
{
    /*�ò��ֱ��������ǰ�棬ATģ�����ȡ�ò������ж���Ϣ����*/
    TAF_PHONE_EVENT                     PhoneEvent;
    MN_OPERATION_ID_T                   ucOpId;
    MN_CLIENT_ID_T                      usClientId;

    TAF_MMA_NET_SCAN_RESULT_ENUM_UINT8  enResult;
    TAF_MMA_NET_SCAN_CAUSE_ENUM_UINT8   enCause;
    VOS_UINT8                           ucFreqNum;                                      /* �ϱ���Ƶ����� */
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_NET_SCAN_INFO_STRU          astNetScanInfo[TAF_MMA_NET_SCAN_MAX_FREQ_NUM];
}TAF_MMA_NET_SCAN_CNF_STRU;



typedef struct
{
    /*�ò��ֱ��������ǰ�棬ATģ�����ȡ�ò������ж���Ϣ����*/
    TAF_PHONE_EVENT                     PhoneEvent;
    MN_OPERATION_ID_T                   OpId;
    MN_CLIENT_ID_T                      ClientId;

    TAF_PLMN_ID_STRU                    stPlmnId;
    TAF_UINT32                          ulRejCause;
    TAF_PH_RAT_TYPE_ENUM_UINT8          enRat;
    TAF_PH_SERVICE_DOMAIN               ucSrvDomain;

    VOS_UINT8                           ucRejType;
    TAF_UINT8                           ucReserved;

}TAF_PH_REG_REJ_INFO_STRU;



enum TAF_PH_PLMN_SELECTION_RESULT_ENUM
{
    TAF_PH_PLMN_SELECTION_RESULT_NORMAL_SERVICE    = 0,                        /* �������� */
    TAF_PH_PLMN_SELECTION_RESULT_LIMITED_SERVICE   = 1,                        /* ���Ʒ��� */
    TAF_PH_PLMN_SELECTION_RESULT_NO_SERVICE        = 2,                        /* �޷��� */
    TAF_PH_PLMN_SELECTION_RESULT_INTERRUPT         = 3,                        /* �������ж� */
    TAF_PH_PLMN_SELECTION_RESULT_BUTT
};
typedef VOS_UINT32 TAF_PH_PLMN_SELECTION_RESULT_ENUM_UINT32;


enum TAF_PH_PLMN_SELECTION_START_END_FLAG_ENUM
{
    TAF_PH_PLMN_SELECTION_START      = 0,                        /* ������ʼ */
    TAF_PH_PLMN_SELECTION_END        = 1,                        /* �������� */
    TAF_PH_PLMN_SELECTION_INTERRUPT  = 2,                        /* ��������� */
    TAF_PH_PLMN_SELECTION_BUTT
};
typedef VOS_UINT32 TAF_PH_PLMN_SELECTION_START_END_FLAG_ENUM_UINT32;

#if (FEATURE_ON == MBB_WPG_COMMON)

typedef VOS_UINT16 TAF_SIMREFRESH_TYPE;
#define TAF_PH_SIMREFRESH_TYPE_MSISDN            0
#define TAF_PH_SIMREFRESH_TYPE_PNN               1

#define SIMREFRESH_INITIAL_FULL_FILE_CHANGE_NOTIFY               (10000)
#define SIMREFRESH_FILE_CHANGE_NOTIFY                            (10001)
#define SIMREFRESH_INITIAL_FILE_CHANGE_NOTIFY                    (10002)
#define SIMREFRESH_INITIALIZATION                                (10003)
#define SIMREFRESH_UICC_RESET                                    (10004)
#define SIMREFRESH_APPLICATION_RESET_3G_ONLY                     (10005)
#define SIMREFRESH_SESSION_RESET_3G_ONLY                         (10006)

#define TAF_PH_EVT_USIM_REFRESH_IND             (81)  /*sim������ָʾ*/

#endif


typedef struct
{
    /*�ò��ֱ��������ǰ�棬ATģ�����ȡ�ò������ж���Ϣ����*/
    TAF_PHONE_EVENT                     PhoneEvent;
    MN_OPERATION_ID_T                   OpId;
    MN_CLIENT_ID_T                      ClientId;

    TAF_PH_PLMN_SELECTION_RESULT_ENUM_UINT32           ulPlmnSelectRlst;
    TAF_PH_PLMN_SELECTION_START_END_FLAG_ENUM_UINT32   ulPlmnSelectFlag; /* ��ʾ������ʼ���������� */
}TAF_PH_PLMN_SELECTION_INFO_STRU;


typedef struct
{
    TAF_PHONE_EVENT             PhoneEvent;
    MN_OPERATION_ID_T           OpId;
    MN_CLIENT_ID_T              ClientId;

    TAF_UINT32                  ulPlmnNum;
    TAF_PH_OPERATOR_NAME_STRU   astPlmnName[MAX_PLMN_NAME_LIST];
    TAF_PLMN_STATUS_STRU        astPlmnInfo[MAX_PLMN_NAME_LIST];
}TAF_PHONE_EVENT_PLMN_LIST_STRU;

typedef struct
{
    /*�ò��ֱ��������ǰ�棬ATģ�����ȡ�ò������ж���Ϣ����*/
    TAF_PHONE_EVENT                    PhoneEvent;
    MN_OPERATION_ID_T                  OpId;
    MN_CLIENT_ID_T                     ClientId;

    TAF_UINT32                         OP_RegPlmn         : 1;
    TAF_UINT32                         OP_CsServiceStatus : 1;
    TAF_UINT32                         OP_PsServiceStatus : 1;
    TAF_UINT32                         OP_PlmnList        : 1;

    TAF_UINT32                         OP_PlmnReselMode   : 1;
    TAF_UINT32                         OP_PhoneError      : 1;
    TAF_UINT32                         OP_CurRegSta       : 1;
    TAF_UINT32                         OP_Rssi            : 1;

    TAF_UINT32                         OP_BatteryPower    : 1;
    TAF_UINT32                         OP_Pin             : 1;
    TAF_UINT32                         OP_UsimAccessData  : 1;
    TAF_UINT32                         OP_PinRemain       : 1;

    TAF_UINT32                         OP_MeLockStatus     : 1;
    TAF_UINT32                         OP_MePersonalisation: 1;
    TAF_UINT32                         OP_OperMode         : 1;
    TAF_UINT32                         OP_SpnInfo          : 1;

    TAF_UINT32                         OP_Mode              : 1;
    TAF_UINT32                         OP_Srvst             : 1;
    TAF_UINT32                         OP_UsimRestrictAccess: 1;
    TAF_UINT32                         OP_UsimPNN           : 1;

    TAF_UINT32                         OP_SysCfg            : 1;
    TAF_UINT32                         OP_UsimOPL           : 1;
    TAF_UINT32                         OP_MmInfo            : 1;
    TAF_UINT32                         OP_PrefPlmnList      : 1;

    TAF_UINT32                         OP_DomainAttachState : 1;
    TAF_UINT32                         OP_SysCfgBandGroup   : 1;


    /* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, begin */
    TAF_UINT32                         OP_PlmnMode          : 1;
    /* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, end */

    TAF_UINT32                         OP_CurPlmn           : 1;

    TAF_UINT32                         Op_CellAcInfo        : 1;
    TAF_UINT32                         OP_Spare             : 2;
    TAF_UINT32                         OP_PsInitRslt        : 1;

    TAF_PHONE_ERROR                    PhoneError;
    TAF_PH_OP_MODE_CNF_STRU            OperMode;


    TAF_MMA_SYS_CFG_PARA_STRU          stSysCfg;


    TAF_PLMN_ID_STRU                   RegPlmn;
    TAF_PH_INFO_RAT_TYPE               RatType;
    TAF_PHONE_SERVICE_STATUS           CsServiceStatus;
    TAF_PHONE_SERVICE_STATUS           PsServiceStatus;
    TAF_PHONE_CHANGED_SERVICE_STATUS   ServiceStatus;
    TAF_PLMN_LIST_STRU                 PlmnList;
    TAF_PLMN_RESEL_MODE_TYPE           PlmnReselMode;
    TAF_PH_REG_STATE_STRU              CurRegSta;
    TAF_PH_RSSI_STRU                   RssiValue;
    TAF_PH_BATTERYPOWER_STRU           BatteryStatus;
    TAF_PH_PIN_CNF_STRU                PinCnf;
    TAF_PH_USIM_RESPONSE_STRU          UsimAccessData;
    TAF_USIM_STATUS                    SimStatus;
    TAF_PH_PIN_TIMECNF_STRU            PinRemainCnf;
    TAF_PH_ME_LOCK_STATUS              MeLockStatus;
    TAF_PH_ME_PERSONLISATION_CNF_STRU  MePersonalisation;
    TAF_PH_SPN_INFO_STRU               PhSpnInfo;
    TAF_PH_RESTRICTED_ACCESS_CNF_STRU  RestrictedAccess;
    NAS_MM_INFO_IND_STRU               stMmInfo;
    TAF_MMA_CELL_AC_INFO_STRU          stCellAcInfo;
    TAF_USER_PLMN_LIST_STRU            stPrefPlmnList;
    TAF_DOMAIN_ATTACH_STATE_STRU       stDomainAttachState;

    MN_PH_PREF_PLMN_TYPE_ENUM_U8       ucPrefPlmnType;
    TAF_CHAR                           strSysCfgBandGroup[TAF_PH_SYSCFG_GROUP_BAND_LEN];

    TAF_PLMN_ID_STRU                   stCurPlmn;                   /* ��ǰפ����PLMN��Ϣ */
#if(FEATURE_ON == MBB_WPG_COMMON)
    TAF_PH_PREF_BAND                         ulSysCfgExLTEBandGroup1;/*mbb��ȡLTEband����*/
    TAF_PH_PREF_BAND                         ulSysCfgExLTEBandGroup2;/**/
#endif/*FEATURE_ON == MBB_WPG_COMMON*/
    TAF_SYS_SUBMODE_ENUM_UINT8         ucSysSubMode;            /* ϵͳ��ģʽ */
    VOS_UINT8                          ucRoamStatus;            /* �ϱ���Ӧ�õ�����״̬ */
    /* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, begin */
    VOS_UINT8                          ucPlmnMode;
    /* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-13, end */

    VOS_UINT8                          aucCurcRptCfg[TAF_MMA_RPT_CFG_MAX_SIZE];         /* CURC���õ������ϱ���ʶ */
    VOS_UINT8                          aucUnsolicitedRptCfg[TAF_MMA_RPT_CFG_MAX_SIZE];  /* �����������õ������ϱ���ʶ */

    VOS_UINT32                          ulPsInitRslt;                                  /* Э��ջ��ʼ����� */
#if (FEATURE_ON == MBB_WPG_COMMON)
    TAF_SIMREFRESH_TYPE                RefreshType;             /* SIMREFRESHԭ��ֵ */
    VOS_UINT16                         aucRes;                 /*�������*/
#endif
}TAF_PHONE_EVENT_INFO_STRU;

#define TAF_SIM_LOCK_MCC_LEN            (3)

/*****************************************************************************
 �ṹ��    : TAF_CUSTOM_CARDLOCK_STATUS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : en_NV_Item_CardlockStatus NV���Ӧ�Ľṹ,
             ���ڱ���SIM LOCK��״̬�Լ�ʣ���������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStatus;            /*�Ƿ񼤻0�����1���� */
    TAF_OPERATOR_LOCK_STATUS_ENUM_U32   enCardlockStatus;    /**/
    VOS_UINT32                          ulRemainUnlockTimes; /*����ʣ�����*/
}TAF_CUSTOM_CARDLOCK_STATUS_STRU;


#define EVT_NAS_MMA_NV_CONTEXT   0xaacc          /* PC�طŹ���NV�ļ�������Ϣ */

/*****************************************************************************
 Structure      : NAS_MMA_NV_CONTEXT_ST
 Description    : PC�طŹ��̣�NV�ļ��ṹ
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             auNvFileName[40];                     /* �ļ������40���ַ�*/
    VOS_UINT32                            ulNvFileLen;                          /* �ļ�����*/
	VOS_UINT32                            ulPacketLen;                          /* ��ǰ���ݱ��ڶ�ȡ���ļ������ݳ���*/
    VOS_UINT8                             auNvFileData[4];                      /* �ļ�����*/
 }NAS_MMA_NV_CONTEXT_ST;

/*****************************************************************************
 Structure      : NAS_MMA_NV_MSG_ST
 Description    : PC�طŹ��̣�NV�ļ��ط���Ϣ
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                           usMsgID;
    VOS_UINT16                           usReserved;                            /* ��PACK(1)��PACK(4)�����ж���ı����ֽ� */
    NAS_MMA_NV_CONTEXT_ST                stNVCtxt;                                  /*NV�ļ�*/
}NAS_MMA_NV_MSG_ST;

/*****************************************************************************
�ṹ��     : MN_PH_CSQLVLEXT_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSQLVLEX��ѯ�����Ľ���ϱ��ṹ
             ����CSQLVLEX��ѯ��ȡ�����źŸ����ͱ��������ʰٷֱȣ���ǰ�汾��֧��BER��ѯ����99
*******************************************************************************/
typedef struct
{
    MN_PH_CSQLVLEXT_RSSILV_VALUE_ENUM_UINT8   enRssilv;                         /* CSQLVLEX��ѯ��ȡ�����źŸ��� */
    MN_PH_CSQLVLEXT_BER_VALUE_ENUM_UINT8      enBer;                            /* ���������ʰٷֱȣ���ʱ��֧��BER��ѯ����99*/
}MN_PH_CSQLVLEXT_PARA_STRU;

/* Added by f62575 for AT Project, 2011-10-04,  Begin */
/*****************************************************************************
 �ṹ��    : MN_PH_CSQLVL_PARA_STRU
 �ṹ˵��  : CSQLVL��ѯ�����Ľ���ϱ��ṹ
             ����RSCP �ȼ���RSCP �ľ���ֵ
*******************************************************************************/
typedef struct
{
    VOS_UINT16                          usRscp;                                 /* RSCP �ȼ� */
    VOS_UINT16                          usLevel;                                /* RSCP �ľ���ֵ */
}MN_PH_CSQLVL_PARA_STRU;
/* Added by f62575 for AT Project, 2011-10-04,  End */


enum AT_CPAM_RAT_PRIO_ENUM
{
    MN_MMA_CPAM_RAT_PRIO_GSM            = 0,                                    /* �������ȼ�����ΪGSM����  */
    MN_MMA_CPAM_RAT_PRIO_WCDMA          = 1,                                    /* �������ȼ�����ΪWCDMA���� */
    MN_MMA_CPAM_RAT_PRIO_NO_CHANGE      = 2,                                    /* �������ȼ�Ϊ���ı� */
    MN_MMA_CPAM_RAT_BUTT
};
typedef VOS_UINT8 MN_MMA_CPAM_RAT_PRIO_ENUM_UINT8;




typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
    VOS_UINT8                           ucRssi;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulCellId;
}MN_MMA_ANQUERY_PARA_STRU;

/*****************************************************************************
�ṹ��    : MN_MMA_CSNR_PARA_STRU
�ṹ˵��  : AT+CSNR��ѯ�����Ľ���ϱ��ṹ
*******************************************************************************/
typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
}MN_MMA_CSNR_PARA_STRU;

/*****************************************************************************
�ṹ��    : MN_MMA_QOSIG_PARA_STRU
�ṹ˵��  : AT*QOSIG  ��ѯ�����Ľ���ϱ��ṹ
*******************************************************************************/
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
typedef struct
{
    VOS_INT16                           sCpichRscp;
    VOS_INT16                           sCpichEcNo;
}MN_MMA_QOSIG_PARA_STRU;
#endif

typedef struct
{
    VOS_UINT8                           ucPlmnType;
    VOS_UINT8                           aucReserve[1];
    VOS_UINT16                          usPlmnNameLen;
    VOS_UINT8                           aucPlmnName[TAF_PH_OPER_NAME_LONG];
}MN_MMA_CRPN_QRY_REQ_STRU;

#define TAF_PH_CRPN_PLMN_MAX_NUM            (16)            /* AT^CRPN�������PLMN���� */


typedef struct
{
    VOS_UINT8                           ucTotalNum;
    VOS_UINT8                           ucMaxMncLen;
    VOS_UINT8                           aucReserved[2];
    MN_MMA_CRPN_QRY_REQ_STRU            stMnMmaCrpnQry;
    TAF_PH_OPERATOR_NAME_STRU           stOperNameList[TAF_PH_CRPN_PLMN_MAX_NUM];
}MN_MMA_CRPN_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT8                           aucRsv[4];
}MN_MMA_CIPHER_QRY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucCipherInfo;
    VOS_UINT8                           aucRsv[3];
}MN_MMA_CIPHER_QRY_CNF_STRU;


typedef struct
{
    VOS_UINT8                           aucRsv[4];
}MN_MMA_LOCATION_INFO_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucRsv;
    VOS_UINT32                          ulCellid;
}MN_MMA_LOCATION_INFO_CNF_STRU;



typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
    MN_MMA_CRPN_QRY_CNF_STRU            stMnMmaCrpnQryCnf;
}MN_MMA_CRPN_QRY_CNF_MSG_STRU;



typedef struct
{
    TAF_PH_USIM_SPN_STRU                stSimSpnInfo;
    TAF_PH_USIM_SPN_STRU                stUsimSpnInfo;
}MN_MMA_SPN_PARA_STRU;

/* MM��������壬�ڴ˻�������չ */
typedef enum
{
    MM_TEST_AT_CMD_MM_STATE             = 0,    /* MM�Ӳ�״̬ */
    MM_TEST_AT_CMD_GMM_STATE            = 1,    /* GMM�Ӳ�״̬ */
    MM_TEST_AT_CMD_GPRS_STATE           = 2,    /* GPRS�ƶ��Թ���״̬ */
    MM_TEST_AT_CMD_MM_REG_STATE         = 3,    /* MMע��״̬ */
    MM_TEST_AT_CMD_GMM_REG_STATE        = 4,    /* GMMע��״̬ */
    MM_TEST_AT_CMD_PLMN_SEARCH_MODE     = 5,    /* �趨����ģʽ, ֻ����NV�� */
    MM_TEST_AT_CMD_SET_RAT_MODE         = 6,    /* �趨����ģʽ, ֻ����NV�� */

    /* Added by s46746 for CS/PS mode 1, 2012-6-19, begin */
    MM_TEST_AT_CMD_SET_ADDITIONAL_UPDATE_RESULT_IE = 7,    /* �趨ADDITIONAL_UPDATE_RESULT_IE */
    MM_TEST_AT_CMD_SET_LTE_UE_USAGE_SETTING        = 8,    /* �趨LTE_UE_USAGE_SETTING */
    /* Added by s46746 for CS/PS mode 1, 2012-6-19, end */

    MM_TEST_AT_CMD_SET_GMM_DEALY_SUSPENDRSP        = 9,    /* �趨gmm�ӳٻظ���������MMC */

    MM_TEST_AT_CMD_SET_CSFB_HIGH_PRIO_FLG         = 10,

    MM_TEST_AT_CMD_CLEAR_USER_PLMN_                   = 11,

    MM_TEST_AT_CMD_BUTT,
}MM_TEST_AT_CMD_ENUM;
typedef VOS_UINT8 MM_TEST_AT_CMD_ENUM_U8;


enum TAF_MMA_CARD_STATUS_ENUM
{
    TAF_MMA_CARD_STATUS_AVAILABLE      = 0,
    TAF_MMA_CARD_STATUS_NOT_AVAILABLE  = 1,
    TAF_MMA_CARD_STATUS_BUTT
};
typedef VOS_UINT8 TAF_MMA_CARD_STATUS_ENUM_UINT8;


enum TAF_MMA_USIMM_CARD_TYPE_ENUM
{
    TAF_MMA_USIMM_CARD_SIM           = 0,
    TAF_MMA_USIMM_CARD_USIM          = 1,
    TAF_MMA_USIMM_CARD_ROM_SIM       = 2,
    TAF_MMA_USIMM_CARD_ISIM          = 3,             /*ISIM��*/
    TAF_MMA_USIMM_CARD_NOCARD        = 255,
    TAF_MMA_USIMM_CARD_TYPE_BUTT
};
typedef VOS_UINT32      TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32;



typedef struct
{
    MM_TEST_AT_CMD_ENUM_U8              ucCmd;
    TAF_UINT8                           ucParaNum;
    TAF_UINT16                          usReserve;
    TAF_UINT32                          aulPara[10];
}MM_TEST_AT_CMD_STRU;


typedef struct
{
    VOS_UINT32                          ulRsltNum;
    VOS_UINT32                          aulRslt[20];
}MM_TEST_AT_RSLT_STRU;



typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
    MM_TEST_AT_RSLT_STRU                stAtCmdRslt;        /* AT����ִ�з��� */
}MN_MM_TEST_CMD_RSP_MSG_STRU;



typedef struct
{
    VOS_MSG_HEADER
    unsigned long                       ulMsgName;

    VOS_UINT8                           ucOmConnectFlg;                         /* UE��PC���ߵ����ӱ�־, VOS_TRUE: ������; VOS_FALSE: δ���� */
    VOS_UINT8                           ucOmPcRecurEnableFlg;                   /* OM���õķ���NAS PC�ط���Ϣ��ʹ�ܱ�־ */

    VOS_UINT8                           aucRsv2[2];                             /* ����   */
}ATMMA_OM_MAINTAIN_INFO_IND_STRU;



typedef struct
{
    VOS_UINT8                           ucLongNameLen;
    VOS_UINT8                           aucLongName[TAF_PH_OPER_NAME_LONG];
    VOS_UINT8                           ucShortNameLen;
    VOS_UINT8                           aucShortName[TAF_PH_OPER_NAME_SHORT];
}TAF_MMA_MM_INFO_PLMN_NAME_STRU;

typedef struct
{
    VOS_UINT32                          ulCsSrvExistFlg;                        /* CSҵ���Ƿ���ڱ�־ */
    VOS_UINT32                          ulPsSrvExistFlg;                        /* PSҵ���Ƿ���ڱ�־ */
}TAF_USER_SRV_STATE_STRU;



typedef struct
{
    VOS_UINT8                           aucRsv[4];
}TAF_MMA_CERSSI_INFO_QUERY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                  ulMsgName;
    AT_APPCTRL_STRU                             stAtAppCtrl;
    TAF_PH_RSSI_STRU                            stCerssi;                       /* ��ǰС���ź�������Ϣ */
    VOS_UINT8                                   ucRslt;                         /* ��� */
    VOS_UINT8                                   aucReserved[3];
}TAF_MMA_CERSSI_INFO_QUERY_CNF_STRU;



/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */


typedef struct
{
    VOS_UINT16                          usFromIndex; /* ��ѯ��Ӫ�����Ƶ���ʼλ�� */
    VOS_UINT16                          usPlmnNum;   /* ��ѯ��Ӫ�����Ƶĸ���������A�˺�C��ͨѶ����Ϣ��С�����ƣ����һ������ѯ50����¼ */
}TAF_MMA_COPN_INFO_QUERY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT16                          usPlmnNum;
    VOS_UINT16                          usFromIndex;
    VOS_UINT8                           aucContent[4];
}TAF_MMA_COPN_INFO_QUERY_CNF_STRU;

/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */


typedef struct
{
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPLMNType;                         /* ��ѯ��Ӫ�����Ƶ����� */
    VOS_UINT8                           aucReserved1[3];
    VOS_UINT32                          ulFromIndex;                            /* ��ѯ��Ӫ�����Ƶ���ʼλ�� */
    VOS_UINT32                          ulPlmnNum;                              /* ��ѯ��Ӫ�����Ƶĸ���������A�˺�C��ͨѶ����Ϣ��С�����ƣ����һ������ѯ50����¼ */
    VOS_UINT32                          ulValidPlmnNum;                         /* ��Ч�������Ӫ�����Ƹ��� */
}TAF_MMA_CPOL_INFO_QUERY_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulFromIndex;
    VOS_UINT32                          ulValidPlmnNum;                         /* ��Ч�������Ӫ�����Ƹ��� */
    TAF_PLMN_NAME_LIST_STRU             stPlmnName;
}TAF_MMA_CPOL_INFO_QUERY_CNF_STRU;


typedef struct
{
    TAF_SIM_INSERT_STATE_ENUM_UINT32    enSimInsertState;   /* ��ѯ��Ӫ�����Ƶĸ���������A�˺�C��ͨѶ����Ϣ��С�����ƣ����һ������ѯ50����¼ */
}TAF_MMA_SIM_INSERT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    AT_APPCTRL_STRU                     stAtAppCtrl;
    VOS_UINT32                          ulResult;
}TAF_MMA_SIM_INSERT_RSP_STRU;


typedef struct
{
    VOS_UINT32                          ulModuleId;         /* ����PID */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
}TAF_MMA_CTRL_STRU;


typedef struct
{
    TAF_PH_MODE                        PhMode;  /* ģʽ */
    TAF_PH_RESET_FLG                   PhReset; /* �Ƿ���Ҫ���� */
    VOS_UINT8                          aucReserve[2];
}TAF_MMA_PHONE_MODE_PARA_STRU;


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhoneModePara;
}TAF_MMA_PHONE_MODE_SET_REQ_STRU;



typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfgPara;
}TAF_MMA_SYS_CFG_REQ_STRU;


typedef struct
{
    TAF_MMA_ACQ_REASON_ENUM_UINT8    enAcqReason;
    VOS_UINT8                        aucReserve[3];
}TAF_MMA_ACQ_PARA_STRU;


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_ACQ_PARA_STRU               stAcqPara;
}TAF_MMA_ACQ_REQ_STRU;


typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT8                           ucPlmnNum;
    VOS_UINT8                           ucCellNum;
    TAF_PLMN_ID_STRU                    astPlmnId[TAF_MMA_REG_MAX_PLMN_NUM];
    VOS_UINT16                          ausCellId[TAF_MMA_REG_MAX_CELL_NUM];
}TAF_MMA_REG_CELL_INFO_STRU;


typedef struct
{
    VOS_UINT32                                    bitOpPrioClass       : 1;
    VOS_UINT32                                    bitOpEpsAttachReason : 1;
    VOS_UINT32                                    bitOpCellInfo        : 1;
    VOS_UINT32                                    bitSpare             : 29;
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8        enPrioClass;
    TAF_MMA_EPS_ATTACH_REASON_ENUM_UINT8          enEpsAttachReason;
    TAF_PH_SERVICE_DOMAIN                         ucAttachDomain;               /* ������0��CS ONLY; 1:PS ONLY; 2:CS_PS; 3:any��ͬ��CS ONLY��4�����ı������*/
    VOS_UINT8                                     aucReserve[1];
    TAF_MMA_REG_CELL_INFO_STRU                    stCellInfo;
}TAF_MMA_REG_PARA_STRU;


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_REG_PARA_STRU               stRegPara;
}TAF_MMA_REG_REQ_STRU;


typedef struct
{
    VOS_UINT8                           aucReserve[4];
}TAF_MMA_POWER_SAVE_PARA_STRU;


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_POWER_SAVE_PARA_STRU        stPowerSavePara;
}TAF_MMA_POWER_SAVE_REQ_STRU;


typedef struct
{
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8     enDetachCause;
    TAF_PH_SERVICE_DOMAIN               ucDetachDomain;                         /* ������0��CS ONLY; 1:PS ONLY; 2:CS_PS; 3:any��ͬ��CS ONLY��4�����ı������*/
    VOS_UINT8                           aucReserve[2];
}TAF_MMA_DETACH_PARA_STRU;


typedef struct
{
    VOS_MSG_HEADER
    TAF_MMA_MSG_TYPE_ENUM_UINT32        ulMsgName;
    TAF_MMA_CTRL_STRU                   stCtrl;
    TAF_MMA_DETACH_PARA_STRU            stDetachPara;
}TAF_MMA_DETACH_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    TAF_PH_MODE                         ucPhMode;  /* ģʽ */
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
    TAF_PHONE_ERROR                     usErrorCause;
    VOS_UINT8                           aucReserve[2];
}TAF_MMA_PHONE_MODE_SET_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
    TAF_PHONE_ERROR                     usErrorCause;
    VOS_UINT8                           aucReserved[2];
}TAF_MMA_SYS_CFG_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                   ulMsgName;
    VOS_UINT16                                   usClientId;
    VOS_UINT8                                    ucOpid;
    VOS_UINT8                                    aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32          enRslt;
    TAF_PLMN_ID_STRU                             stPlmnId;
    VOS_UINT16                                   usArfcn;
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8       enPrioClass;
    VOS_UINT8                                    aucReserve2[1];
}TAF_MMA_ACQ_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                   ulMsgName;
    VOS_UINT16                                   usClientId;
    VOS_UINT8                                    ucOpid;
    VOS_UINT8                                    aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32          enRslt;
    TAF_PLMN_ID_STRU                             stPlmnId;
    VOS_UINT16                                   usArfcn;
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8       enPrioClass;
    VOS_UINT8                                    aucReserve2[1];
}TAF_MMA_REG_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
}TAF_MMA_POWER_SAVE_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                    ulMsgName;
    VOS_UINT16                                    usClientId;
    VOS_UINT8                                     ucOpid;
    VOS_UINT8                                     aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32           enRslt;
    TAF_PLMN_ID_STRU                              stPlmnId;
    VOS_UINT16                                    usArfcn;
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8        enPrioClass;
    VOS_UINT8                                     aucReserve2[1];
}TAF_MMA_ACQ_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enRslt;
    TAF_PHONE_ERROR                     usErrorCause;
    VOS_UINT8                           aucReserved[2];
}TAF_MMA_DETACH_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    TAF_PHONE_SERVICE_STATUS            CsSrvSta; /*CS����״̬*/
    TAF_PHONE_SERVICE_STATUS            PsSrvSta; /*PS����״̬*/
    VOS_UINT8                           ucCsSimValid; /* CS���Ƿ���Ч��VOS_TRUE:��Ч��VOS_FALSE:��Ч */
    VOS_UINT8                           ucPsSimValid; /* PS���Ƿ���Ч��VOS_TRUE:��Ч��VOS_FALSE:��Ч */
}TAF_MMA_SERVICE_STATUS_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                    ulMsgName;
    VOS_UINT16                                    usClientId;
    VOS_UINT8                                     ucOpid;
    VOS_UINT8                                     aucReserve[1];
    TAF_PLMN_ID_STRU                              stPlmnId;
    VOS_UINT16                                    usArfcn;
    TAF_MMA_PLMN_PRIORITY_CLASS_ENUM_UINT8        enPrioClass;
    VOS_UINT8                                     aucReserve2[1];
}TAF_MMA_SYS_INFO_IND_STRU;




typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                    ulMsgName;
    VOS_UINT16                                    usClientId;
    VOS_UINT8                                     ucOpid;
    TAF_MMA_CARD_STATUS_ENUM_UINT8                enCardStatus;                   /* ��״̬*/
    TAF_MMA_USIMM_CARD_TYPE_ENUM_UINT32           enCardType;                     /* ������:SIM��USIM��ROM-SIM  */
}TAF_MMA_SIM_STATUS_IND_STRU;



#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
#define RSFW_CPRIVATE_KEY_LEN      (256)  /*�ͻ���˽Կ�ĳ���*/
#define RSFW_CPUBLIC_KEY_LEN       (256)  /*�ͻ��˹�Կ�ĳ���*/
#define RSFW_SPUBLIC_KEY_LEN       (256)  /*�������˹�Կ�ĳ���*/

#define HVADH_APP_KEY              (3)    /*APP��ʹ�õ�KEY,������C�˽��м��ܲ���*/
#define HVADH_MODEM_KEY            (4)    /*MODEM��ʹ�õ�KEY��������C�˽��м��ܲ���*/

#define DEVICE_KEY_TYPE            (0)    /*����DEVICEKEY������*/
#define MASTER_KEY_TYPE            (1)    /*����MASTERKEY������*/
#define CONTENT_KEY_TYPE           (2)    /*����CONTENTKEY������*/

#define HUK_KEY_LEN                (1024) /*HUK������ʱ��������*/
#define DIE_ID_LEN                 (32)
#define DIE_ID_HASH_LEN            (32)

#define VSIM_DATA_MAGIC_DATA  (0x5B5B5B5B)

typedef VOS_UINT32 VSIM_DATA_EVENT;

enum VSIM_DATA_EVENT_ENUM
{
    VSIM_DATA_EVENT_HVADH_CNF = 0,
    VSIM_DATA_EVENT_HVSHDH_CNF,
    VSIM_DATA_EVENT_HVDIEID_CNF,
    VSIM_DATA_EVENT_BUTT
};



typedef struct
{
    VOS_UINT32                    magic_start;                 /* ������ʼMagic Code 0x5B5B5B5B*/
    VSIM_DATA_EVENT               EventType;                   /* �¼����� */
    union
    {
        SI_PIH_VSIM_HUK_VAL_STRU      HvadhCnf;                    /*517 BYTE*/
        SI_PIH_HVSHDH_SET_CNF_STRU    HvshdhCnf;                   /*136 BYTE*/
        SI_PIH_HVDIEID_QRY_CNF_STRU   HvdieIDCnf;                  /*69  BYTE*/
    }VsimDataEvent;
    VOS_UINT32                    magic_end;                   /* ��������Magic Code 0x5B5B5B5B*/
}TAF_VSIM_DATA_AREA;

/*˫��ͨ��֮��Ľṹ��*/
typedef struct
{
    VOS_UINT8                ucErrorBit;
    VOS_UINT8                randomKey[VSIM_HUK_MAX_LEN];
    VOS_UINT8                hvadh_key_type;
    VOS_UINT8                key_type;
    SI_PIH_VSIM_HUK_VAL_STRU vsimCpublicKey;
    SI_PIH_VSIM_HUK_VAL_STRU vsimCprivateKey;
    SI_PIH_VSIM_HUK_VAL_STRU vsimSpublicKey;
    VOS_UINT8                reserve[3];
}TAF_PH_MASTER_KEY_HUK_STRU;

typedef struct
{
    TAF_PHONE_EVENT                  PhoneEvent;
    MN_OPERATION_ID_T                OpId;
    MN_CLIENT_ID_T                   ClientId;
    TAF_PH_MASTER_KEY_HUK_STRU       stMasterHukKey;
}TAF_PH_MASTER_KEY_HUK_MSG_INFO_STRU;

typedef struct
{
    VOS_UINT8                vsimDieId[DIE_ID_LEN + 1];
    SI_PIH_VSIM_HUK_VAL_STRU vsimDieIdHuk;
}TAF_PH_DIE_ID_HUK_STRU;

typedef struct
{
    TAF_PHONE_EVENT                  PhoneEvent;
    MN_OPERATION_ID_T                OpId;
    MN_CLIENT_ID_T                   ClientId;
    TAF_PH_DIE_ID_HUK_STRU           stDieID;
}TAF_PH_DIE_ID_HUK_MSG_INFO_STRU;
typedef struct
{
    SI_PIH_VSIM_HUK_VAL_STRU vsimDieId;
    SI_PIH_VSIM_HUK_VAL_STRU vsimDieIdHuk;
}TAF_PH_DIE_ID_INFO_STRU;

typedef struct
{
    TAF_PHONE_EVENT                  PhoneEvent;
    MN_OPERATION_ID_T                OpId;
    MN_CLIENT_ID_T                   ClientId;
    TAF_PH_DIE_ID_INFO_STRU          stDieIdInfo;
}TAF_PH_DIE_ID_INFO_MSG_INFO_STRU;
VOS_UINT32 TAF_MasterKeyHukSet 
(
    MN_CLIENT_ID_T ClientId,
    MN_OPERATION_ID_T OpId, 
    TAF_PH_MASTER_KEY_HUK_STRU *pstMasterKey
);
VOS_UINT32 TAF_MasterPrivateKeyEncode
(
    MN_CLIENT_ID_T ClientId,
    MN_OPERATION_ID_T OpId,
    TAF_PH_MASTER_KEY_HUK_STRU *pstMasterKey
);

VOS_UINT32 TAF_DieIdEncode
(
    MN_CLIENT_ID_T ClientId,
    MN_OPERATION_ID_T OpId,
    TAF_PH_DIE_ID_HUK_STRU *pstDieId
);

VOS_UINT32 AT_DieIdHukSet
(
    MN_CLIENT_ID_T ClientId, 
    MN_OPERATION_ID_T OpId, 
    TAF_PH_DIE_ID_HUK_STRU *DieId
);

VOS_UINT32 TAF_WriteVsimDataToVsimDdr(TAF_VSIM_DATA_AREA *src_data);
VOS_UINT32 AT_DieIdInfoSet
(
    MN_CLIENT_ID_T ClientId, 
    MN_OPERATION_ID_T OpId, 
    TAF_PH_DIE_ID_INFO_STRU *DieIdInfo
);

VOS_UINT32 TAF_DieIdDecode
(
    MN_CLIENT_ID_T ClientId,
    MN_OPERATION_ID_T OpId,
    TAF_PH_DIE_ID_INFO_STRU *pstDieIdInfo
);
#endif /*end (MBB_FEATURE_VSIM_HUK == FEATURE_ON)*/
TAF_UINT32 Taf_DefPhClassType(MN_CLIENT_ID_T        ClientId,
                                      MN_OPERATION_ID_T     OpId,
                                      TAF_PH_MS_CLASS_TYPE  MsClass);

TAF_UINT32 Taf_PhoneAttach(MN_CLIENT_ID_T        ClientId,
                                  MN_OPERATION_ID_T    OpId,
                                  TAF_PH_ATTACH_TYPE   AttachType);
TAF_UINT32 Taf_PhonePinHandle(MN_CLIENT_ID_T      ClientId,
                                      MN_OPERATION_ID_T   OpId,
                                      TAF_PH_PIN_DATA_STRU *pPinData);
TAF_UINT32 Taf_PhonePlmnList(MN_CLIENT_ID_T               ClientId,
                                     MN_OPERATION_ID_T            OpId,
                                     TAF_AVAIL_PLMN_LIST_TYPE      ListType);
TAF_UINT32 Taf_PhonePlmnResel(MN_CLIENT_ID_T                ClientId,
                                       MN_OPERATION_ID_T             OpId,
                                       TAF_PLMN_RESEL_MODE_TYPE      ReselType);
TAF_UINT32 Taf_PhoneStartInfoInd(MN_CLIENT_ID_T             ClientId,
                                        MN_OPERATION_ID_T          OpId,
                                        TAF_START_INFO_IND_STRU    StartInfoInd);
TAF_UINT32 TAF_DefQuickStart(MN_CLIENT_ID_T         ClientId,
                                    MN_OPERATION_ID_T       OpId,
                                    TAF_UINT32              ulSetValue);
TAF_UINT32 Taf_DefPhAutoAttach(MN_CLIENT_ID_T       ClientId,
                                       MN_OPERATION_ID_T    OpId,
                                       TAF_UINT32           ulSetValue);
TAF_UINT32 Taf_FplmnHandle(MN_CLIENT_ID_T            ClientId,
                                  MN_OPERATION_ID_T         OpId,
                                  TAF_PH_FPLMN_OPERATE_STRU stFplmnOperate);

VOS_UINT32 Taf_SysCfgHandle(MN_CLIENT_ID_T        ClientId,MN_OPERATION_ID_T  OpId,
                         TAF_MMA_SYS_CFG_PARA_STRU    stSysCfg);

VOS_UINT32 Taf_NetScanHandle(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_MMA_NET_SCAN_REQ_STRU          *pstNetScan
);

VOS_UINT32 Taf_AbortNetScan (
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
);

TAF_UINT32 TAF_DefLoadDefault(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T   OpId);
VOS_BOOL Taf_IsWBandSupported(VOS_UINT16 usBandNo);

TAF_UINT32  Taf_DefGetSPN(TAF_UINT8 ucSpnType, TAF_PH_USIM_SPN_STRU   *pstAtSPNRslt);

VOS_VOID  Taf_GetSyscfgBandGroupStr(TAF_PH_SYSCFG_BAND_STR* pstSysCfgBandStr);


VOS_VOID  MN_MMA_GetSyscfgExLteBandGroupStr(
    TAF_PH_SYSCFG_BAND_STR             *pstSysCfgBandStr
);


TAF_UINT32  Taf_QueryCSNR(TAF_INT16 *psCpichRscp,TAF_INT16 *psCpichEcNo);
/*���AT*QOSIG */
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
TAF_UINT32  Taf_QueryQOSIG(TAF_INT16 *psCpichRscp,TAF_INT16 *psCpichEcNo);
#endif
TAF_UINT32  Taf_DefGetCardMode(TAF_UINT8 *pucCardMode);

TAF_UINT32 Taf_UsimRestrictedAccessCommand(
                                MN_CLIENT_ID_T               ClientId,
                                MN_OPERATION_ID_T            OpId,
                                TAF_SIM_RESTRIC_ACCESS_STRU *pPara);

TAF_UINT32 Taf_PhoneGetNetworkNameForListPlmn( TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU *pstOperName );
TAF_UINT32 Taf_PhoneGetOperNameInfo( TAF_PH_OPERATOR_NAME_FORMAT_OP_STRU *pstOperName );
TAF_UINT32 Taf_MePersonalisationHandle(
                            MN_CLIENT_ID_T                    ClientId,
                            MN_OPERATION_ID_T                 OpId,
                            TAF_ME_PERSONALISATION_DATA_STRU *pMePersonalData);

TAF_UINT32 Taf_DefPhMode(MN_CLIENT_ID_T          ClientId,
                                MN_OPERATION_ID_T       OpId,
                                TAF_PH_OP_MODE_STRU     PhModeSet);
VOS_VOID   Taf_GetProductionID(VOS_CHAR *pcDest);

TAF_UINT32 TAF_GetUsimStatus(TAF_VOID);

TAF_UINT32  TAF_SetPrefPlmnType(
    MN_PH_PREF_PLMN_TYPE_ENUM_U8        enPrefPlmnType
);


TAF_UINT32 TAF_QryUsimInfo(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_QRY_USIM_INFO_STRU           *pstInfo
);

TAF_BOOL TAF_IsNormalSrvStatus(VOS_VOID);

TAF_UINT32 TAF_QryCpnnInfo(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_ICC_TYPE                     IccType
);

VOS_UINT32 MN_PH_RptCostTime( VOS_VOID  );


VOS_UINT8 APP_MN_PH_AppQryPhMode (VOS_VOID);

VOS_UINT8 MN_MMA_GetServiceDomain(VOS_VOID);

TAF_UINT32  Taf_DefMmTestPara(TAF_VOID *pInput,TAF_VOID *pRslt);


VOS_UINT32 TAF_PhonePlmnUserSel(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PLMN_USER_SEL_STRU             *pstPlmnUserSel
);


VOS_UINT32  MN_FillAndSndAppReqMsg(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                            *pPara,
    VOS_UINT32                          ulParaLen,
    VOS_UINT32                          ulReceiverPid
);

TAF_UINT32 Taf_GetCurrentAttachStatus(TAF_PH_CS_STATUS    *pCsResult,
                                                TAF_PH_PS_STATUS    *pPsResult );


TAF_UINT32 Taf_ParaQuery(
    MN_CLIENT_ID_T              ClientId,
    MN_OPERATION_ID_T           OpId,
    TAF_PARA_TYPE               ParaType,
    TAF_VOID                   *pPara
);

TAF_UINT32 Taf_PrefPlmnHandle (
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_PH_PREF_PLMN_OPERATE_STRU       *pstPrefPlmnOperate
);


VOS_UINT32 TAF_AbortPlmnListReq(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
);





VOS_UINT32 Taf_SetEOPlmnHandle(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    TAF_MMA_SET_EOPLMN_LIST_STRU       *pstEOPlmnCfg
);

VOS_UINT32 TAF_MMA_PhoneModeSetReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_PHONE_MODE_PARA_STRU       *pstPhoneModePara
);

VOS_UINT32 TAF_MMA_SetSysCfgReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
);

VOS_UINT32 TAF_MMA_AcqBestNetworkReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_ACQ_PARA_STRU              *pstAcqPara
);

VOS_UINT32 TAF_MMA_RegReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_REG_PARA_STRU              *pstRegPara
);

VOS_UINT32 TAF_MMA_PowerSaveReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_POWER_SAVE_PARA_STRU       *pstPowerSavePara
);

VOS_UINT32 TAF_MMA_DetachReq(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    TAF_MMA_DETACH_PARA_STRU           *pstDetachPara
);

#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
extern int efuseWriteAes(unsigned int *pBuf);
extern int efuseReadAes(unsigned int *pBuf);
#endif /*MBB_FEATURE_VSIM_HUK*/
#if ((TAF_OS_VER == TAF_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafAppMma.h */
