/*lint --e{537,958}*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <asm/mach/irq.h>
#include <linux/interrupt.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <drv_comm.h>
#include <asm/uaccess.h>
/*#include <osl_math64.h>*/
#include <osl_spinlock.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <bsp_nvim.h>
#include <hi_smartstar.h>
#include <bsp_coul.h>
#include "coul_hi6551.h"

struct coul_data{
    spinlock_t      lock;
};
struct coul_data g_coul_st;

#define COUL_BEFORE_TIMES_MAX    19
#define R_COUL_MOHM 10/*�ο�����:10 mohm*/
/*COULУ׼����nvֵ*/
COUL_CALI_NV_TYPE    coul_cali_config={1000,0,1000,0};/*Ĭ��ֵ����У׼*/

void coul_reg_write(u16 reg, u8 val)
{
    bsp_hi6551_reg_write(reg, val);
}

u8 coul_reg_read(u16 reg)
{
    unsigned char val = 0;

    bsp_hi6551_reg_read(reg, &val);

    return val;
}

void coul_reg_mask(u16 reg,u8 val,u8 mask)
{
    bsp_hi6551_reg_write_mask(reg, val, mask);
}
#if 0
/*****************************************************************************
 �� �� ��  : coul_battery_voltage
 ��������  : �Ĵ���ֵת���ɵ�ѹ
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
/**
 * convert_regval2uv
 * 1 bit = 225.1196 uv = 4.8/21322 V = 4.8/21322 * 1000 * 1000 uV = 24 * 1000 * 100/ 10661 uV
 * convert regval to uv
 */
u64 coul_convert_regval2uv(unsigned short reg_val)
{
    u64 temp;

    if (reg_val & 0x8000)
    {
        return -1;
    }

    temp = (u64)((u64)(reg_val)  * (u64)(24 * 1000 * 100));

    temp = div_u64(temp, 10661);

#if 1 /* for debug */
    temp = (u64) coul_cali_config.v_offset_a *temp;
/*    temp = div_u64(temp, 1000000);*/
    temp += coul_cali_config.v_offset_b;
#endif

    return temp;
}
/*****************************************************************************
 �� �� ��  : coul_convert_regval2ua
 ��������  : ����ת������
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
/**
 * convert_regval2ua
 * 10 mohm resistance: 1 bit = 5/10661 A = 5*1000*1000 / 10661 uA
 * 20 mohm resistance: 1 bit = 10 mohm / 2
 * 30 mohm resistance: 1 bit = 10 mohm / 3
 * ...
 * high bit = 0 is in, 1 is out
 * convert regval to ua
 */
s64 coul_convert_regval2ua(short reg_val)
{
    int ret;
    s64 temp;

    ret = reg_val;
    temp = (s64)(ret) * (s64)(1000 * 1000 * 5);
    temp = div_s64(temp, 10661);

    ret = temp / (R_COUL_MOHM/10);

    ret = -ret;/*����?*/

#if 1 /* for debug */
    temp = (s64) coul_cali_config.c_offset_a *ret;
 /*   ret = div_s64(temp, 1000000);*/
    ret += coul_cali_config.c_offset_b;
#endif

    return ret;
}
/*****************************************************************************
 �� �� ��  : coul_battery_voltage
 ��������  : ����ת������(��λ:uC)
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
/**
 * convert_regval2uc
 * 1 bit = 2.345*110*10^(-6) C = 2.5795*10^(-5) C = 25795 / 1000 uC
 * convert regval to uv
 */
u64 coul_convert_regval2uc(unsigned short reg_val)
{
    int ret;
    s64 temp;

    ret = reg_val;
    temp = (s64)(ret) * (s64)(25795);
    temp = div_s64(temp, 1000);

    return temp;
}
#endif
/*****************************************************************************
 �� �� ��  : coul_convert_regval2mv
 ��������  : �Ĵ���ֵת���ɵ�ѹ
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
/**
 * convert_regval2uv
 * 1 bit = 225.1196 uv = 4.8/21322 V = 4.8/21322 * 1000 * 1000 uV = 24 * 1000 * 100/ 10661 uV
 * convert regval to mv
 */
unsigned int coul_convert_regval2mv(unsigned short reg_val)
{
    unsigned int temp;

    if (reg_val & 0x8000)/*��ѹ�����Ǹ�ֵ*/
    {
        return BSP_COUL_UNVALID;
    }

    temp = (unsigned int)(reg_val*225);

    temp = temp / 1000;/*��λת��ΪmV*/

    return temp;
}
/*****************************************************************************
 �� �� ��  : coul_convert_regval2ua
 ��������  : ����ת������
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
/**
 * convert_regval2ua
 * 10 mohm resistance: 1 bit = 5/10661 A = 5*1000*1000 / 10661 uA = 469uA
 * 20 mohm resistance: 1 bit = 10 mohm / 2
 * 30 mohm resistance: 1 bit = 10 mohm / 3
 * ...
 * high bit = 0 is in, 1 is out
 * convert regval to ma
 */
signed int coul_convert_regval2ma(signed short reg_val)
{
    signed curr;
    s32 temp;

    temp = (s32)reg_val * 469;/*uA*/

    curr = temp / (R_COUL_MOHM/10);/*uA*/

    curr = curr / 1000;/*ת��ΪmA*/

    return curr;
}
/*****************************************************************************
 �� �� ��  : coul_battery_voltage
 ��������  : ����ת������(��λ:uC)
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned long long
 ���ú���  :
 ��������  :
*****************************************************************************/
/**
 * convert_regval2uc
 * 1 bit = 2.345*110*10^(-6) C = 2.5795*10^(-5) C = 25.795  uC
 * convert regval to uv
 */
unsigned long long coul_convert_regval2uc(unsigned int reg_val)
{
    unsigned long long temp;

    temp = (unsigned long long)reg_val * 26;/*uc*/
 /*   temp = (temp / 1000);*//*mC**/

    return temp;
}
/*****************************************************************************
 �� �� ��  : coul_cali_voltage
 ��������  : ��ȡУ׼��ĵ�ѹ
 �������  : voltage:δ��У׼�ĵ�ѹ
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int coul_cali_voltage(unsigned voltage)
{
    int calied_volt;

    calied_volt = (int)(coul_cali_config.v_offset_a *voltage);
    calied_volt = calied_volt / 1000;/*��������У׼б�ʼ�����������������*/
    calied_volt += coul_cali_config.v_offset_b;

    return (unsigned int)calied_volt;
}
/*****************************************************************************
 �� �� ��  : coul_cali_current
 ��������  : ��ȡУ׼��ĵ���
 �������  : cur:δ��У׼�ĵ���
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
signed int coul_cali_current(signed cur)
{
    signed int calied_cur;

    calied_cur = (signed int)coul_cali_config.c_offset_a * cur;
    calied_cur = calied_cur / 1000;/*��������У׼б�ʼ�����������������*/
    calied_cur += coul_cali_config.c_offset_b;

    return calied_cur;
}
/*****************************************************************************
 �� �� ��  : coul_convert_regval2mv_calied
 ��������  : �ɼĴ���ֵ��ȡУ׼��ĵ�ѹ
 �������  : voltage:δ��У׼�ĵ�ѹ
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int coul_convert_regval2mv_calied(unsigned short reg_val)
{
    unsigned int uncali_volt;
    unsigned int calied_volt;

    uncali_volt = coul_convert_regval2mv(reg_val);
    calied_volt = coul_cali_voltage(uncali_volt);

    return calied_volt;
}
/*****************************************************************************
 �� �� ��  : coul_convert_regval2calivolt
 ��������  : �ɼĴ���ֵ��ȡУ׼��ĵ���
 �������  : cur:δ��У׼�ĵ���
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
signed int coul_convert_regval2ma_calied(signed short reg_val)
{
    signed int uncali_cur;
    signed int calied_cur;

    uncali_cur = coul_convert_regval2ma(reg_val);
    calied_cur = coul_cali_current(uncali_cur);

    return calied_cur;
}
/*****************************************************************************
 �� �� ��  : coul_voltage_regval
 ��������  : ��ǰ��ѹ�Ĵ�����ȡ
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned short
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned short coul_voltage_regval(void)
{
    unsigned char val1;
    unsigned char val2;
    unsigned short val = 0;

    val1 = coul_reg_read(HI6551_V_OUT0_PRE0_OFFSET);
    val2 = coul_reg_read(HI6551_V_OUT1_PRE0_OFFSET);

    val = (unsigned short)(val1 | ((u32)(val2 & 0x7f)<< 8));/*��ѹΪ��ֵ�����λΪ����λ������ע*/
    return val;
}
/*****************************************************************************
 �� �� ��  : coul_voltage_before_regval
 ��������  : ��ȡ��ǰ��ѹǰtimes�ε�ѹ�Ĵ���ֵ����λ:uv
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned short
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned short coul_voltage_before_regval(unsigned int times)
{
    unsigned char val1;
    unsigned char val2;
    unsigned short val = 0;

    val1 = coul_reg_read((u16)(HI6551_V_OUT0_PRE0_OFFSET + 2 * times));
    val2 = coul_reg_read((u16)(HI6551_V_OUT1_PRE0_OFFSET + 2 * times ));

    val = (unsigned short)(val1 | ((u32)(val2 & 0xef)<< 8));/*��ѹΪ��ֵ�����λΪ����λ������ע*/
    return val;
}
/*****************************************************************************
 �� �� ��  : coul_battery_current_regval
 ��������  : ��ǰ�����Ĵ���ֵ��ȡ
 �������  : void
 �������  : ��
 �� �� ֵ  : signed short
 ���ú���  :
 ��������  :
*****************************************************************************/
signed short coul_current_regval(void)
{
    unsigned char val1;
    unsigned char val2;
    signed short val = 0;

    val1 = coul_reg_read(HI6551_CURRENT0_PRE0_OFFSET);
    val2 = coul_reg_read(HI6551_CURRENT1_PRE0_OFFSET);

    val = (signed short)(val1 | ((u32)val2 << 8));

    return val;
}
/*****************************************************************************
 �� �� ��  : coul_current_before_regval
 ��������  : ��ȡ��ǰ��ѹǰtimes�ε����Ĵ���ֵ
 �������  : times:Ҫ��ȡ��ǰ���εĵ���ֵ([��Χ[1,20])
 �������  : ��
 �� �� ֵ  : signed short
 ���ú���  :
 ��������  :
*****************************************************************************/
signed short coul_current_before_regval(unsigned int times)
{
    unsigned char val1;
    unsigned char val2;
    signed short val = 0;

    val1 = coul_reg_read((u16)(HI6551_CURRENT0_PRE0_OFFSET + 2 * times));
    val2 = coul_reg_read((u16)(HI6551_CURRENT1_PRE0_OFFSET + 2 * times));/*���λ�������λ*/

    val = (signed short)(val1 | ((u32)val2 << 8));
    return val;
}
/*****************************************************************************
 �� �� ��  : coul_in_capacity_regval
 ��������  : ��������Ĵ���ֵ��ȡ
 �������  : void
 �������  : ��
 �� �� ֵ  : signed int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int coul_in_capacity_regval(void)
{
    unsigned char val1;
    unsigned char val2;
    unsigned char val3;
    unsigned char val4;
    unsigned int in;

    val1 = coul_reg_read(HI6551_CL_IN0_OFFSET);
    val2 = coul_reg_read(HI6551_CL_IN1_OFFSET);
    val3 = coul_reg_read(HI6551_CL_IN2_OFFSET);
    val4 = coul_reg_read(HI6551_CL_IN3_OFFSET);
    in = (unsigned int)(val1 | ((u32)val2 << 8) | ((u32)val3 << 16) | ((u32)val4 << 24));

    return in;
}
/*****************************************************************************
 �� �� ��  : coul_out_capacity_regval
 ��������  : ���������Ĵ���ֵ��ȡ
 �������  : void
 �������  : ��
 �� �� ֵ  : signed int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int coul_out_capacity_regval(void)
{
    unsigned char val1;
    unsigned char val2;
    unsigned char val3;
    unsigned char val4;
    unsigned int out;

    val1 = coul_reg_read(HI6551_CL_OUT0_OFFSET);
    val2 = coul_reg_read(HI6551_CL_OUT1_OFFSET);
    val3 = coul_reg_read(HI6551_CL_OUT2_OFFSET);
    val4 = coul_reg_read(HI6551_CL_OUT3_OFFSET);

    out = (unsigned int)(val1 | ((u32)val2 << 8) | ((u32)val3 << 16) | ((u32)val4 << 24));

    return out;
}
/*****************************************************************************
 �� �� ��  : coul_ocv_data_regval
 ��������  : ��ص�ѹ��·��ѹ��ֵ�Ĵ���ֵ��ȡ
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned short
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned short coul_ocv_data_regval(void)
{
    unsigned char val1;
    unsigned char val2;
    unsigned short val = 0;

    val1 = coul_reg_read(HI6551_OCV_DATA1_OFFSET);
    val2 = coul_reg_read(HI6551_OCV_DATA2_OFFSET);

    val = (unsigned short)(val1 | ((u32)val2 << 8));
    return val;
}
/*****************************************************************************
 �� �� ��  : coul_ocv_offset_regval
 ��������  : ��ص�ѹ��·��ѹ���Ĵ���ֵ��ȡ
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned short
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned short coul_ocv_offset_regval(void)
{
    unsigned char val1;
    unsigned char val2;
    unsigned short val = 0;

    val1 = coul_reg_read(HI6551_OFFSET_VOLTAGE0_OFFSET);
    val2 = coul_reg_read(HI6551_OFFSET_VOLTAGE1_OFFSET);

    val = (unsigned short)(val1 | ((u32)val2 << 8));
    return val;
}
/*****************************************************************************
 �� �� ��  : coul_battery_charge_time_regval
 ��������  : ���ؼƳ��ʱ������Ĵ���ֵ��ȡ
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int coul_charge_time_regval(void)
{
    unsigned char val1;
    unsigned char val2;
    unsigned char val3;
    unsigned char val4;

    val1 = coul_reg_read(HI6551_LOAD_TIMER0_OFFSET);
    val2 = coul_reg_read(HI6551_LOAD_TIMER1_OFFSET);
    val3 = coul_reg_read(HI6551_LOAD_TIMER2_OFFSET);
    val4 = coul_reg_read(HI6551_LOAD_TIMER3_OFFSET);

    return (unsigned int)val1 | ((u32)val2 << 8) | ((u32)val3 << 16) | ((u32)val4 << 24);
}

/*****************************************************************************
 �� �� ��  : coul_battery_discharge_time_regval
 ��������  : �ŵ�ʱ��Ĵ���ֵ��ȡ
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int coul_discharge_time_regval(void)
{
    unsigned char val1;
    unsigned char val2;
    unsigned char val3;
    unsigned char val4;

    val1 = coul_reg_read(HI6551_CHG_TIMER0_OFFSET);
    val2 = coul_reg_read(HI6551_CHG_TIMER1_OFFSET);
    val3 = coul_reg_read(HI6551_CHG_TIMER2_OFFSET);
    val4 = coul_reg_read(HI6551_CHG_TIMER3_OFFSET);

    return (unsigned int)val1 | ((u32)val2 << 8) | ((u32)val3 << 16) | ((u32)val4 << 24);
}

/*****************************************************************************
 �� �� ��  : coul_set_vbat_value
 ��������  : ���õ�ص͵�ֵ(��ҪУ׼ת���������)
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
*****************************************************************************/
void coul_voltage_low_regval_set(unsigned short value)
{
    unsigned char val1 = (value & 0xff);
    unsigned char val2 = (value >> 8) & 0xff;

    coul_reg_write(HI6551_V_INT0_OFFSET, val1);
    coul_reg_write(HI6551_V_INT1_OFFSET, val2);
}

/*****************************************************************************
 �� �� ��  : coul_power_ctrl
 ��������  :
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
*****************************************************************************/
void coul_power_ctrl(COUL_POWER_CTRL ctrl)
{
    unsigned char val;
    coul_irqflags_t coul_flags = 0;

    spin_lock_irqsave(&g_coul_st.lock,coul_flags);
    val = coul_reg_read(HI6551_CLJ_CTRL_REG_OFFSET);
    if(COUL_POWER_ON == ctrl){
        val |= COUL_CTRL_ONOFF_MASK;
    }else{
        val &= ~COUL_CTRL_ONOFF_MASK;
    }
    coul_reg_write(HI6551_CLJ_CTRL_REG_OFFSET, val);
    spin_unlock_irqrestore(&g_coul_st.lock,coul_flags);
}

/*****************************************************************************
 �� �� ��  : coul_cali_ctrl
 ��������  : �Ƿ�ǿ�ƽ���У׼״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
*****************************************************************************/
void coul_cali_ctrl(COUL_CALI_CTRL ctrl)
{
    unsigned char val;
    coul_irqflags_t coul_flags = 0;

    spin_lock_irqsave(&g_coul_st.lock,coul_flags);
    val = coul_reg_read(HI6551_CLJ_CTRL_REG_OFFSET);
    if(COUL_CALI_ON == ctrl){
        val |= COUL_CTRL_CALI_MASK;
    }else{
        val &= ~COUL_CTRL_CALI_MASK;
    }
    coul_reg_write(HI6551_CLJ_CTRL_REG_OFFSET, val);
    spin_unlock_irqrestore(&g_coul_st.lock,coul_flags);
}

/*****************************************************************************
 �� �� ��  : coul_reflash_ctrl
 ��������  : ˢ�¿���
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
*****************************************************************************/
void coul_reflash_ctrl(COUL_REFLASH_CTRL ctrl)
{
    unsigned char val;
    coul_irqflags_t coul_flags = 0;

    spin_lock_irqsave(&g_coul_st.lock,coul_flags);
    val = coul_reg_read(HI6551_CLJ_CTRL_REG_OFFSET);
    if(COUL_REFLASH_ECO == ctrl){
        val |= COUL_CTRL_REFLASH_MASK;
    }else{
        val &= ~COUL_CTRL_REFLASH_MASK;
    }
    coul_reg_write(HI6551_CLJ_CTRL_REG_OFFSET, val);
    spin_unlock_irqrestore(&g_coul_st.lock,coul_flags);
}

/*****************************************************************************
 �� �� ��  : coul_eco_ctrl
 ��������  :
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
*****************************************************************************/
void coul_eco_ctrl(COUL_ECO_CTRL ctrl)
{
    unsigned char val;
    coul_irqflags_t coul_flags = 0;

    spin_lock_irqsave(&g_coul_st.lock,coul_flags);
    val = coul_reg_read(HI6551_CLJ_CTRL_REG_OFFSET);
    if(COUL_ECO_FORCE == ctrl){
        val |= COUL_CTRL_ECO_MASK;
    }else{
        val &= ~COUL_CTRL_ECO_MASK;
    }
    coul_reg_write(HI6551_CLJ_CTRL_REG_OFFSET, val);
    spin_unlock_irqrestore(&g_coul_st.lock,coul_flags);
}

/*****************************************************************************
 �� �� ��  : bsp_coul_init
 ��������  : ���ؼ�ģ���ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��ʼ���ɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_coul_init(void)
{
    u32 iret = BSP_COUL_OK;

    /*Ĭ����fastboot��������*/
#if 0
    unsigned int low_batt_thres = 3400;

    /* ���ؼ�Ĭ���ѿ���,�������ܺ����ṩ*/

    coul_power_ctrl(COUL_POWER_ON);

    coul_cali_ctrl(COUL_CALI_ON);

    coul_reflash_ctrl(COUL_REFLASH_ECO);

    coul_eco_ctrl(COUL_REFLASH_ECO);

    coul_set_vbat_value(low_batt_thres);
#endif
    spin_lock_init(&g_coul_st.lock);/*�ж�ֻ��Acoreʵ�֣���core������*/

    /*��ȡnvֵ����ȡ��ѹ�����������*/
    /*read nv,get the exc protect setting*/
    iret = bsp_nvm_read(NV_ID_DRV_COUL_CALI,(unsigned char *)&coul_cali_config,sizeof(COUL_CALI_NV_TYPE));

    if(NV_OK != iret)
    {
        coul_err("coul cali read nv error,not set,use the default config!\n");
    }
    else
        coul_err("coul init ok!\n");

    return BSP_COUL_OK;
}
/*********************���½ӿ�˼���Ƿ��нӿ���Ҫʹ��**************************************/
/*****************************************************************************
 �� �� ��  : bsp_coul_enable
 ��������  : �������ؼ�
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
void bsp_coul_enable(void)
{
    coul_power_ctrl(COUL_POWER_ON);
}
/*****************************************************************************
 �� �� ��  : bsp_coul_disable
 ��������  : �رտ��ؼ�
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
void bsp_coul_disable(void)
{
    coul_power_ctrl(COUL_POWER_OFF);
}
/*********************���½ӿ��ṩ����Ʒ��ʹ��**************************************/
/*����У׼����ʱ����*/
/*****************************************************************************
 �� �� ��  : bsp_coul_voltage_uncali
 ��������  : ��ȡδ��У׼��ǰ��ѹ����λ:mV
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int bsp_coul_voltage_uncali(void)
{
    unsigned short  val = 0;
    unsigned int voltage = 0;

    val = coul_voltage_regval();

    voltage = coul_convert_regval2mv(val);

    coul_dbg("uncali:coul_battery_voltage is %d mV\n",voltage);

    return voltage;
}
/*****************************************************************************
 �� �� ��  : bsp_coul_current_uncali
 ��������  : ��ȡδ��У׼��ǰ����,��λ:mA
 �������  : void
 �������  : ��
 �� �� ֵ  : signed long long
 ���ú���  :
 ��������  :
*****************************************************************************/
signed int  bsp_coul_current_uncali(void)
{
    signed short  val = 0;
    signed int bat_current = 0;

    val = coul_current_regval();

    bat_current = coul_convert_regval2ma(val);

    coul_dbg("uncali:coul_battery_current is %d mA\n",bat_current);

    return bat_current;
}
/*****************************************************************************
 �� �� ��  : bsp_coul_voltage
 ��������  : ��ǰ��ѹ��ȡ����λ:mV
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int bsp_coul_voltage(void)
{
    unsigned short  val = 0;
    unsigned int voltage = 0;

    val = coul_voltage_regval();

    voltage = coul_convert_regval2mv_calied(val);

    coul_dbg("calied:coul_battery_voltage is %d mV\n",voltage);

    return voltage;
}
/*****************************************************************************
 �� �� ��  : bsp_coul_voltage_before
 ��������  : ��ȡ��ǰ��ѹ��times�ε�ѹֵ����λ:mV
 �������  : times:Ҫ��ȡ����ĵ�n�εĵ�ѹֵ([��Χ[1,20])
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int  bsp_coul_voltage_before(unsigned int times)
{
    unsigned short  val = 0;
    unsigned int  voltage = 0;

    if(COUL_BEFORE_TIMES_MAX < times)
    {
        coul_err("coul can only support 19 times before!");
        return BSP_COUL_UNVALID;/*�������ִ�����͵�ѹֵ?*/
    }

    val = coul_voltage_before_regval(times);

    voltage = coul_convert_regval2mv_calied(val);

    coul_dbg("calied:before %d times voltage is %d mV\n",times,voltage);

    return voltage;
}
/*****************************************************************************
 �� �� ��  : bsp_coul_current
 ��������  : ��ǰ������ȡ,��λ:mA
 �������  : void
 �������  : ��
 �� �� ֵ  : signed long long
 ���ú���  :
 ��������  :
*****************************************************************************/
signed int  bsp_coul_current(void)
{
    signed short  val = 0;
    signed int bat_current = 0;

    val = coul_current_regval();

    bat_current = coul_convert_regval2ma_calied(val);

    coul_dbg("calied:coul_battery_current is %d mA\n",bat_current);

    return bat_current;
}
/*****************************************************************************
 �� �� ��  : bsp_coul_current_before
 ��������  : ��ȡ��ǰ����ǰtimes�ε���ֵ����λ:mA
 �������  : times:Ҫ��ȡ��ǰ���εĵ���ֵ([��Χ[1,20])
 �������  : ��
 �� �� ֵ  : unsigned long long
 ���ú���  :
 ��������  :
*****************************************************************************/
signed int bsp_coul_current_before(unsigned int times)
{
    signed short  val = 0;
    signed int  bat_current = 0;

    if(COUL_BEFORE_TIMES_MAX < times)
    {
        coul_err("coul can only support 19 times before!");
        return BSP_COUL_ERR;/*�������ִ�����͵�ѹֵ?*/
    }

    val = coul_current_before_regval(times);

    bat_current = coul_convert_regval2ma_calied(val);

    coul_dbg("calied:before %d times current is %d mA\n",times,bat_current);

    return bat_current;
}
/*****************************************************************************
 �� �� ��  : bsp_coul_in_capacity
 ��������  : ������������ȡ,��λ:uC
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned long long
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned long long bsp_coul_in_capacity(void)
{
    unsigned int  val = 0;
    unsigned long long capacity = 0;

    val = coul_in_capacity_regval();

    capacity = coul_convert_regval2uc(val);

    coul_dbg("in capacity is %lld uC\n",capacity);

    return capacity;
}
/*****************************************************************************
 �� �� ��  : bsp_coul_out_capacity
 ��������  : �������������ȡ,��λ:mC
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned long long
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned long long bsp_coul_out_capacity(void)
{
    unsigned int  val = 0;
    unsigned long long capacity = 0;

    val = coul_out_capacity_regval();

    capacity = coul_convert_regval2uc(val);

    coul_dbg("out capacity is %lld uC\n",capacity);

    return capacity;
}
/*****************************************************************************
 �� �� ��  : bsp_coul_charge_time
 ��������  : ���ʱ���ȡ,��λ:s
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int bsp_coul_charge_time(void)
{
    unsigned int  time = 0;

    time = coul_charge_time_regval();

    coul_dbg("charge_time is %d s\n",time);

    return time;
}
/*****************************************************************************
 �� �� ��  : bsp_coul_charge_time
 ��������  : ���ʱ���ȡ,��λ:s
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int bsp_coul_discharge_time(void)
{
    unsigned int  time = 0;

    time = coul_discharge_time_regval();

    coul_dbg("discharge_time is %d s\n",time);

    return time;
}
/*****************************************************************************
 �� �� ��  : bsp_coul_eco_filter_time
 ��������  : ���ÿ��ؼ�eco�˲�ʱ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
void bsp_coul_eco_filter_time(COUL_FILETR_TIME filter_time)
{
    coul_irqflags_t coul_flags = 0;

    spin_lock_irqsave(&g_coul_st.lock,coul_flags);
    coul_reg_mask(HI6551_CLJ_CTRL_REG_OFFSET,filter_time << COUL_CTRL_FILETR_OFFSET ,COUL_CTRL_FILETR_MASK);
    spin_unlock_irqrestore(&g_coul_st.lock,coul_flags);
}
/*****************************************************************************
 �� �� ��  : bsp_coul_int_register
 ��������  : ע����ؼ��жϻص�����
 �������  : int:�жϺţ�func:�жϴ���ص�������data:�ص���������ָ��
 �������  : ��
 �� �� ֵ  : ע��ɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_coul_int_register(COUL_INT_TYPE irq,COUL_INT_FUNC func,void *data)
{
    /*ע���pmu�жϴ���*/
    if(bsp_pmu_irq_callback_register(irq,func,data))
        return BSP_COUL_ERR;
    else
        return BSP_COUL_OK;
}
/*****************************************************************************
 �� �� ��  : coul_ocv_get
 ��������  : ��ؿ�·��ѹ����ֵ��ȡ
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int bsp_coul_ocv_get(void)
{
    unsigned short val = 0;
    unsigned short data_val = 0;
    unsigned short offset_val = 0;
    unsigned int voltage = 0;

    data_val = coul_ocv_data_regval();
    offset_val = coul_ocv_offset_regval();
    val = data_val - offset_val;
    voltage = coul_convert_regval2mv_calied(val);

    coul_dbg("calied:coul_ocv_voltage is %d mv!\n",voltage);

    return voltage;
}
/*****************************************************************************
 �� �� ��  : bsp_coul_cail_on
 ��������  : ���ؼ�ǿ��У׼
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  : 
 ��������  :
*****************************************************************************/
void bsp_coul_cail_on(void)
{
    coul_cali_ctrl(COUL_CALI_ON);
    return;
}
/*�����ṩ*/
#if 0
/*****************************************************************************
 �� �� ��  : bsp_coul_vbat_set
 ��������  : ���õ�ص͵�ֵ,�жϵ���ֵ
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
*****************************************************************************/
void bsp_coul_vbat_set(unsigned short value)
{
    unsigned char val1 = (value & 0xff);
    unsigned char val2 = (value >> 8) & 0xff;

    coul_reg_write(HI6551_V_INT0_OFFSET, val1);
    coul_reg_write(HI6551_V_INT1_OFFSET, val2);
}
#endif
static void __exit bsp_coul_exit(void)
{
}
module_exit(bsp_coul_exit);
module_init(bsp_coul_init);
MODULE_LICENSE("GPL");

