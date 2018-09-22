

#ifndef __OMCOMMON_H__
#define __OMCOMMON_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include "vos.h"
#include "LPSCommon.h"
#include "AppL2Interface.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 macro
*****************************************************************************/

/*key event id��ȡֵ��Χ��CP V100��0x10500~0x11099������Ͳ���UE��key event id�Ķ���
  typedef VOS_UINT8 OM_PS_KEY_EVENT_ENUM_UINT8  ȡֵ����ì�ܡ�
 �������������key evnet id ��ƫ����*/
#define OM_PS_KEY_EVENT_BASE_ID         0x104FF




/*PS ��ά�ɲ�*/
/* С���ɴ������PLMN���� */
#define LPS_RRC_CSEL_MAX_FOUND_PLMN_COUNT           (6)

/* UE֧�ֵ�ͬƵ����ƵС�������Ŀ */
#define LPS_LRRC_LPHY_MAX_FREQ_CELL_NUM                        33

/* ��ģ��LTEģʱ��UE֧�ֵ���Ƶ�������Ŀ��4��
   ��ģΪLTEģʱ��UE֧�ֵ���Ƶ�������Ŀ��3 */
#define LPS_LRRC_LPHY_MAX_ADDITIONAL_CARRIER_NUM              4

/*��������*/
#define LPS_NAS_ESM_MAX_EPSB_NUM            (11)
/* TA �б������� */

#define LPS_NAS_MM_MAX_TA_NUM     64

#define LPS_APP_MAX_IPV4_ADDR_LEN                               4
#define LPS_APP_MAX_IPV6_ADDR_LEN                               16

#define LPS_NAS_MM_MAX_UEID_BUF_SIZE        10                  /* UNIT: BYTE  */

#define MSP_L3_PID_DT  MSP_PID_DIAG_APP_AGENT
#define L3_MSP_PID_DT  MSP_PID_DIAG_APP_AGENT
#define L3_MSP_PID_DT_IND  MSP_PID_DIAG_AGENT

#define TL_OM_LTE_PDCP_SRB_MAX_RPT_PDU_NUM 3
#define NEW_DATA (0)
#define RETRANS_DATA (1)
#define TL_OM_LTE_RLC_RPT_PDU_LEN                  (4)
#define TL_OM_LTE_RLC_MAX_NACK_NUM                 (5)


/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/* Msg ID����4����:
-----------------------------------------------------------------
  �ֽڸ�λ                                      �ֽڵ�λ
-----------------------------------------------------------------
| BYTE1  |  BYTE2    |   BYTE3    |    BYTE4   |
-----------------------------------------------------------------
BYTE1 ��Ϣ����:
                ȡֵ�ο�UE_MSG_TYPEö�ٵĶ���

BYTE2 Դģ���:
                ȡֵ��Χ�� UE_FUNC_MODULE_ID_ENUM �� UE_APP_MODULE_ID_ENUM�Ķ���


BYTE3 Ŀ��ģ���:
                ȡֵ��ΧͬBYTE2

BYTE4  ��Ϣ��:0~255
*/

/*****************************************************************************
 �ṹ��    : OM_PS_COMM_CMD_ENUM
 �ṹ˵��  : OM��Э��ջ��Ĺ������ܵĽӿ���Ϣ����
*****************************************************************************/
enum OM_PS_COMM_CMD_ENUM
{
    /*------------------- Э��ջ��OM�乫�����ܵĽӿڵ����� -------------------*/
    /*�տ���Ϣ�ϱ�*/
    PS_OMT_AIR_MSG_REPORT_IND       =
            DEF_MSG(ENUM_AIR_MSG, UE_MODULE_PS_ID, UE_APP_SUBSYS_ID, 0x01),

    /*�ؼ��¼��ϱ�MM(SM/RRC/L2)->OM->OMT */
    PS_OMT_KEY_EVT_REPORT_IND       =
            DEF_MSG(ENUM_KEY_EVENT_MSG, UE_MODULE_PS_ID, UE_APP_SUBSYS_ID, 0x01),

    /*͸������,OM���͸�PS����ģ���ͳһ��͸����Ϣ�Ķ���*/
    OM_PS_TRANSPARENT_CMD_REQ       =
            DEF_MSG(ENUM_TRANSPARENT_MSG, UE_APP_SUBSYS_ID, UE_MODULE_PS_ID, 0x01),

    OM_PS_TRANSPARENT_CMD_CNF       =
            DEF_MSG(ENUM_TRANSPARENT_MSG, UE_MODULE_PS_ID, UE_APP_SUBSYS_ID, 0x01)

};
typedef VOS_UINT32 OM_PS_COMM_CMD_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : OM_CMD_ENUM
 �ṹ˵��  : OMT��OM�ĸ���ģ������Ϣ����
*****************************************************************************/
enum OM_CMD_ENUM
{
    /*---------------------------- OM��OMT��ulMsgId --------------------------*/
    /*OMAGENT ��OM֮���������Ϣԭ��*/
    OMAGENT_OM_HANDSHAKE_REQ        =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_APP_SUBSYS_ID, UE_MODULE_OM_ID, 00),

    OM_OMAGENT_HANDSHAKE_CNF        =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_APP_SUBSYS_ID, 00),
    /*OMAGENT ��OM֮���������Ϣԭ��*/
    OMAGENT_OM_HEART_REQ =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_AGENT_ID, UE_MODULE_OM_ID, 0x01),
    OM_OMAGENT_HEART_CNF =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_MODULE_OM_AGENT_ID, 0x01),

    /*OMT���ò����Ϣ�����ر�  OMT<->OM ��ͨ����*/
    OMT_OM_HOOKTRACE_CONFIG_REQ     =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_APP_SUBSYS_ID, UE_MODULE_OM_ID, 01),

    OM_OMT_HOOKTRACE_CONFIG_CNF     =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_APP_SUBSYS_ID, 01),

    /*OMT��������ģ��log����  OMT<->OM ��ͨ����*/
    OMT_OM_LOG_CONFIG_REQ           =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_APP_SUBSYS_ID, UE_MODULE_OM_ID, 02),

    OM_OMT_LOG_CONFIG_CNF           =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_APP_SUBSYS_ID, 02),

    /*OMT�Ը���ģ��log���������  OMT<->OM ��ͨ����*/
    OMT_OM_SET_PS_LOGPRINT_LEV_REQ  =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_APP_SUBSYS_ID, UE_MODULE_OM_ID, 03),

    OM_OMT_SET_PS_LOGPRINT_LEV_CNF  =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_APP_SUBSYS_ID, 03),

    /*OMT����PS����ģ��Ŀտ���Ϣ���ٱ�־ OMT<-> ��ͨ����*/
    OMT_OM_SET_AIR_MSG_TRACE_REQ    =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_APP_SUBSYS_ID, UE_MODULE_OM_ID, 04),

    OM_OMT_SET_AIR_MSG_TRACE_CNF    =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_APP_SUBSYS_ID, 04),


    /*L2 LOG���ýӿ� OMT->MASTER OM->HPA->L2 OM Agent*/
    OMT_L2_LOG_CONFIG_REQ           =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_ID, UE_MODULE_OM_SLAVE_ID, 00),

    /*L2 LOG��Ϣ���ý�� L2 OM Agent->HPA->MASTER OM->OMT*/
    L2_OMT_LOG_CONFIG_CNF           =
                DEF_MSG(ENUM_GENERAL_CMD_MSG, UE_MODULE_OM_SLAVE_ID, UE_MODULE_OM_ID, 00)

};
typedef VOS_UINT32 OM_CMD_ENUM_UINT32;


/*****************************************************************************
 �ṹ��    : PS_OM_KEY_EVENT_ENUM
 �ṹ˵��  : �ؼ��¼���ȡֵ�Ķ���
*****************************************************************************/
enum OM_PS_KEY_EVENT_ENUM
{
    /*--------------------RRC�����key event--------------------*/
    RRC_OM_KEY_EVENT_CELL_SEARCH_SPEC_PLMN       = 1,
    RRC_OM_KEY_EVENT_CELL_SEARCH_PLMN_LIST,
    RRC_OM_KEY_EVENT_CELL_SEARCH_SUIT,
    RRC_OM_KEY_EVENT_CELL_SEARCH_ANYCELL,
    RRC_OM_KEY_EVENT_SIB_RCV,
    RRC_OM_KEY_EVENT_CELL_CAMPED_ON,
    RRC_OM_KEY_EVENT_CELL_RESEL,
    RRC_OM_KEY_EVENT_RRC_CONN_SETUP,
    RRC_OM_KEY_EVENT_RRC_CONN_RELEASE,
    RRC_OM_KEY_EVENT_RB_SETUP,
    RRC_OM_KEY_EVENT_HANDOVER_START,
    RRC_OM_KEY_EVENT_RRC_CONN_REEST,
    RRC_OM_KEY_EVENT_SMC,
    RRC_OM_KEY_EVENT_RRC_CONN_REQ,
    RRC_OM_KEY_EVENT_RRC_CONN_SETUP_CMPL,
    RRC_OM_KEY_EVENT_HANDOVER_SUCC,
    RRC_OM_KEY_EVENT_RRC_UE_CAP_ENQUIRE,
    RRC_OM_KEY_EVENT_W2L_RESEL_STRAT,
    RRC_OM_KEY_EVENT_W2L_RESEL_SUCC,
    RRC_OM_KEY_EVENT_W2L_RESEL_FAIL,
    RRC_OM_KEY_EVENT_W2L_REDIRECTED_STRAT,
    RRC_OM_KEY_EVENT_W2L_REDIRECTED_SUCC,
    RRC_OM_KEY_EVENT_W2L_REDIRECTED_FAIL,
    RRC_OM_KEY_EVENT_W2L_HANDOVER_STRAT,
    RRC_OM_KEY_EVENT_W2L_HANDOVER_SUCC,
    RRC_OM_KEY_EVENT_W2L_HANDOVER_FAIL,
    RRC_OM_KEY_EVENT_W2L_GETUECAPINFO_STRAT,
    RRC_OM_KEY_EVENT_W2L_GETUECAPINFO_SUCC,
    RRC_OM_KEY_EVENT_W2L_GETUECAPINFO_FAIL,
    RRC_OM_KEY_EVENT_W2L_PLMN_SEARCH_STRAT,
    RRC_OM_KEY_EVENT_W2L_PLMN_SEARCH_SUCC,
    RRC_OM_KEY_EVENT_W2L_PLMN_SEARCH_FAIL,
    RRC_OM_KEY_EVENT_L2W_RESEL_START,
    RRC_OM_KEY_EVENT_L2W_RESEL_SUCC,
    RRC_OM_KEY_EVENT_L2W_RESEL_FAIL,
    RRC_OM_KEY_EVENT_L2W_REDIRECTED_START,
    RRC_OM_KEY_EVENT_L2W_REDIRECTED_SUCC,
    RRC_OM_KEY_EVENT_L2W_REDIRECTED_FAIL,
    RRC_OM_KEY_EVENT_L2W_HANDOVER_START,
    RRC_OM_KEY_EVENT_L2W_HANDOVER_SUCC,
    RRC_OM_KEY_EVENT_L2W_HANDOVER_FAIL,
    RRC_OM_KEY_EVENT_L2W_GETUECAPINFO_START,
    RRC_OM_KEY_EVENT_L2W_GETUECAPINFO_SUCC,
    RRC_OM_KEY_EVENT_L2W_GETUECAPINFO_FAIL,
    RRC_OM_KEY_EVENT_G2L_RESEL_STRAT,
    RRC_OM_KEY_EVENT_G2L_RESEL_SUCC,
    RRC_OM_KEY_EVENT_G2L_RESEL_FAIL,
    RRC_OM_KEY_EVENT_G2L_REDIRECTED_STRAT,
    RRC_OM_KEY_EVENT_G2L_REDIRECTED_SUCC,
    RRC_OM_KEY_EVENT_G2L_REDIRECTED_FAIL,
    RRC_OM_KEY_EVENT_G2L_HANDOVER_STRAT,
    RRC_OM_KEY_EVENT_G2L_HANDOVER_SUCC,
    RRC_OM_KEY_EVENT_G2L_HANDOVER_FAIL,
    RRC_OM_KEY_EVENT_G2L_CCO_STRAT,
    RRC_OM_KEY_EVENT_G2L_CCO_SUCC,
    RRC_OM_KEY_EVENT_G2L_CCO_FAIL,
    RRC_OM_KEY_EVENT_L2G_RESEL_START,
    RRC_OM_KEY_EVENT_L2G_RESEL_SUCC,
    RRC_OM_KEY_EVENT_L2G_RESEL_FAIL,
    RRC_OM_KEY_EVENT_L2G_REDIRECTED_START,
    RRC_OM_KEY_EVENT_L2G_REDIRECTED_SUCC,
    RRC_OM_KEY_EVENT_L2G_REDIRECTED_FAIL,
    RRC_OM_KEY_EVENT_L2G_HANDOVER_START,
    RRC_OM_KEY_EVENT_L2G_HANDOVER_SUCC,
    RRC_OM_KEY_EVENT_L2G_HANDOVER_FAIL,
    RRC_OM_KEY_EVENT_L2G_CCO_START,
    RRC_OM_KEY_EVENT_L2G_CCO_SUCC,
    RRC_OM_KEY_EVENT_L2G_CCO_FAIL,
    RRC_OM_KEY_EVENT_L2G_GETUECAPINFO_START,
    RRC_OM_KEY_EVENT_L2G_GETUECAPINFO_SUCC,
    RRC_OM_KEY_EVENT_L2G_GETUECAPINFO_FAIL,
    RRC_OM_KEY_EVENT_L2C_RESEL_FAIL,
    RRC_OM_KEY_EVENT_L2C_REDIR_FAIL,

    /*--------------------NAS�����key event--------------------*/
    MM_KEY_EVENT_PLMN_SPEC_SEARCH_START ,
    MM_KEY_EVENT_PLMN_LIST_SEARCH_START,
    MM_KEY_EVENT_PLMN_SEARCH_SUCC,
    MM_KEY_EVENT_PLMN_SEARCH_FAIL,
    MM_KEY_EVENT_START_AUTO_RESEL,
    MM_KEY_EVENT_START_MANUAL_RESEL,
    MM_KEY_EVENT_PLMN_RESEL_CNF,
    MM_KEY_EVENT_COVERAGE_LOST,

    MM_KEY_EVENT_ATTACH_REQ,
    MM_KEY_EVENT_ATTACH_ACP,
    MM_KEY_EVENT_ATTACH_CMP,
    MM_KEY_EVENT_ATTACH_REJ,

    MM_KEY_EVENT_DETACH_REQ_MT,
    MM_KEY_EVENT_DETACH_ACP_MT,
    MM_KEY_EVENT_DETACH_REQ_MO,
    MM_KEY_EVENT_DETACH_ACP_MO,

    MM_KEY_EVENT_TAU_REQ,
    MM_KEY_EVENT_TAU_ACP,
    MM_KEY_EVENT_TAU_CMP,
    MM_KEY_EVENT_TAU_REJ,

    MM_KEY_EVENT_SER_REQ,
    MM_KEY_EVENT_SER_REJ,
    MM_KEY_EVENT_SER_ACP,

    MM_KEY_EVENT_GUTI_CMD,
    MM_KEY_EVENT_GUTI_CMP,

    MM_KEY_EVENT_IDEN_REQ,
    MM_KEY_EVENT_IDEN_RSP,

    MM_KEY_EVENT_AUTH_REQ,
    MM_KEY_EVENT_AUTH_FAIL,
    MM_KEY_EVENT_AUTH_RSP,
    MM_KEY_EVENT_AUTH_REJ,

    MM_KEY_EVENT_SECU_CMD,
    MM_KEY_EVENT_SECU_CMP,
    MM_KEY_EVENT_SECU_REJ,

    MM_KEY_EVENT_EMM_STATUS,
    MM_KEY_EVENT_EMM_INFO,

    MM_KEY_EVENT_EMM_UPLINK_NAS_TRANSPORT,
    MM_KEY_EVENT_EMM_DOWNLINK_NAS_TRANSPORT,

    MM_KEY_EVENT_EXTENDED_SER_REQ,              /* 2012-02-24 */
    MM_KEY_EVENT_CS_SER_NOTIFICATION,           /* 2012-02-24 */

    ESM_KEY_EVENT_BEARER_5_SETUP,
    ESM_KEY_EVENT_BEARER_5_MODIFY,
    ESM_KEY_EVENT_BEARER_5_RELEASE,

    ESM_KEY_EVENT_BEARER_6_SETUP,
    ESM_KEY_EVENT_BEARER_6_MODIFY,
    ESM_KEY_EVENT_BEARER_6_RELEASE,

    ESM_KEY_EVENT_BEARER_7_SETUP,
    ESM_KEY_EVENT_BEARER_7_MODIFY,
    ESM_KEY_EVENT_BEARER_7_RELEASE,

    ESM_KEY_EVENT_BEARER_8_SETUP,
    ESM_KEY_EVENT_BEARER_8_MODIFY,
    ESM_KEY_EVENT_BEARER_8_RELEASE,

    ESM_KEY_EVENT_BEARER_9_SETUP,
    ESM_KEY_EVENT_BEARER_9_MODIFY,
    ESM_KEY_EVENT_BEARER_9_RELEASE,

    ESM_KEY_EVENT_BEARER_10_SETUP,
    ESM_KEY_EVENT_BEARER_10_MODIFY,
    ESM_KEY_EVENT_BEARER_10_RELEASE,

    ESM_KEY_EVENT_BEARER_11_SETUP,
    ESM_KEY_EVENT_BEARER_11_MODIFY,
    ESM_KEY_EVENT_BEARER_11_RELEASE,

    ESM_KEY_EVENT_BEARER_12_SETUP,
    ESM_KEY_EVENT_BEARER_12_MODIFY,
    ESM_KEY_EVENT_BEARER_12_RELEASE,

    ESM_KEY_EVENT_BEARER_13_SETUP,
    ESM_KEY_EVENT_BEARER_13_MODIFY,
    ESM_KEY_EVENT_BEARER_13_RELEASE,

    ESM_KEY_EVENT_BEARER_14_SETUP,
    ESM_KEY_EVENT_BEARER_14_MODIFY,
    ESM_KEY_EVENT_BEARER_14_RELEASE,

    ESM_KEY_EVENT_BEARER_15_SETUP,
    ESM_KEY_EVENT_BEARER_15_MODIFY,
    ESM_KEY_EVENT_BEARER_15_RELEASE,

    /*--------------------L2�����key event--------------------*/
    /*L2_KEY_EVENT_XYZ       = 41,*/
    L2_KEY_EVENT_PDCP_SETUP_SUCC,           /* PDCPʵ�彨���ɹ� */
    L2_KEY_EVENT_PDCP_SETUP_FAIL,           /* PDCPʵ�彨��ʧ�� */
    L2_KEY_EVENT_PDCP_REEST_START,          /* PDCP�ؽ�����ʼ */
    L2_KEY_EVENT_PDCP_REEST_SUCC,           /* PDCP�ؽ����ɹ� */
    L2_KEY_EVENT_PDCP_REEST_FAIL,           /* PDCP�ؽ���ʧ�� */
    L2_KEY_EVENT_PDCP_ACTIVE_CIPHER,        /* PDCP���ȫ���� */
    L2_KEY_EVENT_PDCP_ACTIVE_CIPHER_FAIL,   /* PDCP���ȫ����ʧ�� */
    L2_KEY_EVENT_PDCP_CHANGE_KEY,           /* PDCP��ȫ���Ը�����Կ */
    L2_KEY_EVENT_PDCP_CHANGE_ALG,           /* PDCP��ȫ���Ը����㷨 */
    L2_KEY_EVENT_PDCP_RELEASE,              /* PDCPʵ���ͷ� */
    L2_KEY_EVENT_PDCP_ULBUF_FULL,           /* PDCP���л����� */
    L2_KEY_EVENT_PDCP_DLBUF_FULL,           /* PDCP���л����� */
    L2_KEY_EVENT_PDCP_INTE_VERIFY_FAIL,     /* PDCP�����Լ��ʧ�� */

    L2_KEY_EVENT_RLC_STABLISH_SUCC,  /*92*/
    L2_KEY_EVENT_RLC_STABLISH_FAIL,
    L2_KEY_EVENT_RLC_RECFG_SUCC,
    L2_KEY_EVENT_RLC_RECFG_FAIL,
    L2_KEY_EVENT_RLC_RESTABLISH_SUCC,
    L2_KEY_EVENT_RLC_RESTABLISH_FAIL,
    L2_KEY_EVENT_RLC_RELEASE_SUCC,
    L2_KEY_EVENT_RLC_RELEASE_FAIL,
    L2_KEY_EVENT_RLC_RETX_TIMES_FULL,   /*RLC AM PDU�ﵽ����ش�����*/
    L2_KEY_EVENT_RLC_CTRL_PDU_ERROR,    /*RLC AM ���յ���״̬PDU����*/
    L2_KEY_EVENT_RLC_PDU_LI_ERROR,      /*RLC���нӵ���PDU LI�ֶ���д�쳣*/


    L2_KEY_EVENT_MAC_SETUP_SUCC,
    L2_KEY_EVENT_MAC_SETUP_FAIL,
    L2_KEY_EVENT_MAC_RESET_SUCC,
    L2_KEY_EVENT_MAC_RESET_FAIL,
    L2_KEY_EVENT_MAC_RELEASE_SUCC,
    L2_KEY_EVENT_MAC_RELEASE_FAIL,
    L2_KEY_EVENT_MAC_RA_SUCC,
    L2_KEY_EVENT_MAC_RA_FAIL,
    L2_KEY_EVENT_MAC_RACH_SUCC,
    L2_KEY_EVENT_MAC_RACH_FAIL,
    L2_KEY_EVENT_MAC_RANDOM_ACCESS_SUCC,
    L2_KEY_EVENT_MAC_RANDOM_ACCESS_FAIL,
    L2_KEY_EVENT_HO_MAC_RX_L3_RA_IND,
    L2_KEY_EVENT_HO_MAC_TX_PREAMBLE,
    L2_KEY_EVENT_HO_MAC_RANDACCESS_SUCC,
    L2_KEY_EVENT_HO_MAC_RX_LAST_PDU,
    L2_KEY_EVENT_HO_MAC_RX_FIRST_PDU,
    L2_KEY_EVENT_HO_MAC_TX_LAST_PDU,
    L2_KEY_EVENT_HO_MAC_TX_FIRST_PDU,
    L2_KEY_EVENT_HO_MAC_RX_LAST_ULGRANT,
    L2_KEY_EVENT_HO_MAC_RX_FIRST_ULGRANT,
    L2_KEY_EVENT_HO_RLC_RX_LAST_PDU,
    L2_KEY_EVENT_HO_RLC_RX_FIRST_PDU,
    L2_KEY_EVENT_HO_RLC_TX_LAST_PDU,
    L2_KEY_EVENT_HO_RLC_TX_FIRST_PDU,
    L2_KEY_EVENT_HO_PDCP_DL_STOP_TIME,
    L2_KEY_EVENT_HO_PDCP_DL_CONTINUE_TIME,
    L2_KEY_EVENT_HO_PDCP_UL_STOP_TIME,
    L2_KEY_EVENT_HO_PDCP_UL_CONTINUE_TIME,

    /* ����Ӱ��·�⣬���������ؼ��¼��ŵ������*/
    MM_KEY_EVENT_EMM_DOWNLINK_GENERIC_NAS_TRANSPORT,
    MM_KEY_EVENT_EMM_UPLINK_GENERIC_NAS_TRANSPORT,

    L2_MCE_DEACTIVE_SCELL1,
    L2_MCE_DEACTIVE_SCELL2,
    L2_MCE_DEACTIVE_SCELL3,
    L2_MCE_DEACTIVE_SCELL4,
    L2_MCE_DEACTIVE_SCELL5,
    L2_MCE_DEACTIVE_SCELL6,
    L2_MCE_DEACTIVE_SCELL7,

    L2_MCE_ACTIVE_SCELL1,
    L2_MCE_ACTIVE_SCELL2,
    L2_MCE_ACTIVE_SCELL3,
    L2_MCE_ACTIVE_SCELL4,
    L2_MCE_ACTIVE_SCELL5,
    L2_MCE_ACTIVE_SCELL6,
    L2_MCE_ACTIVE_SCELL7,

    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL1,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL2,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL3,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL4,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL5,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL6,
    L2_DEACTIVATIONTIMER_TIMEOUT_SCELL7,

    RRC_DEACTIVE_SCELL1,
    RRC_DEACTIVE_SCELL2,
    RRC_DEACTIVE_SCELL3,
    RRC_DEACTIVE_SCELL4,
    RRC_DEACTIVE_SCELL5,
    RRC_DEACTIVE_SCELL6,
    RRC_DEACTIVE_SCELL7
};
typedef VOS_UINT8 OM_PS_KEY_EVENT_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : OM_PS_AIR_MSG_ENUM
 �ṹ˵��  : �տ���Ϣ��ȡֵ�Ķ���
*****************************************************************************/
enum OM_PS_AIR_MSG_ENUM
{
    /*RRC�Ŀտ���Ϣ����*/
    RRC_OM_CDMA2000_CSFB_PARAM_REQ     = 0,
    RRC_OM_CDMA2000_CSFB_PARAM_RSP     = 1,
    RRC_OM_CNT_CHK                     = 2,
    RRC_OM_CNT_CHK_RSP                 = 3,
    RRC_OM_DL_INFO_TRANSF              = 4,
    RRC_OM_HO_FROM_EUTRA_PREP_REQ      = 5,
    RRC_OM_MASTER_INFO_BLOCK           = 6,
    RRC_OM_MEAS_RPRT                   = 7,
    RRC_OM_MOBIL_FROM_EUTRA_CMD        = 8,
    RRC_OM_PAGING                      = 9,
    RRC_OM_CONN_RECFG                  = 10,
    RRC_OM_CONN_RECFG_CMP              = 11,
    RRC_OM_CONN_REESTAB                = 12,
    RRC_OM_CONN_REESTAB_CMP            = 13,
    RRC_OM_CONN_REESTAB_REJ            = 14,
    RRC_OM_CONN_REESTAB_REQ            = 15,
    RRC_OM_CONN_REJ                    = 16,
    RRC_OM_CONN_REL                    = 17,
    RRC_OM_CONN_REQ                    = 18,
    RRC_OM_CONN_SETUP                  = 19,
    RRC_OM_CONN_SETUP_CMP              = 20,
    RRC_OM_SECUR_MODE_CMD              = 21,
    RRC_OM_SECUR_MODE_CMP              = 22,
    RRC_OM_SECUR_MODE_FAIL             = 23,
    RRC_OM_SYS_INFO                    = 24,
    RRC_OM_SIB_TYPE1                   = 25,
    RRC_OM_UE_CAP_ENQUIRY              = 26,
    RRC_OM_UE_CAP_INFO                 = 27,
    RRC_OM_UL_HO_PREP_TRANSF           = 28,
    RRC_OM_UL_INFO_TRANSF              = 29,

    RRC_OM_INTER_RAT_MSG               = 30,
    RRC_OM_HO_CMD                      = 31,
    RRC_OM_HO_PREP_INFO                = 32,
    RRC_OM_UE_RADIO_ACCESS_CAP_INFO    = 33,
    RRC_OM_CONN_RECFG_MOBILE_CONTROL   = 34,

    RRC_OM_HO_CMD_RECFG                = 35,

    RRC_OM_UE_INFO_REQ               = 36,
    RRC_OM_UE_INFO_RSP               = 37,
    RRC_OM_PROXIMITY_IND             = 38,

    /* MBMS Begin */
    RRC_OM_MCCH_MSG                  = 39,
    /* MBMS End */


    /* v7r2 begin */
    RRC_OM_SIB1_V8h0_IES_MSG         = 40,
    RRC_OM_SIB2_V8h0_IES_MSG         = 41,
    RRC_OM_SIB5_V8h0_IES_MSG         = 42,
    RRC_OM_SIB6_V8h0_IES_MSG         = 43,

    RRC_0M_LOGGED_MEASUREMENT_CFG       = 44,

    /* v7r2 end */
    RRC_OM_EUTRA_CAP                 = 45,

    RRC_OM_MBMS_COUNTING_RSP         = 46,
    RRC_AIR_MSG_END                 = 47,

    /* NAS��տ���Ϣ����*/
    /* ESM �տ���Ϣ */
    ESM_ACT_DEFLT_EPS_BEARER_CNTXT_REQ = 100,
    ESM_ACT_DEFLT_EPS_BEARER_CNTXT_ACP,
    ESM_ACT_DEFLT_EPS_BEARER_CNTXT_REJ,

    ESM_ACT_DEDICT_EPS_BEARER_CNTXT_REQ,
    ESM_ACT_DEDICT_EPS_BEARER_CNTXT_ACP,
    ESM_ACT_DEDICT_EPS_BEARER_CNTXT_REJ,

    ESM_MOD_EPS_BEARER_CNTXT_REQ,
    ESM_MOD_EPS_BEARER_CNTXT_ACP,
    ESM_MOD_EPS_BEARER_CNTXT_REJ,

    ESM_DEACT_EPS_BEARER_CNTXT_REQ,
    ESM_DEACT_EPS_BEARER_CNTXT_ACP,

    ESM_PDN_CONNECT_REQ,
    ESM_PDN_CONNECT_REJ,

    ESM_PDN_DISCONNECT_REQ,
    ESM_PDN_DISCONNECT_REJ,

    ESM_BEARER_RESOUCE_ALLOC_REQ,
    ESM_BEARER_RESOUCE_ALLOC_REJ,

    ESM_BEARER_RESOUCE_MOD_REQ,
    ESM_BEARER_RESOUCE_MOD_REJ,

    ESM_INFO_REQ,
    ESM_INFO_RSP,

    ESM_STUS_MT,
    ESM_STUS_MO,

    ESM_NOTIFICATION_MT,

    /* EMM �տ���Ϣ */
    MM_ATTACH_REQ,
    MM_ATTACH_ACP,
    MM_ATTACH_CMP,
    MM_ATTACH_REJ,

    MM_DETACH_REQ_MT,
    MM_DETACH_ACP_MT,
    MM_DETACH_REQ_MO,
    MM_DETACH_ACP_MO,

    MM_TAU_REQ,
    MM_TAU_ACP,
    MM_TAU_CMP,
    MM_TAU_REJ,

    MM_SER_REQ,
    MM_SER_REJ,
    MM_SER_ACP,

    MM_GUTI_CMD,
    MM_GUTI_CMP,

    MM_IDEN_REQ,
    MM_IDEN_RSP,

    MM_AUTH_REQ,
    MM_AUTH_FAIL,
    MM_AUTH_RSP,
    MM_AUTH_REJ,

    MM_SECU_CMD,
    MM_SECU_CMP,
    MM_SECU_REJ,

    MM_EMM_STATUS,

    TC_ACT_TEST_MODE,
    TC_ACT_TEST_MODE_CMP,

    TC_DEACT_TEST_MODE,
    TC_DEACT_TEST_MODE_CMP,

    TC_CLOSE_UE_TEST_LOOP,
    TC_CLOSE_UE_TEST_LOOP_CMP,

    TC_OPEN_UE_TEST_LOOP,
    TC_OPEN_UE_TEST_LOOP_CMP,

    MM_EMM_INFO,

    MM_EMM_DOWNLINK_NAS_TRANSPORT,
    MM_EMM_UPLINK_NAS_TRANSPORT,

    MM_EXTENDED_SER_REQ,                /* 2012-02-24 */
    MM_CS_SER_NOTIFICATION,             /* 2012-02-24 */

    MM_EMM_DOWNLINK_GENERIC_NAS_TRANSPORT,
    MM_EMM_UPLINK_GENERIC_NAS_TRANSPORT,

    /*L2��Ŀտ���Ϣ����*/
    /*PDCP_RRC_DATA_REQ      = 200,
    PDCP_RRC_DATA_IND,

    PDCP_RABM_DATA_REQ,
    PDCP_RABM_DATA_IND,

    PDCP_RLC_DATA_REQ,
    PDCP_RLC_DATA_IND,

    MAC_PHY_UL_FEEDBACK_IND,
    MAC_PHY_DCI_IND,
    MAC_PHY_CQI_IND,
    MAC_PHY_LOOP_IND,

    LMAC_DLCOM_PBCH,
    LMAC_DLCOM_PDSCH,
    LMAC_DLCOM_PRNTI,
    LMAC_DLCOM_SIRNTI,*/


};
typedef VOS_UINT8 OM_PS_AIR_MSG_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : DT_CMD_ENUM
 �ṹ˵��  : DT����ö��
*****************************************************************************/
enum DT_CMD_ENUM
{
    DT_CMD_STOP,        /*ֹͣ*/
    DT_CMD_START,       /*����*/
    DT_CMD_BUTT
};
typedef VOS_UINT8 DT_CMD_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : DT_RESULT_ENUM
 �ṹ˵��  : DT�������ö��
*****************************************************************************/
enum DT_RESULT_ENUM
{
    DT_RESULT_SUCC = 0,
    DT_RESULT_FAIL,
    DT_RESULT_NOT_SUPPORT_MEASURE,                /*��ǰ��֧�ֵĲ���*/

    /**********����ģ��ֱ�������������Ҫ�Ľ��ֵ********/
    /*RRCģʽ�Ľ��ֵ����Begin*/
    DT_RESULT_RRC_BEGIN = 0x1000,

    /*RRCģʽ�Ľ��ֵ����End*/

    /*NASģʽ�Ľ��ֵ����Begin*/
    DT_RESULT_NAS_BEGIN                 = 0x2000,
    DT_RESULT_NAS_PLMN_LOCK             = 0x2001,
    DT_RESULT_NAS_PLMN_UNLOCK           = 0x2002,

    /*NASģʽ�Ľ��ֵ����End*/

    /*L2ģʽ�Ľ��ֵ����Begin*/
   DT_RESULT_L2_BEGIN = 0x3000,

    /*L2ģʽ�Ľ��ֵ����End*/

   /*RRUģʽ�Ľ��ֵ����Begin*/
   DT_RESULT_RRU_BEGIN = 0x4000,

   /*RRUģʽ�Ľ��ֵ����End*/

    DT_RESULT_BUTT
};
typedef VOS_UINT32 DT_RESULT_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : DT_FLAG_ENUM
 �ṹ˵��  : DT��Ч��ʶ
*****************************************************************************/
enum DT_FLAG_ENUM
{
    DT_FLAG_INVALID,                 /* ��Ч*/
    DT_FLAG_VALID,                   /* ��Ч */
    DT_FLAG_ENUM_BUTT
};
typedef VOS_UINT8 DT_FLAG_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : APP_PS_MSG_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э��ջ��APP֮�����ϢID����
*****************************************************************************/

enum APP_PS_MSG_TYPE_ENUM
{

    /*��ά�ɲ�-camped cell information�ϱ�*/
    ID_OM_PS_CAMPEDCELL_INFO_CMD_REQ           = (PS_MSG_ID_APP_TO_PS_BASE + 0x01),/*0x1336*/
    ID_PS_OM_CAMPEDCELL_INFO_CMD_CNF           = (PS_MSG_ID_PS_TO_APP_BASE + 0x01),/*0x1316*/

    /*��ά�ɲ�-handover�ϱ�*/
    ID_OM_PS_HANDOVER_INFO_CMD_REQ             = (PS_MSG_ID_APP_TO_PS_BASE + 0x02),/*0x1337*/
    ID_PS_OM_HANDOVER_INFO_CMD_CNF             = (PS_MSG_ID_PS_TO_APP_BASE + 0x02),/*0x1317*/

    /*��ά�ɲ�-prach\sr�ϱ�*/
    ID_OM_PS_PRACH_SR_INFO_CMD_REQ             = (PS_MSG_ID_APP_TO_PS_BASE + 0x03),/*0x1338*/
    ID_PS_OM_PRACH_SR_INFOCMD_CNF              = (PS_MSG_ID_PS_TO_APP_BASE + 0x03),/*0x1318*/

    /*��ά�ɲ�-bsr�ϱ�*/
    ID_OM_PS_BSR_INFO_CMD_REQ                  = (PS_MSG_ID_APP_TO_PS_BASE + 0x04),/*0x1339*/
    ID_PS_OM_BSR_INFO_CMD_CNF                  = (PS_MSG_ID_PS_TO_APP_BASE + 0x04)/*0x1319*/



};
typedef VOS_UINT32   APP_PS_MSG_TYPE_ENUM_UINT32;

/*added by hujianbo for TDS L2 OM, 20131230*/
/*****************************************************************************
 ö����    : TDS_L2_UP_EVENT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : TL�û����¼�ö�ٶ��壬���ڼ�¼Ӱ��TL�����ĸ����¼�
*****************************************************************************/
enum    TL_UP_EVENT_ENUM
{
    /*CDS�¼�*/
    TL_UP_EVENT_CDS_UL_IPF_ERR                  = 0,
    TL_UP_EVENT_CDS_UL_SOFT_IPF_ERR,
    TL_UP_EVENT_CDS_UL_FLOW_CTRL,
    TL_UP_EVENT_CDS_DL_FLOW_CTRL,
    TL_UP_EVENT_CDS_DL_SDU_QUE_FULL,

    /*TDS�¼�*/
    TL_UP_EVENT_TPDCP_UL_DISCARD_SDU            = 50,
    TL_UP_EVENT_TPDCP_DL_DISCARD_SDU,

    TL_UP_EVENT_TRLC_UL_RETX_PDU                = 100,
    TL_UP_EVENT_TRLC_UL_RETX_PDU_MAX_NUM,
    TL_UP_EVENT_TRLC_UL_TX_NACK,
    TL_UP_EVENT_TRLC_UL_TX_RTS_PDU,
    TL_UP_EVENT_TRLC_UL_TX_RTS_ACK_PDU,
    TL_UP_EVENT_TRLC_UL_SDU_QUE_FULL,
    TL_UP_EVENT_TRLC_UL_RL_FAIL,
    TL_UP_EVENT_TRLC_UL_DISCARD_TIMER_EXPIRED,
    TL_UP_EVENT_TRLC_DL_RX_NACK,
    TL_UP_EVENT_TRLC_DL_RX_MRW,
    TL_UP_EVENT_TRLC_DL_RX_MRW_ACK,
    TL_UP_EVENT_TRLC_DL_RX_RTS_PDU,
    TL_UP_EVENT_TRLC_DL_RX_RTS_ACK_PDU,
    TL_UP_EVENT_TRLC_DL_RX_SN_OUT_OF_WIN,

    TL_UP_EVENT_TMAC_UL_HARQ_RETX               = 150,
    TL_UP_EVENT_TMAC_UL_HARQ_RETX_MAX,
    TL_UP_EVENT_TMAC_UL_HARQ_RESET,
    TL_UP_EVENT_TMAC_UL_PDU_FULL,
    TL_UP_EVENT_TMAC_UL_RX_NACK,
    TL_UP_EVENT_TMAC_UL_SFN_ERR,
    TL_UP_EVENT_TMAC_DL_RX_DPCH_CRC_ERR,
    TL_UP_EVENT_TMAC_DL_RX_DPA_CRC_ERR,
    TL_UP_EVENT_TMAC_DL_REORDER_TIMER_EXPIRED,
    TL_UP_EVENT_TMAC_DL_T312_EXPIRED,
    TL_UP_EVENT_TMAC_DL_T313_EXPIRED,
    TL_UP_EVENT_TMAC_DL_OUT_OF_SYNC,
    TL_UP_EVENT_TMAC_UPA_ACTIVE,
    TL_UP_EVENT_TMAC_UPA_DEACTIVE,
    TL_UP_EVENT_TMAC_DPA_ACTIVE,
    TL_UP_EVENT_TMAC_DPA_DEACTIVE,

    /*LTE�¼�*/
    TL_UP_EVENT_LPDCP_UL_SDU_BUFFER_FULL            = 200,
    TL_UP_EVENT_LPDCP_UL_DISCARD_SDU_HIGH_PRI,
    TL_UP_EVENT_LPDCP_UL_DISCARD_SDU_LOW_PRI,
    TL_UP_EVENT_LPDCP_UL_FLOW_CTRL_STOP_TX,
    TL_UP_EVENT_LPDCP_DL_SN_NOT_CONSECUTIVE,
    TL_UP_EVENT_LPDCP_DL_SN_OUT_OF_WIN,
    TL_UP_EVENT_LPDCP_DL_CIFIFO_FULL,
    TL_UP_EVENT_LPDCP_DL_SDU_LEN_ERR,
    TL_UP_EVENT_LPDCP_DL_DISCARD_PDU_TOTAL,
    TL_UP_EVENT_LPDCP_STOP,
    TL_UP_EVENT_LPDCP_CONTINUE,
    TL_UP_EVENT_LPDCP_REL,

    TL_UP_EVENT_LRLC_UL_RETX_PDU                = 250,
    TL_UP_EVENT_LRLC_UL_RETX_PDU_SEGMENT,
    TL_UP_EVENT_LRLC_UL_RETX_PDU_MAX_NUM,
    TL_UP_EVENT_LRLC_UL_RX_NACK,
    TL_UP_EVENT_LRLC_UL_SDU_QUE_FULL,
    TL_UP_EVENT_LRLC_UL_DISCARD_TIMER_EXPIRED,
    TL_UP_EVENT_LRLC_DL_DISCARD_PDU_TOTAL,
    TL_UP_EVENT_LRLC_DL_DISCARD_PDU_MEM_FULL,
    TL_UP_EVENT_LRLC_DL_START_REORDER_TIMER,
    TL_UP_EVENT_LRLC_DL_SN_OUT_OF_WIN,
    TL_UP_EVENT_LRLC_DL_DISCARD_SDU_MEM_FULL,
    TL_UP_EVENT_LRLC_DL_FEEDBACK_NACK,
    TL_UP_EVENT_LRLC_REEST,
    TL_UP_EVENT_LRLC_REL,

    TL_UP_EVENT_LMAC_UL_HARQ_RETX               = 300,
    TL_UP_EVENT_LMAC_UL_HARQ_RETX_MAX_NUM,
    TL_UP_EVENT_LMAC_UL_SCHED_INVALID,
    TL_UP_EVENT_LMAC_UL_SCHED_PDU_FAIL,
    TL_UP_EVENT_LMAC_UL_SCHED_TIMEOUT,
    TL_UP_EVENT_LMAC_UL_PDU_ERROR,
    TL_UP_EVENT_LMAC_UL_TWO_SCHED_IND_IN_1MS,
    TL_UP_EVENT_LMAC_UL_SCHED_IND_NOT_CONSECUTIVE,
    TL_UP_EVENT_LMAC_UL_SCHED_ERROR_TOTAL,
    TL_UP_EVENT_LMAC_DL_RX_TB_CRC_ERR,
    TL_UP_EVENT_LMAC_DL_RX_TB_REPEAT,
    TL_UP_EVENT_LMAC_SR,
    TL_UP_EVENT_LMAC_SR_MAX_NUM,
    TL_UP_EVENT_LMAC_RESET,
    TL_UP_EVENT_LMAC_RA_MAC_TRIGGERED,
    TL_UP_EVENT_LMAC_RA_RRC_TRIGGERED,
    TL_UP_EVENT_LMAC_RA_PDCCH_TRIGGERED,
    TL_UP_EVENT_LMAC_REL,

    TL_UP_EVENT_BUTT                            =  350
};
typedef VOS_UINT16 TL_UP_EVENT_ENUM_UINT16;

/*****************************************************************************
 ö����    : LSCELL_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LTE CA ��С��״̬
*****************************************************************************/
enum    LSCELL_STATUS_ENUM
{
    LSCELL_NOT_CONFIGED                  = 0,
    LSCELL_CONFIGED_NOT_ACTIVE,
    LSCELL_ACTIVE,
    LSCELL_STATUS_BUTT
};
typedef VOS_UINT8 LSCELL_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : LSCELL_DEACT_TIMER_VIEW_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : LTE CA ȥ���ʱ��OM��ʾ
*****************************************************************************/
enum    LSCELL_DEACT_TIMER_VIEW_ENUM
{
    LSCELL_DEACT_TIMER_INFINITE                  = 0,
    LSCELL_DEACT_TIMER_NOTCONFIG
};
typedef VOS_UINT32 LSCELL_DEACT_TIMER_VIEW_ENUM_UINT32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : APP_OM_MSG_STRU
 �ṹ˵��  : APP(��̨����)��OM��������Ϣ��
*****************************************************************************/
typedef struct
{
     VOS_MSG_HEADER                     /*VOSͷ
 */
     VOS_UINT32          ulMsgId;
     APP_MSG_HEADER                     /*APPͷ
 */
     VOS_UINT8           aucPara[4];    /* �������� */
}APP_OM_MSG_STRU;

/*****************************************************************************
 �ṹ��    : PS_MSG_STRU
 �ṹ˵��  : Э��ջ��ģ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;        /* ��Ϣԭ��ID */
    VOS_UINT8           aucPara[4];     /* �������� */
} PS_MSG_STRU;


/*****************************************************************************
 �ṹ��    : PS_OM_AIR_MSG_REPORT_IND_STRU
 �ṹ˵��  : Э��ջ����ģ���ϱ��տ���Ϣ�Ľṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgId;        /*ԭ������,*/
    APP_MSG_HEADER

    VOS_UINT8                   ucUpDown;       /*�����б�ʶ��   0-���У�1-����  */
    OM_PS_AIR_MSG_ENUM_UINT8    enAirMsgId;     /*���нӿ���Ϣ��Id               */
    VOS_UINT8                   aucReserved[2]; /*����                           */
    VOS_UINT32                  ulAirLength;    /*������Ϣ���ݳ���               */
    VOS_UINT8                   aucData[4];     /*������Ϣ����                   */
}PS_OM_AIR_MSG_REPORT_IND_STRU;

/*****************************************************************************
 �ṹ��    : PS_OMT_KEY_EVENT_REPORT_IND_STRU
 �ṹ˵��  : PS����ģ��->OMT�Ĺؼ��¼��ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;        /*ԭ������,*/
    APP_MSG_HEADER

    OM_PS_KEY_EVENT_ENUM_UINT8          ucKeyEvent;     /*�ؼ��¼����ͣ�Ϊö��ֵ */
    VOS_UINT8                           aucReserved[3];
}PS_OMT_KEY_EVENT_REPORT_IND_STRU;


/*****************************************************************************
 �ṹ��    : OM_PS_TRANSPARENT_CMD_REQ_STRU
 �ṹ˵��  : OMT->PS����ģ���͸�������·��ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;        /*ԭ������*/
    APP_MSG_HEADER

    VOS_UINT8           aucTransCmd[4]; /*͸���������ɱ�*/
}OM_PS_TRANSPARENT_CMD_REQ_STRU;

/*****************************************************************************
 �ṹ��    : PS_OM_TRANSPARENT_CMD_CNF_STRU
 �ṹ˵��  : PS->OMT��͸������ִ�н�����ݽṹ(
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32          ulMsgId;            /*ԭ������*/
    APP_MSG_HEADER

    VOS_UINT8           aucTransCmdCnf[4];  /*͸���������������ɱ�*/
}PS_OM_TRANSPARENT_CMD_CNF_STRU;
/*****************************************************************************
 �ṹ��    : PS_OM_TRANSPARENT_CMD_IND_STRU
 �ṹ˵��  : PS->OMT��͸������ִ��IND���ݽṹ(
*****************************************************************************/
typedef  PS_OM_TRANSPARENT_CMD_CNF_STRU PS_OM_TRANSPARENT_CMD_IND_STRU;


/*PS��ά�ɲ� BEGIN */

/*****************************************************************************
 �ṹ��    : OM_PS_CAMPEDCELL_INFO_REQ_STRU
 �ṹ˵��  : MSP��ѯפ��С����Ϣ��REQ/CNF�������ݽṹ
*****************************************************************************/
typedef  APP_OM_MSG_STRU OM_PS_CAMPEDCELL_INFO_REQ_STRU;
typedef  APP_OM_MSG_STRU PS_OM_CAMPEDCELL_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : OM_PS_HANDOVER_INFO_REQ_STRU
 �ṹ˵��  : MSP��ѯС���л���Ϣ��REQ/CNF�������ݽṹ
*****************************************************************************/
typedef  APP_OM_MSG_STRU OM_PS_HANDOVER_INFO_REQ_STRU;
typedef  APP_OM_MSG_STRU PS_OM_HANDOVER_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : OM_PS_PRACH_SR_INFO_REQ_STRU
 �ṹ˵��  : MSP��ѯС��PRACH\SR��REQ/CNF�������ݽṹ
*****************************************************************************/
typedef  APP_OM_MSG_STRU OM_PS_PRACH_SR_INFO_REQ_STRU;
typedef  APP_OM_MSG_STRU PS_OM_PRACH_SR_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : OM_PS_BSR_INFO_REQ_STRU
 �ṹ˵��  : MSP��ѯBSR��REQ/CNF�������ݽṹ
*****************************************************************************/
typedef  APP_OM_MSG_STRU OM_PS_BSR_INFO_REQ_STRU;
typedef  APP_OM_MSG_STRU PS_OM_BSR_INFO_CNF_STRU;

/*****************************************************************************
 �ṹ��    : OM_L2_THROUGHPUT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : APP��L2����APP��Tx��Rxͳ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_CMD_ENUM_UINT8                   enCmd;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulRptPeriod;
}OM_L2_THROUGHPUT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : L2_OM_THROUGHPUT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OM��L2����APP ��Tx��Rxͳ����Ϣ�Ļ�Ӧ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_RESULT_ENUM_UINT32               enResult;
} L2_OM_THROUGHPUT_CNF_STRU;

/*DCM logger*/
/*****************************************************************************
 �ṹ��    : OM_L2_MAC_PDU_RPT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OM��L2ָʾ�򿪻��߹ر�MAC PDU��Ϣ���ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucCmd;  /*ֵΪ0����ʾ�ر��ϱ���ֵΪ1����ʾ���ϱ�*/
    VOS_UINT8                           aucRsv[3]; /*Ԥ���ֽ�*/
}OM_L2_MAC_PDU_RPT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : L2_OM_MAC_PDU_RPT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : L2��OM�ظ��򿪻��߹ر�MAC PDU��Ϣ���ϱ��Ƿ�ɹ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucResult;  /*ֵΪ0����ʾ�ɹ�������ֵ����ʾʧ��*/
    VOS_UINT8                           aucRsv[3]; /*Ԥ���ֽ�*/
} L2_OM_MAC_PDU_RPT_CNF_STRU;

/*****************************************************************************
 �ṹ��    : OM_L2_BSR_RPT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OM��L2ָʾ�򿪻��߹ر�BSR��Ϣ���ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucCmd;  /*ֵΪ0����ʾ�ر��ϱ���ֵΪ1����ʾ���ϱ�*/
    VOS_UINT8                           aucRsv[3]; /*Ԥ���ֽ�*/
}OM_L2_BSR_RPT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : L2_OM_BSR_RPT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : L2��OM�ظ��򿪻��߹ر�BSR��Ϣ���ϱ��Ƿ�ɹ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    VOS_UINT8                           ucResult;  /*ֵΪ0����ʾ�ɹ�������ֵ����ʾʧ��*/
    VOS_UINT8                           aucRsv[3]; /*Ԥ���ֽ�*/
} L2_OM_BSR_RPT_CNF_STRU;
/*end DCM*/
/*****************************************************************************
 �ṹ��    : OM_L2_SDU_COUNT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : APP��L2�������SDUͳ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_CMD_ENUM_UINT8                   enCmd;
    VOS_UINT8                           aucRsv[3];
    VOS_UINT32                          ulRptPeriod;
}OM_L2_SDU_COUNT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : L2_OM_APP_THROUGHPUT_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : APP��L2�������SDUͳ����Ϣ�Ļ�Ӧ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    APP_MSG_HEADER
    VOS_UINT32                          ulOpId;
    DT_RESULT_ENUM_UINT32               enResult;
} L2_OM_SDU_COUNT_CNF_STRU;


/*****************************************************************************
 �ṹ��    : APP_LPS_PRACH_SR_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PS��MSP�ϱ�PRACH/SR�����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTotalPblNum;         /*Preamble Number*/
    VOS_UINT32                          ulGrpAPblNum;          /*Group A Preamble Number*/
    VOS_UINT32                          ulGrpBPblNum;          /*Group B Preamble Number*/
    VOS_UINT32                          ulContentionPblNum;    /*Contention Preamble Number*/
    VOS_UINT32                          ulNoneContentionPblNum;/*None Contention Preamble Number*/
    VOS_UINT32                          ulRarNum;              /*RAR Number*/
    VOS_UINT32                          ulCompetitionNum;      /*Competition Number*/
    VOS_UINT32                          ulSrNum;               /*SR Number*/
}APP_LPS_PRACH_SR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : APP_LPS_BSR_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PS��MSP�ϱ�BSR�����Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulShortBsrGrpId;          /*short bsr��Ӧ��GROUP ID*/
    VOS_UINT32                          ulShortBsrValue;          /*Short BSR*/
    VOS_UINT32                          ulLongBsr0Value;          /*Long BSR 0*/
    VOS_UINT32                          ulLongBsr1Value;          /*Long BSR 1*/
    VOS_UINT32                          ulLongBsr2Value;          /*Long BSR 2*/
    VOS_UINT32                          ulLongBsr3Value;          /*Long BSR 3*/
}APP_LPS_BSR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LPS_PLMN_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PLMN��Ŀ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[3];
    VOS_UINT8                           ucReserved;
} LPS_PLMN_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : LPS_PLMN_ITEM_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PLMN LIST
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPlmnCount;
    VOS_UINT8                           aucReservered[2];
    LPS_PLMN_ITEM_STRU                  astPlmnItems[LPS_RRC_CSEL_MAX_FOUND_PLMN_COUNT];
} LPS_CSEL_PLMN_LIST_CTX_STRU;

/*****************************************************************************
 �ṹ��    : LPS_NAS_MM_TAC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAC ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTac;
    VOS_UINT8                           ucTacCnt;
    VOS_UINT8                           aucRsv[2];
}LPS_NAS_MM_TAC_STRU;

/*****************************************************************************
 �ṹ��    : LPS_NAS_MM_TA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TA ��Ϣ
*****************************************************************************/
typedef struct
{
    LPS_PLMN_ITEM_STRU                 stPlmnId;
    LPS_NAS_MM_TAC_STRU                stTac;
}LPS_NAS_MM_TA_STRU;

/*****************************************************************************
 �ṹ��    : LPS_NAS_MM_TA_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TA LIST
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTaNum;            /* TA�ĸ���:Ϊ0��ʾ�������Ϣ*/
    LPS_NAS_MM_TA_STRU                  astTa[LPS_NAS_MM_MAX_TA_NUM];
}LPS_NAS_MM_TA_LIST_STRU;

/*****************************************************************************
 �ṹ��    : LPS_NAS_MM_GUTI_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GUTI Head
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLenth;
    VOS_UINT8                           ucOeToi;
    VOS_UINT8                           aucRsv[2];
}LPS_NAS_MM_GUTI_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : LPS_NAS_MM_GUTI_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GUTI Head
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucGroupId;
    VOS_UINT8                           ucGroupIdCnt;
    VOS_UINT8                           aucRsv[2];
}LPS_NAS_MM_MME_GROUPID_STRU;

/*****************************************************************************
 �ṹ��    : LPS_NAS_MM_MME_CODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MME code
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMmeCode;
    VOS_UINT8                           aucRsv[3];
}LPS_NAS_MM_MME_CODE_STRU;

/*****************************************************************************
 �ṹ��    : LPS_NAS_MM_MME_CODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MTIMSI
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMTmsi;
    VOS_UINT8                           ucMTmsiCnt1;
    VOS_UINT8                           ucMTmsiCnt2;
    VOS_UINT8                           ucMTmsiCnt3;
}LPS_NAS_MM_MTMSI_STRU;

/*****************************************************************************
 �ṹ��    : LPS_NAS_MM_MME_CODE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GUTI ��Ϣ
*****************************************************************************/
typedef struct
{
    LPS_NAS_MM_GUTI_HEAD_STRU               stGutiHead;
    LPS_PLMN_ITEM_STRU                      stPlmnId;
    LPS_NAS_MM_MME_GROUPID_STRU             stMmeGroupId;
    LPS_NAS_MM_MME_CODE_STRU                stMmeCode;
    LPS_NAS_MM_MTMSI_STRU                   stMTmsi;
}LPS_NAS_MM_GUTI_STRU;

/*****************************************************************************
 �ṹ��    : LPS_NAS_ESM_IP_ADDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IP��ַ��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIpType;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucIpV4Addr[LPS_APP_MAX_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[LPS_APP_MAX_IPV6_ADDR_LEN];
}LPS_NAS_ESM_IP_ADDR_STRU;

/*****************************************************************************
 �ṹ��    : LPS_NAS_ESM_EPSB_CNTXT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ÿ��EPS���ض�Ӧ��IP ��ַ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEpsbId;           /*��ӦEPS����ID*/
    LPS_NAS_ESM_IP_ADDR_STRU            stPdnAddrInfo;
}LPS_NAS_ESM_EPSB_CNTXT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : LPS_NAS_IMSI_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IMSI��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucImsi[LPS_NAS_MM_MAX_UEID_BUF_SIZE];    /*IMSI*/
    VOS_UINT8                           ucResvd[2];
}LPS_NAS_IMSI_STRU;


/*****************************************************************************
 �ṹ��    : APP_LPS_CAMPED_CELL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PS��MSP�ϱ�פ��С���������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPhyCellId;          /*servering cell id*/
    VOS_UINT16                          usSyncFlag;           /*1:ͬ�� 0:ʧ�� ��ʾ"Sync"or"Out of Sync"*/
    LPS_CSEL_PLMN_LIST_CTX_STRU         stPlmnListInfo;      /*PLMN LIST*/
    LPS_NAS_MM_TA_LIST_STRU             stRegPlmnTaList;     /*TA LIST*/

    LPS_NAS_IMSI_STRU                   stImsiInfo;          /*IMSI*/
    LPS_NAS_MM_GUTI_STRU                stGutiInfo;          /*GUTI*/


    LPS_NAS_ESM_EPSB_CNTXT_INFO_STRU    astEpsbCntxtInfo[LPS_NAS_ESM_MAX_EPSB_NUM]; /* EPS����IP��ַ��Ϣ  */

    VOS_UINT16                          usUlEarfcn;          /*UL EARFCN */
    VOS_UINT16                          usDlEarfcn;          /*DL EARFCN*/
    VOS_UINT16                          usUlFreq;            /*UL Frequency ��λ:Mhz*/
    VOS_UINT16                          usDlFreq;            /*DL Frequency ��λ:Mhz*/
    VOS_UINT16                          usUlBandwidth;       /*��λ:RB���� */
    VOS_UINT16                          usDlBandwidth;       /*��λ:RB���� */
    VOS_UINT32                          ulBand;              /*BAND ID*/

    VOS_UINT16                          usCRnti;             /*C-RNTI*/
    VOS_UINT16                          usSpsRnti;           /*SPS-RNTI*/
    VOS_UINT16                          usPucchRnti;         /*TPC-PUCCH-RNTI*/
    VOS_UINT16                          usPuschRnti;         /*TPC-PUSCH-RNTI*/

    VOS_UINT8                           ucSbuFrmAssignmentType;
    VOS_UINT8                           ucSpecialSubFrmPatterns;
    VOS_UINT8                           ucUlCpLength;
    VOS_UINT8                           ucDlCpLength;

    VOS_UINT8                           ucEnbTxAntennaNum;
    VOS_UINT8                           ucTransmissionMode;
    VOS_UINT8                           aucResv[2];


}APP_LPS_CAMPED_CELL_INFO_STRU;
/*****************************************************************************
 �ṹ��    : APP_PS_HO_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �л�����ͳ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHOTotalCnt;      /*�л��ܴ���*/
    VOS_UINT32                          ulHOSuccCnt;       /*�л��ɹ��Ĵ���*/
    VOS_UINT32                          ulHOFailCnt;       /*�л�ʧ�ܵĴ���*/
}LPS_HO_STAT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : APP_PS_HANDOVER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PS��MSP�ϱ��л��������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLatestHOLatency;      /*���һ���л�ʱ��*/
    VOS_UINT16                          usAverageHOLatency;     /*ƽ���л�ʱ��*/
    LPS_HO_STAT_INFO_STRU                astIntraFreqHO;        /*ͬƵ�л�����ͳ��*/
    LPS_HO_STAT_INFO_STRU                astInterFreqHO;        /*��Ƶ�л�ͳ��*/
    LPS_HO_STAT_INFO_STRU                astInterRatHO;         /*��ϵͳ�л�����ͳ��*/
}APP_LPS_HANDOVER_INFO_STRU;

/*PS��ά�ɲ� END */

/* gaojishan */
typedef DT_CMD_ENUM_UINT8       APP_CMD_ENUM_UINT8;
typedef DT_RESULT_ENUM_UINT32   APP_RESULT_ENUM_UINT32;

/*added by hujianbo for TL L2 OM, 20140106*/

/*****************************************************************************
 �ṹ��    :TL_OM_COMM_HEAD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :TDS L2�����¼��ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPid;
    VOS_UINT16                          usRbId;
    VOS_UINT16                          usFrameNum;
    VOS_UINT16                          usSubFrameNum;
} TL_OM_COMM_HEAD_STRU;

/*****************************************************************************
 �ṹ��    :TDS_L2_SINGLE_EVENT_RPT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :TDS L2�����¼��ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;
    TL_UP_EVENT_ENUM_UINT16             usEvent;
    VOS_UINT16                          usRsv;
} TL_OM_SINGLE_UP_EVENT_RPT_STRU;

/*****************************************************************************
 �ṹ��    :TDS_L2_AlL_EVENT_RPT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :TDS L2�����¼��ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;
    VOS_UINT32                          aulEventStat[TL_UP_EVENT_BUTT];
} TL_OM_AlL_UP_EVENT_RPT_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_CDS_IPF_PROC_STAT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS IPF��ش���ͳ����
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    /*IPF�¼�*/
    VOS_UINT32              ulIpfULIntNum;
    VOS_UINT32              ulULProcIpfIntNum;
    VOS_UINT32              ulUlAdqEmtypIntNum;
    VOS_UINT32              ulUlProcAdqEmptyIntNum;

    /*����RDͳ����Ϣ*/
    VOS_UINT32              ulULIpfRxRDNum;
    VOS_UINT32              ulULIpfTransMemFailNum;
    VOS_UINT32              ulULIpfModemIdErrNum;
    VOS_UINT32              ulULIpfFreePktInLB;
    VOS_UINT32              ulULIpfRxNdisPktNum;
    VOS_UINT32              ulULIpfRxIpPktNum;
    VOS_UINT32              ulULIpfRxIpSegNum;
    VOS_UINT32              ulULIpfFilterErrNum;

    /*����AD��Ϣ*/
    VOS_UINT32              ulULADQCfgAdNum;
    VOS_UINT32              ulULADQCfgAd0Num;
    VOS_UINT32              ulULADQCfgAd1Num;
    VOS_UINT32              ulULADQAllocMemNum;
    VOS_UINT32              ulULADQFreeMemNum;
    VOS_UINT32              ulULADQCfgAdSucc;
    VOS_UINT32              ulULADQCfgAdFail;
    VOS_UINT32              ulULADQStartEmptyTmrNum;
    VOS_UINT32              ulULADQStopEmptyTmrNum;
    VOS_UINT32              ulULADQEmptyTmrTimeoutNum;
    VOS_UINT32              ulULADQAd0EmptyIntNum;
    VOS_UINT32              ulULADQAd1EmptyIntNum;


    /*����IPF��Ϣ*/
    VOS_UINT32              ulDLIpfSaveSrcMemFail;
    VOS_UINT32              ulDLIpfSaveSrcMemSucc;
    VOS_UINT32              ulDLIpfFreeSrcMemNum;
    VOS_UINT32              ulDLIpfFreeSrcMemErr;

    VOS_UINT32              ulDLIpfCfgHaveNoBD;
    VOS_UINT32              ulDLIpfCfgHaveNoCD;
    VOS_UINT32              ulDLIpfCfgCDNotEnough;
    VOS_UINT32              ulDLIpfCfgBDSucc;
    VOS_UINT32              ulDLIpfCfgBDFail;
    VOS_UINT32              ulDLIpfCfgBDAllocMemFail;
    VOS_UINT32              ulDLIpfCfgBDSduLenErr;
}TL_OM_CDS_IPF_PROC_STAT_IND_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_CDS_UL_IP_PKT_STAT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS ����IP����ش���ͳ����
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    /*����IP������*/
    VOS_UINT32              ulULRecvNdPktNum;
    VOS_UINT32              ulULASRxIpPktNum;
    VOS_UINT32              ulULDirectFreePktNum;
    VOS_UINT32              ulULLTERxPktNum;
    VOS_UINT32              ulULGURxPktNum;
    VOS_UINT32              ulULNULLRxPktNum;
    VOS_UINT32              ulULRanModeErrFreeNum;

    VOS_UINT32              ulULLTEFcFreePktNum;
    VOS_UINT32              ulULLTEProcIpSegFail;
    VOS_UINT32              ulULLTESendToLPdcpNum;
    VOS_UINT32              ulULLTESavePktNum;
    VOS_UINT32              ulULLTEERabmStateErr;

    VOS_UINT32              ulULGUFcFreePktNum;
    VOS_UINT32              ulULGUSendToRabmNum;
    VOS_UINT32              ulULGUSavePktNum;
    VOS_UINT32              ulULGURabmStateErr;

    VOS_UINT32              ulULBuffEnQueSucc;
    VOS_UINT32              ulULBuffEnQueFail;
    VOS_UINT32              ulULBuffSoftFilterFail;
    VOS_UINT32              ulULBuffSendPktSuccNum;
    VOS_UINT32              ulULBuffFreePktNum;

    /*��������ͳ����*/
    VOS_UINT32              ulULSoftFilterPktNum;
    VOS_UINT32              ulULSoftFilterIPv4Num;
    VOS_UINT32              ulULSoftFilterIPv6Num;
    VOS_UINT32              ulULSoftFilterFailNum;
    VOS_UINT32              ulULSoftFilterIPSegNum;
    VOS_UINT32              ulULSoftFilterIPSegSucc;
    VOS_UINT32              ulULSoftFilterIPSegFail;
}TL_OM_CDS_UL_IP_PKT_STAT_IND_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_CDS_DL_SDU_STAT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS ����SDU��ش���ͳ����
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    /*�����¼�ͳ��*/
    VOS_UINT32              ulDL10msTmrTrigEvent;
    VOS_UINT32              ulDL1msIntTrigEvent;
    VOS_UINT32              ulDLUmtsIntTrigEvent;
    VOS_UINT32              ulDLProcEventNum;

    /*����SDU��Ϣ*/
    VOS_UINT32              ulDLGSMRxSduNum;
    VOS_UINT32              ulDLGSMRxImsNum;
    VOS_UINT32              ulDLGSMFcFreeSduNum;
    VOS_UINT32              ulDLGSMGetDeftRabIdFail;
    VOS_UINT32              ulDLGSMEnQueSucc;
    VOS_UINT32              ulDLGSMEnQueFail;

    VOS_UINT32              ulDLUMTSRxSduNum;
    VOS_UINT32              ulDLUMTSRxImsNum;
    VOS_UINT32              ulDLUMTSFcFreeSduNum;
    VOS_UINT32              ulDLUMTSDirectFreeSduNum;
    VOS_UINT32              ulDLUMTSGetDeftRabIdFail;
    VOS_UINT32              ulDLUMTSEnQueSucc;
    VOS_UINT32              ulDLUMTSEnQueFail;

    VOS_UINT32              ulDLLteRxSduNum;
    VOS_UINT32              ulDLLteRxDbgPkt;
    VOS_UINT32              ulDLLteRxMbmsSdu;
    VOS_UINT32              ulDLLteRxImsNum;
    VOS_UINT32              ulDLLteFcFreeSduNum;
    VOS_UINT32              ulDLLteDirectFreeSduNum;
    VOS_UINT32              ulDLLteGetEpsbIDFail;
    VOS_UINT32              ulDLLteGetDeftEpsbIDFail;
    VOS_UINT32              ulDLLteEnQueSucc;
    VOS_UINT32              ulDLLteEnQueFail;

    VOS_UINT32              ulDLEnSduQueSucc;
    VOS_UINT32              ulDLEnSduQueFail;
    VOS_UINT32              ulDLSduTrigEvent;
}TL_OM_CDS_DL_SDU_STAT_IND_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_CDS_LOOP_BACK_STAT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS ������ش���ͳ����
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    VOS_UINT32              ulLBDLRxSduInGSM;
    VOS_UINT32              ulLBDLRxSduInUMTS;
    VOS_UINT32              ulLBDLRxSduInLte;
    VOS_UINT32              ulLBDLRxSduInNonModeB;
    VOS_UINT32              ulLBDLAllocMemFail;
    VOS_UINT32              ulLBDDLEnQueSucc;
    VOS_UINT32              ulLBDLEnQueFail;
    VOS_UINT32              ulLBULSoftFilterFail;
    VOS_UINT32              ulLBUlSendPktNum;
    VOS_UINT32              ulLBUlClearPktNum;

}TL_OM_CDS_LOOP_BACK_STAT_IND_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_CDS_IMS_PROC_STAT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CDS IMS��ش���ͳ����
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    VOS_UINT32              ulImsULRxFunCallNum;
    VOS_UINT32              ulImsULRxFunParaErr;
    VOS_UINT32              ulImsULRxNicPktNum;
    VOS_UINT32              ulImsULAllocMemFail;
    VOS_UINT32              ulImsULEnQueFail;
    VOS_UINT32              ulImsULEnQueSucc;
    VOS_UINT32              ulImsULTrigImsEvent;
    VOS_UINT32              ulImsULProcImsEvent;
    VOS_UINT32              ulImsULSoftFilterFail;
    VOS_UINT32              ulImsULSendToRan;

    VOS_UINT32              ulImsDLRxImsPkt;
    VOS_UINT32              ulImsDLNdPktNum;
    VOS_UINT32              ulImsDLAllocMemFail;
    VOS_UINT32              ulImsDLSendToNicFail;
    VOS_UINT32              ulImsDLSendToNicSucc;

}TL_OM_CDS_IMS_PROC_STAT_IND_STRU;



/*****************************************************************************
 �ṹ��    : TL_OM_TDS_PDCP_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TDS PDCPͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT32                          ulPdcpUlRecvSduNum;         /*PDCP���д�RABM���յ���SDU��Ŀ*/
    VOS_UINT32                          ulPdcpUlDiscardSduNum;      /*PDCP���ж�����SDU��Ŀ*/
    VOS_UINT32                          ulPdcpUlSendPduToRlcNum;    /*PDCP���з��͸�RLC ��PDU��Ŀ*/
    VOS_UINT32                          ulPdcpDlRecvPduNum;         /*PDCP���д�RLC���յ���PDU��Ŀ*/
    VOS_UINT32                          ulPdcpDlDiscardPduNum;      /*PDCP���ж�����PDU��Ŀ*/
    VOS_UINT32                          ulPdcpDlSendSduToRabmNum;   /*PDCP���з��͸�RABM��SDU��Ŀ*/
}TL_OM_TDS_PDCP_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_TDS_RLC_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TDS RLCͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT32                          ulRlcRbSetupNum;            /*RLCʵ�彨����Ŀ*/
    VOS_UINT32                          ulRlcRbReleaseNum;          /*RLCʵ���ͷ���Ŀ*/
    VOS_UINT32                          ulRlcRbReCfgNum;            /*RLCʵ��������Ŀ*/
    VOS_UINT32                          ulRlcRbResetNum;            /*RLCʵ��Reset������Ŀ*/

    VOS_UINT32                          ulRlcUlRecvSduNum;          /*RLC���д�PDCP�����յ���SDU��Ŀ*/
    VOS_UINT32                          ulRlcUlDiscardSduNum;       /*RLC���ж�����PDCP SDU��Ŀ*/
    VOS_UINT32                          ulRlcUlSendPduToMacNum;     /*RLC���з��͸�MAC��PDU��Ŀ*/
    VOS_UINT32                          ulRlcUlNewTxPduNum;         /*RLC���з����´�PDU��Ŀ*/
    VOS_UINT32                          ulRlcUlReTxPduNum;          /*RLC���з����ش�PDU��Ŀ*/
    VOS_UINT32                          ulRlcUlReTxMaxCntNum;       /*RLC���з����ش��ﵽ����������Ŀ*/
    VOS_UINT32                          ulRlcUlSendPollNum;         /*RLC���з���Poll��Ŀ*/
    VOS_UINT32                          ulRlcUlSendResetNum;        /*RLC���з���Reset��Ŀ*/
    VOS_UINT32                          ulRlcUlRecvAckNum;          /*RLC�����յ�ACK��Ŀ*/
    VOS_UINT32                          ulRlcUlRecvNackNum;         /*RLC�����յ�NACK��Ŀ*/

    VOS_UINT32                          ulRlcDlRecvPduNum;          /*RLC���д�MAC�յ��� PDU��Ŀ*/
    VOS_UINT32                          ulRlcDlDiscardPdu;          /*RLC���ж�����PDU��Ŀ*/
    VOS_UINT32                          ulRlcDlSendSduToPdcpNum;    /*RLC���з��͸�PDCP��SDU��Ŀ*/
    VOS_UINT32                          ulRlcDlSendAckNum;          /*RLC���������෴��ACK��Ŀ*/
    VOS_UINT32                          ulRlcDlSendNackNum;         /*RLC���������෴��NACK��Ŀ*/
    VOS_UINT32                          ulRlcDlRecvPollNum;         /*RLC�����յ�Poll��Ŀ*/
    VOS_UINT32                          ulRlcDlRecvResetNum;        /*RLC�����յ�Reset��Ŀ*/
}TL_OM_TDS_RLC_STAT_INFO_STRU;

#define TDS_MAC_LOSS_MSG_MAX_NUM 10
/*****************************************************************************
 �ṹ��    : TL_OM_TDS_MAC_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TDS MACͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    VOS_UINT32                          ulMacUlRecvSduNum;          /*MAC���н��յ���RLC PDU��Ŀ*/
    VOS_UINT32                          ulMacUlSendPduToPhyNum;     /*MAC���з��͸�PHY��PDU��Ŀ*/
    VOS_UINT32                          ulMacDlRecvPduNum;          /*MAC���д�PHY���յ���PDU��Ŀ*/
    VOS_UINT32                          ulMacDlSendSduToRlcNum;     /*MAC���з��͸�RLC ��PDU��Ŀ*/

    VOS_UINT32                          ulUlSendToDspMsgTotal;
    VOS_UINT32                          ulUlSendToDspMsgSuccess;
    VOS_UINT32                          ulUlSendToDspMsgFail;
    VOS_UINT32                          ulUlSendToDspImmediateMsgTotal;
    VOS_UINT32                          ulUlSendToDspImmediateMsgSuccess;
    VOS_UINT32                          ulUlSendToDspImmediateMsgFail;
    VOS_UINT32                          ulUlSendToDspImmediateMsgError;
    VOS_UINT32                          ulUlSendDpchTotal;
    VOS_UINT32                          ulUlSendPrachTotal;
    VOS_UINT32                          ulUlSendSi;
    VOS_UINT32                          ulUlRecvGrant;
    VOS_UINT32                          ulUlSendEpuchTotal;
    VOS_UINT32                          ulUlSendEpuchNewTx;
    VOS_UINT32                          ulUlSendEpuchReTx;
    VOS_UINT32                          ulDlRecvFpachTotal;
    VOS_UINT32                          ulDlRecvFpachCrcOk;
    VOS_UINT32                          ulDlRecvFpachCrcError;
    VOS_UINT32                          ulDlRecvSccpchTotal;
    VOS_UINT32                          ulDlRecvSccpchCrcOk;
    VOS_UINT32                          ulDlRecvSccpchCrcError;
    VOS_UINT32                          ulDlRecvPccpchTotal;
    VOS_UINT32                          ulDlRecvPccpchCrcOk;
    VOS_UINT32                          ulDlRecvPccpchCrcError;
    VOS_UINT32                          ulDlRecvDpchTotal;
    VOS_UINT32                          ulDlRecvDpchCrcOk;
    VOS_UINT32                          ulDlRecvDpchCrcError;
    VOS_UINT32                          ulDlRecvHspdschTotal;
    VOS_UINT32                          ulDlRecvHspdschCrcOk;
    VOS_UINT32                          ulDlRecvHspdschCrcError;
    VOS_UINT32                          ulSyncLoss;
    VOS_UINT32                          ulLossMsgID[TDS_MAC_LOSS_MSG_MAX_NUM];
    VOS_UINT32                          ulLossMsgIndex;
}TL_OM_TDS_MAC_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_TDS_L2_OVERVIEW_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TDS L2����ͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    /*More to add*/

}TL_OM_TDS_L2_OVERVIEW_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_PDCP_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE PDCPͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    /*More to add*/
    /*UL*/
    VOS_UINT32                          ulULTotlRxDrbSduCnt;
    VOS_UINT32                          ulULTotlTxDrbPduCnt;
    VOS_UINT32                          ulULTotlRxSrbSduCnt;
    VOS_UINT32                          ulULTotlTxSrbPduCnt;
    VOS_UINT32                          usULTotlFreeSduCnt;
    VOS_UINT32                          ulULTotlRbidErrCnt;

    /*DL*/
    VOS_UINT32                          ulDLTotlRxDrbPduCnt;
    VOS_UINT32                          ulDLTotlTxDrbSduCnt;
    VOS_UINT32                          ulDLTotlRxSrbPduCnt;
    VOS_UINT32                          ulDLTotlTxSrbSduCnt;
    VOS_UINT32                          ulDLTotlRbidErrCnt;

    /*Secu Stat*/
    VOS_UINT32                          ulCh1ChkErrIntCnt;
    VOS_UINT32                          ulCh1CmpIntCnt;
    VOS_UINT32                          ulCh1ChkErrEventCnt;
    VOS_UINT32                          ulCh1CmpEventCnt;
    VOS_UINT32                          ulCh2OneCmpIntCnt;
    VOS_UINT32                          ulCh2CmpEventCnt;
    VOS_UINT32                          ulCh3OneCmpIntCnt;
    VOS_UINT32                          ulCh3CmpEventCnt;
    VOS_UINT32                          ulCh3BdFullCnt;

}TL_OM_LTE_PDCP_ALL_RB_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_PDCP_UL_RB_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE PDCP ����RBͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    /*More to add*/
    VOS_UINT32                          ulUlRxSduCnt;
    VOS_UINT32                          ulUlTxPduCnt;
    VOS_UINT32                          ulUlAckedSduCnt;

    VOS_UINT32                          ulUlDiscardMaxCnt;
    VOS_UINT32                          ulUlDisSduCnt;
    VOS_UINT32                          ulUlBufFullDisSduCnt;
    VOS_UINT32                          ulUlReestDiscardCnt;

    VOS_UINT32                          ulUlInvalidSduCnt;
    VOS_UINT32                          ulUlTxCtrlPduNum;
    VOS_UINT32                          ulUlAckEndSnError;

    VOS_UINT32                          ulUlReestStopAckSn;
    VOS_UINT32                          ulUlReestStopNextTxSn;
    VOS_UINT32                          ulUlReestStopHfn;
    VOS_UINT32                          ulUlReestContAckSn;
    VOS_UINT32                          ulUlReestContNextTxSn;
    VOS_UINT32                          ulUlReestContFirstTxSn;
    VOS_UINT32                          ulUlReestContHfn;

    VOS_UINT32                          ulCompSuccCnt;
    VOS_UINT32                          ulCompFailCnt;
    VOS_UINT32                          ulRohcCompCnt;

    VOS_UINT32                          ulSduEnQueFailCnt;

}TL_OM_LTE_PDCP_UL_RB_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_PDCP_DL_RB_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE PDCP����RBͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    /*More to add*/
    VOS_UINT32                          ulDlRxPduCnt;
    VOS_UINT32                          ulDlTxSduCnt;
    VOS_UINT32                          ulDlDiscPduCnt;
    VOS_UINT32                          ulDlDupPduCnt;
    VOS_UINT32                          ulDlRxCtlPduCnt;
    VOS_UINT32                          ulDlTxStrpPduCnt;
    VOS_UINT32                          ulDlTxRohcPduCnt;
    VOS_UINT32                          ulDlErrPduRlcIndCnt;
    VOS_UINT32                          ulDlExcepFreePduCnt;
    VOS_UINT32                          ulDlReestStopLastSubmitSn;
    VOS_UINT32                          ulDlReestStopNextRxSn;
    VOS_UINT32                          ulDlReestContLastSubmitSn;
    VOS_UINT32                          ulDlReestContHfn;
    VOS_UINT32                          ulDlReestStopHfn;
    VOS_UINT32                          ulDlReestContNextRxSn;
    VOS_UINT32                          ulDlReestContFirstRxSn;

    VOS_UINT32                          ulDlExecReordCnt;
    VOS_UINT32                          ulDlCipherBufFullCnt;
    VOS_UINT32                          ulDlAmRlcDataErrCnt;
    VOS_UINT32                          ulDlRlcDataErrCnt;

    VOS_UINT32                          ulDlUnCompFailCnt;
    VOS_UINT32                          ulHoUnCompFailCnt;
    VOS_UINT32                          ulDeCompSuccCnt;
    VOS_UINT32                          ulDeCompFailCnt;
    VOS_UINT32                          ulRohcDeCompCnt;

}TL_OM_LTE_PDCP_DL_RB_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_RLC_UL_RB_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE RLC����ͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    /*More to add*/
    VOS_UINT32              ulRxPdcpSdu;
    VOS_UINT32              ulRxPdcpDropSdu;
    VOS_UINT32              ulRlcDropSdu;
    VOS_UINT32              ulIndTxSduSucc;
    VOS_UINT32              ulIndTxSduFail;
    VOS_UINT32              ulQueFullDropSdu;
    VOS_UINT32              ulDropSduNoRsn;

    VOS_UINT32              ulMacNtfSendNum;
    VOS_UINT32              ulTxPudToMac;
    VOS_UINT32              ulMacNtfRlcNoRes;
    VOS_UINT32              ulTxNullPduToMac;
    VOS_UINT32              ulMacNtfHarqFail;
    VOS_UINT32              ulResNotEnough;

    VOS_UINT32              ulRxCtrlPdu;
    VOS_UINT32              ulRxDlCtrlPdu;
    VOS_UINT32              ulRxCtrlPduNackSNOutWIn;
    VOS_UINT32              ulTxCtrlPdu;
    VOS_UINT32              ulTotalReTxPdu;
    VOS_UINT32              ulReTxPollTmr;
    VOS_UINT32              ulIndRrcLinkErr;
    VOS_UINT32              ulIndRrcRlcErr;

    VOS_UINT32              ulRxRrcRelease;
    VOS_UINT32              ulRrcCfg;
    VOS_UINT32              ulRrcCfgFail;
    VOS_UINT32              ulReestablish;
    VOS_UINT32              ulReestablishFail;
    VOS_UINT32              ulReTxSegNum;
    VOS_UINT32              ulInputPdu;
    VOS_UINT32              ulInputPduSeg;

}TL_OM_LTE_RLC_UL_RB_STAT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TL_OM_LTE_RLC_DL_RB_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE RLC ����ͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU    stCommHead;

    /*More to add*/

    VOS_UINT32              ulRxMacPdu;
    VOS_UINT32              ulDropMacPdu;
    VOS_UINT32              ulProcMacPduFail;
    VOS_UINT32              ulReRecvSnDrop;
    VOS_UINT32              ulReorderTmrOut;

    VOS_UINT32              ulRxCtrlPdu;
    VOS_UINT32              ulTxEnbCtrlPdu;
    VOS_UINT32              ulTxDlCtrlPdu;
    VOS_UINT32              ulTxDlCtrlPduFail;

    VOS_UINT32              ulTxSduToPdcpSucc;
    VOS_UINT32              ulTxSduToPdcpFail;
    VOS_UINT32              ulAllocSduMsgFail;

    VOS_UINT32              ulResmPdufail;
    VOS_UINT32              ulDropHeadSgmnt;
    VOS_UINT32              ulDropTailSgmnt;

    VOS_UINT32              ulStartTmrFail;
    VOS_UINT32              ulStopTmrFail;

    VOS_UINT32              ulIndRrcRlcMemErr;
    VOS_UINT32              ulIndRrcRlcErr;
    VOS_UINT32              ulRlcDlCfg;
    VOS_UINT32              ulRlcDlCfgFail;
    VOS_UINT32              ulRlcDlRealse;
    VOS_UINT32              ulReCfg;
    VOS_UINT32              ulReCfgFail;
    VOS_UINT32              ulRecePduSeg;
    VOS_UINT32              ulAssemPduSeg;

    VOS_UINT32              ulPduLiError;
    VOS_UINT32              ulPduLsfError;
    VOS_UINT32              ulPduRedupDiscard;

    VOS_UINT32              ulRxPduSize;

}TL_OM_LTE_RLC_DL_RB_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_MAC_RA_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE MAC �������ͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{

    TL_OM_COMM_HEAD_STRU                      stCommHead;

    /*More to add*/
    VOS_UINT32                                ulMacRaReq;
    VOS_UINT32                                ulPdcchNonContentRaReq;
    VOS_UINT32                                ulPdcchContentRaReq;
    VOS_UINT32                                ulRrcNonContentRaReq;
    VOS_UINT32                                ulRrcContentRaReq;
    VOS_UINT32                                ulSelectGroupA;
    VOS_UINT32                                ulSelectGroupB;

    VOS_UINT32                                ulRecvPhyRaCnf;
    VOS_UINT32                                ulRepeatRaReq;
    VOS_UINT32                                ulMaxRaReq;

    VOS_UINT32                                ulRarTimerOut;
    VOS_UINT32                                ulContentTimerOut;
    VOS_UINT32                                ulRaCnfTimerOut;

    VOS_UINT32                                ulRaCauseFail;
    VOS_UINT32                                ulSelectGroupABFail;

    VOS_UINT32                                ulRecvRarNum;
    VOS_UINT32                                ulRecvRarSucc;
    VOS_UINT32                                ulRecvRarFail;
    VOS_UINT32                                ulRarBiNum;
    VOS_UINT32                                ulRarProcSucc;
    VOS_UINT32                                ulNonContentSucc;

    VOS_UINT32                                ulRecvContentionNum;
    VOS_UINT32                                ulWaitContentionProcFail;

    VOS_UINT32                                ulContentTcrntiSucc;
    VOS_UINT32                                ulContentCrntiSucc;
    VOS_UINT32                                ulContentNoMatch;

    VOS_UINT32                                ulSchMsg3Num;
    VOS_UINT32                                ulSchMsg3ReTransNum;
    VOS_UINT32                                ulGetMsg3FromRlcFail;

    VOS_UINT32                                ulMacNewMsg3Rrctrig;
    VOS_UINT32                                ulMacNewMsg3Mactrig;
    VOS_UINT32                                ulMacNewMsg3MacPdu;
    VOS_UINT32                                ulHoMsg3NoRecvCmp;
    VOS_UINT32                                ulMacRetranMsg3Num;
    VOS_UINT32                                ulMacActiveRetranMsg3Num;
    VOS_UINT32                                ulMacOverMsg3MaxRetran;

    VOS_UINT32                                ulStateErrorDrop;
    VOS_UINT32                                ulSendRlcSetupOkNum;
    VOS_UINT32                                ulRarSchedNotFinishNum;
    VOS_UINT32                                ulNoRarCfgCnfNum;

} TL_OM_LTE_MAC_RA_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_MAC_UL_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE MAC ����ͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                      stCommHead;

    /*More to add*/
    VOS_UINT32                                ulRecvSchFrmInd;
    VOS_UINT32                                ulRecvUnexptedSchFrm;
    VOS_UINT32                                ulRecvSameFrame;

    VOS_UINT32                                ulTotalSchNotFinishNum;

    VOS_UINT32                                ulMacSchedMacPduSuccNum;
    VOS_UINT32                                ulMacSchedMacPduFailNum;
    VOS_UINT32                                ulMacPduNotFree;
    VOS_UINT32                                ulMacRecvRlcPduTotal;

    VOS_UINT32                                ulSendPhr;
    VOS_UINT32                                ulGetPhrErr;
    VOS_UINT32                                ulSendSr;
    VOS_UINT32                                ulPhyCancelSr;
    VOS_UINT32                                ulMacCancelSr;
    VOS_UINT32                                ulTaTimeOutNum;
    VOS_UINT32                                ulSCellDeacTimeOutNum;
    VOS_UINT32                                ulSendPadding;
    VOS_UINT32                                ulSendPadHead;

    VOS_UINT32                                ulGetRlcNuLLBuffNum;
    VOS_UINT32                                ulGetCcchInActiveNum;
    VOS_UINT32                                ulGetLchPriFromRlcFail;

    VOS_UINT32                                ulMsg3NotContainHoCmp;

    VOS_UINT32                                ulUlGrantNotSchErr;

    VOS_UINT32                                ulPhyReleaseUlSps;
    VOS_UINT32                                ulMacReleaseUlSps;

    VOS_UINT32                                ulForbidDspSleepFail;
    VOS_UINT32                                ulWriteDediMailBoxFail;
    VOS_UINT32                                ulSendShortBsr;
    VOS_UINT32                                ulSendLongBsr;
    VOS_UINT32                                ulSendAbnormBsr;
    VOS_UINT32                                ulSendPadBsr;
    VOS_UINT32                                ulSendPadShortBsr;
    VOS_UINT32                                ulSendPadLongBsr;
    VOS_UINT32                                ulSendTruncatedBsr;
    VOS_UINT32                                ulCancelBsr;
    VOS_UINT32                                ulLongToShortBsr;

}TL_OM_LTE_MAC_UL_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_MAC_DL_STAT_INFO_STRUE
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE MAC ����ͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                      stCommHead;

    /*More to add*/
    VOS_UINT32                                ulDlDmaInstallOk;                 /*V9R1*/
    VOS_UINT32                                ulDlCommTbBuffAddErr;             /*V9R1*/
    VOS_UINT32                                ulDlCommTbExhaustErr;             /*V9R1*/
    VOS_UINT32                                ulDlDmaInstallErr;                /*V9R1*/
    VOS_UINT32                                ulSemTakeTotal;
    VOS_UINT32                                ulDlTbRecvIntRsp;                 /*V7R2*/
    VOS_UINT32                                ulDlTbRecvIntErr;                 /*V7R2*/
    VOS_UINT32                                ulDlForbidDspSleepFail;           /*V7R2*/

    VOS_UINT32                                ulActDemultipleSucc;
    VOS_UINT32                                ulActDemultipleFail;
    VOS_UINT32                                ulActSendRlcErrorNum;
    VOS_UINT32                                ulActSendRlcNum;
    VOS_UINT32                                ulActDemulOneLchErr;
    VOS_UINT32                                ulActRecvPadding;
    VOS_UINT32                                ulActRecvTa;
    VOS_UINT32                                ulActRecvScellActivation;
    VOS_UINT32                                ulActRecvDrx;
    VOS_UINT32                                ulActRecvErrPkt;

    VOS_UINT32                                ulDlTbAddrNull;
    VOS_UINT32                                ulDlTbMemCheckErr;
    VOS_UINT32                                ulDlTbCheckErr;
    VOS_UINT32                                ulDlTbCellIndexErr;
    VOS_UINT32                                ulDlTbSCellDeactived;
    VOS_UINT32                                ulOterStateRecvTb;
    VOS_UINT32                                ulRadnomStateRecvTb;
    VOS_UINT32                                ulRadnomStateRecvTbErr;
    VOS_UINT32                                ulHoEnQueTb;
    VOS_UINT32                                ulHoDeQueTb;
    VOS_UINT32                                ulHoDeQueTbErr;
    VOS_UINT32                                ulMacPdcchRecvTb;

    VOS_UINT32                                ulRecvBcchTb;
    VOS_UINT32                                ulRecvPbchTb;
    VOS_UINT32                                ulRecvPchTb;

    VOS_UINT32                                ulDlTbEnqueFail;                  /*V9R1*/
    VOS_UINT32                                ulDlTbOverWrite;                  /*V9R1*/
    VOS_UINT32                                ulDlDmaNotDone;                   /*V9R1*/
    VOS_UINT32                                ulDlStartDmaNum;                  /*V9R1*/
    VOS_UINT32                                ulDlTbIntSleepCnt;                /*V9R1*/
    VOS_UINT32                                ulDlTbIntAllocMemFail;
    VOS_UINT32                                ulDlLteMasterGetMemFail;
    VOS_UINT32                                ulDlLteSlaveGetMemFail;
    VOS_UINT32                                ulDlTbRecvQueFull;
    VOS_UINT32                                ulDlOtherErrInd;

}TL_OM_LTE_MAC_DL_STAT_INFO_STRU;

#define TL_OM_LMAC_CA_MAX_RPT_CELL_NUM      (8)
/*****************************************************************************
 �ṹ��    : TL_OM_LTE_MAC_CA_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE MAC CA ͳ����Ϣ�ϱ��ṹ��.Index =0 Ϊ��С��.
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                      stCommHead;

    /*More to add*/
    LSCELL_STATUS_ENUM_UINT8                  ucScellStatusType[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];
    LSCELL_DEACT_TIMER_VIEW_ENUM_UINT32       ulScellDeactTimer[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];
    VOS_UINT32                                ulConfigedNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];           /*���ö�ӦSCell����*/
    VOS_UINT32                                ulDeletedNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];            /*ɾ����ӦSCell����*/
    VOS_UINT32                                ulRecvActiveMceNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];      /*���յ���ӦSCell�������Ԫ����*/
    VOS_UINT32                                ulSendActiveToPhyNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];    /*���Ͷ�ӦSCell�ļ��������DSP�ĸ���*/
    VOS_UINT32                                ulRecvDeactiveMceNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];    /*���յ���ӦSCellȥ�������Ԫ����*/
    VOS_UINT32                                ulSendDeactiveToPhyNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];  /*���Ͷ�ӦSCell��ȥ���������DSP�ĸ���*/
    VOS_UINT32                                ulRecvDlAssignmentNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];   /*���յ���ӦSCell������ָ�ɵĸ���*/
    VOS_UINT32                                ulDeactiveTimerOutNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];   /*��ӦSCellȥ���ʱ����ʱ�Ĵ���*/
    VOS_UINT32                                ulRecvDlTbNum[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];           /*��ӦSCell���յ�����TB��ĸ���*/
    VOS_UINT32                                ulRecvDlTbByte[TL_OM_LMAC_CA_MAX_RPT_CELL_NUM];          /*��ӦSCell���յ�����TB�ֽ���*/

}TL_OM_LTE_MAC_CA_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_MAC_MBMS_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE MAC MBMS ͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                      stCommHead;

    /*More to add*/
    VOS_UINT32                                ulMchRecvSucc;                    /*MCH�����ɹ�����*/
    VOS_UINT32                                ulMchRecvFail;                    /*MCH����ʧ�ܸ���*/
    VOS_UINT32                                ulMchRecvPadding;
    VOS_UINT32                                ulMchMsiNum;
    VOS_UINT32                                ulPmchInValidCnt;
    VOS_UINT32                                ulMcchRecvCnt;
    VOS_UINT32                                ulMtchRecvCnt;

}TL_OM_LTE_MAC_MBMS_STAT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_L2_OVERVIEW_STAT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE L2����ͳ����Ϣ�ϱ��ṹ��
*****************************************************************************/
typedef struct
{
    TL_OM_COMM_HEAD_STRU                stCommHead;

    /*More to add*/

}TL_OM_LTE_L2_OVERVIEW_STAT_INFO_STRU;



/*****************************************************************************
 �ṹ��    : TL_OM_LTE_PDCP_PDU_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE PDCP PDU��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32   ulMsgName;
    VOS_UINT16   usFrameNum;
    VOS_UINT16   usSubFrameNum;

    VOS_UINT8    ucRbId;
    VOS_UINT8    ucPdcpState;
    VOS_UINT8    ucMode;
    VOS_UINT8    ucResv;

    VOS_UINT32   ulPdcpSn;
    VOS_UINT32   ulCount;
    VOS_UINT32   ulHfn;
    VOS_UINT32   ulSduDataLen;
    VOS_UINT8    aucData[4];

}TL_OM_LTE_PDCP_SRB_INFO_RPT_STRU;


/*****************************************************************************
 �ṹ��    : TL_OM_LTE_PDCP_RRC_ENB_CNF_INFO_RPT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE PDCP SRB���յ�ACKȷ����Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32   ulMsgName;
    VOS_UINT16   usFrameNum;
    VOS_UINT16   usSubFrameNum;

    VOS_UINT8    ucRbId;
    VOS_UINT8    ucResv[3];

    VOS_UINT32   ulPdcpSn;
    VOS_UINT32   ulCount;
    VOS_UINT32   ulNextTxSn;

}TL_OM_LTE_PDCP_RRC_CNF_INFO_RPT_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_RLC_UL_SRB_PDU_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE RLC ����SRB PDU��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32   ulMsgName;
    VOS_UINT16   usFrameNum;
    VOS_UINT16   usSubFrameNum;

    VOS_UINT8    ucRbId;
    VOS_UINT8    ucLchId;
    VOS_UINT8    ucRlcState;
    VOS_UINT8    ucRsv;


    VOS_UINT16   usPduSn;
    VOS_UINT16   usDataLen;

    VOS_UINT8    ucRF;
    VOS_UINT8    ucPolling;
    VOS_UINT8    ucFI;
    VOS_UINT8    ucE;

    VOS_UINT16   usStartSduSn;
    VOS_UINT16   usEndSduSn;

    /*�ô��ڱ���������RLC���ݰ���Ĵ��ڱ���*/
    VOS_UINT16    usRetxNum;
    VOS_UINT16    usVTA;
    VOS_UINT16    usVTS;
    VOS_UINT16    usVTMS;
    VOS_UINT8     aucPduData[TL_OM_LTE_RLC_RPT_PDU_LEN];
}TL_OM_LTE_RLC_UL_SRB_PDU_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LRLC_CTRLPDU_NACK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ״̬PDU�е�NACK�����򣬰���NACKSN E1 E2 SOSTART SOEND
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulNackSn;
    VOS_UINT8                   ucE1;
    VOS_UINT8                   ucE2;
    VOS_UINT8                   ucCtrlFlag;/*1:PDU�ش�������һ.0:�ش��������ۼ�*/
    VOS_UINT8                   ucRev;
    VOS_UINT32                  ulSoStart;
    VOS_UINT32                  ulSoEnd;
}TL_OM_LTE_RLC_CTRLPDU_NACK_STRU;



/*****************************************************************************
 �ṹ��    : TL_OM_LTE_RLC_UL_TX_CTRL_PDU_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE RLC ���з���״̬������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32   ulMsgName;
    VOS_UINT16   usFrameNum;
    VOS_UINT16   usSubFrameNum;

    /*More to add*/
    VOS_UINT8                           ucRbId;
    VOS_UINT8                           ucLchId;
    VOS_UINT8                           ucRlcState;
    VOS_UINT8                           ucResv;

    VOS_UINT32                          ulAckSn;
    VOS_UINT32                          ulNackNum;

    TL_OM_LTE_RLC_CTRLPDU_NACK_STRU     astNack[TL_OM_LTE_RLC_MAX_NACK_NUM];

}TL_OM_LTE_RLC_UL_TX_CTRL_PDU_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_RLC_DL_RX_CTRL_PDU_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE RLC ���з���״̬������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32   ulMsgName;
    VOS_UINT16   usFrameNum;
    VOS_UINT16   usSubFrameNum;

    /*More to add*/
    VOS_UINT8    ucRbId;
    VOS_UINT8    ucLchId;
    VOS_UINT8    ucRlcState;
    VOS_UINT8    ucPollFlg;

    /*���ڱ���*/
    VOS_UINT16   usVTA;
    VOS_UINT16   usVTS;
    VOS_UINT16   usVTMS;
    VOS_UINT16   usPollReTxSn;

    VOS_UINT32   ulAckSn;
    VOS_UINT32   ulNackNum;

    TL_OM_LTE_RLC_CTRLPDU_NACK_STRU     astNack[TL_OM_LTE_RLC_MAX_NACK_NUM];

}TL_OM_LTE_RLC_DL_RX_CTRL_PDU_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TL_OM_LTE_RLC_DL_AMD_PDU_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE RLC ����AM DATA PDU��Ϣ
*****************************************************************************/
typedef struct
{

    VOS_UINT8                           ucRbId;
    VOS_UINT8                           ucLchId;
    VOS_UINT8                           ucRlcState;
    VOS_UINT8                           ucResv;

    /*���ڱ����Ǵ����PDU֮ǰ��ֵ*/
    VOS_UINT16                          usVRr;
    VOS_UINT16                          usVRmr;

    VOS_UINT16                          usVRx;
    VOS_UINT16                          usVRh;

    VOS_UINT16                          usVRms;
    VOS_UINT8                           ucCtrlRptFlg;
    VOS_UINT8                           ucStatusProhitFlg;

    VOS_UINT16                          usPduSn;
    VOS_UINT16                          usDataLen;

    VOS_UINT8                           ucRF;
    VOS_UINT8                           ucPolling;
    VOS_UINT8                           ucFI;
    VOS_UINT8                           ucE;

    VOS_UINT8                           aucPduData[TL_OM_LTE_RLC_RPT_PDU_LEN];
}TL_OM_LTE_RLC_DL_AMD_PDU_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TL_OM_LTE_RLC_DL_SRB_PDU_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : LTE RLC ����SRB PDU��Ϣ�ϱ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32   ulMsgName;
    VOS_UINT16   usFrameNum;
    VOS_UINT16   usSubFrameNum;
    TL_OM_LTE_RLC_DL_AMD_PDU_INFO_STRU  stDlPdu;
}TL_OM_LTE_RLC_DL_SRB_PDU_INFO_STRU;



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
extern VOS_VOID LPS_OM_LOG( const VOS_CHAR  *pcFileName,  VOS_UINT32  ulLineNum,
                                  VOS_UINT32      ulModuleId,   VOS_UINT32 ulLevel,
                                  const VOS_CHAR  *pcString );
extern VOS_VOID LPS_OM_LOG1( const VOS_CHAR   *pcFileName, VOS_UINT32  ulLineNum,
                                   VOS_UINT32  ulModuleId,       VOS_UINT32 ulLevel,
                                   const VOS_CHAR    *pcString,  VOS_INT32  lPara1);
extern VOS_VOID LPS_OM_LOG2( const VOS_CHAR   *pcFileName, VOS_UINT32  ulLineNum,
                                   VOS_UINT32 ulModuleId,        VOS_UINT32 ulLevel,
                                   const VOS_CHAR   *pcString,   VOS_INT32  lPara1,
                                   VOS_INT32  lPara2);
extern VOS_VOID LPS_OM_LOG3( const VOS_CHAR  *pcFileName,  VOS_UINT32  ulLineNum,
                                   VOS_UINT32 ulModuleId,        VOS_UINT32 ulLevel,
                                   const VOS_CHAR   *pcString,   VOS_INT32  lPara1,
                                   VOS_INT32  lPara2,            VOS_INT32  lPara3);
extern VOS_VOID LPS_OM_LOG4( const VOS_CHAR   *pcFileName, VOS_UINT32  ulLineNum,
                                   VOS_UINT32 ulModuleId,        VOS_UINT32 ulLevel,
                                   const VOS_CHAR   *pcString,   VOS_INT32  lPara1,
                                   VOS_INT32  lPara2,            VOS_INT32  lPara3,
                                   VOS_INT32  lPara4);
extern VOS_UINT32  OM_GetTimeStamp(void);/*��ȡ����Ϊ0.1�����ʱ���*/

extern VOS_VOID TL_OM_ReportSingleUpEvent(
                                                TL_UP_EVENT_ENUM_UINT16 usEvent,
                                                VOS_UINT16 usPid,
                                                VOS_UINT16 usRbId,
                                                VOS_UINT16 usFrameNum,
                                                VOS_UINT16 usSubFrameNum);

extern VOS_VOID TL_OM_ReportAllUpEvent(VOS_VOID);

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

#endif /* end of OmCommon.h */
