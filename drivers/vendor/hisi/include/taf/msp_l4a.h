#ifndef __MSP_L4A_H__
#define __MSP_L4A_H__

#include "vos.h"


extern VOS_UINT32 OSA_PostMessageToMsp(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);




/* ������Ϣ��PS,�ú��������������������ء�*/
/* ulParam1/2����Ϊָ��.*/
extern VOS_UINT32 OSM_PostMessageToPs(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2);

#endif