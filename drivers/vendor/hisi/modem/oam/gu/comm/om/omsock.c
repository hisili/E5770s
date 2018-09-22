

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "omprivate.h"
#include "NVIM_Interface.h"
#include "omrl.h"
#include "omsock.h"
#include "cpm.h"
#if (VOS_WIN32 == VOS_OS_VER)
#include <winsock2.h>
#include <windows.h>
#elif (VOS_VXWORKS == VOS_OS_VER)
#include <sockLib.h>
#endif

#if (VOS_LINUX == VOS_OS_VER)
#include "hisocket.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif



/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_SOCK_C
/*lint +e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*��Ϊ�����������������˿ڵ�socket*/
SOCKET              g_sockListen = SOCK_NULL;

/*���浱ǰ��·�Ļ�����Ϣ*/
COMM_INFO_STRU      g_astCommInfo[SOCKET_NUM_MAX] = {{SOCK_NULL, VOS_NULL_PTR},{SOCK_NULL, VOS_NULL_PTR}};

/*ͬ���ź�����������֤SOCKET������������APP������������*/
VOS_UINT32          g_ulSockTaskSem = VOS_NULL_PTR;

/*�����ź�����������֤SOCKET���͹����в��ܱ��ر�*/
VOS_UINT32          g_ulSockCloseSem = VOS_NULL_PTR;

/*���浱ǰSOCKET��״̬*/
VOS_UINT32          g_ulSockState = SOCK_OK;

/*���浱ǰSOCKET��ʼ��״̬*/
VOS_UINT32          g_ulSockInitState = VOS_FALSE;

/*****************************************************************************
 Prototype      : Sock_IsEnable
 Description    : SOCK�����Ƿ�֧��
 Input          : void
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2012-05-24
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_BOOL Sock_IsEnable(VOS_VOID)
{
#if (VOS_LINUX == VOS_OS_VER)
    OM_CHANNLE_PORT_CFG_STRU    stPortCfg;

    /* ��ȡOM���������ͨ�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        return VOS_FALSE;
    }

    stPortCfg.enPortNum += CPM_APP_PORT;

    /* ������*/
    if (CPM_WIFI_OM_PORT != stPortCfg.enPortNum)
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 Prototype      : Sock_ShutdownAll
 Description    : �ر����е�SOCKET����
 Input          : VOS_VOID

 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        : ---
    Date        : 2008-05-3
    Author      : g47350
    Modification: Created function
 *****************************************************************************/
VOS_VOID Sock_ShutdownAll(VOS_VOID)
{
    VOS_UINT32 ulIndex;

    for (ulIndex = 0; ulIndex < SOCKET_NUM_MAX; ulIndex++)
    {
        if (SOCK_NULL != g_astCommInfo[ulIndex].socket)
        {
            (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);

            closesocket(g_astCommInfo[ulIndex].socket);

            g_astCommInfo[ulIndex].socket = SOCK_NULL;

            VOS_SmV(g_ulSockCloseSem);
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : Sock_Startup
 Description    : �ṩ��APP���ã���������SOCKET����
 Input          : VOS_VOID

 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        : ---
    Date        : 2008-05-3
    Author      : g47350
    Modification: Created function
 *****************************************************************************/
VOS_VOID Sock_Startup(VOS_VOID)
{
    if (VOS_NULL_PTR == g_ulSockTaskSem)
    {
        return;
    }

    if (VOS_OK != VOS_SmV(g_ulSockTaskSem))
    {
        g_ulSockState = SOCK_V_SEM;
    }

    return;
}

/*****************************************************************************
 Prototype      : Sock_JudgeCommType
 Description    : ͨ����һ�����ݰ������ݣ��ж���OM��·������AT��·
 Input          : pData        - ָ�����ݰ����ݵ�ָ��.
                  uslength     - ָ�����ݰ����ݵĳ���.
 Output         : void
 Return Value   : 1 ΪAT��·
                  0 ΪOM��·

 History        : ---
    Date        : 2008-05-3
    Author      : g47350
    Modification: Created function
 *****************************************************************************/
VOS_UINT32 Sock_JudgeCommType(VOS_UINT8* pucData, VOS_UINT16 uslength)
{
    if (0 == VOS_MemCmp(pucData, "AT\r", uslength))
    {
        /*AT*/
        return 1;
    }

    /*OM*/
    return 0;
}

/*****************************************************************************
 Prototype      : Sock_Init
 Description    : ��ʼ��Socket��������
 Input          : VOS_VOID
 Output         : void
 Return Value   : VOS_TRUE :��ʼ���ɹ�
                  VOS_FALSE:��ʼ��ʧ��

 History        : ---
    Date        : 2008-05-3
    Author      : g47350
    Modification: Created function
 *****************************************************************************/
VOS_BOOL Sock_Init(VOS_VOID)
{
    struct sockaddr_in  sAddr;
    VOS_INT             lAddLen;

#if (VOS_WIN32 == VOS_OS_VER)
    WORD wVersionRequested;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD(2, 2);
    WSAStartup(wVersionRequested, &wsaData);
#endif

    g_sockListen = socket(AF_INET, SOCK_STREAM, 0);

#if (VOS_LINUX == VOS_OS_VER)
    if (VOS_OK > g_sockListen)
#else
    if (INVALID_SOCKET == g_sockListen)
#endif
    {
        g_ulSockState = SOCK_INIT_ERR;

        closesocket(g_sockListen);

        return VOS_FALSE;
    }

    VOS_MemSet(&sAddr, 0, sizeof(sAddr));
    sAddr.sin_family = AF_INET;

    sAddr.sin_addr.s_addr = 0;

    /*�����Ķ˿ں�Ϊ3000*/
    sAddr.sin_port = htons(SOCK_PORT_NUM);

    lAddLen = sizeof(struct sockaddr_in);

    /*������Socket�󶨵���Ӧ�Ķ˿���*/
    if (SOCKET_ERROR == bind(g_sockListen, (struct sockaddr *)&sAddr, lAddLen))
    {
        g_ulSockState = SOCK_BIND_ERR;

        closesocket(g_sockListen);

        return VOS_FALSE;
    }

    /*���÷������˼��������ͻ�����*/
    if (SOCKET_ERROR == listen(g_sockListen, SOCKET_NUM_MAX))
    {
        g_ulSockState = SOCK_LISTEN_ERR;

        closesocket(g_sockListen);

        return VOS_FALSE;
    }

    /* ����SOCKET�����ź��� */
    if(VOS_OK != VOS_SmMCreate("SOCK", VOS_SEMA4_FIFO, &g_ulSockCloseSem))
    {
        closesocket(g_sockListen);
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Prototype      : Sock_ServerProc
 Description    : �������̣߳���������������˺Ϳͻ��˵���������
 Input          : lpParameter - Unused.
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2008-05-3
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_VOID Sock_ServerProc(VOS_VOID)
{
    VOS_INT8    acRcvBuf[OM_APP_SPLIT_MSG_LEN];
    Ip_fd_set   allfds;
    Ip_fd_set   readfds;
    VOS_INT     lRet = 0;
    VOS_INT     lIndex = 0;
    VOS_INT     lRevSize = 0;
    SOCKET      sockUnknown = SOCK_NULL;
    VOS_UINT32  ulFlag;

    SOCK_FD_ZERO(&allfds);
    SOCK_FD_ZERO(&readfds);
    SOCK_FD_SET(g_sockListen, &allfds);
    SOCK_FD_SET(g_sockListen, &readfds);

    for(;;)
    {
        ulFlag = VOS_FALSE;

        /*������������socket����Ϣ*/
        lRet = select(__FD_SETSIZE, &readfds, 0, 0, 0);

    #if (VOS_LINUX == VOS_OS_VER)
        if ( 0 > lRet )
    #else
        if ( (SOCKET_ERROR == lRet) || (0 == lRet) )
    #endif
        {
            g_ulSockState = SOCK_SELECT_ERR;

            return;
        }

        /*�жϴ������Ƿ����ڼ���Socket.*/
        if (0 != SOCK_FD_ISSET(g_sockListen, &readfds))
        {
            ulFlag = VOS_TRUE;

            /*��һ���ͻ��������Ϸ�������������·������δ��*/
            sockUnknown = accept(g_sockListen, NULL, 0);

        #if (VOS_LINUX == VOS_OS_VER)
            if (0 > sockUnknown)
        #else
            if (SOCKET_ERROR == sockUnknown)
        #endif
            {
                sockUnknown   = SOCK_NULL;
                g_ulSockState = SOCK_ACCEPT_ERR;

                continue;
            }

            SOCK_FD_SET(sockUnknown, &allfds);
        }

        /*���Կͻ���socket����Ϣ*/
        for (lIndex = 0; lIndex < SOCKET_NUM_MAX; lIndex++)
        {
            /*���յ�����PC�Ĺ��ߵ�����*/
            if (0 != SOCK_FD_ISSET(g_astCommInfo[lIndex].socket, &readfds))
            {
                ulFlag = VOS_TRUE;
                lRevSize = recv(g_astCommInfo[lIndex].socket, acRcvBuf, OM_APP_SPLIT_MSG_LEN, 0);

                /*�ͻ����Ѿ��رգ���Ҫ���������*/
            #if (VOS_LINUX == VOS_OS_VER)
                if (0 >= lRevSize)
            #else
                if ((SOCKET_ERROR == lRevSize) || (0 == lRevSize))
            #endif
                {
                    SOCK_FD_CLR(g_astCommInfo[lIndex].socket, &allfds);
                    (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);
                    closesocket(g_astCommInfo[lIndex].socket);
                    g_astCommInfo[lIndex].socket = SOCK_NULL;
                    VOS_SmV(g_ulSockCloseSem);

                    continue;
                }

                /*�����յ��������ύ���ϲ㴦��*/
                CPM_ComRcv((lIndex + CPM_WIFI_OM_PORT), acRcvBuf, lRevSize);
            }
        }

        /*ȷ����·������*/
        if (0 != SOCK_FD_ISSET(sockUnknown, &readfds))
        {
            ulFlag = VOS_TRUE;

            lRevSize = recv(sockUnknown, acRcvBuf, OM_APP_SPLIT_MSG_LEN, 0);

            /*�ͻ����Ѿ��رգ���Ҫ���������*/
        #if (VOS_LINUX == VOS_OS_VER)
            if (0 >= lRevSize)
        #else
            if ((SOCKET_ERROR == lRevSize) || (0 == lRevSize))
        #endif
            {
                SOCK_FD_CLR(sockUnknown, &allfds);
                (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);
                closesocket(sockUnknown);
                VOS_SmV(g_ulSockCloseSem);
            }
            else
            {
                /*�жϵ�ǰ��·������*/
                lIndex = (VOS_INT)Sock_JudgeCommType(acRcvBuf, (VOS_UINT16)lRevSize);

                if (SOCK_NULL == g_astCommInfo[lIndex].socket)
                {
                    g_astCommInfo[lIndex].socket = sockUnknown;

                    /*���������Կͻ��˵����ݽ����ϲ�Ӧ��*/
                    CPM_ComRcv((lIndex + CPM_WIFI_OM_PORT), acRcvBuf, lRevSize);
                }
                else
                {
                    SOCK_FD_CLR(sockUnknown, &allfds);
                    (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);
                    closesocket(sockUnknown);
                    VOS_SmV(g_ulSockCloseSem);

                    LogPrint("Sock_ServerProc: The Current Link Is Existent!\r\n");
                }
            }

            sockUnknown = SOCK_NULL;
        }

        if ( VOS_FALSE == ulFlag )/* �д��������ָ�set */
        {
            Sock_ShutdownAll();

            SOCK_FD_ZERO(&allfds);
            SOCK_FD_SET(g_sockListen, &allfds);
        }

        VOS_MemCpy(&readfds, &allfds, sizeof(Ip_fd_set));
    }
}

/*****************************************************************************
 Prototype      : Sock_ServerTask
 Description    : �������̣߳���������������˺Ϳͻ��˵���������
 Input          : lpParameter - Unused.
 Output         : void
 Return Value   : void

 History        : ---
    Date        : 2008-05-3
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_VOID Sock_ServerTask(VOS_VOID)
{
#if (VOS_VXWORKS == VOS_OS_VER)

    /*���統ǰû������ΪWIFIģʽ,��ǿ���˳�*/
    /*if (OMRL_WIFI != g_RlSndLinkType)
    {
        g_ulSockState = SOCK_NO_START;

        return;
    }*/



    /*����ͬ���ź���������֤��Ӧ��֮������*/
    if ( VOS_OK != VOS_SmBCreate( "Sock", 0, VOS_SEMA4_FIFO, &g_ulSockTaskSem))
    {
        g_ulSockState = SOCK_INIT_SEM_ERR;

        return;
    }

    if(VOS_OK != VOS_SmP(g_ulSockTaskSem, 0))
    {
        g_ulSockState = SOCK_P_SEM;

        return;
    }
#endif

    /*��ʼ��SOCKET*/
    if (VOS_FALSE == Sock_Init())
    {
        return;
    }

    g_ulSockState = SOCK_START;
    g_ulSockInitState   = VOS_TRUE;

    Sock_ServerProc();

    return;
}


VOS_INT32 Sock_OMComSend(VOS_UINT8* pucData, VOS_UINT16 uslength)
{
    SOCKET socket;
    VOS_INT nSndNum;

    if (VOS_FALSE == g_ulSockInitState)
    {
        return VOS_ERR;
    }

    (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);

    socket = g_astCommInfo[SOCKET_OM].socket;

    if (SOCK_NULL == socket)
    {
        VOS_SmV(g_ulSockCloseSem);

        return VOS_ERR;
    }

    /*����send������ͨ��socket���ͳ�ȥ*/
    nSndNum = send(socket, pucData, uslength, 0);

    VOS_SmV(g_ulSockCloseSem);

    if (nSndNum != uslength)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_INT32 Sock_ATComSend(VOS_UINT8* pucData, VOS_UINT16 uslength)
{
    SOCKET socket;
    VOS_INT nSndNum;

    if (VOS_FALSE == g_ulSockInitState)
    {
        return VOS_ERR;
    }

    (VOS_VOID)VOS_SmP(g_ulSockCloseSem, 0);

    socket = g_astCommInfo[SOCKET_AT].socket;

    if (SOCK_NULL == socket)
    {
        VOS_SmV(g_ulSockCloseSem);

        return VOS_ERR;
    }

    /*����send������ͨ��socket���ͳ�ȥ*/
    nSndNum = send(socket, pucData, uslength, 0);

    VOS_SmV(g_ulSockCloseSem);

    if (nSndNum != uslength)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 Sock_PortInit(VOS_VOID)
{
    if((BSP_MODULE_SUPPORT == DRV_GET_WIFI_SUPPORT())
                && (VOS_TRUE == Sock_IsEnable()))
    {
        CPM_PhySendReg(CPM_WIFI_OM_PORT,  (CPM_FUNC)Sock_OMComSend);
        CPM_PhySendReg(CPM_WIFI_AT_PORT,  (CPM_FUNC)Sock_ATComSend);
    }

    return VOS_OK;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
