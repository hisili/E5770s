

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "omprivate.h"
#include "omsdlog.h"
#include "cpm.h"
#include "OmApp.h"
#include "NVIM_Interface.h"
#include "DrvInterface.h"
#include "omnvinterface.h"
#include "fastlz.h" /* ��Դѹ���㷨 */

#if (VOS_OS_VER == VOS_LINUX)
#include <linux/scatterlist.h>
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_OM_SD_LOG_C
/*lint +e767 */

/*****************************************************************************
2 ȫ�ֱ�������
*****************************************************************************/
/* ���ڻ�����SD����д���trace */
OM_SD_BUFFER_INNER_DATA_STRU       *g_pstSdBuffer;

/* дSD���ı�־����PC�ർ��SD��traceʱ�ñ�־��Ϊ����д */
VOS_UINT32                          g_ulWriteSDLogFlag = VOS_OK;

/* ��¼��ȡSD��trace�Ĵ��� */
VOS_UINT32                          g_ulReadSDErrType  = OM_SD_OK;

/* ��¼дSD��trace�Ĵ��� */
VOS_UINT32                          g_ulWriteSDErrType = OM_SD_OK;

/* ��¼��SD��cluster����Ŀ�����Ǹ�cluster��ʼ�� */
OM_SD_READ_INFO_STRU                g_stReadInfo;

/* ����SD����ͷ��������Ϣ */
OM_SD_HEAD_STRU                     *g_pstHeadInfo;

VOS_UINT32                          g_ulInterval = 10;

VOS_UINT8*                          g_pucBuffer;

/* ����SD����Debug ��Ϣ */
OM_SD_DEBUG_INFO                    g_stOmSDDebugInfo;

#if (VOS_LINUX == VOS_OS_VER)

#if (FEATURE_ON == FEATURE_COMPRESS_WRITE_LOG_FILE)
VOS_CHAR                            g_acFSLogType[] = "ucmx";
#else
VOS_CHAR                            g_acFSLogType[] = "ucm";
#endif

#if (FEATURE_ON == FEATURE_MULTI_FS_PARTITION)
VOS_CHAR                            g_acFSLogDir[OM_SD_LOG_PATH_MAX_LENGTH]     = "/mnvm3:0/Log";
VOS_CHAR                            g_acFSLogCfgPath[OM_SD_LOG_PATH_MAX_LENGTH] = "/mnvm3:0/Log/Config";
OM_FLASH_DEBUG_INFO_STRU            g_stFSLogFileInfo =
                                        {VOS_FALSE, 0, 0, 0, OM_FLASH_DEFAULT_FILE_SIZE, 0, 0, 0, "/mnvm3:0/Log/OmLog"};
#else
VOS_CHAR                            g_acFSLogDir[OM_SD_LOG_PATH_MAX_LENGTH]     = "/online/modemlog/Log";
VOS_CHAR                            g_acFSLogCfgPath[OM_SD_LOG_PATH_MAX_LENGTH] = "/online/modemlog/Log/Config";
OM_FLASH_DEBUG_INFO_STRU            g_stFSLogFileInfo =
                                        {VOS_FALSE, 0, 0, 0, OM_FLASH_DEFAULT_FILE_SIZE, 0, 0, 0,"/online/modemlog/Log/OmLog"};
#endif
#elif (VOS_WIN32 == VOS_OS_VER)
VOS_CHAR                            g_acFSLogDir[] = "";
VOS_CHAR                            g_acFSLogCfgPath[] = "";
OM_FLASH_DEBUG_INFO_STRU            g_stFSLogFileInfo;

#endif

VOS_UINT32                          g_ulLogMaxCout = LOG_WRITE_MAX_COUNT;

OM_FLASH_CFG_INFO_STRU              g_stFSCfgFileInfo;

NV_FLASH_LOG_RECORD_STRU            g_stFlashLogCfg;

VOS_UINT32                          g_ulFSlogStatus;

VOS_UINT32                          g_ulFSLogErrFlag = LOG_OPERATION_OK;

#if (FEATURE_ON == FEATURE_COMPRESS_WRITE_LOG_FILE)
/* ���ѹ�������ݣ������ָ����Լ�ѹ�������ݳ��� */
OM_UCMX_DATA_INFO_STRU              g_stCompressData;

/* ���������� */
VOS_UINT8                           g_aucPackData[OM_MAX_PACK_DATA_LEN];
VOS_UINT32                          g_ulPackLen = 0;

/* ��ν�ɲ� */
OM_COMPRESS_DEBUG_OG_STRU           g_stCompressDebugLog;
#endif
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_UINT32 OM_SDInit(VOS_VOID)
{
    VOS_MemSet(&g_stOmSDDebugInfo, 0, sizeof(OM_CHANNLE_PORT_CFG_STRU));

    CPM_PhySendReg(CPM_SD_PORT, (CPM_FUNC)OM_SDWriteCard);

    g_pstHeadInfo = (OM_SD_HEAD_STRU*)BSP_MALLOC(OM_SD_BLOCK_SIZE, MEM_NORM_DDR_POOL);

    if(VOS_NULL_PTR == g_pstHeadInfo)
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "OM_SDInit:Alloc Head Info Memory fail!");

        return VOS_ERR;
    }

    g_pstSdBuffer = (OM_SD_BUFFER_INNER_DATA_STRU *)BSP_MALLOC(sizeof(OM_SD_BUFFER_INNER_DATA_STRU),
                                                                  MEM_NORM_DDR_POOL);

    if(VOS_NULL_PTR == g_pstSdBuffer)
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "OM_SDInit:Alloc SD Buffer Memory fail!");

        return VOS_ERR;
    }

    /* ��ʼ����������ʼֵ */
    g_pstSdBuffer->ulDataLen = 0;

    return VOS_OK;
}


VOS_UINT32 OM_SDReadHeadInfo(VOS_VOID)
{
    VOS_INT          lRet;
    VOS_UINT         ulSize;

    /* ���õ���ӿڶ�ȡSD����ͷ��������Ϣ��ͷ��������Ϣ�洢�ڵ�0��block */
    DRV_SD_SG_INIT_TABLE((void *)g_pstHeadInfo, OM_SD_BLOCK_SIZE);

    lRet = DRV_SD_MULTI_TRANSFER(0, 1, OM_SD_BLOCK_SIZE, RDFlAG);

    if(VOS_OK != lRet)
    {
        vos_printf("OM_SDReadHeadInfo:err DRV_SD_TRANSFER\n");

        g_ulWriteSDErrType = OM_ERR_DRVAPI;

        return VOS_ERR;
    }

    /* ���SD��Ϊ�¿�,��ʼ��ͷ��������Ϣ */
    if((OM_SD_MAGIC_NUMBER != g_pstHeadInfo->ulMagicNum)
        || (OM_SD_OPPOSITE_MAGIC_NUMBER != g_pstHeadInfo->ulOppositeMagicNum))
    {
        /* ��ȡSD������ */
        ulSize = (VOS_UINT32)DRV_SD_GET_CAPACITY();

        if(0 == ulSize)
        {
            vos_printf("OM_SDReadHeadInfo:ulSize is 0\n");

            g_ulWriteSDErrType = OM_ERR_VALIDPARA;

            return VOS_ERR;
        }

        /* ����SD���ܵ�cluster��Ŀ��Ԥ��10%������ */
        g_pstHeadInfo->ulTotalCNum = (ulSize - (ulSize/10)) / OM_SD_BLOCK_NUM_ONE_CLUSTER;

        g_pstHeadInfo->ulMagicNum = OM_SD_MAGIC_NUMBER;

        g_pstHeadInfo->ulOppositeMagicNum = OM_SD_OPPOSITE_MAGIC_NUMBER;

        g_pstHeadInfo->ulLoopOutFlag = 0;

        g_pstHeadInfo->ulNextCid = 1;

        /* ��ʼ��SD��ͷ��������Ϣ */
        DRV_SD_SG_INIT_TABLE((void *)g_pstHeadInfo, OM_SD_BLOCK_SIZE);
        lRet = DRV_SD_MULTI_TRANSFER(0, 1, OM_SD_BLOCK_SIZE, WRFlAG);

        if(VOS_OK != lRet)
        {
            vos_printf("OM_SDFlushHeadInfo:err DRV_SD_TRANSFER\n");

            g_ulWriteSDErrType = OM_ERR_DRVAPI;

            return VOS_ERR;
        }

    }

    return VOS_OK;

}


VOS_UINT32 OM_SDFlushHeadInfo(VOS_VOID)
{
    VOS_INT lRet;

    g_pstHeadInfo->ulNextCid++;

    /* nextCID�ķ�Χʼ���� 1��(g_stHeadInfo.ulTotalCNum -1)֮�䣬��0��cluster���ڱ���ͷ��������Ϣ*/
    if(0 == (g_pstHeadInfo->ulNextCid % g_pstHeadInfo->ulTotalCNum))
    {
        g_pstHeadInfo->ulNextCid = 1;

        g_pstHeadInfo->ulLoopOutFlag = 1;
    }

    /* ����ͷ��������Ϣ */

    DRV_SD_SG_INIT_TABLE((void *)g_pstHeadInfo, OM_SD_BLOCK_SIZE);

    lRet = DRV_SD_MULTI_TRANSFER(0, 1, OM_SD_BLOCK_SIZE, WRFlAG);

    if(VOS_OK != lRet)
    {
        vos_printf("OM_SDFlushHeadInfo:err DRV_SD_TRANSFER\n");

        g_ulWriteSDErrType = OM_ERR_DRVAPI;

        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 OM_SDWriteCard(VOS_UINT8* pucData, VOS_UINT16 usLen)
{
    VOS_UINT32 ulCurBufDataLen;
    VOS_INT    lRet;
    VOS_UINT32 ulSecAddr;

    ulCurBufDataLen = g_pstSdBuffer->ulDataLen;

    /* ���Ŀ��bufferʣ��ռ䲻���洢����TRACE */
    if(OM_SD_BUFFER_MAX_DATA_LEN < (ulCurBufDataLen + usLen))
    {
        if(VOS_ERR == OM_SDReadHeadInfo())
        {
            vos_printf("OM_SDWriteBuffer:SD card NOT IN\n");

            g_stOmSDDebugInfo.ulReadHeadErrLenth += usLen;
            return VOS_ERR;
        }

        /* ����дSD������ʼblock */
        ulSecAddr                        = g_pstHeadInfo->ulNextCid * OM_SD_BLOCK_NUM_ONE_CLUSTER;

        g_pstSdBuffer->ulClusterId         = g_pstHeadInfo->ulNextCid;

        g_pstSdBuffer->ulOppositeClusterId = ~g_pstHeadInfo->ulNextCid;

        /* дSD��ʧ��ʱ��¼���������˳� */
        DRV_SD_SG_INIT_TABLE((void *)g_pstSdBuffer, OM_SD_BLOCK_NUM_ONE_CLUSTER*OM_SD_BLOCK_SIZE);
        lRet = DRV_SD_MULTI_TRANSFER(ulSecAddr, OM_SD_BLOCK_NUM_ONE_CLUSTER, OM_SD_BLOCK_SIZE, WRFlAG);

        g_stOmSDDebugInfo.ulTatalBlock += OM_SD_BLOCK_NUM_ONE_CLUSTER;

        g_stOmSDDebugInfo.ulDataLenth  += g_pstSdBuffer->ulDataLen;

        if(g_stOmSDDebugInfo.ulDataLenth > OM_SD_MAX_DATA_LENTH)
        {
            g_stOmSDDebugInfo.ulOverNum++;
            g_stOmSDDebugInfo.ulDataLenth -= OM_SD_MAX_DATA_LENTH;
        }

        if(VOS_OK != lRet)
        {
            vos_printf("OM_SDWriteBuffer:err DRV_SD_TRANSFER\n");

            g_ulWriteSDErrType = OM_ERR_DRVAPI;

            return VOS_ERR;
        }

        /* ������д��SD����buffer��д����־�������ֶ���� */
        g_pstSdBuffer->ulDataLen = 0;

        OM_SDFlushHeadInfo();

        ulCurBufDataLen = 0;
    }

    /* copy���� */
    VOS_MemCpy((g_pstSdBuffer->aucBuffer + ulCurBufDataLen), pucData, usLen);

    /* ���³��� */
    g_pstSdBuffer->ulDataLen += (VOS_UINT32)usLen;

    g_stOmSDDebugInfo.ulRemainLenth = g_pstSdBuffer->ulDataLen;

    return VOS_OK;

}


VOS_VOID OM_SDReadCluster(VOS_UINT32 ulPacketSn)
{
    VOS_UINT32                  ulCurReadCID;
    VOS_INT                     lRet;
    OM_APP_MSG_EX_STRU          *pstOmToAppMsg;
    OM_APP_READ_SD_STRU         *pstOmReadSD;
    VOS_UINT32                  ulSecAddr;
    VOS_UINT32                  ulMinValue = g_ulInterval;
    VOS_UINT32                  i;

    /* PC����������ݰ���ų�����Ҫ�������ʱ */
    if(ulPacketSn > (g_stReadInfo.ulTotalNeedCNum - 1))
    {
        g_ulReadSDErrType = OM_ERR_VALIDPARA;

        OM_AcpuSendResult(OM_READSD_FUNC, OM_ERR_VALIDPARA, APP_OM_READ_SD_CNF);

        vos_printf("OM_SDReadCluster:err ulPacketSn\n");

        return;
    }

    /* ���㱾�η��͸�PC���IND���� */
    if(ulMinValue > (g_stReadInfo.ulTotalNeedCNum - ulPacketSn))
    {
       ulMinValue = g_stReadInfo.ulTotalNeedCNum - ulPacketSn;
    }

    for(i = 0; i < ulMinValue; i++)
    {
        ulCurReadCID = g_stReadInfo.ulStartCID + ulPacketSn;

        /* ������0��cluster��ͷ��������Ϣ��ȡ */
        if(ulCurReadCID > (g_pstHeadInfo->ulTotalCNum - 1))
        {
            ulSecAddr = ((ulCurReadCID % g_pstHeadInfo->ulTotalCNum) + 1) * OM_SD_BLOCK_NUM_ONE_CLUSTER;
        }
        else
        {
            ulSecAddr = ulCurReadCID * OM_SD_BLOCK_NUM_ONE_CLUSTER;
        }

        /* ��SD���е����� */
        DRV_SD_SG_INIT_TABLE((void *)g_pstSdBuffer, OM_SD_BLOCK_NUM_ONE_CLUSTER*OM_SD_BLOCK_SIZE);

        lRet =  DRV_SD_MULTI_TRANSFER(ulSecAddr, OM_SD_BLOCK_NUM_ONE_CLUSTER, OM_SD_BLOCK_SIZE, RDFlAG);

        if(VOS_OK != lRet)
        {
            g_ulReadSDErrType = OM_ERR_DRVAPI;

            OM_AcpuSendResult(OM_READSD_FUNC, OM_ERR_DRVAPI, APP_OM_READ_SD_CNF);

            vos_printf("OM_SDReadCluster:err DRV_SD_TRANSFER\n");

            return;
        }

        pstOmToAppMsg = (OM_APP_MSG_EX_STRU*)g_pstSdBuffer->aucReserved;

        pstOmReadSD = (OM_APP_READ_SD_STRU*)(pstOmToAppMsg->aucPara);

        pstOmReadSD->ulClusterId = g_pstSdBuffer->ulClusterId;

        pstOmReadSD->ulSn = ulPacketSn;

        /* ���cluster��CID�ֶκ�~CID�ֶβ���ȡ���Ĺ�ϵ�Ļ�������Ϊ��ǰcluster������ */
        if(g_pstSdBuffer->ulClusterId != (~g_pstSdBuffer->ulOppositeClusterId))
        {
            g_ulReadSDErrType = OM_ERR_DATAERR;

            pstOmReadSD->ulErrCode = VOS_ERR;

            pstOmToAppMsg->usLength = OM_APP_MSG_EX_LEN - VOS_OM_HEADER_LEN + OM_READ_SD_HEAD_LEN;

            vos_printf("OM_SDReadCluster:data err\n");
        }
        else
        {
            pstOmReadSD->ulErrCode = VOS_OK;

            pstOmToAppMsg->usLength = (VOS_UINT16)(OM_APP_MSG_EX_LEN - VOS_OM_HEADER_LEN + OM_READ_SD_HEAD_LEN
                                      + g_pstSdBuffer->ulDataLen);
        }

        OM_AcpuSendContent(OM_READSD_FUNC, (OM_RSP_PACKET_STRU *)(g_pstSdBuffer->aucReserved), APP_OM_READ_SD_IND);

        ulPacketSn++;
    }


    return;
}


VOS_UINT32 OM_SDGetReadPosition(VOS_UINT32 ulNeedSize, VOS_UINT32 ulOffsetSize)
{
    VOS_UINT32                      ulTotalClusterNum;
    VOS_UINT32                      ulOffsetClusterNum;

    ulOffsetClusterNum = (ulOffsetSize + OM_SD_CLUSTER_DATA_LEN - 1)/OM_SD_CLUSTER_DATA_LEN;

    g_stReadInfo.ulTotalNeedCNum = (ulNeedSize + OM_SD_CLUSTER_DATA_LEN - 1)/OM_SD_CLUSTER_DATA_LEN;

    ulTotalClusterNum = g_stReadInfo.ulTotalNeedCNum + ulOffsetClusterNum;

    if (0 == g_pstHeadInfo->ulLoopOutFlag)
    {
        /* �û�ƫ�Ƶ����ݴ���SD������������ */
        if (ulOffsetClusterNum >= (g_pstHeadInfo->ulNextCid - 1))
        {
            g_stReadInfo.ulTotalNeedCNum = 0;

            g_ulReadSDErrType = OM_ERR_EMPTY;

            return OM_ERR_EMPTY;
        }

        /* �û���Ҫ�����ݴ���SD������������ */
        if(ulTotalClusterNum > (g_pstHeadInfo->ulNextCid - 1))
        {
            g_stReadInfo.ulStartCID = 1;

            g_stReadInfo.ulTotalNeedCNum = (g_pstHeadInfo->ulNextCid - 1) - ulOffsetClusterNum;

            g_ulReadSDErrType = OM_ERR_NOENOUGHDATA;

            return OM_SD_OK;
        }

        /* �û���Ҫ������С��SD������������ */
        g_stReadInfo.ulStartCID = g_pstHeadInfo->ulNextCid - ulTotalClusterNum;

        return OM_SD_OK;

    }

    /* ����SD�������з�ת�������û�ƫ�Ƶ����ݴ���SD������������*/
    if (ulOffsetClusterNum >= (g_pstHeadInfo->ulTotalCNum - 1))
    {
        g_stReadInfo.ulTotalNeedCNum = 0;

        g_ulReadSDErrType = OM_ERR_EMPTY;

        return OM_ERR_EMPTY;
    }

    /* ��0��cluster���ڱ���ͷ��������Ϣ */
    if(ulTotalClusterNum > (g_pstHeadInfo->ulTotalCNum - 1))
    {
        g_stReadInfo.ulTotalNeedCNum = (g_pstHeadInfo->ulTotalCNum - 1) - ulOffsetClusterNum;

        /* SD��������תʱ���洢���������Ϊ��һ����д���cluster���� */
        g_stReadInfo.ulStartCID = g_pstHeadInfo->ulNextCid;

        return OM_SD_OK;
    }

    /* ʵ����Ҫ������С��SD���е����� */
    if(g_pstHeadInfo->ulNextCid > ulTotalClusterNum)
    {
        g_stReadInfo.ulStartCID = g_pstHeadInfo->ulNextCid - ulTotalClusterNum;
    }
    else
    {
        g_stReadInfo.ulStartCID = g_pstHeadInfo->ulTotalCNum - (ulTotalClusterNum - (g_pstHeadInfo->ulNextCid - 1));
    }

    return OM_SD_OK;
}


VOS_UINT32 OM_SDParaCheck(VOS_UINT32 ulDataSize, VOS_UINT32 *pulErrNo)
{
    VOS_INT lRet;

    if(0 == ulDataSize)
    {
        *pulErrNo = OM_ERR_VALIDPARA;

        return VOS_ERR;
    }

    /* ���õ���ӿڶ�ȡSD����ͷ��������Ϣ��ͷ��������Ϣ�洢�ڵ�0��block */
    DRV_SD_SG_INIT_TABLE((void *)g_pstHeadInfo, OM_SD_BLOCK_SIZE);

    lRet = DRV_SD_MULTI_TRANSFER(0, 1, OM_SD_BLOCK_SIZE, RDFlAG);

    if(VOS_OK != lRet)
    {
        vos_printf("OM_SDInit:err DRV_SD_TRANSFER\n");

        g_ulWriteSDErrType = OM_ERR_DRVAPI;

        *pulErrNo = OM_ERR_DRVAPI;

        return VOS_ERR;
    }

    /* ���SD��Ϊ�¿�,��ʼ��ͷ��������Ϣ */
    if((OM_SD_MAGIC_NUMBER != g_pstHeadInfo->ulMagicNum)
        || (OM_SD_OPPOSITE_MAGIC_NUMBER != g_pstHeadInfo->ulOppositeMagicNum))
    {
       *pulErrNo = OM_ERR_NEWSDCARD;

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID OM_SDReadReqProc(APP_OM_READ_SD_REQ_STRU * pstReadSDReq)
{
    VOS_UINT32                      ulErrNo = OM_SD_BUTT;
    VOS_UINT32                      ulRet;
    OM_APP_MSG_EX_STRU              *pstOmToAppMsg;
    OM_APP_READ_SD_CNF_STRU         *pstOmToAppCnf;

    ulRet = OM_SDParaCheck(pstReadSDReq->ulTotalSize, &ulErrNo);

    if(VOS_OK != ulRet)
    {
        OM_AcpuSendResult(OM_READSD_FUNC, ulErrNo, APP_OM_READ_SD_CNF);

        vos_printf("OM_SDReadReqProc:reply APP_OM_READ_SD_CNF\n");

        g_ulReadSDErrType = ulErrNo;

        return;
    }

    /* ��ȡʵ����Ҫ����cluster��Ŀ����ʼ����λ�� */
    ulRet = OM_SDGetReadPosition(pstReadSDReq->ulTotalSize, pstReadSDReq->ulOffsetSize);

    /*���㷢�͸����߲���Ϣ�����ܳ���*/
    pstOmToAppMsg = (OM_APP_MSG_EX_STRU*)VOS_MemAlloc(WUEPS_PID_OM, DYNAMIC_MEM_PT, OM_APP_MSG_EX_LEN + sizeof(OM_APP_READ_SD_CNF_STRU));

    if(VOS_NULL_PTR == pstOmToAppMsg)
    {
        g_ulReadSDErrType = OM_ERR_MALLOCSPACE;

        OM_AcpuSendResult(OM_READSD_FUNC, OM_ERR_MALLOCSPACE, APP_OM_READ_SD_CNF);

        return;
    }

    /* �����Ϣ�ֶβ�����Ϣ���͸�PC�� */
    pstOmToAppMsg->usLength = (OM_APP_MSG_EX_LEN + sizeof(OM_APP_READ_SD_CNF_STRU) - VOS_OM_HEADER_LEN);

    pstOmToAppCnf = (OM_APP_READ_SD_CNF_STRU*)(pstOmToAppMsg->aucPara);

    pstOmToAppCnf->ulResult     = ulRet;

    pstOmToAppCnf->ulReportCNum = g_stReadInfo.ulTotalNeedCNum;

    if(0 == g_pstHeadInfo->ulLoopOutFlag)
    {
        pstOmToAppCnf->ulHaveCNum = g_pstHeadInfo->ulNextCid - 1;
    }
    else
    {
        pstOmToAppCnf->ulHaveCNum = g_pstHeadInfo->ulTotalCNum - 1;
    }

    OM_AcpuSendContent(OM_READSD_FUNC, (OM_RSP_PACKET_STRU*)pstOmToAppMsg, APP_OM_READ_SD_CNF);

    VOS_MemFree(WUEPS_PID_OM, pstOmToAppMsg);

    return;

}


VOS_VOID OM_ReadSdMsgProc(OM_REQ_PACKET_STRU *pstRspPacket, OM_RSP_FUNC *pstRspFuncPtr)
{
    APP_OM_MSG_EX_STRU              *pstAppToOmMsg;

   /* ���SD���Ƿ���λ */
    if(VOS_OK != DRV_SD_GET_STATUS())
    {
        g_ulReadSDErrType = OM_ERR_NOCARD;

        vos_printf("\r\n OM_ReadSdMsgProc: DRV_SD_GET_STATUS return ERROR");

        OM_AcpuSendResult(OM_READSD_FUNC, OM_ERR_NOCARD, APP_OM_READ_SD_CNF);

        return;
    }

    pstAppToOmMsg   = (APP_OM_MSG_EX_STRU*)pstRspPacket;

    /* ����PC�ർ��SD�����ݵ���Ϣ */
    if(APP_OM_READ_SD_DATA_REQ == pstAppToOmMsg->usPrimId)
    {
        OM_SDReadReqProc((APP_OM_READ_SD_REQ_STRU *)(pstAppToOmMsg->aucPara));
    }
    else if(APP_OM_READ_SD_CLUSTER_REQ == pstAppToOmMsg->usPrimId)
    {
        OM_SDReadCluster(*((VOS_UINT32 *)pstAppToOmMsg->aucPara));
    }
    else
    {
        /* do nothing */
    }

    return;
}

VOS_VOID OM_PrintfSDError(VOS_VOID)
{
    vos_printf("\r\nThe SD Error Type is:       %d", g_ulReadSDErrType);

    vos_printf("\r\nWrite To DRV Total Block:   %d", g_stOmSDDebugInfo.ulTatalBlock);

    vos_printf("\r\nWrite To SD Total Over Num: %d", g_stOmSDDebugInfo.ulOverNum);

    vos_printf("\r\nWrite To SD  Length :       %d", g_stOmSDDebugInfo.ulDataLenth);

    vos_printf("\r\nRemain Length:              %d", g_stOmSDDebugInfo.ulRemainLenth);

    vos_printf("\r\nRead Head Err Lost Length:  %d", g_stOmSDDebugInfo.ulReadHeadErrLenth);
}

#if (VOS_LINUX == VOS_OS_VER)

VOS_UINT32 OM_FSFlushCfgFile(VOS_VOID)
{
    VOS_INT                             lCfgFile;
    VOS_INT                             lReturnLen;
    VOS_UINT32                          sd_fs = 0;

    sd_fs = SD_FS_GETFS();
    SD_FS_SETFS(KERNEL_DS);

    lCfgFile = SD_FS_OPEN(g_acFSLogCfgPath, O_CREAT|O_TRUNC|O_RDWR, OM_SD_FILE_MODE);

    if (lCfgFile < 0)
    {
        SD_FS_SETFS(sd_fs);
        return VOS_ERR;
    }

    lReturnLen = SD_FS_WRITE(lCfgFile, (VOS_CHAR *)&g_stFSCfgFileInfo, sizeof(OM_FLASH_CFG_INFO_STRU));

    SD_FS_CLOSE(lCfgFile);

    SD_FS_SYNC();

    SD_FS_SETFS(sd_fs);

    if (sizeof(OM_FLASH_CFG_INFO_STRU) != lReturnLen)
    {
        g_stFSLogFileInfo.ulErrLog  = LOG_OPERATION_WRITE_FILE_FAIL;

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 OM_FSInitCfgFile(VOS_VOID)
{
    VOS_INT                             lCfgFile;
    VOS_INT                             lReturnLen;
    VOS_UINT32                          sd_fs = 0;

    sd_fs = SD_FS_GETFS();
    SD_FS_SETFS(KERNEL_DS);

    /* ��Config�ļ� */
    lCfgFile = SD_FS_OPEN(g_acFSLogCfgPath, O_RDONLY, OM_SD_FILE_MODE);

    /* �ļ������� */
    if (lCfgFile < 0)
    {
        /* �ж�LOGĿ¼�Ƿ��Ѿ����� */
        if (VOS_OK != SD_FS_ACCESS(g_acFSLogDir, 0))
        {
            /* ���Ŀ¼�������򴴽�LOGĿ¼ */
            if(SD_FS_MKDIR(g_acFSLogDir, 0) < 0)
            {
                SD_FS_SETFS(sd_fs);
                return VOS_ERR;
            }
        }

        /* ��������ļ������ڣ��򴴽����ļ�����ʼ������ */
        lCfgFile = SD_FS_OPEN(g_acFSLogCfgPath, O_CREAT|O_TRUNC|O_RDWR, OM_SD_FILE_MODE);

        if (lCfgFile < 0)
        {
            SD_FS_SETFS(sd_fs);
            return VOS_ERR;
        }

        lReturnLen = SD_FS_WRITE(lCfgFile, (VOS_CHAR *)&g_stFSCfgFileInfo, sizeof(OM_FLASH_CFG_INFO_STRU));
    }
    else
    {
        lReturnLen = SD_FS_READ(lCfgFile, (VOS_CHAR *)&g_stFSCfgFileInfo, sizeof(OM_FLASH_CFG_INFO_STRU));
    }

    SD_FS_CLOSE(lCfgFile);

    if (sizeof(OM_FLASH_CFG_INFO_STRU) != lReturnLen)
    {
        SD_FS_SETFS(sd_fs);
        return VOS_ERR;
    }

    SD_FS_SETFS(sd_fs);
    return VOS_OK;
}


VOS_UINT32 OM_FSCheckSpace(VOS_VOID)
{
    VOS_CHAR                            acFilePath[OM_SD_LOG_PATH_MAX_LENGTH] = {0};
    VOS_UINT32                          sd_fs = 0;

    /* �Ƚϵ�ǰ�ļ��洢�Ƿ�ﵽ���� */
    if ((g_stFSCfgFileInfo.ulFileMaxId - g_stFSCfgFileInfo.ulFileMinId) < g_stFlashLogCfg.ulGULogFileSize)
    {
        return VOS_OK;
    }

    sd_fs = SD_FS_GETFS();
    SD_FS_SETFS(KERNEL_DS);

    /* ɾ�����ļ��Ա�֤�ռ���� */
    while (g_stFSCfgFileInfo.ulFileMinId < g_stFSCfgFileInfo.ulFileMaxId)
    {
        VOS_sprintf((VOS_CHAR *)acFilePath, "%s_%04d.%s",
            g_stFSLogFileInfo.acName,
            g_stFSCfgFileInfo.ulFileMinId,
            g_acFSLogType);

        g_stFSCfgFileInfo.ulFileMinId++;

        SD_FS_RMFILE(acFilePath);

        if ((g_stFSCfgFileInfo.ulFileMaxId - g_stFSCfgFileInfo.ulFileMinId) < g_stFlashLogCfg.ulGULogFileSize)
        {
            SD_FS_SETFS(sd_fs);

            OM_FSFlushCfgFile();

            return VOS_OK;
        }
    }

    SD_FS_SETFS(sd_fs);

    OM_FSFlushCfgFile();

    return VOS_ERR;
}

#if (FEATURE_ON == FEATURE_COMPRESS_WRITE_LOG_FILE)

VOS_UINT32 OM_AddHeadInfoToFile(OM_UCMX_HEAD_INFO_STRU *pstOmUcmxHeadInfo)
{
    pstOmUcmxHeadInfo->usFileTag         = UCMX_FILE_HEAD_TAG;
    pstOmUcmxHeadInfo->ucFileVersion     = 1;
    pstOmUcmxHeadInfo->ucHeadSegNum      = 1;                               /* �ļ�ͷ���� */
    pstOmUcmxHeadInfo->ulSn              = g_stFSCfgFileInfo.ulFileMaxId;   /* �ļ�����ʱ���ļ���� */

    pstOmUcmxHeadInfo->enSEGType3        = OM_LOG_HEAD_SEG_UE_INFO;
    pstOmUcmxHeadInfo->ucHeadLength3     = 48;
    /* IMEI �� */
    if (VOS_OK != NV_Read(en_NV_Item_IMEI, pstOmUcmxHeadInfo->aucImei, OM_IMEI_NV_LEN))
    {
        vos_printf("OM_AddHeadInfoToFile: read Imei fail");
        return VOS_ERR;
    }

    /* �汾���� */
#if (VOS_WIN32 == VOS_OS_VER)
    pstOmUcmxHeadInfo->ucUEBoardType = OM_WIN32_PLATFORM;
#else
#ifdef BOARD_ASIC
        pstOmUcmxHeadInfo->ucUEBoardType = OM_ASIC_PLATFORM;
#else
        pstOmUcmxHeadInfo->ucUEBoardType = OM_FPGA_PLATFORM;
#endif
#endif  /*(VOS_WIN32 == VOS_OS_VER)*/

    /* ���汾���� 30 �ַ�+ \0 */
    VOS_MemCpy((VOS_CHAR*)pstOmUcmxHeadInfo->aucUEVersion, PRODUCT_CFG_FULL_VERSION_STR, (VER_MAX_LENGTH+1));

    return VOS_OK;

}
#endif


VOS_UINT32 OM_FSCheckFileIsFull(VOS_UINT32 ulLength)
{
    VOS_CHAR                            acFilePath[OM_SD_LOG_PATH_MAX_LENGTH] = {0};
    VOS_INT                             lTempHandle;
    VOS_UINT32                          sd_fs = 0;

#if (FEATURE_ON == FEATURE_COMPRESS_WRITE_LOG_FILE)
    OM_UCMX_HEAD_INFO_STRU              stOmUcmxHeadInfo;
    VOS_INT                             lReturnLen;
#endif

    /*�жϵ�ǰд�볤���Ƿ�ʹ��LOG���*/
    if (g_stFSLogFileInfo.ulFileMaxSize >=
            ((VOS_INT)ulLength + g_stFSLogFileInfo.ulFileSize))
    {
        return VOS_OK;
    }

    sd_fs = SD_FS_GETFS();
    SD_FS_SETFS(KERNEL_DS);

    /* �ر�����д���ļ� */
    SD_FS_CLOSE(g_stFSLogFileInfo.lFileHandle);

    if (VOS_OK != OM_FSCheckSpace())
    {
        SD_FS_SETFS(sd_fs);

        return VOS_ERR;
    }

    VOS_sprintf(acFilePath, "%s_%04d.%s",
                g_stFSLogFileInfo.acName,
                g_stFSCfgFileInfo.ulFileMaxId,
                g_acFSLogType);

    /*��LOG�ļ������ҳ�ʼ��Ϊ�գ�������ļ������ڣ��򴴽����ļ�*/
    lTempHandle = SD_FS_OPEN(acFilePath, O_CREAT|O_RDWR|O_TRUNC, OM_SD_FILE_MODE);

    /*��ʧ��*/
    if (lTempHandle < 0)
    {
        g_stFSLogFileInfo.bIsWritten    = VOS_FALSE;
        g_stFSLogFileInfo.lFileHandle   = -1;

        g_stFSLogFileInfo.ulErrLog  = LOG_OPERATION_OPEN_FILE_FAIL;

        SD_FS_SETFS(sd_fs);

        return VOS_ERR;
    }

    g_stFSLogFileInfo.lFileHandle   = lTempHandle;
    g_stFSLogFileInfo.ulFileSize    = 0;

#if (FEATURE_ON == FEATURE_COMPRESS_WRITE_LOG_FILE)
    /* LOGѹ���㷨��������Ҫ����ͷ�ļ���Ϣ */
    if(VOS_OK != OM_AddHeadInfoToFile(&stOmUcmxHeadInfo))
    {
        return VOS_ERR;
    }

    /*д��LOG����*/
    lReturnLen = SD_FS_WRITE(g_stFSLogFileInfo.lFileHandle, (VOS_CHAR*)&stOmUcmxHeadInfo, sizeof(stOmUcmxHeadInfo));

    if (lReturnLen != sizeof(stOmUcmxHeadInfo))
    {
        g_stFSLogFileInfo.ulWriteFailNum++;
        g_stFSLogFileInfo.ulErrLog  = LOG_OPERATION_WRITE_FILE_FAIL;
        SD_FS_SETFS(sd_fs);

        return VOS_ERR;
    }

    SD_FS_FILE_SYNC(g_stFSLogFileInfo.lFileHandle);
#endif

    g_stFSCfgFileInfo.ulFileMaxId++;

    SD_FS_SETFS(sd_fs);

    OM_FSFlushCfgFile();

    return VOS_OK;
}


VOS_UINT32 OM_FSCheckWriteCount(VOS_VOID)
{
    VOS_CHAR                            acFilePath[OM_SD_LOG_PATH_MAX_LENGTH] = {0};
    VOS_INT                             lTempHandle;
    VOS_UINT32                          sd_fs = 0;

    /* ��������ʱ�����ļ��رգ������´��ļ� */
    if (0 != g_stFSLogFileInfo.ulRemainCount)
    {
        return VOS_OK;
    }

    sd_fs = SD_FS_GETFS();
    SD_FS_SETFS(KERNEL_DS);

    SD_FS_CLOSE(g_stFSLogFileInfo.lFileHandle);

    VOS_sprintf(acFilePath, "%s_%04d",
                g_stFSLogFileInfo.acName,
                g_stFSCfgFileInfo.ulFileMaxId - 1);

    lTempHandle = SD_FS_OPEN(acFilePath,O_CREAT|O_RDWR|O_APPEND, OM_SD_FILE_MODE);

    /*��ʧ��*/
    if (lTempHandle < 0)
    {
        g_stFSLogFileInfo.bIsWritten    = VOS_FALSE;
        g_stFSLogFileInfo.lFileHandle   = -1;

        g_stFSLogFileInfo.ulErrLog  = LOG_OPERATION_OPEN_FILE_FAIL;

        SD_FS_SETFS(sd_fs);

        return VOS_ERR;
    }

    g_stFSLogFileInfo.lFileHandle     = lTempHandle;
    g_stFSLogFileInfo.ulRemainCount   = g_ulLogMaxCout;

    SD_FS_SETFS(sd_fs);
    return VOS_OK;
}


VOS_UINT32 OM_FSWriteLogFile(VOS_CHAR *pcLogData, VOS_UINT32 ulLength)
{
    VOS_INT                             lReturnLen;
    VOS_UINT32                          sd_fs = 0;

    /*�жϵ�ǰ�ļ��Ƿ��д*/
    if (VOS_FALSE == g_stFSLogFileInfo.bIsWritten)
    {
        return VOS_ERR;
    }

    /*�ж�д�볤���Ƿ񳬹����ļ�����󳤶�*/
    if (g_stFSLogFileInfo.ulFileMaxSize < ulLength)
    {
        g_stFSLogFileInfo.ulErrLog  = LOG_OPERATION_LENGTH_TOOBIG;
        return VOS_ERR;
    }

    if (VOS_OK != OM_FSCheckFileIsFull(ulLength))
    {
        return VOS_ERR;
    }

    if (VOS_OK != OM_FSCheckWriteCount())
    {
        return VOS_ERR;
    }

    sd_fs = SD_FS_GETFS();
    SD_FS_SETFS(KERNEL_DS);

    /*д��LOG����*/
    lReturnLen = SD_FS_WRITE(g_stFSLogFileInfo.lFileHandle, pcLogData, ulLength);

    if (ulLength != lReturnLen)
    {
        g_stFSLogFileInfo.ulWriteFailNum++;
        g_stFSLogFileInfo.ulErrLog  = LOG_OPERATION_WRITE_FILE_FAIL;

        SD_FS_SETFS(sd_fs);

        return VOS_ERR;
    }

    /* ����LOG�ļ�д�Ĵ�����ʵ�ʴ�С */
    g_stFSLogFileInfo.ulFileSize += ulLength;

    SD_FS_FILE_SYNC(g_stFSLogFileInfo.lFileHandle);
    SD_FS_SETFS(sd_fs);

    return VOS_OK;
}

#if (FEATURE_ON == FEATURE_COMPRESS_WRITE_LOG_FILE)

VOS_UINT32 OM_CompressRcvLog(VOS_CHAR *pcLogData, VOS_UINT32 ulLength)
{
    VOS_UINT32                          ulCompressDataLen = 0;
    VOS_UINT32                          ulTempPackLen     = 0; /* ��ʱ���δѹ�����ݳ��� */
    VOS_UINT32                          ulRemainLen       = 0; /* �������� */
    VOS_UINT32                          ulNextPackLen     = 0; /* ������һ��ѹ������ */
    VOS_UINT32                          ulIndexMax        = 0;
    VOS_UINT32                          ulIndex           = 0;

    g_stCompressDebugLog.ulRcvNum++;
    g_stCompressDebugLog.ulRcvLen += ulLength;

    /* �ָ���� */
    g_stCompressData.ulDataTag    = UCMX_DATA_TAG;

    /* ÿ��ѹ���ݴ�С�̶����������ѹ���� */
    ulRemainLen = ((ulLength + g_ulPackLen) % OM_MAX_PACK_DATA_LEN);
    ulIndexMax  = (ulLength + g_ulPackLen)/OM_MAX_PACK_DATA_LEN;

    for (ulIndex=0; ulIndex<ulIndexMax; ulIndex++)
    {
        VOS_MemCpy(g_aucPackData + g_ulPackLen, pcLogData + ((ulIndex * OM_MAX_PACK_DATA_LEN) - ulTempPackLen),
                   (OM_MAX_PACK_DATA_LEN - g_ulPackLen));

        if (0 == ulIndex)
        {
            /* �Ѿ�������ݳ��� */
            ulTempPackLen = g_ulPackLen;
        }

        ulCompressDataLen = fastlz_compress(g_aucPackData, OM_MAX_PACK_DATA_LEN, g_stCompressData.aucData);

        g_stCompressDebugLog.ulCompressLen += ulCompressDataLen;

        g_stCompressData.ulDataLength = ulCompressDataLen;
        OM_FSWriteLogFile((VOS_CHAR *)&g_stCompressData, (ulCompressDataLen + (2*sizeof(VOS_UINT32))));

        /* ����������� */
        g_ulPackLen   = 0;

    }

    /* ������һ��ѹ�� */
    ulNextPackLen = (ulRemainLen - g_ulPackLen);
    VOS_MemCpy(g_aucPackData + g_ulPackLen, pcLogData + (ulLength - ulNextPackLen), ulNextPackLen);
    g_ulPackLen += ulNextPackLen;

    return VOS_OK;

}
#endif


VOS_UINT32 OM_FSWriteLogProc(VOS_CHAR *pcLogData, VOS_UINT32 ulLength)
{
#if (FEATURE_ON == FEATURE_COMPRESS_WRITE_LOG_FILE)
    return OM_CompressRcvLog(pcLogData, ulLength);
#else
    return OM_FSWriteLogFile(pcLogData, ulLength);
#endif
}


VOS_UINT32 OM_FSStartLog(VOS_VOID)
{
    /*���GU���ñ���ռ�����Ϊ0������Ҫ���б���*/
    if (0 == g_stFlashLogCfg.ulGULogFileSize)
    {
        return VOS_OK;
    }

    if (VOS_OK != OM_FSInitCfgFile())
    {
        return VOS_ERR;
    }

    if (VOS_OK != OM_FSCheckSpace())
    {
        return VOS_ERR;
    }

    g_stFSLogFileInfo.bIsWritten    = VOS_TRUE;
    g_stFSLogFileInfo.lFileHandle   = -1;
    g_stFSLogFileInfo.ulRemainCount = g_ulLogMaxCout;
    g_stFSLogFileInfo.ulFileSize    = OM_FLASH_DEFAULT_FILE_SIZE;
    g_stFSLogFileInfo.ulFileMaxSize = OM_FLASH_DEFAULT_FILE_SIZE;

    return VOS_OK;
}


VOS_UINT32 OM_FSInitLogFile(VOS_VOID)
{
    /*��ȡFlash����trace����*/
    if(NV_OK != NV_Read(en_NV_Item_FLASH_Log_Record_CFG, &g_stFlashLogCfg, sizeof(NV_FLASH_LOG_RECORD_STRU)))
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "OM_FSInitLogFile:Read NV Config fail!");

        return VOS_OK;
    }

    g_stFSLogFileInfo.bIsWritten    = VOS_FALSE;

    /*���GU���ñ���ռ�����Ϊ0������Ҫ���б���*/
    if (0 == g_stFlashLogCfg.ulGULogFileSize)
    {
        return VOS_OK;
    }

    CPM_PhySendReg(CPM_FS_PORT, (CPM_FUNC)OM_FSWriteLogProc);

    if (VOS_OK != OM_FSStartLog())
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
#endif


VOS_UINT32 OM_LogFileInit(VOS_VOID)
{
    OM_CHANNLE_PORT_CFG_STRU            stPortCfg;

    /*��ȡSD Log��NV�е�����*/
    if(NV_OK != NV_Read(en_NV_Item_Om_Port_Type, &stPortCfg, sizeof(OM_CHANNLE_PORT_CFG_STRU)))
    {
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "OM_LogFileInit:Read NV Config fail!");

        return VOS_OK;
    }

    stPortCfg.enPortNum += CPM_APP_PORT;

    /*��ȡSD Log��NV�е�����Ϊ1��ʱ���ʹ��*/
    if(CPM_SD_PORT == stPortCfg.enPortNum)
    {
        OM_SDInit();

        return VOS_OK;
    }
#if (VOS_OS_VER == VOS_LINUX)
    else if (CPM_FS_PORT == stPortCfg.enPortNum)
    {
        OM_FSInitLogFile();

        return VOS_OK;
    }
#endif

    return VOS_OK;
}

#if (VOS_LINUX == VOS_OS_VER)

VOS_VOID OM_FSShowInfo(VOS_VOID)
{
    vos_printf("File can write ===== %d\r\n", g_stFSLogFileInfo.bIsWritten);
    vos_printf("File Handle ======== %d\r\n", g_stFSLogFileInfo.lFileHandle);
    vos_printf("File RemainCount === %d\r\n", g_stFSLogFileInfo.ulRemainCount);
    vos_printf("File current Size == %d\r\n", g_stFSLogFileInfo.ulFileSize);
    vos_printf("File Max Size ====== %d\r\n", g_stFSLogFileInfo.ulFileMaxSize);
    vos_printf("File Error Info ==== %d\r\n", g_stFSLogFileInfo.ulErrLog);
    vos_printf("File Write Error === %d\r\n", g_stFSLogFileInfo.ulWriteFailNum);

    vos_printf("File Min ID ======== %d\r\n", g_stFSCfgFileInfo.ulFileMinId);
    vos_printf("File Max ID ======== %d\r\n", g_stFSCfgFileInfo.ulFileMaxId);

#if (FEATURE_ON == FEATURE_COMPRESS_WRITE_LOG_FILE)
    vos_printf("Rcv Log len   = %d\r\n", g_stCompressDebugLog.ulRcvLen);
    vos_printf("Rcv Log Num   = %d\r\n", g_stCompressDebugLog.ulRcvNum);
    vos_printf("Compress Log len= %d\r\n", g_stCompressDebugLog.ulCompressLen);
    vos_printf("pack Log len= %d\r\n", g_ulPackLen);

#endif
    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

