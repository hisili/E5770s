/******************************************************************************

  Copyright (C), 2001-2013, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : kerneldev.c
  Version       : Initial Draft
  Created       :
  Description   : kerneldev Init
  Function List :

  History        :
  1.Date         : 2013/11/26
    Author       : ����00249966
    Modification : Created function

******************************************************************************/


#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <asm/uaccess.h>

#include "drv_comm.h"
#include "led_comm.h"
#include <bsp_softtimer.h>
#include "drv_leds.h"

#ifdef __cplusplus
extern "C" {
#endif


/****************************************************************************
 �ⲿ����ԭ��˵��

*****************************************************************************/
#if ((FEATURE_ON == MBB_DLOAD_STICK) || (FEATURE_ON == MBB_DLOAD_HILINK))

extern int led_threecolor_switch(unsigned int new_state);
#endif

/****************************************************************************
 �ڲ�����ԭ��˵��

*****************************************************************************/
static ssize_t dev_open(struct inode *inode, struct file *file);
static ssize_t dev_release(struct inode *inode, struct file *file);
int kernelDeviceIoctl(struct file *file, unsigned int cmd, unsigned long arg);

/****************************************************************************
 �ⲿ����ԭ��˵��

*****************************************************************************/



/****************************************************************************
 ȫ�ֱ�������

*****************************************************************************/
/*ָʾ�Ʋ����������ݽṹ*/
static const struct file_operations balong_led_fops = {
    .owner = THIS_MODULE,
//    .open  = dev_open,
//    .release = dev_release,
    .unlocked_ioctl = kernelDeviceIoctl,
};


/*balong_led_miscdev��Ϊ����misc_register�����Ĳ�����
������linux�ں�ע��ָʾ��misc�豸��
*/
static struct miscdevice balong_led_miscdev = {
    .name = "led",
    .minor = MISC_DYNAMIC_MINOR,/*��̬�������豸�ţ�minor��*/
    .fops = &balong_led_fops,
};


/****************************************************************************
 ��������

*****************************************************************************/
static ssize_t dev_open(struct inode *inode, struct file *file)
{
    printk("[LED] %s\n", __func__);
    return 0;
}

static ssize_t dev_release(struct inode *inode, struct file *file)
{
    printk("[LED] %s\n", __func__);
    return 0;
}


static BSP_S32 kernelDeviceRelease(struct inode *inode, struct file *file)
{
    int ret = BSP_ERROR;
    
    if (NULL != inode && NULL != file)
    {
        ;
    }
    
    ret = misc_deregister(&balong_led_miscdev);
    
    if (0 > ret)
    {
        printk(KERN_ERR "[LED] kernelDeviceRelease: misc_deregister FAIL!\n");
    }
    
    return ret;
}


int kernelDeviceIoctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    int ret = BSP_ERROR;
    LED_IOCTL_ARG stCtrlParms = {0};

    printk(KERN_ERR"[LED] %s:  cmd = %d, arg = 0x%x\n", __func__, cmd, arg);

    /*����ж�*/
    if (NULL != file)
    {
        ;
    }

    /* ����������Ч�� */
    if (_IOC_TYPE(cmd) != MEM_IOC_MAGIC) 
    {
        printk(KERN_ERR"[LED] kernelDeviceIoctl:CMD ERROR,file is NULL! \n");
        return -EINVAL;
    }

    if (_IOC_NR(cmd) >= MEMDEV_IOC_MAXNR) 
    {
        printk(KERN_ERR"[LED] kernelDeviceIoctl:CMD ERROR,file is NULL! \n");
        return -EINVAL;
    }

    if(NULL == arg)
    {
        printk(KERN_ERR"[LED] kernelDeviceIoctl: ARG ERROR,file is NULL! \n");
        return BSP_ERROR;
    } 

    /*�ں˵���*/
    if(NULL == file)
    {
        memcpy(&stCtrlParms, (void *)arg, sizeof(stCtrlParms));
    }
    else
    {
        /*Ӧ�õ���*/
        if (BSP_OK != copy_from_user((LED_IOCTL_ARG *)&stCtrlParms,(LED_IOCTL_ARG *)arg,sizeof(LED_IOCTL_ARG)))
        {
            printk(KERN_ERR"[LED] kernelDeviceIoctl: copy_from_user FAIL!\n");
            return BSP_ERROR;
        }
    }

    switch (cmd)
    {
        case LED_IOCTL_GET:
        {            
            ret = BSP_OK;
            break;
        }
        case LED_IOCTL_SET:
        {
            ret = BSP_OK;
#if defined(BSP_CONFIG_BOARD_STICK) || defined(BSP_CONFIG_BOARD_HILINK)
            ret = led_threecolor_switch(stCtrlParms.led_dev_state);
#endif
            break;
        }
        default:
        {
            printk(KERN_ERR"[LED] kernelDeviceIoctl: CMD ERROR!\n");
            break;
        }
    }

    return ret;
}



static int __init kernelDeviceInit(void)
{
    int ret  = BSP_ERROR;
    int i = 0;
    int j = 0;

    ret = misc_register(&balong_led_miscdev);

    if(ret < 0)
    {
      printk(KERN_ERR "led init, register_chrdev failed.Ret=%d \n",ret);
    }
    printk("[LED] kernelDeviceInit: 1\ret = %d!\n",ret);
    
    return ret;
}

module_init(kernelDeviceInit);
module_exit(kernelDeviceRelease);

MODULE_AUTHOR("MBB.Huawei Device");
MODULE_DESCRIPTION("LED Driver");
MODULE_LICENSE("GPL");


#ifdef __cplusplus
}
#endif

