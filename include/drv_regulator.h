
#ifndef __DRV_REGULATOR_H__
#define __DRV_REGULATOR_H__

#include "drv_comm.h"

#ifndef __CMSIS_RTOS

struct regulator;
/*************************REGULATOR BEGIN***********************************/


/*****************************************************************************
*�� �� ��  : regulator_get
* ��������  :���Ҳ����regulator�����ں��������в�������ʼ��ʱ����
* �������  :dev:�豸�ṹ�壬������ΪNULL
* �������  :id:regulator��id��regulator�ṩ�����֣�ͨ��id�������Ӧ��regulator
* ����ֵ��   A��:
*			 �ɹ�:��õ�regulator�ṹ��ָ��
*            ʧ��:ID_ERR()�ܴ����errno
*			 C��:
*			 �ɹ�:��õ�regulator�ṹ��ָ��
*            ʧ��:NULL
*ע         :��ģ���ʼ��ʱ��ȡregulator��ע��ʱ�ͷ�regulator
*            ��ȡregulatorʧ����Ҫ��ģ�������Ӧ�Ĵ������ʼ��ʧ��
*****************************************************************************/
/* regulator get and put */
#ifdef __KERNEL__
extern struct regulator *regulator_get(struct device *dev, const char *id);
#elif defined(__VXWORKS__)


extern struct regulator *regulator_get(unsigned char *name, char *supply);
#endif

/*****************************************************************************
*�� �� ��  : regulator_put
*��������  : �ͷ�regulator��Դ���ͷ�ǰ��ȷ��regulator_enable(),regulator_disable()
*			 �ɶ�ʹ��
*�������  : regulator��Դ
*����ֵ	   ��
*
*****************************************************************************/
extern void regulator_put(struct regulator *regulator);

/*****************************************************************************
*�� �� ��  : regulator_enable
*��������  : ʹ��regulator�������regulator_disable()�ɶ�ʹ��
*�������  : regulator��Դ
*����ֵ	   ���ɹ�: >= 0
*			 ʧ��: < 0
*ע		   : enable/disable ��Ҫ���سɶ�ʹ��Լ�� ����Ҫ����ʹ�ܣ��󷽿�ȥʹ��
*			 ��ʹ�ܡ�ȥʹ���ܴ���Ӧ��ͬ
*			 �������������regulator_is_enabled�жϵ�ǰ״̬����Լ��ʹ��
*****************************************************************************/
extern int regulator_enable(struct regulator *regulator);
/*****************************************************************************
*�� �� ��  : regulator_disable
*��������  : ȥʹ��regulator�������regulator_enable()�ɶ�ʹ��
*�������  : regulator��Դ
*����ֵ	   ���ɹ�: >= 0
*			 ʧ��: < 0
*ע		   : enable/disable ��Ҫ���سɶ�ʹ��Լ�� ����Ҫ����ʹ�ܣ��󷽿�ȥʹ��
*			 ��ʹ�ܡ�ȥʹ���ܴ���Ӧ��ͬ
*			 �������������regulator_is_enabled�жϵ�ǰ״̬����Լ��ʹ��
*****************************************************************************/
extern int regulator_disable(struct regulator *regulator);
/*****************************************************************************
*�� �� ��  : regulator_is_enabled
*��������  : regulator�Ƿ���ʹ��
*�������  : regulator��Դ
*����ֵ	   ���ɹ�: > 0
*			 ʧ��: = 0
*****************************************************************************/
extern int regulator_is_enabled(struct regulator *regulator);
/*****************************************************************************
*�� �� ��  : regulator_get_voltage
*��������  : ��ȡregulator��ǰ��ѹ
*�������  : regulator��Դ
*����ֵ	   ���ɹ�:��ǰ��ѹֵ
*			 ʧ��:����
*****************************************************************************/
extern int regulator_get_voltage(struct regulator *regulator);
/*****************************************************************************
*�� �� ��  : regulator_set_voltage
*��������  : ����regulator��ѹ
*�������  : regulator��Դ��min_uV��max_uVҪ���õĵ�ѹֵ
*����ֵ	   ���ɹ�:0
*			 ʧ��:����
*****************************************************************************/
extern int regulator_set_voltage(struct regulator *regulator, int min_uV, int max_uV);

/*ģʽ���� NORMAL :�������� IDLE :��regulator����ecoģʽ*/
#ifndef REGULATOR_MODE_NORMAL
#define REGULATOR_MODE_NORMAL		0x2
#endif
#ifndef REGULATOR_MODE_IDLE
#define REGULATOR_MODE_IDLE			0x4
#endif
/*****************************************************************************
*�� �� ��  : regulator_set_mode/regulator_get_mode
*��������  : ���û�ȡregulatorģʽ
*�������  : regulator��Դ��modeҪ���õ�ģʽ
*����ֵ	   ���ɹ�:0
*			 ʧ��:����
*ע        : regulator��ʱֻ�ṩ���ء����õ�ѹ�ȹ��ܣ����û�ȡmode�����ݲ�ʵ��
*****************************************************************************/
extern int regulator_set_mode(struct regulator *regulator, unsigned int mode);

extern unsigned int regulator_get_mode(struct regulator *regulator);

#endif /* __CMSIS_RTOS*/

#endif

