


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AdsDownLink.h"
#include "AdsDebug.h"
#include "DrvInterface.h"
#include "IpsMntn.h"

#include "AcpuReset.h"

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
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_DOWNLINK_C
/*lint +e767*/


#define    bcm43236    (4)    
/*wifiоƬ�꣬��mbb_config.h��û�ж��ض���оƬ����и�ֵ��
�ᵼ�������ж��޷���ȷ���У�Ŀǰ����ֻ��bcm43236��Ҫ�����ó������Ƚϣ����Խ�bcm43236�ĺ궨
��һ�£�������뱣�ָ�wlan_ifģ��������ĺ�һ�¡�*/

#if (bcm43236 == MBB_WIFI_CHIP1) || (bcm43236 == MBB_WIFI_CHIP2) 
#define    ADS_DL_AD_DATA_HEADROOM_PAD  256
#else 
#define    ADS_DL_AD_DATA_HEADROOM_PAD  0
#endif

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_INT32 ADS_DL_IpfIntCB(VOS_VOID)
{
    /* ��������IPF�ж�ͳ�Ƽ��� */
    ADS_DBG_DL_RECV_IPF_BREAK_NUM(1);

    /* ��������RD�����¼� */
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);

    return VOS_OK;
}


VOS_VOID ADS_DL_RcvTiProtectExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    /* ͳ�ƶ�ʱ����ʱ���� */
    ADS_DBG_DL_RD_TI_PROTECT_EXPIRED_NUM(1);

    /* ֹͣ��ʱ�� */
    ADS_StopTimer(ACPU_PID_ADS_DL, TI_ADS_DL_PROTECT);

    if (BSP_IPF_GetDlRdNum() > 0)
    {
        ADS_DBG_DL_RD_PROTECT_EVENT_NUM(1);

        ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);
    }

    /* ��������������ʱ�� */
    ADS_DL_StartProtectTimer();

    return;
}

#if (FEATURE_OFF == FEATURE_SKB_EXP)

VOS_INT32 ADS_DL_IpfAdqEmptyCB(IPF_ADQ_EMPTY_E eAdqEmpty)
{
    /* ��������IPF ADQ���ж�ͳ�Ƽ��� */
    ADS_DBG_DL_RECV_ADQ_EMPTY_BREAK_NUM(1);

    ADS_DBG_DL_GET_ADQ_EMPTY_NUM(eAdqEmpty, 1);

    /* ��������ADQ���жϴ����¼� */
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);

    return VOS_OK;
}


VOS_VOID ADS_DL_ProcIpfAdqEmtpyEvent(VOS_VOID)
{
    VOS_INT32                           lRslt;
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    VOS_UINT                            ulActAd0Num;
    VOS_UINT                            ulActAd1Num;

    ulIpfAd0Num = 0;
    ulIpfAd1Num = 0;
    ulActAd0Num = 0;
    ulActAd1Num = 0;

    /* ��ȡ����ADQ�Ŀ��е�AD���� */
    lRslt = BSP_IPF_GetDlAdNum(&ulIpfAd0Num, &ulIpfAd1Num);

    if (IPF_SUCCESS != lRslt)
    {
        ADS_DBG_DL_GET_AD_FAIL_NUM(1);
        return;
    }

    /* �������ô��ڴ��ADQ1 */
    if (0 != ulIpfAd1Num)
    {
        ADS_DL_ConfigAdq(IPF_AD_1, ulIpfAd1Num, &ulActAd1Num);
    }

    /* ������С�ڴ��ADQ0 */
    if (0 != ulIpfAd0Num)
    {
        ADS_DL_ConfigAdq(IPF_AD_0, ulIpfAd0Num, &ulActAd0Num);
    }

    /* AD0Ϊ�ջ���AD1Ϊ����Ҫ����������ʱ�� */
    if (((0 == ulActAd0Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd0Num))
     || ((0 == ulActAd1Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd1Num)))
    {
        /* �������ADQ�κ�һ���������벻���ڴ棬����ʱ�� */
        ADS_DL_StartAdqEmptyTimer();
    }

    return;
}



VOS_VOID ADS_DL_RcvTiAdqEmptyExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    ADS_StopTimer(ACPU_PID_ADS_DL, TI_ADS_DL_ADQ_EMPTY);
    /* ��������ADQ���жϴ����¼� */
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);
}


VOS_VOID ADS_DL_ConfigAdq(
    IPF_AD_TYPE_E                       enAdType,
    VOS_UINT                            ulIpfAdNum,
    VOS_UINT                           *pulActAdNum
)
{
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstZcData = VOS_NULL_PTR;
    VOS_CHAR                           *pstZcPullData = VOS_NULL_PTR;
    VOS_UINT8                          *pstZcHead = VOS_NULL_PTR;
    VOS_UINT32                          ulActAdNum;
    VOS_UINT16                          usLen;
    IPF_AD_DESC_S                      *pstIpfAdDesc = VOS_NULL_PTR;
    VOS_INT32                           lRslt;

    ulActAdNum = 0;

    if (IPF_AD_0 == enAdType)
    {
        usLen = ADS_DL_AD0_DATA_LEN + ADS_DL_AD_DATA_HEADROOM_PAD;
    }
    else
    {
        usLen = ADS_DL_AD1_DATA_LEN + ADS_DL_AD_DATA_HEADROOM_PAD;
    }


    for (i = 0; i < ulIpfAdNum; i++)
    {
        pstIpfAdDesc = ADS_DL_GET_IPF_AD_BUFFER_PTR(enAdType, i);

        pstZcData = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(usLen);

        if (VOS_NULL_PTR == pstZcData)
        {
            ADS_DBG_DL_ALLOC_AD_FAIL_NUM(enAdType, 1);
            break;
        }

        /* ��������ͷ��� */
        pstZcHead = pstZcData->data;

        /* ƫ��skbuff��tailָ�� */
        IMM_ZcPut(pstZcData, usLen);

        /* ƫ��headָ��14���ֽڣ�����MACͷ */
        pstZcPullData = (VOS_CHAR *)IMM_ZcPull(pstZcData, ADS_DL_AD_DATA_PTR_OFFSET + ADS_DL_AD_DATA_HEADROOM_PAD);

        ADS_CACHE_INVALIDATE(pstZcHead, usLen);

        /* ���OUTPUT0��Ŀ�ĵ�ַ */
        pstIpfAdDesc->u32OutPtr0 = (VOS_UINT32)virt_to_phys((VOS_UINT32 *)pstZcPullData);

        /* ���OUTPUT1��SKBUFF */
        pstIpfAdDesc->u32OutPtr1 = (VOS_UINT32)pstZcData;

        ADS_DBG_DL_ALLOC_AD_SUCC_NUM(enAdType, 1);;

        ulActAdNum++;
    }

    /* ���뵽AD����Ҫ����ADQ */
    if (0 != ulActAdNum)
    {
        lRslt = BSP_IPF_ConfigDlAd(enAdType, ulActAdNum, ADS_DL_GET_IPF_AD_BUFFER_PTR(enAdType, 0));

        if (IPF_SUCCESS != lRslt)
        {
            ADS_DBG_DL_CONFIG_AD_FAIL_NUM(enAdType, 1);

            /* ����ʧ�ܣ��ͷ��ڴ� */
            for (i = 0; i < ulActAdNum; i++)
            {
                IMM_ZcFree((IMM_ZC_STRU *)ADS_DL_GET_IPF_AD_BUFFER_PTR(enAdType, i)->u32OutPtr1);
            }

            *pulActAdNum = 0;
            return;
        }

        ADS_DBG_DL_CONFIG_AD_SUCC_NUM(enAdType, 1);
    }

    /* ���ʵ�����õ�AD��Ŀ */
    *pulActAdNum = ulActAdNum;

    return;
}



VOS_VOID ADS_DL_ProcAdq(VOS_VOID)
{
    VOS_INT32                           lRslt;
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    VOS_UINT                            ulActAd0Num;
    VOS_UINT                            ulActAd1Num;

    ulIpfAd0Num = 0;
    ulIpfAd1Num = 0;
    ulActAd0Num = 0;
    ulActAd1Num = 0;

    /* ��ȡ����ADQ�Ŀ��е�AD���� */
    lRslt = BSP_IPF_GetDlAdNum(&ulIpfAd0Num, &ulIpfAd1Num);

    if (IPF_SUCCESS != lRslt)
    {
        ADS_DBG_DL_GET_AD_FAIL_NUM(1);
        return;
    }

    /* �������ô��ڴ��ADQ1 */
    if (0 != ulIpfAd1Num)
    {
        ADS_DL_ConfigAdq(IPF_AD_1, ulIpfAd1Num, &ulActAd1Num);
    }

    /* ������С�ڴ��ADQ0 */
    if (0 != ulIpfAd0Num)
    {
        ADS_DL_ConfigAdq(IPF_AD_0, ulIpfAd0Num, &ulActAd0Num);
    }
   /* AD0Ϊ�ջ���AD1Ϊ����Ҫ����������ʱ�� */
    if (((0 == ulActAd0Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd0Num))
     || ((0 == ulActAd1Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd1Num)))
    {
        /* �������ADQ�κ�һ���������벻���ڴ棬����ʱ�� */
        ADS_DL_StartAdqEmptyTimer();
    }
    return;
}


VOS_VOID ADS_DL_InitAdq(VOS_VOID)
{
    ADS_DL_ProcAdq();
}


VOS_VOID ADS_DL_SendNdClientDataInd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT32                          ulResult;
    ADS_NDCLIENT_DATA_IND_STRU         *pstDataInd;
    /* Modified by l60609 for DSDA Phase II, 2012-12-14, Begin */
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT16                          usDataLen;

    pstImmZc = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);

    usDataLen = pstRdDesc->u16PktLen;

    /*������Ϣ  */
    pstDataInd = (ADS_NDCLIENT_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + usDataLen - 2);

    /* �ڴ�����ʧ�ܣ����� */
    if( VOS_NULL_PTR == pstDataInd )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: pstDataInd is NULL!");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstDataInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + usDataLen - 2 - VOS_MSG_HEAD_LENGTH);

    /*��д��Ϣ����*/
    /* ND CLIENT ��PID */
    pstDataInd->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstDataInd->enMsgId       = ID_ADS_NDCLIENT_DATA_IND;
    pstDataInd->enModemId     = ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->ucRabId       = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->usLen         = usDataLen;

    PS_MEM_CPY(pstDataInd->aucData, pstImmZc->data, usDataLen);

    /* Modified by l60609 for DSDA Phase II, 2012-12-14, End */

    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstDataInd);

    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: Send msg fail!");
    }

    return;
}


VOS_VOID ADS_DL_FreeIpfUsedAd0(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulAdNum;

    IPF_AD_DESC_S                       astAdDesc[IPF_DLAD0_DESC_SIZE];

    ulAdNum = 0;
    PS_MEM_SET(astAdDesc, 0, sizeof(IPF_AD_DESC_S) * IPF_DLAD0_DESC_SIZE);
    if (IPF_SUCCESS == BSP_IPF_GetUsedDlAd(IPF_AD_0, (BSP_U32 *)&ulAdNum, astAdDesc))
    {
        /* �ͷ�ADQ0���ڴ� */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD0_DESC_SIZE); i++)
        {
            IMM_ZcFree((IMM_ZC_STRU *)astAdDesc[i].u32OutPtr1);
        }
    }

    return;
}


VOS_VOID ADS_DL_FreeIpfUsedAd1(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulAdNum;

    IPF_AD_DESC_S                       astAdDesc[IPF_DLAD1_DESC_SIZE];

    ulAdNum = 0;
    PS_MEM_SET(astAdDesc, 0, sizeof(IPF_AD_DESC_S) * IPF_DLAD1_DESC_SIZE);
    if (IPF_SUCCESS == BSP_IPF_GetUsedDlAd(IPF_AD_1, (BSP_U32 *)&ulAdNum, astAdDesc))
    {
        /* �ͷ�ADQ1���ڴ� */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD1_DESC_SIZE); i++)
        {
            IMM_ZcFree((IMM_ZC_STRU *)astAdDesc[i].u32OutPtr1);
        }
    }

    return;
}


#if 0

VOS_VOID ADS_DL_SendNdClientErrInd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT32                          ulResult;
    ADS_NDCLIENT_ERR_IND_STRU          *pstErrInd;
    /* Modified by l60609 for DSDA Phase II, 2012-12-14, Begin */
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT16                          usDataLen;

    pstImmZc = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);

    usDataLen = pstRdDesc->u16PktLen;

    /*������Ϣ  */
    pstErrInd = (ADS_NDCLIENT_ERR_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ACPU_PID_ADS_DL,
                                             sizeof(ADS_NDCLIENT_ERR_IND_STRU) + usDataLen -2);

    /* �ڴ�����ʧ�ܣ����� */
    if( VOS_NULL_PTR == pstErrInd )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientErrInd: pstErrInd is NULL!");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstErrInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_NDCLIENT_ERR_IND_STRU) + usDataLen -2 - VOS_MSG_HEAD_LENGTH);

    /*��д��Ϣ����*/
    /* ND CLIENT ��PID */
    pstErrInd->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstErrInd->enMsgId       = ID_ADS_NDCLIENT_ERR_IND;
    pstErrInd->enModemId     = ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD_1(pstRdDesc->u16UsrField1);
    pstErrInd->ucRabId       = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD_1(pstRdDesc->u16UsrField1);
    pstErrInd->enErrType     = ADS_NDCLIENT_ERR_TYPE_MTU_OVERLONG;
    pstErrInd->usLen         = usDataLen;

    PS_MEM_CPY(pstErrInd->aucData, pstImmZc->data, usDataLen);

    /* Modified by l60609 for DSDA Phase II, 2012-12-14, End */

    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstErrInd);

    if(VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientErrInd: Send msg fail!");
    }

    return;
}
#endif

#else

VOS_VOID ADS_DL_SendNdClientDataInd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT32                          ulResult;
    ADS_NDCLIENT_DATA_IND_STRU         *pstDataInd;
    /* Modified by l60609 for DSDA Phase II, 2012-12-14, Begin */
    VOS_UINT16                          usDataLen;

    usDataLen = pstRdDesc->u16PktLen;

    /*������Ϣ  */
    pstDataInd = (ADS_NDCLIENT_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + usDataLen - 2);

    if (0 == usDataLen)
    {
        vos_printf("ADS_DL_SendNdClientDataInd: usDataLen is 0\r\n");
    }

    if (0 == pstRdDesc->u32OutPtr)
    {
        vos_printf("ADS_DL_SendNdClientDataInd: u32OutPtr is NULL\r\n");
    }

    /* �ڴ�����ʧ�ܣ����� */
    if( VOS_NULL_PTR == pstDataInd )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: pstDataInd is NULL!");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstDataInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + usDataLen -2 - VOS_MSG_HEAD_LENGTH);

    /*��д��Ϣ����*/
    /* ND CLIENT ��PID */
    pstDataInd->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstDataInd->enMsgId       = ID_ADS_NDCLIENT_DATA_IND;
    pstDataInd->enModemId     = ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->ucRabId       = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->usLen         = usDataLen;

    PS_MEM_CPY(pstDataInd->aucData, (VOS_UINT8 *)TTF_PHY_TO_VIRT(pstRdDesc->u32OutPtr), usDataLen);
    /* Modified by l60609 for DSDA Phase II, 2012-12-14, End */

    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstDataInd);

    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: Send msg fail!");
    }

    return;
}

#if 0

VOS_VOID ADS_DL_SendNdClientErrInd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT32                          ulResult;
    ADS_NDCLIENT_ERR_IND_STRU          *pstErrInd;
    /* Modified by l60609 for DSDA Phase II, 2012-12-14, Begin */
    VOS_UINT16                          usDataLen;

    usDataLen = pstRdDesc->u16PktLen;

    /*������Ϣ  */
    pstErrInd = (ADS_NDCLIENT_ERR_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ACPU_PID_ADS_DL,
                                             sizeof(ADS_NDCLIENT_ERR_IND_STRU) + usDataLen - 2);

    /* �ڴ�����ʧ�ܣ����� */
    if( VOS_NULL_PTR == pstErrInd )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientErrInd: pstErrInd is NULL!");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstErrInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(ADS_NDCLIENT_ERR_IND_STRU) + usDataLen - 2 - VOS_MSG_HEAD_LENGTH);

    /*��д��Ϣ����*/
    /* ND CLIENT ��PID */
    pstErrInd->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstErrInd->enMsgId       = ID_ADS_NDCLIENT_ERR_IND;
    pstErrInd->enModemId     = ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD_1(pstRdDesc->u16UsrField1);
    pstErrInd->ucRabId       = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD_1(pstRdDesc->u16UsrField1);
    pstErrInd->enErrType     = ADS_NDCLIENT_ERR_TYPE_MTU_OVERLONG;
    pstErrInd->usLen         = usDataLen;

    PS_MEM_CPY(pstErrInd->aucData, (VOS_UINT8 *)pstRdDesc->u32OutPtr, usDataLen);

    /* Modified by l60609 for DSDA Phase II, 2012-12-14, End */

    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstErrInd);

    if(VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientErrInd: Send msg fail!");
    }

    return;
}
#endif

#endif


VOS_VOID ADS_DL_FreeRd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    IMM_ZcFree((IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr));
#else
    /* �ͷ�C���ڴ� */
    IMM_RemoteFreeTtfMem(ADS_DL_GET_TTFMEM_FROM_IPF_USR2(pstRdDesc->u32UsrField2));
#endif

    return;
}

VOS_VOID ADS_DL_Xmit(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucInstanceIndex,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType,
    IMM_ZC_STRU                        *pstCurImmZc
)
{
    RCV_DL_DATA_FUNC                    pRcvDlDataFunc = VOS_NULL_PTR;
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL)
    RCV_DL_DATA_FUNC                    pRcvDlFilterDataFunc    = VOS_NULL_PTR;
    VOS_UINT32                          ulDataFilterSended = VOS_FALSE;
#endif
    IMM_ZC_STRU                        *pstLstImmZc = VOS_NULL_PTR;
    ADS_PKT_TYPE_ENUM_UINT8             enLstIpType;

    /* ��ȡRABID��Ӧ���лص�����ָ�� */
    if (ADS_IS_VALID_RABID(ucRabId))
    {
        pRcvDlDataFunc = ADS_DL_GET_DATA_CALLBACK_FUNC(ucInstanceIndex, ucRabId);
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL)
        pRcvDlFilterDataFunc    = ADS_DL_GET_FILTER_DATA_CALLBACK_FUNC(ucInstanceIndex, ucRabId);
#endif
    }
    else
    {
        ADS_NORMAL_LOG1(ACPU_PID_ADS_DL,
            "ADS_DL_SndImmZc: Invaild rabId is", ucRabId);

        ADS_DBG_DL_FREE_NUM(ucInstanceIndex,1);

        IMM_ZcFree(pstCurImmZc);

        return;
    }

    pstLstImmZc = ADS_DL_GET_LST_DATA_PTR(ucInstanceIndex,ucRabId);
    enLstIpType    = ADS_DL_GET_LST_DATA_IPTYPE(ucInstanceIndex,ucRabId);

#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL)
    /*note: �˶δ����Ǵ�v3r3����ֲ�������ǽ������ݷ�����������filter�����ݷ��͵�filter�ص��������������ݷ�����ԭ���лص�*/
    /* ���������й��˻ص������������ж��Ƿ���Ҫ���͸����й��˺������� */
    if (VOS_NULL_PTR != pRcvDlFilterDataFunc)
    {
        if (VOS_NULL_PTR != pstLstImmZc)
        {
            ADS_DBG_SEND_DL_PKT_NUM(ucInstanceIndex, 1);
            pstLstImmZc->psh = 0;
            if (VOS_NULL_PTR == pstCurImmZc)
            {
                pstLstImmZc->psh = 1;
            }
            
            /* �������й������ݰ�������������Ƿ���Ҫ���ɹ��˺������� */
            if (VOS_OK == ADS_FILTER_ProcDlPacket(pstLstImmZc, enLstIpType) || (VOS_NULL_PTR == pRcvDlDataFunc))
            {
                (VOS_VOID)pRcvDlFilterDataFunc(ADS_BUILD_EX_RAB_ID(ucInstanceIndex, ucRabId), pstLstImmZc, enLstIpType);
                ulDataFilterSended = VOS_TRUE;
            }
            
        }
        ADS_DL_SET_LST_DATA_PTR(ucInstanceIndex,ucRabId, pstCurImmZc);
        ADS_DL_SET_LST_DATA_IPTYPE(ucInstanceIndex,ucRabId, enIpType);
        
        if ( (VOS_NULL_PTR == pRcvDlDataFunc) || ( VOS_TRUE == ulDataFilterSended ) )
        {
            return;
        }
    }
#endif

    /* ������������ */
    if (VOS_NULL_PTR != pRcvDlDataFunc)
    {
        if (VOS_NULL_PTR != pstLstImmZc)
        {
            ADS_DBG_SEND_DL_PKT_NUM(ucInstanceIndex, 1);
            pstLstImmZc->psh = 0;
            if (VOS_NULL_PTR == pstCurImmZc)
            {
                pstLstImmZc->psh = 1;
            }

            (VOS_VOID)pRcvDlDataFunc(ADS_BUILD_EX_RAB_ID(ucInstanceIndex, ucRabId), pstLstImmZc, enLstIpType);
        }
        ADS_DL_SET_LST_DATA_PTR(ucInstanceIndex,ucRabId, pstCurImmZc);
        ADS_DL_SET_LST_DATA_IPTYPE(ucInstanceIndex,ucRabId, enIpType);
    }
    else
    {
        ADS_NORMAL_LOG1(ACPU_PID_ADS_DL,
            "ADS_DL_SendNetDevData1: Free TTF memory, RabId is", ucRabId);

        ADS_DBG_DL_FREE_NUM(ucInstanceIndex, 1);

        IMM_ZcFree(pstCurImmZc);
        if (VOS_NULL_PTR != pstLstImmZc)
        {
            IMM_ZcFree(pstLstImmZc);
        }
        ADS_DL_SET_LST_DATA_PTR(ucInstanceIndex,ucRabId,VOS_NULL_PTR);
    }

    return;
}

VOS_VOID ADS_DL_ProcRd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT8                           ucRabId;
    ADS_PKT_TYPE_ENUM_UINT8             enIpType;
    IMM_ZC_STRU                        *pstImmZc       = VOS_NULL_PTR;

    /* Added by l60609 for DSDA Phase II, 2012-11-24, Begin */
    VOS_UINT8                           ucInstanceIndex;
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    VOS_UINT32                          ulIpLen;
#endif

    /* �ӿ��޸ĺ󣬻�ȡ��ֵ */
    ucInstanceIndex = (VOS_UINT8)ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    ucRabId = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    enIpType = ADS_DL_GET_IP_TYPE_FROM_IPF_RSLT(pstRdDesc->u16Result);

    /* Modified by l60609 for AP������Ŀ ��2012-08-31 Begin */
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    /* �����Ź��ܣ����ָ������SK BUFF */
    pstImmZc       = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);
    ulIpLen        = ADS_DL_GET_LEN_FROM_IPF_PKT_LEN(pstRdDesc->u16PktLen);
    pstImmZc->tail -= (pstImmZc->len - ulIpLen);
    pstImmZc->len  = ulIpLen;
#else
    /* ��IPF���˳�������ת����Zc���� */
    pstImmZc = IMM_DataTransformImmZc((VOS_UINT8*)TTF_PHY_TO_VIRT((VOS_UINT32)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr)),
                                      ADS_DL_GET_LEN_FROM_IPF_PKT_LEN(pstRdDesc->u16PktLen),
                                      ADS_DL_GET_TTFMEM_FROM_IPF_USR2(pstRdDesc->u32UsrField2));
    if (VOS_NULL_PTR == pstImmZc)
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNetDevData1: pstImmZc is null! ");

        ADS_DBG_DL_TRANS_FROM_IMMZC_ERR_NUM(1);

        /*IMM_DataTranferImmZc���벻��IMM_ZCͷ�ڵ㣬�ӿ��ڲ�����C�˿�˹����ڴ档*/
        return;
    }
#endif

    IPS_MNTN_TraceIpInfo(pstImmZc,ID_IPS_TRACE_IP_ADS_DL);

    ADS_DL_Xmit(ucRabId, ucInstanceIndex, enIpType, pstImmZc);

    /* Modified by l60609 for AP������Ŀ ��2012-08-31 End */
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    return;
}


VOS_VOID ADS_DL_ProcIpfResult(VOS_VOID)
{
    BSP_U32                             ulRdNum = IPF_DLRD_DESC_SIZE;
    VOS_UINT32                          ulCnt;
    ADS_DL_IPF_RESULT_STRU             *pstIpfRslt;
    IPF_RD_DESC_S                      *pstRdDesc;
    ADS_DRV_ASSEM_FUNC                  pFcAssemTuneFunc = VOS_NULL_PTR;
    /* Added by l60609 for DSDA Phase II, 2012-11-24, Begin */
    VOS_UINT8                           ucInstanceIndex;
    /* Added by l60609 for DSDA Phase II, 2012-11-24, End */
    VOS_UINT8                           ucRabId;
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
#endif

    ucInstanceIndex = 0;

    /*
    IPF_RD_DESC_S��u16Result����
    [15]Reserve
    [14]bd_cd_noeqBD��len��CD�ĳ��Ȳ��ȴ�����ʾ��0��ʾ����ƥ�䣬1��ʾ���Ȳ�ƥ��
    [13]pkt_parse_err���ݽ�������ָʾ��0��ʾ���ݽ���������1��ʾ���ݽ�������
    [12]bd_pkt_noeqBD��len��IP��ͷָʾ��len���ȴ���ָʾ��0��ʾ����ƥ�䣬1��ʾ���Ȳ�ƥ��
    [11]head_len_err IPV4���ȴ���ָʾ�źţ�IPV6����鳤�ȣ�0��ʾͷ������ȷ��1��ʾͷ���ȴ���
    [10]version_err�汾�Ŵ���ָʾ��0��ʾ�汾����4��6��1��ʾ�汾�Ų���4��6
    [9]ip_type IP�����ͣ�0��ʾIPV4��1��ʾIPV6
    [8]ff_type��Ƭ����һ����Ƭ�Ƿ�����ϲ�ͷָʾ��0��ʾ��Ƭ����һ����Ƭ�����ϲ�ͷ(IP��δ��ƬʱҲΪ0)
     1��ʾ��Ƭ����һ����Ƭ�����ϲ�ͷ
    [7:6]pf_type IP����Ƭָʾ���ͣ�00��ʾIP��δ��Ƭ��01��ʾIP����Ƭ����Ϊ��һ����Ƭ��
       02��ʾ��Ƭ����Ϊ���һ����Ƭ��03��ʾ��Ƭ����Ϊ�м��Ƭ
    [0:5]bear_id���غţ����Ϊ0x3F�������й�������ƥ��
    */

    /*
    IPF_RD_DESC_S��user field����
    u16UsrField1: RabId
    u32UsrField2: Ŀ��TTF_MEM_STָ��
    u32UsrField3: ԴTTF_MEM_STָ��
    */

    /* ��ȡRD */
    pstRdDesc = ADS_DL_GET_IPF_RD_BUFFER_PTR(0);
    BSP_IPF_GetDlRd(&ulRdNum, pstRdDesc);

    /* ��ȡ��RDΪ0 */
    if (0 == ulRdNum)
    {
        /* ����RD��ȡ����Ϊ0��ͳ�Ƹ��� */
        ADS_DBG_DL_RECV_RD_ZERO_NUM(1);

        return;
    }

#if (FEATURE_OFF == FEATURE_LTE)
    DRV_WDT_FEED(0);
#endif

    /* ����RDͳ�Ƹ��� */
    ADS_DBG_DL_RECV_RD_NUM(ulRdNum);

    /* ׷�����н������� */
    ADS_MNTN_TraceRcvDlData();

    /* ����Ƿ���Ҫ��������������� */
    if (VOS_TRUE == ADS_DL_IsFcAssemTuneNeeded(ulRdNum))
    {
        pFcAssemTuneFunc = ADS_DL_GET_FC_ASSEM_TUNE_FUNC(0);
        pFcAssemTuneFunc();
    }

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    /* ������AD���ٴ���RD */
    ADS_DL_ProcAdq();
#endif

    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    for (ulCnt = 0; ulCnt < ulRdNum; ulCnt++)
    {
        pstRdDesc  = ADS_DL_GET_IPF_RD_BUFFER_PTR(ulCnt);
        pstIpfRslt = (ADS_DL_IPF_RESULT_STRU*)&(pstRdDesc->u16Result);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
        pstImmZc = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);
        ADS_CACHE_INVALIDATE(pstImmZc->data - ADS_DL_AD_DATA_PTR_OFFSET, pstRdDesc->u16PktLen + ADS_DL_AD_DATA_PTR_OFFSET);
#endif

        /* �ӿ��޸ĺ󣬻�ȡ��ֵ */
        ucInstanceIndex = (VOS_UINT8)ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);

        /* ͳ�������������յ��������ֽ���������������ѯ */
        ADS_RECV_DL_PERIOD_PKT_NUM(ucInstanceIndex, ADS_DL_GET_LEN_FROM_IPF_PKT_LEN(pstRdDesc->u16PktLen));

        /* BearId 0x3F: �����������ݰ���Ҫת����NDIS/PPP/RNIC*/
        if (CDS_ADS_DL_IPF_BEARER_ID_INVALID == pstIpfRslt->usBearedId)
        {
            if (ADS_DL_IPF_RD_RSLT_IS_ERR_PKT(pstRdDesc->u16Result))
            {
                ADS_DBG_DL_IPF_ERR_PKT_NUM(ucInstanceIndex, 1);
            }

            ADS_DL_ProcRd(pstRdDesc);
        }
        /* BearId 19: NDClient������Ҫת����NDClient */
        else if (CDS_ADS_DL_IPF_BEARER_ID_ICMPV6 == pstIpfRslt->usBearedId)
        {
            /* ����ͳ�Ƽ��� */
            ADS_DBG_DL_RECV_NDCLIENT_PKT_NUM(ucInstanceIndex, 1);

            ADS_DL_SendNdClientDataInd(pstRdDesc);

            ADS_DL_FreeRd(pstRdDesc);
        }
        /* [0,4]��[5,15]����Ϊ�Ƿ����ݰ�; [16,17,18,20,21]Ŀǰֱ���ͷ� */
        else
        {
            /* ����ͳ�Ƽ��� */
            ADS_DBG_DL_RABID_ERR_PKT_NUM(ucInstanceIndex, 1);

            ADS_DL_FreeRd(pstRdDesc);
        }
    }

    for (ucRabId = ADS_RAB_ID_MIN; ucRabId < ADS_RAB_ID_MAX; ucRabId++)
    {
        ADS_DL_Xmit(ucRabId, ucInstanceIndex, 0, VOS_NULL_PTR);
    }

    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    BSP_NCM_Write_Ready();

    return;
}


VOS_UINT32 ADS_DL_IsFcAssemTuneNeeded(VOS_UINT32 ulRdNum)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemInfo;
    VOS_UINT32                          ulRslt = VOS_FALSE;

    /* ��ȡ������ֵ���� */
    pstFcAssemInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    if (VOS_TRUE != pstFcAssemInfo->ulEnableMask)
    {
        pstFcAssemInfo->ulRdCnt += ulRdNum;

        if (ADS_TIME_AFTER_EQ(ADS_GET_CURR_KERNEL_TIME(), (pstFcAssemInfo->ulTmrCnt + pstFcAssemInfo->ulExpireTmrLen)))
        {
            if (VOS_FALSE == pstFcAssemInfo->ulFcActiveFlg)
            {
                if (pstFcAssemInfo->ulRdCnt >= pstFcAssemInfo->ulRateUpLev)
                {
                    ADS_DBG_DL_FC_ACTIVATE_NUM(1);
                    pstFcAssemInfo->ulFcActiveFlg = VOS_TRUE;
                    ulRslt = VOS_TRUE;
                }
            }
            else
            {
                if (pstFcAssemInfo->ulRdCnt <= pstFcAssemInfo->ulRateDownLev)
                {
                    pstFcAssemInfo->ulFcActiveFlg = VOS_FALSE;
                }
            }

            ADS_DBG_DL_FC_TMR_EXP_NUM(1);
            pstFcAssemInfo->ulTmrCnt = ADS_GET_CURR_KERNEL_TIME();
            pstFcAssemInfo->ulRdCnt = 0;
        }
    }

    return ulRslt;
}


VOS_VOID ADS_DL_RegDrvAssemFunc(FC_ADS_DRV_ASSEM_STRU *pstDrvAssemParam)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemParamInfo;

    pstFcAssemParamInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    pstFcAssemParamInfo->ulEnableMask     = pstDrvAssemParam->ucEnableMask;
    pstFcAssemParamInfo->ulRateUpLev      = pstDrvAssemParam->ulDlRateUpLev;
    pstFcAssemParamInfo->ulRateDownLev    = pstDrvAssemParam->ulDlRateDownLev;
    pstFcAssemParamInfo->ulExpireTmrLen   = pstDrvAssemParam->ulExpireTmrLen;
    pstFcAssemParamInfo->pFcAssemTuneFunc = pstDrvAssemParam->pDrvAssemFunc;

    return;
}


VOS_UINT32 ADS_DL_RegDlDataCallback(
    VOS_UINT8                           ucRabId,
    RCV_DL_DATA_FUNC                    pFunc)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId�ĸ�2��bit��ʾmodem id*/
    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* RabId�Ϸ��Լ�� */
    if (VOS_OK != ADS_IsValidRabId(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RegDlDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    /* ����ADS�������ݻص����� */
    pstDlRabInfo->ucRabId        = ucRealRabId;
    pstDlRabInfo->pRcvDlDataFunc = pFunc;

    return VOS_OK;
}


VOS_UINT32 ADS_DL_RegFilterDataCallback(
    VOS_UINT8                           ucRabId,
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr,
    RCV_DL_DATA_FUNC                    pFunc
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId�ĸ�2��bit��ʾmodem id*/
    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* RabId�Ϸ��Լ�� */
    if (!ADS_IS_VALID_RABID(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RegFilterDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* ����ADS�������ݹ��˻ص����� */
    pstDlRabInfo->ucRabId               = ucRealRabId;
    pstDlRabInfo->pRcvDlFilterDataFunc  = pFunc;

    /* ������˵�ַ��Ϣ */
    ADS_FILTER_SaveIPAddrInfo(pstFilterIpAddr);

    return VOS_OK;
}


VOS_UINT32 ADS_DL_DeregFilterDataCallback(VOS_UINT8 ucRabId)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId�ĸ�2��bit��ʾmodem id*/
    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* RabId�Ϸ��Լ�� */
    if (!ADS_IS_VALID_RABID(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_DeregFilterDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* ȥע��ADS�������ݹ��˻ص����� */
    pstDlRabInfo->pRcvDlFilterDataFunc  = VOS_NULL_PTR;

    /* ���������Ϣ */
    ADS_FILTER_Reset();

    return VOS_OK;
}

/* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */

VOS_UINT32 ADS_DL_ProcPdpStatusInd(
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL)
    VOS_UINT8                                           ucCid,
#endif
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    ADS_PDP_STATUS_ENUM_UINT8           enPdpStatus,
    ADS_QCI_TYPE_ENUM_UINT8             enQciType,
    ADS_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    /* Added by l60609 for DSDA Phase II, 2012-11-24, Begin */
    VOS_UINT8                           ucInstanceIndex;
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;

    enPktType      = ADS_CDS_IPF_PKT_TYPE_IP;

    ucInstanceIndex = (VOS_UINT8)enModemId;
    /* Added by l60609 for DSDA Phase II, 2012-11-24, End */

    /* RabId�Ϸ��Լ�� */
    if (VOS_OK != ADS_IsValidRabId(ucRabId))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_ProcPdpStatusInd: Rab Id is invalid");

        return VOS_ERR;
    }

    if (ADS_PDP_PPP == enPdpType)
    {
        enPktType = ADS_CDS_IPF_PKT_TYPE_PPP;
    }

    /* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRabId);
    /* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

    /* PDP���� */
    if (ADS_PDP_STATUS_ACT == enPdpStatus)
    {
        /* ����ADS�������ݻص���RABID */
        pstDlRabInfo->ucRabId        = ucRabId;
        pstDlRabInfo->enPktType      = enPktType;
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL)
        pstDlRabInfo->ulIdMark      |= (1 << ucCid);
#endif
    }
    /* PDPȥ����  */
    else if (ADS_PDP_STATUS_DEACT == enPdpStatus)
    {
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL)
        pstDlRabInfo->ulIdMark      &= (~(1 << ucCid));

        if ( 0 == pstDlRabInfo->ulIdMark )
        {
            /* ���ADS�������ݻص����� */
            pstDlRabInfo->ucRabId        = ADS_RAB_ID_INVALID;
            pstDlRabInfo->pRcvDlDataFunc = VOS_NULL_PTR;
            pstDlRabInfo->pRcvDlFilterDataFunc = VOS_NULL_PTR;
        }
#else
        /* ���ADS�������ݻص����� */
        pstDlRabInfo->ucRabId        = ADS_RAB_ID_INVALID;
        pstDlRabInfo->pRcvDlDataFunc = VOS_NULL_PTR;
        pstDlRabInfo->pRcvDlFilterDataFunc = VOS_NULL_PTR;
#endif
    }
    else
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_ProcPdpStatusInd: Pdp Status is invalid");
    }

    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvTafPdpStatusInd(MsgBlock *pMsg)
{
    ADS_PDP_STATUS_IND_STRU            *pstPdpStatusInd;
    VOS_UINT32                          ulRslt;

    pstPdpStatusInd = (ADS_PDP_STATUS_IND_STRU *)pMsg;

    ulRslt = ADS_DL_ProcPdpStatusInd(
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL) /*add parameter CID when BIP*/
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



VOS_UINT32 ADS_DL_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;

    /* ֹͣ���������Ķ�ʱ�� */
    for (ucIndex = 0; ucIndex < ADS_MAX_TIMER_NUM; ucIndex++)
    {
        ADS_StopTimer(ACPU_PID_ADS_DL, ucIndex);
    }

#if (FEATURE_OFF == FEATURE_SKB_EXP)
    /* �ͷ�IPF��AD */
    ADS_DL_FreeIpfUsedAd1();
    ADS_DL_FreeIpfUsedAd0();
#endif

    /* �ͷ��ź�����ʹ�õ���API����������� */
    VOS_SmV(ADS_GetDLResetSem());

    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvCcpuResetEndInd(
    MsgBlock                           *pstMsg
)
{
#if (FEATURE_OFF == FEATURE_SKB_EXP)
    /* ��λIPF */
    BSP_IPF_DlRegReInit();

    /* ���³�ʼ��ADQ */
    ADS_DL_InitAdq();
#endif

    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvTafMsg(MsgBlock* pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_APS_ADS_PDP_STATUS_IND:
            ADS_DL_RcvTafPdpStatusInd(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvCdsMsg(MsgBlock *pMsg)
{
    /* ��ʱû��Ҫ�������Ϣ������յ���Ϣ�����д��� */
    return VOS_ERR;
}


VOS_UINT32 ADS_DL_RcvAdsDlMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    /* Modified by l60609 for L-C��������Ŀ, 2014-01-07, Begin */
    switch(pstMsg->ulMsgName)
    {
        case ID_ADS_CCPU_RESET_START_IND:
            ADS_DL_RcvCcpuResetStartInd(pMsg);
            break;

        case ID_ADS_CCPU_RESET_END_IND:
            ADS_DL_RcvCcpuResetEndInd(pMsg);
            break;

        default:
            ADS_NORMAL_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RcvAdsDlMsg: rcv error msg id %d\r\n", pstMsg->ulMsgName);
            break;
    }
    /* Modified by l60609 for L-C��������Ŀ, 2014-01-07, End */

    return VOS_OK;
}


VOS_VOID ADS_DL_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* ��Ϣ�ķַ����� */
    switch ( pMsg->ulSenderPid )
    {
        /* ����APS����Ϣ */
        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
            ADS_DL_RcvTafMsg(pMsg);
            return;

        /* ����CDS����Ϣ */
        case UEPS_PID_CDS:
            ADS_DL_RcvCdsMsg(pMsg);
            return;

        /* ����ADS DL����Ϣ */
        case ACPU_PID_ADS_DL:
            ADS_DL_RcvAdsDlMsg(pMsg);
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

