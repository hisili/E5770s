/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: nvchar.c                                                        */
/*                                                                           */
/* Author: yuyangyang                                                        */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2013-3-12                                                           */
/*                                                                           */
/* Description:   nv read&write user interface                               */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Modification: Create this file                                         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/



/*lint --e{533,830}*/
#include <linux/device.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/cdev.h>

#include "nv_comm.h"


#define NVCHAR_DEVICE_NAME    "nv"
#define NVCHAR_DEVICE_CLASS   "nv_class"
#define NVCHAR_MAX_ID         0xffff
#define IOCTRL_MAGIC           'c'


#define IOCTRL_NVFLUSH        _IOW(IOCTRL_MAGIC, 0, struct nv_data_stru)
#define IOCTRL_NVBACKUP       _IOW(IOCTRL_MAGIC, 1, struct nv_data_stru)
#define IOCTRL_NVREVERT       _IOR(IOCTRL_MAGIC, 2, struct nv_data_stru)
#define IOCTRL_NVSETDEFATULT  _IOW(IOCTRL_MAGIC, 2, struct nv_data_stru)

#define NV_MAX_USER_BUFF_LEN      1024  /* �޸�Ϊ��Ӧ��ƥ�������û�buff�ߴ� */

struct nv_dev
{
    unsigned int nvid;
    struct cdev cdev;
};


typedef enum
{ 
    TYPE_MAC_ADDR = 0,   /*  mac��ַ*/ 
    TYPE_NDIS_STATE,  /*ndis��״̬*/ 
    TYPE_SD_MODE,     /*SD MODE*/ 
    TYPE_APP_INFO,    /*��½��Ϣ*/
    
    TYPE_SSID1_INFO,   /*SSID1*/ 
    TYPE_WIFI_PASSWD1_WPA, /*WIFI PASSWORD*/ 
    TYPE_WIFI_PASSWD1_WEP, /*WIFI PASSWORD*/ 
    
    TYPE_SSID2_INFO,   /*SSID2*/ 
    TYPE_WIFI_PASSWD2_WPA, /*WIFI PASSWORD*/ 
    TYPE_WIFI_PASSWD2_WEP, /*WIFI PASSWORD*/
    
    TYPE_APPIN_INFO,  /*�� CPEʹ��,���ڼ�¼ WIFI WPS��PIN��*/ 
    TYPE_GPS_ONOFF, /*GPS�Ƿ�ʹ��*/
    
    TYPE_MULT_WIFI_BASIC, /*V7R2 WIFI SSID*/
    TYPE_MULT_WIFI_SEC,   /*V7R2 WIFI KEY*/
    TYPE_FACTORY_MODE,    /*����ģʽ*/      
    TYPE_CPE_TELNET_SWITCH_NVIM_STRU,    /*��NV�����ڿ���CPE��Ʒtelnet�����Ƿ��*/

    /*����Ϊ��ͨƽ̨nv��balong���漰*/
    TYPE_FOTA_PPP_APN,            /* ����PPP����ʱ��APN */
    TYPE_FOTA_PPP_USER_ID,        /* ����PPP����������û��� */
    TYPE_FOTA_PPP_PASSWORD,       /* ����PPP������������� */
    TYPE_FOTA_PPP_AUTH,           /* ����PPP����ʱ���õļ�Ȩ��ʽ */
    TYPE_FOTA_SERVER_IP,          /* FOTA��������IP */
    TYPE_FOTA_SERVER_PORT,        /* FOTA�������Ķ˿ں� */
    TYPE_FOTA_MODE,               /* FOTAģʽ���趨 */
    TYPE_FOTA_DETECT_COUNT,       /* ���ؼ�������ֵ*/
    TYPE_FOTA_NWTIME,             /* ���ڲ�ѯ�Ļ�׼ʱ�� */
    TYPE_FOTA_TIMER,              /* ��ʱ���Ĳ��� */
    TYPE_FOTA_INTERVAL,           /* �ֶ��汾��ѯ�ļ��ʱ�� */
    TYPE_FOTA_SMS_CONFIG,         /* fota��δʹ�ã�Ԥ��*/
    TYPE_FOTA_TIME_STAMP,         /* fota��δʹ�ã�Ԥ��*/
    TYPE_FOTA_RSA_PUB_MODE,       /* fota��δʹ�ã�Ԥ��*/
    TYPE_FOTA_RSA_PUB_EXP,        /* fota��δʹ�ã�Ԥ��*/
    TYPE_FOTA_SMS_FLAG,  /* �ȱ�ʶ����FOTA ��־λ��Ҳ�����յ�FOTA ���ź���������� */
    /*����Ϊ��ͨƽ̨nv��balong���漰*/

    TYPE_NV_FACTORY_INFO_I,         /*32 ���ڼ�¼���߹�λ�ļ����*/
    TYPE_NV_HUAWEI_BT_INFO_I,       /*33 �����豸��MAC��������Ϣ*/
    TYPE_DATA_LOCK_HASH_VAL,        /*34 �ն˳���˽������hashֵ32�ֽ�*/
    TYPE_WIFI_MAC_NUM,              /*35 wifi mac��ַ������TYPE_MAC_ADDRΪ ��mac��ַ��4�ֽ���������*/
    TYPE_LAN_MAC,                   /*36 LAN mac��ַ��ascci�ַ���ʽ�洢*/
    TYPE_LAN_MAC_NUM,               /*37 LAN mac��ַ������4�ֽ���������*/
    TYPE_TTS_CFG,                   /*38 TTS����*/

    TYPE_BT_MAC_NUM  = 51,          /*51 Bluetooth mac��ַ������4�ֽ���������*/
    TYPE_USB_MAC_NUM = 52,          /*52 USB mac��ַ������4�ֽ���������*/

    TYPE_NV_VSIM_UE_MODE = 54,      /*54 �жϿ�ģʽ��VSIMģʽ����Ӳ��ģʽ*/
    TYPE_SMS_CTRL_WIFI_INFO = 67,   /*67 MS2172s-818 ���ƹ��� SMS CTRL WIFI*/
    TYPE_NV_MAX, 
}TYPE_KERNEL_NV_INFO; 
/*lint -e64 -e156 */

/**
* �˱��е�NV ID��TYPE_KERNEL_NV_INFO�е�ö��һһ��Ӧ��
* �������ô˴�����Ҫͨ�����������ӻ����޸�
*/
unsigned long nv_index_table[TYPE_NV_MAX + 1] = \ 
{
    {NV_ID_MSP_MAC_ADDR},                        /* TYPE_MAC_ADDR   50014 */ 
    {NV_ID_DRV_USB_DYNAMIC_PID_TYPE_PARAM},      /* TYPE_NDIS_STATE   50091 */ 
    {NV_ID_DRV_WEBNAS_SD_WORK_MODE},             /* TYPE_SD_MODE   51 */ 
    {NULL},                                      /* TYPE_APP_INFO   50418 */ 
    {NULL},                                      /* TYPE_SSID1_INFO   50290*/   /*50290-50295Ϊ��ͨ��NV��balong�ϲ�ʹ��*/         
    {NULL},                                      /* TYPE_WIFI_PASSWD1_WPA   50291 */ 
    {NULL},                                      /* TYPE_WIFI_PASSWD1_WEP   50292 */ 
    {NULL},                                      /* TYPE_SSID2_INFO   50293 */ 
    {NULL},                                      /* TYPE_WIFI_PASSWD2_WPA   50294 */ 
    {NULL},                                      /* TYPE_WIFI_PASSWD2_WEP   50295 */ 
    {NV_ID_DRV_WPS_PIN},                         /* TYPE_APPIN_INFO   balongΪ0xCB8D*/ 
    {NULL},                                      /* TYPE_GPS_ONOFF   50280 */ 
    {NV_ID_DRV_MULTI_WIFI_STATUS_SSID},          /* TYPE_MULT_WIFI_BASIC   9111 */
    {NV_ID_DRV_MULTI_WIFI_KEY},                  /* TYPE_MULT_WIFI_SEC   9110 */
    {NV_ID_DRV_VER_FLAG},                        /* TYPE_FACTORY_MODE   36 */
    {NV_ID_TELNET_SWITCH_I},                     /* TYPE_CPE_TELNET_SWITCH_NVIM_STRU   50501 */
    /*����Ϊ��ͨƽ̨nv��balong���漰*/
    {NULL},                                      /*TYPE_FOTA_PPP_APN*/ 
    {NULL},                                      /*TYPE_FOTA_PPP_USER_ID*/ 
    {NULL},                                      /*TYPE_FOTA_PPP_PASSWORD*/ 
    {NULL},                                      /*TYPE_FOTA_PPP_AUTH*/ 
    {NULL},                                      /*TYPE_FOTA_SERVER_IP*/ 
    {NULL},                                      /*TYPE_FOTA_SERVER_PORT*/ 
    {NULL},                                      /*TYPE_FOTA_MODE*/ 
    {NULL},                                      /*TYPE_FOTA_DETECT_COUNT*/ 
    {NULL},                                      /*TYPE_FOTA_NWTIME*/ 
    {NULL},                                      /*TYPE_FOTA_TIMER*/ 
    {NULL},                                      /*TYPE_FOTA_INTERVAL*/ 
    {NULL},                                      /*TYPE_FOTA_SMS_CONFIG*/ 
    {NULL},                                      /*TYPE_FOTA_TIME_STAMP*/ 
    {NULL},                                      /*TYPE_FOTA_RSA_PUB_MODE*/ 
    {NULL},                                      /*TYPE_FOTA_RSA_PUB_EXP*/ 
    {NULL},                                      /*TYPE_FOTA_SMS_FLAG*/ 
    /*����Ϊ��ͨƽ̨nv��balong���漰*/

    {NV_ID_DRV_NV_FACTORY_INFO_I},               /* TYPE_NV_FACTORY_INFO_I   114 */
    {NV_ID_MSP_MAC_ADDR},                        /* TYPE_NV_HUAWEI_BT_INFO_I   50014*/
    {NV_ID_DATA_LOCK_I},                         /* TYPE_DATA_LOCK_HASH_VAL*/
    {NV_ID_DRV_MAC_NUM},                         /* TYPE_WIFI_MAC_NUM  50517*/
    {NV_ID_MSP_MAC_ADDR},                        /* TYPE_LAN_MAC       50014*/
    {NV_ID_DRV_MAC_NUM},                         /* TYPE_LAN_MAC_NUM   50517*/
    {NULL/*nv�������*/},                        /* TYPE_TTS_CFG*/
    {NULL},                                      /* 39 Ԥ�� */
    {NULL},                                      /* 40 Ԥ�� */
    {NULL},                                      /* 41 Ԥ�� */
    {NULL},                                      /* 42 Ԥ�� */
    {NULL},                                      /* 43 Ԥ�� */
    {NULL},                                      /* 44 Ԥ�� */
    {NULL},                                      /* 45 Ԥ�� */
    {NULL},                                      /* 46 Ԥ�� */
    {NULL},                                      /* 47 Ԥ�� */
    {NULL},                                      /* 48 FOTA�ݽ��汾������ */     
    {NULL},                                      /* 49 USB log���ƹ�����ӦNV 50498 */
    {NULL},                                      /* 50 webui������� */
    {NV_ID_DRV_MAC_NUM},                         /* 51 TYPE_BT_MAC_NUM   50517 */
    {NV_ID_DRV_MAC_NUM},                         /* 52 TYPE_USB_MAC_NUM  50517 */
    {NULL},                                      /* 53 ��ƽ̨С����*/
    {NV_Item_VSIM_Ue_Mode},           /* 54 TYPE_NV_VSIM_UE_MODE  50549*/
    {NULL},                                      /*55*/
    {NULL},                                     /*56*/
    {NULL},                                     /*57*/
    {NULL},                                     /*58*/
    {NULL},                                     /*59*/
    {NULL},                                     /*60*/
    {NULL},                                     /*61*/
    {NULL},                                     /*62*/
    {NULL},                                     /*63*/
    {NULL},                                     /*64*/
    {NULL},                                     /*65*/
    {NULL},                                     /*66*/
    {NULL},                                      /* TYPE_NV_MAX */
}; 
/*lint +e64 +e156 */

typedef struct
{
    unsigned char lanmac_num;        /* LAN_MAC/Cradle MAC����*/
    unsigned char wifimac_num;       /* WIFI_MAC ����*/
    unsigned char btmac_num;        /* BLUETOOTH_MAC����*/
    unsigned char usbmac_num;       /* USB_MAC����*/
    unsigned char reserve[4];          /*Ԥ���ֶ�*/
}NV_MAC_NUM_STRU;


/* �޸�Ϊ��Ӧ��ƥ��Ľṹ�� */
struct nv_data_stru
{
    TYPE_KERNEL_NV_INFO type;
    unsigned int        len;
    unsigned int        rst;
    unsigned char       data[NV_MAX_USER_BUFF_LEN];
};

#define NV_HEAD_LEN            (sizeof(struct nv_data_stru) - NV_MAX_USER_BUFF_LEN)

static struct nv_dev nv_cdev = {0};
static unsigned int nvchar_major;
static struct class* nv_class;
/*lint -save -e438*/
/*lint -save -e745 -e601 -e49 -e65 -e64 -e533 -e830*/
ssize_t nvdev_open(struct inode * inode, struct file * file);
ssize_t nvdev_release(struct inode * inode, struct file * file);
ssize_t nvdev_read(struct file *file, char __user *buf, size_t count,
			loff_t *ppos);
ssize_t nvdev_write(struct file *file, const char __user *buf, size_t count,
			loff_t *ppos);

static struct file_operations nv_fops = {
    .owner   = THIS_MODULE,
    .read    = nvdev_read,
    .write   = nvdev_write,
    .open    = nvdev_open,
    .release = nvdev_release,
};

ssize_t nvdev_open(struct inode *inode, struct file *file)/*lint !e830*/
{
    struct nv_dev* dev;

    dev = (struct nv_dev*)container_of(inode->i_cdev,struct nv_dev,cdev);
    file->private_data = dev;
    return 0;
}
ssize_t nvdev_release(struct inode *inode, struct file *file)
{
    inode = inode;
    file  = file;
    return 0;
}

#define MAC_STR_LEN    (17)    /*XX:XX:XX:XX:XX:XXʵ�ʳ�����12+5*/
#define MAC_HALF_NUM   (3 )  
#define MAC_ARRAY_LEN  (32) 
#define BITS_OF_BYTE   (8 )
#define BYTE_OF_NUM    (3 )    /*XX:�ĳ���*/
/************************************************************************
func: ��MAC(mac_input)��offset�󷵻ظ�mac_intput , mac��ʽ: XX:XX:XX:XX:XX:XX
input: mac_input: ��MAC   nv_len: �ϲ㴫������Ҫ��ȡNV�ĳ���
output: None
return: None
Example: 
AA:BB:CC:00:00:00 AA:BB:CC:00:00:01 AA:BB:CC:00:00:02 AA:BB:CC:00:00:03
AA:BB:CC:FF:FF:FE AA:BB:CC:FF:FF:FF AA:BB:CC:00:00:00 AA:BB:CC:00:00:01
AA:BB:CC:FF:FE:FE AA:BB:CC:FF:FE:FF AA:BB:CC:FF:FF:00 AA:BB:CC:FF:FF:01
************************************************************************/
/*lint -save -e160 -e506 -e522 -e527 */
void BaseMACToWLAN( char* mac_input, int offset, unsigned long nv_len )
{
    unsigned long temp = 0;
    char array_mac[MAC_ARRAY_LEN] = {0};
    int  cnt = 0;
    unsigned long low_mac = 0;
    char array_temp[4] = {0};

    if ( MAC_STR_LEN >= nv_len )
    {
        printk( KERN_ERR "%s, nv_len not enough: %u", __func__, nv_len );
    }

    strncpy( array_mac, mac_input, MAC_STR_LEN ); 
   
    for ( cnt = 0; cnt < MAC_HALF_NUM; cnt++ )
    {
        sscanf( ( char * )( array_mac + ( cnt + MAC_HALF_NUM ) * BYTE_OF_NUM ), "%X", &temp ); 
        
        low_mac |= (unsigned long)( temp << ( ( MAC_HALF_NUM - cnt - 1 ) * BITS_OF_BYTE ) ); 
    }

    low_mac += offset;

    for ( cnt = 0; cnt < MAC_HALF_NUM; cnt++ )
    {
        temp = (unsigned char)( low_mac >> ( ( MAC_HALF_NUM - cnt - 1 ) * BITS_OF_BYTE ) );
        memset( array_temp, 0, sizeof(array_temp) );
        sprintf( array_temp, "%02X", (unsigned char)temp );
        memcpy( ( array_mac + ( cnt + MAC_HALF_NUM ) * BYTE_OF_NUM ), array_temp, 2 ); 
    }

    /*����ĩβ'\0'*/
    array_mac[MAC_STR_LEN] = 0;

    memcpy( mac_input, array_mac, MAC_STR_LEN + 1 );
}
/*lint -restore*/


/*****************************************************************************
 �� �� ��  : get_mac_offset
 ��������  : ��ȡ�豸��һ��mac��ַ����ڻ�mac��ַ��ƫ����
 �������  : type:�豸���ͣ�wifi��blooth��lan�ȣ�
             data:��ȡ��nv 50517���ֵ
 �������  : ��
 �� �� ֵ  : ƫ����
 ˵    ��  : ƫ�����ļ�������: nv 50014����һ����mac��ַBASE_MAC��nv50517����ÿ���豸
             mac�ĸ�����Ȼ�����¼���:
             LAN_MAC :[BASE_MAC,BASE_MAC+ lanmac_num)
             WIFI_MAC:[BASE_MAC+ lanmac_num,BASE_MAC+ lanmac_num+ wifimac_num)
             BLUETOOTH_MAC:
                      [BASE_MAC+lanmac_num+wifimac_num,
                       BASE_MAC+lanmac_num+wifimac_num+ btmac_num)
             USB_MAC:
                      [BASE_MAC+lanmac_num+wifimac_num+ btmac_num,
                       BASE_MAC+lanmac_num+wifimac_num+ btmac_num+ usbmac_num)  
             
*****************************************************************************/
int get_mac_offset(TYPE_KERNEL_NV_INFO type,void * data)
{
    int offset = 0;
    NV_MAC_NUM_STRU * mac_temp = data;
    switch(type)
    {
        case TYPE_LAN_MAC:
            offset = 0;
            break;
        case TYPE_MAC_ADDR:
            offset = mac_temp->lanmac_num;
            break;
        case TYPE_NV_HUAWEI_BT_INFO_I:
            offset = mac_temp->wifimac_num + mac_temp->lanmac_num;
            break;       
        default:
            break;
    }
    return offset;

}

/*****************************************************************************
 �� �� ��  : get_mac_num
 ��������  : ��ȡ�����豸mac ��ַ�ĸ���
 �������  : type:�豸���ͣ�wifi��blooth��lan�ȣ�
             data:��ȡ��nv 50517���ֵ
 �������  : ��
 �� �� ֵ  : mac��ַ����
 *****************************************************************************/
int get_mac_num(TYPE_KERNEL_NV_INFO type,void * data)
{
    int num = 0;
    NV_MAC_NUM_STRU * mac_temp = data;
    switch(type)
    {
        case TYPE_WIFI_MAC_NUM:
            num = mac_temp->wifimac_num;
            break;
        case TYPE_LAN_MAC_NUM:
            num = mac_temp->lanmac_num;
            break;
        case TYPE_BT_MAC_NUM:
            num = mac_temp->btmac_num;
            break;
        case TYPE_USB_MAC_NUM:
            num = mac_temp->usbmac_num;
            break;
        default:
            break;
    }
    return num;
}

/*lint -restore +e745 +e601 +e49 +e65 +e64 +e533 +e830*/
/*
data stru:
    ---------------------------------------------
    | NV ID | data length |     data      |
    ---------------------------------------------
*/

/*lint -save --e{529,527}*/
ssize_t nvdev_read(struct file *file,char __user *buf, size_t count,
			loff_t *ppos)
{
    ssize_t ret;
    struct nv_data_stru* kbuf = NULL;
    unsigned long   k_nvid = 0;
    unsigned long   k_nvlen = 0;
    unsigned long   mac_num = 0;
    unsigned char   mac_offset = 0; 
    NV_MAC_NUM_STRU nv_mac_num ={0};

    if((NULL == buf)||(count <= NV_HEAD_LEN)||(count > NV_MAX_USER_BUFF_LEN))/*lint !e737*/
    {
        return BSP_ERR_NV_INVALID_PARAM;
    }

    kbuf = (struct nv_data_stru*)kmalloc(count+1,GFP_KERNEL);
    if(NULL == kbuf)
    {
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    if(copy_from_user(kbuf,buf,count))
    {
        kfree(kbuf);
        return -1;
    }
    /*BEGIN EUAP ��һ��*/

    if ( TYPE_NV_MAX <= kbuf->type )
    {
        printk( KERN_ERR "kbuf->type is err: %u", kbuf->type );
        kfree(kbuf);
        return -1;
    }
   
    k_nvid = nv_index_table[kbuf->type];
    
    if(TYPE_WIFI_MAC_NUM == kbuf->type || TYPE_LAN_MAC_NUM == kbuf->type
       || TYPE_BT_MAC_NUM == kbuf->type || TYPE_USB_MAC_NUM == kbuf->type)
    {
        k_nvlen = sizeof(NV_MAC_NUM_STRU);
    }
    else
    {
        k_nvlen = count-(sizeof(TYPE_KERNEL_NV_INFO) + sizeof(unsigned int) + sizeof(unsigned int));
    }
    
    /*����NV��֧��ֱ�ӷ���*/
    if((0 == k_nvlen) || ((unsigned long )NULL == k_nvid))
    {
        printk(KERN_ERR "The request nv is not support here or para is err, kbuf->type = %d,count = %d\n", \
                         kbuf->type,count);
        kfree(kbuf);
        return -1;
    }

    /*����Ƕ�ȡmac��ַ���Ȼ�ȡmacƫ����*/
    if(TYPE_MAC_ADDR == kbuf->type || TYPE_NV_HUAWEI_BT_INFO_I == kbuf->type || TYPE_LAN_MAC == kbuf->type)
    {
        ret = (ssize_t)bsp_nvm_read(NV_ID_DRV_MAC_NUM,(u8*)&nv_mac_num,sizeof(NV_MAC_NUM_STRU));
        if(ret)
        {
            printk( KERN_ERR "[%s]nv read err!\n",__func__);
            kfree(kbuf);
            return ret;
        }      
        mac_offset = get_mac_offset(kbuf->type,&nv_mac_num);       
    }
    /* coverity[tainted_data] */
    ret = (ssize_t)bsp_nvm_read(k_nvid,kbuf->data,k_nvlen);
    kbuf->len = k_nvlen;
    if(ret)
    {
        kfree(kbuf);
        return ret;
    }

    kbuf->rst = NV_OK;


    if ( TYPE_MAC_ADDR == kbuf->type || TYPE_NV_HUAWEI_BT_INFO_I == kbuf->type || TYPE_LAN_MAC == kbuf->type )
    {
        BaseMACToWLAN( (char *)kbuf->data, mac_offset, k_nvlen );
    }

    else if(TYPE_WIFI_MAC_NUM == kbuf->type || TYPE_LAN_MAC_NUM == kbuf->type 
        || TYPE_BT_MAC_NUM == kbuf->type || TYPE_USB_MAC_NUM == kbuf->type)
    {
        mac_num = get_mac_num(kbuf->type,kbuf->data);
        memset(kbuf->data,0x0,(count + 1) - (sizeof(TYPE_KERNEL_NV_INFO) + sizeof(unsigned int) + sizeof(unsigned int)));
        kbuf->data[0] = mac_num;
        kbuf->len = 1;
        printk("[%s]kbuf->type=%d,mac_num=%d\n",__func__,kbuf->type,kbuf->data[0]);
    }
    
    ret = (ssize_t)copy_to_user(buf,kbuf,count);
    if(ret)
    {
        kfree(kbuf);
        return ret;
    }

    kfree(kbuf);
    return (ssize_t)count;
}
/*lint -restore*/

/*lint -save --e{529,527}*/
ssize_t nvdev_write(struct file *file,const char __user *buf, size_t count,
			loff_t *ppos)
{
    ssize_t ret;
    struct nv_data_stru* kbuf = NULL;
    unsigned long k_nvid = 0;
    unsigned long k_nvlen = 0;

    if((NULL == buf)||(count <= NV_HEAD_LEN)||(count > NV_MAX_USER_BUFF_LEN))/*lint !e737*/
    {
        printk("invalid parameter!\n");
        return BSP_ERR_NV_INVALID_PARAM;
    }

    kbuf = (struct nv_data_stru*)kmalloc(count+1,GFP_KERNEL);
    if(NULL == kbuf)
    {
        return BSP_ERR_NV_MALLOC_FAIL;
    }

    if(copy_from_user(kbuf,buf,count))
    {
        printk("copy from user fail!\n");
        kfree(kbuf);
        return -1;
    }
    /*BEGIN EUAP ��һ��*/

    if ( TYPE_NV_MAX <= kbuf->type )
    {
        printk( KERN_ERR "kbuf->nvid is err: %u", kbuf->type );
        kfree(kbuf);
        return -1;
    }
    
    k_nvid = nv_index_table[kbuf->type];
    k_nvlen = count-(sizeof(TYPE_KERNEL_NV_INFO) + sizeof(unsigned int) + sizeof(unsigned int));

    /*����NV��֧��ֱ�ӷ���*/
    if((0 == k_nvlen) ||((unsigned long )NULL == k_nvid))
    {
        printk(KERN_ERR "The request nv is not support here or para is err, kbuf->type = %d,count = %d\n", \
                         kbuf->type,count);
        kfree(kbuf);
        return -1;
    }

    /* coverity[tainted_data] */
    ret = (ssize_t)bsp_nvm_write(k_nvid,kbuf->data,k_nvlen);
    if(ret)
    {
        kfree(kbuf);
        return ret;
    }

    kfree(kbuf);
    return (ssize_t)count;
}
/*lint -restore*/
/*lint -save -e527 -e533*/
void nvchar_dev_setup_cdev(struct nv_dev* dev,struct file_operations* fops)
/*lint -restore*/
{
    int ret;
    unsigned int devno = MKDEV(nvchar_major,0);


    cdev_init(&dev->cdev,fops);
    dev->cdev.owner= THIS_MODULE;
    dev->cdev.ops = fops;

    ret = cdev_add(&dev->cdev,devno,1);
    if(ret)
    {
        printk("add nv fail!\n");
        return ;
    }

    nv_class = class_create(THIS_MODULE,NVCHAR_DEVICE_CLASS);
    if(IS_ERR(nv_class))
    {

        printk("class create failed!\n");
        return ;
    }

    device_create(nv_class, NULL, devno, NULL, NVCHAR_DEVICE_NAME);
}



/*nv device init*/
/*lint -save --e{529}*/
int nvchar_init(void)
{
    int ret;
    dev_t dev = 0;

    /*dynamic dev num use*/
    ret = alloc_chrdev_region(&dev,0,1,NVCHAR_DEVICE_NAME);
    nvchar_major = MAJOR(dev);

    if(ret)
    {
        printk("nvchar failed alloc :%d\n",nvchar_major);
        return ret;
    }
    /*setup dev*/
    nvchar_dev_setup_cdev(&nv_cdev,&nv_fops);

    printk("nvchar init end! major: 0x%x\n",nvchar_major);
    return NV_OK;
}
/*lint -restore*/




MODULE_AUTHOR("Hisilicon Drive Group");
MODULE_DESCRIPTION("Balong NV driver for Hisilicon");
MODULE_LICENSE("GPL");

/*lint -restore*/

