
#ifndef _BSP_BBP_H_
#define _BSP_BBP_H_

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__CMSIS_RTOS)
#include "osl_common.h"
#else
#include "osl_types.h"
#endif
#include "soc_interrupts.h"
#include "drv_bbp.h"
#include "drv_dpm.h"
#include "drv_comm.h"
#include "drv_timer.h"
#include "bsp_om.h"
#include "hi_bbp.h"

#define  bbp_print_error(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_BBP, "[bbp]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  bbp_print_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_BBP, "[bbp]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

/*�����ڴ�ʹ��*/
#define IRM_POWRON_OFFSET 0

s32  bbp_int_init(void);
void bsp_bbp_timerintregcb(BSPBBPIntTimerFunc pfunc);
void bsp_bbp_dltbintregcb(BSPBBPIntDlTbFunc pfunc);
void bsp_bbp_timerintclear(void);
int bsp_bbp_timerintenable(void);
void bsp_bbp_timerintdisable(void);
u32 bsp_bbp_getcurtime(unsigned long long *pcurtime);
u16 bsp_bbp_getsysframe(void);
u16 bsp_bbp_getsyssubframe(void);

void bsp_bbp_tdstf_regcb(BSPBBPIntTdsFunc pFunc);
int bsp_bbp_tdstf_enable(void);
void bsp_bbp_tdstf_disable(void);

int bbp_pwrctrl_irm_poweron(void);
int bbp_pwrctrl_irm_poweroff(void);
PWC_COMM_STATUS_E bbp_pwrctrl_irm_status(void);

void bbp_wakeup_int_enable(PWC_COMM_MODE_E mode);
void bbp_wakeup_int_disable(PWC_COMM_MODE_E mode);
void bbp_wakeup_int_clear(PWC_COMM_MODE_E mode);
/*****************************************************************************
* ����  : bsp_bbp_get_tds_subframe
* ����  : get tds system sub frame num
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
u16 bsp_bbp_get_tds_subframe(void);

/*****************************************************************************
* ����  : bsp_bbp_set_tds_subframoffset
* ����  : set tds system sub frame offset
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
u16 bsp_bbp_set_tds_subframoffset(u16 sf_offset);

/*****************************************************************************
* ����  : bsp_bbp_get_tds_sleep_time
* ����  : Get tds sleep time
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
u32 bsp_bbp_get_tds_sleep_time(void);

/*****************************************************************************
* ����  : bsp_bbp_get_tdsclk_switch
* ����  : get_tdsclk_switch
* ����  : void
* ���  : 0��ʾ�л���ϵͳʱ�ӣ�1��ʾ�л���32kʱ��
* ����  : void
*****************************************************************************/
int bsp_bbp_get_tdsclk_switch(void);

/*****************************************************************************
Function:   BSP_PWC_GetMeansFlag
Description:
Input:
Output:     the means flag value;
Return:
Others:
*****************************************************************************/
 BSP_S32 BSP_PWC_GetMeansFlag(PWC_COMM_MODE_E enCommMode);
/*****************************************************************************
* �� �� : bbp_get_wakeup_time
* �� �� : ���͹��ĵ��ã�������ѯ˯�߳�ʱʱ��
* �� �� : ��
* �� �� : void
* �� �� : bbp˯��ʣ��ʱ�䣬��λΪ32.768KHzʱ�Ӽ���
*****************************************************************************/
u32 bsp_bbp_get_wakeup_time(void);
/*****************************************************************************
* �� �� : bsp_bbp_g1_poweron
* �� �� : ���͹��ĵ��ã�������G1 BBP�ϵ�
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� :
*****************************************************************************/
int bsp_bbp_pwrctrl_g1bbp_poweron(void);
/*****************************************************************************
* �� �� : bsp_bbp_g1_poweroff
* �� �� : ���͹��ĵ��ã�������G1 BBP�µ�
* �� �� : ģʽ
* �� �� : void
* �� �� : �µ��Ƿ�ɹ�
* ˵ �� :
*****************************************************************************/
int bsp_bbp_pwrctrl_g1bbp_poweroff(void);

/*****************************************************************************
* �� �� : bsp_bbp_pwrctrl_g1_status
* �� �� : ���͹��ĵ��ã�������G1 BBP�ϵ�
* �� �� : void
* �� �� : void
* �� �� : 0x10Ϊopen, 0x20Ϊclose
* ˵ �� :
*****************************************************************************/
PWC_COMM_STATUS_E bsp_bbp_pwrctrl_g1bbp_status(void);

/*****************************************************************************
* �� �� : bsp_bbp_g2_poweron
* �� �� : ���͹��ĵ��ã�������G2 BBP�ϵ�
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� :
*****************************************************************************/
int bsp_bbp_pwrctrl_g2bbp_poweron(void);

/*****************************************************************************
* �� �� : bsp_bbp_g2_poweroff
* �� �� : ���͹��ĵ��ã�������G1 BBP�µ�
* �� �� : ģʽ
* �� �� : void
* �� �� : �µ��Ƿ�ɹ�
* ˵ �� :
*****************************************************************************/
int bsp_bbp_pwrctrl_g2bbp_poweroff(void);

/*****************************************************************************
* �� �� : bsp_bbp_pwrctrl_g2_status
* �� �� : ���͹��ĵ��ã�������G1 BBP�ϵ�
* �� �� : void
* �� �� : void
* �� �� : 0x10Ϊopen, 0x20Ϊclose
* ˵ �� :
*****************************************************************************/
PWC_COMM_STATUS_E bsp_bbp_pwrctrl_g2bbp_status(void);

/*****************************************************************************
* �� �� : bsp_bbp_wbbp_poweron
* �� �� : ���͹��ĵ��ã�������W BBP�ϵ�
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� :
*****************************************************************************/
int bsp_bbp_pwrctrl_wbbp_poweron(void);

/*****************************************************************************
* �� �� : bsp_bbp_wbbp_poweroff
* �� �� : ���͹��ĵ��ã�������W BBP�µ�
* �� �� : ģʽ
* �� �� : void
* �� �� : �µ��Ƿ�ɹ�
* ˵ �� :
*****************************************************************************/
int bsp_bbp_pwrctrl_wbbp_poweroff(void);

/*****************************************************************************
* �� �� : bsp_bbp_pwrctrl_wbbp_status
* �� �� : ���͹��ĵ��ã�������W BBP�ϵ�
* �� �� : void
* �� �� : void
* �� �� : 0x10Ϊopen, 0x20Ϊclose
* ˵ �� :
*****************************************************************************/
PWC_COMM_STATUS_E bsp_bbp_pwrctrl_wbbp_status(void);

/*****************************************************************************
* �� �� : bsp_bbp_twbbp_poweron
* �� �� : ���͹��ĵ��ã�������TW BBP�ϵ�
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� :
*****************************************************************************/
int bsp_bbp_pwrctrl_twbbp_poweron(void);

/*****************************************************************************
* �� �� : bsp_bbp_wbbp_poweroff
* �� �� : ���͹��ĵ��ã�������W BBP�µ�
* �� �� : ģʽ
* �� �� : void
* �� �� : �µ��Ƿ�ɹ�
* ˵ �� :
*****************************************************************************/
int bsp_bbp_pwrctrl_twbbp_poweroff(void);

/*****************************************************************************
* �� �� : bsp_bbp_pwrctrl_wbbp_status
* �� �� : ���͹��ĵ��ã�������W BBP�ϵ�
* �� �� : void
* �� �� : void
* �� �� : 0x10Ϊopen, 0x20Ϊclose
* ˵ �� :
*****************************************************************************/
PWC_COMM_STATUS_E bsp_bbp_pwrctrl_twbbp_status(void);

/*****************************************************************************
* �� �� : bsp_bbp_pwrctrl_tdsbbp_clk_enable
* �� �� : ���͹��ĵ��ã�������TDS����
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� : 
*****************************************************************************/
int bsp_bbp_pwrctrl_tdsbbp_clk_enable(void);
/*****************************************************************************
* �� �� : bsp_bbp_pwrctrl_tdsbbp_clk_disable
* �� �� : ���͹��ĵ��ã�������TDS����
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� : 
*****************************************************************************/
int bsp_bbp_pwrctrl_tdsbbp_clk_disable(void);

/*****************************************************************************
* �� �� : bsp_bbp_pwrctrl_wbbp_clk_disable
* �� �� : ���͹��ĵ��ã�������wģ����
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� : 
*****************************************************************************/
int bsp_bbp_pwrctrl_wbbp_clk_disable(void);

/*****************************************************************************
* �� �� : bsp_bbp_pwrctrl_tdsbbp_clk_enable
* �� �� : ���͹��ĵ��ã�������W����
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� : 
*****************************************************************************/
int bsp_bbp_pwrctrl_wbbp_clk_enable(void);
/*****************************************************************************
* �� �� : bsp_bbp_lps_get_ta
* �� �� : ��lps����,�鿴������֡ͷ���ϵͳ��֡ͷ����ǰ��
* �� �� : void
* �� �� : void
* �� �� : 
* ˵ �� : 
*****************************************************************************/
u16 bsp_bbp_lps_get_ta(void);
int bsp_bbp_int_debug(void);

u32 bsp_bbp_get_gubbp_wakeup_status(void);

#ifdef __cplusplus
}
#endif

#endif /*end #ifndef _BSP_DRV_SCI_H_*/


