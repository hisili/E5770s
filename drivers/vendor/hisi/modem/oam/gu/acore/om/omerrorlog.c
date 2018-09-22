
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "OmApp.h"
#include "omprivate.h"
#include "OmAppRl.h"
#include "omnvinterface.h"
#include "omerrorlog.h"
#include "AtAppVcomInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_OM_ERRORLOG_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
OM_APP_MSG_RECORD_STRU                  g_stOmAppMsgRecord; /* OM�յ�AP��Ҫ��ȫ�ֱ����м�¼���� */

#if(FEATURE_ON == FEATURE_PTM)

#if (VOS_LINUX == VOS_OS_VER)
struct semaphore                        g_stOmRxErrorLogBuffSem;
#endif

OM_VCOM_DEBUG_INFO                      g_stErrLogVcomDebugInfo   = {0};

OM_ERR_LOG_DEBUG_INFO                   g_stRcvUESendAP           = {0};

HTIMER                                  g_AcpuErrLogFullTmr       = VOS_NULL_PTR ;

/* Error Log �ϱ��漰PID */
VOS_UINT32    g_aulModem0ErrLogDetail[OM_MAX_MODULE_ID]= {
                         I0_WUEPS_PID_MMC,I0_UEPS_PID_MTA,0,               I0_WUEPS_PID_USIM,
                         0,               I0_UEPS_PID_GAS,0,               0,
                         I0_UEPS_PID_SN,  0,              WUEPS_PID_WRR,   0,
                         0,               0,              0,               DSP_PID_WPHY,
                         I0_DSP_PID_APM,  I0_DSP_PID_GPHY,0,               0,
                         PS_PID_ERRC,     TPS_PID_RRC,    0,               0,
                         PS_PID_MM,       PS_PID_ESM,     0,               0,
                         TPS_PID_MAC,     PS_PID_MAC_UL,  0,               0};
#if ( FEATURE_ON == FEATURE_MULTI_MODEM )
VOS_UINT32    g_aulModem1ErrLogDetail[OM_MAX_MODULE_ID]= {
                         I1_WUEPS_PID_MMC,I1_UEPS_PID_MTA,0,               I1_WUEPS_PID_USIM,
                         0,               I1_UEPS_PID_GAS,0,               0,
                         I1_UEPS_PID_SN,  0,              WUEPS_PID_WRR,   0,
                         0,               0,              0,               DSP_PID_WPHY,
                         I1_DSP_PID_APM,  I1_DSP_PID_GPHY,0,               0,
                         PS_PID_ERRC,     TPS_PID_RRC,    0,               0,
                         PS_PID_MM,       PS_PID_ESM,     0,               0,
                         TPS_PID_MAC,     PS_PID_MAC_UL,  0,               0};
#endif

/* ����ģʽ�����ϱ��漰PID */
VOS_UINT32    g_aulModem0FTMDetail[OM_MAX_MODULE_ID]={
                         I0_WUEPS_PID_MMC,I0_WUEPS_PID_MM,I0_WUEPS_PID_GMM,WUEPS_PID_OM_CALLBACK,
                         0,               0,               0,              0,
                         0,               0,               0,              0,
                         WUEPS_PID_WRR,   0,               0,              DSP_PID_WPHY,
                         I0_DSP_PID_APM,  I0_DSP_PID_GPHY, 0,              0,
                         PS_PID_ERRC,     TPS_PID_RRC,     0,              0,
                         PS_PID_MM,       PS_PID_ESM,      0,              0,
                         0,               0,               0,              0};

#if ( FEATURE_ON == FEATURE_MULTI_MODEM )
VOS_UINT32    g_aulModem1FTMDetail[OM_MAX_MODULE_ID]={
                         I1_WUEPS_PID_MMC,I1_WUEPS_PID_MM,I1_WUEPS_PID_GMM,WUEPS_PID_OM_CALLBACK,
                         0,               0,              0,               0,
                         0,               0,              0,               0,
                         WUEPS_PID_WRR,   0,              0,               DSP_PID_WPHY,
                         I1_DSP_PID_APM,  I1_DSP_PID_GPHY,0,               0,
                         PS_PID_ERRC,     TPS_PID_RRC,    0,               0,
                         PS_PID_MM,       PS_PID_ESM,     0,               0,
                         0,               0,              0,               0};
#endif

/* ����ģʽ�����ϱ������ӦPID */
/* ����������moduleIDֻ��Ϊ����֤�˹������ӣ���û��ʵ���õ� */
APP_OM_FTM_MSG_PID_STRU    g_astModem0FTMMsgModule[]={
                            {OM_ERR_LOG_MOUDLE_ID_IMS,  0},
                            {OM_ERR_LOG_MOUDLE_ID_IMSA, 0},
                           };

#if ( FEATURE_ON == FEATURE_MULTI_MODEM )
/* ����������moduleIDֻ��Ϊ����֤�˹������ӣ���û��ʵ���õ� */
APP_OM_FTM_MSG_PID_STRU    g_astModem1FTMMsgModule[]={
                            {OM_ERR_LOG_MOUDLE_ID_IMS,  0},
                            {OM_ERR_LOG_MOUDLE_ID_IMSA, 0},
                           };
#endif

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/
extern VOS_SPINLOCK      g_stVosErrLogSendSpinLock;  /* ��������������g_ulErrLogReportSend���ٽ���Դ���� */

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/


VOS_VOID OM_AcpuRcvMsgFinish(VOS_VOID)
{
    OM_APP_REPORT_STATUS_STRU               stOmAppReportStatus;

    stOmAppReportStatus.stOmHeader.ulMsgType = OM_ERR_LOG_MSG_ERR_REPORT_END;
    stOmAppReportStatus.stOmHeader.ulMsgSN   = g_stErrLogVcomDebugInfo.ulVCOMSendSn++;
    stOmAppReportStatus.stOmHeader.ulMsgLen  = (sizeof(OM_APP_REPORT_STATUS_STRU) - sizeof(OM_ALARM_MSG_HEAD_STRU));
    stOmAppReportStatus.usModemID            = g_stOmAppMsgRecord.usModemId;
    stOmAppReportStatus.ulReportStatus       = g_stOmAppMsgRecord.ulErrLogReportSend;

    OM_AcpuSendVComData((VOS_UINT8 *)&stOmAppReportStatus, sizeof(OM_APP_REPORT_STATUS_STRU));
    
    /* ��ֹ��Ϣ�ٴ��·����ɹ� */
    g_stOmAppMsgRecord.ulErrLogReportSend = OM_AP_NO_MSG_SEND;

    return ;
}


VOS_VOID OM_AcpuSendAppResult(VOS_UINT32 ulRest, VOS_UINT16  usModemId)
{
    OM_APP_RESULT_CNF_STRU               stOmAppResultCnf;

    stOmAppResultCnf.stOmHeader.ulMsgType = OM_ERR_LOG_MSG_RESULT;
    stOmAppResultCnf.stOmHeader.ulMsgSN   = g_stErrLogVcomDebugInfo.ulVCOMSendSn++;
    stOmAppResultCnf.stOmHeader.ulMsgLen  = (sizeof(OM_APP_RESULT_CNF_STRU) - sizeof(OM_ALARM_MSG_HEAD_STRU));
    stOmAppResultCnf.usModemID            = usModemId;
    stOmAppResultCnf.ulStatus             = ulRest;

    OM_AcpuSendVComData((VOS_UINT8 *)&stOmAppResultCnf, sizeof(OM_APP_RESULT_CNF_STRU));

    return ;
}


VOS_INT OM_AcpuSwitchOnOffErrLog(APP_OM_CTRL_STATUS_STRU  *pstAppOmCtrlStatus)
{
    NV_ID_ERR_LOG_CTRL_INFO_STRU         stNvErrLogCtrlInfo;
    OM_ERROR_LOG_CTRL_IND_STRU          *pOmErrorLogCtrlInd;
    VOS_UINT32                          *pulErrorLogModule;
    VOS_UINT32                           i;

    /* �������� */
    stNvErrLogCtrlInfo.ucAlmStatus = pstAppOmCtrlStatus->ucAlmStatus;
    stNvErrLogCtrlInfo.ucAlmLevel  = pstAppOmCtrlStatus->ucAlmLevel;

    /* modem ID ���*/
    if (MODEM_ID_0 == pstAppOmCtrlStatus->usModemID)
    {
        pulErrorLogModule = g_aulModem0ErrLogDetail;
    }
#if ( FEATURE_ON == FEATURE_MULTI_MODEM )
    else if (MODEM_ID_1 == pstAppOmCtrlStatus->usModemID)
    {
        pulErrorLogModule = g_aulModem1ErrLogDetail;
    }
#endif
    else
    {
        OM_ERR_LOG("OM_AcpuSwitchOnOffErrLog: modem id error!\r\n ");
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrNum++;
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrLen += (pstAppOmCtrlStatus->stOmHeader.ulMsgLen + sizeof(OM_ALARM_MSG_HEAD_STRU));
        OM_AcpuSendAppResult(OM_APP_SEND_MODEM_ID_ERR, pstAppOmCtrlStatus->usModemID);
        return OM_APP_SEND_MODEM_ID_ERR;
    }

    if (VOS_OK !=NV_WriteEx(pstAppOmCtrlStatus->usModemID,
                            en_NV_Item_ErrLogCtrlInfo,
                            &stNvErrLogCtrlInfo,
                            sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU)))
    {
        /* ��Ap �ظ���Ϣ */
        OM_ERR_LOG("OM_AcpuSwitchOnOffErrLog: nv write fail!\r\n ");
        OM_AcpuSendAppResult(OM_APP_OMACPU_WRITE_NV_ERR, pstAppOmCtrlStatus->usModemID);
        return OM_APP_OMACPU_WRITE_NV_ERR;
    }

    for (i=0; i < OM_MAX_MODULE_ID; i++)
    {
        if (OM_PID_NULL != pulErrorLogModule[i])
        {
            pOmErrorLogCtrlInd = (OM_ERROR_LOG_CTRL_IND_STRU*)VOS_AllocMsg(ACPU_PID_OM,
                                  (sizeof(OM_ERROR_LOG_CTRL_IND_STRU) - VOS_MSG_HEAD_LENGTH));
            if (VOS_NULL_PTR == pOmErrorLogCtrlInd)
            {
                OM_AcpuSendAppResult(OM_APP_OMACPU_ALLOC_MSG_ERR, pstAppOmCtrlStatus->usModemID);
                return OM_APP_OMACPU_ALLOC_MSG_ERR;
            }

            pOmErrorLogCtrlInd->ulReceiverPid = pulErrorLogModule[i];
            pOmErrorLogCtrlInd->ulMsgName     = ID_OM_ERR_LOG_CTRL_IND;
            pOmErrorLogCtrlInd->usModemID     = pstAppOmCtrlStatus->usModemID;
            pOmErrorLogCtrlInd->ucAlmStatus   = pstAppOmCtrlStatus->ucAlmStatus;
            pOmErrorLogCtrlInd->ucAlmLevel    = pstAppOmCtrlStatus->ucAlmLevel;
            (VOS_VOID)VOS_SendMsg(ACPU_PID_OM, pOmErrorLogCtrlInd);
        }
    }

    /* ��AP�ظ���Ϣ */
    OM_AcpuSendAppResult(OM_APP_MSG_OK, pstAppOmCtrlStatus->usModemID);

    return VOS_OK;
}


VOS_INT OM_AcpuSwitchOnOffFTM(APP_OM_CTRL_STATUS_STRU *pstAppOmCtrlStatus)
{
    NV_ID_FTM_DETAIL_STRU               stNvFTMDetail;
    OM_FTM_CTRL_IND_STRU               *pstOmFtmCtrlInd;
    VOS_UINT32                          ulRest;
    VOS_UINT32                          i;

    /* modem ID ���*/
    if (MODEM_ID_0 == pstAppOmCtrlStatus->usModemID)
    {
        g_stOmAppMsgRecord.pulFTMModule = g_aulModem0FTMDetail;
    }
#if ( FEATURE_ON == FEATURE_MULTI_MODEM )
    else if (MODEM_ID_1 == pstAppOmCtrlStatus->usModemID)
    {
        g_stOmAppMsgRecord.pulFTMModule = g_aulModem1FTMDetail;
    }
#endif
    else
    {
        OM_ERR_LOG("OM_AcpuSwitchOnOffFTM: modem id error!\r\n ");
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrNum++;
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrLen += (pstAppOmCtrlStatus->stOmHeader.ulMsgLen + sizeof(OM_ALARM_MSG_HEAD_STRU));
        OM_AcpuSendAppResult(OM_APP_SEND_MODEM_ID_ERR, pstAppOmCtrlStatus->usModemID);
        return OM_APP_SEND_MODEM_ID_ERR;
    }

    ulRest = NV_ReadEx(pstAppOmCtrlStatus->usModemID, en_NV_Item_FTMDetail,
                       (VOS_VOID*)&stNvFTMDetail, sizeof(NV_ID_FTM_DETAIL_STRU));
    if (VOS_OK != ulRest)
    {
        OM_ERR_LOG("OM_AcpuSwitchOnOffFTM: nv read faile!\r\n ");
        OM_AcpuSendAppResult(OM_APP_OMACPU_READ_NV_ERR, pstAppOmCtrlStatus->usModemID);
        return OM_APP_OMACPU_READ_NV_ERR;
    }

    g_stOmAppMsgRecord.ulFTMReportSend = stNvFTMDetail.ulFTMDetail;

    /* �������������ȼ��ϸߣ��ȸ�AP�ظ���Ϣ��������ʧ�ܵĳ���������ά�ɲ⣬���Թ��ȿ��� */
    OM_AcpuSendAppResult(OM_APP_MSG_OK, pstAppOmCtrlStatus->usModemID);

    /* ���ݹ���ģʽ����ԣ����ӦPID������Ϣ */
    for (i=0; i<OM_MAX_MODULE_ID; i++)
    {
        if ((0 !=(BIT_N(i) & g_stOmAppMsgRecord.ulFTMReportSend)) && (OM_PID_NULL != g_stOmAppMsgRecord.pulFTMModule[i]))
        {
            /* ����Ӧ��PID������Ϣ */
            pstOmFtmCtrlInd = (OM_FTM_CTRL_IND_STRU*)VOS_AllocMsg(ACPU_PID_OM,
                                  (sizeof(OM_FTM_CTRL_IND_STRU) - VOS_MSG_HEAD_LENGTH));
            if (VOS_NULL_PTR == pstOmFtmCtrlInd)
            {
                OM_AcpuSendAppResult(OM_APP_OMACPU_ALLOC_MSG_ERR, pstAppOmCtrlStatus->usModemID);
                return OM_APP_OMACPU_ALLOC_MSG_ERR;
            }

            pstOmFtmCtrlInd->ulReceiverPid = g_stOmAppMsgRecord.pulFTMModule[i];
            pstOmFtmCtrlInd->ulMsgName     = ID_OM_FTM_CTRL_IND;
            pstOmFtmCtrlInd->usModemID     = pstAppOmCtrlStatus->usModemID;
            pstOmFtmCtrlInd->ucActionFlag  = pstAppOmCtrlStatus->ucAlmStatus;

            (VOS_VOID)VOS_SendMsg(ACPU_PID_OM, pstOmFtmCtrlInd);
        }
    }

    return VOS_OK;
}


VOS_INT OM_AcpuSwitchOnOff(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    APP_OM_CTRL_STATUS_STRU              *pstAppOmCtrlStatus;

    pstAppOmCtrlStatus = (APP_OM_CTRL_STATUS_STRU*)pucData;

    if (OM_APP_SWITCH_MSG_ID_ERR_LOG == pstAppOmCtrlStatus->ulMsgModuleID)
    {
        /* Error log ���� */
        return OM_AcpuSwitchOnOffErrLog(pstAppOmCtrlStatus);
    }
    else if (OM_APP_SWITCH_MSG_ID_FTM == pstAppOmCtrlStatus->ulMsgModuleID)
    {
        /* ����ģʽ���� */
        return OM_AcpuSwitchOnOffFTM(pstAppOmCtrlStatus);
    }
    else
    {
        /* �쳣��Ϣ�ϱ� */
        OM_ERR_LOG("OM_AcpuSwitchOnOff: Msg Module id error!\r\n ");
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrNum++;
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrLen += ulLen;
        OM_AcpuSendAppResult(OM_APP_MSG_MODULE_ID_ERR, pstAppOmCtrlStatus->usModemID);
    }

    return OM_APP_MSG_MODULE_ID_ERR;
}


VOS_INT OM_AcpuRcvAppMsgCheck(APP_OM_REQ_ERR_LOG_STRU *pstAppOmReqErrLog)
{
    NV_ID_ERR_LOG_CTRL_INFO_STRU        stNvErrLogCtrlInfo;
    VOS_UINT32                          ulRest;

    /* modem ID ���*/
    if (MODEM_ID_0 == pstAppOmReqErrLog->usModemID)
    {
        g_stOmAppMsgRecord.pulErrorLogModule = g_aulModem0ErrLogDetail;
    }
#if ( FEATURE_ON == FEATURE_MULTI_MODEM )
    else if (MODEM_ID_1 == pstAppOmReqErrLog->usModemID)
    {
        g_stOmAppMsgRecord.pulErrorLogModule = g_aulModem1ErrLogDetail;
    }
#endif
    else
    {
        OM_ERR_LOG("OM_AcpuRcvAppMsgCheck: modem id error!\r\n ");
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrNum++;
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrLen += (pstAppOmReqErrLog->stOmHeader.ulMsgLen + sizeof(OM_ALARM_MSG_HEAD_STRU));
        OM_AcpuSendAppResult(OM_APP_SEND_MODEM_ID_ERR, pstAppOmReqErrLog->usModemID);
        return OM_APP_SEND_MODEM_ID_ERR;
    }

    g_stOmAppMsgRecord.usModemId = pstAppOmReqErrLog->usModemID;

    /* ����������ԵĺϷ��� */
    if ( OM_MAX_FAULT_ID < pstAppOmReqErrLog->usFaultId)
    {
        OM_ERR_LOG1("OM_AcpuRcvAppMsgCheck: fault id error, id is %d!\r\n ", pstAppOmReqErrLog->usFaultId);
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrNum++;
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrLen += (pstAppOmReqErrLog->stOmHeader.ulMsgLen + sizeof(OM_ALARM_MSG_HEAD_STRU));
        OM_AcpuSendAppResult(OM_APP_SEND_FAULT_ID_ERR, pstAppOmReqErrLog->usModemID);
        return OM_APP_SEND_FAULT_ID_ERR;
    }

    /* �жϿ����Ƿ�� */
    ulRest = NV_ReadEx(pstAppOmReqErrLog->usModemID,
                       en_NV_Item_ErrLogCtrlInfo,
                       (VOS_VOID*)&stNvErrLogCtrlInfo,
                       sizeof(NV_ID_ERR_LOG_CTRL_INFO_STRU));
    if (VOS_OK != ulRest)
    {
        OM_ERR_LOG1("OM_AcpuRcvAppMsgCheck: nv read fail nv id is: %d!\r\n",en_NV_Item_ErrLogCtrlInfo);
        OM_AcpuSendAppResult(OM_APP_OMACPU_READ_NV_ERR, pstAppOmReqErrLog->usModemID);
        return OM_APP_OMACPU_READ_NV_ERR;
    }

    /* �жϿ����Ƿ�� */
    if (OM_APP_STATUS_CLOSE == stNvErrLogCtrlInfo.ucAlmStatus)
    {
        OM_ERR_LOG("OM_AcpuRcvAppMsgCheck: error log switch is close!\r\n");
        OM_AcpuSendAppResult(OM_APP_ERRLOG_SWITCH_CLOSE_ERR, pstAppOmReqErrLog->usModemID);
        return OM_APP_ERRLOG_SWITCH_CLOSE_ERR;
    }

    /* ���û���ϱ���� */
    if (OM_AP_SEND_MSG_FINISH != g_stOmAppMsgRecord.ulErrLogReportSend)
    {
        OM_ERR_LOG1("OM_AcpuRcvAppMsgCheck: error log report not end: %d!\r\n ", g_stOmAppMsgRecord.ulErrLogReportSend);
        OM_AcpuSendAppResult(OM_APP_REPORT_NOT_FINISH_ERR, pstAppOmReqErrLog->usModemID);
        return OM_APP_REPORT_NOT_FINISH_ERR;
    }

    return VOS_OK;
}



VOS_INT OM_AcpuRcvAppFaultIDCheck(APP_OM_REQ_ERR_LOG_STRU *pstAppOmReqErrLog)
{
    NV_ALARM_ID_RELATIONSHIP_STRU       stAlarmIdRelationship;
    VOS_UINT32                          ulFaultId = OM_ERR_FAULT_ID;
    VOS_UINT32                          ulLockLevel;
    VOS_UINT32                          i;

    if (VOS_OK != NV_ReadEx(pstAppOmReqErrLog->usModemID,
                       en_NV_Item_AlarmidRelationship,
                       (VOS_VOID*)&stAlarmIdRelationship,
                       sizeof(NV_ALARM_ID_RELATIONSHIP_STRU)))
    {
        OM_ERR_LOG1("OM_AcpuReportErrLogMsg: nv read fail nv id is: %d!\r\n", en_NV_Item_AlarmidRelationship);
        OM_AcpuSendAppResult(OM_APP_OMACPU_READ_NV_ERR, pstAppOmReqErrLog->usModemID);
        return OM_APP_OMACPU_READ_NV_ERR;
    }

    /* ���ݸ澯��ʶ���Ҹ澯����� */
    for (i=0; i < OM_MAX_FAULT_ID; i++)
    {
        if (pstAppOmReqErrLog->usFaultId == stAlarmIdRelationship.astOmAlarmidRelationship[i].ulAlarmid)
        {
            ulFaultId = i;
            break;
        }
    }

    /* û���ҵ����ϳ������ID */
    if(OM_ERR_FAULT_ID == ulFaultId)
    {
        OM_ERR_LOG1("OM_AcpuReportErrLogMsg: no this fault id!\r\n ", pstAppOmReqErrLog->usFaultId);
        OM_AcpuSendAppResult(OM_APP_NO_FAULT_ID_ERR, pstAppOmReqErrLog->usModemID);
        return OM_APP_NO_FAULT_ID_ERR;
    }

    /*VOS_Splx(intLockLevel);*/
    VOS_SpinLockIntLock(&g_stVosErrLogSendSpinLock, ulLockLevel);

    g_stOmAppMsgRecord.ulErrLogReportSend = stAlarmIdRelationship.astOmAlarmidRelationship[ulFaultId].ulAlarmidDetail;

    VOS_SpinUnlockIntUnlock(&g_stVosErrLogSendSpinLock, ulLockLevel);

    return VOS_OK;

}


VOS_INT OM_AcpuReportErrLogMsg(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    APP_OM_REQ_ERR_LOG_STRU            *pstAppOmReqErrLog;
    OM_ERR_LOG_REPORT_REQ_STRU         *pstOmErrLogReportReq;
    VOS_UINT32                          ulSendPidCount = 0;
    VOS_INT                             lRest;
    VOS_UINT32                          i;

    pstAppOmReqErrLog = (APP_OM_REQ_ERR_LOG_STRU*)pucData;

    /* �յ�AP��Ϣ��� */
    lRest = OM_AcpuRcvAppMsgCheck(pstAppOmReqErrLog);
    if (VOS_OK != lRest)
    {
        return lRest;
    }

    /* ���ϳ�����ż�� */
    lRest = OM_AcpuRcvAppFaultIDCheck(pstAppOmReqErrLog);
    if (VOS_OK != lRest)
    {
        return lRest;
    }

    /* �������������ȼ��ϸߣ��ȸ�AP�ظ���Ϣ��������ʧ�ܵĳ���������ά�ɲ⣬���Թ��ȿ��� */
    OM_AcpuSendAppResult(OM_APP_MSG_OK, pstAppOmReqErrLog->usModemID);

    /* ���ݸ澯����ԣ����ӦPID������Ϣ */
    for (i=0; i<OM_MAX_MODULE_ID; i++)
    {
        if ((0 != (BIT_N(i) & g_stOmAppMsgRecord.ulErrLogReportSend)) && (0 != g_stOmAppMsgRecord.pulErrorLogModule[i]))
        {
            ulSendPidCount++;
            /* ����Ӧ��PID������Ϣ */
            pstOmErrLogReportReq  = (OM_ERR_LOG_REPORT_REQ_STRU*)VOS_AllocMsg(ACPU_PID_OM,
                                     (sizeof(OM_ERR_LOG_REPORT_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

            if (VOS_NULL_PTR == pstOmErrLogReportReq)
            {
                OM_AcpuSendAppResult(OM_APP_OMACPU_ALLOC_MSG_ERR, pstAppOmReqErrLog->usModemID);
                return OM_APP_OMACPU_ALLOC_MSG_ERR;
            }
            pstOmErrLogReportReq->ulReceiverPid = g_stOmAppMsgRecord.pulErrorLogModule[i];
            pstOmErrLogReportReq->ulMsgName     = ID_OM_ERR_LOG_REPORT_REQ;
            pstOmErrLogReportReq->usModemID     = pstAppOmReqErrLog->usModemID;

            (VOS_VOID)VOS_SendMsg(ACPU_PID_OM, pstOmErrLogReportReq);
        }
    }

    /* ����û�и澯�����PID��ֱ�Ӹ�AP�ظ���Ϣ�ϱ���� */
    if (0 == ulSendPidCount)
    {
        g_stOmAppMsgRecord.usModemId = pstAppOmReqErrLog->usModemID;
        OM_AcpuRcvMsgFinish();
        return VOS_OK;
    }

    /* ��5s��ʱ�� */
    g_AcpuErrLogFullTmr = VOS_NULL_PTR;
    if (VOS_OK != VOS_StartRelTimer(&g_AcpuErrLogFullTmr, ACPU_PID_OM, OM_ERRLOG_TIMER_LENTH, 
                                    OM_ERRLOG_TIMER, 0, VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_5))
    {
        OM_ERR_LOG("\r\n OM_AcpuReportErrLogMsg: StartDrxTimer fail\n");
        return OM_APP_ERRLOG_START_TIMER_ERR;
    }

    return VOS_OK;
}


VOS_VOID OM_AcpuSendVComData(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    /* ����ע�ắ������Vcom������ */
    g_stErrLogVcomDebugInfo.ulVCOMSendNum++;
    g_stErrLogVcomDebugInfo.ulVCOMSendLen += ulLen;

    /*lint -e40*/
    OM_ACPU_DEBUG_TRACE((VOS_UINT8*)pucData, ulLen, OM_ACPU_ERRLOG_SEND);
    /*lint +e40*/

    if(VOS_OK != APP_VCOM_Send(APP_VCOM_DEV_INDEX_ERRLOG, pucData, ulLen))
    {
        g_stErrLogVcomDebugInfo.ulVCOMSendErrNum++;
        g_stErrLogVcomDebugInfo.ulVCOMSendErrLen += ulLen;

        OM_ERR_LOG("\r\n Info: OM_AcpuSendVComData: Nas Send Msg fail\n");

        return ;
    }
    return ;
}


VOS_VOID OM_AcpuSendFTMMsgOther(APP_OM_FTM_REQ_STRU *pstAppOmFtmReq, VOS_UINT32 ulLen, VOS_UINT32 ulPID)
{
    OM_FTM_REQUIRE_STRU                *pstOmFtmReq;  

    if (VOS_NULL == ulPID)
    {
        return;
    }
    
    /* ����ģʽ�����ϱ�֪ͨ��Ӧ����� */
    pstOmFtmReq  = (OM_FTM_REQUIRE_STRU*)VOS_AllocMsg(ACPU_PID_OM, 
                                         (ulLen + sizeof(VOS_UINT32) + sizeof(VOS_UINT16)));

    if (VOS_NULL_PTR == pstOmFtmReq)
    {
        OM_AcpuSendAppResult(OM_APP_OMACPU_ALLOC_MSG_ERR, pstAppOmFtmReq->usModemID);
        OM_ERR_LOG("OM_AcpuSendFTMMsgOther:malloc msg fail\r\n");
        return ;
    }
    pstOmFtmReq->ulReceiverPid = ulPID;
    pstOmFtmReq->ulMsgName     = ID_OM_FTM_REQUIRE_IND;
    pstOmFtmReq->usModemID     = pstAppOmFtmReq->usModemID;
    VOS_MemCpy((VOS_VOID*)pstOmFtmReq->aucContent, (VOS_VOID*)pstAppOmFtmReq, ulLen);

    /* ��ǰ�ظ���Ϣ */
    OM_AcpuSendAppResult(OM_APP_MSG_OK, pstAppOmFtmReq->usModemID);

    (VOS_VOID)VOS_SendMsg(ACPU_PID_OM, pstOmFtmReq);

    return ;
}


VOS_INT OM_AcpuFTMMsgReq(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    APP_OM_FTM_REQ_STRU                *pstAppOmReqFtm;
    VOS_UINT32                          ulIndex;

    pstAppOmReqFtm = (APP_OM_FTM_REQ_STRU*)pucData;

    /* modem ID ���*/
    if (MODEM_ID_0 == pstAppOmReqFtm->usModemID)
    {
        for (ulIndex=0; ulIndex<(sizeof(g_astModem0FTMMsgModule) / sizeof(g_astModem0FTMMsgModule[0])); ulIndex++)
        {
            if (pstAppOmReqFtm->ulMsgModuleID == g_astModem0FTMMsgModule[ulIndex].ulMsgModuleID)
            {
                OM_AcpuSendFTMMsgOther(pstAppOmReqFtm, ulLen, g_astModem0FTMMsgModule[ulIndex].ulPID);
                break;
            }
        }

        if ( (sizeof(g_astModem0FTMMsgModule) / sizeof(g_astModem0FTMMsgModule[0])) <= ulIndex )
        {
            OM_ERR_LOG1("OM_AcpuFTMMsgReq:MsgModule ID is error %d\r\n", pstAppOmReqFtm->ulMsgModuleID);
            return OM_APP_MSG_MODULE_ID_ERR;
        }
    }
    
#if ( FEATURE_ON == FEATURE_MULTI_MODEM )
    else if (MODEM_ID_1 == pstAppOmReqFtm->usModemID)
    {
        for (ulIndex=0; ulIndex<(sizeof(g_astModem1FTMMsgModule) / sizeof(g_astModem1FTMMsgModule[0])); ulIndex++)
        {
            if (pstAppOmReqFtm->ulMsgModuleID == g_astModem1FTMMsgModule[ulIndex].ulMsgModuleID)
            {
                OM_AcpuSendFTMMsgOther(pstAppOmReqFtm, ulLen, g_astModem1FTMMsgModule[ulIndex].ulPID);
                break;
            }
        }

        if ( (sizeof(g_astModem0FTMMsgModule) / sizeof(g_astModem0FTMMsgModule[0])) <= ulIndex )
        {
            OM_ERR_LOG1("OM_AcpuFTMMsgReq:MsgModule ID is error %d\r\n", pstAppOmReqFtm->ulMsgModuleID);
            return OM_APP_MSG_MODULE_ID_ERR;
        }  
    }
#endif
    else
    {
        OM_ERR_LOG("OM_AcpuFTMMsgReq: modem id error!\r\n ");
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrNum++;
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrLen += ulLen;
        OM_AcpuSendAppResult(OM_APP_SEND_MODEM_ID_ERR, pstAppOmReqFtm->usModemID);
        return OM_APP_SEND_MODEM_ID_ERR;
    }

    return OM_APP_MSG_OK;  
    
}


VOS_UINT32 OM_AcpuRcvErrLogMsgCheck(OM_RCV_DATA_INFO_STRU *pstOmRcvDataInfo, VOS_UINT32 *pulSendPidCount)
{
    VOS_UINT32                          ulLockLevel;
    VOS_UINT32                          i;

    /* Error Log �ϱ� */
    if (VOS_NULL_PTR == g_stOmAppMsgRecord.pulErrorLogModule)
    {
        OM_ERR_LOG("OM_AcpuRcvMsgCheck: not expect report Err log msg!\r\n ");
        return VOS_ERR;
    }

    g_stRcvUESendAP.ulErrLogRcvNum++;
    g_stRcvUESendAP.ulErrLogRcvLen += pstOmRcvDataInfo->stOmHeader.ulMsgLen;

    /* ��¼��Ӧ������ϱ���Ϣ */
    for (i=0; i<OM_MAX_MODULE_ID; i++)
    {
        if ((g_stOmAppMsgRecord.pulErrorLogModule[i] == pstOmRcvDataInfo->ulSenderPid)
            && (OM_PID_NULL != g_stOmAppMsgRecord.pulErrorLogModule[i])
            && (0 != (BIT_N(i) & g_stOmAppMsgRecord.ulErrLogReportSend)))
        {
            (*pulSendPidCount)++;
            g_stRcvUESendAP.ulErrLogSendNum++;
            g_stRcvUESendAP.ulErrLogSendLen += pstOmRcvDataInfo->stOmHeader.ulMsgLen;

            /*VOS_Splx(intLockLevel);*/
            VOS_SpinLockIntLock(&g_stVosErrLogSendSpinLock, ulLockLevel);

            /* �����PID��0�������Ѿ��ϱ��� */
            g_stOmAppMsgRecord.ulErrLogReportSend = g_stOmAppMsgRecord.ulErrLogReportSend & (~((VOS_UINT32)(BIT_N(i))));

            VOS_SpinUnlockIntUnlock(&g_stVosErrLogSendSpinLock, ulLockLevel);
            break;
        }
    }

    OM_ERR_LOG2("OM_AcpuRcvMsgCheck:error log Module id is %d, g_stOmAppMsgRecord.ulErrLogReportSend is!\r\n ",
                 g_stOmAppMsgRecord.pulErrorLogModule[i], g_stOmAppMsgRecord.ulErrLogReportSend);

    return VOS_OK;
}


VOS_UINT32 OM_AcpuRcvFTMReportMsgCheck(OM_RCV_DATA_INFO_STRU *pstOmRcvDataInfo, VOS_UINT32 *pulSendPidCount)
{
    VOS_UINT32                          i;

    /* ����ģʽ�����ϱ� */
    if (VOS_NULL_PTR == g_stOmAppMsgRecord.pulFTMModule)
    {
        OM_ERR_LOG("OM_AcpuRcvMsgCheck: not expect report Ftm msg!\r\n ");
        return VOS_ERR;
    }

    /* ����ģʽ�ϱ� */
    g_stRcvUESendAP.ulFTMRcvNum++;
    g_stRcvUESendAP.ulFTMRcvLen += pstOmRcvDataInfo->stOmHeader.ulMsgLen;
    for(i=0; i<OM_MAX_MODULE_ID; i++)
    {
        if ((g_stOmAppMsgRecord.pulFTMModule[i] == pstOmRcvDataInfo->ulSenderPid)
             && (0 !=(BIT_N(i) & g_stOmAppMsgRecord.ulFTMReportSend))
             && (OM_PID_NULL != g_stOmAppMsgRecord.pulFTMModule[i]))
        {
            (*pulSendPidCount)++;
            g_stRcvUESendAP.ulFTMSendNum++;
            g_stRcvUESendAP.ulFTMSendLen += pstOmRcvDataInfo->stOmHeader.ulMsgLen;

            break;
        }
    }

    OM_ERR_LOG2("OM_AcpuRcvMsgCheck: Module id is %d, g_stOmAppMsgRecord.ulFTMReportSend is!\r\n ",
                 g_stOmAppMsgRecord.pulFTMModule[i], g_stOmAppMsgRecord.ulFTMReportSend);

    return VOS_OK;
}


VOS_UINT32 OM_AcpuRcvFTMCnfMsgCheck(OM_RCV_DATA_INFO_STRU *pstOmRcvDataInfo, VOS_UINT32 *pulSendPidCount)
{
    OM_APP_FTM_CNF_STRU                *pstOmAppFtmCnf;
    VOS_UINT32                          ulIndex;

    /* ����ģʽ��Ӧ�ϱ���С��Ϣ���� */
    if ((4*sizeof(VOS_UINT32)) > pstOmRcvDataInfo->stOmHeader.ulMsgLen)
    {
        OM_ERR_LOG1("OM_AcpuRcvFTMCnfMsgCheck:MsgModule ID is error %d\r\n", pstOmRcvDataInfo->stOmHeader.ulMsgLen);
        return OM_APP_MSG_LENGTH_ERR;
    }

    pstOmAppFtmCnf= (OM_APP_FTM_CNF_STRU*)(&pstOmRcvDataInfo->stOmHeader.ulMsgType);

    if (MODEM_ID_0 == pstOmAppFtmCnf->usModemID)
    {
        for (ulIndex=0; ulIndex<(sizeof(g_astModem0FTMMsgModule) / sizeof(g_astModem0FTMMsgModule[0])); ulIndex++)
        {
            if ((g_astModem0FTMMsgModule[ulIndex].ulMsgModuleID == pstOmAppFtmCnf->ulMsgModuleID)
                && (g_astModem0FTMMsgModule[ulIndex].ulPID == pstOmRcvDataInfo->ulSenderPid))
            {
               (*pulSendPidCount)++;
                break;
            }
        }

        if ((sizeof(g_astModem0FTMMsgModule) / sizeof(g_astModem0FTMMsgModule[0])) <= ulIndex)
        {
            OM_ERR_LOG1("OM_AcpuFTMMsgReq:MsgModule ID is error %d\r\n", pstOmAppFtmCnf->ulMsgModuleID);
            return OM_APP_MSG_MODULE_ID_ERR;
        }
    }
#if ( FEATURE_ON == FEATURE_MULTI_MODEM )
    else if (MODEM_ID_1 == pstOmAppFtmCnf->usModemID)
    {
        for (ulIndex=0; ulIndex<(sizeof(g_astModem1FTMMsgModule) / sizeof(g_astModem1FTMMsgModule[0])); ulIndex++)
        {
            if ((g_astModem1FTMMsgModule[ulIndex].ulMsgModuleID == pstOmAppFtmCnf->ulMsgModuleID)
                && (g_astModem1FTMMsgModule[ulIndex].ulPID == pstOmRcvDataInfo->ulSenderPid))
            {
               (*pulSendPidCount)++;
                break;
            }
        }

        if ((sizeof(g_astModem1FTMMsgModule) / sizeof(g_astModem1FTMMsgModule[0])) <= ulIndex)
        {
            OM_ERR_LOG1("OM_AcpuFTMMsgReq:MsgModule ID is error %d\r\n", pstOmAppFtmCnf->ulMsgModuleID);
            return OM_APP_MSG_MODULE_ID_ERR;
        }
    }
#endif
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;

}

VOS_UINT32 OM_AcpuRcvMsgCheck(OM_RCV_DATA_INFO_STRU *pstOmRcvDataInfo)
{
    VOS_UINT32                          ulSendPidCount = 0;

    switch(pstOmRcvDataInfo->stOmHeader.ulMsgType)
    {
        case OM_ERR_LOG_MSG_ERR_REPORT:
            /* Error Log �ϱ� */
            if(VOS_OK != OM_AcpuRcvErrLogMsgCheck(pstOmRcvDataInfo, &ulSendPidCount))
            {
                return VOS_ERR;
            }
            break;

        case OM_ERR_LOG_MSG_FTM_REPORT:            
            /* ����ģʽ�����ϱ� */
            if(VOS_OK != OM_AcpuRcvFTMReportMsgCheck(pstOmRcvDataInfo, &ulSendPidCount))
            {
                return VOS_ERR;
            }                
            break;

        case OM_ERR_LOG_MSG_FTM_CNF:
            /* ����ģʽ�����ϱ� */
            if(VOS_OK != OM_AcpuRcvFTMCnfMsgCheck(pstOmRcvDataInfo, &ulSendPidCount))
            {
                return VOS_ERR;
            }  
            break;

        case OM_AUDIO_ERR_LOG_MSG_REPORT:
            /* AUDIO���ErrLog�ϱ� */
            ulSendPidCount++;
            break;

        default:
            /* �쳣 */
            OM_ERR_LOG("OM_AcpuRcvMsgCheck: Msg type error!\r\n ");
            return VOS_ERR;
    }

    /* ����Ԥ���ϱ�,������Ϣ */
    if (OM_AP_NO_MSG_SEND == ulSendPidCount)
    {
        OM_ERR_LOG("OM_AcpuRcvMsgCheck: No msg Send!\r\n ");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID OM_AcpuErrLogInfoShow(VOS_VOID)
{
    vos_printf("\r\nVCom Send sn is           %d", g_stErrLogVcomDebugInfo.ulVCOMSendSn);
    vos_printf("\r\nVCom Send num is           %d", g_stErrLogVcomDebugInfo.ulVCOMSendNum);
    vos_printf("\r\nVCom Send Len is           %d", g_stErrLogVcomDebugInfo.ulVCOMSendLen);

    vos_printf("\r\nVCom Send Error num is         %d", g_stErrLogVcomDebugInfo.ulVCOMSendErrNum);
    vos_printf("\r\nVCom Send Error Len is         %d\r\n", g_stErrLogVcomDebugInfo.ulVCOMSendErrLen);

    vos_printf("\r\nVCom receive sn is           %d", g_stErrLogVcomDebugInfo.ulVCOMRcvSn);
    vos_printf("\r\nVCom receive num is           %d", g_stErrLogVcomDebugInfo.ulVCOMRcvNum);
    vos_printf("\r\nVCom receive Len is           %d", g_stErrLogVcomDebugInfo.ulVCOMRcvLen);

    vos_printf("\r\nVCom receive Error num is         %d", g_stErrLogVcomDebugInfo.ulVCOMRcvErrNum);
    vos_printf("\r\nVCom receive Error Len is         %d\r\n", g_stErrLogVcomDebugInfo.ulVCOMRcvErrLen);


    vos_printf("\r\nOM Rcv Err log msg num is         %d", g_stRcvUESendAP.ulErrLogRcvNum);
    vos_printf("\r\nOM Rcv Err log msg len is         %d", g_stRcvUESendAP.ulErrLogRcvLen);

    vos_printf("\r\nOM Rcv FTM msg num is         %d", g_stRcvUESendAP.ulFTMRcvNum);
    vos_printf("\r\nOM Rcv FTM msg len is         %d", g_stRcvUESendAP.ulFTMRcvLen);

    vos_printf("\r\nOM Send Err log msg num is         %d", g_stRcvUESendAP.ulErrLogSendNum);
    vos_printf("\r\nOM Send Err log msg len is         %d", g_stRcvUESendAP.ulErrLogSendLen);

    vos_printf("\r\nOM Send FTM msg num is         %d", g_stRcvUESendAP.ulFTMSendNum);
    vos_printf("\r\nOM Send FTM msg len is         %d\r\n", g_stRcvUESendAP.ulFTMSendLen);

    return;
}


VOS_VOID OM_AcpuRcvAPCtrl(VOS_UINT32 ultype,          VOS_UINT32 ulValuse,
                          VOS_UINT16 usModemID,       VOS_UINT8  ucAlmStatus,
                          VOS_UINT8  ucAlmLevel)
{
    APP_OM_CTRL_STATUS_STRU              stAppOmCtrlStatus;

    VOS_MemSet(&stAppOmCtrlStatus, 0, sizeof(stAppOmCtrlStatus));

    stAppOmCtrlStatus.stOmHeader.ulMsgType = ultype;
    stAppOmCtrlStatus.stOmHeader.ulMsgSN   = VOS_OK;
    stAppOmCtrlStatus.stOmHeader.ulMsgLen  = 2*sizeof(VOS_UINT32);
    stAppOmCtrlStatus.ulMsgModuleID        = ulValuse;
    stAppOmCtrlStatus.usModemID            = usModemID;
    stAppOmCtrlStatus.ucAlmStatus          = ucAlmStatus;
    stAppOmCtrlStatus.ucAlmLevel           = ucAlmLevel;

    OM_AcpuReadVComData(APP_VCOM_DEV_INDEX_ERRLOG, (VOS_UINT8*)&stAppOmCtrlStatus, sizeof(APP_OM_CTRL_STATUS_STRU));
}



VOS_VOID OM_AcpuReportErrLog(VOS_UINT16 usModemID, VOS_UINT16 usFaultId)
{
    APP_OM_REQ_ERR_LOG_STRU              stAppOmCtrlStatus;

    VOS_MemSet(&stAppOmCtrlStatus, 0, sizeof(stAppOmCtrlStatus));

    stAppOmCtrlStatus.stOmHeader.ulMsgType = 0x01;
    stAppOmCtrlStatus.stOmHeader.ulMsgSN   = 2;
    stAppOmCtrlStatus.stOmHeader.ulMsgLen  = 2*sizeof(VOS_UINT32);
    stAppOmCtrlStatus.ulMsgModuleID        = 0x01;
    stAppOmCtrlStatus.usModemID            = usModemID;
    stAppOmCtrlStatus.usFaultId            = usFaultId;

    OM_AcpuReadVComData(APP_VCOM_DEV_INDEX_ERRLOG, (VOS_UINT8*)&stAppOmCtrlStatus, sizeof(APP_OM_REQ_ERR_LOG_STRU));
}

#endif


VOS_VOID OM_AcpuErrLogMsgProc(MsgBlock* pMsg)
{
#if(FEATURE_ON == FEATURE_PTM)
    OM_RCV_DATA_INFO_STRU              *pstOmRcvDataInfo;

    pstOmRcvDataInfo = (OM_RCV_DATA_INFO_STRU*)pMsg;

    /* �ж���ϢID�Ƿ�Ϊ�涨��ϢID */
    if ((ID_OM_FTM_REPROT_IND != pstOmRcvDataInfo->ulMsgName)
         && (ID_OM_ERR_LOG_REPORT_CNF != pstOmRcvDataInfo->ulMsgName)
         && (ID_OM_FTM_REQUIRE_CNF != pstOmRcvDataInfo->ulMsgName)
         && (ID_OM_AUDIO_ERR_LOG_IND != pstOmRcvDataInfo->ulMsgName))
    {
        OM_ERR_LOG("OM_AcpuErrLogMsgProc: not error Log msg.\n");
        return ;
    }

    /*  �յ���Ϣ����Ƿ���Ҫ�ϱ� */
    if (VOS_OK != OM_AcpuRcvMsgCheck(pstOmRcvDataInfo))
    {
        OM_ERR_LOG("OM_AcpuErrLogMsgProc: rcv msg error!\r\n ");
        return ;
    }

    pstOmRcvDataInfo->stOmHeader.ulMsgSN = g_stErrLogVcomDebugInfo.ulVCOMSendSn++;

    OM_AcpuSendVComData((VOS_UINT8*)&pstOmRcvDataInfo->stOmHeader.ulMsgType,
                        pstOmRcvDataInfo->stOmHeader.ulMsgLen + sizeof(OM_ALARM_MSG_HEAD_STRU));

    if ((OM_ERR_LOG_MSG_ERR_REPORT == pstOmRcvDataInfo->stOmHeader.ulMsgType)
        && (OM_AP_SEND_MSG_FINISH == g_stOmAppMsgRecord.ulErrLogReportSend))
    {
        /* ͣ��ʱ�� */
        VOS_StopRelTimer(&g_AcpuErrLogFullTmr);
        OM_AcpuRcvMsgFinish();
    }

    OM_ERR_LOG("OM_AcpuErrLogMsgProc: rcv msg Send Seccussr\n ");

#endif

    return ;
}


VOS_INT OM_AcpuReadVComData(VOS_UINT8 ucDevIndex, VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
#if(FEATURE_ON == FEATURE_PTM)
    OM_ALARM_MSG_HEAD_STRU             *pstOmAlarmMsgHead;

    if (APP_VCOM_DEV_INDEX_ERRLOG != ucDevIndex)
    {
        OM_ERR_LOG1("\r\n OM_AcpuReadVComData:PhyPort port is error: %d\n", ucDevIndex);
        OM_AcpuSendAppResult(OM_APP_VCOM_DEV_INDEX_ERR, MODEM_ID_BUTT);

        return VOS_ERR;
    }

#if (VOS_LINUX == VOS_OS_VER)
     down(&g_stOmRxErrorLogBuffSem);
#endif

    g_stErrLogVcomDebugInfo.ulVCOMRcvNum++;
    g_stErrLogVcomDebugInfo.ulVCOMRcvLen += ulLen;

    if ((VOS_NULL_PTR == pucData) || (sizeof(APP_OM_CTRL_STATUS_STRU)> ulLen))
    {
        OM_ERR_LOG1("\r\n OM_AcpuReadVComData:Send data is NULL or len is error:%d\n", ulLen);
        OM_AcpuSendAppResult(OM_APP_MSG_LENGTH_ERR, MODEM_ID_BUTT);
#if (VOS_LINUX == VOS_OS_VER)
        up(&g_stOmRxErrorLogBuffSem);
#endif
        return VOS_ERR;
    }

    /*lint -e40*/
    OM_ACPU_DEBUG_TRACE((VOS_UINT8*)pucData, ulLen, OM_ACPU_ERRLOG_RCV);
    /*lint +e40*/

    /* ������Ϣͷ�ж��������� */
    pstOmAlarmMsgHead = (OM_ALARM_MSG_HEAD_STRU *)pucData;

    g_stErrLogVcomDebugInfo.ulVCOMRcvSn = pstOmAlarmMsgHead->ulMsgSN;

    if (OM_ERR_LOG_MSG_ON_OFF == pstOmAlarmMsgHead->ulMsgType)
    {
#if (VOS_LINUX == VOS_OS_VER)
        up(&g_stOmRxErrorLogBuffSem);
#endif
        return OM_AcpuSwitchOnOff(pucData, ulLen);
    }
    else if(OM_ERR_LOG_MSG_SET_ERR_REPORT == pstOmAlarmMsgHead->ulMsgType)
    {
#if (VOS_LINUX == VOS_OS_VER)
        up(&g_stOmRxErrorLogBuffSem);
#endif
        return OM_AcpuReportErrLogMsg(pucData, ulLen);
    }
    else if(OM_ERR_LOG_MSG_FTM_REQ == pstOmAlarmMsgHead->ulMsgType)
    {
#if (VOS_LINUX == VOS_OS_VER)
        up(&g_stOmRxErrorLogBuffSem);
#endif
        return OM_AcpuFTMMsgReq(pucData, ulLen);
    }
    else
    {
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrNum++;
        g_stErrLogVcomDebugInfo.ulVCOMRcvErrLen += ulLen;
        OM_ERR_LOG("\r\n OM_AcpuReadVComData:Recv msg type is err\n");
        OM_AcpuSendAppResult(OM_APP_MSG_TYPE_ERR, MODEM_ID_BUTT);
    }

#if (VOS_LINUX == VOS_OS_VER)
    up(&g_stOmRxErrorLogBuffSem);
#endif

#endif

    return VOS_ERR;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
