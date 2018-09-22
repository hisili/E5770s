

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafAgentCtx.h"
#include  "TafAgentLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

    /*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_AGENT_CTX_C
    /*lint -e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

TAFAGENT_CTX_STRU                       g_stTafAgentCtx = {0};
TAF_AGENT_STATS_INFO_STRU               g_stTafAgentStats = {0};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_UINT32 Taf_Agent_InitCtx(VOS_VOID)
{
    g_stTafAgentCtx.pucTafAcpuCnfMsg = VOS_NULL_PTR;

    /* ���以���ź��� */
    if (VOS_OK != VOS_SmMCreate("SYNC", VOS_SEMA4_FIFO, &g_stTafAgentCtx.ulTafAcpuSyncSem))
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "Create aps acpu sycn sem failed!");
        TAF_AGENT_DBG_CREATE_MUTEX_SEM_FAIL_NUM(1);
        g_stTafAgentCtx.ulInitFlg = VOS_FALSE;
        return VOS_ERR;
    }
    else
    {
        TAF_AGENT_DBG_SAVE_MUTEX_SEM_ID(g_stTafAgentCtx.ulTafAcpuSyncSem);
    }

    /* ����������ź��� */
    if (VOS_OK != VOS_SmBCreate( "CNF", 0, VOS_SEMA4_FIFO, &g_stTafAgentCtx.ulTafAcpuCnfSem))
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "Create aps acpu cnf sem failed!");
        TAF_AGENT_DBG_CREATE_BINARY_SEM_FAIL_NUM(1);
        g_stTafAgentCtx.ulInitFlg = VOS_FALSE;
        return VOS_ERR;
    }
    else
    {
        TAF_AGENT_DBG_SAVE_BINARY_SEM_ID(g_stTafAgentCtx.ulTafAcpuCnfSem);
    }

    g_stTafAgentCtx.ulInitFlg = VOS_TRUE;

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    TAF_AGENT_ClearMsg();

    return VOS_OK;
}


VOS_UINT32 TAF_AGENT_GetTafAcpuSyncSem(VOS_VOID)
{
    return g_stTafAgentCtx.ulTafAcpuSyncSem;
}


VOS_UINT32 TAF_AGENT_GetTafAcpuCnfSem(VOS_VOID)
{
    return g_stTafAgentCtx.ulTafAcpuCnfSem;
}


VOS_UINT8* TAF_AGENT_GetTafAcpuCnfMsg(VOS_VOID)
{
    return g_stTafAgentCtx.pucTafAcpuCnfMsg;
}


VOS_VOID TAF_AGENT_SetTafAcpuCnfMsg(VOS_UINT8* pMsg)
{
    g_stTafAgentCtx.pucTafAcpuCnfMsg = pMsg;
}


VOS_VOID TAF_AGENT_ClearMsg(VOS_VOID)
{
    PS_MEM_SET(g_stTafAgentCtx.aucMsg,0,sizeof(g_stTafAgentCtx.aucMsg));
}


VOS_UINT8* TAF_AGENT_SaveMsg(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen
)
{
    if ((TAFAGENT_APS_MAX_MSG_LEN - VOS_MSG_HEAD_LENGTH) >= ulLen)
    {
        /* ���ݻظ���Ϣ */
        PS_MEM_CPY(g_stTafAgentCtx.aucMsg, pucMsg, ulLen + VOS_MSG_HEAD_LENGTH);

        return &(g_stTafAgentCtx.aucMsg[0]);
    }
    else
    {
        vos_printf("TAF_AGENT_SaveMsg-->msg len too big\n");
        return VOS_NULL_PTR;
    }
}


VOS_VOID TAF_AGENT_ShowStats(VOS_VOID)
{
    vos_printf("********************TAF AGENTͳ����Ϣ*******************\n");
    vos_printf("ģ���ʼ����ʶ                              %d\n", g_stTafAgentCtx.ulInitFlg);
    vos_printf("��ǰ�Ļ����ź���                            %x\n", g_stTafAgentCtx.ulTafAcpuSyncSem);
    vos_printf("��ǰ�Ļ����ź���                            %x\n", g_stTafAgentCtx.ulTafAcpuCnfSem);
    vos_printf("�����Ļ����ź���                            %x\n", g_stTafAgentStats.ulMutexSemId);
    vos_printf("�����Ķ������ź���                          %x\n", g_stTafAgentStats.ulBinarySemId);
    vos_printf("���������ź���ʧ�ܴ���                      %d\n", g_stTafAgentStats.ulCreateMutexSemFailNum);
    vos_printf("�����������ź���ʧ�ܴ���                    %d\n", g_stTafAgentStats.ulCreateBinarySemFailNum);
    vos_printf("�������ź���ʧ�ܴ���                        %d\n", g_stTafAgentStats.ulLockMutexSemFailNum);
    vos_printf("���������ź���ʧ�ܴ���                      %d\n", g_stTafAgentStats.ulLockBinarySemFailNum);
    vos_printf("���һ���������ź���ʧ��ԭ��                %x\n", g_stTafAgentStats.ulLastMutexSemErrRslt);
    vos_printf("���һ�����������ź���ʧ��ԭ��              %x\n", g_stTafAgentStats.ulLastBinarySemErrRslt);
    vos_printf("ͬ����ϢΪ�մ���                            %d\n", g_stTafAgentStats.ulSyncMsgIsNullNum);
    vos_printf("ͬ����Ϣ��ƥ�����                          %d\n", g_stTafAgentStats.ulSyncMsgNotMatchNum);

    vos_printf("\r\n");

}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
