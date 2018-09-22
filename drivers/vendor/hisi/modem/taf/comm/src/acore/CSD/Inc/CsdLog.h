

#ifndef __CSDLOG_H__
#define __CSDLOG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "pslog.h"
#include "PsCommonDef.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*================================================*/
/* ��ֵ�궨�� */
/*================================================*/
#define CSD_MEM_FAIL()\
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "CSD Mem Operation Failed!");
#define CSD_MSG_FAIL()\
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "CSD Msg Opration Failed!");
#define CSD_TIMER_FAIL()\
        PS_LOG(WUEPS_PID_OM, 0, PS_PRINT_ERROR, "CSD Timer Opration Failed!");

/*================================================*/
/* ���ܺ����궨�� */
/*================================================*/
#ifndef SUBMOD_NULL
#define    SUBMOD_NULL                                                  (0)
#endif

#define CSD_INFO_LOG(Mod, String)\
        PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_INFO, (String) )
#define CSD_INFO_LOG1(Mod, String,Para1)\
        PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1) )
#define CSD_INFO_LOG2(Mod, String,Para1,Para2)\
        PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define CSD_INFO_LOG3(Mod, String,Para1,Para2,Para3)\
        PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define CSD_INFO_LOG4(Mod, String,Para1,Para2,Para3,Para4)\
        PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_INFO, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define CSD_NORMAL_LOG(Mod, String)\
        PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_NORMAL, (String) )
#define CSD_NORMAL_LOG1(Mod, String,Para1)\
        PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1) )
#define CSD_NORMAL_LOG2(Mod, String,Para1,Para2)\
        PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define CSD_NORMAL_LOG3(Mod, String,Para1,Para2,Para3)\
        PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define CSD_NORMAL_LOG4(Mod, String,Para1,Para2,Para3,Para4)\
        PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_NORMAL, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define CSD_WARNING_LOG(Mod, String)\
        PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_WARNING, (String) )
#define CSD_WARNING_LOG1(Mod, String,Para1)\
        PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1) )
#define CSD_WARNING_LOG2(Mod, String,Para1,Para2)\
        PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define CSD_WARNING_LOG3(Mod, String,Para1,Para2,Para3)\
        PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define CSD_WARNING_LOG4(Mod, String,Para1,Para2,Para3,Para4)\
        PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_WARNING, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

#define CSD_ERROR_LOG(Mod, String)\
        PS_LOG ( (Mod), SUBMOD_NULL,  PS_PRINT_ERROR, (String) )
#define CSD_ERROR_LOG1(Mod, String,Para1)\
        PS_LOG1 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1) )
#define CSD_ERROR_LOG2(Mod, String,Para1,Para2)\
        PS_LOG2 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )
#define CSD_ERROR_LOG3(Mod, String,Para1,Para2,Para3)\
        PS_LOG3 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )
#define CSD_ERROR_LOG4(Mod, String,Para1,Para2,Para3,Para4)\
        PS_LOG4 ( (Mod), SUBMOD_NULL, PS_PRINT_ERROR, (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )

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

#endif /* end of CsdLog.h */
