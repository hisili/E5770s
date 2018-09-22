

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifndef __DRV_SIO_H__
#define __DRV_SIO_H__

#include <linux/kernel.h>
#include "DrvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define DRV_SC_BASE_ADDR                (0x90000000U)                           /* SC����ַ */


#define DRV_SIO_CLK_CTRL_WORD           (0x0010)                                /* V7R1 CS��SIO����ʱ�ӿ�����,��4bit��1 */
#define DRV_SIO_SIO_MODE                (DRV_SC_BASE_ADDR + 0x0030)             /* V7R1 CS��SIOʱ�ӿ��ƼĴ��� */
#define DRV_SIO_PCM_MODE                (DRV_SC_BASE_ADDR + 0x0940)             /* PCM�ӿڹܽſ��ƼĴ��� */
#define DRV_SIO_UART_PIN_CTRL           (DRV_SC_BASE_ADDR + 0x0988)             /* �ܽŸ�����Ϣ���ƼĴ��� */
#define DRV_SIO_CLK_FREQ_CTRL           (DRV_SC_BASE_ADDR + 0x0044)             /* V7R1 SIO MASTER����������� */


#define DRV_SIO_COMBINE_INT_NO          (10)                                    /* SIO����ж��жϺ� */
#define DRV_SIO_RX_INT_NO               (8)                                     /* SIO�����ж��жϺ� */
#define DRV_SIO_TX_INT_NO               (9)                                     /* SIO�����ж��жϺ� */
extern BSP_U32 g_ulSioBaseAddr_A;

#define SIO_BASE_ADDR_PHY   (0x900A7000U)
#define SIO_SIZE            (0x1000)

#define DRV_SIO_BASE_ADDR       (g_ulSioBaseAddr_A)

#define DRV_SIO_MODE                    (DRV_SIO_BASE_ADDR + 0x40)              /* ģʽ�Ĵ���                      */
#define DRV_SIO_INTR_STATUS             (DRV_SIO_BASE_ADDR + 0x44)              /* SIO���ж�״ָ̬ʾ�Ĵ���         */
#define DRV_SIO_INTR_CLR                (DRV_SIO_BASE_ADDR + 0x48)              /* �ж�����Ĵ���                  */
#define DRV_SIO_I2S_LEFT_XD             (DRV_SIO_BASE_ADDR + 0x4c)              /* I2S�������������ݼĴ���         */
#define DRV_SIO_I2S_RIGHT_XD            (DRV_SIO_BASE_ADDR + 0x50)              /* I2S�������������ݼĴ���         */
#define DRV_SIO_PCM_XD                  (DRV_SIO_BASE_ADDR + 0x50)              /* PCMģʽ�µ����ݷ��ͼĴ���       */
#define DRV_SIO_I2S_LEFT_RD             (DRV_SIO_BASE_ADDR + 0x54)              /* I2S�������������ݼĴ���         */
#define DRV_SIO_I2S_RIGHT_RD            (DRV_SIO_BASE_ADDR + 0x58)              /* I2S�������������ݼĴ���         */
#define DRV_SIO_PCM_RD                  (DRV_SIO_BASE_ADDR + 0x58)              /* PCM�������ݼĴ���               */
#define DRV_SIO_CTRL_SET                (DRV_SIO_BASE_ADDR + 0x5c)              /* ���üĴ���                      */
#define DRV_SIO_CTRL_CLR                (DRV_SIO_BASE_ADDR + 0x60)              /* ����Ĵ���                      */
#define DRV_SIO_RX_STA                  (DRV_SIO_BASE_ADDR + 0x68)              /* SIO����״̬�Ĵ���               */
#define DRV_SIO_TX_STA                  (DRV_SIO_BASE_ADDR + 0x6c)              /* SIO����״̬�Ĵ���               */
#define DRV_SIO_DATA_WIDTH_SET          (DRV_SIO_BASE_ADDR + 0x78)              /* ��I2S/PCMģʽ�µ����ݿ�ȼĴ��� */
#define DRV_SIO_I2S_START_POS           (DRV_SIO_BASE_ADDR + 0x7c)              /* I2S����������ַ�ϲ����д��ʼ����λ�����üĴ��� */
#define DRV_SIO_I2S_POS_FLAG            (DRV_SIO_BASE_ADDR + 0x80)              /* I2S������ַ�ϲ����´ζ�д��������λ�üĴ���     */
#define DRV_SIO_SIGNED_EXT              (DRV_SIO_BASE_ADDR + 0x84)              /* ��λ���ݷ�����չʹ�ܼĴ���      */
#define DRV_SIO_INTR_MASK               (DRV_SIO_BASE_ADDR + 0x8c)              /* �ж����μĴ���                  */
#define DRV_SIO_I2S_POS_MERGE_EN        (DRV_SIO_BASE_ADDR + 0x88)              /* I2S����������ַ�ϲ����ƼĴ���   */
#define DRV_SIO_I2S_DUAL_RX_CHN         (DRV_SIO_BASE_ADDR + 0xa0)              /* I2S���������ϲ���������ݼĴ��� */
#define DRV_SIO_I2S_DUAL_TX_CHN         (DRV_SIO_BASE_ADDR + 0xc0)              /* I2S�����ϲ���д�������ݼĴ���   */

#define DRV_SC_SIO_BCLK_ENABLE_REG_ADDR     (DRV_SC_BASE_ADDR+0x0024U)
#define DRV_SC_SIO_BCLK_DISABLE_REG_ADDR    (DRV_SC_BASE_ADDR+0x0028U)
#define DRV_SC_CLK_CTRL_ENABLE_REG_ADDR     (DRV_SC_BASE_ADDR+0x000CU)          /* V7R1 CS������ʱ��ʹ�ܼĴ��� */
#define DRV_SC_CLK_CTRL_DISABLE_REG_ADDR    (DRV_SC_BASE_ADDR+0x0010U)          /* V7R1 CS������ʱ�ӹرռĴ��� */

/*
SIO CTRL �Ĵ���˵��:
    b31-16 b15  b14    b13   b12     b11         b10         b9          b8
    res    rst int_en rx_en tx_en rx_fifo_dis tx_fifo_dis rx_merge_en tx_merge_en

      b7-4         b3-0
    rx_fifo_th tx_fifo_th
*/
#define DRV_SIO_GetStatusPtr()          (&g_stDrvSioCtrl.stStatus)              /* ��ȡSIO״̬�Ĵ���ָ�� */
#define DRV_SIO_GetIntIsrPtr()          (&g_stDrvSioCtrl.stIsr)                 /* ��ȡSIO�жϻص�����ȫ�ֱ���*/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ʵ������  : DRV_SIO_INT_MASK_ENUM
 ��������  : SIO�����ж�����
*****************************************************************************/
enum DRV_SIO_INT_MASK_ENUM
{
    DRV_SIO_INT_MASK_RX_INTR            = 0x1,                                  /* ����FIFO������ֵ�ж�                 */
    DRV_SIO_INT_MASK_TX_INTR            = 0x2,                                  /* ����FIFO������ֵ�ж�                 */
    DRV_SIO_INT_MASK_RX_RIGHT_FIFO_OVER = 0x4,                                  /* I2Sģʽ��Ϊ����������FIFO������ж�  */
                                                                                /* PCMģʽ��ΪPCM����FIFO������ж�     */
    DRV_SIO_INT_MASK_RX_LEFT_FIFO_OVER  = 0x8,                                  /* ����������FIFO�����,ֻ��I2Sģʽ��Ч */
    DRV_SIO_INT_MASK_TX_RIGHT_FIFO_UNDER= 0x10,                                 /* I2Sģʽ��Ϊ����������FIFO������ж�  */
                                                                                /* PCMģʽ��ΪPCM����FIFO������ж�     */
    DRV_SIO_INT_MASK_TX_LEFT_FIFO_UNDER = 0x20,                                 /* ����������FIFO�����,ֻ��I2Sģʽ��Ч */
    DRV_SIO_INT_MASK_BUTT               = 0x40
};
typedef BSP_U16 DRV_SIO_INT_MASK_ENUM_UINT16;

/*****************************************************************************
 ʵ������  : DRV_SIO_MODE_ENUM
 ��������  : SIO����ģʽ
*****************************************************************************/
enum DRV_SIO_MODE_ENUM
{
    DRV_SIO_MODE_CLOSE                  = 0,                                    /* SIOʱ�ӹر� */
    DRV_SIO_MODE_OPEN,                                                          /* SIOʱ�Ӵ� */
    DRV_SIO_MODE_BUTT
};
typedef BSP_U32 DRV_SIO_MODE_ENUM_UINT32;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : DRV_SIO_INT_FUNC
 ��������  : SIO�жϴ���ص�����
 �������  : enIntType - �ж�����, �μ�DRV_SIO_INT_TYPE_ENUM_UINT16
             uwPara    - �û�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
typedef BSP_VOID (*DRV_SIO_INT_FUNC)(
                DRV_SIO_INT_MASK_ENUM_UINT16 enIntType,
                BSP_U32                   uwPara);

/*****************************************************************************
 ʵ������  : DRV_SIO_INT_ISR_STRU
 ��������  : ����SIO�жϻص���������ʵ��
*****************************************************************************/
typedef struct
{
    DRV_SIO_INT_FUNC                    pfFunc;                                 /* �ص�����ָ�� */
    BSP_U32                          uwPara;                                 /* �ص�����     */

} DRV_SIO_INT_ISR_STRU;

/*****************************************************************************
 ʵ������  : DRV_SIO_STATUS_STRU
 ��������  : ����SIO״̬����ʵ��
*****************************************************************************/
typedef struct
{
    DRV_SIO_MODE_ENUM_UINT32            enMode;                                 /* SIOģʽ */
    BSP_U32                          uwPinCtrlStatus;                        /* ����SIO PCM�ܽſ����ֳ�ʼֵ */
    BSP_U32                          uwUartPinCtrlStatus;                    /* ����UART�ܽſ����ֳ�ʼֵ */
    BSP_U32                          uwSioClkIomgStatus;                     /* ����V3R2 CS��SIOʱ�ӹܽſ����ֳ�ʼֵ */
    BSP_U32                          uwSioDiIomgStatus;                      /* ����V3R2 CS��SIO_DIN�ܽſ����ֳ�ʼֵ */
    BSP_U32                          uwSioDoIomgStatus;                      /* ����V3R2 CS��SIO_DOUT�ܽſ����ֳ�ʼֵ */

} DRV_SIO_STATUS_STRU;

/*****************************************************************************
 ʵ������  : DRV_SIO_CTRL_STRU
 ��������  : ����SIO����ʵ��
*****************************************************************************/
typedef struct
{
    DRV_SIO_STATUS_STRU                 stStatus;                               /* ����SIOģ�����״̬ */
    DRV_SIO_INT_ISR_STRU                stIsr;                                  /* ����SIO�жϻص� */

} DRV_SIO_CTRL_STRU;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern BSP_VOID DRV_SIO_Close_A(BSP_VOID);
extern BSP_VOID DRV_SIO_Init_A(BSP_VOID);

extern BSP_VOID DRV_SIO_Open_A(
                       DRV_SIO_INT_MASK_ENUM_UINT16    enIntMask,
                       DRV_SIO_INT_FUNC                pfIntHandleFunc,
                       BSP_U32                      uwPara);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of drv_sio.h */
