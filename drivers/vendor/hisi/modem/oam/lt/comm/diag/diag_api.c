


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint --e{10,718,746,628}*/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
/*lint -save -e537*/
#include  "vos.h"
#include  "diag_common.h"
#include  "diag_buf_ctrl.h"
#include  "SOCPInterface.h"
#include  "diag_debug.h"
#include  "diag_api.h"
#include  "diag_cfg.h"
#include  "msp_diag.h"
#include  "msp_errno.h"
#include  "osm.h"
#include  "DrvInterface.h"
/*lint -restore*/

/*lint -save -e767 ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_API_C
/*lint -restore +e767*/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


VOS_UINT32 diag_CheckMsgPara(DIAG_AIR_MSG_LOG_STRU* pstRptMessage);
VOS_UINT32 diag_GetLayerMsgCfg(VOS_UINT32 ulCatId, VOS_UINT32 ulMsgId);
VOS_UINT32 diag_GetLayerSrcCfg(VOS_UINT32 ulModuleId);
VOS_UINT32 diag_GetLayerDstCfg(VOS_UINT32 ulModuleId);
VOS_UINT32 diag_GetLayerCfg(VOS_UINT32 ulSrcModuleId, VOS_UINT32 ulDstModuleId, VOS_UINT32 ulMsgId);
VOS_UINT32 diag_GetUserPlaneCfg(VOS_UINT32 ulMsgId);
VOS_UINT32 diag_GetPrintCfg(VOS_UINT32 ulModuleId, VOS_UINT32 ulLevel);
/*****************************************************************************
  3 Function
*****************************************************************************/


/*lint -save -e958*/
VOS_VOID diag_SocpPsLogPkt(VOS_UINT8 * pstSocpPackt, VOS_UINT8 ucMsgType, VOS_UINT32 ulCmdParaLen)
{
    VOS_UINT64 ulTime = 0;

    /* ��SOCP��*/
    ulTime                           = diag_GetFrameTime();
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->usSId              = MSP_SOCP_SID_DIAG_SERVER;
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->usSSId             = MSP_SOCP_HIGH4BIT_SSID;    // ����λ
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->ucServiceSessionId = MSP_SOCP_SERVER_SESSION_ID;
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->ucMsgType          = MSP_SOCP_MSG_TYPE_IND;
    VOS_MemCpy(((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->aucTimeData, &ulTime, sizeof(VOS_UINT64));
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->ulMsgTransId = (g_DiagLogPktNum.ulIndNum)++;

    /* ����ṹ��ID(DIAG HEADER)*/
    ((MSP_DIAG_HEAD_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU)))->ulDataSize = ulCmdParaLen;
    ((MSP_DIAG_HEAD_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU)))->ulID =
        (MSP_STRU_ID_GET_28_31_FIELD(MSP_STRU_ID_28_31_GROUP_PS) | MSP_STRU_ID_GET_16_23_FIELD(ucMsgType));

}
/*lint -restore*/

/*lint -save -e958*/
VOS_VOID diag_SocpIndCmdPkt(VOS_UINT8 * pstSocpPackt, VOS_UINT8 ucCmdType, VOS_UINT32 ulCmdParaLen, VOS_UINT16 ulCmdId)
{
    VOS_UINT64 ulTime = 0;

    /* ��SOCP��*/
    ulTime                           = diag_GetFrameTime();
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->usSId              = MSP_SOCP_SID_DIAG_SERVER;
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->usSSId             = MSP_SOCP_HIGH4BIT_SSID;    // ����λ
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->ucServiceSessionId = MSP_SOCP_SERVER_SESSION_ID;
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->ucMsgType          = MSP_SOCP_MSG_TYPE_IND;
    VOS_MemCpy(((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->aucTimeData, &ulTime, sizeof(VOS_UINT64));
    ((MSP_SOCP_HEAD_STRU*)pstSocpPackt)->ulMsgTransId = (g_DiagLogPktNum.ulIndNum)++;

    /* ����ṹ��ID(DIAG HEADER)*/
    ((MSP_DIAG_HEAD_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU)))->ulDataSize = ulCmdParaLen;
    ((MSP_DIAG_HEAD_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU)))->ulID =
        (MSP_STRU_ID_GET_28_31_FIELD(MSP_STRU_ID_28_31_GROUP_MSP) | MSP_STRU_ID_GET_16_23_FIELD(ucCmdType) \
        | MSP_STRU_ID_GET_0_15_FIELD(ulCmdId));

}
/*lint -restore*/

VOS_UINT32 diag_CheckMsgPara(DIAG_AIR_MSG_LOG_STRU* pstRptMessage)
{
    VOS_UINT32 ulRst = ERR_MSP_SUCCESS;

    /* �������Ϸ���*/
	if(NULL == pstRptMessage)
	{
		ulRst = ERR_MSP_INVALID_PARAMETER;
	}
	else if((pstRptMessage->ulDataSize == 0) && (NULL == pstRptMessage->pData))
	{
		ulRst = ERR_MSP_INVALID_PARAMETER;
        /*lint -save -e525*/
    }
    /*lint -restore*/
    return ulRst;
}


VOS_UINT32 diag_GetLayerMsgCfg(VOS_UINT32 ulCatId, VOS_UINT32 ulMsgId)
{
    DIAG_CFG_LOG_CAT_MSG_CFG_STRU *pstItemCfg =NULL;
    VOS_UINT32 i =  0;

    for(i = 0 ; i < g_stMsgCfg.ulCfgCnt; i++)
    {
       pstItemCfg = (g_stMsgCfg.astMsgCfgList + i);

       if(ulMsgId == pstItemCfg->ulId )
       {
           if(DIAG_CFG_SWT_CLOSE == pstItemCfg->ulSwt)
           {
              return ERR_MSP_CFG_LOG_NOT_ALLOW;
           }
           else if(DIAG_CFG_SWT_OPEN == pstItemCfg->ulSwt)
           {
              return ERR_MSP_SUCCESS;
           }
           else
           {
              return ERR_MSP_DIAG_MSG_CFG_NOT_SET;
           }
       }
    }

    return ERR_MSP_DIAG_MSG_CFG_NOT_SET;

}


VOS_UINT32 diag_GetLayerSrcCfg(VOS_UINT32 ulModuleId)
{
    /*lint -save -e40*/
    if(DOPRA_PID_TIMER == ulModuleId)
    {
        return ERR_MSP_SUCCESS;
    }
    /*lint -save -e539*/
	if(DIAG_CFG_LAYER_MODULE_IS_VALID((VOS_INT32)ulModuleId))
	{
   /*lint -restore*/
		if(DIAG_CFG_SWT_OPEN == g_LayerSrcModuleCfg[ulModuleId])
		{
			return	ERR_MSP_SUCCESS;
		}
	}
	/*lint -restore +e40*/
	return ERR_MSP_CFG_LOG_NOT_ALLOW;
}

VOS_UINT32 diag_GetLayerDstCfg(VOS_UINT32 ulModuleId)
{
        /*lint -save -e40*/
	if(DIAG_CFG_LAYER_MODULE_IS_VALID((VOS_INT32)ulModuleId))
	{
		if(DIAG_CFG_SWT_OPEN == g_LayerDecModuleCfg[ulModuleId])
		{
			return	ERR_MSP_SUCCESS;
		}
	}
	  /*lint -restore +e40*/
	return ERR_MSP_CFG_LOG_NOT_ALLOW;
}


VOS_UINT32 diag_GetLayerCfg(VOS_UINT32 ulSrcModuleId, VOS_UINT32 ulDstModuleId, VOS_UINT32 ulMsgId)
{
    VOS_UINT32 ret = ERR_MSP_CFG_LOG_NOT_ALLOW;
    VOS_UINT32 ulMsgCfg = ERR_MSP_DIAG_MSG_CFG_NOT_SET;

    /*���ж���ϢID���˹����Ƿ�򿪣�����У��������ϢID����*/
    ulMsgCfg = diag_GetLayerMsgCfg(DIAG_CMD_LOG_CATETORY_LAYER_ID, ulMsgId);
    if(ERR_MSP_DIAG_MSG_CFG_NOT_SET == ulMsgCfg )
    {
    	ret = diag_GetLayerSrcCfg(ulSrcModuleId);
		ret |= diag_GetLayerDstCfg(ulDstModuleId);
		return ret;
    }
    else if(ERR_MSP_SUCCESS == ulMsgCfg )
    {
        return ERR_MSP_SUCCESS;
    }
    else
    {
        return ERR_MSP_CFG_LOG_NOT_ALLOW;
    }
}


VOS_UINT32 diag_GetUserPlaneCfg(VOS_UINT32 ulMsgId)
{
    VOS_UINT32 i = 0;

    for(i=0;i<DIAG_CFG_USER_PLANE_ID_NUM;i++)
    {
        if(ulMsgId == g_stUserPlaneCfg[i].ulMsgId)
        {
            if(DIAG_CFG_SWT_OPEN == g_stUserPlaneCfg[i].ulSwitch)
            {
                return ERR_MSP_SUCCESS;
            }
            else if(DIAG_CFG_SWT_CLOSE == g_stUserPlaneCfg[i].ulSwitch)
            {
                return ERR_MSP_CFG_LOG_NOT_ALLOW;
            }
            else
            {
                return ERR_MSP_FAILURE;
            }
        }
    }

    return ERR_MSP_CFG_LOG_NOT_ALLOW;
}


VOS_UINT32 diag_GetPrintCfg(VOS_UINT32 ulModuleId, VOS_UINT32 ulLevel)
{
    VOS_UINT32 ulLevelFilter = 0;

    /*��Э��ջ��LEVELֵת����MSP��HSO֮���LEVELֵ*/
    /*0x80000000<->0;0x40000000<->1;0x20000000<->2;0x10<->3;0x08000000<->4*/
	if((PS_LOG_LEVEL_OFF == ulLevel)||(ulLevel >= PS_LOG_LEVEL_BUTT))
	{
		return ERR_MSP_CFG_LOG_NOT_ALLOW;
	}

    ulLevelFilter = ((VOS_UINT32)1<<(7-ulLevel));

    /* ��ӡ�ܿ���ģ������*/
    if(DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE != g_PrintTotalCfg)
    {
        if(ulLevelFilter & g_PrintTotalCfg)
        {
            return ERR_MSP_SUCCESS;
        }
        else
        {
            return ERR_MSP_CFG_LOG_NOT_ALLOW;
        }
    }
    else
    {
        /*lint -save -e40*/
        /*��ȡģ���ӡ����״̬*/
        if(DIAG_CFG_MODULE_IS_INVALID((VOS_INT32)ulModuleId))
        {
            return  ERR_MSP_CFG_LOG_NOT_ALLOW;
        }

        if(ulLevelFilter & g_PrintModuleCfg[ulModuleId - VOS_PID_DOPRAEND])
        {
            return ERR_MSP_SUCCESS;
        }
        else
        {
            return ERR_MSP_CFG_LOG_NOT_ALLOW;
        }
        /*lint -restore +e40*/
    }

}



VOS_UINT32 DIAG_PrintfV_TDS( VOS_CHAR* pszFmt, ...)
{
	return 0;
}

VOS_UINT32 DIAG_PrintfV_TDS1( VOS_UINT32 id ,VOS_CHAR* pszFmt, ...)
{
	return 0;
}


#define LTE_DIAG_PRINTF_LEN             (256+sizeof(VOS_UINT32)+sizeof(VOS_UINT32))

#define LTE_LOG_AFFIRM(c) \
do{ \
    if(!(c)) \
    { \
        vos_printf("LTE_LOG_ASSERT %d.\n", __LINE__); \
        return -1; \
    } \
}while(0)
#if 0

/******************************************************************************
��������: LTE_DIAG_LOG
��������: ��ӡ�����͵Ĵ�ӡ�ӿں���
����˵��:
            ulModuleId[in]  : ģ��id����ӦPID
            ulSubModId[in]  : ��ģ��id
            ulLevel[in]     : ��ӡ����
            ulLogId[in]     : ���ļ��ź��кŸ���DIAG_LOG_ID����
            amount[in]      : �ɱ����������������ulModuleId/ulLevel/ulLogId/amout��
            ...             : �ɱ����
����Լ��:
            1. ���Խ�ֹ�Դ˺������ж��η�װ��ֻ��ת����
            2. ֧�ֿɱ�Ĳ����������������ڵ���ʱ�ɲ���amountָ����������
            3. �ɱ����ֻ֧��int����
            4. Ŀǰ�汾��֧�ֵ�������������6���������Ĳ���Ĭ�϶���
******************************************************************************/
VOS_INT32 LTE_DIAG_LOG(VOS_UINT32 ulModuleId, VOS_UINT32 ulSubModId, 
                        VOS_UINT32 ulLevel, VOS_UINT32 ulLogId, 
                        VOS_UINT32 amount, ...)
{
    VOS_UINT32 ulRst          = ERR_MSP_SUCCESS;
    VOS_UINT32 ulParaBufSize  = 0;
    VOS_UINT8* pstSocpPackt   = NULL;
    DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU* pRptInfo = NULL;
    VOS_UINT32 ulDataLength =0;
    VOS_CHAR ucDiagPrintData[LTE_DIAG_PRINTF_LEN]={0};
    VOS_INT32 val, i, lTmpLen, lSpareLen, lOccupyLen;
    va_list vl;
    VOS_UINT32 paranum;
    
    /* ֻ��¼���ô���*/
    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT, ulLogId, 0, 0);

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_NO_INITILIZATION, ulLogId, 1);
        return ERR_MSP_NO_INITILIZATION;
    }
    
    ulRst = diag_GetPrintCfg(ulModuleId, ulLevel);
    if(ERR_MSP_SUCCESS != ulRst)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_UNAVAILABLE, ulLogId, 2);
        return ERR_MSP_UNAVAILABLE;
    }

    *((VOS_UINT32*)ucDiagPrintData) = ulModuleId;
    *(VOS_UINT32*)(ucDiagPrintData + sizeof(VOS_UINT32)) = ulLevel;

    lOccupyLen = 8;
    /*lint -save -e713 -e732*/
    lSpareLen  = LTE_DIAG_PRINTF_LEN - lOccupyLen;

    lTmpLen    = VOS_nsprintf(ucDiagPrintData + lOccupyLen, lSpareLen, "%d, ", ulLogId);
    LTE_LOG_AFFIRM(0 <= lTmpLen);

    lOccupyLen += lTmpLen;
    LTE_LOG_AFFIRM(LTE_DIAG_PRINTF_LEN >= (VOS_UINT32)lOccupyLen);
    lSpareLen  = LTE_DIAG_PRINTF_LEN - lOccupyLen;

    lTmpLen    = VOS_nsprintf(ucDiagPrintData + lOccupyLen, lSpareLen, "%u, ", VOS_GetTick());
    LTE_LOG_AFFIRM(0 <= lTmpLen);

    lOccupyLen += lTmpLen;
    LTE_LOG_AFFIRM(LTE_DIAG_PRINTF_LEN >= (VOS_UINT32)lOccupyLen);
    lSpareLen  = LTE_DIAG_PRINTF_LEN - lOccupyLen;

    va_start(vl, amount);/*lint !e530*/
    paranum = (amount > LTE_DIAG_PRINTF_PARAM_MAX_NUM) ? LTE_DIAG_PRINTF_PARAM_MAX_NUM : amount;
    
    for(i = 0; i < (VOS_INT32)paranum; i++)
    {
        val = va_arg(vl, int);
        /* coverity[overrun-local] */
        lTmpLen = VOS_nsprintf(ucDiagPrintData + lOccupyLen, lSpareLen, "%d, ", val);
        if(0 > lTmpLen)
        {
            DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_TOO_SMALL_BUFFER, lSpareLen, 3);
            va_end(vl);
            return -1;
        }
        
        lOccupyLen += lTmpLen;
        /* coverity[cond_at_most] */
        if(LTE_DIAG_PRINTF_LEN < (VOS_UINT32)lOccupyLen)
        {
            DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_TOO_SMALL_BUFFER, lOccupyLen, 4);
            va_end(vl);
            return -1;
        }
        lSpareLen  = LTE_DIAG_PRINTF_LEN - lOccupyLen;
    }
    va_end(vl);

    ulDataLength = lOccupyLen;
    
    /*�������ԴBUFFER*/
    diag_LockCoderSrcBuf();
    ulParaBufSize = sizeof(DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU) + ulDataLength;
    pstSocpPackt = diag_GetCoderSrcBuf(sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
        ulParaBufSize, SOCP_CODER_SRC_LOM_NORMAL_IND);
    if (NULL == pstSocpPackt)
    {
        diag_UnLockCoderSrcBuf();
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_NOT_ENOUGH_MEMORY, 0, 5);
        return ERR_MSP_NOT_ENOUGH_MEMORY;
    }
    
    /*��װSOCP��*/
    diag_SocpPsLogPkt(pstSocpPackt, MSP_STRU_ID_16_23_TYPE_DOT, ulParaBufSize);
    pRptInfo = (DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU));

    /*��װDIAG�������*/
    pRptInfo->ulModule = ulModuleId;
    pRptInfo->ulNo = (g_DiagLogPktNum.ulPrintTxtNum)++;                  
    pRptInfo->ulLevel  = ulLevel;
    VOS_MemCpy(pRptInfo->szText, ucDiagPrintData, ulDataLength);

    /*д�����ݵ�����ԴBUFFER*/
    ulRst = diag_SendCoderSrcToSocp(pstSocpPackt,sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
            ulParaBufSize, SOCP_CODER_SRC_LOM_NORMAL_IND);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_DOT_ERR, ERR_MSP_NOT_FOUND, ulRst, 6);
    }
    diag_UnLockCoderSrcBuf();

	return ulRst;
    /*lint -restore*/
}
#endif

VOS_UINT32 DIAG_PrintfV(VOS_UINT32 id, VOS_CHAR* pszFileName, VOS_UINT32 ulLineNum, VOS_CHAR* pszFmt, ...)
{
	VOS_UINT32 ulRst          = ERR_MSP_SUCCESS;
	VOS_UINT32 ulParaBufSize  = 0;                   // ����Buf Size
	VOS_UINT32 ulModuleId     = 0;
    VOS_UINT32 ulLevelFilter  = 0;
	VOS_UINT32 ulPrintLevel = 0;
    /*lint -save -e40 -e530*/
    va_list arg;
    VOS_INT32 ulParamLen =0;
    VOS_UINT8* pstSocpPackt = NULL;
    DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU* pRptInfo = NULL;
    VOS_UINT32 ulDataLength =0;
	VOS_CHAR ucDiagPrintData[DIAG_PRINTF_MAX_LEN+1]={0};

    /* ֻ��¼���ô���*/
    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_PRINTFV, id, 0, 0);

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_PRINTFV_ERR, ERR_MSP_NO_INITILIZATION, id, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

    /*��ȡ�����±�*/
    ulModuleId = DIAG_GET_MODULE_ID(id);

    /*��ȡģ�鿪��״̬*/
    ulLevelFilter = DIAG_GET_PRINTF_LEVEL(id);
#if 1
    ulRst = diag_GetPrintCfg(ulModuleId,ulLevelFilter);
    if(ERR_MSP_SUCCESS != ulRst)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_PRINTFV_ERR, ERR_MSP_UNAVAILABLE, id, 2);
        return ERR_MSP_UNAVAILABLE;
    }
#endif

    /*��HSO�Ĵ�ӡ�ַ�����ʽ����:pszFileName[ulLineNum]data��HSO����������[]ȥ��ȡ��Ӧ����Ϣ*/
    /*lint -save -e539*/
	ulParamLen = VOS_nsprintf(ucDiagPrintData,DIAG_PRINTF_MAX_LEN,"%s[%d]",pszFileName,ulLineNum);
    /*lint -restore*/
    /* coverity[cond_at_least] */
    if(ulParamLen > DIAG_PRINTF_MAX_LEN)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_PRINTFV_ERR, ERR_MSP_FAILURE, id, 11);
    }

	/*ulParamLen δ����\0*/
    va_start(arg, pszFmt);/*lint !e516*/
    /* coverity[overrun-local] */
    ulParamLen = VOS_nvsprintf(ucDiagPrintData + ulParamLen,\
				 DIAG_PRINTF_MAX_LEN - (VOS_UINT32)ulParamLen,(const VOS_CHAR *) pszFmt, arg);
    if(ulParamLen > DIAG_PRINTF_MAX_LEN)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_PRINTFV_ERR, ERR_MSP_FAILURE, id, 12);
    }
    va_end(arg);
    /*lint -restore +e40 +e530*/
	ucDiagPrintData[DIAG_PRINTF_MAX_LEN - 1] = '\0';
	ulDataLength = VOS_StrLen(ucDiagPrintData);

    /*�������ԴBUFFER*/
    diag_LockCoderSrcBuf();
    ulParaBufSize = sizeof(DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU) + ulDataLength;
    pstSocpPackt = diag_GetCoderSrcBuf(sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
        ulParaBufSize, SOCP_CODER_SRC_LOM_NORMAL_IND);
    if (NULL == pstSocpPackt)
    {
        diag_UnLockCoderSrcBuf();
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_PRINTFV_ERR, ERR_MSP_NOT_ENOUGH_MEMORY, 0, 3);
        return ERR_MSP_NOT_ENOUGH_MEMORY;
    }

    /*��װSOCP��*/
    diag_SocpPsLogPkt(pstSocpPackt, MSP_STRU_ID_16_23_TYPE_PRINT, ulParaBufSize);
    pRptInfo = (DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU));

    /*��װDIAG�������*/
    pRptInfo->ulModule = ulModuleId;
    pRptInfo->ulNo = (g_DiagLogPktNum.ulPrintTxtNum)++;
    pRptInfo->ulLevel  = ulPrintLevel;
    VOS_MemCpy(pRptInfo->szText, ucDiagPrintData, ulDataLength);

    /*д�����ݵ�����ԴBUFFER*/
    ulRst = diag_SendCoderSrcToSocp(pstSocpPackt,sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
            ulParaBufSize, SOCP_CODER_SRC_LOM_NORMAL_IND);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_PRINTFV_ERR, ulRst, 0, 4);
    }
    diag_UnLockCoderSrcBuf();

	return ulRst;
}


/*lint -save -e958*/
VOS_UINT32 DIAG_ReportCommand(VOS_UINT16 ulID, VOS_UINT32 ulDataSize, VOS_VOID* pData)
{
    VOS_UINT32 ulRst         = ERR_MSP_SUCCESS;
    VOS_UINT8* pstSocpPackt     = NULL;

    /* ֻ��¼���ô���*/
    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportStatLog, ulID, g_ulDiagCfgInfo, 0);

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportStatLog_ERR, ulDataSize, ulID, 2);
        return ERR_MSP_NO_INITILIZATION;
    }

    /*�������Ϸ���*/
    if((NULL == pData) ||(0 == ulDataSize) || (ulDataSize > DIAG_CMD_DATA_MAX_LEN))
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportStatLog_ERR, ulDataSize, ulID, 1);

        return ERR_MSP_INVALID_PARAMETER;
    }

    /*�������ԴBUFFER*/
    diag_LockCoderSrcBuf();
    pstSocpPackt = diag_GetCoderSrcBuf(sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
        ulDataSize, SOCP_CODER_SRC_LOM_PRECEDENCE_IND);

    if (NULL == pstSocpPackt)
    {
        diag_UnLockCoderSrcBuf();
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportStatLog_ERR, ERR_MSP_NOT_ENOUGH_MEMORY, ulID, 6);
        return ERR_MSP_NOT_ENOUGH_MEMORY;
    }

    /*��װSOCP��*/
    diag_SocpIndCmdPkt(pstSocpPackt, MSP_STRU_ID_16_23_IND_MSP, ulDataSize, ulID);

    VOS_MemCpy(((MSP_DIAG_HEAD_STRU*)(pstSocpPackt+sizeof(MSP_SOCP_HEAD_STRU)))->ucData,pData, ulDataSize);

    /*д�����ݵ�����ԴBUFFER*/
    ulRst = diag_SendCoderSrcToSocp(pstSocpPackt,sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +ulDataSize, \
            SOCP_CODER_SRC_LOM_PRECEDENCE_IND);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportStatLog_ERR, ulDataSize, 0, 7);
    }
    diag_UnLockCoderSrcBuf();
    return ulRst;
}
/*lint -restore*/

VOS_UINT32 DIAG_ReportEventLog(VOS_UINT32 id, VOS_UINT32 ulEventID)
{
	VOS_UINT32 ulRst                                = ERR_MSP_SUCCESS;
	VOS_UINT32 ulParaBufSize                        = 0;

    VOS_UINT8* pstSocpPackt           = NULL;
    DIAG_CMD_LOG_EVENT_IND_STRU *pEventIndInfo = NULL;

    /* ֻ��¼���ô���*/
    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportEventLog, id, ulEventID, 0);


    /*����Ƿ������¼��ϱ�*/
    if(!DIAG_IS_EVENT_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportEventLog_ERR, ulRst, id, 1);
        return ERR_MSP_NO_INITILIZATION;
    }

	/*�������ԴBUFFER*/
    diag_LockCoderSrcBuf();
    ulParaBufSize = sizeof(DIAG_CMD_LOG_EVENT_IND_STRU);
    pstSocpPackt = diag_GetCoderSrcBuf(sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
        ulParaBufSize, SOCP_CODER_SRC_LOM_PRECEDENCE_IND);

    if (NULL == pstSocpPackt)
    {
        diag_UnLockCoderSrcBuf();
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportEventLog_ERR, ERR_MSP_NOT_ENOUGH_MEMORY, id, 4);
        return ERR_MSP_NOT_ENOUGH_MEMORY;

    }
    /*��װSOCP��*/
    diag_SocpPsLogPkt(pstSocpPackt, MSP_STRU_ID_16_23_TYPE_EVENT, ulParaBufSize);

    /*��װDIAG�������*/
    pEventIndInfo = (DIAG_CMD_LOG_EVENT_IND_STRU *)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU));
    pEventIndInfo->ulNo = (g_DiagLogPktNum.ulEventNum)++;
    pEventIndInfo->ulId = ulEventID;

    /*д�����ݵ�����ԴBUFFER*/
    ulRst = diag_SendCoderSrcToSocp(pstSocpPackt,sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +ulParaBufSize,
            SOCP_CODER_SRC_LOM_PRECEDENCE_IND);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportEventLog_ERR, ulRst, 0, 7);
    }
    diag_UnLockCoderSrcBuf();

    return ulRst;
}


VOS_UINT32 DIAG_ReportAirMessageLog(DIAG_AIR_MSG_LOG_STRU* pRptMessage)
{
    VOS_UINT32 ulRst         = ERR_MSP_SUCCESS;
    VOS_UINT32 ulParaBufSize = 0;
    DIAG_CMD_LOG_AIR_IND_STRU* pRptInfo = NULL;
    VOS_UINT8* pstSocpPackt = NULL;

    /* ֻ��¼���ô���*/
    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportAirMessageLog, g_ulDiagCfgInfo, 0, 0);

    /*����Ƿ�����LT �տ��ϱ�*/
    if (!DIAG_IS_LT_AIR_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportAirMessageLog_ERR, ulRst, pRptMessage->ulId, 2);
        return ERR_MSP_NO_INITILIZATION;
    }


    /*�������Ϸ���*/
    ulRst = diag_CheckMsgPara(pRptMessage);

    if (ERR_MSP_SUCCESS != ulRst)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportAirMessageLog_ERR, ulRst, (NULL != pRptMessage ? pRptMessage->ulId : 0), 1);
        return ulRst;
    }

    /*�������ԴBUFFER*/
    diag_LockCoderSrcBuf();
    ulParaBufSize = sizeof(DIAG_CMD_LOG_AIR_IND_STRU) + pRptMessage->ulDataSize;
    pstSocpPackt = diag_GetCoderSrcBuf(sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
        ulParaBufSize, SOCP_CODER_SRC_LOM_PRECEDENCE_IND);

    if (NULL == pstSocpPackt)
    {
        diag_UnLockCoderSrcBuf();
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportAirMessageLog_ERR, ulParaBufSize, pRptMessage->ulId, 6);
        return ERR_MSP_NOT_ENOUGH_MEMORY;
    }

    /*��װSOCP��*/
    diag_SocpPsLogPkt(pstSocpPackt, MSP_STRU_ID_16_23_TYPE_AIR, ulParaBufSize);
    pRptInfo = (DIAG_CMD_LOG_AIR_IND_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU));

    /*��װDIAG�������*/
    pRptInfo->ulId     = pRptMessage->ulMessageID;
    pRptInfo->ulSide   = pRptMessage->ulSideId;
    pRptInfo->ulModule = DIAG_GET_MODULE_ID(pRptMessage->ulId);
    pRptInfo->ulNo = (g_DiagLogPktNum.ulAirNum)++;
    VOS_MemCpy(pRptInfo->aucDta, pRptMessage->pData, pRptMessage->ulDataSize);

    /*д�����ݵ�����ԴBUFFER*/
    ulRst = diag_SendCoderSrcToSocp(pstSocpPackt,sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
            ulParaBufSize, SOCP_CODER_SRC_LOM_PRECEDENCE_IND);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportAirMessageLog_ERR, ulRst, pRptMessage->ulId, 7);
    }
    diag_UnLockCoderSrcBuf();
	return ulRst;
}

/*****************************************************************************
 Function Name   : DIAG_ReportVoLTELog
 Description     : VoLTE��Ϣ�ϱ��ӿ�
 Input           : DIAG_VoLTE_LOG_STRU* pRptMessage
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.fuxin      2013-12-30  create
*****************************************************************************/
VOS_UINT32 DIAG_ReportVoLTELog(DIAG_VoLTE_LOG_STRU* pRptMessage)
{
    VOS_UINT32 ulRst         = ERR_MSP_SUCCESS;
    VOS_UINT32 ulParaBufSize = 0;
    VOS_UINT32 ulModuleId;
    DIAG_CMD_LOG_VoLTE_IND_STRU* pRptInfo = NULL;
    VOS_UINT8* pstSocpPackt = NULL;

    /* ֻ��¼���ô���*/
    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportVoLTELog_ERR, g_ulDiagCfgInfo, 0, 0);

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportVoLTELog_ERR, ulRst, pRptMessage->ulId, 2);
        return ERR_MSP_NO_INITILIZATION;
    }

    /*�������Ϸ���*/
    ulRst = diag_CheckMsgPara((DIAG_AIR_MSG_LOG_STRU *)pRptMessage);

    if (ERR_MSP_SUCCESS != ulRst)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportVoLTELog_ERR, ulRst, (NULL != pRptMessage ? pRptMessage->ulId : 0), 1);
        return ulRst;
    }

    ulModuleId  = DIAG_GET_MODULE_ID(pRptMessage->ulId);
    ulRst = diag_GetLayerCfg(ulModuleId, ulModuleId, pRptMessage->ulMessageID);

    if(ERR_MSP_SUCCESS != ulRst)
    {
        ulRst = ERR_MSP_CFG_LOG_NOT_ALLOW;
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportVoLTELog_ERR, ulRst, pRptMessage->ulId, 4);
	  return ulRst;
    }

    /*�������ԴBUFFER*/
    diag_LockCoderSrcBuf();
    ulParaBufSize = sizeof(DIAG_CMD_LOG_VoLTE_IND_STRU) + pRptMessage->ulDataSize;
    pstSocpPackt = diag_GetCoderSrcBuf(sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
        ulParaBufSize, SOCP_CODER_SRC_LOM_PRECEDENCE_IND);

    if (NULL == pstSocpPackt)
    {
        diag_UnLockCoderSrcBuf();
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportVoLTELog_ERR, ulParaBufSize, pRptMessage->ulId, 6);
        return ERR_MSP_NOT_ENOUGH_MEMORY;
    }

    /*��װSOCP��*/
    diag_SocpPsLogPkt(pstSocpPackt, MSP_STRU_ID_16_23_VoLTE, ulParaBufSize);
    pRptInfo = (DIAG_CMD_LOG_VoLTE_IND_STRU *)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU));

    /*��װDIAG�������*/
    pRptInfo->ulId     = pRptMessage->ulMessageID;
    pRptInfo->ulSide   = pRptMessage->ulSideId;
    pRptInfo->ulModule = DIAG_GET_MODULE_ID(pRptMessage->ulId);
    pRptInfo->ulNo = (g_DiagLogPktNum.ulVoLTENum)++;
    VOS_MemCpy(pRptInfo->aucDta, pRptMessage->pData, pRptMessage->ulDataSize);

    /*д�����ݵ�����ԴBUFFER*/
    ulRst = diag_SendCoderSrcToSocp(pstSocpPackt,sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
            ulParaBufSize, SOCP_CODER_SRC_LOM_PRECEDENCE_IND);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportVoLTELog_ERR, ulRst, pRptMessage->ulId, 7);
    }
    diag_UnLockCoderSrcBuf();

	return ulRst;
}


/*lint -save -e958*/
VOS_UINT32 DIAG_ReportGUAirMessageLog(VOS_VOID* pRptMessage,VOS_UINT16 ulMsgLen)
{
	VOS_UINT32 ulRst         = ERR_MSP_SUCCESS;
	VOS_UINT32 ulParaBufSize = 0;
	VOS_UINT32 ulDataOffset = 0;
    VOS_UINT32 ulSrcMod = 0;
	DIAG_CMD_LOG_AIR_IND_STRU* pRptInfo = NULL;
	VOS_UINT8* pstSocpPackt = NULL;
	DIAG_GU_AIR_MSG_LOG_STRU *pstGUMsgStru = NULL;
/*lint -restore*/

	/* ֻ��¼���ô���*/
	DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportAirMessageLog, g_ulDiagCfgInfo, 0, 0);

	/*����Ƿ�����GU �տ��ϱ�*/
	if (!DIAG_IS_GU_AIR_ON)
	{
	    ulRst = ERR_MSP_NO_INITILIZATION;
	    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportAirMessageLog_ERR, ulRst, 0, 2);
	    return ERR_MSP_NO_INITILIZATION;
	}

        /*�������Ϸ���*/
	if(pRptMessage == NULL)
	{
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportAirMessageLog_ERR, 1, 0, 1);
        return ERR_MSP_INVALID_PARAMETER;
	}

    /*��ȡGU�տ���Ϣ�ṹ�����ĳ��ȣ�����������Ϣ�쳣*/
    pstGUMsgStru = (DIAG_GU_AIR_MSG_LOG_STRU *)pRptMessage;
    /*lint -save -e40*/
    if(pstGUMsgStru->usPrimId == ID_WAS_OM_OTA_IND)
    {
        ulSrcMod = WUEPS_PID_WRR;
        ulDataOffset = WAS_OM_OTA_IND_OFFSET;

    }
    else if(pstGUMsgStru->usPrimId == ID_GAS_OM_OTA_IND)
    {
        ulSrcMod = UEPS_PID_GAS;
        ulDataOffset = GAS_OM_OTA_IND_OFFSET;

    }
    else if(pstGUMsgStru->usPrimId == NAS_OM_OTA_IND)
    {
        ulSrcMod = GU_PID_NAS;
        ulDataOffset = NAS_OM_OTA_OFFSET;

    }
    else
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportAirMessageLog_ERR, ulRst, pstGUMsgStru->usPrimId, 4);
        return ERR_MSP_INVALID_PARAMETER;
    }
    /*lint -restore +e40*/
    /*�������ԴBUFFER*/
    diag_LockCoderSrcBuf();
	ulParaBufSize = sizeof(DIAG_CMD_LOG_AIR_IND_STRU) + ulMsgLen -ulDataOffset;
	pstSocpPackt = diag_GetCoderSrcBuf(sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
	    ulParaBufSize, SOCP_CODER_SRC_LOM_PRECEDENCE_IND);
    if (NULL == pstSocpPackt)
    {
        diag_UnLockCoderSrcBuf();
	    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportAirMessageLog_ERR, ulParaBufSize, pstGUMsgStru->usPrimId, 6);
	    return ERR_MSP_NOT_ENOUGH_MEMORY;
	}

    /*��װSOCP��*/
    diag_SocpPsLogPkt(pstSocpPackt, MSP_STRU_ID_16_23_TYPE_AIR, ulParaBufSize);
    pRptInfo = (DIAG_CMD_LOG_AIR_IND_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU));

    /*��װDIAG�������*/
    pRptInfo->ulId     = pstGUMsgStru->usOtaMsgID;
    pRptInfo->ulSide   = pstGUMsgStru->ucUpDown;   //
    pRptInfo->ulModule = ulSrcMod;
    pRptInfo->ulNo = (g_DiagLogPktNum.ulAirNum)++;
    VOS_MemCpy(pRptInfo->aucDta, (VOS_UINT8 *)pstGUMsgStru+ulDataOffset , (ulParaBufSize -sizeof(DIAG_CMD_LOG_AIR_IND_STRU)));

    /*д�����ݵ�����ԴBUFFER*/
    ulRst = diag_SendCoderSrcToSocp(pstSocpPackt,sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
            ulParaBufSize, SOCP_CODER_SRC_LOM_PRECEDENCE_IND);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportAirMessageLog_ERR, ulRst, 0, 7);
    }
    diag_UnLockCoderSrcBuf();
	return ulRst;
}


VOS_UINT32 DIAG_ReportLayerMessageLog(DIAG_LAYER_MSG_STRU* pRptMessage)
{
    VOS_UINT32 ulRst         = ERR_MSP_SUCCESS;
    VOS_UINT32 ulParaBufSize = 0;                   // ����Buf Size
    VOS_UINT32 ulModuleId;
    VOS_UINT8* pstSocpPackt           = NULL;
    DIAG_CMD_LOG_LAYER_IND_STRU *pLayerIndInfo = NULL;

    /* ֻ��¼���ô���*/
    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportLayerMessageLog, 0, 0, 0);

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportLayerMessageLog_ERR, ulRst, pRptMessage->ulId, 2);
        return ERR_MSP_NO_INITILIZATION;
    }

    /*�������Ϸ���*/
    ulRst = diag_CheckMsgPara((DIAG_AIR_MSG_LOG_STRU*)pRptMessage);
    if(ERR_MSP_SUCCESS != ulRst)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportLayerMessageLog_ERR,ulRst,(NULL != pRptMessage ? pRptMessage->ulId : 0),1);
        return ulRst;
    }

    ulModuleId  = DIAG_GET_MODULE_ID(pRptMessage->ulId);
    /*����Ƿ���������Ϣ�ϱ�*/
    ulRst = diag_GetLayerCfg(ulModuleId, pRptMessage->ulDestMod, pRptMessage->ulMessageID);

    if(ERR_MSP_SUCCESS != ulRst)
    {
        ulRst = ERR_MSP_CFG_LOG_NOT_ALLOW;
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportLayerMessageLog_ERR, ulRst, pRptMessage->ulId, 4);
	  return ulRst;
    }

    /*�������ԴBUFFER*/
    diag_LockCoderSrcBuf();
    ulParaBufSize  = sizeof(DIAG_CMD_LOG_LAYER_IND_STRU) + pRptMessage->ulDataSize;
    pstSocpPackt = diag_GetCoderSrcBuf(sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
        ulParaBufSize, SOCP_CODER_SRC_LOM_PRECEDENCE_IND);

    if (NULL == pstSocpPackt)
    {
        diag_UnLockCoderSrcBuf();
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportLayerMessageLog_ERR, ERR_MSP_NOT_ENOUGH_MEMORY, pRptMessage->ulId, 5);
	    return ERR_MSP_NOT_ENOUGH_MEMORY;
    }

    /*��װSOCP��*/
    diag_SocpPsLogPkt(pstSocpPackt, MSP_STRU_ID_16_23_TYPE_LAYER, ulParaBufSize);
    pLayerIndInfo = (DIAG_CMD_LOG_LAYER_IND_STRU *)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU));

    /*��װDIAG�������*/
    pLayerIndInfo->ulModule  = ulModuleId;
    pLayerIndInfo->ulDestMod = pRptMessage->ulDestMod;
    pLayerIndInfo->ulNo = (g_DiagLogPktNum.ulLayerNum++);
    pLayerIndInfo->ulId      = pRptMessage->ulMessageID;
    VOS_MemCpy(pLayerIndInfo->aucDta, pRptMessage->pData, pRptMessage->ulDataSize);

    /*д�����ݵ�����ԴBUFFER*/
    ulRst = diag_SendCoderSrcToSocp(pstSocpPackt,sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
            ulParaBufSize, SOCP_CODER_SRC_LOM_PRECEDENCE_IND);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportLayerMessageLog_ERR, ulRst, 0, 7);
    }
    diag_UnLockCoderSrcBuf();
    return ulRst;
}


VOS_UINT32 DIAG_ReportUserPlaneMessageLog(DIAG_USERPLANE_MSG_STRU* pRptMessage)
{
    VOS_UINT32 ulRst         = ERR_MSP_SUCCESS;
    VOS_UINT32 ulParaBufSize = 0;                   // ����Buf Size
    VOS_UINT32 ulMessageId;
    VOS_UINT8* pstSocpPackt = NULL;
    DIAG_CMD_LOG_USERPLANE_IND_STRU* pRptInfo = NULL;


    /* ֻ��¼���ô���*/
    DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportUserPlaneMessageLog, 0, 0, 0);

    /*���DIAG�Ƿ��ʼ����HSO�Ƿ�������*/
    if(!DIAG_IS_CONN_ON)
    {
        ulRst = ERR_MSP_NO_INITILIZATION;
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportUserPlaneMessageLog_ERR, ulRst, pRptMessage->ulMessageID, 2);
        return ulRst;
    }

    /*�������Ϸ���*/
    if((NULL == pRptMessage)||((0 == pRptMessage->ulDataSize) && (NULL == pRptMessage->pData)))
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportUserPlaneMessageLog_ERR,ERR_MSP_INVALID_PARAMETER,
            (NULL != pRptMessage ? pRptMessage->ulMessageID : 0),1);

        return ERR_MSP_INVALID_PARAMETER;
    }

    ulMessageId = pRptMessage->ulMessageID;

    ulRst = diag_GetUserPlaneCfg(ulMessageId);
    if(ERR_MSP_SUCCESS != ulRst)
    {
        /* �������ò������ϱ�*/
        ulRst = ERR_MSP_CFG_LOG_NOT_ALLOW;
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportUserPlaneMessageLog_ERR, ulRst, pRptMessage->ulMessageID, 4);

        return ulRst;
    }

    /*�������ԴBUFFER*/
    diag_LockCoderSrcBuf();
    ulParaBufSize = sizeof(DIAG_CMD_LOG_USERPLANE_IND_STRU) + pRptMessage->ulDataSize;
    pstSocpPackt = diag_GetCoderSrcBuf(sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
        ulParaBufSize, SOCP_CODER_SRC_LOM_NORMAL_IND);
    if (NULL == pstSocpPackt)
    {
        diag_UnLockCoderSrcBuf();
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportUserPlaneMessageLog_ERR, ERR_MSP_NOT_ENOUGH_MEMORY, 0, 7);
        return ERR_MSP_NOT_ENOUGH_MEMORY;
    }

    /*��װSOCP��*/
    diag_SocpPsLogPkt(pstSocpPackt, MSP_STRU_ID_16_23_TYPE_USER, ulParaBufSize);
    pRptInfo = (DIAG_CMD_LOG_USERPLANE_IND_STRU*)(pstSocpPackt + sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU));

    /*��װDIAG�������*/
    pRptInfo->ulId = pRptMessage->ulMessageID;
    pRptInfo->ulNo = (g_DiagLogPktNum.ulUserNum)++;
    VOS_MemCpy(pRptInfo->aucDta, pRptMessage->pData, pRptMessage->ulDataSize);

    /*д�����ݵ�����ԴBUFFER*/
    ulRst = diag_SendCoderSrcToSocp(pstSocpPackt,sizeof(MSP_SOCP_HEAD_STRU) + sizeof(MSP_DIAG_HEAD_STRU) +
        ulParaBufSize, SOCP_CODER_SRC_LOM_NORMAL_IND);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        DIAG_DEBUG_SDM_FUN(EN_SDM_DIAG_ReportUserPlaneMessageLog_ERR, ulRst, 0, 7);
    }
    diag_UnLockCoderSrcBuf();
    return ulRst;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


