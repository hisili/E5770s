


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸��ˣ�g47350�������ˣ�l46160��ԭ������������־�ļ���ID����*/
#define    THIS_FILE_ID        PS_FILE_ID_CPM_C
/*lint +e767 �޸��ˣ�g47350�������ˣ�l46160*/


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "cpm.h"

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

CPM_PHY_PORT_CFG_STRU   g_astCPMPhyPortCfg[CPM_PORT_BUTT - CPM_APP_PORT];
CPM_LOGIC_PORT_CFG_STRU g_astCPMLogicPortCfg[CPM_COMM_BUTT];

/*****************************************************************************
  3 ����������
*****************************************************************************/

extern VOS_UINT32 OM_SDInit(VOS_VOID);
extern VOS_VOID GU_OamPortInit(VOS_VOID);
extern VOS_UINT32 Sock_PortInit(VOS_VOID);
extern VOS_UINT32 OM_LogFileInit(VOS_VOID);

/*****************************************************************************
  4 �����嶨��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : CPM_PhySendReg
 ��������  : �ṩ���ⲿ��ע�ắ������������ͨ�����յ����ݵĴ���
 �������  : enPhyPort��  ע�������ͨ����
             pRecvFunc��  ���ݽ��պ���
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID CPM_PhySendReg(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_FUNC pSendFunc)
{
    if (CPM_PORT_BUTT > enPhyPort)
    {
        CPM_PHY_SEND_FUNC(enPhyPort - CPM_APP_PORT) = pSendFunc;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CPM_LogicRcvReg
 ��������  : ���߼�ͨ��ע����պ���
 �������  : enLogicPort�� ע����߼�ͨ����
             pRecvFunc��   ���ݽ��պ���
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID CPM_LogicRcvReg(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort, CPM_FUNC pRcvFunc)
{
    if (CPM_COMM_BUTT > enLogicPort)
    {
        CPM_LOGIC_RCV_FUNC(enLogicPort) = pRcvFunc;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CPM_QueryPhyPort
 ��������  : ��ѯ��ǰ�߼�ͨ��ʹ�õ�����˿�
 �������  : enLogicPort��  �߼�ͨ����
 �������  : ��
 �� �� ֵ  : ����ͨ����

*****************************************************************************/
CPM_PHY_PORT_ENUM_UINT32 CPM_QueryPhyPort(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort)
{
    return CPM_LOGIC_PHY_PORT(enLogicPort);
}

/*****************************************************************************
 �� �� ��  : CPM_ConnectPorts
 ��������  : ������ͨ�����߼�ͨ��������
 �������  : enPhyPort��    ����ͨ����
             enLogicPort��  �߼�ͨ����
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID CPM_ConnectPorts(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort)
{
    if ((CPM_PORT_BUTT <= enPhyPort) || (CPM_COMM_BUTT <= enLogicPort))
    {
        return;
    }

    if (CPM_APP_PORT > enPhyPort)
    {
        /* ��AT��÷������ݵĺ���ָ�� */
        CPM_LOGIC_SEND_FUNC(enLogicPort) = AT_QuerySndFunc(enPhyPort);

        /* ���߼�ͨ���Ľ��պ�����ATģ�� */
        AT_RcvFuncReg(enPhyPort, CPM_LOGIC_RCV_FUNC(enLogicPort));
    }
    else
    {
        /* ���ӷ���ͨ�� */
        CPM_LOGIC_SEND_FUNC(enLogicPort)= CPM_PHY_SEND_FUNC(enPhyPort - CPM_APP_PORT);

        /* ���ӽ���ͨ�� */
        CPM_PHY_RCV_FUNC(enPhyPort - CPM_APP_PORT) = CPM_LOGIC_RCV_FUNC(enLogicPort);
    }

    /* �������ͺ���ע����߼�ͨ�� */
    CPM_LOGIC_PHY_PORT(enLogicPort) = enPhyPort;

    return;
}

/*****************************************************************************
 �� �� ��  : CPM_DisconnectPorts
 ��������  : �Ͽ�����ͨ�����߼�ͨ������
 �������  : enPhyPort��    ����ͨ����
             enLogicPort��  �߼�ͨ����
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID CPM_DisconnectPorts(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort)
{
    if ((CPM_PORT_BUTT <= enPhyPort) || (CPM_COMM_BUTT <= enLogicPort))
    {
        return;
    }

    /* ���統ǰ�߼�ͨ����û��ʹ�ô�����ͨ�������ô��� */
    if (enPhyPort != CPM_LOGIC_PHY_PORT(enLogicPort))
    {
        return;
    }

    if (CPM_APP_PORT > enPhyPort)
    {
        /* ��ATȥע����պ��� */
        AT_RcvFuncReg(enPhyPort, VOS_NULL_PTR);
    }
    else
    {
        /* �Ͽ�����ͨ�� */
        CPM_PHY_RCV_FUNC(enPhyPort - CPM_APP_PORT) = VOS_NULL_PTR;
    }

    /* �Ͽ�����ͨ�� */
    CPM_LOGIC_SEND_FUNC(enLogicPort)= VOS_NULL_PTR;
    CPM_LOGIC_PHY_PORT(enLogicPort) = CPM_PORT_BUTT;

    return;
}

/*****************************************************************************
 �� �� ��  : CPM_NotifyChangePort
 ��������  : �ṩ��ACPU ATģ����ã�����֪ͨOM���ж˿��л�
 �������  : enLogicPort���߼�ͨ����
             enPhyPort��  ����ͨ����
 �������  : ��
 �� �� ֵ  : VOS_OK:�ɹ�������Ϊʧ��

*****************************************************************************/
VOS_UINT32 CPM_NotifyChangePort(AT_PHY_PORT_ENUM_UINT32 enPhyPort,
                                       CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort)
{
    /* ������� */
    if ((enPhyPort >= CPM_PORT_BUTT) || (enLogicPort>= CPM_COMM_BUTT))
    {
        return VOS_ERR;
    }

    /* �жϵ�ǰOMͨ���Ƿ�ΪWIFI */
    if (CPM_WIFI_OM_PORT == CPM_LOGIC_PHY_PORT(enLogicPort))
    {
        /* �ر�SOCKET���� */
    }

    /* �Ͽ���ǰͨ�� */
    CPM_DisconnectPorts(CPM_LOGIC_PHY_PORT(enLogicPort), enLogicPort);

    CPM_ConnectPorts(enPhyPort, enLogicPort);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CPM_PnpAppPortCB
 ��������  : ע���DRV�Ĳ�λص�����
 �������  : bPortState�� VOS_TRUEͨ�������ӡ�VOS_FALSEͨ���ѶϿ�
 �������  : ��
 �� �� ֵ  : VOS_OK:�ɹ�������Ϊʧ��

*****************************************************************************/
VOS_VOID CPM_PnpAppPortCB(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, VOS_BOOL bPortState)
{
    CPM_PHY_PORT_ENUM_UINT32 enCurPhyPort;

    /* USBͨ���Ѵ� */
    if (VOS_TRUE == bPortState)
    {
        enCurPhyPort = CPM_LOGIC_PHY_PORT(CPM_OM_COMM);

        if ((CPM_APP_PORT != enCurPhyPort) && (CPM_CTRL_PORT != enCurPhyPort))
        {
            CPM_DisconnectPorts(enCurPhyPort, CPM_OM_COMM);

            /* ����APP�ں�OMͨ�� */
            CPM_ConnectPorts(enPhyPort, CPM_OM_COMM);
        }

        return ;
    }

    /* USBͨ���ѹرգ��Ͽ�APP����OMͨ�� */
    CPM_DisconnectPorts(CPM_APP_PORT, CPM_OM_COMM);

    return ;
}


VOS_UINT32 CPM_InitPhyPort(VOS_VOID)
{
    if (VOS_OK != OM_LogFileInit())
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_WARNING, "OM_Init: OM_SDInit failed.\n");
        return VOS_ERR;
    }

    GU_OamPortInit();

    if (VOS_OK != Sock_PortInit())
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : CPM_ComSend
 ��������  : �������ݺ������ṩ���߼�ͨ��ʹ��
 �������  : enLogicPort���߼�ͨ����
             pucData��    �������ݵ�ָ��
             ulLen:       �������ݵĳ���

 �������  : ��
 �� �� ֵ  : VOS_OK:�ɹ�������Ϊʧ��

*****************************************************************************/
VOS_UINT32 CPM_ComSend(CPM_LOGIC_PORT_ENUM_UINT32 enLogicPort, VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    /* ������� */
    if ((CPM_COMM_BUTT <= enLogicPort) || (VOS_NULL_PTR == pucData) || (0 == ulLen))
    {
        return CPM_SEND_PARA_ERR;
    }

    if (VOS_NULL_PTR == CPM_LOGIC_SEND_FUNC(enLogicPort))
    {
        return CPM_SEND_FUNC_NULL;
    }

    return CPM_LOGIC_SEND_FUNC(enLogicPort)(pucData, ulLen);
}

/*****************************************************************************
 �� �� ��  : CPM_ComRcv
 ��������  : �������ݺ������ṩ������ͨ��ʹ��
 �������  : enPhyPort��  ����ͨ����
             pucData��    �������ݵ�ָ��
             ulLen:       �������ݵĳ���
 �������  : ��
 �� �� ֵ  : VOS_OK:�ɹ�������Ϊʧ��

*****************************************************************************/
VOS_UINT32 CPM_ComRcv(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    /* ������� */
    if ((CPM_PORT_BUTT <= enPhyPort) || (VOS_NULL_PTR == pucData) || (0 == ulLen))
    {
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == CPM_PHY_RCV_FUNC(enPhyPort - CPM_APP_PORT))
    {
        LogPrint1("\r\nCPM_ComRcv The Phy Port %d Rec Func is NULL", (VOS_INT)enPhyPort);

        return VOS_ERR;
    }

    return CPM_PHY_RCV_FUNC(enPhyPort - CPM_APP_PORT)(pucData, ulLen);
}

/*****************************************************************************
 �� �� ��  : CPM_Show
 ��������  : ��ʾ��ǰ���߼�������˿ڶ�Ӧ��ϵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

*****************************************************************************/
VOS_VOID CPM_Show(VOS_VOID)
{
    CPM_PHY_PORT_ENUM_UINT32    enPhyPort;
    CPM_LOGIC_PORT_ENUM_UINT32  enLogicPort;

    vos_printf("\r\nCPM_Show The Logic and Phy Relation is :");

    for(enLogicPort=CPM_AT_COMM; enLogicPort<CPM_COMM_BUTT; enLogicPort++)
    {
        enPhyPort = CPM_QueryPhyPort(enLogicPort);

        vos_printf("\r\nThe Logic Port %d is connnect PHY Port %d.", enLogicPort, enPhyPort);
    }

    vos_printf("\r\nCPM_Show The Phy Info is :");

    for(enPhyPort=0; enPhyPort<(CPM_PORT_BUTT - CPM_APP_PORT); enPhyPort++)
    {
        vos_printf("\r\nThe Phy %d Port's Rec Func is 0x%x, Send Func is 0x%x",
                        enPhyPort,
                        g_astCPMPhyPortCfg[enPhyPort].pRcvFunc,
                        g_astCPMPhyPortCfg[enPhyPort].pSendFunc);
    }

    for(enLogicPort=0; enLogicPort<CPM_COMM_BUTT; enLogicPort++)
    {
        vos_printf("\r\nThe Logic %d Port's Rec Func is 0x%x, Send Func is 0x%x",
                        enLogicPort,
                        g_astCPMLogicPortCfg[enLogicPort].pRcvFunc,
                        g_astCPMLogicPortCfg[enLogicPort].pSendFunc);
    }

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
