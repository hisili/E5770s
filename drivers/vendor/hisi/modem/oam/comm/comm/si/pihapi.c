
/*lint  --e{537,958,767,718,746,553,516}*/

#include "vos.h"
#include "si_pih.h"
#include "si_pb.h"
#include "sitypedef.h"
#include "product_config.h"
#include "NasNvInterface.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

#define    THIS_FILE_ID PS_FILE_ID_PIH_API_C

#if  ((OSA_CPU_ACPU == VOS_OSA_CPU) || (defined(DMT)))

VOS_UINT32 SI_PIH_IsSvlte(VOS_VOID)
{
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    SVLTE_SUPPORT_FLAG_STRU             stSvlteFlag;

    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_SVLTE_FLAG, &stSvlteFlag, sizeof(SVLTE_SUPPORT_FLAG_STRU)))
    {
        return VOS_FALSE;
    }

    return (VOS_UINT32)stSvlteFlag.ucSvlteSupportFlag;

#else

    return VOS_FALSE;

#endif
}


VOS_UINT32 SI_PIH_GetReceiverPid(MN_CLIENT_ID_T  ClientId, VOS_UINT32 *pulReceiverPid)
{
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    MODEM_ID_ENUM_UINT16    enModemID;

    /* ���ýӿڻ�ȡModem ID */
    if(VOS_OK != AT_GetModemIdFromClient(ClientId,&enModemID))
    {
        return VOS_ERR;
    }

    if(MODEM_ID_1 == enModemID)
    {
        *pulReceiverPid = I1_MAPS_PIH_PID;
    }
    else
    {
        *pulReceiverPid = I0_MAPS_PIH_PID;
    }

    if (VOS_TRUE == SI_PIH_IsSvlte())
    {
        *pulReceiverPid = I0_MAPS_PIH_PID;
    }
#else
    *pulReceiverPid = MAPS_PIH_PID;
#endif

    return VOS_OK;
}



SI_UINT32 SI_PIH_FdnEnable ( MN_CLIENT_ID_T                  ClientId,
                                    MN_OPERATION_ID_T               OpId,
                                    SI_UINT8                        *pPIN2)
{
    SI_PIH_FDN_ENABLE_REQ_STRU     *pMsg;
    VOS_UINT32                      ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_FdnEnable:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

#if (FEATURE_MULTI_MODEM == FEATURE_OFF)
    if(PB_INIT_FINISHED != gstPBInitState.enPBInitStep)
    {
        PIH_ERROR_LOG("SI_PIH_FdnEnable:PB is Busy.");
        return TAF_FAILURE;
    }
#endif

    pMsg = (SI_PIH_FDN_ENABLE_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_FDN_ENABLE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PIH_WARNING_LOG("SI_PIH_FdnEnable:WARNING AllocMsg FAILED.");
        return TAF_FAILURE;
    }

    pMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pMsg->stMsgHeader.ulMsgName     = SI_PIH_FDN_ENABLE_REQ;
    pMsg->stMsgHeader.usClient      = ClientId;
    pMsg->stMsgHeader.ucOpID        = OpId;
    pMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_FDN_CNF;

    if(VOS_NULL_PTR != pPIN2)
    {
        VOS_MemCpy(pMsg->aucPIN2, pPIN2, SI_PIH_PIN_CODE_LEN);
    }

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PIH_WARNING_LOG("SI_PIH_FdnEnable:WARNING SendMsg FAILED.");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;

}


SI_UINT32 SI_PIH_FdnDisable ( MN_CLIENT_ID_T                  ClientId,
                                    MN_OPERATION_ID_T               OpId,
                                    SI_UINT8                        *pPIN2)
{
    SI_PIH_FDN_DISABLE_REQ_STRU     *pMsg;
    VOS_UINT32                      ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_FdnDisable:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

#if (FEATURE_MULTI_MODEM == FEATURE_OFF)
    if(PB_INIT_FINISHED != gstPBInitState.enPBInitStep)
    {
        PIH_ERROR_LOG("SI_PIH_FdnEnable:PB is Busy.");
        return TAF_FAILURE;
    }
#endif

    pMsg = (SI_PIH_FDN_DISABLE_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_FDN_DISABLE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PIH_WARNING_LOG("SI_PIH_FdnDisable:WARNING AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pMsg->stMsgHeader.ulMsgName     = SI_PIH_FDN_DISALBE_REQ;
    pMsg->stMsgHeader.usClient      = ClientId;
    pMsg->stMsgHeader.ucOpID        = OpId;
    pMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_FDN_CNF;

    if(VOS_NULL_PTR != pPIN2)
    {
        VOS_MemCpy(pMsg->aucPIN2, pPIN2, SI_PIH_PIN_CODE_LEN);
    }

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PIH_WARNING_LOG("SI_PIH_FdnDisable:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


SI_UINT32 SI_PIH_FdnBdnQuery(MN_CLIENT_ID_T                ClientId,
                                    MN_OPERATION_ID_T               OpId,
                                    SI_PIH_QUERY_TYPE_ENUM_UINT32   QueryType)
{
    SI_PIH_MSG_HEADER_STRU          *pMsg;
    VOS_UINT32                      ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_FdnBdnQuery:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    pMsg = (SI_PIH_MSG_HEADER_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_MSG_HEADER_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PIH_WARNING_LOG("SI_PIH_FdnDisable:WARNING AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;

    if(QueryType == SI_PIH_FDN_QUERY)
    {
        pMsg->ulEventType   = SI_PIH_EVENT_FDN_CNF;
        pMsg->ulMsgName     = SI_PIH_FDN_QUERY_REQ;
    }
    else
    {
        pMsg->ulEventType   = SI_PIH_EVENT_BDN_CNF;
        pMsg->ulMsgName     = SI_PIH_BDN_QUERY_REQ;
    }

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PIH_WARNING_LOG("SI_PIH_FdnDisable:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


SI_UINT32 SI_PIH_GenericAccessReq(MN_CLIENT_ID_T             ClientId,
                                            MN_OPERATION_ID_T           OpId,
                                            SI_PIH_CSIM_COMMAND_STRU    *pstData)
{
    SI_PIH_GACCESS_REQ_STRU         *pMsg;
    VOS_UINT32                      ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_GenericAccessReq:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    if(pstData->ulLen == 0)
    {
        PIH_ERROR_LOG("SI_PIH_GenericAccessReq: Data Len is Error");
        return TAF_FAILURE;
    }

    if((pstData->ulLen > SI_PIH_APDU_HDR_LEN)&&(pstData->aucCommand[4] != pstData->ulLen-SI_PIH_APDU_HDR_LEN))
    {
        PIH_ERROR_LOG("SI_PIH_GenericAccessReq: Data Len is Not Eq P3");
        return TAF_FAILURE;
    }

    pMsg = (SI_PIH_GACCESS_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_GACCESS_REQ_STRU)-VOS_MSG_HEAD_LENGTH+pstData->ulLen);

    if (VOS_NULL_PTR == pMsg)
    {
        PIH_WARNING_LOG("SI_PIH_GenericAccessReq: AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pMsg->stMsgHeader.ulMsgName     = SI_PIH_GACCESS_REQ;
    pMsg->stMsgHeader.usClient      = ClientId;
    pMsg->stMsgHeader.ucOpID        = OpId;
    pMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_GENERIC_ACCESS_CNF;
    pMsg->ulDataLen                 = pstData->ulLen;

    if(0 != pstData->ulLen)
    {
        VOS_MemCpy(pMsg->aucData, pstData->aucCommand, pstData->ulLen);
    }

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PIH_WARNING_LOG("SI_PIH_FdnDisable:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


SI_UINT32 SI_PIH_IsdbAccessReq(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    SI_PIH_ISDB_ACCESS_COMMAND_STRU    *pstData)
{
    SI_PIH_ISDB_ACCESS_REQ_STRU     *pstMsg;
    VOS_UINT32                      ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_IsdbAccessReq:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    if (0 == pstData->ulLen)
    {
        PIH_ERROR_LOG("SI_PIH_IsdbAccessReq: Data Len is Error");

        return TAF_FAILURE;
    }

    pstMsg  = (SI_PIH_ISDB_ACCESS_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT,
                                                   sizeof(SI_PIH_ISDB_ACCESS_REQ_STRU) - VOS_MSG_HEAD_LENGTH + pstData->ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_IsdbAccessReq: AllocMsg FAILED");

        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid   =   ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName       =   SI_PIH_ISDB_ACCESS_REQ;
    pstMsg->stMsgHeader.usClient        =   ClientId;
    pstMsg->stMsgHeader.ucOpID          =   OpId;
    pstMsg->stMsgHeader.ulEventType     =   SI_PIH_EVENT_ISDB_ACCESS_CNF;
    pstMsg->ulDataLen                   =   pstData->ulLen;

    if (0 != pstData->ulLen)
    {
        VOS_MemCpy(pstMsg->aucData, pstData->aucCommand, pstData->ulLen);
    }

    if (VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_IsdbAccessReq:WARNING SendMsg FAILED");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


SI_UINT32 SI_PIH_CchoSetReq(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    SI_PIH_CCHO_COMMAND_STRU           *pstCchoCmd)
{
    SI_PIH_CCHO_SET_REQ_STRU           *pstMsg;
    VOS_UINT32                          ulReceiverPid;

    /* ������� */
    if ((0 == pstCchoCmd->ulAIDLen)
        || ((USIMM_AID_LEN_MAX*2) < pstCchoCmd->ulAIDLen))
    {
        PIH_ERROR_LOG("SI_PIH_CchoSetReq: AID length is incorrect.");

        return TAF_FAILURE;
    }

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_CchoSetReq:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    /* ������Ϣ�ڴ� */
    pstMsg  = (SI_PIH_CCHO_SET_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_CCHO_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_CchoSetReq: AllocMsg FAILED");

        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid   =   ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName       =   SI_PIH_CCHO_SET_REQ;
    pstMsg->stMsgHeader.usClient        =   ClientId;
    pstMsg->stMsgHeader.ucOpID          =   OpId;
    pstMsg->stMsgHeader.ulEventType     =   SI_PIH_EVENT_CCHO_SET_CNF;
    pstMsg->ulAIDLen                    =   pstCchoCmd->ulAIDLen;

    VOS_MemCpy(pstMsg->aucADFName, pstCchoCmd->pucADFName, pstCchoCmd->ulAIDLen);

    if (VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_CchoSetReq:WARNING SendMsg FAILED");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;

}


SI_UINT32 SI_PIH_CchcSetReq(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    VOS_UINT32                          ulSessionID)
{
    SI_PIH_CCHC_SET_REQ_STRU           *pstMsg;
    VOS_UINT32                          ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_CchcSetReq:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    /* ������Ϣ�ڴ� */
    pstMsg  = (SI_PIH_CCHC_SET_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_CCHC_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_CchcSetReq: AllocMsg FAILED");

        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid   =   ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName       =   SI_PIH_CCHC_SET_REQ;
    pstMsg->stMsgHeader.usClient        =   ClientId;
    pstMsg->stMsgHeader.ucOpID          =   OpId;
    pstMsg->stMsgHeader.ulEventType     =   SI_PIH_EVENT_CCHC_SET_CNF;
    pstMsg->ulSessionID                 =   ulSessionID;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_CchcSetReq:WARNING SendMsg FAILED");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;

}


SI_UINT32 SI_PIH_CglaSetReq(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    SI_PIH_CGLA_COMMAND_STRU           *pstData)
{
    SI_PIH_CGLA_REQ_STRU               *pstMsg;
    VOS_UINT32                          ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_CglaSetReq:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    /* ������Ϣ�ڴ� */
    pstMsg  = (SI_PIH_CGLA_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT,
                                                   sizeof(SI_PIH_CGLA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_CglaSetReq: AllocMsg FAILED");

        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid   =   ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName       =   SI_PIH_CGLA_SET_REQ;
    pstMsg->stMsgHeader.usClient        =   ClientId;
    pstMsg->stMsgHeader.ucOpID          =   OpId;
    pstMsg->stMsgHeader.ulEventType     =   SI_PIH_EVENT_CGLA_SET_CNF;
    pstMsg->ulSessionID                 =   pstData->ulSessionID;
    pstMsg->ulDataLen                   =   pstData->ulLen;

    VOS_MemCpy(pstMsg->aucData, pstData->pucCommand, pstData->ulLen);

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_CglaSetReq:WARNING SendMsg FAILED");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


SI_UINT32 SI_PIH_GetCardATRReq(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId)
{
    SI_PIH_MSG_HEADER_STRU             *pstMsg;
    VOS_UINT32                          ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_CchoSetReq:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    /* ������Ϣ�ڴ� */
    pstMsg  = (SI_PIH_MSG_HEADER_STRU *)VOS_AllocMsg(WUEPS_PID_AT,
                                                   sizeof(SI_PIH_MSG_HEADER_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_CglaSetReq: AllocMsg FAILED");

        return TAF_FAILURE;
    }

    pstMsg->ulReceiverPid   =   ulReceiverPid;
    pstMsg->ulMsgName       =   SI_PIH_CARD_ATR_QRY_REQ;
    pstMsg->usClient        =   ClientId;
    pstMsg->ucOpID          =   OpId;
    pstMsg->ulEventType     =   SI_PIH_EVENT_CARD_ATR_QRY_CNF;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_CglaSetReq:WARNING SendMsg FAILED");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

#if (FEATURE_ON == FEATURE_VSIM)

VOS_UINT32 SI_PIH_HvsDHQuery(MN_CLIENT_ID_T             ClientId,
                                     MN_OPERATION_ID_T          OpId)
{
    SI_PIH_HVS_QRY_REQ_STRU            *pstMsg;
    VOS_UINT32                          ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_HvsDHQuery:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    pstMsg = (SI_PIH_HVS_QRY_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_HVS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_HvsDHQuery: AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName     = SI_PIH_HVSDH_QRY_REQ;
    pstMsg->stMsgHeader.usClient      = ClientId;
    pstMsg->stMsgHeader.ucOpID        = OpId;
    pstMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_HVSDH_QRY_CNF;


    if(VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_HvsDHQuery:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


VOS_UINT32 SI_PIH_HvsContQuery(MN_CLIENT_ID_T           ClientId,
                                    MN_OPERATION_ID_T         OpId)
{
    SI_PIH_HVS_QRY_REQ_STRU            *pstMsg;
    VOS_UINT32                          ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_HvsContQuery:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    pstMsg = (SI_PIH_HVS_QRY_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_HVS_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_HvsContQuery: AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName     = SI_PIH_HVSCONT_QRY_REQ;
    pstMsg->stMsgHeader.usClient      = ClientId;
    pstMsg->stMsgHeader.ucOpID        = OpId;
    pstMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_HVSCONT_QUERY_CNF;

    if(VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_HvsContQuery:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;

}


VOS_UINT32 SI_PIH_HvSstQuery(MN_CLIENT_ID_T                 ClientId,
                                    MN_OPERATION_ID_T             OpId)
{
    SI_PIH_MSG_HEADER_STRU *pMsg;
    VOS_UINT32              ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_HvSstQuery:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    pMsg = (SI_PIH_MSG_HEADER_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_MSG_HEADER_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PIH_WARNING_LOG("SI_PIH_HvSstQuery:WARNING AllocMsg FAILED");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;
    pMsg->ulMsgName     = SI_PIH_HVSST_QUERY_REQ;
    pMsg->ulEventType   = SI_PIH_EVENT_HVSST_QUERY_CNF;

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PIH_WARNING_LOG("SI_PIH_HvSstQuery:WARNING SendMsg FAILED");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}



VOS_UINT32 SI_PIH_HvSstSet (MN_CLIENT_ID_T                  ClientId,
                             MN_OPERATION_ID_T                  OpId,
                             SI_PIH_HVSST_SET_STRU              *pstHvSStSet)
{
    SI_PIH_HVSST_REQ_STRU   *pMsg;
    VOS_UINT32               ulReceiverPid;

    if(VOS_NULL_PTR == pstHvSStSet)
    {
        PIH_WARNING_LOG("SI_PIH_HvSstSet:Parameter is Wrong");

        return TAF_FAILURE;
    }

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_HvSstSet:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    pMsg = (SI_PIH_HVSST_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_HVSST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PIH_WARNING_LOG("SI_PIH_HvSstSet:WARNING AllocMsg FAILED");

        return TAF_FAILURE;
    }

    pMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pMsg->stMsgHeader.usClient      = ClientId;
    pMsg->stMsgHeader.ucOpID        = OpId;
    pMsg->stMsgHeader.ulMsgName     = SI_PIH_HVSST_SET_REQ;
    pMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_HVSST_SET_CNF;

    VOS_MemCpy(&pMsg->stHvSSTData, pstHvSStSet, sizeof(SI_PIH_HVSST_SET_STRU));

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PIH_WARNING_LOG("SI_PIH_HvSstSet:WARNING SendMsg FAILED");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


VOS_UINT32 SI_PIH_AtFileWrite(MN_CLIENT_ID_T                  ClientId,
                                    MN_OPERATION_ID_T               OpId,
                                    SI_PIH_FILEWRITE_DATA_STRU     *pstData)
{
    SI_PIH_FILE_WRITE_REQ_STRU     *pstMsg;
    VOS_UINT32                      ulMsgLen;

    VOS_UINT32                      ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_AtFileWrite:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    if(VOS_NULL_PTR == pstData)
    {
        PIH_WARNING_LOG("SI_PIH_AtFileWrite:Para Check Error");

        return TAF_FAILURE;
    }

    if((VOS_NULL_PTR == pstData->stFileData.pucData)
        ||(VOS_NULL == pstData->stFileData.ulDataLen)
        ||(VOS_NULL_PTR == pstData->stFileName.pucData)
        ||(VOS_NULL == pstData->stFileName.ulDataLen))
    {
        PIH_WARNING_LOG("SI_PIH_AtFileWrite:Para File Data Check Error");

        return TAF_FAILURE;
    }

    /* ����SI_PIH_FILE_WRITE_REQ_STRU��aucData�ֶζ��࣬��Ҫ��ȥsizeof(VOS_UINT32) */
    ulMsgLen = (sizeof(SI_PIH_FILE_WRITE_REQ_STRU) - VOS_MSG_HEAD_LENGTH)- sizeof(VOS_UINT32)+ pstData->stFileData.ulDataLen;

    pstMsg = (SI_PIH_FILE_WRITE_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_AtFileWrite:WARNING AllocMsg FAILED");

        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName     = SI_PIH_FILE_WRITE_REQ;
    pstMsg->stMsgHeader.usClient      = ClientId;
    pstMsg->stMsgHeader.ucOpID        = OpId;
    pstMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_FILE_WRITE_CNF;

    /*��Ϣ����*/
    pstMsg->ucIndex         = (VOS_UINT8)pstData->ulIndex;
    pstMsg->ucRef           = (VOS_UINT8)pstData->ulRef;
    pstMsg->ucTotalNum      = (VOS_UINT8)pstData->ulTotalNum;
    pstMsg->ulFileDataLen   = pstData->stFileData.ulDataLen;
    pstMsg->ucFileNameLen   = (VOS_UINT8)pstData->stFileName.ulDataLen;
#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
    pstMsg->enVsimIndex   = pstData->enVsimIndex;
#endif/*end (FEATURE_ON == MBB_FEATURE_VSIM_HUK)*/

    VOS_MemCpy(pstMsg->aucFileName, pstData->stFileName.pucData, pstData->stFileName.ulDataLen);

    VOS_MemCpy(pstMsg->aucFileData, pstData->stFileData.pucData, pstData->stFileData.ulDataLen);

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_AtFileWrite:WARNING SendMsg FAILED");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)

VOS_UINT32 SI_PIH_HvsDHSet(MN_CLIENT_ID_T ClientId, 
                                    MN_OPERATION_ID_T OpId, 
                                    SI_PIH_SIM_INDEX_ENUM_UINT8 enVsimIndex)
{
    SI_PIH_HVSDH_SET_REQ_STRU          *pstMsg;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_HvsDHSet:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    ulMsgLen = sizeof(SI_PIH_HVSDH_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH ;

    pstMsg = (SI_PIH_HVSDH_SET_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_AT, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_HvsDHSet: AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName     = SI_PIH_HVSDH_SET_REQ;
    pstMsg->stMsgHeader.usClient      = ClientId;
    pstMsg->stMsgHeader.ucOpID        = OpId;
    pstMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_HVSDH_SET_CNF;
    pstMsg->enVsimIndex               = enVsimIndex;

    if(VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_HvsDHSet:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


VOS_UINT32 SI_PIH_HvsContSet(MN_CLIENT_ID_T ClientId, 
                            MN_OPERATION_ID_T OpId, 
                            SI_PIH_SIM_INDEX_ENUM_UINT8 enVsimIndex)
{
    SI_PIH_HVSCONT_SET_REQ_STRU         *pstMsg;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_HvsContSet:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    ulMsgLen = sizeof(SI_PIH_HVSCONT_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH ;

    pstMsg = (SI_PIH_HVSCONT_SET_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_AT, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_HvsContSet: AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName     = SI_PIH_HVSCONT_SET_REQ;
    pstMsg->stMsgHeader.usClient      = ClientId;
    pstMsg->stMsgHeader.ucOpID        = OpId;
    pstMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_HVSCONT_SET_CNF;
    pstMsg->enVsimIndex               = enVsimIndex;

    if(VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_HvsContSet:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


VOS_UINT32 SI_PIH_HvAdhSet ( MN_CLIENT_ID_T                  ClientId,
                             MN_OPERATION_ID_T                  OpId,
                                 SI_PIH_HVADH_SET_STRU *pstHvAdhSet)
{
    SI_PIH_HVADH_REQ_STRU   *pMsg = VOS_NULL;
    VOS_UINT32               ulReceiverPid;

    if(VOS_NULL_PTR == pstHvAdhSet)
    {
        PIH_WARNING_LOG("SI_PIH_HvAdhSet:Parameter is Wrong");
        return TAF_FAILURE;
    }

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_HvAdhSet:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    pMsg = (SI_PIH_HVADH_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, 
                    sizeof(SI_PIH_HVADH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PIH_WARNING_LOG("SI_PIH_HvAdhSet:WARNING AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pMsg->stMsgHeader.usClient      = ClientId;
    pMsg->stMsgHeader.ucOpID        = OpId;
    pMsg->stMsgHeader.ulMsgName     = SI_PIH_HVADH_SET_REQ;
    pMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_HVADH_SET_CNF;

    VOS_MemCpy(&(pMsg->stHvADHData), pstHvAdhSet, sizeof(SI_PIH_HVADH_SET_STRU));

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PIH_WARNING_LOG("SI_PIH_HvAdhSet:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

VOS_UINT32 SI_PIH_HvshDHSet(MN_CLIENT_ID_T ClientId,
                            MN_OPERATION_ID_T OpId,
                            SI_PIH_KEY_INDEX_ENUM_UINT8 enKeyIndex)
{
    SI_PIH_HVSDH_SET_REQ_STRU          *pstMsg;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_HvshDHSet:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    ulMsgLen = sizeof(SI_PIH_HVSDH_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH ;

    pstMsg = (SI_PIH_HVSDH_SET_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_AT, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_HvshDHSet: AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName     = SI_PIH_HVSHDH_SET_REQ;
    pstMsg->stMsgHeader.usClient      = ClientId;
    pstMsg->stMsgHeader.ucOpID        = OpId;
    pstMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_HVSHDH_SET_CNF;
    pstMsg->enVsimIndex               = enKeyIndex;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_HvshDHSet:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;

}

VOS_UINT32 SI_PIH_HvdieIDQuery(MN_CLIENT_ID_T ClientId,
                            MN_OPERATION_ID_T OpId)
{
    SI_PIH_MSG_HEADER_STRU          *pMsg;
    VOS_UINT32                      ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_HvdieIDQuery:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    pMsg = (SI_PIH_MSG_HEADER_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_MSG_HEADER_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PIH_WARNING_LOG("SI_PIH_HvdieIDQuery:WARNING AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->usClient        = ClientId;
    pMsg->ucOpID        = OpId;
    pMsg->ulMsgName     = SI_PIH_HVDIEID_QRY_REQ;
    pMsg->ulEventType    = SI_PIH_EVENT_HVDIEID_QRY_CNF;

    if (VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PIH_WARNING_LOG("SI_PIH_HvdieIDQuery:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;

}


VOS_UINT32 SI_PIH_HvdDHSet(MN_CLIENT_ID_T ClientId, 
                            MN_OPERATION_ID_T OpId, 
                            SI_PIH_CLEAN_KEY_INDEX_ENUM_UINT8 enCleanKeyType)
{
    SI_PIH_HVDDH_SET_REQ_STRU          *pstMsg;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_HvdDHSet:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    ulMsgLen = sizeof(SI_PIH_HVDDH_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH ;

    pstMsg = (SI_PIH_HVDDH_SET_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_AT, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_HvdDHSet: AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName     = SI_PIH_HVDDH_SET_REQ;
    pstMsg->stMsgHeader.usClient      = ClientId;
    pstMsg->stMsgHeader.ucOpID        = OpId;
    pstMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_HVDDH_SET_CNF;
    pstMsg->enCleanKeyType              = enCleanKeyType;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_HvdDHSet:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;

}
#else


VOS_UINT32 SI_PIH_HvsDHSet(MN_CLIENT_ID_T                ClientId,
                                    MN_OPERATION_ID_T           OpId,
                                    VSIM_KEYDATA_STRU           *pstSKey)
{
    SI_PIH_HVSDH_SET_REQ_STRU          *pstMsg;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulReceiverPid;

    /* ������� */
    if(VOS_NULL_PTR == pstSKey)
    {
        PIH_ERROR_LOG("SI_PIH_HvsDHSet: Para is Error");
        return TAF_FAILURE;
    }

    if ((VOS_NULL == pstSKey->ulKeyLen) || (VSIM_KEYLEN_MAX < pstSKey->ulKeyLen))
    {
        PIH_ERROR_LOG("SI_PIH_HvsDHSet: Data Len is Error");
        return TAF_FAILURE;
    }

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_HvsDHSet:Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    /* ����SI_PIH_HVSDH_SET_REQ_STRU��aucData�ֶζ��࣬��Ҫ��ȥsizeof(VOS_UINT32) */
    ulMsgLen = sizeof(SI_PIH_HVSDH_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH - sizeof(VOS_UINT32) + pstSKey->ulKeyLen;

    pstMsg = (SI_PIH_HVSDH_SET_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_AT, ulMsgLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_HvsDHSet: AllocMsg FAILED");
        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName     = SI_PIH_HVSDH_SET_REQ;
    pstMsg->stMsgHeader.usClient      = ClientId;
    pstMsg->stMsgHeader.ucOpID        = OpId;
    pstMsg->stMsgHeader.ulEventType   = SI_PIH_EVENT_HVSDH_SET_CNF;
    pstMsg->ulDataLen                 = pstSKey->ulKeyLen;

    VOS_MemCpy(pstMsg->aucData, pstSKey->aucKey, pstSKey->ulKeyLen);

    if(VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_HvsDHSet:WARNING SendMsg FAILED");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}
#endif/*end (FEATURE_ON == MBB_FEATURE_VSIM_HUK)*/
#endif  /*end of (FEATURE_VSIM == FEATURE_ON)*/

#if (FEATURE_ON == FEATURE_IMS)

VOS_UINT32 SI_PIH_UiccAuthReq(MN_CLIENT_ID_T                ClientId,
                                    MN_OPERATION_ID_T               OpId,
                                    SI_PIH_UICCAUTH_STRU            *pstData)
{
    SI_PIH_UICCAUTH_REQ_STRU        *pstMsg;
    VOS_UINT32                      ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_UiccAuthReq:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    if (VOS_NULL_PTR == pstData)
    {
        PIH_WARNING_LOG("SI_PIH_UiccAuthReq:Para Check Error");

        return TAF_FAILURE;
    }

    /* ������Ϣ�ڴ� */
    pstMsg  = (SI_PIH_UICCAUTH_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_UICCAUTH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_UiccAuthReq: AllocMsg FAILED");

        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid   =   ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName       =   SI_PIH_UICCAUTH_REQ;
    pstMsg->stMsgHeader.usClient        =   ClientId;
    pstMsg->stMsgHeader.ucOpID          =   OpId;
    pstMsg->stMsgHeader.ulEventType     =   SI_PIH_EVENT_UICCAUTH_CNF;

    VOS_MemCpy(&pstMsg->stAuthData, pstData, sizeof(SI_PIH_UICCAUTH_STRU));

    if (VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_UiccAuthReq:WARNING SendMsg FAILED");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}


VOS_UINT32 SI_PIH_AccessUICCFileReq(MN_CLIENT_ID_T       ClientId,
                                    MN_OPERATION_ID_T               OpId,
                                    SI_PIH_ACCESSFILE_STRU          *pstData)
{
    SI_PIH_ACCESSFILE_REQ_STRU      *pstMsg;
    VOS_UINT32                      ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_AccessUICCFileReq:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    if (VOS_NULL_PTR == pstData)
    {
        PIH_WARNING_LOG("SI_PIH_AccessUICCFileReq:Para Check Error");

        return TAF_FAILURE;
    }

    /* ������Ϣ�ڴ� */
    pstMsg  = (SI_PIH_ACCESSFILE_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_ACCESSFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PIH_WARNING_LOG("SI_PIH_AccessUICCFileReq: AllocMsg FAILED");

        return TAF_FAILURE;
    }

    pstMsg->stMsgHeader.ulReceiverPid   =   ulReceiverPid;
    pstMsg->stMsgHeader.ulMsgName       =   SI_PIH_URSM_REQ;
    pstMsg->stMsgHeader.usClient        =   ClientId;
    pstMsg->stMsgHeader.ucOpID          =   OpId;
    pstMsg->stMsgHeader.ulEventType     =   SI_PIH_EVENT_URSM_CNF;

    VOS_MemCpy(&pstMsg->stCmdData, pstData, sizeof(SI_PIH_ACCESSFILE_STRU));

    if (VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pstMsg))
    {
        PIH_WARNING_LOG("SI_PIH_AccessUICCFileReq:WARNING SendMsg FAILED");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}
#endif



VOS_UINT32 SI_PIH_CardTypeQuery(MN_CLIENT_ID_T       ClientId,
                                               MN_OPERATION_ID_T    OpId)
{
    SI_PIH_MSG_HEADER_STRU *pMsg;
    VOS_UINT32              ulReceiverPid;

    if (VOS_OK != SI_PIH_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PIH_ERROR_LOG("SI_PIH_CardTypeQuery: Get ulReceiverPid Error.");
        return TAF_FAILURE;
    }

    pMsg = (SI_PIH_MSG_HEADER_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PIH_MSG_HEADER_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PIH_WARNING_LOG("SI_PIH_CardTypeQuery: WARNING AllocMsg FAILED");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;
    pMsg->ulMsgName     = SI_PIH_CARDTYPE_QUERY_REQ;
    pMsg->ulEventType   = SI_PIH_EVENT_CARDTYPE_QUERY_CNF;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PIH_WARNING_LOG("SI_PIH_CardTypeQuery: WARNING SendMsg FAILED");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

#endif

#if  ((OSA_CPU_CCPU == VOS_OSA_CPU) || (defined(DMT)))


VOS_VOID SI_PIH_ChangePollTimer(SI_PIH_TIMER_NAME_ENUM_UINT32      enTimerName,
                                        SI_PIH_POLLTIMER_STATE_ENUM_UINT32  enState,
                                        VOS_UINT32                          ulTimerLen,
                                        USIMM_POLL_FCP_ENUM_UINT32          enData)
{
    g_stPIHPollTime[enTimerName].enPollState = enState; /*���¶�ʱ��״̬*/
    g_stPIHPollTime[enTimerName].enPollData  = enData;  /*�����Ƿ���Ҫ�ظ����ݣ�������Status������*/

    if (SI_PIH_TIMER_LEN_NO_CHANGE != ulTimerLen)       /*�����Ҫ�޸Ķ�ʱ��ʱ��*/
    {
        g_stPIHPollTime[enTimerName].ulTimeLen   = ulTimerLen;
    }

    SI_PIH_PollTimerPro(&g_stPIHPollTime[enTimerName]); /*����ʱ��*/

    return;
}



VOS_UINT32 SI_PIH_RegisterPID(VOS_UINT32 ulRegPID, VOS_UINT32 ulRegListNum, VOS_UINT32 *pulRegList)
{
    VOS_UINT32                          i;

    for (i = 0; i < ulRegListNum; i++)
    {
        if (ulRegPID == pulRegList[i])  /*�Ѿ�ע�᲻���ظ�д��*/
        {
            return VOS_OK;
        }
    }

    for (i = 0; i < ulRegListNum; i++)
    {
        if (VOS_NULL == pulRegList[i])  /*��ѯ��λ��*/
        {
            pulRegList[i] = ulRegPID;

            return VOS_OK;
        }
    }

    return VOS_ERR;
}


VOS_UINT32 PIH_RegUsimCardStatusIndMsg(VOS_UINT32 ulRegPID)
{
    VOS_UINT32              ulResult;

    if (VOS_TRUE != VOS_CheckPSPidValidity(ulRegPID))
    {
        PIH_WARNING_LOG("PIH_RegUsimCardStatusIndMsg: PID is Error");

        return VOS_ERR;
    }

    if (VOS_OK != VOS_TaskLock())
    {
        PIH_WARNING_LOG("PIH_RegUsimCardStatusIndMsg: VOS_TaskLock Error");

        return VOS_ERR;
    }

    ulResult = SI_PIH_RegisterPID(ulRegPID, SI_PIH_BCPID_REG_MAX, g_aulPIHUsimBCPid);

    if (VOS_OK != ulResult)
    {
        PIH_WARNING_LOG("PIH_RegUsimCardStatusIndMsg: Space is Full");
    }

    VOS_TaskUnlock();

    return ulResult;
}


VOS_UINT32 PIH_DeregUsimCardStatusIndMsg(VOS_UINT32 ulRegPID)
{
    VOS_UINT32                          i;

    if (VOS_OK != VOS_TaskLock())
    {
        PIH_WARNING_LOG("PIH_RegUsimCardStatusIndMsg: SmP Error");

        return VOS_ERR;
    }

    for (i = 0; i < SI_PIH_BCPID_REG_MAX; i++)
    {
        if (ulRegPID == g_aulPIHUsimBCPid[i])
        {
            g_aulPIHUsimBCPid[i] = VOS_NULL;

            VOS_TaskUnlock();

            return VOS_OK;
        }
    }

    VOS_TaskUnlock();

    return VOS_ERR;
}


VOS_UINT32 PIH_RegCardRefreshIndMsg(VOS_UINT32 ulRegPID)
{
    VOS_UINT32                          ulResult;

    if (VOS_TRUE != VOS_CheckPSPidValidity(ulRegPID))
    {
        PIH_WARNING_LOG("PIH_RegUsimCardStatusIndMsg: PID is Error");

        return VOS_ERR;
    }

    if (VOS_OK != VOS_TaskLock())
    {
        PIH_WARNING_LOG("PIH_RegUsimCardStatusIndMsg: SmP Error");

        return VOS_ERR;
    }

    ulResult = SI_PIH_RegisterPID(ulRegPID, SI_PIH_BCPID_REG_MAX, g_aulPIHRefreshBCPid);

    if (VOS_OK != ulResult)
    {
        PIH_WARNING_LOG("PIH_RegUsimCardStatusIndMsg: Space is Full");
    }

    VOS_TaskUnlock();

    return ulResult;
}


VOS_UINT32 PIH_DeregCardRefreshIndMsg(VOS_UINT32 ulRegPID)
{
    VOS_UINT32                          i;

    if (VOS_OK != VOS_TaskLock())
    {
        PIH_WARNING_LOG("PIH_RegUsimCardStatusIndMsg: SmP Error");

        return VOS_ERR;
    }

    for (i = 0; i<SI_PIH_BCPID_REG_MAX; i++)
    {
        if (ulRegPID == g_aulPIHRefreshBCPid[i])
        {
            g_aulPIHRefreshBCPid[i] = VOS_NULL;

            VOS_TaskUnlock();

            return VOS_OK;
        }
    }

    VOS_TaskUnlock();

    return VOS_ERR;
}


VOS_UINT32 PIH_RegISIMCardIndMsg(VOS_UINT32 ulRegPID)
{
    VOS_UINT32                          ulResult;

    if (VOS_TRUE != VOS_CheckPSPidValidity(ulRegPID))
    {
        PIH_WARNING_LOG("PIH_RegISIMCardIndMsg: PID is Error");

        return VOS_ERR;
    }

    if (VOS_OK != VOS_TaskLock())
    {
        PIH_WARNING_LOG("PIH_RegISIMCardIndMsg: SmP Error");

        return VOS_ERR;
    }

    ulResult = SI_PIH_RegisterPID(ulRegPID, SI_PIH_BCPID_REG_MAX, g_aulPIHISIMBCPid);

    if (VOS_OK != ulResult)
    {
        PIH_WARNING_LOG("PIH_RegISIMCardIndMsg: Space is Full");
    }

    VOS_TaskUnlock();

    return ulResult;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





