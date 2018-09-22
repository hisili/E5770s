
#include "drv_comm.h"
#include "sdio_slave.h"
#include "sdio_slave_osi.h"
#include "sdio_slave_hal.h"
#include "sdio_slave_cfg.h"
#include "sdio_slave_errcode.h"
extern BSP_S32 slave_init(void);
extern BSP_S32 SLAVE_Open(void);
extern BSP_VOID SLAVE_Close(BSP_S32 u32SlaveDevId);
extern BSP_S32 SLAVE_Ioctl(BSP_S32 s32SlaveDevId, BSP_U32 cmd, BSP_U32 arg);
extern BSP_S32 SLAVE_Write(BSP_S32 s32SlaveDevId, BSP_U8 *pBuf, BSP_U8 *pBufPhy, BSP_U32 u32Size);
extern BSP_S32 SLAVE_Read(BSP_S32 u32SlaveDevId, BSP_U8 *pBuf, BSP_U32 u32Size);

/*�豸�򿪱�־*/
static BSP_BOOL bModuleOpen = BSP_FALSE;

BSP_S32 BSP_SLAVE_Init(BSP_VOID)
{
    return slave_init();
}
EXPORT_SYMBOL(BSP_SLAVE_Init);

/*****************************************************************************
* �� �� ��  : BSP_SLAVE_Open
*
* ��������  : SLAVE �豸��
*
* �������  : ��
*           
* �������  : ��
* �� �� ֵ  : �豸ID
*****************************************************************************/
BSP_S32 BSP_SLAVE_Open(BSP_VOID)
{
    BSP_S32 ret = 0;

    if(bModuleOpen)
    {
        return BSP_ERROR;
    }
    
    //SLAVE_Init();
    
    /*���豸*/
    ret = SLAVE_Open();
    if(!ret)
    {
        return BSP_ERROR;
    }
    
    bModuleOpen = BSP_TRUE;

    return ret;
}
EXPORT_SYMBOL(BSP_SLAVE_Open);

/*****************************************************************************
* �� �� ��  : BSP_SLAVE_Close
*
* ��������  : SLAVE �豸�ر�
*
* �������  : s32SlaveDevId:  �豸ID
*           
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_SLAVE_Close(BSP_S32 s32SlaveDevId)
{
    if(BSP_FALSE ==bModuleOpen)
    {
        printk("dev was closed\n");
        return BSP_ERROR;
    }

    bModuleOpen = BSP_FALSE;
    
    SLAVE_Close(s32SlaveDevId);
    return BSP_OK;

}
EXPORT_SYMBOL(BSP_SLAVE_Close);

/*****************************************************************************
* �� �� ��  : BSP_SLAVE_Ioctl
*
* ��������  : SLAVE IOCTL�ӿ�
*
* �������  : handle:  �豸���
*             cmd:     ��������
*             u32Size: Դ���ݵ��ֽ���
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_SLAVE_Ioctl(BSP_S32 handle, BSP_U32 cmd, BSP_U32 arg)
{
    if(BSP_TRUE != bModuleOpen)
    {
        return BSP_ERROR;   
    }
    else 
        return SLAVE_Ioctl(handle,cmd,arg);

}
EXPORT_SYMBOL(BSP_SLAVE_Ioctl);

/*****************************************************************************
* �� �� ��  : BSP_SLAVE_Write
*
* ��������  : SLAVE д�ӿ�
*
* �������  : handle:  �豸���
*             pBuf:    Դ����buffer���׵�ַ
*             u32Size: Դ���ݵ��ֽ���
* �������  : ��
* �� �� ֵ  : ״̬/д���ֽ���
*****************************************************************************/
BSP_S32 BSP_SLAVE_Write(BSP_S32 handle, BSP_U8 *buf, BSP_U8 *bufPhy, BSP_U32 len)
{
    if(BSP_TRUE !=bModuleOpen)
    {
        return BSP_ERROR;
    }
    else 
        return SLAVE_Write(handle,buf, bufPhy, len);
}
EXPORT_SYMBOL(BSP_SLAVE_Write);

/*****************************************************************************
* �� �� ��  : BSP_SLAVE_Read
*
* ��������  : SLAVE �������ӿ�
*
* �������  : handle:  �豸���
*             pBuf:    ����buffer���׵�ַ
*             u32Size: Դ���ݵ��ֽ���
* �������  : ��
* �� �� ֵ  : ״̬/д���ֽ���
*****************************************************************************/
BSP_S32 BSP_SLAVE_Read(BSP_S32 handle, BSP_U8 *buf, BSP_U32 len)
{
    if(BSP_TRUE !=bModuleOpen)
    {
        return BSP_ERROR;
    }
    else 
        return SLAVE_Read(handle,buf,len);
}
EXPORT_SYMBOL(BSP_SLAVE_Read);
