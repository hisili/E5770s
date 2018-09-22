

/*lint --e{537,958}*/
#if defined(__KERNEL__)
#include <osl_irq.h>
#endif
#include <osl_bio.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#include <hi_smartstar.h>
#include <bsp_ipc.h>
#include "pmu_balong.h"
#include "common_hi6551.h"

struct hi6551_common_data{
    spinlock_t      lock;
};
struct hi6551_common_data g_hi6551_comm_st;

#if defined(__KERNEL__)

#include<bsp_pmu.h>

/*32Kʱ��ƫ��*/
static u8 hi6551_32k_clk_offset[PMU_32K_CLK_MAX + 1] = {7,6,5};
static u32 hi6551_backbat_volt[3] ={2500,3000,3300};

/*para check func*/
static __inline__ int hi6551_32k_para_check(pmu_clk_e clk_id)
{
    if(PMU_32K_CLK_MAX <= clk_id || PMU_32K_CLK_A > clk_id)
        return BSP_PMU_ERROR;
    else
        return BSP_PMU_OK;
}
/*****************************************************************************
 �� �� ��  : hi6551_32k_clk_enable
 ��������  : ������Ӧ·32kʱ��
 �������  : pmu 32k ʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
int hi6551_32k_clk_enable(pmu_clk_e clk_id)
{
    hi6551_commflags_t comm_flag = 0;
    u8 regval = 0;
    u8 bit_offset;

    if(hi6551_32k_para_check(clk_id))
        return BSP_PMU_ERROR;

    bit_offset = hi6551_32k_clk_offset[clk_id];     /*BITƫ��*/

    /*���ڻ���*/
    /*lint --e{746,718}*/
    spin_lock_irqsave(&g_hi6551_comm_st.lock,comm_flag);
    bsp_hi6551_reg_read(HI6551_ONOFF8_OFFSET, &regval);
    regval |= (u8)((u32)0x1 << bit_offset);
    bsp_hi6551_reg_write(HI6551_ONOFF8_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6551_comm_st.lock,comm_flag);

    return BSP_PMU_OK;
}
/*****************************************************************************
 �� �� ��  : hi6551_32k_clk_disable
 ��������  : �رն�Ӧ·32kʱ��
 �������  : pmu 32k ʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
int hi6551_32k_clk_disable(pmu_clk_e clk_id)
{
    hi6551_commflags_t comm_flag = 0;
    u8 regval = 0;
    u8 bit_offset;

    if(hi6551_32k_para_check(clk_id))
        return BSP_PMU_ERROR;

    if(PMU_32K_CLK_A == clk_id)
    {
        pmic_print_info("soc use,can not be closed!\n");
        return BSP_PMU_ERROR;
    }

    bit_offset = hi6551_32k_clk_offset[clk_id];     /*BITƫ��*/

    /*���ڻ���*/
    spin_lock_irqsave(&g_hi6551_comm_st.lock,comm_flag);
    bsp_hi6551_reg_read(HI6551_ONOFF8_OFFSET, &regval);
    regval &= ~(u8)((u32)0x1 << bit_offset);
    bsp_hi6551_reg_write(HI6551_ONOFF8_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6551_comm_st.lock,comm_flag);

    return BSP_PMU_OK;
}
/*****************************************************************************
 �� �� ��  : hi6551_32k_clk_is_enabled
 ��������  : ��ѯ��Ӧ·32kʱ���Ƿ���
 �������  : pmu 32k ʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
int hi6551_32k_clk_is_enabled(pmu_clk_e clk_id)
{
    u8 regval = 0;
    u8 bit_offset;

    if(hi6551_32k_para_check(clk_id))
        return BSP_PMU_ERROR;

    bit_offset = hi6551_32k_clk_offset[clk_id];     /*BITƫ��*/
    bsp_hi6551_reg_read(HI6551_ONOFF8_OFFSET, &regval);

    return (int)(regval & ((u32)0x1<<bit_offset));
}

/*-------------------------Ŧ�۵��ģ��ӿ�-----------------------------------------------*/
void hi6551_backbat_charge_enabled(void)
{
    hi6551_commflags_t comm_flag = 0;
    u8 regval = 0;

    /*���ڻ���*/
    spin_lock_irqsave(&g_hi6551_comm_st.lock,comm_flag);
    bsp_hi6551_reg_read(HI6551_NP_REG_CHG_OFFSET, &regval);
    regval |= ((u32)0x1 << 2);
    bsp_hi6551_reg_write(HI6551_NP_REG_CHG_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6551_comm_st.lock,comm_flag);
}
void hi6551_backbat_charge_disabled(void)
{
    hi6551_commflags_t comm_flag = 0;
    u8 regval = 0;

    /*���ڻ���*/
    spin_lock_irqsave(&g_hi6551_comm_st.lock,comm_flag);
    bsp_hi6551_reg_read(HI6551_NP_REG_CHG_OFFSET, &regval);
    regval &= ~((u32)0x1 << 2);
    bsp_hi6551_reg_write(HI6551_NP_REG_CHG_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6551_comm_st.lock,comm_flag);
}
/*��λmv*/
void hi6551_backbat_charge_volt_set(u32 volt)
{
    int i = 0;
    hi6551_commflags_t comm_flag = 0;

    for(i=0; i<3; i++)
    {
        if(hi6551_backbat_volt[i] == volt)
            break;
    }

    if(i >= 3)
        /*û�и���Ҫ��ĵ�ѹ*/
        return ;
    else
    {
        /*���ڻ���*/
        spin_lock_irqsave(&g_hi6551_comm_st.lock,comm_flag);
        bsp_hi6551_reg_write_mask(HI6551_NP_REG_CHG_OFFSET,(u8)i,0x3);
        spin_unlock_irqrestore(&g_hi6551_comm_st.lock,comm_flag);
    }

}

/*----------------------------------�������ػ�ģ��---------------------------------------*/
void hi6551_long_powerkey_time_set(u32 time)
{
    hi6551_commflags_t comm_flag = 0;

    if((6 > time) ||(11 < time))
    {
        /*no this time*/
            return;
    }
    else
    {
        /*���ڻ���*/
        spin_lock_irqsave(&g_hi6551_comm_st.lock,comm_flag);
        bsp_hi6551_reg_write_mask(HI6551_NP_REG_ADJ_OFFSET,(u8)(time - 6),0x7);
        spin_unlock_irqrestore(&g_hi6551_comm_st.lock,comm_flag);
    }
}

void hi6551_long_powerkey_off_mask(void)
{
    hi6551_commflags_t comm_flag = 0;
    u8 regval = 0;

    /*���ڻ���*/
    spin_lock_irqsave(&g_hi6551_comm_st.lock,comm_flag);
    bsp_hi6551_reg_read(HI6551_NP_REG_ADJ_OFFSET, &regval);
    regval |= (0x1 << 3);
    bsp_hi6551_reg_write(HI6551_NP_REG_ADJ_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6551_comm_st.lock,comm_flag);
}
void hi6551_long_powerkey_off_unmask(void)
{
    hi6551_commflags_t comm_flag = 0;
    u8 regval = 0;

    /*���ڻ���*/
    spin_lock_irqsave(&g_hi6551_comm_st.lock,comm_flag);
    bsp_hi6551_reg_read(HI6551_NP_REG_ADJ_OFFSET, &regval);
    regval &= ~(0x1 << 3);
    bsp_hi6551_reg_write(HI6551_NP_REG_ADJ_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6551_comm_st.lock,comm_flag);
}
/*****************************************************************************
 �� �� ��  : bsp_hi6551_usb_state_get
 ��������  : ��ȡusb�Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : usb�����γ�(1:���룻0:�γ�)
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool hi6551_power_key_state_get(void)
{
    u8 regval = 0;

    bsp_hi6551_reg_read(HI6551_STATUS1_OFFSET, &regval);
    return  (regval & PMU_HI6551_POWER_KEY_MASK) ? 1 : 0;
}
/*****************************************************************************
 �� �� ��  : bsp_hi6551_usb_state_get
 ��������  : ��ȡusb�Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : usb�����γ�(1:���룻0:�γ�)
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool hi6551_usb_state_get(void)
{
    u8 regval = 0;

    bsp_hi6551_reg_read(HI6551_STATUS2_OFFSET, &regval);
    return  (regval & PMU_HI6551_USB_STATE_MASK) ? 1 : 0;
}
/*****************************************************************************
 �� �� ��  : hi6551_sim_deb_time_set
 ��������  : ����SIM���ж�ȥ��ʱ�䣬��λ��us��
             ��Χ��(120,600),step:30;
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
int hi6551_sim_deb_time_set(u32 uctime)
{
    hi6551_commflags_t comm_flag = 0;
    u32 time = 0;

    /* �����Ϸ��Լ�� */
    if((120 > uctime) && (600 < uctime))
    {
        pmic_print_error("sim debtime can not be set %d us,it's range is from 120 to 600 us,!\n", (s32)uctime);
        return BSP_PMU_ERROR;
    }

    /* Ѱ�ҿ�����ֵ */
    for(time = 120; time < 600; time += 30)
    {
        if ((uctime >= time) && (uctime < time + 30))
        {
            break;
        }
    }

    pmic_print_info("sim debtime is set at %d us!\n",(int)time);
    
    /* ʵ��ʱ��ת��Ϊ�Ĵ���ֵ */
    time = time / 30 - 1;   /* ʵ��ʱ��ͼĴ�����ֵ����ת����ϵ: 30 * (reg_val + 1) = time */     
    
    spin_lock_irqsave(&g_hi6551_comm_st.lock,comm_flag);
    bsp_hi6551_reg_write_mask(HI6551_SIM_DEB_OFFSET, (u8)time, 0x1f);
    spin_unlock_irqrestore(&g_hi6551_comm_st.lock,comm_flag);
    return BSP_PMU_OK;

}
void hi6551_ldo22_res_enable(void)
{
    hi6551_commflags_t comm_flag = 0;
    u8 regval = 0;

    /*���ڻ���*/
    spin_lock_irqsave(&g_hi6551_comm_st.lock,comm_flag);
    bsp_hi6551_reg_read(HI6551_LDO22_REG_ADJ_OFFSET, &regval);

    /* 210/220��Ϊb'11�����������ֵ��230/240��Ϊb'00�����1.5k */
    if((BSP_PMU_V210 == bsp_pmu_version_get()) || (BSP_PMU_V220 == bsp_pmu_version_get()))
    {
        regval |= (0x3 << 4);
    }
    else /* BSP_PMU_V230/BSP_PMU_V240 */
    {
        regval &= ~(0x3 << 4);
    }
    
    bsp_hi6551_reg_write(HI6551_LDO22_REG_ADJ_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6551_comm_st.lock,comm_flag);
}
void hi6551_ldo22_res_disable(void)
{
    hi6551_commflags_t comm_flag = 0;
    u8 regval = 0;

    /*ȥʹ�� bit5 4-10*/
    /*���ڻ���*/
    spin_lock_irqsave(&g_hi6551_comm_st.lock,comm_flag);
    bsp_hi6551_reg_read(HI6551_LDO22_REG_ADJ_OFFSET, &regval);
    regval &= ~(0x1 << 4);
    regval |= (0x1 << 5);
    bsp_hi6551_reg_write(HI6551_LDO22_REG_ADJ_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6551_comm_st.lock,comm_flag);
}
#endif
#if defined(__CMSIS_RTOS)
#define PASTAR_VCC PMIC_HI6551_LVS05
/*****************************************************************************
 �� �� ��  : hi6551_pastar_enable
 ��������  : ����pastar��ѹ
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
void hi6551_pastar_enable(void)
{
    bsp_hi6551_volt_enable(PASTAR_VCC);
}
/*****************************************************************************
 �� �� ��  : hi6551_pastar_disable
 ��������  : �ر�pastar��ѹ
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
void hi6551_pastar_disable(void)
{
    bsp_hi6551_volt_disable(PASTAR_VCC);
}
#endif
/*****************************************************************************
 �� �� ��  : hi6451_version_get
 ��������  : ��ȡpmu�İ汾��
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
u8 hi6551_version_get(void)
{
    u8 regval = 0;

    bsp_hi6551_reg_read(HI6551_VERSION_OFFSET, &regval);
    return  regval;
}
/*****************************************************************************
 �� �� ��  : bsp_hi6551_common_init
 ��������  : PMIC HI6551 commonģ���ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��ע˵��  : ��ʼ��app�����ź���
*****************************************************************************/
void bsp_hi6551_common_init(void)
{
    spin_lock_init(&g_hi6551_comm_st.lock);/*�ж�ֻ��Acoreʵ�֣���core*/
}


