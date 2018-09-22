

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "RnicTimerMgmt.h"
#include "RnicCtx.h"
#include "v_timer.h"
#include "RnicLog.h"
#include "DrvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_TIMERMGMT_C
/*lint -e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_VOID  RNIC_InitAllTimers(
    RNIC_TIMER_CTX_STRU                 *pstRnicTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        pstRnicTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstRnicTimerCtx[i].enTimerId     = TI_RNIC_TIMER_BUTT;
        pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
    }
}


VOS_VOID  RNIC_StartTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId,
    VOS_UINT32                          ulLen
)
{
    VOS_UINT32                          ulRet;
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          i;
    RNIC_UL_CTX_STRU                   *pstUlCtx;
    VOS_TIMER_PRECISION_ENUM_UINT32     enTimerPrecision;

    /* Ŀǰ���貦�ŵĹ���ֻ������0���� */
    pstUlCtx            = RNIC_GetUlCtxAddr(RNIC_RM_NET_ID_0);

    pstRnicTimerCtx     = RNIC_GetTimerAddr();
    enTimerPrecision    = VOS_TIMER_PRECISION_5;

    /* �����������иö�ʱ���Ѿ�������ֱ�ӷ��� */
    for (i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++)
    {
        if ((RNIC_TIMER_STATUS_RUNING == pstRnicTimerCtx[i].enTimerStatus)
         && (enTimerId                == pstRnicTimerCtx[i].enTimerId))
        {
            RNIC_INFO_LOG1(ACPU_PID_RNIC, "RNIC_StartTimer:timer is running", enTimerId);
            return;
        }
    }

    for (i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++)
    {
        if ( RNIC_TIMER_STATUS_STOP == pstRnicTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if (i >= RNIC_MAX_TIMER_NUM)
    {
        RNIC_WARNING_LOG1(ACPU_PID_RNIC, "RNIC_StartTimer:too many timer", enTimerId);
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* �����δ���û���Դ��־�������ǰ���Ͽ���ʱ���������øñ�־����������32Kʱ��Ϊ����Դ */
    if ((VOS_FALSE == RNIC_GetTimer4WakeFlg())
      && (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId))
    {
        BSP_PWC_SetTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_TRUE);
    }

#endif

     /* ����������ϱ���ʱ���������26Mʱ���ϣ��Խ��͹��� */
    if (RNIC_IS_DSFLOW_TIMER_ID(enTimerId))
    {
        enTimerPrecision = VOS_TIMER_NO_PRECISION;
    }


    /* VOS_StartRelTimer ������ʱ�� */
    ulRet = VOS_StartRelTimer(&(pstRnicTimerCtx[i].hTimer),
                              ACPU_PID_RNIC,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              enTimerPrecision);
    if (VOS_OK != ulRet)
    {
        RNIC_WARNING_LOG(ACPU_PID_RNIC, "NAS_MMC_StartTimer:NAS_StartRelTimer failed");
        return;
    }

    if (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId)
    {
        /* ���貦��ͳ������ */
        pstUlCtx->stULDataStats.ulULPeriodSndPkts = 0;
    }

    pstRnicTimerCtx[i].enTimerId     = enTimerId;
    pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_RUNING;


    /* ��ʱ��״̬�������� */

}



VOS_VOID  RNIC_StopTimer(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          i;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();

    for ( i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++ )
    {
        if ( ( RNIC_TIMER_STATUS_RUNING  == pstRnicTimerCtx[i].enTimerStatus )
          && ( enTimerId                 == pstRnicTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= RNIC_MAX_TIMER_NUM)
    {
        RNIC_WARNING_LOG1(ACPU_PID_RNIC, "RNIC_StopTimer:too many timer", enTimerId);
        return;
    }

    /* ֹͣVOS��ʱ��: ����ʱ����ָ���Ѿ�Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
    if (VOS_NULL_PTR != pstRnicTimerCtx[i].hTimer)
    {
        VOS_StopRelTimer(&(pstRnicTimerCtx[i].hTimer));
    }

    pstRnicTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstRnicTimerCtx[i].enTimerId     = TI_RNIC_TIMER_BUTT;
    pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;

    /* ��ʱ��״̬�������� */
#if (FEATURE_ON == FEATURE_LTE)
    /* ����Ѿ������˻���Դ��־�������ǰ���Ͽ���ʱ����������ñ�־����������32Kʱ��Ϊ�ǻ���Դ */
    if ((VOS_TRUE == RNIC_GetTimer4WakeFlg())
     && (TI_RNIC_DEMAND_DIAL_DISCONNECT == enTimerId))
    {
        BSP_PWC_DelTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_FALSE);
    }
#endif
}



VOS_VOID  RNIC_StopAllTimer( VOS_VOID )
{

    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          i;

    pstRnicTimerCtx   =  RNIC_GetTimerAddr();

    for (i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++)
    {
        if (RNIC_TIMER_STATUS_RUNING  == pstRnicTimerCtx[i].enTimerStatus)
        {
            /* ֹͣVOS��ʱ�� */
            VOS_StopRelTimer(&(pstRnicTimerCtx[i].hTimer));

            pstRnicTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstRnicTimerCtx[i].enTimerId     = TI_RNIC_TIMER_BUTT;
            pstRnicTimerCtx[i].enTimerStatus = RNIC_TIMER_STATUS_STOP;
        }
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ����Ѿ������˻���Դ��־��������ñ�־����������32Kʱ��Ϊ�ǻ���Դ */
    if (VOS_TRUE == RNIC_GetTimer4WakeFlg())
    {
        BSP_PWC_DelTimer4WakeSrc();

        RNIC_SetTimer4WakeFlg(VOS_FALSE);
    }
#endif
}



RNIC_TIMER_STATUS_ENUM_UINT8  RNIC_GetTimerStatus(
    RNIC_TIMER_ID_ENUM_UINT16           enTimerId
)
{
    RNIC_TIMER_CTX_STRU                *pstRnicTimerCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulLeftLen;

    pstRnicTimerCtx = RNIC_GetTimerAddr();

    ulLeftLen       = 0;

    for (i = 0 ; i < RNIC_MAX_TIMER_NUM ; i++)
    {
        if ((RNIC_TIMER_STATUS_RUNING  == pstRnicTimerCtx[i].enTimerStatus)
         && (enTimerId                 == pstRnicTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if (i >= RNIC_MAX_TIMER_NUM)
    {
        return RNIC_TIMER_STATUS_STOP;
    }

    if (VOS_OK != (VOS_GetRelTmRemainTime(&(pstRnicTimerCtx[i].hTimer), &ulLeftLen )))
    {
        RNIC_StopTimer(enTimerId);
        return RNIC_TIMER_STATUS_STOP;
    }

    return RNIC_TIMER_STATUS_RUNING;

}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

