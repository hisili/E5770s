
/*lint --e{537,718,746,958,959}*/
#include <linux/time.h>
#include <linux/delay.h>
#include <osl_spinlock.h>
#include <osl_module.h>
#include <bsp_om.h>
#include <bsp_ipc.h>
#include <bsp_shared_ddr.h>
#include <drv_sync.h>
#include <bsp_hardtimer.h>

#define SYNC_LOCK_ADDR           (SHM_MEM_SYNC_ADDR)
#define SYNC_STATE_ADDR         (SYNC_LOCK_ADDR + 0x30)
#define SYNC_SLEEP(a) msleep(a*10)
struct sync_control
{
	char *g_pSyncLock;
	char *g_pSyncState;
	spinlock_t lock;
};
	/*lint -save -e34 -e35*/

struct sync_control sync_ctrl;

static unsigned long  SyncSpinLock(void)
{
	unsigned long flag = 0;
	spin_lock_irqsave(&sync_ctrl.lock,flag);
	bsp_ipc_spin_lock(IPC_SEM_SYNC);
	return flag;
}

static void SyncSpinUnlock(unsigned long flag)
{
	bsp_ipc_spin_unlock(IPC_SEM_SYNC);
	spin_unlock_irqrestore(&sync_ctrl.lock,flag);
	return;
}

static void BSP_SYNC_Init(void)
{
    static int sync_init = false;
    if(!sync_init)
    {
        sync_ctrl.g_pSyncLock = (char*)SYNC_LOCK_ADDR;
	    sync_ctrl.g_pSyncState = (char*)SYNC_STATE_ADDR;
		spin_lock_init(&sync_ctrl.lock);
        sync_init = true;
    }
}
/*****************************************************************************
* �� �� �� : BSP_SYNC_Lock
*
* ��������: ��������ѯģ��ĳ�ʼ��״̬
*
* �������: u32Module     ģ��
*                         pState        ״ָ̬��
*                         u32TimeOut    ��ʱֵ��0Ϊ��Զ�ȴ���
*
* �������: ��
*
* �� �� ֵ   : OK&ERROR
*
* ����˵��: ��
*
*****************************************************************************/
int BSP_SYNC_Lock(SYNC_MODULE_E u32Module, unsigned int *pState, unsigned int u32TimeOut)
{
	unsigned long flag;
	u32 tick_end=0;
	u32 tick_begin=0;
	 BSP_SYNC_Init();
	if(!pState || (u32Module >= SYNC_MODULE_BUTT))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_Lock, invalid param, module=0x%x, pState=0x%x\n", u32Module, (u32)pState);
		return BSP_ERROR;
	}
	tick_begin = bsp_get_slice_value();
	tick_end = tick_begin + HI_TIMER_STAMP_CLK*u32TimeOut/100;
	/* Ŀǰֻ����usrAppInit��ʹ�ã�����������£�ʹ��ѭ����ѯЧ�ʽϸ�
       �����Ҫ֧�ֶ�������Ҫ�ʵ����ó�CPU */
	for(;;)
	{
		if(!sync_ctrl.g_pSyncLock[u32Module])
		{
			flag = SyncSpinLock();
			if(!sync_ctrl.g_pSyncLock[u32Module])
			{
				sync_ctrl.g_pSyncLock[u32Module] = 1;
				cache_sync();
				SyncSpinUnlock(flag);
				break;
			}
			else
			{
				SyncSpinUnlock(flag);
			}
		}
		if(u32TimeOut)
		{
			if(bsp_get_slice_value()>tick_end)
			{
				bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_Lock, timeout2, module=0x%x, u32TimeOut=0x%x\n", u32Module, u32TimeOut);
				return BSP_ERR_SYNC_TIMEOUT;
			}
		}
		SYNC_SLEEP(1);
	}
	/*lint -save -e571*/
	*pState = (u32)sync_ctrl.g_pSyncState[u32Module];
	/*lint -restore +e571*/
	return BSP_OK;
}


/*****************************************************************************
* �� �� ��      : BSP_SYNC_UnLock
*
* ��������  : ����������ģ���ʼ��״̬
*
* �������  : u32Module     ģ��
*                           u32State       ����ģ��״̬
*
* �������  : ��
*
* �� �� ֵ      : OK&ERROR
*
* ����˵��  : ��
*
*****************************************************************************/
int BSP_SYNC_UnLock(SYNC_MODULE_E u32Module, unsigned int u32State)
{
	 BSP_SYNC_Init();
	if(u32Module >= SYNC_MODULE_BUTT)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_UnLock, invalid param, module=0x%x\n", u32Module);
		return BSP_ERROR;
	}
	sync_ctrl.g_pSyncState[u32Module] = (char)u32State;
	sync_ctrl.g_pSyncLock[u32Module] = (char)0;
	return BSP_OK;
}
/*****************************************************************************
* �� �� ��     : BSP_SYNC_Wait
*
* ��������  : �Ӻ˵ȴ����˲�����ɺ���
*
* �������  : u32Module     ģ��
*                           u32TimeOut    ��ʱֵ��0Ϊ��Զ�ȴ���
*
* �������  : ��
*
* �� �� ֵ      : OK&ERROR
*
* ����˵��  : ��
*
*****************************************************************************/
int BSP_SYNC_Wait(SYNC_MODULE_E u32Module, unsigned int u32TimeOut)
{
	u32 tick_begin = 0,tick_end = 0;
	 BSP_SYNC_Init();

	if(u32Module >= SYNC_MODULE_BUTT)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_UnLock, invalid param, module=0x%x\n", u32Module);
		return BSP_ERROR;
	}
	tick_begin = bsp_get_slice_value();
	tick_end = tick_begin + HI_TIMER_STAMP_CLK*u32TimeOut/100;
	for(;;)
	{
		if(sync_ctrl.g_pSyncState[u32Module])
		{
			return BSP_OK;
		}
		if(u32TimeOut)
		{
			if(bsp_get_slice_value()>tick_end)
			{
				bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_Wait, timeout, module=0x%x, u32TimeOut=0x%x\n", u32Module, u32TimeOut);
				return BSP_ERR_SYNC_TIMEOUT;
			}
		}
		SYNC_SLEEP(1);
	}
}
/*****************************************************************************
* �� �� ��     : BSP_SYNC_Give
*
* ��������  : ����֪ͨ�Ӻ����˲����Ѿ����
*
* �������  :
* �������  : ��
*
* �� �� ֵ     : OK&ERROR
*
* ����˵��  : ��
*
*****************************************************************************/
int BSP_SYNC_Give(SYNC_MODULE_E u32Module)
{
	 BSP_SYNC_Init();

	if(u32Module >= SYNC_MODULE_BUTT)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SYNC,"BSP_SYNC_Give, invalid param, module=0x%x\n", u32Module);
		return BSP_ERROR;
	}
	sync_ctrl.g_pSyncState[u32Module] = 1;
	cache_sync();
	return BSP_OK;
}
/*lint -restore +e34 +e35*/
/*lint -save -e19*/
EXPORT_SYMBOL(BSP_SYNC_Lock);
EXPORT_SYMBOL(BSP_SYNC_UnLock);
EXPORT_SYMBOL(BSP_SYNC_Wait);
EXPORT_SYMBOL(BSP_SYNC_Give);
/*lint -restore +e19*/


