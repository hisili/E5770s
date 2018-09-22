
/*test hi6559 volt enable/isenable*/
/*notice:���ܹ��رյĵ�Դ���в���*/
#include <osl_bio.h>
#include <osl_thread.h>
#include <bsp_shared_ddr.h>
#if defined(__KERNEL__)
#include "dr_hi6559.h"
#endif
#include <pmu_balong.h>


#define PMIC_HI6559_TEST_TASK_PRI               (25)
#define PMIC_HI6559_TEST_TASK_STACK_SIZE        (0x1000)

s32 volt_onoff_test[] = 
{
    PMIC_HI6559_BUCK0,PMIC_HI6559_BUCK5,PMIC_HI6559_LDO01,PMIC_HI6559_LDO09,
    PMIC_HI6559_LDO10,PMIC_HI6559_LDO11,PMIC_HI6559_LDO13,PMIC_HI6559_LDO14,
    PMIC_HI6559_LDO23,PMIC_HI6559_LDO24,PMIC_HI6559_LVS07
};
s32 volt_setget_test[] =
{
    PMIC_HI6559_BUCK0,PMIC_HI6559_BUCK5,PMIC_HI6559_LDO01,PMIC_HI6559_LDO09,
    PMIC_HI6559_LDO10,PMIC_HI6559_LDO11,PMIC_HI6559_LDO13,PMIC_HI6559_LDO14,
    PMIC_HI6559_LDO23,PMIC_HI6559_LDO24,PMIC_HI6559_LVS07
};
s32 mode_set_get_test[] =
{
    PMIC_HI6559_BUCK3,PMIC_HI6559_BUCK4,PMIC_HI6559_BUCK6,PMIC_HI6559_LDO03,
    PMIC_HI6559_LDO07,PMIC_HI6559_LDO09,PMIC_HI6559_LDO10,PMIC_HI6559_LDO12,
    PMIC_HI6559_LDO22,PMIC_HI6559_LDO24
    
};

/*****************************************************************************
 �� �� ��  : hi6559_volt_test_table_check
 ��������  : ���Ե�ѹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static s32 hi6559_volt_test_table_check(PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table)
{
    if((SHM_PMU_VOLTTABLE_MAGIC_START_DATA == hi6559_volt_table->magic_start) && 
        (SHM_PMU_VOLTTABLE_MAGIC_END_DATA == hi6559_volt_table->magic_end))
    {
        return BSP_PMU_OK;
    }
    else
    {
        return BSP_PMU_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : hi6559_volt_enable_test
 ��������  : ��Դʹ�ܲ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_volt_enable_test(void)
{
    s32 j = 0, ret = BSP_PMU_OK;
    s32 test_num = (sizeof(volt_onoff_test)/sizeof(int));

    for(j = 0;j < test_num; j++)
    {
        ret = bsp_hi6559_volt_enable(volt_onoff_test[j]);
        if(ret)
        {
            pmic_print_error("\nERROR: volt%d: enable failed��ret %d!\n", volt_onoff_test[j], ret);
        }
        
        if(0 == bsp_hi6559_volt_is_enabled(volt_onoff_test[j]))
        {
            pmic_print_error("\nERROR: volt%d: is still disabled failed!\n", volt_onoff_test[j]);
            return volt_onoff_test[j];
        }
    }
    pmic_print_info("hi6559_volt_enable_test ok!!\n",volt_onoff_test[j]);

    return BSP_PMU_OK;
}

/*****************************************************************************
 �� �� ��  : hi6559_volt_disable_test
 ��������  : ��Դdisable����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_volt_disable_test(void)
{
    s32 j = 0, ret = BSP_PMU_OK;
    s32 test_num = (sizeof(volt_onoff_test)/sizeof(int));

    for(j = 0;j < test_num; j++)
    {
        ret = bsp_hi6559_volt_disable(volt_onoff_test[j]);
        if(ret)
        {
            pmic_print_error("\nERROR: volt%d: disable failed,ret %d!\n", volt_onoff_test[j], ret);
        }
        if(0 == bsp_hi6559_volt_is_enabled(volt_onoff_test[j]))
        {
            pmic_print_error("\nERROR: volt%d: is still enabled failed!\n", volt_onoff_test[j]);
            return volt_onoff_test[j];
        }
    }
    pmic_print_info("hi6559_volt_disable_test ok!!\n",volt_onoff_test[j]);

    return BSP_PMU_OK;

}

/*****************************************************************************
 �� �� ��  : hi6559_volt_onoff_err_test
 ��������  : ��Դʹ���쳣���̲���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_volt_onoff_err_test(void)
{
    s32 iret = 0;
    s32 result = BSP_PMU_OK;
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;

    /* �쳣id */
    iret = bsp_hi6559_volt_enable(PMIC_HI6559_VOLT_MIN - 1);/*lint !e415 !e831*/
    if(BSP_PMU_PARA_ERROR != iret)
    {
        pmic_print_error("bsp_hi6559_volt_enable err id test error!\n");
        result = BSP_PMU_ERROR;
    }
    
    /* �쳣id */
    iret = bsp_hi6559_volt_disable(PMIC_HI6559_VOLT_MAX + 1);/*lint !e415 !e831*/
    if(BSP_PMU_PARA_ERROR != iret)
    {
        pmic_print_error("bsp_hi6559_volt_disable err id test error!\n");
        result = BSP_PMU_ERROR;
    }
    
    /* �쳣id */
    iret = bsp_hi6559_volt_is_enabled(PMIC_HI6559_VOLT_MIN - 1);/*lint !e415 !e831*/
    if(BSP_PMU_PARA_ERROR != iret)
    {
        pmic_print_error("bsp_hi6559_volt_is_enabled err id test error!\n");
        result = BSP_PMU_ERROR;
    }
    
    /* ��Ϊ��дtableǰ��ħ���� */
    hi6559_volt_table->magic_start = 0xa0a0a0;
    iret = bsp_hi6559_volt_enable(mode_set_get_test[0]);/*lint !e415 !e831*/
    if(BSP_PMU_VOLTTABLE_ERROR != iret)
    {
        pmic_print_error("bsp_hi6559_volt_enable err table test error!\n");
        result = BSP_PMU_ERROR;
    }
    
    iret = bsp_hi6559_volt_disable(mode_set_get_test[0]);/*lint !e415 !e831*/
    if(BSP_PMU_VOLTTABLE_ERROR != iret)
    {
        pmic_print_error("bsp_hi6559_volt_disable err table test error!\n");
        result = BSP_PMU_ERROR;
    }
    
    iret = bsp_hi6559_volt_is_enabled(mode_set_get_test[0]);/*lint !e415 !e831*/
    if(BSP_PMU_VOLTTABLE_ERROR != iret)
    {
        pmic_print_error("bsp_hi6559_volt_is_enabled err table test error!\n");
        result = BSP_PMU_ERROR;
    }
    
    /* �ָ�tableǰ��ħ���� */
    hi6559_volt_table->magic_start = SHM_PMU_VOLTTABLE_MAGIC_START_DATA;

    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_volt_set_get_voltage_test
 ��������  : ��Դ��ѹ��ȡ/���ù��ܲ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_volt_set_get_voltage_test(void)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    PMIC_HI6559_VLTGS_ATTR *hi6559_volt;
    u32 selector = 0;
    s32 voltage = 0;
    s32 test_sub, iret = 0;
    s32 test_num = (sizeof(volt_setget_test)/sizeof(int));
    u8 j = 0;

    /* ��ѹ���Ա�ȫ�Լ�� */
    iret = hi6559_volt_test_table_check(hi6559_volt_table);
    if(BSP_PMU_OK != iret)
    {
        return  BSP_PMU_VOLTTABLE_ERROR;
    }

    /* ���ζ�ÿ·��ѹԴ��ÿ����ѹ�������á���ȡ������ȡlist volt */
    for(test_sub = 0;test_sub < test_num; test_sub++)
    {
        hi6559_volt = &hi6559_volt_table->hi6559_volt_attr[volt_setget_test[test_sub]];

        for(j = 0; j <= hi6559_volt->voltage_nums;j++)
        {
            voltage = hi6559_volt->voltage_list[j];
            iret = bsp_hi6559_volt_set_voltage(volt_setget_test[test_sub],voltage,voltage,&selector);
            if(BSP_PMU_OK != iret)
            {
                pmic_print_error("ERROR: volt%d set voltage failed, iret %d!!\n", 
                    volt_setget_test[test_sub], iret);
            }            

            if(voltage != bsp_hi6559_volt_get_voltage(volt_setget_test[test_sub]))
            {
                pmic_print_error("ERROR: volt%d get voltage failed!!\n", volt_setget_test[test_sub]);
            }
            
            if(voltage != bsp_hi6559_volt_list_voltage(volt_setget_test[test_sub],selector))
            {
                pmic_print_error("ERROR: volt%d get list voltage failed, selector %d!!\n", 
                    volt_setget_test[test_sub], selector);
            }
        }
    }
    
    pmic_print_info("hi6559_volt_set_get_voltage_test ok!!\n",volt_setget_test[test_sub]);
    
    return BSP_PMU_OK;
}

/*****************************************************************************
 �� �� ��  : hi6559_volt_setget_err_test
 ��������  : ��Դ��ѹ��ȡ/�����쳣��֧����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_volt_setget_err_test(void)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    s32 iret = 0;
    s32 result = BSP_PMU_OK;
    u32 selector;

    /* �쳣id */
    iret = bsp_hi6559_volt_set_voltage(PMIC_HI6559_VOLT_MIN - 1,0,0,&selector);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_volt_set_voltage err id test error, iret %d!\n", iret);
        result = BSP_PMU_ERROR;
    }
    
    /* �쳣id */
    iret = bsp_hi6559_volt_get_voltage(PMIC_HI6559_VOLT_MAX + 1);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_volt_get_voltage err id test error, iret %d!\n", iret);
        result = BSP_PMU_ERROR;
    }
    
    /* �쳣id */
    iret = bsp_hi6559_volt_list_voltage(PMIC_HI6559_VOLT_MIN - 1,0);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_volt_is_enabled err id test error, iret %d!\n", iret);
        result = BSP_PMU_ERROR;
    }

    /* ��Ϊ��дtable���ħ���� */
    hi6559_volt_table->magic_end = 0xa0a0a0;
    iret = bsp_hi6559_volt_set_voltage(volt_setget_test[0],0,0,&selector);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_volt_set_voltage err table test error, iret %d!\n", iret);
        result = BSP_PMU_ERROR;
    }
    
    iret = bsp_hi6559_volt_get_voltage(volt_setget_test[0]);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_volt_get_voltage err table test error, iret %d!\n", iret);
        result = BSP_PMU_ERROR;
    }
    
    iret = bsp_hi6559_volt_list_voltage(volt_setget_test[0],0);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_volt_list_voltage err table test error, iret %d!\n", iret);
        result = BSP_PMU_ERROR;
    }
    
    /* �ָ�table���ħ���� */
    hi6559_volt_table->magic_end = SHM_PMU_VOLTTABLE_MAGIC_END_DATA;

    /* ��Ч��ѹֵ */
    iret = bsp_hi6559_volt_set_voltage(volt_setget_test[0],0,0,&selector);
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_volt_set_voltage err voltage test error, iret %d!\n", iret);
        result = BSP_PMU_ERROR;
    }
    
    /* ��Ч��λֵ */
    iret = bsp_hi6559_volt_list_voltage(volt_setget_test[0],500);
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_volt_list_voltage err selector test error, iret %d!\n", iret);
        result = BSP_PMU_ERROR;
    }

    return result;
}
/*****************************************************************************
 �� �� ��  : hi6559_force_mode_set_get_test
 ��������  : ǿ��ecoģʽ���ò���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_force_mode_set_get_test(void)
{
    s32 i,iret = 0;
    s32 result = BSP_PMU_OK;
    s32 test_num = (sizeof(mode_set_get_test)/sizeof(int));

    for(i = 0;i < test_num;i++)
    {
        iret = bsp_hi6559_volt_set_mode(mode_set_get_test[i],PMU_MODE_ECO_FORCE);
        if(BSP_PMU_OK != iret)
        {
            pmic_print_error("hi6559 volt %d set_force_mode error, iret %d\n", mode_set_get_test[i], iret);
            result = BSP_PMU_ERROR;
        }
        else
        {
            if(PMU_MODE_ECO_FORCE != bsp_hi6559_volt_get_mode(mode_set_get_test[i]))
            {
                pmic_print_error("hi6559 volt %d force_mode_set_get_test error\n", mode_set_get_test[i]);
                result = BSP_PMU_ERROR;
            }
        }
    }

    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_normal_mode_set_get_test
 ��������  : normalģʽ���ò���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_normal_mode_set_get_test(void)
{
    s32 i,iret = 0;
    s32 result = BSP_PMU_OK;
    s32 test_num = (sizeof(mode_set_get_test)/sizeof(int));

    for(i = 0;i< test_num;i++)
    {
        iret = bsp_hi6559_volt_set_mode(mode_set_get_test[i],PMU_MODE_NORMAL);
        if(BSP_PMU_OK != iret)
        {
            pmic_print_error("hi6559 volt %d set_normal_mode error, iret %d\n", mode_set_get_test[i], iret);
            result = BSP_PMU_ERROR;
        }
        else
        {
            if(PMU_MODE_NORMAL != bsp_hi6559_volt_get_mode(mode_set_get_test[i]))
            {
                pmic_print_error("hi6559_normal_mode_set_get_test error\n");
                result = BSP_PMU_ERROR;
            }
        }
    }

    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_follow_mode_set_get_test
 ��������  : followģʽ���ò���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_follow_mode_set_get_test(void)
{
    s32 i,iret = 0;
    s32 result = BSP_PMU_OK;
    s32 test_num = (sizeof(mode_set_get_test)/sizeof(int));

    for(i = 0; i< test_num; i++)
    {
        iret = bsp_hi6559_volt_set_mode(mode_set_get_test[i],PMU_MODE_ECO_FOLLOW);
        if(BSP_PMU_OK != iret)
        {
            pmic_print_error("hi6559 volt %d set_follow_mode error, iret %d\n", mode_set_get_test[i], iret);
            result = BSP_PMU_ERROR;
        }
        else
        {
            if(PMU_MODE_ECO_FOLLOW != bsp_hi6559_volt_get_mode(mode_set_get_test[i]))
            {
                pmic_print_error("hi6559_follow_mode_set_get_test error\n");
                result = BSP_PMU_ERROR;
            }
        }
    }

    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_volt_mode_err_test
 ��������  : ģʽ�����֧����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_volt_mode_err_test(void)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    s32 iret = 0;
    s32 result = BSP_PMU_OK;

    /* �쳣id */
    iret = bsp_hi6559_volt_set_mode(PMIC_HI6559_VOLT_MIN - 1,PMU_MODE_NORMAL);/*lint !e415 !e831*/
    if(BSP_PMU_PARA_ERROR != iret)
    {
        pmic_print_error("bsp_hi6559_volt_set_mode err para test error, iret %d!\n", iret);
        result = BSP_PMU_ERROR;
    }
    /* �쳣id */
    if(PMU_MODE_BUTTOM != bsp_hi6559_volt_get_mode(PMIC_HI6559_VOLT_MAX + 1))
    {
        pmic_print_error("bsp_hi6559_volt_get_mode err para test error!\n");
        result = BSP_PMU_ERROR;
    }

    /* ��Ϊ��дtableǰ��ħ���� */
    hi6559_volt_table->magic_start = 0xa0a0a0;
    iret = bsp_hi6559_volt_set_mode(mode_set_get_test[0],PMU_MODE_NORMAL);/*lint !e415 !e831*/
    if(BSP_PMU_VOLTTABLE_ERROR != iret)
    {
        pmic_print_error("bsp_hi6559_volt_set_mode err table test error, iret %d!\n", iret);
        result = BSP_PMU_ERROR;
    }
    if(PMU_MODE_BUTTOM != bsp_hi6559_volt_get_mode(mode_set_get_test[0]))
    {
        pmic_print_error("bsp_hi6559_volt_get_mode err table test error!\n");
        result = BSP_PMU_ERROR;
    }

    /* �ָ�tableǰ��ħ���� */
    hi6559_volt_table->magic_start = SHM_PMU_VOLTTABLE_MAGIC_START_DATA;

    /* ģʽ���� */
    iret = bsp_hi6559_volt_set_mode(mode_set_get_test[0],PMU_MODE_BUTTOM);
    if(BSP_PMU_ERROR != iret)
    {
        pmic_print_error("bsp_hi6559_volt_set_mode err mode test error, iret %d!\n", iret);
        result = BSP_PMU_ERROR;
    }

    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_volttable_magic_start_test
 ��������  : ��ѹ��ͷħ��������д����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_volttable_magic_start_test(void)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    s32 iret;
    s32 result = BSP_PMU_OK;

    /* ��Ϊ��дtableǰ��ħ���� */
    hi6559_volt_table->magic_start = 0xa0a0a0;
    iret = bsp_hi6559_volt_is_enabled(20);
    if( BSP_PMU_VOLTTABLE_ERROR != iret)
    {
        pmic_print_error("hi6559_volttable_magic_start_test error, iret %d\n", iret);
        result = BSP_PMU_ERROR;
    }
    else
    {
        result = BSP_PMU_OK;
    }

    /*�ָ�tableǰ��ħ����*/
    hi6559_volt_table->magic_start = SHM_PMU_VOLTTABLE_MAGIC_START_DATA;
    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_volttable_magic_end_test
 ��������  : ��ѹ��βħ��������д����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_volttable_magic_end_test(void)
{
    s32 iret;
    s32 result = BSP_PMU_OK;
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;

    /*��Ϊ��дtable���ħ����*/
    hi6559_volt_table->magic_end = 0x0a0a0a0a;
    iret = bsp_hi6559_volt_get_voltage(20);
    if( BSP_PMU_VOLTTABLE_ERROR != iret)
    {
        pmic_print_error("hi6559_volttable_magic_end_test error, iret %d\n", iret);
        result = BSP_PMU_ERROR;
    }
    else
    {
        result = BSP_PMU_OK;
    }

    /* �ָ�table���ħ���� */
    hi6559_volt_table->magic_end = SHM_PMU_VOLTTABLE_MAGIC_END_DATA;
    return result;
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_onoff_test
 ��������  : ��ѹԴ���ز���
 �������  : @test_times ���Դ���
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 bsp_hi6559_volt_onoff_test(u32 test_times)
{
    s32 fail_times[3] = {0,0,0};
    u32 test_counts = 0;

    for(test_counts = 0; test_counts < test_times ; test_counts++)
    {
        if(BSP_PMU_OK != hi6559_volt_enable_test())
        {
            fail_times[0]++;
        }

        if(BSP_PMU_OK != hi6559_volt_disable_test())
        {
            fail_times[1]++;
        }

        if(BSP_PMU_OK != hi6559_volt_onoff_err_test())
        {
            fail_times[2]++;
        }
    }

    if((0 != fail_times[0]) || (0 != fail_times[1]) || (0 != fail_times[2]))
    {
        pmic_print_error("test %d times ,enable %d times failed,disable %d times failed,err check %d times failed!!\n",test_times,fail_times[0],fail_times[1],fail_times[2]);
        return BSP_PMU_ERROR;
    }
    else
    {
        pmic_print_error("test %d times ok!!\n",test_times);
        return BSP_PMU_OK;
    }
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_setget_test
 ��������  : ��ѹԴ�ĵ�ѹֵ����/��ȡ����
 �������  : @test_times ���Դ���
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 bsp_hi6559_volt_setget_test(u32 test_times)
{
    u32 test_counts = 0;
    s32 fail_times[2] = {0,0};

    for(test_counts = 0; test_counts < test_times ; test_counts++)
    {
        if(BSP_PMU_OK != hi6559_volt_set_get_voltage_test())
        {
            fail_times[0]++;
        }
        if(BSP_PMU_OK != hi6559_volt_setget_err_test())
        {
            fail_times[1]++;
        }
    }

    if((0 != fail_times[0])||(0 != fail_times[1]))
    {
        pmic_print_error("test %d times ,setget %d times failed,err check %d failed!!\n",test_times,fail_times[0],fail_times[1]);
        return BSP_PMU_ERROR;
    }
    else
    {
        pmic_print_error("test %d times ok!!\n",test_times);
        return BSP_PMU_OK;
    }

}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_mode_test
 ��������  : ��ѹԴģʽ����
 �������  : @test_times ���Դ���
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 bsp_hi6559_volt_mode_test(u32 test_times)
{
    s32 fail_times[4] = {0,0,0,0};
    u32 test_counts = 0;

    for(test_counts = 0; test_counts < test_times ; test_counts++)
    {
        if(BSP_PMU_OK != hi6559_force_mode_set_get_test())
        {
            fail_times[0]++;
        }

        if(BSP_PMU_OK != hi6559_normal_mode_set_get_test())
        {
            fail_times[1]++;
        }

        if(BSP_PMU_OK != hi6559_follow_mode_set_get_test())
        {
            fail_times[2]++;
        }

        if(BSP_PMU_OK != hi6559_volt_mode_err_test())
        {
            fail_times[3]++;
        }
    }

    if((0 != fail_times[0])||(0 != fail_times[1])||(0 != fail_times[2])||(0 != fail_times[3]))
    {
        pmic_print_error("test %d times ,force mode: %d times failed,normal mode: %d times failed,eco mode :%d times failed,err check:%d times failed!!\n",\
                        test_times,fail_times[0],fail_times[1],fail_times[2],fail_times[3]);
        return BSP_PMU_ERROR;
    }
    else
    {
        pmic_print_error("test %d times ok!!\n",test_times);
        return BSP_PMU_OK;
    }
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volttable_test
 ��������  : ��ѹ���Ա����
 �������  : @test_times ���Դ���
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 bsp_hi6559_volttable_test(u32 test_times)
{
    s32 fail_times[2] = {0,0};
    u32 test_counts = 0;

    for(test_counts = 0; test_counts < test_times ; test_counts++)
    {
        if(BSP_PMU_OK != hi6559_volttable_magic_start_test())
        {
            fail_times[0]++;
        }

        if(BSP_PMU_OK != hi6559_volttable_magic_end_test())
        {
            fail_times[1]++;
        }
    }

    if((0 != fail_times[0])||(0 != fail_times[1]))
    {
        pmic_print_error("test %d times ,magic start: %d times failed,magic end: %d times failed!!\n",\
                        test_times,fail_times[0],fail_times[1]);
        return BSP_PMU_ERROR;
    }
    else
    {
        pmic_print_error("test %d times ok!!\n",test_times);
        return BSP_PMU_OK;
    }
}

/* ���´�����Ϊ��Ƭ����֤Ӳ���ṩ���Ż�reg���õĲ��� */
typedef struct
{
    u16 regAddr;
    u8 regValue;
    u8 reserved;
}BBStar_CFG_S;

BBStar_CFG_S g_BBStar_CFG_V03[] =
{
    { 0x117 ,0x02},
    { 0X5A  ,0x3c},
    { 0X61  ,0x00},
    { 0X5F  ,0x12},
    { 0X60  ,0x03},
    { 0X5D  ,0x20},
    { 0X5E  ,0x01},
    { 0X65  ,0x01},
    { 0X6C  ,0x00},
    { 0X6B  ,0x03},
    { 0X6A  ,0x12},
    { 0X69  ,0x11},
    { 0X71  ,0x01},
    { 0X76  ,0x12},
    { 0X78  ,0x01},
    { 0X77  ,0x03},
    { 0X74  ,0x00},
    { 0X75  ,0x01},
    { 0X7A  ,0x15},
    { 0X7C  ,0x01},
    { 0X81  ,0x12},
    { 0x80  ,0x03},
    { 0x83  ,0x00},
    { 0X82  ,0x03},
    { 0X7F  ,0x01},
    { 0X87  ,0x01},
    { 0X90  ,0x00},
    { 0X8E  ,0x12},
    { 0x8D  ,0x01},
    { 0X8F  ,0x03},
    { 0X92  ,0x13},
    { 0X95  ,0x01},
    { 0X0BA ,0X0E},
    { 0X0BB ,0X32},
    { 0X0BC ,0X3B},
    { 0X0B2 ,0X31},
    { 0x025 ,0xFE},
    { 0x022 ,0xFA},
    { 0x028 ,0xAA},
    { 0x02B ,0xEA},
};

BBStar_CFG_S g_BBStar_CFG[] =
{
    {0X5A,0x3c},
    {0X61,0x00},
    {0X5F,0x12},
    {0X60,0x03},
    {0X5D,0x20},
    {0X5E,0x01},
    {0X6C,0x00},
    {0X6B,0x03},
    {0X6A,0x12},
    {0X69,0x11},
    {0X76,0x12},
    {0X78,0x01},
    {0X77,0x03},
    {0X74,0x00},
    {0X75,0x01},
    {0X7A,0x13},
    {0X81,0x12},
    {0x80,0x03},
    {0x83,0x00},
    {0X82,0x03},
    {0X7F,0x01},
    {0X90,0x00},
    {0X8E,0x12},
    {0x8D,0x01},
    {0X8F,0x03},
    {0X92,0x13},
    {0x020,0x45},
    {0X0BA,0X0E},
    {0X0BB,0X32},
    {0X0BC,0X3B},
    {0x0B2,0x01},
};

/*****************************************************************************
 �� �� ��  : bsp_hi6559_optreg_test
 ��������  : hi6559 �Ż�reg���ò���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void bsp_hi6559_optreg_test(void)
{
#if 0
    u32 test_num = 0;
    u32 m;
    u8 value;

    if(BSP_PMU_V230 == bsp_pmu_version_get())
    {
        test_num = sizeof(g_BBStar_CFG)/sizeof(BBStar_CFG_S);
        for(m = 0; m < test_num; m++)
        {
            bsp_hi6559_reg_read(g_BBStar_CFG[m].regAddr,&value);

            pmic_print_info("the value of addr %x is %x\n", g_BBStar_CFG[m].regAddr,value);

            if(g_BBStar_CFG_V03[m].regValue != value)
            {
                pmic_print_error("the value of addr %x is different\n", g_BBStar_CFG[m].regAddr);
                pmic_print_error("read value is %x,should be %x\n", value,g_BBStar_CFG[m].regValue);
            }
        }
    }
    else if((BSP_PMU_V210 == bsp_pmu_version_get())||(BSP_PMU_V220 == bsp_pmu_version_get()))
    {
        test_num = sizeof(g_BBStar_CFG_V03)/sizeof(BBStar_CFG_S);
        for(m = 0; m < test_num; m++)
        {
            bsp_hi6559_reg_read(g_BBStar_CFG_V03[m].regAddr,&value);

            pmic_print_info("the value of addr %x is %x\n", g_BBStar_CFG_V03[m].regAddr,value);

            if(g_BBStar_CFG_V03[m].regValue != value)
            {
                pmic_print_error("the value of addr %x is different\n", g_BBStar_CFG_V03[m].regAddr);
                pmic_print_error("read value is %x,should be %x\n", value,g_BBStar_CFG_V03[m].regValue);
            }
        }
    }
#else
    pmic_print_error("strub now\n");
#endif
    pmic_print_error("test ok!\n");

    return;
}

#ifdef __KERNEL__
extern PMIC_HI6559_DRS_ATTR hi6559_dr_attr[PMIC_HI6559_DR_MAX + 1];
extern s32 bsp_hi6559_dr_set_current_test(s32 dr_id, s32 min_uA, s32 max_uA);

/*****************************************************************************
 �� �� ��  : hi6559_dr_enable_test
 ��������  : DRʹ�ܲ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 hi6559_dr_enable_test(void)
{
    s32 id_test = 0;
    s32 ret = BSP_PMU_OK;
    s32 result = BSP_PMU_OK;
    for(id_test = PMIC_HI6559_DR_MIN; id_test <= PMIC_HI6559_DR_MAX; id_test++)
    {
        /* ��˸ģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test, PMU_DRS_MODE_FLA_FLASH);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_set_mode failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }
        
        ret = bsp_hi6559_dr_enable(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_enable failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }

        ret = bsp_hi6559_dr_is_enabled(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_is_enabled failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }
        
        /* ����ģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_BRE_FLASH);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_set_mode failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }        

        ret = bsp_hi6559_dr_enable(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_enable failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }
        
        /* ��˸ģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_FLA_LIGHT);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_set_mode failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }        

        ret = bsp_hi6559_dr_enable(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_enable failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }        

        ret = bsp_hi6559_dr_is_enabled(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_is_enabled failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }
        
        /* ����ģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_BRE);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_set_mode failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }        

        ret = bsp_hi6559_dr_enable(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_enable failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }        

        ret = bsp_hi6559_dr_is_enabled(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_is_enabled failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

        /* ��������ģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_BRE_LIGHT);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_set_mode failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         
        ret = bsp_hi6559_dr_enable(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_enable failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         
        ret = bsp_hi6559_dr_is_enabled(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_is_enabled failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

    }

    if(result)
    {
        pmic_print_error("hi6559_dr_enable_test ok!!\n");
    }
    else
    {
        pmic_print_error("hi6559_dr_enable_test failed!!\n");
    }

    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_dr_disable_test
 ��������  : DR��ʹ�ܲ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 hi6559_dr_disable_test(void)
{
    s32 id_test = 0, ret = BSP_PMU_OK;
    s32 result = BSP_PMU_OK;

    for(id_test = PMIC_HI6559_DR_MIN; id_test <= PMIC_HI6559_DR_MAX; id_test++)
    {
        /* flaģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_FLA_FLASH);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_set_mode failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         
        
        ret = bsp_hi6559_dr_disable(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_disable failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }  
        
        ret = bsp_hi6559_dr_is_enabled(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_is_enabled failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

        /* breģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_BRE_FLASH);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_set_mode failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }      
        
        ret = bsp_hi6559_dr_disable(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_disable failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        } 

        ret = bsp_hi6559_dr_is_enabled(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_is_enabled failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

        /* flaģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_FLA_LIGHT);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_set_mode failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

        ret = bsp_hi6559_dr_disable(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_disable failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

        ret = bsp_hi6559_dr_is_enabled(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_is_enabled failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

        /* breģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_BRE);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_set_mode failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

        ret = bsp_hi6559_dr_disable(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_disable failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

        ret = bsp_hi6559_dr_is_enabled(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_is_enabled failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

        /* ��������ģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_BRE_LIGHT);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_set_mode failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

        ret = bsp_hi6559_dr_disable(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_disable failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

        ret = bsp_hi6559_dr_is_enabled(id_test);
        if(ret)
        {
            pmic_print_error("ERROR bsp_hi6559_dr_is_enabled failed, dr_id %d, ret %d!\n", id_test, ret);
            result |= ret;
        }         

    }

    if(result)
    {
        pmic_print_error("hi6559_dr_disable_test ok!!\n");
    }
    else
    {
        pmic_print_error("hi6559_dr_disable_test failed!!\n");
    }
    
    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_dr_onoff_err_test
 ��������  : DR���ش������̲���
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 hi6559_dr_onoff_err_test(void)
{
    s32 iret = 0;
    s32 result = BSP_PMU_OK;

    /* �쳣id */
    iret = bsp_hi6559_dr_enable(PMIC_HI6559_DR_MIN - 1);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_dr_enable err, ret %d!\n", iret);
        result |= iret;
    }
    /* �쳣id */
    iret = bsp_hi6559_dr_disable(PMIC_HI6559_DR_MAX + 1);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_dr_disable err, ret %d!\n", iret);
        result |= iret;
    }
    /* �쳣id */
    iret = bsp_hi6559_dr_is_enabled(PMIC_HI6559_DR_MIN - 1);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_dr_is_enabled err, ret %d!\n", iret);
        result |= iret;
    }

    if(result)
    {
        pmic_print_error("hi6559_dr_onoff_err_test ok!!\n");
    }
    else
    {
        pmic_print_error("hi6559_dr_onoff_err_test failed!!\n");
    }
    
    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_dr_current_test
 ��������  : DR����set/get����
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 hi6559_dr_current_test(void)
{
    PMIC_HI6559_DRS_ATTR *hi6559_dr = NULL;
    u32 selector = 0;
    s32 i = 0, j = 0;
    s32 result = BSP_PMU_OK;
    s32 dr_current = 0;

    for(i = PMIC_HI6559_DR_MIN; i <= PMIC_HI6559_DR_MAX; i++)
    {
        hi6559_dr = &hi6559_dr_attr[i];
        for(j = 0; j < NUM_OF_DR_CURRENT; j++)
        {
            dr_current = hi6559_dr->current_list[j];
            
            result = bsp_hi6559_dr_set_current(i,dr_current,dr_current,&selector);
            if(BSP_PMU_OK != result)
            {
                pmic_print_error("ERROR bsp_hi6559_dr_set_current err, ret %d!\n", result);
            }            

            if(dr_current != bsp_hi6559_dr_get_current(i))
            {
                pmic_print_error("ERROR bsp_hi6559_dr_get_current error dr_id %d!!\n", i);
                result |= BSP_PMU_ERROR;
            }
            
            if(dr_current != bsp_hi6559_dr_list_current(i,selector))
            {
                pmic_print_error("ERROR bsp_hi6559_dr_list_current error dr_id %d!!\n", i);
                result |= BSP_PMU_ERROR;
            }
        }
    }

    if(!result)
    {
        pmic_print_error("hi6559_dr_current_test ok!!\n");
    }
    else
    {
        pmic_print_error("hi6559_dr_current_test failed, return %d!!\n", result);
    }

    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_dr_current_test
 ��������  : DR����set/get����
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 hi6559_dr_current_err_test(void)
{
    s32 iret = 0;
    s32 result = BSP_PMU_OK;

    /* �쳣id */
    iret = bsp_hi6559_dr_set_current_test(PMIC_HI6559_DR_MIN - 1,0,0);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_dr_set_current err id test error!\n");
        result |= iret;
    }
    
    /* �쳣id */
    iret = bsp_hi6559_dr_get_current(PMIC_HI6559_DR_MAX + 1);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_dr_get_current err id test error!\n");
        result |= iret;
    }
    
    /* �쳣id */
    iret = bsp_hi6559_dr_list_current(PMIC_HI6559_DR_MIN - 1,0);/*lint !e415 !e831*/
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_dr_list_current err, ret %d!\n", iret);
        result |= iret;
    }

    /* ��Ч����ֵ */
    iret = bsp_hi6559_dr_set_current_test(2,100000,200000);
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_dr_set_current err, ret %d!\n", iret);
        result |= iret;
    }
    
    /* ��Ч��λֵ */
    iret = bsp_hi6559_dr_list_current(3,500);
    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_hi6559_dr_list_current err, ret %d!\n", iret);
        result |= iret;
    }

    if(!result)
    {
        pmic_print_error("hi6559_dr_current_err_test ok!!\n");
    }
    else
    {
        pmic_print_error("hi6559_dr_current_err_test failed, return %d!!\n", result);
    }
    
    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_dr_bre_mode_test
 ��������  : DR����ģʽ���ò���
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 hi6559_dr_bre_mode_test(void)
{
    dr_mode_e  mode = PMU_DRS_MODE_BUTTOM;
    s32 id_test = 0;
    s32 result = BSP_PMU_OK;
    s32 ret = BSP_PMU_OK;

    /* DR1/2����ģʽ */
    for(id_test = PMIC_HI6559_DR_MIN; id_test < PMIC_HI6559_DR03; id_test++)
    {
        /* ������˸ģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_BRE_FLASH);
        if(BSP_PMU_OK != ret)
        {
            pmic_print_error("bsp_hi6559_dr_set_mode err, ret %d!\n", ret);
            result |= ret;
        }
        
        mode = bsp_hi6559_dr_get_mode(id_test);
        if(PMU_DRS_MODE_BRE_FLASH != mode)
        {
            pmic_print_error("test error\n");
            result |= BSP_PMU_ERROR;
        }

        /* ��������ģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_BRE_LIGHT);
        if(BSP_PMU_OK != ret)
        {
            pmic_print_error("bsp_hi6559_dr_set_mode err, ret %d!\n", ret);
            result |= ret;
        }
        
        mode = bsp_hi6559_dr_get_mode(id_test);
        if(PMU_DRS_MODE_BRE_LIGHT != mode)
        {
            pmic_print_error("test error\n");
            result |= BSP_PMU_ERROR;
        }
    }
    
    /* DR3/4/5����ģʽ */
    for(id_test = PMIC_HI6559_DR03; id_test <= PMIC_HI6559_DR_MAX; id_test++)
    {
        /* ����ģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_BRE);
        if(BSP_PMU_OK != ret)
        {
            pmic_print_error("bsp_hi6559_dr_set_mode err, ret %d!\n", ret);
            result |= ret;
        }
        
        mode = bsp_hi6559_dr_get_mode(id_test);
        if(PMU_DRS_MODE_BRE != mode)
        {
            pmic_print_error("test error\n");
            result |= BSP_PMU_ERROR;
        }
        
        /* ������˸ģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_BRE_FLASH);
        if(BSP_PMU_OK != ret)
        {
            pmic_print_error("bsp_hi6559_dr_set_mode err, ret %d!\n", ret);
            result |= ret;
        }
        
        mode = bsp_hi6559_dr_get_mode(id_test);
        if(PMU_DRS_MODE_BRE != mode)
        {
            pmic_print_error("test error\n");
            result |= BSP_PMU_ERROR;
        }

        /* ��������ģʽ */
        ret = bsp_hi6559_dr_set_mode(id_test,PMU_DRS_MODE_BRE_LIGHT);
        if(BSP_PMU_OK != ret)
        {
            pmic_print_error("bsp_hi6559_dr_set_mode err, ret %d!\n", ret);
            result |= ret;
        }
        
        mode = bsp_hi6559_dr_get_mode(id_test);
        if(PMU_DRS_MODE_BRE != mode)
        {
            pmic_print_error("test error\n");
            result |= BSP_PMU_ERROR;
        }
    }

    if(!result)
    {
        pmic_print_error("hi6559_dr_bre_mode_test ok!!\n");
    }
    else
    {
        pmic_print_error("hi6559_dr_bre_mode_test failed, return %d!!\n", result);
    }    

    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_dr_fla_mode_test
 ��������  : flaģʽ���ò���
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 hi6559_dr_fla_mode_test(void)
{
    dr_mode_e  mode = PMU_DRS_MODE_BUTTOM;
    s32 id_test = 0;
    s32 result = BSP_PMU_OK;
    s32 ret = BSP_PMU_OK;

    for(id_test = PMIC_HI6559_DR_MIN;id_test <= PMIC_HI6559_DR_MAX; id_test++)
    {
        ret = bsp_hi6559_dr_set_mode(id_test, PMU_DRS_MODE_FLA_FLASH);
        if(BSP_PMU_OK != ret)
        {
            pmic_print_error("bsp_hi6559_dr_set_mode err, ret %d!\n", ret);
            result |= ret;
        }
        
        mode = bsp_hi6559_dr_get_mode(id_test);
        if(PMU_DRS_MODE_FLA_FLASH != mode)
        {
            pmic_print_error("test error\n");
            result |= BSP_PMU_ERROR;
            break;
        }
        ret = bsp_hi6559_dr_set_mode(id_test, PMU_DRS_MODE_FLA_LIGHT);
        if(BSP_PMU_OK != ret)
        {
            pmic_print_error("bsp_hi6559_dr_set_mode err, ret %d!\n", ret);
            result |= ret;
        }
        
        mode = bsp_hi6559_dr_get_mode(id_test);
        if(PMU_DRS_MODE_FLA_LIGHT != mode)
        {
            pmic_print_error("test error\n");
            result |= BSP_PMU_ERROR;
            break;
        }
    }

    if(!result)
    {
        pmic_print_error("hi6559_dr_bre_mode_test ok!!\n");
    }
    else
    {
        pmic_print_error("hi6559_dr_bre_mode_test failed, return %d!!\n", result);
    }    

    return result;
}

/*****************************************************************************
 �� �� ��  : hi6559_dr_err_mode_test
 ��������  : DRģʽ�����֧����
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 hi6559_dr_mode_err_test(void)
{
    dr_mode_e  mode = PMU_DRS_MODE_BUTTOM;
    s32 iret = 0;
    s32 result = BSP_PMU_OK;

    /* ģʽ���� */
    iret = bsp_hi6559_dr_set_mode(PMIC_HI6559_DR_MIN,PMU_DRS_MODE_BUTTOM);
    if(BSP_PMU_ERROR != iret)
    {
        pmic_print_error("bsp_hi6559_dr_set_mode err mode test error, ret %d!\n", iret);
        result |= iret;
    }
    /*��Чid*/
    iret = bsp_hi6559_dr_set_mode(PMIC_HI6559_DR_MAX + 1,PMU_DRS_MODE_BRE);/*lint !e415 !e831*/
    if(BSP_PMU_PARA_ERROR != iret)
    {
        pmic_print_error("bsp_hi6559_dr_set_mode err para test errorʱ, ret %d!\n", iret);
        result |= iret;
    }
    /*��Чid*/
    mode = bsp_hi6559_dr_get_mode(PMIC_HI6559_DR_MAX + 1);/*lint !e415 !e831*/
    if(PMU_DRS_MODE_BUTTOM != mode)
    {
        pmic_print_error("bsp_hi6559_dr_get_mode err para test error!\n");
        result |= BSP_PMU_ERROR;
    }
    
    if(!result)
    {
        pmic_print_error("hi6559_dr_mode_err_test ok!!\n");
    }
    else
    {
        pmic_print_error("hi6559_dr_mode_err_test failed, return %d!!\n", result);
    } 
    
    return result;
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_dr_onoff_test
 ��������  : DR���ز���
 �������  : @test_times - ���Դ���
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 bsp_hi6559_dr_onoff_test(u32 test_times)
{
    u32 fail_times[3] = {0,0,0};
    u32 test_counts = 0;
    s32 result = BSP_PMU_OK;
    s32 ret = BSP_PMU_OK;
    
    for(test_counts = 0; test_counts < test_times ; test_counts++)
    {
        ret = hi6559_dr_enable_test();
        if(BSP_PMU_OK != ret)
        {
            fail_times[0]++;
            result |= ret;
        }

        ret = hi6559_dr_disable_test();
        if(BSP_PMU_OK != ret)
        {
            fail_times[1]++;
            result |= ret;
        }

        ret = hi6559_dr_onoff_err_test();
        if(BSP_PMU_OK != ret)
        {
            fail_times[2]++;
            result |= ret;
        }
    }

    if((0 != fail_times[0]) || (0 != fail_times[1]) || (0 != fail_times[2]))
    {
        pmic_print_error("test %d times ,enable %d times failed,disable %d times failed,err check %d times failed!!\n",test_times,fail_times[0],fail_times[1],fail_times[2]);
    }
    else
    {
        pmic_print_error("bsp_hi6559_dr_onoff_test %d times ok!!\n", test_times);
    }

    return result;
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_dr_setget_test
 ��������  : DR��������/��ȡ���ܲ���
 �������  : @test_times - ���Դ���
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 bsp_hi6559_dr_setget_test(u32 test_times)
{
    u32 fail_times[2] = {0,0};
    u32 test_counts = 0;
    s32 result = BSP_PMU_OK;
    s32 ret = BSP_PMU_OK;

    for(test_counts = 0; test_counts < test_times ; test_counts++)
    {
        ret = hi6559_dr_current_test();
        if(BSP_PMU_OK != ret)
        {
            fail_times[0]++;
            result |= ret;
        }
        
        ret = hi6559_dr_current_err_test();
        if(BSP_PMU_OK != ret)
        {
            fail_times[1]++;
            result |= ret;
        }
    }

    if((0 != fail_times[0])||(0 != fail_times[1]))
    {
        pmic_print_error("ERROR bsp_hi6559_dr_setget_test: test %d times ,current setget %d times failed,err check %d times failed!!\n",test_times,fail_times[0],fail_times[1]);
    }
    else
    {
        pmic_print_error("bsp_hi6559_dr_setget_test %d times ok!!\n",test_times);
    }

    return result;
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_dr_mode_test
 ��������  : DRģʽ����/��ȡ���ܲ���
 �������  : @test_times - ���Դ���
 �������  : ��
 �� �� ֵ  : 0 - �ɹ���else - ʧ��
*****************************************************************************/
s32 bsp_hi6559_dr_mode_test(u32 test_times)
{
    u32 fail_times[3] = {0,0,0};
    u32 test_counts = 0;
    s32 result = BSP_PMU_OK;
    s32 ret = BSP_PMU_OK;

    for(test_counts = 0; test_counts < test_times; test_counts++)
    {
        ret = hi6559_dr_bre_mode_test();
        if(BSP_PMU_OK != ret)
        {
            fail_times[0]++;
            result |= ret;
        }
        
        ret = hi6559_dr_fla_mode_test();
        if(BSP_PMU_OK != ret)
        {
            fail_times[1]++;
            result |= ret;
        }
        
        ret = hi6559_dr_mode_err_test();
        if(BSP_PMU_OK != ret)
        {
            fail_times[2]++;
            result |= ret;
        }
    }

    if((0 != fail_times[0]) || (0 != fail_times[1]) || (0 != fail_times[2]))
    {
        pmic_print_error("ERROR bsp_hi6559_dr_mode_test %d times ,bre mode: %d times failed,fla mode: %d times failed,mode err :%d times failed!!\n",\
                        test_times,fail_times[0],fail_times[1],fail_times[2]);
    }
    else
    {
        pmic_print_error("bsp_hi6559_dr_mode_test ok!!\n",test_times);
    }

    return result;
}
#endif

/*****************************************************************************
 �� �� ��  : bsp_hi6559_test_init
 ��������  : hi6559 testģ��ĳ�ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
s32 bsp_hi6559_test_init(void)
{
    s32 iret = BSP_PMU_OK;

    struct pmu_test_ops hi6559_test_ops = {
        .pmu_volt_onoff_test = bsp_hi6559_volt_onoff_test,
        .pmu_volt_setget_test = bsp_hi6559_volt_setget_test,
        .pmu_volt_mode_test = bsp_hi6559_volt_mode_test,
        .pmu_volt_table_test = bsp_hi6559_volttable_test,
#ifdef __KERNEL__
        .pmu_dr_onoff_test = bsp_hi6559_dr_onoff_test,
        .pmu_dr_setget_test = bsp_hi6559_dr_setget_test,
        .pmu_dr_mode_test = bsp_hi6559_dr_mode_test,
#endif
    };

    iret = bsp_pmu_test_register(PMIC_HI6559,hi6559_test_ops);

    if(BSP_PMU_OK != iret)
        pmic_print_error("bsp_pmu_test_register error!\n");
    else
        pmic_print_info("bsp_hi6559_test_init ok!\n");

    return iret;
}




