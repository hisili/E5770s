
#ifndef _OM_PRIVATE_H_
#define _OM_PRIVATE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "om.h"
#include "omrl.h"
#include "product_config.h"
#include "cpm.h"
#include "TtfOamInterface.h"
#include "WasOmInterface.h"
#include "OmToolInterface.h"
#include "SOCPInterface.h"
#include "OmApp.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*���NV�����ķ���ֵ*/
#define  NV_GET_RETURN(errNo, nvId) do {\
                VOS_UINT32 ulNvId = (VOS_UINT32)nvId;\
                ulNvId <<= 16;\
                errNo  = ulNvId | errNo;\
            }while(0)\

/*Э��ջģ���������*/
#define OM_MAX_PS_MODULE_NUM                      (VOS_PID_BUTT - VOS_PID_DOPRAEND)

/*������Ϣȫ���򿪣����ý��й��ˣ�����TRACE,EVENT*/
#define OM_ALL_MSG_ON                             0xffffffff
/*WPHY MailBox�����Ƶ�ǰHPA���͸�OM����Ϣ��û�б�OM���������*/
#define DSP_SEND_OM_MSG_MAX_NUM                   (VOS_FID_QUEUE_LENGTH - 110)
/*Used to control sequence number mutex.*/
#define OM_PV_TIMEOUT                             5000
/*ֵΪOM_APP_READ_NV_STRU�ṹ���У�sizeof(ulErrorCode) + sizeof(ulCount)*/
#define OM_READ_NV_HEAD_SIZE                      8
/*����ΪNVID��ֵ+NVID������ռ�ڴ泤��*/
#define OM_NV_ITEM_SIZE                           4
/*����FuncId�ķ��仮�֣�30������ΪOM����ʹ�ã�����30Ϊ�ⲿ��ϵͳʹ��*/
#define OM_FUNCID_PART_NUM                        30
#define OM_FUNCID_ACPU_PART_NUM                   45
#define OM_FUNCID_MAX_NUM                         60
/*The size of the password*/
#define OM_PASSWORD_LEN                           8
/*The type of restoring NV items*/
#define OM_RESTORE_ALL                            0
#define OM_RESTORE_MANUFACTURE                    1
/*���û�û��Ȩ�޽��в���ʱ�����صĴ�����*/
#define OM_NEED_AUTH                              20
/*����װ�����ߵİ汾��ѯ����Ϊ�ڲ��汾���ⲿ�汾*/
#define OM_INSIDE_VER                             0
#define OM_OUTSIDE_VER                            1
/*����OM_FACTORY_VER_STRU�ṹ�еİ汾����*/
#define OM_FACTORY_VER_LEN                        32
/*����OM_FACTORY_VER_STRU�ṹ�е�CDROM�汾����*/
#define OM_CDROM_VER_LEN                          128
/*IMEI�����NV���еĳ���*/
#define OM_IMEI_NV_LEN                            16
/*���ظ����߲��IMEI���*/
#define OM_IMEI_LEN                               9
/*��ѯ�ڴ�����ʹ�õ��ڴ����*/
#define OM_MAX_MEMORY_ADDR_CNT                    8

/*��2bit������ָʾ��ǰ��Ϣ������Modem�����������FuncIDֻ�к�6Bit*/
#define OM_FUNCID_VALUE_BITS                      (0x3F)

/*���ڻ�ȡ��2Bit��Modem ID ��ֵ*/
#define OM_GET_FUNCID_MODEMINFO(ucFuncID)           ((ucFuncID>>6)&0x3)
#define OM_ADD_FUNCID_MODEMINFO(ucFuncID, ucModemID)(ucFuncID|((ucModemID<<6)&0xc0))

#if (FEATURE_ON == FEATURE_MULTI_FS_PARTITION)
#define OAM_ICC_RECORD_MAX_NUM           (1024)
#else
#define OAM_ICC_RECORD_MAX_NUM           (1)
#endif

#define OAM_ICC_RECORD_MAX_FILE          (20)

#define OM_ICC_MAX_NAME_LEN              (40)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*Query PA attribute*/
enum
{
    OM_W_PA_TEMP = 1,
    OM_G_PA_TEMP,
    OM_W_PLL_LOCK,
    OM_G_PLL_LOCK,
    OM_W_HKADC,
    OM_G_HKADC,
    OM_W_BBP_PLL_LOCK,
    OM_G_BBP_PLL_LOCK,
    OM_DSP_PLL_LOCK,
    OM_ARM_PLL_LOCK,
    OM_SIM_TEMP,
    OM_TCM_STATUS,
    OM_SDMMC_STATUS,
    OM_BATTER_VOLT,
    OM_BATTER_TEMP,
    OM_OLED_TEMP,
    OM_DCXO_TEMP,
    OM_DCXO_TEMP_LT,
    OM_OLED_BUTT
};

/*Ӳ������*/
typedef enum
{
    ID_OM_PMU_STATUS = 1,
    ID_OM_ABB_STATUS,
    ID_OM_SPI_STATUS,
    ID_OM_I2C_STATUS,
    ID_OM_SIC_STATUS,
    ID_OM_BUTT
}OM_HARDWARE_STATUS_ENUM;

typedef enum
{
    LEVEL_NORMAL = 0,
    LEVEL_ADVANCED,
    LEVEL_BUTT
}OM_PRIVILEGE_LEVEL_ENUM;

typedef enum
{
    OM_FILE_TIMER = 1,     /*����ָʾ�����ļ�ʱ�����ĳ�ʱ��ʱ��*/
    OM_ICC_TIMER,
    OM_BUFF_TIMER,
    OM_ERRLOG_TIMER,

    OM_FILE_TIMER_BUTT
}OM_TIMER_NAME_ENUM;

/* the definition of error number which results in reboot ,created by xucheng*/

enum
{
    LOG_FROM_PS_LOG = 0,        /* ps_log �����log */
    LOG_FROM_PRINTF,             /* printf �����log */
    LOG_FROM_OM,                /* om �����log     */
    LOG_SOURCE_BUTT
};

/* the definition of error number which results in reboot ,created by xucheng*/

enum
{
    OAM_PROTECTION_LOAD_DSP         = 0x20000000,
    OAM_PROTECTION_DSP_Init         = 0x20000001,
    OAM_UL_AHB_PARTITION_ERR        = 0x20000002,
    OAM_UL_AHB_LENGTH_ERR           = 0x20000003,
    OAM_DL_R99_AHB_HEAD_ERR         = 0x20000004,
    OAM_UL_R99_AHB_HEAD_ERR         = 0x20000005,
    OAM_DL_PP_AHB_HEAD_ERR          = 0x20000006,
    OAM_UL_PP_AHB_HEAD_ERR          = 0x20000007,
    OAM_DL_NPP_AHB_HEAD_ERR         = 0x20000008,
    OAM_UL_NPP_AHB_HEAD_ERR         = 0x20000009,
    OAM_PARA_CHECK_ERR              = 0x2000000a,
    DRV_CACHEMALLOC_ERR             = 0x2000000b,
    OAM_PROTECTION_DSP_SHARE        = 0x2000000c,
    OAM_USB_SEND_ERROR              = 0x2000000d,
    OAM_LOAD_DSP_BUFFER_ERR         = 0x2000000e,

    DRX_REPORT_ERROR                = 0x2000000f,
    DRX_REPORT_BBP_POWERDOWN_ERROR  = 0x20000010,
    DRX_REPORT_BBP_READ_ERROR       = 0x20000011,
    DRX_ACTIVATEHW_ERROR            = 0x20000012,

    DRV_SOCP_ERROR_START            = 0x20000050,
    DRV_SOCP_ERROR_END              = 0x20000060,
    OAM_REG_REPORT_ERROR_END        = 0x20000070,
    OAM_PC_LENGTH_TOO_BIG           = 0x20000080,
    OAM_PROTECTION_ID_BUTT          = 0x2fffffff
};

/* OM ��event���� */
enum
{
    OAM_EVENT_TIMER        = 5,
    OAM_DEGUG_EVENT_ID1    = 6,
    OAM_DEGUG_EVENT_ID2    = 7,
    OAM_DEGUG_EVENT_ID3    = 8,
    OAM_DEGUG_EVENT_ID4    = 9,

    /* �´ζ���� 100 ��ʼ���� ֮ǰ�ı�ʹ�� */
    OAM_DEGUG_EVENT_ID100  = 100,

    OAM_EVENT_BUTT
};


typedef enum
{
    OM_HSIC_INIT_NOTIFY     = 0x0,

    OM_HSIC_INIT_BUTT
}OM_HSIC_INIT_ENUM;
typedef VOS_UINT32      OM_HSIC_INIT_ENUM_UINT32;

/* ����DRV_CACHEDMAM_ALLOC��������ռ�ʧ�ܣ�ֱ�Ӹ�λ */
#define OM_DRV_CACHEDMAM_ALLOC_ERROR()\
    DRV_SYSTEM_ERROR(DRV_CACHEMALLOC_ERR, (VOS_INT)THIS_FILE_ID, (VOS_INT)__LINE__, VOS_NULL_PTR, 0)

typedef enum
{
    OM_SOCPVOTE_CALLBEGIN   = 0,
    OM_SOCPVOTE_CALLEND     = 1,
    OM_SOCPVOTE_SENDSLEEPMSG= 2,
    OM_SOCPVOTE_SENDWAKEMSG = 3,
    OM_SOCPVOTE_WARNNING    = 4,
    OM_SOCPVOTE_ERROR       = 5,
    OM_SOCPVOTE_FATAL       = 6,
    OM_SOCPVOTE_INFO_BUTT
}OM_SOCPVOTEINFO_ENUM;
typedef VOS_UINT32  OM_SOCPVOTEINFO_ENUM_UINT32;

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
typedef struct
{
    VOS_OM_HEADER
    VOS_UINT16             usPrimId;   /*Indicates current msg type.*/
    VOS_UINT16             usToolId;   /*Not used now.*/
    VOS_UINT8              aucPara[4]; /*Message content.*/
}OM_APP_MSG_EX_STRU;

typedef VOS_UINT32 (*OM_FUN)(APP_OM_MSG_EX_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);

typedef struct
{
    VOS_UINT32  ulPrimId;           /*Indicates current msg type.*/
    OM_FUN      pfFun;              /*Reserves the pointer of function handles current msg.*/
    VOS_UINT32  ulReturnPrimId;     /*Indicates return msg type.*/
}OM_MSG_FUN_STRU;

typedef struct
{
    VOS_UINT32               ulFuncType;
    OM_REQUEST_PROCEDURE    *pOmFuncProc;
    OM_PRIVILEGE_LEVEL_ENUM  enPrivilegeLev;
}OM_FUNCID_PROC_STRU;

typedef struct
{
    OM_APP_HEADER_STRU  stAppHeader;
    VOS_UINT16          usEventId;    /*Indicates current event type.*/
    VOS_UINT16          usReserved;
    VOS_UINT32          ulModuleId;   /*Indicates PID sends current event.*/
    VOS_UINT8           aucPara[4];
}OM_APP_EVENT_STRU;

typedef struct
{
    OM_APP_HEADER_STRU  stAppHeader;
    VOS_UINT16          usPrimId;     /*Indicates current log type.*/
    VOS_UINT16          usReserved;
    VOS_UINT32          ulModuleId;   /*Indicates PID sends current event.*/
    VOS_UINT32          ulPrintLev;   /*Indicates print level.*/
    VOS_UINT8           aucPara[4];
}OM_APP_LOG_STRU;

typedef struct
{
    VOS_UINT16    usSysMsg;       /*0 - ������ϵͳ��Ϣ��1 - ����ϵͳ��Ϣ*/
    VOS_UINT16    usL2Msg;        /*0 - �رղ�2��Ϣ, 1 - �ϱ���2��Ϣ     3 - �ϱ���2����*/
    VOS_UINT32    ulModuleNum;    /* ��Ҫ����ģ�����Ŀ*/
    VOS_UINT32    aulModuleId[OM_MAX_PS_MODULE_NUM];
}OM_TRACE_CONFIG_REQ_STRU;

typedef struct
{
    VOS_UINT32    ulModuleNum;    /* ����Ϊ�ϱ�ģ�����Ŀ, 0Ϊ�رգ�-1Ϊȫ���ϱ�*/
    VOS_UINT32    aulModuleId[OM_MAX_PS_MODULE_NUM];  /*���߲�ֻ�÷����ϱ���ģ�飬�����ϱ��Ĳ�����*/
}OM_TRACE_MASK_CONFIG_REQ_STRU;

typedef struct
{
    VOS_UINT32    ulModuleNum;    /* ����Ϊ�ϱ�ģ�����Ŀ, 0Ϊ�رգ�-1Ϊȫ���ϱ�*/
    VOS_UINT32    aulModuleId[OM_MAX_PS_MODULE_NUM];  /*���߲�ֻ�÷����ϱ���ģ�飬�����ϱ��Ĳ�����*/
}OM_EVENT_CONFIG_TABLE_STRU;

typedef struct
{
    VOS_UINT16    usSysMsg;       /*0 - ������ϵͳ��Ϣ��1 - ����ϵͳ��Ϣ*/
    VOS_UINT16    usL2Msg;        /*0 - �رղ�2��Ϣ, 1 - �ϱ���2��Ϣ     3 - �ϱ���2����*/
    VOS_UINT32    aulRptConfigLevl[OM_MAX_PS_MODULE_NUM]; /*PSģ��Trace��Event�ϱ�״̬ bit0ΪTrace��bit1ΪEvent*/
}OM_TRACE_EVENT_CONFIG_PS_STRU;

/*Log config structs come from last version, I doesn't attend to modify in this version.*/
typedef struct
{
    VOS_UINT32    ulModuleNumber;
    VOS_UINT32    ulSubModuleNumber;
    VOS_UINT32    ulPrintLev;
}OM_MODULE_PRINT_LEV_STRU;

typedef struct
{
    VOS_UINT32 ulCount;	            /*Ҫ��ȡ��NV�����*/
    VOS_UINT16 ausNvItemId[2];      /*Ҫ��ȡ��NV��ID���飬���и���ΪulCount*/
}APP_OM_READ_NV_STRU;

typedef struct
{
    VOS_UINT32 ulErrorCode;        /*����ִ�н��*/
    VOS_UINT32 ulCount;            /*���ص�NV�����*/
    VOS_UINT16 ausNVItemData[2];   /*����NVIDֵ��NVID���ݵĳ��ȡ�NVID������*/
}OM_APP_READ_NV_STRU;

typedef struct
{
    VOS_UINT32 ulCount;             /*Ҫд���NV�����*/
    VOS_UINT16 ausNvItemData[2];    /*����NVIDֵ��NVID���ݵĳ��ȡ�NVID������*/
}APP_OM_WRITE_NV_STRU;

typedef struct
{
    VOS_UINT32          ulErrorCode;    /*����ִ�н��*/
    VOS_UINT16          usCount;        /*���ص�NV�����*/
    VOS_UINT8           ucTotalMsgCnt;  /*����Ϣ�������������ְ��ϱ�ʹ��*/
    VOS_UINT8           ucMsgIndex;     /*��ǰ��Ϣ�������������ְ��ϱ�ʹ��*/
    NV_LIST_INFO_STRU   astNvInfo[1];
}OM_APP_GET_NV_LIST_STRU;

typedef struct
{
    VOS_UINT32          ulErrorCode;        /* �����룺OK/ERR */
    VOS_UINT32          ulProductId;        /* ��Ʒ��         */
    VOS_UINT32          ulCount;            /* ����NV Id����  */
    VOS_UINT16          ausNvFilterList[2]; /* NV Id�б�      */
}OM_APP_GET_NV_FILTER_LIST_STRU;

/*��ѯ��ǰӲ���ķ�������״̬��Ϣ*/
typedef struct
{
   VOS_UINT32 ulNum;
   VOS_UINT32 aulHWId[1];
}APP_OM_APERIODIC_STATUS_STRU;

typedef struct
{
    VOS_UINT32 ulHWId;
    VOS_UINT32 ulHWStatus;
}OM_HW_STATUS_STRU;

typedef struct
{
    VOS_UINT32        ulNum;
    OM_HW_STATUS_STRU astHWStatus[1];
}OM_APP_APERIODIC_STATUS_STRU;
/*��ѯPA���Խṹ��*/
typedef struct
{
    VOS_UINT16        usQueryType;
    VOS_INT16         sQueryResult;
}OM_PA_ITEM_STRU;

typedef struct
{
    VOS_UINT32        ulResult;
    OM_PA_ITEM_STRU   aPaItem[1];
}OM_APP_PA_ATTRIBUTE_STRU;

typedef struct
{
    VOS_OM_HEADER
    VOS_UINT16             usPrimId;   /*Indicates current msg type.*/
    VOS_UINT16             usToolId;   /*Not used now.*/
    VOS_UINT32             ulResult;   /*Result of operation*/
    VOS_UINT8              aucSoftwareVersion[OM_FACTORY_VER_LEN];  /*Software Version*/
    VOS_UINT8              aucHardwareVersion[OM_FACTORY_VER_LEN];  /*Hareware Version*/
    VOS_UINT8              aucProductVersion[OM_FACTORY_VER_LEN];   /*Product Version*/
    VOS_UINT8              aucCdRomVersion[OM_CDROM_VER_LEN];       /*CdRom Version*/
}OM_FACTORY_VER_STRU;

typedef struct
{
    VOS_OM_HEADER
    VOS_UINT16             usPrimId;   /*Indicates current msg type.*/
    VOS_UINT16             usToolId;   /*Not used now.*/
    VOS_UINT32             ulResult;   /*Result of operation*/
    VOS_UINT8              aucIMEI[OM_IMEI_LEN];  /*Software Version*/
    VOS_UINT8              aucResv[3];
}OM_FACTORY_LABEL_STRU;

typedef struct
{
    VOS_UINT32              ulLength;
    VOS_UINT8               aucPassword[OM_PASSWORD_LEN];
}OM_PASSWORD_STRU;

typedef struct
{
    VOS_UINT16              usSysMode;
    VOS_UINT8               ucNvEnable;
    VOS_UINT8               ucFtmMode;
}OM_LMT_MSG_STRU;

typedef struct
{
    VOS_UINT16              usSysMode;
    VOS_UINT16              usRsv;
}OM_ACTIVE_PHY_STRU;

typedef struct
{
    VOS_UINT32                  ulResult;
    VOS_UINT                    ulAllocMemSize;
    VOS_UINT                    ulTotalMemSize;
    VOS_UINT32                  ulMinPid;
    VOS_UINT32                  ulPidNum;
    VOS_MEM_OCCUPYING_INFO_ST   astMemOccupyInfo[1];
}OM_MEMORY_INFO_STRU;

/*NV���б��浱ǰ֧��Ƶ�εĽṹ��*/
typedef struct
{
    VOS_UINT16                  usWBands;
    VOS_UINT16                  usGBands;
}OM_HW_BANDS_STRU;

typedef struct
{
    VOS_UINT16                  usNvId;
    VOS_UINT16                  usLen;
    VOS_CHAR*                   pcNvData;
}OM_RECOVER_NV_INfO;

typedef struct
{
    VOS_UINT32  ulCnt;
    VOS_UINT32  aulAddr[OM_MAX_MEMORY_ADDR_CNT];
}OM_QUERY_MEMORY_STRU;

typedef struct
{
    VOS_UINT16  usEfId;         /* Ҫ��ȡ���ļ���ID */
    VOS_UINT8   ucRecordNum;    /* �ļ��ļ�¼��     */
    VOS_UINT8   ucRsv;
}OM_QUERY_USIMM_STRU;

typedef struct
{
    VOS_UINT16  usEfId;         /* Ҫ��ȡ���ļ���ID */
    VOS_UINT8   ucRecordNum;    /* �ļ��ļ�¼��     */
    VOS_UINT8   ucEfLen;        /* �ļ���¼�ĳ���   */
    VOS_UINT8   aucEf[4];       /* �ļ�������       */
}OM_CONFIG_USIMM_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgName;
}OM_HSIC_INIT_NOTIFY_MSG_STRU;

typedef struct
{
    VOS_UINT16                          usSendPid;
    VOS_UINT16                          usRecvPid;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulSlice;
    VOS_UINT32                          ulReserved;
}OM_ICC_INFO_STRU;

typedef struct
{
    VOS_UINT32                  ulSlice;
    VOS_UINT32                  ulCounter;
}OM_SOCPVOTE_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulResult;           /* ����ֶ� */
    VOS_UINT32                          ulRsv;              /* �����ֶ� */
    VOS_UINT64                          ulSlice;            /* SLICEֵ */
}OM_QUERY_SLICE_CNF_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT16  *g_pusAdcTable;           /*��NV���л��RF���¶�*/
extern VOS_UINT16  *g_pusUsimTempTable;    /*�¶�HKADCת����ϵ��*/
extern VOS_UINT16  *g_pusBatteryTempTable; /*Battery hkadcת����*/
extern VOS_UINT16  *g_pusLedTempTable;      /*LED hkadcת����*/
extern VOS_UINT16  *g_pusDcxoAdcTable;       /*DCXO hkadcת����*/

extern VOS_UINT32                       g_ulAcpuOMSwitchOnOff;
extern VOS_UINT32                       g_ulOMSwitchOnOff;
extern OM_FUNCID_PROC_STRU              g_astAcpuOmFuncIdProcTbl[];
extern OM_FUNCID_PROC_STRU              g_astOmFuncIdProcTbl[];

/*��¼��PC�෢�����ݵ�������Ϣ */
extern OM_UE_PC_SUC_STRU                g_stAcpuUeToPcSucRecord;

/*��¼��PC�෢������ʱ�����ĸ������*/
extern OM_UE_PC_FAIL_STRU               g_stAcpuUeToPcErrRecord;

/*��¼��PC�෢�����ݵ�������Ϣ */
extern OM_UE_PC_SUC_STRU                g_stUeToPcSucRecord;

/*��¼��PC�෢������ʱ�����ĸ������*/
extern OM_UE_PC_FAIL_STRU               g_stUeToPcErrRecord;

extern OM_ACPU_DEBUG_INFO               g_stAcpuDebugInfo;
extern OM_TRACE_EVENT_CONFIG_PS_STRU    g_stAcpuTraceEventConfig;

/*��OMģ���ڲ�ʹ��*/
extern VOS_VOID   OM_SendResult(VOS_UINT8 ucFuncType,
                              VOS_UINT32 ulResult, VOS_UINT16 usReturnPrimId);
extern VOS_VOID   OM_SendContent(VOS_UINT8 ucFuncType, OM_APP_MSG_EX_STRU *pstOmToAppMsg, VOS_UINT16 usReturnPrimId);
extern VOS_UINT32 OM_SendLog(VOS_UINT8 *pucLogData, VOS_UINT32 lLength);
extern VOS_VOID   OM_QueryMsgProc(OM_REQ_PACKET_STRU *pRspPacket, OM_RSP_FUNC *pRspFuncPtr);
extern VOS_VOID   OM_InitAuthVariable(VOS_VOID);
extern VOS_VOID   OM_ConfigMsgProc(OM_REQ_PACKET_STRU *pRspPacket, OM_RSP_FUNC *pRspFuncPtr);
extern VOS_UINT32 OM_ReadNv(APP_OM_MSG_EX_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
extern VOS_UINT32 OM_WriteNv(APP_OM_MSG_EX_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
extern VOS_UINT32 OM_SysCtrlCmd(VOS_UINT16 usClientId, VOS_UINT32 ulMode, MODEM_ID_ENUM_UINT16 enModemID);
extern VOS_UINT32 OM_SetFTMReq(APP_OM_MSG_EX_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
extern VOS_UINT32 OM_QueryModemNumReq(APP_OM_MSG_EX_STRU *pstAppToOmMsg, VOS_UINT16 usReturnPrimId);
extern VOS_UINT32  OM_SysparaGetUsimFileReq(APP_OM_MSG_EX_STRU *pstAppToOmMsg,VOS_UINT16 usReturnPrimId);
extern VOS_UINT32 OM_SysparaSetUsimFileReq(APP_OM_MSG_EX_STRU *pstAppToOmMsg,VOS_UINT16 usReturnPrimId);

/*OM��������ģ���API*/
extern VOS_UINT32 Log_InitFile(VOS_VOID);
extern VOS_VOID   Log_OmMsgProc(OM_REQ_PACKET_STRU *pRspPacket, OM_RSP_FUNC *pRspFuncPtr);
extern VOS_UINT32 Mmc_GetStaVersionInfo(OM_QUERY_VERSION_INFO_STRU * pstStaVersionInfo);

extern VOS_UINT32 Hi_Media_GetVersion( VOS_UINT8* pucBuff, VOS_UINT ulLength);
extern VOS_UINT32 WuepsAgingPidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_VOID   Aging_MsgProc(MsgBlock* pMsg);
extern VOS_UINT32 WuepsRegPidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_VOID   Reg_MsgProc(MsgBlock *pRcvMsg);
extern VOS_BOOL   Sock_IsEnable(VOS_VOID);
extern VOS_VOID   Sock_ServerTask(VOS_VOID);
extern VOS_UINT32 OM_PrintfInit(VOS_VOID);
extern VOS_VOID   OM_PrintfMsgProc(OM_REQ_PACKET_STRU *pstRspPacket, OM_RSP_FUNC *pstRspFuncPtr);
extern VOS_VOID   OM_PrintfTask(VOS_VOID);
extern VOS_INT    OM_RuningPsStateCheckCb(VOS_VOID);
extern VOS_UINT32 OM_QueryDspType(APP_OM_MSG_EX_STRU *pstAppToOmMsg,VOS_UINT16 usReturnPrimId);
extern VOS_VOID   OM_DspTypeInd(VOS_UINT8 ucModemId,VOS_UINT32 ulPhyMode,VOS_UINT16 usReturnPrimId);
extern VOS_UINT32 OM_InitLogFile(VOS_UINT32 ulModuleId, VOS_UINT32 ulFileSize);
extern VOS_UINT32 OM_WriteLogFile(VOS_UINT32 ulModuleId, VOS_CHAR *pcLogData, VOS_UINT32 ulLength);
extern VOS_VOID   OM_RemoveLogFile(VOS_UINT32 ulModuleId);
extern VOS_VOID   OM_PauseLogFile(VOS_UINT32 ulModuleId);
extern VOS_VOID   OM_ResumeLogFile(VOS_UINT32 ulModuleId);
extern VOS_VOID   OM_InitLogPath(void);
extern VOS_VOID   OM_ReadSdMsgProc(OM_REQ_PACKET_STRU *pstRspPacket, OM_RSP_FUNC *pstRspFuncPtr);

extern VOS_UINT32 OMRL_IccDataRecv(VOS_UINT8 *pucData, VOS_UINT16 uslen);

extern VOS_VOID   OM_ComRx_RegisterCB(OM_ICC_CHANNEL_ENUM_UINT32 enPortNum, OM_PORT_READ_DATA_CB pfDataFun);

extern VOS_UINT32 OM_HsicConnectReq(VOS_VOID);

extern VOS_VOID   OM_AcpuQueryMsgProc(OM_REQ_PACKET_STRU *pRspPacket, OM_RSP_FUNC *pRspFuncPtr);

extern VOS_VOID   GU_OamSocpSendDataToUDI(SOCP_CODER_DST_ENUM_U32 enChanID, VOS_UINT8 *pucData, VOS_UINT8 *pucPHYData, VOS_UINT32 ulDataLen);

extern VOS_UINT32 OM_EstablishReq(APP_OM_MSG_EX_STRU *pstAppToOmMsg,
                                           VOS_UINT16 usReturnPrimId);

extern VOS_UINT32 OM_ReleaseReq(APP_OM_MSG_EX_STRU *pstAppToOmMsg,
                                           VOS_UINT16 usReturnPrimId);

extern VOS_VOID OM_NotifyOtherCpuReleaseLink(VOS_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
