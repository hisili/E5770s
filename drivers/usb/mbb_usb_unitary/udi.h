
#ifndef    _UDI_H_
#define    _UDI_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

#ifndef VOID
typedef void                VOID;
#endif

#ifndef BSP_VOID
typedef void                BSP_VOID;
#endif

#ifndef BSP_U8
typedef unsigned char       BSP_U8;
#endif

#ifndef BSP_BOOL
typedef unsigned int        BSP_BOOL;
#endif

#ifndef BSP_U32
typedef unsigned int        BSP_U32;
#endif

#ifndef BSP_S32
typedef signed int          BSP_S32;
#endif

#ifndef BSP_S16
typedef signed short        BSP_S16;
#endif

#ifndef BSP_S8
typedef signed char         BSP_S8;
#endif

#ifndef BSP_CHAR
typedef char                BSP_CHAR;
#endif

#ifndef BSP_OK
#define BSP_OK              0
#endif

#ifndef OK
#define OK                  0
#endif

#ifndef BSP_ERROR
#define BSP_ERROR           (-1)
#endif

#ifndef ERROR
#define ERROR               (-1)
#endif

#ifndef TRUE
#define TRUE                (1)
#endif

#ifndef FALSE
#define FALSE               (0)
#endif




#define UDI_BUILD_DEV_ID(dev, type) (((BSP_U32)(dev) << 8) | ((BSP_U32)(type) & 0x00ff))
//#define UDI_BUILD_CMD_ID(dev, cmd) (((BSP_U32)(dev) << 8) | ((BSP_U32)(cmd) & 0xffff))


#define UDI_IOCTL_SET_WRITE_CB UDI_IOCTL_SET_READ_CB
#define UDI_IOCTL_SET_READ_CB  UDI_IOCTL_SET_READ_CB

typedef BSP_U32 UDI_HANDLE;

/* ���豸���� */
typedef enum tagUDI_DEVICE_MAIN_ID
{
    UDI_DEV_USB_ACM = 0,

    UDI_DEV_MAX                 /* ���������, ���ڱ߽�ֵ */
}UDI_DEVICE_MAIN_ID;

/* ���豸���Ͷ���(Ҫ�� usb ���豸��̬ͳһ����) */
/* ACM */
typedef enum tagUDI_ACM_DEV_TYPE
{
    UDI_USB_ACM_CTRL,
    UDI_USB_ACM_AT,
    UDI_USB_ACM_SHELL,
    UDI_USB_ACM_LTE_DIAG,
    UDI_USB_ACM_OM,
    UDI_USB_ACM_MODEM,
    UDI_USB_ACM_GPS,      /*HISO*/
    UDI_USB_ACM_3G_GPS,   /*ashell*/
    UDI_USB_ACM_3G_PCVOICE, /*Ԥ��*/
    UDI_USB_ACM_PCVOICE,    /*Ԥ��*/
    /*UDI_USB_ACM_3G_AT,    //3G AT*/
    /*UDI_USB_ACM_3G_MODEM, //3G PPP*/

    //qijiwen added for HSIC USB
    UDI_USB_HSIC_ACM0,
    UDI_USB_HSIC_ACM1,
    UDI_USB_HSIC_ACM2,
    UDI_USB_HSIC_ACM3,
    UDI_USB_HSIC_ACM4,
    UDI_USB_HSIC_ACM5,
    UDI_USB_HSIC_ACM6,
    UDI_USB_HSIC_ACM7,
    UDI_USB_HSIC_ACM8,
    UDI_USB_HSIC_ACM9,
    UDI_USB_HSIC_ACM10,
    UDI_USB_HSIC_ACM11,
    UDI_USB_HSIC_ACM12,
    UDI_USB_HSIC_ACM13,
	UDI_USB_HSIC_ACM14,
    UDI_USB_ACM_MAX                /* ���������, ���ڱ߽�ֵ */
}UDI_ACM_DEV_TYPE;

/* �豸ID�Ŷ��� */
typedef enum tagUDI_DEVICE_ID
{
    /* USB ACM */
    UDI_ACM_CTRL_ID =  UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_CTRL),
    UDI_ACM_AT_ID =    UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_AT),
    UDI_ACM_SHELL_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_SHELL),
    UDI_ACM_LTE_DIAG_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_LTE_DIAG),
    UDI_ACM_OM_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_OM),
    UDI_ACM_MODEM_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_MODEM),
    UDI_ACM_GPS_ID      = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_GPS),     //HISO
    UDI_ACM_3G_GPS_ID   = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_GPS),  //ashell
    UDI_ACM_3G_PCVOICE_ID = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_PCVOICE), //Ԥ��
    UDI_ACM_PCVOICE_ID    = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_PCVOICE),    //Ԥ��
    //UDI_ACM_3G_AT_ID      = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_AT),    //3G AT
    //UDI_ACM_3G_MODEM_ID   = UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_MODEM), //3G PPP

    /* MUST BE LAST */
    UDI_INVAL_DEV_ID = 0xFFFF
} UDI_DEVICE_ID;


/* �豸�Ĵ򿪲��� */
typedef struct tagUDI_OPEN_PARAM
{
    UDI_DEVICE_ID devid;                        /* �豸ID */
    void   *pPrivate;                            /* ģ�����е����� */
} UDI_OPEN_PARAM;


/*****************************************************************************
* �� �� ��  : udi_open
*
* ��������  : ���豸(����ͨ��)
*
* �������  : pParam: �豸�Ĵ����ò���
* �������  : ��
* �� �� ֵ  : -1:ʧ�� / ����:�ɹ�
*****************************************************************************/
UDI_HANDLE udi_open(UDI_OPEN_PARAM *pParam);

/*****************************************************************************
* �� �� ��  : udi_close
*
* ��������  : �ر��豸(����ͨ��)
*
* �������  : handle: �豸��handle
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_close(UDI_HANDLE handle);

/*****************************************************************************
* �� �� ��  : udi_write
*
* ��������  : ����д
*
* �������  : handle:  �豸��handle
*             pMemObj: buffer�ڴ� �� �ڴ��������
*             u32Size: ����д�ߴ� �� �ڴ��������ɲ�����
* �������  :
*
* �� �� ֵ  : ����ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_write(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size);

/*****************************************************************************
* �� �� ��  : udi_read
*
* ��������  : ���ݶ�
*
* �������  : handle:  �豸��handle
*             pMemObj: buffer�ڴ� �� �ڴ��������
*             u32Size: ���ݶ��ߴ� �� �ڴ��������ɲ�����
* �������  :
*
* �� �� ֵ  : ����ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_read(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size);

/*****************************************************************************
* �� �� ��  : udi_ioctl
*
* ��������  : ����ͨ����������
*
* �������  : handle: �豸��handle
*             u32Cmd: IOCTL������
*             pParam: ��������
* �������  :
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_ioctl(UDI_HANDLE handle, BSP_U32 u32Cmd, VOID* pParam);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _UDI_H_ */

