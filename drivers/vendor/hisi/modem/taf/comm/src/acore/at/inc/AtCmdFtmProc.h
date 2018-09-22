

#ifndef __ATCMDFTMPROC_H__
#define __ATCMDFTMPROC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "AtCtx.h"
#include "AtParse.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* LOG3.5�Ķ˿ڶ���: USB */
#define AT_LOG_PORT_USB                 (0)

/* LOG3.5�Ķ˿ڶ���: VCOM */
#define AT_LOG_PORT_VCOM                (1)

#define AT_JAM_DETECT_DEFAULT_METHOD                        (2)
#define AT_JAM_DETECT_DEFAULT_THRESHOLD                     (10)
#define AT_JAM_DETECT_DEFAULT_FREQ_NUM                      (30)




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

VOS_UINT32 At_SetLogPortPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_QryLogPortPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetDpdtTestFlagPara(TAF_UINT8 ucIndex);
VOS_UINT32 At_SetDpdtPara(TAF_UINT8 ucIndex);
VOS_UINT32 At_SetQryDpdtPara(TAF_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaSetDpdtTestFlagCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvMtaSetDpdtValueCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvMtaQryDpdtValueCnf(VOS_VOID *pMsg);



VOS_UINT32 At_SetJamDetectPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_QryJamDetectPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaSetJamDetectCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaJamDetectInd(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_SetRatFreqLock(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryRatFreqLock(VOS_UINT8 ucIndex);

VOS_UINT32 AT_RcvMtaSetRatFreqLockCnf(
    VOS_VOID                           *pMsg
);


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

#endif /* end of AtCmdFtmProc.h */
