

#ifndef _OM_APP_AGENT_H_
#define _OM_APP_AGENT_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define WAITING_CNF_TIMEOUT_LEN          (5000)

/* ACPU��CCPU���͵�������Ϣ��������Ҫ�ȴ���ظ�����λ�ֽ�Ϊ0*/
#define ERRORLOG_REQ                (0x0007)
#define ERRORLOG_CNF                (0x0008)
#define OM_AUTOCONFIG_REQ           (0x0009)
#define OM_AUTOCONFIG_CNF           (0x000A)
#define OM_WRITE_LOG_REQ            (0x000C)


/* CCPU��ACPU���͵�������Ϣ������Ҫ�ȴ��ظ�����λ�ֽ�Ϊ3 */
#define OM_OLED_CLEAR_REQ           (0x0301)
#define OM_OLED_DISPLAY_REQ         (0x0303)
#define OM_LINK_STATUS_REQ          (0x0305)
#define OM_HSIC_CONNECT_REQ         (0x0307)
#define OM_RECORD_DBU_INFO_REQ      (0x0309)
#define OM_SET_FTM_MODE_REQ         (0x030a)

#define IS_CAGENT_CNF_MSG(usPrimId) (0 == (usPrimId >> 8))

#define ERRORLOG_HEAD_LEN           (52)

#define OM_LOG_FILE_MAX_SIZE        (0x40000)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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
    VOS_MSG_HEADER
    VOS_UINT16  usPrimId;           /* ָʾ��ǰΪErrorLog������� */
    VOS_UINT8   aucReserved[2];
    VOS_UINT8   aucFileName[32];    /* ����ErrorLog API�����ļ��� */
    VOS_UINT32  ulFileId;           /* ����ErrorLog API�����ļ����ļ�ID */
    VOS_UINT32  ulLine;             /* ����ErrorLog API�����ļ����к� */
    VOS_UINT32  ulErrNo;            /* ErrorLog�Ĵ���� */
    VOS_UINT32  ulLen;              /* ErrorLog��������ݵĳ��� */
    VOS_UINT8   aucData[4];         /* ErrorLog��������ݣ����ݳ��ȸ���ulLenֵȷ�� */
}ERRORLOG_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16 usPrimId;            /* ָʾ��ǰΪErrorLog���������� */
    VOS_UINT16 usResult;           /* VOS_OKΪ�ɹ���VOS_ERRΪʧ�� */
}ERRORLOG_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16  usPrimId;           /* ָʾ��ǰ����Ϣ���� */
    VOS_UINT8   aucReserved[2];
}OM_AUTOCONFIG_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16  usPrimId;           /* ָʾ��ǰ����Ϣ���� */
    VOS_UINT8   aucData[2];
}OM_AUTOCONFIG_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16 usPrimId;            /* ��ϢID */
    VOS_UINT16 usReserve;           /* ���� */
}OM_OLED_CLEAR_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16 usPrimId;            /* ��ϢID */
    VOS_UINT16 usReserve;           /* ���� */
    VOS_UINT16 usXPos;
    VOS_UINT16 usYPos;
}OM_OLED_DISPLAY_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16  usPrimId;           /* ָʾ��ǰΪErrorLog������� */
    VOS_UINT8   aucFileName[32];    /* Log�ļ��� */
    VOS_UINT32  ulLen;              /* Log���ݵĳ��� */
    VOS_UINT8   aucData[4];         /* Log�����ݣ����ݳ��ȸ���ulLenֵȷ�� */
}OM_WRITELOG_REQ_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16 usPrimId;            /* ��ϢID */
    VOS_UINT16 usReserve;           /* ���� */
}OM_HSIC_CONNECT_REQ_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

