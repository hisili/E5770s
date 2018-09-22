/******************************************************************************/
/*  Copyright (C), 2007-2014, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_sio.h */
/* Version       : 2.0 */
/* Author        : zuofenghua*/
/* Created       : 2014-06-28*/
/* Last Modified : */
/* Description   :  The C union definition file for the module sio*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Author        : zuofenghua*/
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_SIO_H__
#define __HI_SIO_H__

/*
 * Project: hi
 * Module : sio
 */

#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4)
#endif

/********************************************************************************/
/*    sio �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_SIO_VERSION_OFFSET                             (0x3C) /* �汾�Ĵ�����������¼SIO�İ汾�źͽ���SIO���Բ��ԡ� */
#define    HI_SIO_MODE_OFFSET                                (0x40) /* ģʽ�Ĵ�����������SIO�����Ļ���ģʽ����ѡ��(I)��ģʽ�£�CRG��ʱ�Ӻ�ͬ���źŸ�CODEC��ͬʱ��SIO��(I)��ģʽ�£�ʱ�Ӻ�ͬ���ź����ⲿCODEC�͸�SIO��I2S��PCM������ģʽѡ����ϵͳ���ƼĴ���SC_PERCTRL6�趨�� */
#define    HI_SIO_INTSTATUS_OFFSET                           (0x44) /* SIO���ж�״ָ̬ʾ�Ĵ��������ڽ����жϣ�������FIFO��������ȴ���FIFO��ֵʱ����һֱ�Ѹߵ�ƽ���浽�ж�״̬�Ĵ����У�һֱ�����жϣ���ʹCPU��һ���жϣ����ж�״̬�Ĵ���������һ��ʱ�������ٴ���λ������ˣ�����CPU�Ĵ�����Ϊ��(S)��SIO_CT_CLR[intr_en]д1���ر�ȫ���ж�ʹ�ܡ�(S)���ж�״̬�Ĵ���SIO_INTSTATUS��(S)�����ж�Դ������Ӧ����(S)��SIO_INTCLR����Ӧλд1������жϡ�(S)��д�Ĵ���SIO_CT_SET[intr_en]д1����ȫ���ж�ʹ�ܡ�(SE)�����жϵĲ�����ʽ������жϲ�����ʽ��ͬ����˶��ڷ����жϵĴ�������Ҳ������ͬ�ķ�ʽ�����Ĵ�����ԭʼ�ж�״̬�Ĵ���������Ӧ�ж�λ���ε�����£��ж���������ʱ����Ӧ�ж�״̬λ��Ȼ����λ�������ᴥ���жϡ� */
#define    HI_SIO_INTCLR_OFFSET                              (0x48) /* �ж�����Ĵ��������԰�λ�����BitֵΪ0��ʾ������жϣ�Ϊ1��ʾ����жϡ� */
#define    HI_SIO_I2S_LEFT_XD_OFFSET                         (0x4C) /* I2Sģʽ�µ����������ݷ��ͼĴ�������Ĵ���д����ʱ����Ч��������ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */
#define    HI_SIO_I2S_RIGHT_XD_OFFSET                        (0x50) /* I2Sģʽ�µ����������ݷ��ͼĴ�����PCM���ݷ��ͼĴ�����I2S���������ݷ��ͼĴ����Ǹ��õġ���Ĵ���д����ʱ����Ч��������ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */
#define    HI_SIO_PCM_XD_OFFSET                              (0x50) /* PCMģʽ�µ����ݷ��ͼĴ�����PCM���ݷ��ͼĴ�����I2S���������ݷ��ͼĴ����Ǹ��õġ���Ĵ���д��Ч����ʱ����Ч��������ڼĴ����ĵ�bit�������磬8bit���ʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݡ�16bit���ʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */
#define    HI_SIO_I2S_LEFT_RD_OFFSET                         (0x54) /* I2S���������ݽ��ռĴ�����SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */
#define    HI_SIO_I2S_RIGHT_RD_OFFSET                        (0x58) /* I2S���������ݽ��ռĴ�����SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */
#define    HI_SIO_PCM_RD_OFFSET                              (0x58) /* PCM�������ݼĴ���������I2S���������ռĴ����Ǹ��õġ�SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */
#define    HI_SIO_CT_SET_OFFSET                              (0x5C) /* ���üĴ�����Ϊ���ܹ�����Ķ�SIO���ƼĴ�������λ��������SIO�У�ΪSIO���ƼĴ���������2����ַ��0x05C��SIO_CT_SET����0x060��SIO_CT_CLR�������У�0x05CΪ���üĴ�����ַ������0x05C�Ĵ�������Ӧλд��1ʱ����Ӧλ����Ϊ1��д0��Ч���üĴ�������Ϊ��д�� */
#define    HI_SIO_CT_CLR_OFFSET                              (0x60) /* ����Ĵ�����Ϊ���ܹ�����Ķ�SIO���ƼĴ�������λ��������SIO�У�ΪSIO���ƼĴ���������2����ַ��0x05C��SIO_CT_SET����0x060��SIO_CT_CLR�������У�0x060Ϊ����Ĵ�����ַ������Ĵ�������Ӧλд��1ʱ����Ӧλ�������д0��Ч���üĴ�������Ϊֻд�� */
#define    HI_SIO_RX_STA_OFFSET                              (0x68) /* SIO����״̬�Ĵ����� */
#define    HI_SIO_TX_STA_OFFSET                              (0x6C) /* SIO����״̬�Ĵ����� */
#define    HI_SIO_DATA_WIDTH_SET_OFFSET                      (0x78) /* I2S/PCMģʽ�µ����ݿ�����üĴ����� */
#define    HI_SIO_I2S_START_POS_OFFSET                       (0x7C) /* I2S����������ʼλ�����ÿ��ƼĴ�������I2Sģʽ�£������������ݲ�����ַ�ϲ�ʹ�ܺ󣬿�����ʼ�����Ǵ���������ʼ���Ǵ���������ʼ�� */
#define    HI_I2S_POS_FLAG_OFFSET                            (0x80) /* I2S��������������ǰλ��״̬�Ĵ�������I2Sģʽ�£������������ݲ�����ַ�ϲ�ʹ�ܺ�ָʾ��һ�η��ʼĴ����Ǵ���������ʼ���Ǵ���������ʼ�� */
#define    HI_SIO_SIGNED_EXT_OFFSET                          (0x84) /* ��λ���ݷ�����չʹ�ܼĴ������ñ�־ֻ�Խ���������Ч���Է���������Ч��PCMģʽ��I2Sģʽ�½��յ������ݶ�֧�ַ�����չ���ڽ�����Ч����λ��Ϊ8/16/18/20/24 bitʱ������ñ�־ʹ�ܣ��ѽ��յ�������ת��Ϊ32bit����ʱ����32bit���ݵĸ�λ��Ч��������Ϊ�������������Чbit��Ӧ��ֵ��Ȼ����д�����FIFO����16bitλ��Ϊ����if (data_rx[15] == 1 ) data_rx[31:16]=0xffff;elsedata_rx[31:16]=0x0000; */
#define    HI_SIO_I2S_POS_MERGE_EN_OFFSET                    (0x88) /* I2Sģʽ�����������ݲ�����ַ�ϲ�ʹ�ܼĴ�������I2Sģʽ�£���DMA��ʽ��дSIO��FIFO����ʱ����Ϊ�����������ݵ�ַ��ͬ����ҪCPU��������DMA�����ĵ�ַ������CPUЧ�ʵ͡�Ϊ�����CPU��Ч�ʣ��ṩ�����������ݵĶ�д��ͳһ��ַʹ�ܿ��ơ�ʹ������£���������������ͳһʹ��SIO_I2S_DUAL_RX_CHN�Ĵ�����д������������ͳһʹ��SIO_I2S_DUAL_TX_CHN�Ĵ����� */
#define    HI_SIO_INTMASK_OFFSET                             (0x8C) /* �ж����μĴ����� */
#define    HI_SIO_I2S_DUAL_RX_CHN_OFFSET                     (0xA0) /* ��ȡ�������ݼĴ�����I2S��������������ַ�ϲ�ʹ�ܺ󣬶�ȡ�������ݡ� */
#define    HI_SIO_I2S_DUAL_TX_CHN_OFFSET                     (0xC0) /* д�������ݼĴ�����I2S��������������ַ�ϲ�ʹ�ܺ�д�������ݡ� */


#ifndef __ASSEMBLY__

/********************************************************************************/
/*    sio �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    vesion                     : 8; /* [7..0] SIO�İ汾�š� */
        unsigned int    sio_loop                   : 1; /* [8..8] 0������ģʽ��1��SIO���ͺͽ������ݻ���ģʽ������SIO���Բ��ԡ��ڸ�ģʽ�£���SIO�Ķ���ӿڴ���SIO���մ�����������SIO���ʹ���������ֱ�������� */
        unsigned int    reserved                   : 23; /* [31..9] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_VERSION_T;    /* �汾�Ĵ�����������¼SIO�İ汾�źͽ���SIO���Բ��ԡ� */

typedef union
{
    struct
    {
        unsigned int    sio_mode                   : 1; /* [0..0] PCM/I2Sģʽѡ��0��I2Sģʽ��1��PCMģʽ�� */
        unsigned int    pcm_mode                   : 1; /* [1..1] PCMʱ��ģʽ��0����׼ģʽ��1���Զ���ģʽ�� */
        unsigned int    reserved_1                 : 1; /* [2..2] ��������������Ϊ0 */
        unsigned int    ext_rec_en                 : 1; /* [3..3] ��׼ģʽ�£�I2S�����������������ݣ�������������������PCMֻ����һ�����������ݡ���·����ģʽ�£�����I2S��PCM������ͨ�����������á���ģʽ�£�ͨ�������ݿ�ȱ���Ϊ8bit��16bit��0����׼��I2S��PCM����ģʽ��1����չ��I2S��PCM��·����ģʽ�� */
        unsigned int    chn_num                    : 2; /* [5..4] ��·���յ�ͨ����ѡ��00��2 chn��01��4 chn��10��8 chn��11��16 chn */
        unsigned int    clk_edge                   : 1; /* [6..6] PCM��·����ģʽ�£���������ʱ�ӱ���ѡ��0���½�����Ч��1����������Ч�� */
        unsigned int    reserved_0                 : 25; /* [31..7] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_MODE_T;    /* ģʽ�Ĵ�����������SIO�����Ļ���ģʽ����ѡ��(I)��ģʽ�£�CRG��ʱ�Ӻ�ͬ���źŸ�CODEC��ͬʱ��SIO��(I)��ģʽ�£�ʱ�Ӻ�ͬ���ź����ⲿCODEC�͸�SIO��I2S��PCM������ģʽѡ����ϵͳ���ƼĴ���SC_PERCTRL6�趨�� */

typedef union
{
    struct
    {
        unsigned int    rx_intr                    : 1; /* [0..0] ����FIFO������ֵ�ж�״̬��0��δ�����жϣ�1���Ѳ����жϡ� */
        unsigned int    tx_intr                    : 1; /* [1..1] ����FIFO������ֵ�ж�״̬��0��δ�����жϣ�1���Ѳ����жϡ� */
        unsigned int    rx_right_fifo_over         : 1; /* [2..2] I2Sģʽ�£�����������FIFO�����ж�״̬��PCMģʽ�£�PCM����FIFO�����־��0��δ�����жϣ�1���Ѳ����жϡ� */
        unsigned int    rx_left_fifo_over          : 1; /* [3..3] I2Sģʽ�£�����������FIFO�����ж�״̬��PCMģʽ����Ч��0��δ�����жϣ�1���Ѳ����жϡ� */
        unsigned int    tx_right_fifo_under        : 1; /* [4..4] I2Sģʽ�£�����������FIFO�����ж�״̬��PCMģʽ�£�PCM����FIFO�����־��0��δ�����жϣ�1���Ѳ����жϡ� */
        unsigned int    tx_left_fifo_under         : 1; /* [5..5] I2Sģʽ�£�����������FIFO�����ж�״̬��PCMģʽ����Ч��0��δ�����жϣ�1���Ѳ����жϡ� */
        unsigned int    reserved                   : 26; /* [31..6] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_INTSTATUS_T;    /* SIO���ж�״ָ̬ʾ�Ĵ��������ڽ����жϣ�������FIFO��������ȴ���FIFO��ֵʱ����һֱ�Ѹߵ�ƽ���浽�ж�״̬�Ĵ����У�һֱ�����жϣ���ʹCPU��һ���жϣ����ж�״̬�Ĵ���������һ��ʱ�������ٴ���λ������ˣ�����CPU�Ĵ�����Ϊ��(S)��SIO_CT_CLR[intr_en]д1���ر�ȫ���ж�ʹ�ܡ�(S)���ж�״̬�Ĵ���SIO_INTSTATUS��(S)�����ж�Դ������Ӧ����(S)��SIO_INTCLR����Ӧλд1������жϡ�(S)��д�Ĵ���SIO_CT_SET[intr_en]д1����ȫ���ж�ʹ�ܡ�(SE)�����жϵĲ�����ʽ������жϲ�����ʽ��ͬ����˶��ڷ����жϵĴ�������Ҳ������ͬ�ķ�ʽ�����Ĵ�����ԭʼ�ж�״̬�Ĵ���������Ӧ�ж�λ���ε�����£��ж���������ʱ����Ӧ�ж�״̬λ��Ȼ����λ�������ᴥ���жϡ� */

typedef union
{
    struct
    {
        unsigned int    rx_intr                    : 1; /* [0..0] ����FIFO������ֵ�ж������ */
        unsigned int    tx_intr                    : 1; /* [1..1] ����FIFO������ֵ�ж������ */
        unsigned int    rx_right_fifo_over         : 1; /* [2..2] I2Sģʽ�£�����������FIFO�����ж������PCMģʽ�£�PCM����FIFO�����ж������ */
        unsigned int    rx_left_fifo_over          : 1; /* [3..3] I2Sģʽ�£�����������FIFO�����ж������PCMģʽ����Ч�� */
        unsigned int    tx_right_fifo_under        : 1; /* [4..4] I2Sģʽ�£�����������FIFO�����ж������PCMģʽ�£�PCM����FIFO�����ж������ */
        unsigned int    tx_left_fifo_under         : 1; /* [5..5] I2Sģʽ�£�����������FIFO�����ж������PCMģʽ����Ч�� */
        unsigned int    reserved                   : 26; /* [31..6] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_INTCLR_T;    /* �ж�����Ĵ��������԰�λ�����BitֵΪ0��ʾ������жϣ�Ϊ1��ʾ����жϡ� */

typedef union
{
    struct
    {
        unsigned int    tx_left_data               : 32; /* [31..0] �������������ݡ� */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_LEFT_XD_T;    /* I2Sģʽ�µ����������ݷ��ͼĴ�������Ĵ���д����ʱ����Ч��������ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */

typedef union
{
    struct
    {
        unsigned int    tx_right_data              : 32; /* [31..0] �������������ݡ� */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_RIGHT_XD_T;    /* I2Sģʽ�µ����������ݷ��ͼĴ�����PCM���ݷ��ͼĴ�����I2S���������ݷ��ͼĴ����Ǹ��õġ���Ĵ���д����ʱ����Ч��������ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */

typedef union
{
    struct
    {
        unsigned int    tx_data                    : 16; /* [15..0] PCM�������ݡ� */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_PCM_XD_T;    /* PCMģʽ�µ����ݷ��ͼĴ�����PCM���ݷ��ͼĴ�����I2S���������ݷ��ͼĴ����Ǹ��õġ���Ĵ���д��Ч����ʱ����Ч��������ڼĴ����ĵ�bit�������磬8bit���ʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݡ�16bit���ʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */

typedef union
{
    struct
    {
        unsigned int    rx_left_data               : 32; /* [31..0] I2S�������������ݡ� */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_LEFT_RD_T;    /* I2S���������ݽ��ռĴ�����SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */

typedef union
{
    struct
    {
        unsigned int    rx_right_data              : 32; /* [31..0] I2S�������������ݡ� */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_RIGHT_RD_T;    /* I2S���������ݽ��ռĴ�����SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */

typedef union
{
    struct
    {
        unsigned int    rx__data                   : 16; /* [15..0] PCM�������ݡ� */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_PCM_RD_T;    /* PCM�������ݼĴ���������I2S���������ռĴ����Ǹ��õġ�SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0�� */

typedef union
{
    struct
    {
        unsigned int    tx_fifo_threshold          : 4; /* [3..0] ����FIFO��ֵ����tx_right_depth < (tx_fifo_threshold + 1)ʱ���������жϺ�DMA���� */
        unsigned int    rx_fifo_threshold          : 4; /* [7..4] ����FIFO��ֵ����rx_right_depth 3 (rx_fifo_threshold + 1)ʱ���������жϺ�DMA���� */
        unsigned int    tx_data_merge_en           : 1; /* [8..8] ���ݷ��ͺϲ�ʹ�ܣ�ֻ��I2S ģʽ��������λ��Ϊ16bitʱ��Ч��0����ʹ�ܣ�1��ʹ�ܡ���λΪ1ʱ��������������ƴ��һ��32bit������FIFO�н��д洢��������16bit����ռ�ݸ�16λ��������16bit����ռ�ݵ�16λ�������������FIFO�������ʣ����ṩ����ʱ��Ļ�������������������£�CPU����FIFO��д������ʱ����������˳����������FIFOд��һ��32bit���ݣ�����������16bit�ϲ��ɵ�һ��32bit���ݣ�������������FIFOд��һ��32bit���ݣ���˷����� */
        unsigned int    rx_data_merge_en           : 1; /* [9..9] ���ݽ��պϲ�ʹ�ܣ�ֻ��I2Sģʽ��������λ��Ϊ16bitʱ��Ч��0����ʹ�ܣ�1��ʹ�ܡ���λΪ1ʱ��������������ƴ��һ��32bit������FIFO�н��д洢��������16bit����ռ�ݸ�16λ��������16bit����ռ�ݵ�16λ�������������FIFO�������ʣ����ṩ����ʱ��Ļ���������CPU�ӽ���FIFO�ж�����ʱ����������˳�򣺴�������FIFO����һ��32bit���ݣ�����������16bit�ϲ��ɵ�һ��32bit���ݣ����ٴ�������FIFO����һ��32bit���ݣ���˷����� */
        unsigned int    tx_fifo_disable            : 1; /* [10..10] ����FIFO��ֹ��0��ʹ�ܣ�1����ֹ�� */
        unsigned int    rx_fifo_disable            : 1; /* [11..11] ����FIFO��ֹ��0��ʹ�ܣ�1����ֹ�� */
        unsigned int    tx_enable                  : 1; /* [12..12] ����ͨ��ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    rx_enable                  : 1; /* [13..13] ����ͨ��ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    intr_en                    : 1; /* [14..14] �ж�ȫ��ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    rst_n                      : 1; /* [15..15] I2S/PCMͨ����λ���͵�ƽ��Ч������I2S/PCM���պͷ���ģ�飨����FIFO�����и�λ����˷��ͺͽ���FIFO״̬�Ĵ������Ϊ0�������ḴλCPU�ӿڼĴ���ģ�顣 */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_CT_SET_T;    /* ���üĴ�����Ϊ���ܹ�����Ķ�SIO���ƼĴ�������λ��������SIO�У�ΪSIO���ƼĴ���������2����ַ��0x05C��SIO_CT_SET����0x060��SIO_CT_CLR�������У�0x05CΪ���üĴ�����ַ������0x05C�Ĵ�������Ӧλд��1ʱ����Ӧλ����Ϊ1��д0��Ч���üĴ�������Ϊ��д�� */

typedef union
{
    struct
    {
        unsigned int    tx_fifo_threshold          : 4; /* [3..0] ����FIFO��ֵ����tx_right_depth < (tx_fifo_threshold + 1)ʱ���������жϺ�DMA���� */
        unsigned int    rx_fifo_threshold          : 4; /* [7..4] ����FIFO��ֵ����rx_right_depth 3 (rx_fifo_threshold + 1)ʱ���������жϺ�DMA���� */
        unsigned int    tx_data_merge_en           : 1; /* [8..8] ���ݷ��ͺϲ�ʹ�ܣ�ֻ��I2S ģʽ��������λ��Ϊ16bitʱ��Ч��0����ʹ�ܣ�1��ʹ�ܡ���λΪ1ʱ��������������ƴ��һ��32bit������FIFO�н��д洢��������16bit����ռ�ݸ�16λ��������16bit����ռ�ݵ�16λ�������������FIFO�������ʣ����ṩ����ʱ��Ļ�������������������£�CPU����FIFO��д������ʱ����������˳����������FIFOд��һ��32bit���ݣ�����������16bit�ϲ��ɵ�һ��32bit���ݣ�������������FIFOд��һ��32bit���ݣ���˷����� */
        unsigned int    rx_data_merge_en           : 1; /* [9..9] ���ݽ��պϲ�ʹ�ܣ�ֻ��I2Sģʽ��������λ��Ϊ16bitʱ��Ч��0����ʹ�ܣ�1��ʹ�ܡ���λΪ1ʱ��������������ƴ��һ��32bit������FIFO�н��д洢��������16bit����ռ�ݸ�16λ��������16bit����ռ�ݵ�16λ�������������FIFO�������ʣ����ṩ����ʱ��Ļ���������CPU�ӽ���FIFO�ж�����ʱ����������˳�򣺴�������FIFO����һ��32bit���ݣ�����������16bit�ϲ��ɵ�һ��32bit���ݣ����ٴ�������FIFO����һ��32bit���ݣ���˷����� */
        unsigned int    tx_fifo_disable            : 1; /* [10..10] ����FIFO��ֹ��0��ʹ�ܣ�1����ֹ�� */
        unsigned int    rx_fifo_disable            : 1; /* [11..11] ����FIFO��ֹ��0��ʹ�ܣ�1����ֹ�� */
        unsigned int    tx_enable                  : 1; /* [12..12] ����ͨ��ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    rx_enable                  : 1; /* [13..13] ����ͨ��ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    intr_en                    : 1; /* [14..14] �ж�ȫ��ʹ�ܡ�0����ֹ��1��ʹ�ܡ� */
        unsigned int    rst_n                      : 1; /* [15..15] I2S/PCMͨ����λ���͵�ƽ��Ч������I2S/PCM���պͷ���ģ�飨����FIFO�����и�λ����˷��ͺͽ���FIFO״̬�Ĵ������Ϊ0�������ḴλCPU�ӿڼĴ���ģ�顣 */
        unsigned int    reserved                   : 16; /* [31..16] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_CT_CLR_T;    /* ����Ĵ�����Ϊ���ܹ�����Ķ�SIO���ƼĴ�������λ��������SIO�У�ΪSIO���ƼĴ���������2����ַ��0x05C��SIO_CT_SET����0x060��SIO_CT_CLR�������У�0x060Ϊ����Ĵ�����ַ������Ĵ�������Ӧλд��1ʱ����Ӧλ�������д0��Ч���üĴ�������Ϊֻд�� */

typedef union
{
    struct
    {
        unsigned int    rx_right_depth             : 5; /* [4..0] I2Sģʽ�£�Ϊ����������FIFO���ָʾ��PCMģʽ�£�ΪPCM����FIFO���ָʾ�� */
        unsigned int    rx_left_depth              : 5; /* [9..5] ����������FIFO���ָʾ��ֻ��I2Sģʽ����Ч�� */
        unsigned int    reserved                   : 22; /* [31..10] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_RX_STA_T;    /* SIO����״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    tx_right_depth             : 5; /* [4..0] I2Sģʽ�£�Ϊ����������FIFO���ָʾ��PCMģʽ�£�ΪPCM����FIFO���ָʾ�� */
        unsigned int    tx_left_depth              : 5; /* [9..5] ����������FIFO���ָʾ��ֻ��I2Sģʽ����Ч�� */
        unsigned int    reserved                   : 22; /* [31..10] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_TX_STA_T;    /* SIO����״̬�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    tx_mode                    : 3; /* [2..0] �������ݳ�������λ������I2Sģʽ000��������001��16bit��010��18bit��011��20bit��100��24bit��101��32bit��110��111��������000��8bit001��16bit��010��32bit��011��64bit��100��128bit��101��111�������� */
        unsigned int    rx_mode                    : 3; /* [5..3] �������ݳ�������λ��000��8bit��001��16bit��010��18bit��011��20bit��100��24bit��101��32bit��110��111������������I2Sģʽ��֧��16/18/20/24/32bit������PCMģʽ��֧��8/16bit�����ڶ�·���գ�����ģʽֻ֧��8/16bit�� */
        unsigned int    reserved                   : 26; /* [31..6] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_DATA_WIDTH_SET_T;    /* I2S/PCMģʽ�µ����ݿ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    start_pos_read             : 1; /* [0..0] ������FIFOʱ��0������������ʼ���ʣ�1������������ʼ���ʡ� */
        unsigned int    start_pos_write            : 1; /* [1..1] д����FIFOʱ��0������������ʼ���ʣ�1������������ʼ���ʡ� */
        unsigned int    reserved                   : 30; /* [31..2] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_START_POS_T;    /* I2S����������ʼλ�����ÿ��ƼĴ�������I2Sģʽ�£������������ݲ�����ַ�ϲ�ʹ�ܺ󣬿�����ʼ�����Ǵ���������ʼ���Ǵ���������ʼ�� */

typedef union
{
    struct
    {
        unsigned int    start_pos_read             : 1; /* [0..0] ������FIFOʱ��0����һ�δ���������ʼ���ʣ�1����һ�δ���������ʼ���ʡ� */
        unsigned int    start_pos_write            : 1; /* [1..1] д����FIFOʱ��0����һ�δ���������ʼ���ʣ�1����һ�δ���������ʼ���ʡ� */
        unsigned int    reserved                   : 30; /* [31..2] ������ */
    } bits;
    unsigned int    u32;
}HI_I2S_POS_FLAG_T;    /* I2S��������������ǰλ��״̬�Ĵ�������I2Sģʽ�£������������ݲ�����ַ�ϲ�ʹ�ܺ�ָʾ��һ�η��ʼĴ����Ǵ���������ʼ���Ǵ���������ʼ�� */

typedef union
{
    struct
    {
        unsigned int    signed_ext_en              : 1; /* [0..0] ��λ���ݷ�����չʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_SIGNED_EXT_T;    /* ��λ���ݷ�����չʹ�ܼĴ������ñ�־ֻ�Խ���������Ч���Է���������Ч��PCMģʽ��I2Sģʽ�½��յ������ݶ�֧�ַ�����չ���ڽ�����Ч����λ��Ϊ8/16/18/20/24 bitʱ������ñ�־ʹ�ܣ��ѽ��յ�������ת��Ϊ32bit����ʱ����32bit���ݵĸ�λ��Ч��������Ϊ�������������Чbit��Ӧ��ֵ��Ȼ����д�����FIFO����16bitλ��Ϊ����if (data_rx[15] == 1 ) data_rx[31:16]=0xffff;elsedata_rx[31:16]=0x0000; */

typedef union
{
    struct
    {
        unsigned int    merge_en                   : 1; /* [0..0] ��I2Sģʽ�£��������������ݵĲ�����ַ�ϲ�ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    reserved                   : 31; /* [31..1] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_POS_MERGE_EN_T;    /* I2Sģʽ�����������ݲ�����ַ�ϲ�ʹ�ܼĴ�������I2Sģʽ�£���DMA��ʽ��дSIO��FIFO����ʱ����Ϊ�����������ݵ�ַ��ͬ����ҪCPU��������DMA�����ĵ�ַ������CPUЧ�ʵ͡�Ϊ�����CPU��Ч�ʣ��ṩ�����������ݵĶ�д��ͳһ��ַʹ�ܿ��ơ�ʹ������£���������������ͳһʹ��SIO_I2S_DUAL_RX_CHN�Ĵ�����д������������ͳһʹ��SIO_I2S_DUAL_TX_CHN�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rx_intr                    : 1; /* [0..0] ����FIFO������ֵ�ж����Ρ�0�������θ��жϣ�1�����θ��жϡ� */
        unsigned int    tx_intr                    : 1; /* [1..1] ����FIFO������ֵ�ж����Ρ�0�������θ��жϣ�1�����θ��жϡ� */
        unsigned int    rx_right_fifo_over         : 1; /* [2..2] I2Sģʽ�£�����������FIFO�����ж����Ρ�PCMģʽ�£�PCM����FIFO�����ж����Ρ�0�������θ��жϣ�1�����θ��жϡ� */
        unsigned int    rx_left_fifo_over          : 1; /* [3..3] I2Sģʽ�£�����������FIFO�����ж����Ρ�PCMģʽ����Ч��0�������θ��жϣ�1�����θ��жϡ� */
        unsigned int    tx_right_fifo_under        : 1; /* [4..4] I2Sģʽ�£�����������FIFO�����ж����Ρ�PCMģʽ�£�PCM����FIFO�����ж����Ρ�0�������θ��жϣ�1�����θ��жϡ� */
        unsigned int    tx_left_fifo_under         : 1; /* [5..5] I2Sģʽ�£�����������FIFO�����ж����Ρ�PCMģʽ����Ч��0�������θ��жϣ�1�����θ��жϡ� */
        unsigned int    reserved                   : 26; /* [31..6] ������ */
    } bits;
    unsigned int    u32;
}HI_SIO_INTMASK_T;    /* �ж����μĴ����� */

typedef union
{
    struct
    {
        unsigned int    rx_data                    : 32; /* [31..0] ���յ������ݡ� */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_DUAL_RX_CHN_T;    /* ��ȡ�������ݼĴ�����I2S��������������ַ�ϲ�ʹ�ܺ󣬶�ȡ�������ݡ� */

typedef union
{
    struct
    {
        unsigned int    tx_data                    : 32; /* [31..0] ���͵����ݡ� */
    } bits;
    unsigned int    u32;
}HI_SIO_I2S_DUAL_TX_CHN_T;    /* д�������ݼĴ�����I2S��������������ַ�ϲ�ʹ�ܺ�д�������ݡ� */


/********************************************************************************/
/*    sio ��������Ŀ��_ģ����_�Ĵ�����_��Ա��_set)        */
/********************************************************************************/
HI_SET_GET(hi_sio_version_vesion,vesion,HI_SIO_VERSION_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_VERSION_OFFSET)
HI_SET_GET(hi_sio_version_sio_loop,sio_loop,HI_SIO_VERSION_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_VERSION_OFFSET)
HI_SET_GET(hi_sio_version_reserved,reserved,HI_SIO_VERSION_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_VERSION_OFFSET)
HI_SET_GET(hi_sio_mode_sio_mode,sio_mode,HI_SIO_MODE_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_MODE_OFFSET)
HI_SET_GET(hi_sio_mode_pcm_mode,pcm_mode,HI_SIO_MODE_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_MODE_OFFSET)
HI_SET_GET(hi_sio_mode_reserved_1,reserved_1,HI_SIO_MODE_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_MODE_OFFSET)
HI_SET_GET(hi_sio_mode_ext_rec_en,ext_rec_en,HI_SIO_MODE_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_MODE_OFFSET)
HI_SET_GET(hi_sio_mode_chn_num,chn_num,HI_SIO_MODE_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_MODE_OFFSET)
HI_SET_GET(hi_sio_mode_clk_edge,clk_edge,HI_SIO_MODE_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_MODE_OFFSET)
HI_SET_GET(hi_sio_mode_reserved_0,reserved_0,HI_SIO_MODE_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_MODE_OFFSET)
HI_SET_GET(hi_sio_intstatus_rx_intr,rx_intr,HI_SIO_INTSTATUS_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTSTATUS_OFFSET)
HI_SET_GET(hi_sio_intstatus_tx_intr,tx_intr,HI_SIO_INTSTATUS_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTSTATUS_OFFSET)
HI_SET_GET(hi_sio_intstatus_rx_right_fifo_over,rx_right_fifo_over,HI_SIO_INTSTATUS_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTSTATUS_OFFSET)
HI_SET_GET(hi_sio_intstatus_rx_left_fifo_over,rx_left_fifo_over,HI_SIO_INTSTATUS_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTSTATUS_OFFSET)
HI_SET_GET(hi_sio_intstatus_tx_right_fifo_under,tx_right_fifo_under,HI_SIO_INTSTATUS_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTSTATUS_OFFSET)
HI_SET_GET(hi_sio_intstatus_tx_left_fifo_under,tx_left_fifo_under,HI_SIO_INTSTATUS_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTSTATUS_OFFSET)
HI_SET_GET(hi_sio_intstatus_reserved,reserved,HI_SIO_INTSTATUS_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTSTATUS_OFFSET)
HI_SET_GET(hi_sio_intclr_rx_intr,rx_intr,HI_SIO_INTCLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTCLR_OFFSET)
HI_SET_GET(hi_sio_intclr_tx_intr,tx_intr,HI_SIO_INTCLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTCLR_OFFSET)
HI_SET_GET(hi_sio_intclr_rx_right_fifo_over,rx_right_fifo_over,HI_SIO_INTCLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTCLR_OFFSET)
HI_SET_GET(hi_sio_intclr_rx_left_fifo_over,rx_left_fifo_over,HI_SIO_INTCLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTCLR_OFFSET)
HI_SET_GET(hi_sio_intclr_tx_right_fifo_under,tx_right_fifo_under,HI_SIO_INTCLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTCLR_OFFSET)
HI_SET_GET(hi_sio_intclr_tx_left_fifo_under,tx_left_fifo_under,HI_SIO_INTCLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTCLR_OFFSET)
HI_SET_GET(hi_sio_intclr_reserved,reserved,HI_SIO_INTCLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTCLR_OFFSET)
HI_SET_GET(hi_sio_i2s_left_xd_tx_left_data,tx_left_data,HI_SIO_I2S_LEFT_XD_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_I2S_LEFT_XD_OFFSET)
HI_SET_GET(hi_sio_i2s_right_xd_tx_right_data,tx_right_data,HI_SIO_I2S_RIGHT_XD_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_I2S_RIGHT_XD_OFFSET)
HI_SET_GET(hi_sio_pcm_xd_tx_data,tx_data,HI_SIO_PCM_XD_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_PCM_XD_OFFSET)
HI_SET_GET(hi_sio_pcm_xd_reserved,reserved,HI_SIO_PCM_XD_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_PCM_XD_OFFSET)
HI_SET_GET(hi_sio_i2s_left_rd_rx_left_data,rx_left_data,HI_SIO_I2S_LEFT_RD_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_I2S_LEFT_RD_OFFSET)
HI_SET_GET(hi_sio_i2s_right_rd_rx_right_data,rx_right_data,HI_SIO_I2S_RIGHT_RD_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_I2S_RIGHT_RD_OFFSET)
HI_SET_GET(hi_sio_pcm_rd_rx__data,rx__data,HI_SIO_PCM_RD_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_PCM_RD_OFFSET)
HI_SET_GET(hi_sio_pcm_rd_reserved,reserved,HI_SIO_PCM_RD_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_PCM_RD_OFFSET)
HI_SET_GET(hi_sio_ct_set_tx_fifo_threshold,tx_fifo_threshold,HI_SIO_CT_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_SET_OFFSET)
HI_SET_GET(hi_sio_ct_set_rx_fifo_threshold,rx_fifo_threshold,HI_SIO_CT_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_SET_OFFSET)
HI_SET_GET(hi_sio_ct_set_tx_data_merge_en,tx_data_merge_en,HI_SIO_CT_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_SET_OFFSET)
HI_SET_GET(hi_sio_ct_set_rx_data_merge_en,rx_data_merge_en,HI_SIO_CT_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_SET_OFFSET)
HI_SET_GET(hi_sio_ct_set_tx_fifo_disable,tx_fifo_disable,HI_SIO_CT_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_SET_OFFSET)
HI_SET_GET(hi_sio_ct_set_rx_fifo_disable,rx_fifo_disable,HI_SIO_CT_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_SET_OFFSET)
HI_SET_GET(hi_sio_ct_set_tx_enable,tx_enable,HI_SIO_CT_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_SET_OFFSET)
HI_SET_GET(hi_sio_ct_set_rx_enable,rx_enable,HI_SIO_CT_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_SET_OFFSET)
HI_SET_GET(hi_sio_ct_set_intr_en,intr_en,HI_SIO_CT_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_SET_OFFSET)
HI_SET_GET(hi_sio_ct_set_rst_n,rst_n,HI_SIO_CT_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_SET_OFFSET)
HI_SET_GET(hi_sio_ct_set_reserved,reserved,HI_SIO_CT_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_SET_OFFSET)
HI_SET_GET(hi_sio_ct_clr_tx_fifo_threshold,tx_fifo_threshold,HI_SIO_CT_CLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_CLR_OFFSET)
HI_SET_GET(hi_sio_ct_clr_rx_fifo_threshold,rx_fifo_threshold,HI_SIO_CT_CLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_CLR_OFFSET)
HI_SET_GET(hi_sio_ct_clr_tx_data_merge_en,tx_data_merge_en,HI_SIO_CT_CLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_CLR_OFFSET)
HI_SET_GET(hi_sio_ct_clr_rx_data_merge_en,rx_data_merge_en,HI_SIO_CT_CLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_CLR_OFFSET)
HI_SET_GET(hi_sio_ct_clr_tx_fifo_disable,tx_fifo_disable,HI_SIO_CT_CLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_CLR_OFFSET)
HI_SET_GET(hi_sio_ct_clr_rx_fifo_disable,rx_fifo_disable,HI_SIO_CT_CLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_CLR_OFFSET)
HI_SET_GET(hi_sio_ct_clr_tx_enable,tx_enable,HI_SIO_CT_CLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_CLR_OFFSET)
HI_SET_GET(hi_sio_ct_clr_rx_enable,rx_enable,HI_SIO_CT_CLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_CLR_OFFSET)
HI_SET_GET(hi_sio_ct_clr_intr_en,intr_en,HI_SIO_CT_CLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_CLR_OFFSET)
HI_SET_GET(hi_sio_ct_clr_rst_n,rst_n,HI_SIO_CT_CLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_CLR_OFFSET)
HI_SET_GET(hi_sio_ct_clr_reserved,reserved,HI_SIO_CT_CLR_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_CT_CLR_OFFSET)
HI_SET_GET(hi_sio_rx_sta_rx_right_depth,rx_right_depth,HI_SIO_RX_STA_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_RX_STA_OFFSET)
HI_SET_GET(hi_sio_rx_sta_rx_left_depth,rx_left_depth,HI_SIO_RX_STA_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_RX_STA_OFFSET)
HI_SET_GET(hi_sio_rx_sta_reserved,reserved,HI_SIO_RX_STA_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_RX_STA_OFFSET)
HI_SET_GET(hi_sio_tx_sta_tx_right_depth,tx_right_depth,HI_SIO_TX_STA_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_TX_STA_OFFSET)
HI_SET_GET(hi_sio_tx_sta_tx_left_depth,tx_left_depth,HI_SIO_TX_STA_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_TX_STA_OFFSET)
HI_SET_GET(hi_sio_tx_sta_reserved,reserved,HI_SIO_TX_STA_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_TX_STA_OFFSET)
HI_SET_GET(hi_sio_data_width_set_tx_mode,tx_mode,HI_SIO_DATA_WIDTH_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_DATA_WIDTH_SET_OFFSET)
HI_SET_GET(hi_sio_data_width_set_rx_mode,rx_mode,HI_SIO_DATA_WIDTH_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_DATA_WIDTH_SET_OFFSET)
HI_SET_GET(hi_sio_data_width_set_reserved,reserved,HI_SIO_DATA_WIDTH_SET_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_DATA_WIDTH_SET_OFFSET)
HI_SET_GET(hi_sio_i2s_start_pos_start_pos_read,start_pos_read,HI_SIO_I2S_START_POS_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_I2S_START_POS_OFFSET)
HI_SET_GET(hi_sio_i2s_start_pos_start_pos_write,start_pos_write,HI_SIO_I2S_START_POS_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_I2S_START_POS_OFFSET)
HI_SET_GET(hi_sio_i2s_start_pos_reserved,reserved,HI_SIO_I2S_START_POS_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_I2S_START_POS_OFFSET)
HI_SET_GET(hi_i2s_pos_flag_start_pos_read,start_pos_read,HI_I2S_POS_FLAG_T,HI_LTESIO_REGBASE_ADDR, HI_I2S_POS_FLAG_OFFSET)
HI_SET_GET(hi_i2s_pos_flag_start_pos_write,start_pos_write,HI_I2S_POS_FLAG_T,HI_LTESIO_REGBASE_ADDR, HI_I2S_POS_FLAG_OFFSET)
HI_SET_GET(hi_i2s_pos_flag_reserved,reserved,HI_I2S_POS_FLAG_T,HI_LTESIO_REGBASE_ADDR, HI_I2S_POS_FLAG_OFFSET)
HI_SET_GET(hi_sio_signed_ext_signed_ext_en,signed_ext_en,HI_SIO_SIGNED_EXT_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_SIGNED_EXT_OFFSET)
HI_SET_GET(hi_sio_signed_ext_reserved,reserved,HI_SIO_SIGNED_EXT_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_SIGNED_EXT_OFFSET)
HI_SET_GET(hi_sio_i2s_pos_merge_en_merge_en,merge_en,HI_SIO_I2S_POS_MERGE_EN_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_I2S_POS_MERGE_EN_OFFSET)
HI_SET_GET(hi_sio_i2s_pos_merge_en_reserved,reserved,HI_SIO_I2S_POS_MERGE_EN_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_I2S_POS_MERGE_EN_OFFSET)
HI_SET_GET(hi_sio_intmask_rx_intr,rx_intr,HI_SIO_INTMASK_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTMASK_OFFSET)
HI_SET_GET(hi_sio_intmask_tx_intr,tx_intr,HI_SIO_INTMASK_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTMASK_OFFSET)
HI_SET_GET(hi_sio_intmask_rx_right_fifo_over,rx_right_fifo_over,HI_SIO_INTMASK_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTMASK_OFFSET)
HI_SET_GET(hi_sio_intmask_rx_left_fifo_over,rx_left_fifo_over,HI_SIO_INTMASK_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTMASK_OFFSET)
HI_SET_GET(hi_sio_intmask_tx_right_fifo_under,tx_right_fifo_under,HI_SIO_INTMASK_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTMASK_OFFSET)
HI_SET_GET(hi_sio_intmask_tx_left_fifo_under,tx_left_fifo_under,HI_SIO_INTMASK_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTMASK_OFFSET)
HI_SET_GET(hi_sio_intmask_reserved,reserved,HI_SIO_INTMASK_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_INTMASK_OFFSET)
HI_SET_GET(hi_sio_i2s_dual_rx_chn_rx_data,rx_data,HI_SIO_I2S_DUAL_RX_CHN_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_I2S_DUAL_RX_CHN_OFFSET)
HI_SET_GET(hi_sio_i2s_dual_tx_chn_tx_data,tx_data,HI_SIO_I2S_DUAL_TX_CHN_T,HI_LTESIO_REGBASE_ADDR, HI_SIO_I2S_DUAL_TX_CHN_OFFSET)

#endif

#endif // __HI_SIO_H__

