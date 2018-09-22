

#ifndef __FCINTRAMSG_H__
#define __FCINTRAMSG_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "FcInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/
enum FC_MSG_TYPE_ENUM
{
    ID_FC_CPU_A_OVERLOAD_IND            = 0x0001,           /* _H2ASN_MsgChoice FC_CPULOAD_IND_STRU */
    ID_FC_CPU_A_UNDERLOAD_IND           = 0x0002,           /* _H2ASN_MsgChoice FC_CPULOAD_IND_STRU */
    ID_FC_TEMPERATURE_OVERLOAD_IND      = 0x0003,           /* _H2ASN_MsgChoice FC_TEMPERATURE_IND_STRU */
    ID_FC_TEMPERATURE_UNDERLOAD_IND     = 0x0004,           /* _H2ASN_MsgChoice FC_TEMPERATURE_IND_STRU */
    ID_FC_TEMPERATURE_RECOVER_IND       = 0x0005,           /* _H2ASN_MsgChoice FC_TEMPERATURE_IND_STRU */
    ID_FC_SET_GPRS_FLOWCTRL_IND         = 0x0006,           /* _H2ASN_MsgChoice FC_SET_GPRS_FLOWCTRL_IND_STRU */
    ID_FC_STOP_GPRS_FLOWCTRL_IND        = 0x0007,           /* _H2ASN_MsgChoice FC_STOP_GPRS_FLOWCTRL_IND_STRU */
    ID_FC_SET_POINT_FLOWCTRL_IND        = 0x0008,           /* _H2ASN_MsgChoice FC_SET_POINT_FLOWCTRL_IND_STRU */
    ID_FC_STOP_POINT_FLOWCTRL_IND       = 0x0009,           /* _H2ASN_MsgChoice FC_STOP_POINT_FLOWCTRL_IND_STRU */
    ID_FC_REG_POINT_IND                 = 0x000A,           /* _H2ASN_MsgChoice FC_REG_POINT_IND_STRU */
    ID_FC_DEREG_POINT_IND               = 0x000B,           /* _H2ASN_MsgChoice FC_DEREG_POINT_IND_STRU */
    ID_FC_CHANGE_POINT_IND              = 0x000C,           /* _H2ASN_MsgChoice FC_CHANGE_POINT_IND_STRU */
    ID_FC_ADD_RAB_FCID_MAP_IND          = 0x000D,           /* _H2ASN_MsgChoice FC_ADD_RAB_FCID_MAP_IND_STRU */
    ID_FC_DEL_RAB_FCID_MAP_IND          = 0x000E,           /* _H2ASN_MsgChoice FC_DEL_RAB_FCID_MAP_IND_STRU */
    ID_FC_MEM_UP_TO_TARGET_PRI_IND      = 0x000F,           /* _H2ASN_MsgChoice FC_MEM_UP_TO_TARGET_PRI_IND_STRU */
    ID_FC_MEM_DOWN_TO_TARGET_PRI_IND    = 0x0010,           /* _H2ASN_MsgChoice FC_MEM_DOWN_TO_TARGET_PRI_IND_STRU */
    ID_FC_CPU_C_OVERLOAD_IND            = 0x0011,           /* _H2ASN_MsgChoice FC_CPULOAD_IND_STRU */
    ID_FC_CPU_C_UNDERLOAD_IND           = 0x0012,           /* _H2ASN_MsgChoice FC_CPULOAD_IND_STRU */
    ID_FC_GPRS_C_FLOWCTRL_NOTIFY        = 0x0013,           /* _H2ASN_MsgChoice FC_GPRS_FLOWCTRL_NOTIFY_STRU */
    ID_FC_ACORE_CRESET_START_IND        = 0x0014,           /* _H2ASN_MsgChoice FC_ACORE_CRESET_IND_STRU */
    ID_FC_ACORE_CRESET_END_IND          = 0x0015,           /* _H2ASN_MsgChoice FC_ACORE_CRESET_IND_STRU */
    ID_FC_ACORE_CRESET_START_RSP        = 0x0016,           /* _H2ASN_MsgChoice FC_ACORE_CRESET_RSP_STRU */
    ID_FC_ACORE_CRESET_END_RSP          = 0x0017,           /* _H2ASN_MsgChoice FC_ACORE_CRESET_RSP_STRU */

    ID_FC_MSG_TYPE_BUTT                 = 0xFFFF
};
typedef VOS_UINT16 FC_MSG_TYPE_ENUM_UINT16;


/*****************************************************************************
  3 �궨��
*****************************************************************************/


/*****************************************************************************
  4 STRUCT����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulCpuLoad;
    VOS_UINT32                          ulUlRate;
    VOS_UINT32                          ulDlRate;
}FC_CPULOAD_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT16                          usTemperature;
}FC_TEMPERATURE_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
}FC_SET_GPRS_FLOWCTRL_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
}FC_GPRS_FLOWCTRL_NOTIFY_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
}FC_STOP_GPRS_FLOWCTRL_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    FC_ID_ENUM_UINT32                   enFcId;
}FC_SET_POINT_FLOWCTRL_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    FC_ID_ENUM_UINT32                   enFcId;
}FC_STOP_POINT_FLOWCTRL_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    FC_REG_POINT_STRU                   stFcPoint;
}FC_REG_POINT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;      /* _H2ASN_Replace VOS_UINT16  enModemId; */
    FC_ID_ENUM_UINT32                   enFcId;
}FC_DEREG_POINT_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;      /* _H2ASN_Replace VOS_UINT16  enModemId; */
    FC_ID_ENUM_UINT32                   enFcId;
    FC_POLICY_ID_ENUM_UINT8             enPolicyId;
    VOS_UINT8                           aucRsv2[3];
    FC_PRI_ENUM_UINT32                  enPri;
}FC_CHANGE_POINT_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;      /* _H2ASN_Replace VOS_UINT16  enModemId; */
    FC_ID_ENUM_UINT32                   enFcId;
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucRsv2[3];
} FC_ADD_RAB_FCID_MAP_IND_STRU;

#if 0
typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucRsv[1];
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT8                           aucRsv2[2];
} FC_DEL_RAB_FCID_MAP_IND_STRU;
#endif
typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    MODEM_ID_ENUM_UINT16                enModemId;      /* _H2ASN_Replace VOS_UINT16  enModemId; */
    VOS_UINT8                           ucRabId;
    VOS_UINT8                           aucRsv[3];
} FC_DEL_RAB_FCID_MAP_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT16                          usMemFreeCnt;
    FC_PRI_ENUM_UINT32                  enTargetPri;
} FC_MEM_UP_TO_TARGET_PRI_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT16                          usMemFreeCnt;
    FC_PRI_ENUM_UINT32                  enTargetPri;
} FC_MEM_DOWN_TO_TARGET_PRI_IND_STRU;

/*****************************************************************************
 �ṹ��    : FC_ACORE_CRESET_IND_STRU
 Э����  : ��
 ASN.1���� : ��
 �ṹ˵��  : C�˵�����λ�����У�����֪ͨFcACore��ָʾ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
}FC_ACORE_CRESET_IND_STRU;

/*****************************************************************************
 �ṹ��    : FC_ACORE_CRESET_RSP_STRU
 Э����  : ��
 ASN.1���� : ��
 �ṹ˵��  : C�˵�����λ�����У�FcACore��ɻص�������֪ͨ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /* _H2ASN_Skip */
    FC_MSG_TYPE_ENUM_UINT16             usMsgName;      /* _H2ASN_Skip */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulResult;
}FC_ACORE_CRESET_RSP_STRU;

/*****************************************************************************
  5 OTHERS����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    FC_MSG_TYPE_ENUM_UINT16             enMsgID;    /*_H2ASN_MsgChoice_Export FC_MSG_TYPE_ENUM_UINT16*/

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          FC_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}FC_INTRA_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    FC_INTRA_MSG_DATA                   stMsgData;
}FcIntraMsg_MSG;


/******************************************************************************
   6 �ⲿ��������
******************************************************************************/


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

#endif /* FcIntraMsg.h */


