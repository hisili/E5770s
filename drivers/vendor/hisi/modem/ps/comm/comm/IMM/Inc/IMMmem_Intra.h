

#ifndef __IMM_MEM_INTRA_H__
#define __IMM_MEM_INTRA_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "ImmInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* IMM �ڴ�ؿ��ܵ���󳤶� */
#define IMM_MEM_BLK_MAX_BYTE_LEN        (1953)

/* IMM �ڴ�ؿ��ܵ���൵λ */
#define IMM_MEM_BLK_MAX_CLUSTER_NUM     (8)

/* IMM ����ͷ����ڴ�ָ�� */
#define IMM_ADD_CTL_HEAD_MEM(pstImmHead, pMem)          ((pstImmHead)->p_Imm_Ttf_Mem = (pMem))

#define IMM_GET_4BYTE_ALIGN_VALUE(ulSize)   ( ((ulSize) + 0x03) & (~0x03) )

#define IMM_CACHE_INVALID(data, len) __dma_single_dev_to_cpu_nocheck(data, len, DMA_FROM_DEVICE)
#define IMM_CACHE_FLUSH(data, len) __dma_single_cpu_to_dev_nocheck(data, len, DMA_TO_DEVICE)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
#define IMM_DEBUG_TRACE_FUNC            FEATURE_OFF
extern unsigned char                    g_ucImmMemDebugPrint;


#ifdef _lint

#define IMM_DEBUG_TRACE_FUNC_ENTER()
#define IMM_DEBUG_TRACE_FUNC_LEAVE()

#else

#if(IMM_DEBUG_TRACE_FUNC == FEATURE_ON)

#ifdef __UT_CENTER__
#define __func__ __FUNCTION__
#endif

/* ���Դ�ӡ */
/*
#define IMM_DEBUG_PRINT(...)\
             do{\
                 if ( PS_TRUE == g_ucMemDebugPrint )\
                 {\
                     vos_printf(__VA_ARGS__);
                 }\
             }while(0)
*/


#define IMM_DEBUG_TRACE_FUNC_ENTER()\
                do{\
                    if ( IMM_TRUE == g_ucImmMemDebugPrint )\
                    {\
                        printk("Enter Function: ");\
                        printk(__func__);\
                        printk("\n");\
                    }\
                }while(0)

#define IMM_DEBUG_TRACE_FUNC_LEAVE()\
                do{\
                    if ( IMM_TRUE == g_ucImmMemDebugPrint )\
                    {\
                        printk("Normal Leave Function: ");\
                        printk(__func__);\
                        printk("\n");\
                    }\
                }while(0)
#else
#define IMM_DEBUG_TRACE_FUNC_ENTER()
#define IMM_DEBUG_TRACE_FUNC_LEAVE()
#endif
#endif


enum IMM_MEM_USED_INFO_TRIG_TYPE_ENUM
{
    IMM_MEM_TRIG_TYPE_ALERT                      = 0x0,     /*�ڴ泬���޸澯*/
    IMM_MEM_TRIG_TYPE_ALLOC_FAIL,                           /*�ڴ�����ʧ��*/
    IMM_MEM_TRIG_TYPE_LEAK,                                 /*��鵽���ڴ�й¶*/
    IMM_MEM_TRIG_TYPE_OVERTIME_OCCUPANCY,                   /* ��⵽���ڴ汻����ʱ��ʹ�� */
    IMM_MEM_TRIG_TYPE_BUTT
};
typedef unsigned char IMM_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8;

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


enum IMM_MEM_TYPE_ID_ENUM
{
    IMM_MEM_TYPE_ID_SHARE = 0,              /* A�˹����ڴ�� */
    IMM_MEM_TYPE_ID_EXT,                    /* ����C�˵Ŀ���ڴ� */

    IMM_MEM_TYPE_ID_BUTT
};
typedef unsigned char IMM_MEM_TYPE_ID_ENUM_UINT8;



enum IMM_INVALID_MEM_TYPE_ENUM
{
    IMM_INVALID_MEM_TYPE_MAGICNUM = 1,              /* �ڴ�ħ���ִ��� */
    IMM_INVALID_MEM_TYPE_POOLID,                    /* �ڴ��ID�Ƿ�  */
    IMM_INVALID_MEM_TYPE_CTRLADDR,                  /* �ڴ��ַ�Ƿ� */
    IMM_INVALID_MEM_TYPE_STUTAS,                    /* �ڴ�״̬���� */

    IMM_INVALID_MEM_TYPE_BUTT
};
typedef unsigned char IMM_INVALID_MEM_TYPE_ENUM_UINT8;


typedef struct
{
    /*��������IMM_MEM_STRU�ܸ���*/
    unsigned short                      usTotalCnt;

    /*��������IMM_MEM_STRU���и���*/
    unsigned short                      usFreeCnt;

    /*�����ڴ�����ݳ���*/
    unsigned short                      usLen;

    unsigned char                       aucRsv[2];

    /*��¼IMM_MEM_ST�����ڴ��������ջ��Ԫ�أ�������ΪIMM_MEM_STָ�� */
    IMM_MEM_STRU                      **apstFreeStack;
}IMM_MEM_CLUSTER_STRU;


typedef void (*IMM_MEM_EXT_FREE_CALLBACK)(void *pAddr);
typedef void (*IMM_MEM_USED_INFO_EVENT_RPT_CALLBACK)( unsigned char  ucPoolId, IMM_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8 enTrigType );
typedef unsigned long (*IMM_OM_GET_SLICE_CALLBACK)(void);


typedef struct
{
    /* ��ʶ���ڴ���Ƿ�ʹ�� */
    unsigned char                       ucUsedFlag;

    /* ���ڴ��һ���ж��ټ�*/
    unsigned char                       ucClusterCnt;

    /* ���ڴ����ʹ�õ�����û��ֽ� */
    unsigned short                      usMaxByteLen;

    /* ָ�򳤶��������ָ�� */
    unsigned char                       aucLenIndexTable[IMM_MEM_BLK_MAX_BYTE_LEN];
    unsigned char                       aucResv[3];

    /* ָ�����������ָ�� */
    IMM_MEM_CLUSTER_STRU                astClusterTable[IMM_MEM_BLK_MAX_CLUSTER_NUM];

    unsigned short                      usImmMemTotalCnt;       /* ���ڴ��һ���ж���IMM_MEM_ST */
    unsigned short                      usImmMemUsedCnt;        /* ʹ���˶���IMM_MEM_ST */

    unsigned short                      usImmExcThresholdCnt;   /* �����ڴ�ʧ�ܳ������޴��� */
    unsigned short                      usImmAllocFailCnt;      /* ���һ�ι����������ڴ�ʧ�ܴ��� */

    unsigned long                       ulImmMemMaxBlkCcpuUsedCnt; /* ��ߵ�A�˴���C�˵Ŀ���� */

    IMM_MEM_STRU                       *pstImmMemStStartAddr;   /* ָ��ImmMemST�׵�ַ��ָ�� */
    IMM_MEM_EVENT_CALLBACK              pMemAllocEvent;
    IMM_MEM_EVENT_CALLBACK              pMemFreeEvent;
    IMM_MEM_EXT_FREE_CALLBACK           pMemExtFreeFunc;        /* ָ���ⲿע����ͷź���*/
} IMM_MEM_POOL_STRU;



typedef struct
{
    unsigned short                          usSize;    /* �������Ĵ�С */
    unsigned short                          usCnt;     /* �������� */
}IMM_MEM_CLUSTER_CFG_INFO_STRU;



typedef struct
{
    IMM_MEM_POOL_ID_ENUM_UINT8          enPoolId;           /* ���� ID */
    unsigned char                       ucClusterCnt;       /* ���ڴ���ж��ټ� */
    unsigned char                       aucResv[2];

    IMM_MEM_CLUSTER_CFG_INFO_STRU      *pstClusterCfgInfo;  /* ÿ���ľ�����Ϣ */
} IMM_MEM_POOL_CFG_INFO_STRU;



typedef struct
{
    IMM_OM_GET_SLICE_CALLBACK                   pImmOmGetSliceFunc;   /* ��ȡCPU CLICE ע�ắ��ָ�� */
    IMM_MEM_USED_INFO_EVENT_RPT_CALLBACK        pImmMemEventRptFunc;  /* �ϱ��ڴ��¼�ע�ắ��ָ�� */
}IMM_MEM_REG_MNTN_FUNC_STRU;

/*****************************************************************************
 �ṹ��    : IMM_MEM_FREE_NULL_PTR_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMM MEM FREE�յ���ָ����Ϣ
*****************************************************************************/
typedef struct IMM_MEM_FREE_NULL_PTR_INFO
{
    unsigned long           ulImmMemFreeNullPtrCnt;     /* ImmMemFree �յ���ָ����� */
    unsigned short          usImmMemFreeFileId;         /* ImmMemFree �յ���ָ������ļ�ID�����������һ���յ���ָ���ļ�ID��Ϣ */
    unsigned short          usImmMemFreeLineNum;        /* ImmMemFree �յ���ָ������ļ�ID�����������һ���յ���ָ���к���Ϣ */
}IMM_MEM_FREE_NULL_PTR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMM_MEM_FREE_INVALIED_MEM_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMM MEM FREE �յ��ķǷ�IMM MEM �ڴ���Ϣ
*****************************************************************************/
typedef struct IMM_MEM_FREE_INVALIED_MEM_INFO
{
    unsigned long                           ulInvalidImmMemCnt;         /* IMM MEM FREE �յ��ķǷ��ڴ���� */
    unsigned long                           ulInvalidImmMemAddr;        /* IMM MEM FREE ���һ���յ��ķǷ�IMM MEM �ڴ��ַ */
    unsigned short                          usImmMemFreeFileId;         /* IMM MEM FREE ���һ���յ��ķǷ�IMM MEM �ڴ��ļ�ID��Ϣ */
    unsigned short                          usImmMemFreeLineNum;        /* IMM MEM FREE ���һ���յ��ķǷ�IMM MEM �ڴ��к���Ϣ */
    IMM_INVALID_MEM_TYPE_ENUM_UINT8         ucImmMemInvalidType;        /* IMM MEM FREE ���һ���յ��ķǷ�IMM MEM �ڴ�������Ϣ */
    unsigned char                           aucReserve[1];              /* ���� */
    unsigned short                          usImmMemInvalidValue;       /* IMM MEM FREE ���һ���յ��ķǷ�IMM MEM �ڴ����ֵ */
}IMM_MEM_FREE_INVALIED_MEM_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMM_MEM_FREE_MNTN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����IMM �ڴ��ͷſ�ά�ɲ���Ϣ
*****************************************************************************/
typedef struct IMM_MEM_FREE_MNTN_INFO
{
    IMM_MEM_FREE_INVALIED_MEM_INFO_STRU astImmMemFreeInvalidMemInfo;    /* IMM MEM FREE �յ��ķǷ�IMM MEM �ڴ���Ϣ */
    IMM_MEM_FREE_NULL_PTR_INFO_STRU     astImmMemFreeNullPtrInfo;       /* IMM MEM FREE �յ�һ��ָ��Ϊ�յ���Ϣ */
    IMM_MEM_FREE_NULL_PTR_INFO_STRU     astImmMemFreeNullPPtrInfo;      /* IMM MEM FREE �յ�����ָ��Ϊ�յ���Ϣ */
    unsigned long                       ulImmMemExtFreeFailCnt;         /* IMM MEM �ͷ��ⲿ�ڴ�ʧ�ܴ��� */
}IMM_MEM_FREE_MNTN_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern IMM_MEM_POOL_STRU                        g_astImmMemPool[IMM_MEM_POOL_ID_BUTT];
extern IMM_MEM_POOL_STRU * const                g_pstImmExtMemPool;
extern const IMM_MEM_CLUSTER_CFG_INFO_STRU      g_astImmMemCtrlPoolClusterTableInfo[];
extern const unsigned long * const              g_pulImmMemCtrlMemSuffix;
extern const unsigned long * const              g_paulImmMemCtrlMemSpace;
extern unsigned short                           g_usImmAllocFailCntThreshold;
extern unsigned short * const                   g_apusImmExcThresholdCnt[];
extern unsigned short * const                   g_apusImmAllocFailCnt[];
extern IMM_MEM_FREE_MNTN_INFO_STRU              g_stImmMemFreeMntnEntity;


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern void IMM_MemRegMntnFuncCallBack
(
    IMM_OM_GET_SLICE_CALLBACK   pImmOmGetSliceFunc,
    IMM_MEM_USED_INFO_EVENT_RPT_CALLBACK    pImmMemEventRptFunc
);

extern  unsigned long IMM_MemRegExtFreeCallBack
(
    IMM_MEM_EXT_FREE_CALLBACK           pMemExtFreeFunc
);

extern  IMM_MEM_POOL_STRU *IMM_MemPoolGet(unsigned char ucPoolId);

extern void IMM_MemFreeShowMntnInfo(void);

/* IMM MEM ��ȡ�ڴ��ָ�� */
#define IMM_MEM_GET_POOL(ucPoolId)      (&g_astImmMemPool[(ucPoolId)])

#define IMM_MEM_CTRL_HEAD_ALLOC(usFileID, usLineNum)\
        IMM_MemAlloc_Debug(usFileID, usLineNum, IMM_MEM_POOL_ID_EXT, 0 )


#pragma pack(0)



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of IMM.h */

