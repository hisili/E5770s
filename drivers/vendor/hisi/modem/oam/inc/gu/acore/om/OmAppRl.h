

#ifndef __OMAPPRL_H__
#define __OMAPPRL_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "omrl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
extern VOS_UINT32                          g_ulOmAcpuDbgFlag ;


#define BIT_N(num)          (0x01 << (num))

#define OM_ACPU_RECV_USB        BIT_N(0)
#define OM_ACPU_DISPATCH_MSG    BIT_N(1)
#define OM_ACPU_SEND_SOCP       BIT_N(2)
#define OM_ACPU_SEND_USB        BIT_N(3)
#define OM_ACPU_USB_CB          BIT_N(4)
#define OM_ACPU_DIAG            BIT_N(5)
#define OM_ACPU_ERRLOG_SEND     BIT_N(6)
#define OM_ACPU_ERRLOG_RCV      BIT_N(7)
#define OM_ACPU_ERRLOG_PRINT    BIT_N(8)
#define OM_ACPU_RECV_CBT        BIT_N(9)

#define OM_ACPU_DEBUG_TRACE(pucData, ulDataLen, ulSwitch) \
    if(VOS_FALSE != (g_ulOmAcpuDbgFlag&ulSwitch)) \
    { \
        VOS_UINT32 ulOmDbgIndex; \
        vos_printf("\n%s, Data Len: = %d\n", __FUNCTION__, ulDataLen); \
        for (ulOmDbgIndex = 0 ; ulOmDbgIndex < ulDataLen; ulOmDbgIndex++) \
        { \
            vos_printf("%02x ", *((VOS_UINT8*)pucData + ulOmDbgIndex)); \
        } \
        vos_printf("\r\n"); \
    } \

/* ����ErrLog ��ӡ */
#define OM_ERR_LOG(string) \
    if(VOS_FALSE != (g_ulOmAcpuDbgFlag & OM_ACPU_ERRLOG_PRINT)) \
    {\
        vos_printf("%s.\r\n",string);\
    }\

#define OM_ERR_LOG1(string, para1) \
    if(VOS_FALSE != (g_ulOmAcpuDbgFlag & OM_ACPU_ERRLOG_PRINT)) \
    {\
        vos_printf("%s %d.\r\n", string, para1);\
    }\

#define OM_ERR_LOG2(string, para1, para2) \
    if(VOS_FALSE != (g_ulOmAcpuDbgFlag & OM_ACPU_ERRLOG_PRINT)) \
    {\
        vos_printf("%s %d, %d.\r\n", string, para1, para2);\
    }\

#define USB_MAX_DATA_LEN            (60*1024)   /*USB���͵�������ݳ���*/

#define SOCP_SEND_DATA_PARA_CHECK(enChanID, ulDataLen, pucData) \
    if ((SOCP_CODER_DST_GU_OM != enChanID)\
    || (0 == ulDataLen)\
    || (VOS_NULL_PTR == pucData))\
    {\
        g_stAcpuDebugInfo.ulSocpCBParaErrNum++;\
        return;\
    }\


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
#if (FEATURE_ON == FEATURE_CBT_LOG)
enum
{
    OM_NOT_CBT_MSG,
    OM_CBT_MSG
};
#endif

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
�ṹ��    : OMRL_MSG_COMBINE_INFO_STRU
�ṹ˵��  : OMRLģ����������Ҫ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTotalSegNum;      /* �ܵķֶ��� */
    VOS_UINT8                           ucExpectedSegSn;    /* ��������������õ�����Ϣ����� */
    VOS_UINT16                          usRsv;
    VOS_UINT32                          ulTotalMsgLen;      /* ����������������Ϣ�ܵĳ��� */
    VOS_UINT32                          ulMoveLen;          /* ���������ÿ����һ��Ϣ�����ƫ�� */
    MsgBlock                           *pstWholeMsg;        /*ָ�����������������Ϣ��*/
}OMRL_MSG_COMBINE_INFO_STRU;

/*****************************************************************************
  7 ȫ�ֱ�������
*****************************************************************************/
extern OMRL_MSG_COMBINE_INFO_STRU              g_stMsgCombineInfo;

/* ��¼��pc�ൽue��ʱ��������������Ϣ */
extern OM_ACPU_PC_UE_SUC_STRU                  g_stAcpuPcToUeSucRecord;

/* ��¼���ݴ�pc�ൽue��ʱ�����ĸ������ */
extern OM_ACPU_PC_UE_FAIL_STRU                 g_stAcpuPcToUeErrRecord;

/*��¼��PC�෢�����ݵ�������Ϣ */
extern OM_UE_PC_SUC_STRU                       g_stAcpuUeToPcSucRecord;

/*��¼��PC�෢������ʱ�����ĸ������*/
extern OM_UE_PC_FAIL_STRU                      g_stAcpuUeToPcErrRecord;

/*��¼��ʼʱ��*/
extern VOS_UINT32                              g_ulAcpuLastTick;

/*��¼�ֽڳ���*/
extern VOS_UINT32                              g_ulAcpuLastByteCnt;

extern VOS_UINT32                              g_ulAcpuFTMFlag;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 GU_OamSndPcMsgToCcpu(VOS_UINT8 *pucData, VOS_UINT32 ulSize);

VOS_UINT32 OMRL_AcpuCpuIdToPid(VOS_UINT8 ucCpuId, VOS_UINT32 *pulPid);
VOS_UINT32 OMRL_AcpuMsgDispatch(VOS_VOID);
VOS_UINT32 OMRL_AcpuMsgCombine(VOS_UINT8 *pucData, VOS_UINT16 usLen);
VOS_UINT32 OMRL_AcpuSendMsg(VOS_UINT8 *pucData, VOS_UINT32 ulSize, VOS_UINT32 ulSenderPid, VOS_UINT32 ulReceiverPid);
VOS_UINT32 OMRL_AcpuReportEvent(VOS_VOID);
VOS_UINT32 OMRL_AcpuInit(VOS_VOID);
VOS_UINT32 OMRL_AcpuHdlcInit(VOS_VOID);
VOS_UINT32 OMRL_AcpuNVHdlcInit(VOS_VOID);
VOS_UINT32 OMRL_AcpuUsbFrameInit(VOS_VOID);
VOS_UINT32 OMRL_AcpuHeadProc(VOS_UINT8 *pucData, VOS_UINT32 ulSize);

VOS_UINT32 OMRL_AcpuSendMsg(VOS_UINT8 *pucData, VOS_UINT32 ulSize,
                            VOS_UINT32 ulSenderPid, VOS_UINT32 ulReceiverPid);
VOS_UINT32 OMRL_AcpuReleaseSocpData(VOS_VOID);
VOS_UINT32 OMRL_AcpuSendSocpData(VOS_UINT8 *pucHead, VOS_UINT32 ulHeadLen,
                            VOS_UINT8 *pucData, VOS_UINT32 ulDataLen);
VOS_UINT32 OMRL_AcpuIsBDEnough(VOS_UINT8 ucMsgCnt);
VOS_UINT32 OMRL_AcpuMsgSplit(VOS_UINT8 *pucMsg, VOS_UINT16 usMsgLen);

VOS_VOID   OmAcpuRate(VOS_VOID);

VOS_UINT32 OMRL_AcpuRcvData(VOS_UINT8 *pucData, VOS_UINT32 ulLen);

#if (FEATURE_ON == FEATURE_CBT_LOG)
VOS_UINT32 OMRL_AcpuCBTMsgDispatch(VOS_VOID);
VOS_UINT32 OMRL_AcpuCBTMsgCombine(VOS_UINT8 *pucData, VOS_UINT16 usLen);
VOS_UINT32 OMRL_AcpuCBTHeadProc(VOS_UINT8 *pucData, VOS_UINT32 ulSize);
VOS_INT OMRL_AcpuRcvCBTData(VOS_UINT8 ucDevIndex, VOS_UINT8 *pucData, VOS_UINT32 ulLen);
#endif

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

#endif /* end of OmRl.h */

