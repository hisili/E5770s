
#ifndef __DRV_NCM_H__
#define __DRV_NCM_H__

#include "drv_comm.h"

typedef struct tagNCM_PKT_S
{
    BSP_U8 *pBuffer;       /* bufferָ��*/
    BSP_U32  u32BufLen;      /* buffer���� */
}NCM_PKT_S;

/* NCM�豸����ö��*/
typedef enum tagNCM_DEV_TYPE_E
{
    NCM_DEV_DATA_TYPE,      /* ����ͨ�����ͣ�PSʹ��*/
    NCM_DEV_CTRL_TYPE       /* ����ͨ����MSP����AT����ʹ��*/
}NCM_DEV_TYPE_E;

/* ������·�հ�����ָ�� */
typedef BSP_VOID (*USBUpLinkRxFunc)(UDI_HANDLE handle, BSP_VOID * pPktNode);

/* ����װ�ͷź���ָ�� */
typedef BSP_VOID (*USBFreePktEncap)(BSP_VOID *PktEncap);

/* USB IOCTLö�� */
typedef enum tagNCM_IOCTL_CMD_TYPE_E
{
    NCM_IOCTL_NETWORK_CONNECTION_NOTIF,      /* 0x0,NCM�����Ƿ�������*/
    NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF, /* 0x1,NCM�豸Э�̵������ٶ�*/
    NCM_IOCTL_SET_PKT_ENCAP_INFO,            /* 0x2,���ð���װ��ʽ*/
    NCM_IOCTL_REG_UPLINK_RX_FUNC,            /* 0x3,ע�������հ��ص�����*/
    NCM_IOCTL_REG_FREE_PKT_FUNC,             /* 0x4,ע���ͷŰ���װ�ص�����*/
    NCM_IOCTL_FREE_BUFF,                     /* 0x5,�ͷŵ���buffer*/
    NCM_IOCTL_GET_USED_MAX_BUFF_NUM,         /* 0x6,��ȡ�ϲ�������ռ�õ�ncm buffer����*/
    NCM_IOCTL_GET_DEFAULT_TX_MIN_NUM,        /* 0x7,��ȡĬ�Ϸ���������ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_GET_DEFAULT_TX_TIMEOUT,        /* 0x8,��ȡĬ�Ϸ�����ʱʱ�䣬������ʱ�������һ��NCM����*/
    NCM_IOCTL_GET_DEFAULT_TX_MAX_SIZE,       /* 0x9,��ȡĬ�Ϸ����ֽ���ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_SET_TX_MIN_NUM,                /* 0xa,���÷���������ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_SET_TX_TIMEOUT,                /* 0xb,���÷�����ʱʱ�䣬������ʱ�������һ��NCM����*/
    NCM_IOCTL_SET_TX_MAX_SIZE,               /* 0xc,�������ֲ���ʹ�á����÷����ֽ���ֵ����������ֵ������һ��NCM����*/
    NCM_IOCTL_GET_RX_BUF_SIZE,               /* 0xd,��ȡ�հ�buffer��С*/
    NCM_IOCTL_FLOW_CTRL_NOTIF,               /* 0xe,���ؿ��ƿ���*/
    NCM_IOCTL_REG_AT_PROCESS_FUNC,           /* 0xf,ע��AT�����ص�����*/
    NCM_IOCTL_AT_RESPONSE,                   /* 0x10,AT�����Ӧ*/
    NCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC,     /* 0x11,ע������״̬�ı�֪ͨ�ص�����*/
    NCM_IOCTL_SET_PKT_STATICS,               /* 0x12,����ͳ����Ϣ*/
    
    NCM_IOCTL_GET_FLOWCTRL_STATUS,           /* 0x13 ��ѯNCM����״̬*/
    /* END:   Modified by liumengcun, 2011-4-21 */

    
    NCM_IOCTL_GET_CUR_TX_MIN_NUM,              /* 0x14 ��ȡ��ǰ����������ֵ*/
    NCM_IOCTL_GET_CUR_TX_TIMEOUT,               /* 0x15 ��ȡ��ǰ������ʱʱ��*/
    NCM_IOCTL_IPV6_DNS_NOTIF,              /*0x16 IPV6 DNS�����ϱ�*/
    /* END:   Modified by liumengcun, 2011-6-23 */
    /* BEGIN: Modified by liumengcun, 2011-7-20 ֧��IPV6 DNS����*/
    NCM_IOCTL_SET_IPV6_DNS,                     /* 0x16 ����IPV6 DNS*/
    /* END:   Modified by liumengcun, 2011-7-20 */
    /* BEGIN: Modified by liumengcun, 2011-8-10 MSP������*/
    NCM_IOCTL_CLEAR_IPV6_DNS,                     /* 0x17 ���IPV6 DNS�ڰ�˵Ļ���,param�ڴ�������û�����壬�����ָ�뼴��*/
    NCM_IOCTL_GET_NCM_STATUS,                     /* 0x18 ��ȡNCM����״̬ enable:TRUE(1);disable:FALSE(0) */
    /* END:   Modified by liumengcun, 2011-8-10 */

    NCM_IOCTL_SET_ACCUMULATION_TIME,

    /* BEGIN: Modified by baoxianchun, 2012-5-17 GU PS ������*/
	NCM_IOCTL_SET_RX_MIN_NUM,		/*�����հ�������ֵ*/
	NCM_IOCTL_SET_RX_TIMEOUT,			/*�����հ���ʱʱ��*/
    /* END: Modified by baoxianchun, 2012-5-17 GU PS ������*/

    NCM_IOCTL_REG_NDIS_RESP_STATUS_FUNC,   /* NDISͨ��AT����״̬����ص����� */
#if (FEATURE_ON == MBB_COMMON)
    NCM_IOCTL_GET_MBIM_FLAG,               /* ��ȡ��ǰ�Ƿ���MBIMģʽ */
#endif
}NCM_IOCTL_CMD_TYPE_E;

/* NCM����״̬ö��,NCM_IOCTL_NETWORK_CONNECTION_NOTIF�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_CONNECTION_STATUS_E
{
    NCM_IOCTL_CONNECTION_LINKDOWN,      /* NCM����Ͽ�����*/
    NCM_IOCTL_CONNECTION_LINKUP         /* NCM��������*/
}NCM_IOCTL_CONNECTION_STATUS_E;

/* NCM�����ٶȽṹ,NCM_IOCTL_CONNECTION_SPEED_CHANGE_NOTIF�����ֶ�Ӧ�����ṹ��*/
typedef struct tagNCM_IOCTL_CONNECTION_SPEED_S
{
    BSP_U32 u32DownBitRate;
    BSP_U32 u32UpBitRate;
}NCM_IOCTL_CONNECTION_SPEED_S;

/* ����װ�ṹ��,NCM_IOCTL_SET_PKT_ENCAP_INFO�����ֶ�Ӧ�����ṹ��*/
typedef struct tagNCM_PKT_ENCAP_INFO_S
{
    BSP_S32 s32BufOft;      /* bufƫ���� */
    BSP_S32 s32LenOft;      /* lenƫ���� */
    BSP_S32 s32NextOft;     /* nextƫ���� */
}NCM_PKT_ENCAP_INFO_S;

/* AT����ظ�����ָ�뼰���� NCM_IOCTL_AT_RESPONSE*/
typedef struct tagNCM_AT_RSP_S
{
    BSP_U8* pu8AtAnswer;
    BSP_U32 u32Length;
} NCM_AT_RSP_S;
typedef struct tagNCM_IPV6_DNS_NTF_S
{
    BSP_U8* pu8Ipv6DnsNtf;
    BSP_U32 u32Length;
} NCM_AT_IPV6_DNS_NTF_S;

/* AT������պ���ָ�룬�ú���Ϊͬ���ӿڣ���ӦNCM_IOCTL_REG_AT_PROCESS_FUNC������*/
typedef BSP_VOID (*USBNdisAtRecvFunc)(BSP_U8 * pu8Buf, BSP_U32 u32Len);

/* NCM���ؿ���ö��,NCM_IOCTL_NETWORK_CONNECTION_NOTIF�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_FLOW_CTRL_E
{
    NCM_IOCTL_FLOW_CTRL_ENABLE,      /* ������*/
    NCM_IOCTL_FLOW_CTRL_DISABLE      /* �ر�����*/
}NCM_IOCTL_FLOW_CTRL_E;

/* NCM����״̬�ı�֪ͨö��,NCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC�����ֶ�Ӧ����ö��*/
typedef enum tagNCM_IOCTL_CONNECT_STUS_E
{
    NCM_IOCTL_STUS_CONNECT,      /* ����*/
    NCM_IOCTL_STUS_BREAK         /* �����Ͽ�,����*/
}NCM_IOCTL_CONNECT_STUS_E;

/* ����״̬�л�֪ͨ��������ӦNCM_IOCTL_REG_CONNECT_STUS_CHG_FUNC������*/
typedef BSP_VOID (*USBNdisStusChgFunc)(NCM_IOCTL_CONNECT_STUS_E enStatus, BSP_VOID * pBuffer);

/* NDISͨ��AT����״̬����ص����� */
typedef BSP_VOID (*USBNdisRespStatusCB)(BSP_VOID *pBuffer, BSP_U32 status);

/*  �´��ϴ������ذ��ĸ���ͳ����Ϣ��
    �����͸�PC�������ȴ�PC�Ķ�ȡ,NCM_IOCTL_SET_PKT_STATICS�����ֶ�Ӧ�����ṹ*/
typedef struct tagNCM_IOCTL_PKT_STATISTICS_S
{
    BSP_U32     u32TxOKCount;         /*���Ͱ���*/
    BSP_U32     u32RxOKCount;         /*���հ���*/
    BSP_U32     u32TxErrCount;        /*���ʹ���*/
    BSP_U32     u32RxErrCount;        /*���մ���*/
    BSP_U32     u32TxOverFlowCount;   /*�����������*/
    BSP_U32     u32RxOverFlowCount;   /*�����������*/
    BSP_U32     u32CurrentTx;         /*��������*/
    BSP_U32     u32CurrentRx;         /*��������*/
} NCM_IOCTL_PKT_STATISTICS_S;

/* BEGIN: Modified by liumengcun, 2011-7-20 IPV6 DNS���ýṹ,NCM_IOCTL_SET_IPV6_DNS��Ӧ�����ṹ*/
#define BSP_NCM_IPV6_DNS_LEN     32
 typedef struct tagNCM_IPV6DNS_S  /* 0x16 ����IPV6 DNS*/
 {
     BSP_U8 * pu8Ipv6DnsInfo;/* 32�ֽڣ���16�ֽڱ�ʾprimaryDNS����16�ֽڱ�ʾSecondaryDNS��*/
     BSP_U32 u32Length;
 } NCM_IPV6DNS_S;
/* END:   Modified by liumengcun, 2011-7-20 */

typedef struct tagNCM_PKT_INFO_S
{
    BSP_U32 u32PsRcvPktNum;              /* �հ��͵�PS�İ�����*/
    BSP_U32 u32RcvUnusedNum;             /* �հ�������PSҪ����������*/
    BSP_U32 u32NcmSendPktNum;            /* ��������*/
}NCM_PKT_INFO_S;

//just for fk silly stub v9r1
static INLINE BSP_VOID  BSP_NCM_Write_Ready(BSP_VOID)
{}

#endif

