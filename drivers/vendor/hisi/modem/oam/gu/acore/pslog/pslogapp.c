
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/********************ͷ�ļ�****************************************************/

#include "vos.h"
#include "PsLogAdapterApp.h"
#include "omprivate.h"
#include "NVIM_Interface.h"
#include "omnvinterface.h"


/******************ȫ�ֱ�������************************************************/
#define THIS_FILE_ID PS_FILE_ID_PS_LOG_APP_C

/* ErrLogʵ�� */
MNTN_ERRLOG_STRU g_stErrLogStru;

/* Logʵ�� */
LOG_ENTITY_ST  g_stLogEnt =
{LOG_FALSE,  OM_OUTPUT_SHELL, LOG_NULL_PTR, LOG_NULL_PTR};

/*������RingBuffer���л������*/
LOG_SEM        g_logBuffSem;

/*ȫ�ֱ�������������ÿ��ģ��Ĵ�ӡ����*/

LOG_LEVEL_EN   g_aulLogPrintLevPsTable[LOG_PS_MODULE_MAX_NUM] = {LOG_LEVEL_OFF};
LOG_LEVEL_EN   g_aulLogPrintLevDrvTable[LOG_DRV_MODULE_MAX_NUM] = {LOG_LEVEL_OFF};

#if (FEATURE_ON == FEATURE_MULTI_FS_PARTITION) /* SFT board*/
/*�������ļ�ϵͳ�е�LOG�ļ���Ϣ*/
LOG_FILE_INFO_STRU g_astLogFileInfo[LOG_SOURCE_BUTT]
               = {{VOS_FALSE, LOG_FILE_1, 0, LOG_FILE_MAX_SIZE, 0, "/modem_log/Log/PsLog0"},
                  {VOS_FALSE, LOG_FILE_1, 0, LOG_FILE_MAX_SIZE, 0, "/modem_log/Log/Printf0"},
                  {VOS_FALSE, LOG_FILE_1, 0, (LOG_FILE_MAX_SIZE*2), 0, "/modem_log/Log/OmLog0"}};
#else
/*�������ļ�ϵͳ�е�LOG�ļ���Ϣ*/
LOG_FILE_INFO_STRU g_astLogFileInfo[LOG_SOURCE_BUTT]
               = {{VOS_FALSE, LOG_FILE_1, 0, LOG_FILE_MAX_SIZE, 0, "/yaffs0/Log/PsLog0"},
                  {VOS_FALSE, LOG_FILE_1, 0, LOG_FILE_MAX_SIZE, 0, "/yaffs0/Log/Printf0"},
                  {VOS_FALSE, LOG_FILE_1, 0, (LOG_FILE_MAX_SIZE*2), 0, "/yaffs0/Log/OmLog0"}};
#endif

/* ����LOGд��FLASH�ӿڵĶ�λ��Ϣ */
VOS_UINT32  g_ulLogErrFlag = LOG_OPERATION_OK;
#if (VOS_VXWORKS == VOS_OS_VER)
#if (FEATURE_ON == FEATURE_MULTI_FS_PARTITION) /* SFT board*/
VOS_CHAR    g_acLogDir[LOG_FILE_PATH_MAX_LENGTH] = "/modem_log/Log";
#else
/*LOG File Directory */
VOS_CHAR    g_acLogDir[LOG_FILE_PATH_MAX_LENGTH] = "/yaffs0/Log";
#endif

#elif (VOS_WIN32 == VOS_OS_VER)

/*LOG File Directory */
VOS_CHAR    g_acLogDir[] = "";

#endif

extern VOS_UINT32 OM_AcpuSendLog(VOS_UINT8 *pucLogData, VOS_UINT32 ulLength);


unsigned long LOG_GetTick(void)
{
#if ((VOS_OS_VER == VOS_VXWORKS)||(VOS_OS_VER == VOS_LINUX))
/*lint -e718*/
/*lint -e746*/

    /*��ASIC/FPGAƽ̨�£���Ҫ��Sliceֵת����tickֵ����֤��SDT����ʾһ��*/
    unsigned long   ulSlice;
    ulSlice = OM_GetSlice();
    /*Sliceֵÿ��һ������32768��ͨ�����¼���ת����10ms��tickֵ
    ��������7λ���ٳ���100����Ϊ�˷�ֹ���ݹ�������*/
    ulSlice >>= 7;
    ulSlice *= 100;
    ulSlice >>= 8;
    return ulSlice;

/*lint +e718*/
/*lint +e746*/

#elif(VOS_OS_VER == VOS_WIN32)
    return (unsigned long)GetTickCount();
#else
    return LOG_OK;
#endif
}


unsigned long Log_GetPrintLevel(VOS_UINT32 ulModuleId)
{
    /*������ΪOM���ʱ�������OMģ��Ĵ�ӡ��Ϣ�������п��ܻ������ѭ��*/
    if ((VOS_PID_BUTT == ulModuleId) && (OM_OUTPUT_SDT == g_stLogEnt.ulLogOutput))
    {
        return LOG_LEVEL_OFF;
    }
    /*�ж�ģ��ID�Ƿ���ACPU֧�ֵ�PS��Χ��*/
    if ((VOS_PID_DOPRAEND <= ulModuleId)
         && (VOS_PID_BUTT > ulModuleId))
    {
        return g_aulLogPrintLevPsTable[ulModuleId - VOS_PID_DOPRAEND];
    }
    /*�ж�ģ��ID�Ƿ���ACPU֧�ֵ�DRV��Χ��*/
    if ((LOG_MIN_MODULE_ID_ACPU_DRV <= ulModuleId)
         && (LOG_MAX_MODULE_ID_ACPU_DRV >= ulModuleId))
    {
        return g_aulLogPrintLevDrvTable[ulModuleId - LOG_MIN_MODULE_ID_ACPU_DRV];
    }
    return LOG_LEVEL_OFF;
}


long Log_GetPathOffset(char* pcFileName)
{
    long     lOffset;
    long     lOffset1;
    long     lOffset2;
    char    *pcPathPos;

    lOffset1  = 0;
    lOffset2  = 0;

    /* ����ϵͳ����ʹ��'\'������·�� */
    pcPathPos = (char*)strrchr(pcFileName, '\\');
    if (LOG_NULL_PTR != pcPathPos)
    {
        lOffset1 = (pcPathPos - pcFileName) + 1;
    }

    /* ����ϵͳ����ʹ��'/'������·�� */
    pcPathPos = (char*)strrchr(pcFileName, '/');
    if (LOG_NULL_PTR != pcPathPos)
    {
        lOffset2 = (pcPathPos - pcFileName) + 1;
    }

    lOffset = (lOffset1 > lOffset2) ? lOffset1 : lOffset2;

    return lOffset;
}


void Log_Init(void)
{
    OM_PORT_CFG_STRU    stPortCfg;

    g_stLogEnt.ulPrintSwitch = LOG_FALSE;

    if (VOS_OK != VOS_SmMCreate("LOG_MSem", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &g_logBuffSem))
    {
        vos_printf("Log: Error, semMCreate Fail");
        return ;
    }


    if (VOS_OK != VOS_SmCCreate("LOG_CSem", 0, VOS_SEMA4_FIFO, &(g_stLogEnt.semOmPrint)))
    {
        VOS_SmDelete(g_logBuffSem);
        vos_printf("Log: Error, semCCreate Fail");
        return ;
    }

    g_stLogEnt.rngOmRbufId = OM_RingBufferCreate(LOG_BUF_VOLUMN);
    if (LOG_NULL_PTR == g_stLogEnt.rngOmRbufId)
    {
        VOS_SmDelete(g_logBuffSem);
        VOS_SmDelete(g_stLogEnt.semOmPrint);
        vos_printf("Log: Error, rngCreate Fail");
        return;
    }

    /* ��NV���ж���LOG�������ʽ���ļ�֧�ֵ�����С */
    if(NV_OK != NV_Read(en_NV_Item_Om_PsLog_Port,
                                &stPortCfg,
                                sizeof(OM_PORT_CFG_STRU)))
    {
        vos_printf("Log_InitFile: NV_Read fail, NV Id :%d\n", en_NV_Item_Om_PsLog_Port);
        stPortCfg.ulMaxFileSize = 0;
    }
    else
    {
        /*�������*/
        if (OM_OUTPUT_BUTT > stPortCfg.enPortType)
        {
            g_stLogEnt.ulLogOutput = (LOG_ULONG)stPortCfg.enPortType;
        }
    }

    g_stLogEnt.ulPrintSwitch = LOG_TRUE;

    /* ע�����Ļص�����������OM_Log...... */
#ifdef __LOG_BBIT__
    LOG_RegisterDrv((LOG_PFUN)OM_Log, (LOG_PFUN)OM_Log1, (LOG_PFUN)OM_Log2,
                     (LOG_PFUN)OM_Log3, (LOG_PFUN)OM_Log4);
#endif

#ifdef __LOG_RELEASE__
    LOG_RegisterDrv((LOG_PFUN)OM_LogId, (LOG_PFUN)OM_LogId1, (LOG_PFUN)OM_LogId2,
                    (LOG_PFUN)OM_LogId3, (LOG_PFUN)OM_LogId4);
#endif

    return;
}

#ifdef __LOG_BBIT__


void OM_Log(char             *cFileName,  unsigned long      ulLineNum,
            LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN   enSubModId,
            LOG_LEVEL_EN      enLevel,    char              *pcString)
{
    Log_StrNParam(cFileName, ulLineNum, enModuleId, enSubModId, enLevel,
            pcString, 0, LOG_NULL_PTR);
    return;
}


void OM_Log1(char             *cFileName,  unsigned long      ulLineNum,
             LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN   enSubModId,
             LOG_LEVEL_EN      enLevel,    char              *pcString,
             long              lPara1)
{
    long alParam[4];
    alParam[0] = lPara1;

    Log_StrNParam(cFileName, ulLineNum, enModuleId, enSubModId, enLevel,
            pcString, 1, alParam);
    return;
}


void OM_Log2(char             *cFileName,  unsigned long      ulLineNum,
             LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN   enSubModId,
             LOG_LEVEL_EN      enLevel,    char              *pcString,
             long              lPara1,     long               lPara2)
{
    long alParam[4];

    alParam[0] = lPara1;
    alParam[1] = lPara2;

    Log_StrNParam(cFileName, ulLineNum, enModuleId, enSubModId, enLevel,
            pcString, 2, alParam);

    return;
}


void OM_Log3(char             *cFileName,  unsigned long      ulLineNum,
             LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN   enSubModId,
             LOG_LEVEL_EN      enLevel,    char              *pcString,
             long              lPara1,     long               lPara2,
             long              lPara3)
{
    long alParam[4];

    alParam[0] = lPara1;
    alParam[1] = lPara2;
    alParam[2] = lPara3;

    Log_StrNParam(cFileName, ulLineNum, enModuleId, enSubModId, enLevel,
            pcString, 3, alParam);

    return;
}


void OM_Log4(char             *cFileName,  unsigned long      ulLineNum,
             LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN   enSubModId,
             LOG_LEVEL_EN      enLevel,    char              *pcString,
             long              lPara1,     long               lPara2,
             long              lPara3,     long               lPara4)
{
    long alParam[4];

    alParam[0] = lPara1;
    alParam[1] = lPara2;
    alParam[2] = lPara3;
    alParam[3] = lPara4;

    Log_StrNParam(cFileName, ulLineNum, enModuleId, enSubModId, enLevel,
            pcString, 4, alParam);

    return;
}


void Log_BuildStr(char          *pcFileName,  unsigned long  ulLineNum,
                  LOG_LEVEL_EN   enPrintLev,  char          *pcOriStr,
                  unsigned char  ucParaCnt,   long          *plPara,
                  char          *pcDstStr,    unsigned long *pulLen)
{
    long            lTmpLen;
    long            lStrLen;
    long            lOffset;
    long            lParamLen;
    long            lSpareLen;
    long            lOccupyLen;
    unsigned char   i;

    *pulLen = 0;

    switch ( enPrintLev )
    {
        case LOG_LEVEL_ERROR :
            lTmpLen    = LOG_SNPRINTF( pcDstStr, LOG_MAX_COLUMN_VAL, "\nERROR,F: ");
            break;
        case LOG_LEVEL_WARNING :
            lTmpLen    = LOG_SNPRINTF( pcDstStr, LOG_MAX_COLUMN_VAL, "\nWARNING,F: ");
            break;
        case LOG_LEVEL_NORMAL :
            lTmpLen    = LOG_SNPRINTF( pcDstStr, LOG_MAX_COLUMN_VAL, "\nNORMAL,F: ");
            break;
        case LOG_LEVEL_INFO :
            lTmpLen    = LOG_SNPRINTF( pcDstStr, LOG_MAX_COLUMN_VAL, "\nINFO,F: ");
            break;
        default:
            lTmpLen    = LOG_SNPRINTF( pcDstStr, LOG_MAX_COLUMN_VAL, "\nF: ");
            break;
    }

    lOccupyLen = lTmpLen;
    LOG_AFFIRM(LOG_MAX_COLUMN_VAL >= lOccupyLen)

    lSpareLen  = LOG_MAX_COLUMN_VAL - lOccupyLen;
    LOG_AFFIRM(lSpareLen >= LOG_MAX_FILENAME_LEN)

        /* ��·��ȥ��,ֻ�����ļ����� */
    lOffset = Log_GetPathOffset(pcFileName);
    lTmpLen = (long)strlen(pcFileName + lOffset);
    if (lTmpLen < LOG_MAX_FILENAME_LEN)
    {
        memcpy(pcDstStr + lOccupyLen, pcFileName + lOffset, (unsigned int)lTmpLen);
        lOccupyLen += lTmpLen;
    }
    else
    {
        memcpy(pcDstStr + lOccupyLen, pcFileName + lOffset, LOG_MAX_FILENAME_LEN);
        lOccupyLen += LOG_MAX_FILENAME_LEN;
    }

    lSpareLen   = LOG_MAX_COLUMN_VAL - lOccupyLen;

    lTmpLen = LOG_SNPRINTF( pcDstStr + lOccupyLen, (unsigned int)lSpareLen,
                           ", Line: %u, Tick: %u, ", ulLineNum, LOG_GetTick());

    lOccupyLen += lTmpLen;
    lSpareLen   = LOG_MAX_COLUMN_VAL - lOccupyLen;

        /*=======================*/ /* �������������Ҫ�ĳ��� */
    lParamLen = ucParaCnt * LOG_MAX_PARA_LEN;
    lStrLen   = lSpareLen - lParamLen;
    LOG_AFFIRM(0 <= lStrLen)

        /*=======================*/ /* �����ַ�����Ϣ */
    lTmpLen = (long)strlen(pcOriStr);
    if (lTmpLen <= lStrLen)
    {
        memcpy(pcDstStr + lOccupyLen, pcOriStr, (unsigned int)lTmpLen);
        lOccupyLen += lTmpLen;
    }
    else
    {
        memcpy(pcDstStr + lOccupyLen, pcOriStr, (unsigned int)lStrLen);
        lOccupyLen += lStrLen;
    }

    if (0 == ucParaCnt)
    {
        if (LOG_MAX_COLUMN_VAL == lOccupyLen)
        {
            *(pcDstStr + (lOccupyLen - 1)) = '\0';
        }
        else
        {
            *(pcDstStr + lOccupyLen) = '\0';
            lOccupyLen = lOccupyLen + 1;
        }

        LOG_AFFIRM(LOG_MAX_COLUMN_VAL >= lOccupyLen)
        *pulLen = (unsigned long)lOccupyLen;
        return;
    }

    *(pcDstStr + lOccupyLen) = ':';
    lOccupyLen = lOccupyLen + 1;
    LOG_AFFIRM(LOG_MAX_COLUMN_VAL > lOccupyLen)

    lSpareLen = LOG_MAX_COLUMN_VAL - lOccupyLen;

        /*=======================*/ /* ������� */
    for (i = 0; i < ucParaCnt; i++)
    {
        lTmpLen = LOG_SNPRINTF( pcDstStr + lOccupyLen, (unsigned int)lSpareLen, " %d.", *(plPara + i));
        lOccupyLen += lTmpLen;
        LOG_AFFIRM(LOG_MAX_COLUMN_VAL >= lOccupyLen)

        lSpareLen  = LOG_MAX_COLUMN_VAL - lOccupyLen;
    }

    *pulLen = (unsigned long)(LOG_MAX_COLUMN_VAL - lSpareLen);
    return;
}


int Log_StrNParam(char             *cFileName,  unsigned long      ulLineNum,
             LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN   enSubModId,
             LOG_LEVEL_EN      enLevel,    char              *pcOriStr,
             unsigned char     ucParaCnt,  long              *plPara)
{
    unsigned long     ulLen;
    int               ret = VOS_ERR;

    /*lint -e813*/
    char              acLogStr[LOG_MAX_COLUMN_VAL_EX + 1];
    /*lint +e813*/

    if (LOG_TRUE != g_stLogEnt.ulPrintSwitch)
    {
        return ret;
    }

    if (enLevel > Log_GetPrintLevel(enModuleId))
    {
        return ret;
    }

#if(VOS_OS_VER == VOS_WIN32)

    switch ( enLevel )
    {
        case LOG_LEVEL_ERROR :
            vos_printf("\r\nERROR,");
            break;
        case LOG_LEVEL_WARNING :
            vos_printf("\r\nWARNING,");
            break;
        case LOG_LEVEL_NORMAL :
            vos_printf("\r\nNORMAL,");
            break;
        case LOG_LEVEL_INFO :
            vos_printf("\r\nINFO,");
            break;
        default:
            break;
    }
    vos_printf("%s, L: %d, T: %u, %s", (cFileName + Log_GetPathOffset(cFileName)), ulLineNum, LOG_GetTick(), pcOriStr);

    for (ulLen = 0; ulLen < ucParaCnt; ulLen++)
    {
        vos_printf(",%d ", plPara[ulLen]);
    }
#else
    *((VOS_UINT32*)acLogStr) = (VOS_UINT32)enModuleId;
    *(VOS_UINT32*)(acLogStr + sizeof(VOS_UINT32)) = (VOS_UINT32)enLevel;
    /*����LOG_MODULE_ID_LEN��������LOG���ݵ�ͷ�������Module ID
      ����ɵ�ƫ��*/
    Log_BuildStr(cFileName, ulLineNum, enLevel,  pcOriStr,
                 ucParaCnt, plPara,    acLogStr + LOG_MODULE_ID_LEN, &ulLen);
    ret = Log_BufInput(acLogStr, ulLen + LOG_MODULE_ID_LEN);
#endif

    return ret;
}
#endif

#ifdef __LOG_RELEASE__


void OM_LogId(LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN  enSubModId,
              LOG_LEVEL_EN      enLevel,    unsigned long     ulLogId)
{
    Log_IdNParam(enModuleId, enSubModId, enLevel, ulLogId, 0, LOG_NULL_PTR);
    return;
}


void OM_LogId1(LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN  enSubModId,
               LOG_LEVEL_EN      enLevel,    unsigned long     ulLogId,
               long              lPara1)
{
    long alParam[4];
    alParam[0] = lPara1;

    Log_IdNParam(enModuleId, enSubModId, enLevel, ulLogId, 1, alParam);
    return;
}


void OM_LogId2(LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN  enSubModId,
               LOG_LEVEL_EN      enLevel,    unsigned long     ulLogId,
               long              lPara1,     long              lPara2)
{
    long alParam[4];

    alParam[0] = lPara1;
    alParam[1] = lPara2;

    Log_IdNParam(enModuleId, enSubModId, enLevel, ulLogId, 2, alParam);

    return;
}


void OM_LogId3(LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN  enSubModId,
               LOG_LEVEL_EN      enLevel,    unsigned long     ulLogId,
               long              lPara1,     long              lPara2,
               long              lPara3)
{
    long alParam[4];

    alParam[0] = lPara1;
    alParam[1] = lPara2;
    alParam[2] = lPara3;

    Log_IdNParam(enModuleId, enSubModId, enLevel, ulLogId, 3, alParam);

    return;
}


void OM_LogId4(LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN  enSubModId,
               LOG_LEVEL_EN      enLevel,    unsigned long     ulLogId,
               long              lPara1,     long              lPara2,
               long              lPara3,     long              lPara4)
{
    long alParam[4];

    alParam[0] = lPara1;
    alParam[1] = lPara2;
    alParam[2] = lPara3;
    alParam[3] = lPara4;

    Log_IdNParam(enModuleId, enSubModId, enLevel, ulLogId, 4, alParam);

    return;
}


void Log_BuildId(unsigned long  ulLogId, unsigned char  ucParaCnt, long *plPara,
                    char          *pcDst,   unsigned long *pulLen)
{
    long             lTmpLen;
    long             lSpareLen;
    long             lOccupyLen;
    unsigned char    i;

    *pulLen = 0;

    if (ucParaCnt > LOG_MAX_PARA_CNT)
    {
        ucParaCnt = LOG_MAX_PARA_CNT;
    }

    lTmpLen    = LOG_SNPRINTF( pcDst, LOG_MAX_COLUMN_VAL, "%d, ", ulLogId);
    LOG_AFFIRM (0 <= lTmpLen)

    lOccupyLen = lTmpLen;
    LOG_AFFIRM(LOG_MAX_COLUMN_VAL >= lOccupyLen)
    lSpareLen  = LOG_MAX_COLUMN_VAL - lOccupyLen;

    lTmpLen    = LOG_SNPRINTF( pcDst + lOccupyLen, lSpareLen, "%u, ", LOG_GetTick());
    LOG_AFFIRM(0 <= lTmpLen)

    lOccupyLen += lTmpLen;
    LOG_AFFIRM(LOG_MAX_COLUMN_VAL >= lOccupyLen)
    lSpareLen  = LOG_MAX_COLUMN_VAL - lOccupyLen;

    for (i = 0; i < ucParaCnt; i ++)
    {
        lTmpLen = LOG_SNPRINTF( pcDst + lOccupyLen, lSpareLen, "%d, ", *plPara);
        LOG_AFFIRM(0 <= lTmpLen)

        lOccupyLen += lTmpLen;
        LOG_AFFIRM(LOG_MAX_COLUMN_VAL >= lOccupyLen)
        lSpareLen  = LOG_MAX_COLUMN_VAL - lOccupyLen;
        plPara++;
    }

    *pulLen = (unsigned long)(LOG_MAX_COLUMN_VAL - lSpareLen);

    return;
}


int Log_IdNParam(LOG_MODULE_ID_EN enModuleId, LOG_SUBMOD_ID_EN  enSubModId,
               LOG_LEVEL_EN     enLevel,    unsigned long     ulLogId,
               unsigned char    ucParaCnt,  long             *plPara)
{
    unsigned long     ulLen;
    int               ret = VOS_ERR;

/*lint -e813*/
    char              acLogStr[LOG_MAX_COLUMN_VAL_EX + 1];
/*lint +e813*/

    if (LOG_TRUE != g_stLogEnt.ulPrintSwitch)
    {
        return ret;
    }

    if (enLevel > Log_GetPrintLevel(enModuleId))
    {
        return ret;
    }

    *((VOS_UINT32*)acLogStr) = (VOS_UINT32)enModuleId;
    *(VOS_UINT32*)(acLogStr + sizeof(VOS_UINT32)) = (VOS_UINT32)enLevel;
    /*����LOG_MODULE_ID_LEN��������LOG���ݵ�ͷ�������Module ID
      ����ɵ�ƫ��*/
    Log_BuildId(ulLogId, ucParaCnt, plPara, acLogStr + LOG_MODULE_ID_LEN, &ulLen);
    ret = Log_BufInput(acLogStr, ulLen + LOG_MODULE_ID_LEN);

    return ret;
}
#endif


int Log_BufInput(char *pcLogStr, unsigned long ulLen)
{
    int     sRet;

#if (VOS_OS_VER == VOS_LINUX)
    if( in_interrupt() )
    {
        return VOS_ERR;
    }
#endif

    if (0 < ulLen)
    {
        if(VOS_OK != VOS_SmP(g_logBuffSem, 0))
        {
            return VOS_ERR;
        }

        if ((ulLen + sizeof(unsigned long)) > (unsigned long)OM_RingBufferFreeBytes(g_stLogEnt.rngOmRbufId))
        {
            VOS_SmV(g_logBuffSem);
            return VOS_ERR;
        }

        sRet = OM_RingBufferPut(g_stLogEnt.rngOmRbufId, (char*)(&ulLen), sizeof(unsigned long));
        if ((int)sizeof(unsigned long) == sRet)
        {
            sRet = OM_RingBufferPut(g_stLogEnt.rngOmRbufId, pcLogStr, (long)ulLen);
            VOS_SmV(g_logBuffSem);

            if (ulLen == (unsigned long)sRet)
            {
                VOS_SmV(g_stLogEnt.semOmPrint);
                return VOS_OK ;
            }
            else
            {
                vos_printf("\nLog, Error, rngBufPut Data not OK");
            }
        }
        else
        {
            VOS_SmV(g_logBuffSem);
            vos_printf("\nLog, Error, rngBufPut DataLen not OK");
        }
    }
    return VOS_ERR;
}


void Log_SelfTask(unsigned long ulPara1, unsigned long ulPara2,
                  unsigned long ulPara3, unsigned long ulPara4)
{
    int             sRet;
    unsigned long   ulLen;
/*lint -e813*/
    char            acTmpStr[LOG_MAX_COLUMN_VAL_EX + 1];
/*lint +e813*/
    Log_Init();

    for(;;)
    {
        if(VOS_OK != VOS_SmP(g_stLogEnt.semOmPrint, 0))
        {
            continue;
        }

        if (LOG_NULL_PTR == g_stLogEnt.rngOmRbufId)
        {
            continue;
        }

        if (LOG_TRUE == OM_RingBufferIsEmpty(g_stLogEnt.rngOmRbufId))
        {
            continue;
        }

        sRet = OM_RingBufferGet(g_stLogEnt.rngOmRbufId, (char*)(&ulLen), sizeof(unsigned long));
        if (sizeof(unsigned long) != (unsigned long)sRet)
        {
            continue;
        }

        if(LOG_MAX_COLUMN_VAL_EX < ulLen)
        {
            OM_RingBufferFlush(g_stLogEnt.rngOmRbufId);

            continue;
        }

        sRet = OM_RingBufferGet(g_stLogEnt.rngOmRbufId, acTmpStr, (long)ulLen);
        if (ulLen == (unsigned long)sRet)
        {
            Log_Output(g_stLogEnt.ulLogOutput, acTmpStr, ulLen);
        }
    }
}

void Log_Output(unsigned long ulOutputType, char *pcStr, unsigned long ulLen)
{
    if (ulLen < LOG_MAX_COLUMN_VAL_EX)
    {
        pcStr[ulLen] = '\0';
    }
    else
    {
        pcStr[LOG_MAX_COLUMN_VAL_EX] = '\0';
    }

    switch (ulOutputType)
    {
        case OM_OUTPUT_SHELL:
            vos_printf("%s\n", pcStr + LOG_MODULE_ID_LEN);/* ���ַ������������ */
            break;

        case OM_OUTPUT_SDT:
            OM_AcpuSendLog((unsigned char*)pcStr, ulLen);
            break;

        default:
            break;
    }

    return;
}


VOS_UINT32 Log_SetOutputType(OM_OUTPUT_PORT_ENUM_UINT32 enOutputType)
{
    /*�����Ϸ��Լ��*/
    if (OM_OUTPUT_BUTT <= enOutputType)
    {
        return VOS_ERR;
    }

/*���ڹ��߲಻֧���ַ��������ʽ����Ҫ����ʧ��*/
#ifdef __LOG_BBIT__
    if (OM_OUTPUT_SDT == enOutputType)
    {
        return VOS_ERR;
    }
#endif

    g_stLogEnt.ulLogOutput = enOutputType;

    return VOS_OK;
}


VOS_UINT32 Log_CheckPara(LOG_ID_LEVEL_STRU *pstLogIdLevel, VOS_UINT32 ulLength)
{
    VOS_UINT32 ulModuleNum;

    ulModuleNum = pstLogIdLevel->ulModuleNum;

    /*�жϸ����ͳ��ȼ�Ĺ�ϵ�Ƿ���ȷ*/
    if (ulLength != (sizeof(ulModuleNum)
             + (ulModuleNum*sizeof(LOG_MODULE_LEVEL_STRU))))
    {
        vos_printf("Log_CheckPara: Received length isn't correct.\n");
        return VOS_ERR;
    }

    return VOS_OK;
}

void Log_SetModuleIdLev(LOG_MODULE_ID_EN enModuleId, LOG_SUBMOD_ID_EN enSubModId,
                                LOG_LEVEL_EN enLevel)
{
	/*lint -e662 -e661*/
    /*����ӡ���𲻺Ϸ�ʱ������ʧ��*/
    if (LOG_LEVEL_BUTT <= enLevel)
    {
        vos_printf("Log_SetModuleIdLev: ModuleId is %d, Level is %d.\r\n", enModuleId, enLevel);
        return;
    }

    if (LOG_MIN_MODULE_ID_ACPU_DRV <= enModuleId && LOG_MAX_MODULE_ID_ACPU_DRV >= enModuleId)
    {
        g_aulLogPrintLevDrvTable[enModuleId - LOG_MIN_MODULE_ID_ACPU_DRV] = enLevel;
    }
    else if ((VOS_PID_DOPRAEND <= enModuleId) && (VOS_PID_BUTT > enModuleId))
    {
        g_aulLogPrintLevPsTable[enModuleId - VOS_PID_DOPRAEND] = enLevel;
    }
    else
    {
        vos_printf("Log_SetModuleIdLev: enModuleId isn't correct. ModuleId is %d.\r\n", enModuleId);
    }
	/*lint +e662 +e661*/
}


VOS_UINT32 Log_SetPrintLev(LOG_ID_LEVEL_STRU *pstLogIdLevel, VOS_UINT32 ulLength)
{
    VOS_UINT32         ulIndex;
    VOS_UINT32         ulModuleId;
    VOS_UINT32         ulModuleNum;
    LOG_LEVEL_EN       enPrintLev;

    /*�������ĺϷ���*/
    if (VOS_ERR == Log_CheckPara(pstLogIdLevel, ulLength))
    {
        return VOS_ERR;
    }

    /*����ϴ�����*/
    VOS_MemSet(g_aulLogPrintLevPsTable, 0, LOG_PS_MODULE_MAX_NUM*sizeof(LOG_LEVEL_EN));
    VOS_MemSet(g_aulLogPrintLevDrvTable, 0, LOG_DRV_MODULE_MAX_NUM*sizeof(LOG_LEVEL_EN));

    ulModuleNum = pstLogIdLevel->ulModuleNum;

    /*��ÿ��ģ��Ĵ�ӡ�������뵽ȫ�ֹ��˱���*/
    for (ulIndex = 0; ulIndex < ulModuleNum; ulIndex++)
    {
        ulModuleId = pstLogIdLevel->astModuleLev[ulIndex].ulModuleId;
        enPrintLev = pstLogIdLevel->astModuleLev[ulIndex].enPrintLev;

        Log_SetModuleIdLev((LOG_MODULE_ID_EN)ulModuleId, (LOG_SUBMOD_ID_EN)0, enPrintLev);
    }

    return VOS_OK;
}


VOS_VOID Log_AcpuOmMsgProc(OM_REQ_PACKET_STRU *pRspPacket, OM_RSP_FUNC *pRspFuncPtr)
{
    APP_OM_MSG_EX_STRU             *pstAppToOmMsg;
    VOS_UINT32                      ulOutputType;

    pstAppToOmMsg = (APP_OM_MSG_EX_STRU*)pRspPacket;
    /*������־�����ʽ��ԭ����Ϣ*/
    if (APP_OM_SET_PRINT_OUTPUT_REQ == pstAppToOmMsg->usPrimId)
    {
        ulOutputType = *((VOS_UINT32*)pstAppToOmMsg->aucPara);
        Log_SetOutputType((OM_OUTPUT_PORT_ENUM_UINT32)ulOutputType);
    }
    /*������־��ӡ�����ԭ����Ϣ*/
    else if (APP_OM_SET_PRINT_LEV_REQ == pstAppToOmMsg->usPrimId)
    {
        Log_SetPrintLev((LOG_ID_LEVEL_STRU*)(pstAppToOmMsg->aucPara),
        pstAppToOmMsg->usLength - (OM_APP_MSG_EX_LEN - VOS_OM_HEADER_LEN));
    }
    /*ɾ���ļ�ϵͳ�е���־�ļ�*/
    else if (APP_OM_EXPORT_LOG_END_CNF == pstAppToOmMsg->usPrimId)
    {
        return;
    }
    else
    {
        vos_printf("Undefined PrimId : %d", pstAppToOmMsg->usPrimId);
        return;
    }

    return;
}


VOS_VOID LogAcpuShow(VOS_VOID)
{
    VOS_UINT32      ulBufferLen;

    if (LOG_TRUE == g_stLogEnt.ulPrintSwitch)
    {
        vos_printf("The Current Log State:      ON\n");
    }
    else
    {
        vos_printf("The Current Log State:      OFF\n");
    }

#ifdef __LOG_BBIT__
    vos_printf("The Data Type:              STRING\n");
#else
    vos_printf("The Data Type:              DOT\n");
#endif

    if (OM_OUTPUT_SHELL == g_stLogEnt.ulLogOutput)
    {
        vos_printf("The Output Type:            COM\n");
    }
    else if (OM_OUTPUT_FS == g_stLogEnt.ulLogOutput)
    {
        vos_printf("The Output Type:            File System\n");
    }
    else if (OM_OUTPUT_SDT == g_stLogEnt.ulLogOutput)
    {
        vos_printf("The Output Type:            SDT\n");
    }
    else
    {
        /*Make pclint happy*/
    }

    if (VOS_TRUE == g_astLogFileInfo[LOG_FROM_PS_LOG].bIsWritten)
    {
        vos_printf("The Log File:               OK\n");
    }
    else
    {
        vos_printf("The Log File:               ERROR\n");
    }

    ulBufferLen = (VOS_UINT32)OM_RingBufferFreeBytes(g_stLogEnt.rngOmRbufId);
    vos_printf("Remainder Len of Log buffer:%ld\n", ulBufferLen);
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


