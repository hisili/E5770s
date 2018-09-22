/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_pwm.h */
/* Version       : 2.0 */
/* Created       : 2013-09-30*/
/* Last Modified : */
/* Description   :  The C union definition file for the module pwm*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_PWM_H__
#define __HI_PWM_H__

/*
 * Project: hi
 * Module : pwm
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    pwm �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_PWM_OUTA_EN_OFFSET                             (0x0) /* PWM���1ʹ���ź����üĴ��� */
#define    HI_PWM_OUTB_EN_OFFSET                             (0x4) /* PWM���2ʹ���ź����üĴ����� */
#define    HI_PWM_OUTA_DIV_OFFSET                            (0x8) /* PWM���1��Ƶ��ָʾ�źżĴ����� */
#define    HI_PWM_OUTB_DIV_OFFSET                            (0xC) /* PWM���2��Ƶ��ָʾ�źżĴ����� */
#define    HI_PWM_OUTA_WIDE_OFFSET                           (0x10) /* PWM���1ռ�ձȵ��ƼĴ��� */
#define    HI_PWM_OUTB_WIDE_OFFSET                           (0x14) /* PWM���2ռ�ձȵ��ƼĴ��� */
#define    HI_PWM_OUTA_WARN_OFFSET                           (0x18) /* PWM���1ģʽ����Ĵ����� */
#define    HI_PWM_OUTB_WARN_OFFSET                           (0x1C) /* PWM���2ģʽ����Ĵ����� */

/********************************************************************************/
/*    pwm �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    OUTA_EN                    : 1; /* [0..0] PWM���1ʹ��:1��b0�����Ϊ�͵�ƽ��1��b1�����Ϊ���ƺ��ź� */
        unsigned int    reserved                   : 31; /* [31..1] ����λ����ʱ����0��дʱ��Ӱ�졣 */
    } bits;
    unsigned int    u32;
}HI_PWM_OUTA_EN_T;    /* PWM���1ʹ���ź����üĴ��� */

typedef union
{
    struct
    {
        unsigned int    OUTB_EN                    : 1; /* [0..0] PWM���2ʹ��:1��b0�����Ϊ�͵�ƽ��1��b1�����Ϊ���ƺ��ź� */
        unsigned int    reserved                   : 31; /* [31..1] ����λ����ʱ����0��дʱ��Ӱ�졣 */
    } bits;
    unsigned int    u32;
}HI_PWM_OUTB_EN_T;    /* PWM���2ʹ���ź����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    OUTA_DIV                   : 11; /* [10..0] ָʾ��Ƶϵ����11��b00000000001����Ƶ��1��1��11��b00000000010����Ƶ��2��1��11��b00000000011����Ƶ��3��1��11��b00000000100����Ƶ��4��1������ ����11��b10000000000����Ƶ��1024��1������ֵ�������塣 */
        unsigned int    reserved                   : 21; /* [31..11] ����λ����ʱ����0��дʱ��Ӱ�졣 */
    } bits;
    unsigned int    u32;
}HI_PWM_OUTA_DIV_T;    /* PWM���1��Ƶ��ָʾ�źżĴ����� */

typedef union
{
    struct
    {
        unsigned int    OUTB_DIV                   : 11; /* [10..0] ָʾ��Ƶϵ����11��b00000000001����Ƶ��1��1��11��b00000000010����Ƶ��2��1��11��b00000000011����Ƶ��3��1��11��b00000000100����Ƶ��4��1������ ����11��b10000000000����Ƶ��1024��1������ֵ�������塣 */
        unsigned int    reserved                   : 21; /* [31..11] ����λ����ʱ����0��дʱ��Ӱ�졣 */
    } bits;
    unsigned int    u32;
}HI_PWM_OUTB_DIV_T;    /* PWM���2��Ƶ��ָʾ�źżĴ����� */

typedef union
{
    struct
    {
        unsigned int    OUTA_WIDE                  : 11; /* [10..0] ָʾռ�ձȣ������Ƶ��ΪN��0��ռ�ձ�Ϊ0��ʼ��Ϊ�͵�ƽ����1��ռ�ձ�Ϊ1/N��2��ռ�ձ�Ϊ2/N������ ����N��ռ�ձ�Ϊ1��ʼ��Ϊ�ߵ�ƽ���������ʽָʾ����PWM_OUTA_DIV�Ĵ���ֵΪ0��PWM_OUTA_WIDE�Ĵ���ֵΪ0ʱ��ռ�ձ�Ϊ1/2�����������Ϊ�ο�ʱ�ӱ��� */
        unsigned int    reserved                   : 21; /* [31..11] ����λ����ʱ����0��дʱ��Ӱ�졣 */
    } bits;
    unsigned int    u32;
}HI_PWM_OUTA_WIDE_T;    /* PWM���1ռ�ձȵ��ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    OUTB_WIDE                  : 11; /* [10..0] ָʾռ�ձȣ������Ƶ��ΪN��0��ռ�ձ�Ϊ0��ʼ��Ϊ�͵�ƽ����1��ռ�ձ�Ϊ1/N��2��ռ�ձ�Ϊ2/N������ ����N��ռ�ձ�Ϊ1��ʼ��Ϊ�ߵ�ƽ���������ʽָʾ����PWM_OUTA_DIV�Ĵ���ֵΪ0��PWM_OUTA_WIDE�Ĵ���ֵΪ0ʱ��ռ�ձ�Ϊ1/2�����������Ϊ�ο�ʱ�ӱ��� */
        unsigned int    reserved                   : 21; /* [31..11] ������ */
    } bits;
    unsigned int    u32;
}HI_PWM_OUTB_WIDE_T;    /* PWM���2ռ�ձȵ��ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    OUTA_WARN                  : 1; /* [0..0] 1��b1��PWM_OUTA_WIDE��ֵ����PWM_OUTA_DIV��ֵ��ͬʱ���޲ο�ʱ������ʱָʾ����ߵ�ƽ��1��b0��PWM_OUTA_WIDE��ֵС�ڻ����PWM_OUTA_DIV��ֵ��ͬʱ���޲ο�ʱ������ʱָʾ����͵�ƽ�� */
        unsigned int    reserved                   : 31; /* [31..1] ����λ����ʱ����0��дʱ��Ӱ�졣 */
    } bits;
    unsigned int    u32;
}HI_PWM_OUTA_WARN_T;    /* PWM���1ģʽ����Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    OUTB_WARN                  : 1; /* [0..0] 1��b1��PWM_OUTB_WIDE��ֵ����PWM_OUTB_DIV��ֵ��ͬʱ���޲ο�ʱ������ʱָʾ����ߵ�ƽ��1��b0��PWM_OUTB_WIDE��ֵС�ڻ����PWM_OUTB_DIV��ֵ��ͬʱ���޲ο�ʱ������ʱָʾ����͵�ƽ�� */
        unsigned int    reserved                   : 31; /* [31..1] ����λ����ʱ����0��дʱ��Ӱ�졣 */
    } bits;
    unsigned int    u32;
}HI_PWM_OUTB_WARN_T;    /* PWM���2ģʽ����Ĵ����� */


/********************************************************************************/
/*    pwm ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_pwm_outa_en_outa_en,outa_en,HI_PWM_OUTA_EN_T,HI_PWM_BASE_ADDR, HI_PWM_OUTA_EN_OFFSET)
HI_SET_GET(hi_pwm_outa_en_reserved,reserved,HI_PWM_OUTA_EN_T,HI_PWM_BASE_ADDR, HI_PWM_OUTA_EN_OFFSET)
HI_SET_GET(hi_pwm_outb_en_outb_en,outb_en,HI_PWM_OUTB_EN_T,HI_PWM_BASE_ADDR, HI_PWM_OUTB_EN_OFFSET)
HI_SET_GET(hi_pwm_outb_en_reserved,reserved,HI_PWM_OUTB_EN_T,HI_PWM_BASE_ADDR, HI_PWM_OUTB_EN_OFFSET)
HI_SET_GET(hi_pwm_outa_div_outa_div,outa_div,HI_PWM_OUTA_DIV_T,HI_PWM_BASE_ADDR, HI_PWM_OUTA_DIV_OFFSET)
HI_SET_GET(hi_pwm_outa_div_reserved,reserved,HI_PWM_OUTA_DIV_T,HI_PWM_BASE_ADDR, HI_PWM_OUTA_DIV_OFFSET)
HI_SET_GET(hi_pwm_outb_div_outb_div,outb_div,HI_PWM_OUTB_DIV_T,HI_PWM_BASE_ADDR, HI_PWM_OUTB_DIV_OFFSET)
HI_SET_GET(hi_pwm_outb_div_reserved,reserved,HI_PWM_OUTB_DIV_T,HI_PWM_BASE_ADDR, HI_PWM_OUTB_DIV_OFFSET)
HI_SET_GET(hi_pwm_outa_wide_outa_wide,outa_wide,HI_PWM_OUTA_WIDE_T,HI_PWM_BASE_ADDR, HI_PWM_OUTA_WIDE_OFFSET)
HI_SET_GET(hi_pwm_outa_wide_reserved,reserved,HI_PWM_OUTA_WIDE_T,HI_PWM_BASE_ADDR, HI_PWM_OUTA_WIDE_OFFSET)
HI_SET_GET(hi_pwm_outb_wide_outb_wide,outb_wide,HI_PWM_OUTB_WIDE_T,HI_PWM_BASE_ADDR, HI_PWM_OUTB_WIDE_OFFSET)
HI_SET_GET(hi_pwm_outb_wide_reserved,reserved,HI_PWM_OUTB_WIDE_T,HI_PWM_BASE_ADDR, HI_PWM_OUTB_WIDE_OFFSET)
HI_SET_GET(hi_pwm_outa_warn_outa_warn,outa_warn,HI_PWM_OUTA_WARN_T,HI_PWM_BASE_ADDR, HI_PWM_OUTA_WARN_OFFSET)
HI_SET_GET(hi_pwm_outa_warn_reserved,reserved,HI_PWM_OUTA_WARN_T,HI_PWM_BASE_ADDR, HI_PWM_OUTA_WARN_OFFSET)
HI_SET_GET(hi_pwm_outb_warn_outb_warn,outb_warn,HI_PWM_OUTB_WARN_T,HI_PWM_BASE_ADDR, HI_PWM_OUTB_WARN_OFFSET)
HI_SET_GET(hi_pwm_outb_warn_reserved,reserved,HI_PWM_OUTB_WARN_T,HI_PWM_BASE_ADDR, HI_PWM_OUTB_WARN_OFFSET)

#endif // __HI_PWM_H__

