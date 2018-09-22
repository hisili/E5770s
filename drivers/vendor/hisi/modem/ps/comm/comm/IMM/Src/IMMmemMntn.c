



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "IMMmemMntn.h"
#include "om.h"
#include "OmApp.h"
#include "IMMmemRB.h"
#include "linux/skbuff.h"
#include "PsCommonDef.h"

#include <asm/atomic.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*lint -e767*/
#define THIS_FILE_ID                     PS_FILE_ID_IMM_MNTN_C
/*lint +e767*/
#if (FEATURE_ON == FEATURE_SKB_EXP)


const VOS_UINT8             g_ulImmBlkMemCheck = 1;             /* �����Ƿ����IMM BLK MEM */


#define IMM_BLK_MEM_DEBUG_SWITCH_ON     (1 == g_ulImmBlkMemCheck)

/* �ڴ����¼���ǰʱ�� */
VOS_UINT32                              g_ulCurrentTimeSlice = 0;

/* �ڴ��ռ��ʱ�䳬ʱ���� 1s */
const VOS_UINT32                        g_ulOverTimeSliceThreshold = 32768*1;

/* �ڴ�й¶�¼��ϱ��������ȫ�ֱ��� */
atomic_t                                g_stIMMBlkMemAlertEvtCnt = ATOMIC_INIT(0);

/* �ڴ�����ʧ���¼��ϱ��������ȫ�ֱ��� */
atomic_t                                g_stIMMBlkMemAlocFailEvtCnt = ATOMIC_INIT(0);

/* IMM �ڴ�ؿ�ά�ɲ���¼��ϱ��������ڴ���� */
const VOS_UINT16                        EVENT_BLK_MEM_USED_INFO_CNT_PER_MSG = 41;

/* IMM ÿ�η����ڴ��ϱ��¼�ʱ��ÿ�������ڴ��¼��������� */
VOS_UINT32                              g_ulImmEventRptCntThresholdPerTime = 1;

VOS_UINT8                               g_ucPrintDetail = IMM_FALSE;

atomic_t                                g_stCheckLeakFlag = ATOMIC_INIT(0);

extern VOS_UINT32                       g_ulImmMemRbFreeSem;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/



VOS_UINT8 IMM_MntnCheckReportMemInfoStatus( IMM_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8 enTrigType )
{

    /*
    ������������ϱ��¼�
    1�������ڴ�й¶:IMM_MEM_TRIG_TYPE_LEAK
    2����һ�η����ڴ�����ʧ��:IMM_MEM_TRIG_TYPE_ALLOC_FAIL
    3����һ�η����ڴ治��澯:IMM_MEM_TRIG_TYPE_ALERT
    */

    if ( IMM_MEM_TRIG_TYPE_LEAK == enTrigType )
    {
        return IMM_TRUE;
    }
    else if( IMM_MEM_TRIG_TYPE_ALLOC_FAIL == enTrigType )
    {
        if ( 0 == atomic_read(&g_stIMMBlkMemAlocFailEvtCnt) )
        {
            atomic_inc(&g_stIMMBlkMemAlocFailEvtCnt);
        }
    }
    else if( IMM_MEM_TRIG_TYPE_ALERT == enTrigType )
    {
        if ( 0 == atomic_read(&g_stIMMBlkMemAlertEvtCnt) )
        {
            atomic_inc(&g_stIMMBlkMemAlertEvtCnt);
        }
    }
    else
    {
        return IMM_FALSE;
    }

    return IMM_TRUE;

}



VOS_VOID IMM_MntnPrintBlkMemPoolUsedInfo( IMM_MEM_POOL_STRU  *pstImmMemPoolInfo )
{
#if (FEATURE_ON == FEATURE_IMM_MEM_DEBUG)
    VOS_UINT16                          usImmMemNum;
    IMM_BLK_MEM_DEBUG_STRU             *pstImmMemDebugInfo;
#endif
    IMM_MEM_STRU                       *pMem;


    if (VOS_NULL_PTR == pstImmMemPoolInfo)
    {
       IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_WARNING, "pstImmMemPoolInfo is NULL ! \n");
       return ;
    }


    if (IMM_TRUE != pstImmMemPoolInfo->ucUsedFlag)
    {
       IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_WARNING, "POOL not uesed ! \n");

       return ;
    }

    pMem = pstImmMemPoolInfo->pstImmMemStStartAddr;

    IMM_LOG2(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "Pool ID %u Blk Mem used %u  \n", pMem->enPoolId, pstImmMemPoolInfo->usImmMemUsedCnt);

    if( IMM_FALSE == g_ucPrintDetail )
    {
        return;
    }

#if (FEATURE_ON == FEATURE_IMM_MEM_DEBUG)
    for (usImmMemNum = 0;
            usImmMemNum < pstImmMemPoolInfo->usImmMemTotalCnt;
            usImmMemNum ++)
    {
        pMem = pstImmMemPoolInfo->pstImmMemStStartAddr + usImmMemNum;
        pstImmMemDebugInfo = &pMem->stDbgInfo;

        if ( MEM_BLK_STATE_FREE != pstImmMemDebugInfo->enMemStateFlag)
        {
            IMM_LOG4(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "Alloc: File %4d L %5d T %11u, Blk Mem Level: %4u, ",
                (VOS_INT32)pstImmMemDebugInfo->usAllocFileID,
                (VOS_INT32)pstImmMemDebugInfo->usAllocLineNum,
                (VOS_INT32)pstImmMemDebugInfo->ulAllocTick,
                usImmMemNum);
/*lint -e713*/
            IMM_LOG4(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "Status: %d, Status: %d, TraceFile:%4d, TraceLine:%5d, TraceTick:%11d, \n",
                pstImmMemDebugInfo->enMemStateFlag,
                (VOS_INT32)pstImmMemDebugInfo->usTraceFileID,
                (VOS_INT32)pstImmMemDebugInfo->usTraceLineNum,
                (VOS_INT32)pstImmMemDebugInfo->ulTraceTick);
/*lint +e713*/

            /* ��ӡPDU���� */
            IMM_LOG1(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "Data ptr: 0x%x\n ", (VOS_INT32)pMem->pstMemBlk);
        }
    }
#endif

}/* IMM_MntnPrintBlkMemPoolUsedInfo */



VOS_VOID IMM_MntnShowUsedBlkMemInfo(VOS_VOID)
{
    IMM_MEM_POOL_STRU                  *pstImmMemPoolInfo;
    VOS_UINT8                           ucPoolId;


    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_ShowUsedBlkMemInfo:Begin.\r\n");

    for (ucPoolId = 0; ucPoolId < IMM_MEM_POOL_ID_BUTT; ucPoolId++)
    {
        pstImmMemPoolInfo = IMM_MemPoolGet(ucPoolId);

        IMM_LOG1(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_ShowUsedBlkMemInfo print pool %d info begin: \n", ucPoolId );
        IMM_MntnPrintBlkMemPoolUsedInfo(pstImmMemPoolInfo);
        IMM_LOG1(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_ShowUsedBlkMemInfo print pool %d info end! \n", ucPoolId);
    }

    return ;
}/*IMM_MntnShowUsedBlkMemInfo */



VOS_VOID IMM_MntnMemUseBlkCntRpt
(
    VOS_UINT8                               ucPoolId,
    IMM_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8  enTrigType
)
{
    VOS_UINT32                              ulTotalCnt;
    VOS_UINT32                              ulLength;
    VOS_UINT32                              ulDataLen;
    PS_OM_EVENT_IND_STRU                   *pstImmOmEventInd;
    IMM_MEM_POOL_STRU                      *pstPoolInfo;
    IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU    *pstImmOmEventBlkMemUsedInfo;


    pstPoolInfo     = IMM_MEM_GET_POOL(ucPoolId);

    ulDataLen = offsetof(IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU, astBlkMemTraceInfo);

    /*��Ϣ�ܳ���*/
    ulLength  = offsetof(PS_OM_EVENT_IND_STRU, aucData) + ulDataLen;

    /*������Ϣ�ڴ�*/
    pstImmOmEventInd    = (PS_OM_EVENT_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_IMM_RB_FREE, ulLength);

    if (VOS_NULL_PTR == pstImmOmEventInd )
    {
        IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_ERROR, "IMM_BlkMemUsedInfoEventRpt: MemAlloc Fail!\n");
        return;
    }

    ulTotalCnt      = pstPoolInfo->usImmMemUsedCnt;

    /*��д��Ϣ����*/
    pstImmOmEventInd->ulLength      = ulLength - offsetof( PS_OM_EVENT_IND_STRU, usEventId);
    pstImmOmEventInd->usEventId     = IMM_EVENT_BLK_MEM_USED_INFO;
    pstImmOmEventInd->ulModuleId    = UEPS_PID_IMM_RB_FREE;

    pstImmOmEventBlkMemUsedInfo     = (IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU *)pstImmOmEventInd->aucData;
    pstImmOmEventBlkMemUsedInfo->ucPoolId       = ucPoolId;
    pstImmOmEventBlkMemUsedInfo->enTrigType     = enTrigType;
    pstImmOmEventBlkMemUsedInfo->ucNo           = 1;
    pstImmOmEventBlkMemUsedInfo->usRptCnt       = 0;
    pstImmOmEventBlkMemUsedInfo->ulTotalUsedCnt = ulTotalCnt;

    /*����OM���¼��ϱ��ӿ�*/
    if ( PS_SUCC != OM_AcpuEvent((PS_OM_EVENT_IND_STRU*)pstImmOmEventInd))
    {
        IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_ERROR, "IMM_BlkMemUsedInfoEventRpt: OM Send Event Fail! \n");
    }
    /*�ͷ�������ڴ�*/
    PS_MEM_FREE(UEPS_PID_IMM_RB_FREE, pstImmOmEventInd);

    return;
}/* IMM_MntnMemUseBlkCntRpt */



VOS_UINT32 IMM_MntnTimeDiff(VOS_UINT32 ulTimeStart, VOS_UINT32 ulTimeEnd)
{
    VOS_UINT32                          ulTimeDiff;


    if (ulTimeEnd > ulTimeStart)
    {
        ulTimeDiff = ulTimeEnd - ulTimeStart;
    }
    else
    {
        /* �����ʼʱ����ڽ���ʱ�䣬˵��������ת��ֻ��Ϊ������תһ�� */
        ulTimeDiff = PS_NULL_UINT32 + ulTimeEnd - ulTimeStart + 1;
    }

    return ulTimeDiff;
} /* IMM_MntnTimeDiff */


#if (FEATURE_ON == FEATURE_IMM_MEM_DEBUG)

VOS_UINT32 IMM_MntnGetOverMemBlkCnt( VOS_UINT8 ucPoolId )
{
    IMM_MEM_POOL_STRU                  *pstImmMemPool;
    IMM_BLK_MEM_DEBUG_STRU             *pstImmMemDebugInfo;
    IMM_MEM_STRU                       *pstMem;
    VOS_UINT32                          ulBlkMemNum;
    VOS_UINT32                          ulTotolCnt = 0;


    /* ��ȡ��ǰCPU Slice */
    g_ulCurrentTimeSlice = OM_GetSlice();
    pstImmMemPool        = IMM_MEM_GET_POOL(ucPoolId);

    /* �����ڴ��ÿ���ڴ� */
    for (ulBlkMemNum = 0; ulBlkMemNum < pstImmMemPool->usImmMemTotalCnt; ++ulBlkMemNum )
    {
        pstMem = pstImmMemPool->pstImmMemStStartAddr + ulBlkMemNum;
        pstImmMemDebugInfo = &pstMem->stDbgInfo;

        /* �ڴ��״̬��� */
        if ( MEM_BLK_STATE_FREE == pstImmMemDebugInfo->enMemStateFlag )
        {
            continue;
        }

        /* �ж��ڴ�����ʱ���뵱ǰʱ��֮���Ƿ񳬹����� */
        if ( g_ulOverTimeSliceThreshold <= IMM_MntnTimeDiff(pstImmMemDebugInfo->ulAllocTick, g_ulCurrentTimeSlice))
        {
            ++ ulTotolCnt;
        }
    }

    return ulTotolCnt;
}/* IMM_MntnGetOverMemBlkCnt */



VOS_VOID IMM_MntnMemTraceInfoRptSaveMemData
(
    VOS_UINT8  ucPoolId,
    IMM_BLK_MEM_TRACE_INFO_STRU *pstBlkMemTraceInfo,
    IMM_MEM_STRU *pMem
)
{

    if ( ucPoolId != pMem->enPoolId )
    {
        IMM_LOG2(UEPS_PID_IMM_RB_FREE, IMM_PRINT_ERROR, "IMM_MntnMemTraceInfoRptSaveMemData, ucPoolId %d, pMem->enPoolId %d Mismatch! \n", ucPoolId, pMem->enPoolId);
        return;
    }

    if ( IMM_MEM_POOL_ID_SHARE == ucPoolId )
    {
        if ( NULL != pMem->pstMemBlk )
        {
            pstBlkMemTraceInfo->aucMemData[0]   = pMem->pstMemBlk[0];
            pstBlkMemTraceInfo->aucMemData[1]   = pMem->pstMemBlk[1];
            pstBlkMemTraceInfo->aucMemData[2]   = pMem->pstMemBlk[2];
            pstBlkMemTraceInfo->aucMemData[3]   = pMem->pstMemBlk[3];
        }
        else
        {
            VOS_MemSet(pstBlkMemTraceInfo->aucMemData, 0, 4);
            IMM_LOG1(UEPS_PID_IMM_RB_FREE, IMM_PRINT_ERROR, "IMM_MntnMemTraceInfoRptSaveMemData, ucPoolId %d Mem Ptr is Null! \n", ucPoolId);
        }

        return;
    }

    if ( IMM_MEM_POOL_ID_EXT == ucPoolId )
    {
        *((VOS_UINT32 *)pstBlkMemTraceInfo->aucMemData) = (VOS_UINT32)pMem->pstMemBlk;
    }

    return;
}/* IMM_MntnMemTraceInfoRptSaveMemData */



VOS_VOID IMM_MntnMemUsedBlkTraceInfoRpt
(
    VOS_UINT8  ucPoolId,
    IMM_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8 enTrigType
)
{
    VOS_UINT32                              ulTotalCnt;
    VOS_UINT32                              ulLength;
    VOS_UINT32                              ulDataLen;
    PS_OM_EVENT_IND_STRU                   *pstImmOmEventInd;
    IMM_MEM_POOL_STRU                      *pstPoolInfo;
    IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU    *pstImmOmEventBlkMemUsedInfo;
    IMM_BLK_MEM_TRACE_INFO_STRU            *pstBlkMemTraceInfo;
    VOS_UINT32                              ulBlkMemNum;
    IMM_MEM_STRU                           *pMem;
    IMM_BLK_MEM_DEBUG_STRU                 *pstImmMemDebugInfo;
    VOS_UINT32                              ulOffset;
    VOS_UINT8                               ucRptNo = 0;
    VOS_UINT16                              usRptCnt = 0;
    VOS_UINT16                              usRptEventCnt = 0;


    pstPoolInfo = IMM_MEM_GET_POOL(ucPoolId);

    ulTotalCnt  = pstPoolInfo->usImmMemUsedCnt;

    /* �ϱ��ڴ������Ϣ */
    ulDataLen           = offsetof(IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU, astBlkMemTraceInfo) + ( EVENT_BLK_MEM_USED_INFO_CNT_PER_MSG * sizeof(IMM_BLK_MEM_TRACE_INFO_STRU));

    /*��Ϣ�ܳ���*/
    ulLength            = offsetof(PS_OM_EVENT_IND_STRU,aucData) + ulDataLen;

    /*������Ϣ�ڴ�*/
    pstImmOmEventInd    = (PS_OM_EVENT_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_IMM_RB_FREE, ulLength);

    if ( VOS_NULL_PTR == pstImmOmEventInd )
    {
        IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_ERROR, "IMM_BlkMemUsedInfoEventRpt: MemAlloc Fail!");
        return;
    }

    if ( IMM_TRUE == pstPoolInfo->ucUsedFlag )
    {
        for (ulBlkMemNum = 0; ulBlkMemNum < pstPoolInfo->usImmMemTotalCnt; ulBlkMemNum ++)
        {
            pMem = pstPoolInfo->pstImmMemStStartAddr + ulBlkMemNum;
            pstImmMemDebugInfo = &pMem->stDbgInfo;

            if (MEM_BLK_STATE_FREE != pstImmMemDebugInfo->enMemStateFlag)
            {
                ulOffset    =  offsetof(IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU, astBlkMemTraceInfo)  + ( usRptCnt * sizeof(IMM_BLK_MEM_TRACE_INFO_STRU) );

                pstBlkMemTraceInfo  = (IMM_BLK_MEM_TRACE_INFO_STRU *)(pstImmOmEventInd->aucData + ulOffset );
                pstBlkMemTraceInfo->ulAllocTick         = pstImmMemDebugInfo->ulAllocTick;
                pstBlkMemTraceInfo->usAllocFileId       = pstImmMemDebugInfo->usAllocFileID;
                pstBlkMemTraceInfo->usAllocLineNum      = pstImmMemDebugInfo->usAllocLineNum;

                pstBlkMemTraceInfo->ulTraceTick         = pstImmMemDebugInfo->ulTraceTick;
                pstBlkMemTraceInfo->usTraceFileId       = (pstImmMemDebugInfo->usTraceFileID);
                pstBlkMemTraceInfo->usTraceLineNum      = (pstImmMemDebugInfo->usTraceLineNum);

                IMM_MntnMemTraceInfoRptSaveMemData(ucPoolId, pstBlkMemTraceInfo, pMem);

                usRptCnt ++;

                if (  EVENT_BLK_MEM_USED_INFO_CNT_PER_MSG == usRptCnt )/* �������ͣ�ÿ����෢��һǧ�� */
                {
                    ucRptNo++;
                    usRptCnt = 0;
                    /*��д��Ϣ����*/

                    pstImmOmEventInd->ulLength      = ulLength - offsetof( PS_OM_EVENT_IND_STRU, usEventId);
                    pstImmOmEventInd->usEventId     = IMM_EVENT_BLK_MEM_USED_INFO;
                    pstImmOmEventInd->ulModuleId    = UEPS_PID_IMM_RB_FREE;

                    pstImmOmEventBlkMemUsedInfo     = (IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU *)pstImmOmEventInd->aucData;
                    pstImmOmEventBlkMemUsedInfo->ucPoolId       = ucPoolId;
                    pstImmOmEventBlkMemUsedInfo->enTrigType     = enTrigType;
                    pstImmOmEventBlkMemUsedInfo->ucNo           = ucRptNo;
                    pstImmOmEventBlkMemUsedInfo->usRptCnt       = EVENT_BLK_MEM_USED_INFO_CNT_PER_MSG;
                    pstImmOmEventBlkMemUsedInfo->ulTotalUsedCnt = ulTotalCnt;

                    /*����OM���¼��ϱ��ӿ�*/
                    if ( PS_SUCC != OM_AcpuEvent((PS_OM_EVENT_IND_STRU*)pstImmOmEventInd))
                    {
                        IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_ERROR, "IMM_BlkMemUsedInfoEventRpt: OM Send Event Fail! \n");
                    }

                    ++usRptEventCnt;
                }

                if ( g_ulImmEventRptCntThresholdPerTime < usRptEventCnt )
                {
                    /* �ͷ�������ڴ� */
                    PS_MEM_FREE(UEPS_PID_IMM_RB_FREE, pstImmOmEventInd);
                    return;
                }

            }
        }
    }

    if ( 0 != usRptCnt )/* ���һ�����ݿ������� EVENT_BLK_MEM_USED_INFO_CNT_PER_MSG */
    {
        ucRptNo++;

        ulDataLen   = ( usRptCnt * sizeof(IMM_BLK_MEM_TRACE_INFO_STRU))  + offsetof(IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU, astBlkMemTraceInfo) ;

        ulLength    = offsetof(PS_OM_EVENT_IND_STRU, aucData) + ulDataLen;

        /*��д��Ϣ����*/
        pstImmOmEventInd->ulLength      = ulLength - offsetof( PS_OM_EVENT_IND_STRU, usEventId);
        pstImmOmEventInd->usEventId     = IMM_EVENT_BLK_MEM_USED_INFO;
        pstImmOmEventInd->ulModuleId    = UEPS_PID_IMM_RB_FREE;

        pstImmOmEventBlkMemUsedInfo     = (IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU *)pstImmOmEventInd->aucData;
        pstImmOmEventBlkMemUsedInfo->ucPoolId       = ucPoolId;
        pstImmOmEventBlkMemUsedInfo->enTrigType     = enTrigType;
        pstImmOmEventBlkMemUsedInfo->ucNo           = ucRptNo;
        pstImmOmEventBlkMemUsedInfo->usRptCnt       = usRptCnt;
        pstImmOmEventBlkMemUsedInfo->ulTotalUsedCnt = ulTotalCnt;

        /*����OM���¼��ϱ��ӿ�*/
        if ( PS_SUCC != OM_AcpuEvent((PS_OM_EVENT_IND_STRU*)pstImmOmEventInd))
        {
            IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_ERROR, "IMM_BlkMemUsedInfoEventRpt: OM Send Event Fail! \n");
        }
    }

    /*�ͷ�������ڴ�*/
    PS_MEM_FREE(UEPS_PID_IMM_RB_FREE, pstImmOmEventInd);

    return ;

}



VOS_UINT32 IMM_MntnReportMemLeakMsg( VOS_UINT32 ulPid )
{
    IMM_MEM_LEAK_INFO_IND_MSG          *pstImmMemLeakInfoInd;

    /*������Ϣ  */
    pstImmMemLeakInfoInd = (IMM_MEM_LEAK_INFO_IND_MSG *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ulPid,
                                               sizeof(IMM_MEM_LEAK_INFO_IND_MSG));

    /* �ڴ�����ʧ�ܣ����� */
    if ( VOS_NULL_PTR == pstImmMemLeakInfoInd )
    {
        return VOS_ERR;
    }

    /*��д��Ϣ����*/
    pstImmMemLeakInfoInd->ulReceiverPid     = ulPid;
    pstImmMemLeakInfoInd->enMsgID           = ID_IMM_MEM_LEAK_INFO_IND;

    /* ������Ϣ */
    PS_SEND_MSG(ulPid, pstImmMemLeakInfoInd);

    return VOS_OK;

}



VOS_VOID IMM_MntnMemOverTimeInfoRpt( VOS_VOID )
{
    VOS_UINT32                              ulTotalCnt;
    VOS_UINT32                              ulLength;
    VOS_UINT32                              ulDataLen;
    PS_OM_EVENT_IND_STRU                   *pstImmOmEventInd;
    IMM_MEM_POOL_STRU                      *pstPoolInfo;
    IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU    *pstImmOmEventBlkMemUsedInfo;
    IMM_BLK_MEM_TRACE_INFO_STRU            *pstBlkMemTraceInfo;
    IMM_BLK_MEM_DEBUG_STRU                 *pstImmMemDebugInfo;
    VOS_UINT32                              ulBlkMemNum;
    IMM_MEM_STRU                           *pMem;
    VOS_UINT32                              ulOffset;
    VOS_UINT8                               ucRptNo = 0;
    VOS_UINT16                              usRptCnt = 0;
    VOS_UINT16                              usNeedRptCnt;
    VOS_UINT32                              ulDrvRsvMemCnt;


    /* ��ȡ�ڴ�� */
    pstPoolInfo = IMM_MEM_GET_POOL(IMM_MEM_POOL_ID_SHARE);

    /* ��ȡ��ʱ���ڴ����� */
    ulTotalCnt  = IMM_MntnGetOverMemBlkCnt(IMM_MEM_POOL_ID_SHARE);

    /* �ϱ��ڴ������Ϣ */
    ulDataLen           = offsetof(IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU, astBlkMemTraceInfo) + ( EVENT_BLK_MEM_USED_INFO_CNT_PER_MSG * sizeof(IMM_BLK_MEM_TRACE_INFO_STRU));

    /*��Ϣ�ܳ���*/
    ulLength            = offsetof(PS_OM_EVENT_IND_STRU,aucData) + ulDataLen;

    /*������Ϣ�ڴ�*/
    pstImmOmEventInd    = (PS_OM_EVENT_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_IMM_RB_FREE, ulLength);

    if ( VOS_NULL_PTR == pstImmOmEventInd )
    {
        IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_ERROR, "IMM_MntnMemOverTimeInfoRpt: MemAlloc Fail!");
        return;
    }

    ulDrvRsvMemCnt = DRV_GET_PREMALLOC_SKB_NUM();

    /* ������Ԥ�����ڴ棬С������Ԥ�����ڴ治���ڴ�й¶ */
    if(ulTotalCnt <= ulDrvRsvMemCnt)
    {
        usNeedRptCnt = 0;
    }
    else if( EVENT_BLK_MEM_USED_INFO_CNT_PER_MSG  < ulTotalCnt )/* ��෢�� EVENT_BLK_MEM_USED_INFO_CNT_PER_MSG �� */
    {
        usNeedRptCnt = EVENT_BLK_MEM_USED_INFO_CNT_PER_MSG ;
    }
    else
    {
        usNeedRptCnt = (VOS_UINT16)(ulTotalCnt - 1);
    }

    for ( ulBlkMemNum = 0; ulBlkMemNum < pstPoolInfo->usImmMemTotalCnt; ++ulBlkMemNum )
    {
        pMem = pstPoolInfo->pstImmMemStStartAddr + ulBlkMemNum;
        pstImmMemDebugInfo = &pMem->stDbgInfo;

        if ( MEM_BLK_STATE_FREE != pstImmMemDebugInfo->enMemStateFlag )
        {

            if ( g_ulOverTimeSliceThreshold > IMM_MntnTimeDiff(pstImmMemDebugInfo->ulAllocTick, g_ulCurrentTimeSlice))
            {
                continue;
            }

            if( usNeedRptCnt > 0 )
            {
                ulOffset    =  offsetof(IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU, astBlkMemTraceInfo)  + ( usRptCnt * sizeof(IMM_BLK_MEM_TRACE_INFO_STRU) );

                pstBlkMemTraceInfo  = (IMM_BLK_MEM_TRACE_INFO_STRU *)(pstImmOmEventInd->aucData + ulOffset );
                pstBlkMemTraceInfo->ulAllocTick         = pstImmMemDebugInfo->ulAllocTick;
                pstBlkMemTraceInfo->usAllocFileId       = pstImmMemDebugInfo->usAllocFileID;
                pstBlkMemTraceInfo->usAllocLineNum      = pstImmMemDebugInfo->usAllocLineNum;

                pstBlkMemTraceInfo->ulTraceTick         = pstImmMemDebugInfo->ulTraceTick;
                pstBlkMemTraceInfo->usTraceFileId       = (pstImmMemDebugInfo->usTraceFileID);
                pstBlkMemTraceInfo->usTraceLineNum      = (pstImmMemDebugInfo->usTraceLineNum);

                if ( NULL !=pMem->pstMemBlk )
                {
                    pstBlkMemTraceInfo->aucMemData[0]       = pMem->pstMemBlk[0];
                    pstBlkMemTraceInfo->aucMemData[1]       = pMem->pstMemBlk[1];
                    pstBlkMemTraceInfo->aucMemData[2]       = pMem->pstMemBlk[2];
                    pstBlkMemTraceInfo->aucMemData[3]       = pMem->pstMemBlk[3];
                }

                ++usRptCnt;
                usNeedRptCnt --;
            }
        }
    }
    /*��д��Ϣ����*/

    ucRptNo = 1;


    pstImmOmEventInd->ulLength      = ulLength - offsetof( PS_OM_EVENT_IND_STRU, usEventId);
    pstImmOmEventInd->usEventId     = IMM_EVENT_BLK_MEM_USED_INFO;
    pstImmOmEventInd->ulModuleId    = UEPS_PID_IMM_RB_FREE;

    pstImmOmEventBlkMemUsedInfo     = (IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU *)pstImmOmEventInd->aucData;
    pstImmOmEventBlkMemUsedInfo->ucPoolId       = IMM_MEM_POOL_ID_SHARE;
    pstImmOmEventBlkMemUsedInfo->enTrigType     = IMM_MEM_TRIG_TYPE_OVERTIME_OCCUPANCY;
    pstImmOmEventBlkMemUsedInfo->ucNo           = ucRptNo;
    pstImmOmEventBlkMemUsedInfo->usRptCnt       = usRptCnt;

    /* USB��Ҫ��ǰ����һ�����ݿ飬���С�ڵ���1,����й¶�ڴ�*/
    if(ulTotalCnt > ulDrvRsvMemCnt)
    {
        pstImmOmEventBlkMemUsedInfo->ulTotalUsedCnt = ulTotalCnt - 1;
        IMM_MntnReportMemLeakMsg(UEPS_PID_IMM_RB_FREE);
    }
    else
    {
        pstImmOmEventBlkMemUsedInfo->ulTotalUsedCnt = 0;
    }


    /*����OM���¼��ϱ��ӿ�*/
    if ( PS_SUCC != OM_AcpuEvent((PS_OM_EVENT_IND_STRU*)pstImmOmEventInd))
    {
        PS_LOG(UEPS_PID_IMM_RB_FREE, 0, IMM_PRINT_ERROR, "IMM_MntnMemOverTimeInfoRpt: OM Send Event Fail! \n");
    }

    /* �ͷ�������ڴ� */
    PS_MEM_FREE(UEPS_PID_IMM_RB_FREE, pstImmOmEventInd);

    return;
}/* IMM_MntnMemOverTimeInfoRpt */



VOS_VOID  IMM_MntnCheckPoolOverTimeOccupancy(VOS_VOID)
{
    IMM_MEM_POOL_STRU              *pstImmMemPool;


    pstImmMemPool = IMM_MEM_GET_POOL(IMM_MEM_POOL_ID_SHARE);

    if ( IMM_TRUE != pstImmMemPool->ucUsedFlag )
    {
        IMM_LOG1(UEPS_PID_IMM_RB_FREE, IMM_PRINT_WARNING, "IMM_MntnCheckPoolOverTimeOccupancy ,Pool %d is not used! \n", IMM_MEM_POOL_ID_SHARE);
        return ;
    }

    /* �ϱ��ڴ泬ʱ�¼� */
    IMM_MntnMemOverTimeInfoRpt();

    return ;
} /* IMM_MntnCheckPoolOverTimeOccupancy */


VOS_VOID  IMM_MntnRptPoolLeakInfo(VOS_VOID)
{
    if ( VOS_TRUE == atomic_read(&g_stCheckLeakFlag) )
    {
        /* ���ó�ʱ��� */
        IMM_MntnCheckPoolOverTimeOccupancy();

        atomic_set(&g_stCheckLeakFlag, VOS_FALSE);
    }
}

#endif



VOS_VOID IMM_MntnMemUsedInfoEventRpt
(
    VOS_UINT8  ucPoolId,
    IMM_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8 enTrigType
)
{

    if ( IMM_TRUE != IMM_MntnCheckReportMemInfoStatus(enTrigType) )
    {
        return;
    }

/*û�д��ڴ���Ա��뿪�أ�����û�д��ڴ����ʹ�ÿ��أ����ϱ�IMM Blk MEM й¶�ܿ��� */
/*lint -e506 -e774 */
#if (FEATURE_ON == FEATURE_TTF_MEM_DEBUG)
    if ( !IMM_BLK_MEM_DEBUG_SWITCH_ON )
#endif
/*lint +e506 +e774 */
    {
        IMM_MntnMemUseBlkCntRpt(ucPoolId, enTrigType);
        return;
    }

#if (FEATURE_ON == FEATURE_TTF_MEM_DEBUG)
    /* �����ڴ���Ա����ʹ�ÿ��أ��ϱ��ڴ������Ϣ */
    IMM_MntnMemUsedBlkTraceInfoRpt(ucPoolId, enTrigType);
    return ;
#endif


}/* IMM_MntnMemUsedInfoEventRpt s*/



VOS_UINT32  IMM_MntnCheckPoolLeak(VOS_UINT8 ucPoolId)
{
    IMM_MEM_POOL_STRU              *pstImmMemPool;
    VOS_UINT32                      ulDrvRsvMemCnt;


    if ( IMM_MEM_POOL_ID_BUTT <= ucPoolId )
    {
        IMM_LOG1(UEPS_PID_IMM_RB_FREE, IMM_PRINT_ERROR, "IMM_MemCheckPoolLeak,Poolid %d is invalid! \n", ucPoolId);
        return VOS_FALSE;
    }

    /* ��ȡ�ڴ�� */
    pstImmMemPool = IMM_MEM_GET_POOL(ucPoolId);

    /* ����ڴ���Ƿ�ʹ�� */
    if ( IMM_TRUE != pstImmMemPool->ucUsedFlag )
    {
        IMM_LOG1(UEPS_PID_IMM_RB_FREE, IMM_PRINT_WARNING, "IMM_MemCheckPoolLeak,Pool %d is not used! \n", ucPoolId);
        return VOS_FALSE;
    }

    /* ��ȡ��������Mem���� */
    ulDrvRsvMemCnt = DRV_GET_PREMALLOC_SKB_NUM();

    /*����ڴ��Ƿ�й¶ */
    if ( ulDrvRsvMemCnt >= pstImmMemPool->usImmMemUsedCnt )
    {
        return VOS_FALSE;
    }

    IMM_LOG1(UEPS_PID_IMM_RB_FREE, IMM_PRINT_WARNING, "IMM_MEM_BLK Is Leak, UsedCnt %d ! \n",
        pstImmMemPool->usImmMemUsedCnt);

    /* ��SDT�ϱ��ڴ�й¶�¼� */
    IMM_MntnMemUsedInfoEventRpt(ucPoolId, IMM_MEM_TRIG_TYPE_LEAK);

    return VOS_TRUE;
} /* IMM_MntnCheckPoolLeak */



VOS_UINT32  IMM_MntnCheckLeak(void)
{
    VOS_UINT8                           ucPoolId;
    VOS_UINT32                          ulRet    = VOS_FALSE;
    VOS_UINT32                          ulFinal  = VOS_FALSE;


    for ( ucPoolId = IMM_MEM_POOL_ID_SHARE; ucPoolId < IMM_MEM_POOL_ID_BUTT; ++ucPoolId )
    {

        ulRet = IMM_MntnCheckPoolLeak(ucPoolId);

        if ( VOS_TRUE == ulRet )
        {
            ulFinal = VOS_TRUE;
        }
     }

    return ulFinal;
} /* IMM_MntnCheckLeak */



VOS_VOID IMM_MntnCheckMemPoolLeak(VOS_UINT8 ucCheckType)
{
    switch(ucCheckType)
    {
        case IMM_MNTN_CHECK_POOL_LEAK_TYPE_USDCNT:
        IMM_MntnCheckLeak();
        break;

#if (FEATURE_ON == FEATURE_IMM_MEM_DEBUG)
        case IMM_MNTN_CHECK_POOL_LEAK_TYPE_OVERTIME:
        IMM_MntnCheckPoolOverTimeOccupancy();
        break;
#endif
        default:
        IMM_LOG1(UEPS_PID_IMM_RB_FREE, IMM_PRINT_WARNING, "IMM_MntnCheckMemPoolLeak Invalid type %d \n", ucCheckType);
        break;
    }

    return;
}/* IMM_MntnCheckMemPoolLeak */



VOS_VOID IMM_MntnAcpuCheckPoolLeak( VOS_VOID )
{
    if ( VOS_NULL == g_ulImmMemRbFreeSem )
    {
        return ;
    }

    atomic_set(&g_stCheckLeakFlag, 1);

    VOS_SmV(g_ulImmMemRbFreeSem);

    return;
}/* IMM_MntnAcpuCheckPoolLeak */



VOS_VOID IMM_MemGetAllocFailCnt(VOS_VOID)
{
    VOS_UINT16                          usLoop;


    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemGetAllocFailCnt Start: \n");

    IMM_LOG1(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemGetAllocFailCnt Threshold: %d \n", g_usImmAllocFailCntThreshold);

#if ( FEATURE_ON == FEATURE_SKB_EXP )
    /* ��ӡ SKB ���ƽ������ʧ�ܴ��� */
    skb_get_fail_cnt();
#endif

    for( usLoop = 0; usLoop < IMM_MEM_POOL_ID_BUTT; ++usLoop )
    {
        IMM_LOG1(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM Mem Pool ID: %d \n", usLoop);
        IMM_LOG3(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM Mem Alloc Fail Cnt: %d * %d + %d \n",
                    *g_apusImmExcThresholdCnt[usLoop], g_usImmAllocFailCntThreshold, *g_apusImmAllocFailCnt[usLoop]);
    }

    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemGetAllocFailCnt End. \n");

    return;
}/* IMM_MemGetAllocFailCnt */



VOS_VOID IMM_MemSetAllocFailThreshold(VOS_UINT16 usThreshold)
{
    g_usImmAllocFailCntThreshold = usThreshold;

    return;
}/* IMM_MemSetAllocFailThreshold */



VOS_VOID IMM_MemReSetAllocFailStatus(VOS_VOID)
{
    VOS_UINT16                          usLoop;

#if ( FEATURE_ON == FEATURE_SKB_EXP )
    skb_reset_fail_cnt();
#endif

    for( usLoop = 0; usLoop < IMM_MEM_POOL_ID_BUTT; ++usLoop )
    {
        *g_apusImmExcThresholdCnt[usLoop]  = 0;
        *g_apusImmAllocFailCnt[usLoop]     = 0;
    }

    return;
}/* IMM_MemReSetAllocFailStatus */



VOS_VOID IMM_MntnInit( VOS_VOID )
{

#if (FEATURE_ON == FEATURE_IMM_MEM_DEBUG)
    IMM_MemRegMntnFuncCallBack(OM_GetSlice, IMM_MntnMemUsedInfoEventRpt);
#else
    IMM_MemRegMntnFuncCallBack(VOS_NULL_PTR, IMM_MntnMemUsedInfoEventRpt);
#endif

    return;
}/* IMM_MntnInit */



VOS_VOID IMM_MemPrintDetail(VOS_UINT8 ucChoice)
{
    g_ucPrintDetail = ucChoice;

    return;
}/* IMM_MemPrintDetail */



VOS_VOID IMM_MemHelp( VOS_VOID )
{
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "********************IMM_MEM�����Ϣ************************\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MntnCheckPoolLeak(ulPoolId):            ���IMM_MEM�ڴ�й¶������ulPoolId:\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "                                            0--SHARE; 1--EXT;\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MntnShowUsedBlkMemInfo(VOS_VOID)        �鿴�ڴ��ʹ����Ϣ(g_ucPrintDetail =1ʱ��ӡ����ϸ��Ϣ)��\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemSetTraceFunc(ucChoice)               ���ú������ٹ켣��ӡ��ucChoice = 0 �رչ켣��ӡ��\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemPrintDetail(ucChoice)                ������ʹ��IMM_MntnShowUsedBlkMemInfoʱ���Ƿ���ʹ����Ϣ��ӡ��\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemGetAllocFailCnt(VOS_VOID)            ��ȡ�ڴ�����ʧ�ܴ�����Ϣ��\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemSetAllocFailThreshold(usThreshold)   �����ڴ�����ʧ���ϱ����ޡ�\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemReSetAllocFailStatus(VOS_VOID)       �����ڴ�����ʧ��ͳ����Ϣ��\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemShowMntnInfo(VOS_VOID)               ��ȡIMM �ڴ��ά�ɲ���Ϣ��\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemClearMntnInfo(VOS_VOID)              ���IMM �ڴ��ά�ɲ���Ϣ��\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemGetFreeMntnEntityAddr(VOS_VOID)      ��ȡ IMM FREE �ڴ��ά�ɲ�ʵ���ַ��\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_MemGetRbMntnEntityAddr(VOS_VOID)        ��ȡ IMM RB �ڴ��ά�ɲ�ʵ���ַ��\n");
    IMM_LOG(UEPS_PID_IMM_RB_FREE, IMM_PRINT_NORMAL, "IMM_RbMemPrintIsrCnt(VOS_VOID)              A���յ�IPF�жϴ�����\n");

    return;
}


#if(IMM_DEBUG_TRACE_FUNC == FEATURE_ON)

VOS_VOID IMM_MemSetTraceFunc(VOS_UINT8 ucChoice)
{
    g_ucImmMemDebugPrint = ucChoice;

    return;
}/* IMM_MemSetTraceFunc */
#endif


/******************************************************************************/
/*******************************V9R1�汾***************************************/
/******************************************************************************/
#else

VOS_VOID IMM_MntnAcpuCheckPoolLeak( VOS_VOID )
{
    return;
}/* IMM_MntnAcpuCheckPoolLeak */


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

