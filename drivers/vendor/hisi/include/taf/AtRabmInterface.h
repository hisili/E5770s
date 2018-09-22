
#ifndef __AT_RABM_INTERFACE_H__
#define __AT_RABM_INTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafTypeDef.h"
#include  "PsTypeDef.h"
#include "NasNvInterface.h"

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

enum AT_RABM_MSG_ID_ENUM
{
    ID_AT_RABM_SET_FASTDORM_PARA_REQ = 0 ,                                           /* _H2ASN_MsgChoice AT_RABM_SET_FASTDORM_PARA_REQ_STRU */
    ID_AT_RABM_QRY_FASTDORM_PARA_REQ = 1 ,                                           /* _H2ASN_MsgChoice AT_RABM_QRY_FASTDORM_PARA_REQ_STRU */


    ID_RABM_AT_SET_FASTDORM_PARA_CNF = 2 ,                                           /* _H2ASN_MsgChoice RABM_AT_SET_FASTDORM_PARA_CNF_STRU */
    ID_RABM_AT_QRY_FASTDORM_PARA_CNF = 3 ,                                           /* _H2ASN_MsgChoice RABM_AT_QRY_FASTDORM_PARA_CNF_STRU */

    ID_AT_RABM_SET_RELEASE_RRC_REQ   = 4 ,                                           /* _H2ASN_MsgChoice AT_RABM_RELEASE_RRC_REQ_STRU */
    ID_RABM_AT_SET_RELEASE_RRC_CNF   = 5 ,                                           /* _H2ASN_MsgChoice RABM_AT_RELEASE_RRC_CNF_STRU */

    ID_RABM_AT_MSG_ID_ENUM_BUTT

};
typedef VOS_UINT32 AT_RABM_MSG_ID_ENUM_UINT32;


enum    AT_RABM_PARA_SET_RSLT_ENUM
{
    AT_RABM_PARA_SET_RSLT_SUCC         = 0,                                     /* �������óɹ� */
    AT_RABM_PARA_SET_RSLT_FAIL,                                                 /* ��������ʧ�� */
    AT_RABM_PARA_SET_RSLT_BUTT
};
typedef VOS_UINT32 AT_RABM_PARA_SET_RSLT_ENUM_UINT32;



enum AT_RABM_FASTDORM_OPERATION_ENUM
{
    AT_RABM_FASTDORM_STOP_FD_ASCR,                                              /* ֹͣFD��ASCR */
    AT_RABM_FASTDORM_START_FD_ONLY,                                             /* ������FD */
    AT_RABM_FASTDORM_START_ASCR_ONLY,                                           /* ������ASCR */
    AT_RABM_FASTDORM_START_FD_ASCR,                                             /* ����FD��ASCR */
    AT_RABM_FASTDORM_START_BUTT
};
typedef VOS_UINT32 AT_RABM_FASTDORM_OPERATION_ENUM_UINT32;


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
    AT_RABM_FASTDORM_OPERATION_ENUM_UINT32      enFastDormOperationType;        /* �������� */
    VOS_UINT32                                  ulTimeLen;                      /* ������ʱ�� */
}AT_RABM_FASTDORM_PARA_STRU;




typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MN_CLIENT_ID_T                      usClientId;                             /* AT����Ϣ��RABM������ClientId */
    MN_OPERATION_ID_T                   ucOpId;                                 /* AT����Ϣ��RABM������OpId */
    VOS_UINT8                           aucReserve1[1];                         /* ���� */
    AT_RABM_FASTDORM_PARA_STRU          stFastDormPara;                         /* FAST DORMANCY������صĲ��� */
}AT_RABM_SET_FASTDORM_PARA_REQ_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MN_CLIENT_ID_T                      usClientId;                             /* AT����Ϣ��RABM������ClientId */
    MN_OPERATION_ID_T                   ucOpId;                                 /* AT����Ϣ��RABM������OpId */
    VOS_UINT8                           aucReserve1[1];                         /* ���� */
}AT_RABM_QRY_FASTDORM_PARA_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;                             /* AT����Ϣ��RABM������ClientId */
    VOS_UINT8                           ucOpId;                                 /* AT����Ϣ��RABM������OpId */
    VOS_UINT8                           aucReserve1[1];                         /* ���� */
}AT_RABM_RELEASE_RRC_REQ_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    VOS_UINT16                          usClientId;                             /* AT����Ϣ��RABM������ClientId */
    VOS_UINT8                           ucOpId;                                 /* AT����Ϣ��RABM������OpId */
    VOS_UINT8                           aucReserve1[1];                         /* ���� */
    VOS_UINT32                          ulRslt;                                 /* ���ý�� */
}RABM_AT_RELEASE_RRC_CNF_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MN_CLIENT_ID_T                      usClientId;                             /* AT����Ϣ��RABM������ClientId */
    MN_OPERATION_ID_T                   ucOpId;                                 /* AT����Ϣ��RABM������OpId */
    VOS_UINT8                           aucReserve1[1];                         /* ���� */
    AT_RABM_PARA_SET_RSLT_ENUM_UINT32   enRslt;                                 /* ���ý�� */
}RABM_AT_SET_FASTDORM_PARA_CNF_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /* ��Ϣͷ */ /*_H2ASN_Skip*/
    MN_CLIENT_ID_T                      usClientId;                             /* AT����Ϣ��RABM������ClientId */
    MN_OPERATION_ID_T                   ucOpId;                                 /* AT����Ϣ��RABM������OpId */
    /* Added by l60609 for B070 Project, 2012/03/20, begin */
    VOS_UINT8                           ucRslt;                                 /* ��� */
    /* Added by l60609 for B070 Project, 2012/03/20, end */
    AT_RABM_FASTDORM_PARA_STRU          stFastDormPara;                         /* ��ѯ���صĵ�ǰ���� */
}RABM_AT_QRY_FASTDORM_PARA_CNF_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    AT_RABM_MSG_ID_ENUM_UINT32          enMsgID;    /*_H2ASN_MsgChoice_Export AT_RABM_MSG_ID_ENUM_UINT32 */
                                                    /* Ϊ�˼���NAS����Ϣͷ���壬����ת��ASN.AT_RABM_MSG_ID_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_RABM_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}AT_RABM_SND_INTERNAL_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    AT_RABM_SND_INTERNAL_DATA                    stMsgData;
}AtRabmInterfacemsg_MSG;



/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


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

#endif /* end of NasMmcSuspendProcAct.h */

