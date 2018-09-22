

#ifndef __PSRRMINTERFACE_H__
#define __PSRRMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "PsTypeDef.h"
#include  "vos_Id.h"

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum PS_RRM_MSG_TYPE_ENUM
{
    ID_PS_RRM_RADIO_RESOURCE_APPLY_REQ                          = 0x0001,       /* _H2ASN_MsgChoice PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU */
    ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF                          = 0x0002,       /* _H2ASN_MsgChoice RRM_PS_RADIO_RESOURCE_APPLY_CNF_STRU */

    ID_PS_RRM_RADIO_RESOURCE_RELEASE_IND                        = 0x0003,       /* _H2ASN_MsgChoice PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU */

    ID_PS_RRM_REGISTER_IND                                      = 0x0004,       /* _H2ASN_MsgChoice PS_RRM_REGISTER_IND_STRU */
    ID_PS_RRM_DEREGISTER_IND                                    = 0x0005,       /* _H2ASN_MsgChoice PS_RRM_DEREGISTER_IND_STRU */

    ID_RRM_PS_STATUS_IND                                        = 0x0006,       /* _H2ASN_MsgChoice RRM_PS_STATUS_IND_STRU */

    ID_PS_RRM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 PS_RRM_MSG_TYPE_ENUM_UINT32;


enum RRM_PS_RAT_TYPE_ENUM
{
    RRM_PS_RAT_TYPE_NONE                    = 0,
    RRM_PS_RAT_TYPE_GSM                     = 1,
    RRM_PS_RAT_TYPE_WCDMA                   = 2,
    RRM_PS_RAT_TYPE_TDS                     = 3,
    RRM_PS_RAT_TYPE_LTE                     = 4,
    RRM_PS_RAT_TYPE_1X                      = 5,
    RRM_PS_RAT_TYPE_EVDO                    = 6,
    RRM_PS_RAT_TYPE_BUTT
};
typedef VOS_UINT8 RRM_PS_RAT_TYPE_ENUM_UINT8;



enum RRM_PS_TASK_TYPE_ENUM
{
    /* ��ʼ״̬������ */
    RRM_PS_TASK_TYPE_NONE                          = 0,

    /* 1-100���ڶ���NAS���� */
    RRM_PS_TASK_TYPE_NAS_SEARCH                    = 1,

    /* 101-200���ڶ���GSM���� */
    RRM_PS_TASK_TYPE_GSM_NAS_SPEC_SEARCH           = 111,
    RRM_PS_TASK_TYPE_GSM_NAS_LIST_SEARCH           = 112,

    /* 201-300���ڶ���WCDMA���� */
    RRM_PS_TASK_TYPE_WCDMA_NAS_SPEC_SEARCH         = 210,
    RRM_PS_TASK_TYPE_WCDMA_NAS_LIST_SEARCH         = 211,

    RRM_PS_TASK_TYPE_BUTT
};
typedef VOS_UINT16 RRM_PS_TASK_TYPE_ENUM_UINT16;


enum PS_RRM_RESULT_ENUM
{
    PS_RRM_RESULT_SUCCESS               = 0,
    PS_RRM_RESULT_FAIL                  = 1,
    PS_RRM_RESULT_BUTT
};
typedef VOS_UINT8 PS_RRM_RESULT_ENUM_UINT8;

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
    MSG_HEADER_STRU                             stMsgHeader;                    /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                        enModemId;                      /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_RAT_TYPE_ENUM_UINT8                  enRatType;                      /* ��Ҫʹ����Ƶ��Դ��ģʽ���������ϵͳ����������дĿ��ģʽ */
    VOS_UINT8                                   aucReserved[1];
}PS_RRM_RADIO_RESOURCE_APPLY_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* ��Ϣͷ */ /*_H2ASN_Skip*/
    PS_RRM_RESULT_ENUM_UINT8                    enResult;
    VOS_UINT8                                   aucReserved[3];
} RRM_PS_RADIO_RESOURCE_APPLY_CNF_STRU;



typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                        enModemId;                      /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_RAT_TYPE_ENUM_UINT8                  enRatType;                      /* �ͷ���Ƶ��Դ��ģʽ���������ϵͳ����������дĿ��ģʽ */
    VOS_UINT8                                   aucReserved[1];
}PS_RRM_RADIO_RESOURCE_RELEASE_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                        enModemId;                      /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_TASK_TYPE_ENUM_UINT16                enTaskType;                     /* ��Ч������ע�ᣬBUTT��ȥע�� */
    RRM_PS_RAT_TYPE_ENUM_UINT8                  enRatType;
    VOS_UINT8                                   aucReserved[3];
} PS_RRM_REGISTER_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MODEM_ID_ENUM_UINT16                        enModemId;                      /* _H2ASN_Replace VOS_UINT16 enModemId; */
    RRM_PS_TASK_TYPE_ENUM_UINT16                enTaskType;                     /* ��Ч������ע�ᣬBUTT��ȥע�� */
    RRM_PS_RAT_TYPE_ENUM_UINT8                  enRatType;
    VOS_UINT8                                   aucReserved[3];
} PS_RRM_DEREGISTER_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                             stMsgHeader;                    /* ��Ϣͷ */ /*_H2ASN_Skip*/
    RRM_PS_TASK_TYPE_ENUM_UINT16                enTaskType;
    VOS_UINT8                                   aucReserved[2];
} RRM_PS_STATUS_IND_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : PS_RRM_MSG_DATA
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PS_RRM_MSG_DATA���ݽṹ����������ASN�ļ�
*****************************************************************************/
typedef struct
{
    PS_RRM_MSG_TYPE_ENUM_UINT32                 enMsgId;                        /*_H2ASN_MsgChoice_Export PS_RRM_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                                   aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          PS_RRM_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
}PS_RRM_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : PsRrmInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PsRrmInterface_MSG���ݽṹ,��������ASN�ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    PS_RRM_MSG_DATA                             stMsgData;
}PsRrmInterface_MSG;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/





#if (VOS_OS_VER != VOS_WIN32)
 #pragma pack()
#else
 #pragma pack(pop)
#endif

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif

#endif /* end of PsRrmInterface.h */


