

#ifndef __MSP_AT_H__
#define __MSP_AT_H__

#include <vos.h>
#include "TafTypeDef.h"

#ifdef __cplusplus
extern "C"
{
#endif


#define MSP_AT_SYSMODE_LTE


/*****************************************************************************
 ��Ϣ����
*****************************************************************************/
#define ID_MSG_AT_BASE  0x500  /* ע�⣬�����ϢID��Ҫͳһ���䣬����Ҫ�����û�׼ֵ*/


#define ID_MSG_AT_FW_BEGIN                 (ID_MSG_AT_BASE)
#define ID_MSG_AT_FW_CLIENT_REGISTER_REQ   (ID_MSG_AT_BASE+0x01)
#define ID_MSG_AT_FW_CLIENT_REGISTER_CNF   (ID_MSG_AT_BASE+0x02)
#define ID_MSG_AT_FW_CLIENT_CONFIG_IND     (ID_MSG_AT_BASE+0x03)
#define ID_MSG_AT_FW_CLIENT_STATUS_IND     (ID_MSG_AT_BASE+0x04)
#define ID_MSG_AT_FW_CLIENT_CONFIG_REQ     (ID_MSG_AT_BASE+0x05)
#define ID_MSG_AT_FW_CLIENT_CONFIG_CNF     (ID_MSG_AT_BASE+0x06)

#define ID_MSG_AT_FW_CMD_STREAM_REQ        (ID_MSG_AT_BASE+0x10)
#define ID_MSG_AT_FW_CMD_STREAM_CNF        (ID_MSG_AT_BASE+0x11)
#define ID_MSG_AT_FW_CMD_STREAM_IND        (ID_MSG_AT_BASE+0x12)
#define ID_MSG_AT_FW_CMD_BINARY_MSG        (ID_MSG_AT_BASE+0x13)
#define ID_MSG_AT_FW_CMD_PARAM_REQ         (ID_MSG_AT_BASE+0x14)

#define ID_MSG_MMC_MODE_IND                (ID_MSG_AT_BASE+0x20)

#define ID_MSG_AT_FW_END                   (ID_MSG_AT_BASE+0x50)



#define ID_MSG_AT_CMD_BASE                   0x0FFFFFFF
#define ID_MSG_AT_CMD_ERROR_IND              (ID_MSG_AT_CMD_BASE+0x00)
#define ID_MSG_AT_CMD_STATUS_IND             (ID_MSG_AT_CMD_BASE+0x00)


/* TODO:
 */
typedef struct
{
    VOS_UINT32 ulResult;
    VOS_UINT8  aucSysMode[4];
} AT_FW_MMC_SYS_MODE_IND_STRU;

/*****************************************************************************
 PID����
*****************************************************************************/
#if defined(WIN32_DEMO) /* DEMOʹ�ã���������Ҫ����OSA���ͷ�ļ�.*/
#define MSP_L4_AT_FW_PID                    100 
#define MSP_L4_AT_LTE_PID                   101
#define MSP_L4_AT_GU_PID                    102
#endif

#define AT_FW_URC_RPT_DISABLE               0
#define AT_FW_URC_RPT_ENABLE                1
#define AT_FW_URC_RPT_AUTO                  2

#define AT_FW_SYS_MODE_NULL                 0x00
#define AT_FW_SYS_MODE_GSM                  0x01
#define AT_FW_SYS_MODE_WCDMA                0x02
#define AT_FW_SYS_MODE_LTE                  0x04
#define AT_FW_SYS_MODE_CDMA                 0x08
#define AT_FW_SYS_MODE_TDSCDMA              0x10
#define AT_FW_SYS_MODE_AUTO                 0xFF

#define AT_FW_PACKET_FMT_STREAM             0x01
#define AT_FW_PACKET_FMT_BINARY             0x02


#define AT_FW_CLIENT_CHANNEL_STATUS_AT      0x00
#define AT_FW_CLIENT_CHANNEL_STATUS_OM      0x01

#define AT_FW_CLIENT_NAME_LEN               16
#define AT_FW_CMD_NAME_LEN                  16



enum AT_FW_CAMPON_RESULT_ENUM
{
    EN_AT_FW_CAMPON_OVER     = 0x00,
    EN_AT_FW_CAMPON_BEING    = 0x01,
    EN_AT_FW_CAMPON_BUTT     = 0xFF
};


/* ATFW��Ϣ��ʽ*/
typedef struct
{
    VOS_UINT32 ulMsgId;
    VOS_UINT32 pMsgParam[0];
} AT_FW_MSG_STRU;

/* Client ����*/
enum
{
    EN_AT_FW_CLIENT_ID_AUTO     = 0x00,
    EN_AT_FW_CLIENT_ID_PCUI1    = 0x01,         /* AT��PC��Ӧ�ÿͻ��ˣ���mobile partner
 */
    EN_AT_FW_CLIENT_ID_PCUI2    = 0x02,         /* AT��PC��Ӧ�ÿͻ��ˣ��糬���ն�
 */
    EN_AT_FW_CLIENT_ID_NCMCTRL  = 0x03,         /* ��������
 */
    EN_AT_FW_CLIENT_ID_EQU      = 0x10,         /* AT��װ���ͻ���
 */
    EN_AT_FW_CLIENT_ID_PPP      = 0x11,         /* PPPģ��ͻ���
 */
    EN_AT_FW_CLIENT_ID_NDIS     = 0x12,         /* NDISģ��ͻ���
 */
    EN_AT_FW_CLIENT_ID_DIAG     = 0x20,         /* DIAGģ��ͻ���
 */
    EN_AT_FW_CLIENT_ID_OM       = 0x21,         /* OMģ��ͻ���
 */
    EN_AT_FW_CLIENT_ID_OM_AGENT = 0x22,
    EN_AT_FW_CLIENT_ID_ALL      = 0xFF
};

typedef struct
{
    const VOS_UINT8  *pszCmdName;
} AT_FW_CMD_NAME_STRU;


/* URC�ϱ��������������*/
typedef struct
{
    VOS_UINT16 usCmdNum;
    VOS_UINT16 ausReserved[3];
    const AT_FW_CMD_NAME_STRU  *pszUrcElementTbl;
} AT_FW_CMD_URC_DISCARD_STRU;



/*****************************************************************************
 ���� : �ͻ���ע��
 ID   : ID_MSG_AT_FW_CLIENT_REGISTER_REQ
        ID_MSG_AT_FW_CLIENT_REGISTER_CNF
 REQ  : AT_FW_CLIENT_REGISTER_REQ_STRU
 CNF  : AT_FW_CLIENT_REGISTER_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucInterfaceCfg;  /* AT_FW_URC_RPT_DISABLE/ENABLE/AUTO , AT_FW_PACKET_FMT_STREAM/BINARY*/
    VOS_UINT8 ucSysMode;       /* AT_FW_SYS_MODE_NULL/GSM/WCDMA/LTE/CDMA/TDSCDMA/AUTO*/
    VOS_UINT8 ucReserved;
    VOS_BOOL bRegister;
    VOS_CHAR szName[AT_FW_CLIENT_NAME_LEN];
    const AT_FW_CMD_URC_DISCARD_STRU* pstDiscardUrc;
} AT_FW_CLIENT_REGISTER_REQ_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved[3];
    VOS_UINT32 ulRc;
} AT_FW_CLIENT_REGISTER_CNF_STRU;


/*****************************************************************************
 ���� : �ͻ�������
 ID   : ID_MSG_AT_FW_CLIENT_CONFIG_REQ
        ID_MSG_AT_FW_CLIENT_CONFIG_CNF
        ID_MSG_AT_FW_CLIENT_CONFIG_IND
 REQ  : AT_FW_CLIENT_CONFIG_REQ_STRU
 CNF  : AT_FW_CLIENT_CONFIG_CNF_STRU
 IND  : AT_FW_CLIENT_CONFIG_IND_STRU
*****************************************************************************/  
typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved[3];
    VOS_UINT8 ucConfigClientId;
    VOS_UINT8 ucInterfaceCfg;  /* AT_FW_URC_RPT_DISABLE/ENABLE/AUTO , AT_FW_PACKET_FMT_STREAM/BINARY*/
    VOS_UINT16 usCmdNum;
    const AT_FW_CMD_NAME_STRU  *pszUrcFilterTbl;
} AT_FW_CLIENT_CONFIG_REQ_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved[3];
    VOS_UINT32 ulRc;
} AT_FW_CLIENT_CONFIG_CNF_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved[3];
    VOS_BOOL  bRtsCts;
    VOS_UINT16 usBaudRate;
    VOS_UINT8 ucReserved1[2];
} AT_FW_CLIENT_CONFIG_IND_STRU;


/*****************************************************************************
 ���� : �ͻ���״̬�ϱ�
 ID   : ID_MSG_AT_FW_CLIENT_STATUS_IND
 IND  : AT_FW_CLIENT_STATUS_IND_STRU
*****************************************************************************/  
typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucStatus;
    VOS_UINT8 ucReserved[2];
} AT_FW_CLIENT_STATUS_IND_STRU;


/*****************************************************************************
 ���� : �ͻ�������������
 ID   : ID_MSG_AT_FW_CMD_STREAM_REQ
        ID_MSG_AT_FW_CMD_STREAM_CNF
        ID_MSG_AT_FW_CMD_STREAM_IND
 REQ  : AT_FW_CMD_STREAM_REQ_STRU
 CNF  : AT_FW_CMD_STREAM_CNF_STRU
 IND  : AT_FW_CMD_STREAM_IND_STRU
*****************************************************************************/  
typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucBuildPacketFmt;
    VOS_UINT16 usStreamSize;
    VOS_UINT8  pStream[0];
} AT_FW_CMD_STREAM_REQ_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved;
    VOS_UINT16 usStreamSize;
    VOS_UINT8  pStream[0];
} AT_FW_CMD_STREAM_CNF_STRU;

typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved;
    VOS_UINT16 usStreamSize;
    VOS_UINT8  pStream[0];
} AT_FW_CMD_STREAM_IND_STRU;


/*****************************************************************************
 ���� : �ͻ��˶�������Ϣ����
 ID   : ID_MSG_AT_FW_CMD_BINARY_MSG
 IND  : AT_FW_CMD_BINARY_MSG_STRU
*****************************************************************************/  
typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucSysMode;
    VOS_UINT16 usMsgSize;
    VOS_UINT32 ulMsgId;
    VOS_UINT8  pMsg[0];
} AT_FW_CMD_BINARY_MSG_STRU;


/*****************************************************************************
 ���� : ������ʽ����
 ID   : ID_MSG_AT_FW_CMD_PARAM_REQ
 IND  : AT_FW_CMD_PARAM_REQ_STRU
*****************************************************************************/  
typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved;
    VOS_UINT16 usDataSize;
    VOS_UINT8  pData[0];
} AT_FW_CMD_PARAM_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                   ulMsgId;           /* ��Ϣ�� */
    VOS_UINT32                   ulClientId;        /* �˿ں�*/
    VOS_UINT32                   ulLen;             /* ���ݳ��� */
    VOS_UINT8                    pContext[0];       /* ������ʵ��ַ*/
}AT_FW_DATA_MSG_STRU;


#if 0
/* AT������Ϣͨ���e�`����*/
typedef struct
{
    VOS_UINT8 ucClientId;
    VOS_UINT8 ucReserved[3];
    VOS_UINT32 ulMsgId;
    VOS_UINT32 ulRc;
} AT_CMD_ERROR_IND_STRU;
#endif


#ifdef __cplusplus
}
#endif


#endif /*__MSP_AT_H__*/

