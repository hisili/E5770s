

#ifndef __DIAG_PORT_H__
#define __DIAG_PORT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "osm.h"

#include "SOCPInterface.h"
#include "SCMProc.h"
#include "AtAppVcomInterface.h"
#include "msp_errno.h"
#include "diag_debug.h"
#include "socp_lfix_chan.h"
#include "DrvInterface.h"
#include "diag_cmd_param_plugin.h"
#include "blist.h"
#include "dms.h"

#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
#define DIAG_FD_ISSET(d, set)     (HI_FD_ISSET(d, set))
#define DIAG_FD_SET(d, set)       (HI_FD_SET(d, set))
#define DIAG_FD_CLR(d, set)       (HI_FD_CLR(d, set))
#define DIAG_FD_ZERO(set)         (HI_FD_ZERO(set))

#define DIAG_PORT_READ_LEN     1024
#define DIAG_PORT_READ_SLEEP_TIME  50

#define DIAG_DISCONN 0
#define DIAG_CONN 1

#define DIAG_SOCP_SEND_SIZE_MAX  1024*8

#define DIAG_DATA_READ_BUFFER_SIZE      4*1024
#define DIAG_DATA_MAX_BUFFER_COUNT      16


#if (FEATURE_ON == FEATURE_VCOM_EXT)
/*APP VCOM TL log����������ͨ��*/
#define DIAG_APPVCOM_CHAN_CTRL          DMS_VCOM_OM_CHAN_TL_CTRL
#define DIAG_APPVCOM_CHAN_APP           DMS_VCOM_OM_CHAN_TL_DATA
#else
/*��֤���룬��ʵ������*/
#define DIAG_APPVCOM_CHAN_CTRL          DMS_VCOM_OM_CHAN_BUTT
#define DIAG_APPVCOM_CHAN_APP           DMS_VCOM_OM_CHAN_BUTT
#endif



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
typedef VOS_VOID (*DIAG_PORT_CONNECT_STA_PFN)(VOS_UINT8 flag);



/*****************************************************************************
  4 Enum
*****************************************************************************/
typedef enum
{
    EN_DIAG_SOCKET_BEARER_TCP_20248 = 0,
	EN_DIAG_USB_BEARER_DIAG_CTRL,
	EN_DIAG_USB_BEARER_DIAG_APP,
	EN_DIAG_HSIC_BEARER_DIAG_CTRL,
	EN_DIAG_HSIC_BEARER_DIAG_APP,
	EN_DIAG_VCOM_BEABER_DIAG_CTRL,
	EN_DIAG_VCOM_BEABER_DIAG_APP,
    EN_DIAG_SD_BEARER_DIAG,
	EN_DIAG_PORT_BEARER_LAST
} DIAG_PORT_PHY_BEAR_ENUM;


typedef enum
{
    DIAG_LOG_PORT_USB = 0,
    DIAG_LOG_PORT_VCOM,
    DIAG_LOG_PORT_SD,
    DIAG_LOG_PORT_HSIC,
    DIAG_LOG_PORT_SOCKET,
    DIAG_LOG_PORT_BUTT
}DIAG_LOG_SAVE_ENUM;

typedef enum
{
	EN_NO_HDLC_DATA =0,
	EN_HDLC_DATA,
	EN_HDLC_DATA_LAST
}HDLC_DATA_ENUM;

typedef enum
{
    EN_PORT_INIT_FAIL,
    EN_PORT_INIT_SUCC,
    EN_PORT_INIT_BUTT
}ENUM_PORT_INIT_STATE;

typedef enum
{
    PORT_SWITCH_OFF,
    PORT_SWITCH_ON
}ENUM_PORT_SWITCH_ONOFF;

typedef enum
{
	EN_DIAG_SEND_LOG_TO_USB= 0,
	EN_DIAG_SEND_LOG_TO_SD,
	EN_DIAG_SEND_LOG_BUTT
} ENUM_DMS_LOG_SEND_TYPE;

typedef enum
{
	EN_TCP_PORT_DIAG = 0, // DIAG
	EN_TCP_PORT_FULL
} DIAG_TCPIP_PORT_ENUM;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/

typedef struct
{
	VOS_INT32  slPortHandle;            /*PORT���*/
	VOS_UINT8  ucChanStat;              /*ͨ����ǰ״̬*/
	VOS_UINT8  ucHdlcFlag;				/*0 ��ʾ��HDLC���ݣ�1��ʾ��HDLC����*/
	VOS_UINT8  ucReserve[2];
	VOS_UINT32 ulDecodeSrcChanId;		/*����Դͨ��ID*/
	VOS_UINT32 ulCodeDesChanId;   		/*����Ŀ��ͨ��ID*/
	VOS_UINT32 ulRecivBufLen;
    VOS_UINT32 ulInitStat;              /*ͨ����ʼ��״̬*/
    VOS_UINT32 ulSwitchStat;            /*����״̬*/
} DIAG_PORT_STAT_INFO_STRU;

typedef struct
{
	DIAG_PORT_CONNECT_STA_PFN pFnConnCallBack;
	DIAG_PORT_PHY_BEAR_ENUM ancPort;
	VOS_BOOL  ucPortSleepFlag ;
    VOS_BOOL  ulTraceDebugSw;
} DIAG_PORT_CTRL_INFO_STRU;


typedef struct
{
	ENUM_DMS_LOG_SEND_TYPE	enSendLogType;
	VOS_UINT32	   ulPeriod;				   /*����ʱ�䣬HSO�·��ĵ�λΪ���ӣ�����ת��������� */
	VOS_UINT64	   ulStorageLogSize;	       /*HSO�·�����MBΪ��λ������ת�����ֽڼ���*/
	VOS_UINT64	   StartTime ;				   /* ��ʼʱ��*/
	VOS_UINT64	   StorageTotalSize;           /*�Ѵ洢�������ܳ���*/
	VOS_UINT64		MaxFileSize;               /*���Դ洢����󳤶�*/
	VOS_UINT32		ulFileNum;                 /*��ǰĿ¼���ļ�����*/
	VOS_UINT32		ulCurrenFileSize;          /*��ǰ����д����ļ��Ĵ�С*/
	VOS_INT32       CurrentFileFd;             /*��ǰ���ڲ������ļ����*/
	VOS_UINT32		ulStartFlag;
    VOS_UINT32      ulMinFileNum;              /*��ǰĿ¼����С�ļ����к�*/
} DIAG_SEND_LOG_CTRL_INFO_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern DIAG_PORT_STAT_INFO_STRU    g_diagPort[EN_DIAG_PORT_BEARER_LAST];
extern DIAG_PORT_CTRL_INFO_STRU    g_diagPort_ctrl;

#define DIAG_PORT_GET_CONN_CALLBACK()            (g_diagPort_ctrl.pFnConnCallBack)
#define DIAG_PORT_GET_CONN_PORT()                (g_diagPort_ctrl.ancPort)
#define DIAG_PORT_SLEEP_FLAG()                   (g_diagPort_ctrl.ucPortSleepFlag)
#define DIAG_PORT_PORT_SWITCH(enPort) \
    do { g_diagPort_ctrl.ancPort = enPort; } while(0);
#define DIAG_PORT_SET_SLEEP_FLAG(b) \
    do { g_diagPort_ctrl.ucPortSleepFlag = b;} while(0);


#define DIAG_PORT_GET_HANDLE(enPort)             (g_diagPort[enPort].slPortHandle)
#define DIAG_PORT_GET_STATE(enPort)              (g_diagPort[enPort].ucChanStat)
#define DIAG_PORT_GET_INIT(enPort)               (g_diagPort[enPort].ulInitStat)
#define DIAG_PORT_GET_SWITCH(enPort)             (g_diagPort[enPort].ulSwitchStat)
#define DIAG_PORT_GET_DECODE_SRC(enPort)         (g_diagPort[enPort].ulDecodeSrcChanId)
#define DIAG_PORT_GET_CODE_DES(enPort)           (g_diagPort[enPort].ulCodeDesChanId)

#define DIAG_PORT_HANDLE_SWITCH(enPort,switch) \
    do { g_diagPort[enPort].slPortHandle = switch; } while(0);
#define DIAG_PORT_INIT_STATE_SWITCH(enPort,switch) \
    do { g_diagPort[enPort].ulInitStat   = switch; } while(0);
#define DIAG_PORT_CHAN_STATE_SWITCH(enPort,switch) \
    do { g_diagPort[enPort].ucChanStat   = switch; } while(0);

#define diag_TraceDebug(pdata,len) \
    if(g_diagPort_ctrl.ulTraceDebugSw == TRUE) \
    {\
        VOS_UINT32 i;\
        diag_printf("<%s> datalen : 0x%x\n",__func__,len); \
        for(i=0;i<len;i++)\
        {\
            diag_printf("%02x ",*((VOS_CHAR*)pdata+i));\
        }\
        diag_printf("\n");\
    };

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*sd */
ENUM_DMS_LOG_SEND_TYPE diag_GetLogSendType(VOS_VOID);
VOS_UINT32 diag_StorDataToSD(VOS_UINT8* ucBuf , VOS_UINT32 ulBufLen);
VOS_UINT32 diag_SetLogCtrlInfo(DIAG_CMD_SET_LPD_MODE_REQ_STRU* pstLdpReq);

 /*socket tcp/ip*/
VOS_UINT32 diag_TcpIpInit(VOS_VOID);
VOS_UINT32 diag_TcpSendData(DIAG_TCPIP_PORT_ENUM enTcpPort,VOS_UINT8 *pcData, VOS_UINT32 usDataLen, VOS_UINT32 * pusWrtLen);
VOS_VOID diag_TcpPortLock(DIAG_TCPIP_PORT_ENUM enTcpPort);
VOS_VOID diag_TcpPortUnLock(DIAG_TCPIP_PORT_ENUM enTcpPort);
VOS_VOID diag_CloseSocket(DIAG_TCPIP_PORT_ENUM enTcpPort);



VOS_UINT32 diag_SocpCodeDesDataProc(SOCP_CODER_DST_ENUM_U32 enChanID,VOS_UINT8 *pucData, VOS_UINT8 *pucPHYData,VOS_UINT32 ulSize);

VOS_UINT32 diag_PortInit(VOS_VOID);
VOS_VOID diag_PortSetConnStaCB(DIAG_PORT_CONNECT_STA_PFN pfnReg);

VOS_VOID diag_PortTask(VOS_VOID);


VOS_VOID diag_PortEvtCB(ACM_EVT_E  ulEvt,DIAG_PORT_PHY_BEAR_ENUM enPort);
VOS_VOID diag_PortWrtCB (DIAG_PORT_PHY_BEAR_ENUM enPort,VOS_CHAR* pDoneBuff, VOS_INT s32DoneSize);
VOS_VOID diag_PortRdCB(DIAG_PORT_PHY_BEAR_ENUM enPort);
VOS_UINT32 diag_PortClose(DIAG_PORT_PHY_BEAR_ENUM enPort);
VOS_UINT32 diag_PortOpen(DIAG_PORT_PHY_BEAR_ENUM enPort,UDI_ACM_DEV_TYPE devid,\
    VOS_VOID * pEvtCB,VOS_VOID* pWrtCB,VOS_VOID* pRdCB);

VOS_UINT32 diag_UsbInit(VOS_VOID);
VOS_UINT32 diag_HiscInit(VOS_VOID);
VOS_UINT32 diag_SdInit(VOS_VOID);
VOS_UINT32 diag_VcomInit(VOS_VOID);
VOS_UINT32 diag_SocketInit(VOS_VOID);


VOS_VOID diag_BindListenTcpSocket(VOS_VOID);
VOS_VOID diag_AcceptRecvFromSocket(VOS_VOID);

VOS_UINT32 diag_VcomWriteSync(DIAG_PORT_PHY_BEAR_ENUM enPort,
                                 VOS_UINT32 ulChan,
                                 VOS_UINT8 *pucDataBuf,VOS_UINT32 ulLen);

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
VOS_VOID diag_PortAddToDataBuf(DIAG_PORT_PHY_BEAR_ENUM enPort, VOS_UINT8 * data, VOS_UINT32 dataSize);
extern VOS_UINT32 diag_PortDataBufIsEmpty(VOS_VOID);
#endif
/*****************************************************************************
  9 OTHERS
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

#endif /* end of diag_port.h */

