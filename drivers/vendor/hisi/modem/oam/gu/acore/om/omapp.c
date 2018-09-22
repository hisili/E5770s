
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "om.h"
#include "OmApp.h"
#include "omprivate.h"
#include "DrvInterface.h"
#include "pslog.h"
#include "omsdlog.h"
#include "cpm.h"
#include "Omappagent.h"
#include "NVIM_Interface.h"
#include "DrvInterface.h"
#include "OamSpecTaskDef.h"
#include "GU_MSPComm.h"
#include "omappoperator.h"
#include "OmAppRl.h"
#include "omnvinterface.h"
#include "TafNvInterface.h"
#include "FileSysInterface.h"
#include "DrvNvInterface.h"

#if (RAT_MODE != RAT_GU)
#include "msp_nvim.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*lint -e767 �޸��ˣ�����47350�������ˣ�����46160��ԭ�������LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_ACPU_OM_C
/*lint +e767 �޸��ˣ�����47350�������ˣ�lixiao��*/

/*caution: no more 30 char */
#define OAM_PLATFORM_VERSION "V700R001C01B010"

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*��������TRACE��EVENT�ϱ��Ĺ�����Ϣ*/
OM_TRACE_EVENT_CONFIG_PS_STRU           g_stAcpuTraceEventConfig;

/*���кţ�����TRACE,EVENT��Ϣ�����*/
/*VOS_UINT32                            g_ulAcpuOMMsgSN         = 1;*/
#if ( (VOS_LINUX == VOS_OS_VER) || (VOS_WIN32 == VOS_OS_VER) )
atomic_t                                g_ulAcpuOMMsgSN;
#endif

/*���浱ǰ�Ĺ���ID��*/
VOS_UINT16                              g_usAcpuToolId          = 0;

/* ����ͬ��NV��д��ErrorLog�������,��֤ÿ��ֻ��һ�������ڽ��в���*/
VOS_UINT32                              g_ulOmAcpuSyncSem;

/* �������ź����������ȴ����ؽ�� */
VOS_UINT32                              g_ulOmAcpuCnfSem;

/*�����ź�������������OM HSIC���� */
VOS_UINT32                              g_ulOmAcpuHsicSem;

/* ����ظ���Ϣ��ָ�� */
MsgBlock                               *g_pstOmAcpuCnfMsg  = VOS_NULL_PTR;

/*OM BUF FULL �����ϱ�CPU��Ϣ��ʱ��*/
HTIMER                                  g_stAcpuRegularBufFullTmr = VOS_NULL_PTR ;

/* HSIC��OM����״̬��Ĭ��Ϊ������ */
OM_HSIC_PORT_STATUS_ENUM_UINT32         g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_OFF;

/*����OMͨ����·��״̬�������Ƿ��������ͨ��*/
VOS_UINT32                              g_ulAcpuOMSwitchOnOff = OM_STATE_IDLE;

/* ��¼�յ���Ϣ��Ϣ��buffer����ǰ���� */
OM_RECORD_BUF_STRU                      g_astAcpuRecordInfo[VOS_EXC_DUMP_MEM_NUM_BUTT];

/* ��¼CCORE ��ǰ״̬*/
OM_CPU_STATUS_INFO                      g_astCcoreStatus[OM_CPU_STATUS_BUTT];

/* ��¼ICC�˼���Ϣ�ļ�·�� */
VOS_CHAR                                g_acICCLogFilePath[OM_ICC_MAX_NAME_LEN];

#if (FEATURE_ON == FEATURE_MULTI_FS_PARTITION)
#define  OM_ICC_LOG_PATH                "/data/modemlog/Log/Icc-log"
#define  OM_ICC_UNITARY_LOG_PATH        "/modem_log/Log/Icc-log"
#else
#define  OM_ICC_LOG_PATH                "/yaffs0/Log/Icc-log"
#define  OM_ICC_UNITARY_LOG_PATH        "/modem_log/Log/Icc-log"
#endif

/* ��¼ICC�˼���Ϣ�ļ�����ֵ��Ĭ��0 */
VOS_UINT32                              g_ulICCLogFileIndex;

/* ��¼ICC�˼���ϢBUFF */
OM_ICC_INFO_STRU                        g_astIccRecordInfo[OAM_ICC_RECORD_MAX_NUM];

/* ��¼ICC�˼���Ϣ����ֵ */
VOS_UINT32                              g_ulIccRecordIndex = 0;

/* ��¼ICC�˼���Ϣ��ʱ�� */
HTIMER                                  g_AcpuIccLogTimerId;

#define NO_CONFIG_BIT                   (0)
#define TRACE_CONFIG_BIT                (BIT_N(0))
#define EVENT_CONFIG_BIT                (BIT_N(1))
#define TRACE_MASK_CONFIG_BIT           (BIT_N(2))


/*****************************************************************************
  3 ��������
*****************************************************************************/
extern VOS_VOID   Log_AcpuOmMsgProc(OM_REQ_PACKET_STRU *pRspPacket, OM_RSP_FUNC *pRspFuncPtr);
extern VOS_UINT32 WuepsDiagPidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_VOID   DIAG_AcpuMsgProc(struct MsgCB *pMsg);

extern VOS_UINT32 WuepsPBPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase);
extern VOS_VOID   SI_PB_PidMsgProc(struct MsgCB *pstPBMsg);

extern VOS_UINT32 OM_AcpuAgentPidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_VOID   OM_AcpuAgentMsgProc(MsgBlock* pMsg);

extern VOS_UINT32 OM_PcvPidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_VOID   OM_PcvMsgProc(MsgBlock *pMsg);
extern VOS_VOID   OM_PcvTransmitTaskEntry( VOS_VOID );
extern VOS_VOID   PCSC_AcpuMsgProc(MsgBlock *pMsg);

extern VOS_UINT32 GU_OamAppSendDataSync(VOS_UINT8 *pucData, VOS_UINT32 ulDataLen);

extern VOS_VOID Om_AcpuBbpConfigMsgProc(OM_REQ_PACKET_STRU *pRspPacket, OM_RSP_FUNC *pRspFuncPtr);

extern VOS_VOID SCM_StopAllSrcChan(VOS_VOID);

extern VOS_VOID  GU_OamDisconnectPorts(CPM_PHY_PORT_ENUM_UINT32  enPhyPort);

extern VOS_VOID OM_AcpuErrLogMsgProc(MsgBlock* pMsg);

extern VOS_UINT32 VOS_GetMsgName(VOS_UINT32 ulAddrress);

extern VOS_VOID OM_AcpuICCInfoWriteLog(VOS_UINT32 ulParam, VOS_UINT32 ulTimerName);

#if(FEATURE_ON == FEATURE_PTM)
extern VOS_VOID OM_AcpuRcvMsgFinish(VOS_VOID);
#endif
/*****************************************************************************
 Prototype      : OM_AcpuAddSNTime
 Description    : Add the Sequence number and Time stamp into the packet.
 Input          : pulSN        - The pointer of the sequence number.
                  pulTimeStamp - The pointer of the time stamp.
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2008-05-3
    Author      : g47350
    Modification: Created function
 *****************************************************************************/
VOS_VOID OM_AcpuAddSNTime(VOS_UINT32 *pulSN, VOS_UINT32 *pulTimeStamp)
{
    /* VOS_INT   lLockKey; */

    /* lLockKey = VOS_SplIMP(); */

#if ( (VOS_LINUX == VOS_OS_VER) || (VOS_WIN32 == VOS_OS_VER) )
    *(pulSN) = (VOS_UINT32)atomic_inc_return(&g_ulAcpuOMMsgSN);
#endif

    /* VOS_Splx(lLockKey); */

    if (VOS_NULL_PTR != pulTimeStamp)
    {
        *(pulTimeStamp) = OM_GetSlice();
    }
}

/*****************************************************************************
 Prototype       : OM_AcpuAddAppHeader
 Description     : Add the APP header to the front of msg.
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2008-03-20
    Author       : g47350
    Modification : Created function

    Data         : 2008-9-13
    Author       : ���� 47350.
    Modification : ��Ӷ�LOG������Ϣͷ�Ĳ���
 *****************************************************************************/
VOS_VOID OM_AcpuAddAppHeader (VOS_UINT8 ucFuncType, VOS_UINT8* pucInputMsg,
                              OM_APP_HEADER_STRU* pstAppHeader, VOS_UINT32 ulTraceMsgLen)
{
    PS_OM_EVENT_IND_STRU   *pstrEvent;
    OM_APP_TRACE_STRU      *pstAppTrace;
    OM_APP_EVENT_STRU      *pstAppEvent;
    OM_APP_LOG_STRU        *pstAppLog;

    pstAppHeader->ucFuncType = ucFuncType;
    pstAppHeader->usLength = (VOS_UINT16)(ulTraceMsgLen - VOS_OM_HEADER_LEN);
    OM_AcpuAddSNTime(&(pstAppHeader->ulSn), &(pstAppHeader->ulTimeStamp));
    /*Complete different procedures by function type.*/
    switch (ucFuncType)
    {
        case OM_TRACE_FUNC:
        case OM_AIR_FUNC:
            pstAppTrace = (OM_APP_TRACE_STRU*)pstAppHeader;
            pstAppTrace->usPrimId = OM_APP_TRACE_IND;
            VOS_MemCpy(pstAppTrace->aucPara, pucInputMsg, ulTraceMsgLen - OM_APP_TRACE_LEN);
            break;

        case OM_EVENT_FUNC:
            pstrEvent = (PS_OM_EVENT_IND_STRU*)pucInputMsg;
            pstAppEvent = (OM_APP_EVENT_STRU*)pstAppHeader;
            pstAppEvent->ulModuleId = pstrEvent->ulModuleId;
            pstAppEvent->usEventId =  pstrEvent->usEventId;
            VOS_MemCpy(pstAppEvent->aucPara, pstrEvent->aucData, ulTraceMsgLen - OM_APP_EVENT_LEN);
            break;

        case OM_LOG_FUNC:
            pstAppLog = (OM_APP_LOG_STRU*)pstAppHeader;
            pstAppLog->usPrimId = OM_APP_PRINT_IND;
            VOS_MemCpy(&(pstAppLog->ulModuleId), pucInputMsg,
                         (ulTraceMsgLen - OM_APP_LOG_LEN) + LOG_MODULE_ID_LEN);
            break;
         default:
            break;
    }
    return;
}

/*****************************************************************************
 Prototype      : OM_AcpuSendData
 Description    : OM sends the data to tool side.
 Input          : ucFuncType      - The function type of msg.
                  ulResult        - The execution result.
 Output         : void
 Return Value   : VOS_OK - Success.

 History        : ---
    Date        : 2008-06-19
    Author      : g47350
    Modification: Created function
 *****************************************************************************/
VOS_UINT32 OM_AcpuSendData(OM_RSP_PACKET_STRU *pucMsg, VOS_UINT16 usMsgLen)
{
    OM_APP_MSG_EX_STRU                 *pstAppMsg;

    g_stAcpuUeToPcSucRecord.stTotalData.ulDataLen += usMsgLen;
    g_stAcpuUeToPcSucRecord.stTotalData.ulNum++;

    /* ������� */
    if ( (0 == usMsgLen) || (VOS_NULL_PTR == pucMsg ) )
    {
        LogPrint("The input parameter is wrong.\n");

        g_stAcpuUeToPcErrRecord.stParaErrData.ulDataLen += usMsgLen;
        g_stAcpuUeToPcErrRecord.stParaErrData.ulNum++;

        return VOS_ERR;
    }

    if( VOS_FALSE != VOS_CheckInterrupt() )
    {
        g_stAcpuUeToPcErrRecord.stIntData.ulDataLen += usMsgLen;
        g_stAcpuUeToPcErrRecord.stIntData.ulNum++;

        return VOS_ERR;
    }

    pstAppMsg = (OM_APP_MSG_EX_STRU*)pucMsg;

    if ((OM_STATE_ACTIVE == g_ulAcpuOMSwitchOnOff)
        || ((OM_QUERY_FUNC == pstAppMsg->ucFuncType)
            &&(OM_APP_ESTABLISH_CNF == pstAppMsg->usPrimId)))
    {
        if(VOS_OK != OMRL_AcpuMsgSplit((VOS_UINT8*)pucMsg, usMsgLen))
        {
            g_stAcpuUeToPcErrRecord.stLostData.ulDataLen += usMsgLen;
            g_stAcpuUeToPcErrRecord.stLostData.ulNum++;
        }

        return VOS_OK;
    }

    g_stAcpuUeToPcErrRecord.stLinkErrData.ulDataLen += usMsgLen;
    g_stAcpuUeToPcErrRecord.stLinkErrData.ulNum++;

    return VOS_ERR;
}


VOS_VOID OM_AcpuSendResult(VOS_UINT8 ucFuncType,
                            VOS_UINT32 ulResult, VOS_UINT16 usReturnPrimId)
{
    OM_APP_MSG_EX_STRU stOmToAppMsg;

    stOmToAppMsg.ucFuncType = ucFuncType;
    stOmToAppMsg.usLength   = OM_APP_MSG_EX_LEN;
    stOmToAppMsg.usPrimId   = usReturnPrimId;
    stOmToAppMsg.usToolId   = g_usAcpuToolId;
    *((VOS_UINT32*)(stOmToAppMsg.aucPara)) = ulResult;

    OM_AcpuSendData((OM_RSP_PACKET_STRU*)&stOmToAppMsg, (VOS_UINT16)sizeof(OM_APP_MSG_EX_STRU));

    return;
}


VOS_VOID OM_AcpuSendContent(VOS_UINT8 ucFuncType,
                             OM_RSP_PACKET_STRU *pstOmToAppMsg, VOS_UINT16 usReturnPrimId)
{
    OM_APP_MSG_EX_STRU *pstTmpMsg;

    pstTmpMsg = (OM_APP_MSG_EX_STRU*)pstOmToAppMsg;

    pstTmpMsg->ucFuncType = ucFuncType;
    pstTmpMsg->usPrimId   = usReturnPrimId;
    pstTmpMsg->usToolId   = g_usAcpuToolId;

    OM_AcpuSendData(pstOmToAppMsg,
            (VOS_UINT16)(pstOmToAppMsg->usLength + VOS_OM_HEADER_LEN));
    return;
}


VOS_UINT32 OM_AppGreenChannel(VOS_UINT8 ucFuncType, VOS_UINT16 usPrimId,
                              VOS_UINT8 *pucData, VOS_UINT16 usLen)
{
    OM_APP_TRACE_STRU      *pstAppMsg;
    VOS_UINT32              ulResult;

    pstAppMsg = (OM_APP_TRACE_STRU*)VOS_MemAlloc(ACPU_PID_OM,
                                         DYNAMIC_MEM_PT, usLen + OM_APP_TRACE_LEN);
    if (NULL == pstAppMsg)
    {
        PS_LOG(ACPU_PID_OM, 0, PS_PRINT_ERROR, "OM_AppGreenChannel:VOS_MemAlloc.\n");

        return VOS_ERR;
    }

    pstAppMsg->stAppHeader.ucFuncType = ucFuncType;
    pstAppMsg->stAppHeader.usLength   = (usLen + OM_APP_TRACE_LEN) - VOS_OM_HEADER_LEN;
    pstAppMsg->usPrimId = usPrimId;
    pstAppMsg->usToolId = 0;

    OM_AcpuAddSNTime(&(pstAppMsg->stAppHeader.ulSn), &(pstAppMsg->stAppHeader.ulTimeStamp));

    /*�������ݳ���Ϊ0����ʾû�з�������*/
    if ((0 != usLen) && (VOS_NULL_PTR != pucData))
    {
        VOS_MemCpy(pstAppMsg->aucPara, pucData, usLen);
    }

    ulResult = OM_AcpuSendData((OM_RSP_PACKET_STRU*)pstAppMsg, usLen + OM_APP_TRACE_LEN);

    VOS_MemFree(ACPU_PID_OM, pstAppMsg);

    return ulResult;
}



VOS_UINT32 OM_AcpuSendLog(VOS_UINT8 *pucLogData, VOS_UINT32 ulLength)
{
    VOS_UINT8   *pucLogMsg;
    VOS_UINT32   ulLogMsgLen;

    /*���㷢�͸����߲�LOG��Ϣ�����ܳ��ȣ�����OM_APP_LOG_LEN��
    �Ѿ�������ModuleId�ĳ��ȣ�����Ҫ�����ȥ*/
    ulLogMsgLen = (ulLength + OM_APP_LOG_LEN) - LOG_MODULE_ID_LEN;
    pucLogMsg = (VOS_UINT8*)VOS_MemAlloc(ACPU_PID_OM,
                                           DYNAMIC_MEM_PT, ulLogMsgLen);
    if (VOS_NULL_PTR == pucLogMsg)
    {
        vos_printf("OM_AcpuSendLog, VOS_MemAlloc FAIL!\n");
        return VOS_ERR;
    }

    OM_AcpuAddAppHeader(OM_LOG_FUNC, pucLogData,
          (OM_APP_HEADER_STRU*)pucLogMsg, ulLogMsgLen);

    /*Sent to the tool side.*/
    OM_AcpuSendData((OM_RSP_PACKET_STRU*)pucLogMsg, (VOS_UINT16)ulLogMsgLen);

    VOS_MemFree(ACPU_PID_OM, pucLogMsg);

    return VOS_OK;
}


VOS_UINT32 OM_AcpuCheckMsgPID(VOS_UINT32 ulModuleId, VOS_UINT32 ulConfigBit)
{
    VOS_UINT32 ulResult;

    ulResult = NO_CONFIG_BIT;

    if ((VOS_PID_DOPRAEND <= ulModuleId) && (VOS_PID_BUTT > ulModuleId))
    {
        ulResult = (g_stAcpuTraceEventConfig.aulRptConfigLevl[ulModuleId - VOS_PID_DOPRAEND] & ulConfigBit);
    }

    return ulResult;
}


VOS_VOID OM_AcpuSavePSConfigInfo(VOS_UINT32* pulModuleIds,VOS_UINT32 ulModuleNum, VOS_UINT32 ulConfigBit)
{
    VOS_UINT32 ulModuleIndex;
    VOS_UINT32 ulModuleId;

    if (OM_ALL_MSG_ON == ulModuleNum)
    {
        for (ulModuleIndex = 0; ulModuleIndex < OM_MAX_PS_MODULE_NUM; ulModuleIndex++)
        {
            g_stAcpuTraceEventConfig.aulRptConfigLevl[ulModuleIndex] |= ulConfigBit;
        }

        return;
    }

    /* ����ϴ����� */
    for (ulModuleIndex = 0; ulModuleIndex < OM_MAX_PS_MODULE_NUM; ulModuleIndex++)
    {
        g_stAcpuTraceEventConfig.aulRptConfigLevl[ulModuleIndex] &= (~ulConfigBit);
    }

    /* �������� */
    for (ulModuleIndex = 0; ulModuleIndex < ulModuleNum; ulModuleIndex++)
    {
        ulModuleId = pulModuleIds[ulModuleIndex];

        if ((VOS_PID_DOPRAEND <= ulModuleId) && (VOS_PID_BUTT > ulModuleId) )
        {
            g_stAcpuTraceEventConfig.aulRptConfigLevl[ulModuleId-VOS_PID_DOPRAEND] |= ulConfigBit;
        }
    }

    return;
}


VOS_VOID OM_AcpuShowPSConfigInfo(VOS_UINT32 ulModuleId)
{
    if ((ulModuleId >= VOS_PID_BUTT) || (ulModuleId < VOS_PID_DOPRAEND))
    {
        vos_printf("OM_AcpuShowPSConfigInfo: Module Id is wrong.");
        return;
    }

    vos_printf("OM_AcpuShowPSConfigInfo: ModuleId is %d, Config Level is %d\n",
        ulModuleId, g_stAcpuTraceEventConfig.aulRptConfigLevl[ulModuleId - VOS_PID_DOPRAEND]);
}

/*lint -e416 -e661 -e662 -e717 �޸���:����*/

/*****************************************************************************
 Prototype       : OM_ACPUConfigMsgProc
 Description     : Complete the config of the ACPU's TRACE, EVENT.
 Input           : pstAppToOMMsg -- The pointer of the msg received from APP.
 Output          : None
 Return Value    : VOS_VOID

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_VOID OM_AcpuConfigMsgProc(OM_REQ_PACKET_STRU *pRspPacket, OM_RSP_FUNC *pRspFuncPtr)
{
    APP_OM_MSG_EX_STRU             *pstAppToOmMsg;
    OM_TRACE_CONFIG_REQ_STRU       *pstTraceConfig;
    OM_TRACE_MASK_CONFIG_REQ_STRU  *pstTraceMaskCfg;
    OM_EVENT_CONFIG_TABLE_STRU     *pstEventConfig;

    pstAppToOmMsg = (APP_OM_MSG_EX_STRU*)pRspPacket;

    switch (pstAppToOmMsg->ucFuncType)
    {
        case OM_TRACE_FUNC:
            if (APP_OM_TRACE_REQ == pstAppToOmMsg->usPrimId)
            {
                pstTraceConfig = (OM_TRACE_CONFIG_REQ_STRU*)(pstAppToOmMsg->aucPara);

                VOS_MemCpy(&g_stAcpuTraceEventConfig,pstTraceConfig,sizeof(VOS_UINT32));
                OM_AcpuSavePSConfigInfo(pstTraceConfig->aulModuleId,pstTraceConfig->ulModuleNum, TRACE_CONFIG_BIT);
            }

            if (APP_OM_TRACE_MASK_REQ == pstAppToOmMsg->usPrimId)
            {
                pstTraceMaskCfg = (OM_TRACE_MASK_CONFIG_REQ_STRU*)(pstAppToOmMsg->aucPara);

                OM_AcpuSavePSConfigInfo(pstTraceMaskCfg->aulModuleId, pstTraceMaskCfg->ulModuleNum, TRACE_MASK_CONFIG_BIT);
            }

            break;

        case OM_EVENT_FUNC:

            pstEventConfig = (OM_EVENT_CONFIG_TABLE_STRU*)(pstAppToOmMsg->aucPara);

            OM_AcpuSavePSConfigInfo(pstEventConfig->aulModuleId,pstEventConfig->ulModuleNum, EVENT_CONFIG_BIT);

            break;

        default:
            break;
    }

    return;
}

/*Global map table used to find the function according the FuncId.*/
OM_FUNCID_PROC_STRU g_astAcpuOmFuncIdProcTbl[OM_FUNCID_MAX_NUM] =
{
    {0,                VOS_NULL_PTR,                LEVEL_NORMAL},
    {OM_TRACE_FUNC,    OM_AcpuConfigMsgProc,        LEVEL_NORMAL},
    {OM_AIR_FUNC,      VOS_NULL_PTR,                LEVEL_NORMAL},
    {OM_FS_FUNC,       VOS_NULL_PTR,                LEVEL_NORMAL},
    {OM_TRANS_FUNC,    VOS_NULL_PTR,                LEVEL_NORMAL},
    {OM_EVENT_FUNC,    OM_AcpuConfigMsgProc,        LEVEL_NORMAL},
    {OM_LOG_FUNC,      Log_AcpuOmMsgProc,           LEVEL_NORMAL},
    {OM_WRF_FUNC,      VOS_NULL_PTR,                LEVEL_NORMAL},
    {OM_GRF_FUNC,      VOS_NULL_PTR,                LEVEL_NORMAL},
    {OM_AUTH_NV_FUNC,  VOS_NULL_PTR,                LEVEL_NORMAL},
    {OM_QUERY_FUNC,    OM_AcpuQueryMsgProc,         LEVEL_NORMAL}, /*���ڴ�����·��Ϣ*/
    {OM_NV_FUNC,       VOS_NULL_PTR,                LEVEL_NORMAL},
    {OM_SIGCAL_FUNC,   VOS_NULL_PTR,                LEVEL_NORMAL},
    {OM_GREEN_FUNC,    VOS_NULL_PTR,                LEVEL_NORMAL},
    {OM_PRINTF_FUNC,   OM_PrintfMsgProc,            LEVEL_NORMAL},
    {OM_READSD_FUNC,   OM_ReadSdMsgProc,            LEVEL_NORMAL},
    {OM_NOSIG_FUNC,    VOS_NULL_PTR,                LEVEL_NORMAL},
    {OM_BBP_FUNC,      Om_AcpuBbpConfigMsgProc,     LEVEL_NORMAL}
};



VOS_INT32  OM_AcpuRegisterReqProc(VOS_UINT8 ucModuleId,
                                                OM_REQUEST_PROCEDURE *pReqPro)
{
    if ((OM_FUNCID_ACPU_PART_NUM >= ucModuleId) || (OM_FUNCID_MAX_NUM <= ucModuleId)
        || (0 != g_astAcpuOmFuncIdProcTbl[ucModuleId].ulFuncType))
    {
        return VOS_ERR;
    }

    g_astAcpuOmFuncIdProcTbl[ucModuleId].ulFuncType = (VOS_UINT32)ucModuleId;
    g_astAcpuOmFuncIdProcTbl[ucModuleId].pOmFuncProc = pReqPro;

    return VOS_OK;
}


VOS_VOID OM_AcpuRegisterDrvCB(VOS_VOID)
{
    DRV_MSP_PROC_REG(OM_REQUEST_PROC, (BSP_MspProc)OM_AcpuRegisterReqProc);

    DRV_MSP_PROC_REG(OM_ADDSNTIME_PROC, (BSP_MspProc)OM_AcpuAddSNTime);

    return;
}


 VOS_UINT32 OM_AcpuStartEventTimer(VOS_VOID)
{
    VOS_UINT32 ulRtn;

    ulRtn = VOS_StartRelTimer(&g_stAcpuRegularBufFullTmr, ACPU_PID_OM,
                              OM_BUFF_TIMER_LENTH,
                              OM_BUFF_TIMER, 0,
                              VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);

    if (VOS_OK != ulRtn)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID OM_AcpuTimerMsgProc(MsgBlock* pMsg)
{
    VOS_UINT32 ulName;

    ulName = ((REL_TIMER_MSG*)pMsg)->ulName;

    if (OM_BUFF_TIMER == ulName)
    {
        OMRL_AcpuReportEvent();

        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_WARNING, "OM_AcpuTimerMsgProc:Recv timer and Send Event.");

        if (VOS_OK !=  OM_AcpuStartEventTimer())
        {
            PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_WARNING, "OM_AcpuTimerMsgProc:Start timer fail\r\n.");

            return ;
        }
    }
    else if (OM_ICC_TIMER == ulName)
    {
        OM_AcpuICCInfoWriteLog(0, ulName);
    }
#if(FEATURE_ON == FEATURE_PTM)
    else if(OM_ERRLOG_TIMER == ulName)
    {
        OM_AcpuRcvMsgFinish();
    }
#endif
    else
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_WARNING, "OM_TimerMsgProc:Unknown timer.");
    }
}

/* Added by h59254 for AP-Modem Personalisation Project, 2012/04/09, begin */
/*****************************************************************************
 Prototype       : OM_GetHsicPortStatus
 Description     : OM�ں�HSIC����
 Input           : None
 Output          : None
 Return Value    : OM_HSIC_PORT_STATUS_ENUM_UINT32

 History         : ---
    Date         : 2012-04-09
    Author       : h59254
    Modification : AP-Modem����������Ŀ��������
 *****************************************************************************/
OM_HSIC_PORT_STATUS_ENUM_UINT32 OM_GetHsicPortStatus(VOS_VOID)
{
    /* ����OM�ں�HSIC����״̬ */
    return g_ulOmHsicConnectStatus;
}
/*****************************************************************************
 Prototype       : Om_HsicConnectProc
 Description     : OM�ں�HSIC����
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2012-04-09
    Author       : h59254
    Modification : AP-Modem����������Ŀ��������
 *****************************************************************************/
VOS_VOID Om_HsicConnectProc(VOS_VOID)
{
    if (VOS_OK != VOS_SmP(g_ulOmAcpuHsicSem, 0))
    {
        return;
    }

    /* ��Ʒ��֧��HSIC���ԣ�ֱ�ӳ�ʼ���ɹ� */
    if (BSP_MODULE_SUPPORT != DRV_GET_HSIC_SUPPORT())
    {
        VOS_SmV(g_ulOmAcpuHsicSem);

        return;
    }

    /* ����Ѿ������ϲ������� */
    if (OM_HSIC_PORT_STATUS_ON == g_ulOmHsicConnectStatus)
    {
        VOS_SmV(g_ulOmAcpuHsicSem);

        return;
    }

    /* ��ȫ�ֱ�������Ϊ�ѹ����� */
    g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_ON;

    VOS_SmV(g_ulOmAcpuHsicSem);

    return;
}

/*****************************************************************************
 Prototype       : Om_HsicDisconnectProc
 Description     : OM�ں�HSIC�������
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2012-04-09
    Author       : h59254
    Modification : AP-Modem����������Ŀ��������
 *****************************************************************************/
VOS_VOID Om_HsicDisconnectProc(VOS_VOID)
{
    /* ��Ʒ��֧��HSIC���ԣ�ֱ�ӳ�ʼ���ɹ� */
    if (BSP_MODULE_SUPPORT != DRV_GET_HSIC_SUPPORT())
    {
        return;
    }

    /* ����Ѿ���δ����״̬��������������� */
    if (OM_HSIC_PORT_STATUS_OFF == g_ulOmHsicConnectStatus)
    {
        return;
    }

    /* ��ȫ�ֱ�������Ϊ�ѽ�������� */
    g_ulOmHsicConnectStatus = OM_HSIC_PORT_STATUS_OFF;

    return;
}
/* Added by h59254 for AP-Modem Personalisation Project, 2012/04/09, end */
/*****************************************************************************
 Prototype       : Om_PortSwitchProc
 Description     :
 Input           : pMsg -- The pointer of the msg.
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2012-03-05
    Author       : h59254
    Modification : Created function
 *****************************************************************************/
VOS_VOID Om_PortSwitchProc(OM_PORT_SWITCH_MODE_ENUM_UINT32 ulSwitchMode)
{
    if (OM_PORT_SWITCH_AP2MODEM == ulSwitchMode)
    {
        GU_OamDisconnectPorts(CPM_HSIC_PORT);

        g_stAcpuPcToUeSucRecord.stRlsInfo.ulRlsAp2Modem++;
        g_stAcpuPcToUeSucRecord.stRlsInfo.ulSlice = OM_GetSlice();
    }
    else if (OM_PORT_SWITCH_MODEM2AP == ulSwitchMode)
    {
        GU_OamDisconnectPorts(CPM_APP_PORT);

        g_stAcpuPcToUeSucRecord.stRlsInfo.ulRlsModem2Ap++;
        g_stAcpuPcToUeSucRecord.stRlsInfo.ulSlice = OM_GetSlice();

        CPM_ConnectPorts(CPM_HSIC_PORT, CPM_OM_COMM);
    }
    else
    {
        /*do nothing*/
    }
    return;
}

/*****************************************************************************
 Prototype       : OM_AcpuAtMsgProc
 Description     : A����OM����AT��Ϣ������
 Input           : pMsg -- The pointer of the msg.
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2012-03-05
    Author       : h59254
    Modification : Created function
 *****************************************************************************/
VOS_VOID OM_AcpuAtMsgProc(MsgBlock *pMsg)
{
    AT_OM_MSG_STRU                     *pstAtOmMsg;

    pstAtOmMsg = (AT_OM_MSG_STRU *)pMsg;

    switch (pstAtOmMsg->ulMsgName)
    {
        case AT_OM_PORT_SWITCH:
            Om_PortSwitchProc(((OM_PORT_SWITCH_MSG_STRU *)pstAtOmMsg)->ulSwitchMode);
            break;
        case AT_OM_HSIC_PORT_CONNECT:
            Om_HsicConnectProc();
            break;
        case AT_OM_HSIC_PORT_DISCONNECT:
            Om_HsicDisconnectProc();
            break;
        default:
            break;
    }

    return;
}

/*****************************************************************************
 Prototype       : OM_AcpuMsgProc
 Description     : Handle all messages sent to ACPU OM.
 Input           : pMsg -- The pointer of the msg.
 Output          : None
 Return Value    : VOS_VOID

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_VOID OM_AcpuMsgProc(MsgBlock* pMsg)
{
    APP_OM_MSG_EX_STRU    *pstAppToOmMsg;
    OM_REQUEST_PROCEDURE  *pOmFuncProc;
    VOS_UINT32             ulCurrentId;
    VOS_UINT32             ulOriginalId;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, pMsg->ulSenderPid, ACPU_PID_OM, *((VOS_UINT32*)pMsg->aucValue));

    /* ����Error log �ϱ� */
    OM_AcpuErrLogMsgProc(pMsg);

    /*�������Թ��߲����Ϣ*/
    if ((ACPU_PID_OM == pMsg->ulSenderPid) || (UEPS_PID_OMRL == pMsg->ulSenderPid))
    {
        pstAppToOmMsg = (APP_OM_MSG_EX_STRU*)pMsg->aucValue;
        ulOriginalId = (VOS_UINT32)pstAppToOmMsg->ucFuncType;

        ulCurrentId = g_astAcpuOmFuncIdProcTbl[ulOriginalId].ulFuncType;
        pOmFuncProc = g_astAcpuOmFuncIdProcTbl[ulOriginalId].pOmFuncProc;

        if ((VOS_NULL_PTR == pOmFuncProc) || (ulOriginalId != ulCurrentId))
        {
            PS_LOG2(ACPU_PID_OM, 0, PS_PRINT_ERROR,
                    "OM_AcpuMsgProc: Error Func Id: %d, FuncProc :%x.\n",
                    (VOS_INT32)ulOriginalId, (VOS_INT32)pOmFuncProc);

            OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

            return;
        }

        if (OM_FUNCID_PART_NUM >= ulOriginalId)
        {
            g_usAcpuToolId = pstAppToOmMsg->usToolId;

            pOmFuncProc((OM_REQ_PACKET_STRU*)pstAppToOmMsg, OM_AcpuSendData);

        }
        /*����ACPU CallBack����������*/
        else if ((OM_FUNCID_ACPU_PART_NUM < ulOriginalId) && (OM_FUNCID_MAX_NUM > ulOriginalId))
        {
            VOS_ReserveMsg(WUEPS_PID_OM, pMsg);

            pMsg->ulReceiverPid = ACPU_PID_OM_CALLBACK;

            (VOS_VOID)VOS_SendMsg(ACPU_PID_OM_CALLBACK, pMsg);
        }
        else
        {
            PS_LOG1(ACPU_PID_OM, 0, PS_PRINT_ERROR,
                    "OM_AcpuMsgProc: Error Func Id: %d.\n", (VOS_INT32)ulOriginalId);
        }
    }
    else if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        OM_AcpuTimerMsgProc(pMsg);
    }
    else if(WUEPS_PID_AT == pMsg->ulSenderPid)
    {
        OM_AcpuAtMsgProc(pMsg);
    }
    else
    {
        PS_LOG(WUEPS_PID_OM, 0, LOG_LEVEL_WARNING, "OM_AcpuMsgProc: Send Pid Err.\n");
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    return;
}

/*lint +e416 +e661 +e662 +e717*/
/*****************************************************************************
 Prototype       : OM_AcpuTraceMsgHook
 Description     : OM' hook function
 Input           : pMsg -- The pointer of the msg.
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 OM_AcpuTraceMsgHook(VOS_VOID* pMsg)
{
    MsgBlock                    *pNewMsg;
    VOS_UINT32                   ulTraceMsgLen;
    OM_APP_TRACE_STRU            stAppTrace;
    VOS_UINT32                   ulPidConfigFlag;

    ulPidConfigFlag = NO_CONFIG_BIT;

    if (VOS_NULL_PTR == pMsg)
    {
        PS_LOG(ACPU_PID_OM, 0, PS_PRINT_ERROR, "OM_AcpuTraceMsgHook: Input para is NULL.\n");
        return VOS_OK;
    }

    pNewMsg = (MsgBlock*)pMsg;

    /*Check if the current msg is system msg.*/
    if (pNewMsg->ulSenderPid < VOS_PID_DOPRAEND)
    {
        if (0 == g_stAcpuTraceEventConfig.usSysMsg)
        {
            PS_LOG(ACPU_PID_OM, 0, PS_PRINT_INFO, "OM_AcpuTraceMsgHook, System message is filtered.!\n");
            return VOS_OK;
        }
    }
    /*If the current msg is not system msg, we should filter the msgs according the config sent by tools.*/
    else
    {
        if (TRACE_MASK_CONFIG_BIT == OM_AcpuCheckMsgPID(pNewMsg->ulReceiverPid, TRACE_MASK_CONFIG_BIT))
        {
            return VOS_OK;
        }

        ulPidConfigFlag = OM_AcpuCheckMsgPID(pNewMsg->ulSenderPid, TRACE_CONFIG_BIT);

        ulPidConfigFlag |= OM_AcpuCheckMsgPID(pNewMsg->ulReceiverPid, TRACE_CONFIG_BIT);

        if (NO_CONFIG_BIT == ulPidConfigFlag)
        {
            return VOS_OK;
        }
    }

#if 0
    /*Filer the msg by the interface by TTF group.*/
    bResult =  TTF_FilterMsg(pNewMsg);
    if (PS_FALSE == bResult)
    {
        return VOS_OK;
    }
#endif

    /*Construct the msg sent to tool side.*/
    ulTraceMsgLen = OM_APP_TRACE_LEN + VOS_MSG_HEAD_LENGTH + pNewMsg->ulLength;

    stAppTrace.stAppHeader.ucFuncType = OM_TRACE_FUNC;
    stAppTrace.stAppHeader.usLength   = (VOS_UINT16)(ulTraceMsgLen - VOS_OM_HEADER_LEN);

    OM_AcpuAddSNTime(&(stAppTrace.stAppHeader.ulSn),
                    &(stAppTrace.stAppHeader.ulTimeStamp));
    stAppTrace.usPrimId   = OM_APP_TRACE_IND;
    *((VOS_UINT32*)stAppTrace.aucPara)  = (VOS_UINT32)pNewMsg;

    /*Sent to the tool side.*/
    OM_AcpuSendData((OM_RSP_PACKET_STRU*)&stAppTrace, (VOS_UINT16)ulTraceMsgLen);

    return VOS_OK;
}

/*****************************************************************************
 Prototype       : OM_AcpuEvent
 Description     :
 Input           : pMsg -- The pointer of the msg.
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2008-03-20
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 OM_AcpuEvent(PS_OM_EVENT_IND_STRU *pstEvent)
{
    VOS_UINT32  ulTotalLen;
    VOS_UINT8  *pucEventPara = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstEvent)
    {
        PS_LOG( ACPU_PID_OM, 0, PS_PRINT_ERROR," OM_AcpuEvent:Input para is NULL\n");
        return VOS_ERR;
    }

    if (NO_CONFIG_BIT == OM_AcpuCheckMsgPID(pstEvent->ulModuleId, EVENT_CONFIG_BIT))
    {
        PS_LOG( ACPU_PID_OM, 0, PS_PRINT_ERROR," OM_AcpuEvent: Event Module Id is not configed\n");
        return VOS_ERR;
    }

    /*Construct the event msg sent to tool side.*/
    ulTotalLen = sizeof(OM_APP_HEADER_STRU) + pstEvent->ulLength;
    pucEventPara = (VOS_UINT8 *)VOS_MemAlloc(ACPU_PID_OM, DYNAMIC_MEM_PT, ulTotalLen);

    if (VOS_NULL_PTR == pucEventPara)
    {
        PS_LOG( ACPU_PID_OM, 0, PS_PRINT_ERROR," OM_AcpuEvent:VOS_MemAlloc Failed\n");
        return VOS_ERR;
    }

    OM_AcpuAddAppHeader(OM_EVENT_FUNC, (VOS_UINT8*)pstEvent,
                                 (OM_APP_HEADER_STRU*)pucEventPara, ulTotalLen);

    OM_AcpuSendData((OM_RSP_PACKET_STRU*)pucEventPara, (VOS_UINT16)ulTotalLen);

    VOS_MemFree(ACPU_PID_OM, pucEventPara);

    return VOS_OK;
}

/* ��C��OM�ӿ��г�ͻ��ȷ��ST���̱���ͨ�� */
#if (VOS_WIN32 != VOS_OS_VER)
/*****************************************************************************
 Prototype       : OM_GetSlice
 Description     : ���ݵ�ǰ�Ƿ�ΪASIC�汾���ṩ��ͬ��ʱ���
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2008-12-08
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 OM_GetSlice(VOS_VOID)
{
    /* Add for L Only version */
    if (BOARD_TYPE_LTE_ONLY == BSP_OM_GetBoardType())
    {
        return VOS_GetTick();
    }
    /* Add for L Only version */

#if (VOS_WIN32 != VOS_OS_VER)
    return DRV_GET_SLICE();
#else
    return VOS_GetTick();
#endif
}
#endif

#if (FEATURE_ON == MBB_WPG_COMMON)
VOS_UINT32  OM_GetSeconds(VOS_VOID)
{
    return DRV_GET_SECONDS();
}
#endif

#if (VOS_WIN32 == VOS_OS_VER)
VOS_VOID OM_AcpuRecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber)
{
    return;
}
VOS_VOID OM_AcpuRecordInfoStart(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber, VOS_UINT32 ulSendPid, VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgName)
{
    return;
}
#else

VOS_VOID OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber)
{
    VOS_UINT32 *pulBuf;

    if(VOS_EXC_DUMP_MEM_NUM_BUTT <= enNumber)
    {
        return;
    }

    if(VOS_NULL_PTR == g_astAcpuRecordInfo[enNumber].pucBuf)
    {
        return;
    }

    if(0 == g_astAcpuRecordInfo[enNumber].ulLen)
    {
        return;
    }

    /* ��start���Ѿ�����˼�¼endslice�ĳ��ȣ���˴˴������ĸ��ֽ���дendslice��ֵ */
    pulBuf = (VOS_UINT32*)(g_astAcpuRecordInfo[enNumber].pucBuf + g_astAcpuRecordInfo[enNumber].ulLen - sizeof(VOS_UINT32));

    *pulBuf = VOS_GetSlice();

    return;
}


VOS_VOID OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber, VOS_UINT32 ulSendPid, VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgName)
{
    OM_RECORD_INFO_STRU     stRecordInfo;

    if(VOS_EXC_DUMP_MEM_NUM_BUTT <= enNumber)
    {
       return;
    }

    if(VOS_NULL_PTR == g_astAcpuRecordInfo[enNumber].pucBuf)
    {
       return;
    }

    g_astAcpuRecordInfo[enNumber].ulLen %= VOS_TASK_DUMP_INFO_SIZE;

    stRecordInfo.usSendPid      = (VOS_UINT16)ulSendPid;
    stRecordInfo.usRcvPid       = (VOS_UINT16)ulRcvPid;
    stRecordInfo.ulMsgName      = ulMsgName;
    stRecordInfo.ulSliceStart   = VOS_GetSlice();
    stRecordInfo.ulSliceEnd     = 0;

    VOS_MemCpy((g_astAcpuRecordInfo[enNumber].pucBuf + g_astAcpuRecordInfo[enNumber].ulLen),
              &stRecordInfo, sizeof(OM_RECORD_INFO_STRU));

    g_astAcpuRecordInfo[enNumber].ulLen += sizeof(OM_RECORD_INFO_STRU);

    return;
}


VOS_VOID OM_RecordMemInit(VOS_VOID)
{
   VOS_UINT32 i;

   VOS_MemSet(g_astAcpuRecordInfo, 0, sizeof(g_astAcpuRecordInfo));

   /* ����ÿ��ģ���¼��ν�ɲ���Ϣ�Ŀռ� */
   for(i = 0; i < VOS_EXC_DUMP_MEM_NUM_BUTT; i++)
   {
      g_astAcpuRecordInfo[i].pucBuf = (VOS_UINT8*)VOS_ExcDumpMemAlloc(i);

      if(VOS_NULL_PTR == g_astAcpuRecordInfo[i].pucBuf)
      {
          return;
      }
   }

   return;
}

#endif

#if (VOS_OS_VER == VOS_LINUX)

#define NV_APP_HEAD     VOS_UINT16  usNvId;\
                        VOS_UINT16  usLength;\
                        VOS_UINT32  ulResult;

#define NV_APP_HEAD_LEN     8

#define NV_USER_MAX_LEN     (1024)

#define NV_VFILE_CRT_LEVEL  (0660)


typedef struct
{
    NV_APP_HEAD
    VOS_UINT8   aucData[NV_USER_MAX_LEN];
}NV_APP_DATA_STRU;



ssize_t NV_LinuxUserRead(struct file *file, char __user *buf, size_t len, loff_t *ppos)
{
    NV_APP_DATA_STRU    stNvData;

    VOS_MemSet(&stNvData, 0, sizeof(stNvData));

    if(len > sizeof(NV_APP_DATA_STRU))
    {
        printk("\r\n NV_LinuxUserRead: The Input Error Len is %d:", len);
        return VOS_ERROR;
    }

    if(VOS_OK != copy_from_user(&stNvData, buf, len))   /*�����û��ռ����ݵ��ں˿ռ�����*/
    {
        printk("\r\n NV_LinuxUserRead: copy_from_user is Error");
        return VOS_ERROR;
    }

    if((stNvData.usLength > NV_USER_MAX_LEN)||(stNvData.usLength == 0))
    {
        printk("\r\n NV_LinuxUserRead: The Data len Error: %d", stNvData.usLength);
        return VOS_ERROR;
    }

    stNvData.ulResult = NV_ReadEx(MODEM_ID_0,stNvData.usNvId, stNvData.aucData, stNvData.usLength);    /*���� Nv ��ȡ�ӿ�*/

    if(NV_OK != stNvData.ulResult)
    {
        printk("\r\n NV_LinuxUserRead: Read Nv Data Error %d", (VOS_INT)stNvData.ulResult);
    }

    if(VOS_OK != copy_to_user(buf, &stNvData, len))
    {
        printk("\r\n NV_LinuxUserRead: copy_to_user is Error");
        return VOS_ERROR;
    }

    return VOS_OK;
}




ssize_t NV_LinuxUserWrite(struct file *file, const char __user *buf, size_t len, loff_t *ppos)
{
    NV_APP_DATA_STRU    stNvData;

    VOS_MemSet(&stNvData, 0, sizeof(stNvData));

    if(len > sizeof(NV_APP_DATA_STRU))
    {
        printk("\r\n NV_LinuxUserRead: The Input Error Len is %d:", len);
        return VOS_ERROR;
    }

    if(VOS_OK != copy_from_user(&stNvData, buf, len))   /*�����û��ռ����ݵ��ں˿ռ�����*/
    {
        printk("\r\n NV_LinuxUserRead: copy_from_user is Error");
        return VOS_ERROR;
    }

    if((0 == stNvData.usLength)||(stNvData.usLength > NV_USER_MAX_LEN))
    {
        printk("\r\n NV_LinuxUserWrite: NV Length Error %d", stNvData.usLength);
        return VOS_ERROR;
    }

    stNvData.ulResult = NV_WriteEx(MODEM_ID_0,stNvData.usNvId, stNvData.aucData, stNvData.usLength);

    if(VOS_OK != stNvData.ulResult)
    {
        printk("\r\n NV_LinuxUserWrite: NV Write Error %d", (VOS_INT)stNvData.ulResult);
    }

    if(VOS_OK != copy_to_user(buf, &stNvData, NV_APP_HEAD_LEN))
    {
        printk("\r\n NV_LinuxUserRead: copy_to_user is Error");
        return VOS_ERROR;
    }

    return VOS_OK;
}



static const struct file_operations g_stNV_FOPS =
{
    .owner      = THIS_MODULE,
    .write      = NV_LinuxUserWrite,
    .read       = NV_LinuxUserRead,
};

VOS_UINT32 NV_VFInit(VOS_VOID)
{
    if(VOS_NULL_PTR == proc_create("OmNv", NV_VFILE_CRT_LEVEL, VOS_NULL_PTR, &g_stNV_FOPS))
    {
        LogPrint("\r\nNv_VFInit: proc_create Return NULL");

        return VOS_ERR;
    }

    return VOS_OK;
}

#endif


VOS_UINT32 OM_AcpuRegNvInit(VOS_VOID)
{
#if (VOS_WIN32 == VOS_OS_VER)
    /* Init NV's code for reading NV */
    if (VOS_OK != NV_Init())
    {
        return VOS_ERR;
    }
#endif

#if (VOS_OS_VER == VOS_LINUX)
    NV_VFInit();
#endif

    DRV_MSP_PROC_REG(OM_WRITE_NV_PROC, (BSP_MspProc)NV_WriteEx);

    return VOS_OK;
}


VOS_VOID OM_AcpuICCInfoFileName( VOS_CHAR * cFileName )
{
    FILE                                *fp;

    if ( VOS_NULL_PTR == cFileName )
    {
        return;
    }

    /* ��ȡ��󱣴��ļ�����ֵ */
    fp = DRV_FILE_OPEN((VOS_CHAR*)g_acICCLogFilePath, "rb+");

    /* ���û�ж�ȡ���ļ�����ֵ�ļ��������״α��棬�ļ�����ֵʹ��Ĭ��ֵ0��ʼ */
    if (VOS_NULL_PTR == fp)
    {
        g_ulICCLogFileIndex = 0;
    }
    else
    {
        DRV_FILE_READ(&g_ulICCLogFileIndex, sizeof(VOS_UINT32), 1, fp);

        DRV_FILE_CLOSE(fp);
    }

    VOS_MemSet(cFileName, 0, OM_ICC_MAX_NAME_LEN);

    VOS_StrNCpy(cFileName, g_acICCLogFilePath, VOS_StrLen(g_acICCLogFilePath));

    VOS_nsprintf((VOS_CHAR *)(cFileName+VOS_StrLen(g_acICCLogFilePath)), 2, ".%d", g_ulICCLogFileIndex);

    return;
}


VOS_VOID OM_AcpuICCInfoWriteLog(VOS_UINT32 ulParam, VOS_UINT32 ulTimerName)
{
    VOS_UINT32                          ulLen;
    VOS_CHAR                            ucFileName[OM_ICC_MAX_NAME_LEN];
    FILE                                *fp;

    OM_AcpuICCInfoFileName(ucFileName);

    fp = DRV_FILE_OPEN((VOS_CHAR*)ucFileName, "ab+");  /*����׷�ӷ�ʽ���ļ�*/

    if(VOS_NULL_PTR == fp)                      /*����ļ���ʧ��˵�������ļ�Ҳ���ɹ�*/
    {
        return;
    }

    DRV_FILE_LSEEK(fp, 0, DRV_SEEK_END);

    ulLen = (VOS_UINT32)DRV_FILE_TELL(fp);

    if(ulLen >= OM_LOG_FILE_MAX_SIZE)            /*�ļ���С��������*/
    {
        DRV_FILE_CLOSE(fp);

        g_ulICCLogFileIndex++;

        if (g_ulICCLogFileIndex > OAM_ICC_RECORD_MAX_FILE)
        {
            g_ulICCLogFileIndex = 0;
        }

        /* ����ǰ�ļ�����ֵ��¼��Icc-log�ļ��� */
        fp = DRV_FILE_OPEN((VOS_CHAR*)g_acICCLogFilePath, "wb+");

        if(VOS_NULL_PTR == fp)
        {
            return;
        }

        DRV_FILE_WRITE(&g_ulICCLogFileIndex, sizeof(VOS_UINT32), 1, fp);

        DRV_FILE_CLOSE(fp);

        /* ��ȡ�¼�¼�ļ��� */
        OM_AcpuICCInfoFileName(ucFileName);

        fp = DRV_FILE_OPEN((VOS_CHAR*)ucFileName, "wb+");  /*����ļ�����*/
    }

    if(VOS_NULL_PTR == fp)                      /*����ļ���ʧ��˵�������ļ�Ҳ���ɹ�*/
    {
        return;
    }

    /* ͨ����¼����Ϣ����ֵ��¼��ǰ�����ICC��Ϣ */
    DRV_FILE_WRITE(g_astIccRecordInfo, sizeof(OM_ICC_INFO_STRU), OAM_ICC_RECORD_MAX_NUM, fp);

    DRV_FILE_CLOSE(fp);

    /* ÿ�μ�¼��ɺ���յ�ǰICC��ά�ɲ�BUFF */
    VOS_MemSet(g_astIccRecordInfo, 0, sizeof(OM_ICC_INFO_STRU)*OAM_ICC_RECORD_MAX_NUM);

    g_ulIccRecordIndex = 0;

    return;
}


VOS_UINT32  OM_AcpuICCInfoInit( VOS_VOID )
{
    NV_SOCP_SDLOG_CFG_STRU              stInfoCfg ;

    VOS_MemSet(&stInfoCfg, 0, sizeof(stInfoCfg));

    g_AcpuIccLogTimerId = VOS_NULL;

    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_ID_SOCP_SDLOG_CFG, &stInfoCfg, sizeof(NV_SOCP_SDLOG_CFG_STRU)))
    {
        return VOS_ERR;
    }

    if(VOS_TRUE != stInfoCfg.ulSocpDelayWriteFlg)
    {
        return VOS_OK;
    }

    /* ʹ���ӳ�д��NVʱ����������ʱ���涨ʱ�� */
    (VOS_VOID)VOS_StartRelTimer(&g_AcpuIccLogTimerId, ACPU_PID_OM, stInfoCfg.ulTimeOutValue,
                    OM_ICC_TIMER, 0, VOS_RELTIMER_LOOP, VOS_TIMER_PRECISION_5);

    return VOS_OK;
}


VOS_VOID OM_AcpuICCInfoRecord(MsgBlock *pMsgCtrlBlk)
{
    if (VOS_NULL_PTR == pMsgCtrlBlk)
    {
        return;
    }

    g_astIccRecordInfo[g_ulIccRecordIndex].usSendPid    = (VOS_UINT16)pMsgCtrlBlk->ulSenderPid;
    g_astIccRecordInfo[g_ulIccRecordIndex].usRecvPid    = (VOS_UINT16)pMsgCtrlBlk->ulReceiverPid;
    g_astIccRecordInfo[g_ulIccRecordIndex].ulMsgName    = VOS_GetMsgName((VOS_UINT32)pMsgCtrlBlk);
    g_astIccRecordInfo[g_ulIccRecordIndex].ulSlice      = OM_GetSlice();

    g_ulIccRecordIndex++;

    /* ����¼��ICC��Ϣ����BUFF�������ֵ����BUFFͷ��ʼ���¼�¼ */
    if (g_ulIccRecordIndex >= OAM_ICC_RECORD_MAX_NUM)
    {
        g_ulIccRecordIndex = 0;
    }

    return;
}


VOS_UINT32 OM_AcpuGetLogPath(VOS_CHAR *pucBuf, VOS_CHAR *pucOldPath, VOS_CHAR *pucUnitaryPath)
{
    NV_PRODUCT_TYPE_FOR_LOG_DIRECTORY   stLogDir;

    if (VOS_OK != NV_Read(en_NV_Item_ProductTypeForLogDirectory, &stLogDir, sizeof(stLogDir)))
    {
        /* ��NVʧ��,ֱ�ӷ��� */
        return VOS_ERR;
    }

    /*0:MBB V3R3 stick/E5,etc.; 1:V3R3 M2M & V7R2; 2:V9R1 phone; 3:K3V3&V8R1;*/
    if ((1 == stLogDir.usProductType) || (3 == stLogDir.usProductType))
    {
        VOS_StrCpy(pucBuf, pucUnitaryPath);
    }
    else
    {
        VOS_StrCpy(pucBuf, pucOldPath);
    }

    return VOS_OK;
}


/*****************************************************************************
 Prototype       : OM_AcpuInit
 Description     : OM' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 OM_AcpuInit(VOS_VOID)
{
    /* ԭ�ӱ�������ʼֵΪ0����Ϊʹ��ʱ���ȼ�һ�ٷ��ص� */
#if ( (VOS_LINUX == VOS_OS_VER) || (VOS_WIN32 == VOS_OS_VER) )
    atomic_set(&g_ulAcpuOMMsgSN, 0);
#endif

#if (VOS_WIN32 == VOS_OS_VER)
    OM_RegisterMsgHook(OM_AcpuTraceMsgHook, OM_MSG_HOOK_LTE);
#else
    /* ��OSA�ҽӹ��Ӻ��� */
    VOS_RegisterMsgGetHook(OM_AcpuTraceMsgHook);
#endif

    /* ���以���ź��� */
    if (VOS_OK != VOS_SmMCreate("SYNC", VOS_SEMA4_FIFO, &g_ulOmAcpuSyncSem))
    {
        return VOS_ERR;
    }

    /* Modified by h59254 for AP-Modem Personalisation Project, 2012/04/12, begin */
    /* ���以���ź��� */
    if (VOS_OK != VOS_SmMCreate("HSIC", VOS_SEMA4_FIFO, &g_ulOmAcpuHsicSem))
    {
        return VOS_ERR;
    }
    /* Modified by h59254 for AP-Modem Personalisation Project, 2012/04/12, end */

    /* ����������ź��� */
    if (VOS_OK != VOS_SmBCreate( "CNF", 0, VOS_SEMA4_FIFO, &g_ulOmAcpuCnfSem))
    {
        return VOS_ERR;
    }

    /* ��ʼ������ͨ�� */
    if (VOS_OK != CPM_InitPhyPort())
    {
        return VOS_ERR;
    }

    /* ��ʼ��OM�߼�ͨ�� */
    if (VOS_OK != OMRL_AcpuInit())
    {
        return VOS_ERR;
    }

    /*ע�ắ��������ʹ��*/
    OM_AcpuRegisterDrvCB();

    /* ��ʼ��PS������Ϣ */
    VOS_MemSet(&g_stAcpuTraceEventConfig, 0, sizeof(OM_TRACE_EVENT_CONFIG_PS_STRU));

    /* ��ʼ��C�˸�λ��¼ȫ�ֱ��� */
    VOS_MemSet(g_astCcoreStatus,0,sizeof(g_astCcoreStatus));

    if (VOS_OK != OM_PrintfInit())
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_WARNING, "OM_AcpuInit: OM_Printf_Init failed.\n");
    }

    if(VOS_OK != OM_AcpuStartEventTimer())
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_WARNING, "OM_AcpuInit: OM_AcpuStartEventTimer failed.\n");

        return VOS_ERR;
    }

    if (VOS_OK != OM_AcpuICCInfoInit())
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_WARNING, "OM_AcpuInit: OM_AcpuICCInfoInit failed.\n");
    }

    if (VOS_OK != OM_AcpuGetLogPath(g_acICCLogFilePath, OM_ICC_LOG_PATH, OM_ICC_UNITARY_LOG_PATH))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 OM_AcpuPortInit(VOS_VOID)
{
    OM_CHANNLE_PORT_CFG_STRU    stPortCfg;

#if (VOS_OS_VER == VOS_WIN32)
    stPortCfg.enPortNum = CPM_WIFI_OM_PORT;
#else
    /* Modified by h59254 for AP-Modem Personalisation Project, 2012/04/12, begin */
    /* ��Ʒ֧��HSIC���ԣ�ֱ�ӷ��سɹ��������˿ڹ��� */
    if (BSP_MODULE_SUPPORT == DRV_GET_HSIC_SUPPORT())
    {
        return VOS_OK;
    }
    /* Modified by h59254 for AP-Modem Personalisation Project, 2012/04/12, end */

    /* ��ȡOM���������ͨ�� */
    if (NV_OK != NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        return VOS_ERR;
    }

    stPortCfg.enPortNum += CPM_APP_PORT;
#endif

    /* ������*/
    if (CPM_PORT_BUTT >= stPortCfg.enPortNum)
    {
        CPM_ConnectPorts(stPortCfg.enPortNum, CPM_OM_COMM);

        if (CPM_WIFI_OM_PORT == stPortCfg.enPortNum)
        {
            CPM_ConnectPorts(CPM_WIFI_AT_PORT, CPM_AT_COMM);
        }
    }

    return VOS_OK;
}


VOS_VOID OM_AutoConfigProc(VOS_VOID)
{
    OM_CHANNLE_PORT_CFG_STRU    stPortCfg;
    VOS_UINT8                   aucEstablishReq[] = {0x0a,0x00,0x08,0x00,
                                                     0xb1,0x80,0x00,0x00,
                                                     0x01,0x00,0x00,0x00};
    FILE*                       lCfgFile = DRV_FILE_NULL;
    VOS_UINT8                   aucHeadData[OM_CONFIG_HEAD_SIZE];
    VOS_INT32                   lReadSize;
    VOS_UINT32                  ulMsgLen = 0;
    MsgBlock                    *pstMsgBlk;
    VOS_CHAR                    aucConfigPath[100];

    if (NV_OK != NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        return;
    }

    /* �жϵ�ǰ�Ƿ�ΪSD����ʽ��� */
    if ( (CPM_SD_PORT == (stPortCfg.enPortNum + CPM_APP_PORT)) ||
        (CPM_FS_PORT == (stPortCfg.enPortNum + CPM_APP_PORT)))
    {
        /*SD������Log��FLASH����Log��������Ҫ���������ļ���ʼ������*/
    }
    else
    {
        return;
    }

    g_ulAcpuOMSwitchOnOff   = OM_STATE_ACTIVE;

    /* ֪ͨCCPU */
    (VOS_VOID)GU_OamSndPcMsgToCcpu((VOS_UINT8*)aucEstablishReq, sizeof(aucEstablishReq));

    if (VOS_OK != OM_AcpuGetLogPath(aucConfigPath, OM_CONFIG_PATH, OM_CONFIG_UNITARY_PATH))
    {
        return;
    }

    /*��ȡ�����ļ�*/
    lCfgFile = DRV_FILE_OPEN(aucConfigPath, "rb");
    if (DRV_FILE_NULL == lCfgFile)
    {
        LogPrint("OM_AutoConfig: The config file is not exsit!\n");
        return;
    }

    DRV_FILE_LSEEK(lCfgFile, 0, 0);

    for(;;)
    {
        lReadSize = DRV_FILE_READ((VOS_CHAR*)aucHeadData, sizeof(VOS_CHAR), OM_CONFIG_HEAD_SIZE, lCfgFile);
        if (OM_CONFIG_HEAD_SIZE != lReadSize)
        {
            break;
        }

        /*���������Ϣ�ĳ���, ǰ3���ֽ�Ϊ���߱����ֶ�*/
        VOS_MemCpy(&ulMsgLen, (VOS_UINT8*)(aucHeadData + 3), sizeof(VOS_UINT32));

        /*����Ϣ���Ƚ��кϷ�ֵ�жϣ�����PC�뵥�彻���ĳ����ֶ�Ϊ2�ֽ�,
        ����ʹ��0xffff�����ж�*/
        if (ulMsgLen > 0xffff)
        {
            LogPrint1("OM_AutoConfig: The Msg Len is too big : %d!\n", (VOS_INT32)ulMsgLen);
            break;
        }

        pstMsgBlk = VOS_AllocMsg(UEPS_PID_OMRL, ulMsgLen);
        if (VOS_NULL_PTR == pstMsgBlk)
        {
            break;
        }

        if (ulMsgLen != DRV_FILE_READ((VOS_CHAR*)(pstMsgBlk->aucValue), sizeof(VOS_CHAR), (VOS_UINT32)ulMsgLen, lCfgFile))
        {
            VOS_FreeMsg(UEPS_PID_OMRL, pstMsgBlk);
            break;
        }

        if (VOS_OK != OMRL_AcpuCpuIdToPid(pstMsgBlk->aucValue[1],&pstMsgBlk->ulReceiverPid))
        {
            VOS_FreeMsg(UEPS_PID_OMRL, pstMsgBlk);
            continue;
        }

        /*��������Ϣ���͸�OM����*/
        if (VOS_OK != VOS_SendMsg(UEPS_PID_OMRL, pstMsgBlk))
        {
            break;
        }
    }

    DRV_FILE_CLOSE(lCfgFile);

    return;
}

/*****************************************************************************
 Prototype       : OM_AcpuPidInit
 Description     : ACPU OM PID' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 OM_AcpuPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    OM_AUTOCONFIG_REQ_STRU *pstAutoConfigReq;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            return OM_AcpuInit();

        case VOS_IP_INITIAL:
            pstAutoConfigReq = (OM_AUTOCONFIG_REQ_STRU*)VOS_AllocMsg(ACPU_PID_OMAGENT,
                                sizeof(OM_AUTOCONFIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

            /* ������Ϣʧ�� */
            if (VOS_NULL_PTR == pstAutoConfigReq)
            {
                return VOS_ERR;
            }

            pstAutoConfigReq->ulReceiverPid = CCPU_PID_OMAGENT;
            pstAutoConfigReq->usPrimId      = OM_AUTOCONFIG_REQ;

            return VOS_SendMsg(ACPU_PID_OMAGENT, pstAutoConfigReq);

        case VOS_IP_BROADCAST_STATE:
            OM_SendAcpuSocpVote(SOCP_VOTE_FOR_SLEEP);
            break;

        case VOS_IP_BUTT:
            DRV_MSP_PROC_REG (OM_MNTN_ERRLOG, (BSP_MspProc)MNTN_ErrorLog);
            return OM_AcpuPortInit();

        default:
            break;
    }

    return VOS_OK;
}



/*****************************************************************************
 Prototype       : OM_AcpuSelfTaskReg
 Description     : ACPU OM FID' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 OM_AcpuSelfTaskReg(VOS_VOID)
{
    VOS_UINT32                              ulRslt;
    APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU  stPcvConfig;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU         stAPPConfig;


#if ( VOS_WIN32 != VOS_OS_VER )
    ulRslt = VOS_RegisterSelfTaskPrio(ACPU_FID_OM,
                                 (VOS_TASK_ENTRY_TYPE)Log_SelfTask,
                                 COMM_LOG_SELFTASK_PRIO, LOG_SELF_TASK_STACK_SIZE);
    if ( VOS_NULL_BYTE == ulRslt )
    {
        return VOS_ERR;
    }
#endif

    /*��ȡPcVoice��NV�е�����*/
    if(NV_OK!= NV_Read(en_NV_Item_PCVOICE_Support_Flg, &stPcvConfig, sizeof(APP_VC_NVIM_PC_VOICE_SUPPORT_FLAG_STRU)))
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "OM_AcpuSelfTaskReg:Read NV Config fail!");

        stPcvConfig.usPcVoiceSupportFlag =  VOS_FALSE;
    }

    /*��ȡPcVoice��NV�е�����Ϊ1��ʱ���ʹ��*/
    if(VOS_TRUE == stPcvConfig.usPcVoiceSupportFlag)
    {
        vos_printf("\r\nOM_AcpuSelfTaskReg: Reg the PCVoice Task and PID ");

        /* ����OM_PCVģ���Դ������� */
        ulRslt = VOS_RegisterSelfTask(ACPU_FID_OM,
                                     (VOS_TASK_ENTRY_TYPE)OM_PcvTransmitTaskEntry,
                                     VOS_PRIORITY_P2, PCV_TRANS_TASK_STACK_SIZE);
        if ( VOS_NULL_BYTE == ulRslt )
        {
            return VOS_ERR;
        }

        ulRslt = VOS_RegisterPIDInfo(ACPU_PID_PCVOICE,
                                    (Init_Fun_Type)OM_PcvPidInit,
                                    (Msg_Fun_Type)OM_PcvMsgProc);
        if( VOS_OK != ulRslt )
        {
            return VOS_ERR;
        }
    }

    /*��ȡӦ����NV�е�����Ϊ1��ʱ���ʹ��*/
    if(NV_OK != NV_Read(en_NV_Item_System_APP_Config, &stAPPConfig, sizeof(NAS_NVIM_SYSTEM_APP_CONFIG_STRU)))
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "OM_AcpuSelfTaskReg:Read NV en_NV_Item_System_APP_Config fail!");

        stAPPConfig.usSysAppConfigType = SYSTEM_APP_BUTT;
    }

    if(SYSTEM_APP_WEBUI== stAPPConfig.usSysAppConfigType)
    {
        vos_printf("\r\nOM_AcpuSelfTaskReg: Reg the OMPrintf Task");

        /* ����OM_printfģ���Դ������� */
        ulRslt = VOS_RegisterSelfTaskPrio(ACPU_FID_OM,
                                     (VOS_TASK_ENTRY_TYPE)OM_PrintfTask,
                                     COMM_PRINTF_SELFTASK_PRIO, OM_PRINTF_TASK_STACK_SIZE);
        if ( VOS_NULL_BYTE == ulRslt )
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_INT OM_AcpuCcoreResetCB(DRV_RESET_CALLCBFUN_MOMENT enParam, VOS_INT lUserData)
{
    if(DRV_RESET_CALLCBFUN_RESET_BEFORE == enParam) /* ��λǰ����*/
    {
        g_astCcoreStatus[OM_CPU_STATUS_RESET].ulResetNum++;
        g_astCcoreStatus[OM_CPU_STATUS_RESET].ulSlice = OM_GetSlice();

        OM_AcpuSendResult(OM_QUERY_FUNC, g_astCcoreStatus[OM_CPU_STATUS_RESET].ulResetNum, OM_APP_CCORE_RESET_CNF);

        SCM_StopAllSrcChan();
    }
    else if(DRV_RESET_CALLCBFUN_RESET_AFTER == enParam) /*��λ��*/
    {
        g_astCcoreStatus[OM_CPU_STATUS_OK].ulResetNum++;
        g_astCcoreStatus[OM_CPU_STATUS_OK].ulSlice = OM_GetSlice();
    }
    else
    {
        vos_printf("OM_AcpuCcoreResetCB:param err\r\n");
    }

    return VOS_OK;

}


VOS_VOID Om_ShowCcpuResetInfo(VOS_VOID)
{
    vos_printf("Ccpu Reset Num:     %d \r\n",  g_astCcoreStatus[OM_CPU_STATUS_RESET].ulResetNum);
    vos_printf("Ccpu Reset Time:    0x%x \r\n",  g_astCcoreStatus[OM_CPU_STATUS_RESET].ulSlice);
    vos_printf("Ccpu Ok Num:        %d \r\n",  g_astCcoreStatus[OM_CPU_STATUS_OK].ulResetNum);
    vos_printf("Ccpu Ok Time:       0x%x \r\n",  g_astCcoreStatus[OM_CPU_STATUS_OK].ulSlice);
}

/*****************************************************************************
 Prototype       : OM_AcpuFidInit
 Description     : ACPU OM FID' initializtion function
 Input           : None
 Output          : None
 Return Value    : VOS_UINT32

 History         : ---
    Date         : 2011-07-01
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_UINT32 OM_AcpuFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;
    VOS_INT                             lResut;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_OM,
                                        (Init_Fun_Type)OM_AcpuPidInit,
                                        (Msg_Fun_Type)OM_AcpuMsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_PB,
                                        (Init_Fun_Type)WuepsPBPidInit,
                                        (Msg_Fun_Type)SI_PB_PidMsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_OMAGENT,
                                        VOS_NULL_PTR,
                                        (Msg_Fun_Type)OM_AcpuAgentMsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_PCSC,
                                        VOS_NULL_PTR,
                                        (Msg_Fun_Type)PCSC_AcpuMsgProc);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterMsgTaskPrio(ACPU_FID_OM, VOS_PRIORITY_M2);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            if(VOS_OK != OM_AcpuSelfTaskReg())
            {
                return VOS_ERR;
            }

            /* ע��C�˵�����λ���� */
            lResut = DRV_CCORERESET_REGCBFUNC(OAM_MODELE_NAME,(pdrv_reset_cbfun)OM_AcpuCcoreResetCB,
                VOS_NULL,OAM_CCORE_RESET_CBFUN_PRI);

            if( VOS_OK != lResut )
            {
                vos_printf("OM_AcpuFidInit: Reg Ccore Reset CB FUN Fail\r\n");

                return VOS_ERR;
            }

            break;
        }

        default:
            break;
    }
    return VOS_OK;
}

#if (VOS_WIN32 != VOS_OS_VER)

VOS_VOID OM_OSAEvent(VOS_VOID *pData, VOS_UINT32 ulLength)
{
    PS_OM_EVENT_IND_STRU    *pstEventInd;
    VOS_UINT32               ulEventLenth;

    ulEventLenth = sizeof(PS_OM_EVENT_IND_STRU)
                    + ulLength
                    - 4 * sizeof(VOS_UINT8);/*�ṹ���а�����4byte������������Ҫ��ȥ*/

    pstEventInd = (PS_OM_EVENT_IND_STRU *)VOS_MemAlloc(ACPU_PID_OM, DYNAMIC_MEM_PT, ulEventLenth);
    if(VOS_NULL_PTR == pstEventInd)
    {
        return;
    }

    pstEventInd->ulLength   = ulEventLenth;

    pstEventInd->usEventId  = (VOS_UINT16)OAM_EVENT_TIMER;

    pstEventInd->ulModuleId = ACPU_PID_OM;

    /*lint -e419 -e416  */
    VOS_MemCpy((VOS_UINT8 *)pstEventInd->aucData, (VOS_UINT8 *)pData, ulLength);
    /*lint +e419 +e416*/

    if (VOS_OK != OM_AcpuEvent(pstEventInd))
    {
        PS_LOG(ACPU_PID_OM, VOS_NULL, PS_PRINT_WARNING, "OM_OSAEvent: send event fail.");
    }

    VOS_MemFree(ACPU_PID_OM, pstEventInd);

    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
