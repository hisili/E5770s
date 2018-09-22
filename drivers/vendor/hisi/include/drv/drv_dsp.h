
#ifndef __DRV_DSP_H__
#define __DRV_DSP_H__

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
  ������:       int bsp_bbe_load_muti()
  ��������:     ���ؾ�����TCM
  �������:     ��
  �������:     ��
  ����ֵ:       �ɹ���0
                ʧ�ܣ�����
*******************************************************************************/
extern int bsp_bbe_load_muti(void);
#define DRV_BBE_LOAD() bsp_bbe_load_muti()
/* �����Ͻӿ� */
#define BSP_LoadDsp() DRV_BBE_LOAD()

/*******************************************************************************
  ������:       int bsp_bbe_run()
  ��������:     ����DSP0
  �������:     ��
  �������:     ��
  ����ֵ:       �ɹ���0
                ʧ�ܣ�����
*******************************************************************************/
extern int bsp_bbe_run(void);
#define DRV_BBE_RUN() bsp_bbe_run()
/* �����Ͻӿ� */
#define BSP_RunDsp() DRV_BBE_RUN()

/* GU DSP�ӿ����� */
extern int BSP_GUDSP_UpateShareInfo(unsigned long shareAddr);
#define DRV_BSP_UPDATE_DSP_SHAREINFO(addr) BSP_GUDSP_UpateShareInfo(addr)

/*****************************************************************************
 �� �� ��  : DRV_GET_CODEC_FUNC_STATUS
 ��������  : ��ȡCODEC����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : 1:  CODEC����
             0��CODEC ������
*****************************************************************************/
int bsp_dsp_is_hifi_exist(void);
#define DRV_GET_CODEC_FUNC_STATUS() bsp_dsp_is_hifi_exist()

/* ����V9R1��׮ */
static INLINE int ZSP_Init(void)
{
    return OK;
}

static INLINE int DRV_DSP_SHARE_ADDR_GET(void)
{
    return OK;
}

static INLINE int DRV_DSP_DRX_GPIO_VAL_SET(UINT32 val)
{
    return OK;
}

static INLINE int BSP_TDS_GetDynTableAddr(void)
{
    return OK;
}

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_ArmPllStatusGet
 ��������  : ��ȡARM PLL�ȶ�״̬��
 �������  : �ޡ�
 �������  :�ޡ�
 �� �� ֵ  :
                     0���ȶ�
                     1��δ�ȶ�
*****************************************************************************/
static INLINE unsigned int DRV_GET_ARM_PLL_STATUS(void)
{
    return OK;     /* ��׮ */
}

extern int bsp_bbe_stop(void);

extern int bsp_bbe_power_on(void);

extern int bsp_bbe_power_off(void);

extern int bsp_bbe_unreset(void);

extern int bsp_bbe_reset(void);

extern int bsp_bbe_clock_enable(void);

extern int bsp_bbe_clock_disable(void);

extern int bsp_bbe_adp_restore(void);

extern int bsp_bbe_adp_store(void);

extern int bsp_bbe_adp_get_state(void);

extern int bsp_msp_bbe_restore(void);

extern int bsp_msp_bbe_store(void);

extern int bsp_msp_wait_edma_ok(void);

/*****************************************************************************
 Prototype       : DRV_PWRCTRL_DSP_RUN
 Description     : ����DSPΪRUNģʽ
 Input           : None
 Output          : None.
 Return Value    : 0: �ɹ�
                   -1: ʧ��
*****************************************************************************/
#define DRV_PWRCTRL_DSP_RUN() bsp_bbe_run()
/*****************************************************************************
 Prototype       : DRV_PWRCTRL_DSP_HOLD
 Description     : ����DSPΪstallģʽ
 Input           : None
 Output          : None.
 Return Value    : 0: �ɹ�
                   -1: ʧ��
*****************************************************************************/
#define DRV_PWRCTRL_DSP_HOLD() bsp_bbe_stop()
/*****************************************************************************
 Prototype       : DRV_EDMA_DSP_MemRestore
 Description     : �ָ�BBE16����TCM
 Input           : None
 Output          : None.
 Return Value    : 0: �ɹ�
                   -1 ʧ��
*****************************************************************************/
#define DRV_EDMA_DSP_MemRestore() bsp_msp_bbe_restore()
/*****************************************************************************
 Prototype       : DRV_EDMA_DSP_MemRestore
 Description     : ����BBE16����TCM
 Input           : None
 Output          : None.
 Return Value    : 0: �ɹ�
                   -1: ʧ��
*****************************************************************************/
#define DRV_EDMA_DSP_MemStore() bsp_msp_bbe_store()
/*****************************************************************************
 Prototype       : DRV_EDMA_DSP_StateGet
 Description     : ���BBE16 TCM����ָ��Ƿ����
 Input           : None
 Output          : None.
 Return Value    : 1: DSP TCM����ָ����
*****************************************************************************/
#define DRV_EDMA_DSP_StateGet() bsp_msp_wait_edma_ok()
/*****************************************************************************
 Prototype       : DRV_PWRCTRL_DSP_UNRESET
 Description     : �⸴λBBE16
 Input           : None
 Output          : None.
*****************************************************************************/
#define DRV_PWRCTRL_DSP_UNRESET() bsp_bbe_unreset()
/*****************************************************************************
 Prototype       : DRV_PWRCTRL_DSP_UNRESET
 Description     : ��λBBE16
 Input           : None
 Output          : None.
*****************************************************************************/
#define DRV_PWRCTRL_DSP_RESET() bsp_bbe_reset()
/*****************************************************************************
 Prototype       : DRV_PWRCTRL_DSP_CLKENABLE
 Description     : ��BBE16ʱ��
 Input           : None
 Output          : None.
*****************************************************************************/
#define DRV_PWRCTRL_DSP_CLKENABLE() bsp_bbe_clock_enable()
/*****************************************************************************
 Prototype       : DRV_PWRCTRL_DSP_CLKDISABLE
 Description     : �ر�BBE16ʱ��
 Input           : None
 Output          : None.
*****************************************************************************/
#define DRV_PWRCTRL_DSP_CLKDISABLE() bsp_bbe_clock_disable()
#ifdef __cplusplus
}
#endif

#endif

