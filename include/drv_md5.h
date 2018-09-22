

#ifndef __DRV_MD5_H__
#define __DRV_MD5_H__

#include "drv_comm.h"

/*************************MD5��� START*******************************/

/*****************************************************************************
 �� �� ��  : VerifySIMLock
 ��������  : �жϵ�ǰ�������Ƿ���ȷ .
 �������  : imei       - ����IMEI��
             unlockcode - ������
 �������  : �ޡ�
 �� �� ֵ  : 1��   �����ɹ�
             0:    ����ʧ��
*****************************************************************************/
extern int VerifySIMLock(char* UnlockCode, char* Key);
#define DRV_CARDLOCK_MD5_VERIFY(unlockcode, imei)  VerifySL(unlockcode, imei)
#ifdef CONFIG_SIMLOCK_2_1
extern int VerifySL(char* UnlockCode, char* Key);
#endif


extern int GetAuthVer(void);
#define DRV_GET_AUTH_VER()  GetAuthVer()

/*************************MD5��� END*********************************/

#endif

