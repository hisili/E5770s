/*
 * pmu_hi6551.c -- simple synchronous userspace interface to SSI devices
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
#include <linux/workqueue.h>

#include <osl_bio.h>
#include <bsp_ipc.h>
#include <hi_smartstar.h>
#include <bsp_memmap.h>
#include <bsp_om.h>
#include <bsp_dump.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <bsp_shared_ddr.h>

#include <osl_thread.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#include <pmu_balong.h>
#include <irq_hi6551.h>
#include <common_hi6551.h>
#include "exc_hi6551.h"


/*----------------------------ȫ�ֱ���\������---------------------------------------------*/
/*�����ڴ棬�쳣��¼����0\���¡�Ƿѹ��ѹ; 1 \����; 2\rtc; 3\buck��·; 4~11\���� */
u8 pmu_hi6551_om_data[12] = {0};/*��ǰ��*//*�жϼĴ���,��˼��*/
u8 pmu_hi6551_om_boot[12] = {0};/*�ϴ�״̬����*//*���µ��ж�reg*/
static bool pmu_om_flag = false;
/*nv����*/
/*����warning����init�и�ֵ*/
PMU_EXC_PRO_NV_STRU pmu_exc_pro;
#define PMU_MODULE_ID BSP_MODU_PMU
struct hi6551_exc_data{
    spinlock_t      lock;
    struct workqueue_struct *hi6551_om_wq;
    struct delayed_work hi6551_om_wk;
};
struct hi6551_exc_data g_hi6551_exc_st;

void hi6551_om_wk_handler(void)
{
    int i,j = 0;

    /*������µ�Ĵ���ֵ*/
    for(j = 0; j < 11; j++)
    {
        print2file(PMU_OM_LOG,"pmu_hi6551:np%d:%x!\n",j+1,pmu_hi6551_om_boot[j]);
    }

    /*�����쳣����*/
    /*Ƿѹ*/
    if(pmu_hi6551_om_boot[0] & (0x01 << HI6551_VSYS_UNDER_2P5_OFFSET ) )
        print2file(PMU_OM_LOG,"pmu_hi6551:vsys under 2.5v last time!\n");
    if(pmu_hi6551_om_boot[0] & (0x01 << HI6551_VSYS_UNDER_2P7_OFFSET ) )
        print2file(PMU_OM_LOG,"pmu_hi6551:vsys under 2.7/3.0v last time!\n");
    /*��ѹ*/
    if(pmu_hi6551_om_boot[0] & (0x01 << HI6551_VSYS_OVER_6P0_OFFSET ))
        print2file(PMU_OM_LOG,"pmu_hi6551:vsys over 6.0v last time!\n");
    /*����*/
    if(pmu_hi6551_om_boot[1] & (0x01 << HI6551_OTMP_150_OFFSET ) )
        print2file(PMU_OM_LOG,"pmu_hi6551:temperature over 150�� last time!\n");
    /*otp*/
    if(pmu_hi6551_om_boot[0] & (0x01 << HI6551_OTMP_125_OFFSET))
        print2file(PMU_OM_LOG,"pmu_hi6551:temperature over 125�� last time!\n");
    /*ocp*/
    /*buck��·*/
    for (j = 1; j < 6; j++)
    {
         if (pmu_hi6551_om_boot[3] & (u8)((u32)0x1 << j))
            print2file(PMU_OM_LOG,"pmu_hi6551:Buck %d short last time!\n",j+1);
    }
    /*buck����*/
    for (j = 2; j < 8; j++)
    {
         if (pmu_hi6551_om_boot[4] & (u8)((u32)0x1 << j))
            print2file(PMU_OM_LOG,"pmu_hi6551:Buck %d overflow last time!\n",j-1);
    }

    /*ldo ocp exc handle*/
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (pmu_hi6551_om_boot[i + 5] & (u8)((u32)0x1 << j))
            {
                print2file(PMU_OM_LOG,"pmu_hi6551:LDO id %d overflow last time!\n" ,(i*8+j+1));
            }
        }
    }
    /*lvs ocp*/
    for(j = 0; j < 7; j++)
    {
        if (pmu_hi6551_om_boot[8] & (u8)((u32)0x1 << j))
        {
            if(4 == j)      /* LVS7�Ĺ���bitƫ����4 */
            {
                print2file(PMU_OM_LOG,"pmu_hi6551:LVS 7 overflow last time!\n");/*LVS��LVS2��ʼ���*/
            }
            else if(5 == j) /* LVS6�Ĺ���bitƫ����5 */
            {
                print2file(PMU_OM_LOG,"pmu_hi6551:LVS 6 overflow last time!\n");/*LVS��LVS2��ʼ���*/
            }        
            else
            {
                print2file(PMU_OM_LOG,"pmu_hi6551:LVS %d overflow last time!\n",j+2);/*LVS��LVS2��ʼ���*/
            }        
        }
    }
    for(j = 0; j < 1; j++)
    {
         if (pmu_hi6551_om_boot[9] & (u8)((u32)0x1 << j))
            print2file(PMU_OM_LOG,"pmu_hi6551:LVS %d overflow last time!\n",j+9);
    }
    /*boost,class������*/
}
void hi6551_boot_om_log_save(void)
{
    u16 j = 0;
    unsigned long timeout = 0;

    if(!pmu_om_flag)
    {
        for(j = 0; j < 11; j++)
        {
            bsp_hi6551_reg_read((HI6551_NP_IRQ1_RECORD_OFFSET+j), &pmu_hi6551_om_boot[j]);
        }
        pmu_om_flag = true;
    }

    /*��¼������pmu�����״̬����������ԭ��,��¼��־ʱ�䳤�����ù����������*/
    /*��ʼ����������*/
    g_hi6551_exc_st.hi6551_om_wq = create_singlethread_workqueue("bsp_hi6551_om");
    if (!g_hi6551_exc_st.hi6551_om_wq)
    {
        printk("%s: create_singlethread_workqueue fail\n", __FUNCTION__);
        return;
    }
    INIT_DELAYED_WORK(&g_hi6551_exc_st.hi6551_om_wk, (void *)hi6551_om_wk_handler);
    queue_delayed_work(g_hi6551_exc_st.hi6551_om_wq,&g_hi6551_exc_st.hi6551_om_wk, timeout);
}
/*****************************************************************************
 �� �� ��  : hi6551_om_log_save
 ��������  : ��¼hi6551���쳣��Ϣ
 �������  : void
 �������  : reset.log
 �� �� ֵ  : pmu�����ok
 ���ú���  :
 ��������  : ϵͳ��ά�ɲ�
*****************************************************************************/
void hi6551_om_log_save(pmu_om_log_e hi6551_om_log_flag)
{
    switch(hi6551_om_log_flag)
    {
        case PMU_OM_LOG_START:
            print2file(PMU_OM_LOG,"system start....\n");
            break;
        case PMU_OM_LOG_EXC:
            break;
        default:
            break;
    }
}
/*****************************************************************************
 �� �� ��  : hi6551_get_boot_state
 ��������  : ϵͳ����ʱ���pmu�Ĵ���״̬��
                ȷ���Ƿ�����pmu���������
 �������  : void
 �������  : reset.log
 �� �� ֵ  : pmu�����ok
 ���ú���  :
 ��������  : ϵͳ��ά�ɲ�
*****************************************************************************/
int hi6551_get_boot_state(void)
{

/*    u8 hi6551_om_boot[12] = {0};*/
    u16 j = 0;
    int iret = PMU_STATE_OK;

    if(!pmu_om_flag)/*���û�ж�ȡ�����µ�Ĵ�������û��������ȡ��ȫ�ֱ�����*/
    {
        for(j = 0; j < 11; j++)
        {
            bsp_hi6551_reg_read((HI6551_NP_IRQ1_RECORD_OFFSET+j), &pmu_hi6551_om_boot[j]);
        }
        pmu_om_flag = true;
    }
    /*Ƿѹ����ѹ*/
    if((pmu_hi6551_om_boot[0] & (0x01 << HI6551_VSYS_UNDER_2P5_OFFSET ))||(pmu_hi6551_om_boot[0] & (0x01 << HI6551_VSYS_UNDER_2P7_OFFSET )))
        iret|= PMU_STATE_UNDER_VOL;
    if(pmu_hi6551_om_boot[0] & (0x01 << HI6551_VSYS_OVER_6P0_OFFSET ))
        iret|=  PMU_STATE_OVER_VOL;
    /*����*/
    if(pmu_hi6551_om_boot[1] & (0x01 << HI6551_OTMP_150_OFFSET ) )
        iret|=  PMU_STATE_OVER_TEMP;
    /*����,����buck��·����·������boostǷѹ����ѹ����·*/
    for(j= 0; j < 8; j++)
    {
        if(pmu_hi6551_om_boot[j+3])
            iret|=  PMU_STATE_OVER_CUR;
    }

    return iret;
}

/*****************************************************************************
 �� �� ��  : bsp_hi6551_otp_threshold_set
 ��������  : ϵͳ����ʱ���ù��¾�����ֵ
 �������  : Ҫ���õ��¶�
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  : �쳣ģ���ʼ������
*****************************************************************************/
void bsp_hi6551_otp_threshold_set(int threshold)
{
    hi6551_excflags_t exc_flags = 0;
    /*lint --e{746,718}*/
    spin_lock_irqsave(&g_hi6551_exc_st.lock,exc_flags);
    switch(threshold)
    {
        case 105:
            bsp_hi6551_reg_write_mask(HI6551_BANDGAP_THSD_ADJ2_OFFSET, 0x00,0x30);
            break;
        case 115:
            bsp_hi6551_reg_write_mask(HI6551_BANDGAP_THSD_ADJ2_OFFSET, 0x10,0x30);
                break;
        case 125:
            bsp_hi6551_reg_write_mask(HI6551_BANDGAP_THSD_ADJ2_OFFSET, 0x20,0x30);;
                break;
        default:
                break;
            /*����������Ĭ��ֵ125�� */
    }
    spin_unlock_irqrestore(&g_hi6551_exc_st.lock,exc_flags);
}
/*****************************************************************************
 �� �� ��  : bsp_hi6551_uvp_threshold_set
 ��������  : ϵͳ����ʱ����Ƿѹ������ֵ
 �������  : Ҫ���õĵ�ѹ
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  : �쳣ģ���ʼ������
*****************************************************************************/
void bsp_hi6551_uvp_threshold_set(int threshold)
{
    hi6551_excflags_t exc_flags = 0;

    spin_lock_irqsave(&g_hi6551_exc_st.lock,exc_flags);
    switch(threshold)
    {
        case 3000:
            bsp_hi6551_reg_write_mask(HI6551_NP_REG_ADJ_OFFSET, 0x00,0x10);
            break;
        case 2700:
            bsp_hi6551_reg_write_mask(HI6551_NP_REG_ADJ_OFFSET, 0x10,0x10);
            break;
        default:
            break;
            /*����������Ĭ��ֵ3v  */
    }
    spin_unlock_irqrestore(&g_hi6551_exc_st.lock,exc_flags);
}

/*------------------------------����������------------------------------------------*/
void hi6551_ocp_scp_handle(void* para)
{
    u8 a_ucRecordReg[8] = {0};/*�����Ĵ�����ȡֵ*/
    u64 volt_need_off = 0;
    u64 *pmu_ocp_flag = (u64 *)SHM_PMU_OCP_INFO_ADDR;/*��������Ҫ�رյĹ���Դ*/
    u8 i = 0;
    u8 j = 0;
    /*lint --e{690,831}*/
    para=para;

    pmic_print_error("*******hi6551_current_overflow!**********\n");

    for(i = 0; i < 8; i++)
    {
        bsp_hi6551_reg_read((HI6551_NP_SCP_RECORD1_OFFSET+i), &a_ucRecordReg[i]);
        /*���жϴ��������У��Ƿ���Ҫ����?*/
        pmu_hi6551_om_data[i + 3] |= a_ucRecordReg[i];
    }
    /* �������SCP_RECORD ��OCP_RECORD�е�״̬,����nv���ý��а�ȫ���� */
    /*BUCK��·�͹����������BUCK�Ƿ���Ҫ�ر�,buck01 ������*/
    for (j = 1; j < 6; j++)
    {
         if (a_ucRecordReg[0] & (u8)((u32)0x1 << j))/*lint !e690,!e831*/
         {
            volt_need_off |= ((u64)0x1 << (j+1));
            *pmu_ocp_flag |= ((u64)0x1 << (j+1));

            print2file(PMU_OM_LOG,"pmu_hi6551:BUCK %d short !\n",j+1);
         }
    }
    /*buck ocp exc handle;OCP_RECORD1*/
    for (j = 2; j < 8; j++)
    {
         if (a_ucRecordReg[1] & (u8)((u32)0x1 << j))/*lint !e690,!e831*/
         {
            volt_need_off |= ((u64)0x1 << (j-1));
            *pmu_ocp_flag |= ((u64)0x1 << (j-1));
            print2file(PMU_OM_LOG,"pmu_hi6551:BUCK %d overflow !\n",j-1);
         }
    }
    /*ldo ocp exc handle,OCP_RECORD2,3,4*/
    for (i = 2; i < 5; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (a_ucRecordReg[i] & (u8)((u32)0x1 << j))/*lint !e690,!e831*/
            {
                volt_need_off |= ((u64)0x1 << (PMIC_HI6551_LDO_MIN +(i-2)*8+j));/*ldo*/
                *pmu_ocp_flag |= ((u64)0x1 << (PMIC_HI6551_LDO_MIN +(i-2)*8+j));/*ldo*/
                print2file(PMU_OM_LOG,"pmu_hi6551:LDO %d overflow !\n" ,((i-2)*8+j+1));
            }
        }
    }
    /*lvs ocp*/
    /*lvs 2-8,OCP_RECORD5*/
    for (j = 0; j < 7; j++)
    {
        if (a_ucRecordReg[5] & (u8)((u32)0x1 << j))/*lint !e690,!e831*/
        {
            volt_need_off |= ((u64)0x1 << (PMIC_HI6551_LVS_MIN+j));/*lvs*/
            *pmu_ocp_flag |= ((u64)0x1 << (PMIC_HI6551_LVS_MIN+j));/*lvs*/
            print2file(PMU_OM_LOG,"pmu_hi6551:LVS %d overflow !\n",j+2);/*LVS��LVS2��ʼ���*/
        }
    }
    /*lvs 9-10,OCP_RECORD6*/
    for (j = 0; j < 2; j++)
    {
        if (a_ucRecordReg[6] & (u8)((u32)0x1 << j))/*lint !e690,!e831*/
        {
            volt_need_off |= ((u64)0x1 << (PMIC_HI6551_LVS_MIN+7+j));/*lvs*/
            *pmu_ocp_flag |= ((u64)0x1 << (PMIC_HI6551_LVS_MIN+7+j));/*lvs*/
            print2file(PMU_OM_LOG,"pmu_hi6551:LVS %d overflow !\n",j+9);
        }
    }
    /*boost,OCP_RECORD7,class������ֻ��¼*/
    if (a_ucRecordReg[7] & 0x0f)/*lint !e661,!e690,!e831*/
    {
        volt_need_off |= (u64)(0x1 << PMIC_HI6551_BOOST);/*BOOST*/
        *pmu_ocp_flag |= (u64)(0x1 << PMIC_HI6551_BOOST);/*boost*/
    }
    if (a_ucRecordReg[7] & (0x1 << 0))/*lint !e661*/
    {
        pmic_print_info("pmu_hi6551:BOOST overflow !\n");
        print2file(PMU_OM_LOG,"pmu_hi6551:BOOST overflow !\n");
    }
    if (a_ucRecordReg[7] & (0x1 << 1))/*lint !e661*/
    {
        pmic_print_info("pmu_hi6551:BOOST short !\n");
        print2file(PMU_OM_LOG,"pmu_hi6551:BOOST short !\n");
    }
    if (a_ucRecordReg[7] & (0x1 << 2))/*lint !e661*/
    {
        pmic_print_info("pmu_hi6551:BOOST overvolt !\n");
        print2file(PMU_OM_LOG,"pmu_hi6551:BOOST overvolt !\n");
    }
    if (a_ucRecordReg[7] & (0x1 << 3))/*lint !e661*/
    {
        pmic_print_info("pmu_hi6551:BOOST undervolt !\n");
        print2file(PMU_OM_LOG,"pmu_hi6551:BOOST undervolt !\n");
    }
    if (a_ucRecordReg[7] & (0x1 << 4))/*lint !e661*/
    {
        pmic_print_info("pmu_hi6551:CLASSED undervolt !\n");
        print2file(PMU_OM_LOG,"pmu_hi6551:CLASSED undervolt !\n");/*ֻ��¼��������*/
    }



    for(j = PMIC_HI6551_VOLT_MIN;j < PMIC_HI6551_VOLT_MAX ;j++)
    {
        if(pmu_exc_pro.ulOcpIsOff)
        {
            if(volt_need_off & ((u64)0x1 << j))
            {
                pmic_print_error("hi6551:volt id %d overflow !\n",j);

                if(pmu_exc_pro.VoltProConfig[j].VoltOcpIsOff)
                {
                   /* print2file(PMU_OM_LOG,"pmu_hi6551:volt id %d overflow !\n",j);*/
                    pmic_print_error("hi6551:volt id %d will be closed !\n",j);
                    bsp_hi6551_volt_disable(j);
                }
                if(pmu_exc_pro.VoltProConfig[j].VoltOcpIsRst)
                {
                    pmic_print_error("hi6551:system will be restart!\n");
                    system_error(DRV_ERRNO_PMU_OVER_CUR, PMU_STATE_OVER_CUR, j, (char *)&volt_need_off, (u32)sizeof(volt_need_off));
                }
            }
        }
        else
        {
            if(volt_need_off & ((u64)0x1 << j))
                pmic_print_error("hi6551:volt id %d overflow !\n",j);
        }
    }

    /*��¼����error.log*/
    /*for(j = PMIC_HI6551_VOLT_MIN;j < PMIC_HI6551_VOLT_MAX ;j++)
    {
        if(volt_need_off & (0x1 << j))
        {
            print2file(PMU_OM_LOG,"pmu_hi6551:volt id %d overflow !\n",j);
        }
    }*/
    /*hi6551_om_log_save(PMU_OM_LOG_EXC);*/
    /*������µ��ж�״̬�Ĵ���*/
    for(i = 0; i < 8; i++)
    {
        bsp_hi6551_reg_write((HI6551_NP_SCP_RECORD1_OFFSET+i), a_ucRecordReg[i]);/*lint !e661*/
    }
}/*lint !e438*/
/*------------------------------���´�����------------------------------------------*/
void hi6551_otp_handle(void* para)
{
    int i = 0;
    /*u8 otp_is_off[PMIC_HI6551_VOLT_MAX] = {};*/

    para = para;

    pmic_print_error("hi6551:temperature overflow (>125/115/105��)!\n");

    /*��nv���ƹ����Ƿ�ر�*/
    pmu_hi6551_om_data[0] |= (0x01 << HI6551_OTMP_125_OFFSET);
    /*����nv���ã������Ƿ�رշǺ��ĵ�Դ,�������Ӳ�Ʒ��̬������⴦��*/
    if(pmu_exc_pro.ulOtpCurIsOff)
    {
        for(i = PMIC_HI6551_VOLT_MIN;i < PMIC_HI6551_VOLT_MAX;i++)
        {
            if(pmu_exc_pro.VoltProConfig[i].VoltOtpIsOff)
            {
                pmic_print_error("hi6551:volt id %d will be closed !\n",i);
                bsp_hi6551_volt_disable(i);
            }
        }
    }
    if(pmu_exc_pro.ulOtpIsRst)
    {
        pmic_print_error("hi6551:system will be restart!\n");
        system_error(DRV_ERRNO_PMU_OVER_TEMP, PMU_STATE_OVER_TEMP, 0, NULL, 0);
    }

    /*��¼om log*/
    /*hi6551_om_log_save(PMU_OM_LOG_EXC);*/
    print2file(PMU_OM_LOG,"pmu_hi6551:temperature overflow (>125/115/105��)!\n");
    /*clear np int */
    bsp_hi6551_reg_write(HI6551_NP_SCP_RECORD1_OFFSET, (0x01 << HI6551_OTMP_125_OFFSET));
}/*lint !e438*/
/*------------------------------��ѹ������------------------------------------------*/
void hi6551_ovp_handle(void* para)
{
    para = para;

    pmu_hi6551_om_data[0] |= (0x01 << HI6551_VSYS_OVER_6P0_OFFSET);
    /*��¼om log*/
    //hi6551_om_log_save(PMU_OM_LOG_EXC);
    print2file(PMU_OM_LOG,"pmu_hi6551:vsys over 6.0v last time!\n");

    /*������µ�reg,write 1 clear*/
    bsp_hi6551_reg_write(HI6551_NP_IRQ1_RECORD_OFFSET, (0x01 << HI6551_VSYS_OVER_6P0_OFFSET));
    pmic_print_error("\n**********hi6551_ovp_isr**********\n");
}/*lint !e438*/

/*****************************************************************************
 �� �� ��  : hi6551_uvp_warning_handle
 ��������  : Ƿѹ������2.7/3.0����ѹ�����趨�ĸ澯��ֵ����Ҫ���еĴ���
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  : smarstar�жϴ�������
*****************************************************************************/
void hi6551_uvp_warning_handle(void* para)
{
    para = para;
    pmu_hi6551_om_data[0] |= (0x01 << HI6551_VSYS_UNDER_2P7_OFFSET);
    /*�����ֳ�*/
    /*��¼om log
    hi6551_om_log_save(PMU_OM_LOG_EXC);*/
    print2file(PMU_OM_LOG,"pmu_hi6551:vsys under 2.7/3.0v !\n");

    /*����nv���ô����ʩ*/
    if(pmu_exc_pro.ulUvpIsRst)
    {
        pmic_print_error("hi6551:system will be restart!\n");
        system_error(DRV_ERRNO_PMU_UNDEF_VOL, PMU_STATE_UNDER_VOL, 0, NULL, 0);
    }

    /*������µ�reg��write 1 clear*/
    bsp_hi6551_reg_write(HI6551_NP_IRQ1_RECORD_OFFSET, (0x01 << HI6551_VSYS_UNDER_2P7_OFFSET));
    pmic_print_error("**********hi6551_uvp_2p7_isr**********\n");
}/*lint !e438*/
/*****************************************************************************
 �� �� ��  : hi6551_uvp_die_handle
 ��������  : Ƿѹ������2.5����ѹ����PMU�������̵���ֵʱ��Ҫ���еĴ���(����
             ���������õ���ϵͳ�ͻ��)
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  : smarstar�жϴ�������
*****************************************************************************/
void hi6551_uvp_die_handle(void* para)
{
    para = para;

    pmu_hi6551_om_data[0] |= (0x01 << HI6551_VSYS_UNDER_2P5_OFFSET);
    /*��¼om log
    hi6551_om_log_save(PMU_OM_LOG_EXC);*/
    print2file(PMU_OM_LOG,"pmu_hi6551:vsys under 2.5v !\n");

    /*������µ�reg,write 1 clear*/
    bsp_hi6551_reg_write(HI6551_NP_IRQ1_RECORD_OFFSET, (0x01 << HI6551_VSYS_UNDER_2P5_OFFSET));
    pmic_print_error("\n**********hi6551_uvp_2p5_isr**********\n");
}/*lint !e438*/

/*****************************************************************************
 �� �� ��  : bsp_hi6551_exc_init
 ��������  : �쳣����ģ���ʼ������
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  : ϵͳģ�����
*****************************************************************************/
int bsp_hi6551_exc_init(void)
{
    u16 i = 0;
    hi6551_excflags_t exc_flags = 0;
    u64 *volt_need_off = (u64 *)SHM_PMU_OCP_INFO_ADDR;/*��������Ҫ�رյĹ���Դ*/
    int ret;
    u32 iret;
    u8 reg_temp = 0;

    /*init default nv config*/
    memset((void*)&pmu_exc_pro, 0, sizeof(PMU_EXC_PRO_NV_STRU));
    pmu_exc_pro.ulOcpIsOn = 0;
    pmu_exc_pro.ulOcpIsOff = 1;
    pmu_exc_pro.ulOtpCurIsOff = 1;
    pmu_exc_pro.ulOtpIsRst = 0;
    pmu_exc_pro.ulOtpIsOff = 1;
    pmu_exc_pro.ulOtpLimit = 125;
    pmu_exc_pro.ulUvpIsRst = 1;
    pmu_exc_pro.ulUvpLimit = 2700;

    spin_lock_init(&g_hi6551_exc_st.lock);/*�ж�ֻ��Acoreʵ�֣���core������*/
    /*read nv,get the exc protect setting*/
    iret = bsp_nvm_read(NV_ID_DRV_NV_PMU_EXC_PRO,(u8 *)&pmu_exc_pro,sizeof(PMU_EXC_PRO_NV_STRU));
    if(NV_OK != iret)
    {
        pmic_print_error("pmu exc pro read nv error,not set,use the default config!\n");
    }
    else
    {
        /*set the Otp Limit threshold*/
        bsp_hi6551_otp_threshold_set((int)pmu_exc_pro.ulOtpLimit);
        /*set the Uvp Limit threshold*/
        bsp_hi6551_uvp_threshold_set((int)pmu_exc_pro.ulUvpLimit);
    }

    /*write start flag to pmu_om_log */
    hi6551_om_log_save(PMU_OM_LOG_START);
    /*�ȼ�¼�����*/
    hi6551_boot_om_log_save();

    /*������µ�reg*/
    for(i = 0; i < 11; i++)
    {
        spin_lock_irqsave(&g_hi6551_exc_st.lock,exc_flags);
        bsp_hi6551_reg_read((HI6551_NP_IRQ1_RECORD_OFFSET+i), &reg_temp);
        bsp_hi6551_reg_write((HI6551_NP_IRQ1_RECORD_OFFSET+i), reg_temp);
        spin_unlock_irqrestore(&g_hi6551_exc_st.lock,exc_flags);
    }

    /*��ʼ��������־λ*/
    *volt_need_off = 0;

    /*register hi6551 ocp interrupt*/
    ret = hi6551_irq_callback_register(IRQ_HI6551_OCP_SCP, hi6551_ocp_scp_handle, NULL);
    if (ret) {
        pmic_print_error("hi6551 irq register ocp interrupt failed!\n");
    }
    ret = hi6551_irq_callback_register(IRQ_HI6551_OTMP, hi6551_otp_handle, NULL);
    if (ret) {
        pmic_print_error("hi6551 irq register otmp interrupt failed!\n");
    }
    ret = hi6551_irq_callback_register(IRQ_HI6551_VSYS_UNDER_2P5, hi6551_uvp_die_handle, NULL);
    if (ret) {
        pmic_print_error("hi6551 irq register ocp interrupt failed!\n");
    }
    ret = hi6551_irq_callback_register(IRQ_HI6551_VSYS_UNDER_2P7, hi6551_uvp_warning_handle, NULL);
    if (ret) {
        pmic_print_error("hi6551 irq register otmp interrupt failed!\n");
    }
    ret = hi6551_irq_callback_register(IRQ_HI6551_VSYS_OVER_6P0, hi6551_ovp_handle, NULL);
    if (ret) {
        pmic_print_error("hi6551 irq register otmp interrupt failed!\n");
    }

    pmic_print_error("hi6551 exc init ok!\n");

    return ret;
}

module_init(bsp_hi6551_exc_init);
static void __exit bsp_hi6551_exc_exit(void)
{
}
module_exit(bsp_hi6551_exc_exit);

