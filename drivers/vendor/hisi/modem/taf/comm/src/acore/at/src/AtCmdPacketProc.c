


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AtCmdPacketProc.h"
#include "AtDataProc.h"

#include "product_config.h"
#if (FEATURE_ON == MBB_WPG_COMMON)
#include "MbbAtGuComm.h"
#include "MbbPsCsCommon.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_PACKET_PROC_C
/*lint +e767*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef BSP_CONFIG_BOARD_K5160
extern AT_USER_TYPE                           g_stAtNdisUserType;
extern VOS_UINT8                              g_stAtNdisCid;
#endif/*BSP_CONFIG_BOARD_K5160*/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-27, begin */

AT_APP_CONN_STATE_ENUM_U32 AT_AppConvertPdpStateToConnStatus(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_APP_CONN_STATE_ENUM_U32          enConnStatus;

    switch (enPdpState)
    {
        case AT_PDP_STATE_ACTING:
            enConnStatus = AT_APP_DIALING;
            break;

        case AT_PDP_STATE_ACTED:
        case AT_PDP_STATE_DEACTING:
            enConnStatus = AT_APP_DIALED;
            break;

        case AT_PDP_STATE_IDLE:
        default:
            enConnStatus = AT_APP_UNDIALED;
            break;
    }

    return enConnStatus;
}


VOS_UINT32 AT_SetChdataPara_AppUser(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucCid;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    RNIC_RM_NET_ID_ENUM_UINT8           enRnicRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* ָ��CID��PDP���Ѿ����������ɾ�����޸ĸ�CID��ͨ��ӳ���ϵ��ֱ�ӷ���ERROR */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
      && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulRmNetActFlg))
    {
        return AT_ERROR;
    }

    /* �ڶ�������Ϊ�գ����ʾɾ�����ù�ϵ */
    if (0 == gastAtParaList[1].usParaLen)
    {
        pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_FALSE;
        pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = AT_PS_INVALID_RMNET_ID;
        return AT_OK;
    }

    enDataChannelId = gastAtParaList[1].ulParaValue;

    /* ��ȡ����ID */
    ulRslt = AT_PS_GetRnicRmNetIdFromChDataValue(ucIndex, enDataChannelId, &enRnicRmNetId);

    if (VOS_OK != ulRslt)
    {
        return AT_ERROR;
    }

    /* �����Ƿ��в�ͬ��<CID>��������ͬ��<enRnicRmNetId> */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (ucLoop != ucCid)
          && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (enRnicRmNetId == (RNIC_RM_NET_ID_ENUM_UINT8)pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId)
#if ((defined(BSP_CONFIG_BOARD_WINGLE_MS2172S_818) && (FEATURE_OFF == MBB_FEATURE_BOX_FTEN)) \
      || defined(BSP_CONFIG_BOARD_MS2372H))
          && (UDI_INVALID_HANDLE == pstPsModemCtx->astChannelCfg[ucLoop].ulHandle)
#endif
           )
        {
            /* ��ͬ��<CID>��������ͬ��<enRnicRmNetId>��ֱ�ӷ���ERROR */
            return AT_ERROR;
        }
    }

    /* ��������ͨ��ӳ��� */
    pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_TRUE;
    pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = enRnicRmNetId;

    return AT_OK;
}


VOS_UINT32 AT_SetChdataPara_HsicUser(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucCid;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    UDI_DEVICE_ID                       enUdiDevId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* ָ��CID��PDP���Ѿ����������ɾ�����޸ĸ�CID��ͨ��ӳ���ϵ��ֱ�ӷ���ERROR */
    if ((VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulUsed)
      && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucCid].ulRmNetActFlg))
    {
        return AT_ERROR;
    }

    /* �ڶ�������Ϊ�գ����ʾɾ�����ù�ϵ */
    if (0 == gastAtParaList[1].usParaLen)
    {
        pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_FALSE;
        pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = UDI_INVAL_DEV_ID;
        return AT_OK;
    }

    enDataChannelId = gastAtParaList[1].ulParaValue;

    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, begin */
    /* ����ӿڷ���ֵ�޸ģ�֮ǰ����PS_TRUE��ΪSUPPORT */
    if (BSP_MODULE_SUPPORT == DRV_USB_HSIC_SUPPORT_NCM())
    {
        if (AT_CH_DATA_CHANNEL_ID_1 == enDataChannelId)
        {
            enUdiDevId = UDI_NCM_HSIC_NCM0_ID;
        }
        else if(AT_CH_DATA_CHANNEL_ID_2 == enDataChannelId)
        {
            enUdiDevId = UDI_NCM_HSIC_NCM1_ID;
        }
        else
        {
            enUdiDevId = UDI_NCM_HSIC_NCM2_ID;
        }
    }
    else
    {
        if (AT_CH_DATA_CHANNEL_ID_1 == enDataChannelId)
        {
            enUdiDevId = UDI_ACM_HSIC_ACM1_ID;
        }
        else if(AT_CH_DATA_CHANNEL_ID_2 == enDataChannelId)
        {
            enUdiDevId = UDI_ACM_HSIC_ACM3_ID;
        }
        else
        {
            enUdiDevId = UDI_ACM_HSIC_ACM5_ID;
        }
    }
    /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, end */

    /* �����Ƿ��в�ͬ��<CID>��������ͬ��<enUdiDevId> */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (ucLoop != ucCid)
          && (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (enUdiDevId == (UDI_DEVICE_ID)pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId))
        {
            /* ��ͬ��<CID>��������ͬ��<enUdiDevId>��ֱ�ӷ���ERROR */
            return AT_ERROR;
        }
    }

    /* ��������ͨ��ӳ��� */
    pstPsModemCtx->astChannelCfg[ucCid].ulUsed     = VOS_TRUE;
    pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId  = enUdiDevId;

    return AT_OK;
}


VOS_UINT32 AT_SetChdataPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usClientId;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 2)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��һ������Ϊ�� */
    if ((0 == gastAtParaList[0].usParaLen))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* PCUI����������PCUI��ģ��NDISDUP���� */
    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcuiPsCallFlag())
        {
            usClientId = AT_GetPcuiUserClientId();

            /* HSIC��MUXͨ���Ĵ��� */
            if (VOS_TRUE == AT_IsHsicOrMuxUser((VOS_UINT8)usClientId))
            {
                return AT_SetChdataPara_HsicUser((VOS_UINT8)usClientId);
            }

            /* APPͨ���Ĵ��� */
            if (VOS_TRUE == AT_CheckAppUser((VOS_UINT8)usClientId))
            {
                return AT_SetChdataPara_AppUser((VOS_UINT8)usClientId);
            }
        }
    }

    /* CTRL����������CTRL��ģ��NDISDUP���� */
    if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetCtrlPsCallFlag())
        {
            usClientId = AT_GetCtrlUserClientId();

            /* HSIC��MUXͨ���Ĵ��� */
            if (VOS_TRUE == AT_IsHsicOrMuxUser((VOS_UINT8)usClientId))
            {
                return AT_SetChdataPara_HsicUser((VOS_UINT8)usClientId);
            }

            /* APPͨ���Ĵ��� */
            if (VOS_TRUE == AT_CheckAppUser((VOS_UINT8)usClientId))
            {
                return AT_SetChdataPara_AppUser((VOS_UINT8)usClientId);
            }
        }
    }

    /* HSIC��MUXͨ���Ĵ��� */
    if (VOS_TRUE == AT_IsHsicOrMuxUser(ucIndex))
    {
        return AT_SetChdataPara_HsicUser(ucIndex);
    }

    /* APPͨ���Ĵ��� */
    if (VOS_TRUE == AT_CheckAppUser(ucIndex))
    {
        return AT_SetChdataPara_AppUser(ucIndex);
    }

    return AT_ERROR;
}


VOS_UINT32 AT_QryChdataPara_AppUser(TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucNum;
    VOS_UINT16                          usLength;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    ucNum    = 0;
    usLength = 0;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* ������ */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (AT_PS_INVALID_RMNET_ID != pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId) )
        {
            if (0 != ucNum)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
            }

            /* ^CHDATA:  */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"^CHDATA: ");

            /* <cid> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d", ucLoop);

            /* <datachannel> */
            ulRslt = AT_PS_GetChDataValueFromRnicRmNetId((RNIC_RM_NET_ID_ENUM_UINT8)(pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId), &enDataChannelId);

            if (VOS_OK != ulRslt)
            {
                return AT_ERROR;
            }

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,",%d", enDataChannelId);

            ucNum++;
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryChdataPara_HsicUser(TAF_UINT8 ucIndex)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucNum;
    VOS_UINT16                          usLength;
    AT_CH_DATA_CHANNEL_ENUM_UINT32      enDataChannelId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;

    ucNum    = 0;
    usLength = 0;

    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    /* ������ */
    for (ucLoop = 1; ucLoop <= TAF_MAX_CID; ucLoop++)
    {
        if ( (VOS_TRUE == pstPsModemCtx->astChannelCfg[ucLoop].ulUsed)
          && (UDI_INVAL_DEV_ID != pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId) )
        {
            if (0 != ucNum)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
            }

            /* ^CHDATA:  */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"^CHDATA: ");

            /* <cid> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d", ucLoop);

            /* <datachannel> */
            /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, begin */
            switch ( pstPsModemCtx->astChannelCfg[ucLoop].ulRmNetId)
            {
                case UDI_ACM_HSIC_ACM1_ID:
                case UDI_NCM_HSIC_NCM0_ID:
                    enDataChannelId = AT_CH_DATA_CHANNEL_ID_1;
                    break;
                case UDI_ACM_HSIC_ACM3_ID:
                case UDI_NCM_HSIC_NCM1_ID:
                    enDataChannelId = AT_CH_DATA_CHANNEL_ID_2;
                    break;
                case UDI_ACM_HSIC_ACM5_ID:
                case UDI_NCM_HSIC_NCM2_ID:
                    enDataChannelId = AT_CH_DATA_CHANNEL_ID_3;
                    break;
                default:
                    return AT_ERROR;
            }
            /* Modified by L47619 for C52 HSIC ACM->NCM Project, 2012/09/06, end */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR*)pgucAtSndCodeAddr,(VOS_CHAR*)pgucAtSndCodeAddr + usLength,",%d", enDataChannelId);

            ucNum++;
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryChdataPara(TAF_UINT8 ucIndex)
{
    VOS_UINT16                          usClientId;

    /*����״̬���ͼ��*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* PCUI����������PCUI��ģ��NDISDUP���� */
    if (AT_USBCOM_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetPcuiPsCallFlag())
        {
            usClientId = AT_GetPcuiUserClientId();

            /* APPͨ���Ĵ��� */
            if (VOS_TRUE == AT_CheckAppUser((VOS_UINT8)usClientId))
            {
                return AT_QryChdataPara_AppUser((VOS_UINT8)usClientId);
            }

            /* HSIC��MUXͨ���Ĵ��� */
            if (VOS_TRUE == AT_IsHsicOrMuxUser((VOS_UINT8)usClientId))
            {
                return AT_QryChdataPara_HsicUser((VOS_UINT8)usClientId);
            }
        }
    }

    /* CTRL����������CTRL��ģ��NDISDUP���� */
    if (AT_CTR_USER == gastAtClientTab[ucIndex].UserType)
    {
        if (VOS_TRUE == AT_GetCtrlPsCallFlag())
        {
            usClientId = AT_GetCtrlUserClientId();

            /* APPͨ���Ĵ��� */
            if (VOS_TRUE == AT_CheckAppUser((VOS_UINT8)usClientId))
            {
                return AT_QryChdataPara_AppUser((VOS_UINT8)usClientId);
            }

            /* HSIC��MUXͨ���Ĵ��� */
            if (VOS_TRUE == AT_IsHsicOrMuxUser((VOS_UINT8)usClientId))
            {
                return AT_QryChdataPara_HsicUser((VOS_UINT8)usClientId);
            }
        }
    }

    /* APPͨ���Ĵ��� */
    if (VOS_TRUE == AT_CheckAppUser(ucIndex))
    {
        return AT_QryChdataPara_AppUser(ucIndex);
    }

    /* HSIC��MUXͨ���Ĵ��� */
    if (VOS_TRUE == AT_IsHsicOrMuxUser(ucIndex))
    {
        return AT_QryChdataPara_HsicUser(ucIndex);
    }

    return AT_ERROR;
}


VOS_UINT32 AT_TestChdataPara(VOS_UINT8 ucIndex)
{
    /* Modified by l60609 for AP������Ŀ ��2012-09-10 Begin */
    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }
    /* Modified by l60609 for AP������Ŀ ��2012-09-10 End */

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: %s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       CHDATA_TEST_CMD_PARA_STRING);

    return AT_OK;
}


VOS_UINT32 AT_PS_ReportDhcp(VOS_UINT8 ucIndex)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    VOS_UINT8                           ucCallId;
    AT_DHCP_PARA_STRU                   stDhcpConfig;

    usLength = 0;
    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);
    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportDhcp:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    if (AT_PDP_STATE_ACTED != pstCallEntity->enIpv4State)
    {
        AT_WARN_LOG("AT_PS_ReportDhcp: PDP is not actived.");
        return AT_ERROR;
    }

    /* ��ȡ�������۴���*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("AT_PS_ReportDhcp: ERROR : AT_GetDisplayRate Error!");
    }

    /* ��ȡDHCP����(������) */
    AT_GetDhcpPara(&stDhcpConfig, &pstCallEntity->stIpv4DhcpInfo);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulIPAddr);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSubNetMask);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulPrimDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSndDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d,",ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d",ulSpeed);

#ifdef BSP_CONFIG_BOARD_K5160
    if ( AT_USBCOM_USER == g_stAtNdisUserType )
    {
       usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, 
               (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%d", g_stAtNdisCid);
    }
#endif/*BSP_CONFIG_BOARD_K5160*/

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 At_SetDhcpPara(VOS_UINT8 ucIndex)
{
    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ѯָ��CID��ʵ��PDP������ */
    return AT_PS_ReportDhcp(ucIndex);
}


VOS_UINT32 At_QryDhcpPara_AppUser(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_WPG_COMMON)
    return AT_PS_ReportDefaultDhcp(ucIndex);
#else
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    AT_DHCP_PARA_STRU                   stDhcpConfig;

    usLength         = 0;
    pstAppPdpEntity  = AT_APP_GetPdpEntInfoAddr();
    ulPdpActingFlg   = AT_AppCheckIpv4PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_AppCheckIpv4PdpState(AT_PDP_STATE_DEACTING);

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ((AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4State)
       && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State)))
    {
        AT_WARN_LOG("At_QryDhcpPara_AppUser: PDP is not active for APP.");
        return AT_ERROR;
    }

    /* ��ȡ�������۴���*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("At_QryDhcpPara_AppUser: ERROR : AT_GetDisplayRate Error!");
    }

    /* ��ȡDHCP����(������) */
    AT_GetDhcpPara(&stDhcpConfig, &pstAppPdpEntity->stIpv4Dhcp);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulIPAddr);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSubNetMask);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulPrimDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%08X,",stDhcpConfig.stDhcpCfg.ulSndDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d,",ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d",ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
#endif
}


VOS_UINT32 At_QryDhcpPara_NdisUser(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_FEATURE_MPDP)
    return AT_PS_ReportDefaultDhcp(ucIndex);
#else
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    AT_DHCP_PARA_STRU                   stDhcpConfig;

    /* Modified by S62952 for IPV6, 2011-04-19, begin */
    ulPdpActingFlg      = AT_NdisCheckIpv4PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg    = AT_NdisCheckIpv4PdpState(AT_PDP_STATE_DEACTING);
    usLength            = 0;

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ((AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
       && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State)))
    {
        AT_WARN_LOG("At_QryDhcpPara_NdisUser AT_NdisGetState:");
        return AT_ERROR;
    }

    /* ��ȡ�������۴���*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_ERR_LOG("At_QryDhcpPara_NdisUser : ERROR : AT_GetDisplayRate Error!");
    }

    /* ��ȡDHCP����(������) */
    AT_NdisGetDhcpPara(&stDhcpConfig);

    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulIPAddr);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulSubNetMask);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulGateWay);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulPrimDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%X,",stDhcpConfig.stDhcpCfg.ulSndDNS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d,",ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,"%d",ulSpeed);
    /* Modified by S62952 for IPV6, 2011-04-19, end */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
#endif
}


AT_USER_TYPE AT_PS_GetDailPortUsrType(AT_USER_TYPE enUsrType)
{
    VOS_UINT8                          *pucSystemAppConfig = VOS_NULL_PTR;
    AT_USER_TYPE                        enExpUsrType;

    pucSystemAppConfig = AT_GetSystemAppConfigAddr();
    enExpUsrType       = enUsrType;

    if (AT_USBCOM_USER == enUsrType)
    {
        switch (*pucSystemAppConfig)
        {
            case SYSTEM_APP_MP:
                enExpUsrType = AT_NDIS_USER;
                break;

            case SYSTEM_APP_WEBUI:
                enExpUsrType = AT_APP_USER;
                break;

            default:
                break;
        }
    }

    return enExpUsrType;
}


VOS_UINT32 At_QryDhcpPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    AT_USER_TYPE                        enUsrType;

    ulResult  = AT_OK;

    enUsrType = AT_PS_GetDailPortUsrType(gastAtClientTab[ucIndex].UserType);

    switch (enUsrType)
    {
        case AT_NDIS_USER:
            ulResult = At_QryDhcpPara_NdisUser(ucIndex);
            break;

        case AT_APP_USER:
            ulResult = At_QryDhcpPara_AppUser(ucIndex);
            break;

        default:
            break;
    }

    return ulResult;
}


VOS_UINT32 AT_TestDhcpPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

#if (FEATURE_ON == FEATURE_IPV6)

VOS_UINT32 AT_PS_ReportDhcpv6(TAF_UINT8 ucIndex)
{
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulSpeed;
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];

    usLength = 0;
    PS_MEM_SET(aucIpv6AddrStr, 0x00, (TAF_MAX_IPV6_ADDR_COLON_STR_LEN));
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, TAF_IPV6_ADDR_LEN);

    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);
    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportDhcpv6:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    if (AT_PDP_STATE_ACTED != pstCallEntity->enIpv6State)
    {
        AT_WARN_LOG("AT_PS_ReportDhcpv6: PDP is not actived.");
        return AT_ERROR;
    }

    /* ��ȡ�������۴���*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("AT_PS_ReportDhcpv6: ERROR : AT_GetDisplayRate Error!");
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ��дIPV6��ַ */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstCallEntity->stIpv6DhcpInfo.aucIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", aucIpv6AddrStr);

    /* ��дIPV6����, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дIPV6����, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дDHCP IPV6, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дIPV6 Primary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstCallEntity->stIpv6DhcpInfo.aucIpv6PrimDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дIPV6 Secondary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstCallEntity->stIpv6DhcpInfo.aucIpv6SecDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дMAX TX/RX Rate */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);

#ifdef BSP_CONFIG_BOARD_K5160
    /*PCUI*/
    if ( AT_USBCOM_USER == g_stAtNdisUserType )
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
               (VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", g_stAtNdisCid);
    }
#endif/*BSP_CONFIG_BOARD_K5160*/

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_SetDhcpv6Para(VOS_UINT8 ucIndex)
{
    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ѯָ��CID��ʵ��PDP������ */
    return AT_PS_ReportDhcpv6(ucIndex);
}

VOS_UINT32 AT_QryDhcpV6Para_AppUser(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_WPG_COMMON)
    return AT_PS_ReportDefaultDhcpV6(ucIndex);
#else
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    VOS_UINT32                          ulSpeed;

    usLength                            = 0;

    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    ulPdpActingFlg   = AT_AppCheckIpv6PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_AppCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ((AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
       && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State)))
    {
        AT_ERR_LOG("AT_QryDhcpV6Para_AppUser:ERROR: PDP is not active for APP.");
        return AT_ERROR;
    }

    /* ��ȡ�������۴���*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_WARN_LOG("AT_QryDhcpV6Para_AppUser:WARNING: AT_GetDisplayRate Error!");
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ��дIPV6��ַ */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstAppPdpEntity->stIpv6Dhcp.aucIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", aucIpv6AddrStr);

    /* ��дIPV6����, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дIPV6����, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дDHCP IPV6, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дIPV6 Primary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstAppPdpEntity->stIpv6Dhcp.aucIpv6PrimDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дIPV6 Secondary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      pstAppPdpEntity->stIpv6Dhcp.aucIpv6SecDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дMAX TX/RX Rate */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
#endif
}


VOS_UINT32 AT_QryDhcpV6Para_NdisUser(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_FEATURE_MPDP)
    return AT_PS_ReportDefaultDhcpV6(ucIndex);
#else
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    VOS_UINT32                          ulSpeed;

    usLength                            = 0;

    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    ulPdpActingFlg   = AT_NdisCheckIpv6PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_NdisCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

    if ((VOS_TRUE == ulPdpActingFlg)
     || (VOS_TRUE == ulPdpDeactingFlg)
     || ((AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State)))
    {
        AT_WARN_LOG("AT_QryDhcpV6Para_NdisUser AT_NdisGetState:");
        return AT_ERROR;
    }

    /* ��ȡ�������۴���*/
    if (VOS_ERR == AT_GetDisplayRate(ucIndex, &ulSpeed))
    {
        ulSpeed = AT_DEF_DISPLAY_SPEED;
        AT_ERR_LOG("AT_QryDhcpV6Para_NdisUser : ERROR : AT_GetDisplayRate Error!");
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr, "%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ��дIPV6��ַ */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, "%s", aucIpv6AddrStr);

    /* ��дIPV6����, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дIPV6����, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дDHCP IPV6, ���ֶ���ȫ0 */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      aucInvalidIpv6Addr,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s", aucIpv6AddrStr);

    /* ��дIPV6 Primary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6PrimDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s",  aucIpv6AddrStr);

    /* ��дIPV6 Secondary DNS */
    AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                      g_stAtNdisDhcpPara.stIpv6Dhcp.aucIpv6SecDNS,
                                      TAF_IPV6_STR_RFC2373_TOKENS);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength, ",%s",  aucIpv6AddrStr);

    /* ��дMAX TX/RX Rate */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", ulSpeed);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
#endif
}


VOS_UINT32 AT_QryDhcpv6Para(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;
    AT_USER_TYPE                        enUsrType;

    ulResult  = AT_OK;

    enUsrType = AT_PS_GetDailPortUsrType(gastAtClientTab[ucIndex].UserType);

    switch (enUsrType)
    {
        case AT_NDIS_USER:
            ulResult = AT_QryDhcpV6Para_NdisUser(ucIndex);
            break;

        case AT_APP_USER:
            ulResult = AT_QryDhcpV6Para_AppUser(ucIndex);
            break;

        default:
            break;
    }

    return ulResult;
}


VOS_UINT32 AT_TestDhcpv6Para(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

VOS_UINT32 AT_PS_ReportApraInfo(TAF_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    VOS_UINT32                          ulMtuSize;
    VOS_UINT32                          ulPrefixBitLen;
    VOS_UINT32                          ulPreferredLifetime;
    VOS_UINT32                          ulValidLifetime;
    AT_PS_CALL_ENTITY_STRU             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;

    usLength                            = 0;
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));
    PS_MEM_SET(aucIpv6AddrStr, 0x00, (TAF_MAX_IPV6_ADDR_COLON_STR_LEN));
    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);
    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportApraInfo:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    if (AT_PDP_STATE_ACTED != pstCallEntity->enIpv6State)
    {
        AT_WARN_LOG("AT_PS_ReportApraInfo: PDP is not actived.");
        return AT_ERROR;
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ��дMTU */
    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpMtuSize)
    {
        ulMtuSize = 0;
    }
    else
    {
        ulMtuSize = pstCallEntity->stIpv6RaInfo.ulMtuSize;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       ulMtuSize);
    /* ��дPrefix */
    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpPrefixAddr)
    {
        ulPrefixBitLen = 0;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          aucInvalidIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }
    else
    {
        ulPrefixBitLen = pstCallEntity->stIpv6RaInfo.ulPrefixBitLen;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstCallEntity->stIpv6RaInfo.aucPrefixAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",\"%s/%d\"",
                                       aucIpv6AddrStr,
                                       ulPrefixBitLen);

    /* ��дPreferred Lifetime */
    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpPreferredLifetime)
    {
        ulPreferredLifetime = 0;
    }
    else
    {
        ulPreferredLifetime = pstCallEntity->stIpv6RaInfo.ulPreferredLifetime;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulPreferredLifetime);

    if (VOS_FALSE == pstCallEntity->stIpv6RaInfo.bitOpValidLifetime)
    {
        ulValidLifetime = 0;
    }
    else
    {
        ulValidLifetime = pstCallEntity->stIpv6RaInfo.ulValidLifetime;
    }

    /* ��дValid Lifetime */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulValidLifetime);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_SetApRaInfoPara(VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ѯָ��CID��ʵ��PDP������ */
    return AT_PS_ReportApraInfo(ucIndex);
}


VOS_UINT32 AT_QryApRaInfoPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_WPG_COMMON)
    return AT_PS_ReportDefaultApraInfo(ucIndex);
#else
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;
    VOS_UINT32                          ulMtuSize;
    VOS_UINT32                          ulPrefixBitLen;
    VOS_UINT32                          ulPreferredLifetime;
    VOS_UINT32                          ulValidLifetime;

    usLength                            = 0;

    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
    pstAppRaInfoAddr                    = AT_APP_GetRaInfoAddr();

    ulPdpActingFlg   = AT_AppCheckIpv6PdpState(AT_PDP_STATE_ACTING);
    ulPdpDeactingFlg = AT_AppCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

    if ( (VOS_TRUE == ulPdpActingFlg)
      || (VOS_TRUE == ulPdpDeactingFlg)
      || ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
        && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) ) )
    {
        AT_ERR_LOG("AT_QryApRaInfoPara:ERROR: PDP is not active for APP.");
        return AT_ERROR;
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ��дMTU */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpMtuSize)
    {
        ulMtuSize = 0;
    }
    else
    {
        ulMtuSize = pstAppRaInfoAddr->ulMtuSize;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       ulMtuSize);
    /* ��дPrefix */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPrefixAddr)
    {
        ulPrefixBitLen = 0;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          aucInvalidIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }
    else
    {
        ulPrefixBitLen = pstAppRaInfoAddr->ulPrefixBitLen;
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstAppRaInfoAddr->aucPrefixAddr,
                                          (VOS_UINT8)ulPrefixBitLen/16);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",\"%s/%d\"",
                                       aucIpv6AddrStr,
                                       ulPrefixBitLen);

    /* ��дPreferred Lifetime */
    if (VOS_FALSE == pstAppRaInfoAddr->bitOpPreferredLifetime)
    {
        ulPreferredLifetime = 0;
    }
    else
    {
        ulPreferredLifetime = pstAppRaInfoAddr->ulPreferredLifetime;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulPreferredLifetime);

    if (VOS_FALSE == pstAppRaInfoAddr->bitOpValidLifetime)
    {
        ulValidLifetime = 0;
    }
    else
    {
        ulValidLifetime = pstAppRaInfoAddr->ulValidLifetime;
    }

    /* ��дValid Lifetime */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%u",
                                       ulValidLifetime);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
#endif
}


VOS_UINT32 AT_TestApRaInfoPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}



VOS_UINT32 AT_PS_ReportLanAddr(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity = VOS_NULL_PTR;
    AT_IPV6_RA_INFO_STRU               *pstIpv6RaInfo;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];

    usLength = 0;
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));
    /* ����cid��ȡ��Ӧ��callid */
    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportLanAddr:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

    /* ��ǰδ���ֱ�ӷ���error */
    if (AT_PDP_STATE_ACTED != pstPsCallEntity->enIpv6State)
    {
        return AT_ERROR;
    }

    pstIpv6RaInfo = &(pstPsCallEntity->stIpv6RaInfo);

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (VOS_FALSE == pstIpv6RaInfo->bitOpLanAddr)
    {
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          aucInvalidIpv6Addr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }
    else
    {
        AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                          pstIpv6RaInfo->aucLanAddr,
                                          TAF_IPV6_STR_RFC2373_TOKENS);
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "\"%s\"",
                                       aucIpv6AddrStr);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       pstIpv6RaInfo->ulPrefixBitLen);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_SetApLanAddrPara(VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ѯָ��CID��ʵ��PDP������ */
    return AT_PS_ReportLanAddr(ucIndex);
}


VOS_UINT32 AT_QryApLanAddrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucIpv6AddrStr[TAF_MAX_IPV6_ADDR_COLON_STR_LEN];
    VOS_UINT8                           aucInvalidIpv6Addr[TAF_IPV6_ADDR_LEN];
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_IPV6_RA_INFO_STRU               *pstAppRaInfoAddr;
    VOS_UINT32                          ulPdpActingFlg;
    VOS_UINT32                          ulPdpDeactingFlg;

    usLength                            = 0;
    PS_MEM_SET(aucInvalidIpv6Addr, 0x00, sizeof(aucInvalidIpv6Addr));

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {

        pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();
        pstAppRaInfoAddr                    = AT_APP_GetRaInfoAddr();

        ulPdpActingFlg   = AT_AppCheckIpv6PdpState(AT_PDP_STATE_ACTING);
        ulPdpDeactingFlg = AT_AppCheckIpv6PdpState(AT_PDP_STATE_DEACTING);

        if ( (VOS_TRUE == ulPdpActingFlg)
          || (VOS_TRUE == ulPdpDeactingFlg)
          || ( (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv6State)
            && (AT_PDP_STATE_IDLE == pstAppPdpEntity->enIpv4v6State) ) )
        {
            AT_ERR_LOG("AT_QryApLanAddrPara:ERROR: PDP is not active for APP.");
            return AT_ERROR;
        }

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        if (VOS_FALSE == pstAppRaInfoAddr->bitOpLanAddr)
        {
            AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                              aucInvalidIpv6Addr,
                                              TAF_IPV6_STR_RFC2373_TOKENS);
        }
        else
        {
            AT_ConvertIpv6AddrToCompressedStr(aucIpv6AddrStr,
                                              pstAppRaInfoAddr->aucLanAddr,
                                              TAF_IPV6_STR_RFC2373_TOKENS);
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "\"%s\"",
                                           aucIpv6AddrStr);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstAppRaInfoAddr->ulPrefixBitLen);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_TestApLanAddrPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}

#endif


VOS_UINT32 AT_PS_ReportConnSt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucCallId;
    AT_PS_CALL_ENTITY_STRU             *pstPsCallEntity = VOS_NULL_PTR;
    AT_APP_CONN_STATE_ENUM_U32          enIpv4ConnStatus;
#if (FEATURE_ON == FEATURE_IPV6)
    AT_APP_CONN_STATE_ENUM_U32          enIpv6ConnStatus;
#endif
    VOS_UINT16                          usLength;

    usLength = 0;

    /* ����cid��ȡ��Ӧ��callid */
    ucCallId = AT_PS_TransCidToCallId(ucIndex, (VOS_UINT8)gastAtParaList[0].ulParaValue);

    if (VOS_TRUE != AT_PS_IsCallIdValid(ucIndex, ucCallId))
    {
        AT_ERR_LOG("AT_PS_ReportConnSt:ERROR: CallId is invalid!");
        return AT_ERROR;
    }

    pstPsCallEntity = AT_PS_GetCallEntity(ucIndex, ucCallId);

#if (FEATURE_ON == FEATURE_IPV6)
    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv4State);

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv6State);

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv4State);
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv6State);

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        default:
            break;
    }
#else
    enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(pstPsCallEntity->enIpv4State);

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,\"IPV4\"",
                                       enIpv4ConnStatus);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32  At_SetApConnStPara(
    VOS_UINT8                           ucIndex
)
{
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ��ѯָ��CID��ʵ��PDP������ */
    return AT_PS_ReportConnSt(ucIndex);
}


VOS_UINT32  At_QryApConnStPara(
    VOS_UINT8                           ucIndex
)
{
    AT_PDP_ENTITY_STRU                 *pstAppPdpEntity;
    AT_APP_CONN_STATE_ENUM_U32          enIpv4ConnState;
    VOS_UINT16                          usLength;

    pstAppPdpEntity                     = AT_APP_GetPdpEntInfoAddr();

    usLength                            = 0;

    if (AT_PDP_STATE_ACTING == pstAppPdpEntity->enIpv4State)
    {
        enIpv4ConnState = AT_APP_DIALING;
    }
    else if (AT_PDP_STATE_ACTED == pstAppPdpEntity->enIpv4State)
    {
        enIpv4ConnState = AT_APP_DIALED;
    }
    else
    {
        enIpv4ConnState = AT_APP_UNDIALED;
    }


    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       enIpv4ConnState);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

    /* ����֧�ֶ�WWAN���޸� */
#if 0
    AT_APP_CONN_STATE_ENUM_U32         enIpv4ConnStatus;
#if (FEATURE_ON == FEATURE_IPV6)
    AT_APP_CONN_STATE_ENUM_U32         enIpv6ConnStatus;
    AT_APP_CONN_STATE_ENUM_U32         enIpv4v6ConnStatus;
#endif
    VOS_UINT16                         usLength = 0;

#if (FEATURE_ON == FEATURE_IPV6)
    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
            enIpv4v6ConnStatus  = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4V6));

            if (AT_APP_UNDIALED == enIpv4v6ConnStatus)
            {
                enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4));
                enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV6));
            }
            else
            {
                enIpv4ConnStatus = enIpv4v6ConnStatus;
                enIpv6ConnStatus = enIpv4v6ConnStatus;
            }

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4));
            enIpv6ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%d,\"IPV4\"",
                                               enIpv4ConnStatus);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",%d,\"IPV6\"",
                                               enIpv6ConnStatus);
            break;

        default:
            break;
    }
#else
    enIpv4ConnStatus = AT_AppConvertPdpStateToConnStatus(AT_AppGetPdpState(TAF_PDP_IPV4));

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,\"IPV4\"",
                                       enIpv4ConnStatus);
#endif

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
#endif
}


VOS_UINT32 AT_TestApConnStPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}


VOS_UINT32 At_SetApThroughputPara(
    VOS_UINT8                           ucIndex
)
{
    AT_RNIC_DSFLOW_IND_STRU            *pstMsg;
    RNIC_RM_NET_ID_ENUM_UINT8           enRnicRmNetId;
    AT_MODEM_PS_CTX_STRU               *pstPsModemCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucCid;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex != 1)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    ucCid = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /* ��ȡ��Ӧ��RNIC���� */
    pstPsModemCtx = AT_GetModemPsCtxAddrFromClientId(ucIndex);

    enRnicRmNetId = (RNIC_RM_NET_ID_ENUM_UINT8)pstPsModemCtx->astChannelCfg[ucCid].ulRmNetId;

    if (enRnicRmNetId >= RNIC_RM_NET_ID_BUTT)
    {
        return AT_ERROR;
    }

    /* ����ID_AT_RNIC_DSFLOW_IND��Ϣ */
    pstMsg = (AT_RNIC_DSFLOW_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_DSFLOW_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_SetApThroughputPara: alloc msg fail!");
        return AT_ERROR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(AT_RNIC_DSFLOW_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    pstMsg->clientId        = gastAtClientTab[ucIndex].usClientId;
    pstMsg->enRnicRmNetId   = enRnicRmNetId;

    /* ��ID_AT_RNIC_DSFLOW_IND��Ϣ��RNIC��ȡ��ǰ������ */
    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APTHROUGH_PUT_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("At_SetApThroughputPara: Send msg failed!");
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryApThroughputPara(
    VOS_UINT8                           ucIndex
)
{
    AT_RNIC_DSFLOW_IND_STRU            *pstMsg;

    /* ����ID_AT_RNIC_DSFLOW_IND��Ϣ */
    pstMsg = (AT_RNIC_DSFLOW_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_DSFLOW_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_QryApThroughputPara: alloc msg fail!");
        return AT_ERROR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR*)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(AT_RNIC_DSFLOW_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_DSFLOW_IND;
    pstMsg->clientId        = gastAtClientTab[ucIndex].usClientId;
    pstMsg->enRnicRmNetId   = RNIC_RM_NET_ID_0;

    /* ��ID_AT_RNIC_DSFLOW_IND��Ϣ��RNIC��ȡ��ǰ������ */
    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APTHROUGH_PUT_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("At_QryApThroughputPara: Send msg failed!");
        return AT_ERROR;
    }
}


VOS_UINT32 AT_TestApThroughputPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s: (1-11)",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    return AT_OK;
}
/* Modified by l60609 for V9R1 IPv6&TAF/SM Project, 2013-4-27, end */


VOS_UINT32 AT_SetApEndPppPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == FEATURE_AT_HSIC)
    AT_DCE_MSC_STRU                     stMscStru;
    VOS_UINT8                           ucActIndex;
    VOS_UINT8                           ucDlci;

    if (VOS_TRUE != AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /*ģ������DTR�ź�*/
    VOS_MemSet(&stMscStru, 0x00, sizeof(stMscStru));
    stMscStru.OP_Dtr = 1;
    stMscStru.ucDtr  = 0;

    /* HSIC MODEM������ */
    ucActIndex  = AT_CLIENT_TAB_HSIC_MODEM_INDEX;

    /*MODEM��·�� */
    ucDlci      = AT_MODEM_USER_DLCI;

    At_ModemMscInd(ucActIndex, ucDlci, &stMscStru);

    return AT_OK;
#else
    return AT_ERROR;
#endif
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
