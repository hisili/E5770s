

#ifndef __TRRCERRLOGINTERFACE_H__
#define __TRRCERRLOGINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "omerrorlog.h"
#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
#include  "vos.h"
#include "omerrorlog.h"
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
/* TDS���������������ϱ���ǿ3������ */
#define TRRC_APP_MAX_NCELL_NUM                     (3)

/* RRC error����ʱ������RRC�����������¼���� */
#define TRRC_ERRLOG_CODE_MAX_NUM                   (4)

/* RRC error����ʱ��ģ�����������Ϣ������¼���� */
#define TRRC_APP_INFO_NUM                          (16)

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 ö����    : RRC_APP_ERROR_CODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC����������
*****************************************************************************/
enum TRRC_APP_ERROR_CODE_ENUM
{
    TRRC_APP_RB_PROTOCOL_CHECK_ERR            = 0,   /* RB����ʧ��--Protocol���ʧ�� */
    TRRC_APP_RB_TRANSACTION_CHECK_ERR,               /* RB����ʧ��--Transaction ID���ʧ�� */
    TRRC_APP_RB_INTEGRITY_CHECK_ERR,                 /* RB����ʧ��--Integrity���ʧ�� */

    TRRC_APP_RBREC_PROTOCOL_CHECK_ERR         = 10,  /* RB������ʧ��--Protocol���ʧ�� */
    TRRC_APP_RBREC_TRANSACTION_CHECK_ERR,            /* RB������ʧ��--Transaction ID���ʧ�� */
    TRRC_APP_RBREC_INTEGRITY_CHECK_ERR,              /* RB������ʧ��--Integrity���ʧ�� */

    TRRC_APP_CELLUPDATECNF_PROTOCOL_CHECK_ERR     =20,  /* С������ʧ��--Protocol���ʧ�� */
    TRRC_APP_CELLUPDATECNF_TRANSACTION_CHECK_ERR,       /* С������ʧ��--Transaction ID���ʧ�� */
    TRRC_APP_CELLUPDATECNF_INTEGRITY_CHECK_ERR,         /* С������ʧ��--Integrity���ʧ�� */

    TRRC_APP_EST_T300_ERR                         =30,  /* ��������N300ʱ��¼ */
    TRRC_APP_EST_CS_ACC_PROBABILITY_ERR,                /* CS����AC�ȼ��ж�ʧ�� */
    TRRC_APP_EST_PS_ACC_PROBABILITY_ERR,                /* PS����AC�ȼ��ж�ʧ�� */

    TRRC_APP_EST_AREA_LOST_ERR                    =40,  /* RRC���� */
    TRRC_APP_ASN_RLST_ERR,                              /* ASN�������� */
    TRRC_APP_AM_INTEGRITY_CHECK_ERR,                    /* AM���������Լ��ʧ�� */
    TRRC_APP_UM_INTEGRITY_CHECK_ERR,                    /* UM���������Լ��ʧ�� */

    TRRC_APP_MEAS_CTRL_PROTOCOL_CHECK_ERR         =50,  /* ��������ʧ��--Protocol���ʧ�� */
    TRRC_APP_MEAS_CTRL_TRANSACTION_CHECK_ERR,           /* ��������ʧ��--Transaction ID���ʧ�� */

    TRRC_APP_ERR_CODE_BUTT
};
typedef VOS_UINT8 TRRC_APP_ERROR_CODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TRRC_APP_FTM_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ģʽ�ϱ����ͣ����������ϱ������º��ϱ���
*****************************************************************************/
enum TRRC_APP_FTM_TYPE_ENUM
 {
    TRRC_APP_FTM_PERIOD_INFO,     /* �������ϱ��Ĺ���ģʽ��Ϣ��ĿǰIdle״̬�ϱ�����ΪDRX���ڣ�Connected״̬������Ϊ1�� */
    TRRC_APP_FTM_CHANGE_INFO,     /* ���º��ϱ��͵Ĺ���ģʽ��Ϣ������ϱ����������� */
    TRRC_APP_FTM_INFO_BUIT
 };
 typedef VOS_UINT32 TRRC_APP_FTM_TYPE_ENUM_UINT32;

 /*********************************************************
 ö����    : TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ϱ�����ģʽ���Ͷ���
**********************************************************/
 enum TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM
 {
     TRRC_APP_FTM_CHANGE_CELL_INFO,      /* RRCפ��С����Ϣ���仯���ϱ����л�����ѡ��ɺ��ϱ� */
     TRRC_APP_FTM_CHANGE_STATE_INFO,     /* RRC״̬��Ϣ���仯���ϱ� */

     TRRC_APP_FTM_CHANGE_BUTT
 };
  typedef VOS_UINT32 TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM_UINT32;

 /*****************************************************************************
  ö����    : TRRC_APP_PROTOCOL_STATE_ENUM
  Э����  :
  ASN.1���� :
  ö��˵��  : TRRCЭ��״̬
 *****************************************************************************/
 enum TRRC_APP_PROTOCOL_STATE_ENUM
 {
     TRRC_APP_PROTOCOL_STATE_IDLE                           = 0,                /* IDLE̬ */
     TRRC_APP_PROTOCOL_STATE_CELL_PCH                          ,                /* CELL_PCH̬ */
     TRRC_APP_PROTOCOL_STATE_URA_PCH                           ,                /* URA_PCH̬ */
     TRRC_APP_PROTOCOL_STATE_CELL_FACH                         ,                /* CELL_FACH̬ */
     TRRC_APP_PROTOCOL_STATE_CELL_DCH                          ,                /* CELL_DCH̬ */

     TRRC_APP_PROTOCOL_STATE_BUTT
 };
 typedef VOS_UINT8 TRRC_APP_PROTOCOL_STATE_ENUM_UINT8;

 /*****************************************************************************
  ö����     :TRRC_APP_GRR_BANDINDICATOR_ENUM
  Э����  :
  ASN.1����   :
  ö��˵�� : 2GС��Ƶ��ָʾ
 *****************************************************************************/
 enum TRRC_APP_GRR_BANDINDICATOR_ENUM
 {
     TRRC_APP_GRR_BANDINDICATOR_DCS1800       = 0,
     TRRC_APP_GRR_BANDINDICATOR_PCS1900       ,

     TRRC_APP_GRR_BANDINDICATOR_BUTT
 };
 typedef VOS_UINT16    TRRC_APP_GRR_BANDINDICATOR_ENUM_UINT16;

  /*****************************************************************************
  ö����     :TRRC_APP_RRC_STATE_ENUM
  Э����  :
  ASN.1����   :
  ö��˵�� : RRC״̬���ڲ�״̬����Э��״̬
 *****************************************************************************/
 enum TRRC_APP_RRC_STATE_ENUM
 {
    TRRC_APP_NUL,   // 0x00  /* TTRRC_APP_CHANGE FOR ע��: ����ǰ���Ͷ�ʧ����*/
    TRRC_APP_SEL,   // 0x01
    TRRC_APP_IDL,   // 0x02
    TRRC_APP_RES,   // 0x03
    TRRC_APP_ACC,   // 0x04
    TRRC_APP_FCH,   // 0x05
    TRRC_APP_DCH,   // 0x06
    TRRC_APP_PCH,   // 0x07
    TRRC_APP_WCA,   // 0x08
    TRRC_APP_REL,   // 0x09
    TRRC_APP_CNF,   // 0x0A
    TRRC_APP_LIM,   // 0x0b
    TRRC_APP_SNW,   // 0x0c
    TRRC_APP_INACTIVE,//0x0d PDM100 200909 for dual mode
    TRRC_APP_PREDEF,  //PDM100 200909 for SIB16
    TRRC_APP_PEND,    //PDM100 200909 for inter-RAT res and CCO
    TRRC_APP_RATHO,   //PDM100 200909 for inter-RAT HO
    TRRC_APP_WAIT,
    TRRC_APP_POWEROFF
 };
typedef VOS_UINT8 TRRC_APP_RRC_STATE_ENUM_UINT8;
/*****************************************************************************
 ö����    : TRRC_FLOW_CTRL_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���̿�������ö��
             �޸�ö��ʱ��Ҫע�⣬ʧ������ȡֵ = ��������ȡֵ+1
 ����: LRRC_FLOW_CTRL_TYPE_G2L_RESEL_FAIL = LRRC_FLOW_CTRL_TYPE_G2L_START_RESEL + 1
*****************************************************************************/
enum TRRC_APP_FLOW_CTRL_TYPE_ENUM
{
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL            = 0,     /* TDS�����̱߽� */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_IDL_SYS_UPDATA,     /* TDS������IDL̬ϵͳ��Ϣ���²����������� */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_PCH_SYS_UPDATA,     /* TDS������PCH̬ϵͳ��Ϣ���²����������� */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_ENTER_PCH,          /* TDS�����̴�����״̬��DCH/FACH->PCH̬ת������ */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_ENTER_FCH,          /* TDS�����̴�����״̬��IDL->FCH̬ת������ */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_ENTER_DCH,          /* TDS�����̴�����״̬��IDL->DCH̬ת������ */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_RES_ENTER_FCH,             /* TDS��������ѡ�����FCH״̬���� */
    /* TL RESEL PHASE2 begin */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NAS_SUSPEND,               /* TDS������NAS�������� */
    /* TL RESEL PHASE2 end */
    TRRC_APP_FLOW_CTRL_TYPE_T2T_NORMAL_END,                /* TDS�����̱߽� */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_START_RESEL,               /* G->T��ʼ��ѡ */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_RESEL_FAIL,                /* G->T��ѡʧ�� */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_RESEL,                /* G->Tֹͣ��ѡ */

    TRRC_APP_FLOW_CTRL_TYPE_T2G_START_RESEL,               /* T->G��ʼ��ѡ */
    TRRC_APP_FLOW_CTRL_TYPE_T2G_RESEL_FAIL,                /* T->G��ѡʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_MEAS,                      /* G->T �������� */
    /* TL RESEL BEGIN */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_START_RESEL,               /* L->T��ʼ��ѡ */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_RESEL_FAIL,                /* L->T��ѡʧ�� */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_STOP_RESEL,                /* L->Tֹͣ��ѡ */

    TRRC_APP_FLOW_CTRL_TYPE_L2T_IDLE_MEAS,                 /* L->T IDLE�������� */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_CONN_MEAS,                 /* L->T CONN�������� */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_RELALL,                    /* L->T RELALL */

    TRRC_APP_FLOW_CTRL_TYPE_T2L_START_RESEL,               /* T->L��ʼ��ѡ */
    TRRC_APP_FLOW_CTRL_TYPE_T2L_RESEL_FAIL,                /* T->L��ѡʧ�� */

	/* TOER_HO BEGIN */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_START_CCO,                 /* G->T��ʼCCO */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_CCO_FAIL,                  /* G->T CCOʧ�� */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_CCO,                  /* G->TֹͣCCO */

    TRRC_APP_FLOW_CTRL_TYPE_T2G_START_CCO,                 /* T->G��ʼCCO */
    TRRC_APP_FLOW_CTRL_TYPE_T2G_CCO_FAIL,                  /* T->G CCOʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_T2L_START_HO,                  /* T->L��ʼ�л� */
    TRRC_APP_FLOW_CTRL_TYPE_T2L_HO_FAIL,                   /* T->L�л�ʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_L2T_START_HO,                  /* L->T��ʼHO */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_HO_FAIL,                   /* L->T HOʧ�� */
    TRRC_APP_FLOW_CTRL_TYPE_L2T_STOP_HO,                   /* L->TֹͣHO */

    TRRC_APP_FLOW_CTRL_TYPE_T2G_START_HO,                  /* T->G��ʼ�л� */
    TRRC_APP_FLOW_CTRL_TYPE_T2G_HO_FAIL,                   /* T->G�л�ʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_START_HO,                  /* G->T��ʼHO */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_HO_FAIL,                   /* G->T HOʧ�� */
    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_HO,                   /* G->TֹͣHO */
    /* TOER_HO END */

    TRRC_APP_FLOW_CTRL_TYPE_T2T_SYSCFG_SUSPEND,            /* TDS���������ҹ������� */
    /* TL RESEL PHASE2 begin */
    #if 0
    TRRC_APP_FLOW_CTRL_TYPE_T2L_MEAS,                      /* T->L �������� */
    #endif
    /* TL RESEL PHASE2 end */
    /* TL RESEL end */
    /* TL Redir begin */
    TRRC_APP_FLOW_CTRL_TYPE_T2L_REDIR,                     /* T->L�ض��� */
    /* TL Redir end */
    LRRC_APP_FLOW_CTRL_TYPE_L2T_REDIR_FAIL,                /* L->W�ض���ʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_L2T_STOP_REDIR,                /* L->T�ض���ֹͣ */

    /*׼FR����begin*/
    TRRC_APP_FLOW_CTRL_TYPE_T2G_REDIR,                     /* T->G�ض��� */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_REDIR_FAIL,                /* G->T�ض���ʧ�� */

    TRRC_APP_FLOW_CTRL_TYPE_G2T_STOP_REDIR,                /* G->T�ض���ֹͣ */
    /*׼FR����end*/

    TRRC_APP_FLOW_CTRL_TYPE_BUTT
};
typedef VOS_UINT16 TRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT16;
/*****************************************************************************
 ö����    : TRRC_APP_EST_SIGNALLING_TYPE
 Э����  :
 ASN.1���� :
 ö��˵��  : ��·����
*****************************************************************************/

enum  TRRC_APP_EST_SIGNALLING_TYPE
{
  TRRC_APP_NO_SIGNALLING_CONNECTION = 0,
  TRRC_APP_SIGNALLING_CONNECTION_ESTABLISHING,
  TRRC_APP_SIGNALLING_CONNECTION_ESTABLISHED
};

typedef VOS_UINT32 TRRC_APP_EST_SIGNALLING_TYPE_UINT32;
/*****************************************************************************
 ö����    : TRRC_APP_EST_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRMM_EST_REQ_STRU��Ϣ�е�enEstCause����25.331Э�鶨�屣��һ��
*****************************************************************************/
enum TRRC_APP_EST_CAUSE_ENUM
{
    TRRC_APP_EST_CAUSE_ORIGIN_CONVERSAT_CALL             = 0,
    TRRC_APP_EST_CAUSE_ORIGIN_STREAM_CALL                = 1,
    TRRC_APP_EST_CAUSE_ORIGIN_INTERACT_CALL              = 2,
    TRRC_APP_EST_CAUSE_ORIGIN_BACKGROUND_CALL            = 3,
    TRRC_APP_EST_CAUSE_ORIGIN_SUBSCRIB_TRAFFIC_CALL      = 4,
    TRRC_APP_EST_CAUSE_TERMINAT_CONVERSAT_CALL           = 5,
    TRRC_APP_EST_CAUSE_TERMINAT_STREAM_CALL              = 6,
    TRRC_APP_EST_CAUSE_TERMINAT_INTERACT_CALL            = 7,
    TRRC_APP_EST_CAUSE_TERMINAT_BACKGROUND_CALL          = 8,
    TRRC_APP_EST_CAUSE_EMERGENCY_CALL                    = 9,
    TRRC_APP_EST_CAUSE_INTER_RAT_CELL_RESELECT           = 10,
    TRRC_APP_EST_CAUSE_INTER_RAT_CELL_CHANGE_ORDER       = 11,
    TRRC_APP_EST_CAUSE_REGISTRATION                      = 12,
    TRRC_APP_EST_CAUSE_DETACH                            = 13,
    TRRC_APP_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL       = 14,
    TRRC_APP_EST_CAUSE_ORIGIN_LOW_PRIORITY_SIGNAL        = 15,
    TRRC_APP_EST_CAUSE_CALL_RE_ESTABLISH                 = 16,
    TRRC_APP_EST_CAUSE_TERMINAT_HIGH_PRIORITY_SIGNAL     = 17,
    TRRC_APP_EST_CAUSE_TERMINAT_LOW_PRIORITY_SIGNAL      = 18,
    TRRC_APP_EST_CAUSE_TERMINAT_CAUSE_UNKNOWN            = 19,
    TRRC_APP_EST_CAUSE_BUTT
};
typedef VOS_UINT32 TRRC_APP_EST_CAUSE_ENUM_UINT32;
/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
                               ����ģʽ �ϱ����ݽṹ
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TRRC_APP_CHANGE_CELL_INFO_STRU
 �ṹ˵��  : �仯�ϱ��Ĺ���ģʽ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                usUlFreq;          /* ��������Ƶ�㵥λ:100Khz */
    VOS_UINT16                                usDlFreq;          /* ��������Ƶ�㵥λ:100Khz */
    VOS_UINT32                                ulCellId;          /* TD-SCDMAС��ID��ָRRC���С��ID������������ */
    VOS_UINT16                                usPagingCycle;     /* Ѱ������128,256,512,1024����λms*/
    VOS_UINT16                                usReserved;
}TRRC_APP_CHANGE_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_TDS_NCELL_INFO_STRU
 �ṹ˵��  : TD-SCDMAͬƵ����ƵС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usFrequency;      /* TD-SCDMA��С����������Ƶ�� ��λ:100Khz */
    VOS_UINT16                         usCellId;         /* TD-SCDMA��С��С��ID */
    VOS_UINT8                          ucRscp;           /* TD-SCDMA��С��Rscp���չ��ʣ���ʵֵ=ucRscp - 116����λdbm */
    VOS_UINT8                          aucReserved[3];
}TRRC_APP_TDS_NCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_TDS_NCELL_STRU
 �ṹ˵��  : TD-SCDMAͬƵ����ƵС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulNCellNumber;
    TRRC_APP_TDS_NCELL_INFO_STRU    stCellMeasInfo[TRRC_APP_MAX_NCELL_NUM];
}TRRC_APP_TDS_NCELL_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_LTE_NCELL_INFO_STRU
 �ṹ˵��  : TD-SCDMA��ϵͳLTEС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          usCellId;   /* ����С��ID */
    VOS_INT16                           sRsrp;      /* �������RSRP */
    VOS_INT16                           sRsrq;      /* �������RSRQ */
}TRRC_APP_LTE_NCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_LTE_NCELL_STRU
 �ṹ˵��  : TD-SCDMA��ϵͳLTEС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulNCellNumber;
    TRRC_APP_LTE_NCELL_INFO_STRU    stCellMeasInfo[TRRC_APP_MAX_NCELL_NUM];
}TRRC_APP_LTE_NCELL_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_GERAN_NCELL_INFO_STRU
 �ṹ˵��  : TD-SCDMA��ϵͳGSMС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usArfcn;
    TRRC_APP_GRR_BANDINDICATOR_ENUM_UINT16                  enBandInd;          /* ����T->Gʱ����������Ϣ�е�Ƶ��ָʾһ�� */
    VOS_INT16                                               sRssi;              /* sRssi ȡֵ��Χ[-110 * 8,-48 * 8],��λ:dbm,����1/8 */
    VOS_UINT8                                               ucNcc;              /*  �ƶ�ͨѶGSM����ʶ�����: ����ɫ��(NCC) */
    VOS_UINT8                                               ucBcc;              /*  �ƶ�ͨѶGSM����ʶ�����: ��վɫ��(BCC) */
}TRRC_APP_GERAN_NCELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_GERAN_NCELL_STRU
 �ṹ˵��  : TD-SCDMA��ϵͳGSMС����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                        ulNCellNumber;
    TRRC_APP_GERAN_NCELL_INFO_STRU    stCellMeasInfo[TRRC_APP_MAX_NCELL_NUM];
}TRRC_APP_GERAN_NCELL_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_NCELL_INFO_STRU
 �ṹ˵��  : ����С����ͬƵ����Ƶ�Լ���ϵͳ�������
*****************************************************************************/
typedef struct
{
    TRRC_APP_TDS_NCELL_STRU               stIntraFreqInfo;/* ͬƵ������Ϣ*/
    TRRC_APP_TDS_NCELL_STRU               stInterFreqInfo;/* ��Ƶ������Ϣ*/
    TRRC_APP_LTE_NCELL_STRU               stLTENcellInfo; /* LTE��ϵͳ����*/
    TRRC_APP_GERAN_NCELL_STRU             stGeranNcellInfo; /* GERAN��ϵͳ���� */
}TRRC_APP_NCELL_INFO_STRU;

/****************************************************************************
 �ṹ��    : TRRC_APP_FTM_CHANGE_INFO_STRU
 �ṹ˵��  : �仯�ϱ��Ĺ���ģʽ�ṹ
*****************************************************************************/
typedef struct
{
    TRRC_APP_FTM_CHANGE_INFO_TYPE_ENUM_UINT32     ulFtmChangeInfoType;

    union
    {
        TRRC_APP_CHANGE_CELL_INFO_STRU            stCellInfo;
        TRRC_APP_PROTOCOL_STATE_ENUM_UINT8        enTrrcProtocolState;
    }uchangeInfo;
}TRRC_APP_FTM_CHANGE_INFO_STRU;
/*****************************************************************************
 �ṹ��    : APP_RRC_SINR_INFO_STRU
 �ṹ˵��  : SINR�ṹ
*****************************************************************************/
typedef struct
{
	VOS_UINT16                                     usModuFormat;
	VOS_UINT16                                     usTbiOut;
}TRRC_APP_CQI_INFO_STRU;
/*****************************************************************************
 �ṹ��    : APP_RRC_SINR_INFO_STRU
 �ṹ˵��  : SINR�ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                              sSinrDB;
    VOS_UINT16                             usRev;
}TRRC_APP_DPCH_SINR_INFO_STRU;
/*****************************************************************************
 �ṹ��    : TDS_ERRLOG_UL_POWER_STRU
 �ṹ˵��  : UE���з��书��
*****************************************************************************/
typedef struct
{
	VOS_INT16 sDpchPwr;
	VOS_INT16 sEpuchPwr;
}TDS_APP_ERRLOG_UL_POWER_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_PERIOD_INFO
 �ṹ˵��  : �����ϱ��Ĺ���ģʽ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sCellRSCP;
    VOS_UINT16                          usReserved;
    TDS_APP_ERRLOG_UL_POWER_STRU        stUeTxPower;
    TRRC_APP_DPCH_SINR_INFO_STRU        stSINR;             /* SINR  RS_SNR */
    TRRC_APP_CQI_INFO_STRU              stCQI;              /* CQI�������� */
    TRRC_APP_NCELL_INFO_STRU            stNcellInfo;        /*������Ϣ*/
}TRRC_APP_FTM_PERIOD_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_INFO_STRU
 �ṹ˵��  : ����ģʽ�ϱ����ݽṹ
*****************************************************************************/
typedef struct
{
    TRRC_APP_FTM_TYPE_ENUM_UINT32             enRrcAppFtmType;

    union
    {
        TRRC_APP_FTM_PERIOD_INFO_STRU         stPeriodInfo;  /* ����ģʽ�£������ϱ����ݣ� Idle״̬�ϱ�����ĿǰΪDRX���ڣ�Connected״̬������Ϊ1�� */
        TRRC_APP_FTM_CHANGE_INFO_STRU         stChangInfo;   /* ����ģʽ�£�������ϱ����� */
    }u;
}TRRC_APP_FTM_INFO_STRU;
/*****************************************************************************
 �ṹ��    : TRRC_OM_FTM_REPROT_CONTENT_STRU
 �ṹ˵��  : ����ģʽ�ϱ����ݽṹ
*****************************************************************************/
typedef struct
{
    /* ��ģ��ID */
    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32    ulMsgModuleID;

    /* 00������, 01������ ,10/11:����  */
    VOS_UINT16                          usModemId;

    VOS_UINT16                          usProjectID;
    VOS_UINT32                          ulLength;

    TRRC_APP_FTM_INFO_STRU               stTrrcFtmInfo;

}TRRC_OM_FTM_REPROT_CONTENT_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_OM_FTM_REPROT_IND_STRU
 �ṹ˵��  : ����ģʽ�ϱ����ݽṹ
*****************************************************************************/
/* ���������ģʽ�����ϱ����� ����� -> OM*/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* ����ģʽ�ϱ������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    TRRC_OM_FTM_REPROT_CONTENT_STRU     stTrrcFtmContent;
}TRRC_OM_FTM_REPROT_IND_STRU;

/*****************************************************************************
                               ERROR LOG �ϱ����ݽṹ
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_PERIOD_INFO
 �ṹ˵��  : ERROR LOG ���ݽṹ
 ulNextIndex������һ������������������ulNextIndex = 1����aenRrcAppErrorCode[0]
 �����µĴ�����
 ���ulNextIndex = 0��aenRrcAppErrorCode[0] = TRRC_APP_ERR_CODE_BUTT����û�б��������
*****************************************************************************/
typedef struct
{
    VOS_INT32                        ulNextIndex;
    TRRC_APP_ERROR_CODE_ENUM_UINT8   aenRrcAppErrorCode[TRRC_ERRLOG_CODE_MAX_NUM];
}TRRC_APP_ERROR_CODE_INFO_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_RECIVE_MSG_STRU
 �ṹ˵��  : RRC �����Ϣ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   ulSendPid;    /* ��������Pid */
    VOS_UINT32                   ulMsgName;    /* ������ϢID */
}TRRC_APP_RECIVE_MSG_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_RECIVE_MSG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :ERROR��ӡ��Ϣ����ṹ
  ulNextIndex������һ���յ���Ϣ����������ulNextIndex = 1����astReciveMsgInfo[0]
 �����µ��յ�����ϢID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNextIndex;
    TRRC_APP_RECIVE_MSG_STRU            astReciveMsgInfo[TRRC_APP_INFO_NUM];
} TRRC_APP_RECIVE_MSG_INFO_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_STATE_INFO_STRU
 �ṹ˵��  : ERROR LOG RRC״̬��Ϣ������Э��״̬���ڲ�״̬����ϵͳ����
*****************************************************************************/
typedef struct
{
    TRRC_APP_PROTOCOL_STATE_ENUM_UINT8          enTrrcProtocolState;   /* RRCЭ��״̬ */
    TRRC_APP_RRC_STATE_ENUM_UINT8               enRrcState;            /* RRC״̬���ڲ�״̬����Э��״̬ */
    TRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT16         enErrcFlowCtrlType;    /* TD-SCDMA������ϵͳ����ʱ����ϵͳ���̱�ʶ */
}TRRC_APP_STATE_INFO_STRU;
/*****************************************************************************
 �ṹ��    : TRRC_APP_EST_INFO_STRU
 �ṹ˵��  : ERROR LOG RRC״̬��Ϣ
 enEstSignallingType[0]:CS;enEstSignallingType[1]:ps
*****************************************************************************/
typedef struct
{
    TRRC_APP_EST_SIGNALLING_TYPE_UINT32        enEstSignallingType[2];
    TRRC_APP_EST_CAUSE_ENUM_UINT32             enEstCause;
}TRRC_APP_EST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_PERIOD_INFO
 �ṹ˵��  : ERROR LOG ���ݽṹ
*****************************************************************************/
typedef struct
{
    TRRC_APP_RECIVE_MSG_INFO_STRU     stRrAppReciveMsgInfo;
    TRRC_APP_STATE_INFO_STRU          stRrcAppStateInfo;
    TRRC_APP_EST_INFO_STRU            stRrcAppEstInfo;

}TRRC_APP_ERR_LOG_RRC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TRRC_APP_ERR_LOG_INFO_STRU
 �ṹ˵��  : ERROR LOG ���ݽṹ
*****************************************************************************/
typedef struct
{
    TRRC_APP_ERROR_CODE_INFO_STRU    stErrorCodeInfo;
    TRRC_APP_ERR_LOG_RRC_INFO_STRU   stErrorLogInfo;
}TRRC_APP_ERR_LOG_INFO_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_PERIOD_INFO
 �ṹ˵��  : ERROR LOG ���ݽṹ
*****************************************************************************/
typedef struct
{
    /* ��ģ��ID */
    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32    ulMsgModuleID;

    /* 00������, 01������ ,10/11:����  */
    VOS_UINT16                          usModemId;

    /*  sub sys,modeule,sub module   �ݲ�ʹ��   */
    VOS_UINT16                          usALMID;

    /* ERR LOG�ϱ�����,
    Warning��0x04������ʾ��
    Minor��0x03�����Ҫ
    Major��0x02�����Ҫ
    Critical��0x01�������    */
    VOS_UINT16                          usALMLevel;

    /* ÿ��ERR LOG����������:
    ����&�澯����
    ͨ�ţ�0x00
    ҵ��������0x01
    �������0x02
    �豸���ϣ�0x03
    �������ϣ�0x04    */
    VOS_UINT16                          usALMType;

    VOS_UINT32                          usAlmLowSlice;/*ʱ���*/
    VOS_UINT32                          usAlmHighSlice;

    VOS_UINT32                          ulAlmLength;
    TRRC_APP_ERR_LOG_INFO_STRU          stAlmInfo;
}TRRC_OM_ERR_LOG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : OM_ERR_LOG_REPORT_CNF_STRU
 �ṹ˵��  : ERROR LOG ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* �������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    TRRC_OM_ERR_LOG_INFO_STRU           stAppFtmInfo;
} TRRC_OM_ERR_LOG_REPORT_CNF_STRU;

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






#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TrrcErrLogInterface.h */


