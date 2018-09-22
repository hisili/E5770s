

#ifndef __DRV_USB_H__
#define __DRV_USB_H__

#include "drv_comm.h"
#include "drv_udi.h"
#if (FEATURE_ON == MBB_USB)
#include "product_config.h"
#endif

#ifdef __KERNEL__
#include <linux/skbuff.h>
#endif
/* �豸ö�����˿ڸ��� */
#define DYNAMIC_PID_MAX_PORT_NUM        17

typedef  enum
{
    FLOW_CON,     /* ����        */
    PDP_STATUS,   /* PDP������ */
    SIGNAL_LEVEL, /* �ź�ǿ��    */
    PKT_STATICS,  /* ����ͳ��    */
    AT_CMD,       /* AT����      */
    PS_NOTIFY,    /* Notify����  */
    RESERVE       /* ����        */
}NDIS_NOTICE;

typedef unsigned long (*pPCSCFUNC)(unsigned long CmdType, unsigned char *pApdu, unsigned long ApduLen);

/* NV��50091�ṹ�������豸��Ҫö�ٵĶ˿���̬ */
typedef struct
{
    unsigned long ulStatus;
    unsigned char aucFirstPortStyle[DYNAMIC_PID_MAX_PORT_NUM];  /* �豸�л�ǰ�˿���̬ */
    unsigned char aucRewindPortStyle[DYNAMIC_PID_MAX_PORT_NUM]; /* �豸�л���˿���̬ */
    unsigned char reserved[22];
}DRV_DYNAMIC_PID_TYPE_STRU;

typedef enum
{
    WWAN_WCDMA   = 1,/*WCDMAģʽ*/
    WWAN_CDMA    = 2  /*CDMAģʽ*/
}NDIS_WWAN_MODE;

/*�ܽ��źŵĶ���*/
#define IO_CTRL_FC                      (0x02)
#define IO_CTRL_DSR                     (0x20)
#define IO_CTRL_DTR                     (0x01)
#define IO_CTRL_RFR                     (0x04)
#define IO_CTRL_CTS                     (0x10)
#define IO_CTRL_RI                      (0x40)
#define IO_CTRL_DCD                     (0x80)

typedef int  (*pComRecv)(unsigned char  uPortNo, unsigned char* pData, unsigned short uslength);

typedef int  (*pUartRecv)(unsigned char uPortNo, unsigned char* pData, unsigned short uslength);

typedef long (*pUsbStatus)(unsigned char ucStatus);

typedef long  (*pUsbState)(unsigned char ucStatus);

typedef int  (*pComStatusNotify)(unsigned char uStatus);

/* MODEM �ܽ��źŽṹ�嶨��*/
typedef struct tagMODEM_MSC_STRU
{
    BSP_U32 OP_Dtr     :    1;          /*DTR CHANGE FLAG*/
    BSP_U32 OP_Dsr     :    1;          /*DSR CHANGE FLAG*/
    BSP_U32 OP_Cts     :    1;          /*CTSCHANGE FLAG*/
    BSP_U32 OP_Rts     :    1;          /*RTS CHANGE FLAG*/
    BSP_U32 OP_Ri      :    1;          /*RI CHANGE FLAG*/
    BSP_U32 OP_Dcd     :    1;          /*DCD CHANGE FLAG*/
    BSP_U32 OP_Fc      :    1;          /*FC CHANGE FLAG*/
    BSP_U32 OP_Brk     :    1;          /*BRK CHANGE FLAG*/
    BSP_U32 OP_Spare   :    24;         /*reserve*/
    BSP_U8   ucDtr;                     /*DTR  VALUE*/
    BSP_U8   ucDsr;                     /*DSR  VALUE*/
    BSP_U8   ucCts;                     /*DTS VALUE*/
    BSP_U8   ucRts;                     /*RTS  VALUE*/
    BSP_U8   ucRi;                      /*RI VALUE*/
    BSP_U8   ucDcd;                     /*DCD  VALUE*/
    BSP_U8   ucFc;                      /*FC  VALUE*/
    BSP_U8   ucBrk;                     /*BRK  VALUE*/
    BSP_U8   ucBrkLen;                  /*BRKLEN VALUE*/
} MODEM_MSC_STRU, *PMODEM_MSC_STRU,AT_DCE_MSC_STRU;

/*Э��ջBULK���ݽ��ջص��������Ͷ���*/
typedef int (*USB_MODEM_RECV_CALL)
(
    unsigned char ucPortType,          /*�˿ں�*/
    unsigned char ucDlci,                 /*��·��*/
    unsigned char *pData,               /*����ָ��*/
    unsigned short usLen                /*���ݳ���*/
);

/*Э��ջ��Ϣͨ��״̬�仯���ݽ��ջص���������*/
typedef int (*USB_MODEM_AT_Sig)
(
    unsigned char ucPortType,          /*�˿ں�*/
    unsigned char ucDlci,                   /*��·��*/
    MODEM_MSC_STRU* data  /*ָ��MODEM �ܽ��źŽṹ���ָ��*/
);

/*Э��ջ�����������ص�����*/
typedef int (*USB_MODEM_IN_OUT)
(
    unsigned char ucPortType,           /*�˿ں�*/
    unsigned char ucDlci                   /*��·��*/
);

/*Э��ջ�����ܸ��ƺ�������*/
typedef void (*USB_MODEM_COPY)
(
    unsigned char   *pDest,
    unsigned char   *pSrc,
    unsigned long   ulLen
);

typedef struct
{
    unsigned int    GateWayIpAddr;  /* PDP�����ȡ����Զ������IP��ַ      */
    unsigned int    LocalIpAddr;    /* PDP�����ȡ���ķ��䵽MODEM��IP��ַ */
    unsigned int    MaskAddr;       /* �������� */
    unsigned int    speed;          /* �����ٶȣ���λbps */
    unsigned char   ActiveSatus;    /* ��������0Ϊ�ɹ�������Ϊʧ�� */
}NDIS_PDP_STRU,*pNDIS_PDP_STRU;

typedef struct
{
    unsigned int    currentTx;    /* CURRENT_TX */
    unsigned int    currentRx;    /* CURRENT_RX */
    unsigned int    maxTx;        /* MAX_TX */
    unsigned int    maxRx;        /* MAX_RX */
}NDIS_RATE_STRU,*pNDIS_RATE_STRU;

typedef struct
{
    unsigned int     TxOKCount;         /*���Ͱ���*/
    unsigned int     RxOKCount;         /*���հ���*/
    unsigned int     TxErrCount;        /*���ʹ���*/
    unsigned int     RxErrCount;        /*���մ���*/
    unsigned int     TxOverFlowCount;   /*�����������*/
    unsigned int     RxOverFlowCount;   /*�����������*/
    unsigned int     MaxTx;         /*��������*/
    unsigned int     MaxRx;         /*��������*/
} NDIS_PKT_STATISTICS, *pNDIS_PKT_STATISTICS;

typedef struct
{
    unsigned char   *pucAtCmd;          /*ָ��AT�����ָ��*/
    unsigned short   usLen;             /*AT����ĳ���*/
}NDIS_AT_CMD_STRU, *pNDIS_AT_CMD_STRU;

/* �ź��ϱ�����ʹ�õĽṹ��*/
typedef struct
{
    NDIS_NOTICE                 type;
    union
    {
        NDIS_PDP_STRU           pdp;
        NDIS_PKT_STATISTICS     pktStatics;
        unsigned char           flowFlag;   /*  1:���أ�0�������� */
        int                     dbm;
        NDIS_AT_CMD_STRU        atCmd;
    }NDIS_STATUS_DATA;
} NDIS_PRO_STRU, *pNDIS_PRO_STRU;

typedef int (*USB_NDIS_RECV_CALL)
(
    unsigned char *pData, /* ���ջ�����ָ��,����ΪIP���� */
    unsigned short usLen  /* ���ݳ��� */
);

typedef int (*USB_NDIS_BRK)
(
    void
);

typedef int (*USB_NDIS_EST)
(
    unsigned char *pData /* ���ջ�����ָ�룬����Ϊ�������ù������ */
);

typedef int (*USB_NDIS_PKT_STATISTICS_PERIOD)
(
    unsigned int period /*��λS */
);

typedef int (*USB_NDIS_GET_RATE)
(
    NDIS_RATE_STRU  *pRate
);

typedef int (*USB_NDIS_AT_CMD_RECV)
(
    unsigned char *pBuff,   /*ָ��AT����ָ��*/
    unsigned short usLen    /*AT�����*/
);

typedef unsigned int (*USB_NDIS_GET_WWAN_MODE)  /*��ȡ��ǰ����ģʽcdma/wcdma*/
(
    void
);

typedef unsigned long (*USB_NET_DEV_SET_MAX_TX_PACKET_NUMBER)
(
    unsigned long ulNumber
);

typedef unsigned long (*MNTN_ERRLOGREGFUN)(char * cFileName,unsigned int ulFileId, unsigned int ulLine,
                unsigned int ulErrNo, void * pBuf, unsigned int ulLen);

#define USB_CAPABILITY_THREE BSP_USB_CapabilityThree
#define DRV_GET_USB_SPEED(a)   BSP_USB_GetSpeed(a)

#if (FEATURE_ON == MBB_USB)
/*****************************************************************************
��������   BSP_USB_GetSpeed
��������:  �ṩ���ϲ��ѯ�豸USB���ʽӿ�
��������� char *buf
����ֵ��   0:    ��ѯ�ɹ�
           ��������ѯʧ��
*****************************************************************************/
int BSP_USB_GetSpeed(unsigned char * buf);
/*****************************************************************************
��������   BSP_USB_CapabilityThree
��������:  ��ѯ�豸USB����ģʽ�ӿ�
��������� char *
����ֵ��   
*****************************************************************************/
int BSP_USB_CapabilityThree(void);
#else
/*****************************************************************************
��������   BSP_USB_GetSpeed
��������:  �ṩ���ϲ��ѯ�豸USB���ʽӿ�
��������� char *buf
����ֵ��   0:    ��ѯ�ɹ�
           ��������ѯʧ��
*****************************************************************************/
static INLINE int BSP_USB_GetSpeed(unsigned char * buf)
{
    return ERROR;
}
/*****************************************************************************
��������   BSP_USB_CapabilityThree
��������:  ��ѯ�豸USB����ģʽ�ӿ�
��������� char *
����ֵ��   
*****************************************************************************/
static INLINE int BSP_USB_CapabilityThree(void)
{
    return ERROR;
}
#endif

/*****************************************************************************
 �� �� ��  : BSP_USB_SetPid
 ��������  :
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern int BSP_USB_SetPid(unsigned char u2diagValue);
#define DRV_SET_PID(u2diagValue)    BSP_USB_SetPid(u2diagValue)

/*****************************************************************************
��������   BSP_USB_PortTypeQuery
��������:  ��ѯ��ǰ���豸ö�ٵĶ˿���ֵ̬
��������� stDynamicPidType  �˿���̬
��������� stDynamicPidType  �˿���̬
����ֵ��   0:    ��ѯ�ɹ�
           ��������ѯʧ��
*****************************************************************************/
unsigned int BSP_USB_PortTypeQuery(DRV_DYNAMIC_PID_TYPE_STRU *pstDynamicPidType);
#define DRV_SET_PORT_QUIRY(a)   BSP_USB_PortTypeQuery(a)

/*****************************************************************************
��������   BSP_USB_PortTypeValidCheck
��������:  �ṩ���ϲ��ѯ�豸�˿���̬���úϷ��Խӿ�
           1���˿�Ϊ��֧�����ͣ�2������PCUI�ڣ�3�����ظ��˿ڣ�4���˵���������16��
           5����һ���豸��ΪMASS��
��������� pucPortType  �˿���̬����
           ulPortNum    �˿���̬����
����ֵ��   0:    �˿���̬�Ϸ�
           �������˿���̬�Ƿ�
*****************************************************************************/
unsigned int BSP_USB_PortTypeValidCheck(unsigned char *pucPortType, unsigned long ulPortNum);
#define DRV_USB_PORT_TYPE_VALID_CHECK(pucPortType, ulPortNum)  \
                    BSP_USB_PortTypeValidCheck(pucPortType, ulPortNum)

/*****************************************************************************
��������   BSP_USB_GetAvailabePortType
��������:  �ṩ���ϲ��ѯ��ǰ�豸֧�ֶ˿���̬�б�ӿ�
��������� ulPortMax    Э��ջ֧�����˿���̬����
�������:  pucPortType  ֧�ֵĶ˿���̬�б�
           pulPortNum   ֧�ֵĶ˿���̬����
����ֵ��   0:    ��ȡ�˿���̬�б�ɹ�
           ��������ȡ�˿���̬�б�ʧ��
*****************************************************************************/
unsigned int BSP_USB_GetAvailabePortType(unsigned char *pucPortType,
                            unsigned long *pulPortNum, unsigned long ulPortMax);
#define DRV_USB_GET_AVAILABLE_PORT_TYPE(pucPortType, pulPortNum, ulPortMax)  \
                BSP_USB_GetAvailabePortType(pucPortType, pulPortNum, ulPortMax)

/*****************************************************************************
 �� �� ��  : BSP_USB_ATProcessRewind2Cmd
 ��������  : rewind2 CMD ����
 �������  : pData�����ݡ�
 �������  : ��
 �� �� ֵ  : false(0):����ʧ��
             tool(1):����ɹ�
*****************************************************************************/
extern int BSP_USB_ATProcessRewind2Cmd(unsigned char *pData);
#define DRV_PROCESS_REWIND2_CMD(pData)    BSP_USB_ATProcessRewind2Cmd(pData)

/*****************************************************************************
 �� �� ��  : BSP_USB_GetDiagModeValue
 ��������  : ����豸���͡�
 �������  : �ޡ�
 �������  : ucDialmode:  0 - ʹ��Modem����; 1 - ʹ��NDIS����; 2 - Modem��NDIS����
              ucCdcSpec:   0 - Modem/NDIS������CDC�淶; 1 - Modem����CDC�淶;
                           2 - NDIS����CDC�淶;         3 - Modem/NDIS������CDC�淶
 �� �� ֵ  : VOS_OK/VOS_ERR
*****************************************************************************/
extern BSP_S32 BSP_USB_GetDiagModeValue(unsigned char *pucDialmode,
                             unsigned char *pucCdcSpec);
#define DRV_GET_DIAG_MODE_VALUE(pucDialmode, pucCdcSpec)    \
                             BSP_USB_GetDiagModeValue(pucDialmode, pucCdcSpec)

/*****************************************************************************
 �� �� ��  : BSP_USB_GetPortMode
 ��������  : ��ȡ�˿���̬ģʽ�����ضԽ����󣬴�׮��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern unsigned char BSP_USB_GetPortMode(char*PsBuffer, unsigned long*Length );
#define DRV_GET_PORT_MODE(PsBuffer, Length)    BSP_USB_GetPortMode(PsBuffer,Length)

/*****************************************************************************
 �� �� ��  : BSP_USB_GetU2diagDefaultValue
 ��������  : ��ö˿�Ĭ��u2diagֵ
 �������  : �ޡ�
 �������  : �ޡ�
 ����ֵ��   u2diagֵ

*****************************************************************************/
extern BSP_U32 BSP_USB_GetU2diagDefaultValue(void);
#define DRV_GET_U2DIAG_DEFVALUE()    BSP_USB_GetU2diagDefaultValue()


#ifdef __VXWORKS__
static INLINE void MNTN_ERRLOG_REG_FUNC(MNTN_ERRLOGREGFUN pRegFunc)
{
    return ;
}
#else
extern void MNTN_ERRLOG_REG_FUNC(MNTN_ERRLOGREGFUN pRegFunc);
#endif

/*****************************************************************************
 �� �� ��  : BSP_USB_UdiagValueCheck
 ��������  : ���ӿ����ڼ��NV����USB��ֵ̬�ĺϷ���.
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0��OK��
            -1��ERROR
*****************************************************************************/
extern int BSP_USB_UdiagValueCheck(unsigned long DiagValue);
#define DRV_UDIAG_VALUE_CHECK(DiagValue)     BSP_USB_UdiagValueCheck(DiagValue)
#define DRV_U2DIAG_VALUE_CHECK(DiagValue)     BSP_USB_UdiagValueCheck(DiagValue)

/*****************************************************************************
 �� �� ��  : BSP_USB_GetLinuxSysType
 ��������  : ���ӿ����ڼ��PC���Ƿ�ΪLinux���Թ��Linux��̨���β���ʧ�ܵ�����.
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0��Linux��
            -1����Linux��
*****************************************************************************/
extern int BSP_USB_GetLinuxSysType(void) ;
#define DRV_GET_LINUXSYSTYPE()    BSP_USB_GetLinuxSysType()

/********************************************************
����˵���� ���ص�ǰ�豸�б���֧��(sel=1)���߲�֧��(sel=0)PCSC���豸��ֵ̬
��������:
���������sel
          0: ͨ������dev_type���ص�ǰ����PCSC���豸��ֵ̬
          1��ͨ������dev_type���ص�ǰ��PCSC���豸��ֵ̬
���������dev_type д����Ҫ���豸��ֵ̬�����û����д��ֵ��
          NV�д洢���豸��ֵ̬
���������pulDevType ��ulCurDevType��Ӧ���豸��ֵ̬�����û�з���ֵ1��
����ֵ��
          0����ѯ����Ӧ���豸��ֵ̬��
          1��û�в�ѯ����Ӧ���豸��ֵ̬��
********************************************************/
int BSP_USB_PcscInfoSet(unsigned int  ulSel, unsigned int  ulCurDevType, unsigned int *pulDevType);
#define DRV_USB_PCSC_INFO_SET(ulSel, ulCurDevType, pulDevType)    BSP_USB_PcscInfoSet(ulSel, ulCurDevType, pulDevType)

/*TCP/IPЭ��ջ��ά�ɲⲶ�����Ϣ��ʶ*/
enum IPS_MNTN_TRACE_IP_MSG_TYPE_ENUM
{
    /* IP ���ݰ���ά�ɲ��ϱ� */
    ID_IPS_TRACE_IP_ADS_UL                  = 0xD030,
    ID_IPS_TRACE_IP_ADS_DL                  = 0xD031,
    ID_IPS_TRACE_IP_USB_UL                  = 0xD032,
    ID_IPS_TRACE_IP_USB_DL                  = 0xD033,

    ID_IPS_TRACE_IP_MSG_TYPE_BUTT
};

/********************************************************
����˵����Э��ջע��USB��SKB�ؼ���Ϣ�ϱ���SDT�ص�����
��������:
���������pFunc: SKB�ؼ���Ϣ�ϱ���SDT�ص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
#ifdef __KERNEL__
typedef void (*USB_IPS_MNTN_TRACE_CB_T)(struct sk_buff *skb,unsigned short usType);
extern unsigned int BSP_USB_RegIpsTraceCB(USB_IPS_MNTN_TRACE_CB_T pFunc);
#define DRV_USB_REG_IPS_TRACECB(x) BSP_USB_RegIpsTraceCB(x)
#endif

/********************************************************
����˵����Э��ջע��USBʹ��֪ͨ�ص�����
��������:
���������pFunc: USBʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
typedef void (*USB_UDI_ENABLE_CB_T)(void);
extern unsigned int BSP_USB_RegUdiEnableCB(USB_UDI_ENABLE_CB_T pFunc);
#define DRV_USB_REGUDI_ENABLECB(x) BSP_USB_RegUdiEnableCB(x)

/********************************************************
����˵����Э��ջע��USBȥʹ��֪ͨ�ص�����
��������:
���������pFunc: USBʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
typedef void (*USB_UDI_DISABLE_CB_T)(void);
extern unsigned int BSP_USB_RegUdiDisableCB(USB_UDI_DISABLE_CB_T pFunc);
#define DRV_USB_REGUDI_DISABLECB(x) BSP_USB_RegUdiDisableCB(x)

/********************************************************
����˵����Э��ջע��HSICʹ��֪ͨ�ص�����
��������:
���������pFunc: HSICʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
typedef void (*HSIC_UDI_ENABLE_CB_T)(void);
extern unsigned int BSP_HSIC_RegUdiEnableCB(HSIC_UDI_ENABLE_CB_T pFunc);
#define DRV_HSIC_REGUDI_ENABLECB(x) BSP_HSIC_RegUdiEnableCB(x)

/********************************************************
����˵����Э��ջע��HSICȥʹ��֪ͨ�ص�����
��������:
���������pFunc: HSICȥʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
typedef void (*HSIC_UDI_DISABLE_CB_T)(void);
extern unsigned int BSP_HSIC_RegUdiDisableCB(HSIC_UDI_DISABLE_CB_T pFunc);
#define DRV_HSIC_REGUDI_DISABLECB(x) BSP_HSIC_RegUdiDisableCB(x)
/********************************************************
����˵����Э��ջ��ѯHSICö��״̬
��������:
�����������
�����������
�����������
����ֵ��  1��ö�����
          0��ö��δ���
********************************************************/
extern unsigned int BSP_GetHsicEnumStatus(void);
#define DRV_GET_HSIC_ENUM_STATUS() BSP_GetHsicEnumStatus()

/********************************************************************************************************
 �� �� ��  : USB_otg_switch_signal_set
 ��������  : ����BALONG��K3�Խ�ʱUSBͨ���л�GPIO���ſ���
 �������  : ��š����źź�ֵ
 �������  : ��

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int USB_otg_switch_signal_set(UINT8 ucGroup, UINT8 ucPin, UINT8 ucValue);
#define DRV_USB_OTG_SWITCH_SIGNAL_SET(group, pin, value) USB_otg_switch_signal_set(group, pin, value)

#define DRV_GPIO_SET(group, pin, value) USB_otg_switch_signal_set(group, pin, value)
#define DRV_GPIO_USB_SWITCH             200
#define DRV_GPIO_HIGH                   1
#define DRV_GPIO_LOW                    0

/********************************************************************************************************
 �� �� ��  : USB_otg_switch_set
 ��������  : ����BALONG��K3�Խ�ʱMODEM�࿪����ر�USB PHY
 �������  : ������ر�
 �������  : ��

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int USB_otg_switch_set(UINT8 ucValue);
#define DRV_USB_PHY_SWITCH_SET(value) USB_otg_switch_set(value)

#define AT_USB_SWITCH_SET_VBUS_VALID            1
#define AT_USB_SWITCH_SET_VBUS_INVALID          2

#define USB_SWITCH_ON                           1
#define USB_SWITCH_OFF                          0

/********************************************************************************************************
 �� �� ��  : USB_otg_switch_get
 ��������  : ����BALONG��K3�Խ�ʱMODEM��USB PHY״̬��ѯ
 �������  : ��
 �������  : ����USB PHY����״̬

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
extern int USB_otg_switch_get(UINT8 *pucValue);
#define DRV_USB_PHY_SWITCH_GET(value) USB_otg_switch_get(value)

extern unsigned long USB_ETH_DrvSetDeviceAssembleParam(
    unsigned long ulEthTxMinNum,
    unsigned long ulEthTxTimeout,
    unsigned long ulEthRxMinNum,
    unsigned long ulEthRxTimeout);

extern unsigned long USB_ETH_DrvSetHostAssembleParam(unsigned long ulHostOutTimeout);

/********************************************************
����˵����Э��ջ��ѯHSIC�Ƿ�֧��NCM
��������:
�����������
�����������
�����������
����ֵ��  1��֧��NCM
          0����֧��NCM
********************************************************/
extern int BSP_USB_HSIC_SupportNcm(void);
#define DRV_USB_HSIC_SUPPORT_NCM() BSP_USB_HSIC_SupportNcm()

/********************************************************
����˵����TTF��ѯԤ����SKB Num
��������:
�����������
�����������
�����������
����ֵ��  SKB Num
********************************************************/
extern BSP_U32 BSP_AcmPremallocSkbNum(void);
#define DRV_GET_PREMALLOC_SKB_NUM() BSP_AcmPremallocSkbNum()

/********************************************************
��������   BSP_UDI_FindVcom
���������� ��ѯ��ǰ�豸��̬��ָ����UDI���⴮�ڶ˿��Ƿ����
��������� UDI_DEVICE_IDö��ֵ��������ѯ�����⴮�ڶ˿�ID
��������� ��
����ֵ��
           0����ǰ�豸��̬��֧�ֲ�ѯ�����⴮�ڶ˿ڣ�
           1����ǰ�豸��̬֧�ֲ�ѯ�����⴮�ڶ˿ڡ�
ע����� ��
********************************************************/
extern int BSP_UDI_FindVcom(UDI_DEVICE_ID enVCOM);

/*****************************************************************************
* �� �� ��  : DRV_USB_RegEnumDoneForMsp
* ��������  : �ṩ�� MSP ע�� USB ö����ɺ�֪ͨ����
* �������  : pFunc: ö����ɻص�����ָ��
* �������  : ��
* �� �� ֵ  : 0: �ɹ�ע��,�ȴ�ö�����֪ͨ;
*             1: USB �Ѿ�ö�����, ����ֱ�ӳ�ʼ�� USB ����;
*             -1: ʧ��, ��USB��̬,û��USB����
*****************************************************************************/
extern signed int BSP_USB_RegEnumDoneForMsp(void *pFunc);
#define DRV_USB_RegEnumDoneForMsp   BSP_USB_RegEnumDoneForMsp

/*****************************************************************************
* �� �� ��  : BSP_USB_RegEnumDoneForPs
* ��������  : �ṩ�� PS ע�� USB ö����ɺ�֪ͨ����
* �������  : pFunc: ö����ɻص�����ָ��
* �������  : ��
* �� �� ֵ  : 0: �ɹ�ע��,�ȴ�ö�����֪ͨ;
*             1: USB �Ѿ�ö�����, ����ֱ�ӳ�ʼ�� USB ����;
*             -1: ʧ��, ��USB��̬,û��USB����
*****************************************************************************/
extern signed int BSP_USB_RegEnumDoneForPs(void *pFunc);
#define DRV_USB_RegEnumDoneForPs    BSP_USB_RegEnumDoneForPs

/********************************************************
����˵���� ���ص�ǰNV���е��豸��ֵ̬���Ƿ�֧��PCSC
��������:
��������� dev_type���豸��ֵ̬��OAM��NV�ж�����

��������� �ޡ�
����ֵ��
          0: dev_type��֧��PCSC�豸��
          1��dev_type֧��PCSC�豸
********************************************************/
/*unsigned int pcsc_info_quiry(unsigned int ulDevType);*/
#define DRV_USB_PCSC_INFO_QUIRY(a)            DRV_OK


/*���翨��δ���� ����ʱAPI ��׮begin*/
/*****************************************************************************
 �� �� ��  : BSP_USB_RndisAppEventDispatch
 ��������  : ���ӿ�����֪ͨAPP ��Ӧ��USB����¼�
 �������  : usb�¼���
 �� �� ֵ  :��
*****************************************************************************/
extern void BSP_USB_RndisAppEventDispatch(unsigned ulStatus) ;
#define DRV_RNDIS_APP_ENENT_DISPATCH(ulStatus)    BSP_USB_RndisAppEventDispatch(ulStatus)

/************************************************************************
 * FUNCTION
 *       rndis_app_event_dispatch
 * DESCRIPTION
 *       ���翨�汾����Ӧ�ý��в��Ż�Ͽ���������
 * INPUTS
 *       ���в��Ż�Ͽ�����ָʾ
 * OUTPUTS
 *       NONE
 *************************************************************************/
extern VOID rndis_app_event_dispatch(unsigned int ulStatus);
extern VOID DRV_AT_SETAPPDAILMODE(unsigned int ulStatus);

/************************************************************************
 * FUNCTION
 *       PDP_ACT_DRV_CALLBACK
 * DESCRIPTION
 *       PDP�������õ���Ļص�������ԭ�������翨���������ط��ű���Ϣ�����ڴ�׮
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
extern int PDP_ACT_DRV_CALLBACK(void);

typedef void(* USB_NET_DEV_SWITCH_GATEWAY)
(
    void
);

/*****************************************************************************
 �� �� ��  : BSP_USB_NASSwitchGatewayRegExtFunc
 ��������  : ���ӿ�����NASע���л�����֪ͨ�ص�����
 �������  :�ص��ӿڡ�
 �������  : �ޡ�
 �� �� ֵ  : 0���ɹ�
                       ����:ʧ��
*****************************************************************************/
extern int BSP_USB_NASSwitchGatewayRegFunc(USB_NET_DEV_SWITCH_GATEWAY switchGwMode);
#define DRV_USB_NAS_SWITCH_GATEWAY_REGFUNC(switchGwMode)    BSP_USB_NASSwitchGatewayRegFunc(switchGwMode)
/*���翨��δ���� ����ʱAPI ��׮end*/

extern unsigned long USB_ETH_DrvSetRxFlowCtrl(unsigned long ulParam1, unsigned long ulParam2);
extern unsigned long USB_ETH_DrvClearRxFlowCtrl(unsigned long ulParam1, unsigned long ulParam2);

static INLINE BSP_VOID  DRV_AT_SETAPPDIALMODE(unsigned int ulStatus)
{}

#define DRV_COM_RCV_CALLBACK_REGI(uPortNo,pCallback)    DRV_OK

/*�궨��*/
#define USB_L2_ENTER   1
#define USB_L2_EXIT   0

/*�����ص�ָ�붨��*/
typedef  void  (*FUNC_USB_LP_NOTIFY)(int iStatus);

/*****************************************************************************
 �� �� ��  : DRV_USB_LP_CB_REGISTER
 ��������  : L2״̬�����˳�֪ͨ�ص�����ע��ӿ�
 �������  : FUNC_USB_LP_NOTIFY *pUSBLPFunc�ص�����ָ��
 �������  : ��
 �� �� ֵ  : 0   : ע��ɹ�
             ������ע��ʧ��
*****************************************************************************/
extern int l2_notify_register(FUNC_USB_LP_NOTIFY pUSBLPFunc);
#define DRV_USB_LP_CB_REGISTER(pUSBLPFunc)  \
                l2_notify_register(pUSBLPFunc)


/*
 * ---------------------------
 * PCSC(CCID) �ӿ�
 * ---------------------------
 */
typedef unsigned long (*pFunAPDUProcess)(unsigned long cmd_type, unsigned char *apdu, unsigned long apdu_len);
typedef unsigned long (*GetCardStatus)(void);

typedef struct
{
    pFunAPDUProcess pFuncApdu;
    GetCardStatus   pFuncGetCardStatus;
}BSP_CCID_REGFUNC;

/*****************************************************************************
 �� �� ��  : pcsc_usim_ctrl_cmd
 ��������  : PCSC����ظ�����
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/
unsigned long pcsc_usim_ctrl_cmd(unsigned long cmd_type, unsigned long status,
                unsigned char *buf, unsigned long length);
#define DRV_PCSC_SEND_DATA(CmdType, Result, Buffer, Length) pcsc_usim_ctrl_cmd(CmdType, Result, Buffer, Length)

/*****************************************************************************
 �� �� ��  : pcsc_usim_int
 ��������  : ע��PCSC������պ���
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/
void pcsc_usim_int(pFunAPDUProcess pFun1, GetCardStatus pFun2);
#define DRV_PCSC_REG_CALLBACK(pFun1, pFun2) pcsc_usim_int((pFun1), (pFun2))

#ifdef CONFIG_NCM_MBIM_SUPPORT 
/*****************************************************************************
��������   BSP_USB_MBIMSetMode
��������:  �ṩ���ϲ��л�MBIM�˿ڹ���ģʽ�Ľӿ�
��������� switch_idex   ��Ҫ�л��Ķ˿���̬
�������:  ��
����ֵ��   ��
*****************************************************************************/
void BSP_USB_MBIMSetMode(int switch_idex);
#define DRV_USB_MBIM_SET_MODE(switch_idex) BSP_USB_MBIMSetMode(switch_idex)

/*****************************************************************************
��������   BSP_USB_MBIMGetMode
��������:  �ṩ���ϲ���MBIM�˿ڹ���ģʽ�Ľӿ�
��������� ��
�������:  ��
����ֵ��   ��
*****************************************************************************/           
unsigned int BSP_USB_MBIMGetMode(void);
#define DRV_USB_MBIM_GET_MODE() BSP_USB_MBIMGetMode() 
#endif
/*****************************************************************************
��������   BSP_USB_SetSwitchPcVoice
��������:  �ṩ���ϲ��Ƿ����������ܵĽӿ�
��������� 1��ʾ������������ 0��ʾ�ر���������
�������:  ��
����ֵ��   ��
*****************************************************************************/
void BSP_USB_SetSwitchPcVoice(unsigned mode);
#endif

