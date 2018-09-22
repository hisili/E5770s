

#ifndef __DRV_ANTEN_H__
#define __DRV_ANTEN_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include <drv_comm.h>
#include <drv_dpm.h>


/*****************************************************************************
 �� �� ��  : DRV_MNTN_GetExtAntenLockState
 ��������  : ��ȡ���������ߵ�����״̬
 �������  : None
 �������  : 0 - ��������
             1 - ��������
 �� �� ֵ  : 0 - �ɹ�
             ����Ϊʧ��

*****************************************************************************/
extern int drv_anten_lock_status_get(PWC_COMM_MODEM_E modem_id, unsigned int *status);
#define DRV_GET_ANTEN_LOCKSTATE(modem_id, status)    drv_anten_lock_status_get(modem_id, status)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_ExtAntenIntInstall
 ��������  : �ж�ע�ắ����������õ�ǰ������״̬
 �������  : routine   - �жϴ�����
             para      - �����ֶ�
 �������  : None
 �� �� ֵ  : void

*****************************************************************************/
extern void drv_anten_int_install(PWC_COMM_MODEM_E modem_id,void* routine, int para);
#define DRV_ANTEN_INT_INSTALL(modem_id, routine, para)    drv_anten_int_install(modem_id,routine, para)

extern int drv_anten_ipc_reg_fun(void);
#define BSP_MNTN_ANT_IFC_REGFUNC()    drv_anten_ipc_reg_fun()

#define BSP_MNTN_GetExtAntenLockState(modem_id, status) drv_anten_lock_status_get( modem_id, status)

#ifdef __cplusplus
}
#endif

#endif

