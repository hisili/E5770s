
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "omappoperator.h"
#include "OmApp.h"
#include "OmAppRl.h"
#include "omprintf.h"

#if(FEATURE_ON == FEATURE_SOCP_ON_DEMAND)
#include "msp_diag.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*lint -e767 �޸���:���� 47350;ԭ��:Log��ӡ */
#define    THIS_FILE_ID        PS_FILE_ID_ACPU_OMOPERATOR_C
/*lint +e767 �޸���:���� 47350;*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if(FEATURE_ON == FEATURE_SOCP_ON_DEMAND)
OM_SOCPVOTE_INFO_STRU       g_astOmAcpuSocpVoteInfo[OM_SOCPVOTE_INFO_BUTT]= {0};
#endif

#if (FEATURE_ON == FEATURE_CBT_LOG)
extern VOS_UINT32                     g_ulCBTLogEnable;
#endif

/*****************************************************************************
  3 ��������
*****************************************************************************/

VOS_UINT32 OM_AcpuEstablishReq(APP_OM_MSG_EX_STRU *pstAppToOmMsg,
                                           VOS_UINT16 usReturnPrimId)
{
    VOS_UINT32                          ulRet;
#if (FEATURE_ON == FEATURE_CBT_LOG)    
    VOS_UINT32                          ulState;

    ulState = g_ulAcpuOMSwitchOnOff;
#endif

    VOS_MemSet(&g_stAcpuTraceEventConfig, 0, sizeof(OM_TRACE_EVENT_CONFIG_PS_STRU));
    VOS_MemSet(g_astOmPrintfOutPutLev, 0, OM_PRINTF_MODULE_MAX_NUM*sizeof(LOG_LEVEL_EN));
    VOS_MemSet(g_aulLogPrintLevPsTable, 0, LOG_PS_MODULE_MAX_NUM*sizeof(LOG_LEVEL_EN));
    VOS_MemSet(g_aulLogPrintLevDrvTable, 0, LOG_DRV_MODULE_MAX_NUM*sizeof(LOG_LEVEL_EN));

    /* �ȶϿ���· */
    g_ulAcpuOMSwitchOnOff = OM_STATE_IDLE;

#if(FEATURE_ON == FEATURE_SOCP_ON_DEMAND)
    OM_AcpuSocpVoteInfoAdd(OM_SOCPVOTE_CALLBEGIN);
    DRV_SOCP_VOTE(SOCP_VOTE_GU_OM_APP, SOCP_VOTE_FOR_WAKE);
    OM_AcpuSocpVoteInfoAdd(OM_SOCPVOTE_CALLEND);
#endif

    /* �Լ���У׼���ߣ������ɹ��ظ�״̬��0x02 */
    ulRet = 0x02;

    /* �����߻ظ������ɹ�״̬ */
    OM_AcpuSendResult(OM_QUERY_FUNC, ulRet, usReturnPrimId);

    /* ������· */
    g_ulAcpuOMSwitchOnOff = OM_STATE_ACTIVE;

#if (FEATURE_ON == FEATURE_CBT_LOG)
    if ((OM_STATE_ACTIVE == ulState) && (OM_CBT_LOG_ENABLE_FLAG == g_ulCBTLogEnable))
    {
        return VOS_OK;
    }
#endif

    /* ֪ͨCCPU��·״̬ */
    if(VOS_OK != GU_OamSndPcMsgToCcpu((VOS_UINT8*)pstAppToOmMsg, sizeof(APP_OM_MSG_EX_STRU)))
    {
        /* ��ӡ���� */
        LogPrint("OM_AcpuEstablishReq: The ICC UDI Write is Error.\n");
    }

    return VOS_OK;
}


VOS_VOID OM_NotifyOtherCpuReleaseLink(VOS_VOID)
{
    VOS_UINT32                          ulMsgId;

    ulMsgId                     = APP_OM_RELEASE_REQ;

    /* Ŀǰ���������ͨ�Ż������⣬��˳��˸�CCPU�������˲����Ͷ�����Ϣ������A�˻Ḵλ begin */
    /* ��HIFI֪ͨ��·�Ͽ���Ϣ */
    OMRL_AcpuSendMsg((VOS_UINT8*)&ulMsgId, sizeof(VOS_UINT32), ACPU_PID_OM, DSP_PID_HIFI_OM);

    /* ��MCU֪ͨ��·�Ͽ���Ϣ */
    /* OMRL_AcpuSendMsg((VOS_UINT8*)&ulMsgId, sizeof(VOS_UINT32), ACPU_PID_OM, ACPU_PID_MCU_OM); */
    /* Ŀǰ���������ͨ�Ż������⣬��˳��˸�CCPU�������˲����Ͷ�����Ϣ������A�˻Ḵλ end */
    return;
}

VOS_UINT32 OM_AcpuReleaseReq(APP_OM_MSG_EX_STRU *pstAppToOmMsg,
                                           VOS_UINT16 usReturnPrimId)
{

#if (FEATURE_ON == FEATURE_CBT_LOG)
    if (OM_CBT_LOG_ENABLE_FLAG == g_ulCBTLogEnable)
    {
        return VOS_OK;
    }
#endif

    g_ulAcpuOMSwitchOnOff       = OM_STATE_IDLE;

    /* ͨ��ICCͨ��֪ͨCCPU��·�Ͽ� */
    if(VOS_OK != GU_OamSndPcMsgToCcpu((VOS_UINT8*)pstAppToOmMsg, sizeof(APP_OM_MSG_EX_STRU)))
    {
        /* ��ӡ���� */
        LogPrint("OM_AcpuReleaseReq: The ICC UDI Write is Error.\n");
    }

    OM_NotifyOtherCpuReleaseLink();

    g_stAcpuPcToUeSucRecord.stRlsData.ulDataLen = OM_GetSlice();
    g_stAcpuPcToUeSucRecord.stRlsData.ulNum++;

    OM_SendAcpuSocpVote(SOCP_VOTE_FOR_SLEEP);

    return VOS_OK;
}

/*****************************************************************************
  4 ��Ϣ������ӳ���
*****************************************************************************/
/*Global map table used to find the function according the PrimId.*/
OM_MSG_FUN_STRU g_astAcpuOmMsgFunTbl[] =
{
    {APP_OM_ESTABLISH_REQ,              OM_AcpuEstablishReq,              OM_APP_ESTABLISH_CNF},
    {APP_OM_RELEASE_REQ,                OM_AcpuReleaseReq,                OM_APP_RELEASE_CNF}
};


VOS_VOID OM_AcpuQueryMsgProc(OM_REQ_PACKET_STRU *pRspPacket, OM_RSP_FUNC *pRspFuncPtr)
{
    APP_OM_MSG_EX_STRU                 *pstAppToOmMsg;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulTotalNum;
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReturnPrimId;
    VOS_UINT32                          ulResult = VOS_ERR;

    pstAppToOmMsg = (APP_OM_MSG_EX_STRU*)pRspPacket;
    ulTotalNum = sizeof(g_astAcpuOmMsgFunTbl)/sizeof(OM_MSG_FUN_STRU);
    usPrimId = pstAppToOmMsg->usPrimId;
    /*Search the corresponding function and return PrimId*/
    for (ulIndex = 0; ulIndex < ulTotalNum; ulIndex++)
    {
        if (usPrimId == (VOS_UINT16)(g_astAcpuOmMsgFunTbl[ulIndex].ulPrimId))
        {
            usReturnPrimId = (VOS_UINT16)(g_astAcpuOmMsgFunTbl[ulIndex].ulReturnPrimId);
            ulResult = g_astAcpuOmMsgFunTbl[ulIndex].pfFun(pstAppToOmMsg, usReturnPrimId);
            break;
        }
    }

    /*Can't find the function handles the usPrimId.*/
    if (ulIndex == ulTotalNum)
    {
        OM_AcpuSendResult(pstAppToOmMsg->ucFuncType, ulResult, usPrimId);
    }
    return;
}



VOS_VOID OmAcpuShowOnOff(VOS_VOID)
{
    vos_printf("g_ulAcpuOMSwitchOnOff = %d\r\n",g_ulAcpuOMSwitchOnOff);

    return;
}

/*****************************************************************************
 Prototype       : OM_SocpVoteInfoAdd
 Description     : Acpu OM Record the information of om vote. Only for K3V3
 Input           : enVote  - The information type value.
 Output          : None.
 Return Value    : None.

 History         : ---
    Date         : 2014-02-20
    Author       : zhuli
    Modification : Created function
 *****************************************************************************/

VOS_VOID OM_AcpuSocpVoteInfoAdd(OM_SOCPVOTEINFO_ENUM_UINT32 enInfoType)
{
#if(FEATURE_ON == FEATURE_SOCP_ON_DEMAND)
    if (enInfoType >= OM_SOCPVOTE_INFO_BUTT)
    {
        return;
    }

    g_astOmAcpuSocpVoteInfo[enInfoType].ulCounter++;

    g_astOmAcpuSocpVoteInfo[enInfoType].ulSlice = OM_GetSlice();
#endif

    return;
}

/*****************************************************************************
 Prototype       : OM_SendAcpuSocpVote
 Description     : Acpu OM send the Socp volte massage. Only for K3V3
 Input           : enVote  - The vote value.
 Output          : None.
 Return Value    : None.

 History         : ---
    Date         : 2014-02-20
    Author       : zhuli
    Modification : Created function
 *****************************************************************************/
VOS_VOID OM_SendAcpuSocpVote(SOCP_VOTE_TYPE_ENUM_U32 enVote)
{
#if(FEATURE_ON == FEATURE_SOCP_ON_DEMAND)
    DIAG_MSG_SOCP_VOTE_REQ_STRU *pstMsg;

    if (enVote >= SOCP_VOTE_TYPE_BUTT)
    {
        OM_AcpuSocpVoteInfoAdd(OM_SOCPVOTE_WARNNING);

        return;
    }

    pstMsg = (DIAG_MSG_SOCP_VOTE_REQ_STRU *)VOS_AllocMsg(ACPU_PID_OM, sizeof(DIAG_MSG_SOCP_VOTE_REQ_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg) /*Alloc msg fail could reboot*/
    {
        OM_AcpuSocpVoteInfoAdd(OM_SOCPVOTE_FATAL);

        return;
    }

    pstMsg->ulReceiverPid   = MSP_PID_DIAG_APP_AGENT;
    pstMsg->ulVoteId        = SOCP_VOTE_GU_OM_APP;
    pstMsg->ulVoteType      = enVote;

    if (VOS_OK != VOS_SendMsg(ACPU_PID_OM, pstMsg))
    {
        OM_AcpuSocpVoteInfoAdd(OM_SOCPVOTE_ERROR);

        return;
    }

    if (SOCP_VOTE_FOR_SLEEP == enVote)
    {
        OM_AcpuSocpVoteInfoAdd(OM_SOCPVOTE_SENDSLEEPMSG);
    }
    else
    {
        OM_AcpuSocpVoteInfoAdd(OM_SOCPVOTE_SENDWAKEMSG);
    }
#endif

    return;
}

/*****************************************************************************
 Prototype       : OM_ASocpVoteInfoShow
 Description     : Show the mnte info of OM Socp vote. Only for K3V3
 Input           : None.
 Output          : None.
 Return Value    : None.

 History         : ---
    Date         : 2014-02-20
    Author       : zhuli
    Modification : Created function
 *****************************************************************************/
VOS_VOID OM_ASocpVoteInfoShow(VOS_VOID)
{
#if(FEATURE_ON == FEATURE_SOCP_ON_DEMAND)
    VOS_UINT32  i;
    VOS_CHAR    *acInfoTital[OM_SOCPVOTE_INFO_BUTT] = { "OM_SOCPVOTE_CALLBEGIN",
                                                        "OM_SOCPVOTE_CALLEND",
                                                        "OM_SOCPVOTE_SENDSLEEPMSG",
                                                        "OM_SOCPVOTE_SENDWAKEMSG",
                                                        "OM_SOCPVOTE_WARNNING",
                                                        "OM_SOCPVOTE_ERROR",
                                                        "OM_SOCPVOTE_FATAL"};

    for(i=0; i<OM_SOCPVOTE_INFO_BUTT; i++)
    {
        vos_printf("\r\n%s: Counter is %d, Slice is 0x%x",  acInfoTital[i], 
                                                            g_astOmAcpuSocpVoteInfo[i].ulCounter,
                                                            g_astOmAcpuSocpVoteInfo[i].ulSlice);
    }
#endif

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

