

/*===========================================================================
                       linuxϵͳͷ�ļ�
===========================================================================*/
#ifdef WLAN_AT_API_APP_BUILD
    #include <unistd.h>
    #include <sys/wait.h>
#else
    #include <linux/module.h>
    #include <linux/kernel.h>
    #include <linux/delay.h>
    #include <linux/ctype.h>
    #include <linux/fs.h>
    #include <asm/uaccess.h>
    #include "wlan_if.h"
#endif /*WLAN_AT_API_APP_BUILD*/

/*===========================================================================
                       ƽ̨ͷ�ļ�
===========================================================================*/
#include "wlan_at.h"
#include "wlan_utils.h"
#include "bsp_version.h"

/*===========================================================================
                       �궨��
===========================================================================*/
#define WLAN_AT_SSID_SUPPORT    1           /* ֧�ֵ�SSID���� */
#define WLAN_AT_KEY_SUPPORT     5           /* ֧�ֵķ����� */
#define WLAN_AT_MODE_SUPPORT    "2,3,4"   /* ֧�ֵ�ģʽ(cw:0/a:1/b:2/g:3/n:4/ac:5) */
#define WLAN_AT_BAND_SUPPORT    "0,1"       /* ֧�ֵĴ���(20M:0/40M:1/80M:2/160M:3) */
#if defined(FEATURE_HUAWEI_MBB_RTL8189)
    #define WLAN_AT_TSELRF_SUPPORT  "0"           /* ֧��1*1������ */
#elif defined(FEATURE_HUAWEI_MBB_RTL8192)
    #define WLAN_AT_TSELRF_SUPPORT  "0,1"         /* ֧��2*2˫���� */
#endif

#define MAX_POW_INDEX    63           /* �����indexֵ */

/* ���֧���ŵ����� */
#define WLAN_RTL_CHANNEL_24G_MAX (14)

/*WIFI���ʵ�������*/
#define WLAN_AT_WIFI_POWER_MIN           (-15)
#define WLAN_AT_WIFI_POWER_MAX           (30)

/*cmd�ַ�������*/
#define WIFI_CMD_MAX_SIZE   256
#define WIFI_AP_INTERFACE   "wlan0"

/* ��CE��֤������TXռ�ձ�100% */
#define WLAN_AT_TX_FULL_DUTY_RATIO 255

/*WiFiоƬʹ�ܶ��Լ��*/
#define IS_CW_MODE(wifi_mode) ((AT_WIMODE_80211b == wifi_mode) ? AT_FEATURE_ENABLE : AT_FEATURE_DISABLE)

/*��WiFiоƬ�·���������*/
#define WIFI_TEST_CMD(cmd) do { \
    if (WLAN_SUCCESS != wlan_run_cmd(cmd)) \
    { \
        PLAT_WLAN_INFO("Run CMD Error!!!"); \
        return AT_RETURN_FAILURE; \
    } \
    if (NULL != strstr(cmd, " down")) \
    { \
        PLAT_WLAN_INFO("RX TX Status Clear!!!"); \
        g_wlan_at_data.WiTX = AT_FEATURE_DISABLE; \
        g_wlan_at_data.WiRX.onoff = AT_FEATURE_DISABLE; \
    } \
}while(0)

/*�򵥰��·�shell����*/
#define WIFI_SHELL_CMD(shell) do { \
    if (WLAN_SUCCESS != wlan_run_shell(shell)) \
    { \
        PLAT_WLAN_INFO("Run SHELL Error!!!"); \
        return AT_RETURN_FAILURE; \
    } \
}while(0)

/*WiFiоƬʹ�ܶ��Լ��*/
#define ASSERT_WiFi_OFF(ret) do { \
    if (AT_WIENABLE_OFF == g_wlan_at_data.WiEnable) \
    { \
        PLAT_WLAN_INFO("Exit on WiFi OFF"); \
        return ret; \
    } \
}while(0)

#define WIFI_TOOL_IWPRIV     "/system/bin/iwpriv"            /* iwpriv���� */
#define WIFI_TOOL_IFCONFIG   "/system/bin/busybox ifconfig"  /* ifconfig���� */

#define WIFI_POWER_DIFF_MIN (-7) 
#define WIFI_POWER_DIFF_MAX (8)

#if defined(FEATURE_HUAWEI_MBB_RTL8189)
    #define IS_TSELRF_VAILD(tselrf) ((AT_TSELRF_A == tselrf))
#elif defined(FEATURE_HUAWEI_MBB_RTL8192)
    #define IS_TSELRF_VAILD(tselrf) ((AT_TSELRF_A == tselrf) || (AT_TSELRF_B == tselrf))
#else
    #error "ERROR: NO DEFINED VAILD CHIP!!"
#endif

#ifdef MBB_ROUTER_QCT
    #define WLAN_CURRENT_TSELRF (IS_TSELRF_VAILD(WlanATGetTSELRF())? WlanATGetTSELRF() : AT_TSELRF_A)
#else
    #define WLAN_CURRENT_TSELRF (IS_TSELRF_VAILD(g_wlan_at_data.WiTselrf)? g_wlan_at_data.WiTselrf : AT_TSELRF_A)
#endif /* MBB_ROUTER_QCT */

/* ��������ǰ��֤RX/TX����ֹͣ״̬ */
#define WLAN_SET_RXTX_STOP() do { \
    if (AT_FEATURE_DISABLE != g_wlan_at_data.WiRX.onoff) \
    { \
        WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_arx stop"); \
        g_wlan_at_data.WiRX.onoff = AT_FEATURE_DISABLE; \
    } \
    if (AT_FEATURE_DISABLE != g_wlan_at_data.WiTX) \
    { \
        WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_ctx stop"); \
        g_wlan_at_data.WiTX = AT_FEATURE_DISABLE; \
    } \
}while(0)

/*===========================================================================
                       ���Ͷ���
===========================================================================*/
typedef enum
{
    AT_TSELRF_A   = 0,  /*��ƵA ·*/
    AT_TSELRF_B   = 1,  /*��ƵB ·*/
    AT_TSELRF_MAX      /*���ֵ*/
}WLAN_AT_TSELRF_TYPE;
typedef struct _AT_WIMODE_GLOBAL
{
    WLAN_AT_FEATURE_TYPE    cw_enable;  /* cwģʽʹ�� */
    WLAN_AT_WIMODE_TYPE     mode;       /*wifiЭ��ģʽ*/
}AT_WIMODE_GLOBAL_TYPE;
typedef struct _AT_WIFREQ_GLOBAL
{
    uint32               channel;       /*wifiƵ���Ӧ�ŵ�*/
    WLAN_AT_WIFREQ_STRU  freq;          /*wifiƵ����Ϣ*/
}AT_WIFREQ_GLOBAL_TYPE;
typedef struct _AT_WICAL_CH_POWER
{
    uint8 ch;
    uint8 data;
}AT_WICAL_CH_POWER_TYPE;
typedef struct _AT_WICAL_POWER
{
    AT_WICAL_CH_POWER_TYPE   cck[3];  /* 802.11b, ����У׼���и��ŵ� */
    AT_WICAL_CH_POWER_TYPE   ht40[3]; /* 40M, ����У׼���и��ŵ� */
    uint8   diffht20;                 /* 20M  diff*/
    uint8   diffofdm;                 /* ofdm  diff*/
    uint8   diffht40_2s;              /* 40M  2s  diff */
}AT_WICAL_POWER_TYPE;
typedef struct _AT_WICAL_GLOBAL
{
    WLAN_AT_FEATURE_TYPE    onoff;      /* У׼�л����� */
    
    AT_WICAL_POWER_TYPE    power[AT_TSELRF_MAX];
    uint8 power_onoff[AT_TSELRF_MAX];   /* ����efuse ��д��־λ */
    
    uint8   crystal;                    /* Ƶ�ʲ��� */
    uint8 crystal_onoff;                /* Ƶ�� efuse ��д��־λ */
    
    uint8   thermal;                    /* �¶Ȳ��� */
    uint8 thermal_onoff;                /* �¶�efuse ��д��־λ */
}AT_WICAL_GLOBAL_TYPE;
typedef struct tagWlanATGlobal
{
    WLAN_AT_WIENABLE_TYPE   WiEnable;       /*Ĭ�ϼ��ز���ģʽ*/
    AT_WIMODE_GLOBAL_TYPE   WiMode;
    WLAN_AT_WIBAND_TYPE     WiBand;         /* wifiЭ����ʽ*/
    AT_WIFREQ_GLOBAL_TYPE   WiFreq;         /* Ƶ�� */
    uint32                  WiDataRate;     /* wifi��������*/
    int32                   WiPow;          /* wifi���书��*/
    WLAN_AT_FEATURE_TYPE    WiTX;           /* wifi�����״̬*/
    WLAN_AT_WIRX_STRU       WiRX;           /* wifi���ջ�״̬*/
    WLAN_AT_WiPARANGE_TYPE  WiParange;      /*wifi��������ģʽ*/

    WLAN_AT_WICALTEMP_STRU  WiCalTemp;      /*wifi�¶�У׼*/
    /* У׼������Ϣ*/
    AT_WICAL_GLOBAL_TYPE WiCal;
    WLAN_AT_WICALDATA_STRU WiCalData;
    
    WLAN_AT_TSELRF_TYPE  WiTselrf;          /* �������� */
    
    WLAN_AT_WICALFREQ_STRU  WiCalFreq;      /* У׼Ƶ�� */
    WLAN_AT_WICALPOW_STRU   WiCalPow;       /* У׼���� */
    
} WLAN_AT_GLOBAL_ST;

typedef struct _WLAN_AT_WICAL_PWR_PARAM_SET
{
    const char * cck;
    const char * diff_th20;
    const char * diff_th20_ofdm;
    const char * diff_th40;
    const char * th40_1s;
    const char * diff_th40_2s;
}WLAN_AT_WICAL_PWR_PARAM_SET_TYPE;

/*===========================================================================
                       ȫ����Ϣ
===========================================================================*/
/*����WiFi��Ĭ�ϲ���*/
STATIC WLAN_AT_GLOBAL_ST g_wlan_at_data =
{   .WiEnable   = AT_WIENABLE_TEST,
    .WiMode     = {AT_FEATURE_DISABLE, AT_WIMODE_80211n},
    .WiBand     = AT_WIBAND_20M,
    .WiFreq     = {1, {2412, 0}}, /* ��ʼ��Ƶ�� */
    .WiDataRate = 5850,            /* ��ʼ������ */
    .WiPow      = 3175,            /* ��ʼ������ */
    .WiTX       = AT_FEATURE_DISABLE,
    .WiRX       = {AT_FEATURE_DISABLE, {0}, {0}},
    .WiParange  = AT_WiPARANGE_HIGH,
    .WiCalTemp  = {0, 0},
    .WiCal      = {   .onoff = AT_FEATURE_DISABLE            /* У׼�л����� */
                    , .power_onoff = {AT_FEATURE_DISABLE}    /* ����efuse ��д��־λ */
                    , .crystal = 0                           /* Ƶ�ʲ��� */
                    , .crystal_onoff = AT_FEATURE_DISABLE    /* Ƶ�� efuse ��д��־λ */
                    , .thermal = 0                           /* �¶Ȳ��� */
                    , .thermal_onoff = AT_FEATURE_DISABLE    /* �¶�efuse ��д��־λ */
                },
    .WiCalData  = {AT_WICALDATA_REL_IDX_POW, 0, AT_WIMODE_80211n, AT_WIFREQ_24G, AT_WIBAND_20M, 1, {0}},
    .WiTselrf   = AT_TSELRF_A,
    .WiCalFreq  = {AT_WICALFREQ_INDEX, 32},  /* ��ʼ��Ƶƫ��ʼֵ */
    .WiCalPow   = {AT_WICALPOW_POWER, 3175}, /* ��ʼ��У׼���� */
};

/*�ŵ��б�*/
const uint16 g_ausChannels[] = {2412,2417,2422,2427,2432,2437,2442,2447,2452,2457,2462,2467,2472,2484};

const WLAN_AT_WICAL_PWR_PARAM_SET_TYPE g_wical_pwr_param_set[] =
{
#if defined(FEATURE_HUAWEI_MBB_RTL8189)
    {.cck            = "HW_TX_POWER_CCK_A",
     .diff_th20      = NULL,
     .diff_th20_ofdm = "HW_TX_POWER_DIFF_HT20_OFDM",
     .th40_1s        = "HW_TX_POWER_HT40_1S_A",
     .diff_th40_2s   = NULL
    },
#else
    {.cck            = "HW_TX_POWER_CCK_A",
     .diff_th20      = "HW_TX_POWER_DIFF_HT20_A",
     .diff_th20_ofdm = "HW_TX_POWER_DIFF_HT20_OFDM_A",
     .th40_1s        = "HW_TX_POWER_HT40_1S_A",
     .diff_th40_2s   = "HW_TX_POWER_DIFF_HT40_2S_A"
    },
    {.cck            = "HW_TX_POWER_CCK_B",
     .diff_th20      = "HW_TX_POWER_DIFF_HT20_B",
     .diff_th20_ofdm = "HW_TX_POWER_DIFF_HT20_OFDM_B",
     .th40_1s        = "HW_TX_POWER_HT40_1S_B",
     .diff_th40_2s   = "HW_TX_POWER_DIFF_HT40_2S_B"
    },
#endif
};
/*����3���Ĵ���λ���ڿ���RX����*/
unsigned long g_dw_c14_value = 0;
unsigned long g_dw_c1c_value = 0;
unsigned char g_b_a07_value = 0;

/*===========================================================================
                       ����ʵ��
===========================================================================*/
/*****************************************************************************
 ��������  : RTL_POW_DIFF
 ��������  : ��ȡpowerֵ
 �������  : 
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
inline int32 RTL_POW_DIFF(int wtselrf, uint8 reg_idx)
{
    int pow_diff = ((reg_idx & (0x0F << (wtselrf * 4))) >> (wtselrf * 4)); /* ����ȡreg_idxֵ: A·ȡ��4λ��B·ȡ��4λ */
    return (pow_diff > 8 ? (pow_diff - 16) : pow_diff); /* diffȡֵ��ΧΪ -7 ~ 8 */
}
/*****************************************************************************
 ��������  : STATIC void WlanRegInforToDig(const char *nptr, const int byte_count, unsigned long *value)
 ��������  : �Ĵ�����ѯ�ַ���ת��Ϊ��������
 �������  : nptr:�ַ���ָ�룬byte_count:�ַ������ȣ�value���ַ�ת�������������
 �������  : NA
 �� �� ֵ  : NA
*****************************************************************************/
STATIC void WlanRegInforToDig(const char *nptr, const int byte_count, unsigned long *value)
{
    int i = 0;
    unsigned long byte_value = 0;
    if (NULL == nptr)
    {
        PLAT_WLAN_ERR("NULL Pointe");
        return ;
    }
    PLAT_WLAN_INFO(" nptr = %s, byte_count = %d", nptr, byte_count);
    /* ȥ�ո� */
    while (isspace(*nptr))
    {
        nptr++;
    }

    for(i = 0; i < byte_count; i++)
    {
        byte_value = 0;
        byte_value = (unsigned long)wlan_strtoi(nptr, NULL, WLAN_BASE10); /*��ȡ10������*/
        PLAT_WLAN_INFO(" byte_value = %0x, after offset byte_value = %0x", byte_value, byte_value << ((byte_count - i - 1) * 8));
        *value |= byte_value << ((byte_count - i - 1) * 8);
        PLAT_WLAN_INFO(" value = %0x ", *value);

        /* ȥ�ո� */
        if(i < byte_count - 1)
        {
            nptr +=3;
            while (isspace(*nptr))
            {
                nptr++;
            }
            PLAT_WLAN_INFO(" nptr = %s ", nptr);
        }
    }
    return;

}

/*****************************************************************************
 ��������  : STATIC int WlanReadRegInfor(const char *cmd, char *value)
 ��������  : ��ȡ����ִ�еĽ���ַ���
 �������  : cmd����Ҫִ�е����value���ַ�����ĳ���
 �������  : NA
 �� �� ֵ  : �ɹ�����value�ĳ��ȣ�ʧ�ܷ���0
*****************************************************************************/
STATIC int WlanReadRegInfor(const char *cmd, char *value)
{
    const char *info_key = "read_reg:";
    char *p_buf = NULL;
    int i=0;
    char buf[WIFI_CMD_MAX_SIZE] = {0};
    char cmd_buf[WIFI_CMD_MAX_SIZE] = {0};

    PLAT_WLAN_INFO(" cmd = %s", cmd);
    SIZEOF_SNPRINTF(cmd_buf, "%s >/var/reginfo 2>&1", cmd);
    WIFI_SHELL_CMD(cmd_buf);
    memset(buf, 0, sizeof(buf));
    if(0 == wlan_read_file("/var/reginfo", buf, sizeof(buf)))
    {
        PLAT_WLAN_ERR("read_from_file fail");
        return 0;
    }
    PLAT_WLAN_INFO(" buf = %s", buf);
    p_buf = strstr(buf, info_key);
    p_buf += strlen(info_key);
    if (NULL == p_buf)
    {
        return 0;
    }
    PLAT_WLAN_INFO(" p_buf = %s", p_buf);
    strncpy(value, p_buf, strlen(p_buf) + 1);
    PLAT_WLAN_INFO(" value = %s", value);

    return strlen(value);
}


/*****************************************************************************
 ��������  : WlanReadPow
 ��������  :��ȡpowerֵ
 �������  : 
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 WlanReadPow(uint32 *reg_val, WLAN_AT_WIMODE_TYPE mode
                    , WLAN_AT_WIBAND_TYPE band, uint32 channel, WLAN_AT_TSELRF_TYPE wtselrf)
{
    char buf[WIFI_CMD_MAX_SIZE] = {0};
    char *p_buf = NULL;
    const char *efuse_key = NULL;
    const char *info_key   = "=";
    
    ASSERT_NULL_POINTER(reg_val, AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("Entry, mode = %d, band = %d , channel = %d, wtselrf =%d", mode, band, channel, wtselrf);

    if (!IS_TSELRF_VAILD(wtselrf))
    {
        PLAT_WLAN_INFO("Error  wtselrf =%d",  wtselrf);
        return AT_RETURN_FAILURE;
    }

    switch (mode)
    {
        case AT_WIMODE_80211b:
        {
            efuse_key = g_wical_pwr_param_set[(int)wtselrf].cck;
            break;
        }
        case AT_WIMODE_80211g:
        {
            efuse_key = g_wical_pwr_param_set[(int)wtselrf].diff_th20_ofdm;
            break;
        }
        case AT_WIMODE_80211n:
        {
            switch (band)
            {
                case AT_WIBAND_20M:
                {
                #if defined(FEATURE_HUAWEI_MBB_RTL8189)
                    efuse_key = g_wical_pwr_param_set[(int)wtselrf].diff_th20_ofdm;
                #else
                    efuse_key = g_wical_pwr_param_set[(int)wtselrf].diff_th20;
                #endif
                    break;
                }
                case AT_WIBAND_40M:
                {
                    efuse_key = g_wical_pwr_param_set[(int)wtselrf].th40_1s;
                    break;
                }
                default:
                    PLAT_WLAN_ERR("Error band = %d", band);
                    break;
            }
            break;
        }
        default:
        {
            PLAT_WLAN_ERR("Error mode = %d", mode);
            break;
        }
    }

    ASSERT_NULL_POINTER(efuse_key, AT_RETURN_FAILURE);
    
    SIZEOF_SNPRINTF(buf, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" efuse_get %s >/var/staInfo 2>&1", efuse_key);
    WIFI_SHELL_CMD(buf);

    memset(buf, 0, sizeof(buf));
    if(0 == wlan_read_file("/var/staInfo", buf, sizeof(buf)))
    {
        PLAT_WLAN_ERR("read_from_file fail");
        return AT_RETURN_FAILURE;
    }
    
    p_buf = strstr(buf, info_key);
    if (NULL == p_buf)
    {
        return AT_RETURN_FAILURE;
    }
#if defined(FEATURE_HUAWEI_MBB_RTL8189)
    if (efuse_key == g_wical_pwr_param_set[(int)wtselrf].diff_th20_ofdm)
    {
        p_buf += (strlen(info_key));  /* �����ŵ���ѯpowerֵ */
    }
    else
    {
        p_buf += (strlen(info_key) + (channel - 1) * 2);  /* �����ŵ���ѯpowerֵ */
    }
#else
    p_buf += (strlen(info_key) + (channel - 1) * 2);  /* �����ŵ���ѯpowerֵ */
#endif
    p_buf[2] = '\0';  /* ����ַ��������� */
    PLAT_WLAN_INFO("channel = %d , buf:%s ", channel, p_buf);

    *reg_val = (uint32)wlan_strtoi(p_buf, NULL, WLAN_BASE16); /*��ȡ16������*/

#if defined(FEATURE_HUAWEI_MBB_RTL8189)
    if (efuse_key == g_wical_pwr_param_set[(int)wtselrf].diff_th20_ofdm)
    {
        if (AT_WIMODE_80211g == mode)
        {
            *reg_val = (uint32)(0x0F & *reg_val); /* ����4λ��ʾ11g��power���� */
        }
        else if (AT_WIBAND_20M == band)
        {
            *reg_val = (uint32)((0xF0 & *reg_val) >> 4); /* ��4λ��ʾ20M��power���� */
        }
    }
#endif
    
    PLAT_WLAN_INFO("Exit, reg_value = %d", (int)*reg_val);
    return AT_RETURN_SUCCESS;
}

/*===========================================================================
 (1)^WIENABLE ����WiFiģ��ʹ��
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiEnable
 ��������  : ����WiFiģ��ʹ��
 �������  : onoff:ʹ�ܿ���
 �������  : NA
 �� �� ֵ  : int32
*****************************************************************************/
STATIC int32 ATSetWifiEnable(WLAN_AT_WIENABLE_TYPE onoff)
{
    PLAT_WLAN_INFO("Enter [onoff=%d]", onoff);

    switch (onoff)
    {
    case AT_WIENABLE_OFF:
        WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_stop");
        WIFI_TEST_CMD(WIFI_TOOL_IFCONFIG" "WIFI_AP_INTERFACE" down");
        break;
    case AT_WIENABLE_TEST:
        WIFI_TEST_CMD(WIFI_TOOL_IFCONFIG" "WIFI_AP_INTERFACE" down");
        //���ε���8192d��ص�����
        //WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" set_mib trsw_pape_C9=0");
        //WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" set_mib trsw_pape_CC=0");
        //WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" set_mib macPhyMode=0");
        //WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" set_mib phyBandSelect=1");
        WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" set_mib mp_specific=1");
        WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" set_mib channel=1"); /*��������Զ��ŵ�ѡ��*/
        WIFI_TEST_CMD(WIFI_TOOL_IFCONFIG" "WIFI_AP_INTERFACE" up");
        WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_start");
        break;
    default:
        PLAT_WLAN_INFO("Exit on PARAMS FAILED");
        return (AT_RETURN_FAILURE);
    }

    g_wlan_at_data.WiEnable = onoff;
    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiEnable
 ��������  : ��ȡ��ǰ��WiFiģ��ʹ��״̬
 �������  : NA
 �������  : NA
 �� �� ֵ  : WLAN_AT_WIENABLE_TYPE
*****************************************************************************/
STATIC WLAN_AT_WIENABLE_TYPE ATGetWifiEnable(void)
{
    PLAT_WLAN_INFO("Enter [status=%d]", g_wlan_at_data.WiEnable);
    if (WLAN_SUCCESS != wlan_run_cmd(WIFI_TOOL_IFCONFIG" "WIFI_AP_INTERFACE))   //check  wlan0
    {
        PLAT_WLAN_ERR(" wifi driver status error!!!");
        return AT_WIENABLE_OFF;
    }
    
    return (g_wlan_at_data.WiEnable);
}

/*===========================================================================
 (2)^WIMODE ����WiFiģʽ���� Ŀǰ��Ϊ��ģʽ����
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiMode
 ��������  : ����WiFi AP֧�ֵ�����ģʽ
 �������  : mode:����ģʽ
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiMode(WLAN_AT_WIMODE_TYPE mode)
{
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);

    PLAT_WLAN_INFO("Enter [cur_mode=%d set_mode=%d]", g_wlan_at_data.WiMode.mode, mode);

    WLAN_SET_RXTX_STOP();

    switch (mode)
    {
        case AT_WIMODE_CW:
        {
            g_wlan_at_data.WiMode.cw_enable = AT_FEATURE_ENABLE;
            g_wlan_at_data.WiMode.mode = AT_WIMODE_80211b;
            g_wlan_at_data.WiBand = AT_WIBAND_20M;
            WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_rate 108");
            WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_bandwidth 40M=0,shortGI=0");
            break;
        }
        case AT_WIMODE_80211b:
        case AT_WIMODE_80211g:
        case AT_WIMODE_80211n:
        {
            g_wlan_at_data.WiMode.cw_enable = AT_FEATURE_DISABLE;
            g_wlan_at_data.WiMode.mode = mode;
            break;
        }
        default:
            PLAT_WLAN_INFO("Error mode = %d", mode);
            return (AT_RETURN_FAILURE);
    }

    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiMode
 ��������  : ��ȡ��ǰWiFi֧�ֵ�����ģʽ
 �������  : NA
 �������  : strBuf:��ǰģʽ�����ַ�����ʽ����eg: 2
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiMode(WLAN_AT_BUFFER_STRU *strBuf)
{
    ASSERT_NULL_POINTER(strBuf, AT_RETURN_FAILURE);
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);

    PLAT_WLAN_INFO("Enter [cw_enable = %d, cur_mode = %d]"
        , g_wlan_at_data.WiMode.cw_enable, g_wlan_at_data.WiMode.mode);

    SIZEOF_SNPRINTF(strBuf->buf, "%d"
        , ((AT_FEATURE_ENABLE == g_wlan_at_data.WiMode.cw_enable) ? AT_WIMODE_CW : g_wlan_at_data.WiMode.mode));
    PLAT_WLAN_INFO(" return  %s  ", strBuf->buf);
    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiModeSupport
 ��������  : ��ȡWiFi APоƬ֧�ֵ���������ģʽ
 �������  : NA
 �������  : strBuf:֧�ֵ�����ģʽ�����ַ�����ʽ����eg: 2,3,4
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiModeSupport(WLAN_AT_BUFFER_STRU *strBuf)
{
    ASSERT_NULL_POINTER(strBuf, AT_RETURN_FAILURE);

    PLAT_WLAN_INFO("Enter [mode=%s]", WLAN_AT_MODE_SUPPORT);

    SIZEOF_SNPRINTF(strBuf->buf, "%s", WLAN_AT_MODE_SUPPORT);
    return (AT_RETURN_SUCCESS);
}

/*===========================================================================
 (3)^WIBAND ����WiFi�������
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiBand
 ��������  : ����WiFi�������
 �������  : width:����
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiBand(WLAN_AT_WIBAND_TYPE width)
{
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("Enter [band=%d]", width);

    WLAN_SET_RXTX_STOP();

    switch(width)
    {
    case AT_WIBAND_20M:
        WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_bandwidth 40M=0,shortGI=0");
        break;
    case AT_WIBAND_40M:
        WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_bandwidth 40M=1,shortGI=0");
        break;
    default:
        PLAT_WLAN_INFO("Exit on PARAMS FAILED");
        return AT_RETURN_FAILURE;
    }

    g_wlan_at_data.WiBand = width;
    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiBand
 ��������  : ��ȡ��ǰ��������
 �������  : NA
 �������  : strBuf:��ǰ�������ַ�����ʽ����eg: 0
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiBand(WLAN_AT_BUFFER_STRU *strBuf)
{
    ASSERT_NULL_POINTER(strBuf, AT_RETURN_FAILURE);
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);

    PLAT_WLAN_INFO("Enter [band=%d]", g_wlan_at_data.WiBand);

    SIZEOF_SNPRINTF(strBuf->buf, "%d", g_wlan_at_data.WiBand);
    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiBandSupport
 ��������  : ��ȡWiFi AP֧�ֵĴ�������
 �������  : NA
 �������  : strBuf:֧�ִ������ַ�����ʽ����eg: 0,1
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiBandSupport(WLAN_AT_BUFFER_STRU *strBuf)
{
    ASSERT_NULL_POINTER(strBuf, AT_RETURN_FAILURE);

    PLAT_WLAN_INFO("Enter [band=%s]", WLAN_AT_BAND_SUPPORT);

    SIZEOF_SNPRINTF(strBuf->buf, "%s", WLAN_AT_BAND_SUPPORT);
    return (AT_RETURN_SUCCESS);
}

/*===========================================================================
 (4)^WIFREQ ����WiFiƵ��
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiFreq
 ��������  : ����WiFiƵ��
 �������  : pFreq:Ƶ����Ϣ
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiFreq(WLAN_AT_WIFREQ_STRU *pFreq)
{
    int8 acCmd[WIFI_CMD_MAX_SIZE] = {0};
    uint32 channel = 0;

    ASSERT_NULL_POINTER(pFreq, AT_RETURN_FAILURE);
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);

    for (channel = 0; channel < ARRAY_SIZE(g_ausChannels); channel++)
    {
        if (pFreq->value == g_ausChannels[channel])
        {
            break;
        }
    }

    PLAT_WLAN_INFO("Enter [freq=%d idx=%d<%d]", pFreq->value, (int)(channel + 1), ARRAY_SIZE(g_ausChannels));

    if (ARRAY_SIZE(g_ausChannels) <= channel)
    {
        return (AT_RETURN_FAILURE);
    }

    WLAN_SET_RXTX_STOP();

    channel++;
    SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_channel %d", (int)channel);
    WIFI_TEST_CMD(acCmd);

    g_wlan_at_data.WiFreq.channel = channel;
    g_wlan_at_data.WiFreq.freq.value = pFreq->value;
    g_wlan_at_data.WiFreq.freq.offset = pFreq->offset;
    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiFreq
 ��������  : ��ȡWiFiƵ��
 �������  : NA
 �������  : pFreq:��ǰƵ��
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiFreq(WLAN_AT_WIFREQ_STRU *pFreq)
{
    ASSERT_NULL_POINTER(pFreq, AT_RETURN_FAILURE);
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);

    PLAT_WLAN_INFO("Enter [channel = %d, freq = %d, offset = %d]"
        , (int)g_wlan_at_data.WiFreq.channel
        , (int)g_wlan_at_data.WiFreq.freq.value
        , (int)g_wlan_at_data.WiFreq.freq.offset
        );

    memcpy(pFreq, &(g_wlan_at_data.WiFreq.freq), sizeof(*pFreq));
    return (AT_RETURN_SUCCESS);
}

/*===========================================================================
 (5)^WIDATARATE ���úͲ�ѯ��ǰWiFi���ʼ�����
  WiFi���ʣ���λΪ0.01Mb/s��ȡֵ��ΧΪ0��65535
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiDataRate
 ��������  : ����WiFi���ʼ�����
 �������  : rate:����ֵ
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiDataRate(uint32 rate)
{
    int8    acCmd[WIFI_CMD_MAX_SIZE] = {0};
    uint32  ulNRate = 0;
    const uint32  aucAtWifiNRate_Table[] = {650, 1300, 1950, 2600, 3900, 5200, 5850, 6500};          /*20M DataRate*/
    const uint32  aucAtWifiNRate_40M_Table[] = {1350, 2700, 4050, 5400, 8100, 10800, 12150, 13500}; /*40M DataRate*/

    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("Enter [mode=%d rate=%d]", g_wlan_at_data.WiMode.mode, (int)rate);

    WLAN_SET_RXTX_STOP();

    switch (g_wlan_at_data.WiMode.mode)
    {
    case AT_WIMODE_80211b:
    case AT_WIMODE_80211g:
        SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_rate %d", (int)(rate / 50)); /*DataRate*/
        break;
    case AT_WIMODE_80211n:
        for (ulNRate = 0; ulNRate < ARRAY_SIZE(aucAtWifiNRate_Table); ulNRate++)
        {
            if (aucAtWifiNRate_Table[ulNRate] == rate)
            {
                break;
            }
            if (aucAtWifiNRate_40M_Table[ulNRate] == rate)
            {
                break;
            }
        }
        if (ARRAY_SIZE(aucAtWifiNRate_Table) <= ulNRate)
        {
            return (AT_RETURN_FAILURE);
        }
        SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_rate %d", (int)(128 + ulNRate));/* ���� */
        break;
    default:
        return (AT_RETURN_FAILURE);
    }
    WIFI_TEST_CMD(acCmd);

    g_wlan_at_data.WiDataRate = rate;

    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiDataRate
 ��������  : ��ѯ��ǰWiFi���ʼ�����
 �������  : NA
 �������  : NA
 �� �� ֵ  : uint32:����ֵ
*****************************************************************************/
STATIC uint32 ATGetWifiDataRate(void)
{
    PLAT_WLAN_INFO("Enter [mode=%d rate=%d]", g_wlan_at_data.WiMode.mode, (int)g_wlan_at_data.WiDataRate);

    return g_wlan_at_data.WiDataRate;
}

/*===========================================================================
 (6)^WIPOW ������WiFi���书��
   WiFi���书�ʣ���λΪ0.01dBm��ȡֵ��ΧΪ -32768��32767
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiPOW
 ��������  : ����WiFi���书��
 �������  : power_dBm_percent:����ֵ
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiPOW(int32 power_dBm_percent)
{
    int8   acCmd[WIFI_CMD_MAX_SIZE] = {0};
    int32  lWifiPower = (power_dBm_percent / 100); /* dBm */
    uint32  pow_index = 0;
    uint32  curr_index = 0;
    uint32  ht40_index  = 0;
    uint32  curr_tselrf = WLAN_CURRENT_TSELRF;
#ifdef WLAN_NV_READ_POW
    WLAN_AT_WIINFO_POWER_STRU stGetPwrWiinfo;
#endif /*WLAN_NV_READ_POW*/
    static struct _target_power_
    {
        uint8 init;
        uint8 dot11b;
        uint8 dot11g;
        uint8 dot11n;
    }s_target_power = {0, 13, 11, 9}; /* power init */

    PLAT_WLAN_INFO("Enter [power=%d]", (int)power_dBm_percent);
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);

    if (lWifiPower < WLAN_AT_WIFI_POWER_MIN)
    {
        lWifiPower = WLAN_AT_WIFI_POWER_MIN;
    }

    if (lWifiPower > WLAN_AT_WIFI_POWER_MAX)
    {
        lWifiPower = WLAN_AT_WIFI_POWER_MAX;
    }

    if (!s_target_power.init)
    {
    #ifdef WLAN_NV_READ_POW
        memset(&stGetPwrWiinfo, 0, sizeof(stGetPwrWiinfo));
        if(AT_RETURN_SUCCESS != WLAN_NV_READ_POW(&stGetPwrWiinfo, sizeof(WLAN_AT_WIINFO_POWER_STRU)))
        {
            PLAT_WLAN_ERR("Read target wifi power failed!!");
            return AT_RETURN_FAILURE;
        }
        PLAT_WLAN_INFO("NV_Read PWRWIINFO SUCCESS, sPower_24G_bMode=%s,sPower_24G_gMode=%s,sPower_24G_nMode=%s\n"
        , stGetPwrWiinfo.bMode_24G_pwr
        , stGetPwrWiinfo.gMode_24G_pwr
        , stGetPwrWiinfo.nMode_24G_pwr);

        if ('\0' != stGetPwrWiinfo.bMode_24G_pwr[0])
        {
            s_target_power.dot11b = wlan_strtoi((char *)stGetPwrWiinfo.bMode_24G_pwr, NULL, WLAN_BASE10);
        }
        if ('\0' != stGetPwrWiinfo.gMode_24G_pwr[0])
        {
            s_target_power.dot11g = wlan_strtoi((char *)stGetPwrWiinfo.gMode_24G_pwr, NULL, WLAN_BASE10);
        }
        if ('\0' != stGetPwrWiinfo.nMode_24G_pwr[0])
        {
            s_target_power.dot11n = wlan_strtoi((char *)stGetPwrWiinfo.nMode_24G_pwr, NULL, WLAN_BASE10);
        }
    #endif /*WLAN_NV_READ_POW*/

        s_target_power.init = 1;
    }

    PLAT_WLAN_INFO("target_power_11b = %d, target_power_11g = %d target_power_11n = %d\n"
        , s_target_power.dot11b
        , s_target_power.dot11g
        , s_target_power.dot11n);

    //��ȡ40M����
    if (AT_RETURN_SUCCESS != WlanReadPow(&ht40_index, AT_WIMODE_80211n, AT_WIBAND_40M
                                , g_wlan_at_data.WiFreq.channel, WLAN_CURRENT_TSELRF))
    {
        PLAT_WLAN_INFO("ERROR: N40 WlanReadPow");
        return AT_RETURN_FAILURE;
    }
    //��ȡʵ�ʽ��
    PLAT_WLAN_INFO("wifi_mode = %d, wifi_band = %d, wifi_channel = %d , WiTselrf =  %d", g_wlan_at_data.WiMode.mode
        , g_wlan_at_data.WiBand, (int)g_wlan_at_data.WiFreq.channel, WLAN_CURRENT_TSELRF);
    if (AT_RETURN_SUCCESS != WlanReadPow(&curr_index, g_wlan_at_data.WiMode.mode
                                    , g_wlan_at_data.WiBand, g_wlan_at_data.WiFreq.channel, WLAN_CURRENT_TSELRF))
    {
        PLAT_WLAN_ERR("ERROR: get this mode reg value");
        return AT_RETURN_FAILURE;
    }

    PLAT_WLAN_INFO("efuse_get rmap index is 0x%02x,  ht40_index is 0x%02x", (unsigned int)curr_index, (unsigned int)ht40_index);

   if(MAX_POW_INDEX >= ht40_index)
   {
        switch (g_wlan_at_data.WiMode.mode)
        {
            case AT_WIMODE_80211b:
            {
                if (0 == lWifiPower)
                {
                    pow_index = 50; /* 802.11bĬ��ֵ */
                }
                else
                {
                    pow_index = curr_index + (lWifiPower - (s_target_power.dot11b / 10)) * 2; /* �μ�MP�ĵ� */
                }
                break;
            }
            case AT_WIMODE_80211g:
            {
                if (0 == lWifiPower)
                {
                    pow_index = 41; /* 802.11gĬ��ֵ */
                }
                else if (IS_TSELRF_VAILD(curr_tselrf))
                {
                    pow_index = ht40_index + RTL_POW_DIFF(curr_tselrf, curr_index) 
                        + ((lWifiPower - (s_target_power.dot11g / 10)) * 2); /*MP*/
                }
                else
                {
                    PLAT_WLAN_INFO("Error  wtselrf =%d", curr_tselrf);
                    return AT_RETURN_FAILURE;
                }
                break;
            }
            case AT_WIMODE_80211n:
            {
                if (0 == lWifiPower)
                {
                    pow_index = 40; /* 802.11nĬ��ֵ */
                }
                else
                {
                    switch (g_wlan_at_data.WiBand)
                    {
                        case AT_WIBAND_20M:
                        {
                            if (IS_TSELRF_VAILD(curr_tselrf))
                            {
                                pow_index = ht40_index + RTL_POW_DIFF(curr_tselrf, curr_index) 
                                            + ((lWifiPower - (s_target_power.dot11n / 10)) * 2); /*MP*/
                            }
                            else
                            {
                                PLAT_WLAN_INFO("Error  wtselrf =%d", curr_tselrf);
                                return AT_RETURN_FAILURE;
                            }
                            break;
                        }
                        case AT_WIBAND_40M:
                            pow_index = curr_index + (lWifiPower - (s_target_power.dot11n / 10)) * 2; /* MP 40M */
                            break;
                        default:
                            PLAT_WLAN_ERR("ERROR: WiBand = %d", g_wlan_at_data.WiBand);
                            return AT_RETURN_FAILURE;
                    }
                }
                break;
            }
            default:
                PLAT_WLAN_ERR("ERROR: mode = %d", g_wlan_at_data.WiMode.mode);
                return AT_RETURN_FAILURE;
        }
    }
    else
    {
         PLAT_WLAN_INFO(" The power is not verfied, send mp_txpower patha=%d,pathb=%d as  default value.\n", (int)MAX_POW_INDEX/2,  (int)MAX_POW_INDEX/2 );
         pow_index=(int)MAX_POW_INDEX/2;
    }

    WLAN_SET_RXTX_STOP();

    PLAT_WLAN_INFO("power_index = %d, mode = %d, band = %d"
        , (int)pow_index, g_wlan_at_data.WiMode.mode, g_wlan_at_data.WiBand);
    SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_txpower patha=%d,pathb=%d", (int)pow_index, (int)pow_index);
    WIFI_TEST_CMD(acCmd);

    g_wlan_at_data.WiPow = power_dBm_percent;
    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiPOW
 ��������  : ��ȡWiFi��ǰ���书��
 �������  : NA
 �������  : NA
 �� �� ֵ  : int32:����ֵ
*****************************************************************************/
STATIC int32 ATGetWifiPOW(void)
{
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("Enter [power=%d]", (int)g_wlan_at_data.WiPow);

    return g_wlan_at_data.WiPow;
}

/*===========================================================================
 (7)^WITX ����WiFi�����״̬
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiTX
 ��������  : ����WiFi�����״̬
 �������  : NA
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiTX(WLAN_AT_FEATURE_TYPE onoff)
{
    int tx_flag = (int)onoff;
    char cmd_buf[WIFI_CMD_MAX_SIZE] = {0};
    char value_buf[WIFI_CMD_MAX_SIZE] = {0};
    int len = 0;
    int tmp_reg_value=0;

    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("Enter onoff = %d, tselrf = %d", onoff, WLAN_CURRENT_TSELRF);

    WLAN_SET_RXTX_STOP();

    switch (tx_flag)
    {
    case AT_FEATURE_DISABLE:
#ifdef FEATURE_HUAWEI_MBB_RTL8192
        /*ͨ��д�뱣���c14,c1c,a07�Ĵ���λ����RX*/
        SIZEOF_SNPRINTF(cmd_buf, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" write_reg dw,c14,%0x", g_dw_c14_value);
        WIFI_SHELL_CMD(cmd_buf);

        SIZEOF_SNPRINTF(cmd_buf, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" write_reg dw,c1c,%0x", g_dw_c1c_value);
        WIFI_SHELL_CMD(cmd_buf);

        SIZEOF_SNPRINTF(cmd_buf, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" write_reg b,a07,%0x", g_b_a07_value);
        WIFI_SHELL_CMD(cmd_buf);
#endif

        break;
    case AT_FEATURE_ENABLE:
    case WLAN_AT_TX_FULL_DUTY_RATIO:
    {
        switch (WLAN_CURRENT_TSELRF)
        {
        case AT_TSELRF_A:
            WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_ant_tx a");
            break;
        case AT_TSELRF_B:
            WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_ant_tx b");
            break;
        default:
            PLAT_WLAN_ERR("error group = %d", WLAN_CURRENT_TSELRF);
            return AT_RETURN_FAILURE;
        }

        msleep(100); /* �ȴ������л� */

#ifdef FEATURE_HUAWEI_MBB_RTL8192
        /*ͨ������WlanReadRegInfor����c14,c1c,a07�Ĵ���*/
        memset(cmd_buf, 0, sizeof(cmd_buf));
        memset(value_buf, 0, sizeof(value_buf));
        SIZEOF_SNPRINTF(cmd_buf, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" read_reg dw,c14 ");
        len = WlanReadRegInfor(cmd_buf, value_buf);
        PLAT_WLAN_INFO("value_buf = %s  sizeof(g_dw_c14_value) / sizeof(char) = %d", value_buf, sizeof(g_dw_c14_value) / sizeof(char));
        if(0 != len)
        {
            WlanRegInforToDig(value_buf, sizeof(g_dw_c14_value) / sizeof(char), &g_dw_c14_value);
            PLAT_WLAN_INFO("g_dw_c14_value = %0X", g_dw_c14_value);
        }

        memset(cmd_buf, 0, sizeof(cmd_buf));
        memset(value_buf, 0, sizeof(value_buf));
        SIZEOF_SNPRINTF(cmd_buf, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" read_reg dw,c1c ");
        len = WlanReadRegInfor(cmd_buf, value_buf);
        PLAT_WLAN_INFO("value_buf = %s  sizeof(g_dw_c1c_value) / sizeof(char) = %d", value_buf, sizeof(g_dw_c1c_value) / sizeof(char));
        if(0 != len)
        {
            WlanRegInforToDig(value_buf, sizeof(g_dw_c1c_value) / sizeof(char), &g_dw_c1c_value);
            PLAT_WLAN_INFO("g_dw_c1c_value = %0X", g_dw_c1c_value);
        }

        memset(cmd_buf, 0, sizeof(cmd_buf));
        memset(value_buf, 0, sizeof(value_buf));
        SIZEOF_SNPRINTF(cmd_buf, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" read_reg b,a07 ");
        len = WlanReadRegInfor(cmd_buf, value_buf);
        PLAT_WLAN_INFO("value_buf = %s  sizeof(g_b_a07_value) / sizeof(char) = %d", value_buf, sizeof(g_b_a07_value) / sizeof(char));
        if(0 != len)
        {
            WlanRegInforToDig(value_buf, sizeof(g_b_a07_value) / sizeof(char), &g_b_a07_value);
            PLAT_WLAN_INFO("g_b_a07_value = %0X", g_b_a07_value);
        }

        /*ͨ��д���c14,c1c,a07�Ĵ���λ�ر�RX*/
        SIZEOF_SNPRINTF(cmd_buf, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" write_reg dw,c14,00000000");
        WIFI_SHELL_CMD(cmd_buf);

        SIZEOF_SNPRINTF(cmd_buf, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" write_reg dw,c1c,00000000");
        WIFI_SHELL_CMD(cmd_buf);

        tmp_reg_value = g_b_a07_value | 0xF; //0xF:����λ��1
        SIZEOF_SNPRINTF(cmd_buf, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" write_reg b,a07,%0x", tmp_reg_value);
        WIFI_SHELL_CMD(cmd_buf);
#endif

        if (WLAN_AT_TX_FULL_DUTY_RATIO == tx_flag)
        {
            WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_ctx background"); /*ռ�ձ�100%*/
        }
        else if (AT_FEATURE_ENABLE == g_wlan_at_data.WiMode.cw_enable)
        {
            WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_ctx background,stone");
        }
        else
        {
            WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_ctx background,pkt");
        }
        onoff = AT_FEATURE_ENABLE;

        msleep(100);/* �ȴ�TX׼���� */
        break;
    }
    default:
        return (AT_RETURN_FAILURE);
    }

    g_wlan_at_data.WiTX = onoff;

    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiTX
 ��������  : ��ȡWiFi�����״̬
 �������  : NA
 �������  : NA
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
STATIC WLAN_AT_FEATURE_TYPE ATGetWifiTX(void)
{
    ASSERT_WiFi_OFF(AT_FEATURE_DISABLE);
    PLAT_WLAN_INFO("Enter [tx_onoff=%d]", g_wlan_at_data.WiTX);

    return g_wlan_at_data.WiTX;
}

/*===========================================================================
 (8)^WIRX ����WiFi���ջ�����
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiRX
 ��������  : ����WiFi���ջ�����
 �������  : params:��ǰ��Ҫ���õ�RX����
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiRX(WLAN_AT_WIRX_STRU *params)
{
    int8   acCmd[WIFI_CMD_MAX_SIZE] = {0};
    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("Enter, onoff = %d, tselrf = %d", params->onoff, WLAN_CURRENT_TSELRF);

    WLAN_SET_RXTX_STOP();

    switch (params->onoff)
    {
    case AT_FEATURE_DISABLE:
        break;
    case AT_FEATURE_ENABLE:
        switch (WLAN_CURRENT_TSELRF)
        {
        case AT_TSELRF_A:
            WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_ant_rx a");
            break;
        case AT_TSELRF_B:
            WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_ant_rx b");
            break;
        default:
            PLAT_WLAN_ERR("error tselrf = %d", WLAN_CURRENT_TSELRF);
            return AT_RETURN_FAILURE;
        }
        PLAT_WLAN_INFO("src_mac=%s\n", params->src_mac);  /*MAC*/
        SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_arx filter_SA=%s", params->src_mac);  /*MAC*/
        WIFI_TEST_CMD(acCmd);
        WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_arx start");
        break;
    default:
        return (AT_RETURN_FAILURE);
    }

    memcpy(&g_wlan_at_data.WiRX, params, sizeof(*params));
    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiRX
 ��������  : ��ȡWiFi�ӿڻ�����״̬
 �������  : NA
 �������  : params:��ǰ���õ�RX����
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiRX(WLAN_AT_WIRX_STRU *params)
{
    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);

    memcpy(params, &g_wlan_at_data.WiRX, sizeof(*params));

    PLAT_WLAN_INFO("Exit [onoff=%d]", params->onoff);

    return (AT_RETURN_SUCCESS);
}

/*===========================================================================
 (9)^WIRPCKG ��ѯWiFi���ջ�����룬�ϱ����յ��İ�������
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiRPCKG
 ��������  : WiFi�ϱ����յ��İ�����������
 �������  : flag:����ͳ������
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiRPCKG(int32 flag)
{
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);

    if (0 != flag)
    {
        PLAT_WLAN_INFO("Exit on flag=%d", (int)flag);
        return (AT_RETURN_FAILURE);
    }

    WIFI_TEST_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_reset_stats");
    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiRPCKG
 ��������  : ��ѯWiFi���ջ�����룬�ϱ����յ��İ�������
 �������  : NA
 �������  : params:���ݰ�ͳ����Ϣ
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiRPCKG(WLAN_AT_WIRPCKG_STRU *params)
{

    char buf[WIFI_CMD_MAX_SIZE] = {0};
    char *p_buf = NULL;
    const char *info_key = "Rx OK:";
    int staPkgs = 0;

    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);

    if (AT_FEATURE_ENABLE != g_wlan_at_data.WiRX.onoff)
    {
        PLAT_WLAN_ERR("Exit on RX OFF");
        return (AT_RETURN_FAILURE);
    }

    WIFI_SHELL_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_query >/var/staInfo 2>&1");
    
    memset(buf, 0, sizeof(buf));
    if (0 == wlan_read_file("/var/staInfo", buf, sizeof(buf)))
    {
        PLAT_WLAN_ERR("Exit on read file failed");
        return (AT_RETURN_FAILURE);
    }
    
    p_buf = strstr(buf, info_key);
    if(NULL == p_buf) 
    {
        return AT_RETURN_FAILURE;
    }
    p_buf += strlen(info_key);
    staPkgs = wlan_strtoi(p_buf, NULL, WLAN_BASE10); /* ת��Ϊʮ������ */

    params->good_result = staPkgs;
    params->bad_result = 0;

    PLAT_WLAN_INFO("Exit [good=%d,bad=%d]", (int)params->good_result, (int)params->bad_result);
    return (AT_RETURN_SUCCESS);
}

/*===========================================================================
 (10)^WIINFO ��ѯWiFi�������Ϣ
===========================================================================*/
/*****************************************************************************
 ��������  : ATGetWifiInfo
 ��������  : ��ѯWiFi�������Ϣ(�ڲ��ӿ�)
 �������  : NA
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiInfo(WLAN_AT_WIINFO_STRU *params)
{
    static char sChannels24G[] = "1,2,3,4,5,6,7,8,9,10,11";
    static char sChannels24G_h40[] = "3,4,5,6,7,8,9,10,11";

    static  WLAN_AT_WIINFO_MEMBER_STRU sChannelGroup[] =
    {
        {"b",  sChannels24G},
        {"g",  sChannels24G},
        {"n",  sChannels24G},
        {"n4", sChannels24G_h40},
    };
    static  WLAN_AT_WIINFO_MEMBER_STRU sPowerGroup[] =
    {
        {"b", "130"},/*E5 ��Ƶ�ṩĿ�깦�ʹ��*/
        {"g", "110"},
        {"n", "90"},
        {"n4", "90"},
    };
    static  WLAN_AT_WIINFO_MEMBER_STRU sFreqGroup[] =
    {
        {"b", "0"},/*0��ʾ2.4G, 1��ʾ5G*/
        {"g", "0"},
        {"n", "0"},
        {"n4", "0"},
    };
    static WLAN_AT_WIINFO_GROUP_STRU sTotalInfoGroups[] =
    {
        {sChannelGroup, ARRAY_SIZE(sChannelGroup)},
        {sPowerGroup, ARRAY_SIZE(sPowerGroup)},
        {sFreqGroup, ARRAY_SIZE(sFreqGroup)},
    };
    char *strBuf = NULL;
    int32 iLen = 0, idx = 0, iTmp = 0;
    WLAN_AT_WIINFO_GROUP_STRU *pstuInfoGrup = NULL;

    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("Enter [group=%d,type=%d]", (int)params->member.group, params->type);

    if (!IS_TSELRF_VAILD(params->member.group)) /* ˫���ߣ�֧��������1 */
    {
        return (AT_RETURN_FAILURE);
    }

    switch (params->type)
    {
    case AT_WIINFO_CHANNEL:
    case AT_WIINFO_POWER:
    case AT_WIINFO_FREQ:
        idx = params->type;
        break;
    default:
        return (AT_RETURN_FAILURE);
    }

    pstuInfoGrup = &sTotalInfoGroups[idx];
    strBuf = (char *)params->member.content;
    iLen = (int32)(sizeof(params->member.content) - 1);
    for (idx = 0; idx < (int32)pstuInfoGrup->size; idx++)
    {
        if (NULL == pstuInfoGrup->member[idx].name
                || NULL == pstuInfoGrup->member[idx].value)
        {
            continue;
        }

        OSA_SNPRINTF(strBuf, iLen, "%s,%s"
                     , pstuInfoGrup->member[idx].name
                     , pstuInfoGrup->member[idx].value);
        iTmp = (int32)(strlen(strBuf) + 1);
        iLen -= iTmp;
        strBuf += iTmp;
        if (iLen <= 0)
        {
            return (AT_RETURN_FAILURE);
        }
    }
    *strBuf = '\0';
    return (AT_RETURN_SUCCESS);
}

/*===========================================================================
 (11)^WIPLATFORM ��ѯWiFi����ƽ̨��Ӧ����Ϣ
===========================================================================*/
/*****************************************************************************
 ��������  : ATGetWifiPlatform
 ��������  : ��ѯWiFi����ƽ̨��Ӧ����Ϣ
 �������  : NA
 �������  : NA
 �� �� ֵ  : WLAN_AT_WIPLATFORM_TYPE
*****************************************************************************/
STATIC WLAN_AT_WIPLATFORM_TYPE ATGetWifiPlatform(void)
{
    PLAT_WLAN_INFO("Enter [plat=%d]", AT_WIPLATFORM_REALTEK);
    return (AT_WIPLATFORM_REALTEK);
}

/*===========================================================================
 (12)^TSELRF ��ѯ���õ����WiFi��Ƶͨ·
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetTSELRF
 ��������  : �������ߣ��Ƕ�ͨ·��0
 �������  : group:��������
 �������  : NA
 �� �� ֵ  : int32
*****************************************************************************/
STATIC int32 ATSetTSELRF(uint32 group)
{
    PLAT_WLAN_INFO("Enter [plat=%d]", (int)group);

    if (!IS_TSELRF_VAILD(group))
    {
        return (AT_RETURN_FAILURE);
    }

    g_wlan_at_data.WiTselrf = (WLAN_AT_TSELRF_TYPE)group;
    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetTSELRFSupport
 ��������  : ֧�ֵ�������������
 �������  : NA
 �������  : strBuf:�������������ַ�����ʽ����eg: 0,1,2,3
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetTSELRFSupport(WLAN_AT_BUFFER_STRU *strBuf)
{
    ASSERT_NULL_POINTER(strBuf, AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("Enter [TSELRF=%s]", WLAN_AT_TSELRF_SUPPORT);

    SIZEOF_SNPRINTF(strBuf->buf, "%s", WLAN_AT_TSELRF_SUPPORT);
    return (AT_RETURN_SUCCESS);
}

/*===========================================================================
 (13)^WiPARANGE���á���ȡWiFi PA���������
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiParange
 ��������  : ����WiFi PA���������
 �������  : pa_type:����ֵ����
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiParange(WLAN_AT_WiPARANGE_TYPE pa_type)
{
    ASSERT_WiFi_OFF(AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("Enter [pa_type=%c]", pa_type);

    if (AT_WiPARANGE_HIGH != pa_type) /*��֧������PA*/
    {
        return AT_RETURN_FAILURE;
    }

    g_wlan_at_data.WiParange = pa_type;

    return (AT_RETURN_SUCCESS);
}

/*****************************************************************************
 ��������  : ATGetWifiParange
 ��������  : ��ȡWiFi PA���������
 �������  : NA
 �������  : NA
 �� �� ֵ  : WLAN_AT_WiPARANGE_TYPE
*****************************************************************************/
STATIC WLAN_AT_WiPARANGE_TYPE ATGetWifiParange(void)
{
    ASSERT_WiFi_OFF(AT_WiPARANGE_BUTT);

    PLAT_WLAN_INFO("Exit [pa_mode=%c]", g_wlan_at_data.WiParange);

    return g_wlan_at_data.WiParange;
}

/*****************************************************************************
 ��������  : ATGetWifiParangeSupport
 ��������  : ֧�ֵ�paģʽ����
 �������  : NA
 �������  : strBuf:֧�ֵ��������У����ַ�����ʽ����eg: l,h
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiParangeSupport(WLAN_AT_BUFFER_STRU *strBuf)
{
    ASSERT_NULL_POINTER(strBuf, AT_RETURN_FAILURE);

    SIZEOF_SNPRINTF(strBuf->buf, "%c", AT_WiPARANGE_HIGH);

    PLAT_WLAN_INFO("Exit [support=%s]", strBuf->buf);

    return (AT_RETURN_SUCCESS);
}

/*===========================================================================
 (14)^WICALTEMP���á���ȡWiFi���¶Ȳ���ֵ
===========================================================================*/
/*****************************************************************************
 ��������  : ATGetWifiCalTemp
 ��������  : ����WiFi���¶Ȳ���ֵ
 �������  : NA
 �������  : params:�¶Ȳ�������
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiCalTemp(WLAN_AT_WICALTEMP_STRU *params)
{
    char buf[WIFI_CMD_MAX_SIZE] = {0};
    char *p_buf = NULL;
    const char *info_key = "mp_ther:";
    
    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);

    WIFI_SHELL_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_ther >/var/staInfo 2>&1");

    memset(buf, 0, sizeof(buf));
    if (0 == wlan_read_file("/var/staInfo", buf, sizeof(buf)))
    {
        PLAT_WLAN_ERR("read_from_file fail");
        return AT_RETURN_FAILURE;
    }
    PLAT_WLAN_INFO("get_mib ther: %s", buf);
    p_buf = strstr(buf, info_key);
    ASSERT_NULL_POINTER(p_buf, AT_RETURN_FAILURE);

    p_buf += strlen(info_key);
    params->value = wlan_strtoi(p_buf, NULL, WLAN_BASE10);
    PLAT_WLAN_INFO("index: %d, staTemp: %d", (int)params->index, (int)params->value);

    return AT_RETURN_SUCCESS;
}

/*****************************************************************************
 ��������  : ATSetWifiCalTemp
 ��������  : ����WiFi���¶Ȳ���ֵ
 �������  : params:�¶Ȳ�������
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiCalTemp(WLAN_AT_WICALTEMP_STRU *params)
{
    char acCmd[WIFI_CMD_MAX_SIZE] = {0};
    char buf[WIFI_CMD_MAX_SIZE] = {0};
    char *p_buf = NULL;
    const char *info_key = "get_mib:";
    int32 tmp_data = 0;
    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("index = %d, staTemp = %d", (int)params->index, (int)params->value);

    WLAN_SET_RXTX_STOP();

    if (255 == params->index)/* �������ֵ����ʾ��ȡ�Ĵ����е�������Ϣ�·� */
    {
        WIFI_SHELL_CMD(WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" get_mib ther >/var/staInfo 2>&1");
    
        memset(buf, 0, sizeof(buf));
        if(0 == wlan_read_file("/var/staInfo", buf, sizeof(buf)))
        {
            PLAT_WLAN_ERR("read_from_file fail");
            return AT_RETURN_FAILURE;
        }
        PLAT_WLAN_INFO("get_mib ther: %s", buf);
        p_buf = strstr(buf, info_key);
        ASSERT_NULL_POINTER(p_buf, AT_RETURN_FAILURE);
    
        p_buf += strlen(info_key);
        tmp_data = wlan_strtoi(p_buf, NULL, WLAN_BASE10);
        SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_pwrtrk ther=%d", tmp_data);
        WIFI_TEST_CMD(acCmd);
    }
    else
    {
        SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_pwrtrk ther=%d", (int)params->value);
        WIFI_TEST_CMD(acCmd);
    }
    return AT_RETURN_SUCCESS;
}

/*===========================================================================
 (15)^WICALDATA���á���ȡָ�����͵�WiFi��������
===========================================================================*/
/*****************************************************************************
 ��������  : ATGetWifiCalData
 ��������  : ָ�����͵�WiFi��������
 �������  : NA
 �������  : params:��������
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiCalData(WLAN_AT_WICALDATA_STRU * params)
{
    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);
    memcpy(params, &g_wlan_at_data.WiCalData, sizeof(g_wlan_at_data.WiCalData));
    
    return  AT_RETURN_SUCCESS;
}

/*****************************************************************************
 ��������  : ATSetWifiCalData
 ��������  : ָ�����͵�WiFi��������
 �������  : params:��������
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiCalData(WLAN_AT_WICALDATA_STRU *params)
{
    uint32 channel = 0, idx = 0;
    int32 data = 0;

    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);
    
    PLAT_WLAN_INFO("Entry type = %d, group = %d, mode = %d, band = %d, bandwidth = %d, freq = %d, data = %s"
        , params->type, (int)params->group, params->mode, params->band, params->bandwidth, (int)params->freq, params->data);
    
    /* Ƶ������ */
    if (AT_WIFREQ_24G != params->band)
    {
        PLAT_WLAN_ERR("Error, band = %d", params->band);
        return AT_RETURN_FAILURE;
    }
    
    /* ���߼�� */
    if (!IS_TSELRF_VAILD(params->group))
    {
        PLAT_WLAN_INFO("Error  wtselrf =%d",  params->group);
        return AT_RETURN_FAILURE;
    }

    /* �ŵ���� */
    for (channel = 0; channel < ARRAY_SIZE(g_ausChannels); channel++)
    {
        if (params->freq == g_ausChannels[channel])
        {
            break;
        }
    }
    if (channel == ARRAY_SIZE(g_ausChannels))
    {
        PLAT_WLAN_ERR("Error, freq = %d", (int)params->freq);
        return AT_RETURN_FAILURE;
    }
    channel++;
    data = wlan_strtoi(params->data, NULL, WLAN_BASE10);
    PLAT_WLAN_INFO("channel = %d, data = %d", (int)channel, (int)data);

    switch(params->type) 
    {
    case AT_WICALDATA_REL_IDX_POW:
    case AT_WICALDATA_ABS_IDX_POW:
    {
        switch (params->mode)
        {
            case AT_WIMODE_80211b:
            {
                for (idx = 0; idx < ARRAY_SIZE(g_wlan_at_data.WiCal.power[params->group].cck); idx++)
                {
                    if (0 == g_wlan_at_data.WiCal.power[params->group].cck[idx].ch
                        || channel == g_wlan_at_data.WiCal.power[params->group].cck[idx].ch
                        )
                    {
                        g_wlan_at_data.WiCal.power[params->group].cck[idx].ch = channel;
                        g_wlan_at_data.WiCal.power[params->group].cck[idx].data = (uint8)data;
                        break;
                    }
                }
                if (idx == ARRAY_SIZE(g_wlan_at_data.WiCal.power[params->group].cck))
                {
                    PLAT_WLAN_ERR("Error, channel = %d out of MAX ARRAY %d"
                        , channel, ARRAY_SIZE(g_wlan_at_data.WiCal.power[params->group].cck));
                    return AT_RETURN_FAILURE;
                }
                break;
            }
            case AT_WIMODE_80211g:
            {
                if (WIFI_POWER_DIFF_MIN > data || data > WIFI_POWER_DIFF_MAX)
                {
                    PLAT_WLAN_ERR("Error, data = %d", (int)data);
                    return AT_RETURN_FAILURE;
                }
                if (HW_VER_PRODUCT_E5573S_852 == bsp_version_get_board_type())
                {
                    g_wlan_at_data.WiCal.power[params->group].diffofdm = (uint8)(0x0F & (data+1)); /* ��ȡ��4λ */
				}
                else
                {
                    g_wlan_at_data.WiCal.power[params->group].diffofdm = (uint8)(0x0F & data); /* ��ȡ��4λ */
                }
                break;
            }
            case AT_WIMODE_80211n:
            {
                switch(params->bandwidth)
                {
                    case AT_WIBAND_20M:
                    {
                        if (WIFI_POWER_DIFF_MIN > data || data > WIFI_POWER_DIFF_MAX)
                        {
                            PLAT_WLAN_ERR("Error, data = %d", (int)data);
                            return AT_RETURN_FAILURE;
                        }
                    #if defined(FEATURE_HUAWEI_MBB_RTL8189)
                        g_wlan_at_data.WiCal.power[params->group].diffofdm = (
                            (g_wlan_at_data.WiCal.power[params->group].diffofdm & 0x0F) /* ��4λ���� */
                            | ((0x0F & data) << 4)); /* 20M�����ݴ����OFDM�ĸ�4λ */
                    #else
                        g_wlan_at_data.WiCal.power[params->group].diffht20 = (uint8)(0x0F & data); /* ��ȡ��4λ */
                    #endif
                        break;
                    }
                    case AT_WIBAND_40M:
                    {
                        for (idx = 0; idx < ARRAY_SIZE(g_wlan_at_data.WiCal.power[params->group].ht40); idx++)
                        {
                            if (0 == g_wlan_at_data.WiCal.power[params->group].ht40[idx].ch
                                || channel == g_wlan_at_data.WiCal.power[params->group].ht40[idx].ch
                                )
                            {
                                g_wlan_at_data.WiCal.power[params->group].ht40[idx].ch = channel;
                                g_wlan_at_data.WiCal.power[params->group].ht40[idx].data = (uint8)data;
                                break;
                            }
                        }
                        if (idx == ARRAY_SIZE(g_wlan_at_data.WiCal.power[params->group].ht40))
                        {
                            PLAT_WLAN_ERR("Error, channel = %d out of MAX ARRAY %d"
                                , channel, ARRAY_SIZE(g_wlan_at_data.WiCal.power[params->group].ht40));
                            return AT_RETURN_FAILURE;
                        }
                        break;
                    }
                    default:
                        PLAT_WLAN_ERR("Error, bandwidth = %d", params->bandwidth);
                        return AT_RETURN_FAILURE;
                }
                break;
            }
            default:
                PLAT_WLAN_ERR("Error, mode = %d", params->mode);
                return AT_RETURN_FAILURE;
        }
        g_wlan_at_data.WiCal.power_onoff[params->group] = AT_FEATURE_ENABLE;
        break;
    }
    case AT_WICALDATA_ABS_IDX_FREQ:
        g_wlan_at_data.WiCal.crystal = (uint8)data;
        g_wlan_at_data.WiCal.crystal_onoff = AT_FEATURE_ENABLE;
        PLAT_WLAN_INFO("crystal_data = %d", (int)g_wlan_at_data.WiCal.crystal);
        break;
    case AT_WICALDATA_ABS_IDX_TEMP:
        g_wlan_at_data.WiCal.thermal = (uint8)data;
        g_wlan_at_data.WiCal.thermal_onoff = AT_FEATURE_ENABLE;
        PLAT_WLAN_INFO("thermal_data = %d", (int)g_wlan_at_data.WiCal.thermal);
        break;
    default:
        PLAT_WLAN_ERR("error type = %d", params->type);
        return AT_RETURN_FAILURE;
    }

    memcpy(&g_wlan_at_data.WiCalData, params, sizeof(g_wlan_at_data.WiCalData));
    
    return AT_RETURN_SUCCESS;
}

/*===========================================================================
 (16)^WICAL���á���ȡУ׼������״̬���Ƿ�֧�ֲ���
===========================================================================*/
/*****************************************************************************
 ��������  : wlan_cal_power_sprintf
 ��������  : ��У׼���ݰ��չ�������14���ŵ�����
 �������  : buf:���棻size: �����С��p_ch_pow: У׼���ݣ�ch_size:У׼���ݴ�С
 �������  : NA
 �� �� ֵ  : NA
*****************************************************************************/
STATIC int32 wlan_cal_power_sprintf(char *buf, int buf_size, AT_WICAL_CH_POWER_TYPE *p_ch_pow, int ch_size)
{
    int32   len = 0;
    uint8   i = 0, j = 0, ch_idx = 0, ch = 0, data = 0;
    if ((NULL == buf) || (buf_size <= 0) || (NULL == p_ch_pow) || (ch_size <= 0))
    {
        PLAT_WLAN_ERR("buf = %p, buf_size = %d, p_ch_pow = %p, ch_size = %d", buf, buf_size, p_ch_pow, ch_size);
        return len;
    }
    
    /* У׼���ݰ����ŵ����� */
    for (i = 0; i < ch_size - 1; i++)
    {
        ch_idx = i;
        for (j = i + 1; j < ch_size; j++)
        {
            if (p_ch_pow[j].ch < p_ch_pow[ch_idx].ch)
            {
                ch_idx = j;
            }
        }
        if (ch_idx != i)
        {
            ch = p_ch_pow[i].ch;
            data = p_ch_pow[i].data;
            p_ch_pow[i].ch = p_ch_pow[ch_idx].ch;
            p_ch_pow[i].data = p_ch_pow[ch_idx].data;
            p_ch_pow[ch_idx].ch = ch;
            p_ch_pow[ch_idx].data = data;
        }
    }
    i = 0, ch_idx = 0, ch = 0, len = 0;
    do
    {
        /* ��ȡ��ǰ��channel�μ���Ӧ��У׼data */
        while(i < ch_size)
        {
            if (ch < p_ch_pow[i].ch)
            {
                if (i + 1 >= ch_size)
                {
                    ch = WLAN_RTL_CHANNEL_24G_MAX;
                }
                else
                {
                    ch = ((p_ch_pow[i].ch + p_ch_pow[i + 1].ch) / 2);
                }
                data = p_ch_pow[i].data;
                break;
            }
            i++;
        }
        PLAT_WLAN_INFO("channel %d ~ %d power = %d", (ch_idx + 1), ch, data);
        /* ����У׼���� */
        while (ch_idx < ch)
        {
            ch_idx++;
            len += snprintf(&buf[len], (buf_size - len), "%02x", data);
        }
        /* д����һ�� */
        i++;
    }while(ch < WLAN_RTL_CHANNEL_24G_MAX);
    
    return len;
}

/*****************************************************************************
 ��������  : ATSetWifiCal
 ��������  : ����У׼������״̬
 �������  : onoff:0,����У׼��1,����У׼
 �������  : NA
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiCal(WLAN_AT_FEATURE_TYPE onoff)
{
    int     len = 0;
    uint8   idx = 0, ch_idx = 0;
    int8    acCmd[WIFI_CMD_MAX_SIZE] = {0};
    
    /* �ǽ���У׼״̬��ֱ�ӷ��� */
    PLAT_WLAN_INFO("onoff = %d, crystal_onoff = %d, thermal_onoff = %d"
                    , onoff, g_wlan_at_data.WiCal.crystal_onoff, g_wlan_at_data.WiCal.thermal_onoff);
    if (AT_FEATURE_DISABLE != onoff)
    {
        g_wlan_at_data.WiCal.crystal = 0;
        g_wlan_at_data.WiCal.thermal = 0;
        memset(g_wlan_at_data.WiCal.power, 0x0, sizeof(g_wlan_at_data.WiCal.power));
        g_wlan_at_data.WiCal.onoff = onoff;
        return AT_RETURN_SUCCESS;
    }

    /* freq cal */
    if (AT_FEATURE_ENABLE == g_wlan_at_data.WiCal.crystal_onoff)
    {
        SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE
            " efuse_set HW_11N_XCAP=%02x"
            , g_wlan_at_data.WiCal.crystal);
        WIFI_TEST_CMD(acCmd);
        g_wlan_at_data.WiCal.crystal_onoff = AT_FEATURE_DISABLE;
    }

    /* temp cal */
    if (AT_FEATURE_ENABLE == g_wlan_at_data.WiCal.thermal_onoff)
    {
        memset(acCmd,0,WIFI_CMD_MAX_SIZE);
        SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE
            " efuse_set HW_11N_THER=%02x", 
            g_wlan_at_data.WiCal.thermal);
        WIFI_TEST_CMD(acCmd);
        g_wlan_at_data.WiCal.thermal_onoff = AT_FEATURE_DISABLE;
    }

    /* power cal */
    for (idx = AT_TSELRF_A; IS_TSELRF_VAILD(idx); idx++)
    {
        PLAT_WLAN_INFO("idx = %d, power_onoff = %d", idx, g_wlan_at_data.WiCal.power_onoff[idx]);
        if (AT_FEATURE_ENABLE != g_wlan_at_data.WiCal.power_onoff[idx])
        {
            continue;
        }

        /* 11b�ŵ�У׼ */
        if (NULL != g_wical_pwr_param_set[idx].cck)
        {
            memset(acCmd,0, sizeof(acCmd));
            len = snprintf(acCmd, sizeof(acCmd), WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE
                " efuse_set %s=" , g_wical_pwr_param_set[idx].cck);
            len += wlan_cal_power_sprintf(&acCmd[len], (sizeof(acCmd) - len)
                , g_wlan_at_data.WiCal.power[idx].cck, ARRAY_SIZE(g_wlan_at_data.WiCal.power[idx].cck));
            WIFI_TEST_CMD(acCmd);
        }

        /* 40M����У׼ */
        if (NULL != g_wical_pwr_param_set[idx].th40_1s)
        {
            memset(acCmd,0, sizeof(acCmd));
            len = snprintf(acCmd, sizeof(acCmd), WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE
                " efuse_set %s=" , g_wical_pwr_param_set[idx].th40_1s);
            len += wlan_cal_power_sprintf(&acCmd[len], (sizeof(acCmd) - len)
                , g_wlan_at_data.WiCal.power[idx].ht40, ARRAY_SIZE(g_wlan_at_data.WiCal.power[idx].ht40));
            WIFI_TEST_CMD(acCmd);
        }

        /* 20M����У׼ */
        if (NULL != g_wical_pwr_param_set[idx].diff_th20)
        {
            memset(acCmd,0,WIFI_CMD_MAX_SIZE);
            len = snprintf(acCmd, sizeof(acCmd), WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE
                " efuse_set %s=" , g_wical_pwr_param_set[idx].diff_th20);
            for (ch_idx = 0; ch_idx < WLAN_RTL_CHANNEL_24G_MAX; ch_idx++)
            {
                len += snprintf(&acCmd[len], (sizeof(acCmd) - len), "%02x", g_wlan_at_data.WiCal.power[idx].diffht20);
            }
            WIFI_TEST_CMD(acCmd);
        }

        /* 11g�ŵ�У׼ */
        if (NULL != g_wical_pwr_param_set[idx].diff_th20_ofdm)
        {
            memset(acCmd,0,WIFI_CMD_MAX_SIZE);
            len = snprintf(acCmd, sizeof(acCmd), WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE
                " efuse_set %s=" , g_wical_pwr_param_set[idx].diff_th20_ofdm);
            for (ch_idx = 0; ch_idx < WLAN_RTL_CHANNEL_24G_MAX; ch_idx++)
            {
                len += snprintf(&acCmd[len], (sizeof(acCmd) - len), "%02x", g_wlan_at_data.WiCal.power[idx].diffofdm);
            }
            WIFI_TEST_CMD(acCmd);
        }

        /* ˫��У׼ */
        if (NULL != g_wical_pwr_param_set[idx].diff_th40_2s)
        {
            memset(acCmd,0,WIFI_CMD_MAX_SIZE);
            SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE
                " efuse_set %s=0000000000000000000000000000", g_wical_pwr_param_set[idx].diff_th40_2s);
            WIFI_TEST_CMD(acCmd);
        }

        g_wlan_at_data.WiCal.power_onoff[idx] = AT_FEATURE_DISABLE;
    }

    memset(acCmd,0,WIFI_CMD_MAX_SIZE);
    SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" efuse_sync");
    WIFI_TEST_CMD(acCmd);

    g_wlan_at_data.WiCal.onoff = onoff;
    return AT_RETURN_SUCCESS;
}

/*****************************************************************************
 ��������  : ATGetWifiCal
 ��������  : ��ȡУ׼������״̬
 �������  : NA
 �������  : NA
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
STATIC WLAN_AT_FEATURE_TYPE ATGetWifiCal(void)
{
    PLAT_WLAN_INFO("cal_switch = %d", g_wlan_at_data.WiCal.onoff);

    return  g_wlan_at_data.WiCal.onoff;
}

/*****************************************************************************
 ��������  : ATGetWifiCalSupport
 ��������  : �Ƿ�֧��У׼
 �������  : NA
 �������  : NA
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
STATIC WLAN_AT_FEATURE_TYPE ATGetWifiCalSupport(void)
{
    return AT_FEATURE_ENABLE;
}

/*===========================================================================
 (17)^WICALFREQ ���á���ѯƵ�ʲ���ֵ
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiCalFreq
 ��������  : ����Ƶ�ʲ���
 �������  : params:��������
 �������  : NA
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiCalFreq(WLAN_AT_WICALFREQ_STRU *params)
{
    int8    acCmd[WIFI_CMD_MAX_SIZE] = {0};
    
    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("type = %d, value = %d", params->type, (int)params->value);

    WLAN_SET_RXTX_STOP();

    SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_phypara xcap=%d", (int)params->value);
    WIFI_TEST_CMD(acCmd);

    memcpy(&g_wlan_at_data.WiCalFreq, params, sizeof(g_wlan_at_data.WiCalFreq));
    return AT_RETURN_SUCCESS;
}

/*****************************************************************************
 ��������  : ATGetWifiCalFreq
 ��������  : ����Ƶ�ʲ���
 �������  : NA
 �������  : params:��������
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
STATIC int32 ATGetWifiCalFreq(WLAN_AT_WICALFREQ_STRU *params)
{
    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("type = %d, value = %d", g_wlan_at_data.WiCalFreq.type, (int)g_wlan_at_data.WiCalFreq.value);
    memcpy(params, &g_wlan_at_data.WiCalFreq, sizeof(g_wlan_at_data.WiCalFreq));
    return AT_RETURN_SUCCESS;
}

/*===========================================================================
 (18)^WICALPOW ���á���ѯ���ʲ���ֵ
===========================================================================*/
/*****************************************************************************
 ��������  : ATSetWifiCalPOW
 ��������  : ���ù��ʲ���
 �������  : NA
 �������  : params:��������
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
STATIC int32 ATSetWifiCalPOW(WLAN_AT_WICALPOW_STRU *params)
{
    int8    acCmd[WIFI_CMD_MAX_SIZE] = {0};
    
    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("type = %d, value = %d, tselrf = %d", params->type, (int)params->value, WLAN_CURRENT_TSELRF);

    WLAN_SET_RXTX_STOP();

    SIZEOF_SNPRINTF(acCmd, WIFI_TOOL_IWPRIV" "WIFI_AP_INTERFACE" mp_txpower patha=%d,pathb=%d"
                    , (int)params->value, (int)params->value);
    WIFI_TEST_CMD(acCmd);
    memcpy(&g_wlan_at_data.WiCalPow, params, sizeof(g_wlan_at_data.WiCalPow));
    return AT_RETURN_SUCCESS;
}

/*****************************************************************************
 ��������  : ATGetWifiCalPOW
 ��������  : У׼���书��ʱ����ѯ��Ӧֵ
 �������  : NA
 �������  : NA
 �� �� ֵ  : int32
*****************************************************************************/
STATIC int32 ATGetWifiCalPOW(WLAN_AT_WICALPOW_STRU *params)
{
    ASSERT_NULL_POINTER(params, AT_RETURN_FAILURE);
    PLAT_WLAN_INFO("Entry type = %d, value = %d", g_wlan_at_data.WiCalPow.type, (int)g_wlan_at_data.WiCalPow.value);
    params->type = g_wlan_at_data.WiCalPow.type;
    switch(g_wlan_at_data.WiMode.mode)
    {
    case AT_WIMODE_80211n:
        params->value = 32; /* 802.11n */
        break;
    case AT_WIMODE_80211g:
        params->value = 35; /* 802.11g */
        break;
    case AT_WIMODE_80211b:
        params->value = 31; /* 802.11b */
        break;
    default:
        PLAT_WLAN_ERR("error mode = %d", g_wlan_at_data.WiMode.mode);
        return AT_RETURN_FAILURE;
    }
    PLAT_WLAN_INFO("Exit type = %d, value = %d", params->type, (int)params->value);
    return AT_RETURN_SUCCESS;
}



STATIC WLAN_CHIP_OPS rtl_def_ops = 
{
    .WlanATSetWifiEnable = ATSetWifiEnable,
    .WlanATGetWifiEnable = ATGetWifiEnable,
    
    .WlanATSetWifiMode   = ATSetWifiMode,
    .WlanATGetWifiMode   = ATGetWifiMode,
    .WlanATGetWifiModeSupport = ATGetWifiModeSupport, 

    .WlanATSetWifiBand = ATSetWifiBand,
    .WlanATGetWifiBand = ATGetWifiBand,
    .WlanATGetWifiBandSupport = ATGetWifiBandSupport,

    .WlanATSetWifiFreq = ATSetWifiFreq,
    .WlanATGetWifiFreq = ATGetWifiFreq,

    .WlanATSetWifiDataRate = ATSetWifiDataRate,
    .WlanATGetWifiDataRate = ATGetWifiDataRate,

    .WlanATSetWifiPOW = ATSetWifiPOW,
    .WlanATGetWifiPOW = ATGetWifiPOW,

    .WlanATSetWifiTX = ATSetWifiTX,
    .WlanATGetWifiTX = ATGetWifiTX,

    .WlanATSetWifiRX = ATSetWifiRX,
    .WlanATGetWifiRX = ATGetWifiRX,

    .WlanATSetWifiRPCKG = ATSetWifiRPCKG,
    .WlanATGetWifiRPCKG = ATGetWifiRPCKG,

    .WlanATGetWifiInfo  = ATGetWifiInfo,

    .WlanATGetWifiPlatform = ATGetWifiPlatform,
    
    .WlanATGetTSELRF = NULL,
    .WlanATSetTSELRF = ATSetTSELRF,
    .WlanATGetTSELRFSupport = ATGetTSELRFSupport, 

    .WlanATSetWifiParange = ATSetWifiParange,
    .WlanATGetWifiParange = ATGetWifiParange,

    .WlanATGetWifiParangeSupport = ATGetWifiParangeSupport,
    
    .WlanATGetWifiCalTemp = ATGetWifiCalTemp,
    .WlanATSetWifiCalTemp = ATSetWifiCalTemp,
    
    .WlanATSetWifiCalData = ATSetWifiCalData,
    .WlanATGetWifiCalData = ATGetWifiCalData,
    
    .WlanATSetWifiCal = ATSetWifiCal,
    .WlanATGetWifiCal = ATGetWifiCal,
    .WlanATGetWifiCalSupport = ATGetWifiCalSupport,
    
    .WlanATSetWifiCalFreq = ATSetWifiCalFreq,
    .WlanATGetWifiCalFreq = ATGetWifiCalFreq,
    
    .WlanATSetWifiCalPOW = ATSetWifiCalPOW,
    .WlanATGetWifiCalPOW = ATGetWifiCalPOW
};

/*****************************************************************************
��������  : wlan_at_init_rtl_def
��������  : rtl8192оƬװ���ӿڳ�ʼ������
�������  : NA
�������  : NA
�� �� ֵ  : int
*****************************************************************************/
int __init wlan_at_init_rtl_def(void)
{
    PLAT_WLAN_INFO("enter");
#if defined(FEATURE_HUAWEI_MBB_RTL8189)
    wlan_at_reg_chip(rtl8189, &rtl_def_ops);
#elif defined(FEATURE_HUAWEI_MBB_RTL8192)
    wlan_at_reg_chip(rtl8192, &rtl_def_ops);
#endif
    PLAT_WLAN_INFO("exit");
    return AT_RETURN_SUCCESS;
}
module_init(wlan_at_init_rtl_def); /*lint !e529*/

