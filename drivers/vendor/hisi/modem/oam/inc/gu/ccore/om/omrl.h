/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : OmRl.h
  �� �� ��   : ����
  ��    ��   : ���� 46160
  ��������   : 2008��6��11��
  ����޸�   :
  ��������   : OmRl.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��6��11��
    ��    ��   : ���� 46160
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OMRL_H__
#define __OMRL_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "omringbuffer.h"
#include "pslog.h"
#include "PsTypeDef.h"
#include "om.h"
#include "OmToolInterface.h"
#if((VOS_OS_VER == VOS_LINUX) || (VOS_OSA_CPU == OSA_CPU_ACPU))
#include "PsLogAdapterApp.h"
#else
#include "pslogadapter.h"
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
/* GU datatype */
#define OM_RL_DATATYPE_GU                           (0x1)

/* datatype �ֶγ��� */
#define OM_RL_DATATYPE_LEN                          (0x1)

/* �����·����ݰ��������󳤶� */
#define OM_RL_TOTAL_MSG_MAX_LEN                     (8*1024)


#define OM_RL_HDLC_FRAME                            0x0
#define OM_RL_USB_FRAME                             0x1

/*Indicates current OM's state.*/
#define OM_STATE_IDLE                               0 /*IDLE̬��OM���������빤�߽���ͨ��*/
#define OM_STATE_ACTIVE                             1 /*ACTIVE̬��OM�ܹ���������*/

#define OM_HDLC_MAX_RATE_SIZE                       (2)
#define OM_HDLC_MAX_HEAD_SIZE                       (6)

#define OM_APP_MSG_SEGMENT_HEADER_LENGTH            4
#define APP_OM_HEADER_LENGTH                        4
#define OM_APP_MSG_SEGMENT_LEN                      (4*1024)  /* Modify By Lx SOCP  */
#define OM_APP_SPLIT_MSG_LEN                        (OM_APP_MSG_SEGMENT_LEN + OM_APP_MSG_SEGMENT_HEADER_LENGTH)

/*#define OM_DRV_MAX_IO_LEN                           (OM_APP_MSG_SEGMENT_LEN          \
 */
/*                                                    + sizeof(OM_APP_MSG_SEG_EX_STRU) \
 */
/*                                                    + sizeof(VOS_UINT32))                  tail aaaa5555 */

#define OM_SWITCH_DATA_LEN                          15  /*������·���ͷ���·���ݵĳ���*/
#define OM_SWITCH_REQ_OFFSET                        17  /*�ظ���Ϣ���������������ƫ�Ƴ���*/
#define OM_SWITCH_CRC_OFFSET                        21  /*�ظ���Ϣ����������FCSУ���ƫ�Ƴ���*/

#define OM_USB_EXIST                                1

#define UEPS_PID_OMRL                               WUEAPP_PID_MUX
#define OM_HDLC_DEST_MAX                            ((OM_APP_MSG_SEGMENT_LEN*2) + 6)
/*Buffer length provided the HDLC API*/
#define OM_HDLC_BUF_MAX_LEN                         (OM_APP_SPLIT_MSG_LEN + OM_USB_FRAME_LEN + OM_RL_DATATYPE_LEN + OM_HDLC_FCS_LEN)

/*�ڼ���OM_APP_MSG_SEGMENT_STRU�ṹsizeʱ�����һ���ֽ�*/
#define OM_MSG_SEGMENT_REDUNDANT                    1

#define OM_USB_FRAME_HEAD                           0xaaaa5555
#define OM_USB_FRAME_TAIL                           0x5555aaaa

/* ֧��CBTץLOG */
#define OM_CBT_LOG_ENABLE_FLAG                      0x5a5a5a5a

#define OM_USB_HEAD_LEN                             4
#define OM_USB_TAIL_LEN                             4

/*֡����ΪOM_USB_FRAME_HEAD���� + OM_USB_FRAME_TAIL����*/
#define OM_USB_FRAME_LEN                            (OM_USB_HEAD_LEN + OM_USB_TAIL_LEN)

#define OM_CONFIG_HEAD_SIZE                         (9)       /*3(PC�����ֶ�) + 4(��Ϣ����) + 2(PC�����ֶ�)*/

#define OM_EST_LINK_SIZE                            (24)

#define OM_DATA_MAX_LENGTH                          (0x7FFFFFFF)

extern VOS_UINT32                                   g_ulOmCcpuDbgFlag ;

extern VOS_UINT32                                   g_ulFTMFlag;

/* CCPU ���� DEBUG ��Ϣ */
#define OM_CCPU_DEBUG_TRACE(pucData, ulDataLen, ulSwitch) \
    if(VOS_FALSE != (g_ulOmCcpuDbgFlag&ulSwitch)) \
    { \
        VOS_UINT32 ulOmDbgIndex; \
        vos_printf("\n%s, Data Len: = %d\n", __FUNCTION__, ulDataLen); \
        for (ulOmDbgIndex = 0 ; ulOmDbgIndex < ulDataLen; ulOmDbgIndex++) \
        { \
            vos_printf("%02x ", *((VOS_UINT8*)pucData + ulOmDbgIndex)); \
        } \
        vos_printf("\r\n"); \
    } \

#define OM_BIT_N(num)               (0x01 << (num))

/* ��������OM�Ĵ�ӡ��� */
#ifdef OAM_UT_DEBUG
#define OM_CCPU_RECV_ICC            OM_BIT_N(1)
#else
#define OM_CCPU_RECV_ICC            OM_BIT_N(0)
#endif

#define OM_CCPU_PUT_OM_BUFF         OM_BIT_N(1)

#define OM_CCPU_ERRLOG_RCV          OM_BIT_N(7)
#define OM_CCPU_ERRLOG_PRINT        OM_BIT_N(8)

/* ����ErrLog ��ӡ */
#define OM_CCPU_ERR_LOG(string) \
    if(VOS_FALSE != (g_ulOmCcpuDbgFlag & OM_CCPU_ERRLOG_PRINT)) \
    {\
        vos_printf("%s.\r\n",string);\
    }\

#define OM_CCPU_ERR_LOG1(string, para1) \
    if(VOS_FALSE != (g_ulOmCcpuDbgFlag & OM_CCPU_ERRLOG_PRINT)) \
    {\
        vos_printf("%s %d.\r\n", string, para1);\
    }\

#define OM_CCPU_ERR_LOG2(string, para1, para2) \
    if(VOS_FALSE != (g_ulOmCcpuDbgFlag & OM_CCPU_ERRLOG_PRINT)) \
    {\
        vos_printf("%s %d, %d.\r\n", string, para1, para2);\
    }\

#define OM_GET_SOCP_STATUS                (1)
#define OM_GET_SOCP_DEBUG_INFO            (2)
#define OM_SEND_DEBUG_INFO_MAX_LEN        (2*1024)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum OM_PORT_MODE_ENUM
{
     AT_MODE = 0,
     OM_MODE,
     DIAG_MODE,
     MODE_BUTT
};

typedef VOS_UINT32      OM_PORT_MODE_ENUM_UINT32;

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
    VOS_OM_HEADER
    VOS_UINT8                      aucPara[4]; /*The content*/
}APP_OM_GU_MSG_STRU;


typedef struct
{
    VOS_UINT16      usPacketLen;        /*֡����*/
    VOS_UINT16      usRemainLen;        /*���������Ѿ��е����ݳ���*/
    VOS_UINT8       *pucRemainData;     /*ָ�򻺳�����ָ��*/
}OM_REMAIN_FRAME_STRU;

typedef struct _OM_BUFFER_POOL
{
    struct _OM_BUFFER_POOL  *pstNext;   /*ָ����һ��������*/
    VOS_UINT32              ulLen;      /*�������Ѿ�ʹ�õĳ���*/
    VOS_UINT8               *pucPacket; /*ָ�򻺳���������ڴ�ռ�*/
} OM_BUFFER_POOL;

typedef struct
{
    VOS_UINT32              ulPoolNum;  /*�������ĸ���*/
    OM_BUFFER_POOL          *pstWrite;  /*ָ������д�����ݵĻ�����*/
    OM_BUFFER_POOL          *pstRead;   /*ָ��������ȡ���ݵĻ�����*/
} OM_BUFFER_QUEUE;

/*****************************************************************************
�ṹ��    : OM_CCPU_ICC_REC_SUC_STRU
�ṹ˵��  : CCPU ICCͨ���ɹ����յĿ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulICCOmRecMsgNum;       /*��ǰ���յ�����Ϣ��*/
    VOS_UINT32                      ulICCOmRecLen;          /*��ǰ���յ�����Ϣ����*/
    VOS_UINT32                      ulICCOmRecSlice;        /*��ǰ���յ����һ�����ݵ�ʱ��*/
}OM_CCPU_ICC_REC_SUC_STRU;

/*****************************************************************************
�ṹ��    : OM_CCPU_ICC_REC_FAIL_STRU
�ṹ˵��  : CCPU ICCͨ������ʧ�ܵĿ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                      ulICCOmParaErrNum;      /*��ǰ���յĴ����¼*/
    VOS_UINT32                      ulICCOmRecErrMsgNum;    /*��ǰ���յĴ�������Ϣ��*/
    VOS_UINT32                      ulICCOmRecErrLen;       /*��ǰ���յĴ�������Ϣ����*/
    VOS_UINT32                      ulICCOmRecErrSlice;     /*��ǰ���յĴ�����Ϣ���һ�����ݵ�ʱ��*/
}OM_CCPU_ICC_REC_FAIL_STRU;

/*****************************************************************************
�ṹ��    : OM_ACPU_ICC_SEND_SUC_STRU
�ṹ˵��  : ACPU ICCͨ���ɹ����͵Ŀ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulICCOmSendMsgNum;      /*��ǰ���͵�����Ϣ��*/
    VOS_UINT32                          ulICCOmSendLen;         /*��ǰ���͵�����Ϣ����*/
    VOS_UINT32                          ulICCOmSendSlice;       /*��ǰ���͵����һ�����ݵ�ʱ��*/
}OM_ACPU_ICC_SEND_SUC_STRU;

/*****************************************************************************
�ṹ��    : OM_ACPU_ICC_SEND_FAIL_STRU
�ṹ˵��  : ACPU ICCͨ������ʧ�ܵĿ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulICCOmSendErrNum;      /*��ǰ���͵Ĵ����¼*/
    VOS_UINT32                          ulICCOmSendErrLen;      /*��ǰ���͵Ĵ�������Ϣ����*/
    VOS_UINT32                          ulICCOmSendErrSlice;    /*��ǰ���͵Ĵ�����Ϣ���һ�����ݵ�ʱ��*/
}OM_ACPU_ICC_SEND_FAIL_STRU;

/*****************************************************************************
�ṹ��    : OM_MAINTENANCE_INFO_STRU
�ṹ˵��  : OMģ���ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataLen; /* ���ջ������ݳ��� */
    VOS_UINT32                          ulNum;     /* ���ջ������ݴ��� */
}OM_MAINTENANCE_INFO_STRU;

/*****************************************************************************
�ṹ��    : OM_CCPU_PC_UE_SUC_STRU
�ṹ˵��  : OMģ���������տ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    OM_MAINTENANCE_INFO_STRU            stTotalData;       /* ��¼���յ��������� */
    OM_MAINTENANCE_INFO_STRU            stRealData;        /* ��¼��������omģ������� */
    OM_CCPU_ICC_REC_SUC_STRU            stICCRecSUCInfo;   /* ��¼CCPU�ɹ����յ�ICC���� */
}OM_CCPU_PC_UE_SUC_STRU;

/*****************************************************************************
�ṹ��    : OM_CCPU_PC_UE_FAIL_STRU
�ṹ˵��  : OMģ�����ʧ�ܿ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    OM_MAINTENANCE_INFO_STRU            stParaErrData;     /* ��¼��Ϊ�������󶪵������� */
    OM_MAINTENANCE_INFO_STRU            stSendErrData;     /* ��¼����OMģ��ʱ������������*/
    OM_CCPU_ICC_REC_FAIL_STRU           stICCRecFailInfo;  /* ��¼CCPU����ʧ�ܵ�ICC���� */
}OM_CCPU_PC_UE_FAIL_STRU;

/*****************************************************************************
�ṹ��    : OM_ACPU_PC_UE_RELEASE_INFO_STRU
�ṹ˵��  : OMģ�����������Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRlsAp2Modem;     /* AP��Modem�л� */
    VOS_UINT32                          ulRlsModem2Ap;     /* Modem��AP�л� */
    VOS_UINT32                          ulRlsDrvSuspend;   /* DRV���� */
    VOS_UINT32                          ulRlsPortClose;    /* �˿ڹر� */
    VOS_UINT32                          ulRlsPortSwitch;   /* �˿��л� */
    VOS_UINT32                          ulSlice;           /* ���һ���յ�������ʱ�� */
}OM_ACPU_PC_UE_RELEASE_INFO_STRU;

/*****************************************************************************
�ṹ��    : OM_ACPU_PC_UE_SUC_STRU
�ṹ˵��  : OMģ���������տ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    OM_MAINTENANCE_INFO_STRU            stTotalData;       /* ��¼���յ��������� */
    OM_MAINTENANCE_INFO_STRU            stHdlcDecapData;
    OM_MAINTENANCE_INFO_STRU            stLinkData;        /* ��¼�յ�����·���� */
    OM_MAINTENANCE_INFO_STRU            stCcpuData;        /* ��¼����CCPU������ */
    OM_MAINTENANCE_INFO_STRU            stAcpuData;        /* ��¼����ACPU������ */
    OM_MAINTENANCE_INFO_STRU            stMcuData;         /* ��¼����MCU������ */
    OM_MAINTENANCE_INFO_STRU            stHifiData;        /* ��¼����HIFI������ */
    OM_ACPU_ICC_SEND_SUC_STRU           stICCSendSUCInfo;  /* ��¼ACPU�ɹ����͵�ICC���� */
    OM_MAINTENANCE_INFO_STRU            stRlsData;         /* ��¼���߷��͵�Release���� */
    OM_ACPU_PC_UE_RELEASE_INFO_STRU     stRlsInfo;         /* ��¼Release��Ϣ */
}OM_ACPU_PC_UE_SUC_STRU;

/*****************************************************************************
�ṹ��    : OM_ACPU_PC_UE_FAIL_STRU
�ṹ˵��  : OMģ���쳣���տ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    OM_MAINTENANCE_INFO_STRU            stLostData;         /* ��¼���������� */
    VOS_UINT32                          ulFrameDecapErr;    /* ��¼������֡����Ĵ��� */

    VOS_UINT16                          usPacketLenErr;     /* ��¼����������С��OM_RL_DATATYPE_LEN + OM_USB_FRAME_LEN����Ĵ��� */
    VOS_UINT16                          usLenTooShortErr;   /* ��¼�������ݳ���С�ڷֶ�ͷ�Ĵ������ */
    VOS_UINT16                          usSegLenErr;        /* ��¼�����γ��ȴ������ */
    VOS_UINT16                          usSegNumErr;        /* ��¼��������Ŀ������� */

    VOS_UINT16                          usDatatypeErr;      /* ��¼����datatype�ֶδ������ */
    VOS_UINT16                          usMsgTooLongErr;    /* ��¼�����������Ϣ����8K�Ĵ������ */
    VOS_UINT16                          usCpuIdErr;         /* ��¼����CPU id������� */
    VOS_UINT16                          usNoMemErr;         /* ��¼�����ռ䲻��Ĵ������ */

    VOS_UINT16                          usDataHeadErr;      /* ��¼��������֡ͷ��������� */
    VOS_UINT16                          usMsgLenErr;        /* ��¼������Ϣ���ȴ������ */
    VOS_UINT16                          usMsgSnErr;         /* ��¼������Ϣ��Ŵ������ */
    VOS_UINT16                          usPacketLostErr;    /* ��¼��������ʧ�Ĵ������ */

    VOS_UINT16                          usLinkDataLenErr;   /* ��¼��·��Ϣ���ȴ���Ĵ��� */
    VOS_UINT16                          usLinkStatusErr;    /* ��¼��·�ر�ʱ�յ���Ϣ���Ĵ��� */
    VOS_UINT16                          usAllocMsg;         /* ��¼��Ϣ����ʧ�ܵĴ��� */
    VOS_UINT16                          usRcv;

    OM_ACPU_ICC_SEND_FAIL_STRU          stICCSendFailInfo;  /* ��¼ACPU�ɹ����͵�ICC���� */
}OM_ACPU_PC_UE_FAIL_STRU;

/*****************************************************************************
�ṹ��    : OM_UE_PC_SUC_STRU
�ṹ˵��  : OMģ���������Ϳ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    OM_MAINTENANCE_INFO_STRU            stTotalData;         /* ��¼Э��ջ���͵������� */
    OM_MAINTENANCE_INFO_STRU            stRealSendData;      /* ��¼��������SOCP������ */
    OM_MAINTENANCE_INFO_STRU            stRealRlsData;       /* ��¼�����ͷ�SOCP������ */
    VOS_UINT32                          ulMaxUsedBufSize;    /* ��¼ʹ��buf�����ֵ */
}OM_UE_PC_SUC_STRU;

/*****************************************************************************
�ṹ��    : OM_UE_PC_FAIL_STRU
�ṹ˵��  : OMģ���쳣���Ϳ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    OM_MAINTENANCE_INFO_STRU            stIntData;           /* ��¼��Ϊ�ж��е��ö��������� */
    OM_MAINTENANCE_INFO_STRU            stLostData;          /* ��¼��Ϊ���ִ��󶪵������� */
    OM_MAINTENANCE_INFO_STRU            stLinkErrData;       /* ��¼��Ϊ��·�رն��������� */
    OM_MAINTENANCE_INFO_STRU            stParaErrData;       /* ��¼��Ϊ�������󶪵������� */

    VOS_UINT16                          usSemErr;            /* ��¼��ȡ�ź���ʧ�ܵĴ��� */
    VOS_UINT16                          usRlsRdErr;          /* ��¼��ȡ�ѷ���RDʧ�ܵĴ��� */
    VOS_UINT16                          usRlsMemErr;         /* ��¼��ȡ�ͷŻ������ڴ�ʧ�ܵĴ��� */
    VOS_UINT16                          usBDLackErr;         /* ��¼BD����Ĵ��� */
    VOS_UINT16                          usGetBDErr;          /* ��¼��ȡBDAPI���ش���Ĵ��� */
    VOS_UINT16                          usNoMemErr;          /* ��¼�ڴ治��Ĵ��� */

    VOS_UINT16                          usSendSocpDataErr;   /* ��¼�������ݵ�SOCP����Ĵ��� */
    VOS_UINT16                          usSendAddrErr;       /* ��¼���͵�ַת������ */

    VOS_UINT16                          usRlsAddrErr;        /* ��¼�ͷŵ�ַת������ */
    VOS_UINT16                          usSendInIsrErr;      /* ��¼���ж��з������ݴ������ */
}OM_UE_PC_FAIL_STRU;

/* �ϱ���ά�ɲ�����Ϣ�ṹ�� */
typedef struct
{
    VOS_UINT32                         ulLenth;
    VOS_UINT8                         *pucAddr;

}OM_SEND_DEBUG_INFO_STRU;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/* ��¼CCPU���յ�PC�����ݵ�������Ϣ */
extern OM_CCPU_PC_UE_SUC_STRU                  g_stPcToUeSucRecord;

/* ��¼CCPU���յ�PC�����ݵ��쳣��Ϣ */
extern OM_CCPU_PC_UE_FAIL_STRU                 g_stPcToUeErrRecord;

/*��¼��PC�෢�����ݵ�������Ϣ */
extern OM_UE_PC_SUC_STRU                       g_stUeToPcSucRecord;

/*��¼��PC�෢������ʱ�����ĸ������*/
extern OM_UE_PC_FAIL_STRU                      g_stUeToPcErrRecord;


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32 OMRL_Init(VOS_VOID);
VOS_VOID   OMRL_FlushBuffer(VOS_VOID);
VOS_UINT32 OMRL_MsgSplit(VOS_UINT8 *pucMsg, VOS_UINT16 usMsgLen);
VOS_UINT32 OMRL_UsbFrameInit(VOS_VOID);
VOS_UINT32 OMRL_CcpuReportEvent(VOS_VOID);
VOS_UINT32 OMRL_SendMsg(VOS_UINT8 *pucData, VOS_UINT32 ulSize, VOS_UINT32 ulSenderPid, VOS_UINT32 ulReceiverPid);
VOS_UINT32 OMRL_ReleaseSocpData(VOS_VOID);
VOS_UINT32 OMRL_SendSocpData(VOS_UINT8 *pucHead, VOS_UINT32 ulHeadLen,
                             VOS_UINT8 *pucData, VOS_UINT32 ulDataLen);
VOS_UINT32 OMRL_IsBDEnough(VOS_UINT8 ucMsgCnt);
VOS_UINT32 OMRL_MsgSplit(VOS_UINT8 *pucMsg, VOS_UINT16 usMsgLen);

VOS_UINT32 SCM_GetDebugLogInfoLen(VOS_VOID);
VOS_UINT8* SCM_GetDebugLogInfo(VOS_VOID);

VOS_UINT32 SOCP_GetDebugLogInfoLen(VOS_UINT32  ulType);
VOS_UINT8* SOCP_GetDebugLogInfo(VOS_UINT32  ulType);
VOS_VOID OM_LogShowToFile(VOS_BOOL bIsSendMsg);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif

