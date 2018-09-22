#include <linux/kernel.h>
#include <linux/string.h>
#include <asm/io.h>
#include "DrvInterface.h"
#include "drv_dma.h"
#include "ucom_comm.h"
#include "bsp_memmap.h"


#ifdef __cplusplus
extern "C" {
#endif

DMA_CXISR_STRU g_astDmaCxIntIsr[DMA_MAX_CHANNEL_NUM];
BSP_U32 g_ulEdmaBaseAddr = 0;


BSP_VOID DRV_DMA_Init(BSP_VOID)
{

#if 0
    /*��ʼ��g_astDmaCxIntIsrΪȫ��*/
    DMA_CXISR_STRU  *pstDmaCxIsr = DMA_GetCxIsrPtr();
    memset(pstDmaCxIsr, 0, sizeof(DMA_CXISR_STRU)*DMA_MAX_CHANNEL_NUM);
#endif

    //debug
    printk("enter DRV_DMA_Init\n");

    /*ѡ��EDMA��ΪSIO��DMA*/
    //BSP_REG_SETBITS(IO_ADDRESS(SC_DMA_SEL_CTRL_ADDR), 0x0, 2, 1, 1);

    //debug
    printk("1\n");

    g_ulEdmaBaseAddr = (unsigned long)ioremap(DMA_BASE_ADDR_PHY, DMA_SIZE);

    //debug
    printk("2, g_ulSioBaseAddr=0x%x\n", g_ulEdmaBaseAddr);

    /*����д0�����¼Ĵ���Ĭ������HIFI DMA�ж�*/
    BSP_REG_WRITE(DMA_INT_ERR1_MASK_HIFI, 0, 0);
    BSP_REG_WRITE(DMA_INT_ERR2_MASK_HIFI, 0, 0);
    BSP_REG_WRITE(DMA_INT_ERR3_MASK_HIFI, 0, 0);
    BSP_REG_WRITE(DMA_INT_TC1_MASK_HIFI, 0, 0);
    BSP_REG_WRITE(DMA_INT_TC2_MASK_HIFI, 0, 0);

    /*ע��DMA ISR*/
    //add code

    /*ʹ��EDMA�ж�*/
    //add code

    //debug
    printk("out DRV_DMA_Init\n");
}


BSP_VOID DRV_DMA_STOP(BSP_U16 usChNo)
{
    DMA_CXISR_STRU  *pstDmaCxIsr = DMA_GetCxIsrPtr();

    /*д0��DMA_CX_CONFIG(ulChNo)bit0ֹͣ��ӦDMAͨ��*/
    BSP_REG_SETBITS(DMA_CX_CONFIG((BSP_U32)usChNo), 0x0, UCOM_BIT0, 1, 0);

    /*����д(usChNo��ӦbitΪ0)�����¼Ĵ�������HIFI��ӦDMAͨ���ж�*/
    BSP_REG_SETBITS(DMA_INT_ERR1_MASK_HIFI, 0x0, usChNo, 1, 0);
    BSP_REG_SETBITS(DMA_INT_ERR2_MASK_HIFI, 0x0, usChNo, 1, 0);
    BSP_REG_SETBITS(DMA_INT_ERR3_MASK_HIFI, 0x0, usChNo, 1, 0);
    BSP_REG_SETBITS(DMA_INT_TC1_MASK_HIFI, 0x0, usChNo, 1, 0);
    BSP_REG_SETBITS(DMA_INT_TC2_MASK_HIFI, 0x0, usChNo, 1, 0);

    /*���ȫ�ֱ����ж�Ӧͨ����������*/
    memset(&pstDmaCxIsr[usChNo], 0, sizeof(DMA_CXISR_STRU));
}

BSP_U32 DMA_StartWithCfg(
    BSP_U16 usChannelNo,
    DMA_CXCFG_STRU *pstCfg,
    DMA_INT_FUNC pfIntHandleFunc,
    BSP_U32 ulPara)
{
    BSP_U32 ulChannelMask = (0x1L << usChannelNo);
#if 0
    DMA_CXISR_STRU *pstCxIsr = DMA_GetCxIsrPtr();
#endif

    //debug
    printk("enter DMA_StartWithCfg\n");

    /*д0��DMA_CX_CONFIG(usChannelNo)bit0��ֹͨ��*/
    BSP_REG_SETBITS(DMA_CX_CONFIG((BSP_U32)usChannelNo),
                    0,
                    UCOM_BIT0,
                    1,
                    0);

    /*дͨ��X��ǰһά����ʣ���byte��,[15,0]*/
    BSP_REG_SETBITS(DMA_CX_CNT0((BSP_U32)usChannelNo),
                    0x0,
                    UCOM_BIT0,
                    16,
                    pstCfg->usACount);

    /*дͨ��X��Դ��ַ[31,0]��Ŀ�ĵ�ַ[31,0]*/
    BSP_REG_WRITE(DMA_CX_DES_ADDR(usChannelNo), 0, pstCfg->ulDstAddr);
    BSP_REG_WRITE(DMA_CX_SRC_ADDR(usChannelNo), 0, pstCfg->ulSrcAddr);

    /*дͨ��X�������ַ����*/
    BSP_REG_WRITE(DMA_CX_LLI(usChannelNo), 0, pstCfg->ulLli);

    /*���ͨ��X�ĸ����ж�״̬*/
    BSP_REG_WRITE(DMA_INT_TC1_RAW, 0, ulChannelMask);
    BSP_REG_WRITE(DMA_INT_TC2_RAW, 0, ulChannelMask);
    BSP_REG_WRITE(DMA_INT_ERR1_RAW, 0, ulChannelMask);
    BSP_REG_WRITE(DMA_INT_ERR2_RAW, 0, ulChannelMask);
    BSP_REG_WRITE(DMA_INT_ERR3_RAW, 0, ulChannelMask);

    /*���ص������ǿգ��򱣴��ֵ*/
    if(1/*BSP_NULL != pfIntHandleFunc*/)
    {

#if 0
        pstCxIsr[usChannelNo].pfFunc = pfIntHandleFunc;
        pstCxIsr[usChannelNo].ulPara = ulPara;
#endif

        /*����д(usChannelNo��ӦbitΪ1)�����¼Ĵ�����HIFI��Ӧ��DMAͨ���ж�����*/
        BSP_REG_SETBITS(DMA_INT_ERR1_MASK_HIFI, 0x0, usChannelNo, 1, 1);
        BSP_REG_SETBITS(DMA_INT_ERR2_MASK_HIFI, 0x0, usChannelNo, 1, 1);
        BSP_REG_SETBITS(DMA_INT_ERR3_MASK_HIFI, 0x0, usChannelNo, 1, 1);
        BSP_REG_SETBITS(DMA_INT_TC1_MASK_HIFI, 0x0, usChannelNo, 1, 1);
        BSP_REG_SETBITS(DMA_INT_TC2_MASK_HIFI, 0x0, usChannelNo, 1, 1);
    }

    /*дͨ��X������*/
    BSP_REG_WRITE(DMA_CX_CONFIG(usChannelNo), 0, pstCfg->ulCongfig);

    //debug
    printk("out DMA_StartWithCfg\n");

    return BSP_OK;
}

BSP_VOID DMA_Isr(BSP_VOID)
{
    //add code
}


BSP_U32 Debug_Bsp_Read_Reg(BSP_U32 ulReg)
{
    BSP_U32 ulRegVal = 0;

    return BSP_REG_READ(ulReg, 0, ulRegVal);
}


BSP_VOID Debug_Bsp_Write_Reg(BSP_U32 ulReg, BSP_U32 ulVal)
{
    BSP_REG_WRITE(ulReg, 0, ulVal);
}


BSP_U32 Debug_TcRaw_1_Read_Reg(void)
{
    BSP_U32 ulRegVal = 0;

    return BSP_REG_READ(DMA_INT_TC1_RAW, 0, ulRegVal);
}


BSP_U32 Debug_TcRaw_2_Read_Reg(void)
{
    BSP_U32 ulRegVal = 0;

    return BSP_REG_READ(DMA_INT_TC2_RAW, 0, ulRegVal);
}


BSP_VOID Debug_TcRaw_1_Write_Reg(BSP_U32 ulRegVal)
{
    BSP_REG_WRITE(DMA_INT_TC1_RAW, 0, ulRegVal);
}


BSP_VOID Debug_TcRaw_2_Write_Reg(BSP_U32 ulRegVal)
{
    BSP_REG_WRITE(DMA_INT_TC2_RAW, 0, ulRegVal);
}


BSP_U32 Debug_Tc_1_Mask_Read_Reg(void)
{
    BSP_U32 ulRegVal = 0;

    return BSP_REG_READ(DMA_INT_TC1_MASK_HIFI, 0, ulRegVal);
}


BSP_U32 Debug_Tc_2_Mask_Read_Reg(void)
{
    BSP_U32 ulRegVal = 0;

    return BSP_REG_READ(DMA_INT_TC2_MASK_HIFI, 0, ulRegVal);
}





#ifdef __cplusplus
}
#endif /* __cplusplus */

