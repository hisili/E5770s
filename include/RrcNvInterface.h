

#ifndef __RRCNVINTERFACE_H__
#define __RRCNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "PsTypeDef.h"

#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
	/* �Ǳ�׼Ƶ�� begin */
#define LTE_COMM_NONSTANDARD_BAND_BEGIN                     101
#define LTE_COMM_NONSTANDARD_BAND_END                       116
	
#define LTE_COMM_NONSTANDARD_BAND_MAX_COUNT                 16
	/* �Ǳ�׼Ƶ�� end */


/* reportCGI stub Begin */
/* CMM����С��CGI��Ϣ�б�ṹ */
#define RRC_NV_USER_SET_CGI_MAX_NUM             (5)
#define RRC_NV_AUTO_SRCH_CGI_MAX_NUM            (16)
#define RRC_UU_MAX_NUM_OF_PLMN_ID_LIST_2        (5)
#define RRC_UU_MNC_MCC_MAX_LEN                  (3)
/* reportCGI stub end */

#define RRC_NV_CSEL_MAX_INTER_FREQ_COUNT        (8)
#define RRC_NV_EACH_BAND_FREQ_COUNT             (32)                            /* ÿ��band��nv�洢��Ƶ����� */
#define RRC_MAX_NUM_OF_COUNT_IN_ONE_BAND        (4)
#define RRC_NV_CSEL_MAX_STORED_CELL_COUNT_PER_FREQ (4)
#define RRC_CSEL_MAX_FREQ_COUNT                 (128)                            /* csel���ر����Ƶ������� */
#define RRC_NV_EACH_BAND_BANDS_COUNT            (4)

#define RRC_NV_LWCLASH_RANGE_COUNT              (16)

/* UE������غ궨�� */
#define RRC_MAX_NUM_OF_BANDS                    (64)
#define RRC_MAX_NUM_OF_CDMA_BAND_CLASS          (32)
#define RRC_MAX_NUM_OF_FEATURE_GROUP            (32)
/* v7r2 LLD begin */
#if 0
#define RRC_MAX_NUM_OF_BAND_COMB_R10            (128)
#define RRC_MAX_NUM_OF_SIMULTANEOUS_BANDS_R10   (64)
#define RRC_MAX_NUM_OF_BANDWIDTH_CLASS_R10      (16)
#endif
#define RRC_MAX_NUM_OF_BAND_COMB_R10            (32)
#define RRC_MAX_NUM_OF_SIMULTANEOUS_BANDS_R10   (4)
#define RRC_MAX_NUM_OF_BANDWIDTH_CLASS_R10      (16)

#define RRC_MAX_NUM_OF_SUPPORT_BAND_COMB_EXT_R10 (128)

/* v7r2 LLD end */

#define RRC_REL8_ACCESS_STRATUM_REL             0x01
#define RRC_REL9_ACCESS_STRATUM_REL             0x02
/* v7r2 code begin */
#define RRC_REL10_ACCESS_STRATUM_REL            0x04
/* v7r2 code end */
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
/*****************************************************************************
 ö����    : LRRC_LTE_MODE_TYPE_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  : LTEģʽ����
*****************************************************************************/
enum LTE_COMM_BAND_MODE_TYPE_ENUM
{
	LTE_COMM_BAND_MODE_TYPE_FDD 			   = 0, 							/* LTE FDD ��ʽ */
	LTE_COMM_BAND_MODE_TYPE_TDD 			   = 1, 							/* LTE TDD ��ʽ */
	LTE_COMM_BAND_MODE_TYPE_BUTT
};
typedef VOS_UINT8 LTE_COMM_BAND_MODE_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CATEGORY_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : UE Category
*****************************************************************************/
enum RRC_UE_CATEGORY_ENUM
{
    RRC_UE_CATEGORY_1                   = 0,
    RRC_UE_CATEGORY_2                   = 1,
    RRC_UE_CATEGORY_3                   = 2,
    RRC_UE_CATEGORY_4                   = 3,
    RRC_UE_CATEGORY_5                   = 4,
    RRC_UE_CATEGORY_BUTT
};
typedef VOS_UINT8 RRC_UE_CATEGORY_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_ROH_CONTEXT_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : maxNumberROHC-ContextSessions
*****************************************************************************/
enum RRC_UE_CAP_ROH_CONTEXT_ENUM
{
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS2    = 0,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS4    ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS8    ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS12   ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS16   ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS24   ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS32   ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS48   ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS64   ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS128  ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS256  ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS512  ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS1024 ,
    RRC_MAX_NUM_ROHC_CTX_SESSION_CS16384,
    RRC_MAX_NUM_ROHC_CTX_SESSION_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_ROH_CONTEXT_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_UTRA_FDD_BAND_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  : utra-FDD-Band
*****************************************************************************/
enum RRC_UE_CAP_UTRA_FDD_BAND_ENUM
{
    RRC_UE_CAP_UTRA_FDD_BAND_I          = 0,
    RRC_UE_CAP_UTRA_FDD_BAND_II         = 1,
    RRC_UE_CAP_UTRA_FDD_BAND_III        = 2,
    RRC_UE_CAP_UTRA_FDD_BAND_IV         = 3,
    RRC_UE_CAP_UTRA_FDD_BAND_V          = 4,
    RRC_UE_CAP_UTRA_FDD_BAND_VI         = 5,
    RRC_UE_CAP_UTRA_FDD_BAND_VII        = 6,
    RRC_UE_CAP_UTRA_FDD_BAND_VIII       = 7,
    RRC_UE_CAP_UTRA_FDD_BAND_IX         = 8,
    RRC_UE_CAP_UTRA_FDD_BAND_X          = 9,
    RRC_UE_CAP_UTRA_FDD_BAND_XI         = 10,
    RRC_UE_CAP_UTRA_FDD_BAND_XII        = 11,
    RRC_UE_CAP_UTRA_FDD_BAND_XIII       = 12,
    RRC_UE_CAP_UTRA_FDD_BAND_XIV        = 13,
    RRC_UE_CAP_UTRA_FDD_BAND_XV         = 14,
    RRC_UE_CAP_UTRA_FDD_BAND_XVI        = 15,
    RRC_UE_CAP_UTRA_FDD_BAND_XVII       = 16,
    RRC_UE_CAP_UTRA_FDD_BAND_XVIII      = 17,
    RRC_UE_CAP_UTRA_FDD_BAND_XIX        = 18,
    RRC_UE_CAP_UTRA_FDD_BAND_XX         = 19,
    RRC_UE_CAP_UTRA_FDD_BAND_XXI        = 20,
    RRC_UE_CAP_UTRA_FDD_BAND_XXII       = 21,
    RRC_UE_CAP_UTRA_FDD_BAND_XXIII      = 22,
    RRC_UE_CAP_UTRA_FDD_BAND_XXIV       = 23,
    RRC_UE_CAP_UTRA_FDD_BAND_XXV        = 24,
    RRC_UE_CAP_UTRA_FDD_BAND_XXVI       = 25,
    RRC_UE_CAP_UTRA_FDD_BAND_XXVII      = 26,
    RRC_UE_CAP_UTRA_FDD_BAND_XXVIII     = 27,
    RRC_UE_CAP_UTRA_FDD_BAND_XXIX       = 28,
    RRC_UE_CAP_UTRA_FDD_BAND_XXX        = 29,
    RRC_UE_CAP_UTRA_FDD_BAND_XXXI       = 30,
    RRC_UE_CAP_UTRA_FDD_BAND_XXXII      = 31,
    RRC_UE_CAP_UTRA_FDD_BAND_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_UTRA_FDD_BAND_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_UTRA_TDD128_BAND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : utra-TDD128Band
*****************************************************************************/
enum RRC_UE_CAP_UTRA_TDD128_BAND_ENUM
{
    RRC_UE_CAP_UTRA_TDD128_BAND_A       = 0,
    RRC_UE_CAP_UTRA_TDD128_BAND_B       = 1,
    RRC_UE_CAP_UTRA_TDD128_BAND_C       = 2,
    RRC_UE_CAP_UTRA_TDD128_BAND_D       = 3,
    RRC_UE_CAP_UTRA_TDD128_BAND_E       = 4,
    RRC_UE_CAP_UTRA_TDD128_BAND_F       = 5,
    RRC_UE_CAP_UTRA_TDD128_BAND_G       = 6,
    RRC_UE_CAP_UTRA_TDD128_BAND_H       = 7,
    RRC_UE_CAP_UTRA_TDD128_BAND_I       = 8,
    RRC_UE_CAP_UTRA_TDD128_BAND_J       = 9,
    RRC_UE_CAP_UTRA_TDD128_BAND_K       = 10,
    RRC_UE_CAP_UTRA_TDD128_BAND_L       = 11,
    RRC_UE_CAP_UTRA_TDD128_BAND_M       = 12,
    RRC_UE_CAP_UTRA_TDD128_BAND_N       = 13,
    RRC_UE_CAP_UTRA_TDD128_BAND_O       = 14,
    RRC_UE_CAP_UTRA_TDD128_BAND_P       = 15,
    RRC_UE_CAP_UTRA_TDD128_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_UTRA_TDD128_BAND_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_UTRA_TDD384_BAND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : utra-TDD384Band
*****************************************************************************/
enum RRC_UE_CAP_UTRA_TDD384_BAND_ENUM
{
    RRC_UE_CAP_UTRA_TDD384_BAND_A       = 0,
    RRC_UE_CAP_UTRA_TDD384_BAND_B       = 1,
    RRC_UE_CAP_UTRA_TDD384_BAND_C       = 2,
    RRC_UE_CAP_UTRA_TDD384_BAND_D       = 3,
    RRC_UE_CAP_UTRA_TDD384_BAND_E       = 4,
    RRC_UE_CAP_UTRA_TDD384_BAND_F       = 5,
    RRC_UE_CAP_UTRA_TDD384_BAND_G       = 6,
    RRC_UE_CAP_UTRA_TDD384_BAND_H       = 7,
    RRC_UE_CAP_UTRA_TDD384_BAND_I       = 8,
    RRC_UE_CAP_UTRA_TDD384_BAND_J       = 9,
    RRC_UE_CAP_UTRA_TDD384_BAND_K       = 10,
    RRC_UE_CAP_UTRA_TDD384_BAND_L       = 11,
    RRC_UE_CAP_UTRA_TDD384_BAND_M       = 12,
    RRC_UE_CAP_UTRA_TDD384_BAND_N       = 13,
    RRC_UE_CAP_UTRA_TDD384_BAND_O       = 14,
    RRC_UE_CAP_UTRA_TDD384_BAND_P       = 15,
    RRC_UE_CAP_UTRA_TDD384_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_UTRA_TDD384_BAND_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_UTRA_TDD768_BAND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : utra-TDD768Band
*****************************************************************************/
enum RRC_UE_CAP_UTRA_TDD768_BAND_ENUM
{
    RRC_UE_CAP_UTRA_TDD768_BAND_A       = 0,
    RRC_UE_CAP_UTRA_TDD768_BAND_B       = 1,
    RRC_UE_CAP_UTRA_TDD768_BAND_C       = 2,
    RRC_UE_CAP_UTRA_TDD768_BAND_D       = 3,
    RRC_UE_CAP_UTRA_TDD768_BAND_E       = 4,
    RRC_UE_CAP_UTRA_TDD768_BAND_F       = 5,
    RRC_UE_CAP_UTRA_TDD768_BAND_G       = 6,
    RRC_UE_CAP_UTRA_TDD768_BAND_H       = 7,
    RRC_UE_CAP_UTRA_TDD768_BAND_I       = 8,
    RRC_UE_CAP_UTRA_TDD768_BAND_J       = 9,
    RRC_UE_CAP_UTRA_TDD768_BAND_K       = 10,
    RRC_UE_CAP_UTRA_TDD768_BAND_L       = 11,
    RRC_UE_CAP_UTRA_TDD768_BAND_M       = 12,
    RRC_UE_CAP_UTRA_TDD768_BAND_N       = 13,
    RRC_UE_CAP_UTRA_TDD768_BAND_O       = 14,
    RRC_UE_CAP_UTRA_TDD768_BAND_P       = 15,
    RRC_UE_CAP_UTRA_TDD768_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_UTRA_TDD768_BAND_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_GERAN_BAND_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : geran-Band
*****************************************************************************/
enum RRC_UE_CAP_GERAN_BAND_ENUM
{
    RRC_UE_CAP_GSM450_GERAN_BAND = 0,
    RRC_UE_CAP_GSM480_GERAN_BAND,
    RRC_UE_CAP_GSM710_GERAN_BAND,
    RRC_UE_CAP_GSM750_GERAN_BAND,
    RRC_UE_CAP_GSM810_GERAN_BAND,
    RRC_UE_CAP_GSM850_GERAN_BAND,
    RRC_UE_CAP_GSM900P_GERAN_BAND,
    RRC_UE_CAP_GSM900E_GERAN_BAND,
    RRC_UE_CAP_GSM900R_GERAN_BAND,
    RRC_UE_CAP_GSM1800_GERAN_BAND,
    RRC_UE_CAP_GSM1900_GERAN_BAND,
    RRC_UE_CAP_GERAN_BAND_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_GERAN_BAND_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_CDMA2000_HRPD_TX_CONFIG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : cdma2000-HRPD-TxConfig
*****************************************************************************/
enum RRC_UE_CAP_CDMA2000_HRPD_TX_CONFIG_ENUM
{
    RRC_UE_CAP_CDMA2000_HRPD_TX_SINGLE  = 0,
    RRC_UE_CAP_CDMA2000_HRPD_TX_DUAL    = 1,
    RRC_UE_CAP_CDMA2000_HRPD_TX_BUTT
} ;
typedef VOS_UINT8 RRC_UE_CAP_CDMA2000_HRPD_TX_CONFIG_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_CDMA2000_HRPD_RX_CONFIG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : cdma2000-HRPD-RxConfig
*****************************************************************************/
enum RRC_UE_CAP_CDMA2000_HRPD_RX_CONFIG_ENUM
{
    RRC_UE_CAP_CDMA2000_HRPD_RX_SINGLE  = 0,
    RRC_UE_CAP_CDMA2000_HRPD_RX_DUAL    = 1,
    RRC_UE_CAP_CDMA2000_HRPD_RX_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_CDMA2000_HRPD_RX_CONFIG_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_CDMA2000_1X_RTT_TX_CONFIG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : cdma2000-1xRTT-TxConfig
*****************************************************************************/
enum RRC_UE_CAP_CDMA2000_1X_RTT_TX_CONFIG_ENUM
{
    RRC_UE_CAP_CDMA2000_1X_RTT_TX_SINGLE = 0,
    RRC_UE_CAP_CDMA2000_1X_RTT_TX_DUAL = 1,
    RRC_UE_CAP_CDMA2000_1X_RTT_TX_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_CDMA2000_1X_RTT_TX_CONFIG_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_CDMA2000_1X_RTT_RX_CONFIG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : cdma2000-1xRTT-RxConfig
*****************************************************************************/
enum RRC_UE_CAP_CDMA2000_1X_RTT_RX_CONFIG_ENUM
{
    RRC_UE_CAP_CDMA2000_1X_RTT_RX_SINGLE = 0,
    RRC_UE_CAP_CDMA2000_1X_RTT_RX_DUAL   = 1,
    RRC_UE_CAP_CDMA2000_1X_RTT_RX_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_CDMA2000_1X_RTT_RX_CONFIG_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_CDMA2000_BANDCLASS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : CDMA2000-Bandclass
*****************************************************************************/
enum RRC_UE_CAP_CDMA2000_BANDCLASS_ENUM
{
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC0   = 0,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC1   = 1,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC2   = 2,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC3   = 3,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC4   = 4,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC5   = 5,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC6   = 6,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC7   = 7,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC8   = 8,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC9   = 9,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC10  = 10,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC11  = 11,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC12  = 12,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC13  = 13,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC14  = 14,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC15  = 15,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC16  = 16,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BC17  = 17,
    RRC_UE_CAP_CDMA2000_BANDCLASS_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_CDMA2000_BANDCLASS_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : RRC_NV_LOCK_INFO_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ָʾ
 *****************************************************************************/
enum RRC_NV_LOCK_INFO_ENUM
{
    RRC_NV_LOCK_NONE           = 0,                                           /* ������ */
    RRC_NV_LOCK_BAND,                                                         /* ����BAND */
    RRC_NV_LOCK_FREQ,                                                         /* ����Ƶ�� */
    RRC_NV_LOCK_CELL,                                                         /* ����С�� */
    RRC_NV_LOCK_BUTT
};
typedef VOS_UINT32  RRC_NV_LOCK_INFO_ENUM_UINT32;
/*****************************************************************************
 �ṹ��    : RRC_NV_UE_RFRD_TYPE_ENUM
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ƶ����ָʾ
 *****************************************************************************/
enum RRC_NV_UE_RFRD_TYPE_ENUM
{
    RRC_NV_UE_RFRD_HI6360           = 0,
    RRC_NV_UE_RFRD_AD9361,
    RRC_NV_UE_RFRD_BUTT
};
typedef VOS_UINT8  RRC_NV_UE_RFRD_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ָʾ�����Ƿ�֧��
*****************************************************************************/
enum RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM
{
    RRC_UE_CAP_FEATURE_SUPPORTED     = 0,
    RRC_UE_CAP_FEATURE_NOT_SUPPORTED = 1,
    RRC_UE_CAP_FEATURE_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_UE_CAP_DEVICE_TYPE_R9_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  : ����ָʾ�Ƿ��ȡNW-basedʡ���Ż�
*****************************************************************************/
enum RRC_UE_CAP_DEVICE_TYPE_R9_ENUM
{
    RRC_NO_BEN_FROM_BAT_CONSUMP_OPT   = 0,
    RRC_BEN_FROM_BAT_CONSUMP_OPT      = 1,
    RRC_BAT_CONSUMP_OPT_BUTT
};
typedef VOS_UINT8 RRC_UE_CAP_DEVICE_TYPE_R9_ENUM_UINT8;

/* v7r2 LLD begin */
/*****************************************************************************
 ö����    : RRC_CA_BANDWIDTH_CLASS_R10_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum RRC_CA_BANDWIDTH_CLASS_R10_ENUM
{
    RRC_CA_BANDWIDTH_CLASS_A          = 0,
    RRC_CA_BANDWIDTH_CLASS_B,
    RRC_CA_BANDWIDTH_CLASS_C,
    RRC_CA_BANDWIDTH_CLASS_D,
    RRC_CA_BANDWIDTH_CLASS_E,
    RRC_CA_BANDWIDTH_CLASS_F
};
typedef VOS_UINT8 RRC_CA_BANDWIDTH_CLASS_R10_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_MIMO_CAP_UL_R10_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum RRC_MIMO_CAP_UL_R10_ENUM
{
    RRC_MIMO_CAP_UL_TWO_LAYERS        = 0,
    RRC_MIMO_CAP_UL_FOUR_LAYERS       = 1
};
typedef VOS_UINT8 RRC_MIMO_CAP_UL_R10_ENUM_UINT8;

/*****************************************************************************
 ö����    : RRC_MIMO_CAP_DL_R10_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :
*****************************************************************************/
enum RRC_MIMO_CAP_DL_R10_ENUM
{
    RRC_TWO_LAYERS_MIMO_CAP_DL_R10               = 0,
    RRC_FOUR_LAYERS_MIMO_CAP_DL_R10              = 1,
    RRC_EIGHT_LAYERS_MIMO_CAP_DL_R10             = 2
};
typedef VOS_UINT8 RRC_MIMO_CAP_DL_R10_ENUM_UINT8;

/*********************************************************************
ö����    : RRC_PDCP_SN_EXT_R11_ENUM
Э����  :
ASN.1���� :
ö��˵��  :
*********************************************************************/
typedef enum
{
    RRC_SUPP_PDCP_SN_EXT_R11                     = 0
}RRC_PDCP_SN_EXT_R11_ENUM;
typedef VOS_UINT8                 RRC_PDCP_SN_EXT_R11_ENUM_UINT8;
/*********************************************************************
ö����    : RRC_SUPPORT_ROHC_CONTEXT_CONTINUE_R11_ENUM
Э����  :
ASN.1���� :
ö��˵��  :
*********************************************************************/
typedef enum
{
    RRC_SUPP_SUPPORT_ROHC_CONTEXT_CONTINUE_R11   = 0
}RRC_SUPPORT_ROHC_CONTEXT_CONTINUE_R11_ENUM;
typedef VOS_UINT8                 RRC_SUPPORT_ROHC_CONTEXT_CONTINUE_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: crs-InterfHandl-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_CRS_INTERF_HANDL_R11                = 0
}RRC_CRS_INTERF_HANDL_R11_ENUM;
typedef VOS_UINT8                 RRC_CRS_INTERF_HANDL_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: ePDCCH-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_EPDCCH_R11                          = 0
}RRC_EPDCCH_R11_ENUM;
typedef VOS_UINT8                 RRC_EPDCCH_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: multiACK-CSI-Reporting-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_MULTI_ACK_CSI_RPRTING_R11           = 0
}RRC_MULTI_ACK_CSI_RPRTING_R11_ENUM;
typedef VOS_UINT8                 RRC_MULTI_ACK_CSI_RPRTING_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: ss-CCH-InterfHandl-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_SS_CCH_INTERF_HANDL_R11             = 0
}RRC_SS_CCH_INTERF_HANDL_R11_ENUM;
typedef VOS_UINT8                 RRC_SS_CCH_INTERF_HANDL_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: tdd-SpecialSubframe-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_TDD_SPECIAL_SUBFRAME_R11            = 0
}RRC_TDD_SPECIAL_SUBFRAME_R11_ENUM;
typedef VOS_UINT8                 RRC_TDD_SPECIAL_SUBFRAME_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: txDiv-PUCCH1b-ChSelect-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_TX_DIV_PUCCH1B_CH_SELECT_R11        = 0
}RRC_TX_DIV_PUCCH1B_CH_SELECT_R11_ENUM;
typedef VOS_UINT8                 RRC_TX_DIV_PUCCH1B_CH_SELECT_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: ul-CoMP-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_UL_COMP_R11                         = 0
}RRC_UL_COMP_R11_ENUM;
typedef VOS_UINT8                 RRC_UL_COMP_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: multipleTimingAdvance-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP                                     = 0
}RRC_MULTIPLE_TIMING_ADVANCE_R11_ENUM;
typedef VOS_UINT8                 RRC_MULTIPLE_TIMING_ADVANCE_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: simultaneousRx-Tx-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_SIMUL_RX_TX_R11                     = 0
}RRC_SIMUL_RX_TX_R11_ENUM;
typedef VOS_UINT8                 RRC_SIMUL_RX_TX_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: supportedCSI-Proc-r11
* ȡֵ��Χ: ENUM(0..2)
*********************************************************************/
typedef enum
{
    RRC_N1_SUPP_CSI_PROC_R11                     = 0,
    RRC_N3_SUPP_CSI_PROC_R11                     = 1,
    RRC_N4_SUPP_CSI_PROC_R11                     = 2
}RRC_SUPP_CSI_PROC_R11_ENUM;
typedef VOS_UINT8                 RRC_SUPP_CSI_PROC_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: rsrqMeasWideband-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_RSRQ_MEAS_WIDEBAND_R11              = 0
}RRC_RSRQ_MEAS_WIDEBAND_R11_ENUM;
typedef VOS_UINT8                 RRC_RSRQ_MEAS_WIDEBAND_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: cdma2000-NW-Sharing-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_CDMA2000_NW_SHARING_R11             = 0
}RRC_CDMA2000_NW_SHARING_R11_ENUM;
typedef VOS_UINT8                 RRC_CDMA2000_NW_SHARING_R11_ENUM_UINT8;


/*********************************************************************
* ASN �ı�: inDeviceCoexInd-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_IN_DEVICE_COEX_IND_R11              = 0
}RRC_IN_DEVICE_COEX_IND_R11_ENUM;
typedef VOS_UINT8                 RRC_IN_DEVICE_COEX_IND_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: powerPrefInd-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_PWR_PREF_IND_R11                    = 0
}RRC_PWR_PREF_IND_R11_ENUM;
typedef VOS_UINT8                 RRC_PWR_PREF_IND_R11_ENUM_UINT8;

/*********************************************************************
* ASN �ı�: ue-Rx-TxTimeDiffMeasurements-r11
* ȡֵ��Χ: ENUM(0..0)
*********************************************************************/
typedef enum
{
    RRC_SUPP_UE_RX_TX_TIME_DIFF_MEAS_R11         = 0
}RRC_UE_RX_TX_TIME_DIFF_MEAS_R11_ENUM;
typedef VOS_UINT8                 RRC_UE_RX_TX_TIME_DIFF_MEAS_R11_ENUM_UINT8;

/* v7r2 LLD end */

/*****************************************************************************
   5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : RRC_NV_CSEL_CAND_FREQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ĳ����Ƶ�ʵ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqInfo;                             /* Ƶ��Ƶ�� */
    VOS_UINT16                          usCellCount;                            /* Ƶ���е�С��ID */
    VOS_UINT16                          ausCellIds[RRC_NV_CSEL_MAX_STORED_CELL_COUNT_PER_FREQ]; /* ��С���б� */
} RRC_NV_CSEL_CAND_FREQ_STRU;

/*****************************************************************************
 �ṹ��    : RRC_NV_CSEL_FREQ_BAND_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����Ƶ����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqBegin;                            /* ��ʼƵ�� */
    VOS_UINT16                          usFreqEnd;                              /* ����Ƶ�� */
} RRC_NV_CSEL_FREQ_BAND_INFO_STRU;
/* reportCGI stub begin */
/*****************************************************************************
 �ṹ��    : RRC_UU_MCC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCnt;    /*(0, 3)*/
    VOS_UINT8                           aucItem[3];
}RRC_UU_MCC_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UU_MNC_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCnt;    /*(0, 3)*/
    VOS_UINT8                           aucItem[3];
}RRC_UU_MNC_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UU_PLMN_ID_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    RRC_UU_MCC_STRU                     Mcc;                          /* optional */
    RRC_UU_MNC_STRU                     Mnc;
}RRC_UU_PLMN_ID_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UU_CGI_EUTRA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    RRC_UU_PLMN_ID_STRU                 PlmnId;
    VOS_UINT32                          ulCellId;
}RRC_UU_CGI_EUTRA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UU_PLMN_ID_LIST2_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С��CGI��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCnt;    /*(0, 1..RRC_UU_MAX_NUM_OF_PLMN_ID_LIST_2)*/
    RRC_UU_PLMN_ID_STRU                 aItem[RRC_UU_MAX_NUM_OF_PLMN_ID_LIST_2];
}RRC_UU_PLMN_ID_LIST2_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UU_CGI_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С��CGI��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    RRC_UU_CGI_EUTRA_STRU               CellGlobalId;
    VOS_UINT16                          usTrackingAreaCode;
    RRC_UU_PLMN_ID_LIST2_STRU           PlmnIdList;                   /* optional */
}RRC_UU_CGI_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_CMM_CGI_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С��CGI��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPhyCellId;
    VOS_UINT16                          usFreq;
    RRC_UU_CGI_INFO_STRU                stCGI;
}RRC_NV_CGI_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_CMM_USER_SET_CGI_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �û��ֶ����õ�С��CGI��Ϣ�б�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCnt;
    VOS_UINT8                           aucReserved[2];
    RRC_NV_CGI_INFO_STRU                astCgiInfo[RRC_NV_USER_SET_CGI_MAX_NUM];
}RRC_NV_USER_SET_CGI_LIST_STRU;

/*****************************************************************************
 �ṹ��    : RRC_CMM_AUTO_SRCH_CGI_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE�Զ������õ���С��CGI��Ϣ�б�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCnt;
    VOS_UINT8                           aucReserved[2];
    RRC_NV_CGI_INFO_STRU                astCgiInfo[RRC_NV_AUTO_SRCH_CGI_MAX_NUM];
}RRC_NV_AUTO_SRCH_CGI_LIST_STRU;

/*****************************************************************************
 �ṹ��    : RRC_CMM_CELL_CGI_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : С��CGI��Ϣ�б�ṹ
*****************************************************************************/
typedef struct
{
    RRC_NV_USER_SET_CGI_LIST_STRU      stUserSetCgiList;                       /* �û��ֶ����õ�CGI��Ϣ�б� */
    RRC_NV_AUTO_SRCH_CGI_LIST_STRU     stAutoSrchCgiList;                      /* UE�Զ���ȡ��CGI��Ϣ�б� */
}RRC_NV_CELL_CGI_LIST_STRU;
/* reportCGI stub end */

/*****************************************************************************
 �ṹ��    : RRC_NV_SIB_SUPPORT_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE֧�ֵ�ϵͳ��Ϣ��ṹ
*****************************************************************************/
typedef struct
{
    /* MBMS��begin */
    #if 0
    VOS_UINT8   aucSibn[12];
    #endif
    VOS_UINT8   aucSibn[16];
    /* MBMS��end */
}RRC_NV_SIB_SUPPORT_STRU;

/* UE�����ṹ���� */
/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_SUPP_ROH_CPROFILES_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������PDCP->ROHC����
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enProfile0x0001;
    PS_BOOL_ENUM_UINT8                  enProfile0x0002;
    PS_BOOL_ENUM_UINT8                  enProfile0x0003;
    PS_BOOL_ENUM_UINT8                  enProfile0x0004;
    PS_BOOL_ENUM_UINT8                  enProfile0x0006;
    PS_BOOL_ENUM_UINT8                  enProfile0x0101;
    PS_BOOL_ENUM_UINT8                  enProfile0x0102;
    PS_BOOL_ENUM_UINT8                  enProfile0x0103;
    PS_BOOL_ENUM_UINT8                  enProfile0x0104;
    VOS_UINT8                           aucReserved[3];
}RRC_UE_CAP_SUPP_ROH_CPROFILES_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_PDCP_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������PDCP����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[3];
    RRC_UE_CAP_ROH_CONTEXT_ENUM_UINT8   enMaxNumRohcContextSessions;
    RRC_UE_CAP_SUPP_ROH_CPROFILES_STRU  stPdcpSuppRohCprofiles;
} RRC_UE_CAP_PDCP_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_PDCP_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������PHY����
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enUeTxAntennaSelectionSupp;
    PS_BOOL_ENUM_UINT8                  enUeSpecRefSigsSupp;
    VOS_UINT8                           aucReserved[2];
} RRC_UE_CAP_PHY_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_SUPP_EUTRA_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������RF->Band����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEutraBand;
    PS_BOOL_ENUM_UINT8                  enHalfDuplex;
    VOS_UINT8                           aucReserved[2];
} RRC_UE_CAP_SUPP_EUTRA_BAND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_RF_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������RF����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[2];
    VOS_UINT16                          usCnt;
    RRC_UE_CAP_SUPP_EUTRA_BAND_STRU     astSuppEutraBandList[RRC_MAX_NUM_OF_BANDS];
} RRC_UE_CAP_RF_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_INTER_FREQ_EUTRA_BAND_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������MEAS->EutraInterFreqBand����
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enInterFreqNeedForGaps;
    VOS_UINT8                           aucReserved[3];
} RRC_INTER_FREQ_EUTRA_BAND_LIST_STRU;

/*****************************************************************************
 �ṹ��    : RRC_INTER_FREQ_EUTRA_BAND_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������MEAS->InterFreqBand����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[2];
    VOS_UINT16                          usCnt;
    RRC_INTER_FREQ_EUTRA_BAND_LIST_STRU astEutraInterFreqBandList[RRC_MAX_NUM_OF_BANDS];
} RRC_INTER_FREQ_EUTRA_BAND_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_INTER_RAT_BAND_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������MEAS->InterRatBand����
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enInterRatNeedForGaps;
    VOS_UINT8                           aucReserved[3];
} RRC_INTER_RAT_BAND_LIST_STRU;

/*****************************************************************************
 �ṹ��    : RRC_INTER_RAT_BAND_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������MEAS->InterRatBand����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[2];
    VOS_UINT16                          usCnt;
    RRC_INTER_RAT_BAND_LIST_STRU        astInterRatBandList[RRC_MAX_NUM_OF_BANDS];
} RRC_INTER_RAT_BAND_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_MEAS_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������MEAS����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[2];
    VOS_UINT16                          usCnt;
    VOS_UINT32                          aulUeCapMeasIdx[RRC_MAX_NUM_OF_BANDS];
} RRC_UE_CAP_MEAS_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_UTRA_FDD_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SupportedUTRA-FDD-BandListItem
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_UTRA_FDD_BAND_ENUM_UINT8 enUtraFddBand;
    VOS_UINT8                           aucReserved[3];
} RRC_UE_CAP_SUPP_UTRA_FDD_BAND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_UTRA_FDD_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������INTER RAT->UTRA FDD����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[2];
    VOS_UINT16                          usCnt;
    RRC_UE_CAP_SUPP_UTRA_FDD_BAND_STRU  astSuppUtraFddBandList[RRC_MAX_NUM_OF_BANDS];
} RRC_IRAT_UTRA_FDD_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_SUPP_UTRA_TDD128_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SupportedUTRA-TDD128BandListItem
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_UTRA_TDD128_BAND_ENUM_UINT8        enUtraTdd128Band;
    VOS_UINT8                                     aucReserved[3];
} RRC_UE_CAP_SUPP_UTRA_TDD128_BAND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_UTRA_TDD128_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SupportedUTRA-TDD128BandList
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                     aucReserved[2];
    VOS_UINT16                                    usCnt;
    RRC_UE_CAP_SUPP_UTRA_TDD128_BAND_STRU         astSuppUtraTdd128BandList[RRC_MAX_NUM_OF_BANDS];
} RRC_IRAT_UTRA_TDD128_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_SUPP_UTRA_TDD384_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SupportedUTRA-TDD384BandListItem
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_UTRA_TDD384_BAND_ENUM_UINT8        enUtraTdd384Band;
    VOS_UINT8                                     aucReserved[3];
} RRC_UE_CAP_SUPP_UTRA_TDD384_BAND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_UTRA_TDD384_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SupportedUTRA-TDD384BandList
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                     aucReserved[2];
    VOS_UINT16                                    usCnt;
    RRC_UE_CAP_SUPP_UTRA_TDD384_BAND_STRU         astSuppUtraTdd384BandList[RRC_MAX_NUM_OF_BANDS];
} RRC_IRAT_UTRA_TDD384_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_SUPP_UTRA_TDD768_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SupportedUTRA-TDD768BandListItem
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_UTRA_TDD768_BAND_ENUM_UINT8        enUtraTdd768Band;
    VOS_UINT8                                     aucReserved[3];
} RRC_UE_CAP_SUPP_UTRA_TDD768_BAND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_UTRA_TDD768_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SupportedUTRA-TDD768BandList
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                     aucReserved[2];
    VOS_UINT16                                    usCnt;
    RRC_UE_CAP_SUPP_UTRA_TDD768_BAND_STRU         astSuppUtraTdd768BandList[RRC_MAX_NUM_OF_BANDS];
} RRC_IRAT_UTRA_TDD768_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_SUPP_GERAN_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SupportedGERAN-BandListItem
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_GERAN_BAND_ENUM_UINT8    enGeranBand;
    VOS_UINT8                           aucReserved[3];
} RRC_UE_CAP_SUPP_GERAN_BAND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_GERAN_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IRAT-GERAN-Parameters
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucReserved;
    PS_BOOL_ENUM_UINT8                  enInterRatPsHoToGeran;
    VOS_UINT16                          usCnt;
    RRC_UE_CAP_SUPP_GERAN_BAND_STRU     astSuppGeranBandList[RRC_MAX_NUM_OF_BANDS];
} RRC_IRAT_GERAN_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_SUPP_HRPD_BAND_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SupportedHRPD-BandList
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved[2];
    VOS_UINT16                          usCnt;
    RRC_UE_CAP_CDMA2000_BANDCLASS_ENUM_UINT8      aenCdma2000HrpdBand[RRC_MAX_NUM_OF_CDMA_BAND_CLASS];
} RRC_UE_CAP_SUPP_HRPD_BAND_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_CDMA2000_HRPD_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IRAT-CDMA2000-HRPD-Parameters
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                     aucReserved[2];
    RRC_UE_CAP_CDMA2000_HRPD_TX_CONFIG_ENUM_UINT8 enCdma2000HrpdTxCfg;
    RRC_UE_CAP_CDMA2000_HRPD_RX_CONFIG_ENUM_UINT8 enCdma2000HrpdRxCfg;
    RRC_UE_CAP_SUPP_HRPD_BAND_INFO_STRU           stSuppHrpdBandList;
} RRC_IRAT_CDMA2000_HRPD_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_SUPP_1X_RTT_BAND_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Supported1xRTT-BandList
*****************************************************************************/
typedef struct
{
    VOS_UINT8                             aucReserved[2];
    VOS_UINT16                            usCnt;
    RRC_UE_CAP_CDMA2000_BANDCLASS_ENUM_UINT8      aenCdma20001xRttBand[RRC_MAX_NUM_OF_CDMA_BAND_CLASS];
} RRC_UE_CAP_SUPP_1X_RTT_BAND_INFO_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_CDMA2000_1X_RTT_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IRAT-CDMA2000-1xRTT-Parameters
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                           aucReserved[2];
    RRC_UE_CAP_CDMA2000_1X_RTT_TX_CONFIG_ENUM_UINT8     enCdma20001xRttTxCfg;
    RRC_UE_CAP_CDMA2000_1X_RTT_RX_CONFIG_ENUM_UINT8     enCdma20001xRttRxCfg;
    RRC_UE_CAP_SUPP_1X_RTT_BAND_INFO_STRU               stSupp1xRttBandList;
} RRC_IRAT_CDMA2000_1X_RTT_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_INTER_RAT_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������INTER RAT����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitCdma2000HrpdPresent     : 1;
    VOS_UINT32                          bitCdma20001xRttPresent    : 1;
    VOS_UINT32                          bitSpare                   : 30;

    RRC_IRAT_UTRA_FDD_PARA_STRU         stUtraFdd;
    RRC_IRAT_UTRA_TDD128_PARA_STRU      stUtraTdd128;
    RRC_IRAT_UTRA_TDD384_PARA_STRU      stUtraTdd384;
    RRC_IRAT_UTRA_TDD768_PARA_STRU      stUtraTdd768;
    RRC_IRAT_GERAN_PARA_STRU            stGeran;
    RRC_IRAT_CDMA2000_HRPD_PARA_STRU    stCdma2000Hrpd;
    RRC_IRAT_CDMA2000_1X_RTT_PARA_STRU  stCdma20001xRtt;
} RRC_UE_CAP_INTER_RAT_PARA_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_FEATURE_GROUP_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������������ָʾ��aucFeatureInd[]: 1��֧�֣�0����֧�֣�
             ����Ԫ��0ָʾGroup1,Ԫ��1ָʾGroup2,��������

*****************************************************************************/
typedef struct
{
    VOS_UINT8                     aucFeatureInd[RRC_MAX_NUM_OF_FEATURE_GROUP];
} RRC_UE_CAP_FEATURE_GROUP_IND_STRU;

/* v7r2 LLD begin */
/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_FEATURE_GROUP_IND_R9ADD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������������ָʾ��aucFeatureInd[]: 1��֧�֣�0����֧�֣�
             ����Ԫ��0ָʾGroup33,Ԫ��1ָʾGroup64,��������

*****************************************************************************/
typedef struct
{
    VOS_UINT8                     aucFeatureInd[RRC_MAX_NUM_OF_FEATURE_GROUP];
} RRC_UE_CAP_FEATURE_GROUP_IND_R9ADD_STRU;
/* v7r2 LLD end */

/*****************************************************************************
 �ṹ��    : RRC_PHY_LAYER_PARAM_V920_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PhyLayerParameters-v920
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enEnhncDualLayerFddR9;
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enEnhncDualLayerTddR9;
    VOS_UINT8                                     aucReserved[2];
}RRC_PHY_LAYER_PARAM_V920_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_PARAM_GERAN_V920_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IRAT-ParametersGERAN-v920
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enDtmR9;
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enEReDirGeranR9;
    VOS_UINT8                                     aucReserved[2];
}RRC_IRAT_PARAM_GERAN_V920_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_PARAM_UTRA_V920_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IRAT-ParametersUTRA-v920
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enEReDirUtraR9;
    VOS_UINT8                                     aucReserved[3];
}RRC_IRAT_PARAM_UTRA_V920_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_PARAM_CDMA2000_1XRTT_V920_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IRAT-ParametersCDMA2000-1XRTT-v920
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enECsfb1xrttR9;
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enECsfbConcPsMob1XrttR9;
    VOS_UINT8                                     aucReserved[2];
}RRC_IRAT_PARAM_CDMA2000_1XRTT_V920_STRU;

/*****************************************************************************
 �ṹ��    : RRC_CSG_PROXIMITY_IND_PARAM_R9_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSG-ProximityIndicationParameters-r9
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enIntraFreqProximityIndR9;
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enInterFreqProximityIndR9;
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enUtranProximityIndR9;
    VOS_UINT8                                     ucReserved;
}RRC_CSG_PROXIMITY_IND_PARAM_R9_STRU;

/*****************************************************************************
 �ṹ��    : RRC_NEIGH_CELL_SI_ACQ_PARAM_R9_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NeighCellSI-AcquisitionParameters-r9
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enIntraFreqSiAcqForHoR9;
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enInterFreqSiAcqForHoR9;
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enUtranSiAcqForHoR9;
    VOS_UINT8                                     ucReserved;
}RRC_NEIGH_CELL_SI_ACQ_PARAM_R9_STRU;

/*****************************************************************************
 �ṹ��    : RRC_SON_PARAM_R9_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SON-Parameters-r9
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8    enRachRprtR9;
    VOS_UINT8                                     aucReserved[3];
}RRC_SON_PARAM_R9_STRU;

/* v7r2 LLD begin */
/*****************************************************************************
 �ṹ��    : RRC_UE_EUTRA_CAP_ADD_XDD_MODE_R9_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE-EUTRA-CapabilityAddXDD-Mode-r9
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitPhyLayerParamR9Present                   : 1;
    VOS_UINT32    bitFeatureGroupIndicatorsR9Present          : 1;
    VOS_UINT32    bitFeatureGroupIndRel9AddR9Present          : 1;
    VOS_UINT32    bitInterRatParamGeranR9Present              : 1;
    VOS_UINT32    bitInterRatParamUtraR9Present               : 1;
    VOS_UINT32    bitInterRatParamCdma2000R9Present           : 1;
    VOS_UINT32    bitNeighCellSiAcqParamR9Present             : 1;
    VOS_UINT32    bitSpare                                    : 25;

    RRC_UE_CAP_PHY_PARA_STRU                    stPhyLayerParamR9;              /* optional */
    RRC_UE_CAP_FEATURE_GROUP_IND_STRU           stFeatureGroupIndicatorsR9;     /* optional */
    RRC_UE_CAP_FEATURE_GROUP_IND_R9ADD_STRU     stFeatureGroupIndRel9AddR9;     /* optional */
    RRC_IRAT_GERAN_PARA_STRU                    stInterRatParamGeranR9;         /* optional */
    RRC_IRAT_PARAM_UTRA_V920_STRU               stInterRatParamUtraR9;          /* optional */
    RRC_IRAT_PARAM_CDMA2000_1XRTT_V920_STRU     stInterRatParamCdma2000R9;      /* optional */
    RRC_NEIGH_CELL_SI_ACQ_PARAM_R9_STRU         stNeighCellSiAcqParamR9;        /* optional */
}RRC_UE_EUTRA_CAP_ADD_XDD_MODE_R9_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_EUTRA_CAP_V9A0_IES_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE-EUTRA-Capability-v9a0-IEs
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitFeatureGroupIndRel9AddR9Present          : 1;
    VOS_UINT32    bitFddAddUeEutraCapabilitiesR9Present       : 1;
    VOS_UINT32    bitTddAddUeEutraCapabilitiesR9Present       : 1;
    VOS_UINT32    bitSpare                                    : 29;

    RRC_UE_CAP_FEATURE_GROUP_IND_R9ADD_STRU     stFeatureGroupIndRel9AddR9;     /* optional */
    RRC_UE_EUTRA_CAP_ADD_XDD_MODE_R9_STRU       stFddAddUeEutraCapabilitiesR9;  /* optional */
    RRC_UE_EUTRA_CAP_ADD_XDD_MODE_R9_STRU       stTddAddUeEutraCapabilitiesR9;  /* optional */
}RRC_UE_EUTRA_CAP_V9A0_IES_STRU;

/*****************************************************************************
 �ṹ��    : RRC_NON_CONTI_UL_RA_WITHIN_CC_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NonContiguousUL-RA-WithinCC-r10
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   aucReserved[3];
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8  enNonContiguousUlRaWithinCcInfoR10;    /* optional */
}RRC_NON_CONTI_UL_RA_WITHIN_CC_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_NON_CONT_UL_RA_WITHIN_CC_LIST_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : NonContiguousUL-RA-WithinCC-List-r10
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usCnt;    /*(0, 1..RRC_MAX_NUM_OF_BANDS)*/
    VOS_UINT8                                   aucReserved[2];
    RRC_NON_CONTI_UL_RA_WITHIN_CC_R10_STRU      astItem[RRC_MAX_NUM_OF_BANDS];
}RRC_NON_CONT_UL_RA_WITHIN_CC_LIST_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_PHY_LAYER_PARAM_V1020_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PhyLayerParameters-v1020
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       aucReserved[2];

    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8      enTwoAntennaPortsForPucchR10;         /* optional */
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8      enTm9With8txFddR10;         /* optional */
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8      enPmiDisablingR10;          /* optional */
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8      enCrossCarrierSchdlR10;     /* optional */
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8      enSimulPucchPuschR10;       /* optional */
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8      enMultiClusterPuschWithinCcR10;        /* optional */
    RRC_NON_CONT_UL_RA_WITHIN_CC_LIST_R10_STRU      stNonContiguousUlRaWithinCcListR10;    /* optional */
}RRC_PHY_LAYER_PARAM_V1020_STRU;

/*****************************************************************************
 �ṹ��    : RRC_CA_MIMO_PARAM_UL_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CA-MIMO-ParametersUL-r10
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitSuppMimoCapUlR10Present                  : 1;
    VOS_UINT32    bitSpare                                    : 31;
    VOS_UINT8     aucReserved[2];

    RRC_CA_BANDWIDTH_CLASS_R10_ENUM_UINT8       enCaBwClassUlR10;
    RRC_MIMO_CAP_UL_R10_ENUM_UINT8              enSuppMimoCapUlR10;             /* optional */
}RRC_CA_MIMO_PARAM_UL_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_CA_MIMO_PARAM_DL_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CA-MIMO-ParametersDL-r10
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitSuppMimoCapDlR10Present                  : 1;
    VOS_UINT32    bitSpare                                    : 31;
    VOS_UINT8     aucReserved[2];

    RRC_CA_BANDWIDTH_CLASS_R10_ENUM_UINT8       enCaBwClassDlR10;
    RRC_MIMO_CAP_DL_R10_ENUM_UINT8              enSuppMimoCapDlR10;           /* optional */
}RRC_CA_MIMO_PARAM_DL_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_BAND_PARAM_UL_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BandParametersUL-r10
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usCnt;    /*(0, 1..UU_MAX_NUM_OF_BANDWIDTH_CLASS_R10)*/
    VOS_UINT8                                   aucReserved[2];
    RRC_CA_MIMO_PARAM_UL_R10_STRU               astItem[RRC_MAX_NUM_OF_BANDWIDTH_CLASS_R10];
}RRC_BAND_PARAM_UL_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_BAND_PARAM_DL_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BandParametersDL-r10
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usCnt;    /*(0, 1..UU_MAX_NUM_OF_BANDWIDTH_CLASS_R10)*/
    VOS_UINT8                                   aucReserved[2];
    RRC_CA_MIMO_PARAM_DL_R10_STRU               astItem[RRC_MAX_NUM_OF_BANDWIDTH_CLASS_R10];
}RRC_BAND_PARAM_DL_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_BAND_PARAM_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BandParameters-r10
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   aucReserved[3];
    VOS_UINT8                                   ucBandEutraR10;                 /*(1..64)*/
    RRC_BAND_PARAM_UL_R10_STRU                  stBandParamUlR10;               /* optional */
    RRC_BAND_PARAM_DL_R10_STRU                  stBandParamDlR10;               /* optional */
}RRC_BAND_PARAM_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_BAND_COMB_PARAM_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BandCombinationParameters-r10
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usCnt;    /*(0, 1..UU_MAX_NUM_OF_SIMULTANEOUS_BANDS_R10)*/
    VOS_UINT8                                   aucReserved[2];
    RRC_BAND_PARAM_R10_STRU                     astItem[RRC_MAX_NUM_OF_SIMULTANEOUS_BANDS_R10];
}RRC_BAND_COMB_PARAM_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_SUPP_BAND_COMB_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SupportedBandCombination-r10
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usCnt;    /*(0, 1..UU_MAX_NUM_OF_BAND_COMB_R10)*/
    VOS_UINT8                                   aucReserved[2];
    RRC_BAND_COMB_PARAM_R10_STRU                astItem[RRC_MAX_NUM_OF_BAND_COMB_R10];
}RRC_SUPP_BAND_COMB_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RF_PARAM_V1020_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF-Parameters-v1020
*****************************************************************************/
typedef struct
{
   RRC_SUPP_BAND_COMB_R10_STRU                  stSuppBandCombR10;
}RRC_RF_PARAM_V1020_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_MEAS_EUTRA_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������MEAS->Band����
*****************************************************************************/
typedef struct
{
    RRC_INTER_FREQ_EUTRA_BAND_INFO_STRU stInterFreqEutraBandInfo;
    RRC_INTER_RAT_BAND_INFO_STRU        stInterRatBandInfo;
}RRC_UE_CAP_MEAS_EUTRA_BAND_STRU;

/*****************************************************************************
 �ṹ��    : RRC_BAND_COMB_LIST_EUTRA_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : BandCombinationListEUTRA-r10
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                  usCnt;    /*(0, 1..UU_MAX_NUM_OF_BAND_COMB_R10)*/
    VOS_UINT8                                   aucReserved[2];
    RRC_UE_CAP_MEAS_EUTRA_BAND_STRU             astItem[RRC_MAX_NUM_OF_BAND_COMB_R10];
}RRC_BAND_COMB_LIST_EUTRA_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_MEAS_PARAM_V1020_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MeasParameters-v1020
*****************************************************************************/
typedef struct
{
   RRC_BAND_COMB_LIST_EUTRA_R10_STRU            stBandCombListEutraR10;
}RRC_MEAS_PARAM_V1020_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_BASED_NETW_PERF_MEAS_PARAM_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE-BasedNetwPerfMeasParameters-r10
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitLoggedMeasIdleR10Present                 : 1;
    VOS_UINT32    bitStandaloneGnssLocR10Present              : 1;
    VOS_UINT32    bitSpare                                    : 30;
}RRC_UE_BASED_NETW_PERF_MEAS_PARAM_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_IRAT_PARAM_UTRA_TDD_V1020_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : IRAT-ParametersUTRA-TDD-v1020
*****************************************************************************/
typedef struct
{
    RRC_UE_CAP_FEATURE_SUPPORT_FLAG_ENUM_UINT8  enEReDirUtraTddR10;
}RRC_IRAT_PARAM_UTRA_TDD_V1020_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_CAP_FEATURE_GROUP_IND_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE EUTRA������������ָʾ��aucFeatureIndR10[]: 1��֧�֣�0����֧�֣�
             ����Ԫ��0ָʾGroup1,Ԫ��1ָʾGroup2,��������

*****************************************************************************/
typedef struct
{
    VOS_UINT8                     aucFeatureIndR10[RRC_MAX_NUM_OF_FEATURE_GROUP];
} RRC_UE_CAP_FEATURE_GROUP_IND_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_EUTRA_CAP_ADD_XDD_MODE_V1060_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE-EUTRA-CapabilityAddXDD-Mode-v1060
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitPhyLayerParamV1060Present                : 1;
    VOS_UINT32    bitFeatureGroupIndRel10V1060Present         : 1;
    VOS_UINT32    bitInterRatParamCdma2000V1060Present        : 1;
    VOS_UINT32    bitInterRatParamUtraTddV1060Present         : 1;
    VOS_UINT32    bitSpare                                    : 28;

    RRC_PHY_LAYER_PARAM_V1020_STRU              stPhyLayerParamV1060;           /* optional */
    RRC_UE_CAP_FEATURE_GROUP_IND_R10_STRU       stFeatureGroupIndRel10V1060;    /* optional */
}RRC_UE_EUTRA_CAP_ADD_XDD_MODE_V1060_STRU;

/*****************************************************************************
 �ṹ��    : RRC_SUPP_BANDWIDTH_COMB_SET_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF-Parameters-v1060
*****************************************************************************/
typedef struct
{
    VOS_UINT16          usBitCnt;  /* 1..(8 * UU_MAX_NUM_OF_SUPPORT_BAND_WIDTH_COMB_SET_R10) ��Чbitλ*/
    VOS_UINT8           aucReserved[2];
    VOS_UINT8           aucItem[4];
}RRC_SUPP_BANDWIDTH_COMB_SET_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_BAND_COMB_PARAM_EXT_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF-Parameters-v1060
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitSuppBwCombSetR10Present                  : 1;
    VOS_UINT32    bitSpare                                    : 31;

    RRC_SUPP_BANDWIDTH_COMB_SET_R10_STRU stSuppBwCombSetR10;             /* optional */
}RRC_BAND_COMB_PARAM_EXT_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_SUPP_BAND_COMB_EXT_R10_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF-Parameters-v1060
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCnt;    /*(0, 1..UU_MAX_NUM_OF_SUPPORT_BAND_COMB_EXT_R10)*/
    VOS_UINT8                           ucReserved[2];
    RRC_BAND_COMB_PARAM_EXT_R10_STRU    aItem[RRC_MAX_NUM_OF_SUPPORT_BAND_COMB_EXT_R10];
}RRC_SUPP_BAND_COMB_EXT_R10_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RF_PARAM_V1060_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF-Parameters-v1060
*****************************************************************************/
typedef struct
{
    RRC_SUPP_BAND_COMB_EXT_R10_STRU      stSuppBandCombExtR10;
}RRC_RF_PARAM_V1060_STRU;

/*****************************************************************************
 �ṹ��    : RRC_RF_MEAS_PARAM_V1020_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RF-MEAS-Parameters-v1020
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usCnt;    /*(0, 1..UU_MAX_NUM_OF_BAND_COMB_R10)*/
    VOS_UINT8                           ucReserved[2];
    VOS_UINT32                          aulBandCombMeasGapParaIdx[RRC_MAX_NUM_OF_BAND_COMB_R10];
}RRC_RF_MEAS_PARAM_V1020_STRU;

typedef struct
{
    RRC_BAND_COMB_PARAM_R10_STRU        stBandCombParamR10;
    RRC_UE_CAP_MEAS_EUTRA_BAND_STRU     stUeCapMeasEutraBand;
}RRC_BAND_COMB_MEAS_GAP_PARAM_STRU;

/*********************************************************************
* ASN �ı� :PhyLayerParameters-v1130
*********************************************************************/
typedef struct
{
    VOS_UINT32    bitCrsInterfHandlR11Present                 : 1;
    VOS_UINT32    bitEpdcchR11Present                         : 1;
    VOS_UINT32    bitMultiAckCsiRprtingR11Present             : 1;
    VOS_UINT32    bitSsCchInterfHandlR11Present               : 1;
    VOS_UINT32    bitTddSpecialSubframeR11Present             : 1;
    VOS_UINT32    bitTxDivPucch1bChSelectR11Present           : 1;
    VOS_UINT32    bitUlCompR11Present                         : 1;
    VOS_UINT32    bitSpare                                    : 25;

    VOS_UINT8                            ucRev;
    RRC_CRS_INTERF_HANDL_R11_ENUM_UINT8  enCrsInterfHandlR11;          /* optional */
    RRC_EPDCCH_R11_ENUM_UINT8            enEpdcchR11;                  /* optional */
    RRC_MULTI_ACK_CSI_RPRTING_R11_ENUM_UINT8    enMultiAckCsiRprtingR11;    /* optional */
    RRC_SS_CCH_INTERF_HANDL_R11_ENUM_UINT8    enSsCchInterfHandlR11;   /* optional */
    RRC_TDD_SPECIAL_SUBFRAME_R11_ENUM_UINT8    enTddSpecialSubframeR11;    /* optional */
    RRC_TX_DIV_PUCCH1B_CH_SELECT_R11_ENUM_UINT8    enTxDivPucch1bChSelectR11;    /* optional */
    RRC_UL_COMP_R11_ENUM_UINT8           enUlCompR11;                  /* optional */
}RRC_PHY_LAYER_PARAM_V1130_STRU;

/*********************************************************************
�ṹ��    : RRC_PDCP_PARAM_V1130_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : RRC_PDCP_PARAM_V1130_STRU-IEs
*********************************************************************/
typedef struct
{
    VOS_UINT32    bitPdcpSnExtR11Present                      : 1;
    VOS_UINT32    bitSupportRohcContextContinueR11Present     : 1;
    VOS_UINT32    bitSpare                                    : 30;

    VOS_UINT8     ucRev[2];
    RRC_PDCP_SN_EXT_R11_ENUM_UINT8       enPdcpSnExtR11;               /* optional */
    RRC_SUPPORT_ROHC_CONTEXT_CONTINUE_R11_ENUM_UINT8    enSupportRohcContextContinueR11;    /* optional */
}RRC_PDCP_PARAM_V1130_STRU;

/*********************************************************************
* ASN �ı� :BandParameters-v1130
*********************************************************************/
typedef struct
{
    VOS_UINT8                            ucRev[3];
    RRC_SUPP_CSI_PROC_R11_ENUM_UINT8     enSuppCsiProcR11;
}RRC_BAND_PARAM_V1130_STRU;

typedef struct
{
    VOS_UINT8                            ucRev[2];
    VOS_UINT16                           usCnt;    /*(0, 1..UU_MAX_NUM_OF_SIMULTANEOUS_BANDS_R10)*/
    RRC_BAND_PARAM_V1130_STRU            aItem[RRC_MAX_NUM_OF_SIMULTANEOUS_BANDS_R10];
}RRC_BAND_PARAM_LIST_R11_STRU;

/*********************************************************************
* ASN �ı� :BandCombinationParameters-v1130
*********************************************************************/
typedef struct
{
    VOS_UINT32    bitMultipleTimingAdvanceR11Present          : 1;
    VOS_UINT32    bitSimulRxTxR11Present                      : 1;
    VOS_UINT32    bitSpare                                    : 30;

    VOS_UINT8                            ucRev[2];
    RRC_MULTIPLE_TIMING_ADVANCE_R11_ENUM_UINT8    enMultipleTimingAdvanceR11;    /* optional */
    RRC_SIMUL_RX_TX_R11_ENUM_UINT8       enSimulRxTxR11;               /* optional */
    RRC_BAND_PARAM_LIST_R11_STRU         BandParamListR11;             /* optional */
}RRC_BAND_COMB_PARAM_V1130_STRU;

/*********************************************************************
* ASN �ı� :SupportedBandCombination-v1130
*********************************************************************/
typedef struct
{
    VOS_UINT8                            ucRev[2];
    VOS_UINT16                           usCnt;    /*(0, 1..UU_MAX_NUM_OF_BAND_COMB_R10)*/
    RRC_BAND_COMB_PARAM_V1130_STRU       aItem[RRC_MAX_NUM_OF_BAND_COMB_R10];
}RRC_SUPP_BAND_COMB_V1130_STRU;

/*********************************************************************
�ṹ��    : RRC_RF_PARAM_V1130_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : RRC_RF_PARAM_V1130_STRU-IEs
*********************************************************************/
typedef struct
{
    RRC_SUPP_BAND_COMB_V1130_STRU        SuppBandCombV1130;            /* optional */
}RRC_RF_PARAM_V1130_STRU;

/*********************************************************************
�ṹ��    : RRC_MEAS_PARAM_V1130_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : RRC_MEAS_PARAM_V1130_STRU-IEs
*********************************************************************/
typedef struct
{
    VOS_UINT32    bitRsrqMeasWidebandR11Present               : 1;
    VOS_UINT32    bitSpare                                    : 31;

    VOS_UINT8                            ucRev[3];
    RRC_RSRQ_MEAS_WIDEBAND_R11_ENUM_UINT8    enRsrqMeasWidebandR11;    /* optional */
}RRC_MEAS_PARAM_V1130_STRU;


/*********************************************************************
�ṹ��    : RRC_IRAT_PARAM_CDMA2000_V1130_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : RRC_IRAT_PARAM_CDMA2000_V1130_STRU-IEs
*********************************************************************/
typedef struct
{
    VOS_UINT32    bitCdma2000NwSharingR11Present              : 1;
    VOS_UINT32    bitSpare                                    : 31;

    VOS_UINT8                            ucRev[3];
    RRC_CDMA2000_NW_SHARING_R11_ENUM_UINT8    enCdma2000NwSharingR11;  /* optional */
}RRC_IRAT_PARAM_CDMA2000_V1130_STRU;



/*********************************************************************
�ṹ��    : RRC_OTHER_PARAM_R11_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : RRC_OTHER_PARAM_R11_STRU-IEs
*********************************************************************/
typedef struct
{
    VOS_UINT32    bitInDeviceCoexIndR11Present                : 1;
    VOS_UINT32    bitPwrPrefIndR11Present                     : 1;
    VOS_UINT32    bitUeRxTxTimeDiffMeasR11Present             : 1;
    VOS_UINT32    bitSpare                                    : 29;

    VOS_UINT8                            ucRev;
    RRC_IN_DEVICE_COEX_IND_R11_ENUM_UINT8    enInDeviceCoexIndR11;     /* optional */
    RRC_PWR_PREF_IND_R11_ENUM_UINT8      enPwrPrefIndR11;              /* optional */
    RRC_UE_RX_TX_TIME_DIFF_MEAS_R11_ENUM_UINT8    enUeRxTxTimeDiffMeasR11;    /* optional */
}RRC_OTHER_PARAM_R11_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_EUTRA_CAP_V1130_IES_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE-EUTRA-Capability-v1130-IEs
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitPhyLayerParamV1130Present                : 1;
    VOS_UINT32    bitSpare                                    : 31;

    RRC_PDCP_PARAM_V1130_STRU            PdcpParamV1130;
    RRC_PHY_LAYER_PARAM_V1130_STRU       PhyLayerParamV1130;           /* optional */
    RRC_RF_PARAM_V1130_STRU              RfParamV1130;
    RRC_MEAS_PARAM_V1130_STRU            MeasParamV1130;
    RRC_IRAT_PARAM_CDMA2000_V1130_STRU   InterRatParamCdma2000V1130;
    RRC_OTHER_PARAM_R11_STRU             OtherParamR11;
}RRC_UE_EUTRA_CAP_V1130_IES_STRU;

typedef VOS_UINT16           RRC_FREQ_BAND_IND_V9E0_UINT16;

/*********************************************************************
�ṹ��    : RRC_BAND_PARAM_V1090_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : RRC_BAND_PARAM_V1090_STRU-IEs
*********************************************************************/
typedef struct
{
    VOS_UINT32    bitBandEutraV1090Present                    : 1;
    VOS_UINT32    bitSpare                                    : 31;

    VOS_UINT8                            ucRev[2];
    RRC_FREQ_BAND_IND_V9E0_UINT16        usBandEutraV1090;             /* optional */
}RRC_BAND_PARAM_V1090_STRU;

/*********************************************************************
�ṹ��    : RRC_BAND_COMB_PARAM_V1090_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : RRC_BAND_COMB_PARAM_V1090_STRU-IEs
*********************************************************************/
typedef struct
{
    VOS_UINT8                            ucRev[2];
    VOS_UINT16                           usCnt;    /*(0, 1..RRC_MAX_NUM_OF_SIMULTANEOUS_BANDS_R10)*/
    RRC_BAND_PARAM_V1090_STRU            aItem[RRC_MAX_NUM_OF_SIMULTANEOUS_BANDS_R10];
}RRC_BAND_COMB_PARAM_V1090_STRU;

/*********************************************************************
�ṹ��    : RRC_SUPP_BAND_COMB_V1090_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : RRC_SUPP_BAND_COMB_V1090_STRU-IEs
*********************************************************************/
typedef struct
{
    VOS_UINT8                            ucRev[2];
    VOS_UINT16                           usCnt;    /*(0, 1..RRC_MAX_NUM_OF_BAND_COMB_R10)*/
    RRC_BAND_COMB_PARAM_V1090_STRU       aItem[RRC_MAX_NUM_OF_BAND_COMB_R10];
}RRC_SUPP_BAND_COMB_V1090_STRU;

/*********************************************************************
�ṹ��    : RRC_RF_PARAM_V1090_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : RRC_RF_PARAM_V1090_STRU-IEs
*********************************************************************/
typedef struct
{
    RRC_SUPP_BAND_COMB_V1090_STRU        SuppBandCombV1090;            /* optional */
}RRC_RF_PARAM_V1090_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_EUTRA_CAP_V1090_IES_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE-EUTRA-Capability-v1090-IEs
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitRfParamV1090Present                      : 1;
    VOS_UINT32    bitNonCritiExtPresent                       : 1;
    VOS_UINT32    bitSpare                                    : 30;

    RRC_RF_PARAM_V1090_STRU              RfParamV1090;                 /* optional */

}RRC_UE_EUTRA_CAP_V1090_IES_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_EUTRA_CAP_V1060_IES_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE-EUTRA-Capability-v1060-IEs
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitFddAddUeEutraCapabilitiesV1060Present    : 1;
    VOS_UINT32    bitTddAddUeEutraCapabilitiesV1060Present    : 1;
    VOS_UINT32    bitRfParamV1060Present                      : 1;
    VOS_UINT32    bitNonCritiExtPresent                       : 1;
    VOS_UINT32    bitSpare                                    : 28;

    RRC_UE_EUTRA_CAP_ADD_XDD_MODE_V1060_STRU    stFddAddUeEutraCapabilitiesV1060;    /* optional */
    RRC_UE_EUTRA_CAP_ADD_XDD_MODE_V1060_STRU    stTddAddUeEutraCapabilitiesV1060;    /* optional */
    /* R10 NV�޸� begin*/
    //RRC_RF_PARAM_V1060_STRU                     stRfParamV1060;                 /* optional */
    /* R10 NV�޸� end*/
}RRC_UE_EUTRA_CAP_V1060_IES_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_EUTRA_CAP_V1020_IES_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE-EUTRA-Capability-v1020-IEs
*****************************************************************************/
typedef struct
{
    /* R10 NV �޸� begin */
    VOS_UINT32    bitUeCatgV1020Present                       : 1;
    VOS_UINT32    bitPhyLayerParamV1020Present                : 1;
    //VOS_UINT32    bitRfParamV1020Present                      : 1;
    //VOS_UINT32    bitMeasParamV1020Present                    : 1;
    VOS_UINT32    bitRfMeasParamV1020Present                  : 1;
    VOS_UINT32    bitFeatureGroupIndRel10R10Present           : 1;
    VOS_UINT32    bitInterRatParamCdma2000V1020Present        : 1;
    VOS_UINT32    bitUeBasedNetwPerfMeasParamR10Present       : 1;
    VOS_UINT32    bitInterRatParamUtraTddV1020Present         : 1;
    VOS_UINT32    bitNonCritiExtPresent                       : 1;
    VOS_UINT32    bitSpare                                    : 24;
    VOS_UINT8     aucReserved[3];

    VOS_UINT8                                   ucUeCatgV1020;                  /* optional */    /*(6..8)*/
    RRC_PHY_LAYER_PARAM_V1020_STRU              stPhyLayerParamV1020;           /* optional */

    //RRC_RF_PARAM_V1020_STRU                   stRfParamV1020;                 /* optional */
    //RRC_MEAS_PARAM_V1020_STRU                 stMeasParamV1020;               /* optional */
    RRC_UE_CAP_FEATURE_GROUP_IND_R10_STRU       stFeatureGroupIndRel10R10;      /* optional */
    RRC_UE_BASED_NETW_PERF_MEAS_PARAM_R10_STRU  stUeBasedNetwPerfMeasParamR10;  /* optional */
    //RRC_UE_EUTRA_CAP_V1060_IES_STRU           stNonCritiExt;
    RRC_RF_MEAS_PARAM_V1020_STRU                stRfMeasParamV1020;
    /* optional */
    /* R10 NV �޸� end */

}RRC_UE_EUTRA_CAP_V1020_IES_STRU;

/*****************************************************************************
 �ṹ��    : RRC_UE_EUTRA_CAP_V940_IES_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE-EUTRA-Capability-v940-IEs
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitUeEutraCapV9a0Present                    : 1;
    VOS_UINT32    bitUeEutraCapV1020Present                   : 1;
    VOS_UINT32    bitSpare                                    : 30;

    /*R10 NV begin*/
    //RRC_UE_EUTRA_CAP_V9A0_IES_STRU              stUeEutraCapV9a0;               /* optional */
    //RRC_UE_EUTRA_CAP_V1020_IES_STRU             stUeEutraCapV1020;              /* optional */
    /*R10 NV end*/
}RRC_UE_EUTRA_CAP_V940_IES_STRU;
/* v7r2 LLD end */

/*****************************************************************************
 �ṹ��    : RRC_UE_EUTRA_CAP_V920_IES_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : UE-EUTRA-Capability-v920-IEs
*****************************************************************************/
typedef struct
{
    VOS_UINT32    bitInterRatParamUtraV920Present             : 1;
    VOS_UINT32    bitInterRatParamCdma2000V920Present         : 1;
    /* v7r2 LLD begin */
    VOS_UINT32    bitUeEutraCapV940Present                    : 1;
    VOS_UINT32    bitSpare                                    : 29;
    #if 0
    VOS_UINT32    bitSpare                                    : 30;
    #endif
    /* v7r2 LLD end */

    RRC_PHY_LAYER_PARAM_V920_STRU               stPhyLayerParamV920;
    RRC_IRAT_PARAM_GERAN_V920_STRU              stInterRatParamGeranV920;
    RRC_IRAT_PARAM_UTRA_V920_STRU               stInterRatParamUtraV920;        /* optional */
    RRC_IRAT_PARAM_CDMA2000_1XRTT_V920_STRU     stInterRatParamCdma2000V920;    /* optional */
    RRC_UE_CAP_DEVICE_TYPE_R9_ENUM_UINT8        enDeviceTypeR9;
    VOS_UINT8                                   aucReserved[3];
    RRC_CSG_PROXIMITY_IND_PARAM_R9_STRU         stCsgProximityIndParamR9;
    RRC_NEIGH_CELL_SI_ACQ_PARAM_R9_STRU         stNeighCellSiAcqParamR9;
    RRC_SON_PARAM_R9_STRU                       stSonParamR9;
    /* v7r2 LLD begin */
    RRC_UE_EUTRA_CAP_V940_IES_STRU              stUeEutraCapV940;               /* optional */
    /* v7r2 LLD end */
}RRC_UE_EUTRA_CAP_V920_IES_STRU;

/* add by lishangfeng for NorStandard begin */
/*****************************************************************************
 �ṹ��    : LTE_NON_STANDARD_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �Ǳ�Ƶ�ε�Ƶ����Ϣ��ص����ݽṹ,��36101 talbe 5.7.3-1��Ӧ

            RealFreq = usFLow + (RealArfcn - usRangOfNLow),
            ���� RealFreq ��ʵ��Ƶ����Ϣ��usRangOfNLow��usFLow��NV���л�ȡ�����庬��
            �����ݽṹ�е�˵��; RealArfcnʵ�ʵ�arfcn��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                usFLow;                           /* ��ʼƵ�㣬��λ��100khz */
    VOS_UINT16                                usFHigh;                          /* ����Ƶ�㣬��λ��100khz */
    VOS_UINT16                                usRangOfNLow;                     /* Nlow,��Noffsetһ�� */
    VOS_UINT16                                usRangOfNHigh;                    /* Nhigh*/
}LTE_COMM_NON_STANDARD_FREQ_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_NON_STANDARD_POWER_CLASS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �Ǳ�Ƶ��power class��ص����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                 usUEPowerClass;
    VOS_INT16                                  sPowerToleranceHigh;    /* ��λ 0.1dBm */
    VOS_INT16                                  sPowerToleranceLow;     /* ��λ 0.1dBm */
    VOS_UINT8                                  aucReservered[2];
}LTE_COMM_NON_STANDARD_POWER_CLASS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_NON_STANDARD_BAND_TEST_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �Ǳ�Ƶ�εĲ�����Ϣ��ص����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucBandWidth;                       /* ������λ0.1MHz����ѡֵ14;30;50;150;200 */
    VOS_UINT8                                   aucReservered[3];
    VOS_UINT16                                  usTestFreqs[3];                    /* ���Ե͡��С���Ƶ�㣬��λ0.1MHz */
    VOS_INT16					                sRxRefSensPower;                   /* ���в��������ȹ��ʣ���λ0.1dBm */
    VOS_UINT32                                  aulReservered[16];
}LTE_NON_STANDARD_BAND_TEST_INFO_STRU;

/*****************************************************************************
 �ṹ��    : LTE_NON_STANDARD_BAND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �Ǳ�Ƶ�ε�Ƶ����Ϣ��ص����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucBandID;                       /* band iD */
    LTE_COMM_BAND_MODE_TYPE_ENUM_UINT8          enBandMode;
    VOS_INT16                                   sTxRxFreqSepara;
    LTE_COMM_NON_STANDARD_FREQ_INFO_STRU        stUlFreqInfo;
    LTE_COMM_NON_STANDARD_FREQ_INFO_STRU        stDlFreqInfo;
    LTE_COMM_NON_STANDARD_POWER_CLASS_INFO_STRU stUePowerClassInfo;
    LTE_NON_STANDARD_BAND_TEST_INFO_STRU		stTestInfo[6];                 /*1.4MHz��3MHz��5MHz,10MHz,15MHz��20MHz����Ĳ��Բ��� */
    VOS_UINT32                                  aulReservered[16];
}LTE_COMM_NON_STANDARD_BAND_COMM_STRU;

/* add by lishangfeng for NorStandard end */

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

#endif /* end of RrcNvInterface.h */
