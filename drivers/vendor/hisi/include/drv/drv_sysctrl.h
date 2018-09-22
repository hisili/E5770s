

#ifndef __DRV_SYSCTRL_H__
#define __DRV_SYSCTRL_H__

#include "drv_comm.h"


/*************************SYSCTRL START*******************************/


/*****************************************************************************
 �� �� ��  : DRV_SYSCTRL_REG_SET
 ��������  : sysctrlд�ӿڹ�GU�������á�
 �������  : regAddr:SC�Ĵ���ƫ�Ƶ�ַ;setData:SC�Ĵ���ֵ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_SYSCTRL_REG_SET(unsigned int regAddr, unsigned int setData);
#define DRV_SYSCTRL_REG_SET(regAddr, setData)	BSP_SYSCTRL_REG_SET(regAddr, setData)

/*****************************************************************************
 �� �� ��  : DRV_SYSCTRL_REG_GET
 ��������  : sysctrl���ӿڹ�GU�������á�
 �������  : regAddr:SC�Ĵ���ƫ�Ƶ�ַ;getData:���ص�SC�Ĵ���ֵ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_SYSCTRL_REG_GET(unsigned int regAddr, unsigned int * getData);
#define DRV_SYSCTRL_REG_GET(regAddr, getData)	BSP_SYSCTRL_REG_GET(regAddr, getData)

/*************************SYSCTRL START*******************************/

#endif

