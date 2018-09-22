

#ifndef __ATDIPCINTERFACE_H__
#define __ATDIPCINTERFACE_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  1 ��Ϣͷ����
*****************************************************************************/

enum AT_DIPC_MSG_TYPE_ENUM
{
    ID_AT_DIPC_PDP_ACT_IND  = 0x00, /* _H2ASN_MsgChoice AT_DIPC_PDP_ACT_STRU*/   /*AT��DIPCģ��ָʾPDP�Ѽ����ԭ��ID*/
    ID_AT_DIPC_PDP_REL_IND  = 0x01, /* _H2ASN_MsgChoice AT_DIPC_PDP_DEACT_STRU*/ /*AT��DIPCģ��ָʾPDP�ѶϿ���ԭ��ID*/

    ID_AT_DIPC_MSG_TYPE_BUTT
};
typedef VOS_UINT32 AT_DIPC_MSG_TYPE_ENUM_UINT32;


enum DIPC_BEARER_TYPE_ENUM
{
    DIPC_BEARER_TYPE_IPV4               = 0x01,
    DIPC_BEARER_TYPE_IPV6               = 0x02,
    DIPC_BEARER_TYPE_IPV4V6             = 0x03,

    DIPC_BEARER_TYPE_BUTT               = 0xFF
};
typedef VOS_UINT8 DIPC_BEARER_TYPE_ENUM_UINT8;

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MIN_RAB_ID              5
#define MAX_RAB_ID              15


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                          /*_H2ASN_Skip*/
    AT_DIPC_MSG_TYPE_ENUM_UINT32        enMsgType;                          /*_H2ASN_Skip*/
    VOS_UINT8                           ucRabId;                            /* RAB��ʶ��ȡֵ��Χ:[5,15] */
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType;
    VOS_UINT8                           aucRsv[2];
    UDI_DEVICE_ID                       enUdiDevId;                         /* �豸ID����д��ΧΪUDI_ACM_HSIC_ACM1_ID��UDI_ACM_HSIC_ACM3_ID��UDI_ACM_HSIC_ACM5_ID */
} AT_DIPC_PDP_ACT_STRU;


typedef struct
{
    VOS_MSG_HEADER                                                          /*_H2ASN_Skip*/
    AT_DIPC_MSG_TYPE_ENUM_UINT32        enMsgType;                          /*_H2ASN_Skip*/
    VOS_UINT8                           ucRabId;                            /* RAB��ʶ��ȡֵ��Χ:[5,15] */
    DIPC_BEARER_TYPE_ENUM_UINT8         enBearerType;
    VOS_UINT8                           aucRsv[2];
} AT_DIPC_PDP_DEACT_STRU;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    AT_DIPC_MSG_TYPE_ENUM_UINT32        enMsgId;            /* _H2ASN_MsgChoice_Export AT_DIPC_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_DIPC_MSG_TYPE_ENUM_UINT32
    ****************************************************************************/
} AT_DIPC_INTERFACE_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    AT_DIPC_INTERFACE_MSG_DATA          stMsgData;
} AtDipcInterface_MSG;

/*****************************************************************************
  10 ��������
*****************************************************************************/


UDI_HANDLE  DIPC_GetDevHandleByRabId(VOS_UINT8 ucRabId);


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

#endif



