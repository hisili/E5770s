/******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : R_ITF_FlowCtrl.c
  Author       : g45205
  Version      : V100R001
  Date         : 2006-05-17
  Description  :
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2006-05-17
     Author: g45205
     Modification:Create
******************************************************************************/


/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "R_ITF_FlowCtrl.h"
#include "om.h"
#include "NVIM_Interface.h"
#include "TTFMem.h"
#include "FcIntraMsg.h"
#include "PsCommonDef.h"
#include "Fc.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   2 �ⲿ������������
******************************************************************************/
extern VOS_UINT32   OM_TraceMsgHook(VOS_VOID *pMsg);

extern VOS_UINT32 IPSCH_FeatureSwitchIsOn(VOS_VOID);

/******************************************************************************
   3 ˽�ж���
******************************************************************************/
/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID                    PS_FILE_ID_R_ITF_FLOW_CTRL_C


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
/* R�ӿ�����ʵ�嶨�� */
R_ITF_FLOW_CTRL_STRU                    g_stRItfFlowCtrl;
VOS_UINT32                              g_ulRItfFlowCtrlProTime = 0;
R_ITF_FLOW_CTRL_CONFIG_STRU             g_stRItfFlowCtrlConfig;
VOS_UINT32                              g_ulLteFlowCtrl  =   VOS_FALSE;

VOS_UINT32      g_ulRItfFlowCtrlCnt = 0;
VOS_UINT32      g_ulRItfFlowCtrlDiscardNum = 20;

#define         RITF_FLOWCTRL_WRED_THRESHOLD        (g_ulRItfFlowCtrlDiscardNum)


/******************************************************************************
   6 ����ʵ��
******************************************************************************/


VOS_VOID R_ITF_MntnFlowCtrlEvent
(
    R_ITF_FLOW_CTRL_TYPE_ENUM_UINT32 ulFlowCtrlType,
    VOS_UINT32                       ulNewLev,
    R_ITF_FLOW_CTRL_CMD_ENUM_UINT32  ulFlowCtrlCmd,
    VOS_UINT32                       ulResult
)
{
    R_ITF_FLOW_CTRL_MNTN_INFO_STRU                stMntnInfo;


    stMntnInfo.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stMntnInfo.ulSenderPid     = WUEPS_PID_RLC;
    stMntnInfo.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stMntnInfo.ulReceiverPid   = WUEPS_PID_RLC;
    stMntnInfo.ulLength        = sizeof(R_ITF_FLOW_CTRL_MNTN_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    stMntnInfo.enFlowCtrlType  = ulFlowCtrlType;
    stMntnInfo.ulNewLevel      = ulNewLev;
    stMntnInfo.enFlowCtrlCmd   = ulFlowCtrlCmd;
    stMntnInfo.ulResult        = ulResult;

    OM_TraceMsgHook(&stMntnInfo);

    return;
}

/******************************************************************************
 Prototype      : R_ITF_TtfMemAllocEvent
 Description    : ����MEM����ص�����
 Input          : ulMemUsedCnt  -- �ڴ����
                  ulMemUsedSize -- �ڴ��ܴ�С
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-08-31
    Author      : �߲�(g45205)
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_TtfMemAllocEvent(VOS_UINT32 ulMemUsedCnt, VOS_UINT32 ulMemUsedSize)
{
    R_ITF_SetFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_CNT, ulMemUsedCnt);
    R_ITF_SetFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_SIZE, ulMemUsedSize);
} /* R_ITF_TtfMemAllocEvent */


/******************************************************************************
 Prototype      : R_ITF_TtfMemFreeEvent
 Description    : ����MEM�ͷŻص�����
 Input          : ulMemUsedCnt  -- �ڴ����
                  ulMemUsedSize -- �ڴ��ܴ�С
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-08-31
    Author      : �߲�(g45205)
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_TtfMemFreeEvent(VOS_UINT32 ulMemUsedCnt, VOS_UINT32 ulMemUsedSize)
{
    R_ITF_ClearFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_CNT, ulMemUsedCnt);
    R_ITF_ClearFlowCtrl(R_ITF_FLOW_CTRL_TYPE_MEM_SIZE, ulMemUsedSize);
} /* R_ITF_TtfMemFreeEvent */



VOS_UINT32 R_ITF_SetGprsFlowCtrl(VOS_VOID)
{
    FC_SET_GPRS_FLOWCTRL_IND_STRU        *pstFcSetGprsInd;


    pstFcSetGprsInd = (FC_SET_GPRS_FLOWCTRL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_FLOWCTRL_C, sizeof(FC_SET_GPRS_FLOWCTRL_IND_STRU));

    /* ������Ϣʧ�� */
    if (VOS_NULL_PTR == pstFcSetGprsInd)
    {
        /* �澯��ӡ */
        LogPrint("R_ITF_SetGprsFlowCtrl, ERROR, alloc msg fail\r\n");
        return VOS_ERR;
    }

    /* ��д��Ϣ���� */
    pstFcSetGprsInd->usMsgName          = ID_FC_SET_GPRS_FLOWCTRL_IND;
    pstFcSetGprsInd->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstFcSetGprsInd->ulReceiverPid      = UEPS_PID_FLOWCTRL_A;

    /* ����Ϣ */
    PS_SEND_MSG(UEPS_PID_FLOWCTRL_C, pstFcSetGprsInd);

    return VOS_OK;
}    /* FC_GPRS_SetFlowCtrl */


VOS_UINT32 R_ITF_GprsFlowCtrlNotify(VOS_VOID)
{
    FC_GPRS_FLOWCTRL_NOTIFY_STRU        *pstFcGprsNotify;

    pstFcGprsNotify = (FC_GPRS_FLOWCTRL_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
        UEPS_PID_FLOWCTRL_C, sizeof(FC_GPRS_FLOWCTRL_NOTIFY_STRU));

    /* ������Ϣʧ�� */
    if (VOS_NULL_PTR == pstFcGprsNotify)
    {
        /* �澯��ӡ */
        LogPrint("R_ITF_StopGprsFlowCtrl, ERROR, alloc msg fail\r\n");
        return VOS_ERR;
    }

    /* ��д��Ϣ���� */
    pstFcGprsNotify->usMsgName         = ID_FC_GPRS_C_FLOWCTRL_NOTIFY;

    pstFcGprsNotify->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFcGprsNotify->ulReceiverPid     = UEPS_PID_FLOWCTRL_C;


    /* ����Ϣ */
    PS_SEND_MSG(UEPS_PID_FLOWCTRL_C, pstFcGprsNotify);

    return VOS_OK;

}


VOS_VOID R_ITF_UpdateFlowCtrlCnt(VOS_VOID)
{
    g_ulRItfFlowCtrlCnt++;
    return;
}


VOS_UINT32 R_Itf_FlowctrlGetStatCnt(VOS_UINT32 *pulFcStatCnt)
{
    *pulFcStatCnt = g_ulRItfFlowCtrlCnt;
    return VOS_OK;
}


VOS_UINT32 R_Itf_FlowctrlSetStatCnt(VOS_UINT32 pulFcStatCnt)
{
    g_ulRItfFlowCtrlCnt = pulFcStatCnt;
    return VOS_OK;
}



VOS_UINT32 R_ITF_FlowCtrlCntIsOverFlow(VOS_VOID)
{
    VOS_INT32               lLockKey;

    if (RITF_FLOWCTRL_WRED_THRESHOLD < g_ulRItfFlowCtrlCnt)
    {
        /* ���������ٽ��� */
        lLockKey            = VOS_SplIMP();

        g_ulRItfFlowCtrlCnt = 0;

        VOS_Splx(lLockKey);
        return VOS_YES;
    }

    return VOS_NO;
}


VOS_UINT32 R_ITF_StopGprsFlowCtrl(VOS_VOID)
{
    FC_SET_GPRS_FLOWCTRL_IND_STRU        *pstFcStopGprsInd;

    pstFcStopGprsInd = (FC_SET_GPRS_FLOWCTRL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
        UEPS_PID_FLOWCTRL_C, sizeof(FC_SET_GPRS_FLOWCTRL_IND_STRU));

    /* ������Ϣʧ�� */
    if (VOS_NULL_PTR == pstFcStopGprsInd)
    {
        /* �澯��ӡ */
        LogPrint("R_ITF_StopGprsFlowCtrl, ERROR, alloc msg fail\r\n");
        return VOS_ERR;
    }

    /* ��д��Ϣ���� */
    pstFcStopGprsInd->usMsgName         = ID_FC_STOP_GPRS_FLOWCTRL_IND;

    pstFcStopGprsInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFcStopGprsInd->ulReceiverPid     = UEPS_PID_FLOWCTRL_A;


    /* ����Ϣ */
    PS_SEND_MSG(UEPS_PID_FLOWCTRL_C, pstFcStopGprsInd);

    return VOS_OK;
}    /* FC_GPRS_StopFlowCtrl */



VOS_UINT32 R_ITF_ExcFlowCtrl
(
    R_ITF_FLOW_CTRL_CMD_ENUM_UINT32  ulFlowCtrlCmd,
    VOS_UINT32                       ulFlowCtrlType,
    VOS_UINT32                      *pulNeedTrace
)
{
    VOS_UINT32      ulResult = VOS_OK;

    if ( R_ITF_FLOW_CTRL_START == ulFlowCtrlCmd )
    {
        /* PS�ںϺ�, ����ֻ����ڴ�, �����������ȫ��ͳһ��FC�Ŀ���� */
        if ((R_ITF_FLOW_CTRL_TYPE_MEM_CNT == ulFlowCtrlType)
            || (R_ITF_FLOW_CTRL_TYPE_MEM_SIZE == ulFlowCtrlType))
        {
            ulResult        = R_ITF_SetGprsFlowCtrl();    /* �������غ��� */
            *pulNeedTrace   = PS_TRUE;
        }
    }
    else if ( R_ITF_FLOW_CTRL_STOP == ulFlowCtrlCmd )
    {
        /* PS�ںϺ�, ����ֻ����ڴ�, �����������ȫ��ͳһ��FC�Ŀ���� */
        if ((R_ITF_FLOW_CTRL_TYPE_MEM_CNT == ulFlowCtrlType)
            || (R_ITF_FLOW_CTRL_TYPE_MEM_SIZE == ulFlowCtrlType))
        {
            ulResult        = R_ITF_StopGprsFlowCtrl();    /* �������ؽ������ */
            *pulNeedTrace   = PS_TRUE;
        }
    }
    else
    {
        LogPrint1("R_ITF_ExcFlowCtrl, WARNING, Unknow flow control command %u\r\n",
                  (VOS_INT32)ulFlowCtrlCmd);

        return VOS_ERR;
    }

    return ulResult;
}



VOS_UINT32 R_ITF_SetFlowCtrl(VOS_UINT32 ulFlowCtrlType, VOS_UINT32 ulNewLev)
{
    R_ITF_FLOW_LEV_STRU                 *pFlowLev;
    VOS_INT32                           lLockKey;
    VOS_UINT32                          ulOldMask;
    VOS_UINT32                          ulCurrTick;
    VOS_UINT32                          ulNeedExec;              /* �Ƿ���Ҫ�������ػ��߽�����ز��� */
    VOS_UINT32                          ulResult;                /* ����ִ�н�� */


    if (R_ITF_FLOW_CTRL_TYPE_BUTT <= ulFlowCtrlType)
    {
        return VOS_ERR;
    }

    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    ulNeedExec          = PS_FALSE;
    ulResult            = VOS_OK;
    pFlowLev            = &g_stRItfFlowCtrl.astFlowCtrl[ulFlowCtrlType];
    ulCurrTick          = VOS_GetTick();

    if (pFlowLev->ulMaxLev < ulNewLev)
    {
        pFlowLev->ulMaxLev = ulNewLev;
    }

    /* ����ʵ���ﱣ��ĵ�ǰֵ��Ҫ�����Ᵽ�� */
    pFlowLev->ulCurrLev = ulNewLev;
    ulOldMask           = g_stRItfFlowCtrl.ulCtrlMask;

    /* ���ڽ�����״̬ʱ������ֵ, �������� */
    if (ulNewLev >= pFlowLev->ulWarningLev)
    {
        if (0 == ulOldMask)
        {
            ulNeedExec  = PS_TRUE;

            g_stRItfFlowCtrl.ulLastOptTick  = ulCurrTick;
            g_stRItfFlowCtrl.ulCtrlMask    |=  pFlowLev->ulMask;

            g_stRItfFlowCtrl.ulGprsCtrlFlag = R_ITF_FLOW_CTRL_START;
        }
    }

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    if (PS_TRUE == ulNeedExec)
    {
        ulResult        = R_ITF_GprsFlowCtrlNotify();    /* �������غ��� */
        R_ITF_UpdateFlowCtrlCnt();

        if (VOS_OK == ulResult)
        {
            /* �������ػ��߽�����ز�����ͬʱ, ���пɲ��ά */
            R_ITF_MntnFlowCtrlEvent(ulFlowCtrlType, ulNewLev, R_ITF_FLOW_CTRL_START, ulResult);
        }
    }

    return ulResult;
} /* R_ITF_SetFlowCtrl */

/******************************************************************************
 Prototype      : R_ITF_ClearFlowCtrl
 Description    : ��������������ж��Ƿ���Ҫ�������
 Input          : ulFlowCtrlType    -- ��������
                  ulNewLev          -- ���������͵�����ֵ
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2008-04-07
    Author      : �߲�(g45205)
    Modification: Created function
******************************************************************************/
VOS_UINT32 R_ITF_ClearFlowCtrl(VOS_UINT32 ulFlowCtrlType, VOS_UINT32 ulNewLev)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;
    VOS_UINT32              ulCurrTick;
    VOS_UINT32              ulNeedExec;              /* �Ƿ���Ҫ�������ػ��߽�����ز��� */
    VOS_UINT32              ulResult;                /* ����ִ�н�� */
    VOS_UINT32              ulUpdatedMask;


    if (R_ITF_FLOW_CTRL_TYPE_BUTT <= ulFlowCtrlType)
    {
        return VOS_ERR;
    }

    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    ulNeedExec          = PS_FALSE;
    ulResult            = VOS_OK;
    pFlowLev            = &g_stRItfFlowCtrl.astFlowCtrl[ulFlowCtrlType];
    ulCurrTick          = VOS_GetTick();

    /* ����ʵ���ﱣ��ĵ�ǰֵ��Ҫ�����Ᵽ�� */
    pFlowLev->ulCurrLev = ulNewLev;

    /* ��û����Ϊ�������͵�������, ���������� */
    if (0 == (g_stRItfFlowCtrl.ulCtrlMask & pFlowLev->ulMask))
    {
        VOS_Splx(lLockKey);
        return VOS_OK;
    }

    if (ulNewLev < pFlowLev->ulNormalLev)
    {
        if ((ulCurrTick - g_stRItfFlowCtrl.ulLastOptTick) >= g_ulRItfFlowCtrlProTime)
        {
            ulUpdatedMask = g_stRItfFlowCtrl.ulCtrlMask &  (~(pFlowLev->ulMask));

            /*�����������������������£�ִ�н�����ز���*/
            if ( 0 == ulUpdatedMask )
            {
                ulNeedExec      = PS_TRUE;

                g_stRItfFlowCtrl.ulLastOptTick = ulCurrTick;
                g_stRItfFlowCtrl.ulCtrlMask   &=  ~(pFlowLev->ulMask);

                g_stRItfFlowCtrl.ulGprsCtrlFlag = R_ITF_FLOW_CTRL_STOP;
            }
        }
    }

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    if (PS_TRUE == ulNeedExec)
    {
        ulResult        = R_ITF_GprsFlowCtrlNotify();    /* �������ؽ������ */

        if (VOS_OK == ulResult)
        {
            /*�����¼���ά�ɲ�*/
            R_ITF_MntnFlowCtrlEvent(ulFlowCtrlType, ulNewLev, R_ITF_FLOW_CTRL_STOP, ulResult);
        }
    }

    return ulResult;
} /* R_ITF_ClearFlowCtrl */

/******************************************************************************
 Prototype      : R_ITF_SetFlowLev
 Description    : ��ʱ�������ط�ֵ
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2008-04-07
    Author      : �߲�(g45205)
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_SetFlowLev(VOS_UINT32 ulFlowCtrlType, VOS_UINT32 ulNormalLev, VOS_UINT32 ulWarningLev)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;


    if (R_ITF_FLOW_CTRL_TYPE_BUTT <= ulFlowCtrlType)
    {
        return;
    }

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[ulFlowCtrlType];
    pFlowLev->ulNormalLev   = ulNormalLev;
    pFlowLev->ulWarningLev  = ulWarningLev;

    R_ITF_ResetFlowCtrl();

    vos_printf("\r\nFlowCtrltype:%u, NormalLev:%u, ulWarningLev:%u\r\n",ulFlowCtrlType,
        pFlowLev->ulNormalLev, pFlowLev->ulWarningLev);
}/* R_ITF_SetFlowLev */
/* ��ֵ���ݲ��Դ��� END */


VOS_VOID R_ITF_SetLFlowLev(VOS_VOID)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;

    /* PS�ںϺ�, Lģ��C����������A���Ͽ���, �����C���Ͻ����޸�Ϊ�����, �������������� */

    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 600;
    pFlowLev->ulWarningLev  = 1200;
    pFlowLev->ulMaxLev      = 0;

    if ( VOS_FALSE == g_ulLteFlowCtrl )
    {
        pFlowLev->ulWarningLev  = 0xffffffff;
        pFlowLev->ulNormalLev   = 0xffffffff;
    }

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 900000;
    pFlowLev->ulWarningLev  = 1800000;
    pFlowLev->ulMaxLev      = 0;

    if ( VOS_FALSE == g_ulLteFlowCtrl )
    {
        pFlowLev->ulWarningLev  = 0xffffffff;
        pFlowLev->ulNormalLev   = 0xffffffff;
    }

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* ��Lģ��, �ڴ���A�˼��, ���C���ϲ���Ҫ�ڴ��⹳�� */
    TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, VOS_NULL_PTR, VOS_NULL_PTR);

    return;
}



/******************************************************************************
 Prototype      : R_ITF_SetWFlowLev
 Description    : ҵ���л�ΪWģʱ��������������
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2009-02-27
    Author      : ����48156
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_SetWFlowLev(VOS_VOID)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;

    /* PS�ںϺ�, Wģ��C����������A���Ͽ���, �����C���Ͻ����޸�Ϊ�����, �������������� */
    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 0xffffffff;/*1000*/
    pFlowLev->ulWarningLev  = 0xffffffff;/*2000*/
    pFlowLev->ulMaxLev      = 0;

    /* PS�ںϺ�, Wģ����ʹ��A���ڴ�, ��˽���������Ϊ�����, �����ڴ������� */
    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 0xffffffff;/*1200000*/
    pFlowLev->ulWarningLev  = 0xffffffff;/*2000000*/
    pFlowLev->ulMaxLev      = 0;

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* ��Wģ��, �ڴ���A�˼��, ���C���ϲ���Ҫ�ڴ��⹳�� */
    TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, VOS_NULL_PTR, VOS_NULL_PTR);

    return;
}


/******************************************************************************
 Prototype      : R_ITF_SetGFlowLev
 Description    : ҵ���л�ΪGģʱ��������������
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2009-02-27
    Author      : ����48156
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_SetGFlowLev(VOS_VOID)
{
    R_ITF_FLOW_LEV_STRU    *pFlowLev;
    VOS_INT32               lLockKey;

    /* ���������ٽ��� */
    lLockKey            = VOS_SplIMP();

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulNormalLev   = 600;
    pFlowLev->ulWarningLev  = 600;
    pFlowLev->ulMaxLev      = 0;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulNormalLev   = 30000;
    pFlowLev->ulWarningLev  = 30000;
    pFlowLev->ulMaxLev      = 0;

    /* �뿪�����ٽ��� */
    VOS_Splx(lLockKey);

    R_ITF_ResetFlowCtrl();

    /* V9R1��ʹ������NV����GPRS����ʹ��λ���ж��Ƿ�ע�ṳ�Ӻ��� */
    if ( (FC_POLICY_MASK(FC_POLICY_ID_GPRS) == FC_POLICY_GetEnableMask(FC_POLICY_ID_GPRS) ))
    {
        /* ��Gģ��, A���ڴ���Ҫ������C��TTF_MEM��, ���C������Ҫ�ڴ��⹳�� */
        TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, R_ITF_TtfMemAllocEvent, R_ITF_TtfMemFreeEvent);
    }
    else
    {
        /* V9R1��ʹ�ú����жϣ������V9R1,��ע�ṳ�Ӻ��� */
        TTF_MemRegEventCallBack(TTF_MEM_POOL_ID_UL_DATA, VOS_NULL_PTR, VOS_NULL_PTR);
    }

    return;
}


/******************************************************************************
 Prototype      : R_ITF_InitFlowCtrl
 Description    : ��ʼ������ʵ��
 Input          : ulFlowCtrlType    -- ��������
                  ulNewLev          -- ���������͵�����ֵ
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2008-04-07
    Author      : �߲�(g45205)
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_InitFlowCtrl(VOS_VOID)
{
    VOS_UINT32                          ulResult;
    R_ITF_FLOW_CTRL_CONFIG_STRU        *pstRItfFlowCtrlConfig;
    R_ITF_FLOW_LEV_STRU                *pFlowLev;

    pstRItfFlowCtrlConfig               = &g_stRItfFlowCtrlConfig;

    /*Read the NV Config Value*/
    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_RITF_FLOW_CTRL_Config, pstRItfFlowCtrlConfig, sizeof(R_ITF_FLOW_CTRL_CONFIG_STRU));

    /*Read NV Content is Failed , Configed the Vaule By Default Value*/
    if ( NV_OK != ulResult )
    {
        pstRItfFlowCtrlConfig->ulRateDismatchUsbEnable  = 1;
        pstRItfFlowCtrlConfig->ulRateDismatchWifiEnable = 0;
    }
    else
    {
        if ( 1 < pstRItfFlowCtrlConfig->ulRateDismatchUsbEnable )
        {
            pstRItfFlowCtrlConfig->ulRateDismatchUsbEnable  = 1;
        }

        if ( 1 < pstRItfFlowCtrlConfig->ulRateDismatchWifiEnable )
        {
            pstRItfFlowCtrlConfig->ulRateDismatchWifiEnable = 0;
        }
    }

    g_stRItfFlowCtrl.ulCtrlMask     = 0;
    g_stRItfFlowCtrl.ulLastOptTick  = 0;
    g_stRItfFlowCtrl.ulGprsCtrlFlag = R_ITF_FLOW_CTRL_STOP;;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_CNT];
    pFlowLev->ulMask        = R_ITF_FLOW_CTRL_MASK_MEM_CNT;

    pFlowLev                = &g_stRItfFlowCtrl.astFlowCtrl[R_ITF_FLOW_CTRL_TYPE_MEM_SIZE];
    pFlowLev->ulMask        = R_ITF_FLOW_CTRL_MASK_MEM_SIZE;

    R_ITF_SetWFlowLev();


} /* R_ITF_InitFlowCtrl */


/******************************************************************************
 Prototype      : R_ITF_RateDismatchUsbEnable
 Description    :
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-03-11
    Author      : hefeng
    Modification: Created function
******************************************************************************/
VOS_UINT32 R_ITF_RateDismatchUsbEnable(VOS_VOID)
{
    return g_stRItfFlowCtrlConfig.ulRateDismatchUsbEnable;
}


/******************************************************************************
 Prototype      : R_ITF_RateDismatchWifiEnable
 Description    :
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2011-03-11
    Author      : hefeng
    Modification: Created function
******************************************************************************/
VOS_UINT32 R_ITF_RateDismatchWifiEnable(VOS_VOID)
{
    return g_stRItfFlowCtrlConfig.ulRateDismatchWifiEnable;
}


/******************************************************************************
 Prototype      : R_ITF_ResetMaxLev
 Description    :
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2008-04-07
    Author      : �߲�(g45205)
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_ResetMaxLev(VOS_VOID)
{
    VOS_UINT32  ulLoop;


    for (ulLoop = 0; ulLoop < R_ITF_FLOW_CTRL_TYPE_BUTT; ulLoop++)
    {
        g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulMaxLev   = 0;
    }
} /* R_ITF_ResetMaxLev */


VOS_VOID R_ITF_ResetFlowCtrl(VOS_VOID)
{
    VOS_UINT32  ulLoop;
    R_ITF_FLOW_LEV_STRU    *pFlowLev;

    for ( ulLoop = 0; ulLoop <= R_ITF_FLOW_CTRL_TYPE_MEM_SIZE; ++ulLoop )
    {
        pFlowLev = &g_stRItfFlowCtrl.astFlowCtrl[ulLoop];

        if ( pFlowLev->ulCurrLev >= pFlowLev->ulWarningLev )
        {
            R_ITF_SetFlowCtrl(ulLoop, pFlowLev->ulCurrLev);
        }
        else
        {
            R_ITF_ClearFlowCtrl(ulLoop, pFlowLev->ulCurrLev);
        }
    }

    return;

}

/* ��ʱ���Դ��룬�����ɼ�R�ӿ����صķ�ֵ������ֱ��ʹ���� vos_printf */
/******************************************************************************
 Prototype      : R_ITF_Print
 Description    : ��ӡ����ʵ���������ʱ����ʹ��
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2008-04-07
    Author      : �߲�(g45205)
    Modification: Created function
******************************************************************************/
VOS_VOID R_ITF_Print(VOS_VOID)
{
    VOS_UINT32  ulLoop;


    vos_printf("\r\n");

    for (ulLoop = 0; ulLoop < R_ITF_FLOW_CTRL_TYPE_BUTT; ulLoop++)
    {
        vos_printf("Type:%u, MaxLev=%u, CurrLev=%u, ulWarningLev=%u, ulNormalLev=%u\r\n",
            ulLoop,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulMaxLev,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulCurrLev,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulWarningLev,
            g_stRItfFlowCtrl.astFlowCtrl[ulLoop].ulNormalLev );
    }
} /* R_ITF_Print */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


