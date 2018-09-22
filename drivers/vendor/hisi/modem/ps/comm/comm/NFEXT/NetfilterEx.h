/*******************************************************************************
  Copyright   : 2005-2010, Huawei Tech. Co., Ltd.
  File name   : NetWInterface.h
  Version     : V300R002
  Date        : 2011-11-23
  Description :
  History     :
  1. Date:2011-11-23
     Author: caikai
     Modification:Create
*******************************************************************************/

#ifndef _NETFILTEREX_H_
#define _NETFILTEREX_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "v_id.h"
#include "vos.h"
#include "SysNvId.h"
#include "NVIM_Interface.h"
#include "NetWInterface.h"
#include "PsTypeDef.h"
#include "IpsMntn.h"
#include "omringbuffer.h"
#include "PsCommonDef.h"
#include "LinuxInterface.h"
#include "TtfNvInterface.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define DBG_ON                                      (1)
#define DBG_OFF                                     (0)

#define NF_EXT_DBG                                  DBG_ON

#define NF_EXT_DEF_BR_ARP_HOOK_ON_MASK              (g_stExHookMask.ulBrArpHookValue)

#define NF_EXT_DEF_PRE_ROUTING_HOOK_ON_MASK         (g_stExHookMask.ulInHookValue)

#define NF_EXT_DEF_POST_ROUTING_HOOK_ON_MASK        (g_stExHookMask.ulOutHookValue)

/* ����Э��ջ����HOOK MASK���� */
#define NF_EXT_DEF_FLOW_CTRL_HOOK_ON_MASK           (g_stExHookMask.ulFlowCtrlHookValue)


#define NF_EXT_RPO_TCP                              (0x6)   /*TCPЭ�����ͱ�־*/
#define NF_EXT_RING_BUF_SIZE                        (2048)  /*����buff�Ĵ�С*/
#define NF_TX_MSG_TASK_STACK_SIZE                   (32768)
#define MAC_HEADER_LENGTH                           (14)

#define NF_EXT_MAX_IP_SIZE                          (1500)

/* netfilter���Ӻ������� */
#define NF_EXT_BR_PRE_ROUTING_HOOK_ON_MASK          (1)
#define NF_EXT_BR_POST_ROUTING_HOOK_ON_MASK         (1 << 1)
#define NF_EXT_BR_FORWARD_HOOK_ON_MASK              (1 << 2)
#define NF_EXT_BR_LOCAL_IN_HOOK_ON_MASK             (1 << 3)
#define NF_EXT_BR_LOCAL_OUT_HOOK_ON_MASK            (1 << 4)
#define NF_EXT_ARP_LOCAL_IN_ON_MASK                 (1 << 5)
#define NF_EXT_ARP_LOCAL_OUT_ON_MASK                (1 << 6)
#define NF_EXT_IP4_PRE_ROUTING_HOOK_ON_MASK         (1 << 7)
#define NF_EXT_IP4_POST_ROUTING_HOOK_ON_MASK        (1 << 8)
#define NF_EXT_IP4_LOCAL_IN_HOOK_ON_MASK            (1 << 9)
#define NF_EXT_IP4_LOCAL_OUT_HOOK_ON_MASK           (1 << 10)
#define NF_EXT_IP4_FORWARD_HOOK_ON_MASK             (1 << 11)
#define NF_EXT_IP6_PRE_ROUTING_HOOK_ON_MASK         (1 << 12)
#define NF_EXT_IP6_POST_ROUTING_HOOK_ON_MASK        (1 << 13)
#define NF_EXT_IP6_LOCAL_IN_HOOK_ON_MASK            (1 << 14)
#define NF_EXT_IP6_LOCAL_OUT_HOOK_ON_MASK           (1 << 15)
#define NF_EXT_IP6_FORWARD_HOOK_ON_MASK             (1 << 16)
#define NF_EXT_BR_FORWARD_FLOW_CTRL_HOOK_ON_MASK    (1 << 17)

#define NF_EXT_BR_FORWARD_FLOW_CTRL_MASK            (1)

#define NF_EXT_BR_NAME                              "br0"
#if(NF_EXT_DBG == DBG_ON)
#define NF_EXT_STATS_INC(a, b)                       (g_stNfExtStats.aulStats[b] += a)
#else
#define NF_EXT_STATS_INC(a, b)                       do{}while(0)
#endif

#define NF_EXT_TX_BYTES_INC(a, b)                    (g_stExFlowCtrlEntity.aulTxBytesCnt[b] += a)

#ifndef __UT_CENTER__
#define NF_EXT_MEM_ALLOC(pid, size)                  kmalloc(size, GFP_ATOMIC)
#define NF_EXT_MEM_FREE(pid, p)                      kfree(p);
#else
#define NF_EXT_MEM_ALLOC(pid, size)                  PS_MEM_ALLOC(pid, size)
#define NF_EXT_MEM_FREE(pid, p)                      PS_MEM_FREE(pid, p);
#endif

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
enum NF_EXT_FLAG_OM_DATA_ENUM
{
    NF_EXT_FLAG_OM_DATA                = 0,                    /* OM��Ϣ��־ */
    NF_EXT_FLAG_NOT_OM_DATA            = 1,                    /* ��OM��Ϣ��־ */

    NF_EXT_FLAG_OM_DATA_BUTT
};
typedef int NF_EXT_FLAG_OM_DATA_ENUM_U32;

enum NF_EXT_FLAG_BLOCK_ENUM
{
    NF_EXT_FLAG_BLOCKED                = 0,                    /* ������־ */
    NF_EXT_FLAG_UNBLOCKED              = 1,                    /* ��������־ */

    NF_EXT_FLAG_BUTT
};

enum NF_EXT_TX_BYTES_CNT_ENUM
{
    NF_EXT_TX_BYTES_CNT_BR             = 0,                    /* ͳ������ */
    NF_EXT_TX_BYTES_CNT_BUTT
};

#if(NF_EXT_DBG == DBG_ON)
enum NF_EXT_STATS_ENUM
{
    NF_EXT_STATS_BR_FC_DROP            = 0,
    NF_EXT_STATS_BR_FC_ENTER,
    NF_EXT_STATS_BUF_FULL_DROP,
    NF_EXT_STATS_PUT_BUF_FAIL,
    NF_EXT_STATS_ALLOC_MEM_FAIL,
    NF_EXT_STATS_GET_BUF_FAIL,

    NF_EXT_STATS_BUT
};
#endif
/*****************************************************************************
  4 �ṹ����
*****************************************************************************/
/*********************************************
 �ṹ���� :NF_EXT_MASK_OPS_STRU
 Э���� :��
 �ṹ��˵�� :���ӿ�������ӳ���ṹ��
*********************************************/
typedef struct
{
    u_int32_t                       ulHookMask;
    struct nf_hook_ops              stNfExtOps;
} NF_EXT_MASK_OPS_STRU;


typedef struct
{
    VOS_UINT32                      ulIsBlkflag;               /* �������� */
    VOS_UINT32                      ulCurHookOnMask;           /* ��ǰHook���� */
    VOS_UINT32                      ulIsDeviceOpen ;           /* �豸�Ƿ����ı�־ */
    VOS_UINT32                      ulOmIp;
    VOS_UINT8                       aucKbuff[DEV_BUFF_LEN];    /* �ں˿ռ�Ļ����� */
#ifndef __UT_CENTER__
    struct class                   *pstNfExtClass;
#else
    struct classStub               *pstNfExtClass;
#endif
    struct cdev                     stNfExtCdev;               /* �ַ��豸�ṹ�� */
    dev_t                           ulDevNo;                   /* �ַ��豸�� */
    OM_RING_ID                      pRingBufferId;             /* ����buff*/
    wait_queue_head_t               stWaitHeadDev;             /* �ȴ�����ͷ */
    wait_queue_head_t               stWaitHeadTxTask;          /* �ȴ�����ͷ���Դ�������ʹ�� */
    spinlock_t                      stLockTxTask;              /* �����������ڻ���buff�����Ļ��Ᵽ�� */
}NF_EXT_ENTITY_STRU;

typedef struct
{
    VOS_UINT16   usDataLen;
    VOS_UINT8    aucRsv[2];
    VOS_UINT8   *pData;
}NF_EXT_DATA_RING_BUF_STRU;


typedef struct
{
    VOS_UINT32         ulFlowCtrlMsk;
    VOS_UINT32         aulTxBytesCnt[NF_EXT_TX_BYTES_CNT_BUTT];
    VOS_UINT8          aucRsv[4];
    struct net_device *pstBrDev;
}NF_EXT_FLOW_CTRL_ENTITY;

#if(NF_EXT_DBG == DBG_ON)
typedef struct
{
    VOS_UINT32  aulStats[NF_EXT_STATS_BUT];
}NF_EXT_STATS_STRU;
#endif

typedef struct
{
    VOS_UINT32          ulBrArpHookValue;       /* ���ź�ARP���Ӻ�����Ӧ������ */
    VOS_UINT32          ulInHookValue;          /* IP��PRE_ROUTING���Ӻ�����Ӧ������ */
    VOS_UINT32          ulOutHookValue;         /* IP��POST_ROUTING���Ӻ�����Ӧ������ */
    VOS_UINT32          ulFlowCtrlHookValue;    /* �������ع��Ӻ�������Ӧ������ */
}NF_EXT_HOOK_MASK_NV_STRU;

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
#if(NF_EXT_DBG == DBG_ON)
extern NF_EXT_STATS_STRU g_stNfExtStats;
#endif

/*****************************************************************************
  6 ��������
*****************************************************************************/
extern unsigned int NFExt_BrPreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrPostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));


extern unsigned int NFExt_BrLocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrLocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_ArpInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_ArpOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4PreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4PostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4LocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4LocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip4ForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6PreRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6PostRoutingHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6LocalInHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6LocalOutHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_Ip6ForwardHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));

extern unsigned int NFExt_BrForwardFlowCtrlHook(unsigned int hooknum,
                            struct sk_buff *skb,
                            const struct net_device *in,
                            const struct net_device *out,
                            int (*okfn)(struct sk_buff *));


extern unsigned int NFExt_Poll(struct file *file, poll_table *wait);
extern int NFExt_Open(struct inode *inode, struct file *file);

extern int NFExt_Release(struct inode *inode, struct file *file);

extern ssize_t NFExt_Read(struct file *filp, char *buff, size_t len, loff_t *offset);

extern ssize_t NFExt_Write(struct file *filp, const char *buff, size_t len, loff_t *offset);

extern PS_BOOL_ENUM_UINT8 NFExt_ConfigEffective(IPS_MNTN_TRACE_CONFIG_REQ_STRU *pRcvMsg);

extern VOS_UINT32 NFExt_AddDataToRingBuf(NF_EXT_DATA_RING_BUF_STRU *pstMsg);

extern VOS_UINT32 NFExt_SaveBrDev(VOS_VOID);

extern VOS_VOID NFExt_FlowCtrlInit(VOS_VOID);

#if(NF_EXT_DBG == DBG_ON)
extern VOS_VOID NFExt_StatsShow(VOS_VOID);
#endif

#ifdef __cplusplus
#if __cplusplus
                            }
#endif
#endif

#endif
