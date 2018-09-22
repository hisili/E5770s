

#ifndef __DRV_DPM_H__
#define __DRV_DPM_H__

#include "drv_comm.h"


/*************************DPM START***********************************/
#ifndef PWC_SUCCESS
#define PWC_SUCCESS        0
#endif

#ifndef PWC_PARA_INVALID
#define PWC_PARA_INVALID				0x1
#endif

/* ����ֵ���� */
typedef enum
{
    RET_ERR_PARAM_NULL = -0xF000,
    RET_ERR_PARAM_INVALID,
    RET_ERR_OVERFLOW,
    RET_ERR_INSUFFICIENT,
    RET_ERR_LIMITED,
    RET_ERR_NOT_FOUND,
    RET_ERR_NOT_OPEN,
    RET_ERR_DUPLICATE,
    RET_ERR_CONNECT_FAIL,
    RET_ERR_TIME_OUT,
    RET_ERR_UNKNOWN,
    RET_ERR = -1,
    RET_OK = 0
} EM_PWC_RET;

#define PWRCTRL_GET_SUCCESS         (0x00)
#define PWRCTRL_GET_PARAINVALID     (0x01)
#define PWRCTRL_ONORLOCK            (0x10)
#define PWRCTRL_OFFORUNLOCK         (0x20)


typedef enum tagPWC_COMM_MODE_E
{
    PWC_COMM_MODE_GSM,
    PWC_COMM_MODE_WCDMA,
    PWC_COMM_MODE_LTE,
    PWC_COMM_MODE_TDS,
    PWC_COMM_MODE_LCIPHER,
    PWC_COMM_MODE_BUTT
}PWC_COMM_MODE_E;

typedef enum tagPWC_COMM_MODULE_E
{
    PWC_COMM_MODULE_PA,
    PWC_COMM_MODULE_RF,
    PWC_COMM_MODULE_BBE16,
    PWC_COMM_MODULE_BBP_DRX,
    PWC_COMM_MODULE_BBP_DPA,
    PWC_COMM_MODULE_BBP_MEM,
    PWC_COMM_MODULE_ABB,

    /*GU��OAM����ʹ������ö��*/
    PWC_COMM_MODULE_BBP_PWR,
    PWC_COMM_MODULE_DSP,
    PWC_COMM_MODULE_BBP_SOC,
    PWC_COMM_MODULE_BUTT
}PWC_COMM_MODULE_E;

typedef enum tagPWC_COMM_MODEM_E
{
    PWC_COMM_MODEM_0=0,
    PWC_COMM_MODEM_1=1,
    PWC_COMM_MODEM_BUTT
}PWC_COMM_MODEM_E;

typedef enum tagPWC_COMM_STATUS_E
{
    PWC_COMM_MODEM_ON = 0x10,
    PWC_COMM_MODEM_OFF = 0x20,
/* for v9r1 compact */
    PWRCTRL_COMM_ON = 0x10,
    PWRCTRL_COMM_OFF = 0x20,
    PWC_COMM_STATUS_BUTT
}PWC_COMM_STATUS_E;

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_PWRUP
 ��������  : Wģ��Gģ��Lģ��PA��RF��BBP��DSP��ABB��HIFI���ϵ���ơ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_RF/PWC_COMM_MODULE_BBP/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_PWRUP (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_PWRDOWN
 ��������  : Wģ��Gģ��Lģ��PA��RF��BBP��DSP��ABB��HIFI���µ���ơ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_RF/PWC_COMM_MODULE_BBP/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_PWRDOWN (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_PwrStatusGet
 ��������  : Wģ��Gģ��Lģ��PA��RF��BBP��DSP��ABB�����µ�״̬��ѯ��
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_RF/PWC_COMM_MODULE_BBP/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWRCTRL_GET_SUCCESS/PWRCTRL_GET_PARAINVALID/PWRCTRL_ONORLOCK/PWRCTRL_OFFORUNLOCK
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_PWRSTATUSGET(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_PLL_ENABLE
 ��������  : Wģ��Gģ��Lģ��PA��DSP��ABB��PLLʹ�ܡ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_PLLENABLE(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem);

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_PLL_DISABLE
 ��������  : Wģ��Gģ��Lģ��PA��DSP��ABB��PLLȥʹ�ܡ�
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWC_PARA_INVALID/PWC_SUCCESS
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_PLLDISABLE (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem);


/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_PllStatusGet
 ��������  : Wģ��Gģ��Lģ��PA��DSP��ABB��PLL״̬��ѯ��
 �������  : enCommMode: PWC_COMM_MODE_WCDMA/PWC_COMM_MODE_GSM/PWC_COMM_MODE_LTE,
             enCommModule:PWC_COMM_MODULE_PA/PWC_COMM_MODULE_DSP/PWC_COMM_MODULE_ABB,
 �������  : None
 �� �� ֵ  : PWRCTRL_GET_SUCCESS/PWRCTRL_GET_PARAINVALID/PWRCTRL_ONORLOCK/PWRCTRL_OFFORUNLOCK
*****************************************************************************/
BSP_U32 DRV_PWRCTRL_PLLSTATUSGET (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem);

/***************************************************************************
 �� �� ��  : DRV_PWRCTRL_BBPCLKENABLE()
 ��������  : TCXO ��ʱ������
 �������  : enModeId      ͨ��ģʽ
    	                     enModuleId    ͨ��ģ��
    	                     enModemId    ����
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
                         RET_ERR        ʧ��
**************************************************************************/
BSP_S32	DRV_PWRCTRL_BBPCLKENABLE(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);

/***************************************************************************
 �� �� ��  : DRV_PWRCTRL_BBPCLKDISABLE()
 ��������  : TCXO ��ʱ������
 �������  : enModeId      ͨ��ģʽ
    	                     enModuleId    ͨ��ģ��
    	                     enModemId    ����
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
                         RET_ERR        ʧ��
**************************************************************************/
BSP_S32	DRV_PWRCTRL_BBPCLKDISABLE(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId);


#endif

