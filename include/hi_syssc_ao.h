/******************************************************************************/
/*  Copyright (C), 2007-2014, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_syssc_ao.h */
/* Version       : 2.0 */
/* Author        : xxx*/
/* Created       : 2014-02-18*/
/* Last Modified : */
/* Description   :  The C union definition file for the module syssc_ao*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Author        : xxx*/
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_SYSSC_AO_H__
#define __HI_SYSSC_AO_H__

/*
 * Project: hi
 * Module : syssc_ao
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    syssc_ao �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_SC_CTRL0_OFFSET                                (0x400) /* Remap���ƼĴ����� */
#define    HI_SC_CTRL1_OFFSET                                (0x404) /* PMU����/EFUSE JTAGλ�Ĵ����� */
#define    HI_SC_CTRL2_OFFSET                                (0x408) /* ���Ź����üĴ����� */
#define    HI_SC_CTRL3_OFFSET                                (0x40C) /* �������üĴ����� */
#define    HI_SC_CTRL4_OFFSET                                (0x410) /* CICOM�ӽ���ģʽ���üĴ����� */
#define    HI_SC_CTRL5_OFFSET                                (0x414) /* App A9������ַ���üĴ����� */
#define    HI_SC_CTRL6_OFFSET                                (0x418) /* Mod A9������ַ���üĴ����� */
#define    HI_SC_CTRL7_OFFSET                                (0x41C) /* a9 ��������ַ���� */
#define    HI_SC_CTRL8_OFFSET                                (0x420) /* HIFI2������ַ���üĴ����� */
#define    HI_SC_CTRL9_OFFSET                                (0x424) /* dsp0������ַ���üĴ����� */
#define    HI_SC_CTRL10_OFFSET                               (0x428) /* App A9���üĴ����� */
#define    HI_SC_CTRL11_OFFSET                               (0x42C) /* Modem A9���üĴ����� */
#define    HI_SC_CTRL12_OFFSET                               (0x430) /* HIFI2 DSP CORE ���üĴ����� */
#define    HI_SC_CTRL13_OFFSET                               (0x434) /* dsp0 DSP CORE ���üĴ����� */
#define    HI_SC_CTRL14_OFFSET                               (0x438) /* �����Ĵ����� */
#define    HI_SC_CTRL15_OFFSET                               (0x43C) /* M3���üĴ���0�� */
#define    HI_SC_CTRL16_OFFSET                               (0x440) /* M3���üĴ���1�� */
#define    HI_SC_CTRL17_OFFSET                               (0x444) /* HPM���ƼĴ����� */
#define    HI_SC_CTRL18_OFFSET                               (0x448) /* coresight event�Ĵ����� */
#define    HI_SC_CTRL19_OFFSET                               (0x44C) /* �����Ĵ����� */
#define    HI_SC_CTRL20_OFFSET                               (0x450) /* �����Զ��ſ�ʱ�ӿ��ƼĴ���0�� */
#define    HI_SC_CTRL21_OFFSET                               (0x454) /* �����Զ��ſ�ʱ�ӿ��ƼĴ���1�� */
#define    HI_SC_CTRL22_OFFSET                               (0x458) /* memory ʱ�����üĴ���0�� */
#define    HI_SC_CTRL23_OFFSET                               (0x45C) /* memory ʱ�����üĴ���1�� */
#define    HI_SC_CTRL24_OFFSET                               (0x460) /* memory ʱ�����üĴ���2�� */
#define    HI_SC_CTRL25_OFFSET                               (0x464) /* SOC �����ź�ѡ��Ĵ��� */
#define    HI_SC_CTRL26_OFFSET                               (0x468) /* SOC �����ź�bypass�Ĵ����� */
#define    HI_SC_CTRL27_OFFSET                               (0x46C) /* Coresight Debug���üĴ����� */
#define    HI_SC_CTRL28_OFFSET                               (0x470) /* ��ַ�����׵�ַ�� */
#define    HI_SC_CTRL29_OFFSET                               (0x474) /* ��ַ����β��ַ�� */
#define    HI_SC_CTRL30_OFFSET                               (0x478) /* SCI���üĴ����� */
#define    HI_SC_CTRL31_OFFSET                               (0x47C) /* �����Ĵ����� */
#define    HI_SC_CTRL32_OFFSET                               (0x480) /* EBI���ƼĴ����� */
#define    HI_SC_CTRL33_OFFSET                               (0x484) /* dram_test����ģʽ�Ĵ����� */
#define    HI_SC_CTRL34_OFFSET                               (0x488) /* HSICPHY/HSIC���������üĴ����� */
#define    HI_SC_CTRL35_OFFSET                               (0x48C) /* HSICPHY���Կ��ƼĴ����� */
#define    HI_SC_CTRL36_OFFSET                               (0x490) /* USBPHY���ƼĴ���0�� */
#define    HI_SC_CTRL37_OFFSET                               (0x494) /* USBPHY���ƼĴ���1�� */
#define    HI_SC_CTRL38_OFFSET                               (0x498) /* USBPHY���ƼĴ���2�� */
#define    HI_SC_CTRL39_OFFSET                               (0x49C) /* USBPHY���ƼĴ���3�� */
#define    HI_SC_CTRL40_OFFSET                               (0x4A0) /* USBPHY���ƼĴ���4�� */
#define    HI_SC_CTRL41_OFFSET                               (0x4A4) /* USB Controller ���ƼĴ���0 */
#define    HI_SC_CTRL42_OFFSET                               (0x4A8) /* USB Controller ���ƼĴ���1 */
#define    HI_SC_CTRL43_OFFSET                               (0x4AC) /* USB Controller ���ƼĴ���2 */
#define    HI_SC_CTRL44_OFFSET                               (0x4B0) /* SSIC PHY���ƼĴ����� */
#define    HI_SC_CTRL45_OFFSET                               (0x4B4) /* uicc���жϺϲ����ƼĴ����� */
#define    HI_SC_CTRL46_OFFSET                               (0x4B8) /* �жϺϲ���ʱ�Ĵ���0�� */
#define    HI_SC_CTRL47_OFFSET                               (0x4BC) /* �жϺϲ���ʱ�Ĵ���1�� */
#define    HI_SC_CTRL48_OFFSET                               (0x4C0) /* CPU���ж���λ�Ĵ����� */
#define    HI_SC_CTRL49_OFFSET                               (0x4C4) /* CPU���ж�����Ĵ����� */
#define    HI_SC_CTRL50_OFFSET                               (0x4C8) /* CPU���ж�״̬�Ĵ����� */
#define    HI_SC_CTRL51_OFFSET                               (0x4CC) /* M3���������жϼĴ����� */
#define    HI_SC_CTRL52_OFFSET                               (0x4D0) /* dsp0���������жϼĴ����� */
#define    HI_SC_CTRL53_OFFSET                               (0x4D4) /* HIFI DSP���������жϼĴ����� */
#define    HI_SC_CTRL54_OFFSET                               (0x4D8) /* DMAѡ����ƼĴ����� */
#define    HI_SC_CTRL55_OFFSET                               (0x4DC) /* memory�͹������üĴ���0�� */
#define    HI_SC_CTRL56_OFFSET                               (0x4E0) /* BBP LBUS���ƼĴ����� */
#define    HI_SC_CTRL57_OFFSET                               (0x4E4) /* BBP�������ƼĴ����� */
#define    HI_SC_CTRL68_OFFSET                               (0x510) /* memory�͹������üĴ���2�� */
#define    HI_SC_CTRL69_OFFSET                               (0x514) /* ϵͳ�����ַ���ʹ��ܼĴ����� */
#define    HI_SC_CTRL70_OFFSET                               (0x518) /* �������ȼ����üĴ���0�� */
#define    HI_SC_CTRL71_OFFSET                               (0x51C) /* �������ȼ����üĴ���1�� */
#define    HI_SC_CTRL72_OFFSET                               (0x520) /* �������ȼ����üĴ���2�� */
#define    HI_SC_CTRL81_OFFSET                               (0x544) /* appa9 gpio0�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL85_OFFSET                               (0x554) /* mdma9 gpio0�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL98_OFFSET                               (0x588) /* M3 GPIO0�ж�ʹ�ܼĴ����� */
#define    HI_SC_CTRL103_OFFSET                              (0x59C) /* slave active���μĴ���0�� */
#define    HI_SC_CTRL104_OFFSET                              (0x5A0) /* slave active���μĴ���1�� */
#define    HI_SC_CTRL105_OFFSET                              (0x5A4) /* slave active���μĴ���2�� */
#define    HI_SC_CTRL121_OFFSET                              (0x5E4) /* �����Ĵ����� */
#define    HI_SC_CTRL122_OFFSET                              (0x5E8) /* �����Ĵ����� */
#define    HI_SC_CTRL123_OFFSET                              (0x5EC) /* �����Ĵ����� */
#define    HI_SC_CTRL124_OFFSET                              (0x5F0) /* �����Ĵ����� */
#define    HI_SC_CTRL125_OFFSET                              (0x5F4) /* �����Ĵ����� */
#define    HI_SC_CTRL126_OFFSET                              (0x5F8) /* �����Ĵ����� */
#define    HI_SC_CTRL127_OFFSET                              (0x5FC) /* �����Ĵ����� */
#define    HI_SC_STAT0_OFFSET                                (0x600) /* ��λ��¼/����/����ģʽ״̬�Ĵ����� */
#define    HI_SC_STAT1_OFFSET                                (0x604) /* App/Modem A9״̬�Ĵ����� */
#define    HI_SC_STAT2_OFFSET                                (0x608) /* HIFI/dsp0/BBE16 DSP CORE״̬�Ĵ����� */
#define    HI_SC_STAT3_OFFSET                                (0x60C) /* hmp״̬�Ĵ���0�� */
#define    HI_SC_STAT4_OFFSET                                (0x610) /* hmp״̬�Ĵ���1�� */
#define    HI_SC_STAT5_OFFSET                                (0x614) /* �����Ĵ��� */
#define    HI_SC_STAT6_OFFSET                                (0x618) /* App/Modem A9У��״̬�Ĵ����� */
#define    HI_SC_STAT7_OFFSET                                (0x61C) /* �����Ĵ����� */
#define    HI_SC_STAT8_OFFSET                                (0x620) /* LTE BBP��ά�ɲ���������� */
#define    HI_SC_STAT9_OFFSET                                (0x624) /* AXI������״̬�Ĵ���0�� */
#define    HI_SC_STAT10_OFFSET                               (0x628) /* AXI������״̬�Ĵ���1�� */
#define    HI_SC_STAT11_OFFSET                               (0x62C) /* SDCC����״̬�Ĵ��� */
#define    HI_SC_STAT12_OFFSET                               (0x630) /* SDCC�����仯�ж�״̬�Ĵ��� */
#define    HI_SC_STAT13_OFFSET                               (0x634) /* �����Ĵ��� */
#define    HI_SC_STAT14_OFFSET                               (0x638) /* usb3PHY״̬�Ĵ���1�� */
#define    HI_SC_STAT15_OFFSET                               (0x63C) /* slave active״̬�Ĵ����� */
#define    HI_SC_STAT16_OFFSET                               (0x640) /* lte drx abs_timer״̬�Ĵ���0 */
#define    HI_SC_STAT17_OFFSET                               (0x644) /* lte drx abs_timer״̬�Ĵ���1 */
#define    HI_SC_STAT18_OFFSET                               (0x648) /* gsm deepsleep״̬�Ĵ��� */
#define    HI_SC_STAT19_OFFSET                               (0x64C) /* �����Ĵ����� */
#define    HI_SC_STAT20_OFFSET                               (0x650) /* �����Ĵ����� */
#define    HI_SC_STAT21_OFFSET                               (0x654) /* usb_pd״̬�Ĵ����� */
#define    HI_SC_STAT22_OFFSET                               (0x658) /* AXI������״̬�Ĵ���2�� */
#define    HI_SC_STAT23_OFFSET                               (0x65C) /* func mbist fail״̬�Ĵ����� */
#define    HI_SC_STAT24_OFFSET                               (0x660) /* func mbist done״̬�Ĵ���0�� */
#define    HI_SC_STAT25_OFFSET                               (0x664) /* func mbist done״̬�Ĵ���1�� */
#define    HI_SC_STAT26_OFFSET                               (0x668) /* master״̬�Ĵ����� */
#define    HI_SC_STAT27_OFFSET                               (0x66C) /* slave active״̬�Ĵ���0�� */
#define    HI_SC_STAT28_OFFSET                               (0x670) /* slave active״̬�Ĵ���1�� */
#define    HI_SC_STAT29_OFFSET                               (0x674) /* slave active״̬�Ĵ���2�� */
#define    HI_SC_STAT31_OFFSET                               (0x67C) /* bbp_sys_1control״̬�Ĵ���1�� */
#define    HI_SC_STAT32_OFFSET                               (0x680) /* bbp����״̬�Ĵ����� */
#define    HI_SC_STAT33_OFFSET                               (0x684) /* �����Ĵ��� */
#define    HI_SC_STAT34_OFFSET                               (0x688) /* �����Ĵ��� */
#define    HI_SC_STAT35_OFFSET                               (0x68C) /* func mbist done״̬�Ĵ���2�� */
#define    HI_SC_STAT36_OFFSET                               (0x690) /* func mbist done״̬�Ĵ���3�� */
#define    HI_SC_STAT37_OFFSET                               (0x694) /* func mbist done״̬�Ĵ���4�� */
#define    HI_SC_STAT38_OFFSET                               (0x698) /* func mbist done״̬�Ĵ���5�� */
#define    HI_SC_STAT39_OFFSET                               (0x69C) /* func mbist done״̬�Ĵ���6�� */
#define    HI_SC_STAT40_OFFSET                               (0x6A0) /* func mbist done״̬�Ĵ���7�� */
#define    HI_SC_STAT41_OFFSET                               (0x6A4) /* master���ʴ���״̬�Ĵ���0�� */
#define    HI_SC_STAT42_OFFSET                               (0x6A8) /* master���ʴ���״̬�Ĵ���1�� */
#define    HI_SC_STAT43_OFFSET                               (0x6AC) /* ahb������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT44_OFFSET                               (0x6B0) /* soc���������apb������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT45_OFFSET                               (0x6B4) /* soc���賣����apb������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT46_OFFSET                               (0x6B8) /* glb��m1�ڣ�dw_axi_bbphy��д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT47_OFFSET                               (0x6BC) /* glb��m1�ڣ�dw_axi_bbphy�������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT48_OFFSET                               (0x6C0) /* glb��m2�ڣ�dw_axi_mst��д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT49_OFFSET                               (0x6C4) /* glb��m2�ڣ�dw_axi_mst�������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT50_OFFSET                               (0x6C8) /* glb��m3�ڣ�app a9 m0�ڣ�д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT51_OFFSET                               (0x6CC) /* glb��m3�ڣ�app a9 m0�ڣ������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT52_OFFSET                               (0x6D0) /* glb��m4�ڣ�mdm a9 m0�ڣ�д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT53_OFFSET                               (0x6D4) /* glb��m4�ڣ�mdm a9 m0�ڣ������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT54_OFFSET                               (0x6D8) /* glb��m5�ڣ�reserved��д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT55_OFFSET                               (0x6DC) /* glb��m5�ڣ�reserved�������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT56_OFFSET                               (0x6E0) /* glb��m6�ڣ�hifi��д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT57_OFFSET                               (0x6E4) /* glb��m6�ڣ�hifi�������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT58_OFFSET                               (0x6E8) /* cpu��m1�ڣ�app a9 m1�ڣ������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT59_OFFSET                               (0x6EC) /* cpu��m2�ڣ�mdm a9 m1�ڣ������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT60_OFFSET                               (0x6F0) /* cpu��m1�ڣ�app a9 m1�ڣ�д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT61_OFFSET                               (0x6F4) /* cpu��m2�ڣ�mdm a9 m1�ڣ�д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT62_OFFSET                               (0x6F8) /* bbphy��m1�ڣ�dw_axi_glb��д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT63_OFFSET                               (0x6FC) /* bbphy��m1�ڣ�dw_axi_glb�������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT64_OFFSET                               (0x700) /* bbphy��m2�ڣ�dsp0��д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT65_OFFSET                               (0x704) /* bbphy��m2�ڣ�dsp0�������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT66_OFFSET                               (0x708) /* bbphy��m3�ڣ�bbp��д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT67_OFFSET                               (0x70C) /* bbphy��m3�ڣ�bbp�������ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT68_OFFSET                               (0x710) /* axi_amon��m1д���ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT69_OFFSET                               (0x714) /* axi_amon��m1�����ʴ����ַ�Ĵ����� */
#define    HI_SC_STAT70_OFFSET                               (0x718) /* PCIE ������״̬�Ĵ���0 */
#define    HI_SC_STAT71_OFFSET                               (0x71C) /* PCIE ������״̬�Ĵ���1 */
#define    HI_SC_STAT72_OFFSET                               (0x720) /* PCIE ������״̬�Ĵ���2 */
#define    HI_SC_STAT73_OFFSET                               (0x724) /* PCIE ������״̬�Ĵ���3 */
#define    HI_SC_STAT74_OFFSET                               (0x728) /* PCIE ������״̬�Ĵ���4 */
#define    HI_SC_STAT75_OFFSET                               (0x72C) /* PCIE PHY״̬�Ĵ��� */
#define    HI_SC_STAT76_OFFSET                               (0x730) /* PCIE ������״̬�Ĵ���5 */
#define    HI_SC_STAT77_OFFSET                               (0x734) /* PCIE ������״̬�Ĵ���6 */
#define    HI_SC_STAT78_OFFSET                               (0x738) /* PCIE ������״̬�Ĵ���7 */
#define    HI_SC_STAT79_OFFSET                               (0x73C) /* PCIE ������״̬�Ĵ���8 */
#define    HI_SC_STAT80_OFFSET                               (0x740) /* m3״̬�Ĵ���0�� */
#define    HI_SC_STAT81_OFFSET                               (0x744) /* m3״̬�Ĵ���1�� */
#define    HI_SC_STAT82_OFFSET                               (0x748) /* m3״̬�Ĵ���2�� */
#define    HI_SC_STAT83_OFFSET                               (0x74C) /* m3״̬�Ĵ���3�� */
#define    HI_SC_STAT84_OFFSET                               (0x750) /* m3״̬�Ĵ���4�� */
#define    HI_SC_STAT85_OFFSET                               (0x754) /* m3״̬�Ĵ���5�� */
#define    HI_SC_STAT86_OFFSET                               (0x758) /* tsensor trim�Ĵ��� */
#define    HI_SC_STAT87_OFFSET                               (0x75C) /* PCIE ������״̬�Ĵ���9 */
#define    HI_VERSION_ID_OFFSET                              (0xF00) /* оƬ�汾�Ĵ����� */


#ifndef __ASSEMBLY__

/********************************************************************************/
/*    syssc_ao �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    remap_clear                : 1; /* [0..0] ����FlashƬѡ1��ROM��Ӧ�ľ�̬Boot Memory��ַ��ӳ���������0��������ӳ��״̬����Ĭ��ֵ��1�������ӳ�䡣 */
        unsigned int    m3_remap_clear             : 1; /* [1..1] M3��ַ��ӳ����� */
        unsigned int    reserved_1                 : 2; /* [3..2] ������ */
        unsigned int    remap_stat                 : 1; /* [4..4] remap״ָ̬ʾ��0��remap_clear��Ч��1��remap_clear��Ч��Ĭ��ֵ���� */
        unsigned int    cm3_remap_stat             : 1; /* [5..5] cm3_remap״ָ̬ʾ��0��cm3_remap_clear��Ч��1��cm3_remap_clear��Ч��Ĭ��ֵ���� */
        unsigned int    reserved_0                 : 26; /* [31..6] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL0_T;    /* Remap���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    pmu_rstout_n               : 1; /* [0..0] PMU��λ��������źš�0����λ��1������λ��Ĭ��ֵ�����ÿ���λ�뿴�Ź���λ�ź����룬��һ��Ч����λPMU�� */
        unsigned int    pmu_hold                   : 1; /* [1..1] �ⲿPMU״̬�����źš�0��PMU�µ磨Ĭ��ֵ����1��PMU������ */
        unsigned int    pmu_irq_mask               : 1; /* [2..2] PMU�ж�����0�������Σ�1�����Ρ� */
        unsigned int    pmu_irq_n_pos_sel          : 1; /* [3..3] �ⲿPMU�жϼ������á�0������Ϊ�ͣ�Ĭ��ֵ����1������Ϊ�ߡ� */
        unsigned int    efuse_sys_ctrl_en          : 1; /* [4..4] efuse����JTAG���ʿ��Ʊ�����0��ǿ���������JTAG��1������efuse��дֵȷ��JTAG�Ƿ�������ʡ���Ĭ��ֵ�� */
        unsigned int    wdt_reset_sel              : 1; /* [5..5] watchdog��λʱ����λPMU����ֻ��λоƬ��0����λPMU��1��ֻ��λоƬ�� */
        unsigned int    reserved_1                 : 2; /* [7..6] ������ */
        unsigned int    usbphy_tcxo_buff_ctrl      : 6; /* [13..8] usbphy tcxo buffer����.             [5]��ѡ�����/pwrctrl����         0��usbphy tcxo buffer ʹ����pwrctrl����                        1����usbphy_tcxo_buff_ctrl[2]����[4]��pwrctrl����ʱ��ѡ�� ch0_tcxoen/ch1_tcxoen��Ϊen���ƣ�                        0=��ѡ��ch0_tcxoen                  1=��ѡ��ch1_tcxoen[3]��reserved��[2]�����ʹ��usbphy tcxo buffer���ƣ�                                0����ֹ                              1��ʹ��[1:0]��in_dr */
        unsigned int    reserved_0                 : 18; /* [31..14] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL1_T;    /* PMU����/EFUSE JTAGλ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    wdt_clk_en                 : 1; /* [0..0] ���Ź�ʱ��ʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܣ�Ĭ��ֵ����ע�⣺�Ը�λ����д0����ʱ����Ҫ�Ƚ��üĴ�����16λֵдΪ0x6920������wdt_en_ctrlλдΪ0x6920���򿪱�����Ȼ���ٶԴ˱���д��ֵ�ſ�����Ч������������� */
        unsigned int    reserved_1                 : 2; /* [2..1] ���������ݿ�д�룩�� */
        unsigned int    wdt_en_ov                  : 1; /* [3..3] WDTʱ��ǿ��ʹ�ܿ���λ��0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ���wdt_en_ovʹ��ʱ�����Ź�������ʱ�ӣ�pclk��������������32Kʱ�Ӽ�������λһ������£�����Ҫʹ�ã�һֱ����Ϊ0�� */
        unsigned int    reserved_0                 : 12; /* [15..4] ���������ݿ�д�룩�� */
        unsigned int    wdt_en_ctrl                : 16; /* [31..16] wdt_enдʹ�ܿ��ơ��ÿ���λ��Ϊ�˷�ֹ�����������Ź��������ı����߼������Ź�ʱ��ʹ�ܿ���ֻ���ڸ�λ����Ϊ6920�󣬲ſɸ��ġ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL2_T;    /* ���Ź����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    lcd_rst_n                  : 1; /* [0..0] LCD��λ����λ��0����λ��Ĭ��ֵ����1������λ�� */
        unsigned int    emi_sel                    : 1; /* [1..1] LCD�ӿ�ʱ��ѡ��0��Intel 8080��Ĭ��ֵ����1��Motorola�� */
        unsigned int    zsi_en                     : 1; /* [2..2]  */
        unsigned int    sio_master_mode            : 1; /* [3..3] sio ģʽѡ��0��slaveģʽ��Ĭ��ֵ����1��masterģʽ�� */
        unsigned int    mmc0_sample_tuning_enable  : 1; /* [4..4] MMC0 �ӿ�ʱ���Ż�ʱ�ܡ�0����ʹ��ʱ���Ż�1��ʹ��ʱ���Ż� */
        unsigned int    mmc1_sample_tuning_enable  : 1; /* [5..5] MMC1 �ӿ�ʱ���Ż�ʱ�ܡ�0����ʹ��ʱ���Ż�1��ʹ��ʱ���Ż� */
        unsigned int    mmc_msc                    : 1; /* [6..6] MMC IO��ѹ���ơ�0��1.8v��1��3.3v�� */
        unsigned int    ssp0_mode                  : 1; /* [7..7] ssp0ģʽ���ơ�0������ģʽ��1������ģʽ�� */
        unsigned int    ssp1_mode                  : 1; /* [8..8] ssp1ģʽ���ơ�0������ģʽ��1������ģʽ�� */
        unsigned int    amon_cpufast_monitor_start : 1; /* [9..9] ���Cpu_fast AXI����axi monitor����ֹͣ�źš�0��ֹͣ��1�������� */
        unsigned int    amon_soc_monitor_start     : 1; /* [10..10] ���Global AXI����axi monitor����ֹͣ�źš�0��ֹͣ��1�������� */
        unsigned int    pmussi0_mst_cnt            : 3; /* [13..11] pmussi0������ʱ���� */
        unsigned int    reserved_2                 : 1; /* [14..14] ������ */
        unsigned int    dsp0_uart_en               : 5; /* [19..15] LTEDSP UARTѡ��[4]��uart3[3]��uart2��Ĭ��ֵ��[2]��uart1[1]��uart0[0]��hs uartÿ����ֵΪ1��ʾʹ�ö�Ӧuart��0��ʾ��ʹ�� */
        unsigned int    hifi_uart_en               : 4; /* [23..20] VDSP UARTѡ��[3]��uart3��Ĭ��ֵ��[2]��uart2[1]��uart1[0]��uart0ÿ����ֵΪ1��ʾʹ�ö�Ӧuartx��0��ʾ��ʹ�� */
        unsigned int    reserved_1                 : 4; /* [27..24] ������ */
        unsigned int    reserved_0                 : 3; /* [30..28] ���� */
        unsigned int    test_clk_en                : 1; /* [31..31] ����ʱ��ʹ���źţ������ſظ�Ƶʱ�ӵķ�Ƶ��·��0����ʹ�ܣ���Ĭ��ֵ��1��ʹ�ܡ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL3_T;    /* �������üĴ����� */

typedef union
{
    struct
    {
        unsigned int    cicom0_sel_mod             : 1; /* [0..0] ģʽѡ��λ��0��WCDMA�ӽ���ģʽ��Ĭ��ֵ����1��GSM�ӽ���ģʽ�� */
        unsigned int    cicom1_sel_mod             : 1; /* [1..1] ģʽѡ��λ��0��WCDMA�ӽ���ģʽ��Ĭ��ֵ����1��GSM�ӽ���ģʽ�� */
        unsigned int    reserved                   : 30; /* [31..2] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL4_T;    /* CICOM�ӽ���ģʽ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 13; /* [12..0] ������ */
        unsigned int    sw_appa9_boot_addr         : 19; /* [31..13] App A9������ַ����ַ�ռ��С64/32/16KB/8KB���õ�ַ��Ҫ64/32/16KB/8KB���룬������SCTRL7���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL5_T;    /* App A9������ַ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 13; /* [12..0] ������ */
        unsigned int    sw_modema9_boot_addr       : 19; /* [31..13] Modem A9������ַ����ַ�ռ��С64/32/16KB/8KB���õ�ַ��Ҫ64/32/16KB/8KB���룬������SCTRL7���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL6_T;    /* Mod A9������ַ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    appa9_remap_size           : 2; /* [1..0] appa9��������ַ���ơ�00����ַ�ռ��С64KB���õ�ַ��Ҫ64KB���룻01����ַ�ռ��С32KB���õ�ַ��Ҫ32KB���룻10����ַ�ռ��С16KB���õ�ַ��Ҫ16KB���룻11����ַ�ռ��С8KB���õ�ַ��Ҫ8KB���룻 */
        unsigned int    mdma9_remap_size           : 2; /* [3..2] mdm9��������ַ���ơ�00����ַ�ռ��С64KB���õ�ַ��Ҫ64KB���룻01����ַ�ռ��С32KB���õ�ַ��Ҫ32KB���룻10����ַ�ռ��С16KB���õ�ַ��Ҫ16KB���룻11����ַ�ռ��С8KB���õ�ַ��Ҫ8KB���룻 */
        unsigned int    reserved                   : 28; /* [31..4] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL7_T;    /* a9 ��������ַ���� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 16; /* [15..0] ������ */
        unsigned int    sw_hifi_boot_addr          : 16; /* [31..16] HIFI������ַ���á���ַ�ռ��С64KB���õ�ַ��Ҫ64KB���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL8_T;    /* HIFI2������ַ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 16; /* [15..0] ������ */
        unsigned int    sw_dsp0_boot_addr          : 16; /* [31..16] dsp0��������ַ���á���ַ�ռ��С64KB���õ�ַ��Ҫ64KB���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL9_T;    /* dsp0������ַ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_3                 : 1; /* [0..0] ������ */
        unsigned int    appa9_cfgnmfi              : 1; /* [1..1] �����жϲ������ο���λ��0�������1�����ã�Ĭ��ֵ����ֻ��CPU resetʱ�������� */
        unsigned int    appa9_cfgsdisable          : 1; /* [2..2] ������������Ҫ���üĴ���д������0����ʹ�ܣ�1��ʹ�ܡ��ñ���ʹ�ܺ���Է�ֹdistributor��A9�������ӿڡ�LSPIs�Ĳ��ּĴ������޸ġ������Ҫʹ�ô˹��ܣ�ARM�����û���boot�׶�������������ؼĴ�����ʹ�ܸù��ܡ������ϣ�ϵͳֻ����Ӳ��λʱ��Ҫ�رոñ������ܡ� */
        unsigned int    appa9_cp15sdisable         : 1; /* [3..3] secure registerд������0����ʹ�ܣ�1��ʹ�ܡ�reset 0�� then 1 by software������CPU�ڲ��Ĵ������ã���ϵͳ�Ĵ����߼�������ֵֻ�ɸı�һ�Ρ� */
        unsigned int    appa9_pwrctli0             : 2; /* [5..4] CPU0״̬�Ĵ���[1:0]��λֵ�����޵�Դ���������0�� */
        unsigned int    appa9_spiden               : 1; /* [6..6] secure privilege invasive Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    appa9_spniden              : 1; /* [7..7] secure privilege Non-invasive Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    appa9_niden                : 1; /* [8..8] Non-invasive Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    appa9_dbgen                : 1; /* [9..9] Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    appa9_eventi_cfg           : 2; /* [11..10] APPA9ѡͨmdma9_evento��cm3_evento���ơ�[10]:ѡͨmdma9_evento���ƣ�����Ч��[11]:ѡͨcm3_evento���ƣ�����Ч�� */
        unsigned int    reserved_2                 : 2; /* [13..12] ������ */
        unsigned int    appa9_l2_spniden           : 1; /* [14..14]  */
        unsigned int    reserved_1                 : 1; /* [15..15] ������ */
        unsigned int    appa9_l2_waysize           : 3; /* [18..16] appa9 L2 cache way size��000��reserved001��16KB010��32KBothers��reserved */
        unsigned int    reserved_0                 : 1; /* [19..19] ������ */
        unsigned int    appa9_l2_regfilebase       : 12; /* [31..20] appa9 L2 cache �Ĵ�������ַ�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL10_T;    /* App A9���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_3                 : 1; /* [0..0] ������ */
        unsigned int    moda9_cfgnmfi              : 1; /* [1..1] �����жϲ������ο���λ��0�������1�����ã�Ĭ��ֵ����ֻ��CPU resetʱ�������� */
        unsigned int    moda9_cfgsdisable          : 1; /* [2..2] ������������Ҫ���üĴ���д������0����ʹ�ܣ�1��ʹ�ܡ��ñ���ʹ�ܺ���Է�ֹdistributor��A9�������ӿڡ�LSPIs�Ĳ��ּĴ������޸ġ������Ҫʹ�ô˹��ܣ�ARM�����û���boot�׶�������������ؼĴ�����ʹ�ܸù��ܡ������ϣ�ϵͳֻ����Ӳ��λʱ��Ҫ�رոñ������ܡ� */
        unsigned int    moda9_cp15sdisable         : 1; /* [3..3] secure registerд������0����ʹ�ܣ�1��ʹ�ܡ�reset 0�� then 1 by software������CPU�ڲ��Ĵ������ã���ϵͳ�Ĵ����߼�������ֵֻ�ɸı�һ�Ρ� */
        unsigned int    moda9_pwrctli0             : 2; /* [5..4] CPU0״̬�Ĵ���[1:0]��λֵ�����޵�Դ���������0�� */
        unsigned int    moda9_spiden               : 1; /* [6..6] secure privilege invasive Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    moda9_spniden              : 1; /* [7..7] secure privilege Non-invasive Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    moda9_niden                : 1; /* [8..8] Non-invasive Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    moda9_dbgen                : 1; /* [9..9] Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    moda9_eventi_cfg           : 2; /* [11..10] MDMA9ѡͨAPPA9_evento��cm3_evento���ơ�[10]:ѡͨAPPA9_evento���ƣ�����Ч��[11]:ѡͨcm3_evento���ƣ�����Ч�� */
        unsigned int    reserved_2                 : 2; /* [13..12]  */
        unsigned int    moda9_l2_spniden           : 1; /* [14..14]  */
        unsigned int    reserved_1                 : 1; /* [15..15] ������ */
        unsigned int    moda9_l2_waysize           : 3; /* [18..16] moda9 L2 cache way size��000��reserved001��16KB010��32KBothers��reserved */
        unsigned int    reserved_0                 : 1; /* [19..19] ������ */
        unsigned int    moda9_l2_regfilebase       : 12; /* [31..20] moda9 L2 cache �Ĵ�������ַ�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL11_T;    /* Modem A9���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    hifi_ocdhaltonreset        : 1; /* [0..0] �ڽ⸴λʱǿ�н���OCDHaltģʽ��0������ģʽ��Ĭ��ֵ����1��OCDHaltģʽ����bit�ڽ⸴λǰ6�����ڼ���10�����ڲ����޸ġ��ڽ⸴λ��ɺ󣬸ı��bitû��Ӱ�졣 */
        unsigned int    hifi_runstall              : 1; /* [1..1] ����/ֹͣ��0�����У�1��ֹͣ����Ĭ��ֵ�� */
        unsigned int    hifi_statvectorsel         : 1; /* [2..2] ������ַѡ��0���ڲ�TCM������Ĭ��ֵ��1���ⲿ������������ַ���ⲿ������ַ�Ĵ������� */
        unsigned int    hifi_breaksync_en          : 3; /* [5..3]  */
        unsigned int    hifi_crosstrig_en          : 3; /* [8..6]  */
        unsigned int    reserved_1                 : 1; /* [9..9] ������ */
        unsigned int    reserved_0                 : 22; /* [31..10] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL12_T;    /* HIFI2 DSP CORE ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 16; /* [15..0] ������ */
        unsigned int    dsp0_ocdhaltonreset        : 1; /* [16..16] dsp0�ڽ⸴λʱǿ�н���OCDHaltģʽ��0������ģʽ��Ĭ��ֵ����1��OCDHaltģʽ����bit�ڽ⸴λǰ6�����ڼ���10�����ڲ����޸ġ��ڽ⸴λ��ɺ󣬸ı��bitû��Ӱ�졣 */
        unsigned int    dsp0_runstall              : 1; /* [17..17] dsp0����/ֹͣ��0�����У�1��ֹͣ����Ĭ��ֵ�� */
        unsigned int    dsp0_statvectorsel         : 1; /* [18..18] dsp0������ַѡ��0���ڲ�TCM������Ĭ��ֵ��1���ⲿ������������ַ���ⲿ������ַ�Ĵ������� */
        unsigned int    dsp0_breaksync_en          : 3; /* [21..19]  */
        unsigned int    dsp0_crosstrig_en          : 3; /* [24..22]  */
        unsigned int    reserved_0                 : 7; /* [31..25] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL13_T;    /* dsp0 DSP CORE ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL14_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cm3_fix_mst_type           : 1; /* [0..0] 0��ahb-ap hmasterֵ���ڲ�MasterType�Ĵ���������1��ahb-ap hmasterֵ�̶�Ϊ1 */
        unsigned int    cm3_dap_en                 : 1; /* [1..1] dapʱ��ʹ�� */
        unsigned int    cm3_ts_clk_chg             : 1; /* [2..2] timestampʱ�Ӹı�ָʾ */
        unsigned int    cm3_mpu_disable            : 1; /* [3..3] 1��disable mcu */
        unsigned int    cm3_dbgen                  : 1; /* [4..4] debugʹ�� */
        unsigned int    cm3_eventi_cfg             : 3; /* [7..5] eventiԴѡ��Bit[12]��ѡͨappa9_eventoBit[11]��ѡͨmdma9_eventoBit[10]��ѡͨa15_evento */
        unsigned int    reserved                   : 24; /* [31..8] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL15_T;    /* M3���üĴ���0�� */

typedef union
{
    struct
    {
        unsigned int    cm3_stcalib                : 26; /* [25..0] [25]��cm3 timer �Ƿ����ⲿ�ο�ʱ��STCLK��0��û���ⲿ�ο�ʱ�ӣ�1�����ⲿ�ο�ʱ�ӣ�[24]���ο�ʱ��Ƶ���Ƿ�10ms�ı�����0���ο�ʱ��Ƶ����10ms�ı�����1���ο�ʱ��Ƶ�ʲ���10ms�ı�����[23:0]��timer�ο�ʱ�������10ms(100Hz)��ʱ������ֵ�� */
        unsigned int    reserved                   : 6; /* [31..26] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL16_T;    /* M3���üĴ���1�� */

typedef union
{
    struct
    {
        unsigned int    hpm0_clk_div               : 6; /* [5..0] hpm0��Ƶϵ���� */
        unsigned int    reserved_3                 : 1; /* [6..6] ������ */
        unsigned int    hpm0_en                    : 1; /* [7..7] hpm0ʹ�ܿ��ơ� 0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    hpm1_clk_div               : 6; /* [13..8] hpm1��Ƶϵ���� */
        unsigned int    reserved_2                 : 1; /* [14..14] ������ */
        unsigned int    hpm1_en                    : 1; /* [15..15] hpm1ʹ�ܿ��ơ� 0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    hpm2_clk_div               : 6; /* [21..16] hpm2��Ƶϵ���� */
        unsigned int    reserved_1                 : 1; /* [22..22] ������ */
        unsigned int    hpm2_en                    : 1; /* [23..23] hpm2ʹ�ܿ��ơ� 0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    reserved_0                 : 8; /* [31..24] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL17_T;    /* HPM���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    cs_event_hwe               : 32; /* [31..0] �ⲿ�¼����͸�coresight HWEVENT�ڡ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL18_T;    /* coresight event�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL19_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    axi_mem_ret_gatedclock_en  : 1; /* [0..0] axi_mem�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    cicom0_auto_clk_gate_en    : 1; /* [1..1] cicom0�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    cicom0_soft_gate_clk_en    : 1; /* [2..2] cicom0ʱ���ſؿ���(���Զ��ſ�ʹ��Ϊ0ʱ��Ч)��0�����ضϣ�Ĭ��ֵ����1���ض�ʱ�ӡ� */
        unsigned int    cicom1_auto_clk_gate_en    : 1; /* [3..3] cicom1�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    cicom1_soft_gate_clk_en    : 1; /* [4..4] cicom1ʱ���ſؿ���(���Զ��ſ�ʹ��Ϊ0ʱ��Ч)��0�����ضϣ�Ĭ��ֵ����1���ض�ʱ�ӡ� */
        unsigned int    hs_uart_gatedclock_en      : 1; /* [5..5] hs_uart�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    uart_gatedclock_en         : 1; /* [6..6] �ǵ�����uart0, ������uart1/2/3�Զ��ſ�ʹ��1��ʹ��0����ʹ�ܣ�Ĭ��ֵ�� */
        unsigned int    sdcc_hclk_wkup_en          : 1; /* [7..7] sdccʱ�ӻ���ʹ�ܣ�sdcc_hclk_soft_en����Ϊ0ʱ��Ч����0������hclkʱ�ӣ�1��ʹ��ʱ�ӻ��ѹ��ܣ�Ĭ��ֵ�����˹���������sdccʹ���Զ�ʱ���ſأ�sdcc_gatedclock_en������ʱ��Ч�� */
        unsigned int    sdcc_hclk_soft_en          : 1; /* [8..8] sdccʱ���ſ�������á�0��ʱ�ӻ��ѣ�ʱ�ӿ���״̬��sdcc_hclk_wkup_en������1������hclkʱ�ӡ���Ĭ��ֵ���˹���������sdccʹ���Զ�ʱ���ſأ�sdcc_gatedclock_en������ʱ��Ч�� */
        unsigned int    dw_ssi_gatedclock_en       : 1; /* [9..9] spi0��spi1�Զ��ſ�ʹ��1��ʹ��0����ʹ�ܣ�Ĭ��ֵ�� */
        unsigned int    usb3_gatedclock_en         : 1; /* [10..10] USB3 controller�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    hdlc_soft_gate_clk_en      : 1; /* [11..11] hdlcʱ���ſؿ��ơ�0���Զ��ſأ�Ĭ��ֵ����1���ض�ʱ�ӡ� */
        unsigned int    reseved                    : 1; /* [12..12] ������ */
        unsigned int    cs_cg_en                   : 1; /* [13..13] CoreSight�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    reserved_1                 : 5; /* [18..14] ������ */
        unsigned int    hsic_gatedclock_en         : 1; /* [19..19] hsic��uicc�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ��˳�Աͬʱ����hsic_gatedclock_en��uicc_gatedclock_en�� */
        unsigned int    hsic_ss_scaledown_mode     : 2; /* [21..20] hsic��uicc������ٿ��ơ�00�����ٹرգ�Ĭ��ֵ����01��ʹ�ܳ�speed enumeration,HNP/SRP,Host mode suspend nad resume֮���timingvalue��10����ʹ��device mode suspend and resume timing value��11��ʹ�ܱ���0��1 scale-down timing values���ۺ�ʱ����Ϊ00���˳�Աͬʱ����hsic_ss_scaledown_mode��uicc_ss_scaledown_mode�� */
        unsigned int    upacc_auto_clk_gate_en     : 1; /* [22..22] upacc�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    upacc_soft_gate_clk_en     : 1; /* [23..23] upaccʱ���ſؿ���(���Զ��ſ�ʹ��Ϊ0ʱ��Ч)��0�����ضϣ�Ĭ��ֵ����1���ض�ʱ�ӡ� */
        unsigned int    reserved_0                 : 3; /* [26..24]  */
        unsigned int    ios_gatedclock_en          : 1; /* [27..27] ioshare�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    ipcm_auto_clk_gate_en      : 1; /* [28..28] ipcm�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    ipcm_soft_gate_clk_en      : 1; /* [29..29] ipcmʱ���ſؿ���(���Զ��ſ�ʹ��Ϊ0ʱ��Ч)��0�����ضϣ�Ĭ��ֵ����1���ض�ʱ�ӡ� */
        unsigned int    hdlc_auto_clk_gate_en      : 1; /* [30..30] hdlc�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    sysctrl_cg_en              : 1; /* [31..31] sysctrl�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL20_T;    /* �����Զ��ſ�ʱ�ӿ��ƼĴ���0�� */

typedef union
{
    struct
    {
        unsigned int    reserved_4                 : 3; /* [2..0] ������ */
        unsigned int    sdcc_gatedclock_en         : 1; /* [3..3] sdcc�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    timer_gatedclock_en        : 1; /* [4..4] timer0-23�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    reserved_3                 : 1; /* [5..5] tsensor�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    reserved_2                 : 1; /* [6..6] ������ */
        unsigned int    mddrc_ddrphy_ac_pdd        : 1; /* [7..7] �̶�Ϊ0��ʵ�ʲ��� */
        unsigned int    ddrc_apb_gt_en             : 1; /* [8..8] mddrc�Ĵ������õ�·ʱ�ӿ���1����ʱ�ӣ�Ĭ��ֵ��0���ر�ʱ�� */
        unsigned int    dw_axi_cpu_cg_en           : 1; /* [9..9] cpu axi�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    dw_axi_glb_cg_en           : 1; /* [10..10] global axi�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    dw_axi_mst_cg_en           : 1; /* [11..11] master axi�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    dw_axi_amon_gatedclock_en  : 1; /* [12..12] amon�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    dw_axi_bbphy_cg_en         : 1; /* [13..13] bbphy axi�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    dw_rs_cg_en                : 1; /* [14..14] rs axi�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ�Rsλ��PCIE�2�� */
        unsigned int    dw_x2x_async_cg_en         : 1; /* [15..15] async x2x�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ�async x2x�ֲ��ڣ�DSP0������HIFI2�� */
        unsigned int    dw_x2x_qsync_cg_en         : 1; /* [16..16] qsync x2x�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ�qsync x2x Ŀǰû�С� */
        unsigned int    dw_x2h_qsync_cg_en         : 1; /* [17..17] rs axi�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    dw_hmx_cg_en               : 1; /* [18..18] hmx�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ�λ��m3��ahb2axi_mst���һ�� */
        unsigned int    dw_x2p_cg_en               : 1; /* [19..19] x2p�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    dw_gs_cg_en                : 1; /* [20..20] gs�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ�gsλ��axi mem�� */
        unsigned int    ashb_gatedclock_en         : 1; /* [21..21] h2x�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ�λ��m3��ahb2axi_mst���һ�� */
        unsigned int    dw_ahb_mst_gatedclock_en   : 1; /* [22..22] mst ahb�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    axi_guacc_gatedclock_en    : 1; /* [23..23] guacc�����Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    edmac_autogated_clk_en     : 1; /* [24..24] edmac�Զ��ſ�ʹ�ܡ�0����ʹ�ܣ�Ĭ��ֵ����1��ʹ�ܡ� */
        unsigned int    reserved_1                 : 6; /* [30..25] ������ */
        unsigned int    reserved_0                 : 1; /* [31..31] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL21_T;    /* �����Զ��ſ�ʱ�ӿ��ƼĴ���1�� */

typedef union
{
    struct
    {
        unsigned int    hifi_ema                   : 3; /* [2..0] extra margin adjustment ,[0] = LSB */
        unsigned int    hifi_emaw                  : 2; /* [4..3] extra margin adjustment write,[0] = LSB */
        unsigned int    hifi_emas                  : 1; /* [5..5] extra margin adjustment sense amplifier pulse */
        unsigned int    reserved_1                 : 10; /* [15..6] ������ */
        unsigned int    dsp0_ema                   : 3; /* [18..16] extra margin adjustment ,[0] = LSB */
        unsigned int    dsp0_emaw                  : 2; /* [20..19] extra margin adjustment write,[0] = LSB */
        unsigned int    dsp0_emas                  : 1; /* [21..21] extra margin adjustment sense amplifier pulse */
        unsigned int    reserved_0                 : 10; /* [31..22] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL22_T;    /* memory ʱ�����üĴ���0�� */

typedef union
{
    struct
    {
        unsigned int    axi_mem_ema                : 3; /* [2..0] extra margin adjustment ,[0] = LSB */
        unsigned int    axi_mem_emaw               : 2; /* [4..3] extra margin adjustment write,[0] = LSB */
        unsigned int    axi_mem_emas               : 1; /* [5..5] extra margin adjustment sense amplifier pulse */
        unsigned int    reserved_2                 : 2; /* [7..6] ������ */
        unsigned int    soc_mem_ema                : 3; /* [10..8] extra margin adjustment ,[0] = LSB������soc spram ��dpram���Լ�tpram��A�ڡ���soc_mem��ע�⣺soc spram������socp��coresight��hs_uart��nandc��ipf,cipher,hsic,uicc,usb3ģ���ڵ�spram��soc dpram������mmc0��mmc1��mmc2��ssdma��sdccģ���ڵ�dpram��soc tpram������socp��edmac��ssdmac��amon��gmac��ipf��cipher��mipiģ���ڵ�tpram�� */
        unsigned int    soc_mem_spram_emaw         : 2; /* [12..11] extra margin adjustment write,[0] = LSB */
        unsigned int    soc_mem_spram_emas         : 1; /* [13..13] extra margin adjustment sense amplifier pulse */
        unsigned int    soc_mem_tpram_emab         : 3; /* [16..14] extra margin adjustment ,[0] = LSB������soc tpram��B�ڡ� */
        unsigned int    soc_mem_tpram_emasa        : 1; /* [17..17] extra margin adjustment sense amplifier pulse */
        unsigned int    soc_mem_dpram_emaw         : 2; /* [19..18] extra margin adjustment write,[0] = LSB */
        unsigned int    soc_mem_dpram_emas         : 1; /* [20..20] extra margin adjustment sense amplifier pulse */
        unsigned int    reserved_1                 : 3; /* [23..21] ������ */
        unsigned int    bootrom_ema                : 3; /* [26..24] ema */
        unsigned int    bootrom_pgen               : 1; /* [27..27] pgen ����Ч��power_down mode Enable */
        unsigned int    bootrom_ken                : 1; /* [28..28] ken ����Ч��0��the keepers on the bitlines are enabled.this keeps the functional state of the bitlines by holding the bitline values, but slows down the access time by 1-2%.1��keepers disabled. */
        unsigned int    reserved_0                 : 3; /* [31..29] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL23_T;    /* memory ʱ�����üĴ���1�� */

typedef union
{
    struct
    {
        unsigned int    appa9_hs_mem_adjust        : 10; /* [9..0] AppA9 memory ʱ��/�͹��Ŀ��ơ�[9:7]������[6]��ret1n[5]��EMAS[4:3]��EMAW[2:0]��EMA */
        unsigned int    moda9_hs_mem_adjust        : 10; /* [19..10] ModA9 memory ʱ��/�͹��Ŀ��ơ�[9:7]������[6]��ret1n[5]��EMAS[4:3]��EMAW[2:0]��EMA */
        unsigned int    appa9_l2_ema               : 3; /* [22..20] extra margin adjustment ,[0] = LSB */
        unsigned int    appa9_l2_emaw              : 2; /* [24..23] extra margin adjustment write,[0] = LSB */
        unsigned int    appa9_l2_emas              : 1; /* [25..25] extra margin adjustment sense amplifier pulse */
        unsigned int    moda9_l2_ema               : 3; /* [28..26] extra margin adjustment ,[0] = LSB */
        unsigned int    moda9_l2_emaw              : 2; /* [30..29] extra margin adjustment write,[0] = LSB */
        unsigned int    moda9_l2_emas              : 1; /* [31..31] extra margin adjustment sense amplifier pulse */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL24_T;    /* memory ʱ�����üĴ���2�� */

typedef union
{
    struct
    {
        unsigned int    test_sys0_sel              : 1; /* [0..0] SOC test�ź������0����ioshare�ź�ѡ��SOC �����ź����ʱ���Ѹ���PD���mtcmos_ctrl�����PAD��1����ioshare�ź�ѡ��SOC �����ź����ʱ����glb�ŵ�dlock�ź������PAD�� */
        unsigned int    test_sys1_sel              : 1; /* [1..1] SOC test�ź������0����glb������ʱ����test_sys_bypass�ź�Ϊ0ʱ���Զ���glb�ŵ�dlock�ź������PAD��1����glb������ʱ����test_sys_bypass�ź�Ϊ0ʱ���Զ��Ѹ���PD���mtcmos_ctrl�����PAD�� */
        unsigned int    reserved                   : 30; /* [31..2] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL25_T;    /* SOC �����ź�ѡ��Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    test_sys0_bypass           : 32; /* [31..0] SOC �����ź�bypass�Ĵ�������glb������ʱ�����á�0����bypass�� 1��bypass */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL26_T;    /* SOC �����ź�bypass�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cs_spiden                  : 1; /* [0..0] CoreSight secure privilege invasive Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܣ�Ĭ��ֵ���� */
        unsigned int    cs_spniden                 : 1; /* [1..1] CoreSight secure privilege Non-invasive Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܣ�Ĭ��ֵ���� */
        unsigned int    cs_dbgen                   : 1; /* [2..2] Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܣ�Ĭ��ֵ���� */
        unsigned int    cs_niden                   : 1; /* [3..3] Non-invasive Debugʹ�ܿ��ơ�0����ʹ�ܣ�1��ʹ�ܣ�Ĭ��ֵ���� */
        unsigned int    cs_tpctl                   : 1; /* [4..4] ָʾtracectl�ź��Ƿ���ڡ�0����ʹ�ܣ�1��ʹ�ܣ�Ĭ��ֵ���� */
        unsigned int    cs_deviceen                : 1; /* [5..5] �豸ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܣ�Ĭ��ֵ���� */
        unsigned int    reserved_1                 : 2; /* [7..6] ������ */
        unsigned int    cs_tpmaxdataasize          : 5; /* [12..8] TRACEDATA������ݹܽ����á� */
        unsigned int    cs_nsguaren                : 1; /* [13..13] �ǰ�ȫ��axi���ʿ��ƣ�0����ʹ�ܣ�1��ʹ�ܣ� */
        unsigned int    cs_tsmaxwidth              : 1; /* [14..14] ���timestampλ��0��48bit1��64bit */
        unsigned int    cs_tsnatural               : 1; /* [15..15] timestamp���뷽ʽ��0��gray1��bin */
        unsigned int    cs_timestamp_en            : 1; /* [16..16] coresight timestamp ����ʹ�ܡ� */
        unsigned int    reserved_0                 : 15; /* [31..17] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL27_T;    /* Coresight Debug���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 20; /* [19..0] ������ */
        unsigned int    filter_start               : 12; /* [31..20] ��ַ�����׵�ַ����C����ʼ��ַΪ0x5000_0000�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL28_T;    /* ��ַ�����׵�ַ�� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 20; /* [19..0] ������ */
        unsigned int    filter_end                 : 12; /* [31..20] ��ַ����β��ַ����C�ν�����ַΪ0x7FEF_FFFF�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL29_T;    /* ��ַ����β��ַ�� */

typedef union
{
    struct
    {
        unsigned int    sci0_clk_od_en             : 1; /* [0..0] SCIʱ�����ģʽ�����źš�0��CMOS���ģʽ��Ĭ��ֵ����1��Opern-drain���ģʽ�� */
        unsigned int    sci0_data_od_en            : 1; /* [1..1] SCI�������ģʽ���á�0:CMOS���ģʽ��Ĭ��ֵ����1:Opern-drain���ģʽ�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ������ */
        unsigned int    sci1_clk_od_en             : 1; /* [4..4] SCIʱ�����ģʽ�����źš�0��CMOS���ģʽ��Ĭ��ֵ����1��Opern-drain���ģʽ�� */
        unsigned int    sci1_data_od_en            : 1; /* [5..5] SCI�������ģʽ���á�0��CMOS���ģʽ��Ĭ��ֵ����1��Opern-drain���ģʽ�� */
        unsigned int    reserved_0                 : 26; /* [31..6] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL30_T;    /* SCI���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL31_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ebi_normal_mode            : 1; /* [0..0] ͣ��ģʽѡ��0��ͣ��ģʽ��1����ͣ��ģʽ��ͣ��ģʽ�£����û�п���������EBI������ٲø�ͨ��1��nandc������ͣ��ģʽ�£����û�����룬�򲻻��ٲø���һ��ͨ���� */
        unsigned int    reserved_2                 : 3; /* [3..1] ������ */
        unsigned int    ebi_timeoutvalue1          : 10; /* [13..4] nandcͨ��timeoutֵ�� */
        unsigned int    reserved_1                 : 2; /* [15..14] ������ */
        unsigned int    ebi_timeoutvalue2          : 10; /* [25..16] emiͨ��timeoutֵ�� */
        unsigned int    reserved_0                 : 6; /* [31..26] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL32_T;    /* EBI���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_2                 : 1; /* [0..0] ������ */
        unsigned int    func_ddr_testmode          : 1; /* [1..1] DramTest����ͨ·���ơ�0�����򿪲���ͨ·��Ĭ�ϣ���1���򿪲���ͨ·�� */
        unsigned int    reserved_1                 : 6; /* [7..2] ������ */
        unsigned int    reserved_0                 : 24; /* [31..8] tsensorģ��IP���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL33_T;    /* dram_test����ģʽ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    refclk_div                 : 7; /* [6..0] �ο�ʱ��Ƶ��ѡ��0010100��20MHz��0010101��19.2MHz��0011010��16MHz��0011100��15MHz��0011100��13MHz��0100100��12MHz������ֵ��������������power-on resetǰ������ɣ�������normal�²����䡣 */
        unsigned int    txrputune                  : 2; /* [8..7] ��������迹���ڣ�����DATA��STROBE����Դ�迹��00��+11%��01��+5%��10��Ĭ��ֵ��11��-5%�� */
        unsigned int    txrpdtune                  : 2; /* [10..9] ��������迹���ڣ�����DATA��STROBE����Դ�迹��00��-11%��01��-5%��10��Ĭ��ֵ��11��+5%�� */
        unsigned int    txsrtune                   : 4; /* [14..11] ���slew rate���ڣ�����DATA��STROBE���б�ʡ�0000��-20%��0001��-10%��0011��Ĭ��ֵ��0111��+10%��1111��+20%�� */
        unsigned int    loopbackenb                : 1; /* [15..15] Loopback Test Enable��0�����ݴ����ڼ䣬�����߼���ʹ�ܣ�1�����ݴ����ڼ䣬�����߼�ʹ�ܡ���run BIST�ڼ��������ã�����ģʽ��Ҳ��ʹ�á� */
        unsigned int    siddq                      : 1; /* [16..16] IDDQ Test Enable����ʹ�û��ڵ�������ģ��blockʱ����IDDQ���ԡ�0��ģ��block�����磻1��ģ��block���硣 */
        unsigned int    txbitstuffen               : 1; /* [17..17] Low-byte transmit Bit-Stuffing Enable. ����OPMODEΪ2'b11ʱ����DATAIN[7:0]λ��䡣0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    txbitstuffenh              : 1; /* [18..18] High-byte transmit Bit-Stuffing Enable. ����OPMODEΪ2'b11ʱ����DATAINH[7:0]λ��䡣0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    hsic_portreset             : 1; /* [19..19] Per-Port Reset������û�йر�HSIC Transceiver PHY��ʱ���¸�λ���ͽ����߼���0�����ͽ���״̬������������and the line_state logic becomes sequential after 11 PHYCLK cycles��1�����ͽ���״̬����λ�� */
        unsigned int    reserved_1                 : 1; /* [20..20] �����Ĵ����� */
        unsigned int    dmpulldown                 : 1; /* [21..21] HSIC PHY�����ź�dmpulldown���á�0��deviceģʽ��1��hostģʽ�� */
        unsigned int    dppulldown                 : 1; /* [22..22] HSIC PHY�����ź�dppulldown���á�0��deviceģʽ��1��hostģʽ�� */
        unsigned int    reserved_0                 : 7; /* [29..23] ������ */
        unsigned int    utmi_hostdisconnect        : 1; /* [30..30]  */
        unsigned int    utmiotg_iddig              : 1; /* [31..31] mini A/B plgy indicator��0��Mini-A connected��hostģʽ��1��Mini-B connected��deviceģʽ�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL34_T;    /* HSICPHY/HSIC���������üĴ����� */

typedef union
{
    struct
    {
        unsigned int    test_addr                  : 4; /* [3..0] HSIC PHY���ԽӿڼĴ�����ַ�����������Ҫ��Ϊ0�� */
        unsigned int    test_datain                : 8; /* [11..4] HSIC PHY�����������ߡ���4bit����������ݣ���4bitΪ��Ӧ��дʹ�ܡ�������ý�Ϊ0�� */
        unsigned int    test_clk                   : 1; /* [12..12] HSIC PHY����ʱ�ӣ�������Ҫ��Ϊ0�� */
        unsigned int    test_dataoutsel            : 1; /* [13..13] HSIC PHY�����������ѡ��0���ڲ������1�����������������ý�Ϊ0�� */
        unsigned int    reserved                   : 14; /* [27..14] ������ */
        unsigned int    test_dataout               : 4; /* [31..28] HSIC PHY��������������ߣ�������test_dataoutselѡ�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL35_T;    /* HSICPHY���Կ��ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    fsel                       : 3; /* [2..0] �ο�ʱ��ѡ��000��9.6MHz��001��10MHz��010��12MHz��011��19.2MHz��Ĭ��ֵ����100��20MHz��101��24MHz��110��reserved��111��50MHz�� */
        unsigned int    refclk_sel                 : 2; /* [4..3] PLLģ��ο�ʱ��Դѡ�񡣴˳�Ա�������ϵ縴λǰ���ò�����������ʱ�����ġ�00�����壻01��XO�ܽ��ϵ��ⲿ2.5Vʱ�ӣ�10��CLKCORE�ܽ�����ʱ�ӣ��ɴ�core������11�������� */
        unsigned int    common_on_n                : 1; /* [5..5] Common Block��XO,Bias,PLL��������źš����źű����ϵ縴λǰ��á�0��suspendģʽ�£�XO,Bias,PLLģ����磻sleepģʽ�£����crystal��Ϊ�ο�ʱ�ӣ�XOģ��һֱ�����磻1��suspendģʽ�£�XO,Bias,PLLģ����磻sleepģʽ�£�Bias,PLLģ����硣 */
        unsigned int    port_reset                 : 1; /* [6..6] �˿ڸ�λ���ơ�����û�йر�HSIC PHY��ʱ���¸�λ���ͽ����߼���0������λ��1����λ�� */
        unsigned int    vatestenb                  : 2; /* [8..7] ģ����Թܽ�ѡ��ʹ��ģ����Ե�ѹ����ANALOGTEST��ID0�ܽ�00����������01������ID0��10������ANALOGTEST��11�������� */
        unsigned int    txvreftune                 : 4; /* [12..9] ����DC��ѹ���ڡ�0000��-10%��0001��-8.75%��0010��-7.5%��0011��-6.25%��0100��-5%��0101��-3.75%��0110��-2.5%��0111��-1.25%��1000��Design default%��1001��+1.25%��1010��+2.5%��1011��+3.75%��1100��+5%��1101��+6.25%��1110��+7.5%��1111��+8.75%�� */
        unsigned int    txfslstune                 : 4; /* [16..13] ȫ��/����Դ���迹������0000��+5%��0001��+2.5%��0011��Ĭ��ֵ��0111��-2.5%��1111��-5%��others��reserved�� */
        unsigned int    txhsxvtune                 : 2; /* [18..17] ���ٷ����źŵ�ѹ����������00��reserved��01��-15mV��10��+15mV��11��Ĭ��ֵ�� */
        unsigned int    otgtune                    : 3; /* [21..19] VBUS��Ч��ֵ��ѹ������000��-12%��001��-9%��010��-6%��011��-3%��100��Ĭ��ֵ��101��+3%��110��+6%��111��+9%�� */
        unsigned int    compdistune                : 3; /* [24..22] �Ͽ�������ֵ��ѹ������000��-6%��001��-4.5%��010��-3%��011��-1.5%100��Ĭ��ֵ��101��+1.5%��110��+3%��111��+4.5%�� */
        unsigned int    sqrxtune                   : 3; /* [27..25] Squelch��ֵ��ѹ������000��+15%��001��+10%��010��+5%��011��Ĭ��ֵ��100��-5%��101��-10%��110��-15%��111��-20%�� */
        unsigned int    txrisetune                 : 2; /* [29..28] ���ٷ�������/�½���ʱ�������00��+20%��01��+15%��10��Design default��11��-10%�� */
        unsigned int    txpreempamptune            : 2; /* [31..30] ���ٷ���Ԥ���ص������ơ�00����ʹ�ܣ�01��1��Ԥ���ص�����10��2��Ԥ���ص�����11��3��Ԥ���ص����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL36_T;    /* USBPHY���ƼĴ���0�� */

typedef union
{
    struct
    {
        unsigned int    test_addr                  : 4; /* [3..0] ���ԽӿڼĴ�����ַ�����������Ҫ��Ϊ0 */
        unsigned int    test_clk                   : 1; /* [4..4] ����ʱ�ӣ�������Ҫ��Ϊ0 */
        unsigned int    test_dataout_sel           : 1; /* [5..5] �����������ѡ��0���ڲ������1�����������������ý�Ϊ0 */
        unsigned int    phy_clk_sel                : 1; /* [6..6] ���utmi_clkʱ��ѡ��0�����FREECLK��1�����PHYCLOCK0�� */
        unsigned int    phy_id_sel                 : 1; /* [7..7] mul_id_bc_val���ѡ��0�����iddig״̬��1�����{rid_float,rid_gnd,rid_a,rid_b,rid_c}�� */
        unsigned int    test_datain                : 8; /* [15..8] �����������ߣ���4bit����������ݣ���4bitΪ��Ӧ��дʹ�ܡ�������ý�Ϊ0 */
        unsigned int    test_dataout               : 4; /* [19..16] ��������������ߣ�������test_dataoutselѡ�� */
        unsigned int    acaenb                     : 1; /* [20..20] ACAʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    retenablen                 : 1; /* [21..21] retentionģʽʹ�ܣ�����Ч����������ģʽ�£���bit��������Ϊ1������retentionģʽ֧��PHY��0.9v��3.3v��Դ�������硣0��ʹ�ܣ�1����ʹ�ܡ� */
        unsigned int    reserved                   : 2; /* [23..22] ���� */
        unsigned int    txpreemppulsetune          : 1; /* [24..24] ���ٷ���Ԥ����ʱ����ơ�0��2��Ԥ����ʱ�䣬Ĭ��ֵ��1: 1��Ԥ����ʱ�䡣 */
        unsigned int    otgdisable                 : 1; /* [25..25] OTG����ʹ�ܡ� 0��ʹ�ܣ�1����ʹ�ܡ� */
        unsigned int    loopbackenb                : 1; /* [26..26] ���ز���ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    vbusvldextsel              : 1; /* [27..27] �ⲿVbus��Чѡ���źš�0��ʹ���ڲ�session valid comparator(Ĭ������)��1��ʹ��vbusvldext�źš� */
        unsigned int    vbusvldext                 : 1; /* [28..28] Vbus��Чָʾ�źš����ź���vbusvldextsel�ź�����Ϊ1����deviceģʽʱ��Ч��0��vbus��Ч����ʹ��D+�ϵ��������裻1��vbus�ź���Ч��ʹ��D+�ϵ��������衣 */
        unsigned int    txrestune                  : 2; /* [30..29] Դ���迹������00: ����1.5����01: Ĭ��ֵ��10: ��С2 ����11: ��С4 ���� */
        unsigned int    siddq                      : 1; /* [31..31] IDDQ����ģʽʹ�ܡ�����SIDDQģʽ������ģ��ģ����硣0����ʹ�ܣ�1��ʹ�ܡ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL37_T;    /* USBPHY���ƼĴ���1�� */

typedef union
{
    struct
    {
        unsigned int    compdistune                : 3; /* [2..0]  */
        unsigned int    otgtune                    : 3; /* [5..3]  */
        unsigned int    sqrxtune                   : 3; /* [8..6]  */
        unsigned int    txfslstune                 : 4; /* [12..9]  */
        unsigned int    txhsxvtune                 : 2; /* [14..13]  */
        unsigned int    txpreempamptune            : 2; /* [16..15]  */
        unsigned int    txpreemppulsetune          : 1; /* [17..17]  */
        unsigned int    txrestune                  : 2; /* [19..18]  */
        unsigned int    txrisetune                 : 2; /* [21..20]  */
        unsigned int    txvreftune                 : 4; /* [25..22]  */
        unsigned int    los_bias                   : 3; /* [28..26]  */
        unsigned int    los_level2_0               : 3; /* [31..29] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL38_T;    /* USBPHY���ƼĴ���2�� */

typedef union
{
    struct
    {
        unsigned int    los_level4_3               : 2; /* [1..0]  */
        unsigned int    pcs_tx_deemph_3p5db        : 6; /* [7..2]  */
        unsigned int    pcs_tx_deemph_6db          : 6; /* [13..8]  */
        unsigned int    pcs_tx_swing_full          : 7; /* [20..14]  */
        unsigned int    lane0_tx_term_offset       : 5; /* [25..21]  */
        unsigned int    tx_vboost_lvl              : 3; /* [28..26]  */
        unsigned int    reserved                   : 3; /* [31..29] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL39_T;    /* USBPHY���ƼĴ���3�� */

typedef union
{
    struct
    {
        unsigned int    cr_data_in                 : 16; /* [15..0]  */
        unsigned int    cr_cap_addr                : 1; /* [16..16]  */
        unsigned int    cr_cap_data                : 1; /* [17..17]  */
        unsigned int    cr_write                   : 1; /* [18..18]  */
        unsigned int    cr_read                    : 1; /* [19..19]  */
        unsigned int    rtune_req                  : 1; /* [20..20]  */
        unsigned int    reserved                   : 11; /* [31..21] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL40_T;    /* USBPHY���ƼĴ���4�� */

typedef union
{
    struct
    {
        unsigned int    usb3_bus_filter_bypass     : 4; /* [3..0]  */
        unsigned int    usb3_fladj_30mhz_reg       : 6; /* [9..4]  */
        unsigned int    usb3_host_u2_port_disable  : 1; /* [10..10]  */
        unsigned int    usb3_host_u3_port_disable  : 1; /* [11..11]  */
        unsigned int    usb3_host_port_pwrctl      : 1; /* [12..12]  */
        unsigned int    usb3_host_msi_enable       : 1; /* [13..13]  */
        unsigned int    usb3_pm_power_state_request : 2; /* [15..14]  */
        unsigned int    usb3_xhci_revision         : 1; /* [16..16]  */
        unsigned int    usb3_xhc_bme               : 1; /* [17..17]  */
        unsigned int    reserved_1                 : 1; /* [18..18]  */
        unsigned int    reserved_0                 : 1; /* [19..19]  */
        unsigned int    usb3_pmu_iddig_override    : 1; /* [20..20]  */
        unsigned int    usb3_pmu_avalid_override   : 1; /* [21..21]  */
        unsigned int    usb3_pmu_bvalid_override   : 1; /* [22..22]  */
        unsigned int    usb3_pmu_vbusvalid_override : 1; /* [23..23]  */
        unsigned int    usb3_pmu_sessend_override  : 1; /* [24..24]  */
        unsigned int    usb3_pmu_powerpresent_override : 1; /* [25..25]  */
        unsigned int    usb3_pmu_iddig_override_en : 1; /* [26..26]  */
        unsigned int    usb3_pmu_avalid_override_en : 1; /* [27..27]  */
        unsigned int    usb3_pmu_bvalid_override_en : 1; /* [28..28]  */
        unsigned int    usb3_pmu_vbusvalid_override_en : 1; /* [29..29]  */
        unsigned int    usb3_pmu_sessend_override_en : 1; /* [30..30]  */
        unsigned int    usb3_pmu_powerpresent_override_en : 1; /* [31..31]  */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL41_T;    /* USB Controller ���ƼĴ���0 */

typedef union
{
    struct
    {
        unsigned int    usb3_pmu_pm_pmu_config_strap : 30; /* [29..0]  */
        unsigned int    usb3_pmu_port_overcurrent  : 2; /* [31..30]  */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL42_T;    /* USB Controller ���ƼĴ���1 */

typedef union
{
    struct
    {
        unsigned int    usb3_hub_port_perm_attach  : 2; /* [1..0]  */
        unsigned int    usb3_pme_en                : 1; /* [2..2]  */
        unsigned int    reserved                   : 29; /* [31..3] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL43_T;    /* USB Controller ���ƼĴ���2 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL44_T;    /* SSIC PHY���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    uicc_ic_usb_vbusvalid      : 1; /* [0..0] VBUS��Ч���ơ�0����Ч��1����Ч�� */
        unsigned int    reserved                   : 7; /* [7..1] ������ */
        unsigned int    intr_merge0_en             : 1; /* [8..8] �жϺϲ�������0ʹ�ܿ��ơ�1��ʹ�ܣ� 0����ֹ�� */
        unsigned int    intr_merge0_mode           : 1; /* [9..9] �жϺϲ�������0ģʽѡ��0��ģʽ0��1��ģʽ1�� */
        unsigned int    intr_merge1_en             : 1; /* [10..10] �жϺϲ�������1ʹ�ܿ��ơ�1��ʹ�ܣ� 0����ֹ�� */
        unsigned int    intr_merge1_mode           : 1; /* [11..11] �жϺϲ�������1ģʽѡ��0��ģʽ0��1��ģʽ1�� */
        unsigned int    intr_merge2_en             : 1; /* [12..12] �жϺϲ�������2ʹ�ܿ��ơ�1��ʹ�ܣ� 0����ֹ�� */
        unsigned int    intr_merge2_mode           : 1; /* [13..13] �жϺϲ�������2ģʽѡ��0��ģʽ0��1��ģʽ1�� */
        unsigned int    intr_merge3_en             : 1; /* [14..14] �жϺϲ�������3ʹ�ܿ��ơ�1��ʹ�ܣ� 0����ֹ�� */
        unsigned int    intr_merge3_mode           : 1; /* [15..15] �жϺϲ�������3ģʽѡ��0��ģʽ0��1��ģʽ1�� */
        unsigned int    intr_merge0_sel            : 4; /* [19..16] ѡ���ĸ��жϽ���merge             12��uicc_intr                         11~10��ipfilter[1:0]                     9��edmac_intr                        8��hsic_intr                         7��cipher_intr                       6��mmc1_intr                         5��mmc0_intr                             4��sdcc_intr                         3��pcie_edma_int                     2��pcie_pm_int                       1��usb3_otg_intr                     0��usb3_intr */
        unsigned int    intr_merge1_sel            : 4; /* [23..20] ѡ���ĸ��жϽ���merge             12��uicc_intr                         11~10��ipfilter[1:0]                     9��edmac_intr                        8��hsic_intr                         7��cipher_intr                       6��mmc1_intr                         5��mmc0_intr                             4��sdcc_intr                         3��pcie_edma_int                     2��pcie_pm_int                       1��usb3_otg_intr                     0��usb3_intr */
        unsigned int    intr_merge2_sel            : 4; /* [27..24] ѡ���ĸ��жϽ���merge             12��uicc_intr                         11~10��ipfilter[1:0]                     9��edmac_intr                        8��hsic_intr                         7��cipher_intr                       6��mmc1_intr                         5��mmc0_intr                             4��sdcc_intr                         3��pcie_edma_int                     2��pcie_pm_int                       1��usb3_otg_intr                     0��usb3_intr */
        unsigned int    intr_merge3_sel            : 4; /* [31..28] ѡ���ĸ��жϽ���merge             12��uicc_intr                         11~10��ipfilter[1:0]                     9��edmac_intr                        8��hsic_intr                         7��cipher_intr                       6��mmc1_intr                         5��mmc0_intr                             4��sdcc_intr                         3��pcie_edma_int                     2��pcie_pm_int                       1��usb3_otg_intr                     0��usb3_intr */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL45_T;    /* uicc���жϺϲ����ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    intr_merge0_timer0         : 16; /* [15..0] �жϺϲ�������0��ʱ���ã���λ��48MHzʱ�ӵ�һ�����ڡ� */
        unsigned int    intr_merge0_timer1         : 16; /* [31..16] �жϺϲ�������1��ʱ���ã���λ��48MHzʱ�ӵ�һ�����ڡ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL46_T;    /* �жϺϲ���ʱ�Ĵ���0�� */

typedef union
{
    struct
    {
        unsigned int    int2_merge0_timer2         : 16; /* [15..0] �жϺϲ�������2��ʱ���ã���λ��48MHzʱ�ӵ�һ�����ڡ� */
        unsigned int    intr_merge0_timer3         : 16; /* [31..16] �жϺϲ�������3��ʱ���ã���λ��48MHzʱ�ӵ�һ�����ڡ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL47_T;    /* �жϺϲ���ʱ�Ĵ���1�� */

typedef union
{
    struct
    {
        unsigned int    sysctrl_intr_appa9         : 2; /* [1..0] ϵͳ������ARM����жϡ�[1]��AppA9 101���ж�  1��ʹ��  0����ʹ��[0]��AppA9 100���ж�  1��ʹ��  0����ʹ�� */
        unsigned int    sysctrl_intr_mdma9         : 2; /* [3..2] ϵͳ������ARM����жϡ�[1]��MDMA9 101���ж�  1��ʹ��  0����ʹ��[0]��MDMA9 100���ж�  1��ʹ��  0����ʹ�� */
        unsigned int    sysctrl_intr_cm3           : 2; /* [5..4] ϵͳ������ARM����жϡ�[1]��CM3 74���ж�  1��ʹ��  0����ʹ��[0]��CM3 75���ж�  1��ʹ��  0����ʹ�� */
        unsigned int    reserved                   : 26; /* [31..6] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL48_T;    /* CPU���ж���λ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    sysctrl_intr_appa9         : 2; /* [1..0] ϵͳ������ARM����жϡ�[1]��AppA9 101���ж�  1�����  0�������[0]��AppA9 100���ж�  1�����  0������� */
        unsigned int    sysctrl_intr_mdma9         : 2; /* [3..2] ϵͳ������ARM����жϡ�[1]��MDMA9 101���ж�  1�����  0�������[0]��MDMA9 100���ж�  1�����  0������� */
        unsigned int    sysctrl_intr_cm3           : 2; /* [5..4] ϵͳ������ARM����жϡ�[1]��CM3 75���ж�  1�����  0�������[0]��Cm3 740���ж�  1�����  0������� */
        unsigned int    reserved                   : 26; /* [31..6] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL49_T;    /* CPU���ж�����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    sysctrl_intr_appa9         : 2; /* [1..0] ϵͳ������ARM����жϡ�[1]��AppA9 101���ж�  1��ʹ��  0����ʹ��[0]��AppA9 100���ж�  1��ʹ��  0����ʹ�� */
        unsigned int    sysctrl_intr_mdma9         : 2; /* [3..2] ϵͳ������ARM����жϡ�[1]��MDMA9 101���ж�  1��ʹ��  0����ʹ��[0]��MDMA9 100���ж�  1��ʹ��  0����ʹ�� */
        unsigned int    sysctrl_intr_cm3           : 2; /* [5..4] ϵͳ������ARM����жϡ�[1]��CM3 75���ж�  1��ʹ��  0����ʹ��[0]��CM3 74���ж�  1��ʹ��  0����ʹ�� */
        unsigned int    reserved                   : 26; /* [31..6] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL50_T;    /* CPU���ж�״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cm3_nmi                    : 16; /* [15..0] cm3���������жϣ���һbitΪ�߼���Ч�� */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL51_T;    /* M3���������жϼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dsp0_nmi                   : 16; /* [15..0] dsp0���������жϣ���һbitΪ�߼���Ч�� */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL52_T;    /* dsp0���������жϼĴ����� */

typedef union
{
    struct
    {
        unsigned int    hifi_nmi                   : 16; /* [15..0] HIFI2���������жϣ���һbitΪ�߼���Ч�� */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL53_T;    /* HIFI DSP���������жϼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dw_ssi0_dma_sel            : 1; /* [0..0] DW_SSI0 DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    dw_ssi1_dma_sel            : 1; /* [1..1] DW_SSI1 DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    sio_dma_sel                : 1; /* [2..2] SIO DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    hs_uart_dma_sel            : 1; /* [3..3] HS_UART DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    uart0_dma_sel              : 1; /* [4..4] UART0 DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    uart1_dma_sel              : 1; /* [5..5] UART1 DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    uart2_dma_sel              : 1; /* [6..6] UART2 DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    sci0_dma_sel               : 1; /* [7..7] SCI0 DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    sci1_dma_sel               : 1; /* [8..8] SCI1 DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    bbp_dbg_dma_sel            : 1; /* [9..9] bbp dbg DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    bbp_grif_dma_sel           : 1; /* [10..10] bbp grif DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    amon_soc_dma_sel           : 1; /* [11..11] axi monitor soc DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    amon_fast_dma_sel          : 1; /* [12..12] axi monitor fast DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    i2c0_dma_sel               : 1; /* [13..13] I2C0 DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    i2c1_dma_sel               : 1; /* [14..14] I2C1 DMAѡ��0��ѡ��EDAM��1��ѡ��EDMA_CH4�� */
        unsigned int    reserved                   : 17; /* [31..15] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL54_T;    /* DMAѡ����ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 1; /* [0..0] ������ */
        unsigned int    cs_ret1n                   : 1; /* [1..1] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    gmac_ret1n                 : 1; /* [2..2] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    usb3_ret1n                 : 1; /* [3..3] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    reserved_0                 : 1; /* [4..4] ������ */
        unsigned int    uicc_ret1n                 : 1; /* [5..5] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    nandc_ret1n                : 1; /* [6..6] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    sdcc_ret1n                 : 1; /* [7..7] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    hsic_ret1n                 : 1; /* [8..8] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    amon_soc_ret1n             : 1; /* [9..9] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    amon_cpufast_ret1n         : 1; /* [10..10] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    pcie_colldisn              : 1; /* [11..11] memory��д��ͻ��·disable���ơ�0��disable ��д��ͻ��·��1��enable ��д��ͻ��·�� */
        unsigned int    mmc_colldisn               : 1; /* [12..12] memory��д��ͻ��·disable���ơ�0��disable ��д��ͻ��·��1��enable ��д��ͻ��·�� */
        unsigned int    edmac_colldisn             : 1; /* [13..13] memory��д��ͻ��·disable���ơ�0��disable ��д��ͻ��·��1��enable ��д��ͻ��·�� */
        unsigned int    ssdma_colldisn             : 1; /* [14..14] memory��д��ͻ��·disable���ơ�0��disable ��д��ͻ��·��1��enable ��д��ͻ��·�� */
        unsigned int    sdcc_colldisn              : 1; /* [15..15] memory��д��ͻ��·disable���ơ�0��disable ��д��ͻ��·��1��enable ��д��ͻ��·�� */
        unsigned int    socp_colldisn              : 1; /* [16..16] memory��д��ͻ��·disable���ơ�0��disable ��д��ͻ��·��1��enable ��д��ͻ��·�� */
        unsigned int    amon_colldisn              : 1; /* [17..17] memory��д��ͻ��·disable���ơ�0��disable ��д��ͻ��·��1��enable ��д��ͻ��·�� */
        unsigned int    gmac_colldisn              : 1; /* [18..18] memory��д��ͻ��·disable���ơ�0��disable ��д��ͻ��·��1��enable ��д��ͻ��·�� */
        unsigned int    ipf_ret1n                  : 1; /* [19..19] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    ipf_colldisn               : 1; /* [20..20] memory��д��ͻ��·disable���ơ�0��disable ��д��ͻ��·��1��enable ��д��ͻ��·�� */
        unsigned int    cipher_ret1n               : 1; /* [21..21] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    cipher_colldisn            : 1; /* [22..22] memory��д��ͻ��·disable���ơ�0��disable ��д��ͻ��·��1��enable ��д��ͻ��·�� */
        unsigned int    socp_ret1n                 : 1; /* [23..23] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    mipi_ret1n                 : 1; /* [24..24] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    hs_uart_ret1n              : 1; /* [25..25] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    mmc0_ret1n                 : 1; /* [26..26] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    mmc1_ret1n                 : 1; /* [27..27] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    pcie_ret1n                 : 1; /* [28..28] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    edmac_ret1n                : 1; /* [29..29] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    ssdma_ret1n                : 1; /* [30..30] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    mipi_colldisn              : 1; /* [31..31] memory��д��ͻ��·disable���ơ�0��disable ��д��ͻ��·��1��enable ��д��ͻ��·�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL55_T;    /* memory�͹������üĴ���0�� */

typedef union
{
    struct
    {
        unsigned int    prior_level                : 2; /* [1..0] �������ȼ����á�00�����ȼ�dma > axi;01�����ȼ�axi > dma. */
        unsigned int    gatedclock_en              : 1; /* [2..2] lbus�����Զ�ʱ���ſ�ʹ�ܡ�1��ʹ�ܣ�0����ֹ�� */
        unsigned int    dw_axi_rs_gatedclock_en    : 1; /* [3..3] axi rs�Զ��ſ�ʹ�ܡ�1��ʹ�ܣ�0����ֹ�� */
        unsigned int    dw_axi_gs_gatedclock_en    : 1; /* [4..4] axi gs�Զ��ſ�ʹ�ܡ�1��ʹ�ܣ�0����ֹ�� */
        unsigned int    overf_prot                 : 2; /* [6..5] ���߷���������ѡ�00���رշ�����������01��ʹ�ܷ�������������ʱʱ�䣺512 cycles��10��ʹ�ܷ�������������ʱʱ�䣺1024 cycles��11��ʹ�ܷ�������������ʱʱ�䣺2048 cycles */
        unsigned int    reserved                   : 9; /* [15..7] ������ */
        unsigned int    atpram_ctrl                : 16; /* [31..16] memory�͹��Ŀ��ơ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL56_T;    /* BBP LBUS���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    soc2lte_tbd                : 16; /* [15..0]  */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL57_T;    /* BBP�������ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    moda9_l2_ret1n             : 1; /* [0..0] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    moda9_l2_ret2n             : 1; /* [1..1] memory retention mode2���ơ�0������retention��1��������retention�� */
        unsigned int    moda9_l2_pgen              : 1; /* [2..2] memory power down���ơ�0��������power down��1������power down�� */
        unsigned int    reserved_5                 : 1; /* [3..3] ������ */
        unsigned int    appa9_l2_ret1n             : 1; /* [4..4] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    appa9_l2_ret2n             : 1; /* [5..5] memory retention mode2���ơ�0������retention��1��������retention�� */
        unsigned int    appa9_l2_pgen              : 1; /* [6..6] memory power down���ơ�0��������power down��1������power down�� */
        unsigned int    reserved_4                 : 1; /* [7..7] ������ */
        unsigned int    dsp0_ret1n                 : 1; /* [8..8] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    dsp0_ret2n                 : 1; /* [9..9] memory retention mode2���ơ�V7R2��memory��֧�ִ�bit����0������retention��1��������retention�� */
        unsigned int    dsp0_pgen                  : 1; /* [10..10] memory power down���ơ�V7R2��memory��֧�ִ�bit����0��������power down��1������power down�� */
        unsigned int    reserved_3                 : 1; /* [11..11] ������ */
        unsigned int    hifi_ret1n                 : 1; /* [12..12] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    hifi_ret2n                 : 1; /* [13..13] memory retention mode2���ơ�V7R2��memory��֧�ִ�bit����0������retention��1��������retention�� */
        unsigned int    hifi_pgen                  : 1; /* [14..14] memory power down���ơ� V7R2��memory��֧�ִ�bit����0��������power down��1������power down�� */
        unsigned int    reserved_2                 : 1; /* [15..15] ������ */
        unsigned int    pd_axi_mem_ret1n           : 1; /* [16..16] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    pd_axi_mem_ret2n           : 1; /* [17..17] memory retention mode2���ơ�0������retention��1��������retention�� */
        unsigned int    pd_axi_mem_pgen            : 1; /* [18..18] memory power down���ơ�0��������power down��1������power down�� */
        unsigned int    reserved_1                 : 1; /* [19..19] ������ */
        unsigned int    ret_axi_mem_ret1n          : 1; /* [20..20] memory retention mode1���ơ�0������retention��1��������retention�� */
        unsigned int    ret_axi_mem_ret2n          : 1; /* [21..21] memory retention mode2���ơ�0������retention��1��������retention�� */
        unsigned int    ret_axi_mem_pgen           : 1; /* [22..22] memory power down���ơ�0��������power down��1������power down�� */
        unsigned int    reserved_0                 : 9; /* [31..23] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL68_T;    /* memory�͹������üĴ���2�� */

typedef union
{
    struct
    {
        unsigned int    axi_bbphy_xdcdr_sel        : 1; /* [0..0] 0�����ʹ��ӡ���λ������ģ��������ı������߼���������DECERR��1�����ʹ��ӡ���λ������ģ�鱨�������뵽default slave������DECERR�� */
        unsigned int    axi_amon_xdcdr_sel         : 1; /* [1..1] 0�����ʹ��ӡ���λ������ģ��������ı������߼���������DECERR��1�����ʹ��ӡ���λ������ģ�鱨�������뵽default slave������DECERR�� */
        unsigned int    axi_cpu_xdcdr_sel          : 1; /* [2..2] 0�����ʹ��ӡ���λ������ģ��������ı������߼���������DECERR��1�����ʹ��ӡ���λ������ģ�鱨�������뵽default slave������DECERR�� */
        unsigned int    axi_glb_xdcdr_sel          : 1; /* [3..3] 0�����ʹ��ӡ���λ������ģ��������ı������߼���������DECERR��1�����ʹ��ӡ���λ������ģ�鱨�������뵽default slave������DECERR�� */
        unsigned int    sysapb_pslverr_sel         : 1; /* [4..4] 0�����ʹ��ӡ���λ������ģ��������ı������߼���������DECERR��1�����ʹ��ӡ���λ������ģ�鱨�������뵽default slave������DECERR�� */
        unsigned int    socapb_pslverr_sel         : 1; /* [5..5] 0�����ʹ��ӡ���λ������ģ��������ı������߼���������DECERR��1�����ʹ��ӡ���λ������ģ�鱨�������뵽default slave������DECERR�� */
        unsigned int    x2h_hslverr_sel            : 1; /* [6..6] x2h�������߼���0�����ʹ��ӡ���λ������ģ��������ı������߼���ϵͳ���ܹ�����1�����ʹ��ӡ���λ������ģ�鱨�������뵽default slave��ϵͳ��������default slave����ok�� */
        unsigned int    mst_err_srst_req           : 1; /* [7..7] ���д�����Ϣ��λ����0������λ��1����λ����mst_err�жϺ�״̬�� */
        unsigned int    reserved                   : 24; /* [31..8] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL69_T;    /* ϵͳ�����ַ���ʹ��ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    axi_bbphy_priority_m1      : 2; /* [1..0] dw_axi_bbphy m1�ڣ�dw_axi_glb�ţ����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_bbphy_priority_m2      : 2; /* [3..2] dw_axi_bbphy m2�ڣ�dsp0�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_bbphy_priority_m3      : 2; /* [5..4] dw_axi_bbphy m3�ڣ�LTEBBP/TDSBBP�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_bbphy_priority_m4      : 2; /* [7..6] dw_axi_bbphy m4�ڣ�WBBP�����ȼ����á� */
        unsigned int    axi_guacc_priority_m1      : 2; /* [9..8] dw_axi_guacc m1�ڣ�cicom0�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ���ֵͬ�Ķ˿ں�С�����ȼ��ߡ� */
        unsigned int    axi_guacc_priority_m2      : 2; /* [11..10] dw_axi_guacc m2�ڣ�cicom1�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ���ֵͬ�Ķ˿ں�С�����ȼ��ߡ� */
        unsigned int    axi_guacc_priority_m3      : 2; /* [13..12] dw_axi_guacc m3�ڣ�hdlc�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ���ֵͬ�Ķ˿ں�С�����ȼ��ߡ� */
        unsigned int    axi_guacc_priority_m4      : 2; /* [15..14] dw_axi_guacc m4�ڣ�upacc�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ���ֵͬ�Ķ˿ں�С�����ȼ��ߡ� */
        unsigned int    axi_mst_priority_m9        : 4; /* [19..16] dw_axi_mxt m9�ڣ�CM3�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_mst_priority_m10       : 4; /* [23..20] dw_axi_mxt m10�ڣ�usb3�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    reserved_1                 : 4; /* [27..24] ������ */
        unsigned int    axi_cpu_priority_m1        : 1; /* [28..28] dw_axi_cpu��m1�ڣ�App A9 M1�ڣ����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_cpu_priority_m2        : 1; /* [29..29] dw_axi_cpu��m2�ڣ�Modem A9 M1�ڣ����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_amon_mst_priority_m1   : 1; /* [30..30] axi_amon m1�ڣ�axi_glb�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    reserved_0                 : 1; /* [31..31] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL70_T;    /* �������ȼ����üĴ���0�� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 4; /* [3..0] ���� */
        unsigned int    axi_glb_priority_m1        : 3; /* [6..4] dw_axi_glb m1�ڣ�dw_axi_bbphy�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_glb_priority_m2        : 3; /* [9..7] dw_axi_glb m2�ڣ�dw_axi_mst�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_glb_priority_m3        : 3; /* [12..10] dw_axi_glb m3�ڣ�appa9�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_glb_priority_m4        : 3; /* [15..13] dw_axi_glb m4�ڣ�mdma9�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_glb_priority_m5        : 3; /* [18..16] dw_axi_glb m5�ڣ�reserved�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_glb_priority_m6        : 3; /* [21..19] dw_axi_glb m6�ڣ�hifi�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_mst_cache_cfg_en       : 1; /* [22..22] APP��MOD CPU cache����ʹ�ܡ�0��ʹ������master cache��Ĭ�ϣ���1��ʹ��axi_mst_cache����ֵ�� */
        unsigned int    axi_mst_sideband           : 5; /* [27..23] ��GLB AXI�Ŵ��뵽ACP AW/ARUSERS�˵Ŀ����źš�[24:21]�ڲ�����0000��strongly-ordered��0001��device��0011��normal memory non-cacheable��0110��write-through��0111��write-back no write allocate��1111��write-back write allocate��[20]����AWIDMx[2]=0ʱ0��non-coherent request��1��coherent request�� */
        unsigned int    axi_mst_cache              : 4; /* [31..28] APP��MOD CPU cacheֵ��0000��noncacheable��nonbufferable0001��bufferable only0010��cacheable��but do not allocate0011��cacheable��bufferable��but do not allocate0100��reserved0101��reserved0110��cachable write-through, allocate on reads only0111��cachable write-back, allocate on reads only1000��reserved1001��reserved1010��cachable write-through, allocate on writes only1011��cachable write-back, allocate on writes only1100��reserved1101��reserved1110��cachable write-through, allocate on write & reads 1111��cachable write-back, allocate on write &reads */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL71_T;    /* �������ȼ����üĴ���1�� */

typedef union
{
    struct
    {
        unsigned int    axi_mst_priority_m1        : 4; /* [3..0] dw_axi_mxt m1�ڣ�dw_ahb�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_mst_priority_m2        : 4; /* [7..4] dw_axi_mxt m2�ڣ�edmac_ch4�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_mst_priority_m3        : 4; /* [11..8] dw_axi_mxt m3�ڣ�cipher�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_mst_priority_m4        : 4; /* [15..12] dw_axi_mxt m4�ڣ�ipf�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_mst_priority_m5        : 4; /* [19..16] dw_axi_mxt m5�ڣ�dw_axi_guacc�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_mst_priority_m6        : 4; /* [23..20] dw_axi_mxt m6�ڣ�cs_tmc�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_mst_priority_m7        : 4; /* [27..24] dw_axi_mxt m7�ڣ�socp�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
        unsigned int    axi_mst_priority_m8        : 4; /* [31..28] dw_axi_mxt m8�ڣ�edmac�����ȼ����á�ֵԽ�����ȼ�Խ�ߡ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL72_T;    /* �������ȼ����üĴ���2�� */

typedef union
{
    struct
    {
        unsigned int    appa9_gpio0_en             : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL81_T;    /* appa9 gpio0�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    mdma9_gpio0_en             : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL85_T;    /* mdma9 gpio0�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    cm3_gpio0_en               : 32; /* [31..0] M3 GPIO0�ж�ʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL98_T;    /* M3 GPIO0�ж�ʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_6                 : 1; /* [0..0] ���� �� */
        unsigned int    bbphy_dsp0_axislv_active   : 1; /* [1..1] dw_axi_bbyphy����dsp0 axi slave��active�ź����μĴ����� */
        unsigned int    bbphy_bbp_axislv_active    : 1; /* [2..2] dw_axi_bbyphy����bbp axi slave��active�ź����μĴ����� */
        unsigned int    reserved_5                 : 1; /* [3..3] ������ */
        unsigned int    amon_soc_axislv_active     : 1; /* [4..4] dw_axi_amon����amon_soc slave��active�ź����μĴ����� */
        unsigned int    amon_cpufast_axislv_active : 1; /* [5..5] dw_axi_amon����amon_cpufast slave��active�ź����μĴ����� */
        unsigned int    cs_axislv_active           : 1; /* [6..6] dw_axi_amon����coresight slave��active�ź����μĴ����� */
        unsigned int    reserved_4                 : 1; /* [7..7] ������ */
        unsigned int    mdmacp_axislv_active       : 1; /* [8..8] dw_axi_glb����mdma9 slave��active�ź����μĴ����� */
        unsigned int    appacp_axislv_active       : 1; /* [9..9] dw_axi_glb����mappa9 slave��active�ź����μĴ����� */
        unsigned int    ddrdata_axislv_active      : 1; /* [10..10] dw_axi_glb����mddrc slave��active�ź����μĴ����� */
        unsigned int    axi_mem_axislv_active      : 1; /* [11..11] dw_axi_glb����axi mem slave��active�ź����μĴ����� */
        unsigned int    x2h_peri_axislv_active     : 1; /* [12..12] dw_axi_glb����x2p�� slave��active�ź����μĴ����� */
        unsigned int    bbphy_axislv_active        : 1; /* [13..13] dw_axi_glb����bbephy�� slave��active�ź����μĴ����� */
        unsigned int    x2p_axislv_active          : 1; /* [14..14] dw_axi_glb����x2p�� slave��active�ź����μĴ��� */
        unsigned int    hifi_axislv_active         : 1; /* [15..15] dw_axi_glb����hifi slave��active�ź����μĴ����� */
        unsigned int    dw_axi_amon_axislv_active  : 1; /* [16..16] dw_axi_glb����dw_axi_amon slave��active�ź����μĴ����� */
        unsigned int    cpu_slv_active             : 1; /* [17..17] dw_axi_cpu��slave��active���μĴ�������ddr data actvie��0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    reserved_3                 : 1; /* [18..18] ������ */
        unsigned int    wdog_apbslv_active         : 1; /* [19..19] wdog apb slave��active�ź����μĴ����� */
        unsigned int    timer0_7_apbslv_active     : 1; /* [20..20] timer0_7 apb slave��active�ź����μĴ����� */
        unsigned int    timer8_15_apbslv_active    : 1; /* [21..21] timer8_15 apb slave��active�ź����μĴ����� */
        unsigned int    timer16_23_apbslv_active   : 1; /* [22..22] timer16_23 apb slave��active�ź����μĴ����� */
        unsigned int    reserved_2                 : 1; /* [23..23] ������ */
        unsigned int    gpio0_apbslv_active        : 1; /* [24..24] gpio0 apb slave��active�ź����μĴ����� */
        unsigned int    uart0_apbslv_active        : 1; /* [25..25] uart0 apb slave��active�ź����μĴ����� */
        unsigned int    reserved_1                 : 1; /* [26..26] ������ */
        unsigned int    sci0_apbslv_active         : 1; /* [27..27] sci0 apb slave��active�ź����μĴ����� */
        unsigned int    sci1_apbslv_apbactive      : 1; /* [28..28] sci1 apb slave��active�ź����μĴ����� */
        unsigned int    tsensor_apbslv_active      : 1; /* [29..29] tsensor apb slave��active�ź����μĴ����� */
        unsigned int    usbotg_apbslv_active       : 1; /* [30..30] usbotg apb slave��active�ź����μĴ����� */
        unsigned int    reserved_0                 : 1; /* [31..31] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL103_T;    /* slave active���μĴ���0�� */

typedef union
{
    struct
    {
        unsigned int    cs_slv_active              : 1; /* [0..0] coresight apb slave��active�ź����μĴ��� */
        unsigned int    pmussi0_slv_active         : 1; /* [1..1] pmussi0 apb slave��active�ź����μĴ��� */
        unsigned int    reserved_8                 : 1; /* [2..2] ���� */
        unsigned int    usb_otg_slv_active         : 1; /* [3..3] usb_otg apb slave��active�ź����μĴ��� */
        unsigned int    reserved_7                 : 1; /* [4..4] ���� */
        unsigned int    reserved_6                 : 1; /* [5..5] ���� */
        unsigned int    dwssi0_slv_active          : 1; /* [6..6] dw_ssi0 apb slave��active�ź����μĴ��� */
        unsigned int    gpio1_slv_active           : 1; /* [7..7] gpio1 apb slave��active�ź����μĴ��� */
        unsigned int    gpio2_slv_active           : 1; /* [8..8] gpio2 apb slave��active�ź����μĴ��� */
        unsigned int    gpio3_slv_active           : 1; /* [9..9] gpio3 apb slave��active�ź����μĴ��� */
        unsigned int    reserved_5                 : 1; /* [10..10] ���� */
        unsigned int    uart1_slv_active           : 1; /* [11..11] uart1 apb slave��active�ź����μĴ��� */
        unsigned int    uart2_slv_active           : 1; /* [12..12] uart2 apb slave��active�ź����μĴ��� */
        unsigned int    uart3_slv_active           : 1; /* [13..13] uart3 apb slave��active�ź����μĴ��� */
        unsigned int    i2c0_slv_active            : 1; /* [14..14] i2c0 apb slave��active�ź����μĴ��� */
        unsigned int    i2c1_slv_active            : 1; /* [15..15] i2c1 apb slave��active�ź����μĴ��� */
        unsigned int    mddrc_slv_active           : 1; /* [16..16] mddrc ���ÿ� apb slave��active�ź����μĴ��� */
        unsigned int    efusec_slv_active          : 1; /* [17..17] efusec apb slave��active�ź����μĴ����� */
        unsigned int    reserved_4                 : 1; /* [18..18] ������ */
        unsigned int    dwssi1_slv_active          : 1; /* [19..19] dw_ssi1 apb slave��active�ź����μĴ����� */
        unsigned int    edam_slv_active            : 1; /* [20..20] edma apb slave��active�ź����μĴ����� */
        unsigned int    dt_slv_active              : 1; /* [21..21] dt apb slave��active�ź����μĴ����� */
        unsigned int    edmac_ch4_slv_active       : 1; /* [22..22] edma_ch4 apb slave��active�ź����μĴ����� */
        unsigned int    reserved_3                 : 1; /* [23..23] ������ */
        unsigned int    pcie_phy_slv_active        : 1; /* [24..24] pcie_phy apb slave��active�ź����μĴ����� */
        unsigned int    reserved_2                 : 1; /* [25..25] ������ */
        unsigned int    mipi_slv_active            : 1; /* [26..26] mipi apb slave��active�ź����μĴ����� */
        unsigned int    reserved_1                 : 1; /* [27..27] ������ */
        unsigned int    bbp_ao_slv_active          : 1; /* [28..28] bbp_ao apb slave��active�ź����μĴ����� */
        unsigned int    reserved_0                 : 1; /* [29..29] ������ */
        unsigned int    pwm0_slv_active            : 1; /* [30..30] pwm0 apb slave��active�ź����μĴ����� */
        unsigned int    pwm1_slv_active            : 1; /* [31..31] pwm1 apb slave��active�ź����μĴ���0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL104_T;    /* slave active���μĴ���1�� */

typedef union
{
    struct
    {
        unsigned int    uicc                       : 1; /* [0..0] uicc ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    hsic                       : 1; /* [1..1] hsic ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    reserved_8                 : 1; /* [2..2] ���� */
        unsigned int    emi_reg                    : 1; /* [3..3] emi ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    emi_mem                    : 1; /* [4..4] emi ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    nandc_reg                  : 1; /* [5..5] nandc ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    ipcm                       : 1; /* [6..6] ipcm ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    sio                        : 1; /* [7..7] sio ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    hs_uart                    : 1; /* [8..8] hs uart ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    socp                       : 1; /* [9..9] soc ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    reserved_7                 : 1; /* [10..10] ���� */
        unsigned int    cipher                     : 1; /* [11..11] cipher ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    ipf                        : 1; /* [12..12] ipf ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    mmc0                       : 1; /* [13..13] mmc0 ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    mmc1                       : 1; /* [14..14] mmc1 ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    reserved_6                 : 1; /* [15..15] ���� */
        unsigned int    sdcc                       : 1; /* [16..16] sdcc ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    reserved_5                 : 1; /* [17..17] ���� */
        unsigned int    reserved_4                 : 1; /* [18..18] ���� */
        unsigned int    cicom0                     : 1; /* [19..19] cicom0 ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    cicom1                     : 1; /* [20..20] cicom1 ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    hdlc                       : 1; /* [21..21] hdlc ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    usb3                       : 1; /* [22..22] usb3������ ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    nandc_mem                  : 1; /* [23..23] nandc ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    reserved_3                 : 1; /* [24..24] ���� */
        unsigned int    vic1                       : 1; /* [25..25] vic1 ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    cm3                        : 1; /* [26..26] cm3 ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    reserved_2                 : 1; /* [27..27] ���� */
        unsigned int    reserved_1                 : 1; /* [28..28] ���� */
        unsigned int    upacc                      : 1; /* [29..29] upacc ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
        unsigned int    reserved_0                 : 1; /* [30..30] ���� */
        unsigned int    tcssi1                     : 1; /* [31..31] tcss1 ������ ahb slave��active�ź����μĴ�����0�������Σ�1������active�߼���slave�̶�Ϊ�ɷ���״̬�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL105_T;    /* slave active���μĴ���2�� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL121_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL122_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL123_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL124_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL125_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL126_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL127_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    boot_mode2_0               : 3; /* [2..0] ����ģʽѡ��000��Ƭ��nandflash����001��onchiprom nand/usb����010��onchiprom emmac/usb����011��onchiprom HS_UART����100��onchiprom HSIC��������ֵ������                                              ˵����efuseʹ��1bit��������ģʽ�����庬�������efuse�Ĵ����ֲᡣ    0������boot_mode[3:0]ָʾ����       1���̶���onchiprom���� */
        unsigned int    boot_mode3                 : 1; /* [3..3] USBǿ���Ծ�ָʾ                   0��onchiprom������ǿ��USB�Ծ�     1��onchiprom���������������������boot_mode2_0�����ж�������ʽ */
        unsigned int    reserved_2                 : 4; /* [7..4] ������ */
        unsigned int    jtag_mode0                 : 1; /* [8..8]  */
        unsigned int    jtag_mode1                 : 1; /* [9..9]  */
        unsigned int    reserved_1                 : 1; /* [10..10] ������ */
        unsigned int    jtag_dft_mode              : 1; /* [11..11] JTAG DFTģʽ��0������״̬��Ĭ�ϣ���1��JTAG0��BSD��JTAG1��NO USE�� */
        unsigned int    wdt_rst_n_store            : 1; /* [12..12] ���Ź���λ����״̬0�����Ź���λ��PMU1���޴�bitд1������üĴ������첽��λ���ܣ��ϵ���ʼֵ��ȷ������Ҫ������ϵ��Ը�λд1����λ��¼���ܲſ�����ʹ�� */
        unsigned int    pmu_rst_n_store            : 1; /* [13..13] ϵͳ�����λ����״̬0�������λ��PMU1���޴�bitд1������üĴ������첽��λ���ܣ��ϵ���ʼֵ��ȷ������Ҫ������ϵ��Ը�λд1����λ��¼���ܲſ�����ʹ�� */
        unsigned int    reserved_0                 : 18; /* [31..14] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT0_T;    /* ��λ��¼/����/����ģʽ״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    appa9_pmupriv              : 1; /* [0..0] AppA9״ָ̬ʾ��0���û�ģʽ��1����Ȩģʽ���ñ�����Ϣ��CoreSight�в��ṩ�� */
        unsigned int    appa9_pmusecure            : 1; /* [1..1] AppA9��ȫ״̬��0���ǰ�ȫ״̬��1����ȫ״̬���ñ�����Ϣ��CoreSight�в��ṩ�� */
        unsigned int    appa9_smpnamp              : 1; /* [2..2] AppA9 AMP/SMPģʽ��0�����Գƣ�1���Գơ� */
        unsigned int    appa9_scuevabort           : 1; /* [3..3] �쳣��־�źţ�ָʾ��һ��������ڼ��ⲿ��������ֹ����������CPU���ܼ�أ��������¿������� */
        unsigned int    appa9_pwrctlo0             : 2; /* [5..4] ָʾCPU��ǰ����״̬��0x��CPU0�����ϵ磻10��CPU0���Խ���dormant mode��11��CPU0���Խ���powered-off mode�� */
        unsigned int    appa9_l2_tagclkouten       : 1; /* [6..6] l2 tagclkouten״̬�� */
        unsigned int    appa9_l2_dataclkouten      : 4; /* [10..7] l2 dataclkouten״̬�� */
        unsigned int    appa9_l2_idle              : 1; /* [11..11] l2 idle״̬�� */
        unsigned int    appa9_l2_clkstopped        : 1; /* [12..12] l2 clk_stopped ״̬�� */
        unsigned int    reserved_1                 : 3; /* [15..13] ������ */
        unsigned int    moda9_pmupriv              : 1; /* [16..16] ModA9״ָ̬ʾ��0���û�ģʽ��1����Ȩģʽ���ñ�����Ϣ��CoreSight�в��ṩ�� */
        unsigned int    moda9_pmusecure            : 1; /* [17..17] ModA9��ȫ״̬��0���ǰ�ȫ״̬��1����ȫ״̬���ñ�����Ϣ��CoreSight�в��ṩ�� */
        unsigned int    moda9_smpnamp              : 1; /* [18..18] ModA9 AMP/SMPģʽ��0�����Գƣ�1���Գơ� */
        unsigned int    moda9_scuevabort           : 1; /* [19..19] �쳣��־�źţ�ָʾ��һ��������ڼ��ⲿ��������ֹ����������CPU���ܼ�أ��������¿������ա�0��δ����1���ѷ��� */
        unsigned int    moda9_pwrctlo0             : 2; /* [21..20] CPU��ǰ����״̬��0x��CPU0�����ϵ磻10��CPU0���Խ���dormant mode��11��CPU0���Խ���powered-off mode�� */
        unsigned int    moda9_l2_tagclkouten       : 1; /* [22..22] l2 tagclkouten״̬�� */
        unsigned int    moda9_l2_dataclkouten      : 4; /* [26..23] l2 dataclkouten״̬�� */
        unsigned int    moda9_l2_idle              : 1; /* [27..27] l2 idle״̬�� */
        unsigned int    moda9_l2_clkstopped        : 1; /* [28..28] l2 clk_stopped ״̬�� */
        unsigned int    reserved_0                 : 3; /* [31..29] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT1_T;    /* App/Modem A9״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    hifi_pwaitmode             : 1; /* [0..0] ������˯��״ָ̬ʾ��0��������1��˯�ߡ���DSPִ��WAITIָ��ȴ��ж�ʱ�����ź������κ�û��disable���ж϶��ỽ�Ѵ������� */
        unsigned int    hifi_xocdmode              : 1; /* [1..1] ָʾ����������OCD Haltģʽ��0��������1��OCD Haltģʽ�� */
        unsigned int    appa9_deflags              : 7; /* [8..2] A��deflags״̬�� */
        unsigned int    reserved_1                 : 7; /* [15..9] ������ */
        unsigned int    dsp0_pwaitmode             : 1; /* [16..16] ������˯��״ָ̬ʾ��0��������1��˯�ߡ���DSPִ��WAITIָ��ȴ��ж�ʱ�����ź������κ�û��disable���ж϶��ỽ�Ѵ������� */
        unsigned int    dsp0_xocdmode              : 1; /* [17..17] ָʾ����������OCD Haltģʽ��0��������1��OCD Haltģʽ�� */
        unsigned int    reserved_0                 : 14; /* [31..18] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT2_T;    /* HIFI/dsp0/BBE16 DSP CORE״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    hpm0_opc                   : 10; /* [9..0] hpm0��OPCֵ�� */
        unsigned int    hpm0_opc_vld               : 1; /* [10..10] hpm0��opc��Ч�źš� */
        unsigned int    reserved_1                 : 1; /* [11..11] ������ */
        unsigned int    hpm1_opc                   : 10; /* [21..12] hpm1��OPCֵ�� */
        unsigned int    hpm1_opc_vld               : 1; /* [22..22] hpm1��opc��Ч�źš� */
        unsigned int    reserved_0                 : 9; /* [31..23] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT3_T;    /* hmp״̬�Ĵ���0�� */

typedef union
{
    struct
    {
        unsigned int    hpm2_opc                   : 10; /* [9..0] hpm2��OPCֵ�� */
        unsigned int    hpm2_opc_vld               : 1; /* [10..10] hpm2��opc��Ч�źš� */
        unsigned int    reserved                   : 21; /* [31..11] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT4_T;    /* hmp״̬�Ĵ���1�� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT5_T;    /* �����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    appa9_parityfail0          : 8; /* [7..0] AppA9 RAM����У������0��У��ɹ���1��У��ʧ�ܡ�[7] BTAC parity error[6] GHB[5] Instruction tag RAM[4] Instruction data RAM[3] Main TLB[2] D outer RAM[1] Data tag RAM[0] Data data RAM */
        unsigned int    appa9_parityfailscu        : 1; /* [8..8] AppA9 SCU tag RAMУ������0��У��ɹ���1��У��ʧ�ܡ� */
        unsigned int    reserved_1                 : 3; /* [11..9] ������ */
        unsigned int    moda9_parityfail0          : 8; /* [19..12] A9 RAM����У������0��У��ɹ���1��У��ʧ�ܡ�[7] BTAC parity error[6] GHB[5] Instruction tag RAM[4] Instruction data RAM[3] Main TLB[2] D outer RAM[1] Data tag RAM[0] Data data RAM */
        unsigned int    moda9_parityfailscu        : 1; /* [20..20] SCU tag RAMУ������0��У��ɹ���1��У��ʧ�ܡ� */
        unsigned int    reserved_0                 : 11; /* [31..21] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT6_T;    /* App/Modem A9У��״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT7_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bbp_timer_readcnt          : 32; /* [31..0] BBP��ά�ɲ��������������ÿ�ζԴ˼Ĵ������ж�������ֵ��1������1���� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT8_T;    /* LTE BBP��ά�ɲ���������� */

typedef union
{
    struct
    {
        unsigned int    dw_axi_mst_dlock_wr        : 1; /* [0..0] ���������дָʾ��0������1��д�� */
        unsigned int    dw_axi_mst_dlock_slv       : 1; /* [1..1] ��������master��slave�˿ںš� */
        unsigned int    reserved_3                 : 2; /* [3..2] ������ */
        unsigned int    dw_axi_mst_dlock_mst       : 4; /* [7..4] ������master��С�˿ںš� */
        unsigned int    dw_axi_cpu_dlock_wr        : 1; /* [8..8] ���������дָʾ��0������1��д�� */
        unsigned int    dw_axi_cpu_dlock_slv       : 1; /* [9..9] ��������master��slave�˿ںš� */
        unsigned int    dw_axi_cpu_dlock_mst       : 1; /* [10..10] ������master��С�˿ںš� */
        unsigned int    reserved_2                 : 1; /* [11..11] ������ */
        unsigned int    axi_amon_dlock_wr          : 1; /* [12..12] ���������дָʾ��0������1��д�� */
        unsigned int    axi_amon_dlock_slv         : 3; /* [15..13] ��������master��slave�˿ںš� */
        unsigned int    axi_amon_dlock_mst         : 3; /* [18..16] ������master��С�˿ںš� */
        unsigned int    reserved_1                 : 1; /* [19..19] ������ */
        unsigned int    dw_axi_glb_dlock_wr        : 1; /* [20..20] ���������дָʾ��0������1��д�� */
        unsigned int    dw_axi_glb_dlock_slv       : 4; /* [24..21] ��������master��slave�˿ںš� */
        unsigned int    dw_axi_glb_dlock_mst       : 3; /* [27..25] ������master��С�˿ںš� */
        unsigned int    reserved_0                 : 4; /* [31..28] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT9_T;    /* AXI������״̬�Ĵ���0�� */

typedef union
{
    struct
    {
        unsigned int    dw_axi_glb_dlock_id        : 8; /* [7..0] GLB AXI������ID�� */
        unsigned int    dw_axi_amon_dlock_id       : 12; /* [19..8] AMON AXI������ID�� */
        unsigned int    dw_axi_cpu_dlock_id        : 8; /* [27..20] CPU AXI������ID�� */
        unsigned int    dw_axi_mst_dlock_id        : 4; /* [31..28] MST AXI������ID�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT10_T;    /* AXI������״̬�Ĵ���1�� */

typedef union
{
    struct
    {
        unsigned int    sdcc_pull_stat             : 1; /* [0..0] sdcc��������������״̬0����1������������Ĭ��ֵ�� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT11_T;    /* SDCC����״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    sdcc_pull_raw              : 1; /* [0..0] sdcc��������������仯ԭʼ�ж�״̬0����������״̬�ޱ仯1����������״̬�б仯��bitд1��� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT12_T;    /* SDCC�����仯�ж�״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT13_T;    /* �����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    cr_data_out                : 16; /* [15..0]  */
        unsigned int    cr_ack                     : 1; /* [16..16]  */
        unsigned int    reserved_2                 : 3; /* [19..17]  */
        unsigned int    rtune_ack                  : 1; /* [20..20]  */
        unsigned int    reserved_1                 : 3; /* [23..21]  */
        unsigned int    ref_clkreq_n               : 1; /* [24..24]  */
        unsigned int    reserved_0                 : 7; /* [31..25]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT14_T;    /* usb3PHY״̬�Ĵ���1�� */

typedef union
{
    struct
    {
        unsigned int    sysapb_pslv_active0        : 14; /* [13..0] ������apb slave��active�ź�״̬0��bit[0]��sysctrl����ֵ1��bit[1]��wdogbit[2]��timer0��7bit[3]��timer8��15bit[4]��timer16��23bit[5]��rtc����ֵ1��bit[6]��gpio0bit[7]��uart0bit[8]��synopsys spi0bit[9]��sci0bit[10]��sci1bit[11]��tsensorbit[12]��bc_ctrl                                         bit[13]��crg(��ֵ1) */
        unsigned int    reserved_1                 : 2; /* [15..14]  */
        unsigned int    sysapb_pslv_active1        : 3; /* [18..16] ������apb slave��active�ź�״̬1��bit[0]��ios_pd����ֵ1��bit[1]��ios_ao����ֵ1��bit[2]��efusec����ֵ1�� */
        unsigned int    reserved_0                 : 13; /* [31..19]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT15_T;    /* slave active״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ldrx2dbg_abs_timer_31_0    : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT16_T;    /* lte drx abs_timer״̬�Ĵ���0 */

typedef union
{
    struct
    {
        unsigned int    ldrx2dbg_abs_timer_63_32   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT17_T;    /* lte drx abs_timer״̬�Ĵ���1 */

typedef union
{
    struct
    {
        unsigned int    wdrx_deepsleep_flag        : 1; /* [0..0]  */
        unsigned int    g1_gdrx_deepsleep_falg     : 1; /* [1..1]  */
        unsigned int    g2_gdrx_deepsleep_falg     : 1; /* [2..2]  */
        unsigned int    reserved                   : 29; /* [31..3] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT18_T;    /* gsm deepsleep״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT19_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT20_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    usb3_connect_state_u2pmu   : 1; /* [0..0]  */
        unsigned int    usb3_connect_state_u3pmu   : 1; /* [1..1]  */
        unsigned int    usb3_host_current_belt     : 12; /* [13..2]  */
        unsigned int    reserved_1                 : 2; /* [15..14]  */
        unsigned int    usb3_pmu_current_power_state_u2pmu : 2; /* [17..16]  */
        unsigned int    usb3_pmu_current_power_state_u3pmu : 2; /* [19..18]  */
        unsigned int    usb3_pmu_phy_u2dsport_vbus_ctrl : 1; /* [20..20]  */
        unsigned int    usb3_pmu_phy_u3dsport_vbus_ctrl : 1; /* [21..21]  */
        unsigned int    reserved_0                 : 10; /* [31..22] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT21_T;    /* usb_pd״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dw_axi_bbphy_dlock_mst     : 2; /* [1..0]  */
        unsigned int    dw_axi_bbphy_dlock_slv     : 3; /* [4..2]  */
        unsigned int    dw_axi_bbphy_dlock_wr      : 1; /* [5..5]  */
        unsigned int    reserved_1                 : 2; /* [7..6]  */
        unsigned int    dw_axi_bbphy_dlock_id      : 12; /* [19..8]  */
        unsigned int    reserved_0                 : 12; /* [31..20]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT22_T;    /* AXI������״̬�Ĵ���2�� */

typedef union
{
    struct
    {
        unsigned int    func_mbist_fail            : 32; /* [31..0] func mbist fail״̬�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT23_T;    /* func mbist fail״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    func_mbist_done            : 32; /* [31..0] func mbist done״̬�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT24_T;    /* func mbist done״̬�Ĵ���0�� */

typedef union
{
    struct
    {
        unsigned int    func_mbist_done            : 32; /* [31..0] func mbist done״̬�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT25_T;    /* func mbist done״̬�Ĵ���1�� */

typedef union
{
    struct
    {
        unsigned int    socp_idle                  : 1; /* [0..0] socp�Ƿ����״̬ */
        unsigned int    ipf_idle                   : 1; /* [1..1] ipf�Ƿ����״̬ */
        unsigned int    cicom0_clk_state           : 1; /* [2..2] cicom0�Ƿ����״̬ */
        unsigned int    cicom1_clk_state           : 1; /* [3..3] cicom1�Ƿ����״̬ */
        unsigned int    hdlc_clk_state             : 1; /* [4..4] hdlc�Ƿ����״̬ */
        unsigned int    reserved                   : 27; /* [31..5]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT26_T;    /* master״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bbphy_slv_active           : 4; /* [3..0] dw_axi_bbphy��slave��active�ź�״̬��bit[0]��dw_axi_dspbit[1]��dsp0bit[2]��bbpbit[3]��reserved */
        unsigned int    amon_slv_active            : 3; /* [6..4] axi_amon��slave��active�ź�״̬��bit[4]��socbit[5]��cpu fastbit[6]��core sight */
        unsigned int    reserved_1                 : 1; /* [7..7] ������ */
        unsigned int    glb_slv_active             : 9; /* [16..8] dw_axi_glb��slave��active�ź�״̬��bit[8]��mdm acpbit[9]��app acpbit[10]��ddr databit[11]��axi_membit[12]��x2h_peribit[13]��dw_axi_dspbit[14]��x2p������1��bit[15]��hifibit[16]��stm */
        unsigned int    cpu_slv_active             : 1; /* [17..17] dw_axi_cpu��slave��active״̬����ddr data actvie״̬�� */
        unsigned int    reserved_0                 : 14; /* [31..18] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT27_T;    /* slave active״̬�Ĵ���0�� */

typedef union
{
    struct
    {
        unsigned int    socapb_pslv_active         : 32; /* [31..0] ������apb slave��active�ź�״̬��bit[0]��coresightbit[1]��pmussi0bit[2]�� ����ֵ1��bit[3]��usb othphybit[5:4]������ֵ11��bit[6]��ssi0bit[7]��gpio1bit[8]��gpio2bit[9]��gpio3bit[10]��sys_peri����ֵ1��bit[11]��uart1bit[12]��uart2bit[13]��uart3bit[14]��i2c0bit[15]��i2c1                                       bit[16]��mddrcbit[17]��efusebit[18]��reservedbit[19]��spi_fastbit[20]��edmabit[21]��ashbbit[22]��edma_ch4bit[23]��cm3 ashb����ֵ1��bit[24]��pcie_phybit[25]��reservedbit[26]��mipibit[27]��reservedbit[28]��bbpbit[29]��reservedbit[30]��pwm0                                        bit[31]��pwm1 */
    } bits;
    unsigned int    u32;
}HI_SC_STAT28_T;    /* slave active״̬�Ĵ���1�� */

typedef union
{
    struct
    {
        unsigned int    x2h_peri_slv_active        : 32; /* [31..0] bit[0]��uiccbit[1]��hsicbit[2]��gmacbit[3]��emi���ÿ�bit[4]��emi���ݿ�bit[5]��nandc���ÿ�bit[6]��ipcmbit[7]��siobit[8]��hs_uartbit[9]��socpbit[10]��reservedbit[11]��cipherbit[12]��ipfbit[13]��mmc0bit[14]��mmc1bit[15]��reservedbit[16]��sdccbit[17]��reservedbit[18]��reservedbit[19]��cicom0bit[20]��cicom1bit[21]��hdlcbit[22]��usb3bit[23]��nandc���ݿ�bit[24]��reservedbit[25]��vic1bit[26]��cm3bit[27]��reservedbit[28]��reservedbit[29]��upacc                                          bit[30]��reservedbit[31]��reserved */
    } bits;
    unsigned int    u32;
}HI_SC_STAT29_T;    /* slave active״̬�Ĵ���2�� */

typedef union
{
    struct
    {
        unsigned int    bbp_sys_1control           : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT31_T;    /* bbp_sys_1control״̬�Ĵ���1�� */

typedef union
{
    struct
    {
        unsigned int    lte2soc_tbd                : 16; /* [15..0]  */
        unsigned int    reserved                   : 16; /* [31..16] ���� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT32_T;    /* bbp����״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT33_T;    /* �����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT34_T;    /* �����Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    func_mbist_done_2          : 32; /* [31..0] func mbist done״̬�Ĵ��� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT35_T;    /* func mbist done״̬�Ĵ���2�� */

typedef union
{
    struct
    {
        unsigned int    func_mbist_done_3          : 32; /* [31..0] func mbist done״̬�Ĵ��� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT36_T;    /* func mbist done״̬�Ĵ���3�� */

typedef union
{
    struct
    {
        unsigned int    func_mbist_done_4          : 32; /* [31..0] func mbist done״̬�Ĵ��� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT37_T;    /* func mbist done״̬�Ĵ���4�� */

typedef union
{
    struct
    {
        unsigned int    func_mbist_done_5          : 32; /* [31..0] func mbist done״̬�Ĵ��� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT38_T;    /* func mbist done״̬�Ĵ���5�� */

typedef union
{
    struct
    {
        unsigned int    func_mbist_done_6          : 32; /* [31..0] func mbist done״̬�Ĵ��� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT39_T;    /* func mbist done״̬�Ĵ���6�� */

typedef union
{
    struct
    {
        unsigned int    func_mbist_done_7          : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT40_T;    /* func mbist done״̬�Ĵ���7�� */

typedef union
{
    struct
    {
        unsigned int    bbphy_mst_err              : 8; /* [7..0] dw_axi_bbphy�ŷ��ʴ���Ĵ�����Bit[0]��m1�ڣ�dw_axi_glb��д���ʴ���Bit[1]��m1�ڣ�dw_axi_glb�������ʴ���Bit[2]��m2�ڣ�dsp0��д���ʴ���Bit[3]��m2�ڣ�dsp0�������ʴ���Bit[4]��m3�ڣ�bbp��д���ʴ���Bit[5]��m3�ڣ�bbp�������ʴ���Bit[6]��m4�ڣ�reserved��д���ʴ���Bit[7]��m4�ڣ�reserved�������ʴ��� */
        unsigned int    axi_amon_mst_err           : 1; /* [8..8] axi_amon mst���ʴ���Ĵ����� */
        unsigned int    reserved                   : 7; /* [15..9] ������ */
        unsigned int    cpu_mst_err                : 4; /* [19..16] dw_axi_cpu�ŷ��ʴ���Ĵ�����Bit[0]��app a9 m1��д���ʴ���Bit[1]��app a9 m1�ڶ����ʴ����ַBit[2]��mdm a9 m1��д���ʴ���Bit[3]��mdm a9 m1�ڶ����ʴ��� */
        unsigned int    glb_mst_err                : 12; /* [31..20] dw_axi_glb�ŷ��ʴ���Ĵ�����Bit[0]��m1�ڣ�dw_axi_bbphy��д���ʴ���Bit[1]��m1�ڣ�dw_axi_bbphy�������ʴ���Bit[2]��m2�ڣ�dw_axi_mst��д���ʴ���Bit[3]��m2�ڣ�dw_axi_mst�������ʴ���Bit[4]��m3�ڣ�app a9 m0�ڣ�д���ʴ���Bit[5]��m3�ڣ�app a9 m0�ڣ������ʴ���Bit[6]��m4�ڣ�mdm a9 m0�ڣ�д���ʴ���Bit[7]��m4�ڣ�mdm a9 m0�ڣ������ʴ���Bit[8]��m5�ڣ�reserved��д���ʴ���Bit[9]��m5�ڣ�reserved�������ʴ���Bit[10]��m6�ڣ�hifi��д���ʴ���Bit[11]��m6�ڣ�hifi�������ʴ��� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT41_T;    /* master���ʴ���״̬�Ĵ���0�� */

typedef union
{
    struct
    {
        unsigned int    sysapb_psel_err            : 1; /* [0..0] soc���賣����apb������ʴ���״̬�� */
        unsigned int    socapb_psel_err            : 1; /* [1..1] soc���������apb������ʴ���״̬�� */
        unsigned int    x2h_peri_mst_err           : 1; /* [2..2] ahb������ʴ���״̬�� */
        unsigned int    reserved                   : 29; /* [31..3] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT42_T;    /* master���ʴ���״̬�Ĵ���1�� */

typedef union
{
    struct
    {
        unsigned int    x2h_peri_addr_err          : 32; /* [31..0] ahb������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT43_T;    /* ahb������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 12; /* [11..0] ������ */
        unsigned int    addr_err                   : 20; /* [31..12] soc���������apb������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT44_T;    /* soc���������apb������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 12; /* [11..0] ������ */
        unsigned int    reserved_0                 : 20; /* [31..12] soc���賣����apb������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT45_T;    /* soc���賣����apb������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m1�ڣ�dw_axi_bbphy��д���ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT46_T;    /* glb��m1�ڣ�dw_axi_bbphy��д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m1�ڣ�dw_axi_bbphy�������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT47_T;    /* glb��m1�ڣ�dw_axi_bbphy�������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m2�ڣ�dw_axi_mst��д���ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT48_T;    /* glb��m2�ڣ�dw_axi_mst��д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m2�ڣ�dw_axi_mst�������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT49_T;    /* glb��m2�ڣ�dw_axi_mst�������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m3�ڣ�app a9 m0�ڣ�д���ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT50_T;    /* glb��m3�ڣ�app a9 m0�ڣ�д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m3�ڣ�app a9 m0�ڣ������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT51_T;    /* glb��m3�ڣ�app a9 m0�ڣ������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m4�ڣ�mdm a9 m0�ڣ�д���ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT52_T;    /* glb��m4�ڣ�mdm a9 m0�ڣ�д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m4�ڣ�mdm a9 m0�ڣ������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT53_T;    /* glb��m4�ڣ�mdm a9 m0�ڣ������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m5�ڣ�reserved��д���ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT54_T;    /* glb��m5�ڣ�reserved��д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m5�ڣ�reserved�������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT55_T;    /* glb��m5�ڣ�reserved�������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m6�ڣ�hifi��д���ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT56_T;    /* glb��m6�ڣ�hifi��д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] glb��m6�ڣ�hifi�������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT57_T;    /* glb��m6�ڣ�hifi�������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] cpu��m1�ڣ�app a9 m1�ڣ������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT58_T;    /* cpu��m1�ڣ�app a9 m1�ڣ������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] cpu��m2�ڣ�mdm a9 m1�ڣ������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT59_T;    /* cpu��m2�ڣ�mdm a9 m1�ڣ������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] cpu��m1�ڣ�app a9 m1�ڣ�д���ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT60_T;    /* cpu��m1�ڣ�app a9 m1�ڣ�д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] cpu��m2�ڣ�mdm a9 m1�ڣ�д���ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT61_T;    /* cpu��m2�ڣ�mdm a9 m1�ڣ�д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] bbphy��m1�ڣ�dw_axi_glb��д���ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT62_T;    /* bbphy��m1�ڣ�dw_axi_glb��д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] bbphy��m1�ڣ�dw_axi_glb�������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT63_T;    /* bbphy��m1�ڣ�dw_axi_glb�������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] bbphy��m2�ڣ�dsp0��д���ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT64_T;    /* bbphy��m2�ڣ�dsp0��д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] bbphy��m2�ڣ�dsp0�������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT65_T;    /* bbphy��m2�ڣ�dsp0�������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] bbphy��m3�ڣ�bbp��д���ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT66_T;    /* bbphy��m3�ڣ�bbp��д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] bbphy��m3�ڣ�bbp�������ʴ����ַ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT67_T;    /* bbphy��m3�ڣ�bbp�������ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] axi_amon_m1д���ʴ����ַ�Ĵ������� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT68_T;    /* axi_amon��m1д���ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    addr_err                   : 32; /* [31..0] axi_amon_m1�����ʴ����ַ�Ĵ������� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT69_T;    /* axi_amon��m1�����ʴ����ַ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pcie_gm_cmposer_lookup_err : 1; /* [0..0] PCIe��X1����������Master Response Composer Lookup Error.Indicates that an overflow that occurred in a lookup table ofthe outbound responses. This indicates that there was a violation for thenumber of outstanding Non-Posted requests issued for the inbounddirection.0����Ч��1����Ч�� */
        unsigned int    pcie_radmx_cmposer_lookup_err : 1; /* [1..1] PCIe��X1����������Slave Response Composer Lookup Error��Indicates that an overflow that occurred in a lookup table ofthe inbound responses. This indicates that there was a violation for thenumber of outstanding Non-Posted requests issued for the outbounddirection��0����Ч��1����Ч�� */
        unsigned int    pcie_pm_xtlh_block_tlp     : 1; /* [2..2] PCIe��X1�������������ڵ�ǰ�ĵ͹���״̬��֪ͨӦ�ò����ֹͣ�����µ�TLPs����Ӧ�ò���Լ�������Completion TLPs��0����Ч��1����Ч�� */
        unsigned int    pcie_cfg_mem_space_en      : 1; /* [3..3] PCIe��X1����������PCI-compatible����Ĵ����е�Memory Space Enable bitλ��״̬��0����Ч��1����Ч�� */
        unsigned int    pcie_cfg_rcb               : 1; /* [4..4] PCIe��X1����������Link���ƼĴ����е�RCB bitλ��0����Ч��1����Ч�� */
        unsigned int    pcie_rdlh_link_up          : 1; /* [5..5] PCIe��X1��������������Link�� up/down ָʾ��0��link down��1��link up�� */
        unsigned int    pcie_pm_curnt_state        : 3; /* [8..6] PCIe��X1����������������ǰ�ĵ�Դ״̬�� */
        unsigned int    pcie_cfg_aer_rc_err_int    : 1; /* [9..9] PCIe��X1����������һ���������������Root Error Status�Ĵ����е�ĳһbit��λ�����Ҷ�Ӧ��Root Error Command�Ĵ����е�ʹ��bit��Ч����ô����Ч����źţ�0����Ч��1����Ч�� */
        unsigned int    pcie_cfg_aer_int_msg_num   : 5; /* [14..10] PCIe��X1����������MSI����MSI-Xʹ�ܵ�ʱ�����Ч��������Root Error Status��[31��27]bit�� */
        unsigned int    pcie_xmlh_link_up          : 1; /* [15..15] PCIe��X1����������PHY Link up/down ָʾ��0��link down��1��link up�� */
        unsigned int    pcie_wake                  : 1; /* [16..16] PCIe��X1���������������źţ����ڴӵ͹��ĵĵ�Դ״̬ */
        unsigned int    pcie_cfg_eml_control       : 1; /* [17..17] PCIe��X1����������Electromechanical Interlock Control. The state ofthe Electromechanical Interlock Control bit in the SlotControl register�� */
        unsigned int    pcie_hp_pme                : 1; /* [18..18] PCIe��X1����������������������Ч��ʱ��Core��Чhp_pme��The PME Enable bit in the Power Management Controland Status register is set to 1.Any bit in the Slot Status register transitions from 0 to 1and the associated event notification is enabled in theSlot Control register�� */
        unsigned int    pcie_hp_int                : 1; /* [19..19] PCIe��X1�������������������������ʱ�򣬴��ź���Ч��The INTx Assertion Disable bit in the Command registeris 0.Hot-Plug interrupts are enabled in the Slot Controlregister.Any bit in the Slot Status register is equal to 1, and theassociated event notification is enabled in the SlotControl register�� */
        unsigned int    pcie_hp_msi                : 1; /* [20..20] PCIe��X1�������������������������Ч��ʱ�򣬴��ź���Ч��һ��cycle�����壩MSI or MSI-X is enabled��Hot-Plug interrupts are enabled in the Slot Controlregister.Any bit in the Slot Status register transitions from 0 to 1and the associated event notification is enabled in theSlot Control register�� */
        unsigned int    pcie_pm_status             : 1; /* [21..21] PCIe1��X2����������PMCSR��PME״̬λ��0����Ч��1����Ч�� */
        unsigned int    pcie_ref_clk_req_n         : 1; /* [22..22] PCIe1��X2�����������ο�ʱ���Ƴ������źš�0����Ч��1����Ч�� */
        unsigned int    mac_phy_powerdown_p2_exit_reg : 1; /* [23..23] mac_phy_powerdown_p2_exit�ж�״̬ */
        unsigned int    radm_msg_req_id_low        : 8; /* [31..24] radm_msg_req_id[7:0]�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT70_T;    /* PCIE ������״̬�Ĵ���0 */

typedef union
{
    struct
    {
        unsigned int    axi_parity_errs_reg        : 4; /* [3..0] ָʾ��ǰPCIe��������AXI bridge�ĵ�ַ�����ϼ�⵽һ����ż����[3]����client1_addrͨ���ϼ�⵽һ����ż����[2]����radmx_addrͨ���ϼ�⵽һ����ż����[1]����slv_req_addrͨ���ϼ�⵽һ����ż����[0]����mstr_req_addrͨ���ϼ�⵽һ����ż���� */
        unsigned int    app_parity_errs_reg        : 3; /* [6..4] ָʾ��ǰPCIe�������ڲ���⵽һ����ż����[6]����XTLHͨ���ϼ�⵽һ����ż����[5]����XADMͨ���ϼ�⵽һ����ż����[4]����RADMͨ���ϼ�⵽һ����ż���� */
        unsigned int    pm_linkst_in_l1            : 1; /* [7..7] ָʾ��ǰ���ڵ�ԴL1״̬ */
        unsigned int    pm_linkst_in_l2            : 1; /* [8..8] ָʾ��ǰ���ڵ�ԴL2״̬ */
        unsigned int    pm_linkst_l2_exit          : 1; /* [9..9] ָʾ��Դ�����˳�L2״̬ */
        unsigned int    mac_phy_power_down         : 2; /* [11..10] ָʾPCIe��������ǰ����PHY��PM״̬00��P0��L0������״̬��ȫ����״̬��01��P0s��L0s���ڵ�״̬���ָ�������״̬ʱ��̣�10��P1��L1�����ͽڵ�״̬���ָ�������״̬ʱ�䳤��11��P2��L2����ͽڵ�״̬�� */
        unsigned int    radm_correctabl_err_reg    : 1; /* [12..12] ָʾPCIe��������ǰ�յ�һ��ERR_COR��Ϣ */
        unsigned int    radm_nonfatal_err_reg      : 1; /* [13..13] ָʾPCIe��������ǰ�յ�һ��ERR_NONFATAL��Ϣ */
        unsigned int    radm_fatal_err_reg         : 1; /* [14..14] ָʾPCIe��������ǰ�յ�һ��ERR_FATAL��Ϣ */
        unsigned int    radm_pm_to_pme_reg         : 1; /* [15..15] ָʾPCIe��������ǰ�յ�һ��PME_PM��Ϣ */
        unsigned int    radm_pm_to_ack_reg         : 1; /* [16..16] ָʾPCIe��������ǰ�յ�һ��PME_TO_ACK��Ϣ */
        unsigned int    radm_cpl_timeout_reg       : 1; /* [17..17] ָʾPCIe��������ǰ��⵽cpl_timeout */
        unsigned int    radm_msg_unlock_reg        : 1; /* [18..18] ָʾPCIe��������ǰ�յ�һ��MSG_UNLOCK��Ϣ */
        unsigned int    cfg_pme_msi_reg            : 1; /* [19..19] ����������������MSI/MSI-X��ЧRoot Control�Ĵ�����ӦPME Enable bit��ЧRoot Status�Ĵ�����ӦPME bit��Ч */
        unsigned int    bridge_flush_not_reg       : 1; /* [20..20] ָʾPCIe�������Ĵ���graceful��λ״̬ */
        unsigned int    link_req_rst_not_reg       : 1; /* [21..21] ָʾPCIe��������⵽��·�쳣�󣬽���link down�������Զ���λ״̬ */
        unsigned int    pcie_cfg_aer_rc_err_msi    : 1; /* [22..22] PCIe��X1��������������������������ʱ����Ч����ź�һ��ʱ��cycleMSI or MSI-X is enabled.A reported error condition causes a bit to be set in theRoot Error Status register.The associated error message reporting enable bit isset in the Root Error Command register. */
        unsigned int    pcie_cfg_sys_err_rc        : 1; /* [23..23] PCIe��X1����������������⵽ϵͳ����һ��ʱ��cycle�����塣0����Ч��1����Ч�� */
        unsigned int    radm_msg_req_id_high       : 8; /* [31..24] radm_msg_req_id[15:8]�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT71_T;    /* PCIE ������״̬�Ĵ���1 */

typedef union
{
    struct
    {
        unsigned int    pcie_stat2                 : 32; /* [31..0] �üĴ�������PCIE_CTRL8[6:5](pcie_stat2_sel)�Ĳ�ֵͬ������ͬ��״̬��Ϣ�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT72_T;    /* PCIE ������״̬�Ĵ���2 */

typedef union
{
    struct
    {
        unsigned int    pcie_stat3                 : 32; /* [31..0] �üĴ�������PCIE_CTRL8[8:7](pcie_stat3_sel)�Ĳ�ֵͬ������ͬ��״̬��Ϣ�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT73_T;    /* PCIE ������״̬�Ĵ���3 */

typedef union
{
    struct
    {
        unsigned int    ltssm_state                : 6; /* [5..0] ָʾ��ǰPCIe������ltssm״̬link up�ɹ���״̬�ǣ�0x11 */
        unsigned int    mac_phy_rate               : 2; /* [7..6] ָʾ��ǰPCIe������������00��2.5Gbps01:5.0Gbps10:8.0Gbps */
        unsigned int    pcie_slv_err_int           : 1; /* [8..8] PCIe������AXI slave�����ж� */
        unsigned int    trgt_lookup_empty          : 1; /* [9..9] TARGET���ұ��ָʾ */
        unsigned int    trgt_cpl_timeout_reg       : 1; /* [10..10] TARGET��ɰ���ʱ�ж�״̬�� */
        unsigned int    reserved                   : 21; /* [31..11] ���� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT74_T;    /* PCIE ������״̬�Ĵ���4 */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] PCIE PHY״̬�Ĵ��� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT75_T;    /* PCIE PHY״̬�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    obff_dec_idle_intr_status  : 1; /* [0..0] obff_dec_idle�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    obff_dec_obff_intr_status  : 1; /* [1..1] obff_dec_obff�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    obff_dec_cpu_active_intr_status : 1; /* [2..2] obff_dec_cpu_active�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    obff_dec_err_intr_status   : 1; /* [3..3] obff_dec_err�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    obff_msg_idle_intr_status  : 1; /* [4..4] obff_msg_idle�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    obff_msg_obff_intr_status  : 1; /* [5..5] obff_msg_obff�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    obff_msg_cpu_active_intr_status : 1; /* [6..6] obff_msg_cpu_active�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    radm_msg_ltr_intr_status   : 1; /* [7..7] radm_msg_ltr�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    cfg_msi_mask_chg_intr_status : 1; /* [8..8] cfg_msi_mask_chg�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    radm_qoverflow_intr_status : 1; /* [9..9] radm_qoverflow�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    amba_ordr_intr_status      : 1; /* [10..10] amba_ordr�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    pcie_clkreq_in_n_intr_status : 1; /* [11..11] pcie_clkreq_in_n�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    pcie_clkreq_in_n_inv_intr_status : 1; /* [12..12] pcie_clkreq_in_n_inv�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    radm_vendor_msg_intr_status : 1; /* [13..13] radm_vendor_msg�ж�״̬λ��0:���жϣ�1:���жϡ� */
        unsigned int    mac_phy_rxelecidle_disable : 1; /* [14..14] PIPE�ӿ��ź�mac_phy_rxelecidle_disableʵʱ״̬�� */
        unsigned int    mac_phy_txcommonmode_disable : 1; /* [15..15] PIPE�ӿ��ź�mac_phy_txcommonmode_disableʵʱ״̬�� */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT76_T;    /* PCIE ������״̬�Ĵ���5 */

typedef union
{
    struct
    {
        unsigned int    obff_dec_owrd_cur_state    : 4; /* [3..0] OBFF�������ӿ��ź�obff_dec_owrd_cur_stateʵʱ״̬�� */
        unsigned int    obff_enc_owre_cur_state    : 4; /* [7..4] OBFF�������ӿ��ź�obff_enc_owre_cur_stateʵʱ״̬�� */
        unsigned int    cfg_obff_en                : 2; /* [9..8] DM�ӿ��ź�cfg_obff_enʵʱ״̬�� */
        unsigned int    cfg_ltr_m_en               : 1; /* [10..10] DM�ӿ��ź�cfg_ltr_m_enʵʱ״̬�� */
        unsigned int    cfg_pwr_budget_sel         : 1; /* [11..11] DM�ӿ��ź�cfg_pwr_budget_selʵʱ״̬�� */
        unsigned int    smlh_in_rl0s               : 1; /* [12..12] DM�ӿ��ź�smlh_in_rl0sʵʱ״̬�� */
        unsigned int    radm_qoverflow             : 1; /* [13..13] DM�ӿ��ź�radm_qoverflowʵʱ״̬�� */
        unsigned int    amba_ordr_mgr_wdt_int      : 1; /* [14..14] DM�ӿ��ź�amba_ordr_mgr_wdt_intʵʱ״̬�� */
        unsigned int    reserved                   : 17; /* [31..15] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT77_T;    /* PCIE ������״̬�Ĵ���6 */

typedef union
{
    struct
    {
        unsigned int    cfg_msi_mask               : 32; /* [31..0] DM�ӿ��ź�cfg_msi_maskʵʱ״̬�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT78_T;    /* PCIE ������״̬�Ĵ���7 */

typedef union
{
    struct
    {
        unsigned int    cfg_ltr_max_latency        : 32; /* [31..0] DM�ӿ��ź�cfg_ltr_max_latencyʵʱ״̬�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT79_T;    /* PCIE ������״̬�Ĵ���8 */

typedef union
{
    struct
    {
        unsigned int    cm3_brch_stat              : 4; /* [3..0] branch state�� */
        unsigned int    cm3_core_halted            : 1; /* [4..4] m3 core ����debug״̬�� */
        unsigned int    cm3_lockup                 : 1; /* [5..5] m3 core ����lockup״̬�� */
        unsigned int    reserved_1                 : 2; /* [7..6] ������ */
        unsigned int    cm3_cur_int_priority       : 8; /* [15..8] nvic current int priority�� */
        unsigned int    reserved_0                 : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT80_T;    /* m3״̬�Ĵ���0�� */

typedef union
{
    struct
    {
        unsigned int    m3_stat1                   : 32; /* [31..0] m3�ڲ�״̬�Ĵ���1�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT81_T;    /* m3״̬�Ĵ���1�� */

typedef union
{
    struct
    {
        unsigned int    m3_stat2                   : 32; /* [31..0] m3�ڲ�״̬�Ĵ���2�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT82_T;    /* m3״̬�Ĵ���2�� */

typedef union
{
    struct
    {
        unsigned int    m3_stat3                   : 32; /* [31..0] m3�ڲ�״̬�Ĵ���3�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT83_T;    /* m3״̬�Ĵ���3�� */

typedef union
{
    struct
    {
        unsigned int    m3_stat4                   : 32; /* [31..0] m3�ڲ�״̬�Ĵ���4�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT84_T;    /* m3״̬�Ĵ���4�� */

typedef union
{
    struct
    {
        unsigned int    m3_stat5                   : 21; /* [20..0] m3�ڲ�״̬�Ĵ���5�� */
        unsigned int    reserved                   : 11; /* [31..21] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_STAT85_T;    /* m3״̬�Ĵ���5�� */

typedef union
{
    struct
    {
        unsigned int    efuse_tsensor_trim         : 32; /* [31..0]  */
    } bits;
    unsigned int    u32;
}HI_SC_STAT86_T;    /* tsensor trim�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    app_ltr_latency            : 32; /* [31..0] DM�ӿ��ź�app_ltr_latencyʵʱ״̬�� */
    } bits;
    unsigned int    u32;
}HI_SC_STAT87_T;    /* PCIE ������״̬�Ĵ���9 */

typedef union
{
    struct
    {
        unsigned int    version_id                 : 32; /* [31..0] оƬ�汾�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_VERSION_ID_T;    /* оƬ�汾�Ĵ����� */


/********************************************************************************/
/*    syssc_ao ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_sc_ctrl0_remap_clear,remap_clear,HI_SC_CTRL0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL0_OFFSET)
HI_SET_GET(hi_sc_ctrl0_m3_remap_clear,m3_remap_clear,HI_SC_CTRL0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL0_OFFSET)
HI_SET_GET(hi_sc_ctrl0_reserved_1,reserved_1,HI_SC_CTRL0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL0_OFFSET)
HI_SET_GET(hi_sc_ctrl0_remap_stat,remap_stat,HI_SC_CTRL0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL0_OFFSET)
HI_SET_GET(hi_sc_ctrl0_cm3_remap_stat,cm3_remap_stat,HI_SC_CTRL0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL0_OFFSET)
HI_SET_GET(hi_sc_ctrl0_reserved_0,reserved_0,HI_SC_CTRL0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL0_OFFSET)
HI_SET_GET(hi_sc_ctrl1_pmu_rstout_n,pmu_rstout_n,HI_SC_CTRL1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL1_OFFSET)
HI_SET_GET(hi_sc_ctrl1_pmu_hold,pmu_hold,HI_SC_CTRL1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL1_OFFSET)
HI_SET_GET(hi_sc_ctrl1_pmu_irq_mask,pmu_irq_mask,HI_SC_CTRL1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL1_OFFSET)
HI_SET_GET(hi_sc_ctrl1_pmu_irq_n_pos_sel,pmu_irq_n_pos_sel,HI_SC_CTRL1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL1_OFFSET)
HI_SET_GET(hi_sc_ctrl1_efuse_sys_ctrl_en,efuse_sys_ctrl_en,HI_SC_CTRL1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL1_OFFSET)
HI_SET_GET(hi_sc_ctrl1_wdt_reset_sel,wdt_reset_sel,HI_SC_CTRL1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL1_OFFSET)
HI_SET_GET(hi_sc_ctrl1_reserved_1,reserved_1,HI_SC_CTRL1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL1_OFFSET)
HI_SET_GET(hi_sc_ctrl1_usbphy_tcxo_buff_ctrl,usbphy_tcxo_buff_ctrl,HI_SC_CTRL1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL1_OFFSET)
HI_SET_GET(hi_sc_ctrl1_reserved_0,reserved_0,HI_SC_CTRL1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL1_OFFSET)
HI_SET_GET(hi_sc_ctrl2_wdt_clk_en,wdt_clk_en,HI_SC_CTRL2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL2_OFFSET)
HI_SET_GET(hi_sc_ctrl2_reserved_1,reserved_1,HI_SC_CTRL2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL2_OFFSET)
HI_SET_GET(hi_sc_ctrl2_wdt_en_ov,wdt_en_ov,HI_SC_CTRL2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL2_OFFSET)
HI_SET_GET(hi_sc_ctrl2_reserved_0,reserved_0,HI_SC_CTRL2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL2_OFFSET)
HI_SET_GET(hi_sc_ctrl2_wdt_en_ctrl,wdt_en_ctrl,HI_SC_CTRL2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL2_OFFSET)
HI_SET_GET(hi_sc_ctrl3_lcd_rst_n,lcd_rst_n,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_emi_sel,emi_sel,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_zsi_en,zsi_en,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_sio_master_mode,sio_master_mode,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_mmc0_sample_tuning_enable,mmc0_sample_tuning_enable,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_mmc1_sample_tuning_enable,mmc1_sample_tuning_enable,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_mmc_msc,mmc_msc,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_ssp0_mode,ssp0_mode,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_ssp1_mode,ssp1_mode,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_amon_cpufast_monitor_start,amon_cpufast_monitor_start,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_amon_soc_monitor_start,amon_soc_monitor_start,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_pmussi0_mst_cnt,pmussi0_mst_cnt,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_reserved_2,reserved_2,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_dsp0_uart_en,dsp0_uart_en,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_hifi_uart_en,hifi_uart_en,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_reserved_1,reserved_1,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_reserved_0,reserved_0,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl3_test_clk_en,test_clk_en,HI_SC_CTRL3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL3_OFFSET)
HI_SET_GET(hi_sc_ctrl4_cicom0_sel_mod,cicom0_sel_mod,HI_SC_CTRL4_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL4_OFFSET)
HI_SET_GET(hi_sc_ctrl4_cicom1_sel_mod,cicom1_sel_mod,HI_SC_CTRL4_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL4_OFFSET)
HI_SET_GET(hi_sc_ctrl4_reserved,reserved,HI_SC_CTRL4_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL4_OFFSET)
HI_SET_GET(hi_sc_ctrl5_reserved,reserved,HI_SC_CTRL5_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL5_OFFSET)
HI_SET_GET(hi_sc_ctrl5_sw_appa9_boot_addr,sw_appa9_boot_addr,HI_SC_CTRL5_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL5_OFFSET)
HI_SET_GET(hi_sc_ctrl6_reserved,reserved,HI_SC_CTRL6_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL6_OFFSET)
HI_SET_GET(hi_sc_ctrl6_sw_modema9_boot_addr,sw_modema9_boot_addr,HI_SC_CTRL6_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL6_OFFSET)
HI_SET_GET(hi_sc_ctrl7_appa9_remap_size,appa9_remap_size,HI_SC_CTRL7_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL7_OFFSET)
HI_SET_GET(hi_sc_ctrl7_mdma9_remap_size,mdma9_remap_size,HI_SC_CTRL7_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL7_OFFSET)
HI_SET_GET(hi_sc_ctrl7_reserved,reserved,HI_SC_CTRL7_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL7_OFFSET)
HI_SET_GET(hi_sc_ctrl8_reserved,reserved,HI_SC_CTRL8_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL8_OFFSET)
HI_SET_GET(hi_sc_ctrl8_sw_hifi_boot_addr,sw_hifi_boot_addr,HI_SC_CTRL8_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL8_OFFSET)
HI_SET_GET(hi_sc_ctrl9_reserved,reserved,HI_SC_CTRL9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL9_OFFSET)
HI_SET_GET(hi_sc_ctrl9_sw_dsp0_boot_addr,sw_dsp0_boot_addr,HI_SC_CTRL9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL9_OFFSET)
HI_SET_GET(hi_sc_ctrl10_reserved_3,reserved_3,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_cfgnmfi,appa9_cfgnmfi,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_cfgsdisable,appa9_cfgsdisable,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_cp15sdisable,appa9_cp15sdisable,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_pwrctli0,appa9_pwrctli0,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_spiden,appa9_spiden,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_spniden,appa9_spniden,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_niden,appa9_niden,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_dbgen,appa9_dbgen,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_eventi_cfg,appa9_eventi_cfg,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_reserved_2,reserved_2,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_l2_spniden,appa9_l2_spniden,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_reserved_1,reserved_1,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_l2_waysize,appa9_l2_waysize,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_reserved_0,reserved_0,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl10_appa9_l2_regfilebase,appa9_l2_regfilebase,HI_SC_CTRL10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL10_OFFSET)
HI_SET_GET(hi_sc_ctrl11_reserved_3,reserved_3,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_cfgnmfi,moda9_cfgnmfi,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_cfgsdisable,moda9_cfgsdisable,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_cp15sdisable,moda9_cp15sdisable,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_pwrctli0,moda9_pwrctli0,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_spiden,moda9_spiden,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_spniden,moda9_spniden,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_niden,moda9_niden,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_dbgen,moda9_dbgen,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_eventi_cfg,moda9_eventi_cfg,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_reserved_2,reserved_2,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_l2_spniden,moda9_l2_spniden,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_reserved_1,reserved_1,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_l2_waysize,moda9_l2_waysize,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_reserved_0,reserved_0,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl11_moda9_l2_regfilebase,moda9_l2_regfilebase,HI_SC_CTRL11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL11_OFFSET)
HI_SET_GET(hi_sc_ctrl12_hifi_ocdhaltonreset,hifi_ocdhaltonreset,HI_SC_CTRL12_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL12_OFFSET)
HI_SET_GET(hi_sc_ctrl12_hifi_runstall,hifi_runstall,HI_SC_CTRL12_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL12_OFFSET)
HI_SET_GET(hi_sc_ctrl12_hifi_statvectorsel,hifi_statvectorsel,HI_SC_CTRL12_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL12_OFFSET)
HI_SET_GET(hi_sc_ctrl12_hifi_breaksync_en,hifi_breaksync_en,HI_SC_CTRL12_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL12_OFFSET)
HI_SET_GET(hi_sc_ctrl12_hifi_crosstrig_en,hifi_crosstrig_en,HI_SC_CTRL12_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL12_OFFSET)
HI_SET_GET(hi_sc_ctrl12_reserved_1,reserved_1,HI_SC_CTRL12_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL12_OFFSET)
HI_SET_GET(hi_sc_ctrl12_reserved_0,reserved_0,HI_SC_CTRL12_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL12_OFFSET)
HI_SET_GET(hi_sc_ctrl13_reserved_1,reserved_1,HI_SC_CTRL13_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL13_OFFSET)
HI_SET_GET(hi_sc_ctrl13_dsp0_ocdhaltonreset,dsp0_ocdhaltonreset,HI_SC_CTRL13_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL13_OFFSET)
HI_SET_GET(hi_sc_ctrl13_dsp0_runstall,dsp0_runstall,HI_SC_CTRL13_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL13_OFFSET)
HI_SET_GET(hi_sc_ctrl13_dsp0_statvectorsel,dsp0_statvectorsel,HI_SC_CTRL13_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL13_OFFSET)
HI_SET_GET(hi_sc_ctrl13_dsp0_breaksync_en,dsp0_breaksync_en,HI_SC_CTRL13_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL13_OFFSET)
HI_SET_GET(hi_sc_ctrl13_dsp0_crosstrig_en,dsp0_crosstrig_en,HI_SC_CTRL13_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL13_OFFSET)
HI_SET_GET(hi_sc_ctrl13_reserved_0,reserved_0,HI_SC_CTRL13_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL13_OFFSET)
HI_SET_GET(hi_sc_ctrl14_reserved,reserved,HI_SC_CTRL14_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL14_OFFSET)
HI_SET_GET(hi_sc_ctrl15_cm3_fix_mst_type,cm3_fix_mst_type,HI_SC_CTRL15_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL15_OFFSET)
HI_SET_GET(hi_sc_ctrl15_cm3_dap_en,cm3_dap_en,HI_SC_CTRL15_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL15_OFFSET)
HI_SET_GET(hi_sc_ctrl15_cm3_ts_clk_chg,cm3_ts_clk_chg,HI_SC_CTRL15_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL15_OFFSET)
HI_SET_GET(hi_sc_ctrl15_cm3_mpu_disable,cm3_mpu_disable,HI_SC_CTRL15_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL15_OFFSET)
HI_SET_GET(hi_sc_ctrl15_cm3_dbgen,cm3_dbgen,HI_SC_CTRL15_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL15_OFFSET)
HI_SET_GET(hi_sc_ctrl15_cm3_eventi_cfg,cm3_eventi_cfg,HI_SC_CTRL15_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL15_OFFSET)
HI_SET_GET(hi_sc_ctrl15_reserved,reserved,HI_SC_CTRL15_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL15_OFFSET)
HI_SET_GET(hi_sc_ctrl16_cm3_stcalib,cm3_stcalib,HI_SC_CTRL16_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL16_OFFSET)
HI_SET_GET(hi_sc_ctrl16_reserved,reserved,HI_SC_CTRL16_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL16_OFFSET)
HI_SET_GET(hi_sc_ctrl17_hpm0_clk_div,hpm0_clk_div,HI_SC_CTRL17_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL17_OFFSET)
HI_SET_GET(hi_sc_ctrl17_reserved_3,reserved_3,HI_SC_CTRL17_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL17_OFFSET)
HI_SET_GET(hi_sc_ctrl17_hpm0_en,hpm0_en,HI_SC_CTRL17_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL17_OFFSET)
HI_SET_GET(hi_sc_ctrl17_hpm1_clk_div,hpm1_clk_div,HI_SC_CTRL17_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL17_OFFSET)
HI_SET_GET(hi_sc_ctrl17_reserved_2,reserved_2,HI_SC_CTRL17_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL17_OFFSET)
HI_SET_GET(hi_sc_ctrl17_hpm1_en,hpm1_en,HI_SC_CTRL17_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL17_OFFSET)
HI_SET_GET(hi_sc_ctrl17_hpm2_clk_div,hpm2_clk_div,HI_SC_CTRL17_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL17_OFFSET)
HI_SET_GET(hi_sc_ctrl17_reserved_1,reserved_1,HI_SC_CTRL17_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL17_OFFSET)
HI_SET_GET(hi_sc_ctrl17_hpm2_en,hpm2_en,HI_SC_CTRL17_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL17_OFFSET)
HI_SET_GET(hi_sc_ctrl17_reserved_0,reserved_0,HI_SC_CTRL17_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL17_OFFSET)
HI_SET_GET(hi_sc_ctrl18_cs_event_hwe,cs_event_hwe,HI_SC_CTRL18_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL18_OFFSET)
HI_SET_GET(hi_sc_ctrl19_reserved,reserved,HI_SC_CTRL19_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL19_OFFSET)
HI_SET_GET(hi_sc_ctrl20_axi_mem_ret_gatedclock_en,axi_mem_ret_gatedclock_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_cicom0_auto_clk_gate_en,cicom0_auto_clk_gate_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_cicom0_soft_gate_clk_en,cicom0_soft_gate_clk_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_cicom1_auto_clk_gate_en,cicom1_auto_clk_gate_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_cicom1_soft_gate_clk_en,cicom1_soft_gate_clk_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_hs_uart_gatedclock_en,hs_uart_gatedclock_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_uart_gatedclock_en,uart_gatedclock_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_sdcc_hclk_wkup_en,sdcc_hclk_wkup_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_sdcc_hclk_soft_en,sdcc_hclk_soft_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_dw_ssi_gatedclock_en,dw_ssi_gatedclock_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_usb3_gatedclock_en,usb3_gatedclock_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_hdlc_soft_gate_clk_en,hdlc_soft_gate_clk_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_reseved,reseved,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_cs_cg_en,cs_cg_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_reserved_1,reserved_1,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_hsic_gatedclock_en,hsic_gatedclock_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_hsic_ss_scaledown_mode,hsic_ss_scaledown_mode,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_upacc_auto_clk_gate_en,upacc_auto_clk_gate_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_upacc_soft_gate_clk_en,upacc_soft_gate_clk_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_reserved_0,reserved_0,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_ios_gatedclock_en,ios_gatedclock_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_ipcm_auto_clk_gate_en,ipcm_auto_clk_gate_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_ipcm_soft_gate_clk_en,ipcm_soft_gate_clk_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_hdlc_auto_clk_gate_en,hdlc_auto_clk_gate_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl20_sysctrl_cg_en,sysctrl_cg_en,HI_SC_CTRL20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL20_OFFSET)
HI_SET_GET(hi_sc_ctrl21_reserved_4,reserved_4,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_sdcc_gatedclock_en,sdcc_gatedclock_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_timer_gatedclock_en,timer_gatedclock_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_reserved_3,reserved_3,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_reserved_2,reserved_2,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_mddrc_ddrphy_ac_pdd,mddrc_ddrphy_ac_pdd,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_ddrc_apb_gt_en,ddrc_apb_gt_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_axi_cpu_cg_en,dw_axi_cpu_cg_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_axi_glb_cg_en,dw_axi_glb_cg_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_axi_mst_cg_en,dw_axi_mst_cg_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_axi_amon_gatedclock_en,dw_axi_amon_gatedclock_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_axi_bbphy_cg_en,dw_axi_bbphy_cg_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_rs_cg_en,dw_rs_cg_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_x2x_async_cg_en,dw_x2x_async_cg_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_x2x_qsync_cg_en,dw_x2x_qsync_cg_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_x2h_qsync_cg_en,dw_x2h_qsync_cg_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_hmx_cg_en,dw_hmx_cg_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_x2p_cg_en,dw_x2p_cg_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_gs_cg_en,dw_gs_cg_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_ashb_gatedclock_en,ashb_gatedclock_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_dw_ahb_mst_gatedclock_en,dw_ahb_mst_gatedclock_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_axi_guacc_gatedclock_en,axi_guacc_gatedclock_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_edmac_autogated_clk_en,edmac_autogated_clk_en,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_reserved_1,reserved_1,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl21_reserved_0,reserved_0,HI_SC_CTRL21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL21_OFFSET)
HI_SET_GET(hi_sc_ctrl22_hifi_ema,hifi_ema,HI_SC_CTRL22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL22_OFFSET)
HI_SET_GET(hi_sc_ctrl22_hifi_emaw,hifi_emaw,HI_SC_CTRL22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL22_OFFSET)
HI_SET_GET(hi_sc_ctrl22_hifi_emas,hifi_emas,HI_SC_CTRL22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL22_OFFSET)
HI_SET_GET(hi_sc_ctrl22_reserved_1,reserved_1,HI_SC_CTRL22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL22_OFFSET)
HI_SET_GET(hi_sc_ctrl22_dsp0_ema,dsp0_ema,HI_SC_CTRL22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL22_OFFSET)
HI_SET_GET(hi_sc_ctrl22_dsp0_emaw,dsp0_emaw,HI_SC_CTRL22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL22_OFFSET)
HI_SET_GET(hi_sc_ctrl22_dsp0_emas,dsp0_emas,HI_SC_CTRL22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL22_OFFSET)
HI_SET_GET(hi_sc_ctrl22_reserved_0,reserved_0,HI_SC_CTRL22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL22_OFFSET)
HI_SET_GET(hi_sc_ctrl23_axi_mem_ema,axi_mem_ema,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_axi_mem_emaw,axi_mem_emaw,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_axi_mem_emas,axi_mem_emas,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_reserved_2,reserved_2,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_soc_mem_ema,soc_mem_ema,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_soc_mem_spram_emaw,soc_mem_spram_emaw,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_soc_mem_spram_emas,soc_mem_spram_emas,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_soc_mem_tpram_emab,soc_mem_tpram_emab,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_soc_mem_tpram_emasa,soc_mem_tpram_emasa,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_soc_mem_dpram_emaw,soc_mem_dpram_emaw,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_soc_mem_dpram_emas,soc_mem_dpram_emas,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_reserved_1,reserved_1,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_bootrom_ema,bootrom_ema,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_bootrom_pgen,bootrom_pgen,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_bootrom_ken,bootrom_ken,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl23_reserved_0,reserved_0,HI_SC_CTRL23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL23_OFFSET)
HI_SET_GET(hi_sc_ctrl24_appa9_hs_mem_adjust,appa9_hs_mem_adjust,HI_SC_CTRL24_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL24_OFFSET)
HI_SET_GET(hi_sc_ctrl24_moda9_hs_mem_adjust,moda9_hs_mem_adjust,HI_SC_CTRL24_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL24_OFFSET)
HI_SET_GET(hi_sc_ctrl24_appa9_l2_ema,appa9_l2_ema,HI_SC_CTRL24_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL24_OFFSET)
HI_SET_GET(hi_sc_ctrl24_appa9_l2_emaw,appa9_l2_emaw,HI_SC_CTRL24_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL24_OFFSET)
HI_SET_GET(hi_sc_ctrl24_appa9_l2_emas,appa9_l2_emas,HI_SC_CTRL24_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL24_OFFSET)
HI_SET_GET(hi_sc_ctrl24_moda9_l2_ema,moda9_l2_ema,HI_SC_CTRL24_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL24_OFFSET)
HI_SET_GET(hi_sc_ctrl24_moda9_l2_emaw,moda9_l2_emaw,HI_SC_CTRL24_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL24_OFFSET)
HI_SET_GET(hi_sc_ctrl24_moda9_l2_emas,moda9_l2_emas,HI_SC_CTRL24_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL24_OFFSET)
HI_SET_GET(hi_sc_ctrl25_test_sys0_sel,test_sys0_sel,HI_SC_CTRL25_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL25_OFFSET)
HI_SET_GET(hi_sc_ctrl25_test_sys1_sel,test_sys1_sel,HI_SC_CTRL25_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL25_OFFSET)
HI_SET_GET(hi_sc_ctrl25_reserved,reserved,HI_SC_CTRL25_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL25_OFFSET)
HI_SET_GET(hi_sc_ctrl26_test_sys0_bypass,test_sys0_bypass,HI_SC_CTRL26_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL26_OFFSET)
HI_SET_GET(hi_sc_ctrl27_cs_spiden,cs_spiden,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_cs_spniden,cs_spniden,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_cs_dbgen,cs_dbgen,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_cs_niden,cs_niden,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_cs_tpctl,cs_tpctl,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_cs_deviceen,cs_deviceen,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_reserved_1,reserved_1,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_cs_tpmaxdataasize,cs_tpmaxdataasize,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_cs_nsguaren,cs_nsguaren,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_cs_tsmaxwidth,cs_tsmaxwidth,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_cs_tsnatural,cs_tsnatural,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_cs_timestamp_en,cs_timestamp_en,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl27_reserved_0,reserved_0,HI_SC_CTRL27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL27_OFFSET)
HI_SET_GET(hi_sc_ctrl28_reserved,reserved,HI_SC_CTRL28_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL28_OFFSET)
HI_SET_GET(hi_sc_ctrl28_filter_start,filter_start,HI_SC_CTRL28_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL28_OFFSET)
HI_SET_GET(hi_sc_ctrl29_reserved,reserved,HI_SC_CTRL29_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL29_OFFSET)
HI_SET_GET(hi_sc_ctrl29_filter_end,filter_end,HI_SC_CTRL29_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL29_OFFSET)
HI_SET_GET(hi_sc_ctrl30_sci0_clk_od_en,sci0_clk_od_en,HI_SC_CTRL30_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL30_OFFSET)
HI_SET_GET(hi_sc_ctrl30_sci0_data_od_en,sci0_data_od_en,HI_SC_CTRL30_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL30_OFFSET)
HI_SET_GET(hi_sc_ctrl30_reserved_1,reserved_1,HI_SC_CTRL30_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL30_OFFSET)
HI_SET_GET(hi_sc_ctrl30_sci1_clk_od_en,sci1_clk_od_en,HI_SC_CTRL30_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL30_OFFSET)
HI_SET_GET(hi_sc_ctrl30_sci1_data_od_en,sci1_data_od_en,HI_SC_CTRL30_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL30_OFFSET)
HI_SET_GET(hi_sc_ctrl30_reserved_0,reserved_0,HI_SC_CTRL30_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL30_OFFSET)
HI_SET_GET(hi_sc_ctrl31_reserved,reserved,HI_SC_CTRL31_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL31_OFFSET)
HI_SET_GET(hi_sc_ctrl32_ebi_normal_mode,ebi_normal_mode,HI_SC_CTRL32_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL32_OFFSET)
HI_SET_GET(hi_sc_ctrl32_reserved_2,reserved_2,HI_SC_CTRL32_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL32_OFFSET)
HI_SET_GET(hi_sc_ctrl32_ebi_timeoutvalue1,ebi_timeoutvalue1,HI_SC_CTRL32_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL32_OFFSET)
HI_SET_GET(hi_sc_ctrl32_reserved_1,reserved_1,HI_SC_CTRL32_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL32_OFFSET)
HI_SET_GET(hi_sc_ctrl32_ebi_timeoutvalue2,ebi_timeoutvalue2,HI_SC_CTRL32_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL32_OFFSET)
HI_SET_GET(hi_sc_ctrl32_reserved_0,reserved_0,HI_SC_CTRL32_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL32_OFFSET)
HI_SET_GET(hi_sc_ctrl33_reserved_2,reserved_2,HI_SC_CTRL33_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL33_OFFSET)
HI_SET_GET(hi_sc_ctrl33_func_ddr_testmode,func_ddr_testmode,HI_SC_CTRL33_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL33_OFFSET)
HI_SET_GET(hi_sc_ctrl33_reserved_1,reserved_1,HI_SC_CTRL33_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL33_OFFSET)
HI_SET_GET(hi_sc_ctrl33_reserved_0,reserved_0,HI_SC_CTRL33_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL33_OFFSET)
HI_SET_GET(hi_sc_ctrl34_refclk_div,refclk_div,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_txrputune,txrputune,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_txrpdtune,txrpdtune,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_txsrtune,txsrtune,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_loopbackenb,loopbackenb,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_siddq,siddq,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_txbitstuffen,txbitstuffen,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_txbitstuffenh,txbitstuffenh,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_hsic_portreset,hsic_portreset,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_reserved_1,reserved_1,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_dmpulldown,dmpulldown,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_dppulldown,dppulldown,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_reserved_0,reserved_0,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_utmi_hostdisconnect,utmi_hostdisconnect,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl34_utmiotg_iddig,utmiotg_iddig,HI_SC_CTRL34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL34_OFFSET)
HI_SET_GET(hi_sc_ctrl35_test_addr,test_addr,HI_SC_CTRL35_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL35_OFFSET)
HI_SET_GET(hi_sc_ctrl35_test_datain,test_datain,HI_SC_CTRL35_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL35_OFFSET)
HI_SET_GET(hi_sc_ctrl35_test_clk,test_clk,HI_SC_CTRL35_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL35_OFFSET)
HI_SET_GET(hi_sc_ctrl35_test_dataoutsel,test_dataoutsel,HI_SC_CTRL35_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL35_OFFSET)
HI_SET_GET(hi_sc_ctrl35_reserved,reserved,HI_SC_CTRL35_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL35_OFFSET)
HI_SET_GET(hi_sc_ctrl35_test_dataout,test_dataout,HI_SC_CTRL35_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL35_OFFSET)
HI_SET_GET(hi_sc_ctrl36_fsel,fsel,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_refclk_sel,refclk_sel,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_common_on_n,common_on_n,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_port_reset,port_reset,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_vatestenb,vatestenb,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_txvreftune,txvreftune,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_txfslstune,txfslstune,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_txhsxvtune,txhsxvtune,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_otgtune,otgtune,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_compdistune,compdistune,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_sqrxtune,sqrxtune,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_txrisetune,txrisetune,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl36_txpreempamptune,txpreempamptune,HI_SC_CTRL36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL36_OFFSET)
HI_SET_GET(hi_sc_ctrl37_test_addr,test_addr,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_test_clk,test_clk,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_test_dataout_sel,test_dataout_sel,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_phy_clk_sel,phy_clk_sel,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_phy_id_sel,phy_id_sel,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_test_datain,test_datain,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_test_dataout,test_dataout,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_acaenb,acaenb,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_retenablen,retenablen,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_reserved,reserved,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_txpreemppulsetune,txpreemppulsetune,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_otgdisable,otgdisable,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_loopbackenb,loopbackenb,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_vbusvldextsel,vbusvldextsel,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_vbusvldext,vbusvldext,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_txrestune,txrestune,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl37_siddq,siddq,HI_SC_CTRL37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL37_OFFSET)
HI_SET_GET(hi_sc_ctrl38_compdistune,compdistune,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl38_otgtune,otgtune,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl38_sqrxtune,sqrxtune,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl38_txfslstune,txfslstune,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl38_txhsxvtune,txhsxvtune,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl38_txpreempamptune,txpreempamptune,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl38_txpreemppulsetune,txpreemppulsetune,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl38_txrestune,txrestune,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl38_txrisetune,txrisetune,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl38_txvreftune,txvreftune,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl38_los_bias,los_bias,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl38_los_level2_0,los_level2_0,HI_SC_CTRL38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL38_OFFSET)
HI_SET_GET(hi_sc_ctrl39_los_level4_3,los_level4_3,HI_SC_CTRL39_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL39_OFFSET)
HI_SET_GET(hi_sc_ctrl39_pcs_tx_deemph_3p5db,pcs_tx_deemph_3p5db,HI_SC_CTRL39_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL39_OFFSET)
HI_SET_GET(hi_sc_ctrl39_pcs_tx_deemph_6db,pcs_tx_deemph_6db,HI_SC_CTRL39_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL39_OFFSET)
HI_SET_GET(hi_sc_ctrl39_pcs_tx_swing_full,pcs_tx_swing_full,HI_SC_CTRL39_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL39_OFFSET)
HI_SET_GET(hi_sc_ctrl39_lane0_tx_term_offset,lane0_tx_term_offset,HI_SC_CTRL39_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL39_OFFSET)
HI_SET_GET(hi_sc_ctrl39_tx_vboost_lvl,tx_vboost_lvl,HI_SC_CTRL39_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL39_OFFSET)
HI_SET_GET(hi_sc_ctrl39_reserved,reserved,HI_SC_CTRL39_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL39_OFFSET)
HI_SET_GET(hi_sc_ctrl40_cr_data_in,cr_data_in,HI_SC_CTRL40_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL40_OFFSET)
HI_SET_GET(hi_sc_ctrl40_cr_cap_addr,cr_cap_addr,HI_SC_CTRL40_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL40_OFFSET)
HI_SET_GET(hi_sc_ctrl40_cr_cap_data,cr_cap_data,HI_SC_CTRL40_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL40_OFFSET)
HI_SET_GET(hi_sc_ctrl40_cr_write,cr_write,HI_SC_CTRL40_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL40_OFFSET)
HI_SET_GET(hi_sc_ctrl40_cr_read,cr_read,HI_SC_CTRL40_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL40_OFFSET)
HI_SET_GET(hi_sc_ctrl40_rtune_req,rtune_req,HI_SC_CTRL40_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL40_OFFSET)
HI_SET_GET(hi_sc_ctrl40_reserved,reserved,HI_SC_CTRL40_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL40_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_bus_filter_bypass,usb3_bus_filter_bypass,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_fladj_30mhz_reg,usb3_fladj_30mhz_reg,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_host_u2_port_disable,usb3_host_u2_port_disable,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_host_u3_port_disable,usb3_host_u3_port_disable,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_host_port_pwrctl,usb3_host_port_pwrctl,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_host_msi_enable,usb3_host_msi_enable,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pm_power_state_request,usb3_pm_power_state_request,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_xhci_revision,usb3_xhci_revision,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_xhc_bme,usb3_xhc_bme,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_reserved_1,reserved_1,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_reserved_0,reserved_0,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_iddig_override,usb3_pmu_iddig_override,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_avalid_override,usb3_pmu_avalid_override,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_bvalid_override,usb3_pmu_bvalid_override,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_vbusvalid_override,usb3_pmu_vbusvalid_override,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_sessend_override,usb3_pmu_sessend_override,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_powerpresent_override,usb3_pmu_powerpresent_override,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_iddig_override_en,usb3_pmu_iddig_override_en,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_avalid_override_en,usb3_pmu_avalid_override_en,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_bvalid_override_en,usb3_pmu_bvalid_override_en,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_vbusvalid_override_en,usb3_pmu_vbusvalid_override_en,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_sessend_override_en,usb3_pmu_sessend_override_en,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl41_usb3_pmu_powerpresent_override_en,usb3_pmu_powerpresent_override_en,HI_SC_CTRL41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL41_OFFSET)
HI_SET_GET(hi_sc_ctrl42_usb3_pmu_pm_pmu_config_strap,usb3_pmu_pm_pmu_config_strap,HI_SC_CTRL42_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL42_OFFSET)
HI_SET_GET(hi_sc_ctrl42_usb3_pmu_port_overcurrent,usb3_pmu_port_overcurrent,HI_SC_CTRL42_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL42_OFFSET)
HI_SET_GET(hi_sc_ctrl43_usb3_hub_port_perm_attach,usb3_hub_port_perm_attach,HI_SC_CTRL43_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL43_OFFSET)
HI_SET_GET(hi_sc_ctrl43_usb3_pme_en,usb3_pme_en,HI_SC_CTRL43_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL43_OFFSET)
HI_SET_GET(hi_sc_ctrl43_reserved,reserved,HI_SC_CTRL43_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL43_OFFSET)
HI_SET_GET(hi_sc_ctrl44_reserved,reserved,HI_SC_CTRL44_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL44_OFFSET)
HI_SET_GET(hi_sc_ctrl45_uicc_ic_usb_vbusvalid,uicc_ic_usb_vbusvalid,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_reserved,reserved,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge0_en,intr_merge0_en,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge0_mode,intr_merge0_mode,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge1_en,intr_merge1_en,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge1_mode,intr_merge1_mode,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge2_en,intr_merge2_en,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge2_mode,intr_merge2_mode,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge3_en,intr_merge3_en,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge3_mode,intr_merge3_mode,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge0_sel,intr_merge0_sel,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge1_sel,intr_merge1_sel,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge2_sel,intr_merge2_sel,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl45_intr_merge3_sel,intr_merge3_sel,HI_SC_CTRL45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL45_OFFSET)
HI_SET_GET(hi_sc_ctrl46_intr_merge0_timer0,intr_merge0_timer0,HI_SC_CTRL46_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL46_OFFSET)
HI_SET_GET(hi_sc_ctrl46_intr_merge0_timer1,intr_merge0_timer1,HI_SC_CTRL46_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL46_OFFSET)
HI_SET_GET(hi_sc_ctrl47_int2_merge0_timer2,int2_merge0_timer2,HI_SC_CTRL47_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL47_OFFSET)
HI_SET_GET(hi_sc_ctrl47_intr_merge0_timer3,intr_merge0_timer3,HI_SC_CTRL47_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL47_OFFSET)
HI_SET_GET(hi_sc_ctrl48_sysctrl_intr_appa9,sysctrl_intr_appa9,HI_SC_CTRL48_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL48_OFFSET)
HI_SET_GET(hi_sc_ctrl48_sysctrl_intr_mdma9,sysctrl_intr_mdma9,HI_SC_CTRL48_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL48_OFFSET)
HI_SET_GET(hi_sc_ctrl48_sysctrl_intr_cm3,sysctrl_intr_cm3,HI_SC_CTRL48_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL48_OFFSET)
HI_SET_GET(hi_sc_ctrl48_reserved,reserved,HI_SC_CTRL48_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL48_OFFSET)
HI_SET_GET(hi_sc_ctrl49_sysctrl_intr_appa9,sysctrl_intr_appa9,HI_SC_CTRL49_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL49_OFFSET)
HI_SET_GET(hi_sc_ctrl49_sysctrl_intr_mdma9,sysctrl_intr_mdma9,HI_SC_CTRL49_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL49_OFFSET)
HI_SET_GET(hi_sc_ctrl49_sysctrl_intr_cm3,sysctrl_intr_cm3,HI_SC_CTRL49_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL49_OFFSET)
HI_SET_GET(hi_sc_ctrl49_reserved,reserved,HI_SC_CTRL49_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL49_OFFSET)
HI_SET_GET(hi_sc_ctrl50_sysctrl_intr_appa9,sysctrl_intr_appa9,HI_SC_CTRL50_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL50_OFFSET)
HI_SET_GET(hi_sc_ctrl50_sysctrl_intr_mdma9,sysctrl_intr_mdma9,HI_SC_CTRL50_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL50_OFFSET)
HI_SET_GET(hi_sc_ctrl50_sysctrl_intr_cm3,sysctrl_intr_cm3,HI_SC_CTRL50_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL50_OFFSET)
HI_SET_GET(hi_sc_ctrl50_reserved,reserved,HI_SC_CTRL50_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL50_OFFSET)
HI_SET_GET(hi_sc_ctrl51_cm3_nmi,cm3_nmi,HI_SC_CTRL51_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL51_OFFSET)
HI_SET_GET(hi_sc_ctrl51_reserved,reserved,HI_SC_CTRL51_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL51_OFFSET)
HI_SET_GET(hi_sc_ctrl52_dsp0_nmi,dsp0_nmi,HI_SC_CTRL52_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL52_OFFSET)
HI_SET_GET(hi_sc_ctrl52_reserved,reserved,HI_SC_CTRL52_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL52_OFFSET)
HI_SET_GET(hi_sc_ctrl53_hifi_nmi,hifi_nmi,HI_SC_CTRL53_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL53_OFFSET)
HI_SET_GET(hi_sc_ctrl53_reserved,reserved,HI_SC_CTRL53_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL53_OFFSET)
HI_SET_GET(hi_sc_ctrl54_dw_ssi0_dma_sel,dw_ssi0_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_dw_ssi1_dma_sel,dw_ssi1_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_sio_dma_sel,sio_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_hs_uart_dma_sel,hs_uart_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_uart0_dma_sel,uart0_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_uart1_dma_sel,uart1_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_uart2_dma_sel,uart2_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_sci0_dma_sel,sci0_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_sci1_dma_sel,sci1_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_bbp_dbg_dma_sel,bbp_dbg_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_bbp_grif_dma_sel,bbp_grif_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_amon_soc_dma_sel,amon_soc_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_amon_fast_dma_sel,amon_fast_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_i2c0_dma_sel,i2c0_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_i2c1_dma_sel,i2c1_dma_sel,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl54_reserved,reserved,HI_SC_CTRL54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL54_OFFSET)
HI_SET_GET(hi_sc_ctrl55_reserved_1,reserved_1,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_cs_ret1n,cs_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_gmac_ret1n,gmac_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_usb3_ret1n,usb3_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_reserved_0,reserved_0,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_uicc_ret1n,uicc_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_nandc_ret1n,nandc_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_sdcc_ret1n,sdcc_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_hsic_ret1n,hsic_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_amon_soc_ret1n,amon_soc_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_amon_cpufast_ret1n,amon_cpufast_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_pcie_colldisn,pcie_colldisn,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_mmc_colldisn,mmc_colldisn,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_edmac_colldisn,edmac_colldisn,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_ssdma_colldisn,ssdma_colldisn,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_sdcc_colldisn,sdcc_colldisn,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_socp_colldisn,socp_colldisn,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_amon_colldisn,amon_colldisn,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_gmac_colldisn,gmac_colldisn,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_ipf_ret1n,ipf_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_ipf_colldisn,ipf_colldisn,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_cipher_ret1n,cipher_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_cipher_colldisn,cipher_colldisn,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_socp_ret1n,socp_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_mipi_ret1n,mipi_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_hs_uart_ret1n,hs_uart_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_mmc0_ret1n,mmc0_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_mmc1_ret1n,mmc1_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_pcie_ret1n,pcie_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_edmac_ret1n,edmac_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_ssdma_ret1n,ssdma_ret1n,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl55_mipi_colldisn,mipi_colldisn,HI_SC_CTRL55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL55_OFFSET)
HI_SET_GET(hi_sc_ctrl56_prior_level,prior_level,HI_SC_CTRL56_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL56_OFFSET)
HI_SET_GET(hi_sc_ctrl56_gatedclock_en,gatedclock_en,HI_SC_CTRL56_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL56_OFFSET)
HI_SET_GET(hi_sc_ctrl56_dw_axi_rs_gatedclock_en,dw_axi_rs_gatedclock_en,HI_SC_CTRL56_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL56_OFFSET)
HI_SET_GET(hi_sc_ctrl56_dw_axi_gs_gatedclock_en,dw_axi_gs_gatedclock_en,HI_SC_CTRL56_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL56_OFFSET)
HI_SET_GET(hi_sc_ctrl56_overf_prot,overf_prot,HI_SC_CTRL56_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL56_OFFSET)
HI_SET_GET(hi_sc_ctrl56_reserved,reserved,HI_SC_CTRL56_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL56_OFFSET)
HI_SET_GET(hi_sc_ctrl56_atpram_ctrl,atpram_ctrl,HI_SC_CTRL56_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL56_OFFSET)
HI_SET_GET(hi_sc_ctrl57_soc2lte_tbd,soc2lte_tbd,HI_SC_CTRL57_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL57_OFFSET)
HI_SET_GET(hi_sc_ctrl57_reserved,reserved,HI_SC_CTRL57_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL57_OFFSET)
HI_SET_GET(hi_sc_ctrl68_moda9_l2_ret1n,moda9_l2_ret1n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_moda9_l2_ret2n,moda9_l2_ret2n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_moda9_l2_pgen,moda9_l2_pgen,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_reserved_5,reserved_5,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_appa9_l2_ret1n,appa9_l2_ret1n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_appa9_l2_ret2n,appa9_l2_ret2n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_appa9_l2_pgen,appa9_l2_pgen,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_reserved_4,reserved_4,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_dsp0_ret1n,dsp0_ret1n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_dsp0_ret2n,dsp0_ret2n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_dsp0_pgen,dsp0_pgen,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_reserved_3,reserved_3,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_hifi_ret1n,hifi_ret1n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_hifi_ret2n,hifi_ret2n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_hifi_pgen,hifi_pgen,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_reserved_2,reserved_2,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_pd_axi_mem_ret1n,pd_axi_mem_ret1n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_pd_axi_mem_ret2n,pd_axi_mem_ret2n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_pd_axi_mem_pgen,pd_axi_mem_pgen,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_reserved_1,reserved_1,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_ret_axi_mem_ret1n,ret_axi_mem_ret1n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_ret_axi_mem_ret2n,ret_axi_mem_ret2n,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_ret_axi_mem_pgen,ret_axi_mem_pgen,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl68_reserved_0,reserved_0,HI_SC_CTRL68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL68_OFFSET)
HI_SET_GET(hi_sc_ctrl69_axi_bbphy_xdcdr_sel,axi_bbphy_xdcdr_sel,HI_SC_CTRL69_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL69_OFFSET)
HI_SET_GET(hi_sc_ctrl69_axi_amon_xdcdr_sel,axi_amon_xdcdr_sel,HI_SC_CTRL69_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL69_OFFSET)
HI_SET_GET(hi_sc_ctrl69_axi_cpu_xdcdr_sel,axi_cpu_xdcdr_sel,HI_SC_CTRL69_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL69_OFFSET)
HI_SET_GET(hi_sc_ctrl69_axi_glb_xdcdr_sel,axi_glb_xdcdr_sel,HI_SC_CTRL69_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL69_OFFSET)
HI_SET_GET(hi_sc_ctrl69_sysapb_pslverr_sel,sysapb_pslverr_sel,HI_SC_CTRL69_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL69_OFFSET)
HI_SET_GET(hi_sc_ctrl69_socapb_pslverr_sel,socapb_pslverr_sel,HI_SC_CTRL69_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL69_OFFSET)
HI_SET_GET(hi_sc_ctrl69_x2h_hslverr_sel,x2h_hslverr_sel,HI_SC_CTRL69_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL69_OFFSET)
HI_SET_GET(hi_sc_ctrl69_mst_err_srst_req,mst_err_srst_req,HI_SC_CTRL69_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL69_OFFSET)
HI_SET_GET(hi_sc_ctrl69_reserved,reserved,HI_SC_CTRL69_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL69_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_bbphy_priority_m1,axi_bbphy_priority_m1,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_bbphy_priority_m2,axi_bbphy_priority_m2,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_bbphy_priority_m3,axi_bbphy_priority_m3,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_bbphy_priority_m4,axi_bbphy_priority_m4,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_guacc_priority_m1,axi_guacc_priority_m1,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_guacc_priority_m2,axi_guacc_priority_m2,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_guacc_priority_m3,axi_guacc_priority_m3,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_guacc_priority_m4,axi_guacc_priority_m4,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_mst_priority_m9,axi_mst_priority_m9,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_mst_priority_m10,axi_mst_priority_m10,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_reserved_1,reserved_1,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_cpu_priority_m1,axi_cpu_priority_m1,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_cpu_priority_m2,axi_cpu_priority_m2,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_axi_amon_mst_priority_m1,axi_amon_mst_priority_m1,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl70_reserved_0,reserved_0,HI_SC_CTRL70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL70_OFFSET)
HI_SET_GET(hi_sc_ctrl71_reserved,reserved,HI_SC_CTRL71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL71_OFFSET)
HI_SET_GET(hi_sc_ctrl71_axi_glb_priority_m1,axi_glb_priority_m1,HI_SC_CTRL71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL71_OFFSET)
HI_SET_GET(hi_sc_ctrl71_axi_glb_priority_m2,axi_glb_priority_m2,HI_SC_CTRL71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL71_OFFSET)
HI_SET_GET(hi_sc_ctrl71_axi_glb_priority_m3,axi_glb_priority_m3,HI_SC_CTRL71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL71_OFFSET)
HI_SET_GET(hi_sc_ctrl71_axi_glb_priority_m4,axi_glb_priority_m4,HI_SC_CTRL71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL71_OFFSET)
HI_SET_GET(hi_sc_ctrl71_axi_glb_priority_m5,axi_glb_priority_m5,HI_SC_CTRL71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL71_OFFSET)
HI_SET_GET(hi_sc_ctrl71_axi_glb_priority_m6,axi_glb_priority_m6,HI_SC_CTRL71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL71_OFFSET)
HI_SET_GET(hi_sc_ctrl71_axi_mst_cache_cfg_en,axi_mst_cache_cfg_en,HI_SC_CTRL71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL71_OFFSET)
HI_SET_GET(hi_sc_ctrl71_axi_mst_sideband,axi_mst_sideband,HI_SC_CTRL71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL71_OFFSET)
HI_SET_GET(hi_sc_ctrl71_axi_mst_cache,axi_mst_cache,HI_SC_CTRL71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL71_OFFSET)
HI_SET_GET(hi_sc_ctrl72_axi_mst_priority_m1,axi_mst_priority_m1,HI_SC_CTRL72_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL72_OFFSET)
HI_SET_GET(hi_sc_ctrl72_axi_mst_priority_m2,axi_mst_priority_m2,HI_SC_CTRL72_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL72_OFFSET)
HI_SET_GET(hi_sc_ctrl72_axi_mst_priority_m3,axi_mst_priority_m3,HI_SC_CTRL72_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL72_OFFSET)
HI_SET_GET(hi_sc_ctrl72_axi_mst_priority_m4,axi_mst_priority_m4,HI_SC_CTRL72_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL72_OFFSET)
HI_SET_GET(hi_sc_ctrl72_axi_mst_priority_m5,axi_mst_priority_m5,HI_SC_CTRL72_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL72_OFFSET)
HI_SET_GET(hi_sc_ctrl72_axi_mst_priority_m6,axi_mst_priority_m6,HI_SC_CTRL72_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL72_OFFSET)
HI_SET_GET(hi_sc_ctrl72_axi_mst_priority_m7,axi_mst_priority_m7,HI_SC_CTRL72_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL72_OFFSET)
HI_SET_GET(hi_sc_ctrl72_axi_mst_priority_m8,axi_mst_priority_m8,HI_SC_CTRL72_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL72_OFFSET)
HI_SET_GET(hi_sc_ctrl81_appa9_gpio0_en,appa9_gpio0_en,HI_SC_CTRL81_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL81_OFFSET)
HI_SET_GET(hi_sc_ctrl85_mdma9_gpio0_en,mdma9_gpio0_en,HI_SC_CTRL85_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL85_OFFSET)
HI_SET_GET(hi_sc_ctrl98_cm3_gpio0_en,cm3_gpio0_en,HI_SC_CTRL98_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL98_OFFSET)
HI_SET_GET(hi_sc_ctrl103_reserved_6,reserved_6,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_bbphy_dsp0_axislv_active,bbphy_dsp0_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_bbphy_bbp_axislv_active,bbphy_bbp_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_reserved_5,reserved_5,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_amon_soc_axislv_active,amon_soc_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_amon_cpufast_axislv_active,amon_cpufast_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_cs_axislv_active,cs_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_reserved_4,reserved_4,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_mdmacp_axislv_active,mdmacp_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_appacp_axislv_active,appacp_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_ddrdata_axislv_active,ddrdata_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_axi_mem_axislv_active,axi_mem_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_x2h_peri_axislv_active,x2h_peri_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_bbphy_axislv_active,bbphy_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_x2p_axislv_active,x2p_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_hifi_axislv_active,hifi_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_dw_axi_amon_axislv_active,dw_axi_amon_axislv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_cpu_slv_active,cpu_slv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_reserved_3,reserved_3,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_wdog_apbslv_active,wdog_apbslv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_timer0_7_apbslv_active,timer0_7_apbslv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_timer8_15_apbslv_active,timer8_15_apbslv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_timer16_23_apbslv_active,timer16_23_apbslv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_reserved_2,reserved_2,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_gpio0_apbslv_active,gpio0_apbslv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_uart0_apbslv_active,uart0_apbslv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_reserved_1,reserved_1,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_sci0_apbslv_active,sci0_apbslv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_sci1_apbslv_apbactive,sci1_apbslv_apbactive,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_tsensor_apbslv_active,tsensor_apbslv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_usbotg_apbslv_active,usbotg_apbslv_active,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl103_reserved_0,reserved_0,HI_SC_CTRL103_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL103_OFFSET)
HI_SET_GET(hi_sc_ctrl104_cs_slv_active,cs_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_pmussi0_slv_active,pmussi0_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_reserved_8,reserved_8,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_usb_otg_slv_active,usb_otg_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_reserved_7,reserved_7,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_reserved_6,reserved_6,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_dwssi0_slv_active,dwssi0_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_gpio1_slv_active,gpio1_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_gpio2_slv_active,gpio2_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_gpio3_slv_active,gpio3_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_reserved_5,reserved_5,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_uart1_slv_active,uart1_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_uart2_slv_active,uart2_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_uart3_slv_active,uart3_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_i2c0_slv_active,i2c0_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_i2c1_slv_active,i2c1_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_mddrc_slv_active,mddrc_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_efusec_slv_active,efusec_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_reserved_4,reserved_4,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_dwssi1_slv_active,dwssi1_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_edam_slv_active,edam_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_dt_slv_active,dt_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_edmac_ch4_slv_active,edmac_ch4_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_reserved_3,reserved_3,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_pcie_phy_slv_active,pcie_phy_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_reserved_2,reserved_2,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_mipi_slv_active,mipi_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_reserved_1,reserved_1,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_bbp_ao_slv_active,bbp_ao_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_reserved_0,reserved_0,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_pwm0_slv_active,pwm0_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl104_pwm1_slv_active,pwm1_slv_active,HI_SC_CTRL104_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL104_OFFSET)
HI_SET_GET(hi_sc_ctrl105_uicc,uicc,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_hsic,hsic,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_reserved_8,reserved_8,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_emi_reg,emi_reg,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_emi_mem,emi_mem,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_nandc_reg,nandc_reg,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_ipcm,ipcm,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_sio,sio,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_hs_uart,hs_uart,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_socp,socp,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_reserved_7,reserved_7,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_cipher,cipher,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_ipf,ipf,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_mmc0,mmc0,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_mmc1,mmc1,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_reserved_6,reserved_6,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_sdcc,sdcc,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_reserved_5,reserved_5,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_reserved_4,reserved_4,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_cicom0,cicom0,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_cicom1,cicom1,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_hdlc,hdlc,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_usb3,usb3,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_nandc_mem,nandc_mem,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_reserved_3,reserved_3,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_vic1,vic1,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_cm3,cm3,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_reserved_2,reserved_2,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_reserved_1,reserved_1,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_upacc,upacc,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_reserved_0,reserved_0,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl105_tcssi1,tcssi1,HI_SC_CTRL105_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL105_OFFSET)
HI_SET_GET(hi_sc_ctrl121_reserved,reserved,HI_SC_CTRL121_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL121_OFFSET)
HI_SET_GET(hi_sc_ctrl122_reserved,reserved,HI_SC_CTRL122_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL122_OFFSET)
HI_SET_GET(hi_sc_ctrl123_reserved,reserved,HI_SC_CTRL123_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL123_OFFSET)
HI_SET_GET(hi_sc_ctrl124_reserved,reserved,HI_SC_CTRL124_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL124_OFFSET)
HI_SET_GET(hi_sc_ctrl125_reserved,reserved,HI_SC_CTRL125_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL125_OFFSET)
HI_SET_GET(hi_sc_ctrl126_reserved,reserved,HI_SC_CTRL126_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL126_OFFSET)
HI_SET_GET(hi_sc_ctrl127_reserved,reserved,HI_SC_CTRL127_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_CTRL127_OFFSET)
HI_SET_GET(hi_sc_stat0_boot_mode2_0,boot_mode2_0,HI_SC_STAT0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT0_OFFSET)
HI_SET_GET(hi_sc_stat0_boot_mode3,boot_mode3,HI_SC_STAT0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT0_OFFSET)
HI_SET_GET(hi_sc_stat0_reserved_2,reserved_2,HI_SC_STAT0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT0_OFFSET)
HI_SET_GET(hi_sc_stat0_jtag_mode0,jtag_mode0,HI_SC_STAT0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT0_OFFSET)
HI_SET_GET(hi_sc_stat0_jtag_mode1,jtag_mode1,HI_SC_STAT0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT0_OFFSET)
HI_SET_GET(hi_sc_stat0_reserved_1,reserved_1,HI_SC_STAT0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT0_OFFSET)
HI_SET_GET(hi_sc_stat0_jtag_dft_mode,jtag_dft_mode,HI_SC_STAT0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT0_OFFSET)
HI_SET_GET(hi_sc_stat0_wdt_rst_n_store,wdt_rst_n_store,HI_SC_STAT0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT0_OFFSET)
HI_SET_GET(hi_sc_stat0_pmu_rst_n_store,pmu_rst_n_store,HI_SC_STAT0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT0_OFFSET)
HI_SET_GET(hi_sc_stat0_reserved_0,reserved_0,HI_SC_STAT0_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT0_OFFSET)
HI_SET_GET(hi_sc_stat1_appa9_pmupriv,appa9_pmupriv,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_appa9_pmusecure,appa9_pmusecure,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_appa9_smpnamp,appa9_smpnamp,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_appa9_scuevabort,appa9_scuevabort,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_appa9_pwrctlo0,appa9_pwrctlo0,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_appa9_l2_tagclkouten,appa9_l2_tagclkouten,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_appa9_l2_dataclkouten,appa9_l2_dataclkouten,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_appa9_l2_idle,appa9_l2_idle,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_appa9_l2_clkstopped,appa9_l2_clkstopped,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_reserved_1,reserved_1,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_moda9_pmupriv,moda9_pmupriv,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_moda9_pmusecure,moda9_pmusecure,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_moda9_smpnamp,moda9_smpnamp,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_moda9_scuevabort,moda9_scuevabort,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_moda9_pwrctlo0,moda9_pwrctlo0,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_moda9_l2_tagclkouten,moda9_l2_tagclkouten,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_moda9_l2_dataclkouten,moda9_l2_dataclkouten,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_moda9_l2_idle,moda9_l2_idle,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_moda9_l2_clkstopped,moda9_l2_clkstopped,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat1_reserved_0,reserved_0,HI_SC_STAT1_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT1_OFFSET)
HI_SET_GET(hi_sc_stat2_hifi_pwaitmode,hifi_pwaitmode,HI_SC_STAT2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT2_OFFSET)
HI_SET_GET(hi_sc_stat2_hifi_xocdmode,hifi_xocdmode,HI_SC_STAT2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT2_OFFSET)
HI_SET_GET(hi_sc_stat2_appa9_deflags,appa9_deflags,HI_SC_STAT2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT2_OFFSET)
HI_SET_GET(hi_sc_stat2_reserved_1,reserved_1,HI_SC_STAT2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT2_OFFSET)
HI_SET_GET(hi_sc_stat2_dsp0_pwaitmode,dsp0_pwaitmode,HI_SC_STAT2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT2_OFFSET)
HI_SET_GET(hi_sc_stat2_dsp0_xocdmode,dsp0_xocdmode,HI_SC_STAT2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT2_OFFSET)
HI_SET_GET(hi_sc_stat2_reserved_0,reserved_0,HI_SC_STAT2_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT2_OFFSET)
HI_SET_GET(hi_sc_stat3_hpm0_opc,hpm0_opc,HI_SC_STAT3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT3_OFFSET)
HI_SET_GET(hi_sc_stat3_hpm0_opc_vld,hpm0_opc_vld,HI_SC_STAT3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT3_OFFSET)
HI_SET_GET(hi_sc_stat3_reserved_1,reserved_1,HI_SC_STAT3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT3_OFFSET)
HI_SET_GET(hi_sc_stat3_hpm1_opc,hpm1_opc,HI_SC_STAT3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT3_OFFSET)
HI_SET_GET(hi_sc_stat3_hpm1_opc_vld,hpm1_opc_vld,HI_SC_STAT3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT3_OFFSET)
HI_SET_GET(hi_sc_stat3_reserved_0,reserved_0,HI_SC_STAT3_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT3_OFFSET)
HI_SET_GET(hi_sc_stat4_hpm2_opc,hpm2_opc,HI_SC_STAT4_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT4_OFFSET)
HI_SET_GET(hi_sc_stat4_hpm2_opc_vld,hpm2_opc_vld,HI_SC_STAT4_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT4_OFFSET)
HI_SET_GET(hi_sc_stat4_reserved,reserved,HI_SC_STAT4_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT4_OFFSET)
HI_SET_GET(hi_sc_stat5_reserved,reserved,HI_SC_STAT5_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT5_OFFSET)
HI_SET_GET(hi_sc_stat6_appa9_parityfail0,appa9_parityfail0,HI_SC_STAT6_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT6_OFFSET)
HI_SET_GET(hi_sc_stat6_appa9_parityfailscu,appa9_parityfailscu,HI_SC_STAT6_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT6_OFFSET)
HI_SET_GET(hi_sc_stat6_reserved_1,reserved_1,HI_SC_STAT6_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT6_OFFSET)
HI_SET_GET(hi_sc_stat6_moda9_parityfail0,moda9_parityfail0,HI_SC_STAT6_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT6_OFFSET)
HI_SET_GET(hi_sc_stat6_moda9_parityfailscu,moda9_parityfailscu,HI_SC_STAT6_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT6_OFFSET)
HI_SET_GET(hi_sc_stat6_reserved_0,reserved_0,HI_SC_STAT6_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT6_OFFSET)
HI_SET_GET(hi_sc_stat7_reserved,reserved,HI_SC_STAT7_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT7_OFFSET)
HI_SET_GET(hi_sc_stat8_bbp_timer_readcnt,bbp_timer_readcnt,HI_SC_STAT8_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT8_OFFSET)
HI_SET_GET(hi_sc_stat9_dw_axi_mst_dlock_wr,dw_axi_mst_dlock_wr,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_dw_axi_mst_dlock_slv,dw_axi_mst_dlock_slv,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_reserved_3,reserved_3,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_dw_axi_mst_dlock_mst,dw_axi_mst_dlock_mst,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_dw_axi_cpu_dlock_wr,dw_axi_cpu_dlock_wr,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_dw_axi_cpu_dlock_slv,dw_axi_cpu_dlock_slv,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_dw_axi_cpu_dlock_mst,dw_axi_cpu_dlock_mst,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_reserved_2,reserved_2,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_axi_amon_dlock_wr,axi_amon_dlock_wr,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_axi_amon_dlock_slv,axi_amon_dlock_slv,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_axi_amon_dlock_mst,axi_amon_dlock_mst,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_reserved_1,reserved_1,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_dw_axi_glb_dlock_wr,dw_axi_glb_dlock_wr,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_dw_axi_glb_dlock_slv,dw_axi_glb_dlock_slv,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_dw_axi_glb_dlock_mst,dw_axi_glb_dlock_mst,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat9_reserved_0,reserved_0,HI_SC_STAT9_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT9_OFFSET)
HI_SET_GET(hi_sc_stat10_dw_axi_glb_dlock_id,dw_axi_glb_dlock_id,HI_SC_STAT10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT10_OFFSET)
HI_SET_GET(hi_sc_stat10_dw_axi_amon_dlock_id,dw_axi_amon_dlock_id,HI_SC_STAT10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT10_OFFSET)
HI_SET_GET(hi_sc_stat10_dw_axi_cpu_dlock_id,dw_axi_cpu_dlock_id,HI_SC_STAT10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT10_OFFSET)
HI_SET_GET(hi_sc_stat10_dw_axi_mst_dlock_id,dw_axi_mst_dlock_id,HI_SC_STAT10_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT10_OFFSET)
HI_SET_GET(hi_sc_stat11_sdcc_pull_stat,sdcc_pull_stat,HI_SC_STAT11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT11_OFFSET)
HI_SET_GET(hi_sc_stat11_reserved,reserved,HI_SC_STAT11_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT11_OFFSET)
HI_SET_GET(hi_sc_stat12_sdcc_pull_raw,sdcc_pull_raw,HI_SC_STAT12_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT12_OFFSET)
HI_SET_GET(hi_sc_stat12_reserved,reserved,HI_SC_STAT12_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT12_OFFSET)
HI_SET_GET(hi_sc_stat13_reserved,reserved,HI_SC_STAT13_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT13_OFFSET)
HI_SET_GET(hi_sc_stat14_cr_data_out,cr_data_out,HI_SC_STAT14_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT14_OFFSET)
HI_SET_GET(hi_sc_stat14_cr_ack,cr_ack,HI_SC_STAT14_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT14_OFFSET)
HI_SET_GET(hi_sc_stat14_reserved_2,reserved_2,HI_SC_STAT14_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT14_OFFSET)
HI_SET_GET(hi_sc_stat14_rtune_ack,rtune_ack,HI_SC_STAT14_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT14_OFFSET)
HI_SET_GET(hi_sc_stat14_reserved_1,reserved_1,HI_SC_STAT14_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT14_OFFSET)
HI_SET_GET(hi_sc_stat14_ref_clkreq_n,ref_clkreq_n,HI_SC_STAT14_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT14_OFFSET)
HI_SET_GET(hi_sc_stat14_reserved_0,reserved_0,HI_SC_STAT14_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT14_OFFSET)
HI_SET_GET(hi_sc_stat15_sysapb_pslv_active0,sysapb_pslv_active0,HI_SC_STAT15_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT15_OFFSET)
HI_SET_GET(hi_sc_stat15_reserved_1,reserved_1,HI_SC_STAT15_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT15_OFFSET)
HI_SET_GET(hi_sc_stat15_sysapb_pslv_active1,sysapb_pslv_active1,HI_SC_STAT15_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT15_OFFSET)
HI_SET_GET(hi_sc_stat15_reserved_0,reserved_0,HI_SC_STAT15_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT15_OFFSET)
HI_SET_GET(hi_sc_stat16_ldrx2dbg_abs_timer_31_0,ldrx2dbg_abs_timer_31_0,HI_SC_STAT16_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT16_OFFSET)
HI_SET_GET(hi_sc_stat17_ldrx2dbg_abs_timer_63_32,ldrx2dbg_abs_timer_63_32,HI_SC_STAT17_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT17_OFFSET)
HI_SET_GET(hi_sc_stat18_wdrx_deepsleep_flag,wdrx_deepsleep_flag,HI_SC_STAT18_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT18_OFFSET)
HI_SET_GET(hi_sc_stat18_g1_gdrx_deepsleep_falg,g1_gdrx_deepsleep_falg,HI_SC_STAT18_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT18_OFFSET)
HI_SET_GET(hi_sc_stat18_g2_gdrx_deepsleep_falg,g2_gdrx_deepsleep_falg,HI_SC_STAT18_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT18_OFFSET)
HI_SET_GET(hi_sc_stat18_reserved,reserved,HI_SC_STAT18_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT18_OFFSET)
HI_SET_GET(hi_sc_stat19_reserved,reserved,HI_SC_STAT19_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT19_OFFSET)
HI_SET_GET(hi_sc_stat20_reserved,reserved,HI_SC_STAT20_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT20_OFFSET)
HI_SET_GET(hi_sc_stat21_usb3_connect_state_u2pmu,usb3_connect_state_u2pmu,HI_SC_STAT21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT21_OFFSET)
HI_SET_GET(hi_sc_stat21_usb3_connect_state_u3pmu,usb3_connect_state_u3pmu,HI_SC_STAT21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT21_OFFSET)
HI_SET_GET(hi_sc_stat21_usb3_host_current_belt,usb3_host_current_belt,HI_SC_STAT21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT21_OFFSET)
HI_SET_GET(hi_sc_stat21_reserved_1,reserved_1,HI_SC_STAT21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT21_OFFSET)
HI_SET_GET(hi_sc_stat21_usb3_pmu_current_power_state_u2pmu,usb3_pmu_current_power_state_u2pmu,HI_SC_STAT21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT21_OFFSET)
HI_SET_GET(hi_sc_stat21_usb3_pmu_current_power_state_u3pmu,usb3_pmu_current_power_state_u3pmu,HI_SC_STAT21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT21_OFFSET)
HI_SET_GET(hi_sc_stat21_usb3_pmu_phy_u2dsport_vbus_ctrl,usb3_pmu_phy_u2dsport_vbus_ctrl,HI_SC_STAT21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT21_OFFSET)
HI_SET_GET(hi_sc_stat21_usb3_pmu_phy_u3dsport_vbus_ctrl,usb3_pmu_phy_u3dsport_vbus_ctrl,HI_SC_STAT21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT21_OFFSET)
HI_SET_GET(hi_sc_stat21_reserved_0,reserved_0,HI_SC_STAT21_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT21_OFFSET)
HI_SET_GET(hi_sc_stat22_dw_axi_bbphy_dlock_mst,dw_axi_bbphy_dlock_mst,HI_SC_STAT22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT22_OFFSET)
HI_SET_GET(hi_sc_stat22_dw_axi_bbphy_dlock_slv,dw_axi_bbphy_dlock_slv,HI_SC_STAT22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT22_OFFSET)
HI_SET_GET(hi_sc_stat22_dw_axi_bbphy_dlock_wr,dw_axi_bbphy_dlock_wr,HI_SC_STAT22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT22_OFFSET)
HI_SET_GET(hi_sc_stat22_reserved_1,reserved_1,HI_SC_STAT22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT22_OFFSET)
HI_SET_GET(hi_sc_stat22_dw_axi_bbphy_dlock_id,dw_axi_bbphy_dlock_id,HI_SC_STAT22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT22_OFFSET)
HI_SET_GET(hi_sc_stat22_reserved_0,reserved_0,HI_SC_STAT22_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT22_OFFSET)
HI_SET_GET(hi_sc_stat23_func_mbist_fail,func_mbist_fail,HI_SC_STAT23_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT23_OFFSET)
HI_SET_GET(hi_sc_stat24_func_mbist_done,func_mbist_done,HI_SC_STAT24_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT24_OFFSET)
HI_SET_GET(hi_sc_stat25_func_mbist_done,func_mbist_done,HI_SC_STAT25_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT25_OFFSET)
HI_SET_GET(hi_sc_stat26_socp_idle,socp_idle,HI_SC_STAT26_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT26_OFFSET)
HI_SET_GET(hi_sc_stat26_ipf_idle,ipf_idle,HI_SC_STAT26_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT26_OFFSET)
HI_SET_GET(hi_sc_stat26_cicom0_clk_state,cicom0_clk_state,HI_SC_STAT26_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT26_OFFSET)
HI_SET_GET(hi_sc_stat26_cicom1_clk_state,cicom1_clk_state,HI_SC_STAT26_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT26_OFFSET)
HI_SET_GET(hi_sc_stat26_hdlc_clk_state,hdlc_clk_state,HI_SC_STAT26_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT26_OFFSET)
HI_SET_GET(hi_sc_stat26_reserved,reserved,HI_SC_STAT26_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT26_OFFSET)
HI_SET_GET(hi_sc_stat27_bbphy_slv_active,bbphy_slv_active,HI_SC_STAT27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT27_OFFSET)
HI_SET_GET(hi_sc_stat27_amon_slv_active,amon_slv_active,HI_SC_STAT27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT27_OFFSET)
HI_SET_GET(hi_sc_stat27_reserved_1,reserved_1,HI_SC_STAT27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT27_OFFSET)
HI_SET_GET(hi_sc_stat27_glb_slv_active,glb_slv_active,HI_SC_STAT27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT27_OFFSET)
HI_SET_GET(hi_sc_stat27_cpu_slv_active,cpu_slv_active,HI_SC_STAT27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT27_OFFSET)
HI_SET_GET(hi_sc_stat27_reserved_0,reserved_0,HI_SC_STAT27_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT27_OFFSET)
HI_SET_GET(hi_sc_stat28_socapb_pslv_active,socapb_pslv_active,HI_SC_STAT28_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT28_OFFSET)
HI_SET_GET(hi_sc_stat29_x2h_peri_slv_active,x2h_peri_slv_active,HI_SC_STAT29_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT29_OFFSET)
HI_SET_GET(hi_sc_stat31_bbp_sys_1control,bbp_sys_1control,HI_SC_STAT31_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT31_OFFSET)
HI_SET_GET(hi_sc_stat32_lte2soc_tbd,lte2soc_tbd,HI_SC_STAT32_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT32_OFFSET)
HI_SET_GET(hi_sc_stat32_reserved,reserved,HI_SC_STAT32_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT32_OFFSET)
HI_SET_GET(hi_sc_stat33_reserved,reserved,HI_SC_STAT33_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT33_OFFSET)
HI_SET_GET(hi_sc_stat34_reserved,reserved,HI_SC_STAT34_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT34_OFFSET)
HI_SET_GET(hi_sc_stat35_func_mbist_done_2,func_mbist_done_2,HI_SC_STAT35_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT35_OFFSET)
HI_SET_GET(hi_sc_stat36_func_mbist_done_3,func_mbist_done_3,HI_SC_STAT36_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT36_OFFSET)
HI_SET_GET(hi_sc_stat37_func_mbist_done_4,func_mbist_done_4,HI_SC_STAT37_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT37_OFFSET)
HI_SET_GET(hi_sc_stat38_func_mbist_done_5,func_mbist_done_5,HI_SC_STAT38_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT38_OFFSET)
HI_SET_GET(hi_sc_stat39_func_mbist_done_6,func_mbist_done_6,HI_SC_STAT39_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT39_OFFSET)
HI_SET_GET(hi_sc_stat40_func_mbist_done_7,func_mbist_done_7,HI_SC_STAT40_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT40_OFFSET)
HI_SET_GET(hi_sc_stat41_bbphy_mst_err,bbphy_mst_err,HI_SC_STAT41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT41_OFFSET)
HI_SET_GET(hi_sc_stat41_axi_amon_mst_err,axi_amon_mst_err,HI_SC_STAT41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT41_OFFSET)
HI_SET_GET(hi_sc_stat41_reserved,reserved,HI_SC_STAT41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT41_OFFSET)
HI_SET_GET(hi_sc_stat41_cpu_mst_err,cpu_mst_err,HI_SC_STAT41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT41_OFFSET)
HI_SET_GET(hi_sc_stat41_glb_mst_err,glb_mst_err,HI_SC_STAT41_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT41_OFFSET)
HI_SET_GET(hi_sc_stat42_sysapb_psel_err,sysapb_psel_err,HI_SC_STAT42_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT42_OFFSET)
HI_SET_GET(hi_sc_stat42_socapb_psel_err,socapb_psel_err,HI_SC_STAT42_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT42_OFFSET)
HI_SET_GET(hi_sc_stat42_x2h_peri_mst_err,x2h_peri_mst_err,HI_SC_STAT42_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT42_OFFSET)
HI_SET_GET(hi_sc_stat42_reserved,reserved,HI_SC_STAT42_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT42_OFFSET)
HI_SET_GET(hi_sc_stat43_x2h_peri_addr_err,x2h_peri_addr_err,HI_SC_STAT43_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT43_OFFSET)
HI_SET_GET(hi_sc_stat44_reserved,reserved,HI_SC_STAT44_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT44_OFFSET)
HI_SET_GET(hi_sc_stat44_addr_err,addr_err,HI_SC_STAT44_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT44_OFFSET)
HI_SET_GET(hi_sc_stat45_reserved_1,reserved_1,HI_SC_STAT45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT45_OFFSET)
HI_SET_GET(hi_sc_stat45_reserved_0,reserved_0,HI_SC_STAT45_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT45_OFFSET)
HI_SET_GET(hi_sc_stat46_addr_err,addr_err,HI_SC_STAT46_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT46_OFFSET)
HI_SET_GET(hi_sc_stat47_addr_err,addr_err,HI_SC_STAT47_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT47_OFFSET)
HI_SET_GET(hi_sc_stat48_addr_err,addr_err,HI_SC_STAT48_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT48_OFFSET)
HI_SET_GET(hi_sc_stat49_addr_err,addr_err,HI_SC_STAT49_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT49_OFFSET)
HI_SET_GET(hi_sc_stat50_addr_err,addr_err,HI_SC_STAT50_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT50_OFFSET)
HI_SET_GET(hi_sc_stat51_addr_err,addr_err,HI_SC_STAT51_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT51_OFFSET)
HI_SET_GET(hi_sc_stat52_addr_err,addr_err,HI_SC_STAT52_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT52_OFFSET)
HI_SET_GET(hi_sc_stat53_addr_err,addr_err,HI_SC_STAT53_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT53_OFFSET)
HI_SET_GET(hi_sc_stat54_addr_err,addr_err,HI_SC_STAT54_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT54_OFFSET)
HI_SET_GET(hi_sc_stat55_addr_err,addr_err,HI_SC_STAT55_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT55_OFFSET)
HI_SET_GET(hi_sc_stat56_addr_err,addr_err,HI_SC_STAT56_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT56_OFFSET)
HI_SET_GET(hi_sc_stat57_addr_err,addr_err,HI_SC_STAT57_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT57_OFFSET)
HI_SET_GET(hi_sc_stat58_addr_err,addr_err,HI_SC_STAT58_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT58_OFFSET)
HI_SET_GET(hi_sc_stat59_addr_err,addr_err,HI_SC_STAT59_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT59_OFFSET)
HI_SET_GET(hi_sc_stat60_addr_err,addr_err,HI_SC_STAT60_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT60_OFFSET)
HI_SET_GET(hi_sc_stat61_addr_err,addr_err,HI_SC_STAT61_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT61_OFFSET)
HI_SET_GET(hi_sc_stat62_addr_err,addr_err,HI_SC_STAT62_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT62_OFFSET)
HI_SET_GET(hi_sc_stat63_addr_err,addr_err,HI_SC_STAT63_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT63_OFFSET)
HI_SET_GET(hi_sc_stat64_addr_err,addr_err,HI_SC_STAT64_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT64_OFFSET)
HI_SET_GET(hi_sc_stat65_addr_err,addr_err,HI_SC_STAT65_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT65_OFFSET)
HI_SET_GET(hi_sc_stat66_addr_err,addr_err,HI_SC_STAT66_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT66_OFFSET)
HI_SET_GET(hi_sc_stat67_addr_err,addr_err,HI_SC_STAT67_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT67_OFFSET)
HI_SET_GET(hi_sc_stat68_addr_err,addr_err,HI_SC_STAT68_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT68_OFFSET)
HI_SET_GET(hi_sc_stat69_addr_err,addr_err,HI_SC_STAT69_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT69_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_gm_cmposer_lookup_err,pcie_gm_cmposer_lookup_err,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_radmx_cmposer_lookup_err,pcie_radmx_cmposer_lookup_err,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_pm_xtlh_block_tlp,pcie_pm_xtlh_block_tlp,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_cfg_mem_space_en,pcie_cfg_mem_space_en,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_cfg_rcb,pcie_cfg_rcb,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_rdlh_link_up,pcie_rdlh_link_up,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_pm_curnt_state,pcie_pm_curnt_state,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_cfg_aer_rc_err_int,pcie_cfg_aer_rc_err_int,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_cfg_aer_int_msg_num,pcie_cfg_aer_int_msg_num,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_xmlh_link_up,pcie_xmlh_link_up,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_wake,pcie_wake,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_cfg_eml_control,pcie_cfg_eml_control,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_hp_pme,pcie_hp_pme,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_hp_int,pcie_hp_int,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_hp_msi,pcie_hp_msi,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_pm_status,pcie_pm_status,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_pcie_ref_clk_req_n,pcie_ref_clk_req_n,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_mac_phy_powerdown_p2_exit_reg,mac_phy_powerdown_p2_exit_reg,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat70_radm_msg_req_id_low,radm_msg_req_id_low,HI_SC_STAT70_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT70_OFFSET)
HI_SET_GET(hi_sc_stat71_axi_parity_errs_reg,axi_parity_errs_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_app_parity_errs_reg,app_parity_errs_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_pm_linkst_in_l1,pm_linkst_in_l1,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_pm_linkst_in_l2,pm_linkst_in_l2,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_pm_linkst_l2_exit,pm_linkst_l2_exit,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_mac_phy_power_down,mac_phy_power_down,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_radm_correctabl_err_reg,radm_correctabl_err_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_radm_nonfatal_err_reg,radm_nonfatal_err_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_radm_fatal_err_reg,radm_fatal_err_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_radm_pm_to_pme_reg,radm_pm_to_pme_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_radm_pm_to_ack_reg,radm_pm_to_ack_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_radm_cpl_timeout_reg,radm_cpl_timeout_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_radm_msg_unlock_reg,radm_msg_unlock_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_cfg_pme_msi_reg,cfg_pme_msi_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_bridge_flush_not_reg,bridge_flush_not_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_link_req_rst_not_reg,link_req_rst_not_reg,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_pcie_cfg_aer_rc_err_msi,pcie_cfg_aer_rc_err_msi,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_pcie_cfg_sys_err_rc,pcie_cfg_sys_err_rc,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat71_radm_msg_req_id_high,radm_msg_req_id_high,HI_SC_STAT71_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT71_OFFSET)
HI_SET_GET(hi_sc_stat72_pcie_stat2,pcie_stat2,HI_SC_STAT72_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT72_OFFSET)
HI_SET_GET(hi_sc_stat73_pcie_stat3,pcie_stat3,HI_SC_STAT73_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT73_OFFSET)
HI_SET_GET(hi_sc_stat74_ltssm_state,ltssm_state,HI_SC_STAT74_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT74_OFFSET)
HI_SET_GET(hi_sc_stat74_mac_phy_rate,mac_phy_rate,HI_SC_STAT74_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT74_OFFSET)
HI_SET_GET(hi_sc_stat74_pcie_slv_err_int,pcie_slv_err_int,HI_SC_STAT74_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT74_OFFSET)
HI_SET_GET(hi_sc_stat74_trgt_lookup_empty,trgt_lookup_empty,HI_SC_STAT74_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT74_OFFSET)
HI_SET_GET(hi_sc_stat74_trgt_cpl_timeout_reg,trgt_cpl_timeout_reg,HI_SC_STAT74_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT74_OFFSET)
HI_SET_GET(hi_sc_stat74_reserved,reserved,HI_SC_STAT74_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT74_OFFSET)
HI_SET_GET(hi_sc_stat75_reserved,reserved,HI_SC_STAT75_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT75_OFFSET)
HI_SET_GET(hi_sc_stat76_obff_dec_idle_intr_status,obff_dec_idle_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_obff_dec_obff_intr_status,obff_dec_obff_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_obff_dec_cpu_active_intr_status,obff_dec_cpu_active_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_obff_dec_err_intr_status,obff_dec_err_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_obff_msg_idle_intr_status,obff_msg_idle_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_obff_msg_obff_intr_status,obff_msg_obff_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_obff_msg_cpu_active_intr_status,obff_msg_cpu_active_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_radm_msg_ltr_intr_status,radm_msg_ltr_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_cfg_msi_mask_chg_intr_status,cfg_msi_mask_chg_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_radm_qoverflow_intr_status,radm_qoverflow_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_amba_ordr_intr_status,amba_ordr_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_pcie_clkreq_in_n_intr_status,pcie_clkreq_in_n_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_pcie_clkreq_in_n_inv_intr_status,pcie_clkreq_in_n_inv_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_radm_vendor_msg_intr_status,radm_vendor_msg_intr_status,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_mac_phy_rxelecidle_disable,mac_phy_rxelecidle_disable,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_mac_phy_txcommonmode_disable,mac_phy_txcommonmode_disable,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat76_reserved,reserved,HI_SC_STAT76_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT76_OFFSET)
HI_SET_GET(hi_sc_stat77_obff_dec_owrd_cur_state,obff_dec_owrd_cur_state,HI_SC_STAT77_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT77_OFFSET)
HI_SET_GET(hi_sc_stat77_obff_enc_owre_cur_state,obff_enc_owre_cur_state,HI_SC_STAT77_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT77_OFFSET)
HI_SET_GET(hi_sc_stat77_cfg_obff_en,cfg_obff_en,HI_SC_STAT77_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT77_OFFSET)
HI_SET_GET(hi_sc_stat77_cfg_ltr_m_en,cfg_ltr_m_en,HI_SC_STAT77_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT77_OFFSET)
HI_SET_GET(hi_sc_stat77_cfg_pwr_budget_sel,cfg_pwr_budget_sel,HI_SC_STAT77_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT77_OFFSET)
HI_SET_GET(hi_sc_stat77_smlh_in_rl0s,smlh_in_rl0s,HI_SC_STAT77_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT77_OFFSET)
HI_SET_GET(hi_sc_stat77_radm_qoverflow,radm_qoverflow,HI_SC_STAT77_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT77_OFFSET)
HI_SET_GET(hi_sc_stat77_amba_ordr_mgr_wdt_int,amba_ordr_mgr_wdt_int,HI_SC_STAT77_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT77_OFFSET)
HI_SET_GET(hi_sc_stat77_reserved,reserved,HI_SC_STAT77_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT77_OFFSET)
HI_SET_GET(hi_sc_stat78_cfg_msi_mask,cfg_msi_mask,HI_SC_STAT78_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT78_OFFSET)
HI_SET_GET(hi_sc_stat79_cfg_ltr_max_latency,cfg_ltr_max_latency,HI_SC_STAT79_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT79_OFFSET)
HI_SET_GET(hi_sc_stat80_cm3_brch_stat,cm3_brch_stat,HI_SC_STAT80_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT80_OFFSET)
HI_SET_GET(hi_sc_stat80_cm3_core_halted,cm3_core_halted,HI_SC_STAT80_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT80_OFFSET)
HI_SET_GET(hi_sc_stat80_cm3_lockup,cm3_lockup,HI_SC_STAT80_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT80_OFFSET)
HI_SET_GET(hi_sc_stat80_reserved_1,reserved_1,HI_SC_STAT80_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT80_OFFSET)
HI_SET_GET(hi_sc_stat80_cm3_cur_int_priority,cm3_cur_int_priority,HI_SC_STAT80_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT80_OFFSET)
HI_SET_GET(hi_sc_stat80_reserved_0,reserved_0,HI_SC_STAT80_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT80_OFFSET)
HI_SET_GET(hi_sc_stat81_m3_stat1,m3_stat1,HI_SC_STAT81_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT81_OFFSET)
HI_SET_GET(hi_sc_stat82_m3_stat2,m3_stat2,HI_SC_STAT82_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT82_OFFSET)
HI_SET_GET(hi_sc_stat83_m3_stat3,m3_stat3,HI_SC_STAT83_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT83_OFFSET)
HI_SET_GET(hi_sc_stat84_m3_stat4,m3_stat4,HI_SC_STAT84_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT84_OFFSET)
HI_SET_GET(hi_sc_stat85_m3_stat5,m3_stat5,HI_SC_STAT85_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT85_OFFSET)
HI_SET_GET(hi_sc_stat85_reserved,reserved,HI_SC_STAT85_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT85_OFFSET)
HI_SET_GET(hi_sc_stat86_efuse_tsensor_trim,efuse_tsensor_trim,HI_SC_STAT86_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT86_OFFSET)
HI_SET_GET(hi_sc_stat87_app_ltr_latency,app_ltr_latency,HI_SC_STAT87_T,HI_SYSSC_AO_BASE_ADDR, HI_SC_STAT87_OFFSET)
HI_SET_GET(hi_version_id_version_id,version_id,HI_VERSION_ID_T,HI_SYSSC_AO_BASE_ADDR, HI_VERSION_ID_OFFSET)

#endif

#endif // __HI_SYSSC_AO_H__

