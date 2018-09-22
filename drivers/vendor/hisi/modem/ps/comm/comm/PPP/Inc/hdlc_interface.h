 

#ifndef __HDLC_INTERFACE_H__
#define __HDLC_INTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
/*lint -e960 -e958 -e763 -e959 -e762 -e830 -e760 -e40*/
#include "vos.h"
#include "ImmInterface.h"
#include "throughput.h"
#include "ppp_mbuf.h"
#include "lcp.h"
#include "ipcp.h"
#include "async.h"
#include "hdlc.h"
#include "chap.h"
#include "pap.h"
#include "layer.h"
#include "proto.h"

/*lint +e960 +e958 +e763 +e959 +e762 +e830 +e760 +e40*/

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NPROTOSTAT                  (13)

extern struct link*                 pgPppLink;

#define PPP_LINK(PppId)             ((pgPppLink + PppId) - 1)
#define PPP_LINK_TO_ID(pLink)       ((pLink - pgPppLink) + 1)

#define LINK_QUEUES(link) (sizeof (link)->Queue / sizeof (link)->Queue[0])
#define LINK_HIGHQ(link) ((link)->Queue + LINK_QUEUES(link) - 1)

#define PPP_HDLC_PROC_AS_FRM_PACKET_IND         (100)

#if (VOS_WIN32 == VOS_OS_VER)
#define PPP_ST_TEST
#define PPP_ONCE_DEAL_MAX_CNT       (2000)
#else
/* ����PPP_ST_TESTʱ����PppStTest.c��������ڵ���������ST��������ʽ�汾������˺� */
#define PPP_ONCE_DEAL_MAX_CNT       (100)
#endif
/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*****************************************************************************
 ��Ӳ��HDLC�����ؽ��
*****************************************************************************/
enum PPP_HDLC_RESULT_TYPE_ENUM
{
    PPP_HDLC_RESULT_COMM_FINISH           = 0,      /* ���δ���������� */
    PPP_HDLC_RESULT_COMM_CONTINUE         = 1,      /* ���δ��������������������ڶ����д��´μ��������������Ƶ����������� */
    PPP_HDLC_RESULT_COMM_ERROR            = 2,      /* ���δ������ */

    PPP_HDLC_RESULT_BUTT
};
typedef VOS_UINT32   PPP_HDLC_RESULT_TYPE_ENUM_UINT32;

/*****************************************************************************
 PPP��������
*****************************************************************************/
enum PPP_DATA_TYPE_ENUM
{
    PPP_PULL_PACKET_TYPE = 1,                       /* IP������������ */
    PPP_PUSH_PACKET_TYPE,                           /* IP������������ */
    PPP_PULL_RAW_DATA_TYPE,                         /* PPP������������ */
    PPP_PUSH_RAW_DATA_TYPE                          /* PPP������������ */
};
typedef VOS_UINT8   PPP_DATA_TYPE_ENUM_UINT8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����Ϣ���Ͷ���
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 ��Ӳ��HDLC������ԭ�ͣ��ڴ���PPPʵ���ʱ�򣬸�����Ҫ�������ؽ�
 �����Ӳ����ʵ�����ʵ�����
*****************************************************************************/
typedef PPP_HDLC_RESULT_TYPE_ENUM_UINT32 (* PPP_HDLC_PROC_DATA_FUNC )
(
    PPP_ID usPppId,
    struct link *pstLink,
    PPP_ZC_QUEUE_STRU *pstDataQ
);

/*****************************************************************************
 ����PPPЭ��ջ�����Э�������Ҫ��װ�󷢸�PC����Ҫ��PPPЭ���ڼ����
*****************************************************************************/
typedef VOS_VOID (* PPP_HDLC_PROC_PROTOCOL_PACKET_FUNC )
(
    struct link *pstLink,
    struct ppp_mbuf *pstMbuf,
    VOS_INT32 ulPri,
    VOS_UINT16 usProtocol
);

/*****************************************************************************
 ����PPPЭ��ջ�����Э��������з�װ�Ĵ���������Ҫ��PPPЭ���ڼ����
*****************************************************************************/
typedef VOS_VOID (* PPP_HDLC_PROC_AS_FRM_PACKET_FUNC )
(
    VOS_UINT16       usPppId,
    VOS_UINT16       usProtocol,
    PPP_ZC_STRU     *pstMem
);

/*****************************************************************************
 ȥʹ��HDLC����ԭ�ͣ�Ӳ��HDLC��Ҫʵ�ִ˽ӿڣ��������Ҫ
*****************************************************************************/
typedef VOS_VOID (* PPP_HDLC_DISABLE_FUNC )(VOS_VOID);

struct link {
  VOS_INT32 type;                           /* _LINK type */
  const VOS_CHAR *name;                     /* Points to datalink::name */
  VOS_INT32 len;                            /* full size of parent struct */
  struct {
    unsigned gather : 1;                    /* Gather statistics ourself ? */
    struct pppThroughput total;             /* Link throughput statistics */
    struct pppThroughput *parent;           /* MP link throughput statistics */
  } stats;
  struct ppp_mqueue Queue[2];               /* Our output queue of mbufs */

  VOS_UINT32 proto_in[NPROTOSTAT];          /* outgoing protocol stats */
  VOS_UINT32 proto_out[NPROTOSTAT];         /* incoming protocol stats */

  struct lcp lcp;                           /* Our line control FSM */

  VOS_UINT32 phase;                         /* Curent phase */
  VOS_INT32 timer_state;
  struct ipcp ipcp;
  struct pap  pap;
  struct chap chap;                         /* Authentication using chap, added by liukai */

  VOS_UINT32 DropedPacketFromGgsn;

  struct async async;
  struct hdlc hdlc;

  struct layer const *layer[LAYER_MAX];     /* i/o layers */
  VOS_INT32 nlayers;
};

/*****************************************************************************
 ��Ӳ��HDLC���ýṹ��
*****************************************************************************/
typedef struct _PPP_HDLC_CONFIG_STRU
{
    PPP_HDLC_PROC_DATA_FUNC                 pFunProcData;           /* ָ�������Ӳ������������ݺ���ָ�� */
    PPP_HDLC_PROC_PROTOCOL_PACKET_FUNC      pFunProcProtocolPacket; /* ָ�������Ӳ������Э��ջ������ݺ���ָ�� */
    PPP_HDLC_DISABLE_FUNC                   pFunDisable;            /* ָ�������Ӳ������ȥʹ�ܺ���ָ�� */
    PPP_HDLC_PROC_AS_FRM_PACKET_FUNC        pFunProcAsFrmData;      /* ָ�������Ӳ�������Է�װ��ʽ������ָ�� */
}PPP_HDLC_CONFIG_STRU;

/*****************************************************************************
 Э��ջ���Э�̰���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT16                          usPppId;
    VOS_UINT16                          usProtocol;
    PPP_ZC_STRU                        *pstMem;
}HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


VOS_VOID PPP_HDLC_ProcIpModeUlData
(
    struct link *pstLink,
    PPP_ZC_STRU *pstMem,
    VOS_UINT16  usProto
);


VOS_VOID PPP_HDLC_ProcPppModeUlData
(
    PPP_ID      usPppId,
    PPP_ZC_STRU *pstMem
);



VOS_VOID PPP_HDLC_ProcDlData(VOS_UINT16 usPppId, PPP_ZC_STRU *pstMem);


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


#endif /* end of hdlc_interface.h */

