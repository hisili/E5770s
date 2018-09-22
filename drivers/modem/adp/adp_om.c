

#include "bsp_om_api.h"
#include "bsp_om.h"
#include "drv_comm.h"
#include "osl_irq.h"



/*****************************************************************************
* �� �� ��  : DRV_OM_SET_HSO_CONN_FLAG
*
* ��������  : flag :���ӱ�־��1��ʾ���ӣ�0��ʾ�Ͽ�
*
* �������  :��
*
*
* �������  :��
*
* �� �� ֵ  :��
*****************************************************************************/

BSP_VOID DRV_OM_SET_HSO_CONN_FLAG(BSP_U32 flag)
{
    bsp_om_set_hso_conn_flag(flag);
}

/*****************************************************************************
* �� �� ��  : DRV_SYSVIEW_SWT_SET
*
* ��������  :sysview�ϱ��������ã���װ�������ṩ��MSPʹ��
*
* �������  :tarce_type :trace����
*                        set_swt  :����ֵ
*                       period  :�ϱ�����
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK
*****************************************************************************/

BSP_U32 DRV_SYSVIEW_SWT_SET(BSP_U32 set_type,BSP_U32 set_swt,BSP_U32 period)
{
    return bsp_sysview_swt_set(set_type,set_swt,period);
}

/*****************************************************************************
* �� �� ��  : DRV_GET_ALL_TASK_ID_NAME
*
* ��������  :��ȡ��ǰ���������ID������
*
* �������  :p_task_stru:�������ƺ�ID����Ľṹ��
*                       param_len:����1�ĳ��ȣ���λ�ֽ�
*
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK
*****************************************************************************/
BSP_U32 DRV_GET_ALL_TASK_ID_NAME(BSP_VOID *p_task_stru,u32 param_len)
{
      return sysview_get_all_task_name((void *)p_task_stru,param_len );
}

/*****************************************************************************
* �� �� ��  : DRV_INT_LOCK
*
* ��������  :���жϽӿڣ��������ж�ͳ��
*
* �������  :��
*
* �������  : ��
*
* �� �� ֵ  : ���жϺ��õ�key
*****************************************************************************/
BSP_S32 DRV_INT_LOCK(BSP_VOID)
{
    unsigned long flags;

    local_irq_save(flags);

    bsp_int_lock_enter();
    return (BSP_S32)flags;
}

/*****************************************************************************
* �� �� ��  : DRV_INT_UNLOCK
*
* ��������  : �����жϽӿڣ��������ж�ͳ��
*
* �������  : ���жϺ��õ�key
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID DRV_INT_UNLOCK(BSP_S32 LockKey)
{
    unsigned long lock_key;

    lock_key = (unsigned long)LockKey;
    
    bsp_int_lock_out();

    local_irq_restore(lock_key);
}


/*****************************************************************************
* �� �� ��  : DRV_SOCP_CHAN_ENABLE
*
* ��������  : ����SOCPͨ��ʹ�ܲ���
*
* �������  : ��
*
*
* �������  :��
*
* �� �� ֵ  :��
*****************************************************************************/

BSP_VOID DRV_SOCP_CHAN_ENABLE(BSP_VOID)
{
    bsp_socp_chan_enable();
}





