

#ifndef __TLL2Errorlog_H__
#define __TLL2Errorlog_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "product_config.h"
#include "omnvinterface.h"
#include "SysNvId.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
/*begin:stub for errorlog test*/
//#define FEATURE_PTM    FEATURE_ON
/*end:stub for errorlog test*/
#define TDS_ERRLOG_MAX_FAR_CELL_NUM                64
#define TDS_ERRLOG_PS_MAX_UE_ID_LENGTH             6

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 ö����    : TL_L2_ERROR_CODE_ENUM
 ö��˵��  : TL_L2����������
*****************************************************************************/
enum TL_L2_ERROR_CODE_ENUM
{
    TL_MAC_RAR_NOTMATCH = 1,
    TL_MAC_RAR_TIMEOUT,
    TL_MAC_CONTENT_TIMEOUT,
    TL_MAC_CONTENT_NOTMATCH,
    TL_MAC_PREBLE_FAIL,
    TL_MAC_MSG3_FAIL,
    TL_MAC_TA_TIMEOUT,
    TL_MAC_SR_FAIL,
    TL_RLC_MAXRETXPDU,
    TL_RLC_MEM_FAIL,    
    TL_PDCP_FAIL,
    TDS_ERRLOG_MAC_RANDOM_ACC_FAIL,
    TDS_ERRLOG_MAC_SYNC_FAIL,
    
};
typedef VOS_UINT8 TL_L2_ERROR_CODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TL_L2_ERRLOG_ALMLEVEL_ENUM
 ö��˵��  : TL_L2����������
*****************************************************************************/
enum TL_L2_ERRLOG_ALMLEVEL_ENUM
{
    TL_L2_ERRLOG_ALMLEVEL_CRITICAL   = 1, /*����*/
    TL_L2_ERRLOG_ALMLEVEL_MAJOR      = 2, /*��Ҫ*/
    TL_L2_ERRLOG_ALMLEVEL_MINOR      = 3, /*��Ҫ*/
    TL_L2_ERRLOG_ALMLEVEL_WARING     = 4, /*��ʾ*/

    TL_L2_ERRLOG_ALMLEVEL_BUTT
};
typedef VOS_UINT16  TL_L2_ERRLOG_ALMLEVEL_ENUM_UINT16;

/*****************************************************************************
 ö����    : TL_L2_ERRLOG_MODULE_TYPE
 ö��˵��  : TL_L2����ģ��
*****************************************************************************/
enum TL_L2_ERRLOG_MODULE_TYPE
{
    TL_L2_ERRLOG_PDCP,
    TL_L2_ERRLOG_RLC,
    TL_L2_ERRLOG_MAC,

    TL_L2_ERRLOG_BUTT
};
typedef VOS_UINT8  TL_L2_ERRLOG_MODULE_TYPE_UINT8;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_PUB_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ʵ���ͷ����Ϣ��ά��ʵ���״̬�Լ�RB��LHID��ӳ���ϵ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucRbId;
    VOS_UINT8                   ucLchId;
    VOS_UINT8                   enRlcState;
    VOS_UINT8                   ucRev;
}LTE_ERRLOG_RLC_PUB_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRLC_TM_RX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TM����ʵ��
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_RLC_PUB_INFO_STRU          stPubInfo;
}LTE_ERRLOG_RLC_TM_RX_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_UM_PDUHDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC UM RLCͷ��Ϣ
*****************************************************************************/

typedef struct
{
    VOS_UINT8                       enPduHdrType;       /*��Ϣͷ���� 5bit��10bit*/
    VOS_UINT8                       ucPduHdrLen;        /*��Ϣͷ���� 1��2�ֽ�*/
    VOS_UINT16                      usRev;
}LTE_ERRLOG_RLC_UM_PDUHDR_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_UM_RX_WIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC UM���ղ�Ĵ���ά������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usVRur;         /*VR(UR)*/
    VOS_UINT16                      usVRux;         /*VR(UX)*/
    VOS_UINT16                      usVRuh;         /*VR(UH)*/
    VOS_UINT16                      usRev;
}LTE_ERRLOG_RLC_UM_RX_WIN_STRU;

/*TTF Timer Management*/
typedef struct
{
    VOS_UINT8                       enTimerState;       /* Timer״̬*/
    VOS_UINT8                       aucReserve[3];      /* 4�ֽڶ��룬���� */
    VOS_UINT32                      ulTimerValue;       /* Timerʱ�� */
    VOS_UINT32                      ulStartTime;        /* ����ʱ��� */
}LTE_ERRLOG_UP_TIMER_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_TMR_NODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC TMR���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                 ulTmrVal;
    LTE_ERRLOG_UP_TIMER_STRU             stTtfTmr;
}LTE_ERRLOG_RLC_TMR_NODE_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_SDU_SGMNT
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����SDU��Ƭ����Ϣ�����ղ�ʹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucUsedFlag; /*SDU��Ƭ����Ч�Ա�־*/
    VOS_UINT8                   ucLsfFlag;            /*��Ǵ�SDU������PDU�Ƿ��ѽ��յ����һ��PDU��Ƭ*/
    VOS_UINT16                  usPduSn;    /*��¼��ǰ�ֶ������Ǹ�PDU*/
    VOS_UINT32                  ulSduLen;
}LTE_ERRLOG_RLC_SDU_SGMNT;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_UM_RX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UM����ģʽ
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_RLC_PUB_INFO_STRU              stPubInfo;

    LTE_ERRLOG_RLC_UM_PDUHDR_STRU             stPduHdr;       /*RLCͷ��Ϣ*/
    LTE_ERRLOG_RLC_UM_RX_WIN_STRU             stRxWinVar;     /*���ղര��ά������*/

    /*��ʱ��*/
    LTE_ERRLOG_RLC_TMR_NODE_STRU              stReorderTmr;   /*������ʱ��*/

    /*������Ϣ*/
    LTE_ERRLOG_RLC_SDU_SGMNT                  stSduSgmnt;                     /*SDU��Ƭ��Ϣ*/

    /*����*/
    VOS_UINT16                      usSnModule;         /*SN��ϵ��  32��1024*/
    VOS_UINT16                      usWinSize;          /*���ڴ�С*/

}LTE_ERRLOG_RLC_UM_RX_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_AM_RX_WIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AM���ղര��״̬�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usVRr;     /*VR(R)*/
    VOS_UINT16                      usVRmr;    /*VR(MR)*/
    VOS_UINT16                      usVRx;     /*VR(X)*/
    VOS_UINT16                      usVRh;     /*VR(H)*/
    VOS_UINT16                      usVRms;    /*VR(MS)*/
    VOS_UINT16                      usRev;
}LTE_ERRLOG_RLC_AM_RX_WIN_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_AM_RX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AM���ղ�ʵ��ṹ
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_RLC_PUB_INFO_STRU              stPubInfo;
    LTE_ERRLOG_RLC_AM_RX_WIN_STRU             stRxWinVar;             /*���ڱ���*/

    /*�Ƿ�ʹ��״̬��ʱ���ı�־*/
    VOS_UINT8                       ucCtrlRptFlag;          /*״̬�����־*/
    VOS_UINT8                       ucStatusProhibitFlag;   /*T_STATUS_PROHIBIT��־*/
    VOS_UINT16                      usPollingSn;            /*��pollingλ��SNֵ*/

    /*��ʱ��*/
    LTE_ERRLOG_RLC_TMR_NODE_STRU              stReorderTmr;           /*������ʱ��*/
    LTE_ERRLOG_RLC_TMR_NODE_STRU              stTStatusProhibit;      /*��ֹ��ʱ��*/

    /*����*/
    LTE_ERRLOG_RLC_SDU_SGMNT                  stSduSgmnt;             /*SDU ��Ƭ��Ϣ*/
}LTE_ERRLOG_RLC_AM_RX_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_RX_ENTITY_STRU;
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC���ղ�ʵ��Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucUsedFlag;     /*�Ƿ�ʹ�ñ�־*/
    VOS_UINT8                       ucRbID;
    VOS_UINT8                       ucLchID;
    VOS_UINT8                       enChoice;      /*AM, UM, TM*/

    union
    {
        LTE_ERRLOG_RLC_TM_RX_STRU             stTmRx;         /*TMʵ��*/
        LTE_ERRLOG_RLC_UM_RX_STRU             stUmRx;         /*UMʵ��*/
        LTE_ERRLOG_RLC_AM_RX_STRU             stAmRx;         /*AMʵ��*/
    }u;

}LTE_ERRLOG_RLC_RX_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_TM_TX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TM����ʵ��
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_RLC_PUB_INFO_STRU          stPubInfo;
}LTE_ERRLOG_RLC_TM_TX_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_UM_TX_WIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC UM���Ͳര��ά���ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulVTus;             /*״̬���� VT(US)*/
}LTE_ERRLOG_RLC_UM_TX_WIN_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_UM_TX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UM����ʵ��
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_RLC_PUB_INFO_STRU              stPubInfo;

    LTE_ERRLOG_RLC_UM_PDUHDR_STRU             stPduHdr;           /*RLCͷ��Ϣ*/
    LTE_ERRLOG_RLC_UM_TX_WIN_STRU             stTxWinVar;         /*RLC���Ͳര��״̬����*/

    /*����*/
    VOS_UINT16                      usSnModule;         /*SN��ϵ��  32��1024*/
    VOS_UINT16                      usRev;
}LTE_ERRLOG_RLC_UM_TX_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_AM_TX_WIN_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC AM���Ͳ��״̬�����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                      usVTa;   /*VT(ACK)*/
    VOS_UINT16                      usVTms;  /*Max Send*/
    VOS_UINT16                      usVTs;   /*Send*/
    VOS_UINT16                      usRev;
}LTE_ERRLOG_RLC_AM_TX_WIN_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_AM_POLL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : poll�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucPollFlag;         /*pλ����*/
    VOS_UINT8                       ucRev;
    VOS_UINT8                       ucPollPduFlag;      /*ʹ�÷���PDU��������PoLL��־*/
    VOS_UINT8                       ucPollByteFlag;     /*ʹ�÷���byte��������PoLL��־*/

    VOS_UINT32                      ulCurTxPduNum;      /*��ǰ���͵�PDU��*/
    VOS_UINT32                      ulCurTxByteNum;    /*��ǰ���͵�BYTE��*/

    /*��ʱ��*/
    LTE_ERRLOG_RLC_TMR_NODE_STRU              stPollTmr;
    VOS_UINT32                      ulTPollRxTxSn;      /*T_poll_retransmit�����SN*/

    /*���ò���*/
    VOS_UINT32                      ulPduPoll;          /*����POLL��PDU��*/
    VOS_UINT32                      ulBytePoll;         /*����POLL��byte��*/
}LTE_ERRLOG_RLC_AM_POLL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_AM_CTRL_PDU_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����PDU�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       enCtrlPduState; /*״̬*/
    VOS_UINT8                       aucRev[3];
    VOS_UINT32                      ulPduLen;       /*����PDU�ĳ���*/
}LTE_ERRLOG_RLC_AM_CTRL_PDU_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_AM_TX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���Ͳ�ʵ��ṹ
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_RLC_PUB_INFO_STRU              stPubInfo;

    LTE_ERRLOG_RLC_AM_TX_WIN_STRU             stTxWinVar;     /*���Ͳ��״̬����*/
    LTE_ERRLOG_RLC_AM_POLL_INFO_STRU          stPollInfo;     /*Poll�ṹ*/
    VOS_UINT16                      usSduSgmntSn;   /*SDU��Ƭ��SN��ָʾSDUʱʹ��*/
    VOS_UINT8                       ucRptLinkDownFlag; /*�Ƿ���RRC�ϱ���·���Ͽ���*/
    VOS_UINT8                       ucRev;

    LTE_ERRLOG_RLC_AM_CTRL_PDU_STRU           stCtrlPdu;      /*RLC���Ͳ�ֻ�������µ�״̬PDU*/

    VOS_UINT32                      ulPduMaxRetxNum;        /*�����ش�����*/
    VOS_UINT32                      ulCtrlMaxRetxNum;       /*����PDU������ش�����*/
}LTE_ERRLOG_RLC_AM_TX_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_TX_ENTITY_STRU;
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RLC���Ͳ�ʵ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       ucUsedFlag;     /*�Ƿ�ʹ�ñ�־*/
    VOS_UINT8                       ucRbID;
    VOS_UINT8                       ucLchID;
    VOS_UINT8                       enChoice;      /*AM, UM, TM*/

    union
    {
        LTE_ERRLOG_RLC_TM_TX_STRU             stTmTx;         /*TMʵ��*/
        LTE_ERRLOG_RLC_UM_TX_STRU             stUmTx;         /*UMʵ��*/
        LTE_ERRLOG_RLC_AM_TX_STRU             stAmTx;         /*AMʵ��*/
    }u;

}LTE_ERRLOG_RLC_TX_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_UL_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRLC������ͳ�����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulRxPdcpSdu;             /*RLC�յ�PDCP��SDU��*/
    VOS_UINT32 ulRxPdcpDropSdu;         /*RLC�յ�PDCP֪ͨ����SDU����*/
    VOS_UINT32 ulRlcDropSdu;            /*RLC�յ���Ϣʵ�ʶ����İ�*/
    VOS_UINT32 ulIndTxSduSucc;          /*RLC ָʾPDCP���ͳɹ���SDU��*/
    VOS_UINT32 ulIndTxSduFail;          /*Rlc ָʾPDCP����ʧ�ܵ�SDU��*/
    VOS_UINT32 ulQueFullDropSdu;        /*SDU����������SDU��*/
    VOS_UINT32 ulDropSduNoRsn;          /*����ԭ����SDU��*/

    VOS_UINT32 ulMacNtfSendNum;         /*MAC֪ͨ���ʹ���*/
    VOS_UINT32 ulTxPudToMac;            /*���͵�MAC��PDU��*/
    VOS_UINT32 ulMacNtfRlcNoRes;        /*MAC����ʱ,RLCû����Դ*/
    VOS_UINT32 ulTxNullPduToMac;        /*���صĿ�PDU�Ĵ���*/
    VOS_UINT32 ulMacNtfHarqFail;        /*MAC֪ͨHARQʧ�ܴ���*/
    VOS_UINT32 ulResNotEnough;          /*MAC������Դ����*/

    VOS_UINT32 ulRxCtrlPdu;             /*�յ�ENB��״̬PDU����*/
    VOS_UINT32 ulRxDlCtrlPdu;           /*�յ����е�״̬������*/
    VOS_UINT32 ulRxCtrlPduNackSNOutWIn; /*�����ܵ���NACK SN�ڴ���*/
    VOS_UINT32 ulTxCtrlPdu;             /*���͵�ENB��״̬PDU��Ŀ*/
    VOS_UINT32 ulTotalReTxPdu;          /*�ش�PDU�Ĵ�����ÿ�ش�һ�μ�һ*/
    VOS_UINT32 ulReTxPollTmr;           /*�ش���ʱ������������*/
    VOS_UINT32 ulIndRrcLinkErr;         /*��L3ָʾ��·ʧ��*/
    VOS_UINT32 ulIndRrcRlcErr;          /*��L3ָʾ����Ĵ�����RLC�ڲ�����*/

    VOS_UINT32 ulRxRrcRelease;          /*�յ�RRC���ͷŴ���*/
    VOS_UINT32 ulRrcCfg;                /*�յ����ô���*/
    VOS_UINT32 ulRrcCfgFail;            /*����ʧ�ܴ���*/
    VOS_UINT32 ulReestablish;           /*�ؽ�������*/
    VOS_UINT32 ulReestablishFail;       /*�ؽ���ʧ�ܴ���*/
    VOS_UINT32 ulReTxSegNum;            /*���͵��طֶη�Ƭ�Ĵ���*/
    VOS_UINT32 ulInputPdu;              /*����״̬��������ش����е�Pdu*/
    VOS_UINT32 ulInputPduSeg;           /*����״̬��������ش����е�Pdu��Ƭ*/
}LTE_ERRLOG_RLC_UL_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_RLC_DL_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LRLC������ͳ�����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulRxMacPdu;              /*�յ�MAC���͵�RLC pdu����*/
    VOS_UINT32 ulDropMacPdu;            /*��������PDU����*/
    VOS_UINT32 ulProcMacPduFail;        /*MAC��PDU����ʧ��*/
    VOS_UINT32 ulReRecvSnDrop;          /*�ظ���SN������*/
    VOS_UINT32 ulReorderTmrOut;         /*������ʱ����*/

    VOS_UINT32 ulRxCtrlPdu;             /*�յ�MAC���͵�״̬PDU������*/
    VOS_UINT32 ulTxEnbCtrlPdu;          /*��RLC���з���ENB״̬PDU������*/
    VOS_UINT32 ulTxDlCtrlPdu;           /*��RLC���з�������״̬PDU������*/
    VOS_UINT32 ulTxDlCtrlPduFail;       /*��RLC���з�������״̬PDUʧ�ܵ�����*/

    VOS_UINT32 ulTxSduToPdcpSucc;       /*���͵�PDCP��SDU�ĳɹ���Ŀ*/
    VOS_UINT32 ulTxSduToPdcpFail;       /*���͵�PDCP��SDU��ʧ����Ŀ*/
    VOS_UINT32 ulAllocSduMsgFail;       /*����SDU��PDCP�����ڴ�ʧ��*/

    VOS_UINT32 ulResmPdufail;           /*����ʧ�ܶ�����PDU*/
    VOS_UINT32 ulDropHeadSgmnt;         /*����ͷ��Ƭ*/
    VOS_UINT32 ulDropTailSgmnt;         /*����β��Ƭ*/

    VOS_UINT32 ulStartTmrFail;          /*������ʱ��ʧ��*/
    VOS_UINT32 ulStopTmrFail;           /*������ʱ��ʧ��*/

    VOS_UINT32 ulIndRrcRlcMemErr;       /*��L3ָʾ�ڴ�ľ��������ڴ汣������*/
    VOS_UINT32 ulIndRrcRlcErr;          /*��L3ָʾ����Ĵ�����RLC�ڲ�����*/
    VOS_UINT32 ulRlcDlCfg;              /*���ô���*/
    VOS_UINT32 ulRlcDlCfgFail;          /*����ʧ�ܴ���*/
    VOS_UINT32 ulRlcDlRealse;           /*�ͷŴ���*/
    VOS_UINT32 ulReCfg;                 /*�ؽ�����*/
    VOS_UINT32 ulReCfgFail;             /*�ؽ�ʧ�ܴ���*/
    VOS_UINT32 ulRecePduSeg;             /*Rlc���յ���Pdu��Ƭ����*/
    VOS_UINT32 ulAssemPduSeg;             /*������طֶε�Pdu����*/

    VOS_UINT32 ulPduLiError;             /*PDU��LI�ֶ��쳣ͳ��*/
    VOS_UINT32 ulPduLsfError;            /*PDU�ֶλ��طֶ�������LSF�ֶ��쳣*/
    VOS_UINT32 ulPduRedupDiscard;         /*PDU�ظ�����������*/

    VOS_UINT32 ulRxPduSize;               /*����PDU�ֽ���*/
}LTE_ERRLOG_RLC_DL_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_ULSCH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPeriodBsrTimer;
    VOS_UINT32                          ulRetxBsrTimer;

    VOS_UINT8                           ucUlMaxHarqTxNum;
    VOS_UINT8                           enTtiBundling;
    VOS_UINT8                           enExtendedBsrSizes;
    VOS_UINT8                           aucRev[1];

}LTE_ERRLOG_MAC_ULSCH_INFO_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_PHR_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPeriodPhrTimer;
    VOS_UINT32                          ulProhibitPhrTimer;
    VOS_UINT8                           ucDlPathLossChange;
    VOS_UINT8                           enExtendPhr;
    VOS_UINT8                           enSimulPUCCH_PUSCH;
    VOS_UINT8                           aucRev[1];
}LTE_ERRLOG_MAC_PHR_INFO_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_SR_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSrPeriod;
    VOS_UINT8                           ucSrOffset;
    VOS_UINT16                          usSrTransMax;

    VOS_UINT8                           usSrCfgFlag;/*SR������Ϣ�Ƿ���Ч��0:��Ч��1:��Ч*/
    VOS_UINT8                           aucRev1[1];
    VOS_UINT16                          usSrProhibitTimer;

}LTE_ERRLOG_MAC_SR_INFO_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_GROUPA_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPblGrpASize;                          /*Group A����Ӧ��Preamble����:����տ�û�У������ó� 0 */
    VOS_UINT8                           aucRev1[1];
    VOS_UINT16                          usMessageSizeGroupA;                    /*Э��36.321�Ĳ���MESSAGE_SIZE_GROUP_A*/

    VOS_INT8                            cMessagePowerOffsetGroupB;              /*Э��36.321�Ĳ���MESSAGE_POWER_OFFSET_GROUP_B,ȡֵЭ�����*/
    VOS_UINT8                           aucRev2[3];

} LTE_ERRLOG_MAC_GROUPA_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_RACH_COMM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitGroupAValid  :1;                     /*Group A��Ϣ�Ƿ���Ч��־��0:��Ч��1:��Ч*/
    VOS_UINT32                          bitSpare        :31;

    LTE_ERRLOG_MAC_GROUPA_CONFIG_STRU             stGroupAConfig;

    VOS_UINT8                           ucPblNum;                               /*Group A��B����Ӧ����Preamble����*/
    VOS_UINT8                           ucPblPwrStep;                           /*Preamble������������*/
    VOS_INT16                           sPblInitTargetPwr;                      /*Preamble��eNB���������չ���*/

    VOS_UINT8                           ucPblMaxTxNum;                          /*�������Preamble����ʹ���*/
    VOS_UINT8                           ucRarWindowSize;                        /*�������������Ӧ��Ϣ�Ĵ���*/
    VOS_UINT8                           ucContentTimer;                         /*���������ʱ��*/
    VOS_UINT8                           ucMaxHarqMsg3Tx;                        /*Msg3����HARQ������ʹ���*/

    VOS_INT8                            cPMax;                                  /*����书�ʣ�ȱʡʱʹ��UE�����е�����书��*/
    VOS_INT8                            cDeltaPblMsg3;                          /*Preamble��Msg3֮���OFFSET*/
    VOS_UINT8                           ucSysULRBNum;                           /*����ϵͳ����*/
    VOS_UINT8                           aucRev1[1];
} LTE_ERRLOG_MAC_RACH_COMM_INFO_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_PRACH_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrachConfigIndex;                     /*�Ѿ�ȷ��:Prach-ConfigurationIndex,0-63*/
    VOS_UINT8                           ucPrachFormat;
    VOS_UINT8                           aucRev[2];
}LTE_ERRLOG_MAC_PRACH_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_RACH_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_MAC_RACH_COMM_INFO_STRU            stRachCommInfo;                         /*36.331 6.3.2��RACH-ConfigCommon*/
    LTE_ERRLOG_MAC_PRACH_CONFIG_STRU              stPrachConfig;                          /*36.331 6.3.2��PRACH-Configuration PRACH��������*/

    VOS_UINT8                           ucUeIdLength;                           /*UE���ȣ��ݶ��ֽ�Ϊ��λ*/
    VOS_UINT8                           aucRev2[1];
    VOS_UINT8                           aucUeId[TDS_ERRLOG_PS_MAX_UE_ID_LENGTH];           /*ue id�ĸ�ʽ������*/

}LTE_ERRLOG_MAC_RACH_INFO_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_TA_TIMER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellTaTimer;
    VOS_UINT16                          usTaTimer;
}LTE_ERRLOG_MAC_TA_TIMER_INFO_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_RNTI_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCRntiValid;                           /*C-RNTI�Ƿ���Ч��־,0:��Ч,1:��Ч*/
    VOS_UINT8                           aucRev[3];
    VOS_UINT16                          usCRnti;                                /*C-RNTIֵ*/
    VOS_UINT16                          usTmpCRnti;                             /*��ʱC-RNTI*/
}LTE_ERRLOG_MAC_RNTI_INFO_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_SPS_DL_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSpsIntervalDL;
    VOS_UINT8                           aucRev[2];

}LTE_ERRLOG_MAC_SPS_DL_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_SPS_UL_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSpsIntervalUL;
    VOS_UINT8                           ucImplicitReleaseAfter;
    VOS_UINT8                           aucRev[1];

}LTE_ERRLOG_MAC_SPS_UL_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_SPS_CONFIG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitSpsDlValid:1;
    VOS_UINT32                          bitSpsUlValid:1;
    VOS_UINT32                          bitSpare:30;

    LTE_ERRLOG_MAC_SPS_DL_CONFIG_STRU             stSpsDlConfig;
    LTE_ERRLOG_MAC_SPS_UL_CONFIG_STRU             stSpsUlConfig;

}LTE_ERRLOG_MAC_SPS_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_TDD_CONFIG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSubFrameAssig;

    VOS_UINT8                           aucRev[3];

}LTE_ERRLOG_MAC_TDD_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_CELL_STATUS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucConfiged;                             /*С������״̬ 1:������; 0:δ����*/
    VOS_UINT8                           ucActived;                              /*С������״̬ 1:���� 0:ȥ����*/
    VOS_UINT8                           aucRev[2];
}LTE_ERRLOG_MAC_CELL_STATUS_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_CA_CONFIG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_MAC_CELL_STATUS_STRU               astLmacStatus[8];
    VOS_UINT32                          ulScellDeactTimer;
}LTE_ERRLOG_MAC_CA_CONFIG_INFO_STRU;

/*****************************************************************************
 �ṹ��    :LTE_ERRLOG_MAC_RA_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucValid;                                /*������������Ϣ�Ƿ���Чָʾ,0:��Ч,1:��Ч*/
    VOS_UINT8                           ucRaPblId;                              /*�������ѡ���PreambleID*/
    VOS_UINT8                           ucRaPblGrpId;                           /*�������ѡ���PreambleȺ��*/
    VOS_UINT8                           ucRarWindowSize;

    VOS_UINT16                          usPathLoss;                             /*����ѡ��Group A��B��ʵ��·�𣬸�ֵ��Ҫȷ�ϻ�ȡ��ʽ */
    VOS_UINT16                          usMsg3Size;                             /*����ѡ��Group A��B����Ϣ3��Сֵ */

    VOS_UINT8                           enRaTrigger;                            /*������봥��Դ��0:RRC,1:MAC,2:PDCCH */
    VOS_UINT8                           enRaCause;                              /*������봥��ԭ��*/
    VOS_UINT8                           enRaType;                               /*�����������*/
    VOS_UINT8                           ucRaTxNum;                              /*��������ط���������*/

    VOS_INT16                           sRaTxPower;                             /*�������ʵ�ʷ��书��*/
    VOS_UINT16                          usBackOff;                              /*BIֵ*/

    VOS_UINT16                          usOpId;                                 /*������*/
    VOS_UINT8                           ucRaPrachMaskIndex;
    VOS_UINT8                           ucRrcOriginMsg3Size;

    VOS_UINT16                          usDetalPrampup;                         /*��������ۼƲ�������ֵ*/
    VOS_UINT16                          usMacPhyOpId;
}LTE_ERRLOG_MAC_RA_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_BSR_DYN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           enPeriBsrFlag;                          /*BSR��־,TRUEΪҪ�ϱ�,FALSEΪ��Ҫ�ϱ�*/
    VOS_UINT8                           enRegBsrFlag;                           /*Regular BSR��־,TRUEΪҪ����SR��FALSEΪ������SR*/

    VOS_UINT8                           ucMaxLchPri;
    VOS_UINT8                           ucLcgNum;

    VOS_UINT8                           aucLcgId[4];                             /*����߼��ŵ���ID*/
    VOS_UINT8                           enSrMaskTrigBsr;
    VOS_UINT8                           aucRev1[3];

}LTE_ERRLOG_MAC_BSR_DYN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_SR_DYN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           enSrState;
    VOS_UINT8                           ucSrCounter;                            /*SR�ۼƴ���*/
    VOS_UINT16                          usSrDynMaxNum;

    VOS_UINT16                          usSrLastFrame;                          /*SR�ϴη��͵�֡��*/
    VOS_UINT8                           ucSrLastSubFrame;                       /*SR�ϴη��͵���֡��*/
    VOS_UINT8                           ucSrSendNotCnf;


    VOS_UINT16                          usSrSendNotCnfCount;                    /*SR���������ò���CNF�ļ���*/
    VOS_UINT16                          usSrOpId;

}LTE_ERRLOG_MAC_SR_DYN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_LPHY_DECREASE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usPowerBackoff;
    VOS_UINT16                         usFrame;
    VOS_UINT8                          ucSubFram;
    VOS_UINT8                          aucRev[3];
}LTE_ERRLOG_MAC_LPHY_DECREASE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_PHR_DYN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCurPhrPathLost;                       /*��ǰ���µ�·������ֵ����תΪdB*/
    VOS_UINT16                          usLastPhrPathLost;                      /*��һ��PHR�ϱ�ʱ��·������ֵ,��תΪdB*/
    VOS_UINT16                          usCurPhrPowerBackoff;                   /*��ǰ���µĹ��ʻ���ֵ����תΪdB*/
    VOS_UINT16                          usLastPhrPowerBackoff;                  /*��һ��PHR�ϱ�ʱ�Ĺ��ʻ���ֵ����תΪdB*/
    VOS_UINT8                           enPeriPhrFlag;                          /*����PHR�ϱ���־,TRUEΪҪ�ϱ�,FALSEΪ��Ҫ�ϱ�*/
    VOS_UINT8                           enProhibitPhrFlag;                      /* Prohibit PHR��ʱ����ʱ������־,TRUEΪҪ�ϱ�,FALSEΪ��Ҫ�ϱ� */
    VOS_UINT8                           aucRev[2];
    LTE_ERRLOG_MAC_LPHY_DECREASE_INFO_STRU        stPrePBInfo;                            /*ǰһ��Power Backoff��Ϣ*/
    LTE_ERRLOG_MAC_LPHY_DECREASE_INFO_STRU        stLatestPBInfo;                         /*���һ��Power Backoff��Ϣ*/
}LTE_ERRLOG_MAC_PHR_DYN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_TA_DYN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           enTaRunFlag;                           /* TA��ʱ��ʱ������û�л�������������������룬�����򴥷� */
    VOS_UINT8                           aucRev1[3];
}LTE_ERRLOG_MAC_TA_DYN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_SPS_DYN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSpsPadCouter;
    VOS_UINT8                           enUlSpsGrantFlag;
    VOS_UINT8                           aucRev1[2];
}LTE_ERRLOG_MAC_SPS_DYN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_CTRL_ELEM_DYN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_MAC_BSR_DYN_INFO_STRU              stLmacBsrDynInfo;
    LTE_ERRLOG_MAC_SR_DYN_INFO_STRU               stLmacSrDynInfo;
    LTE_ERRLOG_MAC_PHR_DYN_INFO_STRU              stLmacPhrDynInfo;
    LTE_ERRLOG_MAC_TA_DYN_INFO_STRU               stLmacTaDynInfo;
    LTE_ERRLOG_MAC_SPS_DYN_INFO_STRU              stLmacSpsDynInfo;
}LTE_ERRLOG_MAC_CTRL_ELEM_DYN_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_MAC_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           enLMacState;                            /*MAC ʵ��״̬*/
    VOS_UINT8                           ucCurrSubFrame;                         /*��ǰ��֡��*/
    VOS_UINT16                          usCurrFrame;                            /*��ǰ֡��*/

    VOS_UINT8                           enLmacFrameType;
    VOS_UINT8                           aucRev1[3];

    LTE_ERRLOG_MAC_ULSCH_INFO_STRU                stLmacUlschInfo;                        /*MAC���д����ŵ�����ز�����Ϣ*/
    LTE_ERRLOG_MAC_PHR_INFO_STRU                  stLmacPhrInfo;                          /*PHR��ز�����Ϣ*/
    LTE_ERRLOG_MAC_SR_INFO_STRU                   stLmacSrInfo;                           /*����������ز�����Ϣ*/
    LTE_ERRLOG_MAC_RACH_INFO_STRU                 stLmacRachInfo;                         /*RACH�ŵ������Ϣ*/
    LTE_ERRLOG_MAC_TA_TIMER_INFO_STRU             stLmacTaTimerInfo;                      /*TA Timer�����Ϣ*/
    LTE_ERRLOG_MAC_RNTI_INFO_STRU                 stLmacRntiInfo;                         /*RNTI �����Ϣ*/
    LTE_ERRLOG_MAC_SPS_CONFIG_INFO_STRU           stLmacSpsConfig;                        /*�뾲̬���������Ϣ*/
    LTE_ERRLOG_MAC_TDD_CONFIG_INFO_STRU           stLmacTddConfig;                        /*TDD�����Ϣ*/
    //LTE_ERRLOG_MAC_CA_CONFIG_INFO_STRU            stLmacCaConifg;                         /*С�����úͼ���״̬��Ϣ*/

    LTE_ERRLOG_MAC_RA_CTRL_STRU                   stLmacRaCtrl;                            /*���������̶�̬����*/

    LTE_ERRLOG_MAC_CTRL_ELEM_DYN_INFO_STRU        stLmacCtrlElemDynInfo;                  /*MAC ����Ԫ�Լ�SR��̬������Ϣ��������־λ��*/

}LTE_ERRLOG_MAC_ENTITY_STRU;

typedef struct
{
    VOS_UINT32                                ulSendShortBsr;
    VOS_UINT32                                ulSendLongBsr;
    VOS_UINT32                                ulSendAbnormBsr;
    VOS_UINT32                                ulSendPadBsr;
    VOS_UINT32                                ulSendPadShortBsr;
    VOS_UINT32                                ulSendPadLongBsr;
    VOS_UINT32                                ulSendTruncatedBsr;
    VOS_UINT32                                ulCancelBsr;
    VOS_UINT32                                ulLongToShortBsr;

}LTE_ERRLOG_MAC_DEBUG_BSR_INFO_STRU;

typedef struct
{
    VOS_UINT32                                ulRecvSchFrmInd;                  /*MAC�յ��ĵ���ָ֡ʾ*/
    VOS_UINT32                                ulRecvUnexptedSchFrm;             /*MAC�յ���������֡������֡��ͳ��*/
    VOS_UINT32                                ulRecvSameFrame;                  /*MAC�յ���ͬ��֡������֡��ͳ��*/

    VOS_UINT32                                ulTotalSchNotFinishNum;           /*MAC1ms����û����ɵĴ���*/

    VOS_UINT32                                ulMacSchedMacPduSuccNum;
    VOS_UINT32                                ulMacSchedMacPduFailNum;          /*MAC ��������쳣ͳ��*/
    VOS_UINT32                                ulMacPduNotFree;                  /*������֡�������ȵ���MAC PDUԴ��û�м�ʱ�ͷ�*/
    VOS_UINT32                                ulMacRecvRlcPduTotal;

    VOS_UINT32                                ulSendPhr;
    VOS_UINT32                                ulGetPhrErr;
    VOS_UINT32                                ulSendSr;
    VOS_UINT32                                ulPhyCancelSr;
    VOS_UINT32                                ulMacCancelSr;
    VOS_UINT32                                ulTaTimeOutNum;
    VOS_UINT32                                ulSCellDeacTimeOutNum;
    VOS_UINT32                                ulSendPadding;
    VOS_UINT32                                ulSendPadHead;

    VOS_UINT32                                ulGetRlcNuLLBuffNum;              /*��ȡRLC������ϢΪ0��ͳ��*/
    VOS_UINT32                                ulGetCcchInActiveNum;             /*����̬�²�ѯ��CCCHΪ�ǿ�ͳ��*/
    VOS_UINT32                                ulGetLchPriFromRlcFail;           /*RLCû�ж��߼��ŵ���ȷ����*/

    VOS_UINT32                                ulMsg3NotContainHoCmp;            /*�л������Ϣû����Msg3ͳ��*/

    VOS_UINT32                                ulUlGrantNotSchErr;               /*������Ȩ�������ʱ�̵�ͳ��*/

    VOS_UINT32                                ulPhyReleaseUlSps;                /*Phy�ͷ����а뾲ָ̬ʾ*/
    VOS_UINT32                                ulMacReleaseUlSps;                /*MAC�ͷ����а뾲ָ̬ʾ*/

    VOS_UINT32                                ulForbidDspSleepFail;             /*ǿ��DSP��˯��ʧ��*/
    VOS_UINT32                                ulWriteDediMailBoxFail;           /*дר������ʧ��*/

    LTE_ERRLOG_MAC_DEBUG_BSR_INFO_STRU                  stBsr;
}LTE_ERRLOG_MAC_DEBUG_UL_STAT_INFO_STRU;

typedef struct
{
    VOS_UINT32                                ulDlTbRecvIntRsp;                 /*����TB�����ж���Ӧͳ��*/
    VOS_UINT32                                ulDlTbRecvIntErr;                 /*����TB���մ����ж�ͳ��*/
    VOS_UINT32                                ulDlForbidDspSleepFail;           /*����TB�����ж��н�ֹDSP˯��ʧ��ͳ��*/
    VOS_UINT32                                ulSemTakeTotal;                   /*MAC����ȡ���ź���ͳ��*/

    VOS_UINT32                                ulActDemultipleSucc;
    VOS_UINT32                                ulActDemultipleFail;
    VOS_UINT32                                ulActSendRlcErrorNum;
    VOS_UINT32                                ulActSendRlcNum;
    VOS_UINT32                                ulActDemulOneLchErr;
    VOS_UINT32                                ulActRecvPadding;
    VOS_UINT32                                ulActRecvTa;
    VOS_UINT32                                ulActRecvScellActivation;
    VOS_UINT32                                ulActRecvDrx;

    VOS_UINT32                                ulDlTbAddrNull;                   /*����TB�ڴ��ַΪ�յ�ͳ��*/
    VOS_UINT32                                ulDlTbMemCheckErr;                /*����TB�ڴ��ַ������*/
    VOS_UINT32                                ulDlTbCheckErr;                   /*����TB CRC���ظ����ݼ�����*/
    VOS_UINT32                                ulDlTbCellIndexErr;               /*����TB С��ID����*/
    VOS_UINT32                                ulDlTbSCellDeactived;             /*����TB��Ӧ��SCell״̬Ϊȥ����*/
    VOS_UINT32                                ulOterStateRecvTb;
    VOS_UINT32                                ulRadnomStateRecvTb;
    VOS_UINT32                                ulRadnomStateRecvTbErr;
    VOS_UINT32                                ulHoEnQueTb;
    VOS_UINT32                                ulHoDeQueTb;
    VOS_UINT32                                ulHoDeQueTbErr;
    VOS_UINT32                                ulMacPdcchRecvTb;

    VOS_UINT32                                ulRecvBcchTb;
    VOS_UINT32                                ulRecvPbchTb;
    VOS_UINT32                                ulRecvPchTb;

    VOS_UINT32                                ulDlTbIntAllocMemFail;            /*���и����жϷ����ڴ�ʧ�ܸ���*/
    VOS_UINT32                                ulDlLteMasterGetMemFail;          /*LTE��ģ��DSP��ȡ�ڴ�ʧ��*/
    VOS_UINT32                                ulDlLteSlaveGetMemFail;           /*LTE��ģ��DSP��ȡ�ڴ�ʧ��*/
    VOS_UINT32                                ulDlTbRecvQueFull;                /*����TB���ն�����*/
    VOS_UINT32                                ulDlOtherErrInd;                  /*DSP�ϱ���������������*/

}LTE_ERRLOG_MAC_DEBUG_DL_STAT_INFO_STRU;

typedef struct
{
    VOS_UINT32                                ulSchMsg3Num;                     /*����������Msg3�Ĵ���*/
    VOS_UINT32                                ulSchMsg3ReTransNum;              /*�����ش�Msg3�Ĵ���*/
    VOS_UINT32                                ulGetMsg3FromRlcFail;
}LTE_ERRLOG_MAC_DEBUG_ONRAND_SCHED_INFO_STRU;

typedef struct
{
    VOS_UINT32                                ulMacRaReq;                       /*MAC���������RA�������*/
    VOS_UINT32                                ulPdcchNonContentRaReq;            /*PDCCH Order����ķǾ���RA�������*/
    VOS_UINT32                                ulPdcchContentRaReq;              /*PDCCH Order����ľ���RA�������*/
    VOS_UINT32                                ulRrcNonContentRaReq;             /*RRC����ķǾ���RA�������*/
    VOS_UINT32                                ulRrcContentRaReq;                /*RRC����ľ���RA�������*/
    VOS_UINT32                                ulSelectGroupA;                   /*RA������ѡ��Ⱥ��A�Ĵ���*/
    VOS_UINT32                                ulSelectGroupB;                   /*RA������ѡ��Ⱥ��B�Ĵ���*/

    VOS_UINT32                                ulRecvPhyRaCnf;                   /*MAC�յ�PHY��RAȷ��*/
    VOS_UINT32                                ulRepeatRaReq;                    /*�ظ����������RA�������*/
    VOS_UINT32                                ulMaxRaReq;                       /*�ﵽ���������RA����������*/

    VOS_UINT32                                ulRarTimerOut;
    VOS_UINT32                                ulContentTimerOut;
    VOS_UINT32                                ulRaCnfTimerOut;

    VOS_UINT32                                ulRaCauseFail;                    /*RAԭ�����*/
    VOS_UINT32                                ulSelectGroupABFail;                   /*RA������ѡ��Ⱥ��B�Ĵ���*/

    VOS_UINT32                                ulRecvRarNum;
    VOS_UINT32                                ulRecvRarSucc;
    VOS_UINT32                                ulRecvRarFail;
    VOS_UINT32                                ulRarBiNum;                                                    /*RAR������BI�ɹ�*/
    VOS_UINT32                                ulRarProcSucc;                                                    /*RAR������BI�ɹ�*/
    VOS_UINT32                                ulNonContentSucc;                                                    /*RAR������BI�ɹ�*/

    VOS_UINT32                                ulRecvContentionNum;
    VOS_UINT32                                ulWaitContentionProcFail;

    VOS_UINT32                                ulContentTcrntiSucc;                                                    /*RAR������BI�ɹ�*/
    VOS_UINT32                                ulContentCrntiSucc;                                                    /*RAR������BI�ɹ�*/
    VOS_UINT32                                ulContentNoMatch;                                                    /*RAR������BI�ɹ�*/

    LTE_ERRLOG_MAC_DEBUG_ONRAND_SCHED_INFO_STRU         stOnRand;

    VOS_UINT32                                ulMacNewMsg3Rrctrig;
    VOS_UINT32                                ulMacNewMsg3Mactrig;
    VOS_UINT32                                ulMacNewMsg3MacPdu;
    VOS_UINT32                                ulHoMsg3NoRecvCmp;                /*��Ϣ3û���յ�Ho Complete��Ϣ*/
    VOS_UINT32                                ulMacRetranMsg3Num;
    VOS_UINT32                                ulMacActiveRetranMsg3Num;
    VOS_UINT32                                ulMacOverMsg3MaxRetran;

    VOS_UINT32                                ulStateErrorDrop;
    VOS_UINT32                                ulSendRlcSetupOkNum;              /*MAC���о������ƥ��ɹ������eNB����UE��CCCH����,MAC�ɹ�����RLC*/
    VOS_UINT32                                ulRarSchedNotFinishNum;           /*RAR��Ȩ����MAC PDU��n-2��֡ͷ��δ��ɰ��Ƶ�ͳ����*/
    VOS_UINT32                                ulNoRarCfgCnfNum;                 /*MAC��n-2��֡ͷ��δ����DSP��RAR CONFIG��ȷ��ԭ��*/
}LTE_ERRLOG_MAC_DEBUG_RA_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_UL_ENTITY_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP ����ʵ�����
*****************************************************************************/
typedef struct
{
    /*���ò���*/
    VOS_UINT8                           enDiscardTimerFlag;
    VOS_UINT8                           ucHdrLen;           /*PDCPͷ����*/
    VOS_UINT16                          usSnMod;            /*���кŵ�ģ*/
    VOS_UINT32                          ulMaxPdcpSn;        /*����PDCP���к�:4095*/
    VOS_UINT32                          ulDiscardTimerLen;  /*������ʱ��ʱ��*/
}LTE_ERRLOG_PDCP_UL_ENTITY_PARA_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_UL_VARIABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP ����ʵ�����ά���ṹ
*****************************************************************************/
typedef struct
{
    /*���к�ά��*/
    VOS_UINT32                          ulNextTxSn;         /*��һ��Ҫ����SDU�����к�*/
    VOS_UINT32                          ulTxHfn;            /*�������кŵ����������*/
    VOS_UINT32                          ulCount;            /*���ڼӽ��ܡ���������֤��COUNTֵ*/
}LTE_ERRLOG_PDCP_UL_VARIABLE_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_UL_BSR_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LPDCP����BSR���
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRecvSduLen;
    VOS_UINT32                          ulSendSduLen;
    VOS_UINT32                          ulReTxPduLen;
}LTE_ERRLOG_PDCP_UL_BSR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_AM_UL_ENTITY_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP AMģʽ������ʵ�����
*****************************************************************************/
typedef struct
{
    /*���ò���*/
    VOS_UINT8                           enStatReportFlag;
    VOS_UINT8                           aucRev[3];

}LTE_ERRLOG_PDCP_AM_UL_ENTITY_PARA_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_AM_UL_VARIABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP AMģʽ������ά���ṹ
*****************************************************************************/
typedef struct
{
    /*���к�ά��*/
    VOS_UINT32                          ulNextAckSn;        /*AMģʽ��ȷ�ϵ���С���к�*/
}LTE_ERRLOG_PDCP_AM_UL_VARIABLE_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_AM_UL_ENTITY_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP AMģʽ������ʵ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_PDCP_AM_UL_ENTITY_PARA_STRU        stAmUlPara;         /*ʵ�����*/
    LTE_ERRLOG_PDCP_AM_UL_VARIABLE_STRU           stVariable;         /*����ά���ṹ*/
}LTE_ERRLOG_PDCP_AM_UL_ENTITY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_UM_UL_ENTITY_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP UMģʽ������ʵ������ṹ
*****************************************************************************/
typedef struct
{
    /*���ò���*/
    VOS_UINT8                           enUmSnBit;          /*UMģʽ���к�λ��*/
    VOS_UINT8                           aucRev[3];
}LTE_ERRLOG_PDCP_UM_UL_ENTITY_PARA_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_UM_UL_VARIABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP UMģʽ������ά���ṹ
*****************************************************************************/
typedef struct
{
    /*����*/
    VOS_UINT32                          ulRev;
}LTE_ERRLOG_PDCP_UM_UL_VARIABLE_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_UM_UL_ENTITY_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP UMģʽ������ʵ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_PDCP_UM_UL_ENTITY_PARA_STRU        stUmUlPara;         /*ʵ�����*/
    LTE_ERRLOG_PDCP_UM_UL_VARIABLE_STRU           stVariable;         /*���к�ά���ṹ*/
}LTE_ERRLOG_PDCP_UM_UL_ENTITY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_UL_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP����ʵ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;             /*[0,31],ʵ���Ӧ��RBID*/
    VOS_UINT8                           enUlState;          /*LPDCP����ʵ���״̬*/
    VOS_UINT8                           enRlcModeChoice;    /*PDCPʵ�����ݴ�����õ�RLCģʽ */
    VOS_UINT8                           ucRev;

    LTE_ERRLOG_PDCP_UL_ENTITY_PARA_STRU           stUlPara;
    LTE_ERRLOG_PDCP_UL_VARIABLE_STRU              stUlVariable;

    LTE_ERRLOG_PDCP_UL_BSR_INFO_STRU              stBsrInfo;          /*BSRͳ��*/
    union
    {
        LTE_ERRLOG_PDCP_AM_UL_ENTITY_INFO_STRU    stAmEntity;
        LTE_ERRLOG_PDCP_UM_UL_ENTITY_INFO_STRU    stUmEntity;
    }u;
}LTE_ERRLOG_PDCP_UL_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_DL_ENTITY_PARA_STRU;
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP ����ʵ������ṹ
*****************************************************************************/
typedef struct
{
    /*���ò���*/
    VOS_UINT8                           ucHdrLen;           /*PDCPͷ����*/
    VOS_UINT8                           ucRev;
    VOS_UINT16                          usSnMod;            /*���кŵ�ģ*/
    VOS_UINT32                          ulMaxPdcpSn;        /*����PDCP���к�*/
}LTE_ERRLOG_PDCP_DL_ENTITY_PARA_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_DL_VARIABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP ���б���ά���ṹ
*****************************************************************************/
typedef struct
{
    /*���к�ά������*/
    VOS_UINT32                          ulNextRxSn;
    VOS_UINT32                          ulRxHfn;            /*�������кŵ����������*/
    VOS_UINT32                          ulCount;            /*���ڼӽ��ܡ���������֤��COUNTֵ*/
}LTE_ERRLOG_PDCP_DL_VARIABLE_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_AM_DL_ENTITY_PARA_STRU;
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP AMģʽ������ʵ������ṹ
*****************************************************************************/
typedef struct
{
    /*���ò���*/
    VOS_UINT8                           enStatReportFlag;
    VOS_UINT8                           aucRev[3];

}LTE_ERRLOG_PDCP_AM_DL_ENTITY_PARA_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_AM_DL_VARIABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP AMģʽ�����б���ά���ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLastSubmitSn;     /*���һ���ݽ���SDU��Ӧ��SN*/
    VOS_UINT32                          ulSduCnt;     /*SDU����*/
}LTE_ERRLOG_PDCP_AM_DL_VARIABLE_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_AM_DL_ENTITY_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP AMģʽ������ʵ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_PDCP_AM_DL_ENTITY_PARA_STRU        stAmDlPara;         /*ʵ�����*/
    LTE_ERRLOG_PDCP_AM_DL_VARIABLE_STRU           stVariable;         /*���к�ά���ṹ*/
}LTE_ERRLOG_PDCP_AM_DL_ENTITY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_UM_DL_ENTITY_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP UMģʽ������ʵ������ṹ
*****************************************************************************/
typedef struct
{
    /*���ò���*/
    VOS_UINT8                           enUmSnBit;          /*UMģʽ���к�λ��*/
    VOS_UINT8                           aucRev[3];
}LTE_ERRLOG_PDCP_UM_DL_ENTITY_PARA_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_UM_DL_VARIABLE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP UMģʽ�����к�ά�������ṹ
*****************************************************************************/
typedef struct
{
    /*����*/
    VOS_UINT32                          ulRev;
}LTE_ERRLOG_PDCP_UM_DL_VARIABLE_STRU;

/*****************************************************************************
 �ṹ��    : LPDCP_UM_DL_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP UMģʽ������ʵ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_PDCP_UM_DL_ENTITY_PARA_STRU        stUmDlPara;         /*ʵ�����*/
    LTE_ERRLOG_PDCP_UM_DL_VARIABLE_STRU           stVariable;         /*���к�ά���ṹ*/
}LTE_ERRLOG_PDCP_UM_DL_ENTITY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_DL_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP����ʵ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRbId;             /*[0,31],ʵ���Ӧ��RBID*/
    VOS_UINT8                           enDlState;          /*LPDCP����ʵ���״̬*/
    VOS_UINT8                           enRlcModeChoice;    /*PDCPʵ�����ݴ�����õ�RLCģʽ */
    VOS_UINT8                           ucRev;

    LTE_ERRLOG_PDCP_DL_ENTITY_PARA_STRU           stDlPara;
    LTE_ERRLOG_PDCP_DL_VARIABLE_STRU              stDlVariable;

    union
    {
        LTE_ERRLOG_PDCP_AM_DL_ENTITY_INFO_STRU    stAmEntity;
        LTE_ERRLOG_PDCP_UM_DL_ENTITY_INFO_STRU    stUmEntity;
    }u;
}LTE_ERRLOG_PDCP_DL_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : LTE_ERRLOG_PDCP_UL_DT_RBID_STAT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP���и�RBID��Ӧ���պͷ��͵�SDU��PDU���ͳ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulUlRxSduCnt;           /*���յ���SDUͳ��*/
    VOS_UINT32      ulUlTxPduCnt;           /*���ͳ�ȥ��PDUͳ��*/
    VOS_UINT32      ulUlAckedSduCnt;        /*���յ�ȷ�ϵ�SDUͳ��*/

    VOS_UINT32      ulUlDiscardMaxCnt; /*�������ֵͳ��*/
    VOS_UINT32      ulUlDisSduCnt;          /*��ʱ����ʱ����SDUͳ��*/
    VOS_UINT32      ulUlBufFullDisSduCnt;   /*�ش�buf���޶���SDUͳ��*/
    VOS_UINT32      ulUlReestDiscardCnt;   /*�ؽ�������ͳ��*/

    VOS_UINT32      ulUlInvalidSduCnt;      /*���յ��ķǷ�SDUͳ��*/
    VOS_UINT32      ulUlTxCtrlPduNum;       /*ʵ�巢�͵Ŀ���PDUͳ��*/
    VOS_UINT32      ulUlAckEndSnError;      /*����RLCACK SN����*/

    VOS_UINT32      ulUlReestStopAckSn;
    VOS_UINT32      ulUlReestStopNextTxSn;
    VOS_UINT32      ulUlReestStopHfn;
    VOS_UINT32      ulUlReestContAckSn;
    VOS_UINT32      ulUlReestContNextTxSn;
    VOS_UINT32      ulUlReestContFirstTxSn;
    VOS_UINT32      ulUlReestContHfn;

    VOS_UINT32      ulCompSuccCnt;          /*ѹ���ɹ�����*/
    VOS_UINT32      ulCompFailCnt;          /*ѹ��ʧ�ܴ���*/
    VOS_UINT32      ulRohcCompCnt;          /*ѹ���������*/

    VOS_UINT32      ulSduEnQueFailCnt;

}LTE_ERRLOG_PDCP_UL_DT_RBID_STAT_STRU;

/*****************************************************************************
 �ṹ��    : LPDCP_DL_RBID_STAT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP���и�RBID���պͷ��͵�PDU��SDU���ͳ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32      ulDlRxPduCnt;           /*���յ�PDU����*/
    VOS_UINT32      ulDlTxSduCnt;           /*���͵�SDU����*/
    VOS_UINT32      ulDlDiscPduCnt;         /*�����򴰿��ⶪ��ͳ��*/
    VOS_UINT32      ulDlDupPduCnt;          /*�ظ�����PDUͳ��*/
    VOS_UINT32      ulDlRxCtlPduCnt;        /*���տ���PDUͳ��*/
    VOS_UINT32      ulDlTxStrpPduCnt;       /*����״̬����PDUͳ��*/
    VOS_UINT32      ulDlTxRohcPduCnt;       /*����ROHC����PDUͳ��*/
    VOS_UINT32      ulDlErrPduRlcIndCnt;    /*RLC����ָʾPDU����ͳ��*/
    VOS_UINT32      ulDlExcepFreePduCnt;    /*�쳣�ͷ�PDUͳ��*/
    VOS_UINT32      ulDlReestStopLastSubmitSn;
    VOS_UINT32      ulDlReestStopNextRxSn;
    VOS_UINT32      ulDlReestContLastSubmitSn;
    VOS_UINT32      ulDlReestContHfn;
    VOS_UINT32      ulDlReestStopHfn;
    VOS_UINT32      ulDlReestContNextRxSn;
    VOS_UINT32      ulDlReestContFirstRxSn;

    VOS_UINT32      ulDlExecReordCnt;        /*����ʵ�彨��������������ִ�д���*/
    VOS_UINT32      ulDlCipherBufFullCnt;       /*����CIPEHR���buf����*/
    VOS_UINT32      ulDlAmRlcDataErrCnt;
    VOS_UINT32      ulDlRlcDataErrCnt;

    VOS_UINT32      ulDlUnCompFailCnt;      /*SDU��ѹ��ʧ������*/
    VOS_UINT32      ulHoUnCompFailCnt;      /*�л���ѹ��ʧ������*/
    VOS_UINT32      ulDeCompSuccCnt;        /*��ѹ���ɹ�����*/
    VOS_UINT32      ulDeCompFailCnt;        /*��ѹ��ʧ�ܴ���*/
    VOS_UINT32      ulRohcDeCompCnt;        /*��ѹ���������*/

}LTE_ERRLOG_PDCP_DL_DT_RBID_STAT_STRU;

/*****************************************************************************
 �ṹ��    : LPDCP_UL_SECU_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PDCP��ȫ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          enCipherAlg;
    VOS_UINT32                          enIntegrityProtAlg;
    VOS_UINT8                           ucSrbCiphKeyIndex;
    VOS_UINT8                           ucDrbCiphKeyIndex;
    VOS_UINT8                           ucIntegrityKeyIndex;
    VOS_UINT8                           aucRev;
}LTE_ERRLOG_PDCP_SECU_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_PDCP_FAIL_STRU
 �ṹ˵��  : PDCP ������Ϣ�ϱ�����
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_PDCP_UL_ENTITY_STRU    stPdcpUlEntity;
    LTE_ERRLOG_PDCP_DL_ENTITY_STRU    stPdcpDlEntity;
    LTE_ERRLOG_PDCP_UL_DT_RBID_STAT_STRU      stUlDtRbidStat;
    LTE_ERRLOG_PDCP_DL_DT_RBID_STAT_STRU      stDlDtRbidStat;
    LTE_ERRLOG_PDCP_SECU_INFO_STRU    stSecuInfo;

}LTE_PDCP_FAIL_STRU;

/*****************************************************************************
 �ṹ��    : LTE_RLC_FAIL_STRU
 �ṹ˵��  : RLC������Ϣ�ϱ�����
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_RLC_RX_ENTITY_STRU     stRlcRxEntity;
    LTE_ERRLOG_RLC_TX_ENTITY_STRU     stRlcTxEntity;
    LTE_ERRLOG_RLC_UL_STAT_INFO_STRU  stRlcULStatInfo;
    LTE_ERRLOG_RLC_DL_STAT_INFO_STRU  stRlcDLStatInfo;
    
}LTE_RLC_FAIL_STRU;

/*****************************************************************************
 �ṹ��    : LTE_MAC_FAIL_STRU
 �ṹ˵��  : MAC������Ϣ�ϱ�����
*****************************************************************************/
typedef struct
{
    LTE_ERRLOG_MAC_ENTITY_STRU  stMacEnt;
    LTE_ERRLOG_MAC_DEBUG_UL_STAT_INFO_STRU  stMacULStat;
    LTE_ERRLOG_MAC_DEBUG_DL_STAT_INFO_STRU  stMacDLStat;
    LTE_ERRLOG_MAC_DEBUG_RA_INFO_STRU  stMacRaStat;
    
}LTE_MAC_FAIL_STRU;

/*****************************************************************************
 �ṹ��    : LTE_L2_ERRLOG_INFO_STRU
 �ṹ˵��  : ERROR LOG �������ݽṹ
*****************************************************************************/
typedef struct
{
    TL_L2_ERRLOG_ALMLEVEL_ENUM_UINT16    almLevel;
    TL_L2_ERROR_CODE_ENUM_UINT8          errorCode;
    TL_L2_ERRLOG_MODULE_TYPE_UINT8       moduleType;
    
    union
    {
        LTE_PDCP_FAIL_STRU                   stPdcpFailInfo;
        LTE_RLC_FAIL_STRU                    stRlcFailInfo;
        LTE_MAC_FAIL_STRU                    stMacFailInfo;
    }u;
    
}LTE_L2_ERRLOG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_L2_OM_ERRLOG_INFO_STRU
 �ṹ˵��  : ERROR LOG ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                        ulMsgModuleID;    /* ��ģ��ID */
    VOS_UINT16                        usModemId;         /* 00������, 01������ ,10/11:����  */
    VOS_UINT16                        usALMID;             /*  sub sys,modeule,sub module   �ݲ�ʹ��   */
    VOS_UINT16                        usALMLevel;         /*�ϱ�����; Warning:0x04; Minor:0x03; Major:0x02;  Critical:0x01; */
    VOS_UINT16                        usALMType;         /* ����&�澯����; ͨ��:0x00; ҵ������:0x01; �������:0x02; �豸����:0x03; ��������:0x04;*/
    VOS_UINT32                        usAlmLowSlice;     /*ʱ���*/
    VOS_UINT32                        usAlmHighSlice;
    VOS_UINT32                        ulAlmLength;
    LTE_L2_ERRLOG_INFO_STRU           stAlmInfo;
}LTE_L2_OM_ERRLOG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_L2_OM_ERRLOG_REPORT_STRU
 �ṹ˵��  : errorlog��Ϣ�ϱ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgName;
    VOS_UINT32                              ulMsgType;
    VOS_UINT32                              ulMsgSN;
    VOS_UINT32                              ulRptlen;             /* �������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    LTE_L2_OM_ERRLOG_INFO_STRU              stErrLogInfo;
}LTE_L2_OM_ERRLOG_REPORT_STRU;

typedef struct
{
  VOS_UINT16       frequency;
  VOS_UINT8        syncId;
  VOS_UINT8        basicMidamble;
}TDS_ERRLOG_CellDesc;

typedef struct
{
  VOS_UINT8                      timeslot;
  VOS_UINT16                     chanCodes;/*bitmap:sf=16*/
  VOS_UINT8                      midambleAllocationMode;/*midambleShift is useless if defaultMidamble,*/
                                                 /*commonMidamble*/
  VOS_UINT8                      midambleShift;
  VOS_UINT8                      midambleConfiguration;
  VOS_UINT8                      wi;
}TDS_ERRLOG_FpachInfo;


typedef struct
{
  TDS_ERRLOG_CellDesc            cellDesc;
  TDS_ERRLOG_FpachInfo           fpachInfo;
  VOS_UINT8                      syncUlCode;
  VOS_UINT8                      prxUppchDes;
  VOS_UINT8                      pathLoss;
  VOS_UINT8                      powerRampStep;
  VOS_UINT8                      maxSync;
  VOS_UINT32                     uRnti;
  VOS_UINT32                     cRnti;
  VOS_UINT8                      syncNeeded;
  VOS_UINT8                      n313;
  VOS_UINT16                     n312;
  VOS_UINT16                     n315;
  VOS_UINT8                      t312;
  VOS_UINT8                      t313;
  VOS_UINT8                      rbNum;
  VOS_UINT8                      rabNum;
  VOS_UINT8                      trchNum;
  VOS_UINT8                      harqInfo;
  VOS_UINT8                      eDchMacdFlowNum;
}TDS_ERRLOG_CMAC_DCH_CONFIG_REQ;

typedef struct
{
  VOS_UINT8                          sccpchId;
  VOS_UINT8                          trchNum;
  VOS_UINT8                          tfcNum;
  VOS_UINT16                         channelisationCode;
}TDS_ERRLOG_SccpchInfo;

typedef struct
{
  VOS_UINT16                     usOpId;
  VOS_UINT32                     uRnti;
  VOS_UINT32                     cRnti;
  VOS_UINT8                      rbNum;
  VOS_UINT8                      ascNum;
  TDS_ERRLOG_SccpchInfo   sccpchInfo;
  VOS_UINT8                      fachMeasOccasionCoeff;
  VOS_UINT8                      measNum;
  VOS_INT16                     framNumDiff;
  VOS_UINT8                      cellUpdate;
  VOS_UINT8                      barredAndIntraNotAllowedNum;
}TDS_ERRLOG_CMAC_FCH_CONFIG_REQ;

typedef struct
{
  VOS_UINT8                      measNum;/*no BA ��0*/
  TDS_ERRLOG_CellDesc            cellList[TDS_ERRLOG_MAX_FAR_CELL_NUM];
  VOS_UINT8                      icsType;/*sel ��0��res ��1��only measurement��2    7:search plmn*/
  VOS_UINT8                      rrcMode;/*idle mode: 0; connected mode:1*/
  VOS_UINT8                      syncStatus; /*20090409*/
  VOS_UINT8                      dmPara;/*suspend TDD meas :0; deactive L1G :1; 3G to 2G fail, return 3G;  20090928  PDM100 UMAC*/
}TDS_ERRLOG_CMAC_FIND_BCH_REQ;

typedef struct
{
  TDS_ERRLOG_CellDesc            cellDesc;
  VOS_INT16                      framNumDiff;
  VOS_UINT8                      scanRlcFlag;/*not need scan rlc when entering FCH state:0;need scan rlc:1*/
  VOS_UINT8                      maxAllowedUlTxPower;
  VOS_UINT8                      syncUlCode;/*bitmap*/
  VOS_UINT8                      prxUppchDes;
  VOS_UINT8                      pathLoss;
  VOS_UINT8                      powerRampStep;
  VOS_UINT8                      maxSync;/*MAX_SYNC_NUM_UL_Transmissions*/
  VOS_UINT8                      mmax;
  VOS_UINT8                      dynamicPersLevel;/*N for P(N)��2^-(N-1)*/
  VOS_UINT8                      ascNum;
}TDS_ERRLOG_CMAC_RANDOM_ACC_REQ;


/*****************************************************************************
 �ṹ��    : TDS_MAC_FAIL_STRU
 �ṹ˵��  : MAC������Ϣ�ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                        stMacCurrentState;
    TDS_ERRLOG_CMAC_DCH_CONFIG_REQ    stMacDchConfigInfo;
    TDS_ERRLOG_CMAC_FCH_CONFIG_REQ    stMacFchConfigInfo;
    TDS_ERRLOG_CMAC_FIND_BCH_REQ      stMacBchInfo;
    TDS_ERRLOG_CMAC_RANDOM_ACC_REQ    stMacRAInfo;
    
}TDS_MAC_FAIL_STRU;

typedef struct
{
  VOS_UINT8                        rbIdentity;
  VOS_UINT8                        upMode;
  VOS_UINT8                        dwMode;
  VOS_UINT8                        ctrlOrUsr;
  VOS_UINT16                       currentState;
}TDS_ERRLOG_RLC_TmUmInfo;

typedef struct
{
  VOS_UINT16                       pduSize;
  VOS_UINT8                        transmissionRlcDiscardChoice;
  VOS_UINT16                       timerDiscard;
  VOS_UINT8                        maxMrw;
  VOS_UINT16                       timerMrw;
  VOS_UINT8                        maxDat;
  VOS_UINT16                       transmissionWindowSize;
  VOS_UINT16                       timerRst;
  VOS_UINT8                        maxRst;
  VOS_UINT8                        PollingInfoPresent;      /*0: no pollingInfo; 1: have pollingInfo*/
  VOS_UINT16                       timerPollProhibit;       /*optional, 0xff indicate  don't usel*/
  VOS_UINT16                       timerPoll;               /*optional, 0xff indicate  don't usel*/
  VOS_UINT8                        pollPdu;                 /*optional, 0xff indicate  don't usel*/
  VOS_UINT8                        pollSdu;                 /*optional, 0xff indicate  don't usel*/
  VOS_UINT8                        lastTransmissionPduPoll;
  VOS_UINT8                        lastRetransmissionPduPoll;
  VOS_UINT8                        pollWindow;              /*optional, 0xff indicate  don't usel*/
  VOS_UINT8                        timerPollPeriodic;       /*optional, 0xff indicate  don't usel*/
 }TDS_ERRLOG_SaveUpAmParas;

typedef struct
{
  VOS_UINT16                       pduSize;/*20060710*/
  VOS_UINT8                        inSequenceDelivery;      /* 0:unSequenceDelivery 1:inSequenceDelivery*/
  VOS_UINT16                       receivingWindowSize;
  VOS_UINT16                       timerStatusProhibit;     /*optional, 0xff indicate timer don't use*/
  VOS_UINT8                        missingPduIndicator;
  VOS_UINT8                        timerStatusPeriodic;     /*optional, 0xff indicate timer don't use*/
 }TDS_ERRLOG_SaveAmDwParas;

typedef struct
{
  VOS_UINT8                        rbIdentity;
  VOS_UINT8                        ctrlOrUsr;
  VOS_UINT16                       currentState;
  VOS_UINT16                       previousState;
  TDS_ERRLOG_SaveUpAmParas           upParas;
  TDS_ERRLOG_SaveAmDwParas           dwParas;
}TDS_ERRLOG_RLC_AmInfo;


/*****************************************************************************
 �ṹ��    : TDS_RLC_FAIL_STRU
 �ṹ˵��  : RLC������Ϣ�ϱ�����
*****************************************************************************/
typedef struct
{

    TDS_ERRLOG_RLC_TmUmInfo     stRlcTmUmInst;
    TDS_ERRLOG_RLC_AmInfo       stRlcAmInst;
}TDS_RLC_FAIL_STRU;

/*****************************************************************************
 �ṹ��    : TDS_PDCP_FAIL_STRU
 �ṹ˵��  : pdcp������Ϣ�ϱ�����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  usRev;
}TDS_PDCP_FAIL_STRU;


/*****************************************************************************
 �ṹ��    : TDS_L2_ERRLOG_INFO_STRU
 �ṹ˵��  : ERROR LOG �������ݽṹ
*****************************************************************************/
typedef struct
{
    TL_L2_ERRLOG_ALMLEVEL_ENUM_UINT16    almLevel;
    TL_L2_ERROR_CODE_ENUM_UINT8          errorCode;
    TL_L2_ERRLOG_MODULE_TYPE_UINT8       moduleType;
    
    union
    {
        TDS_PDCP_FAIL_STRU                   stPdcpFailInfo;
        TDS_RLC_FAIL_STRU                    stRlcFailInfo;
        TDS_MAC_FAIL_STRU                    stMacFailInfo;
    }u;
    
}TDS_L2_ERRLOG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TDS_L2_OM_ERRLOG_INFO_STRU
 �ṹ˵��  : ERROR LOG ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                        ulMsgModuleID;    /* ��ģ��ID */
    VOS_UINT16                        usModemId;         /* 00������, 01������ ,10/11:����  */
    VOS_UINT16                        usALMID;             /*  sub sys,modeule,sub module   �ݲ�ʹ��   */
    VOS_UINT16                        usALMLevel;         /*�ϱ�����; Warning:0x04; Minor:0x03; Major:0x02;  Critical:0x01; */
    VOS_UINT16                        usALMType;         /* ����&�澯����; ͨ��:0x00; ҵ������:0x01; �������:0x02; �豸����:0x03; ��������:0x04;*/
    VOS_UINT32                        usAlmLowSlice;     /*ʱ���*/
    VOS_UINT32                        usAlmHighSlice;
    VOS_UINT32                        ulAlmLength;
    TDS_L2_ERRLOG_INFO_STRU           stAlmInfo;
}TDS_L2_OM_ERRLOG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TDS_L2_OM_ERRLOG_REPORT_STRU
 �ṹ˵��  : errorlog��Ϣ�ϱ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgName;
    VOS_UINT32                              ulMsgType;
    VOS_UINT32                              ulMsgSN;
    VOS_UINT32                              ulRptlen;             /* �������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    TDS_L2_OM_ERRLOG_INFO_STRU              stErrLogInfo;
}TDS_L2_OM_ERRLOG_REPORT_STRU;


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

#endif /* end of TLL2Errorlog.h */
