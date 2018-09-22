

#ifndef __RFA_H__
#define __RFA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "NVIM_Interface.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ��Ʒ��������֧�ֵ�BAND��Ŀ*/
#define RFA_UE_SUPPORT_MAX_BAND_NUM         32

#define RFA_CPHY_SUPPORT_BANDS              0x405BF

#define ID_MMA_RFA_START_MODE_REQ           0x0005
#define ID_MMA_RFA_STOP_MODE_REQ            0x0006

/*APT��NV���ʼ��ֵ*/
#define APT_NV_DATA_INIT                    0

/*һ��APT���Ӧ��NV�������16����*/
#define APT_NV_DATA_MAX_NUM                 16

/*һ��APT���Ӧ��NV����С����*/
#define APT_NV_DATA_MIN_NUM                 0

/*ÿ��APT����128��Ԫ��*/
#define RFA_APT_ITEM_SIZE                   128

/*����������ҪAPT����*/
#define RFA_APT_GAIN_TABLE_NUM              4

/*������APT��Ļ�ַ*/
#define RFA_APT_Table_HIGH_GAIN_Base_P0     700

/*������APT��Ļ�ַ*/
#define RFA_APT_Table_MID_GAIN_Base_P0      700

/*������APT��Ļ�ַ*/
#define RFA_APT_Table_LOW_GAIN_Base_P0      700

/*ÿ��CQI��ĳ���*/
#define RFA_CQI_TABLE_LENGTH                2160

/*CQI����ܳ���*/
#define RFA_CQI_TOTAL_LENGTH                (13*1024)

/*APT����ܳ���*/
#define RFA_APT_TOTAL_LENGTH                (33*1024)

/*ET����ܳ���,��ʱ���壬����������ȷ��*/
#define RFA_ET_TOTAL_LENGTH                 (11*1024)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum APT_GAIN_MODE_ENUM
{
    APT_GAIN_MODE_HIGH = 0,
    APT_GAIN_MODE_MIDDLE,
    APT_GAIN_MODE_LOW,
    APT_GAIN_MODE_BUTT
};
typedef VOS_UINT32 APT_GAIN_MODE_ENUM_U32;

/*���������ͬһNV���APT�����ƫ��*/
#define RFA_APT_GAIN_OFFSET                 (RFA_APT_ITEM_SIZE * APT_GAIN_MODE_BUTT)

/*ÿ�� Band��APT���ܳ���*/
#define RFA_APT_BAND_SIZE                   (RFA_APT_GAIN_OFFSET * RFA_APT_GAIN_TABLE_NUM)

enum RFA_EEIC_MODE_ENUM
{
    RFA_EEIC_MODE_DISABLE = 0,
    RFA_EEIC_MODE_ENABLE,
    RFA_EEIC_MODE_BUTT
};
typedef VOS_UINT16 RFA_EEIC_MODE_ENUM_U16;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern VOS_UINT32 g_ulUeWcdmaBands;

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32    ulCmdType;        /* ��Ϣ����*/
}MMA_RFA_MODE_MSG;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulCount;                             /*Data Number*/
    VOS_INT16                   asNvItem[APT_NV_DATA_MAX_NUM][2];    /*16 sets of Data*/
}RFA_APT_NV_VBIAS_STRU;

typedef struct
{
    VOS_UINT32                  ulCount;                              /*Data Number*/
    VOS_INT16                   asNvPower[APT_NV_DATA_MAX_NUM];       /*Power*/
    VOS_UINT16                  ausNvVolt[APT_NV_DATA_MAX_NUM+1];     /*Vbias, +1Ϊ�˽���ٽ����,���ٽ�������*/
    VOS_INT16                   asNvCompHC[APT_NV_DATA_MAX_NUM+1];    /*High Channel Compensation*/
    VOS_INT16                   asNvCompMC[APT_NV_DATA_MAX_NUM+1];    /*Middle Channel Compensation*/
    VOS_INT16                   asNvCompLC[APT_NV_DATA_MAX_NUM+1];    /*Low Channel Compensation*/

}RFA_APT_NV_DATA_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_UINT32 RFA_MsgProc(MsgBlock *pMsg);
extern VOS_UINT32 WuepsRfaPidInit ( enum VOS_INIT_PHASE_DEFINE ip );

extern VOS_UINT32 RFA_GetFixMemInfo(VOS_UINT32 ulMemType, VOS_UINT32 ulMemSize, VOS_UINT32 *pulMemAddr);

VOS_UINT32 RFA_CQITableProc(VOS_VOID);


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

#endif /* end of RFA.h */
