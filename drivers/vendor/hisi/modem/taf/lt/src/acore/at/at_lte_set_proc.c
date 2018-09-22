/*lint -save -e537 -e958 -e718 -e746*/
#include "osm.h"
#include "gen_msg.h"
#include "at_lte_common.h"
#include "ATCmdProc.h"

/***************************************************************************** 
 �� �� ��  : atSetTmodePara
 ��������  : ����TMODEģʽ��TL C�� 
 �������  : ucClientId Client ID
             ulTmode ģʽ �������  : ��
 �� �� ֵ  : �ɹ�����AT_OK��ʧ�ܷ���AT_ERROR*****************************************************************************/VOS_UINT32 atSetTmodePara(VOS_UINT8 ucClientId, VOS_UINT32 ulTmode)
{
    SYM_SET_TMODE_REQ_STRU stTmode ;
    stTmode.enTmodeMode = (SYM_TMODE_ENUM)ulTmode;

    if(AT_SUCCESS == atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_SYM_SET_TMODE_REQ,ucClientId,
        (VOS_VOID *)(&stTmode), sizeof(SYM_SET_TMODE_REQ_STRU)))
    {
       return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
}

/***************************************************************************** 
 �� �� ��  : atSetTmodeParaCnfProc
 ��������  : TL C��ģʽ���÷��ش����� �������  : ucClientId Client ID
             pMsgBlock  ��Ϣ����             
 �������  : �� 
 �� �� ֵ  : ����AT_FW_CLIENT_STATUS_READY
*****************************************************************************/
VOS_UINT32 atSetTmodeParaCnfProc(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    OS_MSG_STRU* pEvent = NULL;
    SYM_SET_TMODE_CNF_STRU * pTmodeCnf = NULL;

    /* pMsgBlock ���ϲ���������ж��Ƿ�Ϊ�� */
    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
    pTmodeCnf = (SYM_SET_TMODE_CNF_STRU *)pEvent->ulParam1;
    
    HAL_SDMLOG("\n atSetTmodeParaCnfProc, ulErrCode=0x%x\n", (VOS_INT)pTmodeCnf->ulErrCode);

    CmdErrProc(ucClientId, pTmodeCnf->ulErrCode, 0, NULL);
    return AT_FW_CLIENT_STATUS_READY;
}
/*lint -restore*/

