/******************************************************************************

                 ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_baseaddr_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2012-12-08 16:50:26
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��12��8��
    ��    ��   : f00204170
    �޸�����   : �ӡ�Hi6620V100 SOC�Ĵ����ֲ�_BaseAddr.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_BASEADDR_INTERFACE_H__
#define __SOC_BASEADDR_INTERFACE_H__

#include "soc_memmap_comm.h"
#include "bsp_memmap.h"
#include "hi_bbp_systime.h"
#include "hi_timer.h"
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* �Ĵ���˵���� */

#define SOC_BBP_COMM_BASE_ADDR                        HI_CTU_BASE_ADDR

/* �Ĵ���˵���� */
#define SOC_BBP_COMM_ON_BASE_ADDR                     HI_BBP_COMM_ON_BASE_ADDR

/* �Ĵ���˵���� */
#define SOC_BBP_GSM_BASE_ADDR                         HI_GBBP_REG_BASE_ADDR

/* �Ĵ���˵���� */
#define SOC_BBP_GSM_ON_BASE_ADDR                        HI_GBBP_DRX_REG_BASE_ADDR


#define SOC_BBP_GSM1_BASE_ADDR                         HI_GBBP1_REG_BASE_ADDR

/* �Ĵ���˵���� */
#define SOC_BBP_GSM1_ON_BASE_ADDR                        HI_GBBP1_DRX_REG_BASE_ADDR


/* �Ĵ���˵���� */
#define SOC_BBP_WCDMA_BASE_ADDR                       HI_WBBP_REG_BASE_ADDR

/* �Ĵ���˵����*/
#define SOC_BBP_WCDMA_ON_BASE_ADDR                    HI_WBBP_DRX_REG_BASE_ADDR

/* �Ĵ���˵���� */
#define SOC_UPACC_BASE_ADDR           	              HI_UPACC_BASE_ADDR
#define SOC_AO_SCTRL_SC_SLICER_COUNT0_ADDR(x) (HI_BBP_SYSTIME_BASE_ADDR_VIRT+HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET)

/*HIFI timerʹ�ܼ�����V7R2 HIFIʹ�õ�timer���л�Ϊ32k������Ҫ�ϲ�������ʴ�׮*/
#define SOC_AO_SCTRL_SC_TIMER_EN1_ADDR(x)

/*HIFI timerʱ��ʹ��*/
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(x) (HI_SYSCRG_BASE_ADDR+0x18)

/*��ȡtimer����ַ*/
#define SOC_HIFI_Timer00_BASE_ADDR HI_TIMER_00_REGBASE_ADDR
#define SOC_HIFI_Timer08_BASE_ADDR HI_TIMER_08_REGBASE_ADDR

/*ipc��ַ*/
#define SOC_IPC_S_BASE_ADDR HI_IPCM_REGBASE_ADDR

/*DMA��ַ*/
#define SOC_AP_DMAC_BASE_ADDR HI_EDMA_REGBASE_ADDR

/*DMA��ַ*/
#define SOC_UART3_BASE_ADDR HI_UART3_REGBASE_ADDR


#define SOC_AO_SCTRL_SC_SLICER_COUNT0_ADDR(x) (HI_BBP_SYSTIME_BASE_ADDR_VIRT+HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET)

/*HIFI timerʹ�ܼ�����V7R2 HIFIʹ�õ�timer���л�Ϊ32k������Ҫ�ϲ�������ʴ�׮*/
#define SOC_AO_SCTRL_SC_TIMER_EN1_ADDR(x)

/*HIFI timerʱ��ʹ��*/
#define SOC_AO_SCTRL_SC_PERIPH_CLKEN4_ADDR(x) (HI_SYSCRG_BASE_ADDR+0x18)

/*��ȡtimer����ַ*/
#define SOC_HIFI_Timer00_BASE_ADDR HI_TIMER_00_REGBASE_ADDR
#define SOC_HIFI_Timer08_BASE_ADDR HI_TIMER_08_REGBASE_ADDR

/*ipc��ַ*/
#define SOC_IPC_S_BASE_ADDR HI_IPCM_REGBASE_ADDR

/*DMA��ַ*/
#define SOC_AP_DMAC_BASE_ADDR HI_EDMA_REGBASE_ADDR

/*DMA��ַ*/
#define SOC_UART3_BASE_ADDR HI_UART3_REGBASE_ADDR



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  6 STRUCT����
*****************************************************************************/



/*****************************************************************************
  7 UNION����
*****************************************************************************/





/*****************************************************************************
  8 OTHERS����
*****************************************************************************/



/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_baseaddr_interface.h */

