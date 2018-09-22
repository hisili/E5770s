
#ifndef  TAF_CLIENT_API_H
#define  TAF_CLIENT_API_H


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/
typedef VOS_UINT8 MN_CALLBACK_TYPE_T;   /* Type of callback functions for event reporting*/
#define MN_CALLBACK_CS_CALL             0 /* CS call */
#define MN_CALLBACK_PS_CALL             1 /* PS call */
#define MN_CALLBACK_MSG                 2 /* Short message service */
#define MN_CALLBACK_SS                  3 /* Call independent supplemental service */
#define MN_CALLBACK_PHONE               4 /* Phone management and network register service */
#define MN_CALLBACK_DATA_IND            5 /* User plane data indication */
#define MN_CALLBACK_DATA_STATUS         6 /* User plane data status */
#define MN_CALLBACK_DATA_FLOW           7 /* User plane data flow */
#define MN_CALLBACK_SET                 8
#define MN_CALLBACK_QRY                 9
#define MN_CALLBACK_PHONE_BOOK          10 /* Phone book */
#define MN_CALLBACK_STK                 11
#define MN_CALLBACK_CMD_CNF             12 /* Cmd Cnf*/
#define MN_CALLBACK_CHANNEL_STATUS      13
#define MN_CALLBACK_PIH                 14
#define MN_CALLBACK_VOICE_CONTROL       15
#define MN_CALLBACK_LOG_PRINT           16
#define MN_CALLBACK_MAX                 17



#define  TAF_MAX_CLIENT_OF_ONE_PROC       OMA_CLIENT_ID_BUTT

#define TAF_FREE                        0   /*δʹ��*/
#define TAF_USED                        1   /*ʹ��*/



#define TAF_CALL_APP_MSG_BASE           (0x0000)                                /* AT��CALLģ�����Ϣ��ʼ */
#define TAF_MSG_APP_MSG_BASE            (0x1000)                                /* AT��MSGģ�����Ϣ��ʼ */
#define TAF_SSA_APP_MSG_BASE            (0x2000)                                /* AT��SSAģ�����Ϣ��ʼ */
#define TAF_MMA_APP_MSG_BASE            (0x3000)                                /* AT��MMAģ�����Ϣ��ʼ */
#define TAF_APP_SET_MSG_BASE            (0x5000)                                /* AT��MNģ���������Ϣ��ʼ */
#define TAF_APP_QRY_MSG_BASE            (0x6000)                                /* AT��MNģ����ѯ��Ϣ��ʼ */
#define TAF_APS_MSG_BASE                (0x7000)                                /* AT/IMSA��PS����ģ�����Ϣ��ʼ */
#define TAF_SPM_IMSA_MSG_BASE           (0x8000)                                /* IMSA��SPMģ�����Ϣ��ʼ */
#define TAF_MSG_IMSA_MSG_BASE           (0x9000)                                /* IMSA��MSGģ�����Ϣ��ʼ */
#define TAF_MMA_IMSA_MSG_BASE           (0xa000)                                /* IMSA��MMAģ�����Ϣ��ʼ */
#define TAF_CALL_IMSA_MSG_BASE          (0xb000)                                /* CALL��IMSA������Ϣ��ʼ */
#define TAF_IMSA_COMM_MSG_BASE          (0xc000)                                /* TAF��IMSA������Ϣ��ʼ */

#define TAF_IMSA_MSG_MASK               (0xf000)                                /* IMSA��TAF���MASK */

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/





/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* TAF_CLIENT_API_H */


