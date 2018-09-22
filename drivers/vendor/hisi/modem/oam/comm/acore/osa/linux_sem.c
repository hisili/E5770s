/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: linux_sem.c                                                     */
/*                                                                           */
/* Author: Xu Cheng                                                          */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2011-07                                                             */
/*                                                                           */
/* Description: implement linux semaphore                                    */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/
/*lint --e{601,132,718,746,530,115,808,713,516,565}*/
#include "vos_config.h"
#include "v_sem.h"
#include "v_IO.h"
#include "v_task.h"
#include "v_int.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif /* __cplusplus */
#endif /* __cplusplus */

#if (VOS_LINUX == VOS_OS_VER)


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_V_SEM_C
/*lint +e767 modify:x51137; review:h59254; */

typedef struct SEM_CONTROL_STRU
{
    int                       Flag;/* control block's state */
    struct SEM_CONTROL_STRU   *SemId;/* the ID return to User */
    int                       SemType;/* type of SEM */
    int                       SemFlags;
    int                       SemInitCount;
    char                      Name[VOS_MAX_SEM_NAME_LENGTH];
    int                       sleepers;/* wait task count */
    atomic_t                  count;/* resource count */ 
    wait_queue_head_t         wait;/* wait list */
} SEM_CONTROL_BLOCK;

/* the number of queue's control block */
VOS_UINT32              vos_SemCtrlBlkNumber;

/* the start address of queue's control block */
SEM_CONTROL_BLOCK       *vos_SemCtrlBlk;

/* the Max usage of queue */
VOS_UINT32              vos_SemMaxSemId;

#define VOS_SEM_CTRL_BUF_SIZE (sizeof(SEM_CONTROL_BLOCK)*VOS_MAX_SEM_NUMBER)

VOS_CHAR g_acVosSemCtrlBuf[VOS_SEM_CTRL_BUF_SIZE];

static DEFINE_SPINLOCK(VOS_semaphore_lock);

/* ���������������ź������ٽ���Դ���� */
VOS_SPINLOCK             g_stVosSemSpinLock;

/*****************************************************************************
 Function   : VOS_SemCtrlBlkInit
 Description: Init semaphore's control block
 Input      : ulSemCtrlBlkNumber -- number
 Return     : None
 Other      :
 *****************************************************************************/
VOS_VOID VOS_SemCtrlBlkInit(VOS_VOID)
{
    int i;

    vos_SemCtrlBlkNumber = VOS_MAX_SEM_NUMBER;

    vos_SemCtrlBlk = (SEM_CONTROL_BLOCK*)g_acVosSemCtrlBuf;

    for(i=0; i<(int)vos_SemCtrlBlkNumber; i++)
    {
        vos_SemCtrlBlk[i].Flag  = VOS_SEM_CTRL_BLK_IDLE;
        vos_SemCtrlBlk[i].SemId = vos_SemCtrlBlk+i;
    }

    vos_SemMaxSemId = 0;

    VOS_SpinLockInit(&g_stVosSemSpinLock);

    return;
}

/*****************************************************************************
 Function   : VOS_SemCtrlBlkGet
 Description: allocate a control block
 Input      : void
 Return     : address
 Other      :
 *****************************************************************************/
SEM_CONTROL_BLOCK *VOS_SemCtrlBlkGet(VOS_VOID)
{
    VOS_UINT32      i;
    VOS_UINT32      ulLockLevel;

    /*intLockLevel = VOS_SplIMP();*/
    VOS_SpinLockIntLock(&g_stVosSemSpinLock, ulLockLevel);

    for(i=0; i<vos_SemCtrlBlkNumber; i++)
    {
        if(vos_SemCtrlBlk[i].Flag == VOS_SEM_CTRL_BLK_IDLE)
        {
            vos_SemCtrlBlk[i].Flag = VOS_SEM_CTRL_BLK_BUSY;
            break;
        }
    }

    /*VOS_Splx(intLockLevel);*/
    VOS_SpinUnlockIntUnlock(&g_stVosSemSpinLock, ulLockLevel);

    if( i < vos_SemCtrlBlkNumber)
    {
        /* record the max usage of SEM */
        if ( i > vos_SemMaxSemId )
        {
            vos_SemMaxSemId = i;
        }

        return vos_SemCtrlBlk+i;
    }
    else
    {
        LogPrint("# VOS_GetSemCtrlBlk no Idle.\r\n");

        VOS_SetErrorNo(VOS_ERRNO_SEMA4_FULL);

        return(VOS_MAX_SEM_ID_NULL);
    }
}

/*****************************************************************************
 Function   : VOS_SemCtrlBlkFree
 Description: fress a block
 Input      : Sem_Address -- address
 Return     : VOS_OK on success or errno on failure.
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_SemCtrlBlkFree( SEM_CONTROL_BLOCK *Sem_Address )
{
    VOS_UINT32      ulLockLevel;

    if( Sem_Address == Sem_Address->SemId )
    {
        if(Sem_Address->Flag == VOS_SEM_CTRL_BLK_IDLE)
        {
            return(VOS_ERR);
        }
        else
        {
            /*intLockLevel = VOS_SplIMP();*/
            VOS_SpinLockIntLock(&g_stVosSemSpinLock, ulLockLevel);

            Sem_Address->Flag = VOS_SEM_CTRL_BLK_IDLE;

            /*VOS_Splx(intLockLevel);*/
            VOS_SpinUnlockIntUnlock(&g_stVosSemSpinLock, ulLockLevel);
        }

        return(VOS_OK);
    }
    else
    {
        Print("# VOS_FreeSemCtrlBlk free NULL Sem.\r\n");

        return(VOS_ERR);
    }
}

/*****************************************************************************
 Function   : VOS_SmCCreate
 Description: To create a counting semaphore;
 Input      : acSmName -- the semaphore name, can be null
              ulSmInit -- The count number of the semaphore that create;
              ulFlags  -- FIFO or priority;
 Output     : pulSmID  -- the ID of the create semaphore;
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmCCreate( VOS_CHAR   acSmName[4],
                          VOS_UINT32 ulSmInit,
                          VOS_UINT32 ulFlags,
                          VOS_UINT32 *pulSmID )
{
    int                    i;
    SEM_CONTROL_BLOCK      *iSemId;

    iSemId = VOS_SemCtrlBlkGet();

    if (VOS_MAX_SEM_ID_NULL == iSemId)
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
        return(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
    }

    *pulSmID = (VOS_UINT32)iSemId;

    if( 0xFFFFFFFF == ulSmInit )
    {
        atomic_set(&(iSemId->count), 1);

        iSemId->SemType  = VOS_SEM_TYPE_MUTEX;
    }
    else
    {
        atomic_set(&(iSemId->count), ulSmInit);

        iSemId->SemType  = VOS_SEM_TYPE_COUNT;
    }

    iSemId->sleepers = 0;

    init_waitqueue_head(&(iSemId->wait));

    if ( VOS_NULL_PTR != acSmName )
    {
        for(i=0; i<VOS_MAX_SEM_NAME_LENGTH/2; i++)
        {
            iSemId->Name[i]  = acSmName[i];
        }
        iSemId->Name[VOS_MAX_SEM_NAME_LENGTH/2]  = '\0';
    }
    else
    {
        iSemId->Name[0] = '\0';
    }

    iSemId->SemFlags     = ulFlags;
    iSemId->SemInitCount = (int)ulSmInit;

    return(VOS_OK);
}

/*****************************************************************************
 Function   : VOS_SmMCreate
 Description: To create a Mutex semaphore, can be null
 Input      : acSmName[4] -- the semaphore name;
              ulFlags     -- FIFO or priority;
 Output     : pulSmID     -- the ID of the created semaphore;
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmMCreate( VOS_CHAR   Sm_Name[4],
                          VOS_UINT32 Flags,
                          VOS_UINT32 *Sm_ID )
{
    return( VOS_SmCCreate( Sm_Name, 0xFFFFFFFF, Flags, Sm_ID ));
}

/*****************************************************************************
 Function   : VOS_SmCCreate
 Description: To create a counting semaphore;
 Input      : acSmName -- the semaphore name, can be null
              ulSmInit -- The count number of the semaphore that create;
              ulFlags  -- FIFO or priority;
 Output     : pulSmID  -- the ID of the create semaphore;
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmCreate( VOS_CHAR Sm_Name[4],
                         VOS_UINT32 Sm_Init,
                         VOS_UINT32 Flags,
                         VOS_UINT32 * Sm_ID )
{
    return( VOS_SmCCreate( Sm_Name, Sm_Init, Flags, Sm_ID ));
}

/**************************************************************************
 Function   : VOS_SmBCreate
 Description: To create a Binary semaphore;
 Input      : acSmName -- the semaphore name, can be null
              Sm_Ini   -- The count number of the semaphore that create;
              ulFlags  -- FIFO or priority;
 Output     : pulSmID  -- the ID of the create semaphore;
 Return     : VOS_OK on success and errno on failure
 **************************************************************************/
VOS_UINT32 VOS_SmBCreate( VOS_CHAR Sm_Name[4],
                          VOS_UINT32 Sm_Init,
                          VOS_UINT32 Flags,
                          VOS_UINT32 * Sm_ID )
{
    int                    i;
    SEM_CONTROL_BLOCK      *iSemId;
    VOS_INT32              init_state;

    if ( Sm_Init >= 1 )
    {
        init_state = 1;
    }
    else
    {
        init_state = 0;
    }

    iSemId = VOS_SemCtrlBlkGet();

    if( iSemId == VOS_MAX_SEM_ID_NULL)
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
        return(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
    }

    atomic_set(&(iSemId->count), init_state);

    iSemId->sleepers = 0;

    init_waitqueue_head(&(iSemId->wait));
    
    *Sm_ID = (VOS_UINT32)iSemId;

    if ( VOS_NULL_PTR != Sm_Name )
    {
        for(i=0; i<VOS_MAX_SEM_NAME_LENGTH/2; i++)
        {
            iSemId->Name[i]  = Sm_Name[i];
        }
        iSemId->Name[VOS_MAX_SEM_NAME_LENGTH/2]  = '\0';
    }
    else
    {
        iSemId->Name[0] = '\0';
    }
    
    iSemId->SemType  = VOS_SEM_TYPE_BINARY;
    iSemId->SemFlags     = Flags;
    iSemId->SemInitCount = (int)Sm_Init;

    return(VOS_OK);
}

/*****************************************************************************
 Function   : VOS_SmDelete
 Description: to delete the exiting semaphore according to the ulSmID
 Input      : ulSmID -- ID of semaphore
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmDelete( VOS_UINT32 Sm_ID )
{
    SEM_CONTROL_BLOCK *temp_Ptr;

    temp_Ptr = (SEM_CONTROL_BLOCK *)Sm_ID;

    if( temp_Ptr == temp_Ptr->SemId )
    {
        vos_printf("\r\nVOS_SmDelete: Delete the Sem %x", Sm_ID);

        if(temp_Ptr->Flag == VOS_SEM_CTRL_BLK_IDLE)
        {
            VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_OBJTFULL);
            return(VOS_ERRNO_SEMA4_CCREATE_INVALID_SMID);
        }

        return VOS_SemCtrlBlkFree(temp_Ptr);     
    }
    else
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_CCREATE_INVALID_SMID);
        return(VOS_ERRNO_SEMA4_CCREATE_INVALID_SMID);
    }
}

/*****************************************************************************
 Function   : VOS_SemDown
 Description: schedule a task which pend on a sem
 Input      : pSemCB -- control of semaphore
              timeOutInMillSec -- timeout unit is ms
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SemDown(SEM_CONTROL_BLOCK *pSemCB, VOS_UINT32 timeOutInMillSec)
{
    struct task_struct *tsk = current;
    VOS_UINT32         timeintick;
    VOS_UINT32         flags;
    VOS_UINT32         ulRetValue = VOS_OK;
    VOS_INT            sleepers;

    DECLARE_WAITQUEUE(wait, tsk);
    
    /* if timeOutInMillSec = 0, schedule and do not time out
       if timeOutInMillSec > 0, schedule and time out */
    timeintick = (timeOutInMillSec==0)
                  ? MAX_SCHEDULE_TIMEOUT : ((timeOutInMillSec*HZ)/1000);

    tsk->state = TASK_UNINTERRUPTIBLE;

    add_wait_queue_exclusive(&pSemCB->wait, &wait);

    spin_lock_irqsave(&VOS_semaphore_lock, flags);

    pSemCB->sleepers++;

    for ( ; ; ) 
    {
        sleepers = pSemCB->sleepers;

        /* Add "everybody else" into it. They aren't
           playing, because we own the spinlock. */
        if (!atomic_add_negative(sleepers - 1, &pSemCB->count)) 
        {
            pSemCB->sleepers = 0;
            break;
        }

        pSemCB->sleepers = 1;   /* us - see -1 above */

        spin_unlock_irqrestore(&VOS_semaphore_lock, flags);

        /* if timeintick equal MAX_SCHEDULE_TIMEOUT,
           finally will call schedule(), will not return back
           if no other wake up this thread */
           
        if ( 0 == schedule_timeout(timeintick) )
        {
            /* match spin_unlock_irqrestore, which behind */
            spin_lock_irqsave(&VOS_semaphore_lock, flags);
            ulRetValue = VOS_ERRNO_SEMA4_P_TIMEOUT;
            break;         
        }
        else
        {
            ulRetValue = VOS_OK;
        }

        tsk->state = TASK_UNINTERRUPTIBLE;

        spin_lock_irqsave(&VOS_semaphore_lock, flags);
    }

    spin_unlock_irqrestore(&VOS_semaphore_lock, flags);

    remove_wait_queue(&pSemCB->wait, &wait);

    tsk->state = TASK_RUNNING;

    /* wake up another one, now maybe count > 0 */
    wake_up(&pSemCB->wait);

    return ulRetValue;
}


/*****************************************************************************
 Function   : VOS_SmP
 Description: Lock the resource for synchronization, if the resource is none
              then block, otherwise the number of the resource --
 Input      : ulSmID             -- the ID of the resource to lock
              ulTimeOutInMillSec -- the time to wait(0 for ever)
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmP( VOS_UINT32 Sm_ID, VOS_UINT32 ulTimeOutInMillSec )
{
    SEM_CONTROL_BLOCK  *temp_Ptr;
    VOS_UINT32         ulFlags;


    temp_Ptr = (SEM_CONTROL_BLOCK *)Sm_ID;

    if( temp_Ptr != temp_Ptr->SemId )
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_P_IDERR);
        return (VOS_ERRNO_SEMA4_P_IDERR);
    }

    if (VOS_SEM_CTRL_BLK_IDLE == temp_Ptr->Flag)
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_P_NOTACTIVE);
        return(VOS_ERRNO_SEMA4_P_NOTACTIVE);
    }

    spin_lock_irqsave(&temp_Ptr->wait.lock, ulFlags);

    atomic_dec(&temp_Ptr->count);

    if (atomic_add_negative(0, &temp_Ptr->count))
    {
        spin_unlock_irqrestore(&temp_Ptr->wait.lock, ulFlags);

        return VOS_SemDown(temp_Ptr, ulTimeOutInMillSec);
    }

    spin_unlock_irqrestore(&temp_Ptr->wait.lock, ulFlags);

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_SmV
 Description: Release/Unlock the sema4 that has locked a resource
 Input      : ulSmID -- id of semaphore
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_SmV( VOS_UINT32 Sm_ID )
{
    SEM_CONTROL_BLOCK  *temp_Ptr;
    VOS_UINT32         ulFlags;

    temp_Ptr = (SEM_CONTROL_BLOCK *)Sm_ID;

    if ( temp_Ptr != temp_Ptr->SemId )
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_V_IDERR);
        return(VOS_ERRNO_SEMA4_V_IDERR);
    }

    if( temp_Ptr->Flag == VOS_SEM_CTRL_BLK_IDLE)
    {
        VOS_SetErrorNo(VOS_ERRNO_SEMA4_V_NOTACTIVE);
        return(VOS_ERRNO_SEMA4_V_NOTACTIVE);
    }

    spin_lock_irqsave(&temp_Ptr->wait.lock, ulFlags); 

    /* if less than 1, meaning others are waiting */
    if (atomic_inc_return(&temp_Ptr->count) < 1)
    {
        spin_unlock_irqrestore(&temp_Ptr->wait.lock, ulFlags);

        wake_up(&temp_Ptr->wait);

        return VOS_OK;
    }

    if ( (VOS_SEM_TYPE_MUTEX == temp_Ptr->SemType) 
    || (VOS_SEM_TYPE_BINARY == temp_Ptr->SemType) )
    {
        atomic_set(&temp_Ptr->count, 1);     
    }

    spin_unlock_irqrestore(&temp_Ptr->wait.lock, ulFlags);

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_Sm_AsyP
 Description: to lock the resource asynchronous
 Input      : ulSmID -- ID of semaphore
 Return     : VOS_OK on success and errno on failure
 *****************************************************************************/
VOS_UINT32 VOS_Sm_AsyP( VOS_UINT32 Sm_ID )
{
    return(VOS_SmP( Sm_ID, 1 ));
}

/*****************************************************************************
 Function   : VOS_show_sem_info
 Description: print the usage info of Sem
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID VOS_show_sem_info( VOS_VOID )
{
    vos_printf("Max be used sem is %x.\r\n",vos_SemMaxSemId);
}


#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



