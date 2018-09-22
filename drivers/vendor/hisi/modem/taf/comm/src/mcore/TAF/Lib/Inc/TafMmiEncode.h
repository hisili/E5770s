

#ifndef __TAFMMIENCODE_H__
#define __TAFMMIENCODE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "v_typdef.h"
#include "Taf_MmiStrParse.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define TAF_MMI_INSERT_SEPERATION_CHAR(pcOutMmiStr, ulPos)  \
{ \
    *(pcOutMmiStr + ulPos) = '*';   \
    ulPos                 += VOS_StrLen("*");   \
}

#define TAF_MMI_REGISTER_PASSWORD       "**03"

#define TAF_MMI_BuildEventType(usSndPid,usMsgName)         (((usSndPid) << 16) | (usMsgName))                    /* ���� Pid�Լ�usMsgName ����EventType  */

#define TAF_MMI_BITS_PER_OCTET                              (8)
#define TAF_MMI_BITS_PER_SEPTET                             (7)
#define TAF_MMI_USSD_7BIT_PAD                               (0x1a)

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
typedef VOS_UINT32 (*TAF_MMI_ENCODE_PROC_FUNC)(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pMsg,
    VOS_CHAR                           *pOutMmiStr
);


typedef struct
{
    VOS_UINT32                          ulEventType;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;
    VOS_UINT32                          aucReserved1[3];
}TAF_MMI_OPERATION_TABLE_STRU;


typedef struct
{
    VOS_UINT32                          ulEventType;
    TAF_MMI_ENCODE_PROC_FUNC            pMsgProcFunc;
}TAF_MMI_ENCODE_PROC_FUNC_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_UINT32 TAF_MmiEncodeActiveMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pMsg,
    VOS_CHAR                           *pOutMmiStr
);

extern VOS_UINT32 TAF_MmiEncodeBS(
    TAF_SS_BASIC_SERVICE_STRU          *pstBsService,
    VOS_CHAR                           *pOutMmiStr,
    VOS_UINT32                         *pulBSLength
);

extern VOS_VOID TAF_MmiEncodeDN(
    TAF_SS_REGISTERSS_REQ_STRU         *pstRegisterInfo,
    VOS_CHAR                           *pOutMmiStr,
    VOS_UINT32                         *pulDNLength
);

extern VOS_UINT32 TAF_MmiEncodeEraseCcEntryMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pOutMmiStr
);

extern VOS_UINT32 TAF_MmiEncodeMmiString(
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pOutMmiStr
);

extern VOS_VOID TAF_MmiEncodePW(
    VOS_UINT8                          *pucPassword,
    VOS_UINT32                          ulPasswordLength,
    VOS_CHAR                           *pcOutMmiStr,
    VOS_UINT32                         *pulPWLength
);
extern VOS_UINT32 TAF_MmiEncodeRegisterMmiString(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pPara,
    VOS_CHAR                           *pOutMmiStr
);

extern VOS_UINT32 TAF_MmiEncodeRegisterPwdMmiString(
    VOS_UINT32                          ulEventType,
   VOS_VOID                           *pMsg,
   VOS_CHAR                           *pOutMmiStr
);

extern VOS_UINT32 TAF_MmiEncodeSC(
    TAF_SS_CODE                         SsCode,
    VOS_CHAR                           *pOutMmiStr,
    VOS_UINT32                         *pulScLength
);

extern TAF_MMI_OPERATION_TABLE_STRU *TAF_MmiGetEventOperationTypeTblAddr(VOS_VOID);

extern VOS_UINT32 TAF_MmiGetEventOperationTypeTblSize(VOS_VOID);

extern VOS_UINT32 TAF_MmiEncodeUssdMessage (
    TAF_SS_USSD_STRING_STRU            *pstPara
);

VOS_UINT32 TAF_MmiGetOperationType(
    VOS_UINT32                          ulEventType,
    MN_MMI_OPERATION_TYPE_ENUM_U8      *penSsOpType
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

#endif /* end of TafMmiEncode.h */
