/*
 * pmu_hi6559.c -- simple synchronous userspace interface to SSI devices
 *
 * Copyright (C) 2006 SWAPP
 *  Andrea Paterniani <a.paterniani@swapp-eng.it>
 * Copyright (C) 2007 David Brownell (simplification, cleanup)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*lint --e{537,958}*/
#ifdef __KERNEL__
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/clk.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <drv_comm.h>
#include <asm/uaccess.h>
#endif

#include <product_config.h>
#include <osl_bio.h>
#include <osl_thread.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#include <soc_memmap.h>
#include <hi_bbstar.h>
#include <bsp_shared_ddr.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#ifdef __KERNEL__
#include <drv_comm.h>
#endif
#ifdef __VXWORKS__
#include <drv_dpm.h>
#include <drv_pmu.h>
#include <bsp_regulator.h>
#endif

#include <bsp_version.h>
#include <bsp_nvim.h>
#include <bsp_ipc.h>

#ifdef __VXWORKS__
#include <bsp_regulator.h>
#include "pmu_hi6559.h"
#endif

#include "common_hi6559.h"
#include <pmu_balong.h>

#define HI6559_LVS_VOLTAGE 1800000  /* LVS��ѹΪ�̶�ֵ1800000uV */

typedef unsigned long hi6559_pmuflags_t;
typedef struct /* BUCK��ѹ���� */
{
    s32 volt_base;
    s32 volt_step;

}PMIC_HI6559_BUCK_ADJ;

spinlock_t  hi6559_pmu_lock;
static u32 smart_pmu_base_addr;
static u8 volt_ocp_on_flag;

static const PMIC_HI6559_BUCK_ADJ hi6559_buck_volt[PMIC_HI6559_BUCK_MAX + 1] =
{
    { 900000, 50000}, /* BUCK0 */
    { 700000,  8000}, /* BUCK3 */
    {1200000, 25000}, /* BUCK4 */
    {      0,     0}, /* BUCK5��Ϊ��λ���˴���׮ */
    {1800000, 25000}, /* BUCK6 */
};


#if defined(__KERNEL__) || defined(__VXWORKS__)

/* �����:�˼���+������ */
#define pmu_hi6559_mutli_core_lock(flags)      \
    do {                            \
        /*lint --e{746,718}*/ \
        spin_lock_irqsave(&hi6559_pmu_lock,flags);     \
        (void)bsp_ipc_spin_lock(IPC_SEM_PMU_HI6559);   \
    } while (0)
    
#define pmu_hi6559_mutli_core_unlock(flags)        \
    do {                            \
        (void)bsp_ipc_spin_unlock(IPC_SEM_PMU_HI6559);   \
        spin_unlock_irqrestore(&hi6559_pmu_lock,flags);       \
    } while (0)
    
/* ������:������ */
#define pmu_hi6559_single_core_lock(flags)      \
    do {                            \
        spin_lock_irqsave(&hi6559_pmu_lock,flags);      \
    } while (0)
#define pmu_hi6559_single_core_unlock(flags)        \
    do {                            \
        spin_unlock_irqrestore(&hi6559_pmu_lock,flags);      \
    } while (0)

/* mcore�в���Ҫ������Ϊ�� */
#elif defined(__CMSIS_RTOS)

#define pmu_hi6559_mutli_core_lock(flags) 
#define pmu_hi6559_mutli_core_unlock(flags) 
#define pmu_hi6559_single_core_lock(flags)  
#define pmu_hi6559_single_core_unlock(flags) 

#endif

/*****************************************************************************
* �� �� ��  : hi6559_volt_para_check
*
* ��������  : ����ѹԴ�Ƿ�Ϸ�
*
* �������  : @volt_id�������ĵ�ѹԴ
*
* �������  : ��
*
* �� �� ֵ  : BSP_PMU_OK:�Ϸ�;   BSP_PMU_ERROR:���Ϸ�
*****************************************************************************/
s32 hi6559_volt_para_check(s32 volt_id)
{
    /* ��Ч�Լ�� */
    if ((PMIC_HI6559_VOLT_MAX < volt_id) || (PMIC_HI6559_VOLT_MIN > volt_id))
    {
        pmic_print_error("PMIC doesn't have volt %d!\n",volt_id);
        pmic_print_error("the volt you can use in this PMIC is from %d to %d,please check!\n", PMIC_HI6559_VOLT_MIN, PMIC_HI6559_VOLT_MAX);
        return BSP_PMU_ERROR;
    }
    else
    {
        return BSP_PMU_OK;
    }
}

/*****************************************************************************
* �� �� ��  : hi6559_volt_table_check
*
* ��������  : ����ѹԴ���Ա��Ƿ����
*
* �������  : @hi6559_volt_table ��ѹԴ���Ա��ַ
*
* �������  : ��
*
* �� �� ֵ  : BSP_PMU_OK:����;   BSP_PMU_ERROR:������
*****************************************************************************/
static __inline__ s32 hi6559_volt_table_check(PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table)
{
    if(((unsigned long)SHM_PMU_VOLTTABLE_MAGIC_START_DATA == hi6559_volt_table->magic_start) && 
       ((unsigned long)SHM_PMU_VOLTTABLE_MAGIC_END_DATA == hi6559_volt_table->magic_end))
    {
        return BSP_PMU_OK;
    }
    else
    {
        return BSP_PMU_ERROR;
    }
}

/*****************************************************************************
* �� �� ��  : hi6559_reg_write
*
* ��������  : ��pmuоƬ�Ĵ�����д����
*
* �������  : u16 addr����д��ļĴ�����ַ
*             u8 u8Data����д�������
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_hi6559_reg_write( u16 addr, u8 value)
{
    writel((u32) value,(u32)(smart_pmu_base_addr + (addr << 2)));
}

/*****************************************************************************
* �� �� ��  : hi6559_reg_read
*
* ��������  : ��pmuоƬ�Ĵ����Ķ�����
*
* �������  : u16 addr����д��ļĴ�����ַ
*             u8 u8Data������������
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
void  bsp_hi6559_reg_read( u16 addr, u8 *pValue)
{   
    /*lint !e958*/
    *pValue = (u8)readl((u32)(smart_pmu_base_addr + (addr << 2)));
}

/*****************************************************************************
* �� �� ��  : hi6559_reg_write_mask
*
* ��������  : ��pmuоƬ�Ĵ�����ĳЩbitдֵ���磬��Ĵ���0x20��bit3д��1����bsp_hi6559_reg_write_mask(0x20, 1, 8)
*
* �������  : u16 addr����д��ļĴ�����ַ
*             u8 u8Data������������
*             u8 mask: ��д��bit��mask
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_hi6559_reg_write_mask(u16 addr, u8 value, u8 mask)
{
    u8 reg_tmp = 0;

    bsp_hi6559_reg_read(addr, &reg_tmp);
    reg_tmp &= ~mask;
    reg_tmp |= value;
    bsp_hi6559_reg_write(addr, reg_tmp);
}

/*****************************************************************************
* �� �� ��  : hi6559_reg_write_mask
*
* ��������  : ��pmuоƬ�Ĵ�����ĳЩbitдֵ���磬��Ĵ���0x20��bit3д��1����bsp_hi6559_reg_write_mask(0x20, 1, 8)
*
* �������  : u16 addr����д��ļĴ�����ַ
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
s32 bsp_hi6559_reg_show(u16 addr)
{
    u8 Value = 0;

    bsp_hi6559_reg_read(addr, &Value);
    pmic_print_info("pmuRead addr 0x%x value is 0x%x!!\n",addr,Value);
    return Value;
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_enable
 ��������  : ʹ�ܵ�Դvolt_id
 �������  : @volt_id ��Դid
 �������  : ��
 �� �� ֵ  : BSP_PMU_OK: �ɹ��� else:ʧ��
*****************************************************************************/
s32 bsp_hi6559_volt_enable(s32 volt_id)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    PMIC_HI6559_VLTGS_ATTR *hi6559_volt = NULL;
    hi6559_pmuflags_t flags = 0;
    u32 *pmu_ocp_flag = (u32 *)SHM_PMU_OCP_INFO_ADDR;/*��������Ҫ�رյĹ���Դ*/
    s32 iret = BSP_PMU_OK;
    u8 regval = 0;

    /* ������Ч�Լ�� */
    iret = hi6559_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }
    
    /* ��ѹ���Ա�ȫ�Լ�� */
    iret = hi6559_volt_table_check(hi6559_volt_table);
    if(BSP_PMU_OK != iret)
    {
        return  BSP_PMU_VOLTTABLE_ERROR;
    }

    /* �����������򲻴� */
    if((*pmu_ocp_flag & ((u32)0x1 << volt_id))&& !volt_ocp_on_flag)
    {
        pmic_print_error("volt_id %d current overflow,can not open!\n",volt_id);
        return BSP_PMU_ERROR;
    }
    
    hi6559_volt = &hi6559_volt_table->hi6559_volt_attr[volt_id];
    
    /* д1ʹ�ܣ�����LDO9��LDO11��ʹ����ͬһ���Ĵ����ϣ�Ҫ�ȶ���д�������ֱ��д */
    if(PMIC_HI6559_LDO09 == volt_id)
    {
        /*Acore��sim���Ȳ���жϴ����Ccore��sim����ʼ��ʱ����Ҫ�������ʺ˼���+������*/
        pmu_hi6559_mutli_core_lock(flags);
        bsp_hi6559_reg_read(hi6559_volt->enable_reg_addr, &regval);
        regval |= (u8)((u32)0x3 << hi6559_volt->enable_bit_offset); /* ʹ��LDO9��ͬʱ��ʹ��SIM��ת����· */
        bsp_hi6559_reg_write(hi6559_volt->enable_reg_addr, regval);
        
        /*����sim�������������ã����ڿ�����Դ�󣬷�����ë��*/
        bsp_hi6559_reg_write(HI6559_SIM_CFG_OFFSET, 0x10);
        
        pmu_hi6559_mutli_core_unlock(flags);
    }
    else if(PMIC_HI6559_LDO11 == volt_id)
    {
        /* ��LDO9������ͬһ�Ĵ������ʺ˼���*/
        pmu_hi6559_mutli_core_lock(flags);
        bsp_hi6559_reg_read(hi6559_volt->enable_reg_addr, &regval);
        regval |= (u8)((u32)0x1 << hi6559_volt->enable_bit_offset);
        bsp_hi6559_reg_write(hi6559_volt->enable_reg_addr, regval);
        pmu_hi6559_mutli_core_unlock(flags);
    }
    else
    {
        regval = (u8)((u32)0x1 << hi6559_volt->enable_bit_offset);
        bsp_hi6559_reg_write(hi6559_volt->enable_reg_addr, regval);
    }    

    return BSP_PMU_OK;

}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_disable
 ��������  : ��ֹ��Դvolt_id
 �������  : @volt_id ��Դid
 �������  : ��
 �� �� ֵ  : BSP_PMU_OK: �ɹ��� else:ʧ��
*****************************************************************************/
s32 bsp_hi6559_volt_disable(s32 volt_id)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    PMIC_HI6559_VLTGS_ATTR *hi6559_volt = NULL;
    hi6559_pmuflags_t flags = 0;
    s32 iret = BSP_PMU_OK;
    u8 regval = 0;

    /* ������Ч�Լ�� */
    iret = hi6559_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }
    
    /* ��ѹ���Ա�ȫ�Լ�� */
    iret = hi6559_volt_table_check(hi6559_volt_table);
    if(BSP_PMU_OK != iret)
    {
        return  BSP_PMU_VOLTTABLE_ERROR;
    }
    
    hi6559_volt = &hi6559_volt_table->hi6559_volt_attr[volt_id];

    /* LDO9/11��д0�رգ�����ͬһ���Ĵ����ϣ�Ҫ�ȶ���д�������ֱ��д�Ҷ���д1�ر� */
    if(PMIC_HI6559_LDO09 == volt_id)
    {
        /*Acore��sim���Ȳ���жϴ����Ccore��sim����ʼ��ʱ����Ҫ�������ʺ˼���+������*/
        pmu_hi6559_mutli_core_lock(flags);
        bsp_hi6559_reg_write_mask(HI6559_SIM_CFG_OFFSET,0x0c,0x1c);/*ͬʱ�ر�sim0��bb����������*/

        bsp_hi6559_reg_read(hi6559_volt->disable_reg_addr, &regval);
        regval &= ~(u8)((u32)0x3 << hi6559_volt->disable_bit_offset);
        bsp_hi6559_reg_write(hi6559_volt->disable_reg_addr, regval);
        pmu_hi6559_mutli_core_unlock(flags);
    }
    else if(PMIC_HI6559_LDO11 == volt_id)
    {
        /* ��LDO9������ͬһ�Ĵ������ʺ˼���*/
        pmu_hi6559_mutli_core_lock(flags);
        bsp_hi6559_reg_read(hi6559_volt->disable_reg_addr, &regval);
        regval &= ~(u8)((u32)0x1 << hi6559_volt->disable_bit_offset);
        bsp_hi6559_reg_write(hi6559_volt->disable_reg_addr, regval);
        pmu_hi6559_mutli_core_unlock(flags);
    }
    else
    {
        regval = (u8)((u32)0x1 << hi6559_volt->disable_bit_offset);
        bsp_hi6559_reg_write(hi6559_volt->disable_reg_addr, regval);
    }

    return BSP_PMU_OK;

}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_is_enabled
 ��������  : ��ѯĳ·��ѹԴ�Ƿ�����
 �������  : volt_id:��ѹԴid��
 �������  : ��
 �� �� ֵ  : 0:δ������else:����
*****************************************************************************/
s32 bsp_hi6559_volt_is_enabled(s32 volt_id)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    PMIC_HI6559_VLTGS_ATTR *hi6559_volt;
    s32 iret = BSP_PMU_OK;
    u8 regval = 0;

    /* ������Ч�Լ�� */
    iret = hi6559_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }
    /* ��ѹ���Ա�ȫ�Լ�� */
    iret = hi6559_volt_table_check(hi6559_volt_table);
    if(BSP_PMU_OK != iret)
    {
        return  BSP_PMU_VOLTTABLE_ERROR;
    }
    
    hi6559_volt = &hi6559_volt_table->hi6559_volt_attr[volt_id];

    bsp_hi6559_reg_read(hi6559_volt->is_enabled_reg_addr, &regval);

    /* ����״̬bitΪ1ʱ����ʾ��ʹ�� */
    return (regval & ((u32)0x1 << hi6559_volt->is_enabled_bit_offset));
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_get_voltage
 ��������  : ��ȡ��ѹԴvolt_id�ĵ�ѹֵ
 �������  : volt_id:��ѹԴid��
 �������  : ��
 �� �� ֵ  : ��ѹֵ
*****************************************************************************/
s32 bsp_hi6559_volt_get_voltage(s32 volt_id)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    PMIC_HI6559_VLTGS_ATTR *hi6559_volt;
    s32 voltage = 0;
    s32 iret  = BSP_PMU_OK;
    u8 regval = 0;
    u8 vltg = 0;

    /* ������Ч�Լ�� */
    iret = hi6559_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }

    /*DDR�е�ѹ���Ա�ȫ�Լ��*/
    iret = hi6559_volt_table_check(hi6559_volt_table);
    if(BSP_PMU_OK != iret)
    {
        return  BSP_PMU_VOLTTABLE_ERROR;
    }

    /*LVS�ĵ�ѹĬ����1.8v�����ܸı�*/
    if((PMIC_HI6559_LVS_MIN <= volt_id ) && (PMIC_HI6559_LVS_MAX >= volt_id))
    {
        pmic_print_info("volt_id %d's voltage is  %d uV!\n", volt_id, HI6559_LVS_VOLTAGE);
        return HI6559_LVS_VOLTAGE;
    }

    hi6559_volt = (PMIC_HI6559_VLTGS_ATTR *)&(hi6559_volt_table->hi6559_volt_attr[volt_id]);

    bsp_hi6559_reg_read(hi6559_volt->voltage_reg_addr, &regval);

    /* ��ȡ��ѹ��λֵ */
    vltg = (regval & hi6559_volt->voltage_bit_mask) >> hi6559_volt->voltage_bit_offset;

    /* LDO��buck5�ĵ�ѹֵΪ��λ������buck���� */
    if((PMIC_HI6559_BUCK_MAX >= volt_id) && (PMIC_HI6559_BUCK5 != volt_id))
    {
        voltage = (hi6559_buck_volt[volt_id].volt_base + vltg * hi6559_buck_volt[volt_id].volt_step);
    }
    else
    {
        voltage = hi6559_volt->voltage_list[vltg];
    }

    pmic_print_info("volt_id %d's voltage is  %d uV!\n", volt_id, voltage);

    return voltage;

}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_set_voltage
 ��������  : ���õ�ѹԴvolt_id�ĵ�ѹֵ������Ϊ[min_uV, max_uV]�����ֵ���ɣ����������û�кϷ�ֵ��ʧ�ܷ���
 �������  : volt_id: Ҫ���õĵ�Դ���
             min_uV: ��С�Ϸ���ѹֵ
             max_uV: ���Ϸ���ѹֵ
 �������  : @selector: ʵ�����õ�ѹֵ�ĵ�λ
 �� �� ֵ  : BSP_PMU_OK: �ɹ��� else:ʧ��
*****************************************************************************/
s32 bsp_hi6559_volt_set_voltage(s32 volt_id, s32 min_uV, s32 max_uV,unsigned *selector)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    PMIC_HI6559_VLTGS_ATTR *hi6559_volt;
    hi6559_pmuflags_t flags = 0;
    s32 iret = BSP_PMU_OK;
    s32 volt_base = 0;
    s32 volt_step = 0;
    s32 valid = 0;
    s32 voltage = 0; /* ʵ�����õĵ�ѹֵ */
    
    u8 volt_nums = 0;
    u8 i = 0;

    /* ������Ч�Լ�� */
    iret = hi6559_volt_para_check(volt_id);
    if((BSP_PMU_OK != iret) || (!selector))
    {
        return BSP_PMU_PARA_ERROR;
    }

    /* DDR�е�ѹ���Ա�ȫ�Լ�� */
    iret = hi6559_volt_table_check(hi6559_volt_table);
    if(BSP_PMU_OK != iret)
    {
        return  BSP_PMU_VOLTTABLE_ERROR;
    }

    /* LVS�ĵ�ѹĬ����1.8v�����ܸı� */
    if((PMIC_HI6559_LVS_MIN <= volt_id ) && (PMIC_HI6559_LVS_MAX >= volt_id))
    {
        pmic_print_error("volt_id %d's voltage can not be set!\n", volt_id);
        return BSP_PMU_ERROR;
    }

    hi6559_volt = (PMIC_HI6559_VLTGS_ATTR *)&(hi6559_volt_table->hi6559_volt_attr[volt_id]);

    /* buck��ѹֵ����(����buck5) */
    if((PMIC_HI6559_BUCK_MAX >= volt_id) && (PMIC_HI6559_BUCK5 != volt_id))
    {
        volt_base = hi6559_buck_volt[volt_id].volt_base;
        volt_step = hi6559_buck_volt[volt_id].volt_step;
        volt_nums = hi6559_volt->voltage_nums;

        for(i = 0; i <= volt_nums; i++ )
        {
            if((min_uV <= (volt_base + i * volt_step)) && (max_uV >= (volt_base + i * volt_step)))
            {
                valid = true;   /* [min, max]��һ���Ϸ����� */
                break;
            }
        }

        /* [min, max]����Ϸ���Ѱ�������ڵĵ�ѹֵ */
        if(valid)
        {
            voltage = (volt_base + i * volt_step);
            *selector = i;
        }
    }
    else /* LDO��buck5�ĵ�ѹֵΪ��λ */
    {
        /* ��� vltg �Ƿ�Ϊ����Ӧ�ĵ�ѹԴ����Чֵ����ת����ѹֵΪ�Ĵ�������ֵ */
        for (i = 0; i <= hi6559_volt->voltage_nums; i++)
        {
            if ((min_uV <= hi6559_volt->voltage_list[i]) && (max_uV >= hi6559_volt->voltage_list[i]))
            {
                valid = true;
                break;
            }
        }
        voltage = hi6559_volt->voltage_list[i];
        *selector = i;
    }

    /* �������ֵ��Ч�����üĴ��� */
    if (valid)
    {
        pmu_hi6559_single_core_lock(flags);
        bsp_hi6559_reg_write_mask(hi6559_volt->voltage_reg_addr, (u8)((u32)i << hi6559_volt->voltage_bit_offset), hi6559_volt->voltage_bit_mask);
        pmu_hi6559_single_core_unlock(flags);
        pmic_print_info("voltage is set at %d uV!\n", voltage);
        return BSP_PMU_OK;
    }
    else
    {
        pmic_print_error("volt_id %d cann't support voltage between %d and %d uV!\n",volt_id,min_uV,max_uV);
        return BSP_PMU_ERROR;
    }

}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_list_voltage
 ��������  : ��ȡ��ѹԴvolt_id��λΪselector�ĵ�ѹֵ
 �������  : volt_id: Ҫ���õĵ�Դ���
             selector: ��ѹ��λ
 �� �� ֵ  : BSP_PMU_OK: �ɹ��� else:ʧ��
*****************************************************************************/
s32 bsp_hi6559_volt_list_voltage(s32 volt_id, unsigned selector)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    PMIC_HI6559_VLTGS_ATTR *hi6559_volt;
    s32 iret = BSP_PMU_OK;
    s32 voltage = 0;

    /* ������Ч�Լ�� */
    iret = hi6559_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }
    
    /* ��ѹ���Ա�ȫ�Լ�� */
    iret = hi6559_volt_table_check(hi6559_volt_table);
    if(BSP_PMU_OK != iret)
    {
        return  BSP_PMU_VOLTTABLE_ERROR;
    }

    hi6559_volt = &hi6559_volt_table->hi6559_volt_attr[volt_id];

    /* ��鵵λ��Ч�� */
    if (selector > hi6559_volt->voltage_nums) 
    {
        pmic_print_error("selector is %d,not exist,-EINVAL,please input new\n", selector);
        return BSP_PMU_ERROR;
    }

    if((PMIC_HI6559_BUCK_MAX >= volt_id) && (PMIC_HI6559_BUCK5 != volt_id))/* buckΪ����(����buck5) */
    {
        voltage = (hi6559_buck_volt[volt_id].volt_base + (s32)selector * hi6559_buck_volt[volt_id].volt_step);
    }
    else if(PMIC_HI6559_LDO_MAX >= volt_id)/* LDO��buck5�ĵ�ѹֵΪ��λ */
    {
        voltage =  hi6559_volt->voltage_list[selector];
    }
    else
    {
        voltage = HI6559_LVS_VOLTAGE; /* lvsΪ�̶�ֵ */
    }
    
    pmic_print_info("volt %d selector %d is %d uV!!\n",volt_id,selector,voltage);

    return voltage;

}
/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_list_show
 ��������  : ��ʾ��ǰ����·��Դ�����е�λֵ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void bsp_hi6559_volt_list_show(s32 volt_id)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    PMIC_HI6559_VLTGS_ATTR *hi6559_volt;
    s32 iret = BSP_PMU_OK;
    s32 voltage = 0;
    unsigned selector = 0;

    /* ������Ч�Լ�� */
    iret = hi6559_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return;
    }
    
    /* ��ѹ���Ա�ȫ�Լ�� */
    iret = hi6559_volt_table_check(hi6559_volt_table);
    if(BSP_PMU_OK != iret)
    {
        return;
    }

    hi6559_volt = &hi6559_volt_table->hi6559_volt_attr[volt_id];

    for(selector = 0;selector <= hi6559_volt->voltage_nums;selector++)
    {
        voltage = bsp_hi6559_volt_list_voltage(volt_id,selector);
        pmic_print_error("volt %d selector %d is %d uV!!\n",volt_id,selector,voltage);
    }

    return;
}
/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_get_mode
 ��������  : PMIC HI6559��Դģʽ��ѯ
            (֧��normal�͸���PMU����eco��ǿ�ƽ���eco����ģʽ,
             ��֧��ģʽ��·����PMU_MODE_NONE)
 �������  : volt_id:Ҫ��ѯ�ĵ�Դ���
 �������  : ��
 �� �� ֵ  : ��ѹԴ�����ģʽ
 ��ע˵��  : Acore��Ccore���ṩ�ú���ʵ�֣�ֻ��������Ҫ�����
*****************************************************************************/
pmu_mode_e bsp_hi6559_volt_get_mode(s32 volt_id)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    PMIC_HI6559_VLTGS_ATTR *hi6559_volt;
    s32 iret = BSP_PMU_OK;
    u8 regval = 0;

    /* ������Ч�Լ�� */
    iret = hi6559_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return PMU_MODE_BUTTOM;
    }

    /* ��ѹ���Ա�ȫ�Լ�� */
    iret = hi6559_volt_table_check(hi6559_volt_table);
    if(BSP_PMU_OK != iret)
    {
        return PMU_MODE_BUTTOM;
    }

    hi6559_volt = &hi6559_volt_table->hi6559_volt_attr[volt_id];

    /* �жϸ�·�Ƿ���ecoģʽ�����û�У�����NONE */
    if((hi6559_volt->eco_force_reg_addr == PMU_INVAILD_ADDR) && (hi6559_volt->eco_follow_reg_addr == PMU_INVAILD_ADDR))
    {
        pmic_print_info("volt_id[%d] have no eco mode\n", volt_id);
        return PMU_MODE_NONE;          
    }
    
    /* force �����ȼ���� */
    if(hi6559_volt->eco_force_reg_addr != PMU_INVAILD_ADDR)
    {
        bsp_hi6559_reg_read(hi6559_volt->eco_force_reg_addr, &regval);
        if(regval & ((u8)((u32)0x1 << hi6559_volt->eco_force_bit_offset)))
        {
            pmic_print_info("volt_id[%d] is in force eco mode\n", volt_id);
            return PMU_MODE_ECO_FORCE;  /* eco mode */
        }
    }

    if(hi6559_volt->eco_follow_reg_addr != PMU_INVAILD_ADDR)
    {
        bsp_hi6559_reg_read(hi6559_volt->eco_follow_reg_addr, &regval);
        if(regval & ((u8)((u32)0x1 << hi6559_volt->eco_follow_bit_offset)))
        {
            pmic_print_info("volt_id[%d] is in follow eco mode\n", volt_id);
            return PMU_MODE_ECO_FOLLOW; /* eco mode */
        }
    }

    pmic_print_info("volt_id[%d] is in normal mode\n", volt_id);

    /* ��·֧��ECOģʽ�����ǲ�����ECOģʽ������NORMAL */
    return PMU_MODE_NORMAL;             
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_set_mode
 ��������  : PMIC HI6559��Դģʽ����(֧��normal/follow_eco/force_eco����ģʽ,ֻ���ض�·֧��)
 �������  : @volt_id: ��ѹԴid
             @mode:ģʽ
 �������  : ��
 �� �� ֵ  : BSP_PMU_OK: �ɹ��� else:ʧ��
 ��ע˵��  : ֻ��Acore�ṩ�ú���ʵ�֣�������Ӻ˼�����ֻʹ�ú�����
*****************************************************************************/
s32 bsp_hi6559_volt_set_mode(s32 volt_id, pmu_mode_e mode)
{
    PMIC_HI6559_VLTGS_TABLE *hi6559_volt_table = (PMIC_HI6559_VLTGS_TABLE *)SHM_PMU_VOLTTABLE_ADDR;
    PMIC_HI6559_VLTGS_ATTR *hi6559_volt;
    s32 iret = BSP_PMU_OK;
    u8 regval = 0;

    /* ������Ч�Լ�� */
    iret = hi6559_volt_para_check(volt_id);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_PARA_ERROR;
    }

    /* ��ѹ���Ա�ȫ�Լ�� */
    iret = hi6559_volt_table_check(hi6559_volt_table);
    if(BSP_PMU_OK != iret)
    {
        return BSP_PMU_VOLTTABLE_ERROR;
    }
    
    hi6559_volt = &hi6559_volt_table->hi6559_volt_attr[volt_id];

    /*�жϸ�·�Ƿ���ecoģʽ*/
    if(((PMU_INVAILD_ADDR == hi6559_volt->eco_force_reg_addr) && (PMU_MODE_ECO_FORCE== mode)) ||
       ((PMU_INVAILD_ADDR == hi6559_volt->eco_follow_reg_addr) && (PMU_MODE_ECO_FOLLOW== mode)))
    {
        pmic_print_error("PMIC HI6559 this volt doesn't have eco mode!\n");
        return BSP_PMU_ERROR;
    }

    /* ���ݲ�ͬ��ģʽ�������� */
    switch(mode)
    {
        case PMU_MODE_NORMAL:
            pmic_print_info("volt_id[%d] will be set normal mode\n", volt_id);

            if(PMU_INVAILD_ADDR != hi6559_volt->eco_force_reg_addr)
            {
                bsp_hi6559_reg_read(hi6559_volt->eco_force_reg_addr, &regval);
                regval &= ~(u8)((u32)0x1 << hi6559_volt->eco_force_bit_offset);
                bsp_hi6559_reg_write(hi6559_volt->eco_force_reg_addr, regval);
            }

            if(PMU_INVAILD_ADDR != hi6559_volt->eco_follow_reg_addr)
            {
                bsp_hi6559_reg_read(hi6559_volt->eco_follow_reg_addr, &regval);
                regval &= ~(u8)((u32)0x1 << hi6559_volt->eco_follow_bit_offset);
                bsp_hi6559_reg_write(hi6559_volt->eco_follow_reg_addr, regval);
            }
            break;

        case PMU_MODE_ECO_FOLLOW:
            pmic_print_info("volt_id[%d] will be set eco FOLLOW mode\n", volt_id);
            
            if(PMU_INVAILD_ADDR != hi6559_volt->eco_follow_reg_addr)
            {
                bsp_hi6559_reg_read(hi6559_volt->eco_follow_reg_addr, &regval);
                regval |= (u8)((u32)0x1 << hi6559_volt->eco_follow_bit_offset);
                bsp_hi6559_reg_write(hi6559_volt->eco_follow_reg_addr, regval);
            }
            break;

        case PMU_MODE_ECO_FORCE:
            pmic_print_info("volt_id[%d] will be set eco FORCE mode\n", volt_id);
            
            if(PMU_INVAILD_ADDR != hi6559_volt->eco_force_reg_addr)
            {
                bsp_hi6559_reg_read(hi6559_volt->eco_force_reg_addr, &regval);
                regval |= (u8)((u32)0x1 << hi6559_volt->eco_force_bit_offset);
                bsp_hi6559_reg_write(hi6559_volt->eco_force_reg_addr, regval);
            }            
            break;

        default:
            pmic_print_error("ERROR: unkonwn mode %d\n", mode);
            return BSP_PMU_ERROR;
    }

    return BSP_PMU_OK;
}

/*****************************************************************************
 �� �� ��  : bsp_pmu_hi6559_init
 ��������  : PMIC HI6559 PMUģ���ʼ��
 �������  : ��
 �������  : ��
*****************************************************************************/
s32 bsp_pmu_hi6559_init(void)
{
    s32 iret = BSP_PMU_OK;

    smart_pmu_base_addr = HI_PMUSSI0_REGBASE_ADDR;

#ifdef __KERNEL__
    smart_pmu_base_addr = (u32)ioremap(smart_pmu_base_addr,HI_PMUSSI0_REG_SIZE);
    if(0 == smart_pmu_base_addr)
    {
        pmic_print_error("cannot map IO!\n");
        return BSP_PMU_ERROR;
    }
#endif

    /* ��NV����ȡ�쳣�������� */
    iret = (s32)bsp_nvm_readpart(NV_ID_DRV_NV_PMU_EXC_PRO, 0, &volt_ocp_on_flag, sizeof(u8));
    if(NV_OK != iret)
    {
        pmic_print_error("ERROR:pmu exc pro read nv error,not set,use the default config!\n");
    }

    spin_lock_init(&hi6559_pmu_lock);
    
    /* ��ʼ��commonģ���lock */
    bsp_hi6559_common_init();
    
    /* debug��ʼ�� */
    bsp_hi6559_debug_init();

    return iret;
}

s32 hi6559_sim_upres_disable(u32 sim_id)
{
    return BSP_PMU_OK;
}

#ifdef __VXWORKS__
/*****************************************************************************
 ����	: bsp_pmu_hi6559_apt_enable
 ����	: ͨ��ģ��ʹ��APT״̬�ӿ�
 ����	: ��
 ���	: ��
 ����	: 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 bsp_pmu_hi6559_apt_enable(void)
{
    hi6559_pmuflags_t flags = 0;
    
    /* buck0 apt���ܿ��ƼĴ���0x58���ܵ�һ����ֱ��д */
    pmu_hi6559_single_core_lock(flags);

    /* �Ĵ����Ż����ã���оƬ��Ӳ������ */
    bsp_hi6559_reg_write(HI6559_BUCK0_REG12_ADJ_OFFSET, 0x10);
    bsp_hi6559_reg_write(HI6559_BUCK0_REG4_ADJ_OFFSET, 0xBE);
    bsp_hi6559_reg_write(HI6559_BUCK0_REG9_ADJ_OFFSET, 0x02);
    bsp_hi6559_reg_write(HI6559_BUCK0_REG16_ADJ_OFFSET, 0x6A);
    bsp_hi6559_reg_write(HI6559_BUCK0_REG9_ADJ_OFFSET, 0x42);

    /* apt enable */
    bsp_hi6559_reg_write(HI6559_BUCK0_REG5_ADJ_OFFSET, 0x1);
    pmu_hi6559_single_core_unlock(flags);
    return BSP_PMU_OK;
}

/*****************************************************************************
 ����	: bsp_pmu_hi6559_apt_enable
 ����	: ͨ��ģ��ʹ��APT״̬�ӿ�
 ����	: ��
 ���	: ��
 ����	: 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 bsp_pmu_hi6559_apt_disable(void)
{
    hi6559_pmuflags_t flags = 0;

    /* buck0 apt���ܿ��ƼĴ���0x58���ܵ�һ����ֱ��д */
    pmu_hi6559_single_core_lock(flags);

    /* �Ĵ����Ż����ã���оƬ��Ӳ������ */
    bsp_hi6559_reg_write(HI6559_BUCK0_REG16_ADJ_OFFSET, 0x3A);
    bsp_hi6559_reg_write(HI6559_BUCK0_REG9_ADJ_OFFSET, 0x02);
    bsp_hi6559_reg_write(HI6559_BUCK0_REG12_ADJ_OFFSET, 0x30);
    bsp_hi6559_reg_write(HI6559_BUCK0_REG4_ADJ_OFFSET, 0xBA);
    bsp_hi6559_reg_write(HI6559_BUCK0_REG9_ADJ_OFFSET, 0x42);

    /* apt disable */
    bsp_hi6559_reg_write(HI6559_BUCK0_REG5_ADJ_OFFSET, 0x0);
    pmu_hi6559_single_core_unlock(flags);
    return BSP_PMU_OK;
}

/*****************************************************************************
 ����	: drv_pmu_hi6559_apt_status_get
 ����	: ͨ��ģ���ȡ��ǰAPT״̬�ӿ�
 ����	: ��
 ���	: ��
 ����	: 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 bsp_pmu_hi6559_apt_status_get(void)
{
    hi6559_pmuflags_t flags = 0;
    u8 reg_val = 0;
    
    pmu_hi6559_single_core_lock(flags);
    bsp_hi6559_reg_read(HI6559_BUCK0_REG5_ADJ_OFFSET, &reg_val);
    pmu_hi6559_single_core_unlock(flags);

    pmic_print_info("reg_val %d\n", reg_val);
    
    return reg_val;
}

#endif

#ifdef __KERNEL__
arch_initcall(bsp_pmu_hi6559_init);
static void __exit bsp_pmu_hi6559_exit(void)
{
    return;
}
module_exit(bsp_pmu_hi6559_exit);

EXPORT_SYMBOL(bsp_hi6559_reg_write);
EXPORT_SYMBOL(bsp_hi6559_reg_read);
EXPORT_SYMBOL(bsp_hi6559_reg_write_mask);
#endif


