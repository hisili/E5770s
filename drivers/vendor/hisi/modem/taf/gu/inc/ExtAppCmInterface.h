

#ifndef _EXT_APP_CM_INTERFACE_H_
#define _EXT_APP_CM_INTERFACE_H_

#include "vos.h"
#include "TafSmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif    /* __cpluscplus */
#endif    /* __cpluscplus */
#pragma pack(4)
/* ------------------------------API �����ṹ---------------------------------*/

/************************** BASIC TYPE DEFINITION START ************************/

/********************** ENUMERATED STRUCT DEFINITION START *********************/

/* APP-NAS structure : SspTaCause */
typedef enum {
    EN_STC_NORMAL = 0,
    EN_STC_NOT_SUPPT,
    EN_STC_TE_NOT_CONN,
    EN_STC_SSP_TIMEOUT,
    EN_STC_MSG_ERR,
    EN_STC_IE_ERR,
    EN_STC_OTHER_REASON
    /* ... */
} SSP_TA_CAUSE;
typedef VOS_UINT8  ENUM_SSP_TA_CAUSE;

/* APP-NAS structure : SspMtCause */
typedef enum {
    EN_SMC_QUAL_WORSE = 0,
    EN_SMC_CONGEST,
    EN_SMC_COVERAGE_OUT,
    EN_SMC_ACC,
    EN_SMC_NW_OUT_OF_ORDER,
    EN_SMC_BATTERY_ALERM_CONN,
    EN_SMC_BATTERY_ALERM_IDLE,
    EN_SMC_NO_UIM,
    EN_SMC_INVALID_UIM,
    EN_SMC_PIN_BLOCK,
    EN_SMC_ENSURE_EC,
    EN_SMC_NOT_SUPPT,
    EN_SMC_INSUFF_CAPAB,
    EN_SMC_ALREADY_CONNECT,
    EN_SMC_SSP_TIMEOUT,
    EN_SMC_SS_TIMEOUT,
    EN_SMC_SS_PROT_ERR,
    EN_SMC_RRC_PROT_ERR,
    EN_SMC_MM_GMM_PROT_ERR,
    EN_SMC_MSG_ERR,
    EN_SMC_IE_ERR,
    EN_SMC_OTHER_REASON
    /* ... */
} SSP_MT_CAUSE;
typedef VOS_UINT8  ENUM_SSP_MT_CAUSE;
/********************** ENUMERATED STRUCT DEFINITION END   *********************/

/********************** OCTET STRING STRUCT DEFINITION START *******************/
/*Modified by Jim J00240*/
#pragma pack(4)

/* APP-NAS structure : Facility */
typedef struct {
    VOS_UINT32  ulCnt;
    VOS_UINT8  Facility[255];
} ST_SSP_IES_FACILITY;

/* APP-NAS structure : Sspversion */
typedef struct {
    VOS_UINT32  ulCnt;
    VOS_UINT8  Sspversion[1];
} ST_SSP_IES_SSPVERSION;

/* APP-NAS structure : Cause */
typedef struct {
    VOS_UINT32  ulCnt;
    VOS_UINT8  Cause[30];
} ST_SSP_IES_CAUSE;

/********************** OCTET STRING STRUCT DEFINITION END   *******************/

/********************** COMPLEX TYPE STRUCT DEFINITION START *******************/

/* APP-NAS structure : Begin-req */
typedef struct {
    VOS_UINT32  OP_Sspversion    : 1;
    VOS_UINT32  OP_Spare         : 31;

    ST_SSP_IES_FACILITY      Facility;                                          /* OCTET STRING(SIZE(0..255,...)) */
    ST_SSP_IES_SSPVERSION    Sspversion;                                        /* OCTET STRING(SIZE(1,...))  OPTIONAL */
                                                                                /* ... */
} ST_BEGIN_REQ;

/* APP-NAS structure : Facility-req */
typedef struct {
    ST_SSP_IES_FACILITY    Facility;                                            /* OCTET STRING(SIZE(0..255,...)) */
                                                                                /* ... */
} ST_SSP_MSGS_FACILITY_REQ;

/* APP-NAS structure : End-req */
typedef struct {
    VOS_UINT32  OP_Cause       : 1;
    VOS_UINT32  OP_Facility    : 1;
    VOS_UINT32  OP_SspTaCause  : 1;
    VOS_UINT32  OP_Spare       : 29;

    ST_SSP_IES_CAUSE       Cause;                                               /* OCTET STRING(SIZE(2..30,...))  OPTIONAL */
    ST_SSP_IES_FACILITY    Facility;                                            /* OCTET STRING(SIZE(0..255,...))  OPTIONAL */
                                                                                /* ... */
    ENUM_SSP_TA_CAUSE      enSspTaCause;                                        /* ENUMERATED  OPTIONAL */
} ST_END_REQ;

/* APP-NAS structure : Begin-ind */
typedef struct {
    ST_SSP_IES_FACILITY    Facility;                                            /* OCTET STRING(SIZE(0..255,...)) */
                                                                                /* ... */
} ST_BEGIN_IND;

/* APP-NAS structure : Facility-ind */
typedef struct {
    ST_SSP_IES_FACILITY    Facility;                                            /* OCTET STRING(SIZE(0..255,...)) */
                                                                                /* ... */
} ST_SSP_MSGS_FACILITY_IND;


enum SSA_SS_REL_CAUSE_ENUM
{
    SSA_SS_REL_CAUSE_AS_REJ_LOW_LEVEL_FAIL,
    SSA_SS_REL_CAUSE_AS_REJ_OTHER_CAUSES,
    SSA_SS_REL_CAUSE_MM_WRONG_STATE,
    SSA_SS_REL_CAUSE_MM_NO_SERVICE,
    SSA_SS_REL_CAUSE_MM_LIMIT_SERVICE,
    SSA_SS_REL_CAUSE_MM_TIMER_T3230_EXP,
    SSA_SS_REL_CAUSE_MM_REJ_OTHER_CAUSES,
    SSA_SS_REL_CAUSE_BUTT
};
typedef VOS_UINT32 SSA_SS_REL_CAUSE_ENUM_UINT32;



enum SSA_SS_CS_CONN_STATE_ENUM
{
    SSA_SS_CS_CONN_STATE_ABSENT,                                                /* ���Ӳ����� */
    SSA_SS_CS_CONN_STATE_PRESENT,                                               /* ���Ӵ��� */
    SSA_SS_CS_CONN_STATE_BUTT
};
typedef VOS_UINT8 SSA_SS_CS_CONN_STATE_ENUM_UINT8;


typedef struct
{
    SSA_SS_CS_CONN_STATE_ENUM_UINT8     enConnState;
    VOS_UINT8                           aucReserved[3];
}SSA_SS_CS_CONN_IND_STRU;


/* APP-NAS structure : End-ind */
typedef struct {
    VOS_UINT32  OP_Cause       : 1;
    VOS_UINT32  OP_Facility    : 1;
    VOS_UINT32  OP_SspMtCause  : 1;
    VOS_UINT32  OP_Spare       : 29;

    ST_SSP_IES_CAUSE       Cause;                                               /* OCTET STRING(SIZE(2..30,...))  OPTIONAL */
    ST_SSP_IES_FACILITY    Facility;                                            /* OCTET STRING(SIZE(0..255,...))  OPTIONAL */
                                                                                /* ... */
    ENUM_SSP_MT_CAUSE      enSspMtCause;                                        /* ENUMERATED  OPTIONAL */

    SSA_SS_REL_CAUSE_ENUM_UINT32      enSsaSsRelCause;
    VOS_UINT8                         aucReserved[3];

} ST_END_IND;

/* APP-NAS structure : SSPmsgCore */
typedef struct {
    VOS_UINT8      ucChoice;

    #define    D_SMC_BEGIN_REQ       0
    #define    D_SMC_FACILITY_REQ    1
    #define    D_SMC_END_REQ         2
    #define    D_SMC_BEGIN_IND       3
    #define    D_SMC_FACILITY_IND    4
    #define    D_SMC_END_IND         5

    #define    SSA_SS_CS_CONN_IND         (6)

    union  {
        ST_BEGIN_REQ                BeginReq;
        ST_SSP_MSGS_FACILITY_REQ    FacilityReq;
        ST_END_REQ                  EndReq;
        ST_BEGIN_IND                BeginInd;
        ST_SSP_MSGS_FACILITY_IND    FacilityInd;
        ST_END_IND                  EndInd;

        SSA_SS_CS_CONN_IND_STRU     stCsConnInd;

    } u;
} ST_SSP_MSG_CORE;

/* APP-NAS structure : SSPmessage */
typedef struct {
    VOS_UINT8              ucCr;                                                    /* INTEGER(0..255) */
    ST_SSP_MSG_CORE    SspmsgCore;
} ST_SSP_MSG;


/*Added by Jim for asn.1 begin*/
typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                  /* ��Ϣͷ                                   */
    ST_SSP_MSG                      stSspMsg;
}APP_SS_MSG_DATA;
/*_H2ASN_Length VOS_UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    APP_SS_MSG_DATA                 MsgData;
}AppSsInterface_MSG;
/*Added by Jim for asn.1 end*/



#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif
/********************** COMPLEX TYPE STRUCT DEFINITION END   *******************/
#ifdef __cplusplus
#if __cplusplus
}
#endif    /* __cpluscplus */
#endif    /* __cpluscplus */

#endif    /* _PER_INTERFACE_H_ */
