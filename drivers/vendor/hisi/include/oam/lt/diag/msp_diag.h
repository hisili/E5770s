

#ifndef __MSP_DIAG_H__
#define __MSP_DIAG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "DrvInterface.h"

#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
/*���PS��MODID ��DIAG_AIR_MSG_LOG_ID�ĵط����滻��DIAG_ID*/
#define DIAG_ID(module_id, log_type)   (VOS_UINT32)(module_id | (log_type << 12))

#define MODID(module_id, log_type) DIAG_ID(module_id, log_type)

#define DIAG_AIR_MSG_LOG_ID(module_id, is_up_link)  DIAG_ID(module_id, is_up_link) /*module_id��ӦPID*/


/*is_up_linkȡֵ*/
#define OS_MSG_UL                (0x01)/* ��ʾ������Ϣ*/
#define OS_MSG_DL                (0x02)/* ��ʾ������Ϣ*/


#define DIAG_SIDE_UE             (0x1)  /* ��ʾUE���յĿտ���Ϣ��NET-->UE*/
#define DIAG_SIDE_NET            (0x2)  /* ��ʾNET���յĿտ���Ϣ��UE-->NET*/


/* �¼���Ϣ��ӡ������*/
#define LOG_TYPE_INFO            0x00000008UL
#define LOG_TYPE_AUDIT_FAILURE   0x00000004UL
#define LOG_TYPE_AUDIT_SUCCESS   0x00000002UL
#define LOG_TYPE_ERROR           0x00000001UL
#define LOG_TYPE_WARNING         0x00000010UL

/*DIAG��ϢID����*/
/*diag fw�����Լ��Ľ�����Ϣ��������*/
#define ID_MSG_DIAG_CMD_REQ_FW_TO_FW                (0x00010001)

/*diag fw����AGENTģ��������Լ���Ӧ�Ļظ���Ϣ*/
#define ID_MSG_DIAG_CMD_REQ_FW_TO_AGENT             (0x00010002)
#define ID_MSG_DIAG_CMD_CNF_AGENT_TO_FW             (0x00010003)
#define ID_MSG_DIAG_HSO_DISCONN_IND                 (0x00010004)

/*diag fw����APP AGENTģ��������Լ���Ӧ�Ļظ���Ϣ*/
#define ID_MSG_DIAG_CMD_REQ_FW_TO_APP_AGENT         (0x00010005)
#define ID_MSG_DIAG_CMD_CNF_APP_AGENT_TO_FW         (0x00010006)

/*diag AGENT����BBP AGENTģ�������*/
#define ID_MSG_REQ_DRX_DATA_SAMPLE_START            (0x00010009)
#define ID_MSG_REQ_DRX_DATA_SAMPLE_STOP             (0x0001000A)
#define ID_MSG_REQ_DRX_LOG_SAMPLE_START             (0x0001000B)
#define ID_MSG_REQ_DRX_LOG_SAMPLE_STOP              (0x0001000C)

#define ID_MSG_DIAG_CMD_IND                         (0x0001000D)

/*diag AGENT����PSģ���HSO�ط�����*/
#define ID_MSG_DIAG_CMD_REPLAY_TO_PS    			(0x00010100)

/*����diag APP AGENT�Ķ˿����ݴ�����ϢID*/
#define ID_MSG_DIAG_CMD_PORT_REQ_TO_APP_AGENT       (0x00010200)

/*����������λʱMSP����Ĳ���ID��СֵΪ:0xB000000*/
#define DIAG_CALLED_IN_IRQ          (0xB0000000)
#define DIAG_REALSE_POINTER_ERROR   (0xB0000001)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
/* ���͸�MSP_PID_DIAG_APP_AGENT��ͶƱ������Ϣ�ṹ�� */
typedef struct
{
    VOS_MSG_HEADER
    SOCP_VOTE_ID_ENUM_U32   ulVoteId;    /* ͶƱ��� */
    SOCP_VOTE_TYPE_ENUM_U32 ulVoteType;  /* ͶƱ���� */
}DIAG_MSG_SOCP_VOTE_REQ_STRU;

/* ����Ʊ��Ϣ�ظ� */
typedef struct
{
    VOS_MSG_HEADER
    SOCP_VOTE_ID_ENUM_U32   ulVoteId;    /* ͶƱ��� */
    SOCP_VOTE_TYPE_ENUM_U32 ulVoteType;  /* ͶƱ���� */
    VOS_UINT32              ulVoteRst;   /* ͶƱ�����0-�ɹ�, 0xFFFFFFFF-ʧ�� */
}DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU;
#endif
/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*��������ֽ���,����ǰ���ļ������кų��ȣ�-1��Ԥ��\0������*/
#define DIAG_PRINTF_MAX_LEN 	(1000-1)

extern VOS_UINT32 DIAG_PrintfV_TDS( VOS_CHAR* pszFmt, ...);

extern VOS_UINT32 DIAG_PrintfV_TDS1( VOS_UINT32 id ,VOS_CHAR* pszFmt, ...);

extern VOS_UINT32 DIAG_PrintfV(VOS_UINT32 id, VOS_CHAR* pszFileName, VOS_UINT32 ulLineNum, VOS_CHAR* pszFmt, ...);

/* ֧�ֵ����������� */
#define LTE_DIAG_PRINTF_PARAM_MAX_NUM   (6)

/* logid���ɹ��� */
#define DIAG_LOG_ID(FILEID, LINE)       (((FILEID & 0x0000FFFF) << 16 )|(LINE & 0x0000FFFF))

/******************************************************************************
��������: LTE_DIAG_LOG
��������: ��ӡ�����͵Ĵ�ӡ�ӿں���
����˵��:
            ulModuleId[in]  : ģ��id����ӦPID
            ulSubModId[in]  : ��ģ��id
            ulLevel[in]     : ��ӡ����
            ulLogId[in]     : ���ļ��ź��кŸ���DIAG_LOG_ID����
            amount[in]      : �ɱ�������������ֵ6��������ulModuleId/ulLevel/ulLogId/amout��
            ...             : �ɱ����
����Լ��:
            1. ���Խ�ֹ�Դ˺������ж��η�װ��ֻ��ת����
            2. ֧�ֿɱ�Ĳ����������������ڵ���ʱ�ɲ���amountָ����������
            3. �ɱ����ֻ֧��int����
            4. Ŀǰ�汾��֧�ֵ�������������6���������Ĳ���Ĭ�϶���
******************************************************************************/
#if 0
extern VOS_INT32 LTE_DIAG_LOG(VOS_UINT32 ulModuleId, VOS_UINT32 ulSubModId, 
                        VOS_UINT32 ulLevel, VOS_UINT32 ulLogId, 
                        VOS_UINT32 amount, ...);
#endif

extern VOS_UINT32 DIAG_ReportEventLog(VOS_UINT32 ulId, VOS_UINT32 ulEventID);



typedef struct
{
    VOS_UINT32 ulId;
    VOS_UINT32 ulMessageID;  /* Specify the message id.*/
    VOS_UINT32 ulSideId;     /* �տ���Ϣ�ķ���*/
    VOS_UINT32 ulDestMod;    /* Ŀ��ģ��*/
    VOS_UINT32 ulDataSize;   /* the data size in bytes.*/
    VOS_VOID* pData;      /* Pointer to the data buffer.*/
} DIAG_AIR_MSG_LOG_STRU;
extern VOS_UINT32 DIAG_ReportAirMessageLog(DIAG_AIR_MSG_LOG_STRU* pRptMessage);



typedef struct
{
    VOS_UINT32 ulId;
    VOS_UINT32 ulMessageID;  /* Specify the message id.*/
    VOS_UINT32 ulSideId;     /* VoLTE��Ϣ�ķ���,0x1:���ൽUE�� 0x2:UE�ൽ���� 0xFFFFFFFF:Ϊ��Чֵ,�����뷽���޹�*/
    VOS_UINT32 ulDestMod;    /* Ŀ��ģ��*/
    VOS_UINT32 ulDataSize;   /* the data size in bytes.*/
    VOS_VOID*  pData;        /* Pointer to the data buffer.*/
} DIAG_VoLTE_LOG_STRU;

extern VOS_UINT32 DIAG_ReportVoLTELog(DIAG_VoLTE_LOG_STRU* pRptMessage);

typedef struct
{
    VOS_UINT8	    ucFuncType;
    VOS_UINT8       ucReserved1;
    VOS_UINT16      usLength;
    VOS_UINT32      ulSn;           /*Sequence Number for Trace, Event, OTA msg.*/
    VOS_UINT32      ulTimeStamp;    /*CPU time coming from ARM.*/
	VOS_UINT16      usPrimId;
    VOS_UINT16      usToolId;
	VOS_UINT16      usOtaMsgID;         /*�տ���Ϣ��ID��*/
    VOS_UINT8       ucUpDown;           /*�տ���Ϣ�ķ���*/
    VOS_UINT8       ucReserved;         /*�߼��ŵ�����*/
    VOS_UINT32      ulLengthASN;        /*�տ���Ϣ���ݵĳ���*/
	VOS_VOID*    pData;                 /* Pointer to the data buffer.*/
} DIAG_GU_AIR_MSG_LOG_STRU;
extern VOS_UINT32 DIAG_ReportGUAirMessageLog(VOS_VOID* pRptMessage,VOS_UINT16 ulMsgLen);



typedef DIAG_AIR_MSG_LOG_STRU DIAG_LAYER_MSG_STRU;

extern VOS_UINT32 DIAG_ReportLayerMessageLog(DIAG_LAYER_MSG_STRU* pRptMessage);



typedef struct
{
    VOS_UINT32 ulMessageID;    /* Specify the message id.*/
    VOS_UINT32 ulDataSize;     /* the data size in bytes.*/
    VOS_VOID* pData;        /* Pointer to the data buffer.*/
} DIAG_USERPLANE_MSG_STRU;

extern VOS_UINT32 DIAG_ReportUserPlaneMessageLog(DIAG_USERPLANE_MSG_STRU* pRptMessage);


extern VOS_UINT32 DIAG_ReportCommand(VOS_UINT16 ulID,VOS_UINT32 ulDataSize,VOS_VOID* pData);



typedef VOS_UINT32 (*DIAG_GTR_DATA_RCV_PFN)(VOS_UINT32 ulGtrDtaSize, VOS_VOID* pGtrData);

extern VOS_VOID DIAG_GtrRcvCallBackReg(DIAG_GTR_DATA_RCV_PFN pfnGtrRcv);


/*�ṩ��AT����*/
VOS_UINT32 diag_LogPortSwitch(VOS_UINT32 ulLogPort);


VOS_UINT32 diag_getLogPort(VOS_VOID);

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)

VOS_UINT32 DIAG_SocpPowerOn(VOS_VOID);


VOS_VOID DIAG_DspInitFinished(VOS_VOID);
#else
static VOS_UINT32 inline DIAG_SocpPowerOn(VOS_VOID)
{
    return 0;
}

static VOS_VOID inline DIAG_DspInitFinished(VOS_VOID)
{
    return;
}
#endif
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

#endif /* end of msp_diag.h */
