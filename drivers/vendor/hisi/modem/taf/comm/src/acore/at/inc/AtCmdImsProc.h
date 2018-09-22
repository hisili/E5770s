

#ifndef __ATCMDIMSPROC_H__
#define __ATCMDIMSPROC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "AtCtx.h"
#include "AtParse.h"
#include "AtImsaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 �궨��
*****************************************************************************/


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

/*AT��IMSAģ�����Ϣ������ָ��*/
typedef VOS_UINT32 (*AT_IMSA_MSG_PROC_FUNC)(VOS_VOID *pMsg);

/*****************************************************************************
 �ṹ��    : AT_IMSA_MSG_PRO_FUNC_STRU
 �ṹ˵��  : AT��IMSA��Ϣ���Ӧ�������Ľṹ
*****************************************************************************/
typedef struct
{
    AT_IMSA_MSG_TYPE_ENUM_UINT32        ulMsgId;
    AT_IMSA_MSG_PROC_FUNC               pProcMsgFunc;
}AT_IMSA_MSG_PRO_FUNC_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID AT_ProcImsaMsg(AT_IMSA_MSG_STRU *pstMsg);

VOS_UINT32 AT_RcvImsaCiregSetCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCiregQryCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCirepSetCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCirepQryCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaImpuSetCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCirephInd(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCirepiInd(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCireguInd(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaCcwaiSetCnf(VOS_VOID * pMsg);

VOS_UINT32 AT_RcvImsaVtPdpActInd(VOS_VOID * pMsg);
VOS_UINT32 AT_RcvImsaVtPdpDeactInd(VOS_VOID * pMsg);

#endif /* end of FEATURE_IMS */

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

#endif /* end of AtCmdImsProc.h */

