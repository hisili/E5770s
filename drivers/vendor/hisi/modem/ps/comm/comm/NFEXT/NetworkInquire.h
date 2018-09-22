/*******************************************************************************
  Copyright   : 2005-2010, Huawei Tech. Co., Ltd.
  File name   : NetworkInquire.h
  Version     : V300R002
  Date        : 2011-11-23
  Description :
  History     :
  1. Date:2011-11-23
     Author: w68271
     Modification:Create
*******************************************************************************/

#ifndef __NETWORK_INQUIRE_H__
#define __NETWORK_INQUIRE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "NetWInterface.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*================================================*/
/* ��ֵ�궨�� */
/*================================================*/
#define MAX_RST_BUF                          (1011)         /*һ�����Ķ�ȡ����*/
#define READ_SIZE_PER_TIME                   (1)            /*��������Ԫ�صĴ�С*/
#define MAX_TIMER_LEN                        (0x7FFFFFFF)
#define WAIT_KO_READY_ONE_TIME_LEN           (5)
#define MAX_WAIT_KO_READY_TIMES              (10)

/*================================================*/
/* ���ܺ����궨�� */
/*================================================*/
#define NW_INQUIRE_ARRAY_SIZE(x)    (sizeof(x)/sizeof(x[0]))
#define EXC(x)                      NW_ShellExc(x)
typedef void NW_InquireFunc(void);

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
enum NW_INQUIRE_RETURN_ENUM
{
        NW_INQUIRE_ERROR          = 0,
        NW_INQUIRE_OK             = 1,
        NW_INQUIRE_BUTT
};

typedef int NW_INQUIRE_RETURN;

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
typedef struct
{
    NETWORK_INQUIRE_CONFIG_STRU stInquireCfg;
}NETWORK_INQUIRE_ENTITY_STRU;

typedef struct
{
    unsigned int             ulMask;
    NW_InquireFunc          *pInquireFunc;
} NW_INQUERY_MASK_FUNC_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern int NW_InquireInit(int *fd);
extern int NW_EstHandlerForTimer(struct sigaction *sa);
extern void NW_DoInquire(void);
extern void NW_InquireIfconfig(void);
extern void NW_InquireArp(void);
extern void NW_InquireRoute(void);
extern void NW_InquireNetstate(void);
extern void NW_InquireNat(void);
extern void NW_ShellExc(char* cmd);
extern void NW_ProcessThread(void);
extern int NW_DeviceInit(int *fd);
extern void NW_DeviceRelease(int *fd);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* NetworkInquire.h */

