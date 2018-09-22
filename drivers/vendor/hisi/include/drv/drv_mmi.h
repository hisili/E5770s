

#ifndef __DRV_MMI_H__
#define __DRV_MMI_H__

#include "drv_comm.h"

/*************************MMI START*****************************/

/***************************************************************
*  ������        :   BSP_MMI_TestResultSet
*  ��������      :   ���ӿ��ǽ�MMI�Ĳ��Ա�־д��NV
                     ��ulFlag == 1 ��д�� ��ST P��
                     ��ulFlag == 0 ��д�� ��ST F��
*  �������      :   BSP_U32 ulFlag
*  �������      :   ��
*  ����ֵ        :   �ɹ�(0)  ʧ��(-1)
***************************************************************/
int BSP_MMI_TestResultSet(unsigned int ulFlag);
#define DVR_MMI_TEST_RESULT_SET(ulFlag) BSP_MMI_TestResultSet(ulFlag)

/***************************************************************
*  ������        :   BSP_MMI_TestResultGet
*  ��������      :   ���ӿڱȽ�MMI NV�е��Ƿ��ǡ�ST P��
                                  �Ƿ���1   ���Ƿ���0
*  �������      :   ��
*  �������      :   ��
*  ����ֵ        :   �ɹ�(1)  ʧ��(0)
***************************************************************/
unsigned int BSP_MMI_TestResultGet(void);
#define DVR_MMI_TEST_RESULT_GET() BSP_MMI_TestResultGet()

/*************************MMI END*****************************/

#endif

