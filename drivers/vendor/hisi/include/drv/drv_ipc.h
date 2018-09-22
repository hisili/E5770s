

#ifndef __DRV_IPCM_H__
#define __DRV_IPCM_H__
#include "drv_comm.h"
#include "drv_ipc_enum.h"
/*************************IPC BEGIN**********************************/
#define INTSRC_NUM                     32

/*****************************************************************************
* �� �� ��  : BSP_DRV_IPCIntInit
*
* ��������  : IPCģ���ʼ��
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ  : ��

*****************************************************************************/
BSP_S32 BSP_DRV_IPCIntInit(void);


/*****************************************************************************
* �� �� ��  : DRV_IPC_SEMCREATE
*
* ��������  : �ź�����������
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ  : ��

*****************************************************************************/
BSP_S32 BSP_IPC_SemCreate(BSP_U32 u32SignalNum);
#define DRV_IPC_SEMCREATE(u32SignalNum) BSP_IPC_SemCreate(u32SignalNum)

/*****************************************************************************
* �� �� ��  : DRV_IPC_SEMDELETE
*
* ��������  : ɾ���ź���
*
* �������  :   BSP_U32 u32SignalNum Ҫɾ�����ź������

* �������  : ��
*
* �� �� ֵ  : OK&ERROR

*****************************************************************************/
BSP_S32 BSP_IPC_SemDelete(BSP_U32 u32SignalNum);
#define  DRV_IPC_SEMDELETE(u32SignalNum) BSP_IPC_SemDelete(u32SignalNum)

/*****************************************************************************
* �� �� ��  : BSP_IPC_IntEnable
*
* ��������  : ʹ��ĳ���ж�
*
* �������  :
                BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
* �������  : ��
*
* �� �� ֵ  : OK&ERROR

*****************************************************************************/
BSP_S32 BSP_IPC_IntEnable (IPC_INT_LEV_E ulLvl);
#define  DRV_IPC_INTENABLE(ulLvl)  BSP_IPC_IntEnable(ulLvl)

/*****************************************************************************
* �� �� ��  : DRV_IPC_INTDISABLE
*
* ��������  : ȥʹ��ĳ���ж�
*
* �������  :
            BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
* �������  : ��
*
* �� �� ֵ  : OK&ERROR

*****************************************************************************/
BSP_S32 BSP_IPC_IntDisable (IPC_INT_LEV_E ulLvl);
#define  DRV_IPC_INTDISABLE(ulLvl) BSP_IPC_IntDisable(ulLvl)

/*****************************************************************************
* �� �� ��  : BSP_IPC_IntConnect
*
* ��������  : ע��ĳ���ж�
*
* �������  :
           BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
           VOIDFUNCPTR routine �жϷ������
*             BSP_U32 parameter      �жϷ���������
* �������  : ��
*
* �� �� ֵ  : OK&ERROR

*****************************************************************************/
BSP_S32 BSP_IPC_IntConnect  (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, BSP_U32 parameter);
#define DRV_IPC_INTCONNECT(ulLvl,routine,parameter) BSP_IPC_IntConnect(ulLvl,routine,parameter)

/*****************************************************************************
* �� �� ��  : BSP_IPC_IntDisonnect
*
* ��������  : ȡ��ע��ĳ���ж�
*
* �������  :
*              BSP_U32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��31
*              VOIDFUNCPTR routine �жϷ������
*             BSP_U32 parameter      �жϷ���������
* �������  : ��
*
* �� �� ֵ  : OK&ERROR

*****************************************************************************/
BSP_S32 BSP_IPC_IntDisonnect  (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, BSP_U32 parameter);

/*****************************************************************************
* �� �� ��  : DRV_IPC_INTSEND
*
* ��������  : �����ж�
*
* �������  :
                IPC_INT_CORE_E enDstore Ҫ�����жϵ�core
                BSP_U32 ulLvl Ҫ���͵��жϺţ�ȡֵ��Χ0��31
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*

*****************************************************************************/
BSP_S32 BSP_IPC_IntSend(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);
#define  DRV_IPC_INTSEND(enDstCore, ulLvl) BSP_IPC_IntSend(enDstCore, ulLvl)

/*****************************************************************************
* �� �� ��  : DRV_IPC_SEMTAKE
*
* ��������  : ��ȡ�ź���
*
* �������  : u32SignalNum Ҫ��ȡ���ź���
* �������  : ��
*
* �� �� ֵ  : ��

*****************************************************************************/
BSP_S32 BSP_IPC_SemTake(BSP_U32 u32SignalNum,BSP_S32 s32timeout);
#define  DRV_IPC_SEMTAKE(u32SignalNum, s32timeout) BSP_IPC_SemTake(u32SignalNum, s32timeout)

/*****************************************************************************
* �� �� ��  : DRV_IPC_SEMGIVE
*
* ��������  : �ͷ��ź���
*
* �������  : u32SignalNum Ҫ�ͷŵ��ź���
* �������  : ��
*
* �� �� ֵ  : ��
*
*****************************************************************************/
BSP_VOID BSP_IPC_SemGive(BSP_U32 u32SignalNum);
#define  DRV_IPC_SEMGIVE(u32SignalNum) BSP_IPC_SemGive(u32SignalNum)

/*****************************************************************************
* �� �� ��  : BSP_IPC_SpinLock
*
* ��������  : ��ȡ�ź���,�������жϹ��ܣ�ʹ��֮ǰ��Ҫ�û�
						���ж�
*
* �������  : u32SignalNum Ҫ��ȡ���ź���
*
* �� �� ֵ  : ��
*
*****************************************************************************/
BSP_VOID BSP_IPC_SpinLock (BSP_U32 u32SignalNum);
#define DRV_SPIN_LOCK(u32SignalNum)  BSP_IPC_SpinLock(u32SignalNum)

/*****************************************************************************
* �� �� ��  : DRV_SPIN_UNLOCK
*
* ��������  : �ͷ��ź���,�������жϹ��ܣ���BSP_IPC_SpinLock����ʹ��
					ʹ�ú��ж�
*
* �������  : u32SignalNum Ҫ�ͷŵ��ź���
* �������  : ��
*
* �� �� ֵ  : ��
*
*****************************************************************************/
BSP_VOID BSP_IPC_SpinUnLock (BSP_U32 u32SignalNum);
#define DRV_SPIN_UNLOCK(u32SignalNum) BSP_IPC_SpinUnLock(u32SignalNum)

BSP_S32 BSP_IPC_SpinLock_IrqSave(BSP_U32 u32SignalNum,unsigned long *flags);
BSP_S32 BSP_IPC_SpinUnLock_IrqRestore(BSP_U32 u32SignalNum,unsigned long *flags);

/*****************************************************************************
* �� �� ��  : DRV_SPIN_LOCK_IRQSAVE
*
* ��������  : ��ȡ�ź���,�����жϹ���
* �������  : u32SignalNum Ҫ��ȡ���ź���
					   flags:���жϱ�ǣ������ʹ�òο�spin_lock_irqsave�÷���
					   ������DRV_SPIN_UNLOCK_IRQRESTORE���,ֻ����ͬһ������
					   �ڲ�ǰ�󱻵���
* �������  : ��
*
* �� �� ֵ  : 
*****************************************************************************/

#define DRV_SPIN_LOCK_IRQSAVE(u32SignalNum,flags) 		BSP_IPC_SpinLock_IrqSave(u32SignalNum, &flags)
/*****************************************************************************
* �� �� ��  : DRV_SPIN_UNLOCK_IRQRESTORE
*
* ��������  : �ͷŻ�ȡ���ź���,���ָ��жϹ���
* �������  : u32SignalNum Ҫ�ͷŵ��ź���
						flags:���жϱ�ǣ��ο�spin_lock_irqrestore�÷�����������
					   DRV_SPIN_LOCK_IRQSAVE���,ֻ����ͬһ�������ڲ�
					   ǰ�󱻵���
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
*****************************************************************************/

#define DRV_SPIN_UNLOCK_IRQRESTORE(u32SignalNum,flags) 		BSP_IPC_SpinUnLock_IrqRestore(u32SignalNum,&flags);

BSP_S32 BSP_SGI_Connect(BSP_U32 ulLvl,VOIDFUNCPTR routine, BSP_U32 parameter);
BSP_S32 BSP_SGI_IntSend(BSP_U32 ulLvl);

/*************************IPC END************************************/

#endif

