#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include "drv_ncm.h"
#include "bsp_ncm.h"
#include "drv_udi.h"  

/*****************************************************************************
* �� �� ��  : bsp_ncm_open
*
* ��������  : ������ȡ����ʹ��NCM�豸ID,����ͨ�����ͣ�PSʹ��;����ͨ�����ͣ�
*              MSP����AT����ʹ��
*
* �������  : NCM_DEV_TYPE_E enDevType  �豸����
* �������  : pu32NcmDevId              NCM �豸ID
*
* �� �� ֵ  : BSP_ERR_NET_NOIDLEDEV
*             OK
*
* �޸ļ�¼  : 2010��3��17��   liumengcun  creat
*****************************************************************************/
BSP_U32 bsp_ncm_open(NCM_DEV_TYPE_E enDevType, BSP_U32 pu32NcmDevId)
{
    return 0;
}

/*****************************************************************************
* �� �� ��  : bsp_ncm_write
*
* ��������  : ��������
*
* �������  : BSP_U32 u32NcmDevId  NCM�豸ID
                             void *     net_priv tcp/ip�����Ĳ���������tcp/ip�Խ�ʱ�ò�������ΪNULL
* �������  : BSP_VOID *pPktEncap       ����װ�׵�ַ
*
* �� �� ֵ  : BSP_OK
*             BSP_ERR_NET_INVALID_PARA
*             BSP_ERR_NET_BUF_ALLOC_FAILED
*
* �޸ļ�¼  : 2010��3��17��   liumengcun  creat
*****************************************************************************/
BSP_U32 bsp_ncm_write(BSP_U32 u32NcmDevId, BSP_VOID *pPktEncap, void *net_priv)
{
    return 0;
}

/*****************************************************************************
* �� �� ��  : bsp_ncm_ioctl
*
* ��������  : ����NCM�豸����
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ  : 
*
* �޸ļ�¼  : 2010��3��17��   liumengcun  creat
*****************************************************************************/
BSP_U32 bsp_ncm_ioctl(BSP_U32 u32NcmDevId, NCM_IOCTL_CMD_TYPE_E enNcmCmd, BSP_VOID *param)
{
    return 0;
}

/*****************************************************************************
* �� �� ��  : bsp_ncm_close
*
* ��������  : �ر�NCM�豸
*
* �������  : NCM_DEV_TYPE_E enDevType   �豸ID����
*             BSP_U32 u32NcmDevId        NCM�豸ID
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : 2010��3��17��   liumengcun  creat
*****************************************************************************/
BSP_U32 bsp_ncm_close(NCM_DEV_TYPE_E enDevType, BSP_U32 u32NcmDevId)
{
    return 0;
}
