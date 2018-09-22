

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#ifndef __PHYOAMINTERFACE_H__
#define __PHYOAMINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* ��SAR��ulMask���� */
#define UPHY_OAM_SAR_MASK_ANTSTATE          ( 0x1 )
#define UPHY_OAM_SAR_MASK_REDUCTION         ( 0x2 )

/* ��̬���ض���,ĿǰV9R1��û��ʵ�ʵļ��ض���,�������Ϊ1 */
#define UPHY_DYN_CODE_MODULE_BUTT           ( 0x01 )

/* ���뱣�ֺ�phytoolinterface.h��UPHY_TOOL_SLEEP_INFO_NUM�Ĵ�С����һ�� */
#define UPHY_OAM_SLEEP_INFO_NUM             ( 16 )

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
 ö����    :UPHY_OAM_MSG_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :PHY��OAMԭ���б�
*****************************************************************************/
enum UPHY_OAM_MSG_ID_ENUM
{
    /* OAM��UPHY_APM��ԭ�� */
    ID_OAM_UPHY_ACTIVE_UPHY_REQ             = 0xD200,                   /* _H2ASN_MsgChoice  UPHY_OAM_ACTIVE_UPHY_REQ_STRU */
    ID_UPHY_OAM_ACTIVE_UPHY_CNF             = 0x2D00,                   /* _H2ASN_MsgChoice  UPHY_OAM_ACTIVE_UPHY_CNF_STRU */

    ID_UPHY_OAM_LOAD_NV_REQ                 = 0x2D01,                   /* _H2ASN_MsgChoice  UPHY_OAM_LOAD_NV_REQ_STRU */
    ID_OAM_UPHY_LOAD_NV_CNF                 = 0xD201,                   /* _H2ASN_MsgChoice  UPHY_OAM_LOAD_NV_CNF_STRU */

    ID_OAM_UPHY_GET_NV_ADDR_REQ             = 0xD202,                   /* _H2ASN_MsgChoice  UPHY_OAM_GET_NV_ADDR_REQ_STRU */
    ID_UPHY_OAM_GET_NV_ADDR_IND             = 0x2D02,                   /* _H2ASN_MsgChoice  UPHY_OAM_GET_NV_ADDR_IND_STRU */

    ID_UPHY_OAM_BOOT_INFO_REQ               = 0x2D03,                   /* _H2ASN_MsgChoice  UPHY_OAM_BOOT_INFO_REQ_STRU */
    ID_OAM_UPHY_BOOT_INFO_IND               = 0xD203,                   /* _H2ASN_MsgChoice  UPHY_OAM_BOOT_INFO_IND_STRU */

    /* OAM��UPHY_DRX��ԭ�� */
    ID_OAM_UPHY_MASTER_WAKE_CMD             = 0xD220,                   /* _H2ASN_MsgChoice  UPHY_OAM_WAKE_CMD_STRU */
    ID_UPHY_OAM_MASTER_SLEEP_IND            = 0x2D20,                   /* _H2ASN_MsgChoice  UPHY_OAM_SLEEP_IND_STRU */

    ID_OAM_UPHY_SLAVE_WAKE_CMD              = 0xD221,                   /* _H2ASN_MsgChoice  UPHY_OAM_WAKE_CMD_STRU */
    ID_UPHY_OAM_SLAVE_SLEEP_IND             = 0x2D21,                   /* _H2ASN_MsgChoice  UPHY_OAM_SLEEP_IND_STRU */


    /* OAM��W/GPHY��ԭ��,���ݽ���PID���� */
    ID_OAM_PHY_LOAD_PHY_REQ                 = 0xD240,                   /* _H2ASN_MsgChoice  PHY_OAM_LOAD_PHY_REQ_STRU */
    ID_PHY_OAM_LOAD_PHY_CNF                 = 0x2D40,                   /* _H2ASN_MsgChoice  PHY_OAM_LOAD_PHY_CNF_STRU */

    ID_OAM_PHY_SAR_CTRL_REQ                 = 0xD241,                   /* _H2ASN_MsgChoice  PHY_OAM_SAR_CTRL_REQ_STRU */
    ID_PHY_OAM_SAR_CTRL_CNF                 = 0x2D41,                   /* _H2ASN_MsgChoice  PHY_OAM_SAR_CTRL_CNF_STRU */


    /* OAM��GPHY��ԭ�� */
    ID_OAM_GPHY_RF_AGING_TEST_REQ           = 0xD280,                   /* _H2ASN_MsgChoice  GPHY_OAM_RF_AGING_TEST_REQ_STRU */
    ID_GPHY_OAM_RF_AGING_TEST_CNF           = 0x2D80,                   /* _H2ASN_MsgChoice  GPHY_OAM_RF_AGING_TEST_CNF_STRU */


    /* OAM��WPHY��ԭ�� */
    ID_OAM_WPHY_RF_AGING_TEST_REQ           = 0xD2C0,                   /* _H2ASN_MsgChoice  WPHY_OAM_RF_AGING_TEST_REQ_STRU */
    ID_WPHY_OAM_RF_AGING_TEST_CNF           = 0x2DC0,                   /* _H2ASN_MsgChoice  WPHY_OAM_RF_AGING_TEST_CNF_STRU */

    ID_OAM_WPHY_UPDATE_REG_STATE_REQ        = 0xD2C1,                   /* _H2ASN_MsgChoice  WPHY_OAM_UPDATE_REG_STATE_REQ_STRU */
    ID_WPHY_OAM_UPDATE_REG_STATE_CNF        = 0x2DC1,                   /* _H2ASN_MsgChoice  WPHY_OAM_UPDATE_REG_STATE_CNF_STRU */


    ID_PHY_OAM_MSG_ID_BUTT
};
typedef VOS_UINT16 UPHY_OAM_MSG_ID_ENUM_UINT16;


/*****************************************************************************
 ö����    :VOS_RATMODE_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  :˯�߻���ʱ,����ģʽ����
            ע�⣻˫��˫����ö��ֵ������Э��ջ��DRVЭ��ΪGULT;
            ��Ҫ��DrvInterface.h�е�PWC_COMM_MODE_E����һ��

*****************************************************************************/
enum VOS_RATMODE_ENUM
{
    VOS_RATMODE_GSM                         = 0,
    VOS_RATMODE_WCDMA                       = 1,
    VOS_RATMODE_LTE                         = 2,
    VOS_RATMODE_TDS                         = 3,
    VOS_RATMODE_BUTT
};
typedef VOS_UINT32 VOS_RATMODE_ENUM_UINT32;


typedef VOS_UINT32 SLEEP_MODE_ENUM_UINT32;


/*****************************************************************************
 ö����    :UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :�����������ҵ������
*****************************************************************************/
enum UPHY_OAM_BUSINESS_TYPE_ENUM
{
    UPHY_OAM_BUSINESS_TYPE_NORMAL           = 0,                                /* ����ҵ������ */
    UPHY_OAM_BUSINESS_TYPE_CT                  ,                                /* У׼CT���� */
    UPHY_OAM_BUSINESS_TYPE_NO_SIG_BT           ,                                /* �߲������BT���� */
    UPHY_OAM_BUSINESS_TYPE_SIG_BT              ,                                /* ����BT���� */

    UPHY_OAM_BUSINESS_TYPE_BUTT
};
typedef VOS_UINT16 UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16;



/*****************************************************************************
 ö����    :UPHY_OAM_WAKE_TYPE_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  :�������Ͷ���
*****************************************************************************/
enum UPHY_OAM_WAKE_TYPE_ENUM
{
    UPHY_OAM_NORMAL_WAKE                    = 0,
    UPHY_OAM_FORCE_WAKE                     = 1,
    UPHY_OAM_WAKE_TYPE_BUTT
};
typedef VOS_UINT32 UPHY_OAM_WAKE_TYPE_ENUM_UINT32;



/*****************************************************************************
 ö����    :UPHY_OAM_RSLT_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :UPHY�ظ�OAM��CNF��,Я���Ĵ�����ö��
*****************************************************************************/
enum UPHY_OAM_RSLT_ENUM
{
    UPHY_OAM_RSLT_SUCC                      = 0,
    UPHY_OAM_RSLT_FAIL                      = 1,

    UPHY_OAM_RSLT_BUTT
};
typedef VOS_UINT16 UPHY_OAM_RSLT_ENUM_UINT16;




/*****************************************************************************
 ö����    :UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :�ϻ�����ö�ٶ���
*****************************************************************************/
enum UPHY_OAM_AGING_TEST_CTRL_ENUM
{
    UPHY_OAM_AGING_TEST_ON                  = 0x5555,
    UPHY_OAM_AGING_TEST_OFF                 = 0xaaaa,
    UPHY_OAM_AGING_TEST_BUTT
};
typedef VOS_UINT16 UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16;


enum PS_REG_UPDATE_STATE_ENUM
{
    PS_REG_STATE_STOP = 0,
    PS_REG_STATE_ACTIVE,
    PS_REG_STATE_BUTT
};
typedef VOS_UINT16  PS_REG_UPDATE_STATE_ENUM_UINT16;



/*****************************************************************************
 ö����    :PHY_OM_TRANS_MSG_ID_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :��������OM֮����Ϣ͸����ID
*****************************************************************************/
enum PHY_OM_TRANS_MSG_ID_ENUM
{
    ID_PHY_OM_TRANS_MSG_ID              = 0x5001,
    ID_PHY_AT_TRANS_MSG_ID              = 0x4201,

    ID_PHY_OM_TRANS_MSG_BUTT

};
typedef VOS_UINT16 PHY_OM_TRANS_MSG_ID_ENUM_UINT16;


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : PHY_TOOL_MSG_HEAD_STRU
 Э����  :
 �ṹ˵��  : ���ߺ������֮����Ϣ͸��ʱ��Ϣ͸�ṹ
*****************************************************************************/

typedef struct
{
    PHY_OM_TRANS_MSG_ID_ENUM_UINT16     usTransPrimId;                          /* ͸����ϢID = 0x5001 */
    VOS_UINT16                          usRsv;                                  /* ���� */
    VOS_UINT16                          usFuncType;                             /* ��Ϣ���ͣ�7ΪW RF�����������Ϣ */
    VOS_UINT16                          usMsgLen;                               /* ��Ϣ���ȣ���λ�ֽ� */
}PHY_TOOL_MSG_HEAD_STRU;




/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                              usMsgId;                            /* ԭ��ID */
    VOS_UINT8                               aucData[2];                         /* Msg Data*/
}PHY_OAM_MSG_STRU;


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/




/*****************************************************************************
 �ṹ��    : UPHY_OAM_ACTIVE_UPHY_REQ_STRU
 �ṹ˵��  : �ϵ��ʼ����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatTpye;                          /* ģʽ */
}UPHY_OAM_ACTIVE_UPHY_REQ_STRU;




/*****************************************************************************
 �ṹ��    : UPHY_OAM_ACTIVE_UPHY_CNF_STRU
 �ṹ˵��  : �ϵ��ʼ������ظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatTpye;                          /* ģʽ */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ������ */
    VOS_UINT16                              usRsv;                              /* ���� */
}UPHY_OAM_ACTIVE_UPHY_CNF_STRU;



/*****************************************************************************
 �ṹ��    : UPHY_OAM_LOAD_NV_REQ_STRU
 �ṹ˵��  : UPHY��OAM�����ϱ�NV�׵�ַ,OAM�յ���ַ��,��NV��д��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* �ϱ�ģʽ */
    VOS_UINT32                              uwNvAddr;
}UPHY_OAM_LOAD_NV_REQ_STRU;




/*****************************************************************************
 �ṹ��    : UPHY_OAM_LOAD_NV_CNF_STRU
 �ṹ˵��  : OAM��ȡ�׵�ַ��,��NV��д��,Ȼ��ظ�CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* �ϱ�ģʽ */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ������ */
    VOS_UINT16                              usRsv;                              /* ���� */
}UPHY_OAM_LOAD_NV_CNF_STRU;




/*****************************************************************************
 �ṹ��    : UPHY_OAM_GET_NV_ADDR_REQ_STRU
 �ṹ˵��  : OAM�·���ȡNV����׵�ַ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* �ϱ�ģʽ */
}UPHY_OAM_GET_NV_ADDR_REQ_STRU;



/*****************************************************************************
 �ṹ��    : UPHY_OAM_GET_NV_ADDR_IND_STRU
 �ṹ˵��  : UPHY��OAM�ظ�NV�׵�ַ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* �ϱ�ģʽ */
    VOS_UINT32                              uwNvAddr;
}UPHY_OAM_GET_NV_ADDR_IND_STRU;





/*****************************************************************************
 �ṹ��    : UPHY_OAM_BOOT_INFO_REQ_STRU
 �ṹ˵��  : UPHY��OAM������Ϣ,����:
             ulUmtsBandBitMap:W֧�ֵ�Ƶ��
             ulCQIAddr:CQI���׵�ַ
             ulAPTAddr:APT���׵�ַ
             ulETAddr:ET���׵�ַ
             UPHY_MODULE_ADDR_INFO_STRU:���صĶ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* �ϱ�ģʽ */
}UPHY_OAM_BOOT_INFO_REQ_STRU;




/*****************************************************************************
 �ṹ��    : UPHY_OAM_BOOT_INFO_IND_STRU
 �ṹ˵��  : OAM�·�BOOT INFO�����Ϣ��GPHY
             ulUmtsBandBitMap:W֧�ֵ�Ƶ��
             ulCQIAddr:CQI���׵�ַ
             ulAPTAddr:APT���׵�ַ
             ulETAddr:ET���׵�ַ
             PHY_MODULE_ADDR_INFO_STRU:���صĶ���Ϣ
             ���������,û�м���,����Ҫ���ضε�ַ��Ϣ,��˱��ӿڱ���,��д����.
             ����Ϣһ�ſ���ȡһ��,����Ѿ���ȡ,����Բ��ٻ�ȡ
*****************************************************************************/

typedef struct
{
    VOS_UINT32                              ulSegSDRamAddr;                         /* ���ݶλ��ߴ������SDRAM�еĵ�ַ */
    VOS_UINT32                              ulSegSDRamLength;                       /* ���ݶλ��ߴ���γ��� */
    VOS_UINT32                              ulSegTcmAddr;                           /* ���ݶλ��ߴ������DSP�ڲ���AHB��ַ */
}UPHY_MODULE_ADDR_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* �ϱ�ģʽ */
    VOS_UINT32                              ulUmtsBandBitMap;                   /* Ƶ����Чλͼ */
    VOS_UINT32                              ulCQIAddr;                          /* CQI����SDRAM�е��׵�ַ */
    VOS_UINT32                              ulAPTAddr;                          /* APT���ַ:ע��V3R3�����ַ��û�� */
    VOS_UINT32                              ulETAddr;                           /* ET���ַ:ע��V3R3�����ַ��û�� */
    UPHY_MODULE_ADDR_INFO_STRU              astPhyModuleAddrInfo[UPHY_DYN_CODE_MODULE_BUTT];
}UPHY_OAM_BOOT_INFO_IND_STRU;






/*****************************************************************************
 �ṹ��    : UPHY_OAM_WAKE_CMD_STRU
 �ṹ˵��  : OAM��UPHY_DRX�·�����:������ϢΪ:MODEM/MODE/��ģ/��ģ/ǿ��/��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ��ϢID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* �ϱ�ģʽ */
    UPHY_OAM_WAKE_TYPE_ENUM_UINT32          enWakeType;                         /* �������� */
}UPHY_OAM_WAKE_CMD_STRU;



/*****************************************************************************
 �ṹ��    : UPHY_OAM_SLEEP_IND_STRU
 �ṹ˵��  : UPHY_DRX ��OAM����˯�߰�����ϢΪ:MODEM/MODE/��ģ/��ģ/˯��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* �ϱ�ģʽ */
}UPHY_OAM_SLEEP_IND_STRU;





/*****************************************************************************
 �ṹ��    : PHY_OAM_LOAD_PHY_REQ_STRU
 �ṹ˵��  : OAM�·�����W/GPHY,����ģʽ,����/������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* �ϱ�ģʽ */
    UPHY_OAM_BUSINESS_TYPE_ENUM_UINT16      enBusinessType;                     /* ����ҵ������ */
    VOS_UINT16                              usRsv;                              /* ���� */
}PHY_OAM_LOAD_PHY_REQ_STRU;





/*****************************************************************************
 �ṹ��    : PHY_OAM_LOAD_PHY_CNF_STRU
 �ṹ˵��  : W/GPHY���յ�LOAD���������ɺ�ظ�CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    MODEM_ID_ENUM_UINT16                    enModem;                            /* MODEM��Ϣ */
    VOS_RATMODE_ENUM_UINT32                 enRatMode;                          /* �ϱ�ģʽ */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ������ */
    VOS_UINT16                              usRsv;                              /* ���� */
}PHY_OAM_LOAD_PHY_CNF_STRU;





/*****************************************************************************
 �ṹ��    : PHY_OAM_SAR_CTRL_REQ_STRU
 �ṹ˵��  : OAM��W/GPHY�·�SAR��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ��ϢID */
    VOS_UINT16                              usRsv;                              /* ���� */
    VOS_UINT32                              ulMask;                             /* ������� */
    VOS_INT32                               lAntenStatus;                       /* ��ǰ���ߵ�״̬������maskΪPHY_OM_SAR_MASK_ANTSTATEʱ���������Ч,���ֵΪ-1���������ִ�д���*/
    VOS_UINT32                              ulSarReduction;                     /* ���ʻ��˵ȼ�,����maskΪPHY_OM_SAR_MASK_REDUCTIONʱ,�������Ч*/
}PHY_OAM_SAR_CTRL_REQ_STRU;




/*****************************************************************************
 �ṹ��    : PHY_OAM_SAR_CTRL_CNF_STRU
 �ṹ˵��  : W/GPHY��OAM�ظ�SAR��������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ��ϢID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ������ */
}PHY_OAM_SAR_CTRL_CNF_STRU;



/*****************************************************************************
 �ṹ��    : GPHY_OAM_RF_AGING_TEST_REQ_STRU
 �ṹ˵��  : OAM��GPHY�·��ϻ���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ��ϢID */
    VOS_UINT16                              usRsv;                              /* ���� */
    VOS_UINT16                              usFreqNum;                          /* (Band << 12) | Arfcn */
    UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16    enTxEnable;                         /* ����ʹ�ܿ���:0x5555-ʹ�ܷ���;0xAAAA-ֹͣ����;TSC 0; TxData: ����� */
    VOS_UINT16                              usModType;                          /* ������Ʒ�ʽ:0ΪGMSK����;1Ϊ8PSK���Ʒ�ʽ */
    VOS_UINT16                              usTxPower;                          /* Ŀ�귢�书��,��λΪ0.1dBm,GSM��EDGE���� */
    VOS_UINT16                              usSlotCnt;                          /* ����ʱ϶��������Χ1~4������ָ������ʹ����Щʱ϶��DSP�Զ�����1~4ʱ϶���� */
    VOS_UINT16                              usRsv2;
}GPHY_OAM_RF_AGING_TEST_REQ_STRU;



/*****************************************************************************
 �ṹ��    : GPHY_OAM_RF_AGING_TEST_CNF_STRU
 �ṹ˵��  : OAM��GPHY�·��ϻ�����������ظ�CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ������ */
}GPHY_OAM_RF_AGING_TEST_CNF_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_OAM_RF_AGING_TEST_REQ_STRU
 �ṹ˵��  : OAM��WPHY�·��ϻ���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgID;                                /* ��ϢID */
    VOS_UINT16                              usRsv;                                  /* ����λ */
    UPHY_OAM_AGING_TEST_CTRL_ENUM_UINT16    enTxOnOff;                              /* ����ʹ�ܿ���:0x5555-ʹ�ܷ���;0xAAAA-ֹͣ���� */
    VOS_UINT16                              usTxBand;                               /* band */
    VOS_UINT16                              usTxChannel;                            /* ���� */
    VOS_UINT16                              usTxPower;                              /* Ŀ�귢�书��,��λΪ0.1dBm */
}WPHY_OAM_RF_AGING_TEST_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_OAM_RF_AGING_TEST_CNF_STRU
 �ṹ˵��  : OAM��WPHY�·��ϻ�����������ظ�CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ������ */
}WPHY_OAM_RF_AGING_TEST_CNF_STRU;



/*****************************************************************************
 �ṹ��    : WPHY_OAM_UPDATE_REG_STATE_REQ_STRU
 Э����  :
 �ṹ˵��  : �Ĵ�������������Ϣԭ���������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;
    PS_REG_UPDATE_STATE_ENUM_UINT16         enRegState;                         /* 0����ʾ�����мĴ�������, 1�����мĴ������� */
}WPHY_OAM_UPDATE_REG_STATE_REQ_STRU;


/*****************************************************************************
 �ṹ��    : WPHY_OAM_UPDATE_REG_STATE_CNF_STRU
 Э����  :
 �ṹ˵��  : �Ĵ�������������Ϣԭ��ظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    UPHY_OAM_MSG_ID_ENUM_UINT16             enMsgId;                            /* ԭ��ID */
    UPHY_OAM_RSLT_ENUM_UINT16               enRslt;                             /* ������ */
}WPHY_OAM_UPDATE_REG_STATE_CNF_STRU;


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


/*****************************************************************************
 �� �� ��  : SLEEP_MasterWakeSlave
 ��������  : GUPHY��Ϊ��ģ���Ѵ�ģ����.
 �������  : MODEM_ID_ENUM_UINT16      enModem   ��Ҫ���ѵ�MODEM
             VOS_RATMODE_ENUM_UINT32   enRatMode ��Ҫ���ѵ�MODE

 �������  : ��

 �� �� ֵ  : VOS_UINT32
*****************************************************************************/
VOS_UINT32 SLEEP_MasterWakeSlave(
                    VOS_RATMODE_ENUM_UINT32   enRatMode );



VOS_UINT32 SLEEP_AwakeInfoGet( SLEEP_MODE_ENUM_UINT32 enMode, VOS_UINT32 *pstAwakeHWInfo, VOS_UINT32 uLen );



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

#endif /* end of gphytoolinterface.h */

