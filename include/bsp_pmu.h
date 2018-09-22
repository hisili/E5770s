

#ifndef _BSP_PMU_H_
#define _BSP_PMU_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#include "osl_types.h"

#ifdef __VXWORKS__
#include <drv_dpm.h>
#include <drv_pmu.h>
#endif

#ifdef __FASTBOOT__
#include <boot/boot.h>
#include "types.h"
#endif

#include "bsp_om.h"

/*PMU VOLT MODE */
typedef enum  _pmu_mode_e
{
    PMU_MODE_NORMAL = 0,        /* ��ͨģʽ */
    PMU_MODE_ECO = 1,           /* HI6451�е�Դ��ecoģʽ */
    PMU_MODE_ECO_FORCE = 2,     /* HI6551/HI6559�е�Դ��ecoģʽ:ǿ�ƽ���ecoģʽ */
    PMU_MODE_ECO_FOLLOW = 3,    /* HI6551/HI6559�е�Դ��ecoģʽ:����pmu����ecoģʽ */
    PMU_MODE_NONE = 4,          /* HI6551/HI6559�е�Դ��ģʽ:��·û��ecoģʽ */
    PMU_MODE_BUTTOM
}pmu_mode_e;

/*pmu״̬�궨�壬��om����*/
#define PMU_STATE_OK    0
#define PMU_STATE_UNDER_VOL 1 << 0
#define PMU_STATE_OVER_VOL  1 << 1
#define PMU_STATE_OVER_CUR  1 << 2
#define PMU_STATE_OVER_TEMP 1 << 3

/*fastboot���ṩ��lcdģ�鿪�ص�Դ*/
#ifdef __FASTBOOT__
typedef enum  _power_switch_e
{
    POWER_OFF = 0,
    POWER_ON ,
    POWER_SWITCH_BUTTOM
}power_switch_e;

/*��������*/
/*****************************************************************************
 �� �� ��  : bsp_pmu_init
 ��������  : pmuģ���ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : fastboot��pmuģ���ʼ��ʱ����
*****************************************************************************/
void bsp_pmu_init(void);

/*****************************************************************************
 �� �� ��  : bsp_pmu_lcd_io_power_switch
 ��������  : ����lcdio�ĵ�ѹԴ(lvs04)
 �������  : power_switch_e sw��POWER_ON:�򿪣�POWER_OFF:�رգ�
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : ��
*****************************************************************************/
s32 bsp_pmu_lcd_io_power_switch(power_switch_e sw);

/*****************************************************************************
 �� �� ��  : bsp_pmu_lcd_analog_power_switch
 ��������  : ����lcdģ���Դ(ldo14)
 �������  : ��
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : fastboot��lcd�ļ�����
*****************************************************************************/
s32 bsp_pmu_lcd_analog_power_switch(power_switch_e sw);

/*****************************************************************************
 �� �� ��  : bsp_pmu_lcd_analog_volt_set
 ��������  : ����lcdģ���Դ(ldo14)��ѹ
 �������  : s32 voltage:Ҫ���õĵ�ѹֵ����λuV!
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : fastboot��lcd�ļ�����
*****************************************************************************/
s32 bsp_pmu_lcd_analog_volt_set(s32 voltage);

/*****************************************************************************
 �� �� ��  : bsp_pmu_lcd_bl_power_switch
 ��������  : ����lcd����
 �������  :
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : fastboot��lcd�ļ�����
*****************************************************************************/
s32 bsp_pmu_lcd_bl_power_switch(power_switch_e sw);

/*****************************************************************************
 �� �� ��  : bsp_pmu_lcd_analog_volt_set
 ��������  : ����lcd����ĵ���
 �������  : s32 cur:Ҫ���õĵ���ֵ����λuA!
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : fastboot��lcd�ļ�����
*****************************************************************************/
s32 bsp_pmu_lcd_bl_current_set(s32 cur);

/*****************************************************************************
 �� �� ��  : bsp_pmu_efuse_power_switch
 ��������  : ����efuse��Դ(ldo23)
 �������  : ��
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : fastboot��efuse�ļ�����
*****************************************************************************/
s32 bsp_pmu_efuse_power_switch(power_switch_e sw);

/*****************************************************************************
 �� �� ��  : bsp_pmu_efuse_volt_set
 ��������  : ����lcdģ���Դ(ldo14)��ѹ
 �������  : s32 voltage:Ҫ���õĵ�ѹֵ����λuV!
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : fastboot��lcd�ļ�����
*****************************************************************************/
s32 bsp_pmu_efuse_volt_set(s32 voltage);

/*****************************************************************************
 �� �� ��  : bsp_pmu_hreset_state_get
 ��������  : �ж�pmu�Ƿ�Ϊ������
 �������  : void
 �������  : ��
 �� �� ֵ     : pmu����������������(1:��������0:������)
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool bsp_pmu_hreset_state_get(void);

/*****************************************************************************
 �� �� ��  : bsp_pmu_hreset_state_get
 ��������  : ���pmu��������־
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
void bsp_pmu_hreset_state_clear(void);

/*****************************************************************************
 �� �� ��  : bsp_pmu_version_get
 ��������  : ��ȡusb�Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : usb�����γ�:1:����;0:�γ�
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool bsp_pmu_usb_state_get(void);

/*****************************************************************************
 �� �� ��  : bsp_pmu_key_state_get
 ��������  : ��ȡ�����Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : �����Ƿ���:1:���£�0:δ����
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool bsp_pmu_key_state_get(void);

/*****************************************************************************
 �� �� ��  : bsp_pmu_version_get
 ��������  : ��ȡpmu�汾��
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ���ú���  :
 ��������  : ����hso��msp����
*****************************************************************************/
u8 bsp_pmu_version_get(void);

/*****************************************************************************
 �� �� ��  : bsp_pmu_get_boot_state
 ��������  :ϵͳ����ʱ���pmu�Ĵ���״̬��
                ȷ���Ƿ�����pmu���������
 �������  : void
 �������  : reset.log
 �� �� ֵ  : pmu�����ok
 ���ú���  :
 ��������  :ϵͳ��ά�ɲ�
*****************************************************************************/
s32 bsp_pmu_get_boot_state(void);

/*****************************************************************************
 �� �� ��  : bsp_pmu_default_set
 ��������  : PMUģ�����nv����������Ĭ�ϵ�ѹ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : fastboot main����
*****************************************************************************/
void bsp_pmu_set_by_nv(void);
int bsp_dr_current_set(int dr_id, int min_uA, int max_uA);
int bsp_dr_switch(int dr_id, power_switch_e sw);
#endif

#ifdef __KERNEL__

/*PMU 32K CLK ö������ */
typedef enum  _pmu_clk_e
{
    PMU_32K_CLK_A = 0,   /*SOC˯��ʱ�ӣ�����ģ�鲻��ʹ��*/
    PMU_32K_CLK_B,       /**/
#if defined(CONFIG_PMIC_HI6551)
    PMU_32K_CLK_C,       /*ֻ��hi6551���и�·ʱ��*/
#endif
    PMU_32K_CLK_MAX
}pmu_clk_e;



/*��ʹ��pmu�жϵ�ģ�����*/
typedef void (*pmufuncptr)(void *);

typedef enum  _pmu_int_e
{
#if defined(CONFIG_PMIC_HI6451)
    PMU_INT_POWER_KEY_1SS_PRESS =      5,
    PMU_INT_POWER_KEY_20MS_RELEASE =   6,
    PMU_INT_POWER_KEY_20MS_PRESS =     7,
    PMU_INT_USB_IN = 10 ,
    PMU_INT_USB_OUT = 11 ,
    PMU_INT_ALARM_A = 16 ,
    PMU_INT_ALARM_B = 17 ,
    PMU_INT_ALARM_C = 18 ,
#elif defined(CONFIG_PMIC_HI6551)
    PMU_INT_POWER_KEY_1SS_PRESS =     4,
    PMU_INT_POWER_KEY_20MS_RELEASE =  5,
    PMU_INT_POWER_KEY_20MS_PRESS =    6,
    PMU_INT_USB_OUT = 9 ,
    PMU_INT_USB_IN  = 10 ,
    PMU_INT_ALARM_A = 11 ,
    PMU_INT_ALARM_B = 12 ,
    PMU_INT_ALARM_C = 13 ,
#elif defined(CONFIG_PMIC_HI6559)
    PMU_INT_POWER_KEY_1SS_PRESS =     4,
    PMU_INT_POWER_KEY_20MS_RELEASE =  5,
    PMU_INT_POWER_KEY_20MS_PRESS =    6,
    PMU_INT_USB_OUT = 9 ,
    PMU_INT_USB_IN  = 10 ,
    PMU_INT_ALARM_A = 11 ,
    PMU_INT_ALARM_B = 12 ,
    PMU_INT_ALARM_C = 13 ,
#else
    PMU_INT_POWER_KEY_1SS_PRESS = 100,/*�˲���Ϊ������hi6451��hi6551ʱ�Ĵ�׮*/
    PMU_INT_POWER_KEY_20MS_RELEASE,
    PMU_INT_POWER_KEY_20MS_PRESS,
    PMU_INT_USB_IN ,
    PMU_INT_USB_OUT,
    PMU_INT_ALARM_A,
    PMU_INT_ALARM_B,
    PMU_INT_ALARM_C,
#endif
/*������жϺ�ֻ��hi6551�д���,ʹ����ע��*/
#if defined(CONFIG_PMIC_HI6551)
    PMU_INT_ALARM_D = 14 ,
    PMU_INT_ALARM_E = 15 ,
    PMU_INT_ALARM_F = 16 ,
    PMU_INT_SIM0_IN_FALL = 17 ,
    PMU_INT_SIM0_IN_RAISE = 18 ,
    PMU_INT_SIM0_OUT_FALL = 19 ,
    PMU_INT_SIM0_OUT_RAISE = 20 ,
    PMU_INT_SIM1_IN_FALL = 21 ,
    PMU_INT_SIM1_IN_RAISE = 22 ,
    PMU_INT_SIM1_OUT_FALL = 23 ,
    PMU_INT_SIM1_OUT_RAISE = 24 ,
    PMU_INT_COUL_INT = 25 ,   /*cl_out>cl_intʱ�ϱ��ж�*/
    PMU_INT_COUL_OUT = 26 ,    /*cl_out������81.25%�ϱ��ж�*/
    PMU_INT_COUL_IN = 27 ,      /*cl_in������81.25%�ϱ��ж�*/
    PMU_INT_CHG_TIMER = 28 ,  /*chg_timer������81.25%�ϱ��ж�*/
    PMU_INT_LOAD_TIMER = 29 ,/*load_timer������81.25%�ϱ��ж�*/
    PMU_INT_VBAT_INT = 30 ,    /*vbat��ѹ<�趨��vbat_intֵ*/
#elif defined(CONFIG_PMIC_HI6559) 
    PMU_INT_ALARM_D = 14 ,
    PMU_INT_ALARM_E = 15 ,
    PMU_INT_ALARM_F = 16 ,
    PMU_INT_SIM0_IN_FALL = 17 ,
    PMU_INT_SIM0_IN_RAISE = 18 ,
    PMU_INT_SIM0_OUT_FALL = 19 ,
    PMU_INT_SIM0_OUT_RAISE = 20 ,
#else
/*û�ж���hi6551�Ĵ�׮,ʹ����ע��*/
    PMU_INT_ALARM_D = 150 ,
    PMU_INT_ALARM_E,
    PMU_INT_ALARM_F,
    PMU_INT_SIM0_OUT_FALL,
    PMU_INT_SIM0_OUT_RAISE,
    PMU_INT_SIM0_IN_FALL,
    PMU_INT_SIM0_IN_RAISE,
    PMU_INT_SIM1_OUT_FALL,
    PMU_INT_SIM1_OUT_RAISE,
    PMU_INT_SIM1_IN_FALL,
    PMU_INT_SIM1_IN_RAISE,
    PMU_INT_COUL_INT,   /*cl_out>cl_intʱ�ϱ��ж�*/
    PMU_INT_COUL_OUT,    /*cl_out������81.25%�ϱ��ж�*/
    PMU_INT_COUL_IN,      /*cl_in������81.25%�ϱ��ж�*/
    PMU_INT_CHG_TIMER,  /*chg_timer������81.25%�ϱ��ж�*/
    PMU_INT_LOAD_TIMER,/*load_timer������81.25%�ϱ��ж�*/
    PMU_INT_VBAT_INT,    /*vbat��ѹ<�趨��vbat_intֵ*/
#endif
    PMU_INT_BUTTOM
}pmu_int_e;

#endif

/*DRģ�飬��led����*/
#if defined(__FASTBOOT__) || defined(__KERNEL__)
/*DR���*/
typedef enum  _dr_id_e
{
    PMU_DR01 = 1,
    PMU_DR02 ,
    PMU_DR03 ,
    PMU_DR04 ,
    PMU_DR05 ,
    DR_ID_BUTTOM
}dr_id_e;
#define PMU_DR_MIN  PMU_DR01
#define PMU_DR_MAX  PMU_DR05
typedef enum  _dr_mode_e
{
    PMU_DRS_MODE_FLA_FLASH = 0,    /*��˸����ģʽ(DR1/2/3/4/5)*/
    PMU_DRS_MODE_FLA_LIGHT ,       /*��˸����ģʽ(DR1/2/3/4/5)*/
    PMU_DRS_MODE_BRE ,       /*����ģʽ(DR3/4/5)*/
    PMU_DRS_MODE_BRE_FLASH , /*������˸ģʽ���߾�����˸(DR1/2)*/
    PMU_DRS_MODE_BRE_LIGHT , /*��������ģʽ(DR1/2)*/
    PMU_DRS_MODE_BUTTOM
}dr_mode_e;

typedef enum  _dr_bre_time_e
{
    PMU_DRS_BRE_ON_MS = 0,    /*��������ʱ��(DR1/2/3/4/5)*/
    PMU_DRS_BRE_OFF_MS ,       /*��������ʱ��(DR1/2/3/4/5)*/
    PMU_DRS_BRE_RISE_MS ,       /*��������ʱ��(DR1/2/3/4/5))*/
    PMU_DRS_BRE_FALL_MS ,       /*��������ʱ��(DR1/2/3/4/5))*/
    PMU_DRS_BRE_TIME_BUTTOM
}dr_bre_time_e;

typedef struct
{
    /*unsigned int fla_feriod_us;��˸����ʱ��*/
    unsigned int fla_on_us;/*��˸����ʱ��*/
    unsigned int fla_off_us;/*��˸����ʱ��*/
}DR_FLA_TIME;

typedef struct
{
    unsigned int bre_on_ms;
    unsigned int bre_off_ms;
    unsigned int bre_rise_ms;
    unsigned int bre_fall_ms;
}DR_BRE_TIME;

#define ALWAYS_ON_OFF_TIME_DR12     5000/*�������߳����Ĵ�������ֵ*/
#define ALWAYS_ON_OFF_TIME_DR345    50000/*�������߳����Ĵ�������ֵ*/
#define BRE_TIME_NOT_SURE    0xfffffe/*�������߳����Ĵ�������ֵ*/
#define DR_VALUE_INVALIED   0xffffffff
#define DR345_START_DELAY_STEP  256
#define DR_CUR_NUMS 8   /*����Դ��λ��Ϊ8*/

/*error code*/
#define BSP_DR_OK              0
#define BSP_DR_ERROR          (-1)
#endif

#ifdef __KERNEL__
/*��������*/
/*****************************************************************************
 �� �� ��  : bsp_pmu_get_boot_state
 ��������  :ϵͳ����ʱ���pmu�Ĵ���״̬��
                ȷ���Ƿ�����pmu���������
 �������  : void
 �������  : reset.log
 �� �� ֵ  : pmu�����ok
 ���ú���  :
 ��������  :ϵͳ��ά�ɲ�
*****************************************************************************/
int bsp_pmu_get_boot_state(void);

/*****************************************************************************
 �� �� ��  : bsp_pmu_32k_clk_enable
 ��������  : ����pmu��32kʱ��
 �������  : clk_id:32kʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_32k_clk_enable(pmu_clk_e clk_id);
/*****************************************************************************
 �� �� ��  : bsp_pmu_32k_clk_disable
 ��������  : �ر�pmu��32kʱ��
 �������  : clk_id:32kʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �رճɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_32k_clk_disable(pmu_clk_e clk_id);
/*****************************************************************************
 �� �� ��  : bsp_pmu_32k_clk_is_enabled
 ��������  : ��ѯpmu��32kʱ���Ƿ���
 �������  : clk_id:32kʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : ������ر�
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_32k_clk_is_enabled(pmu_clk_e clk_id);
/*****************************************************************************
 �� �� ��  : bsp_pmu_version_get
 ��������  : ��ȡusb�Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : usb�����γ�:1:����;0:�γ�
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool bsp_pmu_usb_state_get(void);
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
void bsp_pmu_irq_mask(unsigned int irq);
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
void bsp_pmu_irq_unmask(unsigned int irq);
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
int bsp_pmu_irq_is_masked(unsigned int irq);
/*****************************************************************************
 �� �� ��  : bsp_pmu_key_state_get
 ��������  : ��ȡ�����Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : �����Ƿ���:1:���£�0:δ����
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool bsp_pmu_key_state_get(void);
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
int bsp_pmu_irq_callback_register(unsigned int irq,pmufuncptr routine,void *data);
/*****************************************************************************
* �� �� ��  : bsp_dr_list_current
* ��������  :��ѯĳ·����Դָ����λ������
* �������  :dr_id:����Դid�ţ�selector��Ҫ��ѯ�ĵ�λ��
* �������  :��
* ����ֵ��   ����ѯ�ĵ���Դָ����λ�ĵ���ֵ����λ��uA��
*
*****************************************************************************/
int bsp_dr_list_current(int dr_id, unsigned selector);
/*****************************************************************************
* �� �� ��  : bsp_pmu_dr_set_mode
* ��������  :����ĳ·����Դģʽ��
* �������  :dr_id:����Դid�ţ�mode�����õ�ģʽ��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_dr_set_mode(int dr_id, dr_mode_e mode);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_dr_get_mode
* ��������  :��ȡĳ·����Դģʽ��
* �������  :dr_id:����Դid�ţ�
* �������  :��
* ����ֵ��   ����Դ��ǰģʽ
*
*****************************************************************************/
dr_mode_e bsp_dr_get_mode(int dr_id);
/*****************************************************************************
 �� �� ��  : bsp_dr_fla_time_set
 ��������  : ����dr����˸����ʱ��͵���ʱ��
 �������  : dr_fla_time_st:��˸ʱ������ṹ��;��λ:us
 �������  : ��
 �� �� ֵ  : ���óɹ�����ʧ��
 ���ú���  :
 ��ע˵��  : ��Ӧ�Ĵ���ֻ������ʱ��Ĺ��ܣ�����Ҫ������
             ��˸����:reg_value*31.25ms;����ʱ��:reg_value*7.8125ms
*****************************************************************************/
int bsp_dr_fla_time_set(DR_FLA_TIME *dr_fla_time_st);
int bsp_dr_fla_time_get(DR_FLA_TIME *dr_fla_time_st);
/*****************************************************************************
 �� �� ��  : bsp_dr_bre_time_set
 ��������  : ����dr�ĺ���ʱ��(��������������������������ʱ��)
 �������  : dr_id:Ҫ���õĵ���Դ���;dr_bre_time_st:����ʱ������ṹ��;
            û���ҵ����õ�ʱ�䣬������Ϊ����
 �������  : ��
 �� �� ֵ  : ���óɹ�����ʧ��
 ���ú���  :
 ��ע˵��  : ��Ӧ�Ĵ���ֻ������ʱ��Ĺ��ܣ�����Ҫ������
*****************************************************************************/
int bsp_dr_bre_time_set(dr_id_e dr_id, DR_BRE_TIME *dr_bre_time_st);
int bsp_dr_bre_time_get(dr_id_e dr_id, DR_BRE_TIME *dr_bre_time_st);
/*****************************************************************************
 �� �� ��  : bsp_dr_bre_time_list
 ��������  : ����dr�ĺ���ʱ��(��������������������������ʱ��)����λ��ʱ��ֵ
 �������  : dr_id:Ҫ��ѯ�ĵ���Դ���;bre_time_enum:��Ҫ��ѯ��ʱ������;
             selector��ʱ�䵵λ
 �������  : ��
 �� �� ֵ  : ��λʱ��
 ���ú���  :
 ��ע˵��  :
*****************************************************************************/
unsigned bsp_dr_bre_time_list(dr_id_e dr_id, dr_bre_time_e bre_time_enum ,unsigned selector);
/*****************************************************************************
 �� �� ��  : bsp_dr_bre_time_selectors_get
 ��������  : ��ȡdr ����ʱ���ܹ���λֵ
 �������  : dr_id:Ҫ���õĵ���Դ���;bre_time_enum:��Ҫ��ѯ��ʱ������;
 �������  : ��
 �� �� ֵ  : ��λʱ��
 ���ú���  :
 ��ע˵��  :
*****************************************************************************/
unsigned bsp_dr_bre_time_selectors_get(dr_id_e dr_id, dr_bre_time_e bre_time_enum);
/*****************************************************************************
 �� �� ��  : bsp_dr_start_delay_set
 ��������  : ����dr��������ʱʱ��
 �������  : dr_id:Ҫ���õĵ���Դ���;delay_ms:������ʱ��ʱ�䣬��λ:ms
             ���÷�Χ:[0 , 32768]ms
 �������  : ��
 �� �� ֵ  : ���óɹ���ʧ��
 ���ú���  :
 ��ע˵��  : ��Ӧ�Ĵ���ֻ������ʱ��Ĺ��ܣ�����Ҫ��������ֻ��DR3/4/5�д˹���
*****************************************************************************/
int bsp_dr_start_delay_set(dr_id_e dr_id, unsigned delay_ms);
/*****************************************************************************

 �� �� ��  : bsp_pmu_sim_debtime_set
 ��������  : ����SIM���ж�ȥ��ʱ�䣬��λ��us��
 �������  : uctime
:���õ�ȥ��ʱ��(��Χ��(120,600),step:30;)
 �������  : ���óɹ���ʧ��
 �� �� ֵ  : ��
 ���ú���  :

 ��������  : sim��ģ��
*****************************************************************************/

int bsp_pmu_sim_debtime_set(u32 uctime);
void bsp_pmu_ldo22_res_enable(void);
void bsp_pmu_ldo22_res_disable(void);
#endif

#if defined(__VXWORKS__) || defined(__CMSIS_RTOS)
/*****************************************************************************

 �� �� ��  : bsp_pmu_init
 ��������  : ϵͳ������ʼ��pmu����ź���
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
��������  :ccore��mcoreϵͳ��ʼ����غ���
*****************************************************************************/

void bsp_pmu_init(void);
int bsp_sim_upres_disable(u32 sim_id);
#endif

#if defined(__VXWORKS__)
s32 bsp_pmu_apt_enable(void);
s32 bsp_pmu_apt_disable(void);
s32 bsp_pmu_apt_status_get(void);
#endif

/*fastboot��a��c��mcore���ṩ*/
/*****************************************************************************
 �� �� ��  : bsp_pmu_version_get
 ��������  : ��ȡpmu�汾��
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ���ú���  :
 ��������  : ����hso��msp����
*****************************************************************************/
u8 bsp_pmu_version_get(void);

#ifdef CONFIG_PMIC_HI6451

#define PMIC_HI6451_BUCK1  1
#define PMIC_HI6451_BUCK2  2
#define PMIC_HI6451_BUCK3  3
#define PMIC_HI6451_BUCK4  4
#define PMIC_HI6451_BUCK5  5
#define PMIC_HI6451_BUCK6  6
#define PMIC_HI6451_LDO1   7
#define PMIC_HI6451_LDO2   8
#define PMIC_HI6451_LDO3   9
#define PMIC_HI6451_LDO4   10
#define PMIC_HI6451_LDO5   11
#define PMIC_HI6451_LDO6   12
#define PMIC_HI6451_LDO7   13
#define PMIC_HI6451_LDO8   14
#define PMIC_HI6451_LDO9   15
#define PMIC_HI6451_LDO10  16
#define PMIC_HI6451_LDO11  17
#define PMIC_HI6451_LDO12  18
#define PMIC_HI6451_LDO13  19
#define PMIC_HI6451_LDO14  20
#define PMIC_HI6451_LDO15  21
#define PMIC_HI6451_DR1    22
#define PMIC_HI6451_DR2    23
#define PMIC_HI6451_DR3    24


#define PMIC_HI6451_REGULATOR_MIN   PMIC_HI6451_BUCK1
#define PMIC_HI6451_REGULATOR_MAX   PMIC_HI6451_DR3/*APT����ע��*/
#define PMIC_HI6451_VOLT_ECO_MIN    PMIC_HI6451_BUCK1
#define PMIC_HI6451_VOLT_ECO_MAX    PMIC_HI6451_LDO15
#define PMIC_HI6451_VOLT_MIN    PMIC_HI6451_BUCK1
#define PMIC_HI6451_VOLT_MAX    PMIC_HI6451_DR3
/*delete later*/
#define PMIC_MAX_VECO_NUM 22

/*������*/
#define SPI_BAUT_RATE 2000000
/*PMIC����Э���ַƫ��*/
#define ADDR_BIT_OFFSET 9
/*PMIC����Э������ƫ��*/
#define CMD_BIT_OFFSET 8
#define HI6451_32K_CLK_A 1
#define HI6451_32K_CLK_B 2

typedef struct{
u8 onoff_reg_addr;
u8 onoff_bit_offset;
u8 voltage_reg_addr;
u8 voltage_bit_mask;
u8 voltage_bit_offset;
u8 voltage_nums;
u8 eco_reg_addr;
u8 eco_bit_offset;
int *voltage_list;
}PMIC_HI6451_VLTGS_ATTR;

/*��������*/
/*****************************************************************************
* �� �� ��  : bsp_hi6451_reg_write
* ��������  :дhi6451�Ĵ�����
* �������  :addr:Ҫ�����ļĴ�����ַ��value:Ҫд���ֵ
* �������  :��
* ����ֵ��   ��
*
*****************************************************************************/
int bsp_hi6451_reg_write( u8 addr, u8 value);
/*****************************************************************************
* �� �� ��  : bsp_hi6451_reg_read
* ��������  :��hi6451�Ĵ�����
* �������  :addr:Ҫ�����ļĴ�����ַ��pValue:������ֵ
* �������  :��
* ����ֵ��   ��
*
*****************************************************************************/
int bsp_hi6451_reg_read( u8 addr, u8 *pValue);
/*****************************************************************************
* �� �� ��  : bsp_hi6451_reg_show
* ��������  :��ʾhi6451�Ĵ������ݡ�
* �������  :addr:Ҫ�����ļĴ�����ַ;
* �������  :������ֵ
* ����ֵ��   ��
*
*****************************************************************************/
int  bsp_hi6451_reg_show( u8 addr);
/*****************************************************************************
* �� �� ��  : bsp_hi6451_reg_write_mask
* ��������  :�����Ĵ�����ĳ��bit��
* �������  :addr:Ҫ�����ļĴ�����ַ��value:Ҫд���ֵ;
*               mask:
* �������  :��
* ����ֵ��   ��
*
*****************************************************************************/
int bsp_hi6451_reg_write_mask(u8 addr, u8 value, u8 mask);
/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_is_enabled
* ��������  :��ѯĳ·��ѹԴ�Ƿ�����
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   ������������0���رգ�����:ʧ��
*
*****************************************************************************/
int bsp_hi6451_volt_is_enabled(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_enable
* ��������  :��ĳ·��ѹԴ��
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6451_volt_enable(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_disable
* ��������  :�ر�ĳ·��ѹԴ��
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6451_volt_disable(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_get_voltage
* ��������  :��ȡĳ·��ѹԴ��ѹ��
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   ��ѹֵ����λ��uV��
*
*****************************************************************************/
int bsp_hi6451_volt_get_voltage(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_set_voltage
* ��������  :����ĳ·��ѹԴ��ѹ��
* �������  :volt_id:��ѹԴid�ţ�min_uV�����õ���С��ѹ��max_uV������ѹ��
* �������  :selector�������õĵ�ѹ�ǵڼ���
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6451_volt_set_voltage(int volt_id, int min_uV, int max_uV, unsigned *selector);
/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_set_mode
* ��������  :����ĳ·��ѹԴģʽ��
* �������  :volt_id:��ѹԴid�ţ�mode�����õ�ģʽ��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6451_volt_set_mode(int volt_id, pmu_mode_e mode);
/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_get_mode
* ��������  :��ȡĳ·��ѹԴ��ѹ��
* �������  :volt_id:��ѹԴid�ţ�
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
pmu_mode_e bsp_hi6451_volt_get_mode(int volt_id);

/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_list_voltage
* ��������  :��ѯĳ·��ѹԴָ����λ��ѹ��
* �������  :volt_id:��ѹԴid�ţ�selector��Ҫ��ѯ�ĵ�λ��
* �������  :��
* ����ֵ��   ����ѯ�ĵ�ѹԴָ����λ�ĵ�ѹֵ����λ��uV��
*
*****************************************************************************/
int bsp_hi6451_volt_list_voltage(int volt_id, unsigned selector);

#ifdef __VXWORKS__
int bsp_pmu_hi6451_init(void);
#endif

#endif

#ifdef CONFIG_PMIC_HI6551
 #define PMIC_HI6551_BUCK0  0
 #define PMIC_HI6551_BUCK1  1
 #define PMIC_HI6551_BUCK2  2
 #define PMIC_HI6551_BUCK3  3
 #define PMIC_HI6551_BUCK4  4
 #define PMIC_HI6551_BUCK5  5
 #define PMIC_HI6551_BUCK6  6
 #define PMIC_HI6551_BOOST  7
 #define PMIC_HI6551_LDO01  8
 #define PMIC_HI6551_LDO02  9
 #define PMIC_HI6551_LDO03  10
 #define PMIC_HI6551_LDO04  11
 #define PMIC_HI6551_LDO05  12
 #define PMIC_HI6551_LDO06  13
 #define PMIC_HI6551_LDO07  14
 #define PMIC_HI6551_LDO08  15
 #define PMIC_HI6551_LDO09  16
 #define PMIC_HI6551_LDO10  17
 #define PMIC_HI6551_LDO11  18
 #define PMIC_HI6551_LDO12  19
 #define PMIC_HI6551_LDO13  20
 #define PMIC_HI6551_LDO14  21
 #define PMIC_HI6551_LDO15  22
 #define PMIC_HI6551_LDO16  23
 #define PMIC_HI6551_LDO17  24
 #define PMIC_HI6551_LDO18  25
 #define PMIC_HI6551_LDO19  26
 #define PMIC_HI6551_LDO20  27
 #define PMIC_HI6551_LDO21  28
 #define PMIC_HI6551_LDO22  29
 #define PMIC_HI6551_LDO23  30
 #define PMIC_HI6551_LDO24  31
 #define PMIC_HI6551_LVS02  32
 #define PMIC_HI6551_LVS03  33
 #define PMIC_HI6551_LVS04  34
 #define PMIC_HI6551_LVS05  35
 #define PMIC_HI6551_LVS06  36
 #define PMIC_HI6551_LVS07  37
 #define PMIC_HI6551_LVS08  38
 #define PMIC_HI6551_LVS09  39
 #define PMIC_HI6551_LVS10  40

#define PMIC_HI6551_VOLT_MIN        PMIC_HI6551_BUCK2
#define PMIC_HI6551_VOLT_MAX        PMIC_HI6551_LVS10
#define PMIC_HI6551_BUCK_MAX        PMIC_HI6551_BUCK6
#define PMIC_HI6551_LDO_MIN         PMIC_HI6551_LDO01
#define PMIC_HI6551_LDO_MAX         PMIC_HI6551_LDO24
#define PMIC_HI6551_LVS_MIN         PMIC_HI6551_LVS02
#define PMIC_HI6551_LVS_MAX         PMIC_HI6551_LVS10

/*DR���*/
#define PMIC_HI6551_DR01     1
#define PMIC_HI6551_DR02     2
#define PMIC_HI6551_DR03     3
#define PMIC_HI6551_DR04     4
#define PMIC_HI6551_DR05     5

typedef struct
{
    u16 enable_reg_addr;
    u16 disable_reg_addr;

    u16 is_enabled_reg_addr;
    u16 voltage_reg_addr;

    u16 eco_follow_reg_addr;
    u16 eco_force_reg_addr;

    u8 enable_bit_offset;
    u8 disable_bit_offset;
    u8 is_enabled_bit_offset;
    u8 voltage_bit_mask;

    u8 voltage_bit_offset;
    u8 voltage_nums;
    u8 eco_follow_bit_offset;
    u8 eco_force_bit_offset;

    int voltage_list[8];
}PMIC_HI6551_VLTGS_ATTR;

typedef struct
{
    unsigned long   magic_start;
    PMIC_HI6551_VLTGS_ATTR    hi6551_volt_attr[PMIC_HI6551_VOLT_MAX+1];
    unsigned long   magic_end;
} PMIC_HI6551_VLTGS_TABLE;

/*��������*/
/*****************************************************************************
* �� �� ��  : bsp_hi6551_reg_write
* ��������  :дhi6551�Ĵ�����
* �������  :addr:Ҫ�����ļĴ�����ַ��value:Ҫд���ֵ
* �������  :��
* ����ֵ��   ��
*
*****************************************************************************/
void bsp_hi6551_reg_write( u16 addr, u8 value);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_reg_read
* ��������  :��hi6551�Ĵ�����
* �������  :addr:Ҫ�����ļĴ�����ַ��pValue:������ֵ
* �������  :��
* ����ֵ��   ��
*
*****************************************************************************/
void  bsp_hi6551_reg_read( u16 addr, u8 *pValue);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_reg_show
* ��������  :��ʾhi6551�Ĵ������ݡ�
* �������  :addr:Ҫ�����ļĴ�����ַ;
* �������  :������ֵ
* ����ֵ��   ��
*
*****************************************************************************/
int  bsp_hi6551_reg_show( u16 addr);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_reg_write_mask
* ��������  :�����Ĵ�����ĳ��bit��
* �������  :addr:Ҫ�����ļĴ�����ַ��value:Ҫд���ֵ;
*               mask:
* �������  :��
* ����ֵ��   ��
*
*****************************************************************************/
void bsp_hi6551_reg_write_mask(u16 addr, u8 value, u8 mask);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_volt_is_enabled
* ��������  :��ѯĳ·��ѹԴ�Ƿ�����
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   ��0��������0���ر�
*
*****************************************************************************/
int bsp_hi6551_volt_is_enabled(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_volt_enable
* ��������  :��ĳ·��ѹԴ��
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6551_volt_enable(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_volt_disable
* ��������  :�ر�ĳ·��ѹԴ��
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6551_volt_disable(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_volt_get_voltage
* ��������  :��ȡĳ·��ѹԴ��ѹ��
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   ��ѹֵ����λ��uV��
*
*****************************************************************************/
int bsp_hi6551_volt_get_voltage(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_volt_set_voltage
* ��������  :����ĳ·��ѹԴ��ѹ��
* �������  :volt_id:��ѹԴid�ţ�min_uV�����õ���С��ѹ��max_uV������ѹ��
* �������  :selector�������õĵ�ѹ�ǵڼ���
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6551_volt_set_voltage(int volt_id, int min_uV, int max_uV, unsigned *selector);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_volt_list_voltage
* ��������  :��ѯĳ·��ѹԴָ����λ��ѹ��
* �������  :volt_id:��ѹԴid�ţ�selector��Ҫ��ѯ�ĵ�λ��
* �������  :��
* ����ֵ��   ����ѯ�ĵ�ѹԴָ����λ�ĵ�ѹֵ����λ��uV��
*
*****************************************************************************/
int bsp_hi6551_volt_list_voltage(int volt_id, unsigned selector);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_volt_set_mode
* ��������  :����ĳ·��ѹԴģʽ��
* �������  :volt_id:��ѹԴid�ţ�mode�����õ�ģʽ��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6551_volt_set_mode(int volt_id, pmu_mode_e mode);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_volt_get_mode
* ��������  :��ȡĳ·��ѹԴ��ѹ��
* �������  :volt_id:��ѹԴid�ţ�
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
pmu_mode_e bsp_hi6551_volt_get_mode(int volt_id);

#ifdef __VXWORKS__
int bsp_pmu_hi6551_init(void);
#endif
/*dr��ؽӿڣ�ֻ��Acoreʹ��*/
#if defined(__KERNEL__) || defined(__FASTBOOT__)
/*****************************************************************************
 �� �� ��  : bsp_hi6551_dr_is_enabled
 ��������  : ��ѯĳ·����Դ�Ƿ�����
 �������  : dr_id:����Դid��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��ע˵��  : ֻ��Acore�ṩ�ú���ʵ�֣�
*****************************************************************************/
int bsp_hi6551_dr_is_enabled(int dr_id);

/*****************************************************************************
 �� �� ��  : hi6551_dr_bre_time_set
 ��������  : ����dr�ĺ���ʱ��(��������������������������ʱ��)
 �������  : dr_id:Ҫ���õĵ���Դ���;dr_bre_time_st:����ʱ������ṹ��;
            û���ҵ����õ�ʱ�䣬������Ϊ����
 �������  : ��
 �� �� ֵ  : ���óɹ�����ʧ��
 ���ú���  :
 ��ע˵��  : ��Ӧ�Ĵ���ֻ������ʱ��Ĺ��ܣ�����Ҫ������
*****************************************************************************/
int hi6551_dr_bre_time_set(dr_id_e dr_id, DR_BRE_TIME *dr_bre_time_st);

/*****************************************************************************
* �� �� ��  : bsp_hi6551_dr_enable
* ��������  : ��ĳ·����Դ��
* �������  : dr_id:����Դid��
* �������  : ��
* ����ֵ��    �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6551_dr_enable(int dr_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_dr_disable
* ��������  :�ر�ĳ·����Դ��
* �������  :dr_id:����Դid��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6551_dr_disable(int dr_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_dr_get_current
* ��������  :��ȡĳ·����Դ������
* �������  :dr_id:����Դid��
* �������  :��
* ����ֵ��   ��ѹֵ����λ��uV��
*
*****************************************************************************/
int bsp_hi6551_dr_get_current(int dr_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_dr_set_current
* ��������  :����ĳ·����Դ������
* �������  :dr_id:����Դid�ţ�min_uA�����õ���С������max_uA����������
* �������  :selector�������õĵ�ѹ�ǵڼ���
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6551_dr_set_current(int dr_id, int min_uA, int max_uA, unsigned *selector);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_dr_list_current
* ��������  :��ѯĳ·����Դָ����λ������
* �������  :dr_id:����Դid�ţ�selector��Ҫ��ѯ�ĵ�λ��
* �������  :��
* ����ֵ��   ����ѯ�ĵ���Դָ����λ�ĵ���ֵ����λ��uA��
*
*****************************************************************************/
int bsp_hi6551_dr_list_current(int dr_id, unsigned selector);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_dr_set_mode
* ��������  :����ĳ·����Դģʽ��
* �������  :dr_id:����Դid�ţ�mode�����õ�ģʽ��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6551_dr_set_mode(int dr_id, dr_mode_e mode);
/*****************************************************************************
* �� �� ��  : bsp_hi6551_dr_get_mode
* ��������  :��ȡĳ·����Դģʽ��
* �������  :dr_id:����Դid�ţ�
* �������  :��
* ����ֵ��   ����Դ��ǰģʽ
*
*****************************************************************************/
dr_mode_e bsp_hi6551_dr_get_mode(int dr_id);
#endif
#endif

#ifdef CONFIG_PMIC_HI6559

/* ���������Դ */
#define PMIC_HI6559_BUCK0  0
#define PMIC_HI6559_BUCK3  1
#define PMIC_HI6559_BUCK4  2
#define PMIC_HI6559_BUCK5  3
#define PMIC_HI6559_BUCK6  4
#define PMIC_HI6559_LDO01  5
#define PMIC_HI6559_LDO03  6
#define PMIC_HI6559_LDO06  7
#define PMIC_HI6559_LDO07  8
#define PMIC_HI6559_LDO08  9
#define PMIC_HI6559_LDO09  10
#define PMIC_HI6559_LDO10  11
#define PMIC_HI6559_LDO11  12
#define PMIC_HI6559_LDO12  13
#define PMIC_HI6559_LDO13  14
#define PMIC_HI6559_LDO14  15
#define PMIC_HI6559_LDO22  16
#define PMIC_HI6559_LDO23  17
#define PMIC_HI6559_LDO24  18
#define PMIC_HI6559_LVS07  19
#define PMIC_HI6559_LVS09  20

/* ���ڲ����Ϸ��Լ�� */
#define PMIC_HI6559_VOLT_MIN        PMIC_HI6559_BUCK0
#define PMIC_HI6559_VOLT_MAX        PMIC_HI6559_LVS09
#define PMIC_HI6559_BUCK_MAX        PMIC_HI6559_BUCK6
#define PMIC_HI6559_LDO_MIN         PMIC_HI6559_LDO01
#define PMIC_HI6559_LDO_MAX         PMIC_HI6559_LDO24
#define PMIC_HI6559_LVS_MIN         PMIC_HI6559_LVS07
#define PMIC_HI6559_LVS_MAX         PMIC_HI6559_LVS09

/*DR���*/
#define PMIC_HI6559_DR01     1
#define PMIC_HI6559_DR02     2
#define PMIC_HI6559_DR03     3
#define PMIC_HI6559_DR04     4
#define PMIC_HI6559_DR05     5

/* ��ѹԴ�ĵ�ѹֵ��λ���� */
#define HI6559_VOLT_LIST_NUM 16

typedef struct
{
    u16 enable_reg_addr;
    u16 disable_reg_addr;

    u16 is_enabled_reg_addr;
    u16 voltage_reg_addr;

    u16 eco_follow_reg_addr;
    u16 eco_force_reg_addr;

    u8 enable_bit_offset;
    u8 disable_bit_offset;
    u8 is_enabled_bit_offset;
    u8 voltage_bit_mask;

    u8 voltage_bit_offset;
    u8 voltage_nums;
    u8 eco_follow_bit_offset;
    u8 eco_force_bit_offset;

    int voltage_list[HI6559_VOLT_LIST_NUM];
}PMIC_HI6559_VLTGS_ATTR;

typedef struct
{
    unsigned long   magic_start;
    PMIC_HI6559_VLTGS_ATTR    hi6559_volt_attr[PMIC_HI6559_VOLT_MAX + 1];
    unsigned long   magic_end;
}PMIC_HI6559_VLTGS_TABLE;

/*��������*/
/*****************************************************************************
* �� �� ��  :bsp_hi6559_reg_write
* ��������  :дhi6559�Ĵ�����
* �������  :addr:Ҫ�����ļĴ�����ַ��value:Ҫд���ֵ
* �������  :��
* ����ֵ��   ��
*
*****************************************************************************/
void bsp_hi6559_reg_write( u16 addr, u8 value);
/*****************************************************************************
* �� �� ��  : bsp_hi6559_reg_read
* ��������  :��hi6559�Ĵ�����
* �������  :addr:Ҫ�����ļĴ�����ַ��pValue:������ֵ
* �������  :��
* ����ֵ��   ��
*
*****************************************************************************/
void  bsp_hi6559_reg_read( u16 addr, u8 *pValue);
/*****************************************************************************
* �� �� ��  : bsp_hi6559_reg_show
* ��������  :��ʾhi6559�Ĵ������ݡ�
* �������  :addr:Ҫ�����ļĴ�����ַ;
* �������  :������ֵ
* ����ֵ��   ��
*
*****************************************************************************/
int  bsp_hi6559_reg_show( u16 addr);
/*****************************************************************************
* �� �� ��  : bsp_hi6559_reg_write_mask
* ��������  :�����Ĵ�����ĳ��bit��
* �������  :addr:Ҫ�����ļĴ�����ַ��value:Ҫд���ֵ;
*               mask:
* �������  :��
* ����ֵ��   ��
*
*****************************************************************************/
void bsp_hi6559_reg_write_mask(u16 addr, u8 value, u8 mask);
/*****************************************************************************
* �� �� ��  : bsp_hi6559_volt_is_enabled
* ��������  :��ѯĳ·��ѹԴ�Ƿ�����
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   ��0��������0���ر�
*
*****************************************************************************/
int bsp_hi6559_volt_is_enabled(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6559_volt_enable
* ��������  :��ĳ·��ѹԴ��
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6559_volt_enable(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6559_volt_disable
* ��������  :�ر�ĳ·��ѹԴ��
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6559_volt_disable(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6559_volt_get_voltage
* ��������  :��ȡĳ·��ѹԴ��ѹ��
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   ��ѹֵ����λ��uV��
*
*****************************************************************************/
int bsp_hi6559_volt_get_voltage(int volt_id);
/*****************************************************************************
* �� �� ��  : bsp_hi6559_volt_set_voltage
* ��������  :����ĳ·��ѹԴ��ѹ��
* �������  :volt_id:��ѹԴid�ţ�min_uV�����õ���С��ѹ��max_uV������ѹ��
* �������  :selector�������õĵ�ѹ�ǵڼ���
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6559_volt_set_voltage(int volt_id, int min_uV, int max_uV, unsigned *selector);
/*****************************************************************************
* �� �� ��  : bsp_hi6559_volt_list_voltage
* ��������  :��ѯĳ·��ѹԴָ����λ��ѹ��
* �������  :volt_id:��ѹԴid�ţ�selector��Ҫ��ѯ�ĵ�λ��
* �������  :��
* ����ֵ��   ����ѯ�ĵ�ѹԴָ����λ�ĵ�ѹֵ����λ��uV��
*
*****************************************************************************/
int bsp_hi6559_volt_list_voltage(int volt_id, unsigned selector);
/*****************************************************************************
* �� �� ��  : bsp_hi6559_volt_set_mode
* ��������  :����ĳ·��ѹԴģʽ��
* �������  :volt_id:��ѹԴid�ţ�mode�����õ�ģʽ��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6559_volt_set_mode(int volt_id, pmu_mode_e mode);
/*****************************************************************************
* �� �� ��  : bsp_hi6559_volt_get_mode
* ��������  :��ȡĳ·��ѹԴ��ѹ��
* �������  :volt_id:��ѹԴid�ţ�
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
pmu_mode_e bsp_hi6559_volt_get_mode(int volt_id);

#ifdef __VXWORKS__
int bsp_pmu_hi6559_init(void);
s32 bsp_pmu_hi6559_apt_enable(void);
s32 bsp_pmu_hi6559_apt_disable(void);
s32 bsp_pmu_hi6559_apt_status_get(void);
#endif
/*dr��ؽӿڣ�ֻ��Acoreʹ��*/
#if defined(__KERNEL__) || defined(__FASTBOOT__)
/*****************************************************************************
 �� �� ��  : bsp_hi6559_dr_is_enabled
 ��������  : ��ѯĳ·����Դ�Ƿ�����
 �������  : dr_id:����Դid��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��ע˵��  : ֻ��Acore�ṩ�ú���ʵ�֣�
*****************************************************************************/
int bsp_hi6559_dr_is_enabled(int dr_id);

/*****************************************************************************
* �� �� ��  : bsp_hi6559_dr_enable
* ��������  : ��ĳ·����Դ��
* �������  : dr_id:����Դid��
* �������  : ��
* ����ֵ��    �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6559_dr_enable(int dr_id);

/*****************************************************************************
* �� �� ��  : bsp_hi6559_dr_disable
* ��������  :�ر�ĳ·����Դ��
* �������  :dr_id:����Դid��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6559_dr_disable(int dr_id);

/*****************************************************************************
* �� �� ��  : bsp_hi6559_dr_get_current
* ��������  :��ȡĳ·����Դ������
* �������  :dr_id:����Դid��
* �������  :��
* ����ֵ��   ��ѹֵ����λ��uV��
*
*****************************************************************************/
int bsp_hi6559_dr_get_current(int dr_id);

/*****************************************************************************
* �� �� ��  : bsp_hi6559_dr_set_current
* ��������  :����ĳ·����Դ������
* �������  :dr_id:����Դid�ţ�min_uA�����õ���С������max_uA����������
* �������  :selector�������õĵ�ѹ�ǵڼ���
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6559_dr_set_current(int dr_id, int min_uA, int max_uA, unsigned *selector);

/*****************************************************************************
* �� �� ��  : bsp_hi6559_dr_list_current
* ��������  :��ѯĳ·����Դָ����λ������
* �������  :dr_id:����Դid�ţ�selector��Ҫ��ѯ�ĵ�λ��
* �������  :��
* ����ֵ��   ����ѯ�ĵ���Դָ����λ�ĵ���ֵ����λ��uA��
*
*****************************************************************************/
int bsp_hi6559_dr_list_current(int dr_id, unsigned selector);

/*****************************************************************************
* �� �� ��  : bsp_hi6559_dr_set_mode
* ��������  :����ĳ·����Դģʽ��
* �������  :dr_id:����Դid�ţ�mode�����õ�ģʽ��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_hi6559_dr_set_mode(int dr_id, dr_mode_e mode);

/*****************************************************************************
* �� �� ��  : bsp_hi6559_dr_get_mode
* ��������  :��ȡĳ·����Դģʽ��
* �������  :dr_id:����Դid�ţ�
* �������  :��
* ����ֵ��   ����Դ��ǰģʽ
*
*****************************************************************************/
dr_mode_e bsp_hi6559_dr_get_mode(int dr_id);
#endif /* #if defined(__KERNEL__) || defined(__FASTBOOT__)  */
#endif /* #ifdef CONFIG_PMIC_HI6559 */

/*PMU�汾�ź�*/
#ifdef CONFIG_PMIC_HI6559
#define BSP_PMU_V100 0x10
#else
#define BSP_PMU_V210 0x21
#define BSP_PMU_V220 0x22
#define BSP_PMU_V230 0x23
#define BSP_PMU_V240 0x24
#endif

/*�ж�ddr�Ƿ񱻸�д��ħ����*/
#define SHM_PMU_VOLTTABLE_MAGIC_START_DATA   0xc7c7c7c7
#define SHM_PMU_VOLTTABLE_MAGIC_END_DATA     0xa6a6a6a6

/*�����붨��*/
#define BSP_PMU_ERROR   -1
#define BSP_PMU_OK      0
#define BSP_PMU_NO_PMIC      0x2001/*ϵͳû��PMUоƬ*/
#define BSP_PMU_PARA_ERROR      0x2002/*��Ч����ֵ*/
#define BSP_PMU_VOLTTABLE_ERROR      0x2003/*DDR����д��table���ƻ�*/

#define PMU_INVAILD_ADDR 0/*��ַ����Чֵ*/
#define PMU_INVAILD_DATA 0/*���ݵ���Чֵ*/
#define PMU_INVAILD_OFFSET 0/*ƫ�Ƶ���Чֵ*/

/* �������exc_hi6559.c/irq_hi6559.c�ж��õ� */
#define HI6559_NP_RECORD_REG_NUM                    10      /* ���µ�״̬��¼�Ĵ����������Ĵ���0x15~0x1E */

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/(sizeof((a)[0])))
#endif

typedef enum  _pmic_id_e
{
#ifdef CONFIG_PMIC_HI6451
    PMIC_HI6451 ,
#endif
#ifdef CONFIG_PMIC_HI6551
    PMIC_HI6551 ,/*HI6551�е�Դ��ecoģʽ:ǿ�ƽ���ecoģʽ*/
#endif
#ifdef CONFIG_PMIC_HI6559
    PMIC_HI6559 ,/*HI6559�е�Դ��ecoģʽ:ǿ�ƽ���ecoģʽ*/
#endif

#ifdef CONFIG_PASTAR
	PMIC_HI6561 ,
#endif
#ifdef CONFIG_PASTAR_V200
	PMIC_HI6562 ,
#endif
    PMIC_BUTTOM
}pmic_id_e;


/*om log*/
/*PMU om log ö������ */
typedef enum  _pmu_om_log_e
{
    PMU_OM_LOG_START = 0,   /*PMU om log*/
    PMU_OM_LOG_RESET,
    PMU_OM_LOG_EXC,       /*wifi clk */
    PMU_OM_LOG_END
}pmu_om_log_e;
#define PMU_OM_LOG            "/modem_log/log/pmu_om.log"
/*debug*/


/*��������*/
#if defined(__CMSIS_RTOS)
int bsp_pmu_suspend(void);
int bsp_pmu_resume(void);
int bsp_pmu_sdio_suspend(void);
int bsp_pmu_sdio_resume(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* end #define _BSP_PMU_H_*/
