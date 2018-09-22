#!/bin/sh

#******************************************************************#
#***************               ����˵��                 ***********#
#******************************************************************#
#CONFIG_EXT_CLK_26M         //�Ƿ�֧��26mʱ�Ӿ���
#CONFIG_PHY_EAT_40MHZ       //�Ƿ�֧��40mʱ�Ӿ���
#CONFIG_RTL_88E_SUPPORT     //RTL8189оƬ��Ҫ����Ϊy
#CONFIG_RTL_92E_SUPPORT     //RTL8192оƬ��Ҫ����Ϊy
#WIFI_MODULE_NAME           //wifi ������ģ������

#CONFIG_AUTOCH_TIMER            //֧�ֶ�̬�Զ��ŵ�ѡ������
#CFG_RTL_SDIO30                 //֧��SDIO3.0����
#SDIO_AP_PS                     //֧�ֵ͹���ģʽ(����֧��WiFi����BB������ز�Ʒ����ʡ�繦��)
#INTEL_BEACON_POWER_NO_INC      //�ر����intel����������Զ������power�Ĵ���
#WLAN_PLATFORM_POWER_EXT_LNA    //֧�����LNA

#WLAN_PLATFORM_BALONG_V3        //����V3ƽ̨���Ժ�
#WLAN_PLATFORM_BALONG_V7        //����V7ƽ̨���Ժ�
#WLAN_PLATFORM_QUALCOMM_9x15    //��ͨ9x15ƽ̨���Ժ�
#WLAN_PLATFORM_HUAWEI_COMMON    //��Ϊ��Ʒ��Ҫ����������
#WLAN_PLATFORM_HUAWEI_FACTORY   //��Ƭ�汾��Ҫ���������

#�����еĺ궨��,���ݲ�ͬ��Ʒ���岻ͬ�ĺ� 
#CFG_WIFI_EXTRA_NORMAL      //Ϊ�����汾��Ҫ����ĺ�
#CFG_WIFI_EXTRA_FACTORY     //Ϊ��Ƭ�汾��Ҫ����ĺ�
#CFG_WIFI_EXTRA_COMMON      //Ϊ��������Ƭ�汾����Ҫ����ĺ�

#******************************************************************#
#***************               ����ʵ��                 ***********#
#******************************************************************#
WIFI_MODULE_NAME=rtl8192es
export CONFIG_RTL_92E_SUPPORT=y
export CONFIG_PHY_EAT_40MHZ=y

#Ĭ�Ϻ궨��
CFG_WIFI_EXTRA_NORMAL=""
CFG_WIFI_EXTRA_COMMON="-DCFG_RTL_SDIO30 -DWLAN_PLATFORM_BALONG_V7 -DINTEL_BEACON_POWER_NO_INC -DSOFTAP_PS_DURATION -DSDIO_AP_PS"
export CFG_WIFI_EXTRA_CFLAGS="${CFG_WIFI_EXTRA_COMMON}"
#��Ʒ�궨��


