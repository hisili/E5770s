#ifndef __PCSC_PROC_H__
#define __PCSC_PROC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "vos.h"
#include "pslog.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define PS_USIM_GET_STATUS_IND                  27
#define SI_PIH_PCSC_DATA_CNF                    0xA5

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
enum USIMM_CARD_TYPE_ENUM
{
    USIMM_CARD_SIM           = 0,
    USIMM_CARD_USIM          = 1,
    USIMM_CARD_ROM_SIM       = 2,
    USIMM_CARD_ISIM          = 3,             /*ISIM��*/
    USIMM_CARD_NOCARD        = 255,
    USIMM_CARD_TYPE_BUTT
};
typedef VOS_UINT32      USIMM_CARD_TYPE_ENUM_UINT32;

enum USIMM_CARD_SERVIC_ENUM
{
    USIMM_CARD_SERVIC_ABSENT        =0,     /* �޿� */
    USIMM_CARD_SERVIC_UNAVAILABLE   =1,  /* �п�,���񲻿��� */
    USIMM_CARD_SERVIC_SIM_PIN       =2,    /* SIM����������PIN��ԭ�򲻿��� */
    USIMM_CARD_SERVIC_SIM_PUK       =3,    /* SIM����������PUK��ԭ�򲻿��� */
    USIMM_CARD_SERVIC_NET_LCOK      =4,   /* SIM������������������ԭ�򲻿��� */
    USIMM_CARD_SERVIC_IMSI_LCOK     =5,   /* SIM����������IMSI����ԭ�򲻿��� */
    USIMM_CARD_SERVIC_AVAILABLE     =6,   /* ������� */
    USIMM_CARD_SERVIC_BUTT
};
typedef VOS_UINT32      USIMM_CARD_SERVIC_ENUM_UINT32;

enum SI_PIH_EVENT_ENUM
{
    SI_PIH_EVENT_PIN_OPER_CNF       = 1,      /* ����PIN�뷵�ؽ��        */
    SI_PIH_EVENT_PIN_QUERY_CNF      = 2,      /* ��ѯPIN�뷵�ؽ��        */
    SI_PIH_EVENT_PIN_INFO_IND       = 3,      /* ����PIN�������ϱ�        */
    SI_PIH_EVENT_SIM_INFO_IND       = 4,      /* SIM����Ϣ�ϱ�            */
    SI_PIH_EVENT_GENERIC_ACCESS_CNF = 5,      /* +CSIM �ظ�               */
    SI_PIH_EVENT_RESTRIC_ACCESS_CNF = 6,      /* +CRSM �ظ�               */
    SI_PIH_EVENT_FDN_CNF            = 7,      /* FDN�ظ�                  */
    SI_PIH_EVENT_BDN_CNF            = 8,      /* BDN�ظ�                  */
    SI_PIH_EVENT_PERO_LOCK_CNF      = 9,      /* �����ظ�                 */
    SI_PIH_EVENT_BUTT
};
typedef VOS_UINT32  SI_PIH_EVENT;

enum SI_PIH_REQ_ENUM
{
    SI_PIH_NULL_REQ                 = 0,
    SI_PIH_FDN_ENABLE_REQ           = 1,
    SI_PIH_FDN_DISALBE_REQ          = 2,
    SI_PIH_GACCESS_REQ              = 3,
    SI_PIH_BDN_QUERY_REQ            = 4,
    SI_PIH_FDN_QUERY_REQ            = 5,
    SI_PIH_PCSC_DATA_REQ            = 6,
    SI_PIH_REQ_BUTT
};
typedef VOS_UINT32      SI_PIH_REQ_ENUM_UINT32;


/*****************************************************************************
  4 STRUCT����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;       /* ��Ϣ�� */
    VOS_UINT16                          usClient;        /* �ͻ���ID */
    VOS_UINT8                           ucOpID;
    VOS_UINT8                           ucRsv;
    SI_PIH_EVENT                        ulEventType;
}SI_PIH_MSG_HEADER_STRU;

typedef struct
{
    SI_PIH_MSG_HEADER_STRU          stMsgHeader;
    VOS_UINT16                      ulMsgType;
    VOS_UINT32                      ulCmdType;
    VOS_UINT32                      ulCmdLen;
    VOS_UINT8                       aucAPDU[8];
}SI_PIH_PCSC_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgName;
    USIMM_CARD_TYPE_ENUM_UINT32     enCardType;     /* ������:SIM��USIM��ROM-SIM  */
    USIMM_CARD_SERVIC_ENUM_UINT32   enCardStatus;   /* ��״̬*/
    VOS_UINT8                       aucIMSI[9];     /* IMSI��*/
    VOS_UINT8                       ucIMSILen;      /* IMSI���� */
    VOS_UINT8                       ucReason;       /* �ϱ�ԭ��*/
    VOS_UINT8                       ucRsv;
}PS_USIM_STATUS_IND_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                      ulMsgName;          /* ��Ϣ���� */
    VOS_UINT32                      ulResult;           /* PC/SC����ִ�н�� */
    VOS_UINT32                      ulCmdType;          /* �������� */
    VOS_UINT32                      ulRspLen;           /* ����ִ�еõ������ݳ��� */
    VOS_UINT8                       aucContent[4];      /* �������� */
}SI_PIH_PCSC_CNF_STRU;




#ifdef __cplusplus
#if __cplusplus
        }
#endif
#endif

#endif
