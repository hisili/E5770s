#include "pmu_balong.h"

struct pmu_dbg g_pmu_dbg;

/*��������*/
void bsp_pmu_dbg_enable(void);
void bsp_pmu_dbg_disable(void);
void bsp_pmu_volt_state(void);
void bsp_pmu_om_data_show(void);
void bsp_pmu_om_boot_show(void);
void bsp_pmu_exc_state(void);
void bsp_pmu_pmic_info(void);

/*����ʵ��*/
/*****************************************************************************
 �� �� ��  : bsp_pmu_dbg_enable
 ��������  :��pmuģ��dbg��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_pmu_dbg_enable(void)
{
    g_pmu_dbg.info_print_sw = 1;
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_dbg_disable
 ��������  :�ر�pmuģ��dbg��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :�쳣��λ
*****************************************************************************/
void bsp_pmu_dbg_disable(void)
{
    g_pmu_dbg.info_print_sw = 0;
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_dbg_register
 ��������  : pmuģ��dbg��Ϣע��
 �������  : void
 �������  : ��
 �� �� ֵ  : ע��ɹ���ʧ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_pmu_dbg_register(pmic_id_e pmic_id,struct pmu_dbg_ops ops_func)
{
    if(PMIC_BUTTOM <= pmic_id)
    {
        pmic_print_info("*****bsp_pmu_all_volt_state*****\n");
        return  BSP_PMU_PARA_ERROR;
    }

    g_pmu_dbg.dbg_ops[pmic_id]= ops_func;

    return  BSP_PMU_OK;

}
/*****************************************************************************
 �� �� ��  : bsp_pmu_volt_state
 ��������  : ��ʾ��ǰPMIC������·��Դ��ʹ����Ϣ(�������أ���ѹ��)
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :�쳣��λ
*****************************************************************************/
void bsp_pmu_volt_state(void)
{
    int i = 0;

    pmic_print_info("*****bsp_pmu_all_volt_state*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_dbg.dbg_ops[i].pmu_volt_state)
            g_pmu_dbg.dbg_ops[i].pmu_volt_state();
    }
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_om_data_show
 ��������  : ��ʾ�˴����й����е�ǰPMU״̬���쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_pmu_om_data_show(void)
{
    int i = 0;

    pmic_print_info("*****bsp_pmu_om_data_show*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_dbg.dbg_ops[i].pmu_om_data_show)
            g_pmu_dbg.dbg_ops[i].pmu_om_data_show();
    }
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_boot_om_show
 ��������  : ��ʾ�˴����й����е�ǰPMU״̬���쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_pmu_om_boot_show(void)
{
    int i = 0;

    pmic_print_info("*****bsp_pmu_boot_om_show*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_dbg.dbg_ops[i].pmu_om_boot_show)
            g_pmu_dbg.dbg_ops[i].pmu_om_boot_show();
    }
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_exc_state
 ��������  : ��ʾ��ǰ����PMIC�������쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :�쳣��λ
*****************************************************************************/
void bsp_pmu_exc_state(void)
{
    int i = 0;

    pmic_print_info("*****bsp_pmu_exc_state*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_dbg.dbg_ops[i].pmu_exc_state)
            g_pmu_dbg.dbg_ops[i].pmu_exc_state();
    }
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_pmic_info
 ��������  : ��ʾ��ǰ����PMIC�İ汾��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_pmu_pmic_info(void)
{
    int i = 0;

    pmic_print_info("*****bsp_pmu_pmic_info*****\n");
    for(i = 0;i < PMIC_BUTTOM;i++)
    {
        if(NULL != g_pmu_dbg.dbg_ops[i].pmu_pmic_info)
            g_pmu_dbg.dbg_ops[i].pmu_pmic_info();
    }
}

