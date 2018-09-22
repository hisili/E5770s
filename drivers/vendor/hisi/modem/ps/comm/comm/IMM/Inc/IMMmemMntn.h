

#ifndef __IMMMEMMNTN_H__
#define __IMMMEMMNTN_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "product_config.h"

#if ( FEATURE_ON == FEATURE_SKB_EXP )
#include "IMMmem.h"
#else
#include "IMMmem_Intra.h"
#endif

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


enum IMM_MNTN_CHECK_POOL_LEAK_TYPE_ENUM
{
    IMM_MNTN_CHECK_POOL_LEAK_TYPE_USDCNT             = 0,
    IMM_MNTN_CHECK_POOL_LEAK_TYPE_OVERTIME,
    IMM_MNTN_CHECK_POOL_LEAK_TYPE_BUTT
};
typedef VOS_UINT8 IMM_MNTN_CHECK_POOL_LEAK_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����    : IMM_OM_EVENT_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : �¼��ϱ�ID
*****************************************************************************/
enum IMM_OM_EVENT_ID_ENUM
{
    IMM_EVENT_BLK_MEM_USED_INFO             = 0X0101,   /* _H2ASN_MsgChoice TTF_OM_EVENT_BLK_MEM_USED_INFO_STRU */
    IMM_EVENT_BUTT
};
typedef VOS_UINT16 IMM_OM_EVENT_ID_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : IMM_OM_EVENT_USED_BLK_MEM_INFO_STRU
 Э����  :
 ASN.1���� :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulAllocTick;        /* CPU tick when alloc or free */
    VOS_UINT16                      usAllocFileId;      /* File ID when alloc or free */
    VOS_UINT16                      usAllocLineNum;     /* File Line when alloc or free */
    VOS_UINT32                      ulTraceTick;        /* CPU tick when traced */
    VOS_UINT16                      usTraceFileId;      /* File ID when traced */
    VOS_UINT16                      usTraceLineNum;     /* File Line when traced */
    VOS_UINT8                       aucMemData[4];
}IMM_BLK_MEM_TRACE_INFO_STRU;


typedef struct
{
    VOS_UINT8                                   ucPoolId;
    VOS_UINT8                                   ucRes[3];
    IMM_MEM_USED_INFO_TRIG_TYPE_ENUM_UINT8      enTrigType;
    VOS_UINT8                                   ucNo;
    VOS_UINT16                                  usRptCnt;
    VOS_UINT32                                  ulTotalUsedCnt;
    IMM_BLK_MEM_TRACE_INFO_STRU                 astBlkMemTraceInfo[1];
}IMM_OM_EVENT_BLK_MEM_USED_INFO_STRU;


enum IMM_MEM_MSG_ID_ENUM
{
    ID_IMM_MEM_LEAK_INFO_IND            = 0x315,  /* _H2ASN_MsgChoice IMM_MEM_LEAK_INFO_IND_MSG */

    ID_IMM_MEM_LEAK_ENUM_BUTT
};
typedef VOS_UINT16  IMM_MEM_MSG_ID_ENUM_UINT16;



typedef struct
{
    VOS_MSG_HEADER                                /* ��Ϣͷ */        /* _H2ASN_Skip */
    IMM_MEM_MSG_ID_ENUM_UINT16          enMsgID;  /* ��Ϣ���� */      /* _H2ASN_Skip */
    VOS_UINT8                           aucReserve[2];
}IMM_MEM_LEAK_INFO_IND_MSG;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID IMM_MntnInit( VOS_VOID );
extern VOS_VOID IMM_MntnRptPoolLeakInfo(VOS_VOID);


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

#endif /* end of IMMmemMntn.h */
