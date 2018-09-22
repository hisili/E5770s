


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
//#include  "vos.h"
#include  "diag_debug.h"

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
DIAG_DEBUG_INFO_TBL_STRU g_ast_diag_debug_info_table[EN_DIAG_DEBUG_INFO_MAX] = {{0}};

DIAG_DEBUG_INFO_TBL_STRU* diag_DebugGetInfo(VOS_VOID)
{
   return g_ast_diag_debug_info_table;
}


VOS_CHAR    DecoderDestReadCB_LogPath[sizeof(DECODER_DEST_READCB_LOGPATH)] = DECODER_DEST_READCB_LOGPATH;
VOS_CHAR    UsbCtrlRdCB_LogPath[sizeof(USB_CTRL_RDCB_LOGPATH)] = USB_CTRL_RDCB_LOGPATH;
/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_VOID diag_Debug(DIAG_DEBUG_MSG_ID_ENUM ulType,
                     VOS_UINT32 ulRserved1, VOS_UINT32 ulRserved2, VOS_UINT32 ulRserved3)
{
    g_ast_diag_debug_info_table[ulType].ulCalledNum += 1;
    g_ast_diag_debug_info_table[ulType].ulRserved1 = ulRserved1;
    g_ast_diag_debug_info_table[ulType].ulRserved2 = ulRserved2;
    g_ast_diag_debug_info_table[ulType].ulRserved3 = ulRserved3;
    g_ast_diag_debug_info_table[ulType].ulRtcTime  = VOS_GetTick();


}

#if (VOS_OS_VER == VOS_LINUX)

VOS_VOID Debug_DiagFw(VOS_VOID)
{
    DIAG_DEBUG_INFO_TBL_STRU* pstTable;
    pstTable = diag_DebugGetInfo();

    vos_printf("*------------DiagFw INIT-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_FW_INIT].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_FW_INIT].ulRserved1,
            pstTable[EN_DIAG_DEBUG_FW_INIT].ulRserved2);
    vos_printf("*------------DiagFw INIT ERROR-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n fail branch  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_FW_INIT_ERROR].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_FW_INIT_ERROR].ulRserved1,
            pstTable[EN_DIAG_DEBUG_FW_INIT_ERROR].ulRserved2,
            pstTable[EN_DIAG_DEBUG_FW_INIT_ERROR].ulRserved3);

    vos_printf("*------------DiagFw DECODE CMD-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY].ulRserved1,
            pstTable[EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY].ulRserved2);
    vos_printf("*------------DiagFw DECODE CMD ERROR-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n fail branch  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY_ERROR].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY_ERROR].ulRserved1,
            pstTable[EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY_ERROR].ulRserved2,
            pstTable[EN_DIAG_DEBUG_FW_DECODE_CMD_ENTRY_ERROR].ulRserved3);

    vos_printf("*------------DiagFw TIME_OUT-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_FW_TIME_OUT_ENTRY].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_FW_TIME_OUT_ENTRY].ulRserved1,
            pstTable[EN_DIAG_DEBUG_FW_TIME_OUT_ENTRY].ulRserved2);
    vos_printf("*------------DiagFw TIME_OUT ERROR-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n fail branch  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_FW_TIME_OUT_ENTRY_ERROR].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_FW_TIME_OUT_ENTRY_ERROR].ulRserved1,
            pstTable[EN_DIAG_DEBUG_FW_TIME_OUT_ENTRY_ERROR].ulRserved2,
            pstTable[EN_DIAG_DEBUG_FW_TIME_OUT_ENTRY_ERROR].ulRserved3);

    vos_printf("*------------DiagFw APP_CNF-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_FW_APP_CNF_ENTRY].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_FW_APP_CNF_ENTRY].ulRserved1,
            pstTable[EN_DIAG_DEBUG_FW_APP_CNF_ENTRY].ulRserved2);
    vos_printf("*------------DiagFw APP_CNF ERROR-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n fail branch  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_FW_APP_CNF_ENTRY_ERROR].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_FW_APP_CNF_ENTRY_ERROR].ulRserved1,
            pstTable[EN_DIAG_DEBUG_FW_APP_CNF_ENTRY_ERROR].ulRserved2,
            pstTable[EN_DIAG_DEBUG_FW_APP_CNF_ENTRY_ERROR].ulRserved3);

    vos_printf("*------------DiagFw AGENT_CNF-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_FW_AGENT_CNF_ENTRY].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_FW_AGENT_CNF_ENTRY].ulRserved1,
            pstTable[EN_DIAG_DEBUG_FW_AGENT_CNF_ENTRY].ulRserved2);
    vos_printf("*------------DiagFw AGENT_CNF ERROR-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n fail branch  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_FW_AGENT_CNF_ENTRY_ERROR].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_FW_AGENT_CNF_ENTRY_ERROR].ulRserved1,
            pstTable[EN_DIAG_DEBUG_FW_AGENT_CNF_ENTRY_ERROR].ulRserved2,
            pstTable[EN_DIAG_DEBUG_FW_AGENT_CNF_ENTRY_ERROR].ulRserved3);

}

#endif
VOS_VOID Debug_DiagApi(VOS_UINT32 ulApiType)
{
    DIAG_DEBUG_INFO_TBL_STRU* pstTable;
    pstTable = diag_DebugGetInfo();

    /* �տ������*/
    if(DIAG_DEBUG_API == ulApiType || DIAG_DEBUG_API_AIR == ulApiType)
    {
        vos_printf("*------------DIAG ReportAirMessageLog is called?----------------\n");
        vos_printf("DIAG ReportAirMessageLog Call Times    : %d \n",pstTable[EN_SDM_DIAG_ReportAirMessageLog].ulCalledNum);
        vos_printf("DIAG ReportAirMessageLog para ID       : %#x \n", pstTable[EN_SDM_DIAG_ReportAirMessageLog].ulRserved1);
        vos_printf("MEAN called at function head           : %#x \n", pstTable[EN_SDM_DIAG_ReportAirMessageLog].ulRserved2);
        vos_printf("No Use                                 : %d \n\n", pstTable[EN_SDM_DIAG_ReportAirMessageLog].ulRserved3);
        vos_printf("DIAG ReportAirMessageLog RTC Time      : %d \n\n", pstTable[EN_SDM_DIAG_ReportAirMessageLog].ulRtcTime);

        vos_printf("*------------DIAG ReportAirMessageLog ʧ�ܴ���----------------\n");
        vos_printf("ReportAirMessageLog Call failure Times : %d \n",pstTable[EN_SDM_DIAG_ReportAirMessageLog_ERR].ulCalledNum);
        vos_printf("ReportAirMessageLog PRIOR call         : %#x \n", pstTable[EN_SDM_DIAG_ReportAirMessageLog_ERR].ulRserved1);
        vos_printf("ReportAirMessageLog para ID            : %#x \n", pstTable[EN_SDM_DIAG_ReportAirMessageLog_ERR].ulRserved2);
        vos_printf("Failure Position 1 mean first branch   : %d \n\n", pstTable[EN_SDM_DIAG_ReportAirMessageLog_ERR].ulRserved3);
        vos_printf("ReportAirMessageLog RTC Time           : %d \n\n", pstTable[EN_SDM_DIAG_ReportAirMessageLog_ERR].ulRtcTime);
    }
    /*voLTE�����*/
    if(DIAG_DEBUG_API == ulApiType || DIAG_DEBUG_VOLTE == ulApiType)
    {
        vos_printf("*------------DIAG ReportAirMessageLog is called?----------------\n");
        vos_printf("DIAG ReportVolTEMessageLog Call Times    : %d \n",pstTable[EN_SDM_DIAG_ReportVoLTELog_ERR].ulCalledNum);
        vos_printf("DIAG ReportVolTEMessageLog para ID       : %#x \n", pstTable[EN_SDM_DIAG_ReportVoLTELog_ERR].ulRserved1);
        vos_printf("MEAN called at function head           : %#x \n", pstTable[EN_SDM_DIAG_ReportVoLTELog_ERR].ulRserved2);
        vos_printf("No Use                                 : %d \n\n", pstTable[EN_SDM_DIAG_ReportVoLTELog_ERR].ulRserved3);
        vos_printf("DIAG ReportAirMessageLog RTC Time      : %d \n\n", pstTable[EN_SDM_DIAG_ReportVoLTELog_ERR].ulRtcTime);

        vos_printf("*------------DIAG ReportVolTEMessageLog ʧ�ܴ���----------------\n");
        vos_printf("ReportVolTEMessageLog Call failure Times : %d \n",pstTable[EN_SDM_DIAG_ReportVoLTELog_ERR].ulCalledNum);
        vos_printf("ReportVolTEMessageLog PRIOR call         : %#x \n", pstTable[EN_SDM_DIAG_ReportVoLTELog_ERR].ulRserved1);
        vos_printf("ReportVolTEMessageLog para ID            : %#x \n", pstTable[EN_SDM_DIAG_ReportVoLTELog_ERR].ulRserved2);
        vos_printf("Failure Position 1 mean first branch   : %d \n\n", pstTable[EN_SDM_DIAG_ReportVoLTELog_ERR].ulRserved3);
        vos_printf("ReportVolTEMessageLog RTC Time           : %d \n\n", pstTable[EN_SDM_DIAG_ReportVoLTELog_ERR].ulRtcTime);
    }

    /* ��������*/
    if(DIAG_DEBUG_API == ulApiType || DIAG_DEBUG_API_LAYER == ulApiType)
    {
        vos_printf("*------------DIAG ReportLayerMessageLog is called?----------------\n");
        vos_printf("DIAG ReportLayerMessageLog Call Times  : %d \n",pstTable[EN_SDM_DIAG_ReportLayerMessageLog].ulCalledNum);
        vos_printf("DIAG ReportLayerMessageLog para ID     : %#x \n", pstTable[EN_SDM_DIAG_ReportLayerMessageLog].ulRserved1);
        vos_printf("MEAN called at function head           : %#x \n", pstTable[EN_SDM_DIAG_ReportLayerMessageLog].ulRserved2);
        vos_printf("No Use                                 : %d \n\n", pstTable[EN_SDM_DIAG_ReportLayerMessageLog].ulRserved3);
        vos_printf("DIAG ReportLayerMessageLog RTC Time    : %d \n\n", pstTable[EN_SDM_DIAG_ReportLayerMessageLog].ulRtcTime);

        vos_printf("*------------DIAG ReportLayerMessageLog ʧ�ܴ���----------------\n");
        vos_printf("ReportLayerMessageLog Call failure Times: %d \n",pstTable[EN_SDM_DIAG_ReportLayerMessageLog_ERR].ulCalledNum);
        vos_printf("ReportLayerMessageLog PRIOR call       : %#x \n", pstTable[EN_SDM_DIAG_ReportLayerMessageLog_ERR].ulRserved1);
        vos_printf("ReportLayerMessageLog para ID          : %#x \n", pstTable[EN_SDM_DIAG_ReportLayerMessageLog_ERR].ulRserved2);
        vos_printf("Failure Position 1 mean first branch   : %d \n\n", pstTable[EN_SDM_DIAG_ReportLayerMessageLog_ERR].ulRserved3);
        vos_printf("ReportLayerMessageLog RTC Time         : %d \n\n", pstTable[EN_SDM_DIAG_ReportLayerMessageLog_ERR].ulRtcTime);
    }

    /* �û��������*/
    if(DIAG_DEBUG_API == ulApiType || DIAG_DEBUG_API_USERPLANE == ulApiType)
    {
        vos_printf("*------------DIAG ReportUserPlaneMessageLog is called?----------------\n");
        vos_printf("DIAG ReportUserPlaneMessageLog Call Times: %d \n",pstTable[EN_SDM_DIAG_ReportUserPlaneMessageLog].ulCalledNum);
        vos_printf("DIAG ReportUserPlaneMessageLog para ID : %#x \n", pstTable[EN_SDM_DIAG_ReportUserPlaneMessageLog].ulRserved1);
        vos_printf("MEAN called at function head           : %#x \n", pstTable[EN_SDM_DIAG_ReportUserPlaneMessageLog].ulRserved2);
        vos_printf("No Use                                 : %d \n\n", pstTable[EN_SDM_DIAG_ReportUserPlaneMessageLog].ulRserved3);
        vos_printf("DIAG ReportUserPlaneMessageLog RTC Time: %d \n\n", pstTable[EN_SDM_DIAG_ReportUserPlaneMessageLog].ulRtcTime);

        vos_printf("*------------DIAG ReportUserPlaneMessageLog ʧ�ܴ���----------------\n");
        vos_printf("ReportUserPlaneMessageLog Call failure Times: %d \n",pstTable[EN_SDM_DIAG_ReportUserPlaneMessageLog_ERR].ulCalledNum);
        vos_printf("ReportUserPlaneMessageLog PRIOR call   : %#x \n", pstTable[EN_SDM_DIAG_ReportUserPlaneMessageLog_ERR].ulRserved1);
        vos_printf("ReportUserPlaneMessageLog para ID      : %#x \n", pstTable[EN_SDM_DIAG_ReportUserPlaneMessageLog_ERR].ulRserved2);
        vos_printf("Failure Position 1 mean first branch   : %d \n\n", pstTable[EN_SDM_DIAG_ReportUserPlaneMessageLog_ERR].ulRserved3);
        vos_printf("ReportUserPlaneMessageLog RTC Time     : %d \n\n", pstTable[EN_SDM_DIAG_ReportUserPlaneMessageLog_ERR].ulRtcTime);
    }

    /* �¼������*/
    if(DIAG_DEBUG_API == ulApiType || DIAG_DEBUG_API_EVENT == ulApiType)
    {
        vos_printf("*------------DIAG ReportEventLog is called?----------------\n");
        vos_printf("DIAG ReportEventLog Call Times         : %d \n",pstTable[EN_SDM_DIAG_ReportEventLog].ulCalledNum);
        vos_printf("DIAG ReportEventLog para ID            : %#x \n", pstTable[EN_SDM_DIAG_ReportEventLog].ulRserved1);
        vos_printf("MEAN called at function head           : %#x \n", pstTable[EN_SDM_DIAG_ReportEventLog].ulRserved2);
        vos_printf("No Use                                 : %d \n\n", pstTable[EN_SDM_DIAG_ReportEventLog].ulRserved3);
        vos_printf("DIAG ReportEventLog RTC Time           : %d \n\n", pstTable[EN_SDM_DIAG_ReportEventLog].ulRtcTime);

        vos_printf("*------------DIAG ReportEventLog ʧ�ܴ���----------------\n");
        vos_printf("ReportEventLog Call failure Times      : %d \n",pstTable[EN_SDM_DIAG_ReportEventLog_ERR].ulCalledNum);
        vos_printf("ReportEventLog PRIOR call              : %#x \n", pstTable[EN_SDM_DIAG_ReportEventLog_ERR].ulRserved1);
        vos_printf("ReportEventLog para ID                 : %#x \n", pstTable[EN_SDM_DIAG_ReportEventLog_ERR].ulRserved2);
        vos_printf("Failure Position 1 mean first branch   : %d \n\n", pstTable[EN_SDM_DIAG_ReportEventLog_ERR].ulRserved3);
        vos_printf("ReportEventLog RTC Time                : %d \n\n", pstTable[EN_SDM_DIAG_ReportEventLog_ERR].ulRtcTime);
    }

    /* ���������*/
    if(DIAG_DEBUG_API == ulApiType || DIAG_DEBUG_API_REPORT_INFO == ulApiType)
    {
        vos_printf("*------------DIAG_ReportStatLog is called?----------------\n");
        vos_printf("DIAG_ReportStatLog Call Times          : %d \n",pstTable[EN_SDM_DIAG_ReportStatLog].ulCalledNum);
        vos_printf("DIAG_ReportStatLog para ID             : %#x \n", pstTable[EN_SDM_DIAG_ReportStatLog].ulRserved1);
        vos_printf("MEAN called at function head           : %#x \n", pstTable[EN_SDM_DIAG_ReportStatLog].ulRserved2);
        vos_printf("No Use                                 : %d \n\n", pstTable[EN_SDM_DIAG_ReportStatLog].ulRserved3);
        vos_printf("DIAG_ReportStatLog RTC Time            : %d \n\n", pstTable[EN_SDM_DIAG_ReportStatLog].ulRtcTime);

        vos_printf("*------------DIAG_ReportStatLog ʧ�ܴ���----------------\n");
        vos_printf("DIAG_ReportStatLog Call failure Times  : %d \n", pstTable[EN_SDM_DIAG_ReportStatLog_ERR].ulCalledNum);
        vos_printf("DIAG_ReportStatLog PRIOR call          : %#x \n", pstTable[EN_SDM_DIAG_ReportStatLog_ERR].ulRserved1);
        vos_printf("DIAG_ReportStatLog para ID             : %#x \n", pstTable[EN_SDM_DIAG_ReportStatLog_ERR].ulRserved2);
        vos_printf("Failure Position 1 mean first branch   : %d \n\n", pstTable[EN_SDM_DIAG_ReportStatLog_ERR].ulRserved3);
        vos_printf("DIAG_ReportStatLog RTC Time            : %d \n\n", pstTable[EN_SDM_DIAG_ReportStatLog_ERR].ulRtcTime);
    }

    /* ��ӡ�����*/
    if(DIAG_DEBUG_API == ulApiType || DIAG_DEBUG_API_PRINTF == ulApiType)
    {
        vos_printf("*------------DIAG PRINTFV is called?----------------\n");
        vos_printf("DIAG PRINTFV Call Times     : %d \n",pstTable[EN_SDM_DIAG_PRINTFV].ulCalledNum);
        vos_printf("DIAG PRINTFV para ID        : %#x \n", pstTable[EN_SDM_DIAG_PRINTFV].ulRserved1);
        vos_printf("MEAN called at function head: %#x \n", pstTable[EN_SDM_DIAG_PRINTFV].ulRserved2);
        vos_printf("No Use                      : %d \n\n", pstTable[EN_SDM_DIAG_PRINTFV].ulRserved3);
        vos_printf("DIAG PRINTFV RTC Time       : %d \n\n", pstTable[EN_SDM_DIAG_PRINTFV].ulRtcTime);

        vos_printf("*------------DIAG PRINTF V ʧ�ܴ���----------------\n");
        vos_printf("PRINTFV Call failure Times  : %d \n",pstTable[EN_SDM_DIAG_PRINTFV_ERR].ulCalledNum);
        vos_printf("PRINTFV PRIOR call          : %#x \n", pstTable[EN_SDM_DIAG_PRINTFV_ERR].ulRserved1);
        vos_printf("PRINTFV para ID             : %#x \n", pstTable[EN_SDM_DIAG_PRINTFV_ERR].ulRserved2);
        vos_printf("Failure Position 1 mean first branch: %d \n\n", pstTable[EN_SDM_DIAG_PRINTFV_ERR].ulRserved3);
        vos_printf("PRINTFV RTC Time            : %d \n\n", pstTable[EN_SDM_DIAG_PRINTFV_ERR].ulRtcTime);

        vos_printf("*------------DIAG DOT PRINT is called?----------------\n");
        vos_printf("DOT PRINT Call Times        : %d \n",pstTable[EN_SDM_DIAG_DOT].ulCalledNum);
        vos_printf("DOT PRINT para ID           : %#x \n", pstTable[EN_SDM_DIAG_DOT].ulRserved1);
        vos_printf("MEAN called at function head: %#x \n", pstTable[EN_SDM_DIAG_DOT].ulRserved2);
        vos_printf("No Use                      : %d \n\n", pstTable[EN_SDM_DIAG_DOT].ulRserved3);
        vos_printf("DOT PRINT RTC Time          : %d \n\n", pstTable[EN_SDM_DIAG_DOT].ulRtcTime);

        vos_printf("*------------DIAG DOT PRINT ʧ�ܴ���----------------\n");
        vos_printf("DOT PRINT Call failure Times  : %d \n",pstTable[EN_SDM_DIAG_DOT_ERR].ulCalledNum);
        vos_printf("DOT PRINT ERROR CODE          : %#x \n", pstTable[EN_SDM_DIAG_DOT_ERR].ulRserved1);
        vos_printf("DOT PRINT para ID             : %#x \n", pstTable[EN_SDM_DIAG_DOT_ERR].ulRserved2);
        vos_printf("Failure  branch               : %d \n\n", pstTable[EN_SDM_DIAG_DOT_ERR].ulRserved3);
        vos_printf("DOT PRINT RTC Time            : %d \n\n", pstTable[EN_SDM_DIAG_DOT_ERR].ulRtcTime);
    }

    if(DIAG_DEBUG_API == ulApiType || DIAG_DEBUG_API_PRINTF == ulApiType)
    {
    }
}
VOS_VOID Debug_DiagSocp(VOS_VOID);
VOS_VOID Debug_DiagSocp(VOS_VOID)
{
    DIAG_DEBUG_INFO_TBL_STRU* pstTable;
    pstTable = diag_DebugGetInfo();


    vos_printf("*------------vcom���͸�SOCP����Դ����:-------------------\n");
    vos_printf("Call Counts   : %d \nulChanID   : %d \nulDataSize   : %d\n\n",
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_START].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_START].ulRserved1,
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_START].ulRserved2);

	vos_printf("*------------vcom���͸�SOCP����Դʧ����:-------------------\n");
    vos_printf("Fail Counts   : %d \nulRserved1   : %d \nulRserved2   : %d \nbranch    : %d\n\n",
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_START_ERROR].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_START_ERROR].ulRserved1,
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_START_ERROR].ulRserved2,
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_START_ERROR].ulRserved3);

    vos_printf("*------------SOCP����ص�����:-------------------\n");
    vos_printf("Call Counts   : %d \nulChanID   : %d \nulDataSize   : %d\n\n",
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_RCVE].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_RCVE].ulRserved1,
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_RCVE].ulRserved2);

    vos_printf("*------------SOCP����ص�ʧ��:-------------------\n");
    vos_printf("Fail Counts   : %d \nulRserved1   : %d \nulRserved2   : %d \nbranch    : %d\n\n",
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR].ulRserved1,
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR].ulRserved2,
        pstTable[EN_DIAG_DEBUG_DECODE_PACKET_RCVE_ERROR].ulRserved3);

    vos_printf("*------------��ȡSOCP ����ԴBUF����:-------------------\n");
    vos_printf("Call Counts   : %d \nulChanID   : %d \nulDataSize   : %d\n\n",
        pstTable[EN_DIAG_DEBUG_GET_SRC_BUF_START].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_GET_SRC_BUF_START].ulRserved1,
        pstTable[EN_DIAG_DEBUG_GET_SRC_BUF_START].ulRserved2);

    vos_printf("*------------��ȡSOCP ����ԴBUFʧ��:-------------------\n");
    vos_printf("Fail Counts   : %d \nulRserved1   : %d \nulRserved2   : %d \nbranch    : %d\n\n",
        pstTable[EN_DIAG_DEBUG_GET_SRC_BUF_START_ERROR].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_GET_SRC_BUF_START_ERROR].ulRserved1,
        pstTable[EN_DIAG_DEBUG_GET_SRC_BUF_START_ERROR].ulRserved2,
        pstTable[EN_DIAG_DEBUG_GET_SRC_BUF_START_ERROR].ulRserved3);

    vos_printf("*------------д��SOCP�������:-------------------\n");
    vos_printf("Call Counts   : %d \nulChanID   : %d \nulDataSize   : %d\n\n",
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_START].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_START].ulRserved1,
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_START].ulRserved2);

    vos_printf("*------------д��SOCP����ʧ��:-------------------\n");
    vos_printf("Fail Counts   : %d \nulRserved1   : %d \nulRserved2   : %d \nbranch    : %d\n\n",
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_START_ERROR].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_START_ERROR].ulRserved1,
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_START_ERROR].ulRserved2,
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_START_ERROR].ulRserved3);

    vos_printf("*------------����Ŀ�Ľ�������-------------------\n");
    vos_printf("Call Counts   : %d \nulChanID   : %d \nulDataSize   : %d\n\n",
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_RCVE].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_RCVE].ulRserved1,
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_RCVE].ulRserved2);

    vos_printf("*------------����Ŀ��д��USBʧ��-------------------\n");
    vos_printf("Fail Counts   : %d \nulRserved1   : %d \nulRserved2   : %d \nbranch    : %d\n\n",
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_RCVE_ERROR].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_RCVE_ERROR].ulRserved1,
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_RCVE_ERROR].ulRserved2,
        pstTable[EN_DIAG_DEBUG_CODE_PACKET_RCVE_ERROR].ulRserved3);
}


VOS_VOID Debug_DiagCfg(VOS_VOID);
VOS_VOID Debug_DiagCfg(VOS_VOID)
{
    DIAG_DEBUG_INFO_TBL_STRU* pstTable;
    pstTable = diag_DebugGetInfo();

    vos_printf("*------------DIAG CONN CFG-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_CONN_CFG].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_CONN_CFG].ulRserved1,
            pstTable[EN_DIAG_DEBUG_CONN_CFG].ulRserved2);

    vos_printf("*------------DIAG DISCONN CFG-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_DIS_CONN_CFG].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_DIS_CONN_CFG].ulRserved1,
            pstTable[EN_DIAG_DEBUG_DIS_CONN_CFG].ulRserved2);

    vos_printf("*------------DIAG AIR CFG-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_AIR_CFG].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_AIR_CFG].ulRserved1,
            pstTable[EN_DIAG_DEBUG_AIR_CFG].ulRserved2);

    vos_printf("*------------DIAG LAYER CFG-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_LAYER_CFG].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_LAYER_CFG].ulRserved1,
            pstTable[EN_DIAG_DEBUG_LAYER_CFG].ulRserved2);

    vos_printf("*------------DIAG PRINT CFG-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_PRINT_CFG].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_PRINT_CFG].ulRserved1,
            pstTable[EN_DIAG_DEBUG_PRINT_CFG].ulRserved2);

   vos_printf("*------------DIAG MSG CFG-------------------\n");
   vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_MSG].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_MSG].ulRserved1,
            pstTable[EN_DIAG_DEBUG_MSG].ulRserved2);
  vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_MSG_ERR].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_MSG_ERR].ulRserved1,
            pstTable[EN_DIAG_DEBUG_MSG_ERR].ulRserved2);

   vos_printf("*------------DIAG EVENT CFG-------------------\n");
   vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_EVENT_CFG].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_EVENT_CFG].ulRserved1,
            pstTable[EN_DIAG_DEBUG_EVENT_CFG].ulRserved2);

   vos_printf("*------------DIAG USEPLANE CFG-------------------\n");
   vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_USEPLANE_CFG].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_USEPLANE_CFG].ulRserved1,
            pstTable[EN_DIAG_DEBUG_USEPLANE_CFG].ulRserved2);
}

VOS_VOID Debug_DiagCmd(VOS_VOID);
VOS_VOID Debug_DiagCmd(VOS_VOID)
{
    DIAG_DEBUG_INFO_TBL_STRU* pstTable;
    pstTable = diag_DebugGetInfo();

	vos_printf("*------------DiagFw LIST-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : 0x%x \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_FW_LIST_CMD].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_FW_LIST_CMD].ulRserved1,
            pstTable[EN_DIAG_DEBUG_FW_LIST_CMD].ulRserved2);

    vos_printf("*------------DIAG AppAgent RECEIVE CMD-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : 0x%x \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_APP_AGENT_DISPATCH_CMD].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_APP_AGENT_DISPATCH_CMD].ulRserved1,
            pstTable[EN_DIAG_DEBUG_APP_AGENT_DISPATCH_CMD].ulRserved2);

	vos_printf("*------------DIAG Agent RECEIVE CMD-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : 0x%x \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_AGENT_DISPATCH_CMD].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_AGENT_DISPATCH_CMD].ulRserved1,
            pstTable[EN_DIAG_DEBUG_AGENT_DISPATCH_CMD].ulRserved2);

}

VOS_VOID Debug_DiagAppgent(VOS_VOID);
VOS_VOID Debug_DiagAppgent(VOS_VOID)
{
    DIAG_DEBUG_INFO_TBL_STRU* pstTable;
    pstTable = diag_DebugGetInfo();

    vos_printf("*------------DIAG NV RD RECEIVE CMD-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
            pstTable[EN_DIAG_DEBUG_NV_RD].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_NV_RD].ulRserved1,
            pstTable[EN_DIAG_DEBUG_NV_RD].ulRserved2,
			pstTable[EN_DIAG_DEBUG_NV_RD].ulRserved3);

	vos_printf("*------------DIAG NV WR RECEIVE CMD-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
            pstTable[EN_DIAG_DEBUG_NV_WR].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_NV_WR].ulRserved1,
            pstTable[EN_DIAG_DEBUG_NV_WR].ulRserved2,
			pstTable[EN_DIAG_DEBUG_NV_WR].ulRserved3);

	vos_printf("*------------DIAG NV IMPORT RECEIVE CMD-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
            pstTable[EN_DIAG_DEBUG_NV_IMPORT].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_NV_IMPORT].ulRserved1,
            pstTable[EN_DIAG_DEBUG_NV_IMPORT].ulRserved2,
            pstTable[EN_DIAG_DEBUG_NV_IMPORT].ulRserved3);

	vos_printf("*------------DIAG NV EXPORT RECEIVE CMD-------------------\n");
	vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
				pstTable[EN_DIAG_DEBUG_NV_EXPORT].ulCalledNum,
				pstTable[EN_DIAG_DEBUG_NV_EXPORT].ulRserved1,
				pstTable[EN_DIAG_DEBUG_NV_EXPORT].ulRserved2,
				pstTable[EN_DIAG_DEBUG_NV_EXPORT].ulRserved3);

    vos_printf("*------------DIAG LOG SAVE RECEIVE CMD-------------------\n");
	vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
            pstTable[EN_DIAG_DEBUG_LOG_SAVE].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_LOG_SAVE].ulRserved1,
            pstTable[EN_DIAG_DEBUG_LOG_SAVE].ulRserved2,
            pstTable[EN_DIAG_DEBUG_LOG_SAVE].ulRserved3);

    vos_printf("*------------DIAG PS PS_TRANS_REQ-------------------\n");
	vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
            pstTable[EN_DIAG_DEBUG_PS_TRANS_REQ].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_PS_TRANS_REQ].ulRserved1,
            pstTable[EN_DIAG_DEBUG_PS_TRANS_REQ].ulRserved2,
            pstTable[EN_DIAG_DEBUG_PS_TRANS_REQ].ulRserved3);

	vos_printf("*------------DIAG PS_TRANS_CNF-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
            pstTable[EN_DIAG_DEBUG_PS_TRANS_CNF].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_PS_TRANS_CNF].ulRserved1,
            pstTable[EN_DIAG_DEBUG_PS_TRANS_CNF].ulRserved2,
			pstTable[EN_DIAG_DEBUG_PS_TRANS_CNF].ulRserved3);
}

VOS_VOID Debug_DiagAgent(VOS_VOID);
VOS_VOID Debug_DiagAgent(VOS_VOID)
{
    DIAG_DEBUG_INFO_TBL_STRU* pstTable;
    pstTable = diag_DebugGetInfo();

    vos_printf("*------------DIAG AGENT INIT-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_AGENT_INIT].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_AGENT_INIT].ulRserved1,
            pstTable[EN_DIAG_DEBUG_AGENT_INIT].ulRserved2);

    vos_printf("*------------DIAG AGENT INIT ERROR-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_AGENT_INIT_ERROR].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_AGENT_INIT_ERROR].ulRserved1,
            pstTable[EN_DIAG_DEBUG_AGENT_INIT_ERROR].ulRserved2);

    vos_printf("*------------DIAG REG RD RECEIVE CMD-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
            pstTable[EN_DIAG_DEBUG_REG_RD].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_REG_RD].ulRserved1,
            pstTable[EN_DIAG_DEBUG_REG_RD].ulRserved2,
			pstTable[EN_DIAG_DEBUG_REG_RD].ulRserved3);

	vos_printf("*------------DIAG REG WR RECEIVE CMD-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
            pstTable[EN_DIAG_DEBUG_REG_WR].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_REG_WR].ulRserved1,
            pstTable[EN_DIAG_DEBUG_REG_WR].ulRserved2,
			pstTable[EN_DIAG_DEBUG_REG_WR].ulRserved3);

	vos_printf("*------------DIAG BBP SAMPLE RECEIVE CMD-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
            pstTable[EN_DIAG_DEBUG_BBP_SAMPLE].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_BBP_SAMPLE].ulRserved1,
            pstTable[EN_DIAG_DEBUG_BBP_SAMPLE].ulRserved2,
            pstTable[EN_DIAG_DEBUG_BBP_SAMPLE].ulRserved3);

	vos_printf("*------------DIAG BBP LOG RECEIVE CMD-------------------\n");
	vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
				pstTable[EN_DIAG_DEBUG_BBP_LOG].ulCalledNum,
				pstTable[EN_DIAG_DEBUG_BBP_LOG].ulRserved1,
				pstTable[EN_DIAG_DEBUG_BBP_LOG].ulRserved2,
				pstTable[EN_DIAG_DEBUG_BBP_LOG].ulRserved3);

	vos_printf("*------------DIAG BBP SAMPLE RECEIVE CMD-------------------\n");
    vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
            pstTable[EN_DIAG_DEBUG_BBP_SAMPLE].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_BBP_SAMPLE].ulRserved1,
            pstTable[EN_DIAG_DEBUG_BBP_SAMPLE].ulRserved2,
            pstTable[EN_DIAG_DEBUG_BBP_SAMPLE].ulRserved3);

	vos_printf("*------------DIAG LTE_DSP_CNF-------------------\n");
	vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
				pstTable[EN_DIAG_DEBUG_LTE_DSP_CNF].ulCalledNum,
				pstTable[EN_DIAG_DEBUG_LTE_DSP_CNF].ulRserved1,
				pstTable[EN_DIAG_DEBUG_LTE_DSP_CNF].ulRserved2,
				pstTable[EN_DIAG_DEBUG_LTE_DSP_CNF].ulRserved3);

    vos_printf("*------------DIAG TDS_DSP_CNF-------------------\n");
	vos_printf("CALL counts  : %d \n ulRserved1  : %d \n ulRserved2  : %d \n ulRserved3  : %d\n",
            pstTable[EN_DIAG_DEBUG_TDS_DSP_CNF].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_TDS_DSP_CNF].ulRserved1,
            pstTable[EN_DIAG_DEBUG_TDS_DSP_CNF].ulRserved2,
            pstTable[EN_DIAG_DEBUG_TDS_DSP_CNF].ulRserved3);
}

#if (VOS_OS_VER == VOS_LINUX)
VOS_VOID  Debug_DiagVcom(VOS_VOID);
VOS_VOID  Debug_DiagVcom(VOS_VOID)
{
    DIAG_DEBUG_INFO_TBL_STRU* pstTable;
    pstTable = diag_DebugGetInfo();


    vos_printf("*------------ENABLE-------------------\n");
    vos_printf("USB ENABLE counts  : %d \n USB ENABLE fail counts  : %d \n USB ENABLE fail branch  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_VCOM_INIT].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_VCOM_INIT_ERR].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_VCOM_INIT_ERR].ulRserved3);
    vos_printf("*------------DISABLE-------------------\n");
    vos_printf("USB DISABLE counts  : %d \n USB DISABLE fail counts  : %d \n USB DISABLE fail branch  : %d \n\n",
            pstTable[EN_DIAG_DEBUG_VCOM_DISABLE].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_VCOM_DISABLE_ERR].ulCalledNum,
            pstTable[EN_DIAG_DEBUG_VCOM_DISABLE_ERR].ulRserved3);

    vos_printf("*------------OPEN-------------------\n");
    vos_printf("VCOM1 OPEN counts  : %d \n VCOM1 OPEN fail counts  : %d \n  VCOM1 OPEN fail value : %d\n\n",
        pstTable[EN_DIAG_DEBUG_VCOM1_OPEN].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM1_OPEN_ERR].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM1_OPEN_ERR].ulRserved1,
		pstTable[EN_DIAG_DEBUG_VCOM1_OPEN_ERR].ulRserved2,
		pstTable[EN_DIAG_DEBUG_VCOM1_OPEN_ERR].ulRserved3);
    vos_printf("VCOM2 OPEN counts  : %d \n VCOM2 OPEN fail counts  : %d \n  VCOM2 OPEN fail value : %d\n\n",
        pstTable[EN_DIAG_DEBUG_VCOM2_OPEN].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM2_OPEN_ERR].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM2_OPEN_ERR].ulRserved1,
		pstTable[EN_DIAG_DEBUG_VCOM2_OPEN_ERR].ulRserved2,
		pstTable[EN_DIAG_DEBUG_VCOM2_OPEN_ERR].ulRserved3);

    vos_printf("*------------CLOSE-------------------\n");
    vos_printf("VCOM1 CLOSE counts  : %d \n VCOM1 CLOSE fail counts  : %d \n  VCOM1 CLOSE fail value : %d\n\n",
        pstTable[EN_DIAG_DEBUG_VCOM1_CLOSE].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM1_CLOSE_ERR].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM1_CLOSE_ERR].ulRserved1);
    vos_printf("VCOM2 CLOSE counts  : %d \n VCOM2 CLOSE fail counts  : %d \n  VCOM2 CLOSE fail value : %d\n\n",
        pstTable[EN_DIAG_DEBUG_VCOM2_CLOSE].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM2_CLOSE_ERR].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM2_CLOSE_ERR].ulRserved1);

    vos_printf("*------------WRITE_�첽д-------------------\n");
    vos_printf("VCOM1 write counts  : %d \n VCOM1  write len : %d \n VCOM1 write OK counts  : %d \n  VCOM1 Last write OK len : %d\n\n",
        pstTable[EN_DIAG_DEBUG_VCOM1_WRT].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM1_WRT].ulRserved1,
        pstTable[EN_DIAG_DEBUG_VCOM1_WRT_SUCC].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM1_WRT_SUCC].ulRserved1);
    vos_printf("VCOM2 write counts  : %d \n VCOM2  write len : %d\n VCOM2 write OK counts  : %d \n  VCOM2 Last write OK len : %d\n\n",
        pstTable[EN_DIAG_DEBUG_VCOM2_WRT].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM2_WRT].ulRserved1,
        pstTable[EN_DIAG_DEBUG_VCOM2_WRT_SUCC].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM2_WRT_SUCC].ulRserved1);

    vos_printf("*------------WRITE CALL BACK-------------------\n");
    vos_printf("VCOM1 WRITE CALL BACK counts  : %d \n VCOM1 WRITE CALL BACK fail counts  : %d \n  VCOM1 WRITE fail addr : %d\nVCOM1 WRITE fail len :%d\n\n",
        pstTable[EN_DIAG_DEBUG_VCOM1_WRT_CB].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM1_WRT_CB_ERR].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM1_WRT_CB_ERR].ulRserved1,
        pstTable[EN_DIAG_DEBUG_VCOM1_WRT_CB_ERR].ulRserved2);
    vos_printf("VCOM2 WRITE CALL BACK counts  : %d \n VCOM2 WRITE CALL BACK fail counts  : %d \n  VCOM2 WRITE fail addr : %d\nVCOM2 WRITE fail len :%d\n\n",
        pstTable[EN_DIAG_DEBUG_VCOM2_WRT_CB].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM2_WRT_CB_ERR].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM2_WRT_CB_ERR].ulRserved1,
        pstTable[EN_DIAG_DEBUG_VCOM2_WRT_CB_ERR].ulRserved2);

    vos_printf("*------------EVT CALL BACK-------------------\n");
    vos_printf("VCOM1 EVT CALL BACK counts  : %d \n VCOM1 EVT  type : %d\n\n",
        pstTable[EN_DIAG_DEBUG_VCOM1_EVT].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM1_EVT].ulRserved1);
    vos_printf("VCOM2 EVT CALL BACK counts  : %d \n VCOM2 EVT  type : %d\n\n",
        pstTable[EN_DIAG_DEBUG_VCOM2_EVT].ulCalledNum,
        pstTable[EN_DIAG_DEBUG_VCOM2_EVT].ulRserved1);

}

VOS_VOID  Debug_DiagUdiRead(VOS_VOID);
VOS_VOID  Debug_DiagUdiRead(VOS_VOID)
{
    DIAG_DEBUG_INFO_TBL_STRU* pstTable;
    pstTable = diag_DebugGetInfo();


    vos_printf("*------------UDI PRE READ FROM BSP----------------\n");
    vos_printf("Times                    : %d \n", pstTable[EN_DIAG_DEBUG_UDI_READ_START].ulCalledNum);
    vos_printf("slReadlen                : %d \n",  pstTable[EN_DIAG_DEBUG_UDI_READ_START].ulRserved1);
    vos_printf("usToReadSize             : %d \n",  pstTable[EN_DIAG_DEBUG_UDI_READ_START].ulRserved2);
    vos_printf("ucRedBuf                 : %d \n",  pstTable[EN_DIAG_DEBUG_UDI_READ_START].ulRserved3);
    vos_printf("RTC Time                 : %d \n\n", pstTable[EN_DIAG_DEBUG_UDI_READ_START].ulRtcTime);

    vos_printf("*------------UDIREAD FROM BSP----------------\n");
    vos_printf("Times                    : %d \n", pstTable[EN_DIAG_DEBUG_UDI_READ_END].ulCalledNum);
    vos_printf("slReadlen                : %d \n",  pstTable[EN_DIAG_DEBUG_UDI_READ_END].ulRserved1);
    vos_printf("usToReadSize             : %d \n",  pstTable[EN_DIAG_DEBUG_UDI_READ_END].ulRserved2);
    vos_printf("ucRedBuf                 : %d \n",  pstTable[EN_DIAG_DEBUG_UDI_READ_END].ulRserved3);
    vos_printf("RTC Time                 : %d \n\n", pstTable[EN_DIAG_DEBUG_UDI_READ_END].ulRtcTime);
}

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
VOS_VOID  Debug_DiagSocpVote(VOS_VOID)
{
    DIAG_DEBUG_INFO_TBL_STRU* pstTable;
    pstTable = diag_DebugGetInfo();

    vos_printf("*------------DIAG APP SOCP VOTE----------------\n");
    vos_printf("CALL counts  : %d \nVoteId       : %d \nVoteType     : %d \nulRserved3   : %d\nRTC Time     : %d\n",
        pstTable[EN_DIAG_APP_SOCP_VOTE].ulCalledNum,
        pstTable[EN_DIAG_APP_SOCP_VOTE].ulRserved1,
        pstTable[EN_DIAG_APP_SOCP_VOTE].ulRserved2,
        pstTable[EN_DIAG_APP_SOCP_VOTE].ulRserved3,
        pstTable[EN_DIAG_APP_SOCP_VOTE].ulRtcTime);

    vos_printf("*------------DIAG APP SOCP VOTE ERR----------------\n");
    vos_printf("CALL counts  : %d \nVoteId       : %d \nVoteType     : %d \nulRserved3   : %d\nRTC Time     : %d\n",
        pstTable[EN_DIAG_APP_SOCP_VOTE_ERR].ulCalledNum,
        pstTable[EN_DIAG_APP_SOCP_VOTE_ERR].ulRserved1,
        pstTable[EN_DIAG_APP_SOCP_VOTE_ERR].ulRserved2,
        pstTable[EN_DIAG_APP_SOCP_VOTE_ERR].ulRserved3,
        pstTable[EN_DIAG_APP_SOCP_VOTE_ERR].ulRtcTime);
}
#endif
#endif

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
VOS_VOID  Debug_DiagDspMb(VOS_VOID)
{
    DIAG_DEBUG_INFO_TBL_STRU* pstTable;
    pstTable = diag_DebugGetInfo();

    vos_printf("*------------DIAG DSP MB MSG----------------\n");
    vos_printf("CALL counts  : %d \nulRserved1   : %d \nulRserved2    : %d \nulRserved3    : %d\nRTC Time     : %d\n",
        pstTable[EN_DIAG_AGENT_LDSP_MB_MSG].ulCalledNum,
        pstTable[EN_DIAG_AGENT_LDSP_MB_MSG].ulRserved1,
        pstTable[EN_DIAG_AGENT_LDSP_MB_MSG].ulRserved2,
        pstTable[EN_DIAG_AGENT_LDSP_MB_MSG].ulRserved3,
        pstTable[EN_DIAG_AGENT_LDSP_MB_MSG].ulRtcTime);
}
#endif


VOS_VOID diag_help(VOS_VOID);
VOS_VOID diag_help(VOS_VOID)
{

    vos_printf("Debug_DiagVcom:      �鿴ACOREͨ����״̬,���͸�USB������USB���ص�����\n");
    vos_printf("Debug_DiagUdiRead:   �鿴ACORE��USB��ȡ����\n");
    vos_printf("Debug_DiagSocp:      �鿴SOCP����������¼\n");
	vos_printf("Debug_DiagFw:        �鿴����յ������agent�ظ����\n");
    vos_printf("Debug_DiagApi:		 �鿴PS����API����\n");
    vos_printf("Debug_DiagCfg:		 �鿴HSO�·���������״̬\n");
    vos_printf("Debug_DiagCmd:       �鿴FW,AGENTģ���յ�����\n");
    vos_printf("Debug_DiagAppgent:   �鿴APP AGENT���������\n");
    vos_printf("Debug_DiagAgent:     �鿴AGENT���������\n");
	vos_printf("diag_BufHelp:        �鿴DIAG buf״̬������\n");
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    vos_printf("Debug_DiagSocpVote:  �鿴DIAG APP��SOCPͶƱ״̬������\n");
    vos_printf("Debug_DiagDspMb:     �鿴DIAG AGENT��LDSP���佻��������\n");
#endif
}
/*****************************************************************************
�� �� ��  : Debug_DiagCreateFile
��������  : �������debug�ļ�������Ѿ����������ɾ��
�������  : VOS_VOID
�������  : VOS_VOID
�� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID Debug_DiagCreateFile(VOS_VOID)
{
#if 0
    FILE                      *logfp = NULL;

    logfp = DRV_FILE_OPEN(DecoderDestReadCB_LogPath, "w+");
    if (VOS_NULL_PTR == logfp)
    {
        diag_printf("Create DecoderDestReadCB_LogPath txt fail\n");
    }
    else
    {
        DRV_FILE_CLOSE(logfp);
    }

    logfp = DRV_FILE_OPEN(UsbCtrlRdCB_LogPath, "w+");
    if (VOS_NULL_PTR == logfp)
    {
        diag_printf("Create UsbCtrlRdCB_LogPath txt fail\n");
    }
    else
    {
        DRV_FILE_CLOSE(logfp);
    }
#endif
    return;
}
/*****************************************************************************
�� �� ��  : diag_PrintToFile
��������  : ������������ݵ��ļ�ϵͳ
�������  : VOS_CHAR* logpath:�ļ�·��
            VOS_CHAR* pdata:Ҫ�洢�����ݵ�ָ��
            VOS_UINT len:Ҫ�洢�����ݵĳ���
�������  : VOS_VOID
�� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID diag_PrintToFile(VOS_CHAR* logpath, VOS_CHAR* pdata, VOS_UINT len)
{
#if 0
    FILE *      logfp = NULL;
    VOS_UINT32 ulRet;

    if((VOS_NULL == pdata)||(0 == len))
    {
        return;
    }

    logfp = DRV_FILE_OPEN(logpath,"wb+");
    if(!logfp)
    {
        return;
    }

    ulRet = DRV_FILE_WRITE(pdata, 1, len, logfp);
    if(ulRet!= len)
    {
    }

    DRV_FILE_CLOSE(logfp);
#endif
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


