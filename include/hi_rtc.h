/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_rtc.h */
/* Version       : 2.0 */
/* Created       : 2013-02-02*/
/* Last Modified : */
/* Description   :  The C union definition file for the module rtc*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_RTC_H__
#define __HI_RTC_H__

/*
 * Project: hi
 * Module : rtc
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    rtc �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_RTC_CCVR_OFFSET                                (0x0) /* ��ǰ����ֵ�Ĵ����� */
#define    HI_RTC_CMR_OFFSET                                 (0x4) /* �Ƚ�ֵ�Ĵ����� */
#define    HI_RTC_CLR_OFFSET                                 (0x8) /* ����ֵ�Ĵ����� */
#define    HI_RTC_CCR_OFFSET                                 (0xC) /* ���ƼĴ����� */
#define    HI_RTC_STAT_OFFSET                                (0x10) /* �ж�״̬�Ĵ����� */
#define    HI_RTC_RSTAT_OFFSET                               (0x14) /* ԭʼ�ж�״̬�Ĵ����� */
#define    HI_RTC_EOI_OFFSET                                 (0x18) /* �ж�����Ĵ����� */

/********************************************************************************/
/*    rtc �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    ccvr                       : 32; /* [31..0] ��������ǰ����ֵ�� */
    } bits;
    unsigned int    u32;
}HI_RTC_CCVR_T;    /* ��ǰ����ֵ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    cmr                        : 32; /* [31..0] ���ж�ʹ�ܵ�ǰ���£����ڲ��������ļ���ֵ��üĴ������ʱ�������жϡ� */
    } bits;
    unsigned int    u32;
}HI_RTC_CMR_T;    /* �Ƚ�ֵ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    clr                        : 32; /* [31..0] �����ڲ���������ʼֵ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI_RTC_CLR_T;    /* ����ֵ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtc_ien                    : 1; /* [0..0] �ж�ʹ�ܿ���λ��0���������жϣ�1�������жϡ� */
        unsigned int    rtc_mask                   : 1; /* [1..1] �ж����ο���λ��0���������жϣ�1�������жϡ� */
        unsigned int    reserved                   : 30; /* [31..2] ������ */
    } bits;
    unsigned int    u32;
}HI_RTC_CCR_T;    /* ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    rtc_stat                   : 1; /* [0..0] �������κ���ж�״̬�Ĵ�����0���ж���Ч��1���ж���Ч�� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_RTC_STAT_T;    /* �ж�״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtc_rstat                  : 1; /* [0..0] δ�����ε��ж�״̬�Ĵ�����0���ж���Ч��1���ж���Ч�� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_RTC_RSTAT_T;    /* ԭʼ�ж�״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtc_eoi                    : 1; /* [0..0] �ж�����Ĵ�����ͨ�����üĴ���������жϡ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_RTC_EOI_T;    /* �ж�����Ĵ����� */


/********************************************************************************/
/*    rtc ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_rtc_ccvr_ccvr,ccvr,HI_RTC_CCVR_T,HI_RTC_BASE_ADDR, HI_RTC_CCVR_OFFSET)
HI_SET_GET(hi_rtc_cmr_cmr,cmr,HI_RTC_CMR_T,HI_RTC_BASE_ADDR, HI_RTC_CMR_OFFSET)
HI_SET_GET(hi_rtc_clr_clr,clr,HI_RTC_CLR_T,HI_RTC_BASE_ADDR, HI_RTC_CLR_OFFSET)
HI_SET_GET(hi_rtc_ccr_rtc_ien,rtc_ien,HI_RTC_CCR_T,HI_RTC_BASE_ADDR, HI_RTC_CCR_OFFSET)
HI_SET_GET(hi_rtc_ccr_rtc_mask,rtc_mask,HI_RTC_CCR_T,HI_RTC_BASE_ADDR, HI_RTC_CCR_OFFSET)
HI_SET_GET(hi_rtc_ccr_reserved,reserved,HI_RTC_CCR_T,HI_RTC_BASE_ADDR, HI_RTC_CCR_OFFSET)
HI_SET_GET(hi_rtc_stat_rtc_stat,rtc_stat,HI_RTC_STAT_T,HI_RTC_BASE_ADDR, HI_RTC_STAT_OFFSET)
HI_SET_GET(hi_rtc_stat_reserved,reserved,HI_RTC_STAT_T,HI_RTC_BASE_ADDR, HI_RTC_STAT_OFFSET)
HI_SET_GET(hi_rtc_rstat_rtc_rstat,rtc_rstat,HI_RTC_RSTAT_T,HI_RTC_BASE_ADDR, HI_RTC_RSTAT_OFFSET)
HI_SET_GET(hi_rtc_rstat_reserved,reserved,HI_RTC_RSTAT_T,HI_RTC_BASE_ADDR, HI_RTC_RSTAT_OFFSET)
HI_SET_GET(hi_rtc_eoi_rtc_eoi,rtc_eoi,HI_RTC_EOI_T,HI_RTC_BASE_ADDR, HI_RTC_EOI_OFFSET)
HI_SET_GET(hi_rtc_eoi_reserved,reserved,HI_RTC_EOI_T,HI_RTC_BASE_ADDR, HI_RTC_EOI_OFFSET)

#endif // __HI_RTC_H__

