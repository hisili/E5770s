#ifndef __DRV_TEMP_CFG_H__
#define __DRV_TEMP_CFG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <hi_temperature.h>
#include <drv_temperature.h>

#define TSENS_REGION_MAX 3

struct drv_hkadc_map
{
    unsigned int logic_chan;
    unsigned int phy_chan;
    unsigned int nv_id;
    unsigned int nv_len;
    unsigned int modem_id;
    char * name;
};
/* �¶�������ṹ */
typedef struct hkadc_chan_out
{
    unsigned short volt_l;    /* ���ص�HKADC��ѹֵ */
    unsigned short volt_r;    /* ���ص�HKADC��ѹֵȡ�� */
    short          temp_l;    /* ���ص��¶�ֵ */
    short          temp_r;    /* ���ص��¶�ֵȡ�� */
} DRV_CHANNEL_OUTPUT;

/* �¶ȵ�ѹ��Ӧ��ṹ */
typedef struct hkadc_tem_value
{
    short          temp;    /* �¶ȵ� */
    unsigned short volt;    /* ��ѹ�� */
} TEM_VOLT_TABLE;

/* �������bit�ṹ */
typedef struct hkadc_out_config
{
   unsigned int out_prop:2; 
   unsigned int out_wake:1;
   unsigned int out_vol_temp:1;
   unsigned int out_reserv1:4;
   unsigned int out_acore:1;
   unsigned int out_ccore:1;
   unsigned int out_reserv2:22;
} OUT_PROP_CONFIG;

/* �¶��������ṹ */
typedef struct hkadc_chan_config
{
    union 
    {
        unsigned int out_config;    /* bit0-bit1: 0:����� 1:������� 2:ѭ����� */
                                    /* bit2: 1:������� 0:�ǻ������ */
                                    /* bit3: 0:ֻ�����ѹ 1:��ѹ�¶Ⱦ���� */
                                    /* bit8: A����� */
                                    /* bit9: C����� */
        struct hkadc_out_config bit_out_config;
    } outcfg;

    unsigned int have_config;    
    unsigned short out_peroid;      /* ѭ�����ʱ��ѭ�����ڣ���λ:�� */
    unsigned short temp_data_len;   /* �¶�ת������ */
    struct hkadc_tem_value temp_table[32]; /* �¶�ת����ʵ�ʳ��Ȳμ�temp_data_len */
} DRV_CHANNEL_CONFIG;

/* ϵͳ�ŵ��¶ȱ������ýṹ */
typedef struct sys_temp_cfg
{
    unsigned short enable;        /* bit0:���±���ʹ�� bit1:���±���ʹ�� 1 ʹ�� 0 �ر�*/
    unsigned short hkadc_id;      /* ϵͳ�ŵ��¶ȱ�����hkadcͨ��ID */
    short          high_thres;    /* ϵͳ�ŵ���±����ĵ�ѹ��ֵ ���¶�Խ�ߣ���ѹԽ��*/
    unsigned short high_count;    /* ϵͳ�ŵ���±����������ޣ����˺�ϵͳ�ػ� */
    short          low_thres;     /* ϵͳ�ŵ���±����ĵ�ѹ��ֵ ���¶�Խ�ͣ���ѹԽ��*/
    unsigned short low_count;     /* ϵͳ�ŵ���±����������ޣ����˺�ϵͳ�ػ� */

    unsigned int   reserved[2];   /*����*/
} DRV_SYS_TEMP_PRO;

/* TSENEOR�¶ȱ������ýṹ */
typedef struct tsens_region_cfg
{
    unsigned short enable;         /* bit0:���±���ʹ�� bit1:���±���ʹ�� 1 ʹ�� 0 �ر�*/
    unsigned short high_thres;     /* ϵͳ�ŵ���±���*/
    unsigned short high_count;     /* ϵͳ�ŵ���±����������ޣ�ϵͳ�ػ� */
    unsigned short reserved;
    /*unsigned short low_thres;*/     /* ϵͳ�ŵ���±���*/
    /*unsigned short low_count;*/     /* ϵͳ�ŵ���±����������ޣ�ϵͳ�ػ� */
} TSENS_REGION_CFG;

typedef struct tsens_region_config
{
    short temp[256];

}TSENS_REGION_CONFIG;

/* �����¶������ݽṹ */
typedef struct thermal_data_area
{
    unsigned long               magic_start;                 /* ������ʼMagic Code 0x5A5A5A5A*/
    struct hkadc_chan_out       chan_out[HKADC_CHAN_MAX];    /* ��ͨ���������*/
    struct hkadc_chan_config    chan_cfg[HKADC_CHAN_MAX];    /* ��ͨ���������� */
    struct sys_temp_cfg         sys_temp_cfg;                /* ϵͳ�ŵ��±����� */
    unsigned long               hw_ver_id;                   /* �汾ID */
    unsigned short              phy_tbl[HKADC_CHAN_MAX];     /* HKADC����ͨ�����߼�ͨ����Ӧ�� */
    unsigned long               debug_flag;                  /* ���⿪�� */
    struct tsens_region_cfg     tens_cfg[TSENS_REGION_MAX];  /* TSENSOR�±����� */
    struct tsens_region_config  region_cfg;                  /* TSENSOR�������������Ϣ*/
    short                       tsens_out[TSENS_REGION_MAX]; /* TSENSOR������������Ϣ*/
    short                       reserved;                    /* ������Ϣ*/
    unsigned long               magic_end;                   /* ��������Magic Code 0x5A5A5A5A*/
} DRV_HKADC_DATA_AREA;

#ifdef __cplusplus
}
#endif

#endif

