

#ifndef __DRV_BBP_H__
#define __DRV_BBP_H__

#include "drv_comm.h"
#include "drv_dpm.h"

/*����bbp����ʱ�� ��ѯ��֡�ŵȽӿڵķ���ֵ*/
#define BBP_POWER_DOWN_BACK 0xffff
#define BBP_TDS_STU_SFN_MASK 0x1fff

#define BSP_BBP_POWER_DOWN BBP_POWER_DOWN_BACK

typedef BSP_VOID (*BSPBBPIntDlTbFunc)(BSP_VOID);
typedef BSP_VOID (*BSPBBPIntTimerFunc)(BSP_VOID);
typedef BSP_VOID (*BSPBBPIntTdsFunc)(BSP_VOID);

/*****************************************************************************
* ����  : BSP_BBPIntTimerRegCb
* ����  : ��PS���ã����������ע��1ms��ʱ�жϵĻص�
* ����  : pfunc
* ���  : void
* ����  : void
*****************************************************************************/
BSP_VOID BSP_BBPIntTimerRegCb(BSPBBPIntTimerFunc pFunc);

/*****************************************************************************
* ����  : bsp_bbp_dltbintregcb
* ����  : ��PS���ã����������ע������������������жϵĻص�
* ����  : pfunc
* ���  : void
* ����  : void
*****************************************************************************/
BSP_VOID BSP_BBPIntDlTbRegCb(BSPBBPIntDlTbFunc pFunc);

/*****************************************************************************
* �� ��: BSP_BBPIntTimerClear
* �� ��: ��PS���ã��������1ms��ʱ�ж�
* ���� : void
* ��� : void
* �� ��: void
*****************************************************************************/
BSP_VOID BSP_BBPIntTimerClear(void);

/*****************************************************************************
* �� ��: BSP_BBPIntTimerEnable
* �� ��: ��PS���ã�������1ms��ʱ�ж�
* ���� : void
* ��� : void
* ���� : int
*****************************************************************************/
BSP_S32 BSP_BBPIntTimerEnable(void);

/*****************************************************************************
* �� ��: BSP_BBPIntTimerDisable
* �� ��: ��PS���ã������ر�1ms��ʱ�ж�
* ���� : void
* ��� : void
* �� ��: void
*****************************************************************************/
BSP_VOID BSP_BBPIntTimerDisable(void);

/*****************************************************************************
* ����  : BSP_BBPGetCurTime
* ����  : ��PS���ã�������ȡϵͳ��ȷʱ��
* ����  : void
* ���  : u64 *pcurtime
* ����  : u32
*****************************************************************************/
BSP_U32 BSP_BBPGetCurTime(BSP_U64 *pCurTime);

/*****************************************************************************
* ����  : BSP_BBPGetCurTime
* ����  : ��ȡBBP��ʱ����ֵ������OAM ʱ��
* ����  : void
* ���  :
			pulLow32bitValueָ���������Ϊ�գ�����᷵��ʧ�ܡ�
			pulHigh32bitValue���Ϊ�գ� ��ֻ���ص�32bit��ֵ��
* ����  : int
*****************************************************************************/
int DRV_GET_BBP_TIMER_VALUE(unsigned int  *pulHigh32bitValue,  unsigned int  *pulLow32bitValue);

/*****************************************************************************
* ����  : bsp_bbp_getsysframe
* ����  : get system frame num
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
BSP_U16 BSP_GetSysFrame(BSP_VOID);

/*****************************************************************************
* ����  : bsp_bbp_getsyssubframe
* ����  : get system sub frame num
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
BSP_U16 BSP_GetSysSubFrame(BSP_VOID);

/*****************************************************************************
* ����  : BSP_GetTdsSubFrame
* ����  : get tds system sub frame num
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
BSP_U16 BSP_GetTdsSubFrame(BSP_VOID);
#define DRV_GET_TDS_SUB_FRAME()  BSP_GetTdsSubFrame()

/*****************************************************************************
* ����  : BSP_SetTdsSubFrameOffset
* ����  : set tds system sub frame offset
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
BSP_U16 BSP_SetTdsSubFrameOffset(BSP_U16 usOffset);
#define DRV_SET_TDS_SUB_FRAME_OFFSET(usOffset)  BSP_SetTdsSubFrameOffset(usOffset)

/*****************************************************************************
* ����  : BSP_SetTdsSubFrameOffset
* ����  : set tds system sub frame offset
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
BSP_U32 BSP_GetTdsSleepTime(BSP_VOID);
#define DRV_GET_TDS_SLEEP_TIME()  BSP_GetTdsSleepTime()

/*****************************************************************************
* ����  : BSP_BBPIntTdsTFRegCb
* ����  : regist callback
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
BSP_VOID BSP_BBPIntTdsTFRegCb(BSPBBPIntTdsFunc pFunc);

/*****************************************************************************
* ����  : BSP_BBPIntTdsTFEnable 
* ����  : enable tdstf
* ����  : void
* ���  : viod
* ����  : u32
*****************************************************************************/
BSP_S32 BSP_BBPIntTdsTFEnable(BSP_VOID);

/*****************************************************************************
* ����  : BSP_BBPIntTdsTFDisable
* ����  : disable tdstf
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
BSP_VOID BSP_BBPIntTdsTFDisable(BSP_VOID);

/*****************************************************************************
* ����  : DRV_BBPWAKE_INT_ENABLE
* ����  : enable bbp wakeup int
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
BSP_VOID DRV_BBPWAKE_INT_ENABLE(PWC_COMM_MODE_E mode);

/*****************************************************************************
* ����  : BSP_GetTdsClkSwitchStatus
* ����  : get tdsclk switch
* ����  : void
* ���  : 0��ʾ�л���ϵͳʱ�ӣ�1��ʾ�л���32kʱ��
* ����  : void
*****************************************************************************/
BSP_S32 BSP_GetTdsClkSwitchStatus(BSP_VOID);
#define DRV_GET_TDS_CLK_STATUS()   BSP_GetTdsClkSwitchStatus()

/*****************************************************************************
* ����  : DRV_BBPWAKE_INT_DISABLE
* ����  : disable bbp wakeup int
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
BSP_VOID DRV_BBPWAKE_INT_DISABLE(PWC_COMM_MODE_E mode);

/*****************************************************************************
* ����  : DRV_BBPWAKE_INT_CLEAR
* ����  : clear bbp wakeup int
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
BSP_VOID DRV_BBPWAKE_INT_CLEAR(PWC_COMM_MODE_E mode);

/*****************************************************************************
Function:   BSP_PWC_GetMeansFlag
Description:
Input:
Output:     the means flag value;
Return:
Others:
*****************************************************************************/
extern BSP_S32 BSP_PWC_GetMeansFlag(PWC_COMM_MODE_E enCommMode);
#define DRV_PWC_GET_MEANSFLAG(enCommMode) BSP_PWC_GetMeansFlag(enCommMode)


/*****************************************************************************
* �� �� : bbp_timer_int_init
* �� �� : �ҽ�BBP��֡�ж�(T ��L)
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� : 
*****************************************************************************/
extern int bsp_bbp_timer_int_init(PWC_COMM_MODE_E mode);
#define DRV_BBP_TIMER_INT_INIT(mode) bsp_bbp_timer_int_init(mode)

/*****************************************************************************
* �� �� : bbp_dma_int_init
* �� �� : �ҽ�bbp dma �жϣ���ʹ��
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� : 
*****************************************************************************/
int bsp_bbp_dma_int_init(void);
#define DRV_BBP_DMA_INT_INIT() bsp_bbp_dma_int_init()

/*****************************************************************************
* �� �� : bsp_bbp_dma_int_enable
* �� �� : ʹ��bbp dma �ж�
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� : 
*****************************************************************************/
int bsp_bbp_dma_int_enable(void);
#define DRV_BBP_DMA_INT_ENABLE() bsp_bbp_dma_int_enable()

/*****************************************************************************
* �� �� : BSP_LPS_Get_Ta
* �� �� : ��lps����,�鿴������֡ͷ���ϵͳ��֡ͷ����ǰ��
* �� �� : void
* �� �� : void
* �� �� : 
* ˵ �� : 
*****************************************************************************/
BSP_U16 BSP_LPS_GetTa(void);

/*****************************************************************************
* �� �� : BSP_BBPIntTimerSwitchStatus
* �� �� : ���ڻ�ȡLBBP TIMER�ж�ʹ��״̬
* �� �� : BSP_BOOL
* �� �� : void
* �� �� : 
* ˵ �� : 
*****************************************************************************/
BSP_S32 BSP_BBPIntTimerSwitchStatus(BSP_BOOL *pbStat);
#define DRV_BBP_INT_TIMER_SWITCH_STATUS(pbStat) BSP_BBPIntTimerSwitchStatus(pbStat)

#endif

