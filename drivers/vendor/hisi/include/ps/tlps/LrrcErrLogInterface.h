/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LrrcErrLogInterface.h
  Description     : LrrcErrLogInterface.h header file
  History         :
     1.HANLUFENG 41410       2013-8-27     Draft Enact
     2.
******************************************************************************/

#ifndef __LRRCERRLOGINTERFACE_H__
#define __LRRCERRLOGINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"


#include "omerrorlog.h"
#include "AppRrcInterface.h"


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif


/*****************************************************************************
  2 macro
*****************************************************************************/

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
/* LTE֧��CA����£�֧�ֵ������Ƶ����V9R1Ϊ1��V7R2��K3V3Ϊ2��Э��涨���ֵΪ5 */
#define LRRC_APP_MAX_NUM 5

/* RRC error����ʱ��RRC�Ľ�����Ϣ��¼����������������ԭ��ͽ�� */
#define RRC_APP_MAX_RRC_EST_INFO_NUM              (5)

/* Э��ֵ:3 */
#define RRC_APP_MAX_NUM_OF_MCC                    (3)

/* RRC error����ʱ����ӡ�����Ϣ������¼���� */
#define RRC_APP_ERROR_PRINT_INFO_NUM              (4)

/* RRC error����ʱ��ģ�����������Ϣ������¼���� */
#define RRC_APP_RECEIVE_MSG_INFO_NUM              (16)

/* RRC error����ʱ������RRC�����������¼���� */
#define RRC_APP_CODE_NUM                          (4)

/* LTE֧��MIMOʱ�����ͬʱ֧�ֵ������� */
#define NUM_OF_CODEWORD                           (2)

/*****************************************************************************
  4 Enum
*****************************************************************************/
 enum RRC_APP_FTM_TYPE_ENUM
 {
    RRC_APP_FTM_PERIOD_INFO,     /* �������ϱ��Ĺ���ģʽ��Ϣ��ĿǰIdle״̬�ϱ�����ΪDRX���ڣ�Connected״̬������Ϊ1�� */
    RRC_APP_FTM_CHANGE_INFO,     /* ���º��ϱ��͵Ĺ���ģʽ��Ϣ */
    RRC_APP_FTM_INFO_BUTT
 };
 typedef VOS_UINT32 RRC_APP_FTM_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : RRC_APP_PAGING_CYCLE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : Ѱ�����ڣ�RFXX��XX��ʾ����֡��������λΪ10ms,RF32������320ms��������ʾΪXXXms
*****************************************************************************/
enum RRC_APP_PAGING_CYCLE_ENUM
{
    RRC_APP_RF32                                     = 0,
    RRC_APP_RF64                                     = 1,
    RRC_APP_RF128                                    = 2,
    RRC_APP_RF256                                    = 3
};
typedef VOS_UINT32 RRC_APP_PAGING_CYCLE_ENUM_UINT32;
/*****************************************************************************
 ö����    : RRC_APP_TRANSM_MODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ģʽ���ͣ�����ֱ����ʾTMX_TRANSM_MODE����
*****************************************************************************/
enum RRC_APP_TRANSM_MODE_ENUM
{
    RRC_APP_TM1_TRANSM_MODE                          = 0,
    RRC_APP_TM2_TRANSM_MODE                          = 1,
    RRC_APP_TM3_TRANSM_MODE                          = 2,
    RRC_APP_TM4_TRANSM_MODE                          = 3,
    RRC_APP_TM5_TRANSM_MODE                          = 4,
    RRC_APP_TM6_TRANSM_MODE                          = 5,
    RRC_APP_TM7_TRANSM_MODE                          = 6,
    RRC_APP_TM8_TRANSM_MODE                          = 7,
    RRC_APP_TM9_TRANSM_MODE                          = 8,
    RRC_APP_TRANSM_MODE_BUTT
};
typedef VOS_UINT32 RRC_APP_TRANSM_MODE_ENUM_UINT32;
/*****************************************************************************
 ö����    : RRC_APP_PROTOCOL_STATE_IND
 Э����  :
 ASN.1���� :
 ö��˵��  : RRCЭ��״̬����
*****************************************************************************/
enum RRC_APP_PROTOCOL_STATE_IND_ENUM
{
    RRC_APP_PROTOCOL_IDLE                   = 0 ,
    RRC_APP_PROTOCOL_CONNECTED,
    RRC_APP_PROTOCOL_STATE_BUTT
};
typedef VOS_UINT8 RRC_APP_PROTOCOL_STATE_IND_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_APP_ERROR_CODE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC����������
*****************************************************************************/
enum RRC_APP_ERROR_CODE_ENUM
{
    RRC_APP_RB_MEAS_CHECK_ERR               = 0, /* ������ʧ��--measConfig���ʧ�� */
    RRC_APP_RB_MOCTRL_CHECK_ERR             = 1, /* ������ʧ��--MobilCtrlInfo �л���Ϣ���ʧ�� */
    RRC_APP_RB_RADIOSRC_CHECK_ERR           = 2, /* ������ʧ��--RadioRsrcConfigDedic ��Ϣ���ʧ�� */
    RRC_APP_RB_TTIBUNDING_CHECK_ERR         = 3, /* ������ʧ��--TTIBundling ���ʧ�� */
    RRC_APP_RB_SECU_CHECK_ERR               = 4, /* ������ʧ��--SecurCfgHo �л��а�ȫ���ʧ�� */
    RRC_APP_RB_CFGDSP_ERR                   = 5, /* ������ʧ��--����DSP��DSP����ʧ�� */
    RRC_APP_RB_CFGL2_ERR                    = 6, /* ������ʧ��--����L2,L2����ʧ�� */
    RRC_APP_RB_CFGDSP_TIMEROUT_ERR          = 7, /* ������ʧ��--����DSP��������ʱ����ʱ */
    RRC_APP_RB_CFGL2_TIMEROUT_ERR           = 8, /* ������ʧ��--����L2��������ʱ����ʱ */

    RRC_APP_EST_MT_T302_ERR                     = 18, /* RRC���ӽ���ʧ��--MT Call��T302��ʱ�������� */

    RRC_APP_EST_MO_T302_ERR                     = 22, /* RRC���ӽ���ʧ��--Mo Data��T302��ʱ�������� */
    RRC_APP_EST_MO_T303_ERR                     = 23, /* RRC���ӽ���ʧ��--Mo Data��T303��ʱ�������� */
    RRC_APP_EST_MO_ACC_PROBABILITY_ERR          = 24, /* RRC���ӽ���ʧ��--Mo Data��ACC����ȼ����� */
    RRC_APP_EST_MO_RHPLMN_PROBABILITY_ERR       = 25, /* RRC���ӽ���ʧ��--Mo Data��Rplmn��Hplmn���� */
    RRC_APP_EST_MO_ACC_RHPLMN_PROBABILITY_ERR   = 26, /* RRC���ӽ���ʧ��--Mo Data��AcBarringForMoData�����жϱ�Bar */

    RRC_APP_EST_MS_T302_ERR                     = 28, /* RRC���ӽ���ʧ��--Mo Signalling��T302��ʱ�������� */
    RRC_APP_EST_MS_T305_ERR                     = 29, /* RRC���ӽ���ʧ��--Mo Signalling��T305��ʱ�������� */
    RRC_APP_EST_MS_ACC_PROBABILITY_ERR          = 30, /* RRC���ӽ���ʧ��--Mo Signalling��ACC����ȼ����� */
    RRC_APP_EST_MS_RHPLMN_PROBABILITY_ERR       = 31, /* RRC���ӽ���ʧ��--Mo Signalling��Rplmn��Hplmn���� */
    RRC_APP_EST_MS_ACC_RHPLMN_PROBABILITY_ERR   = 32, /* Mo Signalling��AcBarringForMoData�����жϱ�Bar */

    RRC_APP_EST_AREA_LOST_ERR                   = 34, /* ��ǰ�Ѿ���������ֱ�Ӹ�NAS��ʧ�� */

    RRC_APP_REEST_T311_TIMEROUT_ERR             = 49, /* �ؽ���ʧ��--�ؽ�������С������T311��ʱ����ʱ */
    RRC_APP_REEST_T301_TIMEROUT_ERR             = 50, /* �ؽ���ʧ��--���ͽ���Req��Ϣ�󣬵ȴ��ؽ���Ӧ��Ϣ��T301��ʱ */
    RRC_APP_REEST_SRB0CFGDSP_ERR                = 51, /* �ؽ���ʧ��--����DSP��DSP����ʧ�� */
    RRC_APP_REEST_SRB0CFGL2_ERR                 = 52, /* �ؽ���ʧ��--����L2��L2����ʧ�� */
    RRC_APP_REEST_MACCFG_CHECK_ERR              = 53, /* �ؽ���ʧ��--��Ϣ���MasCfgʧ�� */
    RRC_APP_REEST_PHYDEDIC_CHECK_ERR            = 54, /* �ؽ���ʧ��--��Ϣ���PhyCfgDedicʧ�� */
    RRC_APP_REEST_TTIBUND_CHECK_ERR             = 55, /* �ؽ���ʧ��--ttiBundling���ʧ�� */
    RRC_APP_REEST_SRB_CHECK_ERR                 = 56, /* �ؽ���ʧ��--SRB���ʧ�ܳ�ʱ */
    RRC_APP_REEST_SPS_CHECK_ERR                 = 57, /* �ؽ���ʧ��--SPS���ʧ�� */
    RRC_APP_REEST_SRB1CFGDSP_ERR                = 58, /* �ؽ���ʧ��--����DSP��DSP����ʧ�� */
    RRC_APP_REEST_SRB1CFGL2_ERR                 = 59, /* �ؽ���ʧ��--����L2��L2����ʧ�� */
    RRC_APP_REEST_SECU_ERR                      = 60, /* �ؽ���ʧ��--��ȫ������ʧ�� */

    RRC_APP_ERR_CODE_BUTT
};
typedef VOS_UINT16 RRC_APP_ERROR_CODE_ENUM_UINT16;

/*****************************************************************************
 ö����    : LRRC_LNAS_EST_CAUSE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRMM_EST_REQ_STRU��Ϣ�е�enEstCause
              emergency, highPriorityAccess, mt-Access, mo-Signalling, mo-Data,delayTolerantAccess-v1020 ,
*****************************************************************************/
enum LRRC_APP_LNAS_EST_CAUSE_ENUM
{
    LRRC_APP_LNAS_EST_CAUSE_EMERGENCY_CALL          = 0,
    LRRC_APP_LNAS_EST_CAUSE_HIGH_PRIORITY_ACCESS,
    LRRC_APP_LNAS_EST_CAUSE_MT_ACCESS,
    LRRC_APP_LNAS_EST_CAUSE_MO_SIGNALLING,
    LRRC_APP_LNAS_EST_CAUSE_MO_DATA,
    LRRC_APP_LNAS_EST_CAUSE_BUTT
};
typedef VOS_UINT8 LRRC_APP_LNAS_EST_CAUSE_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_LNAS_EST_RESULT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �������ӽ��ö������
*****************************************************************************/
enum LRRC_APP_LNAS_EST_RESULT_ENUM
{
    LRRC_APP_EST_SUCCESS                         = 0,       /* �������ӽ����ɹ� */
    LRRC_APP_EST_PRESENT                         = 1,       /* �����������Ѿ����� */
    LRRC_APP_EST_ESTING                          = 2,       /* �������������ڽ��� */
    LRRC_APP_EST_DELING                          = 3,       /* ���������������ͷ� */
    LRRC_APP_EST_ACCESS_BARRED_MO_CALL           = 4,       /* access barred when MO Call */
    LRRC_APP_EST_ACCESS_BARRED_MO_SIGNAL         = 5,       /* access barred When MO SIGNAL */
    LRRC_APP_EST_ACCESS_BARRED_EMERGENCY_CALL    = 6,       /* access barred When Emergency Call */
    LRRC_APP_EST_ACCESS_BARRED_ALL               = 7,       /* access barred When Rrc Con Rej */
    LRRC_APP_EST_EST_CONN_FAIL                   = 8,       /* RR connection establish failure  */
    LRRC_APP_EST_RJ_INTER_RAT                    = 9,       /* RR connection Reject: ָʾ������ϵͳ */
    LRRC_APP_EST_IMMEDIATE_ASSIGN_REJECT         = 10,      /* �����Ľ�����̣�����RA������յ�����ָ�ɾܾ���Ϣ��
                                                                û���յ�����ָ����Ϣ�����µĽ���ʧ�� */
    LRRC_APP_EST_RANDOM_ACCESS_REJECT            = 11,      /* �����Ľ�����̣�����RA�����û���յ�����������ָ�ɣ�
                                                                Ҳû���յ�����ָ�ɾܾ�������ʧ�� */
    LRRC_APP_EST_CELL_SEARCHING                  = 12,      /* RRCĿǰ���ܴ���������NAS�յ���ԭ��ֵ��
                                                                ֱ���յ�RRC_MM_SYS_INFO_IND�ٷ�����*/
    LRRC_APP_EST_RESULT_BUTT
};
typedef VOS_UINT8 LRRC_APP_LNAS_EST_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    : LRRC_FLOW_CTRL_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���̿�������ö��
             �޸�ö��ʱ��Ҫע�⣬ʧ������ȡֵ = ��������ȡֵ+1
 ����: LRRC_FLOW_CTRL_TYPE_G2L_RESEL_FAIL = LRRC_FLOW_CTRL_TYPE_G2L_START_RESEL + 1
*****************************************************************************/
enum LRRC_APP_FLOW_CTRL_TYPE_ENUM
{
    LRRC_APP_FLOW_CTRL_TYPE_L2L_NORMAL            = 0,     /* LTE������ */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_START_RESEL,               /* G->L��ʼ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_RESEL_FAIL,                /* G->L��ѡʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_STOP_RESEL,                /* G->Lֹͣ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_START_REDIR,               /* G->L��ʼ�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_REDIR_FAIL,                /* G->L�ض���ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_STOP_REDIR,                /* G->Lֹͣ�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_START_CCO,                 /* G->L��ʼCCO */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_CCO_FAIL,                  /* G->L CCOʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_STOP_CCO,                  /* G->LֹͣCCO */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_START_HO,                  /* G->L��ʼHO */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_HO_FAIL,                   /* G->L HOʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_STOP_HO,                   /* G->LֹͣHO */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_START_RESEL,               /* W->L��ʼ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_RESEL_FAIL,                /* W->L��ѡʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_STOP_RESEL,                /* W->Lֹͣ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_START_REDIR,               /* W->L��ʼ�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_REDIR_FAIL,                /* W->L�ض���ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_STOP_REDIR,                /* W->Lֹͣ�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_START_HO,                  /* W->L��ʼHO */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_HO_FAIL,                   /* W->L HOʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_STOP_HO,                   /* W->LֹͣHO */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_START_PLMN,                /* W->L��ʼPLMN���� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_DONE_PLMN,                 /* W->L PLMN������� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_STOP_PLMN,                 /* W->LֹͣPLMN���� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_START_RESEL,               /* L->G��ʼ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_RESEL_FAIL,                /* L->G��ѡʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_START_REDIR,               /* L->G�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_REDIR_FAIL,                /* L->G�ض���ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_START_CCO,                 /* L->G��ʼCCO */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_CCO_FAIL,                  /* L->G CCOʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_START_HO,                  /* L->G��ʼ�л� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_HO_FAIL,                   /* L->G�л�ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_START_RESEL,               /* L->W��ʼ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_RESEL_FAIL,                /* L->W��ѡʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_START_REDIR,               /* L->W�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_REDIR_FAIL,                /* L->W�ض���ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_START_HO,                  /* L->W��ʼ�л� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_HO_FAIL,                   /* L->W�л�ʧ�� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_IDLE_MEAS,                 /* G->L IDLE�������� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_IDLE_MEAS,                 /* W->L IDLE�������� */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_CONN_MEAS,                 /* G->L CONN�������� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_CONN_MEAS,                 /* W->L CONN�������� */
    LRRC_APP_FLOW_CTRL_TYPE_W2L_RELALL,                    /* W->L RELALL */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_START_CELL_SRCH,           /* L->W ���� */
    LRRC_APP_FLOW_CTRL_TYPE_L2W_STOP_CELL_SRCH,            /* L->W ֹͣ���� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_START_CELL_SRCH,           /* L->G ���� */
    LRRC_APP_FLOW_CTRL_TYPE_L2G_STOP_CELL_SRCH,            /* L->G ֹͣ���� */
    LRRC_APP_FLOW_CTRL_TYPE_T2L_RELALL,                    /* T->L RELALL */
    LRRC_APP_FLOW_CTRL_TYPE_G2L_RELALL,                    /* G->L RELALL */
    LRRC_APP_FLOW_CTRL_TYPE_L2T_START_REDIR,               /* L->T�ض��� */
    LRRC_APP_FLOW_CTRL_TYPE_L2T_START_HO,                  /* L->T��ʼ�л� */
    LRRC_APP_FLOW_CTRL_TYPE_L2T_START_RESEL,               /* L->T��ʼ��ѡ */
    LRRC_APP_FLOW_CTRL_TYPE_T2L_IDLE_MEAS,                 /* T->L IDLE�������� */
    LRRC_APP_FLOW_CTRL_TYPE_T2L_CONN_MEAS,                 /* G->L CONN�������� */

    LRRC_APP_FLOW_CTRL_TYPE_BUTT
};
typedef VOS_UINT8 LRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_APP_BOOL_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : PSͳһ��������ö�ٶ���
*****************************************************************************/
enum RRC_APP_BOOL_ENUM
{
    RRC_APP_PS_FALSE                            = 0,
    RRC_APP_PS_TRUE                             = 1,
    RRC_APP_PS_BOOL_BUTT
};
typedef VOS_UINT8   RRC_APP_BOOL_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CATEGORY_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : UE Category����μ�36306Э��
*****************************************************************************/
enum RRC_APP_CATEGORY_ENUM
{
    RRC_APP_UE_CATEGORY_1                   = 0,
    RRC_APP_UE_CATEGORY_2                   = 1,
    RRC_APP_UE_CATEGORY_3                   = 2,
    RRC_APP_UE_CATEGORY_4                   = 3,
    RRC_APP_UE_CATEGORY_5                   = 4,
    RRC_APP_UE_CATEGORY_6                   = 5,
    RRC_APP_UE_CATEGORY_7                   = 6,
    RRC_APP_UE_CATEGORY_BUTT
};
typedef VOS_UINT8 RRC_APP_CATEGORY_ENUM_UINT8;
/*****************************************************************************
 ö����    : RRC_CONN_REEST_IND_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC�����ؽ������ԭ��
*****************************************************************************/
enum RRC_APP_CONN_REEST_IND_ENUM
{
    RRC_APP_CONN_REEST_FOR_RBCFG_ERROR      = 0,                                    /* 0:����RB����ʧ�ܵ��µ�RRC�����ؽ� */
    RRC_APP_CONN_REEST_FOR_HANDOVER_ERROR   = 1,                                    /* 1:�����л�ʧ�ܵ��µ�RRC�����ؽ� */
    RRC_APP_CONN_REEST_FOR_OTHER_ERROR      = 2,                                    /* 2:����������·ʧ�ܻ�����������֤ʧ�ܵ��µ�RRC�����ؽ� */
    RRC_APP_CONN_REEST_FOR_BUTT
};
typedef VOS_UINT8 RRC_APP_CONN_REEST_IND_ENUM_UINT8;

/*********************************************************
 ö����    : RRC_APP_FTM_CHANGE_INFO_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ϱ�����ģʽ���Ͷ���
**********************************************************/
enum RRC_APP_FTM_CHANGE_INFO_TYPE_ENUM
{
    RRC_APP_FTM_CHANGE_CELL_INFO,  /* RRCפ��С����Ϣ���仯���ϱ����л�����ѡ��ɺ��ϱ� */
    RRC_APP_FTM_CHANGE_STATE_INFO, /* RRC״̬��Ϣ���仯���ϱ� */
    RRC_APP_FTM_CHANGE_BUTT
};

typedef VOS_UINT32 RRC_APP_FTM_CHANGE_INFO_TYPE_ENUM_UINT32;
/*********************************************************
 ö����    : LRRC_LPHY_LTE_BAND_WIDTH_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LTE����WIDTH_3M���Ǳ�ʾ���д�����3M��������ʾ3M����
**********************************************************/
enum LRRC_APP_BAND_WIDTH_ENUM
{
    LRRC_APP_LTE_BAND_WIDTH_1D4M = 0,
    LRRC_APP_LTE_BAND_WIDTH_3M,
    LRRC_APP_LTE_BAND_WIDTH_5M,
    LRRC_APP_LTE_BAND_WIDTH_10M,
    LRRC_APP_LTE_BAND_WIDTH_15M,
    LRRC_APP_LTE_BAND_WIDTH_20M,
    LRRC_APP_LTE_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 LRRC_APP_BAND_WIDTH_ENUM_UINT16;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
                  ����ģʽ�ϱ��ṹ�嶨��
*****************************************************************************/
/*********************************************************************
* ASN �ı� :MCC
*********************************************************************/
typedef struct
{
    VOS_UINT8                           ucCnt;    /*(0, 3)*/
    VOS_UINT8                           aucItem[RRC_APP_MAX_NUM_OF_MCC];
}RRC_APP_MCC_STRU;

/*********************************************************************
* ASN �ı� :PLMN-Identity
*********************************************************************/
typedef struct
{
    RRC_APP_MCC_STRU                         Mcc;                          /* optional */
    RRC_APP_MCC_STRU                         Mnc;
}LRRC_APP_PLMN_ID_STRU;
/*****************************************************************************
 �ṹ��    :APP_RRC_Txpwr
 �ṹ˵��  :RRC�ϱ���APP�����з��书��
*****************************************************************************/
typedef struct
{
    VOS_INT16                        sPuschTxPwr;
    VOS_INT16                        sPucchTxPwr;
    VOS_INT16                        sSrsTxpwr;
    VOS_UINT16                       usReserved;
}RRC_APP_Txpwr_INFO_STRU;
/*****************************************************************************
 �ṹ��    :RRC_APP_PUSCH_BLER_STRU
 �ṹ˵��  :RRC�ϱ���APP��PUSCH�����ʽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32             ulAckCnt;    /* �յ���ACK���� */
    VOS_UINT32             ulNackCnt;   /* �յ���NACK���� */
}RRC_APP_PUSCH_BLER_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_PDSCH_BLER_STRU
 �ṹ˵��  :RRC�ϱ���APP��PDSCH�����ʽṹ����Ҫ��ʾ��ʼ�����ʺ��ۼ������ʣ���Ҫ��������ʾ
*****************************************************************************/
typedef struct
{
    VOS_UINT16              ausCWInitTotal[NUM_OF_CODEWORD]; /* ��ʼ�����ʣ��յ�����֡�����������������ȷ�� */
    VOS_UINT16              ausCWInitError[NUM_OF_CODEWORD]; /* ��ʼ�����ʣ��յ��Ĵ�����֡���� */
    VOS_UINT16              ausCWReTotal[NUM_OF_CODEWORD];   /* ���������ʣ��յ�����֡�����������������ȷ�� */
    VOS_UINT16              ausCWReError[NUM_OF_CODEWORD];   /* ���������ʣ��յ��Ĵ�����֡���� */
}RRC_APP_PDSCH_BLER_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_PDCCH_BLER_STRU
 �ṹ˵��  :RRC�ϱ���APP����������Ȩ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulDlGrantCnt; /* ������Ȩ���� */
    VOS_UINT32              ulUlGrantCnt; /* ������Ȩ���� */
}RRC_APP_PDCCH_BLER_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_BLER_INFO_STRU
 �ṹ˵��  :RRC�ϱ���APP�������ʽṹ
*****************************************************************************/
typedef struct
{
    RRC_APP_PUSCH_BLER_STRU         stPuschBlerCnt; /* PUSCH �����BLER */
    RRC_APP_PDSCH_BLER_STRU         stPdschBlerCnt; /* PDSCH �����BLER */
    RRC_APP_PDCCH_BLER_STRU         stPdcchBlerCnt; /* PDCCH ��������Ȩ���� */
}RRC_APP_BLER_INFO_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_PERIOD_CELL_INFO_STRU
 �ṹ˵��  :RRC�����ϱ���APP��פ��С����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sRsrp;              /* RSRP����ֵ��Χ��(-141,-44)����λdbm*/
    VOS_INT16                           sRsrq;              /* RSRQ����ֵ��Χ��(-40, -6) */
    VOS_INT16                           sRssi;              /* RSSI����ֵ����λdbm */
    VOS_UINT16                          usRI;               /* RIֵ */
    VOS_UINT16                          ausCQI[2];          /* CQI�������֣�ֻ��һ������ʱ�������һ��ֵ��Ч */
    VOS_INT32                           lSINR;              /* SINR��С���ο��ź������ */
    RRC_APP_Txpwr_INFO_STRU             stTxPwr;            /* LTE�����ŵ����͹��� */
    RRC_APP_BLER_INFO_STRU              stBler;             /* LTE������ */
}RRC_APP_PERIOD_CELL_INFO_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_FREQ_PARA_STRU
�ṹ˵��  : RRC�ϱ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usUlFreq;          /* ��������Ƶ�� ��λ:100Khz */
    VOS_UINT16                              usDlFreq;          /* ��������Ƶ�� ��λ:100Khz */
    LRRC_APP_BAND_WIDTH_ENUM_UINT16         enDlBandwidth;     /* ���д��� */
    VOS_UINT8                               usBand;            /* Ƶ��ָʾ */
    VOS_UINT8                               aucResv[1];
} RRC_APP_FREQ_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_CHANGE_CELL_INFO_STRU
 �ṹ˵��  : �仯�ϱ��Ĺ���ģʽ�ṹ--פ��С����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                ulValidNum;                      /* LTE֧��CA����£���Ч��Ƶ���� */
    RRC_APP_FREQ_PARA_STRU                    astFreqInfo[LRRC_APP_MAX_NUM];   /* LTE֧��CA����£�������Ƶ����Ϣ */
    VOS_UINT16                                astPhyCellId[LRRC_APP_MAX_NUM];  /* LTE֧��CA����£�����С��ID��Ϣ */
    VOS_UINT8                                 ucSbuFrmAssignmentType;          /* TDDģʽ����Ч��LTE��֡��ȣ�0xFFΪ��Чֵ */
    VOS_UINT8                                 ucSpecialSubFrmPatterns;         /* TDDģʽ����Ч��LTE������֡��ȣ�0xFFΪ��Чֵ */
    RRC_APP_PAGING_CYCLE_ENUM_UINT32          enPagingCycle;                   /* Ѱ������ */
    RRC_APP_TRANSM_MODE_ENUM_UINT32           enTranMode;                      /* LTE����ģʽ */
}RRC_APP_CHANGE_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_CHANGE_INFO_STRU
 �ṹ˵��  : �仯�ϱ��Ĺ���ģʽ�ṹ
*****************************************************************************/
typedef struct
{
    RRC_APP_FTM_CHANGE_INFO_TYPE_ENUM_UINT32  ulFtmChangeInfoType;

    union
    {
        RRC_APP_CHANGE_CELL_INFO_STRU             stCellInfo;  /* �仯�ϱ��Ĺ���ģʽ�ṹ--פ��С����Ϣ */
        RRC_APP_PROTOCOL_STATE_IND_ENUM_UINT8     enState;     /* �仯�ϱ��Ĺ���ģʽ�ṹ--״̬��Ϣ������Э��״̬���ڲ�����״̬ */
    }u;
}RRC_APP_FTM_CHANGE_INFO_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_PERIOD_INFO_STRU
 �ṹ˵��  : �����ϱ��Ĺ���ģʽ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                 ulValidNum;
    RRC_APP_PERIOD_CELL_INFO_STRU              astCellInfo[LRRC_APP_MAX_NUM]; /* RRC�����ϱ���APP��פ��С����Ϣ */
}RRC_APP_FTM_PERIOD_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_INFO_STRU
 �ṹ˵��  : ����ģʽ�ϱ����ݽṹ
*****************************************************************************/
typedef struct
{
    RRC_APP_FTM_TYPE_ENUM_UINT32             enRrcAppFtmType; /* ����ģʽ�£��ϱ���Ϣ����--�����ϱ��ͱ���ϱ����� */

    union
    {
        RRC_APP_FTM_PERIOD_INFO_STRU         stPeriodInfo;    /* ����ģʽ�£������ϱ����ݣ� Idle״̬�ϱ�����ĿǰΪDRX���ڣ�Connected״̬������Ϊ1��*/
        RRC_APP_FTM_CHANGE_INFO_STRU         stChangeInfo;    /* ����ģʽ�£�������ϱ����� */
    }u;
}RRC_APP_FTM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_INFO_STRU
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

    RRC_APP_FTM_INFO_STRU               stLrrcFtmInfo;

}LRRC_OM_FTM_REPROT_CONTENT_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_INFO_STRU
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
    LRRC_OM_FTM_REPROT_CONTENT_STRU     stLrrcFtmContent;
}LRRC_OM_FTM_REPROT_IND_STRU;

/*****************************************************************************
                   ERROR LOG�ϱ��ṹ�嶨��
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : RRC_APP_ACC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC������Ϣ�洢
*****************************************************************************/
typedef struct
{
    VOS_UINT8                              ucAsRelBitmap;      /* ��������UE�����汾��1��֧�֣�0����֧�֣��ӵ͵���λ�ֱ�����ָʾRel8,Rel9,.... */
    VOS_UINT8                              aucReserved[3];
    VOS_UINT32                             ulFeatureGroupInds; /* ��μ�36.331 B.1  Feature group indicators �½ڣ���λȡֵ */
}RRC_APP_ACC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RRC_EST_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC������Ϣ�洢
*****************************************************************************/
typedef struct
{
    LRRC_APP_LNAS_EST_CAUSE_ENUM_UINT8     enEstCause;             /* ����ԭ�� */
    LRRC_APP_LNAS_EST_RESULT_ENUM_UINT8    enResult;               /* ������� */
    VOS_UINT16                             usReserved;
}RRC_APP_RRC_EST_LIST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_EST_INFO_STRU
 �ṹ˵��  : ERR LOG ���ӽ������ݽṹ,
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucEstCnt; /* ��ǰ�洢�Ľ�����Ϣ���� */
    VOS_UINT8                               aucRseverd[3];
    RRC_APP_RRC_EST_LIST_INFO_STRU          astEstInfoList[RRC_APP_MAX_RRC_EST_INFO_NUM];   /* ������� */
}RRC_APP_RRC_EST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_EST_INFO_STRU
 �ṹ˵��  : ERR LOG ���ӽ������ݽṹ
*****************************************************************************/
typedef struct
{
    RRC_APP_RRC_EST_INFO_STRU               stEstInfo;   /* RRC������Ϣ����ṹ */
    RRC_APP_ACC_INFO_STRU                   stAccInfo;   /* RRC����ʱ��UE��������ṹ */
}RRC_APP_EST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_SYNC_INFO_STRU
 �ṹ˵��  : ERR LOG ͬ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulInSyncCnt;   /* LRRC�յ�LPHY�������ͬ������ */
    VOS_UINT32          ulOutSyncCnt;  /* LRRC�յ�LPHY�������ʧ������ */
}RRC_APP_SYNC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_REEST_INFO_STRU
 �ṹ˵��  : ERR LOG �ؽ������ݽṹ
*****************************************************************************/
typedef struct
{
    RRC_APP_CONN_REEST_IND_ENUM_UINT8   enReestConnCause;   /* ���һ���ؽ�ԭ�� */
    VOS_UINT8                           aucReserved[3];
    RRC_APP_SYNC_INFO_STRU              stSyncInfo;         /* �����ͬ����Ϣ */
}RRC_APP_REEST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_ERR_LOG_PRINT_STRU
 �ṹ˵��  : ERROR LOG RRC �����ӡ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   ulFileIdx; /* �ļ�����ͳһ��ţ�ʹ������ */
    VOS_UINT32                   ulLineNo;  /* �к� */
    VOS_INT32                    lPara1;    /* ����1 */
    VOS_INT32                    lPara2;    /* ����2 */
    VOS_INT32                    lPara3;    /* ����3 */
    VOS_INT32                    lPara4;    /* ����4 */
}RRC_APP_ERROR_PRINT_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_RECIVE_MSG_STRU
 �ṹ˵��  : RRC �����Ϣ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                   ulSendPid;    /* ��������Pid */
    VOS_UINT32                   ulMsgName;    /* ������ϢID */
}RRC_APP_RECIVE_MSG_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_ERROR_PRINT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��ӡ�����Ϣ����ṹ
 ulNextIndex������һ���Ĵ����ӡ����������ulNextIndex = 1����astErrLogPrint[0]
 �����µĴ����ӡ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                     ulNextIndex;
    RRC_APP_ERROR_PRINT_STRU       astErrLogPrint[RRC_APP_ERROR_PRINT_INFO_NUM];
} RRC_APP_ERROR_PRINT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_RECIVE_MSG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������ʱ��ģ���յ���������Ϣ
  ulNextIndex������һ���յ���Ϣ����������ulNextIndex = 1����astReciveMsgInfo[0]
 �����µ��յ�����ϢID
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulNextIndex;
    RRC_APP_RECIVE_MSG_STRU            astReciveMsgInfo[RRC_APP_RECEIVE_MSG_INFO_NUM];
} RRC_APP_RECIVE_MSG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_STATE_INFO_STRU
 �ṹ˵��  : ERROR LOG RRC״̬��Ϣ
*****************************************************************************/
typedef struct
{
    RRC_APP_PROTOCOL_STATE_IND_ENUM_UINT8       enState;            /* RRCЭ��״̬ */  
    VOS_UINT8                                   ucErrcTopMsState;   /* RRC��״̬�����ڲ������״̬�� */
    VOS_UINT8                                   ucErrcTopSsState;   /* RRC��״̬�����ڲ������״̬�� */
    LRRC_APP_FLOW_CTRL_TYPE_ENUM_UINT8          enErrcFlowCtrlType; /* LTE������ϵͳ����ʱ����ϵͳ���̱�ʶ */
}RRC_APP_STATE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_PERIOD_INFO
 �ṹ˵��  : ERROR LOG ���ݽṹ
*****************************************************************************/
typedef struct
{
    RRC_APP_ERROR_PRINT_INFO_STRU    stRrcAppErrorPrintInfo; /* RRC��ӡ�����Ϣ */
    RRC_APP_RECIVE_MSG_INFO_STRU     stRrcAppReciveMsgInfo;  /* ��������ʱ��RRC�յ���������Ϣ */
    RRC_APP_STATE_INFO_STRU          stRrcAppStateInfo;      /* ��������ʱ��RRC״̬��Ϣ������Э��״̬�����ڲ�����״̬�� */
    RRC_APP_EST_INFO_STRU            stRrcAppEstInfo;        /* ��������ʱ��RRC���ӽ�����¼��Ϣ */
    RRC_APP_REEST_INFO_STRU          stRrcAppReestInfo;      /* ��������ʱ��RRC�����ӽ�����¼��Ϣ */
}RRC_APP_ERR_LOG_RRC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_CODE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC�����뱣��ṹ
  ulNextIndex������һ������������������ulNextIndex = 1����aenRrcAppErrorCode[0]�����µ��յ�����ϢID;
                                          ulNextIndex = 0����aenRrcAppErrorCode[0] = RRC_APP_ERR_CODE_BUTT;��RRCû�б��������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                         ulNextIndex;
    RRC_APP_ERROR_CODE_ENUM_UINT16     aenRrcAppErrorCode[RRC_APP_CODE_NUM];
} RRC_APP_CODE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_PERIOD_INFO
 �ṹ˵��  : ERROR LOG ���ݽṹ
*****************************************************************************/
typedef struct
{
    RRC_APP_CODE_INFO_STRU           stCodeInfo;           /* �������ϱ��ṹ��ÿ��ģ�鵥����� */
    RRC_APP_ERR_LOG_RRC_INFO_STRU    stErrorLogInfo;       /* ����λ��Ϣ�ϱ��ṹ */
}RRC_APP_ERR_LOG_INFO_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_FTM_PERIOD_INFO
 �ṹ˵��  : ���ն˽�����ERROR LOG ���ݽṹ
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
    RRC_APP_ERR_LOG_INFO_STRU           stAlmInfo;
}LRRC_OM_ERR_LOG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : OM_ERR_LOG_REPORT_CNF_STRU
 �ṹ˵��  : Balongƽ̨�ڲ�������ERROR LOG ���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* �������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    LRRC_OM_ERR_LOG_INFO_STRU           stErrLogInfo;
} LRRC_OM_ERR_LOG_REPORT_CNF_STRU;

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

#endif /* end of LrrcErrLogInterface.h */


