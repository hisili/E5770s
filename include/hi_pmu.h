/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_pmu.h */
/* Version       : 2.0 */
/* Created       : 2013-05-14*/
/* Last Modified : */
/* Description   :  The C union definition file for the module pmu*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_PMU_H__
#define __HI_PMU_H__

/*
 * Project: hi
 * Module : pmu
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    pmu �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_PMU_VERSION_OFFSET                             (0x0) /* �汾�Ĵ����� */
#define    HI_PMU_IRQ1_OFFSET                                (0x1) /* �ж�1�Ĵ����� */
#define    HI_PMU_IRQ2_OFFSET                                (0x2) /* �ж�2�Ĵ����� */
#define    HI_PMU_IRQ3_OFFSET                                (0x3) /* �ж�3�Ĵ����� */
#define    HI_PMU_STATUS1_OFFSET                             (0x4) /* ״̬��־1�Ĵ����� */
#define    HI_PMU_STATUS2_OFFSET                             (0x5) /* ״̬��־2�Ĵ����� */
#define    HI_PMU_STATUS3_OFFSET                             (0x6) /* ״̬��־3�Ĵ����� */
#define    HI_PMU_STATUS4_OFFSET                             (0x7) /* ״̬��־4�Ĵ����� */
#define    HI_PMU_STATUS5_OFFSET                             (0x8) /* ״̬��־5�Ĵ����� */
#define    HI_PMU_IRQM1_OFFSET                               (0x9) /* �ж�����1�Ĵ����� */
#define    HI_PMU_IRQM2_OFFSET                               (0xA) /* �ж�����2�Ĵ����� */
#define    HI_PMU_IRQM3_OFFSET                               (0xB) /* �ж�����3�Ĵ����� */
#define    HI_PMU_ONOFF1_OFFSET                              (0xC) /* ���ؿ���1�Ĵ����� */
#define    HI_PMU_ONOFF2_OFFSET                              (0xD) /* ���ؿ���2�Ĵ����� */
#define    HI_PMU_ONOFF3_OFFSET                              (0xE) /* ���ؿ���3�Ĵ����� */
#define    HI_PMU_ONOFF4_OFFSET                              (0xF) /* ���ؿ���4�Ĵ����� */
#define    HI_PMU_ONOFF5_OFFSET                              (0x10) /* ���ؿ���5�Ĵ����� */
#define    HI_PMU_ONOFF6_OFFSET                              (0x11) /* ���ؿ���6�Ĵ����� */
#define    HI_PMU_ONOFF7_OFFSET                              (0x12) /* ���ؿ���7�Ĵ����� */
#define    HI_PMU_ONOFF8_OFFSET                              (0x13) /* ���ؿ���8�Ĵ����� */
#define    HI_PMU_ONOFF9_OFFSET                              (0x14) /* ���ؿ���9�Ĵ����� */
#define    HI_PMU_LDO_SWICH1_OFFSET                          (0x15) /* LDO����ֱͨģʽ����1�Ĵ����� */
#define    HI_PMU_LDO_SWITCH2_OFFSET                         (0x16) /* LDO����ֱͨģʽ����2�Ĵ����� */
#define    HI_PMU_SET_BUCK1_OFFSET                           (0x17) /* BUCK1��ѹ���ڼĴ����� */
#define    HI_PMU_SET_BUCK2_OFFSET                           (0x18) /* BUCK2��ѹ���ڼĴ����� */
#define    HI_PMU_SET_BUCK3_OFFSET                           (0x19) /* BUCK3��ѹ���ڼĴ����� */
#define    HI_PMU_SET_BUCK4_OFFSET                           (0x1A) /* BUCK4��ѹ���ڼĴ����� */
#define    HI_PMU_SET_BUCK5_OFFSET                           (0x1B) /* BUCK5��ѹ���ڼĴ����� */
#define    HI_PMU_SET_BUCK6_OFFSET                           (0x1C) /* BUCK6��ѹ���ڼĴ����� */
#define    HI_PMU_BUCK1_ADJ1_OFFSET                          (0x1D) /* BUCK1����1�Ĵ����� */
#define    HI_PMU_BUCK1_ADJ2_OFFSET                          (0x1E) /* BUCK1����2�Ĵ����� */
#define    HI_PMU_BUCK2_ADJ1_OFFSET                          (0x1F) /* BUCK2����1�Ĵ����� */
#define    HI_PMU_BUCK2_ADJ2_OFFSET                          (0x20) /* BUCK2����2�Ĵ����� */
#define    HI_PMU_BUCK3_ADJ1_OFFSET                          (0x21) /* BUCK3����1�Ĵ����� */
#define    HI_PMU_BUCK3_ADJ2_OFFSET                          (0x22) /* BUCK3����2�Ĵ����� */
#define    HI_PMU_BUCK1_2_4_ADJ2_OFFSET                      (0x23) /* BUCK1_2_4���ڼĴ����� */
#define    HI_PMU_BUCK5_ADJ_OFFSET                           (0x24) /* BUCK5����2�Ĵ����� */
#define    HI_PMU_BUCK6_ADJ1_OFFSET                          (0x25) /* BUCK6����1�Ĵ����� */
#define    HI_PMU_BUCK6_ADJ2_OFFSET                          (0x26) /* BUCK6����2�Ĵ����� */
#define    HI_PMU_BUCK4_5_FREQ_OFFSET                        (0x27) /* BUCK4_5Ƶ�ʵ��ڼĴ����� */
#define    HI_PMU_BUCK4_COMP_ADJ_OFFSET                      (0x28) /* BUCK4�ȶ��Ե��ڼĴ����� */
#define    HI_PMU_BUCK5_COMP_ADJ_OFFSET                      (0x29) /* BUCK5�ȶ��Ե��ڼĴ����� */
#define    HI_PMU_SET_LDO1_OFFSET                            (0x2A) /* LDO1��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO2_OFFSET                            (0x2B) /* LDO2��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO3_OFFSET                            (0x2C) /* LDO3��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO4_OFFSET                            (0x2D) /* LDO4��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO5_OFFSET                            (0x2E) /* LDO5��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO6_OFFSET                            (0x2F) /* LDO6��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO7_OFFSET                            (0x30) /* LDO7��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO8_OFFSET                            (0x31) /* LDO8��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO9_OFFSET                            (0x32) /* LDO9��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO10_OFFSET                           (0x33) /* LDO10��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO11_OFFSET                           (0x34) /* LDO11��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO13_OFFSET                           (0x35) /* LDO13��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO14_OFFSET                           (0x36) /* LDO14��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO15_OFFSET                           (0x37) /* LDO15��ѹ���ڼĴ����� */
#define    HI_PMU_SET_LDO17_OFFSET                           (0x38) /* LDO17��ѹ���ڼĴ����� */
#define    HI_PMU_SET_OTP_OFFSET                             (0x39) /* OTP���üĴ����� */
#define    HI_PMU_DR1_MODE_OFFSET                            (0x3A) /* DR1���ƼĴ����� */
#define    HI_PMU_DR2_MODE_OFFSET                            (0x3B) /* DR2���ƼĴ����� */
#define    HI_PMU_DR3_MODE_OFFSET                            (0x3C) /* DR3���ƼĴ����� */
#define    HI_PMU_FLASH_PERIOD_OFFSET                        (0x3D) /* DR��˸ģʽ���ڵ��ڼĴ����� */
#define    HI_PMU_FLASH_ON_OFFSET                            (0x3E) /* DR��˸ģʽ����ʱ����ڼĴ����� */
#define    HI_PMU_PERIPH_CTRL1_OFFSET                        (0x3F) /* ��������1�Ĵ����� */
#define    HI_PMU_NO_PWR_IRQ1_OFFSET                         (0x40) /* IRQ1���µ���Ϣ�洢�Ĵ��� */
#define    HI_PMU_NO_PWR_IRQ2_OFFSET                        (0x41) /* IRQ2���µ���Ϣ�洢�Ĵ����� */
#define    HI_PMU_NO_PWR_IRQ3_OFFSET                         (0x42) /* IRQ3f���µ��µ���Ϣ�洢�Ĵ����� */
#define    HI_PMU_NO_PWR_REG_RWC_OFFSET                      (0x43) /* ���µ��¼�Ĵ��� */
#define    HI_PMU_NO_RWR_REG_RW_OFFSET                       (0x44) /* LEAK_CTL���µ�Ĵ����� */
#define    HI_PMU_ANA_IN_OFFSET                              (0x46) /* PMUģ�ⲿ������Ĵ����� */
#define    HI_PMU_RESERVED0_OFFSET                           (0x47) /* ����0�Ĵ����� */
#define    HI_PMU_RESERVED1_OFFSET                           (0x48) /* ����1�Ĵ����� */
#define    HI_PMU_RESERVED2_OFFSET                           (0x49) /* ����2�Ĵ����� */
#define    HI_PMU_CLIM_ADJ_OFFSET                            (0x4A) /* �������������ڼĴ����� */
#define    HI_PMU_LIT_CUR_SET_OFFSET                         (0x4B) /* ����ֵ���üĴ����� */
#define    HI_PMU_OTP_CTRL_OFFSET                            (0x4C) /* OTP�����źżĴ����� */
#define    HI_PMU_OTP_PDIN_OFFSET                            (0x4D) /* OTPд��ֵ�Ĵ����� */
#define    HI_PMU_OTP_PDOB0_OFFSET                           (0x4E) /* OTP����ֵ0�Ĵ����� */
#define    HI_PMU_OTP_PDOB1_OFFSET                           (0x4F) /* OTP����ֵ1�Ĵ����� */
#define    HI_PMU_OTP_PDOB2_OFFSET                           (0x50) /* OTP����ֵ2�Ĵ����� */
#define    HI_PMU_OTP_PDOB3_OFFSET                           (0x51) /* OTP����ֵ3�Ĵ����� */
#define    HI_PMU_BANDGAP_REG_OFFSET                         (0x52) /* BANDGAP�Ĵ����� */
#define    HI_PMU_DET_SD_LEVEL_CMD_OFFSET                    (0x53) /* SD����ƽ���ָ��Ĵ����� */
#define    HI_PMU_DET_SD_LEVEL_STATUS_OFFSET                 (0x54) /* SD����ƽ���״̬�Ĵ����� */
#define    HI_PMU_RTCDR0_OFFSET                              (0x55) /* rtcdr[7:0]�Ĵ����� */
#define    HI_PMU_RTCDR1_OFFSET                              (0x56) /* rtcdr[15:8]�Ĵ����� */
#define    HI_PMU_RTCDR2_OFFSET                              (0x57) /* rtcdr[23:16]�Ĵ����� */
#define    HI_PMU_RTCDR3_OFFSET                              (0x58) /* rtcdr[31:24]�Ĵ����� */
#define    HI_PMU_RTCLR0_OFFSET                              (0x59) /* rtclr[7:0]�Ĵ����� */
#define    HI_PMU_RTCLR1_OFFSET                              (0x5A) /* rtclr[15:8]�Ĵ����� */
#define    HI_PMU_RTCLR2_OFFSET                              (0x5B) /* rtclr[23:16]�Ĵ����� */
#define    HI_PMU_RTCLR3_OFFSET                              (0x5C) /* rtclr[31:24]�Ĵ����� */
#define    HI_PMU_RTCCTRL_OFFSET                             (0x5D) /* rtcctrl�Ĵ����� */
#define    HI_PMU_RTCMRA0_OFFSET                             (0x5E) /* rtcmra[7:0]�Ĵ����� */
#define    HI_PMU_RTCMRA1_OFFSET                             (0x5F) /* rtcmra[15:8]�Ĵ����� */
#define    HI_PMU_RTCMRA2_OFFSET                             (0x60) /* rtcmra[23:16]�Ĵ����� */
#define    HI_PMU_RTCMRA3_OFFSET                             (0x61) /* rtcmra[31:24]�Ĵ����� */
#define    HI_PMU_RTCMRB0_OFFSET                             (0x62) /* rtcmrb[7:0]�Ĵ����� */
#define    HI_PMU_RTCMRB1_OFFSET                             (0x63) /* rtcmrb[15:8]�Ĵ����� */
#define    HI_PMU_RTCMRB2_OFFSET                             (0x64) /* rtcmrb[23:16]�Ĵ����� */
#define    HI_PMU_RTCMRB3_OFFSET                             (0x65) /* rtcmrb[31:24]�Ĵ����� */
#define    HI_PMU_RTCMRC0_OFFSET                             (0x66) /* rtcmrc[7:0]�Ĵ����� */
#define    HI_PMU_RTCMRC1_OFFSET                             (0x67) /* rtcmrc[15:8]�Ĵ����� */
#define    HI_PMU_RTCMRC2_OFFSET                             (0x68) /* rtcmrc[23:16]�Ĵ����� */
#define    HI_PMU_RTCMRC3_OFFSET                             (0x69) /* rtcmrc[31:24]�Ĵ����� */
#define    HI_PMU_RTC_ADJ1_OFFSET                            (0x6A) /* rtc_adj[7:0]�Ĵ����� */
#define    HI_PMU_RTC_ADJ2_OFFSET                            (0x6B) /* rtc_adj[15:8]�Ĵ����� */
#define    HI_PMU_RESERVED3_OFFSET                           (0x6C) /* ����3�Ĵ����� */
#define    HI_PMU_RESERVED4_OFFSET                           (0x6D) /* ����4�Ĵ����� */
#define    HI_PMU_RESERVED5_OFFSET                           (0x6E) /* ����5�Ĵ����� */
#define    HI_PMU_RESERVED6_OFFSET                           (0x6F) /* ����6�Ĵ����� */
#define    HI_PMU_RESERVED7_OFFSET                           (0x70) /* ����6�Ĵ����� */
#define    HI_PMU_RESERVED8_OFFSET                           (0x71) /* ����6�Ĵ����� */
#define    HI_PMU_ONOFF10_OFFSET                             (0x72) /* ���ؿ���10�Ĵ����� */
#define    HI_PMU_DR1_BRE_CTRL_OFFSET                        (0x73) /* DR1���ƼĴ��� */
#define    HI_PMU_DR1_TIM_CONF1_OFFSET                       (0x74) /* DR1��������ʱ������ */
#define    HI_PMU_DR1_TIM_CONF2_OFFSET                       (0x75) /* DR1��������ʱ������ */
#define    HI_PMU_DR2_BRE_CTRL_OFFSET                        (0x76) /* DR2���ƼĴ��� */
#define    HI_PMU_DR2_TIM_CONF1_OFFSET                       (0x77) /* DR2��������ʱ������ */
#define    HI_PMU_DR2_TIM_CONF2_OFFSET                       (0x78) /* DR2��������ʱ������ */
#define    HI_PMU_DR3_BRE_CTRL_OFFSET                        (0x79) /* DR3���ƼĴ��� */
#define    HI_PMU_DR3_TIM_CONF1_OFFSET                       (0x7A) /* DR3��������ʱ������ */
#define    HI_PMU_DR3_TIM_CONF2_OFFSET                       (0x7B) /* DR3��������ʱ������ */
#define    HI_PMU_NO_PWR_RSVED1_OFFSET                       (0x7E) /* ����1���µ�Ĵ����� */
#define    HI_PMU_NO_PWR_RSVED2_OFFSET                       (0x7F) /* ����2���µ�Ĵ����� */

/********************************************************************************/
/*    pmu �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    version                    : 8; /* [7..0] �汾�Ĵ�������ʾ�汾ΪV110�� */
    } bits;
    unsigned int    u32;
}HI_PMU_VERSION_T;    /* �汾�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otmp_d3r                   : 1; /* [0..0] 0:�޴��жϣ�1��otmp ���¶ȳ����趨��ֵ��Ĭ��125�ȣ��жϡ� */
        unsigned int    hreset_n_f                 : 1; /* [1..1] 0:�޴��жϣ�1:������RESETIN_N��λ�ж� �� */
        unsigned int    pwr_ini_2p7_d3f            : 1; /* [2..2] 0:�޴��жϣ�1:pwr_ini��ѹ����2.7V�жϡ� */
        unsigned int    pwr_ini_6p0_d3r            : 1; /* [3..3] 0���޴��жϣ�1:pwr_ini3����ѹ����6V�жϣ�3ms˲̬��ѹ���� */
        unsigned int    pwr_ini_6p0_d100r          : 1; /* [4..4] 0���޴��жϣ�1:pwr_ini ����ѹ����6V�жϣ�100ms��ʱ��ѹ)�� */
        unsigned int    pwron_d1sr                 : 1; /* [5..5] 0:�޴��жϣ�1:PWRON��������1s�жϡ� */
        unsigned int    pwron_d20f                 : 1; /* [6..6] 0:�޴��жϣ�1:PWRON�����ͷ�20ms�ж� �� */
        unsigned int    pwron_d20r                 : 1; /* [7..7] 0:�޴��жϣ�1:PWRON��������20ms�жϡ� */
    } bits;
    unsigned int    u32;
}HI_PMU_IRQ1_T;    /* �ж�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_r                      : 1; /* [0..0] 0:�޴��жϣ�1:��ʾ������һ��BUCK����LDO���أ�CPU�ӵ��Ժ�Ҫȥ�鿴�����״̬�Ĵ�����������һ�����ء� */
        unsigned int    vin_ldo_l_2p5_d3r          : 1; /* [1..1] 0���޴��жϣ�1��vin_ldo_l��ѹ����2.5V�жϡ� */
        unsigned int    usb_4p0_d3f                : 1; /* [2..2] 0���޴��жϣ�1��usb ��ѹ����4V ��usb�γ��жϡ� */
        unsigned int    usb_4p0_d3r                : 1; /* [3..3] 0���޴��жϣ�1��usb ��ѹ����4V ��usb�����жϡ� */
        unsigned int    usb_6p0_d3r                : 1; /* [4..4] 0:�޴��жϣ�1:usb��ѹ����6.0V  �жϡ� */
        unsigned int    vbus_4p0_d3f               : 1; /* [5..5] 0:�޴��жϣ�1:Vbus��ѹ����4.0V �жϡ� */
        unsigned int    vbus_6p0_d3r               : 1; /* [6..6] 0:�޴��жϣ�1:Vbus��ѹ����6.0V �ж� �� */
        unsigned int    vbus_6p0_d100r             : 1; /* [7..7] 0:�޴��жϣ�1:Vbus��ѹ����6.0V��ʱ���ж� �� */
    } bits;
    unsigned int    u32;
}HI_PMU_IRQ2_T;    /* �ж�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    alarm_on_expanda           : 1; /* [0..0] 0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_expandb           : 1; /* [1..1] 0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_expandc           : 1; /* [2..2] 0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_IRQ3_T;    /* �ж�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ldo2                   : 1; /* [0..0] 0��LDO2��������أ�1: LDO2������ء� */
        unsigned int    ocp_ldo1                   : 1; /* [1..1] 0��LDO1��������أ�1: LDO1������ء� */
        unsigned int    ocp_buck6                  : 1; /* [2..2] 0��BUCK6��������أ�1: BUCK6������ء� */
        unsigned int    ocp_buck5                  : 1; /* [3..3] 0��BUCK5��������أ�1: BUCK5������� �� */
        unsigned int    ocp_buck4                  : 1; /* [4..4] 0��BUCK4��������أ�1: BUCK4������� �� */
        unsigned int    ocp_buck3                  : 1; /* [5..5] 0��BUCK3��������أ�1: BUCK3������� �� */
        unsigned int    ocp_buck2                  : 1; /* [6..6] 0��BUCK2��������أ�1: BUCK2������ء� */
        unsigned int    ocp_buck1                  : 1; /* [7..7] 0��BUCK1��������أ�1: BUCK1������ء� */
    } bits;
    unsigned int    u32;
}HI_PMU_STATUS1_T;    /* ״̬��־1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ldo10                  : 1; /* [0..0] 0��LDO10��������أ�1: LDO10������ء� */
        unsigned int    ocp_ldo9                   : 1; /* [1..1] 0��LDO9��������أ�1: LDO9������ء� */
        unsigned int    ocp_ldo8                   : 1; /* [2..2] 0��LDO8��������أ�1: LDO8������ء� */
        unsigned int    ocp_ldo7                   : 1; /* [3..3] 0��LDO7��������أ�1: LDO7������ء� */
        unsigned int    ocp_ldo6                   : 1; /* [4..4] 0��LDO6��������أ�1: LDO6������ء� */
        unsigned int    ocp_ldo5                   : 1; /* [5..5] 0��LDO5��������أ�1: LDO5������ء� */
        unsigned int    ocp_ldo4                   : 1; /* [6..6] 0��LDO4��������أ�1: LDO4������ء� */
        unsigned int    ocp_ldo3                   : 1; /* [7..7] 0��LDO3��������أ�1: LDO3������� �� */
    } bits;
    unsigned int    u32;
}HI_PMU_STATUS2_T;    /* ״̬��־2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ldo15                  : 1; /* [0..0] 0��LDO15��������أ�1: LDO15������ء� */
        unsigned int    ocp_ldo14                  : 1; /* [1..1] 0��LDO14��������أ�1: LDO14������ء� */
        unsigned int    ocp_ldo13                  : 1; /* [2..2] 0��LDO13��������أ�1: LDO13������ء� */
        unsigned int    ocp_ldo12                  : 1; /* [3..3] 0��LDO12��������أ�1: LDO12������ء� */
        unsigned int    ocp_ldo11                  : 1; /* [4..4] 0��LDO11��������أ�1: LDO11������ء� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_STATUS3_T;    /* ״̬��־3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pwr_ini_2p7_d3f            : 1; /* [0..0] 0��pwr_iniû�г���2.7V��1��pwr_ini����2.7V�� */
        unsigned int    pwr_ini_6p0_d3r            : 1; /* [1..1] 0��pwr_iniû�г���6V��1��pwr_ini����6V�� */
        unsigned int    osc_state                  : 1; /* [2..2] 0��OSC����ʱ��û�о�����1��OSC����ʱ���Ѿ�������ʱ���л���ɡ� */
        unsigned int    otmp_d3r                   : 1; /* [3..3] 0:�޴��жϣ�1��otmp ���¶ȳ����趨��ֵ��Ĭ��125�ȣ��ж� �� */
        unsigned int    pwron_d20rf                : 1; /* [4..4] 0��PWRON����ǰ״̬Ϊ�͵�ƽ��1:PWRON����ǰ״̬Ϊ�ߵ�ƽ (pwronΪpwron_n�ķ��򣬱�ʾ��������)�� */
        unsigned int    alarm_on_expenda           : 1; /* [5..5] 0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    alarm_on_expendb           : 1; /* [6..6] 0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    alarm_on_expendc           : 1; /* [7..7] 0:����ʱ��û����1������ʱ�䵽�� */
    } bits;
    unsigned int    u32;
}HI_PMU_STATUS4_T;    /* ״̬��־4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    usb_4p0_d3rf               : 1; /* [0..0] 0��usb_4p0û�г���4V��1��vbus_4p0����4V�� */
        unsigned int    usb_6p0_d3r                : 1; /* [1..1] 0��usb_6p0û�г���6V��1��vbus_6p0����6V�� */
        unsigned int    vbus_4p0_d3f               : 1; /* [2..2] 0��vbus_4p0û�г���4V��1��vbus_4p0����4V�� */
        unsigned int    vbus_6p0_d3r               : 1; /* [3..3] 0��vbus_6p0û�г���6V��1��vbus_6p0����6V�� */
        unsigned int    vin_ldo_l_2p5_d3r          : 1; /* [4..4] 0��vin_ldo_l��ѹû�г���2.5V��1��vin_ldo_l��ѹ����2.5V�� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_STATUS5_T;    /* ״̬��־5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otmp_d3rm                  : 1; /* [0..0] 0��ʹ���жϣ�1������otmp_d3�жϡ� */
        unsigned int    hreset_n_fm                : 1; /* [1..1] 0:ʹ���жϣ�1:�����ж�hreset_n_f�� */
        unsigned int    pwr_ini_2p7_d3fm           : 1; /* [2..2] 0:ʹ���жϣ�1:�����ж�pwr_ini_2p7_d3f�� */
        unsigned int    pwr_ini_6p0_d3rm           : 1; /* [3..3] 0: ʹ���жϣ�1:�����ж�pwr_ini_6p0_d3r�� */
        unsigned int    pwr_ini_6p0_d100rm         : 1; /* [4..4] 0:ʹ���жϣ�1:�����ж�pwr_ini_6p0_d100r�� */
        unsigned int    pwron_d1srm                : 1; /* [5..5] 0:ʹ���жϣ�1:�����ж�pwron_d1sr�� */
        unsigned int    pwron_d20fm                : 1; /* [6..6] 0:ʹ���жϣ�1:�����ж�pwron_d20f�� */
        unsigned int    pwron_d20rm                : 1; /* [7..7] 0:ʹ���жϣ�1:�����ж�pwron_d20r�� */
    } bits;
    unsigned int    u32;
}HI_PMU_IRQM1_T;    /* �ж�����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_rm                     : 1; /* [0..0] 0��ʹ���жϣ�1������ocp_r�жϡ� */
        unsigned int    vin_ldo_l_2p5_d3rm         : 1; /* [1..1] 0��ʹ���жϣ�1������vin_ldo_1_2p5_d3r�жϡ� */
        unsigned int    usb_4p0_d3fm               : 1; /* [2..2] 0:ʹ���жϣ�1:�����ж�usb_4p0_d3f �жϡ� */
        unsigned int    usb_4p0_d3rm               : 1; /* [3..3] 0:ʹ���жϣ�1:�����ж�usb_4p0_d3r�жϡ� */
        unsigned int    usb_6p0_d3rm               : 1; /* [4..4] 0:ʹ���жϣ�1:�����ж�usb_6p0_d3r�жϡ� */
        unsigned int    vbus_4p0_d3fm              : 1; /* [5..5] 0:ʹ���жϣ�1:�����ж�vbus_4p0_d3f �� */
        unsigned int    vbus_6p0_d3rm              : 1; /* [6..6] 0:ʹ���жϣ�1:�����ж�vbus_6p0_d3r�� */
        unsigned int    vbus_6p0_d100rm            : 1; /* [7..7] 0:ʹ���жϣ�1:�����ж�vbus_6p0_d10r�� */
    } bits;
    unsigned int    u32;
}HI_PMU_IRQM2_T;    /* �ж�����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    alarm_on_expendam          : 1; /* [0..0] 0��ʹ���жϣ�1������alarm_on_expend�жϡ� */
        unsigned int    alarm_on_expendbm          : 1; /* [1..1] 0��ʹ���жϣ�1������alarm_on_expend�жϡ� */
        unsigned int    alarm_on_expendcm          : 1; /* [2..2] 0��ʹ���жϣ�1������alarm_on_expend�жϡ� */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_IRQM3_T;    /* �ж�����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_eco_ldo4_int            : 1; /* [0..0] 0��LDO4����ģʽ�����1��LDO4����ģʽ����� */
        unsigned int    en_ldo4_int                : 1; /* [1..1] 0���ر�LDO4��1:����LDO4�� */
        unsigned int    en_eco_ldo3_int            : 1; /* [2..2] 0��LDO3����ģʽ�����1��LDO3����ģʽ����� */
        unsigned int    en_ldo3_int                : 1; /* [3..3] 0���ر�LDO3��1:����LDO3�� */
        unsigned int    en_eco_ldo2_int            : 1; /* [4..4] 0��LDO2����ģʽ�����1��LDO2����ģʽ����� */
        unsigned int    en_ldo2_int                : 1; /* [5..5] 0���ر�LDO2��1:����LDO2�� */
        unsigned int    en_eco_ldo1_int            : 1; /* [6..6] 0��LDO1����ģʽ�����1��LDO1����ģʽ����� */
        unsigned int    en_ldo1_int                : 1; /* [7..7] 0���ر�LDO1�� 1:����LDO1 �� */
    } bits;
    unsigned int    u32;
}HI_PMU_ONOFF1_T;    /* ���ؿ���1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_eco_ldo8_int            : 1; /* [0..0] 0��LDO8����ģʽ�����1��LDO8����ģʽ����� */
        unsigned int    en_ldo8_int                : 1; /* [1..1] 0���ر�LDO8��1:����LDO8�� */
        unsigned int    en_eco_ldo7_int            : 1; /* [2..2] 1��LDO7����ģʽ�����              0��LDO7����ģʽ����� */
        unsigned int    en_ldo7_int                : 1; /* [3..3] 0���ر�LDO7��1:����LDO7�� */
        unsigned int    en_eco_ldo6_int            : 1; /* [4..4] 0��LDO6����ģʽ�����1��LDO6����ģʽ����� */
        unsigned int    en_ldo6_int                : 1; /* [5..5] 0:�ر�LDO6��1:����LDO6�� */
        unsigned int    en_eco_ldo5_int            : 1; /* [6..6] 0��LDO5����ģʽ�����1��LDO5����ģʽ����� */
        unsigned int    en_ldo5_int                : 1; /* [7..7] 0���ر�LDO5��1:����LDO5�� */
    } bits;
    unsigned int    u32;
}HI_PMU_ONOFF2_T;    /* ���ؿ���2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_eco_ldo12_int           : 1; /* [0..0] 0��LDO12����ģʽ�����1��LDO12����ģʽ����� */
        unsigned int    en_ldo12_int               : 1; /* [1..1] 0���ر�LDO12��1:����LDO12�� */
        unsigned int    en_eco_ldo11_int           : 1; /* [2..2] 0��LDO11����ģʽ�����1��LDO11����ģʽ����� */
        unsigned int    en_ldo11_int               : 1; /* [3..3] 0���ر�LDO11��1:����LDO11�� */
        unsigned int    en_eco_ldo10_int           : 1; /* [4..4] 0��LDO10����ģʽ�����1��LDO10����ģʽ����� */
        unsigned int    en_ldo10_int               : 1; /* [5..5] 0���ر�LDO10��1������LDO10�� */
        unsigned int    en_eco_ldo9_int            : 1; /* [6..6] 0��LDO9����ģʽ�����1��LDO9����ģʽ����� */
        unsigned int    en_ldo9_int                : 1; /* [7..7] 0���ر�LDO9��1������LDO9�� */
    } bits;
    unsigned int    u32;
}HI_PMU_ONOFF3_T;    /* ���ؿ���3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_eco_ldo15_int           : 1; /* [0..0] 0��LDO15����ģʽ�����1��LDO15����ģʽ����� */
        unsigned int    en_ldo15_int               : 1; /* [1..1] 0���ر�LDO15��1:����LDO15�� */
        unsigned int    en_eco_ldo14_int           : 1; /* [2..2] 0��LDO14����ģʽ�����1��LDO14����ģʽ����� */
        unsigned int    en_ldo14_int               : 1; /* [3..3] 0���ر�LDO14��1:����LDO14�� */
        unsigned int    en_eco_ldo13_int           : 1; /* [4..4] 0��LDO13����ģʽ�����1��LDO13����ģʽ����� */
        unsigned int    en_ldo13_int               : 1; /* [5..5] 0���ر�LDO13��1:����LDO13�� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_ONOFF4_T;    /* ���ؿ���4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_2                 : 1; /* [0..0] ������ */
        unsigned int    en_buck4_int               : 1; /* [1..1] 0���ر�BUCK4��   1������BUCK4�� */
        unsigned int    reserved_1                 : 1; /* [2..2] ������ */
        unsigned int    en_buck3_int               : 1; /* [3..3] 0���ر�BUCK3��   1������BUCK3�� */
        unsigned int    reserved_0                 : 1; /* [4..4] ������ */
        unsigned int    en_buck2_int               : 1; /* [5..5] 0���ر�BUCK2��   1������BUCK2 �� */
        unsigned int    en_buck1_int               : 2; /* [7..6] 00�����֣�01������BUCK1�� 10: �ر�BUCK1��    11�����֡� */
    } bits;
    unsigned int    u32;
}HI_PMU_ONOFF5_T;    /* ���ؿ���5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 2; /* [1..0] ������ */
        unsigned int    en_buck1_eno6_int          : 1; /* [2..2] 0��BUCK1���ز���ENO6���ƣ�1��BUCK1������ENO6���ơ� */
        unsigned int    en_buck6_ldo_int           : 1; /* [3..3] 0��Buck6��PMU����͹���ģʽʱ��������LDOģʽ��1��Buck6�ڵ͹���ģʽ�½���LDOģʽ�� */
        unsigned int    en_eno6_eco_int            : 1; /* [4..4] ����eno6����sleep���ܼĴ�����0�����ܿ��ƣ�1��eno6�ܹ�����buck��ldo����sleepģʽ�� */
        unsigned int    en_buck6_int               : 1; /* [5..5] 0���ر�BUCK6��  1������BUCK6�� */
        unsigned int    reserved_0                 : 1; /* [6..6] ������ */
        unsigned int    en_buck5_int               : 1; /* [7..7] 0���ر�BUCK5��   1������BUCK5�� */
    } bits;
    unsigned int    u32;
}HI_PMU_ONOFF6_T;    /* ���ؿ���6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otmp_off_ctrl              : 1; /* [0..0] 0�����£�150�棩���ػ���1������(150��)�ػ��� */
        unsigned int    en_32k2                    : 1; /* [1..1] 0�� �ر� C32K_OUT2 ʱ�������1�� C32K_OUT2 ʱ�����ʹ�ܡ� */
        unsigned int    en_32k1                    : 1; /* [2..2] 0�� �ر� C32K_OUT1 ʱ�������1�� C32K_OUT1 ʱ�����ʹ�ܡ� */
        unsigned int    set_tmp                    : 2; /* [4..3] �¶ȱ���ģ�鱨���¶����á�00:  105�棻01:  115�棻10:  125�棻11:  135�棻                       Ĭ������Ϊ125�档 */
        unsigned int    en_tmp                     : 1; /* [5..5] 0:THSD���±���ģ��رգ�1:THSD���±���ģ�鿪���� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_ONOFF7_T;    /* ���ؿ���7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    vbus_4p0_ctrl              : 1; /* [0..0] 0������vbus<4V��⣻1:������vbus<4V��⡣ */
        unsigned int    vbus_6p0_ctrl              : 1; /* [1..1] 0������vbus>6V��⣻1:������vbus>6V��⡣ */
        unsigned int    pwr_ini_2p7_ctrl           : 1; /* [2..2] 0������pwr_ini<2.7V��⣻1:������pwr_ini<2.7V��⡣ */
        unsigned int    pwr_ini_6p0_ctrl           : 1; /* [3..3] 0������pwr_ini>6V��⣻1:������pwr_ini>6.0��⡣ */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_ONOFF8_T;    /* ���ؿ���8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_vbus_4p0                : 1; /* [0..0] 0���ر�Vbus<4.0V����·��1:����Vbus<4.0V����·�� */
        unsigned int    en_vbus_6p0                : 1; /* [1..1] 0���ر�Vbus>6V����·��1:����Vbus>6V����·�� */
        unsigned int    en_pini_2p7                : 1; /* [2..2] 0:�ر� power_ini<2.7V����·��1:����power_ini>2.7V����·�� */
        unsigned int    en_pini_6p0                : 1; /* [3..3] 0: power_ini 6.0V���ģ���·�رգ�1:power_ini 6.0V���ģ���·������ */
        unsigned int    en_vin_ldo_l_2p5           : 1; /* [4..4] 0: VIN_LDO_L 2.5V���ģ���·�رգ�1:VIN_LDO_L 2.5V���ģ���·������ */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_ONOFF9_T;    /* ���ؿ���9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_ldo8_sw                 : 1; /* [0..0] 0:LDO8ֱͨģʽ�رգ�1:LDO8ֱͨģʽ������ */
        unsigned int    en_ldo7_sw                 : 1; /* [1..1] 0:LDO7ֱͨģʽ�رգ�1:LDO7ֱͨģʽ������ */
        unsigned int    en_ldo6_sw                 : 1; /* [2..2] 0:LDO6ֱͨģʽ�رգ�1:LDO6ֱͨģʽ������ */
        unsigned int    en_ldo5_sw                 : 1; /* [3..3] 0:LDO5ֱͨģʽ�رգ�1:LDO5ֱͨģʽ������ */
        unsigned int    en_ldo4_sw                 : 1; /* [4..4] 0:LDO4ֱͨģʽ�رգ�1:LDO4ֱͨģʽ������ */
        unsigned int    en_ldo3_sw                 : 1; /* [5..5] 0:LDO3ֱͨģʽ�رգ�1:LDO3ֱͨģʽ������ */
        unsigned int    en_ldo2_sw                 : 1; /* [6..6] 0:LDO2ֱͨģʽ�رգ�1:LDO2ֱͨģʽ������. */
        unsigned int    en_ldo1_sw                 : 1; /* [7..7] 0: LDO1ֱͨģʽ�رգ�1:LDO1ֱͨģʽ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_LDO_SWICH1_T;    /* LDO����ֱͨģʽ����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_ldo15_sw                : 1; /* [0..0] 0:LDO15ֱͨģʽ�رգ�1:LDO15ֱͨģʽ������ */
        unsigned int    en_ldo14_sw                : 1; /* [1..1] 0:LDO14ֱͨģʽ�رգ�1:LDO14ֱͨģʽ������ */
        unsigned int    en_ldo13_sw                : 1; /* [2..2] 0:LDO13ֱͨģʽ�رգ�1:LDO13ֱͨģʽ������ */
        unsigned int    en_ldo12_sw                : 1; /* [3..3] 0:LDO12ֱͨģʽ�رգ�1:LDO12ֱͨģʽ������ */
        unsigned int    en_ldo11_sw                : 1; /* [4..4] 0:LDO11ֱͨģʽ�رգ�1:LDO11ֱͨģʽ������ */
        unsigned int    en_ldo10_sw                : 1; /* [5..5] 0:LDO10ֱͨģʽ�رգ�1:LDO10ֱͨģʽ������ */
        unsigned int    en_ldo9_sw                 : 1; /* [6..6] 0:LDO9ֱͨģʽ�رգ�1:LDO9ֱͨģʽ������ */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_LDO_SWITCH2_T;    /* LDO����ֱͨģʽ����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    vset_buck1                 : 4; /* [3..0] BUCK1 ��ѹ���ڡ�0x0: 0.80 V ��0x1: 0.90 V ��0x2: 1.00 V ��0x3: 1.05 V �� 0x4: 1.10 V ��0x5: 1.15 V ��                   0x6: 1.30 V ��0x7: 1.80 V ��0x8: 1.85 V ��                       */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_BUCK1_T;    /* BUCK1��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_buck2                 : 4; /* [3..0] BUCK2�ĵ�ѹ���� ��              0x0: 0.90 V ��0x1: 0.95 V ��0x2: 1.00 V ��0x3: 1.05 V ��0x4: 1.10 V ��0x5: 1.15 V ��0x6: 1.20 V ��0x7: 1.30 V �� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_BUCK2_T;    /* BUCK2��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_buck3                 : 4; /* [3..0] BUCK3 ��ѹ���ڡ�0x0: 1.20 V ��0x1: 1.50 V ��0x2: 1.75 V ��0x3: 1.80 V ��0x4: 1.85 V ��0x5: 1.90 V ��0x6: 2.50 V ��0x7: 2.85 V ��                     */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_BUCK3_T;    /* BUCK3��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_buck4                 : 3; /* [2..0] BUCK4 ��ѹ���ڡ�0x0: 2.90 V ��0x1: 3.00 V ��0x2: 3.10 V ��0x3: 3.20 V ��0x4: 3.30 V ��0x5: 3.40 V ��0x6: 3.50 V ��0x7: 3.60 V �� */
        unsigned int    pdm_sel                    : 1; /* [3..3] ʹ��ATP�����źš�0��ATP������Ч��1��ATP������Ч�� */
        unsigned int    buck4_mode_sel_int         : 2; /* [5..4] BUCK4����ģʽѡ��        00:pwm��pfm�Զ��л���01��������pwmģʽ��10��������pfmģʽ��             Ĭ������ΪPWMģʽ�� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_BUCK4_T;    /* BUCK4��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_buck5                 : 3; /* [2..0] BUCK5��ѹ���ڡ�                     0x0:1.20V ��                         0x1:1.30V ��                        0x2:1.50V ��                         0x3:1.80V ��                        0x4:2.20V ��                         0x5:2.25V ��                        0x6:2.80V ��                         0x7:2.85V ��                                                 */
        unsigned int    buck5_mode_sel_int         : 2; /* [4..3] BUCK5����ģʽѡ��             00:pwm��pfm�Զ��л���01��������pwmģʽ��10��������pfmģʽ��              Ĭ������ΪPWMģʽ�� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_BUCK5_T;    /* BUCK5��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_buck6                 : 4; /* [3..0] BUCK6 ��ѹ���ڡ�0x0: 1.20 V ��0x1: 1.25 V ��0x2: 1.30 V ��0x3: 1.35 V ��0x4: 1.80 V ��0x5: 1.85 V ��0x6: 2.50 V ��0x7: 2.55 V ��                      0x8: 3.00 V ��0x9: 3.05 V ��0xa: 3.10 V ��0xb: 3.15 V ��                      0xc: 3.20 V ��0xd: 3.25 V ��0xe: 3.30 V ��0xf: 3.45 V ��                       */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_BUCK6_T;    /* BUCK6��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_d_buck1                : 1; /* [0..0] BUCK1��������ʹ�ܡ�1���������ܹرգ�0���������ܿ����� */
        unsigned int    adj_clx_buck1              : 1; /* [1..1] BUCK1��Ƶ���ݵ��ڡ� */
        unsigned int    adj_rlx_buck1              : 3; /* [4..2] BUCK1��Ƶ������ڡ� */
        unsigned int    icmp_buck1                 : 2; /* [6..5] BUCK1�Ƚ����������ڡ� */
        unsigned int    sleep_buck1_int            : 1; /* [7..7] 0��BUCK1�˳�sleepģʽ��1:BUCK1����sleepģʽ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK1_ADJ1_T;    /* BUCK1����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reg_dr_buck1               : 2; /* [1..0] BUCK1��regulator��̬��Χ���ڡ� */
        unsigned int    reg_r_buck1                : 2; /* [3..2] BUCK1��regulator����������ڡ� */
        unsigned int    reg_c_buck1                : 1; /* [4..4] BUCK1��regulator�������ݵ��ڡ� */
        unsigned int    en_reg_buck1               : 1; /* [5..5] BUCK1 regulator����ʹ�ܡ�0��regulator���ܿ�����1:regulator���ܹرա� */
        unsigned int    dt_sel_buck1               : 1; /* [6..6] BUCK1����ʱ����ڡ� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK1_ADJ2_T;    /* BUCK1����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_d_buck2                : 1; /* [0..0] BUCK2��������ʹ�ܡ�0���������ܿ�����1���������ܹرա� */
        unsigned int    adj_clx_buck2              : 1; /* [1..1] BUCK2��Ƶ���ݵ��ڡ� */
        unsigned int    adj_rlx_buck2              : 3; /* [4..2] BUCK2��Ƶ������ڡ� */
        unsigned int    icmp_buck2                 : 2; /* [6..5] BUCK2�Ƚ����������ڡ� */
        unsigned int    sleep_buck2_int            : 1; /* [7..7] 0��BUCK2�˳�sleepģʽ��1:BUCK2����sleepģʽ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK2_ADJ1_T;    /* BUCK2����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reg_dr_buck2               : 2; /* [1..0] BUCK2��regulator��̬��Χ���ڡ� */
        unsigned int    reg_r_buck2                : 2; /* [3..2] BUCK2��regulator����������ڡ� */
        unsigned int    reg_c_buck2                : 1; /* [4..4] BUCK2��regulator�������ݵ��ڡ� */
        unsigned int    en_reg_buck2               : 1; /* [5..5] BUCK2 regulator����ʹ�ܡ�0��regulator���ܿ�����1:regulator���ܹرա� */
        unsigned int    dt_sel_buck2               : 1; /* [6..6] BUCK2����ʱ����ڡ� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK2_ADJ2_T;    /* BUCK2����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_d_buck3                : 1; /* [0..0] BUCK3��������ʹ�ܡ�0���������ܿ�����1���������ܹرա� */
        unsigned int    adj_clx_buck3              : 1; /* [1..1] BUCK3��Ƶ���ݵ��ڡ� */
        unsigned int    adj_rlx_buck3              : 3; /* [4..2] BUCK3��Ƶ������ڡ� */
        unsigned int    icmp_buck3                 : 2; /* [6..5] BUCK3�Ƚ����������ڡ� */
        unsigned int    sleep_buck3_int            : 1; /* [7..7] 0��BUCK3�˳�sleepģʽ��1:BUCK3����sleepģʽ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK3_ADJ1_T;    /* BUCK3����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reg_dr_buck3               : 2; /* [1..0] BUCK3��regulator��̬��Χ���ڡ� */
        unsigned int    reg_r_buck3                : 2; /* [3..2] BUCK3��regulator����������ڡ� */
        unsigned int    reg_c_buck3                : 1; /* [4..4] BUCK3��regulator�������ݵ��ڡ� */
        unsigned int    en_reg_buck3               : 1; /* [5..5] BUCK3 regulator����ʹ�ܡ�0��regulator���ܿ�����1:regulator���ܹرա� */
        unsigned int    dt_sel_buck3               : 1; /* [6..6] BUCK3����ʱ����ڡ� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK3_ADJ2_T;    /* BUCK3����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_3a_p                   : 1; /* [0..0] BUCK4���������á�0������������㣻1����������㡣 */
        unsigned int    reserved                   : 1; /* [1..1] ������ */
        unsigned int    ccm4_ctr                   : 1; /* [2..2] buck4��ǿ������ģʽ���ܡ�0��ǿ������ģʽ���ܿ�����1��ǿ������ģʽ���ܹرա� */
        unsigned int    sleep_buck4_int            : 1; /* [3..3] 0:BUCK4�˳�sleepģʽ��1��BUCK4����sleepģʽ�� */
        unsigned int    slope_ctrl_buck4           : 1; /* [4..4] ����buck4��б�²�������0��������б�²�����1������б�²����� */
        unsigned int    offset_trim_start_int      : 1; /* [5..5] 0������offset_trim�͵�ƽ��1: ����offset_trim�ߵ�ƽ�� */
        unsigned int    offset_trim_reg            : 1; /* [6..6] offsetУ׼�Ĵ������ơ� */
        unsigned int    offset_cancel_en           : 1; /* [7..7] buck1_2��offset cancel ����ʹ�ܡ�0: ʹ��offsetУ׼���ܣ�1����ʹ��offsetУ׼���ܡ� */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK1_2_4_ADJ2_T;    /* BUCK1_2_4���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ccm5_ctr                   : 1; /* [0..0] buck5��ǿ������ģʽ���ܡ�0��ǿ������ģʽ���ܿ�����1��ǿ������ģʽ���ܹرա� */
        unsigned int    sleep_buck5_int            : 1; /* [1..1] 0:BUCK5�˳�sleepģʽ��1��BUCK5����sleepģʽ�� */
        unsigned int    slope_ctrl_buck5           : 1; /* [2..2] ����buck5��б�²�������0��������б�²�����1������б�²����� */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK5_ADJ_T;    /* BUCK5����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_d_buck6                : 1; /* [0..0] BUCK6��������ʹ�ܡ�0���������ܿ�����1���������ܹرա� */
        unsigned int    adj_clx_buck6              : 1; /* [1..1] BUCK6��Ƶ���ݵ��ڡ� */
        unsigned int    adj_rlx_buck6              : 3; /* [4..2] BUCK6��Ƶ������ڡ� */
        unsigned int    icmp_buck6                 : 2; /* [6..5] BUCK6�Ƚ����������ڡ� */
        unsigned int    sleep_buck6_int            : 1; /* [7..7] 0��BUCK6�˳�sleepģʽ��1:BUCK6����sleepģʽ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK6_ADJ1_T;    /* BUCK6����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reg_dr_buck6               : 2; /* [1..0] BUCK6��regulator��̬��Χ���ڡ� */
        unsigned int    reg_r_buck6                : 2; /* [3..2] BUCK6��regulator����������ڡ� */
        unsigned int    reg_c_buck6                : 1; /* [4..4] BUCK6��regulator�������ݵ��ڡ� */
        unsigned int    en_reg_buck6               : 1; /* [5..5] BUCK6 regulator����ʹ�ܡ�0��regulator���ܿ�����1:regulator���ܹرա� */
        unsigned int    dt_sel_buck6               : 1; /* [6..6] BUCK6����ʱ����ڡ� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK6_ADJ2_T;    /* BUCK6����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck_frq_adj               : 5; /* [4..0] BUCK4_5Ƶ�ʵ��ڡ�Ĭ��Ƶ��Ϊ�趨ֵΪ        01101 �� */
        unsigned int    ocp_shield_p               : 1; /* [5..5] BUCK4��BUCK5�����������ܡ�0�������������ܿ�����1�������������ܹرա� */
        unsigned int    shortn                     : 1; /* [6..6] buck4��·�������ܡ�0����·����������1����·�����رա� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK4_5_FREQ_T;    /* BUCK4_5Ƶ�ʵ��ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_comp_adj             : 8; /* [7..0] BUCK4�ȶ��Ե��ڼĴ����� [7]: ����EA����ߵ�λ��λ�㡣1��1.8V��0��2.6V��[6]: ����PFM�����ıȽ�����ƫֵ������1��1uA��0��0.5uA��[5]: ����PFM����ģʽ��еķ�ֵ�����㡣0�����ӷ�ֵ������1��Ĭ��ֵ��[4��0]�����ڵ���EA�Ŀ絼�Ե����ĵ��衣 */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK4_COMP_ADJ_T;    /* BUCK4�ȶ��Ե��ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_comp_adj             : 8; /* [7..0] BUCK5�ȶ��Ե��ڼĴ����� [7]: ����EA����ߵ�λ��λ�㡣1��1.8V��0��2.6V��[6]: ����PFM�����ıȽ�����ƫֵ������1��1uA��0��0.5uA��[5]: ����PFM����ģʽ��еķ�ֵ�����㡣0�����ӷ�ֵ������1��Ĭ��ֵ��[4��0]���ڵ���EA�Ŀ絼�Լ������ĵ��衣 */
    } bits;
    unsigned int    u32;
}HI_PMU_BUCK5_COMP_ADJ_T;    /* BUCK5�ȶ��Ե��ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo1                  : 3; /* [2..0] LDO1 ��ѹ���ڡ�                    0x0: 1.10V��                         0x1: 1.20V��                        0x2: 1.80 V��0x3: 2.20 V��0x4: 2.50V��0x5: 2.60 V��0x6: 2.80 V��0x7:2.85 V��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO1_T;    /* LDO1��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo2                  : 3; /* [2..0] LDO2 ��ѹ���ڡ�                    0x0: 1.10V��                         0x1: 1.20V��                        0x2: 1.80 V��0x3: 2.20 V��0x4: 2.50V��0x5: 2.60 V��0x6: 2.80 V��0x7:2.85 V��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO2_T;    /* LDO2��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo3                  : 3; /* [2..0] LDO3 ��ѹ���ڡ�                    0x0: 1.10V ��                         0x1: 1.20V ��                        0x2: 1.80 V ��0x3: 2.20 V ��0x4: 2.50V ��0x5: 2.60 V ��0x6: 2.80 V ��0x7:2.85 V ��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO3_T;    /* LDO3��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo4                  : 3; /* [2..0] LDO4 ��ѹ���ڡ�                    0x0: 1.10V��                         0x1: 1.20V��                        0x2: 1.80 V��0x3: 2.20 V��0x4: 2.50V��0x5: 2.60 V��0x6: 2.80 V��0x7:2.85 V��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO4_T;    /* LDO4��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo5                  : 3; /* [2..0] LDO5 ��ѹ���ڡ�                    0x0: 1.10V��                         0x1: 1.20V��                        0x2: 1.80 V��0x3: 1.85 V��0x4: 2.20V��0x5: 2.25 V��0x6: 2.50 V��0x7:2.60 V��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO5_T;    /* LDO5��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo6                  : 3; /* [2..0] LDO6 ��ѹ����                    0x0: 2.20V��                         0x1: 2.30V��                        0x2:2.4V��0x3: 2.5 V��0x4: 2.6V��0x5: 2.8 V��0x6:2.85 V��                 */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO6_T;    /* LDO6��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo7                  : 3; /* [2..0] LDO7 ��ѹ���ڡ�                    0x0: 1.20V��                         0x1: 1.80V��                        0x2: 2.50 V��0x3: 2.80 V��0x4: 2.85V��0x5: 3.0 V��0x6: 3.3 V��0x7:3.5 V��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO7_T;    /* LDO7��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo8                  : 3; /* [2..0] LDO8 ��ѹ���ڡ�                    0x0: 0.90V��                         0x1: 1.00V��                        0x2: 1.10 V��0x3: 1.15 V��0x4: 1.20V��0x5: 1.25 V��0x6: 1.30 V��0x7:1.50 V��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO8_T;    /* LDO8��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo9                  : 3; /* [2..0] LDO9 ��ѹ���ڡ�                  0x0: 0.90V��                         0x1: 1.00V��                        0x2: 1.10 V��0x3: 1.15 V��0x4: 1.20V��0x5: 1.25 V��0x6: 1.30 V��0x7:1.50 V��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO9_T;    /* LDO9��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo10                 : 3; /* [2..0] LDO10 ��ѹ����                    0x0: 1.20V��                         0x1: 1.80V��                        0x2: 2.50 V��0x3: 2.80 V��0x4: 2.85V��0x5: 2.90 V��0x6: 3.00 V��0x7:3.30 V��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO10_T;    /* LDO10��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo11                 : 3; /* [2..0] LDO11 ��ѹ���ڡ�                    0x0: 1.20V��                         0x1: 1.25V��                        0x2: 1.8 V��0x3: 1.85 V��0x4: 3.0V��0x5: 3.05 V��                   */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO11_T;    /* LDO11��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo13                 : 3; /* [2..0] LDO13 ��ѹ����  ��                  0x0: 1.10V��                         0x1: 1.20V��                        0x2: 1.80 V��0x3: 2.20 V��0x4: 2.50V��0x5: 2.60 V��0x6: 2.80 V��0x7: 3V��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO13_T;    /* LDO13��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo14                 : 3; /* [2..0] LDO14 ��ѹ���ڡ�                    0x0: 1.10V��                         0x1: 1.20V��                        0x2: 1.80 V��0x3: 2.20 V��0x4: 2.50V��0x5: 2.60 V��0x6: 2.80 V��0x7:2.85 V��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO14_T;    /* LDO14��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo15                 : 3; /* [2..0] LDO15 ��ѹ���ڡ�                    0x0: 1.10V��                         0x1: 1.20V��                        0x2: 1.80 V��0x3: 2.20 V��0x4: 2.50V��0x5: 2.60 V��0x6: 2.80 V��0x7:2.85 V��                     */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO15_T;    /* LDO15��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo17                 : 2; /* [1..0] LDO17 ��ѹ���� ��                    */
        unsigned int    reserved                   : 6; /* [7..2] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_LDO17_T;    /* LDO17��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    otp_por_pulse              : 1; /* [0..0] 0�����������壻1����otp_read_mask=1ʱ������һ��31000ns�ĸߵ�ƽ���塣 */
        unsigned int    otp_read_mask              : 1; /* [1..1] 0����otp_por�źſ���OTP�Ķ�������1:��otp_por_pulse�źſ���OTP�Ķ������� */
        unsigned int    otp_pwe_pulse              : 1; /* [2..2] 0�����������壻1����otp_write_mask=1ʱ������һ��310us�ĸߵ�ƽ���塣 */
        unsigned int    otp_write_mask             : 1; /* [3..3] 0:��otp_pwe�źſ���OTP��д������1:��otp_pwe_pulse�źſ���OTP��д������ */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_SET_OTP_T;    /* OTP���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr1                   : 3; /* [2..0] DR1�������ڡ�                                    000: 3  mA��001: 6  mA��010: 9  mA��011: 12 mA��100: 15 mA��101: 18 mA��110: 21 mA��111: 24 mA�� */
        unsigned int    en_dr1_int                 : 1; /* [3..3] 0:  �ر�DR1��1: ����DR1  �� */
        unsigned int    dr1_mode                   : 1; /* [4..4] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR1����ģʽ�� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR1_MODE_T;    /* DR1���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr2                   : 3; /* [2..0] DR2�������ڡ�                                    000: 3  mA��001: 6  mA��010: 9  mA��011: 12 mA��100: 15 mA��101: 18 mA��110: 21 mA��111: 24 mA�� */
        unsigned int    en_dr2_int                 : 1; /* [3..3] 0:  �ر�DR2��1: ����DR2�� */
        unsigned int    dr2_mode                   : 1; /* [4..4] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR2����ģʽ��    */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR2_MODE_T;    /* DR2���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr3                   : 3; /* [2..0] DR3�������ڡ�                                    000: 3  mA��001: 6  mA��010: 9  mA��011: 12 mA��100: 15 mA��101: 18 mA��110: 21 mA��111: 24 mA�� */
        unsigned int    en_dr3_int                 : 1; /* [3..3] 0:  �ر�DR3��1: ����DR3 �� */
        unsigned int    dr3_mode                   : 1; /* [4..4] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR3����ģʽ��  */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR3_MODE_T;    /* DR3���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_period               : 8; /* [7..0] ��˸����T = ����ֵ *31.25ms�� */
    } bits;
    unsigned int    u32;
}HI_PMU_FLASH_PERIOD_T;    /* DR��˸ģʽ���ڵ��ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_on                   : 8; /* [7..0] ����ʱ��t =����ֵ *7.8125ms�� */
    } bits;
    unsigned int    u32;
}HI_PMU_FLASH_ON_T;    /* DR��˸ģʽ����ʱ����ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_auto_off               : 1; /* [0..0] 0����֧��OCPģ�飨LDO|BUCK���Զ��رգ�1��֧��OCPģ�飨LDO|BUCK���Զ��رա� */
        unsigned int    ocp_shut_down_ctrl         : 1; /* [1..1] 0: OCP�Զ��ر�ģʽ�£�Ĭ��ģ�飨BUCK1/2/3/6��LDO1/2/7/8/9/12������OCPоƬ���Զ��ػ���1: OCP�Զ��ر�ģʽ�£�Ĭ��ģ�飨BUCK1/2/3/6��LDO1/2/7/8/9/12������OCPоƬ�Զ��ػ���ע��OCP���Զ��ض�ģʽ�£���λ�޹��ܡ� */
        unsigned int    ocp_deb_sel                : 2; /* [3..2] ocpȥ��ʱ�䡣00��500us��01��1ms��10��2ms��11��4ms�� */
        unsigned int    en_buck_ocp_debounce       : 1; /* [4..4] 0��BUCK OCP�����ز�ȥ����1��BUCK OCP������ȥ���� */
        unsigned int    en_ldo_ocp_debounce        : 1; /* [5..5] 0��LDO OCP�����ز�ȥ����1��LDO OCP������ȥ���� */
        unsigned int    lim_mode_int               : 1; /* [6..6] ������׼���á�0����׼����pre_ref ��1����׼����ref(�ϵ�Ĭ�ϱ���Ϊ1)�� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_PERIPH_CTRL1_T;    /* ��������1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    hrst_otmp_d3               : 1; /* [0..0] 0:�޴��жϣ�1��otmp ���¶ȳ����趨��ֵ��Ĭ��125�ȣ��жϡ� */
        unsigned int    hrst_hreset_n_f            : 1; /* [1..1] 0:�޴��жϣ�1:������RESETIN_N��λ�ж� �� */
        unsigned int    hrst_pwr_ini_2p7_d3f       : 1; /* [2..2] 0:�޴��жϣ�1:pwr_ini��ѹ����2.7V�жϡ� */
        unsigned int    hrst_pwr_ini_6p0_d3r       : 1; /* [3..3] 0���޴��жϣ�1:pwr_ini3����ѹ����6V�жϣ�3ms˲̬��ѹ���� */
        unsigned int    hrst_pwr_ini_6p0_d100r     : 1; /* [4..4] 0���޴��жϣ�1:pwr_ini ����ѹ����6V�жϣ�100ms��ʱ��ѹ)�� */
        unsigned int    hrst_pwron_d1sr            : 1; /* [5..5] 0:�޴��жϣ�1:PWRON��������1s�жϡ� */
        unsigned int    hrst_pwron_d20f            : 1; /* [6..6] 0:�޴��жϣ�1:PWRON�����ͷ�20ms�ж� �� */
        unsigned int    hrst_pwron_d20r            : 1; /* [7..7] 0:�޴��жϣ�1:PWRON��������20ms�жϡ� */
    } bits;
    unsigned int    u32;
}HI_PMU_NO_PWR_IRQ1_T;    /* IRQ1���µ���Ϣ�洢�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    hrst_ocp_total             : 1; /* [0..0] 0:�޴��жϣ�1:��ʾ������һ��BUCK����LDO���أ�CPU�ӵ��Ժ�Ҫȥ�鿴�����״̬�Ĵ�����������һ�����ء� */
        unsigned int    hrst_vin_ldo_l_2p5_d3r     : 1; /* [1..1] 0���޴��жϣ�1��vin_ldo_l��ѹ����2.5V�жϡ� */
        unsigned int    hrst_usb_4p0_d3f           : 1; /* [2..2] 0���޴��жϣ�1��usb ��ѹ����4V ��usb�γ��жϡ� */
        unsigned int    hrst_usb_4p0_d3r           : 1; /* [3..3] 0���޴��жϣ�1��usb ��ѹ����4V ��usb�����жϡ� */
        unsigned int    hrst_usb_6p0_d3r           : 1; /* [4..4] 0:�޴��жϣ�1:usb��ѹ����6.0V  �жϡ� */
        unsigned int    hrst_vbus_4p0_d3f          : 1; /* [5..5] 0:�޴��жϣ�1:Vbus��ѹ����4.0V �жϡ� */
        unsigned int    hrst_vbus_6p0_d3r          : 1; /* [6..6] 0:�޴��жϣ�1:Vbus��ѹ����6.0V �ж� �� */
        unsigned int    hrst_vbus_6p0_d100r        : 1; /* [7..7] 0:�޴��жϣ�1:Vbus��ѹ����6.0V��ʱ���жϡ� */
    } bits;
    unsigned int    u32;
}HI_PMU_NO_PWR__IRQ2_T;    /* IRQ2���µ���Ϣ�洢�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    hrst_alarm_on_expenda      : 1; /* [0..0] 0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    hrst_alarm_on_expendb      : 1; /* [1..1] 0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    hrst_alarm_on_expendc      : 1; /* [2..2] 0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_NO_PWR_IRQ3_T;    /* IRQ3f���µ��µ���Ϣ�洢�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otmp150_d3r                : 1; /* [0..0] ֻ�������ᱻRESETIN_N��λ���¶ȳ���150����Ϣ��¼�ڷ��µ�Ĵ����� */
        unsigned int    ilim_sht_pro_d3r           : 1; /* [1..1] 0:������·û�з�����·��1:������·������· */
        unsigned int    reserved                   : 6; /* [7..2] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_NO_PWR_REG_RWC_T;    /* ���µ��¼�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    leak_ctl                   : 1; /* [0..0] ע�⣺���ź�Ҫ�ӷ��µ�Ĵ�������stick״̬�µ��µ�����źš� */
        unsigned int    rc_off                     : 1; /* [1..1] 0������RC������1���ر�RC������ */
        unsigned int    dr_fla_bre_ctrl            : 1; /* [2..2] 0: DR1/2/3�����ں�������ģʽ��1��DR1/2/3��������˸ģʽ�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_NO_RWR_REG_RW_T;    /* LEAK_CTL���µ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ana_in_2d                  : 8; /* [7..0] PMUģ�ⲿ�����룬8bits��ͨ���Ĵ�������������ʹ�á� */
    } bits;
    unsigned int    u32;
}HI_PMU_ANA_IN_T;    /* PMUģ�ⲿ������Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved0                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_RESERVED0_T;    /* ����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved1                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_RESERVED1_T;    /* ����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved2                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_RESERVED2_T;    /* ����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    clim_ctl                   : 4; /* [3..0] ���ڵ���470mA����ֵ�ļĴ����ź�Ĭ��ֵΪ0x0�� */
        unsigned int    clim_vth                   : 3; /* [6..4] ���ڵ����������ͱ�����������һ�µļĴ����ź� Ĭ��ֵΪ0x0�� */
        unsigned int    clim_op_isel               : 1; /* [7..7] OPƫ�õ���ѡ��0��0.5u��1��0.75u�� */
    } bits;
    unsigned int    u32;
}HI_PMU_CLIM_ADJ_T;    /* �������������ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    lit_cur_set                : 2; /* [1..0] ����ֵѡ��00��470mA��                              10��750mA��     11��900mA�� */
        unsigned int    pro_mode                   : 1; /* [2..2] ��LIT_CUR_SET<1>��ͬ�趨�����������ֵ��00��1A��01/10��1.5A��11��3A�� */
        unsigned int    vs                         : 3; /* [5..3] 150mA LDO ���ص����ʵ����źš� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_LIT_CUR_SET_T;    /* ����ֵ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pwe_int                : 1; /* [0..0] OTPд�����źš� */
        unsigned int    otp_por_int                : 1; /* [1..1] OTP�������źš� */
        unsigned int    otp_pa                     : 2; /* [3..2] OTP�ĵ�ַ�źš� */
        unsigned int    otp_ptm                    : 2; /* [5..4] ����ģʽʹ���źš� */
        unsigned int    otp_pprog                  : 1; /* [6..6] ���ģʽʹ���źš� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_OTP_CTRL_T;    /* OTP�����źżĴ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdin                   : 8; /* [7..0] OTP������ֵ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_PMU_OTP_PDIN_T;    /* OTPд��ֵ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob0                  : 8; /* [7..0] OTP_PDOB[7:0]�� */
    } bits;
    unsigned int    u32;
}HI_PMU_OTP_PDOB0_T;    /* OTP����ֵ0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob1                  : 8; /* [7..0] OTP_PDOB[15:8]�� */
    } bits;
    unsigned int    u32;
}HI_PMU_OTP_PDOB1_T;    /* OTP����ֵ1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob2                  : 8; /* [7..0] OTP_PDOB[23:16]�� */
    } bits;
    unsigned int    u32;
}HI_PMU_OTP_PDOB2_T;    /* OTP����ֵ2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob3                  : 8; /* [7..0] OTP_PDOB[31:24]�� */
    } bits;
    unsigned int    u32;
}HI_PMU_OTP_PDOB3_T;    /* OTP����ֵ3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    sleep_bandgap              : 1; /* [0..0] 0��ref_top����������1��ref_top����sleepģʽ�� */
        unsigned int    v0p59_sel                  : 1; /* [1..1] 0:VREF0P59_BUCK���0.59V��1:VREF0P59_BUCK���0.58V�� */
        unsigned int    sleep_ctrl1                : 1; /* [2..2] 0��ref_top����������1��ref_topǿ�ƽ���sleepģʽ������sleep_bandgap���ơ� */
        unsigned int    sleep_ctrl2                : 1; /* [3..3] 0��ref_top����������1��ref_top����testģʽ��������ӻ�׼�� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_BANDGAP_REG_T;    /* BANDGAP�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cmd_sd_2d                  : 1; /* [0..0] 0x0���ر�SD����⹦�ܣ�0x1������SD����⹦�ܡ� */
        unsigned int    reserved                   : 7; /* [7..1] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_DET_SD_LEVEL_CMD_T;    /* SD����ƽ���ָ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    state_sd_2d                : 2; /* [1..0] SD����ƽ״̬��00���������أ�01���������أ��Ҹߵ�ƽΪ1.8V��1X���������أ��Ҹߵ�ƽΪ3V�� */
        unsigned int    reserved                   : 6; /* [7..2] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_DET_SD_LEVEL_STATUS_T;    /* SD����ƽ���״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcdr0                     : 8; /* [7..0] 32 bits,RTC Data Register,�����ص�ǰRTCֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCDR0_T;    /* rtcdr[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcdr1                     : 8; /* [7..0] 32 bits,RTC Data Register,�����ص�ǰRTCֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCDR1_T;    /* rtcdr[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcdr2                     : 8; /* [7..0] 32 bits,RTC Data Register,�����ص�ǰRTCֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCDR2_T;    /* rtcdr[23:16]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcdr3                     : 8; /* [7..0] 32 bits,RTC Data Register,�����ص�ǰRTCֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCDR3_T;    /* rtcdr[31:24]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcclr0                    : 8; /* [7..0] 32 bits RTC load register ���ؼĴ��������õ�ǰʱ�䣩�������������趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCLR0_T;    /* rtclr[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcclr1                    : 8; /* [7..0] 32 bits RTC load register ���ؼĴ��������õ�ǰʱ�䣩�������������趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCLR1_T;    /* rtclr[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcclr2                    : 8; /* [7..0] 32 bits RTC load register ���ؼĴ��������õ�ǰʱ�䣩�������������趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCLR2_T;    /* rtclr[23:16]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcclr3                    : 8; /* [7..0] 32 bits RTC load register ���ؼĴ��������õ�ǰʱ�䣩�������������趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCLR3_T;    /* rtclr[31:24]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr                      : 1; /* [0..0] RTCʹ��λ0����RTC��ǰֵ������ֵȫ��Ϊ0��1����RTC��ǰֵ������ֵΪʵ�ʵ�ǰֵ�� */
        unsigned int    reserved                   : 7; /* [7..1] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCCTRL_T;    /* rtcctrl�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmra0                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRA0_T;    /* rtcmra[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmra1                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRA1_T;    /* rtcmra[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmra2                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRA2_T;    /* rtcmra[23:16]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmra3                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRA3_T;    /* rtcmra[31:24]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmrb0                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRB0_T;    /* rtcmrb[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmrb1                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRB1_T;    /* rtcmrb[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmrb2                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRB2_T;    /* rtcmrb[23:16]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmrb3                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRB3_T;    /* rtcmrb[31:24]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmrc0                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRC0_T;    /* rtcmrc[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmrc1                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRC1_T;    /* rtcmrc[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmrc2                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRC2_T;    /* rtcmrc[23:16]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmrc3                    : 8; /* [7..0] 32 bits,RTC match register �ȽϼĴ���(��������ʱ��)�����������һ�δ��趨ֵ�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTCMRC3_T;    /* rtcmrc[31:24]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtc_clk_setp_adj1          : 8; /* [7..0] ��ʱ���ȿ��Ե��ڣ����ڷ�Χ+/-192ppm��63��ʱ�ӣ������ڲ���3.05ppm��1��ʱ�ӣ���Ĭ��Ϊ0�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTC_ADJ1_T;    /* rtc_adj[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtc_clk_setp_adj2          : 8; /* [7..0] ��ʱ���ȿ��Ե��ڣ����ڷ�Χ+/-192ppm��63��ʱ�ӣ������ڲ���3.05ppm��1��ʱ�ӣ���Ĭ��Ϊ0�� */
    } bits;
    unsigned int    u32;
}HI_PMU_RTC_ADJ2_T;    /* rtc_adj[15:8]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved3                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_RESERVED3_T;    /* ����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved4                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_RESERVED4_T;    /* ����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved5                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_RESERVED5_T;    /* ����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved6                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_RESERVED6_T;    /* ����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved7                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_RESERVED7_T;    /* ����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved8                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_RESERVED8_T;    /* ����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    sht_pro_off_ctrl           : 1; /* [0..0] 0:������·��BUCK������·ʱ�������ػ���1��������·��BUCK������·ʱ�����ػ��� */
        unsigned int    reserved                   : 7; /* [7..1] ������ */
    } bits;
    unsigned int    u32;
}HI_PMU_ONOFF10_T;    /* ���ؿ���10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr1_en_bre                 : 1; /* [0..0] 1��dr1ʹ�ܣ�dr1_flash_en = 1,��˸dr1_flash_en = 0,���� */
        unsigned int    dr1_flash_en               : 1; /* [1..1] 1��dr1��˸ */
        unsigned int    reserved                   : 6; /* [7..2] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR1_BRE_CTRL_T;    /* DR1���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    dr1_t_off                  : 3; /* [2..0] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    dr1_t_on                   : 3; /* [6..4] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR1_TIM_CONF1_T;    /* DR1��������ʱ������ */

typedef union
{
    struct
    {
        unsigned int    dr1_t_rise                 : 3; /* [2..0] 000��0s001��0.25s010��0.5s011��1s100��2s101��4s */
        unsigned int    reserved_1                 : 1; /* [3..3]  */
        unsigned int    dr1_t_fall                 : 3; /* [6..4] 000��0s001��0.25s010��0.5s011��1s100��2s101��4s */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR1_TIM_CONF2_T;    /* DR1��������ʱ������ */

typedef union
{
    struct
    {
        unsigned int    dr2_en_bre                 : 1; /* [0..0] 1��dr2ʹ�ܣ�dr2_flash_en = 1,��˸dr2_flash_en = 0,���� */
        unsigned int    dr2_flash_en               : 1; /* [1..1] 1��dr2��˸ */
        unsigned int    reserved                   : 6; /* [7..2] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR2_BRE_CTRL_T;    /* DR2���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    dr2_t_off                  : 3; /* [2..0] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    dr2_t_on                   : 3; /* [6..4] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR2_TIM_CONF1_T;    /* DR2��������ʱ������ */

typedef union
{
    struct
    {
        unsigned int    dr2_t_rise                 : 3; /* [2..0] 000��0s001��0.25s010��0.5s011��1s100��2s101��4s */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    dr2_t_fall                 : 3; /* [6..4] 000��0s001��0.25s010��0.5s011��1s100��2s101��4s */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR2_TIM_CONF2_T;    /* DR2��������ʱ������ */

typedef union
{
    struct
    {
        unsigned int    d3_en                      : 1; /* [0..0] 1��dr1ʹ�ܣ�dr1_flash_en = 1,��˸dr1_flash_en = 0,���� */
        unsigned int    dr3_flash_en               : 1; /* [1..1] 1��dr1��˸ */
        unsigned int    reserved                   : 6; /* [7..2] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR3_BRE_CTRL_T;    /* DR3���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    dr3_t_off                  : 3; /* [2..0] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    dr3_t_on                   : 3; /* [6..4] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR3_TIM_CONF1_T;    /* DR3��������ʱ������ */

typedef union
{
    struct
    {
        unsigned int    dr3_t_rise                 : 3; /* [2..0] 000��0s001��0.25s010��0.5s011��1s100��2s101��4s */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    dr3_t_fall                 : 3; /* [6..4] 000��0s001��0.25s010��0.5s011��1s100��2s101��4s */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_DR3_TIM_CONF2_T;    /* DR3��������ʱ������ */

typedef union
{
    struct
    {
        unsigned int    no_pwr_resved1             : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_NO_PWR_RSVED1_T;    /* ����1���µ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    no_pwr_resved2             : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI_PMU_NO_PWR_RSVED2_T;    /* ����2���µ�Ĵ����� */


/********************************************************************************/
/*    pmu ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_pmu_version_version,version,HI_PMU_VERSION_T,HI_PMU_BASE_ADDR, HI_PMU_VERSION_OFFSET)
HI_SET_GET(hi_pmu_irq1_otmp_d3r,otmp_d3r,HI_PMU_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_irq1_hreset_n_f,hreset_n_f,HI_PMU_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_irq1_pwr_ini_2p7_d3f,pwr_ini_2p7_d3f,HI_PMU_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_irq1_pwr_ini_6p0_d3r,pwr_ini_6p0_d3r,HI_PMU_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_irq1_pwr_ini_6p0_d100r,pwr_ini_6p0_d100r,HI_PMU_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_irq1_pwron_d1sr,pwron_d1sr,HI_PMU_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_irq1_pwron_d20f,pwron_d20f,HI_PMU_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_irq1_pwron_d20r,pwron_d20r,HI_PMU_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_irq2_ocp_r,ocp_r,HI_PMU_IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ2_OFFSET)
HI_SET_GET(hi_pmu_irq2_vin_ldo_l_2p5_d3r,vin_ldo_l_2p5_d3r,HI_PMU_IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ2_OFFSET)
HI_SET_GET(hi_pmu_irq2_usb_4p0_d3f,usb_4p0_d3f,HI_PMU_IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ2_OFFSET)
HI_SET_GET(hi_pmu_irq2_usb_4p0_d3r,usb_4p0_d3r,HI_PMU_IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ2_OFFSET)
HI_SET_GET(hi_pmu_irq2_usb_6p0_d3r,usb_6p0_d3r,HI_PMU_IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ2_OFFSET)
HI_SET_GET(hi_pmu_irq2_vbus_4p0_d3f,vbus_4p0_d3f,HI_PMU_IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ2_OFFSET)
HI_SET_GET(hi_pmu_irq2_vbus_6p0_d3r,vbus_6p0_d3r,HI_PMU_IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ2_OFFSET)
HI_SET_GET(hi_pmu_irq2_vbus_6p0_d100r,vbus_6p0_d100r,HI_PMU_IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ2_OFFSET)
HI_SET_GET(hi_pmu_irq3_alarm_on_expanda,alarm_on_expanda,HI_PMU_IRQ3_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ3_OFFSET)
HI_SET_GET(hi_pmu_irq3_alarm_on_expandb,alarm_on_expandb,HI_PMU_IRQ3_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ3_OFFSET)
HI_SET_GET(hi_pmu_irq3_alarm_on_expandc,alarm_on_expandc,HI_PMU_IRQ3_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ3_OFFSET)
HI_SET_GET(hi_pmu_irq3_reserved,reserved,HI_PMU_IRQ3_T,HI_PMU_BASE_ADDR, HI_PMU_IRQ3_OFFSET)
HI_SET_GET(hi_pmu_status1_ocp_ldo2,ocp_ldo2,HI_PMU_STATUS1_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS1_OFFSET)
HI_SET_GET(hi_pmu_status1_ocp_ldo1,ocp_ldo1,HI_PMU_STATUS1_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS1_OFFSET)
HI_SET_GET(hi_pmu_status1_ocp_buck6,ocp_buck6,HI_PMU_STATUS1_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS1_OFFSET)
HI_SET_GET(hi_pmu_status1_ocp_buck5,ocp_buck5,HI_PMU_STATUS1_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS1_OFFSET)
HI_SET_GET(hi_pmu_status1_ocp_buck4,ocp_buck4,HI_PMU_STATUS1_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS1_OFFSET)
HI_SET_GET(hi_pmu_status1_ocp_buck3,ocp_buck3,HI_PMU_STATUS1_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS1_OFFSET)
HI_SET_GET(hi_pmu_status1_ocp_buck2,ocp_buck2,HI_PMU_STATUS1_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS1_OFFSET)
HI_SET_GET(hi_pmu_status1_ocp_buck1,ocp_buck1,HI_PMU_STATUS1_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS1_OFFSET)
HI_SET_GET(hi_pmu_status2_ocp_ldo10,ocp_ldo10,HI_PMU_STATUS2_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS2_OFFSET)
HI_SET_GET(hi_pmu_status2_ocp_ldo9,ocp_ldo9,HI_PMU_STATUS2_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS2_OFFSET)
HI_SET_GET(hi_pmu_status2_ocp_ldo8,ocp_ldo8,HI_PMU_STATUS2_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS2_OFFSET)
HI_SET_GET(hi_pmu_status2_ocp_ldo7,ocp_ldo7,HI_PMU_STATUS2_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS2_OFFSET)
HI_SET_GET(hi_pmu_status2_ocp_ldo6,ocp_ldo6,HI_PMU_STATUS2_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS2_OFFSET)
HI_SET_GET(hi_pmu_status2_ocp_ldo5,ocp_ldo5,HI_PMU_STATUS2_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS2_OFFSET)
HI_SET_GET(hi_pmu_status2_ocp_ldo4,ocp_ldo4,HI_PMU_STATUS2_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS2_OFFSET)
HI_SET_GET(hi_pmu_status2_ocp_ldo3,ocp_ldo3,HI_PMU_STATUS2_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS2_OFFSET)
HI_SET_GET(hi_pmu_status3_ocp_ldo15,ocp_ldo15,HI_PMU_STATUS3_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS3_OFFSET)
HI_SET_GET(hi_pmu_status3_ocp_ldo14,ocp_ldo14,HI_PMU_STATUS3_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS3_OFFSET)
HI_SET_GET(hi_pmu_status3_ocp_ldo13,ocp_ldo13,HI_PMU_STATUS3_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS3_OFFSET)
HI_SET_GET(hi_pmu_status3_ocp_ldo12,ocp_ldo12,HI_PMU_STATUS3_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS3_OFFSET)
HI_SET_GET(hi_pmu_status3_ocp_ldo11,ocp_ldo11,HI_PMU_STATUS3_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS3_OFFSET)
HI_SET_GET(hi_pmu_status3_reserved,reserved,HI_PMU_STATUS3_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS3_OFFSET)
HI_SET_GET(hi_pmu_status4_pwr_ini_2p7_d3f,pwr_ini_2p7_d3f,HI_PMU_STATUS4_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS4_OFFSET)
HI_SET_GET(hi_pmu_status4_pwr_ini_6p0_d3r,pwr_ini_6p0_d3r,HI_PMU_STATUS4_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS4_OFFSET)
HI_SET_GET(hi_pmu_status4_osc_state,osc_state,HI_PMU_STATUS4_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS4_OFFSET)
HI_SET_GET(hi_pmu_status4_otmp_d3r,otmp_d3r,HI_PMU_STATUS4_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS4_OFFSET)
HI_SET_GET(hi_pmu_status4_pwron_d20rf,pwron_d20rf,HI_PMU_STATUS4_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS4_OFFSET)
HI_SET_GET(hi_pmu_status4_alarm_on_expenda,alarm_on_expenda,HI_PMU_STATUS4_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS4_OFFSET)
HI_SET_GET(hi_pmu_status4_alarm_on_expendb,alarm_on_expendb,HI_PMU_STATUS4_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS4_OFFSET)
HI_SET_GET(hi_pmu_status4_alarm_on_expendc,alarm_on_expendc,HI_PMU_STATUS4_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS4_OFFSET)
HI_SET_GET(hi_pmu_status5_usb_4p0_d3rf,usb_4p0_d3rf,HI_PMU_STATUS5_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS5_OFFSET)
HI_SET_GET(hi_pmu_status5_usb_6p0_d3r,usb_6p0_d3r,HI_PMU_STATUS5_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS5_OFFSET)
HI_SET_GET(hi_pmu_status5_vbus_4p0_d3f,vbus_4p0_d3f,HI_PMU_STATUS5_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS5_OFFSET)
HI_SET_GET(hi_pmu_status5_vbus_6p0_d3r,vbus_6p0_d3r,HI_PMU_STATUS5_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS5_OFFSET)
HI_SET_GET(hi_pmu_status5_vin_ldo_l_2p5_d3r,vin_ldo_l_2p5_d3r,HI_PMU_STATUS5_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS5_OFFSET)
HI_SET_GET(hi_pmu_status5_reserved,reserved,HI_PMU_STATUS5_T,HI_PMU_BASE_ADDR, HI_PMU_STATUS5_OFFSET)
HI_SET_GET(hi_pmu_irqm1_otmp_d3rm,otmp_d3rm,HI_PMU_IRQM1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM1_OFFSET)
HI_SET_GET(hi_pmu_irqm1_hreset_n_fm,hreset_n_fm,HI_PMU_IRQM1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM1_OFFSET)
HI_SET_GET(hi_pmu_irqm1_pwr_ini_2p7_d3fm,pwr_ini_2p7_d3fm,HI_PMU_IRQM1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM1_OFFSET)
HI_SET_GET(hi_pmu_irqm1_pwr_ini_6p0_d3rm,pwr_ini_6p0_d3rm,HI_PMU_IRQM1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM1_OFFSET)
HI_SET_GET(hi_pmu_irqm1_pwr_ini_6p0_d100rm,pwr_ini_6p0_d100rm,HI_PMU_IRQM1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM1_OFFSET)
HI_SET_GET(hi_pmu_irqm1_pwron_d1srm,pwron_d1srm,HI_PMU_IRQM1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM1_OFFSET)
HI_SET_GET(hi_pmu_irqm1_pwron_d20fm,pwron_d20fm,HI_PMU_IRQM1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM1_OFFSET)
HI_SET_GET(hi_pmu_irqm1_pwron_d20rm,pwron_d20rm,HI_PMU_IRQM1_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM1_OFFSET)
HI_SET_GET(hi_pmu_irqm2_ocp_rm,ocp_rm,HI_PMU_IRQM2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM2_OFFSET)
HI_SET_GET(hi_pmu_irqm2_vin_ldo_l_2p5_d3rm,vin_ldo_l_2p5_d3rm,HI_PMU_IRQM2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM2_OFFSET)
HI_SET_GET(hi_pmu_irqm2_usb_4p0_d3fm,usb_4p0_d3fm,HI_PMU_IRQM2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM2_OFFSET)
HI_SET_GET(hi_pmu_irqm2_usb_4p0_d3rm,usb_4p0_d3rm,HI_PMU_IRQM2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM2_OFFSET)
HI_SET_GET(hi_pmu_irqm2_usb_6p0_d3rm,usb_6p0_d3rm,HI_PMU_IRQM2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM2_OFFSET)
HI_SET_GET(hi_pmu_irqm2_vbus_4p0_d3fm,vbus_4p0_d3fm,HI_PMU_IRQM2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM2_OFFSET)
HI_SET_GET(hi_pmu_irqm2_vbus_6p0_d3rm,vbus_6p0_d3rm,HI_PMU_IRQM2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM2_OFFSET)
HI_SET_GET(hi_pmu_irqm2_vbus_6p0_d100rm,vbus_6p0_d100rm,HI_PMU_IRQM2_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM2_OFFSET)
HI_SET_GET(hi_pmu_irqm3_alarm_on_expendam,alarm_on_expendam,HI_PMU_IRQM3_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM3_OFFSET)
HI_SET_GET(hi_pmu_irqm3_alarm_on_expendbm,alarm_on_expendbm,HI_PMU_IRQM3_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM3_OFFSET)
HI_SET_GET(hi_pmu_irqm3_alarm_on_expendcm,alarm_on_expendcm,HI_PMU_IRQM3_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM3_OFFSET)
HI_SET_GET(hi_pmu_irqm3_reserved,reserved,HI_PMU_IRQM3_T,HI_PMU_BASE_ADDR, HI_PMU_IRQM3_OFFSET)
HI_SET_GET(hi_pmu_onoff1_en_eco_ldo4_int,en_eco_ldo4_int,HI_PMU_ONOFF1_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF1_OFFSET)
HI_SET_GET(hi_pmu_onoff1_en_ldo4_int,en_ldo4_int,HI_PMU_ONOFF1_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF1_OFFSET)
HI_SET_GET(hi_pmu_onoff1_en_eco_ldo3_int,en_eco_ldo3_int,HI_PMU_ONOFF1_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF1_OFFSET)
HI_SET_GET(hi_pmu_onoff1_en_ldo3_int,en_ldo3_int,HI_PMU_ONOFF1_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF1_OFFSET)
HI_SET_GET(hi_pmu_onoff1_en_eco_ldo2_int,en_eco_ldo2_int,HI_PMU_ONOFF1_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF1_OFFSET)
HI_SET_GET(hi_pmu_onoff1_en_ldo2_int,en_ldo2_int,HI_PMU_ONOFF1_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF1_OFFSET)
HI_SET_GET(hi_pmu_onoff1_en_eco_ldo1_int,en_eco_ldo1_int,HI_PMU_ONOFF1_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF1_OFFSET)
HI_SET_GET(hi_pmu_onoff1_en_ldo1_int,en_ldo1_int,HI_PMU_ONOFF1_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF1_OFFSET)
HI_SET_GET(hi_pmu_onoff2_en_eco_ldo8_int,en_eco_ldo8_int,HI_PMU_ONOFF2_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF2_OFFSET)
HI_SET_GET(hi_pmu_onoff2_en_ldo8_int,en_ldo8_int,HI_PMU_ONOFF2_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF2_OFFSET)
HI_SET_GET(hi_pmu_onoff2_en_eco_ldo7_int,en_eco_ldo7_int,HI_PMU_ONOFF2_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF2_OFFSET)
HI_SET_GET(hi_pmu_onoff2_en_ldo7_int,en_ldo7_int,HI_PMU_ONOFF2_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF2_OFFSET)
HI_SET_GET(hi_pmu_onoff2_en_eco_ldo6_int,en_eco_ldo6_int,HI_PMU_ONOFF2_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF2_OFFSET)
HI_SET_GET(hi_pmu_onoff2_en_ldo6_int,en_ldo6_int,HI_PMU_ONOFF2_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF2_OFFSET)
HI_SET_GET(hi_pmu_onoff2_en_eco_ldo5_int,en_eco_ldo5_int,HI_PMU_ONOFF2_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF2_OFFSET)
HI_SET_GET(hi_pmu_onoff2_en_ldo5_int,en_ldo5_int,HI_PMU_ONOFF2_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF2_OFFSET)
HI_SET_GET(hi_pmu_onoff3_en_eco_ldo12_int,en_eco_ldo12_int,HI_PMU_ONOFF3_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF3_OFFSET)
HI_SET_GET(hi_pmu_onoff3_en_ldo12_int,en_ldo12_int,HI_PMU_ONOFF3_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF3_OFFSET)
HI_SET_GET(hi_pmu_onoff3_en_eco_ldo11_int,en_eco_ldo11_int,HI_PMU_ONOFF3_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF3_OFFSET)
HI_SET_GET(hi_pmu_onoff3_en_ldo11_int,en_ldo11_int,HI_PMU_ONOFF3_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF3_OFFSET)
HI_SET_GET(hi_pmu_onoff3_en_eco_ldo10_int,en_eco_ldo10_int,HI_PMU_ONOFF3_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF3_OFFSET)
HI_SET_GET(hi_pmu_onoff3_en_ldo10_int,en_ldo10_int,HI_PMU_ONOFF3_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF3_OFFSET)
HI_SET_GET(hi_pmu_onoff3_en_eco_ldo9_int,en_eco_ldo9_int,HI_PMU_ONOFF3_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF3_OFFSET)
HI_SET_GET(hi_pmu_onoff3_en_ldo9_int,en_ldo9_int,HI_PMU_ONOFF3_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF3_OFFSET)
HI_SET_GET(hi_pmu_onoff4_en_eco_ldo15_int,en_eco_ldo15_int,HI_PMU_ONOFF4_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF4_OFFSET)
HI_SET_GET(hi_pmu_onoff4_en_ldo15_int,en_ldo15_int,HI_PMU_ONOFF4_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF4_OFFSET)
HI_SET_GET(hi_pmu_onoff4_en_eco_ldo14_int,en_eco_ldo14_int,HI_PMU_ONOFF4_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF4_OFFSET)
HI_SET_GET(hi_pmu_onoff4_en_ldo14_int,en_ldo14_int,HI_PMU_ONOFF4_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF4_OFFSET)
HI_SET_GET(hi_pmu_onoff4_en_eco_ldo13_int,en_eco_ldo13_int,HI_PMU_ONOFF4_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF4_OFFSET)
HI_SET_GET(hi_pmu_onoff4_en_ldo13_int,en_ldo13_int,HI_PMU_ONOFF4_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF4_OFFSET)
HI_SET_GET(hi_pmu_onoff4_reserved,reserved,HI_PMU_ONOFF4_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF4_OFFSET)
HI_SET_GET(hi_pmu_onoff5_reserved_2,reserved_2,HI_PMU_ONOFF5_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF5_OFFSET)
HI_SET_GET(hi_pmu_onoff5_en_buck4_int,en_buck4_int,HI_PMU_ONOFF5_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF5_OFFSET)
HI_SET_GET(hi_pmu_onoff5_reserved_1,reserved_1,HI_PMU_ONOFF5_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF5_OFFSET)
HI_SET_GET(hi_pmu_onoff5_en_buck3_int,en_buck3_int,HI_PMU_ONOFF5_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF5_OFFSET)
HI_SET_GET(hi_pmu_onoff5_reserved_0,reserved_0,HI_PMU_ONOFF5_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF5_OFFSET)
HI_SET_GET(hi_pmu_onoff5_en_buck2_int,en_buck2_int,HI_PMU_ONOFF5_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF5_OFFSET)
HI_SET_GET(hi_pmu_onoff5_en_buck1_int,en_buck1_int,HI_PMU_ONOFF5_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF5_OFFSET)
HI_SET_GET(hi_pmu_onoff6_reserved_1,reserved_1,HI_PMU_ONOFF6_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF6_OFFSET)
HI_SET_GET(hi_pmu_onoff6_en_buck1_eno6_int,en_buck1_eno6_int,HI_PMU_ONOFF6_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF6_OFFSET)
HI_SET_GET(hi_pmu_onoff6_en_buck6_ldo_int,en_buck6_ldo_int,HI_PMU_ONOFF6_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF6_OFFSET)
HI_SET_GET(hi_pmu_onoff6_en_eno6_eco_int,en_eno6_eco_int,HI_PMU_ONOFF6_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF6_OFFSET)
HI_SET_GET(hi_pmu_onoff6_en_buck6_int,en_buck6_int,HI_PMU_ONOFF6_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF6_OFFSET)
HI_SET_GET(hi_pmu_onoff6_reserved_0,reserved_0,HI_PMU_ONOFF6_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF6_OFFSET)
HI_SET_GET(hi_pmu_onoff6_en_buck5_int,en_buck5_int,HI_PMU_ONOFF6_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF6_OFFSET)
HI_SET_GET(hi_pmu_onoff7_otmp_off_ctrl,otmp_off_ctrl,HI_PMU_ONOFF7_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF7_OFFSET)
HI_SET_GET(hi_pmu_onoff7_en_32k2,en_32k2,HI_PMU_ONOFF7_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF7_OFFSET)
HI_SET_GET(hi_pmu_onoff7_en_32k1,en_32k1,HI_PMU_ONOFF7_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF7_OFFSET)
HI_SET_GET(hi_pmu_onoff7_set_tmp,set_tmp,HI_PMU_ONOFF7_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF7_OFFSET)
HI_SET_GET(hi_pmu_onoff7_en_tmp,en_tmp,HI_PMU_ONOFF7_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF7_OFFSET)
HI_SET_GET(hi_pmu_onoff7_reserved,reserved,HI_PMU_ONOFF7_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF7_OFFSET)
HI_SET_GET(hi_pmu_onoff8_vbus_4p0_ctrl,vbus_4p0_ctrl,HI_PMU_ONOFF8_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF8_OFFSET)
HI_SET_GET(hi_pmu_onoff8_vbus_6p0_ctrl,vbus_6p0_ctrl,HI_PMU_ONOFF8_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF8_OFFSET)
HI_SET_GET(hi_pmu_onoff8_pwr_ini_2p7_ctrl,pwr_ini_2p7_ctrl,HI_PMU_ONOFF8_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF8_OFFSET)
HI_SET_GET(hi_pmu_onoff8_pwr_ini_6p0_ctrl,pwr_ini_6p0_ctrl,HI_PMU_ONOFF8_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF8_OFFSET)
HI_SET_GET(hi_pmu_onoff8_reserved,reserved,HI_PMU_ONOFF8_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF8_OFFSET)
HI_SET_GET(hi_pmu_onoff9_en_vbus_4p0,en_vbus_4p0,HI_PMU_ONOFF9_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF9_OFFSET)
HI_SET_GET(hi_pmu_onoff9_en_vbus_6p0,en_vbus_6p0,HI_PMU_ONOFF9_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF9_OFFSET)
HI_SET_GET(hi_pmu_onoff9_en_pini_2p7,en_pini_2p7,HI_PMU_ONOFF9_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF9_OFFSET)
HI_SET_GET(hi_pmu_onoff9_en_pini_6p0,en_pini_6p0,HI_PMU_ONOFF9_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF9_OFFSET)
HI_SET_GET(hi_pmu_onoff9_en_vin_ldo_l_2p5,en_vin_ldo_l_2p5,HI_PMU_ONOFF9_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF9_OFFSET)
HI_SET_GET(hi_pmu_onoff9_reserved,reserved,HI_PMU_ONOFF9_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF9_OFFSET)
HI_SET_GET(hi_pmu_ldo_swich1_en_ldo8_sw,en_ldo8_sw,HI_PMU_LDO_SWICH1_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWICH1_OFFSET)
HI_SET_GET(hi_pmu_ldo_swich1_en_ldo7_sw,en_ldo7_sw,HI_PMU_LDO_SWICH1_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWICH1_OFFSET)
HI_SET_GET(hi_pmu_ldo_swich1_en_ldo6_sw,en_ldo6_sw,HI_PMU_LDO_SWICH1_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWICH1_OFFSET)
HI_SET_GET(hi_pmu_ldo_swich1_en_ldo5_sw,en_ldo5_sw,HI_PMU_LDO_SWICH1_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWICH1_OFFSET)
HI_SET_GET(hi_pmu_ldo_swich1_en_ldo4_sw,en_ldo4_sw,HI_PMU_LDO_SWICH1_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWICH1_OFFSET)
HI_SET_GET(hi_pmu_ldo_swich1_en_ldo3_sw,en_ldo3_sw,HI_PMU_LDO_SWICH1_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWICH1_OFFSET)
HI_SET_GET(hi_pmu_ldo_swich1_en_ldo2_sw,en_ldo2_sw,HI_PMU_LDO_SWICH1_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWICH1_OFFSET)
HI_SET_GET(hi_pmu_ldo_swich1_en_ldo1_sw,en_ldo1_sw,HI_PMU_LDO_SWICH1_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWICH1_OFFSET)
HI_SET_GET(hi_pmu_ldo_switch2_en_ldo15_sw,en_ldo15_sw,HI_PMU_LDO_SWITCH2_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWITCH2_OFFSET)
HI_SET_GET(hi_pmu_ldo_switch2_en_ldo14_sw,en_ldo14_sw,HI_PMU_LDO_SWITCH2_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWITCH2_OFFSET)
HI_SET_GET(hi_pmu_ldo_switch2_en_ldo13_sw,en_ldo13_sw,HI_PMU_LDO_SWITCH2_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWITCH2_OFFSET)
HI_SET_GET(hi_pmu_ldo_switch2_en_ldo12_sw,en_ldo12_sw,HI_PMU_LDO_SWITCH2_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWITCH2_OFFSET)
HI_SET_GET(hi_pmu_ldo_switch2_en_ldo11_sw,en_ldo11_sw,HI_PMU_LDO_SWITCH2_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWITCH2_OFFSET)
HI_SET_GET(hi_pmu_ldo_switch2_en_ldo10_sw,en_ldo10_sw,HI_PMU_LDO_SWITCH2_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWITCH2_OFFSET)
HI_SET_GET(hi_pmu_ldo_switch2_en_ldo9_sw,en_ldo9_sw,HI_PMU_LDO_SWITCH2_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWITCH2_OFFSET)
HI_SET_GET(hi_pmu_ldo_switch2_reserved,reserved,HI_PMU_LDO_SWITCH2_T,HI_PMU_BASE_ADDR, HI_PMU_LDO_SWITCH2_OFFSET)
HI_SET_GET(hi_pmu_set_buck1_vset_buck1,vset_buck1,HI_PMU_SET_BUCK1_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK1_OFFSET)
HI_SET_GET(hi_pmu_set_buck1_reserved,reserved,HI_PMU_SET_BUCK1_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK1_OFFSET)
HI_SET_GET(hi_pmu_set_buck2_vset_buck2,vset_buck2,HI_PMU_SET_BUCK2_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK2_OFFSET)
HI_SET_GET(hi_pmu_set_buck2_reserved,reserved,HI_PMU_SET_BUCK2_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK2_OFFSET)
HI_SET_GET(hi_pmu_set_buck3_vset_buck3,vset_buck3,HI_PMU_SET_BUCK3_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK3_OFFSET)
HI_SET_GET(hi_pmu_set_buck3_reserved,reserved,HI_PMU_SET_BUCK3_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK3_OFFSET)
HI_SET_GET(hi_pmu_set_buck4_vset_buck4,vset_buck4,HI_PMU_SET_BUCK4_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK4_OFFSET)
HI_SET_GET(hi_pmu_set_buck4_pdm_sel,pdm_sel,HI_PMU_SET_BUCK4_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK4_OFFSET)
HI_SET_GET(hi_pmu_set_buck4_buck4_mode_sel_int,buck4_mode_sel_int,HI_PMU_SET_BUCK4_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK4_OFFSET)
HI_SET_GET(hi_pmu_set_buck4_reserved,reserved,HI_PMU_SET_BUCK4_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK4_OFFSET)
HI_SET_GET(hi_pmu_set_buck5_vset_buck5,vset_buck5,HI_PMU_SET_BUCK5_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK5_OFFSET)
HI_SET_GET(hi_pmu_set_buck5_buck5_mode_sel_int,buck5_mode_sel_int,HI_PMU_SET_BUCK5_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK5_OFFSET)
HI_SET_GET(hi_pmu_set_buck5_reserved,reserved,HI_PMU_SET_BUCK5_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK5_OFFSET)
HI_SET_GET(hi_pmu_set_buck6_vset_buck6,vset_buck6,HI_PMU_SET_BUCK6_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK6_OFFSET)
HI_SET_GET(hi_pmu_set_buck6_reserved,reserved,HI_PMU_SET_BUCK6_T,HI_PMU_BASE_ADDR, HI_PMU_SET_BUCK6_OFFSET)
HI_SET_GET(hi_pmu_buck1_adj1_ocp_d_buck1,ocp_d_buck1,HI_PMU_BUCK1_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck1_adj1_adj_clx_buck1,adj_clx_buck1,HI_PMU_BUCK1_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck1_adj1_adj_rlx_buck1,adj_rlx_buck1,HI_PMU_BUCK1_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck1_adj1_icmp_buck1,icmp_buck1,HI_PMU_BUCK1_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck1_adj1_sleep_buck1_int,sleep_buck1_int,HI_PMU_BUCK1_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck1_adj2_reg_dr_buck1,reg_dr_buck1,HI_PMU_BUCK1_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_adj2_reg_r_buck1,reg_r_buck1,HI_PMU_BUCK1_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_adj2_reg_c_buck1,reg_c_buck1,HI_PMU_BUCK1_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_adj2_en_reg_buck1,en_reg_buck1,HI_PMU_BUCK1_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_adj2_dt_sel_buck1,dt_sel_buck1,HI_PMU_BUCK1_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_adj2_reserved,reserved,HI_PMU_BUCK1_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck2_adj1_ocp_d_buck2,ocp_d_buck2,HI_PMU_BUCK2_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK2_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck2_adj1_adj_clx_buck2,adj_clx_buck2,HI_PMU_BUCK2_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK2_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck2_adj1_adj_rlx_buck2,adj_rlx_buck2,HI_PMU_BUCK2_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK2_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck2_adj1_icmp_buck2,icmp_buck2,HI_PMU_BUCK2_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK2_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck2_adj1_sleep_buck2_int,sleep_buck2_int,HI_PMU_BUCK2_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK2_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck2_adj2_reg_dr_buck2,reg_dr_buck2,HI_PMU_BUCK2_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK2_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck2_adj2_reg_r_buck2,reg_r_buck2,HI_PMU_BUCK2_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK2_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck2_adj2_reg_c_buck2,reg_c_buck2,HI_PMU_BUCK2_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK2_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck2_adj2_en_reg_buck2,en_reg_buck2,HI_PMU_BUCK2_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK2_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck2_adj2_dt_sel_buck2,dt_sel_buck2,HI_PMU_BUCK2_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK2_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck2_adj2_reserved,reserved,HI_PMU_BUCK2_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK2_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck3_adj1_ocp_d_buck3,ocp_d_buck3,HI_PMU_BUCK3_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK3_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck3_adj1_adj_clx_buck3,adj_clx_buck3,HI_PMU_BUCK3_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK3_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck3_adj1_adj_rlx_buck3,adj_rlx_buck3,HI_PMU_BUCK3_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK3_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck3_adj1_icmp_buck3,icmp_buck3,HI_PMU_BUCK3_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK3_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck3_adj1_sleep_buck3_int,sleep_buck3_int,HI_PMU_BUCK3_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK3_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck3_adj2_reg_dr_buck3,reg_dr_buck3,HI_PMU_BUCK3_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK3_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck3_adj2_reg_r_buck3,reg_r_buck3,HI_PMU_BUCK3_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK3_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck3_adj2_reg_c_buck3,reg_c_buck3,HI_PMU_BUCK3_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK3_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck3_adj2_en_reg_buck3,en_reg_buck3,HI_PMU_BUCK3_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK3_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck3_adj2_dt_sel_buck3,dt_sel_buck3,HI_PMU_BUCK3_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK3_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck3_adj2_reserved,reserved,HI_PMU_BUCK3_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK3_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_2_4_adj2_ocp_3a_p,ocp_3a_p,HI_PMU_BUCK1_2_4_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_2_4_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_2_4_adj2_reserved,reserved,HI_PMU_BUCK1_2_4_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_2_4_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_2_4_adj2_ccm4_ctr,ccm4_ctr,HI_PMU_BUCK1_2_4_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_2_4_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_2_4_adj2_sleep_buck4_int,sleep_buck4_int,HI_PMU_BUCK1_2_4_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_2_4_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_2_4_adj2_slope_ctrl_buck4,slope_ctrl_buck4,HI_PMU_BUCK1_2_4_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_2_4_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_2_4_adj2_offset_trim_start_int,offset_trim_start_int,HI_PMU_BUCK1_2_4_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_2_4_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_2_4_adj2_offset_trim_reg,offset_trim_reg,HI_PMU_BUCK1_2_4_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_2_4_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck1_2_4_adj2_offset_cancel_en,offset_cancel_en,HI_PMU_BUCK1_2_4_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK1_2_4_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck5_adj_ccm5_ctr,ccm5_ctr,HI_PMU_BUCK5_ADJ_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK5_ADJ_OFFSET)
HI_SET_GET(hi_pmu_buck5_adj_sleep_buck5_int,sleep_buck5_int,HI_PMU_BUCK5_ADJ_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK5_ADJ_OFFSET)
HI_SET_GET(hi_pmu_buck5_adj_slope_ctrl_buck5,slope_ctrl_buck5,HI_PMU_BUCK5_ADJ_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK5_ADJ_OFFSET)
HI_SET_GET(hi_pmu_buck5_adj_reserved,reserved,HI_PMU_BUCK5_ADJ_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK5_ADJ_OFFSET)
HI_SET_GET(hi_pmu_buck6_adj1_ocp_d_buck6,ocp_d_buck6,HI_PMU_BUCK6_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK6_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck6_adj1_adj_clx_buck6,adj_clx_buck6,HI_PMU_BUCK6_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK6_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck6_adj1_adj_rlx_buck6,adj_rlx_buck6,HI_PMU_BUCK6_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK6_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck6_adj1_icmp_buck6,icmp_buck6,HI_PMU_BUCK6_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK6_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck6_adj1_sleep_buck6_int,sleep_buck6_int,HI_PMU_BUCK6_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK6_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_buck6_adj2_reg_dr_buck6,reg_dr_buck6,HI_PMU_BUCK6_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK6_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck6_adj2_reg_r_buck6,reg_r_buck6,HI_PMU_BUCK6_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK6_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck6_adj2_reg_c_buck6,reg_c_buck6,HI_PMU_BUCK6_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK6_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck6_adj2_en_reg_buck6,en_reg_buck6,HI_PMU_BUCK6_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK6_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck6_adj2_dt_sel_buck6,dt_sel_buck6,HI_PMU_BUCK6_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK6_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck6_adj2_reserved,reserved,HI_PMU_BUCK6_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK6_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_buck4_5_freq_buck_frq_adj,buck_frq_adj,HI_PMU_BUCK4_5_FREQ_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK4_5_FREQ_OFFSET)
HI_SET_GET(hi_pmu_buck4_5_freq_ocp_shield_p,ocp_shield_p,HI_PMU_BUCK4_5_FREQ_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK4_5_FREQ_OFFSET)
HI_SET_GET(hi_pmu_buck4_5_freq_shortn,shortn,HI_PMU_BUCK4_5_FREQ_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK4_5_FREQ_OFFSET)
HI_SET_GET(hi_pmu_buck4_5_freq_reserved,reserved,HI_PMU_BUCK4_5_FREQ_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK4_5_FREQ_OFFSET)
HI_SET_GET(hi_pmu_buck4_comp_adj_buck4_comp_adj,buck4_comp_adj,HI_PMU_BUCK4_COMP_ADJ_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK4_COMP_ADJ_OFFSET)
HI_SET_GET(hi_pmu_buck5_comp_adj_buck5_comp_adj,buck5_comp_adj,HI_PMU_BUCK5_COMP_ADJ_T,HI_PMU_BASE_ADDR, HI_PMU_BUCK5_COMP_ADJ_OFFSET)
HI_SET_GET(hi_pmu_set_ldo1_vset_ldo1,vset_ldo1,HI_PMU_SET_LDO1_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO1_OFFSET)
HI_SET_GET(hi_pmu_set_ldo1_reserved,reserved,HI_PMU_SET_LDO1_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO1_OFFSET)
HI_SET_GET(hi_pmu_set_ldo2_vset_ldo2,vset_ldo2,HI_PMU_SET_LDO2_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO2_OFFSET)
HI_SET_GET(hi_pmu_set_ldo2_reserved,reserved,HI_PMU_SET_LDO2_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO2_OFFSET)
HI_SET_GET(hi_pmu_set_ldo3_vset_ldo3,vset_ldo3,HI_PMU_SET_LDO3_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO3_OFFSET)
HI_SET_GET(hi_pmu_set_ldo3_reserved,reserved,HI_PMU_SET_LDO3_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO3_OFFSET)
HI_SET_GET(hi_pmu_set_ldo4_vset_ldo4,vset_ldo4,HI_PMU_SET_LDO4_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO4_OFFSET)
HI_SET_GET(hi_pmu_set_ldo4_reserved,reserved,HI_PMU_SET_LDO4_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO4_OFFSET)
HI_SET_GET(hi_pmu_set_ldo5_vset_ldo5,vset_ldo5,HI_PMU_SET_LDO5_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO5_OFFSET)
HI_SET_GET(hi_pmu_set_ldo5_reserved,reserved,HI_PMU_SET_LDO5_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO5_OFFSET)
HI_SET_GET(hi_pmu_set_ldo6_vset_ldo6,vset_ldo6,HI_PMU_SET_LDO6_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO6_OFFSET)
HI_SET_GET(hi_pmu_set_ldo6_reserved,reserved,HI_PMU_SET_LDO6_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO6_OFFSET)
HI_SET_GET(hi_pmu_set_ldo7_vset_ldo7,vset_ldo7,HI_PMU_SET_LDO7_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO7_OFFSET)
HI_SET_GET(hi_pmu_set_ldo7_reserved,reserved,HI_PMU_SET_LDO7_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO7_OFFSET)
HI_SET_GET(hi_pmu_set_ldo8_vset_ldo8,vset_ldo8,HI_PMU_SET_LDO8_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO8_OFFSET)
HI_SET_GET(hi_pmu_set_ldo8_reserved,reserved,HI_PMU_SET_LDO8_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO8_OFFSET)
HI_SET_GET(hi_pmu_set_ldo9_vset_ldo9,vset_ldo9,HI_PMU_SET_LDO9_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO9_OFFSET)
HI_SET_GET(hi_pmu_set_ldo9_reserved,reserved,HI_PMU_SET_LDO9_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO9_OFFSET)
HI_SET_GET(hi_pmu_set_ldo10_vset_ldo10,vset_ldo10,HI_PMU_SET_LDO10_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO10_OFFSET)
HI_SET_GET(hi_pmu_set_ldo10_reserved,reserved,HI_PMU_SET_LDO10_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO10_OFFSET)
HI_SET_GET(hi_pmu_set_ldo11_vset_ldo11,vset_ldo11,HI_PMU_SET_LDO11_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO11_OFFSET)
HI_SET_GET(hi_pmu_set_ldo11_reserved,reserved,HI_PMU_SET_LDO11_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO11_OFFSET)
HI_SET_GET(hi_pmu_set_ldo13_vset_ldo13,vset_ldo13,HI_PMU_SET_LDO13_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO13_OFFSET)
HI_SET_GET(hi_pmu_set_ldo13_reserved,reserved,HI_PMU_SET_LDO13_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO13_OFFSET)
HI_SET_GET(hi_pmu_set_ldo14_vset_ldo14,vset_ldo14,HI_PMU_SET_LDO14_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO14_OFFSET)
HI_SET_GET(hi_pmu_set_ldo14_reserved,reserved,HI_PMU_SET_LDO14_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO14_OFFSET)
HI_SET_GET(hi_pmu_set_ldo15_vset_ldo15,vset_ldo15,HI_PMU_SET_LDO15_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO15_OFFSET)
HI_SET_GET(hi_pmu_set_ldo15_reserved,reserved,HI_PMU_SET_LDO15_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO15_OFFSET)
HI_SET_GET(hi_pmu_set_ldo17_vset_ldo17,vset_ldo17,HI_PMU_SET_LDO17_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO17_OFFSET)
HI_SET_GET(hi_pmu_set_ldo17_reserved,reserved,HI_PMU_SET_LDO17_T,HI_PMU_BASE_ADDR, HI_PMU_SET_LDO17_OFFSET)
HI_SET_GET(hi_pmu_set_otp_otp_por_pulse,otp_por_pulse,HI_PMU_SET_OTP_T,HI_PMU_BASE_ADDR, HI_PMU_SET_OTP_OFFSET)
HI_SET_GET(hi_pmu_set_otp_otp_read_mask,otp_read_mask,HI_PMU_SET_OTP_T,HI_PMU_BASE_ADDR, HI_PMU_SET_OTP_OFFSET)
HI_SET_GET(hi_pmu_set_otp_otp_pwe_pulse,otp_pwe_pulse,HI_PMU_SET_OTP_T,HI_PMU_BASE_ADDR, HI_PMU_SET_OTP_OFFSET)
HI_SET_GET(hi_pmu_set_otp_otp_write_mask,otp_write_mask,HI_PMU_SET_OTP_T,HI_PMU_BASE_ADDR, HI_PMU_SET_OTP_OFFSET)
HI_SET_GET(hi_pmu_set_otp_reserved,reserved,HI_PMU_SET_OTP_T,HI_PMU_BASE_ADDR, HI_PMU_SET_OTP_OFFSET)
HI_SET_GET(hi_pmu_dr1_mode_iset_dr1,iset_dr1,HI_PMU_DR1_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_MODE_OFFSET)
HI_SET_GET(hi_pmu_dr1_mode_en_dr1_int,en_dr1_int,HI_PMU_DR1_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_MODE_OFFSET)
HI_SET_GET(hi_pmu_dr1_mode_dr1_mode,dr1_mode,HI_PMU_DR1_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_MODE_OFFSET)
HI_SET_GET(hi_pmu_dr1_mode_reserved,reserved,HI_PMU_DR1_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_MODE_OFFSET)
HI_SET_GET(hi_pmu_dr2_mode_iset_dr2,iset_dr2,HI_PMU_DR2_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_MODE_OFFSET)
HI_SET_GET(hi_pmu_dr2_mode_en_dr2_int,en_dr2_int,HI_PMU_DR2_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_MODE_OFFSET)
HI_SET_GET(hi_pmu_dr2_mode_dr2_mode,dr2_mode,HI_PMU_DR2_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_MODE_OFFSET)
HI_SET_GET(hi_pmu_dr2_mode_reserved,reserved,HI_PMU_DR2_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_MODE_OFFSET)
HI_SET_GET(hi_pmu_dr3_mode_iset_dr3,iset_dr3,HI_PMU_DR3_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_MODE_OFFSET)
HI_SET_GET(hi_pmu_dr3_mode_en_dr3_int,en_dr3_int,HI_PMU_DR3_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_MODE_OFFSET)
HI_SET_GET(hi_pmu_dr3_mode_dr3_mode,dr3_mode,HI_PMU_DR3_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_MODE_OFFSET)
HI_SET_GET(hi_pmu_dr3_mode_reserved,reserved,HI_PMU_DR3_MODE_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_MODE_OFFSET)
HI_SET_GET(hi_pmu_flash_period_flash_period,flash_period,HI_PMU_FLASH_PERIOD_T,HI_PMU_BASE_ADDR, HI_PMU_FLASH_PERIOD_OFFSET)
HI_SET_GET(hi_pmu_flash_on_flash_on,flash_on,HI_PMU_FLASH_ON_T,HI_PMU_BASE_ADDR, HI_PMU_FLASH_ON_OFFSET)
HI_SET_GET(hi_pmu_periph_ctrl1_ocp_auto_off,ocp_auto_off,HI_PMU_PERIPH_CTRL1_T,HI_PMU_BASE_ADDR, HI_PMU_PERIPH_CTRL1_OFFSET)
HI_SET_GET(hi_pmu_periph_ctrl1_ocp_shut_down_ctrl,ocp_shut_down_ctrl,HI_PMU_PERIPH_CTRL1_T,HI_PMU_BASE_ADDR, HI_PMU_PERIPH_CTRL1_OFFSET)
HI_SET_GET(hi_pmu_periph_ctrl1_ocp_deb_sel,ocp_deb_sel,HI_PMU_PERIPH_CTRL1_T,HI_PMU_BASE_ADDR, HI_PMU_PERIPH_CTRL1_OFFSET)
HI_SET_GET(hi_pmu_periph_ctrl1_en_buck_ocp_debounce,en_buck_ocp_debounce,HI_PMU_PERIPH_CTRL1_T,HI_PMU_BASE_ADDR, HI_PMU_PERIPH_CTRL1_OFFSET)
HI_SET_GET(hi_pmu_periph_ctrl1_en_ldo_ocp_debounce,en_ldo_ocp_debounce,HI_PMU_PERIPH_CTRL1_T,HI_PMU_BASE_ADDR, HI_PMU_PERIPH_CTRL1_OFFSET)
HI_SET_GET(hi_pmu_periph_ctrl1_lim_mode_int,lim_mode_int,HI_PMU_PERIPH_CTRL1_T,HI_PMU_BASE_ADDR, HI_PMU_PERIPH_CTRL1_OFFSET)
HI_SET_GET(hi_pmu_periph_ctrl1_reserved,reserved,HI_PMU_PERIPH_CTRL1_T,HI_PMU_BASE_ADDR, HI_PMU_PERIPH_CTRL1_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq1_hrst_otmp_d3,hrst_otmp_d3,HI_PMU_NO_PWR_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq1_hrst_hreset_n_f,hrst_hreset_n_f,HI_PMU_NO_PWR_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq1_hrst_pwr_ini_2p7_d3f,hrst_pwr_ini_2p7_d3f,HI_PMU_NO_PWR_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq1_hrst_pwr_ini_6p0_d3r,hrst_pwr_ini_6p0_d3r,HI_PMU_NO_PWR_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq1_hrst_pwr_ini_6p0_d100r,hrst_pwr_ini_6p0_d100r,HI_PMU_NO_PWR_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq1_hrst_pwron_d1sr,hrst_pwron_d1sr,HI_PMU_NO_PWR_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq1_hrst_pwron_d20f,hrst_pwron_d20f,HI_PMU_NO_PWR_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq1_hrst_pwron_d20r,hrst_pwron_d20r,HI_PMU_NO_PWR_IRQ1_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ1_OFFSET)
HI_SET_GET(hi_pmu_no_pwr__irq2_hrst_ocp_total,hrst_ocp_total,HI_PMU_NO_PWR__IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR__IRQ2_OFFSET)
HI_SET_GET(hi_pmu_no_pwr__irq2_hrst_vin_ldo_l_2p5_d3r,hrst_vin_ldo_l_2p5_d3r,HI_PMU_NO_PWR__IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR__IRQ2_OFFSET)
HI_SET_GET(hi_pmu_no_pwr__irq2_hrst_usb_4p0_d3f,hrst_usb_4p0_d3f,HI_PMU_NO_PWR__IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR__IRQ2_OFFSET)
HI_SET_GET(hi_pmu_no_pwr__irq2_hrst_usb_4p0_d3r,hrst_usb_4p0_d3r,HI_PMU_NO_PWR__IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR__IRQ2_OFFSET)
HI_SET_GET(hi_pmu_no_pwr__irq2_hrst_usb_6p0_d3r,hrst_usb_6p0_d3r,HI_PMU_NO_PWR__IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR__IRQ2_OFFSET)
HI_SET_GET(hi_pmu_no_pwr__irq2_hrst_vbus_4p0_d3f,hrst_vbus_4p0_d3f,HI_PMU_NO_PWR__IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR__IRQ2_OFFSET)
HI_SET_GET(hi_pmu_no_pwr__irq2_hrst_vbus_6p0_d3r,hrst_vbus_6p0_d3r,HI_PMU_NO_PWR__IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR__IRQ2_OFFSET)
HI_SET_GET(hi_pmu_no_pwr__irq2_hrst_vbus_6p0_d100r,hrst_vbus_6p0_d100r,HI_PMU_NO_PWR__IRQ2_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR__IRQ2_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq3_hrst_alarm_on_expenda,hrst_alarm_on_expenda,HI_PMU_NO_PWR_IRQ3_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ3_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq3_hrst_alarm_on_expendb,hrst_alarm_on_expendb,HI_PMU_NO_PWR_IRQ3_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ3_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq3_hrst_alarm_on_expendc,hrst_alarm_on_expendc,HI_PMU_NO_PWR_IRQ3_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ3_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_irq3_reserved,reserved,HI_PMU_NO_PWR_IRQ3_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_IRQ3_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_reg_rwc_otmp150_d3r,otmp150_d3r,HI_PMU_NO_PWR_REG_RWC_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_REG_RWC_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_reg_rwc_ilim_sht_pro_d3r,ilim_sht_pro_d3r,HI_PMU_NO_PWR_REG_RWC_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_REG_RWC_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_reg_rwc_reserved,reserved,HI_PMU_NO_PWR_REG_RWC_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_REG_RWC_OFFSET)
HI_SET_GET(hi_pmu_no_rwr_reg_rw_leak_ctl,leak_ctl,HI_PMU_NO_RWR_REG_RW_T,HI_PMU_BASE_ADDR, HI_PMU_NO_RWR_REG_RW_OFFSET)
HI_SET_GET(hi_pmu_no_rwr_reg_rw_rc_off,rc_off,HI_PMU_NO_RWR_REG_RW_T,HI_PMU_BASE_ADDR, HI_PMU_NO_RWR_REG_RW_OFFSET)
HI_SET_GET(hi_pmu_no_rwr_reg_rw_dr_fla_bre_ctrl,dr_fla_bre_ctrl,HI_PMU_NO_RWR_REG_RW_T,HI_PMU_BASE_ADDR, HI_PMU_NO_RWR_REG_RW_OFFSET)
HI_SET_GET(hi_pmu_no_rwr_reg_rw_reserved,reserved,HI_PMU_NO_RWR_REG_RW_T,HI_PMU_BASE_ADDR, HI_PMU_NO_RWR_REG_RW_OFFSET)
HI_SET_GET(hi_pmu_ana_in_ana_in_2d,ana_in_2d,HI_PMU_ANA_IN_T,HI_PMU_BASE_ADDR, HI_PMU_ANA_IN_OFFSET)
HI_SET_GET(hi_pmu_reserved0_reserved0,reserved0,HI_PMU_RESERVED0_T,HI_PMU_BASE_ADDR, HI_PMU_RESERVED0_OFFSET)
HI_SET_GET(hi_pmu_reserved1_reserved1,reserved1,HI_PMU_RESERVED1_T,HI_PMU_BASE_ADDR, HI_PMU_RESERVED1_OFFSET)
HI_SET_GET(hi_pmu_reserved2_reserved2,reserved2,HI_PMU_RESERVED2_T,HI_PMU_BASE_ADDR, HI_PMU_RESERVED2_OFFSET)
HI_SET_GET(hi_pmu_clim_adj_clim_ctl,clim_ctl,HI_PMU_CLIM_ADJ_T,HI_PMU_BASE_ADDR, HI_PMU_CLIM_ADJ_OFFSET)
HI_SET_GET(hi_pmu_clim_adj_clim_vth,clim_vth,HI_PMU_CLIM_ADJ_T,HI_PMU_BASE_ADDR, HI_PMU_CLIM_ADJ_OFFSET)
HI_SET_GET(hi_pmu_clim_adj_clim_op_isel,clim_op_isel,HI_PMU_CLIM_ADJ_T,HI_PMU_BASE_ADDR, HI_PMU_CLIM_ADJ_OFFSET)
HI_SET_GET(hi_pmu_lit_cur_set_lit_cur_set,lit_cur_set,HI_PMU_LIT_CUR_SET_T,HI_PMU_BASE_ADDR, HI_PMU_LIT_CUR_SET_OFFSET)
HI_SET_GET(hi_pmu_lit_cur_set_pro_mode,pro_mode,HI_PMU_LIT_CUR_SET_T,HI_PMU_BASE_ADDR, HI_PMU_LIT_CUR_SET_OFFSET)
HI_SET_GET(hi_pmu_lit_cur_set_vs,vs,HI_PMU_LIT_CUR_SET_T,HI_PMU_BASE_ADDR, HI_PMU_LIT_CUR_SET_OFFSET)
HI_SET_GET(hi_pmu_lit_cur_set_reserved,reserved,HI_PMU_LIT_CUR_SET_T,HI_PMU_BASE_ADDR, HI_PMU_LIT_CUR_SET_OFFSET)
HI_SET_GET(hi_pmu_otp_ctrl_otp_pwe_int,otp_pwe_int,HI_PMU_OTP_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_OTP_CTRL_OFFSET)
HI_SET_GET(hi_pmu_otp_ctrl_otp_por_int,otp_por_int,HI_PMU_OTP_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_OTP_CTRL_OFFSET)
HI_SET_GET(hi_pmu_otp_ctrl_otp_pa,otp_pa,HI_PMU_OTP_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_OTP_CTRL_OFFSET)
HI_SET_GET(hi_pmu_otp_ctrl_otp_ptm,otp_ptm,HI_PMU_OTP_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_OTP_CTRL_OFFSET)
HI_SET_GET(hi_pmu_otp_ctrl_otp_pprog,otp_pprog,HI_PMU_OTP_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_OTP_CTRL_OFFSET)
HI_SET_GET(hi_pmu_otp_ctrl_reserved,reserved,HI_PMU_OTP_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_OTP_CTRL_OFFSET)
HI_SET_GET(hi_pmu_otp_pdin_otp_pdin,otp_pdin,HI_PMU_OTP_PDIN_T,HI_PMU_BASE_ADDR, HI_PMU_OTP_PDIN_OFFSET)
HI_SET_GET(hi_pmu_otp_pdob0_otp_pdob0,otp_pdob0,HI_PMU_OTP_PDOB0_T,HI_PMU_BASE_ADDR, HI_PMU_OTP_PDOB0_OFFSET)
HI_SET_GET(hi_pmu_otp_pdob1_otp_pdob1,otp_pdob1,HI_PMU_OTP_PDOB1_T,HI_PMU_BASE_ADDR, HI_PMU_OTP_PDOB1_OFFSET)
HI_SET_GET(hi_pmu_otp_pdob2_otp_pdob2,otp_pdob2,HI_PMU_OTP_PDOB2_T,HI_PMU_BASE_ADDR, HI_PMU_OTP_PDOB2_OFFSET)
HI_SET_GET(hi_pmu_otp_pdob3_otp_pdob3,otp_pdob3,HI_PMU_OTP_PDOB3_T,HI_PMU_BASE_ADDR, HI_PMU_OTP_PDOB3_OFFSET)
HI_SET_GET(hi_pmu_bandgap_reg_sleep_bandgap,sleep_bandgap,HI_PMU_BANDGAP_REG_T,HI_PMU_BASE_ADDR, HI_PMU_BANDGAP_REG_OFFSET)
HI_SET_GET(hi_pmu_bandgap_reg_v0p59_sel,v0p59_sel,HI_PMU_BANDGAP_REG_T,HI_PMU_BASE_ADDR, HI_PMU_BANDGAP_REG_OFFSET)
HI_SET_GET(hi_pmu_bandgap_reg_sleep_ctrl1,sleep_ctrl1,HI_PMU_BANDGAP_REG_T,HI_PMU_BASE_ADDR, HI_PMU_BANDGAP_REG_OFFSET)
HI_SET_GET(hi_pmu_bandgap_reg_sleep_ctrl2,sleep_ctrl2,HI_PMU_BANDGAP_REG_T,HI_PMU_BASE_ADDR, HI_PMU_BANDGAP_REG_OFFSET)
HI_SET_GET(hi_pmu_bandgap_reg_reserved,reserved,HI_PMU_BANDGAP_REG_T,HI_PMU_BASE_ADDR, HI_PMU_BANDGAP_REG_OFFSET)
HI_SET_GET(hi_pmu_det_sd_level_cmd_cmd_sd_2d,cmd_sd_2d,HI_PMU_DET_SD_LEVEL_CMD_T,HI_PMU_BASE_ADDR, HI_PMU_DET_SD_LEVEL_CMD_OFFSET)
HI_SET_GET(hi_pmu_det_sd_level_cmd_reserved,reserved,HI_PMU_DET_SD_LEVEL_CMD_T,HI_PMU_BASE_ADDR, HI_PMU_DET_SD_LEVEL_CMD_OFFSET)
HI_SET_GET(hi_pmu_det_sd_level_status_state_sd_2d,state_sd_2d,HI_PMU_DET_SD_LEVEL_STATUS_T,HI_PMU_BASE_ADDR, HI_PMU_DET_SD_LEVEL_STATUS_OFFSET)
HI_SET_GET(hi_pmu_det_sd_level_status_reserved,reserved,HI_PMU_DET_SD_LEVEL_STATUS_T,HI_PMU_BASE_ADDR, HI_PMU_DET_SD_LEVEL_STATUS_OFFSET)
HI_SET_GET(hi_pmu_rtcdr0_rtcdr0,rtcdr0,HI_PMU_RTCDR0_T,HI_PMU_BASE_ADDR, HI_PMU_RTCDR0_OFFSET)
HI_SET_GET(hi_pmu_rtcdr1_rtcdr1,rtcdr1,HI_PMU_RTCDR1_T,HI_PMU_BASE_ADDR, HI_PMU_RTCDR1_OFFSET)
HI_SET_GET(hi_pmu_rtcdr2_rtcdr2,rtcdr2,HI_PMU_RTCDR2_T,HI_PMU_BASE_ADDR, HI_PMU_RTCDR2_OFFSET)
HI_SET_GET(hi_pmu_rtcdr3_rtcdr3,rtcdr3,HI_PMU_RTCDR3_T,HI_PMU_BASE_ADDR, HI_PMU_RTCDR3_OFFSET)
HI_SET_GET(hi_pmu_rtclr0_rtcclr0,rtcclr0,HI_PMU_RTCLR0_T,HI_PMU_BASE_ADDR, HI_PMU_RTCLR0_OFFSET)
HI_SET_GET(hi_pmu_rtclr1_rtcclr1,rtcclr1,HI_PMU_RTCLR1_T,HI_PMU_BASE_ADDR, HI_PMU_RTCLR1_OFFSET)
HI_SET_GET(hi_pmu_rtclr2_rtcclr2,rtcclr2,HI_PMU_RTCLR2_T,HI_PMU_BASE_ADDR, HI_PMU_RTCLR2_OFFSET)
HI_SET_GET(hi_pmu_rtclr3_rtcclr3,rtcclr3,HI_PMU_RTCLR3_T,HI_PMU_BASE_ADDR, HI_PMU_RTCLR3_OFFSET)
HI_SET_GET(hi_pmu_rtcctrl_rtccr,rtccr,HI_PMU_RTCCTRL_T,HI_PMU_BASE_ADDR, HI_PMU_RTCCTRL_OFFSET)
HI_SET_GET(hi_pmu_rtcctrl_reserved,reserved,HI_PMU_RTCCTRL_T,HI_PMU_BASE_ADDR, HI_PMU_RTCCTRL_OFFSET)
HI_SET_GET(hi_pmu_rtcmra0_rtcmra0,rtcmra0,HI_PMU_RTCMRA0_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRA0_OFFSET)
HI_SET_GET(hi_pmu_rtcmra1_rtcmra1,rtcmra1,HI_PMU_RTCMRA1_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRA1_OFFSET)
HI_SET_GET(hi_pmu_rtcmra2_rtcmra2,rtcmra2,HI_PMU_RTCMRA2_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRA2_OFFSET)
HI_SET_GET(hi_pmu_rtcmra3_rtcmra3,rtcmra3,HI_PMU_RTCMRA3_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRA3_OFFSET)
HI_SET_GET(hi_pmu_rtcmrb0_rtcmrb0,rtcmrb0,HI_PMU_RTCMRB0_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRB0_OFFSET)
HI_SET_GET(hi_pmu_rtcmrb1_rtcmrb1,rtcmrb1,HI_PMU_RTCMRB1_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRB1_OFFSET)
HI_SET_GET(hi_pmu_rtcmrb2_rtcmrb2,rtcmrb2,HI_PMU_RTCMRB2_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRB2_OFFSET)
HI_SET_GET(hi_pmu_rtcmrb3_rtcmrb3,rtcmrb3,HI_PMU_RTCMRB3_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRB3_OFFSET)
HI_SET_GET(hi_pmu_rtcmrc0_rtcmrc0,rtcmrc0,HI_PMU_RTCMRC0_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRC0_OFFSET)
HI_SET_GET(hi_pmu_rtcmrc1_rtcmrc1,rtcmrc1,HI_PMU_RTCMRC1_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRC1_OFFSET)
HI_SET_GET(hi_pmu_rtcmrc2_rtcmrc2,rtcmrc2,HI_PMU_RTCMRC2_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRC2_OFFSET)
HI_SET_GET(hi_pmu_rtcmrc3_rtcmrc3,rtcmrc3,HI_PMU_RTCMRC3_T,HI_PMU_BASE_ADDR, HI_PMU_RTCMRC3_OFFSET)
HI_SET_GET(hi_pmu_rtc_adj1_rtc_clk_setp_adj1,rtc_clk_setp_adj1,HI_PMU_RTC_ADJ1_T,HI_PMU_BASE_ADDR, HI_PMU_RTC_ADJ1_OFFSET)
HI_SET_GET(hi_pmu_rtc_adj2_rtc_clk_setp_adj2,rtc_clk_setp_adj2,HI_PMU_RTC_ADJ2_T,HI_PMU_BASE_ADDR, HI_PMU_RTC_ADJ2_OFFSET)
HI_SET_GET(hi_pmu_reserved3_reserved3,reserved3,HI_PMU_RESERVED3_T,HI_PMU_BASE_ADDR, HI_PMU_RESERVED3_OFFSET)
HI_SET_GET(hi_pmu_reserved4_reserved4,reserved4,HI_PMU_RESERVED4_T,HI_PMU_BASE_ADDR, HI_PMU_RESERVED4_OFFSET)
HI_SET_GET(hi_pmu_reserved5_reserved5,reserved5,HI_PMU_RESERVED5_T,HI_PMU_BASE_ADDR, HI_PMU_RESERVED5_OFFSET)
HI_SET_GET(hi_pmu_reserved6_reserved6,reserved6,HI_PMU_RESERVED6_T,HI_PMU_BASE_ADDR, HI_PMU_RESERVED6_OFFSET)
HI_SET_GET(hi_pmu_reserved7_reserved7,reserved7,HI_PMU_RESERVED7_T,HI_PMU_BASE_ADDR, HI_PMU_RESERVED7_OFFSET)
HI_SET_GET(hi_pmu_reserved8_reserved8,reserved8,HI_PMU_RESERVED8_T,HI_PMU_BASE_ADDR, HI_PMU_RESERVED8_OFFSET)
HI_SET_GET(hi_pmu_onoff10_sht_pro_off_ctrl,sht_pro_off_ctrl,HI_PMU_ONOFF10_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF10_OFFSET)
HI_SET_GET(hi_pmu_onoff10_reserved,reserved,HI_PMU_ONOFF10_T,HI_PMU_BASE_ADDR, HI_PMU_ONOFF10_OFFSET)
HI_SET_GET(hi_pmu_dr1_bre_ctrl_dr1_en_bre,dr1_en_bre,HI_PMU_DR1_BRE_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_BRE_CTRL_OFFSET)
HI_SET_GET(hi_pmu_dr1_bre_ctrl_dr1_flash_en,dr1_flash_en,HI_PMU_DR1_BRE_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_BRE_CTRL_OFFSET)
HI_SET_GET(hi_pmu_dr1_bre_ctrl_reserved,reserved,HI_PMU_DR1_BRE_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_BRE_CTRL_OFFSET)
HI_SET_GET(hi_pmu_dr1_tim_conf1_dr1_t_off,dr1_t_off,HI_PMU_DR1_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr1_tim_conf1_reserved_1,reserved_1,HI_PMU_DR1_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr1_tim_conf1_dr1_t_on,dr1_t_on,HI_PMU_DR1_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr1_tim_conf1_reserved_0,reserved_0,HI_PMU_DR1_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr1_tim_conf2_dr1_t_rise,dr1_t_rise,HI_PMU_DR1_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_dr1_tim_conf2_reserved_1,reserved_1,HI_PMU_DR1_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_dr1_tim_conf2_dr1_t_fall,dr1_t_fall,HI_PMU_DR1_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_dr1_tim_conf2_reserved_0,reserved_0,HI_PMU_DR1_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR1_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_dr2_bre_ctrl_dr2_en_bre,dr2_en_bre,HI_PMU_DR2_BRE_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_BRE_CTRL_OFFSET)
HI_SET_GET(hi_pmu_dr2_bre_ctrl_dr2_flash_en,dr2_flash_en,HI_PMU_DR2_BRE_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_BRE_CTRL_OFFSET)
HI_SET_GET(hi_pmu_dr2_bre_ctrl_reserved,reserved,HI_PMU_DR2_BRE_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_BRE_CTRL_OFFSET)
HI_SET_GET(hi_pmu_dr2_tim_conf1_dr2_t_off,dr2_t_off,HI_PMU_DR2_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr2_tim_conf1_reserved_1,reserved_1,HI_PMU_DR2_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr2_tim_conf1_dr2_t_on,dr2_t_on,HI_PMU_DR2_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr2_tim_conf1_reserved_0,reserved_0,HI_PMU_DR2_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr2_tim_conf2_dr2_t_rise,dr2_t_rise,HI_PMU_DR2_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_dr2_tim_conf2_reserved_1,reserved_1,HI_PMU_DR2_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_dr2_tim_conf2_dr2_t_fall,dr2_t_fall,HI_PMU_DR2_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_dr2_tim_conf2_reserved_0,reserved_0,HI_PMU_DR2_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR2_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_dr3_bre_ctrl_d3_en,d3_en,HI_PMU_DR3_BRE_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_BRE_CTRL_OFFSET)
HI_SET_GET(hi_pmu_dr3_bre_ctrl_dr3_flash_en,dr3_flash_en,HI_PMU_DR3_BRE_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_BRE_CTRL_OFFSET)
HI_SET_GET(hi_pmu_dr3_bre_ctrl_reserved,reserved,HI_PMU_DR3_BRE_CTRL_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_BRE_CTRL_OFFSET)
HI_SET_GET(hi_pmu_dr3_tim_conf1_dr3_t_off,dr3_t_off,HI_PMU_DR3_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr3_tim_conf1_reserved_1,reserved_1,HI_PMU_DR3_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr3_tim_conf1_dr3_t_on,dr3_t_on,HI_PMU_DR3_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr3_tim_conf1_reserved_0,reserved_0,HI_PMU_DR3_TIM_CONF1_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_pmu_dr3_tim_conf2_dr3_t_rise,dr3_t_rise,HI_PMU_DR3_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_dr3_tim_conf2_reserved_1,reserved_1,HI_PMU_DR3_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_dr3_tim_conf2_dr3_t_fall,dr3_t_fall,HI_PMU_DR3_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_dr3_tim_conf2_reserved_0,reserved_0,HI_PMU_DR3_TIM_CONF2_T,HI_PMU_BASE_ADDR, HI_PMU_DR3_TIM_CONF2_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_rsved1_no_pwr_resved1,no_pwr_resved1,HI_PMU_NO_PWR_RSVED1_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_RSVED1_OFFSET)
HI_SET_GET(hi_pmu_no_pwr_rsved2_no_pwr_resved2,no_pwr_resved2,HI_PMU_NO_PWR_RSVED2_T,HI_PMU_BASE_ADDR, HI_PMU_NO_PWR_RSVED2_OFFSET)

#endif // __HI_PMU_H__

