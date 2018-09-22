/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : ppp_init.h
  Author       : ---
  Version      : V200R001
  Date         : 2005-11-18
  Description  : ��ͷ�ļ�������PPPģ��ĳ�ʼ�������Լ�ϵͳ����ʱ���õ�
                 PPPģ��Ľ�������������˵����
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-11-18
     Author: ---fanzhibin 49086
     Modification:Create
 ************************************************************************/

#pragma pack(4)

#include "vos.h"

extern VOS_UINT32    PppInit(enum VOS_INIT_PHASE_DEFINE InitPhase );
extern VOS_VOID PppMsgProc( struct MsgCB * pMsg );
extern VOS_VOID    PppStop();
#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


