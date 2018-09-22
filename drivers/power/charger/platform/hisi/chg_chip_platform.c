


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "../../chg_config.h"

#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
#if defined(CONFIG_HKADC)
#include <bsp_hkadc.h>
#endif
#include <bsp_nvim.h>
#include "bsp_sram.h"
#include "power_com.h"
#ifdef CONFIG_COUL
#include <bsp_coul.h>
#endif
#include <product_config.h>
#include <linux/mmitest.h>

#endif


#include "chg_chip_platform.h"

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/
extern struct i2c_client *g_i2c_client;
extern struct chargeIC_chip *g_chip;

extern int chg_en_flag;
#if (MBB_CHG_EXTCHG == FEATURE_ON)

extern int32_t g_extchg_diable_st;

extern boolean g_exchg_online_flag;
#endif/*defined(MBB_CHG_EXTCHG)*/



#if ((MBB_CHG_EXTCHG == FEATURE_ON) || (MBB_CHG_WIRELESS == FEATURE_ON))
extern void usb_notify_event(unsigned long val, void *v);
#endif/*defined(MBB_CHG_EXTCHG) || defined(MBB_CHG_WIRELESS)*/

#if (MBB_CHG_WIRELESS == FEATURE_ON)

extern boolean g_wireless_online_flag;

#endif/*defined(MBB_CHG_WIRELESS)*/

#if (MBB_CHG_HIGH_VOLT_BATT == FEATURE_ON)
extern int chg_hw_para_updated;
#endif


/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/
#define CHG_BAT_VOLT_ADC_CH    0x20

/*���ڱ���NV�ж�ȡ�ĵ�ص�ѹУ׼����*/
int32_t g_vbatt_max = 0;
/*���ڱ���NV�ж�ȡ�ĵ�ص�ѹУ׼��С��*/
int32_t g_vbatt_min = 0;
/*���ڱ����Ƿ������У׼��ʼ���ı�־*/
boolean g_is_batt_volt_calib_init = FALSE;

#define DEFAULT_VOL    3800
#define DEFAULT_TEP    38
#define ONE_THOUSAND     1000


#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)

#define CHG_BATT_THERM_HKADC_ID    CHG_BATT_TEMP_CHAN/*����¶ȶ�ȡͨ��*/
#define CHG_VBUS_VOLT_HKADC_ID     CHG_VBUS_VOLT_CHAN/*VBUS��ѹ��ȡͨ��*/
#define CHG_BATT_VOLT_HKADC_ID     CHG_BATT_VOLT_CHAN/*��ص�ѹ��ȡͨ��*/
#define CHG_BATT_ID_VOLT_HKADC_ID     CHG_BATT_ID_CHAN/*��ص�ѹ��ȡͨ��*/
/*USB�±�*/ 
#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
#define CHG_USB_TEMP_HKADC_ID      CHG_USB_TEMP_CHAN /*USB�¶ȶ�ȡͨ��*/
#endif

#endif

#define BAT_VOL_SIZE    4


/*����Ӳ��Ҫ�󽫵�ѹ�����޸�Ϊ�ɼ���ԭʼֵ��151Ȼ���ٳ���51��ע��˺겻�ܴ�����*/


#define SMEM_FACT_RELEASE_ON       0X19840a0b      /*���߷ŵ�ħ����*/
#define SMEM_FACT_RELEASE_OFF      0X19850b0a      /*���߷ŵ�ħ����*/


/*�ñ���Ӳ���ṩ*/
/* ����ڲ�NTCʵ���¶�У׼��9x25ƽ̨�ñ��ֵ��ADCģ���޸�*/
#if defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5575S_210) \
    || defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577S_932) \
    || defined(BSP_CONFIG_BOARD_E5573S_856) || defined(BSP_CONFIG_BOARD_E5573S_853) \
    || defined(BSP_CONFIG_BOARD_E5573S_607) || defined(BSP_CONFIG_BOARD_E5577CS_603) \
    || defined(BSP_CONFIG_BOARD_E5577S_603) || defined(BSP_CONFIG_BOARD_E5575S_320) \
    || defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573BS)\
    || defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_E5577BS_937)\
    ||defined(BSP_CONFIG_BOARD_607HW) || defined(BSP_CONFIG_BOARD_R218h)
const  CHG_TEMP_ADC_TYPE  g_adc_batt_therm_map[] =
{
//�ñ���Ӳ���ṩ
    {-30,      2304},   /*vol to temp*/
    {-29,      2295},   /*vol to temp*/
    {-28,      2284},   /*vol to temp*/
    {-27,      2274},   /*vol to temp*/
    {-26,      2263},   /*vol to temp*/
    {-25,      2252},   /*vol to temp*/
    {-24,      2240},   /*vol to temp*/
    {-23,      2228},   /*vol to temp*/
    {-22,      2215},   /*vol to temp*/
    {-21,      2202},   /*vol to temp*/
    {-20,      2189},   /*vol to temp*/
    {-19,      2175},   /*vol to temp*/
    {-18,      2161},   /*vol to temp*/
    {-17,      2146},   /*vol to temp*/
    {-16,      2131},   /*vol to temp*/
    {-15,      2116},   /*vol to temp*/
    {-14,      2100},   /*vol to temp*/
    {-13,      2084},   /*vol to temp*/
    {-12,      2067},    /*vol to temp*/
    {-11,      2050},    /*vol to temp*/
    {-10,      2032},    /*vol to temp*/
    {-9,      2014},    /*vol to temp*/
    {-8,      1996},    /*vol to temp*/
    {-7,      1977},    /*vol to temp*/
    {-6 ,       1958},    /*vol to temp*/
    {-5 ,       1939},    /*vol to temp*/
    {-4 ,       1919},    /*vol to temp*/
    {-3 ,       1898},    /*vol to temp*/
    {-2 ,       1878},    /*vol to temp*/
    {-1 ,       1857},    /*vol to temp*/
    {0 ,       1836},    /*vol to temp*/
    {1 ,       1814},    /*vol to temp*/
    {2 ,       1792},    /*vol to temp*/
    {3     ,    1770},    /*vol to temp*/
    {4     ,    1748},    /*vol to temp*/
    {5     ,    1725},    /*vol to temp*/
    {6     ,    1703},    /*vol to temp*/
    {7     ,    1680},    /*vol to temp*/
    {8     ,    1656},    /*vol to temp*/
    {9     ,    1633},    /*vol to temp*/
    {10     ,    1609},    /*vol to temp*/
    {11     ,    1586},    /*vol to temp*/
    {12     ,    1562},    /*vol to temp*/
    {13 ,       1538},    /*vol to temp*/
    {14 ,       1514},    /*vol to temp*/
    {15 ,       1489},    /*vol to temp*/
    {16 ,       1466},    /*vol to temp*/
    {17 ,       1442},    /*vol to temp*/
    {18 ,       1417},    /*vol to temp*/
    {19 ,       1393},    /*vol to temp*/
    {20 ,       1369},    /*vol to temp*/
    {21 ,       1345},    /*vol to temp*/
    {22 ,       1321},    /*vol to temp*/
    {23 ,       1297},    /*vol to temp*/
    {24 ,       1273},    /*vol to temp*/
    {25 ,       1250},    /*vol to temp*/
    {26 ,       1227},    /*vol to temp*/
    {27 ,       1203},    /*vol to temp*/
    {28 ,       1180},    /*vol to temp*/
    {29 ,       1157},    /*vol to temp*/
    {30 ,       1134},    /*vol to temp*/
    {31 ,       1112},    /*vol to temp*/
    {32 ,       1090},    /*vol to temp*/
    {33 ,       1068},    /*vol to temp*/
    {34 ,       1046},    /*vol to temp*/
    {35 ,       1024},    /*vol to temp*/
    {36 ,       1003},    /*vol to temp*/
    {37 ,       982},    /*vol to temp*/
    {38 ,       961},    /*vol to temp*/
    {39 ,       941},    /*vol to temp*/
    {40 ,        921},    /*vol to temp*/
    {41 ,        901},    /*vol to temp*/
    {42 ,        881},    /*vol to temp*/
    {43 ,        862},    /*vol to temp*/
    {44 ,        843},    /*vol to temp*/
    {45 ,        824},    /*vol to temp*/
    {46 ,        806},    /*vol to temp*/
    {47 ,        787},    /*vol to temp*/
    {48 ,        770},    /*vol to temp*/
    {49 ,        752},    /*vol to temp*/
    {50 ,        735},    /*vol to temp*/
    {51 ,        718},    /*vol to temp*/
    {52 ,        702},    /*vol to temp*/
    {53 ,        686},    /*vol to temp*/
    {54 ,        670},    /*vol to temp*/
    {55 ,        654},    /*vol to temp*/
    {56 ,        639},    /*vol to temp*/
    {57 ,        624},    /*vol to temp*/
    {58 ,        609},    /*vol to temp*/
    {59 ,        595},    /*vol to temp*/
    {60 ,        581},     /*vol to temp*/
    {61 ,        567},     /*vol to temp*/
    {62 ,        554},     /*vol to temp*/
    {63 ,        541},     /*vol to temp*/
    {64 ,        528},     /*vol to temp*/
    {65 ,        515},     /*vol to temp*/
    {66,         503},     /*vol to temp*/
    {67 ,        491},     /*vol to temp*/
    {68 ,        479},     /*vol to temp*/
    {69 ,        468},     /*vol to temp*/
    {70 ,        456},     /*vol to temp*/
    {71 ,        445},     /*vol to temp*/
    {72 ,        434},     /*vol to temp*/
    {73 ,        424},     /*vol to temp*/
    {74 ,        414},     /*vol to temp*/
    {75 ,        404},     /*vol to temp*/
    {76 ,        395},     /*vol to temp*/
    {77 ,        385},     /*vol to temp*/
    {78 ,        376},     /*vol to temp*/
    {79 ,        367},     /*vol to temp*/
    {80 ,        358},     /*vol to temp*/
    {81 ,        349},     /*vol to temp*/
    {82 ,        341},     /*vol to temp*/
    {83 ,        333},     /*vol to temp*/
    {84 ,        325},     /*vol to temp*/
    {85,         317},     /*vol to temp*/
};
#elif defined(BSP_CONFIG_BOARD_E5577S_324)
const  CHG_TEMP_ADC_TYPE  g_adc_batt_therm_map[] =
{
//�ñ���Ӳ���ṩ
    {-30,      2304},   /*vol to temp*/
    {-29,      2295},   /*vol to temp*/
    {-28,      2284},   /*vol to temp*/
    {-27,      2274},   /*vol to temp*/
    {-26,      2263},   /*vol to temp*/
    {-25,      2252},   /*vol to temp*/
    {-24,      2240},   /*vol to temp*/
    {-23,      2228},   /*vol to temp*/
    {-22,      2215},   /*vol to temp*/
    {-21,      2202},   /*vol to temp*/
    {-20,      2189},   /*vol to temp*/
    {-19,      2175},   /*vol to temp*/
    {-18,      2161},   /*vol to temp*/
    {-17,      2146},   /*vol to temp*/
    {-16,      2131},   /*vol to temp*/
    {-15,      2116},   /*vol to temp*/
    {-14,      2100},   /*vol to temp*/
    {-13,      2084},   /*vol to temp*/
    {-12,      2067},    /*vol to temp*/
    {-11,      2050},    /*vol to temp*/
    {-10,      2032},    /*vol to temp*/
    {-9,      2014},    /*vol to temp*/
    {-8,      1996},    /*vol to temp*/
    {-7,      1977},    /*vol to temp*/
    {-6 ,       1958},    /*vol to temp*/
    {-5 ,       1939},    /*vol to temp*/
    {-4 ,       1919},    /*vol to temp*/
    {-3 ,       1898},    /*vol to temp*/
    {-2 ,       1878},    /*vol to temp*/
    {-1 ,       1857},    /*vol to temp*/
    {0 ,       1836},    /*vol to temp*/
    {1 ,       1814},    /*vol to temp*/
    {2 ,       1792},    /*vol to temp*/
    {3     ,    1770},    /*vol to temp*/
    {4     ,    1748},    /*vol to temp*/
    {5     ,    1725},    /*vol to temp*/
    {6     ,    1703},    /*vol to temp*/
    {7     ,    1680},    /*vol to temp*/
    {8     ,    1656},    /*vol to temp*/
    {9     ,    1633},    /*vol to temp*/
    {10     ,    1609},    /*vol to temp*/
    {11     ,    1586},    /*vol to temp*/
    {12     ,    1562},    /*vol to temp*/
    {13 ,       1538},    /*vol to temp*/
    {14 ,       1514},    /*vol to temp*/
    {15 ,       1489},    /*vol to temp*/
    {16 ,       1466},    /*vol to temp*/
    {17 ,       1442},    /*vol to temp*/
    {18 ,       1417},    /*vol to temp*/
    {19 ,       1393},    /*vol to temp*/
    {20 ,       1369},    /*vol to temp*/
    {21 ,       1345},    /*vol to temp*/
    {22 ,       1321},    /*vol to temp*/
    {23 ,       1297},    /*vol to temp*/
    {24 ,       1273},    /*vol to temp*/
    {25 ,       1250},    /*vol to temp*/
    {26 ,       1227},    /*vol to temp*/
    {27 ,       1203},    /*vol to temp*/
    {28 ,       1180},    /*vol to temp*/
    {29 ,       1157},    /*vol to temp*/
    {30 ,       1146},    /*vol to temp*/
    {31 ,       1134},    /*vol to temp*/
    {32 ,       1112},    /*vol to temp*/
    {33 ,       1090},    /*vol to temp*/
    {34 ,       1068},    /*vol to temp*/
    {35 ,       1046},    /*vol to temp*/
    {36 ,       1024},    /*vol to temp*/
    {37 ,       1003},    /*vol to temp*/
    {38 ,       982},    /*vol to temp*/
    {39 ,       961},    /*vol to temp*/
    {40 ,        941},    /*vol to temp*/
    {41 ,        921},    /*vol to temp*/
    {42 ,        901},    /*vol to temp*/
    {43 ,        881},    /*vol to temp*/
    {44 ,        862},    /*vol to temp*/
    {45 ,        843},    /*vol to temp*/
    {46 ,        824},    /*vol to temp*/
    {47 ,        806},    /*vol to temp*/
    {48 ,        787},    /*vol to temp*/
    {49 ,        770},    /*vol to temp*/
    {50 ,        752},    /*vol to temp*/
    {51 ,        735},    /*vol to temp*/
    {52 ,        718},    /*vol to temp*/
    {53 ,        702},    /*vol to temp*/
    {54 ,        686},    /*vol to temp*/
    {55 ,        670},    /*vol to temp*/
    {56 ,        654},    /*vol to temp*/
    {57 ,        639},    /*vol to temp*/
    {58 ,        624},    /*vol to temp*/
    {59 ,        609},    /*vol to temp*/
    {60 ,        595},     /*vol to temp*/
    {61 ,        581},     /*vol to temp*/
    {62 ,        567},     /*vol to temp*/
    {63 ,        554},     /*vol to temp*/
    {64 ,        541},     /*vol to temp*/
    {65 ,        528},     /*vol to temp*/
    {66,         515},     /*vol to temp*/
    {67 ,        503},     /*vol to temp*/
    {68 ,        491},     /*vol to temp*/
    {69 ,        479},     /*vol to temp*/
    {70 ,        468},     /*vol to temp*/
    {71 ,        456},     /*vol to temp*/
    {72 ,        445},     /*vol to temp*/
    {73 ,        434},     /*vol to temp*/
    {74 ,        424},     /*vol to temp*/
    {75 ,        414},     /*vol to temp*/
    {76 ,        404},     /*vol to temp*/
    {77 ,        395},     /*vol to temp*/
    {78 ,        385},     /*vol to temp*/
    {79 ,        376},     /*vol to temp*/
    {80 ,        367},     /*vol to temp*/
    {81 ,        358},     /*vol to temp*/
    {82 ,        349},     /*vol to temp*/
    {83 ,        341},     /*vol to temp*/
    {84 ,        333},     /*vol to temp*/
    {85,         325},     /*vol to temp*/
};
#elif defined(BSP_CONFIG_BOARD_E5573S_156)
const  CHG_TEMP_ADC_TYPE  g_adc_batt_therm_map[] =
{
//�ñ���Ӳ���ṩ
    {-30,      2304},   /*vol to temp*/
    {-29,      2295},   /*vol to temp*/
    {-28,      2284},   /*vol to temp*/
    {-27,      2274},   /*vol to temp*/
    {-26,      2263},   /*vol to temp*/
    {-25,      2252},   /*vol to temp*/
    {-24,      2240},   /*vol to temp*/
    {-23,      2228},   /*vol to temp*/
    {-22,      2215},   /*vol to temp*/
    {-21,      2202},   /*vol to temp*/
    {-20,      2189},   /*vol to temp*/
    {-19,      2175},   /*vol to temp*/
    {-18,      2161},   /*vol to temp*/
    {-17,      2146},   /*vol to temp*/
    {-16,      2131},   /*vol to temp*/
    {-15,      2116},   /*vol to temp*/
    {-14,      2100},   /*vol to temp*/
    {-13,      2084},   /*vol to temp*/
    {-12,      2067},    /*vol to temp*/
    {-11,      2050},    /*vol to temp*/
    {-10,      2032},    /*vol to temp*/
    {-9,      2014},    /*vol to temp*/
    {-8,      1996},    /*vol to temp*/
    {-7,      1977},    /*vol to temp*/
    {-6 ,       1958},    /*vol to temp*/
    {-5 ,       1939},    /*vol to temp*/
    {-4 ,       1919},    /*vol to temp*/
    {-3 ,       1898},    /*vol to temp*/
    {-2 ,       1878},    /*vol to temp*/
    {-1 ,       1857},    /*vol to temp*/
    {0 ,       1836},    /*vol to temp*/
    {1 ,       1814},    /*vol to temp*/
    {2 ,       1792},    /*vol to temp*/
    {3     ,    1770},    /*vol to temp*/
    {4     ,    1748},    /*vol to temp*/
    {5     ,    1725},    /*vol to temp*/
    {6     ,    1703},    /*vol to temp*/
    {7     ,    1680},    /*vol to temp*/
    {8     ,    1656},    /*vol to temp*/
    {9     ,    1633},    /*vol to temp*/
    {10     ,    1609},    /*vol to temp*/
    {11     ,    1586},    /*vol to temp*/
    {12     ,    1562},    /*vol to temp*/
    {13 ,       1538},    /*vol to temp*/
    {14 ,       1514},    /*vol to temp*/
    {15 ,       1489},    /*vol to temp*/
    {16 ,       1466},    /*vol to temp*/
    {17 ,       1442},    /*vol to temp*/
    {18 ,       1417},    /*vol to temp*/
    {19 ,       1393},    /*vol to temp*/
    {20 ,       1369},    /*vol to temp*/
    {21 ,       1345},    /*vol to temp*/
    {22 ,       1321},    /*vol to temp*/
    {23 ,       1297},    /*vol to temp*/
    {24 ,       1273},    /*vol to temp*/
    {25 ,       1250},    /*vol to temp*/
    {26 ,       1227},    /*vol to temp*/
    {27 ,       1203},    /*vol to temp*/
    {28 ,       1180},    /*vol to temp*/
    {29 ,       1157},    /*vol to temp*/
    {30 ,       1134},    /*vol to temp*/
    {31 ,       1112},    /*vol to temp*/
    {32 ,       1090},    /*vol to temp*/
    {33 ,       1068},    /*vol to temp*/
    {34 ,       1046},    /*vol to temp*/
    {35 ,       1024},    /*vol to temp*/
    {36 ,       1003},    /*vol to temp*/
    {37 ,       982},    /*vol to temp*/
    {38 ,       961},    /*vol to temp*/
    {39 ,       941},    /*vol to temp*/
    {40 ,        921},    /*vol to temp*/
    {41 ,        901},    /*vol to temp*/
    {42 ,        881},    /*vol to temp*/
    {43 ,        862},    /*vol to temp*/
    {44 ,        843},    /*vol to temp*/
    {45 ,        824},    /*vol to temp*/
    {46 ,        806},    /*vol to temp*/
    {47 ,        787},    /*vol to temp*/
    {48 ,        770},    /*vol to temp*/
    {49 ,        752},    /*vol to temp*/
    {50 ,        735},    /*vol to temp*/
    {51 ,        718},    /*vol to temp*/
    {52 ,        702},    /*vol to temp*/
    {53 ,        686},    /*vol to temp*/
    {54 ,        670},    /*vol to temp*/
    {55 ,        654},    /*vol to temp*/
    {56 ,        639},    /*vol to temp*/
    {57 ,        624},    /*vol to temp*/
    {57 ,        609},    /*vol to temp*/
    {57 ,        595},    /*vol to temp*/
    {58 ,        581},     /*vol to temp*/
    {58 ,        567},     /*vol to temp*/
    {59 ,        554},     /*vol to temp*/
    {60 ,        541},     /*vol to temp*/
    {61 ,        528},     /*vol to temp*/
    {63 ,        515},     /*vol to temp*/
    {66,         503},     /*vol to temp*/
    {67 ,        491},     /*vol to temp*/
    {68 ,        479},     /*vol to temp*/
    {69 ,        468},     /*vol to temp*/
    {70 ,        456},     /*vol to temp*/
    {71 ,        445},     /*vol to temp*/
    {72 ,        434},     /*vol to temp*/
    {73 ,        424},     /*vol to temp*/
    {74 ,        414},     /*vol to temp*/
    {75 ,        404},     /*vol to temp*/
    {76 ,        395},     /*vol to temp*/
    {77 ,        385},     /*vol to temp*/
    {78 ,        376},     /*vol to temp*/
    {79 ,        367},     /*vol to temp*/
    {80 ,        358},     /*vol to temp*/
    {81 ,        349},     /*vol to temp*/
    {82 ,        341},     /*vol to temp*/
    {83 ,        333},     /*vol to temp*/
    {84 ,        325},     /*vol to temp*/
    {85,         317},     /*vol to temp*/
};
#elif defined(BSP_CONFIG_BOARD_E5_E5578)
const  CHG_TEMP_ADC_TYPE  g_adc_batt_therm_map[] =
{
//�ñ���Ӳ���ṩ
    {-30,      2302},   /*vol to temp*/
    {-29,      2293},   /*vol to temp*/
    {-28,      2283},   /*vol to temp*/
    {-27,      2274},   /*vol to temp*/
    {-26,      2263},   /*vol to temp*/
    {-25,      2252},   /*vol to temp*/
    {-24,      2241},   /*vol to temp*/
    {-23,      2229},   /*vol to temp*/
    {-22,      2217},   /*vol to temp*/
    {-21,      2204},   /*vol to temp*/
    {-20,      2191},   /*vol to temp*/
    {-19,      2177},   /*vol to temp*/
    {-18,      2163},   /*vol to temp*/
    {-17,      2148},   /*vol to temp*/
    {-16,      2133},   /*vol to temp*/
    {-15,      2117},   /*vol to temp*/
    {-14,      2101},   /*vol to temp*/
    {-13,      2084},   /*vol to temp*/
    {-12,      2066},    /*vol to temp*/
    {-11,      2048},    /*vol to temp*/
    {-10,      2030},    /*vol to temp*/
    {-9,      2010},    /*vol to temp*/
    {-8,      1991},    /*vol to temp*/
    {-7,      1971},    /*vol to temp*/
    {-6 ,       1950},    /*vol to temp*/
    {-5 ,       1929},    /*vol to temp*/
    {-4 ,       1908},    /*vol to temp*/
    {-3 ,       1886},    /*vol to temp*/
    {-2 ,       1863},    /*vol to temp*/
    {-1 ,       1840},    /*vol to temp*/
    {0 ,       1817},    /*vol to temp*/
    {1 ,       1793},    /*vol to temp*/
    {2 ,       1780},    /*vol to temp*/
    {3     ,    1769},    /*vol to temp*/
    {4     ,    1744},    /*vol to temp*/
    {5     ,    1719},    /*vol to temp*/
    {6     ,    1694},    /*vol to temp*/
    {7     ,    1668},    /*vol to temp*/
    {8     ,    1643},    /*vol to temp*/
    {9     ,    1617},    /*vol to temp*/
    {10     ,    1590},    /*vol to temp*/
    {11     ,    1564},    /*vol to temp*/
    {12     ,    1537},    /*vol to temp*/
    {13 ,       1483},    /*vol to temp*/
    {14 ,       1456},    /*vol to temp*/
    {15 ,       1429},    /*vol to temp*/
    {16 ,       1415},    /*vol to temp*/
    {17 ,       1402},    /*vol to temp*/
    {18 ,       1375},    /*vol to temp*/
    {19 ,       1348},    /*vol to temp*/
    {20 ,       1320},    /*vol to temp*/
    {21 ,       1293},    /*vol to temp*/
    {22 ,       1267},    /*vol to temp*/
    {23 ,       1240},    /*vol to temp*/
    {24 ,       1213},    /*vol to temp*/
    {25 ,       1187},    /*vol to temp*/
    {26 ,       1160},    /*vol to temp*/
    {27 ,       1134},    /*vol to temp*/
    {28 ,       1125},    /*vol to temp*/
    {29 ,       1117},    /*vol to temp*/
    {30 ,       1100},    /*vol to temp*/
    {31 ,       1075},    /*vol to temp*/
    {32 ,       1050},    /*vol to temp*/
    {33 ,       1025},    /*vol to temp*/
    {34 ,       1000},    /*vol to temp*/
    {35 ,       970},    /*vol to temp*/
    {36 ,       960},    /*vol to temp*/
    {37 ,       950},    /*vol to temp*/
    {38 ,       940},    /*vol to temp*/
    {39 ,       928},    /*vol to temp*/
    {40 ,        905},    /*vol to temp*/
    {41 ,        882},    /*vol to temp*/
    {42 ,        860},    /*vol to temp*/
    {43 ,        838},    /*vol to temp*/
    {44 ,        816},    /*vol to temp*/
    {45 ,        795},    /*vol to temp*/
    {46 ,        774},    /*vol to temp*/
    {47 ,        753},    /*vol to temp*/
    {48 ,        737},    /*vol to temp*/
    {49 ,        727},    /*vol to temp*/
    {50 ,        714},    /*vol to temp*/
    {51 ,        695},    /*vol to temp*/
    {52 ,        676},    /*vol to temp*/
    {53 ,        658},    /*vol to temp*/
    {54 ,        640},    /*vol to temp*/
    {55 ,        622},    /*vol to temp*/
    {56 ,        605},    /*vol to temp*/
    {57 ,        589},    /*vol to temp*/
    {58 ,        573},    /*vol to temp*/
    {59 ,        557},    /*vol to temp*/
    {60 ,        541},     /*vol to temp*/
    {61 ,        526},     /*vol to temp*/
    {62 ,        511},     /*vol to temp*/
    {63 ,        497},     /*vol to temp*/
    {64 ,        483},     /*vol to temp*/
    {65 ,        470},     /*vol to temp*/
    {66,         457},     /*vol to temp*/
    {67 ,        444},     /*vol to temp*/
    {68 ,        431},     /*vol to temp*/
    {69 ,        419},     /*vol to temp*/
    {70 ,        407},     /*vol to temp*/
    {71 ,        395},     /*vol to temp*/
    {72 ,        384},     /*vol to temp*/
    {73 ,        373},     /*vol to temp*/
    {74 ,        363},     /*vol to temp*/
    {75 ,        353},     /*vol to temp*/
    {76 ,        343},     /*vol to temp*/
    {77 ,        334},     /*vol to temp*/
    {78 ,        324},     /*vol to temp*/
    {79 ,        315},     /*vol to temp*/
    {80 ,        306},     /*vol to temp*/
    {81 ,        297},     /*vol to temp*/
    {82 ,        289},     /*vol to temp*/
    {83 ,        282},     /*vol to temp*/
    {84 ,        274},     /*vol to temp*/
    {85,         266},     /*vol to temp*/
};
#elif defined(BSP_CONFIG_BOARD_401HW) || defined(BSP_CONFIG_BOARD_506HW) \
   || defined(BSP_CONFIG_BOARD_506HW_2)
const  CHG_TEMP_ADC_TYPE  g_adc_batt_therm_map[] =
{
    {-30,      2293},   /*vol to temp*/
    {-29,      2283},   /*vol to temp*/
    {-28,      2274},   /*vol to temp*/
    {-27,      2263},   /*vol to temp*/
    {-26,      2252},   /*vol to temp*/
    {-25,      2241},   /*vol to temp*/
    {-24,      2229},   /*vol to temp*/
    {-23,      2217},   /*vol to temp*/
    {-22,      2204},   /*vol to temp*/
    {-21,      2191},   /*vol to temp*/
    {-20,      2177},   /*vol to temp*/
    {-19,      2163},    /*vol to temp*/
    {-18,      2148},    /*vol to temp*/
    {-17,      2133},    /*vol to temp*/
    {-16,      2117},    /*vol to temp*/
    {-15,      2101},    /*vol to temp*/
    {-14,      2084},    /*vol to temp*/
    {-13,       2066},    /*vol to temp*/
    {-12,       2048},    /*vol to temp*/
    {-11,       2030},    /*vol to temp*/
    {-10,       2010},    /*vol to temp*/
    {-9 ,       1991},    /*vol to temp*/
    {-8 ,       1971},    /*vol to temp*/
    {-7 ,       1950},    /*vol to temp*/
    {-6 ,       1929},    /*vol to temp*/
    {-5 ,       1919},    /*vol to temp*/
    {-4 ,       1908},    /*vol to temp*/
    {-3 ,       1886},    /*vol to temp*/
    {-2 ,       1863},    /*vol to temp*/
    {-1 ,       1840},    /*vol to temp*/
    {0  ,       1817},    /*vol to temp*/
    {1  ,       1793},    /*vol to temp*/
    {2  ,       1769},    /*vol to temp*/
    {3  ,       1744},    /*vol to temp*/
    {4  ,       1719},    /*vol to temp*/
    {5  ,       1694},    /*vol to temp*/
    {6  ,       1668},    /*vol to temp*/
    {7 ,        1643},    /*vol to temp*/
    {8 ,        1617},    /*vol to temp*/
    {9 ,        1590},    /*vol to temp*/
    {10 ,       1564},    /*vol to temp*/
    {11 ,       1537},    /*vol to temp*/
    {12 ,       1510},    /*vol to temp*/
    {13 ,       1483},    /*vol to temp*/
    {14 ,       1456},    /*vol to temp*/
    {15 ,       1429},    /*vol to temp*/
    {16 ,       1402},    /*vol to temp*/
    {17 ,       1375},    /*vol to temp*/
    {18 ,       1367},    /*vol to temp*/
    {19 ,       1359},    /*vol to temp*/  
    {20 ,       1351},    /*vol to temp*/ 
    {21 ,       1348},    /*vol to temp*/
    {22 ,       1320},    /*vol to temp*/
    {23 ,       1293},    /*vol to temp*/
    {24 ,       1267},    /*vol to temp*/
    {25 ,       1240},    /*vol to temp*/
    {26 ,       1213},    /*vol to temp*/
    {27 ,       1187},    /*vol to temp*/
    {28 ,       1160},    /*vol to temp*/
    {29 ,       1134},    /*vol to temp*/
    {30 ,       1108},    /*vol to temp*/
    {31 ,       1100},    /*vol to temp*/
    {32 ,       1092},    /*vol to temp*/
    {33 ,       1083},    /*vol to temp*/
    {34 ,       1058},    /*vol to temp*/
    {35 ,       1033},    /*vol to temp*/
    {36 ,       1008},    /*vol to temp*/
    {37 ,        984},    /*vol to temp*/
    {38 ,        959},    /*vol to temp*/
    {39 ,        936},    /*vol to temp*/
    {40 ,        912},    /*vol to temp*/
    {41 ,        890},    /*vol to temp*/
    {42 ,        878},    /*vol to temp*/
    {43 ,        867},    /*vol to temp*/
    {44 ,        845},    /*vol to temp*/
    {45 ,        823},    /*vol to temp*/
    {46 ,        802},    /*vol to temp*/
    {47 ,        781},    /*vol to temp*/
    {48 ,        760},    /*vol to temp*/
    {49 ,        750},    /*vol to temp*/
    {50 ,        740},    /*vol to temp*/
    {51 ,        720},    /*vol to temp*/
    {52 ,        701},    /*vol to temp*/
    {53 ,        682},    /*vol to temp*/
    {54 ,        664},    /*vol to temp*/
    {55 ,        655},    /*vol to temp*/
    {56 ,        646},    /*vol to temp*/
    {57 ,        628},    /*vol to temp*/
    {58 ,        611},    /*vol to temp*/
    {59 ,        594},    /*vol to temp*/
    {60 ,        578},     /*vol to temp*/
    {61 ,        562},     /*vol to temp*/
    {62 ,        546},     /*vol to temp*/
    {63 ,        531},     /*vol to temp*/
    {64 ,        516},     /*vol to temp*/
    {65 ,        502},     /*vol to temp*/
    {65 ,        488},     /*vol to temp*/
    {67 ,        474},     /*vol to temp*/
    {68 ,        461},     /*vol to temp*/
    {69 ,        448},     /*vol to temp*/
    {70 ,        435},     /*vol to temp*/
    {71 ,        423},     /*vol to temp*/
    {72 ,        411},     /*vol to temp*/
    {73 ,        399},     /*vol to temp*/
    {74 ,        388},     /*vol to temp*/
    {75 ,        377},     /*vol to temp*/
    {76 ,        366},     /*vol to temp*/
    {77 ,        356},     /*vol to temp*/
    {78 ,        346},     /*vol to temp*/
    {79 ,        337},     /*vol to temp*/
    {80 ,        327},     /*vol to temp*/
    {81 ,        318},     /*vol to temp*/
    {82 ,        309},     /*vol to temp*/
    {83 ,        300},     /*vol to temp*/
    {84 ,        292},     /*vol to temp*/
    {85 ,        284},     /*vol to temp*/

};
#else /* E5771h��ǰ���VT��δ��������ʱ��Ĭ����else��֧  */
CHG_TEMP_ADC_TYPE  g_adc_batt_therm_map[] =
{
//�ñ���Ӳ���ṩ

    {-30,      2327},   /*vol to temp*/
    {-29,      2319},   /*vol to temp*/
    {-28,      2311},   /*vol to temp*/
    {-27,      2302},   /*vol to temp*/
    {-26,      2293},   /*vol to temp*/
    {-25,      2283},   /*vol to temp*/
    {-24,      2274},   /*vol to temp*/
    {-23,      2263},   /*vol to temp*/
    {-22,      2252},   /*vol to temp*/
    {-21,      2241},   /*vol to temp*/
    {-20,      2229},   /*vol to temp*/
    {-19,      2217},   /*vol to temp*/
    {-18,      2204},   /*vol to temp*/
    {-17,      2191},   /*vol to temp*/
    {-16,      2177},   /*vol to temp*/
    {-15,      2163},    /*vol to temp*/
    {-14,      2148},    /*vol to temp*/
    {-13,      2133},    /*vol to temp*/
    {-12,      2117},    /*vol to temp*/
    {-11,      2101},    /*vol to temp*/
    {-10,      2084},    /*vol to temp*/
    {-9 ,       2066},    /*vol to temp*/
    {-8 ,       2048},    /*vol to temp*/
    {-7 ,       2030},    /*vol to temp*/
    {-6 ,       2010},    /*vol to temp*/
    {-5 ,       1991},    /*vol to temp*/
    {-4 ,       1971},    /*vol to temp*/
    {-3 ,       1950},    /*vol to temp*/
    {-2 ,       1929},    /*vol to temp*/
    {-1 ,       1908},    /*vol to temp*/
    {0     ,    1886},    /*vol to temp*/
    {1     ,    1863},    /*vol to temp*/
    {2     ,    1840},    /*vol to temp*/
    {3     ,    1817},    /*vol to temp*/
    {4     ,    1793},    /*vol to temp*/
    {5     ,    1769},    /*vol to temp*/
    {6     ,    1744},    /*vol to temp*/
    {7     ,    1719},    /*vol to temp*/
    {8     ,    1694},    /*vol to temp*/
    {9     ,    1668},    /*vol to temp*/
    {10 ,       1643},    /*vol to temp*/
    {11 ,       1617},    /*vol to temp*/
    {12 ,       1590},    /*vol to temp*/
    {13 ,       1564},    /*vol to temp*/
    {14 ,       1537},    /*vol to temp*/
    {15 ,       1510},    /*vol to temp*/
    {16 ,       1483},    /*vol to temp*/
    {17 ,       1456},    /*vol to temp*/
    {18 ,       1429},    /*vol to temp*/
    {19 ,       1402},    /*vol to temp*/
    {20 ,       1375},    /*vol to temp*/
    {21 ,       1348},    /*vol to temp*/
    {22 ,       1320},    /*vol to temp*/
    {23 ,       1293},    /*vol to temp*/
    {24 ,       1267},    /*vol to temp*/
    {25 ,       1240},    /*vol to temp*/
    {26 ,       1213},    /*vol to temp*/
    {27 ,       1187},    /*vol to temp*/
    {28 ,       1160},    /*vol to temp*/
    {29 ,       1134},    /*vol to temp*/
    {30 ,       1108},    /*vol to temp*/
    {31 ,       1083},    /*vol to temp*/
    {32 ,       1058},    /*vol to temp*/
    {33 ,       1033},    /*vol to temp*/
    {34 ,       1008},    /*vol to temp*/
    {35 ,        984},    /*vol to temp*/
    {36 ,        959},    /*vol to temp*/
    {37 ,        936},    /*vol to temp*/
    {38 ,        912},    /*vol to temp*/
    {39 ,        890},    /*vol to temp*/
    {40 ,        867},    /*vol to temp*/
    {41 ,        845},    /*vol to temp*/
    {42 ,        823},    /*vol to temp*/
    {43 ,        802},    /*vol to temp*/
    {44 ,        781},    /*vol to temp*/
    {45 ,        760},    /*vol to temp*/
    {46 ,        740},    /*vol to temp*/
    {47 ,        720},    /*vol to temp*/
    {48 ,        701},    /*vol to temp*/
    {49 ,        682},    /*vol to temp*/
    {50 ,        664},    /*vol to temp*/
    {51 ,        646},    /*vol to temp*/
    {52 ,        628},    /*vol to temp*/
    {53 ,        611},    /*vol to temp*/
    {54 ,        594},    /*vol to temp*/
    {55 ,        578},     /*vol to temp*/
    {56 ,        562},     /*vol to temp*/
    {57 ,        546},     /*vol to temp*/
    {58 ,        531},     /*vol to temp*/
    {59 ,        516},     /*vol to temp*/
    {60 ,        502},     /*vol to temp*/
    {61 ,        488},     /*vol to temp*/
    {62 ,        474},     /*vol to temp*/
    {63 ,        461},     /*vol to temp*/
    {64 ,        448},     /*vol to temp*/
    {65 ,        435},     /*vol to temp*/
    {66 ,        423},     /*vol to temp*/
    {67 ,        411},     /*vol to temp*/
    {68 ,        399},     /*vol to temp*/
    {69 ,        388},     /*vol to temp*/
    {70 ,        377},     /*vol to temp*/
    {71 ,        366},     /*vol to temp*/
    {72 ,        356},     /*vol to temp*/
    {73 ,        346},     /*vol to temp*/
    {74 ,        337},     /*vol to temp*/
    {75 ,        327},     /*vol to temp*/
    {76 ,        318},     /*vol to temp*/
    {77 ,        309},     /*vol to temp*/
    {78 ,        300},     /*vol to temp*/
    {79 ,        292},     /*vol to temp*/
    {80 ,        284},     /*vol to temp*/
    {81 ,        276},     /*vol to temp*/
    {82 ,        268},     /*vol to temp*/
    {83 ,        261},     /*vol to temp*/
    {84 ,        254},     /*vol to temp*/
    {85 ,        247},     /*vol to temp*/

};
#endif

/*�ñ���Ӳ���ṩ*/
/* �弶����¶�NTCʵ���¶�У׼��
7x25ƽ̨�ñ��ֵ��ADCģ���޸ģ�EC5075��Ʒ�弶���NTCû�õ���Ԥ��*/
CHG_TEMP_ADC_TYPE  g_adc_battbtm_therm_map[] =
{
    {-30, 2416},     /* */
    {-25,2411},      /* */
    {-20,2353},      /* */
    {-15,2282},      /* */
    {-10,2197},      /* */
    {-5,2173},       /* */
    {0,2058},        /* */
    {5,1927},        /* */
    {10,1782},       /* */
    {15,1623},       /* */
    {20,1463},       /* */
    {25,1300},       /* */
    {30,1141},       /* */
    {35,991},        /* */
    {40,853},        /* */
    {45,729},        /* */
    {50,619},        /* */
    {55,523},        /* */
    {60,441},        /* */
    {65,372},        /* */
    {70,313},        /* */
    {75,263},        /* */
    {80,222},        /* */
    {85,187},        /* */
    {90,158},        /* */
    {95,134},        /* */
    {100,113},       /* */
    {105,97},        /* */
    {110,83},        /* */
    {115,71},        /* */
};

/* usb port temp table, supplied by hardware */
#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
static const  CHG_TEMP_ADC_TYPE  g_adc_usb_therm_map[] =
{
    {-30,      2416},     /*vol to temp*/
    {-25,      2411},     /*vol to temp*/
    {-20,      2353},     /*vol to temp*/
    {-15,      2282},     /*vol to temp*/
    {-10,      2197},     /*vol to temp*/
    {-5,       2173},      /*vol to temp*/
    {0,        2058},       /*vol to temp*/
    {5,        1927},       /*vol to temp*/
    {10,       1782},      /*vol to temp*/
    {15,       1623},      /*vol to temp*/
    {20,       1463},      /*vol to temp*/
    {25,       1300},      /*vol to temp*/
    {30,       1141},      /*vol to temp*/
    {35,        991},       /*vol to temp*/
    {40,        853},       /*vol to temp*/
    {45,        729},       /*vol to temp*/
    {50,        619},       /*vol to temp*/
    {55,        523},       /*vol to temp*/
    {60,        441},       /*vol to temp*/
    {65,        372},       /*vol to temp*/
    {70,        313},       /*vol to temp*/
    {75,        263},       /*vol to temp*/
    {80,        222},       /*vol to temp*/
    {85,        187},       /*vol to temp*/
    {90,        158},       /*vol to temp*/
    {95,        134},       /*vol to temp*/
    {100,       113},      /*vol to temp*/
    {105,        97},       /*vol to temp*/
    {110,        83},       /*vol to temp*/
    {115,        71},       /*vol to temp*/
};
#endif

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
/* ���У׼����С������ѹ**/
#if (MBB_CHG_HIGH_VOLT_BATT == FEATURE_ON)
#if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937) 
#define CHG_BATT_CALI_MIN_VOLT  (3400)/*��ѹУ׼����*/
#define CHG_BATT_CALI_MAX_VOLT  (4200)/*��ѹУ׼����*/
#else
#define CHG_BATT_CALI_MIN_VOLT  (3450)/*��ѹУ׼����*/
#define CHG_BATT_CALI_MAX_VOLT  (4350)/*��ѹУ׼����*/
#endif
#else
#define CHG_BATT_CALI_MIN_VOLT  (3400)/*��ѹУ׼����*/
#define CHG_BATT_CALI_MAX_VOLT  (4200)/*��ѹУ׼����*/
#endif

#define CHG_VBATT_CONVERT_PARA                 (3)
#define MICRO_TO_MILLI_V                   (1000)

int32_t bsp_i2c_read(uint8_t reg)
{
    int ret = 0;

    if(NULL == g_i2c_client)
    {
        pr_err("%s failed due to g_i2c_client doesn't exist@~\n", __FUNCTION__);
        return -1;
    }

    ret = i2c_smbus_read_byte_data(g_i2c_client, reg);

    if(ret < 0)
    {
        return -1;
    }
    else
    {
        return ret;
    }
}

int32_t bsp_i2c_write(uint8_t reg, int32_t value)
{
    if(NULL == g_i2c_client)
    {
        pr_err("%s failed due to g_i2c_client doesn't exist@~\n", __FUNCTION__);
        return -1;
    }

    if(0 == i2c_smbus_write_byte_data(g_i2c_client, reg, value))
    {
        return 0;
    }
    else
    {
        return -1;
    }
}
/**********************************************************************
FUNCTION:    CHG_SET_POWER_OFF
DESCRIPTION: The poweroff func of CHG module, all the power-off operation
             except at boot phase MUST be performed via calling this.
INPUT:       The shutdown reason which triggered system poweroff.
             All VALID REASON:
             DRV_SHUTDOWN_BATTERY_ERROR --BATTERY ERROR;
             DRV_SHUTDOWN_TEMPERATURE_PROTECT --EXTREAM HIGH TEMPERATURE.
             DRV_SHUTDOWN_LOW_TEMP_PROTECT --EXTREAM LOW TEMPERATURE
             DRV_SHUTDOWN_CHARGE_REMOVE --CHGR REMOVAL WHILE POWEROFF CHG
             DRV_SHUTDOWN_LOW_BATTERY --LOW BATTERY
OUTPUT:      None.
RETURN:      None.
NOTE:        When this function get called to power system off, it record
             the shutdown reason, then simulate POWER_KEY event to APP to
             perform the real system shutdown process.
             THUS, THIS FUNCTION DOESN'T TAKE AFFECT IF APP DIDN'T STARTUP.
***********************************************************************/
/***************Note:ƽ̨��ش��룬����ƽ̨����Ҫ��ӣ��е�ƽ̨��9x25��Ҫ
              ��ֲ��Ա������Ҫ����ӻ����Ƴ��±ߺ�������***************************/
void chg_set_power_off(DRV_SHUTDOWN_REASON_ENUM real_reason)
{
    /*���ڹرճ�纯��ʹ��I2C����ʱ����msleep�ȷ�ԭ�Ӳ�����Ҫschedule CPU,
     �ڶ�ʱ���ж�����Ҫatomicʹ�ã��ᵼ���ں�BUG*/
    chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:chg_set_power_off:power off by reason = %d \n ",real_reason);
    #if (MBB_CHG_PLATFORM_V7R2 == FEATURE_OFF)
    kernel_power_off();
    #else
    bsp_drv_set_power_off_reason(real_reason);
    bsp_drv_power_off();
    #endif
    return;
}
/**********************************************************************
FUNCTION:    chg_send_stat_to_app
DESCRIPTION: Charge module sends charge state to application layer.
INPUT:       uint32_t chg_device_id,
             uint32_t chg_event_id
OUTPUT:      None.
RETURN:      None.
NOTE:        None
***********************************************************************/
void chg_send_stat_to_app(uint32_t chg_device_id, uint32_t chg_event_id)
{
#if (MBB_CHG_POWER_SUPPLY == FEATURE_ON)
    /*�ȸ���power supply���ڵ�������Ϣ*/
    chg_update_power_suply_info();

    /*��Ӧ���ϱ�power_supply_changed�¼�*/
    if((DEVICE_ID_TEMP == chg_device_id) || (DEVICE_ID_KEY == chg_device_id)
        || (DEVICE_ID_BATTERY == chg_device_id))
    {
        power_supply_changed(&g_chip->bat);
    }
    else if(DEVICE_ID_WIRELESS == chg_device_id)
    {
        power_supply_changed(&g_chip->wireless);
    }
    else if(DEVICE_ID_EXTCHG == chg_device_id)
    {
        power_supply_changed(&g_chip->extchg);
    }
    else if(DEVICE_ID_USB == chg_device_id)
    {
        power_supply_changed(&g_chip->usb);
    }
    else if(DEVICE_ID_CHARGER == chg_device_id)
    {
        power_supply_changed(&g_chip->ac);
    }
    else
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:chg event device id unknow !\n ");
    }
    chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:chg_send_stat_to_app->deviceid %d, eventid %d \n ",
                            chg_device_id,chg_event_id);
#else
    /*********NOTE:����Ƿ�LINUXϵͳ�Ȳ�ʹ��power supply�¼��ϱ�APP��ʽ��ƽ̨��Ҫ��ƽ̨
              �ϱ��¼��Ľӿں����ڴ��޸�,��V7R1ƽ̨��ʹ�����º���BSP_CHGC_SendStaToApp************/
    //BSP_CHGC_SendStaToApp((uint32_t)chg_device_id, (uint32_t)chg_event_id);
    chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:chg_send_stat_to_app->deviceid %d, eventid %d \n ",
                            chg_device_id,chg_event_id);
#endif/*MBB_CHG_POWER_SUPPLY*/
}


#ifndef CHG_STUB
DRV_START_MODE_ENUM chg_get_start_mode(void)
{
    /*����ģʽ�Ĺ����ڴ���Ҫ����V7R2ƽ̨�������䣬��׮����ģʽ������������*/
#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
    DRV_START_MODE mode = DRV_START_MODE_NORMAL;
    DRV_RUN_MODE boot_mode = get_run_mode();
    DRV_CHARGING_MODE pwd_flag = get_pd_charge_flag();
#if (FEATURE_ON == MBB_DLOAD)
    if((RUN_MODE_NORMAL == boot_mode) && (POWER_DOWN_CHARGING_MODE != pwd_flag))
    {
        /* ����ģʽ */
        mode = DRV_START_MODE_NORMAL;
    }
    else if((RUN_MODE_NORMAL == boot_mode) && ((POWER_DOWN_CHARGING_MODE == pwd_flag)))
    {
        /* �ػ����ģʽ */
        mode = DRV_START_MODE_CHARGING;
    }
    else if(RUN_MODE_RECOVERY == boot_mode)
    {
        /* ����ģʽ */
        mode = DRV_START_MODE_UPDATE;     
    }
#endif
    return mode;
#endif

}
#else
DRV_START_MODE_ENUM chg_get_start_mode(void)
{
    return DRV_START_MODE_NORMAL;
}
#endif
 
boolean chg_is_powdown_charging (void)
{
    DRV_START_MODE_ENUM start_mode = DRV_START_MODE_BUTT;

    /*����ģʽ���岻����ػ����*/
    if(TRUE == chg_is_ftm_mode())
    {
        return FALSE;
    }

    start_mode = chg_get_start_mode();
    if(DRV_START_MODE_CHARGING == start_mode)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

#if (MBB_CHG_WIRELESS == FEATURE_ON)
/*���߳��MMI����ǰ������*/
#define WIRELESS_MMI_IUSB_CURRENT               (900)
/*���߳����������*/
#define WIRELESS_MMI_ICHG_CURRENT               (1024)
/*���߳���ӳ�6S*/
#define WIRELESS_MMI_TEST_DELAY_COUNT           (6000)


void wireless_mmi_test_proc(ulong64_t plug)
{
    int32_t vbus_volt = 0;

    if(0 == plug)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:MMI TEST WIRELESS_CHGR PLUG OUT!\n");
        (void)chg_set_charge_enable(FALSE);
        chg_stm_set_wireless_online_st(FALSE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_WIRELESS, (uint32_t)CHG_EVENT_NONEED_CARE);
        return;
    }

    vbus_volt = chg_get_volt_from_adc(CHG_PARAMETER__VBUS_VOLT);
    if(vbus_volt < VBUS_JUDGEMENT_THRESHOLD)
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_PLT:MMI TEST WIRELESS_CHGR PLUG IN!\n");
        chg_set_wireless_chg_enable(TRUE);
        (void)chg_set_dpm_val(CHG_WIRELESS_DPM_VOLT);
        (void)chg_set_cur_level(WIRELESS_MMI_ICHG_CURRENT);
        (void)chg_set_supply_limit(WIRELESS_MMI_IUSB_CURRENT);
        (void)chg_set_charge_enable(TRUE);
        chg_delay_ms(WIRELESS_MMI_TEST_DELAY_COUNT);

        if(TRUE == chg_is_IC_charging())
        {
            chg_stm_set_wireless_online_st(TRUE);
            chg_send_stat_to_app((uint32_t)DEVICE_ID_WIRELESS, (uint32_t)CHG_EVENT_NONEED_CARE);
        }
        else
        {
            chg_stm_set_wireless_online_st(FALSE);
            chg_send_stat_to_app((uint32_t)DEVICE_ID_WIRELESS, (uint32_t)CHG_EVENT_NONEED_CARE);
        }
        (void)chg_set_charge_enable(FALSE);
    }
    else
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:MMI TEST VBUS above 700mv!\n");
        (void)chg_set_charge_enable(FALSE);
        chg_stm_set_wireless_online_st(FALSE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_WIRELESS, (uint32_t)CHG_EVENT_NONEED_CARE);
    }
}
#endif/*MBB_CHG_WIRELESS*/

#if (MBB_CHG_EXTCHG == FEATURE_ON)

void extchg_mmi_test_proc(void)
{
    boolean extchg_online_st = FALSE;
    /*MMI����ģʽͨ��ʹ�ܶ�������VBUS��ѹ�ж϶�������豸�Ƿ���λ*/
    extchg_online_st = chg_get_extchg_online_status();
    chg_print_level_message(CHG_MSG_INFO, "CHG_PLT:extchg_mmi_test extchg_online_st = %d!!!\n",extchg_online_st);
    chg_stm_set_extchg_online_st(extchg_online_st);
    chg_send_stat_to_app((uint32_t)DEVICE_ID_EXTCHG, (uint32_t)CHG_EVENT_NONEED_CARE);
    chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:extchg_mmi_test over stop extchg!\n");
}
#endif/*defined(MBB_CHG_EXTCHG)*/


/*PT��λʹ�ܳ��ǰ������*/
#define PT_ENABLECHG_IUSB_CURRENT          (500)
/*PT��λʹ�ܳ��������*/
#define PT_ENABLECHG_ICHG_CURRENT          (576)
/*PT��λʹ�ܳ���ѹ��ѹ*/
#define PT_ENABLECHG_CV_VOLTAGE            (4200)
/*PT��λʹ�ܳ���ֹ����*/
#define PT_ENABLECHG_TERMINATE_CURRENT     (128)

void chg_pt_mmi_test_proc(void)
{
    (void)chg_set_supply_limit(PT_ENABLECHG_IUSB_CURRENT);
    (void)chg_set_cur_level(PT_ENABLECHG_ICHG_CURRENT);
    (void)chg_set_vreg_level(PT_ENABLECHG_CV_VOLTAGE);
    (void)chg_set_term_current(PT_ENABLECHG_TERMINATE_CURRENT);
    (void)chg_set_charge_enable(TRUE);
}

static inline char* get_chgr_name_by_id(int32_t chg_type)
{
    static char* chg_chgr_type_name_tab[CHG_CHGR_INVALID + 1] =
    {
        "Unknown",                      //���������δ֪
        "Wall Charger",                 //��׼�����
        "USB HOST PC",                  //USB
        "Non-Standard Chgr",            //�����������
        "wireless chgr"                 //���߳����
        "extchg chgr"                   //��������
        "Invalid",                      //�����������
    };

    return ((chg_type >= CHG_CHGR_UNKNOWN && chg_type <= CHG_CHGR_INVALID) \
                         ? chg_chgr_type_name_tab[chg_type] : "null");
}

/*****************************************************************************
 �� �� ��  : get_chgr_type_from_usb
 ��������  : Get real charger type from USB module.
             This function called the platform interfaces to obtain the real
             charger type from USB module.
 �������  : plug:���Դ����γ�
 �������  : chg_type:���������
 �� �� ֵ  : Charger type of state machine needed.
 CALL-WHOM : Platform interfaces.
 WHO-CALLED: chg_check_and_update_hw_param_per_chgr_type
             chg_transit_state_period_func
 NOTICE    : 1. Platform chgr_type enum may be different from chg_stm design,
             we need convert or remap them before return.
             2. Balong V3R2/V7R1 platform didn't support CHG_USB_HOST_PC,
             CHG_NONSTD_CHGR and CHG_USB_HOST_PC would all be treated as
             CHG_NONSTD_CHGR.
             3. Export Required.
*****************************************************************************/
chg_chgr_type_t get_chgr_type_from_usb(ulong64_t plug,int32_t chg_type)
{

    chg_stm_state_type cur_stat = chg_stm_get_cur_state();
    CHG_MODE_ENUM cur_chg_mode = chg_get_cur_chg_mode();
    chg_chgr_type_t cur_chgr_type = chg_stm_get_chgr_type();

    chg_print_level_message(CHG_MSG_INFO, "CHG_PLT:get_chgr_type_from_usb cur_stat=%d,cur_chg_mode=%d,cur_chgr_type=%d\n",
            cur_stat,cur_chg_mode,cur_chgr_type);
    chg_print_level_message(CHG_MSG_INFO, "CHG_PLT:get_chgr_type_from_usb plug=%d,chg_type=%d\n",
                            plug,chg_type);

    mlog_print(MLOG_CHG, mlog_lv_info, "charger type %s(%d) %s detected.\n",
               get_chgr_name_by_id(chg_type), chg_type,
               plug ? "insertion" : "removal");

    if(TRUE == chg_is_ftm_mode())
    {
#if (MBB_CHG_WIRELESS == FEATURE_ON)
        if(CHG_WIRELESS_CHGR == chg_type)
        {
            wireless_mmi_test_proc(plug);
            return CHG_CHGR_INVALID;
        }
#endif /*defined(MBB_CHG_WIRELESS)*/

#if (MBB_CHG_EXTCHG == FEATURE_ON)
        if(CHG_EXGCHG_CHGR == chg_type)
        {
            /*USB ID�������MMI���*/
            if(1 == plug)
            {
                extchg_mmi_test_proc();
                return CHG_CHGR_INVALID;
            }
            /*USB ID�γ�����USB�����ӿ�D+ D-ֱ������������HS_ID*/
            else
            {
                return CHG_CHGR_INVALID;
            }
        }
#endif/*defined(MBB_CHG_EXTCHG)*/
        return CHG_CHGR_INVALID;
    }
    /*�����е����Ĳ����������У���˲���Ӧ����¼�*/
    if(CHG_SUPPLY_MODE == cur_chg_mode)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_PLT: cur_chg_mode = CHG_SUPPLY_MODE!\n ");
        return CHG_USB_HOST_PC;
    }

    /*���������в������������Ҳ���ܽ���״̬�л�����ֹ��ʱ��δ���屻ʹ�õ��µ�������*/
    if(TRUE == is_in_update_mode())
    {
        return CHG_USB_HOST_PC;
    }
    /*�����紦��*/
#if (MBB_CHG_EXTCHG == FEATURE_ON)
    if(CHG_EXGCHG_CHGR == chg_type)
    {
        chg_extchg_config_data_init();
        if (plug)
        {
            chg_extchg_insert_proc();
        }
        else
        {
            chg_extchg_remove_proc();
        }
        return CHG_EXGCHG_CHGR;
    }
#endif
    /*���ڳ�紦��*/
    chg_stm_set_chgr_type(chg_type);
    if (plug)
    {
#if (MBB_CHG_WIRELESS == FEATURE_ON)
        if(CHG_WIRELESS_CHGR == chg_type)
        {
            chg_stm_set_wireless_online_st(TRUE);
        }
#endif
        if(CHG_CHGR_UNKNOWN == chg_type)
        {
            chg_start_chgr_type_checking();
        }
#if (MBB_CHG_HIGH_VOLT_BATT == FEATURE_ON)
        if(CHG_500MA_WALL_CHGR == chg_type)
        {
            chg_hw_para_updated = 1;
        }
#endif
        chg_send_msg_to_main(CHG_CHARGER_IN_EVENT);
    }
    else
    {
#if (MBB_CHG_WIRELESS == FEATURE_ON)
        if(CHG_WIRELESS_CHGR == chg_type)
        {
            chg_stm_set_wireless_online_st(FALSE);
        }
#endif
#if (MBB_CHG_HIGH_VOLT_BATT == FEATURE_ON)
        chg_hw_para_updated = 0;
#endif
        chg_send_msg_to_main(CHG_CHARGER_OUT_EVENT);
    }

    return (chg_chgr_type_t)chg_type;
}


void chg_lcd_display(CHG_BATT_DISPLAY_TYPE disp_type)
{
    switch(disp_type)
    {
        case CHG_DISP_OK:
            //LCD�����ӿڣ�����ֲ��Ա����ʵ�������װ��
            break;
        case CHG_DISP_FAIL:
            //LCD�����ӿڣ�����ֲ��Ա����ʵ�������װ��
            break;
        case CHG_DISP_BATTERY_LOWER:
            //LCD�����ӿڣ�����ֲ��Ա����ʵ�������װ��
            break;
        case CHG_DISP_BATTERY_BAD:
            //LCD�����ӿڣ�����ֲ��Ա����ʵ�������װ��
            break;
        case CHG_DISP_OVER_HEATED:
            //LCD�����ӿڣ�����ֲ��Ա����ʵ�������װ��
            break;
        case CHG_DISP_TEMP_LOW:
            //LCD�����ӿڣ�����ֲ��Ա����ʵ�������װ��
            break;
        default:
            chg_print_level_message( CHG_MSG_ERR,"CHG_PLT:chg_lcd_display->disp_type invalid!!!\r\n ");
            break;
    }
    return;
}


void chg_led_display(CHG_BATT_DISPLAY_TYPE disp_type)
{
    switch(disp_type)
    {
        case CHG_DISP_OK:
        case CHG_DISP_FAIL:
            //logָʾ���ݲ�֧��(���Ʋ�ƷĿǰ���ǿɲ�ж���);
            chg_print_level_message( CHG_MSG_ERR,"CHG_PLT:chg_led_display->led product not support!!!\r\n ");
            break;
        case CHG_DISP_BATTERY_LOWER:
            /*�������ƽӿڣ���Ƴ���������Ϩ��*/
            break;
        case CHG_DISP_BATTERY_BAD:
        case CHG_DISP_OVER_HEATED: /*ָ���¹ػ�����ͣ��*/
        case CHG_DISP_TEMP_LOW: /*ָ���¹ػ�����ͣ��*/
            /*�����̵�ȫ���ӿ�*/
            break;
        default:
            chg_print_level_message( CHG_MSG_ERR,"CHG_PLT:chg_led_display->disp_type invalid!!!\r\n ");
            break;
    }
    return;
}


void chg_display_interface(CHG_BATT_DISPLAY_TYPE disp_type)
{
#if (MBB_CHG_LCD == FEATURE_ON)
    chg_lcd_display(disp_type);
#elif (MBB_CHG_LED == FEATURE_ON)
    chg_led_display(disp_type);
#endif

    return;
}

/******************************************************************************
  Function      batt_volt_calib_atoi
  Description   ���ַ��������ַ�'0'���ַ�'9'��ɵ����ݶ�ת��Ϊ����
  Input         *name: ��Ҫ����ת�����ַ�����ĵ�ַ
  Output        N/A
  Return        val  : ��ת�������ɵ����α�������
  Others        N/A
******************************************************************************/
static int batt_volt_calib_atoi(char *name)
{
    int val = 0;

    for (;; name++)
    {
        switch (*name)
        {
            case '0' ... '9':
            val = ATOI_CONVERT_NUM * val + (*name - '0');
            break;
            default:
            return val;
        }
    }
}


/***************Note:ƽ̨��ش��룬����ƽ̨����Ҫ��ӣ��е�ƽ̨��9x25��Ҫ
              ��ֲ��Ա������Ҫ����ӻ����Ƴ��±ߺ�������***************************/
void chg_batt_volt_calib_init(void)
{
#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
    int32_t ret = 0;
    VBAT_CALIBRATION_TYPE vbatt_calib_value;

    memset((void *)&vbatt_calib_value, 0, sizeof(VBAT_CALIBRATION_TYPE));

    ret = bsp_nvm_read(NV_BATT_VOLT_CALI_I, &vbatt_calib_value, sizeof(VBAT_CALIBRATION_TYPE));
    if(0 == ret)
    {
        g_vbatt_max = vbatt_calib_value.max_value;
        g_vbatt_min = vbatt_calib_value.min_value;

        chg_print_level_message( CHG_MSG_ERR,"read calibrate value successs! max=%d,min=%d\n", 
        g_vbatt_max,g_vbatt_min,0);
    }
    else
    {
        chg_print_level_message(CHG_MSG_ERR,"read chg nv failed when read check value\n");
        return;
    }
    if(g_vbatt_max <= g_vbatt_min)
    {
        chg_print_level_message( CHG_MSG_ERR,"CHG_PLT:chg_batt_volt_calib_init->max min value error!!!\r\n ");
        return;
    }
    /*��У׼��ʼ����־λ*/
    g_is_batt_volt_calib_init = TRUE;

#endif    

#if 0
    mm_segment_t old_fs = {0};
    struct file *fp_v_low = NULL;
    struct file *fp_v_high = NULL ;
    int bat_low = 0;
    int bat_high = 0;
    loff_t pos_v_low = 0;
    loff_t pos_v_high = 0;
    char bat_vol_low[BAT_VOL_SIZE + 1] = {0};
    char bat_vol_high[BAT_VOL_SIZE + 1] = {0};

    fp_v_low = filp_open("/data/voltage_low", O_RDONLY, 0);
    if (IS_ERR(fp_v_low))
    {
        fp_v_low = NULL;
        chg_print_level_message( CHG_MSG_INFO,"CHG_DEBUG: Open Bat vol Low file failed!\n");
        return;
    }
    pos_v_low = fp_v_low->f_pos;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    vfs_read(fp_v_low, bat_vol_low, BAT_VOL_SIZE, &pos_v_low);

    set_fs(old_fs);

    filp_close(fp_v_low, NULL);
    fp_v_high = filp_open("/data/voltage_high", O_RDONLY, 0);
    if (IS_ERR(fp_v_high))
    {
        fp_v_high = NULL;
        chg_print_level_message( CHG_MSG_ERR,"CHG_DEBUG: Open Bat vol High file failed!\n");
        return;
    }
    pos_v_high = fp_v_high->f_pos;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    vfs_read(fp_v_high, bat_vol_high, BAT_VOL_SIZE, &pos_v_high);

    set_fs(old_fs);

    filp_close(fp_v_high, NULL);

    bat_low = batt_volt_calib_atoi(bat_vol_low);
    bat_high = batt_volt_calib_atoi(bat_vol_high);

    chg_print_level_message( CHG_MSG_ERR,"CHG_DEBUG: bat_low = %d!\n",bat_low);
    chg_print_level_message( CHG_MSG_ERR,"CHG_DEBUG: bat_high = %d!\n",bat_high);

    g_vbatt_min = bat_low;
    g_vbatt_max = bat_high;

    if(g_vbatt_max <= g_vbatt_min)
    {
        chg_print_level_message( CHG_MSG_ERR,"CHG_PLT:chg_batt_volt_calib_init->max min value error!!!\r\n ");
        return;
    }

    /*��У׼��ʼ����־λ*/
    g_is_batt_volt_calib_init = TRUE;
    
#endif
}


int32_t chg_calc_batt_volt_calib_value(int32_t orig_val)
{
    int32_t rtn_vbat_val = 0;
    if(FALSE == g_is_batt_volt_calib_init)
    {
        chg_print_level_message( CHG_MSG_INFO,"CHG_PLT:calib is not init!!!\r\n ");
        return orig_val;
    }
    /*�����ص�ѹУ׼ֵ*/
    rtn_vbat_val = CHG_BATT_CALI_MIN_VOLT + (orig_val - g_vbatt_min)
                * (CHG_BATT_CALI_MAX_VOLT - CHG_BATT_CALI_MIN_VOLT)
                / (g_vbatt_max - g_vbatt_min);
    return rtn_vbat_val;
}


int32_t chg_get_volt_from_adc(CHG_PARAMETER_ENUM param_type)
{

/***************Note:ƽ̨��ش��룬����ƽ̨����Ҫ��ӣ��е�ƽ̨��9x25��Ҫ
              ��ֲ��Ա������Ҫ����ӻ����Ƴ��±ߺ�������***************************/

#if defined(CONFIG_HKADC)
    int ret = 0;
    int32_t rtn_vbat_val = 0;
    int tmp_ret = -1;
    u16 tmp_rtn_vbat_val = 0;



    if (CHG_PARAMETER__BATTERY_VOLT == param_type)
    {
        /*��ص�ѹʹ�ÿ��ؼ�*/
#if (MBB_CHG_COULOMETER == FEATURE_ON)
        rtn_vbat_val = bsp_coul_voltage();
        chg_print_level_message( CHG_MSG_DEBUG,"CHG:VBAT = %d\n", rtn_vbat_val,0,0);
        
#elif (MBB_CHG_BQ27510 == FEATURE_ON)
        rtn_vbat_val = hisi_battery_voltage();
#else
    tmp_ret = bsp_hkadc_convert(CHG_BATT_VOLT_HKADC_ID, &tmp_rtn_vbat_val);
    rtn_vbat_val = (int32_t)(tmp_rtn_vbat_val + tmp_rtn_vbat_val);
    if (tmp_ret < 0)
        {
        chg_print_level_message( CHG_MSG_ERR,"fail to convert, return value %d\n", 
                                            tmp_ret,0,0);
        }
    else
        {
       chg_print_level_message( CHG_MSG_DEBUG,"CHG:VBAT = %d\n", rtn_vbat_val,0,0);
        }
    

#endif
    }
    else if (CHG_PARAMETER__BATT_THERM_DEGC == param_type)
    {
        ret = bsp_hkadc_convert(CHG_BATT_THERM_HKADC_ID,&rtn_vbat_val);
        if(ret)
        {
            chg_print_level_message( CHG_MSG_ERR,"chg_boot_get_volt_from_adc: get adc value failed!!!\r\n ",0,0,0 );
            return ret;
        }
        chg_print_level_message( CHG_MSG_DEBUG,"CHG:BAT_TEMP = %d\n", rtn_vbat_val,0,0);

	}
    else if (CHG_PARAMETER__VBUS_VOLT == param_type)
    {
        ret = bsp_hkadc_convert(CHG_VBUS_VOLT_HKADC_ID,&rtn_vbat_val);
        if(ret)
        {
            chg_print_level_message( CHG_MSG_ERR,"chg_boot_get_volt_from_adc: get adc value failed!!!\r\n ",0,0,0 );
            return ret;
        }
        chg_print_level_message( CHG_MSG_DEBUG,"CHG:VBUS = %d\n", rtn_vbat_val,0,0);

    }
    else if (CHG_PARAMETER__BATTERY_ID_VOLT == param_type)
    {
        ret = bsp_hkadc_convert(CHG_BATT_ID_VOLT_HKADC_ID,&rtn_vbat_val);
        if(ret)
        {
            chg_print_level_message( CHG_MSG_ERR,"chg_boot_get_volt_from_adc: get adc value failed!!!\r\n ",0,0,0 );
            return ret;
        }
        chg_print_level_message( CHG_MSG_DEBUG,"CHG:VBUS = %d\n", rtn_vbat_val,0,0);

    }
     /*USB�±�*/ 
#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
    else if ( CHG_PARAMETER__USB_PORT_TEMP_DEGC == param_type)
    {
        ret = bsp_hkadc_convert(CHG_USB_TEMP_CHAN, &tmp_rtn_vbat_val);
        if (ret)
        {
            chg_print_level_message( CHG_MSG_ERR,"chg_boot_get_usb_volt_from_adc: get adc value failed!!!\r\n ",0,0,0 );
            return ret;
        }
        rtn_vbat_val = (int32_t)tmp_rtn_vbat_val;
        chg_print_level_message( CHG_MSG_DEBUG,"CHG:USB_TEMP_VOLT = %d\n", rtn_vbat_val,0,0);
    } 
#endif
    else
    {
        chg_print_level_message( CHG_MSG_INFO,"VADC bad param_type %d\n", param_type,0,0);
        return 0;
    }

    return rtn_vbat_val;
#endif


#if 0 
    struct qpnp_vadc_result result = {0};
    int32_t rtn_vadc_val = 0;
    int32_t rc = -1;
    struct qpnp_vadc_chip *vadc;
    /*��ȡ��ص�ѹ*/
    vadc = qpnp_get_vadc(&g_i2c_client->dev, "charger");
    if (IS_ERR(vadc))
    {
        chg_print_level_message( CHG_MSG_ERR,"CHG_PLT:get qpnp_vadc_chip error!!!\r\n ");
    }

    if (CHG_PARAMETER__BATTERY_VOLT == param_type)
    {
        rc = qpnp_vadc_read(vadc,VBAT_DETECT, (struct qpnp_vadc_result *)&result);
        if (rc)
        {
            chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT:VADC read VBAT_DETECT error with %d\n", rc);
            return 0;
        }
        result.physical = (int32_t)result.physical * BAT_VOL_MUIT_NUMBER;
    }
    /*��ȡ����ڲ�NTC�¶�*/
    else if (CHG_PARAMETER__BATT_THERM_DEGC == param_type)
    {
        rc = qpnp_vadc_read(vadc,BATTEMP_DETECT, (struct qpnp_vadc_result *)&result);
        if (rc)
        {
            chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT:VADC read BATTEMP_DETECT error with %d\n", rc);
            return 0;
        }
    }
    /*��ȡVBUS��ѹ*/
    else if (CHG_PARAMETER__VBUS_VOLT == param_type)
    {
        rc = qpnp_vadc_read(vadc,VBUS_DETECT, (struct qpnp_vadc_result *)&result);
        if (rc)
        {
            chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT:VADC read VBUS_DETECT error with %d\n", rc);
            return 0;
        }
    }
    else
    {
        chg_print_level_message( CHG_MSG_INFO,"CHG_PLT:VADC bad channel %d\n", param_type);
        return 0;
    }

    /*result.measurement��ȡֵΪ��V,����ת��ΪmV*/
    do_div(result.physical, MICRO_TO_MILLI_V);
    rtn_vadc_val = (int32_t)(result.physical);

    return rtn_vadc_val;
#endif
}


int32_t chg_get_batt_volt_value(void)
{
    int32_t vbatt_from_adc = 0;
    int32_t rtn_vbatt_value = 0;
    if (FALSE == g_is_batt_volt_calib_init)
    {
        chg_batt_volt_calib_init();
    }

    vbatt_from_adc = chg_get_volt_from_adc(CHG_PARAMETER__BATTERY_VOLT);
    rtn_vbatt_value = chg_calc_batt_volt_calib_value(vbatt_from_adc);

    return rtn_vbatt_value;
}


int32_t chg_volt_to_temp (int32_t volt_value, CHG_TEMP_ADC_TYPE *AdcTable, uint32_t table_size)
{
    boolean   desending_flag = TRUE;
    uint32_t  idx = 0;

    if(NULL == AdcTable)
    {
        chg_print_level_message( CHG_MSG_ERR,"CHG_PLT: invalid input para!!!\r\n ");
        /*ֱ�ӷ��ص�ѹ*/
        return volt_value;
    }

    /*�жϱ��ǰ���ѹֵ����or����*/
    if(1 < table_size)
    {
        if(AdcTable[0].voltage < AdcTable[1].voltage)
        {
            desending_flag = FALSE;
        }
    }

    /*��������ڱ���е�λ��*/
    while(idx < table_size)
    {
        if((TRUE == desending_flag) && (AdcTable[idx].voltage < volt_value))
        {
            break;
        }
        else if((FALSE == desending_flag) && (AdcTable[idx].voltage > volt_value))
        {
            break;
        }
        else
        {
            idx++;
        }
    }

    /*����ֵ�жϣ�����ֵ��ʽ���*/
    if(0 == idx)
    {
        return AdcTable[0].temperature;
    }
    else if(table_size == idx)
    {
        return AdcTable[table_size - 1].temperature;
    }
    else
    {
        /*��ֹб�ʼ���Ƿ�*/
        if(AdcTable[idx - 1].voltage == AdcTable[idx].voltage)
        {
            chg_print_level_message( CHG_MSG_ERR,"CHG_PLT: slop invalid!!!\r\n ");
            return AdcTable[idx - 1].temperature;
        }

        return (((AdcTable[idx - 1].temperature - AdcTable[idx].temperature )
            * (volt_value - AdcTable[idx - 1].voltage)) / (AdcTable[idx - 1].voltage - AdcTable[idx].voltage)
            + AdcTable[idx - 1].temperature);
    }
}


int32_t chg_get_temp_value(CHG_PARAMETER_ENUM param_type)
{
    int32_t voltage_from_adc = 0;
    int32_t rtn_temp_value = 0;

    voltage_from_adc = chg_get_volt_from_adc(param_type);

    chg_print_level_message(CHG_MSG_DEBUG,"CHG_PLT:voltage_from_adc =%d \r\n ",voltage_from_adc);

    switch(param_type)
    {
        case CHG_PARAMETER__BATT_THERM_DEGC:
        {
#if (MBB_CHG_BQ27510 == FEATURE_ON)
            rtn_temp_value = hisi_battery_temperature();
#else
            rtn_temp_value = chg_volt_to_temp(voltage_from_adc, g_adc_batt_therm_map,
                                        sizeof(g_adc_batt_therm_map) / sizeof(g_adc_batt_therm_map[0]));
#endif
            chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT:rtn_temp_value =%d \r\n ",rtn_temp_value);

            break;
        }
        /*�弶�¶ȣ���Ӧ�ĵ�ѹ�¶ȶ��ձ�ʹ�õ�صĵ�ѹ�¶ȶ��ձ���ͬ��Ʒ������Ҫ����
         ��Ӱ弶�¶ȵĵ�ѹ�¶ȶ��ձ�*/
        case CHG_PARAMETER__BATT_BOT_THERM_DEGC:
        {
            rtn_temp_value = chg_volt_to_temp(voltage_from_adc, g_adc_battbtm_therm_map,
                                        sizeof(g_adc_battbtm_therm_map) / sizeof(g_adc_battbtm_therm_map[0]));
            break;
        }
        /*USB�±�*/ 
#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
        case CHG_PARAMETER__USB_PORT_TEMP_DEGC:
        {
            rtn_temp_value = chg_volt_to_temp(voltage_from_adc, g_adc_usb_therm_map,
                                        sizeof(g_adc_usb_therm_map) / sizeof(g_adc_usb_therm_map[0]));
            chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT:USB_TEMP:rtn_temp_value =%d.\n",rtn_temp_value);
            break;
        } 
#endif
        default:
        {
            /*�ȷ��ص�ѹֵ*/
            rtn_temp_value = voltage_from_adc;
            break;
        }
    }

    return rtn_temp_value;
}

#if (MBB_CHG_EXTCHG == FEATURE_ON)
/*���º�����ͬƽ̨�ڲ�ʵ�ֲ�ͬ����ֲ��Ա��ע��*/

int extchg_gpio_init(void)
{
#if 0
    if (!gpio_is_valid(EXTCHG_CONTROL_GPIO_EN1))         /* */
    {
        chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT: set EXTCHG_EN1 GPIO59 failed!!\r\n ");
        return -1;
    }
#if (FEATURE_ON != MBB_CHG_PLATFORM_V7R2)
    if (!gpio_is_valid(EXTCHG_CONTROL_GPIO_EN2))         /* */
    {
        chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT: set EXTCHG_EN2 GPIO60 failed!!\r\n ");
        return -1;
    }
#endif
    if (gpio_request(EXTCHG_CONTROL_GPIO_EN1, "EXTCHG_EN1"))         /* */
    {
        chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT: request EXTCHG_EN1 GPIO59 failed!!\r\n ");
        return -1;
    }
#if (FEATURE_ON != MBB_CHG_PLATFORM_V7R2)
    if (gpio_request(EXTCHG_CONTROL_GPIO_EN2, "EXTCHG_EN2"))         /* */
    {
        chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT: request EXTCHG_EN2 GPIO60 failed!!\r\n ");
        return -1;
    }
#endif
#endif
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    if (!gpio_is_valid(EXTCHG_CHG_ENABLE))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: set EXTCHG_CHG_ENABLE GPIO152 failed!!\r\n ");
        return -1;
    }
    if (!gpio_is_valid(RE_ILIM_1A_GPIO))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: set RE_ILIM_1A_GPIO GPIO136 failed!!\r\n ");
        return -1;
    }
    if (!gpio_is_valid(RE_ILIM_2A_GPIO))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: set RE_ILIM_2A_GPIO GPIO137 failed!!\r\n ");
        return -1;
    }
    if (!gpio_is_valid(OTG_ON_CTRL_GPIO))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: set OTG_ON_CTRL_GPIO GPIO159 failed!!\r\n ");
        return -1;
    }
    if (!gpio_is_valid(EXTCHG_OTG_DET_GPIO))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: set EXTCHG_OTG_DET_GPIO GPIO5 failed!!\r\n ");
        return -1;
    }
    if (!gpio_is_valid(USB_GPIO_DM))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: set USB_GPIO_DM GPIO54 failed!!\r\n ");
        return -1;
    }
    if (!gpio_is_valid(USB_GPIO_DP))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: set USB_GPIO_DP GPIO55 failed!!\r\n ");
        return -1;
    }

    if (gpio_request(EXTCHG_OTG_DET_GPIO, "EXTCHG_OTG_DET_GPIO"))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: request EXTCHG_OTG_DET_GPIO GPIO5 failed!!\r\n ");
        return -1;
    }
    if (gpio_request(USB_GPIO_DM, "USB_GPIO_DM"))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: request USB_GPIO_DM GPIO54 failed!!\r\n ");
        return -1;
    }
    if (gpio_request(USB_GPIO_DP, "USB_GPIO_DP"))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: request USB_GPIO_DP GPIO55 failed!!\r\n ");
        return -1;
    }
#if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937) 
    if (gpio_request(EXTCHG_CHG_ENABLE, "EXTCHG_CHG_ENABLE"))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: request EXTCHG_CHG_ENABLE GPIO5 failed!!\r\n ");
        return -1;
    }
    if (gpio_request(OTG_ON_CTRL_GPIO, "OTG_ON_CTRL_GPIO"))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: request OTG_ON_CTRL_GPIO GPIO54 failed!!\r\n ");
        return -1;
    }
    if (gpio_request(RE_ILIM_1A_GPIO, "RE_ILIM_1A_GPIO"))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: request RE_ILIM_1A_GPIO GPIO55 failed!!\r\n ");
        return -1;
    }
    if (gpio_request(RE_ILIM_2A_GPIO, "RE_ILIM_2A_GPIO"))
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "CHG_PLT: request RE_ILIM_2A_GPIO GPIO55 failed!!\r\n ");
        return -1;
    }

#endif
#endif
    return 0;
}

void extchg_gpio_control(uint32_t gpio,int32_t level)
{
#ifdef BSP_CONFIG_BOARD_E5_E5786
#else
   gpio_direction_output(gpio,level);
#endif
}

#endif/*MBB_CHG_EXTCHG*/


#if (MBB_CHG_WIRELESS == FEATURE_ON)
/*���º�����ͬƽ̨�ڲ�ʵ�ֲ�ͬ����ֲ��Ա��ע��*/

int wireless_gpio_init(void)
{
    if (!gpio_is_valid(WIRELESS_CONTROL_GPIO_EN1))         /* */
    {
        chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT: set WIRELESS_EN1 GPIO59 failed!!\r\n ");
        return -1;
    }
    if (!gpio_is_valid(WIRELESS_CONTROL_GPIO_EN2))         /* */
    {
        chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT: set WIRELESS_EN2 GPIO60 failed!!\r\n ");
        return -1;
    }
    if (gpio_request(WIRELESS_CONTROL_GPIO_EN1, "WIRELESS_EN1"))         /* */
    {
        chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT: request WIRELESS_EN1 GPIO59 failed!!\r\n ");
        return -1;
    }
    if (gpio_request(WIRELESS_CONTROL_GPIO_EN2, "WIRELESS_EN2"))         /* */
    {
        chg_print_level_message( CHG_MSG_DEBUG,"CHG_PLT: request WIRELESS_EN2 GPIO60 failed!!\r\n ");
        return -1;
    }
    return 0;
}

void wireless_gpio_control(uint32_t gpio,int32_t level)
{
   gpio_direction_output(gpio,level);
}

#endif/*MBB_CHG_WIRELESS*/


#ifndef CHG_STUB
boolean is_in_update_mode(void)
{
    huawei_smem_info *smem_data = NULL;
    smem_data = (huawei_smem_info *)SRAM_DLOAD_ADDR;


    if(SMEM_DLOAD_FLAG_NUM == smem_data->smem_dload_flag)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
#else
boolean is_in_update_mode(void)
{
    return FALSE;
}
#endif

/**********************************************************************
�� �� ��  : boolean chg_config_para_read(int32_t num)
��������  : ���������ò���
�������  : none
�������  : �ޡ�
�� �� ֵ  : �ޡ�
ע������  : �ɸ���ƽ̨��ͬ�޸�ʵ�ַ���������NV�ȡ�
***********************************************************************/
boolean chg_config_para_read(uint16_t nvID, void *pItem, uint32_t ulLength)
{
    /***************Note:ƽ̨��ش��룬����ʵ�ֿɸ���ƽ̨��ͬʵ�֣���ŵ翪��
                           ��Ա��Ҫ����ƽ̨�ṩ�ӿ�������з�װ���䣬V7R2ƽ̨����ʵ��********************/
    if(bsp_nvm_read(nvID,pItem,ulLength))
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:READ NV ERROR!!!\n");
        return CHG_ERROR;
    }
    else
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:READ NV OK!!!\n");
        return CHG_OK;
    }
}

#if (MBB_CHG_COMPENSATE == FEATURE_ON)

void chg_set_fact_release_mode(boolean on)
{
#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
/*�˴���Ҫ���V7R2ƽ̨�����ڴ��д�����ߺ˼�ͨ��֪ͨC��*/
#else
    huawei_smem_info *smem_data = NULL;

    smem_data = (huawei_smem_info *)SMEM_HUAWEI_ALLOC(SMEM_ID_VENDOR0 , sizeof(huawei_smem_info ));
    if(NULL == smem_data)
    {
        chg_print_level_message( CHG_MSG_ERR,"CHG_PLT: smem alloc fail!!!\r\n ");
        return;
    }

    if (TRUE == on)
    {
        smem_data->smem_fact_chg_flag = SMEM_FACT_RELEASE_ON;
    }
    else
    {
        smem_data->smem_fact_chg_flag = SMEM_FACT_RELEASE_OFF;
    }
    
    if(0 == (smsm_get_state(SMSM_APPS_STATE) & SMSM_VENDOR))
    {
        smsm_change_state(SMSM_APPS_STATE, 0, SMSM_VENDOR);
        chg_print_level_message( CHG_MSG_ERR,"CHG_PLT: smem 0->1!!!\r\n ");
    }
    else
    {
        smsm_change_state(SMSM_APPS_STATE, SMSM_VENDOR, 0);
        chg_print_level_message( CHG_MSG_ERR,"CHG_PLT: smem 1->0!!!\r\n ");
    }
#endif
    
    return;
}

void chg_get_hw_version_id(void)
{
}
#endif

#define CHG_TEST_ECALL_COMMANDS_EXTEND

#if defined(CHG_TEST_ECALL_COMMANDS_EXTEND)
extern int32_t chg_get_sys_batt_temp(void);
extern int32_t chg_get_sys_batt_volt(void);

/*================= ECALL FUNCTIONS for DFT =====================*/
int32_t chg_test_get_sys_batt_temp(void)
{
    int32_t tbat_sys = chg_get_sys_batt_temp();

    /*Set to emergency level to show the msg always.*/
    printk(KERN_EMERG "Battery temperature smoothed: %d'C.\n", tbat_sys);
    return tbat_sys;
}

int32_t chg_test_get_sys_batt_volt(void)
{
    int32_t vbat_sys = chg_get_sys_batt_volt();
    
    /*Set to emergency level to show the msg always.*/
    printk(KERN_EMERG "Battery voltage smoothed: %dmV.\n", vbat_sys);
    return vbat_sys;
}

int32_t chg_test_get_volt_from_adc(CHG_PARAMETER_ENUM chan)
{
    int32_t adc_value;
    
    /*Set to emergency level to show the msg always.*/
    if (CHG_PARAMETER__BATTERY_VOLT != chan &&  CHG_PARAMETER__VBUS_VOLT != chan)
    {
        printk(KERN_EMERG "Invalid channel %d.\n", (int)chan);
        printk(KERN_EMERG "HELP: 0: VBat; 2: VBus;\n");
        return (-1);
    }    

    adc_value = chg_get_volt_from_adc(chan);
    printk(KERN_EMERG "%s is %dmV.\n", 
        (CHG_PARAMETER__BATTERY_VOLT == chan) ? "VBat" : "VBus", adc_value);

    return adc_value;
}

int32_t chg_test_get_temp_value(CHG_PARAMETER_ENUM chan)
{
    int32_t tmp_value;
    
    /*Set to emergency level to show the msg always.*/
    if (CHG_PARAMETER__BATT_THERM_DEGC != chan)
    {
        printk(KERN_EMERG "Invalid channel %d.\n", (int)chan);
        printk(KERN_EMERG "HELP: 1: Battery Temperature;\n");
        return (-1);
    }    

    tmp_value = chg_get_temp_value(chan);
    printk(KERN_EMERG "Tbat is %d'C.\n", tmp_value);

    return tmp_value;
}

int32_t chg_test_get_batt_volt_value(void)
{
    int32_t vbat_cali = chg_get_batt_volt_value();
    
    /*Set to emergency level to show the msg always.*/
    printk(KERN_EMERG "Battery voltage calibrated: %dmV.\n", vbat_cali);
    return vbat_cali;
}
#endif /*CHG_TEST_ECALL_COMMANDS_EXTEND*/
