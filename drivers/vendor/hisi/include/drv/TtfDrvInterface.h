

#ifndef __TTFDRVINTERFACE_H__
#define __TTFDRVINTERFACE_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TtfLinkInterface.h"

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
  7 STRUCT����
*****************************************************************************/
enum TTF_BLK_MEM_STATE_ENUM
{
    TTF_BLK_MEM_STATE_FREE,       /*���ڴ�δ����������ͷ�*/
    TTF_BLK_MEM_STATE_ALLOC,      /*���ڴ�������*/

    TTF_BLK_MEM_STATE_BUTT
};
typedef unsigned int TTF_BLK_MEM_STATE_ENUM_UINT32;

typedef struct
{
    TTF_BLK_MEM_STATE_ENUM_UINT32   enMemStateFlag;
    unsigned int                    ulAllocTick;        /* CPU tick when alloc or free */
    unsigned short                  usAllocFileId;      /* File ID when alloc or free */
    unsigned short                  usAllocLineNum;     /* File Line when alloc or free */
    unsigned short                  usTraceFileId;      /* File ID when traced */
    unsigned short                  usTraceLineNum;     /* File Line when traced */
    unsigned int                    ulTraceTick;        /* CPU tick when traced */
} TTF_BLK_MEM_DEBUG_ST;

typedef struct
{
    unsigned int    aulGroupCnt[4];    /* �� TTF_BLK_MEM_CNT Ƭ TTF_MEM �ڴ����Ϊ 4 ��,
                                        �ֱ��¼��ǰ�������� [0, TTF_BLK_MEM_CNT/4-1],
                                        [TTF_BLK_MEM_CNT/4, TTF_BLK_MEM_CNT/2-1],
                                        [TTF_BLK_MEM_CNT/2, 3*TTF_BLK_MEM_CNT/4-1],
                                        [3*TTF_BLK_MEM_CNT/4, TTF_BLK_MEM_CNT] ��Χ�Ĵ��� */
    unsigned int    ulMaxCnt;    /* ��¼ʹ�õ� TTF_MEM ��ֵ */
} TTF_BLK_MEM_CNT_ST;

typedef struct _TTF_MEM_ST
{
    TTF_NODE_ST                     stNode;
    unsigned char                   ucPoolId;       /*���ڴ�������һ���ڴ�� */
    unsigned char                   ucClusterId;    /*���ڴ���������һ������*/
    unsigned char                   ucReserve[2];
    struct _TTF_MEM_ST             *pNext;          /* �����ݵ���һ�� */
    unsigned short                  usType;         /* �ڴ����ͣ�DYN��BLK��EXT���� */
    unsigned short                  usLen;          /* �������ݵ��ܳ��ȣ�����һ��ȫ����ʹ�� */
    unsigned short                  usUsed;         /* �Ѿ�ʹ�õ����ݳ���   */
    unsigned short                  usApp;          /* ʹ���߿���ʹ�õ����� */

    TTF_BLK_MEM_DEBUG_ST           *pstDbgInfo;

    unsigned char                  *pOrigData;      /* ��¼���ݵ�ԭʼָ�� */
    unsigned char                  *pData;          /* ������ݵ�ָ�룬������ָ��ṹ��������ڴ� */
    void                           *pExtBuffAddr;   /* ����extern���͵��ڴ��ַ�����ͷ� */
    unsigned long                   ulForCds[1];    /*Ԥ����CDSʹ�ã�GUģ���ó�ʼ��*/

#if( FEATURE_LTE == FEATURE_ON )
    unsigned long                   ulForLte[6];    /*Ԥ����LTEʹ�ã�GUģ���ó�ʼ��*/
    #endif
} TTF_MEM_ST;


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

#endif /* end of TtfDrvInterface.h */

