/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafAppRabm.h
******************************************************************************/

#ifndef __TAF_APP_RABM_H__
#define __TAF_APP_RABM_H__


#include "TafTypeDef.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#pragma pack(4)

/*�����ӿں궨��*/
#define TAF_DATA_CS_DOMAIN                   0    /*CS��*/
#define TAF_DATA_PS_DOMAIN                   1    /*PS��*/

#define TAF_RABM_STOP_DATA                   0    /*ָʾAPPֹͣ��������*/
#define TAF_RABM_START_DATA                  1    /*ָʾAPP��ʼ��������*/
#define TAF_DATA_STOP                        2    /*�޷�������������ֹͣ����*/
#define TAF_DATA_START                       3    /*��������(δ��)*/

/*ָʾAPPֹͣ�������ݵ�ԭ��ֵ*/
#define TAF_RABM_STOP_CAUSE_NORMAL                        0xff      /*ֹͣ����*/

/*ָʾAPP��ʼ�������ݵ�ԭ��ֵ*/
#define TAF_RABM_START_CAUSE_REEST_FAILURE                0         /*���ؽ�RABʧ�ܿ�ʼ��������*/
#define TAF_RABM_START_CAUSE_REEST_SUCCESS                1         /*���ؽ�RAB�ɹ���ʼ��������*/
#define TAF_RABM_START_CAUSE_RRC_INDICATION               2         /*��RRCָʾ��ʼ��������*/
#define TAF_RABM_START_CAUSE_2G_TO_3G_CUR_2G              3         /*2Gģʽ����3Gģʽ����ǰ����Ϊ2G(V200R001�汾����)*/
#define TAF_RABM_START_CAUSE_2G_TO_3G_CUR_3G              4         /*2Gģʽ����3Gģʽ����ǰ����Ϊ3G(V200R001�汾����)*/
#define TAR_RABM_START_CAUSE_3G_TO_2G_CUR_3G              5         /*3Gģʽ����2Gģʽ����ǰ����Ϊ3G(V200R001�汾����)*/
#define TAF_RABM_START_CAUSE_3G_TO_2G_RA_UPDATE_FINISH    6         /*3G��2G�л��е�·�����������̽���(V200R001�汾����)*/

/*�޷�����������ԭ��ֵ*/
#define TAF_DATA_CAUSE_REEST_FAILURE         0    /*�û�������ؽ�ʧ��*/
#define TAF_DATA_CAUSE_REEST_SUCCESS         1    /*�û�������ؽ��ɹ�*/
#define TAF_DATA_CAUSE_LOWLAYER_INDICATION   2    /*�û���ײ�ԭ��*/
#define TAF_DATA_CAUSE_NO_TRANSMODE          3    /*��ʱ��NSAPIδ����TRANSMODE(V200R001�汾����)*/
#define TAF_DATA_CAUSE_3G_TO_2G_RA_UPDATE    4    /*���ڽ���3G��2G�л��е�·��������(V200R001�汾����)*/

/*�����궨��:*/
#define   TAF_RABM_MAX_ENT_NUM               11


/*---------------------------------------------------------
             Structs used for DS Flow Report.
---------------------------------------------------------*/
typedef struct
{
    /*0 - The Rabid is not actived.
      1 - The Rabid is activated */
    TAF_UINT8       ucFlag;

    TAF_UINT32      ulUplinkByteRate;     /*������Э�̵ķ������ݵ�����(�ֽ�/��)*/
    TAF_UINT32      ulDownlinkByteRate;   /*������Э�̵Ľ������ݵ�����(�ֽ�/��)*/
}TAF_DS_FLOW_ONE_RATE_STRU;



VOS_VOID Taf_DataReq ( VOS_UINT16    ClientId,
                       VOS_UINT8        ucDomain,
                       VOS_UINT8        ucRabId,
                       VOS_UINT16       usDataLen,
                       VOS_UINT8       *pData);

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

#endif /* end of TafAppRabm.h */
