

#ifndef __APPRRCINTERFACE_H__
#define __APPRRCINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"
#include  "OmCommon.h"
#include  "PsTypeDef.h"
#include  "LPsFsmState.h"
#include  "LPsTimerState.h"
#include  "AppMmInterface.h"
#include  "AppRrcLteCommonInterface.h"

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define RRC_APP_CELL_MAX_COUNT           (32)
#define RRC_APP_MAX_NUM_OF_MCC           (3)

/* gaojishan */
/*typedef DT_CMD_ENUM_UINT8 APP_CMD_ENUM_UINT8;*/
/*typedef DT_RESULT_ENUM_UINT32 APP_RESULT_ENUM_UINT32;*/

/* RRC����������뵽MAC�յ�rar */
#define PS_OM_EST_PTL_SND_MACRA_TO_RCV_RAR_TIME      (11)           /* 11ms T4-T1 */
/* ��mac�յ�rar��������Ϣ3ʱ�� */
#define PS_OM_EST_PTL_RCV_RAR_TO_SND_MSG3_TIME       (3)            /* 2.5ms T5-T4*/
/* ������Ϣ3���յ�setup��Ϣ */
#define PS_OM_EST_PTL_SND_MSG3_TO_RCV_SETUP_TIME     (73)           /* 28.5ms+2*Ts1c  T6-T5*/
/* ����setup��ϢЭ��ʱ�� */
#define PS_OM_EST_PTL_SETUP_TO_CMPL_TIME             (3)             /* 3ms T7-T6*/
/* ����������뵽����setup cmplЭ��ʱ�� */
#define PS_OM_EST_PTL_RRC_SND_MACRA_TO_CMPL_TIME     (92)            /* 47.5ms+2*Ts1c--(50.5~92.5ms) T7-T1*/
/* �����û���ʱ��Э��ֵ */
#define PS_OM_EST_PTL_USER_PLANE_TIME                (106)            /* 61ms+2*Ts1c+Ts1u--66~106ms T13-T1*/

/* С������Э��ʱ�� */
#define PS_OM_REEST_PTL_SEARCH_CELL_TIME             (100)            /* <100ms */
/* ϵͳ��Ϣ����Э��ʱ�� */
#define PS_OM_REEST_PTL_RCV_SI_TIME                  (1280)           /* <1280ms */
/* ��⵽��·ʧ�ܵ�����С���Ϸ����������Э��ʱ�� */
#define PS_OM_REEST_PTL_RCV_REEST_IND_TO_MACRA       (1500)           /* <1500ms */

/*  ������л���ʼ������Э��ʱ�� */
#define PS_OM_HO_PTL_HO_REQ_TO_CNF                   (1)              /* <1ms T6-T5*/

/* ������������յ�Cnf��Э��ʱ�� */
#define PS_OM_HO_PTL_RRC_MACRA_REQ_TO_MACRA_CNF      (11)             /* 2.5 + 1+ 7.5ms T8-T7*/

/* �����л������Ϣ���յ�ȷ����ϢЭ��ʱ�� */
#define PS_OM_HO_PTL_SND_CMPL_TO_CMPL_CNF            (13)             /* 13ms T10-T9*/

/* �յ��л�������Ϣ�������������Э��ʱ�� */
#define PS_OM_HO_PTL_RCV_RBCFG_TO_MACRA_REQ          (50)             /* 50ms T7-T4*/

/* �յ��л���������Ϣ���ظ������û���ʱ��Э��ʱ�� */
#define PS_OM_HO_PTL_USER_PLANE_TIME                 (100)            /* 100ms T11-T4*/
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
/*****************************************************************************
 ö����    : APP_RRC_MSG_ID_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : RRC <-> APP �ӿ���ϢID
*****************************************************************************/
enum APP_RRC_MSG_ID_ENUM
{
    /* RRC����APP��ԭ�� */
    ID_APP_RRC_TRANSPARENT_CMD_REQ      = (PS_MSG_ID_APP_TO_RRC_BASE + 0x00),   /* _H2ASN_MsgChoice APP_RRC_TRANSPARENT_CMD_REQ_STRU */
    ID_APP_RRC_CELL_MEAS_RPT_REQ        = (PS_MSG_ID_APP_TO_RRC_BASE + 0x01),   /* _H2ASN_MsgChoice APP_RRC_CELL_MEAS_RPT_REQ_STRU */
    ID_APP_RRC_TIME_DELAY_RPT_REQ       = (PS_MSG_ID_APP_TO_RRC_BASE + 0x02),   /* _H2ASN_MsgChoice APP_RRC_TIME_DELAY_RPT_REQ_STRU */
    ID_APP_RRC_INQ_CAMP_CELL_INFO_REQ   = (PS_MSG_ID_APP_TO_RRC_BASE + 0x03),   /* _H2ASN_MsgChoice APP_RRC_INQ_CAMP_CELL_INFO_REQ_STRU */
    ID_APP_RRC_LOCK_WORK_INFO_REQ       = (PS_MSG_ID_APP_TO_RRC_BASE + 0x04),   /* _H2ASN_MsgChoice APP_RRC_LOCK_WORK_INFO_REQ_STRU */
    ID_APP_RRC_CSQ_REQ                  = (PS_MSG_ID_APP_TO_RRC_BASE + 0x05),   /* _H2ASN_MsgChoice APP_RRC_CSQ_REQ_STRU */
    ID_APP_RRC_PTL_STATE_QUERY_REQ      = (PS_MSG_ID_APP_TO_RRC_BASE + 0x06),   /* _H2ASN_MsgChoice APP_RRC_PTL_STATE_QUERY_REQ_STRU */
    ID_APP_RRC_CELL_INFO_QUERY_REQ      = (PS_MSG_ID_APP_TO_RRC_BASE + 0x07),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */
    ID_APP_RRC_LWCLASH_REQ              = (PS_MSG_ID_APP_TO_RRC_BASE + 0x08),   /* _H2ASN_MsgChoice APP_RRC_PTL_LWCLASH_REQ_STRU */
    /* niuxiufan DT begin */
    ID_APP_RRC_SERVING_CELL_INFO_QUERY_REQ   = (PS_MSG_ID_APP_TO_RRC_BASE + 0x09),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */
    ID_APP_RRC_CSEL_INFO_QUERY_REQ           = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0a),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */
    ID_APP_RRC_UE_CAP_INFO_QUERY_REQ         = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0b),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */
    ID_APP_RRC_AC_BARRING_INFO_QUERY_REQ     = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0c),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */
    ID_APP_RRC_DRX_INFO_QUERY_REQ            = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0d),   /* _H2ASN_MsgChoice APP_RRC_CELL_INFO_QUERY_REQ_STRU */

    /* niuxiufan DT end */
    ID_APP_RRC_NMR_REQ                  = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0e),   /* _H2ASN_MsgChoice APP_RRC_NMR_REQ_STRU */
    ID_APP_RRC_CELLID_REQ               = (PS_MSG_ID_APP_TO_RRC_BASE + 0x0f),   /* _H2ASN_MsgChoice APP_RRC_CELLID_REQ_STRU */

    /* gaojishan-dcom-resel-cfg */
    ID_APP_LRRC_RESEL_OFFSET_CFG_NTF         = (PS_MSG_ID_APP_TO_RRC_BASE + 0x10),   /* _H2ASN_MsgChoice APP_LRRC_RESEL_OFFSET_CFG_NTF_STRU  */
    ID_APP_LRRC_CON_TO_IDLE_NTF          = (PS_MSG_ID_APP_TO_RRC_BASE + 0x11),   /* _H2ASN_MsgChoice APP_LRRC_CON_TO_IDLE_NTF_STRU  */
    /* gaojishan-fast-dorm-cfg */
    ID_APP_LRRC_FAST_DORM_CFG_NTF          = (PS_MSG_ID_APP_TO_RRC_BASE + 0x12),   /* _H2ASN_MsgChoice APP_LRRC_FAST_DORM_CFG_NTF_STRU  */
    ID_APP_LRRC_GET_NCELL_INFO_REQ      = (PS_MSG_ID_APP_TO_RRC_BASE + 0x13),   /* _H2ASN_MsgChoice APP_LRRC_GET_NCELL_INFO_REQ_STRU  */

    /* yangfan Prob Begin */
    ID_APP_LRRC_INQ_TCFG_TXPOWER_REQ    = (PS_MSG_ID_APP_TO_RRC_BASE + 0x14),   /* _H2ASN_MsgChoice APP_RRC_INQ_TCFG_TXPOWER_REQ_STRU */
    /* yangfan Prob End */
    ID_APP_RRC_FORCE_HOANDCSEL_REQ        = (PS_MSG_ID_APP_TO_RRC_BASE + 0x15),/*_H2ASN_MsgChoice APP_RRC_FORCE_HOANDCSEL_REQ_STRU*/
    ID_APP_RRC_BARCELL_ACCESS_REQ        = (PS_MSG_ID_APP_TO_RRC_BASE + 0x16),/*_H2ASN_MsgChoice APP_RRC_BARCELL_ACCESS_REQ_STRU*/
    ID_APP_LRRC_SET_UE_REL_VERSION_REQ      = (PS_MSG_ID_APP_TO_RRC_BASE + 0x17), /* _H2ASN_MsgChoice APP_LRRC_SET_UE_REL_VERSION_REQ_STRU  */

    /* APP����RRC��ԭ�� */
    ID_RRC_APP_TRANSPARENT_CMD_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x00),   /* _H2ASN_MsgChoice RRC_APP_TRANSPARENT_CMD_CNF_STRU */
    ID_RRC_APP_TRANSPARENT_CMD_IND      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x01),   /* _H2ASN_MsgChoice NULL */
    ID_RRC_APP_CELL_MEAS_RPT_CNF        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x02),   /* _H2ASN_MsgChoice RRC_APP_CELL_MEAS_RPT_CNF_STRU */
    ID_RRC_APP_CELL_MEAS_RPT_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x03),   /* _H2ASN_MsgChoice RRC_APP_CELL_MEAS_REPORT_IND_STRU */
    ID_RRC_APP_TIME_DELAY_RPT_CNF       = (PS_MSG_ID_RRC_TO_APP_BASE + 0x04),   /* _H2ASN_MsgChoice RRC_APP_TIME_DELAY_RPT_CNF_STRU */
    ID_RRC_APP_TIME_DELAY_RPT_IND       = (PS_MSG_ID_RRC_TO_APP_BASE + 0x05),   /* _H2ASN_MsgChoice RRC_APP_TIME_DELAY_RPT_IND_STRU */
    ID_RRC_APP_INQ_CAMP_CELL_INFO_CNF   = (PS_MSG_ID_RRC_TO_APP_BASE + 0x06),   /* _H2ASN_MsgChoice RRC_APP_INQ_CAMP_CELL_INFO_CNF_STRU */
    ID_RRC_APP_INQ_CAMP_CELL_INFO_IND   = (PS_MSG_ID_RRC_TO_APP_BASE + 0x07),   /* _H2ASN_MsgChoice RRC_APP_INQ_CAMP_CELL_INFO_IND_STRU */
    ID_RRC_APP_LOCK_WORK_INFO_CNF       = (PS_MSG_ID_RRC_TO_APP_BASE + 0x08),   /* _H2ASN_MsgChoice RRC_APP_LOCK_WORK_INFO_CNF_STRU */
    ID_RRC_APP_RPT_DBG_INFO_IND         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x09),   /* _H2ASN_MsgChoice RRC_APP_DEBUG_INFO_STRU */
    ID_RRC_APP_CSQ_CNF                  = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0a),   /* _H2ASN_MsgChoice RRC_APP_CSQ_CNF_STRU */
    ID_RRC_APP_CSQ_IND                  = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0b),   /* _H2ASN_MsgChoice RRC_APP_CSQ_IND_STRU */
    ID_RRC_APP_PTL_STATE_QUERY_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0c),     /* _H2ASN_MsgChoice RRC_APP_PTL_STATE_QUERY_CNF_STRU */
    ID_RRC_APP_PTL_STATE_CHANGE_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0d),     /* _H2ASN_MsgChoice RRC_APP_PTL_STATE_CHANGE_IND_STRU */
    ID_RRC_APP_CELL_INFO_QUERY_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0e),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_LWCLASH_CNF              = (PS_MSG_ID_RRC_TO_APP_BASE + 0x0f),   /* _H2ASN_MsgChoice RRC_APP_PTL_LWCLASH_IND_STRU */
    ID_RRC_APP_LWCLASH_IND              = (PS_MSG_ID_RRC_TO_APP_BASE + 0x10),   /* _H2ASN_MsgChoice RRC_APP_PTL_LWCLASH_CNF_STRU */
    /*niuxiufan DT begin */
    ID_RRC_APP_SERVING_CELL_INFO_QUERY_CNF    = (PS_MSG_ID_RRC_TO_APP_BASE + 0x11),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_SERVING_CELL_INFO_IND    = (PS_MSG_ID_RRC_TO_APP_BASE + 0x12),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_CSEL_INFO_QUERY_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x13),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_LTE_CSEL_INFO_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x14),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */

    ID_RRC_APP_UE_CAP_INFO_QUERY_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x15),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_UE_CAP_INFO_IND            = (PS_MSG_ID_RRC_TO_APP_BASE + 0x16),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_AC_BARRING_INFO_QUERY_CNF  = (PS_MSG_ID_RRC_TO_APP_BASE + 0x17),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_AC_BARRING_INFO_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x18),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */

    ID_RRC_APP_UTRA_CSEL_INFO_IND         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x19),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_GERAN_CSEL_INFO_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1a),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_DRX_INFO_QUERY_CNF         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1b),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    ID_RRC_APP_DRX_INFO_IND               = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1c),   /* _H2ASN_MsgChoice RRC_APP_CELL_INFO_QUERY_CNF_STRU */
    /*niuxiufan DT end */
    ID_RRC_APP_NMR_CNF                    = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1d),   /* _H2ASN_MsgChoice RRC_APP_NMR_CNF_STRU */
    ID_RRC_APP_CELLID_CNF                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1e),   /* _H2ASN_MsgChoice RRC_APP_CELLID_CNF_STRU */
    ID_RRC_APP_GET_NCELL_INFO_CNF       = (PS_MSG_ID_RRC_TO_APP_BASE + 0x1f), /*_H2ASN_MsgChoice LRRC_APP_GET_NCELL_INFO_CNF_STRU*/
	/*add for dcm logger Begin */
    ID_RRC_RPT_EVT_DBG_INFO_IND         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x20),   /* _H2ASN_MsgChoice RRC_APP_DEBUG_INFO_STRU */
    ID_RRC_PTL_TIME_DBG_INFO_IND         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x21),   /* _H2ASN_MsgChoice RRC_APP_DEBUG_INFO_STRU */
   	/*add for dcm logger End */

    ID_RRC_PTL_T310_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x22),
    ID_RRC_PTL_T300_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x23),
    ID_RRC_PTL_T302_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x24),
    ID_RRC_PTL_T303_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x25),
    ID_RRC_PTL_T305_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x26),
    ID_RRC_PTL_T306_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x27),
    ID_RRC_PTL_REEST_T311_DBG_INFO_IND           = (PS_MSG_ID_RRC_TO_APP_BASE + 0x28),
    ID_RRC_PTL_REEST_T301_DBG_INFO_IND           = (PS_MSG_ID_RRC_TO_APP_BASE + 0x29),
    ID_RRC_PTL_T304_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2a),
    ID_RRC_PTL_LOSTCOVERAGE_DBG_INFO_IND         = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2b),
    ID_RRC_PTL_T320_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2c),
    ID_RRC_PTL_IDLE_NORMALHYST_DBG_INFO_IND      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2d),
    ID_RRC_PTL_RESELECTION_DBG_INFO_IND          = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2e),
    ID_RRC_PTL_TBARRED_DBG_INFO_IND              = (PS_MSG_ID_RRC_TO_APP_BASE + 0x2f),
    ID_RRC_PTL_TFORBIDDEN_DBG_INFO_IND           = (PS_MSG_ID_RRC_TO_APP_BASE + 0x30),
    ID_RRC_PTL_GERAN_TBARRED_DBG_INFO_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x31),
    ID_RRC_PTL_GERAN_TFORBIDDEN_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x32),
    ID_RRC_PTL_UTRAN_TBARRED_DBG_INFO_IND        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x33),
    ID_RRC_PTL_UTRAN_TFORBIDDEN_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x34),
    ID_RRC_PTL_G2L_RESEL_PUNISH_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x35),
    ID_RRC_PTL_W2L_REDIR_PUNISH_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x36),
    ID_RRC_PTL_MBMS_MCCH_NOTIFY_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x37),
    ID_RRC_PTL_CMM_MOBILITY_NORMALHYST_DBG_INFO_IND      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x38),
    ID_RRC_PTL_T321_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x39),
    ID_RRC_PTL_SIB_3HOUR_UPDATE_DBG_INFO_IND     = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3a),
    ID_RRC_PTL_PAGING_VALID_TIMER_DBG_INFO_IND   = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3b),
    ID_RRC_APP_CSEL_L_DBG_INFO_IND               = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3c),
    ID_RRC_APP_CSEL_W_DBG_INFO_IND               = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3d),
    ID_RRC_APP_CSEL_G_DBG_INFO_IND               = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3e),
    ID_RRC_APP_SSAC_DBG_INFO_IND                 = (PS_MSG_ID_RRC_TO_APP_BASE + 0x3f),
    ID_LRRC_APP_SET_UE_REL_VERSION_CNF      = (PS_MSG_ID_RRC_TO_APP_BASE + 0x40),/* _H2ASN_MsgChoice LRRC_APP_SET_UE_REL_VERSION_CNF_STRU  */
    ID_APP_RRC_FORCE_HOANDCSEL_CNF        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x41),/* _H2ASN_MsgChoice RRC_APP_FORCE_HOANDCSEL_CNF_STRU */
    ID_APP_RRC_BARCELL_ACCESS_CNF        = (PS_MSG_ID_RRC_TO_APP_BASE + 0x42),/* _H2ASN_MsgChoice RRC_APP_BARCELL_ACCESS_CNF_STRU */
    ID_RRC_APP_SERVING_CELL_CA_INFO_IND          = (PS_MSG_ID_RRC_TO_DT_BASE + 0x12),
    ID_APP_RRC_MSG_ID_BUTT
};
typedef VOS_UINT32    APP_RRC_MSG_ID_ENUM_UINT32;

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 ö����    : APP_RRC_CELL_RPT_PERIOD_ENUM
 ö��˵��  :
*****************************************************************************/
enum APP_RRC_CELL_RPT_PERIOD_ENUM
{
    APP_RRC_CELL_REPORT_PERIOD_300MS = 0,
    APP_RRC_CELL_REPORT_PERIOD_600MS,
    APP_RRC_CELL_REPORT_PERIOD_900MS,
    APP_RRC_CELL_REPORT_PERIOD_1200MS,
    APP_RRC_CELL_REPORT_PERIOD_BUTT
};
typedef VOS_UINT8 APP_RRC_CELL_RPT_PERIOD_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_FILE_NAME_ID_ENUM
 ö��˵��  : RRC�ļ���ö��
*****************************************************************************/
enum RRC_FILE_NAME_ID_ENUM
{
    RrcCmmComm_c,
    RrcCmmDebug_c,
    RrcCmmFsm_c,
    RrcCmmGlobal_c,
    RrcCmmHandover_c,
    RrcCmmL3Ie_c,
    RrcCmmL3msg_c,
    RrcCmmMeasCtrl_c,
    RrcCmmMeasEvaluate_c,
    RrcCmmNcellMeasCfg_c,
    RrcCmmPhy_c,
    RrcCmmSpeedState_c,
    RrcCmmState_c,
    RrcCmmTimer_c,
    RrcCselCellSelect_c,
    RrcCselComm_c,
    RrcCselDebug_c,
    RrcCselEvaluate_c,
    RrcCselFsm_c,
    RrcCselGlobal_c,
    RrcCselInit_c,
    RrcCselLimitCell_c,
    RrcCselMeasure_c,
    RrcCselMobility_c,
    RrcCselMsgSend_c,
    RrcCselPlmnSearch_c,
    RrcCselReselect_c,
    RrcCselSysInfo_c,
    RrcCselTimer_c,
    RrcCselPcCellResel_c,
    RrcCselpcCellSearch_c,
    RrcCselPcComm_c,
    RrcCselpcEntry_c,
    RrcCselPcFsm_c,
    RrcCselpcGlobal_c,
    RrcCselpcPlmnSearch_c,
    RrcCselPcStaChange_c,
    RrcCselpcSysInfoUpdate_c,
    RrcItf_c,
    RrcItfFsm_c,
    RrcItfL2Func_c,
    RrcItfNasSndMsg_c,
    RrcItfPhyFunc_c,
    RrcCommPrint_c,
    RrcMainAsn1_c,
    RrcMainEntry_c,
    RrcMainErmmFsm_c,
    RrcMainErrcFsm_c,
    RrcMainFsmComm_c,
    RrcMainGlobal_c,
    RrcMainPrint_c,
    RrcMainTimer_c,
    RrcOmItf_c,
    RrcRbCfgRcvConfigCnf_c,
    RrcRbEntry_c,
    RrcRbFsm_c,
    RrcRbGlobal_c,
    RrcRbHoRcvConfigCnf_c,
    RrcRbRecfgRcvConfigCnf_c,
    RrcRbReconfigMsgProc_c,
    RrcRbSndMsg_c,
    RrcRbUpdateCtx_c,
    RrcReestConnReest_c,
    RrcReestFsm_c,
    RrcReestGlobal_c,
    RrcReestProcConnReestMsg_c,
    RrcReestSndConfigMsg_c,
    RrcReestTimerHandle_c,
    RrcCcb_c,
    RrcComm_c,
    RrcCommSaveIe_c,
    RrcCommSaveSibIe_c,
    RrcRrcConnAccessCtrl_c,
    RrcRrcConnEst_c,
    RrcRrcConnRel_c,
    RrcRrcConnRelComm_c,
    RrcRrcDebug_c,
    RrcRrcErrorProc_c,
    RrcRrcFsm_c,
    RrcRrcGlobal_c,
    RrcRrcNasCmd_c,
    RrcRrcPaging_c,
    RrcRrcProcRrcConnMsg_c,
    RrcRrcPtlTimerHandle_c,
    RrcRrcSndMsg_c,
    RrcRrcUeCapEnquiry_c,
    RrcRrcUeInfoEnquiry_c,
    RrcSndMsgComm_c,
    RrcSibComm_c,
    RrcSibFsm_c,
    RrcSibGlobal_c,
    RrcSibProc_c,
    RrcSmcFsm_c,
    RrcSmcGlobal_c,
    RrcSmcKeyProc_c,
    RrcSmcMsgProc_c,
    LRrcLRrcIratCommProc_c,
    LRrcLRrcIratReselProc_c,
    LRrcLRrcIratRedirProc_c,
    LRrcLRrcIratCcoProc_c,
    LRrcLRrcIratHoProc_c,
    LRrcLRrcIratPlmnSearchProc_c,
    /* MBMS Begin */
    LRrcMbmsComm_c,
    LRrcMbmsProc_c,
    LRrcMbmsGlobal_c,
    LRrcMbmsSndMsg_c,
    /* MBMS End */

    /* bgs begin */
    LRrcLCselBgFsm_c,
    LRrcLCselBgScan_c,
    LRrcLCselBgGlobal_c,
    /* bgs end */
    RRC_FILE_NAME_ID_BUTT
};

typedef VOS_UINT32 RRC_FILE_NAME_ID_ENUM_UINT32;
/*****************************************************************************
 ö����    : APP_LATENCY_TYPE_ENUM
 ö��˵��  :
*****************************************************************************/
enum APP_LATENCY_TYPE_ENUM
{
    APP_LATENCY_EST =0,               /*���ӽ���ʱ��*/
    APP_LATENCY_HO,                   /*�л�ʱ��*/
    APP_LATENCY_REEST,                /*�ؽ�ʱ��*/
    APP_LATENCY_BUTT
};
typedef VOS_UINT8 APP_LATENCY_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : APP_RRC_LOCK_WORK_INFO_TYPE_ENUM
 ö��˵��  : ����������
*****************************************************************************/
enum APP_RRC_LOCK_WORK_INFO_TYPE_ENUM
{
    RRC_APP_LOCK_FREQPOINT,              /* Ƶ������ */
    RRC_APP_LOCK_FREQANDCELL,            /* Ƶ���С���������� */
    RRC_APP_LOCK_FREQBAND,               /* Ƶ������ */
    RRC_APP_LOCK_BUTT
};
typedef VOS_UINT8 APP_RRC_LOCK_WORK_INFO_TYPE_ENUM_UINT8;
/*****************************************************************************
 ö����    : APP_DELAY_TYPE_ENUM
 ö��˵��  :
*****************************************************************************/
enum APP_DELAY_TYPE_ENUM
{
    APP_DELAY_CONTROL_PLANE =0,     /*������ʱ��*/
    APP_DELAY_USER_PLANE,           /*�û���ʱ��*/
    APP_DELAY_HO,                   /*�л�ʱ��*/
    APP_DELAY_BUTT
};
typedef VOS_UINT8 APP_DELAY_TYPE_ENUM_UINT8;
/*****************************************************************************
 ö����    : APP_CAMPED_FLAG_ENUM
 ö��˵��  :
*****************************************************************************/
enum APP_CAMPED_FLAG_ENUM
{
    APP_CAMPED,                 /* ��פ�� */
    APP_NOT_CAMPED,             /* δפ�� */
    APP_CAMPED_BUTT
};
typedef VOS_UINT8 APP_CAMPED_FLAG_ENUM_UINT8;
/*****************************************************************************
 ö����    : APP_DELAY_TYPE_ENUM
 ö��˵��  :
*****************************************************************************/
enum APP_STATE_FLAG_ENUM
{
    APP_STATE_NOT_IN_RANGE,                 /* ���ڳ�ͻ��Χ��,״̬2 */
    APP_STATE_IN_RANGE,                     /* �ڳ�ͻ��Χ��,״̬1*/
    APP_STATE_BUTT
};
typedef VOS_UINT8 APP_STATE_FLAG_ENUM_UINT8;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : APP_RRC_CELL_MEAS_RPT_REQ_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;
    APP_RRC_CELL_RPT_PERIOD_ENUM_UINT8  enPeriod;
    VOS_UINT8                           aucReserved[2];
}APP_RRC_CELL_MEAS_RPT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_CELL_MEAS_RPT_CNF_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_CELL_MEAS_RPT_CNF_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_CELL_MEAS_RSLT_STRU
 �ṹ˵��  :С���������
*****************************************************************************/
typedef struct
{
    VOS_UINT16 usCellId;
    VOS_INT16  sRSRP;
    VOS_INT16  sRSRQ;
    VOS_INT16  sRSSI;
}RRC_APP_CELL_MEAS_RSLT_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_CELL_MEAS_REPORT_IND_STRU
 �ṹ˵��  :RRCͨ����ԭ�������ϱ�С�����������������
            ��ǰ����ͬƵ����ʱ��RRC�ϱ�С���Ĳ�������������ڣ����ϱ����ݣ�
            �����ǰ������ͬƵ���������������֮������ͬƵ������RRC����֮ǰ��OM���ý����ϱ�С�����������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucCellCnt;                              /* С������ */
    VOS_UINT8                           aucReserved[3];
    RRC_APP_CELL_MEAS_RSLT_STRU         astCellMeasInd[RRC_APP_CELL_MAX_COUNT];
}RRC_APP_CELL_MEAS_REPORT_IND_STRU;

/*****************************************************************************
 �ṹ��    : APP_RRC_TIME_DELAY_RPT_REQ_STRU
 �ṹ˵��  : Ҫ���ϱ�������ʱ�ӡ�������ʱ�ӣ�����RB�����Ŀ���ʱ�䣬���������ӽ�������RB1�����ɹ���ʱ�䡣
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;
    APP_DELAY_TYPE_ENUM_UINT8           enDelayType;
    VOS_UINT8                           aucReserved[2];
}APP_RRC_TIME_DELAY_RPT_REQ_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_TIME_DELAY_RPT_CNF_STRU
 �ṹ˵��  :��ԭ��APP_RRC_TIME_DELAY_RPT_REQ_STRU�Ļظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_DELAY_TYPE_ENUM_UINT8           enDelayType;
    VOS_UINT8                           aucReserved[3];
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_TIME_DELAY_RPT_CNF_STRU;
/* add by guojiyu for tmer delay begin */
#if 0
/*****************************************************************************
 �ṹ��    :RRC_APP_TIME_DELAY_RPT_IND_STRU
 �ṹ˵��  :ʱ��ʱ����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_DELAY_TYPE_ENUM_UINT8           enDelayType;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulBeginTime;                            /*ʱ�ӿ�ʼʱ��:ms*/
    VOS_UINT32                          ulEndTime;                              /*ʱ�ӽ���ʱ��:ms*/
}RRC_APP_TIME_DELAY_RPT_IND_STRU;
#endif
/* add by guojiyu for tmer delay end */
/*****************************************************************************
 �ṹ��    :APP_RRC_INQ_CAMP_CELL_INFO_REQ_STRU
 �ṹ˵��  :��ȡ��ǰפ��С����ID��Ƶ�����Ϣ�Ĳ�ѯ���󣬻���ֹͣ�ϱ�פ��С����Ϣ������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;
    VOS_UINT8                           aucReserved[3];
}APP_RRC_INQ_CAMP_CELL_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_INQ_CAMP_CELL_INFO_CNF_STRU
 �ṹ˵��  :��ԭ��APP_RRC_INQ_CAMP_CELL_INFO_REQ_STRU�Ļظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_INQ_CAMP_CELL_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_INQ_CAMP_CELL_INFO_IND_STRU
 �ṹ˵��  :�ϱ���ǰפ��С����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    PS_BOOL_ENUM_UINT8                  enValueFlag;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT16                          usCellId;
    VOS_UINT16                          usFreqInfo;
}RRC_APP_INQ_CAMP_CELL_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_FREQ_BAND_STRU
 �ṹ˵��  :Ƶ����Χ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLowBand;                              /* Ƶ������ */
    VOS_UINT16                          usHighBand;                             /* Ƶ������ */
}APP_RRC_FREQ_BAND_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_CELL_INFO_STRU
 �ṹ˵��  :С����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellId;                               /* С��ID */
    VOS_UINT16                          usFreqPoint;                            /* Ƶ����Ϣ */
}APP_RRC_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_LOCK_INFO_STRU
 �ṹ˵��  :�����������Ϣ
*****************************************************************************/
typedef struct
{
    APP_RRC_LOCK_WORK_INFO_TYPE_ENUM_UINT8  enLockType;                         /* �������� */
    VOS_UINT8                               ucBandInd;
    union
    {
        VOS_UINT16                      usFreqPoint;                            /* ������Ƶ�� */
        APP_RRC_CELL_INFO_STRU          stFreqAndCell;                          /* ������С��ID��Ƶ�� */
        APP_RRC_FREQ_BAND_STRU          stFreqBand;                             /* ����Ƶ���������� */
    }u;
}APP_RRC_LOCK_INFO_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_LOCK_WORK_INFO_REQ_STRU
 �ṹ˵��  :·���·�����������Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32 ulMsgID;                                     /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;                              /* �������ǽ��� */
    VOS_UINT8                           aucReserved[3];                         /* ����, �˴���2, ����Ϊ��һ���ǵ��ֽ� */
    APP_RRC_LOCK_INFO_STRU              stLockInfo;
}APP_RRC_LOCK_WORK_INFO_REQ_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_LOCK_WORK_INFO_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :��ԭ��APP_RRC_LOCK_WORK_INFO_REQ���лظ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_LOCK_WORK_INFO_CNF_STRU;


/*****************************************************************************
 �ṹ��    : APP_RRC_TRANSPARENT_CMD_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  :͸������ͷ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32 ulMsgId;                                     /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT16 usTransCmdNum;
    VOS_UINT16 usParaSize;
    VOS_UINT8  aucPara[4];
}APP_RRC_TRANSPARENT_CMD_REQ_STRU;


/*****************************************************************************
 �ṹ��    : RRC_APP_TRANSPARENT_CMD_CNF_STRU
 �ṹ˵��  : PS->OMT��͸������ִ�н�����ݽṹ(
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32          ulMsgId;                            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8           aucTransCmdCnf[4];  /*͸���������������ɱ�*/
}RRC_APP_TRANSPARENT_CMD_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_CSELDEBUG_PRINT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usArfcn;
    VOS_UINT16                          usFreq;
    VOS_UINT16                          usCellId;
    VOS_INT16                           sGeranCellRxlev;
    VOS_UINT16                          usNcc;
    VOS_UINT16                          usBcc;
    VOS_UINT8                           ucBandInd;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulTick;
}RRC_CSELDEBUG_PRINT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_CSELDEBUG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    RRC_CSELDEBUG_PRINT_INFO_STRU           stRrcCselDbgInfo;
}RRC_APP_CSELDEBUG_INFO_STRU;

typedef struct
{
    VOS_UINT8    ucRrcProtclState;
    VOS_UINT8    ucPlmntype;
    VOS_UINT8    ucMmTelVoicePresent;
    VOS_UINT8    ucMmTelVideoPresent;
    VOS_UINT16   usAccClassMask;
    VOS_UINT8    ucAcBarringForVoiceSpecialAc;
    VOS_UINT8    ucAcBarringForVideoSpecialAc;
    VOS_UINT8    ucBarringFactorForMMTELVoice;
    VOS_UINT8    ucBarringTimeForMMTELVoice;
    VOS_UINT8    ucBarringFactorForMMTELVideo;
    VOS_UINT8    ucBarringTimeForMMTELVideo;
}RRC_SSACDEBUG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_CSELDEBUG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    RRC_SSACDEBUG_INFO_STRU             stRrcSsacDbgInfo;
}RRC_APP_SSACDEBUG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_DEBUG_PRINT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    RRC_FILE_NAME_ID_ENUM_UINT32        enFileName;
    VOS_UINT32                          ulLineNo;
    RRC_MS_ID_ENUM_UINT16               enMainState;
    RRC_SS_ID_ENUM_UINT16               enSubState;
    RRC_PTL_TI_ENUM_UINT16              enPtlTi;
    RRC_STATE_TI_ENUM_UINT16            enStaTi;
    VOS_UINT32                          ulTick;
    VOS_INT32                           lPara1;
    VOS_INT32                           lPara2;
    VOS_INT32                           lPara3;
    VOS_INT32                           lPara4;
}RRC_DEBUG_PRINT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_DEBUG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    RRC_DEBUG_PRINT_INFO_STRU           stRrcDbgInfo;
}RRC_APP_DEBUG_INFO_STRU;

/*****************************************************************************
 �ṹ��    :PS_APP_HO_LATENCY_DETAIL_STRU
 �ṹ˵��  :�л�ʱ�ӹؼ�����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          T4_ulRrcRcvHoRecfg;
    VOS_UINT32                          ulRrcRcvNasRabmRsp;
    VOS_UINT32                          ulRrcRcvCmmHoCnf;
    VOS_UINT32                          ulRrcRcvStopPdcpCnf;
    VOS_UINT32                          T5_ulRrcSndDspHoReq;
    VOS_UINT32                          T6_ulRrcRcvDspHoCnf;
    VOS_UINT32                          T7_ulRrcSndMacRaReq;
    VOS_UINT32                          T12_ulMacSndPhyAccessReq;
    VOS_UINT32                          T13_ulMacRcvRar;
    VOS_UINT32                          T8_ulRrcRcvMacRaCnf;
    VOS_UINT32                          ulRrcSndSmcSecuCfg;
    VOS_UINT32                          T9_ulRrcSndRecfgCmp;
    VOS_UINT32                          T10_ulRrcRcvAmDataCnf;
    VOS_UINT32                          ulRrcRcvCqiSrsCnf;
    VOS_UINT32                          ulRrcRcvPdcpContineCnf;
    VOS_UINT32                          T11_ulRrcRcvRabmStatusRsp;
}PS_APP_HO_LATENCY_DETAIL_STRU;
/*****************************************************************************
 �ṹ��    :PS_APP_HO_COMP_DETAIL_STRU
 �ṹ˵��  :�л�ʱ����Э��Ա�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRealTestT6T5;
    VOS_UINT32                          ulPtlT6T5;          /* 1ms */
    VOS_UINT32                          ulRealTestT8T7;
    VOS_UINT32                          ulPtlT8T7;          /* 2.5 + 1+ 7.5ms */
    VOS_UINT32                          ulRealTestT10T9;
    VOS_UINT32                          ulPtlT10T9;         /* 13ms */
    VOS_UINT32                          ulRealTestT7T4;
    VOS_UINT32                          ulPtlT7T4;          /* 50ms */
    VOS_UINT32                          ulRealTestT11T4;
    VOS_UINT32                          ulPtlT11T4;         /* 100ms */
}PS_APP_HO_COMP_DETAIL_STRU;
/*****************************************************************************
 �ṹ��    :PS_APP_EST_LATENCY_DETAIL_STRU
 �ṹ˵��  :����ʱ�ӹؼ�����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          T1_ulRrcSndMacRaReq;
    VOS_UINT32                          T2_ulMacSndPhyAccessReq;
    VOS_UINT32                          T4_ulMacRcvRar;
    VOS_UINT32                          ulRrcRcvMacRaCnf;
    VOS_UINT32                          T5_ulMacSndMsg3;
    VOS_UINT32                          T6_ulRrcRcvSetUp;
    VOS_UINT32                          T7_ulRrcSndEstCmp;
    VOS_UINT32                          ulRrcRcvSecCmd;
    VOS_UINT32                          ulRrcSndSecCmdCmp;
    VOS_UINT32                          ulRrcRcvCapEnq;
    VOS_UINT32                          ulRrcSndCapInfo;
    VOS_UINT32                          ulRrcRcvRecfg;
    VOS_UINT32                          T13_ulRrcSndRecfgCmp;
}PS_APP_EST_LATENCY_DETAIL_STRU;
/*****************************************************************************
 �ṹ��    :PS_APP_EST_COMP_STRU
 �ṹ˵��  :����ʱ����Э��Ա�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRealTestT4T1;
    VOS_UINT32                          ulPtlT4T1;              /* 5s + 6ms */
    VOS_UINT32                          ulRealTestT5T4;
    VOS_UINT32                          ulPtlT5T4;              /* 2.5ms */
    VOS_UINT32                          ulTestRealT6T5;
    VOS_UINT32                          ulPtlT6T5;              /* 28.5ms+2*Ts1c */
    VOS_UINT32                          ulRealTestT7T6;
    VOS_UINT32                          ulPtlT7T6;              /* 3ms */
    VOS_UINT32                          ulReaTestlT7T1;
    VOS_UINT32                          ulPtlT7T1;              /* 47.5ms+2*Ts1c */
    VOS_UINT32                          ulReaTestlT13T1;
    VOS_UINT32                          ulPtlT13T1;             /* 61ms+2*Ts1c+Ts1u */
}PS_APP_EST_COMP_DETAIL_STRU;
/*****************************************************************************
 �ṹ��    :PS_APP_REEST_LATENCY_DETAIL_STRU
 �ṹ˵��  :�ؽ�ʱ�ӹؼ�����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          T2_ulRrcRcvReestInd;
    VOS_UINT32                          T3_ulRrcSndCellSearchReq;
    VOS_UINT32                          T4_ulRrcRcvCellSearchInd;
    VOS_UINT32                          T5_ulRrcRcvSi;
    VOS_UINT32                          T6_ulRrcSndCampReq;
    VOS_UINT32                          T7_ulRrcRcvCampCnf;
    VOS_UINT32                          T10_ulRrcSndMacRaReq;
    VOS_UINT32                          ulMacSndPhyAccessReq;
    VOS_UINT32                          ulMacRcvRar;
    VOS_UINT32                          ulRrcRcvMacRaCnf;
    VOS_UINT32                          ulMacSndMsg3;
    VOS_UINT32                          ulRrcRcvReest;
    VOS_UINT32                          ulRrcSndReestCmpl;
}PS_APP_REEST_LATENCY_DETAIL_STRU;

/*****************************************************************************
 �ṹ��    :PS_APP_REEST_COMP_DETAIL_STRU
 �ṹ˵��  :�ؽ�ʱ����Э��Ա�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRealTestT4T3;
    VOS_UINT32                          ulPtlT4T3;              /* 100ms */
    VOS_UINT32                          ulRealTestT5T4;
    VOS_UINT32                          ulPtlT5T4;              /* 1280ms */
    VOS_UINT32                          ulRealTestT10T2;
    VOS_UINT32                          ulPtlT10T2;             /* 1500ms */

}PS_APP_REEST_COMP_DETAIL_STRU;
/*****************************************************************************
 �ṹ��    :RRC_APP_TIME_LATENCY_RPT_IND_STRU
 �ṹ˵��  :ʱ��ʱ����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  T7T4_ulHoCPlaneRealLatency;
    VOS_UINT32                                  ulHoCPlanePtlLatency;
    VOS_UINT32                                  T11T4_ulHoUPlaneRealLatency;
    VOS_UINT32                                  ulHoUPlanePtlLatency;
    PS_APP_HO_LATENCY_DETAIL_STRU               stHoLatencyDetail;
    PS_APP_HO_COMP_DETAIL_STRU                  stHoCompDetail;
}PS_APP_HO_LATENCY_STRU;

/*****************************************************************************
 �ṹ��    :PS_APP_REEST_LATENCY_STRU
 �ṹ˵��  :ʱ��ʱ����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  T10T2_ulReestRealLatency;
    VOS_UINT32                                  ulReestPtlLatency;
    PS_APP_REEST_LATENCY_DETAIL_STRU            stReestLatencyDetail;
    PS_APP_REEST_COMP_DETAIL_STRU               stReestCompDetail;
}PS_APP_REEST_LATENCY_STRU;

/*****************************************************************************
 �ṹ��    :PS_APP_EST_LATENCY_STRU
 �ṹ˵��  :ʱ��ʱ����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  T13T1_ulEstUPlaneRealLatency;
    VOS_UINT32                                  ulEstUPlanePtlLatency;
    VOS_UINT32                                  T7T1_ulEstCPlaneRealLatency;
    VOS_UINT32                                  ulEstCPlanePtlLatency;
    PS_APP_EST_LATENCY_DETAIL_STRU              stEstLatencyDetail;
    PS_APP_EST_COMP_DETAIL_STRU                 stEstCompDetail;
}PS_APP_EST_LATENCY_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_TIME_LATENCY_RPT_IND_STRU
 �ṹ˵��  :ʱ��ʱ����ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;

    APP_LATENCY_TYPE_ENUM_UINT8         enLatencyType;
    VOS_UINT8                           aucReserved[3];
union
    {
        PS_APP_HO_LATENCY_STRU             stHoElapse;
        PS_APP_REEST_LATENCY_STRU          stReestElapse;
        PS_APP_EST_LATENCY_STRU            stEstElapse;
    }u;
} RRC_APP_TIME_DELAY_RPT_IND_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_CSQ_REQ_STRU
 �ṹ˵��  :CSQ��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT16                          usSwt;              /* 0: ֹͣ�����ϱ� 1: ��ѯRSSI��������IND�ϱ�  2: ���������ϱ�RSSI */
    VOS_UINT16                          usPeriod;
    VOS_UINT16                          usNdb;              /* ��Χ 0-5 dbm*/
    VOS_UINT16                          usMs;               /* ��Χ 1-20 s*/
}APP_RRC_CSQ_REQ_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_CSQ_CNF_STRU
 �ṹ˵��  :CSQ��ѯ������Ӧ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usRI;                /*RIֵ*/
    VOS_UINT16                          ausCQI[2];           /* CQI�������� */
    VOS_UINT8                           aucRes[2];

}APP_RRC_CQI_INFO_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_CSQ_CNF_STRU
 �ṹ˵��  :CSQ��ѯ������Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
    VOS_INT16                           sRsrp;              /* RSRP����ֵ��Χ��(-141,-44) */
    VOS_INT16                           sRsrq;              /* RSRQ����ֵ��Χ��(-40, -6) */
    VOS_INT16                           sRssi;              /* RSSI����ֵ */
    VOS_UINT16                          usBer;              /* ������ */
    VOS_INT32                           lSINR;              /* SINR  RS_SNR */
    APP_RRC_CQI_INFO_STRU               stCQI;              /* CQI�������� */
}RRC_APP_CSQ_CNF_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_CSQ_IND_STRU
 �ṹ˵��  :RRC�ϱ���APP������CSQ��ѯָʾ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_INT16                           sRsrp;              /* RSRP����ֵ��Χ��(-141,-44) */
    VOS_INT16                           sRsrq;              /* RSRQ����ֵ��Χ��(-40, -6) */
    VOS_INT16                           sRssi;              /* RSSI����ֵ */
    VOS_UINT16                          usBer;              /* ������ */
    VOS_INT32                           lSINR;              /* SINR  RS_SNR */
    APP_RRC_CQI_INFO_STRU               stCQI;              /* CQI�������� */
}RRC_APP_CSQ_IND_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_PTL_STATE_QUERY_REQ_STRU
 �ṹ˵��  :Э��״̬��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;
    APP_RRC_CELL_RPT_PERIOD_ENUM_UINT8  enPeriod;
    VOS_UINT8                           aucReserved[2];

}APP_RRC_PTL_STATE_QUERY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_PTL_STATE_QUERY_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC�ϱ���Э��״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;             /* MSPֱ�ӽ���ID��ΪCmdID����Prob */
    APP_RESULT_ENUM_UINT32              enResult;
    //VOS_UINT32                          ulCurrentState;     /* RRCЭ��״̬, 0:��ʾIDLE̬ 1:��ʾCONNECTED 2:��ʾЭ��״̬��Ч */
}RRC_APP_PTL_STATE_QUERY_CNF_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_PTL_STATE_CHANGE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC�ϱ���Э��״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                          ulCurrentState;     /* RRCЭ��״̬, 0:��ʾIDLE̬ 1:��ʾCONNECTED 2:��ʾЭ��״̬��Ч */
}RRC_APP_PTL_STATE_CHANGE_IND_STRU;
/*niuxiufan DT begin */
/*****************************************************************************
 �ṹ��    : RRC_APP_PTL_STATE_CHANGE_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RRC�ϱ���Э��״̬
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                          ulCurrentState;     /* RRCЭ��״̬, 0:��ʾIDLE̬ 1:��ʾCONNECTED 2:��ʾЭ��״̬��Ч */
}RRC_APP_DT_PTL_STATE_IND_STRU;

/*niuxiufan DT end */

/*****************************************************************************
 �ṹ��    :APP_RRC_PTL_STATE_QUERY_REQ_STRU
 �ṹ˵��  :С��������Ϣ��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
}APP_RRC_CELL_INFO_QUERY_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_PTL_STATE_QUERY_CNF_STRU
 �ṹ˵��  : RRC�ظ���С��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT16                          usFreq;             /* 0xFFFFΪ��Ч,��λ��100KHz */
    VOS_UINT16                          usPci;              /* 0xFFFFΪ��Ч,��Χ��(0,503) */
    VOS_UINT8                           ucDlBandWidth;      /* 0xffΪ��Ч,��Χ:(0,5): (0 : 1.4M , 1 : 3M , 2 : 5M ,3 : 10M , 4 : 15M, 5 : 20M) */
    VOS_UINT8                           aucReserved[3];
}RRC_APP_CELL_INFO_QUERY_CNF_STRU;

/* niuxiufan DT begin */
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_CMD_ENUM_UINT8                  enCommand;
    APP_RRC_CELL_RPT_PERIOD_ENUM_UINT8  enPeriod;
    VOS_UINT8                           aucReserved[2];
}APP_RRC_INQ_CMD_REQ_STRU;

typedef APP_RRC_INQ_CMD_REQ_STRU APP_RRC_INQ_SERVING_CELL_INFO_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}APP_RRC_INQ_CMD_CNF_HEADER_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgID;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
}APP_RRC_INQ_CMD_IND_HEADER_STRU;

/* niuxiufan DT end */

typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_FORCE_HOANDCSEL_CNF_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32 ulMsgID;                                     /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_CMD_ENUM_UINT8                   enCmd;              /* FORCE HO/CSEL FLAG */
    VOS_UINT8                           ucRsv[3];
    VOS_UINT32                          ulPci;              /* PHY Cell ID */
}APP_RRC_FORCE_HOANDCSEL_REQ_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
}RRC_APP_BARCELL_ACCESS_CNF_STRU;
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32 ulMsgID;                                     /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_CMD_ENUM_UINT8                   enCmd;              /* Bar Cell Access FLAG */
    VOS_UINT8                           ucRsv[3];
}APP_RRC_BARCELL_ACCESS_REQ_STRU;


/*****************************************************************************
 �ṹ��    : APP_RRC_MSG_DATA
 Э����  :
 ASN.1���� :
 �ṹ˵��  : APP_RRC_MSG_DATA���ݽṹ,����ΪRRCר��
*****************************************************************************/
typedef struct
{
    APP_RRC_MSG_ID_ENUM_UINT32          enMsgID;        /*_H2ASN_MsgChoice_Export APP_RRC_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          APP_RRC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}APP_RRC_MSG_DATA;

/*_H2ASN_Length UINT32*/

/*****************************************************************************
 �ṹ��    : AppRrcInterface_MSG
 Э����  :
 ASN.1���� :
 �ṹ˵��  : AppRrcInterface_MSG���ݽṹ,����ΪRRCר��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    APP_RRC_MSG_DATA                    stMsgData;
}AppRrcInterface_MSG;
/*********************************************************
 ö����    : LRRC_LPHY_LTE_BAND_WIDTH_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
**********************************************************/
enum RRC_APP_BAND_WIDTH_ENUM
{
    RRC_APP_LTE_BAND_WIDTH_1D4M = 0,
    RRC_APP_LTE_BAND_WIDTH_3M,
    RRC_APP_LTE_BAND_WIDTH_5M,
    RRC_APP_LTE_BAND_WIDTH_10M,
    RRC_APP_LTE_BAND_WIDTH_15M,
    RRC_APP_LTE_BAND_WIDTH_20M,
    RRC_APP_LTE_BAND_WIDTH_BUTT
};
typedef VOS_UINT16 RRC_APP_BAND_WIDTH_ENUM_UINT16;

/*****************************************************************************
 �ṹ��    : APP_RRC_LWCLASH_REQ_STRU
 �ṹ˵��  :Э��״̬��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
} APP_RRC_LWCLASH_REQ_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_LWCLASH_PARA_STRU
�ṹ˵��  : RRC�ϱ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usUlFreq;          /*��������Ƶ�㵥λ:100Khz*/
    VOS_UINT16                              usDlFreq;          /*��������Ƶ�� ��λ:100Khz*/
    RRC_APP_BAND_WIDTH_ENUM_UINT16          usUlBandwidth;     /*���д��� */
    RRC_APP_BAND_WIDTH_ENUM_UINT16          usDlBandwidth;     /*���д��� */
    APP_CAMPED_FLAG_ENUM_UINT8              enCamped;          /*�Ƿ�פ�� */
    APP_STATE_FLAG_ENUM_UINT8               enState;           /*�Ƿ�Ϊ��ͻ״̬ */
    VOS_UINT8                               usBand;            /*Ƶ��ָʾ */
    VOS_UINT8                               aucResv[1];
} RRC_APP_LWCLASH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_LWCLASH_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;         /* MSPֱ�ӽ���ID��ΪCmdID����Prob */
    RRC_APP_LWCLASH_PARA_STRU       stLWClashPara;
} RRC_APP_LWCLASH_CNF_STRU;
/*****************************************************************************
 �ṹ��    : RRC_APP_LWCLASH_IND_STRU
�ṹ˵��  : RRC�ϱ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    RRC_APP_LWCLASH_PARA_STRU       stLWClashPara;
} RRC_APP_LWCLASH_IND_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_NMR_REQ_STRU
 �ṹ˵��  :NMR��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
}APP_RRC_NMR_REQ_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_NMR_CGI_STRU
 �ṹ˵��  :NMR�ṹ�嶨��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMncNum;           /*ָʾ MNC ����*/
    VOS_UINT16                          usMcc;
    VOS_UINT16                          usMnc;
    VOS_UINT8                           aucRes[2];
} RRC_APP_PLMN_ID_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_NMR_CGI_STRU
 �ṹ˵��  :NMR�ṹ�嶨��
*****************************************************************************/
typedef struct
{
    RRC_APP_PLMN_ID_STRU                stPlmnId;
    VOS_UINT32                          sCellId;            /* ��Χ��(0,503) */
} RRC_APP_CELL_GLOBAL_ID_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_NMR_CGI_STRU
 �ṹ˵��  :NMR�ṹ�嶨��
*****************************************************************************/
typedef struct
{
    RRC_APP_CELL_GLOBAL_ID_STRU         stCellGloId;        /* CellGlobalId */
    VOS_UINT16                          usTAC;
    VOS_UINT16                          usPci;              /* 0xFFFFΪ��Ч,��Χ��(0,503) */
    VOS_INT16                           sRsrp;              /* RSRP����ֵ��Χ��(-141,-44) */
    VOS_INT16                           sRsrq;              /* RSRQ����ֵ��Χ��(-40, -6) */
    VOS_UINT16                          usTa;               /* TAֵ*/
    VOS_UINT8                           aucRes[2];
} RRC_APP_LTE_CELL_INFO_STRU;

/*****************************************************************************
 �ṹ��    :RRC_APP_NMR_CNF_STRU
 �ṹ˵��  :NMR��ѯ������Ӧ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
    RRC_APP_LTE_CELL_INFO_STRU          stLteCelInfo;
}RRC_APP_NMR_CNF_STRU;

/*****************************************************************************
 �ṹ��    :APP_RRC_CELLID_REQ_STRU
 �ṹ˵��  :С��������Ϣ��ѯ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
}APP_RRC_CELLID_REQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_APP_CELLID_CNF_STRU
 �ṹ˵��  : RRC�ظ���С��������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;            /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    APP_RESULT_ENUM_UINT32              enResult;
    APP_PLMN_ID_STRU                    stPlmnId;
    VOS_UINT32                          ulCi;               /* 0xFFFFΪ��Ч, */
    VOS_UINT16                          usPci;              /* 0xFFFFΪ��Ч,��Χ��(0,503) */
    VOS_UINT16                          usTAC;             /* TAC */
}RRC_APP_CELLID_CNF_STRU;
#if 0
/*****************************************************************************
 �ṹ��    :RRC_APP_NMR_CGI_STRU
 �ṹ˵��  :NMR�ṹ�嶨��
 RRC_APP_MEAS_RERULT_LIST_STRU       aucMeasReltList[RRC_APP_MAX_CELL_REPORT];
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCellNum;           /* �������� */
    VOS_UINT16                          usPci;              /* 0xFFFFΪ��Ч,��Χ��(0,503) */
    VOS_INT16                           sRsrp;              /* RSRP����ֵ��Χ��(-141,-44) */
    VOS_INT16                           sRsrq;              /* RSRQ����ֵ��Χ��(-40, -6) */
} RRC_APP_MEAS_RERULT_LIST_STRU;
#endif
/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : APP_LPS_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMsgId;      /*��ϢID*/
    VOS_UINT32                          ulSize;       /*��Ϣ��ĳ���*/
    VOS_UINT8                           aucValue[4];  /*��Ϣ����Ч���ݵ�ָ��*/
}APP_LPS_MSG_STRU;

/*****************************************************************************
 �ṹ��    : APP_LRRC_RESEL_OFFSET_CFG_NTF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                         /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/

    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32                           ulFlag;
}APP_LRRC_RESEL_OFFSET_CFG_NTF_STRU;

/* gaojishan-dcom-resel-cfg */
/*****************************************************************************
 �ṹ��    : APP_LRRC_CON_TO_IDLE_NTF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                         /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;

    VOS_INT32              ulReserv;
}APP_LRRC_CON_TO_IDLE_NTF_STRU;

/* gaojishan-fast-dorm-cfg */

/*****************************************************************************
 ö����    : LRRC_LPDCP_FAST_DORMANCY_CMD_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ָʾPDCP������ֹͣFAST_DORMANCY
*****************************************************************************/
enum APP_LRRC_FAST_DORM_ENUM
{
    APP_LRRC_FAST_DORMANCY_STOP         = 0,                                  /* ֹͣFAST_DORMANCY */
    APP_LRRC_FAST_DORMANCY_START,                                             /* ����FAST_DORMANCY */
    APP_LRRC_FAST_DORMANCY_BUTT
};
typedef VOS_UINT32 APP_LRRC_FAST_DORM_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : APP_LRRC_FAST_DORM_CFG_NTF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                         /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;

    APP_LRRC_FAST_DORM_ENUM_UINT32      ulFlag;
    VOS_UINT32            ulTimerLen;   /* unite: s */
}APP_LRRC_FAST_DORM_CFG_NTF_STRU;



/*****************************************************************************
 �ṹ��    : ID_APP_LRRC_SET_UE_REL_VERSION_REQ
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                         /*_H2ASN_Skip*/
    VOS_UINT32             ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT32              ulMode;     /* 2:LTE , 1:TDS */
    VOS_UINT32              ulVersion;  /* 9 - 14 */
}APP_LRRC_SET_UE_REL_VERSION_REQ_STRU;

/*****************************************************************************
 �ṹ��    : ID_LRRC_APP_SET_UE_REL_VERSION_CNF
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP��Ľӿ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                      /*_H2ASN_Skip*/
    VOS_UINT32                          ulMsgId;        /*_H2ASN_Skip*/
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;         /* MSPֱ�ӽ���ID��ΪCmdID����Prob */
    APP_RESULT_ENUM_UINT32              enResult;
} LRRC_APP_SET_UE_REL_VERSION_CNF_STRU;



extern PS_BOOL_ENUM_UINT8  LRRC_COMM_LoadDspAlready( VOS_VOID );

extern VOS_UINT32 LHPA_InitDsp( VOS_VOID );
extern VOS_VOID LHPA_GetBandStatus(VOS_UINT8 *pucBand, VOS_UINT8 *pucMode);
extern VOS_VOID LHPA_DbgSendSetWorkMode_toMaterMode(VOS_VOID);
extern VOS_VOID LHPA_DbgSendSetWorkMode_toSlaveMode(VOS_VOID);
extern VOS_UINT32  RRC_RRC_LoadDsp( VOS_VOID );
extern VOS_VOID * LAPP_MemAlloc( VOS_UINT32 ulSize );
extern VOS_UINT32  LApp_MemFree(VOS_VOID *pAddr );
extern VOS_UINT32  LAppSndMsgToLPs(APP_LPS_MSG_STRU  *pstAppToPsMsg );
extern 	VOS_UINT32 LHPA_InitDsp_ForAT( VOS_VOID );
extern VOS_UINT32 LHPA_InitDspNvForLteTdsCBT(VOS_VOID);
extern VOS_UINT32 LHPA_LoadDspForLteCBT(VOS_VOID);
extern VOS_VOID   LHPA_DbgSetSlaveModeThenMasterMode(VOS_VOID);

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of AppRrcInterface.h */
