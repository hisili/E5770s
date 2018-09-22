

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CsdCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

    /*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_CSD_CTX_C
    /*lint -e767 */

#if( FEATURE_ON == FEATURE_CSD )


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

CSD_CTX_STRU                            g_stCsdCtx;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_UINT8 CSD_UL_GetAtClientIndex(VOS_VOID)
{
    return g_stCsdCtx.ucAtClientIndex;
}


VOS_VOID CSD_UL_SetAtClientIndex(VOS_UINT8 ucIndex)
{
    g_stCsdCtx.ucAtClientIndex = ucIndex;
}


VOS_UINT32 CSD_UL_InsertQueueTail(
    IMM_ZC_HEAD_STRU                   *pstQueueHead,
    IMM_ZC_STRU                        *pstNode
)
{
    /* Modified by l60609 for AP������Ŀ ��2012-08-31 Begin */
    VOS_UINT32                          ulLockLevel;

    ulLockLevel = 0;

    /* ���м��� */
    VOS_SpinLockIntLock(&g_stCsdCtx.stSpinLock, ulLockLevel);

    /* ���ݲ����β */
    IMM_ZcQueueTail(pstQueueHead, pstNode);

    /* ���н��� */
    VOS_SpinUnlockIntUnlock(&g_stCsdCtx.stSpinLock, ulLockLevel);

    /* Modified by l60609 for AP������Ŀ ��2012-08-31 End */

    CSD_NORMAL_LOG3(ACPU_PID_CSD,
                   "CSD_UL_InsertQueueTail:: Queue len is %d, Pre is 0x%x, Next is 0x%x",
                   pstQueueHead->qlen,
                   pstQueueHead->next,
                   pstQueueHead->prev);

    return VOS_OK;
}


IMM_ZC_STRU  *CSD_UL_GetQueueFrontNode(IMM_ZC_HEAD_STRU *pstQueue)
{
    IMM_ZC_STRU                        *pstNode;
    /* Modified by l60609 for AP������Ŀ ��2012-08-31 Begin */
    VOS_UINT32                          ulLockLevel;

    ulLockLevel = 0;

    /* ���м��� */
    VOS_SpinLockIntLock(&g_stCsdCtx.stSpinLock, ulLockLevel);

    /* ���ض�β�ڵ�ָ�� */
    pstNode        = IMM_ZcDequeueHead(pstQueue);
    /* ���н��� */
    VOS_SpinUnlockIntUnlock(&g_stCsdCtx.stSpinLock, ulLockLevel);

    /* Modified by l60609 for AP������Ŀ ��2012-08-31 End */

    CSD_NORMAL_LOG3(ACPU_PID_CSD,
                   "CSD_UL_GetQueueFrontNode:: Queue len is %d, Pre is 0x%x, Next is 0x%x",
                   pstQueue->qlen,
                   pstQueue->next,
                   pstQueue->prev);

    return pstNode;
}

VOS_UINT32 CSD_UL_FreeQueue(IMM_ZC_HEAD_STRU *pstQueue)
{
    IMM_ZC_STRU                        *pstNode;
    VOS_UINT32                          i;
    VOS_UINT32                          ulQueueCnt;

    ulQueueCnt = IMM_ZcQueueLen(pstQueue);

    for (i = 0; i < ulQueueCnt; i++)
    {
        pstNode  = CSD_UL_GetQueueFrontNode(pstQueue);

        if(VOS_NULL_PTR == pstNode)
        {
            CSD_ERROR_LOG1(ACPU_PID_CSD,
                          "CSD_UL_FreeQueue:: CSD_UL_GetQueueFrontNode fail",
                          pstNode);

            return VOS_ERR;
        }

        /*�ͷ������ڴ�*/
        IMM_ZcFree(pstNode);

    }

    CSD_NORMAL_LOG3(ACPU_PID_CSD,
                   "CSD_UL_FreeQueue:: Queue len is %d, Pre is 0x%x, Next is 0x%x",
                   pstQueue->qlen,
                   pstQueue->next,
                   pstQueue->prev);

    return VOS_OK;
}



IMM_ZC_HEAD_STRU *CSD_UL_GetQueue(VOS_VOID)
{
    return g_stCsdCtx.pstULQueue;
}

VOS_VOID CSD_UL_SetQueue(IMM_ZC_HEAD_STRU *pstULQueue)
{
    g_stCsdCtx.pstULQueue = pstULQueue;
}

VOS_UINT32 CSD_GetLastTxSlice(VOS_VOID)
{
    return g_stCsdCtx.ulLastDICCIsrSlice;
}


VOS_VOID CSD_SetCurrTxSlice(VOS_UINT32 ulCurrSlice)
{
    g_stCsdCtx.ulLastDICCIsrSlice       = ulCurrSlice;
}


VOS_UINT32 *CSD_GetUpLinkDataSem(VOS_VOID)
{
    return &g_stCsdCtx.ulULdataSem;
}


VOS_UINT32 *CSD_GetDownLinkDataSem(VOS_VOID)
{
    return &g_stCsdCtx.ulDLdataSem;
}


AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 CSD_GetCallState(VOS_VOID)
{
    return g_stCsdCtx.enCallState;
}


VOS_VOID CSD_SetCallState(AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 enCallState)
{
    g_stCsdCtx.enCallState                  = enCallState;
}

VOS_UINT32 CSD_InitSem(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                         *pULDataSem;
    VOS_UINT32                         *pDLDataSem;

    pDLDataSem  = CSD_GetDownLinkDataSem();
    pULDataSem  = CSD_GetUpLinkDataSem();

    /* ��ʼ�����ź��� */
    ulRslt      = VOS_SmBCreate("ulDldataSem",
                                CSD_SEMAPHORE_INIT_CNT,
                                VOS_SEMA4_FIFO,
                                pDLDataSem);

    if (VOS_OK != ulRslt)
    {
        VOS_SmDelete(*pDLDataSem);
        CSD_ERROR_LOG(ACPU_PID_CSD,
                      "CSD_InitSem:: VOS_SmBCreate pDLDataSem fail");

        return VOS_ERR;
    }

    /* ��ʼ�����ź��� */
    ulRslt      = VOS_SmBCreate("ulUldataSem",
                                CSD_SEMAPHORE_INIT_CNT,
                                VOS_SEMA4_FIFO,
                                pULDataSem);

    if (VOS_OK != ulRslt)
    {
        VOS_SmDelete(*pULDataSem);
        CSD_ERROR_LOG(ACPU_PID_CSD,
                      "CSD_InitSem:: VOS_SmBCreate pULDataSem fail");

        return VOS_ERR;
    }

    return VOS_OK;
}

VOS_UINT32 CSD_InitCtx(VOS_VOID)
{

    /*�������ͷָ���ʼ��*/
    CSD_UL_SetQueue(VOS_NULL_PTR);

    /*������¼�������DICC�жϵ�ʱ�䣬��ʼΪ0*/
    CSD_SetCurrTxSlice(CSD_DEFAULT_TX_SLICE);

    /*CSDĬ��ͨ��״̬����*/
    CSD_SetCallState(AT_CSD_CALL_STATE_OFF);

    /* Added by l60609 for AP������Ŀ ��2012-09-10 Begin */
    /* ����ʼ�� */
    VOS_SpinLockInit(&g_stCsdCtx.stSpinLock);
    /* Added by l60609 for AP������Ŀ ��2012-09-10 End */

    CSD_UL_SetAtClientIndex(0);

    return VOS_OK;
}

#endif /*FEATURE_CSD*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
