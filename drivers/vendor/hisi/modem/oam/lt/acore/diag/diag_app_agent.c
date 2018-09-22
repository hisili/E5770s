

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
/*lint -save -e322 -e7 -e537*/
#include  "vos.h"
#include <linux/slab.h>
#include  "diag_app_agent.h"
#include  "diag_common.h"
#include  "diag_debug.h"
#include  "diag_fw.h"
#include "msp_errno.h"
#include "msp_drx.h"
#include "diag_cfg.h"
#include "diag_port.h"
#include "diag_fs_proc.h"
#include "drx_msp_api.h"
#include "DrvInterface.h"
#include "NVIM_Interface.h"
/*lint -restore*/
/*lint -save -e767 ԭ��:Log��ӡ*/
#define    THIS_FILE_ID          MSP_FILE_ID_DIAG_APP_AGENT_C
/*lint -restore +e767*/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#define DIAG_CMD_TOTAL_FILE                    (0xFFFFFFFF)

DIAG_NV_BIN_LOAD_INFOR g_DiagNvLoadInfo ={0};

DRV_RESET_CALLCBFUN_MOMENT g_DiagResetingCcore = DRV_RESET_CALLCBFUN_MOEMENT_INVALID;
/*****************************************************************************
  3 Function
*****************************************************************************/
VOS_UINT32 diag_PsProcEntry (VOS_UINT8* pstReq , VOS_UINT32 ulCmdId)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
	DIAG_CMD_REPLAY_SET_REQ_STRU *pstReplay=NULL;
	DIAG_CMD_REPLAY_SET_CNF_STRU stCnf={0};

    pstReplay = (DIAG_CMD_REPLAY_SET_REQ_STRU*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    switch(MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId))
    {
        case DIAG_CMD_PS_REPLAY_SET:
			ret = diag_SendMsg(diag_GetAgentPid(),PS_PID_MM,ID_MSG_DIAG_CMD_REPLAY_TO_PS,(VOS_UINT8*)pstReplay,\
							sizeof(DIAG_CMD_REPLAY_SET_REQ_STRU));
            break;
		default:
            break;
    }

	stCnf.ulRet = ret;

	/*�����FW�ظ�*/
	ret = diag_AgentCnfFun((VOS_UINT8*)&stCnf,ulCmdId,sizeof(DIAG_CMD_REPLAY_SET_CNF_STRU));
    return ret;
}


VOS_UINT32 diag_NvProcEntry (VOS_UINT8* pstReq , VOS_UINT32 ulCmdId)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

    switch(MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId))
    {
        case DIAG_CMD_NV_RD:
            ret = diag_NvRdProc(pstReq,ulCmdId);
            break;
        case DIAG_CMD_NV_WR:
            ret = diag_NvWrProc(pstReq,ulCmdId);
            break;
        default:
            break;

    }
    return ret;
}


VOS_UINT32 diag_NvRdProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_NV_QRY_REQ_STRU* pstNVQryReq = NULL;
    DIAG_CMD_NV_QRY_CNF_STRU* pstNVQryCnf = NULL;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulSetRet = 0;
    VOS_UINT32 ulNVLen = 0;

    pstNVQryReq = (DIAG_CMD_NV_QRY_REQ_STRU*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

     /*��������ID��ȡNV���*/
     ret = NV_GetLength((BSP_U16)(pstNVQryReq->ulNVId), (BSP_U32*)&ulNVLen);
     if(ERR_MSP_SUCCESS != ret)
     {
     	 diag_printf("[%s]:ulNVId=0x%x,ulNVLen=%d!\n",__FUNCTION__,pstNVQryReq->ulNVId,ulNVLen);
         return ERR_MSP_FAILURE;
     }

     pstNVQryCnf = VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT,sizeof(DIAG_CMD_NV_QRY_CNF_STRU)+ulNVLen);

     if(NULL  == pstNVQryCnf)
     {
     	 diag_printf("[%s]:malloc error!\n",__FUNCTION__);
         return ERR_MSP_MALLOC_FAILUE;
     }

     ulSetRet = NVM_Read(pstNVQryReq->ulNVId, pstNVQryCnf->aucData, ulNVLen);
     if(ulSetRet != ERR_MSP_SUCCESS)
     {
        diag_printf("[%s]:NV READ ERR 0x%x,ulNVId=0x%x\n",__FUNCTION__,ulSetRet,pstNVQryReq->ulNVId);
     }
     DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_NV_RD,pstNVQryReq->ulNVId,ulSetRet,0);

     pstNVQryCnf->ulNVId = pstNVQryReq->ulNVId;
     pstNVQryCnf->ulRc   = ulSetRet;
     pstNVQryCnf->ulDataSize = ulNVLen;

    /*����ظ���FW*/
    ret = diag_AgentCnfFun((VOS_UINT8*)pstNVQryCnf,ulCmdId,sizeof(DIAG_CMD_NV_QRY_CNF_STRU) + ulNVLen);

    VOS_MemFree(MSP_PID_DIAG_APP_AGENT, pstNVQryCnf);

    return ret;
}


VOS_UINT32 diag_NvWrProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_NV_WR_REQ_STRU* pstNVWRReq = NULL;
    DIAG_CMD_NV_WR_CNF_STRU stNVWRCnf = {0};
    VOS_UINT32 ret;
    VOS_UINT32 ulSetRet;

    pstNVWRReq = (DIAG_CMD_NV_WR_REQ_STRU*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    /*����ж�*/
    if((NULL == pstNVWRReq) ||(pstNVWRReq->ulDataSize > NV_ITEM_MAXSIZE)||
      (sizeof(DIAG_CMD_NV_WR_REQ_STRU) > ((MSP_DIAG_HEAD_STRU *)((VOS_UINT8*)pstReq+ \
       sizeof(MSP_SOCP_HEAD_STRU)))->ulDataSize-sizeof(MSP_DIAG_DATA_REQ_STRU)))
    {
    	diag_printf("[%s]:ulNVId=0x%x,ulNVLen=%d!\n",__FUNCTION__,pstNVWRReq->ulNVId,pstNVWRReq->ulDataSize);
        return ERR_MSP_INVALID_PARAMETER;
    }

    /*д��NV��*/
    ulSetRet = NVM_Write(pstNVWRReq->ulNVId, pstNVWRReq->aucData, pstNVWRReq->ulDataSize);
    if(ulSetRet != ERR_MSP_SUCCESS)
    {
       diag_printf("[%s]:NV Write ERR 0x%x,ulNVId=0x%x\n",__FUNCTION__,ulSetRet,pstNVWRReq->ulNVId);
    }
	DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_NV_WR,pstNVWRReq->ulNVId,ulSetRet,0);

    stNVWRCnf.ulNVId = pstNVWRReq->ulNVId;
    stNVWRCnf.ulRc   = ulSetRet;

    /*����ظ���FW*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stNVWRCnf,ulCmdId,sizeof(DIAG_CMD_NV_WR_CNF_STRU));


    return ret;

}

#if (FEATURE_OFF == FEATURE_MERGE_OM_CHAN)

VOS_UINT32 diag_LogSaveProc (VOS_UINT8* pstReq , VOS_UINT32 ulCmdId)
{
    DIAG_CMD_SET_LPD_MODE_REQ_STRU* pstLdpReq;
    DIAG_CMD_SET_LPD_MODE_CNF_STRU stLdpCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulSetRet;

    pstLdpReq = (DIAG_CMD_SET_LPD_MODE_REQ_STRU*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    stLdpCnf.ulSDFileSaveTime = pstLdpReq->ulSDFileSaveTime;
    stLdpCnf.ulLpdMode = pstLdpReq->ulLpdMode;
    stLdpCnf.ulSDFileSize = pstLdpReq->ulSDFileSize;
    VOS_MemCpy(stLdpCnf.ucSDFileName,pstLdpReq->ucSDFileName,sizeof(pstLdpReq->ucSDFileName));

    ulSetRet = diag_SetLogCtrlInfo(pstLdpReq);
	DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_LOG_SAVE,pstLdpReq->ulLpdMode,ulSetRet,0);

    stLdpCnf.ulRc = ulSetRet;

    /*�����FW�ظ�*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stLdpCnf,ulCmdId,sizeof(DIAG_CMD_SET_LPD_MODE_CNF_STRU));

    return ret;

}
#endif

VOS_UINT32 g_ulCmdId;


VOS_UINT32 diag_PsTransCnfProc(VOS_UINT8* pstCnf ,VOS_UINT32 ulLen)
{
    VOS_UINT32 ulCmdId = 0;
    VOS_UINT32 ret =0;
    /*VOS_UINT32 ulOffsetLen =0;*/
    VOS_UINT32 ulMsgId =0;
#if 0
    ulMsgId =  *((VOS_UINT32*)(pstCnf + DIAG_PS_TRANS_HEAD_LEN));
    ulOffsetLen = DIAG_IS_GUPS_MSG_ID(ulMsgId)? DIAG_GUPS_TRANS_CMD_HEAD_LEN : DIAG_LPS_TRANS_CMD_HEAD_LEN;
    ulCmdId = *((VOS_UINT32*)(pstCnf+ulOffsetLen));

	if(!DIAG_IS_PS_CMD(MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId)))
	{
		return ERR_MSP_INVALID_OP;
	}
#endif

    ulCmdId = g_ulCmdId;

	DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_PS_TRANS_CNF, ulMsgId, ulCmdId,0);

    ret = diag_AgentCnfFun((VOS_UINT8*)pstCnf, ulCmdId, ulLen);

    return ret;
}



VOS_UINT32 diag_PsTransProcEntry(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulPsCmdParasize = 0;
    DIAG_PS_MSG_STRU* pstSendReq = NULL;
    VOS_UINT32 ulCmdId = 0;

    ulPsCmdParasize = ((MSP_DIAG_HEAD_STRU*)DIAG_OFFSET_SOCP_GET_DIAG_HEAD(pstReq))->ulDataSize - sizeof(MSP_DIAG_DATA_REQ_STRU);

 	ulCmdId = ((MSP_DIAG_HEAD_STRU*)DIAG_OFFSET_SOCP_GET_DIAG_HEAD(pstReq))->ulID;

    g_ulCmdId = ulCmdId;

     /* ���͸������*/
    pstSendReq = (DIAG_PS_MSG_STRU*)((MSP_DIAG_DATA_REQ_STRU*)DIAG_OFFSET_SOCP_DIAG_GET_DIAG_DATA(pstReq))->ucData;

	DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_PS_TRANS_REQ,0,0,0);

    pstSendReq->ulSenderPid = MSP_PID_DIAG_APP_AGENT;

	return diag_SendPsTransMsg(pstSendReq->ulReceiverPid, (VOS_UINT8*)pstSendReq, ulPsCmdParasize);
}


VOS_UINT32 diag_AppAgentDispatchCmd(VOS_UINT8* pstReq )
{
    VOS_UINT32 ret =ERR_MSP_FAILURE;
    VOS_UINT32 ulCmdId = 0;

    if(NULL == pstReq)
    {
        return ret;
    }

    ulCmdId = (((MSP_DIAG_HEAD_STRU*)DIAG_OFFSET_SOCP_GET_DIAG_HEAD(pstReq))->ulID);
    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_APP_AGENT_DISPATCH_CMD,ulCmdId,0,0);

    if(MSP_STRU_ID_28_31_GROUP_MSP == MSP_STRU_ID_28_31_CMD_GROUP(ulCmdId))
    {
        switch (MSP_STRU_ID_16_23_CMD_TYPE(ulCmdId))
        {
            /*���ݶ����ֶ������Ǹ�ps��͸�������msp�ڲ��������PMU������*/
            case MSP_STRU_ID_16_23_MSP_CMD:
                switch(MSP_STRU_ID_8_11_CMD_CATEGORY(ulCmdId))
                {
                    /*��������ID��Χ����������msp�ڲ�����*/
					case DIAG_CATEGORY_PS:
						ret = diag_PsProcEntry(pstReq,ulCmdId);
                        break;
                    case DIAG_CATEGORY_CFG:
                        ret = diag_CfgProcEntry(pstReq,ulCmdId);
                        break;
                    case DIAG_CATEGORY_NV:
                        ret = diag_NvProcEntry(pstReq,ulCmdId);
                        break;
                    case DIAG_CATEGORY_FS:
                        ret = diag_FsProcEntry(pstReq,ulCmdId);
                        break;
                    default:
                        break ;
                }
                break;

            case MSP_STRU_ID_16_23_PS_TRANS:
                ret = diag_PsTransProcEntry(pstReq);
                break;

            case MSP_STRU_ID_16_23_SYS_CMD:
                switch(MSP_STRU_ID_8_11_CMD_CATEGORY(ulCmdId))
                {
                    case DIAG_CATEGORY_CONN:
                        ret = diag_ConnProcEntry(pstReq,ulCmdId);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
#if (FEATURE_BSP_LCH_OM == FEATURE_ON)
    else if(MSP_STRU_ID_28_31_GROUP_BSP == MSP_STRU_ID_28_31_CMD_GROUP(ulCmdId))
    {
        switch (MSP_STRU_ID_16_23_CMD_TYPE(ulCmdId))
        {
            case MSP_STRU_ID_16_23_BSP_CMD:
                ret =  diag_BspProcEntry(pstReq,ulCmdId);
                break;

            default:
                break;
        }
    }
#endif
    else
    {

    }
    return ret;
}


#if (FEATURE_BSP_LCH_OM == FEATURE_ON)


VOS_UINT32 diag_BspProcEntry(VOS_UINT8* pstReq , VOS_UINT32 ulCmdId)
{
    VOS_UINT32 ret;

    switch (MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId))
    {
        case DIAG_CMD_BSP_LOG_SET_ACORE:
        case DIAG_CMD_BSP_LOG_SET_CCORE:
            ret = diag_BspLogProcEntry(pstReq,ulCmdId);
            break;

        case DIAG_CMD_BSP_SYSVIEW_SWT_ACORE:
        case DIAG_CMD_BSP_SYSVIEW_SWT_CCORE:
        case DIAG_CMD_BSP_CPU_SWT_ACORE:
        case DIAG_CMD_BSP_CPU_SWT_CCORE:
            ret = diag_BspSysviewProcEntry(pstReq,ulCmdId);
            break;

        case DIAG_CMD_UTRACE_START:
        case DIAG_CMD_UTRACE_TERMINATE:
            ret = diag_BspUtraceProcEntry(pstReq,ulCmdId);
            break;

        default:
            ret = ERR_MSP_FAILURE;
            break ;
    }

    return ret;
}


VOS_UINT32 diag_BspUtraceProcEntry (VOS_UINT8* pstReq , VOS_UINT32 ulCmdId)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

	VOS_UINT8 *pdata =NULL;
	DIAG_CMD_COMMON_CNF stUtraceCnf ={0};


    diag_printf("[%s enter!]\n",__FUNCTION__);



    pdata = (VOS_UINT8*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    switch(MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId))
    {
        case DIAG_CMD_UTRACE_START:
            ret = DRV_UTRACE_START(pdata);
            break;
        case DIAG_CMD_UTRACE_TERMINATE:
            ret = DRV_UTRACE_TERMINATE(pdata);
            break;
        default:
            break;

    }

	stUtraceCnf.ulRet = ret;
	ret = diag_AgentCnfFun((VOS_UINT8*)&stUtraceCnf,ulCmdId,sizeof(DIAG_CMD_COMMON_CNF));

    return ret;
}


VOS_UINT32 diag_BspLogProcEntry(VOS_UINT8* pstReq , VOS_UINT32 ulCmdId)
{
    /*lint -save -e438 -e550*/
    VOS_UINT32  ret = ERR_MSP_SUCCESS;
    VOS_UINT32 data_len = 0;
    VOS_UINT32 cnf_data_len = 0;
    MSP_DIAG_HEAD_STRU *pstDiagHead         = VOS_NULL;
    DIAG_bsp_log_swt_cfg_s *pstLogSet = VOS_NULL;
    DIAG_BSP_PRINT_LOG_SWT_CNF_STRU  stLogSetCnf  = {0};
    VOS_UINT8 *pstCnf = VOS_NULL;

    pstDiagHead = (MSP_DIAG_HEAD_STRU*)(DIAG_OFFSET_SOCP_GET_DIAG_HEAD(pstReq));

    if(DIAG_CMD_BSP_LOG_SET_ACORE == (MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId)) )
    {
        pstLogSet = (DIAG_bsp_log_swt_cfg_s *)DIAG_OFFSET_HEAD_GET_DATA(pstReq);
        data_len = pstDiagHead->ulDataSize  - sizeof(MSP_DIAG_DATA_REQ_STRU);
        stLogSetCnf.ulRet  = ERR_MSP_SUCCESS;
        pstCnf = (VOS_UINT8*)&stLogSetCnf ;
        cnf_data_len = sizeof(DIAG_BSP_PRINT_LOG_SWT_CNF_STRU);
    }
    else if(DIAG_CMD_BSP_LOG_SET_CCORE == (MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId)))
    {
        ret = ERR_MSP_SUCCESS;
    }
    else
    {
        ret = ERR_MSP_FAILURE;
    }

    if(VOS_NULL!=pstCnf)
    {
        ret = diag_AgentCnfFun(pstCnf,ulCmdId,cnf_data_len);
    }

    return ret;
    /*lint -restore*/
}



VOS_UINT32 diag_BspSysviewProcEntry(VOS_UINT8* pstReq , VOS_UINT32 ulCmdId)
{
    VOS_UINT32  ret ;
    VOS_UINT32 cnf_data_len = 0;

    DIAG_BSP_SYVIEW_SWT_CFG_STRU *pstSysviewSet = VOS_NULL;
    DIAG_BSP_SYVIEW_SWT_CNF_STRU  *pstLogSysviewCnf  = VOS_NULL;
    VOS_UINT8 *pstCnf = VOS_NULL;



    if((DIAG_CMD_BSP_SYSVIEW_SWT_ACORE == (MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId)))
        ||(DIAG_CMD_BSP_CPU_SWT_ACORE == (MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId))))
    {
        pstSysviewSet = (DIAG_BSP_SYVIEW_SWT_CFG_STRU *)DIAG_OFFSET_HEAD_GET_DATA(pstReq);

        ret  = DRV_SYSVIEW_SWT_SET(pstSysviewSet->trace_type,pstSysviewSet->trace_swt,pstSysviewSet->period);

        if(ret  == ERR_MSP_SUCCESS)
        {
            if((pstSysviewSet->trace_type ==SYSVIEW_TASK_INFO )&&(pstSysviewSet->trace_swt ==1 ))
            {
                cnf_data_len = sizeof(DIAG_BSP_SYVIEW_SWT_CNF_STRU)+sizeof(DIAG_BSP_TASK_INFO_STRU)*128;
                pstLogSysviewCnf =(DIAG_BSP_SYVIEW_SWT_CNF_STRU*)VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT,cnf_data_len);
                if(VOS_NULL == pstLogSysviewCnf)
                {
                    diag_printf("[%s]:malloc error!\n",__FUNCTION__);
                    return ERR_MSP_MALLOC_FAILUE;
                }
                pstLogSysviewCnf->ullen = sizeof(DIAG_BSP_TASK_INFO_STRU)*128;
                DRV_GET_ALL_TASK_ID_NAME((pstLogSysviewCnf->st_task_info), sizeof(DIAG_BSP_TASK_INFO_STRU)*128);
            }
            else
            {
                cnf_data_len = sizeof(DIAG_BSP_SYVIEW_SWT_CNF_STRU);
                pstLogSysviewCnf =(DIAG_BSP_SYVIEW_SWT_CNF_STRU*)VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT,cnf_data_len);
                if(VOS_NULL == pstLogSysviewCnf)
                {
                    diag_printf("[%s]:malloc error!\n",__FUNCTION__);
                    return ERR_MSP_MALLOC_FAILUE;
                }
                pstLogSysviewCnf->ullen  = 0;

            }

        }
        else
        {
            cnf_data_len = sizeof(DIAG_BSP_SYVIEW_SWT_CNF_STRU);
            pstLogSysviewCnf =(DIAG_BSP_SYVIEW_SWT_CNF_STRU*)VOS_MemAlloc(MSP_PID_DIAG_APP_AGENT, DYNAMIC_MEM_PT,cnf_data_len);
            if(VOS_NULL == pstLogSysviewCnf)
            {
                diag_printf("[%s]:malloc error!\n",__FUNCTION__);
                return ERR_MSP_MALLOC_FAILUE;
            }
            pstLogSysviewCnf->ullen  = 0;

        }

        pstLogSysviewCnf->ulRet = ret;
        pstLogSysviewCnf->trace_type =pstSysviewSet->trace_type;
        pstCnf = (VOS_UINT8*)pstLogSysviewCnf ;

    }
    else if((DIAG_CMD_BSP_SYSVIEW_SWT_CCORE == (MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId)))
                ||(DIAG_CMD_BSP_CPU_SWT_CCORE == (MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId))))
    {
        ret = ERR_MSP_SUCCESS;
    }
    else
    {
        ret = ERR_MSP_INVALID_PARAMETER;
    }

    if(VOS_NULL!=pstCnf)
    {
        ret = diag_AgentCnfFun(pstCnf,ulCmdId,cnf_data_len);
         VOS_MemFree(diag_GetAgentPid(), pstCnf);
    }

    return ret;
}
#endif


VOS_UINT32 diag_AppAgentMsgProcInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_CHAR * resetName = "DIAG";  /*C�˵�����λ������*/
    VOS_INT    resetLevel = 49;
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    if (ip == VOS_IP_RESTART)
    {
        (VOS_VOID)DRV_SOCP_VOTE(SOCP_VOTE_DIAG_APP, SOCP_VOTE_FOR_SLEEP);
        (VOS_VOID)DRV_SOCP_VOTE(SOCP_VOTE_DIAG_DEC, SOCP_VOTE_FOR_SLEEP);
    }
#endif

    if(ip == VOS_IP_LOAD_CONFIG)
    {
        ret = (VOS_UINT32)DRV_CCORERESET_REGCBFUNC(resetName, (pdrv_reset_cbfun)diag_ResetCcoreCB, 0, resetLevel);
        if(ret)
        {
            diag_printf("diag register ccore reset fail\n");
        }
    }

	return ret;
}

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
/*SOCP�Ƿ����*/
VOS_UINT32 g_diagSocpIsEnable = FALSE;
DIAG_SOCP_VOTE_INFO_STRU g_stDiagVoteInfo[SOCP_VOTE_ID_BUTT];


VOS_VOID diag_ShowSocpVoteInfo(VOS_VOID)
{
    diag_printf("************DIAG SOCP VOTE INFO*************\n");
    diag_printf("GU OM APP  : %-5s    0x%x\n", (g_stDiagVoteInfo[SOCP_VOTE_GU_OM_APP].ulVoteType == 0) ? "SLEEP" : "WAKE", g_stDiagVoteInfo[SOCP_VOTE_GU_OM_APP].ulVoteTime);
    diag_printf("GU OM COMM : %-5s    0x%x\n", (g_stDiagVoteInfo[SOCP_VOTE_GU_OM_COMM].ulVoteType == 0) ? "SLEEP" : "WAKE", g_stDiagVoteInfo[SOCP_VOTE_GU_OM_COMM].ulVoteTime);
    diag_printf("GU DSP     : %-5s    0x%x\n", (g_stDiagVoteInfo[SOCP_VOTE_GU_DSP].ulVoteType == 0) ? "SLEEP" : "WAKE", g_stDiagVoteInfo[SOCP_VOTE_GU_DSP].ulVoteTime);
    diag_printf("DIAG COMM  : %-5s    0x%x\n", (g_stDiagVoteInfo[SOCP_VOTE_DIAG_COMM].ulVoteType == 0) ? "SLEEP" : "WAKE", g_stDiagVoteInfo[SOCP_VOTE_DIAG_COMM].ulVoteTime);
    diag_printf("SOCP STATUS: %s\n", (g_diagSocpIsEnable == TRUE) ? "ENABLE" : "DISABLE");
}


VOS_VOID diag_SocpVoteMsgProc(MsgBlock* pMsgBlock)
{
    DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU * voteCnf;
    DIAG_MSG_SOCP_VOTE_REQ_STRU * voteReq;
    VOS_INT32 ret;
    /*lint -save -e740*/
    voteReq = (DIAG_MSG_SOCP_VOTE_REQ_STRU *)pMsgBlock;
    /*lint -restore*/
    DIAG_DEBUG_SDM_FUN(EN_DIAG_APP_SOCP_VOTE, voteReq->ulVoteId, voteReq->ulVoteType, 0);
    if(voteReq->ulVoteId >= SOCP_VOTE_ID_BUTT)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_APP_SOCP_VOTE_ERR, voteReq->ulVoteId, voteReq->ulVoteType, 1);
        diag_printf("%s: invalid vote id 0x%x\n", __FUNCTION__, voteReq->ulVoteId);
        return;
    }

    g_stDiagVoteInfo[voteReq->ulVoteId].ulVoteId = voteReq->ulVoteId;
    g_stDiagVoteInfo[voteReq->ulVoteId].ulVoteType = voteReq->ulVoteType;
    g_stDiagVoteInfo[voteReq->ulVoteId].ulVoteTime = BSP_GetSliceValue();

    ret = DRV_SOCP_VOTE(voteReq->ulVoteId, voteReq->ulVoteType);
    if(ERR_MSP_SUCCESS != ret)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_APP_SOCP_VOTE_ERR, voteReq->ulVoteId, voteReq->ulVoteType, 2);
        diag_printf("%s: 0x%x DRV_SOCP_VOTE ERR\n", __FUNCTION__, voteReq->ulVoteId);
    }

    /* ����Ʊ�Żظ� */
    if(voteReq->ulVoteType == SOCP_VOTE_FOR_SLEEP)
    {
        return;
    }
    /*lint -save -e740*/
    voteCnf = (DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU *)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, sizeof(DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU) - 20);
    /*lint -restore*/
    if(voteCnf == NULL)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_APP_SOCP_VOTE_ERR, voteReq->ulVoteId, voteReq->ulVoteType, 3);
        diag_printf("%s: 0x%x ALLOC MSG ERR\n", __FUNCTION__, voteReq->ulVoteId);
        return;
    }

    voteCnf->ulReceiverPid = voteReq->ulSenderPid;
    voteCnf->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;
    voteCnf->ulLength      = sizeof(DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU) - 20;
    voteCnf->ulVoteId      = voteReq->ulVoteId;
    voteCnf->ulVoteType    = voteReq->ulVoteType;
    voteCnf->ulVoteRst     = (VOS_UINT32)ret;

    if(ERR_MSP_SUCCESS != VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, voteCnf))
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_APP_SOCP_VOTE_ERR, voteReq->ulVoteId, voteReq->ulVoteType, 4);
        diag_printf("%s: 0x%x SEND MSG ERR\n", __FUNCTION__, voteReq->ulVoteId);
    }
}


VOS_VOID diag_PortDataProc(MsgBlock* pMsgBlock)
{
    DIAG_DATA_MSG_STRU * pMsgTmp =NULL;
    DIAG_PORT_DATA_BUF_STRU * dataNode;
    /*lint -save -e740*/
    pMsgTmp = (DIAG_DATA_MSG_STRU *)pMsgBlock;
    /*lint -restore*/
    if(pMsgTmp->ulMsgId != ID_MSG_DIAG_CMD_PORT_REQ_TO_APP_AGENT)
    {
        diag_printf("%s: invalid msg id 0x%x\n", __func__, pMsgTmp->ulMsgId);
        return;
    }

    if(g_diagSocpIsEnable != TRUE)
    {
        if(ERR_MSP_SUCCESS != DRV_SOCP_VOTE(SOCP_VOTE_DIAG_APP, SOCP_VOTE_FOR_WAKE))
        {
            diag_printf("%s: diag app vote fail\n", __func__);
            return;
        }

        g_diagSocpIsEnable = TRUE;
    }

    if(ERR_MSP_SUCCESS != DRV_SOCP_VOTE(SOCP_VOTE_DIAG_DEC, SOCP_VOTE_FOR_WAKE))
    {
        diag_printf("%s: diag dec vote fail\n", __func__);
        return;
    }

    for(;;)
    {
        dataNode = diag_PortGetNodeFromDataBuf();
        if(dataNode == NULL)
        {
            break;
        }
        diag_PortSendDataToSocp(dataNode);
    }

    (VOS_VOID)DRV_SOCP_VOTE(SOCP_VOTE_DIAG_DEC, SOCP_VOTE_FOR_SLEEP);
}
#endif


VOS_VOID diag_AppAgentMsgProc(MsgBlock* pMsgBlock)
{
    DIAG_DATA_MSG_STRU* pMsgTmp =NULL;
    /*lint --e{740, 142} */
    /*����ж�*/
    if (NULL == pMsgBlock)
    {
        return;
    }

    /*����ʼ����������˯��*/
	drx_msp_fid_vote_lock(DRX_DIAG_APP_AGENT_VOTE);
     /*lint -save -e30*/
    /*���ݷ���PID��ִ�в�ͬ����*/
    switch(pMsgBlock->ulSenderPid)
    {
            /*����HDLC��������� */
        case MSP_PID_DIAG_FW:
            pMsgTmp = (DIAG_DATA_MSG_STRU*)pMsgBlock;

            /*��������ID�ַ�����*/
            diag_AppAgentDispatchCmd(pMsgTmp->pContext);
            break;

        case PS_PID_OM:
		case PS_PID_ESM:
		case PS_PID_PDCP_UL:
		case PS_PID_MM:
        case PS_PID_ERRC:
            diag_PsTransCnfProc((VOS_UINT8*)pMsgBlock, (pMsgBlock->ulLength + VOS_MSG_HEAD_LENGTH));
            break;

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
        /*ͶƱ��Ϣ*/
        case MSP_PID_DIAG_AGENT:
        case WUEPS_PID_OM:
        case ACPU_PID_OM:
        case DSP_PID_APM:
            diag_SocpVoteMsgProc(pMsgBlock);
            break;

        /*�˿����ݴ�����Ϣ*/
        case MSP_PID_DIAG_APP_AGENT:
            diag_PortDataProc(pMsgBlock);
            break;
#endif
        default:
            break;

   }
    /*lint -restore*/
   /*����ʼ����������˯��*/
   drx_msp_fid_vote_unlock(DRX_DIAG_APP_AGENT_VOTE);

   return ;
}

/*****************************************************************************
 Function Name   : diag_ResetCcoreCB
 Description     : ���modem������λ�ص�����
 Input           : enParam
 Output          : None
 Return          : VOS_VOID
*****************************************************************************/
VOS_INT diag_ResetCcoreCB(DRV_RESET_CALLCBFUN_MOMENT enParam, int userdata)
{
    VOS_INT ret = ERR_MSP_SUCCESS;
    if(enParam == DRV_RESET_CALLCBFUN_RESET_BEFORE)
    {
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
        (VOS_VOID)DRV_SOCP_VOTE(SOCP_VOTE_DIAG_COMM, SOCP_VOTE_FOR_WAKE);
        (VOS_VOID)DRV_SOCP_VOTE(SOCP_VOTE_GU_OM_COMM, SOCP_VOTE_FOR_WAKE);
        (VOS_VOID)DRV_SOCP_VOTE(SOCP_VOTE_GU_DSP, SOCP_VOTE_FOR_WAKE);
#endif
        g_DiagResetingCcore = DRV_RESET_CALLCBFUN_RESET_BEFORE;
        ret += (VOS_INT)DIAG_ReportCommand(DIAG_CMD_MODEM_WILL_RESET, sizeof(VOS_UINT32), &enParam);
        if((ret != ERR_MSP_NO_INITILIZATION)
            &&( ERR_MSP_SUCCESS != ret))
        {
            diag_printf("report ccore reset fail\n");
        }
    }
    else if(enParam == DRV_RESET_CALLCBFUN_RESET_AFTER)
    {
        g_DiagResetingCcore = DRV_RESET_CALLCBFUN_RESET_AFTER;
    }
    else
    {
        diag_printf("diag_ResetCcoreCB enParam error\n");
    }
    return ERR_MSP_SUCCESS;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

