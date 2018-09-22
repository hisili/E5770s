
#include <osl_bio.h>
#include <bsp_ipc.h>
#include <hi_pmu.h>
#include <bsp_pmu.h>
#include <osl_sem.h>
#include <pmu_balong.h>
#include <osl_spinlock.h>
#if defined(__KERNEL__)
#include <osl_irq.h>
#endif
#include "common_hi6451.h"

struct hi6551_common_data{
    spinlock_t      lock;
};
struct hi6551_common_data g_hi6451_comm_st;
#if defined(__KERNEL__)
/*32Kʱ��ƫ��*/
/*para check func*/
static __inline__ int hi6451_32k_para_check(pmu_clk_e clk_id)
{
    if(PMU_32K_CLK_B < clk_id || PMU_32K_CLK_A > clk_id)
        return BSP_PMU_ERROR;
    else
        return BSP_PMU_OK;
}
/*****************************************************************************
 �� �� ��  : hi6451_32k_clk_enable
 ��������  : ������Ӧ·32kʱ��
 �������  : pmu 32k ʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
int hi6451_32k_clk_enable(pmu_clk_e clk_id)
{
    s32 iRetVal = 0;
    u8 iregVal = 0;
    hi6451_commflags_t flags;

    if(hi6451_32k_para_check(clk_id))
        return BSP_PMU_ERROR;

    /*���ڻ���*/
    spin_lock_irqsave(&g_hi6451_comm_st.lock,flags);
    iRetVal |= bsp_hi6451_reg_read(HI_PMU_ONOFF7_OFFSET,&iregVal);
    iregVal |= 0x02;
    iRetVal |= bsp_hi6451_reg_write(HI_PMU_ONOFF7_OFFSET, iregVal);
    spin_unlock_irqrestore(&g_hi6451_comm_st.lock,flags);

    return iRetVal;
}
/*****************************************************************************
 �� �� ��  : hi6451_32k_clk_disable
 ��������  : �رն�Ӧ·32kʱ��
 �������  : pmu 32k ʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
int hi6451_32k_clk_disable(pmu_clk_e clk_id)
{
    s32 iRetVal = 0;
    u8 iregVal = 0;
    hi6451_commflags_t flags;

    if(hi6451_32k_para_check(clk_id))
        return BSP_PMU_ERROR;

    if(PMU_32K_CLK_A == clk_id)
    {
        pmic_print_info("soc use,can not be closed!\n");
        return BSP_PMU_ERROR;
    }

    /*���ڻ���*/
    spin_lock_irqsave(&g_hi6451_comm_st.lock,flags);
    iRetVal |= bsp_hi6451_reg_read(HI_PMU_ONOFF7_OFFSET,&iregVal);
    iregVal &= ~0x02;
    iRetVal |= bsp_hi6451_reg_write(HI_PMU_ONOFF7_OFFSET, iregVal);
    spin_unlock_irqrestore(&g_hi6451_comm_st.lock,flags);

    return iRetVal;
}
/*****************************************************************************
 �� �� ��  : hi6451_32k_clk_is_enabled
 ��������  : ��ѯ��Ӧ·32kʱ���Ƿ���
 �������  : pmu 32k ʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  : pmu adp�ļ�����
*****************************************************************************/
int hi6451_32k_clk_is_enabled(pmu_clk_e clk_id)
{
    s32 iRetVal = 0;
    u8 iregVal = 0;

    if(hi6451_32k_para_check(clk_id))
        return BSP_PMU_ERROR;

    iRetVal = bsp_hi6451_reg_read(HI_PMU_ONOFF7_OFFSET,&iregVal);
    return (int)(iregVal & (0x1 << 1));
}

/*****************************************************************************
 �� �� ��  : hi6451_power_key_state_get
 ��������  : ��ȡusb�Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : power���Ƿ��£�1:���£�0:δ����)
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool hi6451_power_key_state_get(void)
{
    u8 regval = 0;

    bsp_hi6451_reg_read(HI_PMU_STATUS4_OFFSET, &regval);
    return  (regval & PMU_HI6451_POWER_KEY_MASK) ? 1 : 0;
}
/*****************************************************************************
 �� �� ��  : bsp_hi6451_usb_state_get
 ��������  : ��ȡusb�Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : usb�����γ�(1:���룻0:�γ�)
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool hi6451_usb_state_get(void)
{

    u8 regval = 0;

    bsp_hi6451_reg_read(HI_PMU_STATUS5_OFFSET, &regval);
    return  (regval & PMU_HI6451_USB_STATE_MASK) ? 1 : 0;

}
#endif

/*****************************************************************************
 �� �� ��  : hi6451_version_get
 ��������  : ��ȡpmu�İ汾��
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ���ú���  :
 ��������  : HSO����,MSP����
*****************************************************************************/
u8  hi6451_version_get(void)
{
    u8 regval = 0;

    bsp_hi6451_reg_read(HI_PMU_VERSION_OFFSET, &regval);
    return  regval;
}
/*****************************************************************************
 �� �� ��  : bsp_hi6451_common_init
 ��������  : PMIC HI6451 commonģ���ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��ע˵��  : ��ʼ��app�����ź���
*****************************************************************************/
void bsp_hi6451_common_init(void)
{
    spin_lock_init(&g_hi6451_comm_st.lock);/*�ж�ֻ��Acoreʵ�֣���core*/
}
