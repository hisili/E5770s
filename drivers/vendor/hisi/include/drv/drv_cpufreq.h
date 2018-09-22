

#ifndef __DRV_CPUFREQ_H__
#define __DRV_CPUFREQ_H__


#include <product_config.h>
#include <soc_cpufreq.h>
#include "drv_comm.h"



#define BALONG_FREQ_MAX			(DC_RESV - 1)
#define BALONG_FREQ_MIN			BALONG_FREQ_PRO0
#define BALONG_FREQ_MAX_DDR	(800)

/*������Ƶ�ӿ����*/
#define BALONG_FREQ_LOCK			(0)
#define BALONG_FREQ_UNLOCK			(1)


/*
 * ��ȡ��ǰprofile
 * ���ص�ǰprofile
 */
int pwrctrl_dfs_get_profile(void);


/*
 * ����profile
 * success: return BSP_OK
 * fail:    return BSP_ERROR
 */
int pwrctrl_dfs_set_profile(int profile);


/*
 * ����profile����
 * success: return BSP_OK
 * fail:    return BSP_ERROR
 */
int pwrctrl_dfs_set_baseprofile(int baseprofile);

 

/*
 * ������Ƶ lock=0����;lock=1����
 */
void pwrctrl_dfs_lock(unsigned int lock_frq);


/*
 * ����Ƶ�� BSP_ERROR ����ʧ��;BSP_OK ���óɹ�
 * ��ηֱ�Ϊ��ǰ�˵�cpuƵ�ʣ�ddrƵ�ʣ�slowbusƵ��
 * ע:��C��profile4��5��CPUƵ����ͬ��
 * ����������Ƶ�뽫ccpuƵ����Ϊ���Ƶ+1
 * �ͷ�ʱ��ȡ��Ƶ�������������������Ϊ0
 */
int pwrctrl_dfs_target(int a9freq, int ddrfreq, int slowfreq);
/*
 * ��ȡ��ǰƵ�� BSP_ERROR ����ʧ��;BSP_OK ���óɹ�
 * 
 */
int pwrctrl_dfs_current(int *a9freq, int *ddrfreq, int *slowfreq);

/*
 * �ýӿڸ���cpu���ؼ�⣬
 * ������Ԥ����ֵ�о��Ƿ���Ҫ��M3�����Ƶ
 * �ϵ�������������Ƶ�ʣ��µ��������һ��profile
 */
void cpufreq_update_frequency(void);

/********************************adp interface start**************************************/

/*wangwei dfs*/
typedef  enum
{
    PWRCTRL_DFS_USB = 0,
    PWRCTRL_DFS_SD  = 1,
    PWRCTRL_DFS_PS1 = 2,
    PWRCTRL_DFS_HIFI = 3,  /*hifi*/
    PWRCTRL_DFS_BUTT
} PWC_DFS_ID_E;

typedef enum
{
    DFS_PROFILE_0 = 0,            /*Ƶ�ʼ���1*/
    DFS_PROFILE_1 = 1,            /*Ƶ�ʼ���2*/
    DFS_PROFILE_2 = 2,            /*Ƶ�ʼ���3*/
    DFS_PROFILE_3 = 3,            /*Ƶ�ʼ���4*/
    DFS_PROFILE_4 = 4,            /*Ƶ�ʼ���5*/
    DFS_PROFILE_BUTT
} PWC_DFS_PROFILE_E;

/*
 *  DFS Device QoS
 */
typedef enum tagDFS_QOS_ID_E
{
    DFS_QOS_ID_ACPU_MINFREQ_E = 0,  /*(0)*/
    DFS_QOS_ID_ACPU_MAXFREQ_E,      /*(1)*/
    DFS_QOS_ID_CCPU_MINFREQ_E,      /*(2)*/
    DFS_QOS_ID_CCPU_MAXFREQ_E,      /*(3)*/
    DFS_QOS_ID_DDR_MINFREQ_E,       /*(4)*/
    DFS_QOS_ID_DDR_MAXFREQ_E,       /*(5)*/
    DFS_QOS_ID_GPU_MINFREQ_E,       /*(6)*/
    DFS_QOS_ID_GPU_MAXFREQ_E,       /*(7)*/
    DFS_QOS_ID_BUS_MINFREQ_E,       /*(8)*/
    DFS_QOS_ID_BUS_MAXFREQ_E        /*(9)*/
}DFS_QOS_ID_E;

BSP_S32 PWRCTRL_DfsQosRequest(BSP_S32 qos_id, BSP_U32 req_value, BSP_S32 *req_id);

BSP_S32 PWRCTRL_DfsQosRelease(BSP_S32 qos_id, BSP_S32 *req_id);

BSP_S32 PWRCTRL_DfsQosUpdate(BSP_S32 qos_id, BSP_S32 req_id, BSP_U32 req_value);

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_GetCcpuLoadCB
 ��������  : arm �ṩ��TTF�Ļص�����
 �������  : pFunc:TTF����ָ��
 �������  : ��
 �� �� ֵ  : ����ռ�ĵ�ַ ��
*****************************************************************************/
extern void BSP_PWRCTRL_GetCcpuLoadCB(PWRCTRLFUNCPTR pFunc );
#define DRV_PWRCTRL_GetCcpuLoadCB(pFunc) BSP_PWRCTRL_GetCcpuLoadCB(pFunc)

/*****************************************************************************
 �� �� ��  : DRV_PWRCTRL_GetCpuLoad
 ��������  : arm cpuռ���ʲ�ѯ����
 �������  : ��
 �������  : ulAcpuLoad:Acpuռ���ʵ�ַ.
             ulCcpuLoad:Ccpuռ���ʵ�ַ.
 �� �� ֵ  : 0/1 ��
*****************************************************************************/
extern unsigned int DRV_PWRCTRL_GetCpuLoad(unsigned int *ulAcpuLoad,unsigned int *ulCcpuLoad);

/*****************************************************************************
Function:   DRV_PWRCTRL_DFS_SET_PRF_CCPU
Description:Set the System Min Profile
Input:      ulClientID: The Vote Module Client
            enProfile:  The Min Profile Value
Output:     None
Return:     The Vote Result
Others:
*****************************************************************************/
 BSP_U32  DRV_PWRCTRL_DFS_SET_PRF_CCPU(PWC_DFS_ID_E ulClientID, PWC_DFS_PROFILE_E enProfile);

/*****************************************************************************
Function:   DRV_PWRCTRL_DFS_RLS_PRF_CCPU
Description:Release the Vote Result
Input:      ulClientID: The Vote Module Client
Output:     None;
Return:     The Vote Result
Others:
*****************************************************************************/
 BSP_U32 DRV_PWRCTRL_DFS_RLS_PRF_CCPU(PWC_DFS_ID_E ulClientID);

 /*****************************************************************************
 �� �� ��  : BSP_DFS_GetCurCpuLoad
 ��������  : ��ѯ��ǰCPU
 �������  : pu32AcpuLoad ACPUloadָ��
             pu32CcpuLoad CCPUloadָ��
 �������  : pu32AcpuLoad ACPUloadָ��
             pu32CcpuLoad CCPUloadָ��
 �� �� ֵ  : 0:  �����ɹ���
            -1������ʧ�ܡ�
*****************************************************************************/
 BSP_U32 BSP_DFS_GetCurCpuLoad(BSP_U32 *pu32AcpuLoad,BSP_U32 *pu32CcpuLoad);
#define DRV_GET_CUR_CPU_LOAD(pu32AcpuLoad,pu32CcpuLoad) BSP_DFS_GetCurCpuLoad(pu32AcpuLoad,pu32CcpuLoad)

/********************************adp interface end***************************************/

#endif /*__DRV_CPUFREQ_H__*/

