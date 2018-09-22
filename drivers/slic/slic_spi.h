

#ifndef __SLIC_SPI_H__
#define __SLIC_SPI_H__

//#include "OnChipRom.h"

#define DUMMY_DATA  0x00

extern /*const */UINT32 spiBase[2];
//#define SPI_BASE(x)        ECS_SPI0_BASE
//#define SPI_BASE(x)        (0==(x) ? ECS_SPI0_BASE : ECS_SPI0_BASE)   /* SPI����ַ */
//#define SPI_BASE(x)        (0==(x) ? ECS_SPI0_BASE : ECS_SPI1_BASE)   /* SPI����ַ */
#define SPI_BASE(x)        (spiBase[x])   /* SPI����ַ */

#define SPI_CTRL0(x)       (SPI_BASE(x) + 0x0)
/*����Ctrl0�Ĵ���ʱ������Ա��ƫ��*/
#define SPI_CTRL0_DFS_BITPOS        0   /* ���ݳ��� */
#define SPI_CTRL0_FRF_BITPOS        4   /* ֡���� */
#define SPI_CTRL0_SCPH_BITPOS       6   /* ʱ����λ */
#define SPI_CTRL0_SCPOL_BITPOS      7   /* ʱ�Ӽ��� */

#define SPI_CTRL0_TMOD_BITPOS       8   /* ����ģʽ���� */
#define SPI_CTRL0_TMOD_BITWIDTH     2
#define SPI_CTRL0_TMOD_BITMASK     (((1<<SPI_CTRL0_TMOD_BITWIDTH)-1)<<SPI_CTRL0_TMOD_BITPOS)
#define SPI_CTRL0_TMOD_SEND_RECV    (0x00<<SPI_CTRL0_TMOD_BITPOS)   /* �շ�ģʽ */
#define SPI_CTRL0_TMOD_SEND         (0x01<<SPI_CTRL0_TMOD_BITPOS)   /* ����ģʽ */
#define SPI_CTRL0_TMOD_RECV         (0x02<<SPI_CTRL0_TMOD_BITPOS)   /* ����ģʽ */
#define SPI_CTRL0_TMOD_EEPROM_READ  (0x03<<SPI_CTRL0_TMOD_BITPOS)   /* EEPROM��ģʽ */

#define SPI_CFS_BITPOS              12  /* ����֡��С */

#define SPI_CTRL1(x)       (SPI_BASE(x) + 0x4)
#define SPI_EN(x)          (SPI_BASE(x) + 0x8)
#define SPI_MWCTRL(x)      (SPI_BASE(x) + 0xc)
#define SPI_SLAVE_EN(x)    (SPI_BASE(x) + 0x10)
#define SPI_BAUD(x)        (SPI_BASE(x) + 0x14)
#define SPI_TXFTL(x)       (SPI_BASE(x) + 0x18)
#define SPI_RXFTL(x)       (SPI_BASE(x) + 0x1c)
#define SPI_TXFL(x)        (SPI_BASE(x) + 0x20)
#define SPI_RXFL(x)        (SPI_BASE(x) + 0x24)
#define SLIC_SPI_STATUS(x)      (SPI_BASE(x) + 0x28)
#define SPI_IMR(x)         (SPI_BASE(x) + 0x2c)
#define SPI_INT_STATUS(x)  (SPI_BASE(x) + 0x30)

#define SPI_STATUS_RXFULL         (1 << 4)
#define SPI_STATUS_RXNOTEMPTY     (1 << 3)
#define SPI_STATUS_TXEMPTY        (1 << 2)
#define SPI_STATUS_TXNOTFULL      (1 << 1)
#define SPI_STATUS_BUSY           (1 << 0)

#define SPI_RAW_INT_STATUS(x)  (SPI_BASE(x) + 0x34)
#define SPI_TXO_INT_CLEAR(x)   (SPI_BASE(x) + 0x38)
#define SPI_RXO_INT_CLEAR(x)   (SPI_BASE(x) + 0x3c)
#define SPI_RXU_INT_CLEAR(x)   (SPI_BASE(x) + 0x40)
#define SPI_MST_INT_CLEAR(x)   (SPI_BASE(x) + 0x44)
#define SPI_INT_CLEAR(x)       (SPI_BASE(x) + 0x48)
#define SPI_DMAC(x)            (SPI_BASE(x) + 0x4c)
#define SPI_DMATDL(x)          (SPI_BASE(x) + 0x50)
#define SPI_DMARDL(x)          (SPI_BASE(x) + 0x54)
#define SPI_ID(x)              (SPI_BASE(x) + 0x58)
#define SPI_COMP_VERSION(x)    (SPI_BASE(x) + 0x5c)
#define SPI_DR(x)              (SPI_BASE(x) + 0x60)


//INT32 spiInit(UINT32 spiNo);
//INT32 spiRecv (UINT32 spiNo, UINT32 cs, UINT8* prevData, UINT32 recvSize,UINT8* psendData,UINT32 sendSize );
//INT32 spiSend (UINT32 spiNo, UINT32 cs, UINT8* pData, UINT32 ulLen);

#endif

