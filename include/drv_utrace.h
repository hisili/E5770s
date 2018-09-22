

#ifndef _DRV_UTRACE_H
#define _DRV_UTRACE_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "drv_comm.h"


/*****************************************************************************
 �� �� ��  : DRV_UTRACE_START
 ��������  : USB Trace�����ӿ�, ����Trace�ɼ�
 �������  : pData: Trace�ɼ��������ݽṹ�׵�ַ
 �������  : �ޡ�
 �� �� ֵ  : �ɹ�:0 ʧ��:��0
*****************************************************************************/
BSP_U32 DRV_UTRACE_START(BSP_U8 * pData);

/*****************************************************************************
 �� �� ��  : DRV_UTRACE_TERMINATE
 ��������  : USB Trace��ֹ�ӿڣ�ֹͣ�����쳣����
 �������  : pData  : Trace��ֹ���ݽṹָ��          
 �������  : ��
 �� �� ֵ  : �ɹ�:0 ʧ��:��0
*****************************************************************************/
BSP_U32 DRV_UTRACE_TERMINATE(BSP_U8 * pData);

#ifdef __cplusplus
}
#endif

#endif /* end of _DRV_UTRACE_H*/

