

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AtCmdSimProc.h"
#include "AtEventReport.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_AT_CMD_SIM_PROC_C
/*lint +e767*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_UINT32 At_SetSIMSlotPara(VOS_UINT8 ucIndex)
{
    TAF_NV_SCI_CFG_STRU                 stSCICfg;

    /* ������� */
    if (AT_CMD_OPT_SET_PARA_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (2 != gucAtParaIndex)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����SIM1STATEΪ�ջ����2 */
    if ((0 == gastAtParaList[0].usParaLen)
      || (gastAtParaList[0].ulParaValue > 2))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ����SIM2STATEΪ�ջ����2 */
    if ((0 == gastAtParaList[1].usParaLen)
      || (gastAtParaList[1].ulParaValue > 2))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_SET(&stSCICfg, 0, sizeof(stSCICfg));

    /* ��NV�ж�ȡ��ǰSIM����SCI���� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            ev_NV_Item_SCI_DSDA_CFG,
                            &stSCICfg,
                            sizeof(stSCICfg)))
    {
        AT_ERR_LOG("At_SetSIMSlotPara: ev_NV_Item_SCI_DSDA_CFG read fail!");
        return AT_ERROR;
    }

    /* �����û����õ�ֵ�޸�card0λ��card1λ��ֵ����NV���У��������Ӧ��bitλ��ȡֵ��������:
        card0: bit[8-10]������0ʹ�õ�SCI�ӿ�
            0��ʹ��SCI0��Ĭ��ֵ��
            1��ʹ��SCI1
            ����ֵ����Ч
        card1:bit[11-13]����1��ʹ�õ�SCI�ӿ�
            0��ʹ��SCI0
            1��ʹ��SCI1��Ĭ��ֵ��
            ����ֵ����Ч */
    if (1 == gastAtParaList[0].ulParaValue)
    {
        stSCICfg.ulValue = stSCICfg.ulValue & 0xFFFFF8FF;
    }
    else if (2 == gastAtParaList[0].ulParaValue)
    {
        stSCICfg.ulValue = stSCICfg.ulValue & 0xFFFFF8FF;
        stSCICfg.ulValue = stSCICfg.ulValue | 0x100;
    }
    else
    {
        /* ����Ϊ0�򲻱� */
    }

    if (1 == gastAtParaList[1].ulParaValue)
    {
        stSCICfg.ulValue = stSCICfg.ulValue & 0xFFFFC7FF;
    }
    else if (2 == gastAtParaList[1].ulParaValue)
    {
        stSCICfg.ulValue = stSCICfg.ulValue & 0xFFFFC7FF;
        stSCICfg.ulValue = stSCICfg.ulValue | 0x800;
    }
    else
    {
        /* ����Ϊ0�򲻱� */
    }

    /*�ж�card0��card1�ֶε�ֵ�Ƿ����*/
    if ((stSCICfg.ulValue & 0x700) == ((stSCICfg.ulValue & 0x3800) >> 3))
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*�����õ�SCIֵ���浽NV��*/
    if (NV_OK != NV_WriteEx(MODEM_ID_0,
                            ev_NV_Item_SCI_DSDA_CFG,
                            &stSCICfg,
                            sizeof(stSCICfg)))
    {
        AT_ERR_LOG("At_SetSIMSlotPara: ev_NV_Item_SCI_DSDA_CFG write failed");
        return AT_ERROR;
    }

    return AT_OK;

}


VOS_UINT32 At_QrySIMSlotPara(VOS_UINT8 ucIndex)
{
    TAF_NV_SCI_CFG_STRU                 stSCICfg;
    VOS_UINT32                          ulSim1State;
    VOS_UINT32                          ulSim2State;

    PS_MEM_SET(&stSCICfg, 0, sizeof(stSCICfg));


    /*��NV�ж�ȡ��ǰSIM����SCI����*/
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            ev_NV_Item_SCI_DSDA_CFG,
                            &stSCICfg,
                            sizeof(stSCICfg)))
    {
        AT_ERR_LOG("At_QrySIMSlotPara: ev_NV_Item_SCI_DSDA_CFG read fail!");
        return AT_ERROR;
    }

    ulSim1State = ((stSCICfg.ulValue & 0x700) >> 8) + 1;
    ulSim2State = ((stSCICfg.ulValue & 0x3800) >> 11) + 1;


    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulSim1State,ulSim2State);

    return AT_OK;

}


VOS_VOID At_Base16Encode(VOS_CHAR *pucSrc, VOS_CHAR *pucDst, VOS_UINT32 ulLen)
{
    VOS_CHAR   aucNibble[2];
    VOS_UINT32  i;
    VOS_UINT32  j;

    for (i = 0; i < ulLen; i++)
    {
        aucNibble[0] = (pucSrc[i] & 0xF0) >> 4;
        aucNibble[1] = pucSrc[i] & 0x0F;
        for (j = 0; j < 2; j++)
        {
            if (aucNibble[j] < 10)
            {
                aucNibble[j] += 0x30;
            }
            else
            {
                if (aucNibble[j] < 16)
                {
                    aucNibble[j] = aucNibble[j] - 10 + 'A';
                }
            }

            *pucDst++ = aucNibble[j];
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : At_Base16Decode
 Description    : ^HVSDH
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-20
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_Base16Decode(VOS_CHAR *pcData, VOS_UINT32 ulDataLen, VOS_UINT8* pucDst)
{
    VOS_UINT32 ulLen    = ulDataLen;
    VOS_UINT32 i        = 0;
    VOS_CHAR   n[2] = {0};
    VOS_UINT32 j;

    while(i < ulLen)
    {
        for(j = 0; j < 2; j++)
        {
            if(pcData[i+j] >= '0' && pcData[i+j] <= '9')
            {
                n[j] = pcData[i+j] - '0';
            }
            else if(pcData[i+j] >= 'a' && pcData[i+j] <= 'f')
            {
                n[j] = pcData[i+j] - 'a' + 10;
            }
            else if(pcData[i+j] >= 'A' && pcData[i+j] <= 'F')
            {
                n[j] = pcData[i+j] - 'A' + 10;
            }
            else
            {
                ;
            }
        }

        pucDst[i/2] = (VOS_UINT8)(n[0] * 16 + n[1]);

        i += 2;
    }

    return (ulDataLen/2);
}

#if (FEATURE_ON == FEATURE_VSIM)
/*****************************************************************************
 Prototype      : At_Hex2Base16
 Description    : ��16����ת��BASE64����
 Input          : nptr --- �ַ���
 Output         :
 Return Value   : ���ݳ���
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT16 At_Hex2Base16(VOS_UINT32 MaxLength,VOS_CHAR *headaddr,VOS_CHAR *pucDst,VOS_UINT8 *pucSrc,VOS_UINT16 usSrcLen)
{
    VOS_UINT32          i;
    VOS_CHAR            *pcData;

    pcData = pucDst;

    for(i=0; i<usSrcLen; i++)
    {
        At_sprintf((VOS_INT32)MaxLength,headaddr,pcData,"%X",((pucSrc[i]&0xF0)>>4));

        pcData++;

        At_sprintf((VOS_INT32)MaxLength,headaddr,pcData,"%X",(pucSrc[i]&0x0F));

        pcData++;
    }

    return (VOS_UINT16)(usSrcLen*2);
}

/*****************************************************************************
 Prototype      : At_QryHvsDHPara
 Description    : ^HVSDH
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-20
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_QryHvsDHPara(VOS_UINT8 ucIndex)
{
    if(AT_SUCCESS == SI_PIH_HvsDHQuery(gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSDH_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }

    AT_WARN_LOG("At_QryHvsDHPara: SI_PIH_HvsDHQuery fail.");

    return AT_ERROR;
}



VOS_UINT32 At_SetHvsstPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                              ulResult;
    SI_PIH_HVSST_SET_STRU                   stHvSStSet;

    /* �������� */
    if (gucAtParaIndex > 3)
    {
        AT_WARN_LOG("At_SetHvsstPara: Too Much Parameter.");
        return AT_ERROR;
    }

    /* ���������� */
    if ( (0 == gastAtParaList[0].usParaLen)
       ||(0 == gastAtParaList[1].usParaLen)
       ||(0 == gastAtParaList[2].usParaLen) )
    {
        AT_WARN_LOG("At_SetHvsstPara: Parameter is not enough.");
        return AT_CME_INCORRECT_PARAMETERS;
    }
    /*�������, indexĿǰֻ֧��1����*/
#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
    /*�Ա�ԭ����������ӿ�����У��*/
    if ( (SI_PIH_SIM_REAL_SIM1 != gastAtParaList[0].ulParaValue)
        &&(SI_PIH_SIM_VIRT_PSIM != gastAtParaList[0].ulParaValue)
        &&(SI_PIH_SIM_VIRT_SSIM != gastAtParaList[0].ulParaValue))
#else
    if ( (SI_PIH_SIM_REAL_SIM1 != gastAtParaList[0].ulParaValue)
       &&(SI_PIH_SIM_VIRT_SIM1 != gastAtParaList[0].ulParaValue) )
#endif/*end (FEATURE_ON == MBB_FEATURE_VSIM_HUK)*/
    {
        AT_WARN_LOG("At_SetHvsstPara: Parameter <Index> is Wrong.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stHvSStSet.ucIndex = (VOS_UINT8)gastAtParaList[0].ulParaValue;

    /*�������, enable����*/
    if (gastAtParaList[1].ulParaValue >= SI_PIH_SIM_STATE_BUTT)
    {
        AT_WARN_LOG("At_SetHvsstPara: Parameter <enable> is Wrong.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stHvSStSet.enSIMSet = (VOS_UINT8)gastAtParaList[1].ulParaValue;

    /*�������, slotĿǰֻ֧��2����*/
    if ( (gastAtParaList[2].ulParaValue != SI_PIH_SIM_SLOT1)
       &&(gastAtParaList[2].ulParaValue != SI_PIH_SIM_SLOT2) )
    {
        AT_WARN_LOG("AT_SetHvsstPara: Parameter <slot> is Wrong.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    stHvSStSet.ucSlot = (VOS_UINT8)gastAtParaList[2].ulParaValue;

    ulResult = SI_PIH_HvSstSet(gastAtClientTab[ucIndex].usClientId,
                              gastAtClientTab[ucIndex].opId,
                              &stHvSStSet);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_SetHvsstPara: SI_PIH_HvSstSet fail.");
        return AT_CME_PHONE_FAILURE;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSST_SET;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 At_QryHvsstPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    ulResult = SI_PIH_HvSstQuery(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryPortAttribSetPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSST_QUERY;

    return AT_WAIT_ASYNC_RETURN;
}

/*****************************************************************************
 Prototype      : At_QryHvsContPara
 Description    : ^HVSDH
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-20
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_QryHvsContPara(VOS_UINT8 ucIndex)
{
    if(AT_SUCCESS == SI_PIH_HvsContQuery(gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSCONT_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }

    return AT_ERROR;
}


VOS_UINT32 At_DealRSFWVsim(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLength = 0;
    SI_PIH_FILEWRITE_DATA_STRU          stFWriteStru;
    VOS_UINT8                           *pucRsfw;
#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
    VOS_UINT8    cName[AT_RSFR_RSFW_NAME_LEN + 1]   = {0};

    /* ��ʼ�� */
    PS_MEM_SET(&stFWriteStru,0x00,sizeof(stFWriteStru));

    /*Ӧ��ͨ��RSFW д�������ļ����ӿ��ļ�*/
    /*����ʹ�õڶ��������������ӿ��������������ڴ洢*/
    PS_MEM_CPY(cName, gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen);
    At_UpString((VOS_UINT8*)cName, gastAtParaList[1].usParaLen);

    if(VOS_OK == AT_STRCMP(cName, "PVSIM"))
    {
        stFWriteStru.enVsimIndex = SI_PIH_SIM_VIRT_PSIM;
    }
    else if(VOS_OK == AT_STRCMP(cName, "SVSIM"))
    {
        stFWriteStru.enVsimIndex = SI_PIH_SIM_VIRT_SSIM;
    }
    else
    {
         vos_printf("At_DealRSFWVsim: sub_itemname is error.\n");
         AT_WARN_LOG("At_DealRSFWVsim: sub_itemname is error.");
         return AT_CME_INCORRECT_PARAMETERS;
    }
#else
    /* ��ʼ�� */
    PS_MEM_SET(&stFWriteStru,0x00,sizeof(stFWriteStru));
#endif/*end (FEATURE_ON == MBB_FEATURE_VSIM_HUK)*/

    /* indexֵ����totalֵ */
    if(gastAtParaList[4].ulParaValue > gastAtParaList[3].ulParaValue)
    {
        AT_WARN_LOG("At_DealRSFWVsim: index is greater total.");
        return AT_CME_INVALID_INDEX;
    }

    /* data���ݳ��ȴ������ֵ */
    if(gastAtParaList[5].usParaLen > AT_PARA_MAX_LEN)
    {
        AT_WARN_LOG1("At_DealRSFWVsim: param 5 is too long", gastAtParaList[5].usParaLen);
        return AT_CME_TEXT_STRING_TOO_LONG;
    }

    pucRsfw = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, gastAtParaList[5].usParaLen);/*����ת�����������ڴ�*/

    if (VOS_NULL_PTR == pucRsfw )
    {
        AT_WARN_LOG("At_DealRSFWVsim: alloc memory failed.");
        return AT_CME_MEMORY_FAILURE;
    }

    PS_MEM_SET(pucRsfw, 0, gastAtParaList[5].usParaLen);

    ulRet = AtBase64Decode(gastAtParaList[5].aucPara,
                           gastAtParaList[5].usParaLen,
                           pucRsfw,
                           gastAtParaList[5].usParaLen,
                           &ulLength);

    if(b64Result_OK != ulRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucRsfw);

        AT_WARN_LOG("At_DealRSFWVsim: AtBase64Decode failed.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    stFWriteStru.stFileData.pucData     = pucRsfw;
    stFWriteStru.stFileData.ulDataLen   = ulLength;

    stFWriteStru.ulRef                  = gastAtParaList[2].ulParaValue;
    stFWriteStru.ulTotalNum             = gastAtParaList[3].ulParaValue;
    stFWriteStru.ulIndex                = gastAtParaList[4].ulParaValue;

    stFWriteStru.stFileName.pucData     = (VOS_UINT8*)"VSIM";
    stFWriteStru.stFileName.ulDataLen   = (VOS_UINT32)VOS_StrLen("VSIM");

    ulRet = SI_PIH_AtFileWrite(gastAtClientTab[ucIndex].usClientId, 0, &stFWriteStru);

    if(TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("At_DealRSFWVsim: SI_PIH_AtFileWrite Return Failed.");

        PS_MEM_FREE(WUEPS_PID_AT, pucRsfw);

        return AT_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucRsfw);

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_HvsstQueryCnf
 Description    : HVSST��ѯ����
 Input          : pEvent --- �¼�����
 Output         :
 Return Value   : ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-18
    Author      : zhuli
    Modification: Created function
*****************************************************************************/
VOS_UINT16 At_HvsstQueryCnf(SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT16 usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "^HVSST:");

#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
    /*�����Index �����ӿ�������*/
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                            (VOS_CHAR *)pgucAtSndCodeAddr,
                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                            "%d,%d,",pstEvent->PIHEvent.HVSSTQueryCnf.enVsimIndex,
                            pstEvent->PIHEvent.HVSSTQueryCnf.enVSimState);
#else
    if (SI_PIH_SIM_ENABLE == pstEvent->PIHEvent.HVSSTQueryCnf.enVSimState)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "11,1,");
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "1,1,");
    }
#endif/*end (FEATURE_ON == MBB_FEATURE_VSIM_HUK)*/


    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "%d,", pstEvent->PIHEvent.HVSSTQueryCnf.enSlot);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "%d", pstEvent->PIHEvent.HVSSTQueryCnf.enCardUse);

    return usLength;
}
#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)

VOS_UINT32 At_TestHvsstPara(VOS_UINT8 ucIndex)
{

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "^HVSST: (1,11,12), (0,1), (1)");
    return AT_OK;
}

VOS_UINT32 At_SetHvsDHPara(VOS_UINT8 ucIndex)
{
    SI_PIH_SIM_INDEX_ENUM_UINT8         enVsimIndex;

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        AT_WARN_LOG("At_SetHvsDHPara: Para too much.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����ַ���Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        AT_WARN_LOG("At_SetHvsDHPara: Para Len Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((SI_PIH_KEY_VIRT_PSIM != gastAtParaList[0].ulParaValue)
        && (SI_PIH_KEY_VIRT_SSIM != gastAtParaList[0].ulParaValue)
        && (SI_PIH_KEY_DEVICE_KEY != gastAtParaList[0].ulParaValue)
        && (SI_PIH_KEY_CONTENT_KEY != gastAtParaList[0].ulParaValue))
    {
        AT_WARN_LOG("At_SetHvsDHPara: Para val Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    enVsimIndex = gastAtParaList[0].ulParaValue;

    if(TAF_SUCCESS == SI_PIH_HvsDHSet(gastAtClientTab[ucIndex].usClientId, 0, enVsimIndex))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSDH_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }

    AT_WARN_LOG("At_SetHvsDHPara: SI_PIH_HvsDHSet Error.");

    return AT_ERROR;
}

VOS_UINT32 At_TestHvsDHPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: (11,12,21,22),1",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    return AT_OK;
}

VOS_UINT16 AT_HvsDHQueryCnf(SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT16 usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"^HVSDH:");

    /* <index>, */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d,",pstEvent->PIHEvent.HvsDHCnf.enVsimIndex);

    /* <algrithm>, */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d,",pstEvent->PIHEvent.HvsDHCnf.enAlgorithm);

    /* <c_pkey>, */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    usLength += (VOS_UINT16)At_Hex2Base16(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                pstEvent->PIHEvent.HvsDHCnf.stCkey.aucKey, (VOS_UINT16)pstEvent->PIHEvent.HvsDHCnf.stCkey.ulKeyLen);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\",");

    /* <s_pkey>, */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    if (0 != pstEvent->PIHEvent.HvsDHCnf.stSkey.ulKeyLen)
    {
        usLength += (VOS_UINT16)At_Hex2Base16(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                    pstEvent->PIHEvent.HvsDHCnf.stSkey.aucKey, (VOS_UINT16)pstEvent->PIHEvent.HvsDHCnf.stSkey.ulKeyLen);
    }
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    return usLength;
}

VOS_UINT32 At_SryHvsContPara(VOS_UINT8 ucIndex)
{
    SI_PIH_SIM_INDEX_ENUM_UINT8         enVsimIndex;

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        AT_WARN_LOG("At_SryHvsContPara: Para too much.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����ַ���Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        AT_WARN_LOG("At_SryHvsContPara: Para Len Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*���Index ����Ϸ�*/
    if ((SI_PIH_SIM_REAL_SIM1 != gastAtParaList[0].ulParaValue)
	&&(SI_PIH_SIM_VIRT_PSIM != gastAtParaList[0].ulParaValue)
        &&(SI_PIH_SIM_VIRT_SSIM != gastAtParaList[0].ulParaValue))
    {
        AT_WARN_LOG("At_SryHvsContPara: Para val Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*��Index ����C�˴���*/
    enVsimIndex = gastAtParaList[0].ulParaValue;

    if(TAF_SUCCESS == SI_PIH_HvsContSet(gastAtClientTab[ucIndex].usClientId, 0, enVsimIndex))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSCONT_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }

    AT_WARN_LOG("At_SetHvsDHPara: SI_PIH_HvsDHSet Error.");

    return AT_ERROR;
}

VOS_UINT16 At_SetHvsContCnf(SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT32                          i = 0;
    VOS_UINT32                          j = 0;
    VOS_UINT16                          usLength = 0;
    SI_PIH_CARD_CONTENT_STRU           *pstCardContent;

    pstCardContent = pstEvent->PIHEvent.HvsContCnf.astSimCard;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "^HVSCONT:");

    /* (U)SIM����Ϣ������ֵ */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "%d,",
                                pstCardContent[i].ucIndex);

    /* ֧�ֵĿ����͵����� */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "%d,",
                                pstCardContent[i].ucCardCap);

    /* ��������Ӧ�� */
    if (VOS_NULL == pstCardContent[i].ucCardType)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                ",");
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "%d,",
                                pstCardContent[i].ucCardType);
    }

    /* IMSIֵ�����������IMSI�����PLMNҲӦ��Ϊ�� ,ֱ�ӷ��ص�ǰ����*/
    if (0 == VOS_StrLen((VOS_CHAR*)pstCardContent[i].aucImsi))
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "\"\",\"\"");
        return usLength;

    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "\"%s\"",
                                pstCardContent[i].aucImsi);
    }

    /* HPLMN��EHPLMN */
    for (j = 0; j < pstCardContent[i].usPlmnNum; j++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                   ",\"%X%X%X",
                                   (0x0f & pstCardContent[i].astPlmn[j].ulMCC),
                                   (0x0f00 & pstCardContent[i].astPlmn[j].ulMCC) >> 8,
                                   (0x0f0000 & pstCardContent[i].astPlmn[j].ulMCC) >> 16);

        /* �ж�MNC�����ֽڻ������ֽ� */
        if ( 0x0F == ((0x0f0000 & pstCardContent[i].astPlmn[j].ulMNC) >> 16) )
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%X%X\"",
                                            (0x0f & pstCardContent[i].astPlmn[j].ulMNC),
                                            (0x0f00 & pstCardContent[i].astPlmn[j].ulMNC) >> 8);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%X%X%X\"",
                                            (0x0f & pstCardContent[i].astPlmn[j].ulMNC),
                                            (0x0f00 & pstCardContent[i].astPlmn[j].ulMNC) >> 8,
                                            (0x0f0000 & pstCardContent[i].astPlmn[j].ulMNC) >> 16);
        }
    }

    return usLength;
}

VOS_UINT32 At_SetHvpDHPara(VOS_UINT8 ucIndex)
{
    DRV_AGENT_HVPDH_REQ_STRU         stHvpdhReq;
    VOS_VOID                           *pOutputData;
    VOS_UINT32                          ulOutputLen;
    VOS_UINT32                          ulResult;

    /* �������� */
    if(gucAtParaIndex > 3)
    {
        AT_WARN_LOG("At_SetHvpDHPara: Para too much.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����ַ���Ϊ�գ�������ԿΪbase16���룬�ʱ���Ϊż������ */
    if ((0 == gastAtParaList[0].usParaLen)
        || (0 == gastAtParaList[1].usParaLen)
        || (0 == gastAtParaList[2].usParaLen)
        || (1 == (gastAtParaList[2].usParaLen % 2)))
    {
        AT_WARN_LOG("At_SetHvpDHPara: Para Len Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((SI_PIH_KEY_VIRT_PSIM != gastAtParaList[0].ulParaValue)
        && (SI_PIH_KEY_VIRT_SSIM != gastAtParaList[0].ulParaValue)
        && (SI_PIH_KEY_DEVICE_KEY != gastAtParaList[0].ulParaValue)
        && (SI_PIH_KEY_CONTENT_KEY != gastAtParaList[0].ulParaValue))
    {
        AT_WARN_LOG("At_SetHvpDHPara: Para Val Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pOutputData = PS_MEM_ALLOC(WUEPS_PID_AT, gastAtParaList[2].usParaLen);
    if (VOS_NULL_PTR == pOutputData)
    {
        AT_WARN_LOG("At_SetHvpDHPara: PS_MEM_ALLOC Error.");
        return AT_ERROR;
    }
    VOS_MemSet(pOutputData, 0, gastAtParaList[2].usParaLen);
    VOS_MemSet(&stHvpdhReq, 0, sizeof(stHvpdhReq));

    /* ����Կ���н��� */
    ulOutputLen = At_Base16Decode((VOS_CHAR *)gastAtParaList[2].aucPara, gastAtParaList[2].usParaLen, pOutputData);

    /* ���ȳ������ֵ */
    if ( (DRV_AGENT_DH_KEY_SERVER_PUBLIC_KEY == gastAtParaList[1].ulParaValue)
       ||(DRV_AGENT_DH_KEY_MODEM_PUBLIC_KEY == gastAtParaList[1].ulParaValue) )
    {
        if (VSIM_DH_PUBIIC_KEY < ulOutputLen)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

            AT_WARN_LOG("At_SetHvpDHPara: public key too Long.");

            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        if (VSIM_DH_PRIVATE_KEY < ulOutputLen)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

            AT_WARN_LOG("At_SetHvpDHPara: private key too Long.");

            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    stHvpdhReq.enVsimIndex = gastAtParaList[0].ulParaValue;
    stHvpdhReq.enKeyType = gastAtParaList[1].ulParaValue;
    stHvpdhReq.ulKeyLen  = ulOutputLen;
    PS_MEM_CPY(stHvpdhReq.aucKey, pOutputData, ulOutputLen);

    /* �ͷ���ʹ������ڴ� */
    PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

    /* ���Ϳ����Ϣ��C��, �����Ȩ���� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_HVPDH_REQ,
                                      &stHvpdhReq,
                                      sizeof(stHvpdhReq),
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_SetHvpDHPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVPDH_SET;
    return AT_WAIT_ASYNC_RETURN;

}

VOS_UINT32 At_TestHvpDHPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "^HVPDH: (11,12,21,22)(0,1,2),(key_value)");
    return AT_OK;
}


VOS_UINT32 At_SetHvADHPara(VOS_UINT8 ucIndex)
{
    SI_PIH_HVADH_SET_STRU stHukPara;
    VOS_UINT32 ulResult = 0;

    /* ��������,����3���ϱ����� */
    if(gucAtParaIndex > 3)
    {
        AT_WARN_LOG("At_SetHvADHPara: Para too much.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����ַ���Ϊ��,���ߵ�һ���Ͳ�����Ԥ�ڣ����ز�������*/
    if ((0 == gastAtParaList[0].usParaLen)
        || (0 == gastAtParaList[1].usParaLen)
       ||(0 == gastAtParaList[2].usParaLen)) 
    {
        AT_WARN_LOG("At_SetHvADHPara: Para Len Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if((SI_PIH_HVADH_VSIM_PSIM > gastAtParaList[0].ulParaValue)
           ||(SI_PIH_HVADH_OBJ_BUTT <= gastAtParaList[0].ulParaValue))
    {
        AT_WARN_LOG("At_SetHvADHPara: Para1 Val error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if((SI_PIH_HVADH_ENCRYPT > gastAtParaList[1].ulParaValue)
           ||(SI_PIH_HVADH_MODE_BUTT <= gastAtParaList[1].ulParaValue))
    {
        AT_WARN_LOG("At_SetHvADHPara: Para2 Val error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*���ʹ�ýṹ��*/
    PS_MEM_SET(&stHukPara, 0, sizeof(SI_PIH_HVADH_SET_STRU));

    /*���copy*/
    stHukPara.ulobj = gastAtParaList[0].ulParaValue;
    stHukPara.ulmode = gastAtParaList[1].ulParaValue;

    stHukPara.stciperval.ulLen = (VOS_UINT32)gastAtParaList[2].usParaLen;
    PS_MEM_CPY( stHukPara.stciperval.aucVal, gastAtParaList[2].aucPara,gastAtParaList[2].usParaLen);

    /*�����ݵ��ýӿڴ���C��*/
    ulResult = SI_PIH_HvAdhSet(gastAtClientTab[ucIndex].usClientId,
                              gastAtClientTab[ucIndex].opId,
                              &stHukPara);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_SetHvADHPara: SI_PIH_HvAdhSet fail.");
        return AT_CME_PHONE_FAILURE;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVADH_SET;

    return AT_WAIT_ASYNC_RETURN;

}

VOS_UINT16 At_SetHvADHCnf(SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT16 usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "^HVADH:");

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "%s", 
                                pstEvent->PIHEvent.HvadhCnf.aucVal);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "%s",gaucAtCrLf);

    return usLength;
}

VOS_UINT32 At_TestHvAHPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "^HVADH:(1,2,3,4),(1,2),(ciper_value)");
    return AT_OK;
}


VOS_UINT32 At_SetHvshDHPara(VOS_UINT8 ucIndex)
{
    SI_PIH_KEY_INDEX_ENUM_UINT8         enKeyIndex;

    /*��Ҫ����Ƿ�˿���APP��*/
    if (AT_APP_USER != gastAtClientTab[ucIndex].UserType)
    {
        AT_WARN_LOG("At_SetHvshDHPara: UserType Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        AT_WARN_LOG("At_SetHvshDHPara: Para too much.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����ַ���Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        AT_WARN_LOG("At_SetHvshDHPara: Para Len Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if ((SI_PIH_KEY_DEVICE_KEY != gastAtParaList[0].ulParaValue)
        && (SI_PIH_KEY_CONTENT_KEY != gastAtParaList[0].ulParaValue))
    {
        AT_WARN_LOG("At_SetHvshDHPara: Para val Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    enKeyIndex = gastAtParaList[0].ulParaValue;

    if (TAF_SUCCESS == SI_PIH_HvshDHSet(gastAtClientTab[ucIndex].usClientId, 
                                    gastAtClientTab[ucIndex].opId, enKeyIndex))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSHDH_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }

    AT_WARN_LOG("At_SetHvshDHPara: SI_PIH_HvsDHSet Error.");

    return AT_ERROR;

}

VOS_UINT32 At_TestHvshDHPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "^HVSHDH:(21,22)");
    return AT_OK;

}


VOS_UINT16 AT_HvshDHSetCnf(SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT16 usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "%s",gaucAtCrLf);
    return usLength;

}


VOS_UINT32 At_QryHvdieidPara(VOS_UINT8 ucIndex)
{
    /*��Ҫ����Ƿ�˿���APP��*/
    if (AT_APP_USER != gastAtClientTab[ucIndex].UserType)
    {
        AT_WARN_LOG("At_QryHvdieidPara: UserType Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if(AT_SUCCESS == SI_PIH_HvdieIDQuery(gastAtClientTab[ucIndex].usClientId, gastAtClientTab[ucIndex].opId))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVDIEID_QUERY;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }

    return AT_ERROR;

}


VOS_UINT16 AT_HvdieidQueryCnf(SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT16 usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                        (VOS_CHAR *)pgucAtSndCodeAddr,
                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                        "%s",gaucAtCrLf);

    return usLength;
}


VOS_UINT32 At_SetHvdDHPara(VOS_UINT8 ucIndex)
{
    SI_PIH_CLEAN_KEY_INDEX_ENUM_UINT8      enCleanKeyType;

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        AT_WARN_LOG("At_SetHvdDHPara: Para too much.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����ַ���Ϊ�� */
    if (0 == gastAtParaList[0].usParaLen)
    {
        AT_WARN_LOG("At_SetHvdDHPara: Para Len Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    enCleanKeyType = gastAtParaList[0].ulParaValue;

    if (TAF_SUCCESS == SI_PIH_HvdDHSet(gastAtClientTab[ucIndex].usClientId, 
                                    gastAtClientTab[ucIndex].opId, enCleanKeyType))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVDDH_SET;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }

    AT_WARN_LOG("At_SetHvdDHPara: SI_PIH_HvdDHSet Error.");

    return AT_ERROR;
}


VOS_UINT16 AT_HvdDHSetCnf(SI_PIH_EVENT_INFO_STRU * pstEvent)
{
    VOS_UINT16 usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                "%s",gaucAtCrLf);
    return usLength;

}


VOS_UINT32 At_TestHvdDHPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "^HVDDH:(0,1,2,3,4)");
    return AT_OK;
}

#else

VOS_UINT32 At_TestHvsstPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "^HVSST: (1,11), (0,1), (1)");
    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_HvsContQueryCnf
 Description    : HVSCONT��ѯ����
 Input          : pEvent --- �¼�����
 Output         :
 Return Value   : ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-18
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT16 At_HvsContQueryCnf(SI_PIH_EVENT_INFO_STRU *pstEvent)

{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT16                          usLength = 0;
    SI_PIH_CARD_CONTENT_STRU           *pstCardContent;

    pstCardContent = pstEvent->PIHEvent.HvsContCnf.astSimCard;

    for (i = 0; i < SI_PIH_CARD_BUTT; i++)
    {
        if (0 != i)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s^HVSCONT:", gaucAtCrLf);
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "^HVSCONT:");
        }

        /* (U)SIM����Ϣ������ֵ */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%d,",
                                    pstCardContent[i].ucIndex);

        /* ֧�ֵĿ����͵����� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%d,",
                                    pstCardContent[i].ucCardCap);

        /* ��������Ӧ�� */
        if (VOS_NULL == pstCardContent[i].ucCardType)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    ",");
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%d,",
                                    pstCardContent[i].ucCardType);
        }

        /* IMSIֵ�����������IMSI�����PLMNҲӦ��Ϊ�� */
        if (0 == VOS_StrLen((VOS_CHAR*)pstCardContent[i].aucImsi))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "\"\",\"\"");
            continue;
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "\"%s\"",
                                    pstCardContent[i].aucImsi);
        }

        /* HPLMN��EHPLMN */
        for (j = 0; j < pstCardContent[i].usPlmnNum; j++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",\"%X%X%X",
                                       (0x0f & pstCardContent[i].astPlmn[j].ulMCC),
                                       (0x0f00 & pstCardContent[i].astPlmn[j].ulMCC) >> 8,
                                       (0x0f0000 & pstCardContent[i].astPlmn[j].ulMCC) >> 16);

            /* �ж�MNC�����ֽڻ������ֽ� */
            if ( 0x0F == ((0x0f0000 & pstCardContent[i].astPlmn[j].ulMNC) >> 16) )
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%X%X\"",
                                                (0x0f & pstCardContent[i].astPlmn[j].ulMNC),
                                                (0x0f00 & pstCardContent[i].astPlmn[j].ulMNC) >> 8);
            }
            else
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%X%X%X\"",
                                                (0x0f & pstCardContent[i].astPlmn[j].ulMNC),
                                                (0x0f00 & pstCardContent[i].astPlmn[j].ulMNC) >> 8,
                                                (0x0f0000 & pstCardContent[i].astPlmn[j].ulMNC) >> 16);
            }
        }
    }

    return usLength;
}
/*****************************************************************************
 Prototype      : At_SetHvsDHPara
 Description    : ^HVSDH
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-20
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_SetHvsDHPara(VOS_UINT8 ucIndex)
{
    VSIM_KEYDATA_STRU                   stKeyData;
    VOS_VOID                           *pOutputData;
    VOS_UINT32                          ulOutputLen;

    /* �������� */
    if (gucAtParaIndex > 1)
    {
        AT_WARN_LOG("At_SetHvsDHPara: Para too much.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����ַ���Ϊ�� */
    if ((0 == gastAtParaList[0].usParaLen)
        ||(1 == (gastAtParaList[0].usParaLen%2)))
    {
        AT_WARN_LOG("At_SetHvsDHPara: Para Len Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pOutputData = PS_MEM_ALLOC(WUEPS_PID_AT, gastAtParaList[0].usParaLen);

    if (VOS_NULL_PTR == pOutputData)
    {
        AT_WARN_LOG("At_SetHvsDHPara: PS_MEM_ALLOC Error.");
        return AT_ERROR;
    }

    /* ����������Կ���н��� */
    ulOutputLen = At_Base16Decode((VOS_CHAR *)gastAtParaList[0].aucPara, gastAtParaList[0].usParaLen, pOutputData);

    /* ���ȳ������ֵ */
    if (VSIM_KEYLEN_MAX < ulOutputLen)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

        AT_WARN_LOG("At_SetHvsDHPara: Result Data too Long.");

        return AT_CME_INCORRECT_PARAMETERS;
    }

    PS_MEM_CPY(stKeyData.aucKey, pOutputData, ulOutputLen);

    stKeyData.ulKeyLen = ulOutputLen;

    /* �ͷ���ʹ������ڴ� */
    PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

    if (TAF_SUCCESS == SI_PIH_HvsDHSet(gastAtClientTab[ucIndex].usClientId, 0, &stKeyData))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVSDH_SET;

        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }

    AT_WARN_LOG("At_SetHvsDHPara: SI_PIH_HvsDHSet Error.");

    return AT_ERROR;
}
/*****************************************************************************
 Prototype      : At_TestHvsDHPara
 Description    : ^HVSDH
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2013-03-20
    Author      : g47350
    Modification: Created function
*****************************************************************************/
VOS_UINT32 At_TestHvsDHPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: 1",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : AT_HvsDHQueryCnf
 Description    : HVSDH��ѯ�����
 Input          : pstEvent --- ��Ϣ����
 Output         :
 Return Value   : ���ݳ���
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT16 AT_HvsDHQueryCnf(SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT16 usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"^HVSDH:");

    /* <algrithm>, */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d,",pstEvent->PIHEvent.HvsDHCnf.enAlgorithm);

    /* <c_pkey>, */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    usLength += (VOS_UINT16)At_Hex2Base16(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                pstEvent->PIHEvent.HvsDHCnf.stCkey.aucKey, (VOS_UINT16)pstEvent->PIHEvent.HvsDHCnf.stCkey.ulKeyLen);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\",");

    /* <s_pkey>, */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    if (0 != pstEvent->PIHEvent.HvsDHCnf.stSkey.ulKeyLen)
    {
        usLength += (VOS_UINT16)At_Hex2Base16(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                    pstEvent->PIHEvent.HvsDHCnf.stSkey.aucKey, (VOS_UINT16)pstEvent->PIHEvent.HvsDHCnf.stSkey.ulKeyLen);
    }
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    return usLength;
}

VOS_UINT32 At_SetHvpDHPara(VOS_UINT8 ucIndex)
{
    DRV_AGENT_HVPDH_REQ_STRU            stHvpdhReq;
    VOS_VOID                           *pOutputData;
    VOS_UINT32                          ulOutputLen;
    VOS_UINT32                          ulResult;

    /* �������� */
    if(gucAtParaIndex > 2)
    {
        AT_WARN_LOG("At_SetHvpDHPara: Para too much.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* �����ַ���Ϊ�գ�������ԿΪbase16���룬�ʱ���Ϊż������ */
    if ((0 == gastAtParaList[0].usParaLen)
        || (0 == gastAtParaList[1].usParaLen)
        || (1 == (gastAtParaList[1].usParaLen % 2)))
    {
        AT_WARN_LOG("At_SetHvpDHPara: Para Len Error.");
        return AT_CME_INCORRECT_PARAMETERS;
    }

    pOutputData = PS_MEM_ALLOC(WUEPS_PID_AT, gastAtParaList[1].usParaLen);
    if (VOS_NULL_PTR == pOutputData)
    {
        AT_WARN_LOG("At_SetHvpDHPara: PS_MEM_ALLOC Error.");
        return AT_ERROR;
    }

    /* ����Կ���н��� */
    ulOutputLen = At_Base16Decode((VOS_CHAR *)gastAtParaList[1].aucPara, gastAtParaList[1].usParaLen, pOutputData);

    /* ���ȳ������ֵ */
    if ( (DRV_AGENT_DH_KEY_SERVER_PUBLIC_KEY == gastAtParaList[0].ulParaValue)
       ||(DRV_AGENT_DH_KEY_MODEM_PUBLIC_KEY == gastAtParaList[0].ulParaValue) )
    {
        if (VSIM_DH_PUBIIC_KEY < ulOutputLen)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

            AT_WARN_LOG("At_SetHvpDHPara: public key too Long.");

            return AT_CME_INCORRECT_PARAMETERS;
        }
    }
    else
    {
        if (VSIM_DH_PRIVATE_KEY < ulOutputLen)
        {
            PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

            AT_WARN_LOG("At_SetHvpDHPara: private key too Long.");

            return AT_CME_INCORRECT_PARAMETERS;
        }
    }

    stHvpdhReq.enKeyType = gastAtParaList[0].ulParaValue;
    stHvpdhReq.ulKeyLen  = ulOutputLen;
    PS_MEM_CPY(stHvpdhReq.aucKey, pOutputData, ulOutputLen);

    /* �ͷ���ʹ������ڴ� */
    PS_MEM_FREE(WUEPS_PID_AT, pOutputData);

    /* ���Ϳ����Ϣ��C��, �����Ȩ���� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_HVPDH_REQ,
                                      &stHvpdhReq,
                                      sizeof(stHvpdhReq),
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_SetHvpDHPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HVPDH_SET;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 At_TestHvpDHPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "^HVPDH: (0,2)");
    return AT_OK;
}

#endif/*end (FEATURE_ON == MBB_FEATURE_VSIM_HUK)*/
#endif  /*end of (FEATURE_VSIM == FEATURE_ON)*/

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 Prototype      : AT_UiccAuthCnf
 Description    : �����
 Input          : pstEvent --- ��Ϣ����
 Output         :
 Return Value   : ���ݳ���
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT16 AT_UiccAuthCnf(TAF_UINT8 ucIndex, SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT16 usLength = 0;

    if (AT_CMD_UICCAUTH_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"^UICCAUTH:");

        /* <result> */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d",pstEvent->PIHEvent.UiccAuthCnf.enStatus);

        if (SI_PIH_AUTH_SUCCESS == pstEvent->PIHEvent.UiccAuthCnf.enStatus)
        {
            /* ,<Res> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,",\"");
            usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, &pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucAuthRes[1], pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucAuthRes[0]);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

            if (SI_PIH_UICCAUTH_AKA == pstEvent->PIHEvent.UiccAuthCnf.enAuthType)
            {
                /* ,<ck> */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,",\"");
                usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, &pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucCK[1], pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucCK[0]);
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

                /* ,<ik> */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,",\"");
                usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, &pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucIK[1], pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucIK[0]);
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
            }
        }

        if (SI_PIH_AUTH_SYNC == pstEvent->PIHEvent.UiccAuthCnf.enStatus)
        {
            /* ,"","","",<autn> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,",\"\",\"\",\"\",\"");
            usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, &pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucAuts[1], pstEvent->PIHEvent.UiccAuthCnf.stAkaData.aucAuts[0]);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
        }
    }

    if (AT_CMD_KSNAFAUTH_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"^KSNAFAUTH:");

        /* <status> */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"%d",pstEvent->PIHEvent.UiccAuthCnf.enStatus);

        if (VOS_NULL != pstEvent->PIHEvent.UiccAuthCnf.stNAFData.aucKs_ext_NAF[0])
        {
            /* ,<ks_Naf> */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,",\"");
            usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, &pstEvent->PIHEvent.UiccAuthCnf.stNAFData.aucKs_ext_NAF[1], pstEvent->PIHEvent.UiccAuthCnf.stNAFData.aucKs_ext_NAF[0]);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
        }
    }

    return usLength;
}

/*****************************************************************************
 Prototype      : AT_UiccAccessFileCnf
 Description    : �����
 Input          : pstEvent --- ��Ϣ����
 Output         :
 Return Value   : ���ݳ���
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT16 AT_UiccAccessFileCnf(TAF_UINT8 ucIndex, SI_PIH_EVENT_INFO_STRU *pstEvent)
{
    VOS_UINT16      usLength = 0;

    if ((0 != pstEvent->PIHEvent.UiccAcsFileCnf.ulDataLen)
        && (SI_PIH_ACCESS_READ == pstEvent->PIHEvent.UiccAcsFileCnf.enCmdType))
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"^CURSM:");

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
        usLength += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN, (TAF_INT8 *)pgucAtSndCodeAddr, (TAF_UINT8 *)pgucAtSndCodeAddr+usLength, pstEvent->PIHEvent.UiccAcsFileCnf.aucCommand, (VOS_UINT16)pstEvent->PIHEvent.UiccAcsFileCnf.ulDataLen);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,(VOS_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    }

    return usLength;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

