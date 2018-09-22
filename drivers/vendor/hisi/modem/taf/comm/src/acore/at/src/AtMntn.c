


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "AtMntn.h"
#include "AtInputProc.h"
#include "AtCtx.h"
#include "AtDataProc.h"
#if (FEATURE_ON == MBB_WPG_COMMON)
#include "MbbAtGuComm.h"
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_AT_MNTN_C
/*lint -e767 */

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
#if (FEATURE_OFF == MBB_WPG_COMMON)
AT_DEBUG_INFO_STRU                      g_stAtDebugInfo = {VOS_FALSE};
#endif
AT_RESET_STATS_INFO_STRU                g_stAtResetMntnInfo = {0};
AT_MNTN_STATS_STRU                      g_stAtStatsInfo;


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

VOS_VOID AT_SetPcuiCtrlConcurrentFlag(VOS_UINT8 ucFlag)
{
    g_stAtDebugInfo.ucPcuiCtrlConcurrentFlg = ucFlag;
}


VOS_UINT8 AT_GetPcuiCtrlConcurrentFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcuiCtrlConcurrentFlg;
}


VOS_VOID AT_SetPcuiPsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT16                          usClientId
)
{
    g_stAtDebugInfo.ucPcuiPsCallFlg = ucFlag;
    g_stAtDebugInfo.usUserClientId  = usClientId;
}


VOS_UINT8 AT_GetPcuiPsCallFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucPcuiPsCallFlg;
}


VOS_UINT16 AT_GetPcuiUserClientId(VOS_VOID)
{
    return g_stAtDebugInfo.usUserClientId;
}


VOS_VOID AT_SetCtrlPsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT16                          usClientId
)
{
    g_stAtDebugInfo.ucCtrlPsCallFlg     = ucFlag;
    g_stAtDebugInfo.usCtrlUserClientId  = usClientId;
}


VOS_UINT8 AT_GetCtrlPsCallFlag(VOS_VOID)
{
    return g_stAtDebugInfo.ucCtrlPsCallFlg;
}


VOS_UINT16 AT_GetCtrlUserClientId(VOS_VOID)
{
    return g_stAtDebugInfo.usCtrlUserClientId;
}


VOS_VOID AT_MNTN_TraceEvent(VOS_VOID *pMsg)
{
    if (VOS_OK != OM_AcpuTraceMsgHook(pMsg))
    {
        AT_WARN_LOG("AT_MNTN_TraceEvent: Trace MSG Fail!\r\n");
    }

    return;
}


VOS_VOID AT_MNTN_TraceInputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
)
{
    AT_MNTN_MSC_STRU                    stMntnMsc;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnMsc, ID_AT_MNTN_INPUT_MSC, (sizeof(AT_MNTN_MSC_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnMsc.ulPortId = ucIndex;
    PS_MEM_CPY(&(stMntnMsc.stDceMscInfo), pstDceMsc, sizeof(AT_DCE_MSC_STRU));

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnMsc);

    return;
}


VOS_VOID AT_MNTN_TraceOutputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
)
{
    AT_MNTN_MSC_STRU                    stMntnMsc;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnMsc, ID_AT_MNTN_OUTPUT_MSC, (sizeof(AT_MNTN_MSC_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnMsc.ulPortId = ucIndex;
    PS_MEM_CPY(&(stMntnMsc.stDceMscInfo), pstDceMsc, sizeof(AT_DCE_MSC_STRU));

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnMsc);

    return;
}


VOS_VOID AT_MNTN_TraceStartFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevive
)
{
    AT_MNTN_FLOW_CTRL_STRU              stMntnFlowCtrl;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnFlowCtrl, ID_AT_MNTN_START_FLOW_CTRL, (sizeof(AT_MNTN_FLOW_CTRL_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnFlowCtrl.ulPortId = ucIndex;
    stMntnFlowCtrl.enDevice = enFcDevive;

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnFlowCtrl);

    return;
}


VOS_VOID AT_MNTN_TraceStopFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevive
)
{
    AT_MNTN_FLOW_CTRL_STRU              stMntnFlowCtrl;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnFlowCtrl, ID_AT_MNTN_STOP_FLOW_CTRL, (sizeof(AT_MNTN_FLOW_CTRL_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnFlowCtrl.ulPortId = ucIndex;
    stMntnFlowCtrl.enDevice = enFcDevive;

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnFlowCtrl);

    return;
}


VOS_VOID AT_MNTN_TraceRegFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
)
{
    AT_MNTN_FC_POINT_STRU               stMntnFcPoint;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnFcPoint, ID_AT_MNTN_REG_FC_POINT, (sizeof(AT_MNTN_FC_POINT_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnFcPoint.ulPortId = ucIndex;
    stMntnFcPoint.enPoint  = enFcPoint;

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnFcPoint);

    return;
}


VOS_VOID AT_MNTN_TraceDeregFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
)
{
    AT_MNTN_FC_POINT_STRU               stMntnFcPoint;

    /* ��д��Ϣͷ */
    AT_MNTN_CFG_MSG_HDR(&stMntnFcPoint, ID_AT_MNTN_DEREG_FC_POINT, (sizeof(AT_MNTN_FC_POINT_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    stMntnFcPoint.ulPortId = ucIndex;
    stMntnFcPoint.enPoint  = enFcPoint;

    /* ������Ϣ */
    AT_MNTN_TraceEvent(&stMntnFcPoint);

    return;
}


VOS_VOID AT_MNTN_TraceCmdResult(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen
)
{
    AT_MSG_STRU                        *pstMsg;
    AT_INTER_MSG_ID_ENUM_UINT32         enEventId;
    VOS_UINT32                          ulLength;

    AT_GetAtMsgStruMsgLength(usDataLen, &ulLength);

    /* ������Ϣ�ڴ� */
    pstMsg = (AT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, (ulLength + VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("AT_MNTN_TraceCmdResult:ERROR:Alloc Mem Fail.");
        return;
    }

    /* ��д��Ϣͷ */
    enEventId       = AT_GetResultMsgID(ucIndex);
    AT_MNTN_CFG_MSG_HDR(pstMsg, enEventId, ulLength);

    /* ��д��Ϣ���� */
    pstMsg->ucType  = 0x1;
    pstMsg->ucIndex = ucIndex;
    pstMsg->usLen   = usDataLen;

    AT_GetUserTypeFromIndex(ucIndex, &pstMsg->ucUserType);
    PS_MEM_SET(pstMsg->aucReserved, 0x00, sizeof(pstMsg->aucReserved));
    PS_MEM_CPY((TAF_VOID*)pstMsg->aucValue, pucData, usDataLen);

    /* ��д��Ϣ���� */
    AT_MNTN_TraceEvent(pstMsg);

    /* �ͷ���Ϣ�ڴ� */
    PS_MEM_FREE(WUEPS_PID_AT, pstMsg);

    return;
}


VOS_VOID AT_MNTN_TraceCmdBuffer(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen
)
{
    AT_MSG_STRU                        *pstMsg;
    AT_INTER_MSG_ID_ENUM_UINT32         enEventId;
    VOS_UINT32                          ulLength;

    AT_GetAtMsgStruMsgLength(usDataLen, &ulLength);

    /* ������Ϣ�ڴ� */
    pstMsg = (AT_MSG_STRU *)PS_MEM_ALLOC(WUEPS_PID_AT, (ulLength + VOS_MSG_HEAD_LENGTH));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_ERR_LOG("AT_MNTN_TraceCmdBuffer:ERROR:Alloc Mem Fail.");
        return;
    }

    /* ��д��Ϣͷ */
    enEventId       = AT_GetResultMsgID(ucIndex);
    AT_MNTN_CFG_MSG_HDR(pstMsg, enEventId, ulLength);

    /* ��д��Ϣ���� */
    pstMsg->ucType          = 0x2;
    pstMsg->ucIndex         = ucIndex;
    pstMsg->usLen           = usDataLen;

    AT_GetUserTypeFromIndex(ucIndex, &pstMsg->ucUserType);
    PS_MEM_SET(pstMsg->aucReserved, 0x00, sizeof(pstMsg->aucReserved));
    PS_MEM_CPY((TAF_VOID*)pstMsg->aucValue, pucData, usDataLen);

    /* ��д��Ϣ���� */
    AT_MNTN_TraceEvent(pstMsg);

    /* �ͷ���Ϣ�ڴ� */
    PS_FREE_MSG(WUEPS_PID_AT, pstMsg);

    return;
}


VOS_VOID AT_MNTN_TraceContextData(VOS_VOID)
{
    NAS_AT_SDT_AT_PART_ST                  *pstSndMsgCB     = VOS_NULL_PTR;
    NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST *pstOutsideCtx   = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU                  *pstSmsCtx       = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                    enModemId;

    pstSndMsgCB = (NAS_AT_SDT_AT_PART_ST *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                            sizeof(NAS_AT_SDT_AT_PART_ST));

    if (VOS_NULL_PTR == pstSndMsgCB)
    {
        AT_ERR_LOG("AT_MNTN_TraceContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstSndMsgCB->ulReceiverPid      = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderPid        = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulLength           = sizeof(NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST) + 4;
    pstSndMsgCB->ucType             = AT_PC_REPLAY_MSG;
    pstSndMsgCB->enMsgID            = ID_AT_MNTN_PC_REPLAY_MSG;
    pstSndMsgCB->aucReserved[0]     = 0;
    pstSndMsgCB->aucReserved[1]     = 0;
    pstSndMsgCB->aucReserved[2]     = 0;


    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        pstSmsCtx                           = AT_GetModemSmsCtxAddrFromModemId(enModemId);
        pstOutsideCtx                       = &pstSndMsgCB->astOutsideCtx[enModemId];

        pstOutsideCtx->gucAtCscsType        = gucAtCscsType;
        pstOutsideCtx->gucAtCsdhType        = pstSmsCtx->ucCsdhType;
        pstOutsideCtx->g_OpId               = g_OpId;
        pstOutsideCtx->g_enAtCsmsMsgVersion = pstSmsCtx->enCsmsMsgVersion;
        pstOutsideCtx->g_enAtCmgfMsgFormat  = pstSmsCtx->enCmgfMsgFormat;

        PS_MEM_CPY(&pstOutsideCtx->gstAtCnmiType,
                   &(pstSmsCtx->stCnmiType),
                   sizeof(pstSmsCtx->stCnmiType));

        PS_MEM_CPY(&pstOutsideCtx->g_stAtCgsmsSendDomain,
                   &(pstSmsCtx->stCgsmsSendDomain),
                   sizeof(pstSmsCtx->stCgsmsSendDomain));

        PS_MEM_CPY(&pstOutsideCtx->g_stAtCscaCsmpInfo,
                   &(pstSmsCtx->stCscaCsmpInfo),
                   sizeof(pstSmsCtx->stCscaCsmpInfo));

        PS_MEM_CPY(&pstOutsideCtx->g_stAtCpmsInfo,
                   &(pstSmsCtx->stCpmsInfo),
                   sizeof(pstSmsCtx->stCpmsInfo));

    }

    AT_MNTN_TraceEvent(pstSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_AT, pstSndMsgCB);

    return;
}


VOS_VOID AT_MNTN_TraceClientData(VOS_VOID)
{
    NAS_AT_SDT_AT_CLIENT_TABLE_STRU         *pstSndMsgCB;
    TAF_UINT8                               ucLoop;

    pstSndMsgCB = (NAS_AT_SDT_AT_CLIENT_TABLE_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT,
                                            sizeof(NAS_AT_SDT_AT_CLIENT_TABLE_STRU));

    if ( VOS_NULL_PTR == pstSndMsgCB )
    {
        AT_ERR_LOG("AT_MNTN_TraceClientData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstSndMsgCB->ulReceiverPid      = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderPid        = WUEPS_PID_AT;
    pstSndMsgCB->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstSndMsgCB->ulLength           = sizeof(NAS_AT_SDT_AT_CLIENT_TABLE_STRU) - 20;
    pstSndMsgCB->enMsgID            = ID_AT_MNTN_PC_REPLAY_CLIENT_TAB;
    pstSndMsgCB->ucType             = AT_PC_REPLAY_MSG_CLIENT_TAB;
    pstSndMsgCB->aucReserved[0]     = 0;
    pstSndMsgCB->aucReserved[1]     = 0;
    pstSndMsgCB->aucReserved[2]     = 0;

    for (ucLoop = 0; ucLoop < AT_MAX_CLIENT_NUM; ucLoop++)
    {
        pstSndMsgCB->gastAtClientTab[ucLoop].usClientId   = gastAtClientTab[ucLoop].usClientId;
        pstSndMsgCB->gastAtClientTab[ucLoop].opId         = gastAtClientTab[ucLoop].opId;
        pstSndMsgCB->gastAtClientTab[ucLoop].ucUsed       = gastAtClientTab[ucLoop].ucUsed;
        pstSndMsgCB->gastAtClientTab[ucLoop].UserType     = gastAtClientTab[ucLoop].UserType;
        pstSndMsgCB->gastAtClientTab[ucLoop].Mode         = gastAtClientTab[ucLoop].Mode;
        pstSndMsgCB->gastAtClientTab[ucLoop].IndMode      = gastAtClientTab[ucLoop].IndMode;
    }

    AT_MNTN_TraceEvent(pstSndMsgCB);

    PS_FREE_MSG(WUEPS_PID_AT, pstSndMsgCB);

    return;
}


VOS_VOID AT_InitHsUartStats(VOS_VOID)
{
    PS_MEM_SET(&g_stAtStatsInfo.stHsUartStats, 0x00, sizeof(AT_MNTN_HSUART_STATS_STRU));
    return;
}


VOS_VOID AT_InitModemStats(VOS_VOID)
{
    PS_MEM_SET(&g_stAtStatsInfo.stModemStats, 0x00, sizeof(AT_MNTN_MODEM_STATS_STRU));
    return;
}

#if (FEATURE_ON == FEATURE_AT_HSUART)

VOS_VOID AT_ShowHsUartConfigInfo(VOS_VOID)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;
    AT_UART_FLOW_CTRL_STRU             *pstFlowCtrl = VOS_NULL_PTR;
    AT_UART_RI_CFG_STRU                *pstUartRiCfgInfo = VOS_NULL_PTR;
    AT_UART_PHY_CFG_STRU               *pstUartPhyCfgInfo = VOS_NULL_PTR;
    AT_UART_FORMAT_PARAM_STRU          *pstFormatParam = VOS_NULL_PTR;
    VOS_CHAR                            acParityStr[][20] = {"ODD", "EVEN", "MARK", "SPACE", "NONE"};
    VOS_CHAR                            acDcdStr[][20] = {"ALWAYS ON", "CONNECT ON"};
    VOS_CHAR                            acDtrStr[][20] = {"IGNORE", "SWITCH CMD MODE", "HANGUP CALL"};
    VOS_CHAR                            acDsrStr[][20] = {"ALWAYS ON", "CONNECT ON"};
    VOS_CHAR                            acDceByDteStr[][20] = {"NONE", "XON OR XOFF REMOVE", "RTS", "XON_OR_XOFF_PASS"};
    VOS_CHAR                            acDteByDceStr[][20] = {"NONE", "XON OR XOFF REMOVE", "CTS"};

    pstLineCtrl       = AT_GetUartLineCtrlInfo();
    pstFlowCtrl       = AT_GetUartFlowCtrlInfo();
    pstUartRiCfgInfo  = AT_GetUartRiCfgInfo();
    pstUartPhyCfgInfo = AT_GetUartPhyCfgInfo();
    pstFormatParam    = AT_HSUART_GetFormatParam(pstUartPhyCfgInfo->stFrame.enFormat);

    vos_printf("====================================\r\n");
    vos_printf("[1] HSUART PHY                      \r\n");
    vos_printf("====================================\r\n");
    vos_printf("BaudRate:                   %d\r\n", pstUartPhyCfgInfo->enBaudRate);
    vos_printf("Format:                     %d\r\n", pstUartPhyCfgInfo->stFrame.enFormat);
    vos_printf("->Data Bit Length:          %d\r\n", pstFormatParam->enDataBitLength);
    vos_printf("->Stop Bit Length:          %d\r\n", pstFormatParam->enStopBitLength);
    vos_printf("->Parity Bit Length:        %d\r\n", pstFormatParam->enParityBitLength);
    vos_printf("Parity Type:                %s\r\n", acParityStr[pstUartPhyCfgInfo->stFrame.enParity]);
    vos_printf("====================================\r\n");
    vos_printf("[2] HSUART LINE                     \r\n");
    vos_printf("====================================\r\n");
    vos_printf("DCD[%d]:                    %s\r\n", pstLineCtrl->enDcdMode, acDcdStr[pstLineCtrl->enDcdMode]);
    vos_printf("DTR[%d]:                    %s\r\n", pstLineCtrl->enDtrMode, acDtrStr[pstLineCtrl->enDtrMode]);
    vos_printf("DSR[%d]:                    %s\r\n", pstLineCtrl->enDsrMode, acDsrStr[pstLineCtrl->enDsrMode]);
    vos_printf("====================================\r\n");
    vos_printf("[3] HSUART FLOW CTRL                \r\n");
    vos_printf("====================================\r\n");
    vos_printf("DCE BY DTE[%d]:             %s\r\n", pstFlowCtrl->enDceByDte, acDceByDteStr[pstFlowCtrl->enDceByDte]);
    vos_printf("DTE BY DCE[%d]:             %s\r\n", pstFlowCtrl->enDteByDce, acDteByDceStr[pstFlowCtrl->enDteByDce]);
    vos_printf("====================================\r\n");
    vos_printf("[4] HSUART RI                       \r\n");
    vos_printf("====================================\r\n");
    vos_printf("SMS RI ON (ms):             %u\r\n", pstUartRiCfgInfo->ulSmsRiOnInterval);
    vos_printf("SMS RI OFF (ms):            %u\r\n", pstUartRiCfgInfo->ulSmsRiOffInterval);
    vos_printf("VOICE RI ON (ms):           %u\r\n", pstUartRiCfgInfo->ulVoiceRiOnInterval);
    vos_printf("VOICE RI OFF (ms):          %u\r\n", pstUartRiCfgInfo->ulVoiceRiOffInterval);
    vos_printf("VOICE RI Cycle Times:       %d\r\n", pstUartRiCfgInfo->ucVoiceRiCycleTimes);

    return;
}


VOS_VOID AT_ShowHsUartNvStats(VOS_VOID)
{
    vos_printf("====================================\r\n");
    vos_printf("HSUART NV STATS                     \r\n");
    vos_printf("====================================\r\n");
    vos_printf("Read NV Fail NUM:           %d\r\n", g_stAtStatsInfo.stHsUartStats.ucReadNvFailNum);
    vos_printf("Write NV Fail NUM:          %d\r\n", g_stAtStatsInfo.stHsUartStats.ucWriteNvFailNum);
    vos_printf("BaudRate Invalid NUM:       %d\r\n", g_stAtStatsInfo.stHsUartStats.ucBaudRateERR);
    vos_printf("Format Invalid NUM:         %d\r\n", g_stAtStatsInfo.stHsUartStats.ucFormatERR);

    return;
}


VOS_VOID AT_ShowHsUartIoctlStats(VOS_VOID)
{
    vos_printf("====================================\r\n");
    vos_printf("HSUART IOCTL STATS                  \r\n");
    vos_printf("====================================\r\n");
    vos_printf("Set Read CB ERR:            %d\r\n", g_stAtStatsInfo.stHsUartStats.ucSetReadCbERR);
    vos_printf("Relloc Read BUFF ERR:       %d\r\n", g_stAtStatsInfo.stHsUartStats.ucRellocReadBuffERR);
    vos_printf("Set Free CB ERR:            %d\r\n", g_stAtStatsInfo.stHsUartStats.ucSetFreeBuffCbERR);
    vos_printf("Set MSC Read CB ERR:        %d\r\n", g_stAtStatsInfo.stHsUartStats.ucSetMscReadCbERR);
    vos_printf("Set Switch CB ERR:          %d\r\n", g_stAtStatsInfo.stHsUartStats.ucSetSwitchCmdCbERR);
    vos_printf("Set BaudRate FAIL NUM:      %d\r\n", g_stAtStatsInfo.stHsUartStats.ulSetBaudRateFailNum);
    vos_printf("Set WLEN FAIL NUM:          %d\r\n", g_stAtStatsInfo.stHsUartStats.ulSetWlenFailNum);
    vos_printf("Set STP FAIL NUM:           %d\r\n", g_stAtStatsInfo.stHsUartStats.ulSetStpFailNum);
    vos_printf("Set PARITY FAIL NUM:        %d\r\n", g_stAtStatsInfo.stHsUartStats.ulSetParityFailNum);
    vos_printf("Config FLOW CTL FAIL NUM:   %d\r\n", g_stAtStatsInfo.stHsUartStats.ulConFlowCtrlErr);
    vos_printf("MSC Read CB NUM:            %d\r\n", g_stAtStatsInfo.stHsUartStats.ulMscReadCBNum);
    vos_printf("MSC Write SUCC NUM:         %d\r\n", g_stAtStatsInfo.stHsUartStats.ulMscWriteSuccNum);
    vos_printf("MSC Write FAIL NUM:         %d\r\n", g_stAtStatsInfo.stHsUartStats.ulMscWriteFailNum);
    vos_printf("MSC Switch CMD CB NUM:      %d\r\n", g_stAtStatsInfo.stHsUartStats.ulSwitchCmdCBNum);

    return;
}


VOS_VOID AT_ShowHsUartDataStats(VOS_VOID)
{
    vos_printf("====================================\r\n");
    vos_printf("HSUART UL DATA STATS                \r\n");
    vos_printf("====================================\r\n");
    vos_printf("UL Read CB NUM:             %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlDataReadCBNum);
    vos_printf("UL RD SUCC NUM:             %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlGetRDSuccNum);
    vos_printf("UL RD Fail NUM:             %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlGetRDFailNum);
    vos_printf("UL Invalid RD NUM:          %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlInvalidRDNum);
    vos_printf("UL Invalid CMD DATA NUM:    %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlRcvInvalidCmdNum);
    vos_printf("UL Valid CMD DATA NUM:      %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlValidCmdNum);
    vos_printf("UL IP Data NUM:             %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlIpDataNum);
    vos_printf("UL PPP Data NUM:            %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlPppDataNum);
    vos_printf("UL CSD Data NUM:            %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlOmDataNum);
    vos_printf("UL OM Data NUM:             %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlOmDataNum);
    vos_printf("UL DIAG Data NUM:           %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlDiagDataNum);
    vos_printf("UL Invalid MODE DATA NUM:   %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlInvalidModeDataNum);
    vos_printf("UL Retrun BUFF SUCC NUM:    %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffSuccNum);
    vos_printf("UL Retrun BUFF FAIL NUM:    %d\r\n", g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffFailNum);
    vos_printf("====================================\r\n");
    vos_printf("HSUART DL DATA STATS                \r\n");
    vos_printf("====================================\r\n");
    vos_printf("DL Write Async SUCC NUM:    %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncSuccNum);
    vos_printf("DL Write Async FAIL NUM:    %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncFailNum);
    vos_printf("DL Write Sync SUCC NUM:     %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccNum);
    vos_printf("DL Write Sync FAIL NUM:     %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailNum);
    vos_printf("DL Write Sync SUCC LEN:     %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen);
    vos_printf("DL Write Sync FAIL LEN:     %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailLen);
    vos_printf("DL Free BUFF NUM:           %d\r\n", g_stAtStatsInfo.stHsUartStats.ulDlFreeBuffNum);

    return;
}


VOS_VOID AT_ShowHsUartFcState(VOS_VOID)
{
    VOS_CHAR                            acFcStateStr[][20] = {"START", "STOP"};
    AT_IO_LEVEL_ENUM_UINT8              enIoLevel;

    enIoLevel = AT_GetIoLevel(AT_CLIENT_TAB_HSUART_INDEX, IO_CTRL_CTS);

    vos_printf("====================================\r\n");
    vos_printf("HSUART FLOW CTRL STATE              \r\n");
    vos_printf("====================================\r\n");
    vos_printf("FLOW CTRL STATE:            %s\r\n", acFcStateStr[enIoLevel]);

    return;
}
#endif


VOS_VOID AT_ShowModemDataStats(VOS_VOID)
{
    vos_printf("====================================\r\n");
    vos_printf("MODEM UL DATA STATS                 \r\n");
    vos_printf("====================================\r\n");
    vos_printf("UL Read CB NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlDataReadCBNum);
    vos_printf("UL RD SUCC NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlGetRDSuccNum);
    vos_printf("UL RD Fail NUM:             %d\r\n", g_stAtStatsInfo.stModemStats.ulUlGetRDFailNum);
    vos_printf("UL Invalid RD NUM:          %d\r\n", g_stAtStatsInfo.stModemStats.ulUlInvalidRDNum);
    vos_printf("UL Retrun BUFF SUCC NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulUlReturnBuffSuccNum);
    vos_printf("UL Retrun BUFF FAIL NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulUlReturnBuffFailNum);
    vos_printf("====================================\r\n");
    vos_printf("MODEM DL DATA STATS                 \r\n");
    vos_printf("====================================\r\n");
    vos_printf("DL Write Async SUCC NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulDlWriteAsyncSuccNum);
    vos_printf("DL Write Async FAIL NUM:    %d\r\n", g_stAtStatsInfo.stModemStats.ulDlWriteAsyncFailNum);
    vos_printf("DL Free BUFF NUM:           %d\r\n", g_stAtStatsInfo.stModemStats.ulDlFreeBuffNum);


    return;
}


VOS_VOID AT_ShowPsEntityInfo(VOS_UINT8 ucCallId)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucIpv6PrimDnsStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucIpv6SecDnsStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
#endif

    for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
    {
        vos_printf("################MODEM ID is %d################\n", enModemId);
        pstCallEntity = &(AT_GetModemPsCtxAddrFromModemId(enModemId)->astCallEntity[ucCallId]);

        vos_printf("********************PS����ʵ����Ϣ***********************\n");
        vos_printf("Active Flag                             %d\n", pstCallEntity->ulUsedFlg);
        vos_printf("Current Call Type                       %d\n", pstCallEntity->enCurrPdpType);
        vos_printf("********************�û�������Ϣ*************************\n");
        vos_printf("User Actual Index                       %d\n", pstCallEntity->stUserInfo.enPortIndex);
        vos_printf("User Expect Index                       %d\n", pstCallEntity->stUserInfo.enUserIndex);
        vos_printf("User Type                               %d\n", pstCallEntity->stUserInfo.ucUsrType);
        vos_printf("User CID                                %d\n", pstCallEntity->stUserInfo.ucUsrCid);
        vos_printf("********************IPv4������Ϣ*************************\n");
        vos_printf("IPv4 Bearer CID                         %d\n", pstCallEntity->ucIpv4Cid);
        vos_printf("IPv4 Bearer State                       %d\n", pstCallEntity->enIpv4State);
        vos_printf("IPv4 Bearer ID (RAB ID)                 %d\n", pstCallEntity->stIpv4DhcpInfo.ucRabId);
        vos_printf("IPv4 Bearer Address                     0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4Addr);
        vos_printf("IPv4 Bearer Primary DNS                 0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4PrimDNS);
        vos_printf("IPv4 Bearer Secondary DNS               0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4SecDNS);
        vos_printf("IPv4 Bearer Gate Way                    0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4GateWay);
        vos_printf("IPv4 Bearer NET Mask                    0x%x\n", pstCallEntity->stIpv4DhcpInfo.ulIpv4NetMask);
        vos_printf("***********************************************************\n");

#if (FEATURE_ON == FEATURE_IPV6)
        PS_MEM_SET(aucIpv6AddrStr, 0x00, sizeof(aucIpv6AddrStr));
        PS_MEM_SET(aucIpv6PrimDnsStr, 0x00, sizeof(aucIpv6PrimDnsStr));
        PS_MEM_SET(aucIpv6SecDnsStr, 0x00, sizeof(aucIpv6SecDnsStr));

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6PrimDnsStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6PrimDNS,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        AT_ConvertIpv6AddrToCompressedStr(aucIpv6SecDnsStr,
                                          pstCallEntity->stIpv6DhcpInfo.aucIpv6SecDNS,
                                          TAF_IPV6_STR_RFC2373_TOKENS);

        vos_printf("********************IPv6������Ϣ*************************\n");
        vos_printf("IPv6 Bearer CID                         %d\n", pstCallEntity->ucIpv6Cid);
        vos_printf("IPv6 Bearer State                       %d\n", pstCallEntity->enIpv6State);
        vos_printf("***********************************************************\n");
        vos_printf("IPv6 Bearer ID (RAB ID)                 %d\n", pstCallEntity->stIpv6DhcpInfo.ucRabId);
        vos_printf("IPv6 Bearer Global Address              %s\n", aucIpv6AddrStr);
        vos_printf("IPv6 Bearer Primary DNS                 %s\n", aucIpv6PrimDnsStr);
        vos_printf("IPv6 Bearer Secondary DNS               %s\n", aucIpv6SecDnsStr);
        vos_printf("***********************************************************\n");
#endif
    }

    return;
}


VOS_VOID AT_ShowPsFcIdState(VOS_UINT32 ulFcid)
{
    if (ulFcid >= FC_ID_BUTT)
    {
        vos_printf("AT_ShowFcStatsInfo: Fcid overtop, ulFcid = %d\n", ulFcid);
        return;
    }

    vos_printf("ָ��FCID��Ӧ�Ľ���Ƿ���Ч                  %d\n", g_stFcIdMaptoFcPri[ulFcid].ulUsed);
    vos_printf("ָ��FCID��Ӧ�Ľ������ȼ�                  %d\n", g_stFcIdMaptoFcPri[ulFcid].ulFcPri);
    vos_printf("ָ��FCID��Ӧ�Ľ���RABID����               %d\n", g_stFcIdMaptoFcPri[ulFcid].ulRabIdMask);
    vos_printf("ָ��FCID��Ӧ�Ľ���ModemId                 %d\n", g_stFcIdMaptoFcPri[ulFcid].enModemId);
    vos_printf("\r\n");

    return;
}


VOS_VOID AT_ShowResetStatsInfo(VOS_VOID)
{
    vos_printf("ģ���ʼ����ʶ                              %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulSemInitFlg);
    vos_printf("��ǰ�Ķ������ź���                          %x\n", AT_GetResetSem());
    vos_printf("�����Ķ������ź���                          %x\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulBinarySemId);
    vos_printf("�����������ź���ʧ�ܴ���                    %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulCreateBinarySemFailNum);
    vos_printf("���������ź���ʧ�ܴ���                      %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulLockBinarySemFailNum);
    vos_printf("���һ�����������ź���ʧ��ԭ��              %x\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulLastBinarySemErrRslt);
    vos_printf("C�˸�λǰ�Ĵ���                             %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulResetBeforeNum);
    vos_printf("C�˸�λ��Ĵ���                             %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulResetAfterNum);
    vos_printf("HIFI��λ�ɹ��Ĵ���                          %d\n", g_stAtStatsInfo.stCCpuResetStatsInfo.ulHifiResetNum);
    vos_printf("AT��λ״̬                                  %d\n", AT_GetResetFlag());
    vos_printf("\r\n");

    return;
}


VOS_VOID AT_ShowAllClientState(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_CHAR                            acStateStr[][20] = {"READY", "PEND"};
    VOS_CHAR                            acModeStr[][20] = {"CMD", "DATA", "ONLINE_CMD"};

    vos_printf("\r\n The All Client State: \r\n");

    for (i = 0; i < AT_MAX_CLIENT_NUM; i++)
    {
        vos_printf("Client[%d] State: %s    Mode: %s\r\n", i,
            acStateStr[g_stParseContext[i].ucClientStatus], acModeStr[gastAtClientTab[i].Mode]);
    }

    return;
}


VOS_VOID AT_SetClientState(VOS_UINT8 ucIndex, VOS_UINT8 ucState)
{
    if ((ucIndex >= AT_MAX_CLIENT_NUM)||(ucState > AT_FW_CLIENT_STATUS_PEND))
    {
        return;
    }

    g_stParseContext[ucIndex].ucClientStatus = ucState;

    return;
}


VOS_VOID AT_SetClientMode(VOS_UINT8 ucIndex, VOS_UINT8 ucMode)
{
    if ((ucIndex >= AT_MAX_CLIENT_NUM)||(ucMode > AT_ONLINE_CMD_MODE))
    {
        return;
    }

    gastAtClientTab[ucIndex].Mode = ucMode;

    return;
}


VOS_VOID AT_ShowUsedClient(VOS_VOID)
{
    AT_PORT_BUFF_CFG_STRU              *pstPortCfg;
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           i;
    VOS_CHAR                            acStateStr[][20] = {"READY", "PEND"};
    VOS_CHAR                            acModeStr[][20] = {"CMD", "DATA", "ONLINE_CMD"};

    pstPortCfg = AT_GetPortBuffCfgInfo();

    vos_printf("\r\n The All Used Client State: \r\n");
    for (i = 0; i < pstPortCfg->ucNum; i++)
    {
        ulIndex = pstPortCfg->ulUsedClientID[i];
        vos_printf("Client[%d] State: %s    Mode: %s\r\n", ulIndex,
            acStateStr[g_stParseContext[ulIndex].ucClientStatus], acModeStr[gastAtClientTab[ulIndex].Mode]);
    }

    return;
}




VOS_VOID AT_Help(VOS_VOID)
{
    vos_printf("********************************************************\n");
    vos_printf("PS�����Ϣ                                              \n");
    vos_printf("********************************************************\n");
    vos_printf("AT_ShowPsEntityInfo         ��ʾ����ʵ����Ϣ            \n");
    vos_printf("AT_ShowPsFcIdState(ulFcid)  ��ʾ���ص�״̬��Ϣ          \n");
    vos_printf("********************************************************\n");
    vos_printf("UART�����Ϣ                                            \n");
    vos_printf("********************************************************\n");
    vos_printf("AT_ShowHsUartConfigInfo     ��ʾHSUART��������Ϣ        \n");
    vos_printf("AT_ShowHsUartNvStats        ��ʾHSUART��NV��дͳ����Ϣ  \n");
    vos_printf("AT_ShowHsUartIoctlStats     ��ʾHSUART��IOCTLͳ����Ϣ   \n");
    vos_printf("AT_ShowHsUartDataStats      ��ʾHSUART������ͳ����Ϣ    \n");
    vos_printf("AT_ShowHsUartFcState        ��ʾHSUART������״̬��Ϣ    \n");
    vos_printf("********************************************************\n");
    vos_printf("MODEM�����Ϣ                                           \n");
    vos_printf("********************************************************\n");
    vos_printf("AT_ShowModemDataStats       ��ʾMODEM������ͳ����Ϣ     \n");
    vos_printf("********************************************************\n");
    vos_printf("���������Ϣ                                            \n");
    vos_printf("********************************************************\n");
    vos_printf("AT_ShowResetStatsInfo       ��ʾAT��λ״̬��Ϣ          \n");
    vos_printf("AT_ShowAllClientState       �鿴�˿�״̬��Ϣ            \n");

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


