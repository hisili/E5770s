


/*******************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
*******************************************************************************/

#include "msp_errno.h"
#include <dms.h>
#include "dms_core.h"
#include "vos.h"
#include <DrvInterface.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


pComRecv                                pfnAcmReadData = VOS_NULL;

VOS_UINT32                              dms_debug_flag = VOS_FALSE;
VOS_UINT32                              dms_saveRdDtaCallbackAddr = 0xfffffff;
VOS_UINT32                              dms_saveAcmReadDataAddr = 0xfffffff;
VOS_UINT32                              g_ulPcuiReadUdiCnt = 0;
VOS_UINT32                              g_ulCtrlReadUdiCnt = 0;

#if(FEATURE_ON == MBB_WPG_COMMON)
#define PCUI_OPEN_TIMES            (5)
#define PCUI_OPEN_WAITTIME         (10)
#endif

VOS_VOID dms_setdebugflag(VOS_UINT32 ulFlag)
{
    dms_debug_flag = ulFlag;
    return;
}

VOS_VOID dms_printDebugInfo(VOS_VOID)
{
    DMS_MAIN_INFO * pstMainInfo = dmsGetMainInfo();

    vos_printf("dms_printDebugInfo: dms_saveRdDtaCallbackAddr = %d,\r\n", dms_saveRdDtaCallbackAddr);
    vos_printf("dms_printDebugInfo: dms_saveAcmReadDataAddr = %d\r\n", dms_saveAcmReadDataAddr);

    vos_printf("dms_printDebugInfo: pfnAcmReadData = %d,\r\n", (VOS_UINT32)pfnAcmReadData);
    vos_printf("dms_printDebugInfo: pstMainInfo->pfnRdDtaCallback = %d\r\n", (VOS_UINT32)(pstMainInfo->pfnRdDtaCallback));

    return;
}



VOS_UINT32 Dms_AtReadData(DMS_AT_CLIENT_ENUM enClientId, VOS_UINT8 * pDataBuf, VOS_UINT32 ulLen)
{
    VOS_UINT8 ucPortNo = 0;
    VOS_UINT32 ulRet = 0;

    if((VOS_NULL == pfnAcmReadData) || (VOS_NULL == pDataBuf))
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if(EN_DMS_AT_CLIENT_ACM == enClientId)
    {
        ucPortNo = EN_DMS_BEARER_USB_COM4_AT;
    }

    else if(EN_DMS_AT_CLIENT_CTRL == enClientId)
    {
        ucPortNo = EN_DMS_BEARER_USB_COM_CTRL;
    }

    else
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    if (VOS_TRUE == dms_debug_flag)
    {
        vos_printf("Dms_AtReadData: PortNo = %d, len = %d, buf = %s\r\n", ucPortNo, ulLen, pDataBuf);
    }

   ulRet = (VOS_UINT32)pfnAcmReadData(ucPortNo, pDataBuf, (VOS_UINT16)ulLen);

    return ulRet;
}



VOS_INT32 DMS_ACMRecvFuncReg(pComRecv pCallback)
{
    DMS_MAIN_INFO * pstMainInfo = dmsGetMainInfo();

    if (VOS_NULL == pCallback)
    {
        return ERR_MSP_INVALID_PARAMETER;
    }

    pstMainInfo->pfnRdDtaCallback = Dms_AtReadData;
    pfnAcmReadData = pCallback;

    dms_saveRdDtaCallbackAddr = (VOS_UINT32)Dms_AtReadData;
    dms_saveAcmReadDataAddr = (VOS_UINT32)pCallback;

    return ERR_MSP_SUCCESS;
}




VOS_VOID ctrlAtReadProc(VOS_VOID)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    static VOS_UINT8 aucStaticDtaStore[DMS_RD_BUF_LEN + 32];
    VOS_UINT32 ulReadLen               = 0;
    DMS_READ_DATA_PFN pstGetRdFun = NULL;
/*    DMS_LOGIC_CHAN_ENUM enLogic = EN_DMS_CHANNEL_LAST; */
    DMS_PHY_BEAR_PROPERTY_STRU* aenPhyBear = dmsgetPhyBearProperty();
    VOS_UINT8 *pucCtrlAtStore = NULL;

    /*ȡ32�ֽڶ���ĵ�ַ*/
    pucCtrlAtStore =&(aucStaticDtaStore[32 -(VOS_UINT32)(aucStaticDtaStore)%32]);
    g_ulCtrlReadUdiCnt++;
    if (dms_GetPortHandle(EN_DMS_BEARER_USB_COM_CTRL ) == FALSE)
    {
        VOS_TaskDelay(DMS_RD_SLEEP_TIME);
    }
    else
    {
/*        enLogic = aenPhyBear[EN_DMS_BEARER_USB_COM_CTRL].aenLogicChan; */

        ret =dms_UdiRead(EN_DMS_BEARER_USB_COM_CTRL,pucCtrlAtStore, DMS_RD_BUF_LEN, &ulReadLen);

        if((ret == ERR_MSP_SUCCESS)&&(ulReadLen != 0))
        {
            dmsAtCtrlTaskSetSleepFlag(FALSE);

            /*��ȡ����֪ͨ�ص�*/
            aenPhyBear[EN_DMS_BEARER_USB_COM_CTRL].ucChanStat = ACM_EVT_DEV_READY;

            /*��ȡ���ص�����*/
            pstGetRdFun = dmsGetReadFun();

            if (NULL != pstGetRdFun)
            {
                (VOS_VOID)pstGetRdFun(EN_DMS_AT_CLIENT_CTRL, pucCtrlAtStore, ulReadLen);
            }

            dmsAtCtrlTaskSetSleepFlag(TRUE);

        }
        else
        {
            VOS_TaskDelay(100);
        }
    }
}



VOS_VOID vcomAtReadProc(VOS_VOID)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    static VOS_UINT8 aucStaticDtaStore[DMS_RD_BUF_LEN + 32];
    VOS_UINT32 ulReadLen               = 0;
    DMS_READ_DATA_PFN pstGetRdFun = NULL;
    DMS_PHY_BEAR_PROPERTY_STRU* aenPhyBear = dmsgetPhyBearProperty();
    VOS_UINT8 *pucVcomAtStore = NULL;

    /*ȡ32�ֽڶ���ĵ�ַ*/
    pucVcomAtStore =&(aucStaticDtaStore[32 - (VOS_UINT32)(aucStaticDtaStore)%32]);

    g_ulPcuiReadUdiCnt++;

    if (dms_GetPortHandle(EN_DMS_BEARER_USB_COM4_AT ) == FALSE)
    {
        VOS_TaskDelay(DMS_RD_SLEEP_TIME);
    }
    else
    {
        ret = dms_UdiRead(EN_DMS_BEARER_USB_COM4_AT,pucVcomAtStore, DMS_RD_BUF_LEN, &ulReadLen);

        if (VOS_TRUE == dms_debug_flag)
        {
            vos_printf("vcomAtReadProc: dms_UdiRead ret = %d, len = %d\r\n", ret, ulReadLen);
        }

        if ((ret == ERR_MSP_SUCCESS)&&(ulReadLen != 0))
        {
            dmsAtPcuiTaskSetSleepFlag(FALSE);

            aenPhyBear[EN_DMS_BEARER_USB_COM4_AT].ucChanStat = ACM_EVT_DEV_READY;

            /*��ȡ���ص�����*/
            pstGetRdFun = dmsGetReadFun();

            if (NULL != pstGetRdFun)
            {
                if (VOS_TRUE == dms_debug_flag)
                {
                    vos_printf("vcomAtReadProc: call AT reg func\r\n");
                }

                (VOS_VOID)pstGetRdFun(EN_DMS_AT_CLIENT_ACM, pucVcomAtStore, ulReadLen);
            }

            dmsAtPcuiTaskSetSleepFlag(TRUE);
        }
        else
        {
            VOS_TaskDelay(100);
        }
    }

}




VOS_VOID dms_VcomCtrlAtTask(VOS_VOID)
{
#if (VOS_OS_VER == VOS_WIN32)
    VOS_UINT32 i;
    for(i = 0; i<1; i++)
#else
    for(;;)
#endif
    {
        if (FALSE == dms_GetPortHandle(EN_DMS_BEARER_USB_COM_CTRL))
        {
            if (VOS_OK != VOS_SmP(g_ulCtrlRxSem, 0))
            {
                vos_printf("dms_AtPcuiTask: VOS_SmP fail!\n");
            }
        }
        ctrlAtReadProc();
    }
}



VOS_VOID dms_AtPcuiTask(VOS_VOID)
{
#if (VOS_OS_VER == VOS_WIN32)
    VOS_UINT32 i;
    for(i = 0; i<1; i++)
#else
    for(;;)
#endif
    {
        if (FALSE == dms_GetPortHandle(EN_DMS_BEARER_USB_COM4_AT))
        {
            if (VOS_OK != VOS_SmP(g_ulPcuiRxSem, 0))
            {
                vos_printf("dms_AtPcuiTask: VOS_SmP fail!\n");
            }
        }
        vcomAtReadProc();
    }
}



VOS_VOID dms_VcomAtPcuiEvtCB(ACM_EVT_E  ulEvt)
{
    DMS_PHY_BEAR_PROPERTY_STRU* aenPhyBear = dmsgetPhyBearProperty();
/*    DMS_LOGIC_CHAN_ENUM enLogic = EN_DMS_CHANNEL_LAST; */

    DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_AT_EVT, ulEvt, 0, 0);

    if(ACM_EVT_DEV_READY==ulEvt)
    {
        aenPhyBear[EN_DMS_BEARER_USB_COM4_AT].ucChanStat = ACM_EVT_DEV_READY;
        return ;
    }
    else
    {
/*        enLogic = aenPhyBear[EN_DMS_BEARER_USB_COM4_AT].aenLogicChan; */

        aenPhyBear[EN_DMS_BEARER_USB_COM4_AT].ucChanStat =ACM_EVT_DEV_SUSPEND;

        /*�ָ�Ĭ������*/
        aenPhyBear[EN_DMS_BEARER_USB_COM4_AT].aenLogicChan = EN_DMS_CHANNEL_AT;
    }
    return;
}



VOS_VOID dms_VcomCtrlEvtCB(ACM_EVT_E  ulEvt)
{
    DMS_PHY_BEAR_PROPERTY_STRU* aenPhyBear = dmsgetPhyBearProperty();
/*    DMS_LOGIC_CHAN_ENUM enLogic = EN_DMS_CHANNEL_LAST; */

    if(ACM_EVT_DEV_READY==ulEvt)
    {
        aenPhyBear[EN_DMS_BEARER_USB_COM_CTRL].ucChanStat = ACM_EVT_DEV_READY;
        return ;
    }
    else
    {
/*        enLogic = aenPhyBear[EN_DMS_BEARER_USB_COM_CTRL].aenLogicChan; */

        aenPhyBear[EN_DMS_BEARER_USB_COM_CTRL].ucChanStat =ACM_EVT_DEV_SUSPEND;

        /*�ָ�Ĭ������*/
        aenPhyBear[EN_DMS_BEARER_USB_COM_CTRL].aenLogicChan = EN_DMS_CHANNEL_AT;
    }
    return;
}



VOS_VOID dms_VcomAtPcuiWrtCB (char* pDoneBuff, int s32DoneSize)
{
    DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_AT_WRT_CB,(VOS_UINT32)pDoneBuff , (VOS_UINT32)s32DoneSize, 0);

    if(s32DoneSize < 0)
    {
       DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_AT_WRT_CB_ERR,(VOS_UINT32)pDoneBuff , (VOS_UINT32)s32DoneSize, 0);
    }

    if(Dms_IsStaticBuf ((VOS_UINT8*)pDoneBuff))
    {
        Dms_FreeStaticBuf((VOS_UINT8*)pDoneBuff);
    }
    else
    {
        if(pDoneBuff != NULL)
        {
#if (VOS_LINUX== VOS_OS_VER)
            kfree(pDoneBuff);
#endif
        }

    }

    return;
}



VOS_VOID dms_VcomCtrlWrtCB (char* pDoneBuff, int s32DoneSize)
{
    DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_CTRL_WRT_CB,(VOS_UINT32)pDoneBuff , (VOS_UINT32)s32DoneSize, 0);

    if(s32DoneSize <= 0)
    {
       DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_CTRL_WRT_CB_ERR,(VOS_UINT32)pDoneBuff , (VOS_UINT32)s32DoneSize, 0);
    }

    if(Dms_IsStaticBuf ((VOS_UINT8*)pDoneBuff))
    {
        Dms_FreeStaticBuf((VOS_UINT8*)pDoneBuff);
    }
    else
    {
        if(pDoneBuff != NULL)
        {
#if (VOS_LINUX== VOS_OS_VER)
            kfree(pDoneBuff);
#endif
        }
    }

    return;
}




VOS_UINT32 dmsVcomAtPcuiOpen(VOS_VOID)
{
    VOS_INT32 slUartHd = 0;
#if(FEATURE_ON == MBB_WPG_COMMON)
    VOS_UINT32 i = 0;
#endif
    VOS_UINT32 ret      = ERR_MSP_SUCCESS;
    DMS_PHY_BEAR_PROPERTY_STRU *pstVcomCfg;
    UDI_OPEN_PARAM  stParam ;

    pstVcomCfg =  dmsgetPhyBearProperty();

    if(pstVcomCfg[EN_DMS_BEARER_USB_COM4_AT].slPortHandle !=UDI_INVALID_HANDLE)
    {
        return ERR_MSP_SUCCESS;
    }

    DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_AT_OPEN, 0, 0, 0);

    stParam.devid =(UDI_DEVICE_ID)UDI_USB_ACM_AT;

#if(FEATURE_ON == MBB_WPG_COMMON)
    for(i = 0; i < PCUI_OPEN_TIMES; i++)
    {
        slUartHd = udi_open(&stParam);
        if (UDI_INVALID_HANDLE != slUartHd)
        {
            vos_printf("slUartHd is ok!\n");
            break;
        }
        vos_printf("udi_open times i = %u!\n", i);
        msleep(PCUI_OPEN_WAITTIME);
    }
#else
        slUartHd = udi_open(&stParam);
#endif
    if (UDI_INVALID_HANDLE != slUartHd)
    {
 #if (VOS_LINUX== VOS_OS_VER)
        /*ע��USB�¼��ص�*/
        if( 0 > udi_ioctl((int)slUartHd, (int)ACM_IOCTL_SET_EVT_CB, dms_VcomAtPcuiEvtCB))
        {
            DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_AT_OPEN_ERR, (VOS_UINT32)slUartHd, 0, 0);
        }

        /*ע���첽д��ɻص�*/
        if( 0 >udi_ioctl((int)slUartHd, (int)UDI_IOCTL_SET_WRITE_CB, dms_VcomAtPcuiWrtCB))
        {
            DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_AT_OPEN_ERR, (VOS_UINT32)slUartHd, 0, 1);
        }

        /*���ø�ͨ������bufΪ�ǿ�����ʽ*/
        if( 0 >udi_ioctl((int)slUartHd, (int)ACM_IOCTL_WRITE_DO_COPY, 0))
        {
            DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_AT_OPEN_ERR, (VOS_UINT32)slUartHd, 0, 2);
        }
#endif
#if(FEATURE_ON == MBB_WPG_COMMON)
        vos_printf("dmsVcomAtPcuiOpen success!\n");
#endif
        pstVcomCfg[EN_DMS_BEARER_USB_COM4_AT].slPortHandle = slUartHd;
        VOS_SmV(g_ulPcuiRxSem);
        return ret;
    }
#if(FEATURE_ON == MBB_WPG_COMMON)
    vos_printf("dmsVcomAtPcuiOpen error!\n");
#endif
    DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_AT_OPEN_ERR, (VOS_UINT32)slUartHd, 0, 3);

    return ERR_MSP_FAILURE;

}



VOS_UINT32 dmsVcomCtrolOpen(VOS_VOID)
{
    VOS_INT32 slUartHd = UDI_INVALID_HANDLE;
    VOS_UINT32 ret      = ERR_MSP_SUCCESS;
    DMS_PHY_BEAR_PROPERTY_STRU *pstVcomCfg;

    UDI_OPEN_PARAM  stParam ;

    pstVcomCfg =  dmsgetPhyBearProperty();

    if(pstVcomCfg[EN_DMS_BEARER_USB_COM_CTRL].slPortHandle !=UDI_INVALID_HANDLE)
    {
        return ERR_MSP_SUCCESS;
    }

    DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_CTRL_OPEN, 0, 0, 0);

    stParam.devid =(UDI_DEVICE_ID)UDI_USB_ACM_CTRL;

    slUartHd = udi_open(&stParam);

    if (UDI_INVALID_HANDLE != slUartHd)
    {

#if (VOS_LINUX== VOS_OS_VER)

         /*ע��USB�¼��ص�*/
        if( 0 > udi_ioctl((int)slUartHd, (int)ACM_IOCTL_SET_EVT_CB, dms_VcomCtrlEvtCB))
        {
            DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_CTRL_OPEN_ERR, (VOS_UINT32)slUartHd, 0, 0);
        }

        /*ע���첽д��ɻص�*/
        if( 0 >udi_ioctl((int)slUartHd, (int)UDI_IOCTL_SET_WRITE_CB, dms_VcomCtrlWrtCB))
        {
            DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_CTRL_OPEN_ERR, (VOS_UINT32)slUartHd, 0, 1);
        }

        /*���ø�ͨ������bufΪ�ǿ�����ʽ*/
        if( 0 >udi_ioctl((int)slUartHd, (int)ACM_IOCTL_WRITE_DO_COPY, 0))
        {
            DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_CTRL_OPEN_ERR, (VOS_UINT32)slUartHd, 0, 2);
        }
#endif
        pstVcomCfg[EN_DMS_BEARER_USB_COM_CTRL].slPortHandle = slUartHd;
        VOS_SmV(g_ulCtrlRxSem);
        return ret;
    }

    DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_CTRL_OPEN_ERR, (VOS_UINT32)slUartHd, 0, 3);

    return ERR_MSP_FAILURE;

}



VOS_UINT32 dmsVcomAtPcuiClose(VOS_VOID)
{
    VOS_INT32 slVcomRet = ERR_MSP_SUCCESS;

    DMS_PHY_BEAR_PROPERTY_STRU* aenPhyBear = dmsgetPhyBearProperty();

    if(aenPhyBear[EN_DMS_BEARER_USB_COM4_AT].slPortHandle ==UDI_INVALID_HANDLE)
    {
        return ERR_MSP_SUCCESS;
    }

    DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_AT_CLOSE, 0, 0, 0);

    slVcomRet = udi_close((int)aenPhyBear[EN_DMS_BEARER_USB_COM4_AT].slPortHandle);

    if (slVcomRet == ERR_MSP_SUCCESS)
    {
        aenPhyBear[EN_DMS_BEARER_USB_COM4_AT].slPortHandle = UDI_INVALID_HANDLE;

        aenPhyBear[EN_DMS_BEARER_USB_COM4_AT].ucChanStat =ACM_EVT_DEV_SUSPEND;

        return (VOS_UINT32)slVcomRet;
    }

    DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_AT_CLOSE_ERR, (VOS_UINT32)slVcomRet, 0, 0);

    return ERR_MSP_FAILURE;

}



VOS_UINT32 dmsVcomCtrlClose(VOS_VOID)
{
    VOS_INT32 slVcomRet = ERR_MSP_SUCCESS;

    DMS_PHY_BEAR_PROPERTY_STRU* aenPhyBear = dmsgetPhyBearProperty();

    if(aenPhyBear[EN_DMS_BEARER_USB_COM_CTRL].slPortHandle ==UDI_INVALID_HANDLE)
    {
        return ERR_MSP_SUCCESS;
    }

    DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_CTRL_CLOSE, 0, 0, 0);

    slVcomRet = udi_close((int)aenPhyBear[EN_DMS_BEARER_USB_COM_CTRL].slPortHandle);

    if (slVcomRet == ERR_MSP_SUCCESS)
    {
        aenPhyBear[EN_DMS_BEARER_USB_COM_CTRL].slPortHandle = UDI_INVALID_HANDLE;
        aenPhyBear[EN_DMS_BEARER_USB_COM_CTRL].ucChanStat =ACM_EVT_DEV_SUSPEND;

        return (VOS_UINT32)slVcomRet;
    }

    DMS_DEBUG_SDM_FUN(EN_SDM_DMS_VCOM_CTRL_CLOSE_ERR, (VOS_UINT32)slVcomRet, 0, 0);

    return ERR_MSP_FAILURE;

}

VOS_UINT32 DMS_OpenHsicPort()
{
    return 0;
}

VOS_VOID DMS_ShowReadCnt(VOS_VOID)
{
    vos_printf("=======DMS Read Count\n");
    vos_printf("pcui        : %u \n", g_ulPcuiReadUdiCnt);
    vos_printf("ctrl        : %u \n", g_ulCtrlReadUdiCnt);
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

