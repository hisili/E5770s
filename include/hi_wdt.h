/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_wdt.h */
/* Version       : 2.0 */
/* Created       : 2013-02-01*/
/* Last Modified : */
/* Description   :  The C union definition file for the module wdt*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_WDT_H__
#define __HI_WDT_H__

/*
 * Project: hi
 * Module : wdt
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    wdt �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_WDG_LOAD_OFFSET                                (0x0) /* ������ֵ�Ĵ���������WatchDog�ڲ��������ļ�����ֵ�� */
#define    HI_WDG_VALUE_OFFSET                               (0x4) /* ��������ǰֵ�Ĵ���������WatchDog�ڲ��������ĵ�ǰ����ֵ�� */
#define    HI_WDG_CONTROL_OFFSET                             (0x8) /* ���ƼĴ���������WatchDog�Ĵ�/�رա��жϺ͸�λ���ܡ� */
#define    HI_WDG_INTCLR_OFFSET                              (0xC) /* �ж�����Ĵ��������WatchDog�жϣ�ʹWatchDog���������ֵ���м��������Ĵ�����ֻд�Ĵ�����д��ȥ����ֵ����������WatchDog���жϣ��ڲ���������д���ֵ���޸�λֵ�� */
#define    HI_WDG_RIS_OFFSET                                 (0x10) /* ԭʼ�жϼĴ����� */
#define    HI_WDG_MIS_OFFSET                                 (0x14) /* ���κ��жϼĴ����� */
#define    HI_WDG_LOCK_OFFSET                                (0xC00) /* LOCK�Ĵ���������WatchDog�Ĵ����Ķ�дȨ�ޡ� */

/********************************************************************************/
/*    wdt �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    wdg_load                   : 32; /* [31..0] Watchdog�ڲ��ݼ��������ĳ�ʼֵ����ֵһ����ˢ�£��������������������� */
    } bits;
    unsigned int    u32;
}HI_WDG_LOAD_T;    /* ������ֵ�Ĵ���������WatchDog�ڲ��������ļ�����ֵ�� */

typedef union
{
    struct
    {
        unsigned int    wdogvalue                  : 32; /* [31..0] ���ڵݼ������ļ�������ǰֵ�� */
    } bits;
    unsigned int    u32;
}HI_WDG_VALUE_T;    /* ��������ǰֵ�Ĵ���������WatchDog�ڲ��������ĵ�ǰ����ֵ�� */

typedef union
{
    struct
    {
        unsigned int    inten                      : 1; /* [0..0] WatchDog�ж��ź����ʹ�ܡ�0��������ֹͣ����������ֵ���ֵ�ǰֵ���䣬WatchDog���رգ�1����������������ʹ���жϣ�WatchDog�����������ж���ǰ����ֹ�����ж��ٴα�ʹ��ʱ���������ӼĴ���WdogLoad�������ֵ�����¿�ʼ������ */
        unsigned int    resen                      : 1; /* [1..1] WatchDog��λ�ź����ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    reserved                   : 30; /* [31..2] ������ */
    } bits;
    unsigned int    u32;
}HI_WDG_CONTROL_T;    /* ���ƼĴ���������WatchDog�Ĵ�/�رա��жϺ͸�λ���ܡ� */

typedef union
{
    struct
    {
        unsigned int    wdg_intclr                 : 32; /* [31..0] �ԸüĴ���д������ֵ�����WatchDog���жϣ���ʹWatchDog�ӼĴ���WDG_LOAD�����������ֵ���¼����� */
    } bits;
    unsigned int    u32;
}HI_WDG_INTCLR_T;    /* �ж�����Ĵ��������WatchDog�жϣ�ʹWatchDog���������ֵ���м��������Ĵ�����ֻд�Ĵ�����д��ȥ����ֵ����������WatchDog���жϣ��ڲ���������д���ֵ���޸�λֵ�� */

typedef union
{
    struct
    {
        unsigned int    wdogris                    : 1; /* [0..0] WatchDogԭʼ�ж�״̬�����������ļ���ֵ�ݼ���0ʱ����λ��1��0��δ�����жϣ�1���Ѳ����жϡ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_WDG_RIS_T;    /* ԭʼ�жϼĴ����� */

typedef union
{
    struct
    {
        unsigned int    wdogmis                    : 1; /* [0..0] WatchDog�����κ��ж�״̬��0��δ�����жϻ����жϱ����Σ�1���Ѳ����жϡ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_WDG_MIS_T;    /* ���κ��жϼĴ����� */

typedef union
{
    struct
    {
        unsigned int    wdg_lock                   : 32; /* [31..0] ��üĴ���д��0x1ACC_E551���ɴ����мĴ�����дȨ�ޣ���üĴ���д������ֵ��ر�дȨ�ޡ����üĴ������ؼ�����״̬������д��üĴ�����ֵ��0x0000_0000������д���ʣ�δ��������0x0000_0001����ֹд���ʣ��Ѽ������� */
    } bits;
    unsigned int    u32;
}HI_WDG_LOCK_T;    /* LOCK�Ĵ���������WatchDog�Ĵ����Ķ�дȨ�ޡ� */


/********************************************************************************/
/*    wdt ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_wdg_load_wdg_load,wdg_load,HI_WDG_LOAD_T,HI_WDT_BASE_ADDR, HI_WDG_LOAD_OFFSET)
HI_SET_GET(hi_wdg_value_wdogvalue,wdogvalue,HI_WDG_VALUE_T,HI_WDT_BASE_ADDR, HI_WDG_VALUE_OFFSET)
HI_SET_GET(hi_wdg_control_inten,inten,HI_WDG_CONTROL_T,HI_WDT_BASE_ADDR, HI_WDG_CONTROL_OFFSET)
HI_SET_GET(hi_wdg_control_resen,resen,HI_WDG_CONTROL_T,HI_WDT_BASE_ADDR, HI_WDG_CONTROL_OFFSET)
HI_SET_GET(hi_wdg_control_reserved,reserved,HI_WDG_CONTROL_T,HI_WDT_BASE_ADDR, HI_WDG_CONTROL_OFFSET)
HI_SET_GET(hi_wdg_intclr_wdg_intclr,wdg_intclr,HI_WDG_INTCLR_T,HI_WDT_BASE_ADDR, HI_WDG_INTCLR_OFFSET)
HI_SET_GET(hi_wdg_ris_wdogris,wdogris,HI_WDG_RIS_T,HI_WDT_BASE_ADDR, HI_WDG_RIS_OFFSET)
HI_SET_GET(hi_wdg_ris_reserved,reserved,HI_WDG_RIS_T,HI_WDT_BASE_ADDR, HI_WDG_RIS_OFFSET)
HI_SET_GET(hi_wdg_mis_wdogmis,wdogmis,HI_WDG_MIS_T,HI_WDT_BASE_ADDR, HI_WDG_MIS_OFFSET)
HI_SET_GET(hi_wdg_mis_reserved,reserved,HI_WDG_MIS_T,HI_WDT_BASE_ADDR, HI_WDG_MIS_OFFSET)
HI_SET_GET(hi_wdg_lock_wdg_lock,wdg_lock,HI_WDG_LOCK_T,HI_WDT_BASE_ADDR, HI_WDG_LOCK_OFFSET)

#endif // __HI_WDT_H__

