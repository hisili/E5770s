

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "v_IO.h"
#include "OmApp.h"
#include "omrl.h"
#include "omringbuffer.h"
#include "omprivate.h"
#include "NVIM_Interface.h"
#include "omprintf.h"

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#include "PsLogAdapterApp.h"
#endif

#if (VOS_OS_VER == VOS_LINUX)
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kallsyms.h>
#include <asm/uaccess.h>
#endif
#include "omnvinterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_PRINTF_C
/*lint +e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* OM Printf���뻷�λ�����ID */
OM_RING_ID                          g_pstOmPrintfBufId;

/* OM Printf����˿ڣ�Ĭ��ΪSHELL�� */
VOS_UINT32                          g_ulOmPrintfPort = OM_OUTPUT_SHELL;

/* Printf BUFFER �����ź��� */
VOS_UINT32                          g_ulOmPrintfBuffSem;

/* �Դ��������ź��� */
VOS_UINT32                          g_ulPrintfTaskSem;

/* ��¼OM Printf �����������buffer���� */
OM_PRINTF_ERROR_RECORD_STRU         g_stOmPrintfErrRecord;

/* ��¼OM Printf ��������л�ȡ�ź���ʧ�ܣ���������ʧ�ܵȴ������� */
VOS_UINT32                          g_ulPrintfErrType = OM_OK;

/* ��ʶOM Printfģ���Ƿ��ʼ��*/
VOS_BOOL                            g_bIsPrintfInit = VOS_FALSE;

/* ����ģ���ӡ���� */
LOG_LEVEL_EN                        g_astOmPrintfOutPutLev[OM_PRINTF_MODULE_MAX_NUM];

#if (VOS_OS_VER == VOS_LINUX)
extern ssize_t OmPrintfModule_Write(struct file *file, const char __user *buf, size_t lLength, loff_t *ppos);
extern ssize_t OmPrintf_Write(struct file *file, const char __user *buf, size_t lLength, loff_t *ppos);
extern VOS_UINT32 OmPrintf_VFInit(VOS_VOID);

#define OM_VFILE_CRT_LEVEL (0660)

static const struct file_operations g_stOmPrintf_FOPS =
{
    .owner      = THIS_MODULE,
    .write      = OmPrintf_Write,
};

static const struct file_operations g_stOmPrintfModule_FOPS =
{
    .owner      = THIS_MODULE,
    .write      = OmPrintfModule_Write,
};
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/



VOS_UINT32 OM_PrintfGetModuleIdLev(VOS_UINT32 ulModuleId)
{
    return g_astOmPrintfOutPutLev[ulModuleId-LOG_MIN_MODULE_ID_ACPU_DRV];
}

unsigned long OM_PrintfSetModuleIdLev(unsigned long ulModuleId, unsigned long ulLev)
{
    /* ���������� */
    if((LOG_MAX_MODULE_ID_APP < ulModuleId)||(LOG_MIN_MODULE_ID_ACPU_DRV > ulModuleId)
                                       || (LOG_LEVEL_BUTT <= ulLev))
    {
#if (VOS_OS_VER == VOS_LINUX)
        printk("\r\nOM_PrintfSetModuleIdLev:Unvalid para! ModuleID:%d, Level:%d",(VOS_INT)ulModuleId, (VOS_INT)ulLev);
#else
        printf("OM_PrintfSetModuleIdLev:Unvalid para!");
#endif
        return OM_ERR_UNVALIDPARA;
    }

    g_astOmPrintfOutPutLev[ulModuleId-LOG_MIN_MODULE_ID_ACPU_DRV] = (LOG_LEVEL_EN)ulLev;

    return OM_OK;
}


VOS_UINT32 OM_PrintfSetOutLev(LOG_ID_LEVEL_STRU *pstLogIdLevel, VOS_UINT32 ulLength)
{
    VOS_UINT32         ulIndex;
    VOS_UINT32         ulModuleNum;
    VOS_UINT32         ulModuleId;
    VOS_UINT32         ulLev;

    /*�������ĺϷ���*/
    if (VOS_ERR == Log_CheckPara(pstLogIdLevel, ulLength))
    {
        return VOS_ERR;
    }

    ulModuleNum = pstLogIdLevel->ulModuleNum;

    /*��ÿ��ģ��Ĵ�ӡ�������뵽ȫ�ֹ��˱���*/
    for (ulIndex = 0; ulIndex < ulModuleNum; ulIndex++)
    {
        ulModuleId = pstLogIdLevel->astModuleLev[ulIndex].ulModuleId;
        ulLev      = pstLogIdLevel->astModuleLev[ulIndex].enPrintLev;

        OM_PrintfSetModuleIdLev(ulModuleId,ulLev);
    }

    return VOS_OK;
}


VOS_VOID OM_PrintfMsgProc(OM_REQ_PACKET_STRU *pstRspPacket, OM_RSP_FUNC *pstRspFuncPtr)
{
    APP_OM_MSG_EX_STRU             *pstAppToOmMsg;
    VOS_UINT16                      usReturnPrimId;
    VOS_UINT32                      ulRet = VOS_ERR;
    VOS_UINT32                      ulOutputType;

    pstAppToOmMsg   = (APP_OM_MSG_EX_STRU*)pstRspPacket;

    /* SDT��̬�޸�OM_Printf����˿� */
    if (APP_OM_SET_PRINTF_PORT_REQ == pstAppToOmMsg->usPrimId)
    {
        /* ��ȡ��Ϣ�ж˿����� */
        ulOutputType    = *((VOS_UINT32*)pstAppToOmMsg->aucPara);

        /* ����ж� */
        if( OM_OUTPUT_BUTT <= ulOutputType)
        {
            vos_printf("OM_PrintfMsgProc:wrong output port: %d\n", ulOutputType);
            return;
        }

        usReturnPrimId = OM_APP_SET_PRINTF_PORT_CNF;
        g_ulOmPrintfPort = ulOutputType;

        ulRet = VOS_OK;
    }

    /*������־��ӡ�����ԭ����Ϣ*/
    else if (APP_OM_SET_PRINTF_OUTPUT_LEV_REQ == pstAppToOmMsg->usPrimId)
    {
        usReturnPrimId = APP_OM_SET_PRINTF_OUTPUT_LEV_CNF;

        ulRet = OM_PrintfSetOutLev((LOG_ID_LEVEL_STRU*)(pstAppToOmMsg->aucPara),
          pstAppToOmMsg->usLength - (OM_APP_MSG_EX_LEN - VOS_OM_HEADER_LEN));
    }
    else
    {
        vos_printf("OM_PrintfMsgProc :Undefined PrimId : %d\n", pstAppToOmMsg->usPrimId);
        return;
    }

    /* �����ý�����͸�PC�� */
    OM_AppGreenChannel(OM_PRINTF_FUNC, usReturnPrimId,(VOS_UINT8*)&ulRet, sizeof(ulRet));

    return;
}


VOS_UINT32 OM_PrintfDataPut(VOS_CHAR *pucDataBuf, VOS_UINT32 ulDataLen)
{
    VOS_UINT32          ulFreeSize;
    VOS_UINT32          ulRet;
    VOS_UINT32          ulReturn = OM_OK;
    VOS_UINT32          ulBufAlignLen;
    VOS_CHAR            *pcWarning;

    /* OM Printfδ��ʼ��ʱ������ӡ�����SHELL����ӡʱ����ģ��ID�ĸ��ֽ� */
    if(VOS_FALSE == g_bIsPrintfInit)
    {
#if (VOS_OS_VER == VOS_LINUX)
        printk( "%s", pucDataBuf + OM_PRINTF_OFFSET);
#else
        printf( "%s", pucDataBuf + OM_PRINTF_OFFSET);
#endif
        return OM_OK;
    }

    g_stOmPrintfErrRecord.ulOmPrintfRecvLen += ulDataLen;
    g_stOmPrintfErrRecord.usOmPrintfRecvCount++;

    /* ��ȡbuffer�������ź��� */
    if(VOS_OK != VOS_SmP(g_ulOmPrintfBuffSem, 0))
    {
        g_ulPrintfErrType = OM_ERR_FAILTAKESEM;
        return OM_ERR_FAILTAKESEM;
    }

    /* �鿴OM Printf ringbuffer ʣ��ռ� */
    ulFreeSize = (VOS_UINT32)OM_RingBufferFreeBytes(g_pstOmPrintfBufId);

    ulBufAlignLen = (ulDataLen+OM_ALIGNMENT)&(~OM_ALIGNMENT);

    /* ���ݳ��ȼ����ֽڳ����ֶ� */
    if ((ulBufAlignLen + sizeof(VOS_UINT32)) > ulFreeSize)
    {
       g_stOmPrintfErrRecord.ulOmPrintfNoPrintfBufferLostLen
                          += ((OM_PRINTF_BUFFER_SIZE - ulFreeSize) + ulDataLen);
       g_stOmPrintfErrRecord.usOmPrintfNoPrintfBufferLostCount++;
       g_ulPrintfErrType = OM_ERR_NOBUF;

       /* OM Printf��������ʱ�����ringbuffer����ʾ�û������ݶ�ʧ */
       OM_RingBufferFlush(g_pstOmPrintfBufId);

       pcWarning = "OM_Printf:Warning!Some data lost!\n";

       *((VOS_UINT32*)pucDataBuf)     = WUEPS_PID_OM;
       *(((VOS_UINT32*)pucDataBuf)+1) = LOG_LEVEL_INFO;

       /* �������ڴ��ģ��ID��ǰ���ֽ� */
       VOS_StrCpy(pucDataBuf + OM_PRINTF_OFFSET, pcWarning );
       ulDataLen = VOS_StrLen(pcWarning)+OM_PRINTF_OFFSET;
       ulBufAlignLen = (ulDataLen+OM_ALIGNMENT)&(~OM_ALIGNMENT);

       ulReturn = OM_ERR_NOBUF;
    }

    /* �ѳ����ֶη���OM Printf ringbuffer*/
    ulRet = (VOS_UINT32)OM_RingBufferPut(g_pstOmPrintfBufId, (VOS_CHAR *)&ulDataLen,
                                         (VOS_INT)sizeof(VOS_UINT32));
    if(sizeof(VOS_UINT32) != ulRet)
    {
        OM_RingBufferFlush(g_pstOmPrintfBufId);
        VOS_SmV(g_ulOmPrintfBuffSem);
        g_ulPrintfErrType = OM_ERR_FAILPUTDATA;
        return OM_ERR_FAILPUTDATA;
    }

    /* �����ݷ���OM Printf ringbuffer*/
    ulRet = (VOS_UINT32)OM_RingBufferPut(g_pstOmPrintfBufId, pucDataBuf,(VOS_INT)ulBufAlignLen);
    if(ulBufAlignLen != ulRet)
    {
        OM_RingBufferFlush(g_pstOmPrintfBufId);
        VOS_SmV(g_ulOmPrintfBuffSem);
        g_ulPrintfErrType = OM_ERR_FAILPUTDATA;
        return OM_ERR_FAILPUTDATA;
    }

    VOS_SmV(g_ulOmPrintfBuffSem);

    /* �ͷ��Դ��������ź��� */
    VOS_SmV(g_ulPrintfTaskSem);

    return ulReturn;

}

/*lint -e960 */
unsigned long OM_PrintfWithModule(unsigned long ulModuleId, unsigned long ulLevel, char * pcformat, ... )
/*lint +e960 */
{
    VOS_UINT32          ulReturn = OM_OK;
    VOS_CHAR            *pcWarning;
    VOS_UINT32          ulTempLen;
    VOS_INT32           lRetLen;
    va_list             argument;
    VOS_UINT32          ulDataLen = 0;

    /* ����ǰ���ֽڴ洢ģ��ID���ӵھ��ֽڿ�ʼΪת�����ַ�����Ϊȷ����ת��Ϊ�ַ���
     �����в�Խ�磬�ඨ�����ֽ������� */
    /*lint -e813 */
    VOS_CHAR            acOutput[VOS_MAX_PRINT_LEN + 12];
    /*lint +e813 */

#if (VOS_OS_VER == VOS_LINUX)
    if(in_interrupt())
    {
        printk("\r\nOM_PrintfWithModule: RUN in the IRQ");

        return OM_ERR_RUNINIRQ;
    }
#endif

    /* ���������� */
    if((LOG_MAX_MODULE_ID_APP < ulModuleId)||(LOG_MIN_MODULE_ID_ACPU_DRV > ulModuleId)
                                       ||(LOG_LEVEL_BUTT <= ulLevel))
    {
        vos_printf("\r\nOM_PrintfWithModule: Para Error, ModuleId is %d, Level is %d", ulModuleId, ulLevel);
        return OM_ERR_UNVALIDPARA;
    }

    ulReturn = OM_PrintfGetModuleIdLev(ulModuleId);
    if((ulLevel > ulReturn)||(LOG_LEVEL_OFF == ulLevel))
    {
        return OM_ERR_LOWLEVEL;
    }

    *((VOS_UINT32*)acOutput) = ulModuleId;
    *(((VOS_UINT32*)acOutput)+1) = ulLevel;

    /* ����ʽ���ַ����Ϳɱ����ת��Ϊ�ַ��� */
    va_start( argument, pcformat );
    lRetLen = VOS_nvsprintf(acOutput + OM_PRINTF_OFFSET, VOS_MAX_PRINT_LEN, pcformat, argument);
    va_end( argument );

    /* ����ַ���������־ */
    acOutput[VOS_MAX_PRINT_LEN + OM_PRINTF_OFFSET - 1] = '\0';

    /* ��ת����������жϣ�����ת�����ַ����������Ӧ��ʾ��Ϣ */
    if(lRetLen >= (VOS_MAX_PRINT_LEN - 1))
    {
        pcWarning = "OM_Printf: Warning!Print too long!!!";
        ulTempLen = VOS_StrLen(pcWarning );
        VOS_MemCpy(acOutput + OM_PRINTF_OFFSET, pcWarning, ulTempLen);

        /* ��ת�����ַ��������ڶ����ֽ���ӻ��з� */
        acOutput[VOS_MAX_PRINT_LEN + OM_PRINTF_OFFSET- 2] = '\n';
        ulDataLen = VOS_MAX_PRINT_LEN + OM_PRINTF_OFFSET- 1;
    }
    else if( lRetLen < 0 )
    {
        pcWarning = "OM_Printf:unknown internal error.\r\n";
        VOS_StrCpy(acOutput + OM_PRINTF_OFFSET, pcWarning );
        ulDataLen = VOS_StrLen(pcWarning ) + OM_PRINTF_OFFSET;
    }
    else
    {
        ulDataLen = (VOS_UINT32)lRetLen + OM_PRINTF_OFFSET;
    }

    ulReturn = OM_PrintfDataPut(acOutput, ulDataLen);

    return ulReturn;
}


/*lint -e960 */
unsigned long OM_Printf(char * pcformat, ... )
/*lint +e960 */
{
    VOS_UINT32          ulReturn = OM_OK;
    VOS_CHAR            *pcWarning;
    VOS_UINT32          ulTempLen;
    VOS_INT32           lRetLen;
    va_list             argument;
    VOS_UINT32          ulDataLen = 0;

    /* ����ǰ���ֽڴ洢ģ��ID�������ĸ�ֱ�Ӵ洢��ӡ���𣬴ӵھ��ֽڿ�ʼΪת�����ַ�����Ϊȷ����ת��Ϊ�ַ���
     �����в�Խ�磬�ඨ�����ֽ������� */
    /*lint -e813 */
    VOS_CHAR            acOutput[VOS_MAX_PRINT_LEN + 12];
    /*lint +e813 */

#if (VOS_OS_VER == VOS_LINUX)
    if(in_interrupt())
    {
        printk("\r\nOM_Printf: RUN in the IRQ");

        return OM_ERR_RUNINIRQ;
    }
#endif

    *((VOS_UINT32*)acOutput)     = ACPU_PID_OM;
    *(((VOS_UINT32*)acOutput)+1) = LOG_LEVEL_INFO;

    /* ����ʽ���ַ����Ϳɱ����ת��Ϊ�ַ��� */
    va_start( argument, pcformat );
    lRetLen = VOS_nvsprintf(acOutput + OM_PRINTF_OFFSET, VOS_MAX_PRINT_LEN, pcformat, argument);
    va_end( argument );

    /* ����ַ���������־ */
    acOutput[VOS_MAX_PRINT_LEN + OM_PRINTF_OFFSET - 1] = '\0';

    /* ��ת����������жϣ�����ת�����ַ����������Ӧ��ʾ��Ϣ */
    if( lRetLen >= (VOS_MAX_PRINT_LEN - 1) )
    {
        pcWarning = "OM_Printf: Warning!Print too long!!!";
        ulTempLen = VOS_StrLen(pcWarning );
        VOS_MemCpy(acOutput + OM_PRINTF_OFFSET, pcWarning, ulTempLen);

        /* ��ת�����ַ��������ڶ����ֽ���ӻ��з� */
        acOutput[VOS_MAX_PRINT_LEN + OM_PRINTF_OFFSET- 2] = '\n';
        ulDataLen = VOS_MAX_PRINT_LEN + OM_PRINTF_OFFSET - 1;
    }
    else if( lRetLen < 0 )
    {
        pcWarning = "OM_Printf:unknown internal error.\r\n";
        VOS_StrCpy(acOutput + OM_PRINTF_OFFSET, pcWarning );
        ulDataLen = VOS_StrLen(pcWarning ) + OM_PRINTF_OFFSET;
    }
    else
    {
        ulDataLen = (VOS_UINT32)lRetLen + OM_PRINTF_OFFSET;
    }

    ulReturn = OM_PrintfDataPut(acOutput, ulDataLen);

    return ulReturn;
}


VOS_VOID OM_SndPrintfToOm(VOS_CHAR *pcData, VOS_UINT32 ulLength)
{
    VOS_UINT32          ulRet;
    OM_APP_TRACE_STRU   *pstAppMsg;

    /* ������Ϣ�ռ� */
    pstAppMsg = (OM_APP_TRACE_STRU*)VOS_MemAlloc(WUEPS_PID_OM,
                                         DYNAMIC_MEM_PT, ulLength + OM_APP_TRACE_LEN);
    if (VOS_NULL_PTR == pstAppMsg)
    {
        g_ulPrintfErrType = OM_ERR_MALLOC;
        return;
    }

    /* ������Ϣ���� */
    VOS_MemCpy(pstAppMsg->aucPara, pcData, ulLength);

    /* �����Ϣͷ���ֶ� */
    pstAppMsg->stAppHeader.ucFuncType   = OM_PRINTF_FUNC;
    pstAppMsg->stAppHeader.usLength     = ((VOS_UINT16)ulLength + OM_APP_TRACE_LEN)
                                                                - VOS_OM_HEADER_LEN;
    pstAppMsg->usPrimId                 = OM_APP_OM_PRINTF_IND;
    pstAppMsg->usToolId                 = 0;

    /* �����Ϣ��ź�ʱ��� */
    OM_AcpuAddSNTime(&(pstAppMsg->stAppHeader.ulSn), &(pstAppMsg->stAppHeader.ulTimeStamp));

    /* ����OM API�����ݷ���OM��· ringbuffer*/
    ulRet = OM_AcpuSendData((OM_RSP_PACKET_STRU*)pstAppMsg, (VOS_UINT16)(ulLength + OM_APP_TRACE_LEN));
    if (VOS_OK != ulRet)
    {
        g_ulPrintfErrType = OM_ERR_SENDTOOMBUF;
    }

    VOS_MemFree(WUEPS_PID_OM, pstAppMsg);

    return;
}


VOS_UINT32 OM_PrintfInit(VOS_VOID)
{
    OM_PORT_CFG_STRU                    stPortCfg;
    NAS_NVIM_SYSTEM_APP_CONFIG_STRU     stAPPConfig;

    stAPPConfig.usSysAppConfigType = SYSTEM_APP_BUTT;

    if(NV_OK != NV_Read(en_NV_Item_System_APP_Config, &stAPPConfig, sizeof(NAS_NVIM_SYSTEM_APP_CONFIG_STRU)))
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "OM_AcpuSelfTaskReg:Read NV en_NV_Item_System_APP_Config fail!");
    }

    if(SYSTEM_APP_WEBUI != stAPPConfig.usSysAppConfigType)
    {
        return VOS_OK;
    }

    VOS_MemSet(&g_stOmPrintfErrRecord, 0, sizeof(OM_PRINTF_ERROR_RECORD_STRU));

    VOS_MemSet(g_astOmPrintfOutPutLev, LOG_LEVEL_OFF, OM_PRINTF_MODULE_MAX_NUM*sizeof(LOG_LEVEL_EN));

    /* ��NV���ȡ����˿����ú��ļ���С����ʧ����Ĭ������˿�ΪSHELL�ڣ�
    �ļ���СΪ0��ʾȡĬ���ļ���С */
    if(NV_OK != NV_Read(en_NV_Item_Om_Printf_Port, &stPortCfg, sizeof(OM_PORT_CFG_STRU)))
    {
        stPortCfg.ulMaxFileSize = 0;
    }
    else
    {
        /* �ж϶˿ڷ�Χ */
        if (OM_OUTPUT_BUTT > stPortCfg.enPortType)
        {
            g_ulOmPrintfPort = (VOS_UINT32)stPortCfg.enPortType;
        }
    }

    /* ����Printf BUFFER �����ź��� */
    if(VOS_OK != VOS_SmMCreate("Pt", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE,
                                &g_ulOmPrintfBuffSem))
    {
        return VOS_ERR;
    }

    /*�����洢OM_Printf���ݵĻ��λ�����*/
    g_pstOmPrintfBufId = OM_RingBufferCreate(OM_PRINTF_BUFFER_SIZE);
    if (VOS_NULL_PTR == g_pstOmPrintfBufId)
    {
        VOS_SmDelete(g_ulOmPrintfBuffSem);
        return VOS_ERR;
    }

#if (VOS_OS_VER == VOS_LINUX)
    if (VOS_OK != OmPrintf_VFInit())
    {
        VOS_SmDelete(g_ulOmPrintfBuffSem);
        return VOS_ERR;
    }
#endif

    DRV_MSP_PROC_REG(OM_PRINTF_WITH_MODULE,     (BSP_MspProc)OM_PrintfWithModule);
    DRV_MSP_PROC_REG(OM_PRINTF,                 (BSP_MspProc)OM_Printf);
    DRV_MSP_PROC_REG(OM_PRINTF_GET_MODULE_IDLEV,(BSP_MspProc)OM_PrintfGetModuleIdLev);
    /* ģ���ʼ�����ȫ�ֱ�����TRUE*/
    g_bIsPrintfInit = VOS_TRUE;

    return VOS_OK;
}


VOS_VOID OM_PrintfTask(VOS_VOID)
{
    VOS_UINT32          ulBufLen;
    VOS_UINT32          ulBufAlignLen;
#if (VOS_WIN32 == VOS_OS_VER)
    VOS_UINT32          i;
#endif

    /*lint -e813 */
    /* ǰ���ֽ������洢ģ��ID */
    VOS_CHAR            acOutput[VOS_MAX_PRINT_LEN+8];
    /*lint +e813 */

    VOS_UINT32          ulRet;

    if ( VOS_OK != VOS_SmBCreate( "PRT", 0, VOS_SEMA4_FIFO, &g_ulPrintfTaskSem))
    {
        return;
    }

#if (VOS_WIN32 == VOS_OS_VER)
    for (i = 0; i < 1; i++)
#else
    for (;;)
#endif
    {

        if(VOS_OK != VOS_SmP(g_ulPrintfTaskSem, 0))
        {
            g_ulPrintfErrType = OM_ERR_FAILTAKETASKSEM;
            continue;
        }

        /* ringbuf�������� */
#if (VOS_WIN32 == VOS_OS_VER)
        for (i = 0; i < 1; i++)
#else
        while(VOS_FALSE == OM_RingBufferIsEmpty(g_pstOmPrintfBufId))
#endif
        {
            /* ��ȡ���ݳ��� */
            ulRet = (VOS_UINT32)OM_RingBufferGet(g_pstOmPrintfBufId, (VOS_CHAR *)&ulBufLen,
                                                 sizeof(VOS_UINT32));
            if (sizeof(VOS_UINT32) != ulRet)
            {
                g_ulPrintfErrType = OM_ERR_FAILPUTDATA;
                OM_RingBufferFlush(g_pstOmPrintfBufId);
                continue;
            }

            /* ringbuf�������� */
            if (VOS_MAX_PRINT_LEN <= ulBufLen)
            {
                g_ulPrintfErrType = OM_ERR_DATADESTROY;
                OM_RingBufferFlush(g_pstOmPrintfBufId);
                continue;
            }

            ulBufAlignLen = (ulBufLen+OM_ALIGNMENT)&(~OM_ALIGNMENT);

            /* ��ȡ�������� */
            ulRet = (VOS_UINT32)OM_RingBufferGet(g_pstOmPrintfBufId, (VOS_CHAR *)acOutput,
                                (VOS_INT)ulBufAlignLen);
            if (ulBufAlignLen != ulRet)
            {
                g_ulPrintfErrType = OM_ERR_FAILPUTDATA;
                OM_RingBufferFlush(g_pstOmPrintfBufId);
                continue;
            }

            /* ��������˿ڷַ����� */
            switch(g_ulOmPrintfPort)
            {
                case OM_OUTPUT_SHELL:
                    acOutput[ulBufLen] = 0;
#if (VOS_OS_VER == VOS_LINUX)
                    printk( "%s", acOutput + OM_PRINTF_OFFSET);
#else
                    printf( "%s", acOutput + OM_PRINTF_OFFSET);
#endif
                    break;

                case OM_OUTPUT_SDT:
                    OM_SndPrintfToOm(acOutput, ulBufLen);
                    break;

                default:
                    break;
            }
        }
    }
}

#if (VOS_OS_VER == VOS_LINUX)


VOS_UINT32 OmPrintf_VFInit(VOS_VOID)
{
    if(VOS_NULL_PTR == proc_create("OmPrintf", OM_VFILE_CRT_LEVEL, VOS_NULL_PTR, &g_stOmPrintf_FOPS))
    {
        LogPrint("\r\nOmPrintf_VFInit: proc_create Return NULL");

        return VOS_ERR;
    }

    if(VOS_NULL_PTR == proc_create("OmPrintfModule", OM_VFILE_CRT_LEVEL, VOS_NULL_PTR, &g_stOmPrintfModule_FOPS))
    {
        LogPrint("\r\nOmPrintfModule_VFInit: proc_create Return NULL");

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 OmPrintfWriteData(VOS_UINT32 ulModuleID, VOS_UINT32 ulLevel, VOS_CHAR *pcStr, VOS_UINT32 ulStrLen)
{
    VOS_CHAR    *pcWarning;
    VOS_UINT32  ulTempLen;
    VOS_UINT32  ulDataLen;

    /* ����ǰ���ֽڴ洢ģ��ID�������ĸ�ֱ�Ӵ洢��ӡ���𣬴ӵھ��ֽڿ�ʼΪת�����ַ�����
    Ϊȷ����ת��Ϊ�ַ��������в�Խ�磬�ඨ�����ֽ������� */
    /*lint -e813 */
    VOS_CHAR    acOutput[VOS_MAX_PRINT_LEN + 12];
    /*lint +e813 */

    /*����ͷ����ҪĬ����д*/
    *((VOS_UINT32*)acOutput)     = ulModuleID;
    *(((VOS_UINT32*)acOutput)+1) = ulLevel;

    /* ����ַ���������־ */
    acOutput[VOS_MAX_PRINT_LEN + OM_PRINTF_OFFSET - 1] = '\0';

    /* ����������жϣ�����ת�����ַ����������Ӧ��ʾ��Ϣ */
    if( ulStrLen >= (VOS_MAX_PRINT_LEN - 1) )
    {
        pcWarning = "OM_Printf: Warning!Print too long!!!";
        ulTempLen = VOS_StrLen(pcWarning);
        VOS_MemCpy(acOutput + OM_PRINTF_OFFSET, pcWarning, ulTempLen);

        /* ��ת�����ַ��������ڶ����ֽ���ӻ��з� */
        acOutput[VOS_MAX_PRINT_LEN + OM_PRINTF_OFFSET- 2] = '\n';
        ulDataLen = VOS_MAX_PRINT_LEN + OM_PRINTF_OFFSET - 1;
    }
    else
    {
        ulDataLen = (VOS_UINT32)ulStrLen + OM_PRINTF_OFFSET;
        if ( VOS_OK != copy_from_user(acOutput + OM_PRINTF_OFFSET, pcStr, ulStrLen) ) /*�����û��ռ����ݵ��ں˿ռ�����*/
        {
            /* make Coverity happy*/
        }
    }

    OM_PrintfDataPut(acOutput, ulDataLen);

    return VOS_OK;
}



ssize_t OmPrintf_Write(struct file *file, const char __user *buf, size_t lLength, loff_t *ppos)
{
    if(in_interrupt())
    {
        printk("\r\nOmPrintf_Write: RUN in the IRQ");

        return VOS_OK;
    }

    return (ssize_t)OmPrintfWriteData(ACPU_PID_OM, LOG_LEVEL_INFO, (VOS_CHAR*)buf, (VOS_UINT32)lLength);
}



ssize_t OmPrintfModule_Write(struct file *file, const char __user *buf, size_t lLength, loff_t *ppos)
{
    OMPRITNF_MODULE_APP_STRU    *pstAppData;
    VOS_UINT32                  ulReturn;

    if(in_interrupt())
    {
        printk("\r\nOmPrintfModule_Write: RUN in the IRQ");

        return VOS_OK;
    }

    pstAppData = (OMPRITNF_MODULE_APP_STRU *)buf;

    /* ������� */
    if((LOG_MAX_MODULE_ID_APP < pstAppData->ulModuleId)||(LOG_MIN_MODULE_ID_ACPU_DRV > pstAppData->ulModuleId)
                                       ||(LOG_LEVEL_BUTT <= pstAppData->ulPrintLev))
    {
        printk("\r\n OmPrintfModule_Write: The Para is Error, ModuleId is %d, PrintLev is %d", (VOS_INT)pstAppData->ulModuleId, (VOS_INT)pstAppData->ulPrintLev);
        return VOS_ERROR;
    }

    ulReturn = OM_PrintfGetModuleIdLev(pstAppData->ulModuleId);

    if((pstAppData->ulPrintLev > ulReturn)||(LOG_LEVEL_OFF == pstAppData->ulPrintLev))
    {
        return VOS_ERROR;
    }

    return (ssize_t)OmPrintfWriteData(pstAppData->ulModuleId, pstAppData->ulPrintLev, pstAppData->aucStr, pstAppData->ulStrLen);
}

#endif

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif



