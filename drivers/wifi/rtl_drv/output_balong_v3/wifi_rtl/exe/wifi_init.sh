#!/system/bin/busybox sh

WIFI_PATH=/system/bin/wifi_rtl
export PATH=$PATH:${WIFI_PATH}/exe

if [ ! -e ${WIFI_PATH}/exe/wifi_flags.sh ];then
	echo "[wi-fi]: Error, not exist flags ${WIFI_PATH}/exe/wifi_flags.sh"
	exit 255
fi
. ${WIFI_PATH}/exe/wifi_flags.sh
echo "[wi-fi]: CONFIG_WLAN_MODULE_NAME = ${CONFIG_WLAN_MODULE_NAME}"
echo "[wi-fi]: CONFIG_WLAN_FEATURE_FACTORY = ${CONFIG_WLAN_FEATURE_FACTORY}"
if [ -z "${CONFIG_WLAN_MODULE_NAME}" ];then
	echo "[wi-fi]: Error, CONFIG_WLAN_MODULE_NAME is NULL"
	exit 255
fi

echo "[wi-fi]: Enter CHECK MMC (${CONFIG_WLAN_MODULE_NAME})"
num=0
while [ "$num" -lt 5 ]; do
    num=$(($num+1))
    echo "[wi-fi]: -------$num check mmc"
    if [ "$(ls /sys/devices/platform/balong_sdio.1/mmc_host | echo $?)" = "0" ]; then
        echo "[wi-fi]: ------- check mmc successful"
        break
    fi
    usleep 20000
done
echo "[wi-fi]: mmc device:$(ls /sys/devices/platform/balong_sdio.1/mmc_host)"

if [ "${CONFIG_WLAN_FEATURE_FACTORY}" = "yes" ]; then
    WIFI_KO_NAME=${CONFIG_WLAN_MODULE_NAME}_mfg.ko
else
    WIFI_KO_NAME=${CONFIG_WLAN_MODULE_NAME}.ko
fi

/system/bin/rmmod ${CONFIG_WLAN_MODULE_NAME}

echo "------------ Load ko file ${WIFI_KO_NAME} ---------------"
insmod ${WIFI_PATH}/driver/${WIFI_KO_NAME}
WIFI_RESULT=$?

#factory mode need config
if [ "${CONFIG_WLAN_FEATURE_FACTORY}" = "yes" ]; then
    num=0
    while [ "$num" -le 4 ]; do
        num=$(($num+1))
        echo "------------ $num check wlan0"
        if [ "$(ifconfig wlan0 | grep wlan0)" != "" ]; then
            echo "------------ check wlan0 successful"
            break
        fi
        usleep 100
    done
    #fatcory command list
    ifconfig wlan0 down
    iwpriv wlan0 set_mib mp_specific=1
    #add channel config, avoid auto channel select (ACS)
    iwpriv wlan0 set_mib channel=1
    ifconfig wlan0 up
    iwpriv wlan0 mp_start
fi
echo "[wi-fi]: Exit Load ko ret = ${WIFI_RESULT}"

exit 0
