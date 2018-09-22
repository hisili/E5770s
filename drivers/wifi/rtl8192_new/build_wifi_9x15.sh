#!/bin/sh

#******************************************************************#
#***************               ����ʵ��                 ***********#
#******************************************************************#
#WIFI_HOME                  //�������Ŀ¼����������ļ�(outputĿ¼)�����������м��ļ�(OUT_WIFIĿ¼)�ȣ�Ĭ������Ϊ��ǰĿ¼
#WIFI_OUTPUT_DIR            //����ļ�Ŀ¼���ɶ��ơ���ע����Ŀ¼������rtl_drvĿ¼�µ�ouput����һ������ʹ��rtl_drvĿ¼�µ�ouput
#WIFI_DRV_DIFF_DIR          //��Ʒ�������һ���������첿�����ü�����Ŀ¼������LNA�������еļĴ���TXT����
#�����еĺ궨��,���ݲ�ͬ��Ʒ���岻ͬ�ĺ�(�μ�rtl_drv/macro_readme.txt)���������˵�����£� 
#CFG_WIFI_EXTRA_NORMAL      //Ϊ�����汾��Ҫ����ĺ�
#CFG_WIFI_EXTRA_FACTORY     //Ϊ��Ƭ�汾��Ҫ����ĺ�
#CFG_WIFI_EXTRA_COMMON      //Ϊ��������Ƭ�汾����Ҫ����ĺ�

WIFI_HOME=$(cd "$(dirname "$0")"; pwd)

WIFI_MODULE_NAME=rtl8192es
export CONFIG_RTL_92E_SUPPORT=y
export CONFIG_PHY_EAT_40MHZ=y
WIFI_OUTPUT_DIR=output_qualcomm_9x15

#Ĭ�Ϻ궨��
CFG_WIFI_EXTRA_NORMAL=""
CFG_WIFI_EXTRA_FACTORY="-DWLAN_PLATFORM_HUAWEI_FACTORY"
CFG_WIFI_EXTRA_COMMON="-DWLAN_PLATFORM_HUAWEI_COMMON -DWLAN_PLATFORM_QUALCOMM_9x15"

#��Ʒ�궨��
if [ -z "${CONFIG_FEATURE_PRODUCT_TYPE}" ];  then
    CONFIG_FEATURE_PRODUCT_TYPE="e5"
else
    CONFIG_FEATURE_PRODUCT_TYPE=`echo "${CONFIG_FEATURE_PRODUCT_TYPE}" | tr A-Z a-z`
fi
echo "[Wi-Fi]: wifi CONFIG_FEATURE_PRODUCT_TYPE = ${CONFIG_FEATURE_PRODUCT_TYPE}"

if [ "${CONFIG_FEATURE_PRODUCT_TYPE}" = "e5" ];  then
    CFG_WIFI_EXTRA_NORMAL="${CFG_WIFI_EXTRA_NORMAL} -DSDIO_AP_PS"
else
    CFG_WIFI_EXTRA_NORMAL="${CFG_WIFI_EXTRA_NORMAL} -DCONFIG_AUTOCH_TIMER"
fi

#******************************************************************#
#***************               ��������                 ***********#
#******************************************************************#
cd ${WIFI_HOME}/../rtl_drv
. ./build_wifi_9x15.sh