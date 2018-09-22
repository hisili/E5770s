
#ifndef  APP_VC_API_H
#define  APP_VC_API_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"
#include "vos.h"
#include "NasNvInterface.h"
/*****************************************************************************
  2 ��������
*****************************************************************************/


/*****************************************************************************
  3���Ͷ���
*****************************************************************************/
/* �����豸��0 �ֳ֣�1 �ֳ����᣻2 �������᣻3 ������4 ������7 �������᣻8 ����ͨ�� */
enum VC_PHY_DEVICE_MODE_ENUM
{
    VC_PHY_DEVICE_MODE_HANDSET,                                                 /* �ֳ� */
    VC_PHY_DEVICE_MODE_HANDS_FREE,                                              /* �ֳ����� */
    VC_PHY_DEVICE_MODE_CAR_FREE,                                                /* �������� */
    VC_PHY_DEVICE_MODE_EARPHONE,                                                /* ���� */
    VC_PHY_DEVICE_MODE_BLUETOOTH,                                               /* ���� */
    VC_PHY_DEVICE_MODE_PCVOICE,                                                 /* PC����ģʽ */
    VC_PHY_DEVICE_MODE_HEADPHONE,                                               /* ��������MIC�Ķ���ͨ�� */
    VC_PHY_DEVICE_MODE_SUPER_HANDFREE,                                              /* �������� */
    VC_PHY_DEVICE_MODE_SMART_TALK,                                              /* ����ͨ�� */

    VC_PHY_DEVICE_MODE_BUTT                                                     /* invalid value */
};
typedef VOS_UINT16  VC_PHY_DEVICE_MODE_ENUM_U16;

/*****************************************************************************
 ö����    : APP_VC_VOICE_MODE_ENUM
 �ṹ˵��  : STICK��̬�£��û�ͨ��^CVOICE˽���������õ�����ģʽö��
*****************************************************************************/
enum APP_VC_VOICE_MODE_ENUM
{
    APP_VC_VOICE_MODE_PCVOICE           = 0,
    APP_VC_VOICE_MODE_EARPHONE          = 1,
    APP_VC_VOICE_MODE_HANDSET           = 2,
    APP_VC_VOICE_MODE_HANDS_FREE        = 3,
    APP_VC_VOICE_MODE_BUTT
};
typedef VOS_UINT16 APP_VC_VOICE_MODE_ENUM_U16;

/*****************************************************************************
 ö����    : APP_VC_VOICE_PORT_ENUM
 �ṹ˵��  : ��������˿�ö��
*****************************************************************************/
enum APP_VC_VOICE_PORT_ENUM
{
    APP_VC_VOICE_PORT_MODEM             = 1,
    APP_VC_VOICE_PORT_DIAG              = 2,
    APP_VC_VOICE_PORT_PCUI              = 3,
    APP_VC_VOICE_PORT_PCVOICE           = 4,
    APP_VC_VOICE_PORT_PCSC              = 5,
    APP_VC_VOICE_PORT_BUTT
};
typedef VOS_UINT8 APP_VC_VOICE_PORT_ENUM_U8;

enum APP_VC_EVENT_ENUM
{
    APP_VC_EVT_PARM_CHANGED,                                                /*service para changed*/
    APP_VC_EVT_SET_VOLUME,
    APP_VC_EVT_SET_VOICE_MODE,
    APP_VC_EVT_GET_VOLUME,
    APP_VC_EVT_SET_MUTE_STATUS,
    APP_VC_EVT_GET_MUTE_STATUS,
    APP_VC_EVT_BUTT
};
typedef VOS_UINT32 APP_VC_EVENT_ENUM_U32;

enum APP_VC_MUTE_STATUS_ENUM
{
    APP_VC_MUTE_STATUS_UNMUTED          = 0,
    APP_VC_MUTE_STATUS_MUTED            = 1,
    APP_VC_MUTE_STATUS_BUTT
};
typedef VOS_UINT8 APP_VC_MUTE_STATUS_ENUM_UINT8;



enum APP_VC_MSG_ENUM
{
    APP_VC_MSG_REQ_SET_VOLUME   = 0,                                            /* ��������������Ϣ */
    APP_VC_MSG_REQ_SET_MODE,                                                    /* ����ͨ��ģʽ������Ϣ */

    APP_VC_MSG_REQ_QRY_MODE,                                                    /* ��ѯͨ��ģʽ������Ϣ */
    APP_VC_MSG_CNF_QRY_MODE,                                                    /* ��ѯͨ��ģʽ�ظ���Ϣ */

    APP_VC_MSG_REQ_SET_PORT,                                                    /* ���������˿�������Ϣ */
    APP_VC_MSG_CNF_SET_PORT,                                                    /* ���������˿ڻظ���Ϣ */

    APP_VC_MSG_REQ_QRY_PORT,                                                    /* ��ѯ�����˿�������Ϣ */
    APP_VC_MSG_CNF_QRY_PORT,                                                    /* ��ѯ�����˿ڻظ���Ϣ */

    APP_VC_MSG_REQ_QRY_VOLUME,
    APP_VC_MSG_CNF_QRY_VOLUME,

    APP_VC_MSG_SET_MUTE_STATUS_REQ,                                             /* ���þ���״̬������Ϣ */
    APP_VC_MSG_GET_MUTE_STATUS_REQ,                                             /* ��ȡ����״̬������Ϣ */

    APP_VC_MSG_SET_FOREGROUND_REQ,                                              /* ����ǰ̨ģʽ������Ϣ */
    APP_VC_MSG_SET_FOREGROUND_CNF,                                              /* ����ǰ̨ģʽ�ظ���Ϣ */

    APP_VC_MSG_SET_BACKGROUND_REQ,                                              /* ���ú�̨ģʽ������Ϣ */
    APP_VC_MSG_SET_BACKGROUND_CNF,                                              /* ���ú�̨ģʽ�ظ���Ϣ */

    APP_VC_MSG_FOREGROUND_QRY,                                                  /* ģʽ��ѯ������Ϣ */
    APP_VC_MSG_FOREGROUND_RSP,                                                  /* ģʽ��ѯ�ظ���Ϣ */

    APP_VC_MSG_SET_MODEMLOOP_REQ,                                               /* ������������ģʽ��Ϣ */

    APP_VC_MSG_BUTT
};
typedef VOS_UINT16  APP_VC_MSG_ENUM_U16;


enum APP_VC_QRY_GROUND_ENUM
{
    APP_VC_FOREGROUND                   = 0,
    APP_VC_BACKGROUND                   = 1,
    APP_VC_GROUND_INVALID               = 2,
    APP_VC_GROUND_BUTT
};
typedef VOS_UINT16 APP_VC_QRY_GROUND_ENUM_U16;


enum APP_VC_START_HIFI_ORIG_ENUM
{
    APP_VC_START_HIFI_ORIG_CALL                   = 0,
    APP_VC_START_HIFI_ORIG_IMSA                   = 1,
    APP_VC_START_HIFI_ORIG_BUTT
};
typedef VOS_UINT8 APP_VC_START_HIFI_ORIG_ENUM_UINT8;


typedef struct
{
    VOS_MSG_HEADER
    APP_VC_MSG_ENUM_U16                 enMsgName;                              /* ��Ϣ�� */
    VOS_UINT8                           aucReserve1[2];                         /* ���� */
    MN_CLIENT_ID_T                      clientId;                               /* Client ID */
    MN_OPERATION_ID_T                   opId;                                   /* Operation ID */
    VOS_UINT8                           aucReserve2;                            /* ���� */
    VOS_UINT8                           aucContent[4];                          /* ��Ϣ���� */
} APP_VC_REQ_MSG_STRU;



typedef struct
{
    VOS_BOOL                            bSuccess;                               /*set(get) success or failure */
    VOS_UINT32                          ulErrCode;
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;
    APP_VC_VOICE_PORT_ENUM_U8           enVoicePort;
    VC_PHY_DEVICE_MODE_ENUM_U16         enDevMode;
    VOS_UINT16                          usVolume;
    APP_VC_MUTE_STATUS_ENUM_UINT8       enMuteStatus;
    VOS_UINT8                           aucRsv[3];
}APP_VC_EVENT_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucQryRslt;                              /* ��ѯ success or failure */
    VOS_UINT8                           aucReserved;
    APP_VC_QRY_GROUND_ENUM_U16          enGround;                               /* ��ѯ��� */
}APP_VC_QRY_GROUNG_RSP_STRU;

/*****************************************************************************
  4 �궨��
*****************************************************************************/


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/


VOS_UINT32  APP_VC_SetVoiceVolume(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    VOS_UINT8                           ucVoiceVolume
);


VOS_UINT32  APP_VC_SetVoiceMode(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    VOS_UINT8                           ucVoiceMode,
    VOS_UINT32                          ulTaskPid
);


VOS_UINT32 APP_VC_SetVoicePort(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    APP_VC_VOICE_PORT_ENUM_U8           ucVoicePort
);


VOS_UINT32 APP_VC_GetVoicePort(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
);


VOS_UINT32 APP_VC_GetVoiceMode(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
);


extern  VC_PHY_DEVICE_MODE_ENUM_U16  APP_VC_AppVcVoiceMode2VcPhyVoiceMode(
    APP_VC_VOICE_MODE_ENUM_U16          usVoiceMode
);


extern  APP_VC_VOICE_MODE_ENUM_U16  APP_VC_VcPhyVoiceMode2AppVcVoiceMode(
    VC_PHY_DEVICE_MODE_ENUM_U16         usVoiceMode
);

extern VOS_UINT32  APP_VC_GetVoiceVolume(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId
);

/*****************************************************************************
 �� �� ��  : APP_VC_SetMuteStatus
 ��������  : ���þ���״̬
 �������  : usClientId   - �ͻ���ID
             ucOpId       - ������ID
             enMuteStatus - ����״̬
 �������  : ��
 �� �� ֵ  : VOS_OK       - �ɹ�
             VOS_ERR      - ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32  APP_VC_SetMuteStatus(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    APP_VC_MUTE_STATUS_ENUM_UINT8       enMuteStatus
);


/*****************************************************************************
 �� �� ��  : APP_VC_GetMuteStatus
 ��������  : ��ȡ����״̬
 �������  : usClientId   - �ͻ���ID
             ucOpId       - ������ID
 �������  : ��
 �� �� ֵ  : VOS_OK       - �ɹ�
             VOS_ERR      - ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 APP_VC_GetMuteStatus(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

/* Added by L47619 for VOICE_LOOP, 2013/07/05, begin */
/*****************************************************************************
 �� �� ��  : APP_VC_SetModemLoop
 ��������  : ���ý�����˳���������
 �������  : usClientId   - �ͻ���ID
             ucOpId       - ������ID
             ucModemLoop  - ������˳���������״̬
 �������  : ��
 �� �� ֵ  : VOS_OK       - �ɹ�
             VOS_ERR      - ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 APP_VC_SetModemLoop(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucModemLoop
);
/* Added by L47619 for VOICE_LOOP, 2013/07/05, end */

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

#endif /* APP_VC_API_H */

