/******************************************************************************/
/*  Copyright (C), 2007-2014, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_sysreg_pd.h */
/* Version       : 2.0 */
/* Author        : xxx*/
/* Created       : 2014-02-19*/
/* Last Modified : */
/* Description   :  The C union definition file for the module sysreg_pd*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Author        : xxx*/
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_SYSREG_PD_H__
#define __HI_SYSREG_PD_H__

/*
 * Project: hi
 * Module : sysreg_pd
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    sysreg_pd �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_SC_CTRL58_OFFSET                               (0x4E8) /* PCIE0ϵͳ���ƼĴ���0�Ĵ����� */
#define    HI_SC_CTRL59_OFFSET                               (0x4EC) /* PCIE0ϵͳ���ƼĴ���1�Ĵ����� */
#define    HI_SC_CTRL60_OFFSET                               (0x4F0) /* PCIE0ϵͳ���ƼĴ���2�Ĵ����� */
#define    HI_SC_CTRL61_OFFSET                               (0x4F4) /* PCIE0ϵͳ���ƼĴ���3�Ĵ����� */
#define    HI_SC_CTRL62_OFFSET                               (0x4F8) /* PCIE0ϵͳ���ƼĴ���4�Ĵ����� */
#define    HI_SC_CTRL63_OFFSET                               (0x4FC) /* PCIE0ϵͳ���ƼĴ���5�Ĵ����� */
#define    HI_SC_CTRL64_OFFSET                               (0x500) /* PCIE0ϵͳ���ƼĴ���6�Ĵ����� */
#define    HI_SC_CTRL65_OFFSET                               (0x504) /* PCIE0ϵͳ���ƼĴ���7�Ĵ����� */
#define    HI_SC_CTRL66_OFFSET                               (0x508) /* PCIE0ϵͳ���ƼĴ���8�Ĵ����� */
#define    HI_SC_CTRL67_OFFSET                               (0x50C) /* PCIE0ϵͳ���ƼĴ���9�Ĵ����� */
#define    HI_SC_CTRL73_OFFSET                               (0x524) /* func mbistʹ�ܼĴ���0�� */
#define    HI_SC_CTRL74_OFFSET                               (0x528) /* func mbistʹ�ܼĴ���1�� */
#define    HI_SC_CTRL75_OFFSET                               (0x52C) /* func mbistʹ�ܼĴ���2�� */
#define    HI_SC_CTRL76_OFFSET                               (0x530) /* func mbistʹ�ܼĴ���3�� */
#define    HI_SC_CTRL77_OFFSET                               (0x534) /* func mbistʹ�ܼĴ���4�� */
#define    HI_SC_CTRL78_OFFSET                               (0x538) /* func mbistʹ�ܼĴ���5�� */
#define    HI_SC_CTRL79_OFFSET                               (0x53C) /* func mbistʹ�ܼĴ���6�� */
#define    HI_SC_CTRL80_OFFSET                               (0x540) /* func mbistʹ�ܼĴ���7�� */
#define    HI_SC_CTRL82_OFFSET                               (0x548) /* appa9 gpio1�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL83_OFFSET                               (0x54C) /* appa9 gpio2�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL84_OFFSET                               (0x550) /* appa9 gpio3�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL86_OFFSET                               (0x558) /* mdma9 gpio1�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL87_OFFSET                               (0x55C) /* mdma9 gpio2�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL88_OFFSET                               (0x560) /* mdma9 gpio3�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL89_OFFSET                               (0x564) /* hifi gpio0�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL90_OFFSET                               (0x568) /* hifi gpio1�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL91_OFFSET                               (0x56C) /* hifi gpio2�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL92_OFFSET                               (0x570) /* hifi gpio3�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL93_OFFSET                               (0x574) /* dsp0 gpio0�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL94_OFFSET                               (0x578) /* dsp0 gpio1�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL95_OFFSET                               (0x57C) /* dsp0 gpio2�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL96_OFFSET                               (0x580) /* dsp0 gpio3�жϰ�λʹ�ܼĴ����� */
#define    HI_SC_CTRL97_OFFSET                               (0x584) /* func mbist���ƼĴ����� */
#define    HI_SC_CTRL99_OFFSET                               (0x58C) /* M3 GPIO1�ж�ʹ�ܼĴ����� */
#define    HI_SC_CTRL100_OFFSET                              (0x590) /* M3 GPIO2�ж�ʹ�ܼĴ����� */
#define    HI_SC_CTRL101_OFFSET                              (0x594) /* M3 GPIO3�ж�ʹ�ܼĴ����� */
#define    HI_SC_CTRL102_OFFSET                              (0x598) /* �����Ĵ����� */
#define    HI_SC_CTRL106_OFFSET                              (0x5A8) /* PCIE0ϵͳ���ƼĴ���10�Ĵ����� */
#define    HI_SC_CTRL107_OFFSET                              (0x5AC) /* PCIE0ϵͳ���ƼĴ���11�Ĵ����� */
#define    HI_SC_CTRL108_OFFSET                              (0x5B0) /* PCIE��GMAC�ο�ʱ�����üĴ��� */
#define    HI_SC_CTRL109_OFFSET                              (0x5B4) /* PCIE PHYϵͳ���ƼĴ���0�Ĵ����� */
#define    HI_SC_CTRL110_OFFSET                              (0x5B8) /* PCIE PHYϵͳ���ƼĴ���1�Ĵ����� */
#define    HI_SC_CTRL111_OFFSET                              (0x5BC) /* PCIE PHYϵͳ���ƼĴ���2�Ĵ����� */
#define    HI_SC_CTRL112_OFFSET                              (0x5C0) /* PCIE PHYϵͳ���ƼĴ���3�Ĵ����� */
#define    HI_SC_CTRL113_OFFSET                              (0x5C4) /* PCIE0ϵͳ���ƼĴ���12�Ĵ��� */
#define    HI_SC_CTRL114_OFFSET                              (0x5C8) /* PCIE0ϵͳ���ƼĴ���13�Ĵ��� */
#define    HI_SC_CTRL115_OFFSET                              (0x5CC) /* PCIE0ϵͳ���ƼĴ���14�Ĵ��� */
#define    HI_SC_CTRL116_OFFSET                              (0x5D0) /* PCIE0ϵͳ���ƼĴ���15�Ĵ��� */
#define    HI_SC_CTRL117_OFFSET                              (0x5D4) /* PCIE0ϵͳ���ƼĴ���16�Ĵ��� */
#define    HI_SC_CTRL118_OFFSET                              (0x5D8) /* PCIE0ϵͳ���ƼĴ���17�Ĵ��� */
#define    HI_SC_CTRL119_OFFSET                              (0x5DC) /* PCIE0ϵͳ���ƼĴ���18�Ĵ��� */
#define    HI_SC_CTRL120_OFFSET                              (0x5E0) /* PCIE0ϵͳ���ƼĴ���19�Ĵ��� */


#ifndef __ASSEMBLY__

/********************************************************************************/
/*    sysreg_pd �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    pcie_slv_awmisc_info       : 22; /* [21..0] PCIe��X1����������bit[4:0]��AXI transaction��s TYPE.bit[5]��AXI Transaction��s BCM��bit[6]��AXI Transaction��s EP��bit[7]��AXI Transaction��s TD��bit[9:8]��AXI Transaction��s ATTR��bit[12:10]��AXI Transaction��s TC��bit[20:13]��AXI Transaction��s MSG code��bit[21]���Ƿ�ʹ��ѡ�����õĴ������͡�0��ѡ��ͨ����ַӳ���������ͣ�1��ѡ��Ĵ������õ����ͣ�Ҳ���Ǳ��Ĵ�����[4:0]�� */
        unsigned int    pcie_slv_resp_err_map      : 6; /* [27..22] PCIe��X1���������� Slave��Ӧ�ļ���Error�����bit[22]�� CPL UR��bit[23]�� Not used��bit[24]�� CPL CRS��bit[25]�� CPL Poisoned��bit[26]�� CPL ECRC��bit[27]�� CPL Abort (MLF or UC)��- UR = Unsupported request- CRS = Completion retry request- UC = Unexpected completion- MLF = Malformed */
        unsigned int    pcie_device_type           : 4; /* [31..28] PCIe��X1�������������͡�0000�� PCI Express Endpoint device��0001�� Legacy PCI Express Endpoint device��0100�� Root Port of PCI Express Root Complex�������������� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL58_T;    /* PCIE0ϵͳ���ƼĴ���0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pcie_slv_armisc_info       : 22; /* [21..0] PCIe��X1����������[4:0]��AXI transaction��s TYPE.bit[5]��AXI Transaction��s BCM��bit[6]��AXI Transaction��s EP��bit[7]��AXI Transaction��s TD��bit[9:8]��AXI Transaction��s ATTR��bit[12:10]��AXI Transaction��s TC��bit[20:13]��AXI Transaction��s MSG code��bit[21]���Ƿ�ʹ��ѡ�����õĴ������ͣ�0��ѡ��ͨ����ַӳ���������ͣ�1��ѡ��Ĵ������õ����ͣ�Ҳ���Ǳ��Ĵ�����[4:0]�� */
        unsigned int    reserved                   : 1; /* [22..22] ���� */
        unsigned int    pcie_app_clk_req_n         : 1; /* [23..23] PCIe��X1�������� Ӧ�ò�����ʱ����Ч0������ʱ�ӣ�1��������ʱ�ӣ� */
        unsigned int    pcie_ven_msg_code          : 8; /* [31..24] PCIe��X1��������Vendor�����Message TLP��Message Core�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL59_T;    /* PCIE0ϵͳ���ƼĴ���1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pcie_mstr_bmisc_info       : 14; /* [13..0] PCIe��X1��������AXI Master д��Ӧ��misc��Ϣbit[1:0]��AXI response��s attributesbit[2]��AXI response with Bad EOT assigned to signal native PCIecore to drop this responsebit[5:3]�� AXI response��s TCbit[6]��AXI response��s BCMbit[7]��AXI response��s EPbit[8]��AXI response��s TDbit[11:9]��AXI response��s Function number                           bit[13��12]��Master Response Error Map. */
        unsigned int    pcie_mstr_rmisc_info       : 12; /* [25..14] PCIe��X1��������AXI Master ����Ӧ��misc��Ϣbit[15:14]��AXI response��s attributes��bit[16]��AXI response with Bad EOT�� assigned to signal native PCIecore to drop this response��bit[19:17]��AXI response��s TC��bit[20]��AXI response��s BCM��bit[21]��AXI response��s EP��bit[22]��AXI response��s TD��bit[25:23]��AXI response��s Function number�� */
        unsigned int    pcie_ven_msi_req           : 1; /* [26..26] PCIe��X1��������������Ӧ�ò��Ƿ�������MSI��0��������1������ */
        unsigned int    pcie_ven_msi_vector        : 5; /* [31..27] PCIe��X1������������Messageģʽʹ�ܵ�ʱ����������MSI���ݼĴ��������5bits�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL60_T;    /* PCIE0ϵͳ���ƼĴ���2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pcie_ven_msg_req           : 1; /* [0..0] PCIe��X1����������Ӧ�ò�������һ��Vendor �����Message��һ��req��Ч������Ҫ���ֵ�ven_msg_grant��Ч��0��������1������ */
        unsigned int    pcie_ven_msg_fmt           : 2; /* [2..1] PCIe��X1����������Vendor �����Message TLP��Format bit�� */
        unsigned int    pcie_ven_msg_type          : 5; /* [7..3] PCIe��X1����������Vendor �����Message TLP��Type bit�� */
        unsigned int    pcie_ven_msg_td            : 1; /* [8..8] PCIe��X1����������Vendor �����Message TLP��Digest bit�� */
        unsigned int    pcie_ven_msg_ep            : 1; /* [9..9] PCIe��X1����������Vendor �����Message TLP��EP�� */
        unsigned int    pcie_ven_msg_attr          : 2; /* [11..10] PCIe��X1����������Vendor �����Message TLP��Attributes�� */
        unsigned int    pcie_ven_msg_len           : 10; /* [21..12] PCIe��X1����������Vendor �����Message TLP��Length�� */
        unsigned int    pcie_ven_msg_tag           : 8; /* [29..22] PCIe��X1����������Vendor �����Message TLP��Tag�� */
        unsigned int    reserved                   : 2; /* [31..30] ������������0��д��Ч�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL61_T;    /* PCIE0ϵͳ���ƼĴ���3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pice_ven_msg_data_low      : 32; /* [31..0] PCIe��X1����������Vendor�����Message TLP��Message ���ݵĵ�32bit�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL62_T;    /* PCIE0ϵͳ���ƼĴ���4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pice_ven_msg_data_high     : 32; /* [31..0] PCIe��X1����������Vendor�����Message TLP��Message ���ݵĸ�32bit�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL63_T;    /* PCIE0ϵͳ���ƼĴ���5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    slot_led_blink_period      : 32; /* [31..0] Slot״ָ̬ʾLED��˸���ڿ��ƣ�LED����˸���ڣ��üĴ�����ֵ��Period_of_pcie_clk(8ns)��. */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL64_T;    /* PCIE0ϵͳ���ƼĴ���6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pcie_app_init_rst          : 1; /* [0..0] PCIe��X1����������Ӧ�ò�������һ��Hot Reset�����ζ˿��豸��0����Ч��1����Ч�� */
        unsigned int    pcie_app_req_entr_l1       : 1; /* [1..1] PCIe��X1����������Ӧ�ò��������L1״̬��0����Ч��1����Ч�� */
        unsigned int    pcie_app_ready_entr_l23    : 1; /* [2..2] PCIe��X1����������Ӧ�ò�׼������L23״̬��0����Ч��1����Ч�� */
        unsigned int    pcie_app_req_exit_l1       : 1; /* [3..3] PCIe��X1����������Ӧ�ò������˳�L1״̬��0����Ч��1����Ч�� */
        unsigned int    pcie_app_req_retry_en      : 1; /* [4..4] PCIe��X1����������������ź���Ч��Core���������������0����Ч��1����Ч�� */
        unsigned int    pcie_sys_int               : 1; /* [5..5] PCIe��X1������������sys_int�ӵͱ�ߵ�ʱ��Core����һ��Assert_INTx Message����sys_int�Ӹ߱�͵�ʱ��Core����һ��Deassert_INTx Message�� */
        unsigned int    pcie_outband_pwrup_cmd     : 1; /* [6..6] PCIe��X1����������Ӧ�ò�������PMC״̬���ӵ͹���״̬���ѣ���Ҫ��Чһ��cycle��0����Ч��1����Ч�� */
        unsigned int    pcie_app_unlock_msg        : 1; /* [7..7] PCIe��X1����������Ӧ�ò��������һ��Unlock Message����Чһ��cycle��Core���ᷴ��ȷ����Ϣ��0����Ч��1����Ч�� */
        unsigned int    pcie_apps_pm_xmt_turnoff   : 1; /* [8..8] PCIe��X1����������Ӧ�ò��������һ��PM_Turm_off Message����Чһ��cycle��Core���ᷴ��ȷ����Ϣ��0����Ч��1����Ч�� */
        unsigned int    pcie_apps_pm_xmt_pme       : 1; /* [9..9] PCIe��X1����������Ӧ���߼���Core�ӵ͹���״̬���ѡ�0����Ч��1����Ч�� */
        unsigned int    pcie_sys_aux_pwr_det       : 1; /* [10..10] PCIe��X1����������������Դ��⣬�����Ƿ���ڸ�����Դ��0�������ڣ�1�����ڡ� */
        unsigned int    pcie_app_ltssm_enable      : 1; /* [11..11] PCIe��X1����������Ӧ�ò���Ҫ�ڸ�λ����LTSSM�����״̬����������ź�Ϊ0��ֱ��Ӧ�ò�׼���á� */
        unsigned int    pcie_cfg_pwr_ctrler_ctrl_pol : 1; /* [12..12] PCIe��X1����������Socket��Դ���Ƽ��Կ��ơ�0:����Ч��1:����Ч�� */
        unsigned int    reserved_2                 : 1; /* [13..13] ���� */
        unsigned int    pcie_sys_mrl_sensor_state  : 1; /* [14..14] PCIe��X1��������������MRL������״���������MRL�������Ļ�����0��MRL�أ�1��MRL���� */
        unsigned int    pcie_sys_pwr_fault_det     : 1; /* [15..15] PCIe��X1����������������Դ�������ڲ������⵽��Դ���ϣ�0��δ��⵽��1����⵽�� */
        unsigned int    pcie_sys_mrl_sensor_chged  : 1; /* [16..16] PCIe��X1��������������MRL sensor��״̬�Ƿ�ı䣻0��δ�ı䣻1���ı䡣 */
        unsigned int    reserved_1                 : 1; /* [17..17] ���� */
        unsigned int    pcie_sys_cmd_cpled_int     : 1; /* [18..18] PCIe��X1������������������жϡ�����Hot-Plug���������һ�����0���ж���Ч��1���ж���Ч�� */
        unsigned int    pcie_sys_eml_interlock_engaged : 1; /* [19..19] PCIe DM������������źš������Ƿ�ʹ���˻��绥�����ơ�               0��δʹ��                         1��ʹ�� */
        unsigned int    reserved_0                 : 1; /* [20..20] ���� */
        unsigned int    pcie_int_ctrl              : 8; /* [28..21] PCIe��X1���������ж����Σ�����Ч[0]:��Ӧcfg_aer_rc_err_int[1]:��Ӧven_msi_int[2]:��Ӧmisc_int[3]:��Ӧcfg_pme_int[4]:ѡ���ж�inta�����жϽ�[5]:ѡ���ж�intb����MSI�����жϽ�[6]:ѡ���ж�intc�����жϽ�[7]:ѡ���ж�intd�����жϽ� */
        unsigned int    pcie_linkdown_auto_rstn_disable : 1; /* [29..29] LINKDOWN�¼��Զ�������·ѵ����ֹ���ơ�0������������·ѵ����1����ֹ������·ѵ���� */
        unsigned int    pcie_err_bresp_enable      : 1; /* [30..30] PCIe������AXI slave�ӿ�д������Ӧ(BRESP�������ϱ�ʹ�ܿ��ơ�0��BRESP�̶�Ϊ2'h0��1����ʵ�ϱ�BRESP�� */
        unsigned int    cipe_err_rresp_enable      : 1; /* [31..31] PCIe������AXI slave�ӿڶ���Ӧ(RRESP�������ϱ�ʹ�ܿ����źš�0��RRESP�̶�Ϊ2'h0��1����ʵ�ϱ�RRESP�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL65_T;    /* PCIE0ϵͳ���ƼĴ���7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 3; /* [2..0] ���� */
        unsigned int    cfg_l1_aux_clk_switch_core_clk_gate_en : 1; /* [3..3] ����ʱ��(auxclk)�л��źŵ�һ��ʹ�ܿ��Ʒ��������豸״̬ΪD0��D1����·״̬ΪL1ʱ�����źſ���PCIe core����ʱ���Ƿ��л�������ʱ�ӡ�0�����л�������ʱ�ӣ�1���л�������ʱ�ӡ� */
        unsigned int    cfg_l1_mac_powerdown_override_to_p2_en : 1; /* [4..4] ����·״̬ΪL1�ڼ䣬�ڼ����Ƴ��ο�ʱ�ӣ�refclk��ʱ�����źſ����Ƿ�ʹ��P2���P1��0���������1������� */
        unsigned int    pcie_state2_sel            : 2; /* [6..5] PCIe״̬�Ĵ���2�Ĵ�����PERI_PCIE_STAT2�������MUXѡ���ź� */
        unsigned int    pcie_state3_sel            : 2; /* [8..7] PCIe״̬�Ĵ���3�Ĵ�����PERI_PCIE_STAT3�������MUXѡ���ź� */
        unsigned int    reserved_0                 : 23; /* [31..9] ���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL66_T;    /* PCIE0ϵͳ���ƼĴ���8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL67_T;    /* PCIE0ϵͳ���ƼĴ���9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] func mbistʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL73_T;    /* func mbistʹ�ܼĴ���0�� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] func mbistʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL74_T;    /* func mbistʹ�ܼĴ���1�� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] func mbistʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL75_T;    /* func mbistʹ�ܼĴ���2�� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] func mbistʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL76_T;    /* func mbistʹ�ܼĴ���3�� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] func mbistʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL77_T;    /* func mbistʹ�ܼĴ���4�� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] func mbistʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL78_T;    /* func mbistʹ�ܼĴ���5�� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] func mbistʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL79_T;    /* func mbistʹ�ܼĴ���6�� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] func mbistʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL80_T;    /* func mbistʹ�ܼĴ���7�� */

typedef union
{
    struct
    {
        unsigned int    appa9_gpio1_en             : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL82_T;    /* appa9 gpio1�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    appa9_gpio2_en             : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL83_T;    /* appa9 gpio2�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    appa9_gpio3_en             : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL84_T;    /* appa9 gpio3�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    mdma9_gpio1_en             : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL86_T;    /* mdma9 gpio1�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    mdma9_gpio2_en             : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL87_T;    /* mdma9 gpio2�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    mdma9_gpio3_en             : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL88_T;    /* mdma9 gpio3�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    hifi_gpio0_en              : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL89_T;    /* hifi gpio0�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    hifi_gpio1_en              : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL90_T;    /* hifi gpio1�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    hifi_gpio2_en              : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL91_T;    /* hifi gpio2�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    hifi_gpio3_en              : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL92_T;    /* hifi gpio3�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dsp0_gpio0_en              : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL93_T;    /* dsp0 gpio0�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dsp0_gpio1_en              : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL94_T;    /* dsp0 gpio1�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dsp0_gpio2_en              : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL95_T;    /* dsp0 gpio2�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dsp0_gpio3_en              : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL96_T;    /* dsp0 gpio3�жϰ�λʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ÿ1bit����1bit�жϡ�0���ж�ʹ�ܣ�1���жϲ�ʹ�ܣ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL97_T;    /* func mbist���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    cm3_gpio1_en               : 32; /* [31..0] M3 GPIO1�ж�ʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL99_T;    /* M3 GPIO1�ж�ʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    cm3_gpio2_en               : 32; /* [31..0] M3 GPIO2�ж�ʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL100_T;    /* M3 GPIO2�ж�ʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    cm3_gpio3_en               : 32; /* [31..0] M3 GPIO3�ж�ʹ�ܼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL101_T;    /* M3 GPIO3�ж�ʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 32; /* [31..0] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL102_T;    /* �����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cfg_aer_rc_err_msi_mask    : 1; /* [0..0] cfg_aer_rc_err_msi�ж����� */
        unsigned int    cfg_sys_err_rc_mask        : 1; /* [1..1] cfg_sys_err_rc�ж����� */
        unsigned int    radm_correctable_err_mask  : 1; /* [2..2] radm_correctable_err�ж����� */
        unsigned int    radm_nonfatal_err_mask     : 1; /* [3..3] radm_nonfatal_err�ж����� */
        unsigned int    radm_fatal_err_mask        : 1; /* [4..4] radm_fatal_err�ж����� */
        unsigned int    radm_pm_pme_mask           : 1; /* [5..5] radm_pm_pme�ж����� */
        unsigned int    radm_pm_to_ack_mask        : 1; /* [6..6] radm_pm_to_ack�ж����� */
        unsigned int    ven_msg_int_mask           : 1; /* [7..7] ven_msg_int�ж����� */
        unsigned int    radm_cpl_timeout_mask      : 1; /* [8..8] radm_cpl_timeout�ж����� */
        unsigned int    radm_msg_unlock_mask       : 1; /* [9..9] radm_msg_unlock�ж����� */
        unsigned int    cfg_pme_msi_mask           : 1; /* [10..10] cfg_pme_msi�ж����� */
        unsigned int    bridge_flush_not_mask      : 1; /* [11..11] bridge_flush_not�ж����� */
        unsigned int    link_req_rst_not_mask      : 1; /* [12..12] link_req_rst_not�ж����� */
        unsigned int    pcie_p2_exit_reg_mask      : 1; /* [13..13] pcie��P2�͹����˳��ж����� */
        unsigned int    reserved_1                 : 7; /* [20..14]  */
        unsigned int    pcie_radm_pm_turnoff_mask  : 1; /* [21..21] PCIe������radm_pm_turnoff�ж����� */
        unsigned int    reserved_0                 : 10; /* [31..22] ���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL106_T;    /* PCIE0ϵͳ���ƼĴ���10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pcie_cfg_aer_rc_msi_clr    : 1; /* [0..0] cfg_aer_rc_err_msi�ж���� */
        unsigned int    pcie_cfg_sys_err_rc_clr    : 1; /* [1..1] cfg_sys_err_rc�ж���� */
        unsigned int    pcie_radm_corretable_err_clr : 1; /* [2..2] radm_correctable_err�ж���� */
        unsigned int    pcie_radm_nonfatal_err_clr : 1; /* [3..3] radm_nonfatal_err�ж���� */
        unsigned int    pcie_radm_fatal_err_clr    : 1; /* [4..4] radm_fatal_err�ж���� */
        unsigned int    pcie_radm_pm_pme_clr       : 1; /* [5..5] radm_pm_pme�ж���� */
        unsigned int    pcie_radm_pm_to_ack_clr    : 1; /* [6..6] radm_pm_to_ack�ж���� */
        unsigned int    pcie_ven_msg_int_clr       : 1; /* [7..7] ven_msg_int�ж���� */
        unsigned int    pcie_radm_cpl_timeout_clr  : 1; /* [8..8] radm_cpl_timeout�ж���� */
        unsigned int    pcie_radm_msg_unlock_clr   : 1; /* [9..9] radm_msg_unlock�ж���� */
        unsigned int    pcie_cfg_pme_msi_clr       : 1; /* [10..10] cfg_pme_msi�ж���� */
        unsigned int    pcie_bridge_flush_not_clr  : 1; /* [11..11] bridge_flush_not�ж���� */
        unsigned int    pcie_link_req_rst_not_clr  : 1; /* [12..12] link_req_rst_not�ж���� */
        unsigned int    pcie_p2_exit_int_clr       : 1; /* [13..13] PCIec��P2�͹����˳��ж���� */
        unsigned int    pcie_slv_err_int_clr       : 1; /* [14..14] PCIe������AXI slave�����ж���� */
        unsigned int    pcie_ven_msi_func_num      : 3; /* [17..15] PCIe������Vendor MSI���ܺ� */
        unsigned int    pcie_ven_msg_func_num      : 3; /* [20..18] PCIe������Vendor Message���ܺ� */
        unsigned int    pcie_radm_pm_turnoff_clr   : 1; /* [21..21] PCIe������radm_pm_turnoff�ж���� */
        unsigned int    reserved                   : 10; /* [31..22] ���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL107_T;    /* PCIE0ϵͳ���ƼĴ���11�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pcie0_intx_req             : 1; /* [0..0]  */
        unsigned int    pcie0_msi_req              : 1; /* [1..1]  */
        unsigned int    reserved_5                 : 2; /* [3..2] ������ */
        unsigned int    pcie0_pad_phy_mask         : 1; /* [4..4]  */
        unsigned int    pcie0_pad_out_mask         : 1; /* [5..5]  */
        unsigned int    reserved_4                 : 2; /* [7..6] ������ */
        unsigned int    pcie0_inner_phy_mask       : 1; /* [8..8]  */
        unsigned int    pcie0_inner_out_mask       : 1; /* [9..9]  */
        unsigned int    reserved_3                 : 2; /* [11..10] ������ */
        unsigned int    pcie0_out_gatedclock_en    : 1; /* [12..12]  */
        unsigned int    pcie0_phy_gatedclock_en    : 1; /* [13..13]  */
        unsigned int    reserved_2                 : 2; /* [15..14] ������ */
        unsigned int    pcie0_refclk_oen_sel       : 1; /* [16..16] PCIE0�ο�ʱ�����ʹ��ѡ��0������ϵͳ���������ã�pcie0_refclk_oen_cfg����1������PCIE����������� */
        unsigned int    pcie0_refclk_oen_cfg       : 1; /* [17..17] PCIE0�ο�ʱ�����ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    gmac_refclk_sel            : 1; /* [18..18] �����gmac�Խ������Ĳο�ʱ�ӡ�0��25MHz��1:125MHz�� */
        unsigned int    reserved_1                 : 1; /* [19..19] ������ */
        unsigned int    reserved_0                 : 12; /* [31..20]  */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL108_T;    /* PCIE��GMAC�ο�ʱ�����üĴ��� */

typedef union
{
    struct
    {
        unsigned int    pipe_tx2rx_loopbk          : 1; /* [0..0] PHY����˿��źţ�PIPE���ͣ�TX�����ص����գ�RX�� */
        unsigned int    pipe_pclkreq_n             : 2; /* [2..1] ʱ�����󣬵���Ч��0:No clock removal1: Clock removal for executing L1 with clock PM2: Clock removal for executeing L1 with substates3: Clock removal for executing L1 with substates */
        unsigned int    pipe_pclkreq_n_sel         : 1; /* [3..3] pipe_pclkreq_n[0] MUXѡ��0: ѡ��mac_pclkreq_n1: ѡ��pipe_pclkreq_n[0] */
        unsigned int    pcs_clk_req                : 1; /* [4..4] �ⲿ�߼�����PHY mpll_dword_clk��0: ������1: ���� */
        unsigned int    pcs_common_clocks          : 1; /* [5..5] Ϊ��������ͨ·ѡ�񹫹�ʱ��ģʽ��0: ��ʹ�ù���ʱ��1: ʹ�ù���ʱ�� */
        unsigned int    pipe_port_sel              : 1; /* [6..6] PIPEʹ������0: ����PIPE1: ʹ��PIPE */
        unsigned int    reserved_2                 : 1; /* [7..7] ������ */
        unsigned int    pipe_rx_elecidle_disable   : 1; /* [8..8] ����PIPE�������������м���·��0: ʹ��1: ���� */
        unsigned int    pipe_tx_common_mode_disable : 1; /* [9..9] ���ܷ���(TX)��ģ���ֵ�·��0: ʹ��1: ���� */
        unsigned int    pipe_clkreq_n_cfg          : 1; /* [10..10] ������õ�phy_clkreq_n����pipe_clkreq_n_selΪ1ʱ��Ч��0: ������ʱ��1: ����ʱ�� */
        unsigned int    pipe_clkreq_n_sel          : 1; /* [11..11] phy_clkreq_n�ź���Դѡ��0: ʹ���߼�������pipe_clkreq_n1: ʹ��������õ�pipe_clkreq_n_cfg */
        unsigned int    reserved_1                 : 4; /* [15..12] ������ */
        unsigned int    phy_res_ack_in_cfg         : 1; /* [16..16] ������õ�phy_res_ack_in�źš� */
        unsigned int    phy_res_ack_in_sel         : 1; /* [17..17] phy_res_ack_in�ź���Դѡ��0: ʹ���߼�������phy_res_req_out1: ʹ��������õ�phy_res_ack_in_cfg */
        unsigned int    phy_res_req_in             : 1; /* [18..18] PHY����˿��źš� */
        unsigned int    phy_rtune_req              : 1; /* [19..19] PHY����˿��źš� */
        unsigned int    phy_test_burnin            : 1; /* [20..20] PHY����˿��źš� */
        unsigned int    phy_test_bypass            : 1; /* [21..21] PHY����˿��źš� */
        unsigned int    phy_test_powerdown         : 1; /* [22..22] PHY����˿��źš� */
        unsigned int    reserved_0                 : 9; /* [31..23] ���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL109_T;    /* PCIE PHYϵͳ���ƼĴ���0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    phy_mpll_multiplier        : 7; /* [6..0] PHY����˿��źš� */
        unsigned int    phy_ref_clkdiv2            : 1; /* [7..7] PHY����˿��źš� */
        unsigned int    phy_ref_use_pad            : 1; /* [8..8] PHY����˿��źš� */
        unsigned int    ref_alt_clk_gt_en          : 1; /* [9..9] ref_alt_clkʱ���ſ�ʹ�ܡ�0: ��ʹ��1: ʹ�� */
        unsigned int    reserved_1                 : 6; /* [15..10] ������ */
        unsigned int    phy_reset                  : 1; /* [16..16] PHY��λ�źţ�����Ч����phy_reset_selΪ0ʱ��Ч�� */
        unsigned int    phy_reset_sel              : 1; /* [17..17] phy_reset�ź���Դѡ��0: ʹ��������õ�phy_reset1:  ʹ��ȡ�����pipe_reset_n */
        unsigned int    pipe_reset_n_cfg           : 1; /* [18..18] ������õ�pipe_reset_n������Ч����pipe_reset_selΪ1ʱ��Ч�� */
        unsigned int    pipe_reset_sel             : 1; /* [19..19] pipe_reset_n�ź���Դѡ��0: ʹ��ȡ�����pipe_reset_n1: ʹ��������õ�phy_reset */
        unsigned int    reserved_0                 : 12; /* [31..20] ���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL110_T;    /* PCIE PHYϵͳ���ƼĴ���1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    phy_los_bias               : 3; /* [2..0] PHY����˿��źš� */
        unsigned int    phy_los_level              : 5; /* [7..3] PHY����˿��źš� */
        unsigned int    phy_rx_eq                  : 3; /* [10..8] PHY����˿��źš� */
        unsigned int    pcs_tx_deemph_gen2_3p5db   : 6; /* [16..11] PHY����˿��źš� */
        unsigned int    pcs_tx_deemph_gen2_6db     : 6; /* [22..17] PHY����˿��źš� */
        unsigned int    reserved_1                 : 1; /* [23..23] ���� */
        unsigned int    pcs_tx_deemph_gen1         : 6; /* [29..24] PHY����˿��źš� */
        unsigned int    reserved_0                 : 2; /* [31..30] ���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL111_T;    /* PCIE PHYϵͳ���ƼĴ���2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pcs_tx_swing_full          : 7; /* [6..0] PHY����˿��źš� */
        unsigned int    pcs_tx_swing_low           : 7; /* [13..7] PHY����˿��źš� */
        unsigned int    phy_tx_term_offset         : 5; /* [18..14] PHY����˿��źš� */
        unsigned int    reserved_2                 : 5; /* [23..19] ������ */
        unsigned int    phy_tx_vboost_lvl          : 3; /* [26..24] PHY����˿��źš� */
        unsigned int    reserved_1                 : 1; /* [27..27] ���� */
        unsigned int    vreg_bypass                : 1; /* [28..28] PHY����˿��źš� */
        unsigned int    reserved_0                 : 3; /* [31..29] ���� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL112_T;    /* PCIE PHYϵͳ���ƼĴ���3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    pcie_perst_out_n           : 1; /* [0..0] PCIe PERST�������pcie_perst_oeΪ��ʱ��Ч��PCIe PERST#Ϊ����Ч��λ�źš� */
        unsigned int    pcie_perst_oe              : 1; /* [1..1] PCIe PERST���ʹ�ܣ�����Ч�� */
        unsigned int    pcie_perst_in_n_ctrl       : 2; /* [3..2] ��pcie_ClK_RSTģ��pcie_perst_in_n�����ſصĿ����źš�00:�ſص�0��01:�ſص�1��10:�ſص�0��11:ʹ��ԭֵ��ע:1�����ֶξ���PCIeģ���Ƿ���PERST#��λ���������źŵ�Ӱ�졣ע2�����ֶβ�Ӱ��pcie_perst_oe��pcie_perst_out_n��ֵ������Ӱ��PERST#��λ��������źš�ע3����RCģʽ�����ֶ���Ϊ01��ע4����EPģʽ�����ֶ���Ϊ11�� */
        unsigned int    mac_phy_pclkreq_n_0_ctrl   : 1; /* [4..4] ��mac_phy_pclkreq_n[0]�����ſصĿ����źţ�0:�ſص�0��1:ʹ��ԭֵ�� */
        unsigned int    mac_phy_pclkreq_n_1_ctrl   : 1; /* [5..5] ��mac_phy_pclkreq_n[1]�����ſصĿ����źţ�0:�ſص�0��1:ʹ��ԭֵ�� */
        unsigned int    cfg_l1sub_en_ctrl          : 2; /* [7..6] ��cfg_l1sub_en�����ſصĿ����źţ�00:ʹ��ԭֵ��01:�ſص�1��10:�ſص�0��11:�ſص�0�� */
        unsigned int    clkreq_n_ctrl0             : 2; /* [9..8] ��clkreq_n�����ſصĿ����źţ�00:ʹ��ԭֵ��01:�ſص�1��10:�ſص�0��11:�ſص�0��ע1��clkreq_n�����ſغ�����CLKREQ#���š� */
        unsigned int    clkreq_n_ctrl1             : 2; /* [11..10] ��clkreq_n�����ſصĿ����źţ�00:ʹ��ԭֵ��01:�ſص�1��10:�ſص�0��11:�ſص�0��ע1��clkreq_n�����ſغ�����CLKREQ#���š� */
        unsigned int    rc_wake_n_ctrl             : 1; /* [12..12] ��rc_wake_n�����ſصĿ����źţ�0:ʹ��ԭֵ��1:�ſص�1�� */
        unsigned int    ep_wake_n_ctrl             : 1; /* [13..13] ��ep_wake_n�����ſصĿ����źţ�0:ʹ��ԭֵ��1:�ſص�1�� */
        unsigned int    obff_enc_owre_wake_ctrl    : 1; /* [14..14] ��obff_enc_owre_wake�����ſصĿ����źţ�0:ʹ��ԭֵ��1:�ſص�1�� */
        unsigned int    dwc_pcie_dm_wake_n_ctrl    : 2; /* [16..15] ��dwc_pcie_dm_wake_n�����ſصĿ����źţ�00:ʹ��ԭֵ��01:�ſص�1��10:�ſص�0��11:�ſص�0�� */
        unsigned int    reserved                   : 15; /* [31..17] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL113_T;    /* PCIE0ϵͳ���ƼĴ���12�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    obff_dec_app_init          : 1; /* [0..0] Ӧ���߼���obff_dec_filter�ڲ�״̬�����г�ʼ����ʹ�ܿ����źš�0:��ʹ�ܣ�1:ʹ�ܣ�ע1�����ź���obff_dec_app_idle��obff_dec_app_obff��obff_dec_app_cpu_act��ϣ���obff_dec_filter�ڲ�״̬����ʼ������Ӧ��״̬�� */
        unsigned int    obff_dec_app_idle          : 1; /* [1..1] Ӧ���߼���obff_dec_filter�ڲ�״̬�����г�ʼ����״̬ѡ���źţ���obff_dec_app_initΪ1ʱ��Ч��0:��Ч��1:ѡ��IDLE״̬�� */
        unsigned int    obff_dec_app_obff          : 1; /* [2..2] Ӧ���߼���obff_dec_filter�ڲ�״̬�����г�ʼ����״̬ѡ���źţ���obff_dec_app_initΪ1ʱ��Ч��0:��Ч��1:ѡ��OBFF״̬�� */
        unsigned int    obff_dec_app_cpu_act       : 1; /* [3..3] Ӧ���߼���obff_dec_filter�ڲ�״̬�����г�ʼ����״̬ѡ���źţ���obff_dec_app_initΪ1ʱ��Ч��0:��Ч��1:ѡ��CPU_ACT״̬�� */
        unsigned int    obff_enc_app_owre_idle     : 1; /* [4..4] Ӧ���߼�����obff_enc��WAKE#�����Ϸ���IDLE obff��Ϣ����������Ч��ע1���������Ҫ����IDLE obff��Ϣʱ�����ڸ�λ�ϲ���һ�������ء� */
        unsigned int    obff_enc_app_owre_obff     : 1; /* [5..5] Ӧ���߼�����obff_enc��WAKE#�����Ϸ���OBFF obff��Ϣ����������Ч��ע1���������Ҫ����OBFF obff��Ϣʱ�����ڸ�λ�ϲ���һ�������ء� */
        unsigned int    obff_enc_app_owre_cpu_act  : 1; /* [6..6] Ӧ���߼�����obff_enc��WAKE#�����Ϸ���CPU_ACTIVE obff��Ϣ����������Ч��ע1���������Ҫ����CPU_ACTIVE obff��Ϣʱ�����ڸ�λ�ϲ���һ�������ء� */
        unsigned int    app_obff_idle_msg_req      : 1; /* [7..7] Ӧ���߼�������IDLE obff��ϢTLP������������Ч��ע1���������Ҫ����IDLE obff��Ϣʱ�����ڸ�λ�ϲ���һ�������ء� */
        unsigned int    app_obff_obff_msg_req      : 1; /* [8..8] Ӧ���߼�������OBFF obff��ϢTLP������������Ч��ע1���������Ҫ����OBFF obff��Ϣʱ�����ڸ�λ�ϲ���һ�������ء� */
        unsigned int    app_obff_cpu_active_msg_req : 1; /* [9..9] Ӧ���߼�������CPU_ACTIVE obff��ϢTLP������������Ч��ע1���������Ҫ����CPU_ACTIVE obff��Ϣʱ�����ڸ�λ�ϲ���һ�������ء� */
        unsigned int    app_ltr_msg_req            : 1; /* [10..10] Ӧ���߼�������LTR��ϢTLP������������Ч��ע1���������Ҫ����LTR��Ϣʱ�����ڸ�λ�ϲ���һ�������ء� */
        unsigned int    reserved                   : 21; /* [31..11] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL114_T;    /* PCIE0ϵͳ���ƼĴ���13�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    obff_cfg_wk_max_pls_wdt    : 8; /* [7..0] ����OBFF������/������ʹ�õ�active-inactive���������ȡ�ע1����λΪ19.2MHzʱ�ӵ�һ�����ڡ� */
        unsigned int    obff_cfg_wk_min_pls_wdt    : 8; /* [15..8] ����OBFF������/������ʹ�õ�active-inactive�������С��ȡ�ע1����λΪ19.2MHzʱ�ӵ�һ�����ڡ� */
        unsigned int    obff_cfg_wk_max_f2f_wdt    : 8; /* [23..16] ����OBFF������/������ʹ�õ������½��ص��½��صĿ�ȡ�ע1����λΪ19.2MHzʱ�ӵ�һ�����ڡ� */
        unsigned int    obff_cfg_wk_min_f2f_wdt    : 8; /* [31..24] ����OBFF������/������ʹ�õ���С���½��ص��½��صĿ�ȡ�ע1����λΪ19.2MHzʱ�ӵ�һ�����ڡ� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL115_T;    /* PCIE0ϵͳ���ƼĴ���14�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    obff_dec_idle_intr_mask    : 1; /* [0..0] obff_dec_idle�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    obff_dec_obff_intr_mask    : 1; /* [1..1] obff_dec_obff�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    obff_dec_cpu_active_intr_mask : 1; /* [2..2] obff_dec_cpu_active�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    obff_dec_err_intr_mask     : 1; /* [3..3] obff_dec_err�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    obff_msg_idle_intr_mask    : 1; /* [4..4] obff_msg_idle�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    obff_msg_obff_intr_mask    : 1; /* [5..5] obff_msg_obff�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    obff_msg_cpu_active_intr_mask : 1; /* [6..6] obff_msg_cpu_active�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    radm_msg_ltr_intr_mask     : 1; /* [7..7] radm_msg_ltr�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    cfg_msi_mask_chg_intr_mask : 1; /* [8..8] cfg_msi_mask_chg�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    radm_qoverflow_intr_mask   : 1; /* [9..9] radm_qoverflow�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    amba_order_mgr_wdt_int_intr_mask : 1; /* [10..10] amba_order_mgr_wdt_int�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    pcie_clkreq_in_n_intr_mask : 1; /* [11..11] pcie_clkreq_in_n�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    pcie_clkreq_in_n_inv_intr_mask : 1; /* [12..12] pcie_clkreq_in_n_inv�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    pcie_v721_intr_mask        : 1; /* [13..13] pcie_v721�ж�����λ������Ч��0:���Σ�1:�����Σ� */
        unsigned int    reserved_1                 : 2; /* [15..14] ������ */
        unsigned int    obff_dec_idle_intr_clear   : 1; /* [16..16] obff_dec_idle�ж����λ����������Ч��ע1:��λ��д1�󲻻�����0����Ҫ�����ʽд0�� */
        unsigned int    obff_dec_obff_intr_clear   : 1; /* [17..17] obff_dec_obff�ж����λ����������Ч��ע1:��λ��д1�󲻻�����0����Ҫ�����ʽд0�� */
        unsigned int    obff_dec_cpu_active_intr_clear : 1; /* [18..18] obff_dec_cpu_active�ж����λ����������Ч��ע1:��λ��д1�󲻻�����0����Ҫ�����ʽд0�� */
        unsigned int    obff_dec_err_intr_clear    : 1; /* [19..19] obff_dec_err�ж����λ����������Ч��ע1:��λ��д1�󲻻�����0����Ҫ�����ʽд0�� */
        unsigned int    obff_msg_idle_intr_clear   : 1; /* [20..20] obff_msg_idle�ж����λ����������Ч��ע1:��λ��д1�󲻻�����0����Ҫ�����ʽд0�� */
        unsigned int    obff_msg_obff_intr_clear   : 1; /* [21..21] obff_msg_obff�ж����λ����������Ч��ע1:��λ��д1�󲻻�����0����Ҫ�����ʽд0�� */
        unsigned int    obff_msg_cpu_active_intr_clear : 1; /* [22..22] obff_msg_cpu_active�ж����λ����������Ч��ע1:��λ��д1�󲻻�����0����Ҫ�����ʽд0�� */
        unsigned int    radm_msg_ltr_intr_clear    : 1; /* [23..23] radm_msg_ltr�ж����λ����������Ч��ע1:��λ��д1�󲻻�����0����Ҫ�����ʽд0�� */
        unsigned int    cfg_msi_mask_chg_intr_clear : 1; /* [24..24] cfg_msi_mask_chg�ж����λ����������Ч��ע1:��λ��д1�󲻻�����0����Ҫ�����ʽд0�� */
        unsigned int    radm_qoverflow_intr_clear  : 1; /* [25..25] radm_qoverflow�ж����λ����������Ч��ע1:��λ��д1�󲻻�����0����Ҫ�����ʽд0�� */
        unsigned int    reserved_0                 : 6; /* [31..26] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL116_T;    /* PCIE0ϵͳ���ƼĴ���15�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    cfg_msi_pending            : 32; /* [31..0] ������õ�MSI�����ṹVector Interrupt Pending�Ĵ�����ֵ�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL117_T;    /* PCIE0ϵͳ���ƼĴ���16�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    app_ltr_msg_latency        : 32; /* [31..0] Ӧ�������͵�LTR��Ϣ�� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL118_T;    /* PCIE0ϵͳ���ƼĴ���17�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    cfg_pwr_budget_data_reg    : 32; /* [31..0] ����Ԥ����ؼĴ����� */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL119_T;    /* PCIE0ϵͳ���ƼĴ���18�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    app_ltr_msg_func_num       : 3; /* [2..0] LTR��Ϣ���ܺš� */
        unsigned int    reserved_1                 : 1; /* [3..3] ������ */
        unsigned int    cfg_pwr_budget_func_num    : 3; /* [6..4] ����Ԥ����ؼĴ����ֶΡ� */
        unsigned int    slv_awmisc_info_atu_bypass : 1; /* [7..7] AXI slaveд�����ڲ�ATU��·��0������·��1����·�� */
        unsigned int    slv_armisc_info_atu_bypass : 1; /* [8..8] AXI slave�������ڲ�ATU��·��0������·��1����·�� */
        unsigned int    app_clk_pm_en              : 1; /* [9..9] Clock PMʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    reserved_0                 : 22; /* [31..10] ������ */
    } bits;
    unsigned int    u32;
}HI_SC_CTRL120_T;    /* PCIE0ϵͳ���ƼĴ���19�Ĵ��� */


/********************************************************************************/
/*    sysreg_pd ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_sc_ctrl58_pcie_slv_awmisc_info,pcie_slv_awmisc_info,HI_SC_CTRL58_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL58_OFFSET)
HI_SET_GET(hi_sc_ctrl58_pcie_slv_resp_err_map,pcie_slv_resp_err_map,HI_SC_CTRL58_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL58_OFFSET)
HI_SET_GET(hi_sc_ctrl58_pcie_device_type,pcie_device_type,HI_SC_CTRL58_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL58_OFFSET)
HI_SET_GET(hi_sc_ctrl59_pcie_slv_armisc_info,pcie_slv_armisc_info,HI_SC_CTRL59_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL59_OFFSET)
HI_SET_GET(hi_sc_ctrl59_reserved,reserved,HI_SC_CTRL59_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL59_OFFSET)
HI_SET_GET(hi_sc_ctrl59_pcie_app_clk_req_n,pcie_app_clk_req_n,HI_SC_CTRL59_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL59_OFFSET)
HI_SET_GET(hi_sc_ctrl59_pcie_ven_msg_code,pcie_ven_msg_code,HI_SC_CTRL59_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL59_OFFSET)
HI_SET_GET(hi_sc_ctrl60_pcie_mstr_bmisc_info,pcie_mstr_bmisc_info,HI_SC_CTRL60_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL60_OFFSET)
HI_SET_GET(hi_sc_ctrl60_pcie_mstr_rmisc_info,pcie_mstr_rmisc_info,HI_SC_CTRL60_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL60_OFFSET)
HI_SET_GET(hi_sc_ctrl60_pcie_ven_msi_req,pcie_ven_msi_req,HI_SC_CTRL60_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL60_OFFSET)
HI_SET_GET(hi_sc_ctrl60_pcie_ven_msi_vector,pcie_ven_msi_vector,HI_SC_CTRL60_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL60_OFFSET)
HI_SET_GET(hi_sc_ctrl61_pcie_ven_msg_req,pcie_ven_msg_req,HI_SC_CTRL61_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL61_OFFSET)
HI_SET_GET(hi_sc_ctrl61_pcie_ven_msg_fmt,pcie_ven_msg_fmt,HI_SC_CTRL61_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL61_OFFSET)
HI_SET_GET(hi_sc_ctrl61_pcie_ven_msg_type,pcie_ven_msg_type,HI_SC_CTRL61_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL61_OFFSET)
HI_SET_GET(hi_sc_ctrl61_pcie_ven_msg_td,pcie_ven_msg_td,HI_SC_CTRL61_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL61_OFFSET)
HI_SET_GET(hi_sc_ctrl61_pcie_ven_msg_ep,pcie_ven_msg_ep,HI_SC_CTRL61_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL61_OFFSET)
HI_SET_GET(hi_sc_ctrl61_pcie_ven_msg_attr,pcie_ven_msg_attr,HI_SC_CTRL61_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL61_OFFSET)
HI_SET_GET(hi_sc_ctrl61_pcie_ven_msg_len,pcie_ven_msg_len,HI_SC_CTRL61_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL61_OFFSET)
HI_SET_GET(hi_sc_ctrl61_pcie_ven_msg_tag,pcie_ven_msg_tag,HI_SC_CTRL61_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL61_OFFSET)
HI_SET_GET(hi_sc_ctrl61_reserved,reserved,HI_SC_CTRL61_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL61_OFFSET)
HI_SET_GET(hi_sc_ctrl62_pice_ven_msg_data_low,pice_ven_msg_data_low,HI_SC_CTRL62_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL62_OFFSET)
HI_SET_GET(hi_sc_ctrl63_pice_ven_msg_data_high,pice_ven_msg_data_high,HI_SC_CTRL63_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL63_OFFSET)
HI_SET_GET(hi_sc_ctrl64_slot_led_blink_period,slot_led_blink_period,HI_SC_CTRL64_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL64_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_app_init_rst,pcie_app_init_rst,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_app_req_entr_l1,pcie_app_req_entr_l1,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_app_ready_entr_l23,pcie_app_ready_entr_l23,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_app_req_exit_l1,pcie_app_req_exit_l1,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_app_req_retry_en,pcie_app_req_retry_en,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_sys_int,pcie_sys_int,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_outband_pwrup_cmd,pcie_outband_pwrup_cmd,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_app_unlock_msg,pcie_app_unlock_msg,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_apps_pm_xmt_turnoff,pcie_apps_pm_xmt_turnoff,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_apps_pm_xmt_pme,pcie_apps_pm_xmt_pme,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_sys_aux_pwr_det,pcie_sys_aux_pwr_det,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_app_ltssm_enable,pcie_app_ltssm_enable,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_cfg_pwr_ctrler_ctrl_pol,pcie_cfg_pwr_ctrler_ctrl_pol,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_reserved_2,reserved_2,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_sys_mrl_sensor_state,pcie_sys_mrl_sensor_state,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_sys_pwr_fault_det,pcie_sys_pwr_fault_det,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_sys_mrl_sensor_chged,pcie_sys_mrl_sensor_chged,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_reserved_1,reserved_1,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_sys_cmd_cpled_int,pcie_sys_cmd_cpled_int,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_sys_eml_interlock_engaged,pcie_sys_eml_interlock_engaged,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_reserved_0,reserved_0,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_int_ctrl,pcie_int_ctrl,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_linkdown_auto_rstn_disable,pcie_linkdown_auto_rstn_disable,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_pcie_err_bresp_enable,pcie_err_bresp_enable,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl65_cipe_err_rresp_enable,cipe_err_rresp_enable,HI_SC_CTRL65_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL65_OFFSET)
HI_SET_GET(hi_sc_ctrl66_reserved_1,reserved_1,HI_SC_CTRL66_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL66_OFFSET)
HI_SET_GET(hi_sc_ctrl66_cfg_l1_aux_clk_switch_core_clk_gate_en,cfg_l1_aux_clk_switch_core_clk_gate_en,HI_SC_CTRL66_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL66_OFFSET)
HI_SET_GET(hi_sc_ctrl66_cfg_l1_mac_powerdown_override_to_p2_en,cfg_l1_mac_powerdown_override_to_p2_en,HI_SC_CTRL66_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL66_OFFSET)
HI_SET_GET(hi_sc_ctrl66_pcie_state2_sel,pcie_state2_sel,HI_SC_CTRL66_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL66_OFFSET)
HI_SET_GET(hi_sc_ctrl66_pcie_state3_sel,pcie_state3_sel,HI_SC_CTRL66_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL66_OFFSET)
HI_SET_GET(hi_sc_ctrl66_reserved_0,reserved_0,HI_SC_CTRL66_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL66_OFFSET)
HI_SET_GET(hi_sc_ctrl67_reserved,reserved,HI_SC_CTRL67_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL67_OFFSET)
HI_SET_GET(hi_sc_ctrl73_reserved,reserved,HI_SC_CTRL73_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL73_OFFSET)
HI_SET_GET(hi_sc_ctrl74_reserved,reserved,HI_SC_CTRL74_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL74_OFFSET)
HI_SET_GET(hi_sc_ctrl75_reserved,reserved,HI_SC_CTRL75_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL75_OFFSET)
HI_SET_GET(hi_sc_ctrl76_reserved,reserved,HI_SC_CTRL76_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL76_OFFSET)
HI_SET_GET(hi_sc_ctrl77_reserved,reserved,HI_SC_CTRL77_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL77_OFFSET)
HI_SET_GET(hi_sc_ctrl78_reserved,reserved,HI_SC_CTRL78_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL78_OFFSET)
HI_SET_GET(hi_sc_ctrl79_reserved,reserved,HI_SC_CTRL79_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL79_OFFSET)
HI_SET_GET(hi_sc_ctrl80_reserved,reserved,HI_SC_CTRL80_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL80_OFFSET)
HI_SET_GET(hi_sc_ctrl82_appa9_gpio1_en,appa9_gpio1_en,HI_SC_CTRL82_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL82_OFFSET)
HI_SET_GET(hi_sc_ctrl83_appa9_gpio2_en,appa9_gpio2_en,HI_SC_CTRL83_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL83_OFFSET)
HI_SET_GET(hi_sc_ctrl84_appa9_gpio3_en,appa9_gpio3_en,HI_SC_CTRL84_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL84_OFFSET)
HI_SET_GET(hi_sc_ctrl86_mdma9_gpio1_en,mdma9_gpio1_en,HI_SC_CTRL86_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL86_OFFSET)
HI_SET_GET(hi_sc_ctrl87_mdma9_gpio2_en,mdma9_gpio2_en,HI_SC_CTRL87_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL87_OFFSET)
HI_SET_GET(hi_sc_ctrl88_mdma9_gpio3_en,mdma9_gpio3_en,HI_SC_CTRL88_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL88_OFFSET)
HI_SET_GET(hi_sc_ctrl89_hifi_gpio0_en,hifi_gpio0_en,HI_SC_CTRL89_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL89_OFFSET)
HI_SET_GET(hi_sc_ctrl90_hifi_gpio1_en,hifi_gpio1_en,HI_SC_CTRL90_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL90_OFFSET)
HI_SET_GET(hi_sc_ctrl91_hifi_gpio2_en,hifi_gpio2_en,HI_SC_CTRL91_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL91_OFFSET)
HI_SET_GET(hi_sc_ctrl92_hifi_gpio3_en,hifi_gpio3_en,HI_SC_CTRL92_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL92_OFFSET)
HI_SET_GET(hi_sc_ctrl93_dsp0_gpio0_en,dsp0_gpio0_en,HI_SC_CTRL93_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL93_OFFSET)
HI_SET_GET(hi_sc_ctrl94_dsp0_gpio1_en,dsp0_gpio1_en,HI_SC_CTRL94_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL94_OFFSET)
HI_SET_GET(hi_sc_ctrl95_dsp0_gpio2_en,dsp0_gpio2_en,HI_SC_CTRL95_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL95_OFFSET)
HI_SET_GET(hi_sc_ctrl96_dsp0_gpio3_en,dsp0_gpio3_en,HI_SC_CTRL96_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL96_OFFSET)
HI_SET_GET(hi_sc_ctrl97_reserved,reserved,HI_SC_CTRL97_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL97_OFFSET)
HI_SET_GET(hi_sc_ctrl99_cm3_gpio1_en,cm3_gpio1_en,HI_SC_CTRL99_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL99_OFFSET)
HI_SET_GET(hi_sc_ctrl100_cm3_gpio2_en,cm3_gpio2_en,HI_SC_CTRL100_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL100_OFFSET)
HI_SET_GET(hi_sc_ctrl101_cm3_gpio3_en,cm3_gpio3_en,HI_SC_CTRL101_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL101_OFFSET)
HI_SET_GET(hi_sc_ctrl102_reserved,reserved,HI_SC_CTRL102_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL102_OFFSET)
HI_SET_GET(hi_sc_ctrl106_cfg_aer_rc_err_msi_mask,cfg_aer_rc_err_msi_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_cfg_sys_err_rc_mask,cfg_sys_err_rc_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_radm_correctable_err_mask,radm_correctable_err_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_radm_nonfatal_err_mask,radm_nonfatal_err_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_radm_fatal_err_mask,radm_fatal_err_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_radm_pm_pme_mask,radm_pm_pme_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_radm_pm_to_ack_mask,radm_pm_to_ack_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_ven_msg_int_mask,ven_msg_int_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_radm_cpl_timeout_mask,radm_cpl_timeout_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_radm_msg_unlock_mask,radm_msg_unlock_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_cfg_pme_msi_mask,cfg_pme_msi_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_bridge_flush_not_mask,bridge_flush_not_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_link_req_rst_not_mask,link_req_rst_not_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_pcie_p2_exit_reg_mask,pcie_p2_exit_reg_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_reserved_1,reserved_1,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_pcie_radm_pm_turnoff_mask,pcie_radm_pm_turnoff_mask,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl106_reserved_0,reserved_0,HI_SC_CTRL106_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL106_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_cfg_aer_rc_msi_clr,pcie_cfg_aer_rc_msi_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_cfg_sys_err_rc_clr,pcie_cfg_sys_err_rc_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_radm_corretable_err_clr,pcie_radm_corretable_err_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_radm_nonfatal_err_clr,pcie_radm_nonfatal_err_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_radm_fatal_err_clr,pcie_radm_fatal_err_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_radm_pm_pme_clr,pcie_radm_pm_pme_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_radm_pm_to_ack_clr,pcie_radm_pm_to_ack_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_ven_msg_int_clr,pcie_ven_msg_int_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_radm_cpl_timeout_clr,pcie_radm_cpl_timeout_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_radm_msg_unlock_clr,pcie_radm_msg_unlock_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_cfg_pme_msi_clr,pcie_cfg_pme_msi_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_bridge_flush_not_clr,pcie_bridge_flush_not_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_link_req_rst_not_clr,pcie_link_req_rst_not_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_p2_exit_int_clr,pcie_p2_exit_int_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_slv_err_int_clr,pcie_slv_err_int_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_ven_msi_func_num,pcie_ven_msi_func_num,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_ven_msg_func_num,pcie_ven_msg_func_num,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_pcie_radm_pm_turnoff_clr,pcie_radm_pm_turnoff_clr,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl107_reserved,reserved,HI_SC_CTRL107_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL107_OFFSET)
HI_SET_GET(hi_sc_ctrl108_pcie0_intx_req,pcie0_intx_req,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_pcie0_msi_req,pcie0_msi_req,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_reserved_5,reserved_5,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_pcie0_pad_phy_mask,pcie0_pad_phy_mask,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_pcie0_pad_out_mask,pcie0_pad_out_mask,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_reserved_4,reserved_4,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_pcie0_inner_phy_mask,pcie0_inner_phy_mask,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_pcie0_inner_out_mask,pcie0_inner_out_mask,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_reserved_3,reserved_3,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_pcie0_out_gatedclock_en,pcie0_out_gatedclock_en,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_pcie0_phy_gatedclock_en,pcie0_phy_gatedclock_en,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_reserved_2,reserved_2,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_pcie0_refclk_oen_sel,pcie0_refclk_oen_sel,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_pcie0_refclk_oen_cfg,pcie0_refclk_oen_cfg,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_gmac_refclk_sel,gmac_refclk_sel,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_reserved_1,reserved_1,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl108_reserved_0,reserved_0,HI_SC_CTRL108_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL108_OFFSET)
HI_SET_GET(hi_sc_ctrl109_pipe_tx2rx_loopbk,pipe_tx2rx_loopbk,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_pipe_pclkreq_n,pipe_pclkreq_n,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_pipe_pclkreq_n_sel,pipe_pclkreq_n_sel,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_pcs_clk_req,pcs_clk_req,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_pcs_common_clocks,pcs_common_clocks,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_pipe_port_sel,pipe_port_sel,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_reserved_2,reserved_2,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_pipe_rx_elecidle_disable,pipe_rx_elecidle_disable,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_pipe_tx_common_mode_disable,pipe_tx_common_mode_disable,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_pipe_clkreq_n_cfg,pipe_clkreq_n_cfg,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_pipe_clkreq_n_sel,pipe_clkreq_n_sel,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_reserved_1,reserved_1,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_phy_res_ack_in_cfg,phy_res_ack_in_cfg,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_phy_res_ack_in_sel,phy_res_ack_in_sel,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_phy_res_req_in,phy_res_req_in,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_phy_rtune_req,phy_rtune_req,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_phy_test_burnin,phy_test_burnin,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_phy_test_bypass,phy_test_bypass,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_phy_test_powerdown,phy_test_powerdown,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl109_reserved_0,reserved_0,HI_SC_CTRL109_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL109_OFFSET)
HI_SET_GET(hi_sc_ctrl110_phy_mpll_multiplier,phy_mpll_multiplier,HI_SC_CTRL110_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL110_OFFSET)
HI_SET_GET(hi_sc_ctrl110_phy_ref_clkdiv2,phy_ref_clkdiv2,HI_SC_CTRL110_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL110_OFFSET)
HI_SET_GET(hi_sc_ctrl110_phy_ref_use_pad,phy_ref_use_pad,HI_SC_CTRL110_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL110_OFFSET)
HI_SET_GET(hi_sc_ctrl110_ref_alt_clk_gt_en,ref_alt_clk_gt_en,HI_SC_CTRL110_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL110_OFFSET)
HI_SET_GET(hi_sc_ctrl110_reserved_1,reserved_1,HI_SC_CTRL110_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL110_OFFSET)
HI_SET_GET(hi_sc_ctrl110_phy_reset,phy_reset,HI_SC_CTRL110_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL110_OFFSET)
HI_SET_GET(hi_sc_ctrl110_phy_reset_sel,phy_reset_sel,HI_SC_CTRL110_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL110_OFFSET)
HI_SET_GET(hi_sc_ctrl110_pipe_reset_n_cfg,pipe_reset_n_cfg,HI_SC_CTRL110_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL110_OFFSET)
HI_SET_GET(hi_sc_ctrl110_pipe_reset_sel,pipe_reset_sel,HI_SC_CTRL110_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL110_OFFSET)
HI_SET_GET(hi_sc_ctrl110_reserved_0,reserved_0,HI_SC_CTRL110_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL110_OFFSET)
HI_SET_GET(hi_sc_ctrl111_phy_los_bias,phy_los_bias,HI_SC_CTRL111_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL111_OFFSET)
HI_SET_GET(hi_sc_ctrl111_phy_los_level,phy_los_level,HI_SC_CTRL111_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL111_OFFSET)
HI_SET_GET(hi_sc_ctrl111_phy_rx_eq,phy_rx_eq,HI_SC_CTRL111_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL111_OFFSET)
HI_SET_GET(hi_sc_ctrl111_pcs_tx_deemph_gen2_3p5db,pcs_tx_deemph_gen2_3p5db,HI_SC_CTRL111_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL111_OFFSET)
HI_SET_GET(hi_sc_ctrl111_pcs_tx_deemph_gen2_6db,pcs_tx_deemph_gen2_6db,HI_SC_CTRL111_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL111_OFFSET)
HI_SET_GET(hi_sc_ctrl111_reserved_1,reserved_1,HI_SC_CTRL111_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL111_OFFSET)
HI_SET_GET(hi_sc_ctrl111_pcs_tx_deemph_gen1,pcs_tx_deemph_gen1,HI_SC_CTRL111_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL111_OFFSET)
HI_SET_GET(hi_sc_ctrl111_reserved_0,reserved_0,HI_SC_CTRL111_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL111_OFFSET)
HI_SET_GET(hi_sc_ctrl112_pcs_tx_swing_full,pcs_tx_swing_full,HI_SC_CTRL112_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL112_OFFSET)
HI_SET_GET(hi_sc_ctrl112_pcs_tx_swing_low,pcs_tx_swing_low,HI_SC_CTRL112_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL112_OFFSET)
HI_SET_GET(hi_sc_ctrl112_phy_tx_term_offset,phy_tx_term_offset,HI_SC_CTRL112_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL112_OFFSET)
HI_SET_GET(hi_sc_ctrl112_reserved_2,reserved_2,HI_SC_CTRL112_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL112_OFFSET)
HI_SET_GET(hi_sc_ctrl112_phy_tx_vboost_lvl,phy_tx_vboost_lvl,HI_SC_CTRL112_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL112_OFFSET)
HI_SET_GET(hi_sc_ctrl112_reserved_1,reserved_1,HI_SC_CTRL112_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL112_OFFSET)
HI_SET_GET(hi_sc_ctrl112_vreg_bypass,vreg_bypass,HI_SC_CTRL112_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL112_OFFSET)
HI_SET_GET(hi_sc_ctrl112_reserved_0,reserved_0,HI_SC_CTRL112_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL112_OFFSET)
HI_SET_GET(hi_sc_ctrl113_pcie_perst_out_n,pcie_perst_out_n,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_pcie_perst_oe,pcie_perst_oe,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_pcie_perst_in_n_ctrl,pcie_perst_in_n_ctrl,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_mac_phy_pclkreq_n_0_ctrl,mac_phy_pclkreq_n_0_ctrl,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_mac_phy_pclkreq_n_1_ctrl,mac_phy_pclkreq_n_1_ctrl,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_cfg_l1sub_en_ctrl,cfg_l1sub_en_ctrl,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_clkreq_n_ctrl0,clkreq_n_ctrl0,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_clkreq_n_ctrl1,clkreq_n_ctrl1,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_rc_wake_n_ctrl,rc_wake_n_ctrl,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_ep_wake_n_ctrl,ep_wake_n_ctrl,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_obff_enc_owre_wake_ctrl,obff_enc_owre_wake_ctrl,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_dwc_pcie_dm_wake_n_ctrl,dwc_pcie_dm_wake_n_ctrl,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl113_reserved,reserved,HI_SC_CTRL113_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL113_OFFSET)
HI_SET_GET(hi_sc_ctrl114_obff_dec_app_init,obff_dec_app_init,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl114_obff_dec_app_idle,obff_dec_app_idle,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl114_obff_dec_app_obff,obff_dec_app_obff,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl114_obff_dec_app_cpu_act,obff_dec_app_cpu_act,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl114_obff_enc_app_owre_idle,obff_enc_app_owre_idle,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl114_obff_enc_app_owre_obff,obff_enc_app_owre_obff,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl114_obff_enc_app_owre_cpu_act,obff_enc_app_owre_cpu_act,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl114_app_obff_idle_msg_req,app_obff_idle_msg_req,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl114_app_obff_obff_msg_req,app_obff_obff_msg_req,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl114_app_obff_cpu_active_msg_req,app_obff_cpu_active_msg_req,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl114_app_ltr_msg_req,app_ltr_msg_req,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl114_reserved,reserved,HI_SC_CTRL114_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL114_OFFSET)
HI_SET_GET(hi_sc_ctrl115_obff_cfg_wk_max_pls_wdt,obff_cfg_wk_max_pls_wdt,HI_SC_CTRL115_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL115_OFFSET)
HI_SET_GET(hi_sc_ctrl115_obff_cfg_wk_min_pls_wdt,obff_cfg_wk_min_pls_wdt,HI_SC_CTRL115_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL115_OFFSET)
HI_SET_GET(hi_sc_ctrl115_obff_cfg_wk_max_f2f_wdt,obff_cfg_wk_max_f2f_wdt,HI_SC_CTRL115_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL115_OFFSET)
HI_SET_GET(hi_sc_ctrl115_obff_cfg_wk_min_f2f_wdt,obff_cfg_wk_min_f2f_wdt,HI_SC_CTRL115_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL115_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_dec_idle_intr_mask,obff_dec_idle_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_dec_obff_intr_mask,obff_dec_obff_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_dec_cpu_active_intr_mask,obff_dec_cpu_active_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_dec_err_intr_mask,obff_dec_err_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_msg_idle_intr_mask,obff_msg_idle_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_msg_obff_intr_mask,obff_msg_obff_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_msg_cpu_active_intr_mask,obff_msg_cpu_active_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_radm_msg_ltr_intr_mask,radm_msg_ltr_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_cfg_msi_mask_chg_intr_mask,cfg_msi_mask_chg_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_radm_qoverflow_intr_mask,radm_qoverflow_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_amba_order_mgr_wdt_int_intr_mask,amba_order_mgr_wdt_int_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_pcie_clkreq_in_n_intr_mask,pcie_clkreq_in_n_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_pcie_clkreq_in_n_inv_intr_mask,pcie_clkreq_in_n_inv_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_pcie_v721_intr_mask,pcie_v721_intr_mask,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_reserved_1,reserved_1,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_dec_idle_intr_clear,obff_dec_idle_intr_clear,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_dec_obff_intr_clear,obff_dec_obff_intr_clear,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_dec_cpu_active_intr_clear,obff_dec_cpu_active_intr_clear,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_dec_err_intr_clear,obff_dec_err_intr_clear,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_msg_idle_intr_clear,obff_msg_idle_intr_clear,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_msg_obff_intr_clear,obff_msg_obff_intr_clear,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_obff_msg_cpu_active_intr_clear,obff_msg_cpu_active_intr_clear,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_radm_msg_ltr_intr_clear,radm_msg_ltr_intr_clear,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_cfg_msi_mask_chg_intr_clear,cfg_msi_mask_chg_intr_clear,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_radm_qoverflow_intr_clear,radm_qoverflow_intr_clear,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl116_reserved_0,reserved_0,HI_SC_CTRL116_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL116_OFFSET)
HI_SET_GET(hi_sc_ctrl117_cfg_msi_pending,cfg_msi_pending,HI_SC_CTRL117_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL117_OFFSET)
HI_SET_GET(hi_sc_ctrl118_app_ltr_msg_latency,app_ltr_msg_latency,HI_SC_CTRL118_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL118_OFFSET)
HI_SET_GET(hi_sc_ctrl119_cfg_pwr_budget_data_reg,cfg_pwr_budget_data_reg,HI_SC_CTRL119_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL119_OFFSET)
HI_SET_GET(hi_sc_ctrl120_app_ltr_msg_func_num,app_ltr_msg_func_num,HI_SC_CTRL120_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL120_OFFSET)
HI_SET_GET(hi_sc_ctrl120_reserved_1,reserved_1,HI_SC_CTRL120_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL120_OFFSET)
HI_SET_GET(hi_sc_ctrl120_cfg_pwr_budget_func_num,cfg_pwr_budget_func_num,HI_SC_CTRL120_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL120_OFFSET)
HI_SET_GET(hi_sc_ctrl120_slv_awmisc_info_atu_bypass,slv_awmisc_info_atu_bypass,HI_SC_CTRL120_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL120_OFFSET)
HI_SET_GET(hi_sc_ctrl120_slv_armisc_info_atu_bypass,slv_armisc_info_atu_bypass,HI_SC_CTRL120_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL120_OFFSET)
HI_SET_GET(hi_sc_ctrl120_app_clk_pm_en,app_clk_pm_en,HI_SC_CTRL120_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL120_OFFSET)
HI_SET_GET(hi_sc_ctrl120_reserved_0,reserved_0,HI_SC_CTRL120_T,HI_SYSREG_PD_BASE_ADDR, HI_SC_CTRL120_OFFSET)

#endif

#endif // __HI_SYSREG_PD_H__

