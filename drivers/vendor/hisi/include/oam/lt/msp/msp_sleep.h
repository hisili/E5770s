//*****************************************************************************
//  �� �� ��   : msp_drx.h
//  �� �� ��   : V1.0
//  �޸���ʷ   :
//    �޸����� : �����ļ�
//*****************************************************************************
#ifndef __MSP_DRX_H__
#define __MSP_DRX_H__

#include "vos.h"
#include <DrvInterface.h>

extern VOS_BOOL MSP_IsSleepReady_Acpu(VOS_VOID);
extern VOS_BOOL MSP_IsSleepReady_Mcpu(VOS_VOID);
extern VOS_VOID TLSLEEP_ActivateHw(PWC_COMM_MODE_E modeid);

#endif


