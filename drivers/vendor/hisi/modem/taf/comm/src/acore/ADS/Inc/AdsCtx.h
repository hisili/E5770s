


#ifndef __ADSCTX_H__
#define __ADSCTX_H__

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "PsTypeDef.h"
#include "PsLib.h"
#include "pslog.h"
#include "AdsInterface.h"
#include "AdsDeviceInterface.h"
#include "CdsAdsInterface.h"
#include "AdsNdInterface.h"
#include "AdsTimerMgmt.h"
#include "AdsLog.h"
#include "DrvInterface.h"
#include "BSP_IPF.h"
#include "NVIM_Interface.h"
#include "AdsFcInterface.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#if (VOS_OS_VER == VOS_LINUX)
#include <asm/dma-mapping.h>
#else
#include "LinuxStub.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ADSʵ��������Modem��������һ�� */
#define ADS_INSTANCE_MAX_NUM            (MODEM_ID_BUTT)

/* ADSʵ��0������ֵ */
#define ADS_INSTANCE_INDEX_0            (0)

/* ADSʵ��0������ֵ */
#define ADS_INSTANCE_INDEX_1            (1)

/*���»�����е����ֵ */
#define ADS_RAB_NUM_MAX                 (11)

/* ��ǰ������Ķ�����5��15, �����һ��5��ƫ���� */
#define ADS_RAB_ID_OFFSET               (5)

/* Rab Id����Сֵ */
#define ADS_RAB_ID_MIN                  (5)

/* Rab Id�����ֵ */
#define ADS_RAB_ID_MAX                  (15)

/* Rab Id����Чֵ */
#define ADS_RAB_ID_INVALID              (0xFF)

/* Ϊ�˱���Ƶ������IPF�жϣ���Ҫ�����ܰ����ƣ��ܰ��������� */
#define ADS_UL_SEND_DATA_NUM_THREDHOLD  (32)

/* �����AD��Ҫƫ��14��ΪIPF RD��Ŀ�ĵ�ַ��14ΪMACͷ�ĳ��� */
#define ADS_DL_AD_DATA_PTR_OFFSET       (14)

/* Ĭ�ϵ����ȼ���Ȩ�� */
#define ADS_UL_DEFAULT_PRI_WEIGHTED_NUM (0x01)

#define ADS_GET_CURR_KERNEL_TIME()      (jiffies)
#define ADS_TIME_AFTER_EQ(a, b)         time_after_eq((a), (b))

/* ADS ADQ�ĸ��� */
#define ADS_DL_ADQ_MAX_NUM              (2)

/*����ADQ�ձ�����ʱ������ֵ����������AD�������ڸ�ֵʱ������������ʱ��*/
#define ADS_IPF_DLAD_START_TMR_THRESHOLD (IPF_DLAD0_DESC_SIZE - 6)

/* ADS_UL_SendPacket��ADS_DL_RegDlDataCallback��rabidΪ��չ��rabid��
   ��2bit��ΪMODEM ID����6bit��ΪRAB ID��������չ��RABID��ȡMODEM ID */
#define ADS_GET_MODEM_ID_FROM_EX_RAB_ID(i)   ((i >> 6) & 0x03)

#define ADS_GET_RAB_ID_FROM_EX_RAB_ID(i)     (i & 0x3F)

#define ADS_BUILD_EX_RAB_ID(i, j)            (((i << 6) & 0xC0) | (j & 0x3F))

/*******************************�����¼� Begin*******************************/
/* ADS���������¼� */
#define ADS_UL_EVENT_BASE               (0x00000000)

#define ADS_UL_EVENT_DATA_PROC          (ADS_UL_EVENT_BASE | 0x0001)

/* ADS���������¼� */
#define ADS_DL_EVENT_BASE               (0x00000000)

#define ADS_DL_EVENT_IPF_RD_INT         (ADS_DL_EVENT_BASE | 0x0001)

/* Added by l60609 for DSDA Phase II, 2012-12-20, Begin */
#define ADS_DL_EVENT_IPF_ADQ_EMPTY_INT  (ADS_DL_EVENT_BASE | 0x0002)
/* Added by l60609 for DSDA Phase II, 2012-12-20, End */
/*******************************�����¼� End*******************************/

/*******************************����ͳ�� Begin*******************************/
/* ���õ�ǰ�������� */
#define ADS_SET_CURRENT_UL_RATE(i, n)           (g_stAdsCtx.astAdsSpecCtx[i].stAdsStatsInfoCtx.stULDataStats.ulULCurDataRate = n)

/* ���õ�ǰ�������� */
#define ADS_SET_CURRENT_DL_RATE(i, n)           (g_stAdsCtx.astAdsSpecCtx[i].stAdsStatsInfoCtx.stDLDataStats.ulDLCurDataRate = n)

/* ͳ�������������յ����ĸ��� */
#define ADS_RECV_UL_PERIOD_PKT_NUM(i, n)        (g_stAdsCtx.astAdsSpecCtx[i].stAdsStatsInfoCtx.stULDataStats.ulULPeriodSndBytes += (n))

/* ͳ�������������յ����ĸ��� */
#define ADS_RECV_DL_PERIOD_PKT_NUM(i, n)        (g_stAdsCtx.astAdsSpecCtx[i].stAdsStatsInfoCtx.stDLDataStats.ulDLPeriodRcvBytes += (n))

/* ��ȡ�����������յ����ĸ��� */
#define ADS_GET_UL_PERIOD_PKT_NUM(i)            (g_stAdsCtx.astAdsSpecCtx[i].stAdsStatsInfoCtx.stULDataStats.ulULPeriodSndBytes)

/* ��ȡ�����������յ����ĸ��� */
#define ADS_GET_DL_PERIOD_PKT_NUM(i)            (g_stAdsCtx.astAdsSpecCtx[i].stAdsStatsInfoCtx.stDLDataStats.ulDLPeriodRcvBytes)

/* �������������յ����ĸ������� */
#define ADS_CLEAR_UL_PERIOD_PKT_NUM(i)          (g_stAdsCtx.astAdsSpecCtx[i].stAdsStatsInfoCtx.stULDataStats.ulULPeriodSndBytes = 0)

/* �������������յ����ĸ������� */
#define ADS_CLEAR_DL_PERIOD_PKT_NUM(i)          (g_stAdsCtx.astAdsSpecCtx[i].stAdsStatsInfoCtx.stDLDataStats.ulDLPeriodRcvBytes = 0)

/* ��ȡ����ͳ�ƶ�ʱ��ID */
#define ADS_GET_DSFLOW_TMR_ID(instance)         (TI_ADS_DSFLOW_STATS_0 + instance)
/*******************************����ͳ�� End*******************************/


/*******************************���� Begin*******************************/
/* ��ȡADS����ʵ���ַ */
#define ADS_UL_GET_CTX_PTR(i)                      (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx))

/* ��ȡ���ж���ָ�� */
#define ADS_UL_GET_QUEUE_LINK_PTR(i, j)            (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].pstAdsUlLink)

/* ��ȡ���ж����� */
#define ADS_UL_GET_QUEUE_LINK_SPINLOCK(i, j)       (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].stSpinLock))

/* ��ȡADS����BD���ò�����ַ */
#define ADS_UL_GET_BD_CFG_PARA_PTR(index)          (&(g_stAdsCtx.stAdsIpfCtx.astIpfUlBdBuff[index]))

/* ��ȡADS���з��ͱ�����ʱ��ʱ�� */
#define ADS_UL_GET_PROTECT_TIMER_LEN()             (g_stAdsCtx.stAdsIpfCtx.ulProtectTmrLen)

/* ��ȡRAB�Ƿ��������������ݵı�־λ */
#define ADS_UL_GET_RAB_SND_PERMIT_FLAG(i, j)       (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].ucRabSndPermitFlg)

/* ����RAB�Ƿ��������������ݵı�־λ */
#define ADS_UL_SET_RAB_SND_PERMIT_FLAG(i, j, n)    (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].ucRabSndPermitFlg = n)

/* ��ȡMODEM�Ƿ��������������ݵı�־λ */
#define ADS_UL_GET_MODEM_SND_PERMIT_FLAG(i)        (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.ucModemSndPermitFlg)

/* ����MODEM�Ƿ��������������ݵı�־λ */
#define ADS_UL_SET_MODEM_SND_PERMIT_FLAG(i, n)     (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.ucModemSndPermitFlg = n)

/* ��ȡ�����Ƿ����ڷ��͵ı�־λ */
#define ADS_UL_GET_SENDING_FLAG()                  (g_stAdsCtx.stAdsIpfCtx.ucSendingFlg)

/* ���������Ƿ����ڷ��͵ı�־λ */
#define ADS_UL_SET_SENDING_FLAG(flg)               (g_stAdsCtx.stAdsIpfCtx.ucSendingFlg = flg)

/* ��ȡ�洢���е����� */
#define ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)          (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.aucPrioIndex[j])

/* ��ȡ���ж��е������ȼ�*/
#define ADS_UL_GET_QUEUE_QCI(i, j)                 (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].enPrio)

/* ��ȡ���ж�����Ϣ */
#define ADS_UL_GET_QUEUE_LINK_INFO(i, j)           (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].pstAdsUlLink)

/* ��ȡ���ж���һ����Ȩ����Χ�ڼ�¼�ķ��͸��� */
#define ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(i, j)    (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum)

/* �������ж���һ����Ȩ����Χ�ڼ�¼�ķ��͸��� */
#define ADS_UL_SET_RECORD_NUM_IN_WEIGHTED(i, j, n) (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum += n)

/* ������ж���һ����Ȩ����Χ�ڼ�¼�ķ��͸��� */
#define ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(i, j)    (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[ADS_UL_GET_PRIO_QUEUE_INDEX(i, j)].usRecordNum = 0)

/* ��ȡ���ж������ȼ��ļ�Ȩ�� */
#define ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(i, j)    (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.stQueuePriNv.ausPriWeightedNum[ADS_UL_GET_QUEUE_QCI(i, j)])

/* ��ȡ���ж������ݰ�������*/
#define ADS_UL_GET_QUEUE_PKT_TYPE(InstanceIndex, RabId) \
        (g_stAdsCtx.astAdsSpecCtx[InstanceIndex].stAdsUlCtx.astAdsUlQueue[RabId].enPktType)

/*******************************���� End*******************************/

/* Added by l60609 for AP������Ŀ ��2012-08-31 Begin */
#if(FEATURE_OFF == FEATURE_SKB_EXP)
/* ����IPF�ڴ��ͷŶ����׵�ַ */
#define ADS_UL_IPF_SRCMEM_FREE_QUE()         (&(g_stAdsCtx.stAdsIpfCtx.stUlSrcMemFreeQue))

/* IPF����Դ�ڴ��ͷ�QUEUE�������޳�Ϊ����IPF BD��������2�� */
#define ADS_UL_IPF_SRCMEM_FREE_QUE_SIZE      (2 * IPF_ULBD_DESC_SIZE)

/* ͨ������ADS���ж��г��ȣ�����A��ϵͳ�ڴ棬�����޳���ʼ��ֵ */
#define ADS_UL_MAX_QUEUE_LENGTH              (512)

/* ��ȡ���ж����޳� */
#define ADS_UL_GET_MAX_QUEUE_LENGTH(i)       (g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.ulUlMaxQueueLength)

/* ��ȡADS����IPF AD BUFFER��ַ */
#define ADS_DL_GET_IPF_AD_BUFFER_PTR(i, j)   (&(g_stAdsCtx.stAdsIpfCtx.astIpfDlAdBuff[i][j]))

#endif
/* Added by l60609 for AP������Ŀ ��2012-08-31 End */

/*******************************���� Begin*******************************/
/* ��ȡADS����ʵ���ַ */
#define ADS_DL_GET_CTX_PTR(i)                   (&(g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx))

/* ��ȡADS����IPF RD BUFFER��ַ */
#define ADS_DL_GET_IPF_RD_BUFFER_PTR(index)     (&(g_stAdsCtx.stAdsIpfCtx.astIpfDlRdBuff[index]))

/* ��ȡADS����RAB INFO��ַ */
#define ADS_DL_GET_RAB_INFO_PTR(i, rabid)       (&(ADS_DL_GET_CTX_PTR(i)->astAdsDlRabInfo[rabid - ADS_RAB_ID_OFFSET]))

/* ��ȡADS����RAB��Ӧ�����ݰ����� */
#define ADS_DL_GET_PKT_TYPE(instance, rabid)    (ADS_DL_GET_CTX_PTR(instance)->astAdsDlRabInfo[rabid - ADS_RAB_ID_OFFSET].enPktType)

/* ��ȡADS�������ݻص�����ָ�� */
#define ADS_DL_GET_DATA_CALLBACK_FUNC(i, j)     (ADS_DL_GET_RAB_INFO_PTR(i, j)->pRcvDlDataFunc)

/* get/set the last data buff ptr */
#define ADS_DL_GET_LST_DATA_PTR(mid,rabid)          (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->pstLstPkt)
#define ADS_DL_SET_LST_DATA_PTR(mid,rabid, psPara)  (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->pstLstPkt = (psPara))
/* get/set the last data type */
#define ADS_DL_GET_LST_DATA_IPTYPE(mid,rabid)           (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->enIpType)
#define ADS_DL_SET_LST_DATA_IPTYPE(mid,rabid,usType)   (ADS_DL_GET_RAB_INFO_PTR(mid,rabid)->enIpType = (usType))

#define ADS_DL_GET_FILTER_DATA_CALLBACK_FUNC(ucInstanceIndex, ucRabId) \
            (ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRabId)->pRcvDlFilterDataFunc)

/* ��ȡADS�������ز�����Ϣ��ַ */
#define ADS_DL_GET_FC_ASSEM_INFO_PTR(i)         (&(ADS_DL_GET_CTX_PTR(i)->stFcAssemInfo))

/* ��ȡADS��������������������ص�����ָ�� */
#define ADS_DL_GET_FC_ASSEM_TUNE_FUNC(i)        (ADS_DL_GET_FC_ASSEM_INFO_PTR(i)->pFcAssemTuneFunc)
/*******************************���� End*******************************/

/*******************************IPF Begin*******************************/
/* ��ȡIPF��ص������� */
#define ADS_GET_IPF_CTX_PTR()                    (&(g_stAdsCtx.stAdsIpfCtx))
/*******************************IPF End*******************************/

/* ���RABIID��Ч�� */
#define ADS_IS_VALID_RABID(ucRabId)\
    (((ucRabId) >= ADS_RAB_ID_MIN) && ((ucRabId) <= ADS_RAB_ID_MAX))

#define ADS_UL_IS_REACH_THRESHOLD(ulAllUlQueueDataNum, ucSendingFlg) \
    ((0 != ulAllUlQueueDataNum) && (0 == (ulAllUlQueueDataNum & 0x1F)) && (VOS_FALSE == ucSendingFlg))

#if (VOS_OS_VER == VOS_LINUX)
#if(FEATURE_OFF == FEATURE_SKB_EXP)
#ifdef BSP_CONFIG_HI3630
#define ADS_CACHE_FLUSH(data, len)      dma_map_single(0, data, len, DMA_TO_DEVICE)
#define ADS_CACHE_INVALIDATE(data, len) dma_map_single(0, data, len, DMA_FROM_DEVICE)
#else
#define ADS_CACHE_FLUSH(data, len)      __dma_single_cpu_to_dev(data, len, DMA_TO_DEVICE)
#define ADS_CACHE_INVALIDATE(data, len) __dma_single_dev_to_cpu(data, len, DMA_FROM_DEVICE)
#endif
#else
#define ADS_CACHE_FLUSH(data, len)      __dma_single_cpu_to_dev_nocheck(data, len, DMA_TO_DEVICE)
#define ADS_CACHE_INVALIDATE(data, len) __dma_single_dev_to_cpu_nocheck(data, len, DMA_FROM_DEVICE)
#endif
#else
#define ADS_CACHE_FLUSH(data, len)      (vos_printf("%c, %d\n", data, len))
#define ADS_CACHE_INVALIDATE(data, len) (vos_printf("%c, %d\n", data, len))
#endif

#if !defined(ADS_ARRAY_SIZE)
#define ADS_ARRAY_SIZE(a)               (sizeof((a)) / sizeof((a[0])))
#endif


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/



typedef struct
{
    IMM_ZC_HEAD_STRU                   *pstAdsUlLink;                           /* Rab Id��Ӧ�Ķ��� */
    VOS_UINT8                           ucIsQueueValid;                         /* �����Ƿ񼤻VOS_TRUE:���VOS_FALSE:δ���� */
    ADS_QCI_TYPE_ENUM_UINT8             enPrio;                                 /* �������ȼ� */
    VOS_UINT16                          usRecordNum;                            /* ��¼��һ����Ȩ����Χ�ڷ������ݵĸ��� */
    /* Added by l60609 for AP������Ŀ ��2012-09-10 Begin */
    VOS_SPINLOCK                        stSpinLock;                             /* ������ */
    /* Added by l60609 for AP������Ŀ ��2012-09-10 End */
    /* Added by l60609 for DSDA Phase II, 2012-11-27, Begin */
    VOS_UINT8                           ucRabSndPermitFlg;                      /* ��RAB�����Ƿ������ͣ�Ĭ�������� ,VOS_TRUE */

    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;                              /* ���ݰ����� */

    VOS_UINT8                           aucRsv[2];
    /* Added by l60609 for DSDA Phase II, 2012-11-27, End */
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL)
    VOS_UINT32                          ulIdMark;
#endif
}ADS_UL_QUEUE_STRU;


typedef struct
{
    VOS_UINT8                           ucRabId;                                /* Rab Id */
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;                              /* ���ݰ����� */
    VOS_UINT8                           aucRsv[2];                              /* ���� */
    RCV_DL_DATA_FUNC                    pRcvDlDataFunc;                         /* ��Ӧ�����н��պ��� */
    RCV_DL_DATA_FUNC                    pRcvDlFilterDataFunc;                   /* ��Ӧ�����й��˽��պ��� */
    IMM_ZC_STRU                        *pstLstPkt;
    ADS_PKT_TYPE_ENUM_UINT8             enIpType;
#if (FEATURE_ON == MBB_FEATURE_UNI_PS_CALL)
    VOS_UINT32                          ulIdMark;
#endif
}ADS_DL_RAB_INFO_STRU;


typedef struct
{
    VOS_UINT32              ulEnableMask;
    VOS_UINT32              ulFcActiveFlg;
    VOS_UINT32              ulTmrCnt;
    VOS_UINT32              ulRdCnt;
    VOS_UINT32              ulRateUpLev;
    VOS_UINT32              ulRateDownLev;
    VOS_UINT32              ulExpireTmrLen;
    ADS_DRV_ASSEM_FUNC      pFcAssemTuneFunc;
} ADS_DL_FC_ASSEM_STRU;


typedef struct
{
    /* Modified by l60609 for DSDA Phase II, 2012-11-22, Begin */
    ADS_DL_RAB_INFO_STRU                astAdsDlRabInfo[ADS_RAB_NUM_MAX];       /*����Rab��Ϣ */
    /* Modified by l60609 for DSDA Phase II, 2012-11-22, End */
    ADS_DL_FC_ASSEM_STRU                stFcAssemInfo;
} ADS_DL_CTX_STRU;


typedef struct
{
    /* Modified by l60609 for DSDA Phase II, 2012-11-22, Begin */
    ADS_UL_QUEUE_STRU                   astAdsUlQueue[ADS_RAB_ID_MAX + 1];      /* ���ж��й���ֻ��5-15 */
    VOS_UINT8                           aucPrioIndex[ADS_RAB_NUM_MAX];          /* �洢���ź����ȼ������ж��е����� */
    VOS_UINT8                           ucAdsUlCurIndex;                        /* ��¼��ǰ���ȵĶ��� */
    ADS_UL_QUEUE_SCHEDULER_PRI_NV_STRU  stQueuePriNv;                           /* ��NV�ж�ȡ�����ж������ȼ���Ӧ�ļ�Ȩ�� */
    VOS_UINT8                           ucModemSndPermitFlg;                    /* Modem�Ƿ������ͣ�Ĭ�������� ,VOS_TRUE */
    VOS_UINT8                           aucRsv[3];
    /* Added by l60609 for AP������Ŀ ��2012-08-31 Begin */
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    VOS_UINT32                          ulUlMaxQueueLength;                     /* ���ж����޳� */
#endif
    /* Added by l60609 for AP������Ŀ ��2012-08-31 End */
    /* Modified by l60609 for DSDA Phase II, 2012-11-22, End */
}ADS_UL_CTX_STRU;


typedef struct ADS_UL_DATA_STATS
{
    VOS_UINT32                          ulULCurDataRate;                        /* ��ǰ�������ʣ�����PDP�����2������ʣ�ȥ�������� */
    VOS_UINT32                          ulULPeriodSndBytes;                     /* һ������ͳ�������ڷ��͵�byte�� */
}ADS_UL_DATA_STATS_STRU;


typedef struct ADS_DL_DATA_STATS
{
    VOS_UINT32                          ulDLCurDataRate;                        /* ��ǰ�������ʣ�����PDP�����2������ʣ�ȥ�������� */
    VOS_UINT32                          ulDLPeriodRcvBytes;                     /* һ������ͳ���������յ���byte�� */
}ADS_DL_DATA_STATS_STRU;


typedef struct
{
    ADS_UL_DATA_STATS_STRU              stULDataStats;                          /* ADS��������ͳ�� */
    ADS_DL_DATA_STATS_STRU              stDLDataStats;                          /* ADS��������ͳ�� */
}ADS_STATS_INFO_CTX_STRU;

/* Modified by l60609 for DSDA Phase II, 2012-11-22, Begin */

typedef struct
{
    IPF_CONFIG_ULPARAM_S                astIpfUlBdBuff[IPF_ULBD_DESC_SIZE];     /* ����BD */
    IPF_RD_DESC_S                       astIpfDlRdBuff[IPF_DLRD_DESC_SIZE];     /* ����RD */
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    /* AD */
    IPF_AD_DESC_S                       astIpfDlAdBuff[ADS_DL_ADQ_MAX_NUM][IPF_DLAD0_DESC_SIZE];   /* ����AD0 */
    IMM_ZC_HEAD_STRU                    stUlSrcMemFreeQue;                      /* IPF�����ڴ��ͷ�BUFF */
#endif
    VOS_UINT32                          ulProtectTmrLen;
    VOS_UINT8                           ucSendingFlg;                           /* ���ڷ��ͱ�־ */
    VOS_UINT8                           aucRsv[3];
}ADS_IPF_CTX_STRU;


typedef struct
{
    ADS_UL_CTX_STRU                     stAdsUlCtx;                             /* ���������� */
    ADS_DL_CTX_STRU                     stAdsDlCtx;                             /* ���������� */
    ADS_STATS_INFO_CTX_STRU             stAdsStatsInfoCtx;                      /* ADS����ͳ�� */

}ADS_SPEC_CTX_STRU;


typedef struct
{
    ADS_SPEC_CTX_STRU                   astAdsSpecCtx[ADS_INSTANCE_MAX_NUM];    /* ÿ��ʵ��ר�е������� */
    ADS_IPF_CTX_STRU                    stAdsIpfCtx;                            /* ��IPF��ص������� */
    ADS_TIMER_CTX_STRU                  astAdsTiCtx[ADS_MAX_TIMER_NUM];         /* ��ʱ�������� */
    VOS_UINT8                           ucAdsCurInstanceIndex;                  /* ��ǰʵ����index */
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulULResetSem;                           /* �������ź���������UL��λ����  */
    VOS_UINT32                          ulDLResetSem;                           /* �������ź���������DL��λ����  */
}ADS_CTX_STRU;
/* Modified by l60609 for DSDA Phase II, 2012-11-22, End */

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

extern VOS_UINT32                       g_ulAdsULTaskId;
extern VOS_UINT32                       g_ulAdsDLTaskId;
extern VOS_UINT32                       g_ulAdsULTaskReadyFlag;
extern VOS_UINT32                       g_ulAdsDLTaskReadyFlag;

extern ADS_CTX_STRU                     g_stAdsCtx;


/*****************************************************************************
  10 ��������
*****************************************************************************/
/* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
VOS_UINT32 ADS_UL_IsAllRabNotSndPermitFlg(VOS_VOID);
VOS_UINT32 ADS_UL_GetSpecInstanceSndPermitFlg(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_DL_ProcEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_DL_SndEvent(VOS_UINT32 ulEvent);
VOS_UINT32 ADS_GetCurrentRate(
    VOS_UINT32                         *pulUlBpsRate,
    VOS_UINT32                         *pulDlBpsRate
);
ADS_DL_CTX_STRU* ADS_GetDlCtx(VOS_UINT8 ucInstanceIndex);
ADS_STATS_INFO_CTX_STRU* ADS_GetStatsInfoCtx(VOS_UINT8 ucInstanceIndex);
ADS_TIMER_CTX_STRU* ADS_GetTiCtx(VOS_VOID);
ADS_UL_CTX_STRU* ADS_GetUlCtx(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_InitCtx(VOS_VOID);
VOS_VOID ADS_InitDlCtx(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_InitIpfCtx(VOS_VOID);
VOS_VOID ADS_InitSpecCtx(VOS_VOID);
VOS_VOID ADS_InitStatsInfoCtx(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_InitTiCtx(VOS_VOID);
VOS_VOID ADS_InitUlCtx(VOS_UINT8 ucInstanceIndex);
VOS_UINT32 ADS_IsValidRabId(VOS_UINT8 ucRabId);
VOS_UINT32 ADS_UL_CheckAllQueueEmpty(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_UL_ClearQueue(
    VOS_UINT8                           ucRabId,
    IMM_ZC_HEAD_STRU                   *pstQueue
);
VOS_UINT32 ADS_UL_CreateQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPdpType
);
VOS_VOID ADS_UL_DestroyQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_GetAllQueueDataNum(VOS_VOID);
VOS_UINT32 ADS_UL_GetInsertIndex(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_GetInstanceAllQueueDataNum(VOS_UINT8 ucInstanceIndex);
VOS_UINT32 ADS_UL_InsertQueue(
    VOS_UINT8                           ucInstanceIndex,
    IMM_ZC_STRU                        *pstData,
    VOS_UINT8                           ucRabId
);
VOS_UINT32 ADS_UL_IsQueueExistent(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_OrderQueueIndex(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucIndex
);
VOS_VOID ADS_UL_ProcEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_UL_SetProtectTmrLen(VOS_UINT32 ulTimerLen);
VOS_VOID ADS_UL_SetQueue(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucIsQueueValid,
    IMM_ZC_HEAD_STRU                   *pstUlQueue,
    ADS_QCI_TYPE_ENUM_UINT8             enPrio,
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPdpType
);
VOS_VOID ADS_UL_SndEvent(VOS_UINT32 ulEvent);
VOS_VOID ADS_UL_UpdateQueueInPdpDeactived(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_UpdateQueueInPdpModified(
           VOS_UINT8                           ucInstanceIndex,
           ADS_QCI_TYPE_ENUM_UINT8             enPrio,
           VOS_UINT8                           ucRabId
);
ADS_CTX_STRU* ADS_GetAllCtx(VOS_VOID);
VOS_VOID ADS_DL_ProcAdqEmptyEvent(VOS_UINT32 ulEvent);

/* Modified by l60609 for DSDA Phase II, 2012-11-24, End */
VOS_VOID ADS_DL_InitFcAssemParamInfo(VOS_VOID);

VOS_UINT32 ADS_GetULResetSem(VOS_VOID);
VOS_UINT32 ADS_GetDLResetSem(VOS_VOID);
VOS_VOID ADS_DL_ResetFcAssemParamInfo(VOS_VOID);
VOS_VOID ADS_ResetDlCtx(VOS_UINT8 ucInstanceIndex);
VOS_VOID ADS_ResetSpecCtx(VOS_VOID);
VOS_VOID ADS_ResetIpfCtx(VOS_VOID);

VOS_UINT32 ADS_UL_IsAnyQueueExist(VOS_UINT8 ucInstance);
extern VOS_UINT32 OM_AcpuTraceMsgHook(VOS_VOID *pMsg);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif


