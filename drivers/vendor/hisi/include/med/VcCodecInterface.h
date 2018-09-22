

#ifndef __VCCODECINTERFACE_H__
#define __VCCODECINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum VC_VOICE_MSG_ID_ENUM
{
    /*  ARM->HIFI */
    ID_VC_VOICE_BASE            = 0x9400,
    ID_VC_VOICE_START_REQ       = 0x9402,       /*������������*/                /* _H2ASN_MsgChoice VCVOICE_START_REQ_STRU */
    ID_VC_VOICE_STOP_REQ        = 0x9403,       /*�������ֹͣ����*/            /* _H2ASN_MsgChoice VCVOICE_STOP_REQ_STRU */
    ID_VC_VOICE_SET_DEVICE_REQ  = 0x9404,       /*���������������*/            /* _H2ASN_MsgChoice VCVOICE_SET_DEVICE_REQ_STRU */
    ID_VC_VOICE_SET_VOLUME_REQ  = 0x9405,       /*���������������*/            /* _H2ASN_MsgChoice VCVOICE_SET_VOLUME_REQ_STRU */
    ID_VC_VOICE_SET_CODEC_REQ   = 0x9407,       /*������Դ��������*/          /* _H2ASN_MsgChoice VCVOICE_SET_CODEC_REQ_STRU */
    ID_VC_VOICE_FOREGROUND_REQ  = 0x940A,       /*����Ϊǰ̨ͨ·*/              /* _H2ASN_MsgChoice VCVOICE_FOREGROUND_REQ_STRU */
    ID_VC_VOICE_BACKGROUND_REQ  = 0x940B,       /*����Ϊ��̨ͨ·*/              /* _H2ASN_MsgChoice VCVOICE_BACKGROUND_REQ_STRU */
    ID_VC_VOICE_GROUND_QRY      = 0x940C,       /*��ѯͨ·״̬ */               /* _H2ASN_MsgChoice VCVOICE_GROUND_QRY_STRU */
    /* Added by z60575 for VOICE_LOOP, 2013-7-2 begin */
    ID_VC_VOICE_LOOP_REQ        = 0x940D,       /* ���û��� */                  /* _H2ASN_MsgChoice VCVOICE_LOOP_REQ_STRU */
    /* Added by z60575 for VOICE_LOOP, 2013-7-2 end */

    /*  HIFI->ARM */
    ID_VOICE_VC_BASE            = 0x4900,
    ID_VOICE_VC_START_CNF       = 0x4902,       /*��ӦVC_VOICE_START_REQ*/      /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_STOP_CNF        = 0x4903,       /*��ӦVC_VOICE_STOP_REQ*/       /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_DEVICE_CNF  = 0x4904,       /*��ӦVC_VOICE_SET_DEVICE_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_VOLUME_CNF  = 0x4905,       /*��ӦVC_VOICE_SET_VOLUME_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_SET_CODEC_CNF   = 0x4907,       /*��ӦVC_VOICE_SET_CODEC_REQ*/  /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_FOREGROUND_CNF  = 0x490A,       /*��ӦVC_VOICE_FOREGROUND_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_BACKGROUND_CNF  = 0x490B,       /*��ӦVC_VOICE_BACKGROUND_REQ*/ /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    ID_VOICE_VC_GROUND_RSP      = 0x490C,       /*��ӦVC_VOICE_GROUND_QRY*/     /* _H2ASN_MsgChoice VCVOICE_GROUND_RSP_STRU */
    /* Added by z60575 for VOICE_LOOP, 2013-7-2 begin */
    ID_VOICE_VC_LOOP_CNF        = 0x490D,       /* ���û�����Ӧ */              /* _H2ASN_MsgChoice VCVOICE_OP_RSLT_STRU */
    /* Added by z60575 for VOICE_LOOP, 2013-7-2 end */

    VC_VOICE_MSG_ID_BUTT
};
typedef VOS_UINT16 VC_VOICE_MSG_ID_ENUM_UINT16;

enum VCVOICE_NET_MODE_ENUM
{
    VCVOICE_NET_MODE_GSM         = 0,
    VCVOICE_NET_MODE_WCDMA,
    VCVOICE_NET_MODE_TDSCDMA,
    VCVOICE_NET_MODE_IMS_EUTRAN,
    VCVOICE_NET_MODE_BUTT
};
typedef VOS_UINT16 VCVOICE_NET_MODE_ENUM_UINT16;

enum VCVOICE_TYPE_ENUM
{
    VCVOICE_TYPE_AMR      = 0,                                                  /* amr */
    VCVOICE_TYPE_EFR,                                                           /* enhanced full rate */
    VCVOICE_TYPE_FR,                                                            /* full rate */
    VCVOICE_TYPE_HR,                                                            /* half rate */
    VCVOICE_TYPE_AMR2,                                                          /* amr2 */
    VCVOICE_TYPE_AMRWB,                                                         /* AMR-WB */
    VCVOICE_TYPE_G711,                                                          /* G711 */
    VCVOICE_TYPE_BUTT                                                           /* invalid value */
};
typedef VOS_UINT16  VCVOICE_TYPE_ENUM_UINT16;

enum VCVOICE_EXECUTE_RSLT_ENUM
{
    VCVOICE_EXECUTE_RSLT_SUCC = 0,                                              /* 0 �ɹ� */
    VCVOICE_EXECUTE_RSLT_FAIL,                                                  /* 1 ʧ�� */
    VCVOICE_EXECUTE_RSLT_NULL_PTR,                                              /* 2 ��ָ�� */
    VCVOICE_EXECUTE_RSLT_PARA_ERR,                                              /* 3 �������� */
    VCVOICE_EXECUTE_RSLT_STATE_ERR,                                             /* 4 ״̬���� */
    VCVOICE_EXECUTE_RSLT_UNKNOWN_MSG,                                           /* 5 δ֪��Ϣ */

    VCVOICE_EXECUTE_RSLT_BUTT
};
typedef VOS_UINT16  VCVOICE_EXECUTE_RSLT_ENUM_UINT16;

enum VCVOICE_VOLUME_TARGET_ENUM
{
    VCVOICE_VOLUME_TARGET_UP = 0,                                               /* 0 ���� */
    VCVOICE_VOLUME_TARGET_DOWN,                                                 /* 1 ���� */

    VCVOICE_VOLUME_TARGET_BUTT
};
typedef VOS_UINT16  VCVOICE_VOLUME_TARGET_ENUM_UINT16;

enum VCVOICE_WORK_TYPE_ENUM
{
    VCVOICE_WORK_TYPE_NORMAL = 0,                                               /* 0 ��������ģʽ */
    VCVOICE_WORK_TYPE_TEST,                                                     /* 1 ����ģʽ */
    VCVOICE_WORK_TYPE_BUTT
};
typedef VOS_UINT16  VCVOICE_WORK_TYPE_ENUM_UINT16;

/* ͨ��ģʽö�� */
enum VCVOICE_DEV_MODE_ENUM
{
    VCVOICE_DEV_MODE_HANDSET                = 0,                                /* �ֳ�ģʽ */
    VCVOICE_DEV_MODE_HANDFREE,                                                  /* ����ģʽ */
    VCVOICE_DEV_MODE_CARFREE,                                                   /* ��������ģʽ */
    VCVOICE_DEV_MODE_HEADSET,                                                   /* ����ģʽ */
    VCVOICE_DEV_MODE_BLUETOOTH,                                                 /* ����ģʽ */
    VCVOICE_DEV_MODE_PCVOICE,                                                   /* PC-VOICEģʽ */
    VCVOICE_DEV_MODE_HEADPHONE,                                                 /* ��������MIC�Ķ���ͨ�� */
    VCVOICE_DEV_MODE_SUPER_HANDFREE,                                            /* �������� */
    VCVOICE_DEV_MODE_SMART_TALK,                                                /* ����ͨ�� */
    VCVOICE_DEV_MODE_BUTT
};
typedef VOS_UINT16  VCVOICE_DEV_MODE_ENUM_UINT16;

/* ͨ·״̬ */
enum VCVOICE_GROUND_ENUM
{
    VCVOICE_GROUND_FOREGROUND               = 0,                                /* ǰ̨ģʽ */
    VCVOICE_GROUND_BACKGROUND,                                                  /* ��̨ģʽ */
    VCVOICE_GROUND_INVALID,                                                     /* �Ƿ� */
    VCVOICE_GROUND_BUTT
};
typedef VOS_UINT16  VCVOICE_GROUND_ENUM_UINT16;

/* Added by z60575 for VOICE_LOOP, 2013-7-2 begin */
/* ����״̬ */
enum VCVOICE_LOOP_ENUM
{
    VCVOICE_LOOP_STOP                       = 0,                                /* �˳�����ģʽ */
    VCVOICE_LOOP_START,                                                         /* ���뻷��ģʽ */
    VCVOICE_LOOP_BUTT
};
typedef VOS_UINT16  VCVOICE_LOOP_ENUM_UINT16;
/* Added by z60575 for VOICE_LOOP, 2013-7-2 end */

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

/*****************************************************************************
 �ṹ��    : VCCODEC_START_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* ���� */
    VCVOICE_NET_MODE_ENUM_UINT16        enMode;                                 /* ͨѶ������ʽ��0 G��1 W */
    VCVOICE_TYPE_ENUM_UINT16            enCodecType;                            /* ���������0 AMR��1 EFR��2 FR��3 HR��4 AMR2�� 5 AMRWB */
    VCVOICE_WORK_TYPE_ENUM_UINT16       enWorkType;                             /* ����ģʽ:0 ��������ģʽ 1: ����ģʽ */
    VOS_UINT16                          usReserve2;                             /* ���� */
}VCVOICE_START_REQ_STRU;


/*****************************************************************************
 �ṹ��    : VCCODEC_STOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ֹͣ����������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
}VCVOICE_STOP_REQ_STRU;


/*****************************************************************************
 �ṹ��    : VCVOICE_SET_DEVICE_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �����豸�����ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
    VCVOICE_DEV_MODE_ENUM_UINT16        usDeviceMode;                           /* �����豸��0 �ֳ֣�1 �ֳ����᣻2 �������᣻3 ������4 ������ 5 PC-VOICE  */
    VOS_UINT16                          usReserve2;                             /* ���� */
}VCVOICE_SET_DEVICE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCCODEC_SET_VOLUME_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������������������������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
    VCVOICE_VOLUME_TARGET_ENUM_UINT16   enVolTarget;
    VOS_INT16                           sVolValue;
}VCVOICE_SET_VOLUME_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCCODEC_SET_CODEC_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���������Դ��������������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
    VCVOICE_NET_MODE_ENUM_UINT16        enMode;                                 /* ͨѶ������ʽ��0 G��1 W */
    VCVOICE_TYPE_ENUM_UINT16            enCodecType;                            /* ���������0 AMR��1 EFR��2 FR��3 HR; 4 AMR2; 5 AMRWB */
}VCVOICE_SET_CODEC_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_FOREGROUND_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : VCģ������MED����·�绰����, ������������������ָ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
} VCVOICE_FOREGROUND_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_BACKGROUND_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : VCģ������MED����·�绰ȥ������н����˾���״̬�����е��������ͨ·�Ͽ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
} VCVOICE_BACKGROUND_REQ_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_GROUND_QRY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : VCģ���ѯ��ǰͨ·״̬(ǰ̨/��̨)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
} VCVOICE_GROUND_QRY_STRU;

/*****************************************************************************
 �ṹ��    : VCVOICE_GROUND_RSP_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��������ظ���ǰͨ·״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve;                              /* ���� */
    VCVOICE_GROUND_ENUM_UINT16          enState;                                /* ��ǰ״̬ */
    VOS_UINT16                          usReserve2;                             /* ���� */
} VCVOICE_GROUND_RSP_STRU;

/*****************************************************************************
 �ṹ��    : VCCODEC_OP_RSLT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��VC��Ϣ������Ӧ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* ���� */
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt;                              /* ִ�н�� */
    VOS_UINT16                          usReserve2;
}VCVOICE_OP_RSLT_STRU;

/* Added by z60575 for VOICE_LOOP, 2013-7-2 begin */
/*****************************************************************************
 �ṹ��    : VCVOICE_LOOP_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģʽ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          usMsgName;                              /* ԭ������ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usReserve1;                             /* ���� */
    VCVOICE_LOOP_ENUM_UINT16            enMode;                                 /* ��ǰ״̬ */
    VOS_UINT16                          usReserve2;
}VCVOICE_LOOP_REQ_STRU;
/* Added by z60575 for VOICE_LOOP, 2013-7-2 end */

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
#if 0                                                       /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
/* ��Ҫ������Ӧ��ASN����,ȥ��L��ʽ,������V��ʽ */
typedef struct
{
    VC_VOICE_MSG_ID_ENUM_UINT16         enMsgID;            /* _H2ASN_MsgChoice_Export VC_VOICE_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          VC_VOICE_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_VC_TRACE_MSG_DATA;

/* Э����Ϣ�ṹ*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_VC_TRACE_MSG_DATA               stMsgData;
}VoiceVcTrace_MSG;

#endif                                                     /* _H2ASN_Skip */

/*****************************************************************************
  10 ��������
*****************************************************************************/








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

#endif /* end of VcCodecInterface.h */
