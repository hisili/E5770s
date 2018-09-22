/******************************************************************************
 */
/*
 */
/*                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾
 */
/*
 */
/******************************************************************************
 */
/*  �� �� ��   : at_lte_eventreport_mbb.h
 */
/*  �� �� ��   : V1.0
 */

/*  ��������   : 2014-06-09
 */
/*  ��������   : ��Ʒ�����м��޸�at�����ļ�
 */
/*  �����б�   :
 */
/*  �޸���ʷ   :
 */
/*  1.��    �� : 2011-03-10
 */

/*    �޸����� : �����ļ�
 */
/*
 */
/******************************************************************************
 */
/*************************************************************************************
*************************************************************************************/



#ifndef _MBB_PS_CS_COMMON_H__
#define _MBB_PS_CS_COMMON_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "TafAppMma.h"
#include "TafApsApi.h"
#include "mbb_common.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if (FEATURE_ON == MBB_WPG_COMMON)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define AT_NWSCAN_SET_PARA_TIME                            (60000)
#define BUFFER_LENGTH_256                                           256
#define AT_HFREQINFO_NO_REPORT            0
#define AT_HFREQINFO_REPORT                   1

#define AT_IPV6_FIRST_VERSION           (1)
#define AT_IPV6_SECOND_VERSION          (2)

/*��֧������PDP��������Ŀ��*/
#define TAF_MIN_CID                     (1)


#define MN_MMA_LTE_EUTRAN_BAND1     (0x1)
#define MN_MMA_LTE_EUTRAN_BAND2     (0x2)
#define MN_MMA_LTE_EUTRAN_BAND3     (0x4)
#define MN_MMA_LTE_EUTRAN_BAND4     (0x8)
#define MN_MMA_LTE_EUTRAN_BAND5     (0x10)
#define MN_MMA_LTE_EUTRAN_BAND6     (0x20)
#define MN_MMA_LTE_EUTRAN_BAND7     (0x40)
#define MN_MMA_LTE_EUTRAN_BAND8     (0x80)
#define MN_MMA_LTE_EUTRAN_BAND9     (0x100)
#define MN_MMA_LTE_EUTRAN_BAND10    (0x200)
#define MN_MMA_LTE_EUTRAN_BAND11    (0x400)
#define MN_MMA_LTE_EUTRAN_BAND12    (0x800)
#define MN_MMA_LTE_EUTRAN_BAND13    (0x1000)
#define MN_MMA_LTE_EUTRAN_BAND14    (0x2000)
#define MN_MMA_LTE_EUTRAN_BAND15    (0x4000)
#define MN_MMA_LTE_EUTRAN_BAND16    (0x8000)
#define MN_MMA_LTE_EUTRAN_BAND17    (0x10000)
#define MN_MMA_LTE_EUTRAN_BAND18    (0x20000)
#define MN_MMA_LTE_EUTRAN_BAND19    (0x40000)
#define MN_MMA_LTE_EUTRAN_BAND20    (0x80000)
#define MN_MMA_LTE_EUTRAN_BAND21    (0x100000)
#define MN_MMA_LTE_EUTRAN_BAND22    (0x200000)
#define MN_MMA_LTE_EUTRAN_BAND23    (0x400000)
#define MN_MMA_LTE_EUTRAN_BAND24    (0x800000)
#define MN_MMA_LTE_EUTRAN_BAND25    (0x1000000)
#define MN_MMA_LTE_EUTRAN_BAND26    (0x2000000)
#define MN_MMA_LTE_EUTRAN_BAND27    (0x4000000)
#define MN_MMA_LTE_EUTRAN_BAND28    (0x8000000)
#define MN_MMA_LTE_EUTRAN_BAND29    (0x10000000)
#define MN_MMA_LTE_EUTRAN_BAND30    (0x20000000)
#define MN_MMA_LTE_EUTRAN_BAND31    (0x40000000)
#define MN_MMA_LTE_EUTRAN_BAND32    (0x80000000)
#define MN_MMA_LTE_EUTRAN_BAND33    (0x1)
#define MN_MMA_LTE_EUTRAN_BAND34    (0x2)
#define MN_MMA_LTE_EUTRAN_BAND35    (0x4)
#define MN_MMA_LTE_EUTRAN_BAND36    (0x8)
#define MN_MMA_LTE_EUTRAN_BAND37    (0x10)
#define MN_MMA_LTE_EUTRAN_BAND38    (0x20)
#define MN_MMA_LTE_EUTRAN_BAND39    (0x40)
#define MN_MMA_LTE_EUTRAN_BAND40    (0x80)
#define MN_MMA_LTE_EUTRAN_BAND41    (0x100)
#define MN_MMA_LTE_EUTRAN_BAND42    (0x200)
#define MN_MMA_LTE_EUTRAN_BAND43    (0x400)
#define MN_MMA_LTE_EUTRAN_BAND44    (0x800)
#define MN_MMA_LTE_EUTRAN_BAND45    (0x1000)    
#define MN_MMA_LTE_EUTRAN_BAND46    (0x2000)
#define MN_MMA_LTE_EUTRAN_BAND47    (0x4000)
#define MN_MMA_LTE_EUTRAN_BAND48    (0x8000)
#define MN_MMA_LTE_EUTRAN_BAND49    (0x10000)    
#define MN_MMA_LTE_EUTRAN_BAND50    (0x20000)    
#define MN_MMA_LTE_EUTRAN_BAND51    (0x40000)    
#define MN_MMA_LTE_EUTRAN_BAND52    (0x80000)   
#define MN_MMA_LTE_EUTRAN_BAND53    (0x100000)   
#define MN_MMA_LTE_EUTRAN_BAND54    (0x200000)   
#define MN_MMA_LTE_EUTRAN_BAND55    (0x400000)   
#define MN_MMA_LTE_EUTRAN_BAND56    (0x800000)    
#define MN_MMA_LTE_EUTRAN_BAND57    (0x1000000)   
#define MN_MMA_LTE_EUTRAN_BAND58    (0x2000000)   
#define MN_MMA_LTE_EUTRAN_BAND59    (0x4000000)   
#define MN_MMA_LTE_EUTRAN_BAND60    (0x8000000)    
#define MN_MMA_LTE_EUTRAN_BAND61    (0x10000000)   
#define MN_MMA_LTE_EUTRAN_BAND62    (0x20000000)    
#define MN_MMA_LTE_EUTRAN_BAND63    (0x40000000)   
#define MN_MMA_LTE_EUTRAN_BAND64    (0x80000000)    

#define MN_MMA_LTE_LOW_BAND_NONE        (0x0) 

#define MN_MMA_LTE_LOW_BAND_ALL         (MN_MMA_LTE_EUTRAN_BAND1 | MN_MMA_LTE_EUTRAN_BAND2 \
    | MN_MMA_LTE_EUTRAN_BAND3 | MN_MMA_LTE_EUTRAN_BAND4 \
    | MN_MMA_LTE_EUTRAN_BAND5 | MN_MMA_LTE_EUTRAN_BAND6 \
    | MN_MMA_LTE_EUTRAN_BAND7 | MN_MMA_LTE_EUTRAN_BAND8 \
    | MN_MMA_LTE_EUTRAN_BAND9 | MN_MMA_LTE_EUTRAN_BAND10 \
    | MN_MMA_LTE_EUTRAN_BAND11 | MN_MMA_LTE_EUTRAN_BAND12 \
    | MN_MMA_LTE_EUTRAN_BAND13 | MN_MMA_LTE_EUTRAN_BAND14 \
    | MN_MMA_LTE_EUTRAN_BAND15 | MN_MMA_LTE_EUTRAN_BAND16 \
    | MN_MMA_LTE_EUTRAN_BAND17 | MN_MMA_LTE_EUTRAN_BAND18 \
    | MN_MMA_LTE_EUTRAN_BAND19 | MN_MMA_LTE_EUTRAN_BAND20 \
    | MN_MMA_LTE_EUTRAN_BAND21 | MN_MMA_LTE_EUTRAN_BAND22 \
    | MN_MMA_LTE_EUTRAN_BAND23 | MN_MMA_LTE_EUTRAN_BAND24 \
    | MN_MMA_LTE_EUTRAN_BAND25 | MN_MMA_LTE_EUTRAN_BAND26 \
    | MN_MMA_LTE_EUTRAN_BAND27 | MN_MMA_LTE_EUTRAN_BAND28 \
    | MN_MMA_LTE_EUTRAN_BAND29 | MN_MMA_LTE_EUTRAN_BAND30 \
    | MN_MMA_LTE_EUTRAN_BAND31 | MN_MMA_LTE_EUTRAN_BAND32)

#define MN_MMA_LTE_HIGH_BAND_ALL        (MN_MMA_LTE_EUTRAN_BAND33 | MN_MMA_LTE_EUTRAN_BAND34 \
    | MN_MMA_LTE_EUTRAN_BAND35 | MN_MMA_LTE_EUTRAN_BAND36 \
    | MN_MMA_LTE_EUTRAN_BAND37 | MN_MMA_LTE_EUTRAN_BAND38 \
    | MN_MMA_LTE_EUTRAN_BAND39 | MN_MMA_LTE_EUTRAN_BAND40 \
    | MN_MMA_LTE_EUTRAN_BAND41 | MN_MMA_LTE_EUTRAN_BAND42 \
    | MN_MMA_LTE_EUTRAN_BAND43 | MN_MMA_LTE_EUTRAN_BAND44 \
    | MN_MMA_LTE_EUTRAN_BAND45 | MN_MMA_LTE_EUTRAN_BAND46 \
    | MN_MMA_LTE_EUTRAN_BAND47 | MN_MMA_LTE_EUTRAN_BAND48 \
    | MN_MMA_LTE_EUTRAN_BAND49 | MN_MMA_LTE_EUTRAN_BAND50 \
    | MN_MMA_LTE_EUTRAN_BAND51 | MN_MMA_LTE_EUTRAN_BAND52 \
    | MN_MMA_LTE_EUTRAN_BAND53 | MN_MMA_LTE_EUTRAN_BAND54 \
    | MN_MMA_LTE_EUTRAN_BAND55 | MN_MMA_LTE_EUTRAN_BAND56 \
    | MN_MMA_LTE_EUTRAN_BAND57 | MN_MMA_LTE_EUTRAN_BAND58 \
    | MN_MMA_LTE_EUTRAN_BAND59 | MN_MMA_LTE_EUTRAN_BAND60 \
    | MN_MMA_LTE_EUTRAN_BAND61 | MN_MMA_LTE_EUTRAN_BAND62 \
    | MN_MMA_LTE_EUTRAN_BAND63 | MN_MMA_LTE_EUTRAN_BAND64)

/*check_point*/
#define ID_MSG_L4A_HCSQ_INFO_REQ         (0x0001102A)
#define ID_MSG_L4A_HCSQ_INFO_CNF         (0x0001102B)
#define ID_MSG_L4A_HCSQ_IND                    (0x0001102C)

#define ID_MSG_L4A_LTERSRP_INFO_REQ   (0x0001102D)
#define ID_MSG_L4A_LTERSRP_INFO_CNF   (0x0001102E)
#define ID_MSG_L4A_LTERSRP_IND              (0x0001102F)

#define ID_MSG_L4A_NOTIFY_ATRPT_REQ    (0x00012000)
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
#define ID_MSG_L4A_CIND_INFO_REQ       (0x00012001)
#define ID_MSG_L4A_CIND_INFO_CNF       (0x00012002)
#define ID_MSG_L4A_ANT_INFO_REQ        (0x00012003)
#define ID_MSG_L4A_ANT_INFO_CNF        (0x00012004)
#endif
/*�豸��������С����Ϊ4,��󳤶�Ϊ8,���ܺ�ĳ���Ϊ32*/
#define MAX_DLCK_ENCODE_LEN (32)
#define MIN_DLCK_CODE_LEN (4)
#define MAX_DLCK_CODE_LEN (8)
#define TAF_OPERATOR_PERSONALISATION_DLCK       0x07   /*�Զ���:ӡ�� TATA �豸����ѯ*/
#define TAF_OPERATOR_PERSONALISATION_SETDLCK    0x08   /*�Զ���:ӡ�� TATA �豸������*/

/*�˼�ͨ��ʱ����PLMN������*/
#define MMA_PLMN_LIST_MAX_LEN    (60)     

/****************************************/
/*       EONS ���뷽ʽ����            */
/****************************************/
#define TAF_PH_EONS_GSM_7BIT_DEFAULT  (0)
#define TAF_PH_EONS_GSM_7BIT_PACK       (1)
#define TAF_PH_EONS_UCS2_COMM              (2)
#define TAF_PH_EONS_UCS2_80                   (3) 
#define TAF_PH_EONS_UCS2_81                   (4) 
#define TAF_PH_EONS_UCS2_82                   (5) 
#define TAF_PH_EONS_ASCII                        (6)
#define TAF_PH_EONS_HEX_ASCII                (7)
/****************************************/
/*       EONS ��ȡ����                            */
/****************************************/
#define AT_EONS_TYPE_DEFAULT                       (1)
#define AT_EONS_TYPE_GMM                             (2)
#define AT_EONS_TYPE_PNN                              (3)
#define AT_EONS_TYPE_LOCAL                           (4)
#define AT_EONS_TYPE_MODULE                          (5)
#define AT_ENOS_PLMN_NAME_DEFAULT_LEN                (20)

/****************************************/
/*       PNN��ȡ��Ϣ�洢�ṹ         */
/****************************************/
#define TAF_PH_OPER_NETWORTNAME_LEN    (32)
#define TAF_PH_OPER_SPN_LEN                      (16)
/****************************************/
/*       PLMN ID ������󳤶�             */
/****************************************/
#define AT_PLMN_ID_MAX_LEN                       (6)
/****************************************/
/*       ��Ӧ�����USC2��󳤶�  */
/****************************************/
#define TAF_PH_OPER_PNN_USC2_CODE_LEN    (128)
#define TAF_PH_OPER_SPN_USC2_CODE_LEN    (64)

/*TAF_PH_EVT_EONS_NWNAME_CNF��ֵ������TafAppMma.h�е�TAF_MMA_EVT_NET_SCAN_CNF��ֵ��ͻ*/
#define TAF_PH_EVT_EONS_NWNAME_CNF              (80) /*�ϱ�EONS ����*/

#define AT_NWSCAN_WCDMA         0
#define AT_NWSCAN_CDMA            1
#define AT_NWSCAN_TDSCDMA      2
#define AT_NWSCAN_GSM               3
#define AT_NWSCAN_EDGE             4
#define AT_NWSCAN_LTE_FDD        6
#define AT_NWSCAN_LTE_TDD        7

#define AT_NWSCAN_MAX_PARA_NUM        3
#define AT_NWSCAN_BTU_RAT_NUM          2
#define AT_NWSCAN_BTT_BTL_RAT_NUM   1

#define TAF_PH_IS_WCDMA_RAT            0
#define TAF_PH_IS_TDSCDMA_RAT          1


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*�豸���Ĳ�������*/
typedef enum
{
     DEVICE_LOCK_MODE_DISABLE,    /*ȥ�����豸��*/
     DEVICE_LOCK_MODE_ENABLE,     /*�����豸��*/
     DEVICE_LOCK_MODE_INPUT,      /*��������*/
     DEVICE_LOCK_MODE_MODIFY,     /*�޸�����*/
     DEVICE_LOCK_MODE_MAX
}TATA_DEVICELOCK_ENUM;

/*���䱾��PLMN LIST �б�ѡ���ʶMNCλ��*/
enum PLMN_LIST_ID_LEN
{
    PLMN_ID_LEN_5 = 5,
    PLMN_ID_LEN_6,
    PLMN_ID_LEN_MAX
};
/*���䱾��PLMN LIST �б�ѡ���ʶPLMN ��ʽ*/
enum PLMN_LIST_NETWORKMODE
{
    PLMN_LIST_NETWORKMODE_GSM = 0,
    PLMN_LIST_NETWORKMODE_UMTS,
    PLMN_LIST_NETWORKMODE_LTE,
    PLMN_LIST_NETWORKMODE_CDMA,
    PLMN_LIST_NETWORKMODE_TDSCDMA,
    PLMN_LIST_NETWORKMODE_MAX
};

enum AT_LTERSRP_RAT_ENUM
{
    AT_LTERSRP_RAT_GSM = 0,
    AT_LTERSRP_RAT_WCDMA,
    AT_LTERSRP_RAT_LTE,
    AT_LTERSRP_RAT_BUTT
};

enum AT_HFREQINFO_RAT_TYPE_ENUM
{
    AT_HFREQINFO_RAT_TYPE_GSM = 1,
    AT_HFREQINFO_RAT_TYPE_CDMA, 
    AT_HFREQINFO_RAT_TYPE_WCDMA, 
    AT_HFREQINFO_RAT_TYPE_TDSCDMA, 
    AT_HFREQINFO_RAT_TYPE_WIMAX, 
    AT_HFREQINFO_RAT_TYPE_LTE       
};

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
#if ((FEATURE_ON == MBB_FEATURE_AT_CMD_FILTER) || ((defined (BSP_CONFIG_BOARD_WINGLE_MS2172S_818)) && (FEATURE_OFF == MBB_FEATURE_BOX_FTEN)))
/* LOCK����ṹ���� */
typedef struct
{
    VOS_UINT32 ulCmdIndex;
    VOS_UINT32 ulChkFlag;
    const VOS_UINT8* pszCmdName;
    VOS_UINT16 reserved1;
    VOS_UINT16 reserved2;
}AT_LOCK_CMD_TAB_STRU;
#endif

typedef struct
{
    VOS_UINT32 ulPid;        /* ���AT����DIAG�Ķ�Ӧ�� L4A����Ϣ����PID*/
    VOS_UINT32 ulClientId;   /* ��AT����*/
    VOS_UINT32 ulOpId;       /* �����֣���Զ������ÿ�������һ,���û����*/
} L4A_APPCTRL_STRU;

typedef struct
{
    L4A_APPCTRL_STRU stCtrl;
    VOS_UINT32 ulErrorCode;    /*������*/
    VOS_INT16 sRssi;          /*Rssi*/
    VOS_UINT16 usLevel;        /*����ֶ�*/
    VOS_INT16 sRsrp;          /*Rsrp*/
    VOS_INT16 sRsrq;          /*Rsrq*/
    VOS_INT32 sSinr;
} L4A_HCSQ_STRU;
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
typedef struct
{
    VOS_UINT32 mode;
    VOS_UINT32 keyp;
    VOS_UINT32 disp;
    VOS_UINT32 ind;
    VOS_UINT32 bfr;
}AT_CMD_CMER_PARA;
typedef struct
{
    L4A_APPCTRL_STRU stCtrl;
    VOS_UINT32 ulErrorCode;    /*������*/
    VOS_UINT8  ucSrvStatus;    /*��ǰ����״̬*/
    VOS_INT16  sRssi;          /*Rssi*/
    VOS_UINT16 usLevel;        /*����ֶ�*/
    VOS_INT16  sRsrp;          /*Rsrp*/
    VOS_INT16  sRsrq;          /*Rsrq*/
    VOS_INT32  sSinr;          /*Sinr*/
    VOS_UINT16 sAntLevel;      /*���ߵȼ�*/
} L4A_CIND_STRU;

typedef struct
{
    VOS_UINT32 battchg;
    VOS_UINT32 signal;    /*�ź�*/
    VOS_UINT32 service;   /*����*/
    VOS_UINT32 call;
    VOS_UINT32 roam;
    VOS_UINT32 smsfull;
    VOS_UINT32 packet;
    VOS_UINT32 callsetup;
}AT_CMD_CIND_PARA;
typedef struct
{
    L4A_APPCTRL_STRU stCtrl;
    VOS_UINT32       ulErrorCode;    /*������*/
    VOS_UINT8        ucSrvStatus;    /*��ǰ����״̬*/
    VOS_INT16        sRssi;          /*Rssi*/
    VOS_UINT16       usLevel;        /*����ֶ�*/
    VOS_INT16        sRsrp;          /*Rsrp*/
    VOS_INT16        sRsrq;          /*Rsrq*/
    VOS_INT32        sSinr;          /*Sinr*/
    VOS_UINT16       sAntLevel;      /*���ߵȼ�*/
} L4A_ANT_STRU;
#endif
typedef struct
{
    L4A_APPCTRL_STRU stCtrl;
    VOS_UINT32 ulErrorCode;    /*query result*/
    VOS_UINT16 usRssi;         /*Rssi*/
    VOS_UINT16 usLevel;        /* ����ֶ�*/
    VOS_INT16 sRsrp;          
    VOS_INT16 sRsrq;           
} L4A_LTERSRP_STRU;
/* AT_HFREQINFO_LTE_INFO_STRU����ṹ���� */
typedef struct
{
    VOS_UINT8  usBand;
    VOS_UINT8  reserved;
    VOS_UINT16 usNdl;
    VOS_UINT16 usDlFreq;
    VOS_UINT16 usDlBandwidth;
    VOS_UINT16 usNul;
    VOS_UINT16 usUlFreq;
    VOS_UINT16 usUlBandwidth;
}AT_HFREQINFO_LTE_INFO_STRU;

/*******************************************/
/*        AT^EONS����ṹ              */
/*******************************************/

typedef struct
{
    TAF_UINT16                 ucEonsType;
    TAF_UINT16                 ulLsNameLen;    
}AT_TAF_EONS_LEN_STRU;

typedef struct
{
    TAF_UINT8                  PlmnLen;                                                /* PLMN���� */
    VOS_CHAR                 PLMNId[AT_PLMN_ID_MAX_LEN + 1];          /* PLMN */
    TAF_UINT8                  EonsType;                                               /*EONS ��������*/
    AT_TAF_EONS_LEN_STRU       PlmnNameLen;  /*plmn_name_len*/
}AT_TAF_PLMN_ID;

typedef struct
{
    TAF_PLMN_ID_STRU      PlmnId;            /* MCC, MNC�洢�ṹ */
    TAF_UINT8                   PlmnLen;          /* PLMN���� */
    TAF_UINT8                   ucServiceStatus; /*��־��ǰ����״̬*/
    TAF_UINT8                   ucOnPlmn;          /*��ʶ��ǰ�Ƿ��ѯ��פPLMN*/
    TAF_UINT8                   ucEonsType;
}TAF_PH_PLMN_INFO_STRU;

typedef struct
{
    TAF_UINT8                   ucNameLen;                                 /* ���� */
    TAF_UINT8                   ucNamecode;                                /* ���� */
    TAF_UINT8                   aucName[TAF_PH_OPER_PNN_USC2_CODE_LEN + 1];     /* �����ַ��� */
    TAF_UINT8                   align;
}TAF_PH_NWNAME_INFO_STRU;

typedef struct
{
    TAF_PH_NWNAME_INFO_STRU  stLNameInfo;
    TAF_PH_NWNAME_INFO_STRU  stSNameInfo;
}TAF_PH_FSNWNAME_INFO_STRU;

typedef struct
{
    TAF_UINT8                   ucDispMode;                     /* spn��ʾģʽ */
    TAF_UINT8                   ucSpnLen;                       /* spn���� */
    TAF_UINT8                   ucSPNCode;                      /* spn���뷽ʽ */
    TAF_UINT8                   aucSpn[TAF_PH_OPER_SPN_USC2_CODE_LEN + 1];      /* SPN���� */
}TAF_PH_EONS_SPN_INFO_STRU;

typedef struct
{
    TAF_PH_PLMN_INFO_STRU             stPlmnInfo;    /* PLMN��Ϣ */
    TAF_PH_EONS_SPN_INFO_STRU         stSpnInfo;     /* SPN��Ϣ */
    TAF_PH_FSNWNAME_INFO_STRU         stNWName;      /* ����������Ϣ */
}TAF_PH_EONS_INFO_STRU;

typedef struct
{
    TAF_PHONE_EVENT                  PhoneEvent;
    MN_OPERATION_ID_T               OpId;
    MN_CLIENT_ID_T                     ClientId;
    TAF_PH_EONS_INFO_STRU        stEonsInfo;          /* EONS��ѯ��Ϣ */
}TAF_PH_EONS_INFO_RSP_STRU;

/*��ȡPLMN LISTֻ��Ҫ��ȡ�������������¶���ṹ��
ֻ��ID�ͳ����Լ�MNC����*/
typedef struct
{
    TAF_UINT8                   PlmnLen;
    TAF_PLMN_ID_STRU            PlmnId;
    TAF_CHAR                    aucOperatorNameLong[TAF_PH_OPER_NAME_LONG ];
}TAF_PH_PLMN_NAME_STRU;
/*˫�˼�ͨ�Žṹ�壬��Ҫ��ʶ��ǰCALL BACK���ͼ�
Я����PLMN ��Ϣ����*/
typedef struct
{
    TAF_PHONE_EVENT             PhoneEvent;
    MN_OPERATION_ID_T           OpId;
    MN_CLIENT_ID_T              ClientId;
    TAF_UINT16                  usPlmnListNums;
    TAF_UINT16                  usPlmnListtotalNums;
    TAF_PH_PLMN_NAME_STRU       PlmnListInfo[MMA_PLMN_LIST_MAX_LEN];
}TAF_PH_PLMN_INFO_LIST_STRU; 


typedef struct
{    
    TAF_INT32                 ucRssiValue;          /*ת���ȼ�����ź�ǿ��*/
    TAF_INT16                 ucRSCP;                 /*3G�µ�RSCP��4G�µ�RSRP*/
    TAF_INT16                 ucEcio;                  /*3G�µ�ECIO��4G�µ�SINR*/
    TAF_INT16                 ucRsrq;                  /*4G�µ�RSRQ*/
    TAF_UINT8                 ucSysMode;           /*ϵͳģʽ*/
    TAF_UINT8                 ucSinr;                   /*CDMA�µ�SINR��Ԥ��*/
}TAF_PH_HCSQ_STRU;
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
typedef struct
{
    TAF_UINT8                 ucSrvStatus;          /*����״̬*/
    TAF_INT32                 ucRssiValue;          /*ת���ȼ�����ź�ǿ��*/
    TAF_INT16                 ucRSCP;               /*3G�µ�RSCP��4G�µ�RSRP*/
    TAF_INT16                 ucEcio;               /*3G�µ�ECIO��4G�µ�SINR*/
    TAF_INT16                 ucRsrq;               /*4G�µ�RSRQ*/
    TAF_UINT8                 ucSysMode;            /*ϵͳģʽ*/
    TAF_UINT8                 ucSinr;               /*CDMA�µ�SINR��Ԥ��*/
    TAF_UINT8                 ucAntLevel;           /*����ˮƽ�ȼ�*/
}TAF_PH_CIND_STRU;
typedef struct
{
    TAF_UINT8                 ucSrvStatus;          /*����״̬*/
    TAF_INT32                 ucRssiValue;          /*ת���ȼ�����ź�ǿ��*/
    TAF_INT16                 ucRSCP;               /*3G�µ�RSCP��4G�µ�RSRP*/
    TAF_INT16                 ucEcio;               /*3G�µ�ECIO��4G�µ�SINR*/
    TAF_INT16                 ucRsrq;               /*4G�µ�RSRQ*/
    TAF_UINT8                 ucSysMode;            /*ϵͳģʽ*/
    TAF_UINT8                 ucSinr;               /*CDMA�µ�SINR��Ԥ��*/
    TAF_UINT8                 ucAntLevel;           /*����ˮƽ�ȼ�*/
}TAF_PH_ANT_STRU;
#endif
typedef VOS_UINT8 AT_LTERSRP_RAT_ENUM_UINT8;
typedef VOS_UINT8 AT_HFREQINFO_REPORT_TYPE;
typedef VOS_UINT8 AT_HFREQINFO_RAT_TYPE_ENUM_UINT8;
typedef struct 
{
    VOS_UINT32 ulDLfreqlow;/* ��λΪ100khz*/
    VOS_UINT32 ulNoffdl;
    VOS_UINT32 ulULfreqlow;/* ��λΪ100khz*/
    VOS_UINT32 ulNofful;
}LTE_BANDINFO_STRU;

typedef VOS_UINT32 (*AT_L4A_MSG_FUN)(VOS_VOID* pMsgBlock);
typedef struct
{
    VOS_UINT32 ulMsgId;
    AT_L4A_MSG_FUN atL4aMsgProc;
}AT_L4A_MSG_FUN_TABLE_STRU;

typedef struct
{
    VOS_MSG_HEADER                                                                      /* _H2ASN_Skip */
    VOS_UINT32 enMsgId;                                                                   /* _H2ASN_Skip */
} L4A_ATRPT_NOTIFY_INFO_REQ_STRU;

typedef enum{
    TIME_FORMAT_RPT_TIME,
    TIME_FORMAT_RPT_NWTIME,
    TIME_FORMAT_QRY_NWTIME,
    TIME_FORMAT_QRY_CCLK,
}TIME_FORMAT_ENUM;

typedef VOS_UINT32 TIME_FORMAT_ENUM_UINT32;

#if (FEATURE_ON == MBB_FEATURE_FAKE_ON_OFF)

typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgName;                              /*_H2ASN_Skip*/
    VOS_UINT8                           ucOpid;
    VOS_UINT8                           aucReserve[1];
    USIMM_CARD_SERVIC_ENUM_UINT32       ucSimServiceStatus;  /* SIM ������״̬*/
}TAF_MMA_CFUN_USIM_STATUS_IND_STRU;
#endif/*FEATURE_ON == MBB_FEATURE_FAKE_ON_OFF*/

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/
extern VOS_UINT32                                                    g_ulAtUsbDebugFlag;
extern VOS_CHAR                                                      g_szBufForDebug[BUFFER_LENGTH_256 + 1];
extern AT_HFREQINFO_REPORT_TYPE                      g_AtHFreqinforeport;

#if (FEATURE_ON == MBB_FEATURE_AT_CMD_FILTER)
extern AT_LOCK_CMD_TAB_STRU gastAtLockCmdTab[];
extern const TAF_UINT16 gusAtLockCmdNum;
#endif
/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID AT_PS_HangupAllCall(VOS_UINT16 usClientId);

#define AT_APP_GET_USR_CID()             (g_stAtAppPdpEntity.stUsrInfo.ucUsrCid)


VOS_UINT32 Taf_NwScanHandle(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId,TAF_PH_NW_SCAN_STRU stNwScanPara);
TAF_UINT32 TAF_GetPlmnList ( MN_CLIENT_ID_T  ClientId, MN_OPERATION_ID_T OpId,VOS_UINT32 ulCurIndex);
TAF_UINT32 TAF_EONSGetNWName(MN_CLIENT_ID_T ClientId, MN_OPERATION_ID_T OpId, AT_TAF_PLMN_ID stPlmn);

/*check_point: TAF_PS_GetDsFlowInfo*/
VOS_UINT32 TAF_PS_GetDsFlowInfo(
    VOS_UINT32                          ulModuleId,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucUsrCid,
    VOS_UINT8                           ucOpId
);

extern VOS_VOID SI_PIH_InitImsiCheckTimer(VOS_VOID);

extern TAF_UINT16 At_PrintNwTimeInfo(
    NAS_MM_INFO_IND_STRU                *pstMmInfo,
    TAF_UINT16          usLength,
    CONST_T VOS_CHAR *cmd,
    CONST_T VOS_CHAR *cmd_sep,
    CONST_T VOS_CHAR *ending_str,
    TIME_FORMAT_ENUM_UINT32 eTimeFormat);
extern NAS_MM_INFO_IND_STRU* At_GetTimeInfo(VOS_UINT8 ucIndex);
TAF_VOID At_QryMmPlmnIdRspProc(
    TAF_UINT8                           ucIndex,
    TAF_UINT8                           OpId,
    TAF_VOID                            *pPara
);

extern VOS_UINT32 AT_ConvertCharToHex(VOS_UINT8 ucChar, VOS_UINT8 *pucHexValue);
extern VOS_UINT32 AT_QryCurrSysMode( VOS_UINT8 ucIndex );
extern TAF_VOID At_PbUnicode80FormatPrint(TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen, TAF_UINT8 *pucDst, TAF_UINT16 *pusDstLen);
extern TAF_VOID At_PbUnicode81FormatPrint(TAF_UINT8 *puc81Code, TAF_UINT8 *pucDst, TAF_UINT16 *pusDstLen);
extern TAF_VOID At_PbUnicode82FormatPrint(TAF_UINT8 *puc82Code, TAF_UINT8 *pucDst, TAF_UINT16 *pusDstLen);
extern TAF_UINT16 At_TafCallBackNWNameProc(TAF_UINT8* pData);

#define AT_USB_DEBUG_PRINT()        {\
                                        if (VOS_TRUE == g_ulAtUsbDebugFlag)\
                                        {\
                                            (VOS_VOID)vos_printf("===>%s,%d \n",__func__, __LINE__);\
                                        }\
                                    }
 
#define AT_USB_DEBUG_PRINT_1(var1)  {\
                                        if (VOS_TRUE == g_ulAtUsbDebugFlag)\
                                        {\
                                            (VOS_VOID)vos_printf("===>%s, %d msg id = %d\n", __func__, __LINE__, var1);\
                                        }\
                                    }

#define AT_USB_DEBUG_PRINT_3(var1, var2, var3) {\
    if (VOS_TRUE == g_ulAtUsbDebugFlag)\
    {\
        PS_MEM_SET(g_szBufForDebug, 0, (BUFFER_LENGTH_256 + 1));\
        strncpy(g_szBufForDebug, var3, (var2 > BUFFER_LENGTH_256) ? BUFFER_LENGTH_256 : (var2 > 0 ? (var2 - 1) : 0));\
        (VOS_VOID)vos_printf("===>%s: %d, PortNo = %d, length = %d, data = [%s]\n",\
		 __func__, __LINE__, var1, var2, g_szBufForDebug);\
    }\
}

#define AT_USB_DEBUG_PRINT_5(var1, var2, var3, var4, var5)  {\
    if (VOS_TRUE == g_ulAtUsbDebugFlag)\
    {\
        PS_MEM_SET(g_szBufForDebug, 0, (BUFFER_LENGTH_256 + 1));\
        strncpy(g_szBufForDebug, var4, (var5 > BUFFER_LENGTH_256) ? BUFFER_LENGTH_256 : (var5 > 0 ? (var5 - 1) : 0));\
        (VOS_VOID)vos_printf("===>%s, %d mode=%d, user = %d, port_no = %d, buffer = [%s]\n",\
        __func__, __LINE__, var1, var2, var3, g_szBufForDebug);\
    }\
}
 
#define AT_USB_WORK_MODE_PRINT(ucIndex,modetype,mode)       {\
    if (VOS_TRUE == g_ulAtUsbDebugFlag)\
    {\
        (VOS_VOID)vos_printf("===>%s, %d index = %d, modetype = %d mode = %d\n",__func__, __LINE__, ucIndex, modetype, mode);\
    }\
}

#define  AT_CLIENT_STATUS_PRINT_2(ucIndex,client_status) {\
    if (VOS_TRUE == g_ulAtUsbDebugFlag)\
    {\
        (VOS_VOID)vos_printf("===>%s, %d AT_FW_CLIENT_STATUS : %d Index=%d\n",__func__, __LINE__, client_status, ucIndex);\
    }\
}

#define AT_STOP_TIMER_CMD_READY(ucIndex)  {\
                            AT_StopRelTimer(ucIndex, &gastAtClientTab[ucIndex].hTimer);\
                            g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_READY;\
                            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CURRENT_OPT_BUTT;\
                            gastAtClientTab[ucIndex].opId = 0;\
                            if (VOS_TRUE == g_ulAtUsbDebugFlag)\
                            {\
                                (VOS_VOID)vos_printf("===>%s, %d AT_FW_CLIENT_STATUS : %d Index = %d\n", __func__, __LINE__, \
                                                                        g_stParseContext[ucIndex].ucClientStatus, ucIndex);\
                            }\
                        }
/*��ʼ*********************************************************************
��ά�ɲ��ӡ��װ:��Щ��ӡ�걻���ú���ʽ�汾�������LOG�����Ի�λ�����
ʱ��Bluetooth��DEBUG_TAG,���ɵ��ԡ�
 ------------------------------------------------------------------------*/
#define PRINT_STR(DEBUG_TAG,STR1,STR2,STR3)\
    do{\
        if(DEBUG_TAG)\
        {\
            (VOS_VOID)vos_printf("%s,%s,%s\n",STR1,STR2,STR3);\
        }\
    }while(0)

#define PRINT_POS(DEBUG_TAG,INT1,INT2,INT3)\
    do{\
        if(DEBUG_TAG)\
        {\
            (VOS_VOID)vos_printf("%s-%d:%x,%x,%x\n",__FUNCTION__,__LINE__,INT1,INT2,INT3);\
        }\
    }while(0)
#define PRINT_DATA(DEBUG_TAG,DATA)\
    do{\
        if(DEBUG_TAG)\
        {\
            (VOS_VOID)vos_printf("%x\n",DATA);\
        }\
    }while(0)
#define PRINT_DUMP(DEBUG_TAG,LEN,DATA)\
    do{\
        if(DEBUG_TAG)\
        {\
            (VOS_VOID)vos_printf_dump(LEN,DATA);\
        }\
    }while(0)
/*-------------------------------------------------------------------------
��ά�ɲ��ӡ��װ:��Щ��ӡ�걻���ú���ʽ�汾�������LOG�����Ի�λ�����
ʱ��Bluetooth��DEBUG_TAG,���ɵ��ԡ�
*********************************************************************����*/
extern VOS_UINT32 atLwclashCnfProcMbb(VOS_VOID *pMsgBlock);
extern AT_L4A_MSG_FUN_TABLE_STRU* atL4aGetCnfMsgFunMbb(VOS_UINT32 ulMsgId);
extern AT_L4A_MSG_FUN_TABLE_STRU* atL4aGetIndMsgFunMbb(VOS_UINT32 ulMsgId);
extern VOS_UINT32 Mbb_L4a_Msg_Proc(VOS_UINT32 ulMsgId);
#endif

#if (FEATURE_OFF == MBB_WPG_COMMON)
#define AT_USB_DEBUG_PRINT()  
#define AT_USB_DEBUG_PRINT_1(var1)  
#define AT_USB_DEBUG_PRINT_3(var1, var2, var3)
#define AT_USB_DEBUG_PRINT_4(var1, var2, var3, var4) 
#define AT_USB_DEBUG_PRINT_5(var1, var2, var3, var4, var5) 
#define AT_USB_WORK_MODE_PRINT(ucIndex,modetype,mode)
#define  AT_CLIENT_STATUS_PRINT_2(ucIndex,client_status) 
#endif

#ifdef __cplusplus
}
#endif


#endif /*__AT_H__
 */





