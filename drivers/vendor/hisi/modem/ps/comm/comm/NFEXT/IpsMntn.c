

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "v_typdef.h"
#include "IpsMntn.h"
#include "TTFComm.h"
#include "OmApp.h"
#include "v_id.h"
#include "vos.h"

#ifdef _lint
#include "skbuff.h"
#endif

#if (FEATURE_ON == FEATURE_NFEXT)
#include "NetfilterEx.h"
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_ACPU_IPS_MNTN_C
/*lint -e767 */

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*****************************************************************************
  2 �ṹ����
*****************************************************************************/

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_NFEXT)
IPS_MNTN_TRACE_CONFIG_REQ_STRU          g_stIpsTraceMsgCfg;     /*TCP/IPЭ��ջ��ά�ɲ�������Ϣ*/
IPS_MNTN_INFO_ENTITY                    g_stIpsMntnInfoEntity;  /*TCP/IPЭ��ջ��ά�ɲ�ʵ��*/
#endif      /* #if (FEATURE_ON == FEATURE_NFEXT) */

IPS_MNTN_IP_INFO_CONFIG_REQ_STRU        g_stIpsMntnIPInfoCfg;   /*IP���ݰ�������Ϣ*/

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 UNION����
*****************************************************************************/

/*****************************************************************************
  7 OTHERS����
*****************************************************************************/

/*****************************************************************************
  8 ��������
*****************************************************************************/


VOS_VOID IPS_MNTN_FillMsg(OM_APP_TRACE_STRU *pstAppTrace, VOS_UINT32 ulMsgName, VOS_UINT32 ulMsgLen)
{
    if (VOS_NULL_PTR == pstAppTrace)
    {
        return;
    }

    /* �����Ϣ */
    pstAppTrace->stAppHeader.ucFuncType = OM_TRANS_FUNC;
    pstAppTrace->stAppHeader.usLength   = (VOS_UINT16)(ulMsgLen - VOS_OM_HEADER_LEN);

    OM_AcpuAddSNTime(&(pstAppTrace->stAppHeader.ulSn),
                    &(pstAppTrace->stAppHeader.ulTimeStamp));
    pstAppTrace->usPrimId   = (VOS_UINT16)ulMsgName;
    pstAppTrace->usToolId   = 0;
}


VOS_VOID IPS_MNTN_SndCfgCnf2Om
(
    VOS_UINT16      usPrimId,
    VOS_UINT16      usTransMsgContentLen,
    VOS_VOID       *pTransMsgContent
)
{
    VOS_UINT16                   usIpsMntnToOmMsgLen;
    PS_OM_TRANS_IND_STRU        *pstIpsMntnToOmMsg = VOS_NULL_PTR;

    /*������Ϣ*/
    usIpsMntnToOmMsgLen = PS_OM_TRANS_DATA_OFFSET_LEN + usTransMsgContentLen;
    pstIpsMntnToOmMsg   = (PS_OM_TRANS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_NFEXT, usIpsMntnToOmMsgLen);

    if (VOS_NULL_PTR == pstIpsMntnToOmMsg)
    {
        PS_LOG(ACPU_PID_NFEXT, PS_SUBMOD_NULL, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_SndCfgCnf2Om, ERROR, Call PS_ALLOC_MSG_WITH_HEADER_LEN \
            fail!");
        return;
    }

    /* ��� �� OM��͸����Ϣ */
    IPS_FILL_MSG_HEADER(pstIpsMntnToOmMsg, ACPU_PID_OM);

    pstIpsMntnToOmMsg->usTransPrimId    = OM_TRANS_PRIMID;          /*͸����Ϣ�̶���Ϊ0x5001*/
    pstIpsMntnToOmMsg->ucFuncType       = OM_TRANS_FUNC;            /*͸������*/
    pstIpsMntnToOmMsg->usAppLength      = usIpsMntnToOmMsgLen - PS_OM_TRANS_OM_HEADER_LEN; /*��ȥusAppLength����֮ǰ��ie����*/
    pstIpsMntnToOmMsg->ulSn             = 0;                        /*��ʱ��0*/
    pstIpsMntnToOmMsg->ulTimeStamp      = OM_GetSlice();
    pstIpsMntnToOmMsg->usPrimId         = usPrimId;                 /*����������ϢID��д*/
    pstIpsMntnToOmMsg->usToolsId        = 0;                        /*����ID,Ŀǰ��û��ʹ��*/

    /* ���ȷ����Ϣ */
    if ( (0 != usTransMsgContentLen) && (VOS_NULL_PTR != pTransMsgContent) )
    {
        PS_MEM_CPY(pstIpsMntnToOmMsg->aucData, pTransMsgContent, usTransMsgContentLen);
    }

    if ( VOS_OK != PS_SEND_MSG(ACPU_PID_NFEXT, pstIpsMntnToOmMsg) )
    {
        PS_LOG(ACPU_PID_NFEXT, PS_SUBMOD_NULL, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_SndCfgCnf2Om, ERROR, Call PS_SEND_MSG fail!");
    }

    return;
}

#if (FEATURE_ON == FEATURE_NFEXT)

VOS_UINT32 IPS_MNTN_TransMsg
(
    VOS_UINT8                              *pucTransMsg,
    VOS_UINT32                              ulTransMsgContentLen,
    IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16     enMsgName
)
{
    VOS_UINT32                          ulTraceMsgLen;
    NF_EXT_DATA_RING_BUF_STRU           stBufData;
    OM_APP_TRACE_STRU                  *pstAppTrace = VOS_NULL_PTR;


    if (VOS_NULL_PTR == pucTransMsg)
    {

        PS_LOG(ACPU_PID_NFEXT, PS_SUBMOD_NULL, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_TransMsg, ERROR, pucTransMsg is NULL ");

        return VOS_ERR;
    }



    /*������Ϣ*/
    ulTraceMsgLen   = OM_TRANS_DATA_OFFSET_LEN + ulTransMsgContentLen;
    pstAppTrace     = (OM_APP_TRACE_STRU *)pucTransMsg;

    IPS_MNTN_FillMsg(pstAppTrace, enMsgName, ulTraceMsgLen);

    stBufData.pData         = (VOS_UINT8 *)pstAppTrace;
    stBufData.usDataLen     = (VOS_UINT16)ulTraceMsgLen;

    if (VOS_OK != NFExt_AddDataToRingBuf(&stBufData))
    {
        PS_LOG(ACPU_PID_NFEXT, PS_SUBMOD_NULL, PS_PRINT_WARNING,
            "IPS, IPS_MNTN_TransMsg, ERROR, NFExt_AddDataToRingBuf Fail! ");

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 IPS_MNTN_GetPktLenByTraceCfg
(
    IPS_MNTN_TRACE_CONFIG_STRU     *pstTraceCfg,
    VOS_UINT16                      usPktLen,
    VOS_UINT32                     *pulDataLen
)
{
    *pulDataLen    =   0;

    /*�ж϶�ʱ���Ƿ�����*/
    switch ( pstTraceCfg->ulChoice )
    {
        case IPS_MNTN_TRACE_NULL_CHOSEN:
            return PS_FALSE;
        case IPS_MNTN_TRACE_MSG_HEADER_CHOSEN:
            break;
        case IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN:
            *pulDataLen = TTF_MIN(pstTraceCfg->ulTraceDataLen, usPktLen);
            break;
        case IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN:
            *pulDataLen = usPktLen;
            break;
        default:
            return PS_FALSE;
    }

    return PS_TRUE;
}



VOS_VOID IPS_MNTN_PktInfoCB
(
    VOS_UINT8                              *pucNetIfName,
    VOS_UINT8                              *pucPktData,
    VOS_UINT16                              usPktLen,
    IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16     usType
)
{
    VOS_UINT8                          *pucTraceData;
    IPS_MNTN_TRACE_CONFIG_STRU         *pstTraceCfg;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulRst;

    ulTransDataLen  =   0;
    ulDataLen       =   0;

    if ( VOS_NULL_PTR == pucPktData )
    {
        PS_LOG(ACPU_PID_NFEXT, PS_SUBMOD_NULL, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_PktInfoCB, ERROR, paucPktData is NULL ");
        return;
    }

    /*������Ϣ����ѡ���Ӧ������Ϣ*/
    if(ID_IPS_TRACE_INPUT_DATA_INFO == usType)
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stPreRoutingTraceCfg);
    }
    else if(ID_IPS_TRACE_OUTPUT_DATA_INFO == usType)
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stPostRoutingTraceCfg);
    }
    else if(usType < ID_IPS_TRACE_MSG_TYPE_BUTT)
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stPreRoutingTraceCfg);
    }
    else
    {
        /*��ӡ������Ϣ,��Ϣ���Ͳ�ƥ��*/
        PS_LOG( ACPU_PID_NFEXT, 0, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_PktInfoCB : ERROR : usType is not Expectes!" );
        return;
    }

    /*������Ϣ������Ϣ����ȡ������ĳ���*/
    ulRst = IPS_MNTN_GetPktLenByTraceCfg(pstTraceCfg, usPktLen, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*������ñ���*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_TRACE_MAX_BYTE_LEN, ulDataLen);
    ulTransDataLen      = MNTN_PKT_INFO_OFFSET_LEN + ulDataLen;

    /* ��Linux�ں������ڴ� */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulTransDataLen + OM_TRANS_DATA_OFFSET_LEN);

    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*����͸����Ϣ*/
    pstTraceMsg         = (IPS_MNTN_PKT_INFO_STRU *)(pucTraceData + OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen  = usPktLen;
    DRV_RT_MEMCPY(pstTraceMsg->aucNetIfName, pucNetIfName, IPS_IFNAMSIZ);
    /*lint -e669 */
    DRV_RT_MEMCPY(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, usType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);
    }
}


VOS_VOID IPS_MNTN_BridgePktInfoCB
(
    VOS_UINT8                              *pucSrcPort,
    VOS_UINT8                              *pucDestPort,
    VOS_UINT8                              *pucPktData,
    VOS_UINT16                              usPktLen,
    IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16     usType
)
{
    VOS_UINT8                          *pucTraceData;
    IPS_MNTN_TRACE_CONFIG_STRU         *pstTraceCfg;
    IPS_MNTN_BRIDGE_PKT_INFO_STRU      *pstTraceMsg;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulRst;

    ulTransDataLen  =   0;
    ulDataLen       =   0;

    if ( VOS_NULL_PTR == pucPktData )
    {
        PS_LOG(ACPU_PID_NFEXT, PS_SUBMOD_NULL, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_BridgePktInfoCB, ERROR, paucPktData is NULL ");
        return;
    }

    /*������Ϣ����ѡ���Ӧ������Ϣ*/
    if( usType < ID_IPS_TRACE_MSG_TYPE_BUTT )
    {
        pstTraceCfg = &(g_stIpsTraceMsgCfg.stBridgeArpTraceCfg);
    }
    else
    {
        /*��ӡ������Ϣ,��Ϣ���Ͳ�ƥ��*/
        PS_LOG( ACPU_PID_NFEXT, 0, PS_PRINT_ERROR,
                "IPS, IPS_MNTN_BridgePktInfoCB : ERROR : usType is not Expectes!" );
        return;
    }

    /*������Ϣ������Ϣ����ȡ������ĳ���*/
    ulRst = IPS_MNTN_GetPktLenByTraceCfg(pstTraceCfg, usPktLen, &ulDataLen);
    if(PS_FALSE == ulRst)
    {
        /*������ñ���*/
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_TRACE_MAX_BYTE_LEN, ulDataLen);
    ulTransDataLen      = (MNTN_BRIDGE_PKT_INFO_OFFSET_LEN + ulDataLen);

    /* ��Linux�ں������ڴ� */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulTransDataLen + OM_TRANS_DATA_OFFSET_LEN);

    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*����͸����Ϣ*/
    pstTraceMsg = (IPS_MNTN_BRIDGE_PKT_INFO_STRU *)(pucTraceData + OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen  = usPktLen;

    if (VOS_NULL_PTR != pucSrcPort)
    {
        DRV_RT_MEMCPY(pstTraceMsg->aucSrcPort, pucSrcPort, IPS_END_NAME);
    }
    if (VOS_NULL_PTR != pucDestPort)
    {
        DRV_RT_MEMCPY(pstTraceMsg->aucDestPort, pucDestPort, IPS_END_NAME);
    }

    /*lint -e669 */
    DRV_RT_MEMCPY(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, usType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);
    }

}



VOS_VOID IPS_MNTN_CtrlPktInfoCB
(
    VOS_UINT8                              *pucNetIfName,
    VOS_UINT8                              *pucPktData,
    VOS_UINT16                              usPktLen,
    IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16     usType
)
{

    VOS_UINT8                          *pucTraceData;
    IPS_MNTN_PKT_INFO_STRU             *pstTraceMsg;
    VOS_UINT32                          ulTransDataLen;
    VOS_UINT32                          ulDataLen;

    ulTransDataLen  =   0;
    ulDataLen       =   0;

    if ( VOS_NULL_PTR == pucPktData )
    {
        PS_LOG(ACPU_PID_NFEXT, PS_SUBMOD_NULL, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_CtrlPktInfoCB, ERROR, pucPktData is NULL ");
        return;
    }

    ulDataLen           = PS_MIN(IPS_MNTN_TRACE_MAX_BYTE_LEN, usPktLen);
    ulTransDataLen      = (MNTN_PKT_INFO_OFFSET_LEN + ulDataLen);

    /* ��Linux�ں������ڴ� */
    pucTraceData = NF_EXT_MEM_ALLOC(ACPU_PID_NFEXT, ulTransDataLen + OM_TRANS_DATA_OFFSET_LEN);

    if (VOS_NULL_PTR == pucTraceData)
    {
        NF_EXT_STATS_INC(1, NF_EXT_STATS_ALLOC_MEM_FAIL);

        return;
    }

    /*����͸����Ϣ*/
    pstTraceMsg = (IPS_MNTN_PKT_INFO_STRU *)(pucTraceData + OM_TRANS_DATA_OFFSET_LEN);
    pstTraceMsg->usLen  = usPktLen;
    DRV_RT_MEMCPY(pstTraceMsg->aucNetIfName, pucNetIfName, IPS_IFNAMSIZ);
    /*lint -e669 */
    DRV_RT_MEMCPY(pstTraceMsg->aucData, pucPktData, ulDataLen);
    /*lint +e669 */

    if (VOS_OK != IPS_MNTN_TransMsg(pucTraceData, ulTransDataLen, usType))
    {
        NF_EXT_MEM_FREE(ACPU_PID_NFEXT, pucTraceData);

    }
}



PS_BOOL_ENUM_UINT8  IPS_MNTN_BridgeTraceCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if ( (IPS_MNTN_TRACE_NULL_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_MSG_HEADER_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN != pRcvMsg->stBridgeArpTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


PS_BOOL_ENUM_UINT8  IPS_MNTN_TraceCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    if ( (IPS_MNTN_TRACE_NULL_CHOSEN != pRcvMsg->stPreRoutingTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_MSG_HEADER_CHOSEN != pRcvMsg->stPreRoutingTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN != pRcvMsg->stPreRoutingTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN != pRcvMsg->stPreRoutingTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    if ( (IPS_MNTN_TRACE_NULL_CHOSEN != pRcvMsg->stPostRoutingTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_MSG_HEADER_CHOSEN != pRcvMsg->stPostRoutingTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN != pRcvMsg->stPostRoutingTraceCfg.ulChoice)
        && (IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN != pRcvMsg->stPostRoutingTraceCfg.ulChoice) )
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


PS_BOOL_ENUM_UINT8  IPS_MNTN_TraceAdvancedCfgChkParam(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg)
{
    /*TCP/IPЭ��ջ���Ĺ������ò������*/
    if(PS_FALSE == IPS_MNTN_TraceCfgChkParam(pRcvMsg))
    {
        return PS_FALSE;
    }

    /*������ת���Ĺ������ò������*/
    if(PS_FALSE == IPS_MNTN_BridgeTraceCfgChkParam(pRcvMsg))
    {
        return  PS_FALSE;
    }

    return PS_TRUE;

}


VOS_VOID IPS_MNTN_TraceAdvancedCfgReq(VOS_VOID *pMsg)
{
    PS_BOOL_ENUM_UINT8                  enResult;
    IPS_MNTN_TRACE_CONFIG_REQ_STRU     *pRcvMsg;
    IPS_MNTN_TRACE_CONFIG_CNF_STRU      stIpsTraceCfgCnf;

    pRcvMsg = (IPS_MNTN_TRACE_CONFIG_REQ_STRU *) (((OM_PS_PARAM_REQ_STRU *)pMsg)->aucData);

    /*������ò����Ƿ�Ϸ�*/
    enResult = IPS_MNTN_TraceAdvancedCfgChkParam(pRcvMsg);

    if ( PS_FALSE == enResult )
    {
        /*���������ⲻ�Ϸ�����OM�ظ�����ʧ��*/
        stIpsTraceCfgCnf.enRslt =   PS_FAIL;
        IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );
        PS_LOG(ACPU_PID_NFEXT, 0, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_TraceAdvancedCfgReq check fail");

        return;
    }

    enResult = NFExt_ConfigEffective(pRcvMsg);
    if( PS_FALSE == enResult )
    {
        /*���ע�ṳ�Ӻ���ʧ�ܣ���OM�ظ�����ʧ��*/
        stIpsTraceCfgCnf.enRslt =   PS_FAIL;
        IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );
        PS_LOG(ACPU_PID_NFEXT, 0, PS_PRINT_ERROR,
            "Warning: IPS_MNTN_SetCallbackFunc fail");

        return;
    }

    /*�������ò���*/
    PS_MEM_CPY(&g_stIpsTraceMsgCfg, pRcvMsg, sizeof(IPS_MNTN_TRACE_CONFIG_REQ_STRU));

    /*��OM�ظ����óɹ�*/
    stIpsTraceCfgCnf.enRslt =   PS_SUCC;
    IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF,
            sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );

}


VOS_VOID IPS_MNTN_SendTranMsgDirect(OM_APP_TRACE_STRU *pstAppTrace, VOS_UINT32 ulMsgContenLen, VOS_UINT32 ulMsgName)
{
    VOS_UINT32                          ulTraceMsgLen;

    if (VOS_NULL_PTR == pstAppTrace)
    {
        PS_LOG(ACPU_PID_NFEXT, PS_SUBMOD_NULL, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_SendFlowCtrlMsg, ERROR, pucTransMsg is NULL ");

        return;
    }

    ulTraceMsgLen   = OM_TRANS_DATA_OFFSET_LEN + ulMsgContenLen;

    /* תΪOM͸����Ϣ�ṹ */
    IPS_MNTN_FillMsg(pstAppTrace, ulMsgName, ulTraceMsgLen);

    OM_AcpuSendData((OM_RSP_PACKET_STRU*)pstAppTrace, (VOS_UINT16)ulTraceMsgLen);
}



VOS_VOID IPS_MNTN_FlowCtrl(VOS_UINT32 ulFcType, IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16  usType)
{
    IPS_MNTN_FLOW_CTRL_STRU *pstFlowCtrlMsg;
    VOS_UINT8                aucData[MNTN_FLOW_CTRL_INFO_LEN + OM_TRANS_DATA_OFFSET_LEN];

    pstFlowCtrlMsg = (IPS_MNTN_FLOW_CTRL_STRU *)(aucData + OM_TRANS_DATA_OFFSET_LEN);

    pstFlowCtrlMsg->ulFcType = ulFcType;

    IPS_MNTN_SendTranMsgDirect((OM_APP_TRACE_STRU *)aucData, MNTN_FLOW_CTRL_INFO_LEN, usType);
}

#endif      /* #if (FEATURE_ON == FEATURE_NFEXT) */


PS_BOOL_ENUM_UINT8  IPS_MNTN_IPInfoCfgChkParam(IPS_MNTN_IP_INFO_CONFIG_REQ_STRU *pRcvIpInfoCfg)
{
    if ((PS_TRUE != pRcvIpInfoCfg->enAdsIPConfig) && (PS_FALSE != pRcvIpInfoCfg->enAdsIPConfig))
    {
        return PS_FALSE;
    }

    if ((PS_TRUE != pRcvIpInfoCfg->enUsbIPConfig) && (PS_FALSE != pRcvIpInfoCfg->enUsbIPConfig))
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


VOS_VOID IPS_MNTN_IPInfoCfgReq(VOS_VOID *pMsg)
{
    PS_BOOL_ENUM_UINT8                   enResult;
    IPS_MNTN_IP_INFO_CONFIG_REQ_STRU     *pRcvIpInfoCfg;
    IPS_MNTN_TRACE_CONFIG_CNF_STRU       stIpsTraceCfgCnf;

    pRcvIpInfoCfg   = (IPS_MNTN_IP_INFO_CONFIG_REQ_STRU *) (((OM_PS_PARAM_REQ_STRU *)pMsg)->aucData);

    /*������ò����Ƿ�Ϸ�*/
    enResult        = IPS_MNTN_IPInfoCfgChkParam(pRcvIpInfoCfg);

    if ( PS_FALSE == enResult )
    {
        /*���������ⲻ�Ϸ�����OM�ظ�����ʧ��*/
        stIpsTraceCfgCnf.enRslt = PS_FAIL;
        IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_MNTN_IP_INFO_CONFIG_CNF,
            sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );
        PS_LOG(ACPU_PID_NFEXT, 0, PS_PRINT_ERROR, "Warning: IPS_MNTN_IPInfoCfgReq check fail");

        return;
    }

    /*�������ò���*/
    PS_MEM_CPY(&g_stIpsMntnIPInfoCfg, pRcvIpInfoCfg, sizeof(IPS_MNTN_IP_INFO_CONFIG_REQ_STRU));

    if (PS_TRUE == g_stIpsMntnIPInfoCfg.enUsbIPConfig)
    {
        DRV_USB_REG_IPS_TRACECB(IPS_MNTN_TraceIpInfo);
    }
    else
    {
        DRV_USB_REG_IPS_TRACECB(NULL);
    }

    /*��OM�ظ����óɹ�*/
    stIpsTraceCfgCnf.enRslt = PS_SUCC;
    IPS_MNTN_SndCfgCnf2Om(ID_IPS_OM_MNTN_IP_INFO_CONFIG_CNF,
            sizeof(IPS_MNTN_TRACE_CONFIG_CNF_STRU), &stIpsTraceCfgCnf );
}


VOS_VOID IPS_MNTN_Ipv4DataParse(IPS_MNTN_IP_INFO_STRU *pstIpInfo,VOS_UINT8 *pData)
{
    switch (pstIpInfo->ucL4Proto)
    {
        case IP_IPV4_PROTO_TCP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV4_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_DST_PORT_POS));
            pstIpInfo->ulL4Id         = IP_GET_VAL_NTOH_U32(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_TCP_SEQ_POS));
            pstIpInfo->ulTcpAckSeq    = IP_GET_VAL_NTOH_U32(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_TCP_ACK_POS));
            break;

        case IP_IPV4_PROTO_UDP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV4_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_DST_PORT_POS));
            break;

        case IP_IPV4_PROTO_ICMP:
            pstIpInfo->ucIcmpType     = IP_GET_VAL_NTOH_U8(pData, IP_IPV4_HEAD_LEN);
            if ((IP_IPV4_ICMP_ECHO_REQUEST == pstIpInfo->ucIcmpType)
                ||(IP_IPV4_ICMP_ECHO_REPLY == pstIpInfo->ucIcmpType))
            {
                pstIpInfo->ulL4Id     = IP_GET_VAL_NTOH_U32(pData, (IP_IPV4_HEAD_LEN + IP_IPV4_ICMP_IDENTIFY_POS));
            }
            break;

        default:
            break;
    }

    return;
}


VOS_VOID IPS_MNTN_Ipv6DataParse(IPS_MNTN_IP_INFO_STRU *pstIpInfo,VOS_UINT8 *pData)
{
    switch (pstIpInfo->ucL4Proto)
    {
        case IP_IPV6_PROTO_TCP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV6_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_DST_PORT_POS));
            pstIpInfo->ulL4Id         = IP_GET_VAL_NTOH_U32(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_TCP_SEQ_POS));
            pstIpInfo->ulTcpAckSeq    = IP_GET_VAL_NTOH_U32(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_TCP_ACK_POS));
            break;

        case IP_IPV6_PROTO_UDP:
            pstIpInfo->usSrcPort      = IP_GET_VAL_NTOH_U16(pData, IP_IPV6_HEAD_LEN);
            pstIpInfo->usDstPort      = IP_GET_VAL_NTOH_U16(pData, (IP_IPV6_HEAD_LEN + IP_IPV6_DST_PORT_POS));
            break;

        case IP_IPV6_PROTO_ICMP:
            pstIpInfo->ucIcmpType     = IP_GET_VAL_NTOH_U8(pData, IP_IPV6_HEAD_LEN);
            if ((IP_IPV6_ICMP_ECHO_REQUEST == pstIpInfo->ucIcmpType)
                ||(IP_IPV6_ICMP_ECHO_REPLY == pstIpInfo->ucIcmpType))
            {
                pstIpInfo->ulL4Id     = IP_GET_VAL_NTOH_U32(pData, (IP_IPV6_HEAD_LEN + IP_IPV4_ICMP_IDENTIFY_POS));
            }
            break;

        default:
            break;
    }

    return;
}


VOS_UINT32 IPS_MNTN_GetIPInfoCfg(VOS_UINT16 usType)
{
    if ((ID_IPS_TRACE_IP_ADS_UL == usType)||(ID_IPS_TRACE_IP_ADS_DL == usType))
    {
        return g_stIpsMntnIPInfoCfg.enAdsIPConfig;
    }

    if ((ID_IPS_TRACE_IP_USB_UL == usType)||(ID_IPS_TRACE_IP_USB_DL == usType))
    {
        return g_stIpsMntnIPInfoCfg.enUsbIPConfig;
    }

    return PS_FALSE;
}


VOS_VOID IPS_MNTN_TraceIpInfo(struct sk_buff *skb,VOS_UINT16 usType)
{
    IPS_MNTN_IP_INFO_STRU       *pstIpInfo;
    VOS_UINT32                  ulRst;
    VOS_UINT8                   aucData[MNTN_IP_INFO_LEN + OM_TRANS_DATA_OFFSET_LEN] = {0};
    VOS_UINT32                  ulTraceMsgLen;
    VOS_UINT8                   *pIpData;
    VOS_UINT16                  usIpDataLen;

    ulRst = IPS_MNTN_GetIPInfoCfg(usType);
    if(PS_FALSE == ulRst)
    {
        /*������ñ���*/
        return;
    }

    if ((VOS_NULL_PTR == skb)||(NULL == skb->data))
    {
        PS_LOG(ACPU_PID_NFEXT, PS_SUBMOD_NULL, PS_PRINT_ERROR,
            "IPS, IPS_MNTN_TraceIpInfo, ERROR, skb or skb->data is NULL ");
        return;
    }

    /* USBץȡ��skb data������IP���ݰ������Ǵ�MACͷ��IP���ݰ�*/
    pIpData         = skb->data;

    if (IP_IPV4_VER_AND_HEAD == *pIpData)
    {
        usIpDataLen = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV4_DATA_LEN_POS);
    }
    else if (IP_IPV6_VER_AND_HEAD == *pIpData)
    {
        usIpDataLen = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV6_DATA_LEN_POS);
    }
    else
    {
        usIpDataLen = 0;
    }

    if (usIpDataLen != skb->len)
    {
        pIpData     += MAC_HEAD_LEN;
    }

    /*����͸����Ϣ*/
    pstIpInfo               = (IPS_MNTN_IP_INFO_STRU *)(aucData + OM_TRANS_DATA_OFFSET_LEN);
    pstIpInfo->ucIpVer      = *pIpData>>IP_PROTO_VERSION_POS;

    /* IP���Ľ���TCP,UDP,ICMP��������IP����չͷ*/
    if (IP_IPV4_PROTO_VERSION == pstIpInfo->ucIpVer)
    {
        pstIpInfo->usDataLen  = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV4_DATA_LEN_POS);
        if ((pstIpInfo->usDataLen == skb->len)||(pstIpInfo->usDataLen == (skb->len - MAC_HEAD_LEN)))
        {
            pstIpInfo->usIp4Id    = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV4_IDENTIFY_POS);
            pstIpInfo->ucL4Proto  = IP_GET_VAL_NTOH_U8(pIpData, IP_IPV4_PROTO_POS);

            IPS_MNTN_Ipv4DataParse(pstIpInfo, pIpData);
        }
    }

    if (IP_IPV6_PROTO_VERSION == pstIpInfo->ucIpVer)
    {
        pstIpInfo->usDataLen  = IP_GET_VAL_NTOH_U16(pIpData, IP_IPV6_DATA_LEN_POS);
        if ((pstIpInfo->usDataLen == skb->len)||(pstIpInfo->usDataLen == (skb->len - MAC_HEAD_LEN)))
        {
            pstIpInfo->ucL4Proto  = IP_GET_VAL_NTOH_U8(pIpData, IP_IPV6_PROTO_POS);
            pstIpInfo->usIp4Id    = 0;

            IPS_MNTN_Ipv6DataParse(pstIpInfo, pIpData);
        }
    }

    ulTraceMsgLen = MNTN_IP_INFO_LEN + OM_TRANS_DATA_OFFSET_LEN;
    IPS_MNTN_FillMsg((OM_APP_TRACE_STRU *)aucData, usType, ulTraceMsgLen);

    OM_AcpuSendData((OM_RSP_PACKET_STRU*)aucData, (VOS_UINT16)ulTraceMsgLen);
}
