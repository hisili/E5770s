

#include <linux/module.h>  
#include <linux/kernel.h>  
#include <linux/types.h>  
#include <linux/fs.h>  
#include <linux/init.h>  
#include <linux/delay.h>  
#include <asm/uaccess.h>  
#include <asm/irq.h>  
#include <asm/io.h>  
#include <linux/miscdevice.h> 
#include <linux/ioctl.h>
#include "usb_debug.h"

#define SDDEV_MAJOR 10   /*Ԥ���sd�����豸��,д0��ʾ��̬���䣬д����ֵ���Ծ�̬����
                          *����ע�����һ�������豸�������豸�����豸�Ź̶���10
                          */
/* ����cmd���� */
#define IOCTL_DISK_BLOCK_NUM _IOR( SDDEV_MAJOR, 0, USB_INT)
#define IOCTL_MOUNT_DISK _IO( SDDEV_MAJOR, 1 )
#define IOCTL_UNMOUNT_DISK _IO( SDDEV_MAJOR, 2 )
#define IOCTL_IS_MOUNTED_DISK _IO( SDDEV_MAJOR, 3 )
#if(FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
#define IOCTL_IS_MOUNTED_UDISK _IOWR( SDDEV_MAJOR, 4, USB_INT)
#define IOCTL_HOST_STATUS _IOR( SDDEV_MAJOR, 5, USB_INT)
#define IOCTL_PORT_STATUS _IOR( SDDEV_MAJOR, 6, USB_INT)
#define SDDEV_IOC_MAXNR 6
#else
#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
#define IOCTL_FTEN_USB_STATUS _IOR( SDDEV_MAJOR, 4, USB_INT)
#define SDDEV_IOC_MAXNR 4
#else
#define SDDEV_IOC_MAXNR 3
#endif
#endif

/*�豸����*/
#define SDDEV_NAME "usbware_disk_0"	

#define WEB_MODE 0
#define USB_MODE 1
