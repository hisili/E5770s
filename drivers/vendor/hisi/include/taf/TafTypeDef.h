
#ifndef  TAF_TYPE_DEF_H
#define  TAF_TYPE_DEF_H

#include "v_typdef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)
/* Added by f62575 for AT Project, 2011-10-24, begin */

/* LOCAL */
#ifdef  LOCAL
#undef  LOCAL
#endif

#ifdef _EXPORT_LOCAL
#define LOCAL
#else
#define LOCAL static
#endif
/* Added by f62575 for AT Project, 2011-10-24, end */


/* ---------------LogSaver��ά�ɲ⹦����ض���----------------------- */
/* 1.1: OM_GreenChannel�ĵڶ�������usPrimId�Ķ���*/
#define     TAF_OM_GREEN_CHANNEL_PS     (0xC001)                                /* PS��� */

/* 1.2: OM_GreenChannel�ĵ����������ɴ�һЩ��ά�ɲ���Ϣ��Ϊ����߶�λЧ�ʣ���һЩ����
   ������������ö�ٶ��� */
enum TAF_OM_GREENCHANNEL_ERR_ENUM
{
    TAF_OM_GREENCHANNEL_PS_CID_NOT_DEFINE = 0,
    TAF_OM_GREENCHANNEL_PS_CREATE_PPP_REQ_ERR,
    TAF_OM_GREENCHANNEL_PS_CREATE_RAW_DATA_PPP_REQ_ERR,
    TAF_OM_GREENCHANNEL_PS_IP_TYPE_DIAL_FAIL,
    TAF_OM_GREENCHANNEL_PS_PPP_TYPE_DIAL_FAIL,
    TAF_OM_GREENCHANNEL_PS_DEACTIVE_PDP_ERR_EVT,
    TAF_OM_GREENCHANNEL_PS_ACTIVE_PDP_REJ,
    TAF_OM_GREENCHANNEL_PS_MODIFY_PDP_REJ,
    TAF_OM_GREENCHANNEL_PS_NET_ORIG_DEACTIVE_IND,

    TAF_OM_GREENCHANNEL_ERR_BUTT
};

/*�ֽ�����*/
#define TAF_LITTLE_ENDIAN              1234
#define TAF_BIG_ENDIAN                 4321

#define TAF_BYTE_ORDER                 TAF_LITTLE_ENDIAN

/*OS����*/
#define TAF_WIN32                      1
#define TAF_PSOS                       2
#define TAF_VXWORKS                    3
#define TAF_LINUX                      4
#define TAF_UNIX                       5
#define TAF_SOLARIS                    6
#define TAF_TLINUX                     7
#define TAF_HPUNIX                     8
#define TAF_IBMUNIX                    9
#define TAF_RTT                        10
#define TAF_WINCE                      11
#define TAF_NUCLEUS                    12

#ifndef TAF_OS_VER
#define TAF_OS_VER                     TAF_VXWORKS
#endif

#ifndef CONST
#define CONST const
#endif

#ifndef CONST_T
#define CONST_T   const
#endif

#ifndef STATIC
#define STATIC static
#endif

#undef PUBLIC
#undef PRIVATE
#undef EXTERN
#define PUBLIC    extern
#define EXTERN extern
#ifdef _EXPORT_PRIVATE
#define PRIVATE
#else
#define PRIVATE   static
#endif

#undef OUT
#undef IN
#define OUT
#define IN


/*TAF API��������*/
typedef int                 TAF_INT;
typedef signed   char       TAF_INT8;
typedef unsigned char       TAF_UINT8;

typedef signed   short      TAF_INT16;
typedef unsigned short      TAF_UINT16;

typedef signed   long       TAF_INT32;
typedef unsigned long       TAF_UINT32;

typedef char                TAF_CHAR;
typedef unsigned char       TAF_UCHAR;

typedef void                TAF_VOID;

typedef unsigned long       TAF_BOOL;
enum
{
    TAF_FALSE = 0,
    TAF_TRUE  = 1
};

typedef TAF_UINT8 MN_CLIENT_TYPE;
enum MN_CLIENT_TYPE_ENUM
{
    TAF_APP_CLIENT,
    TAF_AT_CLIENT,
    TAF_CLIENT_TYPE_BUTT
};

typedef TAF_UINT16          MN_CLIENT_ID_T;     /* APP/AT Client ID type */
typedef TAF_UINT8           MN_OPERATION_ID_T;  /* Async operation ID type */

/* ��ʾ���е�Client */
#define MN_CLIENT_ALL                                       ((MN_CLIENT_ID_T)(-1))
#define MN_OP_ID_BUTT                                       ((MN_OPERATION_ID_T)(-1))

/* ����CMMCA��client id */
#define CMMCA_CLIENT_ID                                     (0x88)

#define  TAF_NULL_PTR                   0                    /* null pointer */

#define  TAF_MAX_STATUS_TI              1

/*TAF API �����붨��*/
/*����������*/
typedef TAF_UINT16   TAF_PH_ERR_CODE;
#define TAF_ERR_NO_ERROR                   (0)  /*�ɹ�*/
#define TAF_ERR_ERROR                      (1)  /*ʧ��*/
#define TAF_ERR_NULL_PTR                   (2)  /*��ָ��*/
#define TAF_ERR_PARA_ERROR                 (3)  /*��������*/
#define TAF_ERR_TIME_OUT                   (4)  /*��ʱ����ʱ*/
#define TAF_ERR_TAF_ID_INVALID             (5)  /*CallId����OpId����Smi��Ч*/
#define TAF_ERR_NUM_VALUE_INVALID          (6)  /*��������(����value��Ч)*/
#define TAF_ERR_NUM_LEN_INVALID            (7)  /*���볤��Ϊ0���߳�����󳤶�*/
#define TAF_ERR_CAPABILITY_ERROR           (8)  /*�ն�������֧��*/
#define TAF_ERR_CLIENTID_NO_FREE           (9)  /*û�п���ClientId������ʧ��*/
#define TAF_ERR_CALLBACK_FUNC_ERROR       (10)  /*�ص���������*/
#define TAF_ERR_MSG_DECODING_FAIL         (11)  /*��Ϣ����ʧ��*/
#define TAF_ERR_TI_ALLOC_FAIL             (12)  /*TI����ʧ��*/
#define TAF_ERR_TI_GET_FAIL               (13)  /* ��ȡTiʧ�� */
#define TAF_ERR_CMD_TYPE_ERROR            (14)  /*�������ʹ���*/
#define TAF_ERR_MUX_LINK_EST_FAIL         (15)  /*APP��TAF֮��MUX��·����ʧ��*/
#define TAF_ERR_USIM_SIM_CARD_NOTEXIST    (16)  /*USIM��������*/
#define TAF_ERR_CLIENTID_NOT_EXIST        (17)  /*ClientId������*/
#define TAF_ERR_NEED_PIN1                 (18)  /*��Ҫ����PIN1��*/
#define TAF_ERR_NEED_PUK1                 (19)  /*��Ҫ����PUK1*/
#define TAF_ERR_USIM_SIM_INVALIDATION     (20)  /*��Ч��USIM/SIM��*/
#define TAF_ERR_SIM_BUSY                  (21)  /*SIM��æ*/
#define TAF_ERR_SIM_LOCK                  (22)
#define TAF_ERR_SIM_INCORRECT_PASSWORD    (23)  /*����ȷ������*/
#define TAF_ERR_SIM_FAIL                  (24)  /*SIM������ʧ��*/
#define TAF_ERR_NOT_READY                 (25)  /* ����δ���س�ʼ����ɣ����չ��ߵ��л�FTMģʽ���� */
#define TAF_ERR_FILE_NOT_EXIST            (26)  /* OPL �ļ������� */
#define TAF_ERR_NO_NETWORK_SERVICE        (27)  /* ������ */
/* Added by f62575 for AT Project, 2011-10-04,  Begin */
#define TAF_ERR_GET_CSQLVL_FAIL           (28)                                  /* ��ȡCSQLVL��Ϣ���� */
/* Added by f62575 for AT Project, 2011-10-04,  End */
#define TAF_ERR_AT_ERROR                  (29)  /* ���AT_ERROR */
#define TAF_ERR_CME_OPT_NOT_SUPPORTED     (30)  /* ���AT_CME_OPERATION_NOT_SUPPORTED */

#define TAF_ERR_AT_CONNECT                (31)  /* ���AT_CONNECT */

/* Added by f62575 for AT Project, 2011-11-3, begin */
#define TAF_ERR_USIM_SVR_OPLMN_LIST_INAVAILABLE (32)                            /* ��ȡ(U)SIM��USIM_SVR_OPLMN_LIST����ʧ�� */
/* Added by f62575 for AT Project, 2011-11-3, end */
/* Added by f62575 for C50_IPC Project, 2012/02/23, begin */
#define TAF_ERR_FDN_CHECK_FAILURE                (33)                           /* FDNҵ����ʧ�� */
#define TAF_ERR_INTERNAL                         (34)

/* Added by f62575 for C50_IPC Project, 2012/02/23, end   */

/* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-16, begin */
/* ����ѡ��˵��Ѿ�disable���û�����ָ�������ظ��Ĵ����� */
#define TAF_ERR_NET_SEL_MENU_DISABLE             (36)
/* Added by L60609 for V7R1C50 AT&T&DCM, 2012-6-16, end */

/* CSҵ�����ʱ��AT����SYSCFG�ظ��Ĵ����� */
#define TAF_ERR_SYSCFG_CS_SERV_EXIST             (37)

#define TAF_ERR_NEED_PUK2                        (38)  /*��Ҫ����PUK2*/
/* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
#define TAF_ERR_USSD_NET_TIMEOUT                 (39)  /* USSD��ʱ����ʱ TAF_ERR_USSD_TIME_OUT => TAF_ERR_USSD_NET_TIMEOUT */
/* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

/* SS��USSDҵ��������ǰ����USSDҵ���ʧ�� */
/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
#define TAF_ERR_BUSY_ON_USSD                     (40)
#define TAF_ERR_BUSY_ON_SS                       (41)
#define TAF_ERR_USSD_USER_TIMEOUT                (42)
#define TAF_ERR_SS_NET_TIMEOUT                   (43)
#define TAF_ERR_USSD_TERMINATED_BY_USER          (44)
/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

#define TAF_ERR_NO_SUCH_ELEMENT                  (45)
#define TAF_ERR_MISSING_RESOURCE                 (46)

#define TAF_ERR_SS_DOMAIN_SELECTION_FAILURE         (47)    /* ҵ����ѡ��ʧ�� */
#define TAF_ERR_SS_DOMAIN_SELECTION_TIMER_EXPIRED   (48)    /* ҵ����ѡ�񻺴汣����ʱ����ʱ */
#define TAF_ERR_SS_POWER_OFF                        (49)    /* ҵ����ѡ���յ��ػ�ָʾ������� */

#define TAF_ERR_UNSPECIFIED_ERROR                   (50)  /*������������*/

/* ��SS��صĴ���causeֵת�Ƶ�TafApiSsa.h�ļ�*/

/*�绰���������*/
#define  TAF_ERR_PHONE_BASE                 (150)
#define  TAF_ERR_PHONE_MSG_UNMATCH          (TAF_ERR_PHONE_BASE + 1)  /*��Ϣ��ϵ��ƥ��*/
#define  TAF_ERR_PHONE_ATTACH_FORBIDDEN     (TAF_ERR_PHONE_BASE + 2) /*��ֹATTACH����*/
#define  TAF_ERR_PHONE_DETACH_FORBIDDEN     (TAF_ERR_PHONE_BASE + 3) /*��ֹDETACH����*/

/* ��SS��صĴ���causeֵת�Ƶ�TafApiSsa.h�ļ�*/

/*GNA������*/

/*�绰��������*/
#define TAF_ERR_PB_BASE                             (350)
#define TAF_ERR_PB_NOT_INIT                         (TAF_ERR_PB_BASE + 1)   /*PBģ����δ��ʼ��*/
#define TAF_ERR_PB_MALLOC_FAIL                      (TAF_ERR_PB_BASE + 2)   /*�����ڴ�ʧ��*/
#define TAF_ERR_PB_WRONG_INDEX                      (TAF_ERR_PB_BASE + 3)   /*�����index*/
#define TAF_ERR_PB_WRONG_PARA                       (TAF_ERR_PB_BASE + 4)   /*������������*/
#define TAF_ERR_PB_STORAGE_FULL                     (TAF_ERR_PB_BASE + 5)   /*��������*/
#define TAF_ERR_PB_STORAGE_OP_FAIL                  (TAF_ERR_PB_BASE + 6)   /*������ʧ��*/
#define TAF_ERR_PB_NOT_FOUND                        (TAF_ERR_PB_BASE + 7)   /*��ƥ���¼*/
#define TAF_ERR_PB_DIAL_STRING_TOO_LONG             (TAF_ERR_PB_BASE + 8)   /*����ĺ����д�*/

/*SAT������*/
#define TAF_ERR_SAT_BASE                            (400)
#define TAF_ERR_SAT_MALLOC_FAIL                     (TAF_ERR_SAT_BASE + 1)  /*�����ڴ�ʧ��*/
#define TAF_ERR_SAT_WRONG_PARA                      (TAF_ERR_SAT_BASE + 2)  /*������������*/
#define TAF_ERR_SAT_STORAGE_OP_FAIL                 (TAF_ERR_SAT_BASE + 3)  /*������ʧ��*/
#define TAF_ERR_SAT_STORAGE_OP_93_SW                (TAF_ERR_SAT_BASE + 4)  /*93�ظ�*/
#define TAF_ERR_SAT_NO_MAIN_MENU                    (TAF_ERR_SAT_BASE + 5)  /*û�����˵�*/

#define TAF_ERR_SS_BASE                             (0x400)

#define TAF_ERR_SS_IMS_BASE                         (0x1000)

#define TAF_ERR_SS_IMSA_BASE                        (0x2000)

#ifndef TAF_SUCCESS
#define TAF_SUCCESS    TAF_ERR_NO_ERROR     /*����ִ�гɹ�*/
#endif
#ifndef TAF_FAILURE
#define TAF_FAILURE    TAF_ERR_ERROR        /*����ִ��ʧ��*/
#endif



typedef TAF_UINT8 TAF_PARA_TYPE;
#define TAF_CS_CALL_MODE_PARA          0
#define TAF_CS_SINGLE_NUM_SCHEME_PARA  1
#define TAF_CS_BEARER_SERVICE_PARA     2
#define TAF_CS_CLIR_INFO_PARA          3
#define TAF_CS_CALLED_NUM_TYPE_PARA    4
#define TAF_CS_CUG_INFO_PARA           5
#define TAF_CS_AUTO_ANSWER_PARA        6
#define TAF_CS_UUSINFO_QRY             7
#define TAF_CS_ALS_LINE_NO_QRY         8  /*��ѯ��ǰ����·�� */


/* ɾ������Ĵ��� */

#define TAF_NDIS_AUTHDATA_PARA         41     /*^AUTHDATA*/

#define TAF_SMS_MSG_FORMAT_PARA        60
#define TAF_SMS_SC_ADDR_PARA           61
#define TAF_SMS_SEND_DOMAIN_PARA       62
#define TAF_SMS_VERSION_PARA           63
#define TAF_SMS_TEXT_MODE_PARA         64
#define TAF_SMS_SAVE_AREA_PARA         65
#define TAF_SMS_USIM_RECORDS_PARA      66
#define TAF_SMS_NVIM_RECORDS_PARA      67
#define TAF_SMS_CNMA_ENABLE_PARA       68
#define TAF_SMS_MEM_RECORDS_PARA       69

#define TAF_PH_ACCESS_MODE_PARA          90
#define TAF_PH_MS_CLASS_PARA             91
#define TAF_PH_MS_BAND_PARA              92
#define TAF_PH_REG_PLMN_PARA             93
#define TAF_PH_MFR_ID_PARA               94    /*+CGMI - ��ȡ����������*/
#define TAF_PH_MODEL_ID_PARA             95    /*+CGMM - ��ȡģ���ʶ*/
#define TAF_PH_REVISION_ID_PARA          96    /*+CGMR - ��ȡģ������汾��*/
#define TAF_PH_IMEI_ID_PARA              97    /*+CGSN - ��ȡIMEI*/
#define TAF_PH_IMSI_ID_PARA              98    /*+CIMI - ��ȡIMSI*/
#define TAF_PH_CS_REG_STATE_PARA         99    /*+CREG -CS ����ע��״̬*/
#define TAF_PH_PS_REG_STATE_PARA         100   /*+CGREG - PS����ע��״̬*/
#define TAF_PH_MODE_GET_PARA             101   /*+CFUN��ȡ��ǰ���ֻ�����ģʽ*/
#define TAF_PH_RSSI_VALUE_PARA           102   /*+CSQ��ȡ��ǰ��RSSIֵ*/
#define TAF_PH_BATTERY_POWER_PARA        103   /*+CBC��ȡ��ǰ��Դ����״̬*/
#define TAF_PH_NETWORKNAME_PARA          104   /*+CPOS, �Ӻ��������ȡ��ǰ��Ӫ������*/
#define TAF_PH_NETWORKNAMEFROMUSIM_PARA  105   /*^SPIN, ��USIM�л�ȡ��ǰ��Ӫ������*/
#define TAF_PH_SRV_STATUS_PARA           106   /* ^SRVST��ȡ�ֻ���������״̬*/
#define TAF_PH_IDENTIFICATION_INFO_PARA  107
#define TAF_PH_CUR_FREQ                  108
#define TAF_PH_ICC_ID                    110
#define TAF_PH_CELL_RSCP_VALUE_PARA      111
#define TAF_PH_UE_RFPOWER_FREQ_PARA      112
#define TAF_PH_SYSINFO_VALUE_PARA        113
#define TAF_PH_ICC_TYPE_PARA             114
#define TAF_PH_ICC_STATUS_PARA           115
#define TAF_PH_QUICK_START_PARA          116
#define TAF_PH_LOAD_DEFAULT              117
#define TAF_PH_FPLMN_PARA                118
#define TAF_PH_AUTO_ATTACH_PARA          119
#define TAF_PH_PNN_PARA                  120
#define TAF_PH_OPL_PARA                  121
#define TAF_PH_HS_PARA                   122
#define TAF_PH_QRY_PERF_PLMN_PARA        123
#define TAF_PH_SET_PERF_PLMN_PARA        124
#define TAF_PH_CPNN_PARA                 125
#define TAF_PH_PNN_RANGE_PARA            126
#define TAF_PH_OPL_RANGE_PARA            127
#define TAF_PH_CSQLVLEXT_VALUE_PARA      (128)   /*^CSQLVLEXT��ȡ��ǰ��RSSIֵ*/

#define TAF_PH_SYSINFO_EX_VALUE_PARA     (129)

#define TAF_PH_REGISTER_TIME_VALUE_PARA  (130)
#define TAF_PH_ANQUERY_VALUE_PARA        (131)
#define TAF_PH_HOMEPLMN_VALUE_PARA       (132)
#define TAF_PH_CSNR_VALUE_PARA           (133)
#define TAF_PH_SPN_VALUE_PARA            (134)



/* Added by f62575 for AT Project��2011-10-04,  Begin*/
#define TAF_PH_CSQLVL_VALUE_PARA         (135)                                  /*+CSQLVL��ȡ<csq_level>,<rscp>ֵ*/
/* Added by f62575 for AT Project��2011-10-04,  End*/

#define TAF_PH_EPS_REG_STATE_PARA        (136)                /* +CEREG - EPS����ע��״̬*/

/* Added by f62575 for B050 Project, 2012-2-3, Begin   */
#define TAF_PH_SIMLOCK_VALUE_PARA        (137)                                  /*^SIMLOCK=2��ȡ���ݿ�������״̬ */
/* Added by f62575 for B050 Project, 2012-2-3, end   */


/* ɾ��TAF_PH_CELLROAM_PARA */

#if(FEATURE_ON == MBB_FEATURE_CELLROAM)
#define TAF_PH_CELLROAM_PARA             (138)
#endif/*MBB_FEATURE_CELLROAM*/

#define TAF_MM_PLMN_INFO_QRY_PARA        (139)

#define TAF_PH_PLMN_QRY_PARA             (140)

#define TAF_PH_USER_SRV_STATE_QRY_PARA   (141)
#if (FEATURE_ON == MBB_WPG_COMMON)
#define TAF_MM_PLMN_TIMEZONE_QRY_PARA    (142)
#define TAF_PH_HCSQ_PARA                 (143)
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
#define TAF_PH_CIND_VALUE_PARA     (144)
#define TAF_PH_QOSIG_VALUE_PARA           (145)
#define TAF_PH_ANT_VALUE_PARA         (146)   
#define TAF_TELE_PARA_BUTT               (147)
#else
#define TAF_TELE_PARA_BUTT               (144)
#endif
#else
#define TAF_TELE_PARA_BUTT               (142)

#endif




/*�������ý��*/
typedef TAF_UINT8 TAF_PARA_SET_RESULT;
#define TAF_PARA_OK                            0  /*�������óɹ�*/
#define TAF_PARA_SET_ERROR                     1  /*���ò�������*/
#define TAF_PARA_WRITE_NVIM_ERROR              2  /*дNVIMʧ��*/
#define TAF_PARA_TYPE_NOT_SUPPORT              3  /*��֧�ֵĲ�������*/
#define TAF_PARA_CID_NOT_SUPPORT               4  /*CIDȡֵ����֧�ַ�Χ*/
#define TAF_PARA_NOT_INCLUDE_ALL_OP_IE         5  /*�������÷��޸ģ�δ�������п�ѡ����*/
#define TAF_PARA_IE_DECODE_ERROR               6  /*��Ϣ����ʧ��*/
#define TAF_PARA_IE_ENCODE_ERROR               7  /*��Ϣ����ʧ��*/
#define TAF_PARA_IE_VALUE_ERROR                8  /*����ȡֵ����*/
#define TAF_PARA_CMD_NOT_MATCH_PARA            9  /*�޷��Ըò���ִ�в���*/
#define TAF_PARA_SIM_IS_BUSY                   10 /*SIM����æ*/
#define TAF_PARA_PDP_CONTEXT_NOT_DEFINED       11 /*PDP������δ����*/
#define TAF_PARA_SEC_PDP_CONTEXT_NOT_DEFINED   12 /*����PDP������δ����*/
#define TAF_PARA_TFT_NOT_DEFINED               13 /*TFTδ����*/
#define TAF_PARA_QOS_NOT_DEFINED               14 /*QOSδ����*/
#define TAF_PARA_MIN_QOS_NOT_DEFINED           15 /*MIN QOSδ����*/
#define TAF_PARA_SPN_NO_EXIST                  16 /*spn�ļ�������*/
#define TAF_PARA_ALLOC_MEM_FAIL                17 /*��ѯ����ʱ,�����ڴ�ʧ��*/
#define TAF_PARA_NO_USIM_ERROR                 18 /*��ѯimsiʱ��USIM����*/
#define TAF_PARA_AUTH_NOT_DEFINED              19 /*AUTHδ����*/
#define TAF_PARA_MEMORY_FULL                   20
#define TAF_PARA_INVALID_INDEX                 21
#define TAF_PARA_NDIS_AUTHDATA_NOT_DEFINED     22 /*NDIS AUTHDATAδ����*/
#define TAF_PARA_EPS_QOS_NOT_DEFINED           23 /* EPS QOSδ���� */
#define TAF_PARA_INVALID_PLMNID                24
#define TAF_PARA_DUPLICATE_PLMNINFO            25
#define TAF_PARA_UNSPECIFIED_ERROR             255 /*��������*/


/* �꣬�£��գ�ʱ���֣��룬��ΪBCD�����ʽ��
   ���ֽ�Ϊ10λ�������ֽ�Ϊ��λ������: 0x51 תΪ0x15,��ʾ10������15
   ʱ��Ϊ�з�����������15����Ϊ��λ */
typedef struct{
    VOS_UINT8                       ucYear;
    VOS_UINT8                       ucMonth;
    VOS_UINT8                       ucDay;
    VOS_UINT8                       ucHour;
    VOS_UINT8                       ucMinute;
    VOS_UINT8                       ucSecond;
    VOS_INT8                        cTimeZone;
    VOS_UINT8                       Reserved;
}TIME_ZONE_TIME_STRU;

/* ��ϢMMCMM_INFO_IND�Ľṹ�� */
#if (FEATURE_ON == MBB_WPG_COMMON)
typedef struct
{
    VOS_UINT8                       ucIeFlg;
    VOS_INT8                        cLocalTimeZone;
    VOS_UINT8                       ucDST;
    VOS_UINT8                       ucLSAID[3];
    VOS_UINT8                       aucReserve[2];
    VOS_UINT32                      ulTimeSeconds;    /*record the time slice of get the NITZ*/
    TIME_ZONE_TIME_STRU   stUniversalTimeandLocalTimeZone;
    VOS_UINT32                      blRcvNwNameFlag;
}NAS_MM_INFO_IND_STRU;
#else
typedef struct
{
    VOS_UINT8                       ucIeFlg;
    VOS_INT8                        cLocalTimeZone;
    VOS_UINT8                       ucDST;
    VOS_UINT8                       ucLSAID[3];
    VOS_UINT8                       aucReserve[2];
    TIME_ZONE_TIME_STRU             stUniversalTimeandLocalTimeZone;
}NAS_MM_INFO_IND_STRU;
#endif

#if ((TAF_OS_VER == TAF_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* TAF_TYPE_DEF_H */

