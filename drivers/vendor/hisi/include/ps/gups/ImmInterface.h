

#ifndef __IMMINTERFACE_H__
#define __IMMINTERFACE_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "linux/skbuff.h"
#include "vos.h"
#include "product_config.h"

#if ( FEATURE_ON == FEATURE_SKB_EXP )
#include "IMMmem.h"
#else
#include "IMMmem_PS.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define IMM_MAX_ETH_FRAME_LEN           (1536)
#define IMM_MAC_HEADER_RES_LEN          (14)
#define IMM_INVALID_VALUE               (0xFFFFFFFF)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/



extern IMM_ZC_STRU* IMM_ZcStaticAlloc_Debug(unsigned short usFileID, unsigned short usLineNums,
            unsigned int ulLen);

#define    IMM_ZcStaticAlloc(ulLen)\
    IMM_ZcStaticAlloc_Debug(THIS_FILE_ID, __LINE__, (ulLen))




#define IMM_ZcLargeMemAlloc(ulLen)  dev_alloc_skb((ulLen))


extern IMM_ZC_STRU * IMM_ZcDataTransformImmZc_Debug(unsigned short usFileID,
            unsigned short usLineNum, const unsigned char *pucData, unsigned long ulLen, void *pstTtfMem);


#define IMM_DataTransformImmZc(pucData, ulLen, pstTtfMem)\
    IMM_ZcDataTransformImmZc_Debug(THIS_FILE_ID, __LINE__, (pucData), (ulLen), (pstTtfMem))



extern  IMM_ZC_STRU* IMM_ZcStaticCopy_Debug(VOS_UINT16 usFileID, VOS_UINT16 usLineNums, IMM_ZC_STRU* pstImmZc);

#define IMM_ZcStaticCopy(pstImmZc)\
    IMM_ZcStaticCopy_Debug(THIS_FILE_ID, __LINE__, (pstImmZc))


#define    IMM_ZcFree( pstImmZc )        kfree_skb((pstImmZc))


extern void IMM_ZcHeadFree(IMM_ZC_STRU* pstImmZc);


extern VOS_VOID IMM_RbRemoteFreeMem(VOS_VOID *pucAddr);

#define IMM_RemoteFreeTtfMem(pucAddr)     IMM_RbRemoteFreeMem((pucAddr))



extern unsigned long IMM_ZcAddMacHead (IMM_ZC_STRU *pstImmZc, const unsigned char * pucAddData);


extern VOS_UINT32 IMM_ZcRemoveMacHead (IMM_ZC_STRU *pstImmZc);


extern IMM_MEM_STRU *IMM_ZcMapToImmMem_Debug(unsigned short usFileID,
            unsigned short usLineNum, IMM_ZC_STRU *pstImmZc);


#define IMM_ZcMapToImmMem(pstImmZc)\
    IMM_ZcMapToImmMem_Debug(THIS_FILE_ID, __LINE__, (pstImmZc))



extern unsigned long IMM_ZcGetLocalFreeMemCnt (void);
#define IMM_GetLocalFreeMemCnt()   IMM_ZcGetLocalFreeMemCnt()



extern unsigned char* IMM_ZcPush_Debug(unsigned short usFileId, unsigned short usLineNum,
            IMM_ZC_STRU *pstImmZc, unsigned int len);

#define    IMM_ZcPush(pstImmZc,ulLen)\
            IMM_ZcPush_Debug(THIS_FILE_ID, __LINE__, (pstImmZc), (ulLen))



extern unsigned char* IMM_ZcPull_Debug(unsigned short usFileID, unsigned short usLineNum,
            IMM_ZC_STRU *pstImmZc, unsigned int ulLen);

#define    IMM_ZcPull(pstImmZc,ulLen)\
            IMM_ZcPull_Debug(THIS_FILE_ID, __LINE__, (pstImmZc), (ulLen))


extern unsigned char* IMM_ZcPut_Debug(unsigned short usFileID, unsigned short usLineNum,
            IMM_ZC_STRU *pstImmZc, unsigned int ulLen);

#define    IMM_ZcPut(pstImmZc,ulLen)\
            IMM_ZcPut_Debug(THIS_FILE_ID, __LINE__, pstImmZc, ulLen)



extern void IMM_ZcReserve_Debug(unsigned short usFileID, unsigned short usLineNum,
            IMM_ZC_STRU *pstImmZc, unsigned int ulLen);

#define    IMM_ZcReserve(pstImmZc, ulLen)\
            IMM_ZcReserve_Debug(THIS_FILE_ID, __LINE__, pstImmZc, ulLen)



#define    IMM_ZcHeadRoom( pstImmZc)\
            skb_headroom(pstImmZc)


#define    IMM_ZcTailRoom( pstImmZc )\
            skb_tailroom(pstImmZc)


#define IMM_ZcGetDataPtr(pstImmZc)      ((pstImmZc)->data)



extern unsigned long IMM_ZcGetUsedLen (const IMM_ZC_STRU *pstImmZc);


extern unsigned short IMM_ZcGetUserApp(IMM_ZC_STRU *pstImmZc);





extern void IMM_ZcSetUserApp (IMM_ZC_STRU *pstImmZc, unsigned short usApp);



extern void IMM_ZcQueueHeadInit_Debug(unsigned short usFileID, unsigned short usLineNum,
                                                 IMM_ZC_HEAD_STRU *list);

#define    IMM_ZcQueueHeadInit(pstList)\
            IMM_ZcQueueHeadInit_Debug(THIS_FILE_ID, __LINE__, (pstList))




extern void IMM_ZcQueueHead_Debug(unsigned short usFileID, unsigned short usLineNum,
                                 IMM_ZC_HEAD_STRU *list, IMM_ZC_STRU *pstNew);

#define    IMM_ZcQueueHead(pstList, pstNew)\
            IMM_ZcQueueHead_Debug(THIS_FILE_ID, __LINE__, (pstList), (pstNew))



extern void IMM_ZcQueueTail_Debug(unsigned short usFileID, unsigned short usLineNum,
                                 IMM_ZC_HEAD_STRU *pstList, IMM_ZC_STRU *pstNew);

#define    IMM_ZcQueueTail(pstList, pstNew)\
            IMM_ZcQueueTail_Debug(THIS_FILE_ID, __LINE__, (pstList), (pstNew))



extern IMM_ZC_STRU* IMM_ZcDequeueHead_Debug(unsigned short usFileID, unsigned short usLineNum,
                             IMM_ZC_HEAD_STRU *pstList);

#define    IMM_ZcDequeueHead(pstList)\
            IMM_ZcDequeueHead_Debug(THIS_FILE_ID, __LINE__, (pstList))



extern IMM_ZC_STRU* IMM_ZcDequeueTail_Debug(unsigned short usFileID, unsigned short usLineNum,
                             IMM_ZC_HEAD_STRU *pstList);

#define    IMM_ZcDequeueTail(pstList)\
            IMM_ZcDequeueTail_Debug(THIS_FILE_ID, __LINE__, (pstList))



extern unsigned int IMM_ZcQueueLen_Debug(unsigned short usFileID, unsigned short usLineNum,
                             IMM_ZC_HEAD_STRU *pstList);

#define    IMM_ZcQueueLen(pstList)\
            IMM_ZcQueueLen_Debug(THIS_FILE_ID, __LINE__, (pstList))


#define    IMM_ZcQueuePeek(pstList)        skb_peek((pstList))



#define    IMM_ZcQueuePeekTail(pstList)    skb_peek_tail((pstList))



VOS_VOID IMM_MntnAcpuCheckPoolLeak( VOS_VOID );



extern unsigned long IMM_MemRegEventCallBack
(
    IMM_MEM_POOL_ID_ENUM_UINT8          enPoolId,
    IMM_MEM_EVENT_CALLBACK              pMemAllocEvent,
    IMM_MEM_EVENT_CALLBACK              pMemFreeEvent
);



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of ImmInterface.h */

