/******************************************************************************/
/*  Copyright (C), 2007-2014, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_syscrg.h */
/* Version       : 2.0 */
/* Author        : xxx*/
/* Created       : 2014-03-17*/
/* Last Modified : */
/* Description   :  The C union definition file for the module syscrg*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Author        : xxx*/
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_SYSCRG_H__
#define __HI_SYSCRG_H__

/*
 * Project: hi
 * Module : syscrg
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    syscrg �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_CRG_CLKEN1_OFFSET                              (0x0) /* ʱ��ʹ��1 */
#define    HI_CRG_CLKDIS1_OFFSET                             (0x4) /* ʱ�ӹر�1 */
#define    HI_CRG_CLKSTAT1_OFFSET                            (0x8) /* ʱ�ӿ���״̬1 */
#define    HI_CRG_CLKEN2_OFFSET                              (0xC) /* ʱ��ʹ��2 */
#define    HI_CRG_CLKDIS2_OFFSET                             (0x10) /* ʱ�ӹر�2 */
#define    HI_CRG_CLKSTAT2_OFFSET                            (0x14) /* ʱ�ӿ���״̬2 */
#define    HI_CRG_CLKEN3_OFFSET                              (0x18) /* ʱ��ʹ��3 */
#define    HI_CRG_CLKDIS3_OFFSET                             (0x1C) /* ʱ�ӹر�3 */
#define    HI_CRG_CLKSTAT3_OFFSET                            (0x20) /* ʱ�ӿ���״̬3 */
#define    HI_CRG_CLKEN4_OFFSET                              (0x24) /* ʱ��ʹ��4(MCPU����) */
#define    HI_CRG_CLKDIS4_OFFSET                             (0x28) /* ʱ�ӹر�4(MCPU����) */
#define    HI_CRG_CLKSTAT4_OFFSET                            (0x2C) /* ʱ�ӿ���״̬4(MCPU����) */
#define    HI_CRG_CLKEN5_OFFSET                              (0x30) /* ʱ��ʹ��5��BBP�� */
#define    HI_CRG_CLKDIS5_OFFSET                             (0x34) /* ʱ�ӹر�5 */
#define    HI_CRG_CLKSTAT5_OFFSET                            (0x38) /* ʱ�ӿ���״̬5 */
#define    HI_CRG_SRSTEN1_OFFSET                             (0x60) /* ��λ����ʹ��1 */
#define    HI_CRG_SRSTDIS1_OFFSET                            (0x64) /* ��λ����ر�1 */
#define    HI_CRG_SRSTSTAT1_OFFSET                           (0x68) /* ��λ����״̬1 */
#define    HI_CRG_SRSTEN2_OFFSET                             (0x6C) /* ��λ����ʹ��2 */
#define    HI_CRG_SRSTDIS2_OFFSET                            (0x70) /* ��λ����ر�2 */
#define    HI_CRG_SRSTSTAT2_OFFSET                           (0x74) /* ��λ����״̬2 */
#define    HI_CRG_SRSTEN3_OFFSET                             (0x78) /* ��λ����ʹ��3��ABB+BBP�� */
#define    HI_CRG_SRSTDIS3_OFFSET                            (0x7C) /* ��λ����ر�3��ABB+BBP�� */
#define    HI_CRG_SRSTSTAT3_OFFSET                           (0x80) /* ��λ����״̬3��ABB+BBP�� */
#define    HI_CRG_CLKDIV1_OFFSET                             (0x100) /* ʱ�ӷ�Ƶ����1(SIO PCMʱ�ӷ�Ƶ�� */
#define    HI_CRG_CLKDIV2_OFFSET                             (0x104) /* ʱ�ӷ�Ƶ����2(���߷�Ƶ�� */
#define    HI_CRG_CLKDIV3_OFFSET                             (0x108) /* ʱ�ӷ�Ƶ����3(MMC0/1) */
#define    HI_CRG_CLKDIV4_OFFSET                             (0x10C) /* ʱ�ӷ�Ƶ����4(HIFIʱ�ӷ�Ƶ) */
#define    HI_CRG_CLKDIV5_OFFSET                             (0x110) /* ʱ�ӷ�Ƶ����5(BBE/SCIʱ�ӷ�Ƶ) */
#define    HI_CRG_MMC_CTRL_OFFSET                            (0x114) /* MMC0/1������� */
#define    HI_CRG_PLLLOCK_CTRL_OFFSET                        (0x118) /* pll�������ƼĴ��� */
#define    HI_CRG_CLK_SEL1_OFFSET                            (0x140) /* ʱ��Դѡ�����1 */
#define    HI_CRG_CLK_SEL2_OFFSET                            (0x144) /* ʱ��Դѡ�����2(TIMER) */
#define    HI_CRG_CLK_SEL3_OFFSET                            (0x148) /* ʱ��Դѡ�����3��BBP�� */
#define    HI_CRG_DFS1_CTRL1_OFFSET                          (0x200) /* A9 DFS����1��1.2GHz) */
#define    HI_CRG_DFS1_CTRL2_OFFSET                          (0x204) /* A9 DFS����2 */
#define    HI_CRG_DFS1_CTRL3_OFFSET                          (0x208) /* A9 DFS����3 */
#define    HI_CRG_DFS2_CTRL1_OFFSET                          (0x20C) /* DSP DFS����1(1200MHz) */
#define    HI_CRG_DFS2_CTRL2_OFFSET                          (0x210) /* DSP DFS����2 */
#define    HI_CRG_DFS2_CTRL3_OFFSET                          (0x214) /* DSP DFS����3 */
#define    HI_CRG_DFS3_CTRL1_OFFSET                          (0x218) /* HIFI DFS����1��1.6GHz) */
#define    HI_CRG_DFS3_CTRL2_OFFSET                          (0x21C) /* HIFI DFS����2 */
#define    HI_CRG_DFS3_CTRL3_OFFSET                          (0x220) /* HIFI DFS����3 */
#define    HI_CRG_DFS4_CTRL1_OFFSET                          (0x224) /* BBP DFS����1(491.52MHz) */
#define    HI_CRG_DFS4_CTRL2_OFFSET                          (0x228) /* BBP DFS����2 */
#define    HI_CRG_DFS4_CTRL3_OFFSET                          (0x22C) /* BBP DFS����3 */
#define    HI_CRG_DFS5_CTRL1_OFFSET                          (0x230) /* PERI DFS����1(960MHz) */
#define    HI_CRG_DFS5_CTRL2_OFFSET                          (0x234) /* PERI DFS����2 */
#define    HI_CRG_DFS5_CTRL3_OFFSET                          (0x238) /* PERI DFS����3 */
#define    HI_CRG_DFS6_CTRL1_OFFSET                          (0x23C) /* PERI USB DFS����1(500MHz) */
#define    HI_CRG_DFS6_CTRL2_OFFSET                          (0x240) /* PERI USB DFS����2 */
#define    HI_CRG_DFS6_CTRL3_OFFSET                          (0x244) /* PERI USB DFS����3 */
#define    HI_CRG_CLKSW_STAT1_OFFSET                         (0x260) /* ʱ���л�״̬1 */
#define    HI_CRG_CLKDIV6_OFFSET                             (0x264) /* ʱ�ӷ�Ƶ����6��CM3ʱ�ӷ�Ƶ�� */


#ifndef __ASSEMBLY__

/********************************************************************************/
/*    syscrg �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    mst_aclk_en                : 1; /* [0..0] AXI master����ʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    dsp_aclk_en                : 1; /* [1..1] DSP����ʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�ܡ���bit��Ҫ���ڹ��Ĳ��ԣ���������ʱ��ʱ��һֱΪ1 */
        unsigned int    soc_hclk_en                : 1; /* [2..2] SOC_HCLK/SOC_ASHB_PCLKʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� ��bit��Ҫ���ڹ��Ĳ��ԣ���������ʱ��ʱ��һֱΪ1 */
        unsigned int    amon_cpufast_clk_en        : 1; /* [3..3] AMON_CPUFASTģ��ʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�ܡ� */
        unsigned int    amon_soc_clk_en            : 1; /* [4..4] AMON_SOCʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    tsensor_clk_en             : 1; /* [5..5] TSENSORʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ� */
        unsigned int    reserved_2                 : 2; /* [7..6] ���� */
        unsigned int    ipf_clk_en                 : 1; /* [8..8] IPFʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ� */
        unsigned int    reserved_1                 : 1; /* [9..9] ���� */
        unsigned int    edmac_ch4_clk_en           : 1; /* [10..10] EDMAC_CH4ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ� */
        unsigned int    socp_clk_en                : 1; /* [11..11] SOCPʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    mipi_clk_en                : 1; /* [12..12] MIPIʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    pmussi0_clk_en             : 1; /* [13..13] PMU_SSI0ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    pmussi1_clk_en             : 1; /* [14..14] PMUSSI1ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    dw_ssi0_clk_en             : 1; /* [15..15] DW SSI0ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    efuse_clk_en               : 1; /* [16..16] eFUSEʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    nandc_clk_en               : 1; /* [17..17] NANDCʱ��ʹ�ܡ�                              0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    hs_uart_clk_en             : 1; /* [18..18] HS_UARTʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    emi_clk_en                 : 1; /* [19..19] EMIʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�ܡ� */
        unsigned int    edmac_clk_en               : 1; /* [20..20] EDMAC_CH16ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ� */
        unsigned int    bootrom_clk_en             : 1; /* [21..21] BOOTROMʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ��.��ȫ�����󣬸�ʱ�ӿ��Թرա� */
        unsigned int    pwm1_clk_en                : 1; /* [22..22] PWM1ʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    pwm0_clk_en                : 1; /* [23..23] PWM0ʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    dt_clk_en                  : 1; /* [24..24] DramTestʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�ܡ�ϵͳ������رո�ʱ�ӡ� */
        unsigned int    ipcm_clk_en                : 1; /* [25..25] IPCMʱ��ʹ�ܡ�                            0����Ӱ�죻1��ʱ��ʹ�ܣ���ʱ��ϵͳ������һֱʹ�ܡ� */
        unsigned int    dw_ssi1_clk_en             : 1; /* [26..26] DW SSI1ʱ��ʹ�ܡ�                           0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    i2c1_clk_en                : 1; /* [27..27] I2C1ʱ��ʹ�ܡ�                             0����Ӱ�죻                                 1��ʱ��ʹ�� */
        unsigned int    gpio1_clk_en               : 1; /* [28..28] GPIO1����ʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    i2c0_clk_en                : 1; /* [29..29] I2C0ʱ��ʹ�ܡ�                             0����Ӱ�죻                                 1��ʱ��ʹ�� */
        unsigned int    gpio3_clk_en               : 1; /* [30..30] GPIO3����ʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    reserved_0                 : 1; /* [31..31] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKEN1_T;    /* ʱ��ʹ��1 */

typedef union
{
    struct
    {
        unsigned int    mst_aclk_dis               : 1; /* [0..0] AXI master����ʱ�ӹرտ��ơ�                        0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    dsp_aclk_dis               : 1; /* [1..1] DSP����ʱ�ӹرտ��ơ�                         0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    soc_hclk_dis               : 1; /* [2..2] SOC_HCLK/SOC_ASHB_PCLKʱ�ӹرտ��ơ���AHB��                     0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    amon_cpufast_clk_dis       : 1; /* [3..3] AMON_CPUFASTģ��ʱ�ӹرտ��ơ�                     0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    amon_soc_clk_dis           : 1; /* [4..4] ���� */
        unsigned int    tsensor_clk_dis            : 1; /* [5..5] TSENSORʱ�ӹرտ��ơ�                       0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    reserved_2                 : 2; /* [7..6] ���� */
        unsigned int    ipf_clk_dis                : 1; /* [8..8] IPFʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    reserved_1                 : 1; /* [9..9] ���� */
        unsigned int    edmac_ch4_clk_dis          : 1; /* [10..10] EDAMC_CH4ʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    socp_clk_dis               : 1; /* [11..11] SOCPʱ�ӹرտ��ơ�0����Ӱ�죻 1��ʱ�ӹر� */
        unsigned int    mipi_clk_dis               : 1; /* [12..12] MIPIʱ�ӹرտ��ơ�0����Ӱ�죻 1��ʱ�ӹر� */
        unsigned int    pmussi0_clk_dis            : 1; /* [13..13] PMUSSI0ʱ�ӹرտ��ơ�                           0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    pmussi1_clk_dis            : 1; /* [14..14] PMUSSI1ʱ�ӹرտ��ơ�                           0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    dw_ssi0_clk_dis            : 1; /* [15..15] DW SSI0ʱ�ӹرտ��ơ�                           0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    efuse_clk_dis              : 1; /* [16..16] EFUSEʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    nandc_clk_dis              : 1; /* [17..17] NANDCʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    hs_uart_clk_dis            : 1; /* [18..18] HS_UARTʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    emi_clk_dis                : 1; /* [19..19] EMIʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    edmac_clk_dis              : 1; /* [20..20] EDMAC_CH4ʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    bootrom_clk_dis            : 1; /* [21..21] BOOTROMʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    pwm2_clk_dis               : 1; /* [22..22] PWM2ʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    pwm1_clk_dis               : 1; /* [23..23] PWM1ʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    dt_clk_dis                 : 1; /* [24..24] DTʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    ipcm_clk_dis               : 1; /* [25..25] IPCMʱ�ӹرտ��ơ�                            0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    dw_ssi1_clk_dis            : 1; /* [26..26] DW SSI1ʱ�ӹرտ��ơ�                           0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    i2c1_clk_dis               : 1; /* [27..27] I2Cʱ�ӹرտ��ơ�                             0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    gpio1_clk_dis              : 1; /* [28..28] GPIO1ʱ�ӹرտ��ơ�                           0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    i2c0_clk_dis               : 1; /* [29..29] I2C0ʱ�ӹرտ��ơ�                           0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    gpio3_clk_dis              : 1; /* [30..30] GPIO3ʱ�ӹرտ��ơ�                           0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    reserved_0                 : 1; /* [31..31] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKDIS1_T;    /* ʱ�ӹر�1 */

typedef union
{
    struct
    {
        unsigned int    mst_aclk_status            : 1; /* [0..0] AXI masterʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    dsp_aclk_status            : 1; /* [1..1] DSP����ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    soc_hclk_status            : 1; /* [2..2] SOC_HCLK/SOC_ASHB_PCLKʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    amon_cpufast_clk_status    : 1; /* [3..3] AMON_CPUFASTʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    amon_soc_clk_status        : 1; /* [4..4] AMON_SOCʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    reserved_2                 : 3; /* [7..5] ���� */
        unsigned int    ipf_clk_status             : 1; /* [8..8] IPFʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    reserved_1                 : 1; /* [9..9] ���� */
        unsigned int    edmac_ch4_clk_status       : 1; /* [10..10] EDMAC_CH4ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    socp_clk_status            : 1; /* [11..11] SOCPʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    mipi_clk_status            : 1; /* [12..12] MIPIʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    pmussi0_clk_status         : 1; /* [13..13] PMUSSI1ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    pmussi1_clk_status         : 1; /* [14..14] PMUSSI1ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    dw_ssi0_clk_status         : 1; /* [15..15] DWSSI0ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    efuse_clk_status           : 1; /* [16..16] EFUSEʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    nandc_clk_status           : 1; /* [17..17] NANDCʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    hs_uart_clk_status         : 1; /* [18..18] HS_UARTʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    emi_clk_status             : 1; /* [19..19] EMIʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    edmac_clk_status           : 1; /* [20..20] EDMACʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    bootrom_clk_status         : 1; /* [21..21] BOOTROMʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    pwm2_clk_status            : 1; /* [22..22] PWM2ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    pwm1_clk_status            : 1; /* [23..23] PWM1ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    dt_clk_status              : 1; /* [24..24] DTʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    ipcm_clk_status            : 1; /* [25..25] IPCMʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    dw_ssi1_clk_status         : 1; /* [26..26] DWSSI1ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    i2c1_clk_status            : 1; /* [27..27] I2C1ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    gpio1_clk_status           : 1; /* [28..28] GPIO1ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    i2c0_clk_status            : 1; /* [29..29] I2C0ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    gpio3_clk_status           : 1; /* [30..30] GPIO3ʱ�ӿ���״̬��                            0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    reserved_0                 : 1; /* [31..31] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKSTAT1_T;    /* ʱ�ӿ���״̬1 */

typedef union
{
    struct
    {
        unsigned int    uart3_clk_en               : 1; /* [0..0] UART3����ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    uart2_clk_en               : 1; /* [1..1] UART2����ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    gpio2_clk_en               : 1; /* [2..2] GPIO2ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    cs_clk_en                  : 1; /* [3..3] CORESIGHTģ��ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    appa9_mbist_clk_en         : 1; /* [4..4] appa9_mbist_clkʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ���������ʱ�رո�ʱ�ӡ� */
        unsigned int    moda9_mbist_clk_en         : 1; /* [5..5] moda9_mbist_clkʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ���������ʱ�رո�ʱ�ӡ� */
        unsigned int    cpu_aclk_en                : 1; /* [6..6] CPU����ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ���bit���ڲ���Ŀ�ģ���������ʱһֱʹ�ܡ� */
        unsigned int    mddrc_clk_en               : 1; /* [7..7] MDDRCģ��ʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�ܡ���������ʱ����ʱ����Ҫһֱʹ�ܡ� */
        unsigned int    ddrphy_clk_en              : 1; /* [8..8] DDRPHYʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� ��������ʱ����ʱ����Ҫһֱʹ�ܡ� */
        unsigned int    ddrphy_ddr_clk_en          : 1; /* [9..9] DDRPHY_2XCLKʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� ��DDRPHY������PLL bypassģʽʱ����bit����һֱʹ�ܣ�������Թرո�ʱ�� */
        unsigned int    axi_mem_clk_en             : 1; /* [10..10] AXI_MEM_CLKʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    func_wakeup_pd_clk_en      : 1; /* [11..11] func_wakeupʱ��ʹ�ܿ��ơ�                              0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    soc_peri_usb_pd_clk_en     : 1; /* [12..12] SOC_PERI_USB��ѹ��ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    usbotg_clk_en              : 1; /* [13..13] USBOTGʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    usb_bc_clk_en              : 1; /* [14..14] USBOTG BCʱ��ʹ�ܿ��ơ� 0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    ssic_host_clk_en           : 1; /* [15..15] SSIC HOST������ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    ssic_dev_clk_en            : 1; /* [16..16] SSIC Device������ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    mmc0_clk_en                : 1; /* [17..17] MMC0ʱ��ʹ�ܿ��ơ�                              0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    mmc1_clk_en                : 1; /* [18..18] MMC1ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    mmc0_phase_clk_en          : 1; /* [19..19] MMC0����ʱ��ʹ�ܿ��ơ�                              0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    mmc1_phase_clk_en          : 1; /* [20..20] MMC1����ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    mmc0_refclk_en             : 1; /* [21..21] MMC0��������ʱ��ʹ�ܿ��ơ�                              0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    mmc1_refclk_en             : 1; /* [22..22] MMC1��������ʱ��ʹ�ܿ��ơ�                              0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    usbhsic_clk_en             : 1; /* [23..23] USBHSICʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    sdcc_clk_en                : 1; /* [24..24] SDCCʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    hpm_clk_en                 : 1; /* [25..25] HPM0-2ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ���ʱ�ӿ��Է��ü��ء� */
        unsigned int    sha1_clk_en                : 1; /* [26..26] SHA1ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ���ʱ�ӿ��Է��ü��ء� */
        unsigned int    pcie_ctrl_clk_en           : 2; /* [28..27] PCIE������ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ�Bit[27] - �������߽ӿ�ʱ�ӣ�bit[28] - ����PHY�ӿ�ʱ�ӣ�(core_clk��aux_clk�� */
        unsigned int    pcie_phy_clk_en            : 1; /* [29..29] PCIEPHYʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ� */
        unsigned int    reserved                   : 1; /* [30..30] ���� */
        unsigned int    wdog_clk_en                : 1; /* [31..31] WDOGʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�ܡ���ʱ��ϵͳ������һֱʹ�ܡ� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKEN2_T;    /* ʱ��ʹ��2 */

typedef union
{
    struct
    {
        unsigned int    uart3_clk_dis              : 1; /* [0..0] UART3����ʱ�ӹرտ��ơ�                        0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    uart2_clk_dis              : 1; /* [1..1] UART2����ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    gpio2_clk_dis              : 1; /* [2..2] GPIO2ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    cs_clk_dis                 : 1; /* [3..3] CORESIGHTģ��ʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    appa9_mbist_clk_dis        : 1; /* [4..4] appa9_mbist_clkʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    moda9_mbist_clk_dis        : 1; /* [5..5] moda9_mbist_clkʱ�ӹرտ��ơ�                              0����Ӱ�� ��                                 1��ʱ�ӹر� */
        unsigned int    cpu_aclk_dis               : 1; /* [6..6] CPU����ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    mddrc_clk_dis              : 1; /* [7..7] MDDRC������ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    ddrphy_clk_dis             : 1; /* [8..8] DDRPHYʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    ddrphy_ddr_clk_dis         : 1; /* [9..9] DDRPHY_2XCLKʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    axi_mem_clk_dis            : 1; /* [10..10] AXI_MEM_CLKʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    func_wake_pd_clk_dis       : 1; /* [11..11] func_wakeupʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    soc_usb_pd_clk_dis         : 1; /* [12..12] SOC_USB��ѹ��ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    usbotg_clk_dis             : 1; /* [13..13] USBOTGʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    usb_bc_clk_dis             : 1; /* [14..14] USBOTG BCʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    ssic_host_clk_dis          : 1; /* [15..15] SSIC HOST������ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    ssic_dev_clk_dis           : 1; /* [16..16] SSIC Device������ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    mmc0_clk_dis               : 1; /* [17..17] MMC0ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    mmc1_clk_dis               : 1; /* [18..18] MMC1ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    mmc0_phase_clk_dis         : 1; /* [19..19] MMC0����ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    mmc1_phase_clk_dis         : 1; /* [20..20] MMC1����ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    mmc0_refclk_dis            : 1; /* [21..21] MMC0��������ο�ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    mmc1_refclk_dis            : 1; /* [22..22] MMC1��������ο�ʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    usbhsic_clk_dis            : 1; /* [23..23] USBHSICʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    sdcc_clk_dis               : 1; /* [24..24] SDCCʱ�ӹرտ��ơ�                          0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    hpm_clk_dis                : 1; /* [25..25] HPM0-2ʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹɹرա���ʱ�ӿ��Է��ü��ء� */
        unsigned int    sha1_clk_dis               : 1; /* [26..26] SHA1ʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹɹرա���ʱ�ӿ��Է��ü��ء� */
        unsigned int    pcie_ctrl_clk_dis          : 2; /* [28..27] PCIE������ʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹɹرա� */
        unsigned int    pcie_phy_clk_dis           : 1; /* [29..29] PCIEPHYʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹɹرա� */
        unsigned int    reserved                   : 1; /* [30..30] ���� */
        unsigned int    wdog_clk_dis               : 1; /* [31..31] WDOGʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKDIS2_T;    /* ʱ�ӹر�2 */

typedef union
{
    struct
    {
        unsigned int    uart3_clk_status           : 1; /* [0..0] UART3����ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    uart2_clk_status           : 1; /* [1..1] UART2����ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    gpio2_clk_status           : 1; /* [2..2] GPIO2ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    cs_clk_status              : 1; /* [3..3] CORESIGHTģ��ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    appa9_mbist_clk_status     : 1; /* [4..4] appa9_mbist_clkʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    moda9_mbist_clk_status     : 1; /* [5..5] moda9_mbist_clkʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    cpu_aclk_status            : 1; /* [6..6] CPU����ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    mddrc_clk_status           : 1; /* [7..7] MDDRCģ��ʱ����״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    ddrphy_clk_status          : 1; /* [8..8] DDRPHYʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    ddrphy_ddr_clk_status      : 1; /* [9..9] DDRPHY_2XCLKʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    axi_mem_clk_status         : 1; /* [10..10] AXI_MEM_CLKʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    func_wake_pd_clk_status    : 1; /* [11..11] func_wakeup��ѹ��ʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    soc_usb_pd_clk_status      : 1; /* [12..12] SOC_USB��ѹ��ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    usbotg_clk_status          : 1; /* [13..13] USBOTGʱ��ʹ����״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    usb_bc_clk_status          : 1; /* [14..14] USBOTG BCʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    ssic_host_clk_status       : 1; /* [15..15] SSIC HOST������ʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    ssic_dev_clk_status        : 1; /* [16..16] SSIC Device������ʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    mmc0_clk_status            : 1; /* [17..17] MMC0ʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    mmc1_clk_status            : 1; /* [18..18] MMC1ʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    mmc0_phase_clk_status      : 1; /* [19..19] MMC0����ʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    mmc1_phase_clk_status      : 1; /* [20..20] MMC1����ʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    mmc0_refclk_status         : 1; /* [21..21] MMC0��������ο�ʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    mmc1_refclk_status         : 1; /* [22..22] MMC1��������ο�ʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    usbhsic_clk_status         : 1; /* [23..23] USBHSICʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    sdcc_clk_status            : 1; /* [24..24] SDCCʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    hpm_clk_status             : 1; /* [25..25] HPM0-2ʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�ܸ�ʱ�ӿ��Է��ü��ء� */
        unsigned int    sha1_clk_status            : 1; /* [26..26] SHA1ʱ�ӿ���״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�ܸ�ʱ�ӿ��Է��ü��ء� */
        unsigned int    pcie_ctrl_clk_status       : 2; /* [28..27] PCIE����������״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    pcie_phy_clk_status        : 1; /* [29..29] PCIEPHY����״̬��                     0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    reserved                   : 1; /* [30..30] ���� */
        unsigned int    wdog_clk_status            : 1; /* [31..31] WDOGʱ��״̬0��ʱ�ӹرգ�1��ʱ��ʹ�� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKSTAT2_T;    /* ʱ�ӿ���״̬2 */

typedef union
{
    struct
    {
        unsigned int    gpio0_clk_en               : 1; /* [0..0] GPIO0ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    uart0_clk_en               : 1; /* [1..1] UART0ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm0_clk_en                 : 1; /* [2..2] TIMER0ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm1_clk_en                 : 1; /* [3..3] TIMER1ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm2_clk_en                 : 1; /* [4..4] TIMER2ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm3_clk_en                 : 1; /* [5..5] TIMER3ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm4_clk_en                 : 1; /* [6..6] TIMER4ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm5_clk_en                 : 1; /* [7..7] TIMER5ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm6_clk_en                 : 1; /* [8..8] TIMER6ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm7_clk_en                 : 1; /* [9..9] TIMER7ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm8_clk_en                 : 1; /* [10..10] TIMER8ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm9_clk_en                 : 1; /* [11..11] TIMER9ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm10_clk_en                : 1; /* [12..12] TIMER10ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm11_clk_en                : 1; /* [13..13] TIMER11ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm12_clk_en                : 1; /* [14..14] TIMER12ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm13_clk_en                : 1; /* [15..15] TIMER13ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm14_clk_en                : 1; /* [16..16] TIMER14ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm15_clk_en                : 1; /* [17..17] TIMER15ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm16_clk_en                : 1; /* [18..18] TIMER16ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm17_clk_en                : 1; /* [19..19] TIMER17ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm18_clk_en                : 1; /* [20..20] TIMER18ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm19_clk_en                : 1; /* [21..21] TIMER19ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm20_clk_en                : 1; /* [22..22] TIMER20ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm21_clk_en                : 1; /* [23..23] TIMER21ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm22_clk_en                : 1; /* [24..24] TIMER22ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    tm23_clk_en                : 1; /* [25..25] TIMER23����ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    appa9_clk_en               : 1; /* [26..26] APPA9��ѹ��ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    mdma9_clk_en               : 1; /* [27..27] MDMA9��ѹ��ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    hifi_vic_clk_en            : 1; /* [28..28] DSP VIC�жϿ�����ʱ��ʹ�ܿ��ơ�                         0����Ӱ��1��ʱ��ʹ�� */
        unsigned int    lte_sio_clk_en             : 1; /* [29..29] LTE_SIO ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    hifi_dbg_clk_en            : 1; /* [30..30] HIFI Debugʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    hifi_clk_en                : 1; /* [31..31] HIFI��ϵͳʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKEN3_T;    /* ʱ��ʹ��3 */

typedef union
{
    struct
    {
        unsigned int    gpio0_clk_dis              : 1; /* [0..0] GPIO0ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    uart0_clk_dis              : 1; /* [1..1] UART0ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm0_clk_dis                : 1; /* [2..2] TIMER0ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm1_clk_dis                : 1; /* [3..3] TIMER1ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm2_clk_dis                : 1; /* [4..4] TIMER2ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm3_clk_dis                : 1; /* [5..5] TIMER3ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm4_clk_dis                : 1; /* [6..6] TIMER4ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm5_clk_dis                : 1; /* [7..7] TIMER5ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm6_clk_dis                : 1; /* [8..8] TIMER6ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm7_clk_dis                : 1; /* [9..9] TIMER7ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm8_clk_dis                : 1; /* [10..10] TIMER8ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm9_clk_dis                : 1; /* [11..11] TIMER9ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm10_clk_dis               : 1; /* [12..12] TIMER10ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm11_clk_dis               : 1; /* [13..13] TIMER11ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm12_clk_dis               : 1; /* [14..14] TIMER12ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm13_clk_dis               : 1; /* [15..15] TIMER13ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm14_clk_dis               : 1; /* [16..16] TIMER14ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm15_clk_dis               : 1; /* [17..17] TIMER15ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm16_clk_dis               : 1; /* [18..18] TIMER16ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm17_clk_dis               : 1; /* [19..19] TIMER17ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm18_clk_dis               : 1; /* [20..20] TIMER18ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm19_clk_dis               : 1; /* [21..21] TIMER19ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm20_clk_dis               : 1; /* [22..22] TIMER20�رտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm21_clk_dis               : 1; /* [23..23] TIMER21ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm22_clk_dis               : 1; /* [24..24] TIMER22ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    tm23_clk_dis               : 1; /* [25..25] TIMER23ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    appa9_clk_dis              : 1; /* [26..26] APPA9��ѹ��ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    mdma9_clk_dis              : 1; /* [27..27] MDMA9��ѹ��ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    hifi_vic_clk_dis           : 1; /* [28..28] HIFI VIC�жϿ�����ʱ�ӹرտ��ơ�                         0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    lte_sio_clk_dis            : 1; /* [29..29] LTE_SIO ʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
        unsigned int    hifi_dbg_clk_dis           : 1; /* [30..30] HIFI Debugʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
        unsigned int    hifi_clk_dis               : 1; /* [31..31] HIFI��ϵͳʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKDIS3_T;    /* ʱ�ӹر�3 */

typedef union
{
    struct
    {
        unsigned int    gpio0_clk_status           : 1; /* [0..0] GPIO0ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    uart0_clk_status           : 1; /* [1..1] UART0ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm0_clk_status             : 1; /* [2..2] TIMER0ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm1_clk_status             : 1; /* [3..3] TIMER1ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm2_clk_status             : 1; /* [4..4] TIMER2ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm3_clk_status             : 1; /* [5..5] TIMER3ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm4_clk_status             : 1; /* [6..6] TIMER4ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm5_clk_status             : 1; /* [7..7] TIMER5ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm6_clk_status             : 1; /* [8..8] TIMER6ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm7_clk_status             : 1; /* [9..9] TIMER7ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm8_clk_status             : 1; /* [10..10] TIMER8ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm9_clk_status             : 1; /* [11..11] TIMER9ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm10_clk_status            : 1; /* [12..12] TIMER10ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm11_clk_status            : 1; /* [13..13] TIMER11ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm12_clk_status            : 1; /* [14..14] TIMER12ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm13_clk_status            : 1; /* [15..15] TIMER13ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm14_clk_status            : 1; /* [16..16] TIMER14ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm15_clk_status            : 1; /* [17..17] TIMER15ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm16_clk_status            : 1; /* [18..18] TIMER16ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm17_clk_status            : 1; /* [19..19] TIMER17ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm18_clk_status            : 1; /* [20..20] TIMER18ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm19_clk_status            : 1; /* [21..21] TIMER19ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm20_clk_status            : 1; /* [22..22] TIMER20ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm21_clk_status            : 1; /* [23..23] TIMER21ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm22_clk_status            : 1; /* [24..24] TIMER22ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    tm23_clk_status            : 1; /* [25..25] TIMER23ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    appa9_clk_status           : 1; /* [26..26] APPA9��ѹ��ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    mdma9_clk_status           : 1; /* [27..27] MDMA9��ѹ��ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    hifi_vic_clk_status        : 1; /* [28..28] HIFI VIC�жϿ�����ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    lte_sio_clk_status         : 1; /* [29..29] LTE_SIO ʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    hifi_dbg_clk_status        : 1; /* [30..30] HIFI Debugʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
        unsigned int    hifi_clk_status            : 1; /* [31..31] HIFI��ϵͳʱ�ӿ���״̬��                         0��ʱ�ӹرգ�                                 1��ʱ��ʹ�� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKSTAT3_T;    /* ʱ�ӿ���״̬3 */

typedef union
{
    struct
    {
        unsigned int    dsp0_pd_clk_en             : 1; /* [0..0] DSP��ϵͳʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    dsp0_core_clk_en           : 1; /* [1..1] DSP��ϵͳCOREʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    dsp0_dbg_clk_en            : 1; /* [2..2] DSP��ϵͳDBGʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    reserved_1                 : 4; /* [6..3] ���� */
        unsigned int    guacc_axi_clk_en           : 1; /* [7..7] GUACC������ʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    cicom0_clk_en              : 1; /* [8..8] CICOM0ʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    cicom1_clk_en              : 1; /* [9..9] CICOM1ʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    hdlc_clk_en                : 1; /* [10..10] HDLCʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    upacc_clk_en               : 1; /* [11..11] UPACCʱ��ʹ�ܡ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    sci0_clk_en                : 1; /* [12..12] SCI0ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    sci1_clk_en                : 1; /* [13..13] SCI1ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    uicc_clk_en                : 1; /* [14..14] UICCģ��ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    uart1_clk_en               : 1; /* [15..15] UART1����ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    dsp_vic_clk_en             : 1; /* [16..16] DSP0 VIC�жϿ�����ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    cipher_clk_en              : 1; /* [17..17] CIPHER�жϿ�����ʱ��ʹ�ܿ��ơ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    gmac_rx_clk_en             : 1; /* [18..18] GMAC���շ���Ľ���ʱ��ʹ�ܿ���0:��Ӱ�죻1:ʱ��ʹ�� */
        unsigned int    gmac_tx_clk_en             : 1; /* [19..19] GMAC���ͷ���ķ���ʱ��ʹ�ܿ���0:��Ӱ�죻1:ʱ��ʹ�� */
        unsigned int    gmac_gtx_clk_en            : 1; /* [20..20] RGMII�ӿڵķ�����·ʱ��ʹ�ܿ���0:��Ӱ�죻1:ʱ��ʹ�� */
        unsigned int    gmac_switch_clk_en         : 1; /* [21..21] GMAC125Mʱ��ʹ�ܿ��ƣ�0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    gmac_aclk_en               : 1; /* [22..22] GMAC����ʱ��ʹ�ܿ���0����Ӱ�죻1��ʱ��ʹ�� */
        unsigned int    reserved_0                 : 9; /* [31..23] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKEN4_T;    /* ʱ��ʹ��4(MCPU����) */

typedef union
{
    struct
    {
        unsigned int    dsp0_pd_clk_dis            : 1; /* [0..0] DSP��ϵͳʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
        unsigned int    dsp0_core_clk_dis          : 1; /* [1..1] DSP��ϵͳCOREʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
        unsigned int    dsp0_dbg_clk_dis           : 1; /* [2..2] DSP��ϵͳDBGʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
        unsigned int    reserved_1                 : 4; /* [6..3] ���� */
        unsigned int    guacc_axi_clk_dis          : 1; /* [7..7] GUACC������ʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
        unsigned int    cicom0_clk_dis             : 1; /* [8..8] CICOM0ʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
        unsigned int    cicom1_clk_dis             : 1; /* [9..9] CICOM1ʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
        unsigned int    hdlc_clk_dis               : 1; /* [10..10] HDLCʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
        unsigned int    upacc_clk_dis              : 1; /* [11..11] UPACCʱ�ӹرտ��ơ�0����Ӱ�죻1��ʱ�ӹر� */
        unsigned int    sci0_clk_dis               : 1; /* [12..12] SCI0ʱ�ӹرտ��ơ�                            0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    sci1_clk_dis               : 1; /* [13..13] SCI1ʱ�ӹرտ��ơ�                            0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    uicc_clk_dis               : 1; /* [14..14] UICCģ��ʱ�ӹرտ��ơ�                            0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    uart1_clk_dis              : 1; /* [15..15] UART1����ʱ�ӹرտ��ơ�                            0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    dsp_vic_clk_dis            : 1; /* [16..16] DSP0 VIC�жϿ�����ʱ�ӹرտ��ơ�                            0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    cipher_clk_dis             : 1; /* [17..17] CIPHER�жϿ�����ʱ�ӹرտ��ơ�                            0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    gmac_rx_clk_dis            : 1; /* [18..18] GMAC���շ���Ľ���ʱ�ӹرտ���0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    gmac_tx_clk_dis            : 1; /* [19..19] GMAC���ͷ���ķ���ʱ�ӹرտ���0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    gmac_gtx_clk_dis           : 1; /* [20..20] RGMII�ӿڵķ�����·ʱ�ӹرտ���0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    gmac_switch_clk_dis        : 1; /* [21..21] GMAC125Mʱ�ӹرտ��ƣ�0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    gmac_aclk_dis              : 1; /* [22..22] GMAC����ʱ�ӹرտ���0����Ӱ�죻                                  1��ʱ�ӹر� */
        unsigned int    reserved_0                 : 9; /* [31..23] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKDIS4_T;    /* ʱ�ӹر�4(MCPU����) */

typedef union
{
    struct
    {
        unsigned int    dsp0_pd_clk_status         : 1; /* [0..0] DSP��ϵͳʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    dsp0_core_clk_status       : 1; /* [1..1] DSP��ϵͳCOREʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    dsp0_dbg_clk_status        : 1; /* [2..2] DSP��ϵͳDBGʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    reserved_1                 : 4; /* [6..3] ���� */
        unsigned int    guacc_axi_clk_status       : 1; /* [7..7] GUACC������ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    cicom0_clk_status          : 1; /* [8..8] CICOM0ʱ�ӿ��ƿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    cicom1_clk_status          : 1; /* [9..9] CICOM1ʱ�ӿ��ƿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    hdlc_clk_status            : 1; /* [10..10] HDLCʱ�ӿ��ƿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    upacc_clk_status           : 1; /* [11..11] UPACCʱ�ӿ��ƿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    sci0_clk_status            : 1; /* [12..12] SCI0ʱ�ӿ��ƿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    sci1_clk_status            : 1; /* [13..13] SCI1ʱ�ӿ��ƿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    uicc_clk_status            : 1; /* [14..14] UICCģ��ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    uart1_clk_status           : 1; /* [15..15] UART1����ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    dsp_vic_clk_status         : 1; /* [16..16] DSP0 VIC�жϿ�����ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    cipher_clk_status          : 1; /* [17..17] CIPHER������ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    gmac_rx_clk_status         : 1; /* [18..18] GMAC���շ���Ľ���ʱ�ӿ���״̬0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    gmac_tx_clk_status         : 1; /* [19..19] GMAC���ͷ���ķ���ʱ�ӿ���״̬0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    gmac_gtx_clk_status        : 1; /* [20..20] RGMII�ӿڵķ�����·ʱ�ӿ���״̬0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    gmac_switch_clk_status     : 1; /* [21..21] GMAC125Mʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    gmac_aclk_status           : 1; /* [22..22] GMAC����ʱ�ӿ���״̬0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    reserved_0                 : 9; /* [31..23] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKSTAT4_T;    /* ʱ�ӿ���״̬4(MCPU����) */

typedef union
{
    struct
    {
        unsigned int    bbp_ao_clk_en              : 1; /* [0..0] BBP AO��ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    bbpcommon_2a_clk_en        : 1; /* [1..1] BBPCOMMONģ��ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    ltebbp_pd_clk_en           : 1; /* [2..2] LTE BBP������ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    g1bbp_pd_clk_en            : 1; /* [3..3] G1 BBP������ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    g2bbp_pd_clk_en            : 1; /* [4..4] G2 BBP������ʱ��ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    twbbp_pd_clk_en            : 1; /* [5..5] TW BBP������ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    wbbp_pd_clk_en             : 1; /* [6..6] WBBP������ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    irm_pd_clk_en              : 1; /* [7..7] IRM BBP������ʱ��ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    lbbp_axi_clk_en            : 1; /* [8..8] LTE BBP������AXI�ӿ�ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    lbbp_pdt_clk_en            : 1; /* [9..9] LTE BBP������ʱ�򲿷�ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    lbbp_pdf_clk_en            : 1; /* [10..10] LTE BBP������Ƶ�򲿷�ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    lbbp_tdl_clk_en            : 1; /* [11..11] LTE BBP������TDL���ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    lbbp_vdl_clk_en            : 1; /* [12..12] LTE BBP������VDL���ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    lbbp_tds_clk_en            : 1; /* [13..13] LTE BBP������Ƶ�򲿷�ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    reserved_1                 : 2; /* [15..14] ���� */
        unsigned int    irm_turbo_clk_en           : 1; /* [16..16] IRM BBP������ turboʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    irm_bbc_245m_clk_en        : 1; /* [17..17] IRM BBP������ 245MHzʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    irm_wbbp_122m_clk_en       : 1; /* [18..18] IRM BBP����122MHzʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    twbbp_wbbp_122m_clk_en     : 1; /* [19..19] WTDS/W BBP������TDSģ122MHzʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    twbbp_wbbp_61m_clk_en      : 1; /* [20..20] TDS/W BBP������ WBBP 61MHzʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    twbbp_tbbp_122m_clk_en     : 1; /* [21..21] PDTW BBP������tbbp 122MHzʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    twbbp_tbbp_245m_clk_en     : 1; /* [22..22] PDTW BBP������tbbp 245MHzʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    wbbp_61m_clk_en            : 1; /* [23..23] PDW BBP������61MHzʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    wbbp_122m_clk_en           : 1; /* [24..24] PDW BBP������122MHzʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    wbbp_245m_clk_en           : 1; /* [25..25] PDW BBP������245MHzʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    wbbp_axi_clk_en            : 1; /* [26..26] PDW BBP������AXIʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    reserved_0                 : 5; /* [31..27] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKEN5_T;    /* ʱ��ʹ��5��BBP�� */

typedef union
{
    struct
    {
        unsigned int    bbp_ao_clk_dis             : 1; /* [0..0] BBP AO��ʱ��ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    bbpcommon_clk_dis          : 1; /* [1..1] BBPCOMMONģ��ʱ��ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    ltebbp_pd_clk_dis          : 1; /* [2..2] LTE BBP������ʱ��ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    g1bbp_pd_clk_dis           : 1; /* [3..3] G1 BBP������ʱ��ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    g2bbp_pd_clk_dis           : 1; /* [4..4] G2 BBP������ʱ��ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    twbbp_pd_clk_dis           : 1; /* [5..5] TW BBP������ʱ��ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    wbbp_pd_clk_dis            : 1; /* [6..6] WBBP������ʱ��ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    irm_pd_clk_dis             : 1; /* [7..7] IRM BBP������ʱ��ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    lbbp_axi_clk_dis           : 1; /* [8..8] LTE BBP������AXI�ӿ�ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    lbbp_pdt_clk_dis           : 1; /* [9..9] LTE BBP������ʱ�򲿷�ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    lbbp_pdf_clk_dis           : 1; /* [10..10] LTE BBP������Ƶ�򲿷�ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    lbbp_tdl_clk_dis           : 1; /* [11..11] LTE BBP������TDL���ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    lbbp_vdl_clk_dis           : 1; /* [12..12] LTE BBP������VDL���ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    lbbp_tds_clk_dis           : 1; /* [13..13] LTE BBP������Ƶ�򲿷�ʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    twbbp_tbbp_clk_dis         : 1; /* [14..14] WTDS/W BBP������TDSģʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    twbbp_wbbp_clk_dis         : 1; /* [15..15] TDS/W BBP������ WBBPʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    irm_turbo_clk_dis          : 1; /* [16..16] IRM BBP������ turboʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    irm_bbc_245m_clk_dis       : 1; /* [17..17] IRM BBP������ 245MHzʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    irm_wbbp_122m_clk_dis      : 1; /* [18..18] IRM BBP����122MHzʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    pdtw_wbbp_122m_clk_dis     : 1; /* [19..19] PDTW BBP������wbbp 122MHzʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    pdtw_wbbp_61m_clk_dis      : 1; /* [20..20] PDTW BBP������wbbp 61MHzʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    pdtw_tbbp_122m_clk_dis     : 1; /* [21..21] PDTW BBP������tbbp 122MHzʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    pdtw_tbbp_245m_clk_dis     : 1; /* [22..22] PDTW BBP������tbbp 245MHzʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    pdw_61m_clk_dis            : 1; /* [23..23] PDW BBP������61MHzʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    pdw_122m_clk_dis           : 1; /* [24..24] PDW BBP������122MHzʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    pdw_245m_clk_dis           : 1; /* [25..25] PDW BBP������245MHzʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    pdw_axi_clk_dis            : 1; /* [26..26] PDW BBP������AXIʱ�ӹرտ��ơ�1 - ʱ�ӹر�0 - ��Ӱ�� */
        unsigned int    reserved                   : 5; /* [31..27] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKDIS5_T;    /* ʱ�ӹر�5 */

typedef union
{
    struct
    {
        unsigned int    bbp_ao_clk_stat            : 1; /* [0..0] BBP AO��ʱ��ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    bbpcommon_2a_clk_stat      : 1; /* [1..1] BBPCOMMONģ��ʱ��ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    ltebbp_pd_clk_stat         : 1; /* [2..2] LTE BBP������ʱ��ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    g1bbp_pd_clk_stat          : 1; /* [3..3] G1 BBP������ʱ��ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    g2bbp_pd_clk_stat          : 1; /* [4..4] G2 BBP������ʱ��ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    twbbp_pd_clk_stat          : 1; /* [5..5] TW BBP������ʱ��ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    wbbp_pd_clk_stat           : 1; /* [6..6] WBBP������ʱ��ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    irm_pd_clk_stat            : 1; /* [7..7] IRM BBP(BBPCOMMON_2B)������ʱ��ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    lbbp_axi_clk_stat          : 1; /* [8..8] LTE BBP������AXI�ӿ�ʱ��ʹ�ܿ��ơ�1 - ʱ�Ӵ�0 - ��Ӱ�� */
        unsigned int    lbbp_pdt_clk_stat          : 1; /* [9..9] LTE BBP������ʱ�򲿷�ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    lbbp_pdf_clk_stat          : 1; /* [10..10] LTE BBP������Ƶ�򲿷�ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    lbbp_tdl_clk_stat          : 1; /* [11..11] LTE BBP������TDL���ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    lbbp_vdl_clk_stat          : 1; /* [12..12] LTE BBP������VDL���ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    lbbp_tds_clk_stat          : 1; /* [13..13] LTE BBP������tds����ʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    twbbp_tbbp_clk_stat        : 1; /* [14..14] TDS/W BBP������TDSģʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    twbbp_wbbp_clk_stat        : 1; /* [15..15] TDS/W BBP������ WBBPģʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    irm_turbo_clk_stat         : 1; /* [16..16] IRM BBP������ turboʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    irm_bbc_245m_clk_status    : 1; /* [17..17] IRM BBP������ 245MHzʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    irm_wbbp_122m_clk_status   : 1; /* [18..18] IRM BBP����122MHzʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    pdtw_wbbp_122m_clk_status  : 1; /* [19..19] PDTW BBP������wbbp 122MHzʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    pdtw_wbbp_61m_clk_status   : 1; /* [20..20] PDTW BBP������wbbp 61MHzʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    pdtw_tbbp_122m_clk_status  : 1; /* [21..21] PDTW BBP������tbbp 122MHzʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    pdtw_tbbp_245m_clk_status  : 1; /* [22..22] PDTW BBP������tbbp 245MHzʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    pdw_61m_clk_status         : 1; /* [23..23] PDW BBP������61MHzʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    pdw_122m_clk_status        : 1; /* [24..24] PDW BBP������122MHzʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    pdw_245m_clk_status        : 1; /* [25..25] PDW BBP������245MHzʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    pdw_axi_clk_status         : 1; /* [26..26] PDW BBP������AXIʱ�ӿ���״̬��0��ʱ�ӹرգ�1��ʱ��ʹ�� */
        unsigned int    reserved                   : 5; /* [31..27] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKSTAT5_T;    /* ʱ�ӿ���״̬5 */

typedef union
{
    struct
    {
        unsigned int    appa9_cpu_srst_en          : 1; /* [0..0] APPA9 CPU CORE��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    appa9_dbg_srst_en          : 1; /* [1..1] APPA9 Debug��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    appa9_peri_srst_en         : 1; /* [2..2] APPA9������λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    appa9_scu_srst_en          : 1; /* [3..3] APPA9 SCU��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    appa9_ptm_srst_en          : 1; /* [4..4] APPA9 PTM��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    appa9_wd_srst_en           : 1; /* [5..5] APPA9 WD��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    moda9_cpu_srst_en          : 1; /* [6..6] MODA9 CPU CORE��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    moda9_dbg_srst_en          : 1; /* [7..7] MODA9 Debug��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    moda9_peri_srst_en         : 1; /* [8..8] MODA9 ������λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    moda9_scu_srst_en          : 1; /* [9..9] MODA9 SCU��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    moda9_ptm_srst_en          : 1; /* [10..10] MODA9 PTM��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    moda9_wd_srst_en           : 1; /* [11..11] MODA9 WD��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    hpm_srst_en                : 1; /* [12..12] HPM0-2��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    hpm_clkdiv_srst_en         : 1; /* [13..13] HPMʱ�ӷ�Ƶ����λʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    appa9_srst_en              : 1; /* [14..14] APPA9�ϵ縴λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    mdma9_srst_en              : 1; /* [15..15] MDMA9�ϵ縴λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    cm3_dbg_srst_en            : 1; /* [16..16] CM3 Debug��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    mddrc_srst_en              : 1; /* [17..17] MDDRC��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    cm3_cpu_srst_en            : 1; /* [18..18] CM3 CORE��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    cicom0_srst_en             : 1; /* [19..19] CICOM0��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    cicom1_srst_en             : 1; /* [20..20] CICOM1��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    hdlc_srst_en               : 1; /* [21..21] HDLC��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    upacc_srst_en              : 1; /* [22..22] UPACC��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    edmac_ch4_srst_en          : 1; /* [23..23] EDMAC��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    edmac_srst_en              : 1; /* [24..24] EDMAC��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    emi_srst_en                : 1; /* [25..25] EMI��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    uicc_srst_en               : 1; /* [26..26] UICC��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    reserved                   : 1; /* [27..27] ���� */
        unsigned int    amon_cpufast_srst_en       : 1; /* [28..28] CPUFAST AMONITOR��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    amon_soc_srst_en           : 1; /* [29..29] SOC AMONITOR��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    dt_srst_en                 : 1; /* [30..30] DT��λ��������ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    sha1_srst_en               : 1; /* [31..31] SHA1��λ��������ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
    } bits;
    unsigned int    u32;
}HI_CRG_SRSTEN1_T;    /* ��λ����ʹ��1 */

typedef union
{
    struct
    {
        unsigned int    appa9_cpu_srst_dis         : 1; /* [0..0] APPA9 CPU CORE��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    appa9_dbg_srst_dis         : 1; /* [1..1] APPA9 Debug��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    appa9_peri_srst_dis        : 1; /* [2..2] APPA9������λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    appa9_scu_srst_dis         : 1; /* [3..3] APPA9 SCU��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    appa9_ptm_srst_dis         : 1; /* [4..4] APPA9 PTM��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    appa9_wd_srst_dis          : 1; /* [5..5] APPA9 WD��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    moda9_cpu_srst_dis         : 1; /* [6..6] MODA9 CPU CORE��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    moda9_dbg_srst_dis         : 1; /* [7..7] MODA9 Debug��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    moda9_peri_srst_dis        : 1; /* [8..8] MODA9 ������λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    moda9_scu_srst_dis         : 1; /* [9..9] MODA9 SCU��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    moda9_ptm_srst_dis         : 1; /* [10..10] MODA9 PTM��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    moda9_wd_srst_dis          : 1; /* [11..11] MODA9 WD��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    hpm_srst_dis               : 1; /* [12..12] HPM0-2��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    hpm_clkdiv_srst_dis        : 1; /* [13..13] HPMʱ�ӷ�Ƶ����λ�رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    appa9_srst_dis             : 1; /* [14..14] APPA9�ϵ縴λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    mdma9_srst_dis             : 1; /* [15..15] MDMA9�ϵ縴λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    cm3_dbg_srst_dis           : 1; /* [16..16] CM3 Debug��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    mddrc_srst_dis             : 1; /* [17..17] MDDRC��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    cm3_cpu_srst_dis           : 1; /* [18..18] CM3 COREg��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    cicom0_srst_dis            : 1; /* [19..19] CICOM0��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    cicom1_srst_dis            : 1; /* [20..20] CICOM1��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    hdlc_srst_dis              : 1; /* [21..21] HDLC��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    upacc_srst_dis             : 1; /* [22..22] UPACC��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    edmac_ch4_srst_dis         : 1; /* [23..23] EDMAC��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    edmac_srst_dis             : 1; /* [24..24] EDMAC��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    emi_srst_dis               : 1; /* [25..25] EMI��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    uicc_srst_dis              : 1; /* [26..26] UICC��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    reserved                   : 1; /* [27..27] ���� */
        unsigned int    amon_cpufast_srst_dis      : 1; /* [28..28] CPUFAST AMONITOR��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    amon_soc_srst_dis          : 1; /* [29..29] SOC AMONITOR��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    dt_srst_dis                : 1; /* [30..30] DT��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    sha1_srst_dis              : 1; /* [31..31] SHA1��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
    } bits;
    unsigned int    u32;
}HI_CRG_SRSTDIS1_T;    /* ��λ����ر�1 */

typedef union
{
    struct
    {
        unsigned int    appa9_cpu_srst_status      : 1; /* [0..0] APPA9 CPU CORE��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    appa9_dbg_srst_status      : 1; /* [1..1] APPA9 Debug��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    appa9_peri_srst_status     : 1; /* [2..2] APPA9������λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    appa9_scu_srst_status      : 1; /* [3..3] APPA9 SCU��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    appa9_ptm_srst_status      : 1; /* [4..4] APPA9 PTM��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    appa9_wd_srst_status       : 1; /* [5..5] APPA9 WD��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    moda9_cpu_srst_status      : 1; /* [6..6] MODA9 CPU CORE��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    moda9_dbg_srst_status      : 1; /* [7..7] MODA9 Debug��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    moda9_peri_srst_status     : 1; /* [8..8] MODA9 ������λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    moda9_scu_srst_status      : 1; /* [9..9] MODA9 SCU��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    moda9_ptm_srst_status      : 1; /* [10..10] MODA9 PTM��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    moda9_wd_srst_status       : 1; /* [11..11] MODA9 WD��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    hpm_srst_status            : 1; /* [12..12] HPM0-2��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    hpm_clkdiv_srst_status     : 1; /* [13..13] HPMʱ�ӷ�Ƶ����λ״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    appa9_srst_status          : 1; /* [14..14] APPA9�ϵ縴λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    mdma9_srst_status          : 1; /* [15..15] MDMA9�ϵ縴λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    cm3_dbg_srst_status        : 1; /* [16..16] CM3 Debug��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    mddrc_srst_status          : 1; /* [17..17] MDDRC��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    cm3_core_srst_status       : 1; /* [18..18] CM3 Debug��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    cicom0_srst_status         : 1; /* [19..19] CICOM0��λ����״̬���ơ�0����λ������Ч 1����λ������Ч */
        unsigned int    cicom1_srst_status         : 1; /* [20..20] CICOM1��λ����״̬���ơ�0����λ������Ч 1����λ������Ч */
        unsigned int    hdlc_srst_status           : 1; /* [21..21] HDLC��λ����״̬���ơ�0����λ������Ч 1����λ������Ч */
        unsigned int    upacc_srst_status          : 1; /* [22..22] UPACC��λ����״̬���ơ�0����λ������Ч 1����λ������Ч */
        unsigned int    edmac_ch4_srst_status      : 1; /* [23..23] EDMAC��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    edmac_srst_status          : 1; /* [24..24] EDMAC��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    emi_srst_status            : 1; /* [25..25] EMI��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    uicc_srst_status           : 1; /* [26..26] UICC��λ����״̬���ơ�0����λ������Ч 1����λ������Ч */
        unsigned int    reserved                   : 1; /* [27..27] ���� */
        unsigned int    amon_cpufast_srst_status   : 1; /* [28..28] CPUFAST AMONITOR��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    amon_soc_srst_status       : 1; /* [29..29] SOC AMONITOR��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    dt_srst_status             : 1; /* [30..30] DT��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    sha1_srst_status           : 1; /* [31..31] SHA1��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
    } bits;
    unsigned int    u32;
}HI_CRG_SRSTSTAT1_T;    /* ��λ����״̬1 */

typedef union
{
    struct
    {
        unsigned int    tensi_dps0_pd_srst_en      : 1; /* [0..0] Tensi dsp0��ϵͳ��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    tensi_dsp0_core_srst_en    : 1; /* [1..1] Tensi dsp0 core��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    tensi_dsp0_dbg_srst_en     : 1; /* [2..2] Tensi dsp0 DBG��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч    DSP debug����߼�����bit��0����λ������ƣ�DSP�µ�ʱ����Ҫ���ø�bit��λdebug����߼� */
        unsigned int    reserved_3                 : 1; /* [3..3] ���� */
        unsigned int    func_wakeup_pd_srst_en     : 1; /* [4..4] func_wakeup���縴λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    soc_peri_usb_pd_srst_en    : 1; /* [5..5] SOC_PERI_USB��ѹ����縴λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    mmc0_srst_en               : 1; /* [6..6] MMC0��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    mmc1_srst_en               : 1; /* [7..7] MMC1��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    sdcc_srst_en               : 1; /* [8..8] SDCC��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    rserved                    : 2; /* [10..9] ���� */
        unsigned int    gmac_srst_req              : 1; /* [11..11] GMAC��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    reserved_2                 : 2; /* [13..12] ������ */
        unsigned int    pcie_ctrl_srst_req         : 1; /* [14..14] PCIE��������λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    pcie_phy_srst_req          : 1; /* [15..15] PCIE PHY��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    ddrphy_div_srst_req        : 1; /* [16..16] ddrphy ctl clk��Ƶ����λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    reserved_1                 : 1; /* [17..17] ���� */
        unsigned int    hifi_core_srst_en          : 1; /* [18..18] HIFI DSP CORE��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    hifi_pd_srst_en            : 1; /* [19..19] HIFI ��DBG�����λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������ЧĬ��HIFI��ϵͳ��λ��ʱ��ʱ�ܡ� */
        unsigned int    hifi_dbg_srst_en           : 1; /* [20..20] HIFI DBG��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������ЧHIFI debug����߼�����bit��0�����ƣ�HIFI��ϵͳ�µ�ʱ����Ҫ���ø�bit��λdebug����߼��� */
        unsigned int    usbotg_bc_srst_en          : 1; /* [21..21] USB_BC��������λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbotg_phy_srst_en         : 1; /* [22..22] USBOTG PHY��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbotg_ctrl_srst_en        : 1; /* [23..23] USBOTG ctrl��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbotg_ctrl_vaux_srst_en   : 1; /* [24..24] USBOTG VAUX��������λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbotg_ctrl_vcc_srst_en    : 1; /* [25..25] USBOTG VCC��������λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbhsic_ctrl_srst_en       : 1; /* [26..26] USBHSIC��������λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbhsic_phy_srst_en        : 1; /* [27..27] USBHSIC PHY��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    cs_srst_en                 : 1; /* [28..28] CS��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    tsensor_srst_en            : 1; /* [29..29] TSENSOR��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    reserved_0                 : 2; /* [31..30] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_SRSTEN2_T;    /* ��λ����ʹ��2 */

typedef union
{
    struct
    {
        unsigned int    tensi_dps0_pd_srst_dis     : 1; /* [0..0] Tensi dsp0��ϵͳ��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    tensi_dsp0_core_srst_dis   : 1; /* [1..1] Tensi dsp0 core��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    tensi_dsp0_dbg_srst_dis    : 1; /* [2..2] Tensi dsp0 DBG��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    reserved_3                 : 1; /* [3..3] ���� */
        unsigned int    func_wakeup_pd_srst_dis    : 1; /* [4..4] func_wakeup���縴λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    soc_peri_usb_pd_srst_dis   : 1; /* [5..5] SOC_PERI_USB��ѹ����縴λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    mmc0_srst_dis              : 1; /* [6..6] MMC0��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    mmc1_srst_dis              : 1; /* [7..7] MMC1��λ����ʹ�رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    sdcc_srst_dis              : 1; /* [8..8] SDCC��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    reserved_2                 : 2; /* [10..9] ���� */
        unsigned int    gmac_srst_dis              : 1; /* [11..11] GMAC��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    ssicdev_ctrl_srst_dis      : 1; /* [12..12] SSIC Device��������λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    ssicphy_srst_dis           : 1; /* [13..13] SSIC PHY��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    pcie_ctrl_srst_dis         : 1; /* [14..14] PCIE��������λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    pcie_phy_srst_dis          : 1; /* [15..15] PCIE PHY��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    ddrphy_div_srst_dis        : 1; /* [16..16] ddrphy ctl clk��Ƶ����λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    reserved_1                 : 1; /* [17..17] ���� */
        unsigned int    hifi_core_srst_dis         : 1; /* [18..18] HIFI DSP CORE����λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    hifi_pd_srst_dis           : 1; /* [19..19] HIFI ��DBG�����λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    hifi_dbg_srst_dis          : 1; /* [20..20] HIFI DBG��λ����ʹ�ܿ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbotg_bc_srst_dis         : 1; /* [21..21] USB_BC��������λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbotg_phy_srst_dis        : 1; /* [22..22] USBOTG PHY��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbotg_ctrl_srst_dis       : 1; /* [23..23] USBOTG ctrl��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbotg_ctrl_vaux_srst_dis  : 1; /* [24..24] USBOTG VAUX��������λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbotg_ctrl_vcc_srst_dis   : 1; /* [25..25] USBOTG VCC��������λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbhsic_ctrl_srst_dis      : 1; /* [26..26] USBHSIC��������λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    usbhsic_phy_srst_dis       : 1; /* [27..27] USBHSIC PHY��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    cs_srst_dis                : 1; /* [28..28] Coresight��λ����رտ��ơ�0����Ӱ�죻1����λ������Ч */
        unsigned int    tsensor_srst_dis           : 1; /* [29..29] TSENSOR��λ����رտ��ơ�0����Ӱ��1����λ������Ч */
        unsigned int    reserved_0                 : 2; /* [31..30] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_SRSTDIS2_T;    /* ��λ����ر�2 */

typedef union
{
    struct
    {
        unsigned int    tensi_dps0_pd_srst_status  : 1; /* [0..0] Tensi dsp0��ϵͳ��λ����״̬���ơ�0����λ������Ч 1����λ������Ч */
        unsigned int    tensi_dsp0_core_srst_status : 1; /* [1..1] Tensi dsp0 core��λ����״̬���ơ�0����λ������Ч 1����λ������Ч */
        unsigned int    tensi_dsp0_dbg_srst_status : 1; /* [2..2] Tensi dsp0 DBG��λ����״̬���ơ�0����λ������Ч 1����λ������Ч */
        unsigned int    reserved_3                 : 1; /* [3..3] ���� */
        unsigned int    func_wakeup_pd_srst_status : 1; /* [4..4] func_wakeup���縴λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    soc_peri_usb_pd_srst_status : 1; /* [5..5] SOC_PERI_USB���縴λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    mmc0_srst_status           : 1; /* [6..6] MMC0��λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    mmc1_srst_status           : 1; /* [7..7] MMC1��λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    sdcc_srst_status           : 1; /* [8..8] SDCC��λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    reserved_2                 : 2; /* [10..9] ���� */
        unsigned int    gmac_srst_status           : 1; /* [11..11] GMAC��λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    ssicdev_ctrl_srst_status   : 1; /* [12..12] SSIC Device��������λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    ssicphy_srst_status        : 1; /* [13..13] SSIC PHY��λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    pcie_ctrl_srst_status      : 1; /* [14..14] PCIE��������λ��������״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    pcie_phy_srst_status       : 1; /* [15..15] PCIE PHY��λ��������״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    ddrphy_div_srst_status     : 1; /* [16..16] ddrphy ctl clk��Ƶ����λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    reserved_1                 : 1; /* [17..17] ���� */
        unsigned int    hificore_srst_status       : 1; /* [18..18] HIFI DSP CORE��λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    hifi_pd_srst_status        : 1; /* [19..19] HIFI ��DBG�����λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    hifi_dbg_srst_status       : 1; /* [20..20] HIFI DBG��λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    usbotg_bc_srst_status      : 1; /* [21..21] USB_BC��������λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    usbotg_phy_srst_status     : 1; /* [22..22] USBOTG PHY��λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    usbotg_ctrl_srst_status    : 1; /* [23..23] USBOTG ctrl��λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    usbotg_ctrl_vaux_srst_status : 1; /* [24..24] USBOTG VAUX��������λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    usbotg_ctrl_vcc_srst_status : 1; /* [25..25] USBOTG VCC��������λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    usbhsic_ctrl_srst_status   : 1; /* [26..26] USBHSIC��������λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    usbhsic_phy_srst_v         : 1; /* [27..27] USBHSIC PHY��λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    cs_srst_status             : 1; /* [28..28] Coresight��λ����״̬���ơ�0����λ������Ч��1����λ������Ч */
        unsigned int    tsensor_srst_status        : 1; /* [29..29] TSENSOR��λ����״̬���ơ�0����λ������Ч1����λ������Ч */
        unsigned int    reserved_0                 : 2; /* [31..30] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_SRSTSTAT2_T;    /* ��λ����״̬2 */

typedef union
{
    struct
    {
        unsigned int    bbp_crg_srst_en            : 1; /* [0..0] BBPʱ�Ӹ�λģ����λ����ʹ�ܿ��ơ�0 - ��Ӱ��1 - ��λ��Ч */
        unsigned int    bbpcommon_2a_srst_en       : 1; /* [1..1] BBPCOMMON_2A��λ����ʹ�ܿ��ơ�0 - ��Ӱ��1 - ��λ��Ч */
        unsigned int    lbbp_pd_srst_en            : 1; /* [2..2] LTEBBP����������������λ����ʹ�ܿ��ơ�0 - ��Ӱ��1 - ��λ��Ч */
        unsigned int    g1bbp_pd_srst_en           : 1; /* [3..3] G1BBP������������λ����ʹ�ܿ��ơ�0 - ��Ӱ��1 - ��λ��Ч */
        unsigned int    g2bbp_pd_srst_en           : 1; /* [4..4] G2BBP������������λ����ʹ�ܿ��ơ�0 - ��Ӱ��1 - ��λ��Ч */
        unsigned int    twbbp_pd_srst_en           : 1; /* [5..5] TWBBP����������������λ����ʹ�ܿ��ơ�0 - ��Ӱ��1 - ��λ��Ч */
        unsigned int    wbbp_pd_srst_en            : 1; /* [6..6] WBBP����������������λ����ʹ�ܿ��ơ�0 - ��Ӱ��1 - ��λ��Ч */
        unsigned int    irm_pd_srst_en             : 1; /* [7..7] IRM������������λ����ʹ�ܿ��ơ�0 - ��Ӱ��1 - ��λ��Ч */
        unsigned int    bbc_lbbp_pdt_srst_en       : 1; /* [8..8] BBPCOMMON_2A LBBP PDT��λԴ���ơ�0 - ��Ӱ��1 - ��bit��1 */
        unsigned int    bbc_lbbp_pdf_srst_en       : 1; /* [9..9] BBPCOMMON_2A LBBP PDF��λԴ���ơ�0 - ��Ӱ��1 - ��bit��1 */
        unsigned int    bbc_lbbp_tdl_srst_en       : 1; /* [10..10] BBPCOMMON_2A LBBP TDL��λԴ���ơ�0 - ��Ӱ��1 - ��bit��1 */
        unsigned int    bbc_tbbp_245m_srst_en      : 1; /* [11..11] BBPCOMMON_2A TBBP 245MHz�����߼���λԴ���ơ�0 - ��Ӱ��1 - ��bit��1 */
        unsigned int    bbc_twbbp_122m_srst_en     : 1; /* [12..12] BBPCOMMON_2A TWBBP 122MHz�����߼���λԴ���ơ�0 - ��Ӱ��1 - ��bit��1 */
        unsigned int    bbc_g1bbp_104m_srst_en     : 1; /* [13..13] BBPCOMMON_2A G1BBP 104MHz�����߼���λԴ���ơ�0 - ��Ӱ��1 - ��bit��1 */
        unsigned int    bbc_g2bbp_104m_srst_en     : 1; /* [14..14] BBPCOMMON_2A G2BBP 104MHz�����߼���λԴ���ơ�0 - ��Ӱ��1 - ��bit��1 */
        unsigned int    reserved                   : 16; /* [30..15] ���� */
        unsigned int    abb_srst_en                : 1; /* [31..31] ABB��λ����ʹ�ܿ��ơ�0 - ��Ӱ��1 - ��λ��Ч */
    } bits;
    unsigned int    u32;
}HI_CRG_SRSTEN3_T;    /* ��λ����ʹ��3��ABB+BBP�� */

typedef union
{
    struct
    {
        unsigned int    bbp_crg_srst_dis           : 1; /* [0..0] BBPʱ�Ӹ�λģ����λ����رտ��ơ�0 - ��Ӱ��1 - ��λ��Ч�� */
        unsigned int    bbpcommon_2a_pd_srst_dis   : 1; /* [1..1] BBPCOMMON_2A��λ����رտ��ơ�0 - ��Ӱ��1 - ��λ��Ч�� */
        unsigned int    lbbp_pd_srst_dis           : 1; /* [2..2] LTEBBP����������������λ����رտ��ơ�0 - ��Ӱ��1 - ��λ��Ч�� */
        unsigned int    g1bbp_pd_srst_dis          : 1; /* [3..3] G1BBP������������λ����رտ��ơ�0 - ��Ӱ��1 - ��λ��Ч�� */
        unsigned int    g2bbp_pd_srst_dis          : 1; /* [4..4] G2BBP������������λ����رտ��ơ�0 - ��Ӱ��1 - ��λ��Ч�� */
        unsigned int    twbbp_pd_srst_dis          : 1; /* [5..5] TWBBP����������������λ����رտ��ơ�0 - ��Ӱ��1 - ��λ��Ч�� */
        unsigned int    wbbp_pd_srst_dis           : 1; /* [6..6] WBBP����������������λ����رտ��ơ�0 - ��Ӱ��1 - ��λ��Ч�� */
        unsigned int    irm_pd_srst_dis            : 1; /* [7..7] IRM������������λ����رտ��ơ�0 - ��Ӱ��1 - ��λ��Ч�� */
        unsigned int    bbc_lbbp_pdt_srst_dis      : 1; /* [8..8] BBPCOMMON_2A LBBP PDT��λ���ơ�0 - ��Ӱ��1 - ��bit��0 */
        unsigned int    bbc_lbbp_pdf_srst_dis      : 1; /* [9..9] BBPCOMMON_2A LBBP PDF��λ������λ���ơ�0 - ��Ӱ��1 - ��bit��0 */
        unsigned int    bbc_lbbp_tdl_srst_dis      : 1; /* [10..10] BBPCOMMON_2A LBBP TDL��λ������λ���ơ�0 - ��Ӱ��1 - ��bit��0 */
        unsigned int    bbc_tbbp_245m_srst_dis     : 1; /* [11..11] BBPCOMMON_2A TBBP 245MHz�����߼���λ���ơ�0 - ��Ӱ��1 - ��bit��0 */
        unsigned int    bbc_twbbp_122m_srst_dis    : 1; /* [12..12] BBPCOMMON_2A TWBBP 122MHz�����߼���λ���ơ�0 - ��Ӱ��1 - ��bit��0 */
        unsigned int    bbc_g1bbp_104m_srst_dis    : 1; /* [13..13] BBPCOMMON_2A G1BBP 104MHz�����߼���λ���ơ�0 - ��Ӱ��1 - ��bit��0 */
        unsigned int    bbc_g2bbp_104m_srst_dis    : 1; /* [14..14] BBPCOMMON_2A G2BBP 104MHz�����߼���λ���ơ�0 - ��Ӱ��1 - ��bit��0 */
        unsigned int    reserved                   : 16; /* [30..15] ���� */
        unsigned int    abb_srst_dis               : 1; /* [31..31] ABB��λ����رտ��ơ�0 - ��Ӱ��1 - ��λ��Ч */
    } bits;
    unsigned int    u32;
}HI_CRG_SRSTDIS3_T;    /* ��λ����ر�3��ABB+BBP�� */

typedef union
{
    struct
    {
        unsigned int    bbp_crg_srst_stat          : 1; /* [0..0] BBPʱ�Ӹ�λģ����λ����״̬���ơ�0 - ��λ��Ч1 - ��λ��Ч */
        unsigned int    bbpcommon_2a_srst_stat     : 1; /* [1..1] BBPCOMMON_2A��λ����״̬���ơ�0 - ��λ��Ч1 - ��λ��Ч */
        unsigned int    lbbp_pd_srst_stat          : 1; /* [2..2] LTEBBP����������������λ����״̬���ơ�0 - ��λ��Ч1 - ��λ��Ч */
        unsigned int    g1bbp_pd_srst_stat         : 1; /* [3..3] G1BBP������������λ����״̬���ơ�0 - ��λ��Ч1 - ��λ��Ч */
        unsigned int    g2bbp_pd_srst_stat         : 1; /* [4..4] G2BBP������������λ����״̬���ơ�0 - ��λ��Ч1 - ��λ��Ч */
        unsigned int    twbbp_pd_srst_stat         : 1; /* [5..5] TWBBP����������������λ����״̬���ơ�0 - ��λ��Ч1 - ��λ��Ч */
        unsigned int    wbbp_pd_srst_stat          : 1; /* [6..6] WBBP����������������λ����״̬���ơ�0 - ��λ��Ч1 - ��λ��Ч */
        unsigned int    irm_pd_srst_stat           : 1; /* [7..7] IRM������������λ����״̬���ơ�0 - ��λ��Ч1 - ��λ��Ч */
        unsigned int    bbc_lbbp_pdt_srstctrl_stat : 1; /* [8..8] BBPCOMMON_2A LBBP PDT��λ������ơ�0 - ��λ��LTEBBP��ѹ����λ���ƣ�1 - ��λ��BBPCOMMON_2A��λ���ơ� */
        unsigned int    bbc_lbbp_pdf_srstctrl_stat : 1; /* [9..9] BBPCOMMON_2A LBBP PDF��λ������λ���ơ�0 - ��λ��LTEBBP��ѹ����λ���ƣ�1 - ��λ��BBPCOMMON_2A��λ���ơ� */
        unsigned int    bbc_lbbp_tdl_srstctrl_stat : 1; /* [10..10] BBPCOMMON_2A LBBP TDL��λ������λ������ơ�0 - ��λ��LTEBBP��ѹ����λ���ƣ�1 - ��λ��BBPCOMMON_2A��λ���ơ� */
        unsigned int    bbc_tbbp_245m_srstctrl_stat : 1; /* [11..11] BBPCOMMON_2A TBBP 245MHz�����߼���λ������ơ�0 - ��λ��TWEBBP��ѹ����λ���ƣ�1 - ��λ��BBPCOMMON_2A��λ���ơ� */
        unsigned int    bbc_twbbp_122m_srstctrl_stat : 1; /* [12..12] BBPCOMMON_2A TWBBP 122MHz�����߼���λ������ơ�0 - ��λ��TWEBBP��ѹ����λ���ƣ�1 - ��λ��BBPCOMMON_2A��λ���ơ� */
        unsigned int    bbc_g1bbp_104m_srstctrl_stat : 1; /* [13..13] BBPCOMMON_2A G1BBP 104MHz�����߼���λ������ơ�0 - ��λ��G1EBBP��ѹ����λ���ƣ�1 - ��λ��BBPCOMMON_2A��λ���ơ� */
        unsigned int    bbc_g2bbp_104m_srstctrl_stat : 1; /* [14..14] BBPCOMMON_2A G2BBP 104MHz�����߼���λ��λ������ơ�0 - ��λ��G2EBBP��ѹ����λ���ƣ�1 - ��λ��BBPCOMMON_2A��λ���ơ� */
        unsigned int    reserved                   : 16; /* [30..15] ���� */
        unsigned int    abb_srst_status            : 1; /* [31..31] ABB��λ����״̬���ơ�0 - ��λ��Ч1 - ��λ��Ч */
    } bits;
    unsigned int    u32;
}HI_CRG_SRSTSTAT3_T;    /* ��λ����״̬3��ABB+BBP�� */

typedef union
{
    struct
    {
        unsigned int    pcm_bclk_div               : 16; /* [15..0] sio_bclk��Ƶϵ���� */
        unsigned int    pcm_sync_div               : 12; /* [27..16] sio_sync��Ƶϵ���� */
        unsigned int    reserved                   : 4; /* [31..28] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKDIV1_T;    /* ʱ�ӷ�Ƶ����1(SIO PCMʱ�ӷ�Ƶ�� */

typedef union
{
    struct
    {
        unsigned int    appa9_clk_div              : 4; /* [3..0] app A9��Ƶϵ����ֻҪ�����������߼��������ߵ�Ƶ�ʱȣ�������0-15���κ�ֵ��app A9���600MHz����A9_PLL postdivʱ�ӱ��˷�Ƶϵ����Ƶ���Ƶ�ʡ�Ĭ��A9PLL POSTDIV���ʱ��Ƶ��Ϊ600MHz */
        unsigned int    mdma9_clk_div              : 4; /* [7..4] modem A9��Ƶϵ����ֻҪ�����������߼��������ߵ�Ƶ�ʱȣ�������0-15���κ�ֵ��modem A9���600MHz����A9_PLL postdivʱ�ӱ��˷�Ƶϵ����Ƶ���Ƶ�ʡ�Ĭ��A9PLL POSTDIV���ʱ��Ƶ��Ϊ600MHz */
        unsigned int    soc_clk_div                : 4; /* [11..8] ���߷�Ƶϵ����N - N+1��Ƶ��ֻҪ�����A9���������ߵ�Ƶ�ʱȣ�������1-16���κ�ֵ��slow_aclk=a9pll_postdiv/(slow_clk_div+1)�����������150MHz����֧�ֵ�profile��CRG���� */
        unsigned int    fast_clk_div               : 4; /* [15..12] �������߷�Ƶϵ����N - N+1��Ƶ��ֻҪ�����A9���������ߵ�Ƶ�ʱȣ�������1-16���κη�Ƶ��fast_aclk=a9pll_postdiv/(fast_clk_div+1)�����������300MHz��bit24=0,��DDRPHY PLL bypassģʽ��ʱ�������������Ϊż���� */
        unsigned int    reserved_2                 : 8; /* [23..16] ���� */
        unsigned int    ddr_rate_sel               : 1; /* [24..24] DDR���ʡ�0��DDR����<667MHz��1��DDR����=667MHz��ֻ�е�DDR����<667MHzʱ��DDRPHY��2��Ƶʱ�ӲŻ�򿪡�����bit����Ϊ0����fast_clk_div��������������żż����Ƶ�������������� */
        unsigned int    reserved_1                 : 5; /* [29..25] ���� */
        unsigned int    apb_freqmode               : 1; /* [30..30] APB������SlowBus���߷�Ƶ�����á�0 - 1:11 - 2:1 */
        unsigned int    reserved_0                 : 1; /* [31..31] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKDIV2_T;    /* ʱ�ӷ�Ƶ����2(���߷�Ƶ�� */

typedef union
{
    struct
    {
        unsigned int    mmc0_cclk_div              : 5; /* [4..0] MMC0���ӿ�ʱ�ӷ�Ƶϵ����0 - 1��Ƶ��N - N+1��ƵĬ��4��Ƶ��N=3 */
        unsigned int    reserved_3                 : 2; /* [6..5] ���� */
        unsigned int    mmc0_refclk_sel            : 1; /* [7..7] 0 - HIFIPLL��800MHz)1 - PERIPLL_480MHz */
        unsigned int    mmc0_phase_clk_div         : 3; /* [10..8] MMC0����������ʱ�ӷ�Ƶϵ����0 - 1��Ƶ��N - N+1��ƵĬ��2��Ƶ��N=1 */
        unsigned int    reserved_2                 : 1; /* [11..11] ���� */
        unsigned int    mmc1_cclk_div              : 5; /* [16..12] MMC1���ӿ�ʱ�ӷ�Ƶϵ����0 - 1��Ƶ��N - N+1��ƵĬ��2��Ƶ��N=1 */
        unsigned int    reserved_1                 : 2; /* [18..17] ���� */
        unsigned int    mmc1_refclk_sel            : 1; /* [19..19] 0 - HIFIPLL800MHz)1 - PERIPLL480MHz */
        unsigned int    mmc1_phase_clk_div         : 3; /* [22..20] MMC1����������ʱ�ӷ�Ƶϵ����0 - 1��Ƶ��N - N+1��ƵĬ��2��Ƶ��N=1 */
        unsigned int    reserved_0                 : 1; /* [23..23] ���� */
        unsigned int    hpm_clk_div                : 4; /* [27..24] HPM����ʱ�ӷ�Ƶϵ����0 - 1��Ƶ��N - N��Ƶ�� */
        unsigned int    cipher_clk_div             : 4; /* [31..28] cipher����ʱ�ӷ�Ƶϵ������Ƶ��������ο�ʱ��Ϊ480MHz��N��N��Ƶ����Ĭ������Ϊ5��Ƶ��cipher_clk=960MHz/5=96MHz. */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKDIV3_T;    /* ʱ�ӷ�Ƶ����3(MMC0/1) */

typedef union
{
    struct
    {
        unsigned int    hifi_clk_div_num           : 4; /* [3..0] HIFI COREʱ�ӷ�Ƶϵ����HIFI CORE��߹���Ƶ��Ϊ300MHz��0 - 1��ƵN - N+1��Ƶ */
        unsigned int    hifi_freqmode              : 2; /* [5..4] HIFI CORE�����߷�Ƶ�ȡ���߹���Ƶ��Ϊ150MHz0 - 1:11 - 2:1(default)2 - 3:13 - 4:1 */
        unsigned int    hifi_refclk_sel            : 2; /* [7..6] HIFI����ο�ʱ��ѡ��?0 - DSPPLL_FOUTPOST(300MHz)?1 = PERIPLL_FOUTPOST(960MHz��������Ҫ�������������ʱ���ɽ��ο�ʱ���л���PERIPLL�������ͬʱ�ر�HIFIPLL�Ӷ���ʡ���ġ��л����̣�HIFIPLL -�� PERIPLL1. ����hifi_clk_div_num�����ʵķ�Ƶϵ��2. ����hifi_refclk_sel�л�������������ο�ʱ��3. �ر�HIFIPLL�л����̣�PERIPLL -�� HIFIPLL1. ���HIFIPLL����PD״̬��ʹ��PLL2. ����hifi_clk_div_num�����ʵķ�Ƶϵ��3. ����hifi_refclk_sel�л�������������ο�ʱ�� */
        unsigned int    reserved                   : 24; /* [31..8] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKDIV4_T;    /* ʱ�ӷ�Ƶ����4(HIFIʱ�ӷ�Ƶ) */

typedef union
{
    struct
    {
        unsigned int    bbe_clk_div_num            : 3; /* [2..0] BBE16 COREʱ�ӷ�Ƶϵ������߹���Ƶ��Ϊ3000MHz��0 - 1��ƵN - N+1��Ƶ */
        unsigned int    reserved_2                 : 1; /* [3..3] ���� */
        unsigned int    bbe_freqmode               : 2; /* [5..4] DSP CORE�����߷�Ƶ�ȡ����ߵ���߹���Ƶ��Ϊ150MHz.0 - 1:11 - 2:1(default)10 -3:111- 4:1 */
        unsigned int    bbe_refclk_sel             : 2; /* [7..6] DSP����ο�ʱ��ѡ��?0 - DSPPLL_FOUTPOST(420MHz)?1 - PERIPLL_FOUTPOST(960MHz��������Ҫ�������������ʱ���ɽ�BBE�Ĳο�ʱ���л���PERIPLL��������л����̣�1. ����bbe_clk_div_num�����ʵķ�Ƶϵ��2. ����bbe_refclk_sel�л�������������ο�ʱ�� */
        unsigned int    sci0_clk_div_num           : 3; /* [10..8] SCI0����ʱ�ӷ�Ƶϵ����SCI�����Ƶ��Ϊ60MHzʱ��ԴPERIPLL_FOUT4=120MHzN - N��Ƶ��֧��2~7��Ƶ�� */
        unsigned int    reserved_1                 : 1; /* [11..11] ���� */
        unsigned int    sci1_clk_div_num           : 3; /* [14..12] SCI1����ʱ�ӷ�Ƶϵ����SCI�����Ƶ��Ϊ60MHzʱ��ԴPERIPLL_FOUT4=120MHzN - N��Ƶ��ֻ֧��2~7��Ƶ�� */
        unsigned int    reserved_0                 : 17; /* [31..15] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKDIV5_T;    /* ʱ�ӷ�Ƶ����5(BBE/SCIʱ�ӷ�Ƶ) */

typedef union
{
    struct
    {
        unsigned int    mmc0_drv_sel               : 7; /* [6..0] mmc0_drv_clk������ơ�Bit[6:5] - delay chain select00 - no delay chain01 - 1st delay10 - 2nd delay11 - 3rd delaybit[4:0] - phase shift step select.MMC0ֻ֧��8������steps��bit[4��3]����̶�����Ϊ0��drvʱ��=cclk ����45*bit[2:0]�� */
        unsigned int    mmc0_clk_bypass            : 1; /* [7..7] mmc0_drv_clk/mmc_sampe_clkʱ��Դѡ���źš�1��mmc0_drv_clkʱ��Ϊmmc_cclk����ʱ�ӣ�sample����PAD����ʱ�ӡ�0��mmc0_drv_clk��mmc_sample_clkΪmmc0_clk�����ʱ�� */
        unsigned int    mmc0_sample_sel            : 7; /* [14..8] mmc0_sample_clk������ơ�Bit[14:13] - delay chain select00 - no delay chain01 - 1st delay10 - 2nd delay11 - 3rd delaybit[12:8] - phase shift step select.MMC0ֻ֧��8������steps��bit[12:11]����̶�����Ϊ0��Sampleʱ��=cclk ����45*bit[10:8]�ȴ�ʱphase_clk��cclk��2��Ƶ */
        unsigned int    mmc0_sample_ctrl           : 1; /* [15..15] MMC0����sample�����ݵ�ʱ��Դѡ���źš�0������mmc_cclk_in������ʱ�ӣ�1������mmc_cclk_in�ķ���ʱ�ӡ� */
        unsigned int    mmc1_drv_sel               : 7; /* [22..16] mmc1_drv_clk������ơ�Bit[22:21] - delay chain select00 - no delay chain01 - 1st delay10 - 2nd delay11 - 3rd delaybit[20:16] - phase shift step select.MMC0ֻ֧��16������steps��bit[20]����̶�����Ϊ0��drvʱ��=cclk ����45*bit[19:16]��. */
        unsigned int    mmc1_clk_bypass            : 1; /* [23..23] mmc_drv_clk/mmc_sampe_clkʱ��Դѡ���źš�1��mmc_drv_clkʱ��Ϊmmc_cclk����ʱ�ӣ�sample����PAD����ʱ�ӡ�0��mmc_drv_clk��mmc_sample_clkΪmmc_clk�����ʱ�� */
        unsigned int    mmc1_sample_sel            : 7; /* [30..24] mmc1_sample_clk������ơ�Bit[30:29] - delay chain select00 - no delay chain01 - frist delay10 - 2nd delay11 - third delaybit[28:24] - phase shift step select,MC1ֻ֧��16������steps��bit[28]����̶�����Ϊ0��Sampleʱ��=cclk ����22.5*bit[10:8]��.��ʱphase_clk��cclk��4��Ƶ�� */
        unsigned int    mmc1_sample_ctrl           : 1; /* [31..31] MMC1����sample�����ݵ�ʱ��Դѡ���źš�0������mmc_cclk_in������ʱ�ӣ�1������mmc_cclk_in�ķ���ʱ�ӡ� */
    } bits;
    unsigned int    u32;
}HI_CRG_MMC_CTRL_T;    /* MMC0/1������� */

typedef union
{
    struct
    {
        unsigned int    pll_lock_ctrl              : 16; /* [15..0] �߼��Զ�ʹ��PLL���ʱ�ӵȴ�ʱ��������(tcxo_clk��������������pll_lock_mode=0ʱ�����塣 */
        unsigned int    pll_clk_dis_cfg            : 15; /* [30..16] �����ʽpll���ʱ��ʱ�ܿ���(pll_lock_mode=1����[16] - dsppll foutpost clk[17] - hifipll_foutpost_clk[18] - ������[19] - peripll_foutpost_clk[20] - peripll_fout1_clk[21] - peripll_fout3_clk[22] - peripll_fout4_clk[23] - bbppll_foutpost_clk[24] - hifipll_fout1_clk[25] - hifipll_fout3_clk[26] - hifipll_fout4_clk[27] - peripll_fout2_clk[28] - gmacpll_foutpost_clk[29] - gmacpll_fout2_clk[30] - bbppll_fout2_clkPLLĬ��ΪPD��BYPASSģʽ����ˣ�ֻ��*_FOUTPOSTʱ�������������ʱ��Ϊ0���������� - ��ʱ��1. �ر�pll_clk_en_cfg��Ӧbit2. ����PLL���ȴ�PLL�ȶ���lockָʾ�ź���Ч����3. ����pll_clk_en_cfg��Ӧbit����ʱ���������� - �ر�ʱ��1. �ر�pll_clk_en_cfg��Ӧbit�ر�ʱ�ӣ�2. �����ø����Ӧbits�ر�ʱ�ӣ�������PLL�µ���� */
        unsigned int    pll_lock_mode              : 1; /* [31..31] pll�������Ʒ�ʽ��0��pll�������Զ���ʱ�ӣ�1��pll��������Ҫ���ƴ�ʱ�ӣ� */
    } bits;
    unsigned int    u32;
}HI_CRG_PLLLOCK_CTRL_T;    /* pll�������ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    soc_tcxo_refclk_sel        : 1; /* [0..0] SOC TCXOʱ��ѡ�񡣶�̬�л����л�ʱ���뱣֤����ʱ�ӡ�0 - TCXO0 CLK1 - TCXO1 CLK�л���Ҫ�ڷ�Normalģʽ�����,������ܻᵼ��PLLʧ��������оƬ�����쳣�� */
        unsigned int    pmu_tcxo_clk_sel           : 1; /* [1..1] PMU TCXOʱ��ѡ�񡣾�̬�л�0 - TCXO0 CLK1 - TCXO1 CLK */
        unsigned int    gps_tcxo_clk_sel           : 1; /* [2..2] GPS TCXOʱ��ѡ�񡣾�̬�л�0 - TCXO0 CLK1 - TCXO1 CLK */
        unsigned int    wifi_tcxo_clk_sel          : 1; /* [3..3] WIFI TCXOʱ��ѡ�񡣾�̬�л�0 - TCXO0 CLK1 - TCXO1 CLK */
        unsigned int    sleep_clk_sel              : 1; /* [4..4] sleepʱ��ѡ�񡣾�̬�л�����ʹ��sleepʱ��֮ǰ�����л���0 - PAD sleep_clk1 - TCXO��Ƶ��õ���ʱ�� */
        unsigned int    uart0_clk_sel              : 1; /* [5..5] UART0����ʱ��ѡ�񡣶�̬�л����л�ʱ���뱣֤����ʱ�ӡ�0 - 48MHz1 - 32.768KHz�л����̣��л�ʱ��48MHz��32KHzʱ�ӱ��붼��ʱ������������л����ɹ���1.ȷ�ϸ�Ƶʱ�Ӵ򿪣���Ҫ����PERIPLL��PLLLOCK_CTRL�Ĵ�����2. ����ʱ���л��� */
        unsigned int    sio_clk_sel                : 1; /* [6..6] SIO�ⲿ�ӿ�ʱ�Ӽ���ѡ��0 - ѡ��ͬ��ʱ�ӣ�Ĭ�����ã�1 - ѡ����ʱ�� */
        unsigned int    cs_clk_sel                 : 1; /* [7..7] coresight��ϵͳʱ��Դѡ��0 - ѡ��19.2MHz1 - ѡ��PERIPLL���ʱ���л����̣�1.ȷ�ϸ�Ƶʱ�Ӵ򿪣���Ҫ����PERIPLL��PLLLOCK_CTRL�Ĵ�����2. ����ʱ���л��� */
        unsigned int    a9pll_clk_sel              : 2; /* [9..8] A9��Ƶʱ��Դѡ��01 - A9PLL���ʱ�ӣ�10 - PERIPLL���ʱ�ӣ��������ò�֧�� */
        unsigned int    reserved                   : 2; /* [11..10] ���� */
        unsigned int    pwm0_clk_sel               : 1; /* [12..12] PWM0����ʱ��ѡ����ơ���̬�л���0 - 19.2MHz1 - 32KHz */
        unsigned int    pwm1_clk_sel               : 1; /* [13..13] PWM1����ʱ��ѡ����ơ���̬�л���0 - 19.2MHz1 - 32KHz */
        unsigned int    tcssi0_clk_sel             : 1; /* [14..14] TCSSI0ʱ��ѡ�񡣾�̬�л���0 - TCXO0 CLK1 - TCXO1 CLK */
        unsigned int    tcssi1_clk_sel             : 1; /* [15..15] TCSSI1ʱ��ѡ�񡣾�̬�л���0 - TCXO0 CLK1 - TCXO1 CLK */
        unsigned int    ushsic_utmi_clk_dis        : 1; /* [16..16] UTMIʱ��ʹ�ܿ��ơ���bit��HSIC�͹���ʱʹ�ã���bit17һ��ʹ�á�0 - �򿪿�������UTMIʱ�ӣ�1 - �رտ�������UTMIʱ�ӡ���UTMIʱ���л�ʱ������ͨ��bit16�ر�ʱ�ӣ��л���ɺ��ʱ�ӡ� */
        unsigned int    usbhsic_utmi_clk_sel       : 1; /* [17..17] HSIC������UTMI�ӿ�ʱ��ѡ��0 - ѡ��PHY UTMIʱ�ӣ�1 - ѡ��32.768KHzʱ�� */
        unsigned int    hpm_refclk_sel             : 2; /* [19..18] HPM����ο�ʱ��ѡ��00 - A9PLL01 - DSPPLL10 - DSPPLL11 - ABB���245.76MHzʱ�� */
        unsigned int    a9_wd_srst_en              : 1; /* [20..20] A9 WDT��λ���ơ�0 - A9 WDT��λ��Ч��1 - A9 WDT��λ��Ч�� */
        unsigned int    gmac_rx_clk_sel            : 1; /* [21..21] GMAC���շ���Ľ���ʱ��ѡ��0 - ����ʱ��1 - ����ʱ�� */
        unsigned int    gmac_tx_clk_sel            : 1; /* [22..22] GMAC���ͷ���ķ���ʱ��ѡ��0 - ����ʱ��1 - ����ʱ�� */
        unsigned int    gmac_rtx_clk_sel           : 1; /* [23..23] RGMII�ӿڷ�����·ʱ��ѡ��0 - ����ʱ��1 - ����ʱ�� */
        unsigned int    usbphy_refclk_sel          : 2; /* [25..24] USBPHY�ο�ʱ��ѡ��0��- USB_TCXO_CLK1��- TCXO0_CLK10 - TCXO0 CLK11 - TCXO1 CLK */
        unsigned int    peripll_refclk_sel         : 2; /* [27..26] PERIPLL�ο�ʱ��ѡ��0��- USB_TCXO_CLK1��- TCXO0_CLK10 - TCXO0 CLK11 - TCXO1 CLK */
        unsigned int    cs_refclk_sel              : 1; /* [28..28] CS_AT_CLK�ο�ʱ��ѡ��0 - peripll_fout3_clk(160MHz)1 - peripll_fout4_clk(120MHz) */
        unsigned int    mmc1_refclk_sel            : 1; /* [29..29] MMC1�ο�ʱ��ѡ��0 - PERIPLL480MHz1 - DSPPLL300MHz */
        unsigned int    sio_refclk_sel             : 1; /* [30..30] SIOmasterģʽ�ο�ʱ��ѡ��0 - ѡ��245.76M��Ĭ�����ã�1 - ѡ��TCXOʱ�� */
        unsigned int    mmc0_refclk_sel            : 1; /* [31..31] MMC0�ο�ʱ��ѡ��0 - PERIPLL480MHz1 - DSPPLL300MHz */
    } bits;
    unsigned int    u32;
}HI_CRG_CLK_SEL1_T;    /* ʱ��Դѡ�����1 */

typedef union
{
    struct
    {
        unsigned int    timer0_6_clk_sel           : 7; /* [6..0] TIMER0-6����ʱ��Դѡ�񣬾�̬�л���1 - ѡ��19.2MHzʱ�ӣ�0 - ѡ��32KHzʱ��Note���л�ʱ��ʱ������ȹرն�Ӧ��ʱ�������Ȼ���л�ʱ�ӣ��л���Ϻ��ʱ�� */
        unsigned int    reserved_3                 : 1; /* [7..7] ���� */
        unsigned int    timer8_14_clk_sel          : 7; /* [14..8] TIMER8_14����ʱ��Դѡ�񣬾�̬�л���1 - ѡ��19.2MHzʱ�ӣ�0 - ѡ��32KHzʱ�� */
        unsigned int    reserved_2                 : 1; /* [15..15] ���� */
        unsigned int    timer16_22_clk_sel         : 7; /* [22..16] TIMER16_22����ʱ��Դѡ�񣬾�̬�л���1 - ѡ��19.2MHzʱ�ӣ�0 - ѡ��32KHzʱ�� */
        unsigned int    reserved_1                 : 1; /* [23..23] ���� */
        unsigned int    timer7_clk_sel             : 2; /* [25..24] TIMER7����ʱ��Դѡ�񣬾�̬�л���1�� - PERIPLL FOUT4/2(60MHz)00 - ѡ��32KHzʱ��01 - ѡ��19.2MHzʱ�ӣ� */
        unsigned int    timer15_clk_sel            : 2; /* [27..26] TIMER15����ʱ��Դѡ�񣬾�̬�л���1�� - PERIPLL FOUT4/2(60MHz)00 - ѡ��32KHzʱ��01 - ѡ��19.2MHzʱ�ӣ� */
        unsigned int    timer23_clk_sel            : 2; /* [29..28] TIMER23����ʱ��Դѡ�񣬾�̬�л���1��- PERIPLL FOUT3/N(160MHz)00 - ѡ��32KHzʱ��01 - ѡ��19.2MHzʱ�ӣ� */
        unsigned int    reserved_0                 : 2; /* [31..30] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLK_SEL2_T;    /* ʱ��Դѡ�����2(TIMER) */

typedef union
{
    struct
    {
        unsigned int    abb_tcxo_clk_sel           : 1; /* [0..0] ABB TCXOʱ��Դѡ��0 - TCXO0ʱ�ӣ�1 - TCXO1ʱ�� */
        unsigned int    bbppll_refclk_sel          : 1; /* [1..1] BBPPLL�ο�ʱ��Դѡ�񡣾�̬�л���0 - ABBͨ��0 TCXOʱ�ӣ�1 - ABBͨ��1 TCXOʱ�� */
        unsigned int    bbp_tcxo_clk_sel           : 1; /* [2..2] BBP 19.2MHzʱ��Դѡ�񡣾�̬�л���0 - ABBͨ��0 TCXOʱ�ӣ�1 - ABBͨ��1 TCXOʱ�� */
        unsigned int    ch0_tcxo_clk_sel           : 1; /* [3..3] ͨ��0 19.2MHzʱ��ѡ�񡣾�̬�л���0 - ABBͨ��0 TCXOʱ�ӣ�1 - ABBͨ��1 TCXOʱ�� */
        unsigned int    ch1_tcxo_clk_sel           : 1; /* [4..4] ͨ��1 19.2MHzʱ��ѡ�񡣾�̬�л���0 - ABBͨ��0 TCXOʱ�ӣ�1 - ABBͨ��1 TCXOʱ�� */
        unsigned int    g1bbp_104m_clk_sel         : 1; /* [5..5] G1BBPͨ��ѡ�񡣾�̬�л���0 - ѡ��ͨ��0��1 - ѡ��ͨ��1 */
        unsigned int    g2bbp_104m_clk_sel         : 1; /* [6..6] G2BBPͨ��ѡ�񡣾�̬�л���0 - ѡ��ͨ��0��1 - ѡ��ͨ��1 */
        unsigned int    tdl_clk_sel                : 1; /* [7..7] TDLʱ��Դѡ��0 - 122MHz/245MHz��1 - 245MHz/491MHz */
        unsigned int    lbbp_vdl_clk_sel           : 1; /* [8..8] VDLʱ��Դѡ��0 - 122MHz��1 - 245MHz */
        unsigned int    lbbp_pdf_clk_sel           : 1; /* [9..9] LTEBBP Ƶ��ʱ��Դѡ��0 - 122MHz��1 - 245MHz */
        unsigned int    reserved                   : 22; /* [31..10] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLK_SEL3_T;    /* ʱ��Դѡ�����3��BBP�� */

typedef union
{
    struct
    {
        unsigned int    dfs_frac                   : 24; /* [23..0] Ƶ�ʺϳ�����ƵС�����֡� */
        unsigned int    reserved                   : 8; /* [31..24] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS1_CTRL1_T;    /* A9 DFS����1��1.2GHz) */

typedef union
{
    struct
    {
        unsigned int    dfs_intprog                : 12; /* [11..0] Ƶ�ʺϳ�����Ƶ�������֡� */
        unsigned int    dfs_refdiv                 : 6; /* [17..12] Ƶ�ʺϳ�������ο�ʱ�ӷ�Ƶϵ���� */
        unsigned int    reserved_2                 : 2; /* [19..18] ���� */
        unsigned int    dfs_postdiv2               : 3; /* [22..20] VCO������Ƶϵ���� */
        unsigned int    reserved_1                 : 1; /* [23..23] ���� */
        unsigned int    dfs_postdiv1               : 3; /* [26..24] VCOһ����Ƶϵ���� */
        unsigned int    reserved_0                 : 5; /* [31..27] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS1_CTRL2_T;    /* A9 DFS����2 */

typedef union
{
    struct
    {
        unsigned int    pd                         : 1; /* [0..0] DFS����ģʽ��0����������ģʽ��1��Power Downģʽ�� */
        unsigned int    reserved_1                 : 1; /* [1..1] ������ */
        unsigned int    dsmpd                      : 1; /* [2..2] ������Ƶ����ģʽ��0��ʹ�ܷ�����Ƶ��1����ֹ������Ƶ�� */
        unsigned int    phase4_pd                  : 1; /* [3..3] 4����λʱ�����ʹ�ܡ�0��ʹ�������1����ֹ����� */
        unsigned int    postdivpd                  : 1; /* [4..4] POSTDIVʱ�����ʹ�ܡ�0��ʹ�������1����ֹ����� */
        unsigned int    vcopd                      : 1; /* [5..5] VCO���ʹ�ܡ�0��ʹ��VCO�����1����ֹVCO����� */
        unsigned int    dacpd                      : 1; /* [6..6] Cancellation DAC power down����������ģʽ����λӦ��һֱ����Ϊ1'b0 */
        unsigned int    bypass                     : 1; /* [7..7] DFS��·���ơ�0����������fOUT=fOUT��1����·fOUT=fREF�� */
        unsigned int    pll_ctrl                   : 1; /* [8..8] ARM PLL����ѡ��0�����߼��Զ�����ARM PLL��PD״̬��1�����������ARM PLL����״̬�����pdʹ�� */
        unsigned int    reserved_0                 : 22; /* [30..9] ������ */
        unsigned int    lock                       : 1; /* [31..31] DFS����ָʾ������Ч��0��ʧ����1�������� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS1_CTRL3_T;    /* A9 DFS����3 */

typedef union
{
    struct
    {
        unsigned int    dfs_frac                   : 24; /* [23..0] Ƶ�ʺϳ�����ƵС�����֡� */
        unsigned int    reserved                   : 8; /* [31..24] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS2_CTRL1_T;    /* DSP DFS����1(1200MHz) */

typedef union
{
    struct
    {
        unsigned int    dfs_intprog                : 12; /* [11..0] Ƶ�ʺϳ�����Ƶ�������֡� */
        unsigned int    dfs_refdiv                 : 6; /* [17..12] Ƶ�ʺϳ�������ο�ʱ�ӷ�Ƶϵ���� */
        unsigned int    reserved_2                 : 2; /* [19..18] ���� */
        unsigned int    dfs_postdiv2               : 3; /* [22..20] VCO������Ƶϵ���� */
        unsigned int    reserved_1                 : 1; /* [23..23] ���� */
        unsigned int    dfs_postdiv1               : 3; /* [26..24] VCOһ����Ƶϵ���� */
        unsigned int    reserved_0                 : 5; /* [31..27] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS2_CTRL2_T;    /* DSP DFS����2 */

typedef union
{
    struct
    {
        unsigned int    pd                         : 1; /* [0..0] DFS����ģʽ��0����������ģʽ��1��Power Downģʽ�� */
        unsigned int    reserved_1                 : 1; /* [1..1] ������ */
        unsigned int    dsmpd                      : 1; /* [2..2] ������Ƶ����ģʽ��0��ʹ�ܷ�����Ƶ��1����ֹ������Ƶ�� */
        unsigned int    phase4_pd                  : 1; /* [3..3] 4����λʱ�����ʹ�ܡ�0��ʹ�������1����ֹ����� */
        unsigned int    postdivpd                  : 1; /* [4..4] POSTDIVʱ�����ʹ�ܡ�0��ʹ�������1����ֹ����� */
        unsigned int    vcopd                      : 1; /* [5..5] VCO���ʹ�ܡ�0��ʹ��VCO�����1����ֹVCO����� */
        unsigned int    dacpd                      : 1; /* [6..6] Cancellation DAC power down����������ģʽ����λӦ��һֱ����Ϊ1'b0 */
        unsigned int    bypass                     : 1; /* [7..7] DFS��·���ơ�0����������fOUT=fOUT��1����·fOUT=fREF�� */
        unsigned int    reserved_0                 : 23; /* [30..8] ������ */
        unsigned int    lock                       : 1; /* [31..31] DFS����ָʾ������Ч��0��ʧ����1�������� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS2_CTRL3_T;    /* DSP DFS����3 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS3_CTRL1_T;    /* HIFI DFS����1��1.6GHz) */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS3_CTRL2_T;    /* HIFI DFS����2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] DFS����ָʾ������Ч��0��ʧ����1�������� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS3_CTRL3_T;    /* HIFI DFS����3 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS4_CTRL1_T;    /* BBP DFS����1(491.52MHz) */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS4_CTRL2_T;    /* BBP DFS����2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] DFS����ָʾ������Ч��0��ʧ����1�������� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS4_CTRL3_T;    /* BBP DFS����3 */

typedef union
{
    struct
    {
        unsigned int    dfs_frac                   : 24; /* [23..0] Ƶ�ʺϳ�����ƵС�����֡� */
        unsigned int    reserved                   : 8; /* [31..24] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS5_CTRL1_T;    /* PERI DFS����1(960MHz) */

typedef union
{
    struct
    {
        unsigned int    dfs_intprog                : 12; /* [11..0] Ƶ�ʺϳ�����Ƶ�������֡� */
        unsigned int    dfs_refdiv                 : 6; /* [17..12] Ƶ�ʺϳ�������ο�ʱ�ӷ�Ƶϵ���� */
        unsigned int    reserved_2                 : 2; /* [19..18] ���� */
        unsigned int    dfs_postdiv2               : 3; /* [22..20] VCO������Ƶϵ���� */
        unsigned int    reserved_1                 : 1; /* [23..23] ���� */
        unsigned int    dfs_postdiv1               : 3; /* [26..24] VCOһ����Ƶϵ���� */
        unsigned int    reserved_0                 : 5; /* [31..27] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS5_CTRL2_T;    /* PERI DFS����2 */

typedef union
{
    struct
    {
        unsigned int    pd                         : 1; /* [0..0] DFS����ģʽ��0����������ģʽ��1��Power Downģʽ�� */
        unsigned int    reserved_1                 : 1; /* [1..1] ������ */
        unsigned int    dsmpd                      : 1; /* [2..2] ������Ƶ����ģʽ��0��ʹ�ܷ�����Ƶ��1����ֹ������Ƶ�� */
        unsigned int    phase4_pd                  : 1; /* [3..3] 4����λʱ�����ʹ�ܡ�0��ʹ�������1����ֹ����� */
        unsigned int    postdivpd                  : 1; /* [4..4] POSTDIVʱ�����ʹ�ܡ�0��ʹ�������1����ֹ����� */
        unsigned int    vcopd                      : 1; /* [5..5] VCO���ʹ�ܡ�0��ʹ��VCO�����1����ֹVCO����� */
        unsigned int    dacpd                      : 1; /* [6..6] Cancellation DAC power down����������ģʽ����λӦ��һֱ����Ϊ1'b0 */
        unsigned int    bypass                     : 1; /* [7..7] DFS��·���ơ�0����������fOUT=fOUT��1����·fOUT=fREF�� */
        unsigned int    pll_ctrl                   : 1; /* [8..8] PLL����ѡ��0�����߼��Զ�����PLL��PD״̬��1�����������PLL����״̬�����pdʹ�� */
        unsigned int    reserved_0                 : 22; /* [30..9] ������ */
        unsigned int    lock                       : 1; /* [31..31] DFS����ָʾ������Ч��0��ʧ����1�������� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS5_CTRL3_T;    /* PERI DFS����3 */

typedef union
{
    struct
    {
        unsigned int    dfs_frac                   : 24; /* [23..0] Ƶ�ʺϳ�����ƵС�����֡� */
        unsigned int    reserved                   : 8; /* [31..24] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS6_CTRL1_T;    /* PERI USB DFS����1(500MHz) */

typedef union
{
    struct
    {
        unsigned int    dfs_intprog                : 12; /* [11..0] Ƶ�ʺϳ�����Ƶ�������֡� */
        unsigned int    dfs_refdiv                 : 6; /* [17..12] Ƶ�ʺϳ�������ο�ʱ�ӷ�Ƶϵ���� */
        unsigned int    reserved_2                 : 2; /* [19..18] ���� */
        unsigned int    dfs_postdiv2               : 3; /* [22..20] VCO������Ƶϵ���� */
        unsigned int    reserved_1                 : 1; /* [23..23] ���� */
        unsigned int    dfs_postdiv1               : 3; /* [26..24] VCOһ����Ƶϵ���� */
        unsigned int    reserved_0                 : 5; /* [31..27] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS6_CTRL2_T;    /* PERI USB DFS����2 */

typedef union
{
    struct
    {
        unsigned int    pd                         : 1; /* [0..0] DFS����ģʽ��0����������ģʽ��1��Power Downģʽ�� */
        unsigned int    reserved_1                 : 1; /* [1..1] ������ */
        unsigned int    dsmpd                      : 1; /* [2..2] ������Ƶ����ģʽ��0��ʹ�ܷ�����Ƶ��1����ֹ������Ƶ�� */
        unsigned int    phase4_pd                  : 1; /* [3..3] 4����λʱ�����ʹ�ܡ�0��ʹ�������1����ֹ����� */
        unsigned int    postdivpd                  : 1; /* [4..4] POSTDIVʱ�����ʹ�ܡ�0��ʹ�������1����ֹ����� */
        unsigned int    vcopd                      : 1; /* [5..5] VCO���ʹ�ܡ�0��ʹ��VCO�����1����ֹVCO����� */
        unsigned int    dacpd                      : 1; /* [6..6] Cancellation DAC power down����������ģʽ����λӦ��һֱ����Ϊ1'b0 */
        unsigned int    bypass                     : 1; /* [7..7] DFS��·���ơ�0����������fOUT=fOUT��1����·fOUT=fREF�� */
        unsigned int    pll_ctrl                   : 1; /* [8..8] PLL����ѡ��0�����߼��Զ�����PLL��PD״̬��1�����������PLL����״̬�����pdʹ�� */
        unsigned int    reserved_0                 : 22; /* [30..9] ������ */
        unsigned int    lock                       : 1; /* [31..31] DFS����ָʾ������Ч��0��ʧ����1�������� */
    } bits;
    unsigned int    u32;
}HI_CRG_DFS6_CTRL3_T;    /* PERI USB DFS����3 */

typedef union
{
    struct
    {
        unsigned int    uart0_clksw_stat           : 2; /* [1..0] UART0ʱ���л�״̬��                           00��ʱ��δ�л����01: ���48MHzʱ��10: ���32.768KHzXʱ�� 11�������� */
        unsigned int    socpll_refclksw_stat       : 2; /* [3..2] PLL����ο�ʱ���л�״̬��00��ʱ��δ�л���ɣ�˲��״̬��01��ѡ��TCXO0ʱ�ӣ�10: ѡ��TCXO1ʱ�ӡ�11�������� */
        unsigned int    dsp_ref_clksw_stat         : 2; /* [5..4] DSP����ο�ʱ���л�״̬��00��ʱ��δ�л���ɣ�˲��״̬��01��ѡ��DSPPLL_FOUTPOSTʱ�ӣ�10: ѡ��PERIPLL_FOUTPOSTʱ�ӡ�11�������� */
        unsigned int    hifi_ref_clksw_stat        : 2; /* [7..6] HIFI����ο�ʱ���л�״̬��00��ʱ��δ�л���ɣ�˲��״̬��01��ѡ��HIFIPLL_FOUTPOSTʱ�ӣ�10: ѡ��PERIPLL_FOUTPOSTʱ�ӡ�11�������� */
        unsigned int    pwm0_clksw_stat            : 2; /* [9..8] PWM0����ο�ʱ���л�״̬��00��ʱ��δ�л���ɣ�˲��״̬��01��ѡ��TCXOʱ�ӣ�10: ѡ��32.768KHzʱ�ӡ�11�������� */
        unsigned int    pwm1_clksw_stat            : 2; /* [11..10] PWM1����ο�ʱ���л�״̬��00��ʱ��δ�л���ɣ�˲��״̬��01��ѡ��TCXOʱ�ӣ�10: ѡ��32.768KHzʱ�ӡ�11�������� */
        unsigned int    ssic_pa_ref_clksw_stat     : 2; /* [13..12] SSIC������ssic_pa_clk����ο�ʱ���л�״̬��00��ʱ��δ�л���ɣ�˲��״̬��01��ѡ��HIFIPLL_FOUT3ʱ�ӣ���ʱHIFIPLL_POSTDIV=750MHz����10: ѡ��DSPPLL_FOUTPOSTʱ�ӡ�11�������� */
        unsigned int    a9_pll_clksw_stat          : 3; /* [16..14] A9 ��Ƶ����ο�ʱ���л�״̬��00��ʱ��δ�л���ɣ�˲��״̬��01��ѡ��A9PLL_FOUTPOSTʱ�ӣ�10: ѡ��PERIPLL_FOUT1ʱ��(480MHz)��11�������� */
        unsigned int    reserved                   : 15; /* [31..17] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKSW_STAT1_T;    /* ʱ���л�״̬1 */

typedef union
{
    struct
    {
        unsigned int    cm3_clk_div                : 4; /* [3..0] HPM����ʱ�ӷ�Ƶϵ����N -  2~15N - N��Ƶ��Ĭ��2��Ƶ��ʱ��Դperipll_fout2 240MHz�� */
        unsigned int    reserved                   : 28; /* [31..4] ���� */
    } bits;
    unsigned int    u32;
}HI_CRG_CLKDIV6_T;    /* ʱ�ӷ�Ƶ����6��CM3ʱ�ӷ�Ƶ�� */


/********************************************************************************/
/*    syscrg ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_crg_clken1_mst_aclk_en,mst_aclk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_dsp_aclk_en,dsp_aclk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_soc_hclk_en,soc_hclk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_amon_cpufast_clk_en,amon_cpufast_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_amon_soc_clk_en,amon_soc_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_tsensor_clk_en,tsensor_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_reserved_2,reserved_2,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_ipf_clk_en,ipf_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_reserved_1,reserved_1,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_edmac_ch4_clk_en,edmac_ch4_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_socp_clk_en,socp_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_mipi_clk_en,mipi_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_pmussi0_clk_en,pmussi0_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_pmussi1_clk_en,pmussi1_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_dw_ssi0_clk_en,dw_ssi0_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_efuse_clk_en,efuse_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_nandc_clk_en,nandc_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_hs_uart_clk_en,hs_uart_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_emi_clk_en,emi_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_edmac_clk_en,edmac_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_bootrom_clk_en,bootrom_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_pwm1_clk_en,pwm1_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_pwm0_clk_en,pwm0_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_dt_clk_en,dt_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_ipcm_clk_en,ipcm_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_dw_ssi1_clk_en,dw_ssi1_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_i2c1_clk_en,i2c1_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_gpio1_clk_en,gpio1_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_i2c0_clk_en,i2c0_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_gpio3_clk_en,gpio3_clk_en,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clken1_reserved_0,reserved_0,HI_CRG_CLKEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_mst_aclk_dis,mst_aclk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_dsp_aclk_dis,dsp_aclk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_soc_hclk_dis,soc_hclk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_amon_cpufast_clk_dis,amon_cpufast_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_amon_soc_clk_dis,amon_soc_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_tsensor_clk_dis,tsensor_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_reserved_2,reserved_2,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_ipf_clk_dis,ipf_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_reserved_1,reserved_1,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_edmac_ch4_clk_dis,edmac_ch4_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_socp_clk_dis,socp_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_mipi_clk_dis,mipi_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_pmussi0_clk_dis,pmussi0_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_pmussi1_clk_dis,pmussi1_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_dw_ssi0_clk_dis,dw_ssi0_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_efuse_clk_dis,efuse_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_nandc_clk_dis,nandc_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_hs_uart_clk_dis,hs_uart_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_emi_clk_dis,emi_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_edmac_clk_dis,edmac_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_bootrom_clk_dis,bootrom_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_pwm2_clk_dis,pwm2_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_pwm1_clk_dis,pwm1_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_dt_clk_dis,dt_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_ipcm_clk_dis,ipcm_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_dw_ssi1_clk_dis,dw_ssi1_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_i2c1_clk_dis,i2c1_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_gpio1_clk_dis,gpio1_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_i2c0_clk_dis,i2c0_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_gpio3_clk_dis,gpio3_clk_dis,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkdis1_reserved_0,reserved_0,HI_CRG_CLKDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_mst_aclk_status,mst_aclk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_dsp_aclk_status,dsp_aclk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_soc_hclk_status,soc_hclk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_amon_cpufast_clk_status,amon_cpufast_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_amon_soc_clk_status,amon_soc_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_reserved_2,reserved_2,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_ipf_clk_status,ipf_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_reserved_1,reserved_1,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_edmac_ch4_clk_status,edmac_ch4_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_socp_clk_status,socp_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_mipi_clk_status,mipi_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_pmussi0_clk_status,pmussi0_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_pmussi1_clk_status,pmussi1_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_dw_ssi0_clk_status,dw_ssi0_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_efuse_clk_status,efuse_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_nandc_clk_status,nandc_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_hs_uart_clk_status,hs_uart_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_emi_clk_status,emi_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_edmac_clk_status,edmac_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_bootrom_clk_status,bootrom_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_pwm2_clk_status,pwm2_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_pwm1_clk_status,pwm1_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_dt_clk_status,dt_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_ipcm_clk_status,ipcm_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_dw_ssi1_clk_status,dw_ssi1_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_i2c1_clk_status,i2c1_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_gpio1_clk_status,gpio1_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_i2c0_clk_status,i2c0_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_gpio3_clk_status,gpio3_clk_status,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clkstat1_reserved_0,reserved_0,HI_CRG_CLKSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT1_OFFSET)
HI_SET_GET(hi_crg_clken2_uart3_clk_en,uart3_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_uart2_clk_en,uart2_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_gpio2_clk_en,gpio2_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_cs_clk_en,cs_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_appa9_mbist_clk_en,appa9_mbist_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_moda9_mbist_clk_en,moda9_mbist_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_cpu_aclk_en,cpu_aclk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_mddrc_clk_en,mddrc_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_ddrphy_clk_en,ddrphy_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_ddrphy_ddr_clk_en,ddrphy_ddr_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_axi_mem_clk_en,axi_mem_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_func_wakeup_pd_clk_en,func_wakeup_pd_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_soc_peri_usb_pd_clk_en,soc_peri_usb_pd_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_usbotg_clk_en,usbotg_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_usb_bc_clk_en,usb_bc_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_ssic_host_clk_en,ssic_host_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_ssic_dev_clk_en,ssic_dev_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_mmc0_clk_en,mmc0_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_mmc1_clk_en,mmc1_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_mmc0_phase_clk_en,mmc0_phase_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_mmc1_phase_clk_en,mmc1_phase_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_mmc0_refclk_en,mmc0_refclk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_mmc1_refclk_en,mmc1_refclk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_usbhsic_clk_en,usbhsic_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_sdcc_clk_en,sdcc_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_hpm_clk_en,hpm_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_sha1_clk_en,sha1_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_pcie_ctrl_clk_en,pcie_ctrl_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_pcie_phy_clk_en,pcie_phy_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_reserved,reserved,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clken2_wdog_clk_en,wdog_clk_en,HI_CRG_CLKEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_uart3_clk_dis,uart3_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_uart2_clk_dis,uart2_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_gpio2_clk_dis,gpio2_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_cs_clk_dis,cs_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_appa9_mbist_clk_dis,appa9_mbist_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_moda9_mbist_clk_dis,moda9_mbist_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_cpu_aclk_dis,cpu_aclk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_mddrc_clk_dis,mddrc_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_ddrphy_clk_dis,ddrphy_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_ddrphy_ddr_clk_dis,ddrphy_ddr_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_axi_mem_clk_dis,axi_mem_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_func_wake_pd_clk_dis,func_wake_pd_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_soc_usb_pd_clk_dis,soc_usb_pd_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_usbotg_clk_dis,usbotg_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_usb_bc_clk_dis,usb_bc_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_ssic_host_clk_dis,ssic_host_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_ssic_dev_clk_dis,ssic_dev_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_mmc0_clk_dis,mmc0_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_mmc1_clk_dis,mmc1_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_mmc0_phase_clk_dis,mmc0_phase_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_mmc1_phase_clk_dis,mmc1_phase_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_mmc0_refclk_dis,mmc0_refclk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_mmc1_refclk_dis,mmc1_refclk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_usbhsic_clk_dis,usbhsic_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_sdcc_clk_dis,sdcc_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_hpm_clk_dis,hpm_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_sha1_clk_dis,sha1_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_pcie_ctrl_clk_dis,pcie_ctrl_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_pcie_phy_clk_dis,pcie_phy_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_reserved,reserved,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkdis2_wdog_clk_dis,wdog_clk_dis,HI_CRG_CLKDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_uart3_clk_status,uart3_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_uart2_clk_status,uart2_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_gpio2_clk_status,gpio2_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_cs_clk_status,cs_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_appa9_mbist_clk_status,appa9_mbist_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_moda9_mbist_clk_status,moda9_mbist_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_cpu_aclk_status,cpu_aclk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_mddrc_clk_status,mddrc_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_ddrphy_clk_status,ddrphy_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_ddrphy_ddr_clk_status,ddrphy_ddr_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_axi_mem_clk_status,axi_mem_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_func_wake_pd_clk_status,func_wake_pd_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_soc_usb_pd_clk_status,soc_usb_pd_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_usbotg_clk_status,usbotg_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_usb_bc_clk_status,usb_bc_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_ssic_host_clk_status,ssic_host_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_ssic_dev_clk_status,ssic_dev_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_mmc0_clk_status,mmc0_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_mmc1_clk_status,mmc1_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_mmc0_phase_clk_status,mmc0_phase_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_mmc1_phase_clk_status,mmc1_phase_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_mmc0_refclk_status,mmc0_refclk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_mmc1_refclk_status,mmc1_refclk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_usbhsic_clk_status,usbhsic_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_sdcc_clk_status,sdcc_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_hpm_clk_status,hpm_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_sha1_clk_status,sha1_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_pcie_ctrl_clk_status,pcie_ctrl_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_pcie_phy_clk_status,pcie_phy_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_reserved,reserved,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clkstat2_wdog_clk_status,wdog_clk_status,HI_CRG_CLKSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT2_OFFSET)
HI_SET_GET(hi_crg_clken3_gpio0_clk_en,gpio0_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_uart0_clk_en,uart0_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm0_clk_en,tm0_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm1_clk_en,tm1_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm2_clk_en,tm2_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm3_clk_en,tm3_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm4_clk_en,tm4_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm5_clk_en,tm5_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm6_clk_en,tm6_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm7_clk_en,tm7_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm8_clk_en,tm8_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm9_clk_en,tm9_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm10_clk_en,tm10_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm11_clk_en,tm11_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm12_clk_en,tm12_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm13_clk_en,tm13_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm14_clk_en,tm14_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm15_clk_en,tm15_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm16_clk_en,tm16_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm17_clk_en,tm17_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm18_clk_en,tm18_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm19_clk_en,tm19_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm20_clk_en,tm20_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm21_clk_en,tm21_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm22_clk_en,tm22_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_tm23_clk_en,tm23_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_appa9_clk_en,appa9_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_mdma9_clk_en,mdma9_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_hifi_vic_clk_en,hifi_vic_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_lte_sio_clk_en,lte_sio_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_hifi_dbg_clk_en,hifi_dbg_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clken3_hifi_clk_en,hifi_clk_en,HI_CRG_CLKEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_gpio0_clk_dis,gpio0_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_uart0_clk_dis,uart0_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm0_clk_dis,tm0_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm1_clk_dis,tm1_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm2_clk_dis,tm2_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm3_clk_dis,tm3_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm4_clk_dis,tm4_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm5_clk_dis,tm5_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm6_clk_dis,tm6_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm7_clk_dis,tm7_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm8_clk_dis,tm8_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm9_clk_dis,tm9_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm10_clk_dis,tm10_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm11_clk_dis,tm11_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm12_clk_dis,tm12_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm13_clk_dis,tm13_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm14_clk_dis,tm14_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm15_clk_dis,tm15_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm16_clk_dis,tm16_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm17_clk_dis,tm17_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm18_clk_dis,tm18_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm19_clk_dis,tm19_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm20_clk_dis,tm20_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm21_clk_dis,tm21_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm22_clk_dis,tm22_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_tm23_clk_dis,tm23_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_appa9_clk_dis,appa9_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_mdma9_clk_dis,mdma9_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_hifi_vic_clk_dis,hifi_vic_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_lte_sio_clk_dis,lte_sio_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_hifi_dbg_clk_dis,hifi_dbg_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkdis3_hifi_clk_dis,hifi_clk_dis,HI_CRG_CLKDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_gpio0_clk_status,gpio0_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_uart0_clk_status,uart0_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm0_clk_status,tm0_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm1_clk_status,tm1_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm2_clk_status,tm2_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm3_clk_status,tm3_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm4_clk_status,tm4_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm5_clk_status,tm5_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm6_clk_status,tm6_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm7_clk_status,tm7_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm8_clk_status,tm8_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm9_clk_status,tm9_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm10_clk_status,tm10_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm11_clk_status,tm11_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm12_clk_status,tm12_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm13_clk_status,tm13_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm14_clk_status,tm14_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm15_clk_status,tm15_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm16_clk_status,tm16_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm17_clk_status,tm17_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm18_clk_status,tm18_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm19_clk_status,tm19_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm20_clk_status,tm20_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm21_clk_status,tm21_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm22_clk_status,tm22_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_tm23_clk_status,tm23_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_appa9_clk_status,appa9_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_mdma9_clk_status,mdma9_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_hifi_vic_clk_status,hifi_vic_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_lte_sio_clk_status,lte_sio_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_hifi_dbg_clk_status,hifi_dbg_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkstat3_hifi_clk_status,hifi_clk_status,HI_CRG_CLKSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT3_OFFSET)
HI_SET_GET(hi_crg_clken4_dsp0_pd_clk_en,dsp0_pd_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_dsp0_core_clk_en,dsp0_core_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_dsp0_dbg_clk_en,dsp0_dbg_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_reserved_1,reserved_1,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_guacc_axi_clk_en,guacc_axi_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_cicom0_clk_en,cicom0_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_cicom1_clk_en,cicom1_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_hdlc_clk_en,hdlc_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_upacc_clk_en,upacc_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_sci0_clk_en,sci0_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_sci1_clk_en,sci1_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_uicc_clk_en,uicc_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_uart1_clk_en,uart1_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_dsp_vic_clk_en,dsp_vic_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_cipher_clk_en,cipher_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_gmac_rx_clk_en,gmac_rx_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_gmac_tx_clk_en,gmac_tx_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_gmac_gtx_clk_en,gmac_gtx_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_gmac_switch_clk_en,gmac_switch_clk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_gmac_aclk_en,gmac_aclk_en,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clken4_reserved_0,reserved_0,HI_CRG_CLKEN4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_dsp0_pd_clk_dis,dsp0_pd_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_dsp0_core_clk_dis,dsp0_core_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_dsp0_dbg_clk_dis,dsp0_dbg_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_reserved_1,reserved_1,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_guacc_axi_clk_dis,guacc_axi_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_cicom0_clk_dis,cicom0_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_cicom1_clk_dis,cicom1_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_hdlc_clk_dis,hdlc_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_upacc_clk_dis,upacc_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_sci0_clk_dis,sci0_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_sci1_clk_dis,sci1_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_uicc_clk_dis,uicc_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_uart1_clk_dis,uart1_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_dsp_vic_clk_dis,dsp_vic_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_cipher_clk_dis,cipher_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_gmac_rx_clk_dis,gmac_rx_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_gmac_tx_clk_dis,gmac_tx_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_gmac_gtx_clk_dis,gmac_gtx_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_gmac_switch_clk_dis,gmac_switch_clk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_gmac_aclk_dis,gmac_aclk_dis,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkdis4_reserved_0,reserved_0,HI_CRG_CLKDIS4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_dsp0_pd_clk_status,dsp0_pd_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_dsp0_core_clk_status,dsp0_core_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_dsp0_dbg_clk_status,dsp0_dbg_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_reserved_1,reserved_1,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_guacc_axi_clk_status,guacc_axi_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_cicom0_clk_status,cicom0_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_cicom1_clk_status,cicom1_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_hdlc_clk_status,hdlc_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_upacc_clk_status,upacc_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_sci0_clk_status,sci0_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_sci1_clk_status,sci1_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_uicc_clk_status,uicc_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_uart1_clk_status,uart1_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_dsp_vic_clk_status,dsp_vic_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_cipher_clk_status,cipher_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_gmac_rx_clk_status,gmac_rx_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_gmac_tx_clk_status,gmac_tx_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_gmac_gtx_clk_status,gmac_gtx_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_gmac_switch_clk_status,gmac_switch_clk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_gmac_aclk_status,gmac_aclk_status,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clkstat4_reserved_0,reserved_0,HI_CRG_CLKSTAT4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT4_OFFSET)
HI_SET_GET(hi_crg_clken5_bbp_ao_clk_en,bbp_ao_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_bbpcommon_2a_clk_en,bbpcommon_2a_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_ltebbp_pd_clk_en,ltebbp_pd_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_g1bbp_pd_clk_en,g1bbp_pd_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_g2bbp_pd_clk_en,g2bbp_pd_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_twbbp_pd_clk_en,twbbp_pd_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_wbbp_pd_clk_en,wbbp_pd_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_irm_pd_clk_en,irm_pd_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_lbbp_axi_clk_en,lbbp_axi_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_lbbp_pdt_clk_en,lbbp_pdt_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_lbbp_pdf_clk_en,lbbp_pdf_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_lbbp_tdl_clk_en,lbbp_tdl_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_lbbp_vdl_clk_en,lbbp_vdl_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_lbbp_tds_clk_en,lbbp_tds_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_reserved_1,reserved_1,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_irm_turbo_clk_en,irm_turbo_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_irm_bbc_245m_clk_en,irm_bbc_245m_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_irm_wbbp_122m_clk_en,irm_wbbp_122m_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_twbbp_wbbp_122m_clk_en,twbbp_wbbp_122m_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_twbbp_wbbp_61m_clk_en,twbbp_wbbp_61m_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_twbbp_tbbp_122m_clk_en,twbbp_tbbp_122m_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_twbbp_tbbp_245m_clk_en,twbbp_tbbp_245m_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_wbbp_61m_clk_en,wbbp_61m_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_wbbp_122m_clk_en,wbbp_122m_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_wbbp_245m_clk_en,wbbp_245m_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_wbbp_axi_clk_en,wbbp_axi_clk_en,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clken5_reserved_0,reserved_0,HI_CRG_CLKEN5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKEN5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_bbp_ao_clk_dis,bbp_ao_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_bbpcommon_clk_dis,bbpcommon_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_ltebbp_pd_clk_dis,ltebbp_pd_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_g1bbp_pd_clk_dis,g1bbp_pd_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_g2bbp_pd_clk_dis,g2bbp_pd_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_twbbp_pd_clk_dis,twbbp_pd_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_wbbp_pd_clk_dis,wbbp_pd_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_irm_pd_clk_dis,irm_pd_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_lbbp_axi_clk_dis,lbbp_axi_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_lbbp_pdt_clk_dis,lbbp_pdt_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_lbbp_pdf_clk_dis,lbbp_pdf_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_lbbp_tdl_clk_dis,lbbp_tdl_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_lbbp_vdl_clk_dis,lbbp_vdl_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_lbbp_tds_clk_dis,lbbp_tds_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_twbbp_tbbp_clk_dis,twbbp_tbbp_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_twbbp_wbbp_clk_dis,twbbp_wbbp_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_irm_turbo_clk_dis,irm_turbo_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_irm_bbc_245m_clk_dis,irm_bbc_245m_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_irm_wbbp_122m_clk_dis,irm_wbbp_122m_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_pdtw_wbbp_122m_clk_dis,pdtw_wbbp_122m_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_pdtw_wbbp_61m_clk_dis,pdtw_wbbp_61m_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_pdtw_tbbp_122m_clk_dis,pdtw_tbbp_122m_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_pdtw_tbbp_245m_clk_dis,pdtw_tbbp_245m_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_pdw_61m_clk_dis,pdw_61m_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_pdw_122m_clk_dis,pdw_122m_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_pdw_245m_clk_dis,pdw_245m_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_pdw_axi_clk_dis,pdw_axi_clk_dis,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkdis5_reserved,reserved,HI_CRG_CLKDIS5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIS5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_bbp_ao_clk_stat,bbp_ao_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_bbpcommon_2a_clk_stat,bbpcommon_2a_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_ltebbp_pd_clk_stat,ltebbp_pd_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_g1bbp_pd_clk_stat,g1bbp_pd_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_g2bbp_pd_clk_stat,g2bbp_pd_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_twbbp_pd_clk_stat,twbbp_pd_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_wbbp_pd_clk_stat,wbbp_pd_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_irm_pd_clk_stat,irm_pd_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_lbbp_axi_clk_stat,lbbp_axi_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_lbbp_pdt_clk_stat,lbbp_pdt_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_lbbp_pdf_clk_stat,lbbp_pdf_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_lbbp_tdl_clk_stat,lbbp_tdl_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_lbbp_vdl_clk_stat,lbbp_vdl_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_lbbp_tds_clk_stat,lbbp_tds_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_twbbp_tbbp_clk_stat,twbbp_tbbp_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_twbbp_wbbp_clk_stat,twbbp_wbbp_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_irm_turbo_clk_stat,irm_turbo_clk_stat,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_irm_bbc_245m_clk_status,irm_bbc_245m_clk_status,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_irm_wbbp_122m_clk_status,irm_wbbp_122m_clk_status,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_pdtw_wbbp_122m_clk_status,pdtw_wbbp_122m_clk_status,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_pdtw_wbbp_61m_clk_status,pdtw_wbbp_61m_clk_status,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_pdtw_tbbp_122m_clk_status,pdtw_tbbp_122m_clk_status,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_pdtw_tbbp_245m_clk_status,pdtw_tbbp_245m_clk_status,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_pdw_61m_clk_status,pdw_61m_clk_status,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_pdw_122m_clk_status,pdw_122m_clk_status,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_pdw_245m_clk_status,pdw_245m_clk_status,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_pdw_axi_clk_status,pdw_axi_clk_status,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_clkstat5_reserved,reserved,HI_CRG_CLKSTAT5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSTAT5_OFFSET)
HI_SET_GET(hi_crg_srsten1_appa9_cpu_srst_en,appa9_cpu_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_appa9_dbg_srst_en,appa9_dbg_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_appa9_peri_srst_en,appa9_peri_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_appa9_scu_srst_en,appa9_scu_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_appa9_ptm_srst_en,appa9_ptm_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_appa9_wd_srst_en,appa9_wd_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_moda9_cpu_srst_en,moda9_cpu_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_moda9_dbg_srst_en,moda9_dbg_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_moda9_peri_srst_en,moda9_peri_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_moda9_scu_srst_en,moda9_scu_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_moda9_ptm_srst_en,moda9_ptm_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_moda9_wd_srst_en,moda9_wd_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_hpm_srst_en,hpm_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_hpm_clkdiv_srst_en,hpm_clkdiv_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_appa9_srst_en,appa9_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_mdma9_srst_en,mdma9_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_cm3_dbg_srst_en,cm3_dbg_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_mddrc_srst_en,mddrc_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_cm3_cpu_srst_en,cm3_cpu_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_cicom0_srst_en,cicom0_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_cicom1_srst_en,cicom1_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_hdlc_srst_en,hdlc_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_upacc_srst_en,upacc_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_edmac_ch4_srst_en,edmac_ch4_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_edmac_srst_en,edmac_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_emi_srst_en,emi_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_uicc_srst_en,uicc_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_reserved,reserved,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_amon_cpufast_srst_en,amon_cpufast_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_amon_soc_srst_en,amon_soc_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_dt_srst_en,dt_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srsten1_sha1_srst_en,sha1_srst_en,HI_CRG_SRSTEN1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_appa9_cpu_srst_dis,appa9_cpu_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_appa9_dbg_srst_dis,appa9_dbg_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_appa9_peri_srst_dis,appa9_peri_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_appa9_scu_srst_dis,appa9_scu_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_appa9_ptm_srst_dis,appa9_ptm_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_appa9_wd_srst_dis,appa9_wd_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_moda9_cpu_srst_dis,moda9_cpu_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_moda9_dbg_srst_dis,moda9_dbg_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_moda9_peri_srst_dis,moda9_peri_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_moda9_scu_srst_dis,moda9_scu_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_moda9_ptm_srst_dis,moda9_ptm_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_moda9_wd_srst_dis,moda9_wd_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_hpm_srst_dis,hpm_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_hpm_clkdiv_srst_dis,hpm_clkdiv_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_appa9_srst_dis,appa9_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_mdma9_srst_dis,mdma9_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_cm3_dbg_srst_dis,cm3_dbg_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_mddrc_srst_dis,mddrc_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_cm3_cpu_srst_dis,cm3_cpu_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_cicom0_srst_dis,cicom0_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_cicom1_srst_dis,cicom1_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_hdlc_srst_dis,hdlc_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_upacc_srst_dis,upacc_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_edmac_ch4_srst_dis,edmac_ch4_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_edmac_srst_dis,edmac_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_emi_srst_dis,emi_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_uicc_srst_dis,uicc_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_reserved,reserved,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_amon_cpufast_srst_dis,amon_cpufast_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_amon_soc_srst_dis,amon_soc_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_dt_srst_dis,dt_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srstdis1_sha1_srst_dis,sha1_srst_dis,HI_CRG_SRSTDIS1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS1_OFFSET)
HI_SET_GET(hi_crg_srststat1_appa9_cpu_srst_status,appa9_cpu_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_appa9_dbg_srst_status,appa9_dbg_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_appa9_peri_srst_status,appa9_peri_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_appa9_scu_srst_status,appa9_scu_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_appa9_ptm_srst_status,appa9_ptm_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_appa9_wd_srst_status,appa9_wd_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_moda9_cpu_srst_status,moda9_cpu_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_moda9_dbg_srst_status,moda9_dbg_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_moda9_peri_srst_status,moda9_peri_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_moda9_scu_srst_status,moda9_scu_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_moda9_ptm_srst_status,moda9_ptm_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_moda9_wd_srst_status,moda9_wd_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_hpm_srst_status,hpm_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_hpm_clkdiv_srst_status,hpm_clkdiv_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_appa9_srst_status,appa9_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_mdma9_srst_status,mdma9_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_cm3_dbg_srst_status,cm3_dbg_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_mddrc_srst_status,mddrc_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_cm3_core_srst_status,cm3_core_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_cicom0_srst_status,cicom0_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_cicom1_srst_status,cicom1_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_hdlc_srst_status,hdlc_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_upacc_srst_status,upacc_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_edmac_ch4_srst_status,edmac_ch4_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_edmac_srst_status,edmac_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_emi_srst_status,emi_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_uicc_srst_status,uicc_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_reserved,reserved,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_amon_cpufast_srst_status,amon_cpufast_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_amon_soc_srst_status,amon_soc_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_dt_srst_status,dt_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srststat1_sha1_srst_status,sha1_srst_status,HI_CRG_SRSTSTAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT1_OFFSET)
HI_SET_GET(hi_crg_srsten2_tensi_dps0_pd_srst_en,tensi_dps0_pd_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_tensi_dsp0_core_srst_en,tensi_dsp0_core_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_tensi_dsp0_dbg_srst_en,tensi_dsp0_dbg_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_reserved_3,reserved_3,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_func_wakeup_pd_srst_en,func_wakeup_pd_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_soc_peri_usb_pd_srst_en,soc_peri_usb_pd_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_mmc0_srst_en,mmc0_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_mmc1_srst_en,mmc1_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_sdcc_srst_en,sdcc_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_rserved,rserved,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_gmac_srst_req,gmac_srst_req,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_reserved_2,reserved_2,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_pcie_ctrl_srst_req,pcie_ctrl_srst_req,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_pcie_phy_srst_req,pcie_phy_srst_req,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_ddrphy_div_srst_req,ddrphy_div_srst_req,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_reserved_1,reserved_1,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_hifi_core_srst_en,hifi_core_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_hifi_pd_srst_en,hifi_pd_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_hifi_dbg_srst_en,hifi_dbg_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_usbotg_bc_srst_en,usbotg_bc_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_usbotg_phy_srst_en,usbotg_phy_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_usbotg_ctrl_srst_en,usbotg_ctrl_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_usbotg_ctrl_vaux_srst_en,usbotg_ctrl_vaux_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_usbotg_ctrl_vcc_srst_en,usbotg_ctrl_vcc_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_usbhsic_ctrl_srst_en,usbhsic_ctrl_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_usbhsic_phy_srst_en,usbhsic_phy_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_cs_srst_en,cs_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_tsensor_srst_en,tsensor_srst_en,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srsten2_reserved_0,reserved_0,HI_CRG_SRSTEN2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_tensi_dps0_pd_srst_dis,tensi_dps0_pd_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_tensi_dsp0_core_srst_dis,tensi_dsp0_core_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_tensi_dsp0_dbg_srst_dis,tensi_dsp0_dbg_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_reserved_3,reserved_3,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_func_wakeup_pd_srst_dis,func_wakeup_pd_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_soc_peri_usb_pd_srst_dis,soc_peri_usb_pd_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_mmc0_srst_dis,mmc0_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_mmc1_srst_dis,mmc1_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_sdcc_srst_dis,sdcc_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_reserved_2,reserved_2,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_gmac_srst_dis,gmac_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_ssicdev_ctrl_srst_dis,ssicdev_ctrl_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_ssicphy_srst_dis,ssicphy_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_pcie_ctrl_srst_dis,pcie_ctrl_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_pcie_phy_srst_dis,pcie_phy_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_ddrphy_div_srst_dis,ddrphy_div_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_reserved_1,reserved_1,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_hifi_core_srst_dis,hifi_core_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_hifi_pd_srst_dis,hifi_pd_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_hifi_dbg_srst_dis,hifi_dbg_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_usbotg_bc_srst_dis,usbotg_bc_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_usbotg_phy_srst_dis,usbotg_phy_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_usbotg_ctrl_srst_dis,usbotg_ctrl_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_usbotg_ctrl_vaux_srst_dis,usbotg_ctrl_vaux_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_usbotg_ctrl_vcc_srst_dis,usbotg_ctrl_vcc_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_usbhsic_ctrl_srst_dis,usbhsic_ctrl_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_usbhsic_phy_srst_dis,usbhsic_phy_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_cs_srst_dis,cs_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_tsensor_srst_dis,tsensor_srst_dis,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srstdis2_reserved_0,reserved_0,HI_CRG_SRSTDIS2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS2_OFFSET)
HI_SET_GET(hi_crg_srststat2_tensi_dps0_pd_srst_status,tensi_dps0_pd_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_tensi_dsp0_core_srst_status,tensi_dsp0_core_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_tensi_dsp0_dbg_srst_status,tensi_dsp0_dbg_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_reserved_3,reserved_3,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_func_wakeup_pd_srst_status,func_wakeup_pd_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_soc_peri_usb_pd_srst_status,soc_peri_usb_pd_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_mmc0_srst_status,mmc0_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_mmc1_srst_status,mmc1_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_sdcc_srst_status,sdcc_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_reserved_2,reserved_2,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_gmac_srst_status,gmac_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_ssicdev_ctrl_srst_status,ssicdev_ctrl_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_ssicphy_srst_status,ssicphy_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_pcie_ctrl_srst_status,pcie_ctrl_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_pcie_phy_srst_status,pcie_phy_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_ddrphy_div_srst_status,ddrphy_div_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_reserved_1,reserved_1,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_hificore_srst_status,hificore_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_hifi_pd_srst_status,hifi_pd_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_hifi_dbg_srst_status,hifi_dbg_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_usbotg_bc_srst_status,usbotg_bc_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_usbotg_phy_srst_status,usbotg_phy_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_usbotg_ctrl_srst_status,usbotg_ctrl_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_usbotg_ctrl_vaux_srst_status,usbotg_ctrl_vaux_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_usbotg_ctrl_vcc_srst_status,usbotg_ctrl_vcc_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_usbhsic_ctrl_srst_status,usbhsic_ctrl_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_usbhsic_phy_srst_v,usbhsic_phy_srst_v,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_cs_srst_status,cs_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_tsensor_srst_status,tsensor_srst_status,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srststat2_reserved_0,reserved_0,HI_CRG_SRSTSTAT2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT2_OFFSET)
HI_SET_GET(hi_crg_srsten3_bbp_crg_srst_en,bbp_crg_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_bbpcommon_2a_srst_en,bbpcommon_2a_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_lbbp_pd_srst_en,lbbp_pd_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_g1bbp_pd_srst_en,g1bbp_pd_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_g2bbp_pd_srst_en,g2bbp_pd_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_twbbp_pd_srst_en,twbbp_pd_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_wbbp_pd_srst_en,wbbp_pd_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_irm_pd_srst_en,irm_pd_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_bbc_lbbp_pdt_srst_en,bbc_lbbp_pdt_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_bbc_lbbp_pdf_srst_en,bbc_lbbp_pdf_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_bbc_lbbp_tdl_srst_en,bbc_lbbp_tdl_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_bbc_tbbp_245m_srst_en,bbc_tbbp_245m_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_bbc_twbbp_122m_srst_en,bbc_twbbp_122m_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_bbc_g1bbp_104m_srst_en,bbc_g1bbp_104m_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_bbc_g2bbp_104m_srst_en,bbc_g2bbp_104m_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_reserved,reserved,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srsten3_abb_srst_en,abb_srst_en,HI_CRG_SRSTEN3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTEN3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_bbp_crg_srst_dis,bbp_crg_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_bbpcommon_2a_pd_srst_dis,bbpcommon_2a_pd_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_lbbp_pd_srst_dis,lbbp_pd_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_g1bbp_pd_srst_dis,g1bbp_pd_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_g2bbp_pd_srst_dis,g2bbp_pd_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_twbbp_pd_srst_dis,twbbp_pd_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_wbbp_pd_srst_dis,wbbp_pd_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_irm_pd_srst_dis,irm_pd_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_bbc_lbbp_pdt_srst_dis,bbc_lbbp_pdt_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_bbc_lbbp_pdf_srst_dis,bbc_lbbp_pdf_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_bbc_lbbp_tdl_srst_dis,bbc_lbbp_tdl_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_bbc_tbbp_245m_srst_dis,bbc_tbbp_245m_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_bbc_twbbp_122m_srst_dis,bbc_twbbp_122m_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_bbc_g1bbp_104m_srst_dis,bbc_g1bbp_104m_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_bbc_g2bbp_104m_srst_dis,bbc_g2bbp_104m_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_reserved,reserved,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srstdis3_abb_srst_dis,abb_srst_dis,HI_CRG_SRSTDIS3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTDIS3_OFFSET)
HI_SET_GET(hi_crg_srststat3_bbp_crg_srst_stat,bbp_crg_srst_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_bbpcommon_2a_srst_stat,bbpcommon_2a_srst_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_lbbp_pd_srst_stat,lbbp_pd_srst_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_g1bbp_pd_srst_stat,g1bbp_pd_srst_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_g2bbp_pd_srst_stat,g2bbp_pd_srst_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_twbbp_pd_srst_stat,twbbp_pd_srst_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_wbbp_pd_srst_stat,wbbp_pd_srst_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_irm_pd_srst_stat,irm_pd_srst_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_bbc_lbbp_pdt_srstctrl_stat,bbc_lbbp_pdt_srstctrl_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_bbc_lbbp_pdf_srstctrl_stat,bbc_lbbp_pdf_srstctrl_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_bbc_lbbp_tdl_srstctrl_stat,bbc_lbbp_tdl_srstctrl_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_bbc_tbbp_245m_srstctrl_stat,bbc_tbbp_245m_srstctrl_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_bbc_twbbp_122m_srstctrl_stat,bbc_twbbp_122m_srstctrl_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_bbc_g1bbp_104m_srstctrl_stat,bbc_g1bbp_104m_srstctrl_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_bbc_g2bbp_104m_srstctrl_stat,bbc_g2bbp_104m_srstctrl_stat,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_reserved,reserved,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_srststat3_abb_srst_status,abb_srst_status,HI_CRG_SRSTSTAT3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_SRSTSTAT3_OFFSET)
HI_SET_GET(hi_crg_clkdiv1_pcm_bclk_div,pcm_bclk_div,HI_CRG_CLKDIV1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV1_OFFSET)
HI_SET_GET(hi_crg_clkdiv1_pcm_sync_div,pcm_sync_div,HI_CRG_CLKDIV1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV1_OFFSET)
HI_SET_GET(hi_crg_clkdiv1_reserved,reserved,HI_CRG_CLKDIV1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV1_OFFSET)
HI_SET_GET(hi_crg_clkdiv2_appa9_clk_div,appa9_clk_div,HI_CRG_CLKDIV2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV2_OFFSET)
HI_SET_GET(hi_crg_clkdiv2_mdma9_clk_div,mdma9_clk_div,HI_CRG_CLKDIV2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV2_OFFSET)
HI_SET_GET(hi_crg_clkdiv2_soc_clk_div,soc_clk_div,HI_CRG_CLKDIV2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV2_OFFSET)
HI_SET_GET(hi_crg_clkdiv2_fast_clk_div,fast_clk_div,HI_CRG_CLKDIV2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV2_OFFSET)
HI_SET_GET(hi_crg_clkdiv2_reserved_2,reserved_2,HI_CRG_CLKDIV2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV2_OFFSET)
HI_SET_GET(hi_crg_clkdiv2_ddr_rate_sel,ddr_rate_sel,HI_CRG_CLKDIV2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV2_OFFSET)
HI_SET_GET(hi_crg_clkdiv2_reserved_1,reserved_1,HI_CRG_CLKDIV2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV2_OFFSET)
HI_SET_GET(hi_crg_clkdiv2_apb_freqmode,apb_freqmode,HI_CRG_CLKDIV2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV2_OFFSET)
HI_SET_GET(hi_crg_clkdiv2_reserved_0,reserved_0,HI_CRG_CLKDIV2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV2_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_mmc0_cclk_div,mmc0_cclk_div,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_reserved_3,reserved_3,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_mmc0_refclk_sel,mmc0_refclk_sel,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_mmc0_phase_clk_div,mmc0_phase_clk_div,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_reserved_2,reserved_2,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_mmc1_cclk_div,mmc1_cclk_div,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_reserved_1,reserved_1,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_mmc1_refclk_sel,mmc1_refclk_sel,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_mmc1_phase_clk_div,mmc1_phase_clk_div,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_reserved_0,reserved_0,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_hpm_clk_div,hpm_clk_div,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv3_cipher_clk_div,cipher_clk_div,HI_CRG_CLKDIV3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV3_OFFSET)
HI_SET_GET(hi_crg_clkdiv4_hifi_clk_div_num,hifi_clk_div_num,HI_CRG_CLKDIV4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV4_OFFSET)
HI_SET_GET(hi_crg_clkdiv4_hifi_freqmode,hifi_freqmode,HI_CRG_CLKDIV4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV4_OFFSET)
HI_SET_GET(hi_crg_clkdiv4_hifi_refclk_sel,hifi_refclk_sel,HI_CRG_CLKDIV4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV4_OFFSET)
HI_SET_GET(hi_crg_clkdiv4_reserved,reserved,HI_CRG_CLKDIV4_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV4_OFFSET)
HI_SET_GET(hi_crg_clkdiv5_bbe_clk_div_num,bbe_clk_div_num,HI_CRG_CLKDIV5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV5_OFFSET)
HI_SET_GET(hi_crg_clkdiv5_reserved_2,reserved_2,HI_CRG_CLKDIV5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV5_OFFSET)
HI_SET_GET(hi_crg_clkdiv5_bbe_freqmode,bbe_freqmode,HI_CRG_CLKDIV5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV5_OFFSET)
HI_SET_GET(hi_crg_clkdiv5_bbe_refclk_sel,bbe_refclk_sel,HI_CRG_CLKDIV5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV5_OFFSET)
HI_SET_GET(hi_crg_clkdiv5_sci0_clk_div_num,sci0_clk_div_num,HI_CRG_CLKDIV5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV5_OFFSET)
HI_SET_GET(hi_crg_clkdiv5_reserved_1,reserved_1,HI_CRG_CLKDIV5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV5_OFFSET)
HI_SET_GET(hi_crg_clkdiv5_sci1_clk_div_num,sci1_clk_div_num,HI_CRG_CLKDIV5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV5_OFFSET)
HI_SET_GET(hi_crg_clkdiv5_reserved_0,reserved_0,HI_CRG_CLKDIV5_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV5_OFFSET)
HI_SET_GET(hi_crg_mmc_ctrl_mmc0_drv_sel,mmc0_drv_sel,HI_CRG_MMC_CTRL_T,HI_SYSCRG_BASE_ADDR, HI_CRG_MMC_CTRL_OFFSET)
HI_SET_GET(hi_crg_mmc_ctrl_mmc0_clk_bypass,mmc0_clk_bypass,HI_CRG_MMC_CTRL_T,HI_SYSCRG_BASE_ADDR, HI_CRG_MMC_CTRL_OFFSET)
HI_SET_GET(hi_crg_mmc_ctrl_mmc0_sample_sel,mmc0_sample_sel,HI_CRG_MMC_CTRL_T,HI_SYSCRG_BASE_ADDR, HI_CRG_MMC_CTRL_OFFSET)
HI_SET_GET(hi_crg_mmc_ctrl_mmc0_sample_ctrl,mmc0_sample_ctrl,HI_CRG_MMC_CTRL_T,HI_SYSCRG_BASE_ADDR, HI_CRG_MMC_CTRL_OFFSET)
HI_SET_GET(hi_crg_mmc_ctrl_mmc1_drv_sel,mmc1_drv_sel,HI_CRG_MMC_CTRL_T,HI_SYSCRG_BASE_ADDR, HI_CRG_MMC_CTRL_OFFSET)
HI_SET_GET(hi_crg_mmc_ctrl_mmc1_clk_bypass,mmc1_clk_bypass,HI_CRG_MMC_CTRL_T,HI_SYSCRG_BASE_ADDR, HI_CRG_MMC_CTRL_OFFSET)
HI_SET_GET(hi_crg_mmc_ctrl_mmc1_sample_sel,mmc1_sample_sel,HI_CRG_MMC_CTRL_T,HI_SYSCRG_BASE_ADDR, HI_CRG_MMC_CTRL_OFFSET)
HI_SET_GET(hi_crg_mmc_ctrl_mmc1_sample_ctrl,mmc1_sample_ctrl,HI_CRG_MMC_CTRL_T,HI_SYSCRG_BASE_ADDR, HI_CRG_MMC_CTRL_OFFSET)
HI_SET_GET(hi_crg_plllock_ctrl_pll_lock_ctrl,pll_lock_ctrl,HI_CRG_PLLLOCK_CTRL_T,HI_SYSCRG_BASE_ADDR, HI_CRG_PLLLOCK_CTRL_OFFSET)
HI_SET_GET(hi_crg_plllock_ctrl_pll_clk_dis_cfg,pll_clk_dis_cfg,HI_CRG_PLLLOCK_CTRL_T,HI_SYSCRG_BASE_ADDR, HI_CRG_PLLLOCK_CTRL_OFFSET)
HI_SET_GET(hi_crg_plllock_ctrl_pll_lock_mode,pll_lock_mode,HI_CRG_PLLLOCK_CTRL_T,HI_SYSCRG_BASE_ADDR, HI_CRG_PLLLOCK_CTRL_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_soc_tcxo_refclk_sel,soc_tcxo_refclk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_pmu_tcxo_clk_sel,pmu_tcxo_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_gps_tcxo_clk_sel,gps_tcxo_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_wifi_tcxo_clk_sel,wifi_tcxo_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_sleep_clk_sel,sleep_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_uart0_clk_sel,uart0_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_sio_clk_sel,sio_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_cs_clk_sel,cs_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_a9pll_clk_sel,a9pll_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_reserved,reserved,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_pwm0_clk_sel,pwm0_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_pwm1_clk_sel,pwm1_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_tcssi0_clk_sel,tcssi0_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_tcssi1_clk_sel,tcssi1_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_ushsic_utmi_clk_dis,ushsic_utmi_clk_dis,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_usbhsic_utmi_clk_sel,usbhsic_utmi_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_hpm_refclk_sel,hpm_refclk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_a9_wd_srst_en,a9_wd_srst_en,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_gmac_rx_clk_sel,gmac_rx_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_gmac_tx_clk_sel,gmac_tx_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_gmac_rtx_clk_sel,gmac_rtx_clk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_usbphy_refclk_sel,usbphy_refclk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_peripll_refclk_sel,peripll_refclk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_cs_refclk_sel,cs_refclk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_mmc1_refclk_sel,mmc1_refclk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_sio_refclk_sel,sio_refclk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel1_mmc0_refclk_sel,mmc0_refclk_sel,HI_CRG_CLK_SEL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL1_OFFSET)
HI_SET_GET(hi_crg_clk_sel2_timer0_6_clk_sel,timer0_6_clk_sel,HI_CRG_CLK_SEL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL2_OFFSET)
HI_SET_GET(hi_crg_clk_sel2_reserved_3,reserved_3,HI_CRG_CLK_SEL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL2_OFFSET)
HI_SET_GET(hi_crg_clk_sel2_timer8_14_clk_sel,timer8_14_clk_sel,HI_CRG_CLK_SEL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL2_OFFSET)
HI_SET_GET(hi_crg_clk_sel2_reserved_2,reserved_2,HI_CRG_CLK_SEL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL2_OFFSET)
HI_SET_GET(hi_crg_clk_sel2_timer16_22_clk_sel,timer16_22_clk_sel,HI_CRG_CLK_SEL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL2_OFFSET)
HI_SET_GET(hi_crg_clk_sel2_reserved_1,reserved_1,HI_CRG_CLK_SEL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL2_OFFSET)
HI_SET_GET(hi_crg_clk_sel2_timer7_clk_sel,timer7_clk_sel,HI_CRG_CLK_SEL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL2_OFFSET)
HI_SET_GET(hi_crg_clk_sel2_timer15_clk_sel,timer15_clk_sel,HI_CRG_CLK_SEL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL2_OFFSET)
HI_SET_GET(hi_crg_clk_sel2_timer23_clk_sel,timer23_clk_sel,HI_CRG_CLK_SEL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL2_OFFSET)
HI_SET_GET(hi_crg_clk_sel2_reserved_0,reserved_0,HI_CRG_CLK_SEL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL2_OFFSET)
HI_SET_GET(hi_crg_clk_sel3_abb_tcxo_clk_sel,abb_tcxo_clk_sel,HI_CRG_CLK_SEL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET)
HI_SET_GET(hi_crg_clk_sel3_bbppll_refclk_sel,bbppll_refclk_sel,HI_CRG_CLK_SEL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET)
HI_SET_GET(hi_crg_clk_sel3_bbp_tcxo_clk_sel,bbp_tcxo_clk_sel,HI_CRG_CLK_SEL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET)
HI_SET_GET(hi_crg_clk_sel3_ch0_tcxo_clk_sel,ch0_tcxo_clk_sel,HI_CRG_CLK_SEL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET)
HI_SET_GET(hi_crg_clk_sel3_ch1_tcxo_clk_sel,ch1_tcxo_clk_sel,HI_CRG_CLK_SEL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET)
HI_SET_GET(hi_crg_clk_sel3_g1bbp_104m_clk_sel,g1bbp_104m_clk_sel,HI_CRG_CLK_SEL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET)
HI_SET_GET(hi_crg_clk_sel3_g2bbp_104m_clk_sel,g2bbp_104m_clk_sel,HI_CRG_CLK_SEL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET)
HI_SET_GET(hi_crg_clk_sel3_tdl_clk_sel,tdl_clk_sel,HI_CRG_CLK_SEL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET)
HI_SET_GET(hi_crg_clk_sel3_lbbp_vdl_clk_sel,lbbp_vdl_clk_sel,HI_CRG_CLK_SEL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET)
HI_SET_GET(hi_crg_clk_sel3_lbbp_pdf_clk_sel,lbbp_pdf_clk_sel,HI_CRG_CLK_SEL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET)
HI_SET_GET(hi_crg_clk_sel3_reserved,reserved,HI_CRG_CLK_SEL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLK_SEL3_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl1_dfs_frac,dfs_frac,HI_CRG_DFS1_CTRL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL1_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl1_reserved,reserved,HI_CRG_DFS1_CTRL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL1_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl2_dfs_intprog,dfs_intprog,HI_CRG_DFS1_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl2_dfs_refdiv,dfs_refdiv,HI_CRG_DFS1_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl2_reserved_2,reserved_2,HI_CRG_DFS1_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl2_dfs_postdiv2,dfs_postdiv2,HI_CRG_DFS1_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl2_reserved_1,reserved_1,HI_CRG_DFS1_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl2_dfs_postdiv1,dfs_postdiv1,HI_CRG_DFS1_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl2_reserved_0,reserved_0,HI_CRG_DFS1_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl3_pd,pd,HI_CRG_DFS1_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl3_reserved_1,reserved_1,HI_CRG_DFS1_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl3_dsmpd,dsmpd,HI_CRG_DFS1_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl3_phase4_pd,phase4_pd,HI_CRG_DFS1_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl3_postdivpd,postdivpd,HI_CRG_DFS1_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl3_vcopd,vcopd,HI_CRG_DFS1_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl3_dacpd,dacpd,HI_CRG_DFS1_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl3_bypass,bypass,HI_CRG_DFS1_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl3_pll_ctrl,pll_ctrl,HI_CRG_DFS1_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl3_reserved_0,reserved_0,HI_CRG_DFS1_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs1_ctrl3_lock,lock,HI_CRG_DFS1_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS1_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl1_dfs_frac,dfs_frac,HI_CRG_DFS2_CTRL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL1_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl1_reserved,reserved,HI_CRG_DFS2_CTRL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL1_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl2_dfs_intprog,dfs_intprog,HI_CRG_DFS2_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl2_dfs_refdiv,dfs_refdiv,HI_CRG_DFS2_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl2_reserved_2,reserved_2,HI_CRG_DFS2_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl2_dfs_postdiv2,dfs_postdiv2,HI_CRG_DFS2_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl2_reserved_1,reserved_1,HI_CRG_DFS2_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl2_dfs_postdiv1,dfs_postdiv1,HI_CRG_DFS2_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl2_reserved_0,reserved_0,HI_CRG_DFS2_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl3_pd,pd,HI_CRG_DFS2_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl3_reserved_1,reserved_1,HI_CRG_DFS2_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl3_dsmpd,dsmpd,HI_CRG_DFS2_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl3_phase4_pd,phase4_pd,HI_CRG_DFS2_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl3_postdivpd,postdivpd,HI_CRG_DFS2_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl3_vcopd,vcopd,HI_CRG_DFS2_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl3_dacpd,dacpd,HI_CRG_DFS2_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl3_bypass,bypass,HI_CRG_DFS2_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl3_reserved_0,reserved_0,HI_CRG_DFS2_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs2_ctrl3_lock,lock,HI_CRG_DFS2_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS2_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs3_ctrl1_reserved,reserved,HI_CRG_DFS3_CTRL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS3_CTRL1_OFFSET)
HI_SET_GET(hi_crg_dfs3_ctrl2_reserved,reserved,HI_CRG_DFS3_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS3_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs3_ctrl3_reserved,reserved,HI_CRG_DFS3_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS3_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs4_ctrl1_reserved,reserved,HI_CRG_DFS4_CTRL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS4_CTRL1_OFFSET)
HI_SET_GET(hi_crg_dfs4_ctrl2_reserved,reserved,HI_CRG_DFS4_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS4_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs4_ctrl3_reserved,reserved,HI_CRG_DFS4_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS4_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl1_dfs_frac,dfs_frac,HI_CRG_DFS5_CTRL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL1_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl1_reserved,reserved,HI_CRG_DFS5_CTRL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL1_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl2_dfs_intprog,dfs_intprog,HI_CRG_DFS5_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl2_dfs_refdiv,dfs_refdiv,HI_CRG_DFS5_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl2_reserved_2,reserved_2,HI_CRG_DFS5_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl2_dfs_postdiv2,dfs_postdiv2,HI_CRG_DFS5_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl2_reserved_1,reserved_1,HI_CRG_DFS5_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl2_dfs_postdiv1,dfs_postdiv1,HI_CRG_DFS5_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl2_reserved_0,reserved_0,HI_CRG_DFS5_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl3_pd,pd,HI_CRG_DFS5_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl3_reserved_1,reserved_1,HI_CRG_DFS5_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl3_dsmpd,dsmpd,HI_CRG_DFS5_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl3_phase4_pd,phase4_pd,HI_CRG_DFS5_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl3_postdivpd,postdivpd,HI_CRG_DFS5_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl3_vcopd,vcopd,HI_CRG_DFS5_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl3_dacpd,dacpd,HI_CRG_DFS5_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl3_bypass,bypass,HI_CRG_DFS5_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl3_pll_ctrl,pll_ctrl,HI_CRG_DFS5_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl3_reserved_0,reserved_0,HI_CRG_DFS5_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs5_ctrl3_lock,lock,HI_CRG_DFS5_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS5_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl1_dfs_frac,dfs_frac,HI_CRG_DFS6_CTRL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL1_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl1_reserved,reserved,HI_CRG_DFS6_CTRL1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL1_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl2_dfs_intprog,dfs_intprog,HI_CRG_DFS6_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl2_dfs_refdiv,dfs_refdiv,HI_CRG_DFS6_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl2_reserved_2,reserved_2,HI_CRG_DFS6_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl2_dfs_postdiv2,dfs_postdiv2,HI_CRG_DFS6_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl2_reserved_1,reserved_1,HI_CRG_DFS6_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl2_dfs_postdiv1,dfs_postdiv1,HI_CRG_DFS6_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl2_reserved_0,reserved_0,HI_CRG_DFS6_CTRL2_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL2_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl3_pd,pd,HI_CRG_DFS6_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl3_reserved_1,reserved_1,HI_CRG_DFS6_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl3_dsmpd,dsmpd,HI_CRG_DFS6_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl3_phase4_pd,phase4_pd,HI_CRG_DFS6_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl3_postdivpd,postdivpd,HI_CRG_DFS6_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl3_vcopd,vcopd,HI_CRG_DFS6_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl3_dacpd,dacpd,HI_CRG_DFS6_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl3_bypass,bypass,HI_CRG_DFS6_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl3_pll_ctrl,pll_ctrl,HI_CRG_DFS6_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl3_reserved_0,reserved_0,HI_CRG_DFS6_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL3_OFFSET)
HI_SET_GET(hi_crg_dfs6_ctrl3_lock,lock,HI_CRG_DFS6_CTRL3_T,HI_SYSCRG_BASE_ADDR, HI_CRG_DFS6_CTRL3_OFFSET)
HI_SET_GET(hi_crg_clksw_stat1_uart0_clksw_stat,uart0_clksw_stat,HI_CRG_CLKSW_STAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSW_STAT1_OFFSET)
HI_SET_GET(hi_crg_clksw_stat1_socpll_refclksw_stat,socpll_refclksw_stat,HI_CRG_CLKSW_STAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSW_STAT1_OFFSET)
HI_SET_GET(hi_crg_clksw_stat1_dsp_ref_clksw_stat,dsp_ref_clksw_stat,HI_CRG_CLKSW_STAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSW_STAT1_OFFSET)
HI_SET_GET(hi_crg_clksw_stat1_hifi_ref_clksw_stat,hifi_ref_clksw_stat,HI_CRG_CLKSW_STAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSW_STAT1_OFFSET)
HI_SET_GET(hi_crg_clksw_stat1_pwm0_clksw_stat,pwm0_clksw_stat,HI_CRG_CLKSW_STAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSW_STAT1_OFFSET)
HI_SET_GET(hi_crg_clksw_stat1_pwm1_clksw_stat,pwm1_clksw_stat,HI_CRG_CLKSW_STAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSW_STAT1_OFFSET)
HI_SET_GET(hi_crg_clksw_stat1_ssic_pa_ref_clksw_stat,ssic_pa_ref_clksw_stat,HI_CRG_CLKSW_STAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSW_STAT1_OFFSET)
HI_SET_GET(hi_crg_clksw_stat1_a9_pll_clksw_stat,a9_pll_clksw_stat,HI_CRG_CLKSW_STAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSW_STAT1_OFFSET)
HI_SET_GET(hi_crg_clksw_stat1_reserved,reserved,HI_CRG_CLKSW_STAT1_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKSW_STAT1_OFFSET)
HI_SET_GET(hi_crg_clkdiv6_cm3_clk_div,cm3_clk_div,HI_CRG_CLKDIV6_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV6_OFFSET)
HI_SET_GET(hi_crg_clkdiv6_reserved,reserved,HI_CRG_CLKDIV6_T,HI_SYSCRG_BASE_ADDR, HI_CRG_CLKDIV6_OFFSET)

#endif

#endif // __HI_SYSCRG_H__

