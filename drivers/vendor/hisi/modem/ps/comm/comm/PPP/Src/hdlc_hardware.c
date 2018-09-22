



/******************************************************************************
   ͷ�ļ�����
******************************************************************************/
#include "hdlc_hardware.h"
#include "TTFComm.h"
#include "soc_sctrl_interface.h"
#include "soc_baseaddr_interface.h"
#include "ppp_public.h"


#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#if(FEATURE_ON == FEATURE_PPP)
#ifdef FEATURE_HDLC_MASTER
/*****************************************************************************
   1 Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_HDLC_HARDWARE_C
/*lint +e767 */

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/
#if (VOS_OS_VER == VOS_WIN32)
extern VOS_UINT32  VHW_HDLC_Task( VOS_VOID );
extern VOS_UINT8   g_ucScCtrlRegAddr[0xFFC];
#endif

extern PPP_DATA_Q_CTRL_ST     g_PppDataQCtrl;
/*****************************************************************************
   3 ˽�ж���
*****************************************************************************/
VOS_UINT32 PPP_HDLC_HARD_DefIsr(unsigned int ulPara);

VOS_UINT32 PPP_HDLC_HARD_FrmIsr(unsigned int ulPara);


#define  PPP_HDLC_MNTN_TRACE_PARA       (1)
#define  PPP_HDLC_MNTN_TRACE_REG        (2)
#define  PPP_HDLC_MNTN_TRACE_DATA       (4)

/*****************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/
/* ���װ����ķ�����֡��Ϣ */
HDLC_DEF_UNCOMPLETED_INFO_STRU  g_stUncompletedInfo = {0};

/* ������װʹ�õ��ڴ� */
HDLC_DEF_BUFF_INFO_STRU        *g_pstHdlcDefBufInfo = VOS_NULL_PTR;

/* �����װʹ�õ��ڴ� */
HDLC_FRM_BUFF_INFO_STRU        *g_pstHdlcFrmBufInfo = VOS_NULL_PTR;

/* HDLC���������Ϣ */
HDLC_CONFIG_INFO_STRU           g_stHdlcConfigInfo  =
{
    0,
    0,
    0,
    0,
    0,
    HDLC_DEF_INTERRUPT_LIMIT_DEFAULT,
    HDLC_FRM_INTERRUPT_LIMIT_DEFAULT,
    VOS_NULL_PTR,
    0
};

/* ͳ����Ϣ */
PPP_HDLC_HARD_DATA_PROC_STAT_ST g_PppHdlcHardStat   = {0};

/* ������ԭʼ�ж�ʱ��RAW_INT��STATUSֵ */
HDLC_REG_SAVE_INFO_STRU         g_stHdlcRegSaveInfo;

#define    HDLC_IP_BASE_ADDR    (g_stHdlcConfigInfo.ulHDLCIPBaseAddr)

/* ϵͳ����������ַ */
VOS_UINT32  g_ulHdlcScCtrlBaseAddr  = 0;

VOS_UINT32  g_ulPppVirtAddr;
VOS_UINT32  g_ulPppPhyAddr;

/******************************************************************************
   5 ����ʵ��
******************************************************************************/


VOS_VOID PPP_HDLC_HARD_PeriphClkOpen(VOS_VOID)
{
#if (SC_CTRL_MOD_6758_SFT == SC_CTRL_MOD)

    VOS_UINT32      ulValue = 0;

    ulValue |= (1 << HDLC_PERIPH_CLK_BITPOS);

    TTF_WRITE_32REG(SOC_SCTRL_SC_PERIPH_CLKEN0_ADDR(g_ulHdlcScCtrlBaseAddr), ulValue);

#elif (SC_CTRL_MOD_6930_SFT == SC_CTRL_MOD)

    VOS_UINT32      ulValue = 0;

    ulValue |= (1 << HDLC_CRG_CLK_BITPOS);

    TTF_WRITE_32REG(HDLC_CRG_CLKEN4_ADDR(g_ulHdlcScCtrlBaseAddr), ulValue);

#endif

    return;
}


VOS_VOID PPP_HDLC_HARD_PeriphClkClose(VOS_VOID)
{
#if (SC_CTRL_MOD_6758_SFT == SC_CTRL_MOD)

    VOS_UINT32      ulValue = 0;

    ulValue |= (1 << HDLC_PERIPH_CLK_BITPOS);

    TTF_WRITE_32REG(SOC_SCTRL_C_PERIPH_CLKDIS0_ADDR(g_ulHdlcScCtrlBaseAddr), ulValue);

#elif (SC_CTRL_MOD_6930_SFT == SC_CTRL_MOD)

    VOS_UINT32      ulValue = 0;

    ulValue |= (1 << HDLC_CRG_CLK_BITPOS);

    TTF_WRITE_32REG(HDLC_CRG_CLKENDIS4_ADDR(g_ulHdlcScCtrlBaseAddr), ulValue);

#endif

    return;
}


VOS_UINT32 PPP_HDLC_HARD_MntnSetConfig(VOS_UINT32 ulConfig)
{
    g_stHdlcConfigInfo.ulHdlcMntnTraceCfg = ulConfig;

    return g_stHdlcConfigInfo.ulHdlcMntnTraceCfg;
}


VOS_UINT32 PPP_HDLC_HARD_MntnSetDefIntLimit(VOS_UINT32 ulIntLimit)
{
    g_stHdlcConfigInfo.ulHdlcDefIntLimit = ulIntLimit;

    return g_stHdlcConfigInfo.ulHdlcDefIntLimit;
}


VOS_UINT32 PPP_HDLC_HARD_MntnSetFrmIntLimit(VOS_UINT32 ulIntLimit)
{
    g_stHdlcConfigInfo.ulHdlcFrmIntLimit = ulIntLimit;

    return g_stHdlcConfigInfo.ulHdlcFrmIntLimit;
}


VOS_VOID PPP_HDLC_HARD_MntnShowConfigInfo(VOS_VOID)
{
    /* ���IP�����Ϣ */
    PPP_MNTN_LOG3(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                  "HDLC Hardware Info: g_ulHDLCIPBaseAddr 0x%x g_slHdlcISRDef %d g_slHdlcISRFrm %d\r\n",
                  HDLC_IP_BASE_ADDR, g_stHdlcConfigInfo.slHdlcISRDef, g_stHdlcConfigInfo.slHdlcISRFrm);
    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                  "HDLC Hardware Info: g_ulHdlcDefMasterSem 0x%x g_ulHdlcFrmMasterSem 0x%x\r\n",
                  g_stHdlcConfigInfo.ulHdlcDefMasterSem, g_stHdlcConfigInfo.ulHdlcFrmMasterSem);

    /* ����ڴ������Ϣ */
    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                  "HDLC Memory Info: g_pstHdlcDefBufInfo 0x%x TTF_HDLC_MASTER_DEF_BUF_LEN %d\r\n",
                  g_pstHdlcDefBufInfo, TTF_HDLC_MASTER_DEF_BUF_LEN);
    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                  "HDLC Memory Info: g_pstHdlcFrmBufInfo 0x%x TTF_HDLC_MASTER_FRM_BUF_LEN %d\r\n",
                  g_pstHdlcFrmBufInfo, TTF_HDLC_MASTER_FRM_BUF_LEN);

    return;
}


VOS_VOID PPP_HDLC_HARD_MntnShowStatInfo(VOS_VOID)
{
    vos_printf("\n================HDLC Hardware STAT INFO Begin==========================\n");

    vos_printf("���װ����IP���Ͱ�����            = %d\n", g_PppHdlcHardStat.ulDefIpDataProcCnt);
    vos_printf("���װ����PPP���Ͱ�����           = %d\n", g_PppHdlcHardStat.ulDefPppDataProcCnt);
    vos_printf("���װ���������֡����            = %d\n", g_PppHdlcHardStat.ulDefUncompleteCnt);
    vos_printf("���װ�ȴ��жϴ���                = %d\n", g_PppHdlcHardStat.ulDefWaitIntCnt);
    vos_printf("���װ��ѯ����                    = %d\n", g_PppHdlcHardStat.ulDefWaitQueryCnt);
    vos_printf("���װ�жϴ���                    = %d\n", g_PppHdlcHardStat.ulDefIsrCnt);
    vos_printf("���װLCP֡��ͣ����               = %d\n", g_PppHdlcHardStat.ulDefLcpPauseCnt);
    vos_printf("���װ�ռ�����ͣ����              = %d\n", g_PppHdlcHardStat.ulDefFullPauseCnt);
    vos_printf("���װ�����������ݰ�����          = %d\n", g_PppHdlcHardStat.ulDefInputDiscardCnt);

    vos_printf("��װ����IP���Ͱ�����              = %d\n", g_PppHdlcHardStat.ulFrmIpDataProcCnt);
    vos_printf("��װ����PPP���Ͱ�����             = %d\n", g_PppHdlcHardStat.ulFrmPppDataProcCnt);
    vos_printf("��װ�ȴ��жϴ���                  = %d\n", g_PppHdlcHardStat.ulFrmWaitIntCnt);
    vos_printf("��װ��ѯ����                      = %d\n", g_PppHdlcHardStat.ulFrmWaitQueryCnt);
    vos_printf("��װ�жϴ���                      = %d\n", g_PppHdlcHardStat.ulFrmIsrCnt);
    vos_printf("��װ����Ŀ�Ŀռ��ڴ�ʧ�ܴ���      = %d\n", g_PppHdlcHardStat.ulFrmAllocOutputMemFailCnt);
    vos_printf("��װ�����һ��Ŀ�Ŀռ��ڴ�ʧ�ܴ���= %d\n", g_PppHdlcHardStat.ulFrmAllocFirstMemFailCnt);
    vos_printf("��װ�����������������            = %d\n", g_PppHdlcHardStat.ulFrmOutputLinkFullCnt);
    vos_printf("��װ�����������ݰ�����            = %d\n", g_PppHdlcHardStat.ulFrmInputDiscardCnt);

    vos_printf("���װ�����������ڵ���          = %d\n", g_PppHdlcHardStat.ulDefMaxInputCntOnce);
    vos_printf("���װ������������ܳ���          = %d\n", g_PppHdlcHardStat.ulDefMaxInputSizeOnce);
    vos_printf("���װ�����Ч֡������          = %d\n", g_PppHdlcHardStat.ulDefMaxValidCntOnce);
    vos_printf("���װ��ѯ������                = %d\n", g_PppHdlcHardStat.ulDefMaxQueryCnt);

    vos_printf("��װ�����������ڵ���            = %d\n", g_PppHdlcHardStat.ulFrmMaxInputCntOnce);
    vos_printf("��װ������������ܳ���            = %d\n", g_PppHdlcHardStat.ulFrmMaxInputSizeOnce);
    vos_printf("��װ���ʹ�����ڵ����          = %d\n", g_PppHdlcHardStat.ulFrmMaxOutputCntOnce);
    vos_printf("��װ���ʹ�����ڵ��ܳ���        = %d\n", g_PppHdlcHardStat.ulFrmMaxOutputCntOnce);
    vos_printf("��װ��ѯ������                  = %d\n", g_PppHdlcHardStat.ulFrmMaxQueryCnt);

    vos_printf("���δ������ڵ���                = %d\n", g_PppHdlcHardStat.ulMaxCntOnce);
    vos_printf("�����ܽڵ���                      = %d\n", g_PppHdlcHardStat.ulHdlcHardProcCnt);
    vos_printf("continue����                      = %d\n", g_PppHdlcHardStat.ulContinueCnt);
    vos_printf("usDefExpInfo��ʶ                  = %d\n", g_PppHdlcHardStat.usDefExpInfo);
    vos_printf("usFrmExpInfo��ʶ                  = %d\n", g_PppHdlcHardStat.usFrmExpInfo);

    vos_printf("���HDLC BUG���������ݴ���        = %d\n", g_PppHdlcHardStat.ulForbidHdlcBugNoCpy);
    vos_printf("���HDLC BUG�������ݴ���          = %d\n", g_PppHdlcHardStat.ulForbidHdlcBugCpy);


    vos_printf("================HDLC Hardware STAT INFO End==========================\n");

    return;
}


VOS_VOID PPP_HDLC_HARD_MntnTraceMsg
(
    HDLC_MNTN_TRACE_HEAD_STRU          *pstHead,
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulMsgname,
    VOS_UINT32                          ulDataLen
)
{
    pstHead->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstHead->ulReceiverPid   = PS_PID_APP_PPP;
    pstHead->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstHead->ulSenderPid     = PS_PID_APP_PPP;
    pstHead->ulLength        = ulDataLen - VOS_MSG_HEAD_LENGTH;

    pstHead->ulMsgname       = ulMsgname;

    PPP_MNTN_TRACE_MSG(pstHead);

    return;
}


VOS_VOID PPP_HDLC_HARD_MntnTraceSingleData
(
    VOS_UINT16                          usDataLen,
    VOS_UINT8                          *pucDataAddr,
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulEventType,
    VOS_UINT32                          ulNodeIndex
)
{
    VOS_UINT32                          ulDataLen;
    HDLC_MNTN_NODE_DATA_STRU           *pstNodeData;
    VOS_UINT32                          ulAllocDataLen;


    ulAllocDataLen = TTF_MIN(usDataLen, HDLC_MNTN_ALLOC_MEM_MAX_SIZE);

    /* ��Ϣ���ȵ�����Ϣ�ṹ��С���������ݳ��� */
    ulDataLen   = ulAllocDataLen + sizeof(HDLC_MNTN_NODE_DATA_STRU);

    pstNodeData = (HDLC_MNTN_NODE_DATA_STRU *)PS_MEM_ALLOC(PS_PID_APP_PPP, ulDataLen);

    if (VOS_NULL_PTR == pstNodeData)
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                      "PPP_HDLC_HARD_MntnTraceSingleData, NORMAL, Alloc mem failed, ulEventType %d!\r\n",
                      ulEventType);
        return;
    }

    /* ���ڱ�ʶ����һ�����������еĵڼ���IP�� */
    pstNodeData->usNodeIndex = (VOS_UINT16)ulNodeIndex;
    pstNodeData->usLen       = usDataLen;

    PPP_MemSingleCopy((VOS_UINT8 *)(pstNodeData + 1), pucDataAddr, ulAllocDataLen);

    PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstNodeData,
                               ulEventType, ulDataLen);

    PS_MEM_FREE(PS_PID_APP_PPP, pstNodeData);

    return;
}


VOS_VOID PPP_HDLC_HARD_MntnTraceInputParaLink
(
    HDLC_MNTN_EVENT_TYPE_ENUM_UINT32    ulEventType,
    VOS_UINT32                          ulLinkNodeCnt,
    VOS_UINT32                          ulLinkTotalSize,
    HDLC_PARA_LINK_NODE_STRU           *pastLinkNodeBuf
)
{
    HDLC_MNTN_INPUT_PARA_LINK_STRU      stInputPara;
    HDLC_MNTN_INPUT_PARA_LINK_STRU     *pstInputPara = &stInputPara;
    VOS_UINT32                          ulDataLen;


    ulDataLen = sizeof(HDLC_MNTN_INPUT_PARA_LINK_STRU);

    /* ��¼���ϱ������������нڵ����Ϣ*/
    pstInputPara->ulInputLinkNodeCnt   = ulLinkNodeCnt;
    pstInputPara->ulInputLinkTotalSize = ulLinkTotalSize;

    /* ��������ÿ���ڵ������ */
    VOS_MemCpy((VOS_UINT8 *)(&pstInputPara->astInputParaLinkNodeBuf[0]),
               (VOS_UINT8 *)(pastLinkNodeBuf),
               ulLinkNodeCnt * sizeof(HDLC_PARA_LINK_NODE_STRU));

    PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstInputPara,
                               ulEventType, ulDataLen);

    return;
}


VOS_VOID PPP_HDLC_HARD_MntnDefTraceInput
(
    HDLC_DEF_BUFF_INFO_STRU         *pstDefBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;


    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        PPP_HDLC_HARD_MntnTraceInputParaLink(ID_HDLC_MNTN_DEF_INPUT_PARA,
                                             pstBuildInfo->ulInputLinkNodeCnt,
                                             pstBuildInfo->ulInputLinkTotalSize,
                                             &(pstDefBuffInfo->astInputParaLinkNodeBuf[0]));
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        /* ��¼���ϱ������������нڵ���������ݣ�ÿ���ڵ���һ��IP�� */
        for ( ulNodeLoop = 0; ulNodeLoop < pstBuildInfo->ulInputLinkNodeCnt; ulNodeLoop++ )
        {
            pstParaNode = &(pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)),
                                              ID_HDLC_MNTN_DEF_INPUT_DATA, ulNodeLoop);

#if ((FEATURE_OFF == FEATURE_SKB_EXP) || (FEATURE_ON == FEATURE_TTFMEM_CACHE))
            /* ��Ҫ������д��DDR��HDLC��DDR�ж����� */
            PPP_HDLC_CACHE_FLUSH((VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)), pstParaNode->usDataLen);
#endif
        }
    }

    return;
}


VOS_VOID PPP_HDLC_HARD_MntnDefTraceRegConfig
(
    VOS_UINT32      ulEnable,
    VOS_UINT32      ulValue,
    VOS_UINT32      ulEnableInterrupt
)
{
    HDLC_MNTN_DEF_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_DEF_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;
    VOS_UINT32                              ulDataLen;

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_REG) != 0)
    {
        ulDataLen    = sizeof(HDLC_MNTN_DEF_REG_CONFIG_STRU);

        /* ����ȫ���Ĵ������� */
        pstRegConfig->ulStateSwRst             = TTF_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulPriorTimeoutCtrl       = TTF_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulRdErrCurrAddr          = TTF_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulWrErrCurrAddr          = TTF_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefEn              = TTF_READ_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefRawInt          = TTF_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefIntStatus       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefIntClr          = TTF_READ_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefCfg             = TTF_READ_32REG(SOC_ARM_HDLC_DEF_CFG_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletedLen      = TTF_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletedPro      = TTF_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletedAddr     = TTF_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompleteStAgo     = TTF_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefGoOn            = TTF_READ_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefStatus          = TTF_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefUncompletStNow      = TTF_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInLliAddr           = TTF_READ_32REG(SOC_ARM_HDLC_DEF_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInPktAddr           = TTF_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInPktLen            = TTF_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInPktLenMax         = TTF_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefOutSpcAddr          = TTF_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefOutSpaceDep         = TTF_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefRptAddr             = TTF_READ_32REG(SOC_ARM_HDLC_DEF_RPT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefRptDep              = TTF_READ_32REG(SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor0       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor1       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor2       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcDefErrInfor3       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInfoFr1CntAgo       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulDefInfoFr1CntNow       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(HDLC_IP_BASE_ADDR));

        /* ʹ��ǰ������ʹ�ܼĴ�����û�����ã���Ϊ����֮��HDLC�Ὺʼ��������ı������Ĵ�����ֵ */
        if( VOS_FALSE == ulEnable)
        {
            pstRegConfig->ulHdlcDefEn   = ulValue;
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_DEF_REG_BEFORE_EN, ulDataLen);
        }
        else
        {
            /* ʹ�ܺ󹴰�ʱ����������жϷ�ʽ����RawInt��Statusȡg_stHdlcRegSaveInfo�����ֵ */
            if( VOS_TRUE == ulEnableInterrupt )
            {
                pstRegConfig->ulHdlcDefRawInt   = g_stHdlcRegSaveInfo.ulHdlcDefRawInt;
                pstRegConfig->ulHdlcDefStatus   = g_stHdlcRegSaveInfo.ulHdlcDefStatus;
            }
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_DEF_REG_AFTER_EN, ulDataLen);
        }
    }

    return;
}


VOS_VOID PPP_HDLC_HARD_MntnShowDefReg(VOS_VOID)
{
    HDLC_MNTN_DEF_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_DEF_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;


    /* ����ȫ���Ĵ������� */
    pstRegConfig->ulStateSwRst             = TTF_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulPriorTimeoutCtrl       = TTF_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulRdErrCurrAddr          = TTF_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulWrErrCurrAddr          = TTF_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefEn              = TTF_READ_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefRawInt          = TTF_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefIntStatus       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefIntClr          = TTF_READ_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefCfg             = TTF_READ_32REG(SOC_ARM_HDLC_DEF_CFG_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletedLen      = TTF_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletedPro      = TTF_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletedAddr     = TTF_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompleteStAgo     = TTF_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefGoOn            = TTF_READ_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefStatus          = TTF_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefUncompletStNow      = TTF_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInLliAddr           = TTF_READ_32REG(SOC_ARM_HDLC_DEF_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInPktAddr           = TTF_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInPktLen            = TTF_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInPktLenMax         = TTF_READ_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefOutSpcAddr          = TTF_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefOutSpaceDep         = TTF_READ_32REG(SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefRptAddr             = TTF_READ_32REG(SOC_ARM_HDLC_DEF_RPT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefRptDep              = TTF_READ_32REG(SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor0       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor1       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor2       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcDefErrInfor3       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInfoFr1CntAgo       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulDefInfoFr1CntNow       = TTF_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(HDLC_IP_BASE_ADDR));

    vos_printf("\n================HDLC Hardware ShowDefReg Begin==========================\n");

    vos_printf("ulStateSwRst             = 0x%x\n", pstRegConfig->ulStateSwRst);
    vos_printf("ulPriorTimeoutCtrl       = 0x%x\n", pstRegConfig->ulPriorTimeoutCtrl);
    vos_printf("ulRdErrCurrAddr          = 0x%x\n", pstRegConfig->ulRdErrCurrAddr);
    vos_printf("ulWrErrCurrAddr          = 0x%x\n", pstRegConfig->ulWrErrCurrAddr);
    vos_printf("ulHdlcDefEn              = 0x%x\n", pstRegConfig->ulHdlcDefEn);
    vos_printf("ulHdlcDefRawInt          = 0x%x\n", pstRegConfig->ulHdlcDefRawInt);
    vos_printf("ulHdlcDefIntStatus       = 0x%x\n", pstRegConfig->ulHdlcDefIntStatus);
    vos_printf("ulHdlcDefIntClr          = 0x%x\n", pstRegConfig->ulHdlcDefIntClr);
    vos_printf("ulHdlcDefCfg             = 0x%x\n", pstRegConfig->ulHdlcDefCfg);
    vos_printf("ulDefUncompletedLen      = 0x%x\n", pstRegConfig->ulDefUncompletedLen);
    vos_printf("ulDefUncompletedPro      = 0x%x\n", pstRegConfig->ulDefUncompletedPro);
    vos_printf("ulDefUncompletedAddr     = 0x%x\n", pstRegConfig->ulDefUncompletedAddr);
    vos_printf("ulDefUncompleteStAgo     = 0x%x\n", pstRegConfig->ulDefUncompleteStAgo);
    vos_printf("ulHdlcDefGoOn            = 0x%x\n", pstRegConfig->ulHdlcDefGoOn);
    vos_printf("ulHdlcDefStatus          = 0x%x\n", pstRegConfig->ulHdlcDefStatus);
    vos_printf("ulDefUncompletStNow      = 0x%x\n", pstRegConfig->ulDefUncompletStNow);
    vos_printf("ulDefInLliAddr           = 0x%x\n", pstRegConfig->ulDefInLliAddr);
    vos_printf("ulDefInPktAddr           = 0x%x\n", pstRegConfig->ulDefInPktAddr);
    vos_printf("ulDefInPktLen            = 0x%x\n", pstRegConfig->ulDefInPktLen);
    vos_printf("ulDefInPktLenMax         = 0x%x\n", pstRegConfig->ulDefInPktLenMax);
    vos_printf("ulDefOutSpcAddr          = 0x%x\n", pstRegConfig->ulDefOutSpcAddr);
    vos_printf("ulDefOutSpaceDep         = 0x%x\n", pstRegConfig->ulDefOutSpaceDep);
    vos_printf("ulDefRptAddr             = 0x%x\n", pstRegConfig->ulDefRptAddr);
    vos_printf("ulDefRptDep              = 0x%x\n", pstRegConfig->ulDefRptDep);
    vos_printf("ulHdlcDefErrInfor0       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor0);
    vos_printf("ulHdlcDefErrInfor1       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor1);
    vos_printf("ulHdlcDefErrInfor2       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor2);
    vos_printf("ulHdlcDefErrInfor3       = 0x%x\n", pstRegConfig->ulHdlcDefErrInfor3);
    vos_printf("ulDefInfoFr1CntAgo       = 0x%x\n", pstRegConfig->ulDefInfoFr1CntAgo);
    vos_printf("ulDefInfoFr1CntNow       = 0x%x\n", pstRegConfig->ulDefInfoFr1CntNow);

    vos_printf("\n================HDLC Hardware ShowDefReg End==========================\n");

}


VOS_VOID PPP_HDLC_HARD_MntnDefTraceUncompleteInfo
(
    HDLC_DEF_UNCOMPLETED_INFO_STRU     *pstUncompletedInfo
)
{
    HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU stMntnUncompletedInfo;


    VOS_MemCpy(&stMntnUncompletedInfo.stUncompletedInfo,
               pstUncompletedInfo, sizeof(HDLC_DEF_UNCOMPLETED_INFO_STRU));

    PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)&stMntnUncompletedInfo,
                               ID_HDLC_MNTN_DEF_UNCOMPLETED_INFO,
                               sizeof(HDLC_MNTN_DEF_UNCOMPLETED_INFO_STRU));
    return;
}


VOS_VOID PPP_HDLC_HARD_MntnDefTraceOutput
(
    VOS_UINT16                          usValidFrameNum,
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo
)
{
    HDLC_MNTN_DEF_OUTPUT_PARA_STRU     *pstOutputPara;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNodeLoop;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;
    VOS_UINT16                          usMaxFrameNum;


    /* ���װ�ϱ��ռ��ά�ɲ� */
    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        usMaxFrameNum = (HDLC_MNTN_ALLOC_MEM_MAX_SIZE - sizeof(HDLC_MNTN_DEF_OUTPUT_PARA_STRU)) /
                         sizeof(HDLC_DEF_RPT_NODE_STRU);
        usMaxFrameNum = TTF_MIN(usMaxFrameNum, usValidFrameNum);

        ulDataLen     = sizeof(HDLC_MNTN_DEF_OUTPUT_PARA_STRU) + usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU);
        pstOutputPara = (HDLC_MNTN_DEF_OUTPUT_PARA_STRU *)PS_MEM_ALLOC(PS_PID_APP_PPP, ulDataLen);

        if (VOS_NULL_PTR == pstOutputPara)
        {
            PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                          "PPP_HDLC_HARD_MntnDefTraceOutput, NORMAL, Alloc mem failed ulDataLen %!\r\n",
                          ulDataLen);
            return;
        }

        pstOutputPara->usDefValidNum = usValidFrameNum;
        pstOutputPara->usTraceNum    = usMaxFrameNum;

        VOS_MemCpy((VOS_UINT8 *)(pstOutputPara + 1),
                   (VOS_UINT8 *)(&(pstDefBuffInfo->astRptNodeBuf[0])),
                   usMaxFrameNum * sizeof(HDLC_DEF_RPT_NODE_STRU));

        PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstOutputPara,
                                   ID_HDLC_MNTN_DEF_OUTPUT_PARA, ulDataLen);

        PS_MEM_FREE(PS_PID_APP_PPP, pstOutputPara);
    }

    /* ���װĿ�Ŀռ���ÿ����Ч֡��ά�ɲ� */
    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        for ( ulNodeLoop = 0; ulNodeLoop < usValidFrameNum; ulNodeLoop++ )
        {
            pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstRptNode->usDefOutOneLen, (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstRptNode->pucDefOutOneAddr)),
                                              ID_HDLC_MNTN_DEF_OUTPUT_DATA, ulNodeLoop);
        }
    }

    return;
}


VOS_VOID PPP_HDLC_HARD_MntnFrmTraceInput
(
    HDLC_FRM_BUFF_INFO_STRU         *pstFrmBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;


    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        PPP_HDLC_HARD_MntnTraceInputParaLink(ID_HDLC_MNTN_FRM_INPUT_PARA,
                                             pstBuildInfo->ulInputLinkNodeCnt,
                                             pstBuildInfo->ulInputLinkTotalSize,
                                             &(pstFrmBuffInfo->astInputParaLinkNodeBuf[0]));
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        /* ��¼���ϱ������������нڵ���������ݣ�ÿ���ڵ���һ��IP�� */
        for ( ulNodeLoop = 0; ulNodeLoop < pstBuildInfo->ulInputLinkNodeCnt; ulNodeLoop++ )
        {
            pstParaNode = &(pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)),
                                              ID_HDLC_MNTN_FRM_INPUT_DATA, ulNodeLoop);

#if ((FEATURE_OFF == FEATURE_SKB_EXP) || (FEATURE_ON == FEATURE_TTFMEM_CACHE))
            /* ��Ҫ������д��DDR��HDLC��DDR�ж����� */
            PPP_HDLC_CACHE_FLUSH((VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)), pstParaNode->usDataLen);
#endif
        }
    }

    return;
}


VOS_VOID PPP_HDLC_HARD_MntnFrmTraceRegConfig
(
    VOS_UINT32      ulEnable,
    VOS_UINT32      ulValue,
    VOS_UINT32      ulEnableInterrupt
)
{
    HDLC_MNTN_FRM_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_FRM_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;
    VOS_UINT32                              ulDataLen;

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_REG) != 0)
    {
        ulDataLen    = sizeof(HDLC_MNTN_FRM_REG_CONFIG_STRU);

        /* ����ȫ���Ĵ������� */
        pstRegConfig->ulStateSwRst          = TTF_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulPriorTimeoutCtrl    = TTF_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulRdErrCurrAddr       = TTF_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulWrErrCurrAddr       = TTF_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmEn           = TTF_READ_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmRawInt       = TTF_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmIntStatus    = TTF_READ_32REG(SOC_ARM_HDLC_FRM_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmIntClr       = TTF_READ_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmCfg          = TTF_READ_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmAccm         = TTF_READ_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulHdlcFrmStatus       = TTF_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInLliAddr        = TTF_READ_32REG(SOC_ARM_HDLC_FRM_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInSublliAddr     = TTF_READ_32REG(SOC_ARM_HDLC_FRM_IN_SUBLLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInPktLen         = TTF_READ_32REG(SOC_ARM_HDLC_FRM_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInBlkAddr        = TTF_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmInBlkLen         = TTF_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_LEN_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmOutLliAddr       = TTF_READ_32REG(SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmOutSpaceAddr     = TTF_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmOutSpaceDep      = TTF_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmRptAddr          = TTF_READ_32REG(SOC_ARM_HDLC_FRM_RPT_ADDR(HDLC_IP_BASE_ADDR));
        pstRegConfig->ulFrmRptDep           = TTF_READ_32REG(SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));

        /* ʹ��ǰ������ʹ�ܼĴ�����û�����ã���Ϊ����֮��HDLC�Ὺʼ��������ı������Ĵ�����ֵ */
        if( VOS_FALSE == ulEnable )
        {
            pstRegConfig->ulHdlcFrmEn    = ulValue;
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_FRM_REG_BEFORE_EN, ulDataLen);
        }
        else
        {
            /* ʹ�ܺ󹴰�ʱ����������жϷ�ʽ����RawInt��Statusȡg_stHdlcRegSaveInfo�����ֵ */
            if( VOS_TRUE == ulEnableInterrupt )
            {
                pstRegConfig->ulHdlcFrmRawInt   = g_stHdlcRegSaveInfo.ulHdlcFrmRawInt;
                pstRegConfig->ulHdlcFrmStatus   = g_stHdlcRegSaveInfo.ulHdlcFrmStatus;
            }
            PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstRegConfig,
                                       ID_HDLC_MNTN_FRM_REG_AFTER_EN, ulDataLen);
        }
    }

    return;
}


VOS_VOID PPP_HDLC_HARD_MntnShowFrmReg(VOS_VOID)
{
    HDLC_MNTN_FRM_REG_CONFIG_STRU           stRegConfig;
    HDLC_MNTN_FRM_REG_CONFIG_STRU          *pstRegConfig = &stRegConfig;


    /* ����ȫ���Ĵ������� */
    pstRegConfig->ulStateSwRst          = TTF_READ_32REG(SOC_ARM_HDLC_STATE_SW_RST_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulPriorTimeoutCtrl    = TTF_READ_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulRdErrCurrAddr       = TTF_READ_32REG(SOC_ARM_HDLC_RD_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulWrErrCurrAddr       = TTF_READ_32REG(SOC_ARM_HDLC_WR_ERR_CURR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmEn           = TTF_READ_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmRawInt       = TTF_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmIntStatus    = TTF_READ_32REG(SOC_ARM_HDLC_FRM_INT_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmIntClr       = TTF_READ_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmCfg          = TTF_READ_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmAccm         = TTF_READ_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulHdlcFrmStatus       = TTF_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInLliAddr        = TTF_READ_32REG(SOC_ARM_HDLC_FRM_IN_LLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInSublliAddr     = TTF_READ_32REG(SOC_ARM_HDLC_FRM_IN_SUBLLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInPktLen         = TTF_READ_32REG(SOC_ARM_HDLC_FRM_IN_PKT_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInBlkAddr        = TTF_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmInBlkLen         = TTF_READ_32REG(SOC_ARM_HDLC_FRM_IN_BLK_LEN_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmOutLliAddr       = TTF_READ_32REG(SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmOutSpaceAddr     = TTF_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmOutSpaceDep      = TTF_READ_32REG(SOC_ARM_HDLC_FRM_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmRptAddr          = TTF_READ_32REG(SOC_ARM_HDLC_FRM_RPT_ADDR(HDLC_IP_BASE_ADDR));
    pstRegConfig->ulFrmRptDep           = TTF_READ_32REG(SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR));

    vos_printf("\n================HDLC Hardware ShowFrmReg Begin==========================\n");

    vos_printf("ulStateSwRst                    = 0x%x\n", pstRegConfig->ulStateSwRst);
    vos_printf("ulPriorTimeoutCtrl              = 0x%x\n", pstRegConfig->ulPriorTimeoutCtrl);
    vos_printf("ulRdErrCurrAddr                 = 0x%x\n", pstRegConfig->ulRdErrCurrAddr);
    vos_printf("ulWrErrCurrAddr                 = 0x%x\n", pstRegConfig->ulWrErrCurrAddr);
    vos_printf("ulHdlcFrmEn                     = 0x%x\n", pstRegConfig->ulHdlcFrmEn);
    vos_printf("ulHdlcFrmRawInt                 = 0x%x\n", pstRegConfig->ulHdlcFrmRawInt);
    vos_printf("ulHdlcFrmIntStatus              = 0x%x\n", pstRegConfig->ulHdlcFrmIntStatus);
    vos_printf("ulHdlcFrmIntClr                 = 0x%x\n", pstRegConfig->ulHdlcFrmIntClr);
    vos_printf("ulHdlcFrmCfg                    = 0x%x\n", pstRegConfig->ulHdlcFrmCfg);
    vos_printf("ulHdlcFrmAccm                   = 0x%x\n", pstRegConfig->ulHdlcFrmAccm);
    vos_printf("ulHdlcFrmStatus                 = 0x%x\n", pstRegConfig->ulHdlcFrmStatus);
    vos_printf("ulFrmInLliAddr                  = 0x%x\n", pstRegConfig->ulFrmInLliAddr);
    vos_printf("ulFrmInSublliAddr               = 0x%x\n", pstRegConfig->ulFrmInSublliAddr);
    vos_printf("ulFrmInPktLen                   = 0x%x\n", pstRegConfig->ulFrmInPktLen);
    vos_printf("ulFrmInBlkAddr                  = 0x%x\n", pstRegConfig->ulFrmInBlkAddr);
    vos_printf("ulFrmInBlkLen                   = 0x%x\n", pstRegConfig->ulFrmInBlkLen);
    vos_printf("ulFrmOutLliAddr                 = 0x%x\n", pstRegConfig->ulFrmOutLliAddr);
    vos_printf("ulFrmOutSpaceAddr               = 0x%x\n", pstRegConfig->ulFrmOutSpaceAddr);
    vos_printf("ulFrmOutSpaceDep                = 0x%x\n", pstRegConfig->ulFrmOutSpaceDep);
    vos_printf("ulFrmRptAddr                    = 0x%x\n", pstRegConfig->ulFrmRptAddr);
    vos_printf("ulFrmRptDep                     = 0x%x\n", pstRegConfig->ulFrmRptDep);

    vos_printf("\n================HDLC Hardware ShowFrmReg End==========================\n");

    return;
}



VOS_VOID PPP_HDLC_HARD_MntnFrmTraceOutput
(
    VOS_UINT8                           ucFrmValidNum,
    VOS_UINT16                          usFrmOutSegNum,
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo,
    HDLC_PARA_LINK_BUILD_INFO_STRU     *pstBuildInfo
)
{
    HDLC_MNTN_FRM_OUTPUT_PARA_STRU      stOutputPara;
    HDLC_MNTN_FRM_OUTPUT_PARA_STRU     *pstOutputPara = &stOutputPara;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulNodeLoop;
    HDLC_PARA_LINK_NODE_STRU           *pstParaNode;

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_PARA) != 0)
    {
        ulDataLen     = sizeof(HDLC_MNTN_FRM_OUTPUT_PARA_STRU);

        pstOutputPara->ulOutputLinkNodeCnt   = pstBuildInfo->ulOutputLinkNodeCnt;
        pstOutputPara->ulOutputLinkTotalSize = pstBuildInfo->ulOutputLinkTotalSize;
        pstOutputPara->ucFrmValidNum         = ucFrmValidNum;
        pstOutputPara->usOutputNodeUsedCnt   = usFrmOutSegNum;

        VOS_MemCpy((VOS_UINT8 *)(&(pstOutputPara->astOutputParaLinkNodeBuf[0])),
                   (VOS_UINT8 *)(&(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0])),
                   TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM * sizeof(HDLC_PARA_LINK_NODE_STRU));

        VOS_MemCpy((VOS_UINT8 *)(&(pstOutputPara->astRptNodeBuf[0])),
                   (VOS_UINT8 *)(&(pstFrmBuffInfo->astRptNodeBuf[0])),
                   TTF_HDLC_FRM_RPT_MAX_NUM * sizeof(HDLC_FRM_RPT_NODE_STRU));

        PPP_HDLC_HARD_MntnTraceMsg((HDLC_MNTN_TRACE_HEAD_STRU *)pstOutputPara,
                                        ID_HDLC_MNTN_FRM_OUTPUT_PARA, ulDataLen);
    }

    if ((g_stHdlcConfigInfo.ulHdlcMntnTraceCfg & PPP_HDLC_MNTN_TRACE_DATA) != 0)
    {
        for ( ulNodeLoop = 0; ulNodeLoop < usFrmOutSegNum; ulNodeLoop++ )
        {
            pstParaNode = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeLoop]);

            PPP_HDLC_HARD_MntnTraceSingleData(pstParaNode->usDataLen, (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstParaNode->pucDataAddr)),
                                              ID_HDLC_MNTN_FRM_OUTPUT_DATA, ulNodeLoop);
        }
    }

    return;
}



VOS_UINT32 PPP_HDLC_HARD_InitBuf(VOS_VOID)
{
    BSP_DDR_SECT_QUERY   stQuery;
    BSP_DDR_SECT_INFO    stInfo;
    VOS_UINT32           ulBaseAddr;
    VOS_UINT32           ulHdlcMemBaseAddr;

    stQuery.enSectType = BSP_DDR_SECT_TYPE_TTF;
    DRV_GET_FIX_DDR_ADDR(&stQuery, &stInfo);

    /* A��ʹ�������ַ */
    ulBaseAddr = stInfo.ulSectVirtAddr;

    g_ulPppVirtAddr = stInfo.ulSectVirtAddr;
    g_ulPppPhyAddr  = stInfo.ulSectPhysAddr;

    /* HDLC�ڴ滹û�ж������֣�Ŀǰ��CIPHER�ڴ���� */
    ulHdlcMemBaseAddr = TTF_HDLC_MASTER_START_ADDR(ulBaseAddr);

    /* ����TtfMemoryMap.h��ʼ��HDLC�����ڴ� */
    g_pstHdlcDefBufInfo = (HDLC_DEF_BUFF_INFO_STRU *)ulHdlcMemBaseAddr;
    g_pstHdlcFrmBufInfo = (HDLC_FRM_BUFF_INFO_STRU *)(ulHdlcMemBaseAddr + sizeof(HDLC_DEF_BUFF_INFO_STRU));

    /*lint -e506 -e774*/
    /* TTF_HDLC_MASTER_DEF_BUF_LEN������ṹHDLC_DEF_BUFF_INFO_STRU�Ĵ�Сһ�� */
    if (TTF_HDLC_MASTER_DEF_BUF_LEN != sizeof(HDLC_DEF_BUFF_INFO_STRU))
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                      "PPP_HDLC_HARD_InitBuf, ERROR, TTF_HDLC_MASTER_DEF_BUF_LEN %d sizeof(HDLC_DEF_BUFF_INFO_STRU) %d\r\n",
                      TTF_HDLC_MASTER_DEF_BUF_LEN, sizeof(HDLC_DEF_BUFF_INFO_STRU));
        return VOS_ERR;
    }

    /* TTF_HDLC_MASTER_FRM_BUF_LEN�ձ�����ṹHDLC_FRM_BUFF_INFO_STRU�Ĵ�Сһ�� */
    if (TTF_HDLC_MASTER_FRM_BUF_LEN != sizeof(HDLC_FRM_BUFF_INFO_STRU))
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                      "PPP_HDLC_HARD_InitBuf, ERROR, TTF_HDLC_MASTER_FRM_BUF_LEN %d sizeof(HDLC_FRM_BUFF_INFO_STRU) %d\r\n",
                      TTF_HDLC_MASTER_FRM_BUF_LEN, sizeof(HDLC_FRM_BUFF_INFO_STRU));
        return VOS_ERR;
    }
    /*lint +e506 +e774*/

    return VOS_OK;
}


VOS_UINT32 PPP_HDLC_HARD_Init(VOS_VOID)
{
    VOS_UINT32                          ulBaseAddr;


    /* ��ȡHDLC����ַ */
    ulBaseAddr      = DRV_GET_IP_BASE_ADDR(BSP_IP_TYPE_HDLC);

    HDLC_IP_BASE_ADDR = IO_ADDRESS(ulBaseAddr);

#if (VOS_OS_VER == VOS_WIN32)
    g_ulHdlcScCtrlBaseAddr  = g_ucScCtrlRegAddr;
#else
    ulBaseAddr              = DRV_GET_IP_BASE_ADDR(BSP_IP_TYPE_SYSCTRL);
    g_ulHdlcScCtrlBaseAddr  = IO_ADDRESS(ulBaseAddr);
#endif

    /* �ر�HDLCʱ�� */
    PPP_HDLC_HARD_PeriphClkClose();

    /*��ȡHDLC���װ�жϺ�*/
    g_stHdlcConfigInfo.slHdlcISRDef   = DRV_GET_INT_NO(BSP_INT_TYPE_HDLC_DEF);

    /*��ȡHDLC��װ�жϺ�*/
    g_stHdlcConfigInfo.slHdlcISRFrm   = DRV_GET_INT_NO(BSP_INT_TYPE_HDLC_FRM);

    /* ��ʼ���ڴ� */
    if (VOS_OK != PPP_HDLC_HARD_InitBuf())
    {
        return VOS_ERR;
    }

    if ( VOS_OK != VOS_SmBCreate("HdlcDefMasterSem", 0, VOS_SEMA4_FIFO, &g_stHdlcConfigInfo.ulHdlcDefMasterSem) )
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                     "PPP_HDLC_HARD_Init, ERROR, Create g_ulHdlcDefMasterSem failed!\r\n");
        return VOS_ERR;
    }

    if ( VOS_OK != VOS_SmBCreate("HdlcFrmMasterSem", 0, VOS_SEMA4_FIFO, &g_stHdlcConfigInfo.ulHdlcFrmMasterSem) )
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                     "PPP_HDLC_HARD_Init, ERROR, Create g_ulHdlcFrmMasterSem failed!\r\n");
        return VOS_ERR;
    }

    /* �жϹҽ� */
    if (VOS_OK != DRV_VICINT_CONNECT((VOIDFUNCPTR *)g_stHdlcConfigInfo.slHdlcISRDef, (VOIDFUNCPTR)PPP_HDLC_HARD_DefIsr, 0))
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                      "PPP_HDLC_HARD_Init, ERROR, Connect slHdlcISRDef %d to PPP_HDLC_HARD_DefIsr failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRDef);
        return VOS_ERR;
    }

    /* �ж�ʹ�� */
    if (VOS_OK != DRV_VICINT_ENABLE(g_stHdlcConfigInfo.slHdlcISRDef))
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                      "PPP_HDLC_HARD_Init, ERROR, Enable slHdlcISRDef %d failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRDef);
        return VOS_ERR;
    }

    /* �жϹҽ� */
    if (VOS_OK != DRV_VICINT_CONNECT((VOIDFUNCPTR *)g_stHdlcConfigInfo.slHdlcISRFrm, (VOIDFUNCPTR)PPP_HDLC_HARD_FrmIsr, 0))
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                      "PPP_HDLC_HARD_Init, ERROR, Connect slHdlcISRFrm %d to PPP_HDLC_HARD_FrmIsr failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRFrm);
        return VOS_ERR;
    }

    if (VOS_OK != DRV_VICINT_ENABLE(g_stHdlcConfigInfo.slHdlcISRFrm))
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                      "PPP_HDLC_HARD_Init, ERROR, Enable slHdlcISRFrm %d failed!\r\n",
                      g_stHdlcConfigInfo.slHdlcISRFrm);
        return VOS_ERR;
    }

    return VOS_OK;
}    /* link_HDLCInit */


VOS_VOID PPP_HDLC_HARD_SetUp(PPP_ID usPppId)
{
    HDLC_DEF_UNCOMPLETED_INFO_STRU      *pstUncompletedInfo;


    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId);

    VOS_MemSet(pstUncompletedInfo, 0, sizeof(HDLC_DEF_UNCOMPLETED_INFO_STRU));

    return;
}


VOS_VOID PPP_HDLC_HARD_Disable(VOS_VOID)
{
    /* ���޲�������ΪHDLC�Ż���һ�������װ����װ���ʱ����Ӳ���Զ���frm_en��def_en���㣻
       ��װ����װ���̳���ʱ��Ӳ��Ҳ���Զ����㣬ʹ�ڲ�״̬������IDLE״̬��*/
}


VOS_VOID PPP_HDLC_HARD_CommCfgReg(VOS_VOID)
{
    

    VOS_UINT32                          ulValue = 0x0;


    /* ʹ��AXI����ʱ�жϣ�debugʱʹ�ã�����HDLC���ó�ʱʱ����̣�����������ģʽ�²����� */
/*    SET_BIT_TO_DWORD(ulValue, 8); */

    /* ����AXI����ʱʱ������ֵ��SoC�ṩ�����ұ�֤��ƽ̨���� */
    ulValue |= (HDLC_AXI_REQ_TIMEOUT_VALUE << 16);

    TTF_WRITE_32REG(SOC_ARM_HDLC_PRIROR_TIMEOUT_CTRL_ADDR(HDLC_IP_BASE_ADDR), ulValue);

    return;
}


VOS_VOID PPP_HDLC_HARD_CommReleaseLink
(
    PPP_ZC_STRU     **ppstLinkNode,
    VOS_UINT32        ulRelCnt
)
{
    VOS_UINT32                          ulNodeLoop;


    for ( ulNodeLoop = 0; ulNodeLoop < ulRelCnt; ulNodeLoop++ )
    {
        PPP_MemFree(ppstLinkNode[ulNodeLoop]);

        ppstLinkNode[ulNodeLoop] = VOS_NULL_PTR;
    }

    return;
}


VOS_UINT32 PPP_HDLC_HARD_CommWaitSem
(
    VOS_UINT32          ulHdlcMasterSem,
    VOS_UINT32          ulSemTimeoutLen
)
{
    VOS_UINT32                          ulResult;

    /* �ȴ���װ����װ��� */
    ulResult = VOS_SmP(ulHdlcMasterSem, ulSemTimeoutLen);

    if (VOS_OK != ulResult)
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_HDLC_HARD_CommWaitSem, WARNING, VOS_SmP ulHdlcMasterSem 0x%x failed! ErrorNo = 0x%x\r\n",
                      ulHdlcMasterSem, ulResult);

        g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_SEM_TIMEOUT_IND_BITPOS);
        g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_SEM_TIMEOUT_IND_BITPOS);

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 PPP_HDLC_HARD_DefIsEnabled(VOS_VOID)
{
    VOS_UINT32                          ulValue;


    /* SoC���ڴ�����һ�����������ʱ���Զ���ʹ��λ���� */
    ulValue = TTF_READ_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR));

    if (0x01 == (ulValue & 0x01))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_UINT32 PPP_HDLC_HARD_DefIsr(unsigned int ulPara)
{
    g_stHdlcRegSaveInfo.ulHdlcDefRawInt = TTF_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    g_stHdlcRegSaveInfo.ulHdlcDefStatus = TTF_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));

    /* �յ�һ���жϺ����ԭʼ�ж� */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFF);

    /* �ͷŷ�װ����ź��� */
    VOS_SmV(g_stHdlcConfigInfo.ulHdlcDefMasterSem);

    g_PppHdlcHardStat.ulDefIsrCnt++;

    return IRQ_HANDLED;
}


VOS_UINT32 PPP_HDLC_HARD_DefWaitStatusChange()
{
    /*
    hdlc_def_status  (0x88)
      31 30   24 23   8 7 6  5   4   3   2  1  0
    |---|-------|------|---|---|---|---|---|----|
    |Rsv|  Type |  Num |Rsv|Idx|Ful|Ful|Now|Stat|
    Reserved             [31]    1'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_err_type         [30:24] 7'b0    h/s RO   ��֡�ϱ�ʱ������֡���ͣ���Ӧ��bitλΪ1���������������ʹ���
                                                  bit 30����������6��ת���ַ�0x7D�����һ��Flag��
                                                  bit 29����������5����AC����ѹ��ʱ��Address��ֵ��0xFF��
                                                  bit 28����������4����AC����ѹ��ʱ��Control��ֵ��0x03��
                                                  bit 27����������3����P�������ʱ���յ��Ƿ���Protocol��ֵ��
                                                  bit 26����������2�����װ��֡�ֽ���С��4bites��
                                                  bit 25����������1�����װ��֡�ֽ�������1502bytes��PPP֡��Information�򲻳���1500Bytes������Э���򲻳���1502Bytes����
                                                  bit 24����������0�� CRCУ�����
    def_valid_num        [23:8]  16'b0   h/s RO   ��֡�ϱ�ʱ����Ч֡��Ŀ�������������һ�����ܵķ�����֡��
    Reserved             [7:6]   2'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_error_index      [5]     1'b0    h/s RO   ���װ��������ָʾ
    def_rpt_ful          [4]     1'b0    h/s RO   ���װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ָͣʾ
    def_out_spc_ful      [3]     1'b0    h/s RO   ���װ�ⲿ����洢�ռ������ָͣʾ
    def_uncompleted_now  [2]     1'b0    h/s RO   ����ָʾ��ǰ�����Ƿ��н��������֡��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã�0��û�У�1����
    def_all_pkt_pro_stat [1:0]   2'b0    h/s RO   һ������������״̬��00��δ���һ������������01��δ���һ�������������ѽ��LCP֡��Ӳ��������ͣ״̬��
                                                  10�����һ����������������֡�ϱ���11: ���һ����������������֡�ϱ���
    */
    VOS_UINT32              ulRsltWaitNum;           /* ��ֹӲ���쳣�ı������� */
    volatile VOS_UINT32     ulStatus;                /* ���װ״̬ */

   /* ��ѯhdlc_frm_status (0x28)�ĵ�[0]λ�͵�[1]λ���κ�һ��Ϊ1���߳�ʱ�򷵻� */

    ulRsltWaitNum = 0UL;

    while (ulRsltWaitNum < HDLC_DEF_MAX_WAIT_RESULT_NUM)
    {
        /* ��ѯ״̬�Ĵ���hdlc_def_status (0x88)��0-1��3-5λ���κ�һλ��Ϊ1��ʾ���װģ����ͣ��ֹͣ */
        ulStatus  =   TTF_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));

        if (HDLC_DEF_STATUS_DOING != (ulStatus & HDLC_DEF_STATUS_MASK))
        {
            break;
        }

        ulRsltWaitNum++;
    }

    if ( HDLC_DEF_MAX_WAIT_RESULT_NUM <= ulRsltWaitNum )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_HDLC_HARD_DefWaitStatusChange, WARNING, wait hdlc_def_status timeout %d status 0x%x!\r\n",
                      ulRsltWaitNum, ulStatus);

        g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_WAIT_STATUS_TIMEOUT_IND_BITPOS);

        return VOS_ERR;
    }

    g_PppHdlcHardStat.ulFrmMaxQueryCnt = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxQueryCnt, ulRsltWaitNum);

    return VOS_OK;
}


VOS_UINT32 PPP_HDLC_HARD_DefWaitResult
(
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32                          ulStatus;                /* ���װ״̬ */
    VOS_UINT32                          ulResult;


    if (VOS_TRUE == ulEnableInterrupt)
    {
        /* �ȴ��жϵõ���ͣ�����״̬ */
        ulResult = PPP_HDLC_HARD_CommWaitSem(g_stHdlcConfigInfo.ulHdlcDefMasterSem, HDLC_DEF_MASTER_INT_TIMER_LEN);

        /* �������жϷ�������н��������жϲ�������Statusָʾ�Ƿ�����bit��ԭʼ
           �жϼĴ����������ʴ˴�ȡ������g_stHdlcRegSaveInfo�е�״ֵ̬ */
        ulStatus = g_stHdlcRegSaveInfo.ulHdlcDefStatus;

    }
    else
    {
        /* ��ѯ�õ���ͣ����� */
        ulResult = PPP_HDLC_HARD_DefWaitStatusChange();

        /* ��ѯhdlc_def_status (0x88)��ȡ���װ״̬�����䷵�� */
        ulStatus  =  TTF_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    }

    /* �ϱ��Ĵ�����ά�ɲ� */
    PPP_HDLC_HARD_MntnDefTraceRegConfig(VOS_TRUE, 0, ulEnableInterrupt);

    /* �Ȳ���˵��HDLC���ڹ��� */
    if (VOS_OK != ulResult)
    {
        return HDLC_DEF_STATUS_DOING;
    }

    ulStatus &=  HDLC_DEF_STATUS_MASK;

    return ulStatus;
}


PPP_ZC_STRU * PPP_HDLC_HARD_DefProcRptNode
(
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT32                          usFistSegLen;
    VOS_UINT8                          *pucDefOutOneAddr;


    if ( (0 == pstRptNode->usDefOutOneLen) || (HDLC_DEF_OUT_PER_MAX_CNT < pstRptNode->usDefOutOneLen) )
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_HDLC_HARD_DefProcValidFrames, WARNING, invalid usDefOutOneLen %d\r\n",
                      pstRptNode->usDefOutOneLen);

        return VOS_NULL_PTR;
    }

    pstMem = PPP_MemAlloc(pstRptNode->usDefOutOneLen, PPP_ZC_UL_RESERVE_LEN);

    if (VOS_NULL_PTR == pstMem)
    {
        return VOS_NULL_PTR;
    }

    pucDefOutOneAddr    = (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)pstRptNode->pucDefOutOneAddr);
    /* �жϸ�֡��ʼ�ӳ����Ƿ񳬹�����ռ�β�����������ƻش��� */
    if ((pucDefOutOneAddr + pstRptNode->usDefOutOneLen) >
        HDLC_DEF_OUTPUT_BUF_END_ADDR)
    {
        if (pucDefOutOneAddr <= HDLC_DEF_OUTPUT_BUF_END_ADDR)
        {
            usFistSegLen = (VOS_UINT32)(HDLC_DEF_OUTPUT_BUF_END_ADDR - pucDefOutOneAddr);

            /* ��������ʼ��ַ������ռ�β�������� */
            PPP_MemSingleCopy(PPP_ZC_GET_DATA_PTR(pstMem), pucDefOutOneAddr,
                              usFistSegLen);

            /* ����������ռ��ײ���ʣ������ */
            PPP_MemSingleCopy(PPP_ZC_GET_DATA_PTR(pstMem) + usFistSegLen, HDLC_DEF_OUTPUT_BUF_START_ADDR,
                              pstRptNode->usDefOutOneLen - usFistSegLen);
        }
        else
        {
            PPP_MemFree(pstMem);

            PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                     "\r\nPPP, PPP_HDLC_HARD_DefProcRptNode, ERROR, Error pucDefOutOneAddr.\r\n", pucDefOutOneAddr, HDLC_DEF_OUTPUT_BUF_END_ADDR);

            PPP_HDLC_HARD_MntnShowDefReg();

            return VOS_NULL_PTR;
        }
    }
    else
    {
        PPP_MemSingleCopy(PPP_ZC_GET_DATA_PTR(pstMem), pucDefOutOneAddr,
                          pstRptNode->usDefOutOneLen);
    }

    /* �����㿽�����ݳ��� */
    PPP_ZC_SET_DATA_LEN(pstMem, pstRptNode->usDefOutOneLen);

    return pstMem;
}


VOS_VOID PPP_HDLC_HARD_DefProcValidFrames
(
    VOS_UINT32          ulMode,
        PPP_ID          usPppId,
    struct link        *pstLink
)
{
    VOS_UINT16                          usValidFrameNum;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;
    VOS_UINT32                          ulFrameLoop;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;
    PPP_ZC_STRU                        *pstMem;


    pstDefBuffInfo  = HDLC_DEF_GET_BUF_INFO(usPppId);
    usValidFrameNum = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR), 8, 23);

    /* �ϱ����װ�����ݿ�ά�ɲ�:�ϱ��ռ���Ϣ��������� */
    PPP_HDLC_HARD_MntnDefTraceOutput(usValidFrameNum, pstDefBuffInfo);

    /* ��Ч֡�����ֵ��� */
    if (TTF_HDLC_DEF_RPT_MAX_NUM < usValidFrameNum)
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_HDLC_HARD_DefProcValidFrames, WARNING, usValidFrameNum = %d > TTF_HDLC_DEF_RPT_MAX_NUM = %d",
                      usValidFrameNum, TTF_HDLC_DEF_RPT_MAX_NUM);
        return;
    }

    g_PppHdlcHardStat.ulDefMaxValidCntOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxValidCntOnce, usValidFrameNum);

    /* ��Ŀ�Ŀռ����Ч֡���ݿ������㿽���ڴ棬���ݲ������͵������з����ӿ� */
    for ( ulFrameLoop = 0 ; ulFrameLoop < usValidFrameNum; ulFrameLoop++ )
    {
        pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulFrameLoop]);

        pstMem = PPP_HDLC_HARD_DefProcRptNode(pstRptNode);

        /* ���벻�����ݻ��ϱ���Ϣ���󣬶�������Ч֡ */
        if (VOS_NULL_PTR == pstMem)
        {
            continue;
        }

        if (HDLC_IP_MODE == ulMode)
        {
            PPP_HDLC_ProcIpModeUlData(pstLink, pstMem, pstRptNode->usDefOutOnePro);
        }
        else
        {
            PPP_HDLC_ProcPppModeUlData(usPppId, pstMem);
        }
    }

    return;
}


VOS_VOID PPP_HDLC_HARD_DefProcErrorFrames
(
    struct link        *pstLink
)
{
    VOS_UINT8                           ucErrType;
    VOS_UINT8                           ucMask;
    VOS_UINT32                          ulErrTypeLoop;
    VOS_UINT8                           ucResult;
    HDLC_DEF_ERR_FRAMES_CNT_STRU        stErrCnt;


    /* ��ѯ״̬�Ĵ���hdlc_def_status (0x88)�ĵ�24:30��Ӧ����λΪ1��ʾ��ĳ�ִ���֡�����
       Ϊ0��ʾ��֡��� */
    ucErrType = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR) , 24, 30);

    if (0 == ucErrType)
    {
        return;
    }

    /*lint -e734*/
    /* get fcs error count */
    stErrCnt.usFCSErrCnt        = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get frame too long error count */
    stErrCnt.usLenLongCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_0_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get frame too short error count */
    stErrCnt.usLenShortCnt      = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get error protocol count */
    stErrCnt.usErrProtocolCnt   = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_1_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get error control count */
    stErrCnt.usErrCtrlCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR), 0, 15);

    /* get error address count */
    stErrCnt.usErrAddrCnt       = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_2_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* get error flag position count */
    stErrCnt.usFlagPosErrCnt    = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_DEF_ERR_INFO_3_ADDR(HDLC_IP_BASE_ADDR), 0, 15);
    /*lint +e734*/
    for (ulErrTypeLoop = 0UL; ulErrTypeLoop < HDLC_DEF_MAX_TYPE_CNT; ulErrTypeLoop++)
    {
        ucMask   = SET_BITS_VALUE_TO_BYTE(0x01, ulErrTypeLoop);    /* �������� */
        ucResult = (VOS_UINT8)GET_BITS_FROM_BYTE(ucErrType, ucMask);

        if (0 != ucResult)      /* ���ڴ������ */
        {
            if (0UL == ulErrTypeLoop)   /* ��������0: CRCУ����� */
            {
                pstLink->hdlc.stats.badfcs       += stErrCnt.usFCSErrCnt;
                pstLink->hdlc.lqm.SaveInErrors   += stErrCnt.usFCSErrCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "bad hdlc fcs\r\n");
            }
            else if (1UL == ulErrTypeLoop)    /* ��������1: ���װ��֡�ֽ�������1502bytes */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usLenLongCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "bad hdlc frame length too long\r\n");
            }
            else if (2UL == ulErrTypeLoop)    /* ��������2: ���װ��֡�ֽ���С��4bytes */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usLenShortCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "bad hdlc frame length too short\r\n");
            }
            else if (3UL == ulErrTypeLoop)    /* ��������3: ��P�������ʱ, �յ��Ƿ���Protocol��ֵ(��*******0 *******1��ʽ) */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usErrProtocolCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "bad hdlc frame protocol\r\n");
            }
            else if (4UL == ulErrTypeLoop)    /* ��������4: ��AC����ѹ��ʱ, Control��ֵ��0x03 */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usErrCtrlCnt;
                pstLink->hdlc.stats.badcommand += stErrCnt.usErrCtrlCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "bad hdlc frame control\r\n");
            }
            else if (5UL == ulErrTypeLoop)    /* ��������5: ��AC����ѹ��ʱ, Address��ֵ��0xFF */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usErrAddrCnt;
                pstLink->hdlc.stats.badaddr    += stErrCnt.usErrAddrCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "bad hdlc frame address\r\n");
            }
            else if (6UL == ulErrTypeLoop)    /* ��������6: ת���ַ�0x7D�����һ��Flag�� */
            {
                pstLink->hdlc.lqm.SaveInErrors += stErrCnt.usFlagPosErrCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "bad hdlc frame flag position\r\n");
            }
            else
            {
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "link_HDLCDefDealErr err\r\n");
            }
        }
    }

    return;
}



VOS_VOID PPP_HDLC_HARD_DefCfgGoOnReg
(
    VOS_UINT32          ulDefStatus
)
{
    /*
    hdlc_def_go_on  (0x84)
     31                  17  16  15    9   8  7   1  0
    |----------------------|----|-------|----|-----|----|
    |         Rsv          |Goon|  Rsv  |Goon| Rsv |Goon|
    Reserved             [31:17] 15'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_rpt_ful_goon     [16]    1'b0    h/s WO   �ⲿ���װ��Ч֡��Ϣ�ϱ��ռ������ͣ���
    Reserved             [15:9]  7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_outspc_ful_goon  [8]     1'b0    h/s WO   �ⲿ���װ������ݴ洢�ռ������ͣ״̬���
    Reserved             [7:1]   7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_lcp_goon         [0]     1'b0    h/s WO   ���һ���Ϸ�LCP֡���µ�Ӳ����ͣ״̬����������װģ��δ������һ������װ�����ݣ�<=2KB(def_in_pkt_len_max)�������һ���Ϸ�LCP֡�������ͣ��֡���ȴ��������˼Ĵ���д"1"���ټ�������ʣ������ݡ�
    */

    /* GO_ONǰ����ϴν��װ��ԭʼ�ж� */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFF);

    if (HDLC_DEF_STATUS_PAUSE_RPT_SPACE_FULL == ulDefStatus )
    {
        TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)0x10000);
    }
    else if (HDLC_DEF_STATUS_PAUSE_OUTPUT_SPACE_FULL == ulDefStatus )
    {
        TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)0x100);
    }
    else if (HDLC_DEF_STATUS_PAUSE_LCP == ulDefStatus )
    {
        TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_GO_ON_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)0x1);
    }
    else
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                      "PPP_HDLC_HARD_DefCfgGoOnReg, ERROR, Wrong ulDefStatus %d!\r\n",
                      ulDefStatus);
    }

    /* PC��ʹ��HDLCģ���� */
    #if (VOS_OS_VER == VOS_WIN32)
    VHW_HDLC_Task();
    #endif

    return;
}


VOS_UINT32 PPP_HDLC_HARD_DefCfgReg
(
    VOS_UINT32                      ulMode,
    struct link                    *pstLink,
    HDLC_DEF_UNCOMPLETED_INFO_STRU *pstDefUncompletedInfo
)
{
    /*
        hdlc_def_cfg  (0x70)
         31                           4 3     2   1     0
        |-------------------------------|-------|-----|-----|
        |              Rsv              |  Pfc  | Acfc| ago |
        Reserved             [31:4]  28'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_pfc              [3:2]   2'b0    h/s R/W  P��ѹ��ָʾ��00��P����ѹ��������룻01��P��ѹ��������룻11��P�򲻰��룻��������Ч��
        def_acfc             [1]     1'b0    h/s R/W  AC��ѹ��ָʾ��0��AC����ѹ����1����ʾAC��ѹ����
        def_uncompleted_ago  [0]     1'b0    h/s R/W  ����ָʾ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ���������Ƿ��н��������֡��
                                                      Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã�0��û�У�1����
        */

    VOS_UINT32       ulDeframerCfg;
    VOS_UINT8        ucACComp;
    VOS_UINT8        ucPComp;
    VOS_UINT8        ucLowByte;
    VOS_UINT16       usLowWord;

    /* 1.����ulMode��P���AC���Ƿ�ѹ������hdlc_def_cfg (0x70) */

    /* ��ȡAC��ѹ��ָʾ, P��ѹ��ָʾ */
    ucACComp = (1 == pstLink->lcp.want_acfcomp) ? 1 : 0;

    if (HDLC_IP_MODE == ulMode) /* IPģʽ: P�򲻺��� */
    {
        ucPComp = (1 == pstLink->lcp.want_protocomp)
                   ? HDLC_PROTOCOL_REMOVE_WITH_COMPRESS
                   : HDLC_PROTOCOL_REMOVE_WITHOUT_COMPRESS;
    }
    else                        /* PPPģʽ: P����� */
    {
        ucPComp = HDLC_PROTOCOL_NO_REMOVE;
    }

    /* ��ucPComp���õ�һ���ֽڵĵ�2, 3λ�� */
    ucLowByte = SET_BITS_VALUE_TO_BYTE(ucPComp, HDLC_DEF_PFC_BITPOS);

    if (1 == ucACComp)  /* AC��ѹ�� */
    {
        SET_BIT_TO_BYTE(ucLowByte, HDLC_DEF_ACFC_BITPOS);
    }

    /* 2.���÷�����֡�����Ϣ */
    if ( (VOS_NULL_PTR != pstDefUncompletedInfo) &&
        (HDLC_DEF_UNCOMPLETED_EXIST == pstDefUncompletedInfo->ucExistFlag) )
    {
        /* def_uncompleted_ago��1��ʾ���ϴ�����ķ�����֡���뱾�ν��װ */
        SET_BIT_TO_BYTE(ucLowByte, HDLC_DEF_IS_UNCOMPLETED_AGO_BITPOS);

        /*
        def_uncompleted_len  (0x74)
         31                 16  15                  0
        |---------------------|----------------------|
        |         Rsv         |         Len          |
        Reserved             [31:16] 16'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_uncompleted_len  [15:0]  16'b0   h/s R/W  ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡�ĳ��ȣ�Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ�����
        */
        TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_LEN_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->usDefOutOneLen & 0xFFFF);

        /*
        def_uncompleted_pro  (0x78)
         31                 16  15                  0
        |---------------------|----------------------|
        |         Rsv         |         Pro          |
        Reserved             [31:16] 16'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_uncompleted_pro  [15:0]  16'b0   h/s R/W  ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡��
                                                      Э�飬Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��������е�0Byte��1Byte��2Byte��Ч��
        */
        TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_PRO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->usDefOutOnePro & 0xFFFF);

        /*
        def_uncompleted_addr  (0x7C)
         31                  0
        |----------------------|
        |         Addr         |
        def_uncompleted_addr [31:0]  32'b0   h/s R/W  ��Ӧ��ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������װ����������������֡��
                                                      �ⲿ�洢��ʼ��ַ��Ϊ��֧�ֶ��PPP/IP���Ŷ����ӵ����ã��õ�ַ��������ԭ���ϱ���ͬ���µ�ַ��
        */
        TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->pucDefOutOneAddr);

        /*
        def_uncomplet_st_ago  (0x80)
         31                  16 15             5 4     0
        |----------------------|----------------|-------|
        |         Ago          |       Rsv      |  Ago  |
        crc16_result_ago     [31:16] 16'b0   h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ��CRCУ��ֵ
        Reserved             [15:5]  11'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_data_st_curr_ago [4:0]   5'b0    h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ������״̬����ǰ״̬
        */
        TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_AGO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->ulDefStAgo);

        /*
        def_info_frl_cnt_ago  (0xC0)
         31        27 26                 16 15   11 10              0
        |------------|---------------------|-------|-----------------|
        |    Rsv     |         Ago         |  Rsv  |       Ago       |
        Reserved             [31:27] 5'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_framel_cnt_ago   [26:16] 11'b0   h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ��֡����
        Reserved             [15:11] 5'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
        def_info_cnt_ago     [10:0]  11'b0   h/s R/W  �뵱ǰ���װ��������ͬһPPP/IP���ŵ���ǰ������׽��װ��������������������֡ʱ����Ϣ����
        */
        TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_AGO_ADDR(HDLC_IP_BASE_ADDR),
                        (VOS_UINT32)pstDefUncompletedInfo->ulDefInfoFrlCntAgo);
    }

    usLowWord     = HDLC_MAKE_WORD(0x00, ucLowByte);
    ulDeframerCfg = HDLC_MAKE_DWORD(0x00, usLowWord);

    /* �����ý��д��Ĵ��� */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_CFG_ADDR(HDLC_IP_BASE_ADDR),ulDeframerCfg);

    /* ��������������󵥰�����,���HDLC BUG,��󳤶�+1 */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_IN_PKT_LEN_MAX_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)HDLC_DEF_IN_PER_MAX_CNT);

    return VOS_OK;
}


VOS_VOID PPP_HDLC_HARD_DefSaveUncompletedInfo
(
    PPP_ID          usPppId
)
{
    HDLC_DEF_UNCOMPLETED_INFO_STRU     *pstUncompletedInfo;
    VOS_UINT32                          ulStatus;                /* ���װ״̬ */
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;
    VOS_UINT32                          ulValidNum;
    VOS_UINT8                          *pucDefOutOneAddr;
    HDLC_DEF_RPT_NODE_STRU             *pstRptNode;


    pstDefBuffInfo     = HDLC_DEF_GET_BUF_INFO(usPppId);
    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId);

    ulStatus  =   TTF_READ_32REG(SOC_ARM_HDLC_DEF_STATUS_ADDR(HDLC_IP_BASE_ADDR));

    /* ��ѯ״̬�Ĵ���hdlc_def_status (0x88)�ĵ�2λ
       Ϊ1��ʾ���ν��װ�з�����֡�����
       Ϊ0��ʾ�޷�����֡��� */
    if (0 == (ulStatus & 0x4))
    {
        pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_NOT_EXIST;

        return;
    }

    g_PppHdlcHardStat.ulDefUncompleteCnt++;

    /* def_valid_num        [23:8]  16'b0   h/s RO   ��֡�ϱ�ʱ����Ч֡��Ŀ�������������һ�����ܵķ�����֡�� */
    ulValidNum = (ulStatus & 0xFFFF00) >> 8;

    /* ������֡���ϱ���Ϣ����Ч֡���棬���ǲ�������Ч֡��Ŀ�� */
    if (TTF_HDLC_DEF_RPT_MAX_NUM <= ulValidNum)
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                     "PPP_HDLC_HARD_DefSaveUncompletedInfo, ERROR, ulValidNum %d >= TTF_HDLC_DEF_RPT_MAX_NUM %d!\r\n",
                     ulValidNum, TTF_HDLC_DEF_RPT_MAX_NUM);

        pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_NOT_EXIST;

        return;
    }

    /* �з�����֡ʱ��Ҫ��ȡ������def_uncomplet_st_now(0x8C)��def_info_frl_cnt_now(0xC4)
       ��ȡ�������ϱ��ռ���Ч֮֡��ķ�����֡���ȡ�Э������ݵ�ַ */
    pstUncompletedInfo->ucExistFlag = HDLC_DEF_UNCOMPLETED_EXIST;

    pstRptNode = &(pstDefBuffInfo->astRptNodeBuf[ulValidNum]);

    pucDefOutOneAddr = (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)pstRptNode->pucDefOutOneAddr);


    if (pucDefOutOneAddr != HDLC_DEF_OUTPUT_BUF_START_ADDR)
    {
        if ((pucDefOutOneAddr - HDLC_DEF_OUTPUT_BUF_START_ADDR) >= pstRptNode->usDefOutOneLen)
        {
            DRV_RT_MEMCPY(HDLC_DEF_OUTPUT_BUF_START_ADDR, pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        }
        else
        {
            PS_MEM_MOVE(HDLC_DEF_OUTPUT_BUF_START_ADDR, pucDefOutOneAddr, pstRptNode->usDefOutOneLen);
        }
#ifndef PPP_ST_TEST
        pstRptNode->pucDefOutOneAddr = (VOS_UINT8*)PPP_VIRT_TO_PHY((VOS_UINT32)HDLC_DEF_OUTPUT_BUF_START_ADDR);
#endif
    }


    /* ������֡��Э�顢���Ⱥ��ڴ洢�ռ�ĵ�ַ�����ֻ���ݴ���Щ��Ϣ�����½��װ��ʱ����ԭ�����HDLC */
    pstUncompletedInfo->usDefOutOnePro   = pstRptNode->usDefOutOnePro;
    pstUncompletedInfo->usDefOutOneLen   = pstRptNode->usDefOutOneLen;
    pstUncompletedInfo->pucDefOutOneAddr = pstRptNode->pucDefOutOneAddr;

    /* ���ֻ���ݴ���Щ��Ϣ�����½��װ��ʱ����ԭ�����HDLC */
    pstUncompletedInfo->ulDefStAgo         = TTF_READ_32REG(SOC_ARM_HDLC_DEF_UNCOMPLETED_ST_NOW_ADDR(HDLC_IP_BASE_ADDR));
    pstUncompletedInfo->ulDefInfoFrlCntAgo = TTF_READ_32REG(SOC_ARM_HDLC_DEF_INFO_FRL_CNT_NOW_ADDR(HDLC_IP_BASE_ADDR));

    PPP_HDLC_HARD_MntnDefTraceUncompleteInfo(pstUncompletedInfo);

    return;
}


VOS_VOID PPP_HDLC_HARD_DefProcException
(
    VOS_UINT32          ulStatus,
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32                          ulRawInt;


    if( VOS_TRUE == ulEnableInterrupt )
    {
        /* �������жϷ�������н��������жϲ������ʴ˴�ȡ������g_stHdlcRegSaveInfo�е�ԭʼ�жϼĴ���ֵ */
        ulRawInt                        =   g_stHdlcRegSaveInfo.ulHdlcDefRawInt;
        g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_INTERRUPT_IND_BITPOS);
    }
    else
    {
        ulRawInt  =   TTF_READ_32REG(SOC_ARM_HDLC_DEF_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    }

    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                  "PPP_HDLC_HARD_DefProcException, ERROR, Exception ocurr status 0x%x RAW_INT 0x%x\r\n",
                  ulStatus, ulRawInt);
    PPP_HDLC_HARD_MntnShowFrmReg();
    PPP_HDLC_HARD_MntnShowDefReg();

    g_PppHdlcHardStat.usDefExpInfo |=   (1 << HDLC_EXCEPTION_IND_BITPOS);

    /* ���HDLC�����쳣���򵥰��쳣���� */
    DRV_SYSTEM_ERROR(HDLC_DEF_SYSTEM_ERROR_ID, __LINE__, (VOS_INT)g_PppHdlcHardStat.usDefExpInfo,
                         (VOS_CHAR *)&g_stHdlcRegSaveInfo,
                         sizeof(HDLC_REG_SAVE_INFO_STRU));

    return;
}


VOS_VOID PPP_HDLC_HARD_DefWaitAndProc
(
    VOS_UINT32          ulMode,
    VOS_UINT32          ulEnableInterrupt,
    PPP_ID              usPppId,
    struct link        *pstLink
)
{
    VOS_UINT32                          ulDefStatus;
    VOS_UINT32                          ulContinue;

    for (; ;)
    {
        /* ʹ���жϣ���ȴ��жϸ������ͷ��ź�����������ѯ���װ״̬�Ĵ��� */
        ulDefStatus = PPP_HDLC_HARD_DefWaitResult(ulEnableInterrupt);

        switch ( ulDefStatus )
        {
            case HDLC_DEF_STATUS_PAUSE_RPT_SPACE_FULL :
            case HDLC_DEF_STATUS_PAUSE_OUTPUT_SPACE_FULL :
                /* ������Ч֡������GO_ON�Ĵ��� */
                PPP_HDLC_HARD_DefProcValidFrames(ulMode, usPppId, pstLink);
                PPP_HDLC_HARD_DefCfgGoOnReg(ulDefStatus);

                ulContinue = VOS_TRUE;
                g_PppHdlcHardStat.ulDefFullPauseCnt++;
                break;
            case HDLC_DEF_STATUS_PAUSE_LCP :
                /* ������Ч֡��LCP֡���������üĴ���������GO_ON�Ĵ��� */
                PPP_HDLC_HARD_DefProcValidFrames(ulMode, usPppId, pstLink);
                PPP_HDLC_HARD_DefCfgReg(ulMode, pstLink, VOS_NULL_PTR);
                PPP_HDLC_HARD_DefCfgGoOnReg(ulDefStatus);

                ulContinue = VOS_TRUE;
                g_PppHdlcHardStat.ulDefLcpPauseCnt++;
                break;
            case HDLC_DEF_STATUS_DONE_WITHOUT_FRAMES :
                /* ���ݷ�����ָ֡ʾ�����������֡��Ϣ */
                PPP_HDLC_HARD_DefSaveUncompletedInfo(usPppId);

                ulContinue = VOS_FALSE;
                break;
            case HDLC_DEF_STATUS_DONE_WITH_FRAMES :
                /* ������Ч֡������֡��LCP֡(���������һ֡)�����ݷ�����ָ֡ʾ�����������֡��Ϣ */
                PPP_HDLC_HARD_DefProcValidFrames(ulMode, usPppId, pstLink);
                PPP_HDLC_HARD_DefProcErrorFrames(pstLink);
                PPP_HDLC_HARD_DefSaveUncompletedInfo(usPppId);
                ulContinue = VOS_FALSE;
                break;
            case HDLC_DEF_STATUS_DOING :
            default:
                /* ��ӡ�쳣��־������PPP���� */
                PPP_HDLC_HARD_DefProcException(ulDefStatus, ulEnableInterrupt);

                ulContinue = VOS_FALSE;
                break;
        }

        /* ��ͣ״̬��Ҫ������������״̬���װ����˳� */
        if (VOS_TRUE != ulContinue)
        {
            break;
        }
    }

    g_stHdlcRegSaveInfo.ulHdlcDefRawInt = 0xFFFFFFFF;
    g_stHdlcRegSaveInfo.ulHdlcDefStatus = 0xFFFFFFFF;

    return;
}


PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32 PPP_HDLC_HARD_DefCheckPara
(
    PPP_ZC_STRU                 *pstMem,
    VOS_UINT32                   ulDataLen,
    PPP_DATA_TYPE_ENUM_UINT8     ucDataType
)
{
    PPP_DATA_TYPE_ENUM_UINT8     ucCurrDataType;


    /* ��ȡ����װ���ݰ����� */
    ucCurrDataType = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);

    if ( ucDataType != ucCurrDataType )
    {
        return PPP_HDLC_PARA_CHECK_FAIL_KEEP;
    }

    /* ���װ������볤�����ڴ�ģ���������󳤶ȣ�Ŀǰ��1536B */
    /* ���HDLC Bug�ڴ��������1 */
    if ( (0 == ulDataLen) || (HDLC_DEF_IN_PER_MAX_CNT < ulDataLen) )
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                      "PPP_HDLC_HARD_DefCheckPara, NORMAL, invalid data length %d\r\n", ulDataLen);

        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    return PPP_HDLC_PARA_CHECK_PASS;
}



VOS_VOID PPP_HDLC_HARD_ForbiddenHdlcBug(PPP_ZC_STRU **ppstMem)
{
    PPP_ZC_STRU *pstMem;
    PPP_ZC_STRU *pstTmpMem;
    VOS_UINT8   *pstData;
    VOS_UINT16   usLen;
    const VOS_UINT8    ucEndByte = 0x7e;

    pstMem  = *ppstMem;

    if (VOS_NULL_PTR == pstMem)
    {
        return;
    }

    usLen   = PPP_ZC_GET_DATA_LEN(pstMem);
    pstData = PPP_ZC_GET_DATA_PTR(pstMem);

    if (usLen <= 1)
    {
        return;
    }

    if (ucEndByte != pstData[usLen - 2])
    {
        /* �����ڶ����ֽڲ�Ϊ7e���ô��� */
        return;
    }
    else if ((usLen >= 3) && (ucEndByte == pstData[usLen - 3]))
    {
        /* �����������ֽ�Ϊ7e���ô��� */
        return;
    }
    else
    {
        /*
            �����ڶ����ֽ�Ϊ7e,�����������ֽڲ�Ϊ7e�ĳ���
            �����һ���ֽں�����һ���ֽ�,ͬʱ�ڴ�ĳ���+1

            skb������ڴ�ṹ����
           |--------data(uslen)--------|----32bytes align(0~31)-----|--skb_share_info(256)----|
        */
        if (PPP_ZC_GET_RESERVE_ROOM(pstMem) > 0)
        {
            INSERT_BYTE_LAST(pstMem, pstData, usLen, ucEndByte);
            g_PppHdlcHardStat.ulForbidHdlcBugNoCpy++;
        }
        else
        {
            /* ����һ������1�ֽڵ��ڴ� */

            pstTmpMem = PPP_MemAlloc(usLen + 1, 0);
            if (VOS_NULL_PTR != pstTmpMem)
            {
                PPP_MemWriteData(pstTmpMem, pstData, usLen);

                pstData = PPP_ZC_GET_DATA_PTR(pstTmpMem);

                INSERT_BYTE_LAST(pstTmpMem, pstData, usLen, ucEndByte);
                g_PppHdlcHardStat.ulForbidHdlcBugCpy++;
            }

            /* ������������ڴ��Ƿ�Ϊ�ն�����ȥ,�����洦�� */
            *ppstMem = pstTmpMem;

            /* ��ԭ�ڴ��ͷ� */
            PPP_MemFree(pstMem);
        }
    }
}


VOS_UINT32 PPP_HDLC_HARD_DefBuildInputParaLink
(
    HDLC_PARA_LINK_BUILD_PARA_STRU  *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU  *pstBuildInfo
)
{
    VOS_UINT32                              ulLinkLoop;
    PPP_ZC_STRU                            *pstMem;
    PPP_DATA_TYPE_ENUM_UINT8                ucDataType;
    PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32  enCheckResult;
    VOS_UINT16                              usDataLen;
    HDLC_PARA_LINK_NODE_STRU               *pstParaNode;
    VOS_UINT32                              ulNodeIndex;
    HDLC_DEF_BUFF_INFO_STRU                *pstDefBuffInfo;
    HDLC_DEF_UNCOMPLETED_INFO_STRU         *pstUncompletedInfo;
    VOS_UINT32                              ulMaxDataLen1Time = TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE;


    /* ��������Ϣ */
    VOS_MemSet(pstBuildInfo, 0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    pstUncompletedInfo = HDLC_DEF_GET_UNCOMPLETED_INFO(pstBuildPara->usPppId);

    if (HDLC_DEF_UNCOMPLETED_EXIST == pstUncompletedInfo->ucExistFlag)
    {
        ulMaxDataLen1Time = TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_SIZE - pstUncompletedInfo->usDefOutOneLen;
    }


    /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(pstBuildPara->usPppId);
    ucDataType     = pstBuildPara->ucDataType;

    for ( ulLinkLoop = 0 ; ulLinkLoop < TTF_HDLC_DEF_INPUT_PARA_LINK_MAX_NUM; ulLinkLoop++ )
    {
        pstMem     = (PPP_ZC_STRU *)PPP_ZC_PEEK_QUEUE_HEAD(pstBuildPara->pstDataQ);

        /* ��û�е����ڵ��������Ƕ������Ѿ�û������ */
        if( VOS_NULL_PTR == pstMem )
        {
            break;
        }

        usDataLen     = PPP_ZC_GET_DATA_LEN(pstMem);
        enCheckResult = PPP_HDLC_HARD_DefCheckPara(pstMem, usDataLen, ucDataType);

        if( PPP_HDLC_PARA_CHECK_FAIL_DISCARD == enCheckResult )
        {
            pstMem = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);
            PPP_MemFree(pstMem);
            pstBuildInfo->ulDealCnt++;

            g_PppHdlcHardStat.ulDefInputDiscardCnt++;
            continue;
        }

        if( PPP_HDLC_PARA_CHECK_FAIL_KEEP == enCheckResult )
        {
            break;
        }


        /* ��PPP����ȡ��ͷ��㣬������������� pstBuildInfo->apstInputLinkNode */
        pstMem  = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);

        /* ���HDLC BUG,�ڷ���HDLC BUG�����¶�ԭ�����ݽ����滻,
           �����pstMemΪ�滻����ڴ�ָ��,ԭʼ�ڴ�ָ������Ѿ����ͷ�
         */
        PPP_HDLC_HARD_ForbiddenHdlcBug(&pstMem);

        /* �滻�ڴ��ʱ�������ڴ�ʧ��,ֱ�Ӵ�����һ������  */
        if (VOS_NULL_PTR == pstMem)
        {
            continue;
        }

        /* �ڴ���ܷ����滻,����ȡ���� */
        usDataLen = PPP_ZC_GET_DATA_LEN(pstMem);

        /* һ������������д���װ���ݰ��ܳ����ܳ���15KB */
        /* ���HDLC BUG,�������ݱ��޸Ĺ�,����������1�ֽ�,��Ҫ�ŵ������ж� */
        if( pstBuildInfo->ulInputLinkTotalSize + usDataLen  > ulMaxDataLen1Time )
        {
            /* �ڴ�Żض���,�´��ٴ��� */
            PPP_ZC_ENQUEUE_HEAD(pstBuildPara->pstDataQ, pstMem);

            break;
        }

        /* ��ȡ��ǰҪ��ӽڵ���±� */
        ulNodeIndex = pstBuildInfo->ulInputLinkNodeCnt;

        /* ����Ҫ����Ĳ����ڵ� */
        pstParaNode = &(pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex]);

        /* �ѽڵ�������� */
        if( 0 != ulNodeIndex )
        {
            pstDefBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = (HDLC_PARA_LINK_NODE_STRU*)PPP_VIRT_TO_PHY((VOS_UINT32)pstParaNode);
        }

        /* ��д������������������ */
        pstParaNode->pucDataAddr = (VOS_UINT8*)PPP_VIRT_TO_PHY((VOS_UINT32)PPP_ZC_GET_DATA_PTR(pstMem));
        pstParaNode->usDataLen   = usDataLen;
        pstParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->apstInputLinkNode[ulNodeIndex] = pstMem;
        pstBuildInfo->ulInputLinkTotalSize          += (VOS_UINT32)usDataLen;
        pstBuildInfo->ulInputLinkNodeCnt++;
        pstBuildInfo->ulDealCnt++;

#if ((FEATURE_OFF == FEATURE_SKB_EXP) || (FEATURE_ON == FEATURE_TTFMEM_CACHE))
        /* ��Ҫ������д��DDR��HDLC��DDR�ж����� */
        PPP_HDLC_CACHE_FLUSH(PPP_ZC_GET_DATA_PTR(pstMem), PPP_ZC_GET_DATA_LEN(pstMem));
#endif
    }

    if (0 == pstBuildInfo->ulInputLinkNodeCnt)
    {
        return VOS_ERR;
    }

    /* �ϱ���������������ݿ�ά�ɲ� */
    PPP_HDLC_HARD_MntnDefTraceInput(pstDefBuffInfo, pstBuildInfo);

    return VOS_OK;
}


VOS_VOID PPP_HDLC_HARD_DefCfgBufReg(HDLC_DEF_BUFF_INFO_STRU *pstDefBuffInfo)
{

    /* ����װ��������������ʼ��ַ���ø��Ĵ���def_in_lli_addr(0x90) */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_IN_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_VIRT_TO_PHY((VOS_UINT32)&(pstDefBuffInfo->astInputParaLinkNodeBuf[0])));

    /* ����װ��������������ʼ��ַ���ø��Ĵ���def_out_spc_addr(0xA0) */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_OUT_SPC_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_VIRT_TO_PHY((VOS_UINT32)&(pstDefBuffInfo->aucOutputDataBuf[0])));

    /* ����װ��������������ʼ��ַ���ø��Ĵ���def_out_space_dep(0xA4)��16λ */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_OUT_SPACE_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_DEF_OUTPUT_DATA_BUF_LEN & 0xFFFF);

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ���ʼ��ַ���ø��Ĵ���def_rpt_addr(0xA8) */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_RPT_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_VIRT_TO_PHY((VOS_UINT32)&(pstDefBuffInfo->astRptNodeBuf[0])));

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ�������ø��Ĵ���def_rpt_dep (0xAC)��16λ */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_DEF_RPT_BUF_LEN & 0xFFFF);

    return;
}


VOS_UINT32 PPP_HDLC_HARD_DefCfgEnReg
(
    VOS_UINT32                      ulTotalLen
)
{
    /*
    hdlc_def_en   (0x60)
      31   25 24  23 19 18  17  16  15  14  13  12  11  10   9   8   7   1  0
    |--------|---|-----|---|---|---|---|---|---|---|---|---|---|---|------|---|
    |   Rsv  |en | Rsv |en |en |en |en |en |en |en |en |en |en |en |  Rsv |en |

    Reserved            [31:25] 7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_over_int_en     [24]    1'b0    h/s R/W  һ��������װ�����ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��;
    Reserved            [23:19] 5'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_rpt_ful_en      [18]    1'b0    h/s R/W  ���װ�ⲿ��ȷ֡��Ϣ�ϱ��ռ������ͣ�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��;
    def_out_spc_ful_en  [17]    1'b0    h/s R/W  ���װ�ⲿ����洢�ռ������ͣ�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_lcp_int_en      [16]    1'b0    h/s R/W  ���װ�����ЧLCP֡��ͣ�ж��ϱ�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_rpt_prm_err_en  [15]    1'b0    h/s R/W  ���װ�ϱ��ռ���ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_out_prm_err_en  [14]    1'b0    h/s R/W  ���װ����ռ���ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_in_prm_err_en   [13]    1'b0    h/s R/W  ���װ����������ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_cfg_err_en      [12]    1'b0    h/s R/W  ���װЭ��ѹ��ָʾ���ô����ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_wr_timeout_en   [11]    1'b0    h/s R/W  ���װʱAXI����д����timeout�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_rd_timeout _en  [10]    1'b0    h/s R/W  ���װʱAXI���߶�����timeout�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_wr_err_en       [9]     1'b0    h/s R/W  ���װʱAXI����д���������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    def_rd_err_en       [8]     1'b0    h/s R/W  ���װʱAXI���߶����������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    Reserved            [7:1]   7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    def_en              [0]     1'b0    h/s R/W  һ������������װʹ�ܣ������def_enд��1'b1�������װ������һ������������װ��ɺ���Ӳ���Զ���def_en���㣻
                                                 ���װ���̳���ʱ��Ӳ��Ҳ���def_en�Զ����㣬ʹ�ڲ�״̬������IDLE״̬�����üĴ������ؽ��װ����״̬��
                                                 дʱ����һ������������װʹ�ܣ�0����ʹ�ܽ��װ����1��ʹ�ܽ��װ����
                                                 ��ʱ����һ������������װ����״̬��0��û�ڽ��н��װ����1�����ڽ��н��װ����
    */
    VOS_UINT32          ulEnableInterrupt;
    VOS_UINT32          ulValue;
    const VOS_UINT32    ulInterruptValue    = 0x0107FF01;   /* ʹ���жϷ�ʽʱ����ʹ�ܼĴ�����ֵ */
    const VOS_UINT32    ulPollValue         = 0x01;         /* ʹ����ѯ��ʽʱ����ʹ�ܼĴ�����ֵ */


    if( ulTotalLen > HDLC_DEF_INTERRUPT_LIMIT )
    {
        /* ���÷�װ���ʹ�ܼĴ���hdlc_def_en��[31:0]λΪ0x0107FF01 */
        ulValue             = ulInterruptValue;
        ulEnableInterrupt   = VOS_TRUE;

        g_PppHdlcHardStat.ulDefWaitIntCnt++;
    }
    else
    {
        /* ���÷�װ���ʹ�ܼĴ���hdlc_frm_en��[31:0]λΪ0x01 */
        ulValue             = ulPollValue;
        ulEnableInterrupt   = VOS_FALSE;

        g_PppHdlcHardStat.ulDefWaitQueryCnt++;
    }

    /* ʹ��ǰ����ϴη�װ�����װ��ԭʼ�ж� */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFF);
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFF);

    /* �ϱ��Ĵ�����ά�ɲ� */
    PPP_HDLC_HARD_MntnDefTraceRegConfig(VOS_FALSE, ulValue, ulEnableInterrupt);

    /* ʹ��Ӳ��֮ǰ��ǿ��ARM˳��ִ�н���ǰ���ָ�� */
    TTF_FORCE_ARM_INSTUCTION();

    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_EN_ADDR(HDLC_IP_BASE_ADDR), ulValue);

    /* PC��ʹ��HDLCģ���� */
    #if (VOS_OS_VER == VOS_WIN32)
    VHW_HDLC_Task();
    #endif

    return ulEnableInterrupt;
}


VOS_UINT32 PPP_HDLC_HARD_DefPacket
(
    PPP_ID              usPppId,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;


    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(usPppId);

    stBuildPara.ucDataType = PPP_PULL_PACKET_TYPE;
    stBuildPara.usProtocol = PROTO_IP;
    stBuildPara.pstDataQ   = pstDataQ;

    /* ������������������ϱ������ڴ��ά�ɲ� */
    ulBuildResult = PPP_HDLC_HARD_DefBuildInputParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulDefMaxInputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulDefMaxInputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);

    /* ���÷�װ�����װͨ�üĴ��� */
    PPP_HDLC_HARD_CommCfgReg();

    /* �����ڴ���ؼĴ��� */
    PPP_HDLC_HARD_DefCfgBufReg(pstDefBuffInfo);

    /* ����ѹ��ָʾ��������֡�����Ϣ�Ĵ��� */
    PPP_HDLC_HARD_DefCfgReg(HDLC_IP_MODE, pstLink, HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId));

#if (FEATURE_ON == FEATURE_TTFMEM_CACHE)
    PPP_HDLC_CACHE_FLUSH((VOS_UINT8 *)pstDefBuffInfo, sizeof(HDLC_DEF_BUFF_INFO_STRU));
    PPP_HDLC_CACHE_INVALID((VOS_UINT8 *)pstDefBuffInfo, sizeof(HDLC_DEF_BUFF_INFO_STRU));
#endif

    /* ����ʹ�ܼĴ��������ϱ�ʹ��ǰ�Ĵ�����ά�ɲ� */
    ulEnableInterrupt = PPP_HDLC_HARD_DefCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* �ȴ����װ��ͣ����ɣ�Ȼ����������ݣ����ܻ��ж��ͣ�ȵĹ��� */
    PPP_HDLC_HARD_DefWaitAndProc(HDLC_IP_MODE, ulEnableInterrupt, usPppId, pstLink);

    /* �ͷ��ѽ��װ��ɵ����� */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}


VOS_UINT32 PPP_HDLC_HARD_DefRawData
(
    PPP_ID              usPppId,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_DEF_BUFF_INFO_STRU            *pstDefBuffInfo;


    pstDefBuffInfo = HDLC_DEF_GET_BUF_INFO(usPppId);

    VOS_MemSet(&stBuildInfo, 0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    stBuildPara.ucDataType = PPP_PULL_RAW_DATA_TYPE;
    stBuildPara.usProtocol = PROTO_IP;
    stBuildPara.pstDataQ   = pstDataQ;

    /* ������������������ϱ������ڴ��ά�ɲ� */
    ulBuildResult = PPP_HDLC_HARD_DefBuildInputParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulDefMaxInputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulDefMaxInputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulDefMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);

    /* ���÷�װ�����װͨ�üĴ��� */
    PPP_HDLC_HARD_CommCfgReg();

    /* �����ڴ���ؼĴ��� */
    PPP_HDLC_HARD_DefCfgBufReg(pstDefBuffInfo);

    /* ����ѹ��ָʾ��������֡�����Ϣ�Ĵ��� */
    PPP_HDLC_HARD_DefCfgReg(HDLC_PPP_MODE, pstLink, HDLC_DEF_GET_UNCOMPLETED_INFO(usPppId));

#if (FEATURE_ON == FEATURE_TTFMEM_CACHE)
    PPP_HDLC_CACHE_FLUSH((VOS_UINT8 *)pstDefBuffInfo, sizeof(HDLC_DEF_BUFF_INFO_STRU));
    PPP_HDLC_CACHE_INVALID((VOS_UINT8 *)pstDefBuffInfo, sizeof(HDLC_DEF_BUFF_INFO_STRU));
#endif

    /* ����ʹ�ܼĴ��������ϱ�ʹ��ǰ�Ĵ�����ά�ɲ� */
    ulEnableInterrupt = PPP_HDLC_HARD_DefCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* �ȴ����װ��ͣ����ɣ�Ȼ����������ݣ����ܻ��ж��ͣ�ȵĹ��� */
    PPP_HDLC_HARD_DefWaitAndProc(HDLC_PPP_MODE, ulEnableInterrupt, usPppId, pstLink);

    /* �ͷ��ѽ��װ��ɵ����� */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}


VOS_UINT32 PPP_HDLC_HARD_FrmIsEnabled(VOS_VOID)
{
    VOS_UINT32                          ulValue;


    /* SoC���ڴ�����һ�����������ʱ���Զ���ʹ��λ���� */
    ulValue = TTF_READ_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR));

    if (0x01 == (ulValue & 0x01))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


VOS_UINT32 PPP_HDLC_HARD_FrmIsr(unsigned int ulPara)
{
    g_stHdlcRegSaveInfo.ulHdlcFrmRawInt = TTF_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    g_stHdlcRegSaveInfo.ulHdlcFrmStatus = TTF_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));

    /* �յ�һ���жϺ����ԭʼ�ж� */
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFF);

    /* �ͷŷ�װ����ź��� */
    VOS_SmV(g_stHdlcConfigInfo.ulHdlcFrmMasterSem);

    g_PppHdlcHardStat.ulFrmIsrCnt++;

    return IRQ_HANDLED;
}


VOS_UINT32 PPP_HDLC_HARD_FrmUpdateLink
(
    VOS_UINT32                      ulAllocMemCnt,
    VOS_UINT32 *                    aulAllocLen,
    PPP_ZC_STRU                   **ppstAllocedMem,
    HDLC_PARA_LINK_BUILD_PARA_STRU *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU *pstBuildInfo
)
{
    VOS_UINT32                          ulMemLoop;
    VOS_UINT32                          ulNodeIndex;
    HDLC_PARA_LINK_NODE_STRU           *pstOutputParaNode;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstFrmBuffInfo          = HDLC_FRM_GET_BUF_INFO(pstBuildPara->usPppId);

    if( (pstBuildInfo->ulOutputLinkNodeCnt + ulAllocMemCnt) > TTF_HDLC_FRM_OUTPUT_PARA_LINK_MAX_NUM )
    {
        g_PppHdlcHardStat.ulFrmOutputLinkFullCnt++;

        PPP_HDLC_HARD_CommReleaseLink(ppstAllocedMem, ulAllocMemCnt);

        return VOS_ERR;
    }

    /* ����Ŀ�Ŀռ����� apstOutputLinkNode�������ͷ�Ŀ�Ŀռ� */
    VOS_MemCpy(&(pstBuildInfo->apstOutputLinkNode[pstBuildInfo->ulOutputLinkNodeCnt]),
               &(ppstAllocedMem[0]),
               ulAllocMemCnt * sizeof(PPP_ZC_STRU *));

    /* ����װ�������������ĸ�����Ա��ֵ */
    for ( ulMemLoop = 0; ulMemLoop < ulAllocMemCnt; ulMemLoop++ )
    {
        ulNodeIndex = pstBuildInfo->ulOutputLinkNodeCnt;

        pstOutputParaNode = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeIndex]);

        /* �����ϸ���������������pstNextNode�� */
        if (0 != ulNodeIndex)
        {
            pstFrmBuffInfo->astOutputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = (HDLC_PARA_LINK_NODE_STRU*)PPP_VIRT_TO_PHY((VOS_UINT32)pstOutputParaNode);
        }

        pstOutputParaNode->pucDataAddr = (VOS_UINT8*)PPP_VIRT_TO_PHY((VOS_UINT32)PPP_ZC_GET_DATA_PTR(ppstAllocedMem[ulMemLoop]));
        pstOutputParaNode->usDataLen   = (VOS_UINT16)aulAllocLen[ulMemLoop];
        pstOutputParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->ulOutputLinkNodeCnt++;
        pstBuildInfo->ulOutputLinkTotalSize += aulAllocLen[ulMemLoop];

#if ((FEATURE_OFF == FEATURE_SKB_EXP) || (FEATURE_ON == FEATURE_TTFMEM_CACHE))
        PPP_HDLC_CACHE_INVALID((VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)(pstOutputParaNode->pucDataAddr)), pstOutputParaNode->usDataLen);
#endif
    }

    return VOS_OK;
}


VOS_UINT32 PPP_HDLC_HARD_FrmOutputMemAlloc
(
    VOS_UINT16                           usLen,
    HDLC_PARA_LINK_BUILD_PARA_STRU      *pstBuildPara,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    VOS_UINT16                  usFrmedMaxLen;                                  /* ��װ��Ŀ��ܵ���󳤶� */
    VOS_UINT16                  usAllocLen;
    VOS_UINT16                  usAllocLoop;
    VOS_UINT16                  usLoopCnt;
    VOS_UINT16                  usAllocMemCnt;                                  /* ����������ڴ���� */
    VOS_UINT32                  aulAllocLen[HDLC_OUTPUT_PARA_LINK_MAX_SIZE];    /* ��¼��������ĸ����ڴ�鳤�� */
    PPP_ZC_STRU *               apstAllocedMem[HDLC_OUTPUT_PARA_LINK_MAX_SIZE]; /* ��¼��������ĸ����ڴ��ָ�� */
    PPP_ZC_STRU                *pstMem;

    /* ��װ����ܵ�������ݳ���(2*ԭʼ���ݳ���+13B) */
    usFrmedMaxLen = (VOS_UINT16)HDLC_FRM_GET_MAX_FRAMED_LEN(usLen);
    usAllocMemCnt = 0;
    usLoopCnt     = TTF_CEIL(usFrmedMaxLen, PPP_ZC_MAX_DATA_LEN);

    for ( usAllocLoop = 0 ; usAllocLoop < usLoopCnt; usAllocLoop++ )
    {
        usAllocLen  = PPP_ZC_MAX_DATA_LEN;
        pstMem      = PPP_MemAlloc(usAllocLen, PPP_ZC_DL_RESERVE_LEN);

        if (VOS_NULL_PTR == pstMem)
        {
            break;
        }

        usAllocMemCnt++;
        aulAllocLen[usAllocLoop]    = usAllocLen;
        apstAllocedMem[usAllocLoop] = pstMem;
    }

    /* ����������ڴ�ʧ�ܵ���������ͷű����Ѿ�������ڴ� */
    if (usLoopCnt > usAllocMemCnt)
    {
        PPP_HDLC_HARD_CommReleaseLink(&(apstAllocedMem[0]), usAllocMemCnt);
        return VOS_ERR;
    }

    return PPP_HDLC_HARD_FrmUpdateLink(usAllocMemCnt,
                                       &(aulAllocLen[0]), &(apstAllocedMem[0]),
                                       pstBuildPara, pstBuildInfo);
}



VOS_UINT32 PPP_HDLC_HARD_FrmGetProtocol
(
    PPP_ZC_STRU     *pstMem,
    VOS_UINT16      *pusProtocol
)
{
    VOS_UINT8           aucProto[2];
    VOS_UINT32          ulRtn;


    ulRtn = PPP_MemGet(pstMem, 0, aucProto, 2);

    if ( PS_FAIL == ulRtn )
    {
        return VOS_ERR;
    }

    if ( 0x01 == GET_BITS_FROM_BYTE(aucProto[0], 0x01) )
    {
        *pusProtocol = HDLC_MAKE_WORD(0x00, aucProto[0]);
    }
    else
    {
        if ( 0x01 == GET_BITS_FROM_BYTE(aucProto[1], 0x01) )
        {
            *pusProtocol = HDLC_MAKE_WORD(aucProto[0], aucProto[1]);
        }
        else
        {
            PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                            "PPP_HDLC_HARD_FrmGetProtocol, Warning, PPP mode framer data protocol error\r\n");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32 PPP_HDLC_HARD_FrmCheckPara
(
    PPP_ZC_STRU                 *pstMem,
    VOS_UINT32                   ulDataLen,
    PPP_DATA_TYPE_ENUM_UINT8     ucDataType,
    VOS_UINT16                   usProtocol
)
{
    PPP_DATA_TYPE_ENUM_UINT8     ucCurrDataType;
    VOS_UINT32                   ulRlst;
    VOS_UINT16                   usCurrProtocol;


    /* ��ȡ����װ���ݰ����� */
    ucCurrDataType = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);

    if ( ucDataType != ucCurrDataType )
    {
        return PPP_HDLC_PARA_CHECK_FAIL_KEEP;
    }

    /* ����װ���ݰ������쳣 */
    if ( (0 == ulDataLen) || (HDLC_FRM_IN_PER_MAX_CNT < ulDataLen) )
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                        "PPP_HDLC_HARD_FrmCheckPara,IP mode framer data len wrong %d\r\n", ulDataLen);

        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    /* �������PPPģʽ */
    if( PPP_PUSH_RAW_DATA_TYPE != ucCurrDataType )
    {
        return PPP_HDLC_PARA_CHECK_PASS;
    }

    ulRlst  = PPP_HDLC_HARD_FrmGetProtocol(pstMem, &usCurrProtocol);

    if( VOS_OK != ulRlst )
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                        "PPP_HDLC_HARD_FrmCheckPara, Warning, PPP mode get framer data protocol error\r\n");
        return PPP_HDLC_PARA_CHECK_FAIL_DISCARD;
    }

    /* ��֤һ���������ù����з�װЭ��ֵһ�� */
    if( usProtocol != usCurrProtocol )
    {
        return PPP_HDLC_PARA_CHECK_FAIL_KEEP;
    }

    return PPP_HDLC_PARA_CHECK_PASS;
}


VOS_VOID PPP_HDLC_HARD_FrmStartTimer
(
    HDLC_PARA_LINK_BUILD_PARA_STRU      *pstBuildPara
)
{
    if( VOS_NULL_PTR != g_stHdlcConfigInfo.stHdlcFrmTimerHandle )
    {
        return;
    }

    if (VOS_OK != VOS_StartRelTimer(&g_stHdlcConfigInfo.stHdlcFrmTimerHandle, PS_PID_APP_PPP,
                     HDLC_FRM_TIME_INTERVAL,
                     pstBuildPara->usPppId,
                     HDLC_FRM_OUTPUT_SPACE_ALLOC_FAIL,
                     VOS_RELTIMER_NOLOOP, VOS_TIMER_PRECISION_0))
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                        "PPP_HDLC_HARD_FrmStartTimer, Warning, start reltimer error\r\n");
    }

    return;
}


VOS_UINT32 PPP_HDLC_HARD_FrmBuildParaLink
(
 HDLC_PARA_LINK_BUILD_PARA_STRU      *pstBuildPara,
 HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
 )
{
    PPP_ZC_STRU                             *pstMem;
    VOS_UINT32                               ulLoop;
    VOS_UINT16                               usUnFrmLen;
    VOS_UINT32                               ulAllocResult;
    HDLC_PARA_LINK_NODE_STRU                *pstParaNode;
    VOS_UINT32                               ulNodeIndex;
    PPP_HDLC_PARA_CHECK_RESULT_ENUM_UINT32   enCheckResult;
    VOS_UINT32                               ulAllocMemFail;
    HDLC_FRM_BUFF_INFO_STRU                 *pstFrmBuffInfo;


    VOS_MemSet(pstBuildInfo, 0, sizeof(HDLC_PARA_LINK_BUILD_INFO_STRU));

    /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstFrmBuffInfo = HDLC_FRM_GET_BUF_INFO(pstBuildPara->usPppId);
    ulAllocMemFail = VOS_FALSE;

    for(ulLoop = 0; ulLoop < TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_NUM; ulLoop++)
    {
        pstMem = (PPP_ZC_STRU *)PPP_ZC_PEEK_QUEUE_HEAD(pstBuildPara->pstDataQ);

        if( VOS_NULL_PTR == pstMem )
        {
            break;
        }

        usUnFrmLen    = PPP_ZC_GET_DATA_LEN(pstMem);
        enCheckResult = PPP_HDLC_HARD_FrmCheckPara(pstMem, usUnFrmLen,
                                                   pstBuildPara->ucDataType,
                                                   pstBuildPara->usProtocol);

        if( PPP_HDLC_PARA_CHECK_FAIL_DISCARD == enCheckResult )
        {
            pstMem = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);
            PPP_MemFree(pstMem);
            pstBuildInfo->ulDealCnt++;

            g_PppHdlcHardStat.ulFrmInputDiscardCnt++;
            continue;
        }

        if( PPP_HDLC_PARA_CHECK_FAIL_KEEP == enCheckResult )
        {
            break;
        }

        /* һ������������д���װ���ݰ��ܳ����ܳ���15KB */
        if( pstBuildInfo->ulInputLinkTotalSize + usUnFrmLen > TTF_HDLC_FRM_INPUT_PARA_LINK_MAX_SIZE )
        {
            break;
        }

        /* �����װĿ�Ŀռ� */
        ulAllocResult = PPP_HDLC_HARD_FrmOutputMemAlloc(usUnFrmLen, pstBuildPara, pstBuildInfo);

        if( VOS_OK != ulAllocResult )
        {
            ulAllocMemFail = VOS_TRUE;

            g_PppHdlcHardStat.ulFrmAllocOutputMemFailCnt++;
            break;
        }

        /* ��PPP����ȡ��ͷ��㣬������������� pstBuildInfo->apstInputLinkNode */
        pstMem = PPP_ZC_DEQUEUE_HEAD(pstBuildPara->pstDataQ);

        /* ��ȡ��ǰҪ��ӽڵ���±� */
        ulNodeIndex = pstBuildInfo->ulInputLinkNodeCnt;

        /* ����Ҫ����Ĳ����ڵ� */
        pstParaNode = &(pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex]);

        /* ��д������������������ */
        if( 0 != ulNodeIndex )
        {
            pstFrmBuffInfo->astInputParaLinkNodeBuf[ulNodeIndex - 1].pstNextNode = (HDLC_PARA_LINK_NODE_STRU*)PPP_VIRT_TO_PHY((VOS_UINT32)pstParaNode);
        }

        pstParaNode->pucDataAddr = (VOS_UINT8*)PPP_VIRT_TO_PHY((VOS_UINT32)PPP_ZC_GET_DATA_PTR(pstMem));
        pstParaNode->usDataLen   = usUnFrmLen;
        pstParaNode->pstNextNode = VOS_NULL_PTR;

        pstBuildInfo->apstInputLinkNode[ulNodeIndex] = pstMem;
        pstBuildInfo->ulInputLinkTotalSize          += (VOS_UINT32)usUnFrmLen;
        pstBuildInfo->ulInputLinkNodeCnt++;
        pstBuildInfo->ulDealCnt++;

#if ((FEATURE_OFF == FEATURE_SKB_EXP) || (FEATURE_ON == FEATURE_TTFMEM_CACHE))
        /* ��Ҫ������д��DDR��HDLC��DDR�ж����� */
        PPP_HDLC_CACHE_FLUSH(PPP_ZC_GET_DATA_PTR(pstMem), PPP_ZC_GET_DATA_LEN(pstMem));
#endif
    }

    if (0 == pstBuildInfo->ulInputLinkNodeCnt)
    {
        if (VOS_TRUE == ulAllocMemFail)
        {
            /* �ȴ�һ��ʱ������³��������ڴ��ٷ�װ */
            PPP_HDLC_HARD_FrmStartTimer(pstBuildPara);

            g_PppHdlcHardStat.ulFrmAllocFirstMemFailCnt++;
        }

        return VOS_ERR;
    }

    /* ��������������������ݿ�ά�ɲ� */
    PPP_HDLC_HARD_MntnFrmTraceInput(pstFrmBuffInfo, pstBuildInfo);

    return VOS_OK;
}


VOS_VOID PPP_HDLC_HARD_FrmCfgBufReg(HDLC_FRM_BUFF_INFO_STRU *pstFrmBuffInfo)
{

    /* ����װ��������������ʼ��ַ���ø��Ĵ���frm_in_lli_addr */
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_IN_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_VIRT_TO_PHY((VOS_UINT32)&(pstFrmBuffInfo->astInputParaLinkNodeBuf[0])));

    /* ����װ��������������ʼ��ַ���ø��Ĵ���frm_out_lli_addr */
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_OUT_LLI_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_VIRT_TO_PHY((VOS_UINT32)&(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0])));

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ���ʼ��ַ���ø��Ĵ���frm_rpt_addr */
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_RPT_ADDR(HDLC_IP_BASE_ADDR),
                    PPP_VIRT_TO_PHY((VOS_UINT32)&(pstFrmBuffInfo->astRptNodeBuf[0])));

    /* ����װ��Ч֡�����Ϣ�ϱ��ռ�������ø��Ĵ���frm_rpt_dep��[15:0]λ */
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_RPT_DEP_ADDR(HDLC_IP_BASE_ADDR),
                    (VOS_UINT32)TTF_HDLC_FRM_RPT_BUF_LEN & 0xFFFF);

    return;
}


VOS_VOID PPP_HDLC_HARD_FrmCfgReg
(
    struct link        *pstLink,
    VOS_UINT16          usProtocol
)
{
    /*
    hdlc_frm_cfg   (0x20)
      31              16 15           4 3      2   1      0
    |-------------------|--------------|--------|------|------|
    |      protocol     |      Rsv     |   Pfc  | Acfc |1dor2d|

    frm_protocol         [31:16] 16'b0   h/s R/W  ��װЭ��ֵ����ЧЭ��ֵ�涨�μ�����б�
    Reserved             [15:4]  12'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    frm_pfc              [3:2]   2'b0    h/s R/W  P��ѹ��ָʾ��00��Ӳ��ģ�����P��P����ѹ��;
                                                               01��Ӳ��ģ�����P��P��ѹ��;
                                                               11��Ӳ��ģ�鲻���P��;
                                                               ��������Ч;
    frm_acfc             [1]     1'b0    h/s R/W  AC��ѹ��ָʾ��0��AC����ѹ��;1����ʾAC��ѹ��;
    frm_in_lli_1dor2d    [0]     1'b0    h/s R/W  ��װ����һά���ά����ѡ��ָʾ�Ĵ�����
                                                                0Ϊһά;1Ϊ��ά;

    IPģʽһ�����P��,PPPģʽһ�������P��
      LCP֡: AC��ѹ����P��ѹ��
    */

    VOS_UINT32              ulFrmCfg;


    /* ���Ĵ���hdlc_frm_cfg��[0]λfrm_in_lli_1dor2d����Ϊ0 */
    ulFrmCfg = 0x0;

    /* ����hdlc_frm_cfg�� P��� AC�� */
    if (PROTO_LCP != usProtocol)
    {
        if ( 1 == pstLink->lcp.his_acfcomp )
        {
            ulFrmCfg |= (1 << HDLC_FRM_ACFC_BITPOS);
        }

        if ( 1 == pstLink->lcp.his_protocomp )
        {
            ulFrmCfg |= (1 << HDLC_FRM_PFC_BITPOS);
        }

        /* ����hdlc_frm_accm */
        TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR),
                            pstLink->lcp.his_accmap);
    }
    else
    {
        TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFF);
    }

    /* ���üĴ���hdlc_frm_cfg��[31:16]λfrm_protocolΪusProtocol */
    ulFrmCfg |= ( ((VOS_UINT32)usProtocol) << 16 );

    TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR), ulFrmCfg);

    return;
}


VOS_VOID PPP_HDLC_HARD_FrmRawCfgReg
(
    struct link        *pstLink,
    VOS_UINT16          usProtocol
)
{
    /*
    hdlc_frm_cfg   (0x20)
      31              16 15           4 3      2   1      0
    |-------------------|--------------|--------|------|------|
    |      protocol     |      Rsv     |   Pfc  | Acfc |1dor2d|

    frm_protocol         [31:16] 16'b0   h/s R/W  ��װЭ��ֵ����ЧЭ��ֵ�涨�μ�����б�
    Reserved             [15:4]  12'b0   h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    frm_pfc              [3:2]   2'b0    h/s R/W  P��ѹ��ָʾ��00��Ӳ��ģ�����P��P����ѹ��;
                                                               01��Ӳ��ģ�����P��P��ѹ��;
                                                               11��Ӳ��ģ�鲻���P��;
                                                               ��������Ч;
    frm_acfc             [1]     1'b0    h/s R/W  AC��ѹ��ָʾ��0��AC����ѹ��;1����ʾAC��ѹ��;
    frm_in_lli_1dor2d    [0]     1'b0    h/s R/W  ��װ����һά���ά����ѡ��ָʾ�Ĵ�����
                                                                0Ϊһά;1Ϊ��ά;

    IPģʽһ�����P��,PPPģʽһ�������P��
      LCP֡: AC��ѹ����P��ѹ��
    */

    VOS_UINT32              ulFrmCfg;
    /*PS_BOOL_ENUM_UINT8      enPComp;       �Ƿ�ѹ��Э���ֶ�, �� - PS_TRUE */
    PS_BOOL_ENUM_UINT8      enACComp;     /* �Ƿ�ѹ����ַ�Ϳ����ֶ�, �� - PS_TRUE */
    VOS_UINT32              ulACCM;
    VOS_UINT8               ucACComp;
    VOS_UINT8               ucPComp;
    VOS_UINT8               ucLowByte;
    VOS_UINT16              usLowWord;


    /* ���Ĵ���hdlc_frm_cfg��[0]λfrm_in_lli_1dor2d����Ϊ0 */
    ulFrmCfg    = 0x0;

    if (PROTO_LCP == usProtocol)
    {
        /* LCP֡P��ѹ��, AC��ѹ��, ACCMΪȫת�� */
        /*enPComp     = PS_FALSE; */
        enACComp    = PS_FALSE;
        ulACCM      = 0xFFFFFFFF;
    }
    else
    {
        /* ʹ��Ĭ��ֵ */
        /*enPComp     = (1 == pstLink->lcp.his_protocomp) ? PS_TRUE : PS_FALSE; */
        enACComp    = (1 == pstLink->lcp.his_acfcomp) ? PS_TRUE : PS_FALSE;
        /* ����PPP���Ų�֪��ACCM, ������ΪЭ��Ĭ��ֵ */
        ulACCM      = 0xFFFFFFFF;
    }

    /* ��ȡAC��ѹ��ָʾ, P��ѹ��ָʾ, Э��ֵ, ACCM */
    ucACComp = (PS_TRUE == enACComp) ? 1 : 0;
    ucPComp = HDLC_PROTOCOL_NO_ADD;

    /* ����accm */
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_ACCM_ADDR(HDLC_IP_BASE_ADDR),ulACCM);

    /* ��ucPComp���õ�һ���ֽڵĵ�2, 3λ�� */
    ucLowByte = SET_BITS_VALUE_TO_BYTE(ucPComp, HDLC_FRM_PFC_BITPOS);

    if (1 == ucACComp)  /* AC��ѹ�� */
    {
        SET_BIT_TO_BYTE(ucLowByte, HDLC_FRM_ACFC_BITPOS);
    }
    else
    {
        CLEAR_BIT_TO_BYTE(ucLowByte, HDLC_FRM_ACFC_BITPOS);
    }

    usLowWord   = HDLC_MAKE_WORD(0x00, ucLowByte);
    ulFrmCfg    = HDLC_MAKE_DWORD(usProtocol, usLowWord);

    /* ����AC��ѹ��ָʾ, P��ѹ��ָʾ, Э��ֵ��ʹ�ܷ�װ���, accm */
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_CFG_ADDR(HDLC_IP_BASE_ADDR),ulFrmCfg);

    return;
}


VOS_UINT32 PPP_HDLC_HARD_FrmCfgEnReg(VOS_UINT32   ulTotalLen)
{
    /*
    1.hdlc_frm_en   (0x10)
      31   25 24  23 18 17  16  15  14  13  12  11  10   9   8  7    1  0
    |--------|---|-----|---|---|---|---|---|---|---|---|---|---|------|---|
    |   Rsv  |en | Rsv |en |en |en |en |en |en |en |en |en |en |  Rsv |en |

    Reserved            [31:25] 7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    frm_over_int_en     [24]    1'b0    h/s R/W  һ�������װ�����ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��;
    Reserved            [23:18] 6'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    frm_rpt_dep_err_en  [17]    1'b0    h/s R/W  ��װ�ⲿ��ȷ֡�����ϱ��ռ䲻���ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��;
    frm_out_spc_err_en  [16]    1'b0    h/s R/W  ��װ�ⲿ����洢�ռ䲻���ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_rpt_prm_err_en  [15]    1'b0    h/s R/W  ��װ�ϱ��ռ���ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_out_prm_err_en  [14]    1'b0    h/s R/W  ��װ���������ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_in_prm_err_en   [13]    1'b0    h/s R/W  ��װ����������ز��������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_cfg_err_en      [12]    1'b0    h/s R/W  ��װЭ�鼰��ѹ��ָʾ���ô����ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_wr_timeout_en   [11]    1'b0    h/s R/W  ��װʱAXI����д����timeout�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_rd_timeout_en   [10]    1'b0    h/s R/W  ��װʱAXI���߶�����timeout�ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_wr_err_en       [9]     1'b0    h/s R/W  ��װʱAXI����д���������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    frm_rd_err_en       [8]     1'b0    h/s R/W  ��װʱAXI���߶����������ж�ʹ��;0���жϽ�ֹ;1���ж�ʹ��
    Reserved            [7:1]   7'b0    h/s R/W  ����λ����ʱ����0��дʱ��Ӱ�졣
    frm_en              [0]     1'b0    h/s R/W  һ�������װʹ�ܣ������frm_enд��1'b1������װ����;һ�������װ��ɺ���Ӳ���Զ���frm_en���㣻
                                                 ��װ���̳���ʱ��Ӳ��Ҳ���frm_en�Զ����㣬ʹ�ڲ�״̬������IDLE״̬��
                                                 дʱ����һ�������װʹ��;0����ʹ�ܷ�װ����;1��ʹ�ܷ�װ����;
                                                 ��ʱ����һ�������װ����״̬;0��û�ڽ��з�װ����;1�����ڽ��з�װ����
    */

    VOS_UINT32          ulEnableInterrupt;
    VOS_UINT32          ulValue;
    const VOS_UINT32    ulInterruptValue    = 0x0103FF01;   /* ʹ���жϷ�ʽʱ����ʹ�ܼĴ�����ֵ */
    const VOS_UINT32    ulPollValue         = 0x01;         /* ʹ����ѯ��ʽʱ����ʹ�ܼĴ�����ֵ */


    /* �жϴ���װ���ݵ��ܳ��ȣ�������������ʹ���жϷ�ʽ������ʹ����ѯ��ʽ */
    if( ulTotalLen > HDLC_FRM_INTERRUPT_LIMIT )
    {
        /* ���÷�װ���ʹ�ܼĴ���hdlc_frm_en��[31:0]λΪ0x0103FF01 */
        ulValue             = ulInterruptValue;
        ulEnableInterrupt   = VOS_TRUE;

        g_PppHdlcHardStat.ulFrmWaitIntCnt++;
    }
    else
    {
        /* ���÷�װ���ʹ�ܼĴ���hdlc_frm_en��[31:0]λΪ0x01 */
        ulValue             = ulPollValue;
        ulEnableInterrupt   = VOS_FALSE;

        g_PppHdlcHardStat.ulFrmWaitQueryCnt++;
    }

    /* ʹ��ǰ����ϴη�װ�����װ��ԭʼ�ж� */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEF_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFF);
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_INT_CLR_ADDR(HDLC_IP_BASE_ADDR), 0xFFFFFFFF);

    /* �ϱ��Ĵ�����ά�ɲ� */
    PPP_HDLC_HARD_MntnFrmTraceRegConfig(VOS_FALSE, ulValue, ulEnableInterrupt);

    /* ʹ��Ӳ��֮ǰ��ǿ��ARM˳��ִ�н���ǰ���ָ�� */
    TTF_FORCE_ARM_INSTUCTION();

    TTF_WRITE_32REG(SOC_ARM_HDLC_FRM_EN_ADDR(HDLC_IP_BASE_ADDR), ulValue);

    /* PC��ʹ��HDLCģ���� */
    #if (VOS_OS_VER == VOS_WIN32)
    VHW_HDLC_Task();
    #endif

    return ulEnableInterrupt;
}


VOS_UINT32 PPP_HDLC_HARD_FrmWaitStatusChange(VOS_VOID)
{
    VOS_UINT32              ulFrmRsltWaitNum;           /* ��ֹӲ���쳣�ı������� */
    volatile VOS_UINT32     ulFrmStatus;                /* ��װ״̬ */


   /* ��ѯhdlc_frm_status (0x28)�ĵ�[0]λ�͵�[1]λ���κ�һ��Ϊ1���߳�ʱ�򷵻� */
    ulFrmRsltWaitNum = 0UL;

    while (ulFrmRsltWaitNum < HDLC_FRM_MAX_WAIT_RESULT_NUM)
    {
        /* ��ȡ hdlc_frm_status��[0][1]λ */
        ulFrmStatus  =   TTF_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));

        if (HDLC_FRM_ALL_PKT_DOING != (ulFrmStatus & HDLC_FRM_STATUS_MASK))
        {
            break;
        }

        ulFrmRsltWaitNum++;
    }

    if ( HDLC_FRM_MAX_WAIT_RESULT_NUM <= ulFrmRsltWaitNum )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_HDLC_HARD_FrmWaitStatusChange, WARNING, wait hdlc_frm_status timeout %d status 0x%x!\r\n",
                      ulFrmRsltWaitNum, ulFrmStatus);

        g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_WAIT_STATUS_TIMEOUT_IND_BITPOS);

        return VOS_ERR;
    }

    g_PppHdlcHardStat.ulFrmMaxQueryCnt = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxQueryCnt, ulFrmRsltWaitNum);

    return VOS_OK;
}


VOS_UINT32 PPP_HDLC_HARD_FrmWaitResult
(
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32              ulFrmStatus;        /* ��װ״̬ */
    VOS_UINT32              ulResult;


    if (VOS_TRUE == ulEnableInterrupt)
    {
        /* �ȴ��жϵõ���������״̬ */
        ulResult = PPP_HDLC_HARD_CommWaitSem(g_stHdlcConfigInfo.ulHdlcFrmMasterSem, HDLC_FRM_MASTER_INT_TIMER_LEN);

        /* �������жϷ�������н��������жϲ�������Statusָʾ�Ƿ�����bit��ԭʼ�жϼĴ���
           �������ʴ˴�ȡ������g_stHdlcRegSaveInfo�е�״ֵ̬ */
        ulFrmStatus = g_stHdlcRegSaveInfo.ulHdlcFrmStatus;
    }
    else
    {
        /* ��ѯ�õ��������� */
        ulResult = PPP_HDLC_HARD_FrmWaitStatusChange();

        /* ��ѯhdlc_frm_status (0x28)��ȡ��װ״̬�����䷵�� */
        ulFrmStatus  =  TTF_READ_32REG(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR));
    }

    /* �ϱ��Ĵ�����ά�ɲ� */
    PPP_HDLC_HARD_MntnFrmTraceRegConfig(VOS_TRUE, 0, ulEnableInterrupt);

    /* �Ȳ���˵��HDLC���ڹ��� */
    if (VOS_OK != ulResult)
    {
        return HDLC_FRM_ALL_PKT_DOING;
    }

    ulFrmStatus &=  HDLC_FRM_STATUS_MASK;

    return ulFrmStatus;
}


VOS_VOID PPP_HDLC_HARD_FrmProcValidFrames
(
    PPP_ID                               usPppId,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT16                          usFrmOutSegNum;
    VOS_UINT8                           ucFrmValidNum;
    VOS_UINT32                          ulFrmOutSpaceCnt;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;
    HDLC_PARA_LINK_NODE_STRU           *pstOutputParaLink;
    HDLC_FRM_RPT_NODE_STRU             *pstFrmRptNodeStru;
    PPP_ZC_STRU                       **ppstOutputLinkNode;
    VOS_UINT32                          ucRptSpaceIndex;
    VOS_UINT32                          ulOutputLinkIndex;
    VOS_UINT8                          *pucFrmOutAddr;
    VOS_UINT16                          usFrmOutLen;
    VOS_UINT16                          usDataLen;


    pstFrmBuffInfo     = HDLC_FRM_GET_BUF_INFO(usPppId);                   /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstFrmRptNodeStru  = &(pstFrmBuffInfo->astRptNodeBuf[0]);              /* ��װ�ϱ��ռ��׵�ַ */
    pstOutputParaLink  = &(pstFrmBuffInfo->astOutputParaLinkNodeBuf[0]);   /* ��װ��������׵�ַ */
    ppstOutputLinkNode = &(pstBuildInfo->apstOutputLinkNode[0]);           /* ��װ�������ڵ��Ӧ�㿽���ڴ������׵�ַ */
    ulFrmOutSpaceCnt   = pstBuildInfo->ulOutputLinkNodeCnt;                /* ��װ�������ڵ�ĸ��� */

    /* ��Ч֡���ռ��Ƭ�θ���usFrmOutSegNum= hdlc_frm_status�Ĵ���[31:16]λ��ֵ */
    usFrmOutSegNum = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR), 16, 31);

    /* ��Ч֡����usFrmValidNum= hdlc_frm_status�Ĵ���[15:8]λ��ֵ */
    ucFrmValidNum  = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_FRM_STATUS_ADDR(HDLC_IP_BASE_ADDR), 8, 15);

    /* �ϱ���װ�����ݿ�ά�ɲ�:�ϱ��ռ���Ϣ������������� */
    PPP_HDLC_HARD_MntnFrmTraceOutput(ucFrmValidNum, usFrmOutSegNum, pstFrmBuffInfo, pstBuildInfo);

    /* ucFrmValidNum�϶�ҪС�ڵ���ʹ�õ��ڴ����usFrmOutSegNum */
    if( ucFrmValidNum > usFrmOutSegNum )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                      "PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_valid_num = %d > usFrmOutSegNum = %d",
                      ucFrmValidNum, usFrmOutSegNum);
        PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    /* ucFrmValidNumӦ��������������ͬulInputLinkNodeCnt��������װ������ܻ�Ⱥ���С */
    if( ucFrmValidNum > pstBuildInfo->ulInputLinkNodeCnt )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                      "PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_valid_num = %d > InputLinkNodeCnt = %d",
                      ucFrmValidNum, pstBuildInfo->ulInputLinkNodeCnt);
        PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    /* usFrmOutSegNumʹ�õ��ڴ�����϶�С�ڵ���ulOutputLinkNodeCnt */
    if( usFrmOutSegNum  > ulFrmOutSpaceCnt )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                      "PPP_HDLC_HARD_FrmProcValidFram, ERROR, frm_out_seg_num = %d > OutputLinkNodeCnt = %d",
                      usFrmOutSegNum, ulFrmOutSpaceCnt);
        PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode, ulFrmOutSpaceCnt);
        return;
    }

    ucRptSpaceIndex   = 0;
    ulOutputLinkIndex = 0;

    while( ucRptSpaceIndex < ucFrmValidNum )
    {
        pucFrmOutAddr    = (VOS_UINT8*)PPP_PHY_TO_VIRT((VOS_UINT32)pstFrmRptNodeStru[ucRptSpaceIndex].pucFrmOutOneAddr);
        usFrmOutLen      = pstFrmRptNodeStru[ucRptSpaceIndex].usFrmOutOneLen;

        if ( (0 == usFrmOutLen) || (HDLC_FRM_OUT_PER_MAX_CNT < usFrmOutLen) )
        {
            PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                          "PPP_HDLC_HARD_FrmProcValidFrames, ERROR, invalid usFrmOutOneLen %d\r\n",
                          usFrmOutLen);

            /* �ͷ������Ŀ�Ŀռ� */
            PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                          ulFrmOutSpaceCnt - ulOutputLinkIndex);
            return;
        }

        pstMem      = ppstOutputLinkNode[ulOutputLinkIndex];

        if( pucFrmOutAddr != PPP_ZC_GET_DATA_PTR(pstMem) )
        {
            PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                              "PPP_HDLC_HARD_FrmProcValidFram, ERROR, SOC copy error!");

            /* �ͷ������Ŀ�Ŀռ� */
            PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                          ulFrmOutSpaceCnt - ulOutputLinkIndex);
            return;
        }

        while( usFrmOutLen > 0 )
        {
            /* ��pstBuildInfo->apstOutputLinkNodeȡ��ͷ��� pstMem */
            pstMem    = ppstOutputLinkNode[ulOutputLinkIndex];

            /* ���������������ָĿ�Ŀռ�Ĵ�С */
            usDataLen = pstOutputParaLink[ulOutputLinkIndex].usDataLen;

            if( usFrmOutLen > usDataLen )
            {
                PPP_ZC_SET_DATA_LEN(pstMem, usDataLen);
                usFrmOutLen -= usDataLen;
            }
            else
            {
                PPP_ZC_SET_DATA_LEN(pstMem, usFrmOutLen);
                usFrmOutLen  = 0;
            }

            PPP_HDLC_ProcDlData(usPppId, pstMem);

            g_PppDataQCtrl.stStat.ulDownlinkSndDataCnt++;

            /* ������������ݰ���apstOutputLinkNode����� */
            ppstOutputLinkNode[ulOutputLinkIndex] = VOS_NULL_PTR;

            ulOutputLinkIndex++;
        }

        ucRptSpaceIndex++;
    }

    /* �ͷ�ʣ��δ���õ�Ŀ�Ŀռ� */
    PPP_HDLC_HARD_CommReleaseLink(ppstOutputLinkNode + ulOutputLinkIndex,
                                  ulFrmOutSpaceCnt - ulOutputLinkIndex);

    return;
}


VOS_VOID PPP_HDLC_HARD_FrmProcException
(
    VOS_UINT32          ulStatus,
    VOS_UINT32          ulEnableInterrupt
)
{
    VOS_UINT32                          ulRawInt;


    if( VOS_TRUE == ulEnableInterrupt )
    {
        /* �������жϷ�������н��������жϲ������ʴ˴�ȡ������g_stHdlcRegSaveInfo�е�ԭʼ�жϼĴ���ֵ */
        ulRawInt                        =   g_stHdlcRegSaveInfo.ulHdlcFrmRawInt;
        g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_INTERRUPT_IND_BITPOS);
    }
    else
    {
        ulRawInt  =   TTF_READ_32REG(SOC_ARM_HDLC_FRM_RAW_INT_ADDR(HDLC_IP_BASE_ADDR));
    }

    PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                 "PPP_HDLC_HARD_FrmProcException, ERROR, Exception ocurr status 0x%x RAW_INT 0x%x\r\n",
                 ulStatus, ulRawInt);
    PPP_HDLC_HARD_MntnShowFrmReg();
    PPP_HDLC_HARD_MntnShowDefReg();

    g_PppHdlcHardStat.usFrmExpInfo |=   (1 << HDLC_EXCEPTION_IND_BITPOS);

    /* ��λǰ��Delay 1s��֤��ά�ɲ�������� */
    VOS_TaskDelay(1000);

    /* ���HDLC�����쳣���򵥰��쳣���� */
    DRV_SYSTEM_ERROR(HDLC_FRM_SYSTEM_ERROR_ID, __LINE__, (VOS_INT)g_PppHdlcHardStat.usFrmExpInfo,
                         (VOS_CHAR *)&g_stHdlcRegSaveInfo,
                         sizeof(HDLC_REG_SAVE_INFO_STRU));

    return;
}


VOS_VOID PPP_HDLC_HARD_FrmWaitAndProc
(
    VOS_UINT32                           ulEnableInterrupt,
    PPP_ID                               usPppId,
    struct link                         *pstLink,
    HDLC_PARA_LINK_BUILD_INFO_STRU      *pstBuildInfo
)
{
    VOS_UINT32                          ulFrmStatus;


    /* ʹ���жϣ���ȴ��жϸ������ͷ��ź�����������ѯ���װ״̬�Ĵ��� */
    ulFrmStatus = PPP_HDLC_HARD_FrmWaitResult(ulEnableInterrupt);

    if ( HDLC_FRM_ALL_PKT_DONE == ulFrmStatus )
    {
        /* ������Ч֡�����ͷ�ʣ���ڴ� */
        PPP_HDLC_HARD_FrmProcValidFrames(usPppId, pstBuildInfo);
    }
    else
    {
        /* �ͷ������Ŀ�Ŀռ� */
        PPP_HDLC_HARD_CommReleaseLink(pstBuildInfo->apstOutputLinkNode, pstBuildInfo->ulOutputLinkNodeCnt);

        /* ��ӡ�쳣��־������PPP���� */
        PPP_HDLC_HARD_FrmProcException(ulFrmStatus, ulEnableInterrupt);
    }

    g_stHdlcRegSaveInfo.ulHdlcFrmRawInt = 0xFFFFFFFF;
    g_stHdlcRegSaveInfo.ulHdlcFrmStatus = 0xFFFFFFFF;

    return;
}


VOS_UINT32 PPP_HDLC_HARD_FrmPacket
(
    PPP_ID              usPppId,
    VOS_UINT16          usProtocol,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCurCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    stBuildPara.ucDataType = PPP_PUSH_PACKET_TYPE;
    stBuildPara.usProtocol = usProtocol;
    stBuildPara.usPppId    = usPppId;
    stBuildPara.pstDataQ   = pstDataQ;

    /* ����usPppId�ҵ���Ӧ���ڴ� */
    pstFrmBuffInfo = HDLC_FRM_GET_BUF_INFO(usPppId);

    /* ����������������������ϱ������ڴ��ά�ɲ� */
    ulBuildResult  = PPP_HDLC_HARD_FrmBuildParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCurCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                    "PPP_HDLC_HARD_FrmPacket, WARNING, BuildParaLink Fail.\r\n");
        return ulBuildResult;
    }

    g_PppHdlcHardStat.ulFrmMaxInputCntOnce   = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxInputSizeOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);
    g_PppHdlcHardStat.ulFrmMaxOutputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputCntOnce, stBuildInfo.ulOutputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce, stBuildInfo.ulOutputLinkTotalSize);

    /* ���÷�װ�����װͨ�üĴ��� */
    PPP_HDLC_HARD_CommCfgReg();

    /* �����ڴ���ؼĴ��� */
    PPP_HDLC_HARD_FrmCfgBufReg(pstFrmBuffInfo);

    /* ���÷�װ��ؼĴ��� */
    PPP_HDLC_HARD_FrmCfgReg(pstLink, usProtocol);

#if (FEATURE_ON == FEATURE_TTFMEM_CACHE)
    PPP_HDLC_CACHE_FLUSH((VOS_UINT8 *)pstFrmBuffInfo, sizeof(HDLC_FRM_BUFF_INFO_STRU));
    PPP_HDLC_CACHE_INVALID((VOS_UINT8 *)pstFrmBuffInfo, sizeof(HDLC_FRM_BUFF_INFO_STRU));
#endif

    /* ����ʹ�ܼĴ��������ϱ�ʹ��ǰ�Ĵ�����ά�ɲ� */
    ulEnableInterrupt = PPP_HDLC_HARD_FrmCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* �ȴ���װ��ɣ�Ȼ�����������,�ͷŶ����Ŀ�Ŀռ��ڴ� */
    PPP_HDLC_HARD_FrmWaitAndProc(ulEnableInterrupt, usPppId, pstLink, &stBuildInfo);

    /* �ͷ�pstBuildInfo->apstInputLinkNode�еĽ���ڴ� */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}


VOS_UINT32 PPP_HDLC_HARD_FrmRawData
(
    PPP_ID              usPppId,
    VOS_UINT16          usProtocol,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ,
    VOS_UINT32         *pulDealCurCnt
)
{
    VOS_UINT32                          ulEnableInterrupt;
    HDLC_PARA_LINK_BUILD_INFO_STRU      stBuildInfo;
    HDLC_PARA_LINK_BUILD_PARA_STRU      stBuildPara;
    VOS_UINT32                          ulBuildResult;
    HDLC_FRM_BUFF_INFO_STRU            *pstFrmBuffInfo;


    stBuildPara.ucDataType = PPP_PUSH_RAW_DATA_TYPE;
    stBuildPara.usProtocol = usProtocol;
    stBuildPara.usPppId    = usPppId;
    stBuildPara.pstDataQ   = pstDataQ;

    /* ����usPppId�ҵ���Ӧ���ڴ�  */
    pstFrmBuffInfo         = HDLC_FRM_GET_BUF_INFO(usPppId);

    /* ����������������������ϱ������ڴ��ά�ɲ� */
    ulBuildResult  = PPP_HDLC_HARD_FrmBuildParaLink(&stBuildPara, &stBuildInfo);

    *pulDealCurCnt = stBuildInfo.ulDealCnt;

    if (VOS_OK != ulBuildResult)
    {
        return ulBuildResult;
    }


    g_PppHdlcHardStat.ulFrmMaxInputCntOnce   = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputCntOnce, stBuildInfo.ulInputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxInputSizeOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxInputSizeOnce, stBuildInfo.ulInputLinkTotalSize);
    g_PppHdlcHardStat.ulFrmMaxOutputCntOnce  = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputCntOnce, stBuildInfo.ulOutputLinkNodeCnt);
    g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce = TTF_MAX(g_PppHdlcHardStat.ulFrmMaxOutputSizeOnce, stBuildInfo.ulOutputLinkTotalSize);

    /* ���÷�װ�����װͨ�üĴ��� */
    PPP_HDLC_HARD_CommCfgReg();

    /* �����ڴ���ؼĴ��� */
    PPP_HDLC_HARD_FrmCfgBufReg(pstFrmBuffInfo);

    /* ���÷�װ��ؼĴ��� */
    PPP_HDLC_HARD_FrmRawCfgReg(pstLink, usProtocol);

#if (FEATURE_ON == FEATURE_TTFMEM_CACHE)
    PPP_HDLC_CACHE_FLUSH((VOS_UINT8 *)pstFrmBuffInfo, sizeof(HDLC_FRM_BUFF_INFO_STRU));
    PPP_HDLC_CACHE_INVALID((VOS_UINT8 *)pstFrmBuffInfo, sizeof(HDLC_FRM_BUFF_INFO_STRU));
#endif

    /* ����ʹ�ܼĴ��������ϱ�ʹ��ǰ�Ĵ�����ά�ɲ� */
    ulEnableInterrupt = PPP_HDLC_HARD_FrmCfgEnReg(stBuildInfo.ulInputLinkTotalSize);

    /* �ȴ���װ��ɣ�Ȼ�����������,�ͷŶ����Ŀ�Ŀռ��ڴ� */
    PPP_HDLC_HARD_FrmWaitAndProc(ulEnableInterrupt, usPppId, pstLink, &stBuildInfo);

    /* �ͷ�pstBuildInfo->apstInputLinkNode�еĽ���ڴ� */
    PPP_HDLC_HARD_CommReleaseLink(stBuildInfo.apstInputLinkNode, stBuildInfo.ulInputLinkNodeCnt);

    return VOS_OK;
}


PPP_HDLC_RESULT_TYPE_ENUM_UINT32 PPP_HDLC_HARD_ProcData
(
    PPP_ID              usPppId,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU  *pstDataQ
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT32                          ulDealTotalCnt;
    VOS_UINT32                          ulDealCurCnt;
    VOS_UINT32                          ulDealResult;
    VOS_UINT16                          usProtocol;
    PPP_DATA_TYPE_ENUM_UINT8            ucDataType;


    g_PppHdlcHardStat.ulHdlcHardProcCnt++;

    ulDealTotalCnt  = 0;
    ulDealCurCnt    = 0;

    for (;;)
    {
        pstMem  = (PPP_ZC_STRU *)PPP_ZC_PEEK_QUEUE_HEAD(pstDataQ);

        /* ����Ϊ�յ�ʱ�򷵻ؿ�ָ�� */
        if ( VOS_NULL_PTR == pstMem )
        {
            return PPP_HDLC_RESULT_COMM_FINISH;
        }

        /*����ý��(�����ͷŶ����Ѿ��ڸ��������ڲ���ɣ��������ͷŽ��)*/
        ucDataType   = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);
        ulDealResult = VOS_OK;
        ulDealCurCnt = 0;

        switch ( ucDataType )
        {
            case PPP_PULL_PACKET_TYPE:

                ulDealResult = PPP_HDLC_HARD_DefPacket(usPppId, pstLink, pstDataQ, &ulDealCurCnt);

                g_PppHdlcHardStat.ulDefIpDataProcCnt += ulDealCurCnt;
                break;
            case PPP_PUSH_PACKET_TYPE:

                ulDealResult = PPP_HDLC_HARD_FrmPacket(usPppId, PROTO_IP, pstLink, pstDataQ, &ulDealCurCnt);

                g_PppHdlcHardStat.ulFrmIpDataProcCnt += ulDealCurCnt;
                break;
            case PPP_PULL_RAW_DATA_TYPE:

                ulDealResult = PPP_HDLC_HARD_DefRawData(usPppId, pstLink, pstDataQ, &ulDealCurCnt);

                g_PppHdlcHardStat.ulDefIpDataProcCnt += ulDealCurCnt;
                break;
            case PPP_PUSH_RAW_DATA_TYPE:

                /* ��ȡ����װ���ݰ���Э��ֵusProtocol */
                if (VOS_OK == PPP_HDLC_HARD_FrmGetProtocol(pstMem, &usProtocol))
                {
                    ulDealResult = PPP_HDLC_HARD_FrmRawData(usPppId, usProtocol, pstLink, pstDataQ, &ulDealCurCnt);

                    g_PppHdlcHardStat.ulFrmPppDataProcCnt += ulDealCurCnt;
                }
                else
                {
                    pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(pstDataQ);
                    PPP_MemFree(pstMem);
                }
                break;
            default:
                pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(pstDataQ);
                PPP_MemFree(pstMem);
                PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                              "PPP_HDLC_HARD_ProcData, WARNING, ucDataType %d is Abnormal!", ucDataType);
                break;
        }

        /*ͳ��*/
        ulDealTotalCnt += ulDealCurCnt;

        if ( ulDealTotalCnt > g_PppHdlcHardStat.ulMaxCntOnce )
        {
            g_PppHdlcHardStat.ulMaxCntOnce = ulDealTotalCnt;
        }

        if (VOS_OK != ulDealResult)
        {
            PPP_MNTN_LOG(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                         "PPP_HDLC_HARD_ProcData, WARNING, ulDealResult = ERROR!");
            break;
        }

        /*���ѭ������Ľ����������˶���һ�����������������
          ���˳�ѭ��������PPP_DATA_PROC_NOTIFY��Ϣ*/
        if ( (ulDealTotalCnt >= PPP_ONCE_DEAL_MAX_CNT) )
        {
            g_PppHdlcHardStat.ulContinueCnt++;
            return PPP_HDLC_RESULT_COMM_CONTINUE;
        }
    } /* for (;;) */

    return PPP_HDLC_RESULT_COMM_ERROR;
}


VOS_UINT32 PPP_HDLC_HARD_SendAsFrmPacketMsg
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
)
{
    HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU    *pstMsg;
    VOS_UINT32                               ulLength;


    ulLength    = sizeof(HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU *)PS_ALLOC_MSG(PS_PID_APP_PPP, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                        "PPP_HDLC_HARD_SendMsg, ERROR: PS_ALLOC_MSG Failed!\r\n");
        return VOS_ERR;
    }

    /*��д��Ϣͷ:*/
    pstMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid     = PS_PID_APP_PPP;
    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = PS_PID_APP_PPP;
    pstMsg->MsgHeader.ulLength        = ulLength;

    pstMsg->MsgHeader.ulMsgName       = PPP_HDLC_PROC_AS_FRM_PACKET_IND;
    /*��д��Ϣ��:*/
    pstMsg->usPppId                   = usPppId;
    pstMsg->usProtocol                = usProtocol;
    pstMsg->pstMem                    = pstMem;

    /*���͸���Ϣ*/
    if (VOS_OK != PS_SEND_MSG(PS_PID_APP_PPP, pstMsg))
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                        "PPP_HDLC_HARD_SendAsFrmPacketMsg, ERROR : PS_SEND_MSG Failed!");
        PPP_MemFree(pstMem);
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID PPP_HDLC_HARD_ProcAsFrmPacket
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
)
{
    VOS_UINT32              ulDealCurCnt;
    PPP_ZC_QUEUE_STRU       stDataQ;
    struct link            *pstLink;
    VOS_UINT32              ulDealResult;

    pstLink = PPP_LINK(usPppId);

    ulDealCurCnt = 0;

    /* ��װ������IP�������ݰ� */
    PPP_ZC_SET_DATA_APP(pstMem, (VOS_UINT16)(usPppId << 8) | (VOS_UINT16)PPP_PUSH_PACKET_TYPE);

    /* ��ʼ������stDataQ, ���� pstMem ��� */
    PPP_ZC_QUEUE_INIT(&stDataQ);
    PPP_ZC_ENQUEUE_TAIL(&stDataQ, pstMem);

    /* ֱ�ӽ������ݰ���װ���͸�PC */
    ulDealResult = PPP_HDLC_HARD_FrmPacket(usPppId, usProtocol, pstLink, &stDataQ, &ulDealCurCnt);

    if ((VOS_OK != ulDealResult) || (1 != ulDealCurCnt))
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_ERROR,
                      "PPP_HDLC_HARD_MakeFrmPacket, ERROR, ulDealResult %d ulDealCurCnt %d!\r\n",
                      ulDealResult, ulDealCurCnt);

        /* ˵����ĳ�ִ���������û�дӶ������Ƴ�����Ҫ�ͷ� */
        if (0 < PPP_ZC_GET_QUEUE_LEN(&stDataQ))
        {
            PPP_MemFree(pstMem);
        }

        return;
    }

    g_PppHdlcHardStat.ulFrmIpDataProcCnt++;

    return;
}


VOS_VOID PPP_HDLC_HARD_ProcProtocolPacket
(
    struct link     *pstLink,
    struct ppp_mbuf *pstMbuf,
    VOS_INT32        ulPri,
    VOS_UINT16       usProtocol
)
{
    PPP_ZC_STRU            *pstMem;
    VOS_UINT16              usPppId;
    VOS_UINT32              ulFrmResult;
    VOS_UINT32              ulDefResult;


    usPppId = (VOS_UINT16)PPP_LINK_TO_ID(pstLink);

    pstMem  = ppp_m_alloc_ttfmem_from_mbuf(pstMbuf);

    ppp_m_freem(pstMbuf);
    pstMbuf  = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstMem)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "PPP_HDLC_HARD_ProcProtocolPacket, WARNING, pstMem is NULL!\r\n");
        return;
    }

    /* PPPЭ��ջ�ظ���Э�̰���Ҫ��װ�󷢸�PC��ȷ�ϴ�ʱ�Ƿ��װ����װ���Ѿ���� */
    ulFrmResult     = PPP_HDLC_HARD_FrmIsEnabled();
    ulDefResult     = PPP_HDLC_HARD_DefIsEnabled();

    /* �˺��������н��Э�̰�ʱ��PPPЭ��ջ����Ӧ�����ʱ���װ��Ӧ��ʹ�� */
    if( (VOS_TRUE == ulFrmResult) || (VOS_TRUE == ulDefResult) )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_HDLC_HARD_ProcProtocolPacket, WARNING, ulFrmResult %d, ulDefResult %d!\r\n",
                      ulFrmResult, ulDefResult);
        PPP_HDLC_HARD_SendAsFrmPacketMsg(usPppId, usProtocol, pstMem);

        return;
    }

    /* �´�PPP������ȵ�ʱ���ٷ�װ��Э�̣���ʱ��װ����װ��δʹ�� */
    PPP_HDLC_HARD_ProcAsFrmPacket(usPppId, usProtocol, pstMem);

    return;
}

VOID PPP_Help(VOID)
{
    vos_printf("********************PPP�����Ϣ************************\n");
    vos_printf("PPP_HDLC_HARD_MntnShowStatInfo           ��ӡͳ����Ϣ\n");
    vos_printf("PPP_INPUT_ShowStatInfo                   ��ӡ g_PppDataQCtrl��Ϣ\n");
    vos_printf("PPP_HDLC_HARD_MntnSetConfig              ���ÿ�ά�ɲ�ȼ�:\n");
    vos_printf("                                         1--������2--�Ĵ�����4--����\n");
    vos_printf("PPP_HDLC_HARD_MntnShowDefReg             ��ӡ���װ�Ĵ�����Ϣ\n");
    vos_printf("PPP_HDLC_HARD_MntnShowFrmReg             ��ӡ��װ�Ĵ�����Ϣ\n");
    vos_printf("PPP_HDLC_HARD_MntnSetDefIntLimit         ���ý��װ�ж�ˮ��\n");
    vos_printf("PPP_HDLC_HARD_MntnSetFrmIntLimit         ���÷�װ�ж�ˮ��\n");
    vos_printf("PPP_HDLC_HARD_MntnShowConfigInfo         ��ӡ������Ϣ\n");

    return;
}


VOS_UINT32 PPP_PHY_TO_VIRT(unsigned int ulPAddr)
{
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    if ((ulPAddr >= g_ulPppPhyAddr) && (ulPAddr <= (g_ulPppPhyAddr + TTF_HDLC_MASTER_LINK_TOTAL_LEN)))
    {
        return TTF_PHY_TO_VIRT(ulPAddr);
    }
    else
    {
        return phys_to_virt(ulPAddr);
    }
#else
    return TTF_PHY_TO_VIRT(ulPAddr);
#endif
}


VOS_UINT32 PPP_VIRT_TO_PHY(unsigned int ulVAddr)
{
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    if ((ulVAddr >= g_ulPppVirtAddr) && (ulVAddr <= (g_ulPppVirtAddr + TTF_HDLC_MASTER_LINK_TOTAL_LEN)))
    {
        return TTF_VIRT_TO_PHY(ulVAddr);
    }
    else
    {
        return virt_to_phys(ulVAddr);
    }
#else
    return TTF_VIRT_TO_PHY(ulVAddr);
#endif
}



#else
/*****************************************************************************
   1 Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_HDLC_HARDWARE_C
/*lint +e767 */

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/
#if (VOS_OS_VER == VOS_WIN32)
extern VOS_UINT32 VHW_HDLC_Task( VOS_VOID );
#endif

extern VOS_UINT32 PPP_SendPushedData(VOS_UINT16 usPppId, VOS_UINT8 *pucDataBuf, VOS_UINT16 usLen);
/*****************************************************************************
   3 ˽�ж���
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulFramerCfg;
    VOS_UINT32 ulFramerAccm;
    VOS_UINT32 ulFramerCtrl;
    VOS_UINT32 ulFramerStatus;
} HDLC_RegFramer_STRU;

typedef struct
{
    VOS_UINT32 ulDeframerCfg;
    VOS_UINT32 ulDeframerCtrl;
    VOS_UINT32 ulDeframerGoOn;
    VOS_UINT32 ulDeframerStatus;
} HDLC_RegDeframer_STRU;

typedef struct
{
    VOS_UINT32 ulFramerCtrl;
    VOS_UINT32 ulFramerStatus;
    VOS_UINT8  ucFramerIn[4];
    VOS_UINT8  ucFramerOut[4];
} HDLC_RegFramerCntInOut_STRU;

typedef struct
{
    VOS_UINT32 ulFramerCfg;
    VOS_UINT32 ulFramerAccm;
    VOS_UINT32 ulFramerGroupCnt;
    HDLC_RegFramerCntInOut_STRU astRegFramerInOut[6];    /* ��װ���6��: 1502 / 256 + 1 */
} HDLC_RegFramerCnt_STRU;

typedef struct
{
    VOS_UINT32 ulDeframerCfg[52];    /* һ�������52֡ */
    VOS_UINT32 ulDeframerCtrl;
    VOS_UINT32 ulDeframerStatus[52];
    VOS_UINT32 ulDeframerGoOnCnt;
} HDLC_RegDeframerCntInOut_STRU;

typedef struct

{
    HDLC_RegDeframerCntInOut_STRU astRegDeframerInOut[16];    /* ���װ���16��: 4096 /256 */
    VOS_UINT32 ulDeframerGroupCnt;
} HDLC_RegDeframerCnt_STRU;

typedef struct
{
    VOS_UINT32                  ulUplinkIpDataProcCnt;             /* ����IP���ݰ�������� */
    VOS_UINT32                  ulUplinkPppDataProcCnt;            /* ���м�PPP֡������� */

    VOS_UINT32                  ulDownlinkIpDataProcCnt;           /* ����IP���ݰ�������� */
    VOS_UINT32                  ulDownlinkPppDataProcCnt;          /* ���м�PPP֡������� */

    VOS_UINT32                  ulMaxCntOnce;                      /* PPPһ����ദ��Ľ����� */
} PPP_HDLC_HARD_DATA_PROC_STAT_ST;

/*****************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/
extern PPP_DATA_Q_CTRL_ST       g_PppDataQCtrl;

VOS_UINT32                      g_ulHDLCIPBaseAddr = 0;

HDLC_RegFramer_STRU             stRegFramer;
HDLC_RegDeframer_STRU           stRegDeframer;
VOS_UINT32                      ulHDLCIsrStatus;
VOS_UINT32                      ulHDLCIsrRawData;

PPP_HDLC_HARD_DATA_PROC_STAT_ST g_PppHdlcHardStat = {0};

/* �����װĿ�Ŀռ�ʧ�ܶ�ʱ����� */
/* HDLC���������Ϣ */
HDLC_CONFIG_INFO_STRU           g_stHdlcConfigInfo  =
{
    0,
    0,
    0,
    0,
    0,
    1000,
    1000,
    VOS_NULL_PTR,
    0
};

VOS_UINT32  g_ulPppVirtAddr;
VOS_UINT32  g_ulPppPhyAddr;


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
VOS_VOID    PPP_PrintHardStatInfo(VOS_VOID)
{
    vos_printf("\n================HDLC Hardware STAT INFO Begin==========================\n");

    vos_printf("��������IP�������ݸ���    = %d\n", g_PppHdlcHardStat.ulUplinkIpDataProcCnt);
    vos_printf("��������PPP�������ݸ���   = %d\n", g_PppHdlcHardStat.ulUplinkPppDataProcCnt);
    vos_printf("��������IP�������ݸ���    = %d\n", g_PppHdlcHardStat.ulDownlinkIpDataProcCnt);
    vos_printf("��������PPP�������ݸ���   = %d\n", g_PppHdlcHardStat.ulDownlinkPppDataProcCnt);
    vos_printf("���δ�������������   = %d\n", g_PppHdlcHardStat.ulMaxCntOnce);

    vos_printf("================HDLC Hardware STAT INFO End==========================\n");
}


VOS_UINT32 PPP_HDLC_HARD_Init(VOS_VOID)
{
    link_HDLCInit();

    return VOS_OK;
}


VOS_VOID PPP_HDLC_HARD_SetUp(PPP_ID usPppId)
{

    return;
}


VOS_VOID PPP_HDLC_HARD_Disable(VOS_VOID)
{
    link_HDLCDisable();
}


VOS_VOID link_HDLCInit(VOS_VOID)
{
    HDLC_INTERRUPT_CFG_STRU   stHDLCInterruptCfg;
    HDLC_INTERRUPT_CFG_STRU  *pstHDLCInterruptCfg = &stHDLCInterruptCfg;
    VOS_UINT32                ulInterruptEnable = 0UL;
    VOS_UINT32                ulBaseAddr;

    /*��HDLCʹ��*/
    SOC_AMR_HDLC_ENABLE();

    ulBaseAddr = DRV_GET_IP_BASE_ADDR(BSP_IP_TYPE_HDLC);

    g_ulHDLCIPBaseAddr = IO_ADDRESS(ulBaseAddr);

    stHDLCInterruptCfg.enFramerErrorEnable = PS_TRUE;
    stHDLCInterruptCfg.enFramerDataLessEnable = PS_TRUE;
    stHDLCInterruptCfg.enFramerDataMoreEnable = PS_TRUE;

    stHDLCInterruptCfg.enDeframerErrorEnable = PS_TRUE;
    stHDLCInterruptCfg.enDeframerDataLessEnable = PS_TRUE;
    stHDLCInterruptCfg.enDeframerDataMoreEnable = PS_TRUE;

    /* ����ʱ��Ҫ����Ӧ�ļĴ��� */
    if (PS_TRUE == pstHDLCInterruptCfg->enFramerDataLessEnable)
    {
        SET_BIT_TO_DWORD(ulInterruptEnable, HDLC_INTERRUPT_FRAMER_DATA_LEN_SHORT_ERR_EN_BITPOS);
    }

    if (PS_TRUE == pstHDLCInterruptCfg->enFramerDataMoreEnable)
    {
        SET_BIT_TO_DWORD(ulInterruptEnable, HDLC_INTERRUPT_FRAMER_DATA_LEN_LONG_ERR_EN_BITPOS);
    }

    if (PS_TRUE == pstHDLCInterruptCfg->enFramerErrorEnable)
    {
        SET_BIT_TO_DWORD(ulInterruptEnable, HDLC_INTERRUPT_FRAMER_PARA_ERR_EN_BITPOS);
    }

    if (PS_TRUE == pstHDLCInterruptCfg->enDeframerDataLessEnable)
    {
        SET_BIT_TO_DWORD(ulInterruptEnable, HDLC_INTERRUPT_DEFRAMER_DATA_LEN_SHORT_ERR_EN_BITPOS);
    }

    if (PS_TRUE == pstHDLCInterruptCfg->enDeframerDataMoreEnable)
    {
        SET_BIT_TO_DWORD(ulInterruptEnable, HDLC_INTERRUPT_DEFRAMER_DATA_LEN_LONG_ERR_EN_BITPOS);
    }

    if (PS_TRUE == pstHDLCInterruptCfg->enDeframerErrorEnable)
    {
        SET_BIT_TO_DWORD(ulInterruptEnable, HDLC_INTERRUPT_DEFRAMER_PARA_ERR_EN_BITPOS);
    }

    TTF_WRITE_32REG(SOC_ARM_HDLC_INTERRUPT_ENABLE_ADDR(g_ulHDLCIPBaseAddr),ulInterruptEnable);
}    /* link_HDLCInit */



VOS_VOID link_ReadFramerLastRecord()
{
    vos_printf("ulHDLCIsrStatus is 0x%x \r\n", (VOS_INT32)ulHDLCIsrStatus);
    vos_printf("ulHDLCIsrRawData is 0x%x \r\n", (VOS_INT32)ulHDLCIsrRawData);
    vos_printf("ulFramerCfg is 0x%x \r\n", (VOS_INT32)stRegFramer.ulFramerCfg);
    vos_printf("ulFramerAccm is 0x%x \r\n", (VOS_INT32)stRegFramer.ulFramerAccm);
    vos_printf("ulFramerCtrl is 0x%x \r\n", (VOS_INT32)stRegFramer.ulFramerCtrl);
    vos_printf("ulFramerStatus is 0x%x \r\n", (VOS_INT32)stRegFramer.ulFramerStatus);

    vos_printf("ulDeframerCfg is 0x%x\r\n", (VOS_INT32)stRegDeframer.ulDeframerCfg);
    vos_printf("ulDeframerCtrl is 0x%x\r\n", (VOS_INT32)stRegDeframer.ulDeframerCtrl);
    vos_printf("ulDeframerStatus is 0x%x\r\n", (VOS_INT32)stRegDeframer.ulDeframerStatus);
}    /* link_ReadFramerLastRecord */


VOS_VOID link_HDLCFramerRegRead()
{
    stRegFramer.ulFramerCfg     = TTF_READ_32REG(SOC_ARM_HDLC_FRAMER_CFG_ADDR(g_ulHDLCIPBaseAddr));

    stRegFramer.ulFramerAccm    = TTF_READ_32REG(SOC_ARM_HDLC_FRAMER_ACCM_ADDR(g_ulHDLCIPBaseAddr));

    stRegFramer.ulFramerCtrl    = TTF_READ_32REG(SOC_ARM_HDLC_FRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr));

    stRegFramer.ulFramerStatus  = TTF_READ_32REG(SOC_ARM_HDLC_FRAMER_STATUS_ADDR(g_ulHDLCIPBaseAddr));
}    /* link_HDLCFramerRegRead */


VOS_VOID link_HDLCDeframerRegRead()
{
    stRegDeframer.ulDeframerCfg     = TTF_READ_32REG(SOC_ARM_HDLC_DEFRAMER_CFG_ADDR(g_ulHDLCIPBaseAddr));

    stRegDeframer.ulDeframerCtrl    = TTF_READ_32REG(SOC_ARM_HDLC_DEFRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr));

    stRegDeframer.ulDeframerStatus  = TTF_READ_32REG(SOC_ARM_HDLC_DEFRAMER_STATUS_ADDR(g_ulHDLCIPBaseAddr));
}    /* link_HDLCDeframerRegRead */


VOS_VOID link_HDLCIsrRegRead()
{
    ulHDLCIsrRawData    = TTF_READ_32REG(SOC_ARM_HDLC_INTERRUPT_FRAMER_RAW_INT_ADDR(g_ulHDLCIPBaseAddr));
    ulHDLCIsrStatus     = TTF_READ_32REG(SOC_ARM_HDLC_INTERRUPT_INT_STATUS_ADDR(g_ulHDLCIPBaseAddr));
}    /* link_HDLCIsrRegRead */


VOS_VOID link_HDLCReset(VOS_UINT32 ulHDLCModule,
                        HDLC_RESET_REASON_ENUM_UINT8 enResetReason)
{
#if 0    /* for release */
    VOS_UINT32 ulCfg;
    volatile VOS_UINT32 *pulRttMem;
#endif
    VOS_UINT32   ulTaskID;

    if (HDLC_FRAMER_MODULE == ulHDLCModule)
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "Framer reset reason: %d\r\n", enResetReason);

#if 1    /* for debug */
        /* ��ȡHDLC�Ĵ�����ֵ */
        link_HDLCIsrRegRead();

        /* ��ȡFramer������� */
        link_HDLCFramerRegRead();

        link_ReadFramerLastRecord();
#else    /* for release */
        /* Disable Framer */
        ulCfg = 0UL;      /* frm_en is in bit0 */


        TTF_WRITE_32REG(SOC_ARM_HDLC_FRAMER_CFG_ADDR,ulCfg);

        /* Enable Framer */
        SET_BIT_TO_DWORD(ulCfg, HDLC_FRAMER_CFG_EN_BITPOS);
        TTF_WRITE_32REG(SOC_ARM_HDLC_FRAMER_CFG_ADDR,ulCfg);
#endif
    }

    if (HDLC_DEFRAMER_MODULE == ulHDLCModule)
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"Deframer reset reason: %d\r\n", enResetReason);

#if 1    /* for debug */
        /* ��ȡHDLC�Ĵ�����ֵ */
        link_HDLCIsrRegRead();

        /* ��ȡDeframer������� */
        link_HDLCDeframerRegRead();

        link_ReadFramerLastRecord();
#else    /* for release */
        /* Disable Deframer */
        ulCfg = 0UL;      /* def_en is in bit0 */
        TTF_WRITE_32REG(SOC_ARM_HDLC_DEFRAMER_CFG_ADDR,ulCfg);

        /* Enable Deframer */
        SET_BIT_TO_DWORD(ulCfg, HDLC_DEFRAMER_CFG_EN_BITPOS);
        TTF_WRITE_32REG(SOC_ARM_HDLC_DEFRAMER_CFG_ADDR,ulCfg);
#endif
    }

    ulTaskID = VOS_GetCurrentTaskID();

    if ( VOS_OK != VOS_SuspendTask( ulTaskID ) )
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,"# SUSPED PPP task error.\r\n");
    }
}    /* link_HDLCReset */


VOS_VOID link_HDLC_Enable(VOS_VOID)
{
    #if 0
    VOS_UINT32 ulReg;
    VOS_INT32  intLockLevel;

    intLockLevel = VOS_SplIMP();

    ulReg = TTF_READ_32REG(SOC_SC_PERIPH_CLKEN0_REG);

    ulReg |= 1 << SOC_SC_PERIPH_CLK_HDLC_BIT;

    TTF_WRITE_32REG(SOC_SC_PERIPH_CLKEN0_REG, ulReg);

    VOS_Splx(intLockLevel);
    #endif

    return;
}

VOS_VOID link_HDLC_Disable(VOS_VOID)
{
    #if 0
    VOS_UINT32 ulReg;
    VOS_INT32  intLockLevel;

    intLockLevel = VOS_SplIMP();

    ulReg = TTF_READ_32REG(SOC_SC_PERIPH_CLKDIS0_REG);

    ulReg |= 1 << SOC_SC_PERIPH_CLK_HDLC_BIT;

    TTF_WRITE_32REG(SOC_SC_PERIPH_CLKDIS0_REG, ulReg);

    VOS_Splx(intLockLevel);
    #endif

    return;
}


VOS_VOID link_HDLCDisable(VOS_VOID)
{
    /* ��ΪAt_ModemRelInd��Ҫ����link_HDLCDisable,
       ��NAS����Ҫ���ܼ���PPP_HDLC_BY_HARDWARE�ĺ꿪�ص�AT������
       (����PPP��ص�ͷ�ļ��İ���),
       Ϊ���ܹ�����ͨ��, ֻ���ں���link_HDLCDisable�ڲ�����PPP_HDLC_BY_HARDWARE
       ��PPP_HDLC_BY_SOFTWARE */
    VOS_UINT32 ulCfg;

    /* Disable Framer */
    ulCfg = 0UL;      /* frm_en is in bit0 */
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRAMER_CFG_ADDR(g_ulHDLCIPBaseAddr),ulCfg);

    /* Disable Deframer */
    ulCfg = 0UL;      /* def_en is in bit0 */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEFRAMER_CFG_ADDR(g_ulHDLCIPBaseAddr),ulCfg);
}    /* link_HDLCDisable */



VOS_UINT32 link_HDLCFramer(HDLC_FRAMER_PPP_LINK_PARA_STRU *pstHdlcFramerPppPara,
                           HDLC_FRAMER_PARA_STRU *pstHdlcFramerPara)
{
    VOS_UINT32  ulDataLen;
    VOS_UINT8   ucFramerBlkCnt;         /* ����·����ݷ������� */
    VOS_UINT8   ucPComp;
    VOS_UINT8   ucACComp;
    VOS_UINT8   ucLowByte;
    VOS_UINT16  usLowWord;
    VOS_UINT16  usProtocol;
    VOS_UINT32  ulFramerCfg;            /* ��װ���� */
    VOS_UINT32  ulACCM;
    VOS_UINT32  ulDataLoop;             /* �����ǰ�·����ݵ����, ����ֵ��1��ʼ���� */
    VOS_UINT8  *pucCurrOutData;         /* ��װ�������д��˵�ַ */
    VOS_UINT16  usCurrWrited;           /* ����д�����ݵ��ֽ��� */
    VOS_UINT32  ulFrameRsltWaitNum;     /* ��ֹӲ���쳣�ı������� */
    volatile VOS_UINT32  ulFramerStatus;         /* ��װ״̬ */
    VOS_UINT16  usFrameBlkLen;          /* ����·�һ�����ݱ���װ��ĳ���, ��λ: �ֽ� */
    VOS_UINT16  usFrameByteCnt = 0;         /* ��ȡ�������ܳ� */
    PPP_ZC_STRU   **ppstMem;
    const VOS_UINT16 usByteAllowed = HDLC_FRAMER_IN_PER_MAX_CNT;    /* �����Ӳ��Լ��һ���·����ó���256Bytes */

    /* ��ֹ�������ݹ��� */
    ulDataLen = pstHdlcFramerPara->stInData.ulDataLen;
    if (HDLC_FRAMER_IN_PER_FRAME_MAX_USED_BYTES < ulDataLen)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "Framer data too long\r\n");

        pstHdlcFramerPara->stOutData.usFrameByteCnt = 0;
        return VOS_ERR;
    }

    /* ���㵱ǰ֡��ָ��������з�װ */
    ucFramerBlkCnt = (VOS_UINT8)(((ulDataLen + usByteAllowed) - 1) / usByteAllowed);

    /* ��ȡAC��ѹ��ָʾ, P��ѹ��ָʾ, Э��ֵ, ACCM */
    ucACComp = (PS_TRUE == pstHdlcFramerPara->enACComp) ? 1 : 0;
    if (HDLC_IP_MODE == pstHdlcFramerPara->ucMode)  /* IPģʽ: P�򲻺��� */
    {
        ucPComp = (PS_TRUE == pstHdlcFramerPara->enPComp)
                   ? HDLC_PROTOCOL_ADD_WITH_COMPRESS
                   : HDLC_PROTOCOL_ADD_WITHOUT_COMPRESS;
    }
    else    /* PPPģʽ: P����� */
    {
        ucPComp = HDLC_PROTOCOL_NO_ADD;
    }

    usProtocol = pstHdlcFramerPara->usProtocol;
    ulACCM = pstHdlcFramerPara->ulACCM;

    /* ����accm */
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRAMER_ACCM_ADDR(g_ulHDLCIPBaseAddr),ulACCM);

    /* ��ucPComp���õ�һ���ֽڵĵ�2, 3λ�� */
    ucLowByte = SET_BITS_VALUE_TO_BYTE(ucPComp, (VOS_UINT8)HDLC_FRAMER_CFG_PFC_MOVEBITS_LEN);

    if (1 == ucACComp)  /* AC��ѹ�� */
    {
        SET_BIT_TO_BYTE(ucLowByte, HDLC_FRAMER_CFG_ACFC_BITPOS);
    }
    else
    {
        CLEAR_BIT_TO_BYTE(ucLowByte, HDLC_FRAMER_CFG_ACFC_BITPOS);
    }
    SET_BIT_TO_BYTE(ucLowByte, HDLC_FRAMER_CFG_EN_BITPOS);

    usLowWord = HDLC_MAKE_WORD(0x00, ucLowByte);
    ulFramerCfg = HDLC_MAKE_DWORD(usProtocol, usLowWord);

    /* ����AC��ѹ��ָʾ, P��ѹ��ָʾ, Э��ֵ��ʹ�ܷ�װ���, accm */
    TTF_WRITE_32REG(SOC_ARM_HDLC_FRAMER_CFG_ADDR(g_ulHDLCIPBaseAddr),ulFramerCfg);

    pucCurrOutData = pstHdlcFramerPara->stOutData.pucData;

    for (ulDataLoop = 1UL; ulDataLoop <= (VOS_UINT32)ucFramerBlkCnt; ulDataLoop ++)    /* һ֡�Ƿ�����������Ҫ��װ */
    {
        /*
           ����һ���·����ݵĳ���,
           ����·�һ�����ݵĳ��ȷ�Χ[1,256]Bytes, ��0x01��ʾ����Ϊ1Bytes, 0x100��ʾ256Bytes
        */
        if (ulDataLoop != (VOS_UINT32)ucFramerBlkCnt)
        {
            /* �����һ��, һ����256�ֽ� */
            usCurrWrited = usByteAllowed;
        }
        else
        {
            usCurrWrited = (VOS_UINT16)(ulDataLen - ((ulDataLoop-1) * usByteAllowed));
        }

        /*set new bitpos(bit0), blkCnt(8~10), blkIndex(12~14)*/
        /*
        0:frm_blk_new
        8-10:frm_blk_num
        12-14:frm_blk_index
        16-26:frm_blk_length
        */
        TTF_Write32RegByBit(SOC_ARM_HDLC_FRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr), 8, 10, ucFramerBlkCnt);
        TTF_Write32RegByBit(SOC_ARM_HDLC_FRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr), 12, 14, ulDataLoop);
        TTF_Write32RegByBit(SOC_ARM_HDLC_FRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr), 16, 26, usCurrWrited);
        TTF_Write32RegByBit(SOC_ARM_HDLC_FRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr), 0, 0, 1);

        /* ����memcpy����, ���ָ���֡����, ������Bufferд��,
           Ϊ�˼ӿ���������ٶ�, m_buf��TTF_MEM�����ü��з�ʽ������ȡ�ߵ�HDLC */
        ppstMem = &(pstHdlcFramerPara->stInData.pstMem);

        PPP_MemCutHeadData( ppstMem, (VOS_UINT8 *)(SOC_ARM_HDLC_FRAMER_IN_DATA_ADDR(g_ulHDLCIPBaseAddr)),
                            usCurrWrited);

        /* ��frm_block_new��0, ָʾӲ������Ѿ�����ǰ���·����� */
        TTF_Write32RegByBit(SOC_ARM_HDLC_FRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr), 0, 0, 0);

        #if (VOS_OS_VER == VOS_WIN32)
        VHW_HDLC_Task();
        #endif

        /* �жϵ�ǰ���Ƿ��װ��� */
        ulFrameRsltWaitNum = 0UL;
        while (ulFrameRsltWaitNum < HDLC_FRAMER_MAX_WAIT_RESULT_NUM)
        {
            ulFramerStatus = TTF_READ_32REG(SOC_ARM_HDLC_FRAMER_STATUS_ADDR(g_ulHDLCIPBaseAddr));    /* ��ȡ��ǰ����һ�����װ���ݵ�״̬ */

            if (HDLC_FRAMER_BLOCK_DONE
                == (VOS_UINT8)GET_BITS_FROM_DWORD(ulFramerStatus, HDLC_FRAMER_BLOCK_DONE_MASK))   /* a framer block done */
            {
                break ;
            }

            ulFrameRsltWaitNum ++;
        }

        if ( HDLC_FRAMER_MAX_WAIT_RESULT_NUM != ulFrameRsltWaitNum )
        {
            /*blklen: bit 16~27*/
            usFrameBlkLen = (VOS_UINT16)TTF_Read32RegByBit(SOC_ARM_HDLC_FRAMER_STATUS_ADDR(g_ulHDLCIPBaseAddr), 16, 27);

            if (HDLC_FRAMER_OUT_PER_MAX_CNT < usFrameBlkLen)
            {
                /* �������ݳ���, ��Ϊ�쳣 */
                link_HDLCReset(HDLC_FRAMER_MODULE, HDLC_FRAMER_OUT_PER_LONG_ERR);

                pstHdlcFramerPara->stOutData.usFrameByteCnt = 0;
                return VOS_ERR;
            }

            /* ����˴ο������ȡ�������ܳ�, ��λ: �ֽ� */
            usFrameByteCnt
                = (VOS_UINT16)((pucCurrOutData + usFrameBlkLen) - pstHdlcFramerPara->stOutData.pucData);

            if (HDLCSIZE < usFrameByteCnt)     /* to avoid array overflow */
            {
                /* �����ܳ�����, ��Ϊ�쳣 */
                link_HDLCReset(HDLC_FRAMER_MODULE, HDLC_FRAMER_OUT_ALL_LONG_ERR);

                pstHdlcFramerPara->stOutData.usFrameByteCnt = 0;
                return VOS_ERR;
            }
            else
            {
                /* ��HDLC Framer���� */

                pstHdlcFramerPara->stOutData.pucData = (VOS_UINT8 *)(SOC_ARM_HDLC_FRAMER_OUT_DATA_ADDR(g_ulHDLCIPBaseAddr));
                pucCurrOutData += usFrameBlkLen;
            }
        }
        else    /* HDLC Framer ����ʱ�����, ��Ϊ�쳣 */
        {
            link_HDLCReset(HDLC_FRAMER_MODULE, HDLC_FRAMER_WORK_TIME_LONG_ERR);

            pstHdlcFramerPara->stOutData.usFrameByteCnt = 0;
            return VOS_ERR;
        }
    }   /* end of while loop */

    pstHdlcFramerPara->stOutData.usFrameByteCnt = usFrameByteCnt;

    return VOS_OK;
}   /* link_HDLCFramer */



VOS_VOID link_HDLCPushPacket
(
    struct link    *l,
    PPP_ZC_STRU    *pstInData,
    VOS_INT32       pri,
    VOS_UINT16      usProtocol
)
{
    VOS_UINT32              ulFramerCfg;
    VOS_UINT32              ulFramerCtrl;
    VOS_UINT8              *pucTmpSrcData;
    VOS_UINT32              ulFrameRsltWaitNum; /* ��ֹӲ���쳣�ı������� */
    volatile VOS_UINT32     ulFramerStatus;     /* ��װ״̬ */
    VOS_UINT16              usFrameBlkLen;
    VOS_UINT16              usDataLen;


    /* �������ݳ��� */
    usDataLen = PPP_ZC_GET_DATA_LEN(pstInData);

    if ((0 == usDataLen) || (HDLC_FRAMER_IN_PER_FRAME_MAX_USED_BYTES < usDataLen))
    {
        PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "IP mode framer data len wrong %d\r\n", usDataLen);
        PPP_MemFree(pstInData);

        return ;
    }

    /*=========================================================================
      ulFramerCfg:  bit[0]          ʹ��λ       1Ϊʹ��,0Ϊ��ʹ��
                    bit[1]          AC��ѹ��λ   1ΪAC��ѹ��,0ΪAC��ѹ��
                    bit[2]-bit[3]   P��ѹ��ָʾ  00,Ӳ��ģ�����P��,P��ѹ��
                                                  01,Ӳ��ģ�����P��,P��ѹ��
                                                  11,Ӳ��ģ�鲻���P��
                    bit[16]-bit[31] ��װЭ��ֵ

      IPģʽһ�����P��,PPPģʽһ�������P��
      LCP֡: AC��ѹ����P��ѹ��
    ==========================================================================*/
    ulFramerCfg = 0x01;
    if (PROTO_LCP != usProtocol)
    {
        if (1 == l->lcp.his_acfcomp)
        {
            ulFramerCfg |= (1 << 1);
        }

        if (1 == l->lcp.his_protocomp)
        {
            ulFramerCfg |= (1 << 2);
        }
    }

    ulFramerCfg |= ( ((VOS_UINT32)usProtocol) << 16 );

    *(VOS_UINT32 *)(SOC_ARM_HDLC_FRAMER_CFG_ADDR(g_ulHDLCIPBaseAddr)) = ulFramerCfg;

    /* ����accm */
    if (PROTO_LCP != usProtocol)
    {
        *(VOS_UINT32 *)(SOC_ARM_HDLC_FRAMER_ACCM_ADDR(g_ulHDLCIPBaseAddr)) = l->lcp.his_accmap;
    }
    else
    {
        *(VOS_UINT32 *)(SOC_ARM_HDLC_FRAMER_ACCM_ADDR(g_ulHDLCIPBaseAddr)) = 0xFFFFFFFF;
    }

    /*=========================================================================
    ulFramerCtrl:
        bit[0]          0 ��ɴ���װ��������,1 ��ʼ����װ��������
        bit[8]-bit[10]  ����װ���ݷ�������,HDLC��ǿ��Ϊ1
        bit[12]-bit[14] ��ǰ�·����ݵ����,HDLC��ǿ��Ϊ1
        bit[16]-bit[26] �·�һ�����װ���ݵĳ���
    ==========================================================================*/
    ulFramerCtrl = (0x1101 | (((VOS_UINT32)usDataLen) << 16));

    *(VOS_UINT32 *)(SOC_ARM_HDLC_FRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr)) = ulFramerCtrl;

    pucTmpSrcData   = (VOS_UINT8 *)(SOC_ARM_HDLC_FRAMER_IN_DATA_ADDR(g_ulHDLCIPBaseAddr));

    /* �㿽��Ŀǰ�ݲ�֧����ʽ�ṹ */
    /*
    while (VOS_NULL_PTR != pstMem)
    {
    */
        /*��ȡ�����㿽���ṹ������*/
        DRV_RT_MEMCPY(pucTmpSrcData, PPP_ZC_GET_DATA_PTR(pstInData), usDataLen);

        /*pucTmpSrcData += usDataLen;*/

        PPP_MemFree(pstInData);
    /*
    }
    */

    /* ��SOC_ARM_HDLC_FRAMER_CTRL_ADDR��bit 0��0, ָʾӲ������Ѿ�����ǰ���·����� */
    ulFramerCtrl &= 0xFFFFFFFE;
    *(VOS_UINT32 *)(SOC_ARM_HDLC_FRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr)) = ulFramerCtrl;

    #if (VOS_OS_VER == VOS_WIN32)
    VHW_HDLC_Task();
    #endif

    /* �жϵ�ǰ���Ƿ��װ��� */
    ulFrameRsltWaitNum = 0UL;
    while (ulFrameRsltWaitNum < HDLC_FRAMER_MAX_WAIT_RESULT_NUM)
    {
        /* Linux�������Ż���ֻ��һ��ѭ������volatile��ֹ�������Ż� */
        ulFramerStatus = *(volatile VOS_UINT32 *)(SOC_ARM_HDLC_FRAMER_STATUS_ADDR(g_ulHDLCIPBaseAddr));

        if (HDLC_FRAMER_BLOCK_DONE == (ulFramerStatus & 0x01))
        {
            break ;
        }
        ulFrameRsltWaitNum ++;
    }

    if ( HDLC_FRAMER_MAX_WAIT_RESULT_NUM != ulFrameRsltWaitNum )
    {
        /*blklen: bit 16~27*/
        usFrameBlkLen = (VOS_UINT16)((ulFramerStatus & 0x0fff0000) >> 16);

        if (HDLC_FRAMER_OUT_PER_MAX_CNT < usFrameBlkLen)
        {
            /* �������ݳ���, ��Ϊ�쳣 */
            link_HDLCReset(HDLC_FRAMER_MODULE, HDLC_FRAMER_OUT_PER_LONG_ERR);

            return;
        }
    }
    else    /* HDLC Framer ����ʱ�����, ��Ϊ�쳣 */
    {
        link_HDLCReset(HDLC_FRAMER_MODULE, HDLC_FRAMER_WORK_TIME_LONG_ERR);

        return;
    }

    /* TODO:���滻Ϊ����PPP_HDLC_ProcDlData */
    PPP_SendPushedData((VOS_UINT16)PPP_LINK_TO_ID(l),
                          (VOS_UINT8 *)(SOC_ARM_HDLC_FRAMER_OUT_DATA_ADDR(g_ulHDLCIPBaseAddr)),
                          usFrameBlkLen);

    return;
}    /* link_HDLCPushPacket */


VOS_VOID link_HDLCSetDeframerCfg(HDLC_DEFRAMER_PARA_STRU *pstHdlcDeframerPara)
{
    VOS_UINT32       ulDeframerCfg;
    VOS_UINT8        ucACComp;
    VOS_UINT8        ucPComp;
    VOS_UINT8        ucLowByte;
    VOS_UINT16       usLowWord;

    /* ��ȡAC��ѹ��ָʾ, P��ѹ��ָʾ */
    ucACComp = (PS_TRUE == pstHdlcDeframerPara->enACComp) ? 1 : 0;
    if (HDLC_IP_MODE == pstHdlcDeframerPara->ucMode)  /* IPģʽ: P�򲻺��� */
    {
        ucPComp = (PS_TRUE == pstHdlcDeframerPara->enPComp)
                   ? HDLC_PROTOCOL_REMOVE_WITH_COMPRESS
                   : HDLC_PROTOCOL_REMOVE_WITHOUT_COMPRESS;
    }
    else    /* PPPģʽ: P����� */
    {
        ucPComp = HDLC_PROTOCOL_NO_REMOVE;
    }

    /* ��ucPComp���õ�һ���ֽڵĵ�2, 3λ�� */
    ucLowByte = SET_BITS_VALUE_TO_BYTE(ucPComp, HDLC_DEFRAMER_CFG_PFC_MOVEBITS_NUM);

    if (1 == ucACComp)  /* AC��ѹ�� */
    {
        SET_BIT_TO_BYTE(ucLowByte, HDLC_DEFRAMER_CFG_ACFC_BITPOS);
    }
    else
    {
        CLEAR_BIT_TO_BYTE(ucLowByte, HDLC_DEFRAMER_CFG_ACFC_BITPOS);
    }
    SET_BIT_TO_BYTE(ucLowByte, HDLC_DEFRAMER_CFG_EN_BITPOS);

    usLowWord = HDLC_MAKE_WORD(0x00, ucLowByte);
    ulDeframerCfg = HDLC_MAKE_DWORD(0x00, usLowWord);

    /* ����AC��ѹ��ָʾ, P��ѹ��ָʾ, ʹ�ܽ��װ��� */
    TTF_WRITE_32REG(SOC_ARM_HDLC_DEFRAMER_CFG_ADDR(g_ulHDLCIPBaseAddr),ulDeframerCfg);
}    /* link_HDLCSetDeframerCfg */



VOS_VOID link_HDLCDefDealErr(struct link *l, VOS_UINT8 ucErrType)
{
    VOS_UINT8   ucMask;
    VOS_UINT32  ulErrTypeLoop;
    VOS_UINT8   ucResult;
    HDLC_DEFRAMER_ERR_FRAMES_CNT_STRU   stErrCnt;

    /*lint -e734*/
    /* get fcs error count */
    stErrCnt.usFCSErrCnt        = TTF_Read32RegByBit(SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_0_ADDR(g_ulHDLCIPBaseAddr), 0, 15);

    /* get frame too long error count */
    stErrCnt.usLenLongCnt       = TTF_Read32RegByBit(SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_0_ADDR(g_ulHDLCIPBaseAddr), 16, 31);

    /* get frame too short error count */
    stErrCnt.usLenShortCnt      = TTF_Read32RegByBit(SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_1_ADDR(g_ulHDLCIPBaseAddr), 0, 15);

    /* get error protocol count */
    stErrCnt.usErrProtocolCnt   = TTF_Read32RegByBit(SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_1_ADDR(g_ulHDLCIPBaseAddr), 16, 31);

    /* get error control count */
    stErrCnt.usErrCtrlCnt       = TTF_Read32RegByBit(SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_2_ADDR(g_ulHDLCIPBaseAddr), 0, 15);

    /* get error address count */
    stErrCnt.usErrAddrCnt       = TTF_Read32RegByBit(SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_2_ADDR(g_ulHDLCIPBaseAddr), 16, 31);

    /* get error flag position count */
    stErrCnt.usFlagPosErrCnt    = TTF_Read32RegByBit(SOC_ARM_HDLC_DEFRAMER_ERROR_INFO_3_ADDR(g_ulHDLCIPBaseAddr), 0, 15);
    /*lint +e734*/
    for (ulErrTypeLoop = 0UL; ulErrTypeLoop < HDLC_DEFRAMER_MAX_TYPE_CNT; ulErrTypeLoop ++)
    {
        ucMask = SET_BITS_VALUE_TO_BYTE(0x01, ulErrTypeLoop);    /* �������� */
        ucResult = (VOS_UINT8)GET_BITS_FROM_BYTE(ucErrType, ucMask);

        if (0 != ucResult)      /* ���ڴ������ */
        {
            if (0UL == ulErrTypeLoop)   /* ��������0: CRCУ����� */
            {
                l->hdlc.stats.badfcs       += stErrCnt.usFCSErrCnt;
                l->hdlc.lqm.SaveInErrors   += stErrCnt.usFCSErrCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "bad hdlc fcs\r\n");
            }
            else if (1UL == ulErrTypeLoop)    /* ��������1: ���װ��֡�ֽ�������1502bytes */
            {
                l->hdlc.lqm.SaveInErrors += stErrCnt.usLenLongCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "bad hdlc frame length too long\r\n");
            }
            else if (2UL == ulErrTypeLoop)    /* ��������2: ���װ��֡�ֽ���С��4bytes */
            {
                l->hdlc.lqm.SaveInErrors += stErrCnt.usLenShortCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "bad hdlc frame length too short\r\n");
            }
            else if (3UL == ulErrTypeLoop)    /* ��������3: ��P�������ʱ, �յ��Ƿ���Protocol��ֵ(��*******0 *******1��ʽ) */
            {
                l->hdlc.lqm.SaveInErrors += stErrCnt.usErrProtocolCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "bad hdlc frame protocol\r\n");
            }
            else if (4UL == ulErrTypeLoop)    /* ��������4: ��AC����ѹ��ʱ, Control��ֵ��0x03 */
            {
                l->hdlc.lqm.SaveInErrors += stErrCnt.usErrCtrlCnt;
                l->hdlc.stats.badcommand += stErrCnt.usErrCtrlCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "bad hdlc frame control\r\n");
            }
            else if (5UL == ulErrTypeLoop)    /* ��������5: ��AC����ѹ��ʱ, Address��ֵ��0xFF */
            {
                l->hdlc.lqm.SaveInErrors += stErrCnt.usErrAddrCnt;
                l->hdlc.stats.badaddr += stErrCnt.usErrAddrCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "bad hdlc frame address\r\n");
            }
            else if (6UL == ulErrTypeLoop)    /* ��������6: ת���ַ�0x7D�����һ��Flag�� */
            {
                l->hdlc.lqm.SaveInErrors += stErrCnt.usFlagPosErrCnt;
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "bad hdlc frame flag position\r\n");
            }
            else
            {
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "link_HDLCDefDealErr err\r\n");
            }
        }
    }
}    /* link_HDLCDefDealErr */


VOS_VOID link_HDLCDefDealData
(
    HDLC_DEFRAMER_PPP_LINK_PARA_STRU *pstHdlcDeframerPppPara,
    PS_BOOL_ENUM_UINT8                enDealWithErrFrame,
    VOS_UINT32                        ulDeframerStatusReg,
    HDLC_DEFRAMER_PARA_STRU          *pstHdlcDeframerPara
)
{
    PS_BOOL_ENUM_UINT8                enWithLCPFrame;    /* �����������Ƿ����LCP֡, �� - PS_TRUE, �� - PS_FALSE */
    VOS_UINT32                        ulDeframerPerInfo;
    struct link                      *l;
    VOS_UINT32                        ulValidCnt;        /* ����ĺϷ�֡��֡�� */
    VOS_UINT32                        ulValidLoop;
    VOS_UINT16                        usDataLen;         /* ֡�ĳ���, ��λ: �ֽ� */
    VOS_UINT8                        *pucDataReadAddr;   /* ���װ����һ֡�����ݴ�ŵ�ַ, �˵�ַ��Ӳ����֤��ַһ����4�ֽڵı��� */
    VOS_UINT16                        usProtocol;
    VOS_UINT8                         ucErrType;
    VOS_UINT32                        ulDataAddrOffset;  /* ���װ����һ֡��Խ��װ���������ַƫ�ƶ����ֽ� */
    volatile VOS_UINT32              *pulPerInfoAddr;
    volatile VOS_UINT32              *pulDataRegAddr;    /* �˼Ĵ�������װ����ָʾ���װ����һ֡��Խ��װ���������ַƫ�ƶ����ֽ� */
    PPP_ZC_STRU                      *pstMem;            /* ��Ӳ����ȡ����Ŀ���㿽�� */


    ulValidCnt = TTF_Read32RegByBit(SOC_ARM_HDLC_DEFRAMER_STATUS_ADDR(g_ulHDLCIPBaseAddr), 8, 17);

    if (HDLC_DEFRAMER_OUT_LIST_MAX_CNT < ulValidCnt)
    {
        /* �쳣ʱ��λDeframer */
        link_HDLCReset(HDLC_DEFRAMER_MODULE, HDLC_DEFRAMER_OUT_LIST_LONG_ERR);

        return ;
    }

    enWithLCPFrame = PS_FALSE;  /* initial */
    l = pstHdlcDeframerPppPara->l;

    /* �ԺϷ�֡�Ĵ��� */
    for (ulValidLoop = 1UL; ulValidLoop <= ulValidCnt; ulValidLoop ++)
    {
        /* �ϱ��б��м�¼�˲�����256�ֽ��������������֡�������Ϣ,
           �������һ֡����Ϣ�ڽ��װ�ϱ��б��еĵ�ַ */
        pulPerInfoAddr = (((volatile VOS_UINT32 *)(SOC_ARM_HDLC_DEFRAMER_OUT_LIST_ADDR(g_ulHDLCIPBaseAddr)))
                       + ((ulValidLoop-1) * HDLC_DEFRAMER_PER_FRAME_INFO_DWORD_USE));
        ulDeframerPerInfo = TTF_READ_32REG((VOS_UINT32)pulPerInfoAddr);  /* �ӽ��װ�ϱ��б��ж���һ֡����Ϣ */
        usDataLen = GET_LOW_WORD_FROM_DWORD(ulDeframerPerInfo);     /* ��ȡһ֡�ĳ��� */

        if (0 != usDataLen)     /* ���һ֡�������� */
        {
            /* ��֡���ȳ���, ��ΪӲ���쳣 */
            if (HDLC_DEFRAMER_OUT_PER_FRAME_MAX_USED_BYTES < usDataLen)
            {
                /* �쳣ʱ��λDeframer */
                link_HDLCReset(HDLC_DEFRAMER_MODULE, HDLC_DEFRAMER_OUT_PER_LONG_ERR);

                return ;
            }

            pulDataRegAddr = (volatile VOS_UINT32 *)(pulPerInfoAddr + HDLC_DEFRAMER_PER_FRAME_ADDR_DWORD_OFFSET);
            ulDataAddrOffset = TTF_READ_32REG((VOS_UINT32)pulDataRegAddr);   /* ��ô�֡��Խ��װ���������ַƫ�ƶ����ֽ� */

            /* ��ֹ��ַƫ�Ƴ������װ������ݷ�Χ */
            if ((HDLC_DEFRAMER_OUT_ALL_FRAMES_MAX_USED_BYTES) <= ulDataAddrOffset)
            {
                /* �쳣ʱ��λDeframer */
                link_HDLCReset(HDLC_DEFRAMER_MODULE, HDLC_DEFRAMER_OUT_OFFSET_LONG_ERR);

                return ;
            }

            pucDataReadAddr = (VOS_UINT8 *)((SOC_ARM_HDLC_DEFRAMER_OUT_DATA_BASE_ADDR(g_ulHDLCIPBaseAddr)) + ulDataAddrOffset);

            /* ���ݶ�ȡ��ַ��Ӳ��Լ����4�ֽڱ߽���� */
            if (0 != (((VOS_UINT32)(pucDataReadAddr)) % sizeof(VOS_UINT32)))
            {
                /* �쳣ʱ��λDeframer */
                link_HDLCReset(HDLC_DEFRAMER_MODULE, HDLC_DEFRAMER_OUT_ADDRESS_ERR);

                return ;
            }

            /* ����һ�鳤��ΪusDataLen���㿽���ڴ�� */
            pstMem = PPP_MemAlloc(usDataLen, PPP_ZC_UL_RESERVE_LEN);

            if (VOS_NULL_PTR == pstMem)
            {
                PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL,
                             "Error: PPP, link_HDLCDefDealData, WARING, Alloc Mem for ip type Fail\r\n");
                return;
            }

            /*COPY���㿽���ڴ����ݲ���*/
            PPP_MemWriteData(pstMem, pucDataReadAddr, usDataLen);

            /*
            TTF_TraceData(PS_PID_APP_PPP, PS_PID_APP_PPP, 0x13, pstMem->pData, usDataLen,
                PPP_LINK_TO_ID(l) ,0, 0, 0);
            */

            if (HDLC_IP_MODE == pstHdlcDeframerPara->ucMode)    /* IPģʽ */
            {
                usProtocol = GET_HIGH_WORD_FROM_DWORD(ulDeframerPerInfo);
                if (PROTO_LCP == usProtocol)
                {
                    enWithLCPFrame  = PS_TRUE;
                }

                PPP_HDLC_ProcIpModeUlData(l, pstMem, usProtocol);
            }
            else    /* PPPģʽ */
            {
                PPP_HDLC_ProcPppModeUlData((VOS_UINT16)PPP_LINK_TO_ID(l), pstMem);
            }
        }   /* end of if */
    }   /* end of for */

    if (PS_TRUE == enDealWithErrFrame)    /* when HDLC pause, need not to record error frames counts */
    {
        ucErrType = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_DEFRAMER_STATUS_ADDR(g_ulHDLCIPBaseAddr), 24, 30);
        if (0 != ucErrType)     /* �д���֡ͳ����Ϣ */
        {
            link_HDLCDefDealErr(l, ucErrType);
        }
    }


    /* met LCP frames, need to update deframer parameters */
    if ( PS_TRUE == enWithLCPFrame )
    {
        pstHdlcDeframerPara->enACComp = (1 == l->lcp.want_acfcomp) ? PS_TRUE : PS_FALSE;
        pstHdlcDeframerPara->enPComp = (1 == l->lcp.want_protocomp) ? PS_TRUE : PS_FALSE;

        /* if met LCP frames, update deframer cfg para */
        link_HDLCSetDeframerCfg(pstHdlcDeframerPara);
    }
}    /* link_HDLCDefDealData */


VOS_VOID link_HDLCDeframer(HDLC_DEFRAMER_PPP_LINK_PARA_STRU *pstHdlcDeframerPppPara,
                           HDLC_DEFRAMER_PARA_STRU *pstHdlcDeframerPara)
{
    const VOS_UINT16                    usByteAllowed = HDLC_DEFRAMER_IN_PER_MAX_CNT;    /* �����Ӳ��Լ��һ���·����ó���256Bytes */
    VOS_UINT8                           *pucInDataStart;    /* ָ��ǰҪд��Ĵ����װ���ݵ���ʼ��ַ */
    VOS_UINT32                          ulDataLen;     /* �����װ�����ݳ���, ��λ: �ֽ� */
    VOS_UINT8                           ucDeframerBlkCnt;  /* �����װ�����ݷּ����·� */
    VOS_UINT32                          ulDataLoop;    /* ָʾ�ڼ�������, ��1��ʼ���� */
    VOS_UINT16                          usCurrWrited;      /* �����·������ݳ���, ��λ: �ֽ� */
    VOS_UINT32                          ulDeframeRsltWaitNum;  /* ��ֹӲ�������쳣�ı������� */
    volatile VOS_UINT32                 ulDeframerStatus;
    volatile VOS_UINT8                  ucBlockStatus;
    PS_BOOL_ENUM_UINT8                  enMeetLcpPause;    /* ��¼һ�����ݴ������Ƿ�����LCP֡��ͣ�����, �� - PS_TRUE, �� - PS_FALSE */
    volatile VOS_UINT32                 *pulRttMem;

    /* ��ֹ���ݹ��� */
    ulDataLen = pstHdlcDeframerPara->stDeframerInData.ulLen;
    if (HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES < ulDataLen)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "Deframer data too long\r\n");
        return ;
    }

    link_HDLCSetDeframerCfg(pstHdlcDeframerPara);

    /* initial */
    pucInDataStart = pstHdlcDeframerPara->stDeframerInData.pucData;
    ulDataLoop = 1UL;
    enMeetLcpPause = PS_FALSE;
    usCurrWrited = 0;

    /* ���㵱ǰ���ݻ�ָ��������з�װ */
    ucDeframerBlkCnt = (VOS_UINT8)(((ulDataLen + usByteAllowed) - 1) / usByteAllowed);

    while (ulDataLoop <= (VOS_UINT32)ucDeframerBlkCnt)    /* һ�������Ƿ�����������Ҫ���װ */
    {
        /* ���û�з���LCP֡��ͣ, ��Ҫд���µ�һ������, ������Ҫ */
        if (PS_FALSE == enMeetLcpPause)
        {
            /* ����һ���·����ݵĳ��� */
            if (ulDataLoop != (VOS_UINT32)ucDeframerBlkCnt)
            {
                /* �����һ��, һ����256�ֽ� */
                usCurrWrited = usByteAllowed;
            }
            else
            {
                usCurrWrited = (VOS_UINT16)(ulDataLen - ((ulDataLoop-1)*usByteAllowed));
            }

            /*blklen: 16~27*/
            TTF_Write32RegByBit(SOC_ARM_HDLC_DEFRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr), 16, 27, usCurrWrited);
            TTF_Write32RegByBit(SOC_ARM_HDLC_DEFRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr), 0, 0, 1);

            /* ����memcpy����, ���ָ���֡����, ������Bufferд�� */
            PPP_MemSingleCopy((VOS_UINT8 *)(SOC_ARM_HDLC_DEFRAMER_IN_DATA_ADDR(g_ulHDLCIPBaseAddr)), pucInDataStart, usCurrWrited);

            pucInDataStart += usCurrWrited;

            /* ��def_block_new��0, ָʾӲ������Ѿ�����ǰ���·����� */
            TTF_Write32RegByBit(SOC_ARM_HDLC_DEFRAMER_CTRL_ADDR(g_ulHDLCIPBaseAddr), 0, 0, 0);
        }   /* end of if */

        #if (VOS_OS_VER == VOS_WIN32)
        VHW_HDLC_Task();
        #endif

        /* �жϵ�ǰ���Ƿ���װ��� */
        ulDeframeRsltWaitNum = 0UL;
        while (ulDeframeRsltWaitNum < HDLC_DEFRAMER_MAX_WAIT_RESULT_NUM)
        {
            ucBlockStatus = (VOS_UINT8)TTF_Read32RegByBit(SOC_ARM_HDLC_DEFRAMER_STATUS_ADDR(g_ulHDLCIPBaseAddr), 0, 1);

            if (HDLC_DEFRAMER_BLOCK_STATUS_DOING != ucBlockStatus)   /* a deframer block done */
            {
                break ;
            }

            ulDeframeRsltWaitNum ++;
        }

        ulDeframerStatus = 0;
        if ( HDLC_DEFRAMER_MAX_WAIT_RESULT_NUM != ulDeframeRsltWaitNum )
        {
            switch(ucBlockStatus)
            {
                case HDLC_DEFRAMER_BLOCK_STATUS_DONE_WITH_FRAMES:
                {
                    link_HDLCDefDealData(pstHdlcDeframerPppPara, PS_TRUE, ulDeframerStatus,
                        pstHdlcDeframerPara);
                    ulDataLoop ++;  /* һ�����ݴ������, ѭ����������1 */
                    enMeetLcpPause = PS_FALSE;
                    break ;
                }


                case HDLC_DEFRAMER_BLOCK_STATUS_PAUSE:
                {
                    link_HDLCDefDealData(pstHdlcDeframerPppPara, PS_FALSE, ulDeframerStatus,
                        pstHdlcDeframerPara);

                    /* �������go on */
                    pulRttMem = (volatile VOS_UINT32 *)(SOC_ARM_HDLC_DEFRAMER_GO_ON_ADDR(g_ulHDLCIPBaseAddr));
                    SET_BIT_TO_DWORD(*pulRttMem, HDLC_DEFRAMER_GO_ON_BITPOS);

                    enMeetLcpPause = PS_TRUE;
                    /* ulDataLoop����Ҫ����1, ��Ϊ��������û�д������ */
                    break ;
                }

                case HDLC_DEFRAMER_BLOCK_STATUS_DONE_WITHOUT_FRAMES:
                {
                    ulDataLoop ++;  /* һ�����ݴ������, ѭ����������1 */
                    enMeetLcpPause = PS_FALSE;
                    break ;
                }

                case HDLC_DEFRAMER_BLOCK_STATUS_DOING:
                default:
                {
                    /* �쳣ʱ��λDeframer */
                    link_HDLCReset(HDLC_DEFRAMER_MODULE, HDLC_DEFRAMER_WORK_TIME_LONG_ERR);
                    return ;
                }
            }   /* end of switch */
        }
        else
        {
            /* �쳣ʱ��λDeframer */
            link_HDLCReset(HDLC_DEFRAMER_MODULE, HDLC_DEFRAMER_WORK_TIME_LONG_ERR);
            return ;
        }
    }   /* end of while */

}    /* link_HDLCDeframer */



VOS_VOID link_HDLCPullData(struct link *l, VOS_UINT8 *pucData, VOS_UINT32 ullen)
{
    HDLC_DEFRAMER_PARA_STRU             stHdlcDeframerPara;
    HDLC_DEFRAMER_PPP_LINK_PARA_STRU    stHdlcDeframerPppPara;

    if (!l)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "link_HDLCPullData:Can't Pull an async packet from a logical link\r\n");
        return;
    }

    if (0 == ullen)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "IP mode deframer data len is zero\r\n");
        return ;
    }

    stHdlcDeframerPara.ucMode = HDLC_IP_MODE;
    stHdlcDeframerPara.enPComp = (1 == l->lcp.want_protocomp) ? PS_TRUE : PS_FALSE;
    stHdlcDeframerPara.enACComp = (1 == l->lcp.want_acfcomp) ? PS_TRUE : PS_FALSE;

    stHdlcDeframerPara.stDeframerInData.pucData = (VOS_UINT8 *)pucData;
    stHdlcDeframerPara.stDeframerInData.ulLen = ullen;

    stHdlcDeframerPppPara.l = l;

    link_HDLCDeframer(&stHdlcDeframerPppPara, &stHdlcDeframerPara);
}    /* link_HDLCPullData */



VOS_VOID link_HDLCPullPacket(struct link *l, PPP_ZC_STRU *pstData)
{
    PPP_ZC_STRU            *pstCurrMem;
    VOS_UINT8              *pucCurrDataStart;    /* ��ǰ��m_buf������ʼ��ַ */
    VOS_UINT32              ulCurrDataLen;    /* �˴�pull���ݵĳ���, ������4096�ֽ� */
    VOS_UINT32              ulCurrPullCnt;    /* ��ǰ��m_buf��pull���ܴ��� */
    VOS_UINT32              ulCurrPullLoop;
    VOS_UINT32              ulCurrPulledByteCnt;    /* �˴�pull���ֽ��� */


    if (!l)
    {
        PPP_MemFree(pstData);
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "link_HDLCPullPacket:Can't Pull an async packet from a logical link\r\n");

        return;
    }

    pstCurrMem  = pstData;

    /* ��ǰ�㿽����֧����ʽ */
    /*
    while (VOS_NULL_PTR != pstCurrMem)
    {
    */
        pucCurrDataStart = PPP_ZC_GET_DATA_PTR(pstCurrMem);
        /*lint -e613*/
        ulCurrDataLen    = PPP_ZC_GET_DATA_LEN(pstCurrMem);
        /*lint +e613*/

        /* ���㵱ǰm_buf���ݻ�ָ���ٴ�4096�ֽڽ��н��װ,
           HDLCҪ��һ���������4096�ֽ� */
        ulCurrPullCnt
            = (((ulCurrDataLen + HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES) - 1) / HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES);
        for (ulCurrPullLoop = 0; ulCurrPullLoop < ulCurrPullCnt; ulCurrPullLoop ++)
        {
            if (ulCurrPullLoop != (ulCurrPullCnt-1))
            {
                /* �����һ��pull, һ����4096�ֽ� */
                ulCurrPulledByteCnt = HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES;
            }
            else
            {
                ulCurrPulledByteCnt = (ulCurrDataLen - (ulCurrPullLoop*HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES));
            }
            link_HDLCPullData(l,
                                (pucCurrDataStart + (ulCurrPullLoop * HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES)),
                                ulCurrPulledByteCnt);
        }
    /*
        pstCurrMem  = pstCurrMem->pNext;
    }
    */

    PPP_MemFree(pstData);
}    /* link_HDLCPullPacket */



VOS_UINT32 Ppp_HDLCFrameEncap(VOS_UINT16 usPppId,
                              PPP_ZC_STRU *pstDataMem)
{
    VOS_UINT16 usProtocol;
    struct link *l;
    HDLC_FRAMER_PARA_STRU stHdlcFramerPara;
    VOS_UINT32 ulFrameResult;
    VOS_UINT16 usLen;
    VOS_UINT8           aucProto[2];
    VOS_UINT32          ulRtn;
    HDLC_FRAMER_PPP_LINK_PARA_STRU stHdlcFramerPppPara;

    l = PPP_LINK(usPppId);

    usLen = PPP_ZC_GET_DATA_LEN(pstDataMem);

    if (0 == usLen)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "PPP mode framer data len is zero\r\n");
        return VOS_ERR;
    }

    ulRtn = PPP_MemGet(pstDataMem, 0, aucProto, 2);
    if (PS_FAIL == ulRtn)
    {
        PPP_MemFree(pstDataMem);

        return VOS_ERR;
    }

    if (0x01 == GET_BITS_FROM_BYTE(aucProto[0], 0x01))
    {
        usProtocol = HDLC_MAKE_WORD(0x00, aucProto[0]);
    }
    else
    {
        if (0x01 == GET_BITS_FROM_BYTE(aucProto[1], 0x01))
        {
            usProtocol = HDLC_MAKE_WORD(aucProto[0], aucProto[1]);
        }
        else
        {
            PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "PPP mode framer data protocol error\r\n");
            PPP_MemFree(pstDataMem);

            return VOS_ERR;
        }
    }

    stHdlcFramerPara.usProtocol = usProtocol;
    if (PROTO_LCP == usProtocol)
    {
        /* LCP֡P��ѹ��, AC��ѹ��, ACCMΪȫת�� */
        stHdlcFramerPara.enPComp = PS_FALSE;
        stHdlcFramerPara.enACComp = PS_FALSE;
        stHdlcFramerPara.ulACCM = 0xFFFFFFFF;
    }
    else
    {
        /* ʹ��Ĭ��ֵ */
        stHdlcFramerPara.enPComp = (1 == l->lcp.his_protocomp) ? PS_TRUE : PS_FALSE;
        stHdlcFramerPara.enACComp = (1 == l->lcp.his_acfcomp) ? PS_TRUE : PS_FALSE;
        /* stHdlcFramerPara.ulACCM = l->lcp.his_accmap; */
        /* ����PPP���Ų�֪��ACCM, ������ΪЭ��Ĭ��ֵ */
        stHdlcFramerPara.ulACCM = 0xFFFFFFFF;
    }
    stHdlcFramerPara.ucMode = HDLC_PPP_MODE;

    stHdlcFramerPara.stInData.pstMem = pstDataMem;
    stHdlcFramerPara.stInData.ulDataLen = (VOS_UINT32)usLen;
    stHdlcFramerPara.stOutData.pucData  = (VOS_UINT8 *)(l->async.xbuff);
    stHdlcFramerPppPara.l = l;

    ulFrameResult = link_HDLCFramer(&stHdlcFramerPppPara, &stHdlcFramerPara);

    if (VOS_OK == ulFrameResult)
    {
        /* TODO:���滻Ϊ����PPP_HDLC_ProcDlData */
        PPP_SendPushedData(usPppId,
                           (stHdlcFramerPara.stOutData.pucData),
                           (stHdlcFramerPara.stOutData.usFrameByteCnt));
    }
    else
    {
        if (VOS_NULL_PTR != pstDataMem)
        {
            PPP_MemFree(pstDataMem);
        }
    }

    /* ��link_HDLCFramer�ڲ�ÿ��д������ʱ, ͬʱ�ͷ��ڴ�, ��ȷ���㿽���ڴ��Ѿ���ȫ�ͷ� */
    return ulFrameResult;
}    /* Ppp_HDLCFrameEncap */


VOS_VOID Ppp_HDLCDataDecap(VOS_UINT16 PppId,
                            VOS_UINT8 *pucData,
                            VOS_UINT32 ulLen)
{
    HDLC_DEFRAMER_PARA_STRU stHdlcDeframerPara;
    HDLC_DEFRAMER_PPP_LINK_PARA_STRU stHdlcDeframerPppPara;
    struct link *l;

    if (0 == ulLen)
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING, "PPP mode deframer data len is zero\r\n");
        return ;
    }

    l = PPP_LINK(PppId);

    stHdlcDeframerPara.ucMode = HDLC_PPP_MODE;
    stHdlcDeframerPara.enPComp = (1 == l->lcp.want_protocomp) ? PS_TRUE : PS_FALSE;
    stHdlcDeframerPara.enACComp = (1 == l->lcp.want_acfcomp) ? PS_TRUE : PS_FALSE;

    stHdlcDeframerPara.stDeframerInData.pucData = pucData;
    stHdlcDeframerPara.stDeframerInData.ulLen = ulLen;

    stHdlcDeframerPppPara.l = l;

    link_HDLCDeframer(&stHdlcDeframerPppPara, &stHdlcDeframerPara);

    return ;
}    /* Ppp_HDLCDataDecap */



VOS_VOID Ppp_HDLCFrameDecap(VOS_UINT16 PppId, PPP_ZC_STRU *pstData)
{
    PPP_ZC_STRU            *pstCurrMem;    /* ��ǰ��m_buf */
    VOS_UINT8              *pucCurrDataStart;    /* ��ǰ��m_buf������ʼ��ַ */
    VOS_UINT32              ulCurrDataLen;    /* �˴�pull���ݵĳ���, ������4096�ֽ� */
    VOS_UINT32              ulCurrPullCnt;    /* ��ǰ��m_buf��pull���ܴ��� */
    VOS_UINT32              ulCurrPullLoop;
    VOS_UINT32              ulCurrPulledByteCnt;    /* �˴�pull���ֽ��� */


    pstCurrMem  = pstData;

    /*
    while (VOS_NULL_PTR != pstCurrMem)
    {
    */
        pucCurrDataStart = PPP_ZC_GET_DATA_PTR(pstCurrMem);
        /*lint -e613*/
        ulCurrDataLen    = PPP_ZC_GET_DATA_LEN(pstCurrMem);
        /*lint +e613*/

        /* ���㵱ǰm_buf���ݻ�ָ���ٴ�4096�ֽڽ��н��װ,
           HDLCҪ��һ���������4096�ֽ� */
        ulCurrPullCnt
            = (((ulCurrDataLen + HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES) - 1) / HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES);
        for (ulCurrPullLoop = 0; ulCurrPullLoop < ulCurrPullCnt; ulCurrPullLoop ++)
        {
            if (ulCurrPullLoop != (ulCurrPullCnt-1))
            {
                /* �����һ��pull, һ����4096�ֽ� */
                ulCurrPulledByteCnt = HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES;
            }
            else
            {
                ulCurrPulledByteCnt = (ulCurrDataLen - (ulCurrPullLoop*HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES));
            }
            Ppp_HDLCDataDecap(PppId,
                               (VOS_UINT8 *)(pucCurrDataStart + (ulCurrPullLoop * HDLC_DEFRAMER_IN_ALL_FRAMES_MAX_USED_BYTES)),
                               ulCurrPulledByteCnt);
        }
    /*
        pstCurrMem  = pstCurrMem->pNext;
    }
    */

    PPP_MemFree(pstData);
}    /* Ppp_HDLCFrameDecap */


PPP_HDLC_RESULT_TYPE_ENUM_UINT32 PPP_HDLC_HARD_ProcData
(
    PPP_ID              usPppId,
    struct link        *pstLink,
    PPP_ZC_QUEUE_STRU   *pstDataQ
)
{
    PPP_ZC_STRU                        *pstMem;
    VOS_UINT32                          ulDealCnt = 0;
    PPP_DATA_TYPE_ENUM_UINT8            ucDataType;

    for (;;)
    {
        pstMem  = (PPP_ZC_STRU *)PPP_ZC_DEQUEUE_HEAD(&g_PppDataQCtrl.stDataQ);

        /* ����Ϊ�յ�ʱ�򷵻ؿ�ָ�� */
        if ( VOS_NULL_PTR == pstMem )
        {
            return PPP_HDLC_RESULT_COMM_FINISH;
        }

        /*����ý��(�����ͷŶ����Ѿ��ڸ��������ڲ���ɣ��������ͷŽ��)*/
        ucDataType = (PPP_ZC_GET_DATA_APP(pstMem) & 0x00FF);

        link_HDLC_Enable();

        switch ( ucDataType )
        {
            case PPP_PULL_PACKET_TYPE:
                g_PppHdlcHardStat.ulUplinkIpDataProcCnt++;

                link_HDLCPullPacket(pstLink, pstMem);
                break;
            case PPP_PUSH_PACKET_TYPE:
                g_PppHdlcHardStat.ulDownlinkIpDataProcCnt++;

                link_HDLCPushPacket(pstLink, pstMem, 0, PROTO_IP);
                break;
            case PPP_PULL_RAW_DATA_TYPE:
                g_PppHdlcHardStat.ulUplinkPppDataProcCnt++;

                Ppp_HDLCFrameDecap(usPppId, pstMem);
                break;
            case PPP_PUSH_RAW_DATA_TYPE:
                g_PppHdlcHardStat.ulDownlinkPppDataProcCnt++;

                Ppp_HDLCFrameEncap(usPppId, pstMem);
                break;
            default:
                PPP_MemFree(pstMem);
                PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                              "PPP_ProcDataNotify, WARNING, ucDataType %d is Abnormal!", ucDataType);
                break;
        }

        link_HDLC_Disable();

        /*ͳ��*/
        ulDealCnt++;

        if ( ulDealCnt > g_PppHdlcHardStat.ulMaxCntOnce )
        {
            g_PppHdlcHardStat.ulMaxCntOnce = ulDealCnt;
        }

        /*���ѭ������Ľ����������˶���һ�����������������
          ���˳�ѭ��������PPP_DATA_PROC_NOTIFY��Ϣ*/
        if ( ulDealCnt >= PPP_ONCE_DEAL_MAX_CNT )
        {
            return PPP_HDLC_RESULT_COMM_CONTINUE;
        }
    } /* for (;;) */
}


VOS_VOID PPP_HDLC_HARD_ProcProtocolPacket
(
    struct link     *pstLink,
    struct ppp_mbuf *pstMbuf,
    VOS_INT32       ulPri,
    VOS_UINT16      ulProtocol
)
{
    PPP_ZC_STRU            *pstMem;


    pstMem  = ppp_m_alloc_ttfmem_from_mbuf(pstMbuf);

    ppp_m_freem(pstMbuf);
    pstMbuf  = VOS_NULL_PTR;

    if (VOS_NULL_PTR != pstMem)
    {
        link_HDLCPushPacket(pstLink, pstMem, ulPri, ulProtocol);
    }

    return;
}


VOS_VOID PPP_HDLC_HARD_ProcAsFrmPacket
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
)
{
    /* HDLC�Ż�����Ҫ���������������� */
}


VOS_UINT32 PPP_PHY_TO_VIRT(unsigned int ulPAddr)
{
    VOS_UINT32  ulUpEdge = (g_ulPppPhyAddr + TTF_HDLC_MASTER_LINK_TOTAL_LEN);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    if ((ulPAddr >= g_ulPppPhyAddr) && (ulPAddr <= (g_ulPppPhyAddr + TTF_HDLC_MASTER_LINK_TOTAL_LEN)))
    {
        return TTF_PHY_TO_VIRT(ulPAddr);
    }
    else
    {
        return phys_to_virt(ulPAddr);
    }
#else
    return TTF_PHY_TO_VIRT(ulPAddr);
#endif
}


VOS_UINT32 PPP_VIRT_TO_PHY(unsigned int ulVAddr)
{
    VOS_UINT32  ulUpEdge = (g_ulPppVirtAddr + TTF_HDLC_MASTER_LINK_TOTAL_LEN);

#if(FEATURE_OFF == FEATURE_SKB_EXP)
    if ((ulVAddr >= g_ulPppVirtAddr) && (ulVAddr <= (g_ulPppVirtAddr + TTF_HDLC_MASTER_LINK_TOTAL_LEN)))
    {
        return TTF_VIRT_TO_PHY(ulVAddr);
    }
    else
    {
        return virt_to_phys(ulVAddr);
    }
#else
    return TTF_VIRT_TO_PHY(ulVAddr);
#endif
}


#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

