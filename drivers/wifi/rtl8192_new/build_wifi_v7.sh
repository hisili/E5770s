#!/bin/sh

#******************************************************************#
#***************               ����ʵ��                 ***********#
#******************************************************************#
#WIFI_HOME                  //�������Ŀ¼����������ļ�(outputĿ¼)�����������м��ļ�(OUT_WIFIĿ¼)�ȣ�Ĭ������Ϊ��ǰĿ¼
#WIFI_OUTPUT_DIR            //����ļ�Ŀ¼���ɶ��ơ���ע����Ŀ¼������rtl_drvĿ¼�µ�ouput����һ������ʹ��rtl_drvĿ¼�µ�ouput
#WIFI_DRV_DIFF_DIR          //��Ʒ�������һ���������첿�����ü�����Ŀ¼������LNA�������еļĴ���TXT����
#WLAN_SET_DRV_CURRENT       //��Ʒwifi ����������,�˺������޸�wifi���������Ĵ���0x74��ֵ
#�����еĺ궨��,���ݲ�ͬ��Ʒ���岻ͬ�ĺ�(�μ�rtl_drv/macro_readme.txt)���������˵�����£� 
#CFG_WIFI_EXTRA_NORMAL      //Ϊ�����汾��Ҫ����ĺ�
#CFG_WIFI_EXTRA_FACTORY     //Ϊ��Ƭ�汾��Ҫ����ĺ�
#CFG_WIFI_EXTRA_COMMON      //Ϊ��������Ƭ�汾����Ҫ����ĺ�

WIFI_HOME=$(cd "$(dirname "$0")"; pwd)

WIFI_MODULE_NAME=rtl8192es
export CONFIG_RTL_92E_SUPPORT=y
export CONFIG_PHY_EAT_40MHZ=y
WIFI_OUTPUT_DIR=output_balong_v7
WIFI_CHIP_DIR=wifi_rtl

#Ĭ�Ϻ궨��(wingle��Ʒ)
CFG_WIFI_EXTRA_NORMAL=""
CFG_WIFI_EXTRA_FACTORY="-DWLAN_PLATFORM_HUAWEI_FACTORY"
CFG_WIFI_EXTRA_COMMON="-DWLAN_PLATFORM_HUAWEI_COMMON -DSDIO_AP_PS  -DSOFTAP_PS_DURATION -DCFG_RTL_SDIO30 -DWLAN_PLATFORM_BALONG_V7 -DINTEL_BEACON_POWER_NO_INC"

#��Ʒ�궨��


if [ "${OBB_PRODUCT_NAME}" = "hi6921_v711_r218h" ] ;  then
    CFG_WIFI_EXTRA_NORMAL="${CFG_WIFI_EXTRA_NORMAL} -DSDIO_AP_PS -DSOFTAP_PS_DURATION"
    CFG_WIFI_EXTRA_COMMON="${CFG_WIFI_EXTRA_COMMON} "
fi

#��Ʒ���첿�ֵ�����Ŀ¼����(Ŀ¼���������ʾ�޲���, ������)
WIFI_DRV_DIFF_DIR=rtl_drv_diff/${OBB_PRODUCT_NAME}

#******************************************************************#
#***************               ��������                 ***********#
#******************************************************************#
cd ${WIFI_HOME}/../rtl_drv
if [ "${OBB_PRODUCT_NAME}" = "hi6921_v711_e5770s" ] ;  then
    WIFI_DRV_DIFF_DIR=rtl_drv_diff/${OBB_PRODUCT_NAME}/hi6921_v711_e5770s_923
    WIFI_OUTPUT_DIR=output_balong_v7_5770s
    . ./build_wifi_v7.sh
    
    cd ${WIFI_HOME}/../rtl_drv
    WIFI_DRV_DIFF_DIR=rtl_drv_diff/${OBB_PRODUCT_NAME}/hi6921_v711_e5770s_320
    WIFI_CHIP_DIR=wifi_rtl_320
 
fi

. ./build_wifi_v7.sh
