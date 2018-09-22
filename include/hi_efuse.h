/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_efuse.h */
/* Version       : 2.0 */
/* Created       : 2013-02-27*/
/* Last Modified : */
/* Description   :  The C union definition file for the module efuse*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/


#ifndef __HI_EFUSE_H__
#define __HI_EFUSE_H__

/*
 * Project: hi
 * Module : efuse
 */
#include <hi_base.h>

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/* efuse_nandc support 2 group nandc info */
#define CONFIG_EFUSE_NANDC_GROUP2


#define EFUSE_MAX_SIZE          (16)

/* ��ȫУ��ʹ�ܱ�־ */
#define EFUSE_GRP_SECURITY      15
#define EFUSEC_SEC_EN_POS       4
#define EFUSEC_SEC_EN_WIDTH     1
#define EFUSEC_SEC_EN_MASK      (((1<<EFUSEC_SEC_EN_WIDTH)-1)<<EFUSEC_SEC_EN_POS)
#define EFUSEC_SEC_EN           (1<<EFUSEC_SEC_EN_POS)
#define EFUSE_GRP_DIEID         (8)
#define EFUSE_DIEID_SIZE        (5)
#define EFUSE_DIEID_BIT         (27)
#define EFUSE_DIEID_LEN         (EFUSE_DIEID_SIZE * EFUSE_GROUP_SIZE)

#define EFUSE_GRP_HUK           (4)
#define EFUSE_HUK_SIZE          (4)
#define EFUSE_HUK_LEN           (EFUSE_HUK_SIZE * EFUSE_GROUP_SIZE)
#define EFUSE_GRP_SECBOOT_ID        (13)/* bit416-424 ����ֵ  */

#define EFUSE_COUNT_CFG     (5)
#define PGM_COUNT_CFG       (HI_APB_CLK / 1000000 * 12 - EFUSE_COUNT_CFG)

#define EFUSE_GROUP_ID_FOR_NANDC    (15)
/********************************************************************************/
/*    efuse �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_EFUSEC_CFG_OFFSET                              (0x0) /* ���üĴ���������ʹ�ܶ�/��д���̣��������ʱ���߼��Զ���RDn���Ϊ0������д���ʱ���߼��Զ���PGEn���Ϊ0��. */
#define    HI_EFUSEC_STATUS_OFFSET                           (0x4) /* ״̬�Ĵ��������ڱ�����/��д״̬ */
#define    HI_EFUSE_GROUP_OFFSET                             (0x8) /* ��ȡ/��д��ַ�Ĵ�������eufse���飬ÿ��Ϊ32bit����efuse������д���߶�ȡ��ʱ����һ��groupΪ��λ */
#define    HI_PG_VALUE_OFFSET                                (0xC) /* ÿ�ε���дֵ�Ĵ��� */
#define    HI_EFUSEC_COUNT_OFFSET                            (0x10) /* efuse�ڲ�״̬��ת������ֵ�Ĵ�����ͬʱ��ֵ����4��Ϊefuse�������ڼ�strobe�ź������ȼ���ֵ */
#define    HI_PGM_COUNT_OFFSET                               (0x14) /* һ����д�ڼ�strobe�ź�����ʱ������� */
#define    HI_EFUSEC_DATA_OFFSET                             (0x18) /* ��������efuse��ȡ�����ݼĴ��� */
#define    HI_HW_CFG_OFFSET                                  (0x1C) /* ���efuse�ϵ�⸴λ���group==127��ȡ�����ݼĴ��������������жϵȡ���ʼֵ���û�ͨ��efuse��дȷ�� */

/********************************************************************************/
/*    efuse �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    pgen                       : 1; /* [0..0] ��дʹ���źţ���һ����д��ɺ��߼�����Ϊ�Զ����㡣0����ʹ��1��ʹ�� */
        unsigned int    pre_pg                     : 1; /* [1..1] Ԥ��дʹ���źţ�ʹ�ܺ�Ӳ������PGENB�źš�0����ʹ��1��ʹ�� */
        unsigned int    rden                       : 1; /* [2..2] ��ʹ���źţ���һ�ζ���ɺ��߼�����Ϊ�Զ����㡣0����ʹ��1��ʹ�� */
        unsigned int    aib_sel                    : 1; /* [3..3] AIB�ӿ�ѡ���źš�0��ѡ��AIB����efuse������1��ѡ��APB����efuse������ */
        unsigned int    rr_en                      : 1; /* [4..4] efsue������Ʊ�־��0������ģʽ1������ģʽ */
        unsigned int    pd_en                      : 1; /* [5..5] efuse power-down���ơ�0����ʹ��1��ʹ�� */
        unsigned int    mr_en                      : 1; /* [6..6] efuse Margin��ģʽ���ơ�0����ʹ��1��ʹ�� */
        unsigned int    undefined                  : 25; /* [31..7]  */
    } bits;
    unsigned int    u32;
}HI_EFUSEC_CFG_T;    /* ���üĴ���������ʹ�ܶ�/��д���̣��������ʱ���߼��Զ���RDn���Ϊ0������д���ʱ���߼��Զ���PGEn���Ϊ0��. */

typedef union
{
    struct
    {
        unsigned int    pg_status                  : 1; /* [0..0] ��д״̬��0��δ���1����� */
        unsigned int    rd_status                  : 1; /* [1..1] efuse��״̬0��δ���1�����һ�ζ����� */
        unsigned int    pgenb_status               : 1; /* [2..2] Ԥ��д��λ���״̬��0��δ���1�����Ԥ��д��λ״̬ */
        unsigned int    rd_error                   : 1; /* [3..3] efuse��ǰgroup��ַ�Ƿ��ǽ�ֹ�ġ�0����1���� */
        unsigned int    pd_status                  : 1; /* [4..4] power-down״̬��0������״̬1��power-down״̬ */
        unsigned int    undefined                  : 27; /* [31..5]  */
    } bits;
    unsigned int    u32;
}HI_EFUSEC_STATUS_T;    /* ״̬�Ĵ��������ڱ�����/��д״̬ */

typedef union
{
    struct
    {
        unsigned int    efuse_group                : 7; /* [6..0] ��ȡ/��д��ַgroup, */
        unsigned int    undefined                  : 25; /* [31..7]  */
    } bits;
    unsigned int    u32;
}HI_EFUSE_GROUP_T;    /* ��ȡ/��д��ַ�Ĵ�������eufse���飬ÿ��Ϊ32bit����efuse������д���߶�ȡ��ʱ����һ��groupΪ��λ */

typedef union
{
    struct
    {
        unsigned int    pg_value                   : 32; /* [31..0] һ��32bit����д��Ϣ0������д��bit��1����д��bit�� */
    } bits;
    unsigned int    u32;
}HI_PG_VALUE_T;    /* ÿ�ε���дֵ�Ĵ��� */

typedef union
{
    struct
    {
        unsigned int    efusec_count               : 8; /* [7..0] EFUSE�ڲ�״̬��תʹ�õļ���ֵ�� */
        unsigned int    undefined                  : 24; /* [31..8]  */
    } bits;
    unsigned int    u32;
}HI_EFUSEC_COUNT_T;    /* efuse�ڲ�״̬��ת������ֵ�Ĵ�����ͬʱ��ֵ����4��Ϊefuse�������ڼ�strobe�ź������ȼ���ֵ */

typedef union
{
    struct
    {
        unsigned int    pgm_count                  : 16; /* [15..0] һ����д�ڼ�strobe�ź�����ʱ����������Բο�ʱ��Ϊ����ʱ�ӣ� */
        unsigned int    undefined                  : 16; /* [31..16]  */
    } bits;
    unsigned int    u32;
}HI_PGM_COUNT_T;    /* һ����д�ڼ�strobe�ź�����ʱ������� */

typedef union
{
    struct
    {
        unsigned int    efusec_data                : 32; /* [31..0] ��������efuse��ȡ������ */
    } bits;
    unsigned int    u32;
}HI_EFUSEC_DATA_T;    /* ��������efuse��ȡ�����ݼĴ��� */

typedef union
{
    struct
    {
        unsigned int    pgm_disable                : 1; /* [0..0] 0��64ҳ1��128ҳ */
        unsigned int    pad_disable                : 1; /* [1..1] 0��64ҳ1��128ҳ */
        unsigned int    jtag_en                    : 1; /* [2..2] 0��64ҳ1��128ҳ */
        unsigned int    boot_sel                   : 1; /* [3..3] 0��64ҳ1��128ҳ */
        unsigned int    secboot_en                 : 1; /* [4..4] 0��64ҳ1��128ҳ */
        unsigned int    nf_ctrl_ena0               : 1; /* [5..5] ���Ƶ�һ��nand��Ϣ�ӹܽŻ���efuse�ж�ȡ0��nandc�ӹܽŶ�ȡnand flash���ò���1��nandc��efuse�ж�ȡnand falsh���ò��� */
        unsigned int    nf_block_size1             : 1; /* [6..6] 0��64ҳ1��128ҳ */
        unsigned int    nf_ecc_type1               : 2; /* [8..7] 00����ECC01��1bitECC/4bitECC11��8bitECC10��24bitECC */
        unsigned int    nf_page_size1              : 2; /* [10..9] 00��page size 512�ֽ�01��page size 2K�ֽ�11��page size 4K�ֽ�10��page size 8K�ֽ� */
        unsigned int    nf_addr_num1               : 1; /* [11..11] 0��4���ڵ�ַ1��5���ڵ�ַ */
        unsigned int    nf_ctrl_ena1               : 1; /* [12..12] ���Ƶڶ���nand��Ϣ�ӹܽŻ���efuse�ж�ȡ0��nandc�ӹܽŶ�ȡnand flash���ò���1��nandc��efuse�ж�ȡnand falsh���ò��� */
        unsigned int    reserved_2                 : 3; /* [15..13]  */
        unsigned int    nf_block_size              : 1; /* [16..16] 0��64ҳ1��128ҳ */
        unsigned int    nf_ecc_type                : 2; /* [18..17] 00����ECC01��1bitECC/4bitECC11��8bitECC10��24bitECC */
        unsigned int    reserved_1                 : 1; /* [19..19]  */
        unsigned int    nf_page_size               : 2; /* [21..20] 00��page size 512�ֽ�01��page size 2K�ֽ�11��page size 4K�ֽ�10��page size 8K�ֽ� */
        unsigned int    nf_addr_num                : 1; /* [22..22] 0��4���ڵ�ַ1��5���ڵ�ַ */
        unsigned int    reserved_0                 : 2; /* [24..23] 0��nandc�ӹܽŶ�ȡnand flash���ò���1��nandc��efuse�ж�ȡnand falsh���ò��� */
        unsigned int    nf_ctrl_ena                : 1; /* [25..25] V721�в�ʹ��0��nandc�ӹܽŶ�ȡnand flash���ò���1��nandc��efuse�ж�ȡnand falsh���ò��� */
        unsigned int    undefined                  : 6; /* [31..26]  */
    } bits;
    unsigned int    u32;
}HI_HW_CFG_T;    /* ���efuse�ϵ�⸴λ���group==127��ȡ�����ݼĴ��������������жϵȡ���ʼֵ���û�ͨ��efuse��дȷ�� */


/********************************************************************************/
/*    efuse ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_efusec_cfg_pgen,pgen,HI_EFUSEC_CFG_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_CFG_OFFSET)
HI_SET_GET(hi_efusec_cfg_pre_pg,pre_pg,HI_EFUSEC_CFG_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_CFG_OFFSET)
HI_SET_GET(hi_efusec_cfg_rden,rden,HI_EFUSEC_CFG_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_CFG_OFFSET)
HI_SET_GET(hi_efusec_cfg_aib_sel,aib_sel,HI_EFUSEC_CFG_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_CFG_OFFSET)
HI_SET_GET(hi_efusec_cfg_rr_en,rr_en,HI_EFUSEC_CFG_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_CFG_OFFSET)
HI_SET_GET(hi_efusec_cfg_pd_en,pd_en,HI_EFUSEC_CFG_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_CFG_OFFSET)
HI_SET_GET(hi_efusec_cfg_mr_en,mr_en,HI_EFUSEC_CFG_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_CFG_OFFSET)
HI_SET_GET(hi_efusec_cfg_undefined,undefined,HI_EFUSEC_CFG_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_CFG_OFFSET)
HI_SET_GET(hi_efusec_status_pg_status,pg_status,HI_EFUSEC_STATUS_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_STATUS_OFFSET)
HI_SET_GET(hi_efusec_status_rd_status,rd_status,HI_EFUSEC_STATUS_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_STATUS_OFFSET)
HI_SET_GET(hi_efusec_status_pgenb_status,pgenb_status,HI_EFUSEC_STATUS_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_STATUS_OFFSET)
HI_SET_GET(hi_efusec_status_rd_error,rd_error,HI_EFUSEC_STATUS_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_STATUS_OFFSET)
HI_SET_GET(hi_efusec_status_pd_status,pd_status,HI_EFUSEC_STATUS_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_STATUS_OFFSET)
HI_SET_GET(hi_efusec_status_undefined,undefined,HI_EFUSEC_STATUS_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_STATUS_OFFSET)
HI_SET_GET(hi_efuse_group_efuse_group,efuse_group,HI_EFUSE_GROUP_T,HI_EFUSE_BASE_ADDR, HI_EFUSE_GROUP_OFFSET)
HI_SET_GET(hi_efuse_group_undefined,undefined,HI_EFUSE_GROUP_T,HI_EFUSE_BASE_ADDR, HI_EFUSE_GROUP_OFFSET)
HI_SET_GET(hi_pg_value_pg_value,pg_value,HI_PG_VALUE_T,HI_EFUSE_BASE_ADDR, HI_PG_VALUE_OFFSET)
HI_SET_GET(hi_efusec_count_efusec_count,efusec_count,HI_EFUSEC_COUNT_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_COUNT_OFFSET)
HI_SET_GET(hi_efusec_count_undefined,undefined,HI_EFUSEC_COUNT_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_COUNT_OFFSET)
HI_SET_GET(hi_pgm_count_pgm_count,pgm_count,HI_PGM_COUNT_T,HI_EFUSE_BASE_ADDR, HI_PGM_COUNT_OFFSET)
HI_SET_GET(hi_pgm_count_undefined,undefined,HI_PGM_COUNT_T,HI_EFUSE_BASE_ADDR, HI_PGM_COUNT_OFFSET)
HI_SET_GET(hi_efusec_data_efusec_data,efusec_data,HI_EFUSEC_DATA_T,HI_EFUSE_BASE_ADDR, HI_EFUSEC_DATA_OFFSET)
HI_SET_GET(hi_hw_cfg_pgm_disable,pgm_disable,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_pad_disable,pad_disable,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_jtag_en,jtag_en,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_boot_sel,boot_sel,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_secboot_en,secboot_en,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_nf_ctrl_ena0,nf_ctrl_ena0,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_nf_block_size1,nf_block_size1,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_nf_ecc_type1,nf_ecc_type1,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_nf_page_size1,nf_page_size1,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_nf_addr_num1,nf_addr_num1,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_nf_ctrl_ena1,nf_ctrl_ena1,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_reserved_2,reserved_2,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_nf_block_size,nf_block_size,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_nf_ecc_type,nf_ecc_type,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_reserved_1,reserved_1,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_nf_page_size,nf_page_size,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_nf_addr_num,nf_addr_num,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_reserved_0,reserved_0,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_nf_ctrl_ena,nf_ctrl_ena,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)
HI_SET_GET(hi_hw_cfg_undefined,undefined,HI_HW_CFG_T,HI_EFUSE_BASE_ADDR, HI_HW_CFG_OFFSET)

/* ���efuse�Ƿ�������дbitλ */
static __inline__ unsigned int hi_efuse_get_pgm_disable_flag(void)
{
    return get_hi_hw_cfg_pgm_disable();
}

#endif // __HI_EFUSE_H__

