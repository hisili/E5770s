

#ifndef __ADSTIMERMGMT_H__
#define __ADSTIMERMGMT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ADS��ͬʱ���еĶ�ʱ���������Ŀ,Ŀǰֻ��һ�� */
/* Modified by l60609 for DSDA Phase II, 2012-11-22, Begin */
#define ADS_MAX_TIMER_NUM               (TI_ADS_TIMER_BUTT)
/* Modified by l60609 for DSDA Phase II, 2012-11-22, End */

/* ��ʱ��TI_ADS_UL_SEND��ʱ�� */
#define TI_ADS_UL_SEND_LEN              (10)

/* ��ʱ��TI_ADS_DSFLOW_STATS��ʱ����2��ͳ��һ������ */
#define TI_ADS_DSFLOW_STATS_LEN         (2000)

/* ��ʱ��TI_ADS_DL_PROTECT��ʱ��, 100ms */
#define TI_ADS_DL_PROTECT_LEN           (100)

/* Added by l60609 for DSDA Phase II, 2012-12-20, Begin */
/* ��ʱ��TI_ADS_DL_ADQ_EMPTY��ʱ��, 10ms */
#define TI_ADS_DL_ADQ_EMPTY_LEN         (10)
/* Added by l60609 for DSDA Phase II, 2012-12-20, Begin */

/* ��ʱ��TI_ADS_RPT_STATS��ʱ����2���ϱ�һ��ͳ����Ϣ */
#define TI_ADS_RPT_STATS_LEN         (2000)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum ADS_TIMER_ID_ENUM
{
    TI_ADS_UL_SEND,                                                             /* ADS���з��Ͷ�ʱ�� */
    /* Modified by l60609 for DSDA Phase II, 2012-11-22, Begin */
    TI_ADS_DSFLOW_STATS_0,                                                      /* Instance 0 ������ͳ�ƶ�ʱ�� */
    TI_ADS_DSFLOW_STATS_1,                                                      /* Instance 1 ������ͳ�ƶ�ʱ�� */
    TI_ADS_DL_ADQ_EMPTY,                                                        /* ����ADQ�ն�ʱ�� */
    /* Modified by l60609 for DSDA Phase II, 2012-11-22, End */
    TI_ADS_DL_PROTECT,                                                          /* ����RD������ʱ�� */
    TI_ADS_RPT_STATS_INFO,                                                      /* �ϱ�ͳ����Ϣ��ʱ�� */
    TI_ADS_TIMER_BUTT
};
typedef VOS_UINT32  ADS_TIMER_ID_ENUM_UINT32;



enum ADS_TIMER_STATUS_ENUM
{
    ADS_TIMER_STATUS_STOP,                                                      /* ��ʱ��ֹͣ״̬ */
    ADS_TIMER_STATUS_RUNNING,                                                   /* ��ʱ������״̬ */
    ASD_TIMER_STATUS_BUTT
};
typedef VOS_UINT8 ADS_TIMER_STATUS_ENUM_UINT8;


enum ADS_TIMER_OPERATION_TYPE_ENUM
{
    ADS_TIMER_OPERATION_START,                                                  /*������ʱ��*/
    ADS_TIMER_OPERATION_STOP,                                                   /*ֹͣ��ʱ��*/
    ADS_TIMER_OPERATION_TYPE_ENUM_BUTT
};
typedef VOS_UINT8 ADS_TIMER_OPERATION_TYPE_ENUM_UINT8;


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

/*****************************************************************************
 �ṹ����: ADS_TIMER_PRECISION_STRU
 �ṹ˵��: ADS��ʱ�����Ƚṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          enTimerId;          /* ��ʱ������ */
    VOS_TIMER_PRECISION_ENUM_UINT32     enPrecision;        /* ��ʱ������ */

} ADS_TIMER_PRECISION_STRU;



typedef struct
{
    HTIMER                              hTimer;                                 /* ��ʱ��������ָ�� */
    ADS_TIMER_ID_ENUM_UINT32            enTimerId;                              /* ��ʱ����ID */
    ADS_TIMER_STATUS_ENUM_UINT8         enTimerStatus;                          /* ��ʱ��������״̬,������ֹͣ */
    VOS_UINT8                           aucRsv[3];                              /* ����*/
} ADS_TIMER_CTX_STRU;

/*****************************************************************************
 �ṹ����: ADS_TIMER_INFO_STRU
 �ṹ˵��: ADS��ʱ����Ϣ�ṹ������SDT����ʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* _H2ASN_Skip */
    ADS_TIMER_ID_ENUM_UINT32            enTimerId;          /* _H2ASN_Skip */
    VOS_UINT32                          ulTimerLen;         /* ��ʱ������*/
    ADS_TIMER_OPERATION_TYPE_ENUM_UINT8 enTimerAction;      /* ��ʱ���������� */
    VOS_UINT8                           aucReserved[3];
} ADS_TIMER_INFO_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID ADS_DL_StartProtectTimer(VOS_VOID);

VOS_TIMER_PRECISION_ENUM_UINT32 ADS_GetTimerPrecision(ADS_TIMER_ID_ENUM_UINT32 enTimerId);

VOS_VOID  ADS_StartTimer(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId,
    VOS_UINT32                          ulLen
);

VOS_VOID ADS_StopTimer(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId
);

#if ((FEATURE_ON == MBB_CTF_WAN_QUEUE) || (FEATURE_ON == MBB_FEATURE_FASTIP_WAN_QUEUE))
VOS_VOID ADS_UL_StartSendTmr(VOS_VOID);
#endif /*(FEATURE_ON == MBB_CTF_WAN_QUEUE) || (FEATURE_ON == MBB_FEATURE_FASTIP_WAN_QUEUE)*/

ADS_TIMER_STATUS_ENUM_UINT8 ADS_GetTimerStatus(
    VOS_UINT32                          ulPid,
    ADS_TIMER_ID_ENUM_UINT32            enTimerId
);

#if (FEATURE_OFF == FEATURE_SKB_EXP)
VOS_VOID ADS_DL_StartAdqEmptyTimer(VOS_VOID);
#endif


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

#endif /* end of AdsTimerMgmt.h */
