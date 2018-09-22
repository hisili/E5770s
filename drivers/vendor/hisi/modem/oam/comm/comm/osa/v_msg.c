/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: v_msg.c                                                         */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement message function                                   */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
/*                                                                           */
/*****************************************************************************/

/*lint --e{537,527,661,831,713}*/

#include "v_msg.h"
#include "v_blkMem.h"
#include "v_queue.h"
#include "vos_Id.h"
#include "v_timer.h"
#include "v_iddef.h"
#include "DrvInterface.h"

 /* LINUX ��֧�� */
#if (VOS_VXWORKS== VOS_OS_VER)
#include "stdio.h"
#endif
#if (FEATURE_ON == MBB_WPG_COMMON)
#if defined (__KERNEL__)
#include <linux/wakelock.h>
#include <linux/jiffies.h>
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_V_MSG_C
/*lint +e767 modify:x51137; review:h59254; */


#ifndef OM_DEBUG
extern VOS_MSG_HOOK_FUNC                vos_MsgHook;
#endif

#define MSG_SEND_SIZE    ( sizeof(VOS_UINT32) )

#if (VOS_DEBUG == VOS_DOPRA_VER)

MEMORY_HOOK_FUNC  g_pfnAllocMsgHook = VOS_NULL_PTR;
MEMORY_HOOK_FUNC  g_pfnFreeMsgHook = VOS_NULL_PTR;

#endif

typedef struct
{
    VOS_UINT32 ulQid;
    VOS_UINT32 ulSendPid;
    VOS_UINT32 ulRcvPid;
    VOS_UINT32 ulMsgName;
}VOS_DUMP_MSG_STRU;

/* dump msg info */
#define     DUMP_MSG_INFO_LEN      1024
VOS_CHAR    g_aucDumpMsgInfo[DUMP_MSG_INFO_LEN];

#ifdef VOS_OSA_SINGLE_ARM

VOS_SENDMSG_FUNCLIST_ST g_astVOSSendMsgProcTable[VOS_SUPPORT_CPU_NUM_MAX]={
                                                    {VOS_CPU_ID_1_PID_BUTT, V_SendLocalMsg,V_SendLocalUrgentMsg},/* Send Local Msg */
                                                    {VOS_CPU_ID_1_PID_BUTT, V_SendLocalMsg,V_SendLocalUrgentMsg},/* Send Local Msg */
                                                    {VOS_CPU_ID_1_PID_BUTT, V_SendLocalMsg,V_SendLocalUrgentMsg},/* Send Msg to DSP */
                                                    {VOS_CPU_ID_1_PID_BUTT, V_SendLocalMsg,V_SendLocalUrgentMsg},/* Send Msg to HIFI */
                                                    {VOS_CPU_ID_1_PID_BUTT, V_SendLocalMsg,V_SendLocalUrgentMsg}};/* Send Msg to MCU */
#else

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
VOS_SENDMSG_FUNCLIST_ST g_astVOSSendMsgProcTable[VOS_SUPPORT_CPU_NUM_MAX]={
                            {VOS_CPU_ID_0_PID_BUTT, V_SendLocalMsg,     V_SendLocalUrgentMsg},  /* Send Local Msg */
                            {VOS_CPU_ID_1_PID_BUTT, V_SendMsgByICC,     V_SendMsgByICC},        /* Send Msg to Other ARM */
                            {VOS_CPU_ID_2_PID_BUTT, VOS_NULL_PTR,       VOS_NULL_PTR},          /* Send Msg to DSP */
                            {VOS_CPU_ID_3_PID_BUTT, VOS_SendHIFIMsg,    VOS_SendHIFIUrgentMsg}, /* Send Msg to HIFI */
                            {VOS_CPU_ID_4_PID_BUTT, VOS_SendMCUMsg,     VOS_SendMCUUrgentMsg}}; /* Send Msg to MCU */
#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
VOS_SENDMSG_FUNCLIST_ST g_astVOSSendMsgProcTable[VOS_SUPPORT_CPU_NUM_MAX]={
                            {VOS_CPU_ID_0_PID_BUTT, V_SendMsgByICC,     V_SendMsgByICC},        /*Send Msg to Other ARM*/
                            {VOS_CPU_ID_1_PID_BUTT, V_SendLocalMsg,     V_SendLocalUrgentMsg},  /*Send Local Msg*/
                            {VOS_CPU_ID_2_PID_BUTT, VOS_NULL_PTR,       VOS_NULL_PTR},          /*Send Msg to ZSP, RSV*/
                            {VOS_CPU_ID_3_PID_BUTT, VOS_SendHIFIMsg,    VOS_SendHIFIUrgentMsg}, /*Send Msg to HIFI*/
                            {VOS_CPU_ID_4_PID_BUTT, VOS_SendMCUMsg,     VOS_SendMCUUrgentMsg}}; /*Send Msg to MCU*/
#endif

#endif

enum
{
    VOS_HIFI_TO_ACPU_VOS_MSG_NORMAL,
    VOS_MCU_TO_ACPU_VOS_MSG_NORMAL,
    VOS_HIFI_TO_CCPU_VOS_MSG_NORMAL,
    VOS_MAIL_BOX_MSG_NORMAL_BUTT,
    VOS_HIFI_TO_ACPU_VOS_MSG_URGENT,
    VOS_MCU_TO_ACPU_VOS_MSG_URGENT,
    VOS_HIFI_TO_CCPU_VOS_MSG_URGENT
};

UDI_HANDLE      g_OSAIccUDIHandle = (-1);

/* DSP���ƺ��ṩǿ�ƻ��ѹ��� */
Msg_Fun_Type    g_pfnVosAwakeFunHook = VOS_NULL_PTR;


/* ��Ʒ�Ƿ�֧��HIFI��0 - ��֧�� */
VOS_INT32 g_HifiStatus = 0;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
VOS_UINT32 g_msglpm = 0;

signed int VOS_MsgLpmCb(int x)
{
    g_msglpm = 1;
	return 0;
}
#endif

/*****************************************************************************
 Function   : VOS_RegisterAwakeFun
 Description: register awake fun to OSA
 Input      : hook fun
 Return     : ok or error
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_RegisterAwakeFun(Msg_Fun_Type pfnHook)
{
#ifndef VOS_OSA_SINGLE_ARM

#if (OSA_CPU_CCPU != VOS_OSA_CPU)
    return VOS_ERR;
#endif

#endif

    /* coverity[unreachable] */
    g_pfnVosAwakeFunHook = pfnHook; /* [false alarm]: ����Fortify���� */

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_ExecuteAwakeFun
 Description: Call Awake fun
 Input      : msg
 Return     : none
 Other      :
 *****************************************************************************/
VOS_VOID VOS_ExecuteAwakeFun(MsgBlock *pstMsgCtrlBlk)
{
#ifndef VOS_OSA_SINGLE_ARM

#if (OSA_CPU_CCPU != VOS_OSA_CPU)
    return;
#endif

#endif

#if (VOS_VXWORKS == VOS_OS_VER)
    /*if ( VOS_TRUE == DRV_INT_GET_CONTEXT() )
    {
        return;
    }*/
#endif

    /* coverity[unreachable] */
    if ( VOS_NULL_PTR == g_pfnVosAwakeFunHook ) /* [false alarm]: ����Fortify���� */
    {
        return;
    }

    (g_pfnVosAwakeFunHook)(pstMsgCtrlBlk); /* [false alarm]: ����Fortify���� */

    return;
}

/* Modified by c64416 for hifi mailbox, 2013/09/24, begin */

/*****************************************************************************
 Function   : VOS_DRVMB_OSAMsg_CB
 Description: DRV MB dallback func, read Msg data from MB, and then send it to receiver.
 Input      : ulChannelId  -- Mile box channel id
              pucbuffer -- the pointer of message
              ulLen     -- Msg data length
 Return     : NA
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_VOID VOS_DRVMB_OSAMsg_CB(VOS_VOID *pUserPara, VOS_VOID *pMailHandle, VOS_UINT32 ulLen)
{
    VOS_UINT8                          *pucMsgData;
    MsgBlock                           *pstMsgCtrlBlk;
    VOS_UINT32                         ulMailboxLen = ulLen;
    VOS_UINT32                         ulMailCode;

    if(0 == g_HifiStatus)
    {
        return ;
    }

    if (ulLen <= VOS_MSG_HEAD_LENGTH)
    {
        LogPrint("\n VOS_DRVMB_OSAMsg_CB: The Data Len is small.\n");

        VOS_SetErrorNo(VOS_ERRNO_MSG_MB_DATALENISNULL);

        DRV_SYSTEM_ERROR(VOS_ERRNO_MSG_MB_DATALENISNULL, (VOS_INT)ulLen, (VOS_INT)pUserPara,
                            VOS_NULL_PTR, 0);

        return ;
    }

    /* Alloc message space with static PID number */
    pucMsgData = (VOS_UINT8*)VOS_AllocMsg( VOS_PID_DOPRAEND, (VOS_UINT32)(ulLen-VOS_MSG_HEAD_LENGTH) );

    if ( VOS_NULL_PTR == pucMsgData )
    {
        LogPrint("\n VOS_DRVMB_OSAMsg_CB: Alloc Msg memory failed.\n");

        return ;
    }

    DRV_MAILBOX_READMAILDATA(pMailHandle, pucMsgData, &ulMailboxLen);

    /* get the Message ctrl data from the MB channel */
    pstMsgCtrlBlk = (MsgBlock*)(pucMsgData);

    VOS_ModifyMsgInfo((VOS_VOID *)pstMsgCtrlBlk, pstMsgCtrlBlk->ulSenderPid);

    ulMailCode = (VOS_UINT32)pUserPara;

    if ( VOS_MAIL_BOX_MSG_NORMAL_BUTT < ulMailCode )/*urgend msg*/
    {
        (VOS_VOID)V_SendUrgentMsg(VOS_PID_DOPRAEND, (VOS_VOID**)(&(pucMsgData)), VOS_FILE_ID, (VOS_INT32)(VOS_MSG_HEAD_FLAG + ulMailCode) );
    }
    else
    {
        (VOS_VOID)V_SendMsg(VOS_PID_DOPRAEND, (VOS_VOID**)(&(pucMsgData)), VOS_FILE_ID, (VOS_INT32)(VOS_MSG_HEAD_FLAG + ulMailCode) );
    }

    return ;
}

/*****************************************************************************
 Function   : VOS_DRVMB_Init
 Description: Init the DRV's mailebox channle.
 Input      : void
 Return     : VOS_OK / VOS_ERR
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 VOS_DRVMB_Init(VOS_VOID)
{

    g_HifiStatus = DRV_GET_CODEC_FUNC_STATUS();

    if(0 == g_HifiStatus)
    {
        return VOS_OK;
    }

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    /* Register HIFI->ACPU OSA normal Msg CallBack */
    if (VOS_OK != DRV_MAILBOX_REGISTERRECVFUNC(MAILBOX_MAILCODE_HIFI_TO_ACPU_VOS_MSG_NORMAL,
                                VOS_DRVMB_OSAMsg_CB,
                                (VOS_VOID *)VOS_HIFI_TO_ACPU_VOS_MSG_NORMAL))
    {
        LogPrint("\n VOS_DRVMB_Init: Register HIFI->ACPU Normal CB failed.\n");
        return VOS_ERR;
    }

    /* Register HIFI->ACPU OSA urgent Msg CallBack */
    if (VOS_OK != DRV_MAILBOX_REGISTERRECVFUNC(MAILBOX_MAILCODE_HIFI_TO_ACPU_VOS_MSG_URGENT,
                                VOS_DRVMB_OSAMsg_CB,
                                (VOS_VOID *)VOS_HIFI_TO_ACPU_VOS_MSG_URGENT))
    {
        LogPrint("\n VOS_DRVMB_Init: Register HIFI->ACPU Urgent CB failed.\n");
        return VOS_ERR;
    }
#if 0
    /* Register MCU->ACPU OSA normal Msg CallBack */
    if (VOS_OK != DRV_MAILBOX_REGISTERRECVFUNC(MAILBOX_MAILCODE_MCU_TO_ACPU_VOS_MSG_NORMAL,
                                VOS_DRVMB_OSAMsg_CB,
                                (VOS_VOID *)VOS_MCU_TO_ACPU_VOS_MSG_NORMAL))
    {
        LogPrint("\n VOS_DRVMB_Init: Register MCU->ACPU Normal CB failed.\n");
        return VOS_ERR;
    }

    /* Register MCU->ACPU OSA urgent Msg CallBack */
    if (VOS_OK != DRV_MAILBOX_REGISTERRECVFUNC(MAILBOX_MAILCODE_MCU_TO_ACPU_VOS_MSG_URGENT,
                                VOS_DRVMB_OSAMsg_CB,
                                (VOS_VOID *)VOS_MCU_TO_ACPU_VOS_MSG_URGENT))
    {
        LogPrint("\n VOS_DRVMB_Init: Register MCU->ACPU Urgent CB failed.\n");
        return VOS_ERR;
    }
#endif
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    /* Register HIFI->CCPU OSA Msg CallBack */
    if (VOS_OK != DRV_MAILBOX_REGISTERRECVFUNC(MAILBOX_MAILCODE_HIFI_TO_CCPU_VOS_MSG_NORMAL,
                                VOS_DRVMB_OSAMsg_CB,
                                (VOS_VOID *)VOS_HIFI_TO_CCPU_VOS_MSG_NORMAL))
    {
        LogPrint("\n VOS_DRVMB_Init: Register HIFI->CCPU Normal CB failed.\n");
        return VOS_ERR;
    }

    /* Register HIFI->CCPU OSA Msg CallBack */
    if (VOS_OK != DRV_MAILBOX_REGISTERRECVFUNC(MAILBOX_MAILCODE_HIFI_TO_CCPU_VOS_MSG_URGENT,
                                VOS_DRVMB_OSAMsg_CB,
                                (VOS_VOID *)VOS_HIFI_TO_CCPU_VOS_MSG_URGENT))
    {
        LogPrint("\n VOS_DRVMB_Init: Register HIFI->CCPU Urgent CB failed.\n");
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_SendMsgByDrvMB
 Description: Send the msg to another ARM's OSA by the DRV's mailebox channle.
 Input      : Pid        -- process identifier
              pMsg       -- the pointer of message
              pstMsgPara -- the Msg parameter
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 VOS_SendMsgByDrvMB(VOS_PID                 Pid,
                              VOS_VOID                **ppMsg,
                              VOS_DRVMB_MSG_PARA_STRU *pstMsgPara)
{
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulResult;
    MsgBlock                           *pstMsgCtrlBlk;

    if(0 == g_HifiStatus)
    {
        VOS_FreeMsg(Pid, *ppMsg ); /* need free the Msg memory */
        return VOS_OK;
    }

    pstMsgCtrlBlk = (MsgBlock*)(*ppMsg);

    if ( DOPRA_PID_TIMER == pstMsgCtrlBlk->ulSenderPid )
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_MB_PIDTERROR);

        LogPrint1("\n# VOS_SendMsgByDrvMB Error Timer Sender MB Msg, Rec PID %d\n", (VOS_INT)pstMsgCtrlBlk->ulReceiverPid);

        DRV_SYSTEM_ERROR(VOS_ERRNO_MSG_MB_PIDTERROR, pstMsgPara->ulFileID, pstMsgPara->lLineNo,
                            (VOS_CHAR*)pstMsgPara, sizeof(VOS_DRVMB_MSG_PARA_STRU));

        return(VOS_ERRNO_MSG_MB_PIDTERROR);
    }

    /* Get the Msg Length */
    ulDataLen   = pstMsgCtrlBlk->ulLength + VOS_MSG_HEAD_LENGTH;

    ulResult     = DRV_MAILBOX_SENDMAIL(pstMsgPara->ulMailBoxCode,
                                        *ppMsg,
                                        ulDataLen );

    VOS_FreeMsg(Pid, *ppMsg ); /* need free the Msg memory */

    /* ����HIFI��λ��д mailboxͨ��ʧ�ܻ᷵��һ������ֵ�����ܸ�λ���� */
    if (MAILBOX_TARGET_NOT_READY == ulResult )
    {
        LogPrint3("\n# VOS_SendMsgByDrvMB Error,HIFI Reset, File  %d. line %d. Size %d.\n",
                    (VOS_INT)pstMsgPara->ulFileID, pstMsgPara->lLineNo,ulDataLen);

        return VOS_ERRNO_MSG_MAILBOX_RESET;
    }

    if ( MAILBOX_OK != ulResult ) /* Send Data to mail box channle error */
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_MB_SENDERROR);

        LogPrint4("\n# VOS_SendMsgByDrvMB Error,Write DRV MB Error, File  %d. line %d. Size %d result %d.\n",
                    (VOS_INT)pstMsgPara->ulFileID, pstMsgPara->lLineNo,ulDataLen,ulResult);

        DRV_SYSTEM_ERROR(VOS_ERRNO_MSG_MB_SENDERROR, (VOS_INT)ulResult, 0,
                        (VOS_CHAR*)pstMsgPara, sizeof(VOS_DRVMB_MSG_PARA_STRU));

        return(VOS_ERRNO_MSG_MB_SENDERROR);
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_SendHIFIMsg
 Description: Send the msg to HIFI's OSA by the DRV's mailebox channle.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/

VOS_UINT32 VOS_SendHIFIMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                           VOS_UINT32 ulFileID, VOS_INT32 lLineNo)
{
    VOS_DRVMB_MSG_PARA_STRU             stMsgPara;

    stMsgPara.lLineNo       = lLineNo;
    stMsgPara.ulFileID      = ulFileID;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_ACPU_TO_HIFI_VOS_MSG_NORMAL;
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_CCPU_TO_HIFI_VOS_MSG_NORMAL;
#endif

    return VOS_SendMsgByDrvMB(Pid, ppMsg, &stMsgPara);
}

/*****************************************************************************
 Function   : VOS_SendHIFIUrgentMsg
 Description: Send the urgent msg to HIFI's OSA by the DRV's mailebox channle.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/

VOS_UINT32 VOS_SendHIFIUrgentMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                                 VOS_UINT32 ulFileID, VOS_INT32 lLineNo)
{
    VOS_DRVMB_MSG_PARA_STRU             stMsgPara;

    stMsgPara.lLineNo       = lLineNo;
    stMsgPara.ulFileID      = ulFileID;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_ACPU_TO_HIFI_VOS_MSG_URGENT;
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_CCPU_TO_HIFI_VOS_MSG_URGENT;
#endif

    return VOS_SendMsgByDrvMB(Pid, ppMsg, &stMsgPara);
}


/*****************************************************************************
 Function   : VOS_SendMCUMsg
 Description: Send the msg to MCU's OSA by the DRV's mailebox channle.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 VOS_SendMCUMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                           VOS_UINT32 ulFileID, VOS_INT32 lLineNo)
{
    VOS_FreeMsg(Pid, *ppMsg );
    return 0;
#if 0
    VOS_DRVMB_MSG_PARA_STRU             stMsgPara;

    stMsgPara.lLineNo       = lLineNo;
    stMsgPara.ulFileID      = ulFileID;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_ACPU_TO_MCU_VOS_MSG_NORMAL;
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_CCPU_TO_MCU_VOS_MSG_NORMAL;
#endif

    return VOS_SendMsgByDrvMB(Pid, ppMsg, &stMsgPara);
#endif
}

/*****************************************************************************
 Function   : VOS_SendMCUUrgentMsg
 Description: Send the urgent msg to MCU's OSA by the DRV's mailebox channle.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/

VOS_UINT32 VOS_SendMCUUrgentMsg( VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo )
{
    VOS_FreeMsg(Pid, *ppMsg );
    return 0;
#if 0
    VOS_DRVMB_MSG_PARA_STRU             stMsgPara;

    stMsgPara.lLineNo       = lLineNo;
    stMsgPara.ulFileID      = ulFileID;

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_ACPU_TO_MCU_VOS_MSG_URGENT;
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_CCPU_TO_MCU_VOS_MSG_URGENT;
#endif

    return VOS_SendMsgByDrvMB(Pid, ppMsg, &stMsgPara);
#endif
}

/* Modified by c64416 for hifi mailbox, 2013/09/24, end */

/*****************************************************************************
 Function   : V_AllocMsg
 Description: allocates messages block
 Input      : Pid      -- process identifier
              ulLength -- the length of message
 Return     : The pointer of message on success or VOS_NULL_PTR on failure
 Other      : The pointer of message that returned for application is not the
              actual pointer of message which system used
 *****************************************************************************/
MsgBlock * V_AllocMsg(VOS_PID Pid, VOS_UINT32 ulLength,
                       VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_INT         ulTotalLength;
    MSG_BLOCK_HEAD  *pMsgBlkHead;
    MsgBlock        *MsgBlock_Ptr;

#if (VOS_YES == VOS_CHECK_PARA)
    if(Pid >= VOS_PID_BUTT)
    {
        return((MsgBlock*)VOS_NULL_PTR);
    }

    if( 0 == ulLength )
    {
        return((MsgBlock*)VOS_NULL_PTR);
    }
#endif

    ulTotalLength =
        (VOS_INT)(VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH + ulLength);

    pMsgBlkHead = (MSG_BLOCK_HEAD*)VOS_MemBlkMalloc(Pid, ulTotalLength,
        ulFileID, usLineNo);
    if( VOS_NULL_PTR == pMsgBlkHead )
    {
        return((MsgBlock*)VOS_NULL_PTR);
    }

    pMsgBlkHead->ulFlag = VOS_MSG_HEAD_FLAG;

    MsgBlock_Ptr = (MsgBlock*)( (VOS_UINT32)pMsgBlkHead
                        + VOS_MSG_BLK_HEAD_LEN );
    MsgBlock_Ptr->ulSenderCpuId = VOS_LOCAL_CPUID;
    MsgBlock_Ptr->ulSenderPid   = Pid;
    MsgBlock_Ptr->ulReceiverCpuId = VOS_LOCAL_CPUID;
    MsgBlock_Ptr->ulLength = (VOS_UINT32)ulLength;

#if (VOS_DEBUG == VOS_DOPRA_VER)

    if ( VOS_NULL_PTR != g_pfnAllocMsgHook )
    {
        g_pfnAllocMsgHook((VOS_UINT32)ulTotalLength);
    }

#endif

    return MsgBlock_Ptr;
}

/*****************************************************************************
 Function   : VOS_AllocTimerMsg
 Description: allocates timer messages block
 Input      : Pid      -- process identifier
              ulLength -- the length of message
 Return     : The pointer of message on success or VOS_NULL_PTR on failure
 Other      :
 *****************************************************************************/
MsgBlock * VOS_AllocTimerMsg(VOS_PID Pid, VOS_UINT32 ulLength )
{
    VOS_UINT32      ulTotalLength;
    MSG_BLOCK_HEAD  *pMsgBlkHead;
    MsgBlock        *MsgBlock_Ptr;


    if(Pid >= VOS_PID_BUTT)
    {
        LogPrint("# Alloc Timer msg Pid too big.\r\n");
        return((MsgBlock*)VOS_NULL_PTR);
    }

    if(0 == ulLength)
    {
        return((MsgBlock*)VOS_NULL_PTR);
    }

    ulTotalLength = VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH + ulLength;

    pMsgBlkHead = (MSG_BLOCK_HEAD*)VOS_TIMER_MemCtrlBlkMalloc( Pid,
        (VOS_INT)ulTotalLength );
    if( VOS_NULL_PTR == pMsgBlkHead )
    {
        return((MsgBlock*)VOS_NULL_PTR);
    }

    pMsgBlkHead->ulFlag     = VOS_MSG_HEAD_FLAG;

    MsgBlock_Ptr = (MsgBlock*)( (VOS_UINT32)pMsgBlkHead
                        + VOS_MSG_BLK_HEAD_LEN );

    MsgBlock_Ptr->ulSenderCpuId   = VOS_LOCAL_CPUID;
    MsgBlock_Ptr->ulSenderPid     = DOPRA_PID_TIMER;
    MsgBlock_Ptr->ulReceiverCpuId = VOS_LOCAL_CPUID;
    MsgBlock_Ptr->ulReceiverPid   = Pid;
    MsgBlock_Ptr->ulLength        = ulLength;

    return MsgBlock_Ptr;
}

/*****************************************************************************
 Function   : V_FreeMsg
 Description: Free a message which status must be ALLOCATED
 Input      : Pid  -- PID who free the message
              pMsg -- Pointer of the message to be freed
 Return     : VOS_OK on success or error number on failure
 Other      : This function was only called to free a message which was
              allocated by VOS_AllocMsg but not been send.
 *****************************************************************************/
VOS_UINT32 V_FreeMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_VOID            *pMsgBlkHead;
    MSG_BLOCK_HEAD      *pstMSG;
    VOS_UINT32          ulBlockAdd;
    VOS_UINT32          ulCtrlkAdd;

#if ( VOS_YES == VOS_CHECK_PARA)
    if(Pid >= VOS_PID_BUTT)
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTMSGISNULL);
        return(VOS_ERRNO_MSG_FREE_INPUTMSGISNULL);
    }

    if( VOS_NULL_PTR == ppMsg )
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    if( VOS_NULL_PTR == *ppMsg )
    {
        LogPrint3("# V_FreeMsg,free msg again.F %d L %d T %d.\r\n",
            (VOS_INT)ulFileID, usLineNo, (VOS_INT)VOS_GetTick() );

        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }
#endif

    pMsgBlkHead = (VOS_VOID*)( (VOS_UINT32)(*ppMsg)
                         - VOS_MSG_BLK_HEAD_LEN );

    if ( VOS_OK != VOS_MemCheck( pMsgBlkHead, &ulBlockAdd, &ulCtrlkAdd,
        ulFileID, usLineNo ) )
    {
        return VOS_ERR;
    }

    pstMSG = (MSG_BLOCK_HEAD *)pMsgBlkHead;
    if ( VOS_MSG_RESERVED_HEAD_FLAG == pstMSG->ulFlag )
    {
        return VOS_OK;
    }
    else
    {
        /* Clear user's pointer */
        *ppMsg = VOS_NULL_PTR;

#if (VOS_DEBUG == VOS_DOPRA_VER)

        if ( VOS_NULL_PTR != g_pfnFreeMsgHook )
        {
            g_pfnFreeMsgHook(0);
        }
#endif

        return VOS_MemCtrlBlkFree( (VOS_MEM_CTRL_BLOCK *)ulCtrlkAdd,
            (VOS_MEM_HEAD_BLOCK *)ulBlockAdd, ulFileID, usLineNo );
    }
}

/*****************************************************************************
 Function   : V_ReserveMsg
 Description: In msg proceed function, reserve a message
 Input      : pMsg     -- the pointer of application message (MsgBlock)
              Pid
 Return     : VOS_OK -- success
              ErrorCode -- fail
 *****************************************************************************/
VOS_UINT32 V_ReserveMsg(VOS_PID Pid, MsgBlock * pMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    MSG_BLOCK_HEAD      *MSG_BLOCK_Ptr;
    VOS_UINT32          ulBlockAdd;
    VOS_UINT32          ulCtrlkAdd;

    if(Pid >= VOS_PID_BUTT)
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_RESERVE_INVALIDMSG);
        return(VOS_ERRNO_MSG_RESERVE_INVALIDMSG);
    }

    if(pMsg == VOS_NULL_PTR)
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    MSG_BLOCK_Ptr = (MSG_BLOCK_HEAD*)( (VOS_UINT32)pMsg
                         - VOS_MSG_BLK_HEAD_LEN );

    if ( VOS_OK != VOS_MemCheck( (VOS_VOID *)MSG_BLOCK_Ptr, &ulBlockAdd,
        &ulCtrlkAdd, ulFileID, usLineNo ) )
    {
        return VOS_ERR;
    }

    if ( VOS_MSG_HEAD_FLAG == MSG_BLOCK_Ptr->ulFlag )
    {
        MSG_BLOCK_Ptr->ulFlag = VOS_MSG_RESERVED_HEAD_FLAG;
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
 Function   : V_UnreserveMsg
 Description: In msg proceed function, unreserve a message
 Input      : pMsg     -- the pointer of application message (MsgBlock)
              Pid
 Return     : VOS_OK -- success
              ErrorCode -- fail
 *****************************************************************************/
VOS_UINT32 V_UnreserveMsg( VOS_PID Pid, MsgBlock * pMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    MSG_BLOCK_HEAD      *MSG_BLOCK_Ptr;
    VOS_UINT32          ulBlockAdd;
    VOS_UINT32          ulCtrlkAdd;

    if(Pid >= VOS_PID_BUTT)
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_RESERVE_INVALIDMSG);
        return(VOS_ERRNO_MSG_RESERVE_INVALIDMSG);
    }

    if(pMsg == VOS_NULL_PTR)
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    MSG_BLOCK_Ptr = (MSG_BLOCK_HEAD*)( (VOS_UINT32)pMsg
                         - VOS_MSG_BLK_HEAD_LEN );

    if ( VOS_OK != VOS_MemCheck( (VOS_VOID *)MSG_BLOCK_Ptr, &ulBlockAdd,
        &ulCtrlkAdd, ulFileID, usLineNo ) )
    {
        return VOS_ERR;
    }

    MSG_BLOCK_Ptr->ulFlag = VOS_MSG_HEAD_FLAG;

    return VOS_OK;
}


VOS_BOOL VOS_CheckMsgCPUId( VOS_UINT32 ulCPUId )
{
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
    /* CCPU��idΪ0�������Ϣ���յ�cpuid��Ϊccpu id����Ϊ�����Ϣ */
    if (OSA_CPU_CCPU != ulCPUId)
    {
        return VOS_TRUE;
    }
#elif (OSA_CPU_ACPU == VOS_OSA_CPU)
    /* ACPU��idΪ1�������Ϣ���յ�cpuid��Ϊacpu id����Ϊ�����Ϣ */
    if (OSA_CPU_ACPU != ulCPUId)
    {
        return VOS_TRUE;
    }
#endif
    return VOS_FALSE;
}


VOS_UINT32 VOS_CheckInterrupt( VOS_VOID )
{
#if ((VOS_OS_VER == VOS_VXWORKS) || (VOS_OS_VER == VOS_RTOSCK))
    return DRV_INT_GET_CONTEXT();
#elif (VOS_OS_VER == VOS_LINUX)
    return (VOS_UINT32)in_interrupt(); /* [false alarm]: ����Fortify���� */
#endif
    return VOS_FALSE;
}

/*****************************************************************************
 Function   : V_FreeReservedMsg
 Description: Free a reserved message.
 Input      : pMsg -- Point of the message to free
              Pid
 Return     : VOS_OK on success and error code on failure
 *****************************************************************************/
VOS_UINT32 V_FreeReservedMsg(VOS_PID Pid, VOS_VOID ** ppMsg,
                                    VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_VOID            *pMsgBlkHead;
    MSG_BLOCK_HEAD      *pstMSG;
    VOS_UINT32          ulBlockAdd;
    VOS_UINT32          ulCtrlkAdd;

    if(Pid >= VOS_PID_BUTT)
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTMSGISNULL);
        return(VOS_ERRNO_MSG_FREE_INPUTMSGISNULL);
    }

    if( VOS_NULL_PTR == ppMsg )
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    if( VOS_NULL_PTR == *ppMsg )
    {
        LogPrint3("# V_FreeReservedMsg,free reserved msg again.F %d L %d T %d.\r\n",
            (VOS_INT)ulFileID, usLineNo, (VOS_INT)VOS_GetTick() );

        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    pMsgBlkHead = (VOS_VOID*)( (VOS_UINT32)(*ppMsg)
                         - VOS_MSG_BLK_HEAD_LEN );

    if ( VOS_OK != VOS_MemCheck( pMsgBlkHead, &ulBlockAdd, &ulCtrlkAdd,
        ulFileID, usLineNo ) )
    {
        return VOS_ERR;
    }

    pstMSG = (MSG_BLOCK_HEAD *)pMsgBlkHead;
    if ( VOS_MSG_RESERVED_HEAD_FLAG == pstMSG->ulFlag )
    {
        /* Clear user's pointer */
        *ppMsg = VOS_NULL_PTR;

#if (VOS_DEBUG == VOS_DOPRA_VER)

        if ( VOS_NULL_PTR != g_pfnFreeMsgHook )
        {
            g_pfnFreeMsgHook(0);
        }

#endif

        return VOS_MemCtrlBlkFree( (VOS_MEM_CTRL_BLOCK *)ulCtrlkAdd,
            (VOS_MEM_HEAD_BLOCK *)ulBlockAdd, ulFileID, usLineNo );
    }
    else
    {
        return VOS_ERRNO_MSG_FREERES_STATUSERROR;
    }
}

/*****************************************************************************
 Function   : VOS_CheckRcvPid
 Description: Check if the receiver pid is correct.
 Input      : ulReceiverPid  -- receiver pid
 Return     : VOS_OK on success and error code on failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_CheckRcvPid(VOS_UINT32 ulReceiverPid)
{
    VOS_UINT32                          ulCpuID;

    ulCpuID = VOS_GET_CPU_ID(ulReceiverPid);

    if ( ulCpuID >= VOS_SUPPORT_CPU_NUM_MAX )    /*The CPU ID is too large*/
    {
        return(VOS_ERRNO_MSG_ICC_CPUIDISBIG);
    }

    /* coverity[overrun-local] */
    if ( ulReceiverPid >= g_astVOSSendMsgProcTable[ulCpuID].ulEndPID )  /*The Receive PID is too large*/
    {
        return(VOS_ERRNO_MSG_POST_INPUTPIDINVALID);
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : V_CheckMsgPara
 Description: Check the msg parameter.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      :
 *****************************************************************************/
VOS_UINT32 V_CheckMsgPara(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo )
{
    VOS_UINT32          ulPid;
    VOS_UINT32          ulCpuID;
    MsgBlock           *pMsgCtrlBlk;

#if (VOS_YES == VOS_CHECK_PARA)
    if ( VOS_NULL_PTR == ppMsg )
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);

        DRV_SYSTEM_ERROR(OSA_SEND_MSG_NULL,(VOS_INT)ulFileID,lLineNo,
                            VOS_NULL_PTR,0);

        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    if ( VOS_NULL_PTR == *ppMsg )
    {
        LogPrint2("# V_SendMsg,send msg again.F %d L %d.\r\n",
                    (VOS_INT)ulFileID, lLineNo);

        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);

        DRV_SYSTEM_ERROR(OSA_SEND_MSG_PP_NULL,(VOS_INT)ulFileID,lLineNo,
                            VOS_NULL_PTR,0);

        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }
#endif

    pMsgCtrlBlk     = (MsgBlock*)(*ppMsg);
    ulPid           = pMsgCtrlBlk->ulReceiverPid;
    ulCpuID         = VOS_GET_CPU_ID(ulPid);

    if ( ulCpuID >= VOS_SUPPORT_CPU_NUM_MAX )    /*The CPU ID is too large*/
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_CPUIDISBIG);

        LogPrint1("# V_SendMsg Error,invalid CPU id, PID is %d.\n", (VOS_INT)ulPid);

        DRV_SYSTEM_ERROR(VOS_ERRNO_MSG_ICC_CPUIDISBIG,(VOS_INT)ulFileID,lLineNo,
                        (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        VOS_FreeMsg( Pid, *ppMsg );

        return(VOS_ERRNO_MSG_ICC_CPUIDISBIG);
    }

    if ( ulPid >= g_astVOSSendMsgProcTable[ulCpuID].ulEndPID )  /*The Receive PID is too large*/
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_INPUTPIDINVALID);

        LogPrint1("# V_SendMsg Error,invalid PID %d.\n", (VOS_INT)ulPid);

        DRV_SYSTEM_ERROR(OSA_SEND_MSG_PID_BIG,(VOS_INT)ulFileID,lLineNo,
                        (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        VOS_FreeMsg( Pid, *ppMsg );

        return(VOS_ERRNO_MSG_POST_INPUTPIDINVALID);
    }

    return VOS_OK;
}
/*****************************************************************************
 Function   : V_SendLocalMsg
 Description: Send the msg to a task, which is in this CPU.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 V_SendLocalMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo )

{
    MsgBlock           *pMsgCtrlBlk;
    VOS_UINT32          ulPid;
    VOS_UINT32          ulFid;
    VOS_UINT32          ulQid;
    VOS_VOID            *pActualMsg;
    VOS_UINT32          ulBlockAdd;
    VOS_UINT32          ulCtrlkAdd;
    VOS_DUMP_MSG_STRU   *pstDumpMsgInfo;
    VOS_UINT32          ulTaskTcb;

    pMsgCtrlBlk      = (MsgBlock*)(*ppMsg);
    /* coverity[assignment] */
    ulPid            = pMsgCtrlBlk->ulReceiverPid;

    if ( ulPid < VOS_PID_DOPRAEND )
    {
        LogPrint1("# VOS_SendLocalMsg Rec PID %d Check error.\n", (VOS_INT)ulPid);

        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_PIDTOOSMALL);

        DRV_SYSTEM_ERROR(VOS_ERRNO_MSG_ICC_PIDTOOSMALL, (VOS_INT)ulFileID, lLineNo,
                        (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        VOS_FreeMsg( Pid, *ppMsg );

        return VOS_ERR;
    }

    if ( ulPid >= VOS_PID_BUTT )  /*The Receive PID is too large*/
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_INPUTPIDINVALID);

        LogPrint1("# VOS_SendLocalMsgError,invalid PID %d.\n", (VOS_INT)ulPid);

        DRV_SYSTEM_ERROR(OSA_SEND_MSG_PID_BIG,(VOS_INT)ulFileID,lLineNo,
                        (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        VOS_FreeMsg( Pid, *ppMsg );

        return VOS_ERR;
    }

    ulFid = (VOS_UINT32)(vos_PidRecords[ulPid-VOS_PID_DOPRAEND].Fid);

    /* coverity[first_enum_type] */
    if ( (ulFid < (VOS_UINT32)VOS_FID_DOPRAEND) || (ulFid >= (VOS_UINT32)VOS_FID_BUTT) )
    {
        LogPrint1("# *******VOS_SendLocalMsg Rec PID %d.\n", (VOS_INT)ulPid);

        VOS_SetErrorNo(VOS_ERRNO_MSG_PID_NO_FID);

        DRV_SYSTEM_ERROR(VOS_ERRNO_MSG_PID_NO_FID, (VOS_INT)ulFileID, lLineNo,
                        (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        VOS_FreeMsg( Pid, *ppMsg );

        return VOS_ERR;
    }

    ulQid            = vos_FidCtrlBlk[ulFid].Qid;

    pActualMsg = (VOS_VOID *)((VOS_UINT32)(*ppMsg) - VOS_MSG_BLK_HEAD_LEN);

    if ( VOS_OK != VOS_MemCheck( pActualMsg, &ulBlockAdd, &ulCtrlkAdd,
                                ulFileID, lLineNo ) )
    {
        LogPrint("# VOS_SendLocalMsg Mem Check error.\n");

        DRV_SYSTEM_ERROR(OSA_SEND_MSG_FAIL_TO_CHECK, (VOS_INT)ulFileID, lLineNo,
                        (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        return VOS_ERR;
    }

    if ( VOS_OK != VOS_FixedQueueWrite( ulQid, pActualMsg, (VOS_UINT32)MSG_SEND_SIZE,
                                        VOS_NORMAL_PRIORITY_MSG, ulPid ) )
    {
        LogPrint3("# V_SendMsg Error,queue full,Tx Pid %d Rx Pid %d Name 0x%x.\n",
            (int)(pMsgCtrlBlk->ulSenderPid), (int)ulPid, /* [false alarm]: ����Fortify���� */
            (int)(*(VOS_UINT32 *)(pMsgCtrlBlk->aucValue)) );

        pstDumpMsgInfo = (VOS_DUMP_MSG_STRU *)g_aucDumpMsgInfo;

        VOS_TaskLock();

        pstDumpMsgInfo->ulQid = ulQid;
        pstDumpMsgInfo->ulSendPid = pMsgCtrlBlk->ulSenderPid; /* [false alarm]: ����Fortify���� */
        pstDumpMsgInfo->ulRcvPid = ulPid;
        pstDumpMsgInfo->ulMsgName = *(VOS_UINT32 *)(pMsgCtrlBlk->aucValue);

        pstDumpMsgInfo++;

        VOS_QueuePrintFull(ulQid, (VOS_CHAR *)pstDumpMsgInfo,
            DUMP_MSG_INFO_LEN - sizeof(VOS_DUMP_MSG_STRU) );

        ulTaskTcb = VOS_GetTCBFromTID(vos_FidCtrlBlk[ulFid].Tid);

        DRV_SYSTEM_ERROR(VOS_SAVE_STACK(OSA_SEND_MSG_FAIL_TO_WRITE), (VOS_INT)ulTaskTcb,
                            lLineNo, g_aucDumpMsgInfo, DUMP_MSG_INFO_LEN);

        VOS_TaskUnlock();

        VOS_FreeMsg( Pid, *ppMsg );

        return VOS_ERR;
    }

    if ( VOS_MSG_RESERVED_HEAD_FLAG != ((MSG_BLOCK_HEAD*)pActualMsg)->ulFlag )
    {
        *ppMsg = VOS_NULL_PTR;
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_ModifyMsgInfo
 Description: modify the information. alloc msg. who?
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     :
 Other      :
 *****************************************************************************/
VOS_VOID VOS_ModifyMsgInfo(VOS_VOID *pMsg, VOS_PID Pid)
{
    VOS_VOID            *pActualMsg;
    VOS_UINT32          ulBlockAdd;
    VOS_UINT32          ulCtrlkAdd;

    pActualMsg = (VOS_VOID *)((VOS_UINT32)(pMsg) - VOS_MSG_BLK_HEAD_LEN);

    if ( VOS_OK != VOS_MemCheck( pActualMsg, &ulBlockAdd, &ulCtrlkAdd, 0, 0 ) )
    {
        return;
    }

    VOS_ModifyMemBlkInfo(ulBlockAdd, Pid);

    return;
}

/*****************************************************************************
 Function   : V_SendMsgByICC
 Description: Send the msg to another ARM's OSA by the ICC channle.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 V_SendMsgByICC(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo )
{
    VOS_UINT32              ulDataLen;
    VOS_INT                 lResult;
    MsgBlock                *pMsgCtrlBlk;

    pMsgCtrlBlk = (MsgBlock*)(*ppMsg);

    if ( DOPRA_PID_TIMER == pMsgCtrlBlk->ulSenderPid )
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_PIDTERROR);

        LogPrint1("\n# V_SendMsgByICC Error Timer Sender Icc Msg, Rec PID %d\n", (VOS_INT)pMsgCtrlBlk->ulReceiverPid);

        DRV_SYSTEM_ERROR(VOS_ERRNO_MSG_ICC_PIDTERROR, ulFileID, lLineNo,
                            (VOS_CHAR*)&lResult, sizeof(lResult));          /*Save the UDI result*/

        return(VOS_ERRNO_MSG_ICC_PIDTERROR);
    }

    if ( (-1) == g_OSAIccUDIHandle )
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_UDIHANDLERERROR);

        LogPrint("\n# V_SendMsgByICC Error UDI Not Open\n");

        return(VOS_ERRNO_MSG_ICC_UDIHANDLERERROR);
    }

    ulDataLen   = pMsgCtrlBlk->ulLength + VOS_MSG_HEAD_LENGTH;/*Get the Msg Length*/

    lResult     = DRV_UDI_WRITE( g_OSAIccUDIHandle, *ppMsg, ulDataLen );

    VOS_FreeMsg( Pid, *ppMsg ); /*need free the Msg memory*/

    /* ����C�˸�λ��дICCͨ��ʧ�ܻ᷵��һ������ֵ�����ܸ�λ���� */
    if (BSP_ERR_ICC_CCORE_RESETTING == (VOS_INT32)lResult )
    {
        LogPrint3("\n# V_SendMsgByICC Error,Ccore Reset, File  %d. line %d. Size %d .\n",
                        (VOS_INT)ulFileID, lLineNo,ulDataLen);

        return VOS_ERRNO_MSG_CCORE_RESET;
    }

    if ( ulDataLen != (VOS_UINT32)lResult ) /*Write Data to ICC channle Success*/
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_WRITEMSGERROR);

        LogPrint4("\n# V_SendMsgByICC Error,Write ICC Channel Error, File  %d. line %d. Size %d result %d.\n", (VOS_INT)ulFileID, lLineNo,ulDataLen,lResult);

        DRV_SYSTEM_ERROR(VOS_ERRNO_MSG_ICC_WRITEMSGERROR, (VOS_INT)ulFileID, lLineNo,
                            (VOS_CHAR*)&lResult, sizeof(lResult));          /*Save the UDI result*/

        return(VOS_ERRNO_MSG_ICC_WRITEMSGERROR);
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : V_SendMsg
 Description: Send the msg to a task, the task may be not in the same CPU.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 V_SendMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo)
{
    VOS_UINT32          ulResult;
    VOS_UINT32          ulPid;
    VOS_UINT32          ulCpuID;
    MsgBlock           *pMsgCtrlBlk;
    VOS_UINT32          ulSpanMsg;

    ulResult = V_CheckMsgPara( Pid, ppMsg, ulFileID, lLineNo );

    if ( VOS_OK != ulResult)
    {
        return ulResult;
    }

    pMsgCtrlBlk     = (MsgBlock*)(*ppMsg);
    ulPid           = pMsgCtrlBlk->ulReceiverPid;
    ulCpuID         = VOS_GET_CPU_ID(ulPid);

    if (VOS_NULL_PTR == g_astVOSSendMsgProcTable[ulCpuID].pfSendMsg)
    {
        LogPrint3("# V_SendMsg, send api is null.F %d L %d RecvPid %d.\r\n",
                    (VOS_INT)ulFileID, lLineNo, ulPid);

        VOS_FreeMsg( Pid, *ppMsg );

        VOS_SetErrorNo(VOS_ERRNO_MSG_SEND_FUNCEMPTY);

        return(VOS_ERRNO_MSG_SEND_FUNCEMPTY);
    }

    ulSpanMsg = VOS_CheckMsgCPUId(ulCpuID);

    /* �ж��з��Ϳ����Ϣ�����ش��� */
    if ( (VOS_TRUE == ulSpanMsg)
        && (VOS_FALSE != VOS_CheckInterrupt()) )
    {
        VOS_FreeMsg( Pid, *ppMsg );

        return (VOS_ERRNO_MSG_INT_MSGERROR);
    }

#ifndef OM_DEBUG
    /* �����Ϣ ���Ӻ�����Ϊ�� */
    if ( (VOS_NULL_PTR != vos_MsgHook)
        && (VOS_TRUE == ulSpanMsg))
    {
        (vos_MsgHook)(*ppMsg);
    }
#endif

    return g_astVOSSendMsgProcTable[ulCpuID].pfSendMsg( Pid, ppMsg, ulFileID, lLineNo );
}

/*****************************************************************************
 Function   : OM_ComRx_ICC_OSAMsg_CB
 Description: Receive the msg from the ICC channel, and send it to the Receive PID.
 Input      : ulChannelID   -- The ICC Channel ID
              lLen          -- the Msg data len
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/

VOS_UINT V_ICC_OSAMsg_CB(VOS_UINT ulChannelID,VOS_INT lLen)
{
    VOS_INT32               lResult;
    VOS_UINT8               *pucMsgData;
    MsgBlock                *pMsgCtrlBlk;
    MsgBlock                stTempDebug;

    if ( (-1) == g_OSAIccUDIHandle )
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_UDIHANDLERERROR);

        LogPrint("\n# V_ICC_OSAMsg_CB Error UDI Not Open\n");

        return(VOS_ERRNO_MSG_ICC_UDIHANDLERERROR);
    }

    if ( lLen <= VOS_MSG_HEAD_LENGTH )
    {
        LogPrint("\nV_ICC_OSAMsg_CB: The Data Len is small.\n");

        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_DATALENISNULL);

        lResult = DRV_UDI_READ( g_OSAIccUDIHandle, (VOS_CHAR *)&stTempDebug, (VOS_UINT32)lLen );

        DRV_SYSTEM_ERROR(VOS_ERRNO_MSG_ICC_READDATAFAIL, (VOS_INT)lLen, (VOS_INT)lResult,
                            (VOS_CHAR*)&stTempDebug, sizeof(MsgBlock));

        return VOS_ERR;
    }

    /* Alloc message space with static PID number */
    pucMsgData = (VOS_UINT8*)VOS_AllocMsg( VOS_PID_DOPRAEND, (VOS_UINT32)(lLen-VOS_MSG_HEAD_LENGTH) );

    if ( VOS_NULL_PTR == pucMsgData )
    {
        LogPrint("\nV_ICC_OSAMsg_CB: Alloc Msg memory failed.\n");

        return VOS_ERR;
    }

    /* get the Message data from the ICC channel */
    lResult = DRV_UDI_READ( g_OSAIccUDIHandle, pucMsgData, (VOS_UINT32)lLen );


    if ( lLen != lResult )
    {
        /* Record Debug info */
        VOS_MemCpy((VOS_CHAR *)&stTempDebug, (VOS_CHAR *)pucMsgData, sizeof(MsgBlock));

        VOS_FreeMsg( VOS_PID_DOPRAEND, pucMsgData );

        LogPrint("\nV_ICC_OSAMsg_CB: DRV_UDI_READ is Failed.\n");

        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_READDATAFAIL);

        DRV_SYSTEM_ERROR(VOS_ERRNO_MSG_ICC_READDATAFAIL, (VOS_INT)lLen, (VOS_INT)lResult,
                            (VOS_CHAR*)&stTempDebug, sizeof(MsgBlock));

        return VOS_ERRNO_MSG_ICC_READDATAFAIL;
    }

    pMsgCtrlBlk = (MsgBlock*)(pucMsgData);

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
    if(g_msglpm)
    {
        g_msglpm = 0;
        LogPrint3("[C SR] v_msg senderpid %d, receivepid %d, msgid 0x%x.\n", 
            pMsgCtrlBlk->ulSenderPid, pMsgCtrlBlk->ulReceiverPid, *((VOS_UINT32*)(pMsgCtrlBlk->aucValue))); /* [false alarm]: ����Fortify���� */
    }
#endif
    VOS_ModifyMsgInfo( (VOS_VOID *)pMsgCtrlBlk, pMsgCtrlBlk->ulSenderPid );

    return V_SendMsg(VOS_PID_DOPRAEND, (VOS_VOID**)(&(pucMsgData)), VOS_FILE_ID, __LINE__ );
}

/*****************************************************************************
 Function   : V_SendLocalUrgentMsg
 Description: send urgent message, that in this CPU
 Input      : Pid  -- process identifier to send message
              pMsg -- pointer of the message to be send
 Return     : Rerurn value of Msg_SendMsg
 *****************************************************************************/
VOS_UINT32 V_SendLocalUrgentMsg(VOS_PID Pid, VOS_VOID ** ppMsg,
                                  VOS_UINT32 ulFileID, VOS_INT32 lLineNo )
{
    MsgBlock           *pMsgCtrlBlk;
    VOS_UINT32          ulPid;
    int                 ulFid;
    VOS_UINT32          ulQid;
    VOS_VOID            *pActualMsg;
    VOS_UINT32          ulBlockAdd;
    VOS_UINT32          ulCtrlkAdd;
    VOS_UINT32          ulTaskTcb;
    VOS_DUMP_MSG_STRU   *pstDumpMsgInfo;

    pMsgCtrlBlk      = (MsgBlock*)(*ppMsg);
    /* coverity[assignment] */
    ulPid            = pMsgCtrlBlk->ulReceiverPid;

    if ( ulPid < VOS_PID_DOPRAEND )
    {
        LogPrint1("# V_SendLocalUrgentMsg Rec PID %d Check error.\n", (VOS_INT)ulPid);

        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_PIDTOOSMALL);

        DRV_SYSTEM_ERROR(VOS_ERRNO_MSG_ICC_PIDTOOSMALL, (VOS_INT)ulFileID, lLineNo,
                        (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        VOS_FreeMsg( Pid, *ppMsg );

        return VOS_ERR;
    }

    if ( ulPid >= VOS_PID_BUTT )  /*The Receive PID is too large*/
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_INPUTPIDINVALID);

        LogPrint1("# V_SendLocalUrgentMsg,invalid PID %d.\n", (VOS_INT)ulPid);

        DRV_SYSTEM_ERROR(OSA_SEND_MSG_PID_BIG,(VOS_INT)ulFileID,lLineNo,
                        (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        VOS_FreeMsg( Pid, *ppMsg );

        return VOS_ERR;
    }

    ulFid            = vos_PidRecords[ulPid-VOS_PID_DOPRAEND].Fid;
    ulQid            = vos_FidCtrlBlk[ulFid].Qid;

    pActualMsg = (VOS_VOID *)((VOS_UINT32)(*ppMsg) - VOS_MSG_BLK_HEAD_LEN);

    if ( VOS_OK != VOS_MemCheck( pActualMsg, &ulBlockAdd, &ulCtrlkAdd,
                                    ulFileID, lLineNo ) )
    {
        LogPrint("# V_SendLocalUrgentMsg Error, mem check error.\n");

        DRV_SYSTEM_ERROR(OSA_SEND_URG_MSG_FAIL_TO_CHECK, (VOS_INT)ulFileID, lLineNo,
                        (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        return VOS_ERR;
    }

    if ( VOS_OK != VOS_FixedQueueWrite( ulQid, pActualMsg, (VOS_UINT32)MSG_SEND_SIZE,
                                        VOS_EMERGENT_PRIORITY_MSG, ulPid ) )
    {
        LogPrint3("# V_SendLocalUrgentMsg Error,queue full,Tx Pid %d Rx Pid %d Name 0x%x.\n",
            (int)(pMsgCtrlBlk->ulSenderPid), (int)ulPid, /* [false alarm]: ����Fortify���� */
            (int)(*(VOS_UINT32 *)(pMsgCtrlBlk->aucValue)) );

        pstDumpMsgInfo = (VOS_DUMP_MSG_STRU *)g_aucDumpMsgInfo;

        VOS_TaskLock();

        pstDumpMsgInfo->ulQid = ulQid;
        pstDumpMsgInfo->ulSendPid = pMsgCtrlBlk->ulSenderPid; /* [false alarm]: ����Fortify���� */
        pstDumpMsgInfo->ulRcvPid = ulPid;
        pstDumpMsgInfo->ulMsgName = *(VOS_UINT32 *)(pMsgCtrlBlk->aucValue);

        pstDumpMsgInfo++;

        VOS_QueuePrintFull(ulQid, (VOS_CHAR *)pstDumpMsgInfo,
                            DUMP_MSG_INFO_LEN - sizeof(VOS_DUMP_MSG_STRU) );

        ulTaskTcb = VOS_GetTCBFromTID(vos_FidCtrlBlk[ulFid].Tid);

        DRV_SYSTEM_ERROR(VOS_SAVE_STACK(OSA_SEND_URG_MSG_FAIL_TO_WRITE), (VOS_INT)ulTaskTcb,
                            lLineNo, g_aucDumpMsgInfo, DUMP_MSG_INFO_LEN);

        VOS_TaskUnlock();

        VOS_FreeMsg( Pid, *ppMsg );

        return VOS_ERR;
    }

    if ( VOS_MSG_RESERVED_HEAD_FLAG != ((MSG_BLOCK_HEAD*)pActualMsg)->ulFlag )
    {
        *ppMsg = VOS_NULL_PTR;
    }

    return VOS_OK;

}

/*****************************************************************************
 Function   : V_SendUrgentMsg
 Description: send urgent message
 Input      : Pid  -- process identifier to send message
              pMsg -- pointer of the message to be send
 Return     : Rerurn value of Msg_SendMsg
 *****************************************************************************/
VOS_UINT32 V_SendUrgentMsg(VOS_PID Pid, VOS_VOID ** ppMsg,
                                  VOS_UINT32 ulFileID, VOS_INT32 lLineNo )
{
    VOS_UINT32          ulResult;
    VOS_UINT32          ulPid;
    VOS_UINT32          ulCpuID;
    MsgBlock           *pMsgCtrlBlk;

    ulResult = V_CheckMsgPara( Pid, ppMsg, ulFileID, lLineNo );

    if ( VOS_OK != ulResult)
    {
        return ulResult;
    }

    pMsgCtrlBlk     = (MsgBlock*)(*ppMsg);
    ulPid           = pMsgCtrlBlk->ulReceiverPid;
    ulCpuID         = VOS_GET_CPU_ID(ulPid);

    if (VOS_NULL_PTR == g_astVOSSendMsgProcTable[ulCpuID].pfSendUrgentMsg)
    {
        LogPrint3("# V_SendUrgentMsg, send api is null.F %d L %d RecvPid %d.\r\n",
                    (VOS_INT)ulFileID, lLineNo, ulPid);

        VOS_SetErrorNo(VOS_ERRNO_MSG_SEND_FUNCEMPTY);

        return(VOS_ERRNO_MSG_SEND_FUNCEMPTY);
    }

#ifndef OM_DEBUG
    if ( (VOS_NULL_PTR != vos_MsgHook)
        && (VOS_PID_BUTT != g_astVOSSendMsgProcTable[ulCpuID].ulEndPID))
    {
        (vos_MsgHook)(*ppMsg);
    }
#endif

    return g_astVOSSendMsgProcTable[ulCpuID].pfSendUrgentMsg( Pid, ppMsg, ulFileID, lLineNo );
}

/*****************************************************************************
 Function   : V_PostMsg
 Description: This function is synchronization msg send.
              In fact, it calls receiver Pid's Msg Process func to handle
              the message directly.
 Input      : Pid  -- PID who send the message
              pMsg -- Pointer of message to be sent
 Return     : VOS_OK on success and errno on failure
 Other      : 1) The sender Pid and Receiver Pid must in the same local Board.
              2) The caller should Alloc and Release Msg by itself.
 *****************************************************************************/
VOS_UINT32 V_PostMsg(VOS_PID Pid, VOS_VOID * pMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_UINT32          ulReceiverPid;
    VOS_UINT32          ulReceiverCpuId;
    VOS_UINT32          ulBlockAdd;
    VOS_UINT32          ulCtrlkAdd;
    VOS_VOID            *pActualMsg;

    if( VOS_NULL_PTR == pMsg )
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_INPUTMSGISNULL);
        return VOS_ERRNO_MSG_POST_INPUTMSGISNULL;
    }

    /*The sender Pid and Receiver Pid must in one Board */
    ulReceiverCpuId = ((MsgBlock *)pMsg)->ulReceiverCpuId;
    if( VOS_LOCAL_CPUID != ulReceiverCpuId )
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_RECVCPUNOTLOCAL);
        return VOS_ERRNO_MSG_POST_RECVCPUNOTLOCAL;
    }

    /* coverity[assignment] */
    ulReceiverPid = ((MsgBlock*)pMsg)->ulReceiverPid;
    if( ulReceiverPid >= VOS_PID_BUTT )
    {
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_RECVPIDINVALID);
        return VOS_ERRNO_MSG_POST_RECVPIDINVALID;
    }

    pActualMsg = (VOS_VOID *)((VOS_UINT32)pMsg - VOS_MSG_BLK_HEAD_LEN);

    if ( VOS_OK != VOS_MemCheck( pActualMsg, &ulBlockAdd, &ulCtrlkAdd,
        ulFileID, usLineNo ) )
    {
        LogPrint("# VOS_PostMsg Mem error.\n");
        return VOS_ERR;
    }

    /* call receive Pid's Msg Process func */
    (vos_PidRecords[ulReceiverPid-VOS_PID_DOPRAEND].MsgFunction)((MsgBlock *)pMsg);

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_GetMsgName
 Description: get message name
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_GetMsgName(VOS_UINT32 ulAddrress)
{
    MsgBlock *pstMsgBlock = (MsgBlock*)( ulAddrress + VOS_MSG_BLK_HEAD_LEN ); /* [false alarm]: ����Fortify���� */

    return *((VOS_UINT32 *)(pstMsgBlock->aucValue));
}

#if (VOS_DEBUG == VOS_DOPRA_VER)

/*****************************************************************************
 Function   : VOS_RegisterMemAllocHook
 Description: register a hook to msg alloc
 Input      : void
 Return     : void
 Other      : only for designer
 *****************************************************************************/
VOS_UINT32 VOS_RegisterMsgAllocHook( VOS_UINT32 ulMode, MEMORY_HOOK_FUNC pfnHook)
{
    if ( VOS_ALLOC_MODE == ulMode )
    {
        g_pfnAllocMsgHook = pfnHook;

        return VOS_OK;
    }
    else if ( VOS_FREE_MODE == ulMode )
    {
        g_pfnFreeMsgHook = pfnHook;

        return VOS_OK;
    }
    else
    {
        LogPrint("VOS_RegisterMsgAllocHook mode error.\r\n");

        return VOS_ERR;
    }
}

#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


