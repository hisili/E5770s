
#include <linux/kernel.h>
#include <asm/io.h>
#include <linux/delay.h>
#include <linux/module.h>

#include "DrvInterface.h"
#include "drv_sio.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef enum{
    SLIC_NONE_TONE = 0,                     /* none */
    SLIC_RING,                              /* Ring */
    SLIC_RING_FOR_MONITOR,                  /* Ring for houtai Monitor */
    SLIC_KEEP_RING,                         /* Keep Ring */
    SLIC_DIAL_TONE,                         /* Dial tone */
    SLIC_BUSY_TONE,                         /* Busy tone */
    SLIC_ALARM_TONE,                        /* Alarm tone */
    SLIC_TIP_TONE,                          /* Succeed/fail tone */
    SLIC_FAULT_TONE,                        /* Fault tone */
    SLIC_CALL_WAITING_TONE,                 /* call waiting tone */
    SLIC_RINGBACK_TONE,                     /* Ring Back tone */
    SLIC_CONFIRMATION_TONE,                 /* Confirmation tone */
    SLIC_SUCCEED_TONE,
    SLIC_FAIL_TONE
} slic_tone_enum_type;

extern void slic_sound_start (  slic_tone_enum_type tone );


SIO_CTRL_STRU g_stSioCtrl = {{0}, {0}};

//ȥ��������ʱ������
//BSP_U32 g_ulPcmPara = 0xA5A5;
BSP_U32 g_ulPcmPara = 0x0;

extern void msleep(unsigned int msec);

BSP_VOID SIO_Init(BSP_VOID)
{
    iounmap((int *)SIO_BASE_ADDR_PHY);
    g_ulSioBaseAddr = (unsigned long)ioremap(SIO_BASE_ADDR_PHY, SIO_SIZE);

    printk("g_ulSioBaseAddr=0x%x\n", g_ulSioBaseAddr);

    /*дSIO_CTRL_CLR 0xffff��λSIO����ֹ���䡢��ֹ�ж�*/
    //��λSIO���ܵ����ѹ�����Slic�������⣬������Ҫ�Ƶ�Slic������
    BSP_REG_WRITE(SIO_CTRL_CLR, 0, 0xffff);

    /*дSIO_INTR_CLR 0x3f�������SIO�ж�*/
    BSP_REG_WRITE(SIO_INTR_CLR, 0, 0x3f);

    BSP_REG_WRITE(SIO_CTRL_SET, 0, 0x8000);
}

BSP_VOID SIO_Open(
    SIO_INT_MASK_ENUM_UINT16 enIntMask,
    SIO_INT_FUNC pfIntHandleFunc,
    BSP_U32 ulPara)
{
    /*дSIO_INTR_CLR 0xffff��λSIO����ֹ���䡢��ֹ�ж�*/
    BSP_REG_WRITE(SIO_CTRL_CLR, 0, 0xffff);

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
        BSP_REG_WRITE(SIO_INTR_MASK, 0, ~enIntMask);
    }

    /*ʹ��SIO���ա�����*/
    BSP_REG_WRITE(SIO_CTRL_SET, 0, 0x3000);
}

BSP_VOID SIO_Close(BSP_VOID)
{
    return;
}

BSP_VOID SIO_Isr(BSP_VOID)
{
    return;
}

BSP_U32 Debug_SIO_Read_RX(void)
{
    BSP_U32 ulRegVal = 0;

    return BSP_REG_READ(SIO_PCM_RD, 0, ulRegVal);
}

BSP_U32 Debug_SIO_Read_RX_Sta(void)
{
    BSP_U32 ulRegVal = 0;

    return BSP_REG_READ(SIO_CTRL_RX_STA, 0, ulRegVal);
}

BSP_U32 Debug_SIO_Read_TX_Sta(void)
{
    BSP_U32 ulRegVal = 0;

    return BSP_REG_READ(SIO_CTRL_TX_STA, 0, ulRegVal);
}


BSP_VOID Debug_SIO_Reset(void)
{
    BSP_REG_WRITE(SIO_CTRL_CLR, 0, 0x8000);
    msleep(10);
    BSP_REG_WRITE(SIO_CTRL_SET, 0, 0x8000);
    msleep(10);
}


BSP_VOID Debug_SIO_En_RX_TX(void)
{
    BSP_REG_WRITE(SIO_CTRL_SET, 0, 0x3000);
    BSP_REG_WRITE(SIO_CTRL_CLR, 0, 0x0C00);
}


BSP_VOID Debug_SIO_Dis_RX_TX(void)
{
    BSP_REG_WRITE(SIO_CTRL_CLR, 0, 0x3000);
    BSP_REG_WRITE(SIO_CTRL_SET, 0, 0x0C00);
}

BSP_VOID SetPcmPara(BSP_U32 ulPcmPara)
{
	g_ulPcmPara = ulPcmPara;
}

int Start_Equ_Slic_Test(void)
{
    BSP_U32 ulRegVal = 0x5f9b;
    BSP_U32 ulRegRet = 0;
    BSP_U32 count = 3;

    Debug_SIO_En_RX_TX();

    BSP_REG_WRITE(SIO_PCM_XD,0,ulRegVal);
    printk("---------------check 1 write %x,ulRegVal=%d\n",SIO_PCM_XD,ulRegVal);
    while(count)
    {
        BSP_REG_READ(SIO_PCM_RD, 0, ulRegRet);
        //���ݻ���У����ȷ�����سɹ�
        if (ulRegRet == ulRegVal)
        {
            printk("---------------check 1\n");
            return 1;
        }
        
        count--;
    }
    printk("--------------check 0, %x\n",ulRegRet);
    return 0;
}

EXPORT_SYMBOL(Start_Equ_Slic_Test);


#ifdef __cplusplus
}
#endif

