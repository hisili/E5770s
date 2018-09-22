/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : AtCmdMsgProc.c
  Author       : ---
  Version      : V100R001
  Date         : 2005-04-19
  Description  : ��C�ļ�������---ģ���ʵ��
  Function List:
            At_PidInit
            At_CmdMsgProc

  History      :
  1. Date:2005-04-19
     Author: ---
     Modification:Create

************************************************************************/



/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "ATCmdProc.h"
#include "siapppb.h"
#include "siappstk.h"
#include "AtMsgPrint.h"
#include "DrvInterface.h"
#include "AtPhyInterface.h"
#include "omrl.h"
#include "PppInterface.h"
#include "AtDataProc.h"
#include "AtCmdMsgProc.h"
#include "TafDrvAgent.h"
#include "AtCmdMsgProc.h"
#include "AtEventReport.h"
#include "AtRabmInterface.h"
#include "AtRnicInterface.h"
#include "AtDeviceCmd.h"
#include "AtInit.h"
#include "at_common.h"
#include "AcpuReset.h"

#include "AtInternalMsg.h"

#if (FEATURE_ON==FEATURE_LTE)
#include "msp_nvim.h"

#include "LPsNvInterface.h"
#include "LNvCommon.h"
#endif

#include "MtaPhyInterface.h"

#include "OmApi.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "GasNvInterface.h"
#include "AppVcApi.h"

#include "AtCmdImsProc.h"

#include  "product_config.h"

#include  "AtCmdFtmProc.h"

#if (FEATURE_ON==FEATURE_LTE)
#include "at_lte_common.h"
#endif
/*#if (FEATURE_ON == MBB_WPG_COMMON)*/
#include "MbbPsCsCommon.h"
/*#endif*/
#if (FEATURE_ON == MBB_COMMON)
#include "drv_dload.h"
#include "bsp_version.h"
#endif
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_CMDMSGPROC_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


/*****************************************************************************
  2 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
   3 ȫ�ֱ�������
*****************************************************************************/
/* Added by L60609 for AT Project��2011-10-04,  Begin*/

/*AT ģ�鴦������AT AGENT��Ϣ������Ӧ��*/
const AT_PROC_MSG_FROM_DRV_AGENT_STRU g_astAtProcMsgFromDrvAgentTab[]=
{
    /* ��ϢID */                            /* ��Ϣ������ */
    {DRV_AGENT_MSID_QRY_CNF,                AT_RcvDrvAgentMsidQryCnf},
    {DRV_AGENT_GAS_MNTN_CMD_RSP,            AT_RcvDrvAgentGasMntnCmdRsp},
    {DRV_AGENT_HARDWARE_QRY_RSP,            AT_RcvDrvAgentHardwareQryRsp},
    {DRV_AGENT_FULL_HARDWARE_QRY_RSP,       AT_RcvDrvAgentFullHardwareQryRsp},
    {DRV_AGENT_RXDIV_SET_CNF,               AT_RcvDrvAgentSetRxdivCnf},
    {DRV_AGENT_RXDIV_QRY_CNF,               AT_RcvDrvAgentQryRxdivCnf},
    {DRV_AGENT_SIMLOCK_SET_CNF,             AT_RcvDrvAgentSetSimlockCnf},


    {DRV_AGENT_VERTIME_QRY_CNF,             AT_RcvDrvAgentVertimeQryRsp},
    {DRV_AGENT_YJCX_SET_CNF,                AT_RcvDrvAgentYjcxSetCnf},
    {DRV_AGENT_YJCX_QRY_CNF,                AT_RcvDrvAgentYjcxQryCnf},
    {DRV_AGENT_GPIOPL_SET_CNF,              AT_RcvDrvAgentSetGpioplRsp},
    {DRV_AGENT_GPIOPL_QRY_CNF,              AT_RcvDrvAgentQryGpioplRsp},
    {DRV_AGENT_DATALOCK_SET_CNF,            AT_RcvDrvAgentSetDatalockRsp},
    {DRV_AGENT_TBATVOLT_QRY_CNF,            AT_RcvDrvAgentQryTbatvoltRsp},
    {DRV_AGENT_VERSION_QRY_CNF,             AT_RcvDrvAgentQryVersionRsp},
    {DRV_AGENT_SECUBOOT_QRY_CNF,            AT_RcvDrvAgentQrySecuBootRsp},
    {DRV_AGENT_FCHAN_SET_CNF,               AT_RcvDrvAgentSetFchanRsp},
    {DRV_AGENT_SFEATURE_QRY_CNF,            AT_RcvDrvAgentQrySfeatureRsp},
    {DRV_AGENT_PRODTYPE_QRY_CNF,            AT_RcvDrvAgentQryProdtypeRsp},

    /* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, begin */
    {DRV_AGENT_CPULOAD_QRY_CNF,             AT_RcvDrvAgentCpuloadQryRsp},
    {DRV_AGENT_MFREELOCKSIZE_QRY_CNF,       AT_RcvDrvAgentMfreelocksizeQryRsp},
    /* Added by ��ӳ��/f62575 for CPULOAD&MFREELOCKSIZE�����������C��, 2011/11/15, end */
    {DRV_AGENT_MEMINFO_QRY_CNF,             AT_RcvDrvAgentMemInfoQryRsp},
    /* Added by f62575 for AT Project, 2011-10-04,  Begin */
    {DRV_AGENT_DLOADINFO_QRY_CNF,           AT_RcvDrvAgentDloadInfoQryRsp},
    {DRV_AGENT_FLASHINFO_QRY_CNF,           AT_RcvDrvAgentFlashInfoQryRsp},
    {DRV_AGENT_AUTHORITYVER_QRY_CNF,        AT_RcvDrvAgentAuthorityVerQryRsp},
    {DRV_AGENT_AUTHORITYID_QRY_CNF,         AT_RcvDrvAgentAuthorityIdQryRsp},
    {DRV_AGENT_AUTHVER_QRY_CNF,             AT_RcvDrvAgentAuthVerQryRsp},
    {DRV_AGENT_GODLOAD_SET_CNF,             AT_RcvDrvAgentGodloadSetRsp},

    {DRV_AGENT_PFVER_QRY_CNF,               AT_RcvDrvAgentPfverQryRsp},
    {DRV_AGENT_HWNATQRY_QRY_CNF,            AT_RcvDrvAgentHwnatQryRsp},
    {DRV_AGENT_SDLOAD_SET_CNF,              AT_RcvDrvAgentSdloadSetRsp},
    {DRV_AGENT_APPDMVER_QRY_CNF,            AT_RcvDrvAgentAppdmverQryRsp},
    {DRV_AGENT_DLOADVER_QRY_CNF,            AT_RcvDrvAgentDloadverQryRsp},
    /* Added by f62575 for AT Project, 2011-10-04,  End */

    /* Added by l60609 for AT Project, 2011-11-03,  Begin */
    {DRV_AGENT_IMSICHG_QRY_CNF,             AT_RcvDrvAgentImsiChgQryRsp},
    {DRV_AGENT_INFORBU_SET_CNF,             AT_RcvDrvAgentInfoRbuSetRsp},
#if ( FEATURE_ON == FEATURE_LTE )
    {DRV_AGENT_INFORRS_SET_CNF,             AT_RcvDrvAgentInfoRrsSetRsp},
#endif
    {DRV_AGENT_CPNN_QRY_CNF,                AT_RcvDrvAgentCpnnQryRsp},
    {DRV_AGENT_CPNN_TEST_CNF,               AT_RcvDrvAgentCpnnTestRsp},
    {DRV_AGENT_NVBACKUP_SET_CNF,            AT_RcvDrvAgentNvBackupSetRsp},
    /* Added by l60609 for AT Project, 2011-11-03,  Begin */

    {DRV_AGENT_NVRESTORE_SET_CNF,           AT_RcvDrvAgentSetNvRestoreCnf},
    {DRV_AGENT_NVRSTSTTS_QRY_CNF,           AT_RcvDrvAgentQryNvRestoreRstCnf},
    {DRV_AGENT_NVRESTORE_MANU_DEFAULT_CNF,  AT_RcvDrvAgentNvRestoreManuDefaultRsp},

    {DRV_AGENT_ADC_SET_CNF,                 AT_RcvDrvAgentSetAdcRsp},
    /* Added by f62575 for SMALL IMAGE, 2012-1-3, Begin   */
    {DRV_AGENT_TSELRF_SET_CNF,              AT_RcvDrvAgentTseLrfSetRsp},
    {DRV_AGENT_HKADC_GET_CNF,               AT_RcvDrvAgentHkAdcGetRsp},
    /* Added by f62575 for SMALL IMAGE, 2012-1-3, end   */

    {DRV_AGENT_TBAT_QRY_CNF,                AT_RcvDrvAgentQryTbatRsp},
    /* Added by f62575 for B050 Project, 2012-2-3, Begin   */
    {DRV_AGENT_SECUBOOT_SET_CNF,            AT_RcvDrvAgentSetSecuBootRsp},
    /* Added by f62575 for B050 Project, 2012-2-3, end   */
    /* Added by l60609 for B060 Project, 2012-2-21, Begin   */
#if (FEATURE_ON == FEATURE_SECURITY_SHELL)
    {DRV_AGENT_SPWORD_SET_CNF,              AT_RcvDrvAgentSetSpwordRsp},
#endif
    /* Added by l60609 for B060 Project, 2012-2-21, End   */

    {DRV_AGENT_NVBACKUPSTAT_QRY_CNF,        AT_RcvDrvAgentNvBackupStatQryRsp},
    {DRV_AGENT_NANDBBC_QRY_CNF,             AT_RcvDrvAgentNandBadBlockQryRsp},
    {DRV_AGENT_NANDVER_QRY_CNF,             AT_RcvDrvAgentNandDevInfoQryRsp},
    {DRV_AGENT_CHIPTEMP_QRY_CNF,            AT_RcvDrvAgentChipTempQryRsp},

    /* Added by h59254 for C50 SAR Project, 2012/03/10, begin */
    {DRV_AGENT_ANTSTATE_QRY_IND,            AT_RcvDrvAgentAntStateIndRsp},
    /* Added by h59254 for C50 SAR Project, 2012/03/10, end */

    {DRV_AGENT_MAX_LOCK_TIMES_SET_CNF,      AT_RcvDrvAgentSetMaxLockTmsRsp},

    {DRV_AGENT_AP_SIMST_SET_CNF,            AT_RcvDrvAgentSetApSimstRsp},

    {DRV_AGENT_HUK_SET_CNF,                 AT_RcvDrvAgentHukSetCnf},
    {DRV_AGENT_FACAUTHPUBKEY_SET_CNF,       AT_RcvDrvAgentFacAuthPubkeySetCnf},
    {DRV_AGENT_IDENTIFYSTART_SET_CNF,       AT_RcvDrvAgentIdentifyStartSetCnf},
    {DRV_AGENT_IDENTIFYEND_SET_CNF,         AT_RcvDrvAgentIdentifyEndSetCnf},
    {DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF,    AT_RcvDrvAgentSimlockDataWriteSetCnf},
    {DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF,    AT_RcvDrvAgentPhoneSimlockInfoQryCnf},
    {DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF,     AT_RcvDrvAgentSimlockDataReadQryCnf},
    {DRV_AGENT_PHONEPHYNUM_SET_CNF,         AT_RcvDrvAgentPhonePhynumSetCnf},
    {DRV_AGENT_PHONEPHYNUM_QRY_CNF,         AT_RcvDrvAgentPhonePhynumQryCnf},
    {DRV_AGENT_PORTCTRLTMP_SET_CNF,         AT_RcvDrvAgentPortctrlTmpSetCnf},
    {DRV_AGENT_PORTATTRIBSET_SET_CNF,       AT_RcvDrvAgentPortAttribSetCnf},
    {DRV_AGENT_PORTATTRIBSET_QRY_CNF,       AT_RcvDrvAgentPortAttribSetQryCnf},
    {DRV_AGENT_OPWORD_SET_CNF,              AT_RcvDrvAgentOpwordSetCnf},

    {DRV_AGENT_SWVER_SET_CNF,               AT_RcvDrvAgentSwverSetCnf},

#if(FEATURE_ON == MBB_COMMON)
    {DRV_AGENT_QRY_SIM_STA_CNF,               AT_RcvDrvAgentSimQryCnf},
    {DRV_AGENT_DATALOCK_VERIFY_CNF,            AT_RcvDrvAgentVerifyDatalockRsp},
#endif

#if (FEATURE_ON == FEATURE_VSIM)
    /* Added by L47619 for V9R1 vSIM Project, 2013-8-27, begin */
    {DRV_AGENT_HVPDH_CNF,                   AT_RcvDrvAgentHvpdhSetCnf},
    /* Added by L47619 for V9R1 vSIM Project, 2013-8-27, end */
#endif

    {DRV_AGENT_NVMANUFACTUREEXT_SET_CNF,    AT_RcvNvManufactureExtSetCnf},

    {DRV_AGENT_ANTSWITCH_SET_CNF,           AT_RcvDrvAgentAntSwitchSetCnf},
    {DRV_AGENT_ANTSWITCH_QRY_CNF,           AT_RcvDrvAgentAntSwitchQryCnf},
/*begin add by wanghaijie for simlock 3.0*/
#if (FEATURE_ON == MBB_SIMLOCK_THREE)
    {DRV_AGENT_HWLOCK_SET_CNF,DRVAGENT_RcvDrvAgentHWLockSetCnf},
    {DRV_AGENT_HWLOCK_QURY_CNF,DRVAGENT_RcvDrvAgentHWLockQRYCnf},
#endif
/*end  add by wanghaijie for simlock 3.0*/
};

/* Added by L60609 for AT Project��2011-10-04,  End*/

/* ATģ�鴦������MTA��Ϣ������Ӧ��*/
const AT_PROC_MSG_FROM_MTA_STRU g_astAtProcMsgFromMtaTab[]=
{
    /* ��ϢID */                            /* ��Ϣ������ */
    {ID_MTA_AT_CPOS_SET_CNF,                AT_RcvMtaCposSetCnf},
    {ID_MTA_AT_CPOSR_IND,                   AT_RcvMtaCposrInd},
    {ID_MTA_AT_XCPOSRRPT_IND,               AT_RcvMtaXcposrRptInd},
    {ID_MTA_AT_CGPSCLOCK_SET_CNF,           AT_RcvMtaCgpsClockSetCnf},

    {ID_MTA_AT_APSEC_SET_CNF,               AT_RcvMtaApSecSetCnf},

    {ID_MTA_AT_SIMLOCKUNLOCK_SET_CNF,       AT_RcvMtaSimlockUnlockSetCnf},

    {ID_MTA_AT_QRY_NMR_CNF,                 AT_RcvMtaQryNmrCnf},

    {ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,        AT_RcvMtaWrrAutotestQryCnf},
    {ID_MTA_AT_WRR_CELLINFO_QRY_CNF,        AT_RcvMtaWrrCellinfoQryCnf},
    {ID_MTA_AT_WRR_MEANRPT_QRY_CNF,         AT_RcvMtaWrrMeanrptQryCnf},
    {ID_MTA_AT_WRR_FREQLOCK_SET_CNF,        AT_RcvMtaWrrFreqLockSetCnf},
    {ID_MTA_AT_WRR_RRC_VERSION_SET_CNF,     AT_RcvMtaWrrRrcVersionSetCnf},
    {ID_MTA_AT_WRR_CELLSRH_SET_CNF,         AT_RcvMtaWrrCellSrhSetCnf},
    {ID_MTA_AT_WRR_FREQLOCK_QRY_CNF,        AT_RcvMtaWrrFreqLockQryCnf},
    {ID_MTA_AT_WRR_RRC_VERSION_QRY_CNF,     AT_RcvMtaWrrRrcVersionQryCnf},
    {ID_MTA_AT_WRR_CELLSRH_QRY_CNF,         AT_RcvMtaWrrCellSrhQryCnf},

    {ID_MTA_AT_BODY_SAR_SET_CNF,           AT_RcvMtaBodySarSetCnf},

    {ID_MTA_AT_CURC_QRY_CNF,                AT_RcvMtaQryCurcCnf},
    {ID_MTA_AT_UNSOLICITED_RPT_SET_CNF,     AT_RcvMtaSetUnsolicitedRptCnf},
    {ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF,     AT_RcvMtaQryUnsolicitedRptCnf},

    {ID_MTA_AT_IMEI_VERIFY_QRY_CNF,         AT_RcvMtaImeiVerifyQryCnf},
    {ID_MTA_AT_CGSN_QRY_CNF,                AT_RcvMtaCgsnQryCnf},
    {ID_MTA_AT_NCELL_MONITOR_SET_CNF,       AT_RcvMtaSetNCellMonitorCnf},
    {ID_MTA_AT_NCELL_MONITOR_QRY_CNF,       AT_RcvMtaQryNCellMonitorCnf},
    {ID_MTA_AT_NCELL_MONITOR_IND,           AT_RcvMtaNCellMonitorInd},

    {ID_MTA_AT_REFCLKFREQ_SET_CNF,          AT_RcvMtaRefclkfreqSetCnf},
    {ID_MTA_AT_REFCLKFREQ_QRY_CNF,          AT_RcvMtaRefclkfreqQryCnf},
    {ID_MTA_AT_REFCLKFREQ_IND,              AT_RcvMtaRefclkfreqInd},

    {ID_MTA_AT_HANDLEDECT_SET_CNF,          AT_RcvMtaHandleDectSetCnf},
    {ID_MTA_AT_HANDLEDECT_QRY_CNF,          AT_RcvMtaHandleDectQryCnf},

    {ID_MTA_AT_PS_TRANSFER_IND,             AT_RcvMtaPsTransferInd},

    {ID_MTA_AT_ECID_SET_CNF,                AT_RcvMtaEcidSetCnf},

    {ID_MTA_AT_MIPICLK_QRY_CNF,             AT_RcvMtaMipiInfoCnf},
    {ID_MTA_AT_MIPICLK_INFO_IND,            AT_RcvMtaMipiInfoInd},
    {ID_MTA_AT_SET_DPDTTEST_FLAG_CNF,       AT_RcvMtaSetDpdtTestFlagCnf},
    {ID_MTA_AT_SET_DPDT_VALUE_CNF,          AT_RcvMtaSetDpdtValueCnf},
    {ID_MTA_AT_QRY_DPDT_VALUE_CNF,          AT_RcvMtaQryDpdtValueCnf},

    {ID_MTA_AT_SET_JAM_DETECT_CNF,          AT_RcvMtaSetJamDetectCnf},
    {ID_MTA_AT_JAM_DETECT_IND,              AT_RcvMtaJamDetectInd},

    {ID_MTA_AT_SET_FREQ_LOCK_CNF,           AT_RcvMtaSetRatFreqLockCnf},
#ifdef BSP_CONFIG_BOARD_E5573S_156
    {ID_MTA_AT_WRR_CELLINFO_CNF,        AT_RcvMtaWrrCellinfoCnf},
#endif
#if (FEATURE_ON == MBB_WPG_LTXPOWER)
    {ID_MTA_AT_LTXPOWER_QRY_CNF,       AT_RcvMtaTxPowerQryCnf},
#endif/*end (FEATURE_ON == MBB_WPG_LTXPOWER)*/
};

const AT_PROC_MSG_FROM_MMA_STRU g_astAtProcMsgFromMmaTab[]=
{
    /* ��ϢID */                            /* ��Ϣ������ */
#ifndef __PS_WIN32_RECUR__
    {AT_MMA_OM_MAINTAIN_INFO_IND,       AT_RcvMmaOmMaintainInfoInd},
#endif

    {AT_MMA_USIM_STATUS_IND,            AT_RcvAtMmaUsimStatusInd},
    {AT_MMA_CRPN_QUERY_RSP,             AT_RcvMmaCrpnQueryRsp},
    {AT_MMA_CMM_SET_CMD_RSP,            AT_RcvMmaCmmSetCmdRsp},
    {AT_MMA_CIPHER_INFO_QUERY_CNF,      AT_RcvMmaCipherInfoQueryCnf},
    {AT_MMA_LOCATION_INFO_QUERY_CNF,    AT_RcvMmaLocInfoQueryCnf},
    {AT_MMA_SIMLOCK_STAUS_QUERY_CNF,    AT_RcvSimLockQryRsp},
    {AT_MMA_AC_INFO_QUERY_CNF,          AT_RcvMmaAcInfoQueryCnf},
    {AT_MMA_CERSSI_INFO_QUERY_CNF,      AT_RcvMmaCerssiInfoQueryCnf},
    {AT_MMA_COPN_INFO_QUERY_CNF,        AT_RcvMmaCopnInfoQueryCnf},
    {AT_MMA_SIM_INSERT_RSP,             AT_RcvMmaSimInsertRsp},
    {AT_MMA_CPOL_INFO_QUERY_CNF,        AT_QryParaRspPrefPlmnProc},
    {ID_TAF_MMA_SYS_CFG_SET_CNF,        AT_RcvMmaSysCfgSetCnf},
    {ID_TAF_MMA_PHONE_MODE_SET_CNF,     AT_RcvMmaPhoneModeSetCnf},
    {ID_TAF_MMA_DETACH_CNF,             AT_RcvMmaDetachCnf},
#if (FEATURE_ON == MBB_FEATURE_FAKE_ON_OFF)
    {ID_TAF_MMA_CFUN_SIM_STATUS_IND,    AT_RcvMmaCfunSimStatusInd},
#endif/*FEATURE_ON == MBB_FEATURE_FAKE_ON_OFF*/
};

/* AT������������(����AT�������������)��
   ���øû��������ԭ��:���������ڵ���At_CmdStreamPreProc�ӿ�ʱ��ĳЩ������(��ֱ��ʹ�ó����ն˷���AT����),���
   ����AT������һ���ַ�Ϊ��λ���͵�AT����Ϣ�����У�����AT����Ϣ���������������帴λ��*/
AT_DATA_STREAM_BUFFER_STRU              g_aucAtDataBuff[AT_MAX_CLIENT_NUM];

/*CREG/CGREG��<CI>����4�ֽ��ϱ��Ƿ�ʹ��(VDF����)*/

AT_CLIENT_MANAGE_STRU                   gastAtClientTab[AT_MAX_CLIENT_NUM];

TAF_UINT32                              gulPBPrintTag = VOS_FALSE;

extern VOS_BOOL                         g_bSetFlg;
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
VOS_UINT8                g_TempprtEvent_flag = AT_ANT_TEMPPRTEVENT_L;
#endif

/*****************************************************************************
   3 ��������������
*****************************************************************************/

extern VOS_UINT32    AT_ProcTempprtEventInd(
    TEMP_PROTECT_EVENT_AT_IND_STRU     *pstMsg
);

/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/

#ifdef __PS_WIN32_RECUR__


TAF_VOID AT_RestoreClientData(
    NAS_AT_SDT_AT_CLIENT_TABLE_STRU    *pstAtClientData
)
{
    TAF_UINT8                                       ucLoop;

    for (ucLoop = 0; ucLoop < AT_MAX_CLIENT_NUM; ucLoop++)
    {
        gastAtClientTab[ucLoop].usClientId      = pstAtClientData->gastAtClientTab[ucLoop].usClientId;
        gastAtClientTab[ucLoop].opId            = pstAtClientData->gastAtClientTab[ucLoop].opId;
        gastAtClientTab[ucLoop].ucUsed          = pstAtClientData->gastAtClientTab[ucLoop].ucUsed;
        gastAtClientTab[ucLoop].UserType        = pstAtClientData->gastAtClientTab[ucLoop].UserType;
        gastAtClientTab[ucLoop].Mode            = pstAtClientData->gastAtClientTab[ucLoop].Mode;
        gastAtClientTab[ucLoop].IndMode         = pstAtClientData->gastAtClientTab[ucLoop].IndMode;
    }

    return;
}


TAF_UINT32 AT_RestoreContextData(
    AT_MSG_STRU                         *pMsg
)
{
    NAS_AT_SDT_AT_PART_ST                  *pRcvMsgCB     = VOS_NULL_PTR;
    NAS_AT_OUTSIDE_RUNNING_CONTEXT_PART_ST *pstOutsideCtx = VOS_NULL_PTR;
    AT_MODEM_SMS_CTX_STRU                  *pstSmsCtx     = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                    enModemId;

    pRcvMsgCB     = (NAS_AT_SDT_AT_PART_ST *)pMsg;

    if (AT_PC_REPLAY_MSG == pRcvMsgCB->ucType)
    {
        for (enModemId = 0; enModemId < MODEM_ID_BUTT; enModemId++)
        {
            pstSmsCtx                       = AT_GetModemSmsCtxAddrFromModemId(enModemId);
            pstOutsideCtx                   = &pRcvMsgCB->astOutsideCtx[enModemId];

            gucAtCscsType                   = pstOutsideCtx->gucAtCscsType;
            pstSmsCtx->ucCsdhType           = pstOutsideCtx->gucAtCsdhType;
            g_OpId                          = pstOutsideCtx->g_OpId;
            pstSmsCtx->enCsmsMsgVersion     = pstOutsideCtx->g_enAtCsmsMsgVersion;
            pstSmsCtx->enCmgfMsgFormat      = pstOutsideCtx->g_enAtCmgfMsgFormat;

            PS_MEM_CPY(&(pstSmsCtx->stCnmiType),
                       &pstOutsideCtx->gstAtCnmiType,
                       sizeof(pstSmsCtx->stCnmiType));

            PS_MEM_CPY(&(pstSmsCtx->stCgsmsSendDomain),
                         &pstOutsideCtx->g_stAtCgsmsSendDomain,
                         sizeof(pstSmsCtx->stCgsmsSendDomain));

            PS_MEM_CPY(&(pstSmsCtx->stCscaCsmpInfo),
                         &pstOutsideCtx->g_stAtCscaCsmpInfo,
                         sizeof(pstSmsCtx->stCscaCsmpInfo));

            PS_MEM_CPY(&(pstSmsCtx->stCpmsInfo),
                         &pstOutsideCtx->g_stAtCpmsInfo,
                         sizeof(pstSmsCtx->stCpmsInfo));

            AT_INFO_LOG("MSG: AT_RestoreContextData data is restored.");
        }
    }

    return AT_OK;
}
#endif
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


TAF_VOID At_MmaMsgProc(
    MSG_HEADER_STRU                     *pstMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /*��g_astAtProcMsgFromMmaTab�л�ȡ��Ϣ����*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromMmaTab)/sizeof(AT_PROC_MSG_FROM_MMA_STRU);

    /*g_astAtProcMsgFromMtaTab���������Ϣ�ַ�*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromMmaTab[i].ulMsgName == pstMsg->ulMsgName)
        {
            ulRst = g_astAtProcMsgFromMmaTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_MmaMsgProc: Msg Proc Err!");
            }

            return;
        }
    }

    /*û���ҵ�ƥ�����Ϣ*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_MmaMsgProc: Msg Id is invalid!");
    }

    return;
}


TAF_VOID At_EventMsgProc(MN_AT_IND_EVT_STRU *pMsg)
{
    AT_USB_DEBUG_PRINT_1(pMsg->usMsgName);

    switch(pMsg->usMsgName)
    {
        case MN_CALLBACK_MSG:
            At_SmsMsgProc(pMsg, pMsg->usLen);
            return;

        case MN_CALLBACK_SET:
            At_SetMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_QRY:
            At_QryMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_PS_CALL:
            /* PS���¼����� */
            AT_RcvTafPsEvt((TAF_PS_EVT_STRU*)pMsg);
            return;

        case MN_CALLBACK_DATA_STATUS:
            At_DataStatusMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_CS_CALL:
            At_CsMsgProc(pMsg,pMsg->usLen);
            return;

        case MN_CALLBACK_SS:
            At_SsMsgProc(pMsg->aucContent, pMsg->usLen);
            return;

        case MN_CALLBACK_PHONE:
            At_PhMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        case MN_CALLBACK_PHONE_BOOK:
            At_TAFPbMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        case MN_CALLBACK_CMD_CNF:
            At_CmdCnfMsgProc(pMsg->aucContent, pMsg->usLen);
            break;

        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
        case MN_CALLBACK_VOICE_CONTROL:
            At_VcMsgProc(pMsg, pMsg->usLen);
            break;
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

        case MN_CALLBACK_LOG_PRINT:
            AT_LogPrintMsgProc((TAF_MNTN_LOG_PRINT_STRU *)pMsg);
            break;

        default:
            AT_LOG1("At_MsgProc: invalid message name.", pMsg->usMsgName);
            return;
    }
}



VOS_BOOL AT_E5CheckRight(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    static VOS_BOOL                     bIsRight = VOS_FALSE;
    VOS_UINT8                           aucCmdTmp[20]; /* �����aucQuickCmd[]�ĳ��� */
    VOS_UINT8                           aucQuickCmd[] = "AT^OPENPORT=";
    VOS_UINT16                          usQuickCmdLen;
    VOS_UINT16                          usLeftLen;
    VOS_UINT8                           *pucPwdPos;
    VOS_CHAR                            acPassword[AT_RIGHT_PWD_LEN+1];
    VOS_UINT8                           *pucAtStart ;

    /* ��ǰȨ��δ����,ֱ�ӷ���  */
    if ( AT_RIGHT_OPEN_FLAG_CLOSE == g_stAtRightOpenFlg.enRightOpenFlg )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ���ȡ��Ȩ��,��ֱ�ӷ��� */
    if ( VOS_TRUE == bIsRight )
    {
        return VOS_TRUE;
    }

    /* SSCOM ������ַ���ǰ�� 0x0A */
    pucAtStart = pucData;
    while( (*pucAtStart != 'a') && (*pucAtStart != 'A')  )
    {
        pucAtStart++;
        if ( pucAtStart >= (pucData+usLen) )
        {
            /* δ�ҵ� a �� A break */
            break;
        }
    }
    usLen -= (VOS_UINT16)(pucAtStart - pucData);
    pucData = pucAtStart;

    /* ���ȷǷ�,ֱ�ӷ�����Ȩ�� */
    usQuickCmdLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR *)aucQuickCmd);
    if (usLen <= usQuickCmdLen)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_FALSE;
    }

    VOS_MemSet(aucCmdTmp, 0x00, sizeof(aucCmdTmp));
    VOS_MemCpy(aucCmdTmp, pucData, (SIZE_T)usQuickCmdLen);

    /* ����AT^OPENPORT����ֱ�ӷ�����Ȩ�� */
    if (0 != VOS_StrNiCmp((VOS_CHAR *)aucCmdTmp,
                          (VOS_CHAR *)aucQuickCmd,
                          (SIZE_T)usQuickCmdLen))
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return VOS_FALSE;
    }

    usLeftLen = usLen - usQuickCmdLen;
    pucPwdPos = pucData + usQuickCmdLen;

    if ( usLeftLen >= sizeof(aucCmdTmp) )
    {
        At_FormatResultData(ucIndex,AT_ERROR);
        return VOS_FALSE;
    }

    VOS_MemSet(aucCmdTmp, 0x00, sizeof(aucCmdTmp));
    VOS_MemCpy(aucCmdTmp, pucPwdPos, usLeftLen);

    PS_MEM_SET(acPassword,0x00,sizeof(acPassword));
    PS_MEM_CPY(acPassword,g_stAtRightOpenFlg.acPassword,sizeof(g_stAtRightOpenFlg.acPassword));

    /* �Ƚ������Ƿ���ͬ*/
    if ( 0 == VOS_StrCmp(acPassword, (VOS_CHAR *)aucCmdTmp))
    {
        /* �ϱ�OK����¼��Ȩ�� */
        At_FormatResultData(ucIndex, AT_OK);
        bIsRight = VOS_TRUE;
        return VOS_FALSE;
    }

    /* �ϱ�ERROR */
    At_FormatResultData(ucIndex, AT_ERROR);
    return VOS_FALSE;
}


TAF_VOID At_PppProtocolRelIndProc(AT_PPP_PROTOCOL_REL_IND_MSG_STRU *pMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usPppId;

    usPppId = pMsg->usPppId;
    ucIndex = gastAtPppIndexTab[usPppId];

    if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
      || (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType) )
    {
        if ( (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
          && (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
          && (AT_CMD_WAIT_PPP_PROTOCOL_REL_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) )
        {
            /* ��ATͨ���л�Ϊ����ģʽ */
            At_SetMode(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);
            AT_USB_WORK_MODE_PRINT(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);
            /* ֹͣ��ʱ�� */
            AT_STOP_TIMER_CMD_READY(ucIndex);

            /* �ظ�NO CARRIER */
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_NO_CARRIER);
        }
    }

    return;
}


VOS_VOID AT_ModemMscIndProc(AT_PPP_MODEM_MSC_IND_MSG_STRU *pMsg)
{
    VOS_UINT8                           ucIndex;

    ucIndex = pMsg->ucIndex;

    AT_MNTN_TraceInputMsc(ucIndex, (AT_DCE_MSC_STRU *)pMsg->aucMscInd);

    if ( (AT_MODEM_USER == gastAtClientTab[ucIndex].UserType)
      || (AT_HSUART_USER == gastAtClientTab[ucIndex].UserType) )
    {
        AT_ModemStatusPreProc(ucIndex, (AT_DCE_MSC_STRU *)pMsg->aucMscInd);
    }
    else
    {
        AT_WARN_LOG1("AT_ModemMscIndProc: index %d is unused", ucIndex);
    }

    return;
}

/*****************************************************************************
Prototype      : At_PppMsgProc
Description    : AT����PPP���͵���Ϣ
Input          : pMsg -- VOS��Ϣָ��
Output         : None
Return Value   : None
Calls          : None
Called By      : DOPRA

  History      : ---
  1.Date       : 2009-09-24
  Author       : L47619
  Modification : Created function
*****************************************************************************/
TAF_VOID At_PppMsgProc(MSG_HEADER_STRU *pMsg)
{
    switch  (pMsg->ulMsgName)
    {
        case AT_PPP_RELEASE_IND_MSG:
            At_PppReleaseIndProc(((AT_PPP_RELEASE_IND_MSG_STRU *)pMsg)->ucIndex);
            break;

        case AT_PPP_MODEM_MSC_IND_MSG:
            AT_ModemMscIndProc((AT_PPP_MODEM_MSC_IND_MSG_STRU *)pMsg);
            break;

        case AT_PPP_PROTOCOL_REL_IND_MSG:
            At_PppProtocolRelIndProc((AT_PPP_PROTOCOL_REL_IND_MSG_STRU *)pMsg);
            break;

        default:
            AT_LOG1("At_PppMsgProc: ulMsgName is abnormal!",pMsg->ulMsgName);
            break;
    }
}


VOS_UINT32  At_RfCfgCnfReturnErrProc(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRslt;

    switch (gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
       case AT_CMD_SET_FTXON:
           ulRslt = AT_FTXON_SET_FAIL;
           break;

       case AT_CMD_SET_FRXON:
           ulRslt = AT_FRXON_SET_FAIL;
           break;

       case AT_CMD_QUERY_RSSI:
           ulRslt = AT_FRSSI_OTHER_ERR;
           break;

       /* ���������ͷּ�ʱ�յ�DSP�ظ���������·��صĴ�������ͬ */
       case AT_CMD_SET_RXDIV:
       case AT_CMD_SET_RXPRI:
           ulRslt = AT_CME_RX_DIV_OTHER_ERR;
           break;

       default:
           ulRslt = AT_ERROR;
           break;
    }

   return ulRslt;
}


VOS_VOID  At_RfCfgCnfReturnSuccProc(
    VOS_UINT8                           ucIndex
)
{
    switch (gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        case AT_CMD_SET_FTXON:
            g_stAtDevCmdCtrl.ucTxOnOff = (VOS_UINT8)gastAtParaList[0].ulParaValue;

            /* ����Ǵ򿪷������������Ҫ��¼���һ��ִ�е��Ǵ򿪷�������Ǵ򿪽��ջ����� */
            if (AT_DSP_RF_SWITCH_ON == g_stAtDevCmdCtrl.ucTxOnOff)
            {
                g_stAtDevCmdCtrl.ucRxonOrTxon = AT_TXON_OPEN;
            }
            break;

        case AT_CMD_SET_FRXON:
            g_stAtDevCmdCtrl.ucRxOnOff = (VOS_UINT8)gastAtParaList[0].ulParaValue;

            /* ����Ǵ򿪽��ջ���������Ҫ��¼���һ��ִ�е��Ǵ򿪷�������Ǵ򿪽��ջ����� */
            if (AT_DSP_RF_SWITCH_ON == g_stAtDevCmdCtrl.ucRxOnOff)
            {
                g_stAtDevCmdCtrl.ucRxonOrTxon = AT_RXON_OPEN;
            }
            break;

        case AT_CMD_QUERY_RSSI:
            break;

        case AT_CMD_SET_RXDIV:
           if ((AT_OK == At_SaveRxDivPara(g_stAtDevCmdCtrl.usOrigBand, 1))
            && (AT_TMODE_FTM == g_stAtDevCmdCtrl.ucCurrentTMode))
           {
               g_stAtDevCmdCtrl.ucPriOrDiv = AT_RX_DIV_ON;
               g_stAtDevCmdCtrl.usRxDiv    = g_stAtDevCmdCtrl.usOrigBand;
           }
           break;

        case AT_CMD_SET_RXPRI:
            g_stAtDevCmdCtrl.ucPriOrDiv = AT_RX_PRI_ON;
            g_stAtDevCmdCtrl.usRxPri    = g_stAtDevCmdCtrl.usOrigBand;
            break;

        default:
            break;
    }

    return;

}


VOS_VOID  At_HpaRfCfgCnfProc(
    HPA_AT_RF_CFG_CNF_STRU              *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;

    /*��ȡ���ر�����û�����*/
    ucIndex = g_stAtDevCmdCtrl.ucIndex;

    if (AT_HPA_RSLT_FAIL == pstMsg->usErrFlg)
    {
        AT_INFO_LOG("At_HpaRfCfgCnfProc: set rfcfg err");
        ulRslt = At_RfCfgCnfReturnErrProc(ucIndex);
        AT_STOP_TIMER_CMD_READY(ucIndex);
        At_FormatResultData(ucIndex, ulRslt);
    }
    else
    {
        ulRslt = AT_OK;
        At_RfCfgCnfReturnSuccProc(ucIndex);

        /* ^FRSSI?��GDSP LOAD������յ�ID_HPA_AT_RF_CFG_CNF��Ϣ,�����ϱ�,���յ�
           ID_HPA_AT_RF_RX_RSSI_IND��Ϣʱ���ϱ� */
        if (AT_CMD_QUERY_RSSI != gastAtClientTab[ucIndex].CmdCurrentOpt)
        {
            AT_STOP_TIMER_CMD_READY(ucIndex);
            At_FormatResultData(ucIndex, ulRslt);
        }
    }
    return;
}


VOS_VOID  At_RfRssiIndProc(
    HPA_AT_RF_RX_RSSI_IND_STRU          *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_INT32                           lRssi;

    /*��ȡ���ر�����û�����*/
    ucIndex  = g_stAtDevCmdCtrl.ucIndex;

    if (AT_DSP_RF_AGC_STATE_ERROR == pstMsg->sAGCGain)  /* ���� */
    {
        AT_WARN_LOG("AT_RfRssiIndProc err");
        ulRslt = AT_FRSSI_OTHER_ERR;
    }
    else
    {

        gstAtSendData.usBufLen = 0;

        /*����RSSI����ֵ��λ0.125dBm��Ϊ������������*1000.*/
        lRssi = pstMsg->sRSSI * AT_DSP_RSSI_VALUE_MUL_THOUSAND;

        /*��ȡ��RSSIֵ��������ֵ�ϱ�����ȷ��0.1dBm����ֵ��Ϣ�������ǰ��RSSI
          ֵΪ-85.1dBm������ֵΪ851. ����֮ǰ��1000�����Ծ�ȷ��0.1dBm����Ҫ��100*/
        if (lRssi < 0 )
        {
            lRssi = (-1*lRssi)/100;
        }
        else
        {
            lRssi = lRssi/100;
        }

        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           lRssi);


        gstAtSendData.usBufLen = usLength;
        ulRslt = AT_OK;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRslt);

    return;
}


VOS_VOID  At_HPAMsgProc(
    MsgBlock                            *pstMsg
)
{
    HPA_AT_HEADER_STRU                  *pHeader;

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_HpaMsgProc: pstMsg is NULL");
        return;
    }

    pHeader = (HPA_AT_HEADER_STRU *)pstMsg;

    switch (pHeader->usMsgID)
    {
        case ID_HPA_AT_RF_CFG_CNF:
            At_HpaRfCfgCnfProc((HPA_AT_RF_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_HPA_AT_RF_RX_RSSI_IND:
            At_RfRssiIndProc((HPA_AT_RF_RX_RSSI_IND_STRU *)pstMsg);
            break;

        case ID_AT_WPHY_RF_PLL_STATUS_CNF:
            At_RfPllStatusCnfProc((PHY_AT_RF_PLL_STATUS_CNF_STRU *)pstMsg);
            break;

        case ID_AT_WPHY_POWER_DET_CNF:
            At_RfFpowdetTCnfProc((PHY_AT_POWER_DET_CNF_STRU *)pstMsg);
            break;

        default:
            AT_WARN_LOG("At_HpaMsgProc: ulMsgName is Abnormal!");
            break;
    }

    return;
}

VOS_VOID  At_GHPAMsgProc(
    MsgBlock                            *pstMsg
)
{
    HPA_AT_HEADER_STRU         *pHeader;

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_HpaMsgProc: pstMsg is NULL");
        return;
    }

    pHeader = (HPA_AT_HEADER_STRU *)pstMsg;

    switch (pHeader->usMsgID)
    {
        case ID_GHPA_AT_RF_MSG_CNF:
            At_HpaRfCfgCnfProc((HPA_AT_RF_CFG_CNF_STRU *)pstMsg);
            break;

        case ID_GHPA_AT_RF_RX_RSSI_IND:
            At_RfRssiIndProc((HPA_AT_RF_RX_RSSI_IND_STRU *)pstMsg);
            break;

        case ID_AT_GPHY_RF_PLL_STATUS_CNF:
            At_RfPllStatusCnfProc((PHY_AT_RF_PLL_STATUS_CNF_STRU *)pstMsg);
            break;

        default:
            AT_WARN_LOG("At_HpaMsgProc: ulMsgName is Abnormal!");
            break;
    }

    return;
}


VOS_UINT32 AT_FormatAtiCmdQryString(
    MODEM_ID_ENUM_UINT16                enModemId,
    DRV_AGENT_MSID_QRY_CNF_STRU        *pstDrvAgentMsidQryCnf
)
{
    TAF_PH_MEINFO_STRU                  stMeInfo;
    VOS_UINT16                          usDataLen;
    VOS_UINT8                           aucTmp[AT_MAX_VERSION_LEN];
    VOS_UINT32                          ulI;
    VOS_UINT8                           ucCheckData;

    /* ��ʼ�� */
    usDataLen     = 0;
    ulI           = 0;
    ucCheckData   = 0;
    PS_MEM_SET(&stMeInfo, 0, sizeof(TAF_PH_MEINFO_STRU));


    PS_MEM_SET(aucTmp, 0x00, sizeof(aucTmp));

    /* ��ȡModel��Ϣ */
    if ( (VOS_NULL_PTR == pstDrvAgentMsidQryCnf)
      || (DRV_AGENT_MSID_QRY_NO_ERROR != pstDrvAgentMsidQryCnf->ulResult))
    {
        return AT_ERROR;
    }

    /* ��ȡManufacturer��Ϣ */
    usDataLen = TAF_MAX_MFR_ID_LEN + 1;
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_FMRID, aucTmp, usDataLen))
    {
        AT_WARN_LOG("AT_FormatAtiCmdQryString:WARNING:NVIM Read en_NV_Item_FMRID falied!");
        return AT_ERROR;
    }
    else
    {
        PS_MEM_CPY(stMeInfo.FmrId.aucMfrId, aucTmp, usDataLen);
    }

    /* ��ȡIMEI��Ϣ */
    for (ulI = 0; ulI < TAF_PH_IMEI_LEN; ulI++)
    {
        stMeInfo.ImeisV.aucImei[ulI] = pstDrvAgentMsidQryCnf->aucImei[ulI] + 0x30;
    }

    for (ulI = 0; ulI < (TAF_PH_IMEI_LEN - 2); ulI += 2)
    {
        ucCheckData += (TAF_UINT8)(((pstDrvAgentMsidQryCnf->aucImei[ulI])
                       +((pstDrvAgentMsidQryCnf->aucImei[ulI + 1] * 2) / 10))
                       +((pstDrvAgentMsidQryCnf->aucImei[ulI + 1] * 2) % 10));
    }
    ucCheckData = (10 - (ucCheckData%10)) % 10;

    stMeInfo.ImeisV.aucImei[TAF_PH_IMEI_LEN - 2] = ucCheckData + 0x30;
    stMeInfo.ImeisV.aucImei[TAF_PH_IMEI_LEN - 1] = 0;

    /* ���ATI����ؽ�� */
    usDataLen = 0;
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
    switch(gucAtIType)
        {
            case AT_I_USE0_TYPE:
                usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Serial",stMeInfo.ImeisV.aucImei);
                break;
            case AT_I_USE1_TYPE:
                usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Manufacturer",stMeInfo.FmrId.aucMfrId);
                break;
            case AT_I_USE2_TYPE:
                usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Model",  pstDrvAgentMsidQryCnf->acModelId);
                break;
            case AT_I_USE3_TYPE:
                usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Revision",pstDrvAgentMsidQryCnf->acSoftwareVerId);
                break;
            case AT_I_USE4_TYPE:
                usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","IMEI",stMeInfo.ImeisV.aucImei);
                break;
            case AT_I_USE5_TYPE:
            default:
                usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Manufacturer",stMeInfo.FmrId.aucMfrId);
                usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Model",  pstDrvAgentMsidQryCnf->acModelId);
                usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Revision",pstDrvAgentMsidQryCnf->acSoftwareVerId);
                usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","IMEI",stMeInfo.ImeisV.aucImei);
                usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s","+GCAP: +CGSM,+DS,+ES");
                break;
        }
#else
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Manufacturer",stMeInfo.FmrId.aucMfrId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Model",  pstDrvAgentMsidQryCnf->acModelId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","Revision",pstDrvAgentMsidQryCnf->acSoftwareVerId);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s: %s\r\n","IMEI",stMeInfo.ImeisV.aucImei);
    usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,"%s","+GCAP: +CGSM,+DS,+ES");
#endif
    gstAtSendData.usBufLen = usDataLen;

    return AT_OK;

}


VOS_UINT32 AT_RcvDrvAgentMsidQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_MSID_QRY_CNF_STRU        *pstDrvAgentMsidQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /* ��ʼ�� */
    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentMsidQryCnf = (DRV_AGENT_MSID_QRY_CNF_STRU *)(pRcvMsg->aucContent);

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentMsidQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentMsidQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentMsidQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_MSID_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_SetImeiPara: Get modem id fail.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��ATI����� */
    ulResult = AT_FormatAtiCmdQryString(enModemId, pstDrvAgentMsidQryCnf);
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    if (AT_ERROR == ulResult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentGasMntnCmdRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_GAS_MNTN_CMD_CNF_STRU    *pstDrvAgentGasMntnCmdCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT16                          usLength;

    /* ��ʼ�� */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentGasMntnCmdCnf = (DRV_AGENT_GAS_MNTN_CMD_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult                 = AT_OK;
    usLength                 = 0;
    j                        = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentGasMntnCmdCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGasMntnCmdRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGasMntnCmdRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CGAS_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CGAS����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstDrvAgentGasMntnCmdCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /* ����״̬ */
        if (GAS_AT_CMD_NCELL == pstDrvAgentGasMntnCmdCnf->ucCmd)
        {
            if ((pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum > 0)
             &&((pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum%3) == 0))
            {
                for (i = 0; i< (pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum/3); i++)
                {
                    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                       "%d:%d,",
                                                       (i+1),
                                                       pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[j++]);
                    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                       "0x%X,",
                                                       pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[j++]&0xff);
                    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                       "%d\r\n",
                                                       pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[j++]);
                }
                gstAtSendData.usBufLen = usLength;
            }
            else if (0 == pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "0");
                gstAtSendData.usBufLen = usLength;
            }
            else
            {
                ulResult = AT_ERROR;
            }
        }
        else if (GAS_AT_CMD_SCELL == pstDrvAgentGasMntnCmdCnf->ucCmd)
        {
            /* ����С��״̬ */
            if (3 != pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum)
            {
                ulResult = AT_ERROR;
            }
            else
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "%d,",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[0]);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "0x%X,",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[1]&0xff);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                   "%d",
                                                   pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[2]);
                gstAtSendData.usBufLen = usLength;
                ulResult = AT_OK;
            }
        }
        else if (pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum > 0)
        {
            /* �������� */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                               "%d",
                                               pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[0]);

            for (i = 1; i< pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.ulRsltNum ;i++)
            {
                usLength +=(TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                  (TAF_CHAR *)pgucAtSndCodeAddr+usLength,
                                                  ",%d",
                                                  pstDrvAgentGasMntnCmdCnf->stAtCmdRslt.aulRslt[i]);
            }
            gstAtSendData.usBufLen = usLength;
        }
        else
        {

        }
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentHardwareQryRsp(VOS_VOID *pMsg)
{
    VOS_UINT32                                  ulRet;
    TAF_UINT16                                  usLength;
    VOS_UINT8                                   ucIndex;
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_HARDWARE_QRY_CNF_STRU            *pHardWareCnf;

    /* ��ʼ�� */
    pRcvMsg      = (DRV_AGENT_MSG_STRU*)pMsg;
    pHardWareCnf = (DRV_AGENT_HARDWARE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pHardWareCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHardwareQryRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHardwareQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_HARDWARE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLength               = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pHardWareCnf->ulResult )
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s\"",
                                           pHardWareCnf->aucHwVer);

        gstAtSendData.usBufLen = usLength;
        ulRet                  = AT_OK;
    }
    else
    {
        ulRet                  = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;

}


VOS_UINT32 AT_RcvDrvAgentVertimeQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_VERSION_TIME_STRU        *pstDrvAgentVersionTime;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg                     = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentVersionTime      = (DRV_AGENT_VERSION_TIME_STRU *)(pRcvMsg->aucContent);
    ulResult                    = AT_OK;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentVersionTime->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentVertimeQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentVertimeQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_VERSIONTIME_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^VERTIME����� */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstDrvAgentVersionTime->aucData);

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentYjcxSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_YJCX_SET_CNF_STRU            *pstYjcxSetCnf;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usDataLen;

    /* ��ʼ�� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstYjcxSetCnf   = (DRV_AGENT_YJCX_SET_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult        = AT_OK;
    usDataLen       = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstYjcxSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxSetCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_YJCX_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^YJCX��������� */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstYjcxSetCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usDataLen =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                            "%s: ",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,
                                            "%s",
                                            pstYjcxSetCnf->aucflashInfo);
        gstAtSendData.usBufLen = usDataLen;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentYjcxQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_YJCX_QRY_CNF_STRU            *pstYjcxQryCnf;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usDataLen;

    /* ��ʼ�� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstYjcxQryCnf   = (DRV_AGENT_YJCX_QRY_CNF_STRU *)(pRcvMsg->aucContent);
    ulResult        = AT_OK;
    usDataLen       = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstYjcxQryCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_YJCX_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^YJCX��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstYjcxQryCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usDataLen =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                            "%s: ",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usDataLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usDataLen,
                                            "%s",
                                            pstYjcxQryCnf->aucgpioInfo);

        gstAtSendData.usBufLen = usDataLen;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCrpnQueryRsp(VOS_VOID *pMsg)
{
    MN_MMA_CRPN_QRY_CNF_MSG_STRU       *pstMnMmaCrpnQryCnfMsg;
    MN_MMA_CRPN_QRY_CNF_STRU           *pstMnMmaCrpnQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           aucPlmn[TAF_MAX_AUTHDATA_PLMN_LEN + 1];

    /* ��ʼ�� */
    pstMnMmaCrpnQryCnfMsg   = (MN_MMA_CRPN_QRY_CNF_MSG_STRU *)pMsg;
    pstMnMmaCrpnQryCnf      = &pstMnMmaCrpnQryCnfMsg->stMnMmaCrpnQryCnf;
    ulResult                = AT_OK;
    usLength                = 0;
    ulLoop                  = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMnMmaCrpnQryCnfMsg->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCrpnQueryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentYjcxQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CRPN_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CRPN��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (TAF_ERR_NO_ERROR != pstMnMmaCrpnQryCnfMsg->ulResult)
    {
        ulResult = At_ChgTafErrorCode(ucIndex, (VOS_UINT16)pstMnMmaCrpnQryCnfMsg->ulResult);;
    }
    else
    {
        ulResult = AT_OK;

        for (ulLoop = 0; ulLoop < pstMnMmaCrpnQryCnf->ucTotalNum; ulLoop++)
        {
            if(0 != ulLoop)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s",
                                                   gaucAtCrLf);
            }

            /* ^CRPN:  */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

            /* <PLMN> */
            /* ���ձ�ˣ�����������������PLMN ID�������ʱֱ�Ӳ��������PLMN ID */
            if (2 == pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.ucPlmnType)
            {
                PS_MEM_SET(aucPlmn, 0, sizeof(aucPlmn));
                PS_MEM_CPY(aucPlmn,
                           pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.aucPlmnName,
                           pstMnMmaCrpnQryCnf->stMnMmaCrpnQry.usPlmnNameLen);
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "\"%s\"",
                                                   aucPlmn);
            }
            else
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "\"%X%X%X",
                                                   (0x0f00 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc) >> 8,
                                                   (0x00f0 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc) >> 4,
                                                   (0x000f & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mcc));

#if ( FEATURE_ON == MBB_WPG_COMMON )
                /*334���mcc�ڱ�����и�����mnc��һ����50��һ����050��
                    �������ﲻ��ֱ��ʹ�ó����ж�*/
                if ((0x0f00 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc) != 0xf00)
#else /* FEATURE_ON == MBB_COMMON */
                if (6 == pstMnMmaCrpnQryCnf->ucMaxMncLen)
#endif 
                {
                    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                       "%X",
                                                       (0x0f00 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc) >> 8);

                }
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%X%X\"",
                                                   (0x00f0 & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc) >> 4,
                                                   (0x000f & pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].PlmnId.Mnc));
            }

            /* <short name> */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",\"%s\"",
                                               pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].aucOperatorNameShort);

            /* <long name> */
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",\"%s\"",
                                               pstMnMmaCrpnQryCnf->stOperNameList[ulLoop].aucOperatorNameLong);
        }

        gstAtSendData.usBufLen = usLength;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}




VOS_UINT32 AT_RcvAtMmaUsimStatusInd(VOS_VOID *pMsg)
{
    /* Modified by l60609 for DSDA Phase II, 2012-12-24, Begin */
    AT_MMA_USIM_STATUS_IND_STRU        *pstAtMmaUsimStatusIndMsg;
    MODEM_ID_ENUM_UINT16                enModemId;
    AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

    /* ��ʼ�� */
    pstAtMmaUsimStatusIndMsg   = (AT_MMA_USIM_STATUS_IND_STRU *)pMsg;

    enModemId = VOS_GetModemIDFromPid(pstAtMmaUsimStatusIndMsg->ulSenderPid);

    if (enModemId >= MODEM_ID_BUTT)
    {
        return VOS_ERR;
    }

    pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);

    /* ˢ�¿�״̬ȫ�ֱ��� */
    pstUsimInfoCtx->enCardType   = pstAtMmaUsimStatusIndMsg->enCardType;
    pstUsimInfoCtx->enCardStatus = pstAtMmaUsimStatusIndMsg->enCardStatus;
    pstUsimInfoCtx->ucIMSILen    = pstAtMmaUsimStatusIndMsg->ucIMSILen;
    PS_MEM_CPY(pstUsimInfoCtx->aucIMSI, pstAtMmaUsimStatusIndMsg->aucIMSI, NAS_MAX_IMSI_LENGTH);
    /* Modified by l60609 for DSDA Phase II, 2012-12-24, End */
    return VOS_OK;

}


VOS_UINT32 At_RcvAtCcMsgStateQryCnfProc(VOS_VOID *pMsg)
{
    AT_CC_STATE_QRY_CNF_MSG_STRU           *pstAtCcStateQryCnfMsg;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              i;
    VOS_UINT16                              usLength;

    /* ��ʼ�� */
    pstAtCcStateQryCnfMsg = (AT_CC_STATE_QRY_CNF_MSG_STRU *)pMsg;
    ulResult              = AT_OK;
    usLength              = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstAtCcStateQryCnfMsg->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ǰδ�ȴ�������ظ� */
    if (AT_CMD_CC_STATE_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CCC��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (0 == pstAtCcStateQryCnfMsg->ucCallNum)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
        for ( i = 0 ; i < pstAtCcStateQryCnfMsg->ucCallNum ; i++ )
        {
            AT_ShowCccRst(&pstAtCcStateQryCnfMsg->astCcStateInfoList[i],&usLength);
        }

        if (0 == usLength)
        {
            ulResult = AT_ERROR;
        }
    }

    /* ������ */
    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaCmmSetCmdRsp(VOS_VOID *pMsg)
{
    MN_MM_TEST_CMD_RSP_MSG_STRU        *pstMnMmTestCmdRspMsg;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                              i;
    VOS_UINT16                              usLength;

    /* ��ʼ�� */
    pstMnMmTestCmdRspMsg = (MN_MM_TEST_CMD_RSP_MSG_STRU *)pMsg;
    ulResult              = AT_OK;
    usLength              = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMnMmTestCmdRspMsg->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCmmSetCmdRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCmmSetCmdRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CMM��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstMnMmTestCmdRspMsg->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        if (pstMnMmTestCmdRspMsg->stAtCmdRslt.ulRsltNum > 0)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                               "%d",
                                               pstMnMmTestCmdRspMsg->stAtCmdRslt.aulRslt[0]);

            for (i = 1; i< pstMnMmTestCmdRspMsg->stAtCmdRslt.ulRsltNum ;i++)
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                                   ",%d",
                                                   pstMnMmTestCmdRspMsg->stAtCmdRslt.aulRslt[i]);
            }
            gstAtSendData.usBufLen = usLength;
        }
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentFullHardwareQryRsp(VOS_VOID *pMsg)
{
    TAF_UINT16                                       usLength;
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU            *pstEvent;

    /* ��ʼ�� */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_FULL_HARDWARE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFullHardwareQryRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFullHardwareQryRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_FULL_HARDWARE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLength               = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s ",
                                           pstEvent->aucModelId);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s,",
                                           pstEvent->aucRevisionId);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s\"",
                                           pstEvent->aucHwVer);

        gstAtSendData.usBufLen = usLength;

        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}


VOS_UINT32 At_SendRfCfgAntSelToHPA(VOS_UINT8 ucDivOrPriOn)
{
    AT_HPA_RF_CFG_REQ_STRU              *pstMsg;
    VOS_UINT32                           ulLength;
    VOS_UINT16                           usMask;

    /* ����AT_HPA_RF_CFG_REQ_STRU��Ϣ */
    ulLength = sizeof(AT_HPA_RF_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_HPA_RF_CFG_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_SendRfCfgAntSelToHPA: alloc msg fail!");
        return AT_FAILURE;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(AT_HPA_RF_CFG_REQ_STRU));


    /* ��д��Ϣͷ */
    pstMsg->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid        = WUEPS_PID_AT;
    pstMsg->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid      = DSP_PID_WPHY;
    pstMsg->ulLength           = ulLength;


    /* ��д��Ϣ�� */
    pstMsg->usMsgID            = ID_AT_HPA_RF_CFG_REQ;
    usMask                     = W_RF_MASK_RX_ARFCN | W_RF_MASK_RX_ANTSEL \
                                 | W_RF_MASK_RX_RXONOFF;

    /* ��λ��ʶ�������� */
    pstMsg->stRfCfgPara.usMask = usMask;

    if (AT_RX_DIV_ON == ucDivOrPriOn)
    {
        pstMsg->stRfCfgPara.usRxAntSel = ANT_TWO;
        pstMsg->stRfCfgPara.usRxEnable = DSP_CTRL_RX_ALL_ANT_ON;
    }
    else
    {
        pstMsg->stRfCfgPara.usRxAntSel = ANT_ONE;
        pstMsg->stRfCfgPara.usRxEnable = DSP_CTRL_RX_ANT1_ON;
    }

    pstMsg->stRfCfgPara.usRxBand       = g_stAtDevCmdCtrl.stDspBandArfcn.usDspBand;
    pstMsg->stRfCfgPara.usRxFreqNum    = g_stAtDevCmdCtrl.stDspBandArfcn.usDlArfcn;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("At_SendRfCfgAntSelToHPA: Send msg fail!");
        return AT_FAILURE;
    }

    return AT_SUCCESS;
}


VOS_UINT32 AT_RcvDrvAgentSetSimlockCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_SET_SIMLOCK_CNF_STRU                  *pstEvent;
    VOS_UINT32                                       ulRet;
    VOS_UINT8                                        ucIndex;

    /* ��ʼ�� */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_SET_SIMLOCK_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetSimlockCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetSimlockCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_SIMLOCK_SET_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;

}


VOS_UINT32 AT_RcvDrvAgentQryRxdivCnf(VOS_VOID *pMsg)
{
    VOS_UINT32                                       ulRet;
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_QRY_RXDIV_CNF_STRU                    *pstEvent;
    VOS_UINT32                                       ulUserDivBandsLow;
    VOS_UINT32                                       ulUserDivBandsHigh;
    VOS_UINT32                                       ulDrvDivBandsLow;
    VOS_UINT32                                       ulDrvDivBandsHigh;
    VOS_UINT16                                       usLen;

    /* ��ʼ�� */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_QRY_RXDIV_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryRxdivCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryRxdivCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_RXDIV_QRY_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    usLen                  = 0;
    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        At_CovertMsInternalRxDivParaToUserSet(pstEvent->usDrvDivBands,
                                             &ulDrvDivBandsLow,
                                             &ulDrvDivBandsHigh);
        At_CovertMsInternalRxDivParaToUserSet(pstEvent->usCurBandSwitch,
                                             &ulUserDivBandsLow,
                                             &ulUserDivBandsHigh);

        usLen +=  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR*)pgucAtSndCodeAddr,
                                         "%s:",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        if (0 != ulDrvDivBandsHigh)
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%d,%X%08X,",
                                            0,
                                            ulDrvDivBandsHigh,ulDrvDivBandsLow);
        }
        else
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%d,%X,",
                                            0,
                                            ulDrvDivBandsLow);
        }

        if (0 != ulUserDivBandsHigh)
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%X%08X",
                                            ulUserDivBandsHigh,
                                            ulUserDivBandsLow);
        }
        else
        {
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                            "%X",
                                            ulUserDivBandsLow);
        }
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                        "\r\n");
        usLen +=  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (TAF_CHAR *)pgucAtSndCodeAddr,
                                         (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                         "%s:",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)(pgucAtSndCodeAddr + usLen),
                                        "%d,%X,%X",
                                        1,
                                        0,
                                        0);
        gstAtSendData.usBufLen = usLen;

        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_CME_UNKNOWN;
    }

    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}

VOS_UINT32 AT_RcvDrvAgentSetRxdivCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_AT_RXDIV_CNF_STRU                     *pstEvent;

    /* ��ʼ�� */
    pRcvMsg  = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent = (DRV_AGENT_AT_RXDIV_CNF_STRU *)pRcvMsg->aucContent;


    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetRxdivCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetRxdivCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_DRV_AGENT_RXDIV_SET_REQ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    if( DRV_AGENT_CME_RX_DIV_OTHER_ERR == pstEvent->ulResult )
    {
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_CME_RX_DIV_OTHER_ERR);

        return VOS_ERR;
    }

    if( DRV_AGENT_CME_RX_DIV_NOT_SUPPORTED == pstEvent->ulResult )
    {
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_CME_RX_DIV_NOT_SUPPORTED);

        return VOS_ERR;
    }

    if( AT_DSP_RF_SWITCH_ON == pstEvent->ucRxOnOff )
    {
        if( DRV_AGENT_CME_RX_DIV_BAND_ERR == pstEvent->ulResult )
        {
            gstAtSendData.usBufLen = 0;

            AT_STOP_TIMER_CMD_READY(ucIndex);

            At_FormatResultData(ucIndex, AT_CME_RX_DIV_NOT_SUPPORTED);

            return VOS_ERR;
        }

        if (AT_FAILURE == At_SendRfCfgAntSelToHPA(AT_RX_DIV_ON))
        {
            gstAtSendData.usBufLen = 0;

            AT_STOP_TIMER_CMD_READY(ucIndex);

            At_FormatResultData(ucIndex, AT_CME_RX_DIV_OTHER_ERR);

            return VOS_ERR;
        }

        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SET_RXDIV;
        g_stAtDevCmdCtrl.ucIndex               = ucIndex;
        g_stAtDevCmdCtrl.usOrigBand            = pstEvent->usSetDivBands;

        /* ������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        /* Added by f62575 for SMALL IMAGE, 2012-1-3, begin */
        gstAtSendData.usBufLen = 0;

        AT_STOP_TIMER_CMD_READY(ucIndex);

        At_FormatResultData(ucIndex, AT_ERROR);
        /* Added by f62575 for SMALL IMAGE, 2012-1-3, end   */
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentSetNvRestoreCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                *pstEvent;

    /* ��ʼ�� */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetNvRestoreCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetNvRestoreCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_NVRESTORE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%d",
                                                    pstEvent->ulResult);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;

}


VOS_UINT32 AT_RcvDrvAgentQryNvRestoreRstCnf(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    VOS_UINT32                                       ulRestoreStatus;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                    *pstEvent;

    /* ��ʼ�� */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryNvRestoreRstCnf: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryNvRestoreRstCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_NVRSTSTTS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if ((AT_NV_RESTORE_RESULT_INIT == pstEvent->ulResult)
     || (AT_NV_RESTORE_RUNNING == pstEvent->ulResult))
    {
        ulRestoreStatus = AT_NV_RESTORE_FAIL;
    }
    else if (VOS_OK == pstEvent->ulResult)
    {
        ulRestoreStatus = AT_NV_RESTORE_SUCCESS;
    }
    else
    {
        ulRestoreStatus = AT_NV_RESTORE_FAIL;
    }
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%d",
                                                     ulRestoreStatus);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;

}


VOS_UINT32 AT_RcvDrvAgentNvRestoreManuDefaultRsp(VOS_VOID *pMsg)
{
    VOS_UINT8                                        ucIndex;
    VOS_UINT32                                       ulRst;
    VOS_UINT32                                       ulResult;
    DRV_AGENT_MSG_STRU                              *pRcvMsg;
    DRV_AGENT_NVRESTORE_RST_STRU                    *pstEvent;

    /* ��ʼ�� */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU*)pMsg;
    pstEvent                = (DRV_AGENT_NVRESTORE_RST_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvRestoreManuDefaultRsp: AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvRestoreManuDefaultRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_F_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    ulResult = pstEvent->ulResult;
    if ( NV_OK != ulResult )
    {
        ulRst = AT_ERROR;
    }
    else
    {
        g_bSetFlg = VOS_TRUE;

        /* E5֪ͨAPP�ָ��û�����  */
        AT_PhSendRestoreFactParm();

        ulRst = AT_OK;
    }
    At_FormatResultData(ucIndex, ulRst);

    return VOS_OK;

}



VOS_UINT32  AT_GetImeiValue(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           aucImei[TAF_PH_IMEI_LEN + 1]
)
{
    VOS_UINT8                               aucBuf[TAF_PH_IMEI_LEN + 1];
    VOS_UINT8                               ucCheckData;
    VOS_UINT32                              ulDataLen;
    VOS_UINT32                              i;

    ucCheckData = 0;
    ulDataLen   = TAF_PH_IMEI_LEN;


    PS_MEM_SET(aucBuf, 0x00, sizeof(aucBuf));

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_IMEI, aucBuf, ulDataLen))
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    {
        AT_WARN_LOG("TAF_GetImeiValue:Read IMEI Failed!");
        return VOS_ERR;
    }
    else
    {
        ucCheckData = 0;
        for (i = 0; i < (TAF_PH_IMEI_LEN-2); i += 2)
        {
            ucCheckData += aucBuf[i]
                          +((aucBuf[i+1] + aucBuf[i+1])/10)
                          +((aucBuf[i+1] + aucBuf[i+1])%10);
        }
        ucCheckData = (10 - (ucCheckData%10))%10;
        AT_DeciDigit2Ascii(aucBuf, (VOS_UINT8)ulDataLen, aucImei);
        aucImei[TAF_PH_IMEI_LEN-2] = ucCheckData+0x30;
        aucImei[TAF_PH_IMEI_LEN-1] = 0;
    }
    return VOS_OK;
}



VOS_UINT32 AT_RcvDrvAgentSetGpioplRsp(VOS_VOID *pMsg)
{

    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_GPIOPL_SET_CNF_STRU      *pstDrvAgentGpioSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDrvAgentGpioSetCnf = (DRV_AGENT_GPIOPL_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDrvAgentGpioSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGpioplRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentGpioplRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (AT_CMD_GPIOPL_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE == pstDrvAgentGpioSetCnf->bFail)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ����AT_FormATResultDATa���������� */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}




VOS_UINT32 AT_RcvDrvAgentQryGpioplRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                   *pRcvMsg;
    DRV_AGENT_GPIOPL_QRY_CNF_STRU        *pstGpioQryCnf;
    VOS_UINT16                            usLength;
    VOS_UINT32                            i;
    VOS_UINT8                             ucIndex;
    VOS_UINT32                            ulResult;

    /* ��ʼ����Ϣ����ȡucContent */
    pRcvMsg               = (DRV_AGENT_MSG_STRU *)pMsg;
    pstGpioQryCnf         = (DRV_AGENT_GPIOPL_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstGpioQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryGpioplRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryGpioplRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_GPIOPL_QRY */
    if (AT_CMD_GPIOPL_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /*��λAT״̬*/
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != pstGpioQryCnf->bFail)
    {
        /* ��ӡ��� */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:", g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0; i < DRVAGENT_GPIOPL_MAX_LEN; i++)
        {
           usLength += (VOS_UINT16)At_sprintf (AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               "%02X", pstGpioQryCnf->aucGpiopl[i]);
        }

        gstAtSendData.usBufLen = usLength;
        ulResult               = AT_OK;
    }
    else
    {
        /* ����AT_FormATResultDATa���������� */
        gstAtSendData.usBufLen = 0;
        ulResult               = AT_ERROR;
    }
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}



VOS_UINT32 AT_RcvDrvAgentSetDatalockRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_DATALOCK_SET_CNF_STRU    *pstDatalockSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
#if ((FEATURE_ON == MBB_SIMLOCK_THREE) || (FEATURE_ON == MBB_SIMLOCK_FOUR))
    confidential_nv_opr_info *smem_data = NULL;
    smem_data = (confidential_nv_opr_info *)SRAM_CONFIDENTIAL_NV_OPR_ADDR;
    if (NULL == smem_data)
    {
        vos_printf("smem_confidential_nv_opr_flag malloc fail!\n");
        return VOS_ERR;
    }
#endif
    /* ��ʼ�� */
    pRcvMsg                   = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDatalockSetCnf         = (DRV_AGENT_DATALOCK_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDatalockSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetDatalockRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetDatalockRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_DATALOCK_SET */
    if (AT_CMD_DATALOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != pstDatalockSetCnf->bFail)
    {
        /* ����dATalock�ѽ��� */
        g_bAtDataLocked    =  VOS_FALSE;
#if (FEATURE_ON == MBB_DLOAD)
    (void)bsp_dload_set_datalock_state();
#endif /* MBB_DLOAD */
#if ((FEATURE_ON == MBB_SIMLOCK_THREE) || (FEATURE_ON == MBB_SIMLOCK_FOUR))
        /*datalock���������ý��������ڴ��־*/
        smem_data->smem_datalock_state = SMEM_DATALOCK_STATE_NUM;
#endif
    #if (FEATURE_ON == MBB_COMMON)
        g_ucAtDataLockError = 0; /*lint !e63 ��������������� */
    #endif
        ulResult           =  AT_OK;
    }
    else
    {
    #if (FEATURE_ON == MBB_COMMON)
        g_ucAtDataLockError++; /*lint !e52 ��������������� */
    #endif
        ulResult           =  AT_ERROR;
    }

    /* ����AT_FormAtResultData����������  */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
 }

/* Modified by f62575 for B050 Project, 2012-2-3, Begin   */

VOS_UINT32 AT_GetSimLockStatus(VOS_UINT8 ucIndex)
{

    /* ����Ϣ��C�˻�ȡSIMLOCK ״̬��Ϣ */
    if(TAF_SUCCESS != Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId, 0,
                                    TAF_PH_SIMLOCK_VALUE_PARA, VOS_NULL_PTR))
    {
        AT_WARN_LOG("AT_GetSimLockStatus: Taf_ParaQuery fail.");
        return VOS_ERR;
    }

    /* ^SIMLOCK=2��ѯUE������״̬����AT�����������̣���Ҫ��������������ʱ�������¶˿�״̬ */
    if (AT_SUCCESS != At_StartTimer(AT_SET_PARA_TIME, ucIndex))
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_ERR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt   = AT_CMD_SIMLOCKSTATUS_READ;

    g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
    AT_CLIENT_STATUS_PRINT_2(ucIndex, g_stParseContext[ucIndex].ucClientStatus);
    return VOS_OK;
}
/* Modified by f62575 for B050 Project, 2012-2-3, end   */


VOS_UINT32 AT_RcvDrvAgentQryTbatvoltRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_TBATVOLT_QRY_CNF_STRU    *pstTbatvoltQryCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    pRcvMsg                   = (DRV_AGENT_MSG_STRU *)pMsg;
    pstTbatvoltQryCnf         = (DRV_AGENT_TBATVOLT_QRY_CNF_STRU *)pRcvMsg->aucContent;


    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstTbatvoltQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatvoltRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatvoltRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_TBATVOLT_QRY*/
    if (AT_CMD_TBATVOLT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ص�ѹ��ѯ����ж� */
    if (VOS_TRUE != pstTbatvoltQryCnf->bFail)
    {

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstTbatvoltQryCnf->lBatVol);
        ulResult = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult = AT_ERROR;
    }

    /* ����AT_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
}


VOS_VOID At_RcvVcMsgQryModeCnfProc(MN_AT_IND_EVT_STRU *pstData)
{

    MN_AT_IND_EVT_STRU                  *pRcvMsg;
    APP_VC_EVENT_INFO_STRU              *pstEvent;
    VOS_UINT8                            ucIndex;
    VOS_UINT16                           usVoiceMode;
    VOS_UINT16                           usDevMode;
    VOS_UINT32                           ulRet;


    /* ��ʼ�� */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryModeCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryModeCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ʽ��VMSET����� */
    if (AT_CMD_VMSET_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        usDevMode = pstEvent->enDevMode;

        /* ��Ч��ģʽ��ֱ�ӷ���ERROR */
        if (usDevMode >= VC_PHY_DEVICE_MODE_BUTT)
        {
            gstAtSendData.usBufLen = 0;
            ulRet = AT_ERROR;
        }
        else
        {
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            "%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            usDevMode);
            ulRet = AT_OK;
        }
    }
    /* ��ʽ��CVOICE����� */
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else if ( AT_CMD_CVOICE_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        /* ת��ΪӦ����VC����ģʽ */
        usVoiceMode     = APP_VC_VcPhyVoiceMode2AppVcVoiceMode(pstEvent->enDevMode);

        /* ��Ч��ģʽ��ֱ�ӷ���ERROR */
        if (usVoiceMode >= APP_VC_VOICE_MODE_BUTT)
        {
            gstAtSendData.usBufLen = 0;
            ulRet = AT_ERROR;
        }
        else
        {
            gstAtSendData.usBufLen =(VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                                           "%s: %d, %d, %d, %d",
                                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                           usVoiceMode,
                                                           AT_PCVOICE_SAMPLE_RATE,
                                                           AT_PCVOICE_DATA_BIT,
                                                           AT_PCVOICE_FRAME_PERIOD);
            ulRet = AT_OK;
        }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    else
    {
        return;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}


VOS_VOID At_RcvVcMsgSetPortCnfProc(MN_AT_IND_EVT_STRU *pstData)
{
    MN_AT_IND_EVT_STRU                 *pRcvMsg;
    APP_VC_EVENT_INFO_STRU             *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* ��ʼ�� */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;


    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetPortCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if (VOS_TRUE == pstEvent->bSuccess)
    {
        ulRet = AT_OK;
#if (FEATURE_ON == MBB_PCVOICE)
        /*DDSETEX ���������л��˿�Ϊ����ģʽ����Ҫʹ��diag�˿����������ݿ���������ͨ*/
        BSP_USB_SetSwitchPcVoice(VOS_TRUE);
#endif /* MBB_PCVOICE END */
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;

}


VOS_VOID At_RcvVcMsgQryPortCnfProc(MN_AT_IND_EVT_STRU *pstData)
{
    MN_AT_IND_EVT_STRU                  *pRcvMsg;
    APP_VC_EVENT_INFO_STRU              *pstEvent;
    VOS_UINT8                            ucIndex;
    APP_VC_VOICE_PORT_ENUM_U8            ucVoicePort;                           /* �����豸�˿ں� */
    VOS_UINT32                           ulRet;

    /* ��ʼ�� */
    pRcvMsg         = pstData;
    pstEvent        = (APP_VC_EVENT_INFO_STRU *)pstData->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* ��ѯ�Ķ˿ں� */
    ucVoicePort = pstEvent->enVoicePort;

    if (APP_VC_VOICE_PORT_BUTT > ucVoicePort)
    {
        gstAtSendData.usBufLen =
            (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   "%s: %d",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucVoicePort);
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;

}


VOS_UINT32 AT_RcvRnicDsflowRsp(MsgBlock *pstMsg)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    RNIC_DATA_RATE_STRU                 stCurrentRateInfo;
    RNIC_AT_DSFLOW_RSP_STRU            *pstRcvMsg;

    usLength                            = 0;
    pstRcvMsg                           = (RNIC_AT_DSFLOW_RSP_STRU *)pstMsg;
    stCurrentRateInfo.ulULDataRate      = pstRcvMsg->stRnicDataRate.ulULDataRate;
    stCurrentRateInfo.ulDLDataRate      = pstRcvMsg->stRnicDataRate.ulDLDataRate;

    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryPortCnfProc : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       stCurrentRateInfo.ulULDataRate);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d",
                                       stCurrentRateInfo.ulDLDataRate);

    gstAtSendData.usBufLen = usLength;

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}

VOS_UINT32 AT_RcvRnicDialModeCnf(MsgBlock *pstMsg)
{
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    RNIC_AT_DIAL_MODE_CNF_STRU         *pstRcvMsg;

    usLength                            = 0;
    pstRcvMsg                           = (RNIC_AT_DIAL_MODE_CNF_STRU *)pstMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->clientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvRnicDialModeCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvRnicDialModeCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    usLength =  (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR*)pgucAtSndCodeAddr,
                                        "%s:",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%d",
                                        pstRcvMsg->ulDialMode);

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        ",%d",
                                        pstRcvMsg->ulEventReportFlag);

    usLength += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                         ",%d",
                                         pstRcvMsg->ulIdleTime);

    gstAtSendData.usBufLen = usLength;

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_VOID At_ZeroReplaceBlankInString( VOS_UINT8 *pData, VOS_UINT32 ulLen)
{
    TAF_UINT32 ulChkLen  = 0;
    TAF_UINT8  *pWrite   = pData;
    TAF_UINT8  *pRead    = pData;

    /* ���������� */
    while ( ulChkLen < ulLen )
    {
        /* ʱ���ʽ May  5 2011 17:08:00
           ת����   May 05 2011 17:08:00 */
        if (' ' == *pRead++)
        {
            if (' ' == *pRead)
            {
                pWrite++;
                *pWrite = '0';
                pRead++;
                ulChkLen++;
            }
        }
        pWrite++;
        ulChkLen++;
    }

    return;
}



VOS_UINT32 AT_RcvDrvAgentQryVersionRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_VERSION_QRY_CNF_STRU     *pstVersionQryCnfInfo;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulLen;
    VOS_CHAR                            acTmpTime[AT_AGENT_DRV_VERSION_TIME_LEN] = {0};
    VOS_UINT16                          usLength;
    VOS_BOOL                            bPhyNumIsNull;

    VOS_UINT32                          ulOpt;
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
    VOS_UINT32                          ulRet;
    TAF_NVIM_CS_VER_STRU                stCsver;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
#if (FEATURE_ON == MBB_COMMON)
    VOS_UINT8                           iniVersion[AT_VERSION_INI_LEN] = {0};
#endif
    stCsver.usCsver = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_Csver, &(stCsver.usCsver), sizeof(stCsver.usCsver));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

    /* ��ʼ����Ϣ����ȡucContent */
    ulLen                        = 0;
    pRcvMsg                      = (DRV_AGENT_MSG_STRU *)pMsg;
    pstVersionQryCnfInfo         = (DRV_AGENT_VERSION_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstVersionQryCnfInfo->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_VERSION_QRY/AT_CMD_RSFR_VERSION_QRY, ^RSFR����Ҳ���ô˽ӿ� */
    if ((AT_CMD_VERSION_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
        && (AT_CMD_RSFR_VERSION_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt))
    {
        return VOS_ERR;
    }

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_RcvDrvAgentQryVersionRsp: Get modem id fail.");
        return VOS_ERR;
    }

    ulOpt = gastAtClientTab[ucIndex].CmdCurrentOpt;

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*��ѯ���� */
    if(DRV_AGENT_VERSION_QRY_NO_ERROR != pstVersionQryCnfInfo->enResult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }

#if (FEATURE_ON == MBB_COMMON)
    if (NV_OK != NVM_Read(en_NV_Item_PRI_VERSION, iniVersion, sizeof(iniVersion)))
    {
        return AT_ERROR;
    }
#endif
    /*�汾����ʱ���ʽת������ʱ��������������ո�ĺ�һ���ո���0�滻 */
    ulLen = VOS_StrLen(pstVersionQryCnfInfo->acVerTime);
    PS_MEM_CPY(acTmpTime, pstVersionQryCnfInfo->acVerTime, ulLen + 1);
    At_ZeroReplaceBlankInString((VOS_UINT8 *)acTmpTime, ulLen);

    /* �ַ���Ԥ���� */
    usLength = TAF_CDROM_VERSION_LEN;

#if (FEATURE_ON == MBB_COMMON)
    /* ��OEM������ȡISO�汾�� */
    if (VOS_OK != DRV_GET_CDROM_VERSION((VOS_CHAR *)pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, TAF_CDROM_VERSION_LEN))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp: DRV_GET_CDROM_VERSION Error.");
    }
#endif

    At_DelCtlAndBlankCharWithEndPadding(pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, &usLength);

    /* ��ȡ������Ƿ�Ϊ�յı�ʶ */
    if (AT_OK != AT_PhyNumIsNull(enModemId, AT_PHYNUM_TYPE_IMEI, &bPhyNumIsNull))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryVersionRsp(): AT_PhyNumIsNull Error!");
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    usLength = 0;

    /* �ڲ��汾���ڵ���δд�������ǰ����ѯ����ʵ��ʾ��д������ź����ѯ�汾��ǰδ
       �������ָ��ڲ��汾����ʾΪ�գ�����Ѿ��������ָ��ڲ��汾����ʵ��ʾ */
    if (VOS_FALSE == g_bAtDataLocked || (VOS_TRUE == bPhyNumIsNull))
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:BDT:%s%s",
                                           "^VERSION", acTmpTime, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo,gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stInterHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stFullHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stModelId.aucModelId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stInterModelId.aucModelId, gaucAtCrLf);
    #if (FEATURE_OFF == MBB_COMMON)
        /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:CFG:%d%s",
                                           "^VERSION",stCsver.usCsver, gaucAtCrLf);
        /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:PRL:",
                                           "^VERSION");

        gstAtSendData.usBufLen = usLength;
    #endif
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:BDT:%s%s",
                                           "^VERSION", acTmpTime, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTS:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stSoftVersion.aucRevisionId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTS:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTD:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stIsoVer.aucIsoInfo, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTD:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTH:%s%s",
                                           "^VERSION", pstVersionQryCnfInfo->stInterHwVer.aucHwVer, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTH:%s",
                                           "^VERSION", gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:EXTU:%s%s",
                                           "^VERSION",pstVersionQryCnfInfo->stModelId.aucModelId, gaucAtCrLf);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:INTU:%s",
                                           "^VERSION", gaucAtCrLf);
    #if (FEATURE_OFF == MBB_COMMON)
        /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:CFG:%d%s",
                                           "^VERSION",stCsver.usCsver, gaucAtCrLf);
        /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:PRL:",
                                           "^VERSION");

        gstAtSendData.usBufLen = usLength;
    #endif
    }
   
#if (FEATURE_ON == MBB_COMMON)
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, 
                                            (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                            "%s:CFG:%d%s",
                                            "^VERSION",stCsver.usCsver, gaucAtCrLf);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, 
                                            (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                            "%s:PRL:%s",
                                            "^VERSION", gaucAtCrLf);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, 
                                            (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                            "%s:OEM:%s",
                                            "^VERSION", gaucAtCrLf);

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, 
                                            (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                            "%s:INI:%s",
                                            "^VERSION", iniVersion);
    
    gstAtSendData.usBufLen = usLength;
#endif
    

    /* �����^RSFR�����Ĳ�ѯVERSION��Ϣ������,����^RSFR����ȥ���� */
    if(AT_CMD_RSFR_VERSION_QRY == ulOpt)
    {
        AT_SetRsfrVersionCnf(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

        /* AT���ص��ַ�����AT_SetRsfrVersionCnf�д��� */
        return VOS_OK;
    }

    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;

}



VOS_UINT32 AT_RcvDrvAgentQrySecuBootRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_SECUBOOT_QRY_CNF_STRU    *pstSecubootQryCnfInfo;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg;
    pstSecubootQryCnfInfo    = (DRV_AGENT_SECUBOOT_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstSecubootQryCnfInfo->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySecuBootRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySecuBootRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SECUBOOT_QRY */
    if (AT_CMD_SECUBOOT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ǰ�汾�Ѿ������˰�ȫ���� */
    if (VOS_TRUE != pstSecubootQryCnfInfo->bFail)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstSecubootQryCnfInfo->ucSecuBootEnable);
        ulResult = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult = AT_ERROR;
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex,ulResult);
    return VOS_OK;
}


VOS_UINT32 AT_SetGlobalFchan(VOS_UINT8 ucRATMode)
{
    g_stAtDevCmdCtrl.ucDeviceRatMode = ucRATMode;

    return VOS_OK;
}



VOS_UINT32 AT_SetFchanRspErr(DRV_AGENT_FCHAN_SET_ERROR_ENUM_UINT32  enResult)
{
    if(DRV_AGENT_FCHAN_BAND_NOT_MATCH == enResult)
    {
        return AT_FCHAN_BAND_NOT_MATCH;
    }

    if(DRV_AGENT_FCHAN_BAND_CHANNEL_NOT_MATCH == enResult)
    {
        return AT_FCHAN_BAND_CHANNEL_NOT_MATCH;
    }

    if(DRV_AGENT_FCHAN_OTHER_ERR == enResult)
    {
        g_stAtDevCmdCtrl.bDspLoadFlag = VOS_FALSE;
        AT_WARN_LOG("AT_SetFChanPara: DSP Load fail!");
        return AT_FCHAN_OTHER_ERR;
    }

    return DRV_AGENT_FCHAN_SET_NO_ERROR;

}



VOS_UINT32 AT_RcvDrvAgentSetFchanRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_FCHAN_SET_CNF_STRU       *pstFchanSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulError;

    /* ��ʼ�� */
    pRcvMsg          = (DRV_AGENT_MSG_STRU *)pMsg;
    pstFchanSetCnf   = (DRV_AGENT_FCHAN_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstFchanSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetFchanRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetFchanRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_FCHAN_SET */
    if (AT_CMD_FCHAN_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �����д���Ĵ��� */
    ulError =  AT_SetFchanRspErr(pstFchanSetCnf->enResult);
    if(DRV_AGENT_FCHAN_SET_NO_ERROR != ulError)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, ulError);
        return VOS_OK;
    }

    /* �����޴���Ĵ��� */
    g_stAtDevCmdCtrl.bDspLoadFlag    = VOS_TRUE;
    g_stAtDevCmdCtrl.ucDeviceRatMode = (VOS_UINT8)pstFchanSetCnf->stFchanSetReq.ucDeviceRatMode;
    g_stAtDevCmdCtrl.ucDeviceAtBand  = (VOS_UINT8)pstFchanSetCnf->stFchanSetReq.ucDeviceAtBand;
    g_stAtDevCmdCtrl.stDspBandArfcn  = pstFchanSetCnf->stFchanSetReq.stDspBandArfcn;
    g_stAtDevCmdCtrl.usFDAC          = 0;                                       /* FDAC���㣬��ֹG/W��Χ���� */

    /* ����AT_FormATResultDATa���������� */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex,AT_OK);
    return VOS_OK;
}



VOS_UINT32 AT_GetRxpriErr(DRV_AGENT_ERROR_ENUM_UINT32 enResult)
{
    if(DRV_AGENT_CME_RX_DIV_OTHER_ERR == enResult)
    {
        return AT_CME_RX_DIV_OTHER_ERR;
    }

    if(DRV_AGENT_CME_RX_DIV_NOT_SUPPORTED == enResult)
    {
        return AT_CME_RX_DIV_NOT_SUPPORTED;
    }

    return AT_OK;
}


VOS_VOID AT_SupportHsdpa(
    AT_NVIM_UE_CAPA_STRU               *pstUECapa,
    VOS_BOOL                           *pbSupportHsdpa
    )
{

    /* ��ʼ��Ϊ��֧��DPA */
    *pbSupportHsdpa = VOS_FALSE;

    if (pstUECapa->enAsRelIndicator >= 2)
    {
        if (1 == pstUECapa->ulHspaStatus)
        {
            if (PS_TRUE == pstUECapa->enHSDSCHSupport)
            {
                *pbSupportHsdpa = VOS_TRUE;
            }
        }
        else
        {
            *pbSupportHsdpa = VOS_TRUE;
        }
    }
}



VOS_VOID AT_SupportHsupa(
    AT_NVIM_UE_CAPA_STRU               *pstUECapa,
    VOS_BOOL                           *pbSupportHsupa
)
{

    /* ��ʼ��Ϊ��֧��UPA */
    *pbSupportHsupa = VOS_FALSE;

    if (pstUECapa->enAsRelIndicator >= 3)
    {
       if (1 == pstUECapa->ulHspaStatus)
       {
           if (PS_TRUE == pstUECapa->enEDCHSupport)
           {
               *pbSupportHsupa = VOS_TRUE;
           }
       }
       else
       {
            *pbSupportHsupa = VOS_TRUE;
       }
    }
}


VOS_UINT32 AT_GetWFeatureInfo(
    AT_FEATURE_SUPPORT_ST              *pstFeATure,
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstAtAgentSfeatureQryCnf
)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    VOS_UINT32                          ulLen;
    VOS_BOOL                            bSupportHsdpa;
    VOS_BOOL                            bSupportHsupa;
    VOS_UINT8                           aucStrTmp[50] = {0};
    VOS_UINT8                           aucStrDiv[AT_SFEATURE_DIV_STRING_LEN];
    VOS_UINT32                          ulDivLen;


    bSupportHsdpa = VOS_FALSE;
    bSupportHsupa = VOS_FALSE;

    PS_MEM_SET(&stUECapa, 0x00, sizeof(stUECapa));


    /* ��ȡHSPA,HSPA+֧������ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New, &stUECapa,
                        sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("AT_GetWFeatureInfo: en_NV_Item_WAS_RadioAccess_Capa NV Read  Fail!");
    #if (FEATURE_OFF == MBB_COMMON)
        /* �ڴ��ظ��ͷ� */
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
    #endif
        return VOS_ERR;
    }

    /* ��ȡWcdmaƵ����Ϣ */
    ulLen = (VOS_UINT32)AT_GetWcdmaBandStr(aucStrTmp,&(pstAtAgentSfeatureQryCnf->stBandFeature));

    /* HSPA+�Ƿ�֧�� */
    if ((stUECapa.enAsRelIndicator >= 4)
     && (PS_TRUE == stUECapa.enMacEhsSupport)
     && (stUECapa.ucHSDSCHPhyCategory >= 10)
     && (0 != stUECapa.ucHSDSCHPhyCategoryExt)
     && (PS_TRUE == stUECapa.enHSDSCHSupport))
     {
        pstFeATure[AT_FEATURE_HSPAPLUS].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_HSPAPLUS].aucContent, aucStrTmp, ulLen);
     }

    /* DPA�Ƿ�֧�� */
    AT_SupportHsdpa(&stUECapa, &bSupportHsdpa);
    if (VOS_TRUE == bSupportHsdpa)
    {
        pstFeATure[AT_FEATURE_HSDPA].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_HSDPA].aucContent, aucStrTmp, ulLen);
    }

    /*UPA�Ƿ�֧��*/
    AT_SupportHsupa(&stUECapa, &bSupportHsupa);
    if(VOS_TRUE == bSupportHsupa)
    {
        pstFeATure[AT_FEATURE_HSUPA].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_HSUPA].aucContent, aucStrTmp, ulLen);
    }


    /* �ּ���Ϣ */
    pstFeATure[AT_FEATURE_DIVERSITY].ucFeatureFlag = AT_FEATURE_EXIST;
    /* UMTS�ķּ���Ϣ���*/
    PS_MEM_SET(aucStrDiv, 0x00, sizeof(aucStrDiv));

    ulDivLen = (VOS_UINT32)AT_GetWcdmaDivBandStr(aucStrDiv);

    VOS_MemCpy(pstFeATure[AT_FEATURE_DIVERSITY].aucContent, aucStrDiv, ulDivLen);

    /* UMTS */
    pstFeATure[AT_FEATURE_UMTS].ucFeatureFlag = AT_FEATURE_EXIST;
    VOS_MemCpy(pstFeATure[AT_FEATURE_UMTS].aucContent, aucStrTmp, ulLen);

    return VOS_OK;

}


VOS_VOID AT_GetGFeatureInfo(
    AT_FEATURE_SUPPORT_ST              *pstFeATure,
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstATAgentSfeatureQryCnf
)
{
    VOS_UINT32                          ulLen;

    VOS_UINT16                          usEgprsFlag;
    VOS_UINT8                           aucStrTmp[50] = {0};


    usEgprsFlag = 0;


    /* ��ȡGSMƵ����Ϣ */
    ulLen = (VOS_UINT32)AT_GetGsmBandStr(aucStrTmp,&(pstATAgentSfeatureQryCnf->stBandFeature));

    if ( 0 == ulLen )
    {
        vos_printf("AT_GetGFeatureInfo, Not Support G.\n");
        return;
    }

    /* ��ȡEDGE֧������ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Egprs_Flag, &usEgprsFlag,
                        sizeof(VOS_UINT16)))
    {
        AT_WARN_LOG("AT_GetGFeatureInfo: en_NV_Item_Egprs_Flag NV Read  Fail!");
        pstFeATure[AT_FEATURE_EDGE].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_MemCpy(pstFeATure[AT_FEATURE_EDGE].aucContent, aucStrTmp, ulLen);
    }
    else
    {
        if (usEgprsFlag != 0)
        {
            pstFeATure[AT_FEATURE_EDGE].ucFeatureFlag = AT_FEATURE_EXIST;
            VOS_MemCpy(pstFeATure[AT_FEATURE_EDGE].aucContent, aucStrTmp, ulLen);
        }
    }

    /* GPRS */
    pstFeATure[AT_FEATURE_GPRS].ucFeatureFlag = AT_FEATURE_EXIST;
    VOS_MemCpy(pstFeATure[AT_FEATURE_GPRS].aucContent, aucStrTmp, ulLen);

    /* GSM */
    pstFeATure[AT_FEATURE_GSM].ucFeatureFlag = AT_FEATURE_EXIST;
    VOS_MemCpy(pstFeATure[AT_FEATURE_GSM].aucContent, aucStrTmp, ulLen);
}

#if (FEATURE_ON == MBB_COMMON)


VOS_UINT32 AT_GetWifiFeatureInfo(VOS_UINT8 *pstFeature)
{
#if (FEATURE_ON == MBB_WIFI)

    VOS_UINT32              usBufLen = 0;
    VOS_UINT8               *pBuffer = NULL;
    WLAN_AT_BUFFER_STRU     strBuf;
    
    /* ��ȡWIFIģʽ */
    (void)PS_MEM_SET((void *)&strBuf, 0x00, sizeof(WLAN_AT_BUFFER_STRU));/*lint !e506 !e160*/
    if(AT_RETURN_SUCCESS != WlanATGetWifiModeSupport(&strBuf))
    {
        return VOS_ERR;
    }

    /* �����ַ�����װ */
    pBuffer = (VOS_UINT8 *)strBuf.buf;
    while('\0' != *pBuffer)
    {
        if(*pBuffer >= '0' && *pBuffer <= '9')
        {
            switch(*pBuffer - '0')
            {
                case AT_WLAN_MODE_CW:
                    {
                        /* WIFIģ�� cw ģʽ */
                        usBufLen += (TAF_UINT16)At_sprintf(AT_FEATURE_CONTENT_LEN_MAX,
                                                           (TAF_CHAR *)pstFeature,
                                                           (TAF_CHAR *)pstFeature + usBufLen,
                                                           "%s,",
                                                           "cw");
                        break;
                    }
                case AT_WLAN_MODE_A:
                    {
                        /* WIFIģ�� a ģʽ */
                        usBufLen += (TAF_UINT16)At_sprintf(AT_FEATURE_CONTENT_LEN_MAX,
                                                           (TAF_CHAR *)pstFeature,
                                                           (TAF_CHAR *)pstFeature + usBufLen,
                                                           "%s,",
                                                           "a");
                        break;
                    }
                case AT_WLAN_MODE_B:
                    {
                        /* WIFIģ�� b ģʽ */
                        usBufLen += (TAF_UINT16)At_sprintf(AT_FEATURE_CONTENT_LEN_MAX,
                                                           (TAF_CHAR *)pstFeature,
                                                           (TAF_CHAR *)pstFeature + usBufLen,
                                                           "%s,",
                                                           "b");
                        break;
                    }
                case AT_WLAN_MODE_G:
                    {
                        /* WIFIģ�� g ģʽ */
                        usBufLen += (TAF_UINT16)At_sprintf(AT_FEATURE_CONTENT_LEN_MAX,
                                                           (TAF_CHAR *)pstFeature,
                                                           (TAF_CHAR *)pstFeature + usBufLen,
                                                           "%s,",
                                                           "g");
                        break;
                    }
                case AT_WLAN_MODE_N:
                    {
                        /* WIFIģ�� n ģʽ */
                        usBufLen += (TAF_UINT16)At_sprintf(AT_FEATURE_CONTENT_LEN_MAX,
                                                           (TAF_CHAR *)pstFeature,
                                                           (TAF_CHAR *)pstFeature + usBufLen,
                                                           "%s,",
                                                           "n");
                        break;
                    }
                case AT_WLAN_MODE_AC:
                    {
                        /* WIFIģ�� ac ģʽ */
                        usBufLen += (TAF_UINT16)At_sprintf(AT_FEATURE_CONTENT_LEN_MAX,
                                                           (TAF_CHAR *)pstFeature,
                                                           (TAF_CHAR *)pstFeature + usBufLen,
                                                           "%s,",
                                                           "ac");
                        break;
                    }
                default:
                    break;
            }
        }
        
        pBuffer++;
    }

    /* ȥ����β���� */
    if(0 != usBufLen)
    {
        pstFeature[usBufLen - 1] = '\0';
    }
#endif
    return VOS_OK;
}
#endif


#if(FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_UINT32 AT_GetTdsFeatureInfo(AT_FEATURE_SUPPORT_ST * pstFeATure)
{
    VOS_UINT32 ulRst  = 0;
    NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU stTdsFeature;
    VOS_UINT32 i = 0;
    VOS_UINT32 ulLen;


    PS_MEM_SET(&stTdsFeature, 0x00, sizeof(stTdsFeature));

    ulRst = NV_ReadEx(MODEM_ID_0, en_NV_Item_UTRAN_TDD_FREQ_BAND, &stTdsFeature, sizeof(NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU));
    if( ulRst != ERR_MSP_SUCCESS )
    {
        vos_printf("Read EN_NV_ID_TDS_SUPPORT_FREQ_BAND failed:0x%x.\n", en_NV_Item_UTRAN_TDD_FREQ_BAND);
        return ERR_MSP_FAILURE;
    }
    if(stTdsFeature.ucBandCnt > NVIM_TDS_MAX_SUPPORT_BANDS_NUM)
    {
        vos_printf("Read en_NV_Item_UTRAN_TDD_FREQ_BAND stTdsFeature.ucBandCnt:%d.\n", stTdsFeature.ucBandCnt);
        return ERR_MSP_FAILURE;
    }

#if (FEATURE_ON == MBB_COMMON)
    if(0 == stTdsFeature.ucBandCnt)
    {
        return ERR_MSP_SUCCESS;
    }
#endif

    /* ��ȡNV�ɹ���֧��TDS */
    pstFeATure[AT_FEATURE_TDSCDMA].ucFeatureFlag = AT_FEATURE_EXIST;

    ulLen = 0;

    /* BandA:2000Hz, BanE:2300Hz, BandF:1900Hz */
    for(i = 0; i < stTdsFeature.ucBandCnt; i++)
    {
        if(ID_NVIM_TDS_FREQ_BAND_A == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), "2000,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }

        if(ID_NVIM_TDS_FREQ_BAND_E == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), "2300,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }

        if(ID_NVIM_TDS_FREQ_BAND_F == stTdsFeature.aucBandNo[i])
        {
            VOS_sprintf((VOS_CHAR*)(pstFeATure[AT_FEATURE_TDSCDMA].aucContent + ulLen), "1900,");
            ulLen = VOS_StrLen((VOS_CHAR *)pstFeATure[AT_FEATURE_TDSCDMA].aucContent);
            continue;
        }
    }

    if(ulLen > 0)
    {
        /* ���ε����һ������ */
        pstFeATure[AT_FEATURE_TDSCDMA].aucContent[ulLen - 1] = '\0';
    }

    return ERR_MSP_SUCCESS;
}
#endif

#if (FEATURE_ON == MBB_COMMON)
int get_lan_support(void)
{
#if (FEATURE_ON == MBB_FEATURE_ETH)
    return TRUE;
#else
    return FALSE;
#endif   
}
#endif

/*****************************************************************************
 �� �� ��  : get_usb_switch_support
 ��������  : ��Ʒ�Ƿ�֧��˫usb�л�
 �������  :
 �������  :
 �� �� ֵ  : 1:֧�� 0:��֧��
 ���ú���  :
 ��������  :
*****************************************************************************/
#if (FEATURE_ON == MBB_COMMON)
int get_usb_switch_support(VOS_UINT8 *pstFeature)
{

#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
    VOS_UINT32                usBufLen = 0;

    usBufLen += (TAF_UINT16)At_sprintf(AT_FEATURE_CONTENT_LEN_MAX,
                                       (TAF_CHAR*)pstFeature,
                                       (TAF_CHAR*)pstFeature + usBufLen,
                                       "%s",
                                       "0,1");

    return TRUE;
#else
    return FALSE;
#endif
}
#endif

/*****************************************************************************
 �� �� ��  : get_esim_support
 ��������  : ��Ʒ�Ƿ�֧��esim
 �������  :
 �������  :
 �� �� ֵ  : 1:֧�� 0:��֧��
 ���ú���  :
 ��������  :
*****************************************************************************/
#if (FEATURE_ON == MBB_COMMON)
int get_esim_support(void)
{
#if(FEATURE_ON == MBB_FEATURE_ESIM_SWITCH)
    return TRUE;
#else
    return FALSE;
#endif
}
#endif
/*****************************************************************************
 �� �� ��  : get_ftyreset_support
 ��������  : ��Ʒ�Ƿ�֧��ftyreset
 �������  :
 �������  :
 �� �� ֵ  : 1:֧�� 0:��֧��
 ���ú���  :
 ��������  :
*****************************************************************************/
#if (FEATURE_ON == MBB_COMMON)
int get_ftyreset_support(void)
{
#if defined(BSP_CONFIG_BOARD_STICK) || defined(BSP_CONFIG_BOARD_HILINK)
    return TRUE;
#else
    return FALSE;
#endif
}
#endif


VOS_UINT32 AT_RcvDrvAgentQrySfeatureRsp(VOS_VOID *pMsg)
{
    /* ��ʼ�� */
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_SFEATURE_QRY_CNF_STRU    *pstAtAgentSfeatureQryCnf;
    VOS_UINT8                           ucIndex;
    AT_FEATURE_SUPPORT_ST              *pstFeATure;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          ulReult;
    VOS_UINT8                           ucFeATrueNum;
    VOS_UINT8                           ucIndexTmp;
#if (FEATURE_ON == MBB_COMMON)
    VOS_UINT8                           aucWifiFeature[AT_FEATURE_CONTENT_LEN_MAX] = {0};
#endif
    VOS_UINT8                           aucUsbFeature[AT_FEATURE_CONTENT_LEN_MAX] = {0};

    VOS_UINT8                           aucFeATureName[][AT_FEATURE_NAME_LEN_MAX] =
                                        {
                                            "LTE",
                                            "HSPA+",
                                            "HSDPA",
                                            "HSUPA",
                                            "DIVERSITY",
                                            "UMTS",
                                            "EVDO",
                                            "EDGE",
                                            "GPRS",
                                            "GSM",
                                            "CDMA1X",
                                            "WIMAX",
                                            "WIFI",
                                            "GPS",
                                            "TD",
                                        #if (FEATURE_ON == MBB_COMMON)
                                            "BATTERY",
                                            "EXT-CHARGE",
                                            "SDCARD",
                                            "WIRELESS-CHARG",
                                            "USB3.0",
                                            "LAN",
                                            "COUL",
                                            "USBSWITCH",
#if(FEATURE_ON == MBB_FEATURE_ESIM_SWITCH)
                                            "ESIM",
#endif
                                            "FTYRESET",
                                        #endif
                                        };

    pRcvMsg                      = (DRV_AGENT_MSG_STRU*)pMsg;
    pstAtAgentSfeatureQryCnf     = (DRV_AGENT_SFEATURE_QRY_CNF_STRU*)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstAtAgentSfeatureQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_SFEATURE_QRY */
    if (AT_CMD_SFEATURE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    pstFeATure = (AT_FEATURE_SUPPORT_ST*)PS_MEM_ALLOC(WUEPS_PID_AT, AT_FEATURE_MAX*sizeof(AT_FEATURE_SUPPORT_ST));
    if (VOS_NULL == pstFeATure)
    {
        AT_WARN_LOG("AT_RcvDrvAgentQrySfeatureRsp: GET MEM Fail!");
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }
    VOS_MemSet(pstFeATure, 0, AT_FEATURE_MAX*sizeof(AT_FEATURE_SUPPORT_ST));


    if(HW_VER_PRODUCT_E5771S_852 != bsp_version_get_board_type())
    {
#if (FEATURE_OFF == MBB_3G_DISABLE_CTRL)
        ulReult = AT_GetWFeatureInfo(pstFeATure,pstAtAgentSfeatureQryCnf);

        if (VOS_OK != ulReult)
        {
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_ERROR);
            PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
            return VOS_OK;
        }
#endif /*FEATURE_OFF == MBB_3G_DISABLE_CTRL*/
    }

/* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
#if(FEATURE_ON == FEATURE_LTE)
    ulReult = AT_GetLteFeatureInfo(pstFeATure);
    if (VOS_OK != ulReult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_OK;
    }
#endif
/* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

#if(FEATURE_UE_MODE_TDS == FEATURE_ON)
    ulReult = AT_GetTdsFeatureInfo(pstFeATure);
    if (VOS_OK != ulReult)
    {
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_ERROR);
        PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
        return VOS_OK;
    }
#endif

    AT_GetGFeatureInfo(pstFeATure,pstAtAgentSfeatureQryCnf);

#if (FEATURE_ON == MBB_COMMON)
    if (BSP_MODULE_SUPPORT == DRV_GET_WIFI_SUPPORT())
    {
        /* �Ƿ�֧��WIFI */
        pstFeATure[AT_FEATURE_WIFI].ucFeatureFlag = AT_FEATURE_EXIST;
        (void)VOS_MemSet((void *)pstFeATure[AT_FEATURE_WIFI].aucContent, 
                         0, sizeof(pstFeATure[AT_FEATURE_WIFI].aucContent));
        
        if(VOS_OK == AT_GetWifiFeatureInfo(aucWifiFeature))
        {
            (void)VOS_MemCpy((void *)pstFeATure[AT_FEATURE_WIFI].aucContent, 
                             (void *)aucWifiFeature, 
                             VOS_StrLen((char *)aucWifiFeature));
        }
    }

    if(BSP_MODULE_SUPPORT == DRV_GET_BATTERY_SUPPORT())
    {
        /* BATTERY */
        /* ���͵�ѹֵ����װ��liujunjie��ͨ���˴���ʱΪ�գ������������ٺ�װ����ͨ */
        pstFeATure[AT_FEATURE_BATTERY].ucFeatureFlag = AT_FEATURE_EXIST;
        (void)VOS_MemSet((void *)pstFeATure[AT_FEATURE_BATTERY].aucContent, 
                         0, sizeof(pstFeATure[AT_FEATURE_BATTERY].aucContent));
    }
    
    if(TRUE == chg_tbat_sfeature_inquiry_extchg())
    {
        /* �Ƿ�֧�ֶ����� */
        pstFeATure[AT_FEATURE_EXTCHARGE].ucFeatureFlag = AT_FEATURE_EXIST;
        (void)VOS_MemSet((void *)pstFeATure[AT_FEATURE_EXTCHARGE].aucContent, 
                         0, sizeof(pstFeATure[AT_FEATURE_EXTCHARGE].aucContent));
    }

    if(BSP_MODULE_SUPPORT == DRV_GET_SD_SUPPORT())
    {
        /* �Ƿ�֧��SD�� */
        pstFeATure[AT_FEATURE_SDCARD].ucFeatureFlag = AT_FEATURE_EXIST;
        (void)VOS_MemSet((void *)pstFeATure[AT_FEATURE_SDCARD].aucContent, 
                         0, sizeof(pstFeATure[AT_FEATURE_SDCARD].aucContent));
    }

    if(TRUE == chg_tbat_sfeature_inquiry_wireless())
    {
        /* �Ƿ�֧�����߳�� */
        pstFeATure[AT_FEATURE_WIRELESS].ucFeatureFlag = AT_FEATURE_EXIST;
        (void)VOS_MemSet((void *)pstFeATure[AT_FEATURE_WIRELESS].aucContent, 
                         0, sizeof(pstFeATure[AT_FEATURE_WIRELESS].aucContent));
    }

    if(OK == USB_CAPABILITY_THREE())
    {
        /* �Ƿ�֧��USB3.0���� */
        pstFeATure[AT_FEATURE_USB3_0].ucFeatureFlag = AT_FEATURE_EXIST;
        (void)VOS_MemSet((void *)pstFeATure[AT_FEATURE_USB3_0].aucContent, 
                         0, sizeof(pstFeATure[AT_FEATURE_USB3_0].aucContent));
    }
    if(TRUE == get_coul_support())
    {
        pstFeATure[AT_FEATURE_COUL].ucFeatureFlag = AT_FEATURE_EXIST;
        (void)VOS_MemSet((void *)pstFeATure[AT_FEATURE_COUL].aucContent,
                         0, sizeof(pstFeATure[AT_FEATURE_COUL].aucContent));
    } /* BSP_CONFIG_BOARD_E5771S_852 */

    if(TRUE == get_usb_switch_support(aucUsbFeature))
    {
        pstFeATure[AT_FEATURE_USB_SWITCH].ucFeatureFlag = AT_FEATURE_EXIST;
        (void)VOS_MemSet((void*)pstFeATure[AT_FEATURE_USB_SWITCH].aucContent,
                         0, sizeof(pstFeATure[AT_FEATURE_USB_SWITCH].aucContent));
        (void)VOS_MemCpy((void*)pstFeATure[AT_FEATURE_USB_SWITCH].aucContent,
                         (void*)aucUsbFeature,
                         VOS_StrLen((char*)aucUsbFeature));
    }

#if(FEATURE_ON == MBB_FEATURE_ESIM_SWITCH)
    if(TRUE == get_esim_support())
    {
        pstFeATure[AT_FEATURE_ESIM].ucFeatureFlag = AT_FEATURE_EXIST;
        (void)VOS_MemSet((void*)pstFeATure[AT_FEATURE_ESIM].aucContent,
                         0, sizeof(pstFeATure[AT_FEATURE_ESIM].aucContent));
    }
#endif
    if(TRUE == get_ftyreset_support())
    {
        pstFeATure[AT_FEATURE_FTYRESET].ucFeatureFlag = AT_FEATURE_EXIST;
        (void)VOS_MemSet((void*)pstFeATure[AT_FEATURE_FTYRESET].aucContent,
                         0, sizeof(pstFeATure[AT_FEATURE_FTYRESET].aucContent));
    }

#if (FEATURE_ON == MBB_FEATURE_ETH)
	if(TRUE == get_lan_support())
    {
        /* �Ƿ�֧��LAN���� */
        pstFeATure[AT_FEATURE_LAN].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_sprintf((VOS_CHAR*)pstFeATure[AT_FEATURE_LAN].aucContent, LANPORTNUM);
    }
#endif
#else
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_SUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        /* WIFI */
        pstFeATure[AT_FEATURE_WIFI].ucFeatureFlag = AT_FEATURE_EXIST;
        VOS_sprintf((VOS_CHAR*)pstFeATure[AT_FEATURE_WIFI].aucContent, "B,G,N");
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
#endif

    /* ����֧�����Եĸ��� */
    ucFeATrueNum = 0;
    for (ucIndexTmp = 0; ucIndexTmp < AT_FEATURE_MAX; ucIndexTmp++)
    {
        VOS_MemCpy(pstFeATure[ucIndexTmp].aucFeatureName, aucFeATureName[ucIndexTmp],sizeof(aucFeATureName[ucIndexTmp]));
        if (AT_FEATURE_EXIST == pstFeATure[ucIndexTmp].ucFeatureFlag)
        {
            ucFeATrueNum++;
        }
    }
#if (FEATURE_ON == MBB_CRADLE_FEATURE)
    ucFeATrueNum = 1;
#endif
    ulLen = 0;
    /* ��ӡ���֧�ֵ������� */
    ulLen = (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + ulLen,
                                   "%s:%d%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucFeATrueNum,
                                   gaucAtCrLf);

    /* ���д�ӡ���֧�ֵ����� */
    for (ucIndexTmp = 0; ucIndexTmp < AT_FEATURE_MAX; ucIndexTmp++)
    {
#if (FEATURE_ON == MBB_CRADLE_FEATURE)
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + ulLen,
                                       "%s:%s,%s%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstFeATure[AT_FEATURE_WIFI].aucFeatureName,
                                       pstFeATure[AT_FEATURE_WIFI].aucContent,
                                       gaucAtCrLf);
        break;
#endif /* MBB_CRADLE_FEATURE */
        if (AT_FEATURE_EXIST == pstFeATure[ucIndexTmp].ucFeatureFlag)
        {
        #if (FEATURE_ON == MBB_COMMON)
            if(VOS_StrLen((VOS_CHAR*)(pstFeATure[ucIndexTmp].aucContent)) == 0)
            {
                ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + ulLen,
                                           "%s:%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstFeATure[ucIndexTmp].aucFeatureName,
                                           gaucAtCrLf);
            }
            else
            {
                ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + ulLen,
                                           "%s:%s,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstFeATure[ucIndexTmp].aucFeatureName,
                                           pstFeATure[ucIndexTmp].aucContent,
                                           gaucAtCrLf);
            }
        #else
            ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + ulLen,
                                           "%s:%s,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstFeATure[ucIndexTmp].aucFeatureName,
                                           pstFeATure[ucIndexTmp].aucContent,
                                           gaucAtCrLf);
        #endif
        }
    }

    gstAtSendData.usBufLen = (VOS_UINT16)(ulLen - (VOS_UINT32)VOS_StrLen((VOS_CHAR*)gaucAtCrLf));

    At_FormatResultData(ucIndex, AT_OK);
    PS_MEM_FREE(WUEPS_PID_AT, pstFeATure);
    return VOS_OK;

}



VOS_UINT32 AT_RcvDrvAgentQryProdtypeRsp(VOS_VOID * pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PRODTYPE_QRY_CNF_STRU    *stProdTypeCnf;
    VOS_UINT8                           ucIndex;

    /* ��ʼ����Ϣ */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg;
    stProdTypeCnf            = (DRV_AGENT_PRODTYPE_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(stProdTypeCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryProdtypeRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryProdtypeRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PRODTYPE_QRY */
    if (AT_CMD_PRODTYPE_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stProdTypeCnf->ulProdType);

    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;
}

/* Added by L60609 for AT Project��2011-10-04,  Begin*/

VOS_VOID At_ProcMsgFromDrvAgent(DRV_AGENT_MSG_STRU *pMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*��g_astDrvAgentMsgProcTab�л�ȡ��Ϣ����*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromDrvAgentTab)/sizeof(AT_PROC_MSG_FROM_DRV_AGENT_STRU);

    /*����Ϣ���л�ȡMSG ID*/
    ulMsgId  = ((DRV_AGENT_MSG_STRU *)pMsg)->ulMsgId;

    /*g_astDrvAgentMsgProcTab���������Ϣ�ַ�*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromDrvAgentTab[i].ulMsgType == ulMsgId)
        {
            ulRst = g_astAtProcMsgFromDrvAgentTab[i].pProcMsgFunc(pMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_ProcMsgFromDrvAgent: Msg Proc Err!");
            }

            return;
        }
    }

    /*û���ҵ�ƥ�����Ϣ*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_ProcMsgFromDrvAgent: Msg Id is invalid!");
    }

    return;
}


TAF_UINT32 At_PB_Unicode2UnicodePrint(TAF_UINT32 MaxLength,TAF_INT8 *headaddr,TAF_UINT8 *pucDst, TAF_UINT8 *pucSrc, TAF_UINT16 usSrcLen)
{
    TAF_UINT16 usLen    = 0;
    TAF_UINT16 usChkLen = 0;
    TAF_UINT8  ucHigh1  = 0;
    TAF_UINT8  ucHigh2  = 0;
    TAF_UINT8 *pWrite   = pucDst;
    TAF_UINT8 *pRead    = pucSrc;

    if(((TAF_UINT32)(pucDst - (TAF_UINT8 *)headaddr) + (2 * usSrcLen)) >= MaxLength)
    {
        AT_ERR_LOG("At_Unicode2UnicodePrint too long");
        return 0;
    }

    /* ɨ�������ִ� */
    while( usChkLen < usSrcLen )
    {
        /* ��һ���ֽ� */
        ucHigh1 = 0x0F & (*pRead >> 4);
        ucHigh2 = 0x0F & *pRead;

        if(0x09 >= ucHigh1)   /* 0-9 */
        {
            *pWrite++ = ucHigh1 + 0x30;
        }
        else if(0x0A <= ucHigh1)    /* A-F */
        {
            *pWrite++ = ucHigh1 + 0x37;
        }
        else
        {

        }

        if(0x09 >= ucHigh2)   /* 0-9 */
        {
            *pWrite++ = ucHigh2 + 0x30;
        }
        else if(0x0A <= ucHigh2)    /* A-F */
        {
            *pWrite++ = ucHigh2 + 0x37;
        }
        else
        {

        }

        /* ��һ���ַ� */
        usChkLen++;
        pRead++;


        usLen += 2;    /* ��¼���� */
    }

    return usLen;
}


TAF_UINT16 At_PbGsmFormatPrint(TAF_UINT16 usMaxLength,
                               TAF_UINT8  *pucDst,
                               TAF_UINT8  *pucSrc,
                               TAF_UINT16 usSrcLen)
{
    TAF_UINT32  i;

    if (usSrcLen > usMaxLength)
    {
        AT_ERR_LOG("At_PbGsmFormatPrint error: too long");

        return 0;
    }

    for (i = 0; i < usSrcLen; i++)
    {
        /* �����bit���� */
        pucDst[i] = pucSrc[i] & AT_PB_GSM7_CODE_MAX_VALUE;
    }

    return usSrcLen;
}


TAF_UINT32 At_PbOneUnicodeToIra(TAF_UINT16 usUnicodeChar, TAF_UINT8 *pucDst)
{
    TAF_UINT16 usIndex;

    for(usIndex = 0; usIndex < AT_PB_IRA_MAX_NUM; usIndex++)
    {
        if(usUnicodeChar == g_astIraToUnicode[usIndex].usUnicode)
        {
            *pucDst = g_astIraToUnicode[usIndex].ucOctet;

            return AT_SUCCESS;
        }
    }

    /* δ�ҵ�UCS2��Ӧ��IRA���� */
    AT_LOG1("At_PbOneUnicodeToIra error: no found [%x]",usUnicodeChar);

    return AT_FAILURE;
}


TAF_UINT16 At_PbUnicodeToIraFormatPrint(TAF_UINT16 usMaxLength,
                                        TAF_UINT8  *pucDst,
                                        TAF_UINT8  *pucSrc,
                                        TAF_UINT16 usSrcLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usRetLen = 0;
    TAF_UINT8       *pucData = pucSrc;
    TAF_UINT16      usUnicodeChar;

    /* IRA�����ĳ�����UCS2�������ȵ�һ�� */
    usRetLen = usSrcLen >> 1;

    /* ���洢�ռ��Ƿ��㹻 */
    if (usRetLen > usMaxLength)
    {
       AT_ERR_LOG("At_PbUnicodeToIraFormatPrint error: too long");

       return 0;
    }

    /* �����UCS2�ַ�ͨ�����ת��ΪIRA���� */
    for (usIndex = 0; usIndex < usRetLen; usIndex++)
    {
        /* �Ƚ�UINT8����תΪUINT16 */
        usUnicodeChar = (*pucData << 8) | (*(pucData + 1));
        pucData += 2;

        if (AT_SUCCESS != At_PbOneUnicodeToIra(usUnicodeChar, &pucDst[usIndex]))
        {
            AT_ERR_LOG("At_PbUnicodeToIraFormatPrint error: no found");

            return 0;
        }
    }

    return usRetLen;
}


TAF_VOID At_PbUnicode82FormatPrint(TAF_UINT8  *puc82Code,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{

    TAF_UINT16      usIndex;
    TAF_UINT16      usBaseCode;
    TAF_UINT16      usUnicode;
    TAF_UINT16      usSrcLen;
    TAF_UINT16      usDstIndex  = 0;
    TAF_UINT16      usGsmCodeLen;
    TAF_UINT16      usGsm2UCS2CodeLen;
    TAF_UINT16      *pusUnicode = (TAF_UINT16 *)pucDst;
    TAF_UINT8       *pucSrc;

    /* ȡ��82����ĳ��� */
    usSrcLen = puc82Code[0];

    /* ȡ��82�����Basecode */
    usBaseCode = (puc82Code[1] << 8) | puc82Code[2];

    if((SI_PB_ALPHATAG_MAX_LEN < usSrcLen)||(0xFFFF == usBaseCode)) /*���ݳ��ȴ���*/
    {
        *pusDstLen = 0;

        return;
    }

    /* ȡ��82���������, ���ĸ����Ժ��Byte��ʾ82ѹ��������� */
    pucSrc = puc82Code + 3;

    /* �ӵ��ĸ��ֽڿ�ʼ��82��������� */
    for(usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        usGsmCodeLen = 0;
        while((AT_PB_GSM7_CODE_MAX_VALUE >= pucSrc[usIndex + usGsmCodeLen])
           && ((usIndex + usGsmCodeLen) < usSrcLen))
        {
            usGsmCodeLen++;
        }

        if(0 != usGsmCodeLen)
        {
            usGsm2UCS2CodeLen = 0;
            At_PbGsmToUnicode((pucSrc + usIndex), usGsmCodeLen,
                             (TAF_UINT8 *)(pusUnicode + usDstIndex),
                             &usGsm2UCS2CodeLen);

            usIndex    += (usGsmCodeLen - 1);
            usDstIndex += (usGsm2UCS2CodeLen >> 1);

            continue;
        }

        /* 82 �����Ƚ���8bit���������������� */
        usUnicode = usBaseCode + (pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE);

        AT_UNICODE2VALUE(usUnicode);

        pusUnicode[usDstIndex++] = usUnicode;
    }

    *pusDstLen = (TAF_UINT16)(usDstIndex << 1);

    return;
}


TAF_VOID At_PbUnicode81FormatPrint(TAF_UINT8  *puc81Code,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usUnicode;
    TAF_UINT16      usBaseCode;
    TAF_UINT16      usSrcLen;
    TAF_UINT16      usDstIndex  = 0;
    TAF_UINT16      usGsmCodeLen;
    TAF_UINT16      usGsm2UCS2CodeLen;
    TAF_UINT16      *pusUnicode = (TAF_UINT16 *)pucDst;
    TAF_UINT8       *pucSrc;

    if(SI_PB_ALPHATAG_MAX_LEN < puc81Code[0])    /*�ַ��������ܴ������������ֵ*/
    {
        *pusDstLen = 0;

        return;
    }

    /* ȡ��81����ĳ��� */
    usSrcLen = puc81Code[0];

    /* ȡ��81����Ļ�ָ�� */
    usBaseCode = puc81Code[1] << 7;

    /* ȡ��81���������, ���������Ժ��Byte��ʾ81ѹ��������� */
    pucSrc = puc81Code + 2;

    /* �ӵ������ֽڿ�ʼ��81��������� */
    for (usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        usGsmCodeLen = 0;
        while ((AT_PB_GSM7_CODE_MAX_VALUE >= pucSrc[usIndex + usGsmCodeLen])
            && ((usIndex+usGsmCodeLen) < usSrcLen))
        {
            usGsmCodeLen++;
        }

        if (0 != usGsmCodeLen)
        {
            usGsm2UCS2CodeLen = 0;
            At_PbGsmToUnicode((pucSrc + usIndex), usGsmCodeLen,
                             (TAF_UINT8 *)(pusUnicode + usDstIndex),
                             &usGsm2UCS2CodeLen);

            usIndex    += (usGsmCodeLen - 1);
            usDstIndex += (usGsm2UCS2CodeLen >> 1);

            continue;
        }

        /* 81�����Ƚ���8bit���������������� */
        usUnicode = usBaseCode + (pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE);

        AT_UNICODE2VALUE(usUnicode);

        pusUnicode[usDstIndex++] = usUnicode;
    }

    *pusDstLen = (TAF_UINT16)(usDstIndex << 1);

    return;
}


TAF_VOID At_PbUnicode80FormatPrint(TAF_UINT8  *pucSrc,
                                   TAF_UINT16 usSrcLen,
                                   TAF_UINT8  *pucDst,
                                   TAF_UINT16 *pusDstLen)
{
    if((0xFF == pucSrc[0])&&(0xFF == pucSrc[1]))   /*�����ַ�ΪFFFF����Ϊ��ǰ����Ϊ��*/
    {
        *pusDstLen = 0;
    }
    else
    {
        /* ����80��־λ */
        VOS_MemCpy(pucDst, pucSrc, usSrcLen);

        *pusDstLen = usSrcLen;
    }

    return;
}


TAF_UINT32 At_PbGsmExtToUnicode(TAF_UINT8 ucGsmExtChar, TAF_UINT16 *pusUnicodeChar)
{
    TAF_UINT16      usIndex;

    /* ����GSM��UNICODE��չ���ҵ��򷵻سɹ������򷵻�ʧ�� */
    for (usIndex = 0; usIndex < AT_PB_GSM7EXT_MAX_NUM; usIndex++)
    {
        if (ucGsmExtChar == g_astGsm7extToUnicode[usIndex].ucOctet)
        {
            *pusUnicodeChar = g_astGsm7extToUnicode[usIndex].usUnicode;

            return AT_SUCCESS;
        }
    }

    AT_LOG1("At_PbGsmExtToUnicode warning: no found [0x%x]", ucGsmExtChar);

    return AT_FAILURE;
}


TAF_VOID At_PbGsmToUnicode(TAF_UINT8  *pucSrc,
                           TAF_UINT16 usSrcLen,
                           TAF_UINT8  *pucDst,
                           TAF_UINT16 *pusDstLen)
{
    TAF_UINT16      usIndex;
    TAF_UINT16      usUnicodeLen = 0;
    TAF_UINT16      *pusUnicode  = (TAF_UINT16 *)pucDst;
    TAF_UINT16      usUnicodeChar;

    for (usIndex = 0; usIndex < usSrcLen; usIndex++)
    {
        /* Ϊ������Щƽ̨��GSMģʽ��д���¼ʱδ�����BIT���� */
        pucSrc[usIndex] = pucSrc[usIndex] & AT_PB_GSM7_CODE_MAX_VALUE;

        /* ��0x1B�ַ���ֱ�Ӳ�GSM��UNICODE������ */
        if (AT_PB_GSM7EXT_SYMBOL != pucSrc[usIndex])
        {
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usUnicodeLen++;

            continue;
        }

        /* ��ǰGSM����Ϊ0x1bʱ,����Ϊ��չ��־ */
        if ((usSrcLen - usIndex) < 2)
        {
            /* ���һ���ֽ�Ϊ0x1B����GSM��UNICODE������, ��0x1B��ΪSPACE */
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usUnicodeLen++;

            continue;
        }

        /* ����0x1B 0x1B���������Ϊ���ǲ�֧�ֵ�������չ�����ֱ�ӽ�0x1B
            0x1B��ΪSPACE SPACE */
        if (AT_PB_GSM7EXT_SYMBOL == pucSrc[usIndex + 1])
        {
            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;

            usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex + 1]].usUnicode;
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;

            usIndex++;
            usUnicodeLen += 2;

            continue;
        }

        /* 0x1B����Ϊ��־������GSM��UNICODE��չ�� */
        if (AT_SUCCESS == At_PbGsmExtToUnicode(pucSrc[usIndex + 1], &usUnicodeChar))
        {
            AT_UNICODE2VALUE(usUnicodeChar);
            *pusUnicode = usUnicodeChar;
            pusUnicode++;
            usIndex++;
            usUnicodeLen++;

            continue;
        }

       /* ����1BXX��δ����չ���У���XX��Ϊ0x1B���������ΪSPACE+XX��Ӧ���ַ� */
       usUnicodeChar = g_astGsmToUnicode[pucSrc[usIndex]].usUnicode;
       AT_UNICODE2VALUE(usUnicodeChar);
       *pusUnicode = usUnicodeChar;
       pusUnicode++;
       usUnicodeLen++;
    }

    /* GSM7BIT �����п�������չ�����ַ���GSM7bit��UNICODEת�����Ȳ�һ����ԭ�������ȵ�2�� */
    *pusDstLen = (TAF_UINT16)(usUnicodeLen << 1);

    return;
}


TAF_VOID At_PbRecordToUnicode(SI_PB_EVENT_INFO_STRU *pstEvent,
                              TAF_UINT8             *pucDecode,
                              TAF_UINT16            *pusDecodeLen)
{
    TAF_UINT16      usDecodeLen = 0;

    switch(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
    {
        case SI_PB_ALPHATAG_TYPE_GSM:
            At_PbGsmToUnicode(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                              pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength,
                              pucDecode,
                              &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_80:
            At_PbUnicode80FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_81:
            At_PbUnicode81FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        case SI_PB_ALPHATAG_TYPE_UCS2_82:
            At_PbUnicode82FormatPrint(pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                      pucDecode,
                                      &usDecodeLen);
            break;
        default:
            AT_ERR_LOG("At_PbRecordToUnicode error: not support code type");

            break;
    }

    *pusDecodeLen = usDecodeLen;

    return;
}


TAF_UINT32 At_Pb_AlaphPrint(TAF_UINT16            *pusDataLen,
                            SI_PB_EVENT_INFO_STRU *pstEvent,
                            TAF_UINT8             *pucData)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              usDecodeLen = 0;
    TAF_UINT16              usReturnLen = 0;
    TAF_UINT8               aucDecode[500] = {0};

    if (AT_CSCS_GSM_7Bit_CODE == gucAtCscsType)
    {
        /* ��GSM�ַ����£���֧��UCS2���� */
        if ((SI_PB_ALPHATAG_TYPE_UCS2_80 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_81 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_82 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType))
        {
            usReturnLen = 0;

            AT_LOG1("At_Pb_AlaphPrint error: GSM7 doesn't read UCS code[%d]",
                    pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);
            return AT_FAILURE;
        }

        usReturnLen = At_PbGsmFormatPrint((AT_CMD_MAX_LEN - usLength),
                                          (pucData + usLength),
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
    }
    else  /* ��ǰ�ַ���ΪUCS2��IRAʱ */
    {
        /* ��ǰ�ַ���ΪUCS2��IRAʱ���ȸ��ݴ洢��ʽת��ΪUCS2���� */
        At_PbRecordToUnicode(pstEvent, aucDecode, &usDecodeLen);

        /* ��ǰ�ַ���ΪIRAʱ����UCS2ת��ΪIRA�������*/
        if (AT_CSCS_IRA_CODE == gucAtCscsType)
        {
            usReturnLen = At_PbUnicodeToIraFormatPrint((AT_CMD_MAX_LEN - usLength),
                                                       (pucData + usLength),
                                                       aucDecode,
                                                       usDecodeLen);
        }

        /* ��ǰ�ַ���ΪUCS2ʱ����UCS2ת��Ϊ��ӡ��ʽ���*/
        if (AT_CSCS_UCS2_CODE == gucAtCscsType)
        {
            usReturnLen = (TAF_UINT16)At_Unicode2UnicodePrint(AT_CMD_MAX_LEN,
                                                              (TAF_INT8 *)pucData,
                                                              (pucData + usLength),
                                                              aucDecode,
                                                              usDecodeLen);
        }
    }

    if (0 == usReturnLen)
    {
        gstAtSendData.usBufLen = 0;

        AT_LOG1("At_Pb_AlaphPrint error: usReturnLen = 0,gucAtCscsType = [%d]", gucAtCscsType);

        return AT_FAILURE;
    }

    usLength    += usReturnLen;
    *pusDataLen  = usLength;

    return AT_SUCCESS;
}


TAF_UINT32 At_Pb_CnumAlaphPrint(TAF_UINT16            *pusDataLen,
                            SI_PB_EVENT_INFO_STRU *pstEvent,
                            TAF_UINT8             *pucData)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              usDecodeLen = 0;
    TAF_UINT16              usReturnLen = 0;
    TAF_UINT8               aucDecode[500] = {0};

    if (AT_CSCS_GSM_7Bit_CODE == gucAtCscsType)
    {
        /* ��GSM�ַ����£���֧��UCS2���� */
        if ((SI_PB_ALPHATAG_TYPE_UCS2_80 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_81 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType)
         || (SI_PB_ALPHATAG_TYPE_UCS2_82 == pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType))
        {

            AT_LOG1("At_Pb_AlaphPrint error: GSM7 doesn't read UCS code[%d]",
                    pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);
            return AT_SUCCESS;
        }

        usReturnLen = At_PbGsmFormatPrint((AT_CMD_MAX_LEN - usLength),
                                          (pucData + usLength),
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                          pstEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);
    }
    else  /* ��ǰ�ַ���ΪUCS2��IRAʱ */
    {
        /* ��ǰ�ַ���ΪUCS2��IRAʱ���ȸ��ݴ洢��ʽת��ΪUCS2���� */
        At_PbRecordToUnicode(pstEvent, aucDecode, &usDecodeLen);

        /* ��ǰ�ַ���ΪIRAʱ����UCS2ת��ΪIRA�������*/
        if (AT_CSCS_IRA_CODE == gucAtCscsType)
        {
            usReturnLen = At_PbUnicodeToIraFormatPrint((AT_CMD_MAX_LEN - usLength),
                                                       (pucData + usLength),
                                                       aucDecode,
                                                       usDecodeLen);
        }

        /* ��ǰ�ַ���ΪUCS2ʱ����UCS2ת��Ϊ��ӡ��ʽ���*/
        if (AT_CSCS_UCS2_CODE == gucAtCscsType)
        {
            usReturnLen = (TAF_UINT16)At_Unicode2UnicodePrint(AT_CMD_MAX_LEN,
                                                              (TAF_INT8 *)pucData,
                                                              (pucData + usLength),
                                                              aucDecode,
                                                              usDecodeLen);
        }
    }

    if (0 == usReturnLen)
    {

        AT_LOG1("At_Pb_AlaphPrint error: usReturnLen = 0,gucAtCscsType = [%d]", gucAtCscsType);

        return AT_SUCCESS;
    }

    usLength    += usReturnLen;
    *pusDataLen  = usLength;

    return AT_SUCCESS;
}


TAF_VOID AT_Pb_NumberPrint(TAF_UINT16 *pusDataLen, SI_PB_EVENT_INFO_STRU *pstEvent, TAF_UINT8 *pucData)
{
    TAF_UINT16      usLength = *pusDataLen;

    if(0 == pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData+usLength,
                                           ",\"\",129");
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           ",\"");

        if (PB_NUMBER_TYPE_INTERNATIONAL == pstEvent->PBEvent.PBReadCnf.PBRecord.NumberType )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pucData,
                                               (TAF_CHAR *)pucData+usLength,
                                               "+");
        }

        PS_MEM_CPY(pucData + usLength, pstEvent->PBEvent.PBReadCnf.PBRecord.Number,
                   pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength);

        usLength += (TAF_UINT16)pstEvent->PBEvent.PBReadCnf.PBRecord.NumberLength;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           "\"");

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pucData,
                                           (TAF_CHAR *)pucData + usLength,
                                           ",%d",
                                           pstEvent->PBEvent.PBReadCnf.PBRecord.NumberType);
    }

    *pusDataLen  = usLength;

    return;
}


TAF_UINT32 At_PbCNUMCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT32              ulResult;

    if(SI_PB_CONTENT_INVALID == pEvent->PBEvent.PBReadCnf.PBRecord.ValidFlag)
    {
        return AT_SUCCESS;
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
#if(FEATURE_OFF == MBB_FEATURE_BOX_FTEN)
    /* ע��:������Ҫ���ݱ������ͽ�������������ASCII��ֱ�Ӵ�ӡ�����UNICODE��Ҫת�� */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {
         ulResult = At_Pb_CnumAlaphPrint(&usLength, pEvent, pucData);

        if(AT_SUCCESS != ulResult)
        {
            At_FormatResultData(ucIndex, AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING);

            return AT_FAILURE;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"\"");
#endif


    /* ���绰���뼰�������ʹ����װΪ���� */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);

    *pusDataLen = usLength;

    return AT_SUCCESS;
}


TAF_UINT32 At_PbCPBR2CmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT32              ulResult;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);


    /* ���绰���뼰�������ʹ����װΪ���� */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);

    /* ע��:������Ҫ���ݱ������ͽ�������������ASCII��ֱ�Ӵ�ӡ�����UNICODE��Ҫת�� */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,",\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {
        ulResult = At_Pb_AlaphPrint(&usLength, pEvent, pucData);

        if(AT_SUCCESS != ulResult)
        {
            At_FormatResultData(ucIndex, AT_CME_INVALID_CHARACTERS_IN_TEXT_STRING);

            return AT_FAILURE;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                (TAF_CHAR *)pucData+usLength, "\"");

    *pusDataLen = usLength;

    return AT_SUCCESS;
}



TAF_UINT32 At_PbCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,TAF_UINT8 *pucData,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                    (TAF_CHAR *)pucData+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);


    /* ���绰���뼰�������ʹ����װΪ���� */
    AT_Pb_NumberPrint(&usLength, pEvent, pucData);

    /* ע��:������Ҫ���ݱ������ͽ�������������ASCII��ֱ�Ӵ�ӡ�����UNICODE��Ҫת�� */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,",\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {

        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))  /* DATA:IRA */
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                                (TAF_CHAR *)pucData+usLength, "%X",
                                                pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);

            usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pucData,
                                        pucData+usLength, pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            if((pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength%2) == 0)/*����������������Ҫ���油��FF*/
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,(TAF_CHAR *)pucData + usLength,"FF");
            }
        }
        else                                    /* DATA:UCS2 */
        {
            PS_MEM_CPY((TAF_CHAR *)pucData + usLength,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            usLength += pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                (TAF_CHAR *)pucData+usLength, "\"");

    if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                        (TAF_CHAR *)pucData+usLength, ",1");
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pucData,
                                        (TAF_CHAR *)pucData+usLength, ",0");
    }

    *pusDataLen = usLength;

    return AT_SUCCESS;
}


TAF_VOID At_PbEmailPrint(TAF_UINT8  *pucSrc,
                         TAF_UINT16 usSrcLen,
                         TAF_UINT8  *pucDst,
                         TAF_UINT16 *pusDstLen)
{
    TAF_UINT8   aucUCS2Code[2 * SI_PB_EMAIL_MAX_LEN];
    TAF_UINT16  usUCS2CodeLen;
    TAF_UINT16  usEMailLen = usSrcLen;

    TAF_UINT16  usReturnLen;

    /* ��EMAIL���ȴ���64Byte�����нضϴ��� */
    if(SI_PB_EMAIL_MAX_LEN < usEMailLen)
    {
        usEMailLen = SI_PB_EMAIL_MAX_LEN;
    }

    /* �Ƚ�GSMģʽת��UCS2ģʽ */
    At_PbGsmToUnicode(pucSrc, usEMailLen, aucUCS2Code, &usUCS2CodeLen);

    /* �ٽ�UCS2ģʽת��IRAģʽ */
    usReturnLen = At_PbUnicodeToIraFormatPrint(usSrcLen, pucDst, aucUCS2Code, usUCS2CodeLen);
    if (0 == usReturnLen)
    {
        AT_INFO_LOG("At_PbEmailPrint error: usReturnLen = 0");
        return;
    }

    *pusDstLen = (TAF_UINT16)(usUCS2CodeLen >> 1);

    return;
}


TAF_UINT32 At_PbSCPBRCmdPrint(VOS_UINT8 ucIndex,TAF_UINT16 *pusDataLen,SI_PB_EVENT_INFO_STRU *pEvent)
{
    TAF_UINT16              usLength = *pusDataLen;
    TAF_UINT16              i;
    TAF_UINT16              usEmailLen = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%s: ",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%d",
                                    pEvent->PBEvent.PBReadCnf.PBRecord.Index);


    /* ���绰���뼰�������ʹ����װΪ���� */
    AT_Pb_NumberPrint(&usLength, pEvent, pgucAtSndCrLfAddr);

    for(i = 0; i < 3; i++)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",\"");

        if(0 == pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\",129");

            continue;
        }

        if (PB_NUMBER_TYPE_INTERNATIONAL == pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberType )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "+");
        }

        PS_MEM_CPY(pgucAtSndCrLfAddr + usLength,pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].Number,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength);

        usLength += (TAF_UINT16)pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberLength;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                        (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",%d",
                                        pEvent->PBEvent.PBReadCnf.PBRecord.AdditionNumber[i].NumberType);
    }

    /* ע��:������Ҫ���ݱ������ͽ�������������ASCII��ֱ�Ӵ�ӡ�����UNICODE��Ҫת�� */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr + usLength,",\"");

    if(pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength != 0)
    {
        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))  /* DATA:IRA */
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                                (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "%X",
                                                pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType);

            usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCrLfAddr,
                                        pgucAtSndCrLfAddr+usLength, pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            if((pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength%2) == 0)/*����������������Ҫ���油��FF*/
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr + usLength,"FF");
            }
        }
        else                                    /* DATA:UCS2 */
        {
            PS_MEM_CPY((TAF_CHAR *)pgucAtSndCrLfAddr + usLength,
                        pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTag,
                        pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength);

            usLength += pEvent->PBEvent.PBReadCnf.PBRecord.ucAlphaTagLength;
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

    if (AT_CMD_SCPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {

        if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBReadCnf.PBRecord.AlphaTagType&0x80))
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",1");
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                            (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",0");
        }
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, ",\"");

    if ( 0 != pEvent->PBEvent.PBReadCnf.PBRecord.Email.EmailLen )
    {
        At_PbEmailPrint(pEvent->PBEvent.PBReadCnf.PBRecord.Email.Email,
                        (TAF_UINT16)pEvent->PBEvent.PBReadCnf.PBRecord.Email.EmailLen,
                        (TAF_UINT8 *)(pgucAtSndCrLfAddr + usLength),
                        &usEmailLen);

        usLength += usEmailLen;

    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                    (TAF_CHAR *)pgucAtSndCrLfAddr+usLength, "\"");

    *pusDataLen = usLength;

    return AT_SUCCESS;
}

/*****************************************************************************
 Prototype      : At_PbSearchCnfProc
 Description    : �绰���������ݴ�ӡ����
 Input          : pEvent --- �¼�����
 Output         :
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : h59254
  1.Date        : 2009-03-14
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_VOID At_PbSearchCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent)
{
    TAF_UINT16              usLength = 0;

    gulPBPrintTag = TAF_TRUE;

/*
    if(0 != usLength)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr, (TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
    }
*/
    if(pEvent->PBEvent.PBSearchCnf.PBRecord.ValidFlag == SI_PB_CONTENT_INVALID)/*��ǰ��������Ч*/
    {
        return;              /*���ز�����*/
    }

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%d",pEvent->PBEvent.PBSearchCnf.PBRecord.Index);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",\"");

    if (PB_NUMBER_TYPE_INTERNATIONAL == pEvent->PBEvent.PBSearchCnf.PBRecord.NumberType)
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"+");
    }

    PS_MEM_CPY(pgucAtSndCodeAddr + usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.Number, pEvent->PBEvent.PBSearchCnf.PBRecord.NumberLength);
    usLength += (TAF_UINT16)pEvent->PBEvent.PBSearchCnf.PBRecord.NumberLength;
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d,",pEvent->PBEvent.PBSearchCnf.PBRecord.NumberType);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");
    /* PS_MEM_CPY((TAF_CHAR *)pgucAtSndCodeAddr + usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag, pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength); */
    /* usLength += pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength; */

    if(SI_PB_ALPHATAG_TYPE_UCS2 == (pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTagType & 0x80))  /* DATA:IRA */
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr+usLength,"%X",pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTagType);

        usLength += (TAF_UINT16)At_PB_Unicode2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCodeAddr,pgucAtSndCodeAddr+usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);

        if((pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength%2) == 0)/*����������������Ҫ���油��FF*/
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"FF");
        }
    }
    else                                    /* DATA:UCS2 */
    {
        if(AT_CSCS_UCS2_CODE == gucAtCscsType)       /* +CSCS:UCS2 */
        {
            usLength += (TAF_UINT16)At_Ascii2UnicodePrint(AT_CMD_MAX_LEN,(TAF_INT8 *)pgucAtSndCodeAddr,pgucAtSndCodeAddr+usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);
        }
        else
        {
            PS_MEM_CPY((TAF_CHAR *)pgucAtSndCodeAddr + usLength,pEvent->PBEvent.PBSearchCnf.PBRecord.AlphaTag,pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength);
            usLength += pEvent->PBEvent.PBSearchCnf.PBRecord.ucAlphaTagLength;
        }
    }
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"");

    if(AT_V_ENTIRE_TYPE == gucAtVType)
    {
        PS_MEM_CPY((TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)gaucAtCrLf,2);/*Codeǰ���\r\n*/
        At_SendResultData(ucIndex,pgucAtSndCrLfAddr,usLength+2);
    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

        At_SendResultData(ucIndex,pgucAtSndCodeAddr,usLength);
    }
}



TAF_UINT32 At_PbReadCnfProc(VOS_UINT8 ucIndex,SI_PB_EVENT_INFO_STRU  *pEvent)
{
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usPBReadPrintLength;
    ulResult                            = AT_FAILURE;
    usPBReadPrintLength                 = 0;

    if (SI_PB_CONTENT_INVALID == pEvent->PBEvent.PBReadCnf.PBRecord.ValidFlag)/*��ǰ��������Ч*/
    {
        return AT_SUCCESS;              /*���ز�����*/
    }
    else
    {
        if (TAF_FALSE == gulPBPrintTag)
        {
             usPBReadPrintLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)pgucAtSndCrLfAddr,"%s","\r\n");
        }

        gulPBPrintTag = TAF_TRUE;

        if(AT_CMD_CPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*���� ^CPBR �ķ�ʽ���д�ӡ*/
        {
            ulResult = At_PbCPBRCmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else if(AT_CMD_CPBR2_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*���� +CPBR �ķ�ʽ���д�ӡ*/
        {
            ulResult = At_PbCPBR2CmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else if(AT_CMD_SCPBR_SET == gastAtClientTab[ucIndex].CmdCurrentOpt) /*���� ^SCPBR �ķ�ʽ���д�ӡ*/
        {
            ulResult = At_PbSCPBRCmdPrint(ucIndex,&usPBReadPrintLength,pEvent);
        }
        else if(AT_CMD_CNUM_READ == gastAtClientTab[ucIndex].CmdCurrentOpt) /*���� CNUM �ķ�ʽ���д�ӡ*/
        {
            ulResult = At_PbCNUMCmdPrint(ucIndex,&usPBReadPrintLength,pgucAtSndCrLfAddr,pEvent);
        }
        else
        {
            AT_ERR_LOG1("At_PbReadCnfProc: the Cmd Current Opt %d is Unknow", gastAtClientTab[ucIndex].CmdCurrentOpt);

            return AT_FAILURE;
        }
    }

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if(AT_SUCCESS == ulResult)
    {
        usPBReadPrintLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCrLfAddr,
                                                (TAF_CHAR *)pgucAtSndCrLfAddr + usPBReadPrintLength,
                                                "%s","\r\n");
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    At_SendResultData(ucIndex,pgucAtSndCrLfAddr,usPBReadPrintLength);

    PS_MEM_CPY((TAF_CHAR *)pgucAtSndCrLfAddr,(TAF_CHAR *)gaucAtCrLf,2);/*AT���Buffer��ǰ�����ֽڻָ�Ϊ\r\n*/

    return ulResult;
}



TAF_VOID At_PbCallBackFunc(SI_PB_EVENT_INFO_STRU  *pEvent)
{
    TAF_UINT32 ulSendMsg = 0;
    TAF_UINT8  ucIndex;

    if(TAF_NULL_PTR == pEvent)      /*��������*/
    {
        AT_WARN_LOG("At_PbCallBackFunc pEvent NULL");

        return;
    }

    if(AT_FAILURE == At_ClientIdToUserId(pEvent->ClientId, &ucIndex))/*�ظ��Ŀͻ������ݴ���*/
    {
        //At_SendReportMsg(MN_CALLBACK_PHONE_BOOK, (TAF_UINT8*)pEvent, sizeof(SI_PB_EVENT_INFO_STRU));

        return;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_PbMsgProc : AT_BROADCAST_INDEX.");
        return;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    if(AT_CMD_CNUM == gastAtClientTab[ucIndex].CmdIndex)
    {
        pEvent->PBError = ((TAF_ERR_PB_NOT_FOUND == pEvent->PBError)?TAF_ERR_NO_ERROR:pEvent->PBError);
    }

    if(TAF_ERR_NO_ERROR != pEvent->PBError)/*����������Ϣ����*/
    {
        ulSendMsg = SI_TRUE;
    }
    else if(((pEvent->PBEventType == SI_PB_EVENT_READ_CNF)||(pEvent->PBEventType == SI_PB_EVENT_SREAD_CNF))
        && (pEvent->PBLastTag != SI_PB_LAST_TAG_TRUE))/*���ڶ�ȡ������Ҫ����˲���ͨ��һ���Ե���Ϣ�������ݽ��д���*/
    {
        if ( AT_SUCCESS != At_PbReadCnfProc(ucIndex,pEvent) )
        {
            AT_WARN_LOG("At_PbCallBackFunc:At_PbReadCnfProc Error");
        }

        ulSendMsg = SI_FALSE;
    }
    else if(pEvent->PBEventType == SI_PB_EVENT_SEARCH_CNF)
    {
        if( SI_PB_LAST_TAG_TRUE == pEvent->PBLastTag )
        {
            ulSendMsg = SI_TRUE;
        }
        else
        {
            At_PbSearchCnfProc(ucIndex,pEvent);
            return;
        }
    }
    else        /*�����Ļظ�����ͨ����Ϣ����һ���Է��ʹ���*/
    {
        ulSendMsg = SI_TRUE;
    }

    if (SI_TRUE == ulSendMsg)
    {
        At_SendReportMsg(MN_CALLBACK_PHONE_BOOK,(TAF_UINT8*)pEvent,sizeof(SI_PB_EVENT_INFO_STRU));
    }

    return;
}

/* Added by L60609 for AT Project��2011-10-04,  End*/


VOS_VOID At_RcvVcMsgSetGroundCnfProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc : AT_BROADCAST_INDEX.");
        return;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CBG_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgSetGroundCnfProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    if (VOS_OK == pstData->aucContent[0])
    {
        ulRet = AT_OK;
    }
    else
    {
        ulRet = AT_ERROR;
    }

    /* ������ý�� */
    gstAtSendData.usBufLen = 0;

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}


VOS_VOID At_RcvVcMsgQryGroundRspProc(
    MN_AT_IND_EVT_STRU                 *pstData
)
{
    APP_VC_QRY_GROUNG_RSP_STRU         *pstQryRslt;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstData->clientId, &ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc:WARNING:AT INDEX NOT FOUND!");
        return;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc : AT_BROADCAST_INDEX.");
        return;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CBG_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("At_RcvVcMsgQryGroundRspProc:WARNING:AT ARE WAITING ANOTHER CMD!");
        return;
    }

    /* ��ʼ�� */
    pstQryRslt = (APP_VC_QRY_GROUNG_RSP_STRU *)pstData->aucContent;

    if (VOS_OK == pstQryRslt->ucQryRslt)
    {
        /* �����ѯ��� */
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "^CBG:%d",
                                                        pstQryRslt->enGround);
        ulRet = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulRet = AT_ERROR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRet);

    return;
}



VOS_VOID At_ProcMsgFromVc(MN_AT_IND_EVT_STRU *pMsg)
{
    switch(pMsg->usMsgName)
    {
        case APP_VC_MSG_CNF_QRY_MODE:
            At_RcvVcMsgQryModeCnfProc(pMsg);
            break;

        case APP_VC_MSG_CNF_SET_PORT:
            At_RcvVcMsgSetPortCnfProc(pMsg);
            break;

        case APP_VC_MSG_CNF_QRY_PORT:
            At_RcvVcMsgQryPortCnfProc(pMsg);
            break;

        case APP_VC_MSG_SET_FOREGROUND_CNF:
        case APP_VC_MSG_SET_BACKGROUND_CNF:
            /*AT ���� VC �ϱ���ǰ̨ģʽ����̨ģʽCNF MSG*/
            At_RcvVcMsgSetGroundCnfProc(pMsg);
            break;

        case APP_VC_MSG_FOREGROUND_RSP:
            /*AT ����VC �ϱ��Ĳ�ѯǰ̨ģʽ�ظ���Ϣ*/
            At_RcvVcMsgQryGroundRspProc(pMsg);
            break;

        default:
            return;
    }
    return;
}


VOS_UINT32 At_RcvRnicMsg(MsgBlock *pstMsg)
{
    VOS_UINT32                          ulRst;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader                        = (MSG_HEADER_STRU *)pstMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        /* ����RNIC�����������ϱ� */
        case ID_RNIC_AT_DSFLOW_RSP:

            ulRst = AT_RcvRnicDsflowRsp(pstMsg);
            break;

        /* ����RNIC�����Ĳ���ģʽ��ѯ�ظ� */
        case ID_RNIC_AT_DIAL_MODE_CNF:

            ulRst = AT_RcvRnicDialModeCnf(pstMsg);
            break;

        default:
            ulRst = VOS_OK;
            break;
    }
    return ulRst;
}


VOS_VOID At_ProcMsgFromCc(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU *)pMsg;

    switch(pstMsgHeader->ulMsgName)
    {
        case AT_CC_MSG_STATE_QRY_CNF:
            At_RcvAtCcMsgStateQryCnfProc(pMsg);
            break;

        default:
            break;
    }
    return;
}


VOS_VOID AT_RcvNdisMsg(MsgBlock* pMsg)
{
    VOS_UINT32                          ulResult;
    AT_FW_MSG_STRU                     *pstAtFwMsg;
    AT_FW_CMD_BINARY_MSG_STRU          *pstBinaryInfo;
    AT_NDIS_MSG_STRU                   *pstNdisMsg;

    pstAtFwMsg      = (AT_FW_MSG_STRU*)(pMsg->aucValue);
    pstBinaryInfo   = (AT_FW_CMD_BINARY_MSG_STRU*)(pstAtFwMsg->pMsgParam);
    pstNdisMsg      = (AT_NDIS_MSG_STRU*)pstBinaryInfo;

    switch (pstNdisMsg->ulMsgId)
    {
        case ID_AT_NDIS_PDNINFO_CFG_CNF:
            ulResult = AT_RcvNdisPdnInfoCfgCnf(&pstNdisMsg->unMsg.stNdisPdnInfoCfgCnf);
            break;

        case ID_AT_NDIS_PDNINFO_REL_CNF:
            ulResult = AT_RcvNdisPdnInfoRelCnf(&pstNdisMsg->unMsg.stNdisPdnInfoRelCnf);
            break;

        default:
            AT_WARN_LOG("AT_RcvNdisMsg: Unexpected MSG is received.");
            ulResult = VOS_ERR;
            break;
    }

    if ( VOS_OK != ulResult )
    {
        AT_ERR_LOG1("AT_RcvNdisMsg: Process message failed. <MsgId>",
                    (VOS_INT32)pstNdisMsg->ulMsgId);
    }

    return;
}

/* Added by h44270 for V7R1 phase III, 2011-10-18, begin */

VOS_UINT32    AT_ProcRabmSetFastDormParaCnf(
    RABM_AT_SET_FASTDORM_PARA_CNF_STRU     *pstMsg
)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulRslt;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_ProcRabmSetFastDormParaCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ������ý�� */
    gstAtSendData.usBufLen = 0;
    ulRslt = AT_ERROR;
    if (AT_RABM_PARA_SET_RSLT_SUCC == pstMsg->enRslt)
    {
        ulRslt = AT_OK;
    }

    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}


VOS_UINT32    AT_ProcRabmQryFastDormParaCnf(
    RABM_AT_QRY_FASTDORM_PARA_CNF_STRU     *pstMsg
)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    ulResult = AT_ERROR;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("At_RcvAtCcMsgStateQryCnfProc:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* Added by l60609 for B070 Project, 2012/03/20, begin */
    if (VOS_TRUE == pstMsg->ucRslt)
    {
        /* �����ѯ��� */
        usLength = 0;
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"^FASTDORM:%d",pstMsg->stFastDormPara.enFastDormOperationType);

        if (AT_RABM_FASTDORM_STOP_FD_ASCR != pstMsg->stFastDormPara.enFastDormOperationType)
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",pstMsg->stFastDormPara.ulTimeLen);
        }

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",gaucAtCrLf);

        ulResult = AT_OK;
        gstAtSendData.usBufLen = usLength;
    }
    /* Added by l60609 for B070 Project, 2012/03/20, end */

    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}


VOS_UINT32 AT_ProcRabmReleaseRrcCnf(RABM_AT_RELEASE_RRC_CNF_STRU *pstMsg)
{
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulRslt;

    ulRslt = AT_ERROR;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMsg->usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_ProcRabmReleaseRrcCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ������ý�� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK == pstMsg->ulRslt)
    {
        ulRslt = AT_OK;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    At_FormatResultData(ucIndex, ulRslt);

    return VOS_OK;
}


TAF_VOID AT_RabmMsgProc(
    MSG_HEADER_STRU                    *pstMsg
)
{
    switch(pstMsg->ulMsgName)
    {
        case ID_RABM_AT_SET_FASTDORM_PARA_CNF:
            AT_ProcRabmSetFastDormParaCnf((RABM_AT_SET_FASTDORM_PARA_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_QRY_FASTDORM_PARA_CNF:
            AT_ProcRabmQryFastDormParaCnf((RABM_AT_QRY_FASTDORM_PARA_CNF_STRU*)pstMsg);
            break;

        case ID_RABM_AT_SET_RELEASE_RRC_CNF:
            AT_ProcRabmReleaseRrcCnf((RABM_AT_RELEASE_RRC_CNF_STRU*)pstMsg);
            break;
        default:
            AT_WARN_LOG("At_RabmMsgProc:WARNING:Wrong Msg!");
            break;
    }
}

/* Added by h44270 for V7R1 phase III, 2011-10-18, end */


TAF_VOID At_MsgProc(MsgBlock* pMsg)
{
    /* ��ʱ���� */
    if ( VOS_PID_TIMER == pMsg->ulSenderPid )
    {
        At_TimeOutProc((REL_TIMER_MSG*)pMsg);
        return;
    }

    /* ��Ϣ�ķַ����� */
    switch ( pMsg->ulSenderPid )
    {
        case WUEPS_PID_AT:
            At_CmdMsgDistr((AT_MSG_STRU*)pMsg);
            return;

        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
            At_EventMsgProc((MN_AT_IND_EVT_STRU *)pMsg);
            return;

        case PS_PID_APP_PPP:
            At_PppMsgProc((MSG_HEADER_STRU *)pMsg);
            return;

        case PS_PID_APP_NDIS:
            AT_RcvNdisMsg(pMsg);
            return;

        case DSP_PID_WPHY:
            At_HPAMsgProc(pMsg);
            return;

        case I0_DSP_PID_GPHY:
        case I1_DSP_PID_GPHY:
            At_GHPAMsgProc(pMsg);
            return;

        case I0_WUEPS_PID_MMA:
        case I1_WUEPS_PID_MMA:
            At_MmaMsgProc((MSG_HEADER_STRU *)pMsg);
            return;

        case I0_WUEPS_PID_DRV_AGENT:
        case I1_WUEPS_PID_DRV_AGENT:
            At_ProcMsgFromDrvAgent((DRV_AGENT_MSG_STRU *)pMsg);
            return;

        case I0_WUEPS_PID_VC:
        case I1_WUEPS_PID_VC:
            At_ProcMsgFromVc((MN_AT_IND_EVT_STRU *)pMsg);
            return;

        case ACPU_PID_RNIC:
            At_RcvRnicMsg(pMsg);
            return;

        case I0_WUEPS_PID_CC:
        case I1_WUEPS_PID_CC:
            At_ProcMsgFromCc(pMsg);
            return;
        #if (FEATURE_ON == FEATURE_LTE)
        case MSP_L4_L4A_PID:
            at_L4aCnfProc(pMsg);
            return;

        case MSP_SYS_FTM_PID:
        case MSP_SYS_SYM_PID:
            At_FtmEventMsgProc(pMsg);
            return;
        #endif

        case I0_MAPS_STK_PID:
        case I1_MAPS_STK_PID:
            At_STKMsgProc(pMsg);
            return;

        case I0_MAPS_PB_PID:
        case I1_MAPS_PB_PID:
            At_PbMsgProc(pMsg);
            return;

        case I0_MAPS_PIH_PID:
        case I1_MAPS_PIH_PID:
            At_PIHMsgProc(pMsg);
            return;
        case I0_WUEPS_PID_RABM:
        case I1_WUEPS_PID_RABM:
            AT_RabmMsgProc((MSG_HEADER_STRU *)pMsg);
            return;
        case WUEPS_PID_SPY:
            AT_SpyMsgProc((MSG_HEADER_STRU *)pMsg);
            return;

        case I0_UEPS_PID_MTA:
        case I1_UEPS_PID_MTA:
            At_ProcMtaMsg((AT_MTA_MSG_STRU *)pMsg);
            return;
#if (FEATURE_ON == FEATURE_IMS)
        case PS_PID_IMSA:
            AT_ProcImsaMsg((AT_IMSA_MSG_STRU *)pMsg);
            return;
#endif

        default:
            AT_LOG1("At_MsgProc other PID msg",pMsg->ulSenderPid);
            return;
    }
}

/* Added by f62575 for AT Project, 2011/10/22, begin */

VOS_VOID AT_EventReport(
    VOS_UINT32                          ulPid,
    NAS_OM_EVENT_ID_ENUM_UINT16         enEventId,
    VOS_VOID                           *pPara,
    VOS_UINT32                          ulLen
)
{
    PS_OM_EVENT_IND_STRU               *pstEvent;
    VOS_VOID                           *pData;

    pData = pPara;
    if ((VOS_NULL_PTR == pData) && (ulLen > 0))
    {
        /* �����ӡ */
        AT_WARN_LOG("AT_EventReport:pPara is NULL.");
        return;
    }

    if (4 < ulLen)
    {
        pstEvent = (PS_OM_EVENT_IND_STRU*)PS_MEM_ALLOC(ulPid,
                              ((sizeof(PS_OM_EVENT_IND_STRU)-4)+ulLen));
    }
    else
    {
        pstEvent = (PS_OM_EVENT_IND_STRU*)PS_MEM_ALLOC(ulPid,
                              sizeof(PS_OM_EVENT_IND_STRU));
    }
    if (VOS_NULL_PTR == pstEvent)
    {
        PS_LOG(ulPid, VOS_NULL, PS_PRINT_WARNING, "AT_EventReport:Alloc mem fail.");
        return;
    }
    PS_MEM_SET(pstEvent->aucData, 0x0, ((ulLen>4)?ulLen:4));

    /* ulLength ָ��usEventId��ʼ����β�ĳ��� */
    pstEvent->ulLength        = 8 + ulLen;
    pstEvent->usEventId       = enEventId;
    pstEvent->usReserved      = 0x0;
    pstEvent->ulModuleId      = ulPid;
    /* ulLen>0ʱ��ͨ����������pPara������Ϊ��ָ�� */
    if (VOS_NULL_PTR != pData)
    {
        PS_MEM_CPY(pstEvent->aucData, pData, pstEvent->ulLength-8);
    }

#ifdef DMT
    if (VOS_OK != OM_Event(pstEvent))
#else
    if (VOS_OK != OM_AcpuEvent(pstEvent))
#endif
    {
        AT_WARN_LOG("AT_EventReport:OM_AcpuEvent Fail.");
    }

    PS_MEM_FREE(ulPid, pstEvent);

    return;
}

/* Added by f62575 for AT Project, 2011/10/22, end */


VOS_UINT32 AT_RcvDrvAgentSetAdcRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_ADC_SET_CNF_STRU                *pstAdcCnf;
    VOS_UINT8                                  ucIndex;
    VOS_UINT32                                 ulResult;

    /* ��ʼ����Ϣ */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstAdcCnf       = (DRV_AGENT_ADC_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstAdcCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetAdcRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetAdcRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_ADC_SET */
    if (AT_CMD_ADC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /*��������ֵ�Ƿ�ɹ� */
    if (VOS_TRUE != pstAdcCnf->bFail)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    /* ����AT_FormATResultDATa���������� */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvDrvAgentQryTbatRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_TBAT_QRY_CNF_STRU        *stTbatTypeCnf;
    VOS_UINT8                           ucIndex;

    /* ��ʼ����Ϣ */
    pRcvMsg                = (DRV_AGENT_MSG_STRU *)pMsg;
    stTbatTypeCnf          = (DRV_AGENT_TBAT_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(stTbatTypeCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /*�Զ�Ӧ��������±�����������*/
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentQryTbatRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_TBAT_QRY */
    if (AT_CMD_TBAT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stTbatTypeCnf->ulTbatType);

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, AT_OK);
    return VOS_OK;

}

/* Added by f62575 for B050 Project, 2012-2-3, Begin   */

VOS_UINT32 AT_RcvDrvAgentSetSecuBootRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_SECUBOOT_SET_CNF_STRU    *pstSecuBootCnf;
    VOS_UINT8                           ucIndex;

    /* ��ʼ����Ϣ */
    pRcvMsg                 = (DRV_AGENT_MSG_STRU *)pMsg;
    pstSecuBootCnf          = (DRV_AGENT_SECUBOOT_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstSecuBootCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetSecuBootRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /*�Զ�Ӧ��������±�����������*/
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetSecuBootRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SECUBOOT_SET */
    if (AT_CMD_SECUBOOT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ����At_FormatResultData���������� */
    if (VOS_TRUE == pstSecuBootCnf->bFail)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;

}


VOS_UINT32 AT_RcvSimLockQryRsp(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulRet;
    AT_MMA_SIMLOCK_STATUS_STRU         *pstEvent;

    pstEvent = (AT_MMA_SIMLOCK_STATUS_STRU *)pMsg;

    if (AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvSimLockQryRsp: AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SIMLOCKSTATUS_READ��AT_CMD_CSDFLT_READ */
    if ((AT_CMD_SIMLOCKSTATUS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
#if((FEATURE_ON == MBB_WPG_COMMON) && (FEATURE_ON == MBB_FEATURE_VDF_SIMLOCKEX))
     && (AT_CMD_CSDFLT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
     && (AT_CMD_SIMLOCKEXSTATUS_READ != gastAtClientTab[ucIndex].CmdCurrentOpt))
#else
     && (AT_CMD_CSDFLT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt))
#endif
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    if (AT_CMD_SIMLOCKSTATUS_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%d",
                                                    #if (FEATURE_ON == MBB_COMMON)
                                                        "^SIMLOCK",
                                                    #else
                                                        "SIMLOCK",
                                                    #endif
                                                        pstEvent->bSimlockEnableFlg);
        ulRet                  = AT_OK;

    }
#if ( FEATURE_ON == MBB_WPG_COMMON )
#if ( FEATURE_ON == MBB_FEATURE_VDF_SIMLOCKEX )
    /*����AT^SIMLOCKEX���ϱ�*/
    else if(AT_CMD_SIMLOCKEXSTATUS_READ == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%d",
                                                        "^SIMLOCKEX",
                                                        pstEvent->bSimlockEnableFlg);
        ulRet                  = AT_OK;
    }
#endif
#endif
    else
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = 0;
        ulRet                  = AT_OutputCsdfltDefault(ucIndex, pstEvent->bSimlockEnableFlg);
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulRet);

    return VOS_OK;
}

/* Added by f62575 for B050 Project, 2012-2-3, end   */

#if (VOS_WIN32 == VOS_OS_VER)


VOS_UINT32 WuepsATFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRslt = VOS_OK;

    switch( ip )
    {
        case   VOS_IP_LOAD_CONFIG:
        /* Added by L60609 for AT Project��2011-10-20,  Begin*/
        #if (VOS_WIN32 == VOS_OS_VER)
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_AT,
                                           (Init_Fun_Type)At_PidInit,
                                           (Msg_Fun_Type)At_MsgProc);

            if (VOS_OK != ulRslt)
            {
                return VOS_ERR;
            }
        #endif
            /* Added by L60609 for AT Project��2011-10-20,  Begin*/

            ulRslt = VOS_RegisterMsgTaskPrio(WUEPS_FID_AT, VOS_PRIORITY_P6);

            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;
        default:
            break;
    }

    return VOS_OK;
}
#endif

#if (FEATURE_ON == FEATURE_SECURITY_SHELL)

VOS_UINT32 AT_RcvDrvAgentSetSpwordRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_SPWORD_SET_CNF_STRU             *pstSpwordSetCnf;
    VOS_UINT8                                  ucIndex;

    /* ��ʼ����Ϣ */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstSpwordSetCnf = (DRV_AGENT_SPWORD_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstSpwordSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("pstSpwordSetCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("pstSpwordSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SPWORD_SET */
    if (AT_CMD_SPWORD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ����У��ͨ�������������Ҫ���� */
    if (VOS_OK == pstSpwordSetCnf->ulResult)
    {
        g_stSpWordCtx.ucShellPwdCheckFlag = VOS_TRUE;
        g_stSpWordCtx.ucErrTimes          = 0;

        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_OK);
    }
    /* ����У��ʧ�ܣ����������1 */
    else
    {
        g_stSpWordCtx.ucErrTimes++;

        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}

#endif

VOS_UINT32 AT_RcvMmaCipherInfoQueryCnf(VOS_VOID *pMsg)
{
    MN_MMA_CIPHER_QRY_CNF_STRU         *pstCipherQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pstCipherQryCnf     = (MN_MMA_CIPHER_QRY_CNF_STRU *)pMsg;
    ulResult            = AT_OK;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCipherQryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCipherInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCipherInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_CIPERQRY_READ */
    if (AT_CMD_CIPERQRY_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CIPERQRY��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstCipherQryCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                                   "%s:%d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   pstCipherQryCnf->ucCipherInfo);
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}


VOS_UINT32 AT_RcvMmaLocInfoQueryCnf(VOS_VOID *pMsg)
{
    MN_MMA_LOCATION_INFO_CNF_STRU      *pstLocInfoCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pstLocInfoCnf       = (MN_MMA_LOCATION_INFO_CNF_STRU *)pMsg;
    usLength            = 0;
    ulResult            = AT_OK;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstLocInfoCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaLocInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaLocInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_LOCINFO_READ */
    if (AT_CMD_LOCINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CIPERQRY��ѯ����� */
    if (VOS_OK != pstLocInfoCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        /* �ϱ�MCC��MNC */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X%X%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f) ,
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f00) >> 8,
                                          (VOS_INT32)(pstLocInfoCnf->ulMcc & 0x0f0000) >> 16);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f) ,
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f00) >> 8);

        /* MNC���һλ������F����MNCΪ��λ������Ϊ��λ */
        if (0x0f != ((pstLocInfoCnf->ulMnc & 0x0f0000) >> 16))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%X",
                                          (VOS_INT32)(pstLocInfoCnf->ulMnc & 0x0f0000) >> 16);
        }

        /* Lac */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->usLac);

        /* Rac */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->ucRac);

        /* Cell ID */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          ",0x%X",
                                          pstLocInfoCnf->ulCellid);

        gstAtSendData.usBufLen = usLength;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentNvBackupStatQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU    *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NVBACKUPSTAT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvBackupStatQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNvBackupStatQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_NVBACKUPSTAT_READ */
    if ( AT_CMD_NVBACKUPSTAT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        if ( NV_OK == pstEvent->ulNvBackupStat )
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: %d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               VOS_TRUE);
        }
        else
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: %d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               VOS_FALSE);
        }

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentNandBadBlockQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NANDBBC_QRY_CNF_STRU         *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;
    VOS_UINT32                              uli;
    VOS_UINT32                              ulMaxBBNum;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NANDBBC_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;
    uli             = 0;
    ulMaxBBNum      = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandBadBlockQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandBadBlockQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_NANDBBC_READ */
    if ( AT_CMD_NANDBBC_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->ulBadBlockNum);

        ulMaxBBNum = (pstEvent->ulBadBlockNum > DRV_AGENT_NAND_BADBLOCK_MAX_NUM) ? DRV_AGENT_NAND_BADBLOCK_MAX_NUM : pstEvent->ulBadBlockNum;
        for (uli = 0; uli < ulMaxBBNum; uli++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s%s: %d",
                                               gaucAtCrLf,
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstEvent->aulBadBlockIndex[uli]);
        }

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentNandDevInfoQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_NANDVER_QRY_CNF_STRU         *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_NANDVER_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandDevInfoQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentNandDevInfoQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_NANDVER_READ */
    if ( AT_CMD_NANDVER_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        /* �����ѯ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,\"%s\",%d,\"%s\"",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->stNandDevInfo.ulMufId,
                                           pstEvent->stNandDevInfo.aucMufName,
                                           pstEvent->stNandDevInfo.ulDevId,
                                           pstEvent->stNandDevInfo.aucDevSpec);

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentChipTempQryRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_CHIPTEMP_QRY_CNF_STRU    *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_CHIPTEMP_QRY_CNF_STRU *)pRcvMsg->aucContent;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentChipTempQryRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentChipTempQryRsp: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_CHIPTEMP_READ */
    if ( AT_CMD_CHIPTEMP_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_NO_ERROR == pstEvent->ulResult )
    {
        /* �����ѯ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,%d,%d,%d,%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstEvent->lGpaTemp,
                                           pstEvent->lWpaTemp,
                                           pstEvent->lLpaTemp,
                                           pstEvent->lSimTemp,
                                           pstEvent->lBatTemp);

        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}




#ifndef __PS_WIN32_RECUR__


VOS_UINT32 AT_RcvMmaOmMaintainInfoInd(
    VOS_VOID                           *pstMsg
)
{
    ATMMA_OM_MAINTAIN_INFO_IND_STRU    *pstOmMaintainInfo;

    pstOmMaintainInfo = (ATMMA_OM_MAINTAIN_INFO_IND_STRU*)pstMsg;

    if ( (VOS_TRUE == pstOmMaintainInfo->ucOmConnectFlg)
      && (VOS_TRUE == pstOmMaintainInfo->ucOmPcRecurEnableFlg) )
    {
        AT_MNTN_TraceContextData();
        AT_MNTN_TraceClientData();
    }

    return VOS_OK;
}
#endif


VOS_UINT32 AT_RcvDrvAgentAntStateIndRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    VOS_UINT16                          usLength = 0;
    DRV_AGENT_ANT_STATE_IND_STRU       *pstAntState = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    gstAtSendData.usBufLen  = 0;
    pRcvMsg                 = (DRV_AGENT_MSG_STRU *)pMsg;
    pstAntState             = (DRV_AGENT_ANT_STATE_IND_STRU *)pRcvMsg->aucContent;
    ucIndex                 = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstAntState->stAtAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntStateIndRsp: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       "%s:%d%s",
                                       "^ANTSTATE",
                                       pstAntState->usAntState,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);


    return VOS_OK;
}

VOS_UINT32 AT_RcvDrvAgentSetMaxLockTmsRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU       *pstMaxlockTmsSetCnf;
    VOS_UINT8                                  ucIndex;

    /* ��ʼ����Ϣ */
    pRcvMsg             = (DRV_AGENT_MSG_STRU *)pMsg;
    pstMaxlockTmsSetCnf = (DRV_AGENT_MAX_LOCK_TMS_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMaxlockTmsSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetMaxLockTmsRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetMaxLockTmsRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_MAXLCKTMS_SET */
    if (AT_CMD_MAXLCKTMS_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^MAXLCKTMS��������� */
    if (VOS_OK != pstMaxlockTmsSetCnf->ulResult)
    {
        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_DEVICE_OTHER_ERROR);
    }
    else
    {
        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentSetApSimstRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                        *pRcvMsg;
    DRV_AGENT_AP_SIMST_SET_CNF_STRU           *pstApSimStSetCnf;
    VOS_UINT8                                  ucIndex;

    /* ��ʼ����Ϣ */
    pRcvMsg             = (DRV_AGENT_MSG_STRU *)pMsg;
    pstApSimStSetCnf    = (DRV_AGENT_AP_SIMST_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstApSimStSetCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetApSimstRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSetApSimstRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_APSIMST_SET */
    if (AT_CMD_APSIMST_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^APSIMST��������� */
    if (VOS_OK != pstApSimStSetCnf->ulResult)
    {
        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        /* ����At_FormatResultData���������� */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}



VOS_UINT32 AT_RcvDrvAgentHukSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_HUK_SET_CNF_STRU             *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    /* ��ʼ�� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_HUK_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    ulResult        = VOS_NULL;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentHukSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentHukSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_HUK_SET */
    if (AT_CMD_HUK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if (DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult)
    {
        /* ������ý�� */
        ulResult    = AT_OK;
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentFacAuthPubkeySetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU   *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    /* ��ʼ�� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_FACAUTHPUBKEY_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    ulResult        = VOS_NULL;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentFacAuthPubkeySetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentFacAuthPubkeySetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_FACAUTHPUBKEY_SET */
    if ( AT_CMD_FACAUTHPUBKEY_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentIdentifyStartSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU   *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;
    VOS_UINT16                              usLength;
    VOS_UINT32                              i;

    /* ��ʼ�� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_IDENTIFYSTART_SET_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyStartSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyStartSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_IDENTIFYSTART_SET */
    if ( AT_CMD_IDENTIFYSTART_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s: ",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucRsaText[i]);
        }
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentIdentifyEndSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                     *pRcvMsg;
    DRV_AGENT_IDENTIFYEND_SET_CNF_STRU     *pstEvent;
    VOS_UINT8                               ucIndex;
    VOS_UINT32                              ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_IDENTIFYEND_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyEndSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentIdentifyEndSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_IDENTIFYEND_SET */
    if ( AT_CMD_IDENTIFYEND_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentSimlockDataWriteSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU    *pstEvent;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_SIMLOCKDATAWRITE_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataWriteSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataWriteSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SIMLOCKDATAWRITE_SET */
    if ( AT_CMD_SIMLOCKDATAWRITE_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_CHAR AT_Num2AsciiNum(VOS_UINT8 ucNum)
{
    if (9 >= ucNum)
    {
        return (VOS_CHAR)('0' + ucNum);
    }
    else if (0x0F >= ucNum)
    {
        return (VOS_CHAR)('A' + (ucNum - 0x0A));
    }
    else
    {
        return '*';
    }
}


VOS_UINT32 AT_CheckSimlockCodeLast2Char(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_CHAR                                       *pcStrLast2Char
)
{
    VOS_UINT8                           i           = 0;

    /* ��������λ����Ч��, NET������ */
    if (DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK < enCategory)
    {
        for (i = 0; i < 2; i++)
        {
            /* NETSUB֧�ַ�Χ: 0x00~0x99 */
            if ( ('0' <= pcStrLast2Char[i]) && ('9' >= pcStrLast2Char[i]) )
            {
                continue;
            }
            /* SP֧�ַ�Χ: 0x00~0xFF */
            else if ( (DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER == enCategory)
                   && ('A' <= pcStrLast2Char[i]) && ('F' >= pcStrLast2Char[i]) )
            {
                continue;
            }
            else
            {
                return VOS_ERR;
            }
        }
    }

    return VOS_OK;

}



VOS_UINT32 AT_CheckSimlockCodeStr(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_CHAR                                       *pcStrCode
)
{
    VOS_UINT8                           i           = 0;
    VOS_UINT8                           j           = 0;
    VOS_UINT8                           ucLen;              /* �������볤�� */
    VOS_CHAR                           *pcTmpStr;

    pcTmpStr    = pcStrCode;

    switch(enCategory)
    {
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
            ucLen = AT_PERSONALIZATION_NET_CODE_LEN;
            break;
        default:
            ucLen = AT_PERSONALIZATION_CODE_LEN;
            break;
    }

    /* ���PLMN�Ϸ��Լ���λ�� */
    for (i = 0; i < AT_PERSONALIZATION_NET_CODE_LEN; i++)
    {
        if ( ('0' <= pcTmpStr[i]) && ('9' >= pcTmpStr[i]) )
        {
            continue;
        }
        else if ( ((AT_PERSONALIZATION_NET_CODE_LEN - 1) == i)
               && ('F' == pcTmpStr[i]) )
        {
            for (j = i + 1; j < ucLen; j++)
            {
                pcTmpStr[j - 1] = pcTmpStr[j];
            }
            ucLen = ucLen - 1;
            break;
        }
        else
        {
            return VOS_ERR;
        }
    }

    pcTmpStr[ucLen] = 0;

    /* ��������������������λ�ĺϷ��� */
    if (VOS_OK != AT_CheckSimlockCodeLast2Char(enCategory, &pcTmpStr[ucLen - 2]))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 AT_SimlockCodeBcd2Str(
    DRV_AGENT_PERSONALIZATION_CATEGORY_ENUM_UINT8   enCategory,
    VOS_UINT8                                      *pucBcdNum,
    VOS_CHAR                                       *pcStrNum
)
{
    VOS_UINT8                           i               = 0;
    VOS_UINT8                           ucDecodeLen;
    VOS_UINT8                           ucFirstNum;
    VOS_UINT8                           ucSecondNum;
    VOS_CHAR                           *pcStrTmp        = pcStrNum;
    VOS_CHAR                            cTmpChar;

    switch(enCategory)
    {
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
            ucDecodeLen = AT_PERSONALIZATION_NET_CODE_BCD_LEN;
            break;
        case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
            ucDecodeLen = AT_PERSONALIZATION_SUBNET_CODE_BCD_LEN;
            break;
        case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
            ucDecodeLen = AT_PERSONALIZATION_SP_CODE_BCD_LEN;
            break;
        default:
            return VOS_ERR;
    }

    /* ����������������иߵ��ֽ�ת�� */
    for (i = 0; i < ucDecodeLen; i++)
    {
        /* �ֱ�ȡ���ߵ��ֽ� */
        ucFirstNum  = (VOS_UINT8)((*(pucBcdNum + i)) & 0x0F);
        ucSecondNum = (VOS_UINT8)(((*(pucBcdNum + i)) >> 4) & 0x0F);

        *pcStrTmp++ = AT_Num2AsciiNum(ucFirstNum);
        *pcStrTmp++ = AT_Num2AsciiNum(ucSecondNum);
    }

    /* ������λ������Ƶ�����λ(����߶Խ�) */
    pcStrTmp        = &pcStrNum[AT_PERSONALIZATION_CODE_FOURTH_CHAR_INDEX];
    cTmpChar        = pcStrTmp[0];
    pcStrTmp[0]     = pcStrTmp[1];
    pcStrTmp[1]     = pcStrTmp[2];
    pcStrTmp[2]     = cTmpChar;

    /* �Ըߵ��ֽ�ת�������������������кϷ��Լ�� */
    if (VOS_OK != AT_CheckSimlockCodeStr(enCategory, pcStrNum))
    {
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 AT_PhoneSimlockInfoPrint(
    DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU    *pstPhoneSimlockInfo,
    VOS_UINT8                                   ucIndex,
    VOS_UINT16                                 *pusLength
)
{
    VOS_UINT16                                  usLength        = *pusLength;
    VOS_UINT8                                   ucCatIndex      = 0;
    VOS_UINT8                                   ucGroupIndex    = 0;
    VOS_CHAR                                    acCodeBegin[AT_PERSONALIZATION_CODE_LEN + 1];
    VOS_CHAR                                    acCodeEnd[AT_PERSONALIZATION_CODE_LEN + 1];
    VOS_UINT32                                  ucCodeBeginRslt;
    VOS_UINT32                                  ucCodeEndRslt;

    PS_MEM_SET(acCodeBegin,    0x00,   (AT_PERSONALIZATION_CODE_LEN + 1));
    PS_MEM_SET(acCodeEnd,      0x00,   (AT_PERSONALIZATION_CODE_LEN + 1));
    ucCodeBeginRslt = VOS_NULL;
    ucCodeEndRslt   = VOS_NULL;

    for (ucCatIndex = 0; ucCatIndex < DRV_AGENT_SUPPORT_CATEGORY_NUM; ucCatIndex++)
    {
        if (0 != ucCatIndex)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);
        }

        /* ^PHONESIMLOCKINFO: <cat>,<indicator> [,(<code_begin>,<code_end>)...] */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        switch (pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory)
        {
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NET");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NETSUB");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "SP");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_CORPORATE:
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SIM_USIM:
            default:
                return VOS_ERR;
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enIndicator);
        if (DRV_AGENT_PERSONALIZATION_INDICATOR_ACTIVE == pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enIndicator)
        {
            for (ucGroupIndex = 0; ucGroupIndex < pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].ucGroupNum; ucGroupIndex++)
            {
                ucCodeBeginRslt = AT_SimlockCodeBcd2Str(pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory,
                                                        pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].astLockCode[ucGroupIndex].aucPhLockCodeBegin,
                                                        acCodeBegin);
                ucCodeEndRslt   = AT_SimlockCodeBcd2Str(pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].enCategory,
                                                        pstPhoneSimlockInfo->astCategoryInfo[ucCatIndex].astLockCode[ucGroupIndex].aucPhLockCodeEnd,
                                                        acCodeEnd);
                if ( (VOS_OK == ucCodeBeginRslt)
                  && (VOS_OK == ucCodeEndRslt) )
                {
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                       ",(%s,%s)",
                                                       acCodeBegin,
                                                       acCodeEnd);
                }
                else
                {
                    return VOS_ERR;
                }
            }
        }

    }
    *pusLength = usLength;
    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentPhoneSimlockInfoQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU    *pstEvent;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PHONESIMLOCKINFO_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhoneSimlockInfoQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhoneSimlockInfoQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PHONESIMLOCKINFO_READ */
    if ( AT_CMD_PHONESIMLOCKINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
        /* ��ӡ��� */
        if (VOS_OK != AT_PhoneSimlockInfoPrint(pstEvent, ucIndex, &usLength))
        {
            ulResult = AT_PERSONALIZATION_OTHER_ERROR;
        }
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_SimlockDataReadPrint(
    DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU      stSimlockDataRead,
    VOS_UINT8                                   ucIndex,
    VOS_UINT16                                 *pusLength
)
{
    VOS_UINT16                                  usLength        = *pusLength;
    VOS_UINT8                                   ucCatIndex      = 0;

    for (ucCatIndex = 0; ucCatIndex < DRV_AGENT_SUPPORT_CATEGORY_NUM; ucCatIndex++)
    {
        if (0 != ucCatIndex)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s",
                                               gaucAtCrLf);
        }

        /* ^SIMLOCKDATAREAD: <cat>,<indicator>,<lock_status>,<max_times>,<remain_times> */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        switch(stSimlockDataRead.astCategoryData[ucCatIndex].enCategory)
        {
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NET");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_NETWORK_SUBSET:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "NETSUB");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SERVICE_PROVIDER:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "SP");
                break;
            case DRV_AGENT_PERSONALIZATION_CATEGORY_CORPORATE:
            case DRV_AGENT_PERSONALIZATION_CATEGORY_SIM_USIM:
            default:
                return VOS_ERR;
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",%d",
                                           stSimlockDataRead.astCategoryData[ucCatIndex].enIndicator);
        if (DRV_AGENT_PERSONALIZATION_INDICATOR_ACTIVE == stSimlockDataRead.astCategoryData[ucCatIndex].enIndicator)
        {
            switch (stSimlockDataRead.astCategoryData[ucCatIndex].enStatus)
            {
            case DRV_AGENT_PERSONALIZATION_STATUS_READY:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",READY,,");
                break;
            case DRV_AGENT_PERSONALIZATION_STATUS_PIN:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",PIN,%d,%d",
                                                   stSimlockDataRead.astCategoryData[ucCatIndex].ucMaxUnlockTimes,
                                                   stSimlockDataRead.astCategoryData[ucCatIndex].ucRemainUnlockTimes);
                break;
            case DRV_AGENT_PERSONALIZATION_STATUS_PUK:
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   ",PUK,,");
                break;
            default:
                return VOS_ERR;
            }
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               ",,,");
        }

    }
    *pusLength = usLength;
    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentSimlockDataReadQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                         *pRcvMsg;
    DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU     *pstEvent;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_SIMLOCKDATAREAD_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataReadQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentSimlockDataReadQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SIMLOCKDATAREAD_READ */
    if ( AT_CMD_SIMLOCKDATAREAD_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
        /* ��ӡ��� */
        if (VOS_OK != AT_SimlockDataReadPrint(*pstEvent, ucIndex, &usLength))
        {
            ulResult = AT_PERSONALIZATION_OTHER_ERROR;
        }
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentPhonePhynumSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PHONEPHYNUM_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PHONEPHYNUM_SET */
    if ( AT_CMD_PHONEPHYNUM_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ������ý�� */
        ulResult    = AT_OK;
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentPhonePhynumQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PHONEPHYNUM_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPhonePhynumQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PHONEPHYNUM_READ */
    if ( AT_CMD_PHONEPHYNUM_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        ulResult    = AT_OK;
        /* ��ʽ�������ѯ��� */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s: IMEI,",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucImeiRsa[i]);
        }
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s%s: SN,",
                                           gaucAtCrLf,
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < DRV_AGENT_RSA_CIPHERTEXT_LEN; i++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%02X",
                                          pstEvent->aucSnRsa[i]);
        }
    }
    else
    {
        /* �쳣���, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = usLength;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32  AT_PortCtrlTmpSndMsg(VOS_VOID)
{
    OM_HSIC_CONNECT_MSG_STRU           *pstMsg;

    pstMsg = (OM_HSIC_CONNECT_MSG_STRU*)PS_ALLOC_MSG(WUEPS_PID_AT,
                                                     sizeof(OM_HSIC_CONNECT_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        return AT_ERROR;
    }

    pstMsg->ulReceiverPid  = ACPU_PID_OM;
    pstMsg->ulMsgName      = AT_OM_HSIC_PORT_CONNECT;

    if (VOS_OK !=  PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        return AT_ERROR;
    }

    return AT_OK;
}


VOS_UINT32 AT_RcvDrvAgentPortctrlTmpSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTCTRLTMP_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortctrlTmpSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortctrlTmpSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PORTCTRLTMP_SET */
    if ( AT_CMD_PORTCTRLTMP_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ��OM����Ϣ��OM�˿� */
        ulResult    = AT_PortCtrlTmpSndMsg();
        if ( AT_OK != ulResult)
        {
             ulResult    = AT_ERROR;
        }
        /* c64416 start in 2012-05-10 for LTE OM */
#if (FEATURE_ON==FEATURE_LTE)
        else
        {
            if(AT_SUCCESS != DMS_OpenHsicPort())
            {
                ulResult = AT_ERROR;
            }
        }
#endif
        /* c64416 end in 2012-05-10 for LTE OM */
    }
    else
    {
        /* ������ý��, ת�������� */
        ulResult         = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentPortAttribSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                   *pRcvMsg;
    DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU *pstEvent;
    VOS_UINT8                             ucIndex;
    VOS_UINT32                            ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTATTRIBSET_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PORTATTRIBSET_SET */
    if ( AT_CMD_PORTATTRIBSET_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        /* ������ý��, ת�������� */
        ulResult    = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentPortAttribSetQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                                     *pRcvMsg;
    DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU                   *pstEvent;
    VOS_UINT8                                               ucIndex;
    VOS_UINT32                                              ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_PORTATTRIBSET_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentPortAttribSetQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PORTATTRIBSET_READ */
    if ( AT_CMD_PORTATTRIBSET_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        if( (DRV_AGENT_PORT_STATUS_OFF  == pstEvent->enPortStatus)
         || (DRV_AGENT_PORT_STATUS_ON   == pstEvent->enPortStatus))
        {
            ulResult = AT_OK;
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstEvent->enPortStatus);
        }
        else
        {
            ulResult = AT_PERSONALIZATION_OTHER_ERROR;
        }
    }
    else
    {
        /* ������ý��, ת�������� */
        ulResult = AT_PERSONALIZATION_ERR_BEGIN + pstEvent->enResult;
    }

    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentOpwordSetCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                      *pRcvMsg;
    DRV_AGENT_OPWORD_SET_CNF_STRU           *pstEvent;
    VOS_UINT8                                ucIndex;
    VOS_UINT32                               ulResult;

    /* ��ʼ����Ϣ���� */
    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pMsg;
    pstEvent        = (DRV_AGENT_OPWORD_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstEvent->stAtAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvDrvAgentOpwordSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentOpwordSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_OPWORD_SET */
    if ( AT_CMD_OPWORD_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( DRV_AGENT_PERSONALIZATION_NO_ERROR == pstEvent->enResult )
    {
        /* ����ȶԳɹ�����ȡȨ�� */
        g_enATE5RightFlag   = AT_E5_RIGHT_FLAG_YES;
        ulResult            = AT_OK;
    }
    else
    {
        /* ������ý��, ת�������� */
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvDrvAgentAntSwitchSetCnf(VOS_VOID *pstData)
{
    VOS_UINT8                           ucIndex = 0;
    DRV_AGENT_ANTSWITCH_SET_CNF_STRU   *pstAntSwitchCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;

    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pstData;
    pstAntSwitchCnf = (DRV_AGENT_ANTSWITCH_SET_CNF_STRU *)pRcvMsg->aucContent;
    /* ����ClientID��ȡͨ������ */
    if(AT_FAILURE == At_ClientIdToUserId(pstAntSwitchCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: Get Index Fail!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ATģ���ڵȴ�^ANTSWITCH����Ĳ�������¼��ϱ� */
    if (AT_CMD_ANTSWITCH_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchSetCnf: Error Option!");
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK != pstAntSwitchCnf->ulResult)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvDrvAgentAntSwitchQryCnf(VOS_VOID *pstData)
{
    VOS_UINT8                           ucIndex = 0;
    DRV_AGENT_ANTSWITCH_QRY_CNF_STRU   *pstAntSwitchCnf;
    DRV_AGENT_MSG_STRU                 *pRcvMsg;

    pRcvMsg         = (DRV_AGENT_MSG_STRU *)pstData;
    pstAntSwitchCnf = (DRV_AGENT_ANTSWITCH_QRY_CNF_STRU *)pRcvMsg->aucContent;

    /* ����ClientID��ȡͨ������ */
    if(AT_FAILURE == At_ClientIdToUserId(pstAntSwitchCnf->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: Get Index Fail!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ATģ���ڵȴ�^ANTSWITCH����Ĳ�������¼��ϱ� */
    if (AT_CMD_ANTSWITCH_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvDrvAgentAntSwitchQryCnf: Error Option!");
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);
    gstAtSendData.usBufLen = 0;

    if(pstAntSwitchCnf->ulResult == VOS_OK)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstAntSwitchCnf->ulState);

        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }

    return VOS_OK;
}



VOS_UINT32 AT_RcvMtaCposSetCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                  *pstCposMsg;
    MTA_AT_CPOS_CNF_STRU             *pstEvent;
    VOS_UINT8                         ucIndex;
    VOS_UINT32                        ulResult;

    /* ��ʼ����Ϣ���� */
    pstCposMsg  = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent    = (MTA_AT_CPOS_CNF_STRU*)pstCposMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstCposMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_CPOS_SET */
    if ( AT_CMD_CPOS_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaCposSetCnf: WARNING:Not AT_CMD_CPOS_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult            = AT_OK;
    }
    else
    {
        ulResult            = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormatResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaCposrInd(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstCposrMsg;
    MTA_AT_CPOSR_IND_STRU              *pstEvent;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* ��ʼ����Ϣ���� */
    pstCposrMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent    = (MTA_AT_CPOSR_IND_STRU*)pstCposrMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCposrMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCposrInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ���ݵ�ǰ��AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enCposrReport��ֵ�ж��Ƿ����������ϱ��������ݺ�ָʾ */
    if (AT_CPOSR_ENABLE == pstAgpsCtx->enCposrReport)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s+CPOSR: %s%s",
                                                        gaucAtCrLf, pstEvent->acXmlText, gaucAtCrLf);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaXcposrRptInd(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstXcposrRptMsg;
    MTA_AT_XCPOSRRPT_IND_STRU          *pstEvent;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* ��ʼ����Ϣ���� */
    pstXcposrRptMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent        = (MTA_AT_XCPOSRRPT_IND_STRU*)pstXcposrRptMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstXcposrRptMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaXcposrRptInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ���ݵ�ǰ��AT_GetModemAgpsCtxAddrFromModemId(MODEM_ID_0)->enXcposrReport��ֵ�ж��Ƿ������ϱ������������ */
    if (AT_XCPOSR_ENABLE == pstAgpsCtx->enXcposrReport)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "^XCPOSRRPT: %d",
                                                        pstEvent->ulClearFlg);

        At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);
    }
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaCgpsClockSetCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                  *pRcvMsg;
    MTA_AT_CGPSCLOCK_CNF_STRU        *pstEvent;
    VOS_UINT8                         ucIndex;
    VOS_UINT32                        ulResult;
    /* ��ʼ����Ϣ���� */
    pRcvMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstEvent = (MTA_AT_CGPSCLOCK_CNF_STRU*)pRcvMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId,&ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_CGPSCLOCK_SET */
    if ( AT_CMD_CGPSCLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaCgpsClockSetCnf: WARNING:Not AT_CMD_CGPSCLOCK_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstEvent->enResult )
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;
    /* ����AT_FormATResultDATa���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

VOS_VOID At_ProcMtaMsg(AT_MTA_MSG_STRU *pstMsg)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRst;

    /*��g_astAtProcMsgFromMtaTab�л�ȡ��Ϣ����*/
    ulMsgCnt = sizeof(g_astAtProcMsgFromMtaTab)/sizeof(AT_PROC_MSG_FROM_MTA_STRU);

    /*����Ϣ���л�ȡMSG ID*/
    ulMsgId  = ((AT_MTA_MSG_STRU *)pstMsg)->ulMsgId;

    /*g_astAtProcMsgFromMtaTab���������Ϣ�ַ�*/
    for (i = 0; i < ulMsgCnt; i++)
    {
        if (g_astAtProcMsgFromMtaTab[i].ulMsgType == ulMsgId)
        {
            ulRst = g_astAtProcMsgFromMtaTab[i].pProcMsgFunc(pstMsg);

            if (VOS_ERR == ulRst)
            {
                AT_ERR_LOG("At_ProcMtaMsg: Msg Proc Err!");
            }

            return;
        }
    }

    /*û���ҵ�ƥ�����Ϣ*/
    if (ulMsgCnt == i)
    {
        AT_ERR_LOG("At_ProcMtaMsg: Msg Id is invalid!");
    }

    return;
}


VOS_UINT32 AT_RcvMtaApSecSetCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_APSEC_CNF_STRU              *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulLoop;

    /* ��ʼ�� */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstEvent        = (MTA_AT_APSEC_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    usLength        = 0;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaApSecSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaApSecSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_APSEC_SET */
    if (AT_CMD_APSEC_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaApSecSetCnf: NOT CURRENT CMD OPTION!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϻظ���Ϣ�еĴ����� */
    if (MTA_AT_RESULT_NO_ERROR == pstEvent->enResult)
    {
        /* ������ý�� */
        ulResult    = AT_OK;

        /* ����ɹ��������ȫ�������ӡ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (ulLoop = 0; ulLoop < pstEvent->ulSPLen; ulLoop++)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%02X",
                                               pstEvent->aucSecPacket[ulLoop]);
        }
    }
    else
    {
        /* �쳣���, ���ERROR */
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = usLength;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaSimlockUnlockSetCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_SIMLOCKUNLOCK_CNF_STRU      *pstEvent;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    pstRcvMsg       = (AT_MTA_MSG_STRU *)pMsg;
    pstEvent        = (MTA_AT_SIMLOCKUNLOCK_CNF_STRU *)pstRcvMsg->aucContent;
    ucIndex         = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_SIMLOCKUNLOCK_SET */
    if (AT_CMD_SIMLOCKUNLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSimlockUnlockSetCnf: NOT CURRENT CMD OPTION!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϻظ���Ϣ�еĴ����� */
    if (MTA_AT_RESULT_NO_ERROR == pstEvent->enResult)
    {
        /* �����ɹ������OK */
        ulResult    = AT_OK;
    }
    else
    {
        /* ����ʧ�ܣ����ERROR */
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaQryNmrCnf( VOS_VOID *pMsg )
{
    AT_MTA_MSG_STRU                    *pRcvMsg      = VOS_NULL_PTR;
    MTA_AT_QRY_NMR_CNF_STRU            *pstQryNmrCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulNmrDataIndex;
    VOS_UINT16                          usLength;

    /* ��ʼ�� */
    pRcvMsg      = (AT_MTA_MSG_STRU *)pMsg;
    pstQryNmrCnf = (MTA_AT_QRY_NMR_CNF_STRU *)(pRcvMsg->aucContent);

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNmrCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNmrCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CNMR_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    if (MTA_AT_RESULT_ERROR == pstQryNmrCnf->enResult)
    {
        /* ��ѯʧ��ֱ���ϱ�error */
        gstAtSendData.usBufLen = 0;

        /* ��λAT״̬ */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* ������ */
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_OK;
    }

    usLength = 0;

    /* ��AT^CNMR��ѯ����ؽ�����㷵�ص�����������ʾ�ϱ� */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    if (0 == pstQryNmrCnf->ucTotalIndex)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%d,%d",
                                           0,
                                           0);

        gstAtSendData.usBufLen = usLength;

        /* ��λAT״̬ */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* ������ */
        At_FormatResultData(ucIndex, AT_OK);
        return VOS_OK;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d,%d,",
                                       pstQryNmrCnf->ucTotalIndex,
                                       pstQryNmrCnf->ucCurrIndex);

    for (ulNmrDataIndex = 0; ulNmrDataIndex < pstQryNmrCnf->usNMRLen; ulNmrDataIndex++)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                           "%02x",
                                           pstQryNmrCnf->aucNMRData[ulNmrDataIndex]);
    }

    if (pstQryNmrCnf->ucTotalIndex != pstQryNmrCnf->ucCurrIndex)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s",
                                          gaucAtCrLf);

         At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);
    }


    if (pstQryNmrCnf->ucTotalIndex == pstQryNmrCnf->ucCurrIndex)
    {
        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        gstAtSendData.usBufLen = 0;

        /* ��λAT״̬ */
        AT_STOP_TIMER_CMD_READY(ucIndex);

        /* ������ */
        At_FormatResultData(ucIndex, AT_OK);
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrAutotestQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU   *pstWrrAutotestCnf   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrAutotestCnf   = (MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CWAS_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrAutotestQryCnf : Current Option is not AT_CMD_CWAS_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CWAS����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrAutotestCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        if (pstWrrAutotestCnf->stWrrAutoTestRslt.ulRsltNum > 0)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                             "%d",
                                                             pstWrrAutotestCnf->stWrrAutoTestRslt.aulRslt[0]);

            for (i = 1; i < pstWrrAutotestCnf->stWrrAutoTestRslt.ulRsltNum; i++)
            {
                gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                 (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                                 ",%d",
                                                                 pstWrrAutotestCnf->stWrrAutoTestRslt.aulRslt[i]);
            }
        }
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrCellinfoQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg              = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU   *pstWrrCellinfoQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;

    /* ��ʼ�� */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellinfoQryCnf    = (MTA_AT_WRR_CELLINFO_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CELLINFO_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoQryCnf : Current Option is not AT_CMD_CELLINFO_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CELLINFO����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellinfoQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /*û�л�ȡ��С����Ϣ����ӡ0*/
        if ( 0 == pstWrrCellinfoQryCnf->stWrrCellInfo.ulCellNum )
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                               "no cellinfo rslt");
        }

        for (i = 0; i< pstWrrCellinfoQryCnf->stWrrCellInfo.ulCellNum; i++)
        {
#ifdef BSP_CONFIG_BOARD_E5573S_156
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                             "^CELLINFO:%d,%d,%d,%d\r\n",
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usCellFreq,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usPrimaryScramCode,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichRscp,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichEcN0);
#else
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                             "%d,%d,%d,%d\r\n",
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usCellFreq,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usPrimaryScramCode,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichRscp,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichEcN0);
#endif
        }
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

#ifdef BSP_CONFIG_BOARD_E5573S_156
VOS_UINT32 AT_RcvMtaWrrCellinfoCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg              = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU   *pstWrrCellinfoQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          i;

    /* ��ʼ�� */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellinfoQryCnf    = (MTA_AT_WRR_CELLINFO_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CELLINFO_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellinfoCnf : Current Option is not AT_CMD_CELLINFO_QUERY.");
        //return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CELLINFO����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellinfoQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /*û�л�ȡ��С����Ϣ����ӡ0*/
        if ( 0 == pstWrrCellinfoQryCnf->stWrrCellInfo.ulCellNum )
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                               "no cellinfo rslt");
        }

        for (i = 0; i< pstWrrCellinfoQryCnf->stWrrCellInfo.ulCellNum; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr,
                                                             (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                             "^CELLINFO:%d,%d,%d,%d\r\n",
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usCellFreq,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].usPrimaryScramCode,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichRscp,
                                                             pstWrrCellinfoQryCnf->stWrrCellInfo.astWCellInfo[i].sCpichEcN0);
        }
    }
    At_SendResultData(AT_BROADCAST_CLIENT_INDEX_MODEM_0, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    /* ������ */
   // At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
#endif


VOS_UINT32 AT_RcvMtaWrrMeanrptQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU    *pstWrrMeanrptQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usLength;
    VOS_UINT32                          i;
    VOS_UINT32                          ulCellNumLoop;

    /* ��ʼ�� */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrMeanrptQryCnf     = (MTA_AT_WRR_MEANRPT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    usLength                = 0;
    ucIndex                 = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_MEANRPT_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrMeanrptQryCnf : Current Option is not AT_CMD_MEANRPT_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^MEANRPT����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrMeanrptQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                           "%d",
                                           pstWrrMeanrptQryCnf->stMeanRptRslt.ulRptNum);

        for ( i = 0 ; i < pstWrrMeanrptQryCnf->stMeanRptRslt.ulRptNum; i++ )
        {
            usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (TAF_CHAR *)pgucAtSndCodeAddr,
                                               (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                               "\r\n0x%X,%d",
                                                pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usEventId,
                                                pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usCellNum );
            for ( ulCellNumLoop = 0; ulCellNumLoop < pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].usCellNum; ulCellNumLoop++ )
            {
                usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR*)pgucAtSndCodeAddr+usLength,
                                                   ",%d",
                                                   pstWrrMeanrptQryCnf->stMeanRptRslt.astMeanRptInfo[i].ausPrimaryScramCode[ulCellNumLoop]);
            }

        }
        gstAtSendData.usBufLen = usLength;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrCellSrhSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_SET_CNF_STRU    *pstWrrCellSrhSetCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellSrhSetCnf = (MTA_AT_WRR_CELLSRH_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_WAS_MNTN_SET_CELLSRH != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhSetCnf : Current Option is not AT_CMD_WAS_MNTN_SET_CELLSRH.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CELLSRH����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellSrhSetCnf->ulResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrCellSrhQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_CELLSRH_QRY_CNF_STRU    *pstWrrCellSrhQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrCellSrhQryCnf = (MTA_AT_WRR_CELLSRH_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_WAS_MNTN_QRY_CELLSRH != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrCellSrhQryCnf : Current Option is not AT_CMD_WAS_MNTN_QRY_CELLSRH.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^FREQLOCK��ѯ����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrCellSrhQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR*)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (TAF_INT32)pstWrrCellSrhQryCnf->ucCellSearchType);

    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrFreqLockSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_SET_CNF_STRU   *pstWrrFreqlockCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrFreqlockCnf   = (MTA_AT_WRR_FREQLOCK_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_FREQLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockSetCnf : Current Option is not AT_CMD_FREQLOCK_SET.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^FREQLOCK����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrFreqlockCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrFreqLockQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU   *pstWrrFreqlockCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrFreqlockCnf   = (MTA_AT_WRR_FREQLOCK_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_FREQLOCK_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrFreqLockQryCnf : Current Option is not AT_CMD_FREQLOCK_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^FREQLOCK��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstWrrFreqlockCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        if (VOS_FALSE == pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable)
        {
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable);
        }
        else
        {
            gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                                            (TAF_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.ucFreqLockEnable,
                                                            (TAF_INT32)pstWrrFreqlockCnf->stFreqLockInfo.usLockedFreq);
        }

    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaWrrRrcVersionSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                        *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU    *pstWrrVersionSetCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ��ʼ�� */
    pRcvMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrVersionSetCnf     = (MTA_AT_WRR_RRC_VERSION_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_RRC_VERSION_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionSetCnf : Current Option is not AT_CMD_RRC_VERSION_SET.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^FREQLOCK����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrVersionSetCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        /* ���óɹ������¶�дһ��NV */
        /* Modified by l60609 for DSDA Phase III, 2013-3-5, Begin */
        AT_ReadWasCapabilityNV();
        /* Modified by l60609 for DSDA Phase III, 2013-3-5, End */

        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}




VOS_UINT32 AT_RcvMtaWrrRrcVersionQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                        *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU    *pstWrrVersionQryCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstWrrVersionQryCnf = (MTA_AT_WRR_RRC_VERSION_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_RRC_VERSION_QUERY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaWrrRrcVersionQryCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^FREQLOCK��ѯ����� */
    gstAtSendData.usBufLen = 0;

    if (VOS_OK != pstWrrVersionQryCnf->ulResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (TAF_INT32)pstWrrVersionQryCnf->ucRrcVersion);

    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaAcInfoQueryCnf(VOS_VOID *pstMsg)
{
    TAF_MMA_AC_INFO_QUERY_CNF_STRU     *pstAcInfoQueryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pstAcInfoQueryCnf       = (TAF_MMA_AC_INFO_QUERY_CNF_STRU*)pstMsg;
    usLength                = 0;
    ulResult                = AT_OK;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstAcInfoQueryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAcInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaAcInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_LOCINFO_READ */
    if (AT_CMD_ACINFO_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ����Ƿ�ʧ��,���ʧ���򷵻�ERROR */
    if (VOS_OK != pstAcInfoQueryCnf->ulRslt)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s:%d,%d,%d,%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.ucSrvDomain),/* �ϱ������� */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.enCellAcType),/* �ϱ�С����ֹ�������� */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.ucRestrictRegister),/* �ϱ��Ƿ�ע������ */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellCsAcInfo.ucRestrictPagingRsp));/* �ϱ��Ƿ�Ѱ������ */

        /* ���� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s",
                                          gaucAtCrLf);

        usLength  += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s:%d,%d,%d,%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.ucSrvDomain),/* �ϱ������� */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.enCellAcType),/* �ϱ�С����ֹ�������� */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.ucRestrictRegister),/* �ϱ��Ƿ�ע������ */
                                          (VOS_UINT8)(pstAcInfoQueryCnf->stCellPsAcInfo.ucRestrictPagingRsp));/* �ϱ��Ƿ�Ѱ������ */

        gstAtSendData.usBufLen = usLength;

    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMtaQryCurcCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg          = VOS_NULL_PTR;
    MTA_AT_CURC_QRY_CNF_STRU               *pstMtaAtQryCurcCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;
    VOS_UINT8                               ucLoop;

    /* ��ʼ�� */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtQryCurcCnf  = (MTA_AT_CURC_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;
    usLength            = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CURC_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryCurcCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^CURC��ѯ����� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryCurcCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        usLength        += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  "%s: %d",
                                                  g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                  pstMtaAtQryCurcCnf->enCurcRptType);

        /* ���<mode>����Ϊ2����Ҫ��ӡ����<report_cfg> */
        if (AT_MTA_RPT_GENERAL_CONTROL_CUSTOM == pstMtaAtQryCurcCnf->enCurcRptType)
        {
            usLength    += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  ",0x");

            for (ucLoop = 0; ucLoop < AT_CURC_RPT_CFG_MAX_SIZE; ucLoop++)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%02X",
                                                   pstMtaAtQryCurcCnf->aucRptCfg[ucLoop]);
            }
        }
    }

    gstAtSendData.usBufLen = usLength;

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaSetUnsolicitedRptCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU    *pstSetUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ��ʼ�� */
    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstSetUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_UNSOLICITED_RPT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetUnsolicitedRptCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ������� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstSetUnsolicitedCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}


VOS_UINT32 AT_RcvMtaQryUnsolicitedRptCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU    *pstQryUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ��ʼ�� */
    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstQryUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;
    ucIndex                 = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_UNSOLICITED_RPT_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryUnsolicitedRptCnf : Current Option is not AT_CMD_RRC_VERSION_QUERY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ����ѯ����� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstQryUnsolicitedCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        /* ucIndex���������� */
        ulResult = AT_ProcMtaUnsolicitedRptQryCnf(ucIndex, pstMsg);
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_ProcMtaUnsolicitedRptQryCnf(
    VOS_UINT8                               ucIndex,
    VOS_VOID                               *pstMsg
)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg            = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU    *pstQryUnsolicitedCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    /* ucIndexͨ���ϲ㺯�������� */

    pstRcvMsg               = (AT_MTA_MSG_STRU *)pstMsg;
    pstQryUnsolicitedCnf    = (MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult                = AT_OK;

    switch (pstQryUnsolicitedCnf->enReqType)
    {
        /* TIME��ѯ�Ĵ��� */
        case AT_MTA_QRY_TIME_RPT_TYPE:
            gstAtSendData.usBufLen =
                (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR*)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr,
                                       "%s: %d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstQryUnsolicitedCnf->u.ucTimeRptFlg);
            break;

        /* CTZR��ѯ�Ĵ��� */
        case AT_MTA_QRY_CTZR_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: %d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pstQryUnsolicitedCnf->u.ucCtzvRptFlg);
            break;

        /* CSSN��ѯ�Ĵ��� */
        case AT_MTA_QRY_CSSN_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,
                                                            "%s: %d,%d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstQryUnsolicitedCnf->u.stCssnRptFlg.ucCssiRptFlg,
                                                            pstQryUnsolicitedCnf->u.stCssnRptFlg.ucCssuRptFlg);
            break;

        /* CUSD��ѯ�Ĵ��� */
        case AT_MTA_QRY_CUSD_RPT_TYPE:
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                                            (VOS_CHAR*)pgucAtSndCodeAddr,"%s: %d",
                                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                            pstQryUnsolicitedCnf->u.ucCusdRptFlg);
            break;

        default:
            ulResult = AT_CME_UNKNOWN;

    }

    return ulResult;
}



VOS_UINT32 AT_RcvMmaCerssiInfoQueryCnf(VOS_VOID *pstMsg)
{
    TAF_MMA_CERSSI_INFO_QUERY_CNF_STRU *pstCerssiInfoQueryCnf = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;


    /* ��ʼ�� */
    pstCerssiInfoQueryCnf   = (TAF_MMA_CERSSI_INFO_QUERY_CNF_STRU*)pstMsg;
    usLength                = 0;


    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCerssiInfoQueryCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCerssiInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_CERSSI_READ */
    if (AT_CMD_CERSSI_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ����Ƿ�ʧ��,���ʧ���򷵻�ERROR */
    if (VOS_OK != pstCerssiInfoQueryCnf->ucRslt)
    {
        At_FormatResultData(ucIndex, AT_ERROR);
        return VOS_ERR;
    }
    else
    {
        if (TAF_PH_RAT_GSM == pstCerssiInfoQueryCnf->stCerssi.enRatType)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                               gaucAtCrLf,
                                               gastAtStringTab[AT_STRING_CERSSI].pucText,
                                               pstNetCtx->ucCerssiReportType,
                                               pstNetCtx->ucCerssiMinTimerInterval,
                                               pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stGCellSignInfo.sRssiValue,
                                               0,
                                               255,
                                               0,
                                               0,
                                               0,
                                               0,
                                               gaucAtCrLf);

            gstAtSendData.usBufLen = usLength;

            /* ������ */
            At_FormatResultData(ucIndex, AT_OK);
            return VOS_OK;
        }

        if (TAF_PH_RAT_WCDMA == pstCerssiInfoQueryCnf->stCerssi.enRatType)
        {
            if (TAF_UTRANCTRL_UTRAN_MODE_FDD == pstCerssiInfoQueryCnf->stCerssi.ucCurrentUtranMode)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   gastAtStringTab[AT_STRING_CERSSI].pucText,
                                                   pstNetCtx->ucCerssiReportType,
                                                   pstNetCtx->ucCerssiMinTimerInterval,
                                                   0,      /* rssi */
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sEcioValue,
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   gaucAtCrLf);

                gstAtSendData.usBufLen = usLength;

                /* ������ */
                At_FormatResultData(ucIndex, AT_OK);
                return VOS_OK;
            }
            else
            {
                /* ��fdd 3g С����ecioֵΪ��Чֵ255 */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                                   gaucAtCrLf,
                                                   gastAtStringTab[AT_STRING_CERSSI].pucText,
                                                   pstNetCtx->ucCerssiReportType,
                                                   pstNetCtx->ucCerssiMinTimerInterval,
                                                   0,      /* rssi */
                                                   pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                                   255,
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   gaucAtCrLf);



                gstAtSendData.usBufLen = usLength;

                /* ������ */
                At_FormatResultData(ucIndex, AT_OK);
                return VOS_OK;

            }
        }

    }

    /* �տ���û�н���ģʽ��������������Чֵ */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s%s%d,%d,%d,%d,%d,%d,%d,%d,%d%s",
                                        gaucAtCrLf,
                                        gastAtStringTab[AT_STRING_CERSSI].pucText,
                                        pstNetCtx->ucCerssiReportType,
                                        pstNetCtx->ucCerssiMinTimerInterval,
                                        pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stGCellSignInfo.sRssiValue,      /* rssi */
                                        pstCerssiInfoQueryCnf->stCerssi.aRssi[0].u.stWCellSignInfo.sRscpValue,
                                        255,
                                        0,
                                        0,
                                        0,
                                        0,
                                        gaucAtCrLf);

    gstAtSendData.usBufLen = usLength;

    /* ������ */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}




VOS_UINT32 AT_RcvMtaBodySarSetCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                    *pRcvMsg             = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU             *pstBodySarSetCnf    = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg          = (AT_MTA_MSG_STRU*)pstMsg;
    pstBodySarSetCnf = (MTA_AT_RESULT_CNF_STRU*)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaBodySarSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaBodySarSetCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_BODYSARON_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϻظ���Ϣ�еĴ����� */
    if (MTA_AT_RESULT_NO_ERROR == pstBodySarSetCnf->enResult)
    {
        ulResult    = AT_OK;

        /* ����BODYSAR ״̬ */
        if (MTA_BODY_SAR_OFF == g_enAtBodySarState)
        {
            g_enAtBodySarState = MTA_BODY_SAR_ON;
        }
        else
        {
            g_enAtBodySarState = MTA_BODY_SAR_OFF;
        }
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_VOID AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_ENUM_UINT32 enCause)
{
    VOS_UINT16                          usLength;

    usLength = 0;

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                        (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                        "%s%s%d%s",
                                        gaucAtCrLf,
                                        gastAtStringTab[AT_STRING_RESET].pucText,
                                        enCause,
                                        gaucAtCrLf);

    /* ��Ҫ�ϱ����ϲ��˫RIL */
    At_SendResultData(AT_CLIENT_ID_APP,  pgucAtSndCodeAddr, usLength);
    At_SendResultData(AT_CLIENT_ID_PCUI, pgucAtSndCodeAddr, usLength);

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    At_SendResultData(AT_CLIENT_ID_APP5, pgucAtSndCodeAddr, usLength);
    At_SendResultData(AT_CLIENT_ID_CTRL, pgucAtSndCodeAddr, usLength);
#endif

    return;
}


VOS_VOID AT_StopAllTimer(VOS_VOID)
{
    VOS_UINT8                           ucModemIndex;
    VOS_UINT8                           ucClientIndex;
    VOS_UINT32                          ulTimerName;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx         = VOS_NULL_PTR;
    AT_PARSE_CONTEXT_STRU              *pstParseContext = VOS_NULL_PTR;
    AT_CLIENT_MANAGE_STRU              *pstClientContext = VOS_NULL_PTR;

    for (ucModemIndex = 0; ucModemIndex < MODEM_ID_BUTT; ucModemIndex++)
    {
        pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucModemIndex);

        /* ֹͣS0��ʱ�� */
        if (VOS_TRUE == pstCcCtx->stS0TimeInfo.bTimerStart)
        {
            ulTimerName = pstCcCtx->stS0TimeInfo.ulTimerName;

            AT_StopRelTimer(ulTimerName, &(pstCcCtx->stS0TimeInfo.s0Timer));
            pstCcCtx->stS0TimeInfo.bTimerStart = VOS_FALSE;
            pstCcCtx->stS0TimeInfo.ulTimerName = 0;
        }

    }

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        pstParseContext = &(g_stParseContext[ucClientIndex]);
        AT_StopRelTimer(ucClientIndex, &pstParseContext->hTimer);

        pstClientContext = &(gastAtClientTab[ucClientIndex]);
        AT_StopRelTimer(ucClientIndex, &pstClientContext->hTimer);
    }

    return;
}


VOS_VOID AT_ResetParseCtx(VOS_VOID)
{
    VOS_UINT8                           ucClientIndex;
    AT_PARSE_CONTEXT_STRU              *pstParseContext = VOS_NULL_PTR;

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        pstParseContext = &(g_stParseContext[ucClientIndex]);

        pstParseContext->ucClientStatus = AT_FW_CLIENT_STATUS_READY;
        AT_CLIENT_STATUS_PRINT_2(ucClientIndex, g_stParseContext[ucClientIndex].ucClientStatus);
        /* ������еĻ����AT���� */
        AT_ClearBlockCmdInfo(ucClientIndex);

        /* ����AT��������������Ϣ */
        At_ResetCombinParseInfo(ucClientIndex);

        pstParseContext->ucMode    = AT_NORMAL_MODE;
        AT_USB_WORK_MODE_PRINT(ucClientIndex, AT_CMD_MODE,AT_NORMAL_MODE);
        pstParseContext->usDataLen = 0;
        pstParseContext->usCmdLineLen = 0;

        PS_MEM_SET(pstParseContext->aucDataBuff, 0x00, AT_CMD_MAX_LEN);

        if (NULL != pstParseContext->pucCmdLine)
        {
            AT_FREE(pstParseContext->pucCmdLine);
            pstParseContext->pucCmdLine = NULL;
        }
    }

    return;
}


VOS_VOID AT_ResetClientTab(VOS_VOID)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucClientIndex;

    for (ucClientIndex = 0; ucClientIndex < AT_MAX_CLIENT_NUM; ucClientIndex++)
    {
        /* ��ն�Ӧ���� */
        PS_MEM_SET(&gastAtClientTab[ucClientIndex], 0x00, sizeof(AT_CLIENT_MANAGE_STRU));
    }

    /* USB PCUI */
    ucIndex = AT_CLIENT_TAB_PCUI_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_PCUI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_USB_COM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_USBCOM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB Control */
    ucIndex = AT_CLIENT_TAB_CTRL_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_CTRL;
    gastAtClientTab[ucIndex].ucPortNo        = AT_CTR_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_CTR_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB MODEM */
    ucIndex = AT_CLIENT_TAB_MODEM_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_MODEM;
    gastAtClientTab[ucIndex].ucPortType      = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci          = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_USB_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* NDIS MODEM */
    ucIndex = AT_CLIENT_TAB_NDIS_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_NDIS;
    gastAtClientTab[ucIndex].ucPortNo        = AT_NDIS_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_NDIS_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* USB UART */
    ucIndex = AT_CLIENT_TAB_UART_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_UART;
    gastAtClientTab[ucIndex].ucPortNo        = AT_UART_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_UART_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

#if (FEATURE_ON == FEATURE_AT_HSUART)
    /* HSUART */
    ucIndex = AT_CLIENT_TAB_HSUART_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_HSUART;
    gastAtClientTab[ucIndex].ucPortNo        = AT_HSUART_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_HSUART_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;
#endif

    /* SOCK */
    ucIndex = AT_CLIENT_TAB_SOCK_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_SOCK;
    gastAtClientTab[ucIndex].ucPortNo        = AT_SOCK_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

    /* APP SOCK */
    ucIndex = AT_CLIENT_TAB_APPSOCK_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_APPSOCK;
    gastAtClientTab[ucIndex].ucPortNo        = AT_APP_SOCK_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_APP_SOCK_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;

#if (FEATURE_ON == FEATURE_AT_HSIC)
    /* HSIC */
    for (ucLoop = 0; ucLoop < AT_HSIC_AT_CHANNEL_MAX; ucLoop++)
    {
        ucIndex = g_astAtHsicCtx[ucLoop].ucAtClientTabIdx;
        gastAtClientTab[ucIndex].usClientId  = g_astAtHsicCtx[ucLoop].enAtClientId;
        gastAtClientTab[ucIndex].ucPortNo    = g_astAtHsicCtx[ucLoop].ucHsicPort;
        gastAtClientTab[ucIndex].UserType    = g_astAtHsicCtx[ucLoop].ucHsicUser;
        gastAtClientTab[ucIndex].ucUsed      = AT_CLIENT_USED;
    }
#endif
    /* MAX ��NV�����Ƶģ�CLIENT TAB�����÷��� AT_MuxInit���� */

    /* APP */
    for (ucLoop = 0; ucLoop < AT_VCOM_AT_CHANNEL_MAX; ucLoop++)
    {
        ucIndex = AT_CLIENT_TAB_APP_INDEX + ucLoop;
        gastAtClientTab[ucIndex].usClientId  = AT_CLIENT_ID_APP + ucLoop;
        gastAtClientTab[ucIndex].ucPortNo    = APP_VCOM_DEV_INDEX_0 + ucLoop;
        gastAtClientTab[ucIndex].UserType    = AT_APP_USER;
        gastAtClientTab[ucIndex].ucUsed      = AT_CLIENT_USED;
    }

#if (FEATURE_ON == FEATURE_AT_HSIC)
    /* HSIC MODEM */
    ucIndex = AT_CLIENT_TAB_HSIC_MODEM_INDEX;
    gastAtClientTab[ucIndex].usClientId      = AT_CLIENT_ID_HSIC_MODEM;
    gastAtClientTab[ucIndex].ucPortType      = AT_HSIC_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].ucDlci          = AT_MODEM_USER_DLCI;
    gastAtClientTab[ucIndex].ucPortNo        = AT_HSIC_MODEM_PORT_NO;
    gastAtClientTab[ucIndex].UserType        = AT_MODEM_USER;
    gastAtClientTab[ucIndex].ucUsed          = AT_CLIENT_USED;
#endif

}


VOS_VOID AT_ResetOtherCtx(VOS_VOID)
{
    /* <CR> */
    ucAtS3          = 13;

    gaucAtCrLf[0]   = ucAtS3;

    /* <LF> */
    ucAtS4          = 10;

    gaucAtCrLf[1]   = ucAtS4;

    /* <DEL> */
    ucAtS5          = 8;

    /* ָʾ����������� */
    gucAtVType      = AT_V_ENTIRE_TYPE;

    /* ָʾTE�������� */
    gucAtCscsType   = AT_CSCS_IRA_CODE;

    gucAtEType      = AT_E_ECHO_CMD;

    /* CONNECT <text> result code is given upon entering online data state.
       Dial tone and busy detection are disabled. */
    gucAtXType      = 0;
}


VOS_UINT32 AT_RcvCcpuResetStartInd(
    VOS_VOID                           *pstMsg
)
{
    /* �ϱ�^RESET:0���� */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_CCPU_START);

    /* ֹͣ�����������ڲ���ʱ�� */
    AT_StopAllTimer();

    /* ��ʼ����������Ϣ */
    AT_InitCtx();

    /* ��ȡNV�� */
    AT_ReadNV();

    /* װ����ʼ�� */
    AT_InitDeviceCmd();

    /* STK��ʼ�� */
    AT_InitStk();

    /* ATģ������ĳ�ʼ�� */
    AT_InitPara();

    /* ���ÿͻ��˽�����Ϣ */
    AT_ResetParseCtx();

    /* �����û���Ϣ */
    AT_ResetClientTab();

#if (FEATURE_ON == FEATURE_AT_HSIC)
    /* ��ʼ��MAXͨ�� */
    AT_MuxInit();
#endif

    /* ��������ɢ���ȫ�ֱ��� */
    AT_ResetOtherCtx();

    /* C�˵�����λ�������豸�ڵ㣬��ǰδ���� */
    DRV_MODEM_STATE_SET(PS_FALSE);

    /* �ͷ��ź�����ʹ�õ���API����������� */
    VOS_SmV(AT_GetResetSem());

    return VOS_OK;
}

VOS_UINT32 AT_RcvCcpuResetEndInd(
    VOS_VOID                           *pstMsg
)
{
    /* ���ø�λ��ɵı�־ */
    AT_SetResetFlag(VOS_FALSE);

    /* �ϱ�^RESET:1���� */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_CCPU_END);

    return VOS_OK;
}

VOS_UINT32 AT_RcvHifiResetStartInd(
    VOS_VOID                           *pstMsg
)
{
    /* �ϱ�^RESET:2���� */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_HIFI_START);

    AT_DBG_SAVE_HIFI_RESET_NUM(1);

    return VOS_OK;
}


VOS_UINT32 AT_RcvHifiResetEndInd(
    VOS_VOID                           *pstMsg
)
{
    /* �ϱ�^RESET:3���� */
    AT_ReportResetCmd(AT_RESET_REPORT_CAUSE_HIFI_END);

    return VOS_OK;
}


VOS_UINT32 AT_SpyMsgProc(VOS_VOID* pstMsg)
{
    VOS_UINT32 ulRet = VOS_OK;
    TEMP_PROTECT_EVENT_AT_IND_STRU* pDataMsg = (TEMP_PROTECT_EVENT_AT_IND_STRU*)pstMsg;
/*�����ж�*/
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
    if(SPY_STATE_PSOFF == pDataMsg->ulTempProtectEvent)
    {
        g_TempprtEvent_flag = AT_ANT_TEMPPRTEVENT_H;
    }
    else
    {
        g_TempprtEvent_flag = AT_ANT_TEMPPRTEVENT_L;
    }
#endif
    switch(pDataMsg->ulMsgId)
    {
#if ( FEATURE_ON == FEATURE_LTE )
        case ID_TEMPPRT_AT_EVENT_IND:
            ulRet = AT_ProcTempprtEventInd(pDataMsg);
            break;
#endif

        case ID_TEMPPRT_STATUS_AT_EVENT_IND:
            ulRet = AT_RcvTempprtStatusInd(pDataMsg);
            break;

        default:
            AT_WARN_LOG("AT_SpyMsgProc:WARNING:Wrong Msg!\n");
            break;
    }

    return ulRet;
}


VOS_UINT32 AT_RcvTempprtStatusInd(VOS_VOID *pMsg)
{
    TEMP_PROTECT_EVENT_AT_IND_STRU     *pstTempPrt = VOS_NULL_PTR;
    TAF_TEMP_PROTECT_CONFIG_STRU        stTempProtectPara;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stTempProtectPara, 0x0, sizeof(stTempProtectPara));

    /* ��ȡ�¶ȱ���״̬�����ϱ�NV�� */
    ulResult = NV_ReadEx(MODEM_ID_0,
                         en_NV_Item_TEMP_PROTECT_CONFIG,
                         &stTempProtectPara,
                         sizeof(TAF_TEMP_PROTECT_CONFIG_STRU));

    if (NV_OK != ulResult)
    {
        AT_ERR_LOG("AT_RcvTempprtStatusInd: Read NV fail");
        return VOS_ERR;
    }

    if (AT_TEMPPRT_STATUS_IND_ENABLE == stTempProtectPara.ucSpyStatusIndSupport)
    {
        pstTempPrt = (TEMP_PROTECT_EVENT_AT_IND_STRU*)pMsg;

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s^THERM: %d%s",
                                                         gaucAtCrLf, pstTempPrt->ulTempProtectEvent, gaucAtCrLf);

        At_SendResultData(AT_BROADCAST_CLIENT_INDEX_MODEM_0, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

        return VOS_OK;
    }

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaImeiVerifyQryCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                    *pRcvMsg       = VOS_NULL_PTR;
    VOS_UINT32                         *pulImeiVerify = VOS_NULL_PTR;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg       = (AT_MTA_MSG_STRU*)pstMsg;
    pulImeiVerify = (VOS_UINT32*)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaImeiVerifyQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaImeiVerifyQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_IMEI_VERIFY_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ӡ^IMEIVERIFY */
    usLength  = 0;
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "^IMEIVERIFY: ");

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       *pulImeiVerify);

    gstAtSendData.usBufLen = usLength;
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaCgsnQryCnf(VOS_VOID *pstMsg)
{
    VOS_UINT32                          ulI;
    VOS_UINT8                           ucCheckData;
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstRcvMsg;
    MTA_AT_CGSN_QRY_CNF_STRU           *pstCgsn;
    VOS_UINT8                           aucImeiAscii[TAF_PH_IMEI_LEN];

    /* ��ʼ�� */
    ucCheckData   = 0;
    PS_MEM_SET(aucImeiAscii, 0x00, TAF_PH_IMEI_LEN);

    pstRcvMsg = (AT_MTA_MSG_STRU*)pstMsg;
    pstCgsn   = (MTA_AT_CGSN_QRY_CNF_STRU *)pstRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgsnQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaCgsnQryCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_CGSN_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ȡIMEI��Ϣ */
    for (ulI = 0; ulI < (TAF_PH_IMEI_LEN - 2); ulI += 2)
    {
        aucImeiAscii[ulI]     = pstCgsn->aucImei[ulI] + 0x30;
        aucImeiAscii[ulI + 1] = pstCgsn->aucImei[ulI + 1] + 0x30;

        ucCheckData += (TAF_UINT8)(pstCgsn->aucImei[ulI]
                       +((pstCgsn->aucImei[ulI + 1] * 2) / 10)
                       +((pstCgsn->aucImei[ulI + 1] * 2) % 10));
    }
    ucCheckData = (10 - (ucCheckData%10)) % 10;

    aucImeiAscii[TAF_PH_IMEI_LEN - 2] = ucCheckData + 0x30;
    aucImeiAscii[TAF_PH_IMEI_LEN - 1] = 0;

    gstAtSendData.usBufLen  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      "%s",
                                      aucImeiAscii);

    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
}


/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */

VOS_UINT32 AT_RcvMmaCopnInfoQueryCnf(VOS_VOID *pMsg)
{
    TAF_MMA_COPN_INFO_QUERY_CNF_STRU   *pstCopnInfo = VOS_NULL_PTR;
    TAF_PH_OPERATOR_NAME_STRU          *pstPlmnName = VOS_NULL_PTR;
    TAF_MMA_COPN_INFO_QUERY_REQ_STRU    stCopnInfo;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;

    /* ��ʼ�� */
    pstCopnInfo   = (TAF_MMA_COPN_INFO_QUERY_CNF_STRU *)pMsg;
    usLength      = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCopnInfo->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopnInfoQueryCnf:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaCopnInfoQueryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_COPN_QRY */
    if (AT_CMD_COPN_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ����+COPS��^MMPLMNINFO����� */
    pstPlmnName = (TAF_PH_OPERATOR_NAME_STRU *)pstCopnInfo->aucContent;

    for (ulLoop = 0; ulLoop < pstCopnInfo->usPlmnNum; ulLoop++)
    {
        /*  +COPN: <operator in numeric format><operator in long alphanumeric format>     */
        /* ��������� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: ",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        /* ������ָ�ʽ��Ӫ������ */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "\"%X%X%X",
                                           (TAF_MMA_PLMN_MCC_DIGIT3_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT3_OFFSET,
                                           (TAF_MMA_PLMN_MCC_DIGIT2_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT2_OFFSET,
                                           (TAF_MMA_PLMN_MCC_DIGIT1_MASK & pstPlmnName->PlmnId.Mcc) >> TAF_MMA_PLMN_MCC_DIGIT1_OFFSET);

        if (TAF_MMA_PLMN_MNC_DIGIT3_MASK != (TAF_MMA_PLMN_MNC_DIGIT3_MASK & pstPlmnName->PlmnId.Mnc))
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               "%X",
                                               (TAF_MMA_PLMN_MNC_DIGIT3_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT3_OFFSET);

        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%X%X\"",
                                           (TAF_MMA_PLMN_MNC_DIGIT2_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT2_OFFSET,
                                           (TAF_MMA_PLMN_MNC_DIGIT1_MASK & pstPlmnName->PlmnId.Mnc) >> TAF_MMA_PLMN_MNC_DIGIT1_OFFSET);

        /* ��Ӷ��ŷָ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           ",\"");

        /* �����Ӫ�̳��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s",
                                           pstPlmnName->aucOperatorNameLong);

        /* ������� */
        /* ��Ӷ��ŷָ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"%s",
                                           gaucAtCrLf);

        At_BufferorSendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

        usLength = 0;

        pstPlmnName++;

    }

    /*
    ATģ�����MMA�ϱ�����Ӫ�̸�����ȷ����Ӫ����Ϣ�Ƿ��ռ����: С���������Ӫ��
    ��������Ϊ��Ӫ����Ϣ�Ѿ��ռ���ɣ�ԭ����������:
    ATģ��ÿ������50����Ӫ����Ϣ����ʼλ��Ϊ�Ѿ���������һ����Ӫ�̵���һ����Ӫ����Ϣ����
    ������������Ӫ����Ϣ��������50������ʵ�ʵ������
    �����Ӫ����Ϊ50�ı�������AT���ٷ�һ����Ӫ����Ϣ����MMA�ظ�����Ӫ����Ϣ����Ϊ0
    */
    if (pstCopnInfo->usPlmnNum < TAF_MMA_COPN_PLMN_MAX_NUM)
    {
        /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
        AT_STOP_TIMER_CMD_READY(ucIndex);
        gstAtSendData.usBufLen = 0;
        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        stCopnInfo.usFromIndex  = pstCopnInfo->usFromIndex + pstCopnInfo->usPlmnNum;
        stCopnInfo.usPlmnNum    = TAF_MMA_COPN_PLMN_MAX_NUM;

        ulRet                   = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                                        0,
                                                        TAF_MSG_MMA_COPN_INFO_QUERY_REQ,
                                                        &stCopnInfo,
                                                        sizeof(stCopnInfo),
                                                        I0_WUEPS_PID_MMA);
        if (TAF_SUCCESS != ulRet)
        {
            /* ʹ��AT_STOP_TIMER_CMD_READY�ָ�AT����ʵ��״̬ΪREADY״̬ */
            AT_STOP_TIMER_CMD_READY(ucIndex);
            gstAtSendData.usBufLen = 0;
            At_FormatResultData(ucIndex, AT_ERROR);
        }
    }
    return VOS_OK;
}

/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */


VOS_UINT32 AT_RcvMtaSetNCellMonitorCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                 *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;

    /* ��ʼ�� */
    pstRcvMsg    = (AT_MTA_MSG_STRU *)pstMsg;
    pstSetCnf    = (MTA_AT_RESULT_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult     = AT_OK;
    ucIndex      = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_NCELL_MONITOR_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaSetNCellMonitorCnf : Current Option is not AT_CMD_NCELL_MONITOR_SET.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ������� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;

}


VOS_UINT32 AT_RcvMtaQryNCellMonitorCnf(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg      = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_QRY_CNF_STRU      *pstMtaAtQryCnf = VOS_NULL_PTR;
    VOS_UINT32                              ulResult;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;

    /* ��ʼ�� */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtQryCnf      = (MTA_AT_NCELL_MONITOR_QRY_CNF_STRU *)pstRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;
    usLength            = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_NCELL_MONITOR_READ != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaQryNCellMonitorCnf : Current Option is not AT_CMD_NCELL_MONITOR_READ.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^NCELLMONITOR��ѯ����� */
    gstAtSendData.usBufLen = 0;

    if (MTA_AT_RESULT_NO_ERROR != pstMtaAtQryCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        /* ��ѯʱ������Ҫ�ϱ�����״̬ */
        usLength        += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                                  (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                  "%s: %d,%d",
                                                  g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                  pstMtaAtQryCnf->ucSwitch,
                                                  pstMtaAtQryCnf->ucNcellState);

    }

    gstAtSendData.usBufLen = usLength;

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaNCellMonitorInd(VOS_VOID *pstMsg)
{
    AT_MTA_MSG_STRU                        *pstRcvMsg      = VOS_NULL_PTR;
    MTA_AT_NCELL_MONITOR_IND_STRU          *pstMtaAtInd    = VOS_NULL_PTR;
    VOS_UINT8                               ucIndex;
    VOS_UINT16                              usLength;

    /* ��ʼ�� */
    pstRcvMsg           = (AT_MTA_MSG_STRU *)pstMsg;
    pstMtaAtInd         = (MTA_AT_NCELL_MONITOR_IND_STRU *)pstRcvMsg->aucContent;
    ucIndex             = 0;
    usLength            = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaNCellMonitorInd : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s^NCELLMONITOR: %d%s",
                                       gaucAtCrLf,
                                       pstMtaAtInd->ucNcellState,
                                       gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, usLength);

    return VOS_OK;
}



VOS_UINT32 AT_RcvMmaSimInsertRsp(VOS_VOID *pMsg)
{
    TAF_MMA_SIM_INSERT_RSP_STRU        *pstSimInsertRsp;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstSimInsertRsp = (TAF_MMA_SIM_INSERT_RSP_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstSimInsertRsp->stAtAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSimInsertRsp : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSimInsertRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /*�жϵ�ǰ���������Ƿ�ΪAT_CMD_SIMINSERT_SET */
    if (AT_CMD_SIMINSERT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_OK == pstSimInsertRsp->ulResult)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaRefclkfreqSetCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RESULT_CNF_STRU             *pstRltCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex     = 0;
    pstMtaMsg   = (AT_MTA_MSG_STRU *)pMsg;
    pstRltCnf   = (MTA_AT_RESULT_CNF_STRU *)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_REFCLKFREQ_SET */
    if ( AT_CMD_REFCLKFREQ_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqSetCnf: WARNING:Not AT_CMD_REFCLKFREQ_SET!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstRltCnf->enResult )
    {
        ulResult    = AT_OK;
    }
    else
    {
        ulResult    = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaRefclkfreqQryCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_REFCLKFREQ_QRY_CNF_STRU     *pstRefclkfreqCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU *)pMsg;
    pstRefclkfreqCnf    = (MTA_AT_REFCLKFREQ_QRY_CNF_STRU *)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_REFCLKFREQ_READ */
    if ( AT_CMD_REFCLKFREQ_READ != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqQryCnf: WARNING:Not AT_CMD_REFCLKFREQ_READ!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstRefclkfreqCnf->enResult )
    {
        /* ���GPS�ο�ʱ����Ϣ������汾��Ĭ��Ϊ0 */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: 0,%d,%d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstRefclkfreqCnf->ulFreq,
                                                        pstRefclkfreqCnf->ulPrecision,
                                                        pstRefclkfreqCnf->enStatus);
        ulResult    = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult    = AT_ERROR;
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaRefclkfreqInd(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_REFCLKFREQ_IND_STRU         *pstRefclkfreqInd;

    /* ��ʼ����Ϣ���� */
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstRefclkfreqInd    = (MTA_AT_REFCLKFREQ_IND_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaRefclkfreqInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* ���GPS�ο�ʱ����Ϣ������汾��Ĭ��Ϊ0 */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s%s: 0,%d,%d,%d%s",
                                                    gaucAtCrLf,
                                                    gastAtStringTab[AT_STRING_REFCLKFREQ].pucText,
                                                    pstRefclkfreqInd->ulFreq,
                                                    pstRefclkfreqInd->ulPrecision,
                                                    pstRefclkfreqInd->enStatus,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaHandleDectSetCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_SET_CNF_STRU     *pstSetCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstSetCnf           = (MTA_AT_HANDLEDECT_SET_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_HANDLEDECT_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectSetCnf : Current Option is not AT_CMD_HANDLEDECT_SET.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstSetCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;
    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaHandleDectQryCnf(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pRcvMsg           = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_QRY_CNF_STRU     *pstQryCnf         = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucIndex;

    /* ��ʼ�� */
    pRcvMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstQryCnf           = (MTA_AT_HANDLEDECT_QRY_CNF_STRU *)pRcvMsg->aucContent;
    ulResult            = AT_OK;
    ucIndex             = 0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pRcvMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_HANDLEDECT_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaHandleDectQryCnf : Current Option is not AT_CMD_HANDLEDECT_QRY.");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* ��ʽ��AT^HANDLEDECT?��ѯ����� */
    gstAtSendData.usBufLen = 0;
    if (MTA_AT_RESULT_NO_ERROR != pstQryCnf->enResult)
    {
        ulResult = AT_CME_UNKNOWN;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        (VOS_UINT16)pstQryCnf->usHandle);

    }

    /* ������ */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaPsTransferInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_PS_TRANSFER_IND_STRU        *pstPsTransferInd;

    /* ��ʼ����Ϣ���� */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstPsTransferInd    = (MTA_AT_PS_TRANSFER_IND_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaPsTransferInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^PSTRANSFER: %d%s",
                                                    gaucAtCrLf,
                                                    pstPsTransferInd->ucCause,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaMipiInfoInd(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RF_LCD_MIPICLK_IND_STRU     *pstMipiClkCnf;

    /* ��ʼ����Ϣ���� */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstMipiClkCnf       = (MTA_AT_RF_LCD_MIPICLK_IND_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoInd: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s^MIPICLK: %d%s",
                                                    gaucAtCrLf,
                                                    pstMipiClkCnf->usMipiClk,
                                                    gaucAtCrLf);

    At_SendResultData(ucIndex, pgucAtSndCodeAddr, gstAtSendData.usBufLen);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMtaMipiInfoCnf(
    VOS_VOID                           *pMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_RF_LCD_MIPICLK_CNF_STRU     *pstMipiClkCnf;

    /* ��ʼ����Ϣ���� */
    ucIndex             = 0;
    pstMtaMsg           = (AT_MTA_MSG_STRU*)pMsg;
    pstMipiClkCnf       = (MTA_AT_RF_LCD_MIPICLK_CNF_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaMipiInfoCnf: AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    /* ��ǰAT�Ƿ��ڵȴ�������� */
    if (AT_CMD_MIPI_CLK_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;
    if (VOS_OK != pstMipiClkCnf->usResult)
    {
        ulResult = AT_ERROR;
    }
    else
    {
        ulResult = AT_OK;

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s: %d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstMipiClkCnf->usMipiClk);
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_VOID AT_RcvSwitchCmdModeMsg(VOS_UINT8 ucIndex)
{
    AT_UART_LINE_CTRL_STRU             *pstLineCtrl = VOS_NULL_PTR;

    pstLineCtrl = AT_GetUartLineCtrlInfo();

    /* ����ԭ��(enPortIndex��Ӧ�Ķ˿�):
     * (1) ONLINE-DATAģʽ - �ϱ�OK
     * (2) ����ģʽ        - ����
     */

    /* �˿�������� */
    if (ucIndex >= AT_CLIENT_BUTT)
    {
        return;
    }

    /* ֻ����UART�˿ڼ�⵽���л����� */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return;
    }

    /* Ŀǰֻ֧��PPP��IPģʽ���л�ΪONLINE-COMMANDģʽ */
    if ( (AT_DATA_MODE == gastAtClientTab[ucIndex].Mode)
      && ( (AT_PPP_DATA_MODE == gastAtClientTab[ucIndex].DataMode)
        || (AT_IP_DATA_MODE == gastAtClientTab[ucIndex].DataMode) ) )
    {
        if (AT_UART_DSR_MODE_CONNECT_ON == pstLineCtrl->enDsrMode)
        {
            AT_CtrlDSR(ucIndex, AT_IO_LEVEL_LOW);
        }

        At_SetMode(ucIndex, AT_ONLINE_CMD_MODE, AT_NORMAL_MODE);
        AT_USB_WORK_MODE_PRINT(ucIndex, AT_CMD_MODE, AT_NORMAL_MODE);
        At_FormatResultData(ucIndex, AT_OK);
    }

    return;
}


VOS_UINT32 AT_RcvMtaEcidSetCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    VOS_UINT8                           ucIndex;
    AT_MTA_MSG_STRU                    *pstMtaMsg;
    MTA_AT_ECID_SET_CNF_STRU           *pstEcidSetCnf;
    VOS_UINT32                          ulResult;

    /* ��ʼ����Ϣ���� */
    ucIndex         = 0;
    pstMtaMsg       = (AT_MTA_MSG_STRU*)pMsg;
    pstEcidSetCnf   = (MTA_AT_ECID_SET_CNF_STRU*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if ( AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex) )
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_REFCLKFREQ_READ */
    if ( AT_CMD_ECID_SET != gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:Not AT_CMD_REFCLKFREQ_READ!");
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstEcidSetCnf->enResult )
    {
        /* �����ѯ����ǿ��С����Ϣ */
        /* +ECID=<version>,<rat>,[<cell_description>] */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s=%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstEcidSetCnf->aucCellInfoStr);
        ulResult    = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult    = AT_ERROR;
    }

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}

#if (FEATURE_ON == MBB_WPG_LTXPOWER)

VOS_UINT32 AT_RcvMtaTxPowerQryCnf(VOS_VOID *pMsg)
{
    /* ����ֲ����� */
    VOS_UINT8                   ucIndex;
    AT_MTA_MSG_STRU            *pstMtaMsg = VOS_NULL_PTR;
    MTA_AT_TX_PWR_QRY_CNF      *pstTxPowerQryCnf = VOS_NULL_PTR;
    VOS_UINT32                  ulResult;

    if (VOS_NULL_PTR == pMsg)
    {
        return VOS_ERR;
    }
    /* ��ʼ����Ϣ���� */
    pstMtaMsg = (AT_MTA_MSG_STRU*)pMsg;
    pstTxPowerQryCnf = (MTA_AT_TX_PWR_QRY_CNF*)pstMtaMsg->aucContent;

    /* ͨ��ClientId��ȡucIndex */
    if (AT_FAILURE == At_ClientIdToUserId(pstMtaMsg->stAppCtrl.usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:AT_BROADCAST_INDEX!");
        return VOS_ERR;
    }

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_REFCLKFREQ_READ */
    if (AT_CMD_LTXPOWER_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_WARN_LOG("AT_RcvMtaEcidSetCnf: WARNING:Not AT_CMD_REFCLKFREQ_READ!");
        return VOS_ERR;
    }

    /* ��λAT״̬*/
    AT_STOP_TIMER_CMD_READY(ucIndex);

    /* �жϲ�ѯ�����Ƿ�ɹ� */
    if ( MTA_AT_RESULT_NO_ERROR == pstTxPowerQryCnf->enResult )
    {
        /* �����ѯ�ķ��͹�����Ϣ */
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%d,%d,%d,%d",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        pstTxPowerQryCnf->sPrachPwr,
                                                        pstTxPowerQryCnf->sPucchPwr,
                                                        pstTxPowerQryCnf->sPuschPwr,
                                                        pstTxPowerQryCnf->sSrsPwr);
        ulResult = AT_OK;
    }
    else
    {
        gstAtSendData.usBufLen = 0;
        ulResult = AT_ERROR;
    }

    /* ����At_FormatResultData����������*/
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}
#endif/*end (FEATURE_ON == MBB_WPG_LTXPOWER)*/



VOS_UINT32 AT_RcvMmaSysCfgSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_SYS_CFG_CNF_STRU           *pstCnfMsg;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstCnfMsg = (TAF_MMA_SYS_CFG_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : WARNING:AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : AT_BROADCAST_INDEX.");

        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->usErrorCause);
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaPhoneModeSetCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_PHONE_MODE_SET_CNF_STRU    *pstCnfMsg;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;
    MODEM_ID_ENUM_UINT16                enModemId;
#if(FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucSptLteFlag;
    VOS_UINT8                           ucSptUtralTDDFlag;
#endif

    pstCnfMsg           = (TAF_MMA_PHONE_MODE_SET_CNF_STRU *)pMsg;
    ucIndex             = AT_BROADCAST_CLIENT_INDEX_MODEM_0;
    enModemId           = MODEM_ID_0;
    ulResult            = AT_FAILURE;

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &enModemId))
    {
        AT_ERR_LOG1("AT_RcvMmaPhoneModeSetCnf:Get ModemID From ClientID fail,ClientID=%d", ucIndex);

        return VOS_ERR;
    }

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstCnfMsg->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaSysCfgSetCnf : WARNING:AT INDEX NOT FOUND!");

        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaPhoneModeSetCnf : AT_BROADCAST_INDEX.");

        return VOS_ERR;
    }

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstCnfMsg->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        ulResult = At_ChgTafErrorCode(ucIndex, pstCnfMsg->usErrorCause);       /* �������� */
    }


    if (TAF_PH_MODE_FULL == pstCnfMsg->ucPhMode)
    {
        IMM_MntnAcpuCheckPoolLeak();
    }

    /* Added by c64416 for ^PSTANDBY low power proc, 2013-9-13, Begin */
    /* V7R2 ^PSTANDBY����ùػ��������� */
#ifdef FEATURE_UPGRADE_TL
    if(AT_CMD_PSTANDBY_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        AT_STOP_TIMER_CMD_READY(ucIndex);

        return VOS_OK;
    }
#endif
    /* Added by c64416 for ^PSTANDBY low power proc, 2013-9-13, End */

#if((FEATURE_ON == FEATURE_LTE) || (FEATURE_ON == FEATURE_UE_MODE_TDS))
    /* ���GU��������ȷ�����͵�TL�Ⲣ�ȴ���� */
    if (ulResult == AT_OK)
    {
        ucSptLteFlag        = AT_IsModemSupportRat(enModemId, TAF_PH_RAT_LTE);
        ucSptUtralTDDFlag   = AT_IsModemSupportUtralTDDRat(enModemId);

        if ((VOS_TRUE       == ucSptLteFlag)
         || (VOS_TRUE       == ucSptUtralTDDFlag))
        {
            if ((AT_CMD_TMODE_SET == gastAtClientTab[ucIndex].CmdCurrentOpt)
             || (AT_CMD_SET_TMODE == gastAtClientTab[ucIndex].CmdCurrentOpt))
            {
                AT_ProcOperModeWhenLteOn(ucIndex);
                return VOS_OK;
            }
        }
    }
#endif

    AT_STOP_TIMER_CMD_READY(ucIndex);

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}


VOS_UINT32 AT_RcvMmaDetachCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MMA_DETACH_CNF_STRU            *pstDetachCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    pstDetachCnf = (TAF_MMA_DETACH_CNF_STRU *)pMsg;

    ucIndex = AT_BROADCAST_CLIENT_INDEX_MODEM_0;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDetachCnf->usClientId, &ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDetachCnf : WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvMmaDetachCnf : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }

    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == pstDetachCnf->enRslt)
    {
        ulResult = AT_OK;
    }
    else
    {
        gastAtClientTab[ucIndex].ulCause = pstDetachCnf->usErrorCause;
        ulResult = AT_ERROR;
    }

    gstAtSendData.usBufLen = 0;

    /* ����At_FormatResultData���������� */
    At_FormatResultData(ucIndex, ulResult);

    return VOS_OK;
}




#if(FEATURE_ON == MBB_COMMON)

VOS_UINT32 AT_RcvDrvAgentSimQryCnf(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg          = VOS_NULL_PTR;
   
    DRV_AGENT_SIM_QRY_CNF_STRU         *stSimStaQryCnf   = VOS_NULL_PTR; /*lint !e63*/

    VOS_UINT8                           ucIndex          = 0;
    /* ��ʼ����Ϣ */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg; /*lint !e611 */
    stSimStaQryCnf           = (DRV_AGENT_SIM_QRY_CNF_STRU *)pRcvMsg->aucContent ; /*lint !e63 !e10 !e26*/
    if (AT_FAILURE == At_ClientIdToUserId(stSimStaQryCnf->stAtAppCtrl.usClientId,&ucIndex)) /*lint !e10 */
    {
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_PRODTYPE_QRY */
    if (AT_CMD_SIM_QRY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex); /*lint !e71 !e522*/

    /*�����ǵķ��ؽ�����ظ�������*/ 
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, /*lint !e71*/
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d", /*lint !e64*/
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stSimStaQryCnf->simStatus); /*lint !e10*/


    
     /* ������ */
    At_FormatResultData(ucIndex, AT_OK);

    return VOS_OK;
  
}

VOS_UINT32 AT_RcvDrvAgentVerifyDatalockRsp(VOS_VOID *pMsg)
{
    DRV_AGENT_MSG_STRU                 *pRcvMsg;
    DRV_AGENT_DATALOCK_SET_CNF_STRU    *pstDatalockSetCnf;
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulResult;

    /* ��ʼ�� */
    pRcvMsg                   = (DRV_AGENT_MSG_STRU *)pMsg;
    pstDatalockSetCnf         = (DRV_AGENT_DATALOCK_SET_CNF_STRU *)pRcvMsg->aucContent;

    /* ͨ��clientid��ȡindex */
    if (AT_FAILURE == At_ClientIdToUserId(pstDatalockSetCnf->stAtAppCtrl.usClientId,&ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentVerifyDatalockRsp:WARNING:AT INDEX NOT FOUND!");
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        AT_WARN_LOG("AT_RcvDrvAgentVerifyDatalockRsp : AT_BROADCAST_INDEX.");
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_DATALOCK_VERIFY */
    if (AT_CMD_DATALOCK_VERIFY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex);

    if (VOS_TRUE != pstDatalockSetCnf->bFail)
    {
        /* datalockУ��ok */
        ulResult           =  AT_OK;
    }
    else
    {
        /*datalockУ��ʧ��*/
        ulResult           =  AT_ERROR;
    }

    /* ����AT_FormAtResultData����������  */
    gstAtSendData.usBufLen = 0;
    At_FormatResultData(ucIndex, ulResult);
    return VOS_OK;
 }
#endif

/*begin add by wanghaijie for simlock 3.0*/
#if (FEATURE_ON == MBB_SIMLOCK_THREE)
VOS_UINT32 DRVAGENT_RcvDrvAgentHWLockSetCnf(VOS_VOID *pMsg)
{
   
    DRV_AGENT_MSG_STRU                 *pRcvMsg          = VOS_NULL_PTR;
   
    DRV_AGENT_HWLOCK_SET_QRY_CNF_STRU         *stHWLockSetCnf   = VOS_NULL_PTR; /*lint !e63*/

    VOS_UINT8                           ucIndex          = 0;
    /* ��ʼ����Ϣ */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg; /*lint !e611 */
    stHWLockSetCnf           = (DRV_AGENT_HWLOCK_SET_QRY_CNF_STRU *)pRcvMsg->aucContent ; /*lint !e63 !e10 !e26*/
    if (AT_FAILURE == At_ClientIdToUserId(stHWLockSetCnf->stAtAppCtrl.usClientId,&ucIndex)) /*lint !e10 */
    {
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_HWLOCK_SET */
    if (AT_CMD_HWLOCK_SET != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex); /*lint !e71 !e522*/

    if(VOS_OK == stHWLockSetCnf->ulRelt)
    {
       /* ������ */
        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    return VOS_OK;
}

VOS_UINT32 DRVAGENT_RcvDrvAgentHWLockQRYCnf(VOS_VOID *pMsg)
{
    
    DRV_AGENT_MSG_STRU                 *pRcvMsg          = VOS_NULL_PTR;
   
    DRV_AGENT_HWLOCK_TEST_QRY_CNF_STRU         *stHWLockQRYCnf   = VOS_NULL_PTR; /*lint !e63*/

    VOS_UINT8                           ucIndex          = 0;
    /* ��ʼ����Ϣ */
    pRcvMsg                  = (DRV_AGENT_MSG_STRU *)pMsg; /*lint !e611 */
    stHWLockQRYCnf           = (DRV_AGENT_HWLOCK_SET_QRY_CNF_STRU *)pRcvMsg->aucContent ; /*lint !e63 !e10 !e26*/
    if (AT_FAILURE == At_ClientIdToUserId(stHWLockQRYCnf->stAtAppCtrl.usClientId,&ucIndex)) /*lint !e10 */
    {
        return VOS_ERR;
    }

    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, begin */
    if (AT_IS_BROADCAST_CLIENT_INDEX(ucIndex))
    {
        return VOS_ERR;
    }
    /* Added by ��ӳ��/f62575 for �Զ�Ӧ��������±�����������, 2011/11/28, end */

    /* �жϵ�ǰ���������Ƿ�ΪAT_CMD_HWLOCK_QURY */
    if (AT_CMD_HWLOCK_QURY != gastAtClientTab[ucIndex].CmdCurrentOpt)
    {
        return VOS_ERR;
    }

    /* ��λAT״̬ */
    AT_STOP_TIMER_CMD_READY(ucIndex); /*lint !e71 !e522*/

    if(VOS_OK == stHWLockQRYCnf->ulRelt)
    {
        /* ������ */
        At_FormatResultData(ucIndex, AT_OK);
    }
    else
    {
        At_FormatResultData(ucIndex, AT_ERROR);
    }
    return VOS_OK;

}
#endif
/*end   add by wanghaijie for simlock 3.0*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

