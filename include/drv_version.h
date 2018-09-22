


#ifndef __DRV_VERSION_H__
#define __DRV_VERSION_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "drv_comm.h"
#include "mbb_config.h"

/*************************VERSION START*****************************************
����:
Ӳ���汾����32bit��ʾ�����дӸߵ��ͣ���һ���ֽ�
��ʾ�Ƿ�ΪUDP����Ϊ0��ʾΪ��UDP��0��ʾΪUDP������
�����ֽڷֱ���HKADC��������UDP����ڶ����ֽڱ�ʾ
��Ʒ����(0:E5,1:stick,2:Phone,3:pad,4:cpe,5:mod,6~9:resv),
���������ֽ�Ϊ��С�汾�ţ�UDPP�����
�������ֽ����ڱ�ʶ��Ƶ�۰�汾�š�

ע��:
V9R1�У�Ӳ���汾��Ϊint���ͣ�Ϊ���䣬�����bitλ����Ϊ0;
Porting��\P531����\SFT ��HKADC�汾��Ϊ����趨
********************************************************************************/
#if (FEATURE_ON == MBB_COMMON)
typedef enum tagProductType
{
    PRODUCT_TYPE_STICK = 0,
    PRODUCT_TYPE_MOD,
    PRODUCT_TYPE_E5,
    PRODUCT_TYPE_CPE,
    PRODUCT_TYPE_HILINK,
    PRODUCT_TYPE_WINGLE,
}eProductType;
#else
typedef enum tagProductType
{
    PRODUCT_TYPE_STICK = 0,
    PRODUCT_TYPE_MOD,
    PRODUCT_TYPE_E5,
    PRODUCT_TYPE_CPE,
    PRODUCT_TYPE_PAD,
    PRODUCT_TYPE_PHONE
}eProductType;
#endif

typedef enum{
     BOARD_TYPE_BBIT        = 0,
     BOARD_TYPE_SFT,
     BOARD_TYPE_ASIC,
     BOARD_TYPE_MAX
}BOARD_ACTUAL_TYPE_E;

#define HW_VER_PRODUCT_TYPE_MASK	(BSP_U32)0x00FF0000
#define HW_VER_PRODUCT_TYPE_OS		16

/* Ӳ����Ʒ��Ϣ���� */
#define HW_VER_INVALID              (BSP_U32)0X7FFFFFFF

/* Porting��*/
#define HW_VER_PRODUCT_PORTING      (BSP_U32)0X00FFFFFE

/*P531 fpga����*/
#define HW_VER_PRODUCT_P531_FPGA	(BSP_U32)0X00FFFFFD

/* SFT */
#define HW_VER_PRODUCT_SFT	        (BSP_U32)0x00FFFFFC

/*p531 asic va*/
#define HW_VER_PRODUCT_P531_ASIC_VA (BSP_U32)0X00FFFFFB

/*p531 asic vc*/
#define HW_VER_PRODUCT_P531_ASIC_VC (BSP_U32)0X00FFFFFA

/*DCM E5*/
#define HW_VER_PRODUCT_E5379		(BSP_U32)0X00000001

/* ͨ��E5��Ӳ���汾�Ŷ��� */
/* �׿�E5��Ϊͨ��E5��E5573S-606���汾�Ŵ��� */
#define HW_VER_PRODUCT_E5       (BSP_U32)0X00000003

/*����E5573s-320֧��*/
#define HW_VER_PRODUCT_E5573S_320       (BSP_U32)0X00000006

/*����E5573s-607֧��*/
#define HW_VER_PRODUCT_E5573S_607       (BSP_U32)0X00000306

/*����E5573s-210֧��*/
#define HW_VER_PRODUCT_E5575S_210       (BSP_U32)0X00000400

/*����E5573s-210 VerB֧��*/
#define HW_VER_PRODUCT_E5575S_210_VB    (BSP_U32)0X00000401

/*����E5575s-320֧��*/
#define HW_VER_PRODUCT_E5575S_320       (BSP_U32)0X00000707

/*����E8378ws_210֧��*/
#define HW_VER_PRODUCT_E8378WS_210       (BSP_U32)0X00010200

/*���� Vodafone R216֧��*/
#define HW_VER_PRODUCT_R216       (BSP_U32)0X00000403

/*���� Vodafone R216h֧��*/
#define HW_VER_PRODUCT_R216h       (BSP_U32)0X00000706

/*����E5577s-321֧��*/
#define HW_VER_PRODUCT_E5577S_321       (BSP_U32)0X00000203

/*����E5577s-324֧��*/
#define HW_VER_PRODUCT_E5577S_324       (BSP_U32)0X00000309

/*����E5577s-932֧��*/
#define HW_VER_PRODUCT_E5577S_932       (BSP_U32)0X00000303

/*����E5577Bs-932֧��*/
#define HW_VER_PRODUCT_E5577BS_932       (BSP_U32)0X00000903

/*����E5577Cs-321֧��*/
#define HW_VER_PRODUCT_E5577CS_321      (BSP_U32)0X00000500

/*����E5577Ds-156֧��*/
#define HW_VER_PRODUCT_E5577DS_156      (BSP_U32)0X00000904


/*����E5573s-156֧��*/
#define HW_VER_PRODUCT_E5573S_156       (BSP_U32)0X00000206

/*����E5573s-856֧��*/
#define HW_VER_PRODUCT_E5573S_856       (BSP_U32)0X00000506

/*����E5573Cs-603֧��*/
#define HW_VER_PRODUCT_E5577CS_603       (BSP_U32)0X00000700

/*����E5573s-603֧��*/
#define HW_VER_PRODUCT_E5577S_603       (BSP_U32)0X00000703

/*����E5573s-853֧��*/
#define HW_VER_PRODUCT_E5573S_853       (BSP_U32)0X00000406

/*����E5573s-852֧��*/
#define HW_VER_PRODUCT_E5573S_852       (BSP_U32)0X00000600

/*����E5573s-508֧��*/
#define HW_VER_PRODUCT_E5573S_508       (BSP_U32)0X00000300

#define HW_VER_PRODUCT_E5578S_932       (BSP_U32)0X00000000
#define HW_VER_PRODUCT_401HW            (BSP_U32)0X00000200

/*����506HW֧��*/
#define HW_VER_PRODUCT_506HW            (BSP_U32)0X00000805

/*����506HW-2֧��*/
#define HW_VER_PRODUCT_506HW_2            (BSP_U32)0X00000808

/*E5770s-923Ӳ���汾�Ŷ���*/
#define HW_VER_PRODUCT_E5770S_923       (BSP_U32)0X00000100


/*E5770s-320Ӳ���汾�Ŷ���*/
#define HW_VER_PRODUCT_E5770S_320       (BSP_U32)0X00000106

/*����E5573s-806֧��*/
#define HW_VER_PRODUCT_E5573S_806       (BSP_U32)0X00000606

/*����E5573Bs-320֧��*/
#define HW_VER_PRODUCT_E5573Bs_320      (BSP_U32)0X00000503
#define HW_VER_PRODUCT_E5771S_852      (BSP_U32)0X00000603

/*����E5771s-856֧��*/
#define HW_VER_PRODUCT_E5771S_856       (BSP_U32)0X00000806

/*E5771h-937Ӳ���汾�Ŷ���*/
#define HW_VER_PRODUCT_E5771H_937      (BSP_U32)0X00000803
/* ����K5160֧�� */
#define HW_VER_PRODUCT_K5160            (BSP_U32)0X00010800

/*����E5573Cs-609֧��*/
#define HW_VER_PRODUCT_E5573CS_609       (BSP_U32)0X00000804

/*����E5573Cs-322֧��*/
#define HW_VER_PRODUCT_E5573CS_322       (BSP_U32)0X00000900

/*����E5573Bs-322֧��*/
#define HW_VER_PRODUCT_E5573BS_322       (BSP_U32)0X00000409
/*����E5573Cs-931֧��*/
#define HW_VER_PRODUCT_E5573CS_931       (BSP_U32)0X00000901

/*����E5673s-609֧��*/
#define HW_VER_PRODUCT_E5673S_609       (BSP_U32)0X00000902

/*����E5573Cs-609֧��*/
#define HW_VER_PRODUCT_E5573CS_609_B       (BSP_U32)0X00000905

/*����E5573Cs-322֧��*/
#define HW_VER_PRODUCT_E5573CS_322_B       (BSP_U32)0X00000906

/*����E5573Cs-931֧��*/
#define HW_VER_PRODUCT_E5573CS_931_B       (BSP_U32)0X00000907

/*����E5673s-609֧��*/
#define HW_VER_PRODUCT_E5673S_609_B       (BSP_U32)0X00000908

/*����E5573Cs-323֧��*/
#define HW_VER_PRODUCT_E5573CS_323_B       (BSP_U32)0X00000807

/*����E5573Cs-933֧��*/
#define HW_VER_PRODUCT_E5573CS_933       (BSP_U32)0X00000109
/*����E5573Cs-509֧��*/
#define HW_VER_PRODUCT_E5573CS_509       (BSP_U32)0X00000009
/*����E5577Bs-937֧��*/
#define HW_VER_PRODUCT_E5577BS_937       (BSP_U32)0X00000209

/*����607Hw֧��*/
#define HW_VER_PRODUCT_607HW             (BSP_U32)0X00000509

/*����R218h֧��*/
#define HW_VER_PRODUCT_R218h             (BSP_U32)0X00000709

/*����MS2372h-153֧��*/
#define HW_VER_PRODUCT_MS2372H_153             (BSP_U32)0X00010108

/* CPE��Ӳ���汾�Ŷ��� */
#define HW_VER_PRODUCT_CPE       (BSP_U32)0X00040000

#define HW_VER_PRODUCT_B310s_927        (BSP_U32)0X00040000
#define HW_VER_PRODUCT_B310s_518        (BSP_U32)0X00040001
#define HW_VER_PRODUCT_B310As_852       (BSP_U32)0X00040002
#define HW_VER_PRODUCT_B315s_22         (BSP_U32)0X00040003

/* ʹ��hisi����Ƶ���� */
#define HW_VER_PRODUCT_B310s_927_HISI        (BSP_U32)0X00080000
#define HW_VER_PRODUCT_B310s_518_HISI        (BSP_U32)0X00080001
#define HW_VER_PRODUCT_B310As_852_HISI       (BSP_U32)0X00080002
#define HW_VER_PRODUCT_B315s_22_HISI         (BSP_U32)0X00080003

/* STICK��Ӳ���汾�Ŷ��� */
#define HW_VER_PRODUCT_STICK       (BSP_U32)0X00010100
/*E3372h-510*/
#define HW_VER_PRODUCT_E3372H_510  (BSP_U32)0X00010101
/*E3372h-510 VER B*/
#define HW_VER_PRODUCT_E3372H_510_B  (BSP_U32)0X00010107
/*E3372h-210*/
#define HW_VER_PRODUCT_E3372H_210  (BSP_U32)0X00010102
/*E3372h-607*/
#define HW_VER_PRODUCT_E3372H_607  (BSP_U32)0X00010103
/*MS2372h-517*/
#define HW_VER_PRODUCT_MS2372h_517  (BSP_U32)0X00010206
/*MS2372h-607*/
#define HW_VER_PRODUCT_MS2372h_607  (BSP_U32)0X00010207

/* WINGLE��Ӳ���汾�Ŷ��� */
#define HW_VER_PRODUCT_WINGLE       (BSP_U32)0X00010000
/*E8372H-510*/
#define HW_VER_PRODUCT_E8372H_510   (BSP_U32)0X00010002
/*E8372H-927*/
#define HW_VER_PRODUCT_E8372H_927   (BSP_U32)0X00010003
/*E8372H-511*/
#define HW_VER_PRODUCT_E8372H_511   (BSP_U32)0X00010005
/*E8372H-517*/
#define HW_VER_PRODUCT_E8372H_517   (BSP_U32)0X00010007

/*E8372h-153Ӳ���汾�Ŷ���*/
#define HW_VER_PRODUCT_E8372H_153       (BSP_U32)0X00010001
/*E8372H-607*/
#define HW_VER_PRODUCT_E8372H_607   (BSP_U32)0X00010006
/*E8372h-153Ӳ���汾�Ŷ���*/
#define HW_VER_PRODUCT_MS2172S_818   (BSP_U32)0X00010203
/*E8372h-155Ӳ���汾�Ŷ���*/
#define HW_VER_PRODUCT_E8372h_155   (BSP_U32)0X00010009


/*���԰�*/
#define HW_VER_PRODUCT_UDP			(BSP_U32)0X7FFFFFFB
#define HW_VER_UDP_MASK				(BSP_U32)0X7F000000
#define HW_VER_UN_UDP_MASK			(BSP_U32)0X00FFFFFF

/* RF �۰� */
#define HW_VER_PRODUCT_UDP_RF_HI6361EVB5_VER_D_RF_T	(BSP_U32)0X7F000100/*���Ϊ1j, wangjiaan �ṩ*/
#define HW_VER_PRODUCT_UDP_RF_HIBV7R2RF6_VB			(BSP_U32)0X7F000908/*�����,wangjiaan �ṩ*/
#define HW_VER_PRODUCT_UDP_RF_HI4511RFU1_VER_A		(BSP_U32)0X7F000907/*K3V3RFU1 ,yuanshutian*/
#define HW_VER_PRODUCT_UDP_RF_HIBV7R2RF4_VB			(BSP_U32)0X7F000906/*���Ϊ2c, wangjiaan �ṩ*/
#define HW_VER_PRODUCT_UDP_RF_HIBV7R2RF5_VA_RF1		(BSP_U32)0X7F000905/*�����,wangjiaan �ṩ*/
#define HW_VER_PRODUCT_UDP_RF_HIBV7R2RF7B			(BSP_U32)0X7F000608/*yueminjie �ṩ68*/
#define HW_VER_PRODUCT_UDP_RF_K3V3RFU2_TI_VER_A		(BSP_U32)0X7F000605/*K3V3RFU2_VA(TI),yuanshutian*/
#define HW_VER_PRODUCT_UDP_RF_HIBV7R2RF7			(BSP_U32)0X7F000604/*���Ϊ2m,wangjiaan �ṩ58*/
#define HW_VER_PRODUCT_UDP_RF_K3V3RFU2_RFMD_VER_A	(BSP_U32)0X7F000602/*K3V3RFU2_VA(RFMD),yuanshutian*/
#define HW_VER_PRODUCT_UDP_RF_HL1EMULTR_VER_A		(BSP_U32)0X7F000507/*�����,yuanshutian �ṩ*/
#define HW_VER_PRODUCT_UDP_RF_HIBV7R2RF5_VA_RF		(BSP_U32)0X7F000505/*�����,wangjiaan �ṩ*/
#define HW_VER_PRODUCT_UDP_RF_HIBV7R2RF5_VA_RF2		(BSP_U32)0X7F000504/*�����,wangjiaan �ṩ*/
#define HW_VER_PRODUCT_UDP_RF_HIBV7R2DCM2_VB		(BSP_U32)0X7F000501/*���Ϊ2e, wangjiaan �ṩ61*/
#define HW_VER_PRODUCT_UDP_RF_HI6361SEVB5_VER_D_RF_T		(BSP_U32)0X7F000702/*ʹ��EVB5�۰�ͨ���ĵ�����Ϊ72, ����������*/

/*K3V3_FPGA*/
#define HW_VER_K3V3_FPGA			(BSP_U32)0X33333333
#define HW_VER_K3V3_FPGA_MASK		(BSP_U32)0X33000000
#define HW_VER_K3V3_FPGA_UN_MASK	(BSP_U32)0X00FFFFFF

/*K3V3 UDP*/
#define HW_VER_K3V3_UDP				(BSP_U32)0X3FFFFFFB
#define HW_VER_K3V3_UDP_MASK        (BSP_U32)0X3F000000
#define HW_VER_K3V3_UN_UDP_MASK     (BSP_U32)0X00FFFFFF

/*V711 UDP*/
#define HW_VER_V711_UDP				(BSP_U32)0X71FFFFFB
#define HW_VER_V711_UDP_MASK        (BSP_U32)0X71000000
#define HW_VER_V711_UN_UDP_MASK     (BSP_U32)0X00FFFFFF
/* RF �۰� */
#define HW_VER_V711_UDP_RF_HI6361EVB6_VER_D_RF_T	(BSP_U32)0X71000104/*���Ϊ1j, wangjiaan �ṩ*/

/*K3V3 RF �۰� */
#define HW_VER_K3V3_UDP_RF_HI6361EVB5_VER_D_RF_T	(BSP_U32)0X3F000100/*���Ϊ1j, wangjiaan �ṩ*/
#define HW_VER_K3V3_UDP_RF_HI6361EVB5_VER_D_RF_T_B	(BSP_U32)0X3F000606/*���Ϊ1j, wangjiaan �ṩ*/
#define HW_VER_K3V3_RF_HIBV7R2RF7					(BSP_U32)0X3F000604/*���Ϊ2m,wangjiaan �ṩ58*/
#define HW_VER_K3V3__UDP_RF_K3V3RFU2_RFMD_VER_A		(BSP_U32)0X3F000602/*K3V3RFU2_VA(RFMD),yuanshutian*/

/*оƬ�汾��*/
#define CHIP_VER_HI6950_ASIC    (BSP_U32)0X69500100
#define CHIP_VER_HI6930_ASIC    (BSP_U32)0X69300100
#define CHIP_VER_HI6921_ASIC    (BSP_U32)0X69210100
#define CHIP_VER_HI3630_ASIC    (BSP_U32)0X36300100
#define CHIP_VER_P532_ASIC      (BSP_U32)0X05320100
#define CHIP_VER_P531_ASIC      (BSP_U32)0X05300100

#define CHIP_VER_HI6950_SFT     (BSP_U32)0X6950A100

/*VERSIONINFO_I���ݽṹ�а汾�ַ��������Ч�ַ�����*/
#ifndef VER_MAX_LENGTH
#define VER_MAX_LENGTH                  30
#endif

/*memVersionCtrl�ӿڲ�������*/
#define VERIONREADMODE                  0
#define VERIONWRITEMODE                 1

#define BUILD_DATE_LEN  12
#define BUILD_TIME_LEN  12

/*�������*/
#if (FEATURE_OFF == MBB_COMMON)
typedef enum
{
    VER_BOOTLOAD = 0,
    VER_BOOTROM =1,
    VER_NV =2 ,
    VER_VXWORKS =3,
    VER_DSP =4 ,
    VER_PRODUCT_ID =5 ,
    VER_WBBP =6 ,
    VER_PS =7,
    VER_OAM =8,
    VER_GBBP =9 ,
    VER_SOC =10,
    VER_HARDWARE =11,
    VER_SOFTWARE =12,
    VER_MEDIA =13,
    VER_APP =14,
    VER_ASIC =15,
    VER_RF =16,
    VER_PMU =17,
    VER_PDM = 18,
    VER_PRODUCT_INNER_ID = 19,
    VER_INFO_NUM =20
}COMP_TYPE_I;
#else
typedef enum
{
    VER_BOOTLOAD = 0,
    VER_BOOTROM =1,
    VER_NV =2 ,
    VER_VXWORKS =3,
    VER_DSP =4 ,
    VER_PRODUCT_ID =5 ,
    VER_WBBP =6 ,
    VER_PS =7,
    VER_OAM =8,
    VER_GBBP =9 ,
    VER_SOC =10,
    VER_HARDWARE =11,
    VER_SOFTWARE =12,
    VER_MEDIA =13,
    VER_APP =14,
    VER_ASIC =15,
    VER_RF =16,
    VER_PMU =17,
    VER_PDM = 18,
    VER_PRODUCT_INNER_ID = 19,
    VER_HARDWARE_NO_SUB = 20,/*�����汾�����¼�20*/
    VER_INFO_NUM =21
}COMP_TYPE_I;
#endif /* MBB_COMMON */

typedef enum{
     BOARD_TYPE_LTE_ONLY    = 0,
     BOARD_TYPE_GUL
}BOARD_TYPE_E;

typedef enum{
     PV500_CHIP             = 0,
     V7R1_CHIP              = 1,
     PV500_PILOT_CHIP,
     V7R1_PILOT_CHIP,
     V7R2_CHIP				=5
}BSP_CHIP_TYPE_E;

typedef struct  tagUE_SW_BUILD_VER_INFO_STRU
{
    BSP_U16 ulVVerNo;        /* V���� */
    BSP_U16 ulRVerNo;        /*  R����*/
    BSP_U16 ulCVerNo;        /* C����*/
    BSP_U16 ulBVerNo;         /* B����*/
    BSP_U16 ulSpcNo;          /* SPC����*/
    BSP_U16 ulCustomVer;     /* �ͻ��趨�Ʋ���, ���Ӳ���ӿڵ�8bit PCB��,��8bitHW��*/
    BSP_U32 ulProductNo;     /* such as porting,CPE, ... */
    BSP_S8 acBuildDate[BUILD_DATE_LEN];  /* build����,*/
    BSP_S8 acBuildTime[BUILD_TIME_LEN];  /* buildʱ��*/
} UE_SW_BUILD_VER_INFO_STRU; /* �ڲ��汾*/

typedef struct
{
    unsigned char CompId;              /* ����ţ��μ�COMP_TYPE */
    unsigned char CompVer[VER_MAX_LENGTH+1];         /* ���汾���� 30 �ַ�+ \0 */
}VERSIONINFO_I;


extern int bsp_version_get_boardid(void);
/*****************************************************************************
* �� �� ��  : BSP_HwGetVerMain
* ��������  : ��ȡ��Ʒ�汾��
* �������  :
* �������  :
* �� �� ֵ  :
* �޸ļ�¼  :
*****************************************************************************/
#define BSP_HwGetVerMain() bsp_version_get_boardid()

#define DRV_GET_HW_VERSION_INDEX()       bsp_version_get_boardid()

/*****************************************************************************
* �� �� ��  : BSP_GetProductName
* ��������  : ��ȡ��Ʒ����
* �������  : char* pProductName,�ַ���ָ�룬��֤��С��32�ֽ�
*             BSP_U32 ulLength,����������
* �������  : ��
* �� �� ֵ  : 0����ȷ����0: ʧ��
* �޸ļ�¼  :
*****************************************************************************/
extern BSP_S32 BSP_GetProductName (char * pProductName, unsigned int ulLength);


/*****************************************************************************
 �� �� ��  : DRV_GET_PLATFORM_INFO
 ��������  : ��ȡоƬ�İ汾��
 �������  : ��
 �������  : u32PlatformInfo:оƬ�İ汾��
 �� �� ֵ  : void
*****************************************************************************/
extern BSP_VOID DRV_GET_PLATFORM_INFO(unsigned long *u32PlatformInfo);

/*****************************************************************************
* �� �� ��  : BSP_OM_GetChipType
*
* ��������  : ��ȡоƬ����
*
* �������  : BSP_VOID
*
* �������  : ��
*
* �� �� ֵ  : оƬ����
*             PV500_CHIP:PV500оƬ
*             V7R1_CHIP: V7R1оƬ
*
* ����˵��  : ��
*
*****************************************************************************/
extern BSP_CHIP_TYPE_E BSP_OM_GetChipType(BSP_VOID);

/*****************************************************************************
 �� �� ��  : BSP_InitPlatformVerInfo
 ��������  : ��ʼ��оƬ�İ汾��
 �������  : ��
 �������  : none
 �� �� ֵ  : void
*****************************************************************************/
extern BSP_VOID BSP_InitPlatformVerInfo(BSP_VOID);
#define DRV_INIT_PLATFORM_VER()	BSP_InitPlatformVerInfo()
/*****************************************************************************
* �� �� ��  : BSP_OM_GetBoardType
*
* ��������  : ��ȡ��������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : BSP��������ö��
*
* ����˵��  : ��
*
*****************************************************************************/
extern BOARD_TYPE_E bsp_get_board_mode_type(void);
#define BSP_OM_GetBoardType() 	bsp_get_board_mode_type()

/*************************************************
 �� �� ��   : BSP_MNTN_ProductTypeGet
 ��������   : ���ص�ǰ��Ʒ����
 �������   : ��
 �������   : ��
 �� �� ֵ   :0:STICK
             1:MOD
             2:E5
             3:CPE
*************************************************/
extern BSP_U32 BSP_MNTN_ProductTypeGet(void);
#define DRV_PRODUCT_TYPE_GET()   BSP_MNTN_ProductTypeGet()

/*****************************************************************************
* �� �� ��  : BSP_GetBuildVersion
*
* ��������  :
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2011-3-29 wuzechun creat
*
*****************************************************************************/
extern UE_SW_BUILD_VER_INFO_STRU* BSP_GetBuildVersion(BSP_VOID);

/*****************************************************************************
* �� �� ��  : BSP_HwGetHwVersion
* ��������  : ��ȡӲ���汾����
* �������  : BSP_CHAR* pHwVersion,�ַ���ָ�룬��֤��С��32�ֽ�
* �������  : ��
* �� �� ֵ  : ��
* �޸ļ�¼  :
*****************************************************************************/
extern BSP_S32 BSP_HwGetHwVersion (char* pFullHwVersion, BSP_U32 ulLength);

extern char * bsp_version_get_build_date_time(void);
/*****************************************************************************
 �� �� ��  : BSP_GU_GetVerTime
 ��������  : ��ȡ�汾����ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
#define DRV_GET_VERSION_TIME()    bsp_version_get_build_date_time()

typedef struct
{
    unsigned char CompId;              /* ����ţ��μ�COMP_TYPE */
    unsigned char CompVer[VER_MAX_LENGTH+1];         /* ���汾���� 30 �ַ�+ \0 */
}VERSIONINFO;

/*****************************************************************************
 �� �� ��  : BSP_MNTN_MemVersionCtrl
 ��������  : ����汾��д�ӿڡ�
 �������  : pcData����ModeΪ����ʱ��Ϊ�����ߴ����淵�ص�����汾��Ϣ���ڴ��ַ��
                     ��ModeΪд��ʱ��Ϊ������׼��д�������汾��Ϣ�ĵ�ַ��
             ucLength����ModeΪ����ʱ��Ϊ�����ߴ����淵�ص�����汾��Ϣ���ڴ��С��
                       ��ModeΪд��ʱ��Ϊ������׼��д�������汾��Ϣ���ַ�����������'\0'����
             ucType���汾��ϢID��
             ucMode��0����ȡָ��ID������汾��Ϣ��1��д��ָ��ID������汾��Ϣ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int bsp_version_memversion_ctrl(char *pcData, unsigned char ucLength, COMP_TYPE_I ucType, unsigned char ucMode);
#define DRV_MEM_VERCTRL(pcData,ucLength,ucType,ucMode)  \
                          bsp_version_memversion_ctrl(pcData,ucLength,ucType,ucMode)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetFullHwVersion
 ��������  : Ӳ�������汾���ӿڡ�
 �������  : pFullHwVersion��Ϊ�����ߴ����淵�ص�Ӳ�������汾��Ϣ���ڴ��׵�ַ��
             ulLength      ��Ϊ�����ߴ����淵�ص�Ӳ�������汾��Ϣ���ڴ��С��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
#define  DRV_GET_FULL_HW_VER(pFullHwVersion,ulLength)  \
               BSP_HwGetHwVersion(pFullHwVersion,ulLength)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetProductIdInter
 ��������  : ��Ʒ���������汾���ӿڡ�
 �������  : pProductIdInter��Ϊ�����ߴ����淵�صĲ�Ʒ���������汾���ڴ��׵�ַ��
             ulLength       ��Ϊ�����ߴ����淵�صĲ�Ʒ���������汾���ڴ��С��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/

extern int BSP_MNTN_GetProductIdInter(char * pProductIdInter, unsigned int ulLength);
#define  DRV_GET_PRODUCTID_INTER_VER(pProductIdInter,ulLength)  \
              BSP_MNTN_GetProductIdInter(pProductIdInter,ulLength)

/*****************************************************************************
* �� �� ��  : BSP_GetProductInnerName
* ��������  : ��ȡ�ڲ���Ʒ����
* �������  : char* pProductIdInter,    �ַ���ָ��
*             BSP_U32 ulLength,         ����������
* �������  : ��
* �� �� ֵ  : 0����ȷ����0: ʧ��
* �޸ļ�¼  :
*****************************************************************************/
BSP_S32 BSP_GetProductInnerName (char * pProductIdInter, unsigned int ulLength);

/*****************************************************************************
 �� �� ��  : BSP_MNTN_VersionQueryApi
 ��������  : ��ѯ��������İ汾�š�
 �������  : ppVersionInfo��������İ汾��Ϣ��ַ��
 �������  : ucLength�������ص����ݵ��ֽ�����
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int bsp_version_get_verall(void ** ppVersionInfo, unsigned int * ulLength);
#define  DRV_VER_QUERY(ppVersionInfo,ulLength)  \
              bsp_version_get_verall (ppVersionInfo,ulLength)

/*****************************************************************************
* �� �� ��  : bsp_get_firmware_version
*
* ��������  : ��ȡ����汾��
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : ����汾���ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_firmware(void);

/*****************************************************************************
* �� �� ��  : bsp_get_release_version
*
* ��������  : ��ȡrelease_version
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : release_version�ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_release(void);

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetHwGpioInfo
 ��������  : Get flash infomation
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
extern int BSP_MNTN_GetHwGpioInfo(unsigned char *pGpioInfo, unsigned long usLength );
#define DRV_GET_GPIO_INFO(pGpioInfo, usLength)    BSP_MNTN_GetHwGpioInfo(pGpioInfo, usLength )

/*****************************************************************************
* �� �� ��  : DRV_GET_BOARDACTUALTYPE
*
* ��������  : ��ȡ������������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : BSP��������ö��
*             BBIT/SFT/ASIC
*
* ����˵��  : ��
*
*****************************************************************************/
BOARD_ACTUAL_TYPE_E bsp_get_board_actual_type(BSP_VOID);
#define DRV_GET_BOARDACTUALTYPE()   bsp_get_board_actual_type()

/*************************VERSION END  *****************************/
#if (FEATURE_ON == MBB_COMMON)
/*****************************************************************************
* �� �� ��  : bsp_version_get_baseline
*
* ��������  : ��ȡ���߰汾
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : ���߰汾�ַ���
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_baseline(void);

#endif 

#ifdef __cplusplus
}
#endif

#endif

