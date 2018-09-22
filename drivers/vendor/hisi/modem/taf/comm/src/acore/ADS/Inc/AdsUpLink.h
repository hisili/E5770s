

#ifndef __ADSUPLINK_H__
#define __ADSUPLINK_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AdsCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ��ȡIPF UL BDΪ0�Ĵ��� */
#define ADS_UL_GET_EMPTY_BD_COUNT       (10)

/* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */

/* ����BD��user field 1,�ڶ����ֽ�ΪModem id,��һ���ֽڵĸ�4λΪPktTpye,��һ���ֽڵĵ�4λΪRabId */
#define ADS_UL_BUILD_BD_USER_FIELD_1(InstanceIndex, RabId) \
        (((((VOS_UINT16)InstanceIndex) << 8) & 0xFF00) | ((ADS_UL_GET_QUEUE_PKT_TYPE(InstanceIndex, RabId) << 4) & 0xF0) | (RabId & 0x0F))

/* ��������ţ�Modem0��0��MODEM1��1��ʵ������ͬ */
#define ADS_UL_GET_BD_FC_HEAD(InstanceIndex)          (InstanceIndex)

/* ����������Ϣ:
           bit0:   int_en  �ж�ʹ��
           bit2:1  mode    ģʽ����
           bit3    rsv
           bit6:4  fc_head ��������� mfc_en������Ϊ1ʱ����Ч
           bit15:7 rsv */
#define ADS_UL_BUILD_BD_ATTRIBUTE(Flag, Mode, FcHead) ((Flag & 0x000F) | (Mode << 1 & 0x0006) | (FcHead << 4 &0x0070))

#define ADS_UL_SET_BD_ATTR_INT_FLAG(usAttr)            ((usAttr) = (usAttr) | 0x1)

/* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID ADS_UL_ConfigBD(VOS_UINT32 ulBdNum);
/* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
IMM_ZC_STRU* ADS_UL_GetInstanceNextQueueNode(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                          *pucRabId
);
IMM_ZC_STRU* ADS_UL_GetNextQueueNode(
    VOS_UINT8                          *pucRabId,
    VOS_UINT8                          *pucInstanceIndex
);
/* Modified by l60609 for DSDA Phase II, 2012-11-24, End */
VOS_VOID ADS_UL_ProcLinkData(VOS_VOID);
VOS_VOID ADS_UL_ProcMsg(MsgBlock* pMsg);
VOS_UINT32 ADS_UL_RcvTafMsg(MsgBlock *pMsg);
VOS_UINT32 ADS_UL_RcvTafPdpStatusInd(MsgBlock *pMsg);
VOS_UINT32 ADS_UL_ProcPdpStatusInd(
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL) /*add parameter Cid when BIP*/
    VOS_UINT8                                              ucCid,
#endif
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    ADS_PDP_STATUS_ENUM_UINT8           enPdpStatus,
    ADS_QCI_TYPE_ENUM_UINT8             enQciType,
    ADS_PDP_TYPE_ENUM_UINT8             enPdpType
);
VOS_UINT32 ADS_UL_RcvCdsClearDataInd(MsgBlock *pMsg);
VOS_UINT32 ADS_UL_RcvCdsIpPacketMsg(MsgBlock *pMsg);
VOS_UINT32 ADS_UL_RcvCdsMsg(MsgBlock *pMsg);
VOS_UINT32 ADS_UL_RcvCdsStartSendDataInd(MsgBlock *pMsg);
VOS_UINT32 ADS_UL_RcvCdsStopSendDataInd(MsgBlock *pMsg);
VOS_UINT32 ADS_UL_RcvTimerMsg(MsgBlock *pMsg);
VOS_VOID ADS_UL_SendCdsClearDataRsp(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_SendCdsStartSendDataRsp(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_SendCdsStopSendDataRsp(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_SendPacket(
    IMM_ZC_STRU                        *pstData,
    VOS_UINT8                           ucRabId
);
/* Added by l60609 for AP������Ŀ ��2012-08-30 Begin */
#if(FEATURE_OFF == FEATURE_SKB_EXP)
VOS_VOID ADS_UL_SaveIpfUlSrcMem(IMM_ZC_STRU *pstImmZcNode);
VOS_VOID ADS_UL_FreeIpfUlConfigSuccSrcMem(VOS_VOID);
VOS_VOID ADS_UL_FreeIpfUlConfigFailSrcMem(VOS_UINT32 ucNeedFreeCnt);
VOS_VOID ADS_UL_ClearIpfUlSrcMem(VOS_VOID);
/* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
VOS_VOID ADS_UL_SetMaxQueueLength(
    VOS_UINT32                          ulLength,
    VOS_UINT8                           ucInstanceIndex
);
/* Modified by l60609 for DSDA Phase II, 2012-11-24, End */
#endif
/* Added by l60609 for AP������Ŀ ��2012-08-30 End */

VOS_UINT32 ADS_UL_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
);

VOS_VOID ADS_UL_RcvTiDsFlowStatsExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
);

VOS_VOID ADS_UL_StartDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
);

VOS_VOID ADS_UL_StopDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_StartRptStatsInfoTimer(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_StopRptStatsInfoTimer(VOS_VOID);
VOS_VOID ADS_UL_RcvTiRptStatsInfoExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
);


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

#endif /* end of AdsUlProcData.h */
