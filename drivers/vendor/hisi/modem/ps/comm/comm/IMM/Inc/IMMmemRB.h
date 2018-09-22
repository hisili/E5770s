

#ifndef __IMMMEMRB_H__
#define __IMMMEMRB_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "TTFLink.h"
#include "vos.h"
#include "VosPidDef.h"
#include "om.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

#if (FEATURE_ON == FEATURE_SKB_EXP)
/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* IMM ��װ�Ĵ�ӡ������ */
#define IMM_PRINT_OFF        PS_PRINT_OFF
#define IMM_PRINT_ERROR      PS_PRINT_ERROR
#define IMM_PRINT_WARNING    PS_PRINT_WARNING
#define IMM_PRINT_NORMAL     PS_PRINT_NORMAL
#define IMM_PRINT_INFO       PS_PRINT_INFO
#define IMM_PRINT_BUTT       PS_PRINT_BUTT

#ifdef __UT_CENTER__

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#define IMM_LOG(ModulePID, Level, String)\
            OM_LOG((ModulePID), 0, (Level), (String))
#define IMM_LOG1(ModulePID, Level, String, Para1)\
            OM_LOG1((ModulePID), 0, (Level), (String), (Para1))
#define IMM_LOG2(ModulePID, Level, String, Para1, Para2)\
            OM_LOG2((ModulePID), 0, (Level), (String), (Para1), (Para2))
#define IMM_LOG3(ModulePID, Level, String, Para1, Para2, Para3)\
            OM_LOG3((ModulePID), 0, (Level), (String), (Para1), (Para2), (Para3))
#define IMM_LOG4(ModulePID, Level, String, Para1, Para2, Para3, Para4)\
            OM_LOG4((ModulePID), 0, (Level), (String), (Para1), (Para2), (Para3), (Para4))
#elif (OSA_CPU_CCPU == VOS_OSA_CPU)
#define IMM_LOG(ModulePID, Level, String)\
            PS_LOG((ModulePID), 0, (Level), (String))
#define IMM_LOG1(ModulePID, Level, String, Para1)\
            PS_LOG1((ModulePID), 0, (Level), (String), (Para1))
#define IMM_LOG2(ModulePID, Level, String, Para1, Para2)\
            PS_LOG2((ModulePID), 0, (Level), (String), (Para1), (Para2))
#define IMM_LOG3(ModulePID, Level, String, Para1, Para2, Para3)\
            PS_LOG3((ModulePID), 0, (Level), (String), (Para1), (Para2), (Para3))
#define IMM_LOG4(ModulePID, Level, String, Para1, Para2, Para3, Para4)\
            PS_LOG4((ModulePID), 0, (Level), (String), (Para1), (Para2), (Para3), (Para4))
#endif

#else

#define IMM_LOG(ModulePID, Level, String)\
            IMM_DebugLOG((String))
#define IMM_LOG1(ModulePID, Level, String, Para1)\
            IMM_DebugLOG1((String), (Para1))
#define IMM_LOG2(ModulePID, Level, String, Para1, Para2)\
            IMM_DebugLOG2((String), (Para1), (Para2))
#define IMM_LOG3(ModulePID, Level, String, Para1, Para2, Para3)\
            IMM_DebugLOG3((String), (Para1), (Para2), (Para3))
#define IMM_LOG4(ModulePID, Level, String, Para1, Para2, Para3, Para4)\
            IMM_DebugLOG4((String), (Para1), (Para2), (Para3), (Para4))

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

/*****************************************************************************
 �ṹ��    : IMM_MEM_RB_MNTN_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �˼��ά�ɲ���Ϣ
*****************************************************************************/
typedef struct IMM_MEM_RB_MNTN_INFO
{
    VOS_UINT32          ulImmMemRbSendIntCnt;       /* ImmMemRb ��IPF�����жϴ��� */
    VOS_UINT32          ulImmMemRbReceiveIntCnt;    /* ImmMemRb �յ�IPF�жϴ��� */
    VOS_UINT32          ulImmMemRbEnQFailCnt;       /* ImmMemRb ���ʧ�ܴ��� */
    VOS_UINT32          ulImmMemRbDeQFailCnt;       /* ImmMemRb ����ʧ�ܴ��� */
    VOS_UINT32          ulImmMemRbEnQTotalCnt;      /* ImmMemRb ������� */
    VOS_UINT32          ulImmMemRbDeQTotalCnt;      /* ImmMemRb �������� */
}IMM_MEM_RB_MNTN_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID IMM_RbRemoteFreeMem(VOS_VOID *pucAddr);
extern VOS_VOID IMM_DebugLOG(VOS_CHAR *pcString);
extern VOS_VOID IMM_DebugLOG1(VOS_CHAR *pcString, VOS_INT32 lPara1);
extern VOS_VOID IMM_DebugLOG2(VOS_CHAR *pcString, VOS_INT32 lPara1, VOS_INT32 lPara2);
extern VOS_VOID IMM_DebugLOG3(VOS_CHAR *pcString, VOS_INT32 lPara1, VOS_INT32 lPara2, VOS_INT32 lPara3);
extern VOS_VOID IMM_DebugLOG4(VOS_CHAR *pcString, VOS_INT32 lPara1, VOS_INT32 lPara2, VOS_INT32 lPara3, VOS_INT32 lPara4);
extern VOS_VOID IMM_RbMemFreeFromQue(VOS_VOID);

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

#endif /* end of IMMmemRB.h */
