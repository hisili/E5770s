

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
/*lint -save -e537*/
#include  "diag_fw.h"
#include  "diag_api.h"
#include  "diag_cfg.h"
#include  "msp_errno.h"
#include  "msp_drx.h"
#include  "diag_debug.h"
#include  "diag_common.h"
#include  "diag_cmd_id.h"
#include  "diag_app_agent.h"
#include  "SCMProc.h"
#include "diag_vcom.h"
#include "diag_tcp.h"
#include  "drx_msp_api.h"
/*lint -restore*/
#if (FEATURE_ON == MBB_DLOAD)
#include "bsp_sram.h"
#endif /*MBB_DLOAD*/

/*lint -save -e767 ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_FW_C
/*lint -restore +e767*/
/*lint --e{565, 718, 746} */
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

DIAG_FW_RX_INFO_STRU g_stDiagFwNodeInfoStru = {0};

VOS_SEM g_DiagFwNodeSem =(VOS_SEM)0;

/*****************************************************************************
  3 Function
*****************************************************************************/


DIAG_FW_RX_INFO_STRU* diag_FwGetDiagNodeInfo(VOS_VOID)
{
    return &g_stDiagFwNodeInfoStru;
}


DIAG_FW_RX_INFO_STRU* diag_FwGetExeCmdNode(VOS_UINT32 ulCmdId)
{
    DIAG_FW_RX_INFO_STRU* pHeadNode = NULL;
    DIAG_FW_RX_INFO_STRU* pTempNode = NULL;
    LIST_S* me = NULL;

    /* ��ȡ����ͷ */
    pHeadNode= diag_FwGetDiagNodeInfo();

    /*����ź�������*/
    (VOS_VOID)VOS_SmP(g_DiagFwNodeSem,0);

    /* �������в���ÿ����������*/
    blist_for_each(me, &pHeadNode->HiDiagFwList)
    {
        pTempNode = blist_entry(me, DIAG_FW_RX_INFO_STRU, HiDiagFwList);

        /* �ҵ���Ҫ�Ľڵ�*/
        if (ulCmdId == pTempNode->ulCmdId)
        {
            (VOS_VOID)VOS_SmV(g_DiagFwNodeSem);
            return pTempNode;
        }
    }
    (VOS_VOID)VOS_SmV(g_DiagFwNodeSem);
    return NULL;
}

/*lint -save -e40*/ /* PID �����Ҳ�������*/


VOS_VOID diag_FwDelCmdNode(VOS_UINT32 ulCmdId)
{

    DIAG_FW_RX_INFO_STRU* pHeadNode = NULL;
    DIAG_FW_RX_INFO_STRU* pTempNode = NULL;
    LIST_S* me = NULL;

    /* ��ȡ����ͷ */
    pHeadNode = diag_FwGetDiagNodeInfo();

    /*�������������ͬcmd id*/
    (VOS_VOID)VOS_SmP(g_DiagFwNodeSem,0);
    blist_for_each(me, &pHeadNode->HiDiagFwList)
    {
        pTempNode = blist_entry(me, DIAG_FW_RX_INFO_STRU, HiDiagFwList);
        if(ulCmdId == pTempNode->ulCmdId)
            break;
    }
    (VOS_VOID)VOS_SmV(g_DiagFwNodeSem);
    /*δ�ҵ���ֱ�ӷ���*/
    if(NULL == pTempNode)
    {
        return;
    }
    if(ulCmdId != pTempNode->ulCmdId)
    {
        return;
    }
    /*����ź�������*/
    (VOS_VOID)VOS_SmP(g_DiagFwNodeSem,0);

    /*ɾ���ڵ�*/
    blist_del(&pTempNode->HiDiagFwList);

    (VOS_VOID)VOS_SmV(g_DiagFwNodeSem);

    /*�ͷ��ڴ�*/
    VOS_MemFree(MSP_PID_DIAG_FW,pTempNode);

    return ;
}



DIAG_FW_RX_INFO_STRU* diag_FwAddCmdToList(VOS_UINT8 * pstReq, VOS_UINT32 ulRcvlen)
{
    DIAG_FW_RX_INFO_STRU* pHeadNode = NULL;
    DIAG_FW_RX_INFO_STRU* pNewNode = NULL;
    VOS_UINT32 ret;

    /*����һ���ڵ��С*/
    pNewNode = VOS_MemAlloc(MSP_PID_DIAG_FW,DYNAMIC_MEM_PT,sizeof(DIAG_FW_RX_INFO_STRU) + ulRcvlen);
    if (NULL == pNewNode)
    {
        return NULL;
    }

    VOS_MemSet(pNewNode, 0, ulRcvlen + sizeof(DIAG_FW_RX_INFO_STRU));

    /*������������浽�ڵ���*/
    VOS_MemCpy(pNewNode->ucDiagRcvData, pstReq, ulRcvlen);

    /*��CMDIDȡ���������ں������ִ�нڵ�*/
    pNewNode->ulCmdId = (((MSP_DIAG_HEAD_STRU*)(pNewNode->ucDiagRcvData+sizeof(MSP_SOCP_HEAD_STRU)))->ulID);

    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_LIST_CMD,pNewNode->ulCmdId,ulRcvlen,0);

    /*������ʱ�����Ա�AGENTģ��û�лظ�ʱDIAG FW����������*/
    ret = VOS_StartRelTimer(&pNewNode->fwCtrlTimer, MSP_PID_DIAG_FW,DIAG_CMD_TIMEOUT_TIME_LEN, 0,pNewNode->ulCmdId,VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
    if(ret != ERR_MSP_SUCCESS)
    {
        diag_printf("VOS_StartRelTimer fail [%s]\n",__func__);
    }
    /* ��ȡ����ͷ */
    pHeadNode = diag_FwGetDiagNodeInfo();

    /*����ź�������*/
    (VOS_VOID)VOS_SmP(g_DiagFwNodeSem,0);

    /* ����ڵ㵽����β�� */
    blist_add_tail(&pNewNode->HiDiagFwList, &pHeadNode->HiDiagFwList);

    (VOS_VOID)VOS_SmV(g_DiagFwNodeSem);

    return pNewNode;
}


VOS_VOID diag_FwTimeOutPackt(VOS_VOID * pstRxinfo, VOS_UINT8 * pstSocpPackt)
{
    VOS_UINT64 ulTime = 0;

    /* ��REQ ����pstRxinfo�и��Ƴ�ԭ��SOCP��DIAG HEADER����SOCPͷ*/
    VOS_MemCpy(pstSocpPackt, ((DIAG_FW_RX_INFO_STRU*)pstRxinfo)->ucDiagRcvData,
        sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU));

    /* ��SOCP ��*/
    ulTime                           = diag_GetFrameTime();
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->usSId              = MSP_SOCP_SID_DIAG_SERVER;
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->usSSId             = MSP_SOCP_HIGH4BIT_SSID;  // ����λ
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->ucServiceSessionId = MSP_SOCP_SERVER_SESSION_ID;
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->ucMsgType          = MSP_SOCP_MSG_TYPE_IND;
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->ulMsgTransId       = (g_DiagLogPktNum.ulIndNum)++;
    VOS_MemCpy(((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->aucTimeData, &ulTime, sizeof(VOS_UINT64));

    /* ����ṹ��ID(DIAG HEADER)*/
    ((MSP_DIAG_HEAD_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU)))->ulID =
        (MSP_STRU_ID_GET_28_31_FIELD(MSP_STRU_ID_28_31_GROUP_MSP) | MSP_STRU_ID_GET_16_23_FIELD(MSP_STRU_ID_16_23_SYS_CMD)\
        | MSP_STRU_ID_GET_0_15_FIELD(DIAG_CMD_TIMER_OUT_IND));
    ((MSP_DIAG_HEAD_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU)))->ulDataSize =
        sizeof(DIAG_CMD_TIMER_OUT_IND_STRU);


    /*���DIAG_CMD_TIMER_OUT_IND_STRU��Ӧ���ٷ��ͳ�ʱ��Ϣ����*/
    ((DIAG_CMD_TIMER_OUT_IND_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU) +
        sizeof(MSP_DIAG_HEAD_STRU)))->ulCmdID =
        ((MSP_DIAG_HEAD_STRU*)(((DIAG_FW_RX_INFO_STRU*)pstRxinfo)->ucDiagRcvData + sizeof(MSP_SOCP_HEAD_STRU)))->ulID;
}


VOS_UINT32 diag_FwCmdTimeOutProc(VOS_UINT32 ulCmdId)
{
    VOS_UINT32 ulTmpLen =0;
    VOS_UINT32 ret = ERR_MSP_FAILURE;
    VOS_UINT8 * pBuf =NULL;

    DIAG_FW_RX_INFO_STRU* pHeadNode = NULL;
    DIAG_FW_RX_INFO_STRU* pTempNode = NULL;
    LIST_S* me = NULL;

    /* ��ȡ����ͷ */
    pHeadNode= diag_FwGetDiagNodeInfo();

    /*����ź�������*/
    (VOS_VOID)VOS_SmP(g_DiagFwNodeSem,0);

    /* �������в���ÿ����������*/
    blist_for_each(me, &pHeadNode->HiDiagFwList)
    {
        pTempNode = blist_entry(me, DIAG_FW_RX_INFO_STRU, HiDiagFwList);

        /* �ҵ���Ҫ�Ľڵ�*/
        if (ulCmdId == pTempNode->ulCmdId)
        {
            (VOS_VOID)VOS_SmV(g_DiagFwNodeSem);

            diag_printf("fw cmd 0x%x timer out, node found!\n", pTempNode->ulCmdId);
            ulTmpLen = (sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU)+ sizeof(DIAG_CMD_TIMER_OUT_IND_STRU));

            /*�������Դbuf*/
            diag_LockCoderSrcBuf();
            pBuf = diag_GetCoderSrcBuf(ulTmpLen,SOCP_CODER_SRC_LOM_PRECEDENCE_IND);
            if(NULL == pBuf)
            {
                diag_UnLockCoderSrcBuf();
                return ERR_MSP_FAILURE;
            }
            /*���SOCPͷ*/
            diag_FwTimeOutPackt(pTempNode, pBuf);

            /*����Ҫ�������ݵ�buf�У������͸�SOCP*/
            ret = diag_SendCoderSrcToSocp(pBuf,ulTmpLen,SOCP_CODER_SRC_LOM_PRECEDENCE_IND);
            diag_UnLockCoderSrcBuf();
            return ret;
        }
    }

    (VOS_VOID)VOS_SmV(g_DiagFwNodeSem);

    return ERR_MSP_INVALID_PARAMETER;

}


VOS_VOID diag_FwSocpCnfPackt(DIAG_FW_RX_INFO_STRU * pstRxinfo, VOS_UINT8 * pstSocpPackt,VOS_UINT32 ulCmdParaLen)
{
    /*lint -save -e958*/
    VOS_UINT64 ulTime = 0;
    /*lint -restore*/
    if ((NULL == pstSocpPackt)||(NULL ==pstRxinfo))
    {
        return;
    }

    /* ��REQ ����pstRxinfo�и��Ƴ�ԭ��SOCP��DIAG HEADER����SOCPͷ*/
    VOS_MemCpy(pstSocpPackt, (pstRxinfo)->ucDiagRcvData,
        sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU));

    /*����SOCPͷ��һЩ��Ҫ���ĵ��ֶ�*/
    ulTime                           = diag_GetFrameTime();
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->usSId              = MSP_SOCP_SID_DIAG_SERVER;
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->usSSId             = MSP_SOCP_HIGH4BIT_SSID_ACPU << 4;    // ����λ
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->ucServiceSessionId = MSP_SOCP_SERVER_SESSION_ID;
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->ucMsgType          = MSP_SOCP_MSG_TYPE_CNF;
    VOS_MemCpy(((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->aucTimeData, &ulTime, 8);  // ��ʱʹ�� TO DO

    /* ����ṹ��ID(DIAG HEADER)*/
    ((MSP_DIAG_HEAD_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU)))->ulDataSize =
        sizeof(MSP_DIAG_DATA_CNF_STRU) + ulCmdParaLen;

    /* ���MSP_DIAG_DATA_CNF_STRU,ȡ���ڵ��AUID*/
    ((MSP_DIAG_DATA_CNF_STRU*)(pstSocpPackt +
        sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU)))->ulAuid =
        ((MSP_DIAG_DATA_REQ_STRU*)(((DIAG_FW_RX_INFO_STRU*)pstRxinfo)->ucDiagRcvData +
            sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU)))->ulAuid;
	((MSP_DIAG_DATA_CNF_STRU*)(pstSocpPackt +
        sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU)))->ulSn =
        ((MSP_DIAG_DATA_REQ_STRU*)(((DIAG_FW_RX_INFO_STRU*)pstRxinfo)->ucDiagRcvData +
            sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU)))->ulSn;
}


VOS_UINT32 diag_FwCmdCnfProc(DIAG_FW_RX_INFO_STRU * pstRxinfo,VOS_UINT8* pData,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulTmpLen =0;
    VOS_UINT32 ret = ERR_MSP_FAILURE;
    VOS_UINT8 * pBuf =NULL;

    ulTmpLen = (DIAG_FULL_HEAD_LEN + ulLen);

    /*�������Դbuf*/
    diag_LockCoderSrcBuf();
    pBuf = diag_GetCoderSrcBuf(ulTmpLen,SOCP_CODER_SRC_LOM_CNF);
    if(NULL == pBuf)
    {
        diag_UnLockCoderSrcBuf();
        return ERR_MSP_FAILURE;
    }

    /*���SOCPͷ*/
    diag_FwSocpCnfPackt(pstRxinfo, pBuf,ulLen);

    VOS_MemCpy(pBuf + DIAG_FULL_HEAD_LEN, pData, ulLen);

    /*���͸�SOCP*/
    ret = diag_SendCoderSrcToSocp(pBuf,ulTmpLen,SOCP_CODER_SRC_LOM_CNF);
    diag_UnLockCoderSrcBuf();
    return ret;
}


VOS_UINT32 diag_FwAnsyCmdIndProc(VOS_UINT8* pData,VOS_UINT32 ulLen,VOS_UINT32 ulCmdId)
{
    VOS_UINT32 ulTmpLen =0;
    VOS_UINT32 ret = ERR_MSP_FAILURE;
    VOS_UINT8 * pBuf =NULL;

    ulTmpLen = (sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU)+ ulLen);

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        return ERR_MSP_NO_INITILIZATION;
    }

    /*�������Դbuf*/
    diag_LockCoderSrcBuf();
    pBuf = diag_GetCoderSrcBuf(ulTmpLen,SOCP_CODER_SRC_LOM_PRECEDENCE_IND);
    if(NULL == pBuf)
    {
        diag_UnLockCoderSrcBuf();
        return ERR_MSP_FAILURE;
    }

    /*���SOCPͷ*/
    diag_SocpIndCmdPkt(pBuf, MSP_STRU_ID_16_23_PS_TRANS, ulLen, (VOS_UINT16)ulCmdId);
    VOS_MemCpy(pBuf + sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU), pData, ulLen);

    /*���͸�SOCP*/
    ret = diag_SendCoderSrcToSocp(pBuf,ulTmpLen,SOCP_CODER_SRC_LOM_PRECEDENCE_IND);
    diag_UnLockCoderSrcBuf();
    return ret;
}


VOS_UINT32 diag_FwForwardCmdToAgent(DIAG_FW_RX_INFO_STRU * pNode,VOS_UINT32 ulSendSize)
{
    VOS_UINT32 app_ret = ERR_MSP_SUCCESS;
    VOS_UINT32 comm_ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulCmdId = 0;
    VOS_UINT32 ulConCmdId = 0;
    VOS_UINT32 ulDisConCmdId = 0;

    ulConCmdId = (MSP_STRU_ID_GET_28_31_FIELD(MSP_STRU_ID_28_31_GROUP_MSP)
                 |MSP_STRU_ID_GET_16_23_FIELD(MSP_STRU_ID_16_23_SYS_CMD)
                 |MSP_STRU_ID_GET_0_15_FIELD(DIAG_CMD_HOST_CONNECT));
    ulDisConCmdId = (MSP_STRU_ID_GET_28_31_FIELD(MSP_STRU_ID_28_31_GROUP_MSP)
                 |MSP_STRU_ID_GET_16_23_FIELD(MSP_STRU_ID_16_23_SYS_CMD)
                 |MSP_STRU_ID_GET_0_15_FIELD(DIAG_CMD_HOST_DISCONNECT));

    ulCmdId = (((MSP_DIAG_HEAD_STRU*)DIAG_OFFSET_SOCP_GET_DIAG_HEAD(pNode->ucDiagRcvData))->ulID);

    if((DRV_RESET_CALLCBFUN_RESET_BEFORE == g_DiagResetingCcore)&&(ulCmdId == ulConCmdId))/*������λʱ,�����Connect����,���ش���*/
    {
        return ERR_MSP_UNAVAILABLE;
    }
    else if((DRV_RESET_CALLCBFUN_RESET_BEFORE == g_DiagResetingCcore)&&(ulCmdId == ulDisConCmdId))/*������λʱ,�����DisConnect����,ֻ��A��*/
    {
        /*������ת����APP AGENT ����*/
        app_ret = diag_SendMsg(MSP_PID_DIAG_FW, MSP_PID_DIAG_APP_AGENT,ID_MSG_DIAG_CMD_REQ_FW_TO_APP_AGENT,pNode->ucDiagRcvData, ulSendSize);
        if(app_ret != ERR_MSP_SUCCESS)
        {
           DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY_ERROR, 0, 0, 4);
        }
        return app_ret;
    }
    /*������ת����APP AGENT ����*/
    app_ret = diag_SendMsg(MSP_PID_DIAG_FW, MSP_PID_DIAG_APP_AGENT,ID_MSG_DIAG_CMD_REQ_FW_TO_APP_AGENT,pNode->ucDiagRcvData, ulSendSize);
    if(app_ret != ERR_MSP_SUCCESS)
    {
       DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY_ERROR, 0, 0, 2);
    }

     /*������ת����AGENT ����*/
    comm_ret = diag_SendMsg(MSP_PID_DIAG_FW, MSP_PID_DIAG_AGENT,ID_MSG_DIAG_CMD_REQ_FW_TO_AGENT,pNode->ucDiagRcvData, ulSendSize);
    if(comm_ret != ERR_MSP_SUCCESS)
    {
       DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY_ERROR, 0, 0, 3);
    }

    /* ������Ϣ������ʧ�ܣ��ŷ���ERROR��ɾ���ڵ� */
    return (app_ret&comm_ret);
}

VOS_VOID diag_FwDealTimeOutCmdEntry(VOS_UINT32 ulCmdId)
{

    VOS_UINT32 ret = ERR_MSP_FAILURE;

    /*��ʱ���ظ�*/
    ret = diag_FwCmdTimeOutProc(ulCmdId);
    if(ret != ERR_MSP_SUCCESS)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_TIME_OUT_ENTRY_ERROR,ret,0,0);
    }

    /*ɾ����ʱ����ڵ�*/
    if(ret != ERR_MSP_INVALID_PARAMETER)
    {
        diag_FwDelCmdNode(ulCmdId);
    }

    return ;
}



VOS_VOID diag_FwDealDecodeCmdEntry(VOS_UINT8* pData,VOS_UINT32 ulLen)
{
    DIAG_FW_RX_INFO_STRU *pNode =VOS_NULL;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

    if((NULL == pData)||(0 == ulLen))
    {
       return;
    }

    /*����������ݷ���������*/
    pNode = diag_FwAddCmdToList(pData,ulLen);
    if (NULL == pNode)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY_ERROR,ret,ulLen,1);
        return ;
    }

    /*ת���������Ӧ��AGENTģ�鴦��*/
    ret = diag_FwForwardCmdToAgent(pNode,ulLen);
    if (ERR_MSP_SUCCESS != ret)
    {
        /*ɾ����ʱ��*/
        VOS_StopRelTimer(&pNode->fwCtrlTimer);

        /* �������ϣ�ɾ���ڵ�*/
        diag_FwDelCmdNode(pNode->ulCmdId);
    }
    return ;
}


VOS_VOID diag_FwDealAppAgentCnfEntry(VOS_UINT8* pData,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulCmdId =0;
    DIAG_FW_RX_INFO_STRU *pstRxinfo =NULL;
    VOS_UINT32 ret = ERR_MSP_FAILURE;

    if((NULL == pData)||(0 == ulLen))
    {
       return;
    }

    /*����CMDID���ҽڵ�*/
    ulCmdId = ((DIAG_CMD_AGENT_TO_FW_CNF_STRU*)pData)->ulCmdId;
    pstRxinfo = diag_FwGetExeCmdNode(ulCmdId);
    if(NULL == pstRxinfo)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_APP_CNF_ENTRY_ERROR, ulCmdId, ulLen, 0);
        return;
    }

    /*ɾ����ʱ��*/
    VOS_StopRelTimer(&pstRxinfo->fwCtrlTimer);

    /* MSP��ͨ����ظ�������CNF��������*/
    ret = diag_FwCmdCnfProc(pstRxinfo,((DIAG_CMD_AGENT_TO_FW_CNF_STRU*)pData)->aucData,(ulLen-sizeof(DIAG_CMD_AGENT_TO_FW_CNF_STRU)));
    if(ERR_MSP_SUCCESS !=ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_APP_CNF_ENTRY_ERROR,ret,ulCmdId,1);
    }

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    if(MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId) == DIAG_CMD_HOST_DISCONNECT)
    {
        if(ERR_MSP_SUCCESS != DRV_SOCP_VOTE(SOCP_VOTE_DIAG_APP, SOCP_VOTE_FOR_SLEEP))
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DIS_CONN_CFG, 0, 1, 1);
        }
        g_diagSocpIsEnable = FALSE;
    }
#endif

    /* �������ϣ�ɾ���ڵ�*/
    diag_FwDelCmdNode(pstRxinfo->ulCmdId);

    return;
}


VOS_VOID diag_FwDealAgentCnfEntry(VOS_UINT8* pData,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulCmdId =0;
    DIAG_FW_RX_INFO_STRU *pstRxinfo =NULL;
    VOS_UINT32 ret = ERR_MSP_FAILURE;

    if((NULL == pData)||(0 == ulLen))
    {
       return;
    }

    /*����CMDID���ҽڵ�*/
    ulCmdId = ((DIAG_CMD_AGENT_TO_FW_CNF_STRU*)pData)->ulCmdId;

    pstRxinfo = diag_FwGetExeCmdNode(ulCmdId);
    if(DIAG_IS_PS_CMD(ulCmdId&0xffff))
    {
        /* �Ҳ����ڵ㣬˵����IND����*/
        if(NULL == pstRxinfo)
        {
            /* ����IND��������*/
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_AGENT_PS_IND_ENTRY, ulCmdId, ulLen, 1);
            ret = diag_FwAnsyCmdIndProc(((DIAG_CMD_AGENT_TO_FW_CNF_STRU*)pData)->aucData,(ulLen-sizeof(DIAG_CMD_AGENT_TO_FW_CNF_STRU)),ulCmdId);
            if(ERR_MSP_SUCCESS !=ret)
            {
                DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_AGENT_PS_IND_ENTRY_ERROR,ret,ulCmdId,1);
            }
            return;
        }

        /*ɾ����ʱ��*/
        VOS_StopRelTimer(&pstRxinfo->fwCtrlTimer);

        /* PS͸������ظ�������CNF��������*/
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_AGENT_PS_CNF_ENTRY, ulCmdId, ulLen, 2);
        ret = diag_FwCmdCnfProc(pstRxinfo,((DIAG_CMD_AGENT_TO_FW_CNF_STRU*)pData)->aucData,(ulLen-sizeof(DIAG_CMD_AGENT_TO_FW_CNF_STRU)));
        if(ERR_MSP_SUCCESS !=ret)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_AGENT_PS_CNF_ENTRY_ERROR,ret,ulCmdId,1);
        }

        /* �������ϣ�ɾ���ڵ�*/
        diag_FwDelCmdNode(pstRxinfo->ulCmdId);
        return;
    }

    if(NULL == pstRxinfo)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_AGENT_CNF_ENTRY_ERROR, ulCmdId, ulLen, 0);
        return;
    }

    /*ɾ����ʱ��*/
    VOS_StopRelTimer(&pstRxinfo->fwCtrlTimer);

    /* MSP��ͨ����ظ�������CNF��������*/
    ret = diag_FwCmdCnfProc(pstRxinfo,((DIAG_CMD_AGENT_TO_FW_CNF_STRU*)pData)->aucData,(ulLen-sizeof(DIAG_CMD_AGENT_TO_FW_CNF_STRU)));
    if(ERR_MSP_SUCCESS !=ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_AGENT_CNF_ENTRY_ERROR,ret,ulCmdId,1);
    }

    /* �������ϣ�ɾ���ڵ�*/
    diag_FwDelCmdNode(pstRxinfo->ulCmdId);

    return;
}


VOS_UINT32 diag_FwGlobalInit(VOS_VOID)
{
    DIAG_FW_RX_INFO_STRU* pHeadNode = NULL;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

    /* ��ȡ����ͷ */
    pHeadNode= diag_FwGetDiagNodeInfo();

    /* ��ʼ���������� */
    blist_head_init(&pHeadNode->HiDiagFwList);

    /* �����ڵ㱣���ź���*/
    ret = VOS_SmBCreate(NULL, 1, VOS_SEMA4_FIFO,&g_DiagFwNodeSem);

    return ret;
}


VOS_VOID diag_FwSetChanSta(VOS_UINT32 flag)
{

    /*�����ǰҪ����״̬������״̬һ�£�����ı�*/
    if(((g_ulDiagCfgInfo&0x2)>>1)== flag)
    {
        return;
    }
    else
    {
        diag_CfgResetAllSwt();
#if (FEATURE_BSP_LCH_OM == FEATURE_ON)
        DRV_OM_SET_HSO_CONN_FLAG(0);
#endif
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
        (VOS_VOID)DRV_SOCP_VOTE(SOCP_VOTE_DIAG_APP, SOCP_VOTE_FOR_SLEEP);
        g_diagSocpIsEnable = FALSE;
#endif

        /*��״̬���͸�M��*/
        diag_SendMsg(MSP_PID_DIAG_FW,MSP_PID_DIAG_AGENT,ID_MSG_DIAG_HSO_DISCONN_IND,(VOS_UINT8*)&flag,sizeof(VOS_UINT32));
    }

    return;

}


VOS_UINT32 diag_FwMsgProcInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

    if (ip == VOS_IP_RESTART)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_INIT,ret,0,0);

        /*ȫ�ֱ�����ʼ��*/
        ret = diag_FwGlobalInit();
        if(ret != ERR_MSP_SUCCESS)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_INIT_ERROR,ret,0,1);
            return ret;
        }

        /*DIAG SOCP BUF��ʼ��*/
        ret = diag_BufCtrlGlobalInit();
        if(ret != ERR_MSP_SUCCESS)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_INIT_ERROR,ret,0,2);
            return ret;
        }

        /*ע���SCM�Ľ���Ŀ�Ļص�*/
        ret = SCM_RegDecoderDestProc(SOCP_DECODER_DST_LOM,(SCM_DECODERDESTFUCN)Diag_SocpDecodeDesDataProc);
        if(ret != ERR_MSP_SUCCESS)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_INIT_ERROR,ret,0,3);
            return ret;
        }

        /*����DIAG��ʼ��bit*/
        ret = diag_CfgSetGlobalBitValue(&g_ulDiagCfgInfo,DIAG_CFG_INIT_BIT,DIAG_CFG_SWT_OPEN);
        if(ret != ERR_MSP_SUCCESS)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_INIT_ERROR,ret,0,4);
            return ret;
        }
#if (FEATURE_OFF == FEATURE_MERGE_OM_CHAN)
        diag_PortSetConnStaCB((DIAG_PORT_CONNECT_STA_PFN)diag_FwSetChanSta );
#endif
    }

    return ret;
}


VOS_VOID diag_FwMsgProc(MsgBlock* pMsgBlock)
{
    REL_TIMER_MSG *pTimer =NULL;
    DIAG_DATA_MSG_STRU* pMsgTmp =NULL;
    /*lint --e{740, 142} */
    /*����ж�*/
    if (NULL == pMsgBlock)
    {
        return;
    }

    /*����ʼ����������˯��*/
	drx_msp_fid_vote_lock(DRX_DIAG_FW_VOTE);
    /*lint -save -e30*/
    /*���ݷ���PID��ִ�в�ͬ����*/
    switch(pMsgBlock->ulSenderPid)
    {
        /*��ʱ��Ϣ�����ճ�ʱ����ʽ������ظ�*/
        case DOPRA_PID_TIMER:
            diag_printf("fw cmd timer out!\n");
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_TIME_OUT_ENTRY,0,0,0);
            pTimer   = (REL_TIMER_MSG*)pMsgBlock;
            diag_FwDealTimeOutCmdEntry(pTimer->ulPara);
            break;

        /*����HDLC���������*/
        case MSP_PID_DIAG_FW:

            pMsgTmp = (DIAG_DATA_MSG_STRU*)pMsgBlock;
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY,0,pMsgTmp->ulLen,1);
            diag_FwDealDecodeCmdEntry(pMsgTmp->pContext,pMsgTmp->ulLen);
            break;

        /*����A�˷������Ļظ�*/
        case MSP_PID_DIAG_APP_AGENT:

            pMsgTmp = (DIAG_DATA_MSG_STRU*)pMsgBlock;
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_APP_CNF_ENTRY,0,pMsgTmp->ulLen,2);
            diag_FwDealAppAgentCnfEntry(pMsgTmp->pContext,pMsgTmp->ulLen);
            break;

        /*����M�˷������Ļظ� */
        case MSP_PID_DIAG_AGENT:

            pMsgTmp = (DIAG_DATA_MSG_STRU*)pMsgBlock;
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_AGENT_CNF_ENTRY,0,pMsgTmp->ulLen,3);
            diag_FwDealAgentCnfEntry(pMsgTmp->pContext,pMsgTmp->ulLen);
            break;
#if (FEATURE_ON == FEATURE_MERGE_OM_CHAN)
        case WUEAPP_PID_MUX:
            pMsgTmp = (DIAG_DATA_MSG_STRU*)pMsgBlock;
            if(ID_MSG_DIAG_HSO_DISCONN_IND == pMsgTmp->ulMsgId)
            {
                diag_FwSetChanSta(0);
            }
            else
            {
                diag_printf(" rcv from WUEAPP_PID_MUX err,msg id :0x%x\n",pMsgTmp->ulMsgId);
            }
            break;
#endif
        /*���յ�����PID�������Ĵ������ݣ����账�� */
        default:
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_FW_ERROR_ENTRY,0,0,4);
            break;
    }
    /*lint -restore +e30*/
    /*��������ɣ�����˯��*/
	drx_msp_fid_vote_unlock(DRX_DIAG_FW_VOTE);

    return;
}

VOS_UINT32 diag_FwDecodeDataCheck(VOS_UINT8 * pDataBuf)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
	MSP_SOCP_HEAD_STRU   *pstSocpStru =NULL;
	MSP_DIAG_HEAD_STRU   *pstDiagStru =NULL;

    pstSocpStru = (MSP_SOCP_HEAD_STRU *)pDataBuf;
    pstDiagStru = (MSP_DIAG_HEAD_STRU *)(pDataBuf + sizeof(MSP_SOCP_HEAD_STRU));

    /*���ж�SOCPͷ�Ƿ���ȷ*/
    if(pstSocpStru->usSId != MSP_SOCP_SID_DIAG_SERVER)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, pstSocpStru->usSId, (VOS_UINT32)0, 3);
        return ERR_MSP_NOT_EXIST;
    }

    if(((pstSocpStru->usSSId)>>4 != MSP_SOCP_HIGH4BIT_SSID_MCPU)
    && ((pstSocpStru->usSSId)>>4 != MSP_SOCP_HIGH4BIT_SSID_LTE_DSP)
    && ((pstSocpStru->usSSId)>>4 != MSP_SOCP_HIGH4BIT_SSID_TDS_DSP))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, (pstSocpStru->usSSId)>>4, (VOS_UINT32)0, 4);
        return ERR_MSP_NOT_SUPPORT;
    }

    /*���ж�DIAG ͷ�Ƿ���ȷ*/
    if(((pstDiagStru->ulID)>>28 != MSP_STRU_ID_28_31_GROUP_MSP)
    && ((pstDiagStru->ulID)>>28 != MSP_STRU_ID_28_31_GROUP_PS)
    && ((pstDiagStru->ulID)>>28 != MSP_STRU_ID_28_31_GROUP_LTE_DSP)
    && ((pstDiagStru->ulID)>>28 != MSP_STRU_ID_28_31_GROUP_TDS_DSP)
    && ((pstDiagStru->ulID)>>28 != MSP_STRU_ID_28_31_GROUP_BSP))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, (pstDiagStru->ulID)>>28, (VOS_UINT32)0, 5);
        return ERR_MSP_INVALID_PARAMETER;
    }

    return ret;
}


VOS_UINT32 diag_FwSendDecodeCmdToFw(VOS_UINT8 * pDataBuf, VOS_UINT32 ulLen)
{
    /*lint -save -e958*/
   VOS_UINT32 ret = ERR_MSP_SUCCESS;
    /*lint -restore*/
    /*������飬ȷ��HSO�·������Ƿ���ȷ*/
    ret = diag_FwDecodeDataCheck(pDataBuf);
    if(ret != ERR_MSP_SUCCESS)
    {
        diag_printf("diag_FwDecodeDataCheck ERROR!\n");
        return ret;
    }

    /*���͸�DIAG FW���д���*/
    ret = diag_SendMsg(MSP_PID_DIAG_FW, MSP_PID_DIAG_FW,ID_MSG_DIAG_CMD_REQ_FW_TO_FW,pDataBuf, ulLen);
    if(ret != ERR_MSP_SUCCESS)
    {
       DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, 0, 0, 6);
    }

    return ret;
}



VOS_UINT32 MSP_AppDiagFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRelVal = 0;
#if (FEATURE_ON == MBB_DLOAD)
    huawei_smem_info *smem_data = NULL;
    smem_data = (huawei_smem_info *)SRAM_DLOAD_ADDR;
    
    if (NULL == smem_data)
    {
        //hi_trace(HI_ERR,"Dload smem_data malloc fail!\n");
        return -1;
    }
    if(SMEM_DLOAD_FLAG_NUM == smem_data->smem_dload_flag)
    {
	    return VOS_OK;
    }
#endif
    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
            drx_msp_init();
#if (FEATURE_OFF == FEATURE_MERGE_OM_CHAN)
            ulRelVal = diag_PortInit();
            if (ulRelVal != VOS_OK)
            {
                return VOS_ERR;
            }
#endif
            ulRelVal = VOS_RegisterPIDInfo(MSP_PID_DIAG_FW, (Init_Fun_Type) diag_FwMsgProcInit, (Msg_Fun_Type) diag_FwMsgProc);

            if (ulRelVal != VOS_OK)
            {
                return VOS_ERR;
            }

            ulRelVal = VOS_RegisterPIDInfo(MSP_PID_DIAG_APP_AGENT, (Init_Fun_Type) diag_AppAgentMsgProcInit, (Msg_Fun_Type) diag_AppAgentMsgProc);

            if (ulRelVal != VOS_OK)
            {
                return VOS_ERR;
            }

            ulRelVal = VOS_RegisterMsgTaskPrio(MSP_FID_DIAG_ACPU, VOS_PRIORITY_M2);
            if (ulRelVal != VOS_OK)
            {
                return VOS_ERR;
            }
#if ((FEATURE_OFF == FEATURE_MERGE_OM_CHAN)&&(FEATURE_HISOCKET == FEATURE_ON))
			if(BSP_MODULE_SUPPORT == DRV_GET_WIFI_SUPPORT())
			{
	            ulRelVal = VOS_RegisterSelfTask(MSP_FID_DIAG_ACPU, (VOS_TASK_ENTRY_TYPE)diag_PortTask, VOS_PRIORITY_M2, 0x2000);    //lint !e64
	            if (VOS_NULL_BYTE  == ulRelVal)
	            {
	                return VOS_ERR;
	            }
			}
#endif
            break;
        default:
            break;
    }

    return VOS_OK;
}
/*lint -restore +e40*/


#if (FEATURE_OFF == FEATURE_MERGE_OM_CHAN)
VOS_UINT32 Diag_SocpDecodeDesDataProc(SOCP_DECODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT32 ulSize,VOS_UINT8 *pucRBData, VOS_UINT32 ulRBSize)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    VOS_UINT32 ulTotalLen = 0;
    VOS_UINT8* pData;
    VOS_UINT8* pCurData;
    VOS_UINT32 ulCurLen = 0;
    DIAG_SOCP_DECODE_PACKET_HEAD* HeadInfo;


    /*��μ��*/
    if(pucData == VOS_NULL)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, 0, 0, 0);
        return ERR_MSP_INVALID_PARAMETER;
    }

    ulTotalLen = ulSize + ulRBSize;
    if(!ulTotalLen)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, 0, 0, 1);
        return ERR_MSP_INVALID_PARAMETER;
    }

    pData = VOS_MemAlloc(MSP_PID_DIAG_FW,DYNAMIC_MEM_PT,ulTotalLen);
    if(pData == VOS_NULL)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, 0, 0, 2);
        return ERR_MSP_MALLOC_FAILUE;
    }

    VOS_MemCpy(pData,pucData,ulSize);

    /*�ؾ�ָ�����Ϊ��*/
    if((VOS_NULL != pucRBData)&&(0 != ulRBSize))
    {
        VOS_MemCpy(pData+ulSize,pucRBData,ulRBSize);
    }
    /*�α�ָ��*/
    pCurData = pData;
    while(1)/*lint !e716*/
    {
        HeadInfo = (DIAG_SOCP_DECODE_PACKET_HEAD*)(pCurData+ulCurLen);

        /*û��HISI��ͷ����Ϊ��Ч��*/
        if( HeadInfo->ulMagic != DIAG_SOCP_DECODE_HEAD_MAGIC )
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, 0, HeadInfo->ulMagic, 3);
            diag_printf("err packet head 0x%x ,0x%x!\n",HeadInfo->ulMagic,HeadInfo->ulDatalen);
            break;
        }
        /*ʣ�����ݳ���С�ڰ�ͷ��¼���ȣ���Ϊ��Ч��*/
        if( HeadInfo->ulDatalen >(ulTotalLen-ulCurLen-sizeof(DIAG_SOCP_DECODE_PACKET_HEAD)) )
        {
            diag_printf("%s enter here %d!\n",__func__,__LINE__);
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, HeadInfo->ulDatalen, ulCurLen, 4);
            break;
        }

        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE, enChanID, (VOS_UINT32)(HeadInfo->ulDatalen), 0);

        /*���͵�����*/
        ulRet = diag_FwSendDecodeCmdToFw(HeadInfo->data,HeadInfo->ulDatalen);
        if(ulRet)
        {
            DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, ulRet, 0, 5);
            break;
        }

        /*�ƶ�ָ�뵽��һ����*/
        ulCurLen += ((sizeof(DIAG_SOCP_DECODE_PACKET_HEAD) + HeadInfo->ulDatalen + 7)&(~7));

        /*��һ��������ʼ���ȼ��ϰ�ͷ���Ȳ��ܳ��������ܳ���*/
        if((ulCurLen + sizeof(DIAG_SOCP_DECODE_PACKET_HEAD)) >= ulTotalLen)
        {
            break;
        }
    }

    VOS_MemFree(MSP_PID_DIAG_FW,pData);
    return ulRet;
}
#else
VOS_UINT32 Diag_SocpDecodeDesDataProc(SOCP_DECODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT32 ulSize,VOS_UINT8 *pucRBData, VOS_UINT32 ulRBSize)
{
    VOS_UINT32 ulRet = ERR_MSP_SUCCESS;
    VOS_UINT32 ulTotalLen = 0;
    VOS_UINT8* pData;

    /*��μ��*/
    if(pucData == VOS_NULL)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, 0, 0, 0);
        return ERR_MSP_INVALID_PARAMETER;
    }

    ulTotalLen = ulSize + ulRBSize;
    if(!ulTotalLen)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, 0, 0, 1);
        return ERR_MSP_INVALID_PARAMETER;
    }

    pData = VOS_MemAlloc(MSP_PID_DIAG_FW,DYNAMIC_MEM_PT,ulTotalLen);
    if(pData == VOS_NULL)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR, 0, 0, 2);
        return ERR_MSP_MALLOC_FAILUE;
    }

    VOS_MemCpy(pData,pucData,ulSize);

    /*�ؾ�ָ�����Ϊ��*/
    if((VOS_NULL != pucRBData)&&(0 != ulRBSize))
    {
        VOS_MemCpy(pData+ulSize,pucRBData,ulRBSize);
    }

    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_DECODE_PACKET_RCVE, enChanID, (VOS_UINT32)ulTotalLen, 0);

    ulRet = diag_FwSendDecodeCmdToFw(pData,ulTotalLen);
    if(ulRet)
    {
        diag_printf("diag_FwSendDecodeCmdToFw failed ,ulRet = 0x%x\n",ulRet);
    }

    VOS_MemFree(MSP_PID_DIAG_FW,pData);
    return ulRet;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



