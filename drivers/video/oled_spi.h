#ifndef __OLED_SPI_H__
#define __OLED_SPI_H__


#define ECS_SPI0_BASE HI_SPI_MST0_REGBASE_ADDR_VIRT /*SPI0��������ַ*/
#define ECS_SPI1_BASE HI_SPI_MST1_REGBASE_ADDR_VIRT /*SPI1��������ַ*/
extern const u32 spiBase[2];/*lint !e10*/
#define SPI_BASE(x)        (spiBase[x])   /* SPI����ַ */
#define SPI_CTRL0(x)       (SPI_BASE(x) + HI_SPI_CTRLR0_OFFSET)

/********************************************************************************/
/*    spi �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI_SPI_CTRLR0_OFFSET             (0x0) /* ���ƼĴ���0�� */
#define    HI_SPI_CTRLR1_OFFSET             (0x4) /* ���ƼĴ���1�� */
#define    HI_SPI_SSIENR_OFFSET             (0x8) /* SSIʹ�ܼĴ����� */
#define    HI_SPI_MWCR_OFFSET               (0xC) /* Microwire���ƼĴ����� */
#define    HI_SPI_SER_OFFSET                (0x10) /* slaveʹ�ܼĴ����� */
#define    HI_SPI_BAUDR_OFFSET              (0x14) /* ������ѡ�� */
#define    HI_SPI_TXFTLR_OFFSET             (0x18) /* ����FIFO��ֵ�� */
#define    HI_SPI_RXFTLR_OFFSET             (0x1C) /* ����FIFO��ֵ�� */
#define    HI_SPI_TXFLR_OFFSET              (0x20) /* ����FIFOˮ�߼Ĵ����� */
#define    HI_SPI_RXFLR_OFFSET              (0x24) /* ����FIFOˮ�߼Ĵ����� */
#define    HI_SPI_SR_OFFSET                 (0x28) /* ״̬�Ĵ����� */
#define    HI_SPI_IMR_OFFSET                (0x2C) /* �ж����μĴ����� */
#define    HI_SPI_ISR_OFFSET                (0x30) /* �ж�״̬�Ĵ����� */
#define    HI_SPI_RISR_OFFSET               (0x34) /* ԭʼ�жϼĴ����� */
#define    HI_SPI_TXOICR_OFFSET             (0x38) /* ����FIFO����ж�����Ĵ����� */
#define    HI_SPI_RXOICR_OFFSET             (0x3C) /* ����FIFO����ж�����Ĵ����� */
#define    HI_SPI_RXUICR_OFFSET             (0x40) /* ����FIFO�����ж�����Ĵ����� */
#define    HI_SPI_MSTICR_OFFSET             (0x44) /* ��master��ͻ�ж�����Ĵ����� */
#define    HI_SPI_ICR_OFFSET                (0x48) /* �ж�����Ĵ����� */
#define    HI_SPI_DMACR_OFFSET              (0x4C) /* DMA���ƼĴ����� */
#define    HI_SPI_DMATDLR_OFFSET            (0x50) /* DMA��������ˮ�ߡ� */
#define    HI_SPI_DMARDLR_OFFSET            (0x54) /* DMA��������ˮ�ߡ� */
#define    HI_SPI_IDR_OFFSET                (0x58) /* ID�Ĵ����� */
#define    HI_SPI_SSI_COMP_VERSION_OFFSET   (0x5C) /* �汾�Ĵ����� */
#define    HI_SPI_DR_OFFSET                 (0x60) /* ���ݼĴ����� */
#define    HI_SPI_RX_SAMPLE_DLY_OFFSET      (0xF0) /* ����ʱ���ӳټĴ��� */

/*����Ctrl0�Ĵ���ʱ������Ա��ƫ��*/
#define SPI_CTRL0_DFS_BITPOS        0   /* ���ݳ��� */
#define SPI_CTRL0_FRF_BITPOS        4   /* ֡���� */
#define SPI_CTRL0_SCPH_BITPOS       6   /* ʱ����λ */
#define SPI_CTRL0_SCPOL_BITPOS      7   /* ʱ�Ӽ��� */

#define SPI_CTRL0_TMOD_BITPOS       8   /* ����ģʽ���� */
#define SPI_CTRL0_TMOD_BITWIDTH     2
#define SPI_CTRL0_TMOD_BITMASK    (((1 << SPI_CTRL0_TMOD_BITWIDTH)-1) << SPI_CTRL0_TMOD_BITPOS)
#define SPI_CTRL0_TMOD_SEND_RECV    (0x00 << SPI_CTRL0_TMOD_BITPOS)   /* �շ�ģʽ */
#define SPI_CTRL0_TMOD_SEND         (0x01 << SPI_CTRL0_TMOD_BITPOS)   /* ����ģʽ */
#define SPI_CTRL0_TMOD_RECV         (0x02 << SPI_CTRL0_TMOD_BITPOS)   /* ����ģʽ */
#define SPI_CTRL0_TMOD_EEPROM_READ  (0x03 << SPI_CTRL0_TMOD_BITPOS)   /* EEPROM��ģʽ */

#define SPI_CFS_BITPOS              12  /* ����֡��С */

#define SPI_CTRL1(x)             (SPI_BASE(x) + HI_SPI_CTRLR1_OFFSET)
#define SPI_EN(x)                (SPI_BASE(x) + HI_SPI_SSIENR_OFFSET)
#define SPI_MWCTRL(x)            (SPI_BASE(x) + HI_SPI_MWCR_OFFSET  )
#define SPI_SLAVE_EN(x)          (SPI_BASE(x) + HI_SPI_SER_OFFSET   )
#define SPI_BAUD(x)              (SPI_BASE(x) + HI_SPI_BAUDR_OFFSET )
#define SPI_TXFTL(x)             (SPI_BASE(x) + HI_SPI_TXFTLR_OFFSET)
#define SPI_RXFTL(x)             (SPI_BASE(x) + HI_SPI_RXFTLR_OFFSET)
#define SPI_TXFL(x)              (SPI_BASE(x) + HI_SPI_TXFLR_OFFSET )
#define SPI_RXFL(x)              (SPI_BASE(x) + HI_SPI_RXFLR_OFFSET )
#define SPI_STATUS(x)            (SPI_BASE(x) + HI_SPI_SR_OFFSET    )
#define SPI_IMR(x)               (SPI_BASE(x) + HI_SPI_IMR_OFFSET   )
#define SPI_INT_STATUS(x)        (SPI_BASE(x) + HI_SPI_ISR_OFFSET   )
#define SPI_RX_SAMPLE_DLY(x)     (SPI_BASE(x) + HI_SPI_RX_SAMPLE_DLY_OFFSET)

#define SPI_STATUS_RXFULL         (1 << 4)
#define SPI_STATUS_RXNOTEMPTY     (1 << 3)
#define SPI_STATUS_TXEMPTY        (1 << 2)
#define SPI_STATUS_TXNOTFULL      (1 << 1)
#define SPI_STATUS_BUSY           (1 << 0)

#define SPI_RAW_INT_STATUS(x)  (SPI_BASE(x) + HI_SPI_RISR_OFFSET            )
#define SPI_TXO_INT_CLEAR(x)   (SPI_BASE(x) + HI_SPI_TXOICR_OFFSET          )
#define SPI_RXO_INT_CLEAR(x)   (SPI_BASE(x) + HI_SPI_RXOICR_OFFSET          )
#define SPI_RXU_INT_CLEAR(x)   (SPI_BASE(x) + HI_SPI_RXUICR_OFFSET          )
#define SPI_MST_INT_CLEAR(x)   (SPI_BASE(x) + HI_SPI_MSTICR_OFFSET          )
#define SPI_INT_CLEAR(x)       (SPI_BASE(x) + HI_SPI_ICR_OFFSET             )
#define SPI_DMAC(x)            (SPI_BASE(x) + HI_SPI_DMACR_OFFSET           )
#define SPI_DMATDL(x)          (SPI_BASE(x) + HI_SPI_DMATDLR_OFFSET         )
#define SPI_DMARDL(x)          (SPI_BASE(x) + HI_SPI_DMARDLR_OFFSET         )
#define SPI_ID(x)              (SPI_BASE(x) + HI_SPI_IDR_OFFSET             )
#define SPI_COMP_VERSION(x)    (SPI_BASE(x) + HI_SPI_SSI_COMP_VERSION_OFFSET)
#define SPI_DR(x)              (SPI_BASE(x) + HI_SPI_DR_OFFSET              )

/* for porting test */
/* Porting E2PROMʹ��SPI0 CS0 ; SFLASHʹ��SPI0 CS1*/
#define SPI_NO_DEV          0        /*SPI0*/
#define SPI_CS_EEPROM       (1 << 0)   /* EEPROMʹ��SSI0 CS0 */
#define SPI_CS_SFLASH       (1 << 1)   /* SFLASHʹ��SSI0 CS1 */
#define SPI_CS_DEV          SPI_CS_SFLASH/*Ӳ��ʵ�����ӵ��豸*/
/* ״̬�Ĵ���״̬λ */
#define SPI_DEV_STATUS_WIP  (1 << 0)  /* Write In Progress Bit */
#define SPI_DEV_STATUS_WEL  (1 << 1)  /* Write Enable Latch Bit */
#define SPI_DEV_STATUS_BP0  (1 << 2)  /* Block Protect Bits */
#define SPI_DEV_STATUS_BP1  (1 << 3)  /* Block Protect Bits */
#define SPI_DEV_STATUS_BP2  (1 << 4)  /* Block Protect Bits */
#define SPI_DEV_STATUS_SRWD  (1 << 7)  /* Status Register Write Protect */

#define SPI_MAX_DELAY_TIMES 0x1000 /*����ӳ�ʱ��*/

/*������*/
#define OK              (0)
#define ERROR          (-1)
#define MDELAY_10_MS          (10)

#endif


