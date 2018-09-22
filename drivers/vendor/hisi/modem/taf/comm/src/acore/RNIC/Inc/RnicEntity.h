
#ifndef __RNIC_ENTITY_H__
#define __RNIC_ENTITY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AtRnicInterface.h"
#include "PsCommonDef.h"
#include "ImmInterface.h"
#include "AdsDeviceInterface.h"
#include "RnicLinuxInterface.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*================================================*/
/* ��ֵ�궨�� */
/*================================================*/

#define RNIC_MAC_ADDR_LEN               (6)                                     /* RNIC MAC��ַ���ȣ�6�ֽ� */

#define RNIC_MAX_PACKET                 (1536)                                  /* RNIC�������������Ϊ1500�ֽ� */
#define RNIC_ETH_HEAD_LEN               (14)                                    /* ��̫��ͷ������ */

#define RNIC_IPV4_VERSION               (4)                                     /* IPͷ����IP V4�汾�� */
#define RNIC_IPV6_VERSION               (6)                                     /* IPͷ����IP V6�汾�� */

#define RNIC_IP_HEAD_VERSION_OFFSET_MASK (0x0F)                                 /* IPͷ��Э��汾ƫ�������� */

#define RNIC_GET_IP_VERSION(ucFirstData)\
    (((ucFirstData) >> 4) & (RNIC_IP_HEAD_VERSION_OFFSET_MASK))

#define RNIC_IP_HEAD_DEST_ADDR_OFFSET   (4 * 4)                                 /* IPͷ��Ŀ��IP��ַƫ���� */

#define RNIC_IPV4_BROADCAST_ADDR        (0xFFFFFFFF)                            /* IPV4�㲥����ַ */

#define RNIC_DEFAULT_MTU                (1500)                                  /* RNICĬ�ϵ�MTUֵ */

#define RNIC_ETH_HDR_SIZE               (14)
#define RNIC_ETHER_ADDR_LEN             (6)
/*================================================*/
#define RNIC_TYPE_IP                    (0x0800)                                /* IPЭ�� */
#define RNIC_ETHERTYPE_ARP              (0x0806)                                /* ��������ʽ����ʾARP������  */
#define RNIC_ETHERTYPE_IPV4             (0x0800)                                /* ��������ʽ����ʾIPv4������  */
#define RNIC_ETHERTYPE_IPV6             (0x86DD)                                /* ��������ʽ����ʾIPv6������  */
#define RNIC_ETH_TYPE                   (0x0001)                                /* ��������ʽ��ARP���ĵ�HardwareFormat�ֶ��ã���ʾ��̫������  */
#define RNIC_ARP_REPLY_TYPE             (0x0002)                                /* ��������ʽ��ARP���ĵ�OpCode�ֶ��ã���ʾARPӦ������         */

/* ���ܺ����궨�� */
/*================================================*/

/* ��ȡ����ID��Ӧ��ModemId */
#define RNIC_GET_MODEM_ID_BY_NET_ID(index)              (g_astRnicManageTbl[index].enModemId)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

enum RNIC_NETCARD_STATUS_TYPE_ENUM
{
    RNIC_NETCARD_STATUS_CLOSED,                                                 /* RNICΪ�ر�״̬ */
    RNIC_NETCARD_STATUS_OPENED,                                                 /* RNICΪ��״̬ */
    RNIC_NETCARD_STATUS_BUTT
};
typedef VOS_UINT8 RNIC_NETCARD_STATUS_ENUM_UINT8;


enum RNIC_RESULT_TYPE_ENUM
{
    RNIC_OK             = 0,                                                    /* �������� */
    RNIC_NOTSTARTED     = 1,                                                    /* δ��ʼ */
    RNIC_INPROGRESS     = 2,                                                    /* ������ */
    RNIC_PERM           = 3,
    RNIC_NOENT          = 4,
    RNIC_IO             = 5,
    RNIC_NXIO           = 6,
    RNIC_NOMEM          = 7,                                                    /* δ���뵽�ڴ� */                                                    /* δ���뵽�ڴ� */
    RNIC_BUSY           = 8,                                                    /* RNIC�����豸æ */
    RNIC_NODEV          = 9,                                                    /* ���豸 */
    RNIC_INVAL          = 10,                                                   /* �Ƿ��豸 */
    RNIC_NOTSUPP        = 11,                                                   /* ������֧�� */
    RNIC_TIMEDOUT       = 12,                                                   /* ��ʱ */
    RNIC_SUSPENDED      = 13,                                                   /* ���� */
    RNIC_UNKNOWN        = 14,                                                   /* δ֪���� */
    RNIC_TEST_FAILED    = 15,                                                   /* ����ʧ�� */
    RNIC_STATE          = 16,                                                   /* ״̬���� */
    RNIC_STALLED        = 17,                                                   /* ʧ�� */
    RNIC_PARAM          = 18,                                                   /* �������� */
    RNIC_ABORTED        = 19,                                                   /* ����ȡ�� */
    RNIC_SHORT          = 20,                                                   /* ��Դ���� */
    RNIC_EXPIRED        = 21,                                                   /* ��� */

    RNIC_ADDR_INVALID   = 22,                                                   /* �޷������ַ */
    RNIC_OUT_RANGE      = 23,                                                   /* ������Ч��Χ�� */
    RNIC_ERROR          = 0xff,                                                 /* RNIC����ʧ�� */
    RNIC_BUTT
};
typedef VOS_INT32 RNIC_RESULT_TYPE_ENUM_INT32;

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
    VOS_UINT8                 ucEtherDhost[RNIC_ETHER_ADDR_LEN];                  /* destination ethernet address */
    VOS_UINT8                 ucEtherShost[RNIC_ETHER_ADDR_LEN];                  /* source ethernet address */
    VOS_UINT16                usEtherType;                                       /* packet type ID */
}RNIC_ETH_HEADER_STRU;


typedef struct
{
    RNIC_RM_NET_ID_ENUM_UINT8           enRmNetId;                              /* ����ID */
    MODEM_ID_ENUM_UINT16                enModemId;                              /* Modem Id */
    VOS_CHAR                           *pucRnicNetCardName;                     /* �������� */
    RNIC_ETH_HEADER_STRU                stIpv4Ethhead;                          /* IPV4��̫��ͷ */
    RNIC_ETH_HEADER_STRU                stIpv6Ethhead;                          /* IPV6��̫��ͷ */
}RNIC_NETCARD_ELEMENT_TAB_STRU;


typedef struct
{
    struct net_device_stats             stStats;                                /* Linxu�ں˱�׼������ͳ����Ϣ�ṹ */
    struct net_device                  *pstNetDev;                            /* ���ڼ�¼Linux�ں˷�����������ַ */
    RNIC_NETCARD_STATUS_ENUM_UINT8      enStatus;                               /* �����Ƿ�򿪱�־ */
    RNIC_RM_NET_ID_ENUM_UINT8           enRmNetId;                              /* �豸��Ӧ������ID */
    VOS_UINT8                           aucRsv[2];                              /* ���� */
    VOS_CHAR                           *pcDevName;                              /* ���ڼ�¼Linux�ں˷������������ */
}RNIC_NETCARD_DEV_INFO_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern const RNIC_NETCARD_ELEMENT_TAB_STRU          g_astRnicManageTbl[];

/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_INT RNIC_StopNetCard(
    struct net_device                  *pstNetDev
);
VOS_INT RNIC_OpenNetCard(
    struct net_device                  *pstNetDev
);
VOS_VOID RNIC_SendULIpv4DataInPdpDeactive(
    IMM_ZC_STRU                        *pstSkb,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv
);
VOS_VOID RNIC_SendULDataInPdpActive(
    IMM_ZC_STRU                        *pstImmZc,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucNetIndex,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType
);
VOS_UINT32 RNIC_TransSkbToImmZC(
    IMM_ZC_STRU                       **pstImmZc,
    struct sk_buff                     *pstSkb,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucNetIndex
);
VOS_VOID RNIC_SendULIpv4Data(
    struct sk_buff                     *pstSkb,
    struct net_device                  *pstNetDev,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucNetIndex
);
VOS_VOID RNIC_SendULIpv6Data(
    struct sk_buff                     *pstSkb,
    struct net_device                  *pstNetDev,
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucNetIndex
);
netdev_tx_t RNIC_StartXmit(
    struct sk_buff                     *pstSkb,
    struct net_device                  *pstNetDev
);

VOS_UINT32 RNIC_SendDlData(
    VOS_UINT8                           ucNetIndex,
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enPdpType
);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
VOS_UINT32 RNIC_RcvSdioDlData(
    VOS_UINT8                           ucPdnId,
    IMM_ZC_STRU                        *pstData
);
#endif

VOS_UINT32  RNIC_RcvAdsDlData(
    VOS_UINT8                           ucRabid,
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enPktType
);

VOS_INT RNIC_SetMacAddress(
    struct net_device                  *pstNetDev,
    void                               *pMacAddr
);
VOS_INT RNIC_ChangeMtu(
    struct net_device                  *pstNetDev,
    VOS_INT                             lNewMtu
);
VOS_VOID RNIC_ProcTxTimeout(
    struct net_device                  *pstNetDev
);
VOS_INT RNIC_Ioctrl(
    struct net_device                  *pstNetDev,
    struct ifreq                       *pstIfr,
    VOS_INT                             lCmd
);
VOS_VOID RNIC_DeinitNetCard(
    VOS_VOID                           *pNetDev
);
struct net_device_stats *RNIC_GetNetCardStats(
    struct net_device                  *pstNetDev
);
VOS_INT RNIC_InitNetCard(VOS_VOID);

VOS_UINT32 RNIC_AddMacHead (
    IMM_ZC_STRU                        *pstImmZc,
    const VOS_UINT8                    *pucAddData
);


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

#endif


