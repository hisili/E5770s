
#include <product_config.h>


#ifndef CONFIG_CPUFREQ

#include <bsp_cpufreq.h>
#include <drv_comm.h>

#ifdef __cplusplus
extern "C"
{
#endif


/*�ṩpm���̵��ã��������Ƶ��CPU/DDR*/
void cpufreq_set_max_freq(void)
{
	
}
/*
 * ��ȡ��ǰprofile
 */
int pwrctrl_dfs_get_profile()
{
	return 0;
}
/*
 * ����profile
 * success: return BSP_OK
 * fail:    return BSP_ERROR
 */
int pwrctrl_dfs_set_profile(int profile)
{
	return BSP_OK;
}

/*
 * ����profile����
 * success: return BSP_OK	
 * fail:    return BSP_ERROR
 */
int pwrctrl_dfs_set_baseprofile(int baseprofile)
{
	return BSP_OK;
}

/*
 * ������Ƶ lock=0����;lock=1����
 */
void pwrctrl_dfs_lock(u32 lock)
{
	
}

/*
 * ���Խӿڣ�����Ƶ�� BSP_ERROR ����ʧ��;BSP_OK ���óɹ�
 *
 */
int pwrctrl_dfs_target(int a9freq, int ddrfreq, int slowfreq)
{
	return BSP_OK;
}

int pwrctrl_dfs_current(int *a9freq, int *ddrfreq, int *slowfreq)
{
	return BSP_OK;
}

void cpufreq_update_frequency(void)
{
	
}
unsigned int cpufreq_calccpu_load_netif(void)
{
	return BSP_OK;
}

#ifdef __cplusplus
}
#endif
#endif
