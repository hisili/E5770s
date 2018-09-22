

#ifndef __TTF_MEMCTRL_H__
#define __TTF_MEMCTRL_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TtfMemoryMap.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* TTF�ڴ����ͳ�ʼ����� */
#define TTF_MEMCTRL_TYPE_INIT_FLG                       (1)

/* TTF�ڴ����ʹ��ڲ����ڱ�� */
#define TTF_MEMCTRL_TYPE_EXIST_FLG                      (1)

/* TTF�ڴ����Ϳɼ����ɼ���� */
#define TTF_MEMCTRL_TYPE_VISIBLE_FLG                    (1<<1)

#define TTF_MEMCTRL_INVAILD_SIZE                        (0xFFFFFFFF)

#define TTF_MEMCTRL_SET_ADDR_INIT_FLG(flg)              (g_stTtfMemCtrlAddr.stTtfMemCtrlAddrComm.ucInitFlg = flg)

#define TTF_MEMCTRL_GET_ADDR_INIT_FLG()                 (g_stTtfMemCtrlAddr.stTtfMemCtrlAddrComm.ucInitFlg)

#define TTF_MEMCTRL_SET_TYPE_FLG(type, flg)             (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulAttribute |= flg)

#define TTF_MEMCTRL_GET_TYPE_ATTRIBUTE(type)            (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulAttribute)

#define TTF_MEMCTRL_SET_TYPE_LEN(type, len)             (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulLen = len)

#define TTF_MEMCTRL_GET_TYPE_LEN(type)                  (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulLen)

#define TTF_MEMCTRL_SET_TYPE_OFFSET_BASE_LEN(type, len) (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulOffsetBaseLen = len)

#define TTF_MEMCTRL_GET_TYPE_OFFSET_BASE_LEN(type)      (g_stTtfMemCtrlAddr.astTtfMemCtrlAddrType[type].ulOffsetBaseLen)

/*****************************************************************************
  3 ö�ٶ���
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
/*****************************************************************************
�ṹ��    : TTF_MEMCTRL_ADDR_COMM_STRU
Э����  : ��
ASN.1���� : ��
�ṹ˵��  : TTF�ڴ��ַ�����ṹ
*****************************************************************************/
typedef struct
{
    unsigned char                       ucInitFlg;          /* ��ʼ����� */
    unsigned char                       ucRcv[3];           /* ����λ */
} TTF_MEMCTRL_ADDR_COMM_STRU;


/*****************************************************************************
�ṹ��    : TTF_MEMCTRL_ADDR_TYPE_STRU
Э����  : ��
ASN.1���� : ��
�ṹ˵��  : TTF�ڴ��ַ���ͽṹ
*****************************************************************************/
typedef struct
{
    unsigned long                       ulAttribute;        /* TTF�ڴ��ַ�������� */
    unsigned long                       ulLen;              /* TTF�ڴ��ַ����ռ�õĳ��� */
    unsigned long                       ulOffsetBaseLen;    /* TTF�ڴ��ַ���ͻ��ڻ���ַƫ�Ƶĳ��� */
} TTF_MEMCTRL_ADDR_TYPE_STRU;


/*****************************************************************************
�ṹ��    : TTF_MEMCTRL_ADDR_TYPE_STRU
Э����  : ��
ASN.1���� : ��
�ṹ˵��  : TTF�ڴ��ַ���ͽṹ
*****************************************************************************/
typedef struct
{
    TTF_MEMCTRL_ADDR_COMM_STRU          stTtfMemCtrlAddrComm;
    TTF_MEMCTRL_ADDR_TYPE_STRU          astTtfMemCtrlAddrType[TTF_MEMCTRL_ADDR_TYPE_BUTT];
} TTF_MEMCTRL_ADDR_STRU;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 OTHERS����
*****************************************************************************/



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/



#pragma pack(0)

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of Fc.h */


