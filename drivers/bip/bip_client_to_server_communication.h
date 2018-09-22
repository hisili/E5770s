

#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/semaphore.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/kthread.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/device.h>
#include <linux/workqueue.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <asm/uaccess.h>
#include <linux/netlink.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/mutex.h>
#include <linux/netlink.h>

#include "drv_bip.h"

/*BIP Buffer ��󳤶�*/
#define BIP_MAX_BUFFER_LENGTH               1500

/*BIP APN ��С����*/
#define BIP_MIN_NETWORK_ACCESS_NAME_LENGTH  1

/*BIP APN ��󳤶�*/
#define BIP_MAX_NETWORK_ACCESS_NAME_LENGTH  99

/*BIP IP��ַ ��󳤶�*/
#define BIP_MAX_IPADDRESS_LENGTH            16

/*BIP �����û��� ��󳤶�*/
#define BIP_MAX_DIAL_USERNAME_LEN           255

/*BIP �������� ��󳤶�*/
#define BIP_MAX_DIAL_PASSWORD_LEN           255

/*BIP Э�鶨�� Channel Data��󳤶�*/
#define BIP_MAX_CHANNEL_DATA_LENGTH         255

/*����BIP Client��BIP�豸 ֮�� ͨ�ŵ��豸ID*/
#define DEVICE_ID_BIP                       17

typedef unsigned char       SI_UINT8;
typedef unsigned long       SI_UINT32;
typedef signed long         SI_INT32;
typedef unsigned short      SI_UINT16;

typedef void BSP_VOID;
typedef void SI_VOID;


typedef enum
{
    BIP_NTO_CREATE_SOCKET =  1,
    BIP_TO_CREATE_SOCKET =  2,
    BIP_HAVE_CREATED_SOCKET = 3,
    BIP_CREATE_SOCKET_STATE_BUTT
} BIP_SOCKET_STATE_EN;


/*BIP Client�� BIP�豸ͨ�� ��Ϣö��*/   
typedef enum
{ 
    UICC_INFORM = -1,/*֪ͨBIP Client ȡ����*/
    OTA_TO_UICC = 0, /*BIP Client д�� BIP�ַ��豸 ����*/
    UICC_TO_OTA = 1, /*BIP Client ��ȡ BIP�ַ��豸 ����*/
    UICC_COMPLETE = 0xff /*BIPҵ�����*/
}BIP_EVENT;


#define BIP_SOCKET_CREATE_NOK   0
#define BIP_SOCKET_CREATE_OK     1

/*PACKET DATA Structure to find BIP Data */ 
typedef struct
{  
    BSP_U32               BipServerAddr;
    BSP_U16               BipServerPort;
    BSP_U16               BipClientPort;
    BSP_U8                BipSocketStatus;
}BIP_PACKET_HEADER;
/**************************************************************************
  ��������
**************************************************************************/


static int BipDeviceOpen(struct inode *inode, struct file *file);


static int BipDeviceRelease(struct inode *inode, struct file *file);


static long BipDeviceIoctl(struct file *file, unsigned int  cmd, unsigned long);



BSP_S32 BipDeviceInit(void);


void __init BipClientRegisterFuncInit(void);


BSP_S32 BipDeviceReceiveDataFromBipClient( BIP_Command_Event_STRU *pDst);


BSP_S32 BipDeviceSendDataToModem( BIP_Command_Event_STRU *stru);


BSP_S32 BipDeviceReceiveDataFromModem(SI_VOID *pMsgBody, BSP_U32 u32Len);


BSP_S32 BipDeviceNotifyDataToBipClient( BIP_Command_Event_STRU *pDst, BIP_EVENT event_code);


void BipDeviceShowInfo (BIP_Command_Event_STRU *Data);

#if (FEATURE_ON == MBB_FEATURE_BIP_TEST)


void BipClientTestOpenChannel(BSP_U8 ResultValue);


void BipClientTestCloseChannel(void);


void BipClientTestSendData(BSP_U8 dataLen);


void BipClientTestReceiveData( BSP_U8 dataLen, BSP_U8 LeftDataLen );


void BipClientTestGetChannelStatus(BSP_U8 ChannelStatus);


void BipClientTestGetChannelStatusFail(void);


void BipClientTestChannelStatusEvent(BSP_U8 ChannelStatus);
#endif /*(FEATURE_ON == MBB_FEATURE_BIP_TEST)*/


