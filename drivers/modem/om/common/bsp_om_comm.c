
/*lint -save -e537 -e7 -e322*/
#include "osl_types.h"
#include "osl_io.h"
#include "bsp_memmap.h"
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include "bsp_om_api.h"
#include "bsp_om_save.h"
#include "drv_comm.h"
#include "bsp_hardtimer.h"
/*lint -restore*/

#define OM_TIMER_STAMP_BASE     IO_ADDRESS(HI_TIMER_10_REGBASE_ADDR)		/*timer10*/

static char g_ErrorLogBuffer[256] = {0x00};
/*lint -save -e526*/

u32 om_timer_get(void)
{
	return bsp_get_slice_value();
}

u32 om_timer_tick_get(void)
{
    u32 omTimerValue;
    /*lint -save -e958*/
	u64 omTick;

	omTimerValue = bsp_get_slice_value();
	omTick=((unsigned long long)omTimerValue*100)>>(15);
    /*lint -restore*/
	return (UINT32)omTick;
}


/*****************************************************************************
* �� �� ��  : bsp_int_lock_enter
*
* ��������  :�������ж�ͳ��
*
* �������  :��
*
* �������  : ��
*
* �� �� ֵ  : ���жϺ��õ�key
*****************************************************************************/
void bsp_int_lock_enter(void)
{
    bsp_dump_int_lock((bsp_module_e)0);
}

/*****************************************************************************
* �� �� ��  : bsp_int_lock_out
*
* ��������  : �������ж�ͳ��
*
* �������  : ���жϺ��õ�key
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_int_lock_out(void)
{
    bsp_dump_int_unlock((bsp_module_e)0);
}

void error_log(char *fmt ,...)
{
    /*lint -save -e40 -e522 */
    va_list arglist;
    /*lint -restore +e40 +e522 */
	va_start(arglist, fmt);
	vsnprintf(g_ErrorLogBuffer, 256, fmt, arglist); /* [false alarm]:����Fortify���� */
	va_end(arglist);

    bsp_om_append_file(OM_ERROR_LOG, (void*)g_ErrorLogBuffer, (u32)strlen(g_ErrorLogBuffer), OM_ERROR_LOG_MAX);

    return;
}
/*lint -restore +e526*/

