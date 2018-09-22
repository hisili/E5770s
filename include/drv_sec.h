

#ifndef __DRV_SEC_H__
#define __DRV_SEC_H__

#include "drv_comm.h"


/*************************SEC START***********************************/

/*************************************************
 �� �� ��   : BSP_SEC_Support
 ��������   : ��ǰ�汾�Ƿ�֧�ְ�ȫ����
 �������   : unsigned char *pData
 �������   : unsigned char *pData
 �� �� ֵ   : OK/ERROR
*************************************************/
extern BSP_S32 BSP_SEC_Support(BSP_U8 *pu8Data);
#define DRV_SECURE_SUPPORT(pu8Data) BSP_SEC_Support(pu8Data)

/*************************************************
 �� �� ��   : BSP_SEC_AlreadyUse
 ��������   : ��ѯ��ǰ�汾�Ƿ��Ѿ����ð�ȫ����
 �������   : unsigned char *pData
 �������   : unsigned char *pData
 �� �� ֵ   : OK/ERROR
*************************************************/
extern BSP_S32 BSP_SEC_AlreadyUse(BSP_U8 *pu8Data);
#define DRV_SECURE_ALREADY_USE(pu8Data) BSP_SEC_AlreadyUse(pu8Data)

/*************************************************
 �� �� ��   : BSP_SEC_Start
 ��������   : ���ð�ȫ����
 �������   :
 �������   :
 �� �� ֵ   : OK/ERROR
*************************************************/
extern BSP_S32 BSP_SEC_Start(void);
#define DRV_START_SECURE() BSP_SEC_Start()


extern BSP_S32 BSP_SEC_Check(void);
#define DRV_SEC_CHECK() BSP_SEC_Check()

#if (FEATURE_ON == MBB_COMMON)

extern BSP_U8 drv_secboot_check(void);
#define DRV_SECBOOT_CHECK() drv_secboot_check()


extern void bsp_secboot_check(void);
#endif
/*************************SEC END*************************************/

#endif

