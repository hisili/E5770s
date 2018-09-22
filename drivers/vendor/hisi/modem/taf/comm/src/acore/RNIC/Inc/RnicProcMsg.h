

#ifndef __RNIC_PROCMSG_H__
#define __RNIC_PROCMSG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AtRnicInterface.h"
#include "PsCommonDef.h"
#include "RnicLinuxInterface.h"
#include "v_msg.h"
#include "RnicTimerMgmt.h"

#include "RnicConfigInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum RNIC_DAIL_EVENT_TYPE_ENUM
{
    RNIC_DAIL_EVENT_UP                  = 0x0600,                               /*��Ҫ��������*/
    RNIC_DAIL_EVENT_DOWN                        ,                               /*��Ҫ�Ͽ����� */

    RNIC_DAIL_EVENT_TYPE_BUTT
};
typedef VOS_UINT32 RNIC_DAIL_EVENT_TYPE_ENUM_UINT32;


enum AT_RNIC_DIAL_MODE_ENUM
{
    AT_RNIC_DIAL_MODE_MANUAL,                                                   /*Manual dial mode*/
    AT_RNIC_DIAL_MODE_DEMAND_CONNECT,                                           /*Demand dial mode*/
    AT_RNIC_DIAL_MODE_DEMAND_DISCONNECT,                                        /*Demand dial mode*/
    AT_RNIC_DIAL_MODE_BUTT
};
typedef VOS_UINT32 AT_RNIC_DIAL_MODE_ENUM_UINT32;


enum RNIC_DIAL_EVENT_REPORT_FLAG_ENUM
{
    RNIC_FORBID_EVENT_REPORT            = 0x0000,                               /*����Ӧ���ϱ�*/
    RNIC_ALLOW_EVENT_REPORT             = 0X0001,                               /*�����Ӧ���ϱ�*/

    RNIC_DIAL_EVENT_REPORT_FLAG_BUTT
};
typedef VOS_UINT32 RNIC_DIAL_EVENT_REPORT_FLAG_ENUM_UINT32;

#if 0

enum RNIC_MNTN_EVT_TYPE_ENUM
{
    ID_RNIC_MNTN_EVT_DIAL_CONNECT       = 0x6001,                               /* _H2ASN_MsgChoice RNIC_MNTN_DIAL_CONN_EVT_STRU */
    ID_RNIC_MNTN_EVT_DIAL_DISCONNECT    = 0x6002,                               /* _H2ASN_MsgChoice RNIC_MNTN_DIAL_DISCONN_EVT_STRU */
};
typedef VOS_UINT32 RNIC_MNTN_EVT_TYPE_ENUM_UINT32;
#endif


enum RNIC_MSG_ID_ENUM
{
    ID_RNIC_RMNET_CONFIG_REQ            = 0x0000,                               /* _H2ASN_MsgChoice RNIC_RMNET_CONFIG_REQ_STRU */

    ID_RNIC_CCPU_RESET_START_IND        = 0x1001,                               /* _H2ASN_MsgChoice RNIC_CCPU_RESET_IND_STRU */
    ID_RNIC_CCPU_RESET_END_IND          = 0x1002,                               /* _H2ASN_MsgChoice RNIC_CCPU_RESET_IND_STRU */

    /* ��ν�ɲ���ϢID */
    ID_RNIC_MNTN_EVT_DIAL_CONNECT       = 0x6001,                               /* _H2ASN_MsgChoice RNIC_MNTN_DIAL_CONN_EVT_STRU */
    ID_RNIC_MNTN_EVT_DIAL_DISCONNECT    = 0x6002,                               /* _H2ASN_MsgChoice RNIC_MNTN_DIAL_DISCONN_EVT_STRU */

    /* ����ģʽ��Ϣ ���貦��*/
    ID_RNIC_MNTN_DIAL_MODE_INFO         = 0x6003,                               /* _H2ASN_MsgChoice RNIC_NOTIFY_MSG_STRU */

    /* ����ʱ����Ϣ ���貦��*/
    ID_RNIC_MNTN_IDLE_TIMEOUT_INFO      = 0x6004,                               /* _H2ASN_MsgChoice RNIC_NOTIFY_MSG_STRU */

    /* �Ƿ��ϱ��¼� ���貦��*/
    ID_RNIC_MNTN_EVENT_REPORT_INFO      = 0x6005,                               /* _H2ASN_MsgChoice RNIC_NOTIFY_MSG_STRU */

    /* �ⲿģ������RNIC��������Ϣ */
    ID_RNIC_MNTN_RMNET_CONFIG_INFO      = 0x6006,                               /* _H2ASN_MsgChoice RNIC_RMNET_CONFIG_REQ_STRU */

    ID_RNIC_RNIC_MSG_ID_BUTT
};

typedef VOS_UINT32 RNIC_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/* ��ʱ����ʱ������ָ��*/
typedef VOS_UINT32 (*RNIC_RCV_TI_EXPRIED_PROC_FUNC)(
    MsgBlock                           *pstMsg,
    VOS_UINT8                           ucRmNetId
);

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    AT_RNIC_DIAL_MODE_ENUM_UINT32                           enDialMode;         /* Dialģʽ */
    VOS_UINT32                                              ulIdleTime;        /* ��ʱ�����ȣ���λΪ�� */
    RNIC_DIAL_EVENT_REPORT_FLAG_ENUM_UINT32                 enEventReportFlag;  /*�Ƿ��Ӧ���ϱ���ʶ*/
}RNIC_DIAL_MODE_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */        /*_H2ASN_Skip*/
    RNIC_MSG_ID_ENUM_UINT32             enMsgId;                                /*��Ϣ����*/        /*_H2ASN_Skip*/
    RNIC_DIAL_MODE_STRU                 stDialInfo;                             /*���貦����������*/
}RNIC_NOTIFY_MSG_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    RNIC_MSG_ID_ENUM_UINT32             enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
} RNIC_MNTN_DIAL_CONN_EVT_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    RNIC_MSG_ID_ENUM_UINT32             enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
    VOS_UINT32                          ulPktNum;
    VOS_UINT32                          ulUsrExistFlg;
} RNIC_MNTN_DIAL_DISCONN_EVT_STRU;


typedef struct
{
    VOS_UINT32                          ulMsgId;
    RNIC_RCV_TI_EXPRIED_PROC_FUNC       pTiExpriedProcFunc;
}RNIC_RCV_TI_EXPRIED_PROC_STRU;


/* Modified by l60609 for L-C��������Ŀ, 2014-01-06, Begin */

typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    RNIC_MSG_ID_ENUM_UINT32             enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */

    RNIC_MODEM_TYPE_ENUM_UINT8          enModemType;
    VOS_UINT8                           ucRmNetId;
    VOS_UINT16                          usModemId;
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           ucRabId;
    RNIC_RMNET_STATUS_ENUM_UINT8        enRmnetStatus;
    RNIC_IP_TYPE_ENUM_UINT8             enIpType;
}RNIC_RMNET_CONFIG_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /* ��Ϣͷ */    /* _H2ASN_Skip */
    RNIC_MSG_ID_ENUM_UINT32             enMsgId;                                /* ��ϢID */    /* _H2ASN_Skip */
}RNIC_CCPU_RESET_IND_STRU;
/* Modified by l60609 for L-C��������Ŀ, 2014-01-06, End */

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 RNIC_SendDialEvent(
    VOS_UINT32                          ulDeviceId,
    VOS_UINT32                          ulEventId
);
VOS_UINT32 RNIC_RcvAtIpv4PdpActInd(
    MsgBlock                           *pstMsg
);
VOS_UINT32 RNIC_RcvAtIpv6PdpActInd(
    MsgBlock                           *pstMsg
);
VOS_UINT32 RNIC_RcvAtPdpDeactInd(
    MsgBlock                           *pstMsg
);
VOS_UINT32 RNIC_RcvAtDsflowInd(
    MsgBlock                           *pstMsg
);
VOS_UINT32  RNIC_RcvTiDsflowStatsExpired(
    MsgBlock                           *pstMsg,
    VOS_UINT8                           ucRmNetId
);
VOS_UINT32 RNIC_RcvTiDemandDialDisconnectExpired(
    MsgBlock                           *pstMsg,
    VOS_UINT8                           ucRmNetId
);
VOS_UINT32 RNIC_RcvTiDemandDialProtectExpired(
    MsgBlock                           *pstMsg,
    VOS_UINT8                           ucRmNetId
);
VOS_UINT32 RNIC_RcvTimerMsg(MsgBlock *pstMsg);
VOS_UINT32 RNIC_RcvAtMsg(MsgBlock *pstMsg);
VOS_UINT32 RNIC_ProcMsg (MsgBlock *pstMsg);
VOS_UINT32 RNIC_SendDialInfoMsg(
    RNIC_MSG_ID_ENUM_UINT32                enMsgId
);
VOS_VOID RNIC_MNTN_TraceDialConnEvt(VOS_VOID);
VOS_VOID RNIC_MNTN_TraceDialDisconnEvt(
    VOS_UINT32                          ulPktNum,
    VOS_UINT32                          ulUsrExistFlg
);

VOS_UINT32 RNIC_RcvAtIpv4v6PdpActInd(
    MsgBlock                           *pstMsg
);
RNIC_TIMER_ID_ENUM_UINT16 RNIC_GetDsflowTimerIdByNetId(VOS_UINT8 ucRmNetId);
VOS_UINT32 RNIC_SaveNetIdByRabId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucRmNetId
);
VOS_UINT32 RNIC_BuildRabIdByModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                          *pucRabId
);
VOS_UINT32 RNIC_RcvAtMtuChangeInd(
    MsgBlock                           *pstMsg
);
VOS_UINT8 RNIC_GetNetIdByTimerId(VOS_UINT32 ulMsgId);

/* Added by L47619 for V3R3 Share-PDP Project, 2013-6-3, begin */
VOS_UINT32 RNIC_RcvAtPdnInfoCfgInd(
    MsgBlock                           *pstMsg
);
VOS_UINT32 RNIC_RcvAtPdnInfoRelInd(
    MsgBlock                           *pstMsg
);
/* Added by L47619 for V3R3 Share-PDP Project, 2013-6-3, end */

VOS_VOID RNIC_ProcInsideModemIpv4ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
);

VOS_VOID RNIC_ProcInsideModemIpv6ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
);

VOS_VOID RNIC_ProcRnicPdpActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
VOS_UINT32 RNIC_SaveNetIdByPdnId(
    VOS_UINT8                           ucPdnId,
    VOS_UINT8                           ucRmNetId
);

VOS_VOID RNIC_ProcOutsideModemIpv4ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
);

VOS_VOID RNIC_ProcOutsideModemIpv6ActInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
);

VOS_VOID RNIC_ProcRnicPdpHandoverInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
);
#endif

VOS_VOID RNIC_ProcRnicPdpDeactInd(
    RNIC_RMNET_CONFIG_REQ_STRU           *pstPdpStatusInd
);

VOS_UINT32 RNIC_RcvRnicRmnetConfigReq(
    MsgBlock                           *pstMsg
);

VOS_UINT32 RNIC_SndRnicRmnetConfigReq(
    RNIC_RMNET_CONFIG_STRU              *pstConfigInfo
);

VOS_VOID RNIC_MNTN_SndRmnetConfigInfoMsg(
    RNIC_RMNET_CONFIG_STRU             *pstConfigInfo
);


VOS_UINT32 RNIC_RcvRnicMsg(MsgBlock *pstMsg);
#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 RNIC_RcvImsaMsg(MsgBlock *pstMsg);
VOS_UINT32 RNIC_RcvImsaPdnActInd(
    MsgBlock                           *pstMsg
);
VOS_UINT32 RNIC_RcvImsaPdnDeactInd(
    MsgBlock                           *pstMsg
);
#endif


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

#endif /* end of RnicProcMsg.h */
