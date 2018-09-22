


#ifndef __ATOAMINTERFACE_H__
#define __ATOAMINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "v_msg.h"
#include "siapppih.h"
#include "siapppb.h"
#include "siappstk.h"
#include "MnClient.h"
#if(FEATURE_ON == MBB_WPG_COMMON)
#include "MbbPsCsCommon.h"
#endif
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


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


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/*****************************************************************************
 ö����    : AT_OAM_MSG_TYPE_ENUM
 �ṹ˵��  : TAF��OAM��Ϣ�ӿ�ö��
*****************************************************************************/
enum AT_OAM_MSG_TYPE_ENUM
{
    /* STK -> AT */
    STK_AT_DATAPRINT_CNF,/* MN_APP_STK_AT_DATAPRINT_STRU */
    STK_AT_EVENT_CNF,   /* _H2ASN_MsgChoice MN_APP_STK_AT_CNF_STRU */

    /* PIH -> AT */
    PIH_AT_EVENT_CNF,   /* _H2ASN_MsgChoice MN_APP_PIH_AT_CNF_STRU */

    /* PB -> AT */
    PB_AT_EVENT_CNF,   /* _H2ASN_MsgChoice MN_APP_PB_AT_CNF_STRU */

#if (FEATURE_ON == MBB_FEATURE_BIP)
    STK_AT_BIP_EVENT,   /* BIP EVENT FROM STK */
    STK_AT_BIP_AT_TEST_EVENT,
#endif

    AT_OAM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 AT_OAM_MSG_TYPE_ENUM_UINT32;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : MN_APP_PIH_AT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PIH��AT�ϱ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    SI_PIH_EVENT_INFO_STRU              stPIHAtEvent;
} MN_APP_PIH_AT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MN_APP_PB_AT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PIH��AT�ϱ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    SI_PB_EVENT_INFO_STRU               stPBAtEvent;
} MN_APP_PB_AT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : MN_APP_STK_AT_DATAIND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : STK��AT�ϱ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    SI_STK_PRINTDATA_CNF_STRU           stSTKAtPrint;
} MN_APP_STK_AT_DATAPRINT_STRU;


/*****************************************************************************
 �ṹ��    : MN_APP_STK_AT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : STK��AT�ϱ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    SI_STK_EVENT_INFO_STRU              stSTKAtCnf;
} MN_APP_STK_AT_CNF_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_INT32 At_sprintf(VOS_INT32 MaxLength,VOS_CHAR *headaddr,VOS_CHAR *curraddr,const VOS_CHAR *fmt,...);
extern VOS_UINT32 MMA_VerifyOperatorLockPwd(VOS_UINT8 *pucPwd);
extern VOS_UINT8 MMA_GetCurrentPhoneMode(VOS_VOID);
extern VOS_UINT32 MN_MSG_Decode_UsimMsg(
    VOS_UINT8                           *pucData,
    VOS_UINT32                          ulLen,
    MN_MSG_SUBMIT_LONG_STRU             *pstLongSubmit
);

extern VOS_VOID  MN_CALL_GetCallInfoList(
    TAF_UINT8                           *pucNumOfCalls,
    MN_CALL_INFO_STRU                   *pstCallInfos
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

#endif /* end of AtOamInterface.h */

