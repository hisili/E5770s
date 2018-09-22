
//#include <stdio.h>
//#include <taskLib.h>
//#include <intLib.h>
//#include <logLib.h>
//#include "BSP_GLOBAL.h"
//#include "arm_pbxa9.h"
//#include "product_config.h"
//#include "DrvInterface.h"
#include "DrvInterface.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include "BSP_DRV_SPI.h"
#include "data_types.h"
//#include "BSP_Report.h"

#define INTEGRATOR_SC_BASE 0x90000000

//add new interface

#include "slic_spi.h"
//#include "OnChipRom.h"
//#include "sys.h"
//#include "si3217x_intf.h"
//#include "si3217x_registers.h"
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/earlysuspend.h>
#include <linux/miscdevice.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/sched.h>
#include <linux/jiffies.h>
#include <asm/irq.h>
#include <mach/irqs.h>
//#include <linux/spi/spi.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/compat.h>
//#include <mach/gpio-tlmm-v1.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/spinlock.h>


#include "proslic.h"
#include "si3217x_registers.h"

#include "drv_sio.h"
#include "slic_log.h"

//end






#ifdef __cplusplus
extern "C" {
#endif


enum  EN_PERIPHERAL_TYPE
{
    EN_PERIPHERAL_USB = 0,
    EN_PERIPHERAL_HSIC,
    EN_PERIPHERAL_MAC,
    EN_PERIPHERAL_SIO,
};

BSP_U32 g_ulSioBaseAddr = 0;


    //�̳�M�˼Ĵ����ӿ�����
#define OUTREG32(reg, val) \
    BSP_REG_WRITE(reg, 0, val)

#define INREG32(reg) \
    BSP_REG(reg, 0)

#define SETBITVALUE32(addr, mask, value) \
    OUTREG32((addr), (INREG32(addr)&(~(mask))) | ((value)&(mask)))

    //end




#if 0
    /*����SPI���ԵĽṹ�壬����SPI����ַ��*/
    typedef struct tagSPI_ATTR
    {
        SPI_DEV_ATTR_S stSpiConf[SPI_DEV_CS_MAX];/*�洢Ƭѡ�����豸���ԵĽṹ��*/
        SEM_ID SpiSemId;                         /*ÿ��SPI������һ���ź���*/
        SPI_DEV_CS_E enSpiOwner;                 /*SPI�����ĸ�Ƭѡ���ӵ��豸��������*/
        BSP_U32 u32SpiBaseAddr;                  /*SPI����ַ*/
        BSP_BOOL abFlag[SPI_DEV_CS_MAX];         /*��־SPI�Ƿ���ĳƬѡ���ӵ��豸���ù�*/
    }SPI_ATTR_S;
#endif

    static DEFINE_SPINLOCK(slic_lock);


    /*��¼SPI�Ƿ񱻳�ʼ����ȫ�ֱ���*/
    BSP_BOOL g_bSpiInit = BSP_FALSE;

    //SPI_ATTR_S stSpiDev[SPI_ID_MAX] = {0}; /*lint !e64*/

    /* ��ά�ɲ�ƽ̨ע�ắ��*/
    //extern BSPRegExEventFunc g_pBSPRegExEventFunc;

    /*SPI���ж��е��ã���Ҫ���ж�*/
    BSP_U32 g_stSpiIntCallLock = 0;

    /*SPI �͹����ж��е���*/
#if ((defined (CHIP_BB_6920ES) || defined (CHIP_BB_6920CS))\
    && (defined (BOARD_ASIC)||defined (BOARD_ASIC_BIGPACK)))
#define SPI_DRV_INT_CALL	1
#else
#define SPI_DRV_INT_CALL	0
#endif







    //add new interface
#define ECS_SPI0_BASE       (INTEGRATOR_SC_BASE + 0x00008000)
#define ECS_SPI0_SIZE		0x00001000

#define ECS_SPI1_BASE       (INTEGRATOR_SC_BASE + 0x00023000)
#define ECS_SPI1_SIZE		0x00001000

    /*const */UINT32 spiBase[2] = {ECS_SPI0_BASE, ECS_SPI1_BASE};
    UINT32 g_gpioBase = 0;
    INT32 g_lUserModeStatus = 0;

    //end







#if 0
    /*****************************************************************************
    * �� �� ��  : SPI_Init
    *
    * ��������  : SPI��ʼ��
    *
    * �������  : ��
    *
    * �������  : ��
    *
    * �� �� ֵ  : ��ʼ���ɹ�����ʧ��
    *****************************************************************************/
    BSP_S32 SPI_Init()
    {
        BSP_U32 u32Number;

        /*���SPI�Ѿ���ʼ����ֱ�ӷ���BSP_OK*/
        if(BSP_TRUE == g_bSpiInit)
        {
            return BSP_OK;
        }

        memset(stSpiDev, 0x0, sizeof(SPI_ATTR_S) * SPI_ID_MAX);

        /*Ϊÿ��SPI�Ļ���ַ��ֵ*/
        stSpiDev[SPI_ID0].u32SpiBaseAddr = SPI1_BASE_ADDR;
        stSpiDev[SPI_ID1].u32SpiBaseAddr = SPI2_REGBASE_ADDR;

#if (defined (CHIP_BB_6920ES) || defined(CHIP_BB_6920CS)\
    && (defined (BOARD_ASIC)||defined (BOARD_ASIC_BIGPACK)))
        /* ʹ��SPI���� */
        BSP_REG_WRITEBITS(INTEGRATOR_SC_BASE, INTEGRATOR_SC_IOS_CTRL98, SSP0_CTRL);     // IO����ΪSSP0
        BSP_REG_WRITEBITS(INTEGRATOR_SC_BASE, INTEGRATOR_SC_IOS_CTRL81, SSP0_WIRE_4 | SSP0_CS1_EN);     // ʹ��SSP0,CS0��CS1,����CS1�ܽ�Ĭ��Ϊ�ͣ�����CS0��ʱ��CS1Ҳ��ѡ��
#ifdef FEATURE_BOARD_STUB_BJ_UDP
        BSP_REG_WRITEBITS(INTEGRATOR_SC_BASE, INTEGRATOR_SC_IOS_CTRL98, SSP1_CTRL); 	// IO����ΪSSP1
        BSP_REG_WRITEBITS(INTEGRATOR_SC_BASE, INTEGRATOR_SC_IOS_CTRL81, SSP1_WIRE_4  | SSP1_CS1_EN);     // ʹ��SSP1
#endif
#endif

        for(u32Number = SPI_ID0; u32Number < SPI_ID_MAX; u32Number++)
        {
            stSpiDev[u32Number].enSpiOwner = NO_OWNER;
            /*Ϊÿ��SPI����һ���ź���*/
            stSpiDev[u32Number].SpiSemId = (SEM_ID)semMCreate(SEM_Q_FIFO);
            /* �ź�������ʧ�ܣ����ش���*/
            if(NULL == stSpiDev[u32Number].SpiSemId )
            {
                BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"NULL == stSpiDev[u32Number].SpiSemId.\n",0,0,0,0,0,0);
                return BSP_ERR_SPI_SEM_CREATE;
            }

            /*��ÿ��SPI�е�һЩ�Ĵ�����ֵΪ�ϵ��ʼֵ*/
            BSP_REG_WRITE(stSpiDev[u32Number].u32SpiBaseAddr, SPI_CTRL0_OFFSET, 0x0);
            BSP_REG_WRITE(stSpiDev[u32Number].u32SpiBaseAddr, SPI_CTRL1_OFFSET, 0x0);
            BSP_REG_WRITE(stSpiDev[u32Number].u32SpiBaseAddr, SPI_EN_OFFSET, 0x0);
            BSP_REG_WRITE(stSpiDev[u32Number].u32SpiBaseAddr, SPI_MWCTRL_OFFSET, 0x0);
            BSP_REG_WRITE(stSpiDev[u32Number].u32SpiBaseAddr, SPI_SLAVE_EN_OFFSET, 0x0);
            BSP_REG_WRITE(stSpiDev[u32Number].u32SpiBaseAddr, SPI_BAUD_OFFSET, 0x0);
        }

        g_bSpiInit = BSP_TRUE;

        return BSP_OK;
    }


    /*****************************************************************************
    * �� �� ��  : SPI_Lock
    *
    * ��������  : ����SPI����
    *
    * �������  : enSpiId ��Ҫ������SPI��
    *
    * �������  : ��
    *
    * �� �� ֵ  : �����ɹ�����ʧ��
    *****************************************************************************/
    BSP_S32  SPI_Lock(SPI_DEV_ID_E enSpiId)
    {
#if (SPI_DRV_INT_CALL == 1)
        g_stSpiIntCallLock = intLock();
        return BSP_OK;
#else
        return (semTake(stSpiDev[enSpiId].SpiSemId, WAIT_FOREVER));
#endif
    }

    /*****************************************************************************
    * �� �� ��  : SPI_UnLock
    *
    * ��������  : �ͷ�SPI����
    *
    * �������  : enSpiId ��Ҫ�ͷŵ�SPI��
    *
    * �������  : ��
    *
    * �� �� ֵ  : �ͷųɹ�����ʧ��
    *****************************************************************************/
    BSP_S32 SPI_UnLock(SPI_DEV_ID_E enSpiId)
    {
#if (SPI_DRV_INT_CALL == 1)
        intUnlock(g_stSpiIntCallLock);
        return BSP_OK;
#else
        return (semGive(stSpiDev[enSpiId].SpiSemId));
#endif
    }

    /*****************************************************************************
    * �� �� ��  : SPI_Poll_Send
    *
    * ��������  : ��ѯģʽ�µ����ݷ���
    *
    * �������  : pSpiId  �������ݷ��͵�SPI�ź�Ƭѡ�š�
    pData   ��Ҫ���͵����ݻ�����ָ��
    *             u32time Ҫ�������ݵĴ���
    *
    * �������  : ��
    *
    * �� �� ֵ  : BSP_OK     ���ͳɹ�
    *             ERROR  ����ʧ��
    *****************************************************************************/
    BSP_S32 SPI_POLL_Send(SPI_DEV_S *pSpiId, void *pData, BSP_U32 u32Count)
    {
        BSP_U32 i;
        BSP_U16 *pSh;
        SPI_DATA_LEN_E enTmpDataLen = stSpiDev[pSpiId->enSpiId].stSpiConf[pSpiId->enSpiCs].enDataLen;
        BSP_U32 u32TemBaseAddr = stSpiDev[pSpiId->enSpiId].u32SpiBaseAddr;

        if((NULL == pData) || (0 == u32Count) || (u32Count > SPI_FIFO_DEPTH))
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"SPI_POLL_Send Paramater ERROR. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_INVALID_PARA;
        }

        /* ���ݿ��Ϊ8Bit����16Bit*/
        if((SPI_DATASIZE_8BITS == enTmpDataLen)||(SPI_DATASIZE_16BITS == enTmpDataLen))
        {
            pSh = (BSP_U16*)pData;
            /* �����ݼĴ�����д������*/
            for(i = 0; i < u32Count; i++)
            {
                BSP_REG_WRITE(u32TemBaseAddr, SPI_DATA_OFFSET_BASE,(*pSh));
                pSh++;
            }
        }
        else
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"SPI_POLL_Send enTmpDataLen ERROR. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_DATASIZE_INVALID;
        }

        return BSP_OK;
    }

    /*****************************************************************************
    * �� �� ��  : SPI_Poll_Receive
    *
    * ��������  : ��ѯģʽ�µ����ݽ���
    *
    * �������  : pSpiId  �������ݽ��յ�SPI�ź�Ƭѡ�š�
    pData   �洢�������ݵĻ�����ָ��
    *             u32Lens �����յ����ݳ���
    *
    * �������  : ��
    *
    * �� �� ֵ  : BSP_OK    ���ճɹ�
    *             ERROR ����ʧ��
    *****************************************************************************/
    BSP_S32 SPI_POLL_Receive(SPI_DEV_S *pSpiId,BSP_VOID *pData, BSP_U32 u32Lens)
    {
        BSP_U8 *pCh;
        BSP_U16 *pSh;
        BSP_U32 u32Number = 0;
        BSP_U32 u32Temp = 0;
        SPI_DATA_LEN_E enTmpDataLen = stSpiDev[pSpiId->enSpiId].stSpiConf[pSpiId->enSpiCs].enDataLen;
        BSP_U32 u32TemBaseAddr = stSpiDev[pSpiId->enSpiId].u32SpiBaseAddr;

        if((NULL == pData) || (0 == u32Lens))
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"SPI_POLL_Receive Paramater ERROR. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_INVALID_PARA;
        }

        /* ���ݿ��Ϊ8Bit*/
        if(SPI_DATASIZE_8BITS == enTmpDataLen)
        {
            pCh = (BSP_U8 *)pData;
            /* �ȴ�����FIFO�ǿ�,�ǿ����ȡ����*/
            while(SPI_STATUS & 0x8)
            {
                //            BSP_REG8_READ(u32TemBaseAddr, SPI_DATA_OFFSET_BASE,(*pCh));
                BSP_REG_READ(u32TemBaseAddr, SPI_DATA_OFFSET_BASE, u32Temp);
                (*pCh) = (BSP_U8)(u32Temp & 0xff);
                u32Number++;
                pCh++;
            }
        }
        /* ���ݿ��Ϊ16Bit*/
        else if(SPI_DATASIZE_16BITS == enTmpDataLen)
        {
            pSh = (BSP_U16 *)pData;
            /* �ȴ�����FIFO�ǿ�,�ǿ����ȡ����*/
            while(SPI_STATUS & 0x8)
            {
                //            BSP_REG16_READ(u32TemBaseAddr, SPI_DATA_OFFSET_BASE,(*pSh));
                BSP_REG_READ(u32TemBaseAddr, SPI_DATA_OFFSET_BASE, u32Temp);
                (*pSh) = (BSP_U16)(u32Temp & 0xffff);
                u32Number++;
                pSh++;
            }
        }
        else
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"SPI_POLL_Receive enTmpDataLen ERROR. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_DATASIZE_INVALID;
        }

        /* ����������ݱ�Ԥ�����ݶ࣬���ش���*/
        if(u32Number > u32Lens)
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"SPI_POLL_Receive. The actual data don't equal expected 1. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_RECEIVE_POLL;
        }

        return BSP_OK;
    }

    /*****************************************************************************
    * �� �� ��  : BSP_SPI_SetAttr
    *
    * ��������  : ����SPI�ļĴ��������ÿ��������ֳ��ȡ�����֡���ȵȡ�
    *
    * �������  : enSpiID        ��Ҫ���õ�SPI�ţ��Լ�������ƬƬѡ�������õ�Ƭѡ�š�
    *             pstSpiDevAttr  ��¼SPI����豸���ԵĽṹ��ָ�룬�ṹ���Ա�����豸
    ��Ҫ�������ֳ��ȣ�����֡���ȣ�ʹ��Э�飬�����ʵȡ�
    *
    * �������  : ��
    *
    * �� �� ֵ  : BSP_OK    ���ճɹ�
    *             ERROR ����ʧ��
    *****************************************************************************/
    BSP_S32 BSP_SPI_SetAttr(SPI_DEV_S *pstSpiID,SPI_DEV_ATTR_S *pstSpiDevAttr)
    {
        BSP_U32 u32Ctrl0 = 0;
        BSP_U32 u32TemBaseAddr;
        SPI_DEV_ID_E enTemSpiId = pstSpiID->enSpiId;
        SPI_DEV_CS_E enTemSpiCs = pstSpiID->enSpiCs;

        /*�����ж�*/
        if((enTemSpiId >= SPI_ID_MAX)||(enTemSpiId < SPI_ID0)
            || (enTemSpiCs >= SPI_DEV_CS_MAX) || (enTemSpiCs < SPI_DEV_CS0)
            || ((pstSpiDevAttr -> enCommandLen) >=  SPI_COMMANDSIZE_MAX)
            || ((pstSpiDevAttr -> enCommandLen) <  SPI_COMMANDSIZE_1BITS)
            || ((pstSpiDevAttr ->enDataLen) >= SPI_DATASIZE_MAX)
            || ((pstSpiDevAttr ->enDataLen) < SPI_DATASIZE_4BITS)
            || ((pstSpiDevAttr -> enSpiProt) >= SPI_PROT_MAX)
            || ((pstSpiDevAttr -> enSpiProt) < SPI_PROT_SPI))
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_SetAttr Paramater ERROR. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_INVALID_PARA;
        }

        /*���SPIû�г�ʼ������������SPI�����ش���*/
        if(BSP_FALSE == g_bSpiInit)
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_SetAttr. BSP_FALSE == g_bSpiInit. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_MODULE_NOT_INITED;
        }

        if (BSP_OK != SPI_Lock(enTemSpiId))
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write. BSP_OK != SPI_Lock. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_SEM_LOCK;
        }

        u32TemBaseAddr = stSpiDev[enTemSpiId].u32SpiBaseAddr;

        /* ������豸�����Ա��浽��ԱstSpiConf�� */
        memcpy(&(stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs]), pstSpiDevAttr, sizeof(SPI_DEV_ATTR_S));

        /* ��ԱenSpiOwner��¼��ǰ�ĸ�Ƭѡ���ӵ��豸����ռ��SPI */
        stSpiDev[enTemSpiId].enSpiOwner = enTemSpiCs;

        /* ����abFlag��ʾƬѡ���ӵ��豸�Ƿ�ʹ�ù�SPI�����ʹ�ù����豸���Իᴢ����
        stSpiDev�У��ٴ�ʹ�ø��豸ʱ��ֱ�Ӵ�stSpiDev�л�ȡ�豸����*/
        stSpiDev[enTemSpiId].abFlag[enTemSpiCs] = BSP_TRUE;

        /* �����豸���ԣ���Ͽ��ƼĴ���Ctrl0Ҫ���õ�ֵ*/
        u32Ctrl0 = pstSpiDevAttr->enDataLen | (pstSpiDevAttr->enSpiProt << SPI_PROT_SHIFT_BITS)
            | pstSpiDevAttr->enCommandLen << SPI_COMM_SHIFT_BITS;


        /*��ֹSPI���ݴ���*/
        BSP_REG_WRITE(u32TemBaseAddr, SPI_EN_OFFSET, 0x0);

        /*����ctrl0�Ĵ��������������ֳ��ȣ����ݿ��*/
        BSP_REG_WRITE(u32TemBaseAddr, SPI_CTRL0_OFFSET,u32Ctrl0);

        /*����SPI������*/
        BSP_REG_WRITE(u32TemBaseAddr, SPI_BAUD_OFFSET,pstSpiDevAttr->u16SpiBaud);

        if(BSP_OK != SPI_UnLock(enTemSpiId))
        {
            return BSP_ERR_SPI_SEM_UNLOCK;
        }

        return BSP_OK;

    }



    /*****************************************************************************
    * �� �� ��  : BSP_SPI_Write
    *
    * ��������  : ͨ��SPI���豸д������
    *
    * �������  : pstWriteData ��¼��SPI���ݴ����й���Ϣ�Ľṹ��ָ�룬��Ա����
    Ҫ��д��SPI�ţ�Ƭѡ�ţ�����ģʽ��
    *             pSendData    �洢���յ����ݻ�����ָ��
    *             u32Length    �����յ����ݳ���
    *
    * �������  : ��
    *
    * �� �� ֵ  : BSP_OK    ���ճɹ�
    *             ERROR ����ʧ��
    *****************************************************************************/
    BSP_S32 BSP_SPI_Write(SPI_DATA_HANDLE_S *pstWriteData,BSP_VOID *pSendData, BSP_U32 u32Length)
    {
        BSP_S32 s32State;
        BSP_U32 u32LoopNum = 0;
        BSP_U32 u32RegValue = 0;
        SPI_DEV_ID_E enTemSpiId = SPI_ID0;
        SPI_DEV_CS_E enTemSpiCs = SPI_DEV_CS0;
        SPI_SCPOL_E  enTemScpol = SPI_SCPOL_LOW;
        BSP_U32 u32TemBaseAddr = 0;
        SPI_DATA_LEN_E enDataLen;
        EX_REPORT_SPI_S stReportSpi;

        /*�����ж�*/
        if((NULL == pSendData)||(u32Length < 1)||(NULL == pstWriteData)
            ||(pstWriteData->enSpiID >= SPI_ID_MAX) || (pstWriteData->enSpiID < SPI_ID0)
            ||(pstWriteData->enCsID >= SPI_DEV_CS_MAX) || (pstWriteData->enCsID < SPI_DEV_CS0)
            ||(pstWriteData->enMode >= SPI_SENDMOD_MAX)
            ||(pstWriteData->enMode < SPI_SENDMOD_POLLING))
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write Paramater ERROR. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_INVALID_PARA;
        }

        enTemSpiId = pstWriteData->enSpiID;
        enTemSpiCs = pstWriteData->enCsID;
        enTemScpol = stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs].enSpiScpol;
        enDataLen  =  stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs].enDataLen;
        u32TemBaseAddr = stSpiDev[enTemSpiId].u32SpiBaseAddr;

        /*���SPIû�г�ʼ�������ش���*/
        if(BSP_FALSE == g_bSpiInit)
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write. BSP_FALSE == g_bSpiInit. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_MODULE_NOT_INITED;
        }

        /*����SPI����*/
        if (BSP_OK != SPI_Lock(enTemSpiId))
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write. BSP_OK != SPI_Lock. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_SEM_LOCK;
        }

        /*��ȡ��ǰ��ƬƬѡ���ӵ��豸ռ��SPI����,����ǲ���Ҫ�������豸����Ҫ��������SPI*/
        s32State = SPI_SetSpiOwner((SPI_DEV_S *)pstWriteData);/*lint !e740*/
        if(BSP_OK != s32State)
        {
            if(BSP_OK != SPI_UnLock(enTemSpiId))
            {
                return BSP_ERR_SPI_SEM_UNLOCK;
            }
            return s32State;
        }

        /*��ֹSPI���豸*/
        BSP_REG_WRITE(u32TemBaseAddr,SPI_SLAVE_EN_OFFSET,0x0);

        /*��ֹSPI���ݴ���*/
        BSP_REG_WRITE(u32TemBaseAddr,SPI_EN_OFFSET,0x0);

        /*���üĴ����������ݴ���ģʽ����Ϊ��������*/
        switch(stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs].enSpiProt)
        {
            /*ʹ��NSMЭ��ʱ������MWCR��modλ*/
        case SPI_PROT_NSM:
            BSP_REG_READ(u32TemBaseAddr,SPI_MWCTRL_OFFSET,u32RegValue);
            u32RegValue |= 0x2;
            BSP_REG_WRITE(u32TemBaseAddr,SPI_MWCTRL_OFFSET,u32RegValue);
            break;
            /*ʹ��SPIЭ��ʱ���޸�CTRL0�Ĵ�����Tmodλ*/
        case SPI_PROT_SPI:
            BSP_REG_READ(u32TemBaseAddr,SPI_CTRL0_OFFSET,u32RegValue);
            u32RegValue &= (~0x3cf);
            u32RegValue = (u32RegValue | 0x100 | 0x40 | enDataLen | (enTemScpol << 0x7));
            BSP_REG_WRITE(u32TemBaseAddr,SPI_CTRL0_OFFSET,u32RegValue);
            break;
            /*��ǰ����ʵ�ֲ�֧��SSPЭ��*/
        case SPI_PROT_SSP:
        default:
            if(BSP_OK != SPI_UnLock(enTemSpiId))
            {
                return BSP_ERR_SPI_SEM_UNLOCK;
            }
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write. Prot not support. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_PROT_INVALID;
        }

        /*ʹ��Master�����������ݼĴ���д������ʱ�����ݻ��Լ�ת�Ƶ�FIFO��*/
        BSP_REG_WRITE(u32TemBaseAddr,SPI_EN_OFFSET,0x1);

        /*�����ݼĴ�����д�����ݣ������Լ�ת�Ƶ�FIFO�У�����û��ʹ�ܴ��豸��
        ���ݻ���ʱ�����FIFO�У��������FIFO�з��͵����豸*/
        /* Polling��ʽд������*/
        if(SPI_SENDMOD_POLLING == pstWriteData->enMode)
        {
            s32State = SPI_POLL_Send((SPI_DEV_S *)pstWriteData,(BSP_VOID *)pSendData,u32Length);/*lint !e740*/
            if(BSP_OK != s32State)
            {
                if(BSP_OK != SPI_UnLock(enTemSpiId))
                {
                    return BSP_ERR_SPI_SEM_UNLOCK;
                }
                BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write. SPI_POLL_Send ERROR. \n",0,0,0,0,0,0);
                return s32State;
            }
        }
        /*DMA��ʽд�����ݲ�֧��*/
        else
        {
            if(BSP_OK != SPI_UnLock(enTemSpiId))
            {
                return BSP_ERR_SPI_SEM_UNLOCK;
            }
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write. Not Support Transmit mode. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_TMOD_INVALID;
        }

        /* ʹ�ܴ��豸�����ݿ�ʼ��FIFO���䵽���豸*/
        BSP_REG_WRITE(u32TemBaseAddr,SPI_SLAVE_EN_OFFSET,0x1 << enTemSpiCs);

        /* �ȴ�Transmit FIFO��*/
        while((0x4 != (SPI_STATUS & 0x4)) && (u32LoopNum < 20000))
        {
            u32LoopNum++;
        }

        if(20000 == u32LoopNum)
        {
            /* �쳣״̬�ϱ���ƽ̨*/
            if (NULL != g_pBSPRegExEventFunc)
            {
                stReportSpi.u16FrameNo = (BSP_U16)(*(volatile BSP_U32 *)BSP_SDA_PHY_SYSFRM_ADDR);
                stReportSpi.u16SubFrameNo = (BSP_U16)(*(volatile BSP_U32 *)BSP_SDA_PHY_SUBFRM_ADDR);
                /* SPIд��ʱ��ʱ*/
                stReportSpi.enReportSPI = EX_SPI_WRITE_TIMEOUT;
                (BSP_VOID)g_pBSPRegExEventFunc(EX_MODU_SPI, sizeof(EX_REPORT_SPI_S), &stReportSpi);
            }

            if(BSP_OK != SPI_UnLock(enTemSpiId))
            {
                return BSP_ERR_SPI_SEM_UNLOCK;
            }
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write. Bus not Free. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_RETRY_TIMEOUT;
        }
        u32LoopNum = 0;

        /* �ȴ����߿��У����߿���ʱ��ʾ���ݴ������*/
        while((0x0 != (SPI_STATUS & 0x1))&&(u32LoopNum < 20000))
        {
            u32LoopNum++;
        }

        if(20000 == u32LoopNum)
        {
            /* �쳣״̬�ϱ���ƽ̨*/
            if (NULL != g_pBSPRegExEventFunc)
            {
                stReportSpi.u16FrameNo = (BSP_U16)(*(volatile BSP_U32 *)BSP_SDA_PHY_SYSFRM_ADDR);
                stReportSpi.u16SubFrameNo = (BSP_U16)(*(volatile BSP_U32 *)BSP_SDA_PHY_SUBFRM_ADDR);
                /* SPIд��ʱ��ʱ*/
                stReportSpi.enReportSPI = EX_SPI_WRITE_TIMEOUT;
                (BSP_VOID)g_pBSPRegExEventFunc(EX_MODU_SPI, sizeof(EX_REPORT_SPI_S), &stReportSpi);
            }

            if(BSP_OK != SPI_UnLock(enTemSpiId))
            {
                return BSP_ERR_SPI_SEM_UNLOCK;
            }
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write. Bus not Free. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_RETRY_TIMEOUT;
        }

        /* �ͷ�SPI����*/
        if(BSP_OK != SPI_UnLock(enTemSpiId))
        {
            return BSP_ERR_SPI_SEM_UNLOCK;
        }

        return BSP_OK;

    }

    /*****************************************************************************
    * �� �� ��  : BSP_SPI_Read
    *
    * ��������  : ͨ��SPI��ȡ�豸����
    *
    * �������  : pstReadData  ��¼��SPI���ݴ����й���Ϣ�Ľṹ��ָ�룬��Ա����
    Ҫ��д��SPI�ţ�Ƭѡ�ţ�����ģʽ�ȡ�
    *             u32Length    �����յ����ݳ���
    *
    * �������  : pRecData     �洢���յ����ݻ�����ָ�롣
    *
    * �� �� ֵ  : BSP_OK    ���ճɹ�
    *             ERROR ����ʧ��
    *****************************************************************************/
    BSP_S32 BSP_SPI_Read(SPI_DATA_HANDLE_S *pstReadData,BSP_VOID *pRecData, BSP_U32 u32Length)
    {
        BSP_S32 s32State;
        BSP_U32 u32RegValue = 0;
        BSP_U32 u32LoopNum = 0;
        SPI_DEV_ID_E enTemSpiId = SPI_ID0;
        SPI_DEV_CS_E enTemSpiCs = SPI_DEV_CS0;
        SPI_SCPOL_E  enTemScpol = SPI_SCPOL_LOW;
        BSP_U32 u32TemBaseAddr = 0;
        SPI_DATA_LEN_E enDataLen;
        EX_REPORT_SPI_S stReportSpi;

        /*�����ж�*/
        if((NULL == pRecData) || (0 == u32Length)
            || (pstReadData->enCsID >= SPI_DEV_CS_MAX) || (pstReadData->enCsID < SPI_DEV_CS0)
            || (pstReadData->enSpiID >= SPI_ID_MAX) || (pstReadData->enSpiID < SPI_ID0)
            || (pstReadData->enMode >= SPI_SENDMOD_MAX)
            || (pstReadData->enMode < SPI_SENDMOD_POLLING)
            || (NULL == pstReadData->pvCmdData) || (pstReadData->u32length == 0))
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. Paramater ERROR. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_INVALID_PARA;
        }

        enTemSpiId = pstReadData->enSpiID;
        enTemSpiCs = pstReadData->enCsID;
        enTemScpol = stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs].enSpiScpol;
        enDataLen = stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs].enDataLen;
        u32TemBaseAddr = stSpiDev[enTemSpiId].u32SpiBaseAddr;

        /*���SPIû�г�ʼ�������ش���*/
        if(BSP_FALSE == g_bSpiInit)
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. BSP_FALSE == g_bSpiInit. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_MODULE_NOT_INITED;
        }

        /* SPI�������� */
        if (BSP_OK != SPI_Lock(enTemSpiId))
        {
            return BSP_ERR_SPI_SEM_LOCK;
        }

        /*��ȡ��ǰ��ƬƬѡ���ӵ��豸ռ��SPI����,����ǲ���Ҫ�������豸����Ҫ��������SPI*/

        s32State = SPI_SetSpiOwner((SPI_DEV_S *)pstReadData);/*lint !e740*/
        if(BSP_OK != s32State)
        {
            if(BSP_OK != SPI_UnLock(enTemSpiId))
            {
                return BSP_ERR_SPI_SEM_UNLOCK;
            }
            return s32State;
        }

        /*��ֹSlave*/
        BSP_REG_WRITE(u32TemBaseAddr,SPI_SLAVE_EN_OFFSET,0x0);

        /*��ֹMaster*/
        BSP_REG_WRITE(u32TemBaseAddr,SPI_EN_OFFSET,0x0);

        /* ���ý������ݵ���Ŀ*/
        BSP_REG_WRITE(u32TemBaseAddr,SPI_CTRL1_OFFSET,(u32Length - 1));

        switch(stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs].enSpiProt)
        {
            /*ʹ��NSMЭ��ʱ������MWCR��modλΪ����ģʽ*/
        case SPI_PROT_NSM:
            BSP_REG_READ(u32TemBaseAddr,SPI_MWCTRL_OFFSET,u32RegValue);
            u32RegValue &= (~0x2);
            BSP_REG_WRITE(u32TemBaseAddr,SPI_MWCTRL_OFFSET,u32RegValue);

            /*ʹ��Master�����������ݼĴ���д������ʱ�����ݻ��Լ�ת�Ƶ�FIFO��*/
            BSP_REG_WRITE(u32TemBaseAddr,SPI_EN_OFFSET,0x1);

            /* NSMЭ�飬��������ǰ����Ҫ����豸����������*/
            if(SPI_SENDMOD_POLLING == pstReadData->enMode)
            {
                /*lint -e740*/
                s32State = SPI_POLL_Send((SPI_DEV_S *)pstReadData,(BSP_VOID *)pstReadData->pvCmdData,\
                    pstReadData->u32length);
                if(BSP_OK != s32State)
                {
                    if(BSP_OK != SPI_UnLock(enTemSpiId))
                    {
                        return BSP_ERR_SPI_SEM_UNLOCK;
                    }
                    BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. SPI_POLL_Send ERROR. \n",0,0,0,0,0,0);
                    return s32State;
                }
            }
            else
            {
                if(BSP_OK != SPI_UnLock(enTemSpiId))
                {
                    return BSP_ERR_SPI_SEM_UNLOCK;
                }
                BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. DMA mode not Support. \n",0,0,0,0,0,0);
                return BSP_ERR_SPI_TMOD_INVALID;
            }

            break;

            /* ʹ��SPIЭ��*/
        case SPI_PROT_SPI:
            /* �޸�CTRL0��TMODλ�������ݴ���ģʽ����Ϊ��������*/
            BSP_REG_READ(u32TemBaseAddr,SPI_CTRL0_OFFSET,u32RegValue);

            u32RegValue &= (~0x3cf);
            u32RegValue = (u32RegValue | 0x40 | enDataLen | (enTemScpol << 0x7));
            BSP_REG_WRITE(u32TemBaseAddr,SPI_CTRL0_OFFSET,u32RegValue);

            /*ʹ��Master*/
            BSP_REG_WRITE(u32TemBaseAddr,SPI_EN_OFFSET,0x1);

            if(SPI_SENDMOD_POLLING == pstReadData->enMode)
            {
                s32State = SPI_POLL_Send((SPI_DEV_S *)pstReadData,(BSP_VOID *)pstReadData->pvCmdData,\
                    pstReadData->u32length);
                if(BSP_OK != s32State)
                {
                    if(BSP_OK != SPI_UnLock(enTemSpiId))
                    {
                        return BSP_ERR_SPI_SEM_UNLOCK;
                    }
                    BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. SPI_POLL_Send ERROR. \n",0,0,0,0,0,0);
                    return s32State;
                }
            }
            else
            {
                if(BSP_OK != SPI_UnLock(enTemSpiId))
                {
                    return BSP_ERR_SPI_SEM_UNLOCK;
                }
                BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. DMA mode not Support. \n",0,0,0,0,0,0);
                return BSP_ERR_SPI_TMOD_INVALID;
            }

            break;
            /*lint +e740*/

            /* �ݲ�֧��SSPЭ��*/
        case SPI_PROT_SSP:
        default:
            if(BSP_OK != SPI_UnLock(enTemSpiId))
            {
                return BSP_ERR_SPI_SEM_UNLOCK;
            }
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. Prot not support. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_PROT_INVALID;
        }

        /* ʹ�ܴ��豸�������ִ��䵽���豸�����豸���������ֺ󣬷������ݵ�SPI*/
        BSP_REG_WRITE(u32TemBaseAddr,SPI_SLAVE_EN_OFFSET,0x1<<enTemSpiCs);

        /* �ȴ�Transmit FIFO��*/
        while((0x4 != (SPI_STATUS & 0x4)) && (u32LoopNum < 20000))
        {
            u32LoopNum++;
        }

        if(20000 == u32LoopNum)
        {
            /* �쳣״̬�ϱ���ƽ̨*/
            if (NULL != g_pBSPRegExEventFunc)
            {
                stReportSpi.u16FrameNo = (BSP_U16)(*(volatile BSP_U32 *)BSP_SDA_PHY_SYSFRM_ADDR);
                stReportSpi.u16SubFrameNo = (BSP_U16)(*(volatile BSP_U32 *)BSP_SDA_PHY_SUBFRM_ADDR);
                /* SPI��ȡʱ��ʱ*/
                stReportSpi.enReportSPI = EX_SPI_READ_TIMEOUT;
                (BSP_VOID)g_pBSPRegExEventFunc(EX_MODU_SPI, sizeof(EX_REPORT_SPI_S), &stReportSpi);
            }
            if(BSP_OK != SPI_UnLock(enTemSpiId))
            {
                return BSP_ERR_SPI_SEM_UNLOCK;
            }
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write. Bus not Free. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_RETRY_TIMEOUT;
        }
        u32LoopNum = 0;

        /* �ȴ����߿��У����߿���ʱ��ʾ���ݴ������*/
        while((0x0 != (SPI_STATUS & 0x1))&&(u32LoopNum < 20000))
        {
            u32LoopNum++;
        }

        if(20000 == u32LoopNum)
        {
            /* �쳣״̬�ϱ���ƽ̨*/
            if (NULL != g_pBSPRegExEventFunc)
            {
                stReportSpi.u16FrameNo = (BSP_U16)(*(volatile BSP_U32 *)BSP_SDA_PHY_SYSFRM_ADDR);
                stReportSpi.u16SubFrameNo = (BSP_U16)(*(volatile BSP_U32 *)BSP_SDA_PHY_SUBFRM_ADDR);
                /* SPI��ȡʱ��ʱ*/
                stReportSpi.enReportSPI = EX_SPI_READ_TIMEOUT;
                (BSP_VOID)g_pBSPRegExEventFunc(EX_MODU_SPI, sizeof(EX_REPORT_SPI_S), &stReportSpi);
            }

            if(BSP_OK != SPI_UnLock(enTemSpiId))
            {
                return BSP_ERR_SPI_SEM_UNLOCK;
            }
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. Bus not Free. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_RETRY_TIMEOUT;
        }

        /* Polling��ʽ��������*/
        if(SPI_SENDMOD_POLLING == pstReadData->enMode)
        {
            s32State = SPI_POLL_Receive((SPI_DEV_S *)pstReadData,(BSP_VOID *)pRecData, u32Length);/*lint !e740*/
            if(BSP_OK != s32State)
            {
                if(BSP_OK != SPI_UnLock(enTemSpiId))
                {
                    return BSP_ERR_SPI_SEM_UNLOCK;
                }
                BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. SPI_POLL_Receive ERROR. \n",0,0,0,0,0,0);
                return s32State;
            }
        }
        /* ��ǰ���벻֧��DMA��ʽ��������*/
        else
        {
            if(BSP_OK != SPI_UnLock(enTemSpiId))
            {
                return BSP_ERR_SPI_SEM_UNLOCK;
            }
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. DMA mode not Support. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_TMOD_INVALID;
        }

        /* �ͷ�SPI����*/
        if(BSP_OK != SPI_UnLock(enTemSpiId))
        {
            return BSP_ERR_SPI_SEM_UNLOCK;
        }

        return BSP_OK;

    }

    /*****************************************************************************
    * �� �� ��  : BSP_SPI_GetAttr
    *
    * ��������  : ��ȡ��ǰSPI���õ�����
    *
    * �������  : enSpiId    Ҫ��ѯ��SPI�š�
    *
    * �������  : pstDevAttr ���SPI���ԵĽṹ��ָ�롣
    *
    * �� �� ֵ  : BSP_OK    ��ȡ���Գɹ�
    *             ERROR ��ȡ����ʧ��
    *****************************************************************************/
    BSP_S32 BSP_SPI_GetAttr(SPI_DEV_ID_E enSpiId, SPI_DEV_ATTR_S *pstDevAttr)
    {
        BSP_U16 u16Ctrl0Val;
        BSP_U16 u16BautRate;
        BSP_U32 u32TemBaseAddr = stSpiDev[enSpiId].u32SpiBaseAddr;

        /*�����ж�*/
        if((enSpiId < SPI_ID0)|| (enSpiId >= SPI_ID_MAX) || (NULL == pstDevAttr))
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. Paramater ERROR. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_INVALID_PARA;
        }

        /*���SPIû�г�ʼ�������ش���*/
        if(BSP_FALSE == g_bSpiInit)
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Read. BSP_FALSE == g_bSpiInit. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_MODULE_NOT_INITED;
        }

        if (BSP_OK != SPI_Lock(enSpiId))
        {
            BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write. BSP_OK != SPI_Lock. \n",0,0,0,0,0,0);
            return BSP_ERR_SPI_SEM_LOCK;
        }

        memset((BSP_VOID *)pstDevAttr, 0x0, sizeof(SPI_DEV_ATTR_S));

        /*��ȡSPI�Ĵ����е�ֵ*/
        BSP_REG16_READ(u32TemBaseAddr, SPI_CTRL0_OFFSET, u16Ctrl0Val);
        BSP_REG16_READ(u32TemBaseAddr, SPI_BAUD_OFFSET, u16BautRate);

        /*��SPI�����Դ洢��pstDevAttr��*/
        pstDevAttr->enDataLen = (SPI_DATA_LEN_E)(u16Ctrl0Val & 0xF);
        pstDevAttr->enCommandLen = (SPI_COMMAND_LEN_E)(u16Ctrl0Val >> SPI_COMM_SHIFT_BITS);
        pstDevAttr->enSpiProt = (SPI_PROT_E)((u16Ctrl0Val>>SPI_PROT_SHIFT_BITS) & 0x3);
        pstDevAttr->u16SpiBaud = u16BautRate;

        if(BSP_OK != SPI_UnLock(enSpiId))
        {
            return BSP_ERR_SPI_SEM_UNLOCK;
        }

        return BSP_OK;
    }

    /*****************************************************************************
    * �� �� ��  : SPI_SetSpiOwner
    *
    * ��������  : ���õ�ǰSPI������
    *
    * �������  : enSpiId Ҫ��ѯ��SPI�š�
    *
    * �������  : ��
    *
    * �� �� ֵ  : SPI��ǰʹ�õ�Ƭѡ��
    *****************************************************************************/
    BSP_S32 SPI_SetSpiOwner(SPI_DEV_S *pstSpiID)
    {
        BSP_U32 u32Ctrl0 = 0;
        SPI_DEV_ID_E enTemSpiId = pstSpiID->enSpiId;
        SPI_DEV_CS_E enTemSpiCs = pstSpiID->enSpiCs;
        BSP_U32 u32TemBaseAddr = stSpiDev[enTemSpiId].u32SpiBaseAddr;

        if(enTemSpiCs != (stSpiDev[enTemSpiId].enSpiOwner))
        {
            /* ���Ҫд��Ƭѡ֮ǰû��ʹ�ù����޷���ȡ�豸���ԣ����ش���*/
            if(BSP_FALSE == stSpiDev[enTemSpiId].abFlag[enTemSpiCs])
            {
                if(BSP_OK != SPI_UnLock(enTemSpiId))
                {
                    return BSP_ERR_SPI_SEM_UNLOCK;
                }
                BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SPI,"BSP_SPI_Write. SPI Configed Wrong, please Configure. \n",0,0,0,0,0,0);
                return BSP_ERR_SPI_ATTR_NOTSET;
            }

            /* ���Ҫд��Ƭѡ֮ǰ�ù�,�����ж�Ҫд��Ƭѡ���ӵ��豸�͵�ǰ��ʹ�õ�Ƭѡ����
            ���豸�����Ƿ�һ�£����һ�£�����Ҫ��������SPI,������������SPI*/
            if(0 != memcmp(&(stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs]),
                &(stSpiDev[enTemSpiId].stSpiConf[stSpiDev[enTemSpiId].enSpiOwner]),
                sizeof(SPI_DEV_ATTR_S)))
            {
                u32Ctrl0 = stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs].enCommandLen << SPI_COMM_SHIFT_BITS\
                    | stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs].enSpiProt << SPI_PROT_SHIFT_BITS \
                    | stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs].enDataLen;

                /*��ֹSPI���ݴ���*/
                BSP_REG_WRITE(u32TemBaseAddr, SPI_EN_OFFSET, 0x0);
                /*����ctrl0�Ĵ��������������ֳ��ȣ����ݿ��*/
                BSP_REG_WRITE(u32TemBaseAddr, SPI_CTRL0_OFFSET,u32Ctrl0);
                /*����SPI������*/
                BSP_REG_WRITE(u32TemBaseAddr, SPI_BAUD_OFFSET,stSpiDev[enTemSpiId].stSpiConf[enTemSpiCs].u16SpiBaud);
            }

            /*��������SPIʹ�õ�Ƭѡ��*/
            stSpiDev[enTemSpiId].enSpiOwner = enTemSpiCs;
        }

        return BSP_OK;
    }

    BSP_VOID BSP_ReportTest()
    {

        EX_REPORT_SPI_S stReportSpi;

        if (NULL != g_pBSPRegExEventFunc)
        {
            stReportSpi.u16FrameNo = (BSP_U16)(*(volatile BSP_U32 *)BSP_SDA_PHY_SYSFRM_ADDR);
            stReportSpi.u16SubFrameNo = (BSP_U16)(*(volatile BSP_U32 *)BSP_SDA_PHY_SUBFRM_ADDR);
            /* SPI��ȡʱ��ʱ*/
            stReportSpi.enReportSPI = EX_SPI_READ_TIMEOUT;
            logMsg("\r report spi read timeout!\n",0,0,0,0,0,0);
            (BSP_VOID)g_pBSPRegExEventFunc(EX_MODU_SPI, sizeof(EX_REPORT_SPI_S), &stReportSpi);
        }
    }

    BSP_VOID SPI_GetGlobalVariable()
    {
        BSP_S32 i = 0;
        BSP_S32 j = 0;

        printf(" ============================= g_bSpiInit =============================\n");
        printf("\t g_bSpiInit:        0x%08x\n", (int)g_bSpiInit);

        for(i = 0; i < SPI_ID_MAX; i++)
        {
            printf("\n ============================= stSpiDev[%d]=============================\n",i);

            printf("\t stSpiDev[%d].u32SpiBaseAddr:       0x%08x\n", i,(int)stSpiDev[i].u32SpiBaseAddr);
            printf("\t stSpiDev[%d].enSpiOwner:           0x%08x\n", i,(int)stSpiDev[i].enSpiOwner);
            printf("\t stSpiDev[%d].SpiSemId:             0x%08x\n", i,(int)stSpiDev[i].SpiSemId);

            for(j=0; j<SPI_DEV_CS_MAX; j++)
            {
                printf("\t stSpiDev[%d].abFlag[%d]:            0x%08x\n", i,j,(int)stSpiDev[i].abFlag[j]);
            }

            for(j=0; j<SPI_DEV_CS_MAX; j++)
            {
                if(stSpiDev[i].abFlag[j])
                {
                    printf("\n ====================== stSpiDev[%d].stSpiConf[%d] ======================\n",i,j);
                    printf("\t stSpiDev[%d].stSpiConf[%d].enCommandLen:       0x%08x\n",\
                        i,j,(int)stSpiDev[i].stSpiConf[j].enCommandLen);
                    printf("\t stSpiDev[%d].stSpiConf[%d].enDataLen:          0x%08x\n",\
                        i,j,(int)stSpiDev[i].stSpiConf[j].enDataLen);
                    printf("\t stSpiDev[%d].stSpiConf[%d].enSpiProt:          0x%08x\n",\
                        i,j,(int)stSpiDev[i].stSpiConf[j].enSpiProt);
                    printf("\t stSpiDev[%d].stSpiConf[%d].u16SpiBaud:         0x%08x\n",\
                        i,j,(int)stSpiDev[i].stSpiConf[j].u16SpiBaud);
                }
            }
        }
        printf("\n ======================================================================\n");
        return ;
    }

    BSP_VOID SPI_GetRegistValue()
    {
        BSP_S32 i = 0;

        printf(" ================== Register Value =====================\n");

        for(i = 0; i < SPI_ID_MAX; i++)
        {
            printf("\t SPI[%d] control0  register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_CTRL0_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_CTRL0_OFFSET));
            printf("\t SPI[%d] control1  register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_CTRL1_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_CTRL1_OFFSET));
            printf("\t SPI[%d] Enable    register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_EN_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_EN_OFFSET));
            printf("\t SPI[%d] Microwire register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_MWCTRL_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_MWCTRL_OFFSET));
            printf("\t SPI[%d] slaveEn   register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_SLAVE_EN_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_SLAVE_EN_OFFSET));
            printf("\t SPI[%d] pautslect register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_BAUD_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_BAUD_OFFSET));
            printf("\t SPI[%d] Tx ftlr   register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_TXFTL_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_TXFTL_OFFSET));
            printf("\t SPI[%d] Rx ftlr   register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_RXFTL_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_RXFTL_OFFSET));
            printf("\t SPI[%d] Tx fifo   register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_TXFL_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_TXFL_OFFSET));
            printf("\t SPI[%d] Rx fifo   register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_RXFL_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_RXFL_OFFSET));
            printf("\t SPI[%d] state     register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_STATUS_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_STATUS_OFFSET));
            printf("\t SPI[%d] mask int  register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_INT_MASK_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_INT_MASK_OFFSET));
            printf("\t SPI[%d] int stat  register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_INT_STATUS_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_INT_STATUS_OFFSET));
            printf("\t SPI[%d] rawintstu register:        0x%x = 0x%x\n", i, (int)(stSpiDev[i].u32SpiBaseAddr + SPI_RAW_INT_STATUS_OFFSET),
                BSP_REG(stSpiDev[i].u32SpiBaseAddr, SPI_RAW_INT_STATUS_OFFSET));
            printf("\n");

        }

        printf(" =====================================================\n\n");

        return ;
    }
#endif




    //�������ֹSLIC�ж�
    void EnableSlicIrq( int bEnable )
    {
        if( bEnable )
        {
            SLIC_GPIO_REG_SETBIT(g_gpioBase, HI_GPIO_INTEN, GPIO_23);
        }
        else
        {
            SLIC_GPIO_REG_CLRBIT(g_gpioBase, HI_GPIO_INTEN, GPIO_23);
        }
    }

    //add new interface

    INT32 HiSpiInit(UINT32 spiNo, UINT8 dataWidth, UINT8 clk, UINT8 baud)
    {
        UINT8 ucDataWidth = 0;
        UINT8 ucSCPOL = 0;
        UINT8 ucSCPH = 0;

        ucDataWidth = dataWidth - 1;
        ucSCPOL = (clk & 0x02) >> 1;
        ucSCPH = clk & 0x01;

        if ((0 != spiNo) && (1 != spiNo))
        {
            return ERROR;
        }
        #if 0

        /* PMUʹ��SPI0 CS0 */
        if(0 == spiNo)
        {
            BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x988, SSP0_CTRL, 1, 1);     // IO����ΪSSP0
            BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x944, SSP0_WIRE_4, 2, 3);  // ʹ��SSP0
        }
        else
        {
            /* ʹ��SPI1_CTRL */
            BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x988, SSP1_CTRL, 1, 1);     // IO����ΪSSP1
            BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x944, SSP1_WIRE_4, 2, 3);  // ʹ��SSP1
        }
        #endif

        spiBase[0] = (unsigned long)ioremap(spiBase[0], ECS_SPI0_SIZE);
        spiBase[1] = (unsigned long)ioremap(spiBase[1], ECS_SPI1_SIZE);

        /* ��ֹSPI Slave*/
        OUTREG32(SPI_SLAVE_EN(spiNo), 0);

        /* ��ֹSPI Master*/
        OUTREG32(SPI_EN(spiNo), 0);

        /* ����ctrl0�Ĵ����������ֳ���Ϊ1�����ݿ��Ϊ8,�����ش���,�͵�ƽ��Ч */
        OUTREG32(SPI_CTRL0(spiNo), (ucDataWidth<<SPI_CTRL0_DFS_BITPOS)    \
            | (ucSCPH<<SPI_CTRL0_SCPH_BITPOS)    \
            | (ucSCPOL<<SPI_CTRL0_SCPOL_BITPOS)   \
            | (0 << SPI_CTRL0_FRF_BITPOS)   \
            | (0x00<<SPI_CFS_BITPOS));

        /* ����SPI������ΪSSI CLK��1/24����48/24=2MHz */
        OUTREG32(SPI_BAUD(spiNo), baud);

        /*��ֹ�����ж��ź�*/
        OUTREG32(SPI_IMR(spiNo), 0);

        /*����DMA����*/
        OUTREG32(SPI_DMAC(spiNo), 0);

        return OK;
    }

#define SPI_MAX_DELAY_TIMES 0x10000
#define SPI_CS_DEV          (1<<1)     /* CS1 for EEPROM/SFlash */
#define SPI_CS_PMU          (1<<0)     /* CS0,for eMMC/MMC/SD */

    INT32 HiSpiRecv (UINT32 spiNo, UINT32 cs, UINT8* prevData, UINT32 recvSize,UINT8* psendData,UINT32 sendSize )
    {
        UINT8 *pRh;
        UINT8 *pSh;
        UINT32  i;
        UINT32 ulLoop = SPI_MAX_DELAY_TIMES;

        if (((0 != spiNo) && (1 != spiNo))
            || (SPI_CS_PMU != cs && SPI_CS_DEV != cs)
            || (NULL == psendData) || (NULL == prevData) || (0 == recvSize) || (0 == sendSize))
        {
            return ERROR;
        }

        pRh = prevData;
        pSh = psendData;

        /* ��ֹSPI Slave*/
        OUTREG32(SPI_SLAVE_EN(spiNo), 0);

        /* ��ֹSPI Master*/
        OUTREG32(SPI_EN(spiNo), 0);

        /* ���ó�EEPROM��ģʽ */
        SETBITVALUE32(SPI_CTRL0(spiNo), SPI_CTRL0_TMOD_BITMASK, SPI_CTRL0_TMOD_SEND_RECV);

        /* ���ý������ݵ���Ŀ*/
        OUTREG32(SPI_CTRL1(spiNo),(recvSize-1));

        /*ʹ��SPI Master*/
        OUTREG32(SPI_EN(spiNo), 1);

        /*ʹ��SPI Slave*/
        OUTREG32(SPI_SLAVE_EN(spiNo), cs);

        /* �������� */
        for(i = 0; i < sendSize; i++)
        {
            /* �ȴ�����FIFO���� */
            while(!(INREG32(SLIC_SPI_STATUS(spiNo)) & SPI_STATUS_TXNOTFULL)
                && (0 != --ulLoop))
            {
            }

            if(0 == ulLoop)
            {
                return ERROR;
            }

            OUTREG32(SPI_DR(spiNo), *pSh++);
        }

        /*������FIFO�е�����ȫ������*/
        while(!(INREG32(SLIC_SPI_STATUS(spiNo)) & SPI_STATUS_TXEMPTY)
            && (0 != --ulLoop))
        {
        }

        if(0 == ulLoop)
        {
            return ERROR;
        }

        /* �������� */
        for(i = 0; i < recvSize; i++)
        {
            ulLoop = SPI_MAX_DELAY_TIMES;
            /* �ȴ���ȡ������ */
            while(!(INREG32(SLIC_SPI_STATUS(spiNo)) & SPI_STATUS_RXNOTEMPTY)
                && (0 != --ulLoop))
            {
            }

            if(0 == ulLoop)
            {
                return ERROR;
            }

            *pRh++ = (UINT8)INREG32(SPI_DR(spiNo));
        }

        return OK;
    }


    INT32 HiSpiSend (UINT32 spiNo, UINT32 cs, UINT8* pData, UINT32 ulLen)
    {
        UINT8 *pSh;
        UINT32  i;
        UINT32 ulLoop = SPI_MAX_DELAY_TIMES;
        UINT32 ulVal;

        if (((0 != spiNo) && (1 != spiNo))
            || (SPI_CS_PMU != cs && SPI_CS_DEV != cs)
            || (NULL == pData) || (0 == ulLen))
        {
            return ERROR;
        }

        pSh = (UINT8*)pData;

        /* ��ֹSPI Slave*/
        OUTREG32(SPI_SLAVE_EN(spiNo), 0);

        /* ��ֹSPI Master*/
        OUTREG32(SPI_EN(spiNo), 0);

        /* ���óɷ���ģʽ */
        SETBITVALUE32(SPI_CTRL0(spiNo), SPI_CTRL0_TMOD_BITMASK, SPI_CTRL0_TMOD_SEND);

        /*ʹ��SPI Master*/
        OUTREG32(SPI_EN(spiNo), 1);

        /*ʹ��SPI Slave*/
        OUTREG32(SPI_SLAVE_EN(spiNo), cs);

        /* �������� */
        for(i = 0; i < ulLen; i++)
        {
            /* �ȴ�����FIFO���� */
            while(!(INREG32(SLIC_SPI_STATUS(spiNo)) & SPI_STATUS_TXNOTFULL)
                && (0 != --ulLoop))
            {
            }

            if(0 == ulLoop)
            {
                return ERROR;
            }
            OUTREG32(SPI_DR(spiNo), *pSh++);
        }

        /*������FIFO�е�����ȫ������,�Ҳ�BUSY*/
        ulLoop = SPI_MAX_DELAY_TIMES;
        ulVal = INREG32(SLIC_SPI_STATUS(spiNo));
        while(((!(ulVal & SPI_STATUS_TXEMPTY)) || (ulVal & SPI_STATUS_BUSY))
            && (0 != --ulLoop))
        {
            ulVal = INREG32(SLIC_SPI_STATUS(spiNo));
        }

        if(0 == ulLoop)
        {
            return ERROR;
        }

        return OK;
    }

    void SlicPclkFsyncInit(void)
    {
        printk("enter SlicPclkFsyncInit\n");

        //PCM�ܽŸ���
        //BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x988, 7, 2, 0x1);     // [8:7] = 01b
        //BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x988, 12, 2, 0x0);     // [13:12] = 00b

        //��SIO����ʱ���ſ�
        BSP_REG_WRITE(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x0c, 0x10);  //CRG_CTRL3[4]ʱ��ʹ��

        //�ر�SIO_SOC��λ��ʱ��XCLK
        BSP_REG_WRITE(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x28, 0x2000);  //CRG_CTRL10[13]ʱ�ӹر�

        //����SIOΪ��ģʽ
        BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x30, 4, 3, 0x6);     // [6:5:4] = 110b

        //ʱ�ӷ�Ƶ 122880k/240/64=8k bit0:15=240 bit16:27=64
        //FSYNC���ó�8K PCLKΪ512K
        BSP_REG_WRITE(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x44, 0x004000F0);

        //����PCM�ӿڹܽſ���Ϊmasterģʽ
        BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x0940, 20, 1, 1);
    }

    void SlicPcmSlaveModeEnable(void)
    {
        //����PCMΪSlaveģʽ
        BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x0940, 20, 1, 0);
    }

    void SlicPcmMasterModeEnable(void)
    {
        //����PCMΪMasterģʽ
        BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x0940, 20, 1, 1);
    }

    void ClosePeripheralClock(BSP_U8 ucPeripheralType)
    {
        switch (ucPeripheralType)
        {
            case EN_PERIPHERAL_USB:
            {
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x10, 27, 1, 1);       
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x10, 13, 1, 1);
                break;
            }
            case EN_PERIPHERAL_HSIC:
            {
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x04, 13, 1, 1);            
                break;
            }
            case EN_PERIPHERAL_MAC:
            {
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x04, 10, 1, 1);
                break;
            }
            case EN_PERIPHERAL_SIO:
            {
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x10, 4, 1, 1);
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x28, 13, 1, 1);
                break;
            }
            default:
            {
                printk("invalid para %d\n", ucPeripheralType);
                break;
            }
        }
    }

    void OpenPeripheralClock(BSP_U8 ucPeripheralType)
    {
        switch (ucPeripheralType)
        {
            case EN_PERIPHERAL_USB:
            {
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x0C, 27, 1, 1);       
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x0C, 13, 1, 1);
                break;
            }
            case EN_PERIPHERAL_HSIC:
            {
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x00, 13, 1, 1);            
                break;
            }
            case EN_PERIPHERAL_MAC:
            {
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x00, 10, 1, 1);
                break;
            }
            case EN_PERIPHERAL_SIO:
            {
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x0C, 4, 1, 1);
                BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x24, 13, 1, 1);
                break;
            }
            default:
            {
                printk("invalid para %d\n", ucPeripheralType);
                break;
            }
        }
    }

    /*���Խӿ�*/
    void DebugWriteHiReg(BSP_U32 base, BSP_U32 reg, BSP_U32 data)
    {
        BSP_REG_WRITE(IO_ADDRESS(base), reg, data);
    }

    void DebugSetHiRegBits(BSP_U32 base, BSP_U32 reg, BSP_U32 pos, BSP_U32 bits, BSP_U32 val)
    {
        BSP_REG_SETBITS(IO_ADDRESS(base), reg, pos, bits, val);
    }

    BSP_U32 DebugReadHiReg(BSP_U32 base, BSP_U32 reg, BSP_U32 result)
    {
        return BSP_REG_READ(IO_ADDRESS(base), reg, result);
    }
    /*end*/    

    UINT32 DebugReadSlicPclkFsync(void)
    {
        UINT32 ulReg = 0;
        return BSP_REG_READ(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x44, ulReg);
    }

    void SlicSioInit(void)
    {
        BSP_U32 ulRegVal;
        BSP_U32 ulBitVal = 0;

        printk("enter SlicSioInit\n");

        g_ulSioBaseAddr = (unsigned long)ioremap(SIO_BASE_ADDR_PHY, SIO_SIZE);

        printk("g_ulSioBaseAddr=0x%x\n", g_ulSioBaseAddr);

        BSP_REG_WRITE(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x230, 0x0);
        BSP_REG_WRITE(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x234, 0x1319ec0);
        BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x238, 0, 1, 1);
        BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x238, 0, 1, 0);

        ulBitVal = BSP_REG_GETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x238, 31, 1);
        while(1 != ulBitVal)
        {
            ulBitVal = BSP_REG_GETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x238, 31, 1);
        }

        BSP_REG_WRITE(SIO_CTRL_CLR, 0, 0xffff);

        BSP_REG_WRITE(SIO_INTR_CLR, 0, 0x3f);

        BSP_REG_WRITE(SIO_CTRL_SET, 0, 0x8000);

        msleep(1);

        //��SIO����ʱ���ſ�
        BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x18, 29, 1, 1);

        //����SIOΪ��ģʽ
        BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x40c, 3, 1, 1);

        //ʱ�ӷ�Ƶ 122880k/60/256=8k bit0:15=60 bit16:27=256
        //BSP_REG_WRITE(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x100, 0x0100003C);

        //ʱ�ӷ�Ƶ 120832k/59/256=8k bit0:15=59 bit16:27=256
        BSP_REG_WRITE(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x100, 0x0100003B);

        //����PCM�ӿڹܽſ���Ϊmasterģʽ
        //BSP_REG_SETBITS(IO_ADDRESS(INTEGRATOR_SC_BASE), 0x0940, 20, 1, 1);

        /*дSIO_INTR_CLR 0xffff��λSIO����ֹ���䡢��ֹ�ж�*/
        BSP_REG_WRITE(SIO_CTRL_CLR, 0, 0xffff);

        msleep(1);

        printk("After reset FIFO:%d\n", BSP_REG_READ(SIO_CTRL_RX_STA, 0, ulRegVal));

        /*��������SIO�ж�*/
        BSP_REG_WRITE(SIO_INTR_MASK, 0, 0xffffffff);

        /*�������SIO�ж�*/
        BSP_REG_WRITE(SIO_INTR_CLR, 0, 0x3f);

        /*�⸴λ������ˮ��Tx-8(0.5)��RX-8(0.5)��ʹ���ж�*/
        BSP_REG_WRITE(SIO_CTRL_SET, 0, 0x8088);

        /*����ΪPCMģʽ*/
        BSP_REG_WRITE(SIO_MODE, 0, 0x1);

        /*����Ϊ���͡�����16bitλ��*/
        BSP_REG_WRITE(SIO_DATA_WIDTH_SET, 0, 0x9);

        /*���÷�����չ��ֹ*/
        BSP_REG_WRITE(SIO_SIGNED_EXT, 0, 0);

        /*���жϻص������ǿգ�����ж����Σ��ҽ��жϻص�����*/
        if(1/*BSP_NULL != pfIntHandleFunc*/)
        {
            /*��enIntMaskȡ�������ж�����*/
            BSP_REG_WRITE(SIO_INTR_MASK, 0, ~(0x14UL));
        }

        /*ʹ��SIO���ա�����*/
        BSP_REG_WRITE(SIO_CTRL_SET, 0, 0x3000);

        msleep(1);

        printk("After en rx_tx FIFO:%d\n", BSP_REG_READ(SIO_CTRL_RX_STA, 0, ulRegVal));
    }

    INT32 SlicSpiInit(void)
    {
        INT32 lRet = 0;
        unsigned long flags;

        if(BSP_TRUE == g_bSpiInit)
        {
            return OK;
        }

        SlicPclkFsyncInit();
        msleep(100);

        spin_lock_irqsave(&slic_lock, flags);
        //lRet = HiSpiInit(1, 8, 0x03, 48);
        //SPI��Ƶ�޸�Ϊ256K
        lRet = HiSpiInit(0, 8, 0x03, 6);
        spin_unlock_irqrestore(&slic_lock, flags);

        if(OK == lRet)
        {
            g_bSpiInit = BSP_TRUE;
        }

        return lRet;
    }

    UINT8 SlicSpiRecv(void)
    {
        UINT8 rcvdata = 0;
        UINT8 snddata = 0;

        HiSpiRecv(0, 0x01, &rcvdata, 1, &snddata, 1);
        return rcvdata;
    }

    void SlicSpiSend(UINT8 ucSndByte)
    {
        HiSpiSend(0, 0x01, &ucSndByte, 1);
    }


    UINT8 SlicReadReg(UINT8 ucReg)
    {
        UINT8 ucRegVal = 0;
        unsigned long flags;

        if(BSP_FALSE == g_bSpiInit)
        {
            printk("slic not init\n");
            return ERROR;
        }

        spin_lock_irqsave(&slic_lock, flags);

        SlicSpiSend(0x60);
        SlicSpiSend(ucReg);
        ucRegVal = SlicSpiRecv();

        spin_unlock_irqrestore(&slic_lock, flags);

        return ucRegVal;
    }


    void SlicWriteReg(UINT8 ucReg, UINT8 ucVal)
    {
        unsigned long flags;

        if(BSP_FALSE == g_bSpiInit)
        {
            printk("slic not init\n");
            return;
        }

        spin_lock_irqsave(&slic_lock, flags);

        SlicSpiSend(0x20);
        SlicSpiSend(ucReg);
        SlicSpiSend(ucVal);

        spin_unlock_irqrestore(&slic_lock, flags);
    }

#define MAX_RAM_R_WAIT_TIMES 1000
    UINT32 SlicReadRam(UINT16 usRam)
    {
        UINT8 ucHighAddr = 0;
        UINT8 ucLowAddr = 0;
        UINT8 ucData0 = 0;
        UINT8 ucData1 = 0;
        UINT8 ucData2 = 0;
        UINT8 ucData3 = 0;
        UINT32 ulData = 0;
        UINT32 i = 0;
        unsigned long flags;

        if(BSP_FALSE == g_bSpiInit)
        {
            printk("slic not init\n");
            return ERROR;
        }

        spin_lock_irqsave(&slic_lock, flags);

        ucHighAddr = (usRam & 0x700) >> 3;
        ucLowAddr = usRam & 0xFF;

        SlicWriteReg(RAM_ADDR_HI, ucHighAddr);
        SlicWriteReg(RAM_ADDR_LO, ucLowAddr);

        for(i = 0; i < MAX_RAM_R_WAIT_TIMES; i++)
        {
            if(0 == (0x1 & SlicReadReg(RAMSTAT)))
            {
                break;
            }
        }

        if(MAX_RAM_R_WAIT_TIMES == i)
        {
            printk("SlicReadRam time out error.\n");
            spin_unlock_irqrestore(&slic_lock, flags);
            return -1;
        }

        ucData0 = SlicReadReg(RAM_DATA_B0);
        ucData1 = SlicReadReg(RAM_DATA_B1);
        ucData2 = SlicReadReg(RAM_DATA_B2);
        ucData3 = SlicReadReg(RAM_DATA_B3);

        ulData = (((UINT32)ucData0 >> 3) & 0x1F)
            | (((UINT32)ucData1 << 5) & 0x1FE0)
            | (((UINT32)ucData2 << 13) & 0x1FE000)
            | (((UINT32)ucData3 << 21) & 0x1FE00000);

        spin_unlock_irqrestore(&slic_lock, flags);

        return ulData;
    }

#define MAX_RAM_W_WAIT_TIMES 1000
    void SlicWriteRam(UINT16 usRam, UINT32 ulData)
    {
        UINT8 ucHighAddr = 0;
        UINT8 ucLowAddr = 0;
        UINT8 ucData0 = 0;
        UINT8 ucData1 = 0;
        UINT8 ucData2 = 0;
        UINT8 ucData3 = 0;
        UINT32 i = 0;
        unsigned long flags;

        if(BSP_FALSE == g_bSpiInit)
        {
            printk("slic not init\n");
            return;
        }

        spin_lock_irqsave(&slic_lock, flags);

        ucHighAddr = (usRam & 0x700) >> 3;
        ucLowAddr = usRam & 0xFF;

        ucData0 = (ulData << 3) & 0xF8;
        ucData1 = (ulData >> 5) & 0xFF;
        ucData2 = (ulData >> 13) & 0xFF;
        ucData3 = (ulData >> 21) & 0xFF;

        SlicWriteReg(RAM_ADDR_HI, ucHighAddr);

        SlicWriteReg(RAM_DATA_B0, ucData0);
        SlicWriteReg(RAM_DATA_B1, ucData1);
        SlicWriteReg(RAM_DATA_B2, ucData2);
        SlicWriteReg(RAM_DATA_B3, ucData3);

        SlicWriteReg(RAM_ADDR_LO, ucLowAddr);

        for(i = 0; i < MAX_RAM_W_WAIT_TIMES; i++)
        {
            if(0 == (0x1 & SlicReadReg(RAMSTAT)))
            {
                spin_unlock_irqrestore(&slic_lock, flags);
                return;
            }
        }

        if(MAX_RAM_W_WAIT_TIMES == i)
        {
            printk("SlicWriteRam time out error.\n");
        }

        spin_unlock_irqrestore(&slic_lock, flags);
        return;
    }


    INT32 SlicSetUserMode(BOOL on)
    {
        UINT8 data = 0;
        unsigned long flags;

        if(BSP_FALSE == g_bSpiInit)
        {
            printk("slic not init\n");
            return ERROR;
        }

        spin_lock_irqsave(&slic_lock, flags);

        if (on == TRUE)
        {
            if(g_lUserModeStatus < 2)
            {
                g_lUserModeStatus++;
            }
        }
        else
        {
            if (g_lUserModeStatus > 0)
            {
                g_lUserModeStatus--;
            }

            if (g_lUserModeStatus != 0)
            {
                printk("SlicSetUserMode not match error.\n");
                spin_unlock_irqrestore(&slic_lock, flags);
                return -1;
            }
        }

        data = SlicReadReg(USERMODE_ENABLE);
        if (((data & 1) != 0) == on)
        {
            spin_unlock_irqrestore(&slic_lock, flags);
            return 0;
        }

        SlicWriteReg(USERMODE_ENABLE, 2);
        SlicWriteReg(USERMODE_ENABLE, 8);
        SlicWriteReg(USERMODE_ENABLE, 0xe);
        SlicWriteReg(USERMODE_ENABLE, 0);

        spin_unlock_irqrestore(&slic_lock, flags);

        return 0;
    }

    //end

#ifdef E5172_SLIC_WAKEUP_DEBUG
/* GPIO�ܽŸ������üĴ��� */
#define CS_BASE_ADDR        0x90000000
#define CS_SIZE             0x1000
#define IOSHARE4_OFF_ADDR   0x0908

/* GPIO�ܽŸ��ÿ���λ */
#define GPIO_CTRL0_BIT      11
#endif    

INT32 HiInitIrq(void)
{
    if( 0==g_gpioBase )
    {
        g_gpioBase = (unsigned long)ioremap(0x90006000,  0x1000);
    }

    SLIC_GPIO_REG_CLRBIT(g_gpioBase, HI_GPIO_SWPORT_DDR, 22);     //GPIO_SWPORT_DDR ����GPIOΪ����
    SLIC_GPIO_REG_SETBIT(g_gpioBase, HI_GPIO_INTEN, 22);     // HI_GPIO_INTEN �����ж�ʹ��
    SLIC_GPIO_REG_CLRBIT(g_gpioBase, HI_GPIO_INTMASK, 22);     // HI_GPIO_INTMASK �����ж�����
    SLIC_GPIO_REG_SETBIT(g_gpioBase, HI_GPIO_INTTYPE_LEVEL, 22);     // HI_GPIO_INTTYPE_LEVEL ����Ϊ��ƽ����
    SLIC_GPIO_REG_CLRBIT(g_gpioBase, HI_GPIO_INT_PLOARITY, 22);     // HI_GPIO_INT_PLOARITY����Ϊ�͵�ƽ

    return 0;
}

void EnSlicInt(void)
{
    SLIC_GPIO_REG_CLRBIT(g_gpioBase, HI_GPIO_INTMASK, GPIO_23);     // HI_GPIO_INTMASK �����ж�����
}

void DisSlicInt(void)
{
    SLIC_GPIO_REG_SETBIT(g_gpioBase, HI_GPIO_INTMASK, GPIO_23);     // HI_GPIO_INTMASK �����ж�����
}


#ifdef __cplusplus
}
#endif

