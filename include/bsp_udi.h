
#ifndef    _BSP_UDI_H_
#define    _BSP_UDI_H_


#include  <osl_types.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**************************************************************************
  �궨��
**************************************************************************/
#define UDI_INVALID_HANDLE     (-1)

#define UDI_CAPA_BLOCK_READ	((BSP_U32)(1<<0)) /* ���豸��read�ӿ�Ϊ�����ӿ� */
#define UDI_CAPA_BLOCK_WRITE	((BSP_U32)(1<<1)) /* ���豸��write�ӿ�Ϊ�����ӿ� */
#define UDI_CAPA_READ_CB		((BSP_U32)(1<<2)) /* ���豸֧��read �ص����� */
#define UDI_CAPA_WRITE_CB		((BSP_U32)(1<<3)) /* ���豸֧��write �ص����� */
#define UDI_CAPA_BUFFER_LIST	((BSP_U32)(1<<4)) /* ���豸�Ķ�дbufferΪ�ڴ�����ṹ(Ĭ��Ϊ��ͨ�ڴ��) */
#define UDI_CAPA_CTRL_OPT		((BSP_U32)(1<<5)) /* ���豸֧�ֿ��Ʋ��� */


/**************************************************************************
  �ṹ����
**************************************************************************/
#define UDI_BUILD_DEV_ID(dev, type) (((BSP_U32)(dev) << 8) | ((BSP_U32)(type) & 0x00ff))
#define UDI_BUILD_CMD_ID(dev, cmd) (((BSP_U32)(dev) << 8) | ((BSP_U32)(cmd) & 0xffff))


typedef s32 UDI_HANDLE;

/* ���豸���� */
typedef enum tagUDI_DEVICE_MAIN_ID
{
	UDI_DEV_USB_ACM = 0,
	UDI_DEV_USB_NCM,
	UDI_DEV_ICC,
	UDI_DEV_UART,

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
	UDI_USB_ACM_3G_DIAG,
	UDI_USB_ACM_MODEM,
	UDI_USB_ACM_GPS,
	UDI_USB_ACM_MAX                /* ���������, ���ڱ߽�ֵ */
}UDI_ACM_DEV_TYPE;

/* NCM */
typedef enum tagUDI_NCM_DEV_TYPE
{
	UDI_USB_NCM_NDIS,
	UDI_USB_NCM_CTRL,
	UDI_USB_NCM_NDIS1,
	UDI_USB_NCM_CTRL1,
	UDI_USB_NCM_NDIS2,
	UDI_USB_NCM_CTRL2,
	UDI_USB_NCM_NDIS3,
	UDI_USB_NCM_CTRL3,
    UDI_USB_NCM_BOTTOM,

	UDI_USB_NCM_MAX                /* ���������, ���ڱ߽�ֵ */
}UDI_NCM_DEV_TYPE;

/* �豸ID�Ŷ��� */
typedef enum tagUDI_DEVICE_ID
{
	/* USB ACM */
	UDI_ACM_CTRL_ID =			UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_CTRL),
	UDI_ACM_AT_ID =			UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_AT),
	UDI_ACM_SHELL_ID =			UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_SHELL),
	UDI_ACM_LTE_DIAG_ID =		UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_LTE_DIAG),
	UDI_ACM_3G_DIAG_ID =		UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_3G_DIAG),
	UDI_ACM_MODEM_ID =		UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_MODEM),
	UDI_ACM_GPS_ID=			UDI_BUILD_DEV_ID(UDI_DEV_USB_ACM, UDI_USB_ACM_GPS),

	/* USB NCM */
	UDI_NCM_NDIS_ID =			UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_NDIS),
	UDI_NCM_CTRL_ID =			UDI_BUILD_DEV_ID(UDI_DEV_USB_NCM, UDI_USB_NCM_CTRL),

	/* UART */
	UDI_UART_0_ID =				UDI_BUILD_DEV_ID(UDI_DEV_UART, 0),
	UDI_UART_1_ID =				UDI_BUILD_DEV_ID(UDI_DEV_UART, 1),

	/* ICC */
	UDI_ICC_IFC_ID  =			UDI_BUILD_DEV_ID(UDI_DEV_ICC, 0),
	UDI_ICC_IPM_ID  =			UDI_BUILD_DEV_ID(UDI_DEV_ICC, 1),

	/* MUST BE LAST */
	UDI_INVAL_DEV_ID = 0xFFFF
} UDI_DEVICE_ID;

/* �豸�Ĵ򿪲��� */
typedef struct tagUDI_OPEN_PARAM
{
	UDI_DEVICE_ID devid;			/* �豸ID */
	void   *pPrivate;				/* ģ�����е����� */
} UDI_OPEN_PARAM;

/* IOCTL ������,��Ҫ���������ڴ���� */
typedef enum tagUDI_IOCTL_CMD_TYPE
{
	UDI_IOCTL_SET_WRITE_CB = 0xF001,            /* ����һ����ʼ��ֵ��ֹ��ϵͳ�����ͻ */
	UDI_IOCTL_SET_READ_CB,

	UDI_IOCTL_INVAL_CMD = 0xFFFFFFFF
} UDI_IOCTL_CMD_TYPE;

/**************************************************************************
  ��������
**************************************************************************/
/*****************************************************************************
* �� �� ��  : udi_get_capability
*
* ��������  : �����豸ID��ȡ��ǰ�豸֧�ֵ�����
*
* �������  : devId: �豸ID
* �������  : ��
* �� �� ֵ  : ֧�ֵ�����ֵ
*****************************************************************************/
s32 udi_get_capability(UDI_DEVICE_ID devId);

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
s32 udi_close(UDI_HANDLE handle);

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
s32 udi_write(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size);

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
s32 udi_read(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size);

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
s32 udi_ioctl(UDI_HANDLE handle, BSP_U32 u32Cmd, VOID* pParam);

s32 BSP_UDI_Init(VOID);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BSP_UDI_H_ */

