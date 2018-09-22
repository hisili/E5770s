
#ifndef _SCM_PROC_H_
#define _SCM_PROC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "DrvInterface.h"
#include "vos.h"

#if(VOS_OS_VER == VOS_LINUX)
#include <asm/dma-mapping.h>
#include <linux/dma-mapping.h>
#include <asm/io.h>
#include <linux/gfp.h>
#include <linux/mm.h>
#endif

#if(VOS_OS_VER == VOS_VXWORKS) 
#include "cacheLib.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/**************************************************************************
  2 �궨��
**************************************************************************/

//#define OM_DEBUG_PRINT

/* ����꿪�� */
#if (VOS_OS_VER == VOS_WIN32)
#define SCM_ACORE
#define SCM_CCORE
#else

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#define SCM_ACORE
#endif

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#define SCM_CCORE
#endif

#endif    /*(VOS_OS_VER == VOS_WIN32)*/

/* ͨ���������ݺ����ݳ��� */
typedef VOS_VOID (*SCM_CODERDESTFUCN)(SOCP_CODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT8 *pucPHYData, VOS_UINT32 ulSize);

/* ͨ���������ݡ����ݳ��ȡ��ؾ����ݡ��ؾ����ݳ��� */
typedef VOS_VOID (*SCM_DECODERDESTFUCN)(SOCP_DECODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT32 ulSize, VOS_UINT8 *pucRBData, VOS_UINT32 ulRBSize);

#if (VOS_OS_VER == VOS_WIN32)               /*PC Stub*/
#define SCM_CODER_SRC_NUM           (4)       /* ����Դͨ������ */
#define SCM_CODER_DST_NUM           (3)       /* ����Ŀ��ͨ������ */
#define SCM_DECODER_SRC_NUM         (1)       /* ����Դͨ������ */
#define SCM_DECODER_DST_NUM         (1)       /* ����Ŀ��ͨ������ */

#else
#if (OSA_CPU_CCPU == VOS_OSA_CPU)

#if (RAT_MODE != RAT_GU)                /* Mutil Mode */
#define SCM_CODER_SRC_NUM           (4)       /* ����Դͨ������ */
#else                                       /* GU Single Mode */
#define SCM_CODER_SRC_NUM           (1)       /* ����Դͨ������ */
#endif  /* (RAT_MODE != RAT_GU) */

#endif  /* (OSA_CPU_CCPU == VOS_OSA_CPU) */

#if (OSA_CPU_ACPU == VOS_OSA_CPU)

#if (RAT_MODE != RAT_GU)                /* Mutil Mode */
#define SCM_CODER_SRC_NUM           (3)       /* ����Դͨ������ */
#define SCM_CODER_DST_NUM           (3)       /* ����Ŀ��ͨ������ */
#define SCM_DECODER_SRC_NUM         (1)       /* ����Դͨ������ */
#define SCM_DECODER_DST_NUM         (1)       /* ����Ŀ��ͨ������ */
#else                                       /* GU Single Mode */
#define SCM_CODER_SRC_NUM           (1)       /* ����Դͨ������ */
#define SCM_CODER_DST_NUM           (1)       /* ����Ŀ��ͨ������ */
#endif  /* (RAT_MODE != RAT_GU) */

#endif  /* (OSA_CPU_ACPU == VOS_OSA_CPU) */

#endif /*(VOS_OS_VER == VOS_WIN32)*/


#define SCM_CODER_SRC_MAX_LEN       (16*1024)       /* ����ͨ����������ݳ���  */

#define SCM_DECODER_SRC_SIZE        (8*1024)        /* ����Դͨ���ռ��С */
#define SCM_DECODER_DST_SIZE        (8*1024)        /* ����Ŀ��ͨ���ռ��С */
#define SCM_CODER_DST_IND_SIZE      (80*1024)       /* �����ϱ�����Ŀ��ͨ���ռ��С */
#define SCM_CODER_DST_CNF_SIZE      (16*1024)       /* ����ظ�����Ŀ��ͨ���ռ��С */

#define SCM_CODER_DST_IND_SD_SIZE   (1024*1229)     /* SD�������ϱ�����Ŀ��ͨ���ռ��С 1.2M */

#define SCM_CODE_SRC_BD_NUM         (4*1024)        /* ��ʽͨ��BD�ĸ��� */
#define SCM_CODE_SRC_RD_NUM         (4*1024)        /* ��ʽͨ��RD�ĸ��� */

#define SCM_CODER_SRC_BDSIZE        (sizeof(SOCP_BD_DATA_STRU)*SCM_CODE_SRC_BD_NUM)   /* ��ʽͨ����BD�ռ� */
#define SCM_CODER_SRC_RDSIZE        (sizeof(SOCP_RD_DATA_STRU)*SCM_CODE_SRC_RD_NUM)   /* ��ʽͨ����RD�ռ� */

#define SCM_CODER_DST_THRESHOLD_GU  (4)             /* GU����Ŀ��ͨ����ֵ����λKB */

#define SCM_CODER_DST_THRESHOLD_L   (4)             /* L����Ŀ��ͨ����ֵ����λKB */

#define SCM_CODER_DST_GTHRESHOLD    ((4*1024)+8)    /* ����Դͨ���ٲ���ֵ */

#define SCM_DECODER_DST_THRESHOLD   (1)             /* ����Ŀ��ͨ����ֵ, ��λHDLC֡ */

#define SCM_CODER_SRC_RD_THRESHOLD  (0)             /* ����Դͨ��RD��ֵ */

#define SCM_DATA_SAVE_TAG           (0x5A)          /* SOCP�������ݵļ����� */

#if (VOS_OS_VER == VOS_WIN32)

#ifdef OAM_UT_DEBUG        /*only for UT test*/
#define SCM_MALLOC(ulBytes)         V_MemAlloc(0, 0, ulBytes, 0, 0, 0)
#else                     /*for ST test*/
#define SCM_MALLOC(ulBytes)         malloc(ulBytes)
#endif /* OAM_UT_DEBUG */
#endif /*(VOS_OS_VER == VOS_WIN32)*/

#if((VOS_OS_VER == VOS_WIN32) || (VOS_RTOSCK == VOS_OS_VER))
#define SCM_FLUSH_CACHE(ptr, size)      
#define SCM_INVALID_CACHE(ptr, size)
#elif(VOS_OS_VER == VOS_VXWORKS)
#define SCM_FLUSH_CACHE(ptr, size)      cacheFlush(DATA_CACHE, ptr, size)    
#define SCM_INVALID_CACHE(ptr, size)    cacheInvalidate(DATA_CACHE, ptr, size);
#elif (VOS_OS_VER == VOS_LINUX)
#define SCM_FLUSH_CACHE(ptr, size) dma_map_single(0, ptr, size, DMA_TO_DEVICE)
#define SCM_INVALID_CACHE(ptr, size) dma_map_single(0, ptr, size, DMA_FROM_DEVICE)
#endif


#define SCM_MALLOC_MAX_SIZE     0x200000
#define SCM_MALLOC_MAX_INDEX    9           /*page_size Ϊ4K*/
#define SCM_PAGE_SIZE      		0x1000

/**************************************************************************
  3 ö�ٶ���
**************************************************************************/
enum  SCM_CHANNEL_INIT_ENUM
{
    SCM_CHANNEL_UNINIT = 0,             /* δ��ʼ�� */
    SCM_CHANNEL_INIT_SUCC,              /* ��ʼ���ɹ� */
    SCM_CHANNEL_MEM_FAIL,               /* ��ʼ�������ڴ���� */
    SCM_CHANNEL_CFG_FAIL,               /* ��ʼ��ͨ������ */
    SCM_CHANNEL_START_FAIL,             /* ͨ���������� */
    SCM_CHANNEL_INIT_BUTT
};
typedef VOS_UINT32 SCM_CHANNEL_INIT_ENUM_U32;

/**************************************************************************
  4 �ṹ�嶨��
**************************************************************************/
typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ��ʼ��״̬ */
    VOS_UINT32                  ulChannelID;    /* ͨ��ID */
}SCM_CHANNEL_CFG_HEAD;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_CODER_SRC_ENUM_U32     enChannelID;    /* ����Դͨ��ID���̶����� */
    SOCP_CODER_DST_ENUM_U32     enDstCHID;      /* ����Ŀ��ͨ��ID */
    SOCP_DATA_TYPE_E            enDataType;     /* ������Դ���� */
    SOCP_ENCSRC_CHNMODE_E       enCHMode;       /* ͨ������ */
    SOCP_CHAN_PRIORITY_E        enCHLevel;      /* ͨ�����ȼ� */
    VOS_UINT8                   *pucSrcBuf;     /* ����Դͨ�����ݿռ��ڴ�ָ�� */
    VOS_UINT8                   *pucSrcPHY;
    VOS_UINT32                  ulSrcBufLen;    /* ����Դͨ�����ݿռ��С */
    VOS_UINT8                   *pucRDBuf;      /* ����Դͨ��RD���ݿռ��ڴ�ָ�� */
    VOS_UINT8                   *pucRDPHY;
    VOS_UINT32                  ulRDBufLen;     /* ����Դͨ��RD���ݿռ��С */
}SCM_CODER_SRC_CFG_STRU;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_CODER_DST_ENUM_U32     enChannelID;    /* ����Ŀ��ͨ��ID���̶����� */
    VOS_UINT8                   *pucBuf;        /* ����Ŀ��ͨ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucBufPHY;
    VOS_UINT32                  ulBufLen;       /* ����Ŀ��ͨ�����ݿռ��С */
    VOS_UINT32                  ulThreshold;    /* ����Ŀ��ͨ����ֵ */
    SCM_CODERDESTFUCN           pfunc;          /* ����Ŀ��ͨ�����ݴ���ص����� */
}SCM_CODER_DEST_CFG_STRU;


typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_DECODER_SRC_ENUM_U32   enChannelID;    /* ����Դͨ��ID���̶����� */
    VOS_UINT8                   *pucSrcBuf;     /* ����Դͨ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucSrcPHY;
    VOS_UINT32                  ulSrcBufLen;    /* ����Դͨ�����ݿռ��С */
}SCM_DECODER_SRC_CFG_STRU;

typedef struct
{
    SCM_CHANNEL_INIT_ENUM_U32   enInitState;    /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_DECODER_DST_ENUM_U32   enChannelID;    /* ����Ŀ��ͨ��ID���̶����� */
    SOCP_DECODER_SRC_ENUM_U32   enSrcCHID;      /* ����Դͨ��ID */
    SOCP_DATA_TYPE_E            enDataType;     /* ����������Դ���� */
    VOS_UINT8                   *pucBuf;        /* ����Ŀ�����ݿռ�ָ�� */
    VOS_UINT8                   *pucBufPHY;
    VOS_UINT32                  ulBufLen;       /* ����Ŀ�����ݿռ��С */
    VOS_UINT32                  ulThreshold;    /* ����Ŀ��ͨ����ֵ */
    SCM_DECODERDESTFUCN         pfunc;          /* ����Ŀ��ͨ�����ݴ���ص����� */
}SCM_DECODER_DEST_CFG_STRU;

#define INNER_LOG_DATA_MAX                   0x40

typedef struct
{
    VOS_UINT32                  ulSlice;
    VOS_UINT32                  ulFileNO;
    VOS_INT32                   lLineNO;
    VOS_UINT32                  ulP1;
    VOS_UINT32                  ulP2;
}INNER_LOG_RECORD_STRU;

typedef struct
{
    VOS_UINT32                  ulCnt;
    INNER_LOG_RECORD_STRU       astLogData[INNER_LOG_DATA_MAX];
}INNER_LOG_DATA_STRU;

typedef struct
{
    VOS_UINT32                  aulBDUsedMax[SCM_CODER_SRC_NUM];    /* ��¼�ϲ���õķ���Դͨ��BDʹ�����ֵ */
    VOS_UINT32                  aulRDUsedMax[SCM_CODER_SRC_NUM];    /* ��¼�ϲ���õķ���ԴRDʹ�����ֵ */
    INNER_LOG_DATA_STRU         stCoderSrcLog;                      /* ��¼�ϲ���õķ��ͽӿ�log */
    INNER_LOG_DATA_STRU         stCoderSrcRDLog;                    /* ��¼�ϲ���õ��ͷ�RD�ӿ�log */
    /*INNER_LOG_DATA_STRU         stCoderSrcReset;*/                /* ��¼�ϲ���õĸ�λ�ӿ�log,�ݲ�ʹ�� */
    INNER_LOG_DATA_STRU         stCoderSrcErr;                      /* ��¼����Դͨ���ص�����Log */
#ifdef SCM_ACORE
    INNER_LOG_DATA_STRU         stCoderDstLog;                      /* ��¼�ص��ϲ�ı���Ŀ��ͨ������Log */
    INNER_LOG_DATA_STRU         stCoderDstErr;                      /* ��¼����Ŀ��ͨ���ص�����Log */
    /*INNER_LOG_DATA_STRU         stDoderSrcLog;*/                  /* ��¼�ϲ���õĽ���Դͨ��Log,�ݲ�ʹ�� */
    /*INNER_LOG_DATA_STRU         stDecoderDstLog;*/                /* ��¼�ص��ϲ�Ľ���Ŀ��ͨ������Log,�ݲ�ʹ�� */
    /*INNER_LOG_DATA_STRU         stDecoderDstErr;*/                /* ��¼����Ŀ��ͨ���ص�����Log,�ݲ�ʹ�� */
    /*INNER_LOG_DATA_STRU         stDecoderSrcErr;*/                /* ��¼����Դͨ���ص�����Log,�ݲ�ʹ�� */
#endif
}SCM_INFODATA_STRU;


/**************************************************************************
  5 Log��������
**************************************************************************/
extern VOS_VOID OM_Inner_Log(VOS_CHAR *pucStr, VOS_UINT32 ulP1, VOS_UINT32 ulP2,
                          INNER_LOG_DATA_STRU *pstLogData ,VOS_UINT32 ulFileID, VOS_INT32 lLineNo);

#define SCM_CODER_SRC_LOG(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcLog, VOS_FILE_ID, __LINE__)

#define SCM_CODER_SRCRD_LOG(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcRDLog, VOS_FILE_ID, __LINE__)

#define SCM_CODER_SRCRESET_LOG(pucStr, ulP1, ulP2)\
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcReset, VOS_FILE_ID, __LINE__)*/

#define SCM_CODER_SRC_ERR(pucStr, ulP1, ulP2)\
	vos_printf("%s, %ul, %ul.\n", pucStr, ulP1, ulP2)
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderSrcErr, VOS_FILE_ID, __LINE__)*/

#ifdef SCM_ACORE
#define SCM_CODER_DST_ERR(pucStr, ulP1, ulP2)\
	printk("%s, %ul, %ul.\n", pucStr, ulP1, ulP2)
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderDstErr, VOS_FILE_ID, __LINE__)*/

#define SCM_DECODER_SRC_LOG(pucStr, ulP1, ulP2)\
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDoderSrcLog, VOS_FILE_ID, __LINE__)*/

#define SCM_CODER_DST_LOG(pucStr, ulP1, ulP2)\
    OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stCoderDstLog, VOS_FILE_ID, __LINE__)

#define SCM_DECODER_DST_LOG(pucStr, ulP1, ulP2)\
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDecoderDstLog, VOS_FILE_ID, __LINE__)*/

#define SCM_DECODER_DST_ERR(pucStr, ulP1, ulP2)\
	printk("%s, %ul, %ul.\n", pucStr, ulP1, ulP2)
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDecoderDstErr, VOS_FILE_ID, __LINE__)*/

#define SCM_DECODER_SRC_ERR(pucStr, ulP1, ulP2)\
	printk("%s, %ul, %ul.\n", pucStr, ulP1, ulP2)
    /*OM_Inner_Log(pucStr, ulP1, ulP2, &g_stSCMInfoData.stDecoderSrcErr, VOS_FILE_ID, __LINE__)*/
#endif

extern SCM_INFODATA_STRU           g_stSCMInfoData;    /* ���ڱ���log��Ϣ */

/**************************************************************************
  6 ��������
**************************************************************************/

extern VOS_UINT32 OM_GetSlice(VOS_VOID);

extern VOS_UINT8* SCM_VirtMemAlloc(VOS_UINT32 ulSize,VOS_UINT32 *pulRealAddr);

extern VOS_UINT32 SCM_MemVirtToPhy(VOS_UINT8 *pucCurVirtAddr, VOS_UINT8 *pucPhyStart, VOS_UINT8 *pucVirtStart, VOS_UINT32 ulBufLen);

extern VOS_UINT32 SCM_MemPhyToVirt(VOS_UINT8 *pucCurPhyAddr, VOS_UINT8 *pucPhyStart, VOS_UINT8 *pucVirtStart, VOS_UINT32 ulBufLen);

extern VOS_UINT32 SCM_RlsSrcRDAll(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT32 *pulDataAddr, VOS_UINT32 *pulDataLen);

extern VOS_UINT32 SCM_RlsSrcRDFirst(SOCP_CODER_SRC_ENUM_U32 enChanlID,VOS_UINT32 *pulDataAddr,VOS_UINT32 *pulDataLen);

extern VOS_UINT32 SCM_GetBDFreeNum(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT32 *pulBDNum);

extern VOS_UINT32 SCM_SendCoderSrc(SOCP_CODER_SRC_ENUM_U32 enChanlID, VOS_UINT8 *pucSendData, VOS_UINT32 ulSendLen);

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
extern VOS_UINT32 SCM_RlsDestBuf(VOS_UINT32 ulChanlID, VOS_UINT32 ulReadSize);

extern VOS_UINT32 SCM_RegCoderDestProc(SOCP_CODER_DST_ENUM_U32 enChanlID,SCM_CODERDESTFUCN func);

extern VOS_UINT32 SCM_RegDecoderDestProc(SOCP_DECODER_DST_ENUM_U32 enChanlID,SCM_DECODERDESTFUCN func);

extern VOS_UINT32 SCM_SendDecoderSrc(SOCP_DECODER_SRC_ENUM_U32 enChanlID, VOS_UINT8 *pucSendData, VOS_UINT32 ulSendLen);


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


