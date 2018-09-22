/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       :   drv_nv_def.h
  Description     :   DRV�����NV �ṹ�嶨��
  History         :
******************************************************************************/


#ifndef __DRV_NV_DEF_H__
#define __DRV_NV_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




#include "drv_comm.h"

#define LDO_GPIO_MAX 2


/*******************************************************************/

/*****************************************************************************
 �ṹ��    : nv_protocol_base_type
 �ṹ˵��  : nv_protocol_base_type�ṹ ID= en_NV_Item_Modem_Log_Path 148
 			MBB��̬ modem log·��������������������̬��modem log·����
*****************************************************************************/
typedef struct
{
   BSP_CHAR_TL  ucModemLogPath[32];
   BSP_CHAR_TL  modemLogRsv[4];
}NV_MODEM_LOG_PATH;



/*NV ID = 0xd109*/
/*ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر�*/
typedef struct
{
	BSP_S32 buck2_switch;    /*[0, 1]*/
}NV_PASTAR_BUCK2_SWITCH_STRU;
/*end NV ID = 0xd109*/

/*NV ID  = 0xd10b*/

typedef struct ST_PWC_SWITCH_STRU_S {

	/*����NV���ڵ͹��ĵ�������ƣ�������ЩBIT��ʱδ�ã�������ʱ�������Ϊ׼ȷ������*/
 	BSP_U32 deepsleep  :1; /*bit0*/
    BSP_U32 lightsleep :1; /*bit1*/
    BSP_U32 dfs        :1; /*bit2*/
    BSP_U32 hifi       :1; /*bit3*/
    BSP_U32 drxAbb     :1; /*bit4*/
    BSP_U32 drxZspCore :1; /*bit5*/
    BSP_U32 drxZspPll  :1; /*bit6*/
    BSP_U32 drxWLBbpPll  :1; /*bit7*/
    BSP_U32 drxGBbpPll   :1; /*bit8*/
    BSP_U32 drxRf      :1; /*bit9*/
    BSP_U32 drxPa      :1; /*bit10*/
    BSP_U32 drxGuBbpPd   :1; /*bit11*/
    BSP_U32 drxDspPd     :1; /*bit12*/
    BSP_U32 drxLBbpPd    :1; /*bit13*/
    BSP_U32 drxPmuEco    :1; /*bit14*/
    BSP_U32 drxPeriPd    :1; /*bit15*/
    BSP_U32 l2cache_mntn  :1; /*bit16*/
    BSP_U32 bugChk     :1; /*bit17*/
    BSP_U32 pmuSwitch     :1; /*bit18*/
    BSP_U32 drxLdsp      :1;  /*bit 19*/
    BSP_U32 matserTDSpd  :1; /*bit20*/
    BSP_U32 tdsClk    :1;  /*bit21*/
    BSP_U32 slaveTDSpd   :1; /*bit22*/
    BSP_U32 slow	     :1;/*bit23*/
    BSP_U32 reserved    :8; /*bit24-31*/

	/*����NV����DEBUG���µ�Ϳ�����*/
	BSP_U32 drx_pa0_pd       :1; /*bit0 ���ڿ���PA0�����µ�*/
    BSP_U32 drx_pa1_pd       :1; /*bit1 ���ڿ���PA1�����µ�*/
    BSP_U32 drx_rfic0_pd     :1; /*bit2 ���ڿ���RFIC0�����µ�*/
    BSP_U32 drx_rfic1_pd     :1; /*bit3 ���ڿ���RFIC1�����µ�*/
    BSP_U32 drx_irm_pd       :1; /*bit4 ���ڿ���BBP_IRM�����µ�*/
    BSP_U32 drx_bbe16_pd     :1; /*bit5 ���ڿ���BBE16�����µ�*/
    BSP_U32 drx_abb_pd       :1; /*bit6 ���ڿ���ABB�����µ�*/
    BSP_U32 drx_g1bbp_pd     :1; /*bit7 ���ڿ���G1_BBP�����µ�*/
    BSP_U32 drx_g2bbp_pd     :1; /*bit8 ���ڿ���G2_BBP�����µ�*/
    BSP_U32 drx_wbbp_pd      :1; /*bit9 ���ڿ���WBBP�����µ�*/
    BSP_U32 drx_bbpcommon_pd :1; /*bit10 ���ڿ���BBP_COMMON�����µ�*/
    BSP_U32 drx_twbbp_pd     :1; /*bit11 ���ڿ���TWBBP�����µ�*/
    BSP_U32 drx_bbe16_pll    :1; /*bit12 ���ڿ���BBE16_PLL�Ŀ�����*/
    BSP_U32 drx_bbp_pll      :1; /*bit13 ���ڿ���BBP_PLL�Ŀ�����*/
    BSP_U32 drx_abb0_wpll    :1; /*bit14 ���ڿ���ABB_CH0_WPLL�Ŀ�����*/
    BSP_U32 drx_abb0_gpll    :1; /*bit15 ���ڿ���ABB_CH0_GPLL�Ŀ�����*/
    BSP_U32 drx_abb1_wpll    :1; /*bit16 ���ڿ���ABB_CH1_WPLL�Ŀ�����*/
    BSP_U32 drx_abb1_gpll    :1; /*bit17 ���ڿ���ABB_CH1_GPLL�Ŀ�����*/
    BSP_U32 reserved2        :14; /*bit18-31 δ��*/
}ST_PWC_SWITCH_STRU;


/*NV ID = 0xd10c*/
typedef struct ST_PWC_DFS_STRU_S {
    BSP_U32 CcpuUpLimit;
	BSP_U32 CcpuDownLimit;
	BSP_U32 CcpuUpNum;
	BSP_U32 CcpuDownNum;
	BSP_U32 AcpuUpLimit;
	BSP_U32 AcpuDownLimit;
	BSP_U32 AcpuUpNum;
	BSP_U32 AcpuDownNum;
	BSP_U32 DFSTimerLen;
	BSP_U32 DFSHifiLoad;
 	BSP_U32 Strategy;/*ʹ�ú��ֲ���bit0:1->200ms���ؼ��,bit0:0->4s���ؼ��;bit1:1/0��/�رո���DDR��Ƶ*/
 	BSP_U32 DFSDdrUpLimit;
 	BSP_U32 DFSDdrDownLimit;
 	BSP_U32 DFSDdrprofile;
 	BSP_U32 reserved;
}ST_PWC_DFS_STRU;

/*NV ID = 0xd10f begin������PMU�����쳣ʱ�Ĵ�������*/
typedef struct
{
    BSP_U8  VoltId;         /*��Ҫ�������õĵ�ѹԴ��id��*/
    BSP_U8  VoltOcpIsOff;   /*���õ�ѹԴ�����Ļ��Ƿ�رո�·��ѹԴ*/
    BSP_U8  VoltOcpIsRst;   /*���õ�ѹԴ�����Ļ��Ƿ�����ϵͳ*/
    BSP_U8  VoltOtpIsOff;   /*��PMU������Ҫ�رշǺ��ĵ�Դ�Ļ����Ƿ��ܹرո�·��ѹԴ*/
} PMU_VOLT_PRO_STRU;
typedef struct
{
    BSP_U8    ulOcpIsOn;        /*�����ĵ�Դ�ܷ����´�:0:���ܱ����´򿪣�1:�ܱ����´򿪣�Ĭ��Ϊ���ܴ�--0*/
    BSP_U8    ulOcpIsOff;       /*�����ĵ�Դ�Ƿ�ر�:0:���رգ�1:�رգ�Ĭ��Ϊ�ر�--1*/
    BSP_U8    ulOtpCurIsOff;    /*����(�����¶�Ԥ��ֵ)ʱ�Ƿ�رշǺ��ĵ�Դ:0:���رշǺ��ģ�1:�رշǺ��ĵ�Դ��Ĭ��Ϊ�رշǺ��ĵ�Դ--1*/
    BSP_U8    ulOtpIsRst;       /*����(�����¶�Ԥ��ֵ)ʱ�Ƿ�����ϵͳ:0:��������1:����ϵͳ��Ĭ��Ϊ������ϵͳ--0*/

    BSP_U8    ulOtpIsOff;       /*PMUоƬ���³���150��ʱPMU�Ƿ��µ�(����ʱ������):0:PMU���µ磬1:PMU�µ硣Ĭ��ΪPMU�µ�--1*/
    BSP_U8    ulUvpIsRst;       /*ǷѹԤ��ʱ�Ƿ�����ϵͳ��Ĭ��Ϊ0:������*/
    BSP_U16   reserved2;

    BSP_U16   ulOtpLimit;       /*�¶�Ԥ����ֵ����:105:105�棬115:115�棬125:125�� ��135:135�� (HI6559����֧��135)��Ĭ��Ϊ125��--125 */
    BSP_U16   ulUvpLimit;       /*ǷѹԤ����ֵ���ã���λmv:3000:3v; 2700:2.7v(2850:2.85v.HI6559֧��2.85,HI6551֧��2.7) ��Ĭ��Ϊ3v--3000*/

    PMU_VOLT_PRO_STRU VoltProConfig[50];/*ÿ·��ѹԴ���쳣�����������ã���ͬ��Ʒ��̬��Ҫ�������õĵ�ѹԴ����*/
} PMU_EXC_PRO_NV_STRU;

/*NV ID = 0xd10f end*/

/*ID=0xd110*/
typedef struct
{
    BSP_U32    u32CalcTime;        /* ����ʱ������(10ms) */
    BSP_U32    u32PktNum;          /* �ۼư����� */
    BSP_U32    u32SwichFlag;       /* netif���������俪�� */
} NETIF_INIT_PARM_T;

/*ID=0xd111 begin */
typedef struct
{
    BSP_U32 dump_switch    : 2; /* 00: excdump, 01: usbdump, 1x: no dump */
    BSP_U32 ARMexc         : 1; /* 2 ARM�쳣��⿪��*/
    BSP_U32 stackFlow      : 1; /* 3 ��ջ�����⿪��*/
    BSP_U32 taskSwitch     : 1; /* 4 �����л���¼����*/
    BSP_U32 intSwitch      : 1; /* 5 �жϼ�¼����*/
    BSP_U32 intLock        : 1; /* 6 ���жϼ�¼����*/
    BSP_U32 appRegSave1    : 1; /* 7 �Ĵ�����1��¼���� */
    BSP_U32 appRegSave2    : 1; /* 8 �Ĵ�����2��¼����*/
    BSP_U32 appRegSave3    : 1; /* 9 �Ĵ�����3��¼����*/
    BSP_U32 commRegSave1   : 1; /* 10 �Ĵ�����1��¼���� */
    BSP_U32 commRegSave2   : 1; /* 11 �Ĵ�����2��¼����*/
    BSP_U32 commRegSave3   : 1; /* 12 �Ĵ�����3��¼����*/
    BSP_U32 sysErrReboot   : 1; /* 13 systemError��λ����*/
    BSP_U32 reset_log      : 1; /* 14 ǿ�Ƽ�¼���أ���δʹ��*/
    BSP_U32 fetal_err      : 1; /* 15 ǿ�Ƽ�¼���أ���δʹ��*/
	BSP_U32 log_ctrl       : 2; /* bsp_trsce �������*/
    BSP_U32 reserved1      : 14;
} DUMP_CFG_STRU;

typedef struct
{
    union
    {
        BSP_U32         uintValue;
        DUMP_CFG_STRU   cfg;
    } dumpCfg;

    BSP_U32 appRegAddr1;	/* ACORE����Ĵ������ַ1*/
    BSP_U32 appRegSize1;	/* ACORE����Ĵ����鳤��1*/
    BSP_U32 appRegAddr2;	/* ACORE����Ĵ������ַ2*/
    BSP_U32 appRegSize2;	/* ACORE����Ĵ����鳤��2*/
    BSP_U32 appRegAddr3;	/* ACORE����Ĵ������ַ3*/
    BSP_U32 appRegSize3;	/* ACORE����Ĵ����鳤��3*/

    BSP_U32 commRegAddr1;	/* CCORE����Ĵ������ַ1*/
    BSP_U32 commRegSize1;	/* CCORE����Ĵ����鳤��1*/
    BSP_U32 commRegAddr2;	/* CCORE����Ĵ������ַ2*/
    BSP_U32 commRegSize2;	/* CCORE����Ĵ����鳤��2*/
    BSP_U32 commRegAddr3;	/* CCORE����Ĵ������ַ3*/
    BSP_U32 commRegSize3;	/* CCORE����Ĵ����鳤��3*/

    BSP_U32 traceOnstartFlag;           /* 0:��������Trace, ��0:����������Trace */
    BSP_U32 traceCoreSet;               /* 0:�ɼ�A��Trace, 1:�ɼ�C��Trace, 2:�ɼ�˫��Trace */
    BSP_U32 BusErrorFlagSet;             /* 0:���������������߹�������, ��0:�������������߹������� */
} NV_DUMP_STRU;
/*ID=0xd111 end */

/*NV ID = 0xd114 begin,����PMU��ʼ��ʱӦ�������ʵ�ֵĻ�������*/
#define NUM_OF_PMU_NV  50
typedef struct
{
    BSP_U8  VoltId;     /*��Դid��*/
    BSP_U8  IsNeedSet;  /*�Ƿ���Ҫ�������:0:����Ҫ��1:��Ҫ*/
    BSP_U8  IsOnSet;    /*Ĭ���Ƿ���Ҫ������ѹԴ:0:����Ҫ��1:��Ҫ*/
    BSP_U8  IsOffSet;   /*Ĭ���Ƿ���Ҫ�رյ�ѹԴ:0:����Ҫ��1:��Ҫ*/

    BSP_U8  IsVoltSet;  /*�Ƿ���Ҫ���õ�ѹ:0:����Ҫ��1:��Ҫ*/
    BSP_U8  IsEcoSet;   /*�Ƿ���Ҫ����ECOģʽ:0:����Ҫ��1:��Ҫ*/
    BSP_U8  EcoMod;     /*��Ҫ���õ�ecoģʽ:0:normal;2:force_eco;3:follow_eco*/
    BSP_U8  reserved3;  /*Ĭ��*/

    BSP_U32 Voltage;    /*��Ҫ���õ�Ĭ�ϵ�ѹ*/
} PMU_INIT_CON_STRU;
typedef struct
{
    PMU_INIT_CON_STRU InitConfig[NUM_OF_PMU_NV];
} PMU_INIT_NV_STRU;
/*NV ID = 0xd114 end*/

/*NV ID = 0xd115 start*/

typedef struct {
    BSP_U32	index;           /*Ӳ���汾����ֵ(��汾��1+��汾��2)�����ֲ�ͬ��Ʒ*/
    BSP_U32	hwIdSub;        /*Ӳ���Ӱ汾�ţ����ֲ�Ʒ�Ĳ�ͬ�İ汾*/
	BSP_CHAR_TL  name[32];           /*�ڲ���Ʒ��*/
    BSP_CHAR_TL	namePlus[32];       /*�ڲ���Ʒ��PLUS*/
    BSP_CHAR_TL	hwVer[32];          /*Ӳ���汾����*/
    BSP_CHAR_TL	dloadId[32];        /*������ʹ�õ�����*/
    BSP_CHAR_TL	productId[32];      /*�ⲿ��Ʒ��*/
}PRODUCT_INFO_NV_STRU;

/*NV ID =0xd115 end*/

/*NV ID =0xd116 start,mipi0_chn*/
typedef struct{
	BSP_U32 mipi_chn;
}MIPI0_CHN_STRU;
/*NV ID =0xd116 end,mipi0_chn*/

/*NV ID =0xd117 start,mipi1_chn*/
typedef struct{
	BSP_U32 mipi_chn;
}MIPI1_CHN_STRU;
/*NV ID =0xd117 end,mipi1_chn*/

/*NV ID =0xd12e start, rf power control, pastar config*/
typedef struct{
	BSP_U32 rfpower_m0;/*[0, 1,2]*//*modem0,����ͨ��0�Ĺ��絥Ԫ,valueΪ0��ʾ���򿪵�Դ��Ϊ1��ʾΪpastar���磬Ϊ2��ʾLDO����*/
	BSP_U32 rfpower_m1;/*[0, 1,2]*//*modem1,����ͨ��1�Ĺ��絥Ԫ,valueΪ0��ʾ���򿪵�Դ��Ϊ1��ʾΪpastar���磬Ϊ2��ʾLDO����*/
}NV_RFPOWER_UNIT_STRU;
/*NV ID =0xd12e start, pastar config*/

/* NV ID =0xd13A start, pa power control, pastar config */
typedef struct{
	BSP_U32 papower_m0;/*[0,1,2]*//*modem0,����ͨ��0�Ĺ��絥Ԫ,valueΪ0��ʾ���򿪵�Դ��Ϊ1��ʾΪpastar���磬Ϊ2��ʾ��ع���*/
	BSP_U32 papower_m1;/*[0,1,2]*//*modem1,����ͨ��1�Ĺ��絥Ԫ,valueΪ0��ʾ���򿪵�Դ��Ϊ1��ʾΪpastar���磬Ϊ2��ʾ��ع���*/
}NV_PAPOWER_UNIT_STRU;
/* NV ID =0xd13A start, pastar config */

typedef struct
{
    BSP_U32   nvSysTimeValue;   /* ��õ���ϵͳ����ʱ�� */
}SYS_TIME;

typedef struct
{
    BSP_U32  ulIsEnable;				/*�¶ȱ���ʹ��*/
    BSP_U32    lCloseAdcThreshold;
    BSP_U32  ulTempOverCount;
}CHG_BATTERY_HIGH_TEMP_PROT_NV;

typedef struct
{
    BSP_U32  ulIsEnable;			/*�¶ȱ���ʹ��*/
    BSP_U32    lCloseAdcThreshold;
    BSP_U32  ulTempLowCount;
}CHG_BATTERY_LOW_TEMP_PROTE_NV;

/* ����ģʽnv��,0 : �ǹ���ģʽ 1: ����ģʽ**/
typedef struct
{
    BSP_U32 ulFactoryMode;
}FACTORY_MODE_TYPE;

/* �����������Դ��� */
typedef struct
{
    BSP_U32 ulTryTimes;
}BOOT_TRY_TIMES_STRU;

/* ������������ʱ�� */
typedef struct
{
    BSP_U32 ulPowKeyTime;
}POWER_KEY_TIME_STRU;

typedef struct
{
    BSP_U16 temperature;
    BSP_U16 voltage;
}CHG_TEMP_ADC_TYPE;

typedef struct
{
    CHG_TEMP_ADC_TYPE g_adc_batt_therm_map[31];
}NV_BATTERY_TEMP_ADC;


/*Ӳ��汾nv��,1 : Ӳ��汾 0: ��Ӳ��汾*/
typedef struct
{
    BSP_U32 ulHwVer;
}E5_HW_TEST_TYPE;

/*�Ƿ�֧��APT����nv��,1 : ֧�� 0: ��֧��*/
typedef struct
{
    BSP_U32 ulIsSupportApt;
}NV_SUPPORT_APT_TYPE;

/*PMU�쳣����nv��*/
typedef struct
{
    BSP_U8 TemppmuLimit;  /*PMU�¶���ֵ:0:105��;1:115��;2:125��;3:135��*/
	BSP_U8 ulCurIsOff;  /*����ʱ����Դ�Ƿ��µ磺0���µ磻1�����µ�*/
	BSP_U8 ulOcpIsRst;  /*����ʱ�Ƿ������λ: 0:����λ 1:��λ*/
	BSP_U8 PmuproIsOn;  /*PMU�쳣���������Ƿ�����0����������1������*/
}PMU_PRO_NV;

typedef struct
{
    BSP_U32 u32SciGcfStubFlag;   /* 1: GCF����ʹ�ܣ�0��GCF���Բ�ʹ�� */
}SCI_NV_GCF_STUB_FLAG;

/*���ٿ��ػ������Ƿ�ʹ��NV��*/
typedef struct
{
    BSP_U32 ulEnable;   /*���ٿ��ػ��Ƿ�ʹ�ܣ�0����ʹ�ܣ�1��ʹ��*/
}NV_SHORT_ONOFF_ENABLE_TYPE;

/*���ٿ��ػ�����������ϢNV��*/
typedef struct NV_SHORT_ONOFF_TYPE_S
{
    BSP_U32 ulPowerOffMaxTimes;   /*֧�ֵ����ٹػ�����*/
	BSP_U32 ulMaxTime;            /*�ٹػ���ʷ�ۼ�ʱ����ڵ��ڴ�ʱ���Զ���ػ�����λСʱ*/
	BSP_U32 ulVoltLevel1;         /*���ű�����һ����ѹ����*/
	BSP_U32 ulVoltLevel2;         /*���ű����ڶ�����ѹ����*/
	BSP_U32 ulRTCLevel1;          /*С�ڵ�һ����ѹ��Ӧ��RTC����ʱ��*/
	BSP_U32 ulRTCLevel2;          /*��һ���͵ڶ���֮���ѹ��Ӧ��RTC����ʱ��*/
	BSP_U32 ulRTCLevel3;          /*���ڵ��ڵڶ�����ѹ��Ӧ��RTC����ʱ��*/
}NV_SHORT_ONOFF_TYPE;

/*ʡ��ģʽ���ã���ʶ�������Ƿ�ʹ��NV��*/
typedef struct
{
        BSP_U32 ulLEDEnable;   /*������LED �Ƿ�ʹ�ܣ�0����ʹ�ܣ�1��ʹ��*/
        BSP_U32 ulReserved1;   /*����Ԥ��  �Ƿ�ʹ�ܣ�0����ʹ�ܣ�1��ʹ��*/
        BSP_U32 ulReserved2;   /*����Ԥ��  �Ƿ�ʹ�ܣ�0����ʹ�ܣ�1��ʹ��*/
}NV_POWER_SAVE_TYPE;

/*���ؼƵ�ѹ������У׼����*/
typedef struct
{
    BSP_U32 v_offset_a;         /* ��ѹУ׼���Բ��� */
    BSP_S32 v_offset_b;         /* ��ѹУ׼����ƫ��*/
    BSP_U32 c_offset_a;         /* ����У׼���Բ��� */
    BSP_S32 c_offset_b;         /* ����У׼����ƫ�� */
}COUL_CALI_NV_TYPE;

/*�¶ȱ���HKADC����ͨ�������� NV_ID_DRV_TEMP_HKADC_CONFIG            = 0xd120 */

typedef struct
{
    BSP_U32 out_config;         /* bit0-bit1 0:����� 1:������� 2:ѭ����� */
                                /* bit2 1:������� 0:�ǻ������ */
                                /* bit3: 0:ֻ�����ѹ 1:��ѹ�¶Ⱦ���� */
                                /* bit8: A����� */
                                /* bit9: C����� */
    BSP_U32 have_config;
    BSP_U16 out_period;         /* ѭ�����ʱ��ѭ�����ڣ���λ:�� */
    BSP_U16 convert_list_len;   /* �¶�ת������ */
    BSP_U16 convert_list_id;    /* �¶�ת����NV��־��ʵ�ʳ��Ȳμ�usTempDataLen */
    BSP_U16 reserved;
}TEMP_HKADC_CHAN_CONFIG;

typedef struct
{
    TEMP_HKADC_CHAN_CONFIG chan_config[16];

}TEMP_HKADC_CHAN_CONFIG_ARRAY;

/*�¶ȱ���HKADC����ͨ�������� NV_ID_DRV_TEMP_TSENS_CONFIG            = 0xd121 */
typedef struct
{
    BSP_U16 enable;         /* bit0:���±���ʹ�� bit1:���±���ʹ�� 1 ʹ�� 0 �ر�*/
    BSP_U16 high_thres;     /* оƬ���±����ĵ�ѹ��ֵ  */
    BSP_U16 high_count;     /* оƬ���±����������ޣ�ϵͳ�ػ� */
    BSP_U16 reserved;
    /*BSP_U32 low_thres;*/  /* оƬ���±����ĵ�ѹ��ֵ */
    /*BSP_U32 low_count;*/  /* оƬ���±����������ޣ�ϵͳ�ػ� */

}TEMP_TSENS_REGION_CONFIG;

typedef struct
{
    TEMP_TSENS_REGION_CONFIG region_config[3];

}TEMP_TSENS_REGION_CONFIG_ARRAY;



/*�¶ȱ�����ظߵ��±���  NV_ID_DRV_TEMP_BATTERY_CONFIG          = 0xd122 */
typedef struct
{
    BSP_U16 enable;        /* bit0:���±���ʹ�� bit1:���±���ʹ�� 1 ʹ�� 0 �ر�*/
    BSP_U16 hkadc_id;      /* ϵͳ�ŵ��¶ȱ�����hkadcͨ��ID */
    BSP_U16 high_thres;    /* ϵͳ�ŵ���±������¶ȷ�ֵ */
    BSP_U16 high_count;    /* ϵͳ�ŵ���±����������� */
    BSP_S16 low_thres;     /* ϵͳ�ŵ���±������¶ȷ�ֵ */
    BSP_U16 low_count;     /* ϵͳ�ŵ���±������� */

    BSP_U32 reserved[2];   /*����*/
} DRV_SYS_TEMP_STRU;

/*�¶ȱ��������߼�ת����  NV_ID_DRV_TEMP_CHAN_MAP          = 0xd126 */
typedef struct
{
    BSP_U16 chan_map[16];

}TEMP_HKADC_PHY_LOGIC_ARRAY;

/* WIN7 Feature for usb id:50075 */
typedef struct
{
    BSP_U8 wwan_flag;
    BSP_U8 reserved1;
    BSP_U8 reserved2;
    BSP_U8 reserved3;
    BSP_U8 reserved4;
    BSP_U8 reserved5;
    BSP_U8 reserved6;
    BSP_U8 reserved7;
} NV_WIN7_FEATURE;

typedef struct
{
    BSP_U32 sci_dsda_select;        /* 0: sim0, 1:sim1*/
} DRV_SCI_DSDA_SELECT;
/* SIM gcf test flage*/
typedef struct
{
    BSP_U32 sci_gcf_sub_flag;        /* 0: open, 1:close */
} DRV_SCI_GCF_STUB_FLAG;

/*E5���ڸ���*/
typedef struct
{
	BSP_U32 wait_usr_sele_uart : 1;//[bit 0-0]1: await user's command for a moment; 0: do not wait
	BSP_U32 a_core_uart_num    : 2;//[bit 1-2]the number of uart used by a core
	BSP_U32 c_core_uart_num    : 2;//[bit 3-4]the number of uart used by c core
	BSP_U32 m_core_uart_num    : 2;//[bit 5-6]the number of uart used by m core
	BSP_U32 a_shell            : 1;//[bit 7-7]0:ashell is not used; 1:ashell is used
	BSP_U32 c_shell            : 1;//[bit 8-8]0:cshell is not used; 1:cshell is used
	BSP_U32 uart_at            : 1;//[bit 9-9]uart at control
	BSP_U32 extendedbits       : 22;//[b00]1:open cshell_auart; 0:close
}DRV_UART_SHELL_FLAG;

/* product support module nv define */
typedef struct
{
	BSP_U32 sdcard 		: 1;//1: support; 0: not support
	BSP_U32 charge 		: 1;
	BSP_U32 wifi    	: 1;
	BSP_U32 oled    	: 1;
	BSP_U32 hifi        : 1;
	BSP_U32 onoff       : 1;
	BSP_U32 hsic        : 1;
	BSP_U32 localflash  : 1;
	BSP_U32 reserved    : 24;
} DRV_MODULE_SUPPORT_STRU;

typedef struct
{
	BSP_U8 normalwfi_flag;
	BSP_U8 deepsleep_flag;
	BSP_U8 buck3off_flag;
	BSP_U8 peridown_flag;
	BSP_U32 deepsleep_Tth;
	BSP_U32 TLbbp_Tth;
}DRV_NV_PM_TYPE;

/* NV_ID_DRV_TSENS_TABLE = 0xd129*/
typedef struct
{
    BSP_S16 temp[256];

}DRV_TSENS_TEMP_TABLE;

typedef struct
{
    BSP_U8 ucABBSwitch; /*��Ӧģʽʹ�õ�ABB����ͨ����0 ͨ��0, 1: ͨ��1, 2: ͬʱʹ������ͨ��*/
    BSP_U8 ucRFSwitch;  /*��Ӧģʽʹ�õ�RF����ͨ����0 ͨ��0, 1: ͨ��1, 2: ͬʱʹ������ͨ��*/
    BSP_U8 ucTCXOSwitch; /*��Ӧģʽʹ�õ�TCXO ID 0 TCXO0, 1: TCXO1*/
    BSP_U8 reserve;
}NV_TLMODE_BASIC_PARA_STRU;

typedef struct
{
    NV_TLMODE_BASIC_PARA_STRU stModeBasicParam[2];/*�±�Ϊ0:LTE, 1:TDS*/
}NV_TLMODE_CHAN_PARA_STRU;

typedef struct
{
    BSP_U32 clkdis1; /*��ʼ�ر�ʱ�ӼĴ�������Ӧcrg clk dis1*/
    BSP_U32 clkdis2; /*��ʼ�ر�ʱ�ӼĴ�������Ӧcrg clk dis2*/
    BSP_U32 clkdis3; /*��ʼ�ر�ʱ�ӼĴ�������Ӧcrg clk dis3*/
    BSP_U32 clkdis4;  /*��ʼ�ر�ʱ�ӼĴ�������Ӧcrg clk dis4*/
	BSP_U32 clkdis5;  /*��ʼ�ر�ʱ�ӼĴ�������Ӧcrg clk dis5*/
    BSP_U32 mtcmosdis; /*��ʼ�ر�MTCMOS�Ĵ�������Ӧcrg mtcmosdis*/
}DRV_NV_PM_CLKINIT_STRU;

typedef struct
{
    BSP_U32 ucBBPCh0TcxoSel:1; 	    /* bit 0,CH0 19.2Mʹ�õ�TCXOԴ��0 TCXO0, 1: TCXO1; ��Ӧ�Ĵ��� 0x90000148 */
    BSP_U32 ucBBPCh1TcxoSel:1;  	/* bit 1,CH1 19.2Mʹ�õ�TCXOԴ��0 TCXO0, 1: TCXO1; ��Ӧ�Ĵ��� 0x90000148 */
    BSP_U32 ucABBCh0TcxoSel:1; 		/* bit 2,ABB Ch0 ʹ�õ�TCXOԴ��0 TCXO0, 1: TCXO1; ��ӦABB�Ĵ��� 0x94 */
    BSP_U32 ucABBCh1TcxoSel:1; 		/* bit 3,ABB Ch1 ʹ�õ�TCXOԴ��0 TCXO0, 1: TCXO1; ��Ӧ�Ĵ��� 0x94 */
	BSP_U32 ucBbpPllTcxoSel:1; 		/* bit 4,BBP PLL ʹ�õ�TCXOԴ��0 TCXO0, 1: TCXO1;*/
	BSP_U32 ucG1bp104mTcxoSel:1; 	/* bit 5,G1BBP 104M ʹ�õ�ABBͨ����0��ͨ��0, 1: ͨ��1;*/
	BSP_U32 ucG2bp104mTcxoSel:1; 	/* bit 6,G1BBP 104M ʹ�õ�ABBͨ����0��ͨ��0, 1: ͨ��1;*/
	BSP_U32 reserve:25;             /* bit 7-31*/
}DRV_TCXO_SEL_PARA_STRU;

typedef struct
{
    BSP_U32 u32UsbDbg;   /* usbģ�������Ϣ���� */
}DRV_USB_DBG_STRU;

/*50577*/
typedef struct
{
unsigned char nv_status;    /*��nv�Ƿ񼤻�*/
unsigned char diag_enable;  /*diag�˿��Ƿ�ʹ��*/
unsigned char shell_enable; /*shell�˿��Ƿ�ʹ��*/
unsigned char adb_enable;   /*adb�˿��Ƿ�ʹ��*/
unsigned char om_enable;   /*om�˿��Ƿ�ʹ��*/
unsigned char ucReserved_0; /*�����ֶ�*/
unsigned char ucReserved_1; /*�����ֶ�*/
unsigned char ucReserved_2; /*�����ֶ�*/
}NV_HUAWEI_USB_SECURITY_SHELL;


typedef struct
{
	BSP_U32 wdt_enable;
	BSP_U32 wdt_timeout;
	BSP_U32 wdt_keepalive_ctime;
	BSP_U32 wdt_suspend_timerout;
	BSP_U32 wdt_reserve;
}DRV_WDT_INIT_PARA_STRU;


/*�¶ȱ��������߼�ת����  NV_ID_DRV_TSENSOR_TRIM          = 0xd12f */
typedef struct
{
    BSP_U16 tsensor_trim[16];

}DRV_TSENSOR_TRIM_STRU;

/* axi monitor���ID���� */
typedef struct
{
    BSP_U32 reset_flag;     /* ��λ��־��ƥ�䵽��������Ƿ�λ */
    BSP_U32 opt_type;       /* ������ͣ�01:����10:д��11:��д������ֵ:����� */
    BSP_U32 port;           /* ��ض˿� */
    BSP_U32 master_id;      /* ���masterid */
    BSP_U32 start_addr;     /* �����ʼ��ַ */
    BSP_U32 end_addr;       /* ��ؽ�����ַ */
} AMON_CONFIG_T;

/* axi monitor����NV�� NV_ID_DRV_AMON = 0xd130 */
typedef struct
{
    BSP_U32         en_flag;            /* ʹ�ܱ�־��00:ȥʹ�ܣ�01:SOC��10:CPUFAST��11:SOC,CPUFAST */
    AMON_CONFIG_T   soc_config[8];      /* SOC���ã�8�����ID */
    AMON_CONFIG_T   cpufast_config[8];  /* CPUFAST���ã�8�����ID */
} DRV_AMON_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : NV_RF_GPIO_CFG_STRU
 �ṹ˵��  : RF_GPIO�������ɿ��Ը���ΪDRV_GPIO
             ��һЩ��Ƶ���ܳ�����Ҫ�ı���ЩRF_GPIO���ŵĸ��ù��ܼ����״̬
             ͨ����NV���� ID=10047
*****************************************************************************/
typedef struct
{
    BSP_U16 is_used;    /*Range:[0,1]*/
	BSP_U16 gpio_level; /*Range:[0,1]*/
}RF_MODEM_CONTROL;

typedef struct
{
    BSP_U32 rf_gpio_num;
    RF_MODEM_CONTROL modem_inside;	/*����modem*/
    RF_MODEM_CONTROL modem_outside; /*����modem*/
}RF_GPIO_CFG;

typedef struct
{
    RF_GPIO_CFG rf_switch_cfg[16];
}NV_RF_SWITCH_CFG_STRU;

/* SOCP���迪����������NV�� = 0xd132 */
typedef struct
{
    BSP_U32         en_flag;            /* ʹ�ܱ�־��00:ȥʹ�ܣ�01:ʹ�� */
} DRV_SOCP_ON_DEMAND_STRU;

/* drx delay flag */
typedef struct
{
    BSP_U8         lpm3_flag;         /* 0x11 ����lpm3 */
    BSP_U8         lpm3_0;            /* 1��delay,�����ر�delay */
    BSP_U8         lpm3_1;
    BSP_U8         lpm3_2;
    BSP_U8         lpm3_3;
    BSP_U8         lpm3_4;
    BSP_U8         drv_flag;          /* 0x22 ����drv */
    BSP_U8         drv_0;             /* 1��delay,�����ر�delay */
    BSP_U8         drv_1;
    BSP_U8         drv_2;
    BSP_U8         drv_3;
    BSP_U8         drv_4;
    BSP_U8         msp_flag;          /* 0x33 ����msp */
    BSP_U8         msp_0;             /* 1��delay,�����ر�delay */
    BSP_U8         msp_1;
    BSP_U8         msp_2;
    BSP_U8         msp_3;
    BSP_U8         msp_4;
}DRV_DRX_DELAY_STRU;

/* C�˵�����λ���迪����������NV�� = 0xd134 */
typedef struct
{
    BSP_U32 is_feature_on:1;         /* bit0, ����C�˵�����λ�����Ƿ�� */
    BSP_U32 is_connected_ril:1;      /* bit1, �Ƿ��RIL�Խ� */
	BSP_U32 reserve:30;              /* bit 2-31*/
} DRV_CCORE_RESET_STRU;

/* NV ID = 0xd135 */
/* ���ڱ�ʾÿ·LDO��BUCK�Ƿ�� */
typedef struct
{
	BSP_U32 ldo1_switch     :1;         /* ��0bit��ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر� */
	BSP_U32 ldo2_switch     :1;         /* ��1bit��ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر� */
	BSP_U32 buckpa_switch   :1;         /* ��2bit��ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر� */
	BSP_U32 buck1_switch    :1;         /* ��3bit��ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر� */
	BSP_U32 buck2_switch    :1;         /* ��4bit��ֵΪ1��Ϊ�򿪣�ֵΪ0��Ϊ�ر� */
	BSP_U32 reserved        :27;        /* ��5~31bit��Ԥ����Ĭ��ֵΪ0 */
}NV_PASTAR_SWITCH_STRU_BITS;

typedef struct
{
    union
    {
        BSP_U32 u32;
        NV_PASTAR_SWITCH_STRU_BITS bits;
    }cont;
}NV_PASTAR_SWITCH_STRU;
/* end NV ID = 0xd135 */


/* log2.0 2014-03-19 Begin:*/
typedef struct
{
    BSP_U32 ulSocpDelayWriteFlg;/* SOCP�ӳ�д�빦��������� */
    BSP_U32 ulGuSocpLevel;      /* GU SOCPĿ��BUFFER����ˮ�� */
    BSP_U32 ulLSocpLevel;       /* L SOCPĿ��BUFFER����ˮ�� */
    BSP_U32 ulTimeOutValue;     /* SOCPĿ��BUFFER�ĳ�ʱʱ�� */
}DRV_NV_SOCP_LOG_CFG_STRU;
/* log2.0 2014-03-19 End*/
typedef struct
{
    BSP_U32  enUartEnableCfg;
	BSP_U32  AwaitReplyTimer;
	BSP_U32  AwakeTmer;
	BSP_U32  DoSleepTimer;
}DRV_DUAL_MODEM_STR;

/* GPIO����LDO���� NV�� = 0xd137 */
typedef struct
{
    BSP_U32 gpio;      /* LDO��ӦGPIO��� */
    BSP_U32 used;      /* GPIO�Ƿ�ʹ�� */
} DRV_DRV_LDO_GPIO_CFG;

typedef struct
{
    DRV_DRV_LDO_GPIO_CFG ldo_gpio[2];
}DRV_DRV_LDO_GPIO_STRU;


/* GPIO����LDO���� NV�� = 0xd138 */
typedef struct
{
    BSP_U32 modem_id;      /* modem idĬ�ϴ�0��ʼ�������� */
    BSP_U32 gpio;          /* ANTEN��ӦGPIO��� */
    BSP_U32 used;          /* GPIO�Ƿ�ʹ�� */
} DRV_DRV_ANTEN_GPIO_CFG;

typedef struct
{
    DRV_DRV_ANTEN_GPIO_CFG anten_gpio[LDO_GPIO_MAX];
}DRV_DRV_ANTEN_GPIO_STRU;

/* RSE POWER GPIO���� NV�� = 0xd139 */
typedef struct
{
    BSP_U32 ulRsePowerOnIds;
    BSP_U32 ulFemCtrlInfo;
    BSP_U32 ulRfGpioBitMask;
    BSP_U32 ulRfGpioOutValue;
    BSP_U16 usFemMipiCmdAddr;
    BSP_U16 usFemMipiCmdData;
}RF_NV_RSE_CFG_STRU;

/*���߿��ز��µ�����NV*/
/*NVID = 0xd13b��0Ϊ��ʹ�ܸ����ԣ�1Ϊʹ��*/
typedef struct
{
	BSP_U32 is_enable;/*Range:[0,1]*/
}DRV_ANT_SW_UNPD_ENFLAG;

typedef struct
{
	BSP_U32 gpio_num;	/*GPIO���    */
	BSP_U32 is_used;	/*Range:[0,1]*//*�Ƿ�ʹ��*/
	BSP_U32 value;		/*����ֵ */
}DRV_ANT_GPIO_CFG;

/*nvID = 0xd13c*/
/*���ּ����鿪��+��modem��һ�����߿��ص����ã�ÿ�����8������zhaojunȷ��*/
/*0��ʾ���ּ�1�飬1��ʾ���ּ�2�飬2��ʾ��modem���߿���*/
typedef struct
{
	DRV_ANT_GPIO_CFG 	antn_switch[8];
}DRV_ANT_SW_UNPD_CFG;

typedef struct
{
	BSP_U32	DialupEnableCFG;
	BSP_U32 DialupACShellCFG;
}DRV_DIALUP_HSUART_STRU;

typedef struct
{
	DRV_ANT_SW_UNPD_CFG all_switch[3];
}NV_DRV_ANT_SW_UNPD_CFG;
/*End ���߿��ز��µ�����NV*/


/*
*nvid = 0xd13d
*for mmc support or not
*/
typedef struct
{
	BSP_U32 support;
}DRV_MMC_SUPPORT_STRU;

/* PA/RF����ʵ���Ƿ�ʹ�ÿ��أ�������EM_MODEM_CONSUMER_IDö���е�˳�򱣳�һ�� */
/*ͨ��ģ�鹩��� CONSUMER��idö��
typedef enum EM_MODEM_CONSUMER_ID_E
{
    MODEM_PA0,
    MODEM_RFIC0_ANALOG0,
    MODEM_RFIC0_ANALOG1,
    MODEM_FEM0,
    MODEM_PA_VBIAS0,
    MODEM_PA1,
    MODEM_RFIC1_ANALOG0,
    MODEM_RFIC1_ANALOG1,
    MODEM_FEM1,
    MODEM_PA_VBIAS1,
    MODEM_CONSUMER_ID_BUTT
}EM_MODEM_CONSUMER_ID;
*/
typedef struct
{
	BSP_U32 pa0 				: 1;	//1: Ӳ����ʵ�ʹ�������; 0: Ӳ����ʵ�ʹ�������
	BSP_U32 rfic0_analog0 		: 1;
	BSP_U32 rfic0_analog1    	: 1;
	BSP_U32 fem0    			: 1;
	BSP_U32 pa_vbias0       	: 1;
	BSP_U32 pa1 				: 1;
	BSP_U32 rfic1_analog0 		: 1;
	BSP_U32 rfic1_analog1    	: 1;
	BSP_U32 fem1    			: 1;
	BSP_U32 pa_vbias1       	: 1;
	BSP_U32 reserved    : 22;
}PARF_SWITCH_BITS;

typedef struct
{
    union
    {
        BSP_U32 u32;
        PARF_SWITCH_BITS bits;
    }cont;
} NV_DRV_PARF_SWITCH_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

