

#ifndef __SI_APP_PIH_H__
#define __SI_APP_PIH_H__

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "TafTypeDef.h"
#include "UsimPsInterface.h"
#include "sitypedef.h"
#include "omnvinterface.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define SI_PIH_POLL_TIMER_LEN           28000
#define SI_PIH_IMSI_TIMER_LEN           5000
#define SI_PIH_CALL_TIMER_LEN           4000
#define SI_PIH_TIMER_LEN_NO_CHANGE      0


#define SI_PH_PINCODELENMAX             8
#define SI_MAX_IMSI_LEN                 9

#define SI_MAX_PLMN_ID_LEN              3       /* PLMN ID���� */
#define SI_MAX_PLMN_ID_NUM              4       /* ����ʱ֧�ֵ�PLMN ID�� */

#define SI_APDU_MAX_LEN                 260     /* APDU���ݵ���󳤶� */

#define SI_ATR_MAX_LEN                  (80)    /* ATR����󳤶� */

typedef VOS_UINT32 SI_PIH_ERROR;

#define SI_RSFW_MAX_INDEX               (255)   /* ֧��RSFWX�ְ��������� */
#define SI_PIH_HPLMN_MAX_NUM            (32)    /* ֧��HPLMN/EHPLMN�������� */
#define SI_PIH_EHPLMN_BYTE_NUM          (3)     /* EHPLMN�ļ���ÿ��EHPLMN��Ԫռ��3���ֽ� */

#define SI_AUTH_DATA_MAX                (256)   /* ֧�ּ�Ȩ���ݵ���󳤶� */
/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

enum SI_PIH_PIN_TYPE_ENUM
{
    SI_PIN                          = 0,      /* PIN1*/
    SI_PUK                          = 1,      /* PUK1*/
    SI_PIN2                         = 6,      /* PIN2*/
    SI_PUK2                         = 7,      /* PUK2 */
    SI_PHNET_PIN                    = 8,      /* PH-NET PIN*/
    SI_PHSIM_PIN                    = 9,      /* PH-SIM PIN*/
    SI_SIM_NON                      = 255,    /* ��ȷ������PIN������ʱ�����ֵ*/
    SI_PIN_BUTT
};
typedef SI_UINT32 SI_PIH_PIN_TYPE;

enum SI_PIH_RESTRIC_CMD_ENUM
{
    SI_PIH_READ_BINARY              = 176,
    SI_PIH_READ_RECORD              = 178,
    SI_PIH_UPDATE_BINARY            = 214,
    SI_PIH_UPDATE_RECORD            = 220,
    SI_PIH_STATUS                   = 242,
    SI_PIH_CMD_BUTT
};

typedef SI_UINT32 SI_PIH_RESTRIC_CMD;

enum SI_PIH_EVENT_ENUM
{
    SI_PIH_EVENT_PIN_OPER_CNF       = 1,      /* ����PIN�뷵�ؽ��        */
    SI_PIH_EVENT_PIN_QUERY_CNF      = 2,      /* ��ѯPIN�뷵�ؽ��        */
    SI_PIH_EVENT_PIN_INFO_IND       = 3,      /* ����PIN�������ϱ�        */
    SI_PIH_EVENT_SIM_INFO_IND       = 4,      /* SIM����Ϣ�ϱ�            */
    SI_PIH_EVENT_GENERIC_ACCESS_CNF = 5,      /* +CSIM �ظ�               */
    SI_PIH_EVENT_RESTRIC_ACCESS_CNF = 6,      /* +CRSM �ظ�               */
    SI_PIH_EVENT_FDN_CNF            = 7,      /* FDN�ظ�                  */
    SI_PIH_EVENT_BDN_CNF            = 8,      /* BDN�ظ�                  */
    SI_PIH_EVENT_PERO_LOCK_CNF      = 9,      /* �����ظ�                 */
/* Added by h59254 for V7R1C50 ISDB Project,  2012-8-27 begin */
    SI_PIH_EVENT_ISDB_ACCESS_CNF    = 10,     /* ISDB͸���ظ�             */
/* Added by h59254 for V7R1C50 ISDB Project,  2012-8-27 end */
    SI_PIH_EVENT_HVSST_QUERY_CNF    = 11,       /* ^HVSST��ѯ�����       */
    SI_PIH_EVENT_HVSST_SET_CNF      = 12,       /* ^HVSST���������       */
    SI_PIH_EVENT_HVSDH_SET_CNF      = 13,       /* ^HVSDH���������       */
    SI_PIH_EVENT_HVSDH_QRY_CNF      = 14,       /* ^HVSDH��ѯ�����       */
    SI_PIH_EVENT_HVSCONT_QUERY_CNF  = 15,       /* ^HVSCONT��ѯ�����     */
    SI_PIH_EVENT_FILE_WRITE_CNF     = 16,       /* ^RSFW���������        */
    SI_PIH_EVENT_CCHO_SET_CNF       = 17,       /* +CCHO���������        */
    SI_PIH_EVENT_CCHC_SET_CNF       = 18,       /* +CCHC���������        */
    SI_PIH_EVENT_CGLA_SET_CNF       = 19,       /* +CGLA���������        */
    SI_PIH_EVENT_CARD_ATR_QRY_CNF   = 20,       /* ^CARDATR��ѯ�����     */
    SI_PIH_EVENT_HVRDH_IND          = 21,       /* ^HVRDHָʾ�ϱ�           */
    SI_PIH_EVENT_UICCAUTH_CNF       = 22,       /* ^UICCAUTH���������    */
    SI_PIH_EVENT_URSM_CNF           = 23,       /* ^URSM���������        */
    SI_PIH_EVENT_CARDTYPE_QUERY_CNF = 24,
#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
    SI_PIH_EVENT_HVADH_SET_CNF   = 25,          /*^HVADH���������*/
    SI_PIH_EVENT_HVSCONT_SET_CNF = 26,          /*^HVSCONT���������*/
    SI_PIH_EVENT_HVSHDH_SET_CNF  = 27,        /*^hvshdh ���������*/
    SI_PIH_EVENT_HVDIEID_QRY_CNF  = 28,       /*^hvdieid ��ѯ�����*/
    SI_PIH_EVENT_HVDDH_SET_CNF  = 29,        /*^hvddh ���������*/
#endif/*end (FEATURE_ON == MBB_FEATURE_VSIM_HUK)*/
    /*��500��ʼ��ΪPIH�ڲ���ά�ɲ���Ϣ�Ĺ���*/
    SI_PIH_USIMREG_PID_HOOK         = 500,
    SI_PIH_REFRESHREG_PID_HOOK      = 501,
    SI_PIH_ISIMREG_PID_HOOK         = 502,

    SI_PIH_EVENT_BUTT
};
typedef VOS_UINT32  SI_PIH_EVENT;

enum SI_PIH_POLLTIMER_STATE_ENUM
{
    SI_PIH_POLLTIMER_DISABLE        = 0,
    SI_PIH_POLLTIMER_ENABLE         = 1,
    SI_PIH_POLLTIMER_BUTT
};
typedef VOS_UINT32      SI_PIH_POLLTIMER_STATE_ENUM_UINT32;

enum SI_PIH_TIMER_NAME_ENUM
{
    SI_PIH_TIMER_NAME_CHECKSTATUS       = 0,
    SI_PIH_TIMER_NAME_CALL              = 1,
    SI_PIH_TIMER_NAME_CHECKIMSI         = 2,
    SI_PIH_TIMER_NAME_DEACTIVECARD      = 3,
    SI_PIH_TIMER_NAME_BUTT
};
typedef VOS_UINT32      SI_PIH_TIMER_NAME_ENUM_UINT32;

enum SI_PIH_QUERY_TYPE_ENUM
{
    SI_PIH_BDN_QUERY                = 0,
    SI_PIH_FDN_QUERY                = 1,
    SI_PIH_QUERY_BUTT
};
typedef VOS_UINT32      SI_PIH_QUERY_TYPE_ENUM_UINT32;

enum SI_PIH_FDN_BDN_STATE_ENUM
{
    SI_PIH_STATE_FDN_BDN_DISABLE    = 0,     /*FDN/BDN����δʹ��*/
    SI_PIH_STATE_FDN_BDN_ENABLE     = 1,     /*FDN/BDN����ʹ��*/
    SI_PIH_STATE_FDN_BDN_BUTT
};
typedef SI_UINT32   SI_PIH_FDN_BDN_STATE;


enum SI_PIH_FDN_BDN_CMD_ENUM
{
    SI_PIH_FDN_BDN_DISABLE          = 0,     /*ȥ����FDN/BDN����*/
    SI_PIH_FDN_BDN_ENABLE           = 1,     /*����FDN/BDN����*/
    SI_PIH_FDN_BDN_QUERY            = 2,     /*ȥ����FDN/BDN״̬��ѯ*/
    SI_PIH_FDN_BDN_CMD_BUTT
};
typedef SI_UINT32   SI_PIH_FDN_BDN_CMD;

enum SI_PIH_SIM_SLOT_ENUM
{
    SI_PIH_SIM_SLOT1                = 1,
    SI_PIH_SIM_SLOT2                = 2,
    SI_PIH_SIM_SLOT_BUTT
};
typedef VOS_UINT8 SI_PIH_SIM_SLOT_ENUM_UINT8;

enum SI_PIH_SIM_STATE_ENUM
{
    SI_PIH_SIM_DISABLE              = 0,
    SI_PIH_SIM_ENABLE               = 1,
    SI_PIH_SIM_STATE_BUTT
};
typedef VOS_UINT8 SI_PIH_SIM_STATE_ENUM_UINT8;

enum SI_PIH_CARD_USE_ENUM
{
    SI_PIH_CARD_NOUSE               = 0,
    SI_PIH_CARD_USE                 = 1,
    SI_PIH_CARD_USE_BUTT
};
typedef VOS_UINT8 SI_PIH_CARD_USE_ENUM_UINT8;

enum SI_PIH_CARD_TYPE_ENUM
{
    SI_PIH_RSIM = 0,
    SI_PIH_VSIM,
    SI_PIH_CARD_BUTT,
};

enum SI_PIH_ATUICCAUTH_TYPE_ENUM
{
    SI_PIH_ATUICCAUTH_USIMAKA   = 0,
    SI_PIH_ATUICCAUTH_ISIMAKA,
    SI_PIH_ATUICCAUTH_USIMGBA,
    SI_PIH_ATUICCAUTH_ISIMGBA,
    SI_PIH_ATUICCAUTH_BUTT
};

enum SI_PIH_ATKSNAFAUTH_TYPE_ENUM
{
    SI_PIH_ATKSNAFAUTH_USIM     = 0,
    SI_PIH_ATKSNAFAUTH_ISIM,
    SI_PIH_ATKSNAFAUTH_BUTT
};

enum SI_PIH_UICCAUTH_ENUM
{
    SI_PIH_UICCAUTH_AKA,
    SI_PIH_UICCAUTH_GBA,
    SI_PIH_UICCAUTH_NAF,
    SI_PIH_UICCAUTH_BUTT
};
typedef VOS_UINT32 SI_PIH_UICCAUTH_ENUM_UINT32;

enum SI_PIH_UICCAPP_ENUM
{
    SI_PIH_UICCAPP_USIM,
    SI_PIH_UICCAPP_ISIM,
    SI_PIH_UICCAPP_BUTT
};
typedef VOS_UINT32 SI_PIH_UICCAPP_ENUM_UINT32;

enum SI_PIH_ACCESSTYPE_ENUM
{
    SI_PIH_ACCESS_READ,
    SI_PIH_ACCESS_WRITE,
    SI_PIH_ACCESS_BUTT
};
typedef VOS_UINT8 SI_PIH_ACCESSTYPE_ENUM_UINT8;

enum SI_PIH_AUTHSTATUS_ENUM
{
    SI_PIH_AUTH_SUCCESS,
    SI_PIH_AUTH_FAIL,
    SI_PIH_AUTH_SYNC,
    SI_PIH_AUTH_UNSUPPORT,
    SI_PIH_AUTHSTATUS_BUTT
};
typedef VOS_UINT32 SI_PIH_AUTHSTATUS_ENUM_UINT32;

enum SI_PIH_POLLTIMER_ENUM
{
    SI_PIH_POLLTIMER_DRX,
    SI_PIH_POLLTIMER_REL,
    SI_PIH_POLLTIMER_TYPE_BUTT
};
typedef VOS_UINT32 SI_PIH_POLLTIMER_ENUM_UINT32;


/*****************************************************************************
  4 ���ݽṹ����
*****************************************************************************/


typedef struct
{
    SI_UINT32                           ulLen;                                  /* ����APDU���ݳ��� */
    SI_UINT8                            aucCommand[SI_APDU_MAX_LEN];            /* ����APDU�������� */
}SI_PIH_ISDB_ACCESS_COMMAND_STRU;



typedef struct
{
    SI_UINT32                           ulAIDLen;                               /* AID�ĳ��� */
    SI_UINT8                           *pucADFName;                             /* ����ADF������ */
}SI_PIH_CCHO_COMMAND_STRU;


typedef struct
{
    SI_UINT32                           ulSessionID;                            /* ͨ���� */
    SI_UINT32                           ulLen;                                  /* ����APDU���ݳ��� */
    SI_UINT8                           *pucCommand;                             /* ����APDU�������� */
}SI_PIH_CGLA_COMMAND_STRU;


typedef struct
{
    SI_UINT16                           usLen;                                    /* ���APDU���ݳ��� */
    SI_UINT8                            ucSW1;                                    /* ����״̬��1      */
    SI_UINT8                            ucSW2;                                    /* ����״̬��2      */
    SI_UINT8                            aucCommand[SI_APDU_MAX_LEN];              /* ���APDU�������� */
}SI_PIH_CGLA_COMMAND_CNF_STRU;


typedef struct
{
    SI_UINT32                           ulLen;                                    /* ���APDU���ݳ��� */
    SI_UINT8                            aucCommand[SI_ATR_MAX_LEN];            /* ���APDU�������� */
}SI_PIH_ATR_QRY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : SI_PIH_ISDB_ACCESS_COMMAND_CNF_STRU
 �ṹ˵��  : ISDB͸��APDU�����ݻظ����
*****************************************************************************/
typedef struct
{
    SI_UINT16                           usLen;                                    /* ���APDU���ݳ��� */
    SI_UINT8                            ucSW1;                                    /* ����״̬��1      */
    SI_UINT8                            ucSW2;                                    /* ����״̬��2      */
    SI_UINT8                            aucCommand[SI_APDU_MAX_LEN];               /* ���APDU�������� */
}SI_PIH_ISDB_ACCESS_COMMAND_CNF_STRU;

typedef struct
{
    SI_UINT32                           ulLen;
    SI_UINT8                            aucCommand[SI_APDU_MAX_LEN];
}SI_PIH_CSIM_COMMAND_STRU;

typedef struct
{
    SI_PIH_FDN_BDN_CMD                  FdnCmd;
    SI_PIH_FDN_BDN_STATE                FdnState;
}SI_PIH_EVENT_FDN_CNF_STRU;

typedef struct
{
    SI_PIH_FDN_BDN_CMD                  BdnCmd;
    SI_PIH_FDN_BDN_STATE                BdnState;
}SI_PIH_EVENT_BDN_CNF_STRU;

typedef struct
{
    SI_UINT16                           Len;
    SI_UINT8                            SW1;
    SI_UINT8                            SW2;
    SI_UINT8                            Command[256];
}SI_PIH_CSIM_COMMAND_CNF_STRU;

typedef struct
{
    SI_PIH_RESTRIC_CMD                  CmdType;
    SI_UINT16                           fileId;
    SI_UINT8                            Para1;
    SI_UINT8                            Para2;
    SI_UINT8                            Para3;
    SI_UINT8                            Rsv[3];
    SI_UINT8                            Command[256];
}SI_RESTRIC_ACCESS_STRU;
#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)

enum SI_PIH_SIM_INDEX_ENUM
{
    SI_PIH_SIM_REAL_SIM1          = 1,  /*Ӳ��*/
    SI_PIH_SIM_VIRT_PSIM          = 11, /*��������*/
    SI_PIH_SIM_VIRT_SSIM          = 12, /*�����ӿ�*/
    SI_PIH_SIM_INDEX_BUTT
};
typedef VOS_UINT8 SI_PIH_SIM_INDEX_ENUM_UINT8;


typedef struct
{
    SI_PIH_SIM_SLOT_ENUM_UINT8          enSlot;         /*����*/
    SI_PIH_SIM_STATE_ENUM_UINT8         enVSimState;    /*vSIM��״̬*/
    SI_PIH_CARD_USE_ENUM_UINT8          enCardUse;      /*���ܷ�ʹ��*/
    SI_PIH_SIM_INDEX_ENUM_UINT8         enVsimIndex;    /*ȷ�����ӿ���������*/
}SI_PIH_EVENT_HVSST_QUERY_CNF_STRU;


typedef struct
{
    SI_PIH_SIM_INDEX_ENUM_UINT8         enVsimIndex;   /*������*/
    VOS_UINT8                           aucRsv[3];     /*��λ*/
    VSIM_ALGORITHM_TYPE_ENUM_UINT32     enAlgorithm;   /*���ܷ�ʽ*/
    VSIM_KEYDATA_STRU                   stCkey;        /*�ͻ��˹�Կ*/
    VSIM_KEYDATA_STRU                   stSkey;        /*��������Կ*/
} SI_PIH_HVSDH_QUERY_CNF_STRU;


typedef struct
{
    VOS_UINT32                          ulDataLen;    /*���ݳ���*/
    VOS_UINT8                           *pucData;     /*����ָ��*/
}SI_PIH_U8LV_DATA_STRU;


typedef struct
{
    SI_PIH_U8LV_DATA_STRU               stFileName;
    SI_PIH_U8LV_DATA_STRU               stFileSubName;
    VOS_UINT32                          ulRef;
    VOS_UINT32                          ulTotalNum;
    VOS_UINT32                          ulIndex;
    SI_PIH_SIM_INDEX_ENUM_UINT8         enVsimIndex;
    VOS_UINT8                           aucRsv[3];
    SI_PIH_U8LV_DATA_STRU               stFileData;
}SI_PIH_FILEWRITE_DATA_STRU;


enum SI_PIH_KEY_INDEX_ENUM
{
    SI_PIH_KEY_REAL_SIM1          = 1,  /*Ӳ��*/
    SI_PIH_KEY_VIRT_PSIM          = 11, /*��������*/
    SI_PIH_KEY_VIRT_SSIM          = 12, /*�����ӿ�*/
    SI_PIH_KEY_DEVICE_KEY        = 21, /*Device key */
    SI_PIH_KEY_CONTENT_KEY     = 22, /*Content key*/
    SI_PIH_KEY_INDEX_BUTT
};
typedef VOS_UINT8 SI_PIH_KEY_INDEX_ENUM_UINT8;


typedef struct
{
    SI_PIH_KEY_INDEX_ENUM_UINT8         enKeyIndex;   /*������*/
    VOS_UINT8                           aucRsv[3];     /*��λ*/
    VSIM_KEYDATA_STRU                   stSharekey;        /*������Կ*/
} SI_PIH_HVSHDH_SET_CNF_STRU;


typedef struct
{
    VOS_UINT32                           ulNumLen;
    VOS_UINT8                            aucNum[NV_VSIM_DIEID_MAXLEN+1];
} SI_PIH_HVDIEID_QRY_CNF_STRU;


enum SI_PIH_CLEAN_KEY_INDEX_ENUM
{
    SI_PIH_CLEAN_KEY_ALL        = 0, /*����������Կ*/
    SI_PIH_CLEAN_KEY_PSIM,           /*����������Կ*/
    SI_PIH_CLEAN_KEY_SSIM,           /*�����ӿ���Կ*/
    SI_PIH_CLEAN_KEY_DEVICE,         /*����Device key */
    SI_PIH_CLEAN_KEY_CONTENT,        /*����Content key*/
    SI_PIH_CLEAN_KEY_INDEX_BUTT
};
typedef VOS_UINT8 SI_PIH_CLEAN_KEY_INDEX_ENUM_UINT8;
typedef struct
{
    VOS_UINT32                          ulReDhFlag;
}SI_PIH_HVRDH_IND_STRU;

#else

typedef struct
{
    VOS_BOOL                            ulReDhFlag;
}SI_PIH_HVRDH_IND_STRU;
enum SI_PIH_SIM_INDEX_ENUM
{
    SI_PIH_SIM_REAL_SIM1          = 1,
    SI_PIH_SIM_VIRT_SIM1          = 11,
    SI_PIH_SIM_INDEX_BUTT
};
typedef VOS_UINT8 SI_PIH_SIM_INDEX_ENUM_UINT8;

typedef struct
{
    SI_PIH_SIM_SLOT_ENUM_UINT8          enSlot;         /*����*/
    SI_PIH_SIM_STATE_ENUM_UINT8         enVSimState;    /*vSIM��״̬����Ӳ��״̬����*/
    SI_PIH_CARD_USE_ENUM_UINT8          enCardUse;      /*���ܷ�ʹ��*/
    VOS_UINT8                           ucRsv;
}SI_PIH_EVENT_HVSST_QUERY_CNF_STRU;

typedef struct
{
    VSIM_ALGORITHM_TYPE_ENUM_UINT32     enAlgorithm;
    VSIM_KEYDATA_STRU                   stCkey;
    VSIM_KEYDATA_STRU                   stSkey;
} SI_PIH_HVSDH_QUERY_CNF_STRU;

typedef struct
{
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           *pucData;
}SI_PIH_U8LV_DATA_STRU;

typedef struct
{
    SI_PIH_U8LV_DATA_STRU               stFileName;
    SI_PIH_U8LV_DATA_STRU               stFileSubName;
    VOS_UINT32                          ulRef;
    VOS_UINT32                          ulTotalNum;
    VOS_UINT32                          ulIndex;
    SI_PIH_U8LV_DATA_STRU               stFileData;
}SI_PIH_FILEWRITE_DATA_STRU;
#endif/*end (FEATURE_ON == MBB_FEATURE_VSIM_HUK)*/
typedef struct
{
    VOS_UINT8                           ucIndex;
    SI_PIH_SIM_STATE_ENUM_UINT8         enSIMSet;
    VOS_UINT8                           ucSlot;
    VOS_UINT8                           ucRsv;
} SI_PIH_HVSST_SET_STRU;

typedef struct
{
    VOS_UINT32                          ulMCC;
    VOS_UINT32                          ulMNC;
}SI_PIH_PLMN_STRU;

typedef struct
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCardCap;  /* ��BITλ���д�ţ�BIT1:SIM,BIT2:USIM */
    VOS_UINT8                           ucCardType; /* ��BITλ���д�ţ�BIT1:SIM,BIT2:USIM */
    VOS_UINT8                           ucRsv;
    VOS_UINT8                           aucImsi[USIMM_EF_IMSI_LEN*2];   /* IMSI,��Ҫ����ASCII�볤������һ�� */
    VOS_UINT16                          usPlmnNum;  /* PLMN���� */
    SI_PIH_PLMN_STRU                    astPlmn[SI_PIH_HPLMN_MAX_NUM]; /* PLMN���� */
}SI_PIH_CARD_CONTENT_STRU;

typedef struct
{
    SI_PIH_CARD_CONTENT_STRU            astSimCard[SI_PIH_CARD_BUTT];   /* ֧�ֿ�������������Ӳ�������⿨ */
}SI_PIH_HVSCONT_QUERY_CNF_STRU;


typedef struct
{
    VOS_UINT8                       aucIK[17];          /*Len+Data*/
    VOS_UINT8                       aucCK[17];          /*Len+Data*/
    VOS_UINT8                       aucAuts[15];        /*Len+Data*/
    VOS_UINT8                       aucAuthRes[17];     /*Len+Data*/
}SI_PIH_UICCAKA_DATA_STRU;

typedef struct
{
    VOS_UINT8                       aucKs_ext_NAF[USIMM_T0_APDU_MAX_LEN];   /*Len+Data*/
}SI_PIH_UICCNAF_DATA_STRU;

typedef struct
{
    SI_PIH_AUTHSTATUS_ENUM_UINT32       enStatus;
    SI_PIH_UICCAPP_ENUM_UINT32          enAppType;      /* Ӧ������ */
    SI_PIH_UICCAUTH_ENUM_UINT32         enAuthType;     /* ��Ȩ���� */
    SI_PIH_UICCAKA_DATA_STRU            stAkaData;
    SI_PIH_UICCNAF_DATA_STRU            stNAFData;
}SI_PIH_UICCAUTH_CNF_STRU;

typedef struct
{
    SI_PIH_ACCESSTYPE_ENUM_UINT8        enCmdType;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT16                          usEfId;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucCommand[USIMM_T0_APDU_MAX_LEN];
}SI_PIH_UICCACCESSFILE_CNF_STRU;



typedef struct
{
    VOS_UINT32                          ulRandLen;
    VOS_UINT8                           aucRand[SI_AUTH_DATA_MAX];
    VOS_UINT32                          ulAuthLen;
    VOS_UINT8                           aucAuth[SI_AUTH_DATA_MAX];
}SI_PIH_UICCAUTH_AKA_STRU;

typedef struct
{
    VOS_UINT32                          ulNAFIDLen;
    VOS_UINT8                           aucNAFID[SI_AUTH_DATA_MAX];
    VOS_UINT32                          ulIMPILen;
    VOS_UINT8                           aucIMPI[SI_AUTH_DATA_MAX];
}SI_PIH_UICCAUTH_NAF_STRU;

typedef struct
{
    SI_PIH_UICCAUTH_ENUM_UINT32         enAuthType;
    SI_PIH_UICCAPP_ENUM_UINT32          enAppType;
    union
    {
        SI_PIH_UICCAUTH_AKA_STRU        stAka;
        SI_PIH_UICCAUTH_NAF_STRU        stKsNAF;
    }uAuthData;
}SI_PIH_UICCAUTH_STRU;

typedef struct
{
    SI_PIH_UICCAPP_ENUM_UINT32          enAppType;
    SI_PIH_ACCESSTYPE_ENUM_UINT8        enCmdType;
    VOS_UINT8                           ucRecordNum;
    VOS_UINT16                          usEfId;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucCommand[USIMM_T0_APDU_MAX_LEN];
    VOS_UINT16                          usPathLen;
    VOS_UINT16                          ausPath[USIMM_MAX_PATH_LEN];
}SI_PIH_ACCESSFILE_STRU;

typedef struct
{
    VOS_UINT8                           ucMode;
    VOS_UINT8                           ucHasCModule;
    VOS_UINT8                           ucHasGModule;
    VOS_UINT8                           ucRfu;
} SI_PIH_EVENT_CARDTYPE_QUERY_CNF_STRU;

/*****************************************************************************
  5 �ص��������ݽṹ����
*****************************************************************************/

typedef struct
{
    SI_UINT16                           ClientId;
    SI_UINT8                            OpId;
    SI_UINT8                            Reserve;
    SI_PIH_EVENT                        EventType;
    SI_PIH_ERROR                        PIHError;
    union
    {
        SI_PIH_EVENT_FDN_CNF_STRU                           FDNCnf;
        SI_PIH_EVENT_BDN_CNF_STRU                           BDNCnf;
        SI_PIH_CSIM_COMMAND_CNF_STRU                        GAccessCnf;
        SI_PIH_ISDB_ACCESS_COMMAND_CNF_STRU                 IsdbAccessCnf;
        VOS_UINT32                                          ulSessionID;
        SI_PIH_CGLA_COMMAND_CNF_STRU                        stCglaCmdCnf;
        SI_PIH_ATR_QRY_CNF_STRU                             stATRQryCnf;
        SI_PIH_EVENT_HVSST_QUERY_CNF_STRU                   HVSSTQueryCnf;
        SI_PIH_HVSDH_QUERY_CNF_STRU                         HvsDHCnf;
        SI_PIH_HVSCONT_QUERY_CNF_STRU                       HvsContCnf;
        SI_PIH_HVRDH_IND_STRU                               HvrdhInd;
        SI_PIH_UICCAUTH_CNF_STRU                            UiccAuthCnf;
        SI_PIH_UICCACCESSFILE_CNF_STRU                      UiccAcsFileCnf;
        SI_PIH_EVENT_CARDTYPE_QUERY_CNF_STRU                CardTypeCnf;
#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
        SI_PIH_VSIM_HUK_VAL_STRU                            HvadhCnf;
        SI_PIH_HVSHDH_SET_CNF_STRU                        HvshdhCnf;
        SI_PIH_HVDIEID_QRY_CNF_STRU                       HvdieIDCnf;
#endif/*end (FEATURE_ON == MBB_FEATURE_VSIM_HUK)*/
    }PIHEvent;
}SI_PIH_EVENT_INFO_STRU;

/*****************************************************************************
  6 ��������
*****************************************************************************/
extern VOS_VOID SI_PIH_ChangePollTimer(SI_PIH_TIMER_NAME_ENUM_UINT32 enTimerName,SI_PIH_POLLTIMER_STATE_ENUM_UINT32 enState, VOS_UINT32 ulTimerLen, VOS_UINT32 enData);

extern SI_UINT32 SI_PIH_FdnEnable(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId,SI_UINT8* pPIN2);

extern SI_UINT32 SI_PIH_FdnDisable(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId,SI_UINT8* pPIN2);

extern SI_UINT32  SI_PIH_FdnBdnQuery(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId,SI_PIH_QUERY_TYPE_ENUM_UINT32   QueryType);

extern SI_UINT32 SI_PIH_GenericAccessReq(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId, SI_PIH_CSIM_COMMAND_STRU* pstData);

extern SI_UINT32 SI_PIH_IsdbAccessReq(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, SI_PIH_ISDB_ACCESS_COMMAND_STRU *pstData);

extern SI_UINT32 SI_PIH_CchoSetReq(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, SI_PIH_CCHO_COMMAND_STRU *pstCchoCmd);

extern SI_UINT32 SI_PIH_CchcSetReq(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, VOS_UINT32 ulSessionID);

extern VOS_UINT32 SI_PIH_HvSstQuery(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId);

extern VOS_UINT32 SI_PIH_HvSstSet (MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, SI_PIH_HVSST_SET_STRU *pstHvSStSet);


extern VOS_UINT32 SI_PIH_HvsDHQuery(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId);

extern VOS_UINT32 SI_PIH_HvsContQuery(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId);

#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
extern VOS_UINT32 SI_PIH_HvAdhSet(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, SI_PIH_HVADH_SET_STRU *pstHvAdhSet);

extern VOS_UINT32 SI_PIH_HvsContSet(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, SI_PIH_SIM_INDEX_ENUM_UINT8 enVsimIndex);

extern VOS_UINT32 SI_PIH_HvsDHSet(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, SI_PIH_SIM_INDEX_ENUM_UINT8 enVsimIndex);
extern VOS_UINT32 SI_PIH_HvdieIDQuery(MN_CLIENT_ID_T ClientId,MN_OPERATION_ID_T OpId);
extern VOS_UINT32 SI_PIH_HvshDHSet(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, SI_PIH_KEY_INDEX_ENUM_UINT8 enKeyIndex);

extern VOS_UINT32 SI_PIH_HvdDHSet(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, SI_PIH_CLEAN_KEY_INDEX_ENUM_UINT8 enCleanKeyType);

#else
extern VOS_UINT32 SI_PIH_HvsDHSet(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, VSIM_KEYDATA_STRU* pstSKey);
#endif/*end (FEATURE_ON == MBB_FEATURE_VSIM_HUK)*/

extern VOS_UINT32 SI_PIH_AtFileWrite(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, SI_PIH_FILEWRITE_DATA_STRU *pstData);

extern SI_UINT32 SI_PIH_CglaSetReq(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, SI_PIH_CGLA_COMMAND_STRU *pstData);

extern SI_UINT32 SI_PIH_GetCardATRReq(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId);

extern SI_UINT32 WuepsPIHPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase);

extern VOS_VOID SI_PIH_PidMsgProc(PS_SI_MSG_STRU *pMsg);

extern VOS_UINT32 PIH_RegUsimCardStatusIndMsg(VOS_UINT32 ulRegPID);

extern VOS_UINT32 PIH_DeregUsimCardStatusIndMsg(VOS_UINT32 ulRegPID);

extern VOS_UINT32 PIH_RegCardRefreshIndMsg(VOS_UINT32 ulRegPID);

extern VOS_UINT32 PIH_DeregCardRefreshIndMsg(VOS_UINT32 ulRegPID);

extern VOS_UINT32 PIH_RegISIMCardIndMsg(VOS_UINT32 ulReceiverPID);

extern VOS_UINT32 SI_PIH_CardTypeQuery(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId);

/*������ӿڵ�����*/

extern VOS_UINT32 PIH_RegUsimCardStatusIndMsg_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                          ulRegPID);


extern VOS_UINT32 PIH_DeregUsimCardStatusIndMsg_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                          ulRegPID);


extern VOS_UINT32 PIH_RegCardRefreshIndMsg_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                          ulRegPID);


extern VOS_UINT32 PIH_DeregCardRefreshIndMsg_Instance(
    MODEM_ID_ENUM_UINT16                enModemID,
    VOS_UINT32                          ulRegPID);

extern VOS_UINT32 SI_PIH_UiccAuthReq(MN_CLIENT_ID_T                ClientId,
                                    MN_OPERATION_ID_T               OpId,
                                    SI_PIH_UICCAUTH_STRU            *pstData);


extern VOS_UINT32 SI_PIH_AccessUICCFileReq(MN_CLIENT_ID_T       ClientId,
                                    MN_OPERATION_ID_T               OpId,
                                    SI_PIH_ACCESSFILE_STRU          *pstData);


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

#endif /* end of SiAppSim.h */

