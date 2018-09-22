/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: \vos\include\vos\v_id.h                                         */
/*                                                                           */
/* Author: Qin Peifeng                                                       */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2000-04-21                                                          */
/*                                                                           */
/* Description:                                                              */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2000-04-21                                                       */
/*    Author: Qin Peifeng                                                    */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/
#ifndef _V_ID_H
#define _V_ID_H

#include "v_iddef.h"
#include "VosPidDef.h"
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/* To decide to use dynamic FID/PID or static FID/PID, if using static */
#define VOS_USE_DYNAMIC_FIDPID                 VOS_NO

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
extern VOS_UINT32 HPA_FIDInit( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 GAS_FidPidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 LLC_FID_Init( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 PBD_FID_Init( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 WTTF_MAC_RLC_UlFidInit( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 WTTF_MAC_RLC_DlFidInit( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 WuepsRabmFidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 NAS_MML_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 WuepsCmFidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 USIMM_FID_Init(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 WuepsSIFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 WuepsTafFidInit( enum  VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 WuepsSleepFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 UE_FIDInit( enum  VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 GRM_FID_Init(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 WuepsOMFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 RRC_FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 PS_OM_FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 CM_FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 LMAC_RLC_UlFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 LMAC_RLC_DlFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 LHPA_FidPidInit(enum VOS_INIT_PHASE_DEFINE ip);
//extern VOS_UINT32 COMM_FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 MSP_DiagFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 MSP_L4FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 MSP_FtmFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 OMCallBackFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 Spy_FID_Init(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 OM_AgentFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 CBPCA_FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 CSIMA_FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 OM_NoSigFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 FC_CCORE_FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 TTF_MemRbFreeFidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 CDS_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern VOS_UINT32 NDCLIENT_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern VOS_UINT32 WuepsSleepFidInit(enum VOS_INIT_PHASE_DEFINE ip);

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
extern VOS_UINT32 process_pdc_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
/*extern VOS_UINT32 process_rlc_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );*/
extern VOS_UINT32 process_mac_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 hl100_SndCmd_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
#endif

#elif (OSA_CPU_ACPU == VOS_OSA_CPU)
extern VOS_UINT32 APP_NDIS_FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 DMS_DsFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 OM_AcpuFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 OM_AcpuCallBackFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 RNIC_FidInit( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 NFExt_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 FC_ACORE_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern VOS_UINT32 CPULOAD_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern VOS_UINT32 IMM_RbMemFreeFidInit( enum VOS_INIT_PHASE_DEFINE ip );

extern VOS_UINT32 MSP_AppDiagFidInit(enum VOS_INIT_PHASE_DEFINE ip);

#endif  /*(OSA_CPU_CCPU == VOS_OSA_CPU)*/

#ifdef HPA_ITT
extern VOS_UINT32 MAPS_Stub_Fid_InitFun(enum VOS_INIT_PHASE_DEFINE InitPhase);
#endif  /*HPA_ITT*/

#ifdef USP_2_0
extern VOS_UINT32 WHPA_FidPidInit( enum VOS_INIT_PHASE_DEFINE ip );
#endif  /*USP_2_0*/

#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_UINT32 WuepsATFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 RNIC_FidInit( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 IMM_RbMemFreeFidInit( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 OM_AcpuFidInit( enum VOS_INIT_PHASE_DEFINE ip );
#endif  /*(VOS_WIN32 == VOS_OS_VER)*/

extern VOS_UINT32 ADS_UL_FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 ADS_DL_FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 CSD_FidInit(enum VOS_INIT_PHASE_DEFINE enInitPhase);

extern VOS_UINT32 TAF_AGENT_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase);

/* DSP ����  */
extern VOS_UINT32 UPHY_APM_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 UPHY_UCOM_WphyFidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 UPHY_UCOM_GphyFidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 UPHY_DRX_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 UPHY_IDLE_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 UPHY_UCOM_UpaFidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 UPHY_UCOM_WmeasFidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase);
/* DSP ���� end */

/* Voice in ACPU start */
extern VOS_UINT32 VOICE_NormalFidInit(enum VOS_INIT_PHASE_DEFINE enInitPhrase);
extern VOS_UINT32 VOICE_RtFidInit(enum VOS_INIT_PHASE_DEFINE enInitPhrase);

extern VOS_UINT32 IMSA_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 IMSVA_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 IPS_MNTN_CCORE_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
/************************* MODEM ID DEFINITION ******************************/

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
extern VOS_UINT32 I1_USIMM_FID_Init(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 I1_WuepsSIFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 I1_WuepsSleepFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 I1_GAS_FidPidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 I1_NAS_MML_FidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 I1_WuepsCmFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 I1_WuepsRabmFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 I1_WuepsTafFidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 I1_PBD_FID_Init(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 I1_LLC_FID_Init(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 I1_GRM_FID_Init(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 I1_UPHY_UCOM_GphyFidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 I1_UPHY_APM_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 I1_UPHY_DRX_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 I1_UPHY_IDLE_FidInit ( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 MTC_FidInit (enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_UINT32 RRM_FidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
#endif  /*( FEATURE_MULTI_MODEM == FEATURE_ON )*/

extern VOS_UINT32 CMMCA_FidInit (enum VOS_INIT_PHASE_DEFINE ip);

/************************* MACRO & TYPE DEFINITION ***************************/
/* VOS���ģʽ�µ��û�ģ�黮����Ϣ */
#if (OSA_CPU_CCPU == VOS_OSA_CPU)
BEGIN_FID_DEFINITION()
/* add your FID here, e.g.
  * DEFINE_FID(VOS_FID_APP0)
  * DEFINE_FID(VOS_FID_APPx) */
     DEFINE_FID(WUEPS_FID_OM)
     DEFINE_FID(I0_MAPS_USIMM_FID)
     DEFINE_FID(I0_MAPS_SI_FID)
     DEFINE_FID(MSP_FID_DIAG_CCPU)
     DEFINE_FID(MSP_L4_FID)
     DEFINE_FID(MSP_HAL_FID)
     /* Add by h00135900*/
     DEFINE_FID(MSP_FTM_FID)
     DEFINE_FID(I0_UEPS_FID_SL)
     DEFINE_FID(UEPS_FID_RM)
     DEFINE_FID(I0_UEPS_FID_RR)
     DEFINE_FID(I0_UEPS_FID_GRM)
     DEFINE_FID(WUEPS_FID_HPA)
     DEFINE_FID(I0_WUEPS_FID_MM)
     DEFINE_FID(I0_WUEPS_FID_CM)
#if (VOS_WIN32 == VOS_OS_VER)
     DEFINE_FID(WUEPS_FID_AT)
     DEFINE_FID(ACPU_FID_OM)
#endif  /*(VOS_WIN32 == VOS_OS_VER)*/
     DEFINE_FID(I0_WUEPS_FID_RABMSM)
     DEFINE_FID(I0_WUEPS_FID_TAF)
     DEFINE_FID(WUEPS_FID_OM_CALLBACK)
     DEFINE_FID(WUEPS_FID_SPY)
     DEFINE_FID(AGENT_FID_OM)
     DEFINE_FID(PS_FID_RRC)
     DEFINE_FID(PS_FID_CM)
     DEFINE_FID(PS_FID_OM)
     DEFINE_FID(PS_FID_RM_UL)
     DEFINE_FID(PS_FID_RM_DL)
     DEFINE_FID(PS_FID_HPA)
     DEFINE_FID(PS_FID_COMM)
     DEFINE_FID(PS_FID_IMSA)
     DEFINE_FID(PS_FID_IMSVA)
     /*add for L2 2011-07-04 start */
     DEFINE_FID(UEPS_FID_FLOWCTRL_C)
     DEFINE_FID(UEPS_FID_RM_DL)
     DEFINE_FID(WUEPS_FID_NOSIG)
     /*add for L2 2011-07-04 start */
#ifdef HPA_ITT
     DEFINE_FID(MAPS_STUB_FID)
#endif  /*HPA_ITT*/

#if (VOS_WIN32 == VOS_OS_VER)
    DEFINE_FID(WUEPS_FID_ITTSTUB)
    DEFINE_FID(ACPU_FID_ADS_UL)
    DEFINE_FID(ACPU_FID_ADS_DL)
    DEFINE_FID(ACPU_FID_CSD)
    DEFINE_FID(ACPU_FID_RNIC)
    DEFINE_FID(ACPU_FID_TAFAGENT)
    DEFINE_FID(UEPS_FID_IMM_RB_FREE)
    DEFINE_FID(MSP_APP_DS_FID)
#endif  /*(VOS_WIN32 == VOS_OS_VER)*/

    DEFINE_FID(UEPS_FID_TTF_MEM_RB_FREE)
    DEFINE_FID(UEPS_FID_CDS)
    DEFINE_FID(UEPS_FID_NDCLIENT)
    DEFINE_FID(I0_UEPS_FID_PBD)
    DEFINE_FID(HL1_FID_SNDCMD)
    /*DEFINE_FID(TPS_FID_RLC)*/
    DEFINE_FID(TPS_FID_MAC)
    DEFINE_FID(TPS_FID_PDC)

    DEFINE_FID(WUEPS_FID_NVIM_FLUSH)
    DEFINE_FID(I0_WUEPS_FID_SLEEP)
    /* dsp ���� */
    DEFINE_FID(I0_DSP_FID_APM)
    DEFINE_FID(DSP_FID_UPA)
    DEFINE_FID(DSP_FID_WPHY)
    DEFINE_FID(I0_DSP_FID_GPHY)
    DEFINE_FID(I0_DSP_FID_DRX)
    DEFINE_FID(I0_DSP_FID_IDLE)
    DEFINE_FID(DSP_FID_WMEAS)
    /* dsp ���� end */

    /* add for VoLTE start */
    DEFINE_FID(UEPS_FID_IPS_CCORE)

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    DEFINE_FID(I1_MAPS_USIMM_FID)
    DEFINE_FID(I1_MAPS_SI_FID)
    DEFINE_FID(I1_WUEPS_FID_SLEEP)
    DEFINE_FID(I1_UEPS_FID_RR)
    DEFINE_FID(I1_WUEPS_FID_MM)
    DEFINE_FID(I1_WUEPS_FID_CM)
    DEFINE_FID(I1_WUEPS_FID_RABMSM)
    DEFINE_FID(I1_WUEPS_FID_TAF)
    DEFINE_FID(I1_UEPS_FID_SL)
    DEFINE_FID(I1_UEPS_FID_PBD)
    DEFINE_FID(I1_UEPS_FID_GRM)
    DEFINE_FID(I1_DSP_FID_APM)
    DEFINE_FID(I1_DSP_FID_GPHY)
    DEFINE_FID(I1_DSP_FID_DRX)
    DEFINE_FID(I1_DSP_FID_IDLE)
    DEFINE_FID(UEPS_FID_MTC)

    DEFINE_FID(UEPS_FID_RRM)

#endif  /*( FEATURE_MULTI_MODEM == FEATURE_ON )*/

    DEFINE_FID(WUEPS_FID_CBPCA)
    DEFINE_FID(WUEPS_FID_CSIMA)

    DEFINE_FID(WUEPS_FID_CMMCA)
END_FID_DEFINITION()
#endif  /*(OSA_CPU_CCPU == VOS_OSA_CPU)*/

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
BEGIN_FID_DEFINITION()
/* add your FID here, e.g.
 * DEFINE_FID(VOS_FID_APP0)
 * DEFINE_FID(VOS_FID_APPx) */
    DEFINE_FID(UEPS_FID_IMM_RB_FREE)
    DEFINE_FID(MSP_APP_DS_FID)
    DEFINE_FID(PS_FID_APP_NDIS_PPP_DIPC)
    DEFINE_FID(ACPU_FID_OM_CALLBACK)
    DEFINE_FID(ACPU_FID_OM)
    /* Linux add begin��w68271 */
    DEFINE_FID(ACPU_FID_RNIC)
    DEFINE_FID(ACPU_FID_NFEXT)
    /* Added by L60609 for PS Project��2011-12-06,  Begin*/
    DEFINE_FID(ACPU_FID_ADS_UL)
    DEFINE_FID(ACPU_FID_ADS_DL)
    DEFINE_FID(ACPU_FID_CSD)
    /* Added by L60609 for PS Project��2011-12-06,  End*/
    DEFINE_FID(ACPU_FID_TAFAGENT)
    DEFINE_FID(ACPU_FID_CPULOAD)
    DEFINE_FID(UEPS_FID_FLOWCTRL_A)
#if (RAT_MODE != RAT_GU)
    /* Add by h00135900*/
    DEFINE_FID(MSP_FID_DIAG_ACPU)
#endif  /*(RAT_MODE != RAT_GU)*/

#if (FEATURE_VOICE_UP == FEATURE_ON)
    /* Voice in ACPU start */
    DEFINE_FID(ACPU_FID_MED_RT)
    DEFINE_FID(ACPU_FID_MED)
#endif
    /* Linux add end��w68271 */

END_FID_DEFINITION()
#endif  /*(OSA_CPU_ACPU == VOS_OSA_CPU)*/

#ifdef VOS_OSA_SINGLE_ARM
#define VOS_PID_DOPRAEND                (VOS_PID_CPU_ID_0_DOPRAEND)
#define VOS_PID_BUTT                    (VOS_CPU_ID_1_PID_BUTT)

#else

#if (OSA_CPU_CCPU == VOS_OSA_CPU)
#define VOS_PID_DOPRAEND                (VOS_PID_CPU_ID_0_DOPRAEND)
#define VOS_PID_BUTT                    (VOS_CPU_ID_0_PID_BUTT)
#endif

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#define VOS_PID_DOPRAEND                (VOS_PID_CPU_ID_1_DOPRAEND)
#define VOS_PID_BUTT                    (VOS_CPU_ID_1_PID_BUTT)
#endif

#endif


/* Ϊ�˺�MAPS2000����, ��ʱת��������PID */
#define WUEPS_PID_PHY                   WUEPS_PID_HPA
#define WUEPS_PID_RRCF                  WUEPS_PID_WRR

/* GU NAS PIDת���� */
#define WUEPS_PID_LMM                   PS_PID_MM
#define WUEPS_PID_ESM                   PS_PID_ESM

/*for new HPA */
#define UEPS_PID_WHPA                   WUEPS_PID_HPA
#define UEPS_PID_GHPA_PP                UEPS_PID_GHPA

#define PS_PID_APP                      PS_PID_OM

#if defined(INSTANCE_1)
#define MAPS_USIMM_FID   I1_MAPS_USIMM_FID
#define MAPS_SI_FID      I1_MAPS_SI_FID
#define WUEPS_FID_SLEEP  I1_WUEPS_FID_SLEEP
#define UEPS_FID_RR      I1_UEPS_FID_RR
#define WUEPS_FID_MM     I1_WUEPS_FID_MM
#define WUEPS_FID_CM     I1_WUEPS_FID_CM
#define WUEPS_FID_RABMSM I1_WUEPS_FID_RABMSM
#define WUEPS_FID_TAF    I1_WUEPS_FID_TAF
#define UEPS_FID_SL      I1_UEPS_FID_SL
#define UEPS_FID_PBD     I1_UEPS_FID_PBD
#define UEPS_FID_GRM     I1_UEPS_FID_GRM
#define DSP_FID_APM      I1_DSP_FID_APM
#define DSP_FID_GPHY     I1_DSP_FID_GPHY
#define DSP_FID_DRX      I1_DSP_FID_DRX
#define DSP_FID_IDLE     I1_DSP_FID_IDLE
#else
#define MAPS_USIMM_FID   I0_MAPS_USIMM_FID
#define MAPS_SI_FID      I0_MAPS_SI_FID
#define WUEPS_FID_SLEEP  I0_WUEPS_FID_SLEEP
#define UEPS_FID_RR      I0_UEPS_FID_RR
#define WUEPS_FID_MM     I0_WUEPS_FID_MM
#define WUEPS_FID_CM     I0_WUEPS_FID_CM
#define WUEPS_FID_RABMSM I0_WUEPS_FID_RABMSM
#define WUEPS_FID_TAF    I0_WUEPS_FID_TAF
#define UEPS_FID_SL      I0_UEPS_FID_SL
#define UEPS_FID_PBD     I0_UEPS_FID_PBD
#define UEPS_FID_GRM     I0_UEPS_FID_GRM
#define DSP_FID_APM      I0_DSP_FID_APM
#define DSP_FID_GPHY     I0_DSP_FID_GPHY
#define DSP_FID_DRX      I0_DSP_FID_DRX
#define DSP_FID_IDLE     I0_DSP_FID_IDLE
#endif

/*define product FID table here*/
/* which should be del when only one FID exists */
#undef DEFINE_PRODUCT_FID_TABLE
#if (VOS_WIN32 == VOS_OS_VER)
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#define DEFINE_PRODUCT_FID_TABLE \
    {WUEPS_FID_OM,          "OM",           WuepsOMFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_MAPS_USIMM_FID,     "USIMM_FID",    USIMM_FID_Init,         VOS_START_THIRD,    8192,   0  },\
    {I0_MAPS_SI_FID,        "SI_FID",       WuepsSIFidInit,         VOS_START_THIRD,    0,      0  },\
    {MSP_FID_DIAG_CCPU,     "mspDiag",      MSP_DiagFidInit,        VOS_START_THIRD,    8192,   0  },\
    {MSP_L4_FID,            "mspL4",        MSP_L4FidInit,          VOS_START_THIRD,    16384,  0  },\
    {MSP_HAL_FID,           "mspDRA",       VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {MSP_FTM_FID,           "mspFTM",       MSP_FtmFidInit,         VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_SL,        "I0_SL_FID",    LLC_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_RM,           "RM_FID",       WTTF_MAC_RLC_UlFidInit, VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_RR,        "I0_RR_FID",    GAS_FidPidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_GRM,       "I0_GRM_FID",   GRM_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_HPA,         "HPA_FID",      HPA_FIDInit,            VOS_START_THIRD,    2560,   0  },\
    {I0_WUEPS_FID_MM,       "I0_MM_FID",    NAS_MML_FidInit,        VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_CM,       "I0_CM_FID",    WuepsCmFidInit,         VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_AT,          "NAS_AT",       WuepsATFidInit,         VOS_START_THIRD,    6144,   0  },\
    {ACPU_FID_OM,           "ACPUOM",       OM_AcpuFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_WUEPS_FID_RABMSM,   "I0_RABMSM_FID",WuepsRabmFidInit,       VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_TAF,      "I0_TAF_FID",   WuepsTafFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_OM_CALLBACK, "OMCALLBACK",   OMCallBackFidInit,      VOS_START_THIRD,    5632,   0  },\
    {WUEPS_FID_SPY,         "SPY",          Spy_FID_Init,           VOS_START_THIRD,    6144,   0  },\
    {AGENT_FID_OM,          "AGENT_OM",     OM_AgentFidInit,        VOS_START_THIRD,    0,      0  },\
    {PS_FID_RRC,            "LRRC_FID",     VOS_NULL_PTR,            VOS_START_THIRD,    16384,  0  },\
    {PS_FID_CM,             "LCM_FID",      VOS_NULL_PTR,             VOS_START_THIRD,    16384,  0  },\
    {PS_FID_OM,             "LPSOM_FID",    VOS_NULL_PTR,          VOS_START_THIRD,    4096,   0  },\
    {PS_FID_RM_UL,          "MACRLCUL_FID", VOS_NULL_PTR,     VOS_START_THIRD,    16384,  0  },\
    {PS_FID_RM_DL,          "MACRLCDL_FID", VOS_NULL_PTR,     VOS_START_THIRD,    16384,  0  },\
    {PS_FID_HPA,            "LHPA_FID",     VOS_NULL_PTR,        VOS_START_THIRD,    4096,   0  },\
    {PS_FID_COMM,           "PS_FID_COMM",  VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_IMSA,           "IMSA_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,  0  },\
    {PS_FID_IMSVA,          "IMSVA_FID",    VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_FLOWCTRL_C,   "CCpuFlowCtrl", FC_CCORE_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_RM_DL,        "RM_DL_FID",    WTTF_MAC_RLC_DlFidInit, VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NOSIG,       "OM_NOSIG",     OM_NoSigFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_ITTSTUB,     "ITTSTUB",      WuepsFidITTStubInit,    VOS_START_THIRD,    10240,  0  },\
    {ACPU_FID_ADS_UL,       "ADS_UL",       ADS_UL_FidInit ,        VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_ADS_DL,       "ADS_DL",       ADS_DL_FidInit ,        VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_CSD,          "CSD",          CSD_FidInit,            VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_RNIC,         "RNIC",         RNIC_FidInit,           VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_TAFAGENT,     "TAF_AGENT",    TAF_AGENT_FidInit,      VOS_START_THIRD,    6144,   0  },\
    {UEPS_FID_IMM_RB_FREE,  "IMM_RB_FREE",  IMM_RbMemFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_TTF_MEM_RB_FREE, "MMRB_FREE", TTF_MemRbFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_CDS, "CDS_FID", CDS_FidInit,VOS_START_THIRD,    16384,      0  },\
    {UEPS_FID_NDCLIENT, "NCCLIENT_FID", NDCLIENT_FidInit,VOS_START_THIRD,    8192,      0  },\
    {I0_UEPS_FID_PBD,       "I0_PBD_FID",   PBD_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {HL1_FID_SNDCMD,        "SNDCMD_FID",   hl100_SndCmd_FidInit,  VOS_START_THIRD,    0,      0  },\
    {TPS_FID_MAC,           "TPS_FID_MAC",  process_mac_FidInit,    VOS_START_THIRD,    0,      0  },\
    {TPS_FID_PDC,           "TPS_FID_PDC",  process_pdc_FidInit,    VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NVIM_FLUSH,  "NV_FLUSH",     VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_SLEEP,       "SLEEP",        WuepsSleepFidInit,      VOS_START_THIRD,    0,      0  },\
    {I0_DSP_FID_APM,        "DSP_APM0",     UPHY_APM_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_UPA,           "DSP_UPA",      UPHY_UCOM_UpaFidInit,   VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WPHY,          "DSP_WPHY",     UPHY_UCOM_WphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_GPHY,       "DSP_GPHY0",    UPHY_UCOM_GphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_DRX,        "DSP_DRX0",     UPHY_DRX_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_IDLE,       "DSP_IDLE0",    UPHY_IDLE_FidInit,      VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WMEAS,         "DSP_WMEAS",    UPHY_UCOM_WmeasFidInit, VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_IPS_CCORE,    "IPS_CCORE",    IPS_MNTN_CCORE_FidInit, VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CBPCA,       "CBPCA_FID",    CBPCA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CSIMA,       "CSIMA_FID",    CSIMA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CMMCA,       "CMMCA",        CMMCA_FidInit,          VOS_START_THIRD,    4096,   0  },
#else   /*(FEATURE_OFF == FEATURE_UE_MODE_TDS)*/
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#define DEFINE_PRODUCT_FID_TABLE \
    {WUEPS_FID_OM,          "OM",           WuepsOMFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_MAPS_USIMM_FID,     "USIMM_FID",    USIMM_FID_Init,         VOS_START_THIRD,    8192,   0  },\
    {I0_MAPS_SI_FID,        "SI_FID",       WuepsSIFidInit,         VOS_START_THIRD,    0,      0  },\
    {MSP_FID_DIAG_CCPU,     "mspDiag",      MSP_DiagFidInit,        VOS_START_THIRD,    8192,   0  },\
    {MSP_L4_FID,            "mspL4",        MSP_L4FidInit,          VOS_START_THIRD,    16384,  0  },\
    {MSP_HAL_FID,           "mspDRA",       VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {MSP_FTM_FID,           "mspFTM",       MSP_FtmFidInit,         VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_SL,        "I0_SL_FID",    LLC_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_RM,           "RM_FID",       WTTF_MAC_RLC_UlFidInit, VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_RR,        "I0_RR_FID",    GAS_FidPidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_GRM,       "I0_GRM_FID",   GRM_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_HPA,         "HPA_FID",      HPA_FIDInit,            VOS_START_THIRD,    2560,   0  },\
    {I0_WUEPS_FID_MM,       "I0_MM_FID",    NAS_MML_FidInit,        VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_CM,       "I0_CM_FID",    WuepsCmFidInit,         VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_AT,          "NAS_AT",       WuepsATFidInit,         VOS_START_THIRD,    6144,   0  },\
    {ACPU_FID_OM,           "ACPUOM",       OM_AcpuFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_WUEPS_FID_RABMSM,   "I0_RABMSM_FID",WuepsRabmFidInit,       VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_TAF,      "I0_TAF_FID",   WuepsTafFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_OM_CALLBACK, "OMCALLBACK",   OMCallBackFidInit,      VOS_START_THIRD,    5632,   0  },\
    {WUEPS_FID_SPY,         "SPY",          Spy_FID_Init,           VOS_START_THIRD,    6144,   0  },\
    {AGENT_FID_OM,          "AGENT_OM",     OM_AgentFidInit,        VOS_START_THIRD,    0,      0  },\
    {PS_FID_RRC,            "LRRC_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {PS_FID_CM,             "LCM_FID",      VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {PS_FID_OM,             "LPSOM_FID",    VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_RM_UL,          "MACRLCUL_FID", VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {PS_FID_RM_DL,          "MACRLCDL_FID", VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {PS_FID_HPA,            "LHPA_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_COMM,           "PS_FID_COMM",  VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_IMSA,           "IMSA_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,  0  },\
    {PS_FID_IMSVA,          "IMSVA_FID",    VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_FLOWCTRL_C,   "CCpuFlowCtrl", FC_CCORE_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_RM_DL,        "RM_DL_FID",    WTTF_MAC_RLC_DlFidInit, VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NOSIG,       "OM_NOSIG",     OM_NoSigFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_ITTSTUB,     "ITTSTUB",      WuepsFidITTStubInit,    VOS_START_THIRD,    10240,  0  },\
    {ACPU_FID_ADS_UL,       "ADS_UL",       ADS_UL_FidInit ,        VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_ADS_DL,       "ADS_DL",       ADS_DL_FidInit ,        VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_CSD,          "CSD",          CSD_FidInit,            VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_RNIC,         "RNIC",         RNIC_FidInit,           VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_TAFAGENT,     "TAF_AGENT",    TAF_AGENT_FidInit,      VOS_START_THIRD,    6144,   0  },\
    {UEPS_FID_IMM_RB_FREE,  "IMM_RB_FREE",  IMM_RbMemFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {MSP_APP_DS_FID,        "mspDS",        VOS_NULL_PTR,           VOS_START_THIRD,    4096,  0  },\
    {UEPS_FID_TTF_MEM_RB_FREE, "MMRB_FREE", TTF_MemRbFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_CDS,          "CDS_FID",      CDS_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_NDCLIENT,     "NCCLIENT_FID", NDCLIENT_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_PBD,       "I0_PBD_FID",   PBD_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_NVIM_FLUSH,  "NV_FLUSH",     VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_SLEEP,       "SLEEP",        WuepsSleepFidInit,      VOS_START_THIRD,    4096,   0  },\
    {I0_DSP_FID_APM,        "DSP_APM0",     UPHY_APM_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_UPA,           "DSP_UPA",      UPHY_UCOM_UpaFidInit,   VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WPHY,          "DSP_WPHY",     UPHY_UCOM_WphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_GPHY,       "DSP_GPHY0",    UPHY_UCOM_GphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_DRX,        "DSP_DRX0",     UPHY_DRX_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_IDLE,       "DSP_IDLE0",    UPHY_IDLE_FidInit,      VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WMEAS,         "DSP_WMEAS",    UPHY_UCOM_WmeasFidInit, VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_IPS_CCORE,    "IPS_CCORE",    IPS_MNTN_CCORE_FidInit, VOS_START_THIRD,    8192,   0  },\
    {I1_MAPS_USIMM_FID,     "USIMM_FID1",   VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {I1_MAPS_SI_FID,        "SI_FID1",      VOS_NULL_PTR,           VOS_START_THIRD,    0,      0  },\
    {I1_WUEPS_FID_SLEEP,    "I1_SLEEP",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {I1_UEPS_FID_RR,        "RR_FID1",      VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_MM,       "MM_FID1",      VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_CM,       "CM_FID1",      VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_RABMSM,   "RABMSM_FID1",  VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_TAF,      "TAF_FID1",     VOS_NULL_PTR,           VOS_START_THIRD,    0,      0  },\
    {I1_UEPS_FID_SL,        "SL_FID1",      VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {I1_UEPS_FID_PBD,       "PBD_FID1",     VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {I1_UEPS_FID_GRM,       "GRM_FID1",     VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {I1_DSP_FID_APM,        "DSP_APM1",     VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_GPHY,       "DSP_GPHY1",    VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_DRX,        "DSP_DRX1",     VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_IDLE,       "DSP_IDLE1",    VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_MTC,          "MTC",          VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_RRM,          "RRM_FID",      VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CBPCA,       "CBPCA_FID",    CBPCA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CSIMA,       "CSIMA_FID",    CSIMA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CMMCA,       "CMMCA",        CMMCA_FidInit,          VOS_START_THIRD,    4096,   0  },
#else
#define DEFINE_PRODUCT_FID_TABLE \
    {WUEPS_FID_OM,          "OM",           WuepsOMFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_MAPS_USIMM_FID,     "USIMM_FID",    USIMM_FID_Init,         VOS_START_THIRD,    8192,   0  },\
    {I0_MAPS_SI_FID,        "SI_FID",       WuepsSIFidInit,         VOS_START_THIRD,    0,      0  },\
    {MSP_FID_DIAG_CCPU,     "mspDiag",      MSP_DiagFidInit,        VOS_START_THIRD,    8192,   0  },\
    {MSP_L4_FID,            "mspL4",        MSP_L4FidInit,          VOS_START_THIRD,    16384,  0  },\
    {MSP_HAL_FID,           "mspDRA",       VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {MSP_FTM_FID,           "mspFTM",       MSP_FtmFidInit,         VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_SL,        "I0_SL_FID",    LLC_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_RM,           "RM_FID",       WTTF_MAC_RLC_UlFidInit, VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_RR,        "I0_RR_FID",    GAS_FidPidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_GRM,       "I0_GRM_FID",   GRM_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_HPA,         "HPA_FID",      HPA_FIDInit,            VOS_START_THIRD,    2560,   0  },\
    {I0_WUEPS_FID_MM,       "I0_MM_FID",    NAS_MML_FidInit,        VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_CM,       "I0_CM_FID",    WuepsCmFidInit,         VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_AT,          "NAS_AT",       WuepsATFidInit,         VOS_START_THIRD,    6144,   0  },\
    {ACPU_FID_OM,           "ACPUOM",       OM_AcpuFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_WUEPS_FID_RABMSM,   "I0_RABMSM_FID",WuepsRabmFidInit,       VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_TAF,      "I0_TAF_FID",   WuepsTafFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_OM_CALLBACK, "OMCALLBACK",   OMCallBackFidInit,      VOS_START_THIRD,    5632,   0  },\
    {WUEPS_FID_SPY,         "SPY",          Spy_FID_Init,           VOS_START_THIRD,    6144,   0  },\
    {AGENT_FID_OM,          "AGENT_OM",     OM_AgentFidInit,        VOS_START_THIRD,    0,      0  },\
    {PS_FID_RRC,            "LRRC_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {PS_FID_CM,             "LCM_FID",      VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {PS_FID_OM,             "LPSOM_FID",    VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_RM_UL,          "MACRLCUL_FID", VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {PS_FID_RM_DL,          "MACRLCDL_FID", VOS_NULL_PTR,           VOS_START_THIRD,    16384,  0  },\
    {PS_FID_HPA,            "LHPA_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_COMM,           "PS_FID_COMM",  VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_IMSA,           "IMSA_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,  0  },\
    {PS_FID_IMSVA,          "IMSVA_FID",    VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_FLOWCTRL_C,   "CCpuFlowCtrl", FC_CCORE_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_RM_DL,        "RM_DL_FID",    WTTF_MAC_RLC_DlFidInit, VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NOSIG,       "OM_NOSIG",     OM_NoSigFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_ITTSTUB,     "ITTSTUB",      WuepsFidITTStubInit,    VOS_START_THIRD,    10240,  0  },\
    {ACPU_FID_ADS_UL,       "ADS_UL",       ADS_UL_FidInit ,        VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_ADS_DL,       "ADS_DL",       ADS_DL_FidInit ,        VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_CSD,          "CSD",          CSD_FidInit,            VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_RNIC,         "RNIC",         RNIC_FidInit,           VOS_START_THIRD,    0,      0  },\
    {ACPU_FID_TAFAGENT,     "TAF_AGENT",    TAF_AGENT_FidInit,      VOS_START_THIRD,    6144,   0  },\
    {UEPS_FID_IMM_RB_FREE,  "IMM_RB_FREE",  IMM_RbMemFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {MSP_APP_DS_FID,        "mspDS",        VOS_NULL_PTR,           VOS_START_THIRD,    4096,  0  },\
    {UEPS_FID_TTF_MEM_RB_FREE, "MMRB_FREE", TTF_MemRbFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_CDS,          "CDS_FID",      CDS_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_NDCLIENT,     "NCCLIENT_FID", NDCLIENT_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_PBD,       "I0_PBD_FID",   PBD_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_NVIM_FLUSH,  "NV_FLUSH",     VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_SLEEP,       "SLEEP",        WuepsSleepFidInit,      VOS_START_THIRD,    4096,   0  },\
    {I0_DSP_FID_APM,        "DSP_APM0",     UPHY_APM_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_UPA,           "DSP_UPA",      UPHY_UCOM_UpaFidInit,   VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WPHY,          "DSP_WPHY",     UPHY_UCOM_WphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_GPHY,       "DSP_GPHY0",    UPHY_UCOM_GphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_DRX,        "DSP_DRX0",     UPHY_DRX_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_IDLE,       "DSP_IDLE0",    UPHY_IDLE_FidInit,      VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WMEAS,         "DSP_WMEAS",    UPHY_UCOM_WmeasFidInit, VOS_START_THIRD,    8192,   0  },\
	{PS_FID_IMSA,           "IMSA_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,  0  },\
    {UEPS_FID_IPS_CCORE,    "IPS_CCORE",    IPS_MNTN_CCORE_FidInit, VOS_START_THIRD,    8192,   0  },\
    {PS_FID_IMSVA,          "IMSVA_FID",    VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {WUEPS_FID_CMMCA,       "CMMCA",        CMMCA_FidInit,          VOS_START_THIRD,    4096,   0  },
#endif
#endif /*(FEATURE_ON == FEATURE_UE_MODE_TDS)*/

#elif (OSA_CPU_CCPU == VOS_OSA_CPU)
#if (RAT_MODE == RAT_GU)
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#define DEFINE_PRODUCT_FID_TABLE \
    {WUEPS_FID_OM,          "OM",           WuepsOMFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_MAPS_USIMM_FID,     "USIMM_FID",    USIMM_FID_Init,         VOS_START_THIRD,    8192,   0  },\
    {I0_MAPS_SI_FID,        "SI_FID",       WuepsSIFidInit,         VOS_START_THIRD,    0,      0  },\
    {MSP_FID_DIAG_CCPU,     "mspDiag",      VOS_NULL_PTR,           VOS_START_THIRD,    4096,       0  },\
    {MSP_L4_FID,            "mspL4",        VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {MSP_HAL_FID,           "mspDRA",       VOS_NULL_PTR,           VOS_START_THIRD,    4096,       0  },\
    {MSP_FTM_FID,           "mspFTM",       VOS_NULL_PTR,         VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_SL,        "I0_SL_FID",    LLC_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_RM,           "RM_FID",       WTTF_MAC_RLC_UlFidInit, VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_RR,        "I0_RR_FID",    GAS_FidPidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_GRM,       "I0_GRM_FID",   GRM_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_HPA,         "HPA_FID",      HPA_FIDInit,            VOS_START_THIRD,    2560,   0  },\
    {I0_WUEPS_FID_MM,       "I0_MM_FID",    NAS_MML_FidInit,        VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_CM,       "I0_CM_FID",    WuepsCmFidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_RABMSM,   "I0_RABMSM_FID",WuepsRabmFidInit,       VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_TAF,      "I0_TAF_FID",   WuepsTafFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_OM_CALLBACK, "OMCALLBACK",   OMCallBackFidInit,      VOS_START_THIRD,    5632,   0  },\
    {WUEPS_FID_SPY,         "SPY",          Spy_FID_Init,           VOS_START_THIRD,    6144,   0  },\
    {AGENT_FID_OM,          "AGENT_OM",     OM_AgentFidInit,        VOS_START_THIRD,    0,      0  },\
    {PS_FID_RRC,            "LRRC_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_CM,             "LCM_FID",      VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_OM,             "LPSOM_FID",    VOS_NULL_PTR,           VOS_START_THIRD,    4096,       0  },\
    {PS_FID_RM_UL,          "MACRLCUL_FID", VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_RM_DL,          "MACRLCDL_FID", VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_HPA,            "LHPA_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,       0  },\
    {PS_FID_COMM,           "PS_FID_COMM",  VOS_NULL_PTR,           VOS_START_THIRD,    4096,       0  },\
    {PS_FID_IMSA,           "IMSA_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,  0  },\
    {PS_FID_IMSVA,          "IMSVA_FID",    VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_FLOWCTRL_C,   "CCpuFlowCtrl", FC_CCORE_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_RM_DL,        "RM_DL_FID",    WTTF_MAC_RLC_DlFidInit, VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NOSIG,       "OM_NOSIG",     OM_NoSigFidInit,        VOS_START_THIRD,    0,      0  },\
    {UEPS_FID_TTF_MEM_RB_FREE, "MMRB_FREE", TTF_MemRbFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_CDS,          "CDS_FID",      CDS_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_NDCLIENT,     "NCCLIENT_FID", NDCLIENT_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_PBD,       "I0_PBD_FID",   PBD_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_NVIM_FLUSH,  "NV_FLUSH",     VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_SLEEP,       "SLEEP",        WuepsSleepFidInit,      VOS_START_THIRD,    4096,   0  },\
    {I0_DSP_FID_APM,        "DSP_APM0",     UPHY_APM_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_UPA,           "DSP_UPA",      UPHY_UCOM_UpaFidInit,   VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WPHY,          "DSP_WPHY",     UPHY_UCOM_WphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_GPHY,       "DSP_GPHY0",    UPHY_UCOM_GphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_DRX,        "DSP_DRX0",     UPHY_DRX_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_IDLE,       "DSP_IDLE0",    UPHY_IDLE_FidInit,      VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WMEAS,         "DSP_WMEAS",    UPHY_UCOM_WmeasFidInit, VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_IPS_CCORE,    "IPS_CCORE",    IPS_MNTN_CCORE_FidInit, VOS_START_THIRD,    8192,   0  },\
    {I1_MAPS_USIMM_FID,     "USIMM_FID1",   I1_USIMM_FID_Init,      VOS_START_THIRD,    8192,   0  },\
    {I1_MAPS_SI_FID,        "SI_FID1",      I1_WuepsSIFidInit,      VOS_START_THIRD,    0,      0  },\
    {I1_WUEPS_FID_SLEEP,    "I1_SLEEP",     I1_WuepsSleepFidInit,   VOS_START_THIRD,    4096,   0  },\
    {I1_UEPS_FID_RR,        "RR_FID1",      I1_GAS_FidPidInit,      VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_MM,       "MM_FID1",      I1_NAS_MML_FidInit,     VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_CM,       "CM_FID1",      I1_WuepsCmFidInit,      VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_RABMSM,   "RABMSM_FID1",  I1_WuepsRabmFidInit,    VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_TAF,      "TAF_FID1",     I1_WuepsTafFidInit,     VOS_START_THIRD,    0,      0  },\
    {I1_UEPS_FID_SL,        "SL_FID1",      I1_LLC_FID_Init,        VOS_START_THIRD,    16384,  0  },\
    {I1_UEPS_FID_PBD,       "PBD_FID1",     I1_PBD_FID_Init,        VOS_START_THIRD,    16384,  0  },\
    {I1_UEPS_FID_GRM,       "GRM_FID1",     I1_GRM_FID_Init,        VOS_START_THIRD,    16384,  0  },\
    {I1_DSP_FID_APM,        "DSP_APM1",     I1_UPHY_APM_FidInit,    VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_GPHY,       "DSP_GPHY1",    I1_UPHY_UCOM_GphyFidInit,    VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_DRX,        "DSP_DRX1",     I1_UPHY_DRX_FidInit,    VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_IDLE,       "DSP_IDLE1",    I1_UPHY_IDLE_FidInit,   VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_MTC,          "MTC",          MTC_FidInit,            VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_RRM,          "RRM_FID",      RRM_FidInit,            VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CBPCA,       "CBPCA_FID",    CBPCA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CSIMA,       "CSIMA_FID",    CSIMA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CMMCA,       "CMMCA",        CMMCA_FidInit,          VOS_START_THIRD,    4096,   0  },
#else   /*( FEATURE_MULTI_MODEM == FEATURE_OFF )*/
#define DEFINE_PRODUCT_FID_TABLE \
    {WUEPS_FID_OM,          "OM",           WuepsOMFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_MAPS_USIMM_FID,     "USIMM_FID",    USIMM_FID_Init,         VOS_START_THIRD,    8192,   0  },\
    {I0_MAPS_SI_FID,        "SI_FID",       WuepsSIFidInit,         VOS_START_THIRD,    0,      0  },\
    {MSP_FID_DIAG_CCPU,     "mspDiag",      VOS_NULL_PTR,           VOS_START_THIRD,    4096,       0  },\
    {MSP_L4_FID,            "mspL4",        VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {MSP_HAL_FID,           "mspDRA",       VOS_NULL_PTR,           VOS_START_THIRD,    4096,       0  },\
    {MSP_FTM_FID,           "mspFTM",       VOS_NULL_PTR,         VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_SL,        "I0_SL_FID",    LLC_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_RM,           "RM_FID",       WTTF_MAC_RLC_UlFidInit, VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_RR,        "I0_RR_FID",    GAS_FidPidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_GRM,       "I0_GRM_FID",   GRM_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_HPA,         "HPA_FID",      HPA_FIDInit,            VOS_START_THIRD,    2560,   0  },\
    {I0_WUEPS_FID_MM,       "I0_MM_FID",    NAS_MML_FidInit,        VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_CM,       "I0_CM_FID",    WuepsCmFidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_RABMSM,   "I0_RABMSM_FID",WuepsRabmFidInit,       VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_TAF,      "I0_TAF_FID",   WuepsTafFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_OM_CALLBACK, "OMCALLBACK",   OMCallBackFidInit,      VOS_START_THIRD,    5632,   0  },\
    {WUEPS_FID_SPY,         "SPY",          Spy_FID_Init,           VOS_START_THIRD,    6144,   0  },\
    {AGENT_FID_OM,          "AGENT_OM",     OM_AgentFidInit,        VOS_START_THIRD,    0,      0  },\
    {PS_FID_RRC,            "LRRC_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_CM,             "LCM_FID",      VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_OM,             "LPSOM_FID",    VOS_NULL_PTR,           VOS_START_THIRD,    4096,       0  },\
    {PS_FID_RM_UL,          "MACRLCUL_FID", VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_RM_DL,          "MACRLCDL_FID", VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_HPA,            "LHPA_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,       0  },\
    {PS_FID_COMM,           "PS_FID_COMM",  VOS_NULL_PTR,           VOS_START_THIRD,    4096,       0  },\
    {PS_FID_IMSA,           "IMSA_FID",     VOS_NULL_PTR,           VOS_START_THIRD,    4096,  0  },\
    {PS_FID_IMSVA,          "IMSVA_FID",    VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_FLOWCTRL_C,   "CCpuFlowCtrl", FC_CCORE_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_RM_DL,        "RM_DL_FID",    WTTF_MAC_RLC_DlFidInit, VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NOSIG,       "OM_NOSIG",     OM_NoSigFidInit,        VOS_START_THIRD,    0,      0  },\
    {UEPS_FID_TTF_MEM_RB_FREE, "MMRB_FREE", TTF_MemRbFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_CDS,          "CDS_FID",      CDS_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_NDCLIENT,     "NCCLIENT_FID", NDCLIENT_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_PBD,       "I0_PBD_FID",   PBD_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_NVIM_FLUSH,  "NV_FLUSH",     VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_SLEEP,       "SLEEP",        WuepsSleepFidInit,      VOS_START_THIRD,    4096,   0  },\
    {I0_DSP_FID_APM,        "DSP_APM0",     UPHY_APM_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_UPA,           "DSP_UPA",      UPHY_UCOM_UpaFidInit,   VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WPHY,          "DSP_WPHY",     UPHY_UCOM_WphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_GPHY,       "DSP_GPHY0",    UPHY_UCOM_GphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_DRX,        "DSP_DRX0",     UPHY_DRX_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_IDLE,       "DSP_IDLE0",    UPHY_IDLE_FidInit,      VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WMEAS,         "DSP_WMEAS",    UPHY_UCOM_WmeasFidInit, VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_IPS_CCORE,    "IPS_CCORE",    IPS_MNTN_CCORE_FidInit, VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CBPCA,       "CBPCA_FID",    CBPCA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CSIMA,       "CSIMA_FID",    CSIMA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CMMCA,       "CMMCA",        CMMCA_FidInit,          VOS_START_THIRD,    4096,   0  },
#endif  /*( FEATURE_MULTI_MODEM == FEATURE_ON )*/
#elif (RAT_GU != RAT_MODE)
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#define DEFINE_PRODUCT_FID_TABLE \
    {WUEPS_FID_OM,          "OM",           WuepsOMFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_MAPS_USIMM_FID,     "USIMM_FID",    USIMM_FID_Init,         VOS_START_THIRD,    8192,   0  },\
    {I0_MAPS_SI_FID,        "SI_FID",       WuepsSIFidInit,         VOS_START_THIRD,    0,      0  },\
    {MSP_FID_DIAG_CCPU,     "mspDiag",      MSP_DiagFidInit,           VOS_START_THIRD,    8192,   0  },\
    {MSP_L4_FID,            "mspL4",        MSP_L4FidInit,          VOS_START_THIRD,    16384,  0  },\
    {MSP_HAL_FID,           "mspDRA",       VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {MSP_FTM_FID,           "mspFTM",       MSP_FtmFidInit,         VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_SL,        "I0_SL_FID",    LLC_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_RM,           "RM_FID",       WTTF_MAC_RLC_UlFidInit, VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_RR,        "I0_RR_FID",    GAS_FidPidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_GRM,       "I0_GRM_FID",   GRM_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_HPA,         "HPA_FID",      HPA_FIDInit,            VOS_START_THIRD,    2560,   0  },\
    {I0_WUEPS_FID_MM,       "I0_MM_FID",    NAS_MML_FidInit,        VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_CM,       "I0_CM_FID",    WuepsCmFidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_RABMSM,   "I0_RABMSM_FID",WuepsRabmFidInit,       VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_TAF,      "I0_TAF_FID",   WuepsTafFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_OM_CALLBACK, "OMCALLBACK",   OMCallBackFidInit,      VOS_START_THIRD,    5632,   0  },\
    {WUEPS_FID_SPY,         "SPY",          Spy_FID_Init,           VOS_START_THIRD,    6144,   0  },\
    {AGENT_FID_OM,          "AGENT_OM",     OM_AgentFidInit,        VOS_START_THIRD,    0,      0  },\
    {PS_FID_RRC,            "LRRC_FID",     RRC_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {PS_FID_CM,             "LCM_FID",      CM_FidInit,             VOS_START_THIRD,    16384,  0  },\
    {PS_FID_OM,             "LPSOM_FID",    PS_OM_FidInit,          VOS_START_THIRD,    4096,   0  },\
    {PS_FID_RM_UL,          "MACRLCUL_FID", LMAC_RLC_UlFidInit,     VOS_START_THIRD,    16384,  0  },\
    {PS_FID_RM_DL,          "MACRLCDL_FID", LMAC_RLC_DlFidInit,     VOS_START_THIRD,    16384,  0  },\
    {PS_FID_HPA,            "LHPA_FID",     LHPA_FidPidInit,        VOS_START_THIRD,    4096,   0  },\
    {PS_FID_COMM,           "PS_FID_COMM",  VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_IMSA,           "IMSA_FID",     IMSA_FidInit,           VOS_START_THIRD,    16384,  0  },\
    {PS_FID_IMSVA,          "IMSVA_FID",    IMSVA_FidInit,          VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_FLOWCTRL_C,   "CCpuFlowCtrl", FC_CCORE_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_RM_DL,        "RM_DL_FID",    WTTF_MAC_RLC_DlFidInit, VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NOSIG,       "OM_NOSIG",     OM_NoSigFidInit,        VOS_START_THIRD,    0,      0  },\
    {UEPS_FID_TTF_MEM_RB_FREE, "MMRB_FREE", TTF_MemRbFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_CDS,          "CDS_FID",      CDS_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_NDCLIENT,     "NCCLIENT_FID", NDCLIENT_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_PBD,       "I0_PBD_FID",   PBD_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {HL1_FID_SNDCMD,        "SNDCMD_FID",   hl100_SndCmd_FidInit,   VOS_START_THIRD,    0,      0  },\
    {TPS_FID_MAC,           "TPS_FID_MAC",  process_mac_FidInit,    VOS_START_THIRD,    0,      0  },\
    {TPS_FID_PDC,           "TPS_FID_PDC",  process_pdc_FidInit,    VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NVIM_FLUSH,  "NV_FLUSH",     VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_SLEEP,       "SLEEP",        WuepsSleepFidInit,      VOS_START_THIRD,    4096,   0  },\
    {I0_DSP_FID_APM,        "DSP_APM0",     UPHY_APM_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_UPA,           "DSP_UPA",      UPHY_UCOM_UpaFidInit,   VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WPHY,          "DSP_WPHY",     UPHY_UCOM_WphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_GPHY,       "DSP_GPHY0",    UPHY_UCOM_GphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_DRX,        "DSP_DRX0",     UPHY_DRX_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_IDLE,       "DSP_IDLE0",    UPHY_IDLE_FidInit,      VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WMEAS,         "DSP_WMEAS",    UPHY_UCOM_WmeasFidInit, VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_IPS_CCORE,    "IPS_CCORE",    IPS_MNTN_CCORE_FidInit, VOS_START_THIRD,    8192,   0  },\
    {I1_MAPS_USIMM_FID,     "USIMM_FID1",   I1_USIMM_FID_Init,      VOS_START_THIRD,    8192,   0  },\
    {I1_MAPS_SI_FID,        "SI_FID1",      I1_WuepsSIFidInit,      VOS_START_THIRD,    0,      0  },\
    {I1_WUEPS_FID_SLEEP,    "I1_SLEEP",     I1_WuepsSleepFidInit,   VOS_START_THIRD,    4096,   0  },\
    {I1_UEPS_FID_RR,        "RR_FID1",      I1_GAS_FidPidInit,      VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_MM,       "MM_FID1",      I1_NAS_MML_FidInit,     VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_CM,       "CM_FID1",      I1_WuepsCmFidInit,      VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_RABMSM,   "RABMSM_FID1",  I1_WuepsRabmFidInit,    VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_TAF,      "TAF_FID1",     I1_WuepsTafFidInit,     VOS_START_THIRD,    0,      0  },\
    {I1_UEPS_FID_SL,        "SL_FID1",      I1_LLC_FID_Init,        VOS_START_THIRD,    16384,  0  },\
    {I1_UEPS_FID_PBD,       "PBD_FID1",     I1_PBD_FID_Init,        VOS_START_THIRD,    16384,  0  },\
    {I1_UEPS_FID_GRM,       "GRM_FID1",     I1_GRM_FID_Init,        VOS_START_THIRD,    16384,  0  },\
    {I1_DSP_FID_APM,        "DSP_APM1",     I1_UPHY_APM_FidInit,    VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_GPHY,       "DSP_GPHY1",    I1_UPHY_UCOM_GphyFidInit, VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_DRX,        "DSP_DRX1",     I1_UPHY_DRX_FidInit,    VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_IDLE,       "DSP_IDLE1",    I1_UPHY_IDLE_FidInit,   VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_MTC,          "MTC",          MTC_FidInit,            VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_RRM,          "RRM_FID",      RRM_FidInit,            VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CBPCA,       "CBPCA_FID",    CBPCA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CSIMA,       "CSIMA_FID",    CSIMA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CMMCA,       "CMMCA",        CMMCA_FidInit,          VOS_START_THIRD,    4096,   0  },
#else   /*( FEATURE_MULTI_MODEM == FEATURE_OFF )*/
#define DEFINE_PRODUCT_FID_TABLE \
    {WUEPS_FID_OM,          "OM",           WuepsOMFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_MAPS_USIMM_FID,     "USIMM_FID",    USIMM_FID_Init,         VOS_START_THIRD,    8192,   0  },\
    {I0_MAPS_SI_FID,        "SI_FID",       WuepsSIFidInit,         VOS_START_THIRD,    0,      0  },\
    {MSP_FID_DIAG_CCPU,     "mspDiag",      MSP_DiagFidInit,        VOS_START_THIRD,    8192,   0  },\
    {MSP_L4_FID,            "mspL4",        MSP_L4FidInit,          VOS_START_THIRD,    16384,  0  },\
    {MSP_HAL_FID,           "mspDRA",       VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {MSP_FTM_FID,           "mspFTM",       MSP_FtmFidInit,         VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_SL,        "I0_SL_FID",    LLC_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_RM,           "RM_FID",       WTTF_MAC_RLC_UlFidInit, VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_RR,        "I0_RR_FID",    GAS_FidPidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_GRM,       "I0_GRM_FID",   GRM_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_HPA,         "HPA_FID",      HPA_FIDInit,            VOS_START_THIRD,    2560,   0  },\
    {I0_WUEPS_FID_MM,       "I0_MM_FID",    NAS_MML_FidInit,        VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_CM,       "I0_CM_FID",    WuepsCmFidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_RABMSM,   "I0_RABMSM_FID",WuepsRabmFidInit,       VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_TAF,      "I0_TAF_FID",   WuepsTafFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_OM_CALLBACK, "OMCALLBACK",   OMCallBackFidInit,      VOS_START_THIRD,    5632,   0  },\
    {WUEPS_FID_SPY,         "SPY",          Spy_FID_Init,           VOS_START_THIRD,    6144,   0  },\
    {AGENT_FID_OM,          "AGENT_OM",     OM_AgentFidInit,        VOS_START_THIRD,    0,      0  },\
    {PS_FID_RRC,            "LRRC_FID",     RRC_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {PS_FID_CM,             "LCM_FID",      CM_FidInit,             VOS_START_THIRD,    16384,  0  },\
    {PS_FID_OM,             "LPSOM_FID",    PS_OM_FidInit,          VOS_START_THIRD,    4096,   0  },\
    {PS_FID_RM_UL,          "MACRLCUL_FID", LMAC_RLC_UlFidInit,     VOS_START_THIRD,    16384,  0  },\
    {PS_FID_RM_DL,          "MACRLCDL_FID", LMAC_RLC_DlFidInit,     VOS_START_THIRD,    16384,  0  },\
    {PS_FID_HPA,            "LHPA_FID",     LHPA_FidPidInit,        VOS_START_THIRD,    4096,   0  },\
    {PS_FID_COMM,           "PS_FID_COMM",  VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_IMSA,           "IMSA_FID",     IMSA_FidInit,           VOS_START_THIRD,    16384,  0  },\
    {PS_FID_IMSVA,          "IMSVA_FID",    IMSVA_FidInit,          VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_FLOWCTRL_C,   "CCpuFlowCtrl", FC_CCORE_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_RM_DL,        "RM_DL_FID",    WTTF_MAC_RLC_DlFidInit, VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NOSIG,       "OM_NOSIG",     OM_NoSigFidInit,        VOS_START_THIRD,    0,      0  },\
    {UEPS_FID_TTF_MEM_RB_FREE, "MMRB_FREE", TTF_MemRbFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_CDS,          "CDS_FID",      CDS_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_NDCLIENT,     "NCCLIENT_FID", NDCLIENT_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_PBD,       "I0_PBD_FID",   PBD_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {HL1_FID_SNDCMD,        "SNDCMD_FID",   hl100_SndCmd_FidInit,   VOS_START_THIRD,    0,      0  },\
    {TPS_FID_MAC,           "TPS_FID_MAC",  process_mac_FidInit,    VOS_START_THIRD,    0,      0  },\
    {TPS_FID_PDC,           "TPS_FID_PDC",  process_pdc_FidInit,    VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NVIM_FLUSH,  "NV_FLUSH",     VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_SLEEP,       "SLEEP",        WuepsSleepFidInit,      VOS_START_THIRD,    4096,   0  },\
    {I0_DSP_FID_APM,        "DSP_APM0",     UPHY_APM_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_UPA,           "DSP_UPA",      UPHY_UCOM_UpaFidInit,   VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WPHY,          "DSP_WPHY",     UPHY_UCOM_WphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_GPHY,       "DSP_GPHY0",    UPHY_UCOM_GphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_DRX,        "DSP_DRX0",     UPHY_DRX_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_IDLE,       "DSP_IDLE0",    UPHY_IDLE_FidInit,      VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WMEAS,         "DSP_WMEAS",    UPHY_UCOM_WmeasFidInit, VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_IPS_CCORE,    "IPS_CCORE",    IPS_MNTN_CCORE_FidInit, VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CBPCA,       "CBPCA_FID",    CBPCA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CSIMA,       "CSIMA_FID",    CSIMA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CMMCA,       "CMMCA",        CMMCA_FidInit,          VOS_START_THIRD,    4096,   0  },
#endif  /*( FEATURE_MULTI_MODEM == FEATURE_ON )*/
#else
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
#define DEFINE_PRODUCT_FID_TABLE \
    {WUEPS_FID_OM,          "OM",           WuepsOMFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_MAPS_USIMM_FID,     "USIMM_FID",    USIMM_FID_Init,         VOS_START_THIRD,    8192,   0  },\
    {I0_MAPS_SI_FID,        "SI_FID",       WuepsSIFidInit,         VOS_START_THIRD,    0,      0  },\
    {MSP_FID_DIAG_CCPU,     "mspDiag",      MSP_DiagFidInit,        VOS_START_THIRD,    8192,   0  },\
    {MSP_L4_FID,            "mspL4",        MSP_L4FidInit,          VOS_START_THIRD,    16384,  0  },\
    {MSP_HAL_FID,           "mspDRA",       VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {MSP_FTM_FID,           "mspFTM",       MSP_FtmFidInit,         VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_SL,        "I0_SL_FID",    LLC_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_RM,           "RM_FID",       WTTF_MAC_RLC_UlFidInit, VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_RR,        "I0_RR_FID",    GAS_FidPidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_GRM,       "I0_GRM_FID",   GRM_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_HPA,         "HPA_FID",      HPA_FIDInit,            VOS_START_THIRD,    2560,   0  },\
    {I0_WUEPS_FID_MM,       "I0_MM_FID",    NAS_MML_FidInit,        VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_CM,       "I0_CM_FID",    WuepsCmFidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_RABMSM,   "I0_RABMSM_FID",WuepsRabmFidInit,       VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_TAF,      "I0_TAF_FID",   WuepsTafFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_OM_CALLBACK, "OMCALLBACK",   OMCallBackFidInit,      VOS_START_THIRD,    5632,   0  },\
    {WUEPS_FID_SPY,         "SPY",          Spy_FID_Init,           VOS_START_THIRD,    6144,   0  },\
    {AGENT_FID_OM,          "AGENT_OM",     OM_AgentFidInit,        VOS_START_THIRD,    0,      0  },\
    {PS_FID_RRC,            "LRRC_FID",     RRC_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {PS_FID_CM,             "LCM_FID",      CM_FidInit,             VOS_START_THIRD,    16384,  0  },\
    {PS_FID_OM,             "LPSOM_FID",    PS_OM_FidInit,          VOS_START_THIRD,    4096,   0  },\
    {PS_FID_RM_UL,          "MACRLCUL_FID", LMAC_RLC_UlFidInit,     VOS_START_THIRD,    16384,  0  },\
    {PS_FID_RM_DL,          "MACRLCDL_FID", LMAC_RLC_DlFidInit,     VOS_START_THIRD,    16384,  0  },\
    {PS_FID_HPA,            "LHPA_FID",     LHPA_FidPidInit,        VOS_START_THIRD,    4096,   0  },\
    {PS_FID_COMM,           "PS_FID_COMM",  VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_IMSA,           "IMSA_FID",     IMSA_FidInit,           VOS_START_THIRD,    16384,  0  },\
    {PS_FID_IMSVA,          "IMSVA_FID",    IMSVA_FidInit,          VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_FLOWCTRL_C,   "CCpuFlowCtrl", FC_CCORE_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_RM_DL,        "RM_DL_FID",    WTTF_MAC_RLC_DlFidInit, VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NOSIG,       "OM_NOSIG",     OM_NoSigFidInit,        VOS_START_THIRD,    0,      0  },\
    {UEPS_FID_TTF_MEM_RB_FREE, "MMRB_FREE", TTF_MemRbFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_CDS,          "CDS_FID",      CDS_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_NDCLIENT,     "NCCLIENT_FID", NDCLIENT_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_PBD,       "I0_PBD_FID",   PBD_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {HL1_FID_SNDCMD,        "SNDCMD_FID",   VOS_NULL_PTR,   VOS_START_THIRD,    0,      0  },\
    {TPS_FID_MAC,           "TPS_FID_MAC",  VOS_NULL_PTR,    VOS_START_THIRD,    0,      0  },\
    {TPS_FID_PDC,           "TPS_FID_PDC",  VOS_NULL_PTR,    VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NVIM_FLUSH,  "NV_FLUSH",     VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_SLEEP,       "SLEEP",        WuepsSleepFidInit,      VOS_START_THIRD,    4096,   0  },\
    {I0_DSP_FID_APM,        "DSP_APM0",     UPHY_APM_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_UPA,           "DSP_UPA",      UPHY_UCOM_UpaFidInit,   VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WPHY,          "DSP_WPHY",     UPHY_UCOM_WphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_GPHY,       "DSP_GPHY0",    UPHY_UCOM_GphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_DRX,        "DSP_DRX0",     UPHY_DRX_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_IDLE,       "DSP_IDLE0",    UPHY_IDLE_FidInit,      VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WMEAS,         "DSP_WMEAS",    UPHY_UCOM_WmeasFidInit, VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_IPS_CCORE,    "IPS_CCORE",    IPS_MNTN_CCORE_FidInit, VOS_START_THIRD,    8192,   0  },\
    {I1_MAPS_USIMM_FID,     "USIMM_FID1",   I1_USIMM_FID_Init,      VOS_START_THIRD,    8192,   0  },\
    {I1_MAPS_SI_FID,        "SI_FID1",      I1_WuepsSIFidInit,      VOS_START_THIRD,    0,      0  },\
    {I1_WUEPS_FID_SLEEP,    "I1_SLEEP",     I1_WuepsSleepFidInit,   VOS_START_THIRD,    4096,   0  },\
    {I1_UEPS_FID_RR,        "RR_FID1",      I1_GAS_FidPidInit,      VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_MM,       "MM_FID1",      I1_NAS_MML_FidInit,     VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_CM,       "CM_FID1",      I1_WuepsCmFidInit,      VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_RABMSM,   "RABMSM_FID1",  I1_WuepsRabmFidInit,    VOS_START_THIRD,    16384,  0  },\
    {I1_WUEPS_FID_TAF,      "TAF_FID1",     I1_WuepsTafFidInit,     VOS_START_THIRD,    0,      0  },\
    {I1_UEPS_FID_SL,        "SL_FID1",      I1_LLC_FID_Init,        VOS_START_THIRD,    16384,  0  },\
    {I1_UEPS_FID_PBD,       "PBD_FID1",     I1_PBD_FID_Init,        VOS_START_THIRD,    16384,  0  },\
    {I1_UEPS_FID_GRM,       "GRM_FID1",     I1_GRM_FID_Init,        VOS_START_THIRD,    16384,  0  },\
    {I1_DSP_FID_APM,        "DSP_APM1",     I1_UPHY_APM_FidInit,    VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_GPHY,       "DSP_GPHY1",    I1_UPHY_UCOM_GphyFidInit, VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_DRX,        "DSP_DRX1",     I1_UPHY_DRX_FidInit,    VOS_START_THIRD,    8192,   0  },\
    {I1_DSP_FID_IDLE,       "DSP_IDLE1",    I1_UPHY_IDLE_FidInit,   VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_MTC,          "MTC",          MTC_FidInit,            VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_RRM,          "RRM_FID",      RRM_FidInit,            VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CBPCA,       "CBPCA_FID",    CBPCA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CSIMA,       "CSIMA_FID",    CSIMA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CMMCA,       "CMMCA",        CMMCA_FidInit,          VOS_START_THIRD,    4096,   0  },
#else
#define DEFINE_PRODUCT_FID_TABLE \
    {WUEPS_FID_OM,          "OM",           WuepsOMFidInit,         VOS_START_THIRD,    6144,   0  },\
    {I0_MAPS_USIMM_FID,     "USIMM_FID",    USIMM_FID_Init,         VOS_START_THIRD,    8192,   0  },\
    {I0_MAPS_SI_FID,        "SI_FID",       WuepsSIFidInit,         VOS_START_THIRD,    0,      0  },\
    {MSP_FID_DIAG_CCPU,     "mspDiag",      MSP_DiagFidInit,        VOS_START_THIRD,    8192,   0  },\
    {MSP_L4_FID,            "mspL4",        MSP_L4FidInit,          VOS_START_THIRD,    16384,  0  },\
    {MSP_HAL_FID,           "mspDRA",       VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {MSP_FTM_FID,           "mspFTM",       MSP_FtmFidInit,         VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_SL,        "I0_SL_FID",    LLC_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_RM,           "RM_FID",       WTTF_MAC_RLC_UlFidInit, VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_RR,        "I0_RR_FID",    GAS_FidPidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_UEPS_FID_GRM,       "I0_GRM_FID",   GRM_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {WUEPS_FID_HPA,         "HPA_FID",      HPA_FIDInit,            VOS_START_THIRD,    2560,   0  },\
    {I0_WUEPS_FID_MM,       "I0_MM_FID",    NAS_MML_FidInit,        VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_CM,       "I0_CM_FID",    WuepsCmFidInit,         VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_RABMSM,   "I0_RABMSM_FID",WuepsRabmFidInit,       VOS_START_THIRD,    16384,  0  },\
    {I0_WUEPS_FID_TAF,      "I0_TAF_FID",   WuepsTafFidInit,        VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_OM_CALLBACK, "OMCALLBACK",   OMCallBackFidInit,      VOS_START_THIRD,    5632,   0  },\
    {WUEPS_FID_SPY,         "SPY",          Spy_FID_Init,           VOS_START_THIRD,    6144,   0  },\
    {AGENT_FID_OM,          "AGENT_OM",     OM_AgentFidInit,        VOS_START_THIRD,    0,      0  },\
    {PS_FID_RRC,            "LRRC_FID",     RRC_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {PS_FID_CM,             "LCM_FID",      CM_FidInit,             VOS_START_THIRD,    16384,  0  },\
    {PS_FID_OM,             "LPSOM_FID",    PS_OM_FidInit,          VOS_START_THIRD,    4096,   0  },\
    {PS_FID_RM_UL,          "MACRLCUL_FID", LMAC_RLC_UlFidInit,     VOS_START_THIRD,    16384,  0  },\
    {PS_FID_RM_DL,          "MACRLCDL_FID", LMAC_RLC_DlFidInit,     VOS_START_THIRD,    16384,  0  },\
    {PS_FID_HPA,            "LHPA_FID",     LHPA_FidPidInit,        VOS_START_THIRD,    4096,   0  },\
    {PS_FID_COMM,           "PS_FID_COMM",  VOS_NULL_PTR,           VOS_START_THIRD,    4096,   0  },\
    {PS_FID_IMSA,           "IMSA_FID",     IMSA_FidInit,           VOS_START_THIRD,    4096,  0  },\
    {PS_FID_IMSVA,          "IMSVA_FID",    IMSVA_FidInit,          VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_FLOWCTRL_C,   "CCpuFlowCtrl", FC_CCORE_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_RM_DL,        "RM_DL_FID",    WTTF_MAC_RLC_DlFidInit, VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NOSIG,       "OM_NOSIG",     OM_NoSigFidInit,        VOS_START_THIRD,    0,      0  },\
    {UEPS_FID_TTF_MEM_RB_FREE, "MMRB_FREE", TTF_MemRbFreeFidInit,   VOS_START_THIRD,    4096,   0  },\
    {UEPS_FID_CDS,          "CDS_FID",      CDS_FidInit,            VOS_START_THIRD,    16384,  0  },\
    {UEPS_FID_NDCLIENT,     "NCCLIENT_FID", NDCLIENT_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_UEPS_FID_PBD,       "I0_PBD_FID",   PBD_FID_Init,           VOS_START_THIRD,    16384,  0  },\
    {HL1_FID_SNDCMD,        "SNDCMD_FID",   VOS_NULL_PTR,   VOS_START_THIRD,    0,      0  },\
    {TPS_FID_MAC,           "TPS_FID_MAC",  VOS_NULL_PTR,    VOS_START_THIRD,    0,      0  },\
    {TPS_FID_PDC,           "TPS_FID_PDC",  VOS_NULL_PTR,    VOS_START_THIRD,    0,      0  },\
    {WUEPS_FID_NVIM_FLUSH,  "NV_FLUSH",     VOS_NULL_PTR,           VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_SLEEP,       "SLEEP",        WuepsSleepFidInit,      VOS_START_THIRD,    4096,   0  },\
    {I0_DSP_FID_APM,        "DSP_APM0",     UPHY_APM_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_UPA,           "DSP_UPA",      UPHY_UCOM_UpaFidInit,   VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WPHY,          "DSP_WPHY",     UPHY_UCOM_WphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_GPHY,       "DSP_GPHY0",    UPHY_UCOM_GphyFidInit,  VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_DRX,        "DSP_DRX0",     UPHY_DRX_FidInit,       VOS_START_THIRD,    8192,   0  },\
    {I0_DSP_FID_IDLE,       "DSP_IDLE0",    UPHY_IDLE_FidInit,      VOS_START_THIRD,    8192,   0  },\
    {DSP_FID_WMEAS,         "DSP_WMEAS",    UPHY_UCOM_WmeasFidInit, VOS_START_THIRD,    8192,   0  },\
    {UEPS_FID_IPS_CCORE,    "IPS_CCORE",    IPS_MNTN_CCORE_FidInit, VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CBPCA,       "CBPCA_FID",    CBPCA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CSIMA,       "CSIMA_FID",    CSIMA_FidInit,          VOS_START_THIRD,    8192,   0  },\
    {WUEPS_FID_CMMCA,       "CMMCA",        CMMCA_FidInit,          VOS_START_THIRD,    4096,   0  },
#endif  /*( FEATURE_MULTI_MODEM == FEATURE_ON )*/
#endif  /*(FEATURE_ON == FEATURE_UE_MODE_TDS)*/
#endif  /*(RAT_MODE == RAT_GU)*/
#endif  /*(VOS_WIN32 == VOS_OS_VER)*/

#if (OSA_CPU_ACPU == VOS_OSA_CPU)
#if (FEATURE_VOICE_UP == FEATURE_ON)
#if (RAT_MODE == RAT_GU)
#define DEFINE_PRODUCT_FID_TABLE \
    {UEPS_FID_IMM_RB_FREE,      "IMM_RB_FREE",     IMM_RbMemFreeFidInit,    VOS_START_THIRD,    4096,  0  },\
    {MSP_APP_DS_FID,            "mspAppDS",        DMS_DsFidInit,           VOS_START_THIRD,    8192,  0  },\
    {PS_FID_APP_NDIS_PPP_DIPC,  "AppNdisPppDipc",    APP_NDIS_FidInit,   VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_OM_CALLBACK,      "ACPUOMCB",        OM_AcpuCallBackFidInit,  VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_OM,               "ACPU_OM ",        OM_AcpuFidInit,          VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_RNIC,             "RNIC",            RNIC_FidInit ,           VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_NFEXT,            "ACPU_NFEXT",      NFExt_FidInit,           VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_ADS_UL,           "ADS_UL",          ADS_UL_FidInit ,         VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_ADS_DL,           "ADS_DL",          ADS_DL_FidInit ,         VOS_START_THIRD,    5120,  0  },\
    {ACPU_FID_CSD,              "CSD",             CSD_FidInit ,            VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_TAFAGENT,         "TAF_AGENT",       TAF_AGENT_FidInit ,      VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_CPULOAD,          "CpuLoadMonitor",  CPULOAD_FidInit ,        VOS_START_THIRD,    4096,  0  },\
    {UEPS_FID_FLOWCTRL_A,       "ACpuFlowCtrl",    FC_ACORE_FidInit ,       VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_MED_RT,           "MED_Voice_RT",    VOICE_RtFidInit,         VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_MED,              "MED_Voice",       VOICE_NormalFidInit,     VOS_START_THIRD,    16384, 0  },
#else /* RAT_MODE != RAT_GU) */
#define DEFINE_PRODUCT_FID_TABLE \
    {UEPS_FID_IMM_RB_FREE,      "IMM_RB_FREE",     IMM_RbMemFreeFidInit,    VOS_START_THIRD,    4096,  0  },\
    {MSP_APP_DS_FID,            "mspAppDS",        DMS_DsFidInit,           VOS_START_THIRD,    8192,  0  },\
    {PS_FID_APP_NDIS_PPP_DIPC,  "AppNdisPppDipc",    APP_NDIS_FidInit,   VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_OM_CALLBACK,      "ACPUOMCB",        OM_AcpuCallBackFidInit,  VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_OM,               "ACPU_OM ",        OM_AcpuFidInit,          VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_RNIC,             "RNIC",            RNIC_FidInit ,           VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_NFEXT,            "ACPU_NFEXT",      NFExt_FidInit,           VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_ADS_UL,           "ADS_UL",          ADS_UL_FidInit ,         VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_ADS_DL,           "ADS_DL",          ADS_DL_FidInit ,         VOS_START_THIRD,    5120,  0  },\
    {ACPU_FID_CSD,              "CSD",             CSD_FidInit ,            VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_TAFAGENT,         "TAF_AGENT",       TAF_AGENT_FidInit ,      VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_CPULOAD,          "CpuLoadMonitor",  CPULOAD_FidInit ,        VOS_START_THIRD,    4096,  0  },\
    {UEPS_FID_FLOWCTRL_A,       "ACpuFlowCtrl",    FC_ACORE_FidInit ,       VOS_START_THIRD,    8192,  0  },\
    {MSP_FID_DIAG_ACPU,         "mspAppDiag",      MSP_AppDiagFidInit,       VOS_START_THIRD,    16384,  0  },
    {ACPU_FID_MED_RT,           "MED_Voice_RT",    VOICE_RtFidInit,         VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_MED,              "MED_Voice",       VOICE_NormalFidInit,     VOS_START_THIRD,    16384, 0  },
#endif /* #if (RAT_MODE == RAT_GU) */
#else  /* FEATURE_VOICE_UP != FEATURE_ON */
#if (RAT_MODE == RAT_GU)
#define DEFINE_PRODUCT_FID_TABLE \
    {UEPS_FID_IMM_RB_FREE,      "IMM_RB_FREE",     IMM_RbMemFreeFidInit,    VOS_START_THIRD,    4096,  0  },\
    {MSP_APP_DS_FID,            "mspAppDS",        DMS_DsFidInit,           VOS_START_THIRD,    8192,  0  },\
    {PS_FID_APP_NDIS_PPP_DIPC,  "AppNdisPppDipc",    APP_NDIS_FidInit,   VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_OM_CALLBACK,      "ACPUOMCB",        OM_AcpuCallBackFidInit,  VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_OM,               "ACPU_OM ",        OM_AcpuFidInit,          VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_RNIC,             "RNIC",            RNIC_FidInit ,           VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_NFEXT,            "ACPU_NFEXT",      NFExt_FidInit,           VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_ADS_UL,           "ADS_UL",          ADS_UL_FidInit ,         VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_ADS_DL,           "ADS_DL",          ADS_DL_FidInit ,         VOS_START_THIRD,    5120,  0  },\
    {ACPU_FID_CSD,              "CSD",             CSD_FidInit ,            VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_TAFAGENT,         "TAF_AGENT",       TAF_AGENT_FidInit ,      VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_CPULOAD,          "CpuLoadMonitor",  CPULOAD_FidInit ,        VOS_START_THIRD,    4096,  0  },\
    {UEPS_FID_FLOWCTRL_A,       "ACpuFlowCtrl",    FC_ACORE_FidInit ,       VOS_START_THIRD,    8192,  0  },
#else /* RAT_MODE != RAT_GU) */
#define DEFINE_PRODUCT_FID_TABLE \
    {UEPS_FID_IMM_RB_FREE,      "IMM_RB_FREE",     IMM_RbMemFreeFidInit,    VOS_START_THIRD,    4096,  0  },\
    {MSP_APP_DS_FID,            "mspAppDS",        DMS_DsFidInit,           VOS_START_THIRD,    8192,  0  },\
    {PS_FID_APP_NDIS_PPP_DIPC,  "AppNdisPppDipc",    APP_NDIS_FidInit,   VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_OM_CALLBACK,      "ACPUOMCB",        OM_AcpuCallBackFidInit,  VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_OM,               "ACPU_OM ",        OM_AcpuFidInit,          VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_RNIC,             "RNIC",            RNIC_FidInit ,           VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_NFEXT,            "ACPU_NFEXT",      NFExt_FidInit,           VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_ADS_UL,           "ADS_UL",          ADS_UL_FidInit ,         VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_ADS_DL,           "ADS_DL",          ADS_DL_FidInit ,         VOS_START_THIRD,    5120,  0  },\
    {ACPU_FID_CSD,              "CSD",             CSD_FidInit ,            VOS_START_THIRD,    8192,  0  },\
    {ACPU_FID_TAFAGENT,         "TAF_AGENT",       TAF_AGENT_FidInit ,      VOS_START_THIRD,    16384, 0  },\
    {ACPU_FID_CPULOAD,          "CpuLoadMonitor",  CPULOAD_FidInit ,        VOS_START_THIRD,    4096,  0  },\
    {UEPS_FID_FLOWCTRL_A,       "ACpuFlowCtrl",    FC_ACORE_FidInit ,       VOS_START_THIRD,    8192,  0  },\
    {MSP_FID_DIAG_ACPU,         "mspAppDiag",      MSP_AppDiagFidInit,       VOS_START_THIRD,    16384,  0  },
#endif /* #if (RAT_MODE == RAT_GU) */
#endif
#endif

#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_UINT32 WuepsFidITTStubInit( enum VOS_INIT_PHASE_DEFINE ip ) ;
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _V_ID_H */

