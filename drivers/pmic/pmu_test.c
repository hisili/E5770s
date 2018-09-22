
#include "pmu_balong.h"

struct pmu_test g_pmu_test;

/*****************************************************************************
 �� �� ��  : bsp_pmu_test_enable
 ��������  : ��pmuģ��test����
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_pmu_test_enable(void)
{
    g_pmu_test.test_sw = 1;
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_test_disable
 ��������  :�ر�pmuģ��test����
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :�쳣��λ
*****************************************************************************/
void bsp_pmu_test_disable(void)
{
    g_pmu_test.test_sw = 0;
}

/*****************************************************************************
 �� �� ��  : bsp_pmu_test_register
 ��������  : pmuģ��test��Ϣע��
 �������  : void
 �������  : ��
 �� �� ֵ  : ע��ɹ���ʧ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_pmu_test_register(pmic_id_e pmic_id,struct pmu_test_ops ops_func)
{
    if(PMIC_BUTTOM <= pmic_id)
    {
        pmic_print_error("platform doesn't support this PMIC!\n");
        return  BSP_PMU_PARA_ERROR;
    }

    g_pmu_test.test_ops[pmic_id]= ops_func;

    return  BSP_PMU_OK;

}
/*****************************************************************************
 �� �� ��  : bsp_pmu_volt_onoff_test
 ��������  : ����pmuģ���ѹԴ���ؽӿ�
 �������  : uctimes:���Դ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_pmu_volt_onoff_test(u32 uctimes)
{
    int i = 0;
    int test_result = BSP_PMU_OK;

    pmic_print_info("*****bsp_pmu_volt_onoff_test*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_test.test_ops[i].pmu_volt_onoff_test)
            test_result |= g_pmu_test.test_ops[i].pmu_volt_onoff_test(uctimes);
    }
    return test_result;
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_volt_setget_test
 ��������  : ����pmuģ���ѹԴ���õ�ѹ�ӿ�
 �������  : uctimes:���Դ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_pmu_volt_setget_test(u32 uctimes)
{
    int i = 0;
    int test_result = BSP_PMU_OK;

    pmic_print_info("*****bsp_pmu_volt_setget_test*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_test.test_ops[i].pmu_volt_setget_test)
            test_result |= g_pmu_test.test_ops[i].pmu_volt_setget_test(uctimes);
    }
    return test_result;
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_volt_mode_test
 ��������  : ����pmuģ���ѹԴ����ģʽ�ӿ�
 �������  : uctimes:���Դ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_pmu_volt_mode_test(u32 uctimes)
{
    int i = 0;
    int test_result = BSP_PMU_OK;

    pmic_print_info("*****bsp_pmu_mode_setget_test*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_test.test_ops[i].pmu_volt_mode_test)
            test_result |= g_pmu_test.test_ops[i].pmu_volt_mode_test(uctimes);
    }
    return test_result;
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_mode_setget_test
 ��������  : ����pmuģ���ѹԴ��ѹ����
 �������  : uctimes:���Դ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_pmu_volt_table_test(u32 uctimes)
{
    int i = 0;
    int test_result = BSP_PMU_OK;

    pmic_print_info("*****bsp_pmu_volt_table_test*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_test.test_ops[i].pmu_volt_table_test)
            test_result |= g_pmu_test.test_ops[i].pmu_volt_table_test(uctimes);
    }
    return test_result;
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_test_init
 ��������  : ��ʼ��pmu testģ�飬����pmic���Ժ���ע�ᵽ���Կ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_pmu_test_init(void)
{
    int iret = BSP_PMU_OK;

#ifdef CONFIG_PMIC_HI6451
    iret = bsp_hi6451_test_init();
#endif
#ifdef CONFIG_PMIC_HI6551
    iret |= bsp_hi6551_test_init();
#endif

#ifdef CONFIG_PMIC_HI6559
    iret |= bsp_hi6559_test_init();
#endif

    if(iret)
        pmic_print_error("init error!\n");
    else
        pmic_print_info("init ok!\n");

    return iret;
}
/*pmu adp�ӿڵĲ���*/
#ifdef __KERNEL__
/*����Դ���ֽӿ�*/
/*****************************************************************************
 �� �� ��  : bsp_pmu_dr_onoff_test
 ��������  : ����pmuģ�����Դ���ؽӿ�
 �������  : uctimes:���Դ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �Զ�������
*****************************************************************************/
int bsp_pmu_dr_onoff_test(u32 uctimes)
{
    int i = 0;
    int test_result = BSP_PMU_OK;

    pmic_print_info("*****bsp_pmu_dr_onoff_test*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_test.test_ops[i].pmu_dr_onoff_test)
            test_result |= g_pmu_test.test_ops[i].pmu_dr_onoff_test(uctimes);
    }
    return test_result;
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_dr_setget_test
 ��������  : ����pmuģ�����Դ���õ����ӿ�
 �������  : uctimes:���Դ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_pmu_dr_setget_test(u32 uctimes)
{
    int i = 0;
    int test_result = BSP_PMU_OK;

    pmic_print_info("*****bsp_pmu_volt_setget_test*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_test.test_ops[i].pmu_dr_setget_test)
            test_result |= g_pmu_test.test_ops[i].pmu_dr_setget_test(uctimes);
    }
    return test_result;
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_dr_mode_test
 ��������  : ����pmuģ�����Դ����ģʽ�ӿ�
 �������  : uctimes:���Դ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_pmu_dr_mode_test(u32 uctimes)
{
    int i = 0;
    int test_result = BSP_PMU_OK;

    pmic_print_info("*****bsp_pmu_mode_setget_test*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_test.test_ops[i].pmu_dr_mode_test)
            test_result |= g_pmu_test.test_ops[i].pmu_dr_mode_test(uctimes);
    }
    return test_result;
}
/*����Ƽ���ɫ�ƹ��ܲ�������*/
/*****************************************************************************
 �� �� ��  : bsp_dr_fla_time_set_test
 ��������  : ����drģ����˸ʱ�����ýӿ�
 �������  : uctimes:���Դ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ϵͳ����
*****************************************************************************/
int bsp_dr_fla_time_set_test(unsigned on_us,unsigned off_us)
{
    DR_FLA_TIME fla_time;
    int iret;

    fla_time.fla_on_us = on_us;
    fla_time.fla_off_us = off_us;

    iret = bsp_dr_fla_time_set(&fla_time);
    return  iret;
}
/*****************************************************************************
 �� �� ��  : bsp_dr_fla_time_set_test
 ��������  : ����drģ�����ʱ�����ýӿ�
 �������  : uctimes:���Դ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ϵͳ����
*****************************************************************************/
int bsp_dr_bre_time_set_test(dr_id_e dr_id,unsigned on_ms,unsigned off_ms,unsigned rise_ms,unsigned fall_ms)
{
    DR_BRE_TIME bre_time;
    int iret;

    bre_time.bre_on_ms = on_ms;
    bre_time.bre_off_ms = off_ms;
    bre_time.bre_rise_ms = rise_ms;
    bre_time.bre_fall_ms = fall_ms;

    iret = bsp_dr_bre_time_set(dr_id,&bre_time);
    return  iret;
}

/*��˸ģʽ*/
int bsp_dr_fla_test_001()
{
    return bsp_dr_fla_time_set_test(DR_VALUE_INVALIED,DR_VALUE_INVALIED);
}
#endif
