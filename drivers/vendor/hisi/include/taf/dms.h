

#ifndef __DMS_H__
#define __DMS_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "DrvInterface.h"
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define DMS_LOG_STATIC_BUF_NUM          (16)
#define DMS_LOG_STATIC_ONE_BUF_SIZE     (5120)

#define NVE_AT_SERVER_INDEX             (294)
#define NVE_READ_OPERATE                (1)
#define NVE_WRITE_OPERATE               (0)

/* ͨ���Ͽ�����֪ͨ����
 */
#define DMS_DISNNECT                    (0)
#define DMS_CONNECT                     (1)

#define DMS_VCOM_OM_CHAN_TL_CTRL        (DMS_OM_CHAN_LTE_CTRL)
#define DMS_VCOM_OM_CHAN_TL_DATA        (DMS_OM_CHAN_LTE_DATA)
#define DMS_VCOM_OM_CHAN_GU_DATA        (DMS_OM_CHAN_GU_DATA)
#define DMS_VCOM_OM_CHAN_BUTT           (DMS_OM_CHAN_BUTT)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/* ���µ�ö��ֵ��������޸�*/
typedef enum
{
    EN_DMS_BEARER_TCP_20248 = 0,
    EN_DMS_BEARER_TCP_20249 ,
    EN_DMS_BEARER_UDP,
    EN_DMS_BEARER_ETH_UDP,
    EN_DMS_BEARER_USB_EP,
    EN_DMS_BEARER_USB_COM1_DIAG_CTRL,
    EN_DMS_BEARER_USB_COM2_DIAG_APP,
    EN_DMS_BEARER_USB_COM3_GU,
    EN_DMS_BEARER_USB_COM4_AT,
    EN_DMS_BEARER_USB_COM_CTRL,
    EN_DMS_BEARER_UART,
    EN_DMS_BEARER_USB_NCM,
    EN_DMS_BEARER_LAST
} DMS_PHY_BEAR_ENUM;

typedef enum
{
    EN_DMS_CHANNEL_DIAG = 0,            /* channel identifier, DIAG
 */
    EN_DMS_CHANNEL_AT,                  /* channel identifier, AT
 */
    EN_DMS_CHANNEL_GU,
    EN_DMS_CHANNEL_LAST
} DMS_LOGIC_CHAN_ENUM;


typedef enum
{
    EN_STATIC_BUF_STA_IDLE = 0,
    EN_STATIC_BUF_STA_BUSY,
    EN_STATIC_BUF_STA_BUTT
} ENUM_DMS_BUF_STATUS;

typedef enum
{
    EN_DMS_DYMIC_BUF_TYP = 0,
    EN_DMS_STATIC_BUF_TYP,
    EN_DMS_BUF_BUTT
} ENUM_DMS_BUF_TYP;

typedef enum
{
    EN_DMS_AT_CLIENT_ACM  = 0x01,
    EN_DMS_AT_CLIENT_CTRL = 0x41,
    EN_DMS_AT_CLIENT_UART,
    EN_DMS_AT_CLIENT_NCM,
    EN_DMS_AT_CLIENT_TCP,
    EN_DMS_AT_CLIENT_LAST
} DMS_AT_CLIENT_ENUM;


typedef enum
{

    EN_SDM_DMS_VCOM1_OPEN,
    EN_SDM_DMS_VCOM1_OPEN_ERR,
    EN_SDM_DMS_VCOM2_OPEN,
    EN_SDM_DMS_VCOM2_OPEN_ERR,
    EN_SDM_DMS_VCOM_AT_OPEN,
    EN_SDM_DMS_VCOM_AT_OPEN_ERR,
    EN_SDM_DMS_VCOM_CTRL_OPEN,
    EN_SDM_DMS_VCOM_CTRL_OPEN_ERR,
    EN_SDM_DMS_VCOM1_CLOSE,
    EN_SDM_DMS_VCOM1_CLOSE_ERR,
    EN_SDM_DMS_VCOM2_CLOSE,
    EN_SDM_DMS_VCOM2_CLOSE_ERR,
    EN_SDM_DMS_VCOM_AT_CLOSE,
    EN_SDM_DMS_VCOM_AT_CLOSE_ERR,
    EN_SDM_DMS_VCOM_CTRL_CLOSE,
    EN_SDM_DMS_VCOM_CTRL_CLOSE_ERR,
    EN_SDM_DMS_INIT,
    EN_SDM_DMS_INIT_ERR,
    EN_SDM_DMS_DISABLE,
    EN_SDM_DMS_DISABLE_ERR,
    EN_SDM_DMS_VCOM1_EVT,
    EN_SDM_DMS_VCOM2_EVT,
    EN_SDM_DMS_VCOM_AT_EVT,
    EN_SDM_DMS_VCOM1_WRT,
    EN_SDM_DMS_VCOM1_WRT_SUCC,
    EN_SDM_DMS_VCOM1_WRT_CB,
    EN_SDM_DMS_VCOM1_WRT_CB_ERR,
    EN_SDM_DMS_VCOM2_WRT,
    EN_SDM_DMS_VCOM2_WRT_SUCC,
    EN_SDM_DMS_VCOM2_WRT_CB,
    EN_SDM_DMS_VCOM2_WRT_CB_ERR,
    EN_SDM_DMS_VCOM_AT_WRT,
    EN_SDM_DMS_VCOM_AT_WRT_SUSS,
    EN_SDM_DMS_VCOM_CTRL_WRT,
    EN_SDM_DMS_VCOM_CTRL_WRT_SUSS,
    EN_SDM_DMS_VCOM_AT_WRT_CB,
    EN_SDM_DMS_VCOM_AT_WRT_CB_ERR,
    EN_SDM_DMS_VCOM_CTRL_WRT_CB,
    EN_SDM_DMS_VCOM_CTRL_WRT_CB_ERR,
    EN_SDM_DMS_DECODE_PACKET_SEND,
    EN_SDM_DMS_DECODE_PACKET_SEND_FAIL,
    EN_SDM_DMS_NCM_SEND_TO_DRV,
    EN_SDM_DMS_NCM_SEND_TO_DRV_SUCC,

    EN_SDM_DMS_UDI_READ_START,
    EN_SDM_DMS_UDI_READ_END,

    EN_SDM_DMS_SOCKET_RECV_ERROR,
    EN_SDM_DMS_SOCKET_SEND_ERROR,

    EN_SDM_DMS_SOCKET_ACP,
    EN_SDM_DMS_SOCKET_CLOSE,
    EN_SDM_DMS_SOCKET_RECV,
    EN_SDM_DMS_SOCKET_SEND,
    EN_SDM_DMS_TCP_RECONNECT,
    EN_SDM_DMS_TCP_RECONNECT_ERR,
    EN_SDM_DMS_SOCKET_CLOSE_FAIL,

    EN_SDM_DMS_DEBUG_INFO_MAX
} DMS_DEBUG_MSG_ID_ENUM;

enum PDP_STATUS_ENUM
{
    PDP_STATUS_DEACT                    = 0,
    PDP_STATUS_ACT                      = 1,
    PDP_STATUS_BUTT
};
typedef VOS_UINT32 PDP_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö������: DMS_CHAN_EVT_ENUM
 ö��˵��: ͨ���¼�ö��
*****************************************************************************/
enum DMS_CHAN_EVT_ENUM
{
    DMS_CHAN_EVT_CLOSE                  = 0,
    DMS_CHAN_EVT_OPEN,

    DMS_CHAN_EVT_BUTT
};
typedef VOS_UINT32 DMS_CHAN_EVT_ENUM_UINT32;

/*****************************************************************************
 ö������: DMS_OM_CHAN_ENUM
 ö��˵��: ͨ������ö��
*****************************************************************************/
enum DMS_OM_CHAN_ENUM
{
    DMS_OM_CHAN_LTE_CTRL                = 0,
    DMS_OM_CHAN_LTE_DATA,
    DMS_OM_CHAN_GU_DATA,

    DMS_OM_CHAN_BUTT
};
typedef VOS_UINT32 DMS_OM_CHAN_ENUM_UINT32;


/*****************************************************************************
  4 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_UINT32  ulCalledNum;  /* ���ô���������Ϣ����,���߱����ú����Ƿ񱻵���
 */
    VOS_UINT32 ulRserved1;   /* ������λ�û�������,HAL_DIAG_SYS_DEBUG_ENUM����
 */
    VOS_UINT32 ulRserved2;   /* �������⺬���������,HAL_DIAG_SYS_DEBUG_ENUM����
 */
    VOS_UINT32 ulRserved3;   /* �������⺬���������,HAL_DIAG_SYS_DEBUG_ENUM����
 */
    VOS_UINT32 ulRtcTime;    /* �������ִ�й���ʱ��
 */
} DMS_DEBUG_INFO_TBL_STRU;


typedef struct
{
    VOS_INT32  lOperatRet;    /* 0:��ȡ�ɹ�     -1:��ȡʧ�� */
    VOS_UINT32 ulNvValue;     /* 0:��atserver   1:��atserver */
} DMS_DEBUG_AT_SERV_NV_STRU;


typedef struct
{
    DMS_PHY_BEAR_ENUM aenPhyChan;
    DMS_AT_CLIENT_ENUM enAtClientID;
    VOS_BOOL bRegister;                             /*TRUEΪ�Ѿ����ע�ᣬFALSE ��δע��
 */
} DMS_PHY_CLIENT_TABLE_STRU;


typedef VOS_UINT32 (*DMS_READ_DATA_PFN)(DMS_AT_CLIENT_ENUM enClientId, VOS_UINT8 * pDataBuf, VOS_UINT32 ulLen);

typedef VOS_VOID (*DMS_CONNECT_STA_PFN)(VOS_UINT8 flag);

typedef struct
{
    VOS_UINT8* buf;
    ENUM_DMS_BUF_STATUS enBusy;
} DMS_BUF_STA_STRU;


typedef struct
{
    ENUM_DMS_BUF_TYP enBufType;
    DMS_BUF_STA_STRU stBufSta[DMS_LOG_STATIC_BUF_NUM];
} DMS_STATIC_BUF_STRU;


/* PDP״̬�ϱ�����ʹ�õĽṹ��*/
typedef struct
{
    unsigned long                    ulspeed;             /* �����ٶȣ���λbps */
    PDP_STATUS_ENUM_UINT32           enActiveSatus;       /* ��������0Ϊ�ɹ�������Ϊʧ�� */
} NAS_PRO_STRU;


extern VOS_VOID dms_Debug(DMS_DEBUG_MSG_ID_ENUM ulType,\
                     VOS_UINT32 ulRserved1, VOS_UINT32 ulRserved2, VOS_UINT32 ulRserved3);


#define DMS_DEBUG_SDM_FUN(enType,ulRserved1,ulRserved2,ulRserved3)  \
dms_Debug(enType,ulRserved1,ulRserved2,ulRserved3)

extern VOS_UINT32 dms_WriteData(DMS_LOGIC_CHAN_ENUM enDmsLogicChan,VOS_UINT8 ucQueId, VOS_UINT8* aucDataBuf, VOS_UINT32 usLen);
extern VOS_VOID dms_Init(VOS_VOID);
extern VOS_VOID dms_VcomCtrlAtTask(VOS_VOID);
extern VOS_VOID dms_AtPcuiTask(VOS_VOID);
extern  VOS_VOID  Dms_FreeStaticBuf( VOS_UINT8 * buf);
extern   VOS_UINT8* Dms_GetStaticBuf(VOS_UINT32 ulLen);
extern  VOS_BOOL Dms_IsStaticBuf(VOS_UINT8 *buf);
extern  VOS_VOID Dms_StaticBufInit(VOS_VOID);
extern  VOS_VOID dms_DiagVcomTask(VOS_VOID);

/* Added by L60609 for AT Project��2011-10-17,  Begin*/
/* c64416 for AT unite
 */
typedef int (*USB_NAS_BRK)
(
    void
);

typedef int (*USB_NAS_AT_CMD_RECV)
(
    unsigned char *pBuff,   /*ָ��AT����ָ��*/
    unsigned short usLen    /*AT�����*/
);

typedef unsigned long (*USB_NAS_GET_WWAN_MODE)	/*��ȡ��ǰ����ģʽcdma/wcdma*/
(
    void
);

#define DMS_COM_STATUS_CALLBACK_REGI(uPortNo,pCallback)   NULL

extern VOS_INT32 DMS_ACMRecvFuncReg(pComRecv pCallback);

#define DMS_COM_RCV_CALLBACK_REGI(uPortNo,pCallback) DMS_ACMRecvFuncReg(pCallback)

extern int DMS_NCMExtFuncReg(USB_NAS_BRK connectBrk, USB_NAS_AT_CMD_RECV atCmdRcv);

#define DMS_USB_NAS_REGFUNC(brkFunc, atRecvFunc, getWWANMode)\
                  DMS_NCMExtFuncReg(brkFunc, atRecvFunc)

extern VOS_INT32 Dms_WriteAtData(VOS_UINT8 ucPortNo, VOS_UINT8* pData, VOS_UINT16 uslength);

#define DMS_COM_SEND(uPortNo,pData,uslength) Dms_WriteAtData(uPortNo,pData,uslength)

extern signed long DMS_NCMStatusChangeReg(NAS_PRO_STRU * pPdpStru);

#define DMS_USB_NAS_STATUS_CHANGE(pPdpStru) DMS_NCMStatusChangeReg(pPdpStru)

extern VOS_VOID Dms_NcmProcCbReg(USBNdisStusChgFunc connectBrk,USB_NAS_AT_CMD_RECV atCmdRcv);

/* Added by L60609 for AT Project��2011-10-17,  End*/

extern VOS_VOID dmsAtPcuiTaskSetSleepFlag(VOS_BOOL ucSleepFlag);
extern VOS_BOOL dmsAtPcuiTaskGetSleepFlag(VOS_VOID);
extern VOS_VOID dmsAtCtrlTaskSetSleepFlag(VOS_BOOL ucSleepFlag);
extern VOS_BOOL dmsAtCtrlTaskGetSleepFlag(VOS_VOID);

extern VOS_UINT32 dms_UdiRead(DMS_PHY_BEAR_ENUM enCOM, VOS_UINT8 * ucRedBuf, VOS_UINT32 ulToReadSize, VOS_UINT32 * pulRealySize);
extern VOS_BOOL dms_GetPortHandle(DMS_PHY_BEAR_ENUM enChan);
extern VOS_UINT32 dmsVcomAtPcuiOpen(VOS_VOID);
extern VOS_UINT32 dmsVcomCtrolOpen(VOS_VOID);
extern VOS_UINT32 dmsVcomAtPcuiClose(VOS_VOID);
extern VOS_UINT32 dmsVcomCtrlClose(VOS_VOID);

extern VOS_UINT32 dms_NcmCfg(VOS_VOID);
extern VOS_UINT32 dms_NcmClose(VOS_VOID);
extern VOS_UINT32 dms_NcmSendData(VOS_UINT8 *pData, VOS_UINT32 ulLen);
extern VOS_UINT32 dms_VcomWriteAsync(VOS_UINT32 VcomId ,VOS_UINT8 *pucDataBuf,VOS_UINT32 ulLen);
extern VOS_UINT32 writeAtData(VOS_UINT32 ulClientId, VOS_UINT8 *aucDataBuf, VOS_UINT32 ulLen);

extern DMS_CONNECT_STA_PFN dmsGetConnStaFun(VOS_VOID);
extern VOS_VOID dms_UsbDisableEvtProc(VOS_VOID);
extern VOS_VOID dms_UsbEnableEvtProc(VOS_VOID);
extern DMS_READ_DATA_PFN dmsGetReadFun(VOS_VOID);
extern VOS_VOID dms_SetConnectStaCallback(DMS_CONNECT_STA_PFN pfnReg);


/*****************************************************************************
 �� �� ��  : DMS_OpenHsicPort
 ��������  : C51�汾HSIC ��ά�ɲ�ͨ���򿪽ӿڣ��ṩ��GUģ��OMģ��ʹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0-�ɹ�;����-ʧ��
 ****************************************************************************/
extern VOS_UINT32 DMS_OpenHsicPort(VOS_VOID);


/*****************************************************************************
 �� �� ��  : DMS_GetHsicPortStatus
 ��������  : ��ȡHSIC�ڴ�״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0-δ��״̬;1-��״̬
 ****************************************************************************/
extern VOS_UINT32 DMS_GetHsicPortStatus(VOS_VOID);

extern VOS_VOID Dms_SetNdisChanStatus(ACM_EVT_E enStatus );


typedef VOS_UINT32 (*DMS_OM_CHAN_DATA_READ_CB_FUNC)(DMS_OM_CHAN_ENUM_UINT32 enChan, VOS_UINT8 *pucData, VOS_UINT32 ulLength);
typedef VOS_VOID (*DMS_OM_CHAN_EVENT_CB_FUNC)(DMS_OM_CHAN_ENUM_UINT32 enChan, DMS_CHAN_EVT_ENUM_UINT32 enEvt);

/*****************************************************************************
 �� �� ��  : DMS_RegOmChanDataReadCB
 ��������  : ע��OMͨ�����ݽ��ջص�
 �������  : enChan --- �߼�ͨ��
             pFunc  --- ����ָ��
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
*****************************************************************************/
VOS_UINT32 DMS_RegOmChanDataReadCB(DMS_OM_CHAN_ENUM_UINT32 enChan, DMS_OM_CHAN_DATA_READ_CB_FUNC pFunc);


/*****************************************************************************
 �� �� ��  : DMS_RegOmChanEventCB
 ��������  : ע��OMͨ���¼����ջص�
 �������  : enChan --- �߼�ͨ��
             pFunc  --- ����ָ��
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
*****************************************************************************/
VOS_UINT32 DMS_RegOmChanEventCB(DMS_OM_CHAN_ENUM_UINT32 enChan, DMS_OM_CHAN_EVENT_CB_FUNC pFunc);


/*****************************************************************************
 �� �� ��  : DMS_WriteOmData
 ��������  : дOMͨ������
 �������  : enChan   --- �߼�ͨ��
             pucData  --- ���ݵ�ַ
             ulLength --- ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
*****************************************************************************/
VOS_UINT32 DMS_WriteOmData(DMS_OM_CHAN_ENUM_UINT32 enChan, VOS_UINT8 *pucData, VOS_UINT32 ulLength);


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /*__DMS_H__*/

