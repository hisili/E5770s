/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : adp_pm.c */
/* Version       : 1.0 */
/* Created       : 2013-09-26*/
/* Last Modified : */
/* Description   :  pm adp*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#include <drv_pm.h>
#include <bsp_pm.h>

/*
set&unset wakeup interrupt source
input : wake_src defined in drv_pm.h [DRV_PM_WAKE_SRC_ENUM]
*/
BSP_VOID DRV_PM_SET_WAKE_SRC(DRV_PM_WAKE_SRC_ENUM wake_src)
{
    return;
}

BSP_VOID DRV_PM_UNSET_WAKE_SRC(DRV_PM_WAKE_SRC_ENUM wake_src)
{

    return;
}


/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_DEEPSLEEP_FOREVER
 ��������  : AARM CARM �µ�ӿ�
 �������  : None
 �������  : None
 �� �� ֵ  : None

*****************************************************************************/
 void DRV_PWRCTRL_DEEPSLEEP_FOREVER(void )
 {}

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_SLEEP_CALLBACK_REG
 ��������  : ע��PWC����������ʹ��
 �������  : ��ע��ĺ���
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
 int DRV_PWRCTRL_SLEEP_CALLBACK_REG(PWC_SLEEP_CALLBACK_STRU pCallback)
 {
	return 0;
 }


/*****************************************************************************
Function:   DRV_PWRCTRL_SLEEP_IN_CB
Description:
Input:
Output:     None;
Return:
Others:
*****************************************************************************/
 int DRV_PWRCTRL_SLEEP_IN_CB(PWC_DS_SOCP_CB_STRU stFunc)
 {
	return 0;
 }


