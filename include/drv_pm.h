
#ifndef __DRV_PM_H__
#define __DRV_PM_H__

#include <drv_comm.h>

typedef enum pm_wake_src
{
    DRV_WAKE_SRC_UART0 = 0, /*for acore at_uart*/
    DRV_WAKE_SRC_SOCP ,     /*for acore sd_log*/
    DRV_WAKE_SRC_DRX_TIMER, /*for ccore drx timer*/
    DRV_WAKE_SRC_BUT,
}DRV_PM_WAKE_SRC_ENUM;

/*******************************************************************************
  ������:       BSP_VOID DRV_PM_SET_WAKE_SRC(DRV_PM_WAKE_SRC_ENUM wake_src)
  ��������:     ��̬���û���Դ
  �������:     wake_src  ����Դö��ֵ
  �������:     ��
  ����ֵ:       ��
*******************************************************************************/
BSP_VOID DRV_PM_SET_WAKE_SRC(DRV_PM_WAKE_SRC_ENUM wake_src);

/*******************************************************************************
  ������:       BSP_VOID DRV_PM_SET_WAKE_SRC(DRV_PM_WAKE_SRC_ENUM wake_src)
  ��������:     ��̬ȡ������Դ������
  �������:     wake_src  ����Դö��ֵ
  �������:     ��
  ����ֵ:       ��
*******************************************************************************/
BSP_VOID DRV_PM_UNSET_WAKE_SRC(DRV_PM_WAKE_SRC_ENUM wake_src);


/*****************************************************************************
* �� �� ��  : DRV_SET_DRX_TIMER_WAKE_SRC
* ��������  : ���� DRX timer ��Ϊ����Դ
* �������  :
* �������  :
* �� �� ֵ   :
* �޸ļ�¼  :
*****************************************************************************/
BSP_VOID DRV_SET_DRX_TIMER_WAKE_SRC(BSP_VOID);

/*****************************************************************************
* �� �� ��  : DRV_SET_DRX_TIMER_WAKE_SRC
* ��������  : ȡ������ DRX timer ��Ϊ����Դ
* �������  :
* �������  :
* �� �� ֵ   :
* �޸ļ�¼  :
*****************************************************************************/
BSP_VOID DRV_DEL_DRX_TIMER_WAKE_SRC(BSP_VOID);


/* adp */


/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_DEEPSLEEP_FOREVER
 ��������  : AARM CARM �µ�ӿ�
 �������  : None
 �������  : None
 �� �� ֵ  : None

*****************************************************************************/
extern void DRV_PWRCTRL_DEEPSLEEP_FOREVER(void );

typedef struct
{
    PWRCTRLFUNCPTR drx_slow;
} PWC_SLEEP_CALLBACK_STRU;

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_SLEEP_CALLBACK_REG
 ��������  : ע��PWC����������ʹ��
 �������  : ��ע��ĺ���
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int DRV_PWRCTRL_SLEEP_CALLBACK_REG(PWC_SLEEP_CALLBACK_STRU pCallback);


typedef struct
{
    PWRCTRLFUNCPTRVOID  pFuncDsIn;
    PWRCTRLFUNCPTRVOID  pFuncDsOut;
}PWC_DS_SOCP_CB_STRU;

typedef unsigned long (*pULULFUNCPTR)( unsigned long ulPara );

typedef struct
{
    pULULFUNCPTR pRestoreFunction;
    pULULFUNCPTR pEnableFunction;
    pULULFUNCPTR pDisableFunction;
    pFUNCPTR2    pDfsSetFunc;
    pULULFUNCPTR pDfsReleaseFunc;
}DPM_SLEEP_CALLBACK_STRU;

/*****************************************************************************
Function:   DRV_PWRCTRL_SLEEP_IN_CB
Description:
Input:
Output:     None;
Return:
Others:
*****************************************************************************/
 int DRV_PWRCTRL_SLEEP_IN_CB(PWC_DS_SOCP_CB_STRU stFunc);



#endif

