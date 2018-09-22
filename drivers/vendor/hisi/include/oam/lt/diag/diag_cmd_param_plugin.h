

#ifndef __DIAG_CMD_PARAM_PLUGIN_H__
#define __DIAG_CMD_PARAM_PLUGIN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile                            
*****************************************************************************/
#include  "vos.h" 
#include  "msp_nv_def.h"
#include  "msp_nv_id.h"
#include  "diag_cmd_id.h" 
#include  "DrvInterface.h"

#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/


/*****************************************************************************
  3 Massage Declare 
*****************************************************************************/


/*****************************************************************************
  4 Enum 
*****************************************************************************/

/* ��������ö��*/
typedef enum
{
    BBP_SAMPLE_COUNTER_MODE =0, /*��������*/
    BBP_SAMPLE_SWITCH_MODE     /*ѭ������*/

}BBP_SAMPLE_TYPE;

/*LOG������ʼ������Ĵ�����־*/
typedef enum
{
    BBP_LOG_SAMPLE_START = 0,
    BBP_LOG_SAMPLE_STOP
}BBP_LOG_SAMPLE_TYPE;

/*���ɿ�ʼ������Ĵ�����־*/
typedef enum
{
    BBP_DATA_SAMPLE_START = 0,
    BBP_DATA_SAMPLE_STOP
}BBP_DATA_SAMPLE_TYPE;


/*****************************************************************************
   5 STRUCT 
*****************************************************************************/

/*****************************************************************************
 ���� :һ��ͷ: SOCPͷ
*****************************************************************************/
typedef struct
{
    VOS_UINT8 usSId;  /* ���������ֽ�ͳ��Service ID*/
    VOS_UINT8 usSSId; /* ����λ*/
    VOS_UINT8 ucServiceSessionId;
    VOS_UINT8 ucMsgType;
    VOS_UINT32 ulMsgTransId;
    VOS_UINT8 aucTimeData[8];
} MSP_SOCP_HEAD_STRU;

/*****************************************************************************
 ���� :����ͷ: DIAGͷ
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulID;         /* �ṹ��ID*/
    VOS_UINT32 ulDataSize;   /* �����ucData�ĳ���*/
    VOS_UINT8  ucData[0];    /* ����������*/
} MSP_DIAG_HEAD_STRU;

/*****************************************************************************
 ���� :����ͷ: DIAG ͷ
 REQ:MSP_DIAG_DATA_REQ_STRU
 CNF:MSP_DIAG_DATA_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulAuid;         /* ԭAUID*/
    VOS_UINT32 ulSn;            /* HSO�ַ�������������*/
    VOS_UINT8  ucData[0];      /* ����������*/
} MSP_DIAG_DATA_REQ_STRU;

typedef MSP_DIAG_DATA_REQ_STRU MSP_DIAG_DATA_CNF_STRU;

typedef struct
{
  VOS_UINT32 ulRet;
}DIAG_CMD_COMMON_CNF;

typedef struct
{
    VOS_UINT32 ulRc;       /* 0: SUCCESS OTHER: FAILUE*/
} DIAG_CMD_DSP_CNF_STRU;

/*****************************************************************************
 ���� : ���ģ��Ĵ�ӡ��������,֧�ֶ���������
ID   : DIAG_CMD_LOG_CAT_PRINT
REQ : DIAG_CMD_LOG_CAT_PRINT_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_PRINT_CNF_STRU
IND : DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulModuleId;   /* ���Ϊ0xFFFFFFFF��ʾΪ����ģ���Level����*/
    VOS_UINT32 ulLevelFilter;    /* ERROR|WARNING|NORMAL|INFO 1: OPEN, 0��CLOSE*/
} DIAG_CMD_LOG_CAT_PRINT_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRc; /* �����*/
    VOS_UINT32 ulModuleId;
} DIAG_CMD_LOG_CAT_PRINT_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulModule; /*  ��ӡ��Ϣ���ڵ�ģ��ID */
    VOS_UINT32 ulLevel;  /* �������*/
    VOS_UINT32 ulNo;     /*  IND���*/
    VOS_INT8 szText[0]; /*  ���д�ӡ�ı����ݣ����ܰ����ļ����к�,��'\0'��β*/
} DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU;


/*****************************************************************************
���� : ���ģ��Ĳ�俪��,֧�ֶ���������
ID   : DIAG_CMD_LOG_CAT_LAYER
REQ : DIAG_CMD_LOG_CAT_LAYER_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_LAYER_CNF_STRU
˵��: ��������������������һ��ģ����󣬾ͻ᷵��ʧ�ܣ�������ȷ��ģ�������Ȼ��洢
IND : DIAG_CMD_LOG_LAYER_IND_STRU
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulModuleId;       /* ģ��ID*/
    VOS_UINT32 ulIsDestModule;   /* 0: ��ʾSource Module�� 1����ʾDest Module*/
    VOS_UINT32 ulSwitch;         /* (0x00000000): �أ�(0x80000000)����*/
} DIAG_CMD_LOG_CAT_LAYER_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRc; /* �����*/
    VOS_UINT32 ulModuleId;
} DIAG_CMD_LOG_CAT_LAYER_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulModule;     /* Դģ��ID*/
    VOS_UINT32 ulDestMod;    /* Ŀ��ģ��ID*/
    VOS_UINT32 ulNo;         /* ���*/
    VOS_UINT32 ulId;         /* ID*/
    VOS_INT8 aucDta[0];     /* �û����ݻ�����*/
} DIAG_CMD_LOG_LAYER_IND_STRU;

/*****************************************************************************
���� : ���AIR���ܿ���,֧�ֶ���������
ID   : DIAG_CMD_LOG_CAT_AIR
REQ : DIAG_CMD_LOG_CAT_AIR_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_AIR_CNF_STRU
IND : DIAG_CMD_LOG_AIR_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulSwitch; /* (0x00000000): �أ�(0x80000000)����*/
    VOS_UINT32 ulGuSwitch;   /*  1����0��*/
} DIAG_CMD_LOG_CAT_AIR_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRc; /* �����*/
} DIAG_CMD_LOG_CAT_AIR_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulModule;     /* Դģ��ID*/
    VOS_UINT32 ulSide;       /* 1: NET-->UE, 2: UE-->NET*/
    VOS_UINT32 ulNo;         /* ���*/
    VOS_UINT32 ulId;         /* ID*/
    VOS_INT8 aucDta[0];     /* �û����ݻ�����*/
} DIAG_CMD_LOG_AIR_IND_STRU;

/*****************************************************************************
���� : ���VoLTE���ܿ���,֧�ֶ���������
ID   : DIAG_CMD_LOG_CAT_EVENT
REQ : DIAG_CMD_LOG_CAT_EVENT_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_EVENT_CNF_STRU
IND : DIAG_CMD_LOG_EVENT_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulModule;     /* Դģ��ID*/
    VOS_UINT32 ulSide;       /* 1: NET-->UE, 2: UE-->NET*/
    VOS_UINT32 ulNo;         /* ���*/
    VOS_UINT32 ulId;         /* ID*/
    VOS_INT8   aucDta[0];    /* �û����ݻ�����*/
} DIAG_CMD_LOG_VoLTE_IND_STRU;
/*****************************************************************************
���� : ���EVENT���ܿ���,֧�ֶ���������
ID   : DIAG_CMD_LOG_CAT_EVENT
REQ : DIAG_CMD_LOG_CAT_EVENT_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_EVENT_CNF_STRU
IND : DIAG_CMD_LOG_EVENT_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulSwitch; 
} DIAG_CMD_LOG_CAT_EVENT_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRc; /* �����*/
    VOS_UINT32 ulSwitch;
} DIAG_CMD_LOG_CAT_EVENT_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulNo;      /* ���*/
    VOS_UINT32 ulId;      /* ��Ϣ�����¼�ID,��Ҫ�����Ϣ,�տ�,�¼�,��ͨ��ӡ���ʱ�ó�ԱΪ��*/
} DIAG_CMD_LOG_EVENT_IND_STRU;

/*****************************************************************************
���� : ���UserPlane ��ϢID����,֧�ֶ���������
ID   : DIAG_CMD_LOG_CAT_USERPLANE
REQ : DIAG_CMD_LOG_CAT_USERPLANE_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_USERPLANE_CNF_STRU
˵��:   ��������������������һ��MSG ID���󣬾ͻ᷵��ʧ��,������ȷ�Ĳ�����Ȼ��洢;
IND : DIAG_CMD_LOG_USERPLANE_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulMsgId;  /* ��ϢID*/
    VOS_UINT32 ulSwitch; /* (0x00000000): �أ�(0x80000000)����*/
} DIAG_CMD_LOG_CAT_USERPLANE_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRc; /* �����*/
    VOS_UINT32 ulMsgId;  /* ��ϢID*/
} DIAG_CMD_LOG_CAT_USERPLANE_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulNo;         /* ���*/
    VOS_UINT32 ulId;         /* ID*/
    VOS_INT8 aucDta[0];     /* �û����ݻ�����*/
} DIAG_CMD_LOG_USERPLANE_IND_STRU;

/*****************************************************************************
���� : �����ϢID/����ID����,֧�ֶ���������
ID   : DIAG_CMD_LOG_CAT_CFG
REQ : DIAG_CMD_LOG_CAT_CFG_REQ_STRU
CNF : DIAG_CMD_LOG_CAT_CFG_CNF_STRU
˵��:   ��������������������һ��MSG ID���󣬾ͻ᷵��ʧ��,������ȷ�Ĳ�����Ȼ��洢;
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulId;       /* ��ϢID/����ID*/
    VOS_UINT32 ulCategory; /* ȡֵΪ DIAG_CMD_LOG_CATETORY_XXX*/
    VOS_UINT32 ulSwitch;   
} DIAG_CMD_LOG_CAT_CFG_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRc;       /* �����*/
    VOS_UINT32 ulId;       /* ��ϢID/����ID*/
} DIAG_CMD_LOG_CAT_CFG_CNF_STRU;


/*****************************************************************************
���� : �����ϢID/����ID����,֧�ֶ���������
ID   : DIAG_CMD_GTR_SET
REQ : DIAG_CMD_GTR_SET_REQ_STRU
CNF : DIAG_CMD_GTR_SET_CNF_STRU
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulGtrDtaSize;
    VOS_UINT8 aucDta[0];
} DIAG_CMD_GTR_SET_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRc; /* �����*/
} DIAG_CMD_GTR_SET_CNF_STRU;

/*****************************************************************************
���� : ��ָ���Ĵ�������
ID   : DIAG_CMD_REG_RD
REQ : DIAG_CMD_REG_RD_REQ_STRU
CNF : DIAG_CMD_REG_RD_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulRegAddr[0];          /* the address to read.*/
} DIAG_CMD_REG_RD_REQ_STRU;      

typedef struct
{
    VOS_UINT32 ulRc;
    VOS_UINT32 ulAddr;
    VOS_UINT32 ulRegValue;
} DIAG_CMD_REG_RD_CNF_PARA_STRU;

/*****************************************************************************
���� : дָ���Ĵ�������
ID   : DIAG_CMD_REG_WR
REQ : DIAG_CMD_REG_WR_REQ_STRU
CNF : DIAG_CMD_REG_WR_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulAddr;            /* ��ַ*/
    VOS_UINT32 ulRegValue;        /* ����*/
    VOS_UINT16 ucBeginBit;	      /* ��ʼ����Чλ*/
    VOS_UINT16 ucEndBit;		  /* ��������Чλ*/
    VOS_UINT32 ulTimeSleep;	      /* ʱ��������ʱ���ã�������չ*/
} DIAG_CMD_REG_WR_PARA_STRU;

typedef struct
{
    DIAG_CMD_REG_WR_PARA_STRU ast[0];
} DIAG_CMD_REG_WR_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRc;
    VOS_UINT32 ulAddr;
} DIAG_CMD_REG_WR_CNF_PARA_STRU;


/*****************************************************************************
���� : ��NV
ID   : DIAG_CMD_NV_RD
REQ : DIAG_CMD_NV_QRY_REQ_STRU
CNF : DIAG_CMD_NV_QRY_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulNVId;                       /* ����ȡ��NV��Id*/
} DIAG_CMD_NV_QRY_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRc;                         /* ����ִ�н���Ƿ�ɹ�, 0��ʾ�ɹ���������Ϊ������*/
    VOS_UINT32 ulNVId;                       /* ��ȡ��NV��Id*/
    VOS_UINT32 ulDataSize;                   /* ��ȡ��NV�����ݵĴ�С*/
    VOS_UINT8  aucData[0];                   /* ��ȡ��NV������*/
} DIAG_CMD_NV_QRY_CNF_STRU;

/*****************************************************************************
���� : дNV
ID   : DIAG_CMD_NV_WR
REQ : DIAG_CMD_NV_WR_REQ_STRU
CNF : DIAG_CMD_NV_WR_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulNVId;                       /* ��Ҫд���NV ID*/
    VOS_UINT32 ulDataSize;                   /* ��Ҫд���NV�����ݵĴ�С*/
    VOS_UINT8  aucData[0];                   /* ���ݻ�����*/
} DIAG_CMD_NV_WR_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRc;                         /* ����ִ�н���Ƿ�ɹ�,0��ʾ�ɹ���������Ϊ������*/
    VOS_UINT32 ulNVId;
} DIAG_CMD_NV_WR_CNF_STRU;

/*****************************************************************************
���� : ����NV
ID   : DIAG_CMD_NV_IMPORT
REQ : DIAG_CMD_NV_FILE_LOAD_REQ_STRU
CNF : DIAG_CMD_NV_FILE_LOAD_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT16 ulBlockIndex;                 /* д����ļ������кţ���0��ʼ*/
    VOS_UINT16 ulTotalBlockCnt;              /* �ܿ���,�ܿ���������MSP_BIN_FILE_MAX_SIZE/DIAG_CMD_MEM_RD_MAX_NUM +1*/
    VOS_UINT32 ulTotalSize;                  /* �ļ��ܴ�С��С��126K*/
    VOS_UINT32 ulBlockSize;                  /* ����д������ݴ�С*/
    VOS_UINT8  aucData[0];                   /* ���ݻ�����*/
} DIAG_CMD_NV_FILE_LOAD_REQ_STRU;


typedef struct
{
    /* �����ϸ�������ִ�н��*/
    /* �������ļ�д����ϣ��򷵻������ļ���ִ�н��*/
    VOS_UINT32 ulRc;

    /*��ֵ�����������HSO�������һ��BLOCK INDEX*/
    /* �����п���ѳɹ�д�룬��INDEXΪDIAG_CMD_TOTAL_FILE(0xFFFFFFFF)*/
    /* �紫��INDEXΪ0������ǰ��д��Ŀ飬��Ϊ�ļ�Ϊ�´���*/
    VOS_UINT32 ulIndex;
} DIAG_CMD_NV_FILE_LOAD_CNF_STRU;


/*****************************************************************************
���� : ����NV
ID   : DIAG_CMD_NV_EXPORT
REQ : DIAG_CMD_NV_EXPORT_FILE_REQ_STRU
CNF : DIAG_CMD_NV_EXPORT_FILE_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulOffset;   /* ����ƫ��*/
    VOS_UINT32 ulType;     /* 0: ������ǰ�ĳ�ʼNV�ļ�; 1: ������ǰ������NV�ļ�*/
} DIAG_CMD_NV_EXPORT_FILE_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRst;
    VOS_UINT32 ulOffset;       /* ����ƫ��,REQ�ṹ���������ƫ��*/
    VOS_UINT32 ulType;         /* �����ļ�����, 0: ������ǰ�ĳ�ʼNV�ļ�; 1: ������ǰ������NV�ļ�*/
    VOS_UINT32 ulRemainSize;   /* ʣ��NV�ļ���С*/
    VOS_UINT32 ulSize;         /* ���ص�ʵ�ʴ�С, ������ DIAG_TRANSFER_BLOCK_MAX_SIZE*/
    VOS_UINT8  aucData[0];
} DIAG_CMD_NV_EXPORT_FILE_CNF_STRU;

/*****************************************************************************
���� : LOG����
ID   : DIAG_CMD_DRX_LOG_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_LOG_SAMPLE_REG_WR_REQ_STRU
CNF : DIAG_CMD_DRX_LOG_SAMPLE_REG_WR_REQ_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
/*����ÿ���·��Ĵ������ݽṹ*/
typedef struct
{
    VOS_UINT32  ulAddr;            /* ��ַ*/
    VOS_UINT32  ulRegValue;        /* �Ĵ���ֵ�����ڲ�ѯ�����Ƿ�����Ĵ�����ԭ����Ĵ�
                                                              ��ֵΪ��ֵʱ��ֹͣ����*/
    VOS_UINT16  ucBeginBit;	      /* ��ʼ����Чλ*/
    VOS_UINT16  ucEndBit;		  /* ��������Чλ*/
    VOS_UINT32  ulSleepTime;       /* ִ�и���ԭ�������ԭ��ǰ������ʱ�䣬������֤�Ĵ�����������ʱ��Ҫ�󣬵�λ�趨Ϊms������ʵ�ʲ����������*/
    VOS_UINT32  ulSn;              /* ��������Ӧ����ֵ, Sn = RowID * GRID_COLUMN_COUNT + ulColID;*/

} DIAG_CMD_DRX_REG_WR_PARA_STRU;

/* �͹���Log�������ݲɼ��·�ԭ��ṹ*/
typedef struct
{
    BBP_LOG_SAMPLE_TYPE  enBBPLogCtrl;        /*log����ʱ���������������ǽ���log����*/
    VOS_UINT32  ulLogChannelIndex;            /*����ģ���Ӧ��Logͨ����ţ��������ļ�������ͨ���ţ��޶�Ϊ0~7*/
    VOS_UINT32  ulTotalRegCount;              /* �·����мĴ�������*/
    VOS_UINT32  ulLogStartRegIndex;           /* �·��Ĵ����У������Ĵ�����ʼ���*/
    VOS_UINT32  ulLogStopRegIndex;            /* �·��Ĵ����У�ֹͣ�Ĵ�����ʼ���*/
    VOS_UINT32  ulSampleStatusRegIndex;       /* �·��Ĵ����У�״̬�Ĵ�����ʼ���*/
    VOS_UINT32  ulAccumlateRegIndex;          /* ����˷��Ͱ��������Ĵ�����ʼ���*/
    DIAG_CMD_DRX_REG_WR_PARA_STRU  stDrxRegPara[0];/*�·��Ĵ�����ʼ��ַ*/
} DIAG_CMD_DRX_LOG_SAMPLE_REG_WR_REQ_STRU;

/* DIAG_CMD_DRX_LOG_SAMPLE_REG_WR_REQ_STRU�����Ӧ��CNF������Sleepģ����յ�������󼴿ɷ��سɹ�*/
typedef struct
{
    VOS_UINT32   ulRet;  /*����ִ�з���ֵ���ɹ�����0��ʧ�ܷ���-1*/
} DIAG_CMD_DRX_LOG_SAMPLE_REG_WR_CNF_STRU;

/* �͹��������������ݲɼ��·�ԭ��ṹ*/
/*****************************************************************************
���� : DATA����
ID   : DIAG_CMD_DRX_DATA_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_DATA_SAMPLE_REG_WR_REQ_STRU
CNF : DIAG_CMD_DRX_DATA_SAMPLE_REG_WR_CNF_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
typedef struct
{
    BBP_DATA_SAMPLE_TYPE  enBBPDataSampleCtrl;  /*������������ɱ�ʶ*/
    BBP_SAMPLE_TYPE enSampleType;               /*�͹��Ĳ�������*/
    VOS_UINT32  ulTotalRegCount;               /*�·����мĴ�������*/
    VOS_UINT32  ulStartSampleRegIndex;         /*�·��Ĵ����У��������ɼĴ�����ʼ���*/
    VOS_UINT32  ulStopSampleRegIndex;          /*�·��Ĵ����У��������ɼĴ�����ʼ���*/
    VOS_UINT32  ulCheckSampleFinishRegIndex;   /*�·��Ĵ����У���ѯ�����Ƿ�����Ĵ�����ʼ���*/
    VOS_UINT32  ulSampleStatusRegIndex;        /*�·��Ĵ����У�����״̬�Ĵ�����ʼ���*/
    DIAG_CMD_DRX_REG_WR_PARA_STRU  stDrxRegPara[0];/*�·��Ĵ�����ʼ��ַ*/
} DIAG_CMD_DRX_DATA_SAMPLE_REG_WR_REQ_STRU;

/* DIAG_CMD_DRX_DATA_SAMPLE_REG_WR_REQ�����Ӧ��CNF������Sleepģ����յ�������󼴿ɷ��سɹ�*/
typedef struct
{
    VOS_UINT32   ulRet;  /*����ִ�з���ֵ���ɹ�����0��ʧ�ܷ���-1*/
} DIAG_CMD_DRX_DATA_SAMPLE_REG_WR_CNF_STRU;


/* ����״̬��Ϣ���ɵ���Sleepģ���ϱ����ϱ�BBP�ɼ����ݵİ����Լ���־λ״̬*/
typedef struct
{
    VOS_UINT32  ulTotalRegCount;                       /*�ϱ����мĴ�������*/
    DIAG_CMD_DRX_REG_WR_PARA_STRU stDrxRegPara[0];     /*�ϱ��Ĵ���*/
}DIAG_CMD_DRX_REG_WR_IND_STRU;

/*�����ĵ͹������ɽṹ�壬data ��log ��ȫͳһ*/
/*****************************************************************************
���� :
ID   : DIAG_CMD_DRX_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_SAMPLE_REG_WR_REQ_STRU
CNF : DIAG_CMD_DRX_SAMPLE_REG_WR_CNF_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulOmDrxSampleId;
	VOS_UINT16 usOpid;
	VOS_UINT16 usPowrDomainBitmap;
	VOS_UINT8  ucDrxRegData[0];
}DIAG_CMD_DRX_SAMPLE_REG_WR_REQ_STRU;

typedef struct
{
    VOS_UINT32   ulRet;  /*����ִ�з���ֵ���ɹ�����0��ʧ�ܷ���-1*/
} DIAG_CMD_DRX_SAMPLE_REG_WR_CNF_STRU;

/*****************************************************************************
���� : ��ȡSOCP\BBP DMA����ַ��
ID   : DIAG_CMD_DRX_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_SAMPLE_GET_ADDR_REQ_STRU
CNF : DIAG_CMD_DRX_SAMPLE_GET_ADDR_CNF_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
typedef enum
{
	DRX_SAMPLE_BBP_DMA_BASE_ADDR = 0x00,
	DRX_SAMPLE_BBP_DBG_BASE_ADDR ,
	DRX_SAMPLE_BBP_SRC_BASE_ADDR ,
	DRX_SAMPLE_POW_ONOFF_CLK_BASE_ADDR ,
	DRX_SAMPLE_SOCP_BASE_ADDR 
}DIAG_CMD_DRX_SAMPLE_ADDR_TYPE_E;

typedef struct
{	
	DIAG_CMD_DRX_SAMPLE_ADDR_TYPE_E eDiagDrxSampleAddr;
}DIAG_CMD_DRX_SAMPLE_GET_ADDR_REQ_STRU;

typedef struct
{
    VOS_UINT32   ulDrxSampleType;
    VOS_UINT32   ulDrxSampleAddr;
    VOS_UINT32   ulRet;  /*����ִ�з���ֵ���ɹ�����0��ʧ�ܷ���-1*/
} DIAG_CMD_DRX_SAMPLE_GET_ADDR_CNF_STRU;

/*****************************************************************************
���� : ����SOCP ����ַ
ID   : DIAG_CMD_DRX_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_SAMPLE_CFG_CHNADDR_REQ_STRU
CNF : DIAG_CMD_DRX_SAMPLE_CFG_CHNADDR_CNF_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
#define DIAG_PRODUCT_VERSION_LENGTH  (16)

typedef struct
{
    VOS_UINT32  ulAddrType; /* config here */
}DIAG_CMD_DRX_SAMPLE_GET_VERSION_REQ_STRU;

typedef struct
{	
	VOS_UINT8   ulProductName[DIAG_PRODUCT_VERSION_LENGTH];
	VOS_UINT8   ulSolutiongName[DIAG_PRODUCT_VERSION_LENGTH];
    VOS_UINT32   ulRet;  /*����ִ�з���ֵ���ɹ�����0��ʧ�ܷ���-1*/
} DIAG_CMD_DRX_SAMPLE_GET_VERSION_CNF_STRU;


/*****************************************************************************
���� : ��ȡSOCP\BBP DMA����ַ��
ID   : DIAG_CMD_DRX_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_SAMPLE_GET_ADDR_REQ_STRU
CNF : DIAG_CMD_DRX_SAMPLE_GET_ADDR_CNF_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
typedef enum
{
	DRX_SAMPLE_BBP_DMA_LOG0_CHNSIZE = 0x00,
	DRX_SAMPLE_BBP_DMA_LOG1_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG2_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG3_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG4_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG5_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG6_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_LOG7_CHNSIZE ,
	DRX_SAMPLE_BBP_DMA_DATA_CHNSIZE 
}DIAG_CMD_DRX_SAMPLE_CHNSIZE_E;

typedef enum
{
	SOCP_BBP_DMA_LOG0_CHNSIZE = 0x10000,
	SOCP_BBP_DMA_LOG1_CHNSIZE = 0x0,
	SOCP_BBP_DMA_LOG_COM_CHNSIZE = 0x2000,
}DIAG_SOCP_SAMPLE_CHNSIZE_E;


typedef struct
{	
	DIAG_CMD_DRX_SAMPLE_CHNSIZE_E eDiagDrxSampleChnSize;
}DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_REQ_STRU;

/* DIAG_CMD_DRX_DATA_SAMPLE_REG_WR_REQ�����Ӧ��CNF������Sleepģ����յ�������󼴿ɷ��سɹ�*/
typedef struct
{
    VOS_UINT32   ulChnType;  /*ͨ������*/
    VOS_UINT32   ulChnAddr;  /*ͨ���ڴ���ʼ��ַ*/
	VOS_UINT32   ulChnSize;  /*ͨ����С*/
    VOS_UINT32   ulRet;      /*����ִ�з���ֵ���ɹ�����0��ʧ�ܷ���-1*/
} DIAG_CMD_DRX_SAMPLE_GET_CHNSIZE_CNF_STRU;


/*****************************************************************************
���� : ʹ��SOCP ͨ��
ID   : DIAG_CMD_DRX_SAMPLE_REG_WR
REQ : DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ_STRU
CNF : DIAG_CMD_DRX_SAMPLE_ABLE_CHN_CNF_STRU
IND : DIAG_CMD_DRX_REG_WR_IND_STRU
*****************************************************************************/
typedef enum
{
	DRX_SAMPLE_SOCP_CHN_ENABLE   = 0x00,
	DRX_SAMPLE_SOCP_CHN_DISABLE  = 0x01
}DIAG_CMD_DRX_SAMPLE_ABLE_CHN_E;

typedef struct
{
	DIAG_CMD_DRX_SAMPLE_ABLE_CHN_E eDiagDrxSampleAbleChn;
}DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ_STRU;

typedef struct
{	
    VOS_UINT32   ulRet;  /*����ִ�з���ֵ���ɹ�����0��ʧ�ܷ���-1*/
} DIAG_CMD_DRX_SAMPLE_ABLE_CHN_CNF_STRU;

/*****************************************************************************
 ���� : HSO����UE�豸
ID   : DIAG_CMD_HOST_CONNECT
REQ  : DIAG_CMD_HOST_CONNECT_REQ_STRU
CNF  : DIAG_CMD_HOST_CONNECT_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulMajorMinorVersion; /* ���汾��.�ΰ汾��*/
    VOS_UINT32 ulRevisionVersion;   /* �����汾��*/
    VOS_UINT32 ulBuildVersion;      /* �ڲ��汾��*/
} DIAG_CMD_UE_SOFT_VERSION_STRU;

typedef struct
{
    VOS_UINT16 usVVerNo;           /* V����*/
    VOS_UINT16 usRVerNo;           /* R����*/
    VOS_UINT16 usCVerNo;           /* C����*/
    VOS_UINT16 usBVerNo;           /* B����*/
    VOS_UINT16 usSpcNo;            /* SPC����*/
    VOS_UINT16 usHardwareVerNo;    /* Ӳ��PCB�ź�ӡ�ư�汾��*/
    VOS_UINT32 ulProductNo;        /* ��Ʒ���ͱ�ţ�����ͬ������ϵ�Ӳ��ƽ̨*/
} DIAG_CMD_UE_BUILD_VER_STRU; /* �ڲ��汾*/

typedef struct
{
    VOS_UINT32 ulRc; /* �����*/
    VOS_CHAR szImei[16];
    DIAG_CMD_UE_SOFT_VERSION_STRU stUeSoftVersion;
    DIAG_CMD_UE_BUILD_VER_STRU stBuildVersion;
    VOS_UINT32 ulChipBaseAddr;
    VOS_UINT32 ulDrxControlFlag;/* B135��������ʾ�͹������԰汾: 1:�͹��İ汾��0�������汾��0xFFFFFFFF:MSP��ȡNV��ʧ�ܣ�HSO����Ϊ���Ӳ��ɹ���������ʾ��Ҫ�����½�������*/
    VOS_UINT32 ulLpdMode;
    NV_ITEM_AGENT_FLAG_STRU stAgentFlag;
} DIAG_CMD_HOST_CONNECT_CNF_STRU;

/*****************************************************************************
 ���� : HSO�Ͽ�����UE�豸
ID   : DIAG_CMD_HOST_DISCONNECT
REQ  : DIAG_CMD_HOST_DISCONNECT_REQ_STRU
CNF  : DIAG_CMD_HOST_DISCONNECT_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulRc; /* �����*/
} DIAG_CMD_HOST_DISCONNECT_CNF_STRU;

/******************************************************************************
���� : �������Ƿ��͸�HSO��Ϊĳ�����ʱʱ����
ID   : DIAG_CMD_TIMER_OUT_IND
IND  : DIAG_CMD_TIMER_OUT_IND_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulCmdID;      /* δ���صĳ�ʱ������*/
} DIAG_CMD_TIMER_OUT_IND_STRU;

/*****************************************************************************
 ���� : ���������������õ���LOG�Ǵ洢������ͨ��USB�ϱ�
ID   : DIAG_CMD_SET_LOG_MODE
REQ : DIAG_CMD_SET_LPD_MODE_REQ_STRU
CNF : DIAG_CMD_SET_LPD_MODE_CNF_STRU
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulSDFileSize;
    VOS_UINT32 ulSDFileSaveTime;
    VOS_UINT8  ucSDFileName[256];
    VOS_UINT32 ulLpdMode;
    VOS_UINT32 ulStartEnd;
} DIAG_CMD_SET_LPD_MODE_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulRc;
    VOS_UINT32 ulSDFileSize;
    VOS_UINT32 ulSDFileSaveTime;
    VOS_UINT8  ucSDFileName[256];
    VOS_UINT32 ulLpdMode;
} DIAG_CMD_SET_LPD_MODE_CNF_STRU;

/*****************************************************************************
 ���� : ��������������ÿ���ļ����ļ�����Ϣ
ID   : DIAG_CMD_FS_SCAN_DIR
REQ : DIAG_CMD_FS_SCAN_DIR_REQ
CNF : DIAG_CMD_FS_SCAN_DIR_CNF
*****************************************************************************/
typedef struct
{
    VOS_CHAR   aucDirName[DIAG_CMD_FILE_NAME_LEN];  /* dir or file name*/
    VOS_INT32      st_mode;                         /* Mode of file */
    VOS_UINT64     st_size;                       /* File size in bytes */
    VOS_INT32      st_atime;                        /* Time of last access */
    VOS_INT32      st_mtime;                        /* Time of last modification */
    VOS_INT32      st_ctime;                        /* Time of last status change */
    VOS_UINT32    ulItemType;                       /*file or folder*/
} DIAG_DIR_FILE_INFO_STRU;

typedef struct
{
    VOS_CHAR szDirectory[MSP_DF_DIR_MAX_LEN];/*ɨ���ļ�����*/
}DIAG_CMD_FS_SCAN_DIR_REQ;

typedef struct
{
    VOS_UINT32  ulRet;                      /*�����*/
    VOS_UINT32  ulDirNum;                   /*ָ��Ŀ¼���ļ�/�ļ�����*/
    VOS_UINT32  ulDirInfoLen;               /*ָ��Ŀ¼���ļ�/�ļ��г���*/
    DIAG_DIR_FILE_INFO_STRU stDirInfo[0];    /*ָ��Ŀ¼���ļ�/�ļ�������*/
}DIAG_CMD_FS_SCAN_DIR_CNF;

/*****************************************************************************
 ���� : ��������������ÿ���ļ����ļ�����Ϣ
ID   : DIAG_CMD_FS_MAKE_DIR
REQ : DIAG_CMD_FS_MAKE_DIR_REQ
CNF : DIAG_CMD_FS_MAKE_DIR_CNF
*****************************************************************************/
typedef struct
{
    VOS_CHAR szDirectory[MSP_DF_DIR_MAX_LEN];  /*�����ļ�����*/
}DIAG_CMD_FS_MAKE_DIR_REQ;

typedef struct
{
    VOS_UINT32  ulRet;              /*�����*/
}DIAG_CMD_FS_MAKE_DIR_CNF;

/*****************************************************************************
 ���� : ��������������ÿ���ļ����ļ�����Ϣ
ID   : DIAG_CMD_FS_DELETE
REQ : DIAG_CMD_FS_DELETE_REQ
CNF : DIAG_CMD_FS_DELETE_CNF
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulItemType;                   /*ɾ���ļ������ļ���*/
    VOS_CHAR szDirectory[MSP_DF_DIR_MAX_LEN]; /*ɾ���ļ�/�ļ�����*/
}DIAG_CMD_FS_DELETE_REQ;

typedef struct
{
    VOS_UINT32  ulRet;                  /*�����*/
}DIAG_CMD_FS_DELETE_CNF;

/*****************************************************************************
 ���� : ������������ѯ��Ŀ¼
ID   : DIAG_CMD_FS_QUERY_DIR
REQ : DIAG_CMD_FS_QUERY_REQ
CNF : DIAG_CMD_FS_QUERY_CNF
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulFolderType;                   /*��ѯ���Ǹ�Ŀ¼��������LOGĿ¼*/
}DIAG_CMD_FS_QUERY_REQ;

typedef struct
{
    VOS_UINT32  ulRet;                          /*�����*/
    VOS_UINT32  ulLength;                       /*Ŀ¼����*/
    VOS_UINT8   aucDirPath[DIAG_CMD_FILE_NAME_LEN];                  /*Ŀ¼��*/
}DIAG_CMD_FS_QUERY_CNF;

/*****************************************************************************
 ���� : �����������򿪻򴴽��ļ�
ID   : DIAG_CMD_FS_OPEN
REQ : DIAG_CMD_FS_OPEN_REQ
CNF : DIAG_CMD_FS_OPEN_CNF
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulMode;                         /*�򿪷�ʽ*/
    VOS_CHAR   szDirectory[MSP_DF_DIR_MAX_LEN]; /*��·��*/
}DIAG_CMD_FS_OPEN_REQ;

typedef struct
{
    VOS_UINT32  ulRet;                          /*�����*/
}DIAG_CMD_FS_OPEN_CNF;

/*****************************************************************************
 ���� : ���������������ļ�
ID   : DIAG_CMD_FS_EXPORT
REQ : DIAG_CMD_FS_EXPORT_REQ
CNF : DIAG_CMD_FS_EXPORT_CNF
*****************************************************************************/


typedef struct
{
    VOS_UINT32 ulRet;           /*�����*/
    VOS_UINT32 ulSize;         /* ���ص�ʵ�ʴ�С, ������ DIAG_TRANSFER_BLOCK_MAX_SIZE*/
    VOS_UINT8  aucData[0];     /*��������*/
}DIAG_CMD_FS_EXPORT_CNF;

/*****************************************************************************
 ���� : ���������������ļ�
ID   : DIAG_CMD_FS_IMPORT
REQ : DIAG_CMD_FS_IMPORT_REQ
CNF : DIAG_CMD_FS_IMPORT_CNF
*****************************************************************************/
typedef struct
{
    VOS_UINT32  ulSize;                         /*�����볤��*/
    VOS_CHAR    acContent[0];                   /*��������*/
}DIAG_CMD_FS_IMPORT_REQ;

typedef struct
{
    VOS_UINT32  ulRet;/**/
}DIAG_CMD_FS_IMPORT_CNF;

/*****************************************************************************
 ���� : ������������ѯʣ�༰ʹ�ÿռ�
ID   : DIAG_CMD_FS_SPACE
REQ : DIAG_CMD_FS_SPACE_REQ
CNF : DIAG_CMD_FS_SPACE_CNF
*****************************************************************************/
typedef struct
{
    VOS_CHAR    szDirectory[MSP_DF_DIR_MAX_LEN];  /*��������*/
}DIAG_CMD_FS_SPACE_REQ;

typedef struct
{
    VOS_UINT32        ulRet;            /*Result of operation*/
    VOS_UINT32        ulDiskSpace;
    VOS_UINT32        ulUsedSpace;
    VOS_UINT32        ulValidSpace;
}DIAG_CMD_FS_SPACE_CNF;

typedef struct
{
    VOS_UINT32 ulReserved;/*����*/
} DIAG_CMD_REPLAY_SET_REQ_STRU;
typedef DIAG_CMD_COMMON_CNF DIAG_CMD_REPLAY_SET_CNF_STRU;
typedef struct
{
    VOS_UINT32 print_level;
} DIAG_bsp_log_swt_cfg_s;

typedef struct
{
    VOS_UINT32 ulRet;
} DIAG_BSP_PRINT_LOG_SWT_CNF_STRU;

typedef struct
{
    VOS_UINT32 trace_type;
    VOS_UINT32 trace_swt;
    VOS_UINT32 period;
} DIAG_BSP_SYVIEW_SWT_CFG_STRU;

typedef struct
{
    VOS_UINT32                task_id;
    VOS_UINT8                  name[12];
} DIAG_BSP_TASK_INFO_STRU;

typedef struct
{
    VOS_UINT32 trace_type;
    VOS_UINT32 ulRet;
    VOS_UINT32 ullen;
    DIAG_BSP_TASK_INFO_STRU st_task_info[0];
} DIAG_BSP_SYVIEW_SWT_CNF_STRU;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of diag_cmd_param_plugin.h */
