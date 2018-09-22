#ifndef __MED_CTRL_PCM_H__
#define __MED_CTRL_PCM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include <linux/kernel.h>
#include "DrvInterface.h"
#include "pcm_voip_dma.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MED_CTRL_PCM_FRAME_INSERT_THD   (5)                                     /* ��֡����ֵ */
#define MED_CTRL_PCM_FRAME_WIN_LEN      (1000)                                  /* ����������ͳ�ƴ���*/

#define MED_CTRL_PCM_SHIFT_RIGHT_16     (16)                                    /* ����16λ*/
#define MED_CTRL_PCM_AHB_ADDR_INC       (4)                                     /* AHB�����ַ����*/
#define MED_CTRL_PCM_TX_BUF_SIZE_INIT   (5)                                     /* ���л���buf��ʼֵ*/
#define MED_CTRL_PCM_RX_BUF_SIZE_INIT   (3)                                     /* ���л���buf��ʼֵ*/
#define MED_CTRL_PCM_SIGNAL_RAND_RANGE  (63)                                    /* С�ź���������� */


/*****************************************************************************
 ��    ��  : MED_CTRL_PcmTransferRxDataInd
 ��������  : ֪ͨOM�����������ݰ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ****************************************************************************/
#define MED_CTRL_PcmTransferRxDataInd() \
{ \
    DRV_IPC_TrigInt(IPC_TARGET_CPU_APPARM, PC_VOICE_RX_DATA_ACPU_IPC_BIT); \
}

#define MED_CODED_FRAME_LENGTH                   ((BSP_U16)36)               /* һ֡�������������ݵ����֡������λ˫�ֽڣ�����ΪAMR_WB��72���ֽ�*/
#define MED_CODED_FRAME_WITH_OBJ_LEN             ((BSP_U16)80)               /* һ֡�������������ݵ����֡������λ˫�ֽڣ�����־*/

#define MED_CTRL_PcmGetMicInBufPtr()    (g_psMedCtrlPcmMicIn)
#define MED_CTRL_PcmGetSpkOutBufPtr()   (g_psMedCtrlPcmSpkOut)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/* 3.1 ƹ�һ���ö�� */
typedef enum
{
    MED_CTRL_PCM_BUFF_A = 0,
    MED_CTRL_PCM_BUFF_B,
    MED_CTRL_PCM_BUFF_BUTT
} MED_CTRL_PCM_BUFF_ENUM;

/* 3.2 ���˵�������ö�� */
typedef enum
{
    MED_CTRL_PCM_PLAY_TX = 0,
    MED_CTRL_PCM_PLAY_RX,
    MED_CTRL_PCM_PLAY_TXRX,
    MED_CTRL_PCM_PLAY_BUTT
} MED_CTRL_PCM_PLAY_ENUM;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


#define VOS_PCVOICE_FLG

#ifndef VOS_TEST_NB
#define VOS_TEST_NB
#endif

#define UCOM_ALIGN(bytes)               __attribute__((aligned(bytes)))

#define MED_CTRL_PCM_MAX_FRAME_LENGTH  160
#define MED_CTRL_PCM_FRAME_LENGTH          160
#define MED_CTRL_PCM_FRAME_LENGTH_DOUBLE 320

#define MED_CTRL_MC_DMAC_CHN_MIC        (9) /* �����䣬V3R2����������SIOʹ��ͨ��15 */
#define MED_CTRL_MC_DMAC_CHN_SPK        (8) /* �����䣬V3R2����������SIOʹ��ͨ��14 */

/* 7.1 PCM����buffer�ṹ�� */
typedef struct
{
    BSP_S16                           asMicInBuffA[MED_CTRL_PCM_MAX_FRAME_LENGTH];
    BSP_S16                           asMicInBuffB[MED_CTRL_PCM_MAX_FRAME_LENGTH];
    BSP_S16                           asSpkOutBuffA[MED_CTRL_PCM_MAX_FRAME_LENGTH];
    BSP_S16                           asSpkOutBuffB[MED_CTRL_PCM_MAX_FRAME_LENGTH];

} MED_CTRL_PCM_BUFFER_STRU;

/* ring buffer״̬�ṹ��*/
typedef struct
{
    BSP_U16                          uhwAdpBufferSize;                       /*����Ӧ�����С����λ��֡*/
    BSP_U16                          uhwCntDataSizeIsOne;                    /*���������ݴ�С����1�Ĵ���*/
    BSP_U16                          uhwCurrDataSize;                        /*��ǰ���������ݴ�С����λ��֡*/
    BSP_S16                           shwInsertFrameCnt;                      /*��֡��*/
    BSP_U16                          uhwFrameCnt;                            /*֡��������*/
    BSP_U16                          uhwReserved;
}MED_CTRL_PCM_RING_BUFFER_STATE_STRU;

typedef struct
{
    BSP_U16               usMicInSwEnable;
	BSP_U16               usSpkOutSwEnable;
	
}MED_CTRL_PCM_DMA_FLAG_STRU;

/* PC Voice����ṹ��*/
typedef struct
{
    BSP_U32                          uwRingBuffBaseAddr;
    MED_CTRL_PCM_RING_BUFFER_STATE_STRU stTxRingBufferState;                    /*����ring buffer״̬�ṹ��*/
    MED_CTRL_PCM_RING_BUFFER_STATE_STRU stRxRingBufferState;                    /*����ring buffer״̬�ṹ��*/
}MED_CTRL_PCM_PC_VOICE_OBJ_STRU;
/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/

#define MED_SWITCH_OFF 0
#define MED_SWITCH_ON 1


/*****************************************************************************
  10 ��������
*****************************************************************************/



extern BSP_VOID MED_CTRL_PcmInit(BSP_VOID);
extern BSP_VOID MED_CTRL_MicDmaIsr(
                       DRV_DMA_INT_TYPE_ENUM_UINT16 enIntType,
                       BSP_U32 uwPara);
extern BSP_U32 MED_CTRL_PcmMicInStartLoopDMA( BSP_U16 usChNum );
extern BSP_U32 MED_CTRL_PcmSpkOutStartLoopDMA( BSP_U16 usChNum );
extern BSP_VOID MED_CTRL_PcmSwitchMicBuff(BSP_VOID);
extern BSP_S16* MED_CTRL_PcmGetWritableSpkBuffPtr(BSP_VOID);
extern BSP_VOID MED_CTRL_PcmSwitchSpkBuff(BSP_VOID);
extern BSP_VOID MED_CTRL_PcmClrLastSpkBuff(BSP_VOID);
extern BSP_VOID MED_PCM_Ctrl_Init(BSP_VOID);
extern BSP_VOID MED_PCM_Ctrl_Start(BSP_VOID);
extern BSP_VOID MED_PCM_Ctrl_Stop(BSP_VOID);

extern BSP_VOID MED_CTRL_SpkDmaIsr(
                       DRV_DMA_INT_TYPE_ENUM_UINT16 enIntType,
                       BSP_U32 uwPara);


#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of med_pcm.h */
