
#ifndef __TAFAGENT_LOG_H__
#define __TAFAGENT_LOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "pslog.h"
#include "PsCommonDef.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*================================================*/
/* ��ֵ�궨�� */
/*================================================*/
#define     TAFAGENT_MEM_FAIL()              PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "APSAGENT Mem Operation Failed!");
#define     TAFAGENT_MSG_FAIL()              PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "APSAGENT Msg Opration Failed!");
#define     TAFAGENT_TIMER_FAIL()            PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "APSAGENT Timer Opration Failed!");

/*================================================*/
/* ���ܺ����궨�� */
/*================================================*/
#ifndef SUBMOD_NULL
#define    SUBMOD_NULL                                                  (0)
#endif

#define    TAFAGENT_INFO_LOG(Mod, String)                                    PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_INFO, (String) )
#define    TAFAGENT_INFO_LOG1(Mod, String,Para1)                            PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1) )
#define    TAFAGENT_INFO_LOG2(Mod, String,Para1,Para2)                       PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    TAFAGENT_INFO_LOG3(Mod, String,Para1,Para2,Para3)                 PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    TAFAGENT_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)           PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    TAFAGENT_NORMAL_LOG(Mod, String)                                  PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_NORMAL, (String) )
#define    TAFAGENT_NORMAL_LOG1(Mod, String,Para1)                           PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1) )
#define    TAFAGENT_NORMAL_LOG2(Mod, String,Para1,Para2)                     PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    TAFAGENT_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)               PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    TAFAGENT_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)         PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    TAFAGENT_WARNING_LOG(Mod, String)                                 PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_WARNING, (String) )
#define    TAFAGENT_WARNING_LOG1(Mod, String,Para1)                          PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1) )
#define    TAFAGENT_WARNING_LOG2(Mod, String,Para1,Para2)                    PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    TAFAGENT_WARNING_LOG3(Mod, String,Para1,Para2,Para3)              PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    TAFAGENT_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)        PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define    TAFAGENT_ERROR_LOG(Mod, String)                                   PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_ERROR, (String) )
#define    TAFAGENT_ERROR_LOG1(Mod, String,Para1)                            PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1) )
#define    TAFAGENT_ERROR_LOG2(Mod, String,Para1,Para2)                      PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define    TAFAGENT_ERROR_LOG3(Mod, String,Para1,Para2,Para3)                PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define    TAFAGENT_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)          PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

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
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/


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

#endif /* TafAgentLog.h */



