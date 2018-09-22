
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "om.h"
#include "omprivate.h"
#include "ombbplog.h"
#include "DrvInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*lint -e767 �޸��ˣ����±� */
#define    THIS_FILE_ID        PS_FILE_ID_OM_APP_BBP_LOG_C
/*lint +e767 �޸��ˣ����±� */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/
extern VOS_UINT32 Om_AcpuDumpReboot(APP_OM_MSG_EX_STRU *pstAppToOmMsg,
                                           VOS_UINT16 usReturnPrimId);

extern VOS_UINT32 Om_QueryMsgFunc(OM_REQ_PACKET_STRU *pRspPacket, OM_MSG_FUN_STRU *pstMsgFuncTable, VOS_UINT32 ulTotalNum);

/*****************************************************************************
  4 ��Ϣ������ӳ���
*****************************************************************************/
/*PC�·��� BBP�������ά�ɲ���Ϣ������ӳ��� */
OM_MSG_FUN_STRU                         g_astAcpuOmBbpMsgFunTbl[] =
{
    {APP_OM_BBP_DUMP_DUMP_REQ,    Om_AcpuDumpReboot        ,    OM_APP_BBP_DUMP_DUMP_CNF},
};


/*****************************************************************************
  5 ����ʵ��
*****************************************************************************/


VOS_UINT32 Om_AcpuDumpReboot(APP_OM_MSG_EX_STRU *pstAppToOmMsg,
                                           VOS_UINT16 usReturnPrimId)
{
    BBP_DUMP_CHOOSE_STRU               *pstPcMsg;

    pstPcMsg        = (BBP_DUMP_CHOOSE_STRU*)pstAppToOmMsg->aucPara;

    if (BBP_DUMP_CHOOSE_YES == pstPcMsg->ulChooseRelt)
    {
        LogPrint("Om_AcpuDumpReboot: Reboot\r\n");

        /* ����DRV �ӿڸ�λ���� fastbootģʽ */
        DRV_EDMA_BBP_SAMPLE_REBOOT();
    }

    return VOS_OK;
}


VOS_VOID Om_AcpuBbpConfigMsgProc(OM_REQ_PACKET_STRU *pRspPacket, OM_RSP_FUNC *pRspFuncPtr)
{
    APP_OM_MSG_EX_STRU                 *pstAppToOmMsg;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulTotalNum;
    VOS_UINT16                          usPrimId;
    VOS_UINT16                          usReturnPrimId;
    VOS_UINT32                          ulResult = VOS_ERR;

    pstAppToOmMsg   = (APP_OM_MSG_EX_STRU*)pRspPacket;
    ulTotalNum      = sizeof(g_astAcpuOmBbpMsgFunTbl) / sizeof(OM_MSG_FUN_STRU);
    usPrimId = pstAppToOmMsg->usPrimId;
    /* ��ѯ������ */
    for (ulIndex = 0; ulIndex < ulTotalNum; ulIndex++)
    {
        if (usPrimId == (VOS_UINT16)(g_astAcpuOmBbpMsgFunTbl[ulIndex].ulPrimId))
        {
            usReturnPrimId = (VOS_UINT16)(g_astAcpuOmBbpMsgFunTbl[ulIndex].ulReturnPrimId);
            ulResult = g_astAcpuOmBbpMsgFunTbl[ulIndex].pfFun(pstAppToOmMsg, usReturnPrimId);
            break;
        }
    }

    /* û�в�ѯ��������  */
    if (ulIndex == ulTotalNum)
    {
        OM_AcpuSendResult(pstAppToOmMsg->ucFuncType, ulResult, usPrimId);
    }
    return;

}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

