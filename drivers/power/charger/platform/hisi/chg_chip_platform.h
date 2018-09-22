#ifndef CHG_CHARGE_ADC_H
#define CHG_CHARGE_ADC_H




/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/

/********Note:����ͷ�ļ���ƽ̨ǿ��أ���ֲ��Ա����ƽ̨��Ҫ���*******/
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/jiffies.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/printk.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/gpio.h>
#include <asm/div64.h>
#include <linux/fs.h>
#include <asm/uaccess.h>

/*I2C����ͷ�ļ�*/
#include "bsp_i2c.h"
/*NV����ͷ�ļ�*/
#include "bsp_nvim.h"
/*��ʱ������ͷ�ļ�*/
#include "bsp_softtimer.h"

#include <linux/syscalls.h>
#include <asm/unaligned.h>

#include <linux/spinlock.h>
#ifndef CHG_STUB
#include <linux/mlog_lib.h>
#else
#define  mlog_print(format, ...)
#endif
/********Note:����ͷ�ļ���ƽ̨ǿ��أ���ֲ��Ա����ƽ̨��Ҫ���*******/

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/
extern void kernel_power_off(void);

/*----------------------------------------------*
 * �궨��˵��                                   *
 *----------------------------------------------*/

#if (MBB_CHG_EXTCHG == FEATURE_ON)
/*�����������������GPIO��ʹ�ú궨�����*/
#if (FEATURE_ON == MBB_CHG_PLATFORM_V7R2)
//#define EXTCHG_CONTROL_GPIO_EN1       GPIO_0_11 /* V7R2ƽֻ̨����EN1��EN2��Ӳ��ǿ������*/
#else
#define EXTCHG_CONTROL_GPIO_EN1       59
#define EXTCHG_CONTROL_GPIO_EN2       60
#endif
#endif/*MBB_CHG_EXTCHG*/

#if (MBB_CHG_WIRELESS == FEATURE_ON)
/*�����������������GPIO��ʹ�ú궨�����*/
#if (FEATURE_ON == MBB_CHG_PLATFORM_V7R2)
#define WIRELESS_CONTROL_GPIO_EN1       GPIO_0_11 /* V7R2ƽֻ̨����EN1��EN2��Ӳ��ǿ������*/
#else
#define WIRELESS_CONTROL_GPIO_EN1       59
#endif
#define WIRELESS_CONTROL_GPIO_EN2       60
#define USB_WIRELESS_CHGR_DET    0x0006
#endif/*MBB_CHG_WIRELESS*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/
/**********************************************************************
FUNCTION:    chg_send_stat_to_app
DESCRIPTION: Charge module sends charge state to application layer.
INPUT:       uint32_t chg_device_id,
             uint32_t chg_event_id
OUTPUT:      None.
RETURN:      None.
NOTE:        None
***********************************************************************/
void chg_send_stat_to_app(uint32_t chg_device_id, uint32_t chg_event_id);
/**********************************************************************
FUNCTION:    CHG_SET_POWER_OFF
DESCRIPTION: The poweroff func of CHG module, all the power-off operation
             except at boot phase MUST be performed via calling this.
INPUT:       The shutdown reason which triggered system poweroff.
             All VALID REASON:
             DRV_SHUTDOWN_BATTERY_ERROR --BATTERY ERROR;
             DRV_SHUTDOWN_TEMPERATURE_PROTECT --EXTREAM HIGH TEMPERATURE.
             DRV_SHUTDOWN_LOW_TEMP_PROTECT --EXTREAM LOW TEMPERATURE
             DRV_SHUTDOWN_CHARGE_REMOVE --CHGR REMOVAL WHILE POWEROFF CHG
             DRV_SHUTDOWN_LOW_BATTERY --LOW BATTERY
OUTPUT:      None.
RETURN:      None.
NOTE:        When this function get called to power system off, it record
             the shutdown reason, then simulate POWER_KEY event to APP to
             perform the real system shutdown process.
             THUS, THIS FUNCTION DOESN'T TAKE AFFECT IF APP DIDN'T STARTUP.
***********************************************************************/
void chg_set_power_off(DRV_SHUTDOWN_REASON_ENUM real_reason);


extern int32_t chg_get_volt_from_adc(CHG_PARAMETER_ENUM param_type);



extern int32_t chg_get_batt_volt_value(void);


extern int32_t chg_get_temp_value(CHG_PARAMETER_ENUM param_type);


extern boolean chg_is_powdown_charging (void);

/*****************************************************************************
 �� �� ��  : get_chgr_type_from_usb
 ��������  : Get real charger type from USB module.
             This function called the platform interfaces to obtain the real
             charger type from USB module.
             !!Platform dependent, currently we implemented as Balong V700R001
             design.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : Charger type of state machine needed.
 CALL-WHOM : Platform interfaces.
 WHO-CALLED: chg_check_and_update_hw_param_per_chgr_type
             chg_transit_state_period_func
 NOTICE    : 1. Platform chgr_type enum may be different from chg_stm design,
             we need convert or remap them before return.
             2. Balong V3R2/V7R1 platform didn't support CHG_USB_HOST_PC,
             CHG_NONSTD_CHGR and CHG_USB_HOST_PC would all be treated as
             CHG_NONSTD_CHGR.
             3. Export Required.
*****************************************************************************/
extern chg_chgr_type_t get_chgr_type_from_usb(ulong64_t plug,int32_t chg_type);


void chg_display_interface(CHG_BATT_DISPLAY_TYPE disp_type);


/***************Note:ƽ̨��ش��룬����ƽ̨����Ҫ��ӣ��е�ƽ̨��9x25��Ҫ
              ��ֲ��Ա������Ҫ����ӻ����Ƴ��±ߺ�������***************************/
void chg_batt_volt_calib_init(void);

int32_t chg_get_volt_from_adc(CHG_PARAMETER_ENUM param_type);

#if (MBB_CHG_EXTCHG == FEATURE_ON)

extern int extchg_gpio_init(void);


extern void extchg_gpio_control(uint32_t gpio,int32_t level);
#endif/*MBB_CHG_EXTCHG*/


#if (MBB_CHG_WIRELESS == FEATURE_ON)

extern int wireless_gpio_init(void);

extern void wireless_gpio_control(uint32_t gpio,int32_t level);
#endif/*MBB_CHG_WIRELESS*/


extern boolean is_in_update_mode(void);

/**********************************************************************
�� �� ��  : boolean chg_config_para_read(int32_t num)
��������  : ���������ò���
�������  : none
�������  : �ޡ�
�� �� ֵ  : �ޡ�
ע������  : �ɸ���ƽ̨��ͬ�޸�ʵ�ַ���������NV�ȡ�
***********************************************************************/
boolean chg_config_para_read(uint16_t nvID, void *pItem, uint32_t ulLength);


void chg_pt_mmi_test_proc(void);

#if (MBB_CHG_COMPENSATE == FEATURE_ON)

void chg_set_fact_release_mode(boolean on);
#endif



#endif

