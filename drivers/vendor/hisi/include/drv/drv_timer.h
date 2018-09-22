

#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__

#include "drv_comm.h"
#include "soc_timer_enum.h"
/*************************TIMER BEGIN*****************************/

typedef enum
{
	TIMER_CCPU_DSP_DRX_PROT_ID              =CCPU_DSP_DRX_TIMER,              /*v9r1 ����ӣ���;��ȷ�ϣ��ȱ�֤����ͨ��    liujing*/
	ACORE_SOFTTIMER_ID                      =ACPU_SOFTTIMER_WAKE,             /*A core ����Դ��timer id                lixiaojie*/
	CCORE_SOFTTIMER_ID                      =CCPU_SOFTTIMER_WAKE,             /*C core ����Դ��timer id                lixiaojie*/
	ACORE_WDT_TIMER_ID                      =ACPU_WDT_TIMER,                  /*A CORE���Ź�                           yangqiang*/
	CCORE_WDT_TIMER_ID                      =CCPU_WDT_TIMER,                  /*C CORE���Ź�                           yangqiang*/
	TIME_STAMP_ID                           =STAMP_TIMER,                     /*P531��ʹ�ã�A core C CORE M3ʱ���,��fastboot�׶�ʹ�� ��V7R2ʹ��BBPʱ���lixiaojie*/              
	USB_TIMER_ID                            =USB_TIMER,                       /*A CORE    V7R2 USBʹ��                lvhui*/
	CCORE_SOFTTIMER_NOWAKE_ID               =CCPU_SOFTTIMER_NOWAKE,           /*C core �ǻ���Դ��timer                 lixiaojie*/
	ACORE_SOFTTIMER_NOWAKE_ID               =ACPU_SOFTTIMER_NOWAKE,           /*A core �ǻ���Դ��timer                 lixiaojie*/
	TIMER_DSP_TIMER2_ID                     =DSP_TIMER2,                      /*DSPʹ��                                 liujing*/
	TIMER_MCPU_ID                           =MCU_TIMER,                       /*M3ʹ��                                lixiaojie*/
	TIMER_HIFI_TIMER2_ID                    =HIFI_TIMER2,                     /*hifiʹ��                              fuying*/
	TIMER_UDELAY_TIMER_ID                   =UDELAY_TIMER,                    /*c���ṩudelay����ʹ�ã���fastboot�׶�ʹ��              lixiaojie*/
	CCORE_SYSTEM_TIMER_ID                   =CCPU_SYSTIMER,                   /*C Coreϵͳʱ��                        luting*/
	ACORE_SYSTEM_TIMER_ID                   =ACPU_SYSTIMER,                   /*A COREϵͳʱ��                        luting*/
	ACORE_SOURCE_TIMER_ID                   =ACPU_SOURCE_TIMER,               /*A CORE �¼�Դ                        luting */
	TIMER_ACPU_CPUVIEW_ID                   =ACPU_VIEW_TIMER,                 /*A CORE CPU VIEW                      duxiaopeng*/
	TIMER_CCPU_CPUVIEW_ID                   =CCPU_VIEW_TIMER,                 /*C CORE CPU VIEW                     duxiaopeng*/
	TIMER_HIFI_TIMER1_ID                    =HIFI_TIMER1,                     /*hifiʹ��                             fuying*/
	TIMER_ACPU_OSA_ID                       =ACPU_OSA_TIMER,                  /*A CORE�����ʱ                        cuijunqiang*/
	TIMER_CCPU_OSA_ID                       =CCPU_OSA_TIMER,                  /*C CORE�����ʱ                        cuijunqiang*/
	TIMER_CCPU_DRX1_STABLE_ID               =CCPU_DRX1,                       /*C CORE tcxo�ȶ�ʱ��xujingcui            */
	TIMER_DSP_TIMER1_ID                     =DSP_TIMER1,                      /*DSPʹ��                             liujing*/
	TIMER_CCPU_DRX2_STABLE_ID               =CCPU_DRX2  ,                     /*C CORE tcxo�ȶ�ʱ��xujingcui                    */
	TIMER_CCPU_DRX_TIMER_ID                 =CCPU_DRX_TIMER,                  /*�����ʵʱ�Ի���,cuijunqiang          */
	TIMER_ACPU_OM_TCXO_ID                   =ACPU_OM_TIMER,                  /*���vos timerƵ������, cuijunqiang    */
	TIMER_CCPU_G1PHY_DRX_ID                 =1000 ,                           /*ֻ��V9R1ʹ�ã�V7R2��K3V3�Ȳ�Ʒ��̬��׮:luoqingquan*/
	TIMER_ID_MAX                            =24
} DRV_TIMER_ID;

typedef enum
{
    TIMER_ONCE_COUNT = 0,        /* ���ζ�ʱ��ģʽ */
    TIMER_PERIOD_COUNT,          /* ���ڶ�ʱ��ģʽ */
    TIMER_FREERUN_COUNT,         /* ���ɶ�ʱ��ģʽ */
    TIMER_COUNT_BUTT
}DRV_TIMER_MODE;

typedef enum
{
    TIMER_UNIT_MS = 0,           /* 0��ʾ��λmsģʽ */
    TIMER_UNIT_US,               /* 1��ʾ��λusģʽ */
    TIMER_UNIT_NONE,                /* 2��ʾ��λ1����ֱ�Ӳ���load�Ĵ���ģʽ  */
    TIMER_UNIT_BUTT
}DRV_TIMER_UNIT;


BSP_VOID DRV_TIMER_DEBUG_REGISTER(unsigned int timer_id,FUNCPTR_1 routinue, int arg); 


extern int DRV_TIMER_START
(
    unsigned int     usrClkId,
    FUNCPTR_1        routine,
    int              arg,
    unsigned int     timerValue,
    unsigned int     mode,
    unsigned int     unitType
);


extern int DRV_TIMER_STOP(unsigned int usrClkId);


extern int DRV_TIMER_GET_REST_TIME(unsigned int usrClkId, unsigned int unitType, unsigned int * pRestTime);

/************************************************************************
 * FUNCTION
 *       BSP_GetHardTimerCurTime
 * DESCRIPTION
 *       Get hard timer Current Value
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
     RTC OM
 *************************************************************************/
extern BSP_VOID BSP_ClearTimerINT(BSP_VOID);
#define DRV_CLEAR_TIMER_INT()   BSP_ClearTimerINT()
/************************************************************************
 * FUNCTION
 *       BSP_StartHardTimer
 * DESCRIPTION
 *       start hard timer
 * INPUTS
 *       value -- timer's value.uint is 32K cycle
 * OUTPUTS
 *       NONE
    RTC OM
 *************************************************************************/
extern BSP_VOID BSP_StartHardTimer(BSP_U32 value);
#define DRV_STATR_HARD_TIMER(value)   BSP_StartHardTimer(value)
/************************************************************************
 * FUNCTION
 *       BSP_StopHardTimer
 * DESCRIPTION
 *       Stop hard timer
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
      RTC OM
 *************************************************************************/
extern BSP_VOID BSP_StopHardTimer(BSP_VOID);
#define DRV_STOP_HARD_TIMER()   BSP_StopHardTimer()
/************************************************************************
 * FUNCTION
 *       BSP_GetHardTimerCurTime
 * DESCRIPTION
 *       GetHardTimerCurTime
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
    RTC OM
 *************************************************************************/
extern BSP_U32 BSP_GetHardTimerCurTime(BSP_VOID);
#define DRV_GET_TIMER_CUR_TIME()   BSP_GetHardTimerCurTime()
/************************************************************************
 * FUNCTION
 *       BSP_GetSliceValue
 * DESCRIPTION
 *       GetSliceValue
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
       ��ȡʱ�����ʱ�������ֵΪ����ֵ
 *************************************************************************/
extern unsigned int BSP_GetSliceValue(void);
#define DRV_GET_SLICE()   BSP_GetSliceValue()
#if (FEATURE_ON == MBB_WPG_COMMON)
/************************************************************************
 * FUNCTION
 *       BSP_GetSeconds
 * DESCRIPTION
 *       ��ȡ��ǰ��ϵͳs����Ϣ
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
       ��ȡʱ�����ʱ�������ֵΪ����ֵ
 *************************************************************************/
extern unsigned long BSP_GetSeconds(void);
#define DRV_GET_SECONDS() BSP_GetSeconds()
#endif
#define PWRCTRL_GetSleepSlice() BSP_GetSliceValue()

/************************************************************************
 * FUNCTION
 *       bsp_get_32k_ms
 * DESCRIPTION
 *       GetSliceValue
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
       ��ȡʱ�����ʱ�������ֵΪ����ֵ
 *************************************************************************/
extern unsigned int bsp_get_32k_ms(void);
#define DRV_GET_32K_MS()   bsp_get_32k_ms()

UINT32 omTimerGet(void);
UINT32 omTimerTickGet(void);
/*****************************************************************************
 �� �� ��  : BSP_32K_GetTick
 ��������  : 32Kʱ�Ӷ�ӦTick��ѯ�ӿ�
 �������  : None
 �������  : None
 �� �� ֵ  : 32Kʱ�Ӷ�ӦTickֵ
*****************************************************************************/
 BSP_U32 BSP_32K_GetTick( BSP_VOID );

/*****************************************************************************
 Function   : BSP_PWC_SetTimer4WakeSrc
 Description: ����timer4��Ϊ����Դ
 Input      :
 Return     : void
 Other      :
*****************************************************************************/
 VOID BSP_PWC_SetTimer4WakeSrc(VOID);

/*****************************************************************************
 Function   : BSP_PWC_DelTimer4WakeSrc
 Description: ����timer4����Ϊ����Դ
 Input      :
            :
 Return     : void
 Other      :
*****************************************************************************/
 VOID BSP_PWC_DelTimer4WakeSrc(VOID);
   
#endif

