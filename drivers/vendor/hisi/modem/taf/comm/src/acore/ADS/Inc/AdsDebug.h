

#ifndef __ADSTEST_H__
#define __ADSTEST_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
/* Added by l60609 for AP������Ŀ ��2012-08-30 Begin */
#include "product_config.h"
/* Added by l60609 for AP������Ŀ ��2012-08-30 End */
#include "AdsCtx.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "msp_diag.h"
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

#define ADS_LATENCY_LOG(ModuleId, String)   \
            ADS_LATENCY_OM_LOG(__FILE__, __LINE__, ModuleId, LOG_LEVEL_ERROR, String)

/* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */
/*����ͳ����Ϣ*/
#define  ADS_DBG_RECV_UL_PKT_NUM(i, n)              (g_stAdsStats.astAdsSpecStatsInfo[i].ulUlRecvPktNum += (n))
#define  ADS_DBG_UL_SAVE_BUFF_PKT_NUM(i, n)         (g_stAdsStats.astAdsSpecStatsInfo[i].ulUlSaveBuffPktNum += (n))
#define  ADS_DBG_UL_ENQUE_FAIL_NUM(i, n)            (g_stAdsStats.astAdsSpecStatsInfo[i].ulUlEnQueFail += (n))
#define  ADS_DBG_UL_CFG_FAIL_FREE_NUM(i, n)         (g_stAdsStats.astAdsSpecStatsInfo[i].ulUlCfgFailFreeNum += (n))
#define  ADS_DBG_UL_CURRT_BDCD_NUM(i, n)            (g_stAdsStats.astAdsSpecStatsInfo[i].ulUlCurrtBDCDNum += (n))

/*����ͳ����Ϣ*/
#define  ADS_DBG_RECV_DL_PKT_NUM(i, n)              (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRecvPktNum += (n))
#define  ADS_DBG_SEND_DL_PKT_NUM(i, n)              (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlSendPktNum += (n))
#define  ADS_DBG_DL_IPF_ERR_PKT_NUM(i, n)           (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlIPFErrNum += (n))
#define  ADS_DBG_DL_IPV6_BIG_PKT_NUM(i, n)          (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlIpv6BigPktum += (n))
#define  ADS_DBG_DL_RECV_NDCLIENT_PKT_NUM(i, n)     (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRecvNDClintPktum += (n))
#define  ADS_DBG_DL_RABID_ERR_PKT_NUM(i, n)         (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRabIdErrPktum += (n))
#define  ADS_DBG_DL_RECV_DHCPV4V6_PKT_NUM(i, n)     (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRecvDHCPV4V6Pktum += (n))
#define  ADS_DBG_DL_RECV_IPV6_LINK_LOCAL_ADRESS_PKT_NUM(i, n)  (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRecvIPV6LinkLocalAddressPktum += (n))
/* ֻ��V3R3��ʹ�� */
#define  ADS_DBG_DL_TRANS_FROM_IMMZC_ERR_NUM(n)     (g_stAdsStats.astAdsSpecStatsInfo[0].ulDlTransformImmZcErr += (n))
#define  ADS_DBG_DL_FREE_NUM(i, n)                  (g_stAdsStats.astAdsSpecStatsInfo[i].ulDlFreeNum += (n))

#define  ADS_DBG_UL_CFG_IPF_HAVE_NO_BDCD(n)         (g_stAdsStats.stUlComStatsInfo.ulUlCfgIpfHaveNoBDCD += (n))
#define  ADS_DBG_UL_SEND_BUFF_PKT_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulUlSendBuffPktNum += (n))
#define  ADS_DBG_UL_SEND_PKT_FAIL_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulUlIpfSendPktFailNum += (n))
#define  ADS_DBG_UL_PROC_EVENT_NUM(n)               (g_stAdsStats.stUlComStatsInfo.ulUlProcEventNum += (n))

#define  ADS_DBG_DL_RECV_IPF_BREAK_NUM(n)           (g_stAdsStats.stDlComStatsInfo.ulDlRecvIPFBreakNum += (n))
#define  ADS_DBG_DL_RECV_RD_ZERO_NUM(n)             (g_stAdsStats.stDlComStatsInfo.ulDlRecvRDZeroNum += (n))
#define  ADS_DBG_DL_RECV_RD_NUM(n)                  (g_stAdsStats.stDlComStatsInfo.ulDlRecvRDNum += (n))
#define  ADS_DBG_DL_PROC_EVENT_NUM(n)               (g_stAdsStats.stDlComStatsInfo.ulDlProcEventNum += (n))
#define  ADS_DBG_DL_PROC_RD_EVENT_NUM(n)            (g_stAdsStats.stDlComStatsInfo.ulDlRdEventNum += (n))
#define  ADS_DBG_DL_PROC_AD_EMPTY_EVENT_NUM(n)      (g_stAdsStats.stDlComStatsInfo.ulDlAdEmptyNum += (n))
#define  ADS_DBG_DL_PROC_OTHER_EVENT_NUM(n)         (g_stAdsStats.stDlComStatsInfo.ulDlOtherEvent += (n))
#define  ADS_DBG_DL_PROC_ALL_EVENT_NUM(n)           (g_stAdsStats.stDlComStatsInfo.ulDlAllEvent += (n))
#define  ADS_DBG_DL_PROC_EMPTY_EVENT_NUM(n)         (g_stAdsStats.stDlComStatsInfo.ulDlEmptyEvent += (n))

/* Added by l60609 for AP������Ŀ ��2012-08-30 Begin */
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    /* ����Դ�ڴ��ͷ�ͳ�� */
#define ADS_DBG_UL_IPF_SAVE_SRCMEM_FAIL_NUM(n)      (g_stAdsStats.stUlComStatsInfo.ulUlIpfSaveSrcMemFail  += (n))
#define ADS_DBG_UL_IPF_SAVE_SRCMEM_SUCC_NUM(n)      (g_stAdsStats.stUlComStatsInfo.ulUlIpfSaveSrcMemSucc  += (n))
#define ADS_DBG_UL_IPF_FREE_SRCMEM_NUM(n)           (g_stAdsStats.stUlComStatsInfo.ulUlIpfFreeSrcMemNum   += (n))
#define ADS_DBG_UL_IPF_FREE_SRCMEM_ERROR(n)         (g_stAdsStats.stUlComStatsInfo.ulUlIpfFreeSrcMemErr   += (n))
#define ADS_DBG_UL_DROPPED_PACKET_NUM(n)            (g_stAdsStats.stUlComStatsInfo.ulUlDroppedPacketNum   += (n))

    /* ��������ϵͳ�ڴ�ͳ�� */
#define ADS_DBG_DL_ALLOC_SYS_MEM_FAIL_NUM(n)        (g_stAdsStats.stDlComStatsInfo.ulDlAllocSysMemFailNum   += (n))
#define ADS_DBG_DL_ALLOC_SYS_MEM_SUCC_NUM(n)        (g_stAdsStats.stDlComStatsInfo.ulDlAllocSysMemSuccNum   += (n))

/* ����ADͳ��  */
#define ADS_DBG_DL_GET_AD_FAIL_NUM(n)               (g_stAdsStats.stDlComStatsInfo.ulDlGetAdFailNum         += (n))
#define ADS_DBG_DL_CONFIG_AD_SUCC_NUM(i, n)         (g_stAdsStats.stDlComStatsInfo.aulDlConfigAdSuccNum[i]  += (n))
#define ADS_DBG_DL_CONFIG_AD_FAIL_NUM(i, n)         (g_stAdsStats.stDlComStatsInfo.aulDlConfigAdFailNum[i]  += (n))
#define ADS_DBG_DL_RECV_ADQ_EMPTY_BREAK_NUM(n)      (g_stAdsStats.stDlComStatsInfo.ulDlRecvAdqEmptyBreakNum += (n))
#define ADS_DBG_DL_PROC_ADQ_EMPTY_EVENT_NUM(n)      (g_stAdsStats.stDlComStatsInfo.ulDlProcAdqEmptyEventNum += (n))
#define ADS_DBG_DL_GET_ADQ_EMPTY_NUM(i, n)          (g_stAdsStats.stDlComStatsInfo.aulDlGetAdqEmptyNum[i]   += (n))
#define ADS_DBG_DL_ALLOC_AD_FAIL_NUM(i, n)          (g_stAdsStats.stDlComStatsInfo.aulDlAllocAdFailNum[i]   += (n))
#define ADS_DBG_DL_ALLOC_AD_SUCC_NUM(i, n)          (g_stAdsStats.stDlComStatsInfo.aulDlAllocAdSuccNum[i]   += (n))

#endif
/* Added by l60609 for AP������Ŀ ��2012-08-30 End */

/* Modified by l60609 for DSDA Phase II, 2012-11-24, End */
#define  ADS_DBG_DL_RD_TI_PROTECT_EXPIRED_NUM(n)    (g_stAdsStats.stDlComStatsInfo.ulDlRdTiProtectExpiredNum += (n))
#define  ADS_DBG_DL_RD_PROTECT_EVENT_NUM(n)         (g_stAdsStats.stDlComStatsInfo.ulDlRdProctectEventNum += (n))
#define  ADS_DBG_DL_FC_ACTIVATE_NUM(n)              (g_stAdsStats.stDlComStatsInfo.ulDlFcTmrExpiredCnt += (n))
#define  ADS_DBG_DL_FC_TMR_EXP_NUM(n)               (g_stAdsStats.stDlComStatsInfo.ulDlFcActivateCnt += (n))

#define ADS_DBG_SET_SEM_INIT_FLAG(flag)              (g_stAdsStats.stResetStatsinfo.ulSemInitFlg = (flag))
#define ADS_UL_DBG_SAVE_BINARY_SEM_ID(sem_id)        (g_stAdsStats.stResetStatsinfo.ulULBinarySemId = (sem_id))
#define ADS_DL_DBG_SAVE_BINARY_SEM_ID(sem_id)        (g_stAdsStats.stResetStatsinfo.ulDLBinarySemId = (sem_id))
#define ADS_UL_DBG_CREATE_BINARY_SEM_FAIL_NUM(n)     (g_stAdsStats.stResetStatsinfo.ulULCreateBinarySemFailNum += (n))
#define ADS_DL_DBG_CREATE_BINARY_SEM_FAIL_NUM(n)     (g_stAdsStats.stResetStatsinfo.ulDLCreateBinarySemFailNum += (n))
#define ADS_UL_DBG_LOCK_BINARY_SEM_FAIL_NUM(n)       (g_stAdsStats.stResetStatsinfo.ulULLockBinarySemFailNum += (n))
#define ADS_DL_DBG_LOCK_BINARY_SEM_FAIL_NUM(n)       (g_stAdsStats.stResetStatsinfo.ulDLLockBinarySemFailNum += (n))
#define ADS_UL_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(rslt)  (g_stAdsStats.stResetStatsinfo.ulULLastBinarySemErrRslt = (rslt))
#define ADS_DL_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(rslt)  (g_stAdsStats.stResetStatsinfo.ulDLLastBinarySemErrRslt = (rslt))
#define ADS_UL_DBG_SAVE_CCPU_RESET_SUCCESS_NUM(n)    (g_stAdsStats.stResetStatsinfo.ulULResetSucessNum += (n))
#define ADS_DL_DBG_SAVE_CCPU_RESET_SUCCESS_NUM(n)    (g_stAdsStats.stResetStatsinfo.ulDLResetSucessNum += (n))

/*****************************************************************************
  3 ö�ٶ���
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
/* Modified by l60609 for DSDA Phase II, 2012-11-24, Begin */

typedef struct
{
    /*ADS����ͳ����Ϣ*/
    VOS_UINT32              ulUlRecvPktNum;                                     /*ADS�յ��������ݵĸ���*/
    VOS_UINT32              ulUlSaveBuffPktNum;                                 /*ADS���л��������*/
    VOS_UINT32              ulUlEnQueFail;                                      /*ADS�������ʧ�ܴ���*/
    VOS_UINT32              ulUlCfgFailFreeNum;                                 /*��������BDʧ�ܺ��ͷ�SDU����*/
    VOS_UINT32              ulUlCurrtBDCDNum;                                   /*��ǰ������BD/CD����*/

    /*����RDͳ����Ϣ*/
    VOS_UINT32              ulDlRecvPktNum;                                     /*ADS�յ��������ݵĸ���*/
    VOS_UINT32              ulDlSendPktNum;                                     /*ADS������APP���ݵĸ���*/
    VOS_UINT32              ulDlIPFErrNum;                                      /*IPF���˴��������*/
    VOS_UINT32              ulDlIpv6BigPktum;                                   /*��ȡ������MTU��IPV6������*/
    VOS_UINT32              ulDlRabIdErrPktum;                                  /*RAB ID��������ݰ��ĸ���*/
    VOS_UINT32              ulDlRecvNDClintPktum;                               /*��Ҫת����NDClient���ݰ��ĸ���*/
    VOS_UINT32              ulDlRecvDHCPV4V6Pktum;                              /*��Ҫת����NDClient���ݰ��ĸ���*/
    VOS_UINT32              ulDlRecvIPV6LinkLocalAddressPktum;                  /*��Ҫת����NDClient���ݰ��ĸ���*/

    VOS_UINT32              ulDlTransformImmZcErr;                              /*��Ҫת����NDClient���ݰ��ĸ���*/
    VOS_UINT32              ulDlFreeNum;                                        /*ADS�����ͷ�C���ڴ�Ĵ���*/
}ADS_SPEC_STATS_INFO_STRU;


typedef struct
{
    VOS_UINT32              ulUlCfgIpfHaveNoBDCD;                               /*��������IPFû�л��BD/CD����*/
    VOS_UINT32              ulUlSendBuffPktNum;                                 /*ADS�������л��������*/
    VOS_UINT32              ulUlIpfSendPktFailNum;                              /*����IPF����ʧ�ܵĴ���*/
    VOS_UINT32              ulUlProcEventNum;                                   /*ADS���������¼�����*/
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    VOS_UINT32              ulUlIpfSaveSrcMemFail;                              /* ����IPFԴ�ڴ���в��㵼���ڴ�*/
    VOS_UINT32              ulUlIpfSaveSrcMemSucc;                              /* ���б���Դ�ڴ���� */
    VOS_UINT32              ulUlIpfFreeSrcMemNum;                               /* �����ͷ�Դ�ڴ���� */
    VOS_UINT32              ulUlIpfFreeSrcMemErr;                               /* �����ͷ��ڴ���� */
    VOS_UINT32              ulUlDroppedPacketNum;                               /* ���г����������� */
#endif
}ADS_UL_COM_STATS_INFO_STRU;


typedef struct
{
    VOS_UINT32              ulDlRecvIPFBreakNum;                                /*�����յ�IPF�¼��ĸ���*/
    VOS_UINT32              ulDlRecvRDNum;                                      /*���л�ȡRD�Ĵ���*/
    VOS_UINT32              ulDlRecvRDZeroNum;                                  /*���л�ȡRDΪ0�Ĵ���*/
    VOS_UINT32              ulDlProcEventNum;                                   /*ADS���������¼�����*/
    VOS_UINT32              ulDlRdEventNum;
    VOS_UINT32              ulDlAdEmptyNum;
    VOS_UINT32              ulDlOtherEvent;
    VOS_UINT32              ulDlAllEvent;
    VOS_UINT32              ulDlEmptyEvent;
#if(FEATURE_OFF == FEATURE_SKB_EXP)
    VOS_UINT32              ulDlAllocSysMemSuccNum;                             /* ADS��������ϵͳ�ڴ�ɹ����� */
    VOS_UINT32              ulDlAllocSysMemFailNum;                             /* ADS��������ϵͳ�ڴ�ʧ�ܴ��� */
    VOS_UINT32              ulDlGetAdFailNum;                                   /* ADS���л�ȡADʧ�ܴ��� */
    VOS_UINT32              aulDlConfigAdSuccNum[IPF_AD_MAX];                   /* ADS��������AD�ɹ����� */
    VOS_UINT32              aulDlConfigAdFailNum[IPF_AD_MAX];                   /* ADS��������ADʧ�ܴ��� */
    VOS_UINT32              ulDlRecvAdqEmptyBreakNum;                           /* ADS���п��жϴ��� */
    VOS_UINT32              ulDlProcAdqEmptyEventNum;                           /* ADS���п��ж��¼����� */
    VOS_UINT32              aulDlGetAdqEmptyNum[IPF_EMPTY_MAX];                 /* ADS����ADQΪ�յĴ��� */
    VOS_UINT32              aulDlAllocAdSuccNum[IPF_AD_MAX];                    /* ADS��������AD�ɹ��Ĵ��� */
    VOS_UINT32              aulDlAllocAdFailNum[IPF_AD_MAX];                    /* ADS��������ADʧ�ܵĴ��� */
#endif
    VOS_UINT32              ulDlRdTiProtectExpiredNum;                          /*ADS��������RD������ʱ����ʱ����*/
    VOS_UINT32              ulDlRdProctectEventNum;                             /*ADS��������RD�����¼�����*/
    VOS_UINT32              ulDlFcTmrExpiredCnt;
    VOS_UINT32              ulDlFcActivateCnt;
}ADS_DL_COM_STATS_INFO_STRU;


typedef struct
{
    VOS_UINT32              ulSemInitFlg;                                       /* ��ʼ����ʶ, VOS_TRUE: �ɹ�; VOS_FALSE: ʧ�� */
    VOS_UINT32              ulULBinarySemId;                                    /* ���ж������ź���ID */
    VOS_UINT32              ulDLBinarySemId;                                    /* ���ж������ź���ID */
    VOS_UINT32              ulULCreateBinarySemFailNum;                         /* �������ж������ź���ʧ�ܴ��� */
    VOS_UINT32              ulDLCreateBinarySemFailNum;                         /* �������ж������ź���ʧ�ܴ��� */
    VOS_UINT32              ulULLockBinarySemFailNum;                           /* �����ж������ź���ʧ�ܴ��� */
    VOS_UINT32              ulDLLockBinarySemFailNum;                           /* �����ж������ź���ʧ�ܴ��� */
    VOS_UINT32              ulULLastBinarySemErrRslt;                           /* ���һ���������������ź���ʧ�ܽ�� */
    VOS_UINT32              ulDLLastBinarySemErrRslt;                           /* ���һ���������������ź���ʧ�ܽ�� */
    VOS_UINT32              ulULResetSucessNum;                                 /* C�˸�λ���гɹ��Ĵ��� */
    VOS_UINT32              ulDLResetSucessNum;                                 /* C�˸�λ���гɹ��Ĵ��� */
}ADS_RESET_STATS_INFO_STRU;


typedef struct
{
    ADS_SPEC_STATS_INFO_STRU        astAdsSpecStatsInfo[ADS_INSTANCE_MAX_NUM];  /* ÿ��ʵ��ר�е�ͳ����Ϣ */
    ADS_UL_COM_STATS_INFO_STRU      stUlComStatsInfo;
    ADS_DL_COM_STATS_INFO_STRU      stDlComStatsInfo;
    ADS_RESET_STATS_INFO_STRU       stResetStatsinfo;

}ADS_STATS_INFO_STRU;
/* Modified by l60609 for DSDA Phase II, 2012-11-24, End */

typedef struct
{
    VOS_UINT32                          ulAdType;
    VOS_UINT32                          ulAdNum;
    VOS_UINT32                          ulBeginTi;
    VOS_UINT32                          ulMiddleTi;
    VOS_UINT32                          ulEndTi;
}ADS_DL_DEBUG_AD_TIMER_STRU;

typedef struct
{
    VOS_UINT32                          ulBeginTi;
    VOS_UINT32                          ulEndTi;
}ADS_DL_DEBUG_RD_TIMER_STRU;

typedef struct
{
    VOS_UINT32                          ulBeginTi;
    VOS_UINT32                          ulEndTi;
}ADS_DL_DEBUG_TASK_TIMER_STRU;


typedef struct
{
    ADS_LOG_HEAD_STRU                   stLogHeader;
    ADS_STATS_INFO_STRU                 stAdsStats;                             /* ADS��ͳ����Ϣ */
}ADS_LOG_RPT_STATS_INFO_STRU;

/*****************************************************************************
  8 ȫ�ֱ�������
*****************************************************************************/

extern ADS_STATS_INFO_STRU                     g_stAdsStats;
extern VOS_UINT32                              g_ulAdsPrintUlDataFlg;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_VOID ADS_LATENCY_OM_LOG(const VOS_CHAR  *pcFileName,  VOS_UINT32  ulLineNum,
                                   VOS_UINT32      ulModuleId,   VOS_UINT32 ulLevel,
                                   const VOS_CHAR  *pcString);

extern VOS_VOID ADS_MNTN_TraceRcvUlData(VOS_VOID);
extern VOS_VOID ADS_MNTN_TraceSndUlData(VOS_VOID);
extern VOS_VOID ADS_MNTN_TraceRcvDlData(VOS_VOID);

VOS_VOID ADS_ResetDebugInfo(VOS_VOID);


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

#endif /* end of AdsTest.h */
