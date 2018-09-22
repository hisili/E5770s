

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include <linux/kernel.h>
#include <asm/io.h>
#include <linux/delay.h>
#include "DrvInterface.h"
#include <linux/string.h>
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

#include "pcm_voip_sio.h"
#include "ucom_comm.h"
#include "bsp_memmap.h"

#ifndef VOS_PRODUCT_E5172
#define VOS_PRODUCT_E5172
#endif

#ifndef VOS_TEST_NB
#define VOS_TEST_NB
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



static struct platform_device SIO_device = {
    .name = "SIO",
    .id = -1,
};


BSP_U32 g_ulSioBaseAddr_A =0;
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
DRV_SIO_CTRL_STRU   g_stDrvSioCtrl;    /* SIOģ�����ȫ�ֱ��� */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
irqreturn_t DRV_SIO_Isr_A(BSP_S32 irq, BSP_VOID *dev_id)
{
    BSP_U32                          uwIntState;
    DRV_SIO_INT_ISR_STRU               *pstIntIsr = DRV_SIO_GetIntIsrPtr();

    /*��ȡSIO�ж�״̬*/
    BSP_REG_READ(DRV_SIO_INTR_STATUS,0,uwIntState);

    /*���ж�״̬Ϊ0��ֱ�ӷ���*/
    if (0 == uwIntState)
    {
        return 0;
    }

    /*�����ѯ�����ж�*/
    BSP_REG_WRITE(DRV_SIO_INTR_CLR, 0x0,uwIntState);

    /*��SIO�жϻص������ǿ�,�����*/
    if (BSP_NULL != pstIntIsr->pfFunc)
    {
        pstIntIsr->pfFunc((DRV_SIO_INT_MASK_ENUM_UINT16)uwIntState, pstIntIsr->uwPara);
    }
	 return 1;
}

BSP_VOID DRV_SIO_Init_A(BSP_VOID)
{
    DRV_SIO_INT_ISR_STRU                *pstIntIsr = DRV_SIO_GetIntIsrPtr();
    DRV_SIO_STATUS_STRU                 *pstStatus = DRV_SIO_GetStatusPtr();
    BSP_S32 nRet = 0;
    /* ��ʼ��SioIntIsrΪȫ�� */
    memset(pstIntIsr,0,sizeof(DRV_SIO_INT_ISR_STRU));

    /* ��ʼ��Sio״̬����Ϊȫ0 */
    memset(pstStatus,0,sizeof(DRV_SIO_STATUS_STRU));
  
    g_ulSioBaseAddr_A = (unsigned long)ioremap(SIO_BASE_ADDR_PHY, SIO_SIZE);
 

    /* ��SIOʱ�� */
    //BSP_REG_WRITE(IO_ADDRESS(DRV_SC_BASE_ADDR), 0x000c, DRV_SIO_CLK_CTRL_WORD);

	 /*дDRV_SIO_CTRL_CLR 0xfff0��λSIO����ֹ���䡢��ֹ�ж�*/
    BSP_REG_WRITE(DRV_SIO_CTRL_CLR, 0x0,0xffff);

    /*дDRV_SIO_INTR_CLR 0x3f �������SIO�ж�*/
    BSP_REG_WRITE(DRV_SIO_INTR_CLR,0x0, 0x3f);

    /*ע��SIO ISR*/   
    nRet =request_irq(DRV_SIO_COMBINE_INT_NO,DRV_SIO_Isr_A,IRQF_SHARED,"SIO",&SIO_device);
   
    /*��ֹsio rx�ж�*/
    disable_irq(DRV_SIO_RX_INT_NO);

    /*��ֹsio tx�ж�*/
    disable_irq(DRV_SIO_TX_INT_NO);

    /*�⸴λSIO*/
    BSP_REG_WRITE(DRV_SIO_CTRL_SET,0x0, 0x8000);

    /* �ر�SIOʱ�� */
    //BSP_REG_WRITE(IO_ADDRESS(DRV_SC_BASE_ADDR),0x0010, DRV_SIO_CLK_CTRL_WORD);

    /* ���Ϊ�ر� */
    pstStatus->enMode = DRV_SIO_MODE_CLOSE;

}


BSP_VOID DRV_SIO_Open_A(
                DRV_SIO_INT_MASK_ENUM_UINT16    enIntMask,
                DRV_SIO_INT_FUNC                pfIntHandleFunc,
                BSP_U32                      uwPara)
{
	DRV_SIO_INT_ISR_STRU                *pstIntIsr = DRV_SIO_GetIntIsrPtr();
	DRV_SIO_STATUS_STRU                 *pstStatus = DRV_SIO_GetStatusPtr();

	
	if(DRV_SIO_MODE_OPEN == pstStatus->enMode)
	{
		return;
	}

	/* ��SIO����ʱ�� */
	//BSP_REG_WRITE(IO_ADDRESS(DRV_SC_BASE_ADDR), 0x000c,DRV_SIO_CLK_CTRL_WORD);

	/* ���Ϊ�� */
	pstStatus->enMode = DRV_SIO_MODE_OPEN;


	/* ����SIO�ܽſ����ֵ�ǰ���� */
	//BSP_REG_READ(IO_ADDRESS(DRV_SC_BASE_ADDR),0x0988, pstStatus->uwUartPinCtrlStatus);

	/* ����SIO�ܽſ�����Ϊ����LTE PCM�ܽŹ��� */
	//BSP_REG_SETBITS(IO_ADDRESS(DRV_SC_BASE_ADDR),0x0988, UCOM_BIT12, 2, 0);
	//BSP_REG_SETBITS(IO_ADDRESS(DRV_SC_BASE_ADDR),0x0988, UCOM_BIT7, 2, 1);

	/* ��SIO_1����ʱ�ӽӿ� */
	//BSP_REG_SETBITS(IO_ADDRESS(DRV_SC_BASE_ADDR),0x0024,  UCOM_BIT13, 1, 1);

	
	/* ����SIO masterģʽ */
	//BSP_REG_SETBITS(IO_ADDRESS(DRV_SC_BASE_ADDR),0x0030,  UCOM_BIT5, 1, 1);

	/* ����SIO ʱ����PADʱ��ͬ�� */
	//UCOM_RegBitWr(DRV_SIO_SIO_MODE, UCOM_BIT4, UCOM_BIT4, 0);

	/* ����SIO masterʱʱ��ԴƵ��Ϊ19.2M */
	//UCOM_RegBitWr(DRV_SIO_SIO_MODE, UCOM_BIT6, UCOM_BIT6, 0);

	/* ����PCM�ӿڹܽſ���Ϊmasterģʽ */
	//BSP_REG_SETBITS(IO_ADDRESS(DRV_SC_BASE_ADDR),0x0940,  UCOM_BIT20, 1, 1);
    msleep(1);
	/*дDRV_SIO_CTRL_CLRs 0xfff0��λSIO����ֹ���䡢��ֹ�ж�*/
	BSP_REG_WRITE(DRV_SIO_CTRL_CLR, 0x0,0xffff);

	/*��������SIO�жϣ���Ӧ����Ϊ1�������жϣ�Ϊ0����ж�*/
	BSP_REG_WRITE(DRV_SIO_INTR_MASK,  0x0,0xffffffff);

	/*�������SIO�ж�*/
	BSP_REG_WRITE(DRV_SIO_INTR_CLR,  0x0,0x3f);

	/*�⸴λ������ˮ��Tx-8(0.5)��Rx-8(0.5)��ʹ���ж�*/
	BSP_REG_WRITE(DRV_SIO_CTRL_SET, 0x0, 0x8088);

	/*����ΪPCMģʽ*/
	//UCOM_RegWr(DRV_SIO_MODE, 0x1);

	/*���÷�����չ��ֹ*/
	BSP_REG_WRITE(DRV_SIO_SIGNED_EXT,  0x0,0);

	/*����ΪPCMģʽ*/
	BSP_REG_WRITE(DRV_SIO_MODE,  0x0,0x1);

	/*����Ϊ���͡�����16bitλ��*/
	BSP_REG_WRITE(DRV_SIO_DATA_WIDTH_SET, 0x0, 0x9);


	/*�ر�˫�����ϲ�*/
	BSP_REG_WRITE(DRV_SIO_I2S_POS_MERGE_EN,  0x0,0x0);



	/*���жϻص������ǿգ�����ж�����,����ص�������Ϣ*/
	if (BSP_NULL != pfIntHandleFunc)
	{
		/*��enIntMaskȡ�������ж�����*/
		BSP_REG_WRITE(DRV_SIO_INTR_MASK, 0x0, ~enIntMask);

		pstIntIsr->pfFunc = pfIntHandleFunc;
		pstIntIsr->uwPara = uwPara;
	}

	/*ʹ��SIO���ա�����*/
	BSP_REG_WRITE(DRV_SIO_CTRL_SET, 0x0,0x3000);

    msleep(1);

}

BSP_VOID DRV_SIO_Close_A(BSP_VOID)
{
    DRV_SIO_INT_ISR_STRU                *pstIntIsr = DRV_SIO_GetIntIsrPtr();
    DRV_SIO_STATUS_STRU                 *pstStatus = DRV_SIO_GetStatusPtr();

    if(DRV_SIO_MODE_CLOSE == pstStatus->enMode)
    {
        return;
    }

    /*��λSIO����ֹ���䡢��ֹ�ж�*/
    BSP_REG_WRITE(DRV_SIO_CTRL_CLR, 0x0,0xffff);

    /*��������SIO�ж�*/
    BSP_REG_WRITE(DRV_SIO_INTR_MASK, 0x0, 0xffffffff);

    /*���SIO�ж�*/
    BSP_REG_WRITE(DRV_SIO_INTR_CLR,  0x0,0x3f);

    /*�⸴λSIO*/
    BSP_REG_WRITE(DRV_SIO_CTRL_SET, 0x0, 0x8000);

    /*����жϻص����������Ϣ*/
    memset(pstIntIsr, 0, sizeof(DRV_SIO_INT_ISR_STRU));

    /* �ر�SIO_1����ʱ�ӽӿ� */
    BSP_REG_SETBITS(IO_ADDRESS(DRV_SC_BASE_ADDR),0x0028,  UCOM_BIT13, 1, 1);

    /* �ָ�SIO�ܽſ�����Ϊԭ��ֵ */
   BSP_REG_SETBITS(IO_ADDRESS(DRV_SC_BASE_ADDR),
                  0x0988, 
                  UCOM_BIT12,
                  2,
                  (pstStatus->uwUartPinCtrlStatus>>UCOM_BIT12)&0x3);
    BSP_REG_SETBITS(IO_ADDRESS(DRV_SC_BASE_ADDR),
	           0x0988, 
                  UCOM_BIT7,
                  2,
                  (pstStatus->uwUartPinCtrlStatus>>UCOM_BIT7)&0x3);



    /* �ر�SIOʱ�� */
    BSP_REG_WRITE(IO_ADDRESS(DRV_SC_BASE_ADDR),0x0010, DRV_SIO_CLK_CTRL_WORD);

    /* ���Ϊ�ر� */
    pstStatus->enMode = DRV_SIO_MODE_CLOSE;

}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

