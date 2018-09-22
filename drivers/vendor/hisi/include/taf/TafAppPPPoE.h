/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : TafAppPPPoE.h
  Author      : L47619
  Version     : V200R001
  Date        : 2006-05-06
  Description : ��ͷ�ļ�������TAF�ṩ��APP��ʹ�õ����ݽṹ�ͺ����ӿ�

  History        :
  1. Date        : 2006-05-06
     Author      : L47619
     Modification: Create
  2. Date:2006-08-09
     Author: j60010247
     Modification:�������ⵥA32D03479����PC����ʵ��ʱ��#pragma pack(0)��#pragma pack()�ӱ��뿪��
************************************************************************/

#ifndef __TAF_APP_PPPOE_H__
#define __TAF_APP_PPPOE_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/******************APP-API�����������Ͷ��忪ʼ****************/
#ifndef __VOS_CHANGE_TO_TAF__
#define __VOS_CHANGE_TO_TAF__
#if 0
typedef signed   char       TAF_INT8;
typedef unsigned char       TAF_UINT8;

typedef signed   short      TAF_INT16;
typedef unsigned short      TAF_UINT16;

typedef signed   long       TAF_INT32;
typedef unsigned long       TAF_UINT32;

typedef char                TAF_CHAR;
typedef unsigned char       TAF_UCHAR;

typedef void                TAF_VOID;
#endif
#endif

/******************APP-API�����������Ͷ������****************/


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
typedef enum
{
    TAF_PPPOE_CID_DEFAULT,                             /*ʹ��Ĭ��CID*/
    TAF_PPPOE_CID_MANUAL_SELECT,                       /*�û�����ѡ��CID*/

    TAF_PPPOE_CID_BUTT
}TAF_PPPOE_CID_SELECT_MODE_ENUM;          /*ѡ��CID�ķ�ʽ*/

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


/*****************************************************************************
  8 UNION����
*****************************************************************************/




/*****************************************************************************
  9 �����ӿڶ���
*****************************************************************************/
/*****************************************************************************
 Prototype      : Taf_PPPoESetCid
 Description    : �ṩ���û��Ľӿڣ���������PPPoE��ʹ�õ�CID
 Input          : CidSelectMode      ѡ��CID�ķ�ʽ��TAF_PPPOE_CID_DEFAULT��ʽ�£��ڶ�������ucCid��������ֵ��
                  ucCid              �û���ָ����CID��ȡֵ[0,11],ֻ��TAF_PPPOE_CID_MANUAL_SELECT��ʽ��Ч
 Output         :
 Return Value   : TAF_SUCCESS        CID���óɹ�
                  TAF_FAILURE        CID����ʧ��
 Calls          :
 Called By      : APP

 History        :
  1.Date        : 2006-05-16
    Author      : L47619
    Modification: Created function
*****************************************************************************/
extern TAF_UINT32 Taf_PPPoESetCid(TAF_PPPOE_CID_SELECT_MODE_ENUM CidSelectMode, TAF_UINT8 ucCid);





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

#endif /* end of TafAppPPPoE.h*/
