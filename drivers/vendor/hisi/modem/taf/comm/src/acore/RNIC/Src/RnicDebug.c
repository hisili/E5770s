

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "RnicDebug.h"
#include "RnicCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/

RNIC_STATS_INFO_STRU                    g_astRnicStats[RNIC_NET_ID_MAX_NUM];
VOS_UINT32                              g_ulRnicLatencySwitch = 0;

RNIC_RMNET_CONFIG_CHECK_INFO_STRU       g_stRnicRmnetConfigCheckInfo;
VOS_UINT32                              g_ulRnicPrintDlDataFlg = VOS_FALSE;

VOS_UINT32                              g_ulRnicPrintUlDataFlg = VOS_FALSE;


/******************************************************************************
   5 ����ʵ��
******************************************************************************/

VOS_VOID RNIC_SetPrintUlDataFlg(VOS_UINT32 ulFlg)
{
    g_ulRnicPrintUlDataFlg = ulFlg;
}


VOS_VOID RNIC_ShowRnicPdpStats(VOS_UINT8 ucRmNetId)
{
    RNIC_PDP_CTX_STRU                  *pstPdpCtx;

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        vos_printf("RNIC_ShowRnicPdpStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    pstPdpCtx                           = RNIC_GetPdpCtxAddr(ucRmNetId);

    vos_printf("RNIC %d IPV4 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.enRegStatus);
    vos_printf("RNIC %d IPV4 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucRabId);
    vos_printf("RNIC %d IPV4 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucPdnId);
    vos_printf("RNIC %d IPV4 PDP IPV4ADDR                   %d\n\n", ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ulIpv4Addr);

    vos_printf("RNIC %d IPV6 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.enRegStatus);
    vos_printf("RNIC %d IPV6 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucRabId);
    vos_printf("RNIC %d IPV6 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucPdnId);
    vos_printf("RNIC %d IPV6 PDP IPV6ADDR                   %s\n\n", ucRmNetId, pstPdpCtx->stIpv6PdpInfo.aucIpv6Addr);

    vos_printf("RNIC %d IPV4V6 PDP STATUS                   %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.enRegStatus);
    vos_printf("RNIC %d IPV4V6 PDP RABID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucRabId);
    vos_printf("RNIC %d IPV4V6 PDP PDNID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucPdnId);
    vos_printf("RNIC %d IPV4V6 PDP IPV4ADDR                 %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ulIpv4Addr);
    vos_printf("RNIC %d IPV4V6 PDP IPV6ADDR                 %s\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.aucIpv6Addr);
}


VOS_VOID RNIC_ShowUlProcStats(VOS_UINT8 ucRmNetId)
{
    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        vos_printf("RNIC_ShowUlProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* ����ͳ���� */
    vos_printf("RNIC %d����״̬                                        %d\n", ucRmNetId, g_stRnicCtx.astSpecCtx[ucRmNetId].enFlowCtrlStatus);
    vos_printf("RNIC %d�յ�����IPV4���ݵĸ���                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4PktNum);
    vos_printf("RNIC %d�յ�����IPV6���ݵĸ���                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv6PktNum);
    vos_printf("IPV4V6���ͼ���ʱRNIC %d�յ��������ݵĸ���IPV4IPV6      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4v6PktNum);
    vos_printf("RNIC %dδ����ʱ�յ��������ݵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvUndiaPktNum);
    vos_printf("RNIC %d���з��͸�ADS���ݵĸ���                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktNum);
    vos_printf("RNIC %d��ADS������������ʧ�ܵĸ���                     %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktFailNum);
    vos_printf("RNIC %dδ���Ϻ�ǰ�����յ�IPV4�㲥���ĸ���              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlIpv4BrdcstPktNum);
    vos_printf("RNIC %d����ת��ΪIMM_ZCʧ�ܵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlImmzcFailPktNum);
    vos_printf("RNIC %d����˽�����ݴ��󶪵��������ݰ��ĸ���            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetCardDiscardNum);
    vos_printf("RNIC %d����ID���󶪵��������ݰ��ĸ���                  %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetIdDiscardNum);
    vos_printf("RNIC %dModem ID���󶪵��������ݰ��ĸ���                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlModemIdDiscardNum);
    vos_printf("RNIC %d���ض����������ݰ��ĸ���                        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlFlowCtrlDiscardNum);
    vos_printf("RNIC %d�յ��������ݰ��ĸ�����ipv4ipv6��                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvErrPktNum);
    vos_printf("RNIC %d�ɹ��ϱ�APP���貦��                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpSucc);
    vos_printf("RNIC %d�ϱ�APP���貦��ʧ��                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpFail);
    vos_printf("RNIC %d�ɹ��ϱ�APP�Ͽ�����                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownSucc);
    vos_printf("RNIC %d�ϱ�APP�Ͽ�����ʧ��                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownFail);

    if (RNIC_RM_NET_ID_0 == ucRmNetId)
    {
        vos_printf("����ģʽ                                           %d\n", g_stRnicCtx.stDialMode.enDialMode);
        vos_printf("���貦���Ƿ��ϱ��¼�                               %d\n", g_stRnicCtx.stDialMode.enEventReportFlag);
        vos_printf("���貦�ŶϿ�ʱ��                                   %d\n", g_stRnicCtx.stDialMode.ulIdleTime);
    }

    vos_printf("RNIC %d RAB ID����RNIC���������ݰ�����                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRabIdErr);

    vos_printf("RNIC %d PDN ID����RNIC���������ݰ�����                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlPdnIdErr);

    vos_printf("\r\n");

    return;
}


VOS_VOID RNIC_ShowDLProcStats(VOS_UINT8 ucRmNetId)
{
    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        vos_printf("RNIC_ShowDLProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* ����ͳ���� */
    vos_printf("RNIC %d�յ�����IPV4���ݵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv4PktNum);
    vos_printf("RNIC %d�յ�����IPV6���ݵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv6PktNum);
    vos_printf("RNIC %d�����������ݵĸ���                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktNum);
    vos_printf("RNIC %d������������ʧ�ܵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktFailNum);
    vos_printf("RNIC %d�յ��������ݰ�����MTU�ĸ���                 %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvBigPktNum);
    vos_printf("RNIC %d����δ����������ݸ���                    %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlDiscardPktNum);
    vos_printf("RNIC %d���м�MACͷʧ�ܵĸ���                       %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlAddMacHdFailNum);
    vos_printf("RNIC %d����˽�����ݴ��󶪵��������ݰ��ĸ���        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetCardDiscardNum);
    vos_printf("RNIC %d����ID���󶪵��������ݰ��ĸ���              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetIdDiscardNum);
    vos_printf("RNIC %d�յ��������ݰ��ĸ�����ipv4ipv6��            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvErrPktNum);
    vos_printf("\r\n");

    return;
}


VOS_VOID RNIC_ShowResetStats(VOS_VOID)
{
    vos_printf("ģ���ʼ����ʶ                              %d\n", g_astRnicStats[0].ulSemInitFlg);
    vos_printf("��ǰ�Ķ������ź���                          %x\n", g_stRnicCtx.ulResetSem);
    vos_printf("�����Ķ������ź���                          %x\n", g_astRnicStats[0].ulBinarySemId);
    vos_printf("�����������ź���ʧ�ܴ���                    %d\n", g_astRnicStats[0].ulCreateBinarySemFailNum);
    vos_printf("���������ź���ʧ�ܴ���                      %d\n", g_astRnicStats[0].ulLockBinarySemFailNum);
    vos_printf("���һ�����������ź���ʧ��ԭ��              %x\n", g_astRnicStats[0].ulLastBinarySemErrRslt);
    vos_printf("��λ�ɹ��Ĵ���                              %d\n", g_astRnicStats[0].ulResetSucessNum);
}


VOS_VOID RNIC_ShowRmnetConfigCheckInfo(VOS_VOID)
{
    vos_printf("Totla req                           %d\n", g_stRnicRmnetConfigCheckInfo.ucTotlaCnt);
    vos_printf("Modem type err                      %d\n", g_stRnicRmnetConfigCheckInfo.ucModemTypeErrCnt);
    vos_printf("Rmnet id err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucRmNetIdErrCnt);
    vos_printf("Modem ID err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucModemIdErrCnt);
    vos_printf("Pdn ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucPdnIdErrCnt);
    vos_printf("Rab ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucRabIdErrCnt);
    vos_printf("Rmnet status err                    %d\n", g_stRnicRmnetConfigCheckInfo.ucRmnetStatusErrCnt);
    vos_printf("IP type err                         %d\n", g_stRnicRmnetConfigCheckInfo.ucIpTypeErrCnt);
    vos_printf("Send err                            %d\n", g_stRnicRmnetConfigCheckInfo.ucSendErrCnt);
    vos_printf("Success                             %d\n", g_stRnicRmnetConfigCheckInfo.ucSuccCnt);
}


VOS_VOID RNIC_Help(VOS_VOID)
{

    vos_printf("********************RNIC������Ϣ************************\n");
    vos_printf("RNIC_ShowUlProcStats  ucRmNetId                 ��ʾָ��RNIC��������ͳ����Ϣ\n");
    vos_printf("RNIC_ShowDLProcStats  ucRmNetId                 ��ʾָ��RNIC��������ͳ����Ϣ\n");
    vos_printf("RNIC_ShowRnicPdpStats ucRmNetId                 ��ʾָ��RNIC����PDP������Ϣ\n");
    vos_printf("RNIC_ShowResetStats                             ��ʾָ��RNIC��λ״̬��Ϣ\n");

    return;
}


VOS_VOID RNIC_MNTN_OpenLatency(VOS_VOID)
{
    g_ulRnicLatencySwitch = 1;

    return;
}


VOS_VOID RNIC_MNTN_CloseLatency(VOS_VOID)
{
    g_ulRnicLatencySwitch = 0;

    return;
}


VOS_VOID RNIC_MNTN_TraceRcvUlData(VOS_VOID)
{
    if (1 == g_ulRnicLatencySwitch)
    {
        RNIC_LATENCY_LOG(ACPU_PID_RNIC, "User plane latency trace: RNIC Rcv UL data");
    }

    return;
}


VOS_VOID RNIC_MNTN_TraceRcvDlData(VOS_VOID)
{
    if (1 == g_ulRnicLatencySwitch)
    {
        RNIC_LATENCY_LOG(ACPU_PID_RNIC, "User plane latency trace: RNIC Rcv DL data");
    }

    return;
}


VOS_VOID RNIC_MNTN_TraceSndDlData(VOS_VOID)
{
    if (1 == g_ulRnicLatencySwitch)
    {
        RNIC_LATENCY_LOG(ACPU_PID_RNIC, "User plane latency trace: RNIC Send DL data");
    }

    return;
}


VOS_VOID RNIC_LATENCY_OM_LOG( const VOS_CHAR  *pcFileName,  VOS_UINT32  ulLineNum,
                           VOS_UINT32      ulModuleId,   VOS_UINT32 ulLevel,
                           const VOS_CHAR  *pcString )
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32          ulRslt = 0;

    ulRslt = DIAG_PrintfV(DIAG_ID(ulModuleId, ulLevel), (VOS_CHAR*)pcFileName, ulLineNum, (VOS_CHAR*)("%s"), (VOS_INT32)pcString);
    if (PS_SUCC != ulRslt)
    {
        return;
    }
#endif

    return;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



