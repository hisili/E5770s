

#ifndef __IMSAMMAINTERFACE_H__
#define __IMSAMMAINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"
#include "TafClientApi.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/


#define MMA_IMSA_MSG_ID_HEADER        TAF_MMA_IMSA_MSG_BASE


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
 ö����    : IMSA_CONTROL_CONN_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : �ڲ���ϢID����
*****************************************************************************/
enum    MMA_IMSA_MSG_ID_ENUM
{
    /* MMA����IMSA����Ϣԭ�� */
    ID_MMA_IMSA_START_REQ               = 0x00 + MMA_IMSA_MSG_ID_HEADER,        /* _H2ASN_MsgChoice MMA_IMSA_START_REQ_STRU */
    ID_MMA_IMSA_STOP_REQ                ,                                       /* _H2ASN_MsgChoice MMA_IMSA_STOP_REQ_STRU */
    ID_MMA_IMSA_DEREG_REQ               ,                                       /* _H2ASN_MsgChoice MMA_IMSA_DEREGISTER_REQ_STRU */
    ID_MMA_IMSA_SERVICE_CHANGE_IND      ,                                       /* _H2ASN_MsgChoice MMA_IMSA_SERVICE_CHANGE_IND_STRU */
    ID_MMA_IMSA_CAMP_INFO_CHANGE_IND,                                           /* _H2ASN_MsgChoice MMA_IMSA_CAMP_INFO_CHANGE_IND_STRU */


    /* IMSA����MMA����Ϣԭ�� */
    ID_IMSA_MMA_START_CNF               = 0x40 + MMA_IMSA_MSG_ID_HEADER,        /* _H2ASN_MsgChoice IMSA_MMA_START_CNF_STRU */
    ID_IMSA_MMA_STOP_CNF                ,                                       /* _H2ASN_MsgChoice IMSA_MMA_STOP_CNF_STRU */
    ID_IMSA_MMA_DEREG_CNF               ,                                       /* _H2ASN_MsgChoice IMSA_MMA_DEREGISTER_CNF_STRU */
    ID_IMSA_MMA_IMS_VOICE_CAP_NOTIFY    ,                                       /* _H2ASN_MsgChoice IMSA_MMA_IMS_VOICE_CAP_NOTIFY_STRU */
    ID_IMSA_MMA_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32 MMA_IMSA_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  4 Enum
*****************************************************************************/


enum MMA_IMSA_IMS_VOPS_INDICATOR_ENUM
{
    MMA_IMSA_IMS_VOPS_NOT_SUPPORT =0,
    MMA_IMSA_IMS_VOPS_SUPPORT,
    MMA_IMSA_IMS_VOPS_BUTT
};
typedef VOS_UINT8 MMA_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8;

enum MMA_IMSA_EMS_INDICATOR_ENUM
{
    MMA_IMSA_EMS_NOT_SUPPORT =0,
    MMA_IMSA_EMS_SUPPORT,
    MMA_IMSA_EMS_BUTT
};
typedef VOS_UINT8 MMA_IMSA_EMS_INDICATOR_ENUM_UINT8;

enum MMA_IMSA_RAT_TYPE_ENUM
{
    MMA_IMSA_RAT_TYPE_GSM =0,
    MMA_IMSA_RAT_TYPE_UTRAN,
    MMA_IMSA_RAT_TYPE_LTE,
    MMA_IMSA_RAT_TYPE_BUTT
};
typedef VOS_UINT8 MMA_IMSA_RAT_TYPE_ENUM_UINT8;

enum MMA_IMSA_SERVICE_STATUS_ENUM
{
    MMA_IMSA_NORMAL_SERVICE =0,
    MMA_IMSA_LIMITED_SERVICE,
    MMA_IMSA_NO_SERVICE,
    MMA_IMSA_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 MMA_IMSA_SERVICE_STATUS_ENUM_UINT8;

enum MMA_IMSA_ACCESS_TYPE_ENUM
{
    MMA_IMSA_ACCESS_TYPE_UTRAN_TDD,
    MMA_IMSA_ACCESS_TYPE_UTRAN_FDD,
    MMA_IMSA_ACCESS_TYPE_EUTRAN_TDD,
    MMA_IMSA_ACCESS_TYPE_EUTRAN_FDD,
    MMA_IMSA_ACCESS_TYPE_GERAN,

    MMA_IMSA_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8 MMA_IMSA_ACCESS_TYPE_ENUM_UINT8;

enum MMA_IMSA_IMS_VOICE_CAP_ENUM
{
    MMA_IMSA_IMS_VOICE_CAP_UNAVAILABLE = 0,
    MMA_IMSA_IMS_VOICE_CAP_AVAILABLE,

    MMA_IMSA_IMS_VOICE_CAP_BUTT
};
typedef VOS_UINT8 MMA_IMSA_IMS_VOICE_CAP_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
typedef struct
{
    /* �߼���������ulMcc��0�ֽڱ�ʾMCC digit1�� ulMcc��1�ֽڱ�ʾMCC digit2��
       ulMcc��2�ֽڱ�ʾMCC digit3��ulMcc��3�ֽ���Ч��
       �߼���������ulMnc��0�ֽڱ�ʾMNC digit1�� ulMnc��1�ֽڱ�ʾMNC digit2��
       ulMnc��2�ֽڱ�ʾMNC digit3��ulMnc��3�ֽ���Ч��
       ����MCC+MNCΪ46001����ulMccΪ0x00000604,ulMncΪ0x000f0100*/
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
}MMA_IMSA_PLMN_ID_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMA_IMSA_MSG_ID_ENUM_UINT32         ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}MMA_IMSA_START_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMA_IMSA_MSG_ID_ENUM_UINT32         ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}IMSA_MMA_START_CNF_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_CALL_RESULT_ACTION_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSA_CALL_RESULT_ACTION_IND_STRU��Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMA_IMSA_MSG_ID_ENUM_UINT32         ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}MMA_IMSA_STOP_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMA_IMSA_MSG_ID_ENUM_UINT32         ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}IMSA_MMA_STOP_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMA_IMSA_MSG_ID_ENUM_UINT32         ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}MMA_IMSA_DEREGISTER_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMA_IMSA_MSG_ID_ENUM_UINT32         ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT8                           aucReserve[4];
}IMSA_MMA_DEREGISTER_CNF_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    MMA_IMSA_MSG_ID_ENUM_UINT32                             ulMsgId;            /*_H2ASN_Skip*/
    MMA_IMSA_IMS_VOPS_INDICATOR_ENUM_UINT8                  enImsVoPsInd;
    MMA_IMSA_EMS_INDICATOR_ENUM_UINT8                       enEmsInd;
    MMA_IMSA_SERVICE_STATUS_ENUM_UINT8                      enPsServiceStatus;
    VOS_UINT8                                               ucPsSimValid;       /* VOS_TRUE :��Ч��VOS_FALSE :��Ч*/
    MMA_IMSA_RAT_TYPE_ENUM_UINT8                            enRat;              /* ��ǰ���뼼�� */
    VOS_UINT8                                               aucReserve[3];
}MMA_IMSA_SERVICE_CHANGE_IND_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                  /*_H2ASN_Skip*/
    MMA_IMSA_MSG_ID_ENUM_UINT32         ulMsgId;                    /*_H2ASN_Skip*/
    VOS_UINT8                           ucRoamingFlg;               /* VOS_TRUE :���Σ�VOS_FALSE :������ */

    MMA_IMSA_ACCESS_TYPE_ENUM_UINT8     enAccessType;
    VOS_UINT8                           aucReserved[2];
    VOS_UINT16                          usLac;
    VOS_UINT16                          usTac;
    MMA_IMSA_PLMN_ID_STRU               stPlmnId;
    VOS_UINT32                          ulCellId;
}MMA_IMSA_CAMP_INFO_CHANGE_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    MMA_IMSA_MSG_ID_ENUM_UINT32         ulMsgId;            /*_H2ASN_Skip*/
    MMA_IMSA_IMS_VOICE_CAP_ENUM_UINT8   enImsVoiceCap;
    VOS_UINT8                           aucRsv[3];
}IMSA_MMA_IMS_VOICE_CAP_NOTIFY_STRU;





typedef struct
{
    MMA_IMSA_MSG_ID_ENUM_UINT32         ulMsgId;            /*_H2ASN_MsgChoice_Export MMA_IMSA_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMA_IMSA_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}MMA_IMSA_MSG_DATA;
/*_H2ASN_Length UINT32*/


typedef struct
{
    VOS_MSG_HEADER
    MMA_IMSA_MSG_DATA                    stMsgData;
} ImsaMmaInterface_MSG;


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

#endif /* end of ImsaMmaInterface.h */

