
#ifndef __PHYCODECINTERFACE_H__
#define __PHYCODECINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CodecInterface.h"

/* _H2ASN_Include CODEC_ctrl_mc.h */
/* _H2ASN_Include codec_typedefine.h */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define GPHY_VOICE_DATA_LEN                                   (17)                /* G�������CODEC�������������ݳ���,��λ16Bit */
#define WPHY_VOICE_WCDMA_MAX_CELL_NUM                         (6)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum DSP_VOICE_MSG_ID_ENUM
{
    /*====== WPHY->CODEC ======*/
    ID_WPHY_VOICE_RX_DATA_IND                         = 0xBD01,                 /* W ��������ָʾ */             /* _H2ASN_MsgChoice WPHY_VOICE_RX_DATA_IND_STRU */
    ID_WPHY_VOICE_SYNC_IND                            = 0xBD02,                 /* W ͬ��ָʾ */                 /* _H2ASN_MsgChoice WPHY_VOICE_SYNC_IND_STRU */
    ID_WPHY_VOICE_BACKGROUND_CNF                      = 0xBD03,                 /* W �����ظ��ѽ��뾲Ĭģʽ *//* _H2ASN_MsgChoice GUPHY_VOICE_BACKGROUND_CNF_STRU */
    ID_WPHY_VOICE_FOREGROUND_CNF                      = 0xBD04,                 /* W �����ظ����˳���Ĭģʽ *//* _H2ASN_MsgChoice GUPHY_VOICE_FOREGROUND_CNF_STRU */
    ID_WPHY_VOICE_CHANNEL_QUALITY_IND                 = 0xBD05,                 /* W ������ϱ��ŵ����������ں�̨��ά�ɲ� *//* _H2ASN_MsgChoice WPHY_VOICE_CHANNEL_QUALITY_IND_STRU */

    /*====== CODEC->WPHY ======*/
    ID_VOICE_WPHY_TX_DATA_IND                         = 0xDB01,                 /* W ���������� */             /* _H2ASN_MsgChoice VOICE_WPHY_TX_DATA_IND_STRU */
    ID_VOICE_WPHY_BACKGROUND_REQ                      = 0xDB03,                 /* W ֪ͨPHY���뾲Ĭ����ģʽ */  /* _H2ASN_MsgChoice VOICE_GUPHY_BACKGROUND_REQ_STRU */
    ID_VOICE_WPHY_FOREGROUND_REQ                      = 0xDB04,                 /* W ֪ͨPHY�˳���Ĭ����ģʽ */  /* _H2ASN_MsgChoice VOICE_GUPHY_FOREGROUND_REQ_STRU */

    /*====== GPHY->CODEC ======*/
    ID_GPHY_VOICE_RX_DATA_IND                         = 0xCD01,                 /* GSM ��������ָʾ */           /* _H2ASN_MsgChoice GPHY_VOICE_RX_DATA_IND_STRU */
    ID_GPHY_VOICE_UPDATE_PARA_CMD                     = 0xCD02,                 /* GSM ��������������� */       /* _H2ASN_MsgChoice GPHY_VOICE_UPDATE_PARA_CMD_STRU */
    ID_GPHY_VOICE_PLAY_IND                            = 0xCD04,                 /* GSM ����������������ָʾ */   /* _H2ASN_MsgChoice GPHY_VOICE_PLAY_IND_STRU */
    ID_GPHY_VOICE_RECORD_IND                          = 0xCD05,                 /* GSM ���������ɼ�����ָʾ */   /* _H2ASN_MsgChoice GPHY_VOICE_RECORD_IND_STRU */
    ID_GPHY_VOICE_BACKGROUND_CNF                      = 0xCD07,                 /* G �����ظ��ѽ��뾲Ĭģʽ *//* _H2ASN_MsgChoice GUPHY_VOICE_BACKGROUND_CNF_STRU */
    ID_GPHY_VOICE_FOREGROUND_CNF                      = 0xCD08,                 /* G �����ظ����˳���Ĭģʽ *//* _H2ASN_MsgChoice GUPHY_VOICE_FOREGROUND_CNF_STRU */
    ID_GPHY_VOICE_SYNC_IND                            = 0xCD10,                 /* G ͬ��ָʾ */                /* _H2ASN_MsgChoice GPHY_VOICE_SYNC_IND_STRU */
    ID_GPHY_VOICE_CHANNEL_QUALITY_IND                 = 0xCD11,                 /* G ������ŵ�������ά�ɲ� */ /* _H2ASN_MsgChoice GPHY_VOICE_CHANNEL_QUALITY_IND_STRU */

    /*====== CODEC->GPHY ======*/
    ID_VOICE_GPHY_TX_DATA_IND                         = 0xDC02,                 /* GSM ���������� */           /* _H2ASN_MsgChoice VOICE_GPHY_TX_DATA_IND_STRU */
    ID_VOICE_GPHY_SYNC_REQ                            = 0xDC03,                 /* GSM ����ʱ��ͬ������GPHY�յ�������ָʾ������ʼ�����������ɼ������� */ /* _H2ASN_MsgChoice VOICE_GPHY_SYNC_REQ_STRU */
    ID_VOICE_GPHY_PLAY_CNF                            = 0xDC04,                 /* GSM ����������������ȷ�� */   /* _H2ASN_MsgChoice VOICE_GPHY_PLAY_CNF_STRU */
    ID_VOICE_GPHY_RECORD_CNF                          = 0xDC05,                 /* GSM ����������������ȷ�� */   /* _H2ASN_MsgChoice VOICE_GPHY_RECORD_CNF_STRU */
    ID_VOICE_GPHY_SET_CODEC_IND                       = 0xDC06,                 /* GSM �������л�ָʾ */         /* _H2ASN_MsgChoice VOICE_GPHY_SET_CODEC_IND_STRU */
    ID_VOICE_GPHY_BACKGROUND_REQ                      = 0xDC07,                 /* GSM ֪ͨPHY���뾲Ĭ����ģʽ *//* _H2ASN_MsgChoice VOICE_GUPHY_BACKGROUND_REQ_STRU */
    ID_VOICE_GPHY_FOREGROUND_REQ                      = 0xDC08,                 /* GSM ֪ͨPHY�˳���Ĭ����ģʽ *//* _H2ASN_MsgChoice VOICE_GUPHY_FOREGROUND_REQ_STRU */

    /*====== CODEC->CODEC ======*/
    ID_VOICE_VOICE_ENC_REQ                            = 0xDD03,                   /* G/U������Ϣ,������DMA�������ʱ���� */
    ID_VOICE_VOICE_RECORD_IND                         = 0xDD04,                   /* UMTS ����DMA����������Ϣ,��3ms��ʱ���ж��з��� */        /* _H2ASN_MsgChoice GPHY_VOICE_RECORD_IND_STRU */
    ID_VOICE_VOICE_PLAY_IND                           = 0xDD05,                   /* UMTS ������������,��6ms��ʱ���ж��з��� */               /* _H2ASN_MsgChoice GPHY_VOICE_PLAY_IND_STRU */
    ID_VOICE_VOICE_UPDATE_REQ                         = 0xDD07,                   /* ���������ͱ仯ʱ,�������������д��� */
    ID_VOICE_VOICE_DEC_REQ                            = 0xDD08,                   /* G/U������Ϣ,������DMA�������ʱ���� */

    /*====== UCOM->CODEC ======*/
    ID_UCOM_VOICE_SUSPEND_CMD                         = 0xCD09,                 /* ���������ͣ���ָ���Ϣ����G/U������ϵͳ�л������з��� */ /* _H2ASN_MsgChoice GUPHY_VOICE_SUSPEND_CMD_STRU */

    MSG_ID_BUTT
};
typedef VOS_UINT16 DSP_VOICE_MSG_ID_ENUM_UINT16;

/* PHY��MED����ȷ���гɹ���ʧ��ָʾö�� */
enum DSP_VOICE_RESULT_ENUM
{
    DSP_VOICE_RESULT_SUCC,
    DSP_VOICE_RESULT_FAIL,

    DSP_VOICE_RESULT_BUTT,
};
typedef VOS_UINT16 DSP_VOICE_RESULT_ENUM_UINT16;
/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/
/*****************************************************************************
 ʵ������  : WPHY_VOICE_SYNC_IND_STRU
 ��������  : ����ҵ��������WPHY��9ms�жϷ��͸���Ϣ��CODEC����ʱ��ͬ��ָʾ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD02*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;                             /* ����*/
    VOS_UINT16                          uhwCfn;                                 /* ��ǰCFN */
    VOS_UINT16                          uhwSlotOffset;                          /* ͬ����Ϣƫ��֡ͷλ�õ�slotֵ */
    VOS_UINT16                          uhwChipOffset;                          /* ͬ����Ϣƫ��֡ͷλ�õ�chipֵ */
    VOS_UINT16                          uhwReserve2;
    VOS_UINT32                          uwTimeSlice;                            /* ����ʱ��ʱ�� */
}WPHY_VOICE_SYNC_IND_STRU;

/*****************************************************************************
 ʵ������  : WPHY_VOICE_RX_DATA_IND_STRU
 ��������  : WPHYȡ��AMR�����󣬽��н��ܣ���������͸���Ϣ��CODEC�����ݷ��͹�ȥ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD01*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwCfn;
    WPHY_VOICE_DATA_STRU
}WPHY_VOICE_RX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_WPHY_TX_DATA_IND_STRU
 ��������  : CODEC����������OK�󣬷��͸���Ϣ��WPHY�����ݷ��͹�ȥ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDB01*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    WPHY_VOICE_DATA_STRU
}VOICE_WPHY_TX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : WPHY_VOICE_CELL_INFO_STRU
 ��������  : WС��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwCpichRscp;                           /* CPICH RSCP����ֵ */
    VOS_INT16                           shwCpichEcN0;                           /* CPICH EcN0����ֵ */
}WPHY_VOICE_CELL_INFO_STRU;

/*****************************************************************************
 ʵ������  : WPHY_VOICE_CHANNEL_QUALITY_IND_STRU
 ��������  : W������ά�ɲ⣬�ϱ�С���ŵ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDB01*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwCellNum;                             /* �ϱ�С������ */
    VOS_UINT16                          uhwServCellId;                          /* ����С����Ӧ��ID */
    VOS_UINT16                          uhwReserved;                            /* �����ֶΣ���֤4�ֽڶ��� */
    WPHY_VOICE_CELL_INFO_STRU           astCellInfo[WPHY_VOICE_WCDMA_MAX_CELL_NUM];
}WPHY_VOICE_CHANNEL_QUALITY_IND_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_UPDATE_PARA_CMD_STRU
 ��������  : GPHY�ڳ�ʼ����ͱ�����������仯ʱ���͸���Ϣ����CODEC���б����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD02*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    CODEC_ENUM_UINT16                   enCodecType;                            /*����������: 0 AMR-NB, 1 EFR, 2 FR, 3 HR , 4 AMR-NB 5 AMR-WB*/
    CODEC_DTX_ENUM_UINT16               enDtxMode;                              /* DTXʹ�ܱ�־��0 ��ʹ�ܣ�1 ʹ��*/
    VOS_UINT16                          enAmrMode;                              /* AMR��������ģʽ, �����AMR-NB��ȡֵ��7-0�ֱ��Ӧ8�ֲ�ͬ������ģʽ12.2-4.75�������AMR-WB��ȡֵ2��1��0���ֱ��Ӧ12.65��8.85��6.60*/
    CODEC_AMR_NSYNC_ENUM_UINT16         enAmrNsync;                             /*һ��Ϊ0���л����µĻ�վʱ��ȡ12*/
}GPHY_VOICE_UPDATE_PARA_CMD_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_PLAY_IND_STRU
 ��������  : GPHY���͸���Ϣ����CODEC����������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD04*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwTimeSlice;                            /* ����ʱ��ʱ�� */
}GPHY_VOICE_PLAY_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GPHY_PLAY_CNF_STRU
 ��������  : CODEC���͸���Ϣ�ظ�GPHY��ԭ��ID_VOICE_GPHY_PLAY_CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC04*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwRslt;                                 /*ִ�н��,0�ɹ�/1ʧ��*/
}VOICE_GPHY_PLAY_CNF_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_RECORD_IND_STRU
 ��������  : GPHY���͸���Ϣ����CODEC�������������ɼ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD05*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwTimeSlice;                            /* ����ʱ��ʱ�� */
}GPHY_VOICE_RECORD_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GPHY_RECORD_CNF_STRU
 ��������  : CODEC���͸���Ϣ�ظ�GPHY��ԭ��ID_VOICE_GPHY_RECORD_CNF
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC05*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
    VOS_UINT32                          uwRslt;                                 /*ִ�н��,0�ɹ�/1ʧ��*/
}VOICE_GPHY_RECORD_CNF_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_RX_DATA_IND_STRU
 ��������  : GPHY����������ͨ������Ϣ���͸�CODEC�������н���
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD01 */ /*_H2ASN_Skip*/
    CODEC_ENUM_UINT16                   enCodecType;                            /* ����������: 0-AMR, 1-EFR, 2-FR, 3-HR */
    CODEC_BFI_ENUM_UINT16               enBfi;                                  /* ��֡��־,HR/FR/EFRʹ�� 0 dis 1 enable,bad*/
    CODEC_SID_ENUM_UINT16               enSid;                                  /* HR/FR/EFRʹ�� */
    CODEC_TAF_ENUM_UINT16               enTaf;                                  /* ͬ����־,HR/FR/EFRʹ�� */
    CODEC_HR_UFI_ENUM_UINT16            enUfi;                                  /* 0-�ŵ��ȶ�, 1-�ŵ�����, HRʹ�� */
    VOS_UINT16                          enAmrMode;                              /* AMR��������ģʽ*/
    CODEC_AMR_TYPE_RX_ENUM_UINT16       enAmrFrameType;                         /* AMR֡����, TX_SPEECH_GOOD/TX_SID_FIRST/TX_SID_UPDATA/TX_NO_DATA */
    VOS_UINT16                          puhwData[GPHY_VOICE_DATA_LEN];            /* AMRΪ����ǰ������Ϊ���ź���������ݣ���16bit�������У�������Чλ�ΪFR��260/16�� */
    CODEC_FRAME_FACCH_ENUM_UINT16       enIsFrameFacch;
} GPHY_VOICE_RX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GPHY_TX_DATA_IND_STRU
 ��������  : CODEC�����������󣬷��͸���Ϣ��GPHY��������������ݷ��͹�ȥ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC02 */ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;                             /* ���� */
    CODEC_VAD_ENUM_UINT16               enVadFlag;                              /* VAD��־, 0-����֡, 1-������֡, HR/FR/EFRʱʹ��*/
    CODEC_SP_ENUM_UINT16                enSpFlag;                               /* Speech��־: 0Ϊ������֡��1Ϊ����֡, HR/FR/EFRʱʹ��*/
    CODEC_AMR_TYPE_TX_ENUM_UINT16       enAmrFrameType;                         /*����AMR֡����,TX_SPEECH_GOOD,TX_SPEECH_FIRST,TX_SID_UPDATA,TX_NODATA */
    VOS_UINT16                          enAmrMode;                              /* AMR�������� */
    VOS_UINT16                          auhwData[GPHY_VOICE_DATA_LEN];          /* AMRΪ���ź�����Ϊ����ǰ���������ݣ���16bit�������У�������Чλ�ΪFR��260/16��*/
    CODEC_ENUM_UINT16                   enCodecType;                            /* ����������: 0-AMR, 1-EFR, 2-FR, 3-HR, 5-AMRWB */
}VOICE_GPHY_TX_DATA_IND_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GPHY_SYNC_REQ_STRU
 ��������  : CODEC���͸���Ϣ��GPHY����ʱ��ͬ������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC03*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
} VOICE_GPHY_SYNC_REQ_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GPHY_SET_CODEC_IND_STRU
 ��������  : CODEC�յ�NAS����������ʱ���͸���Ϣ֪ͨGPHY�����������¼�
*****************************************************************************/
 typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xDC06*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;                             /* ������ */
} VOICE_GPHY_SET_CODEC_IND_STRU;

/*****************************************************************************
 ʵ������  : GUPHY_VOICE_SUSPEND_CMD_STRU
 ��������  : GU-PHY��2G3��3G2ʱ���͸���Ϣ����CODEC��ͣ��������
*****************************************************************************/
 typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xCD08*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserve;
} GUPHY_VOICE_SUSPEND_CMD_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GUPHY_BACKGROUND_REQ_STRU
 �ṹ˵��  : VOICEģ��֪ͨPHY���뾲Ĭ����ģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserved;
} VOICE_GUPHY_BACKGROUND_REQ_STRU;

/*****************************************************************************
 ʵ������  : PHY_CODEC_BACKGROUND_CNF_STRU
 �ṹ˵��  : PHY�ظ�CODEC�ѽ��뾲Ĭ����ģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    DSP_VOICE_RESULT_ENUM_UINT16                enResult;
    VOS_UINT16                                  ausReserved[2];
} GUPHY_VOICE_BACKGROUND_CNF_STRU;

/*****************************************************************************
 ʵ������  : VOICE_GUPHY_FOREGROUND_REQ_STRU
 �ṹ˵��  : VOICEģ��֪ͨPHY������������ģʽ(�˳���Ĭģʽ)
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    VOS_UINT16                                  usReserved;
} VOICE_GUPHY_FOREGROUND_REQ_STRU;

/*****************************************************************************
 ʵ������  : GUPHY_VOICE_FOREGROUND_CNF_STRU
 �ṹ˵��  : PHY�ظ�CODEC�ѽ�����������ģʽ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                                  usMsgId;                        /*_H2ASN_Skip*/
    DSP_VOICE_RESULT_ENUM_UINT16                enResult;
    VOS_UINT16                                  ausReserved[2];
} GUPHY_VOICE_FOREGROUND_CNF_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_SYNC_IND_STRU
 ��������  : ����ҵ��������GPHY�ڵ�12֡��0ʱ϶�͸���Ϣ��CODEC����ʱ��ͬ��ָʾ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /*_H2ASN_Skip*/
    VOS_UINT16                          uhwMsgId;                               /* 0xBD10*/ /*_H2ASN_Skip*/
    VOS_UINT16                          uhwReserved1;                           /* ���� */
    VOS_UINT32                          uwFn;                                   /* ֡�� */
    VOS_UINT32                          uwQb;                                   /* QB 0~4999 */
    VOS_UINT32                          uwTimeSlice;                            /* ����ʱ��ʱ�� */
    VOS_UINT16                          uhwTsn;                                 /* ʱ϶�� 0~7 */
    VOS_UINT16                          uhwChanCodeTime;                        /* ���б���ʱ��, ��λ:0.1 ms */
    VOS_UINT16                          uhwChanDecodeTime;                      /* ��������ʱ��, ��λ:0.1 ms */
    VOS_UINT16                          uhwReserved2;                           /* ���� */
}GPHY_VOICE_SYNC_IND_STRU;

/*****************************************************************************
 ʵ������  : GPHY_VOICE_CHANNEL_QUALITY_IND_STRU
 ��������  : GPHY��CODEC����G�ŵ����������ڿ�ά�ɲ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */ /* ��Ϣͷ */
    VOS_UINT16                          uhwMsgId;                               /* _H2ASN_Skip */ /* ԭ������ */
    VOS_UINT16                          uhwDTX;
    VOS_UINT16                          uhwRxlevFull;                            /* �ź�ǿ��+ƫ��(316) */
    VOS_UINT16                          uhwRxlevSub;                             /* �ź�ǿ��+ƫ��(316) */
    VOS_UINT16                          uhwFrmNumFull;                           /* FULL���ĵ�ƽͳ��֡�� */
    VOS_UINT16                          uhwFrmNumSub;                            /* SUB���ĵ�ƽͳ��֡�� */
    VOS_UINT16                          uhwErrBitsFull;                          /* FULL��������BIT�� */
    VOS_UINT16                          uhwErrBitsSub;                           /* SUB��������BIT�� */
    VOS_UINT16                          uhwTotalBitsFull;                        /* FULL���ܵı����� */
    VOS_UINT16                          uhwTotalBitsSub;                         /* SUB���ܵı����� */
    VOS_UINT16                          uhwRxLevVal;
    VOS_UINT16                          uhwMeanBep;
    VOS_UINT16                          uhwCvBep;
    VOS_UINT16                          uhwReserved;
}GPHY_VOICE_CHANNEL_QUALITY_IND_STRU;

/*****************************************************************************
  6 STRUCT����
*****************************************************************************/


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/
#if 0                                                       /* _H2ASN_Skip */

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
/* ��Ҫ������Ӧ��ASN����,ȥ��L��ʽ,������V��ʽ */
typedef struct
{
    DSP_VOICE_MSG_ID_ENUM_UINT16          enMsgID;            /* _H2ASN_MsgChoice_Export DSP_VOICE_MSG_ID_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          DSP_VOICE_MSG_ID_ENUM_UINT16
    ****************************************************************************/
}VOICE_PHY_TRACE_MSG_DATA;

/* Э����Ϣ�ṹ*/
typedef struct
{
    VOS_UINT32 uwSenderCpuId;
    VOS_UINT32 uwSenderPid;
    VOS_UINT32 uwReceiverCpuId;
    VOS_UINT32 uwReceiverPid;
    VOS_UINT32 uwLength;
    VOICE_PHY_TRACE_MSG_DATA              stMsgData;
}VoicePhyTrace_MSG;

#endif                                                     /* _H2ASN_Skip */


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of phycodecinterface.h */
