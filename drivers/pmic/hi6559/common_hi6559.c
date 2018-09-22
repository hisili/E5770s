

/*lint --e{537,958}*/
#include <osl_bio.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#if defined(__KERNEL__)
#include <osl_irq.h>
#include <osl_types.h>
#endif
#include <hi_bbstar.h>
#include <bsp_ipc.h>
#if defined(__KERNEL__)
#include <bsp_pmu.h>
#endif
#include "pmu_balong.h"
#include "common_hi6559.h"

struct hi6559_common_data{
    spinlock_t      lock;
};

struct hi6559_common_data g_hi6559_comm_st;

#if defined(__KERNEL__)

/* 32Kʱ��ʹ��bit�ڼĴ����ڲ���ƫ�� */
static u8 hi6559_32k_clk_offset[PMU_32K_CLK_MAX] = {7,6};
static u32 hi6559_backbat_volt[PMU_HI6559_BACKBAT_CHARGER_VOLT_NUM] ={2500,3000,3300};

/*****************************************************************************
* �� �� ��  : hi6559_32k_para_check
*
* ��������  : ���32K CLK ID�Ƿ�Ϸ�
*
* �������  : @clk_id��������CLK_ID
*
* �������  : ��
*
* �� �� ֵ  : BSP_PMU_OK:�Ϸ�;   BSP_PMU_ERROR:���Ϸ�
*****************************************************************************/
static __inline__ s32 hi6559_32k_para_check(pmu_clk_e clk_id)
{
    if(PMU_32K_CLK_MAX <= clk_id)
    {
        return BSP_PMU_ERROR;
    }
    else
    {
        return BSP_PMU_OK;
    }
}

/*****************************************************************************
 �� �� ��  : hi6559_32k_clk_enable
 ��������  : ������Ӧ·32kʱ��
 �������  : pmu 32k ʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : BSP_PMU_OK: �ɹ���else:ʧ��
*****************************************************************************/
s32 hi6559_32k_clk_enable(pmu_clk_e clk_id)
{
    hi6559_commflags_t comm_flag = 0;
    u8 regval = 0;

    if(hi6559_32k_para_check(clk_id))
    {
        return BSP_PMU_ERROR;
    }
    
    /* ���ڻ��� */
    /* lint --e{746,718} */
    spin_lock_irqsave(&g_hi6559_comm_st.lock, comm_flag);
    bsp_hi6559_reg_read(HI6559_ONOFF8_OFFSET, &regval);
    regval |= (u8)((u32)0x1 << hi6559_32k_clk_offset[clk_id]);
    bsp_hi6559_reg_write(HI6559_ONOFF8_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6559_comm_st.lock, comm_flag);

    return BSP_PMU_OK;
}

/*****************************************************************************
 �� �� ��  : hi6559_32k_clk_disable
 ��������  : �رն�Ӧ·32kʱ��
 �������  : pmu 32k ʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
*****************************************************************************/
s32 hi6559_32k_clk_disable(pmu_clk_e clk_id)
{
    hi6559_commflags_t comm_flag = 0;
    u8 regval = 0;

    if(hi6559_32k_para_check(clk_id))
    {
        return BSP_PMU_ERROR;
    }

    if(PMU_32K_CLK_A == clk_id)
    {
        pmic_print_info("soc use,can not be closed!\n");
        return BSP_PMU_ERROR;
    }

    /* ���ڻ��� */
    spin_lock_irqsave(&g_hi6559_comm_st.lock,comm_flag);
    bsp_hi6559_reg_read(HI6559_ONOFF8_OFFSET, &regval);
    regval &= ~(u8)((u32)0x1 << hi6559_32k_clk_offset[clk_id]);
    bsp_hi6559_reg_write(HI6559_ONOFF8_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6559_comm_st.lock,comm_flag);

    return BSP_PMU_OK;
}

/*****************************************************************************
 �� �� ��  : hi6559_32k_clk_is_enabled
 ��������  : ��ѯ��Ӧ·32kʱ���Ƿ���
 �������  : pmu 32k ʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
s32 hi6559_32k_clk_is_enabled(pmu_clk_e clk_id)
{
    u8 regval = 0;

    if(hi6559_32k_para_check(clk_id))
    {
        return BSP_PMU_ERROR;
    }

    bsp_hi6559_reg_read(HI6559_ONOFF8_OFFSET, &regval);

    return (int)(regval & ((u32)0x1 << hi6559_32k_clk_offset[clk_id]));
}

/*****************************************************************************
 �� �� ��  : hi6559_backbat_charge_enabled
 ��������  : ���õ�س��ʹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_backbat_charge_enabled(void)
{
    hi6559_commflags_t comm_flag = 0;
    u8 regval = 0;

    /* ���ڻ��� */
    spin_lock_irqsave(&g_hi6559_comm_st.lock,comm_flag);
    bsp_hi6559_reg_read(HI6559_NP_REG_CHG_OFFSET, &regval);
    regval |= ((u32)0x1 << PMU_HI6559_BACKBAT_CHARGER_ENABLE_OFFSET);
    bsp_hi6559_reg_write(HI6559_NP_REG_CHG_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6559_comm_st.lock,comm_flag);

    return;
}

/*****************************************************************************
 �� �� ��  : hi6559_backbat_charge_disabled
 ��������  : ���õ�س���ֹ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_backbat_charge_disabled(void)
{
    hi6559_commflags_t comm_flag = 0;
    u8 regval = 0;

    /* ���ڻ��� */
    spin_lock_irqsave(&g_hi6559_comm_st.lock,comm_flag);
    bsp_hi6559_reg_read(HI6559_NP_REG_CHG_OFFSET, &regval);
    regval &= ~((u32)0x1 << PMU_HI6559_BACKBAT_CHARGER_ENABLE_OFFSET);
    bsp_hi6559_reg_write(HI6559_NP_REG_CHG_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6559_comm_st.lock,comm_flag);

    return;
}

/*****************************************************************************
 �� �� ��  : hi6559_backbat_charge_volt_set
 ��������  : ���õ�س���ѹ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_backbat_charge_volt_set(u32 volt)
{
    hi6559_commflags_t comm_flag = 0;
    s32 i = 0;

    for(i = 0; i < PMU_HI6559_BACKBAT_CHARGER_VOLT_NUM; i++)
    {
        if(hi6559_backbat_volt[i] == volt)
        {
            break;
        }
    }

    if(i >= PMU_HI6559_BACKBAT_CHARGER_VOLT_NUM)
    {
        /*û�и���Ҫ��ĵ�ѹ*/
        return ;
    }
    else
    {
        /*���ڻ���*/
        spin_lock_irqsave(&g_hi6559_comm_st.lock,comm_flag);
        bsp_hi6559_reg_write_mask(HI6559_NP_REG_CHG_OFFSET, (u8)i, 0x3);
        spin_unlock_irqrestore(&g_hi6559_comm_st.lock,comm_flag);

        return;
    }
}

/*****************************************************************************
 �� �� ��  : hi6559_long_powerkey_time_set
 ��������  : ������ʱ������
 �������  : @time:Ҫ���õ�ʱ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_long_powerkey_time_set(u32 time)
{
    hi6559_commflags_t comm_flag = 0;

    if((PMU_HI6559_LONGPOWERKEY_TIME_MIN > time) || (PMU_HI6559_LONGPOWERKEY_TIME_MAX < time))
    {
        /* unsupport time */
        return;
    }
    else
    {
        /* ���ڻ��� */
        spin_lock_irqsave(&g_hi6559_comm_st.lock,comm_flag);

        /* �����time-6����Ϊʵ��ʱ��ͼĴ���ֵ֮��Ĳ�ֵΪ6 */
        bsp_hi6559_reg_write_mask(HI6559_NP_REG_ADJ_OFFSET, (u8)(time - 6), PMU_HI6559_LONGPOWERKEY_TIME_MASK);
        spin_unlock_irqrestore(&g_hi6559_comm_st.lock,comm_flag);

        return;
    }
}

/*****************************************************************************
 �� �� ��  : hi6559_long_powerkey_off_mask
 ��������  : ���γ������ػ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_long_powerkey_off_mask(void)
{
    hi6559_commflags_t comm_flag = 0;
    u8 regval = 0;

    /* ���ڻ��� */
    spin_lock_irqsave(&g_hi6559_comm_st.lock, comm_flag);
    bsp_hi6559_reg_read(HI6559_NP_REG_ADJ_OFFSET, &regval);
    regval |= (0x1 << PMU_HI6559_LONGPOWERKEY_OFF_MASK_OFS);
    bsp_hi6559_reg_write(HI6559_NP_REG_ADJ_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6559_comm_st.lock, comm_flag);

    return;
}

/*****************************************************************************
 �� �� ��  : hi6559_long_powerkey_off_unmask
 ��������  : �����γ������ػ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_long_powerkey_off_unmask(void)
{
    hi6559_commflags_t comm_flag = 0;
    u8 regval = 0;

    /* ���ڻ��� */
    spin_lock_irqsave(&g_hi6559_comm_st.lock, comm_flag);
    bsp_hi6559_reg_read(HI6559_NP_REG_ADJ_OFFSET, &regval);
    regval &= ~(0x1 << PMU_HI6559_LONGPOWERKEY_OFF_MASK_OFS);
    bsp_hi6559_reg_write(HI6559_NP_REG_ADJ_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6559_comm_st.lock, comm_flag);

    return;
}

/*****************************************************************************
 �� �� ��  : hi6559_long_powerkey_reboot_mask
 ��������  : ���γ������ػ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_long_powerkey_reboot_mask(void)
{
    hi6559_commflags_t comm_flag = 0;
    u8 regval = 0;

    /* ���ڻ��� */
    spin_lock_irqsave(&g_hi6559_comm_st.lock, comm_flag);
    bsp_hi6559_reg_read(HI6559_NP_REG_ADJ_OFFSET, &regval);
    regval |= (0x1 << PMU_HI6559_LONGPOWERKEY_REBOOT_MASK_OFS);
    bsp_hi6559_reg_write(HI6559_NP_REG_ADJ_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6559_comm_st.lock, comm_flag);

    return;
}

/*****************************************************************************
 �� �� ��  : hi6559_long_powerkey_reboot_unmask
 ��������  : �����γ������ػ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_long_powerkey_reboot_unmask(void)
{
    hi6559_commflags_t comm_flag = 0;
    u8 regval = 0;

    /* ���ڻ��� */
    spin_lock_irqsave(&g_hi6559_comm_st.lock, comm_flag);
    bsp_hi6559_reg_read(HI6559_NP_REG_ADJ_OFFSET, &regval);
    regval &= ~(0x1 << PMU_HI6559_LONGPOWERKEY_REBOOT_MASK_OFS);
    bsp_hi6559_reg_write(HI6559_NP_REG_ADJ_OFFSET, regval);
    spin_unlock_irqrestore(&g_hi6559_comm_st.lock, comm_flag);

    return;
}

/*****************************************************************************
 �� �� ��  : hi6559_power_key_state_get
 ��������  : ��ȡ����״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : 1 - ���£�0 - û�а���
*****************************************************************************/
bool hi6559_power_key_state_get(void)
{
    u8 regval = 0;

    bsp_hi6559_reg_read(HI6559_STATUS1_OFFSET, &regval);
    
    return  (regval & PMU_HI6559_POWER_KEY_MASK) ? 1: 0;
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_usb_state_get
 ��������  : ��ȡusb״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : 1 - ���룻0 - �γ�
*****************************************************************************/
bool hi6559_usb_state_get(void)
{
    u8 regval = 0;

    bsp_hi6559_reg_read(HI6559_STATUS2_OFFSET, &regval);
    return  (regval & PMU_HI6559_USB_STATE_MASK) ? 1 : 0;
}

/*****************************************************************************
 �� �� ��  : hi6559_sim_deb_time_set
 ��������  : ����SIM���ж�ȥ��ʱ�䣬��λ��us����Χ��(120,600),step:30;
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ����˵��  : uctime��(120, 600)��Χ��ʱ�����õ�λΪ������uctime�����ֵ�����򷵻�
*****************************************************************************/
s32 hi6559_sim_deb_time_set(u32 uctime)
{
    hi6559_commflags_t comm_flag = 0;
    u32 time = 0;

    /* �����Ϸ��Լ�� */
    if((PMU_HI6559_SIM_DEB_TIME_MIN > uctime) || (PMU_HI6559_SIM_DEB_TIME_MAX < uctime))
    {
        pmic_print_error("sim debtime can not be set %d us,it's range is from 120 to 600 us,!\n", (s32)uctime);
        return BSP_PMU_ERROR;
    }

    /* Ѱ�ҿ�����ֵ */
    for(time = PMU_HI6559_SIM_DEB_TIME_MIN; time < PMU_HI6559_SIM_DEB_TIME_MAX; time += PMU_HI6559_SIM_DEB_TIME_STEP)
    {
        if ((uctime >= time) && (uctime < time + PMU_HI6559_SIM_DEB_TIME_STEP))
        {
            break;
        }
    }

    /* ʵ��ʱ��ת��Ϊ�Ĵ���ֵ */
    pmic_print_info("set sim debtime %d us!\n", (s32)time);
    time = time / PMU_HI6559_SIM_DEB_TIME_STEP - 1;   /* ʵ��ʱ��ͼĴ�����ֵ����ת����ϵ: 30 * (reg_val + 1) = time */    
    
    spin_lock_irqsave(&g_hi6559_comm_st.lock, comm_flag);
    bsp_hi6559_reg_write_mask(HI6559_SIM_DEB_OFFSET, (u8)time, PMU_HI6559_SIM_DEB_SEL_MASK);
    spin_unlock_irqrestore(&g_hi6559_comm_st.lock, comm_flag);

    return BSP_PMU_OK;
}

/*****************************************************************************
 �� �� ��  : hi6559_ldo22_res_enable
 ��������  : ���õ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_ldo22_res_enable(void)
{
    /* 711 ldo22 ����sd���磬�˴���׮ */
    return;
}

/*****************************************************************************
 �� �� ��  : hi6559_ldo22_res_enable
 ��������  : ���õ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_ldo22_res_disable(void)
{
    /* 711 ldo22 ����sd���磬�˴���׮ */
    return;
}

#endif

#if defined(__CMSIS_RTOS)
#define PASTAR_VCC PMIC_HI6559_LVS09
/*****************************************************************************
 �� �� ��  : hi6559_pastar_enable
 ��������  : ����pastar��ѹ
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
void hi6559_pastar_enable(void)
{
    bsp_hi6559_volt_enable(PASTAR_VCC);
}
/*****************************************************************************
 �� �� ��  : hi6559_pastar_disable
 ��������  : �ر�pastar��ѹ
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
void hi6559_pastar_disable(void)
{
    bsp_hi6559_volt_disable(PASTAR_VCC);
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
u8 hi6559_version_get(void)
{
    u8 regval = 0;
    bsp_hi6559_reg_read(HI6559_VERSION_OFFSET, &regval);
    return  regval;
}
/*****************************************************************************
 �� �� ��  : bsp_hi6559_common_init
 ��������  : PMIC HI6559 commonģ���ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��ע˵��  : ��ʼ��app�����ź���
*****************************************************************************/
void bsp_hi6559_common_init(void)
{
    spin_lock_init(&g_hi6559_comm_st.lock); /* �ж�ֻ��Acoreʵ�֣���core */
}


