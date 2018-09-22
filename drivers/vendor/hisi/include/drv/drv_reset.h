

#ifndef __DRV_RESET___
#define __DRV_RESET___

#include "drv_comm.h"

/*����������Modem/HIFI��λǰ���Ǹ�λ����ûص�����*/
typedef enum
{
	DRV_RESET_CALLCBFUN_RESET_BEFORE,   /*Modem/HIFI ��λǰ*/
	DRV_RESET_CALLCBFUN_RESET_AFTER,    /*Modem/HIFI ��λ��*/
	DRV_RESET_CALLCBFUN_RESETING,       /*Modem/HIFI ��λ��*/
	DRV_RESET_CALLCBFUN_MOEMENT_INVALID
} DRV_RESET_CALLCBFUN_MOMENT;

/*****************************************************************************
 �� �� ��  : pdrv_reset_cbfun
 ��������  : �����Ҫע��Ļص���������.
 �������  : DRV_RESET_CALLCBFUN_MOMENT eparam,��ʾ��λǰ���Ǹ�λ��,
             int userdata,�û�����
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             ��0������ʧ�ܡ�
*****************************************************************************/
typedef int (*pdrv_reset_cbfun)(DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata);

/*****************************************************************************
 �� �� ��  : ccorereset_regcbfunc
 ��������  : �ṩ�ϲ�Ӧ�ó���ע��Modem������λǰ/��Ļص��ӿں�����
 �������  : pname���ϲ����ע������֣�ע�ⲻ�����������9���ַ���������洢��
             pcbfun���ص�����ָ�롣
             userdata:�ϲ�������ݣ��ڵ��ûص�����ʱ����Ϊ��δ����û���
             priolevel: �ص������������ȼ���enum DRV_RESET_CALLCBFUN_PIOR�����ֵ��ֵԽС,���ȼ�Խ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int ccorereset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
#define DRV_CCORERESET_REGCBFUNC(pname,pcbfun, userdata, priolevel)\
                ccorereset_regcbfunc(pname,pcbfun, userdata, priolevel)

/*****************************************************************************
 �� �� ��  : hifireset_regcbfunc
 ��������  : �ṩ�ϲ�Ӧ�ó���ע��HIFI������λ�Ļص��ӿں�����
 �������  : pname���ϲ����ע������֣�ע�ⲻ�����������9���ַ���������洢��
             pcbfun���ص�����ָ�롣
             puserdata:�ϲ�������ݣ��ڵ��ûص�����ʱ����Ϊ��δ����û���
             priolevel: �ص������������ȼ���0-49
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
#define DRV_HIFIRESET_REGCBFUNC(pname,pcbfun, userdata, priolevel)\
                hifireset_regcbfunc(pname,pcbfun, userdata, priolevel)

/*****************************************************************************
 �� �� ��  : BSP_CCPU_Rest_Over
 ��������  : C�˵�����λ�ɹ���COMM������øú�������֪ͨACPU��
 �������  : ��
 �������  : ��
 ʹ��CPU   : CCPU
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_CCPU_Rest_Over(void);
#define DRV_CCPU_RESET_OVER()\
                BSP_CCPU_Rest_Over()

/*****************************************************************************
 �� �� ��  : modem_state_set
 ��������  : �ṩttf����modem״̬��API
 �������  : unsigned int state
 �������  : ��
 �� �� ֵ  : <0     failed,invalid state
             =0     success
*****************************************************************************/
extern int modem_state_set(unsigned int state);
#define DRV_MODEM_STATE_SET(state)\
                modem_state_set(state)

#endif /* end of drv_reset.h */

