

#ifndef __DIAG_BUF_CTRL_H__
#define __DIAG_BUF_CTRL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "DrvInterface.h"
#include  "SOCPInterface.h"


#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/

#if (VOS_LINUX== VOS_OS_VER)
#define DIAG_CODER_SRC_CNF_BUFFER_SIZE               (1024*64)
#define DIAG_CODER_SRC_IND_BUFFER_SIZE               (1024*64*3)
        /*ACPU���CNF����Դ����*/
#define SOCP_CODER_SRC_LOM_CNF SOCP_CODER_SRC_LOM_CNF1
#else
#define DIAG_CODER_SRC_CNF_BUFFER_SIZE               (1024*128)
#define DIAG_CODER_SRC_IND_BUFFER_SIZE               (1024*128*3)
        /*MCPU���CNF����Դ����*/
#define SOCP_CODER_SRC_LOM_CNF SOCP_CODER_SRC_LOM_CNF2
#endif

#if (VOS_LINUX== VOS_OS_VER)
        /*ACPU�����ȼ���ϱ���Դ����*/
#define SOCP_CODER_SRC_LOM_PRECEDENCE_IND SOCP_CODER_SRC_LOM_IND1
#else
        /*MCPU�����ȼ���ϱ���Դ����*/
#define SOCP_CODER_SRC_LOM_PRECEDENCE_IND SOCP_CODER_SRC_LOM_IND2
#endif

#if (VOS_LINUX== VOS_OS_VER)
        /*ACPU�����ȼ���ϱ���Դ����*/
#define SOCP_CODER_SRC_LOM_NORMAL_IND SOCP_CODER_SRC_LOM_IND1
#else
        /*MCPU�����ȼ���ϱ���Դ����*/
#define SOCP_CODER_SRC_LOM_NORMAL_IND SOCP_CODER_SRC_LOM_IND3
#endif

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
typedef enum
{
	DIAG_CODER_SRC_TYPE_CNF = 0,
	DIAG_CODER_SRC_TYPE_IND,
	DIAG_CODER_SRC_TYPE_BUTT
}DIAG_CODER_SRC_TYPE_ENUM;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : DIAG_BUF_CTRL_STRU
 �ṹ˵��  : ����DIAG���������������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_INT32   lAlloc;             /* ָ������ڴ�������׵�ַ��ƫ�Ƶ�ַ */
    VOS_INT32   lRelease;           /* ָ���ͷ��ڴ�������׵�ַ��ƫ�Ƶ�ַ */
    VOS_INT32   lPadding;          /* ��������ڴ�Ĵ�С */
    VOS_INT32   lBufSize;          /* ���滺�����ܴ�С */
    VOS_UINT8   *pucBuf;         /* ָ�򻺳��������׵�ַ */
    VOS_UINT8   *pucRealBuf;     /* ָ�򻺳���ʵ�׵�ַ */
}DIAG_BUF_CTRL_STRU;

/*****************************************************************************
�ṹ��    : DIAG_TO_HSO_FAIL_STRU
�ṹ˵��  : OMģ���쳣���Ϳ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
	VOS_UINT16                          usNoRdNum;           /* ��¼��RD������� */
    VOS_UINT16                          usSemErr;            /* ��¼��ȡ�ź���ʧ�ܵĴ��� */
    VOS_UINT16                          usRlsRdErr;          /* ��¼��ȡ�ѷ���RDʧ�ܵĴ��� */
    VOS_UINT16                          usRlsMemErr;         /* ��¼��ȡ�ͷŻ������ڴ�ʧ�ܵĴ��� */
    VOS_UINT16                          usBDLackErr;         /* ��¼BD����Ĵ��� */
    VOS_UINT16                          usAllocMemErr;       /* ��¼��ȡbuf����Ĵ��� */
    VOS_UINT16                          usNoMemErr;          /* ��¼�ڴ治��Ĵ��� */
    VOS_UINT16                          usSendSocpDataErr;   /* ��¼�������ݵ�SOCP����Ĵ��� */
    VOS_UINT16                          usSendAddrErr;       /* ��¼���͵�ַת������ */
    VOS_UINT16                          usRlsAddrErr;        /* ��¼�ͷŵ�ַת������ */
    VOS_UINT16                          usSendInIsrErr;      /* ��¼���ж��з������ݴ������ */
}DIAG_TO_HSO_FAIL_STRU;
/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern DIAG_BUF_CTRL_STRU                        g_stDiagBufCtrl[DIAG_CODER_SRC_TYPE_BUTT];

/*��¼��PC�෢������ʱ�����ĸ������*/
extern DIAG_TO_HSO_FAIL_STRU                      g_stDiagToHsoErrRecord;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/



extern VOS_UINT8* diag_AllocLogMem(DIAG_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lLen);
extern VOS_UINT32 diag_BufCtrlGlobalInit(VOS_VOID);
extern VOS_UINT8* diag_BuffPhyToVirt(VOS_UINT8 *pucCurPhyAddr, VOS_UINT8 *pucPhyStart, VOS_UINT8 *pucVirtStart, VOS_UINT32 ulBufLen);
extern VOS_UINT8* diag_BuffVirtToPhy(VOS_UINT8 *pucCurVirtAddr, VOS_UINT8 *pucVirtStart, VOS_UINT8 *pucPhyStart, VOS_UINT32 ulBufLen);
extern VOS_UINT32 diag_CreateLogBuf(DIAG_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lBufSize);
extern VOS_UINT8* diag_GetCoderSrcBuf(VOS_UINT32 ulLen,SOCP_CODER_SRC_ENUM_U32 ulChanID);
extern VOS_VOID diag_LockCoderSrcBuf(VOS_VOID);
extern VOS_UINT32 diag_ReleaseLogBuf(SOCP_CODER_SRC_ENUM_U32 ulSrcChanID);
extern VOS_UINT32 diag_ReleaseLogMem(DIAG_BUF_CTRL_STRU *pstBufCtrl, VOS_UINT8 *pAddr, VOS_INT32 lLen);
extern VOS_UINT32 diag_SendCoderSrcToSocp(VOS_UINT8 *pBuf,VOS_UINT32 ulLen, SOCP_CODER_SRC_ENUM_U32 ulCodeSrcId);
extern VOS_VOID diag_UnLockCoderSrcBuf(VOS_VOID);
extern VOS_UINT32 diag_GetBufIndex(SOCP_CODER_SRC_ENUM_U32 ulChanID);
VOS_VOID diag_BufHelp(VOS_VOID);
VOS_VOID diag_BufDebug(VOS_VOID);




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

#endif /* end of diag_buf_ctrl.h */

