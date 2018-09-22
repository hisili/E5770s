
/*lint --e{537}*/
#include "hi_base.h"
#include "soc_clk.h"
#include "bsp_memmap.h"
#include "hi_bbp_systime.h"

#include "bsp_bbp.h"
//#include "osl_types.h"

u64 bbp_judgetime = 0x50000;/*default 10s*/
void bbp_set_judgetime(u64 time_s)
{
    bbp_judgetime = HI_TIMER_STAMP_CLK*time_s;
}
/*****************************************************************************
* ����  : bsp_bbp_getcurtime
* ����  : ��PS���ã�������ȡϵͳ��ȷʱ��
* ����  : void
* ���  : u64 *pcurtime
* ����  : u32
*****************************************************************************/
u32 bsp_bbp_getcurtime(unsigned long long *pcurtime)
{
	/*lint -save -e958*/
    unsigned long long  timervalue[4];
	/*lint -restore*/

    timervalue[0] = get_hi_bbp_systime_abs_timer_l_abs_timer_l();
    timervalue[1] = get_hi_bbp_systime_abs_timer_h_abs_timer_h();
    if(timervalue[0]>=(0xffffffff-bbp_judgetime))
    {
        timervalue[2] = get_hi_bbp_systime_abs_timer_l_abs_timer_l();
        timervalue[3] = get_hi_bbp_systime_abs_timer_h_abs_timer_h();

        if(timervalue[2] < timervalue[0])
        {
            (*pcurtime) = ((timervalue[3] - 1) << 32) | timervalue[0];
        }
        else
        {
            (*pcurtime) = (timervalue[1] << 32) | timervalue[0];
        }
    }
    else
    {
        (*pcurtime) = (timervalue[1] << 32) | timervalue[0];
    }

    return 0;
}

