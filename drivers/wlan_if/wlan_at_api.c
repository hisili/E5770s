

/* linux ϵͳͷ�ļ� */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>


/* ƽ̨ͷ�ļ� */
#include <product_config.h>
#include <mbb_config.h>

#include "wlan_at.h"

/* ��Ӧ��wifiоƬ�������� */
STATIC WLAN_CHIP_OPS* g_wlan_ops[WLAN_CHIP_MAX] = {NULL};

/* Ĭ��wtʹ�õ�һ��оƬУ׼�����ⲿ���������󣬱���cradle����ȣ���Ҫ�޸ĸ�ֵ�߼� */
STATIC int32 g_cur_chip = -1;

/* �ж������Ƿ���Ч */
#define CHIP_IDX_IS_VALID(idx) ((WLAN_CHIP_MAX > idx) && (idx > chipstub) && (NULL != g_wlan_ops[idx]))
/* ������Ч�Ķ��� */
#define ASSERT_CHIP_IDX_VALID(idx, ret)  do { \
    if ((WLAN_CHIP_MAX <= idx) || (idx <= chipstub))\
    {\
        PLAT_WLAN_ERR("chip idx valid = %d", idx); \
        return ret;\
    }\
    if (NULL == g_wlan_ops[idx])\
    {\
        PLAT_WLAN_ERR("chip idx %d valid = NULL", idx); \
        return ret;\
    }\  
}while(0)

/* ƽ̨�ṩ�Ľӿڣ��ж��Ƿ����ģʽ */
extern int bsp_get_factory_mode(void);

//////////////////////////////////////////////////////////////////////////
/*(1)^WIENABLE ����WiFiģ��ʹ�� */
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ��������  : int32 WlanATSetWifiEnable(WLAN_AT_WIENABLE_TYPE onoff)
 ��������  : ����wifi �������ģʽ������ģʽ���ر�wifi
 �������  :  0  �ر�
              1  ������ģʽ
              2  �򿪲���ģʽ
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : 
*****************************************************************************/
int32 WlanATSetWifiEnable(WLAN_AT_WIENABLE_TYPE onoff)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiEnable, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiEnable(onoff);
}
/*****************************************************************************
 ��������  : WLAN_AT_WIENABLE_TYPE WlanATGetWifiEnable()
 ��������  : ��ȡ��ǰ��WiFiģ��ʹ��״̬
 �������  : NA
 �������  : NA
 �� �� ֵ  : 0  �ر�
             1  ����ģʽ(����ģʽ)
             2  ����ģʽ(������ģʽ)
 ����˵��  : 
*****************************************************************************/
WLAN_AT_WIENABLE_TYPE WlanATGetWifiEnable(void)
{ 
    static int is_mp_start = 0;
    if (!is_mp_start)
    {
        is_mp_start = 1;
        (void)wlan_set_log_flag(WLAN_LOG((WLAN_LOG_STDOUT | WLAN_LOG_FILE), WLAN_LOG_DRV_LOW));
    }

    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_WIENABLE_OFF);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiEnable, AT_WIENABLE_OFF);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiEnable();
}

//////////////////////////////////////////////////////////////////////////
/*(2)^WIMODE ����WiFiģʽ���� Ŀǰ��Ϊ��ģʽ����*/
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ��������  : int32 WlanATSetWifiMode(WLAN_AT_WIMODE_TYPE mode)
 ��������  : ����WiFi AP֧�ֵ���ʽ
 �������  : 0,  CWģʽ
             1,  802.11a��ʽ
             2,  802.11b��ʽ
             3,  802.11g��ʽ
             4,  802.11n��ʽ
             5,  802.11ac��ʽ
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : 
*****************************************************************************/
int32 WlanATSetWifiMode(WLAN_AT_WIMODE_TYPE mode)
{
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiMode, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiMode(mode);
}

/*****************************************************************************
 ��������  : int32 WlanATGetWifiMode(WLAN_AT_BUFFER_STRU *strBuf)
 ��������  : ��ȡ��ǰWiFi֧�ֵ���ʽ
             ��ǰģʽ�����ַ�����ʽ����eg: 2
 �������  : NA
 �������  : NA
 �� �� ֵ  : NA
 ����˵��  : 
*****************************************************************************/
int32 WlanATGetWifiMode(WLAN_AT_BUFFER_STRU *strBuf)
{
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiMode, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiMode(strBuf);
}

/*****************************************************************************
 ��������  : int32 WlanATGetWifiModeSupport(WLAN_AT_BUFFER_STRU *strBuf)
 ��������  : ��ȡWiFiоƬ֧�ֵ�����Э��ģʽ
             ֧�ֵ�����ģʽ�����ַ�����ʽ����eg: 2,3,4
 �������  : NA
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : 
*****************************************************************************/
int32 WlanATGetWifiModeSupport(WLAN_AT_BUFFER_STRU *strBuf)
{
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiModeSupport, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiModeSupport(strBuf);
}

//////////////////////////////////////////////////////////////////////////
/*(3)^WIBAND ����WiFi������� */
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ��������  : int32 WlanATSetWifiBand(WLAN_AT_WIBAND_TYPE width)
 ��������  : ��������wifi����
 �������  : 0 20M
             1 40M
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : ֻ����nģʽ�²ſ�������40M����
*****************************************************************************/
int32 WlanATSetWifiBand(WLAN_AT_WIBAND_TYPE band)
{
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiBand, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiBand(band);
}

/*****************************************************************************
 ��������  : int32 WlanATGetWifiBand(WLAN_AT_BUFFER_STRU *strBuf)
 ��������  :��ȡ��ǰ�������� 
            ��ǰ�������ַ�����ʽ����eg: 0
 �������  : NA
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : 
*****************************************************************************/
int32 WlanATGetWifiBand(WLAN_AT_BUFFER_STRU *strBuf)
{
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiBand, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiBand(strBuf);
}

/*****************************************************************************
 ��������  : int32 WlanATGetWifiBandSupport(WLAN_AT_BUFFER_STRU *strBuf)
 ��������  :��ȡWiFi֧�ֵĴ������� 
            ֧�ִ������ַ�����ʽ����eg: 0,1
 �������  : NA
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : 
*****************************************************************************/
int32 WlanATGetWifiBandSupport(WLAN_AT_BUFFER_STRU *strBuf)
{
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiBandSupport, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiBandSupport(strBuf);
}

//////////////////////////////////////////////////////////////////////////
/*(4)^WIFREQ ����WiFiƵ�� */
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ��������  : int32 WlanATSetWifiFreq(WLAN_AT_WIFREQ_STRU *pFreq)
 ��������  : ����WiFiƵ��
 �������  : NA
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : 
*****************************************************************************/
int32 WlanATSetWifiFreq(WLAN_AT_WIFREQ_STRU *pFreq)
{
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiFreq, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiFreq(pFreq);
}

/*****************************************************************************
 ��������  : int32 WlanATGetWifiFreq(WLAN_AT_WIFREQ_STRU *pFreq)
 ��������  : ��ȡWiFiƵ��
 �������  : NA
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : 
*****************************************************************************/
int32 WlanATGetWifiFreq(WLAN_AT_WIFREQ_STRU *pFreq)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiFreq, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiFreq(pFreq);
}

//////////////////////////////////////////////////////////////////////////
/*(5)^WIDATARATE ���úͲ�ѯ��ǰWiFi���ʼ�����
  WiFi���ʣ���λΪ0.01Mb/s��ȡֵ��ΧΪ0��65535 */
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ��������  : int32 WlanATSetWifiDataRate(uint32 rate)
 ��������  : ����WiFi��������
 �������  : NA
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : 
*****************************************************************************/
int32 WlanATSetWifiDataRate(uint32 rate)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiDataRate, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiDataRate(rate);
}
/*****************************************************************************
 ��������  : uint32 WlanATGetWifiDataRate()
 ��������  : ��ѯ��ǰWiFi��������
 �������  : NA
 �������  : NA
 �� �� ֵ  : wifi����
 ����˵��  : 
*****************************************************************************/
uint32 WlanATGetWifiDataRate(void)
{ 
    ASSERT_CHIP_IDX_VALID(g_cur_chip, 0);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiDataRate, 0);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiDataRate();
}

//////////////////////////////////////////////////////////////////////////
/*(6)^WIPOW ������WiFi���书�� 
   WiFi���书�ʣ���λΪ0.01dBm��ȡֵ��ΧΪ -32768��32767 */
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ��������  : int32 WlanATSetWifiPOW(int32 power_dBm_percent)
 ��������  : ����WiFi���书��
 �������  : NA
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : 
*****************************************************************************/
int32 WlanATSetWifiPOW(int32 power_dBm_percent)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiPOW, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiPOW(power_dBm_percent);
}

/*****************************************************************************
 ��������  : int32 WlanATGetWifiPOW()
 ��������  : ��ȡWiFi��ǰ���书��
 �������  : NA
 �������  : NA
 �� �� ֵ  : NA
 ����˵��  : 
*****************************************************************************/
int32 WlanATGetWifiPOW(void)
{ 
    ASSERT_CHIP_IDX_VALID(g_cur_chip, 0);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiPOW, 0);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiPOW();
}

//////////////////////////////////////////////////////////////////////////
/*(7)^WITX ������WiFi��������� */
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ��������  : int32 WlanATSetWifiTX(WLAN_AT_FEATURE_TYPE onoff)
 ��������  : �򿪻�ر�wifi�����
 �������  : 0 �ر�
             1 ��
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : 
*****************************************************************************/
int32 WlanATSetWifiTX(WLAN_AT_FEATURE_TYPE onoff)
{  
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiTX, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiTX(onoff);
}

/*****************************************************************************
 ��������  : WLAN_AT_FEATURE_TYPE WlanATGetWifiTX()
 ��������  : ��ѯ��ǰWiFi�����״̬��Ϣ
 �������  : NA
 �������  : NA
 �� �� ֵ  : 0 �رշ����
             1 �򿪷����
 ����˵��  : 
*****************************************************************************/
WLAN_AT_FEATURE_TYPE WlanATGetWifiTX(void)
{ 
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_FEATURE_DISABLE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiTX, AT_FEATURE_DISABLE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiTX();
}

//////////////////////////////////////////////////////////////////////////
/*(8)^WIRX ����WiFi���ջ����� */
//////////////////////////////////////////////////////////////////////////
int32 WlanATSetWifiRX(WLAN_AT_WIRX_STRU *params)
{  
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiRX, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiRX(params);
}

/*****************************************************************************
 ��������  : int32 WlanATGetWifiRX(WLAN_AT_WIRX_STRU *params)
 ��������  : ��ȡwifi���ջ���״̬
 �������  : NA
 �������  : NA
 �� �� ֵ  : NA
 ����˵��  : 
*****************************************************************************/
int32 WlanATGetWifiRX(WLAN_AT_WIRX_STRU *params)
{ 
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiRX, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiRX(params);
}

//////////////////////////////////////////////////////////////////////////
/*(9)^WIRPCKG ��ѯWiFi���ջ�����룬�ϱ����յ��İ�������*/
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ��������  : int32 WlanATSetWifiRPCKG(int32 flag)
 ��������  : ���Wifi����ͳ�ư�Ϊ��
 �������  : 0 ���wifiͳ�ư�
             ��0 ��Ч����
 �������  : NA
 �� �� ֵ  : 0 �ɹ�
             1 ʧ��
 ����˵��  : 
*****************************************************************************/
int32 WlanATSetWifiRPCKG(int32 flag)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiRPCKG, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiRPCKG(flag);
}

/*****************************************************************************
 ��������  : int32 WlanATSetWifiRPCKG(int32 flag)
 ��������  : ��ѯWiFi���ջ�����룬�ϱ����յ��İ�������
 �������  : WLAN_AT_WIRPCKG_STRU *params
 �������  : uint16 good_result; //������յ��ĺð�����ȡֵ��ΧΪ0~65535
             uint16 bad_result;  //������յ��Ļ�������ȡֵ��ΧΪ0~65535
 �� �� ֵ  : NA
 ����˵��  : 
*****************************************************************************/
int32 WlanATGetWifiRPCKG(WLAN_AT_WIRPCKG_STRU *params)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiRPCKG, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiRPCKG(params);
}

/*===========================================================================
 (10)^WIINFO ��ѯWiFi�������Ϣ
===========================================================================*/
/* ˵��: WlanATGetWifiInfo ����ƽ̨ͨ����nvʵ�֣�wifi����ʵ�ִ˽ӿ� */
/*int32 WlanATGetWifiInfo(WLAN_AT_WIINFO_STRU *params)
{
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiInfo, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiInfo(params);
}*/

//////////////////////////////////////////////////////////////////////////
/*(11)^WIPLATFORM ��ѯWiFi����ƽ̨��Ӧ����Ϣ */
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ��������  : WLAN_AT_WIPLATFORM_TYPE WlanATGetWifiPlatform()
 ��������  : ��ѯWiFi����ƽ̨��Ӧ����Ϣ
 �������  : NA
 �������  : NA
 �� �� ֵ  : NA
 ����˵��  : 
*****************************************************************************/
WLAN_AT_WIPLATFORM_TYPE WlanATGetWifiPlatform(void)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiPlatform, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiPlatform();
}

//////////////////////////////////////////////////////////////////////////
/*(12)^TSELRF ��ѯ���õ����WiFi��Ƶͨ·*/
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ��������  : int32 WlanATSetTSELRF(uint32 group)
 ��������  : �������ߣ��Ƕ�ͨ·��0
 �������  : NA
 �������  : NA
 �� �� ֵ  : NA
 ����˵��  : 
*****************************************************************************/
int32 WlanATSetTSELRF(uint32 group)
{  
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetTSELRF, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetTSELRF(group);
}

/*****************************************************************************
 ��������  : int32 WlanATGetTSELRFSupport(WLAN_AT_BUFFER_STRU *strBuf)
 ��������  : ֧�ֵ������������У����ַ�����ʽ����eg: 0,1,2,3
 �������  : NA
 �������  : NA
 �� �� ֵ  : NA
 ����˵��  : 
*****************************************************************************/
int32 WlanATGetTSELRFSupport(WLAN_AT_BUFFER_STRU *strBuf)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetTSELRFSupport, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetTSELRFSupport(strBuf);
}

//////////////////////////////////////////////////////////////////////////
/*(13)^WiPARANGE���á���ȡWiFi PA���������*/
//////////////////////////////////////////////////////////////////////////
/*****************************************************************************
 ��������  : int32 WlanATSetWifiParange(WLAN_AT_WiPARANGE_TYPE pa_type)
 ��������  : ����WiFi PA���������
 �������  : NA
 �������  : NA
 �� �� ֵ  : NA
 ����˵��  : 
*****************************************************************************/
int32 WlanATSetWifiParange(WLAN_AT_WiPARANGE_TYPE pa_type)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiParange, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiParange(pa_type);
}

/*****************************************************************************
 ��������  : WLAN_AT_WiPARANGE_TYPE WlanATGetWifiParange()
 ��������  : ��ȡWiFi PA���������
 �������  : NA
 �������  : NA
 �� �� ֵ  : NA
 ����˵��  : 
*****************************************************************************/
WLAN_AT_WiPARANGE_TYPE WlanATGetWifiParange(void)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_WiPARANGE_BUTT);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiParange, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiParange();
}

/*****************************************************************************
 ��������  : int32 WlanATGetWifiParangeSupport(WLAN_AT_BUFFER_STRU *strBuf)
 ��������  : ֧�ֵ�paģʽ���У����ַ�����ʽ����eg: l,h
 �������  : NA
 �������  : NA
 �� �� ֵ  : NA
 ����˵��  : 
*****************************************************************************/
int32 WlanATGetWifiParangeSupport(WLAN_AT_BUFFER_STRU *strBuf)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiParangeSupport, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiParangeSupport(strBuf);
}


/*===========================================================================
 (14)^WICALTEMP���á���ȡWiFi���¶Ȳ���ֵ
===========================================================================*/
/*****************************************************************************
 ��������  : int32 WlanATGetWifiCalTemp(WLAN_AT_WICALTEMP_STRU *params)
 ��������  : ����WiFi���¶Ȳ���ֵ
 �������  : NA
 �������  : params:�¶Ȳ�������
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
int32 WlanATGetWifiCalTemp(WLAN_AT_WICALTEMP_STRU *params)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiCalTemp, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiCalTemp(params);
}

/*****************************************************************************
 ��������  : int32 WlanATGetWifiCalTemp(WLAN_AT_WICALTEMP_STRU *params)
 ��������  : ����WiFi���¶Ȳ���ֵ
 �������  : params:�¶Ȳ�������
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
int32 WlanATSetWifiCalTemp(WLAN_AT_WICALTEMP_STRU *params)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiCalTemp, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiCalTemp(params);
}

/*===========================================================================
 (15)^WICALDATA���á���ȡָ�����͵�WiFi��������
===========================================================================*/
/*****************************************************************************
 ��������  : int32 WlanATGetWifiCalData(WLAN_AT_WICALDATA_STRU * params)
 ��������  : ָ�����͵�WiFi��������
 �������  : NA
 �������  : params:��������
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
int32 WlanATGetWifiCalData(WLAN_AT_WICALDATA_STRU * params)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip,AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiCalData,AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiCalData(params);
}

/*****************************************************************************
 ��������  : int32 WlanATSetWifiCalData(WLAN_AT_WICALDATA_STRU *params)
 ��������  : ָ�����͵�WiFi��������
 �������  : params:��������
 �������  : NA
 �� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
int32 WlanATSetWifiCalData(WLAN_AT_WICALDATA_STRU *params)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiCalData, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiCalData(params);
}

/*===========================================================================
 (16)^WICAL���á���ȡУ׼������״̬���Ƿ�֧�ֲ���
===========================================================================*/
/*****************************************************************************
 ��������  : int32 WlanATSetWifiCal(WLAN_AT_FEATURE_TYPE onoff)
 ��������  : ����У׼������״̬
 �������  : onoff:0,����У׼��1,����У׼
 �������  : NA
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
int32 WlanATSetWifiCal(WLAN_AT_FEATURE_TYPE onoff)
{  
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiCal, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiCal(onoff);
}

/*****************************************************************************
 ��������  : WLAN_AT_FEATURE_TYPE WlanATGetWifiCal(void)
 ��������  : ��ȡУ׼������״̬
 �������  : NA
 �������  : NA
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
WLAN_AT_FEATURE_TYPE WlanATGetWifiCal(void)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_FEATURE_DISABLE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiCal, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiCal();
}

/*****************************************************************************
 ��������  : WLAN_AT_FEATURE_TYPE WlanATGetWifiCalSupport(void)
 ��������  : �Ƿ�֧��У׼
 �������  : NA
 �������  : NA
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
WLAN_AT_FEATURE_TYPE WlanATGetWifiCalSupport(void)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_FEATURE_DISABLE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiCalSupport, AT_FEATURE_DISABLE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiCalSupport();
}

/*===========================================================================
 (17)^WICALFREQ ���á���ѯƵ�ʲ���ֵ
===========================================================================*/
/*****************************************************************************
 ��������  : int32 WlanATSetWifiCalFreq(WLAN_AT_WICALFREQ_STRU *params)
 ��������  : ����Ƶ�ʲ���
 �������  : params:��������
 �������  : NA
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
int32 WlanATSetWifiCalFreq(WLAN_AT_WICALFREQ_STRU *params)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiCalFreq, AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiCalFreq(params);
}

/*****************************************************************************
 ��������  : int32 WlanATGetWifiCalFreq(WLAN_AT_WICALFREQ_STRU *params)
 ��������  : ����Ƶ�ʲ���
 �������  : NA
 �������  : params:��������
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
int32 WlanATGetWifiCalFreq(WLAN_AT_WICALFREQ_STRU *params)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiCalFreq,AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiCalFreq(params);
}

/*===========================================================================
 (18)^WICALPOW ���á���ѯ���ʲ���ֵ
===========================================================================*/
/*****************************************************************************
 ��������  : int32 WlanATGetWifiCalFreq(WLAN_AT_WICALFREQ_STRU *params)
 ��������  : ���ù��ʲ���
 �������  : NA
 �������  : params:��������
 �� �� ֵ  : WLAN_AT_FEATURE_TYPE
*****************************************************************************/
int32 WlanATSetWifiCalPOW(WLAN_AT_WICALPOW_STRU *params)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATSetWifiCalPOW,AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATSetWifiCalPOW(params);
}

/*****************************************************************************
 ��������  : int32 WlanATGetWifiCalPOW(WLAN_AT_WICALPOW_STRU *params)
 ��������  : У׼���书��ʱ����ѯ��Ӧֵ
 �������  : NA
 �������  : NA
 �� �� ֵ  : int32
*****************************************************************************/
int32 WlanATGetWifiCalPOW(WLAN_AT_WICALPOW_STRU *params)
{   
    ASSERT_CHIP_IDX_VALID(g_cur_chip, AT_RETURN_FAILURE);
    ASSERT_NULL_POINTER(g_wlan_ops[g_cur_chip]->WlanATGetWifiCalPOW,AT_RETURN_FAILURE);
    return g_wlan_ops[g_cur_chip]->WlanATGetWifiCalPOW(params);
}

/***********************************************************************************
Function:          wlan_at_switch_chip
Description:    wt ģ���ʼ��
Calls:
Input:           
Output:            NA
Return:            NULL or node
                 
************************************************************************************/
void wlan_at_switch_chip(int chip_type)
{
	PLAT_WLAN_INFO("switch chip from (%d)%s to (%d)%s \n"
        , g_cur_chip, wlan_chip_type2name(g_cur_chip), chip_type, wlan_chip_type2name(chip_type));
    g_cur_chip = (int32)chip_type;
}
EXPORT_SYMBOL(wlan_at_switch_chip);

#if (MBB_WIFI_CHIP2 == bcm43236)
/***********************************************************************************
Function:          wlan_at_cradle_insert
Description:    wt ģ���ʼ��
Calls:
Input:           
Output:            NA
Return:            NULL or node
                 
************************************************************************************/
int wlan_at_cradle_insert(void)
{
    if (bcm43236 == g_cur_chip)
    {
        return AT_RETURN_SUCCESS;
    }
    else
    {
        return AT_RETURN_FAILURE;
    }
    PLAT_WLAN_INFO("wlan at switch chip to bcm43236 %d\n", g_cur_chip);
}
EXPORT_SYMBOL(wlan_at_cradle_insert);
#endif

/*****************************************************************************
��������  : wlan_at_reg_chip
��������  : оƬע�ắ��
�������  : NA
�������  : NA
�� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
WLAN_AT_RETURN_TYPE wlan_at_reg_chip(int32 chip_type, WLAN_CHIP_OPS *chip_ops)
{
    /* 0:����ģʽ��1:����ʹ��ģʽ��Ĭ������ģʽ, ��ȡnv36���ж��Ƿ����ģʽ����δʹ�� */
#ifdef MBB_WIFI_CHECK_FACTORY_MODE
    int wlan_mode = 1; 

    wlan_mode = bsp_get_factory_mode();
    PLAT_WLAN_INFO("factory_mode = %d",wlan_mode);
    if (1 == wlan_mode)
    {
        /* ����ģʽ������ */
        return AT_RETURN_FAILURE;
    }
#endif /* MBB_WIFI_CHECK_FACTORY_MODE */

    if (chip_type < 0 || chip_type >= ARRAY_SIZE(g_wlan_ops))
    {
        PLAT_WLAN_ERR("chip idx valid = %d", chip_type);
        return AT_RETURN_FAILURE;
    }

    PLAT_WLAN_INFO("chip %d = (%s) reg %p to %p"
        , chip_type, wlan_chip_type2name(chip_type), g_wlan_ops[chip_type], chip_ops);
    g_wlan_ops[chip_type] = chip_ops;
    if (!CHIP_IDX_IS_VALID(g_cur_chip))
    {
        g_cur_chip = chip_type;
    }
    PLAT_WLAN_INFO("Exit, g_cur_chip= %d\n",g_cur_chip);
    return AT_RETURN_SUCCESS;
}
EXPORT_SYMBOL(wlan_at_reg_chip);

/*****************************************************************************
��������  : wlan_at_unreg_chip
��������  : оƬȥע�ắ��
�������  : NA
�������  : NA
�� �� ֵ  : WLAN_AT_RETURN_TYPE
*****************************************************************************/
WLAN_AT_RETURN_TYPE wlan_at_unreg_chip(int32 chip_type)
{
    ASSERT_CHIP_IDX_VALID(chip_type, AT_RETURN_SUCCESS);
    
    PLAT_WLAN_INFO("Exit, chip %d = (%s) unreg from %p", chip_type, wlan_chip_type2name(chip_type), g_wlan_ops[chip_type]);
    g_wlan_ops[chip_type] = NULL;
    
    return AT_RETURN_SUCCESS;
}
EXPORT_SYMBOL(wlan_at_unreg_chip);

/*****************************************************************************
 ��������  : wlan_wt_init
 ��������  : wlan at root ��ʼ������
 �������  : NA
 �������  : NA
 �� �� ֵ  : int
*****************************************************************************/
static int __init wlan_wt_init(void)
{
    int i = 0;
    PLAT_WLAN_INFO("enter curr_chip %d = (%s)", g_cur_chip, wlan_chip_type2name(g_cur_chip));
    
    for (i = 0; i < ARRAY_SIZE(g_wlan_ops); i++)
    {
        if (NULL != g_wlan_ops[i])
        {
            PLAT_WLAN_INFO("chip %d = (%s) reg to %p", i, wlan_chip_type2name(i), g_wlan_ops[i]);
        }
    }

    PLAT_WLAN_INFO("exit");
    return AT_RETURN_SUCCESS;
}

 /*****************************************************************************
 ��������  : wlan_wt_exit
 ��������  : wlan at root ȥ��ʼ������
 �������  : NA
 �������  : NA
 �� �� ֵ  : int
*****************************************************************************/
static void __exit wlan_wt_exit(void)
{
    PLAT_WLAN_INFO("enter, curr_chip = %d", g_cur_chip);
    memset(g_wlan_ops,0x0,sizeof(g_wlan_ops));
    g_cur_chip = -1;
    PLAT_WLAN_INFO("exit");
}

module_init(wlan_wt_init); /*lint !e529*/
module_exit(wlan_wt_exit); /*lint !e529*/

MODULE_AUTHOR("Huawei");
MODULE_DESCRIPTION("Huawei WT");
MODULE_LICENSE("GPL");

//////////////////////////////////////////////////////////////////////////
EXPORT_SYMBOL(WlanATSetWifiEnable);
EXPORT_SYMBOL(WlanATGetWifiEnable);
EXPORT_SYMBOL(WlanATSetWifiMode);
EXPORT_SYMBOL(WlanATGetWifiMode);
EXPORT_SYMBOL(WlanATGetWifiModeSupport);
EXPORT_SYMBOL(WlanATSetWifiBand);
EXPORT_SYMBOL(WlanATGetWifiBand);
EXPORT_SYMBOL(WlanATGetWifiBandSupport);
EXPORT_SYMBOL(WlanATSetWifiFreq);
EXPORT_SYMBOL(WlanATGetWifiFreq);
EXPORT_SYMBOL(WlanATSetWifiDataRate);
EXPORT_SYMBOL(WlanATGetWifiDataRate);
EXPORT_SYMBOL(WlanATSetWifiPOW);
EXPORT_SYMBOL(WlanATGetWifiPOW);
EXPORT_SYMBOL(WlanATSetWifiTX);
EXPORT_SYMBOL(WlanATGetWifiTX);
EXPORT_SYMBOL(WlanATSetWifiRX);
EXPORT_SYMBOL(WlanATGetWifiRX);
EXPORT_SYMBOL(WlanATSetWifiRPCKG);
EXPORT_SYMBOL(WlanATGetWifiRPCKG);
EXPORT_SYMBOL(WlanATGetWifiPlatform);
EXPORT_SYMBOL(WlanATSetTSELRF);
EXPORT_SYMBOL(WlanATGetTSELRFSupport);
EXPORT_SYMBOL(WlanATSetWifiParange);
EXPORT_SYMBOL(WlanATGetWifiParange);
EXPORT_SYMBOL(WlanATGetWifiParangeSupport);
EXPORT_SYMBOL(WlanATSetWifiCalTemp);
EXPORT_SYMBOL(WlanATGetWifiCalTemp);
EXPORT_SYMBOL(WlanATSetWifiCalData);
EXPORT_SYMBOL(WlanATSetWifiCal);
EXPORT_SYMBOL(WlanATGetWifiCal);
EXPORT_SYMBOL(WlanATGetWifiCalSupport);
EXPORT_SYMBOL(WlanATSetWifiCalPOW);
EXPORT_SYMBOL(WlanATGetWifiCalFreq);
