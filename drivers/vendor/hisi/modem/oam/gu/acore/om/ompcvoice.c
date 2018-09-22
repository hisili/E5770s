

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "omringbuffer.h"
#include "omprivate.h"
#include "cpm.h"
#include "OmCodecInterface.h"
#include "OmApp.h"
#include "hpamailboxdef.h"
#include "DspInterface.h"
/* HIFI ���� */
#include "HifiOmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*lint -e767 �޸���:��� 00128685;������:���� 51137;ԭ��:Log��ӡ */
#define    THIS_FILE_ID        PS_FILE_ID_OM_PC_VOICE_C
/*lint +e767 �޸���:��� 00128685;������:���� 51137; */


#if (FEATURE_ON == MBB_PCVOICE)
#define OM_PCV_BUF_SIZE                         (320 * 6 * 2)
#else
/* ���տ�����640ÿ֡��С ��֧�� V3R3*/
#define OM_PCV_BUF_SIZE                         (640*6*2)
#endif /* MBB_PCVOICE END */

#define OM_PCV_PORT_PCSC                        (3)

/*��ȡ����ʹ��λ*/
#define OM_PCV_HOOK_ENABLE                      (0x010000)
#define OM_PCV_USB_OM_ENABLE                    (0x010400)
#define OM_PCV_OM_MED_ENABLE                    (0x010100)
#define OM_PCV_MED_OM_ENABLE                    (0x010200)

#define OM_PCV_OM_MED_BIT                       (8)
#define OM_PCV_MED_OM_BIT                       (9)
#define OM_PCV_USB_OM_BIT                       (10)

/*EventID:�����쳣*/
#define OM_APP_PCV_EXCEPTION_IND                (0x01)
/*EventID:ringbuf��*/
#define OM_APP_PCV_BUF_FULL_IND                 (0x02)
/*EventID:DSP PLL�µ�*/
#define OM_APP_PCV_DSP_PLL_OFF                  (0x03)
#define OM_APP_PCV_QUNUE_FULL                   (0x04)

/*eventID = 0x05�����Ѿ�ʹ�� */
#define OM_APP_PCV_MED_OM_LEN                   (0x20)
#define OM_APP_PCV_OM_USB_RET                   (0x21)
#define OM_APP_PCV_READ_NV_FAIL                 (0x22)
#define OM_APP_PCV_MAX_MSG_NUM                  (50)

/*HOOK�����ϱ�͸����ϢPrimID*/
#define OM_APP_VOICE_HOOK_IND                   (0xf0fe)

/* ͨ��10�����յ�500֡ */
#define OM_PCV_RCVDATA_TIMES_IN_10S             (500)

/* ÿ10���ӣ�ERRLOG�����̵Ķ���������*/
#define OM_PCV_RBUF_FULL_TIMES_IN_10S           (50)

/*�ṹOM_PCV_TRANS_IND_STRU, sizeof(->ulSn)+ sizeof(ulTimeStamp)
 + sizeof(usPrimID) + sizeof(usReserved) + sizeof(ulFrameTick) +
 sizeof(usHookTarget) + sizeof(usDataLen)*/
#define OM_PCV_TRANS_SIZE                      (20)


#define OM_PCV_RINGBUF_TO_ADDR(StartAddr) \
    ((VOS_UINT32)&(((OM_PCV_RINGBUFFER_STRU*)(StartAddr))->stRingBuffer.pToBuf))

#define OM_PCV_RINGBUF_FROM_ADDR(StartAddr) \
    ((VOS_UINT32)&(((OM_PCV_RINGBUFFER_STRU*)(StartAddr))->stRingBuffer.pFromBuf))

#define OM_PCV_RINGBUF_BUF_ADDR(StartAddr) \
        ((VOS_UINT32)&(((OM_PCV_RINGBUFFER_STRU*)(StartAddr))->stRingBuffer.buf))

typedef struct
{
    VOS_UINT32                          ulProtectWord1;     /*������ 0x55AA55AA*/
    VOS_UINT32                          ulProtectWord2;     /*������ 0x5A5A5A5A*/
    OM_RING                             stRingBuffer;
    VOS_UINT32                          ulProtectWord3;     /*������ 0x55AA55AA*/
    VOS_UINT32                          ulProtectWord4;     /*������ 0x5A5A5A5A*/
}OM_PCV_RINGBUFFER_STRU;

typedef struct
{
    VOS_UINT32                          ulMailBoxAddr;      /* ��������ͷ��ַ */
    VOS_UINT32                          ulBufPhyAddr;       /* �������ݵ������ַ */
    VOS_UINT32                          ulBufVirtAddr;      /* �������ݵ������ַ */
}OM_PCV_ADDR_INFO_STRU;

typedef struct
{
    VOS_UINT32 ulRcvUsbSize;
    VOS_UINT32 ulPutSize;
    VOS_UINT32 ulRcvDspSize;
}OM_PCV_DEBUGGING_INFO_STRU;

typedef struct
{
    VOS_UINT8   ucFuncType;
    VOS_UINT8   ucReserved;
    VOS_UINT16  usLength;
    VOS_UINT32  ulSn;
    VOS_UINT32  ulTimeStamp;
    VOS_UINT16  usPrimID;            /*����MED�ӿ��ļ������������ݳ�Ա*/
    VOS_UINT16  usReserved;
    VOS_UINT32  ulFrameTick;
    VOS_UINT16  usHookTarget;
    VOS_UINT16  usDataLen;
}OM_PCV_TRANS_IND_STRU;

typedef struct
{
    VOS_UINT32  ulStatus;
    VOS_UINT32  ulPort;
    VOS_UINT32  ulCurrentStatus;
    VOS_UINT32  ulIntSlice;
    VOS_UINT32  ulErrSlice;
}OM_PCV_LOG_STRU;


typedef struct
{
    VOS_UINT32  ulDataErr;              /*�����������ݴ�λ��ERRLOGд���*/
    VOS_UINT32  ulFullErr;              /*���������쳣��ERRLOGд���    */
    VOS_UINT32  ulRcvNum;               /*��¼10���������յ�����֡��Ŀ  */
    VOS_UINT32  ulFullNum;              /*��¼10���ڷ��������Ĵ���      */
    VOS_UINT32  ul10sFlag;              /*��һ��10����                */
}OM_PCV_ERRLOG_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16  usPrimId;
    VOS_UINT16  usReserve;
    VOS_UINT32  ulStatus;               /* �������� */
    VOS_UINT32  ulPort;                 /* �˿ںţ�Ŀǰֻ֧�ֶ˿�2 */
}OM_PCV_COM_CFG_REQ;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16  usPrimId;
    VOS_UINT16  usReserve;
    VOS_UINT32  ulPcvHookFlag;
}OM_PCV_TRACE_CFG_REQ;

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*����PC VOICE����ͨ��״̬*/
VOS_UINT32                      g_ulPcvStatus = OM_PCV_CHANNEL_CLOSE;
VOS_UINT8                       g_ucPcvComPort = VOS_NULL_BYTE;
/*PC VOICE(USB->OM->DSP)���λ�����ƿ�*/
OM_PCV_RINGBUFFER_STRU          g_PcvRBufOmToDsp;
/*PC VOICE(DSP->OM->USB)���λ�����ƿ�*/
OM_PCV_RINGBUFFER_STRU          g_PcvRBufDspToOm;

OM_PCV_ADDR_INFO_STRU           g_stPcvOmToDspAddr;

OM_PCV_ADDR_INFO_STRU           g_stPcvDspToOmAddr;

/* ring buffer����ͷ��Ϣ(���ݷ���: USB -> COMM -> VOICE -> PHY -> ����) */
COMM_VOICE_RING_BUFFER_CONTROL_STRU  g_stRingBufferControlTXAddr;

/* ring buffer����ͷ��Ϣ(���ݷ���: USB <- COMM <- VOICE <- PHY <- ����) */
COMM_VOICE_RING_BUFFER_CONTROL_STRU  g_stRingBufferControlRXAddr;

/* the semaphore which be used to wake up PC voice transmit task */
VOS_UINT32                      g_ulPcvTransmitSem;

/* ����cs errorlog��¼�����״̬�ʹ��� */
OM_PCV_ERRLOG_STRU              g_stErrLogFlag;
/*�������ݹ�ȡ��־
* ��16λ: 0--�ر����ݹ�ȡ; 1--�����ݹ�ȡ
* bit8           ��ȡ��8    (OM --> DSP)
* bit9           ��ȡ��9    (DSP -->OM)
* bit10          ��ȡ��10   (USB-->OM)
*/
VOS_UINT32                      g_ulPcvHookFlag = 0;

OM_PCV_DEBUGGING_INFO_STRU      g_stPcvDebuggingInfo;

VOS_UINT32                      g_ulPcvPortMap[]= {OMRL_UART,
                                                   OMRL_UART,
                                                   OMRL_USB_OM,
                                                   OMRL_USB_AT,
                                                   OMRL_UART,
                                                   OM_PCV_PORT_PCSC
                                                  };

VOS_UINT32                      g_ulUsbHookFrameSN =0;

VOS_UINT32                      g_ulOmHookFrameSN =0;

OM_PCV_LOG_STRU                 g_stPcvLog;

extern VOS_BOOL                 g_GUOmOnCtrlPort;

VOS_VOID OM_PcvSendEvent(VOS_UINT16 usEventId, VOS_VOID* pData, VOS_UINT32 ulLen);

extern VOS_UINT32 GU_OamAppSendDataSync(VOS_UINT8 *pucData, VOS_UINT32 ulDataLen);
extern VOS_UINT32 GU_OamAppSendData(VOS_UINT8 *pucData, VOS_UINT32 ulDataLen);

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 Function   : OM_Read32Reg
 Description: read 32bit data from DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 32bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT32 OM_Read32Reg( VOS_UINT32 ulRegAddr )
{
    if ( 0 != (ulRegAddr & 0x03) )/* not 4byte aligned */
    {
        LogPrint1("OM_Read32Reg Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        return 0;
    }

    return *(volatile VOS_UINT32 *)ulRegAddr;
}

/*****************************************************************************
 Function   : OM_Write32Reg
 Description: write 32bit data to DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 32bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID OM_Write32Reg( VOS_UINT32 ulRegAddr, VOS_UINT32 ulRegVal)
{
    if ( 0 != (ulRegAddr & 0x03) )/* not 4byte aligned */
    {
        LogPrint1("OM_Write32Reg Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        return;
    }

    *(volatile VOS_UINT32 *)ulRegAddr = ulRegVal;
}

/*****************************************************************************
 Function   : OM_Read16Reg
 Description: read 16bit data from DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 16bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT16 OM_Read16Reg( VOS_UINT32 ulRegAddr )
{
    if ( 0 != (ulRegAddr & 0x01) )/* not 2byte aligned */
    {
        LogPrint1("OM_Read16Reg Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        return 0;
    }

    return *(volatile VOS_UINT16 *)ulRegAddr;
}

/*****************************************************************************
 Function   : OM_Write16Reg
 Description: write 16bit data to DSP & BBP
 Input      : ulRegAddr -- address of DSP & BBP
            : ulRegVal -- 16bit data
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID OM_Write16Reg( VOS_UINT32 ulRegAddr, VOS_UINT16 usRegVal)
{
    if ( 0 != (ulRegAddr & 0x01) )/* not 2byte aligned */
    {
        LogPrint1("OM_Write16Reg Address: 0x%x not aligned.\r\n",(VOS_INT)ulRegAddr);
        return;
    }

    *(volatile VOS_UINT16 *)ulRegAddr = usRegVal;
}



VOS_VOID OM_PcvHookInd(VOS_UCHAR* pucBuf, VOS_UINT16 usLen, VOS_UINT16 usBit, VOS_UINT32 ulFrameTick)
{
    OM_PCV_TRANS_IND_STRU         * pstOmToAppMsg;

    pstOmToAppMsg = (OM_PCV_TRANS_IND_STRU *)VOS_MemAlloc(ACPU_PID_PCVOICE, DYNAMIC_MEM_PT, sizeof(OM_PCV_TRANS_IND_STRU) + usLen);

    if (VOS_NULL_PTR == pstOmToAppMsg)
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PcvHookInd: VOS_AllocMsg failure.\n");
        return;
    }

    VOS_MemCpy((VOS_UINT8*)pstOmToAppMsg + sizeof(OM_PCV_TRANS_IND_STRU), (VOS_VOID*)pucBuf, usLen);

    pstOmToAppMsg->ucFuncType     = OM_TRANS_FUNC;
    pstOmToAppMsg->usPrimID       = OM_APP_VOICE_HOOK_IND;

    OM_AcpuAddSNTime(&(pstOmToAppMsg->ulSn), &(pstOmToAppMsg->ulTimeStamp));

    /* ��ȡ���bitmap */
    pstOmToAppMsg->usHookTarget   = (VOS_UINT16) BIT_N(usBit);
    pstOmToAppMsg->ulFrameTick    = ulFrameTick;
    pstOmToAppMsg->usDataLen      = usLen;
    pstOmToAppMsg->usLength       = (VOS_UINT16)(OM_PCV_TRANS_SIZE + usLen);

    OM_AcpuSendData((OM_RSP_PACKET_STRU*)pstOmToAppMsg, sizeof(OM_PCV_TRANS_IND_STRU) + usLen);

    VOS_MemFree(ACPU_PID_PCVOICE, pstOmToAppMsg);

    return;
}


VOS_VOID OM_PcvSendEvent(VOS_UINT16 usEventId, VOS_VOID* pData, VOS_UINT32 ulLen)
{
    PS_OM_EVENT_IND_STRU* pstEvent;

    pstEvent = (PS_OM_EVENT_IND_STRU*)VOS_MemAlloc(ACPU_PID_PCVOICE, DYNAMIC_MEM_PT,
                  ((sizeof(PS_OM_EVENT_IND_STRU)-4)+ulLen));

    if (VOS_NULL_PTR == pstEvent)
    {
        PS_LOG(ACPU_PID_PCVOICE, VOS_NULL, PS_PRINT_WARNING, "OM_PcvSendEvent:Alloc mem fail.");
        return;
    }

    pstEvent->ulLength      = 8 + ulLen;
    pstEvent->usEventId     = usEventId;
    pstEvent->usReserved    = 0x0;
    pstEvent->ulModuleId    = ACPU_PID_PCVOICE;
    VOS_MemCpy(pstEvent->aucData, pData, ulLen);

    if(VOS_ERR == OM_AcpuEvent(pstEvent))
    {
        PS_LOG(ACPU_PID_PCVOICE, VOS_NULL, PS_PRINT_WARNING, "OM_PcvSendEvent: send event fail.");
    }

    VOS_MemFree(ACPU_PID_PCVOICE, pstEvent);

    return;
}


VOS_UINT32 OM_PcvInitRBuf(OM_PCV_RINGBUFFER_STRU *pstRingId, OM_PCV_ADDR_INFO_STRU *pstAddrInfo)
{
    pstRingId->ulProtectWord1 = MAIL_BOX_PROTECTWORD_FST;
    pstRingId->ulProtectWord2 = MAIL_BOX_PROTECTWORD_SND;
    pstRingId->ulProtectWord3 = MAIL_BOX_PROTECTWORD_FST;
    pstRingId->ulProtectWord4 = MAIL_BOX_PROTECTWORD_SND;

    pstRingId->stRingBuffer.bufSize = OM_PCV_BUF_SIZE;
    pstRingId->stRingBuffer.buf     = (VOS_CHAR*)pstAddrInfo->ulBufPhyAddr;

    OM_RingBufferFlush(&(pstRingId->stRingBuffer));

    /* ��ringbuf������Ϣд��AHB */
    VOS_MemCpy((VOS_CHAR*)(pstAddrInfo->ulMailBoxAddr),
            (VOS_CHAR*)pstRingId, sizeof(OM_PCV_RINGBUFFER_STRU));

    pstRingId->stRingBuffer.buf     = (VOS_CHAR*)pstAddrInfo->ulBufVirtAddr;

    return (VOS_OK);
}


VOS_UINT32 OM_PcvGetRBufOffset(OM_RING_ID pstRingId, VOS_UINT32 ulAddr)
{
    /*��ȡAHB ringbuf������Ϣ��д��ַ*/
    pstRingId->pToBuf   = (VOS_INT)(OM_Read32Reg(OM_PCV_RINGBUF_TO_ADDR(ulAddr)));

    /*��ȡAHB ringbuf������Ϣ�Ķ���ַ*/
    pstRingId->pFromBuf = (VOS_INT)(OM_Read32Reg(OM_PCV_RINGBUF_FROM_ADDR(ulAddr)));

    if ((pstRingId->pToBuf >= pstRingId->bufSize)
        ||(pstRingId->pFromBuf >= pstRingId->bufSize))
    {
        LogPrint2("OM_PcvGetRBufOffset:Offset Err, pToBuf:%d, pFromBuf:%d\r\n",
            pstRingId->pToBuf, pstRingId->pFromBuf);

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 OM_PcvComRecv(VOS_UINT8 *pucData, VOS_UINT32 ulLen)
{
    VOS_UCHAR*  pcSendData;
    VOS_UINT32  ulSlice;
    VOS_UINT16  usSendLen;
    VOS_UINT16  usFreeSize;
    OAM_MNTN_PCV_ERRLOG_EVENT_STRU      stErrLog;


    if((VOS_NULL_PTR == pucData)||(0 == ulLen))
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PCV_ComRecv, no data!\n");
        return VOS_ERR;
    }

    /* ����ͨ�������У����ÿ10s����50�����ϵĶ����������¼ERRLOG��ÿ��ͨ��ֻ�����¼һ�� */
    g_stErrLogFlag.ulRcvNum++;
    if((0 == g_stErrLogFlag.ulFullErr)
        &&(OM_PCV_RCVDATA_TIMES_IN_10S <= g_stErrLogFlag.ulRcvNum))
    {
        g_stErrLogFlag.ul10sFlag++;

        /* ��һ��10S,����BUF�����������������¼ERRLOG */
        if(1 == g_stErrLogFlag.ul10sFlag)
        {
            g_stErrLogFlag.ulFullNum = 0;
        }

        if(OM_PCV_RBUF_FULL_TIMES_IN_10S < g_stErrLogFlag.ulFullNum)
        {
            g_stErrLogFlag.ulFullErr++;     /*���ERRLOG��д*/

            MNTN_RecordErrorLog(MNTN_OAM_PCV_QUNUE_FULL_EVENT, (void *)&stErrLog,
                                sizeof(OAM_MNTN_PCV_ERRLOG_EVENT_STRU));
        }
        /* ÿ10s���¼�� */
        g_stErrLogFlag.ulRcvNum = 0;
        g_stErrLogFlag.ulFullNum = 0;
    }

    g_stPcvDebuggingInfo.ulRcvUsbSize += (VOS_UINT32)ulLen;

    /*����յ������ֽڣ���Ϊ�쳣�ϱ�*/
    if(VOS_NULL != (ulLen&0x01))
    {
        ulSlice = OM_GetSlice();
        OM_PcvSendEvent(OM_APP_PCV_EXCEPTION_IND, &ulSlice, sizeof(VOS_UINT32));

        /* ÿ��ͨ��ֻ�����¼һ��ERRLOG */
        if(0 != g_stErrLogFlag.ulDataErr)
        {
            return VOS_ERR;
        }

        /* ��Errorlog�ļ��м�¼�յ������ֽ����� */
        g_stErrLogFlag.ulDataErr++;
        MNTN_RecordErrorLog(MNTN_OAM_PCV_DATA_EXCEPTION_EVENT, (void *)&stErrLog,
                                                sizeof(OAM_MNTN_PCV_ERRLOG_EVENT_STRU));

        return VOS_ERR;
    }

    if( OM_PCV_USB_OM_ENABLE == (g_ulPcvHookFlag & OM_PCV_USB_OM_ENABLE) )
    {
        /*Bit10 ��ʾ��ȡUSB-OM����*/
        OM_PcvHookInd( pucData, (VOS_UINT16)ulLen, OM_PCV_USB_OM_BIT,  g_ulUsbHookFrameSN);
        g_ulUsbHookFrameSN++;
    }

    if ( VOS_ERR == OM_PcvGetRBufOffset(&(g_PcvRBufOmToDsp.stRingBuffer), g_stPcvOmToDspAddr.ulMailBoxAddr) )
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PCV_ComRecv, ring buffer be destroy!\n");
        return VOS_ERR;
    }

    usFreeSize = (VOS_UINT16)OM_RingBufferFreeBytes(&(g_PcvRBufOmToDsp.stRingBuffer));

    /*�������ݰ�2 byte����*/
    usFreeSize = usFreeSize & 0xFFFE;
    if(usFreeSize >= (VOS_UINT16)ulLen)
    {
         pcSendData  = (VOS_UCHAR*)pucData;
         usSendLen   = (VOS_UINT16)ulLen ;
         g_stPcvDebuggingInfo.ulPutSize += (VOS_UINT32)usSendLen;
    }
    else
    {
        /*��ʱ���������������ringbuf���������ݶ���*/
        pcSendData = (VOS_UCHAR*)&(pucData[ulLen-usFreeSize]);
        usSendLen  = usFreeSize;
        g_stPcvDebuggingInfo.ulPutSize += (VOS_UINT32)usSendLen;

        /*�������ݶ�ʧ����Ϣ�ϱ�*/
        OM_PcvSendEvent(OM_APP_PCV_BUF_FULL_IND, &g_stPcvDebuggingInfo, sizeof(g_stPcvDebuggingInfo));

        /* ��Errorlog�ļ��м�¼�������ݶ�ʧ*/
        g_stErrLogFlag.ulFullNum++;

    }

    /*���ݿ�����ringbuffer��*/
    (VOS_VOID)OM_RingBufferPut( &(g_PcvRBufOmToDsp.stRingBuffer), (VOS_CHAR*)pcSendData, (VOS_INT)usSendLen );

    VOS_FlushCpuWriteBuf();

    if( OM_PCV_OM_MED_ENABLE == (g_ulPcvHookFlag & OM_PCV_OM_MED_ENABLE) )
    {
        /*Bit8 ��ʾ��ȡOM-MED����*/
        OM_PcvHookInd( (VOS_UCHAR*)pcSendData, usSendLen, OM_PCV_OM_MED_BIT,  g_ulOmHookFrameSN);
        g_ulOmHookFrameSN++;
    }

    /* ����ringbuf������Ϣ��д��ַ */
    OM_Write32Reg(OM_PCV_RINGBUF_TO_ADDR(g_stPcvOmToDspAddr.ulMailBoxAddr),
                    (VOS_UINT32)(g_PcvRBufOmToDsp.stRingBuffer.pToBuf));

    return VOS_OK;
}


VOS_UINT32 OM_PcvOpen(VOS_UINT32 ulPort)
{
    if(OM_PCV_CHANNEL_CLOSE != g_ulPcvStatus)
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PcvTransStatus, channel has been created!\n");
        return VOS_ERR;
    }

    /* ��ʼ������ */
    OM_PcvInitRBuf(&g_PcvRBufOmToDsp, &g_stPcvOmToDspAddr);
    OM_PcvInitRBuf(&g_PcvRBufDspToOm, &g_stPcvDspToOmAddr);

    g_ucPcvComPort = (VOS_UINT8)ulPort;

    CPM_DisconnectPorts(CPM_APP_PORT, CPM_OM_COMM);

    CPM_PhySendReg(CPM_APP_PORT, GU_OamAppSendDataSync);

    CPM_ConnectPorts(CPM_APP_PORT, CPM_PCVOICE_COMM);

    g_ulPcvStatus = OM_PCV_CHANNEL_OPEN;

    return VOS_OK;

}


VOS_UINT32 OM_PcvSwitch(VOS_UINT32 ulPort)
{

    /* �ݲ�֧�� */
    return VOS_ERR;
}


VOS_VOID OM_PcvReleaseAll(VOS_VOID)
{
    /* ע��USB�ص����� */
    if( VOS_NULL_BYTE != g_ucPcvComPort )
    {
        CPM_DisconnectPorts(CPM_APP_PORT, CPM_PCVOICE_COMM);
    }

    CPM_PhySendReg(CPM_APP_PORT, GU_OamAppSendData);

    /* �����ǰOM��û���κ�����˿ڣ����ҵ�ǰû���л���Ctrl�� */
    if((CPM_PORT_BUTT == CPM_QueryPhyPort(CPM_OM_COMM))&&(g_GUOmOnCtrlPort == VOS_TRUE))
    {
        CPM_ConnectPorts(CPM_APP_PORT, CPM_OM_COMM);
    }

    g_ulPcvStatus = OM_PCV_CHANNEL_CLOSE;

    g_ucPcvComPort = VOS_NULL_BYTE;

    /* ERRORLOG ��¼�� */
    VOS_MemSet(&g_stErrLogFlag, 0, sizeof(g_stErrLogFlag));
    return;
}


VOS_UINT32 OM_PcvClose(VOS_UINT32 ulPort)
{
    if(OM_PCV_CHANNEL_OPEN != g_ulPcvStatus)
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PcvTransStatus, no opened channel!\n");
        return VOS_ERR;
    }

    if(g_ucPcvComPort != (VOS_UINT8)ulPort)
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PcvTransStatus, port number is wrong!\n");
        return VOS_ERR;
    }

    OM_PcvReleaseAll();

    return VOS_OK;
}


VOS_UINT32 OM_PcvTransStatus(VOS_UINT32 ulStatus, VOS_UINT32 ulPort)
{
    VOS_UINT32 ulRet;

    /* record debugging info */
    g_stPcvLog.ulStatus = ulStatus;
    g_stPcvLog.ulPort = ulPort;
    g_stPcvLog.ulCurrentStatus = g_ulPcvStatus;
    g_stPcvLog.ulErrSlice = OM_GetSlice();

    switch(ulStatus)
    {
        case OM_PCV_CHANNEL_OPEN:
            ulRet = OM_PcvOpen((VOS_UINT8)g_ulPcvPortMap[ulPort]);
            break;

        case OM_PCV_CHANNEL_CLOSE:
            ulRet =  OM_PcvClose((VOS_UINT8)g_ulPcvPortMap[ulPort]);
            break;

        case OM_PCV_CHANNEL_SWITCH:
            ulRet =  OM_PcvSwitch((VOS_UINT8)g_ulPcvPortMap[ulPort]);
            break;

        default:
            PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "OM_PcvTransStatus, command type is unkown!\n");
            return VOS_ERR;
    }

    if ( VOS_OK != ulRet )
    {
        OM_PcvReleaseAll();

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID OM_PcvTransmitTaskEntry( VOS_VOID )
{
    VOS_UCHAR                          *pucTempBuf;
#if (FEATURE_ON != MBB_PCVOICE)
    VOS_UINT32                          ulRealAddr;
#endif
    VOS_UINT16                          usLen = 0;
    VOS_UINT32                          ulHookFrameSN = 0;
    VOS_INT32                           lRet;

    VOS_MemSet((VOS_CHAR *)(&g_stPcvDebuggingInfo), 0x00, sizeof(OM_PCV_DEBUGGING_INFO_STRU));

    if ( VOS_OK != VOS_SmBCreate( "PCV", 0, VOS_SEMA4_FIFO, &g_ulPcvTransmitSem))
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
            "OM_PcvTransmitTaskEntry: creat sem Err");

        g_ulPcvStatus = OM_PCV_CHANNEL_BUTT;

        return;
    }

    /*������ʱ��������(OM->USB)�����������ʱʹ��*/
#if (FEATURE_ON == MBB_PCVOICE)    /*MBB USB ��BUFFER��ַ������������*/
    pucTempBuf = (VOS_UCHAR  *)VOS_MemAlloc(ACPU_PID_PCVOICE, DYNAMIC_MEM_PT, OM_PCV_BUF_SIZE);
#else
    pucTempBuf = (VOS_UCHAR  *)VOS_UnCacheMemAlloc(OM_PCV_BUF_SIZE, &ulRealAddr);
#endif
    if ( VOS_NULL_PTR == pucTempBuf)
    {
        PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
            "OM_PcvTransmitTaskEntry: alloc mem Err");

        g_ulPcvStatus = OM_PCV_CHANNEL_BUTT;
        OM_DRV_CACHEDMAM_ALLOC_ERROR();
        return;
    }

    /* ERRORLOG ��¼�� */
    VOS_MemSet(&g_stErrLogFlag, 0, sizeof(g_stErrLogFlag));

    for ( ; ; )
    {
        if (VOS_OK != VOS_SmP(g_ulPcvTransmitSem, 0))
        {
            LogPrint("OM_PcvTransmitTaskEntry: VOS_SmP Fail.\r\n");
            continue;
        }
        /* ����ͨ��û�д򿪣���ֱ�ӷ���ʧ�� */
        if(OM_PCV_CHANNEL_OPEN != g_ulPcvStatus)
        {
            LogPrint("OM_PcvTransmitTaskEntry: PLL should not power down. \r\n");
            OM_PcvSendEvent(OM_APP_PCV_DSP_PLL_OFF, &g_stPcvLog, sizeof(g_stPcvLog));
            continue;
        }
        /* ����رգ�֡�����¼��� */
        if ( VOS_NULL == (OM_PCV_HOOK_ENABLE & g_ulPcvHookFlag) )
        {
            ulHookFrameSN = 0;
            g_ulUsbHookFrameSN = 0;
            g_ulOmHookFrameSN = 0;
        }

        /* ��AHB�����ȡringbuf������Ϣ */
        if ( VOS_OK != OM_PcvGetRBufOffset(&(g_PcvRBufDspToOm.stRingBuffer), g_stPcvDspToOmAddr.ulMailBoxAddr) )
        {
           DRV_SYSTEM_ERROR(OAM_UL_R99_AHB_HEAD_ERR, VOS_FILE_ID,
                            __LINE__, (VOS_CHAR*)&g_PcvRBufDspToOm, sizeof(g_PcvRBufDspToOm));
            return;
        }
        usLen = (VOS_UINT16)OM_RingBufferNBytes(&(g_PcvRBufDspToOm.stRingBuffer));

        OM_PcvSendEvent(OM_APP_PCV_MED_OM_LEN, &usLen, sizeof(usLen));
        if( 0 == usLen )    /* ringbuf�������� */
        {
            continue;
        }
        
        /* ��ringbuf�����������ݵ���ʱ������ */
        OM_RingBufferGet(&(g_PcvRBufDspToOm.stRingBuffer), (VOS_CHAR *)pucTempBuf, (VOS_INT)usLen);

        VOS_FlushCpuWriteBuf();

        /* �޸�AHB������ringbuf������Ϣ�еĶ�ָ�� */
        OM_Write32Reg(OM_PCV_RINGBUF_FROM_ADDR(g_stPcvDspToOmAddr.ulMailBoxAddr),
                        (VOS_UINT32)(g_PcvRBufDspToOm.stRingBuffer.pFromBuf));

        g_stPcvDebuggingInfo.ulRcvDspSize += (VOS_UINT32)usLen;

        /* �����������ݵ�USB�˿� */
        lRet = (VOS_INT32)CPM_ComSend(CPM_PCVOICE_COMM, pucTempBuf, usLen);

        OM_PcvSendEvent(OM_APP_PCV_OM_USB_RET, &lRet, sizeof(lRet));

        if( OM_PCV_MED_OM_ENABLE == (g_ulPcvHookFlag & OM_PCV_MED_OM_ENABLE) )
        {
            /* Bit9��ʾ��ȡMED-OM���� */
            OM_PcvHookInd( pucTempBuf, usLen, OM_PCV_MED_OM_BIT,  ulHookFrameSN);
            ulHookFrameSN++;
        }

    }
}

/*****************************************************************************
 Prototype       : OM_PcvIpcIsr
 Description     : PC VOICE IPC Interrupt Process.
 Input           : None
 Output          : None
 Return Value    : None

 History         : ---
    Date         : 2011-10-11
    Author       : g47350
    Modification : Created function
 *****************************************************************************/
VOS_VOID OM_PcvIpcIsr(VOS_VOID)
{
#if (FEATURE_ON == MBB_PCVOICE)
    DRV_IPC_INTDISABLE((IPC_INT_LEV_E)PC_VOICE_RX_DATA_ACPU_IPC_BIT);

    if (OM_PCV_CHANNEL_OPEN == g_ulPcvStatus)
    {
        g_stPcvLog.ulIntSlice = OM_GetSlice();

        /*�յ�0MS�жϻ�֡�жϣ��ͷ��ź���*/
        VOS_SmV(g_ulPcvTransmitSem);
    }

    DRV_IPC_INTENABLE((IPC_INT_LEV_E)PC_VOICE_RX_DATA_ACPU_IPC_BIT);
#else
    /* HIFI ���ƺ�����Ҫ IPC �ж� */

    /*DRV_IPC_INTDISABLE((IPC_INT_LEV_E)PC_VOICE_RX_DATA_ACPU_IPC_BIT);*/

    if (OM_PCV_CHANNEL_OPEN == g_ulPcvStatus)
    {
        g_stPcvLog.ulIntSlice = OM_GetSlice();

        /*�յ�0MS�жϻ�֡�жϣ��ͷ��ź���*/
        VOS_SmV(g_ulPcvTransmitSem);
    }

    /* DRV_IPC_INTENABLE((IPC_INT_LEV_E)PC_VOICE_RX_DATA_ACPU_IPC_BIT);*/
#endif /* MBB_PCVOICE END */
}

/*****************************************************************************
Prototype       : OM_PcvMsgProc
Description     : PCVOICE��Ϣ������.
Input           : pMsg - ָ����Ϣ���ָ��.
Output          : None
Return Value    : None

History         : ---
   Date         : 2011-09-29
   Author       : g47350
   Modification : Created function
*****************************************************************************/
VOS_VOID OM_PcvMsgProc(MsgBlock *pMsg)
{
    OM_PCV_COM_CFG_REQ      *pstComCfg;
    OM_PCV_TRACE_CFG_REQ    *pstTraceCfg;

    /* ����NAS VCģ�鷢��������ͨ��������Ϣ() */
    if (WUEPS_PID_VC == pMsg->ulSenderPid)
    {
        pstComCfg = (OM_PCV_COM_CFG_REQ*)pMsg;

        OM_PcvTransStatus(pstComCfg->ulStatus, pstComCfg->ulPort);
    }
    /* ����HIFI�������������ݹ�ȡ������Ϣ */
    else if (DSP_PID_VOICE == pMsg->ulSenderPid)
    {
        pstTraceCfg = (OM_PCV_TRACE_CFG_REQ*)pMsg;

        if (ID_VOICE_OM_SET_HOOK_IND == pstTraceCfg->usPrimId)
        {
            g_ulPcvHookFlag = pstTraceCfg->ulPcvHookFlag;
        }
    }
    else
    {
        ;
    }

    return;
}

/*****************************************************************************
Prototype       : OM_PcvPidInit
Description     : PCVOICE PID��ʼ������
Input           :  ip - ��ʼ������.
Output          :  None
Return Value    : VOS_OK:�ɹ�������Ϊʧ��

History         : ---
   Date         : 2011-09-29
   Author       : g47350
   Modification : Created function
*****************************************************************************/
VOS_UINT32 OM_PcvPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
#if (FEATURE_ON == MBB_PCVOICE)
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:

            CPM_LogicRcvReg(CPM_PCVOICE_COMM, OM_PcvComRecv);

            DRV_IPC_INTCONNECT((IPC_INT_LEV_E)PC_VOICE_RX_DATA_ACPU_IPC_BIT, (VOIDFUNCPTR)OM_PcvIpcIsr, 0);
            DRV_IPC_INTENABLE((IPC_INT_LEV_E)PC_VOICE_RX_DATA_ACPU_IPC_BIT);

            g_stPcvDspToOmAddr.ulMailBoxAddr = SHD_DDR_P2V(MAILBOX_QUEUE_ADDR(HIFI, ACPU, MSG));
            g_stPcvOmToDspAddr.ulMailBoxAddr = SHD_DDR_P2V(MAILBOX_QUEUE_ADDR(ACPU, HIFI, MSG));

#if (VOS_LINUX == VOS_OS_VER)
            g_stPcvOmToDspAddr.ulBufVirtAddr = (VOS_UINT32)dma_alloc_coherent((struct device *)NULL,
                        OM_PCV_BUF_SIZE, (dma_addr_t*)&g_stPcvOmToDspAddr.ulBufPhyAddr, GFP_KERNEL);

            g_stPcvDspToOmAddr.ulBufVirtAddr = (VOS_UINT32)dma_alloc_coherent((struct device *)NULL,
                        OM_PCV_BUF_SIZE, (dma_addr_t*)&g_stPcvDspToOmAddr.ulBufPhyAddr, GFP_KERNEL);
#else
            /*����uncache�Ķ�̬�ڴ���*/
            g_stPcvOmToDspAddr.ulBufVirtAddr = (VOS_UINT32)DRV_CACHEDMAM_ALLOC( OM_PCV_BUF_SIZE );
            g_stPcvOmToDspAddr.ulBufPhyAddr  = g_stPcvOmToDspAddr.ulBufVirtAddr;

            g_stPcvDspToOmAddr.ulBufVirtAddr = (VOS_UINT32)DRV_CACHEDMAM_ALLOC( OM_PCV_BUF_SIZE );
            g_stPcvDspToOmAddr.ulBufPhyAddr  = g_stPcvDspToOmAddr.ulBufVirtAddr;
#endif

            if ( VOS_NULL_PTR == g_stPcvOmToDspAddr.ulBufVirtAddr )
            {
                PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
                    "OM_PcvTransStatus, Malloc OmToDsp Buffer fail!");

                OM_DRV_CACHEDMAM_ALLOC_ERROR();
                return VOS_ERR;
            }

            if ( VOS_NULL_PTR == g_stPcvDspToOmAddr.ulBufVirtAddr )
            {
                PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
                    "OM_PcvTransStatus, Malloc DspToOm Buffer fail!");

                OM_DRV_CACHEDMAM_ALLOC_ERROR();
                return VOS_ERR;
            }
            return VOS_OK;

        default:
            break;
    }
#else
    /* HIFI ���Ƶ�A�˴����޸� */
    switch(ip)
    {
        case VOS_IP_LOAD_CONFIG:
            CPM_LogicRcvReg(CPM_PCVOICE_COMM, OM_PcvComRecv);

            VOS_MemSet(&g_stRingBufferControlTXAddr, 0, sizeof(COMM_VOICE_RING_BUFFER_CONTROL_STRU));
            g_stPcvOmToDspAddr.ulMailBoxAddr = (VOS_UINT32)&g_stRingBufferControlTXAddr;

            VOS_MemSet(&g_stRingBufferControlRXAddr, 0, sizeof(COMM_VOICE_RING_BUFFER_CONTROL_STRU));
            g_stPcvDspToOmAddr.ulMailBoxAddr = (VOS_UINT32)&g_stRingBufferControlRXAddr;

            /*����uncache�Ķ�̬�ڴ���*/
            g_stPcvOmToDspAddr.ulBufVirtAddr = (VOS_UINT32)VOS_UnCacheMemAlloc(OM_PCV_BUF_SIZE, &g_stPcvOmToDspAddr.ulBufPhyAddr);

            g_stPcvDspToOmAddr.ulBufVirtAddr = (VOS_UINT32)VOS_UnCacheMemAlloc(OM_PCV_BUF_SIZE, &g_stPcvDspToOmAddr.ulBufPhyAddr);

            if ( VOS_NULL_PTR == g_stPcvOmToDspAddr.ulBufVirtAddr )
            {
                PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
                    "OM_PcvTransStatus, Malloc OmToDsp Buffer fail!");

                OM_DRV_CACHEDMAM_ALLOC_ERROR();
                return VOS_ERR;
            }

            if ( VOS_NULL_PTR == g_stPcvDspToOmAddr.ulBufVirtAddr )
            {
                PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
                    "OM_PcvTransStatus, Malloc DspToOm Buffer fail!");

                OM_DRV_CACHEDMAM_ALLOC_ERROR();
                return VOS_ERR;
            }
            return VOS_OK;

        default:
            break;
    }

/* HIFI δ����֮ǰ */
#if 0
    BSP_AXI_SECT_INFO                       stAxiInfo;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            if(BSP_OK != DRV_GET_FIX_AXI_ADDR(BSP_AXI_SECT_TYPE_HIFI, &stAxiInfo))
            {
                PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
                    "OM_PcvPidInit, DRV_GET_FIX_AXI_ADDR Buffer fail!");
                return VOS_ERR;
            }

            CPM_LogicRcvReg(CPM_PCVOICE_COMM, OM_PcvComRecv);

            DRV_IPC_INTCONNECT((IPC_INT_LEV_E)PC_VOICE_RX_DATA_ACPU_IPC_BIT, (VOIDFUNCPTR)OM_PcvIpcIsr, 0);
            DRV_IPC_INTENABLE((IPC_INT_LEV_E)PC_VOICE_RX_DATA_ACPU_IPC_BIT);
/*lint -e413*/
            g_stPcvOmToDspAddr.ulMailBoxAddr = stAxiInfo.ulSectVirtAddr + PC_VOICE_OM_MED_ADDR_OFFSET;
            g_stPcvDspToOmAddr.ulMailBoxAddr = stAxiInfo.ulSectVirtAddr + PC_VOICE_MED_OM_ADDR_OFFSET;
/*lint +e413*/

#if (VOS_LINUX == VOS_OS_VER)
            g_stPcvOmToDspAddr.ulBufVirtAddr = dma_alloc_coherent(NULL,
                        OM_PCV_BUF_SIZE, (dma_addr_t*)&g_stPcvOmToDspAddr.ulBufPhyAddr, GFP_KERNEL);

            g_stPcvDspToOmAddr.ulBufVirtAddr = dma_alloc_coherent(NULL,
                        OM_PCV_BUF_SIZE, (dma_addr_t*)&g_stPcvDspToOmAddr.ulBufPhyAddr, GFP_KERNEL);
#else
            /*����uncache�Ķ�̬�ڴ���*/
            g_stPcvOmToDspAddr.ulBufVirtAddr = (VOS_UINT32)DRV_CACHEDMAM_ALLOC( OM_PCV_BUF_SIZE );
            g_stPcvOmToDspAddr.ulBufPhyAddr  = g_stPcvOmToDspAddr.ulBufVirtAddr;

            g_stPcvDspToOmAddr.ulBufVirtAddr = (VOS_UINT32)DRV_CACHEDMAM_ALLOC( OM_PCV_BUF_SIZE );
            g_stPcvDspToOmAddr.ulBufPhyAddr  = g_stPcvDspToOmAddr.ulBufVirtAddr;
#endif

            if ( VOS_NULL_PTR == g_stPcvOmToDspAddr.ulBufVirtAddr )
            {
                PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
                    "OM_PcvTransStatus, Malloc OmToDsp Buffer fail!");

                OM_DRV_CACHEDMAM_ALLOC_ERROR();
                return VOS_ERR;
            }

            if ( VOS_NULL_PTR == g_stPcvDspToOmAddr.ulBufVirtAddr )
            {
                PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR,
                    "OM_PcvTransStatus, Malloc DspToOm Buffer fail!");

                OM_DRV_CACHEDMAM_ALLOC_ERROR();
                return VOS_ERR;
            }
            return VOS_OK;

        default:
            break;
    }
#endif
#endif /* #if (FEATURE_ON == MBB_PCVOICE)  END */

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : COMM_VOICE_GetPcVoiceRingBuffCtrlAddr
 ��������  : ���RingBuff���ƽṹ��ĵ�ַ
 �������  : enDirection - ���ݷ���
 �������  : ��
 �� �� ֵ  : Ring Buff���ƽṹ��ĵ�ַ(���ַ)
             ��Ring Buff���ƽṹ���ʼ��ʧ���򷵻�VOS_NULL

 ����˵��  : (1) Ring Buff���ƽṹ�����ݶ���ΪCOMM_VOICE_RING_BUFFER_CONTROL_STRU
             (2) Ring Buff���ƽṹ��ȫ�ֱ���������COMM��(Ӧ����2��, �ֱ��������к�������������)
             (3) COMM��Ҫ�ڵ��øýӿں���ǰ���ߵ��øýӿں���ʱ��ʼ��RingBuff���ƽṹ��
*****************************************************************************/
VOS_UINT32 COMM_VOICE_GetPcVoiceRingBuffCtrlAddr(COMM_VOICE_PCVOICE_DATA_DIRECTION_ENUM_UINT32 enDirection)
{
    if (COMM_VOICE_PCVOICE_DATA_DIRECTION_TX == enDirection)
    {
        /* ��ʼ������ */
        OM_PcvInitRBuf(&g_PcvRBufOmToDsp, &g_stPcvOmToDspAddr);

        return (VOS_UINT32)g_stPcvOmToDspAddr.ulMailBoxAddr;
    }

    if (COMM_VOICE_PCVOICE_DATA_DIRECTION_RX == enDirection)
    {
        /* ��ʼ������ */
        OM_PcvInitRBuf(&g_PcvRBufDspToOm, &g_stPcvDspToOmAddr);
        return (VOS_UINT32)g_stPcvDspToOmAddr.ulMailBoxAddr;
    }

    PS_LOG(ACPU_PID_PCVOICE, 0, PS_PRINT_ERROR, "COMM_VOICE_GetPcVoiceRingBuffCtrlAddr, Para is error!\n");

    return VOS_NULL;

}

/*****************************************************************************
 �� �� ��  : COMM_VOICE_TransferPcVoiceRxData
 ��������  : �������з�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK  - ����ɹ�
             VOS_ERR - ����ʧ��

 ����˵��  : (1) VOICE����������д��Ring Buff����øú���֪ͨCOMM�����ݴ�����USB

*****************************************************************************/
VOS_UINT32 COMM_VOICE_TransferPcVoiceRxData(VOS_VOID)
{
    /* �ͷ��ź��� */
    OM_PcvIpcIsr();
    return VOS_OK;
}


VOS_VOID OM_PcvLogShow(VOS_VOID)
{
    vos_printf("\r\n g_ulPcvStatus is   %d", g_ulPcvStatus);
    vos_printf("\r\n g_ucPcvComPort is  %d\r\n", g_ucPcvComPort);

    vos_printf("\r\n g_stErrLogFlag.ulDataErr =  %d", g_stErrLogFlag.ulDataErr);
    vos_printf("\r\n g_stErrLogFlag.ulFullErr =  %d", g_stErrLogFlag.ulFullErr);
    vos_printf("\r\n g_stErrLogFlag.ulRcvNum  =  %d", g_stErrLogFlag.ulRcvNum);
    vos_printf("\r\n g_stErrLogFlag.ulFullNum =  %d", g_stErrLogFlag.ulFullNum);
    vos_printf("\r\n g_stErrLogFlag.ul10sFlag =  %d\r\n", g_stErrLogFlag.ul10sFlag);

    vos_printf("\r\n g_stPcvDebuggingInfo.ulRcvUsbSize =  %d", g_stPcvDebuggingInfo.ulRcvUsbSize);
    vos_printf("\r\n g_stPcvDebuggingInfo.ulPutSize    =  %d", g_stPcvDebuggingInfo.ulPutSize);
    vos_printf("\r\n g_stErrLogFlag.ulRcvNum           =  %d\r\n", g_stPcvDebuggingInfo.ulRcvDspSize);

    vos_printf("\r\n g_stPcvLog.ulStatus        =  %d", g_stPcvLog.ulStatus);
    vos_printf("\r\n g_stPcvLog.ulPort          =  %d", g_stPcvLog.ulPort);
    vos_printf("\r\n g_stPcvLog.ulCurrentStatus =  %d", g_stPcvLog.ulCurrentStatus);
    vos_printf("\r\n g_stPcvLog.ulIntSlice      =  %d", g_stPcvLog.ulIntSlice);
    vos_printf("\r\n g_stPcvLog.ulErrSlice      =  %d\r\n", g_stPcvLog.ulErrSlice);

    return;
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

