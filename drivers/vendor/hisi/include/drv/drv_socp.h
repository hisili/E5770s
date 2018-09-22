

#ifndef _DRV_SOCP_H
#define _DRV_SOCP_H

#include "drv_comm.h"

#ifdef __cplusplus
extern "C"
{
#endif
/**************************************************************************
  �궨��
**************************************************************************/
#define SOCP_CODER_SRC_CHAN                 0x00
#define SOCP_CODER_DEST_CHAN                0x01
#define SOCP_DECODER_SRC_CHAN               0x02
#define SOCP_DECODER_DEST_CHAN              0x03


#define SOCP_CHAN_DEF(chan_type, chan_id)   ((chan_type<<16)|chan_id)
#define SOCP_REAL_CHAN_ID(unique_chan_id)   (unique_chan_id & 0xFFFF)
#define SOCP_REAL_CHAN_TYPE(unique_chan_id) (unique_chan_id>>16)

/*����Դͨ��IDö�ٶ���*/
enum SOCP_CODER_SRC_ENUM
{
    SOCP_CODER_SRC_LOM_CNF1     = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,0),  /* LTE OM������Ӧ */
    SOCP_CODER_SRC_HDLCAT_CNF   = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,1),  /* HDLC��ʽAT������Ӧ */
    SOCP_CODER_SRC_LOM_IND1     = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,2),  /* LTE OM�����Ϣ */
    SOCP_CODER_SRC_GU_OM1       = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,3),  /* GU OM�����Ϣ */
    SOCP_CODER_SRC_LOM_IND2     = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,4),  /* LTE OM�����Ϣ���� */
    SOCP_CODER_SRC_LOM_IND3     = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,5),  /* LTE OM�����Ϣ���� */
    SOCP_CODER_SRC_LOM_CNF2     = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,6),  /* LTE OM������Ӧ */
    SOCP_CODER_SRC_GU_OM2       = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,7),  /* GU OM�����Ϣ */
    SOCP_CODER_SRC_RFU          = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,8),  /* ���� */
    SOCP_CODER_SRC_HIFI         = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,9),  /* GU HIFI�����Ϣ */
    SOCP_CODER_SRC_MUTIL_MEDIA1 = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,10), /* ý�������Ϣ */
    SOCP_CODER_SRC_MUTIL_MEDIA2 = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,11), /* ý�������Ϣ */
    SOCP_CODER_SRC_MCU1         = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,12), /* MCU�����Ϣ */
    SOCP_CODER_SRC_MCU2         = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,13), /* MCU�����Ϣ */
    SOCP_CODER_SRC_LDSP1        = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,14), /* LDSP�����Ϣ */
    SOCP_CODER_SRC_LDSP2        = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,15), /* LDSP�����Ϣ */
    SOCP_CODER_SRC_LBBP1        = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,16), /* LBBP�����Ϣ */
    SOCP_CODER_SRC_LBBP2        = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,17), /* LBBP�����Ϣ */
    SOCP_CODER_SRC_LBBP3        = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,18), /* LBBP�����Ϣ */
    SOCP_CODER_SRC_LBBP4        = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,19), /* LBBP�����Ϣ */
    SOCP_CODER_SRC_LBBP5        = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,20), /* LBBP�����Ϣ */
    SOCP_CODER_SRC_LBBP6        = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,21), /* LBBP�����Ϣ */
    SOCP_CODER_SRC_LBBP7        = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,22), /* LBBP�����Ϣ */
    SOCP_CODER_SRC_LBBP8        = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,23), /* LBBP�����Ϣ */
    SOCP_CODER_SRC_LBBP9        = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,24), /* LBBP�����Ϣ */
    SOCP_CODER_SRC_GUBBP1       = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,25), /* GUBBP�����Ϣ */
    SOCP_CODER_SRC_GUBBP2       = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,26), /* GUBBP�����Ϣ */
    SOCP_CODER_SRC_GUDSP1       = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,27), /* GUDSP�����Ϣ */
    SOCP_CODER_SRC_GUDSP2       = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,28), /* GUDSP�����Ϣ */
    SOCP_CODER_SRC_TDDSP1       = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,29), /* TDDSP�����Ϣ */
    SOCP_CODER_SRC_TDBBP1       = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,30), /* TDBBP�����Ϣ */
    SOCP_CODER_SRC_TDBBP2       = SOCP_CHAN_DEF(SOCP_CODER_SRC_CHAN,31), /* TDBBP�����Ϣ */
    SOCP_CODER_SRC_BUTT
};
typedef BSP_U32 SOCP_CODER_SRC_ENUM_U32;

/*����Դͨ��IDö�ٶ���*/
enum SOCP_DECODER_SRC_ENUM
{
    SOCP_DECODER_SRC_LOM        = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,0),   /* LTE OM���� */
    SOCP_DECODER_SRC_HDLC_AT    = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,1),   /* HDLC�������ʽAT���� */
    SOCP_DECODER_SRC_GUOM       = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,2),   /* GU OM���� */
    SOCP_DECODER_SRC_RFU        = SOCP_CHAN_DEF(SOCP_DECODER_SRC_CHAN,3),   /* ���� */
    SOCP_DECODER_SRC_BUTT
};
typedef BSP_U32 SOCP_DECODER_SRC_ENUM_U32;

/*����Ŀ��ͨ��IDö�ٶ���*/
enum SOCP_CODER_DST_ENUM
{
    SOCP_CODER_DST_LOM_CNF       = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,0), /* LTE OM������Ӧ��� */
    SOCP_CODER_DST_LOM_IND       = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,1), /* LTE OM�����ϱ���� */
    SOCP_CODER_DST_HDLC_AT       = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,2), /* ��ʽAT������Ӧ��� */
    SOCP_CODER_DST_GU_OM         = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,3), /* GU OMĿ��ͨ�� */
    SOCP_CODER_DST_RFU1          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,4), /* ���� */
    SOCP_CODER_DST_RFU2          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,5), /* ���� */
    SOCP_CODER_DST_RFU3          = SOCP_CHAN_DEF(SOCP_CODER_DEST_CHAN,6), /* ���� */
    SOCP_CODER_DST_BUTT
};
typedef BSP_U32 SOCP_CODER_DST_ENUM_U32;

/*����Ŀ��ͨ��IDö�ٶ���*/
enum SOCP_DECODER_DST_ENUM
{
    SOCP_DECODER_DST_LOM        = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,0),  /* LTE OM���� */
    SOCP_DECODER_DST_HDLC_AT    = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,1),  /* HDLC�������ʽAT���� */
    SOCP_DECODER_DST_GUOM       = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,2),  /* GU OM���� */
    SOCP_DECODER_DST_RFU        = SOCP_CHAN_DEF(SOCP_DECODER_DEST_CHAN,3),  /* ���� */
    SOCP_DECODER_DST_BUTT
};
typedef BSP_U32 SOCP_DECODER_DST_ENUM_U32;

#define SOCP_CODER_SRC_CHAN_BASE            0x00000000
#define SOCP_CODER_DEST_CHAN_BASE           0x00010000
#define SOCP_DECODER_SRC_CHAN_BASE          0x00020000
#define SOCP_DECODER_DEST_CHAN_BASE         0x00030000

/**************************************************************************
  �ṹ����
**************************************************************************/
/* SCMʹ�����ݽṹ����V9ͬ�� begin */
enum SOCP_BD_TYPE_ENUM
{
    SOCP_BD_DATA            = 0,    /* SOCP BD���ݿռ�ʹ��ʵ������ */
    SOCP_BD_LIST            = 1,    /* SOCP BD���ݿռ�ʹ��ʵ�����ݵ�ָ�� */
    SOCP_BD_BUTT
};
typedef BSP_U16 SOCP_BD_TYPE_ENUM_UINT16;

enum SOCP_HDLC_FLAG_ENUM
{
    SOCP_HDLC_ENABLE         = 0,    /* ��ǰHDLC���ܴ� */
    SOCP_HDLC_DISABLE        = 1,    /* ��ǰHDLC���ܹر� */
    SOCP_HDLC_FLAG_BUTT
};

enum SOCP_STATE_ENUM
{
    SOCP_IDLE               = 0,    /* SOCP���ڿ���̬ */
    SOCP_BUSY,                      /* SOCP��æ */
    SOCP_UNKNOWN_BUTT              /*  δ֪״̬ */
};
typedef BSP_U32 SOCP_STATE_ENUM_UINT32;

/*����SOCPͨ����BD����Ƭ�ṹ*/
typedef struct
{
    BSP_U8                       *pucData;       /* ���ݵ�ָ�� */
    BSP_U16                      usMsgLen;       /* ���ݳ��� */
    SOCP_BD_TYPE_ENUM_UINT16     enDataType;     /* ʵ���������ͣ�����������ʵ���� */
}SOCP_BD_DATA_STRU;

/*����SOCPͨ����RD����Ƭ�ṹ*/
typedef struct
{
    BSP_U8                      *pucData;       /*����ָ��*/
    BSP_U16                     usMsgLen;       /*���ݳ���*/
    SOCP_BD_TYPE_ENUM_UINT16    enDataType;     /*ʵ���������ͣ�����������ʵ����*/
}SOCP_RD_DATA_STRU;
/* SCMʹ�����ݽṹ����V9ͬ�� end */

typedef enum tagSOCP_EVENT_E
{
    SOCP_EVENT_PKT_HEADER_ERROR         = 0x1,    /* ��ͷ������"HISI" */
    SOCP_EVENT_OUTBUFFER_OVERFLOW       = 0x2,    /* Ŀ��buffer���� */
    SOCP_EVENT_RDBUFFER_OVERFLOW        = 0x4,    /* RDbuffer���� */
    SOCP_EVENT_DECODER_UNDERFLOW        = 0x8,    /* ����Դbuffer���� */
    SOCP_EVENT_PKT_LENGTH_ERROR         = 0x10,   /* ��������ȼ����� */
    SOCP_EVENT_CRC_ERROR                = 0x20,   /* ����CRCУ����� */
    SOCP_EVENT_DATA_TYPE_ERROR          = 0x40,   /* �����������ʹ���*/
    SOCP_EVENT_HDLC_HEADER_ERROR        = 0x80,   /* ����HDLC������ */
    SOCP_EVENT_OUTBUFFER_THRESHOLD_OVERFLOW = 0x100, /* Ŀ��buffer��ֵ����ж� */
    SOCP_EVENT_BUTT
}SOCP_EVENT_E;

/* ����Դ�����ݽṹģʽ */
typedef enum tagSOCP_ENCSRC_CHNMODE_E
{
    SOCP_ENCSRC_CHNMODE_CTSPACKET       = 0,    /* �������ݰ����λ����� */
    SOCP_ENCSRC_CHNMODE_FIXPACKET,              /* �̶��������ݰ����λ����� */
    SOCP_ENCSRC_CHNMODE_LIST,                   /* ��ʽ���λ����� */
    SOCP_ENCSRC_CHNMODE_BUTT
}SOCP_ENCSRC_CHNMODE_E;

/* ����Դ�����ݽṹģʽ */
typedef enum tagSOCP_DECSRC_CHNMODE_E
{
    SOCP_DECSRC_CHNMODE_BYTES        = 0,       /* �����ֽڻ��λ����� */
    SOCP_DECSRC_CHNMODE_LIST,                   /* ��ʽ���λ����� */
    SOCP_DECSRC_CHNMODE_BUTT
}SOCP_DECSRC_CHNMODE_E;

/* ��ʱѡ��ʹ�����ݽṹ��SOCP_TIMEOUT_DECODE_TRF */
typedef enum tagSOCP_TIMEOUT_EN_E
{
    SOCP_TIMEOUT_BUFOVF_DISABLE        = 0,       /* buffer��������ϱ��ж� */
    SOCP_TIMEOUT_BUFOVF_ENABLE,                   /* buffer�������ʱ�����ϱ��ж� */
    SOCP_TIMEOUT_TRF,                             /* �����жϳ�ʱ���� */
    SOCP_TIMEOUT_DECODE_TRF,                      /* �����жϳ�ʱ */
    SOCP_TIMEOUT_BUTT
}SOCP_TIMEOUT_EN_E;

/* ͬһ���͵�ͨ����ͬ���ȼ�ö��ֵ*/
typedef enum tagSOCP_CHAN_PRIORITY_E
{
    SOCP_CHAN_PRIORITY_0     = 0,               /* ������ȼ�*/
    SOCP_CHAN_PRIORITY_1,                       /* �ε����ȼ�*/
    SOCP_CHAN_PRIORITY_2,                       /* �θ����ȼ�*/
    SOCP_CHAN_PRIORITY_3,                       /* ������ȼ�*/
    SOCP_CHAN_PRIORITY_BUTT
}SOCP_CHAN_PRIORITY_E;

/* ��������ö��ֵ*/
typedef enum tagSOCP_DATA_TYPE_E
{
    SOCP_DATA_TYPE_0            = 0,            /* LTE OAM���� */
    SOCP_DATA_TYPE_1,                           /* GU OAM���� */
    SOCP_DATA_TYPE_2,                           /* ���� */
    SOCP_DATA_TYPE_3,                           /* ���� */
    SOCP_DATA_TYPE_BUTT
}SOCP_DATA_TYPE_E;


/* BBP ����ģʽ�����ݶ����򸲸� */
typedef enum tagSOCP_BBP_DS_MODE_E
{
    SOCP_BBP_DS_MODE_DROP           = 0,        /* ���ݶ��� */
    SOCP_BBP_DS_MODE_OVERRIDE,                  /* ���ݸ��� */
    SOCP_BBP_DS_MODE_BUTT
}SOCP_BBP_DS_MODE_E;

/* ����Դͨ��data type ʹ��λ */
typedef enum tagSOCP_DATA_TYPE_EN_E
{
    SOCP_DATA_TYPE_EN           = 0,        /* data type ʹ�ܣ�Ĭ��ֵ */
    SOCP_DATA_TYPE_DIS,                     /* data type ��ʹ�� */
    SOCP_DATA_TYPE_EN_BUTT
}SOCP_DATA_TYPE_EN_E;

/* ����Դͨ��debug ʹ��λ */
typedef enum tagSOCP_ENC_DEBUG_EN_E
{
    SOCP_ENC_DEBUG_DIS          = 0,       /* debug ��ʹ�ܣ�Ĭ��ֵ */
    SOCP_ENC_DEBUG_EN,                     /* debug ʹ�� */
    SOCP_ENC_DEBUG_EN_BUTT
}SOCP_ENC_DEBUG_EN_E;

/* ����ͨ·�������ýṹ�� */
typedef struct tagSOCP_DEC_PKTLGTH_S
{
    BSP_U32             u32PktMax;         /*���������ֵ*/
    BSP_U32             u32PktMin;         /*��������Сֵ*/
}SOCP_DEC_PKTLGTH_S;


/* ͨ��Դͨ��buffer�ṹ�嶨��*/
typedef struct tagSOCP_SRC_SETBUF_S
{
    BSP_U32             u32InputStart;      /* ����ͨ����ʼ��ַ*/
    BSP_U32             u32InputEnd;        /* ����ͨ��������ַ*/
    BSP_U32             u32RDStart;         /* RD buffer��ʼ��ַ*/
    BSP_U32             u32RDEnd;           /* RD buffer������ַ*/
    BSP_U32             u32RDThreshold;     /* RD buffer�����ϱ���ֵ*/
}SOCP_SRC_SETBUF_S;

/* ͨ��Ŀ��ͨ��buffer�ṹ�嶨��*/
typedef struct tagSOCP_DST_SETBUF_S
{
    BSP_U32             u32OutputStart;     /* ���ͨ����ʼ��ַ*/
    BSP_U32             u32OutputEnd;       /* ���ͨ��������ַ*/
    BSP_U32             u32Threshold;       /* ���ͨ������ֵ */
}SOCP_DST_SETBUF_S;

/* ����Դͨ���ṹ�嶨��*/
typedef struct tagSOCP_CODER_SRC_CHAN_S
{
    BSP_U32                 u32DestChanID;      /* Ŀ��ͨ��ID*/
    BSP_U32                 u32BypassEn;        /* ͨ��bypassʹ��*/
    SOCP_DATA_TYPE_E        eDataType;          /* �������ͣ�ָ�����ݷ�װЭ�飬���ڸ��ö�ƽ̨*/
    SOCP_DATA_TYPE_EN_E     eDataTypeEn;        /* ��������ʹ��λ*/
    SOCP_ENC_DEBUG_EN_E     eDebugEn;           /* ����λʹ��*/
    SOCP_ENCSRC_CHNMODE_E   eMode;              /* ͨ������ģʽ*/
    SOCP_CHAN_PRIORITY_E    ePriority;          /* ͨ�����ȼ�*/
    SOCP_SRC_SETBUF_S       sCoderSetSrcBuf;
}SOCP_CODER_SRC_CHAN_S;

/* ����Ŀ�����ýṹ�嶨��*/
typedef struct tagSOCP_CODER_DEST_CHAN_S
{
    BSP_U32                 u32EncDstThrh;     /* ����Ŀ��ͨ����ֵ���ޣ��ٲ�ͨ��ʱʹ��*/
    SOCP_DST_SETBUF_S       sCoderSetDstBuf;
}SOCP_CODER_DEST_CHAN_S;

/* ����Դͨ���ṹ�嶨��*/
typedef struct tagSOCP_DECODER_SRC_CHAN_S
{
    SOCP_DATA_TYPE_EN_E     eDataTypeEn;        /* ��������ʹ��λ*/
    SOCP_DECSRC_CHNMODE_E   eMode;              /* ͨ��ģʽ*/
    SOCP_SRC_SETBUF_S       sDecoderSetSrcBuf;
}SOCP_DECODER_SRC_CHAN_S;

/* ����Ŀ��ͨ���ṹ�嶨��*/
typedef struct tagSOCP_DECODER_DEST_CHAN_S
{
    BSP_U32                 u32SrcChanID;       /* ������Դͨ��ID*/
    SOCP_DATA_TYPE_E        eDataType;          /* �������ͣ�ָ�����ݷ�װЭ�飬���ڸ��ö�ƽ̨*/
    SOCP_DST_SETBUF_S       sDecoderDstSetBuf;
}SOCP_DECODER_DEST_CHAN_S;

/* ͨ��buffer�����ṹ�嶨��*/
typedef struct tagSOCP_BUFFER_RW_S
{
    BSP_CHAR    *pBuffer;                        /* bufferָ��*/
    BSP_U32     u32Size;                        /* ����buffer��С*/
    BSP_CHAR    *pRbBuffer;                      /* �ؾ�bufferָ��*/
    BSP_U32     u32RbSize;                      /* �ؾ�buffer��С*/
}SOCP_BUFFER_RW_S;

/* ����Դͨ����������ṹ�嶨��*/
typedef struct tagSOCP_DECODER_ERROR_CNT_S
{
    BSP_U32     u32PktlengthCnt;                /* �������������*/
    BSP_U32     u32CrcCnt;                      /* CRCУ��������*/
    BSP_U32     u32DataTypeCnt;                 /* �����������ͼ���������*/
    BSP_U32     u32HdlcHeaderCnt;               /* 0x7EУ�����*/
}SOCP_DECODER_ERROR_CNT_S;

/* ����Դ����ͨ�����ýṹ�� */
typedef struct tagSOCP_ENCSRC_RSVCHN_SCOPE_S
{
    BSP_U32                 u32RsvIDMin;        /*����Դ����ͨ��ID��Сֵ*/
    BSP_U32                 u32RsvIDMax;        /*����Դ����ͨ��ID���ֵ*/
}SOCP_ENCSRC_RSVCHN_SCOPE_S;

/* SOCPͶƱ��� */
enum SOCP_VOTE_ID_ENUM
{
    SOCP_VOTE_GU_OM_APP,    /* GU OM APP */
    SOCP_VOTE_GU_OM_COMM,   /* GU OM COMM*/
    SOCP_VOTE_GU_DSP,       /* GU DSP */
    SOCP_VOTE_DIAG_APP,     /* DIAG APP,����DRV APP */
    SOCP_VOTE_DIAG_COMM,    /* DIAG COMM,����LDSP��DRV COMM */
    SOCP_VOTE_DIAG_DEC,     /* DIAG���� */
    SOCP_VOTE_ID_BUTT
};
typedef unsigned int SOCP_VOTE_ID_ENUM_U32;

/* SOCPͶƱ���� */
enum SOCP_VOTE_TYPE_ENUM
{
    SOCP_VOTE_FOR_SLEEP,    /* ����˯�� */
    SOCP_VOTE_FOR_WAKE,     /* ����˯�� */
    SOCP_VOTE_TYPE_BUTT
};
typedef unsigned int SOCP_VOTE_TYPE_ENUM_U32;

typedef BSP_S32 (*socp_event_cb)(BSP_U32 u32ChanID, SOCP_EVENT_E u32Event, BSP_U32 u32Param);
typedef BSP_S32 (*socp_read_cb)(BSP_U32 u32ChanID);
typedef BSP_S32 (*socp_rd_cb)(BSP_U32 u32ChanID);

/* log2.0 2014-03-19 Begin:*/
typedef struct SOCP_ENC_DST_BUF_LOG_CFG
{
    BSP_U32     guWaterMark;    /* SOCP����Ŀ��ͨ�����ݴ���ˮ�ߣ�GUͨ�� */
    BSP_U32     lWaterMark;     /* SOCP����Ŀ��ͨ�����ݴ���ˮ�ߣ�Lͨ�� */
    BSP_U32     overTime;       /* SOCP����Ŀ��ͨ�����ݴ��䳬ʱʱ�� */
    BSP_U32     flushFlag;      /* SOCP����Ŀ��ͨ���������������־ */
    BSP_U32     logOnFlag;      /* LOG2.0����������־ */
} SOCP_ENC_DST_BUF_LOG_CFG_STRU;
/* log2.0 2014-03-19 End*/

/**************************************************************************
  ��������
**************************************************************************/
/*****************************************************************************
* �� �� ��  : DRV_SOCP_INIT
*
* ��������  : ģ���ʼ������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��ʼ���ɹ��ı�ʶ��
*****************************************************************************/
BSP_S32 DRV_SOCP_INIT(BSP_VOID);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_CORDER_SET_SRC_CHAN
 ��������  : �˽ӿ����SOCP������Դͨ���ķ��䣬���ݱ�����Դͨ����������ͨ�����ԣ�����Ŀ��ͨ�������غ���ִ�н����
 �������  : pSrcAttr:������Դͨ�������ṹ��ָ�롣
             pSrcChanID:���뵽��Դͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:����Դͨ������ɹ���
             SOCP_ERROR:����Դͨ������ʧ�ܡ�
*****************************************************************************/
BSP_S32 DRV_SOCP_CORDER_SET_SRC_CHAN(SOCP_CODER_SRC_ENUM_U32 enSrcChanID, SOCP_CODER_SRC_CHAN_S *pSrcAttr);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_CODER_SET_DEST_CHAN_ATTR
 ��������  : �˽ӿ����ĳһ����Ŀ��ͨ�������ã����غ���ִ�еĽ����
 �������  : u32DestChanID:SOCP��������Ŀ��ͨ��ID��
             pDestAttr:SOCP������Ŀ��ͨ�������ṹ��ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:����Ŀ��ͨ�����óɹ���
             SOCP_ERROR:����Ŀ��ͨ������ʧ�ܡ�
*****************************************************************************/
BSP_S32 DRV_SOCP_CODER_SET_DEST_CHAN_ATTR(BSP_U32 u32DestChanID, SOCP_CODER_DEST_CHAN_S *pDestAttr);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_DECODER_SET_DEST_CHAN
 ��������  : �˽ӿ����SOCP������Ŀ��ͨ���ķ��䣬
             ���ݽ���Ŀ��ͨ����������ͨ�����ԣ�
             ������Դͨ�������غ���ִ�н����
 �������  : pAttr:������Ŀ��ͨ�������ṹ��ָ��
             pDestChanID:���뵽��Ŀ��ͨ��ID
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:����Ŀ��ͨ������ɹ���
             SOCP_ERROR:����Ŀ��ͨ������ʧ�ܡ�
*****************************************************************************/
BSP_S32 DRV_SOCP_DECODER_SET_DEST_CHAN(SOCP_DECODER_DST_ENUM_U32 enDestChanID, SOCP_DECODER_DEST_CHAN_S *pAttr);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR
 ��������  : �˽ӿ����ĳһ����Դͨ�������ã����غ���ִ�еĽ����
 �������  : u32SrcChanID:������Դͨ��ID
             pInputAttr:������Դͨ�������ṹ��ָ��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:����Դͨ�����óɹ�
             SOCP_ERROR:����Դͨ������ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_DECODER_SET_SRC_CHAN_ATTR ( BSP_U32 u32SrcChanID,SOCP_DECODER_SRC_CHAN_S *pInputAttr);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_DECODER_GET_ERR_CNT
 ��������  :�˽ӿڸ�������ͨ���������쳣����ļ���ֵ��
 �������  : u32ChanID:������ͨ��ID
                         pErrCnt:�������쳣�����ṹ��ָ��
 �������  : �ޡ�
 �� �� ֵ      : SOCP_OK:�����쳣�����ɹ�
                             SOCP_ERROR:�����쳣����ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_DECODER_GET_ERR_CNT (BSP_U32 u32ChanID, SOCP_DECODER_ERROR_CNT_S *pErrCnt);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_FREE_CHANNEL
 ��������  : �˽ӿڸ���ͨ��ID�ͷŷ���ı����ͨ����
 �������  : u32ChanID:ͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:ͨ���ͷųɹ���
             SOCP_ERROR:ͨ���ͷ�ʧ�ܡ�
*****************************************************************************/
BSP_S32 DRV_SOCP_FREE_CHANNEL(BSP_U32 u32ChanID);

/*****************************************************************************
* �� �� ��  : DRV_SOCP_CLEAN_ENCSRC_CHAN
*
* ��������  : ��ձ���Դͨ����ͬ��V9 SOCP�ӿ�
*
* �������  : enSrcChanID       ����ͨ����
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK
*****************************************************************************/
BSP_U32 DRV_SOCP_CLEAN_ENCSRC_CHAN(SOCP_CODER_SRC_ENUM_U32 enSrcChanID);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_REGISTER_EVENT_CB
 ��������  : �˽ӿ�Ϊ����ͨ��ע���¼��ص�������
 �������  : u32ChanID:ͨ��ID��
             EventCB:�¼��ص��������ο�socp_event_cb��������
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:ע���¼��ص������ɹ���
             SOCP_ERROR:ע���¼��ص�����ʧ�ܡ�
*****************************************************************************/
BSP_S32 DRV_SOCP_REGISTER_EVENT_CB(BSP_U32 u32ChanID, socp_event_cb EventCB);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_START
 ��������  : �˽ӿ�����Դͨ��������������߽��롣
 �������  : u32SrcChanID:Դͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:�������������ɹ���
             SOCP_ERROR:������������ʧ�ܡ�
*****************************************************************************/
BSP_S32 DRV_SOCP_START(BSP_U32 u32SrcChanID);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_STOP
 ��������  : �˽ӿ�����Դͨ����ֹͣ������߽��롣
 �������  : u32SrcChanID:Դͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��������ֹͣ�ɹ���
             SOCP_ERROR:��������ֹͣʧ�ܡ�
*****************************************************************************/
BSP_S32 DRV_SOCP_STOP(BSP_U32 u32SrcChanID);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_SET_TIMEOUT
 ��������  : �˽ӿ����ó�ʱ��ֵ��
 �������  : u32Timeout:��ʱ��ֵ

 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:���ó�ʱʱ����ֵ�ɹ���
             SOCP_ERROR:���ó�ʱʱ����ֵʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_SET_TIMEOUT (SOCP_TIMEOUT_EN_E eTmOutEn, BSP_U32 u32Timeout);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_SET_DEC_PKT_LGTH
 ��������  : ���ý�������ȼ���ֵ
 �������  : pPktlgth:��������ȼ�ֵ

 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:���óɹ���
             ����ֵ:����ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_SET_DEC_PKT_LGTH(SOCP_DEC_PKTLGTH_S *pPktlgth);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_SET_DEBUG
 ��������  : ���ý���Դͨ����debugģʽ
 �������  : u32ChanID:ͨ��ID
             u32DebugEn: debug��ʶ
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:���óɹ���
             ����ֵ:����ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_SET_DEBUG(BSP_U32 u32DestChanID, BSP_U32 u32DebugEn);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_CHAN_SOFT_RESET
 ��������  : Դͨ����λ
 �������  : u32ChanID:ͨ��ID
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:�踴λ�ɹ���
             ����ֵ:��λʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_CHAN_SOFT_RESET(BSP_U32 u32ChanID);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_GET_WRITE_BUFF
 ��������  : �˽ӿ����ڻ�ȡд����buffer��
 �������  : u32SrcChanID:Դͨ��ID
             pBuff:           :д����buffer

 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��ȡд����buffer�ɹ���
             SOCP_ERROR:��ȡд����bufferʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_GET_WRITE_BUFF( BSP_U32 u32SrcChanID, SOCP_BUFFER_RW_S *pBuff);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_WRITE_DONE
 ��������  : �ýӿ��������ݵ�д�������ṩд�����ݵĳ��ȡ�
 �������  : u32SrcChanID:Դͨ��ID
             u32WrtSize:   ��д�����ݵĳ���
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:д�����ݳɹ���
             SOCP_ERROR:д������ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_WRITE_DONE(BSP_U32 u32SrcChanID, BSP_U32 u32WrtSize);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_REGISTER_RD_CB
 ��������  : �ýӿ�����ע���RD�������ж�ȡ���ݵĻص�������
 �������  : u32SrcChanID:Դͨ��ID
             RdCB:  �¼��ص�����
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:ע��RD���λ����������ݻص������ɹ���
             SOCP_ERROR:ע��RD���λ����������ݻص�����ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_REGISTER_RD_CB(BSP_U32 u32SrcChanID, socp_rd_cb RdCB);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_GET_RD_BUFFER
 ��������  : �ô˽ӿ����ڻ�ȡRD buffer������ָ�롣
 �������  : u32SrcChanID:Դͨ��ID
             pBuff:  RD buffer
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��ȡRD���λ������ɹ�
             SOCP_ERROR:��ȡRD���λ�����ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_GET_RD_BUFFER( BSP_U32 u32SrcChanID,SOCP_BUFFER_RW_S *pBuff);

/*****************************************************************************
 �� �� ��  : bsp_socp_read_rd_done
 ��������  : �˽ӿ������ϲ�֪ͨSOCP��������RD buffer��ʵ�ʶ�ȡ�����ݡ�
 �������  : u32SrcChanID:Դͨ��ID
             u32RDSize:  ��RD buffer��ʵ�ʶ�ȡ�����ݳ���
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��ȡRDbuffer�е����ݳɹ�
             SOCP_ERROR:��ȡRDbuffer�е�����ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_READ_RD_DONE(BSP_U32 u32SrcChanID, BSP_U32 u32RDSize);

/*****************************************************************************
 �� �� ��  : bsp_socp_register_read_cb
 ��������  : �ýӿ�����ע������ݵĻص�������
 �������  : u32DestChanID:Ŀ��ͨ��ID
             ReadCB: �¼��ص�����
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:ע������ݻص������ɹ�
             SOCP_ERROR:ע������ݻص�����ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_REGISTER_READ_CB( BSP_U32 u32DestChanID, socp_read_cb ReadCB);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_GET_READ_BUFF
 ��������  : �ô˽ӿ����ڻ�ȡ�����ݻ�����ָ�롣
 �������  : u32DestChanID:Ŀ��ͨ��ID
             ReadCB: ������buffer
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��ȡ�����ݻ������ɹ���
             SOCP_ERROR:��ȡ�����ݻ������ɹ���
*****************************************************************************/
BSP_S32 DRV_SOCP_GET_READ_BUFF(BSP_U32 u32DestChanID,SOCP_BUFFER_RW_S *pBuffer);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_READ_DATA_DONE
 ��������  : �ýӿ������ϲ����SOCP��������Ŀ��ͨ���ж��ߵ�ʵ�����ݡ�
 �������  : u32DestChanID:Ŀ��ͨ��ID
             u32ReadSize: �Ѷ������ݵĳ���
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:�����ݳɹ���
             SOCP_ERROR:������ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_READ_DATA_DONE(BSP_U32 u32DestChanID,BSP_U32 u32ReadSize);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_SET_BBP_ENABLE
 ��������  : ʹ�ܻ�ֹͣBBPͨ����
 �������  : bEnable:ͨ��ID
 �������  : �ޡ�
 �� �� ֵ      : SOCP_OK:���óɹ���
                   ����ֵ:����ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_SET_BBP_ENABLE(int bEnable);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_SET_BBP_DS_MODE
 ��������  : ����BBP DSͨ�������������ģʽ��
 �������  : eDsMode:DSͨ���������ʱ����ģʽ����
 �������  : �ޡ�
 �� �� ֵ      : SOCP_OK:���óɹ���
                   ����ֵ:����ʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_SET_BBP_DS_MODE(SOCP_BBP_DS_MODE_E eDsMode);

/*****************************************************************************
* �� �� ��  : DRV_SOCP_DSPCHN_START
* ��������  : enable DSP channel
* �������  : 
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
BSP_VOID  DRV_SOCP_DSPCHN_START(BSP_VOID);


/*****************************************************************************
* �� �� ��  : DRV_SOCP_DSPCHN_STOP
* ��������  : disable DSP channel
* �������  : 
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
BSP_VOID  DRV_SOCP_DSPCHN_STOP(BSP_VOID);

/*****************************************************************************
* �� �� ��  : DRV_SOCP_GET_STATE
*
* ��������  : ��ȡSOCP״̬
*
* �� �� ֵ  : SOCP_IDLE    ����
*             SOCP_BUSY    æµ
*****************************************************************************/
SOCP_STATE_ENUM_UINT32  DRV_SOCP_GET_STATE(BSP_VOID);

/*****************************************************************************
* �� �� ��  : DRV_BBPDMA_DRX_BAK_REG
* ��������  : BBPDMA����
* �������  : 
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
BSP_S32  DRV_BBPDMA_DRX_BAK_REG(BSP_VOID);

/*****************************************************************************
* �� �� ��  : DRV_BBPDMA_DRX_RESTORE_REG
* ��������  : �ָ�BBPDMA
* �������  : 
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/
BSP_S32  DRV_BBPDMA_DRX_RESTORE_REG(BSP_VOID);

/*****************************************************************************
* �� �� ��  : bsp_socp_enc_dst_buf_flush
* ��������  : SOCP����Ŀ��buffer���������������
* �������  : ��
* �������  : ��
* �� �� ֵ  :
*****************************************************************************/

BSP_S32 DRV_SOCP_ENC_DST_BUF_FLUSH(BSP_VOID);

#define BSP_SOCP_EncDstBufFlush() DRV_SOCP_ENC_DST_BUF_FLUSH()

BSP_U32  DRV_SOCP_INIT_LTE_DSP(BSP_U32 ulChanId,BSP_U32 ulPhyAddr,BSP_U32 ulSize);

BSP_U32  DRV_SOCP_INIT_LTE_BBP_LOG(BSP_U32 ulChanId,BSP_U32 ulPhyAddr,BSP_U32 ulSize);

BSP_U32  DRV_SOCP_INIT_LTE_BBP_DS(BSP_U32 ulChanId,BSP_U32 ulPhyAddr,BSP_U32 ulSize);

BSP_VOID DRV_SOCP_ENABLE_LTE_BBP_DSP(BSP_U32 ulChanId);

BSP_VOID BSP_SOCP_RefreshSDLogCfg(BSP_U32 ulTimerLen);

/*****************************************************************************
* �� �� ��  : DRV_SOCP_VOTE
* ��������  : SOCPͶƱ�ӿڣ�����ͶƱ�������SOCP�Ƿ�˯�ߣ��ýӿ�ֻ��A���ṩ
* �������  : id --- ͶƱ���ID��type --- ͶƱ����
* �������  : ��
* �� �� ֵ  : BSP_S32 0 --- ͶƱ�ɹ���0xFFFFFFFF --- ͶƱʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_VOTE(SOCP_VOTE_ID_ENUM_U32 id, SOCP_VOTE_TYPE_ENUM_U32 type);

/*****************************************************************************
* �� �� ��  : DRV_SOCP_VOTE_TO_MCORE
* ��������  : SOCPͶƱ�ӿڣ��ýӿ�ֻ��C���ṩ������LDSP�״μ��ص�SOCP�ϵ�����
* �������  : type --- ͶƱ����
* �������  : ��
* �� �� ֵ  : BSP_S32 0 --- ͶƱ�ɹ���0xFFFFFFFF --- ͶƱʧ��
*****************************************************************************/
BSP_S32 DRV_SOCP_VOTE_TO_MCORE(SOCP_VOTE_TYPE_ENUM_U32 type);

#ifdef __cplusplus
}
#endif

#endif /* end of _DRV_SOCP_H*/

