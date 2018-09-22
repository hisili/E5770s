#include "drv_wakelock.h"
#include "drv_dpm.h"

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_PWRUP
 ��������  : Wģ��Gģ��Lģ��PA��RF��BBP��DSP��ABB��HIFI���ϵ���ơ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_RF/PWC_COMM_MODULE_BBP/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
BSP_U32 DRV_PWRCTRL_PWRUP(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId)
 {
    return PWC_COMM_MODEM_ON;
 }
/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_PWRDOWN
 ��������  : Wģ��Gģ��Lģ��PA��RF��BBP��DSP��ABB��HIFI���µ���ơ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_RF/PWC_COMM_MODULE_BBP/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_PWRDOWN (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId)
 {
    return PWC_COMM_MODEM_OFF;
 }
/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_PwrStatusGet
 ��������  : Wģ��Gģ��Lģ��PA��RF��BBP��DSP��ABB�����µ�״̬��ѯ��
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_RF/PWC_COMM_MODULE_BBP/PWC_COMM_MODULE_BBE16/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWRCTRL_GET_SUCCESS/PWRCTRL_GET_PARAINVALID/PWRCTRL_ONORLOCK/PWRCTRL_OFFORUNLOCK
*****************************************************************************/
  BSP_U32 DRV_PWRCTRL_PWRSTATUSGET(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId)
 {
	return 0;
 }

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_PLL_ENABLE
 ��������  : Wģ��Gģ��Lģ��PA��DSP��ABB��PLLʹ�ܡ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_PLLENABLE (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem)
 {
	return PWC_COMM_MODEM_ON;
 }

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_PLL_DISABLE
 ��������  : Wģ��Gģ��Lģ��PA��DSP��ABB��PLLȥʹ�ܡ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_PLL_DISABLE (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem)
 {
	return PWC_COMM_MODEM_OFF;
 }
/*****************************************************************************
* �� �� ��  : DRV_PWRCTRL_DSP_RESET
* ��������  : Lģ��DSP��λ�ӿ�
* �������  :
* �������  :
* �� �� ֵ  :
*****************************************************************************/
 int  DRV_PWRCTRL_DSP_RESET(void)
 {
	return 0;
 }


/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_PllStatusGet
 ��������  : Wģ��Gģ��Lģ��PA��DSP��ABB��PLL״̬��ѯ��
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWRCTRL_GET_SUCCESS/PWRCTRL_GET_PARAINVALID/PWRCTRL_ONORLOCK/PWRCTRL_OFFORUNLOCK
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_PLLSTATUSGET (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem)
 {
	return 0;
 }

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_SLEEPVOTE_LOCK
 ��������  : �����ֹ˯��ͶƱ�ӿڡ�
 �������  : enClientId:PWC_CLIENT_ID_E
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_SLEEPVOTE_LOCK(PWC_CLIENT_ID_E enClientId)
 {
	return 0;
 }

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_SLEEPVOTE_UNLOCK
 ��������  : ��������˯��ͶƱ�ӿڡ�
 �������  : enClientId:PWC_CLIENT_ID_E
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_SLEEPVOTE_UNLOCK(PWC_CLIENT_ID_E enClientId)
 {
	return 0;
 }


/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_StandbyStateCcpu/BSP_PWRCTRL_StandbyStateAcpu
 ��������  : AT^PSTANDBY
 �������  :
 �������  :
 ����ֵ��
*****************************************************************************/
 unsigned int BSP_PWRCTRL_StandbyStateAcpu(unsigned int ulStandbyTime, unsigned int ulSwitchTime)
 {
	return 0;
 }
 unsigned int BSP_PWRCTRL_StandbyStateCcpu(unsigned int ulStandbyTime, unsigned int ulSwitchTime)
 {
	return 0;
 }

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_RFLdoDown
 ��������  : ���ӿ�ʵ��WCDMA��GSM RF LDO�µ硣
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
void BSP_GUSYS_RFLdoDown(void)
{

}
/*****************************************************************************
 �� �� ��  : BSP_GUSYS_RFLdoOn
 ��������  : ���ӿ�ʵ��WCDMA��GSM RF LDO�ϵ硣
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
void BSP_GUSYS_RFLdoOn(void)
{

}

 /*****************************************************************************
 �� �� ��  : BSP_GUSYS_BBPAutoAdjust
 ��������  : ��ʼ��ABB����У׼ʹ��
 �������  : uiSysMode��0��WCDMAģʽ��1��GSMģʽ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
int  BSP_GUSYS_BBPAutoAdjust(unsigned char ucAdjustMode)
{
    return OK;
}


