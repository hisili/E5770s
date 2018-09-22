
#ifndef __DRV_WAKECLOCK_H__
#define __DRV_WAKECLOCK_H__

#include <product_config.h>
/******************************************************
*˯��ͶƱID ,��0��ʼ�����32��
*�漰ͶƱ�������Ҫ�ڴ����LOCK ID
*��ͬ���޸�wakelock_balong.c�е�debug_wakelock
*******************************************************/
typedef enum tagPWC_CLIENT_ID_E
{
    PWRCTRL_SLEEP_TLPS = 0,   /*MSP--fuxin*/
    PWRCTRL_SLEEP_PS_G0,        /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_W0,       /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_G1,        /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_W1,       /*GU--ganlan*/
    PWRCTRL_SLEEP_FTM,           /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_FTM_1,       /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_NAS,           /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_NAS_1,       /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_OAM,		   /* LTE --yangzhi */
    PWRCTRL_SLEEP_SCI0,		   /* LTE --yangzhi */
    PWRCTRL_SLEEP_SCI1,		   /* LTE --yangzhi */
    PWRCTRL_SLEEP_DSFLOW,	   /* NAS --zhangyizhan */
    PWRCTRL_SLEEP_TEST,		   /* PM  ---shangmianyou */
    PWRCTRL_SLEEP_UART0,        /*UART0 -zhangliangdong */
    PWRCTRL_SLEEP_TDS,         /*TRRC&TL2----leixiantiao*/
    PWRCTRL_SLEEP_MBB_COMMON,  /* MBB COMMON --- xuchao */
    /*���²��ֵ�ID�Ѿ���ʹ���ˣ����ڻ�ɾ��*/
    PWRCTRL_SLEEP_RNIC,
    LOCK_ID_BOTTOM =32
}PWC_CLIENT_ID_E;

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_SLEEPVOTE_UNLOCK
 ��������  : ��������˯��ͶƱ�ӿڡ�
 �������  : lock_id id
 �������  : None
 �� �� ֵ  : ��
*****************************************************************************/

unsigned int BSP_PWRCTRL_SleepVoteLock(PWC_CLIENT_ID_E id);
unsigned int BSP_PWRCTRL_SleepVoteUnLock(PWC_CLIENT_ID_E id);

#define DRV_PWRCTRL_SLEEPVOTE_LOCK(_clk_id)     BSP_PWRCTRL_SleepVoteLock(_clk_id)
#define DRV_PWRCTRL_SLEEPVOTE_UNLOCK(_clk_id)     BSP_PWRCTRL_SleepVoteUnLock(_clk_id)
/*****************************************************************************
 �� �� ��  : BSP_PWRCTRL_StandbyStateCcpu/BSP_PWRCTRL_StandbyStateAcpu
 ��������  : AT^PSTANDBY
 �������  :
 �������  :
 ����ֵ��
*****************************************************************************/
 unsigned int BSP_PWRCTRL_StandbyStateAcpu(unsigned int ulStandbyTime, unsigned int ulSwitchTime);
 unsigned int BSP_PWRCTRL_StandbyStateCcpu(unsigned int ulStandbyTime, unsigned int ulSwitchTime);
#define DRV_PWRCTRL_STANDBYSTATEACPU(ulStandbyTime, ulSwitchTime)	BSP_PWRCTRL_StandbyStateAcpu(ulStandbyTime, ulSwitchTime)
#define DRV_PWRCTRL_STANDBYSTATECCPU(ulStandbyTime, ulSwitchTime)	BSP_PWRCTRL_StandbyStateCcpu(ulStandbyTime, ulSwitchTime)

#endif

