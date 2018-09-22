

#ifndef __TAF_MMI_STR_PARSE_H__
#define __TAF_MMI_STR_PARSE_H__


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafTypeDef.h"
#include  "MnCallApi.h"
#include  "TafAppSsa.h"
#include  "TafAppMma.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 ��������
*****************************************************************************/
/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */
/* ��Ϊ������TafMmiEncode.cҲҪʹ������꣬��Taf_MmiStrParse.c�ƶ���Taf_MmiStrParse.c */
/*****************************************************************************
  3 �궨��
*****************************************************************************/
#define  MMI_MAX_DTMF_STR_LEN           40
#define MN_MMI_MIN_USSD_LEN             2

#define MN_MMI_DONT_CARE_CHAR           '?'
#define MN_MMI_START_SI_CHAR            '*'
#define MN_MMI_STOP_CHAR                '#'

#define MN_MMI_isdigit(c)               (((c) >= '0') && ((c) <= '9'))

#define MN_MMI_STR_PTR_IS_VALID(pcFrom, pcTo)   ((VOS_NULL_PTR == (pcTo)) || ((VOS_NULL_PTR != (pcTo)) && ((pcFrom) <= (pcTo))))

#define MN_MMI_MAX(a, b)                (((a) > (b)) ? (a) : (b))

#define MN_MMI_MAX_SC_LEN               3                                       /* Ŀǰ��˵����󳤶�Ϊ3*/
#define MN_MMI_MAX_SIA_LEN              30                                      /* �����ں��볤�ȵ�������� */
#define MN_MMI_MAX_SIB_LEN              8                                       /* PWD��PIN�ĳ��� */
#define MN_MMI_MAX_SIC_LEN              8                                       /* PWD��PIN�ĳ��� */

#define MN_MMI_MAX_BUF_SIZE             64
#define MN_MMI_MAX_PARA_NUM             4
/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */
/*****************************************************************************
  3���Ͷ���
*****************************************************************************/
enum TAF_MMI_OPERATION_TYPE_ENUM
{
    TAF_MMI_CALL_ORIG,                                                           /*Setup a Call*/
    TAF_MMI_CALL_CHLD_REQ,
    TAF_MMI_CHANGE_PIN,
    TAF_MMI_CHANGE_PIN2,                                                         /*Change Pin*/
    TAF_MMI_UNBLOCK_PIN,                                                        /*Unblock Pin*/
    TAF_MMI_UNBLOCK_PIN2,
    TAF_MMI_DISPLAY_IMEI,                                                       /*Display IMEI*/
    TAF_MMI_REGISTER_SS,                                                        /*Register Operation*/
    TAF_MMI_ERASE_SS,                                                           /*Erase Operation*/
    TAF_MMI_ACTIVATE_SS,                                                        /*Activate Operation*/
    TAF_MMI_DEACTIVATE_SS,                                                      /*Deactivate Operation*/
    TAF_MMI_INTERROGATE_SS,                                                     /*Interrogate Operation*/
    TAF_MMI_REGISTER_PASSWD,                                                    /*Register the password*/
    /* Delete by f62575 for SS FDN&Call Control, 2013-05-06, begin */
    /* Delete TAF_MMI_GET_PASSWD */
    /* Delete by f62575 for SS FDN&Call Control, 2013-05-06, end */
    TAF_MMI_FWD_CHECK_SS_IND,                                                   /*Forward Check Operation*/
    TAF_MMI_PROCESS_USSD_REQ,                                                   /*Process USSD Request*/
    TAF_MMI_SUPPRESS_CLIR,
    TAF_MMI_INVOKE_CLIR,
    TAF_MMI_SUPPRESS_CLIP,
    TAF_MMI_INVOKE_CLIP,
    TAF_MMI_SUPPRESS_COLR,
    TAF_MMI_INVOKE_COLR,
    TAF_MMI_SUPPRESS_COLP,
    TAF_MMI_INVOKE_COLP,
    TAF_MMI_NULL_OPERATION,                                                     /*Null Operation*/
    TAF_MMI_DEACTIVATE_CCBS,
    TAF_MMI_INTERROGATE_CCBS,
    TAF_MMI_MAX_OPERATION
};
typedef TAF_UINT8 MN_MMI_OPERATION_TYPE_ENUM_U8;

/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */
/* ��Ϊ������TafMmiEncode.cҲҪʹ������ṹ����Taf_MmiStrParse.c�ƶ���Taf_MmiStrParse.c */
typedef struct
{
    VOS_CHAR                            *pString;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enOperationType;
    VOS_UINT8                           aucRsv[3];
}MN_MMI_STR_OPERATION_Tbl_STRU;

typedef struct
{
    VOS_CHAR                            acSsCode[MN_MMI_MAX_SC_LEN + 1];
    VOS_CHAR                            acSia[MN_MMI_MAX_SIA_LEN + 1];
    VOS_CHAR                            acSib[MN_MMI_MAX_SIB_LEN + 1];
    VOS_CHAR                            acSic[MN_MMI_MAX_SIC_LEN + 1];
}MN_MMI_SC_SI_PARA_STRU;

typedef struct
{
    VOS_CHAR                            *pcMmiSc;                               /* MMI value of SC */
    VOS_UINT8                           ucNetSc;                                /* Network SC */
    VOS_UINT8                           aucRsv[3];
} MN_MMI_SC_TABLE_STRU;


typedef struct
{
    VOS_CHAR                            *pcMmiBs;                               /* MMI value of BS */
    VOS_UINT8                           ucNetBsCode;                            /* Network Basic Service Code */
    VOS_UINT8                           ucNetBsType;                            /* Network Basic Service Type */
    VOS_UINT8                           aucRsv[2];
} MN_MMI_BS_TABLE_STRU;

typedef struct
{
    VOS_CHAR                            *pcMmiChldStr;
    MN_CALL_SUPS_CMD_ENUM_U8            enChldOpType;
    VOS_UINT8                           aucRsv[3];
}MN_MMI_CHLD_OP_Tbl_STRU;

typedef struct
{
    VOS_CHAR                            *pcSsOpStr;
    MN_MMI_OPERATION_TYPE_ENUM_U8       enSsOpType;
    VOS_UINT8                           aucRsv[3];
}MN_MMI_SS_OP_Tbl_STRU;
/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */


typedef struct
{
    MN_MMI_OPERATION_TYPE_ENUM_U8       MmiOperationType;                       /*��ǰ�Ĳ�������*/

    TAF_UINT8                           aReserved[2];

    MN_CALL_ORIG_PARAM_STRU             MnCallOrig;
    MN_CALL_SUPS_PARAM_STRU             MnCallSupsReq;
    TAF_SS_REGISTERSS_REQ_STRU          RegisterSsReq;
    TAF_SS_ERASESS_REQ_STRU             EraseSsReq;
    TAF_SS_ACTIVATESS_REQ_STRU          ActivateSsReq;
    TAF_SS_DEACTIVATESS_REQ_STRU        DeactivateSsReq;
    TAF_SS_INTERROGATESS_REQ_STRU       InterrogateSsReq;
    TAF_SS_REGPWD_REQ_STRU              RegPwdReq;
    TAF_SS_GETPWD_RSP_STRU              GetPwdReq;
    TAF_SS_PROCESS_USS_REQ_STRU         ProcessUssdReq;
    TAF_PH_PIN_DATA_STRU                PinReq;
    MN_CALL_CLIR_CFG_ENUM_U8            enClir;
    TAF_SS_ERASECC_ENTRY_REQ_STRU       stCcbsEraseReq;

}MN_MMI_OPERATION_PARAM_STRU;

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  6 �ӿں�������
*****************************************************************************/

TAF_UINT32 MN_MmiStringParse(
    TAF_CHAR                            *pInMmiStr,
    TAF_BOOL                            inCall,
    MN_MMI_OPERATION_PARAM_STRU         *pMmiOpParam,
    TAF_CHAR                            **ppOutRestMmiStr
);


extern MN_CALL_CLIR_CFG_ENUM_U8  f_enClirOperate;

/* Added by f62575 for SS FDN&Call Control, 2013-05-06, begin */

VOS_UINT32 MMI_GetOporationTypeTblSize(VOS_VOID);


MN_MMI_SS_OP_Tbl_STRU *MMI_GetOporationTypeTblAddr(VOS_VOID);


VOS_UINT32 MMI_GetBSTblSize(VOS_VOID);


MN_MMI_BS_TABLE_STRU *MMI_GetBSTblAddr(VOS_VOID);


VOS_UINT32 MMI_GetSCTblSize(VOS_VOID);


MN_MMI_SC_TABLE_STRU *MMI_GetSCTblAddr(VOS_VOID);
/* Added by f62575 for SS FDN&Call Control, 2013-05-06, end */

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

#endif /* __TAF_MMI_STR_PARSE_H___ */

