

#ifndef BSP_SPI_DRV_H
#define BSP_SPI_DRV_H

#include <linux/gpio.h>
#include "DrvInterface.h"
#include "data_types.h"


#ifdef __cplusplus
extern "C"
{
#endif

    //#include "product_config.h"
    //#include "BSP_GLOBAL.h"
    //#include "BSP_VERSION.h"
    //#include "arm_pbxa9.h"

    /* SPI�ܽŸ��ú궨�� */
#define SSP0_WIRE_4 14//(1<<14)
#define SSP0_CS1_EN 15//(1<<15)

#define SSP1_WIRE_4 30//(1<<30)
#define SSP1_CS1_EN 31//(1UL<<31)

#define SSP0_CTRL       11//(1<<11)
#define SSP1_CTRL       15//(1<<15)
#define HS_UART_CTRL    (3<<18)

    typedef struct tagSPI_ADCFG_S
    {
        BSP_U16 regAddr;        /*�Ĵ�����ַ*/
        BSP_U8  regValue;       /*�Ĵ���Ҫ���õ�ֵ*/
    } SPI_ADCFG_S;

#define SPI_LOG_LEVEL_DEBUG 300

    /*����Ctrl0�Ĵ���ʱ������Ա��ƫ��*/
#define SPI_PROT_SHIFT_BITS 0x4
#define SPI_COMM_SHIFT_BITS 0xc

    /*FIFO���*/
#define SPI_FIFO_DEPTH     8

    /*�Ĵ���ƫ��*/
#define SPI_CTRL0_OFFSET   0x0
#define SPI_CTRL1_OFFSET   0x4
#define SPI_EN_OFFSET      0x8
#define SPI_MWCTRL_OFFSET      0xc
#define SPI_SLAVE_EN_OFFSET    0x10
#define SPI_BAUD_OFFSET    0x14
#define SPI_TXFTL_OFFSET    0x18
#define SPI_RXFTL_OFFSET    0x1c
#define SPI_TXFL_OFFSET    0x20
#define SPI_RXFL_OFFSET    0x24
#define SPI_STATUS_OFFSET    0x28
#define SPI_INT_MASK_OFFSET    0x2c
#define SPI_INT_STATUS_OFFSET    0x30
#define SPI_RAW_INT_STATUS_OFFSET    0x34
#define SPI_TXO_INT_CLEAR_OFFSET    0x38
#define SPI_RXO_INT_CLEAR_OFFSET    0x3c
#define SPI_RXU_INT_CLEAR_OFFSET    0x40
#define SPI_MST_INT_CLEAR_OFFSET    0x44
#define SPI_INT_CLEAR_OFFSET    0x48
#define SPI_DMAC_OFFSET    0x4c
#define SPI_DMATDL_OFFSET    0x50
#define SPI_DMARDL_OFFSET    0x54
#define SPI_ID_OFFSET      0x58
#define SPI_COMP_VERSION_OFFSET      0x5c
#define SPI_DATA_OFFSET_BASE    0x60
#define SPI_DATA_OFFSET(i)    (SPI_DATA_OFFSET_BASE + i*0x4)

#define E5172_SLIC_WAKEUP_DEBUG
#undef E5172_SLIC_WAKEUP_DEBUG

#ifdef E5172_SLIC_WAKEUP_DEBUG
/* ���ߵ�Slic�ж���GPIO2_13 */
#define BASE_GPIO_1 0x9000E000
#define GPIO_23 13
#else
#define BASE_GPIO_1 0x90011000
#define GPIO_23 23
#endif


#define HI_GPIO_SWPORT_DDR 0x4
#define HI_GPIO_INTEN 0x30
#define HI_GPIO_INTMASK 0x34
#define HI_GPIO_INTTYPE_LEVEL 0x38
#define HI_GPIO_INT_PLOARITY 0x3C
#define HI_GPIO_GPIO_INTSTATUS 0x40
#define HI_GPIO_SIZE 0x1000
#define HI_GPIO_PORT_EOI 0x4C

#define SLIC_GPIO_REG(base, reg) (*(volatile UINT32 *)(base + (reg)))
#define SLIC_GPIO_REG_GETBIT(base, reg, pos) ( (SLIC_GPIO_REG(base, reg )>>pos) & 1 )
#define SLIC_GPIO_REG_SETBIT(base, reg, pos) (SLIC_GPIO_REG(base, reg) = SLIC_GPIO_REG(base, reg) | (1<< (pos)) )
#define SLIC_GPIO_REG_CLRBIT(base, reg, pos) (SLIC_GPIO_REG(base, reg) = SLIC_GPIO_REG(base, reg) & (~(1<< (pos)) ) )

//����Hi6920�û�ָ�ϣ��������жϺ�
#define HI6920_I2C_IRQ 111
#define HI6920_GPIO0_IRQ 112

#ifdef E5172_SLIC_WAKEUP_DEBUG
#define HI6920_GPIO1_IRQ 114
#else
#define HI6920_GPIO1_IRQ 113
#endif

    extern UINT32 g_gpioBase;

    /*SPI״̬�Ĵ�����ֵ*/
    //#define SPI_STATUS ((*(volatile unsigned int*)(u32TemBaseAddr + SPI_STATUS_OFFSET)))

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
    BSP_S32 SPI_Init();

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
    BSP_S32 SPI_Lock(SPI_DEV_ID_E enSpiId);

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
    BSP_S32 SPI_UnLock(SPI_DEV_ID_E enSpiId);

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
    * �� �� ֵ  : OK     ���ͳɹ�
    *             ERROR  ����ʧ��
    *****************************************************************************/
    BSP_S32 SPI_POLL_Send(SPI_DEV_S *pSpiId, void *pData, BSP_U32 u32time);

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
    * �� �� ֵ  : OK    ���ճɹ�
    *             ERROR ����ʧ��
    *****************************************************************************/
    BSP_S32 SPI_POLL_Receive(SPI_DEV_S *pSpiId,BSP_VOID *pData, BSP_U32 u32Lens);

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
    BSP_S32 SPI_SetSpiOwner(SPI_DEV_S *pstSpiID);

    BSP_VOID SPI_GetGlobalVariable();

    BSP_VOID SPI_GetRegistValue();
#endif

    typedef int BOOL;

    //add new interface
    INT32 SlicSpiInit(void);
    UINT8 SlicReadReg(UINT8 ucReg);
    void SlicWriteReg(UINT8 ucReg, UINT8 ucVal);
    UINT32 SlicReadRam(UINT16 usRam);
    void SlicWriteRam(UINT16 usRam, UINT32 ulData);
    INT32 SlicSetUserMode(BOOL on);
    void EnableSlicIrq( int bEnable );
    void EnSlicInt(void);
    void DisSlicInt(void);

#ifdef __cplusplus
}
#endif

#endif

