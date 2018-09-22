

#ifndef __HDLC_HARDWARE_H__
#define __HDLC_HARDWARE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "hdlc_interface.h"
#include "TTFComm.h"
#include "TtfMemoryMap.h"
#if(FEATURE_ON == FEATURE_PPP)
#include "soc_hdlc_interface.h"
#endif

#if (SC_CTRL_MOD_6930_SFT == SC_CTRL_MOD)
#include "hi_syscrg.h"
#endif

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#pragma pack(4)

#ifdef FEATURE_HDLC_MASTER
/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* 1.============================================================================================ */

/* definitions of bit basic operations */
#define GET_HIGH_WORD_FROM_DWORD(l)           ((VOS_UINT16)((((VOS_UINT32)(l)) >> 16) & 0xFFFF))
#define GET_LOW_WORD_FROM_DWORD(l)           ((VOS_UINT16)(VOS_UINT32)(l))
#define GET_HIGH_BYTE_FROM_WORD(w)           ((VOS_UINT8)(((VOS_UINT16)(w) >> 8) & 0xFF))
#define GET_LOW_BYTE_FROM_WORD(w)           ((VOS_UINT8)(w))
#define HDLC_MAKE_DWORD(hi,low)    ((VOS_UINT32)(((VOS_UINT16)(low))|(((VOS_UINT32)((VOS_UINT16)(hi)))<<16)))
#define HDLC_MAKE_WORD(hi,low)    ((VOS_UINT16)(((VOS_UINT8)(low))|(((VOS_UINT16)((VOS_UINT8)(hi)))<<8)))

#define GET_BITS_FROM_DWORD(DWord, BitMask) ((DWord) & (BitMask))
#define GET_BITS_FROM_WORD(Word, BitMask) ((Word) & (BitMask))
#define GET_BITS_FROM_BYTE(Byte, BitMask)  ((Byte) & (BitMask))
#define SET_BITS_VALUE_TO_BYTE(ucValue, ucStartBitPosition)     ((VOS_UINT8)((ucValue) << (ucStartBitPosition)))

#define SET_BIT_TO_BYTE(ucByte, ucBitPosition)          ((ucByte) |= (0x01 << (ucBitPosition)))
#define CLEAR_BIT_TO_BYTE(ucByte, ucBitPosition)        ((ucByte) &= ~(0x01 << (ucBitPosition)))

#define SET_BIT_TO_WORD(usWord, ucBitPosition)          ((usWord) |= (0x0001 << (ucBitPosition)))
#define CLEAR_BIT_TO_WORD(usWord, ucBitPosition)        ((usWord) &= ~(0x0001 << (ucBitPosition)))

#define SET_BIT_TO_DWORD(ulDWord, ucBitPosition)        ((ulDWord) |= (0x00000001 << (ucBitPosition)))
#define CLEAR_BIT_TO_DWORD(ulDWord, ucBitPosition)      ((ulDWord) &= ~(0x00000001 << (ucBitPosition)))

#define INSERT_BYTE_LAST(pstMem, pstData, usLen, byte) \
{ \
    pstData[usLen]     = pstData[usLen - 1]; \
    pstData[usLen - 1] = byte; \
    PPP_ZC_SET_DATA_LEN(pstMem, 1); \
}
/* 2.============================================================================================ */

/* definition of bit positions and masks in a register */
/* ========================= 1.hdlc_frm_en (0x10) begin ======================= */
/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���frm_en��bit0;
*/
#define     HDLC_FRM_EN_BITPOS                                      (0UL)

/* ========================= 2.hdlc_def_en (0x60) begin ======================= */
/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���def_en��bit0;
*/
#define     HDLC_DEF_EN_BITPOS                                      (0UL)

/* ========================= 3.hdlc_frm_cfg (0x20) begin ======================= */
/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���frm_in_lli_1dor2d��bit0;
        �Ĵ���frm_acfc��bit1;
*/
#define     HDLC_FRM_IN_LLI_1DOR2D_BITPOS                           (0UL)
#define     HDLC_FRM_ACFC_BITPOS                                    (1UL)
#define     HDLC_FRM_PFC_BITPOS                                     (2UL)

/*
   �Ĵ���frm_pfc(2bits)��ֵ����:
        00b: Ӳ��ģ�����P��, P����ѹ��;
        01b: Ӳ��ģ�����P��, P��ѹ��;
        11b: Ӳ��ģ�鲻���P��;
*/
#define     HDLC_PROTOCOL_ADD_WITHOUT_COMPRESS   (0x00)
#define     HDLC_PROTOCOL_ADD_WITH_COMPRESS      (0x01)
#define     HDLC_PROTOCOL_NO_ADD                 (0x03)

/* ========================= 4.hdlc_def_cfg (0x70) begin ======================= */
/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���def_uncompleted_ago��bit0;
        �Ĵ���def_acfc��bit1;
*/
#define     HDLC_DEF_IS_UNCOMPLETED_AGO_BITPOS                      (0UL)
#define     HDLC_DEF_ACFC_BITPOS                                    (1UL)
#define     HDLC_DEF_PFC_BITPOS                                     (2UL)


/* �Ĵ���frm_protocol(16bits)��MASK�� */
#define     HDLC_FRM_PROTOCOL_MASK                       (0x0000FFFF)

/*
   �Ĵ���def_pfc(2bits)��ֵ����:
        00b: P����ѹ��, �����;
        01b: P��ѹ��, �����;
        11b: P�򲻰���;
*/
#define     HDLC_PROTOCOL_REMOVE_WITHOUT_COMPRESS      (0x00)
#define     HDLC_PROTOCOL_REMOVE_WITH_COMPRESS         (0x01)
#define     HDLC_PROTOCOL_NO_REMOVE                    (0x03)

/* ========================= hdlc_prior_ctrl (0x04) begin ======================= */
/*
   �Ĵ���hdlc_prior_ctrl(2bits)��ֵ����:
        00b: ˭�ȱ�ʹ�����Ƚ�˭������;
        01b: ���з�װ���ȼ���;
        10b: ���н��װ���ȼ���;
        11b: ��Ч;
*/
#define     HDLC_PRIOR_FCFS               (0x00)
#define     HDLC_PRIOR_DL_FRM_HIGHER      (0x01)
#define     HDLC_PRIOR_UL_DEF_HIGHER      (0x02)
#define     HDLC_PRIOR_INVALID            (0x03)

/* ====================== ��װ״̬�Ĵ�����ַ hdlc_frm_status (0x28) begin ====================== */
/* ��װģ��״̬�Ĵ�����ַ: ���ƫ�Ƶ�ַ��0x28 */

/* �Ĵ���frm_out_seg_num(16bits)��MASK�� */
#define     HDLC_FRM_OUT_SEG_NUM_MASK                       (0x0000FFFF)

/* �Ĵ���frm_valid_num(8bits)��MASK�� */
#define     HDLC_FRM_VALID_NUM_MASK                         (0x000000FF)

/* �Ĵ���frm_all_pkt_done(1bit)��MASK�� */
#define     HDLC_FRM_ALL_PKT_DONE_MASK                      (0x00000001)

/* ��ѯ��װ״̬��Ϣ������ */
#define     HDLC_FRM_STATUS_MASK                            (0x00000003)

/*
   �Ĵ���frm_block_done([0]λ)��ֵ����:
        0b: δ���һ���������ݴ���;
        1b: ���һ���������ݴ���;
*/
/*
   �Ĵ���frm_error_index([1]λ)��ֵ����:
        1b: ��װ��������;
*/
#define     HDLC_FRM_ALL_PKT_DOING                     (0x00)
#define     HDLC_FRM_ALL_PKT_DONE                      (0x01)
#define     HDLC_FRM_STOP_EXCEPTION_OCCUR              (0x02)
#define     HDLC_FRM_DONE_EXCEPTION_OCCUR              (0x03)




/* ======================= ���װ״̬�Ĵ�����ַdlc_def_status (0x88) begin ===================== */
/* �Ĵ���dlc_def_status(5bits)��MASK�� */
#define     HDLC_DEFRAMER_BLOCK_STATUS_MASK                     (0x0000001B)

/* ��ѯ���װ״̬��Ϣ������ */
#define     HDLC_DEF_STATUS_MASK                                (0x0000003B)

/*
   �Ĵ���dlc_def_status(5bits)��ֵ����:
        000000b: δ���һ�����ݴ���;
        010000b: δ���һ�����ݴ������װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ;
        001000b: δ���һ�����ݴ���, ���װ�ⲿ����洢�ռ������ͣ;
        000001b: δ���һ�����ݴ���, �ѽ��LCP֡, Ӳ��������ͣ״̬;
        000010b: ���һ�����ݴ���, ����֡�ϱ�;
        000011b: ���һ�����ݴ���, ����֡�ϱ�;
        1xx0xxb: ���쳣����;
*/
#define     HDLC_DEF_STATUS_DOING                               (0x00)
#define     HDLC_DEF_STATUS_PAUSE_RPT_SPACE_FULL                (0x10)
#define     HDLC_DEF_STATUS_PAUSE_OUTPUT_SPACE_FULL             (0x08)
#define     HDLC_DEF_STATUS_PAUSE_LCP                           (0x01)
#define     HDLC_DEF_STATUS_DONE_WITHOUT_FRAMES                 (0x02)
#define     HDLC_DEF_STATUS_DONE_WITH_FRAMES                    (0x03)

/* 3.============================================================================================ */
/* definition of HDLC module: FRAMER, DEFRAMER */
#define     HDLC_FRM_MODULE                                     (0UL)
#define     HDLC_DEF_MODULE                                     (1UL)

/* definition of PPP Link type */
#define     HDLC_IP_MODE                                        (0UL)
#define     HDLC_PPP_MODE                                       (1UL)

/* ���װ�Ƿ��з�����֡��ʶ */
#define     HDLC_DEF_UNCOMPLETED_NOT_EXIST                      (0x0)
#define     HDLC_DEF_UNCOMPLETED_EXIST                          (0x1)

#define     HDLC_INPUT_PARA_LINK_MAX_SIZE                       (TTF_MAX(TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM, TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM))
#define     HDLC_OUTPUT_PARA_LINK_MAX_SIZE                      (TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM)

/* ����PPP ID��ȡ��Ӧ�ڴ棬��ʱֻ��һ·����Ϊ��ֵ�����������ж�· */
#define     HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId)              (&g_stUncompletedInfo)
#define     HDLC_DEF_GET_BUF_INFO(usPppId)                      (g_pstHdlcDefBufInfo)
#define     HDLC_FRM_GET_BUF_INFO(usPppId)                      (g_pstHdlcFrmBufInfo)

/* ���װ����ռ��ס�β��ַ�������ж��Ƿ��ƻ� */
#define     HDLC_DEF_OUTPUT_BUF_START_ADDR                      ((VOS_UINT8 *)(&g_pstHdlcDefBufInfo->aucOutputDataBuf[0]))
#define     HDLC_DEF_OUTPUT_BUF_END_ADDR                        (HDLC_DEF_OUTPUT_BUF_START_ADDR + TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN)

/* ��ѯ��װ����װ��ɵĴ��� */
#ifndef  __UT_CENTER__
#define     HDLC_FRM_MAX_WAIT_RESULT_NUM                        (0xFFFF)
#define     HDLC_DEF_MAX_WAIT_RESULT_NUM                        (0xFFFF)
#else
#define     HDLC_FRM_MAX_WAIT_RESULT_NUM                        (0x01)
#define     HDLC_DEF_MAX_WAIT_RESULT_NUM                        (0x01)
#endif

/* �ȴ���װ����װ��Ӧ�ж�ʱ��,�Ժ���Ϊ��λ */
#define     HDLC_FRM_MASTER_INT_TIMER_LEN                       (5000)
#define     HDLC_DEF_MASTER_INT_TIMER_LEN                       (5000)

/* Լ����Ӳ��, ��װһ������ύ1502�ֽڸ�Framer */
#define     HDLC_FRM_IN_PER_MAX_CNT                             (1502L)
#define     HDLC_FRM_OUT_PER_MAX_CNT                            (3013UL)

/* ���װ��󵥸����ݳ���,���HDLC BUG,��󳤶���Ҫ+1 */
#define     HDLC_DEF_IN_PER_MAX_CNT                             (PPP_ZC_MAX_DATA_LEN + 1)
/* ���װ�ϱ�ÿ֡�1502�ֽ�, IPv4�1500�ֽ�, PPPģʽ����Э���ֶ�2�ֽ�, ��1502�ֽ� */
#define     HDLC_DEF_OUT_PER_MAX_CNT                            (1502UL)

/* �����װĿ�Ŀռ�ʧ�ܶ�ʱ��ʱ��,��λ���� */
#define     HDLC_FRM_TIME_INTERVAL                              (100)

/* �����װĿ�Ŀռ�ʧ�ܶ�ʱ������ */
#define     HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL                    (10)

/* ��װ���ڴ����ֵ */
#define     HDLC_FRM_GET_MAX_FRAMED_LEN(usLen)                  (2*usLen + 13)

/* ������ѯ�����ж�ʹ�ܵ�ˮ�ߣ�Ĭ��ֵ */
#define     HDLC_DEF_INTERRUPT_LIMIT_DEFAULT                    (2*1024)
#define     HDLC_FRM_INTERRUPT_LIMIT_DEFAULT                    (2*1024)

/* ������ѯ�����ж�ʹ�ܵ�ˮ�� */
#if (VOS_OS_VER == VOS_WIN32)
/* PC���޷�ģ���жϣ���ʹ�ò�ѯ */
#define     HDLC_DEF_INTERRUPT_LIMIT                            (TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE + 1)
#define     HDLC_FRM_INTERRUPT_LIMIT                            (TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_SIZE + 1)
#else
#define     HDLC_DEF_INTERRUPT_LIMIT                            (g_stHdlcConfigInfo.ulHdlcDefIntLimit)
#define     HDLC_FRM_INTERRUPT_LIMIT                            (g_stHdlcConfigInfo.ulHdlcFrmIntLimit)
#endif

/* AXI���߶�д����ʱ���ж�ֵ����ֵ��SoC�ṩ������������� */
#define     HDLC_AXI_REQ_TIMEOUT_VALUE                          (255)

/* ���װ�������͸��� */
#define     HDLC_DEF_MAX_TYPE_CNT                               (7UL)

/* ��ά�ɲ�������ڴ���󳤶ȣ���ֹ��Ϊ��ά�ɲ����벻���ڴ浼�µ��帴λ */
#define     HDLC_MNTN_ALLOC_MEM_MAX_SIZE                        (2*1024)

/*
   �����쳣��Ϣbitλ��:
        bit0�����Ƿ�����쳣����(1�ǽ����쳣����0��û�н����쳣����);
        bit1�����Ƿ����жϴ���(1���жϴ���0����ѯ����);
        bit2�����Ƿ�ȴ��ź�����ʱ(1�ǣ�0��);
        bit3�����Ƿ���ѯ��ʱ(1�ǣ�0��);
*/
#define     HDLC_EXCEPTION_IND_BITPOS                           (0UL)
#define     HDLC_INTERRUPT_IND_BITPOS                           (1UL)
#define     HDLC_SEM_TIMEOUT_IND_BITPOS                         (2UL)
#define     HDLC_WAIT_STATUS_TIMEOUT_IND_BITPOS                 (3UL)

#if ((FEATURE_OFF == FEATURE_SKB_EXP) || (FEATURE_ON == FEATURE_TTFMEM_CACHE))
#ifdef BSP_CONFIG_HI3630
#define     PPP_HDLC_CACHE_INVALID(data, len)                  dma_map_single(0, data, len, DMA_FROM_DEVICE)
#define     PPP_HDLC_CACHE_FLUSH(data, len)					   dma_map_single(0, data, len, DMA_TO_DEVICE)
#else
#define     PPP_HDLC_CACHE_INVALID(data, len)                  __dma_single_dev_to_cpu_nocheck(data, len, DMA_FROM_DEVICE)
#define     PPP_HDLC_CACHE_FLUSH(data, len)                    __dma_single_cpu_to_dev_nocheck(data, len, DMA_TO_DEVICE)
#endif
#endif

/* ======V3R3��ʹ��: HDLCʱ���ڼĴ���SC_PERIPH_CLKEN0 �� C_PERIPH_CLKDIS0 16bit��λ��======== */
#define     HDLC_PERIPH_CLK_BITPOS                              (16UL)

/* ======V7R2��ʹ��: HDLCʱ���ڼĴ���CRG_CLKEN4 �� CRG_CLKDIS4 10bit��λ��======== */
#define     HDLC_CRG_CLK_BITPOS                                 (10UL)

#if (SC_CTRL_MOD_6930_SFT == SC_CTRL_MOD)
/* ======V7R2�е�ʱ��ʹ�ܼĴ���======== */
#define     HDLC_CRG_CLKEN4_ADDR(base)                          ((base) + (HI_CRG_CLKEN4_OFFSET))

/* ======V7R2�е�ʱ�ӹرռĴ���======== */
#define     HDLC_CRG_CLKENDIS4_ADDR(base)                       ((base) + (HI_CRG_CLKDIS4_OFFSET))

/* ======V7R2�е�ʱ��״̬�Ĵ���======== */
#define     HDLC_CRG_CLKSTA4_ADDR(base)                         ((base) + (HI_CRG_CLKSTAT4_OFFSET))

#endif



/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
enum PPP_HDLC_PARA_CHECK_RESULT_ENUM
{
    PPP_HDLC_PARA_CHECK_PASS            = 0,      /* ��������Ҫ�󣬽������ݳ��� */
    PPP_HDLC_PARA_CHECK_FAIL_DISCARD    = 1,      /* ���ݰ�����������Ҫ����Ҫ���������Ǽ���������һ�����ݰ� */
    PPP_HDLC_PARA_CHECK_FAIL_KEEP       = 2,      /* ���ݰ�����������Ҫ�󣬵���Ҫ�����������´δ��� */

    PPP_HDLC_PARA_CHECK_BUTT
};
typedef VOS_UINT32   PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32;

enum HDLC_MNTN_EVENT_TYPE_ENUM
{
    ID_HDLC_MNTN_FRM_REG_BEFORE_EN     = 101,     /* _H2ASN_MsgChoice HDLC_MNTN_FRM_REG_CONFIG_STRU */
    ID_HDLC_MNTN_FRM_REG_AFTER_EN,                /* _H2ASN_MsgChoice HDLC_MNTN_FRM_REG_CONFIG_STRU */
    ID_HDLC_MNTN_FRM_INPUT_PARA,                  /* _H2ASN_MsgChoice HDLC_MNTN_INPUT_PARA_LINK_STRU */
    ID_HDLC_MNTN_FRM_OUTPUT_PARA,                 /* _H2ASN_MsgChoice HDLC_MNTN_FRM_OUTPUT_PARA_STRU */
    ID_HDLC_MNTN_FRM_INPUT_DATA,                  /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_FRM_OUTPUT_DATA,                 /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_DEF_REG_BEFORE_EN,               /* _H2ASN_MsgChoice HDLC_MNTN_DEF_REG_CONFIG_STRU */
    ID_HDLC_MNTN_DEF_REG_AFTER_EN,                /* _H2ASN_MsgChoice HDLC_MNTN_DEF_REG_CONFIG_STRU */
    ID_HDLC_MNTN_DEF_INPUT_PARA,                  /* _H2ASN_MsgChoice HDLC_MNTN_INPUT_PARA_LINK_STRU */
    ID_HDLC_MNTN_DEF_OUTPUT_PARA,                 /* _H2ASN_MsgChoice HDLC_MNTN_DEF_OUTPUT_PARA_STRU */
    ID_HDLC_MNTN_DEF_INPUT_DATA,                  /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_DEF_OUTPUT_DATA,                 /* _H2ASN_MsgChoice HDLC_MNTN_NODE_DATA_STRU */
    ID_HDLC_MNTN_DEF_UNCOMPLETED_INFO,            /* _H2ASN_MsgChoice HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU */

    ID_HDLC_MNTN_EVENT_TYPE_BUTT         = 0xFFFF
};
typedef VOS_UINT32 HDLC_MNTN_EVENT_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 ��Ϣͷ����Ϣ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  5 STRUCT����
*****************************************************************************/
/* һ�����ݽ���Ĵ���֡��ͳ�� */
typedef struct
{
    VOS_UINT16  usFCSErrCnt;          /* FCS���� */
    VOS_UINT16  usLenLongCnt;         /* ֡���ȹ���, ����1502�ֽ� */
    VOS_UINT16  usLenShortCnt;        /* ֡���ȹ���, ����4�ֽ� */
    VOS_UINT16  usErrProtocolCnt;     /* Э���ֶβ�����xxxxxxx0, xxxxxxx1����ʽ */
    VOS_UINT16  usErrCtrlCnt;         /* �����ֶβ�Ϊ0xFF */
    VOS_UINT16  usErrAddrCnt;         /* ��ַ�ֶβ�Ϊ0x03 */
    VOS_UINT16  usFlagPosErrCnt;      /* 0x7D�������0x7E */
    VOS_UINT8   aucReserve[2];
} HDLC_DEF_ERR_FRAMES_CNT_STRU;

/*
   ��������ڵ�ṹ:
   �����֤���װ�������������ʼ��ַWord���룻(�μ�HiHDLCV200�߼�������˵����)��
   ���ϵ��£���ַ���ӣ��ֱ�Ϊ�ڵ��ڴ�ָ�롢�ڵ㳤�ȡ��¸��ڵ��ַ��
   ����LEN��Ч16bits���ڵ�Half_Word����ַADDR 32bits
*/
typedef struct _HDLC_PARA_LINK_NODE_STRU
{
    VOS_UINT8                          *pucDataAddr;            /* �ò����ڵ�ָ���ڴ��ַ */
    VOS_UINT16                          usDataLen;              /* �ڴ泤�ȣ���λByte */
    VOS_UINT8                           aucReserve[2];
    struct _HDLC_PARA_LINK_NODE_STRU   *pstNextNode;            /* ָ����һ�������ڵ��ָ�� */
} HDLC_PARA_LINK_NODE_STRU;

/* ���������������Ϣ */
typedef struct _HDLC_PARA_LINK_BUILD_PARA_STRU
{
    PPP_DATA_TYPE_ENUM_UINT8            ucDataType;             /* �������� */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usPppId;                /* PPP ID */
    VOS_UINT16                          usProtocol;             /* Э�����ͣ���װ��ʱ��ʹ�� */
    PPP_ZC_QUEUE_STRU                  *pstDataQ;               /* ���ݶ��� */
} HDLC_PARA_LINK_BUILD_PARA_STRU;

/* ���������������Ϣ */
/*lint -e506*/
typedef struct _HDLC_PARA_LINK_BUILD_INFO_STRU
{
    VOS_UINT32                          ulDealCnt;              /* ���ι���������̴����ݶ������ܹ���������ݰ����� */
    VOS_UINT32                          ulInputLinkNodeCnt;     /* �����������ڵ���� */
    VOS_UINT32                          ulInputLinkTotalSize;   /* �����������ڵ����ݰ��ܳ��� */
    PPP_ZC_STRU *                       apstInputLinkNode[HDLC_INPUT_PARA_LINK_MAX_SIZE];   /* �����������ڵ��Ӧ���㿽���ڴ� */
    VOS_UINT32                          ulOutputLinkNodeCnt;                                /* �����������ڵ������ֻ�ڷ�װ��Ч */
    VOS_UINT32                          ulOutputLinkTotalSize;                              /* �����������ڵ����ݰ��ܳ��ȣ�ֻ�ڷ�װ��Ч */
    PPP_ZC_STRU *                       apstOutputLinkNode[HDLC_OUTPUT_PARA_LINK_MAX_SIZE]; /* �����������ڵ��Ӧ���㿽���ڴ棬ֻ�ڷ�װ��Ч */
} HDLC_PARA_LINK_BUILD_INFO_STRU;
/*lint +e506*/

/*
��װ�ϱ��ռ���ṹ:
�����֤��װ�ϱ��ռ���ʼ��ַWord���룻(�μ�HiHDLCV200�߼�������˵����)��
���ϵ��£���ַ���ӣ��ֱ�Ϊ���������ʼ��ַ�����ݳ��ȣ�
����LEN��Ч16bits���ڵ�Half_Word����ַADDR 32bits
*/
typedef struct
{
    VOS_UINT8                          *pucFrmOutOneAddr;       /* ָ���װ������Ч֡������洢��ʼ��ַ */
    VOS_UINT16                          usFrmOutOneLen;         /* ��Ч֡�ĳ��� */
    VOS_UINT8                           aucReserve[2];
} HDLC_FRM_RPT_NODE_STRU;

/* �����װʹ�õ��ڴ� */
typedef struct
{
    HDLC_PARA_LINK_NODE_STRU            astInputParaLinkNodeBuf[TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM];  /* ��װ�����������ʹ�õ��ڴ� */
    HDLC_FRM_RPT_NODE_STRU              astRptNodeBuf[TTF_HDLC_FRM_RPT_MAX_NUM];                        /* ��װ��Ϣ�ϱ��ռ�ʹ�õ��ڴ� */
    HDLC_PARA_LINK_NODE_STRU            astOutputParaLinkNodeBuf[TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM];/* ��װ�����������ʹ�õ��ڴ� */
} HDLC_FRM_BUFF_INFO_STRU;


/*
���װ�ϱ��ռ���ṹ:
�����֤���װ�ϱ��ռ���ʼ��ַWord���룻(�μ�HiHDLCV200�߼�������˵����)��
���ϵ��£���ַ���ӣ��ֱ�Ϊ�������Э�����͡����Ⱥʹ洢��ַ��
����LEN��Ч16bits���ڵ�Half_Word��Э��PRO��Ч16bits���ڸ�Half-Word����ַADDR 32bits
*/
typedef struct
{
    VOS_UINT16                          usDefOutOneLen;         /* ��Ч֡�ĳ��� */
    VOS_UINT16                          usDefOutOnePro;         /* ��Ч֡��Э�� */
    VOS_UINT8                          *pucDefOutOneAddr;       /* ָ����װ������Ч֡����洢����ʼ��ַ */
} HDLC_DEF_RPT_NODE_STRU;


/* ���װ������֡��Ϣ�洢�ṹ */
typedef struct
{
    VOS_UINT8                           ucExistFlag;            /* ������֡�Ƿ���ڱ�ʶ */
    VOS_UINT8                           aucReserve1[3];
    VOS_UINT16                          usDefOutOnePro;         /* ������֡��Э�� */
    VOS_UINT16                          usDefOutOneLen;         /* ������֡�ĳ��� */
    VOS_UINT8                          *pucDefOutOneAddr;       /* ָ����װ���ķ�����֡����洢����ʼ��ַ */
    VOS_UINT32                          ulDefStAgo;             /* ���ڱ���def_uncomplet_st_now�Ĵ���ֵ */
    VOS_UINT32                          ulDefInfoFrlCntAgo;     /* ���ڱ���def_info_frl_cnt_ago�Ĵ���ֵ */
} HDLC_DEF_UNCOMPLETED_INFO_STRU;

/* ������װʹ�õ��ڴ� */
typedef struct
{
    HDLC_PARA_LINK_NODE_STRU            astInputParaLinkNodeBuf[TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM];/* ���װ�����������ʹ�õ��ڴ� */
    HDLC_DEF_RPT_NODE_STRU              astRptNodeBuf[TTF_HDLC_DEF_RPT_MAX_NUM];                      /* ���װ��Ϣ�ϱ��ռ�ʹ�õ��ڴ� */
    VOS_UINT8                           aucOutputDataBuf[TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN];           /* ���װĿ�Ŀռ�ʹ�õ��ڴ� */
} HDLC_DEF_BUFF_INFO_STRU;

/* ������������ά�ɲ�ṹ */
typedef struct
{
    VOS_MSG_HEADER                                              /* ��Ϣͷ */
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulMsgname;
}HDLC_MNTN_TRACE_HEAD_STRU;

/* ��װ��ؼĴ�����ά�ɲ�ṹ */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                     /* _H2ASN_Skip */
    VOS_UINT32                          ulStateSwRst;
    VOS_UINT32                          ulPriorTimeoutCtrl;
    VOS_UINT32                          ulRdErrCurrAddr;
    VOS_UINT32                          ulWrErrCurrAddr;
    VOS_UINT32                          ulHdlcFrmEn;
    VOS_UINT32                          ulHdlcFrmRawInt;
    VOS_UINT32                          ulHdlcFrmIntStatus;
    VOS_UINT32                          ulHdlcFrmIntClr;
    VOS_UINT32                          ulHdlcFrmCfg;
    VOS_UINT32                          ulHdlcFrmAccm;
    VOS_UINT32                          ulHdlcFrmStatus;
    VOS_UINT32                          ulFrmInLliAddr;
    VOS_UINT32                          ulFrmInSublliAddr;
    VOS_UINT32                          ulFrmInPktLen;
    VOS_UINT32                          ulFrmInBlkAddr;
    VOS_UINT32                          ulFrmInBlkLen;
    VOS_UINT32                          ulFrmOutLliAddr;
    VOS_UINT32                          ulFrmOutSpaceAddr;
    VOS_UINT32                          ulFrmOutSpaceDep;
    VOS_UINT32                          ulFrmRptAddr;
    VOS_UINT32                          ulFrmRptDep;
} HDLC_MNTN_FRM_REG_CONFIG_STRU;

/* ���װ��ؼĴ�����ά�ɲ�ṹ */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                     /* _H2ASN_Skip */
    VOS_UINT32                          ulStateSwRst;
    VOS_UINT32                          ulPriorTimeoutCtrl;
    VOS_UINT32                          ulRdErrCurrAddr;
    VOS_UINT32                          ulWrErrCurrAddr;
    VOS_UINT32                          ulHdlcDefEn;
    VOS_UINT32                          ulHdlcDefRawInt;
    VOS_UINT32                          ulHdlcDefIntStatus;
    VOS_UINT32                          ulHdlcDefIntClr;
    VOS_UINT32                          ulHdlcDefCfg;
    VOS_UINT32                          ulDefUncompletedLen;
    VOS_UINT32                          ulDefUncompletedPro;
    VOS_UINT32                          ulDefUncompletedAddr;
    VOS_UINT32                          ulDefUncompleteStAgo;
    VOS_UINT32                          ulHdlcDefGoOn;
    VOS_UINT32                          ulHdlcDefStatus;
    VOS_UINT32                          ulDefUncompletStNow;
    VOS_UINT32                          ulDefInLliAddr;
    VOS_UINT32                          ulDefInPktAddr;
    VOS_UINT32                          ulDefInPktLen;
    VOS_UINT32                          ulDefInPktLenMax;
    VOS_UINT32                          ulDefOutSpcAddr;
    VOS_UINT32                          ulDefOutSpaceDep;
    VOS_UINT32                          ulDefRptAddr;
    VOS_UINT32                          ulDefRptDep;
    VOS_UINT32                          ulHdlcDefErrInfor0;
    VOS_UINT32                          ulHdlcDefErrInfor1;
    VOS_UINT32                          ulHdlcDefErrInfor2;
    VOS_UINT32                          ulHdlcDefErrInfor3;
    VOS_UINT32                          ulDefInfoFr1CntAgo;
    VOS_UINT32                          ulDefInfoFr1CntNow;
} HDLC_MNTN_DEF_REG_CONFIG_STRU;

/* ���������������ݹ���*/
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT16                          usNodeIndex;
    VOS_UINT16                          usLen;
    /* VOS_UINT8[usLen]�������ݷ�����������ʱ����ͷ�����������ݳ��� */
}HDLC_MNTN_NODE_DATA_STRU;

/* ������������ά�ɲ�ṹ */
/*lint -e506*/
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT32                          ulInputLinkNodeCnt;     /* �����������ڵ���� */
    VOS_UINT32                          ulInputLinkTotalSize;   /* �����������ڵ����ݰ��ܳ��� */
    HDLC_PARA_LINK_NODE_STRU            astInputParaLinkNodeBuf[HDLC_INPUT_PARA_LINK_MAX_SIZE];
}HDLC_MNTN_INPUT_PARA_LINK_STRU;
/*lint +e506*/

/* ��װ��������ά�ɲ�ṹ */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT8                           ucFrmValidNum;
    VOS_UINT8                           ucReserve1[1];
    VOS_UINT16                          usOutputNodeUsedCnt;
    VOS_UINT32                          ulOutputLinkNodeCnt;    /* �����������ڵ������ֻ�ڷ�װ��Ч */
    VOS_UINT32                          ulOutputLinkTotalSize;  /* �����������ڵ����ݰ��ܳ��ȣ�ֻ�ڷ�װ��Ч */
    HDLC_PARA_LINK_NODE_STRU            astOutputParaLinkNodeBuf[TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM];/* ��װ�����������ʹ�õ��ڴ� */
    HDLC_FRM_RPT_NODE_STRU              astRptNodeBuf[TTF_HDLC_FRM_RPT_MAX_NUM];                        /* ��װ��Ϣ�ϱ��ռ�ʹ�õ��ڴ� */
}HDLC_MNTN_FRM_OUTPUT_PARA_STRU;

/* ���װ������֡��ά�ɲ�ṹ */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    HDLC_DEF_UNCOMPLETED_INFO_STRU      stUncompletedInfo;
}HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU;

/* ���װ��������ά�ɲ�ṹ */
typedef struct
{
    HDLC_MNTN_TRACE_HEAD_STRU           stHead;                         /* _H2ASN_Skip */
    VOS_UINT16                          usDefValidNum;
    VOS_UINT16                          usTraceNum;
    /* HDLC_DEF_RPT_NODE_STRU[usDefValidNum]�˴�Ϊ��װ��Ϣ�ϱ��ռ�ʹ�õ��ڴ棬
       �����ڴ�ʱ�ɽṹ���ȼ��ϱ��ռ���Ҫ���ڴ��С */
}HDLC_MNTN_DEF_OUTPUT_PARA_STRU;

/* HDLC���������Ϣ�ṹ */
typedef struct
{
    VOS_UINT32                          ulHDLCIPBaseAddr;      /* �ӵ����ȡ��HDLC����ַ */
    VOS_UINT32                          ulHdlcDefMasterSem;    /* ���װ�ź��� */
    VOS_UINT32                          ulHdlcFrmMasterSem;    /* ��װ�ź��� */
    VOS_INT32                           slHdlcISRDef;          /* ���װ�жϺ� */
    VOS_INT32                           slHdlcISRFrm;          /* ��װ�жϺ� */
    VOS_UINT32                          ulHdlcDefIntLimit;     /* ���װ�ж�ˮ�� */
    VOS_UINT32                          ulHdlcFrmIntLimit;     /* ��װ�ж�ˮ�� */
    HTIMER                              stHdlcFrmTimerHandle;  /* �����װĿ�Ŀռ�ʧ�ܶ�ʱ����� */
    VOS_UINT32                          ulHdlcMntnTraceCfg;    /* ��ά�ɲ�ȼ����� */
}HDLC_CONFIG_INFO_STRU;

/* ͳ����Ϣ */
typedef struct
{
    VOS_UINT32                  ulDefIpDataProcCnt;             /* ���װIP���ݰ�������� */
    VOS_UINT32                  ulDefPppDataProcCnt;            /* ���װ��PPP֡������� */
    VOS_UINT32                  ulDefUncompleteCnt;             /* ���װ�з�����֡������� */
    VOS_UINT32                  ulDefWaitIntCnt;                /* ���װ�ȴ��жϴ��� */
    VOS_UINT32                  ulDefWaitQueryCnt;              /* ���װ�ȴ���ѯ���� */
    VOS_UINT32                  ulDefLcpPauseCnt;               /* ���װLCP��ͣ���� */
    VOS_UINT32                  ulDefFullPauseCnt;              /* ���װ����ռ���ϱ��ռ�����ͣ���� */
    VOS_UINT32                  ulDefInputDiscardCnt;           /* ���װ�������ݰ����� */

    VOS_UINT32                  ulFrmIpDataProcCnt;             /* ��װIP���ݰ�������� */
    VOS_UINT32                  ulFrmPppDataProcCnt;            /* ��װ��PPP֡������� */
    VOS_UINT32                  ulFrmWaitIntCnt;                /* ��װ�ȴ��жϴ��� */
    VOS_UINT32                  ulFrmWaitQueryCnt;              /* ��װ�ȴ���ѯ���� */
    VOS_UINT32                  ulFrmAllocOutputMemFailCnt;     /* ��װ����Ŀ���ڴ�ʧ�ܴ��� */
    VOS_UINT32                  ulFrmAllocFirstMemFailCnt;      /* ��װ�����һ���ڵ�Ŀ���ڴ�ʧ�ܴ��� */
    VOS_UINT32                  ulFrmOutputLinkFullCnt;         /* ��װ������������� */
    VOS_UINT32                  ulFrmInputDiscardCnt;           /* ��װ�������ݰ����� */

    VOS_UINT32                  ulDefMaxInputCntOnce;           /* ���װһ������������ݸ��� */
    VOS_UINT32                  ulDefMaxInputSizeOnce;          /* ���װһ��������������ܳ��� */
    VOS_UINT32                  ulDefMaxValidCntOnce;           /* ���װһ����������Ч֡���� */
    VOS_UINT32                  ulDefMaxQueryCnt;               /* ���װ��ѯ������ */

    VOS_UINT32                  ulFrmMaxInputCntOnce;           /* ��װһ������������ݸ��� */
    VOS_UINT32                  ulFrmMaxInputSizeOnce;          /* ��װһ��������������ܳ��� */
    VOS_UINT32                  ulFrmMaxOutputCntOnce;          /* ��װһ��������ʹ�ýڵ������� */
    VOS_UINT32                  ulFrmMaxOutputSizeOnce;         /* ��װһ��������ʹ�ýڵ��ܳ��� */
    VOS_UINT32                  ulFrmMaxQueryCnt;               /* ��װ��ѯ������ */

    VOS_UINT32                  ulMaxCntOnce;                   /* PPPһ����ദ��Ľ����� */
    VOS_UINT32                  ulHdlcHardProcCnt;              /* PPPһ����ദ��Ľ����� */

    VOS_UINT32                  ulDefIsrCnt;                    /* ���װ�жϷ��������ô��� */
    VOS_UINT32                  ulFrmIsrCnt;                    /* ��װ�жϷ��������ô��� */
    VOS_UINT32                  ulContinueCnt;                  /* �����е�������Ҫ�ֶ�δ���Ĵ��� */
    VOS_UINT16                  usDefExpInfo;                   /* ���װ�쳣��Ϣ */
    VOS_UINT16                  usFrmExpInfo;                   /* ��װ�쳣��Ϣ */
    VOS_UINT32                  ulForbidHdlcBugNoCpy;           /* ���HDLC BUG,���������� */
    VOS_UINT32                  ulForbidHdlcBugCpy;             /* ���HDLC BUG,��Ҫ�������� */
} PPP_HDLC_HARD_DATA_PROC_STAT_ST;

/* HDLC�ؼ��Ĵ�����ά�ɲ���Ϣ����ṹ */
typedef struct
{
    VOS_UINT32                          ulHdlcFrmRawInt;        /* ��װԭʼ�жϼĴ���ֵ */
    VOS_UINT32                          ulHdlcFrmStatus;        /* ��װ״̬�Ĵ���ֵ */
    VOS_UINT32                          ulHdlcDefRawInt;        /* ���װԭʼ�жϼĴ���ֵ */
    VOS_UINT32                          ulHdlcDefStatus;        /* ���װ״̬�Ĵ���ֵ */
}HDLC_REG_SAVE_INFO_STRU;

/*****************************************************************************
  6 ȫ�ֱ�������
*****************************************************************************/
extern HDLC_CONFIG_INFO_STRU                          g_stHdlcConfigInfo;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 PPP_HDLC_HARD_Init(VOS_VOID);

extern VOS_VOID   PPP_HDLC_HARD_SetUp(PPP_ID usPppId);

extern VOS_VOID   PPP_HDLC_HARD_Disable(VOS_VOID);

extern PPP_HDLC_RESULT_TYPE_ENUM_UINT32 PPP_HDLC_HARD_ProcData
(
    PPP_ID usPppId,
    struct link *pstLink,
    PPP_ZC_QUEUE_STRU *pstDataQ
);

extern VOS_VOID PPP_HDLC_HARD_ProcProtocolPacket
(
    struct link     *pstLink,
    struct ppp_mbuf *pstMbuf,
    VOS_INT32       ulPri,
    VOS_UINT16      ulProtocol
);

extern VOS_VOID PPP_HDLC_HARD_ProcAsFrmPacket
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
);

extern VOS_VOID PPP_HDLC_HARD_PeriphClkOpen(VOS_VOID);
extern VOS_VOID PPP_HDLC_HARD_PeriphClkClose(VOS_VOID);

extern VOS_UINT32 PPP_PHY_TO_VIRT(unsigned int ulPAddr);

extern VOS_UINT32 PPP_VIRT_TO_PHY(unsigned int ulVAddr);

#else
/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* definitions of bit basic operations */
#define GET_HIGH_WORD_FROM_DWORD(l)           ((VOS_UINT16)((((VOS_UINT32)(l)) >> 16) & 0xFFFF))
#define GET_LOW_WORD_FROM_DWORD(l)           ((VOS_UINT16)(VOS_UINT32)(l))
#define GET_HIGH_BYTE_FROM_WORD(w)           ((VOS_UINT8)(((VOS_UINT16)(w) >> 8) & 0xFF))
#define GET_LOW_BYTE_FROM_WORD(w)           ((VOS_UINT8)(w))
#define HDLC_MAKE_DWORD(hi,low)    ((VOS_UINT32)(((VOS_UINT16)(low))|(((VOS_UINT32)((VOS_UINT16)(hi)))<<16)))
#define HDLC_MAKE_WORD(hi,low)    ((VOS_UINT16)(((VOS_UINT8)(low))|(((VOS_UINT16)((VOS_UINT8)(hi)))<<8)))

#define GET_BITS_FROM_DWORD(DWord, BitMask) ((DWord) & (BitMask))
#define GET_BITS_FROM_WORD(Word, BitMask) ((Word) & (BitMask))
#define GET_BITS_FROM_BYTE(Byte, BitMask)  ((Byte) & (BitMask))
#define SET_BITS_VALUE_TO_BYTE(ucValue, ucStartBitPosition)     ((VOS_UINT8)((ucValue) << (ucStartBitPosition)))

#define SET_BIT_TO_BYTE(ucByte, ucBitPosition)          ((ucByte) |= (0x01 << (ucBitPosition)))
#define CLEAR_BIT_TO_BYTE(ucByte, ucBitPosition)        ((ucByte) &= ~(0x01 << (ucBitPosition)))

#define SET_BIT_TO_WORD(usWord, ucBitPosition)          ((usWord) |= (0x0001 << (ucBitPosition)))
#define CLEAR_BIT_TO_WORD(usWord, ucBitPosition)        ((usWord) &= ~(0x0001 << (ucBitPosition)))

#define SET_BIT_TO_DWORD(ulDWord, ucBitPosition)        ((ulDWord) |= (0x00000001 << (ucBitPosition)))
#define CLEAR_BIT_TO_DWORD(ulDWord, ucBitPosition)      ((ulDWord) &= ~(0x00000001 << (ucBitPosition)))


/* added HDLC register value definition here */
#define     HDLC_FRAMER_ENABLE                          (0x01)
#define     HDLC_FRAMER_DISABLE                         (0x00)

/* definition of HDLC module: FRAMER, DEFRAMER */
#define     HDLC_FRAMER_MODULE                          (0UL)
#define     HDLC_DEFRAMER_MODULE                        (1UL)

/* definition of PPP Link type */
#define     HDLC_IP_MODE                                (0UL)
#define     HDLC_PPP_MODE                               (1UL)

/* definition of wait times of HDLC */
#define     HDLC_FRAMER_MAX_WAIT_RESULT_NUM             (0xFFFF)
#define     HDLC_DEFRAMER_MAX_WAIT_RESULT_NUM           (0xFFFF)

/* definition of data packet or frame type */
#define     HDLC_IP_FRAME_CHOSEN                        (0UL)
#define     HDLC_NOT_IP_FRAME_CHOSEN                    (1UL)

/* Լ����Ӳ��, ��װһ������ύ1502�ֽڸ�Framer */
#define     HDLC_FRAMER_IN_PER_MAX_CNT                  (1502L)

#define     HDLC_FRAMER_OUT_PER_MAX_CNT                 (3013UL)

/* Լ����Ӳ��, ���װһ������ύ3013�ֽڸ�Deframer */
#define     HDLC_DEFRAMER_IN_PER_MAX_CNT                (3013UL)

#define     HDLC_DEFRAMER_OUT_LIST_MAX_CNT              (603UL)

#define     HDLC_DEFRAMER_OUT_ALL_FRAMES_MAX_USED_BYTES (6414UL)

/* ��װ�ϱ�ÿ֡�1502�ֽ�, IPv4�1500�ֽ�, PPPģʽ����Э���ֶ�2�ֽ�, ��1502�ֽ� */
#define     HDLC_FRAMER_IN_PER_FRAME_MAX_USED_BYTES     (1502UL)

/* ���װ����һ���4096�ֽ�, �����ɵ�����ƹ������ */
#define     HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES  (4096UL)

/* ���װ�ϱ�ÿ֡�1502�ֽ�, IPv4�1500�ֽ�, PPPģʽ����Э���ֶ�2�ֽ�, ��1502�ֽ� */
#define     HDLC_DEFRAMER_OUT_PER_FRAME_MAX_USED_BYTES  (1502UL)


#define     HDLC_DEFRAMER_PER_FRAME_INFO_DWORD_USE      (2UL)   /* ���װ�ϱ��б���ÿ֡��Ϣռ��2��DWORD */
#define     HDLC_DEFRAMER_PER_FRAME_ADDR_DWORD_OFFSET   (1UL)   /* ���װ�ϱ��б���ÿ֡��ַ���ƫ��: 1��DWORD */

#define     HDLC_DEFRAMER_MAX_TYPE_CNT                  (7UL)


/* definition of bit positions and masks in a register */
/* ========================= hdlc_int_en (0x04) begin ======================= */
/* HDLCģ���ж�ʹ�ܼĴ�����ַ: ���ƫ�Ƶ�ַ��0x04 */

/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���frm_len_err0_en��bit0;
        �Ĵ���frm_len_err1_en��bit1;
        �Ĵ���frm_cfg_err_en��bit2;
        �Ĵ���def_len_err0_en��bit8;
        �Ĵ���def_len_err1_en��bit9;
        �Ĵ���def_cfg_err_en��bit10;
*/
#define     HDLC_INTERRUPT_FRAMER_DATA_LEN_SHORT_ERR_EN_BITPOS      (0UL)
#define     HDLC_INTERRUPT_FRAMER_DATA_LEN_LONG_ERR_EN_BITPOS       (1UL)
#define     HDLC_INTERRUPT_FRAMER_PARA_ERR_EN_BITPOS                (2UL)
#define     HDLC_INTERRUPT_DEFRAMER_DATA_LEN_SHORT_ERR_EN_BITPOS    (8UL)
#define     HDLC_INTERRUPT_DEFRAMER_DATA_LEN_LONG_ERR_EN_BITPOS     (9UL)
#define     HDLC_INTERRUPT_DEFRAMER_PARA_ERR_EN_BITPOS              (10UL)
/* ========================== hdlc_int_en (0x04) end ======================== */


/* ========================= hdlc_int_raw_data (0x08) begin ======================= */
/* HDLCģ���ж�ʹ�ܼĴ�����ַ: ���ƫ�Ƶ�ַ��0x08 */
/* ========================== hdlc_int_status (0x08) end ======================== */


/* ========================= hdlc_int_status (0x0C) begin ======================= */
/* HDLCģ���ж�ʹ�ܼĴ�����ַ: ���ƫ�Ƶ�ַ��0x0C */
/* ========================== hdlc_int_status (0x0C) end ======================== */


/* ====================== hdlc_int_clr (0x10) begin ===================== */
/* HDLCģ���ж�����Ĵ�����ַ: ���ƫ�Ƶ�ַ��0x10 */

/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���frm_len_err0_clr��bit0;
        �Ĵ���frm_len_err1_clr��bit1;
        �Ĵ���frm_cfg_err_clr��bit2;
        �Ĵ���def_len_err0_clr��bit8;
        �Ĵ���def_len_err1_clr��bit9;
        �Ĵ���def_cfg_err_clr��bit10;
*/
#define     HDLC_INTERRUPT_FRAMER_DATA_LEN_SHORT_ERR_CLEAR_BITPOS      (0UL)
#define     HDLC_INTERRUPT_FRAMER_DATA_LEN_LONG_ERR_CLEAR_BITPOS       (1UL)
#define     HDLC_INTERRUPT_FRAMER_PARA_ERR_CLEAR_BITPOS                (2UL)
#define     HDLC_INTERRUPT_DEFRAMER_DATA_LEN_SHORT_ERR_CLEAR_BITPOS    (8UL)
#define     HDLC_INTERRUPT_DEFRAMER_DATA_LEN_LONG_ERR_CLEAR_BITPOS     (9UL)
#define     HDLC_INTERRUPT_DEFRAMER_PARA_ERR_CLEAR_BITPOS              (10UL)

/* ======================= hdlc_int_frm_clr (0x10) end ====================== */


/* ======================== hdlc_frm_cfg(0x20) begin ======================== */
/* ��װģ�����üĴ�����ַ: ���ƫ�Ƶ�ַ��0x20 */

/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���frm_en��bit0;
        �Ĵ���frm_acfc��bit1;
*/
#define     HDLC_FRAMER_CFG_EN_BITPOS                  (0UL)
#define     HDLC_FRAMER_CFG_ACFC_BITPOS                (1UL)

/*
   �Ĵ���frm_pfc��hdlc_frm_cfg��bit2, bit3,
   ���bit0ƫ��2bits
*/
#define     HDLC_FRAMER_CFG_PFC_MOVEBITS_LEN            (2UL)

/*
   �Ĵ���frm_pfc(2bits)��ֵ����:
        00b: Ӳ��ģ�����P��, P����ѹ��;
        01b: Ӳ��ģ�����P��, P��ѹ��;
        11b: Ӳ��ģ�鲻���P��;
*/
#define     HDLC_PROTOCOL_ADD_WITHOUT_COMPRESS   (0x00)
#define     HDLC_PROTOCOL_ADD_WITH_COMPRESS      (0x01)
#define     HDLC_PROTOCOL_NO_ADD                 (0x03)
/* ========================= hdlc_frm_cfg(0x20) end ========================= */


/* ======================== hdlc_frm_accm(0x24) begin ======================= */
/* ��װģ��ת��ʹ�ܼĴ�����ַ: ���ƫ�Ƶ�ַ��0x24 */
/* ========================= hdlc_frm_accm(0x24) end ======================== */


/* ======================= hdlc_frm_ctrl (0x28) begin ======================= */
/* ��װģ����ƼĴ�����ַ: ���ƫ�Ƶ�ַ��0x28 */

/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���frm_block_new��bit0;
*/
#define     HDLC_FRAMER_CTRL_BLK_NEW_BITPOS             (0UL)

/*
   �Ĵ���frm_block_index��hdlc_frm_ctrl��bit12-bit14,
   ���bit8ƫ��4bits
*/
#define     HDLC_FRAMER_CTRL_BLK_IDX_MOVEBITS_LEN            (4UL)

/*
   �Ĵ���frm_block_num��hdlc_frm_ctrl��bit8-bit10,
   ���bit8ƫ��0bits
*/
#define     HDLC_FRAMER_CTRL_BLK_CNT_MOVEBITS_LEN            (0UL)
/* ======================== hdlc_frm_ctrl (0x28) end ======================== */


/* ====================== hdlc_frm_status (0x2C) begin ====================== */
/* ��װģ��״̬�Ĵ�����ַ: ���ƫ�Ƶ�ַ��0x2C */

/* �Ĵ���frm_frm_length(10bits)��MASK�� */
#define     HDLC_FRAMER_BLOCK_LENGTH_MASK                 (0x000003FF)

/* �Ĵ���frm_block_done(1bit)��MASK�� */
#define     HDLC_FRAMER_BLOCK_DONE_MASK                 (0x00000001)

/*
   �Ĵ���frm_block_done(1bit)��ֵ����:
        0b: δ���һ�����ݴ���;
        1b: ���һ�����ݴ���;
*/
#define     HDLC_FRAMER_BLOCK_NOT_DONE                  (0x00)
#define     HDLC_FRAMER_BLOCK_DONE                      (0x01)
/* ======================= hdlc_frm_status (0x2C) end ======================= */


/* ======================= hdlc_def_cfg (0x40) begin ======================== */
/* hdlc_def_cfg (0x40) */

/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���def_en��bit0;
        �Ĵ���def_acfc��bit1;
*/
#define     HDLC_DEFRAMER_CFG_EN_BITPOS             (0UL)
#define     HDLC_DEFRAMER_CFG_ACFC_BITPOS             (1UL)

/*
   �Ĵ���def_pfc��hdlc_def_cfg��bit2, bit3,
   ���bit0ƫ��2bits
*/
#define     HDLC_DEFRAMER_CFG_PFC_MOVEBITS_NUM            (2UL)

/*
   �Ĵ���def_pfc(2bits)��ֵ����:
        00b: P����ѹ��, �����;
        01b: P��ѹ��, �����;
        11b: P�򲻰���;
*/
#define     HDLC_PROTOCOL_REMOVE_WITHOUT_COMPRESS      (0x00)
#define     HDLC_PROTOCOL_REMOVE_WITH_COMPRESS         (0x01)
#define     HDLC_PROTOCOL_NO_REMOVE                    (0x03)
/* ======================== hdlc_def_cfg (0x40) end ========================= */


/* ====================== hdlc_def_ctrl (0x44) begin ======================== */

/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���def_block_new��bit0;
*/
#define     HDLC_DEFRAMER_CTRL_BLK_NEW_BITPOS             (0UL)
/* ======================= hdlc_def_ctrl (0x44) end ========================= */


/* ====================== hdlc_def_go_on(0x48) begin ======================== */

/*
   ����Ĵ�����32bit Reg�е�bitλ��:
        �Ĵ���def_go_on��bit0;
*/
#define     HDLC_DEFRAMER_GO_ON_BITPOS             (0UL)
/* ======================= hdlc_def_go_on(0x48) end ========================= */


/* ======================= hdlc_def_status (0x4C) begin ===================== */
/* ���װ״̬�Ĵ�����ַ: ���ƫ�Ƶ�ַ��0x4C */

/* �Ĵ���def_block_pro_stat(2bits)��MASK�� */
#define     HDLC_DEFRAMER_BLOCK_STATUS_MASK         (0x00000003)

/*
   �Ĵ���def_block_pro_stat(2bits)��ֵ����:
        00b: δ���һ�����ݴ���;
        01b: δ���һ�����ݴ���, �ѽ��LCP֡, Ӳ��������ͣ״̬;
        10b: ���һ�����ݴ���, ����֡�ϱ�;
        11b: ���һ�����ݴ���, ����֡�ϱ�;
*/
#define     HDLC_DEFRAMER_BLOCK_STATUS_DOING                    (0x00)
#define     HDLC_DEFRAMER_BLOCK_STATUS_PAUSE                    (0x01)
#define     HDLC_DEFRAMER_BLOCK_STATUS_DONE_WITHOUT_FRAMES      (0x02)
#define     HDLC_DEFRAMER_BLOCK_STATUS_DONE_WITH_FRAMES         (0x03)

/* �Ĵ���def_valid_num(6bits)��MASK�� */
#define     HDLC_DEFRAMER_VALID_CNT_MASK         (0x003F)

/* �Ĵ���def_err_type(7bits)��MASK�� */
#define     HDLC_DEFRAMER_ERROR_TYPE_MASK         (0x7F)
/* ======================= hdlc_def_status (0x4C) end ======================= */


/* =================== hdlc_def_err_infor_0 (0x50) begin ==================== */
/* ���װ����֡ͳ�ƼĴ�����һ��: ���ƫ�Ƶ�ַ��0x50 */
/* ==================== hdlc_def_err_infor_0 (0x50) end ===================== */


/* =================== hdlc_def_err_infor_1 (0x54) begin ==================== */
/* ���װ����֡ͳ�ƼĴ�����һ��: ���ƫ�Ƶ�ַ��0x54 */

/* ==================== hdlc_def_err_infor_1 (0x54) end ===================== */

/* �����װĿ�Ŀռ�ʧ�ܶ�ʱ������ */
#define     HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL                    (10)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
enum HDLC_RESET_REASON_ENUM
{
    HDLC_FRAMER_OUT_PER_LONG_ERR  = 0,    /* Framer out per group data too long */
    HDLC_FRAMER_OUT_ALL_LONG_ERR     ,    /* Framer out all group data too long */
    HDLC_FRAMER_WORK_TIME_LONG_ERR   ,    /* Framer work too long */
    HDLC_DEFRAMER_OUT_LIST_LONG_ERR  ,    /* Deframer out list group too more */
    HDLC_DEFRAMER_OUT_PER_LONG_ERR   ,    /* Deframer out per group data too long */
    HDLC_DEFRAMER_OUT_OFFSET_LONG_ERR,    /* Deframer out per group data offset too long */
    HDLC_DEFRAMER_OUT_ADDRESS_ERR    ,    /* Deframer out per group data address can not pack four */
    HDLC_DEFRAMER_WORK_TIME_LONG_ERR ,    /* Deframer work too long */
    HDLC_DEFRAMER_ERR_BUTT
};
typedef VOS_UINT8 HDLC_RESET_REASON_ENUM_UINT8;

enum HDLC_DATA_STORE_ENUM
{
    HDLC_DATA_STORE_M_BUF         = 0,
    HDLC_DATA_STORE_TTF_MEM          ,
    HDLC_DATA_STORE_BUTT
} ;
typedef VOS_UINT8 HDLC_DATA_STORE_ENUM_UINT8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
typedef struct _PPP_HDLC_PARA_LINK_NODE_STRU
{
    VOS_UINT8                              *pucData;      /*�ò����ڵ�ָ���ڴ��ַ*/
    VOS_UINT32                              ulLength;     /*�ڴ泤�ȣ���λByte*/
    struct _PPP_HDLC_PARA_LINK_NODE_STRU   *pstNextNode;   /*ָ����һ�������ڵ��ָ��*/
}PPP_HDLC_PARA_LINK_NODE_STRU;

/*****************************************************************************
  5 ��Ϣͷ����Ϣ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/* ����װ���������, ��ΪHDLC Framer����� */
typedef struct
{
    VOS_UINT32        ulDataLen;            /* ����װ�����ݳ���, ��λ: �ֽ� */

    /* ����װ�����ݵ���Դ */
    PPP_ZC_STRU      *pstMem;
} HDLC_FRAMER_IN_DATA_CHOICE_STRU;

/* ��װ����������, ��ΪHDLC Framer�ĳ��� */
typedef struct
{
    VOS_UINT8       *pucData;           /* ָ���װ������ݵ��׵�ַ */
    VOS_UINT16       usFrameByteCnt;    /* ָ���װ������ݳ���, ��λ: �ֽ� */
    VOS_UINT8        aucReserve[2];
} HDLC_FRAMER_OUT_DATA_STRU;

/* HDLC Framer�Ĳ��� */
typedef struct
{
    VOS_UINT8         ucMode;           /* IPģʽ, ����PPPģʽ */
    VOS_UINT8         aucReserve[3];

    HDLC_FRAMER_IN_DATA_CHOICE_STRU    stInData;    /* ��װ��� */
    HDLC_FRAMER_OUT_DATA_STRU    stOutData;     /* ��װ���� */

    VOS_UINT16   usProtocol;    /* ����װ��Э�� */

    PS_BOOL_ENUM_UINT8    enPComp;      /* �Ƿ�ѹ��Э���ֶ�, �� - PS_TRUE */
    PS_BOOL_ENUM_UINT8    enACComp;     /* �Ƿ�ѹ����ַ�Ϳ����ֶ�, �� - PS_TRUE */
    VOS_UINT32   ulACCM;
} HDLC_FRAMER_PARA_STRU;

/* ��װʱ�õ���PPP���Ӳ��� */
typedef struct
{
    struct link *l;    /* PPP���Ӳ��� */
} HDLC_FRAMER_PPP_LINK_PARA_STRU;

/* �����װ������, ��ΪHDLC Deframer����� */
typedef struct
{
    VOS_UINT8   *pucData;   /* ָ������װ������ */
    VOS_UINT32   ulLen;     /* �����װ�����ݳ���, ��λ: �ֽ� */
} HDLC_DEFRAMER_IN_DATA_STRU;

/* HDLC Deframer�Ĳ��� */
typedef struct
{
    VOS_UINT8             ucMode;       /* IPģʽ, ����PPPģʽ */
    PS_BOOL_ENUM_UINT8    enPComp;      /* �Ƿ�ѹ��Э���ֶ�, �� - PS_TRUE */
    PS_BOOL_ENUM_UINT8    enACComp;     /* �Ƿ�ѹ����ַ�Ϳ����ֶ�, �� - PS_TRUE */
    VOS_UINT8             aucReserve[1];

    HDLC_DEFRAMER_IN_DATA_STRU     stDeframerInData;    /* ���װ��� */
} HDLC_DEFRAMER_PARA_STRU;

/* ���װʱ�õ���PPP���Ӳ��� */
typedef struct
{
    struct link *l;    /* PPP���Ӳ��� */
} HDLC_DEFRAMER_PPP_LINK_PARA_STRU;

/* һ�����ݽ���Ĵ���֡��ͳ�� */
typedef struct
{
    VOS_UINT16  usFCSErrCnt;          /* FCS���� */
    VOS_UINT16  usLenLongCnt;         /* ֡���ȹ���, ����1502�ֽ� */
    VOS_UINT16  usLenShortCnt;        /* ֡���ȹ���, ����4�ֽ� */
    VOS_UINT16  usErrProtocolCnt;     /* Э���ֶβ�����xxxxxxx0, xxxxxxx1����ʽ */
    VOS_UINT16  usErrCtrlCnt;         /* �����ֶβ�Ϊ0xFF */
    VOS_UINT16  usErrAddrCnt;         /* ��ַ�ֶβ�Ϊ0x03 */
    VOS_UINT16  usFlagPosErrCnt;      /* 0x7D�������0x7E */
    VOS_UINT8   aucReserve[2];
} HDLC_DEFRAMER_ERR_FRAMES_CNT_STRU;


typedef struct
{
    PS_BOOL_ENUM_UINT8 enFramerErrorEnable;         /* ��װģ���쳣�ж��ϱ�ʹ��, ʹ�� - PS_TRUE */
    PS_BOOL_ENUM_UINT8 enFramerDataLessEnable;      /* ��װģ�����ݲ����쳣�ж�ʹ��, ʹ�� - PS_TRUE */
    PS_BOOL_ENUM_UINT8 enFramerDataMoreEnable;      /* ��װģ�����ݹ����쳣�ж�ʹ��, ʹ�� - PS_TRUE */
    PS_BOOL_ENUM_UINT8 enDeframerErrorEnable;       /* ���װģ���쳣�ж��ϱ�ʹ��, ʹ�� - PS_TRUE */
    PS_BOOL_ENUM_UINT8 enDeframerDataLessEnable;    /* ���װģ�����ݲ����쳣�ж�ʹ��, ʹ�� - PS_TRUE */
    PS_BOOL_ENUM_UINT8 enDeframerDataMoreEnable;    /* ���װģ�����ݹ����쳣�ж�ʹ��, ʹ�� - PS_TRUE */
} HDLC_INTERRUPT_CFG_STRU;

/* HDLC���������Ϣ�ṹ */
typedef struct
{
    VOS_UINT32                          ulHDLCIPBaseAddr;      /* �ӵ����ȡ��HDLC����ַ */
    VOS_UINT32                          ulHdlcDefMasterSem;    /* ���װ�ź��� */
    VOS_UINT32                          ulHdlcFrmMasterSem;    /* ��װ�ź��� */
    VOS_INT32                           slHdlcISRDef;          /* ���װ�жϺ� */
    VOS_INT32                           slHdlcISRFrm;          /* ��װ�жϺ� */
    VOS_UINT32                          ulHdlcDefIntLimit;     /* ���װ�ж�ˮ�� */
    VOS_UINT32                          ulHdlcFrmIntLimit;     /* ��װ�ж�ˮ�� */
    HTIMER                              stHdlcFrmTimerHandle;  /* �����װĿ�Ŀռ�ʧ�ܶ�ʱ����� */
    VOS_UINT32                          ulHdlcMntnTraceCfg;    /* ��ά�ɲ�ȼ����� */
}HDLC_CONFIG_INFO_STRU;

extern HDLC_CONFIG_INFO_STRU                          g_stHdlcConfigInfo;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID link_HDLCInit(VOS_VOID);

extern VOS_VOID link_HDLCDisable(VOS_VOID);

extern VOS_UINT32 PPP_HDLC_HARD_Init(VOS_VOID);

extern VOS_VOID   PPP_HDLC_HARD_SetUp(PPP_ID usPppId);

extern VOS_VOID   PPP_HDLC_HARD_Disable(VOS_VOID);

extern PPP_HDLC_RESULT_TYPE_ENUM_UINT32 PPP_HDLC_HARD_ProcData
(
    PPP_ID usPppId,
    struct link *pstLink,
    PPP_ZC_QUEUE_STRU *pstDataQ
);

extern VOS_VOID PPP_HDLC_HARD_ProcProtocolPacket
(
    struct link     *pstLink,
    struct ppp_mbuf *pstMbuf,
    VOS_INT32       ulPri,
    VOS_UINT16      ulProtocol
);

extern VOS_VOID PPP_HDLC_HARD_ProcAsFrmPacket
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
);

extern VOS_UINT32 PPP_PHY_TO_VIRT(unsigned int ulPAddr);

extern VOS_UINT32 PPP_VIRT_TO_PHY(unsigned int ulVAddr);


#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* end of hdlc_hardware.h */

