


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AdsUpLink.h"
#include "AdsDebug.h"
#include "IpsMntn.h"

#include "AcpuReset.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#include "AdsFilter.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_UPLINK_C
/*lint +e767*/


#if ((FEATURE_ON == MBB_CTF_WAN_QUEUE) || (FEATURE_ON == MBB_FEATURE_FASTIP_WAN_QUEUE))
extern struct work_struct ads_dl_work;
extern struct work_struct ads_ul_work;
extern struct workqueue_struct *lte_data_process;
#endif /*(FEATURE_ON == MBB_CTF_WAN_QUEUE) || (FEATURE_ON == MBB_FEATURE_FASTIP_WAN_QUEUE)*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_VOID ADS_UL_StartDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
)
{
    /* ������ж��д���, ����������ͳ�ƶ�ʱ�� */
    if (VOS_OK == ADS_UL_IsQueueExistent(ucInstance, ucRabId))
    {
        ADS_StartTimer(ACPU_PID_ADS_UL,
                       ADS_GET_DSFLOW_TMR_ID(ucInstance),
                       TI_ADS_DSFLOW_STATS_LEN);
    }

    return;
}


VOS_VOID ADS_UL_StopDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
)
{
    /* ����������ж����Ѳ����ڣ���ֹͣ����ͳ�ƶ�ʱ�����������ͳ����Ϣ */
    if (VOS_FALSE == ADS_UL_IsAnyQueueExist(ucInstance))
    {
        ADS_StopTimer(ACPU_PID_ADS_UL, ADS_GET_DSFLOW_TMR_ID(ucInstance));
        ADS_InitStatsInfoCtx(ucInstance);
    }

    return;
}


VOS_VOID ADS_UL_StartRptStatsInfoTimer(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
)
{
    /* ������ж��д���, �������ϱ�ͳ����Ϣ��ʱ�� */
    if (VOS_OK == ADS_UL_IsQueueExistent(ucInstance, ucRabId))
    {
        ADS_StartTimer(ACPU_PID_ADS_UL,
                       TI_ADS_RPT_STATS_INFO,
                       TI_ADS_RPT_STATS_LEN);
    }

    return;
}


VOS_VOID ADS_UL_StopRptStatsInfoTimer(VOS_VOID)
{
    VOS_UINT8                           ucInsIndex;

    for (ucInsIndex = 0; ucInsIndex < ADS_INSTANCE_MAX_NUM; ucInsIndex++)
    {
        if (VOS_FALSE == ADS_UL_IsAnyQueueExist(ucInsIndex))
        {
            ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_RPT_STATS_INFO);
        }
    }
}


VOS_UINT32 ADS_UL_IsSendPermit(VOS_VOID)
{
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    return ADS_UL_GET_MODEM_SND_PERMIT_FLAG(ADS_INSTANCE_INDEX_0);
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */
}


VOS_UINT32 ADS_UL_SendPacket(
    IMM_ZC_STRU                        *pstData,
    VOS_UINT8                           ucRabId
)
{
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* �ж��Ƿ�Ϊ�����ݰ� */
    if (VOS_NULL_PTR == pstData)
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendPacket: pstData is null!");
        return VOS_ERR;
    }

    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* �������н�������ͳ�Ƹ��� */
    ADS_DBG_RECV_UL_PKT_NUM(ucInstanceIndex, 1);

    /* ׷�����н������� */
    ADS_MNTN_TraceRcvUlData();

    /* ͳ�������������յ��������ֽ���������������ѯ */
    ADS_RECV_UL_PERIOD_PKT_NUM(ucInstanceIndex, pstData->len);

    /* ��pstData���뵽ucRabId��Ӧ�Ļ�������� */
    if (VOS_OK != ADS_UL_InsertQueue(ucInstanceIndex, pstData, ucRealRabId))
    {
        ADS_DBG_UL_ENQUE_FAIL_NUM(ucInstanceIndex, 1);
        ADS_WARNING_LOG1(ACPU_PID_ADS_UL, "ADS_UL_SendPacket: insert fail, rab id !", ucRealRabId);
        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    return VOS_OK;
}

/* Added by L47619 for V3R3 Share-PDP Project, 2013-6-3, begin */

VOS_UINT32 ADS_UL_SendPacketEx(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType,
    VOS_UINT8                           ucRabId
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* �ж��Ƿ�Ϊ�����ݰ� */
    if (VOS_NULL_PTR == pstData)
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendPacketEx: pstData is null!");
        return VOS_ERR;
    }

    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* �ж��Ƿ��Ѿ�ע������й��˻ص���������ע���������Ҫ���й�����Ϣ����ȡ������ֱ�ӷ��ͱ��� */
    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);
    if (VOS_NULL_PTR != pstDlRabInfo->pRcvDlFilterDataFunc)
    {
        /* ���ù����������ݰ������� */
        ADS_FILTER_ProcUlPacket(pstData, enIpType);
    }

    /* �������н�������ͳ�Ƹ��� */
    ADS_DBG_RECV_UL_PKT_NUM(ucInstanceIndex, 1);

    /* ׷�����н������� */
    ADS_MNTN_TraceRcvUlData();

    /* ͳ�������������յ��������ֽ���������������ѯ */
    ADS_RECV_UL_PERIOD_PKT_NUM(ucInstanceIndex, pstData->len);

    /* ��pstData���뵽ucRabId��Ӧ�Ļ�������� */
    if (VOS_OK != ADS_UL_InsertQueue(ucInstanceIndex, pstData, ucRealRabId))
    {
        ADS_DBG_UL_ENQUE_FAIL_NUM(ucInstanceIndex, 1);
        ADS_WARNING_LOG1(ACPU_PID_ADS_UL, "ADS_UL_SendPacketEx: insert fail, rab id !", ucRealRabId);
        return VOS_ERR;
    }

    return VOS_OK;

}
/* Added by L47619 for V3R3 Share-PDP Project, 2013-6-3, end */

/* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */

IMM_ZC_STRU* ADS_UL_GetInstanceNextQueueNode(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                          *pucRabId
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucCurIndex;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx;
    IMM_ZC_STRU                        *pstNode;

    pstAdsUlCtx = ADS_GetUlCtx(ucInstanceIndex);

    pucCurIndex = &pstAdsUlCtx->ucAdsUlCurIndex;

    pstNode     = VOS_NULL_PTR;

    /* ���ȼ���ʽ */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        /* ��Ϊ�����Ѿ����򣬵�ǰ������Ч�����������ж��ж���Ч
           ����������������Ч���У�������ͷ���� */
        if (VOS_NULL_PTR == ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex))
        {
            i += ADS_RAB_NUM_MAX - (*pucCurIndex + 1);

            *pucCurIndex = 0;

            continue;
        }

        /* ����Ϊ��Ч���е�������ʱ������������ */
        if (0 == ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex)->qlen)
        {
            /* ������һ�����е�����ʱ���������м�¼����� */
            ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex);

            *pucCurIndex = (*pucCurIndex + 1) % ADS_RAB_NUM_MAX;

            continue;
        }

        /* Modified by l60609 for DSDA Phase II, 2012-12-05, Begin */
        /* ��ǰ���в������ͣ� ���������� */
        if (VOS_FALSE == ADS_UL_GET_RAB_SND_PERMIT_FLAG(ucInstanceIndex, ADS_UL_GET_PRIO_QUEUE_INDEX(ucInstanceIndex, *pucCurIndex)))
        {
            *pucCurIndex = (*pucCurIndex + 1) % ADS_RAB_NUM_MAX;

            continue;
        }
        /* Modified by l60609 for DSDA Phase II, 2012-12-05, End */

        /* �������ȼ��ȼ���Ӧ�ļ�Ȩ���������� */
        /* ���ȼ��ߵ��ȷ��� */
        if (ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex) < ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(ucInstanceIndex, *pucCurIndex))
        {
            /* ��ȡ����ͷ��� */
            pstNode = IMM_ZcDequeueHead(ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex));
            /* ��ȡ�ý���RabId */
            *pucRabId = ADS_UL_GET_PRIO_QUEUE_INDEX(ucInstanceIndex, *pucCurIndex);

            /* �����м�¼������ 1*/
            ADS_UL_SET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex, 1);

            /* ����Ѿ������걾���е����ȼ���Ȩ�����������ݣ��������¸����з������� */
            if (ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex) == ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(ucInstanceIndex, *pucCurIndex))
            {
                /* ������һ�����е�����ʱ���������м�¼����� */
                ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex);

                *pucCurIndex = (*pucCurIndex + 1) % ADS_RAB_NUM_MAX;
            }

            break;
        }
    }


    return pstNode;
}


IMM_ZC_STRU* ADS_UL_GetNextQueueNode(
    VOS_UINT8                          *pucRabId,
    VOS_UINT8                          *pucInstanceIndex
)
{
    ADS_CTX_STRU                       *pstAdsCtx = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstNode = VOS_NULL_PTR;
    VOS_UINT8                           i;
    VOS_UINT8                           ucCurInstanceIndex;

    pstAdsCtx = ADS_GetAllCtx();

    ucCurInstanceIndex = pstAdsCtx->ucAdsCurInstanceIndex;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        ucCurInstanceIndex = (ucCurInstanceIndex + i) % ADS_INSTANCE_MAX_NUM;

        pstNode = ADS_UL_GetInstanceNextQueueNode(ucCurInstanceIndex, pucRabId);

        if (VOS_NULL_PTR != pstNode)
        {
            break;
        }
    }

    /* ����ʵ������������BDʱ��modem id */
    *pucInstanceIndex = ucCurInstanceIndex;

    /* ��¼�´δ��ĸ�ʵ����ȥ���� */
    pstAdsCtx->ucAdsCurInstanceIndex = (ucCurInstanceIndex + 1) % ADS_INSTANCE_MAX_NUM;

    return pstNode;
}

/* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

#if(FEATURE_OFF == FEATURE_SKB_EXP)
/* Added by l60609 for AP������Ŀ ��2012-08-30 Begin */

VOS_VOID ADS_UL_SaveIpfUlSrcMem(IMM_ZC_STRU *pstImmZcNode)
{
    IMM_ZC_HEAD_STRU                   *pstUlFreeQue = VOS_NULL_PTR;

    /* ���ٶ����ܵ�Ӱ�죬���ú����ܱ�֤pstIpfUlBdBuff��ulSaveNum����Ч�ԣ����в����в������ */

    pstUlFreeQue = ADS_UL_IPF_SRCMEM_FREE_QUE();

    /* ������� */
    IMM_ZcQueueTail(pstUlFreeQue, pstImmZcNode);

    ADS_DBG_UL_IPF_SAVE_SRCMEM_SUCC_NUM(1);

    return;
}


VOS_VOID ADS_UL_FreeIpfUlConfigSuccSrcMem(VOS_VOID)
{
    IMM_ZC_HEAD_STRU                 *pstUlFreeQue = VOS_NULL_PTR;
    VOS_UINT32                        ulIdleBD;
    VOS_UINT32                        ulBusyBD;
    VOS_UINT32                        ulCanFree;
    VOS_UINT32                        ulQueCnt;
    VOS_UINT32                        ulCnt;
    IMM_ZC_STRU                      *pFreeNode = VOS_NULL_PTR;

    pstUlFreeQue = ADS_UL_IPF_SRCMEM_FREE_QUE();

    ulQueCnt = IMM_ZcQueueLen(pstUlFreeQue);
    if (0 == ulQueCnt)
    {
        return;
    }

    /* get busy bd num */
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    ulIdleBD = BSP_IPF_GetUlDescNum();
#else
    ulIdleBD = BSP_IPF_GetUlBDNum();
#endif
    ulBusyBD = IPF_ULBD_DESC_SIZE - ulIdleBD;
    if (ulQueCnt >= ulBusyBD)
    {
        ulCanFree = ulQueCnt - ulBusyBD;
    }
    else
    {
        ADS_ERROR_LOG2(ACPU_PID_ADS_UL, "ADS_UL_FreeIpfUlSrcMem: Buff Num Less IPF Busy BD Num.",ulQueCnt,ulBusyBD);
        ADS_DBG_UL_IPF_FREE_SRCMEM_ERROR(1);
        return;
    }

    /*free src mem*/
    for (ulCnt = 0; ulCnt < ulCanFree; ulCnt++)
    {
        pFreeNode = IMM_ZcDequeueHead(pstUlFreeQue);

        IMM_ZcFree(pFreeNode);

        ADS_DBG_UL_IPF_FREE_SRCMEM_NUM(1);
    }

    return;
}


VOS_VOID ADS_UL_FreeIpfUlConfigFailSrcMem(VOS_UINT32 ulNeedFreeCnt)
{
    IMM_ZC_HEAD_STRU                 *pstUlFreeQue = VOS_NULL_PTR;
    VOS_UINT32                        ulQueCnt;
    VOS_UINT32                        ulCnt;
    IMM_ZC_STRU                      *pFreeNode = VOS_NULL_PTR;

    pstUlFreeQue = ADS_UL_IPF_SRCMEM_FREE_QUE();

    ulQueCnt = IMM_ZcQueueLen(pstUlFreeQue);
    if (0 == ulQueCnt)
    {
        return;
    }

    if (ulNeedFreeCnt > ulQueCnt)
    {
        ADS_ERROR_LOG2(ACPU_PID_ADS_UL, "ADS_UL_FreeIpfUlConfigFailSrcMem: Queue Num Less Need Free Num.",ulQueCnt,ulNeedFreeCnt);
        ADS_DBG_UL_IPF_FREE_SRCMEM_ERROR(1);
        return;
    }

    /*free src mem*/
    for (ulCnt = 0; ulCnt < ulNeedFreeCnt; ulCnt++)
    {
        pFreeNode = IMM_ZcDequeueTail(pstUlFreeQue);

        IMM_ZcFree(pFreeNode);

        ADS_DBG_UL_IPF_FREE_SRCMEM_NUM(1);
    }

    return;
}


VOS_VOID ADS_UL_ClearIpfUlSrcMem(VOS_VOID)
{
    IMM_ZC_HEAD_STRU                 *pstUlFreeQue = VOS_NULL_PTR;
    VOS_UINT32                        ulQueCnt;
    VOS_UINT32                        ulCnt;
    IMM_ZC_STRU                      *pstFreeNode = VOS_NULL_PTR;
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    VOS_UINT8                         i;
    VOS_UINT32                        ulIpfUlBdNum;

    pstUlFreeQue = ADS_UL_IPF_SRCMEM_FREE_QUE();

    ulQueCnt = IMM_ZcQueueLen(pstUlFreeQue);
    if (0 == ulQueCnt)
    {
        return;
    }

    /* ���е�PDP��ȥ����󣬲���BD�Ѿ�ȫ�����У�����������ȫ�����꣬���������Դ�ڴ���� */
    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        if (VOS_FALSE == ADS_UL_CheckAllQueueEmpty(i))
        {
            return;
        }
    }

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    ulIpfUlBdNum = BSP_IPF_GetUlDescNum();
#else
    ulIpfUlBdNum = BSP_IPF_GetUlBDNum();
#endif

    /* ����BD���63�� */
    if (IPF_ULBD_DESC_SIZE != ulIpfUlBdNum)
    {
        return;
    }
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    /*free src mem*/
    for (ulCnt = 0; ulCnt < ulQueCnt; ulCnt++)
    {
        pstFreeNode = IMM_ZcDequeueHead(pstUlFreeQue);
        IMM_ZcFree(pstFreeNode);

        ADS_DBG_UL_IPF_FREE_SRCMEM_NUM(1);
    }

    return;
}

/* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */

VOS_VOID ADS_UL_SetMaxQueueLength(
    VOS_UINT32                          ulLength,
    VOS_UINT8                           ucInstanceIndex
)
{
    g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.ulUlMaxQueueLength = ulLength;
}
/* Modified by l60609 for DSDA Phase II, 2012-11-24, End */
/* Added by l60609 for AP������Ŀ ��2012-08-30 End */


VOS_VOID ADS_UL_ConfigBD(VOS_UINT32 ulBdNum)
{
    VOS_UINT32                          ulCnt;
    BSP_S32                             lRslt;
    VOS_UINT8                           ucRabId;
    IMM_ZC_STRU                        *pstImmZcNode;
    IPF_CONFIG_ULPARAM_S               *pstIpfConfigUlParam;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT32                          i;

    for (ulCnt = 0; ulCnt < ulBdNum; ulCnt++)
    {
        pstImmZcNode = ADS_UL_GetNextQueueNode(&ucRabId, &ucInstanceIndex);

        if (VOS_NULL_PTR == pstImmZcNode)
        {
            break;
        }

        IPS_MNTN_TraceIpInfo(pstImmZcNode,ID_IPS_TRACE_IP_ADS_UL);

        /* ��ȡ����IPF��BD��Ϣ */
        pstIpfConfigUlParam = ADS_UL_GET_BD_CFG_PARA_PTR(ulCnt);

        pstIpfConfigUlParam->u32Data      = (VOS_UINT32)virt_to_phys((VOS_UINT32 *)pstImmZcNode->data);

        pstIpfConfigUlParam->u16Len       = (VOS_UINT16)pstImmZcNode->len;
        pstIpfConfigUlParam->u16UsrField1 = (VOS_UINT16)ADS_UL_BUILD_BD_USER_FIELD_1(ucInstanceIndex, ucRabId);
        pstIpfConfigUlParam->u32UsrField3 = (VOS_UINT)pstImmZcNode->tstamp.tv64;

        /* ADS �������ݴ�ӡ���� */
        if (VOS_TRUE == g_ulAdsPrintUlDataFlg)
        {
            vos_printf("ADS_UL_ConfigBD: ucInstanceIndex is %d, ucRabId is %d, attribute is %d\r\n", ucInstanceIndex, ucRabId, pstIpfConfigUlParam->u16UsrField1);

            vos_printf("ADS_UL_ConfigBD: Data Len is %d.\r\n", pstImmZcNode->len);

            vos_printf("ADS_UL_ConfigBD: Data Content is :\r\n");

            for (i = 0; i < pstImmZcNode->len; i++)
            {
                if (pstImmZcNode->data[i] > 0xf)
                {
                    vos_printf("%x", pstImmZcNode->data[i]);
                }
                else
                {
                    vos_printf("0%x", pstImmZcNode->data[i]);
                }
            }

            vos_printf("\r\n");
        }

        /* Attribute: �ж�ʹ�ܣ����˼Ӱ��ƣ����������modem0��0��modem1��1 */
        pstIpfConfigUlParam->u16Attribute = (VOS_UINT16)ADS_UL_BUILD_BD_ATTRIBUTE(VOS_FALSE, IPF_MODE_FILTERANDTRANS, ADS_UL_GET_BD_FC_HEAD(ucInstanceIndex));

        /* ��Ҫ������д��DDR��IPF��DDR�ж����� */
        ADS_CACHE_FLUSH(pstImmZcNode->data, pstIpfConfigUlParam->u16Len);

        /* �������õ�BDԴ�ڴ汣�浽Դ�ڴ���� */
        ADS_UL_SaveIpfUlSrcMem(pstImmZcNode);
    }

    /* ʵ�ʴӶ�����ȡ�����ݸ������Ϊ0���쳣 */
    if (0 == ulCnt)
    {
        return;
    }

    /* ���һ��BD�����ж�ʹ�� */
    pstIpfConfigUlParam = ADS_UL_GET_BD_CFG_PARA_PTR(0);
    ADS_UL_SET_BD_ATTR_INT_FLAG(pstIpfConfigUlParam[ulCnt -1].u16Attribute);

    /* ����BD��д��IPF */
    lRslt = BSP_IPF_ConfigUpFilter(ulCnt, ADS_UL_GET_BD_CFG_PARA_PTR(0));
    if (IPF_SUCCESS != lRslt)
    {
        /* дIPFʧ�ܵĴ��� */
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_ConfigBD: IPF CONFIG FAIL!");

        /* IPF����ʧ�ܣ���Ҫ�ͷ�Դ�ڴ� */
        ADS_UL_FreeIpfUlConfigFailSrcMem(ulCnt);

        ADS_DBG_UL_SEND_PKT_FAIL_NUM(ulCnt);

        return;
    }

    ADS_DBG_UL_SEND_BUFF_PKT_NUM(ulCnt);

    /* ׷�����з������� */
    ADS_MNTN_TraceSndUlData();

    return;
}

#else

VOS_VOID ADS_UL_ProcIpfFailConfig(
    VOS_UINT32                          ulBdNum,
    IPF_CONFIG_ULPARAM_S               *pstIpfConfigUlPara
)
{
    VOS_UINT32                          i;
    IMM_MEM_STRU                       *pstImmMem;

    for (i = 0; i < ulBdNum; i++)
    {
        pstImmMem = (IMM_MEM_STRU *)pstIpfConfigUlPara[i].u32UsrField2;

        /* �ͷ�ת�����IMM���� */
        IMM_MemFree(pstImmMem);
    }

    return;
}


VOS_VOID ADS_UL_ConfigBD(VOS_UINT32 ulBdNum)
{
    VOS_UINT32                          ulCnt;
    BSP_S32                             lRslt;
    VOS_UINT8                           ucRabId;
    IMM_ZC_STRU                        *pstImmZcNode;
    IPF_CONFIG_ULPARAM_S               *pstIpfConfigUlParam;
    VOS_UINT8                           ucInstanceIndex;
    IMM_MEM_STRU                       *pstImmMemNode = VOS_NULL_PTR;

    for (ulCnt = 0; ulCnt < ulBdNum; ulCnt++)
    {
        pstImmZcNode = ADS_UL_GetNextQueueNode(&ucRabId, &ucInstanceIndex);

        if (VOS_NULL_PTR == pstImmZcNode)
        {
            break;
        }

        IPS_MNTN_TraceIpInfo(pstImmZcNode,ID_IPS_TRACE_IP_ADS_UL);

        /* ��IMM_Zc�㿽�����ƽڵ�ת����IMM_Mem���ƽڵ� */
        pstImmMemNode = IMM_ZcMapToImmMem(pstImmZcNode);

        if (VOS_NULL_PTR == pstImmMemNode)
        {
            ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_ConfigBD: IMM_ZcMapToImmMem return NULL!");

            break;
        }

        /* ��ȡ����IPF��BD��Ϣ */
        pstIpfConfigUlParam = ADS_UL_GET_BD_CFG_PARA_PTR(ulCnt);

        pstIpfConfigUlParam->u32Data      = (VOS_UINT32)TTF_VIRT_TO_PHY((VOS_UINT32)pstImmZcNode->data);
        /* ����ֻ���˲����ƣ�Դ��ַ��Ŀ�ĵ�ַ��ͬ */
        pstIpfConfigUlParam->u32DesAddr   = pstIpfConfigUlParam->u32Data;
        pstIpfConfigUlParam->u16Len       = (VOS_UINT16)pstImmZcNode->len;
        pstIpfConfigUlParam->u16UsrField1 = (VOS_UINT16)ADS_UL_BUILD_BD_USER_FIELD_1(ucInstanceIndex, ucRabId);
        pstIpfConfigUlParam->u32UsrField2 = (VOS_UINT32)pstImmMemNode;

#if (FEATURE_ON == FEATURE_TTFMEM_CACHE)
        ADS_CACHE_FLUSH(pstImmZcNode->data, pstIpfConfigUlParam->u16Len);
#endif
        /* �ͷ�SK_BUFF ͷ */
        IMM_ZcHeadFree(pstImmZcNode);
    }

    /* ʵ�ʴӶ�����ȡ�����ݸ������Ϊ0���쳣 */
    if (0 == ulCnt)
    {
        return;
    }

    /* ����BD��д��IPF */
    lRslt = BSP_IPF_ConfigUpFilter(ulCnt,
                                   ADS_UL_GET_BD_CFG_PARA_PTR(0),
                                   BSP_TRUE);
    if (IPF_SUCCESS != lRslt)
    {
        /* дIPFʧ�ܵĴ��� */
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_ConfigBD: IPF CONFIG FAIL!");

        ADS_UL_ProcIpfFailConfig(ulCnt, ADS_UL_GET_BD_CFG_PARA_PTR(0));

        ADS_DBG_UL_SEND_PKT_FAIL_NUM(ulCnt);

        return;
    }

    ADS_DBG_UL_SEND_BUFF_PKT_NUM(ulCnt);

    /* ׷�����з������� */
    ADS_MNTN_TraceSndUlData();

    return;
}
#endif


VOS_VOID ADS_UL_ProcLinkData(VOS_VOID)
{
    VOS_UINT32                          ulAllUlQueueDataNum;
    VOS_UINT32                          ulIpfUlBdNum;
    VOS_UINT32                          ulSndBdNum;

    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    /* �жϵ�ǰ�Ƿ������ͣ�����������ͣ�ֱ���˳� */
    if ((VOS_FALSE == ADS_UL_GET_MODEM_SND_PERMIT_FLAG(ADS_INSTANCE_INDEX_0))
     && (VOS_FALSE == ADS_UL_GET_MODEM_SND_PERMIT_FLAG((ADS_INSTANCE_INDEX_0 + 1) % ADS_INSTANCE_MAX_NUM)))
    {
        ADS_NORMAL_LOG(ACPU_PID_ADS_UL, "ADS_UL_ProcLinkData: not permit send!");
        return;
    }
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    /* �������ʱ�е����� */
    for (;;)
    {

        /* ��ȡ���п��Է��͵�BD���� */
#if(FEATURE_OFF == FEATURE_SKB_EXP)
        ulIpfUlBdNum = BSP_IPF_GetUlDescNum();
#else
        ulIpfUlBdNum = BSP_IPF_GetUlBDNum();
#endif
        if (0 == ulIpfUlBdNum)
        {
            ADS_DBG_UL_CFG_IPF_HAVE_NO_BDCD(1);

            /* ���÷��ͽ�����־ */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);

            /* ������ʱ���˳� */
#if ((FEATURE_ON == MBB_CTF_WAN_QUEUE) || (FEATURE_ON == MBB_FEATURE_FASTIP_WAN_QUEUE))
            ADS_UL_StartSendTmr();
#else
            ADS_StartTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_UL_GET_PROTECT_TIMER_LEN());
#endif /*(FEATURE_ON == MBB_CTF_WAN_QUEUE) || (FEATURE_ON == MBB_FEATURE_FASTIP_WAN_QUEUE)*/
            break;
        }


        /* �������ڷ��ͱ�־ */
        ADS_UL_SET_SENDING_FLAG(VOS_TRUE);

        /* ��ȡ��ǰ���ж����е����ݰ����� */
        ulAllUlQueueDataNum = ADS_UL_GetAllQueueDataNum();

        /* ���㵱ǰ�ɷ��͵�BD��Ŀ */
        ulSndBdNum = PS_MIN(ulIpfUlBdNum, ulAllUlQueueDataNum);

        /* Added by l60609 for AP������Ŀ ��2012-08-31 Begin */
#if(FEATURE_OFF == FEATURE_SKB_EXP)
        ADS_UL_FreeIpfUlConfigSuccSrcMem();
#endif
        /* Added by l60609 for AP������Ŀ ��2012-08-31 End */

        /* ����BD��д��IPF */
        ADS_UL_ConfigBD(ulSndBdNum);

        /* ��ȡ��ǰ���ж����е����ݰ����� */
        ulAllUlQueueDataNum = ADS_UL_GetAllQueueDataNum();

        /* ��ǰ������û�����ݣ��˳����ȴ��´ζ����ɿձ�Ϊ�ǿմ��� */
        if (0 == ulAllUlQueueDataNum)
        {
            /* ���÷��ͽ�����־ */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);

            break;
        }
        /* ��ǰ�����������ݣ�������Ҫ�����ܰ� */
        else if (ulAllUlQueueDataNum < ADS_UL_SEND_DATA_NUM_THREDHOLD)
        {
#if ((FEATURE_ON == MBB_CTF_WAN_QUEUE) || (FEATURE_ON == MBB_FEATURE_FASTIP_WAN_QUEUE))
            ADS_UL_StartSendTmr();
#else
            ADS_StartTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_UL_GET_PROTECT_TIMER_LEN());
#endif /*(FEATURE_ON == MBB_CTF_WAN_QUEUE) || (FEATURE_ON == MBB_FEATURE_FASTIP_WAN_QUEUE)*/
            /* ���÷��ͽ�����־ */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);

            break;
        }
        else
        {
            continue;
        }
    }

    return;
}


VOS_VOID ADS_UL_SendCdsStopSendDataRsp(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulResult;
    CDS_ADS_STOP_SENDDATA_RSP_STRU     *pstStopSendDataRsp;

    /* ������Ϣ */
    pstStopSendDataRsp = (CDS_ADS_STOP_SENDDATA_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ACPU_PID_ADS_UL,
                                             sizeof(CDS_ADS_STOP_SENDDATA_RSP_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if( VOS_NULL_PTR == pstStopSendDataRsp )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendCdsStopSendDataRsp: pstStopSendDataRsp is null!");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstStopSendDataRsp + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(CDS_ADS_STOP_SENDDATA_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    /*��д��Ϣ����*/
    pstStopSendDataRsp->ulReceiverPid = UEPS_PID_CDS;
    pstStopSendDataRsp->enMsgId       = ID_CDS_ADS_STOP_SENDDATA_RSP;
    /* Modified by l60609 for DSDA Phase II, 2012-12-14, Begin */
    pstStopSendDataRsp->enModemId     = enModemId;
    pstStopSendDataRsp->ucRabId       = ucRabId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-14, End */

    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_UL, pstStopSendDataRsp);

    if(VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendCdsStopSendDataRsp: Send Msg Fail!");
    }

    return;
}


VOS_VOID ADS_UL_SendCdsStartSendDataRsp(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulResult;
    CDS_ADS_START_SENDDATA_RSP_STRU    *pstStartSendDataRsp;

    /*������Ϣ  */
    pstStartSendDataRsp = (CDS_ADS_START_SENDDATA_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ACPU_PID_ADS_UL,
                                             sizeof(CDS_ADS_START_SENDDATA_RSP_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if( VOS_NULL_PTR == pstStartSendDataRsp )
    {
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstStartSendDataRsp + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(CDS_ADS_START_SENDDATA_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    /*��д��Ϣ����*/
    pstStartSendDataRsp->ulReceiverPid = UEPS_PID_CDS;
    pstStartSendDataRsp->enMsgId       = ID_CDS_ADS_START_SENDDATA_RSP;
    /* Modified by l60609 for DSDA Phase II, 2012-12-14, Begin */
    pstStartSendDataRsp->enModemId     = enModemId;
    pstStartSendDataRsp->ucRabId       = ucRabId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-14, End */

    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_UL, pstStartSendDataRsp);

    if(VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendCdsStartSendDataRsp: Send Msg Fail!");
    }

    return;
}


VOS_VOID ADS_UL_SendCdsClearDataRsp(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT32                          ulResult;
    CDS_ADS_CLEAR_DATA_RSP_STRU        *pstClearDataRsp;

    /*������Ϣ  */
    pstClearDataRsp = (CDS_ADS_CLEAR_DATA_RSP_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ACPU_PID_ADS_UL,
                                             sizeof(CDS_ADS_CLEAR_DATA_RSP_STRU));

    /* �ڴ�����ʧ�ܣ����� */
    if( VOS_NULL_PTR == pstClearDataRsp )
    {
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstClearDataRsp + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(CDS_ADS_CLEAR_DATA_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣ���� */
    pstClearDataRsp->ulReceiverPid = UEPS_PID_CDS;
    pstClearDataRsp->enMsgId       = ID_CDS_ADS_CLEAR_DATA_RSP;
    /* Modified by l60609 for DSDA Phase II, 2012-12-14, Begin */
    pstClearDataRsp->enModemId     = enModemId;
    /* Modified by l60609 for DSDA Phase II, 2012-12-14, End */
    pstClearDataRsp->ucRabId       = ucRabId;

    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_UL, pstClearDataRsp);

    if(VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendCdsClearDataRsp: Send Msg Fail!");
    }

    return;
}

/* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */

VOS_UINT32 ADS_UL_ProcPdpStatusInd(
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL) /*add parameter Cid when BIP*/
    VOS_UINT8                                           ucCid,
#endif
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    ADS_PDP_STATUS_ENUM_UINT8           enPdpStatus,
    ADS_QCI_TYPE_ENUM_UINT8             enQciType,
    ADS_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT8                           ucInstanceIndex;
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;
    ADS_QCI_TYPE_ENUM_UINT8             enPrio;

    enPktType                           = ADS_CDS_IPF_PKT_TYPE_IP;

    ucInstanceIndex                     = (VOS_UINT8)enModemId;

    enPrio                              = enQciType;

    /* RabId�Ϸ��Լ�� */
    if (VOS_OK != ADS_IsValidRabId(ucRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_UL, "ADS_UL_ProcPdpStatusInd: ucRabId is ", ucRabId);
        return VOS_ERR;
    }

    /* ������������ȼ������޸�����PDP��QCIΪ��ͬ���ȼ������������㷨��������ʹ�ȼ����PDP���ȴ��� */
    if (VOS_FALSE == g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.stQueuePriNv.ulStatus)
    {
        enPrio = ADS_QCI_TYPE_QCI9_NONGBR;
    }

    if (ADS_PDP_PPP == enPdpType)
    {
        enPktType = ADS_CDS_IPF_PKT_TYPE_PPP;
    }

    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    /* ����PDP״̬�ֱ���д��� */
    switch(enPdpStatus)
    {
        /* PDP���� */
        case ADS_PDP_STATUS_ACT:
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL)
            g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.astAdsUlQueue[ucRabId].ulIdMark |= (1 << ucCid);
#endif

            /* ����������� */
            ADS_UL_CreateQueue(ucInstanceIndex, ucRabId, enPrio, enPktType);

            /* ��������ͳ�� */
            ADS_UL_StartDsFlowStats(ucInstanceIndex, ucRabId);

            /* �����ϱ�ͳ����Ϣ��ʱ�� */
            ADS_UL_StartRptStatsInfoTimer(ucInstanceIndex, ucRabId);

            break;

        /* PDP�޸� */
        case ADS_PDP_STATUS_MODIFY:

            /* ���޸ĵĶ�����Ϣ���µ����ж��й����� */
            ADS_UL_UpdateQueueInPdpModified(ucInstanceIndex, enPrio, ucRabId);

            break;

        /* PDPȥ���� */
        case ADS_PDP_STATUS_DEACT:

            /* ���ٻ������ */
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL)
            g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.astAdsUlQueue[ucRabId].ulIdMark 
                &= (~(1 << ucCid));
            if ( 0 != g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.astAdsUlQueue[ucRabId].ulIdMark )
            {
                break;
            }
#endif
            ADS_UL_DestroyQueue(ucInstanceIndex, ucRabId);

            /* Added by l60609 for AP������Ŀ ��2012-08-31 Begin */
#if(FEATURE_OFF == FEATURE_SKB_EXP)
            /* �����е�PDP��ȥ��������Դ�ڴ���� */
            ADS_UL_ClearIpfUlSrcMem();
#endif
            /* Added by l60609 for AP������Ŀ ��2012-08-31 End */

            /* ֹͣ����ͳ�� */
            ADS_UL_StopDsFlowStats(ucInstanceIndex, ucRabId);

            /* �ر��ϱ�ͳ����Ϣ��ʱ�� */
            ADS_UL_StopRptStatsInfoTimer();

            break;

        default:
            break;
    }
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvTafPdpStatusInd(MsgBlock *pMsg)
{
    ADS_PDP_STATUS_IND_STRU            *pstPdpStatusInd;
    VOS_UINT32                          ulRslt;

    pstPdpStatusInd = (ADS_PDP_STATUS_IND_STRU *)pMsg;

    ulRslt = ADS_UL_ProcPdpStatusInd(
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL) 
                                    pstPdpStatusInd->ucCid,
#endif
                                     pstPdpStatusInd->enModemId,
                                     pstPdpStatusInd->ucRabId,
                                     pstPdpStatusInd->enPdpStatus,
                                     pstPdpStatusInd->enQciType,
                                     pstPdpStatusInd->enPdpType);

    return ulRslt;
}
/* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */


VOS_UINT32 ADS_UL_RcvCdsStopSendDataInd(MsgBlock *pMsg)
{
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRabId;
    CDS_ADS_STOP_SENDDATA_IND_STRU     *pstStopSendDataIndMsg;

    pstStopSendDataIndMsg = (CDS_ADS_STOP_SENDDATA_IND_STRU *)(pMsg);

    ucInstanceIndex = (VOS_UINT8)pstStopSendDataIndMsg->enModemId;
    ucRabId = pstStopSendDataIndMsg->ucRabId;

    /* ����Ӧ�Ƿ������͵ı�־��ΪVOS_FALSE */
    ADS_UL_SET_RAB_SND_PERMIT_FLAG(ucInstanceIndex, ucRabId, VOS_FALSE);

    /* �жϸ�modem������RAB���������� */
    if (VOS_FALSE == ADS_UL_GetSpecInstanceSndPermitFlg(ucInstanceIndex))
    {
        ADS_UL_SET_MODEM_SND_PERMIT_FLAG(ucInstanceIndex, VOS_FALSE);
    }

    /* ���г��ض��������ͣ�ֹͣADS_UL_SEND_TIMER��ʱ�� */
    if (VOS_TRUE == ADS_UL_IsAllRabNotSndPermitFlg())
    {
        ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND);
    }

    /* �ظ�ID_CDS_ADS_STOP_SENDDATA_RSP��Ϣ */
    ADS_UL_SendCdsStopSendDataRsp(pstStopSendDataIndMsg->enModemId, pstStopSendDataIndMsg->ucRabId);
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvCdsStartSendDataInd(MsgBlock *pMsg)
{
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRabId;
    CDS_ADS_START_SENDDATA_IND_STRU    *pstStartSendDataIndMsg;

    pstStartSendDataIndMsg = (CDS_ADS_START_SENDDATA_IND_STRU *)(pMsg);

    ucInstanceIndex = (VOS_UINT8)pstStartSendDataIndMsg->enModemId;
    ucRabId = (VOS_UINT8)pstStartSendDataIndMsg->ucRabId;

    /* ����Ӧ�Ƿ������͵ı�־��ΪVOS_TRUE */
    ADS_UL_SET_RAB_SND_PERMIT_FLAG(ucInstanceIndex, ucRabId, VOS_TRUE);

    ADS_UL_SET_MODEM_SND_PERMIT_FLAG(ucInstanceIndex, VOS_TRUE);

    /* �ظ�ID_CDS_ADS_START_SENDDATA_RSP��Ϣ */
    ADS_UL_SendCdsStartSendDataRsp(pstStartSendDataIndMsg->enModemId, pstStartSendDataIndMsg->ucRabId);
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    /* �������л��洦���¼� */
    ADS_UL_SndEvent(ADS_UL_EVENT_DATA_PROC);

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvCdsClearDataInd(MsgBlock *pMsg)
{
    VOS_UINT8                           ucRabId;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx;
    CDS_ADS_CLEAR_DATA_IND_STRU        *pstClearData;
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    VOS_UINT8                           ucInstanceIndex;

    pstClearData = (CDS_ADS_CLEAR_DATA_IND_STRU *)pMsg;

    /* AT�ӿ��޸ĺ󣬻�ȡ��ֵ */
    ucInstanceIndex = (VOS_UINT8)pstClearData->enModemId;

    pstAdsUlCtx = ADS_GetUlCtx(ucInstanceIndex);

    ucRabId = pstClearData->ucRabId;

    if (CDS_ADS_ALL_RABID == pstClearData->ucRabId)
    {
        for (ucRabId = ADS_RAB_ID_MIN; ucRabId <= ADS_RAB_ID_MAX; ucRabId++)
        {
            if (VOS_OK == ADS_UL_IsQueueExistent(ucInstanceIndex, ucRabId))
            {
                /* ���ٶ����е����� */
                /* Modified by l60609 for AP������Ŀ ��2012-09-10 Begin */
                ADS_UL_ClearQueue(ucRabId,
                                  pstAdsUlCtx->astAdsUlQueue[ucRabId].pstAdsUlLink);
                /* Modified by l60609 for AP������Ŀ ��2012-09-10 End */
            }
        }
    }
    else
    {
        /* �ж�RabId�Ƿ�Ϊ��Чֵ */
        if (VOS_OK == ADS_IsValidRabId(pstClearData->ucRabId))
        {
            /* �����ڣ������в����� */
            if (VOS_OK == ADS_UL_IsQueueExistent(ucInstanceIndex, pstClearData->ucRabId))
            {
                /* ���ٶ����е����� */
                /* Modified by l60609 for AP������Ŀ ��2012-09-10 Begin */
                ADS_UL_ClearQueue(ucRabId,
                                  pstAdsUlCtx->astAdsUlQueue[ucRabId].pstAdsUlLink);
                /* Modified by l60609 for AP������Ŀ ��2012-09-10 End */
            }
            else
            {
                ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_RcvCdsClearDataInd:Queue is not exist");
            }
        }
        else
        {
            ADS_WARNING_LOG1(ACPU_PID_ADS_UL, "ADS_UL_RcvCdsClearDataInd: Invalid RabId is", pstClearData->ucRabId);
        }
    }

    /* �ظ�ID_CDS_ADS_CLEAR_DATA_RSP��Ϣ */
    ADS_UL_SendCdsClearDataRsp(pstClearData->enModemId, pstClearData->ucRabId);
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvCdsIpPacketMsg(MsgBlock *pMsg)
{
    VOS_UINT32                          ulResult;
    ADS_NDIS_DATA_IND_STRU             *pstAdsNdisDataInd;
    IMM_ZC_STRU                        *pstZcData;
    CDS_ADS_DATA_IND_STRU              *pstDataInd;
    VOS_CHAR                           *pstZcPutData;

    pstDataInd = (CDS_ADS_DATA_IND_STRU *)pMsg;

    /* ������Ϣ  */
    pstAdsNdisDataInd = (ADS_NDIS_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ACPU_PID_ADS_UL,
                                             sizeof(ADS_NDIS_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstAdsNdisDataInd)
    {
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstAdsNdisDataInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_NDIS_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣ���� */
    pstAdsNdisDataInd->ulReceiverPid  = PS_PID_APP_NDIS;
    pstAdsNdisDataInd->enMsgId        = ID_ADS_NDIS_DATA_IND;
    pstAdsNdisDataInd->enModemId      = pstDataInd->enModemId;
    pstAdsNdisDataInd->ucRabId        = pstDataInd->ucRabId;
    pstAdsNdisDataInd->enIpPacketType = pstDataInd->enIpPacketType;

    pstZcData = (IMM_ZC_STRU *)IMM_ZcStaticAlloc((VOS_UINT32)pstDataInd->usLen);

    if (VOS_NULL_PTR == pstZcData)
    {
        PS_MEM_FREE(ACPU_PID_ADS_UL, pstAdsNdisDataInd);

        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase II, 2012-12-21, Begin */

    /*�˲��費���٣�����ƫ������βָ��*/
    /* Modified by l60609 for AP������Ŀ ��2012-08-30 Begin */
    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstZcData, pstDataInd->usLen);
    /* Modified by l60609 for AP������Ŀ ��2012-08-30 End */

    PS_MEM_CPY(pstZcPutData, pstDataInd->aucData, pstDataInd->usLen);
    /* Modified by l60609 for DSDA Phase II, 2012-12-21, End */

    pstAdsNdisDataInd->pstSkBuff = pstZcData;

    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_UL, pstAdsNdisDataInd);

    if(VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_RcvCdsIpPacketMsg: Send Msg Fail!");

        IMM_ZcFree(pstZcData);

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucInsIndex;
    VOS_UINT8                           ucRabIndex;
    VOS_UINT8                           ucTiIndex;
    ADS_CTX_STRU                       *pstAdsCtx = VOS_NULL_PTR;

    pstAdsCtx = ADS_GetAllCtx();

    /* ����������л������ */
    for (ucInsIndex = 0; ucInsIndex < ADS_INSTANCE_MAX_NUM; ucInsIndex++)
    {
        for (ucRabIndex = 0; ucRabIndex < ADS_RAB_ID_MAX + 1; ucRabIndex++)
        {
            ADS_UL_DestroyQueue(ucInsIndex, ucRabIndex);
        }
    }

#if (FEATURE_OFF == FEATURE_SKB_EXP)
    /* ���Դ�ڴ���� */
    ADS_UL_ClearIpfUlSrcMem();
#endif

    /* ֹͣ���������Ķ�ʱ�� */
    for (ucTiIndex = 0; ucTiIndex < ADS_MAX_TIMER_NUM; ucTiIndex++)
    {
        ADS_StopTimer(ACPU_PID_ADS_UL, ucTiIndex);
    }

    /* ��ʼ��ÿ��ʵ���������� */
    ADS_ResetSpecCtx();

    /* ����IPF��ص������� */
    ADS_ResetIpfCtx();

    /* ���õ�ǰʵ������ֵ */
    pstAdsCtx->ucAdsCurInstanceIndex = ADS_INSTANCE_INDEX_0;

    /* ����ADS Filter���������� */
    ADS_FILTER_Reset();

    ADS_ResetDebugInfo();

    /* �ͷ��ź�����ʹ�õ���API����������� */
    VOS_SmV(ADS_GetULResetSem());

    return VOS_OK;
}


VOS_VOID ADS_UL_RcvTiDsFlowStatsExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          ulTaBytes;
    VOS_UINT32                          ulRate;
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    VOS_UINT8                           ucInstance;

    ucInstance = ADS_INSTANCE_INDEX_0;

    /* ����ulTimerName��ȡʵ��index */
    if (TI_ADS_DSFLOW_STATS_0 != ulTimerName)
    {
        ucInstance = (ucInstance + 1) % ADS_INSTANCE_MAX_NUM;
    }

    /* ���û�����ж��д���, ����ͳ������ */
    if (VOS_FALSE == ADS_UL_IsAnyQueueExist(ucInstance))
    {
        ADS_NORMAL_LOG(ACPU_PID_ADS_DL, "ADS_UL_RcvTiDsFlowStatsExpired: no queue is exist!");
        return;
    }

    /* ��ȡ2����������ݸ��� */
    ulTaBytes = ADS_GET_DL_PERIOD_PKT_NUM(ucInstance);

    /* ÿ2���Ӽ���һ��,��λΪ:byte/s */
    ulRate = ulTaBytes>>1;
    ADS_SET_CURRENT_DL_RATE(ucInstance, ulRate);

    /* ��ȡ2����������� */
    ulTaBytes = ADS_GET_UL_PERIOD_PKT_NUM(ucInstance);

    /* ÿ2���Ӽ���һ��,��λΪ:byte/s */
    ulRate = ulTaBytes>>1;
    ADS_SET_CURRENT_UL_RATE(ucInstance, ulRate);

    /* ÿ������ͳ�����ڽ�������Ҫ������ͳ��Byte����� */
    ADS_CLEAR_UL_PERIOD_PKT_NUM(ucInstance);
    ADS_CLEAR_DL_PERIOD_PKT_NUM(ucInstance);
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    /* ��������ͳ�ƶ�ʱ��*/
    ADS_StartTimer(ACPU_PID_ADS_UL,
                   ulTimerName,
                   TI_ADS_DSFLOW_STATS_LEN);

    return ;
}


VOS_VOID ADS_UL_RcvTiRptStatsInfoExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
)
{
    ADS_LOG_RPT_STATS_INFO_STRU        *pstMsg = VOS_NULL_PTR;

    /* ����¼��ͳ����Ϣͨ��SDT��Ϣ������ */
    pstMsg = (ADS_LOG_RPT_STATS_INFO_STRU*)PS_MEM_ALLOC(ACPU_PID_ADS_UL, sizeof(ADS_LOG_RPT_STATS_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_RcvTiRptStatsInfoExpired: ERROR:Alloc Mem Fail");
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(ADS_LOG_RPT_STATS_INFO_STRU));

    pstMsg->stLogHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stLogHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stLogHeader.ulSenderPid     = ACPU_PID_ADS_UL;
    pstMsg->stLogHeader.ulReceiverPid   = ACPU_PID_ADS_UL;
    pstMsg->stLogHeader.ulLength        = sizeof(ADS_LOG_RPT_STATS_INFO_STRU) - VOS_MSG_HEAD_LENGTH;;
    pstMsg->stLogHeader.enMsgId         = ID_ADS_LOG_RPT_STATS_INFO;

    PS_MEM_CPY(&pstMsg->stAdsStats, &g_stAdsStats, sizeof(g_stAdsStats));

    OM_AcpuTraceMsgHook(pstMsg);

    PS_MEM_FREE(ACPU_PID_ADS_UL, pstMsg);

    /* ���������ϱ�ͳ����Ϣ��ʱ�� */
    ADS_StartTimer(ACPU_PID_ADS_UL, ulTimerName, TI_ADS_RPT_STATS_LEN);

    return ;
}



VOS_UINT32 ADS_UL_RcvTafMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;


    switch(pstMsg->ulMsgName)
    {
        case ID_APS_ADS_PDP_STATUS_IND:
            ADS_UL_RcvTafPdpStatusInd(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvCdsMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_CDS_ADS_STOP_SENDDATA_IND:
            ADS_UL_RcvCdsStopSendDataInd(pMsg);
            break;

        case ID_CDS_ADS_START_SENDDATA_IND:
            ADS_UL_RcvCdsStartSendDataInd(pMsg);
            break;

        case ID_CDS_ADS_CLEAR_DATA_IND:
            ADS_UL_RcvCdsClearDataInd(pMsg);
            break;

        case ID_CDS_ADS_IP_PACKET_IND:
            ADS_UL_RcvCdsIpPacketMsg(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvTimerMsg(MsgBlock *pMsg)
{
    REL_TIMER_MSG                      *pstTimerMsg;

    pstTimerMsg = (REL_TIMER_MSG *)pMsg;

    /* ֹͣ�ö�ʱ�� */
    ADS_StopTimer(ACPU_PID_ADS_UL, pstTimerMsg->ulName);

    switch (pstTimerMsg->ulName)
    {
        /* ����ADS_UL_SEND_TIMER��ʱ����ʱ */
        case TI_ADS_UL_SEND:
            /* ������������ */
            

           ADS_UL_ProcLinkData();

            break;

        case TI_ADS_DSFLOW_STATS_0:
        case TI_ADS_DSFLOW_STATS_1:
            ADS_UL_RcvTiDsFlowStatsExpired(pstTimerMsg->ulName, pstTimerMsg->ulPara);
            break;

        case TI_ADS_RPT_STATS_INFO:
            ADS_UL_RcvTiRptStatsInfoExpired(pstTimerMsg->ulName, pstTimerMsg->ulPara);
            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvAdsUlMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    /* Modified by l60609 for L-C��������Ŀ, 2014-01-07, Begin */
    switch(pstMsg->ulMsgName)
    {
        case ID_ADS_CCPU_RESET_START_IND:
            ADS_UL_RcvCcpuResetStartInd(pMsg);
            break;

        case ID_ADS_CCPU_RESET_END_IND:

            /* do nothing */
            ADS_NORMAL_LOG(ACPU_PID_ADS_UL, "ADS_DL_RcvAdsDlMsg: rcv ID_CCPU_ADS_UL_RESET_END_IND");
            break;

        default:
            ADS_NORMAL_LOG1(ACPU_PID_ADS_UL, "ADS_UL_RcvAdsUlMsg: rcv error msg id %d\r\n", pstMsg->ulMsgName);
            break;
    }
    /* Modified by l60609 for L-C��������Ŀ, 2014-01-07, End */

    return VOS_OK;
}


VOS_VOID ADS_UL_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* ��Ϣ�ķַ����� */
    switch ( pMsg->ulSenderPid )
    {
        /* ����Timer����Ϣ */
        case VOS_PID_TIMER:
            ADS_UL_RcvTimerMsg(pMsg);
            return;

        /* ����TAF����Ϣ */
        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
            ADS_UL_RcvTafMsg(pMsg);
            return;


        /* ����CDS����Ϣ */
        case UEPS_PID_CDS:
            ADS_UL_RcvCdsMsg(pMsg);
            return;

        /* ����ADS UL����Ϣ */
        case ACPU_PID_ADS_UL:
            ADS_UL_RcvAdsUlMsg(pMsg);
            return;

        default:
            return;
    }
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
