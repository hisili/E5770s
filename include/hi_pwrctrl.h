/******************************************************************************/
/*  Copyright (C), 2007-2014, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_pwrctrl.h */
/* Version       : 2.0 */
/* Author        : xxx*/
/* Created       : 2014-02-18*/
/* Last Modified : */
/* Description   :  The C union definition file for the module pwrctrl*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Author        : xxx*/
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_PWRCTRL_H__
#define __HI_PWRCTRL_H__

/*
 * Project: hi
 * Module : pwrctrl
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    pwrctrl �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_PWR_CTRL0_OFFSET                               (0xC00) /* ϵͳģʽ���� */
#define    HI_PWR_CTRL1_OFFSET                               (0xC04) /* �ж�ģʽ���� */
#define    HI_PWR_CTRL2_OFFSET                               (0xC08) /* TCXO ���� */
#define    HI_PWR_CTRL3_OFFSET                               (0xC0C) /* PLL ���� */
#define    HI_PWR_CTRL4_OFFSET                               (0xC10) /* ISO cell ����ʹ�� */
#define    HI_PWR_CTRL5_OFFSET                               (0xC14) /* ISO cell �����ֹ */
#define    HI_PWR_CTRL6_OFFSET                               (0xC18) /* MTCMOS �ϵ���� */
#define    HI_PWR_CTRL7_OFFSET                               (0xC1C) /* MTCMOS �µ���� */
#define    HI_PWR_CTRL8_OFFSET                               (0xC20) /* CM3 ���µ綨ʱ���� */
#define    HI_PWR_CTRL9_OFFSET                               (0xC24) /* �������µ���� */
#define    HI_PWR_CTRL10_OFFSET                              (0xC28) /* Retention memory �ϵ���� */
#define    HI_PWR_CTRL11_OFFSET                              (0xC2C) /* Retention memory �µ���� */
#define    HI_PWR_CTRL12_OFFSET                              (0xC30) /* Retention Meory �͹��Ŀ��� */
#define    HI_PWR_CTRL13_OFFSET                              (0xC34) /* PMU���ƼĴ��� */
#define    HI_PWR_CTRL14_OFFSET                              (0xC38) /* sleephold���� */
#define    HI_PWR_CTRL15_OFFSET                              (0xC3C) /* USB���ѿ��� */
#define    HI_PWR_CTRL16_OFFSET                              (0xC40) /* Cortex_M3 �����ж�ʹ��0 */
#define    HI_PWR_CTRL17_OFFSET                              (0xC44) /* Cortex_M3 �����ж�ʹ��1 */
#define    HI_PWR_CTRL18_OFFSET                              (0xC48) /* Cortex_M3 �����ж�ʹ��2 */
#define    HI_PWR_CTRL19_OFFSET                              (0xC4C) /* Cortex_M3 �����ж�ʹ��3 */
#define    HI_PWR_CTRL20_OFFSET                              (0xC50) /* �����Ĵ��� */
#define    HI_PWR_CTRL21_OFFSET                              (0xC54) /* �����Ĵ��� */
#define    HI_PWR_STAT0_OFFSET                               (0xE00) /* pwrctrl ״̬ */
#define    HI_PWR_STAT1_OFFSET                               (0xE04) /* MTCMOS rdy״̬ */
#define    HI_PWR_STAT2_OFFSET                               (0xE08) /* PLL/XTAL ������ */
#define    HI_PWR_STAT3_OFFSET                               (0xE0C) /* ISO cell ����״̬ */
#define    HI_PWR_STAT4_OFFSET                               (0xE10) /* MTCMOS ����״̬ */
#define    HI_PWR_STAT5_OFFSET                               (0xE14) /* retmem_ctrl */
#define    HI_PWR_STAT6_OFFSET                               (0xE18) /* �ж�λ�üĴ��� */
#define    HI_PWR_STAT7_OFFSET                               (0xE1C) /* CM3 �����ж�״̬0 */
#define    HI_PWR_STAT8_OFFSET                               (0xE20) /* CM3 �����ж�״̬1 */
#define    HI_PWR_STAT9_OFFSET                               (0xE24) /* CM3 �����ж�״̬2 */
#define    HI_PWR_STAT10_OFFSET                              (0xE28) /* CM3 �����ж�״̬3 */
#define    HI_PWR_STAT11_OFFSET                              (0xE2C) /* �����Ĵ��� */
#define    HI_PWR_STAT12_OFFSET                              (0xE30) /* �����Ĵ��� */
#define    HI_CM3_PWRCTRL0_OFFSET                            (0x44000) /* ISO cell ����ʹ�� */
#define    HI_CM3_PWRCTRL1_OFFSET                            (0x44004) /* ISO cell �����ֹ */
#define    HI_CM3_ISO_STAT_OFFSET                            (0x44008) /* CM3 ISO cell ����״̬ */
#define    HI_CM3_PWRCTRL2_OFFSET                            (0x44010) /* MTCMOS �ϵ���� */
#define    HI_CM3_PWRCTRL3_OFFSET                            (0x44014) /* MTCMOS �µ���� */
#define    HI_CM3_MTCMOS_STAT_OFFSET                         (0x44018) /* CM3 MTCMOS ����״̬ */
#define    HI_CM3_PWRCTRL4_OFFSET                            (0x44020) /* CM3���Ŀ��ƼĴ��� */
#define    HI_CM3_PWRSTAT0_OFFSET                            (0x44040) /* PWRCTRL MTCMOS ����״̬ */
#define    HI_CM3_PWRSTAT1_OFFSET                            (0x44044) /* PWRCTRL ISO cell ����״̬ */
#define    HI_CM3_DEBUG_STAT_OFFSET                          (0x44048) /* debug ״̬ */


#ifndef __ASSEMBLY__

/********************************************************************************/
/*    pwrctrl �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    cpumode_ctrl               : 3; /* [2..0] CPUģʽ����λ������Ҫ��ϵͳ����������Ĳ���ģʽ��000��sleep��001��doze��010��slow��100��normal����cortex_M3��SLEEP״̬������DOZE״̬ʱ���üĴ����ᱻӲ����Ϊ001��cortex_M3��SLEEP״̬������SLOW״̬ʱ���üĴ����ᱻӲ����Ϊ010����������£������������д�üĴ��� */
        unsigned int    a9_cpumode_status          : 4; /* [6..3] CPUģʽ״̬λ�����巵��ϵͳ������״̬����ǰ�Ĳ���ģʽ��0000��sleep��0001��doze��0010��slow��0011��XTAL CTL��0100��normal��0101��normal WFI��1000��deep sleep��0110��PLL CTL��0111��slow WFI��1001��SW from XTAL��1010��SW from PLL��1011��SW to XTAL��1110��SW to PLL�������������� */
        unsigned int    reserved_1                 : 3; /* [9..7] ���� */
        unsigned int    cpu_dsleep_en              : 1; /* [10..10] CPU����SLEEPģʽʱ�Ƿ���硣0��CPU�����磬����Ŀǰ��ѹ��1��CPU���磬����Deep Sleepģʽ�� */
        unsigned int    reserved_0                 : 11; /* [21..11] ���� */
        unsigned int    doze_es_skip               : 1; /* [22..22] ��ϵͳ����SLEEPģʽ�Ƿ����doze״̬��0����DOZE״̬����SLEEP��1������DOZE״ֱ̬�ӽ���SLEEP�� */
        unsigned int    doze_wk_skip               : 1; /* [23..23] ��ϵͳ��SLEEPģʽ���Ѻ��Ƿ����doze״̬��0�����Ѻ����DOZE״̬��1�����Ѻ����SLOW�� */
        unsigned int    cm3_sleephold_en           : 1; /* [24..24] cortex_M3��sleephold���ܿ��ء�0����ʹ��sleephold����1��ʹ��sleephold���� */
        unsigned int    cm3_sleeping_en            : 1; /* [25..25] cortex_M3��sleeping�ź��Ƿ�ʹ��0��sleeping�Ƿ���Ч������Ӱ���ڲ�״̬������ת��1��sleeping�ź���Чʱ���ڲ�״̬������ת��WFI����SLEEP�ȵ͹���״̬�� */
        unsigned int    cm3_sleepdeep_en           : 1; /* [26..26] cortex_M3��sleepdeep�ź��Ƿ�ʹ��0��sleepdeep�Ƿ���Ч������Ӱ���ڲ�״̬������ת��1��sleepdeep�ź���Чʱ���ڲ�״̬������ת��WFI����SLEEP�ȵ͹���״̬�� */
        unsigned int    arm_dsleep_rst_en          : 1; /* [27..27] ���ƽ�DSLEEPʱ�Ƿ�λCortex_M3��0����DSLEEP����λCortex_M31����DSLEEP��λCortex_M3 */
        unsigned int    usb_irq_glitch_free        : 1; /* [28..28] usb�ж��ź���ë�̿����źš�0������usb�ж��źŹ���1��ֻ��һ��ʱ�����ڵ�usb�ж��źŽ������˵��� */
        unsigned int    io_ret_value_sel           : 1; /* [29..29] io_retention��ISOֵ����idleֵ̬ѡ���źš�                             0����idleֵ̬                         1����ISOֵ */
        unsigned int    arm_boot_type              : 1; /* [30..30] ϵͳ ����������־�Ĵ�����0����������1������������ϵͳ״̬������DSLEEP״̬��Ӳ���Ὣ��bit��1������ʱ�̣�����ɶ���д��. */
        unsigned int    sys_sleep_flag             : 1; /* [31..31] ϵͳ ����sleepģʽ��־�Ĵ�����0��û�н���sleepģʽ��1�������sleepģʽ����ϵͳ״̬������SLEEP״̬��Ӳ���Ὣ��bit��1������ʱ�̣�����ɶ���д��. */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL0_T;    /* ϵͳģʽ���� */

typedef union
{
    struct
    {
        unsigned int    sys_intmod_en              : 1; /* [0..0] ϵͳ�ж�ģʽʹ��λ��0���ر��ж�ģʽ��1�����ж���Чʱ�����ж�ģʽ�� */
        unsigned int    sys_intmod_ctrl            : 3; /* [3..1] �����ж�ģʽ��ϵͳ����ģʽ����ֵ��cpumode_ctrl��ֵ������Ϊ�жϷ�����ϵͳ�����Ĺ���ģʽ�� */
        unsigned int    reserved_1                 : 1; /* [4..4] ���� */
        unsigned int    sys_intmod_stat            : 1; /* [5..5] �ж�ģʽ����/״̬λ��0����ǰδ�����ж�ģʽ��1����ǰ�����ж�ģʽ����ϵͳ�����ж�ģʽ��Ӳ���Ὣ��bit��1��ͬʱ���������ͨ����λ���ƽ�����˳��ж�ģʽ��д0����ʾ�˳��ж�ģʽд1����ʾ������������ж�ģʽ */
        unsigned int    reserved_0                 : 26; /* [31..6] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL1_T;    /* �ж�ģʽ���� */

typedef union
{
    struct
    {
        unsigned int    tcxo_time                  : 16; /* [15..0] TCXO TimeOut Timer��ֵ�Ĵ�������Timer�ӳ�ֵ������16��hFFFʱ���ᷢ��TimerOut�ź� */
        unsigned int    soc_tcxo_over              : 1; /* [16..16] soc tcxo����ѡ��1����ʾsoc tcxoʱ�����������0����ʾsoc tcxoʱ�����߼����ƣ�״̬������DOZE��SLEEP��DEEP SLEEPʱ�߼���ر�soc tcxoʱ�ӣ� */
        unsigned int    reserved_1                 : 1; /* [17..17]  */
        unsigned int    sleep_tcxo_off             : 1; /* [18..18] ��soc tcxo״̬��״̬������ʱ��soc_tcxo_overΪ0����ϵͳ����SLEEP״̬ʱ���Ƿ�ض�SOC TCXO��0�����ض�soc tcxo��1���ض�soc tcxo�� */
        unsigned int    soc_tcxo_on                : 1; /* [19..19] soc tcxoʱ���Ƿ�ʹ�ܡ�0����ʾsoc tcxoʱ�ӹر�1����ʾsoc tcxoʱ�Ӵ� */
        unsigned int    abb_ch0_tcxo_en            : 1; /* [20..20] gul tcxo���ʹ�ܣ���gul_tcxoΪsoc tcxoʱ��ʱ����CRG_CTRL12[SOCPLL_REFCLK_SEL]�����ñ���Ϊ1����soc_tcxo_onΪ1ʱgul tcxoʱ����Ч���ñ���Ϊ0��soc_tcxo_onҲΪ0ʱgul tcxoʱ�Ӳű��رգ���lte_tcxoΪsoc tcxoʱ��ʱ��gul tcxo�������ɸñ��ؿ��ƣ�1��ʾʱ�Ӵ򿪣�0��ʾʱ�ӹرգ��� */
        unsigned int    abb_ch1_tcxo_en            : 1; /* [21..21] lte tcxo���ʹ�ܣ���lte_tcxoΪsoc tcxoʱ��ʱ����CRG_CTRL12[SOCPLL_REFCLK_SEL]�����ñ���Ϊ1����soc_tcxo_onΪ1ʱlte tcxoʱ����Ч���ñ���Ϊ0��soc_tcxo_onҲΪ0ʱlte tcxoʱ�Ӳű��رգ���gul_tcxoΪsoc tcxoʱ��ʱ��lte tcxo�������ɸñ��ؿ��ƣ�1��ʾʱ�Ӵ򿪣�0��ʾʱ�ӹرգ��� */
        unsigned int    pmu_ch0_tcxo_en            : 1; /* [22..22] gul tcxo���ʹ�ܣ���gul_tcxoΪsoc tcxoʱ��ʱ����CRG_CTRL12[SOCPLL_REFCLK_SEL]�����ñ���Ϊ1����soc_tcxo_onΪ1ʱgul tcxoʱ����Ч���ñ���Ϊ0��soc_tcxo_onҲΪ0ʱgul tcxoʱ�Ӳű��رգ���lte_tcxoΪsoc tcxoʱ��ʱ��gul tcxo�������ɸñ��ؿ��ƣ�1��ʾʱ�Ӵ򿪣�0��ʾʱ�ӹرգ��� */
        unsigned int    pmu_ch1_tcxo_en            : 1; /* [23..23] lte tcxo���ʹ�ܣ���lte_tcxoΪsoc tcxoʱ��ʱ����CRG_CTRL12[SOCPLL_REFCLK_SEL]�����ñ���Ϊ1����soc_tcxo_onΪ1ʱlte tcxoʱ����Ч���ñ���Ϊ0��soc_tcxo_onҲΪ0ʱlte tcxoʱ�Ӳű��رգ���gul_tcxoΪsoc tcxoʱ��ʱ��lte tcxo�������ɸñ��ؿ��ƣ�1��ʾʱ�Ӵ򿪣�0��ʾʱ�ӹرգ��� */
        unsigned int    pmu_abb_tcxo_time          : 4; /* [27..24] ״̬�������µ�ʱ����pmu��tcxo_en����abb��tcxo_en��ʱ�Ӽ��������pmu_abb_time_en=1ʱ�����á�                                     0�����1��ʱ��cycle                         1�����2��ʱ��cycle                         ������                                       15�����16��ʱ��cycle */
        unsigned int    pmu_abb_time_en            : 1; /* [28..28] ״̬�������µ�ʱ����pmu��tcxo_en����abb��tcxo_en��ʱ�Ӽ������ʹ�ܡ�                  0��������ֹ��pmu��abb��tcxo_enһ������      1������ʹ�ܣ�ʱ�Ӽ����pmu_abb_tcxo_time */
        unsigned int    pmu_tcxo_en_stat           : 1; /* [29..29] ״̬������ʱpmu tcxo�����Ƿ�ʹ�ܡ�0����ʾpmu tcxo���عر�1����ʾpmu tcxo���ش� */
        unsigned int    reserved_0                 : 2; /* [31..30] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL2_T;    /* TCXO ���� */

typedef union
{
    struct
    {
        unsigned int    pll_time                   : 25; /* [24..0] CPU PLL TimeOut Timer��ֵ�Ĵ�������Timer�ӳ�ֵ������25��h1FF_FFFʱ���ᷢ��TimerOut�źš� */
        unsigned int    pll_time_en                : 1; /* [25..25] �ȴ�PLL������ʱ��ʹ�ܡ�0����ʱ����ʹ�ܣ�1����ʱ��ʹ�ܣ� */
        unsigned int    pll_status                 : 1; /* [26..26] PLL�Ƿ�����״̬�źš�0��APP A9 PLLδ������1��APP A9 PLL������ */
        unsigned int    reserved                   : 5; /* [31..27] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL3_T;    /* PLL ���� */

typedef union
{
    struct
    {
        unsigned int    appa9_iso_en               : 1; /* [0..0] APPA9�������ISO CELL���ʹ���źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    moda9_iso_en               : 1; /* [1..1] MODA9�������ISO CELL���ʹ���źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    reserved_3                 : 1; /* [2..2] ���� */
        unsigned int    hisc_iso_en                : 1; /* [3..3] HSIC�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    dsp0_iso_en                : 1; /* [4..4] DSP0�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    hifi_iso_en                : 1; /* [5..5] HIFI�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    lbbp_iso_en                : 1; /* [6..6] LBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    twbbp_iso_en               : 1; /* [7..7] TWBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    wbbp_iso_en                : 1; /* [8..8] WBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    g1bbp_iso_en               : 1; /* [9..9] G1BBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    g2bbp_iso_en               : 1; /* [10..10] G2BBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    irm_iso_en                 : 1; /* [11..11] IRM�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    usb_iso_en                 : 1; /* [12..12] USB�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    sd_iso_en                  : 1; /* [13..13] SD �������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    reserved_2                 : 8; /* [21..14] ���� */
        unsigned int    io_ddr_ret                 : 1; /* [22..22] DDR �� IO ��retention�����źš�0����Ӱ��1��ret�ź�ʹ�� */
        unsigned int    reserved_1                 : 3; /* [25..23]  */
        unsigned int    io_ret_lp_ctrl             : 4; /* [29..26] IO��retention�����źš���ӦbitΪ0����Ӱ���ӦbitΪ1��ret�ź�ʹ�� */
        unsigned int    reserved_0                 : 2; /* [31..30] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL4_T;    /* ISO cell ����ʹ�� */

typedef union
{
    struct
    {
        unsigned int    appa9_iso_dis              : 1; /* [0..0] APPA9�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    moda9_iso_dis              : 1; /* [1..1] MODA9�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    reserved_3                 : 1; /* [2..2] ���� */
        unsigned int    hisc_iso_dis               : 1; /* [3..3] HSIC�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    dsp0_iso_dis               : 1; /* [4..4] DSP0�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    hifi_iso_dis               : 1; /* [5..5] HIFI�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    lbbp_iso_dis               : 1; /* [6..6] LBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    twbbp_iso_dis              : 1; /* [7..7] TWBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    wbbp_iso_dis               : 1; /* [8..8] WBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    g1bbp_iso_dis              : 1; /* [9..9] G1BBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    g2bbp_iso_dis              : 1; /* [10..10] G2BBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    irm_iso_dis                : 1; /* [11..11] IRM�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    usb_iso_dis                : 1; /* [12..12] USB�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    sd_iso_dis                 : 1; /* [13..13] SD �������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    reserved_2                 : 8; /* [21..14] ���� */
        unsigned int    io_ddr_ret                 : 1; /* [22..22] DDR �� IO ��retention�����źš�0����Ӱ��1��ret�źŽ�ֹ */
        unsigned int    reserved_1                 : 3; /* [25..23]  */
        unsigned int    io_ret_lp_ctrl             : 4; /* [29..26] IO��retention�����źš���ӦbitΪ0����Ӱ���ӦbitΪ1��ret�źŽ�ֹ */
        unsigned int    reserved_0                 : 2; /* [31..30] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL5_T;    /* ISO cell �����ֹ */

typedef union
{
    struct
    {
        unsigned int    appa9_mtcmos_en            : 1; /* [0..0] APP A9 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    moda9_mtcmos_en            : 1; /* [1..1] MOD A9 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    reserved_1                 : 1; /* [2..2]  */
        unsigned int    hisc_mtcmos_en             : 1; /* [3..3] HSIC MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    dsp0_mtcmos_en             : 1; /* [4..4] DSP0 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    hifi_mtcmos_en             : 1; /* [5..5] HIFI MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    lbbp_mtcmos_en             : 1; /* [6..6] LBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    twbbp_mtcmos_en            : 1; /* [7..7] TWBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    wbbp_mtcmos_en             : 1; /* [8..8] WBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    g1bbp_mtcmos_en            : 1; /* [9..9] G1BBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    g2bbp_mtcmos_en            : 1; /* [10..10] G2BBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    irm_mtcmos_en              : 1; /* [11..11] IRM MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    usb_mtcmos_en              : 1; /* [12..12] USB MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    sd_mtcmos_en               : 1; /* [13..13] SD MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    reserved_0                 : 18; /* [31..14] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL6_T;    /* MTCMOS �ϵ���� */

typedef union
{
    struct
    {
        unsigned int    appa9_mtcmos_dis           : 1; /* [0..0] APP A9 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    moda9_mtcmos_dis           : 1; /* [1..1] MOD A9 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    reserved_1                 : 1; /* [2..2]  */
        unsigned int    hisc_mtcmos_dis            : 1; /* [3..3] HSIC MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    dsp0_mtcmos_dis            : 1; /* [4..4] DSP0 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    hifi_mtcmos_dis            : 1; /* [5..5] HIFI MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    lbbp_mtcmos_dis            : 1; /* [6..6] LBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    twbbp_mtcmos_dis           : 1; /* [7..7] TWBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    wbbp_mtcmos_dis            : 1; /* [8..8] WBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    g1bbp_mtcmos_dis           : 1; /* [9..9] G1BBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    g2bbp_mtcmos_dis           : 1; /* [10..10] G2BBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    irm_mtcmos_dis             : 1; /* [11..11] IRM MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    usb_mtcmos_dis             : 1; /* [12..12] USB MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    sd_mtcmos_dis              : 1; /* [13..13] SD MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    reserved_0                 : 18; /* [31..14] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL7_T;    /* MTCMOS �µ���� */

typedef union
{
    struct
    {
        unsigned int    cpu_pwrup_time             : 12; /* [11..0] Cortex_M3 �ϵ綨ʱ����ֵ����Timer�ӳ�ֵ������12��hFFFʱ���ᷢ��TimerOut�źš� */
        unsigned int    reserved_1                 : 4; /* [15..12] ���� */
        unsigned int    cpu_pwrdn_time             : 12; /* [27..16] Cortex_M3 �µ綨ʱ����ֵ����Timer�ӳ�ֵ������12��hFFFʱ���ᷢ��TimerOut�źš� */
        unsigned int    cpu_pwrtime_en             : 1; /* [28..28] Cortex_M3 ���µ綨ʱ��ʹ�ܡ�0��Cortex_M3 ���µ��Ƿ���ɲ��Զ�ʱ��timeoutΪ��־��1��Cortex_M3 ���µ��Ƿ���ɿ���ʱ��timeoutָʾ�� */
        unsigned int    reserved_0                 : 3; /* [31..29] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL8_T;    /* CM3 ���µ綨ʱ���� */

typedef union
{
    struct
    {
        unsigned int    peri_pwrup_time            : 12; /* [11..0] ��ͨ�������ϵ綨ʱ����ֵ����Timer�ӳ�ֵ������12��hFFFʱ���ᷢ��TimerOut�źš� */
        unsigned int    reserved_1                 : 4; /* [15..12] ���� */
        unsigned int    peri_pwrdn_time            : 12; /* [27..16] ��ͨ�������µ綨ʱ����ֵ����Timer�ӳ�ֵ������12��hFFFʱ���ᷢ��TimerOut�źš� */
        unsigned int    peri_pwrtime_en            : 1; /* [28..28] �ȴ���ͨ���������µ綨ʱ��ʹ�ܡ�0����ͨ���������µ��Ƿ���ɲ��Զ�ʱ��timeoutΪ��־��1����ͨ���������µ��Ƿ���ɿ���ʱ��timeoutָʾ�� */
        unsigned int    dsleep_peri_pwrdn          : 1; /* [29..29] ��ͨ��������DSLEEPʱ����ģʽ��0����ͨ�����������磻1����ͨ���������硣 */
        unsigned int    sleep_periclk_en           : 1; /* [30..30] ��Cortex_M3˯��ʱ������ʱ�ӵ�״̬���ơ�0������ʱ�ӹر�1������ʱ�Ӳ��ر� */
        unsigned int    reserved_0                 : 1; /* [31..31] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL9_T;    /* �������µ���� */

typedef union
{
    struct
    {
        unsigned int    retmem_nor_time            : 25; /* [24..0] Retention Memory���ϵ綨ʱ����ֵ����Timer�ӳ�ֵ������25��h1FF_FFFʱ���ᷢ��TimerOut�źš��������ʱ����Ϊһ���ϴ��ֵ���������Ϊ����ʹ�÷���ʱ��ܳ��� */
        unsigned int    reserved                   : 7; /* [31..25] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL10_T;    /* Retention memory �ϵ���� */

typedef union
{
    struct
    {
        unsigned int    retmem_ret_time            : 25; /* [24..0] Retention Memory���µ綨ʱ���ȴ�ʱ�䡣��Timer�ӳ�ֵ������25��h1FF_FFFʱ���ᷢ��TimerOut�źš��������ʱ����Ϊһ���ϴ��ֵ���������Ϊ����ʹ�÷���ʱ��ܳ��� */
        unsigned int    reserved                   : 7; /* [31..25] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL11_T;    /* Retention memory �µ���� */

typedef union
{
    struct
    {
        unsigned int    ema                        : 3; /* [2..0] memory�����ʿ��ƣ����ֵ������memory����ʱ���� */
        unsigned int    reserved_3                 : 1; /* [3..3] ���� */
        unsigned int    emaw                       : 2; /* [5..4] memoryд���ʿ��ƣ����ֵ������memoryд��ʱ���� */
        unsigned int    emas                       : 1; /* [6..6] ��memory��emas���� */
        unsigned int    reserved_2                 : 3; /* [9..7] ���� */
        unsigned int    retmem_ret1n_cfg           : 1; /* [10..10] retention memory ����ʡ��ģʽ��RET1N �źſ��ơ� */
        unsigned int    retmem_ret2n_cfg           : 1; /* [11..11] retention memory ����ʡ��ģʽ��RET2N �źſ��ơ� */
        unsigned int    retmem_pgen_cfg            : 1; /* [12..12] retention memory ����ʡ��ģʽ��PGEN �źſ��ơ� */
        unsigned int    reserved_1                 : 3; /* [15..13] ���� */
        unsigned int    retmem_sw_lp_ctrl          : 1; /* [16..16] �����retention Memory���ĵ�Դ�������������ʹ�ܣ���bitֻ�ܿ���APP ��Modem A9 ���ڹ���״̬ʱAXI Memory���Ĺ���ģʽ��д1������LS/DS/SD״̬д0������Normal״̬ */
        unsigned int    dsleep_retmem_ret          : 1; /* [17..17] retention Memory����״̬������ sleepʱ����ģʽ��0��retention Memory������ Normal״̬��1��retention Memory������ʡ��ģʽ�� */
        unsigned int    reserved_0                 : 14; /* [31..18] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL12_T;    /* Retention Meory �͹��Ŀ��� */

typedef union
{
    struct
    {
        unsigned int    pmu_pwrup_time             : 12; /* [11..0] PMU�ϵ綨ʱ����ֵ��PMU����ʹ�ܣ�dsleep_pmu_pwrdn=1��ʱ����ϵͳ��dsleep���ѣ��˼�������ʼ��������Timer�ӳ�ֵ������12��hFFFʱ���ᷢ��TimerOut�źš� */
        unsigned int    reserved_1                 : 4; /* [15..12]  */
        unsigned int    dsleep_pmu_pwrdn           : 1; /* [16..16] PMU��DSLEEPʱ����ģʽ��0��PMU�����磻1��PMU���硣 */
        unsigned int    sleep_pmuclk_en            : 1; /* [17..17] ��Cortex_M3˯��ʱ��PMUʱ�ӵ�״̬���ơ�0��PMUʱ�ӹر�1��PMUʱ�Ӳ��ر� */
        unsigned int    reserved_0                 : 14; /* [31..18]  */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL13_T;    /* PMU���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    sleep_hold_cycle           : 16; /* [15..0] ��ʾsleephold��Ҫ�ӳٵ�cycle���� */
        unsigned int    sleephole_cnt              : 16; /* [31..16] ��ʾsleephold����ֵ������ǰ�Ѿ��ӳٵ�cycle���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL14_T;    /* sleephold���� */

typedef union
{
    struct
    {
        unsigned int    moda9_usbwkup_en           : 1; /* [0..0] USB ���� Modem A9ʹ���źţ�����Ч�� */
        unsigned int    appa9_usbwkup_en           : 1; /* [1..1] USB ���� APP A9ʹ���źţ�����Ч�� */
        unsigned int    a9_otgphy_wkup_en          : 8; /* [9..2] utmiotg_iddig 0 ����  A9ʹ���źţ�����Ч�� */
        unsigned int    a9_otgsuspend_wkup_en      : 3; /* [12..10] utmiotg_iddig 1 ����  A9ʹ���źţ�����Ч�� */
        unsigned int    otgawson_wpc_clk_en        : 1; /* [13..13] utmiotg_bvalid 0 ����  A9ʹ���źţ�����Ч�� */
        unsigned int    reserved_1                 : 2; /* [15..14] ���� */
        unsigned int    sleep_usbwkup_en           : 1; /* [16..16] USB PHY�ж���Ϊ��sleep���ѵ��ж�Դʹ�ܡ�         0��USB PHY �жϻ���sleep��ֹ                       1��USB PHY �жϻ���sleepʹ�� */
        unsigned int    reserved_0                 : 15; /* [31..17] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL15_T;    /* USB���ѿ��� */

typedef union
{
    struct
    {
        unsigned int    cm3_irqs_en_31_0           : 32; /* [31..0] Cortex_M3 �����ж�ʹ��bit31-bit0�� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL16_T;    /* Cortex_M3 �����ж�ʹ��0 */

typedef union
{
    struct
    {
        unsigned int    cm3_irqs_en_63_32          : 32; /* [31..0] Cortex_M3 �����ж�ʹ��bit63-bit32�� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL17_T;    /* Cortex_M3 �����ж�ʹ��1 */

typedef union
{
    struct
    {
        unsigned int    cm3_irqs_en_95_64          : 32; /* [31..0] Cortex_M3 �����ж�ʹ��bit95-bit64�� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL18_T;    /* Cortex_M3 �����ж�ʹ��2 */

typedef union
{
    struct
    {
        unsigned int    cm3_irqs_en_127_96         : 32; /* [31..0] Cortex_M3 �����ж�ʹ��bit127-bit96�� */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL19_T;    /* Cortex_M3 �����ж�ʹ��3 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL20_T;    /* �����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_PWR_CTRL21_T;    /* �����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    cpu_volt_fsm               : 4; /* [3..0] ��ѹ����״̬����״̬��4'h0����ѹ����4'h1��CPU���ǯλ4'h2��CPU����4'h3���������4'h4�������ϵ�4'h5��CPU�ϵ�4'h6��CPU���ǯλ����4'h7��CPU�����趼����4'h8��RETMEM�������͹���״̬4'h9��RETMEM�����������״̬������������ */
        unsigned int    cpu_pwrup_timeout          : 1; /* [4..4] �ȴ�Modem A9�ϵ綨ʱ����ʱ��0����ʱ��û�г�ʱ��1����ʱ����ʱ�� */
        unsigned int    cpu_pwrdn_timeout          : 1; /* [5..5] �ȴ�Modem A9���綨ʱ����ʱ��0����ʱ��û�г�ʱ��1����ʱ����ʱ�� */
        unsigned int    peri_pwrup_timeout         : 1; /* [6..6] �ȴ���ͨ�����ϵ綨ʱ����ʱ��0����ʱ��û�г�ʱ��1����ʱ����ʱ�� */
        unsigned int    peri_pwrdn_timeout         : 1; /* [7..7] �ȴ���ͨ������綨ʱ����ʱ��0����ʱ��û�г�ʱ��1����ʱ����ʱ�� */
        unsigned int    retmem_nor_timeout         : 1; /* [8..8] �ȴ�RetMem����ѹ����normal��ʱ����ʱ��0����ʱ��û�г�ʱ��1����ʱ����ʱ�� */
        unsigned int    retmem_ret_timeout         : 1; /* [9..9] �ȴ�RetMem����ѹ����retention��ʱ����ʱ��0����ʱ��û�г�ʱ��1����ʱ����ʱ�� */
        unsigned int    moda9_standbywfi           : 1; /* [10..10] Modem A9 standbywfi�źŵ�ֵ1����ʾ��ǰMODA9����standbywfi״̬0����ʾMODA9����standbywfi״̬ */
        unsigned int    moda9_standbywfe           : 1; /* [11..11] Modem A9 standbywfe�źŵ�ֵ1����ʾ��ǰMODA9����standbywfe״̬0����ʾMODA9����standbywfe״̬ */
        unsigned int    appa9_standbywfi           : 1; /* [12..12] App A9 standbywfi�źŵ�ֵ1����ʾ��ǰAPPA9����standbywfi״̬0����ʾAPPA9����standbywfi״̬ */
        unsigned int    appa9_standbywfe           : 1; /* [13..13] App A9 standbywfe�źŵ�ֵ1����ʾ��ǰAPPA9����standbywfe״̬0����ʾAPPA9����standbywfe״̬ */
        unsigned int    pmu_pwrup_timeout          : 1; /* [14..14] �ȴ�PMU�ϵ綨ʱ����ʱ��0����ʱ��û�г�ʱ��1����ʱ����ʱ�� */
        unsigned int    reserved_1                 : 5; /* [19..15] ���� */
        unsigned int    cm3_sleeping               : 1; /* [20..20] ��ʾCortex_M3�����sleeping�ź�ֵ */
        unsigned int    cm3_sleepdeep              : 1; /* [21..21] ��ʾCortex_M3�����sleepdeep�ź�ֵ */
        unsigned int    cm3_sleephold_ack_n        : 1; /* [22..22] ��ʾCortex_M3�����sleephold_ack_n�ź�ֵ0����ʾCortex_M3������pwrctrl��sleephold_req�ź�1����ʾCortex_M3û�н���pwrctrl��sleephold_req�ź� */
        unsigned int    reserved_0                 : 9; /* [31..23] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT0_T;    /* pwrctrl ״̬ */

typedef union
{
    struct
    {
        unsigned int    appa9_mtcmos_rdy           : 1; /* [0..0] APPA9 CORE ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    moda9_mtcmos_rdy           : 1; /* [1..1] MODA9 CORE ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    peri_mtcmos_rdy            : 1; /* [2..2] SOC PERI ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    hisc_mtcmos_rdy            : 1; /* [3..3] HISC ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    dsp0_mtcmos_rdy            : 1; /* [4..4] DSP0 ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    hifi_mtcmos_rdy            : 1; /* [5..5] HIFI CORE ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    lbbp_mtcmos_rdy            : 1; /* [6..6] LBBP ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    twbbp_mtcmos_rdy           : 1; /* [7..7] TWBBP ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    wbbp_mtcmos_rdy            : 1; /* [8..8] WBBP ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    g1bbp_mtcmos_rdy           : 1; /* [9..9] G1BBP ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    g2bbp_mtcmos_rdy           : 1; /* [10..10] G2BBP ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    irm_mtcmos_rdy             : 1; /* [11..11] IRM ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    usb_mtcmos_rdy             : 1; /* [12..12] USB ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    sd_mtcmos_rdy              : 1; /* [13..13] SD ��ѹ��MTCOMS������ɣ���Դ�ȶ��źš�1����ʾ�е�0����ʾ���� */
        unsigned int    reserved                   : 18; /* [31..14] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT1_T;    /* MTCMOS rdy״̬ */

typedef union
{
    struct
    {
        unsigned int    sccnt_data                 : 25; /* [24..0] PLL/XTAL �������� */
        unsigned int    reserved                   : 7; /* [31..25] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT2_T;    /* PLL/XTAL ������ */

typedef union
{
    struct
    {
        unsigned int    appa9_iso_ctrl             : 1; /* [0..0] APPA9�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    moda9_iso_ctrl             : 1; /* [1..1] MODA9�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    peri_iso_ctrl              : 1; /* [2..2] SOC_PERI�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    hisc_iso_ctrl              : 1; /* [3..3] HSIC�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    dsp0_iso_ctrl              : 1; /* [4..4] DSP0�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    hifi_iso_ctrl              : 1; /* [5..5] HIFI�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    lbbp_iso_ctrl              : 1; /* [6..6] LBBP�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    twbbp_iso_ctrl             : 1; /* [7..7] TWBBP�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    wbbp_iso_ctrl              : 1; /* [8..8] WBBP�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    g1bbp_iso_ctrl             : 1; /* [9..9] G1BBP�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    g2bbp_iso_ctrl             : 1; /* [10..10] G2BBP�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    irm_iso_ctrl               : 1; /* [11..11] IRM�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    usb_iso_ctrl               : 1; /* [12..12] USB�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    sd_iso_ctrl                : 1; /* [13..13] SD �������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    reserved_2                 : 8; /* [21..14] ���� */
        unsigned int    io_ddr_ret                 : 1; /* [22..22] DDR �� IO ��retention�����źš�0����ʾret�źŽ�ֹ1����ʾret�ź�ʹ�� */
        unsigned int    reserved_1                 : 3; /* [25..23]  */
        unsigned int    io_ret_lp_ctrl             : 4; /* [29..26] IO��retention�����źš���ӦbitΪ0��ret�źŽ�ֹ��ӦbitΪ1��ret�ź�ʹ�� */
        unsigned int    pmu_iso_ctrl               : 1; /* [30..30] PMU �������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    reserved_0                 : 1; /* [31..31] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT3_T;    /* ISO cell ����״̬ */

typedef union
{
    struct
    {
        unsigned int    appa9_mtcmos_ctrl          : 1; /* [0..0] APP A9 MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    moda9_mtcmos_ctrl          : 1; /* [1..1] MOD A9 MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    peri_mtcmos_ctrl           : 1; /* [2..2] SOC_PERI MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    hisc_mtcmos_ctrl           : 1; /* [3..3] HSIC MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    dsp0_mtcmos_ctrl           : 1; /* [4..4] DSP0 MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    hifi_mtcmos_ctrl           : 1; /* [5..5] HIFI MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    lbbp_mtcmos_ctrl           : 1; /* [6..6] LBBP MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    twbbp_mtcmos_ctrl          : 1; /* [7..7] TWBBP MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    wbbp_mtcmos_ctrl           : 1; /* [8..8] WBBP MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    g1bbp_mtcmos_ctrl          : 1; /* [9..9] G1BBP MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    g2bbp_mtcmos_ctrl          : 1; /* [10..10] G2BBP MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    irm_mtcmos_ctrl            : 1; /* [11..11] IRM MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    usb_mtcmos_ctrl            : 1; /* [12..12] USB MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    sd_mtcmos_ctrl             : 1; /* [13..13] SD MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    reserved_1                 : 16; /* [29..14] ���� */
        unsigned int    pmu_pwr_on                 : 1; /* [30..30] PMU MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    reserved_0                 : 1; /* [31..31] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT4_T;    /* MTCMOS ����״̬ */

typedef union
{
    struct
    {
        unsigned int    retmem_ctrl                : 16; /* [15..0]  */
        unsigned int    reserved                   : 16; /* [31..16] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT5_T;    /* retmem_ctrl */

typedef union
{
    struct
    {
        unsigned int    cm3_wkup_stat0             : 1; /* [0..0] Cortex_M3 �����ж�λ�á�0��Cortex_M3 �����ж�0 �����жϲ���1��Cortex_M3 �����ж�0 �����жϲ��� */
        unsigned int    cm3_wkup_stat1             : 1; /* [1..1] Cortex_M3 �����ж�λ�á�0��Cortex_M3 �����ж�1 �����жϲ���1��Cortex_M3 �����ж�1 �����жϲ��� */
        unsigned int    cm3_wkup_stat2             : 1; /* [2..2] Cortex_M3 �����ж�λ�á�0��Cortex_M3 �����ж�2 �����жϲ���1��Cortex_M3 �����ж�2 �����жϲ��� */
        unsigned int    cm3_wkup_stat3             : 1; /* [3..3] Cortex_M3 �����ж�λ�á�0��Cortex_M3 �����ж�3 �����жϲ���1��Cortex_M3 �����ж�3 �����жϲ��� */
        unsigned int    reserved                   : 28; /* [31..4] ���� */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT6_T;    /* �ж�λ�üĴ��� */

typedef union
{
    struct
    {
        unsigned int    app_wkup_irq0              : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT7_T;    /* CM3 �����ж�״̬0 */

typedef union
{
    struct
    {
        unsigned int    app_wkup_irq1              : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT8_T;    /* CM3 �����ж�״̬1 */

typedef union
{
    struct
    {
        unsigned int    app_wkup_irq2              : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT9_T;    /* CM3 �����ж�״̬2 */

typedef union
{
    struct
    {
        unsigned int    app_wkup_irq3              : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT10_T;    /* CM3 �����ж�״̬3 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT11_T;    /* �����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_PWR_STAT12_T;    /* �����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    appa9_iso_en               : 1; /* [0..0] APPA9�������ISO CELL���ʹ���źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    moda9_iso_en               : 1; /* [1..1] MODA9�������ISO CELL���ʹ���źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    peri_iso_en                : 1; /* [2..2] SOC_PERI �������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    hisc_iso_en                : 1; /* [3..3] HSIC�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    dsp0_iso_en                : 1; /* [4..4] DSP0�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    hifi_iso_en                : 1; /* [5..5] HIFI�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    lbbp_iso_en                : 1; /* [6..6] LBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    twbbp_iso_en               : 1; /* [7..7] TWBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    wbbp_iso_en                : 1; /* [8..8] WBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    g1bbp_iso_en               : 1; /* [9..9] G1BBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    g2bbp_iso_en               : 1; /* [10..10] G2BBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    irm_iso_en                 : 1; /* [11..11] IRM�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    usb_iso_en                 : 1; /* [12..12] USB�������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    sd_iso_en                  : 1; /* [13..13] SD �������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    reserved_2                 : 8; /* [21..14] ���� */
        unsigned int    io_ddr_ret_sw              : 1; /* [22..22] DDR �� IO ��retention�����źš�0����Ӱ��1��ret�ź�ʹ�� */
        unsigned int    reserved_1                 : 3; /* [25..23]  */
        unsigned int    io_ret_lp_ctrl_sw          : 4; /* [29..26] IO��retention�����źš���ӦbitΪ0����Ӱ���ӦbitΪ1��ret�ź�ʹ�� */
        unsigned int    pmu_iso_en                 : 1; /* [30..30] PMU �������ISO CELL�����źš�0����Ӱ��1����ʾ�����ǯλ */
        unsigned int    reserved_0                 : 1; /* [31..31] ����CM3��ͷ�ļĴ�����CM3��ר�üĴ�����ֻ��ͨ��CM3��ר��APB�ӿڲ��ܷ��� */
    } bits;
    unsigned int    u32;
}HI_CM3_PWRCTRL0_T;    /* ISO cell ����ʹ�� */

typedef union
{
    struct
    {
        unsigned int    appa9_iso_dis              : 1; /* [0..0] APPA9�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    moda9_iso_dis              : 1; /* [1..1] MODA9�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    peri_iso_dis               : 1; /* [2..2] SOC_PERI �������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    hisc_iso_dis               : 1; /* [3..3] HSIC�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    dsp0_iso_dis               : 1; /* [4..4] DSP0�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    hifi_iso_dis               : 1; /* [5..5] HIFI�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    lbbp_iso_dis               : 1; /* [6..6] LBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    twbbp_iso_dis              : 1; /* [7..7] TWBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    wbbp_iso_dis               : 1; /* [8..8] WBBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    g1bbp_iso_dis              : 1; /* [9..9] G1BBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    g2bbp_iso_dis              : 1; /* [10..10] G2BBP�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    irm_iso_dis                : 1; /* [11..11] IRM�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    usb_iso_dis                : 1; /* [12..12] USB�������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    sd_iso_dis                 : 1; /* [13..13] SD �������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    reserved_2                 : 8; /* [21..14] ���� */
        unsigned int    io_ddr_ret                 : 1; /* [22..22] DDR �� IO ��retention�����źš�0����Ӱ��1��ret�źŽ�ֹ */
        unsigned int    reserved_1                 : 3; /* [25..23]  */
        unsigned int    io_ret_lp_ctrl             : 4; /* [29..26] IO��retention�����źš���ӦbitΪ0����Ӱ���ӦbitΪ1��ret�źŽ�ֹ */
        unsigned int    pmu_iso_dis                : 1; /* [30..30] PMU �������ISO CELL�����źš�0����Ӱ��1����ʾ�����Ч */
        unsigned int    reserved_0                 : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_CM3_PWRCTRL1_T;    /* ISO cell �����ֹ */

typedef union
{
    struct
    {
        unsigned int    appa9_iso_ctrl             : 1; /* [0..0] APPA9�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    moda9_iso_ctrl             : 1; /* [1..1] MODA9�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    peri_iso_ctrl              : 1; /* [2..2] SOC_PERI�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    hisc_iso_ctrl              : 1; /* [3..3] HSIC�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    dsp0_iso_ctrl              : 1; /* [4..4] DSP0�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    hifi_iso_ctrl              : 1; /* [5..5] HIFI�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    lbbp_iso_ctrl              : 1; /* [6..6] LBBP�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    twbbp_iso_ctrl             : 1; /* [7..7] TWBBP�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    wbbp_iso_ctrl              : 1; /* [8..8] WBBP�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    g1bbp_iso_ctrl             : 1; /* [9..9] G1BBP�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    g2bbp_iso_ctrl             : 1; /* [10..10] G2BBP�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    irm_iso_ctrl               : 1; /* [11..11] IRM�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    usb_iso_ctrl               : 1; /* [12..12] USB�������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    sd_iso_ctrl                : 1; /* [13..13] SD �������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    reserved_2                 : 8; /* [21..14] ���� */
        unsigned int    io_ddr_ret                 : 1; /* [22..22] DDR �� IO ��retention�����źš�0����ʾret�źŽ�ֹ1����ʾret�ź�ʹ�� */
        unsigned int    reserved_1                 : 3; /* [25..23]  */
        unsigned int    io_ret_lp_ctrl             : 4; /* [29..26] IO��retention�����źš���ӦbitΪ0��ret�źŽ�ֹ��ӦbitΪ1��ret�ź�ʹ�� */
        unsigned int    pmu_iso_ctrl               : 1; /* [30..30] PMU �������ISO CELL�����źš�0����ʾ�����Ч1����ʾ�����ǯλ */
        unsigned int    reserved_0                 : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_CM3_ISO_STAT_T;    /* CM3 ISO cell ����״̬ */

typedef union
{
    struct
    {
        unsigned int    appa9_mtcmos_en            : 1; /* [0..0] APP A9 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    moda9_mtcmos_en            : 1; /* [1..1] MOD A9 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    peri_mtcmos_en             : 1; /* [2..2] SOC_PERI MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    hisc_mtcmos_en             : 1; /* [3..3] HSIC MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    dsp0_mtcmos_en             : 1; /* [4..4] DSP0 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    hifi_mtcmos_en             : 1; /* [5..5] HIFI MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    lbbp_mtcmos_en             : 1; /* [6..6] LBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    twbbp_mtcmos_en            : 1; /* [7..7] TWBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    wbbp_mtcmos_en             : 1; /* [8..8] WBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    g1bbp_mtcmos_en            : 1; /* [9..9] G1BBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    g2bbp_mtcmos_en            : 1; /* [10..10] G2BBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    irm_mtcmos_en              : 1; /* [11..11] IRM MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    usb_mtcmos_en              : 1; /* [12..12] USB MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    sd_mtcmos_en               : 1; /* [13..13] SD MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    reserved_1                 : 16; /* [29..14]  */
        unsigned int    pmu_pwr_on                 : 1; /* [30..30] PMU �ϵ�ʹ�ܿ����ź�              0����Ӱ��1����ʾ�ϵ� */
        unsigned int    reserved_0                 : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_CM3_PWRCTRL2_T;    /* MTCMOS �ϵ���� */

typedef union
{
    struct
    {
        unsigned int    appa9_mtcmos_dis           : 1; /* [0..0] APP A9 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    moda9_mtcmos_dis           : 1; /* [1..1] MOD A9 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    peri_mtcmos_dis            : 1; /* [2..2] SOC_PERI MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    hisc_mtcmos_dis            : 1; /* [3..3] HSIC MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    dsp0_mtcmos_dis            : 1; /* [4..4] DSP0 MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    hifi_mtcmos_dis            : 1; /* [5..5] HIFI MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    lbbp_mtcmos_dis            : 1; /* [6..6] LBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    twbbp_mtcmos_dis           : 1; /* [7..7] TWBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    wbbp_mtcmos_dis            : 1; /* [8..8] WBBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    g1bbp_mtcmos_dis           : 1; /* [9..9] G1BBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    g2bbp_mtcmos_dis           : 1; /* [10..10] G2BBP MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    irm_mtcmos_dis             : 1; /* [11..11] IRM MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    usb_mtcmos_dis             : 1; /* [12..12] USB MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    sd_mtcmos_dis              : 1; /* [13..13] SD MTCMOS CELL�����źš�0����Ӱ��1����ʾ�ϵ� */
        unsigned int    reersved                   : 16; /* [29..14]  */
        unsigned int    pmu_pwr_off                : 1; /* [30..30] PMU �ϵ�ʹ�ܿ����ź�              0����Ӱ��1����ʾ�ϵ� */
        unsigned int    reserved                   : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_CM3_PWRCTRL3_T;    /* MTCMOS �µ���� */

typedef union
{
    struct
    {
        unsigned int    appa9_mtcmos_ctrl          : 1; /* [0..0] APP A9 MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    moda9_mtcmos_ctrl          : 1; /* [1..1] MOD A9 MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    peri_mtcmos_ctrl           : 1; /* [2..2] SOC_PERI MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    hisc_mtcmos_ctrl           : 1; /* [3..3] HSIC MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    dsp0_mtcmos_ctrl           : 1; /* [4..4] DSP0 MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    hifi_mtcmos_ctrl           : 1; /* [5..5] HIFI MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    lbbp_mtcmos_ctrl           : 1; /* [6..6] LBBP MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    twbbp_mtcmos_ctrl          : 1; /* [7..7] TWBBP MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    wbbp_mtcmos_ctrl           : 1; /* [8..8] WBBP MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    g1bbp_mtcmos_ctrl          : 1; /* [9..9] G1BBP MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    g2bbp_mtcmos_ctrl          : 1; /* [10..10] G2BBP MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    irm_mtcmos_ctrl            : 1; /* [11..11] IRM MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    usb_mtcmos_ctrl            : 1; /* [12..12] USB MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    sd_mtcmos_ctrl             : 1; /* [13..13] SD MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    reserved_1                 : 16; /* [29..14] ���� */
        unsigned int    pmu_pwr_on                 : 1; /* [30..30] PMU MTCMOS CELL�����źš�0����ʾ�ϵ�1����ʾ�ϵ� */
        unsigned int    reserved_0                 : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_CM3_MTCMOS_STAT_T;    /* CM3 MTCMOS ����״̬ */

typedef union
{
    struct
    {
        unsigned int    peri_clk_en                : 1; /* [0..0] SOC_PERI ʱ��ʹ�ܿ���                      0��ʱ�ӽ�ֹ                      1��ʱ��ʹ�� */
        unsigned int    peri_srst_req              : 1; /* [1..1] SOC_PERI ��λ����                      0����λ������Ч                     1����λ������Ч */
        unsigned int    pmu_clk_en                 : 1; /* [2..2] PMU ʱ��ʹ�ܿ���                      0��ʱ�ӽ�ֹ                      1��ʱ��ʹ�� */
        unsigned int    pmu_srst_req               : 1; /* [3..3] PMU ��λ����                      0����λ������Ч                     1����λ������Ч */
        unsigned int    tcxo_en                    : 4; /* [7..4] TCXOʹ�ܿ��ƣ���Ӧ����            0��tcxo��ֹ                       1��tcxoʹ��                       bit[7]��Ӧpmu_ch1_tcxo_en     bit[6]��Ӧpmu_ch0_tcxo_en     bit[5]��Ӧabb_ch1_tcxo_en    bit[4]��Ӧabb_ch0_tcxo_en */
        unsigned int    pwrctrl_bypass             : 1; /* [8..8] pwrctrl���Ŀ�����·����           0��������pwrctrl����źſ���      1��pwrctrl����·��������CM3ֱ�ӿ��� */
        unsigned int    clk_sw_req                 : 6; /* [14..9] ʱ���л�����                     bit[14]:cm3_tcxo_clk_sw_req bit[13]:cm3_sleep_clk_sw_req bit[12]:cm3_pll_clk_sw_req bit[11]:bus_tcxo_clk_sw_req bit[10]:bus_sleep_clk_sw_req    bit[9]:bus_pll_clk_sw_req */
        unsigned int    reserved                   : 9; /* [23..15]  */
        unsigned int    debug_sel                  : 8; /* [31..24] debug״̬�Ĵ�������ֵѡ����ơ����Ĵ���CM3_DEBUG_STAT */
    } bits;
    unsigned int    u32;
}HI_CM3_PWRCTRL4_T;    /* CM3���Ŀ��ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    mtcmos_ctrl_stat           : 31; /* [30..0] ͬ�Ĵ���PWR_STAT4 */
        unsigned int    reserved                   : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_CM3_PWRSTAT0_T;    /* PWRCTRL MTCMOS ����״̬ */

typedef union
{
    struct
    {
        unsigned int    iso_ctrl_stat              : 31; /* [30..0] ͬ�Ĵ���PWR_STAT3 */
        unsigned int    reserved                   : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_CM3_PWRSTAT1_T;    /* PWRCTRL ISO cell ����״̬ */

typedef union
{
    struct
    {
        unsigned int    debug_stat                 : 32; /* [31..0] debug״̬�Ĵ���������debug_selȡ��ͬ��ֵ��Ӧ���õ�״̬��          0��ͬ�Ĵ���PWR_STAT1                 1��                                bit[9]:pwrctrl�����peri_clk_en   bit[8]:pwrctrl�����peri_srst_req        bit[7]:pwrctrl�����pmu_clk_en   bit[6]:pwrctrl�����pmu_srst_req bit[5]:pwrctrl�����cm3_clk_en bit[4]:pwrctrl�����cm3_srst_req bit[3:0]:pwrctrl�����tcxo_en                               2�� ʱ���л����״̬                   bit[5]:cm3_tcxo_clk_sw_done bit[4]:cm3_sleep_clk_sw_done bit[3]:cm3_pll_clk_sw_done bit[2]:bus_tcxo_clk_sw_done bit[1]:bus_sleep_clk_sw_done    bit[0]:bus_pll_clk_sw_done                              3��ͬ�Ĵ���SC_STAT15               4��ͬ�Ĵ���SC_STAT9                               5��ͬ�Ĵ���SC_STAT10                                    6��ͬ�Ĵ���SC_STAT22                               7��ͬ�Ĵ���SC_STAT27                              8��ͬ�Ĵ���SC_STAT28                                9��ͬ�Ĵ���SC_STAT29              0xFF��DDRC��APB�ӿڶ�ȡ������ */
    } bits;
    unsigned int    u32;
}HI_CM3_DEBUG_STAT_T;    /* debug ״̬ */


/********************************************************************************/
/*    pwrctrl ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_pwr_ctrl0_cpumode_ctrl,cpumode_ctrl,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_a9_cpumode_status,a9_cpumode_status,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_reserved_1,reserved_1,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_cpu_dsleep_en,cpu_dsleep_en,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_reserved_0,reserved_0,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_doze_es_skip,doze_es_skip,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_doze_wk_skip,doze_wk_skip,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_cm3_sleephold_en,cm3_sleephold_en,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_cm3_sleeping_en,cm3_sleeping_en,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_cm3_sleepdeep_en,cm3_sleepdeep_en,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_arm_dsleep_rst_en,arm_dsleep_rst_en,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_usb_irq_glitch_free,usb_irq_glitch_free,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_io_ret_value_sel,io_ret_value_sel,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_arm_boot_type,arm_boot_type,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl0_sys_sleep_flag,sys_sleep_flag,HI_PWR_CTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL0_OFFSET)
HI_SET_GET(hi_pwr_ctrl1_sys_intmod_en,sys_intmod_en,HI_PWR_CTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL1_OFFSET)
HI_SET_GET(hi_pwr_ctrl1_sys_intmod_ctrl,sys_intmod_ctrl,HI_PWR_CTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL1_OFFSET)
HI_SET_GET(hi_pwr_ctrl1_reserved_1,reserved_1,HI_PWR_CTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL1_OFFSET)
HI_SET_GET(hi_pwr_ctrl1_sys_intmod_stat,sys_intmod_stat,HI_PWR_CTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL1_OFFSET)
HI_SET_GET(hi_pwr_ctrl1_reserved_0,reserved_0,HI_PWR_CTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL1_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_tcxo_time,tcxo_time,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_soc_tcxo_over,soc_tcxo_over,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_reserved_1,reserved_1,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_sleep_tcxo_off,sleep_tcxo_off,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_soc_tcxo_on,soc_tcxo_on,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_abb_ch0_tcxo_en,abb_ch0_tcxo_en,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_abb_ch1_tcxo_en,abb_ch1_tcxo_en,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_pmu_ch0_tcxo_en,pmu_ch0_tcxo_en,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_pmu_ch1_tcxo_en,pmu_ch1_tcxo_en,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_pmu_abb_tcxo_time,pmu_abb_tcxo_time,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_pmu_abb_time_en,pmu_abb_time_en,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_pmu_tcxo_en_stat,pmu_tcxo_en_stat,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl2_reserved_0,reserved_0,HI_PWR_CTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL2_OFFSET)
HI_SET_GET(hi_pwr_ctrl3_pll_time,pll_time,HI_PWR_CTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL3_OFFSET)
HI_SET_GET(hi_pwr_ctrl3_pll_time_en,pll_time_en,HI_PWR_CTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL3_OFFSET)
HI_SET_GET(hi_pwr_ctrl3_pll_status,pll_status,HI_PWR_CTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL3_OFFSET)
HI_SET_GET(hi_pwr_ctrl3_reserved,reserved,HI_PWR_CTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL3_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_appa9_iso_en,appa9_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_moda9_iso_en,moda9_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_reserved_3,reserved_3,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_hisc_iso_en,hisc_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_dsp0_iso_en,dsp0_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_hifi_iso_en,hifi_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_lbbp_iso_en,lbbp_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_twbbp_iso_en,twbbp_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_wbbp_iso_en,wbbp_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_g1bbp_iso_en,g1bbp_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_g2bbp_iso_en,g2bbp_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_irm_iso_en,irm_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_usb_iso_en,usb_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_sd_iso_en,sd_iso_en,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_reserved_2,reserved_2,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_io_ddr_ret,io_ddr_ret,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_reserved_1,reserved_1,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_io_ret_lp_ctrl,io_ret_lp_ctrl,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl4_reserved_0,reserved_0,HI_PWR_CTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL4_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_appa9_iso_dis,appa9_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_moda9_iso_dis,moda9_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_reserved_3,reserved_3,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_hisc_iso_dis,hisc_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_dsp0_iso_dis,dsp0_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_hifi_iso_dis,hifi_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_lbbp_iso_dis,lbbp_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_twbbp_iso_dis,twbbp_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_wbbp_iso_dis,wbbp_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_g1bbp_iso_dis,g1bbp_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_g2bbp_iso_dis,g2bbp_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_irm_iso_dis,irm_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_usb_iso_dis,usb_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_sd_iso_dis,sd_iso_dis,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_reserved_2,reserved_2,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_io_ddr_ret,io_ddr_ret,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_reserved_1,reserved_1,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_io_ret_lp_ctrl,io_ret_lp_ctrl,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl5_reserved_0,reserved_0,HI_PWR_CTRL5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL5_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_appa9_mtcmos_en,appa9_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_moda9_mtcmos_en,moda9_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_reserved_1,reserved_1,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_hisc_mtcmos_en,hisc_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_dsp0_mtcmos_en,dsp0_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_hifi_mtcmos_en,hifi_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_lbbp_mtcmos_en,lbbp_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_twbbp_mtcmos_en,twbbp_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_wbbp_mtcmos_en,wbbp_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_g1bbp_mtcmos_en,g1bbp_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_g2bbp_mtcmos_en,g2bbp_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_irm_mtcmos_en,irm_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_usb_mtcmos_en,usb_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_sd_mtcmos_en,sd_mtcmos_en,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl6_reserved_0,reserved_0,HI_PWR_CTRL6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL6_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_appa9_mtcmos_dis,appa9_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_moda9_mtcmos_dis,moda9_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_reserved_1,reserved_1,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_hisc_mtcmos_dis,hisc_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_dsp0_mtcmos_dis,dsp0_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_hifi_mtcmos_dis,hifi_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_lbbp_mtcmos_dis,lbbp_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_twbbp_mtcmos_dis,twbbp_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_wbbp_mtcmos_dis,wbbp_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_g1bbp_mtcmos_dis,g1bbp_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_g2bbp_mtcmos_dis,g2bbp_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_irm_mtcmos_dis,irm_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_usb_mtcmos_dis,usb_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_sd_mtcmos_dis,sd_mtcmos_dis,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl7_reserved_0,reserved_0,HI_PWR_CTRL7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL7_OFFSET)
HI_SET_GET(hi_pwr_ctrl8_cpu_pwrup_time,cpu_pwrup_time,HI_PWR_CTRL8_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL8_OFFSET)
HI_SET_GET(hi_pwr_ctrl8_reserved_1,reserved_1,HI_PWR_CTRL8_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL8_OFFSET)
HI_SET_GET(hi_pwr_ctrl8_cpu_pwrdn_time,cpu_pwrdn_time,HI_PWR_CTRL8_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL8_OFFSET)
HI_SET_GET(hi_pwr_ctrl8_cpu_pwrtime_en,cpu_pwrtime_en,HI_PWR_CTRL8_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL8_OFFSET)
HI_SET_GET(hi_pwr_ctrl8_reserved_0,reserved_0,HI_PWR_CTRL8_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL8_OFFSET)
HI_SET_GET(hi_pwr_ctrl9_peri_pwrup_time,peri_pwrup_time,HI_PWR_CTRL9_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL9_OFFSET)
HI_SET_GET(hi_pwr_ctrl9_reserved_1,reserved_1,HI_PWR_CTRL9_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL9_OFFSET)
HI_SET_GET(hi_pwr_ctrl9_peri_pwrdn_time,peri_pwrdn_time,HI_PWR_CTRL9_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL9_OFFSET)
HI_SET_GET(hi_pwr_ctrl9_peri_pwrtime_en,peri_pwrtime_en,HI_PWR_CTRL9_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL9_OFFSET)
HI_SET_GET(hi_pwr_ctrl9_dsleep_peri_pwrdn,dsleep_peri_pwrdn,HI_PWR_CTRL9_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL9_OFFSET)
HI_SET_GET(hi_pwr_ctrl9_sleep_periclk_en,sleep_periclk_en,HI_PWR_CTRL9_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL9_OFFSET)
HI_SET_GET(hi_pwr_ctrl9_reserved_0,reserved_0,HI_PWR_CTRL9_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL9_OFFSET)
HI_SET_GET(hi_pwr_ctrl10_retmem_nor_time,retmem_nor_time,HI_PWR_CTRL10_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL10_OFFSET)
HI_SET_GET(hi_pwr_ctrl10_reserved,reserved,HI_PWR_CTRL10_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL10_OFFSET)
HI_SET_GET(hi_pwr_ctrl11_retmem_ret_time,retmem_ret_time,HI_PWR_CTRL11_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL11_OFFSET)
HI_SET_GET(hi_pwr_ctrl11_reserved,reserved,HI_PWR_CTRL11_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL11_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_ema,ema,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_reserved_3,reserved_3,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_emaw,emaw,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_emas,emas,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_reserved_2,reserved_2,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_retmem_ret1n_cfg,retmem_ret1n_cfg,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_retmem_ret2n_cfg,retmem_ret2n_cfg,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_retmem_pgen_cfg,retmem_pgen_cfg,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_reserved_1,reserved_1,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_retmem_sw_lp_ctrl,retmem_sw_lp_ctrl,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_dsleep_retmem_ret,dsleep_retmem_ret,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl12_reserved_0,reserved_0,HI_PWR_CTRL12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL12_OFFSET)
HI_SET_GET(hi_pwr_ctrl13_pmu_pwrup_time,pmu_pwrup_time,HI_PWR_CTRL13_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL13_OFFSET)
HI_SET_GET(hi_pwr_ctrl13_reserved_1,reserved_1,HI_PWR_CTRL13_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL13_OFFSET)
HI_SET_GET(hi_pwr_ctrl13_dsleep_pmu_pwrdn,dsleep_pmu_pwrdn,HI_PWR_CTRL13_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL13_OFFSET)
HI_SET_GET(hi_pwr_ctrl13_sleep_pmuclk_en,sleep_pmuclk_en,HI_PWR_CTRL13_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL13_OFFSET)
HI_SET_GET(hi_pwr_ctrl13_reserved_0,reserved_0,HI_PWR_CTRL13_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL13_OFFSET)
HI_SET_GET(hi_pwr_ctrl14_sleep_hold_cycle,sleep_hold_cycle,HI_PWR_CTRL14_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL14_OFFSET)
HI_SET_GET(hi_pwr_ctrl14_sleephole_cnt,sleephole_cnt,HI_PWR_CTRL14_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL14_OFFSET)
HI_SET_GET(hi_pwr_ctrl15_moda9_usbwkup_en,moda9_usbwkup_en,HI_PWR_CTRL15_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL15_OFFSET)
HI_SET_GET(hi_pwr_ctrl15_appa9_usbwkup_en,appa9_usbwkup_en,HI_PWR_CTRL15_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL15_OFFSET)
HI_SET_GET(hi_pwr_ctrl15_a9_otgphy_wkup_en,a9_otgphy_wkup_en,HI_PWR_CTRL15_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL15_OFFSET)
HI_SET_GET(hi_pwr_ctrl15_a9_otgsuspend_wkup_en,a9_otgsuspend_wkup_en,HI_PWR_CTRL15_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL15_OFFSET)
HI_SET_GET(hi_pwr_ctrl15_otgawson_wpc_clk_en,otgawson_wpc_clk_en,HI_PWR_CTRL15_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL15_OFFSET)
HI_SET_GET(hi_pwr_ctrl15_reserved_1,reserved_1,HI_PWR_CTRL15_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL15_OFFSET)
HI_SET_GET(hi_pwr_ctrl15_sleep_usbwkup_en,sleep_usbwkup_en,HI_PWR_CTRL15_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL15_OFFSET)
HI_SET_GET(hi_pwr_ctrl15_reserved_0,reserved_0,HI_PWR_CTRL15_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL15_OFFSET)
HI_SET_GET(hi_pwr_ctrl16_cm3_irqs_en_31_0,cm3_irqs_en_31_0,HI_PWR_CTRL16_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL16_OFFSET)
HI_SET_GET(hi_pwr_ctrl17_cm3_irqs_en_63_32,cm3_irqs_en_63_32,HI_PWR_CTRL17_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL17_OFFSET)
HI_SET_GET(hi_pwr_ctrl18_cm3_irqs_en_95_64,cm3_irqs_en_95_64,HI_PWR_CTRL18_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL18_OFFSET)
HI_SET_GET(hi_pwr_ctrl19_cm3_irqs_en_127_96,cm3_irqs_en_127_96,HI_PWR_CTRL19_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL19_OFFSET)
HI_SET_GET(hi_pwr_ctrl20_reserved,reserved,HI_PWR_CTRL20_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL20_OFFSET)
HI_SET_GET(hi_pwr_ctrl21_reserved,reserved,HI_PWR_CTRL21_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_CTRL21_OFFSET)
HI_SET_GET(hi_pwr_stat0_cpu_volt_fsm,cpu_volt_fsm,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_cpu_pwrup_timeout,cpu_pwrup_timeout,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_cpu_pwrdn_timeout,cpu_pwrdn_timeout,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_peri_pwrup_timeout,peri_pwrup_timeout,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_peri_pwrdn_timeout,peri_pwrdn_timeout,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_retmem_nor_timeout,retmem_nor_timeout,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_retmem_ret_timeout,retmem_ret_timeout,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_moda9_standbywfi,moda9_standbywfi,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_moda9_standbywfe,moda9_standbywfe,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_appa9_standbywfi,appa9_standbywfi,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_appa9_standbywfe,appa9_standbywfe,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_pmu_pwrup_timeout,pmu_pwrup_timeout,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_reserved_1,reserved_1,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_cm3_sleeping,cm3_sleeping,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_cm3_sleepdeep,cm3_sleepdeep,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_cm3_sleephold_ack_n,cm3_sleephold_ack_n,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat0_reserved_0,reserved_0,HI_PWR_STAT0_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT0_OFFSET)
HI_SET_GET(hi_pwr_stat1_appa9_mtcmos_rdy,appa9_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_moda9_mtcmos_rdy,moda9_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_peri_mtcmos_rdy,peri_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_hisc_mtcmos_rdy,hisc_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_dsp0_mtcmos_rdy,dsp0_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_hifi_mtcmos_rdy,hifi_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_lbbp_mtcmos_rdy,lbbp_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_twbbp_mtcmos_rdy,twbbp_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_wbbp_mtcmos_rdy,wbbp_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_g1bbp_mtcmos_rdy,g1bbp_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_g2bbp_mtcmos_rdy,g2bbp_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_irm_mtcmos_rdy,irm_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_usb_mtcmos_rdy,usb_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_sd_mtcmos_rdy,sd_mtcmos_rdy,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat1_reserved,reserved,HI_PWR_STAT1_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT1_OFFSET)
HI_SET_GET(hi_pwr_stat2_sccnt_data,sccnt_data,HI_PWR_STAT2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT2_OFFSET)
HI_SET_GET(hi_pwr_stat2_reserved,reserved,HI_PWR_STAT2_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT2_OFFSET)
HI_SET_GET(hi_pwr_stat3_appa9_iso_ctrl,appa9_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_moda9_iso_ctrl,moda9_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_peri_iso_ctrl,peri_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_hisc_iso_ctrl,hisc_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_dsp0_iso_ctrl,dsp0_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_hifi_iso_ctrl,hifi_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_lbbp_iso_ctrl,lbbp_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_twbbp_iso_ctrl,twbbp_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_wbbp_iso_ctrl,wbbp_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_g1bbp_iso_ctrl,g1bbp_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_g2bbp_iso_ctrl,g2bbp_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_irm_iso_ctrl,irm_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_usb_iso_ctrl,usb_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_sd_iso_ctrl,sd_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_reserved_2,reserved_2,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_io_ddr_ret,io_ddr_ret,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_reserved_1,reserved_1,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_io_ret_lp_ctrl,io_ret_lp_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_pmu_iso_ctrl,pmu_iso_ctrl,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat3_reserved_0,reserved_0,HI_PWR_STAT3_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT3_OFFSET)
HI_SET_GET(hi_pwr_stat4_appa9_mtcmos_ctrl,appa9_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_moda9_mtcmos_ctrl,moda9_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_peri_mtcmos_ctrl,peri_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_hisc_mtcmos_ctrl,hisc_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_dsp0_mtcmos_ctrl,dsp0_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_hifi_mtcmos_ctrl,hifi_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_lbbp_mtcmos_ctrl,lbbp_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_twbbp_mtcmos_ctrl,twbbp_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_wbbp_mtcmos_ctrl,wbbp_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_g1bbp_mtcmos_ctrl,g1bbp_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_g2bbp_mtcmos_ctrl,g2bbp_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_irm_mtcmos_ctrl,irm_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_usb_mtcmos_ctrl,usb_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_sd_mtcmos_ctrl,sd_mtcmos_ctrl,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_reserved_1,reserved_1,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_pmu_pwr_on,pmu_pwr_on,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat4_reserved_0,reserved_0,HI_PWR_STAT4_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT4_OFFSET)
HI_SET_GET(hi_pwr_stat5_retmem_ctrl,retmem_ctrl,HI_PWR_STAT5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT5_OFFSET)
HI_SET_GET(hi_pwr_stat5_reserved,reserved,HI_PWR_STAT5_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT5_OFFSET)
HI_SET_GET(hi_pwr_stat6_cm3_wkup_stat0,cm3_wkup_stat0,HI_PWR_STAT6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT6_OFFSET)
HI_SET_GET(hi_pwr_stat6_cm3_wkup_stat1,cm3_wkup_stat1,HI_PWR_STAT6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT6_OFFSET)
HI_SET_GET(hi_pwr_stat6_cm3_wkup_stat2,cm3_wkup_stat2,HI_PWR_STAT6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT6_OFFSET)
HI_SET_GET(hi_pwr_stat6_cm3_wkup_stat3,cm3_wkup_stat3,HI_PWR_STAT6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT6_OFFSET)
HI_SET_GET(hi_pwr_stat6_reserved,reserved,HI_PWR_STAT6_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT6_OFFSET)
HI_SET_GET(hi_pwr_stat7_app_wkup_irq0,app_wkup_irq0,HI_PWR_STAT7_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT7_OFFSET)
HI_SET_GET(hi_pwr_stat8_app_wkup_irq1,app_wkup_irq1,HI_PWR_STAT8_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT8_OFFSET)
HI_SET_GET(hi_pwr_stat9_app_wkup_irq2,app_wkup_irq2,HI_PWR_STAT9_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT9_OFFSET)
HI_SET_GET(hi_pwr_stat10_app_wkup_irq3,app_wkup_irq3,HI_PWR_STAT10_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT10_OFFSET)
HI_SET_GET(hi_pwr_stat11_reserved,reserved,HI_PWR_STAT11_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT11_OFFSET)
HI_SET_GET(hi_pwr_stat12_reserved,reserved,HI_PWR_STAT12_T,HI_PWRCTRL_BASE_ADDR, HI_PWR_STAT12_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_appa9_iso_en,appa9_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_moda9_iso_en,moda9_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_peri_iso_en,peri_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_hisc_iso_en,hisc_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_dsp0_iso_en,dsp0_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_hifi_iso_en,hifi_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_lbbp_iso_en,lbbp_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_twbbp_iso_en,twbbp_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_wbbp_iso_en,wbbp_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_g1bbp_iso_en,g1bbp_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_g2bbp_iso_en,g2bbp_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_irm_iso_en,irm_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_usb_iso_en,usb_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_sd_iso_en,sd_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_reserved_2,reserved_2,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_io_ddr_ret_sw,io_ddr_ret_sw,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_reserved_1,reserved_1,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_io_ret_lp_ctrl_sw,io_ret_lp_ctrl_sw,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_pmu_iso_en,pmu_iso_en,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl0_reserved_0,reserved_0,HI_CM3_PWRCTRL0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL0_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_appa9_iso_dis,appa9_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_moda9_iso_dis,moda9_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_peri_iso_dis,peri_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_hisc_iso_dis,hisc_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_dsp0_iso_dis,dsp0_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_hifi_iso_dis,hifi_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_lbbp_iso_dis,lbbp_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_twbbp_iso_dis,twbbp_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_wbbp_iso_dis,wbbp_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_g1bbp_iso_dis,g1bbp_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_g2bbp_iso_dis,g2bbp_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_irm_iso_dis,irm_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_usb_iso_dis,usb_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_sd_iso_dis,sd_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_reserved_2,reserved_2,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_io_ddr_ret,io_ddr_ret,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_reserved_1,reserved_1,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_io_ret_lp_ctrl,io_ret_lp_ctrl,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_pmu_iso_dis,pmu_iso_dis,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl1_reserved_0,reserved_0,HI_CM3_PWRCTRL1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL1_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_appa9_iso_ctrl,appa9_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_moda9_iso_ctrl,moda9_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_peri_iso_ctrl,peri_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_hisc_iso_ctrl,hisc_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_dsp0_iso_ctrl,dsp0_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_hifi_iso_ctrl,hifi_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_lbbp_iso_ctrl,lbbp_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_twbbp_iso_ctrl,twbbp_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_wbbp_iso_ctrl,wbbp_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_g1bbp_iso_ctrl,g1bbp_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_g2bbp_iso_ctrl,g2bbp_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_irm_iso_ctrl,irm_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_usb_iso_ctrl,usb_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_sd_iso_ctrl,sd_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_reserved_2,reserved_2,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_io_ddr_ret,io_ddr_ret,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_reserved_1,reserved_1,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_io_ret_lp_ctrl,io_ret_lp_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_pmu_iso_ctrl,pmu_iso_ctrl,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_iso_stat_reserved_0,reserved_0,HI_CM3_ISO_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_ISO_STAT_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_appa9_mtcmos_en,appa9_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_moda9_mtcmos_en,moda9_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_peri_mtcmos_en,peri_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_hisc_mtcmos_en,hisc_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_dsp0_mtcmos_en,dsp0_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_hifi_mtcmos_en,hifi_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_lbbp_mtcmos_en,lbbp_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_twbbp_mtcmos_en,twbbp_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_wbbp_mtcmos_en,wbbp_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_g1bbp_mtcmos_en,g1bbp_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_g2bbp_mtcmos_en,g2bbp_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_irm_mtcmos_en,irm_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_usb_mtcmos_en,usb_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_sd_mtcmos_en,sd_mtcmos_en,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_reserved_1,reserved_1,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_pmu_pwr_on,pmu_pwr_on,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl2_reserved_0,reserved_0,HI_CM3_PWRCTRL2_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL2_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_appa9_mtcmos_dis,appa9_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_moda9_mtcmos_dis,moda9_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_peri_mtcmos_dis,peri_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_hisc_mtcmos_dis,hisc_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_dsp0_mtcmos_dis,dsp0_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_hifi_mtcmos_dis,hifi_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_lbbp_mtcmos_dis,lbbp_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_twbbp_mtcmos_dis,twbbp_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_wbbp_mtcmos_dis,wbbp_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_g1bbp_mtcmos_dis,g1bbp_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_g2bbp_mtcmos_dis,g2bbp_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_irm_mtcmos_dis,irm_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_usb_mtcmos_dis,usb_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_sd_mtcmos_dis,sd_mtcmos_dis,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_reersved,reersved,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_pmu_pwr_off,pmu_pwr_off,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl3_reserved,reserved,HI_CM3_PWRCTRL3_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL3_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_appa9_mtcmos_ctrl,appa9_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_moda9_mtcmos_ctrl,moda9_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_peri_mtcmos_ctrl,peri_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_hisc_mtcmos_ctrl,hisc_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_dsp0_mtcmos_ctrl,dsp0_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_hifi_mtcmos_ctrl,hifi_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_lbbp_mtcmos_ctrl,lbbp_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_twbbp_mtcmos_ctrl,twbbp_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_wbbp_mtcmos_ctrl,wbbp_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_g1bbp_mtcmos_ctrl,g1bbp_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_g2bbp_mtcmos_ctrl,g2bbp_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_irm_mtcmos_ctrl,irm_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_usb_mtcmos_ctrl,usb_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_sd_mtcmos_ctrl,sd_mtcmos_ctrl,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_reserved_1,reserved_1,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_pmu_pwr_on,pmu_pwr_on,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_mtcmos_stat_reserved_0,reserved_0,HI_CM3_MTCMOS_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_MTCMOS_STAT_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl4_peri_clk_en,peri_clk_en,HI_CM3_PWRCTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL4_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl4_peri_srst_req,peri_srst_req,HI_CM3_PWRCTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL4_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl4_pmu_clk_en,pmu_clk_en,HI_CM3_PWRCTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL4_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl4_pmu_srst_req,pmu_srst_req,HI_CM3_PWRCTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL4_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl4_tcxo_en,tcxo_en,HI_CM3_PWRCTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL4_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl4_pwrctrl_bypass,pwrctrl_bypass,HI_CM3_PWRCTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL4_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl4_clk_sw_req,clk_sw_req,HI_CM3_PWRCTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL4_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl4_reserved,reserved,HI_CM3_PWRCTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL4_OFFSET)
HI_SET_GET(hi_cm3_pwrctrl4_debug_sel,debug_sel,HI_CM3_PWRCTRL4_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRCTRL4_OFFSET)
HI_SET_GET(hi_cm3_pwrstat0_mtcmos_ctrl_stat,mtcmos_ctrl_stat,HI_CM3_PWRSTAT0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRSTAT0_OFFSET)
HI_SET_GET(hi_cm3_pwrstat0_reserved,reserved,HI_CM3_PWRSTAT0_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRSTAT0_OFFSET)
HI_SET_GET(hi_cm3_pwrstat1_iso_ctrl_stat,iso_ctrl_stat,HI_CM3_PWRSTAT1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRSTAT1_OFFSET)
HI_SET_GET(hi_cm3_pwrstat1_reserved,reserved,HI_CM3_PWRSTAT1_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_PWRSTAT1_OFFSET)
HI_SET_GET(hi_cm3_debug_stat_debug_stat,debug_stat,HI_CM3_DEBUG_STAT_T,HI_PWRCTRL_BASE_ADDR, HI_CM3_DEBUG_STAT_OFFSET)

#endif

#endif // __HI_PWRCTRL_H__

