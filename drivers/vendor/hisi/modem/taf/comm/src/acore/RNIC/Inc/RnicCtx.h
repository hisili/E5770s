
#ifndef _RNIC_CTX_H_
#define _RNIC_CTX_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsLogdef.h"
#include "PsTypeDef.h"
#include "AtRnicInterface.h"
#include "RnicLinuxInterface.h"
#include "RnicTimerMgmt.h"
#include "RnicProcMsg.h"
#include "RnicEntity.h"

 #include "RnicConfigInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define RNIC_NET_ID_MAX_NUM             (RNIC_RM_NET_ID_BUTT)
#define RNIC_MODEM_ID_MAX_NUM           (MODEM_ID_BUTT)

#define RNIC_MAX_IPV6_ADDR_LEN          (16)                                    /* IPV6��ַ���� */

#define RNIC_MAX_DSFLOW_BYTE            (0xFFFFFFFF)                            /* RNIC�������ֵ */

#define RNIC_DIAL_DEMA_IDLE_TIME        (600)

#define RNIC_SET_FLOW_CTRL_STATUS(status, index)    (g_stRnicCtx.astSpecCtx[index].enFlowCtrlStatus = (status))

#define RNIC_GET_FLOW_CTRL_STATUS(index)            (g_stRnicCtx.astSpecCtx[index].enFlowCtrlStatus)

/* RabId�ĸ���λ��ʾModemId, 00��ʾModem0, 01��ʾModem1 */
#define RNIC_RABID_TAKE_MODEM_1_MASK    (0x40)                                  /* RabidЯ��Modem1������ */
#define RNIC_RABID_UNTAKE_MODEM_1_MASK  (0x3F)                                  /* Rabidȥ��Modem1������ */

/* ���RABIDֵ */
#define RNIC_RAB_ID_MAX_NUM             (11)
#define RNIC_RAB_ID_OFFSET              (5)

/* Rab Id����Сֵ */
#define RNIC_RAB_ID_MIN                 (5)

/* Rab Id�����ֵ */
#define RNIC_RAB_ID_MAX                 (15)

#define RNIC_RAB_ID_INVALID             (0xFF)

#define RNIC_RAB_ID_IS_VALID(ucRabId)\
    (((ucRabId) >= RNIC_RAB_ID_MIN) && ((ucRabId) <= RNIC_RAB_ID_MAX))

#define RNIC_PDN_ID_MAX_NUM             (20)
#define RNIC_PDN_ID_OFFSET              (1)

/* PDN Id����Сֵ */
#define RNIC_PDN_ID_MIN                 (1)

/* PDN Id�����ֵ */
#define RNIC_PDN_ID_MAX                 (20)

#define RNIC_PDN_ID_INVALID             (0xFF)

#define RNIC_PDN_ID_IS_VALID(ucPdnId)\
    (((ucPdnId) >= RNIC_PDN_ID_MIN) && ((ucPdnId) <= RNIC_PDN_ID_MAX))


/* ��ȡIPV4����PDP�����PDNID */
#define RNIC_GET_SPEC_NET_IPV4_PDNID(index)         (RNIC_GET_SPEC_NET_CTX(index)->stIpv4PdpInfo.ucPdnId)

/* ��ȡIPV6����PDP�����PDNID */
#define RNIC_GET_SPEC_NET_IPV6_PDNID(index)         (RNIC_GET_SPEC_NET_CTX(index)->stIpv6PdpInfo.ucPdnId)

/* ��ȡָ��Modem��PDNID��Ϣ */
#define RNIC_GET_SPEC_MODEM_PDNID_INFO()            (&g_stRnicCtx.stPdnIdInfo)

/* ��ȡPDNID��Ӧ������ID */
#define RNIC_GET_RM_NET_ID_BY_PDN_ID(PDNId) \
        (RNIC_GET_SPEC_MODEM_PDNID_INFO()->aucRmNetId[PDNId - RNIC_PDN_ID_OFFSET])


/* ��ȡָ��������PDP�����ĵ�ַ */
#define RNIC_GET_SPEC_NET_CTX(index)                (&g_stRnicCtx.astSpecCtx[index].stPdpCtx)

/* ��ȡIPV4����PDP�����RABID */
#define RNIC_GET_SPEC_NET_IPV4_RABID(index)         (RNIC_GET_SPEC_NET_CTX(index)->stIpv4PdpInfo.ucRabId)

/* ��ȡIPV6����PDP�����RABID */
#define RNIC_GET_SPEC_NET_IPV6_RABID(index)         (RNIC_GET_SPEC_NET_CTX(index)->stIpv6PdpInfo.ucRabId)

/* ��ȡIPV4����PDP�����RABID */
#define RNIC_GET_SPEC_NET_IPV4_REG_STATE(index)     (RNIC_GET_SPEC_NET_CTX(index)->stIpv4PdpInfo.enRegStatus)

/* ��ȡ��ǰ�Ĳ���ģʽ */
#define RNIC_GET_DIAL_MODE()                        (g_stRnicCtx.stDialMode.enDialMode)

/* ��ȡ���������ĵ�ַ */
#define RNIC_GET_UL_CTX_ADDR(index)                 (&g_stRnicCtx.astSpecCtx[index].stUlCtx)

/* ��ȡ���������ĵ�ַ */
#define RNIC_GET_DL_CTX_ADDR(index)                 (&g_stRnicCtx.astSpecCtx[index].stDlCtx)

/* ��ȡָ��������Ӧ��modem type */
#define RNIC_GET_SPEC_NET_MODEM_TYPE(index)         (g_stRnicCtx.astSpecCtx[index].enModemType)

/* ��ȡָ��Modem��RABID��Ϣ */
#define RNIC_GET_SPEC_MODEM_RABID_INFO(index)       (&g_stRnicCtx.astRabIdInfo[index])

/* ��ȡRABID��Ӧ������ID */
#define RNIC_GET_RM_NET_ID_BY_MODEM_ID(ModemId, RabId) \
        (RNIC_GET_SPEC_MODEM_RABID_INFO(ModemId)->aucRmNetId[RabId - RNIC_RAB_ID_OFFSET])

/* ��ȡ����˽�����ݵ�ַ */
#define RNIC_GET_SPEC_PRIV_INFO_ADDR(index)          (g_stRnicCtx.astSpecCtx[index].pstNetDevInfo)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum RNIC_PDP_REG_STATUS_ENUM
{
    RNIC_PDP_REG_STATUS_DEACTIVE,                                               /* δע���� */
    RNIC_PDP_REG_STATUS_ACTIVE,                                                 /* ��ע���� */
    RNIC_PDP_REG_STATUS_BUTT
};
typedef VOS_UINT32 RNIC_PDP_REG_STATUS_ENUM_UINT32;


enum RNIC_FLOW_CTRL_STATUS_ENUM
{
    RNIC_FLOW_CTRL_STATUS_STOP          = 0x00,                                 /* ����ֹͣ */
    RNIC_FLOW_CTRL_STATUS_START         = 0x01,                                 /* �������� */
    RNIC_FLOW_CTRL_STATUS_BUTT          = 0xFF
};
typedef VOS_UINT32 RNIC_FLOW_CTRL_STATUS_ENUM_UINT32;

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


typedef struct RNIC_DL_DATA_STATS
{
    VOS_UINT32                          ulDLCurDataRate;                        /* ��ǰ�������ʣ�����PDP�����2������ʣ�ȥ�������� */
    VOS_UINT32                          ulDLTotalDroppedPkts;                   /* ���ж�������������PDP�����ڼ���Ч */
    VOS_UINT32                          ulDLPeriodRcvPkts;                      /* �����յ����ݰ�����,ͳ��һ�����ŶϿ���ʱ���������յ��ĸ�������ʱ����� */
    VOS_UINT32                          ulDLPeriodRcvBytes;                     /* һ������ͳ���������յ���byte�� */
    VOS_UINT32                          ulDLTotalRcvBytes;                      /* �����յ����ݰ�byte����PDP�����ʼͳ�ƣ�PDPȥ�������� */
}RNIC_DL_DATA_STATS_STRU;


typedef struct RNIC_UL_DATA_STATS
{
    VOS_UINT32                          ulULTotalRcvPktsInDeactive;             /* PDPδ���������£��յ��������ݰ����������ű�����ʱ����ʱ����� */
    VOS_UINT32                          ulULCurDataRate;                        /* ��ǰ�������ʣ�����PDP�����2������ʣ�ȥ�������� */
    VOS_UINT32                          ulULTotalDroppedPkts;                   /* ���ж������� */
    VOS_UINT32                          ulULPeriodSndPkts;                      /* ���з�����Ч����,ͳ��һ�����ŶϿ���ʱ���������յ��ĸ�������ʱ����� */
    VOS_UINT32                          ulULPeriodSndBytes;                     /* һ������ͳ�������ڷ��͵�byte�� */
    VOS_UINT32                          ulULTotalSndBytes;                      /* ���з���byte����PDP�����ʼͳ�ƣ�PDPȥ�������� */
}RNIC_UL_DATA_STATS_STRU;


typedef struct
{
    VOS_UINT32                          OP_EnableDestAddr      : 1;             /* ʹ��Ŀ��IP��ַ��Ϊ�������� */
    VOS_UINT32                          OP_EnableDestMask      : 1;             /* ʹ��Ŀ������������Ϊ�������� */
    VOS_UINT32                          OP_EnableDestPortLow   : 1;             /* ʹ��Ŀ�Ķ˿ں�������Ϊ�������� */
    VOS_UINT32                          OP_EnableDestPortHigh  : 1;             /* ʹ��Ŀ�Ķ˿ں�������Ϊ�������� */
    VOS_UINT32                          OP_EnableSrcPortLow    : 1;             /* ʹ��Դ�˿ں�������Ϊ�������� */
    VOS_UINT32                          OP_EnableSrcPortHigh   : 1;             /* ʹ��Դ�˿ں�������Ϊ�������� */
    VOS_UINT32                          OP_EnableReserved      : 26;            /* ���� */
    VOS_UINT32                          ulDestAddr;                             /* Ŀ��IP��ַ */
    VOS_UINT32                          ulDestMask;                             /* Ŀ���������� */
    VOS_UINT16                          usDestPortLow;                          /* Ŀ�Ķ˿ں����� */
    VOS_UINT16                          usDestPortHigh;                         /* Ŀ�Ķ˿ں����� */
    VOS_UINT16                          usSrcPortLow;                           /* Դ�˿ں����� */
    VOS_UINT16                          usSrcPortHigh;                          /* Դ�˿ں����� */
}RNIC_FILTER_INFO_STRU;


typedef struct RNIC_FTI
{
    VOS_INT32                           ulFilterId;                             /* ���͹�������ID */
    RNIC_FILTER_INFO_STRU               stFilter;                               /* ���͹���������Ϣ */
    struct RNIC_FTI                    *pNextItem;                              /* ָ����һ���б��� */
}RNIC_FILTER_LST_STRU;


typedef struct
{
    RNIC_UL_DATA_STATS_STRU             stULDataStats;                           /* ��������ͳ�� */
}RNIC_UL_CTX_STRU;


typedef struct
{
    RNIC_DL_DATA_STATS_STRU             stDLDataStats;                          /* ��������ͳ�� */
}RNIC_DL_CTX_STRU;


typedef struct
{
    RNIC_PDP_REG_STATUS_ENUM_UINT32     enRegStatus;                            /* ��ʶ��PDP�������Ƿ�ע�� */

    VOS_UINT8                           ucRabId;                                /* ���ر�ʶ */
    /* Added by l60609 for L-C��������Ŀ, 2014-01-06, Begin */
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           aucRsv[2];                              /* ���� */
    /* Added by l60609 for L-C��������Ŀ, 2014-01-06, End */

    VOS_UINT32                          ulIpv4Addr;                             /* IP��ַ */
}RNIC_IPV4_PDP_INFO_STRU;


typedef struct
{
    RNIC_PDP_REG_STATUS_ENUM_UINT32     enRegStatus;                            /* ��ʶ��PDP�������Ƿ�ע�� */

    /* Modified by l60609 for L-C��������Ŀ, 2014-01-06, Begin */
    VOS_UINT8                           ucRabId;                                /* ���ر�ʶ */
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           aucRsv[2];                              /* ���� */
    /* Modified by l60609 for L-C��������Ŀ, 2014-01-06, End */

    VOS_UINT8                           aucIpv6Addr[RNIC_MAX_IPV6_ADDR_LEN];    /* ��AT������IPV6��ַ���ȣ�������":" */
}RNIC_IPV6_PDP_INFO_STRU;


typedef struct
{
    RNIC_PDP_REG_STATUS_ENUM_UINT32     enRegStatus;                            /* ��ʶ��PDP�������Ƿ�ע�� */

    /* Modified by l60609 for L-C��������Ŀ, 2014-01-06, Begin */
    VOS_UINT8                           ucRabId;                                /* ���ر�ʶ */
    VOS_UINT8                           ucPdnId;
    VOS_UINT8                           aucRsv[2];                              /* ���� */
    /* Modified by l60609 for L-C��������Ŀ, 2014-01-06, End */

    VOS_UINT32                          ulIpv4Addr;                             /* IP��ַ */
    VOS_UINT8                           aucIpv6Addr[RNIC_MAX_IPV6_ADDR_LEN];    /* ��AT������IPV6��ַ���ȣ�������":" */
}RNIC_IPV4V6_PDP_INFO_STRU;


typedef struct
{
    RNIC_IPV4_PDP_INFO_STRU             stIpv4PdpInfo;                          /* IPV4��PDP��Ϣ */
    RNIC_IPV6_PDP_INFO_STRU             stIpv6PdpInfo;                          /* IPV6��PDP��Ϣ */
    RNIC_IPV4V6_PDP_INFO_STRU           stIpv4v6PdpInfo;                        /* IPV4V6��PDP��Ϣ */

    /* Ϊ������չ������2���������� */
    RNIC_FILTER_LST_STRU               *pstFilterList;                          /* ���͹������б� */
    VOS_UINT8                          *pucFragmBuf;                            /* ����IP��Ƭ�Ļ��� */
} RNIC_PDP_CTX_STRU;


typedef struct
{
    RNIC_RM_NET_ID_ENUM_UINT8           aucRmNetId[RNIC_RAB_ID_MAX_NUM];        /* RABID��Ӧ������ID */
}RNIC_RABID_INFO_STAU;

/* Modified by l60609 for L-C��������Ŀ, 2014-01-06, Begin */

typedef struct
{
    RNIC_RM_NET_ID_ENUM_UINT8           aucRmNetId[RNIC_PDN_ID_MAX_NUM];        /* PDNID��Ӧ������ID */
}RNIC_PDNID_INFO_STAU;
/* Modified by l60609 for L-C��������Ŀ, 2014-01-06, End */


typedef struct
{
    RNIC_UL_CTX_STRU                    stUlCtx;                                /* RNIC���������� */
    RNIC_DL_CTX_STRU                    stDlCtx;                                /* RNIC���������� */
    RNIC_PDP_CTX_STRU                   stPdpCtx;                               /* RNIC��PDP������ */

    RNIC_FLOW_CTRL_STATUS_ENUM_UINT32   enFlowCtrlStatus;                       /* ����״̬ */

    RNIC_TIMER_ID_ENUM_UINT16           enTiDsFlowStats;                        /* ����ͳ�ƶ�ʱ�� */
    MODEM_ID_ENUM_UINT16                enModemId;                              /* ���������ĸ�modem */

    /* Modified by l60609 for L-C��������Ŀ, 2014-01-06, Begin */
    RNIC_MODEM_TYPE_ENUM_UINT8          enModemType;                            /* ��¼��ǰ�������ӵ�������modem�ͻ������modem */
    VOS_UINT8                           ucReserved[3];
    /* Modified by l60609 for L-C��������Ŀ, 2014-01-06, End */

    /* ����ϵͳ�����Netcard˽����������ַ */
    RNIC_NETCARD_DEV_INFO_STRU         *pstNetDevInfo;                          /* �����豸��Ϣ */
}RNIC_SPEC_CTX_STRU;


typedef struct
{
    /****** RNICÿ������ר�е������� ******/
    RNIC_SPEC_CTX_STRU                  astSpecCtx[RNIC_NET_ID_MAX_NUM];        /* �ض�������������Ϣ */

    RNIC_RABID_INFO_STAU                astRabIdInfo[RNIC_MODEM_ID_MAX_NUM];    /* RabId��Ӧ������ID */

    /* Modified by l60609 for L-C��������Ŀ, 2014-01-06, Begin */
    RNIC_PDNID_INFO_STAU                stPdnIdInfo;                            /* ��¼sdio pdn id��Ӧ������id*/
    /* Modified by l60609 for L-C��������Ŀ, 2014-01-06, End */

    /****** RNIC��ʱ�������� ******/
    RNIC_TIMER_CTX_STRU                 astTimerCtx[RNIC_MAX_TIMER_NUM];

    /****** RNIC���������� ******/
    RNIC_DIAL_MODE_STRU                 stDialMode;                             /* ����ģʽ */
    VOS_UINT32                          ulTiDialDownExpCount;                   /* ���ŶϿ���ʱ����ʱ��������ͳ�� */

    VOS_UINT32                          ulSetTimer4WakeFlg;                     /* �Ƿ�����Timer4���ѱ�־ */

    VOS_UINT32                          ulResetSem;                             /* �������ź��������ڸ�λ����  */

}RNIC_CTX_STRU;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

extern RNIC_CTX_STRU                                g_stRnicCtx;


/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_VOID RNIC_InitCtx(
    RNIC_CTX_STRU                      *pstRnicCtx
);
VOS_VOID RNIC_InitDlCtx(
    RNIC_DL_CTX_STRU                   *pstDlCtx
);
VOS_VOID RNIC_InitUlCtx(
    RNIC_UL_CTX_STRU                   *pstUlCtx
);
VOS_VOID RNIC_InitPdpCtx(
    RNIC_PDP_CTX_STRU                  *pstPdpCtx,
    VOS_UINT8                           ucRmNetId
);
VOS_VOID RNIC_InitDialMode(
    RNIC_DIAL_MODE_STRU                *pstDialMode
);
VOS_VOID RNIC_InitIpv4PdpCtx(
    RNIC_IPV4_PDP_INFO_STRU            *pstIpv4PdpCtx
);
VOS_VOID RNIC_InitIpv6PdpCtx(
    RNIC_IPV6_PDP_INFO_STRU            *pstIpv6PdpCtx
);
VOS_VOID RNIC_InitIpv4v6PdpCtx(
    RNIC_IPV4V6_PDP_INFO_STRU          *pstIpv4v6PdpCtx,
    VOS_UINT8                           ucRmNetId
);
RNIC_CTX_STRU* RNIC_GetRnicCtxAddr(VOS_VOID);
VOS_UINT32 RNIC_GetTiDialDownExpCount( VOS_VOID);
VOS_VOID RNIC_IncTiDialDownExpCount( VOS_VOID);
VOS_VOID RNIC_ClearTiDialDownExpCount( VOS_VOID);

VOS_UINT32 RNIC_GetCurrentUlRate(VOS_UINT8 ucIndex);
VOS_VOID RNIC_SetCurrentUlRate(
    VOS_UINT32                          ulULDataRate,
    VOS_UINT8                           ucIndex
);
VOS_UINT32 RNIC_GetCurrentDlRate(VOS_UINT8 ucIndex);
VOS_VOID RNIC_SetCurrentDlRate(
    VOS_UINT32                          ulDLDataRate,
    VOS_UINT8                           ucIndex
);
RNIC_DIAL_MODE_STRU* RNIC_GetDialModeAddr(VOS_VOID);
RNIC_PDP_CTX_STRU* RNIC_GetPdpCtxAddr(VOS_UINT8 ucIndex);
RNIC_UL_CTX_STRU* RNIC_GetUlCtxAddr(VOS_UINT8 ucIndex);
RNIC_DL_CTX_STRU* RNIC_GetDlCtxAddr(VOS_UINT8 ucIndex);

RNIC_TIMER_CTX_STRU*  RNIC_GetTimerAddr( VOS_VOID );
VOS_VOID RNIC_SetTimer4WakeFlg(VOS_UINT32 ulFlg);
VOS_UINT32 RNIC_GetTimer4WakeFlg(VOS_VOID);

VOS_VOID RNIC_InitRabidInfo(
    RNIC_RABID_INFO_STAU               *pstRabIdInfo
);

VOS_VOID RNIC_InitPdnIdInfo(
    RNIC_PDNID_INFO_STAU               *pstPdnIdInfo
);

RNIC_NETCARD_DEV_INFO_STRU *RNIC_GetSpecNetCardPrivateAddr(VOS_UINT8 ucIndex);
VOS_VOID RNIC_SetSpecNetCardPrivate(
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv,
    VOS_UINT8                           ucIndex
);
RNIC_SPEC_CTX_STRU *RNIC_GetSpecNetCardCtxAddr(VOS_UINT8 ucIndex);
RNIC_RABID_INFO_STAU *RNIC_GetSpecModemRabIdInfoAddr(
    MODEM_ID_ENUM_UINT16                enModemId
);

VOS_VOID RNIC_ResetDialMode(
    RNIC_DIAL_MODE_STRU                *pstDialMode
);
VOS_VOID RNIC_InitResetSem(VOS_VOID);
VOS_UINT32 RNIC_GetResetSem(VOS_VOID);

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

#endif /* end of RnicCtx.h */

