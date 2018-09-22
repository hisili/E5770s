/*******************************************************************************
  Copyright   : 2005-2010, Huawei Tech. Co., Ltd.
  File name   : NetWInterface.h
  Version     : V300R002
  Date        : 2011-11-23
  Description :
  History     :
  1. Date:2011-11-23
     Author: caikai
     Modification:Create
*******************************************************************************/

#ifndef _NETWINTERFACE_H_
#define _NETWINTERFACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#if !defined(__UT_CENTER__) && !defined(_lint)
#include<linux/types.h>
#else
#include "linuxstub.h"
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*================================================*/
/* ��ֵ�궨�� */
/*================================================*/
#define NW_INQUIRE_IFCONFIG_ON_MASK      (1)        /*��ѯIfconfig����*/
#define NW_INQUIRE_ARP_ON_MASK           (1 << 1)   /*��ѯArp����*/
#define NW_INQUIRE_ROUTE_ON_MASK         (1 << 2)   /*��ѯRoute����*/
#define NW_INQUIRE_NETSTATE_ON_MASK      (1 << 3)   /*��ѯNetstate����*/
#define NW_INQUIRE_NAT_ON_MASK           (1 << 4)   /*��ѯNat����*/

#define NW_INQUIRE_CFG_ALL_MASK          ( NW_INQUIRE_IFCONFIG_ON_MASK \
                                            | NW_INQUIRE_ARP_ON_MASK \
                                            | NW_INQUIRE_ROUTE_ON_MASK \
                                            | NW_INQUIRE_NETSTATE_ON_MASK \
                                            | NW_INQUIRE_NAT_ON_MASK)

#define DEVICE_NAME                      "NetfilterExtDev"     /*�ַ��豸��*/
#define CLASS_NAME                       "NetfilterExtClass"
#define DEV_BUFF_LEN                     (sizeof(NETWORK_INQUIRE_CONFIG_STRU))
#define DEVICE_PATH_LEN                  (100)                 /*�豸����·���ĳ���*/
#define DEVICE_NUM                       (1)                   /*ע���ַ��豸����Ŀ*/
#define MINOR_NO_START                   (500)                 /*���豸����ʼ��*/


/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*****************************************************************************
  4 �ṹ����
*****************************************************************************/
/*********************************************
 �ṹ����   :NETWORK_INQUIRE_CONFIG_STRU
 Э���� :
 �ṹ��˵�� :network inquire������Ϣ
*********************************************/
typedef struct
{
    unsigned long ulOnOffMask;                  /* ���ܿ������� */
    unsigned long ulTimerLen;                   /* �ϱ����ڶ�ʱ������ */
}NETWORK_INQUIRE_CONFIG_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

