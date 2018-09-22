

#ifndef __TTFOAMINTERFACE_H__
#define __TTFOAMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TTFLink.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
/* R99 Mailbox VTB �������ݵ�ַ */
extern VOS_UINT32  g_aulR99MailboxVtbAddr[];


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

#ifndef COMM_ITT
/* Supported by L2 */
extern VOS_VOID WTTF_MAC_R99MailBox_ReadFor3G0MsIsr(VOS_VOID);

extern VOS_VOID WTTF_INTResponseNotify(VOS_VOID);

extern VOS_VOID WTTF_MACDL_DpaDecodeIntNotify(VOS_VOID);

extern VOS_VOID WTTF_HsupaStatusIndINTResponseNotify(VOS_VOID);

extern MsgBlock *           TTF_TraceMsg(MsgBlock *pMsg);

extern VOS_UINT8            TTF_FilterMsg(MsgBlock *msg);

extern VOS_VOID             TTF_TraceModuleSet(VOS_INT32 lModuleNum,VOS_UINT32 *paulModuleId);

#endif

extern VOS_VOID             TTF_TraceSet(VOS_UINT32 ulOption);     /* L2��Ϣ���������趨�ӿ� */


extern VOS_VOID WTTF_MACDL_BbpMasterVoteAllowSleep(VOS_VOID);

extern VOS_VOID WTTF_MACDL_BbpMasterDrxInit(VOS_VOID);

extern VOS_VOID WTTF_MAC_R99MailBox_ReadForIpcHalt(VOS_VOID);



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

#endif /* end of WasOmInterface.h */

