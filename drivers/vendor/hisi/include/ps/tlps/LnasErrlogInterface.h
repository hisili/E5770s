/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LnasErrLogInterface.h
  Description     : LnasErrLogInterface.h header file
  History         :
     1.HANLUFENG 41410       2013-8-27     Draft Enact
     2.
******************************************************************************/

#ifndef __LNASERRLOGINTERFACE_H__
#define __LNASERRLOGINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "omerrorlog.h"
#include    "LnasFtmInterface.h"

#pragma  pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
#define LNAS_OM_ERRLOG_ID_ESM_REJ_CN_CAUSE     (400)
#define LNAS_OM_ERRLOG_ID_EMM_FAIL_CAUSE       (600)
#define LNAS_OM_ERRLOG_ID_EMM_REJ_CN_CAUSE     (800)
#define LNAS_OM_ERRLOG_MAX_NUM                 (4)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum LNAS_OM_ERRLOG_ID_ENUM
{
    /*ESMģ��ʧ�ܾܾ�*/
    LNAS_ESM_CAUSE_OPERATOR_DETERMINE_BARRING = LNAS_OM_ERRLOG_ID_ESM_REJ_CN_CAUSE, /* ����ܾ�����ʾ��������ֹ */
    LNAS_ESM_CAUSE_INSUFFICIENT_RESOURCES,             /* ����ܾ�,��ʾ��Դ����        */
    LNAS_ESM_CAUSE_UNKNOWN_OR_MISSING_APN,             /* ����ܾ�,��ʾAPN�޷�ʶ��     */
    LNAS_ESM_CAUSE_UNKNOWN_PDN_TYPE,                   /* ����ܾ�����ʾPDN�����޷�ʶ��*/
    LNAS_ESM_CAUSE_USER_AUTH_FAIL,                     /* ����ܾ�����ʾ�û���Ȩʧ��   */
    LNAS_ESM_CAUSE_REQ_REJ_BY_SGW_OR_PGW,              /* ����ܾ�����ʾSGW����PGW�ܾ��û����� */
    LNAS_ESM_CAUSE_REQ_REJ_UNSPECITY,                  /* ����ܾ���ԭ���� */
    LNAS_ESM_CAUSE_SERVICE_OPTION_NOT_SUPPORT,         /* ����ܾ�����ʾ����ѡ�֧�� */
    LNAS_ESM_CAUSE_REQ_SERVICE_NOT_SUBSCRIBED,         /* ����ܾ�����ʾ����ѡ��û��ǩԼ */
    LNAS_ESM_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER,      /* ����ܾ�����ʾ����ѡ����ʱ�Բ�֧��*/
    LNAS_ESM_CAUSE_PTI_ALREADY_IN_USED,                /* ����ܾ�����ʾPTI��ʹ��*/
    LNAS_ESM_CAUSE_REGULAR_DEACTIVATION,               /* ����ܾ�����ʾ����ȥ����*/
    LNAS_ESM_CAUSE_EPS_QOS_NOT_ACCEPT,                 /* ����ܾ�����ʾQosδ������*/
    LNAS_ESM_CAUSE_NETWORK_FAILURE,                    /* ����ܾ�����ʾ�������*/
    LNAS_ESM_CAUSE_REACTIVATION_REQUESTED,             /* ����ܾ�����ʾ��Ҫ���¼���*/
    LNAS_ESM_CAUSE_SEMANTIC_ERR_IN_TFT,                /* ����ܾ�����ʾTFT�������*/
    LNAS_ESM_CAUSE_SYNTACTIC_ERR_IN_TFT,               /* ����ܾ�����ʾTFT�﷨����*/
    LNAS_ESM_CAUSE_INVALID_EPS_BEARER_IDENTITY,        /* ����ܾ�����ʾ�Ƿ��ĳ��ر�ʶ*/
    LNAS_ESM_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER,      /* ����ܾ�����ʾPacketFilter�������*/
    LNAS_ESM_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER,    /* ����ܾ�����ʾPacketFilter�﷨����*/
    LNAS_ESM_CAUSE_BEARER_WITHOUT_TFT_ACT,             /* ����ܾ�����ʾ�����������û��TFT�ĳ���*/
    LNAS_ESM_CAUSE_PTI_MISMATCH,                       /* ����ܾ�����ʾPTI��ƥ��*/
    LNAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED,       /* ����ܾ�����ʾ����PDN�������ͷ�*/
    LNAS_ESM_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED,          /* ����ܾ�����ʾPDN����ֻ����IpV4*/
    LNAS_ESM_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED,          /* ����ܾ�����ʾPDN����ֻ����IpV6*/
    LNAS_ESM_CAUSE_SINGLE_ADDR_BEARER_ONLY_ALLOWED,    /* ����ܾ�����ʾPDNֻ������IP��ַ*/
    LNAS_ESM_CAUSE_ESM_INFORMATION_NOT_RECEIVED,       /* ����ܾ�����ʾESM Info��Ϣû���յ�*/
    LNAS_ESM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST,      /* ����ܾ�����ʾPDN���Ӳ�����*/
    LNAS_ESM_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED, /* ����ܾ�����ʾ��PDN�������Ӧͬһ��APN*/
    LNAS_ESM_CAUSE_COLLISION_WITH_NETWORK_INITIATED_REQUEST,  /* ����ܾ�����ʾ�����紥���������ͻ*/
    LNAS_ESM_CAUSE_UNSUPPORTED_QCI_VALUE,              /* ����ܾ�����ʾQCI��ֵ�޷�֧��*/
    LNAS_ESM_CAUSE_INVALID_PTI_VALUE,                  /* ����ܾ�����ʾPTI��ֵ������*/
    LNAS_ESM_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE,     /* ����ܾ�����ʾ��Ϣ���岻��ȷ*/
    LNAS_ESM_CAUSE_INVALID_MANDATORY_INFORMATION,      /* ����ܾ�����ʾ��ѡ��Ԫ����ȷ*/
    LNAS_ESM_CAUSE_MESSAGE_TYPE_NON_EXIST_OR_NOT_IMPLEMENTED, /* ����ܾ�����ʾ��Ϣ���Ͳ����ڻ򲻿���*/
    LNAS_ESM_CAUSE_MESSAGE_TYPE_NOT_COMPATIBLE_WITH_PROT_STA, /* ����ܾ�����ʾ��Ϣ������Э�鲻һ��*/
    LNAS_ESM_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENTED, /* ����ܾ�����ʾ��Ԫ�����ڻ򲻿���*/
    LNAS_ESM_CAUSE_CONDITIONAL_IE_ERROR,               /* ����ܾ�����ʾ������Ԫ����*/
    LNAS_ESM_CAUSE_MESSAGE_NOT_COMPATIBLE_WITH_PROT_STA, /* ����ܾ�����ʾ��Ϣ��Э��涨��һ��*/
    LNAS_ESM_CAUSE_PROTOCOL_ERROR,                     /* ����ܾ�����ʾ��ָ����Э�����*/
    LNAS_ESM_CAUSE_APN_RESTRICTION_VAL_INCOMPATIBLE_WITH_ACT_BEARER, /* ����ܾ�����ʾapnԼ�������뼤����������Ĳ���*/

    /*EMMģ��ʧ��ԭ��*/
    LNAS_OM_ERRLOG_ID_ATTACH_FAIL_NO_IMSI    = LNAS_OM_ERRLOG_ID_EMM_FAIL_CAUSE, /* USIM��������*/
    LNAS_OM_ERRLOG_ID_ATTACH_FAIL_ACCESS_BAR,

    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_ILLEGAL_UE = LNAS_OM_ERRLOG_ID_EMM_REJ_CN_CAUSE, /* ����ܾ�,��ʾ�Ƿ�UE*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_ILLEGAL_ME,                                      /* ����ܾ�,��ʾ�Ƿ�ME*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_EPS_SERV_NOT_ALLOW,                              /* ����ܾ�,��ʾEPSҵ������*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,             /* ����ܾ�,��ʾEPS�ͷ�EPSҵ������*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_PLMN_NOT_ALLOW,                                  /* ����ܾ�,��ʾPLMN������*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_TA_NOT_ALLOW,                                    /* ����ܾ�,��ʾ��ǰTA������*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_ROAM_NOT_ALLOW,                                  /* ����ܾ�,��ʾ��ǰTA�в�������*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,                      /* ����ܾ�����ʾ��ǰPLMN��EPSҵ������*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_NO_SUITABL_CELL,                                 /* ����ܾ�����ʾ��ǰTA��û�п��õ�С��*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_ESM_FAILURE,                                     /* ����ܾ�����ʾESM����*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,                     /* ����ܾ�����ʾ��ǰ�û�û��CSG��Ȩ*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_SEMANTICALLY_INCORRECT_MSG,                      /* ����ܾ�����ʾ��Ϣ�﷨����ȷ*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_INVALID_MANDATORY_INFORMATION,                   /* ����ܾ�����ʾ��ѡ��Ԫ�Ƿ�*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_MSG_TYPE_NON_EXIST_OR_IMPLEMENT,                 /* ����ܾ�����ʾ�����ڻ�֧�ֵ���Ϣ*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENT,         /* ����ܾ�����ʾ��Ϣ��Ԫ�����ڻ�֧��*/
    LNAS_OM_ERRLOG_ID_LMM_CN_CAUSE_PROTOCOL_ERROR,                                  /* ����ܾ�����ʾЭ�����*/
    LNAS_OM_ERRLOG_ID_CN_CAUSE_OTHERS                                               /* ����������ԭ��ܾ�*/
};
typedef VOS_UINT16  LNAS_OM_ERRLOG_ID_ENUM_UINT16;


enum    LMM_OM_ERR_ID_ENUM
{
    LNAS_OM_ERR_ID_LMM_APP_SUCC             = 1,
    LNAS_OM_ERR_ID_LMM_NULL_PTR             ,
    LNAS_OM_ERR_ID_LMM_TIMER_EXPIRE,
    LNAS_OM_ERR_ID_LMM_INPUT_PARA_ERR,  /* �����Ϣ��ڲ������� *//* �����϶࣬��Ҫ����NV�����ã�APP��ڣ� */
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_ATTACH_TYPE_NOT_COMPATIBLE_WITH_UE_TYPE,  /* ATTACH REQ��������UE���õ����Ͳ����ݣ��޷�����ATTACH *//* ATTACH REQ����ӦΪPS���� */
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_PLMN_SEARCHING,   /* ATTACH ʧ�ܣ���ǰû��С��פ����������С�� */ /* ��UE�ƶ����źŽϺõĵط� */
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_T3411_IS_RUNNING, /* ATTEMPINT TO ATTACH״̬�£�TIMER 3411�������У���3411��ʱ�󣬻��Զ�����ATTACH��������APP
                                                    ��ATTACH REQ����ATTACH���̣� */  /*UE�Ժ��Զ�����ATTACH�������ֶ�����*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_NO_SUITABLE_CELL, /* ��ǰС���޷��ṩ�������� */ /* ��UE�ƶ�������С�������������� */
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_NO_IMSI,/* ��IMSI */ /* ����Ƿ��п������Ƿ��������������²�ο�����������UE */
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_NO_CELL, /* ��С�� */ /* ��UE�ƶ����źŽϺõĵط� */
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_ATTEMPTING_TO_UPDATE, /*������ͼ����״̬*/ /*�Ժ�����*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_LIMITED_SERVICE,/*���Ʒ���״̬ */ /*�Ժ�����*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_ACCESS_BAR,/*���뱻BAR*/ /*�Ժ�����*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_WAIT_CN_DETACH_CNF,/*��ǰ״̬WAIT_CN_DETACH_CNF,����ATTACH*//*�Ժ�����*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_WAIT_CN_TAU_CNF,/*��ǰ״̬WAIT_CN_TAU_CNF,����ATTACH*//*�Ժ�����*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_WAIT_CN_SER_CNF,/*��ǰ״̬WAIT_CN_TAU_CNF,����ATTACH*//*�Ժ�����*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_AUTH_FAIL,/*��Ȩʧ��*/ /*���USIM���Ƿ���Ч�������¿���*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_ESM_FAILURE,/*ESM�д�*/ /*���USIM���Ƿ���Ч�������¿���*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_MT_DETACH_FAILURE,/*�յ����緢���DETACH*/ /*���¿���*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_MO_DETACH_FAILURE,/*ATTACH�����У�UE�����DETACH*/ /*���¿���*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_T3402_IS_RUNNING,/*TIMER 3402�������У�*/ /*�Ժ�����*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_FORBID_PLMN,/*FORBID_PLMN*/ /*���USIM���Ƿ���Ч�����ƶ�λ�ú����³���*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_FORBID_PLMN_FOR_GPRS,/*FORBID_PLMN_FOR_GPRS*/ /*���USIM���Ƿ�ͨGPRSҵ�񣬻��ƶ�λ�ú����³���*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_FORBID_TA_FOR_ROAMING,/*FORBID_TA_FOR_ROAMING*/ /*���USIM���Ƿ�ͨ��ǰTA��������ҵ��*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_FORBID_TA_FOR_RPOS,/*FORBID_TA_FOR_REGINAL PROVISION OF SERVICE*/ /*���USIM���Ƿ���Ч�����¿���*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_PS_ATT_NOT_ALLOW,/*PS_ATT_NOT_ALLOW*/ /*���USIM���Ƿ���Ч�����¿���*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL_LOCAL_ESM_FAILURE,/*LOCAL_ESM_FAILURE*/ /*���¿���*/
    LNAS_OM_ERR_ID_LMM_ATTACH_FAIL,/**/ /**/
    LNAS_OM_ERR_ID_LMM_DETACH_IMSI_PAGING,/* IMSI_PAGING */ /*���¿���*/
    LNAS_OM_ERR_ID_LMM_DETACH_NONE_SPECIR,/* δ֪ԭ���DETACH */ /*���¿���*/
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_IMSI_UNKNOWN_IN_HSS                        = 0x100 + NAS_OM_LMM_CAUSE_IMSI_UNKNOWN_IN_HSS,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_ILLEGAL_UE                                 = 0x100 + NAS_OM_LMM_CAUSE_ILLEGAL_UE,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_IMSI_UNKNOWN_IN_VLR                        = 0x100 + NAS_OM_LMM_CAUSE_IMSI_UNKNOWN_IN_VLR,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_IMEI_NOT_ACCEPTED                          = 0x100 + NAS_OM_LMM_CAUSE_IMEI_NOT_ACCEPTED,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_ILLEGAL_ME                                 = 0x100 + NAS_OM_LMM_CAUSE_ILLEGAL_ME,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_EPS_SERV_NOT_ALLOW                         = 0x100 + NAS_OM_LMM_CAUSE_EPS_SERV_NOT_ALLOW,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW        = 0x100 + NAS_OM_LMM_CAUSE_EPS_SERV_AND_NON_EPS_SERV_NOT_ALLOW,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW              = 0x100 + NAS_OM_LMM_CAUSE_MS_ID_CANNOT_BE_DERIVED_BY_NW,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_EPS_IMPLICITLY_DETACHED                    = 0x100 + NAS_OM_LMM_CAUSE_EPS_IMPLICITLY_DETACHED,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_PLMN_NOT_ALLOW                             = 0x100 + NAS_OM_LMM_CAUSE_PLMN_NOT_ALLOW,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_TA_NOT_ALLOW                               = 0x100 + NAS_OM_LMM_CAUSE_TA_NOT_ALLOW,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_ROAM_NOT_ALLOW                             = 0x100 + NAS_OM_LMM_CAUSE_ROAM_NOT_ALLOW,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN                 = 0x100 + NAS_OM_LMM_CAUSE_EPS_SERV_NOT_ALLOW_IN_PLMN,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_NO_SUITABL_CELL                            = 0x100 + NAS_OM_LMM_CAUSE_NO_SUITABL_CELL,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE              = 0x100 + NAS_OM_LMM_CAUSE_MSC_TEMPORARILY_NOT_REACHABLE,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_NETWORKFAILURE                             = 0x100 + NAS_OM_LMM_CAUSE_NETWORKFAILURE,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_CS_DOMAIN_NOT_AVAILABLE                    = 0x100 + NAS_OM_LMM_CAUSE_CS_DOMAIN_NOT_AVAILABLE,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_ESM_FAILURE                                = 0x100 + NAS_OM_LMM_CAUSE_ESM_FAILURE,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_CONGESTION                                 = 0x100 + NAS_OM_LMM_CAUSE_CONGESTION,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG                = 0x100 + NAS_OM_LMM_CAUSE_NOT_AUTHORIZED_FOR_THIS_CSG,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN= 0x100 + NAS_OM_LMM_CAUSE_REQUESTED_SER_OPTION_NOT_AUTHORIZED_IN_PLMN,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE               = 0x100 + NAS_OM_LMM_CAUSE_CS_DOMAIN_TEMP_NOT_AVAILABLE,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED            = 0x100 + NAS_OM_LMM_CAUSE_NO_EPS_BEARER_CONTEXT_ACTIVATED,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_SEMANTICALLY_INCORRECT_MSG                 = 0x100 + NAS_OM_LMM_CAUSE_SEMANTICALLY_INCORRECT_MSG,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_INVALID_MANDATORY_INFORMATION              = 0x100 + NAS_OM_LMM_CAUSE_INVALID_MANDATORY_INFORMATION,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_MSG_TYPE_NON_EXIST_OR_IMPLEMENT            = 0x100 + NAS_OM_LMM_CAUSE_MSG_TYPE_NON_EXIST_OR_IMPLEMENT,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENT    = 0x100 + NAS_OM_LMM_CAUSE_INFO_ELEMENT_NON_EXIST_OR_NOT_IMPLEMENT,
    LNAS_OM_ERR_ID_LMM_CN_CAUSE_MSG_NOT_COMPATIBLE_WITH_PROTOCOL_STATE     = 0x100 + NAS_OM_LMM_CAUSE_MSG_NOT_COMPATIBLE_WITH_PROTOCOL_STATE,

    LNAS_OM_ERR_ID_LMM_NONE_SPECIRY,
    LNAS_OM_ERR_ID_BUTT

};
typedef VOS_UINT32  LNAS_OM_ERR_ID_ENUM_UINT32;
typedef VOS_UINT32  LMM_OM_ERR_ID_ENUM_UINT32;
typedef VOS_UINT32  ESM_OM_ERR_ID_ENUM_UINT32;


/*****************************************************************************
 ö����    : LMM_ERR_LOG_ATTACH_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ATTACH������
*****************************************************************************/
enum    LMM_ERRLOG_INFO_TYPE_ENUM
{
    LMM_ERR_LOG_NONE_SPECIFY       = 0,    /* δ֪���̣���Ӧ�ľ�����ϢҲ��Ч */
    LMM_ERR_LOG_ATTACH_IND         = 1,    /* ATTACH����*/
    LMM_ERR_LOG_TAU_RESULT_IND,            /* TAU���� */
    LMM_ERR_LOG_SERVICE_RESULT_IND,        /* SERVICE���� */
    LMM_ERR_LOG_DETACH_IND,                /* DETACH���� */
    LMM_ERR_LOG_INFO_TYPE_BUTT
};
typedef VOS_UINT32  LMM_ERRLOG_INFO_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_ERR_LOG_ATTACH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : UE������ATTACH TYPE
*****************************************************************************/
enum LMM_ERR_LOG_ATTACH_TYPE_ENUM
{
    LMM_ERR_LOG_ATT_TYPE_EPS_ONLY                = 1, /* EPSע�� */
    LMM_ERR_LOG_ATT_TYPE_COMBINED_EPS_IMSI       = 2, /* ����ע�� */
    LMM_ERR_LOG_ATT_TYPE_EPS_EMERGENCY           = 6, /* ����ע�� */
    LMM_ERR_LOG_ATT_TYPE_BUTT
};
typedef VOS_UINT32 LMM_ERR_LOG_ATTACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_ERR_LOG_TAU_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : UE������TAU����
*****************************************************************************/
enum LMM_ERR_LOG_TAU_TYPE_ENUM
{
    LMM_ERR_LOG_TA_UPDATING                     = 0,
    LMM_ERR_LOG_COMBINED_TA_LA_UPDATING         = 1,
    LMM_ERR_LOG_COMBINED_TA_LA_WITH_IMSI        = 2,
    LMM_ERR_LOG_PS_PERIODIC_UPDATING            = 3,
    LMM_ERR_LOG_CS_PS_PERIODIC_UPDATING         = 4,
    LMM_ERR_LOG_TAU_TYPE_BUTT
};
typedef VOS_UINT32 LMM_ERR_LOG_TAU_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_ERR_LOG_TAU_CN_RSLT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ������Ӧ��TAU�������
*****************************************************************************/
enum LMM_ERR_LOG_TAU_CN_RSLT_ENUM
{
    LMM_ERR_LOG_TA_UPDATED                              = 0,
    LMM_ERR_LOG_COMBINED_TA_LA_UPDATED                  = 1,
    LMM_ERR_LOG_TA_UPDATED_ISR_ACTIVATED                = 4,
    LMM_ERR_LOG_COMBINED_TA_LA_UPDATED_ISR_ACTIVATED    = 5,
    LMM_ERR_LOG_TAU_CN_RSLT_BUTT
};
typedef VOS_UINT32 LMM_ERR_LOG_TAU_CN_RSLT_ENUM_UINT32;

/*****************************************************************************
 ö����    : LMM_ERR_LOG_MT_DETACH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ���ഥ����DETACH����
*****************************************************************************/
enum LMM_ERR_LOG_MT_DETACH_TYPE_ENUM
{
    LMM_ERR_LOG_MT_DET_REATTACH_REQUIRED            = 1,
    LMM_ERR_LOG_MT_DET_REATTACH_NOT_REQUIRED        = 2,
    LMM_ERR_LOG_MT_DET_IMSI                         = 3,
    LMM_ERR_LOG_MT_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 LMM_ERR_LOG_MT_DETACH_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����    : LMM_ERR_LOG_SERVICE_TYPE_ENUM
 Э����  : 24301Э��9.9.3.27
 ASN.1���� :
 ö��˵��  : UE������SERVICE���ͣ���ʱ����
*****************************************************************************/
enum LMM_ERR_LOG_SERVICE_TYPE_ENUM
{
    LMM_ERR_LOG_SERVICE_MO_CSFB_1XCSFB              = 0,
    LMM_ERR_LOG_SERVICR_MT_CSFB_1XCSFB,
    LMM_ERR_LOG_SERVICR_MO_CSFB_1XCSFB_EMERGENCY,
    LMM_ERR_LOG_SERVICE_TYPE_BUTT
};
typedef VOS_UINT32 LMM_ERR_LOG_SERVICE_TYPE_ENUM_UINT32;


/*****************************************************************************
 ö����    : LMM_ERR_LOG_MO_DETACH_TYPE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : UE������DETACH TYPE
*****************************************************************************/
enum LMM_ERR_LOG_MO_DETACH_TYPE_ENUM
{
    LMM_ERR_LOG_MO_DET_PS_ONLY                        = 1, /* ��PS */
    LMM_ERR_LOG_MO_DET_CS_ONLY                        = 2, /* ��CS */
    LMM_ERR_LOG_MO_DET_CS_PS                          = 3, /* CS+PS */
    LMM_ERR_LOG_MO_DETACH_TYPE_BUTT
};
typedef VOS_UINT32 LMM_ERR_LOG_MO_DETACH_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_LMM_ERR_LOG_MAIN_STATE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : MM�����в���״̬������״̬��ö�ٶ���
*****************************************************************************/
enum    NAS_LMM_ERR_LOG_MAIN_STATE_ENUM
{
    /*=================== LMM����״̬ ===================*/
    LMM_OM_MS_NULL                 = 0x0000,
    LMM_OM_MS_DEREG                        ,
    LMM_OM_MS_REG_INIT                     ,           /*ATTACH������״̬*/
    LMM_OM_MS_REG                          ,
    LMM_OM_MS_TAU_INIT                     ,           /*TAU������״̬*/
    LMM_OM_MS_SER_INIT                     ,           /*SERVICE������״̬*/
    LMM_OM_MS_DEREG_INIT                   ,           /*DETACH������״̬*/

    LMM_OM_MS_RRC_CONN_EST_INIT            ,           /*����RRC���ӵĹ���*/
    LMM_OM_MS_RRC_CONN_REL_INIT            ,           /*�ͷ�RRC���ӵĹ���*/
    LMM_OM_MS_AUTH_INIT                    ,           /*AUTH����*/

    LMM_OM_MS_SUSPEND                      ,           /*�������*/
    LMM_OM_MS_RESUME                       ,           /*��ҹ���*/

    /*=================== Ԥ������״̬,�ݲ�ʹ�� ===================*/
    LMM_OM_MS_RESERVE1                     ,           /* RESERVE */
    LMM_OM_MS_RESERVE2                     ,           /* RESERVE */
    LMM_OM_MS_RESERVE3                     ,           /* RESERVE */
    LMM_OM_MS_RESERVE4                     ,           /* RESERVE */
    LMM_OM_MS_RESERVE5                     ,           /* RESERVE */
    LMM_OM_MS_RESERVE6                     ,           /* RESERVE */
    LMM_OM_MS_RESERVE7                     ,           /* RESERVE */

    /*=================== SECU ��CUR ״̬ ===================*/
    LMM_OM_CUR_SECU_NOT_EXIST,   /*17*/
    LMM_OM_CUR_SECU_EXIST_NOT_ACTIVE, /*18*/
    LMM_OM_CUR_SECU_EXIST_ACTIVE, /*19*/

    NAS_LMM_ERR_LOG_MAIN_STATE_BUTT
};
typedef VOS_UINT16 NAS_LMM_ERR_LOG_MAIN_STATE_ENUM_UINT16;

/*****************************************************************************
 ö����    : NAS_LMM_ERR_LOG_MAIN_STATE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : MM�����в���״̬������״̬��ö�ٶ���
*****************************************************************************/
enum    NAS_LMM_ERR_LOG_SUB_STATE_ENUM
{

    /*=================== LMM����״̬ ===================*/

    /*========== NULL�µ���״̬ ===============*/
    LMM_OM_SS_NULL_WAIT_APP_START_REQ      = 0x0000,
    LMM_OM_SS_NULL_WAIT_READING_USIM               ,
    LMM_OM_SS_NULL_WAIT_MMC_START_CNF              ,
    LMM_OM_SS_NULL_WAIT_RRC_START_CNF              ,
    LMM_OM_SS_NULL_WAIT_SWITCH_OFF                 ,
    LMM_OM_SS_NULL_WAIT_MMC_STOP_CNF               ,
    LMM_OM_SS_NULL_WAIT_RRC_STOP_CNF               ,


    /*========== DEREG�µ���״̬ ==============*/
    LMM_OM_SS_DEREG_NORMAL_SERVICE                 ,
    LMM_OM_SS_DEREG_LIMITED_SERVICE                ,
    LMM_OM_SS_DEREG_ATTEMPTING_TO_ATTACH           ,
    LMM_OM_SS_DEREG_PLMN_SEARCH                    ,
    LMM_OM_SS_DEREG_NO_IMSI                        ,
    LMM_OM_SS_DEREG_ATTACH_NEEDED                  ,
    LMM_OM_SS_DEREG_NO_CELL_AVAILABLE              ,

    /*========== ATTACH_INIT����״̬ ==========*/
    LMM_OM_SS_ATTACH_WAIT_ESM_PDN_RSP              ,
    LMM_OM_SS_ATTACH_WAIT_CN_ATTACH_CNF            ,
    LMM_OM_SS_ATTACH_WAIT_MRRC_REL_CNF             ,
    LMM_OM_SS_ATTACH_WAIT_ESM_BEARER_CNF           ,
    LMM_OM_SS_ATTACH_WAIT_RRC_DATA_CNF             ,


    /*========== REG�µ���״̬ ================*/
    LMM_OM_SS_REG_NORMAL_SERVICE                   ,
    LMM_OM_SS_REG_ATTEMPTING_TO_UPDATE             ,
    LMM_OM_SS_REG_LIMITED_SERVICE                  ,
    LMM_OM_SS_REG_PLMN_SEARCH                      ,
    LMM_OM_SS_REG_WAIT_ACCESS_GRANT_IND            ,
    LMM_OM_SS_REG_NO_CELL_AVAILABLE                ,
    LMM_OM_SS_REG_ATTEMPTING_TO_UPDATE_MM          ,
    LMM_OM_SS_REG_IMSI_DETACH_WATI_CN_DETACH_CNF   ,


    /*========== TAU_INIT����״̬  ============*/
    LMM_OM_SS_TAU_WAIT_CN_TAU_CNF                  ,

    /*========== SER_INIT����״̬ =============*/
    LMM_OM_SS_SER_WAIT_CN_SER_CNF                  ,

    /*========== DETACH_INIT����״̬ ==========*/
    LMM_OM_SS_DETACH_WAIT_CN_DETACH_CNF            ,
    LMM_OM_SS_DETACH_WAIT_MRRC_REL_CNF             ,


    /*========== LMM_OM_MS_RRC_CONN_INIT����״̬ =*/
    LMM_OM_SS_RRC_CONN_WAIT_EST_CNF                ,
    LMM_OM_SS_RRC_CONN_WAIT_REL_CNF                ,


    /*========== AUTH�����е���״̬ ===========*/
    LMM_OM_SS_AUTH_WAIT_CN_AUTH,

    /*========== SUSPEND�����е���״̬ ========*/
    LMM_OM_SS_SUSPEND_RRCORI_WAIT_MMC_SUSPEND,
    LMM_OM_SS_SUSPEND_RRCORI_WAIT_OTHER_SUSPEND,
    LMM_OM_SS_SUSPEND_WAIT_END,
    LMM_OM_SS_SUSPEND_MMCORI_WAIT_OTHER_SUSPEND,
    LMM_OM_SS_SUSPEND_SYSCFGORI_WAIT_OTHER_SUSPEND,

    /*========== RESUME�����е���״̬ ========*/
    LMM_OM_SS_RESUME_RRCRSM_WAIT_OTHER_RESUME,
    LMM_OM_SS_RESUME_RRCORI_WAIT_SYS_INFO_IND,
    LMM_OM_SS_RESUME_MMCORI_WAIT_SYS_INFO_IND,

    /*========== GUTI     ����������״̬  =====*/
    /*========== IDEN     ����������״̬  =====*/
    /*========== SECURITY ����������״̬  =====*/

    /*=================== SECU��NEW״̬ ===================*/
    LMM_OM_NEW_SECU_NOT_EXIST,/*56*/
    LMM_OM_NEW_SECU_EXIST,

    LMM_OM_SS_BUTT
};
typedef VOS_UINT16  NAS_LMM_ERR_LOG_SUB_STATE_ENUM_UINT16;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*�������: IE ��Ч��ʱ��IE��������Ϊ 0 */

/*****************************************************************************
 �ṹ����   :LMM_ERR_LOG_ATTACH_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   :ATTACH������ݽṹ
*****************************************************************************/
typedef struct
{
    LMM_ERR_LOG_ATTACH_TYPE_ENUM_UINT32    ulReqType;    /* ATTACH����ʱ������ */
}LMM_ERR_LOG_ATTACH_IND_STRU;

/*****************************************************************************
 �ṹ����   :LMM_ERR_LOG_TAU_RESULT_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   :TAU�ṹ���ݽṹ
*****************************************************************************/
typedef struct
{
    LMM_ERR_LOG_TAU_CN_RSLT_ENUM_UINT32    ulCnRst;      /* ������Ӧ��TAU����*/
    LMM_ERR_LOG_TAU_TYPE_ENUM_UINT32       ulReqType;    /* TAU����ҵ��ʱ������*/
} LMM_ERR_LOG_TAU_RESULT_IND_STRU;


/*****************************************************************************
 �ṹ����   :LMM_ERR_LOG_SERVICE_RESULT_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   :SERVICE������ݽṹ
*****************************************************************************/
typedef struct
{
    LMM_ERR_LOG_SERVICE_TYPE_ENUM_UINT32    ulReqType;   /* SERVICE������� */
    VOS_UINT32                              ulRsv;       /* ���� */
} LMM_ERR_LOG_SERVICE_RESULT_IND_STRU;

/*****************************************************************************
 �ṹ����   :LMM_ERR_LOG_STATE_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   :EMM״̬��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    NAS_LMM_ERR_LOG_MAIN_STATE_ENUM_UINT16      usLmmMainState; /* EMM��״̬*/
    NAS_LMM_ERR_LOG_SUB_STATE_ENUM_UINT16       usLmmSubState;  /* EMM��״̬*/
}LMM_ERR_LOG_STATE_STRU;

/*****************************************************************************
 �ṹ����   :LMM_ERR_LOG_DETACH_IND_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   :DETACH������ݽṹ
*****************************************************************************/
typedef struct
{

    LMM_ERR_LOG_MO_DETACH_TYPE_ENUM_UINT32  ulUeReqType;        /* UE������DETACH����*/
    LMM_ERR_LOG_MT_DETACH_TYPE_ENUM_UINT32  ulCnReqType;        /* ���ഥ����DETACH����*/
}LMM_ERR_LOG_DETACH_IND_STRU;


/*****************************************************************************
 �ṹ����   : LMM_ERR_INFO_DETAIL_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LMM������Ϣ��ϸ�ṹ
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERRLOG_ID_ENUM_UINT16           usErrLogID;         /* �������� */
    VOS_UINT16                              usRsv;              /* ����*/
    LMM_ERR_LOG_STATE_STRU                  stLmmState;         /* EMM״̬��Ϣ*/
    LMM_ERRLOG_INFO_TYPE_ENUM_UINT32        ulInfoType;         /* ��ʶ�����ĸ��ṹ��Ч */
    LMM_ERR_LOG_ATTACH_IND_STRU             stAttachInd;        /* ATTACH��� */
    LMM_ERR_LOG_TAU_RESULT_IND_STRU         stTauResultInd;	    /* TAU��� */
    LMM_ERR_LOG_SERVICE_RESULT_IND_STRU     stServiceResultInd; /* SERVICE��� */
    LMM_ERR_LOG_DETACH_IND_STRU             stDetachInd;        /* DETACH�����*/

}LMM_ERR_INFO_DETAIL_STRU;


/*****************************************************************************
 �ṹ����   : ESM_OM_ERR_INFO_DETAIL_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ESM������Ϣ��ϸ�ṹ
*****************************************************************************/
typedef struct
{
    LNAS_OM_ERRLOG_ID_ENUM_UINT16       usErrLogID;    /* �������� */
    VOS_UINT16                          usRsv;         /* ���� */
} ESM_ERR_INFO_DETAIL_STRU;


/*****************************************************************************
 �ṹ����   : LMM_ALM_INFO_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ERRLOG���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulErrlogNum;   /* ������������ЧERRLOG�ĸ��� */

    /* LMM��ERR LOG����ʱ���˴����������Ϣ */
    LMM_ERR_INFO_DETAIL_STRU            stLmmErrInfoDetail[LNAS_OM_ERRLOG_MAX_NUM];

}LMM_ALM_INFO_STRU;

/*****************************************************************************
 �ṹ����   : ESM_ALM_INFO_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ERRLOG���ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulErrlogNum;   /* ������������ЧERRLOG�ĸ��� */

    /* ESM��ERR LOG����ʱ���˴����������Ϣ */
    ESM_ERR_INFO_DETAIL_STRU            stEsmErrInfoDetail[LNAS_OM_ERRLOG_MAX_NUM];

}ESM_ALM_INFO_STRU;


/*****************************************************************************
 �ṹ����   : LMM_OM_ERR_LOG_INFO_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : LMM ERRLOG��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    /* ��ģ��ID */
    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32    ulMsgModuleID;

    /* 00������, 01������ ,10/11:����  */
    VOS_UINT16                          usModemId;

    /*  sub sys,modeule,sub module   �ݲ�ʹ��   */
    VOS_UINT16                          usALMID;

    /* ERR LOG�ϱ�����,
    Warning��0x04������ʾ��
    Minor��0x03�����Ҫ
    Major��0x02�����Ҫ
    Critical��0x01�������    */
    VOS_UINT16                          usALMLevel;

    /* ÿ��ERR LOG����������:
    ����&�澯����
    ͨ�ţ�0x00
    ҵ��������0x01
    �������0x02
    �豸���ϣ�0x03
    �������ϣ�0x04    */
    VOS_UINT16                          usALMType;
    VOS_UINT32                          ulAlmLowSlice;/*ʱ���*/
    VOS_UINT32                          ulAlmHighSlice;
    VOS_UINT32                          ulAlmLength;
    LMM_ALM_INFO_STRU                   stAlmInfo;

}LMM_OM_ERR_LOG_INFO_STRU;

/*****************************************************************************
 �ṹ����   : ESM_OM_ERR_LOG_INFO_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ESM ERRLOG��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    /* ��ģ��ID */
    OM_ERR_LOG_MOUDLE_ID_ENUM_UINT32    ulMsgModuleID;

    /* 00������, 01������ ,10/11:����  */
    VOS_UINT16                          usModemId;

    /*  sub sys,modeule,sub module   �ݲ�ʹ��   */
    VOS_UINT16                          usALMID;

    /* ERR LOG�ϱ�����,
    Warning��0x04������ʾ��
    Minor��0x03�����Ҫ
    Major��0x02�����Ҫ
    Critical��0x01�������    */
    VOS_UINT16                          usALMLevel;

    /* ÿ��ERR LOG����������:
    ����&�澯����
    ͨ�ţ�0x00
    ҵ��������0x01
    �������0x02
    �豸���ϣ�0x03
    �������ϣ�0x04    */
    VOS_UINT16                          usALMType;
    VOS_UINT32                          ulAlmLowSlice;/*ʱ���*/
    VOS_UINT32                          ulAlmHighSlice;
    VOS_UINT32                          ulAlmLength;
    ESM_ALM_INFO_STRU                   stAlmInfo;

}ESM_OM_ERR_LOG_INFO_STRU;

/*****************************************************************************
 �ṹ����   : LMM_OM_ERR_LOG_REPORT_CNF_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : NAS��ģ��LMM��OM�ظ�ERRLOGӦ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;    VOS_UINT32                          ulMsgType;    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;   /* �������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    LMM_OM_ERR_LOG_INFO_STRU            stLmmErrlogInfo;

}LMM_OM_ERR_LOG_REPORT_CNF_STRU;

/*****************************************************************************
 �ṹ����   : ESM_OM_ERR_LOG_REPORT_CNF_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : NAS��ģ��ESM��OM�ظ�ERRLOGӦ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;    VOS_UINT32                          ulMsgType;    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;   /* �������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    ESM_OM_ERR_LOG_INFO_STRU            stEsmErrlogInfo;

}ESM_OM_ERR_LOG_REPORT_CNF_STRU;


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
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

#endif /* end of LnasErrlogInterface.h */


