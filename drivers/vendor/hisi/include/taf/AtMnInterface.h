

#ifndef  AT_MN_INTERFACE_H
#define  AT_MN_INTERFACE_H

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "vos.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "v_msg.h"
#include "TafTypeDef.h"
#include "TafClientApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* Added by f62575 for AT Project��2011-10-03,  Begin*/

enum AT_MN_MSGTYPE_ENUM
{
    /* ��Ϣ���� */                                          /*��ϢID*/          /* ��ע */
    /* AT��CALLģ�����Ϣ */
    MN_APP_MSG_CLASS_CALL                                   = TAF_CALL_APP_MSG_BASE,
    /* ������� */
    MN_CALL_APP_ORIG_REQ                                    = 0x0001,           /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* �������� */
    MN_CALL_APP_END_REQ,                                                        /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* Ӧ������ */
    MN_CALL_APP_ANSWER_REQ,                                                     /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ��ʼ����DTMF */
    MN_CALL_APP_START_DTMF_REQ,                                                 /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ֹͣ����DTMF */
    MN_CALL_APP_STOP_DTMF_REQ,                                                  /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ���������ز���ҵ����� */
    MN_CALL_APP_SUPS_CMD_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ��ȡ������Ϣ */
    MN_CALL_APP_GET_INFO_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    /* ��ȡͨ��ʱ�� */
    MN_CALL_APP_GET_CDUR_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_SET_UUSINFO_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_QRY_UUSINFO_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_SET_ALS_REQ,                                                    /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_QRY_ALS_REQ,                                                    /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    MN_CALL_APP_MAX_REQ,

    MN_CALL_APP_CUSTOM_ECC_NUM_REQ,                                             /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    ID_TAFAGENT_MN_GET_CALL_INFO_REQ,                                           /* TAFAGENT_>MN  ��ȡͨ����Ϣ������Ϣ*/

    MN_CALL_APP_CLPR_GET_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    MN_CALL_APP_XLEMA_REQ,                                                      /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    MN_CALL_APP_SET_CSSN_REQ,                                                   /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    MN_CALL_APP_CALL_MODIFY_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    MN_CALL_APP_CALL_ANSWER_REMOTE_MODIFY_REQ,                                  /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */

    TAF_CALL_APP_ECONF_DIAL_REQ,                                                /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */
    TAF_CALL_APP_GET_ECONF_CALLED_INFO_REQ,                                     /* _H2ASN_MsgChoice MN_CALL_APP_REQ_MSG_STRU */


    /* AT��MSGģ�����Ϣ */
    MN_APP_MSG_CLASS_MSG                                    = TAF_MSG_APP_MSG_BASE,
    MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT                       = 0x1001,           /* _H2ASN_MsgChoice MN_MSG_SEND_PARM_STRU */
    MN_MSG_MSGTYPE_SEND_RPDATA_FROMMEM                      = 0x1002,           /* _H2ASN_MsgChoice MN_MSG_SEND_FROMMEM_PARM_STRU */
    MN_MSG_MSGTYPE_SEND_RPRPT                               = 0x1003,           /* _H2ASN_MsgChoice MN_MSG_SEND_ACK_PARM_STRU */
    MN_MSG_MSGTYPE_WRITE                                    = 0x1004,           /* _H2ASN_MsgChoice MN_MSG_WRITE_PARM_STRU */
    MN_MSG_MSGTYPE_READ                                     = 0x1005,           /* _H2ASN_MsgChoice MN_MSG_READ_PARM_STRU */
    MN_MSG_MSGTYPE_LIST                                     = 0x1006,           /* _H2ASN_MsgChoice MN_MSG_LIST_PARM_STRU */
    MN_MSG_MSGTYPE_DELETE                                   = 0x1007,           /* _H2ASN_MsgChoice MN_MSG_DELETE_PARAM_STRU */
    MN_MSG_MSGTYPE_DELETE_TEST                              = 0x1008,           /* _H2ASN_MsgChoice MN_MSG_MEM_STORE_ENUM_U8 */
    MN_MSG_MSGTYPE_WRITE_SRV_PARA                           = 0x1009,           /* _H2ASN_MsgChoice MN_MSG_WRITE_SRV_PARAM_STRU */
    MN_MSG_MSGTYPE_READ_SRV_PARA                            = 0x100a,           /* _H2ASN_MsgChoice MN_MSG_READ_COMM_PARAM_STRU */
    MN_MSG_MSGTYPE_DELETE_SRV_PARA                          = 0x100b,           /* _H2ASN_MsgChoice MN_MSG_DELETE_PARAM_STRU */
    MN_MSG_MSGTYPE_MODIFY_STATUS                            = 0x100c,           /* _H2ASN_MsgChoice MN_MSG_MODIFY_STATUS_PARM_STRU */
    MN_MSG_MSGTYPE_SET_RCVPATH                              = 0x100d,           /* _H2ASN_MsgChoice MN_MSG_SET_RCVMSG_PATH_PARM_STRU */
    MN_MSG_MSGTYPE_GET_RCVPATH                              = 0x100e,           /* _H2ASN_MsgChoice MN_MSG_GET_RCVMSG_PATH_PARM_STRU */
    MN_MSG_MSGTYPE_GET_STORAGESTATUS                        = 0x100f,           /* _H2ASN_MsgChoice MN_MSG_GET_STORAGE_STATUS_PARM_STRU */
    MN_MSG_MSGTYPE_READ_STARPT                              = 0x1010,           /* _H2ASN_MsgChoice MN_MSG_READ_COMM_PARAM_STRU */
    MN_MSG_MSGTYPE_DELETE_STARPT                            = 0x1011,           /* _H2ASN_MsgChoice MN_MSG_DELETE_PARAM_STRU */
    MN_MSG_MSGTYPE_GET_STARPT_FROMMOMSG                     = 0x1012,           /* _H2ASN_MsgChoice MN_MSG_SEND_PARM_STRU */
    MN_MSG_MSGTYPE_GET_MOMSG_FROMSTARPT                     = 0x1013,           /* _H2ASN_MsgChoice MN_MSG_SEND_PARM_STRU */
    MN_MSG_MSGTYPE_SET_MEMSTATUS                            = 0x1014,           /* _H2ASN_MsgChoice MN_MSG_SET_MEMSTATUS_PARM_STRU */
    MN_MSG_MSGTYPE_SET_RELAY_LINK_CTRL                      = 0x1015,           /* _H2ASN_MsgChoice MN_MSG_SET_LINK_CTRL_STRU */
    MN_MSG_MSGTYPE_GET_RELAY_LINK_CTRL                      = 0x1016,           /* _H2ASN_MsgChoice  */
    MN_MSG_MSGTYPE_STUB                                     = 0x1017,           /* _H2ASN_MsgChoice MN_MSG_STUB_MSG_STRU */
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    MN_MSG_MSGTYPE_GET_ALLCBMIDS                            = 0x1018,           /* _H2ASN_MsgChoice  */
    MN_MSG_MSGTYPE_ADD_CBMIDS                               = 0x1019,           /* _H2ASN_MsgChoice MN_MSG_CBMIR_LIST_STRU */
    MN_MSG_MSGTYPE_DELETE_CBMIDS                            = 0x101a,           /* _H2ASN_MsgChoice MN_MSG_CBMIR_LIST_STRU */
    MN_MSG_MSGTYPE_EMPTY_CBMIDS                             = 0x101b,           /* _H2ASN_MsgChoice  */
#endif

    MN_MSG_MSGTYPE_MAX,

    /* AT��SSAģ�����Ϣ */
    MN_APP_MSG_CLASS_SSA                                    = TAF_SSA_APP_MSG_BASE,
/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */
    /*����ҵ�������ʱ����Ϣ����*/
    TAF_MSG_REGISTERSS_MSG,
    TAF_MSG_ERASESS_MSG,
    TAF_MSG_ACTIVATESS_MSG,
    TAF_MSG_DEACTIVATESS_MSG,
    TAF_MSG_INTERROGATESS_MSG,
    TAF_MSG_REGPWD_MSG,
    TAF_MSG_PROCESS_USS_MSG,
    TAF_MSG_ERASECCENTRY_MSG,
    TAF_MSG_RLEASE_MSG,
    TAF_MSG_SET_USSDMODE_MSG,
/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */

    /* AT��MMAģ�����Ϣ */
    MN_APP_MSG_CLASS_MMA                                    = TAF_MMA_APP_MSG_BASE,

    /* AT��MNģ������ò��������Ϣ��δ�Ż����֣����Ż���ɾ�� */
    MN_APP_MSG_CLASS_SET                                    = TAF_APP_SET_MSG_BASE,

    /* AT��MNģ����ѯ���������Ϣ��δ�Ż����֣����Ż���ɾ�� */
    MN_APP_MSG_CLASS_QRY                                    = TAF_APP_QRY_MSG_BASE,

    /* AT��PS����ģ�����Ϣ */
    MN_APP_MSG_CLASS_PS                                     = TAF_APS_MSG_BASE,

    /* �ⲿ����Ϣ�Ķ���Ǩ�Ƶ�TafAppAps.h�ļ��� */


    MN_APP_MSG_CLASS_MASK                                   = TAF_IMSA_MSG_MASK
};
typedef VOS_UINT16 AT_MN_MSGTYPE_ENUM_UINT16;

typedef AT_MN_MSGTYPE_ENUM_UINT16 MN_MSG_MSGTYPE_ENUM_U16;

typedef VOS_UINT32  MN_CALL_APP_REQ_ENUM_UINT32;
/* Added by f62575 for AT Project��2011-10-03,  End*/

/*****************************************************************************
 ö����    : AT_CC_MSGTYPE_ENUM
 ö��˵��  : AT��CCģ����ԭ��
*****************************************************************************/
enum AT_CC_MSGTYPE_ENUM
{
    /* ��Ϣ���� */                                          /*��ϢID*/          /* ��ע */
    /* AT����CC����Ϣ */
    AT_CC_MSG_STATE_QRY_REQ                                 = 0x0000,

    /* CC����AT����Ϣ */
    AT_CC_MSG_STATE_QRY_CNF                                 = 0x0001,

    AT_CC_MSG_BUTT

 };
typedef VOS_UINT16 AT_CC_MSGTYPE_ENUM_UINT16;

/*****************************************************************************
  4 �궨��
*****************************************************************************/

/*****************************************************************************
  5 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : AT_APPCTRL_STRU
 �ṹ˵��  : AT APP ���ƽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           aucReserved[1];
} AT_APPCTRL_STRU;

/* Added by f62575 for AT Project��2011-10-03,  Begin*/
/* MN����AT���¼��ṹ */
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;
    VOS_UINT8                           aucReserved1[2];
    MN_CLIENT_ID_T                      clientId;
    VOS_UINT16                          usLen;
    VOS_UINT8                           aucContent[4];
}MN_AT_IND_EVT_STRU;

/*****************************************************************************
 �ṹ����  : TAF_MNTN_LOG_PRINT_STRU
 �ṹ˵��  : ��ά�ɲ�LOG��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_CHAR                            acLog[4];           /* ��ӡ�ַ��� */
} TAF_MNTN_LOG_PRINT_STRU;


/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    AT_MN_MSGTYPE_ENUM_UINT16           enMsgID;                                /*_H2ASN_MsgChoice_Export AT_MN_MSGTYPE_ENUM_U32*/
                                                                                /* Ϊ�˼���NAS����Ϣͷ���壬����ת��ASN.1ʹ��AT_MN_MSGTYPE_ENUM_U32 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_MN_MSGTYPE_ENUM_U32
    ****************************************************************************/
}AT_MN_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    AT_MN_MSG_DATA                      stMsgData;
}AtMnInterface_MSG;
/* Added by f62575 for AT Project��2011-10-03,  End*/

/*****************************************************************************
 ö����    : MN_APP_REQ_MSG_STRU
 �ṹ˵��  : ����APP��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                          usMsgName;                              /* ��Ϣ�� */
    VOS_UINT8                           aucReserve1[2];                             /* ���� */
    MN_CLIENT_ID_T                      clientId;                               /* Client ID */
    MN_OPERATION_ID_T                   opId;                                   /* Operation ID */
    VOS_UINT8                           aucReserve2[1];                         /* ���� */
    VOS_UINT8                           aucContent[4];                          /* ��Ϣ���� */
} MN_APP_REQ_MSG_STRU;





/*****************************************************************************
  6 ��������
*****************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


#endif /* end of AtMnInterface.h */
