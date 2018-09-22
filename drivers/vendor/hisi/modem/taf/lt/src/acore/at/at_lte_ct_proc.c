/******************************************************************************
 */
/*
 */
/*                  ��Ȩ���� (C), 1998-2010, ��Ϊ�������޹�˾
 */
/*
 */
/******************************************************************************
 */
/*  �� �� ��   : at_cmd_ct.c
 */
/*  �� �� ��   : V1.0
 */

/*  ��������   : 2010-05-14
 */
/*  ��������   : CT
 */
/*
 */
/*  �����б�   : TODO: ...
 */
/*  �޸���ʷ   :
 */
/*  1.��    �� : 2010-05-14
 */

/*    �޸����� : �����ļ�
 */
/*
 */
/******************************************************************************
 */

/******************************************************************************
 */
/* PROJECT   :
 */
/* SUBSYSTEM :
 */
/* MODULE    :
 */
/* OWNER     :
 */

/******************************************************************************
 */
/*#include <stdlib.h>
 */
#include "osm.h"
#include "gen_msg.h"

#include "at_lte_common.h"
/*lint --e{7,64,537,322,958,734,813,718,746,830,438,409}*/
#include "ATCmdProc.h"
#include "AtCmdMsgProc.h"
#include "TafDrvAgent.h"
#include "LPsNvInterface.h"

#if (FEATURE_ON == MBB_COMMON)
#include "wlan_at_api.h"
#endif

#include "LNvCommon.h"

/*lint -e767 ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        MSP_FILE_ID_AT_LTE_CT_PROC_C
/*lint +e767 */

/******************************************************************************
 */
/* ��������: ����VCTCXO��ѹ
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetVCTCXOPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FVCTCXO_REQ_STRU stVCTCXOSetReq = {0};
    VOS_UINT32 ulRst;

    /* �������
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stVCTCXOSetReq.ulVol = gastAtParaList[0].ulParaValue;

    /* TO DO, ��VCTCXO��ѹ��Χȷ������Ե�ѹ�Ƿ���������ж�
 */
    /* �����õ�ѹֵ���ߣ��򷵻���ʾ�û�
 */
    /* �������ϸ߳���ȷ��
 */
#if 0
    if(((0x8200 - 200) > stVCTCXOSetReq.ulVol) || ((0x8200 + 200) < stVCTCXOSetReq.ulVol))
    {
        return ERR_MSP_VCTCXO_OVER_HIGH;
    }
#endif

    
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FVCTCXO_REQ,ucClientId, (VOS_VOID*)(&stVCTCXOSetReq), sizeof(stVCTCXOSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* ���õ�ǰ��������
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FVCTCXO_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetVCTCXOParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_FVCTCXO_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_FVCTCXO_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}


/******************************************************************************
 */
/* ��������: ��ѯVCTCXO��ѹ
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryVCTCXOPara(VOS_UINT8 ucClientId)
{
    FTM_RD_FVCTCXO_REQ_STRU stVCTCXOQryReq = {0};
    VOS_UINT32 ulRst;

    
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FVCTCXO_REQ,ucClientId, (VOS_VOID*)(&stVCTCXOQryReq), sizeof(stVCTCXOQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FVCTCXO_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryVCTCXOParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    FTM_RD_FVCTCXO_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_FVCTCXO_CNF_STRU *)pEvent->ulParam1;


	if(NULL == pstCnf)
	{
	    return ERR_MSP_FAILURE;
	}

	usLength = 0;
	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
		(VOS_CHAR *)pgucLAtSndCodeAddr,
		(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FVCTCXO:%d",
		pstCnf->ulVol);


	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;



}


/******************************************************************************
 */
/* ��������: �������ŵ�
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFTXONPara(VOS_UINT8 ucClientId)
{
    FTM_SET_TXON_REQ_STRU stFTXONSetReq = {(FTM_TXON_SWT_ENUM)0, };
    VOS_UINT32 ulRst;

    // �������
    
    
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stFTXONSetReq.enSwtich = (FTM_TXON_SWT_ENUM)(gastAtParaList[0].ulParaValue);

    
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_TXON_REQ, ucClientId, (VOS_VOID*)(&stFTXONSetReq), sizeof(stFTXONSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* ���õ�ǰ��������
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FTXON_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFTXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

	OS_MSG_STRU* pEvent = NULL;
	FTM_SET_TXON_CNF_STRU *pstCnf = NULL;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_TXON_CNF_STRU *)pEvent->ulParam1;

	CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

	return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* ��������: ��ѯ�����ŵ���״̬
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFTXONPara(VOS_UINT8 ucClientId)
{
    FTM_RD_TXON_REQ_STRU stFTXONQryReq = {0};
    VOS_UINT32 ulRst;


	
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_TXON_REQ,ucClientId, (VOS_VOID*)(&stFTXONQryReq), sizeof(stFTXONQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FTXON_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFTXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

	FTM_RD_TXON_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_TXON_CNF_STRU *)pEvent->ulParam1;


	if(NULL == pstCnf)
	{
		return ERR_MSP_FAILURE;
	}

	usLength = 0;
	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
		(VOS_CHAR *)pgucLAtSndCodeAddr,
		(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FTXON:%d",
		pstCnf->enSwtich);


	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
	return AT_FW_CLIENT_STATUS_READY;



}

VOS_UINT32 atQryFPllStatusPara(VOS_UINT8 ucClientId)
{
    FTM_RD_FPLLSTATUS_REQ_STRU stFPLLSTATUSQryReq = {0};
    VOS_UINT32 ulRst;

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FPLLSTATUS_REQ,ucClientId, (VOS_VOID*)(&stFPLLSTATUSQryReq), sizeof(stFPLLSTATUSQryReq));
    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FPLLSTATUS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFPllStatusParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

    FTM_RD_FPLLSTATUS_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    VOS_UINT16 usLength = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_FPLLSTATUS_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
    {
        return ERR_MSP_FAILURE;
    }

    usLength = 0;
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
        (VOS_CHAR *)pgucLAtSndCodeAddr,
        (VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
        "^FPLLSTATUS: %d,%d",
        pstCnf->tx_status,pstCnf->rx_status);

    CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
    return AT_FW_CLIENT_STATUS_READY;
}


/******************************************************************************
 */
/* ��������: �������ŵ�
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFRXONPara(VOS_UINT8 ucClientId)
{
    FTM_SET_RXON_REQ_STRU stFRXONSetReq = {0};
    VOS_UINT32 ulRst;

    /* �������
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    stFRXONSetReq.ulRxSwt = gastAtParaList[0].ulParaValue;

    
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_RXON_REQ,ucClientId, (VOS_VOID*)(&stFRXONSetReq), sizeof(stFRXONSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* ���õ�ǰ��������
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FRXON_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFRXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

	OS_MSG_STRU* pEvent = NULL;
	FTM_SET_RXON_CNF_STRU *pstCnf = NULL;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_RXON_CNF_STRU *)pEvent->ulParam1;

	CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

	return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* ��������: ��ѯ�����ŵ�����״̬
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFRXONPara(VOS_UINT8 ucClientId)
{
    FTM_RD_RXON_REQ_STRU stFRXONQryReq = {0};
    VOS_UINT32 ulRst;

    
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_RXON_REQ,ucClientId, (VOS_VOID*)(&stFRXONQryReq), sizeof(stFRXONQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FRXON_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFRXONParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

	FTM_RD_RXON_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_RXON_CNF_STRU *)pEvent->ulParam1;


	if(NULL == pstCnf)
	{
		return ERR_MSP_FAILURE;
	}

	usLength = 0;
	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
		(VOS_CHAR *)pgucLAtSndCodeAddr,
		(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FRXON:%d",
		pstCnf->ulRxSwt);


	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
	return AT_FW_CLIENT_STATUS_READY;



}

/******************************************************************************
 */
/* ��������: ���÷�������ŵ�
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFCHANPara(VOS_UINT8 ucClientId)
{
    FTM_SET_FCHAN_REQ_STRU stFCHANSetReq = {(FCHAN_MODE_ENUM)0, };
    VOS_UINT32 ulRst;
    /* �������
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(3 != gucAtParaIndex)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(0 == gastAtParaList[1].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(0 == gastAtParaList[2].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    stFCHANSetReq.enFchanMode = (FCHAN_MODE_ENUM)(gastAtParaList[0].ulParaValue);
    stFCHANSetReq.ucBand = (VOS_UINT8)(gastAtParaList[1].ulParaValue);
	stFCHANSetReq.usChannel = (VOS_UINT16)(gastAtParaList[2].ulParaValue);

	(VOS_VOID)AT_SetGlobalFchan((VOS_UINT8)(gastAtParaList[0].ulParaValue));


    
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FCHAN_REQ,ucClientId, (VOS_VOID*)(&stFCHANSetReq), sizeof(stFCHANSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* ���õ�ǰ��������
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCHAN_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFCHANParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_FCHAN_CNF_STRU *pstCnf = NULL;
    

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_FCHAN_CNF_STRU *)pEvent->ulParam1;

    
    if(ERR_MSP_SUCCESS == pstCnf->ulErrCode)
    {
       (VOS_VOID)AT_SetGlobalFchan((VOS_UINT8)(pstCnf->enFchanMode));
    }
    

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* ��������:
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFWAVEPara(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst;
    FTM_SET_FWAVE_REQ_STRU stFWaveSetReq = { 0 };

    /* �������
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(2 != gucAtParaIndex)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(0 == gastAtParaList[1].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    stFWaveSetReq.usType  = gastAtParaList[0].ulParaValue;
    stFWaveSetReq.usPower = gastAtParaList[1].ulParaValue;

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_FWAVE_REQ,ucClientId,
        (VOS_VOID*)(&stFWaveSetReq), sizeof(stFWaveSetReq));


	if(AT_SUCCESS == ulRst)
    {
        /* ���õ�ǰ��������
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FWAVE_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFWAVEParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    FTM_SET_FWAVE_CNF_STRU *pstCnf = NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_FWAVE_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
    return AT_FW_CLIENT_STATUS_READY;
}


/*******************************************************************************/

/* ��������: ��ѯ��������ŵ� */

/* ����˵��:*/

/*   ulIndex [in] ... */

/* �� �� ֵ: */

/*    TODO: ... */
/*******************************************************************************/
VOS_UINT32 atQryFCHANPara(VOS_UINT8 ucClientId)
{
    FTM_RD_FCHAN_REQ_STRU stFCHANQryReq = {0};
    VOS_UINT32 ulRst;

    
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_FCHAN_REQ,ucClientId, (VOS_VOID*)(&stFCHANQryReq), sizeof(stFCHANQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FCHAN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

#define AT_CT_FREQ_INVALID_VALUE                (65536)  /* 36.101 0-65535
 */

VOS_UINT32 atQryFCHANParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
 	FTM_RD_FCHAN_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_FCHAN_CNF_STRU *)pEvent->ulParam1;


	if(NULL == pstCnf)
	{
		return ERR_MSP_FAILURE;
	}

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
    	(VOS_CHAR *)pgucLAtSndCodeAddr,
    	(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
    	"^FCHAN:%d,%d,%d,%d",
    	pstCnf->enFchanMode,
    	pstCnf->ucBand,
    	pstCnf->usUlChannel,
    	pstCnf->usDlChannel);

	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
	return AT_FW_CLIENT_STATUS_READY;
}

/******************************************************************************
 */
/* ��������: AT^TSELRF  ѡ����Ƶͨ·ָ��
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
#if 1
extern VOS_UINT32 g_ulWifiRF;

VOS_UINT32 atSetTselrfPara(VOS_UINT8 ucClientId)
{
    FTM_SET_TSELRF_REQ_STRU stTselrfSetReq = { 0 };
    VOS_UINT32 ulRst = AT_SUCCESS;
#if (FEATURE_ON == MBB_COMMON)
#else
    VOS_UINT32 Rst;
#endif
    VOS_UINT8 ulPath = 0 ;

    
#if (FEATURE_ON == MBB_COMMON)
#else
    VOS_CHAR acCmd[200]={0};
#endif
    

    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if((1 != gucAtParaIndex) &&
       (2 != gucAtParaIndex))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }
    
    if(0 == gastAtParaList[0].usParaLen)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }
    
#if (FEATURE_ON == MBB_COMMON)
    if(2 == gucAtParaIndex)
    {
        if(0 == gastAtParaList[1].usParaLen)
        {
            return ERR_MSP_INVALID_PARAMETER;
        }
    }
#endif
    
    ulPath = (VOS_UINT8)(gastAtParaList[0].ulParaValue);

    if((FTM_TSELRF_FDD_LTE_MAIN     == ulPath)
        || (FTM_TSELRF_TDD_LTE_MAIN == ulPath)
        || (FTM_TSELRF_FDD_LTE_SUB  == ulPath)
        || (FTM_TSELRF_TDD_LTE_SUB  == ulPath)
        || (FTM_TSELRF_TD           == ulPath))
    
    {
#if (FEATURE_ON == MBB_COMMON)
        if(2 == gucAtParaIndex)
        {
            stTselrfSetReq.ucPath  = ulPath;
            stTselrfSetReq.ucGroup = (VOS_UINT8)gastAtParaList[1].ulParaValue;
        }
        else
        {
            stTselrfSetReq.ucPath  = ulPath;
            stTselrfSetReq.ucGroup = 0;
        }
#else
        stTselrfSetReq.ucPath  = ulPath;
        stTselrfSetReq.ucGroup = (VOS_UINT8)gastAtParaList[1].ulParaValue;
    
#endif
    }
    /* WIFI��Ƶͨ·���� */
#if (FEATURE_ON == MBB_COMMON)
#if (FEATURE_ON == MBB_WIFI)
    else if (FTM_TSELRF_WIFI == ulPath)
    {
        if ( BSP_MODULE_SUPPORT == DRV_GET_WIFI_SUPPORT())
        {
            if(2 == gucAtParaIndex)
            {
                /* WIFIͨ·���� */
                if(AT_RETURN_SUCCESS != WlanATSetTSELRF(gastAtParaList[1].ulParaValue))
                {
                    return AT_ERROR;
                }
            }
            else
            {
                /* WIFIͨ·���� */
                if(AT_RETURN_SUCCESS != WlanATSetTSELRF(0))
                {
                    return AT_ERROR;
                }
            }
            
            return AT_OK;
        }
        else
        {
            return AT_ERROR;
        }
    }
#endif
#else
    else if(FTM_TSELRF_WIFI == ulPath)
    {
#ifdef VERSION_V7R1_C010
        ulRst=BSP_HwIsSupportWifi();
#endif
        if(ulRst == ERR_MSP_SUCCESS)
        {
            /*WIFIδEnableֱ�ӷ���ʧ��*/
            if(VOS_FALSE == (VOS_UINT32)WIFI_GET_STATUS())
            {
                return AT_ERROR;
            }

            if((0 != gastAtParaList[1].ulParaValue) && (1 != gastAtParaList[1].ulParaValue))
            {
                return AT_ERROR;
            }

            g_ulWifiRF = gastAtParaList[1].ulParaValue;


            Rst = (VOS_UINT32)VOS_sprintf(acCmd, "wl txchain %d", (gastAtParaList[1].ulParaValue + 1));
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);

            Rst = (VOS_UINT32)VOS_sprintf(acCmd, "wl rxchain %d", (gastAtParaList[1].ulParaValue + 1));
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);


            Rst = (VOS_UINT32)VOS_sprintf(acCmd, "wl txant %d", gastAtParaList[1].ulParaValue);
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);

            Rst = (VOS_UINT32)VOS_sprintf(acCmd, "wl antdiv %d", gastAtParaList[1].ulParaValue);
            if(Rst != ERR_MSP_SUCCESS)
            {

            }

            WIFI_TEST_CMD(acCmd);

            return AT_OK;
        }
    }
#endif
    else
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_TSELRF_REQ, ucClientId,(VOS_VOID*)(&stTselrfSetReq), sizeof(stTselrfSetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* ���õ�ǰ��������
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_TSELRF_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬
 */
    }

    return ulRst;
}
VOS_UINT32 atSetTselrfParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
	OS_MSG_STRU* pEvent = NULL;
    FTM_SET_TSELRF_CNF_STRU* pstCnf = NULL;

	HAL_SDMLOG("\n enter atSetTselrfParaCnfProc !!!\n");

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_TSELRF_CNF_STRU *)pEvent->ulParam1;

	CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

	return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* ��������: AT^TSELRF  ѡ����Ƶͨ·ָ��
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */

VOS_UINT32 atQryTselrfPara(VOS_UINT8 ucClientId)
{
/*
ƽ̨���ṩ�ýӿڣ��ɲ�Ʒ��ʵ�֡�����ʹ����������NV���ȡ:
10000 NV_WG_RF_MAIN_BAND
0xD22C NV_ID_UE_CAPABILITY
0xD304 EN_NV_ID_TDS_SUPPORT_FREQ_BAND
*/
    return AT_OK;
}
#endif
/******************************************************************************
 */
/* ��������: ���ý��ջ�LNA�ĵȼ�
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atSetFLNAPara(VOS_UINT8 ucClientId)
{
    FTM_SET_AAGC_REQ_STRU stFLNASetReq = {0};
    VOS_UINT32 ulRst;

    /* �������
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(0 == gastAtParaList[0].usParaLen)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stFLNASetReq.ucAggcLvl = (VOS_UINT8)(gastAtParaList[0].ulParaValue);

    
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_AAGC_REQ,ucClientId, (VOS_VOID*)(&stFLNASetReq), sizeof(stFLNASetReq));

    if(AT_SUCCESS == ulRst)
    {
        /* ���õ�ǰ��������
 */
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FLNA_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬
 */
    }

    return AT_ERROR;
}

VOS_UINT32 atSetFLNAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

	OS_MSG_STRU* pEvent = NULL;
	FTM_SET_AAGC_CNF_STRU *pstCnf = NULL;


	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_AAGC_CNF_STRU *)pEvent->ulParam1;

	CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

	return AT_FW_CLIENT_STATUS_READY;

}

/******************************************************************************
 */
/* ��������: ��ѯ���ջ�LNA�ĵȼ�
 */
/*
 */
/* ����˵��:
 */
/*   ulIndex [in] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/******************************************************************************
 */
VOS_UINT32 atQryFLNAPara(VOS_UINT8 ucClientId)
{
    FTM_RD_AAGC_REQ_STRU stFLNAQryReq = {0};
    VOS_UINT32 ulRst;

    
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_AAGC_REQ,ucClientId, (VOS_VOID*)(&stFLNAQryReq), sizeof(stFLNAQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FLNA_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 atQryFLNAParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

	FTM_RD_AAGC_CNF_STRU *pstCnf = NULL;
	OS_MSG_STRU*pEvent = NULL;
	VOS_UINT16 usLength = 0;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_AAGC_CNF_STRU *)pEvent->ulParam1;


	if(NULL == pstCnf)
	{
		return ERR_MSP_FAILURE;
	}

	usLength = 0;
	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
		(VOS_CHAR *)pgucLAtSndCodeAddr,
		(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
		"^FLNA:%d",
		pstCnf->ucAggcLvl);


	CmdErrProc(ucClientId, pstCnf->ulErrCode, usLength, pgucLAtSndCodeAddr);
	return AT_FW_CLIENT_STATUS_READY;

}

/*******************************************************************************/

/* ��������: ��ѯRSSI*/

/* ����˵��: */

/*   ulIndex [in] ... */

/* �� �� ֵ: */

/*    TODO: ... */

/*******************************************************************************/
VOS_UINT32 atQryFRSSIPara(VOS_UINT8 ucClientId)
{
    FTM_FRSSI_REQ_STRU stFRssiQryReq = {0};
    VOS_UINT32 ulRst;

    
    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_FRSSI_REQ,ucClientId, (VOS_VOID*)(&stFRssiQryReq), sizeof(stFRssiQryReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FRSSI_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
VOS_UINT32 atQryFRSSIParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{

	OS_MSG_STRU* pEvent = NULL;
	FTM_FRSSI_CNF_STRU *pstCnf = NULL;
	VOS_UINT16 usLength = 0;

	pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_FRSSI_CNF_STRU *)pEvent->ulParam1;

	if(NULL == pstCnf)
	{
		return ERR_MSP_FAILURE;
	}

   	usLength = 0;
   	usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucLAtSndCodeAddr,(VOS_CHAR *)pgucLAtSndCodeAddr + usLength,
     			"^FRSSI:%d", pstCnf->lValue);

	CmdErrProc(ucClientId, pstCnf->ulErrCode,usLength, pgucLAtSndCodeAddr);
	return AT_FW_CLIENT_STATUS_READY;
}


VOS_UINT32 AT_GetLteFeatureInfo(AT_FEATURE_SUPPORT_ST*pstFeATure)
{

    /*AT_FEATURE_SUPPORT_ST *pstFeATure = NULL;
 */
    /*RRC_NV_SUPPORT_BAND_ID_LIST_STRU stSupportBandID = {0};
 */
    VOS_UINT32 ulRst  = 0;

    VOS_UINT8 ucBandStr[64] = {0};
    VOS_UINT8 ucBandNv = 0;
    VOS_UINT8 ucBandFlag = 0;

    VOS_UINT32 ulStrlen1=0;
#if (FEATURE_ON == MBB_COMMON)
    VOS_UINT8 ucDivBandStr[64] = {0};
    VOS_UINT32 ulStrlenDiv = 0;
    VOS_UINT32 ulStrlenGsmDiv = 0;
#endif
    VOS_UINT32 i =0;

    VOS_UINT8  ucBandNum[65]={0};
    LRRC_NV_UE_EUTRA_CAP_STRU *pstEutraCap = NULL;

    pstEutraCap = VOS_MemAlloc(WUEPS_PID_AT, (DYNAMIC_MEM_PT), sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));

    if( pstEutraCap == NULL)
    {
        return ERR_MSP_MALLOC_FAILUE;
    }

    MSP_MEMSET(pstEutraCap, 0, sizeof(LRRC_NV_UE_EUTRA_CAP_STRU ));

    ulRst = NVM_Read(EN_NV_ID_UE_CAPABILITY,pstEutraCap,sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));
    if( ulRst != ERR_MSP_SUCCESS )
    {
        VOS_MemFree(WUEPS_PID_AT, pstEutraCap);
        return ERR_MSP_FAILURE;
    }

	/*RRC_MAX_NUM_OF_BANDS
 */

    for( i = 0; i < pstEutraCap->stRfPara.usCnt; i++ )
    {
        if( pstEutraCap->stRfPara.astSuppEutraBandList[i].ucEutraBand > 0 )
        {
            ucBandNv=pstEutraCap->stRfPara.astSuppEutraBandList[i].ucEutraBand;
            if( ucBandNv < (RRC_MAX_NUM_OF_BANDS+1) )
            {
                ucBandNum[ucBandNv]=1;
                ucBandFlag++;
            }
        }
    }

    /*������ȡLTE band��Ϣ
 */
#if (FEATURE_ON == MBB_COMMON)
    if(AT_FEATURE_EXIST == pstFeATure[AT_FEATURE_DIVERSITY].ucFeatureFlag)
    {
        ulStrlenGsmDiv = strlen(pstFeATure[AT_FEATURE_DIVERSITY].aucContent);
        pstFeATure[AT_FEATURE_DIVERSITY].aucContent[ulStrlenGsmDiv] = ',';
        ulStrlenGsmDiv += 1;
    }
#endif
    if( ucBandFlag > 0 )
    {
        pstFeATure[AT_FEATURE_LTE].ucFeatureFlag = AT_FEATURE_EXIST;
#if (FEATURE_ON == MBB_COMMON)
        pstFeATure[AT_FEATURE_DIVERSITY].ucFeatureFlag = AT_FEATURE_EXIST;
#endif
        /*ulStrlen1 += At_sprintf(64,ucBandStr,ucBandStr+ulStrlen1,"%s","LTE,");
 */
    }
    else
    {
        VOS_MemFree(WUEPS_PID_AT, pstEutraCap);
        return ERR_MSP_FAILURE;
    }

    for( i = 1 ; i < 65; i++ )
    {
        if( ucBandNum[i] == 1 )
        {
            ulStrlen1 +=(VOS_UINT32) At_sprintf(64,(VOS_CHAR* )ucBandStr,(VOS_CHAR* )(ucBandStr+ulStrlen1),"B%d,",i);
#if (FEATURE_ON == MBB_COMMON)
            ulStrlenDiv +=(VOS_UINT32) At_sprintf(64,(VOS_CHAR* )ucDivBandStr,\
                                  (VOS_CHAR* )(ucDivBandStr+ulStrlenDiv),"L%d,",i);
#endif
            /*ucBandNum[i]=2;
 */
        }
    }

    for( i = 0 ; i < ulStrlen1-1; i++ )
    {
        pstFeATure[AT_FEATURE_LTE].aucContent[i] = ucBandStr[i];
    }
#if (FEATURE_ON == MBB_COMMON)
    ulStrlenDiv += ulStrlenGsmDiv;
    for(i = ulStrlenGsmDiv; i < ulStrlenDiv - 1; i++)
    {
        pstFeATure[AT_FEATURE_DIVERSITY].aucContent[i] = ucDivBandStr[i - ulStrlenGsmDiv];
    }
    if (0 != ulStrlenDiv)
    {
        pstFeATure[AT_FEATURE_DIVERSITY].aucContent[ulStrlenDiv - 1] = '\0';
    }
#endif

    for( i = 0 ; i < ulStrlen1; i++ )/* [false alarm]:fortify */
    {
        ucBandStr[i] = 0;/* [false alarm]:fortify */
    }/* [false alarm]:fortify */

    ulStrlen1 = 0;/* [false alarm]:fortify*/

    VOS_MemFree(WUEPS_PID_AT, pstEutraCap);/* [false alarm]:fortify */
    return ERR_MSP_SUCCESS;/* [false alarm]:fortify */

}


VOS_UINT32 atSetTBATPara(VOS_UINT8 ucClientId)
{
#if (FEATURE_ON == MBB_COMMON)
    VOS_INT32                       batInfo = 0;
    VOS_UINT8  ucType = 0;
    VOS_UINT8  ucOpr = 0;
#else
    FTM_SET_TBAT_REQ_STRU stTbatSet ={0};
    FTM_RD_TBAT_REQ_STRU  stTbatRd={0};

    VOS_UINT8  ucType = 0;
    VOS_UINT8  ucOpr = 0;
    VOS_UINT16 usValue = 0;
    VOS_UINT32 ulRst=0;
#endif


    /* �������
 */
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(4 < gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if((0 == gastAtParaList[0].usParaLen) ||
       (0 == gastAtParaList[1].usParaLen) )
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucType = (VOS_UINT8)(gastAtParaList[0].ulParaValue);
    ucOpr = (VOS_UINT8)(gastAtParaList[1].ulParaValue);
#if (FEATURE_ON == MBB_COMMON)
    /*�����ж�:����Ʒ��֧�ֵ�أ���ֱ�ӷ���ERROR*/
    if (BSP_MODULE_UNSUPPORT == DRV_GET_BATTERY_SUPPORT())
    {
        return AT_ERROR;
    }
    
    if(AT_TBAT_GET_FROM_UUT == ucOpr && 2 == gucAtParaIndex)
    {
        /* ��ȡ */
        switch(ucType)
        {
            case AT_TBAT_ANALOG_VOLTAGE:
            {
                if (CHG_OK != chg_tbat_read(CHG_AT_BATTERY_LEVEL, &batInfo))
                {
                    return AT_ERROR;
                }
            }
            break;
            case AT_TBAT_DIGITAL_VOLTAGE:
            {
                if (CHG_OK != chg_tbat_read(CHG_AT_BATTERY_ADC, &batInfo))
                {
                    return AT_ERROR;
                }
            }
            break;
            case AT_TBAT_VOLUME:
            {
                if (CHG_OK != chg_tbat_read(CHG_AT_BATTERY_CAPACITY, &batInfo))
                {
                    return AT_ERROR;
                }
            }
            break;
            default:
                return AT_ERROR;
        }
        
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                 "%s:%d,%d",
                                 g_stParseContext[ucClientId].pstCmdElement->pszCmdName,
                                 ucType,
                                 batInfo);
        return AT_OK;
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
#else
    if( ucOpr == 1 )
    {
        /*����
 */
        if(0 != gastAtParaList[2].usParaLen)/* [false alarm]:fortify */
        {
            usValue = gastAtParaList[2].usParaLen;/* [false alarm]:fortify*/

            stTbatSet.ucOpr = ucOpr;/* [false alarm]:fortify */
            stTbatSet.ucType = ucType;/* [false alarm]:fortify */
            stTbatSet.usValueMin = (VOS_UINT16)gastAtParaList[2].ulParaValue;/* [false alarm]:fortify */
            stTbatSet.usValueMax = (VOS_UINT16)gastAtParaList[3].ulParaValue;/* [false alarm]:fortify */

            HAL_SDMLOG("\n stTbatSet.usValueMin=%d,stTbatSet.usValueMax=%d\n",stTbatSet.usValueMin,stTbatSet.usValueMax);

            ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_TBAT_REQ,ucClientId, (VOS_VOID*)(&stTbatSet), sizeof(stTbatSet));/* [false alarm]:fortify */
            if(AT_SUCCESS == ulRst)
            {
                gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_TBAT_SET;
                return AT_WAIT_ASYNC_RETURN;
            }
            return AT_ERROR;
        }
        else
        {
            return AT_ERROR;
        }
    }
    else if( ucOpr == 0 )
    {
        /*��ѯ
 */
        usValue = (VOS_UINT16)gastAtParaList[2].usParaLen;/* [false alarm]:fortify */

        stTbatRd.ucOpr = ucOpr;/* [false alarm]:fortify */
        stTbatRd.ucType = ucType;/* [false alarm]:fortify */
        stTbatRd.usValue = usValue;

        ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_TBAT_REQ,ucClientId, (VOS_VOID*)(&stTbatRd), sizeof(stTbatRd));
        if(AT_SUCCESS == ulRst)
        {
            gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_TBAT_READ;
            return AT_WAIT_ASYNC_RETURN;
        }
        return AT_ERROR;

    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
#endif
}


VOS_UINT32 atSetTbatCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU*pEvent = NULL;
    FTM_SET_TBAT_CNF_STRU *pstCnf=NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_SET_TBAT_CNF_STRU *)pEvent->ulParam1;
    HAL_SDMLOG("\n enter into atSetTbatCnf\n");
    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
    return AT_OK;
}

VOS_UINT32 atRdTbatCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU*pEvent = NULL;
    FTM_RD_TBAT_CNF_STRU *pstCnf=NULL;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_RD_TBAT_CNF_STRU *)pEvent->ulParam1;
    HAL_SDMLOG("\n enter into atRdTbatCnf\n");
    HAL_SDMLOG("\n pstCnf->ucType=%d,pstCnf->usValue=%d \n",(VOS_INT)pstCnf->ucType,(VOS_INT)pstCnf->usValue);

    gstLAtSendData.usBufLen = 0;
    gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "^TBAT:%d,%d",
                                               pstCnf->ucType,pstCnf->usValue
                                             );

    CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);

    return AT_OK;
}

// *****************************************************************************
// ��������: ���÷�����ķ��书��
//
// ����˵��:
//   ulIndex [in] ...
//                ...
//
// �� �� ֵ:
//    TODO: ...
// *****************************************************************************
VOS_UINT32 atSetFPOWPara(VOS_UINT8 ucClientId)
{
    FTM_FPOW_REQ_STRU stFPOWSetReq = {0};
    VOS_UINT32 ulRst = 0;
    VOS_INT16 sPower = 0;

    /*lint -e516*/
    HAL_SDMLOG("-----enter:[%s] \n", __FUNCTION__);
    /*lint -e516*/

    // �������
    if(AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(1 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    } 

    if(0 != gastAtParaList[0].usParaLen)
    {
        //sPower = (S16_T)atoi((CONST CHAR_T*)(gastAtParaList[0].aucPara));
        //sPower = gastAtParaList[0].ulParaValue;
        ulRst = initParaListS16((AT_PARSE_PARA_TYPE_STRU *)(&(gastAtParaList[0])),1,(VOS_INT16*)(&sPower));

        if(ulRst != ERR_MSP_SUCCESS)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
        
        if(-60 > sPower || 24 < sPower)
        {
            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stFPOWSetReq.sPower = sPower;
      
    //(S16_T)(gastAtParaList[0].ulParaValue);
    HAL_SDMLOG("-----[%s]:send data to C-core \n", __FUNCTION__);

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_FPOW_REQ, ucClientId, (VOS_VOID*)(&stFPOWSetReq), sizeof(stFPOWSetReq));

    if(AT_SUCCESS == ulRst)
    {
        // ���õ�ǰ��������
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_FPOW_SET;

        return AT_WAIT_ASYNC_RETURN;    
        // ������������״̬
     }

    return AT_ERROR;
}

VOS_UINT32 atSetFPOWParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID*pMsgBlock)
{

    OS_MSG_STRU* pEvent = NULL;
    FTM_FPOW_CNF_STRU *pstCnf = NULL;


    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pstCnf = (FTM_FPOW_CNF_STRU *)pEvent->ulParam1;

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_FW_CLIENT_STATUS_READY;

}


