

#ifndef __DRV_ABB_H__
#define __DRV_ABB_H__
#ifdef __cplusplus
extern "C" {
#endif

#include "drv_comm.h"

/*************************ABB START***********************************/


extern int bsp_abb_write(unsigned int regAddr, unsigned int setData);
#define DRV_ABB_REG_SET(regAddr, setData) bsp_abb_write(regAddr, setData)


extern int bsp_abb_read(unsigned int regAddr, unsigned int * getData);
#define DRV_ABB_REG_GET(regAddr, getData) bsp_abb_read(regAddr, getData)


static INLINE int DRV_AUX_ABB_REG_SET(unsigned int regAddr, unsigned int setData)
{
    return 0;     /* ��׮,mohaojuȷ�� */
}


static INLINE int DRV_AUX_ABB_REG_GET(unsigned int regAddr, unsigned int * getData)
{
    return 0;    /* ��׮,mohaojuȷ�� */
}

/*****************************************************************************
 �� �� ��  : BSP_MNTN_ABBSelfCheck
 ��������  : ����abb�Լ���
 �������  : None
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
static INLINE int BSP_MNTN_ABBSelfCheck(void)
{
	return 0;
}
#define DRV_ABB_SELFCHECK()    BSP_MNTN_ABBSelfCheck()

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_ABBGSMRxCtrl
 ��������  : ���ӿ�ʵ��ABB GSM���տ��ơ�
 �������  : ucStatus��0���رգ�1���򿪡�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
static INLINE unsigned int  DRV_ABB_GRX_CTRL(unsigned char ucStatus)
{
    return OK;     /* ��׮ */
}


/*****************************************************************************
 �� �� ��  : BSP_GUSYS_GsmPllStatusGet
 ��������  : ��ȡGSM BBP PLL�ȶ�״̬��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0���ȶ�
             1��δ�ȶ�
*****************************************************************************/
static INLINE unsigned long DRV_GET_GSM_PLL_STATUS(void)
{
#if 0
    unsigned char ucData;

    /* ����ABB�ļĴ�����ȡ�ӿ�BSP_ABB_RegGet����ȡGPLL״̬��*/
    if(OK == BSP_ABB_RegGet(GSM_PLL_REG, &ucData))
    {
        if(ucData & (1 << GSM_PLL_STABLE_BIT))
        {
            return OK;
        }
        else
        {
            return 1;
        }
    }
    else
#endif
    {
        return 1;
    }
}


/*****************************************************************************
 �� �� ��  : BSP_GUSYS_WcdmaPllStatusGet
 ��������  : ��ȡWCDMA BBP PLL�ȶ�״̬��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0���ȶ�
             1��δ�ȶ�
*****************************************************************************/
static INLINE unsigned long DRV_GET_WCDMA_PLL_STATUS(void)
{
#if 0   /* v7r1��ʵ�� */
    unsigned char ucData;

    /* ����ABB�ļĴ�����ȡ�ӿ�BSP_ABB_RegGet����ȡWPLL״̬��*/
    if(OK == BSP_ABB_RegGet(WCDMA_PLL_REG, &ucData))
    {
        if(ucData & (1 << WCDMA_PLL_STABLE_BIT))
        {
            return OK;
        }
        else
        {
            return 1;
        }
    }
    else
#endif
    {
        return 1;
    }
}

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_ABBWCDMARxCtrl
 ��������  : ���ӿ�ʵ��ABB WCDMA���տ��ơ�
 �������  : ucStatus��0���رգ�1���򿪡�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
                        -1������ʧ�ܡ�
*****************************************************************************/
static INLINE unsigned int  DRV_ABB_WRX_CTRL(unsigned char ucStatus)
{
    return OK;     /* ��׮ */
}

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_DspPllStatusGet
 ��������  : ��ȡDSP PLL�ȶ�״̬��
 �������  : �ޡ�
 �������  :�ޡ�
 �� �� ֵ  :
                     0���ȶ�
                     1��δ�ȶ�
*****************************************************************************/
static INLINE unsigned long DRV_GET_DSP_PLL_STATUS(void)
{
    return OK;     /* ��׮ */
}

/* ����V9R1��׮����adp_dpm.c��ʵ�� */
extern void DRV_DSP_AHB_RESET(void);
extern void DRV_DSP_AHB_RESET_CANCEL(void);

/*************************ABB END*************************************/

#ifdef __cplusplus
}
#endif

#endif

