

#ifndef __DIAG_CFG_H__
#define __DIAG_CFG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile                            
*****************************************************************************/
#include  "vos.h"  
#include  "VosPidDef.h" 
#include  "diag_cmd_id.h" 
#include "diag_cmd_param_plugin.h"

#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/

#define DIAG_CFG_PID_NUM (VOS_PID_BUTT - VOS_PID_DOPRAEND) 
/*Ϊʹ�����Ϣ֧�������˷��͵���Ϣ�ϱ�,���Ӳ����Ϣģ��ID�ķ�ΧΪ���к�ID�ܺ�*/
#define DIAG_CFG_PID_NUM_EVERY_CORE (256)   /*ÿ���˵�PID����*/
#define DIAG_CFG_CORE_NUM           (6)     /*Ŀǰ�ж��ٺ�*/
#define DIAG_CFG_PID_SUM            (DIAG_CFG_PID_NUM_EVERY_CORE * DIAG_CFG_CORE_NUM)/*���к�PID����*/

#define DIAG_CFG_MODULE_IS_VALID(ulModuleId) ((ulModuleId < VOS_PID_BUTT)&&(ulModuleId >= VOS_PID_DOPRAEND))
#define DIAG_CFG_MODULE_IS_INVALID(ulModuleId) ((ulModuleId >= VOS_PID_BUTT)||(ulModuleId < VOS_PID_DOPRAEND))
/*�����Ϣģ��ID�Ϸ��Լ��*/
#define DIAG_CFG_LAYER_MODULE_IS_VALID(ulModuleId)  ((ulModuleId < DIAG_CFG_PID_SUM)&&(ulModuleId >= 0))
#define DIAG_CFG_LAYER_MODULE_IS_INVALID(ulModuleId) ((ulModuleId >= DIAG_CFG_PID_SUM)||(ulModuleId < 0))

/* DIAG�ѳ�ʼ�� */
#define DIAG_CFG_INIT                0x00000001

/* HSO������ */
#define DIAG_CFG_CONN                0x00000002

/* LT�տ���Ϣ�Ѵ� */
#define DIAG_CFG_LT_AIR              0x00000004

/* GU�տ���Ϣ�Ѵ� */
#define DIAG_CFG_GU_AIR              0x00000008

/* �û��濪���Ѵ� */
#define DIAG_CFG_EVT                 0x00000010

#define DIAG_NOT_SET_USERPALNE_MSGID 0

#define DIAG_CMD_DATA_MAX_LEN              (4096)

/*****************************************************************************
  3 Massage Declare 
*****************************************************************************/


/*****************************************************************************
  4 Enum 
*****************************************************************************/
enum ENUM_DIAG_CFG_BIT
{
    DIAG_CFG_INIT_BIT     = 0,
    DIAG_CFG_CONN_BIT,
    DIAG_CFG_LT_AIR_BIT,              
    DIAG_CFG_GU_AIR_BIT,
    DIAG_CFG_EVENT_BIT,
    DIAG_CFG_BIT_BUTT
};
typedef VOS_UINT32 ENUM_DIAG_CFG_BIT_U32 ; 

/*��䡢�տڡ��û������ݵĿ��ز������º궨�壬ע����U32�ĳ�U8*/
enum ENUM_DIAG_CFG_SWT
{
    DIAG_CFG_SWT_CLOSE  = 0,
    DIAG_CFG_SWT_OPEN,
    DIAG_CFG_SWT_BUTT
};
typedef VOS_UINT8 ENUM_DIAG_CFG_SWT_U8; 

typedef enum
{
    SYSVIEW_MEM_TRACE       = 1,
    SYSVIEW_CPU_INFO        = 2,
    SYSVIEW_TASK_INFO       = 3,
    SYSVIEW_INT_LOCK_INFO   = 4,
    SYSVIEW_SWT_ALL         = 0xff,
    SYSVIEW_SWT_MAX         /* �߽�ֵ */
} BSP_SYSVIEW_TYPE_E;


/*****************************************************************************
   5 STRUCT 
*****************************************************************************/
    


typedef struct
{
    VOS_UINT32 ulId;           // ��ϢID
    VOS_UINT32 ulSwt;          
}DIAG_CFG_LOG_CAT_MSG_CFG_STRU;

typedef struct 
{
    VOS_UINT32 ulCatId;
    VOS_UINT32 ulCfgCnt;
    DIAG_CFG_LOG_CAT_MSG_CFG_STRU astMsgCfgList[DIAG_CFG_CAT_CFG_NUM];
}DIAG_CFG_LOG_CAT_CFG_STRU;

typedef struct
{
    VOS_UINT    ulErrcode;                  /*0:�ɹ� 1:TL ʱ�����ȡʧ�� 2:gU ʱ�����ȡʧ��*/
    VOS_UINT    ulGuTimeStampInitValue;     /*Gu timestamp value*/
    VOS_UINT64  ulTLTimeStampInitValue;     /*TL timestamp value*/
}DIAG_TIMESTAMP_CNF_STRU;
/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern VOS_UINT32 g_ulDiagCfgInfo;
extern VOS_UINT8 g_LayerSrcModuleCfg[DIAG_CFG_PID_SUM] ;
extern VOS_UINT8 g_LayerDecModuleCfg[DIAG_CFG_PID_SUM] ;
extern VOS_UINT8 g_PrintModuleCfg[DIAG_CFG_PID_NUM];
extern VOS_UINT32 g_PrintTotalCfg;
extern DIAG_CMD_LOG_CAT_USERPLANE_REQ_STRU g_stUserPlaneCfg[DIAG_CFG_USER_PLANE_ID_NUM];
extern DIAG_CFG_LOG_CAT_CFG_STRU g_stMsgCfg;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


extern VOS_UINT32 diag_AirCfgProc (VOS_UINT8* pstReq,VOS_UINT32 ulCmdId);
extern VOS_UINT32 diag_CfgProcEntry (VOS_UINT8* pstReq , VOS_UINT32 ulCmdId);
extern VOS_VOID diag_CfgResetAllSwt(VOS_VOID);
extern VOS_UINT32 diag_CfgSetGlobalBitValue(VOS_UINT32* pstDiagGlobal,ENUM_DIAG_CFG_BIT_U32 enBit,ENUM_DIAG_CFG_SWT_U8 enSwtich);
extern VOS_UINT32 diag_CfgSetLayerSwt(DIAG_CMD_LOG_CAT_LAYER_REQ_STRU* pstLayerReq, VOS_UINT32 ulCfgSize);
extern VOS_UINT32 diag_CfgSetMsgSwt(DIAG_CMD_LOG_CAT_CFG_REQ_STRU *pstCatCfgReq,VOS_UINT32 ulCfgSize);
extern VOS_UINT32 diag_CfgSetPrintSwt(DIAG_CMD_LOG_CAT_PRINT_REQ_STRU* pstPrintReq, VOS_UINT32 ulCfgSize);
extern VOS_UINT32 diag_CfgSetUserPlaneSwt(DIAG_CMD_LOG_CAT_USERPLANE_REQ_STRU *pstUserPlaneReq,VOS_UINT32 ulCfgSize);
extern VOS_UINT32 diag_ConnProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId);
VOS_UINT32 diag_GetTimeStampInitValue(VOS_UINT8* pstReq , VOS_UINT32 ulCmdId);
extern VOS_UINT32 diag_ConnProcEntry(VOS_UINT8* pstReq , VOS_UINT32 ulCmdId);
extern VOS_UINT32 diag_DisConnProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId);
extern VOS_UINT32 diag_EventCfgProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId);
extern VOS_UINT32 diag_LayerCfgProc (VOS_UINT8* pstReq,VOS_UINT32 ulCmdId);
extern VOS_UINT32 diag_MsgCfgProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId);
extern VOS_UINT32 diag_PrintCfgProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId);
extern VOS_UINT32 diag_UsrPlaneCfgProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId);
extern VOS_VOID diag_AppAgentTimeOutProcEntry(VOS_VOID* pstPara);





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

#endif /* end of diag_cfg.h */
