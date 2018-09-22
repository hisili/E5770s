#ifndef _IPS_MNTN_H_
#define _IPS_MNTN_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "om.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define IPS_IFNAMSIZ                    (16)                    /*�����������Ƴ���*/
#define IPS_END_NAME                    (16)
#define IPS_APP_CMD_INFO_LEN            (200)                   /*����APP��������������*/
#define IPS_MNTN_INFO_LEN               (10000)                 /*����TCP/IPЭ��ջ������Ϣ�����*/
#define IPS_MNTN_TRACE_MAX_BYTE_LEN     (1514)                  /*����TCP/IPЭ��ջ��������� */
#define IPS_MNTN_NAT_MAPPING_INFO_LEN   (40)                    /*����TCP/IPЭ��ջNATӳ����Ϣ��������*/
#define IPS_MNTN_INFO_TYPE_OFFSET       (4)                     /*TCP/IPЭ��ջ������Ϣ����ƫ��*/
#define IPS_MNTN_INFO_LEN_OFFSET        (4)                     /*TCP/IPЭ��ջ������Ϣ����ƫ��*/

/* IP ���ݰ���ά�ɲ�*/
#define IP_IPV4_PROTO_VERSION        4      /* IPV4Э��汾�� */
#define IP_IPV4_HEAD_LEN             20     /* IPV4����ͷͷ������ */
#define IP_IPV4_PROTO_TCP            6      /* IPV4��TCPЭ��� */
#define IP_IPV4_PROTO_UDP            17     /* IPV4��UDPЭ��� */
#define IP_IPV4_PROTO_ICMP           1      /* IPV4��ICMPЭ��� */
#define IP_IPV4_ICMP_ECHO_REQUEST    8      /* IPV4��ICMP��TYPE ECHO REQ */
#define IP_IPV4_ICMP_ECHO_REPLY      0      /* IPV4��ICMP��TYPE ECHO REPLY */
#define IP_IPV4_DATA_LEN_POS         2      /* IPV4��IP���ݰ������ֶ�ƫ�� */
#define IP_IPV4_IDENTIFY_POS         4      /* IPV4��IP���ݰ�IDENTIFY�ֶ�ƫ�� */
#define IP_IPV4_PROTO_POS            9      /* IPV4��IP���ݰ�Э���ֶ�ƫ�� */
#define IP_IPV4_ICMP_IDENTIFY_POS    4      /* ȥ��IPͷ��ICMP��IDENTIFY�ֶ�ƫ�� */
#define IP_IPV4_ICMP_SN_POS          6      /* ȥ��IPͷ��ICMP��SN�ֶ�ƫ�� */
#define IP_IPV4_TCP_SEQ_POS          4      /* ȥ��IPͷ��TCP��SEQ�ֶ�ƫ�� */
#define IP_IPV4_TCP_ACK_POS          8      /* ȥ��IPͷ��TCP��ACK�ֶ�ƫ�� */
#define IP_IPV4_DST_PORT_POS         2      /* ȥ��IPͷ��IPV4��Ŀ�Ķ˿��ֶ�ƫ�� */
#define IP_PROTO_VERSION_POS         4      /* IP���ݰ���Э��汾�ֶ�ƫ�� */

#define IP_IPV6_PROTO_VERSION        6      /* IPV6Э��汾�� */
#define IP_IPV6_HEAD_LEN             40     /* IPV6����ͷͷ������ */
#define IP_IPV6_PROTO_TCP            6      /* IPV6��TCPЭ��� */
#define IP_IPV6_PROTO_UDP            17     /* IPV6��UDPЭ��� */
#define IP_IPV6_PROTO_ICMP           58     /* IPV6��ICMPЭ��� */
#define IP_IPV6_ICMP_ECHO_REQUEST    128    /* IPV6��ICMP��TYPE ECHO REQ */
#define IP_IPV6_ICMP_ECHO_REPLY      129    /* IPV6��ICMP��TYPE ECHO REPLY */
#define IP_IPV6_DATA_LEN_POS         4      /* IPV6��IP���ݰ������ֶ�ƫ�� */
#define IP_IPV6_PROTO_POS            6      /* IPV6��IP���ݰ�Э���ֶ�ƫ�� */
#define IP_IPV6_ICMP_IDENTIFY_POS    4      /* ȥ��IPͷ��ICMP��IDENTIFY�ֶ�ƫ�� */
#define IP_IPV6_TCP_SEQ_POS          4      /* ȥ��IPͷ��TCP��SEQ�ֶ�ƫ�� */
#define IP_IPV6_TCP_ACK_POS          8      /* ȥ��IPͷ��TCP��ACK�ֶ�ƫ�� */
#define IP_IPV6_DST_PORT_POS         2      /* ȥ��IPͷ��IPV6��Ŀ�Ķ˿��ֶ�ƫ�� */

#define IP_IPV4_VER_AND_HEAD         0x45   /* IPv4�汾���ֶε�ֵ */
#define IP_IPV6_VER_AND_HEAD         0x60   /* IPv6�汾���ֶε�ֵ */
#define MAC_HEAD_LEN                 14     /* MACͷ���� */

/* ��IP���ݰ�����ȡ���ݣ����������ֽ���ת��Ϊ�����ֽ��� */
#define IP_GET_VAL_NTOH_U8(data,pos)    ((data)[pos])
#define IP_GET_VAL_NTOH_U16(data,pos)   (((data)[pos]<<8)|((data)[pos+1]))
#define IP_GET_VAL_NTOH_U32(data,pos)   (((data)[pos]<<24)|((data)[pos+1]<<16)|((data)[pos+2]<<8)|((data)[pos+3]))

#define MNTN_IP_INFO_LEN                sizeof(IPS_MNTN_IP_INFO_STRU)

/*�����Ϣͷ*/
#define IPS_FILL_MSG_HEADER(pSendMsg, RecvPid)    \
        (pSendMsg)->ulReceiverCpuId  = VOS_LOCAL_CPUID; \
        (pSendMsg)->ulReceiverPid    = RecvPid;

/*lint -e813*/
#define OM_TRANS_DATA_OFFSET_LEN        offsetof(OM_APP_TRACE_STRU, aucPara)

#define PS_OM_TRANS_DATA_OFFSET_LEN     offsetof(PS_OM_TRANS_IND_STRU, aucData)

#define PS_OM_TRANS_OM_HEADER_LEN       offsetof(PS_OM_TRANS_IND_STRU, ulSn)

#define MNTN_PKT_INFO_OFFSET_LEN        offsetof(IPS_MNTN_PKT_INFO_STRU, aucData)

#define MNTN_BRIDGE_PKT_INFO_OFFSET_LEN offsetof(IPS_MNTN_BRIDGE_PKT_INFO_STRU, aucData)

#define MNTN_APP_CMD_INFO_OFFSET_LEN    offsetof(IPS_MNTN_APP_CMD_INFO_STRU, aucData)

#define MNTN_FLOW_CTRL_INFO_LEN         sizeof(IPS_MNTN_FLOW_CTRL_STRU)
/*lint +e813*/

#define MNTN_PKT_INFO_LEN               (OM_TRANS_DATA_OFFSET_LEN + MNTN_PKT_INFO_OFFSET_LEN + IPS_MNTN_TRACE_MAX_BYTE_LEN)

#define MNTN_BRIDGE_PKT_INFO_LEN        (OM_TRANS_DATA_OFFSET_LEN + MNTN_BRIDGE_PKT_INFO_OFFSET_LEN + IPS_MNTN_TRACE_MAX_BYTE_LEN)

#define MNTN_APP_CMD_INFO_LEN           (OM_TRANS_DATA_OFFSET_LEN + MNTN_APP_CMD_INFO_OFFSET_LEN + IPS_APP_CMD_INFO_LEN)

#define MNTN_INFO_LEN                   (OM_TRANS_DATA_OFFSET_LEN + IPS_MNTN_INFO_LEN)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
enum IPS_MNTN_TRACE_CONFIG_TYPE_ENUM
{
    ID_OM_IPS_ADVANCED_TRACE_CONFIG_REQ = 0xD013,               /* ����TCP/IPЭ��ջ ��������*/
    ID_IPS_OM_ADVANCED_TRACE_CONFIG_CNF = 0xD014,               /* ����TCP/IPЭ��ջ ����ָʾ*/

    ID_OM_IPS_MNTN_INFO_CONFIG_REQ      = 0xD015,               /* �����Բ���TCP/IPЭ��ջ ������Ϣ����*/
    ID_IPS_OM_MNTN_INFO_CONFIG_CNF      = 0xD016,               /* �����Բ���TCP/IPЭ��ջ ������Ϣ����ָʾ*/

    ID_OM_IPS_MNTN_IP_INFO_CONFIG_REQ   = 0xD017,               /* ����IP ���ݰ���Ϣ����*/
    ID_IPS_OM_MNTN_IP_INFO_CONFIG_CNF   = 0xD018,               /* ����IP ���ݰ���Ϣ����ָʾ*/

    ID_IPS_MNTN_TRACE_CONFIG_TYPE_BUTT
};
typedef VOS_UINT16 IPS_MNTN_TRACE_CONFIG_TYPE_ENUM_UINT16;

enum IPS_MNTN_INFO_ACTION_ENUM
{
    IPS_MNTN_INFO_REPORT_STOP           = 0,                    /*���������Բ���TCP/IPЭ��ջ������Ϣ*/
    IPS_MNTN_INFO_REPORT_START          = 1,                    /*�ر������Բ���TCP/IPЭ��ջ������Ϣ*/

    IPS_MNTN_INFO_REPORT_BUTT
};
typedef VOS_UINT16 IPS_MNTN_INFO_ACTION_ENUM_UINT16;

enum IPS_MNTN_RESULT_TYPE_ENUM
{
    IPS_MNTN_RESULT_OK                  = 0,
    IPS_MNTN_RESULT_START_TIMER_FAIL    = 1,
    IPS_MNTN_RESULT_ALLOC_MEM_FAIL      = 2,
    IPS_MNTN_RESULT_ALLOC_MSG_FAIL      = 3,
    IPS_MNTN_RESULT_INPUT_PARAM_ERR     = 4,
    IPS_MNTN_RESULT_LOCAL_PARAM_ERR     = 5,

    IPS_MNTN_RESULT_BUTT
};
typedef VOS_UINT16  IPS_MNTN_RESULT_TYPE_ENUM_UINT16;

enum IPS_MNTN_TIMER_NAME_ENUM
{
    IPS_MNTN_INFO_TIMER                 = 0x00000001,           /*�����Բ���TCP/IPЭ��ջ������Ϣ��ʱ��*/

    IPS_MNTN_TIMER_NAME_BUTT
};
typedef VOS_UINT32 IPS_MNTN_TIMER_NAME_ENUM_UINT32;

enum IPS_MNTN_TRACE_CHOSEN_ENUM
{
    IPS_MNTN_TRACE_NULL_CHOSEN               =   0,             /*����������Ϣ*/
    IPS_MNTN_TRACE_MSG_HEADER_CHOSEN         =   1,             /*������ͷ��*/
    IPS_MNTN_TRACE_CONFIGURABLE_LEN_CHOSEN   =   2,             /*�������ò�����*/
    IPS_MNTN_TRACE_WHOLE_DATA_LEN_CHOSEN     =   3,             /*������ȫ������*/

    IPS_MNTN_TRACE_MSG_CHOSEN_BUTT
};
typedef VOS_UINT32   IPS_MNTN_TRACE_CHOSEN_ENUM_UINT32;

/*TCP/IPЭ��ջ��ά�ɲⲶ�����Ϣ��ʶ*/
enum IPS_MNTN_TRACE_MSG_TYPE_ENUM
{
    ID_IPS_TRACE_INPUT_DATA_INFO            = 0xD017,               /*TCP/IP��ά�ɲ���ձ���*/
    ID_IPS_TRACE_OUTPUT_DATA_INFO           = 0xD018,               /*TCP/IP��ά�ɲⷢ�ͱ���*/
    ID_IPS_TRACE_BRIDGE_DATA_INFO           = 0xD019,               /*TCP/IP������ת����*/
    ID_IPS_TRACE_RECV_ARP_PKT               = 0xD01A,               /*TCP/IPЭ��ջ���յ�ARP���Ʊ���*/
    ID_IPS_TRACE_SEND_ARP_PKT               = 0xD01B,               /*TCP/IPЭ��ջ���͵�ARP���Ʊ���*/
    ID_IPS_TRACE_RECV_DHCPC_PKT             = 0xD01C,               /*TCP/IPЭ��ջ���յ�DHCP���Ʊ���*/
    ID_IPS_TRACE_SEND_DHCPC_PKT             = 0xD01D,               /*TCP/IPЭ��ջ���͵�DHCP���Ʊ���*/
    ID_IPS_TRACE_RECV_DHCPS_PKT             = 0xD01E,               /*TCP/IPЭ��ջ���յ�DHCP���Ʊ���*/
    ID_IPS_TRACE_SEND_DHCPS_PKT             = 0xD01F,               /*TCP/IPЭ��ջ���͵�DHCP���Ʊ���*/
    ID_IPS_TRACE_APP_CMD                    = 0xD020,               /*APP����������Ϣ*/
    ID_IPS_TRACE_MNTN_INFO                  = 0xD021,               /*TCP/IPЭ��ջ������Ϣ*/
    ID_IPS_TRACE_BRIDGE_PRE_ROUTING_INFO    = 0xD022,
    ID_IPS_TRACE_BRIDGE_POST_ROUTING_INFO   = 0xD023,
    ID_IPS_TRACE_BRIDGE_LOCAL_IN_INFO       = 0xD024,
    ID_IPS_TRACE_BRIDGE_LOCAL_OUT_INFO      = 0xD025,
    ID_IPS_TRACE_IP4_FORWARD_INFO           = 0xD026,
    ID_IPS_TRACE_IP4_LOCAL_IN_INFO          = 0xD027,
    ID_IPS_TRACE_IP4_LOCAL_OUT_INFO         = 0xD028,
    ID_IPS_TRACE_IP6_FORWARD_INFO           = 0xD029,
    ID_IPS_TRACE_IP6_LOCAL_IN_INFO          = 0xD02A,
    ID_IPS_TRACE_IP6_LOCAL_OUT_INFO         = 0xD02B,

    /* �������ؿ�ά�ɲ��ϱ� */
    ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_START = 0xD02C,
    ID_IPS_TRACE_BR_FORWARD_FLOW_CTRL_STOP  = 0xD02D,

    ID_IPS_TRACE_MSG_TYPE_BUTT
};
typedef VOS_UINT16  IPS_MNTN_TRACE_MSG_TYPE_ENUM_UINT16;

/*TCP/IPЭ��ջ������Ϣ����*/
enum IPS_MNTN_INFO_TYPE_ENUM
{
    ID_IPS_MNTN_IFCONFIG_INFO           = 0x0001,               /*����������Ϣ*/
    ID_IPS_MNTN_NETSTAT_ROUTES_INFO     = 0x0002,               /*·����Ϣ*/
    ID_IPS_MNTN_NETSTAT_ENTRIES_INFO    = 0x0003,               /*����״̬��Ϣ*/
    ID_IPS_MNTN_NAT_RULES_INFO          = 0x0004,               /*NAT�������Ϣ*/
    ID_IPS_MNTN_NAT_STATS_INFO          = 0x0005,               /*NAT��״̬��Ϣ*/
    ID_IPS_MNTN_NAT_PROXIES_INFO        = 0x0006,               /*NAT��Э����Ϣ*/
    ID_IPS_MNTN_NAT_MAPPINGS_INFO       = 0x0007,               /*NAT��ӳ����Ϣ*/

    ID_IPS_MNTN_NAT_TYPE_BUTT           = 0xffff
};
typedef VOS_UINT16 IPS_MNTN_INFO_TYPE_ENUM_UINT16;

/*****************************************************************************
  4 �ṹ����
*****************************************************************************/
#pragma pack(4)



typedef struct
{
    IPS_MNTN_TRACE_CHOSEN_ENUM_UINT32   ulChoice;
    VOS_UINT32                          ulTraceDataLen;         /* ��ѡ��TRACE_CONFIGURABLE_LEN_CHOSENʱ����ֵ��Ч */

}IPS_MNTN_TRACE_CONFIG_STRU;

typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_BRIDGE_TRACE_CFG_STRU;

typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_INPUT_TRACE_CFG_STRU;

typedef IPS_MNTN_TRACE_CONFIG_STRU  IPS_MNTN_OUTPUT_TRACE_CFG_STRU;

typedef struct
{
    IPS_MNTN_BRIDGE_TRACE_CFG_STRU      stBridgeArpTraceCfg;        /*���ò���������Ϣ*/
    IPS_MNTN_INPUT_TRACE_CFG_STRU       stPreRoutingTraceCfg;       /*���ò���TCP/IPЭ��ջ������Ϣ*/
    IPS_MNTN_OUTPUT_TRACE_CFG_STRU      stPostRoutingTraceCfg;      /*���ò���TCP/IPЭ��ջ������Ϣ*/
    VOS_UINT8                           aucRsv[100];                /* ����λ��Ϊ���ڿ���չ */
}IPS_MNTN_TRACE_CONFIG_REQ_STRU;


typedef struct
{
    PS_RSLT_CODE_ENUM_UINT32            enRslt;                 /* ���ز�ѯ�ṹ�ɹ���ʧ�ܣ�PS_SUCC��ʾ�ɹ���PS_FAIL��ʾʧ�� */

}IPS_MNTN_TRACE_CONFIG_CNF_STRU;

typedef struct
{
    IPS_MNTN_INFO_ACTION_ENUM_UINT16    enCommand;
    VOS_UINT16                          usTimeLen;              /*��λ���� */
}IPS_MNTN_INFO_CFG_REQ_STRU;

typedef struct
{
    IPS_MNTN_INFO_ACTION_ENUM_UINT16    enCommand;
    IPS_MNTN_RESULT_TYPE_ENUM_UINT16    enRslt;
}IPS_MNTN_INFO_CFG_CNF_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_INFO_ENTITY
 �ṹ˵��  : ����TCP/IPЭ��ջ������Ϣʵ��
*****************************************************************************/
typedef struct
{
    HTIMER                              hIpsMntnTimer;          /*��ʱ��*/
    VOS_UINT32                          ulIpsMntnTimerLen;      /*��ʱ�����ȣ��̶�1s*/
    IPS_MNTN_INFO_ACTION_ENUM_UINT16    enIpsMntnFlag;          /*����TCP/IPЭ��ջ������Ϣ������־*/
    VOS_UINT8                           aucData[2];
}IPS_MNTN_INFO_ENTITY;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_PKT_INFO_STRU
 �ṹ˵��  : TCP/IPЭ��ջ���Ĳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucNetIfName[IPS_IFNAMSIZ]; /* ������������ */
    VOS_UINT16                              usLen;
    VOS_UINT8                               aucData[2];
} IPS_MNTN_PKT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_BRIDGE_PKT_INFO_STRU
 �ṹ˵��  : ������ת���Ĳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucSrcPort[IPS_END_NAME];   /* ��������������Ϣ */
    VOS_UINT8                               aucDestPort[IPS_END_NAME];  /* ���������������� */
    VOS_UINT16                              usLen;
    VOS_UINT8                               aucData[2];
} IPS_MNTN_BRIDGE_PKT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_APP_CMD_INFO_STRU
 �ṹ˵��  : APP���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usLen;
    VOS_UINT8                               aucData[2];
} IPS_MNTN_APP_CMD_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_INFO_STRU
 �ṹ˵��  : APP���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usType;
    VOS_UINT8                               aucData[2];
    VOS_UINT32                              ulLen;
} IPS_MNTN_INFO_STRU;


typedef struct
{
    VOS_UINT32  ulFcType;
    VOS_UINT8   aucRsv[4];
}IPS_MNTN_FLOW_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_IP_INFO_CONFIG_REQ_STRU
 �ṹ˵��  : IP���Ĳ�������
*****************************************************************************/
typedef struct
{
    VOS_UINT8    enAdsIPConfig;
    VOS_UINT8    enUsbIPConfig;
    VOS_UINT8    aucRsv[2];
}IPS_MNTN_IP_INFO_CONFIG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : IPS_MNTN_IP_INFO_STRU
 �ṹ˵��  : IPЭ��ջ���Ĳ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucIpVer;        /* IP Э��汾 */
    VOS_UINT8                               ucL4Proto;      /* Э������ICMP,TCP,UDP */
    VOS_UINT8                               ucIcmpType;     /* ICMP��������*/
    VOS_UINT8                               aucRsv[1];
    VOS_UINT16                              usDataLen;      /* IP ���ݰ�����*/
    VOS_UINT16                              usIp4Id;        /* IPv4 IDENTIFY�ֶ� */
    VOS_UINT16                              usSrcPort;      /* IP Դ�˿ں�*/
    VOS_UINT16                              usDstPort;      /* IP Ŀ�Ķ˿ں� */
    VOS_UINT32                              ulL4Id;         /* ��4��IDENTIFY,ICMP IDENTIFY+SN,TCP SEQ */
    VOS_UINT32                              ulTcpAckSeq;    /* TCP ACK SEQ */
} IPS_MNTN_IP_INFO_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif
/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  6 ��������
*****************************************************************************/
extern VOS_VOID IPS_MNTN_SndCfgCnf2Om
(
    VOS_UINT16      usPrimId,
    VOS_UINT16      usTransMsgContentLen,
    VOS_VOID       *pTransMsgContent
);

extern VOS_VOID IPS_MNTN_TraceAdvancedCfgReq(VOS_VOID *pMsg);

/* IP ���ݰ���ά�ɲ�*/
extern VOS_VOID IPS_MNTN_TraceIpInfo(struct sk_buff *skb,VOS_UINT16 usType);
extern VOS_VOID IPS_MNTN_IPInfoCfgReq(VOS_VOID *pMsg);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*_IPS_MNTN_H_*/


