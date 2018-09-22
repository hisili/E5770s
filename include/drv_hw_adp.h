#ifndef __DRV_HW_ADP_H__
#define __DRV_HW_ADP_H__

#include "drv_comm.h"
#include <soc_interrupts.h>
/* ����������Ҫ��ѯ��IP���� */
typedef enum tagBSP_IP_TYPE_E
{
    BSP_IP_TYPE_CICOM0,
    BSP_IP_TYPE_CICOM1,
	BSP_IP_TYPE_ZSP_DTCM,
	BSP_IP_TYPE_AHB,
    BSP_IP_TYPE_GBBP,
    BSP_IP_TYPE_GBBP_DRX,
    BSP_IP_TYPE_GBBP1,
    BSP_IP_TYPE_GBBP1_DRX,
    BSP_IP_TYPE_WBBP,
    BSP_IP_TYPE_WBBP_DRX,
    BSP_IP_TYPE_SYSCTRL,
    BSP_IP_TYPE_TDSSYS,
	BSP_IP_TYPE_BBPMASTER,
    BSP_IP_TYPE_HDLC,
    BSP_IP_TYPE_CTU,
    BSP_IP_TYPE_COMMON,
    BSP_IP_TYPE_BBPDMA,
    BSP_IP_TYPE_BBPDBG,
    BSP_IP_TYPE_BBPSRC,
    BSP_IP_TYPE_SOCP,

    BSP_IP_TYPE_BUTTOM

}BSP_IP_TYPE_E;

typedef enum tagBSP_DDR_TYPE_E
{
    BSP_DDR_TYPE_DDR_GU = 0,
    BSP_DDR_TYPE_DDR_TLPHY_IMAGE,
    BSP_DDR_TYPE_DDR_LPHY_SDR,
    BSP_DDR_TYPE_DDR_TLPHY_LCS,
    BSP_DDR_TYPE_DDR_TLPHY_BANDNV,
    BSP_DDR_TYPE_DDR_HIFI,
    BSP_DDR_TYPE_SRAM_TLPHY,
    BSP_DDR_TYPE_SRAM_RTT_SLEEP_FLAG,
    BSP_DDR_TYPE_SHM_TIMESTAMP,
    BSP_DDR_TYPE_SHM_TEMPERATURE,
    BSP_DDR_TYPE_SRAM_MAILBOX_PROTECT_FLG,
    BSP_DDR_TYPE_MAILBOX_HEAD_BBE16_HIFI_MSG,
    BSP_DDR_TYPE_MAILBOX_HEAD_HIFI_BBE16_MSG,
    BSP_DDR_TYPE_MAILBOX_QUEUE_BBE16_HIFI_MSG,
    BSP_DDR_TYPE_MAILBOX_QUEUE_HIFI_BBE16_MSG,
    BSP_DDR_TYPE_BUTTOM
}BSP_DDR_TYPE_E;

BSP_U32 BSP_GetIPBaseAddr(BSP_IP_TYPE_E enIPType);
#define DRV_GET_IP_BASE_ADDR(enIPType)  BSP_GetIPBaseAddr(enIPType)
BSP_S32 BSP_GetMemAddrSize(BSP_DDR_TYPE_E enDdrType, BSP_U32 * addr, BSP_U32 * size);

/* ��Ҫ��ѯ���ж����� */
typedef enum tagBSP_INT_TYPE_E
{
	BSP_INT_TYPE_GBBP_DSP                  = INT_LVL_GBBP_DSP,                 /* GSM1 Ԥ����DRX�ж�(g1_int_bbp_to_dsp)         */
	BSP_INT_TYPE_GBBP_GSML_NODRX_INTR      = INT_LVL_GBBP_GSML_NODRX_INTR,     /* PHY_104Mʱ�����ж�(����������ǵ�����)        */
	BSP_INT_TYPE_GBBP_AWAKE_DSP            = INT_LVL_GBBP_AWAKE_DSP,           /* GSM1 Ԥ��DRX�����ж�(g1_int_bbp_to_dsp_32k)   */
	BSP_INT_TYPE_GBBP_GSML_RESERVED_INTR   = INT_LVL_GBBP_GSML_RESERVED_INTR,  /* PHY_32Kʱ�����ж�(�����ǵ�����)               */
	BSP_INT_TYPE_GBBP                      = INT_LVL_GBBP,                     /* GSM1 ��DRX�ж�(g1_int_bbp_to_cpu)             */
	BSP_INT_TYPE_GBBP_AWAKE                = INT_LVL_GBBP_AWAKE,               /* GSM1 DRX�����ж�(g1_int_bbp_to_cpu_32k)       */
	BSP_INT_TYPE_GBBP1_DSP                 = INT_LVL_GBBP1_DSP,                /* GSM2 Ԥ����DRX�ж�(g2_int_bbp_to_dsp)         */
	BSP_INT_TYPE_GBBP1_AWAKE_DSP           = INT_LVL_GBBP1_AWAKE_DSP,          /* GSM2 Ԥ��DRX�����ж�(g2_int_bbp_to_dsp_32k)   */
	BSP_INT_TYPE_GBBP1                     = INT_LVL_GBBP1,                    /* GSM2 ��DRX�ж�(g2_int_bbp_to_cpu)             */
	BSP_INT_TYPE_GBBP1_AWAKE               = INT_LVL_GBBP1_AWAKE,              /* GSM2 DRX�����ж�(g2_int_bbp_to_cpu_32k)       */
	BSP_INT_TYPE_WBBP_0MS                  = INT_LVL_WBBP_0MS,                 /* card1 0ms�ж�                                 */
	BSP_INT_TYPE_WBBP_AWAKE                = INT_LVL_WBBP_AWAKE,               /* ˯�ߡ������ж�                                */
	BSP_INT_TYPE_WBBP_SWITCH               = INT_LVL_WBBP_SWITCH,              /* ʱ���л��ж�                                  */
	BSP_INT_TYPE_WBBP1_0MS                 = INT_LVL_WBBP1_0MS,                /* Card2 0ms �ж�                                */
	BSP_INT_TYPE_WBBP_CARD2_0MS_INTR       = INT_LVL_WBBP_CARD2_0MS_INTR,      /* Card2 0ms �ж�                                */
	BSP_INT_TYPE_WBBP_SEARCH               = INT_LVL_WBBP_SEARCH,              /* С�������ж�                                  */
	BSP_INT_TYPE_WBBP_SEARCH_INTR          = INT_LVL_WBBP_SEARCH_INTR,         /* С�������ж�                                  */
	BSP_INT_TYPE_WBBP_RAKE                 = INT_LVL_WBBP_RAKE,                /* Rake����ϱ��ж�                              */
	BSP_INT_TYPE_WBBP_RAKE_INTR            = INT_LVL_WBBP_RAKE_INTR,           /* Rake����ϱ��ж�                              */
	BSP_INT_TYPE_WBBP_DECODE               = INT_LVL_WBBP_DECODE,              /* ���������ϱ��ж�                              */
	BSP_INT_TYPE_WBBP_DECODE_INTR          = INT_LVL_WBBP_DECODE_INTR,         /* ���������ϱ��ж�                              */
	BSP_INT_TYPE_WBBP_TIME                 = INT_LVL_WBBP_TIME,                /* card1��ʱ�ж�                                 */
	BSP_INT_TYPE_WBBP_CARD1_TIME_INTR      = INT_LVL_WBBP_CARD1_TIME_INTR,     /* card1��ʱ�ж�                                 */
	BSP_INT_TYPE_WBBP1_TIME                = INT_LVL_WBBP1_TIME,               /* card2��ʱ�ж�                                 */
	BSP_INT_TYPE_WBBP_CARD2_TIME_INTR      = INT_LVL_WBBP_CARD2_TIME_INTR,     /* card2��ʱ�ж�                                 */
	BSP_INT_TYPE_WBBP_MULTI_SEARCH         = INT_LVL_WBBP_MULTI_SEARCH,        /* �ྶ���������ж�                              */
	BSP_INT_TYPE_WBBP_MULTI_SEARCH_INTR    = INT_LVL_WBBP_MULTI_SEARCH_INTR,   /* �ྶ���������ж�                              */
	BSP_INT_TYPE_WBBP_BBPMST               = INT_LVL_WBBP_BBPMST,              /* ����BBP Master�ϱ��ж�                        */
	BSP_INT_TYPE_BBPMASTER                 = INT_LVL_BBPMASTER,                /* ����BBP Master�ϱ��ж�                        */
	BSP_INT_TYPE_CTU_INT_G                 = INT_LVL_CTU_INT_G,                /* CTU������Gģ��ص��ж�(G����Ϊ��ģ��Ҳ����Ϊ��ģ)*/
	BSP_INT_TYPE_CTU_INT_W                 = INT_LVL_CTU_INT_W,                /* CTU������Wģ��ص��ж�(W����Ϊ��ģ��Ҳ����Ϊ��ģ)*/
	BSP_INT_TYPE_INT12_G2                  = INT_LVL_INT12_G2,                 /* ��δ����                                         */
	BSP_INT_TYPE_UPACC_DSP                 = INT_LVL_GU_UPACC_DSP,             /* ��Ҫ����ȷ��                                     */
	BSP_INT_TYPE_UPACC_INTR                = INT_LVL_UPACC_INTR,               /* ��Ҫ����ȷ��                                     */
	BSP_INT_TYPE_CICOM_DL                  = INT_LVL_CICOM_DL,
	BSP_INT_TYPE_CICOM_UL                  = INT_LVL_CICOM_UL,
	BSP_INT_TYPE_CICOM1_DL                 = INT_LVL_GU_CICOM1_DL,
	BSP_INT_TYPE_CICOM1_UL                 = INT_LVL_GU_CICOM1_UL,
    BSP_INT_TYPE_HDLC_FRM                  = INT_LVL_GU_HDLC_FRM,
    BSP_INT_TYPE_HDLC_DEF                  = INT_LVL_GU_HDLC_DEF,

/******����ΪLTE�ж�***********/
	BSP_INT_TYPE_LBBP_AWAKE                = INT_LVL_LTE_ARM_WAKEUP_INT,
	BSP_INT_TYPE_TBBP_AWAKE                = INT_LVL_TDS_DRX_ARM_WAKEUP_INT,

    BSP_INT_TYPE_BUTTOM
}BSP_INT_TYPE_E;

/*************************��ѯģ���Ƿ�֧�� START**********************/

/* ��ǰ�汾�Ƿ�֧��ĳ��ģ�� */
typedef enum tagBSP_MODULE_SUPPORT_E
{
    BSP_MODULE_SUPPORT     = 0,
    BSP_MODULE_UNSUPPORT   = 1,
    BSP_MODULE_SUPPORT_BUTTOM
}BSP_MODULE_SUPPORT_E;

/* ��ѯ��ģ������ */
typedef enum tagBSP_MODULE_TYPE_E
{
    BSP_MODULE_TYPE_SD = 0x0,
    BSP_MODULE_TYPE_CHARGE,
    BSP_MODULE_TYPE_WIFI,
    BSP_MODULE_TYPE_OLED,
    BSP_MODULE_TYPE_HIFI,
    BSP_MODULE_TYPE_POWER_ON_OFF,
    BSP_MODULE_TYPE_HSIC,
    BSP_MODULE_TYPE_LOCALFLASH,
    BSP_MODULE_TYPE_BUTTOM
}BSP_MODULE_TYPE_E;

/*****************************************************************************
 �� �� ��  : BSP_CheckModuleSupport
 ��������  : ��ѯģ���Ƿ�֧��
 �������  : enModuleType: ��Ҫ��ѯ��ģ������
 �������  : ��
 ����ֵ    ��BSP_MODULE_SUPPORT��BSP_MODULE_UNSUPPORT
*****************************************************************************/
BSP_MODULE_SUPPORT_E BSP_CheckModuleSupport(BSP_MODULE_TYPE_E enModuleType);

#define DRV_GET_BATTERY_SUPPORT()   BSP_CheckModuleSupport(BSP_MODULE_TYPE_CHARGE)

#define DRV_GET_WIFI_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_WIFI)

#define DRV_GET_SD_SUPPORT()        BSP_CheckModuleSupport(BSP_MODULE_TYPE_SD)

#define DRV_GET_OLED_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_OLED)

#define DRV_GET_HIFI_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_HIFI)

#define DRV_GET_HSIC_SUPPORT()      BSP_CheckModuleSupport(BSP_MODULE_TYPE_HSIC)

/*************************��ѯģ���Ƿ�֧�� END************************/

#define WRFlAG     1
#define RDFlAG     0

/*****************************************************************************
 �� �� ��  : BSP_GetIntNO
 ��������  : �жϺŲ�ѯ
 �������  : enIntType: ��Ҫ��ѯ���ж�����
 �������  : ��
 ����ֵ    ����ѯ�����жϺ�
*****************************************************************************/
BSP_S32 BSP_GetIntNO(BSP_INT_TYPE_E enIntType);
#define DRV_GET_INT_NO(enIntType)    BSP_GetIntNO(enIntType)
/*****************************************************************************
* �� �� ��  : DRV_VICINT_ENABLE
*
* ��������  : ʹ��ĳ���ж�
*
* �������  : INT32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��40
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  : 2009��3��5��   zhanghailun  creat
*****************************************************************************/
BSP_S32	adp_int_enable(int ulLvl);

#define DRV_VICINT_ENABLE(ulLvl)    adp_int_enable(ulLvl)

/*****************************************************************************
 * �� �� ��  : DRV_VICINT_DISABLE
 *
 * ��������  : ȥʹ��ĳ���ж�
 *
 * �������  : INT32 ulLvl Ҫʹ�ܵ��жϺţ�ȡֵ��Χ0��40
 * �������  : ��
 *
 * �� �� ֵ  : OK&ERROR
 *
 * �޸ļ�¼  : 2009��3��5��   zhanghailun  creat
 *****************************************************************************/
BSP_S32 adp_int_disable(int ulLvl);

#define  DRV_VICINT_DISABLE(ulLvl)    adp_int_disable(ulLvl)

/*****************************************************************************
 * �� �� ��  : DRV_VICINT_CONNECT
 *
 * ��������  : ע��ĳ���ж�
 *
 * �������  : VOIDFUNCPTR * vector �ж������ţ�ȡֵ��Χ0��40
 *            routine  �жϷ������
 *           INT32 parameter      �жϷ���������
 * �������  : ��
 *
 * �� �� ֵ  : OK&ERROR
 *
 * �޸ļ�¼  : 2009��3��5��   zhanghailun  creat
 *****************************************************************************/
BSP_S32 adp_int_connect(int ulLvl,FUNCPTR_1 routine,int parameter);

#define DRV_VICINT_CONNECT(vector,routine,parameter)    adp_int_connect(vector,routine,parameter)
/* stub */
#define DRV_VICINT_EXIT_HOOK_ADD(p_Func)
#define DRV_VICINT_EXIT_HOOK_DEL()


#endif

