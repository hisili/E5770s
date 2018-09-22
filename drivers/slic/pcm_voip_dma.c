#include <linux/kernel.h>
#include <linux/string.h>
#include <asm/io.h>
#include "DrvInterface.h"
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
#include <linux/jiffies.h>
#include <asm/irq.h>
#include <mach/irqs.h>
#include <linux/spi/spi.h>
#include <linux/platform_device.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>

#include "pcm_voip_dma.h"
#include "ucom_comm.h"
#include "bsp_memmap.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


static struct platform_device DMA_device = {
    .name = "DMA",
    .id = -1,
};
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* DMAͨ���жϴ�����ָ������, ��DRV_DMA_RegisterIsr��ֵ */
DRV_DMA_CXISR_STRU g_astDrvDmaCxIntIsr[DRV_DMA_MAX_CHANNEL_NUM];
BSP_U32 g_uldmaBaseAddr = 0;
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


irqreturn_t DRV_DMA_Isr_A(BSP_S32 irq, BSP_VOID *dev_id)
{
    BSP_U32                          i;
    BSP_U32                          uwErr1;
    BSP_U32                          uwErr2;
    BSP_U32                          uwErr3;
    BSP_U32                          uwTc1;
    BSP_U32                          uwTc2;
    BSP_U32                          uwIntMask;
    BSP_U32                          uwIntState;
    DRV_DMA_INT_TYPE_ENUM_UINT16        enIntType;
    DRV_DMA_CXISR_STRU                 *pstDmaCxIsr = DRV_DMA_GetCxIsrPtr();

	BSP_REG_READ(DRV_DMA_INT_STAT_HIFI,0,uwIntState);

    /*��ͨ��״̬ȫ0��ʾȫͨ�����жϻ��ж��Ѵ���,ֱ���˳�*/
    if (0 == uwIntState)
    {
        return 0;
    }

    /*��ȡ���жϼĴ���,��ѯ���ж�״̬,����Tc1/Tc2/Err1/Err2/Err3*/
    BSP_REG_READ(DRV_DMA_INT_ERR1_HIFI,0,uwErr1);
    BSP_REG_READ(DRV_DMA_INT_ERR2_HIFI,0,uwErr2);
    BSP_REG_READ(DRV_DMA_INT_ERR3_HIFI,0,uwErr3);
    BSP_REG_READ(DRV_DMA_INT_TC1_HIFI,0,uwTc1);
    BSP_REG_READ(DRV_DMA_INT_TC2_HIFI,0,uwTc2);
    /*дuwIntState���ε����Ĵ�������ж�,������β�ѯ����ͨ���ж�*/
    BSP_REG_WRITE(DRV_DMA_INT_TC1_RAW,0, uwIntState);
    BSP_REG_WRITE(DRV_DMA_INT_TC2_RAW, 0,uwIntState);
    BSP_REG_WRITE(DRV_DMA_INT_ERR1_RAW, 0,uwIntState);
    BSP_REG_WRITE(DRV_DMA_INT_ERR2_RAW, 0,uwIntState);
    BSP_REG_WRITE(DRV_DMA_INT_ERR3_RAW,0, uwIntState);

    /*�������ø�ͨ��ע��Ļص�������*/
    for ( i = 0; i < DRV_DMA_MAX_CHANNEL_NUM; i++)
    {
        uwIntMask = 0x1L << i;

        /*����ͨ�����жϲ���(��Ӧ����Ϊ1)*/
        if (uwIntState & uwIntMask)
        {
            if (BSP_NULL != pstDmaCxIsr[i].pfFunc)
            {
                /*��ERR1�ж�״̬��Ӧ����Ϊ1*/
                if (uwErr1 & uwIntMask)
                {
                    enIntType = DRV_DMA_INT_TYPE_ERR1;
                }
                /*��ERR2�ж�״̬��Ӧ����Ϊ1*/
                else if (uwErr2 & uwIntMask)
                {
                    enIntType = DRV_DMA_INT_TYPE_ERR2;
                }
                /*��ERR3�ж�״̬��Ӧ����Ϊ1*/
                else if (uwErr3 & uwIntMask)
                {
                    enIntType = DRV_DMA_INT_TYPE_ERR3;
                }
                /*��TC1�ж�״̬��Ӧ����Ϊ1*/
                else if (uwTc1 & uwIntMask)
                {
                    enIntType = DRV_DMA_INT_TYPE_TC1;
                }
                /*��TC2�ж�״̬��Ӧ����Ϊ1*/
                else if (uwTc2 & uwIntMask)
                {
                    enIntType = DRV_DMA_INT_TYPE_TC2;
                }
                /*δ֪�ж�*/
                else
                {
                    enIntType = DRV_DMA_INT_TYPE_BUTT;
                }

                /*����ע����жϴ�����*/
                pstDmaCxIsr[i].pfFunc(enIntType, pstDmaCxIsr[i].uwPara);
            }
        }
    }
	return 1;
}

BSP_VOID DRV_DMA_Init_A( BSP_VOID )
{
    int err = 0;
    DRV_DMA_CXISR_STRU                 *pstDmaCxIsr = DRV_DMA_GetCxIsrPtr();
    	
    /*��ʼ��g_astDrvDmaCxIntIsrΪȫ��*/
    memset(pstDmaCxIsr, 0, sizeof(DRV_DMA_CXISR_STRU)*DRV_DMA_MAX_CHANNEL_NUM);
    g_uldmaBaseAddr = (unsigned long)ioremap(DMA_BASE_ADDR_PHY, DMA_SIZE);
   
    /* V7R1 ѡ��LTE SIO��DMAΪEDMA */
    //BSP_REG_SETBITS(IO_ADDRESS(SC_DMA_SEL_CTRL_ADDR), 0x0, 2, 1, 1);
	

    /*����д0�����¼Ĵ���Ĭ������HiFi DMA�ж�*/
    BSP_REG_WRITE(DRV_DMA_INT_ERR1_MASK_HIFI, 0, 0);
    BSP_REG_WRITE(DRV_DMA_INT_ERR2_MASK_HIFI, 0, 0);
    BSP_REG_WRITE(DRV_DMA_INT_ERR3_MASK_HIFI, 0, 0);
    BSP_REG_WRITE(DRV_DMA_INT_TC1_MASK_HIFI, 0, 0);
    BSP_REG_WRITE(DRV_DMA_INT_TC2_MASK_HIFI, 0, 0);

  
    err = request_irq(DRV_DMA_INT_NO_HIFI,DRV_DMA_Isr_A,IRQF_SHARED,"DMA",&DMA_device);
    if(0 != err)
    {
        printk("request irq for DMA error.\n");
    }
  
}

BSP_U32 DRV_DMA_StartWithCfg_A(
                BSP_U16              uhwChannelNo,
                DRV_DMA_CXCFG_STRU     *pstCfg,
                DRV_DMA_INT_FUNC        pfIntHandleFunc,
                BSP_U32              uwPara)
{
    BSP_U32                          uwChannelMask   = (0x1L << uhwChannelNo);
    DRV_DMA_CXISR_STRU                 *pstCxIsr        = DRV_DMA_GetCxIsrPtr();
  
    /* �������Ƿ�Ƿ� */
    if (uhwChannelNo >= DRV_DMA_MAX_CHANNEL_NUM)
    {
        return BSP_ERROR;
    }

    /*д0��DRV_DMA_CX_CONFIG(uhwChannelNo) bit0��ֹͨ��*/
    BSP_REG_SETBITS(DRV_DMA_CX_CONFIG((BSP_U32)uhwChannelNo),
                   0x0,
                  UCOM_BIT0,
                  1,
                  0);

    /*дͨ��X��ǰһά����ʣ���Byte��,[15,0]*/
    BSP_REG_SETBITS(DRV_DMA_CX_CNT0((BSP_U32)uhwChannelNo),
                   0x0,
                  UCOM_BIT0,
                  16,
                  pstCfg->uhwACount);
    
    /*дͨ��X��ǰ��ά����ʣ���Array����,[31,16]*/
    BSP_REG_SETBITS(DRV_DMA_CX_CNT0((BSP_U32)uhwChannelNo),
                   0x0,
                  UCOM_BIT16,
                  16,
                  pstCfg->uhwBCount);

    /*дͨ��X��ǰ��ά����ʣ���Frame��,[15,0]*/
    BSP_REG_SETBITS(DRV_DMA_CX_CNT1((BSP_U32)uhwChannelNo),
                   0x0,
                  UCOM_BIT0,
                  16,
                  pstCfg->uhwCCount);

    /*дͨ��X�Ķ�άԴ��ַƫ����[31,16]��Ŀ�ĵ�ַƫ����[15,0]*/
    BSP_REG_SETBITS(DRV_DMA_CX_BINDX((BSP_U32)uhwChannelNo),
                   0x0,
                  UCOM_BIT0,
                  16,
                  pstCfg->uhwDstBIndex);
    BSP_REG_SETBITS(DRV_DMA_CX_BINDX((BSP_U32)uhwChannelNo),
                   0x0,
                  UCOM_BIT16,
                  16,
                  pstCfg->uhwSrcBIndex);

    /*дͨ��X����άԴ��ַƫ����[31,16]��Ŀ�ĵ�ַƫ����[15,0]*/
    BSP_REG_SETBITS(DRV_DMA_CX_CINDX((BSP_U32)uhwChannelNo),
                   0x0,
                  UCOM_BIT0,
                  16,
                  pstCfg->uhwDstCIndex);
    BSP_REG_SETBITS(DRV_DMA_CX_CINDX((BSP_U32)uhwChannelNo),
                   0x0,
                  UCOM_BIT16,
                  16,
                  pstCfg->uhwSrcCIndex);

    /*дͨ��X��Դ��ַ[31,0]��Ŀ�ĵ�ַ[31,0]*/
    BSP_REG_WRITE(DRV_DMA_CX_DES_ADDR((BSP_U32)uhwChannelNo),0,pstCfg->uwDstAddr);
    BSP_REG_WRITE(DRV_DMA_CX_SRC_ADDR((BSP_U32)uhwChannelNo),0,pstCfg->uwSrcAddr);

    /*дͨ��X�������ַ����*/
    BSP_REG_WRITE(DRV_DMA_CX_LLI((BSP_U32)uhwChannelNo), 0, pstCfg->uwLli);

    /*���ͨ��X�ĸ����ж�״̬*/
    BSP_REG_WRITE(DRV_DMA_INT_TC1_RAW,  0,uwChannelMask);
    BSP_REG_WRITE(DRV_DMA_INT_TC2_RAW,  0,uwChannelMask);
    BSP_REG_WRITE(DRV_DMA_INT_ERR1_RAW,  0,uwChannelMask);
    BSP_REG_WRITE(DRV_DMA_INT_ERR2_RAW,  0,uwChannelMask);
    BSP_REG_WRITE(DRV_DMA_INT_ERR3_RAW, 0, uwChannelMask);

    /*���ص������ǿ�,�򱣴��ֵ*/
    if (BSP_NULL!= pfIntHandleFunc)
    {
        pstCxIsr[uhwChannelNo].pfFunc  = pfIntHandleFunc;
        pstCxIsr[uhwChannelNo].uwPara  = uwPara;

        /*����д(uhwChannelNo��ӦbitΪ1)�����¼Ĵ�����HiFi��ӦDMAͨ���ж�����*/
        BSP_REG_SETBITS(DRV_DMA_INT_ERR1_MASK_HIFI, 0x0,uhwChannelNo, 1, 1);
        BSP_REG_SETBITS(DRV_DMA_INT_ERR2_MASK_HIFI, 0x0,uhwChannelNo, 1, 1);
        BSP_REG_SETBITS(DRV_DMA_INT_ERR3_MASK_HIFI, 0x0,uhwChannelNo, 1, 1);
        BSP_REG_SETBITS(DRV_DMA_INT_TC1_MASK_HIFI, 0x0,uhwChannelNo, 1, 1);
        BSP_REG_SETBITS(DRV_DMA_INT_TC2_MASK_HIFI, 0x0,uhwChannelNo, 1, 1);

    }

    /*дͨ��X������*/
    BSP_REG_WRITE(DRV_DMA_CX_CONFIG((BSP_U32)uhwChannelNo), 0,pstCfg->uwConfig);
    return BSP_OK;

}

BSP_VOID DRV_DMA_Stop_A(BSP_U16 uhwChannelNo)
{
    DRV_DMA_CXISR_STRU                 *pstCxIsr        = DRV_DMA_GetCxIsrPtr();

    /* д0��DRV_DMA_CX_CONFIG(uhwChannelNo) bit0 ֹͣ��ӦDMAͨ�� */
    BSP_REG_SETBITS(DRV_DMA_CX_CONFIG((BSP_U32)uhwChannelNo),0x0,  UCOM_BIT0, 1, 0);

    /*����д(uhwChannelNo��ӦbitΪ0)�����¼Ĵ�������HiFi��ӦDMAͨ���ж�*/
    BSP_REG_SETBITS(DRV_DMA_INT_ERR1_MASK_HIFI, 0x0, uhwChannelNo, 1, 0);
    BSP_REG_SETBITS(DRV_DMA_INT_ERR2_MASK_HIFI, 0x0, uhwChannelNo, 1, 0);
    BSP_REG_SETBITS(DRV_DMA_INT_ERR3_MASK_HIFI, 0x0, uhwChannelNo, 1, 0);
    BSP_REG_SETBITS(DRV_DMA_INT_TC1_MASK_HIFI, 0x0, uhwChannelNo, 1, 0);
    BSP_REG_SETBITS(DRV_DMA_INT_TC2_MASK_HIFI, 0x0, uhwChannelNo, 1, 0);

    /*���ȫ�ֱ����ж�Ӧͨ����������*/
    memset(&pstCxIsr[uhwChannelNo],0,sizeof(DRV_DMA_CXISR_STRU));
}



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

