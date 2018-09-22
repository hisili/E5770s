
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AdsInit.h"
#include "AdsUpLink.h"
#include "AdsDownLink.h"
#include "AdsDebug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if ((FEATURE_ON == MBB_CTF_WAN_QUEUE) || (FEATURE_ON == MBB_FEATURE_FASTIP_WAN_QUEUE))
struct work_struct ads_dl_work;
struct work_struct ads_ul_work;
struct workqueue_struct *lte_data_process;
EXPORT_SYMBOL(lte_data_process);
#endif
/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_INIT_C
/*lint +e767*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_INT ADS_UL_CCpuResetCallback(
    DRV_RESET_CALLCBFUN_MOMENT          enParam,
    VOS_INT                             iUserData
)
{
    ADS_CCPU_RESET_IND_STRU                 *pstMsg = VOS_NULL_PTR;

    /* ����Ϊ0��ʾ��λǰ���� */
    if (DRV_RESET_CALLCBFUN_RESET_BEFORE == enParam)
    {
        /* ������Ϣ */
        pstMsg = (ADS_CCPU_RESET_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_ADS_UL,
                                                                        sizeof(ADS_CCPU_RESET_IND_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_CCPU_RESET_IND_STRU: Malloc Msg Failed!\r\n");
            return VOS_ERROR;
        }

        /* ��д��Ϣͷ */
        pstMsg->ulReceiverPid               = ACPU_PID_ADS_UL;
        pstMsg->enMsgId                     = ID_ADS_CCPU_RESET_START_IND;

        /* ����Ϣ */
        if (VOS_OK != PS_SEND_MSG(ACPU_PID_ADS_UL, pstMsg))
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_CCpuResetCallback: Send Msg Failed!\r\n");
            return VOS_ERROR;
        }

        /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ���Ϣ��������ź��������� */
        if (VOS_OK != VOS_SmP(ADS_GetULResetSem(), ADS_RESET_TIMEOUT_LEN))
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_CCpuResetCallback: Lock Binary SEM Failed!\r\n");
            ADS_UL_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

            return VOS_ERROR;
        }

        return VOS_OK;
    }
    /* ��λ�� */
    else if (DRV_RESET_CALLCBFUN_RESET_AFTER == enParam)
    {
        ADS_UL_DBG_SAVE_CCPU_RESET_SUCCESS_NUM(1);

        return VOS_OK;
    }
    else
    {
        return VOS_ERROR;
    }

}


VOS_INT ADS_DL_CCpuResetCallback(
    DRV_RESET_CALLCBFUN_MOMENT          enParam,
    VOS_INT                             iUserData
)
{
    ADS_CCPU_RESET_IND_STRU                *pstMsg = VOS_NULL_PTR;

    /* ����Ϊ0��ʾ��λǰ���� */
    if (DRV_RESET_CALLCBFUN_RESET_BEFORE == enParam)
    {
        /* �յ���λָʾʱ����Ҫ�ȳ���һ�ζ�RD�Ķ��� */
        ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);

        /* ������Ϣ */
        pstMsg = (ADS_CCPU_RESET_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_ADS_DL,
                                                                        sizeof(ADS_CCPU_RESET_IND_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_CCPU_RESET_IND_STRU: Malloc Msg Failed!\r\n");
            return VOS_ERROR;
        }

        /* ��д��Ϣͷ */
        pstMsg->ulReceiverPid               = ACPU_PID_ADS_DL;
        pstMsg->enMsgId                     = ID_ADS_CCPU_RESET_START_IND;

        /* ����Ϣ */
        if (VOS_OK != PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg))
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_CCpuResetCallback: Send Msg Failed!\r\n");
            return VOS_ERROR;
        }

        /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ���Ϣ��������ź��������� */
        if (VOS_OK != VOS_SmP(ADS_GetDLResetSem(), ADS_RESET_TIMEOUT_LEN))
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_CCpuResetCallback: Lock Binary SEM Failed!\r\n");
            ADS_DL_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

            return VOS_ERROR;
        }

        return VOS_OK;
    }
    /* ��λ�� */
    else if (DRV_RESET_CALLCBFUN_RESET_AFTER == enParam)
    {
        ADS_DL_DBG_SAVE_CCPU_RESET_SUCCESS_NUM(1);

        /* ������Ϣ */
        pstMsg = (ADS_CCPU_RESET_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_ADS_DL,
                                                                        sizeof(ADS_CCPU_RESET_IND_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_CCPU_RESET_IND_STRU: Malloc Msg Failed!\r\n");
            return VOS_ERROR;
        }

        /* ��д��Ϣͷ */
        pstMsg->ulReceiverPid               = ACPU_PID_ADS_DL;
        pstMsg->enMsgId                     = ID_ADS_CCPU_RESET_END_IND;

        /* ����Ϣ */
        if (VOS_OK != PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg))
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_CCpuResetCallback: Send Msg Failed!\r\n");
            return VOS_ERROR;
        }

        return VOS_OK;
    }
    else
    {
        return VOS_ERROR;
    }
}


VOS_UINT32 ADS_UL_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch ( enPhase )
    {
        case VOS_IP_LOAD_CONFIG:
            /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
            ADS_InitCtx();
            /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

            /* ������ע��ص�����������C�˵�����λ�Ĵ��� */
            DRV_CCORERESET_REGCBFUNC(NAS_ADS_UL_FUNC_PROC_NAME,
                                     ADS_UL_CCpuResetCallback,
                                     0,
                                     ACPU_RESET_PRIORITY_ADS_UL);

            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_VOID ADS_UL_FidTask(
    VOS_UINT32                          ulQueueID,
    VOS_UINT32                          FID_value,
    VOS_UINT32                          Para1,
    VOS_UINT32                          Para2
)
{
    MsgBlock                           *pMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulEvent       = 0;
    VOS_UINT32                          ulTaskID      = 0;
    VOS_UINT32                          ulRtn         = VOS_ERR;
    VOS_UINT32                          ulEventMask   = 0;
    VOS_UINT32                          ulExpectEvent = 0;

    ulTaskID = VOS_GetCurrentTaskID();
    if (PS_NULL_UINT32 == ulTaskID)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_FidTask: ERROR, TaskID is invalid.");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_FidTask: ERROR, create event fail.");
        return;
    }

    g_ulAdsULTaskId         = ulTaskID;
    g_ulAdsULTaskReadyFlag  = 1;

    ulExpectEvent = ADS_UL_EVENT_DATA_PROC | VOS_MSG_SYNC_EVENT;
    ulEventMask   = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    while (1)
    /*lint +e716*/
    {
        ulRtn = VOS_EventRead(ulExpectEvent, ulEventMask, 0, &ulEvent);
        if (VOS_OK != ulRtn)
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_FidTask: ERROR, read event error.");
            continue;
        }

        /*�¼�����*/
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            ADS_UL_ProcEvent(ulEvent);
            continue;
        }

        pMsg = (MsgBlock*)VOS_GetMsg(ulTaskID);
        if (VOS_NULL_PTR != pMsg)
        {
            if (ACPU_PID_ADS_UL == pMsg->ulReceiverPid)
            {
                ADS_UL_ProcMsg(pMsg);
            }

            PS_FREE_MSG(ACPU_PID_ADS_UL, pMsg);
        }
    }
}



VOS_UINT32 ADS_UL_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:

            /* ����PID��ʼ�� */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_ADS_UL,
                                         (Init_Fun_Type)ADS_UL_PidInit,
                                         (Msg_Fun_Type)ADS_UL_ProcMsg);

            if (VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }


            ulRslt = VOS_RegisterMsgTaskEntry(ACPU_FID_ADS_UL, (VOS_VOIDFUNCPTR)ADS_UL_FidTask);

            if (VOS_OK != ulRslt)
            {
                return ulRslt;
            }

            /* �������ȼ� */
            ulRslt = VOS_RegisterTaskPrio(ACPU_FID_ADS_UL, ADS_UL_TASK_PRIORITY);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_DL_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch ( enPhase )
    {
        case VOS_IP_LOAD_CONFIG:
            /* Added by l60609 for DSDA Phase II, 2012-12-19, Begin */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
            /* ADQ��ʼ�� */
            ADS_DL_InitAdq();
#endif
            /* Added by l60609 for DSDA Phase II, 2012-12-19, End */

            /* ������ע��ص�����������C�˵�����λ�Ĵ��� */
            DRV_CCORERESET_REGCBFUNC(NAS_ADS_DL_FUNC_PROC_NAME,
                                     ADS_DL_CCpuResetCallback,
                                     0,
                                     ACPU_RESET_PRIORITY_ADS_DL);

            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_VOID ADS_DL_FidTask(
    VOS_UINT32                          ulQueueID,
    VOS_UINT32                          FID_value,
    VOS_UINT32                          Para1,
    VOS_UINT32                          Para2
)
{
    MsgBlock                           *pMsg          = VOS_NULL_PTR;
    VOS_UINT32                          ulEvent       = 0;
    VOS_UINT32                          ulTaskID      = 0;
    VOS_UINT32                          ulRtn         = PS_FAIL;
    VOS_UINT32                          ulEventMask   = 0;
    VOS_UINT32                          ulExpectEvent = 0;

    ulTaskID = VOS_GetCurrentTaskID();
    if (PS_NULL_UINT32 == ulTaskID)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_FidTask: ERROR, TaskID is invalid.");
        return;
    }

    if (VOS_OK != VOS_CreateEvent(ulTaskID))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_FidTask: ERROR, create event fail.");
        return;
    }

    g_ulAdsDLTaskId         = ulTaskID;
    g_ulAdsDLTaskReadyFlag  = 1;

    ulExpectEvent = ADS_DL_EVENT_IPF_RD_INT | ADS_DL_EVENT_IPF_ADQ_EMPTY_INT | VOS_MSG_SYNC_EVENT;
    ulEventMask   = (VOS_EVENT_ANY | VOS_EVENT_WAIT);

    /*lint -e716*/
    while (1)
    /*lint +e716*/
    {
        ulRtn = VOS_EventRead(ulExpectEvent, ulEventMask, 0, &ulEvent);

        if (VOS_OK != ulRtn)
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_FidTask: ERROR, read event error.");
            continue;
        }

        /* ͳ�������¼� */
        ADS_DBG_DL_PROC_ALL_EVENT_NUM(1);

        /*RD�¼�����*/
        if (VOS_MSG_SYNC_EVENT != ulEvent)
        {
            ADS_DL_ProcEvent(ulEvent);
#ifdef __PC_UT__
            break;
#endif
            continue;
        }
        pMsg = (MsgBlock*)VOS_GetMsg(ulTaskID);
        if (VOS_NULL_PTR != pMsg)
        {
            if (ACPU_PID_ADS_DL == pMsg->ulReceiverPid)
            {
                ADS_DL_ProcMsg(pMsg);
            }

            PS_FREE_MSG(ACPU_PID_ADS_DL, pMsg);
        }
        else
        {
            /* ͳ�ƿ��¼� */
            ADS_DBG_DL_PROC_EMPTY_EVENT_NUM(1);
        }

    }
}


VOS_UINT32 ADS_DL_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;
    VOS_INT32                           lIpfRslt;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:

            /* ����PID��ʼ�� */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_ADS_DL,
                                         (Init_Fun_Type)ADS_DL_PidInit,
                                         (Msg_Fun_Type)ADS_DL_ProcMsg);

            if ( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }


#if ((FEATURE_ON == MBB_CTF_WAN_QUEUE) || (FEATURE_ON == MBB_FEATURE_FASTIP_WAN_QUEUE))
        lte_data_process = alloc_workqueue("lte_data_process_FZH",  WQ_UNBOUND | WQ_MEM_RECLAIM, 1);
        INIT_WORK(&ads_dl_work, ADS_DL_ProcIpfResult);
        INIT_WORK(&ads_ul_work, ADS_UL_ProcLinkData);
#else
            ulRslt = VOS_RegisterMsgTaskEntry(ACPU_FID_ADS_DL, (VOS_VOIDFUNCPTR)ADS_DL_FidTask);

            if (VOS_OK != ulRslt)
            {
                return ulRslt;
            }
#endif 

            /* ����BSP_IPF_RegisterWakeupDlCbע���жϴ����� */
            lIpfRslt = BSP_IPF_RegisterWakeupDlCb((BSP_IPF_WakeupDlCb)ADS_DL_IpfIntCB);

            if (IPF_SUCCESS != lIpfRslt)
            {
                return VOS_ERR;
            }

            /* Added by l60609 for DSDA Phase II, 2012-12-19, Begin */
#if (FEATURE_OFF == FEATURE_SKB_EXP)
            /* ����ע��AD���жϴ����� */
            lIpfRslt = BSP_IPF_RegisterAdqEmptyDlCb((BSP_IPF_AdqEmptyDlCb)ADS_DL_IpfAdqEmptyCB);

            if (IPF_SUCCESS != lIpfRslt)
            {
                return VOS_ERR;
            }
#endif
            /* Added by l60609 for DSDA Phase II, 2012-12-19, End */


            /* �������ȼ� */
            ulRslt = VOS_RegisterMsgTaskPrio(ACPU_FID_ADS_DL, VOS_PRIORITY_P6);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;
    }

    return VOS_OK;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
