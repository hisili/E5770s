

#ifndef __TTFMEMORYMAP_H__
#define __TTFMEMORYMAP_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "MemoryMap.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* 32 �ֽڶ��� */
#define TTF_GET_32BYTE_ALIGN_VALUE(ulAddr)   (((unsigned long)(ulAddr) + 0x1F) & (~0x1F))

    /*********Uncache mem(20M) deploy begin*********/
    /*->startAddr|-------------------------------|   */
    /*           |HDLC_DEF_INPUT_PARA_LINK_BUF   |   */
    /*           |-----------------------------  |   */
    /*           |      HDLC_DEF_RPT_BUF         |   */
    /*           |-----------------------------  |   */
    /*           |     HDLC_DEF_OUTPUT_BUF       |   */
    /*           |-----------------------------  |   */
    /*           |HDLC_FRM_INPUT_PARA_LINK_BUF   |   */
    /*           |-----------------------------  |   */
    /*           |    HDLC_FRM_RPT_BUF_ADDR      |   */
    /*           |-----------------------------  |   */
    /*           |HDLC_FRM_OUTPUT_PARA_LINK_BUF  |   */
    /*           |-----------------------------  |   */
    /*           |         PAD (0-31B)           |   */
    /*           |-----------------------------  |   */
    /*           |UL CIPHER PARA NODE(35k)       |   */
    /*           |-------------------------------|   */
    /*           |UL CIPHER SRC SEG DATA (51k)   |   */
    /*           |-------------------------------|   */
    /*           |UL CIPHER DST SEG DATA (51k)   |   */
    /*           |-------------------------------|   */
    /*           |   UL CIPHER KEY (1k)          |   */
    /*           |-------------------------------|   */
    /*           |DL CIPHER PARA NODE(11k)       |   */
    /*           |-------------------------------|   */
    /*           |DL CIPHER MAC SEG DATA(155k)   |   */
    /*           |-------------------------------|   */
    /*           |DL CIPHER RLC SEG DATA(155k)   |   */
    /*           |-------------------------------|   */
    /*           |   DL CIPHER KEY (1k)          |   */
    /*           |-------------------------------|   */
    /*           |TTF_LL_CIPHER_PARA_NODE(1k)    |   */
    /*           |-------------------------------|   */
    /*           |TTF_LL_CIPHER_KEY(16B)         |   */
    /*           |-------------------------------|   */
    /*           |TTF_LL_CIPHER_ARRAY(1560B)     |   */
    /*           |-------------------------------|   */
    /*           |I1_TTF_LL_CIPHER_PARA_NODE(1k) |   */
    /*           |-------------------------------|   */
    /*           |I1_TTF_LL_CIPHER_KEY(16B)      |   */
    /*           |-------------------------------|   */
    /*           |I1_TTF_LL_CIPHER_ARRAY(1560B)  |   */
    /*           |-------------------------------|   */
    /*           |         PAD (0-31B)           |   */
    /*           |-----------------------------  |   */
    /*           |                               |   */
    /*           |     TTF_BBPMASTER_MEM         |   */
    /*           |                               |   */
    /*           |-----------------------------  |   */
    /*           |                               |   */
    /*           |     TTF_ACORE_POOL_MEM        |   */
    /*           |                               |   */
    /*           |-----------------------------  |   */
    /*           |         PAD (0-31B)           |   */
    /*           |-----------------------------  |   */
    /*           |                               |   */
    /*           |     TTF_CCORE_POOL_MEM        |   */
    /*           |                               |   */
    /*           |-----------------------------  |   */


/* �����TTF�����ڴ��С�ͻ���ַ */

/* ���ڵ����������ڴ� */

/* HDLC �豸ʹ����ʼ��ַ */
#define TTF_HDLC_MASTER_START_ADDR(BaseAddr) \
            (TTF_MEMCTRL_GetTypeAddr((TTF_GET_32BYTE_ALIGN_VALUE(BaseAddr)), TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE))

/* CICOM �豸ʹ����ʼ��ַ*/
#define TTF_UL_CIPHER_PARA_NODE_ADDR(BaseAddr) \
            (TTF_MEMCTRL_GetTypeAddr((TTF_GET_32BYTE_ALIGN_VALUE(BaseAddr)), TTF_MEMCTRL_CIPHER_MASTER_ADDR_TYPE))

/* BBP Masterʹ���ڴ����ַ */
#define TTF_BBP_MASTER_START_ADDR(BaseAddr) \
            (TTF_MEMCTRL_GetTypeAddr((TTF_GET_32BYTE_ALIGN_VALUE(BaseAddr)), TTF_MEMCTRL_BBP_MASTER_ADDR_TYPE))

/* A CPU ����cache�ڴ����ַ */
#define TTF_ACORE_POOL_MEM_START_ADDR(BaseAddr) \
            (TTF_MEMCTRL_GetTypeAddr((TTF_GET_32BYTE_ALIGN_VALUE(BaseAddr)), TTF_MEMCTRL_ACORE_POOL_ADDR_TYPE))

/* C CPU ����cache�ڴ����ַ */
#define TTF_CCORE_POOL_MEM_START_ADDR(BaseAddr) \
            (TTF_MEMCTRL_GetTypeAddr((TTF_GET_32BYTE_ALIGN_VALUE(BaseAddr)), TTF_MEMCTRL_CCORE_POOL_ADDR_TYPE))


/* ----------------HDLC�Ż������ڴ� START---------------- */

/* HDLC Master�豸ʹ���ڴ����ַ */
#if 0
/* HDLC �豸ʹ����ʼ��ַ */
#define TTF_HDLC_MASTER_START_ADDR(BaseAddr)                TTF_GET_8BYTE_ALIGN_VALUE(BaseAddr)
#endif

/* ���װ�������������������ڵ���� */
#define TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM        (20)

/* ���װ��������ڴ��С�ͻ���ַ
   HDLC_DEF_INPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU) */
#define TTF_HDLC_DEF_INPUT_PARA_LINK_BUF_LEN        (TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM * 12)

/* ���װ��������������������ܳ��� */
#define TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE       (13*1024)


/* һ�ν��װ���IP��/��PPP֡������ = һ�ν��װ������볤��/��СIP������(20B) */
#define TTF_HDLC_DEF_OUTPUT_MAX_NUM                 (TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE/20)

/* ���װ��Ϣ�ϱ������� */
#define TTF_HDLC_DEF_RPT_MAX_NUM                    (TTF_HDLC_DEF_OUTPUT_MAX_NUM)

/* ���װ��Ϣ�ϱ��ռ��ڴ��С�ͻ���ַ
   һ�ν��װ��������IP��/��PPP֡����*sizeof(HDLC_FRM_RPT_NODE) */
#define TTF_HDLC_DEF_RPT_BUF_LEN                    (TTF_HDLC_DEF_RPT_MAX_NUM*8)

/* ((TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE / 6 + 1) * 8)
 * 6Ϊռ�����ռ����С��Ч֡
 * 8Ϊ���ֽڶ���
 * +1 ΪС������ȡ��
*/

#define TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN            (18 * 1024)

    /* ��HDLC MASTER�豸ʹ�õ��ڴ��ܳ��ȣ����ṹ��HDLC_DEF_BUFF_INFO_STRU�仯ʱ��
        �ú�Ӧ����Ӧ�仯 */
#define TTF_HDLC_MASTER_DEF_BUF_LEN                 (TTF_HDLC_DEF_INPUT_PARA_LINK_BUF_LEN + \
                                                        TTF_HDLC_DEF_RPT_BUF_LEN + \
                                                        TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN)

/* ��װ�������������������ڵ���� */
#define TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM        (20)

/* ��װ��������������������ܳ��� */
#define TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_SIZE       (15*1024)

/* ��װ��������ڴ��С = TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU) */
#define TTF_HDLC_FRM_INPUT_PARA_LINK_BUF_LEN        (TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM * 12)

/* ��װ��Ϣ������ */
#define TTF_HDLC_FRM_RPT_MAX_NUM                    (TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM)

/* ��װ��Ϣ�ϱ��ռ��ڴ��С�ͻ���ַ
   TTF_HDLC_FRM_RPT_MAX_NUM * sizeof(HDLC_DEF_RPT_NODE) */
#define TTF_HDLC_FRM_RPT_BUF_LEN                    (TTF_HDLC_FRM_RPT_MAX_NUM * 8)

/* ��װ�������������������ڵ���� */
#define TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM       (40)

/* ��װ��������ڴ��С�ͻ���ַ
   TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU) */
#define TTF_HDLC_FRM_OUTPUT_PARA_LINK_BUF_LEN       (TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM * 12)

/* ��HDLC MASTER�豸ʹ�õ��ڴ��ܳ��ȣ����ṹ��HDLC_FRM_BUFF_INFO_STRU�仯ʱ��
    �ú�Ӧ����Ӧ�仯 */
#define TTF_HDLC_MASTER_FRM_BUF_LEN                 (TTF_HDLC_FRM_INPUT_PARA_LINK_BUF_LEN + \
                                                        TTF_HDLC_FRM_RPT_BUF_LEN + \
                                                        TTF_HDLC_FRM_OUTPUT_PARA_LINK_BUF_LEN)

#if (FEATURE_ON == FEATURE_PPP)
/* ��HDLC MASTER�豸ʹ�õ��ڴ��ܳ��� */
#define TTF_HDLC_MASTER_LINK_TOTAL_LEN              (TTF_GET_32BYTE_ALIGN_VALUE((TTF_HDLC_MASTER_DEF_BUF_LEN + \
                                                        TTF_HDLC_MASTER_FRM_BUF_LEN)))
#else
#define TTF_HDLC_MASTER_LINK_TOTAL_LEN              (0)
#endif

/* ----------------HDLC�Ż������ڴ� END---------------- */

#if 0
/* HDLC Master�豸ʹ���ڴ�β��ַ */
#define TTF_HDLC_MASTER_END_ADDR(BaseAddr)\
           (TTF_HDLC_MASTER_START_ADDR(BaseAddr) + TTF_HDLC_MASTER_LINK_LEN)

/* ----------------HDLC�Ż������ڴ� END---------------- */
/* CICOM �豸ʹ����ʼ��ַ*/
#if (FEATURE_ON == FEATURE_PPP) && defined(FEATURE_HDLC_MASTER)
#define TTF_UL_CIPHER_PARA_NODE_ADDR(BaseAddr)  TTF_GET_32BYTE_ALIGN_VALUE(TTF_HDLC_MASTER_END_ADDR(BaseAddr))/* �ò���Ҫ��8�ֽڶ��� */
#else
#define TTF_UL_CIPHER_PARA_NODE_ADDR(BaseAddr) TTF_GET_8BYTE_ALIGN_VALUE(BaseAddr) /* �ò���Ҫ��8�ֽڶ��� */
#endif
#endif

/* ----------------CICOM�豸�ڴ� START---------------- */

/*1096(WTTF_MAX_PDU_NUM_PER_UL_LOCH) * 32Byte(RLC_PDU_SEG_CIPHER_PARA_STRU) �� 35KByte*/
#define TTF_UL_CIPHER_PARA_NODE_LEN         (35*1024)

#define TTF_UL_CIPHER_SRC_SEG_DATA_ADDR(BaseAddr)\
           (TTF_UL_CIPHER_PARA_NODE_ADDR(BaseAddr) + TTF_UL_CIPHER_PARA_NODE_LEN)

#define TTF_UL_CIPHER_SRC_SEG_DATA_LEN      (51*1024)

#define TTF_UL_CIPHER_DST_SEG_DATA_ADDR(BaseAddr)\
            (TTF_UL_CIPHER_SRC_SEG_DATA_ADDR(BaseAddr) + TTF_UL_CIPHER_SRC_SEG_DATA_LEN)

#define TTF_UL_CIPHER_DST_SEG_DATA_LEN      (51*1024)

#define TTF_UL_CIPHER_KEY_ADDR(BaseAddr)\
            (TTF_UL_CIPHER_DST_SEG_DATA_ADDR(BaseAddr) + TTF_UL_CIPHER_DST_SEG_DATA_LEN)

/* ���м�����Կʹ���ڴ泤�Ⱥͻ���ַ
   3(RLC_CPH_CFG_NUM) * 16Byte(WUE_CIPHER_KEY_LEN) = 48Byte ȡ��Ϊ1K */
#define TTF_UL_CIPHER_KEY_LEN               (1*1024)

#define TTF_DL_CIPHER_PARA_NODE_ADDR(BaseAddr)\
           (TTF_UL_CIPHER_KEY_ADDR(BaseAddr) + TTF_UL_CIPHER_KEY_LEN)

/* ���н��ܲ����ڵ�ʹ���ڴ泤�Ⱥͻ���ַ
    350(WTTF_MAX_PDU_NUM_PER_DL_LOCH) * 32Byte(RLC_PDU_SEG_CIPHER_PARA_STRU) �� 11KByte */
#define TTF_DL_CIPHER_PARA_NODE_LEN         (11*1024)

/* Modified Mem Reduce End */
#define TTF_DL_CIPHER_MAC_SEG_DATA_ADDR(BaseAddr)\
           (TTF_DL_CIPHER_PARA_NODE_ADDR(BaseAddr) + TTF_DL_CIPHER_PARA_NODE_LEN)

/* ����MAC-ehs SDU�ֶ�ʹ���ڴ泤�Ⱥͻ���ַ */
/*13200(WTTF_MAC_EHS_SDU_SEG_DATA_NUM) * 12Byte(SEG_DATA_STRU��С) �� 155KByte */
#define TTF_DL_CIPHER_MAC_SEG_DATA_LEN      (155*1024)

#define TTF_DL_CIPHER_SEG_DATA_ADDR(BaseAddr)\
           (TTF_DL_CIPHER_MAC_SEG_DATA_ADDR(BaseAddr) + TTF_DL_CIPHER_MAC_SEG_DATA_LEN)

#define TTF_DL_RLC_CIPHER_SEG_DATA_LEN      (155*1024)

#define TTF_DL_CIPHER_KEY_ADDR(BaseAddr)\
           (TTF_DL_CIPHER_SEG_DATA_ADDR(BaseAddr) + TTF_DL_RLC_CIPHER_SEG_DATA_LEN)

/* ���н�����Կʹ���ڴ泤�Ⱥͻ���ַ
   3(RLC_CPH_CFG_NUM) * 16Byte(WUE_CIPHER_KEY_LEN) = 48Byte ȡ��Ϊ1K */
#define TTF_DL_CIPHER_KEY_LEN               (1*1024)

#define TTF_UL_CIPHER_PDU_NODE_TOTAL_LEN    \
    (TTF_UL_CIPHER_PARA_NODE_LEN + TTF_UL_CIPHER_SRC_SEG_DATA_LEN + TTF_UL_CIPHER_DST_SEG_DATA_LEN)

#define TTF_DL_CIPHER_PDU_NODE_TOTAL_LEN    \
    (TTF_DL_CIPHER_PARA_NODE_LEN + TTF_DL_CIPHER_MAC_SEG_DATA_LEN + TTF_DL_RLC_CIPHER_SEG_DATA_LEN)

/* Wģ ��MASTER�豸ʹ�õ��ڴ��ܳ��� */
#define TTF_CIPHER_MASTER_LINK_LEN          (TTF_UL_CIPHER_PDU_NODE_TOTAL_LEN + TTF_UL_CIPHER_KEY_LEN + \
                                             TTF_DL_CIPHER_PDU_NODE_TOTAL_LEN + TTF_DL_CIPHER_KEY_LEN)

/* Gģ�ӽ���ʹ�õ��ڴ� */
#define TTF_LL_CIPHER_PARA_NODE_ADDR(BaseAddr) \
           (TTF_UL_CIPHER_PARA_NODE_ADDR(BaseAddr) + TTF_CIPHER_MASTER_LINK_LEN)

/*1(ÿ��ֻ����һ��LLC PDU��Ŀǰ�ȶ�ΪLLC PDU��һ��TTF MEM��) * 32Byte(sizeof(LLC_PDU_SEG_CIPHER_PARA_STRU)) = 32Byte*/
#define TTF_LL_CIPHER_PARA_NODE_LEN     (1*1024)

/* ���CK���ڴ���ʼ��ַ */
#define TTF_LL_CIPHER_KEY_ADDR(BaseAddr)\
           (TTF_LL_CIPHER_PARA_NODE_ADDR(BaseAddr) + TTF_LL_CIPHER_PARA_NODE_LEN)

/* ��ԿΪ1�飬Ϊ16�ֽ� */
#define TTF_CIPHER_KEY_LEN              (1*16)

/* ��ż�����ļӽ������е��ڴ� */
#define TTF_LL_CIPHER_ARRAY_ADDR(BaseAddr)\
           (TTF_LL_CIPHER_KEY_ADDR(BaseAddr) + TTF_CIPHER_KEY_LEN)

/* �ӽ��������Ϊ1560Bytes*/
#define TTF_CIPHER_KEY_ARRAY_LEN        (1560)

/* Modem1��GSM�ӽ���ʹ�õ��ڴ� */
#define I1_TTF_LL_CIPHER_PARA_NODE_ADDR(BaseAddr) \
            (TTF_LL_CIPHER_ARRAY_ADDR(BaseAddr) + TTF_CIPHER_KEY_ARRAY_LEN)

/* ���CK���ڴ���ʼ��ַ */
#define I1_TTF_LL_CIPHER_KEY_ADDR(BaseAddr)\
            (I1_TTF_LL_CIPHER_PARA_NODE_ADDR(BaseAddr) + TTF_LL_CIPHER_PARA_NODE_LEN)

/* ��ż�����ļӽ������е��ڴ� */
#define I1_TTF_LL_CIPHER_ARRAY_ADDR(BaseAddr)\
            (I1_TTF_LL_CIPHER_KEY_ADDR(BaseAddr) + TTF_CIPHER_KEY_LEN)

/* Modem0��GģLLC MASTER�豸ʹ�õ��ڴ��ܳ��� */
#define I0_TTF_LL_CIPHER_MASTER_LINK_LEN   \
            (TTF_LL_CIPHER_PARA_NODE_LEN + TTF_CIPHER_KEY_LEN + TTF_CIPHER_KEY_ARRAY_LEN)

/* Modem1��GģLLC MASTER�豸ʹ�õ��ڴ��ܳ��� */
#define I1_TTF_LL_CIPHER_MASTER_LINK_LEN   \
            (TTF_LL_CIPHER_PARA_NODE_LEN + TTF_CIPHER_KEY_LEN + TTF_CIPHER_KEY_ARRAY_LEN)

/* ����GģLLC MASTER�豸ʹ�õ��ڴ��ܳ��� */
#define TTF_LL_CIPHER_MASTER_LINK_LEN   \
            (I0_TTF_LL_CIPHER_MASTER_LINK_LEN + I1_TTF_LL_CIPHER_MASTER_LINK_LEN )

/*
    TTFMem.c�е�g_ulTtfActiveMemTotalLen��¼�˸�ƽ̨��ECS_TTF_SIZE��ʵ��ʹ�õ��ܴ�С
    ���޸ļ��ܲ����ڴ���ڴ�ش�Сʱ����ʹ��COMM_CODE_GU/ConfigĿ¼��Ӧƽ̨��FeatureXXX.h�ļ���
    ����COMM_CODE_GU\Balong_GU_Inc\win32Ŀ¼�µ��ļ���Ȼ������UT���̣����g_ulTtfActiveMemTotalLen
    ȷ��g_ulTtfActiveMemTotalLen������MemoryMap.h�е����ֵ�ECS_TTF_SIZE
*/
#define TTF_PARA_MEM_TOTAL_LEN    \
            (TTF_GET_32BYTE_ALIGN_VALUE(TTF_CIPHER_MASTER_LINK_LEN + TTF_LL_CIPHER_MASTER_LINK_LEN))


#if 0
/* CIPHER Master�豸ʹ���ڴ�β��ַ */
#define TTF_CIPHER_MASTER_END_ADDR(BaseAddr)\
           (I1_TTF_LL_CIPHER_ARRAY_ADDR(BaseAddr) + TTF_CIPHER_KEY_ARRAY_LEN)
#endif

/* ----------------CICOM�豸�ڴ� END---------------- */


/* ----------------BBPMASTER�����ڴ� START---------------- */
#if 0
/* ----------------BBPMASTER�����ڴ� START---------------- */
/* BBP Masterʹ���ڴ����ַ */
#define TTF_BBP_MASTER_START_ADDR(BaseAddr)                 (TTF_GET_32BYTE_ALIGN_VALUE(TTF_CIPHER_MASTER_END_ADDR(BaseAddr)))
#endif
#if (FEATURE_ON == FEATURE_BBP_MASTER)
/* BBPMASTER DATA BUFF LENTH (��WTTFPHY_MAC_HSDPA_TB_DATA_SIZEһ��) */
#define TTF_BBPMST_BUFF_TOTAL_LEN             (5408)
#else
#define TTF_BBPMST_BUFF_TOTAL_LEN             (0)
#endif

#if 0
/* HDLC Master�豸ʹ���ڴ�β��ַ */
#define TTF_BBP_MASTER_END_ADDR(BaseAddr)\
           (TTF_CIPHER_MASTER_END_ADDR(BaseAddr) + TTF_BBPMST_BUFF_LEN)
#endif
/* ----------------BBPMASTER�����ڴ� END---------------- */


/* ----------------A CPU ����cache�ڴ� START---------------- */
/* �����ڴ�ؿ��� */
#if ( FEATURE_ON == FEATURE_LTE )
/* LTE�����ڴ��ܳ���:   WithWifi      12,854,528 �ֽ�
                        WithOutWifi   12,620,608 �ֽ� */
/* ==================================================== */
/* IMM MEM �����ڴ�ؿ��� */
#define IMM_MEM_CTRL_MEM_CNT                (2103)

/*******************************************************************************
const IMM_MEM_CLUSTER_CFG_INFO_STRU   g_astImmMemSharePoolClusterTableInfo[] =
{
        {864,                           1427},
#if(FEATURE_WIFI == FEATURE_ON )
        {1952,                          1887}
#else
        {1888,                          1887}
#endif
};

�ڴ���ܳ���: WithWifi      4,826,240�ֽ�
              WithOutWifi   4,707,520�ֽ�
*******************************************************************************/
/* IMM MEM �����ڴ����λ�ڴ���С */
#define IMM_MEM_SHARE_POOL_SIZE_CLUSTER_0           (864)
#if(FEATURE_WIFI == FEATURE_ON)
#define IMM_MEM_SHARE_POOL_SIZE_CLUSTER_1           (1952)
#else
#define IMM_MEM_SHARE_POOL_SIZE_CLUSTER_1           (1888)
#endif

/* IMM MEM �����ڴ����λ�ڴ���� */
#define IMM_MEM_SHARE_POOL_CNT_CLUSTER_0            (1427)
#define IMM_MEM_SHARE_POOL_CNT_CLUSTER_1            (1887)

/* IMM MEM �����ڴ��ܿ��� */
#define IMM_MEM_SHARE_POOL_MEM_CNT                  (IMM_MEM_SHARE_POOL_CNT_CLUSTER_0 + IMM_MEM_SHARE_POOL_CNT_CLUSTER_1)

/* IMM MEM �����ڴ��ܴ�С */
#define IMM_MEM_SHARE_POOL_TOTAL_LEN                ((IMM_MEM_SHARE_POOL_SIZE_CLUSTER_0 * IMM_MEM_SHARE_POOL_CNT_CLUSTER_0) + \
                                                     (IMM_MEM_SHARE_POOL_SIZE_CLUSTER_1 * IMM_MEM_SHARE_POOL_CNT_CLUSTER_1))

/* TTF MEM �����ڴ�ؿ��� */
#define TTF_MEM_CTRL_MEM_CNT                        (IMM_MEM_SHARE_POOL_MEM_CNT)

#else

/* LTE�����ڴ��ܳ���:   WithWifi      9,789,888 �ֽ�
                        WithOutWifi   9,656,448 �ֽ� */
/* IMM MEM �����ڴ�ؿ��� */
#define IMM_MEM_CTRL_MEM_CNT                        (533)

/*******************************************************************************
const IMM_MEM_CLUSTER_CFG_INFO_STRU    g_astImmMemSharePoolClusterTableInfo[] =
{
        {864,                           1427},
#if(FEATURE_WIFI == FEATURE_ON )
        {1952,                          1887}
#else
        {1888,                          1887}
#endif
};


�ڴ���ܳ���: WithWifi      4,826,240�ֽ�
              WithOutWifi   4,707,520�ֽ�
*******************************************************************************/
/* IMM MEM �����ڴ����λ�ڴ���С */
#define IMM_MEM_SHARE_POOL_SIZE_CLUSTER_0           (864)
#if(FEATURE_WIFI == FEATURE_ON)
#define IMM_MEM_SHARE_POOL_SIZE_CLUSTER_1           (1952)
#else
#define IMM_MEM_SHARE_POOL_SIZE_CLUSTER_1           (1888)
#endif

/* IMM MEM �����ڴ����λ�ڴ���� */
#define IMM_MEM_SHARE_POOL_CNT_CLUSTER_0            (1510)
#define IMM_MEM_SHARE_POOL_CNT_CLUSTER_1            (1440)

/* IMM MEM �����ڴ��ܿ��� */
#define IMM_MEM_SHARE_POOL_MEM_CNT                  (IMM_MEM_SHARE_POOL_CNT_CLUSTER_0 + IMM_MEM_SHARE_POOL_CNT_CLUSTER_1)

/* IMM MEM �����ڴ��ܴ�С */
#define IMM_MEM_SHARE_POOL_TOTAL_LEN                ((IMM_MEM_SHARE_POOL_SIZE_CLUSTER_0 * IMM_MEM_SHARE_POOL_CNT_CLUSTER_0) + \
                                                     (IMM_MEM_SHARE_POOL_SIZE_CLUSTER_1 * IMM_MEM_SHARE_POOL_CNT_CLUSTER_1))

/* TTF MEM �����ڴ�ؿ��� */
#define TTF_MEM_CTRL_MEM_CNT                        (IMM_MEM_SHARE_POOL_MEM_CNT)
#endif




#if 0
#if (FEATURE_ON == FEATURE_BBP_MASTER)
/* A CPU ����cache�ڴ����ַ */
#define TTF_ACORE_POOL_MEM_START_ADDR(BaseAddr) (TTF_GET_32BYTE_ALIGN_VALUE(TTF_BBP_MASTER_END_ADDR(BaseAddr)))
#else
/* A CPU ����cache�ڴ����ַ */
#define TTF_ACORE_POOL_MEM_START_ADDR(BaseAddr) (TTF_GET_32BYTE_ALIGN_VALUE(TTF_CIPHER_MASTER_END_ADDR(BaseAddr)))
#endif
#endif
/* IMM MEM �����ڴ��������ͷ�ܿ���*/
#define IMM_MEM_CTRL_MEM_TOTAL_CNT              (IMM_MEM_SHARE_POOL_MEM_CNT + IMM_MEM_CTRL_MEM_CNT)

/* A CPU IMM�ڴ�ػ���ַ */
#define IMM_MEM_POOL_BASE_ADDR(BaseAddr)        ((TTF_ACORE_POOL_MEM_START_ADDR(BaseAddr)))

/* A CPU �����ڴ����ʼ��ַ */
#define IMM_SHARE_MEM_POOL_ADDR(BaseAddr)       (IMM_MEM_POOL_BASE_ADDR(BaseAddr))

#if (FEATURE_ON == FEATURE_SKB_EXP)   /* V3R3�汾 */
/* A CPU �����ڴ���ܴ�С */
#define TTF_ACORE_POOL_MEM_TOTAL_LEN            (TTF_GET_32BYTE_ALIGN_VALUE(IMM_MEM_SHARE_POOL_TOTAL_LEN))
#else
#define TTF_ACORE_POOL_MEM_TOTAL_LEN            (0)
#endif


#if 0
/* A CPU ����cache�ڴ�β��ַ */
#define TTF_ACORE_POOL_MEM_END_ADDR(BaseAddr)   (TTF_ACORE_POOL_MEM_START_ADDR(BaseAddr) + TTF_ACORE_POOL_MEM_TOTAL_LEN)

/* C CPU ����cache�ڴ����ַ */
#define TTF_CCORE_POOL_MEM_START_ADDR(BaseAddr) (TTF_GET_32BYTE_ALIGN_VALUE(TTF_ACORE_POOL_MEM_END_ADDR(BaseAddr)))
#endif



/* �û����ں��ڴ��ͷŹ�������ڴ���� */
#define TTF_MEM_FREE_AREA_SIZE                  (16*1024)
#define TTF_MEM_FREE_QUE_LEN                    (4000)

#define IMM_MEM_FREE_AREA_SIZE                  (16*1024)
#define IMM_MEM_FREE_QUE_LEN                    (4000)

#if 0
/* ����TTF_GET_32BYTE_ALIGN_VALUE���ܵ����ڴ��ַ�������ƫ31�ֽڣ�������û�м����ڳ�����
   �ڼ���C���ڴ�ػ���ǰ�����������Σ��ֱ���TTF_HDLC_DEF_INPUT_PARA_LINK_BUF_ADDR��
   TTF_ACORE_POOL_MEM_START_ADDR��TTF_CCORE_POOL_MEM_START_ADDR */
#define TTF_MEM_32BYTE_ALIGN_PADDING_LEN       (3*32)
#endif

/* ----------------A CPU ����cache�ڴ� END---------------- */


/* ----------------C CPU ����cache�ڴ� START--------------- */

/* C CPU TTF MEM�ڴ�ػ���ַ */
#define TTF_MEM_POOL_BASE_ADDR(BaseAddr)        (TTF_CCORE_POOL_MEM_START_ADDR(BaseAddr))

#define TTF_CCORE_POOL_MEM_TOTAL_LEN            (12035808) /* C-CPU �ڴ���ܳ��ȣ�32�ֽڶ��� */

/* ----------------C CPU ����cache�ڴ� END---------------- */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum TTF_MEMCTRL_ADDR_TYPE_ENUM
{
    TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE   = 0,
    TTF_MEMCTRL_CIPHER_MASTER_ADDR_TYPE,
    TTF_MEMCTRL_BBP_MASTER_ADDR_TYPE,
    TTF_MEMCTRL_ACORE_POOL_ADDR_TYPE,
    TTF_MEMCTRL_CCORE_POOL_ADDR_TYPE,
    TTF_MEMCTRL_ADDR_TYPE_BUTT
};
typedef unsigned long TTF_MEMCTRL_ADDR_TYPE_ENUM_UINT32;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/
extern unsigned long   TTF_MEMCTRL_ACORE_AddrInit(void);
extern unsigned long   TTF_MEMCTRL_CCORE_AddrInit(void);
extern unsigned long   TTF_MEMCTRL_GetOffsetBaseLen(unsigned long  ulType);
extern unsigned long   TTF_MEMCTRL_GetTypeAddr(unsigned long ulAddr, unsigned long  ulType);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TtfMemoryMap.h */

