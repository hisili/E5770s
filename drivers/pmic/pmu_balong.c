
#ifdef __VXWORKS__
#include <drv_dpm.h>
#include <drv_pmu.h>
#include <bsp_pmu.h>
#include <bsp_regulator.h>
#include "bsp_pmu_hi6561.h"
#endif
#include "pmu_balong.h"

#ifdef __KERNEL__
#ifdef CONFIG_PMIC_HI6451
#include "hi6451/irq_hi6451.h"
#endif
#ifdef CONFIG_PMIC_HI6551
#include "hi6551/irq_hi6551.h"
#include "hi6551/dr_hi6551.h"
#endif
#ifdef CONFIG_PMIC_HI6559
#include "hi6559/irq_hi6559.h"
#include "hi6559/dr_hi6559.h"
#endif
#endif

#ifdef CONFIG_PMIC_HI6451
#include "hi6451/common_hi6451.h"
#endif
#ifdef CONFIG_PMIC_HI6551
#include "hi6551/common_hi6551.h"
#endif
#ifdef CONFIG_PMIC_HI6559
#include "hi6559/common_hi6559.h"
#endif

struct pmu_adp_ops{
#if defined(__KERNEL__)
    int (*get_boot_state)(void);
    int (*clk_32k_enable)(pmu_clk_e clk_id);
    int (*clk_32k_disable)(pmu_clk_e clk_id);
    int (*clk_32k_is_enabled)(pmu_clk_e clk_id);
    bool (*usb_state_get)(void);
    bool (*key_state_get)(void);
    void (*irq_mask)(unsigned int irq);
    void (*irq_unmask)(unsigned int irq);
    int (*irq_is_masked)(unsigned int irq);
    int (*irq_callback_register)(unsigned int irq,pmufuncptr routine,void *data);
    int (*dr_list_current)(int dr_id, unsigned selector);
    int (*dr_set_mode)(int dr_id, dr_mode_e mode);
    dr_mode_e (*dr_get_mode)(int dr_id);
    int (*dr_fla_time_set)(DR_FLA_TIME *dr_fla_time_st);
    int (*dr_fla_time_get)(DR_FLA_TIME *dr_fla_time_st);
    int (*dr_bre_time_set)(dr_id_e dr_id, DR_BRE_TIME *dr_bre_time_st);
    int (*dr_bre_time_get)(dr_id_e dr_id, DR_BRE_TIME *dr_bre_time_st);
    unsigned (*dr_bre_time_list)(dr_id_e dr_id, dr_bre_time_e bre_time_enum ,unsigned selector);
    unsigned (*dr_bre_time_selectors_get)(dr_id_e dr_id, dr_bre_time_e bre_time_enum);
    int (*dr_start_delay_set)(dr_id_e dr_id, unsigned delay_ms);
    int (*sim_debtime_set)(u32 uctime);
    void (*ldo22_res_enable)(void);
    void (*ldo22_res_disable)(void);
#endif
#ifdef __VXWORKS__
    int (*pmu_init)(void);
    s32 (*apt_enable)(void);
    s32 (*apt_disable)(void);
    s32 (*apt_status_get)(void);
#endif
    u8 (*version_get)(void);
    int (*sim_upres_disable)(u32 sim_id);

};

/*��������*/
#if defined(__VXWORKS__)
u8 dummy_info_get_handler(void);
#endif

#if defined(__KERNEL__)
/*****************************************************************************
 �� �� ��  : dummy_32k_clk_enable
 ��������  : �������رա���ѯpmu��32kʱ�Ӵ�׮����
 �������  : clk_id:32kʱ�ӱ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
int dummy_32k_clk_handler(pmu_clk_e clk_id)
{
    pmic_print_error("no pmic macro defined,use dummy!");
    return  0;
}
/*****************************************************************************
 �� �� ��  : dummy_irq_handler
 ��������  : mask,unmask pmu�а�����ģ���irq��׮����
 �������  : clk_id:32kʱ�ӱ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
void dummy_irq_mask_handler(unsigned int irq)
{
    pmic_print_error("no pmic macro defined,use dummy!");
}
/*****************************************************************************
 �� �� ��  : dummy_irq_handler
 ��������  : ��ѯpmu�а���ģ���ж��Ƿ����δ�׮����
 �������  : clk_id:32kʱ�ӱ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
int dummy_irq_state_handler(unsigned int irq)
{
    pmic_print_error("no pmic macro defined,use dummy!");
    return  0;
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����Ĭ�ϴ�׮����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
int dummy_irq_callback_register(unsigned int irq,pmufuncptr routine,void *data)
{
    pmic_print_error("no pmic macro defined,use dummy!");
    return  0;
}
/*****************************************************************************
 �� �� ��  : dummy_get_boot_state
 ��������  :ϵͳ����ʱ���pmu�Ĵ���״̬��Ĭ�ϴ�׮����
 �������  : void
 �������  : reset.log
 �� �� ֵ  : pmu�����ok
 ���ú���  :
 ��������  :ϵͳ��ά�ɲ�
*****************************************************************************/
int dummy_get_boot_state(void)
{
    pmic_print_error("no pmic macro defined,use dummy!");
    return  0;
}
/*****************************************************************************
 �� �� ��  : dummy_get_part_state
 ��������  :ϵͳ����ʱ���pmu��usb\��������״̬��Ĭ�ϴ�׮����
 �������  : void
 �������  : reset.log
 �� �� ֵ  : pmu�����ok
 ���ú���  :
 ��������  :��ŵ硢���ػ�
*****************************************************************************/
bool dummy_get_part_state(void)
{
    pmic_print_error("no pmic macro defined,use dummy!");
    return  0;
}
/*****************************************************************************
* �� �� ��  : dummy_dr_list_current
* ��������  :��ѯĳ·����Դָ����λ������׮��
* �������  :dr_id:����Դid�ţ�selector��Ҫ��ѯ�ĵ�λ��
* �������  :��
* ����ֵ��   ����ѯ�ĵ���Դָ����λ�ĵ���ֵ����λ��uA��
*
*****************************************************************************/
int dummy_dr_list_current(int dr_id, unsigned selector)
{
    pmic_print_error("no pmic macro defined,use dummy!");
    return  BSP_PMU_NO_PMIC;
}
/*****************************************************************************
* �� �� ��  : dummy_dr_set_mode
* ��������  :����ĳ·����Դģʽ��׮��
* �������  :dr_id:����Դid�ţ�mode�����õ�ģʽ��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int dummy_dr_set_mode(int dr_id, dr_mode_e mode)
{
    pmic_print_info("dr_id is %d,mode is %d!\n",dr_id,mode);
    pmic_print_error("no pmic macro defined,use dummy!");
    return  BSP_PMU_NO_PMIC;
}
/*****************************************************************************
* �� �� ��  : dummy_dr_get_mode
* ��������  :��ȡĳ·����Դģʽ��׮��
* �������  :dr_id:����Դid�ţ�
* �������  :��
* ����ֵ��   ����Դ��ǰģʽ
*
*****************************************************************************/
dr_mode_e dummy_dr_get_mode(int dr_id)
{
    pmic_print_info("dr_id is %d!\n",dr_id);
    pmic_print_error("no pmic macro defined,use dummy!");
    return  PMU_DRS_MODE_BUTTOM;
}
/*****************************************************************************
 �� �� ��  : dummy_dr_fla_time_set
 ��������  : DR��˸ʱ�����ã�Ĭ�ϴ�׮����
 �������  : void
 �������  : reset.log
 �� �� ֵ  : pmu�����ok
 ���ú���  :
 ��������  : LEDģ��
*****************************************************************************/
int dummy_dr_fla_time_set(DR_FLA_TIME* dr_fla_time_st)
{
    pmic_print_info("fla_on_us is %d,fla_off_us is %d!\n",\
        dr_fla_time_st->fla_on_us,dr_fla_time_st->fla_off_us);
    pmic_print_error("no pmic macro defined,use dummy!");
    return  BSP_PMU_NO_PMIC;
}
/*****************************************************************************
 �� �� ��  : dummy_dr_bre_time_set
 ��������  : DR����ʱ�����ã�Ĭ�ϴ�׮����
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�����ok
 ���ú���  :
 ��������  : LEDģ��
*****************************************************************************/
int dummy_dr_bre_time_set(dr_id_e dr_id, DR_BRE_TIME* dr_bre_time_st)
{
    pmic_print_info("on_ms is %d,off_ms is %d,rise_ms is %d,fall_ms is %d!\n",\
        dr_bre_time_st->bre_on_ms,dr_bre_time_st->bre_off_ms,dr_bre_time_st->bre_rise_ms,dr_bre_time_st->bre_fall_ms);
    pmic_print_error("no pmic macro defined,use dummy!");
    return  BSP_PMU_NO_PMIC;
}
/*****************************************************************************
 �� �� ��  : dummy_dr_bre_time_list
 ��������  : DR����ʱ�䵵λֵ��ȡ��Ĭ�ϴ�׮����
 �������  : void
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  : LEDģ��
*****************************************************************************/
unsigned dummy_dr_bre_time_list(dr_id_e dr_id, dr_bre_time_e bre_time_enum ,unsigned selector)
{
    pmic_print_info("no pmic macro defined,use dummy,dr_id %d,bre_time_enum %d,selector %d!\n",\
        dr_id,bre_time_enum,selector);
    return  BSP_PMU_NO_PMIC;
}
/*****************************************************************************
 �� �� ��  : dummy_dr_bre_time_list
 ��������  : DR����ʱ�䵵λ����ȡ��Ĭ�ϴ�׮����
 �������  : void
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  : LEDģ��
*****************************************************************************/
unsigned dummy_dr_bre_time_selectors_get(dr_id_e dr_id, dr_bre_time_e bre_time_enum)
{
    pmic_print_info("no pmic macro defined,use dummy,dr_id %d,bre_time_enum %d,selector %d!",dr_id,bre_time_enum);
    return  BSP_PMU_NO_PMIC;
}
/*****************************************************************************
 �� �� ��  : dummy_dr_bre_time_set
 ��������  : DR����ʱ�����ã�Ĭ�ϴ�׮����
 �������  : void
 �������  : reset.log
 �� �� ֵ  : pmu�����ok
 ���ú���  :
 ��������  : LEDģ��
*****************************************************************************/
int dummy_dr_start_delay_set(dr_id_e dr_id, unsigned delay_ms)
{
    pmic_print_info("dr_id is %d,delay_ms is %d!",dr_id,delay_ms);
    pmic_print_error("no pmic macro defined,use dummy!");
    return  BSP_PMU_NO_PMIC;
}
/*****************************************************************************
 �� �� ��  : dummy_sim_debtime_set
 ��������  : ����SIM���ж�ȥ��ʱ��Ĵ�׮����
 �������  : para:����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
int dummy_sim_debtime_set(u32 para)
{
    pmic_print_info("para is %d",para);
    pmic_print_error("no pmic macro defined,use dummy!");
    return  BSP_PMU_NO_PMIC;
}
void dummy_no_para_handler(void)
{
    pmic_print_info("no pmic macro defined,use dummy!");
}
#endif

#if defined(__VXWORKS__)
/*****************************************************************************
 �� �� ��  : dummy_pmu_init
 ��������  : ��ʼ��Ĭ�ϴ�׮����
 �������  : void
 �������  : ��
 �� �� ֵ  : �� 
 ���ú���  :
 ��������  : LEDģ��
*****************************************************************************/
s32 dummy_pmu_init(void)
{
    pmic_print_error("no pmic macro defined,use dummy!");
    return BSP_PMU_OK;
}

#endif
/*****************************************************************************
 �� �� ��  : dummy_info_get_handler
 ��������  : ��ѯPMU�汾�ŵĴ�׮����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
u8 dummy_info_get_handler(void)
{
    pmic_print_error("no pmic macro defined,use dummy!");
    return  0;
}
int dummy_sim_upres_disable(u32 para)
{
    pmic_print_info("para is %d",para);
    pmic_print_error("no pmic macro defined,use dummy!");
    return  BSP_PMU_NO_PMIC;
}

#if defined (CONFIG_PMIC_HI6451)
struct pmu_adp_ops pmu_adp_ops = {
#if defined(__KERNEL__)
    .get_boot_state = hi6451_get_boot_state,
    .clk_32k_enable = hi6451_32k_clk_enable,
    .clk_32k_disable = hi6451_32k_clk_disable,
    .clk_32k_is_enabled = hi6451_32k_clk_is_enabled,
    .usb_state_get = hi6451_usb_state_get,
    .key_state_get = hi6451_power_key_state_get,
    .irq_mask = dummy_irq_mask_handler,
    .irq_unmask = dummy_irq_mask_handler,
    .irq_is_masked = dummy_irq_state_handler,
    .irq_callback_register = hi6451_irq_callback_register,
    .dr_list_current = dummy_dr_list_current,
    .dr_set_mode = dummy_dr_set_mode,
    .dr_get_mode = dummy_dr_get_mode,
    .dr_fla_time_set = dummy_dr_fla_time_set,
    .dr_fla_time_get = dummy_dr_fla_time_set,
    .dr_bre_time_set = dummy_dr_bre_time_set,
    .dr_bre_time_get = dummy_dr_bre_time_set,
    .dr_bre_time_list = dummy_dr_bre_time_list,
    .dr_bre_time_selectors_get = dummy_dr_bre_time_selectors_get,
    .dr_start_delay_set = dummy_dr_start_delay_set,
    .sim_debtime_set = dummy_sim_debtime_set,
    .ldo22_res_enable = dummy_no_para_handler,
    .ldo22_res_disable = dummy_no_para_handler,
    .pmu_init = bsp_pmu_hi6451_init,
#endif
    .version_get = hi6451_version_get,
    .sim_upres_disable = dummy_sim_upres_disable,
#if defined(__VXWORKS__)
    .pmu_init = bsp_pmu_hi6451_init,
#endif
};

#elif defined (CONFIG_PMIC_HI6551)
struct pmu_adp_ops pmu_adp_ops = {
#if defined(__KERNEL__)
    .get_boot_state = hi6551_get_boot_state,
    .clk_32k_enable = hi6551_32k_clk_enable,
    .clk_32k_disable = hi6551_32k_clk_disable,
    .clk_32k_is_enabled = hi6551_32k_clk_is_enabled,
    .usb_state_get = hi6551_usb_state_get,
    .key_state_get = hi6551_power_key_state_get,
    .irq_mask = hi6551_irq_mask,
    .irq_unmask = hi6551_irq_unmask,
    .irq_is_masked = hi6551_irq_is_masked,
    .irq_callback_register = hi6551_irq_callback_register,
    .dr_list_current = bsp_hi6551_dr_list_current,
    .dr_set_mode = bsp_hi6551_dr_set_mode,
    .dr_get_mode = bsp_hi6551_dr_get_mode,
    .dr_fla_time_set = hi6551_dr_fla_time_set,
    .dr_fla_time_get = hi6551_dr_fla_time_get,
    .dr_bre_time_set = hi6551_dr_bre_time_set,
    .dr_bre_time_get = hi6551_dr_bre_time_get,
    .dr_bre_time_list = hi6551_dr_bre_time_list,
    .dr_bre_time_selectors_get = hi6551_dr_bre_time_selectors_get,
    .dr_start_delay_set = hi6551_dr_start_delay_set,
    .sim_debtime_set = hi6551_sim_deb_time_set,
    .ldo22_res_enable = hi6551_ldo22_res_enable,
    .ldo22_res_disable = hi6551_ldo22_res_disable,
#endif
    .version_get = hi6551_version_get,
    .sim_upres_disable = hi6551_sim_upres_disable,
#if defined(__VXWORKS__)
    .pmu_init = bsp_pmu_hi6551_init
#endif
};

#elif defined (CONFIG_PMIC_HI6559)
struct pmu_adp_ops pmu_adp_ops = {
#if defined(__KERNEL__)
    .get_boot_state = hi6559_get_boot_state,
    .clk_32k_enable = hi6559_32k_clk_enable,
    .clk_32k_disable = hi6559_32k_clk_disable,
    .clk_32k_is_enabled = hi6559_32k_clk_is_enabled,
    .usb_state_get = hi6559_usb_state_get,
    .key_state_get = hi6559_power_key_state_get,
    .irq_mask = hi6559_irq_mask,
    .irq_unmask = hi6559_irq_unmask,
    .irq_is_masked = hi6559_irq_is_masked,
    .irq_callback_register = hi6559_irq_callback_register,
    .dr_list_current = bsp_hi6559_dr_list_current,
    .dr_set_mode = bsp_hi6559_dr_set_mode,
    .dr_get_mode = bsp_hi6559_dr_get_mode,
    .dr_fla_time_set = hi6559_dr_fla_time_set,
    .dr_fla_time_get = hi6559_dr_fla_time_get,
    .dr_bre_time_set = hi6559_dr_bre_time_set,
    .dr_bre_time_get = hi6559_dr_bre_time_get,
    .dr_bre_time_list = hi6559_dr_bre_time_list,
    .dr_bre_time_selectors_get = hi6559_dr_bre_time_selectors_get,
    .dr_start_delay_set = hi6559_dr_start_delay_set,
    .sim_debtime_set = hi6559_sim_deb_time_set,
    .ldo22_res_enable = hi6559_ldo22_res_enable,
    .ldo22_res_disable = hi6559_ldo22_res_disable,
#endif
    .version_get = hi6559_version_get,
    .sim_upres_disable = hi6559_sim_upres_disable,
#if defined(__VXWORKS__)
    .pmu_init = bsp_pmu_hi6559_init,
    .apt_enable = bsp_pmu_hi6559_apt_enable,
    .apt_disable = bsp_pmu_hi6559_apt_disable,
    .apt_status_get = bsp_pmu_hi6559_apt_status_get,
#endif
};

#else
struct pmu_adp_ops pmu_adp_ops = {
#if defined(__KERNEL__)
    .get_boot_state = dummy_get_boot_state,
    .clk_32k_enable = dummy_32k_clk_handler,
    .clk_32k_disable = dummy_32k_clk_handler,
    .clk_32k_is_enabled = dummy_32k_clk_handler,
    .usb_state_get = dummy_get_part_state,
    .key_state_get = dummy_get_part_state,
    .irq_mask = dummy_irq_mask_handler,
    .irq_unmask = dummy_irq_mask_handler,
    .irq_is_masked = dummy_irq_state_handler,
    .irq_callback_register = dummy_irq_callback_register,
    .dr_list_current = dummy_dr_list_current,
    .dr_set_mode = dummy_dr_set_mode,
    .dr_get_mode = dummy_dr_get_mode,
    .dr_fla_time_set = dummy_dr_fla_time_set,
    .dr_fla_time_get = dummy_dr_fla_time_set,
    .dr_bre_time_set = dummy_dr_bre_time_set,
    .dr_bre_time_get = dummy_dr_bre_time_set,
    .dr_bre_time_list = dummy_dr_bre_time_list,
    .dr_bre_time_selectors_get = dummy_dr_bre_time_selectors_get,
    .dr_start_delay_set = dummy_dr_start_delay_set,
    .sim_debtime_set = dummy_sim_debtime_set,
    .ldo22_res_enable = dummy_no_para_handler,
    .ldo22_res_disable = dummy_no_para_handler,
#endif
    .version_get = dummy_info_get_handler,
    .sim_upres_disable = dummy_sim_upres_disable,
#if defined(__VXWORKS__)
    .pmu_init = dummy_pmu_init,
#endif
};
#endif /* #if defined (CONFIG_PMIC_HI6451) */

/*���º���ֻ��Acore���ṩ*/
#if defined(__KERNEL__)
/*****************************************************************************
 �� �� ��  : bsp_pmu_get_boot_state
 ��������  :ϵͳ����ʱ���pmu�Ĵ���״̬��
                ȷ���Ƿ�����pmu���������
 �������  : void
 �������  : reset.log
 �� �� ֵ  : pmu�����ok
 ���ú���  :
 ��������  :ϵͳ��ά�ɲ�
*****************************************************************************/
int bsp_pmu_get_boot_state(void)
{
    return  pmu_adp_ops.get_boot_state();
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_32k_clk_enable
 ��������  : ����pmu��32kʱ��
 �������  : clk_id:32kʱ�ӱ��
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_32k_clk_enable(pmu_clk_e clk_id)
{
    return  pmu_adp_ops.clk_32k_enable(clk_id);
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_32k_clk_disable
 ��������  : �ر�pmu��32kʱ��
 �������  : clk_id:32kʱ�ӱ��
 �������  : ��
 �� �� ֵ  : �رճɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_32k_clk_disable(pmu_clk_e clk_id)
{
    return  pmu_adp_ops.clk_32k_disable(clk_id);
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_32k_clk_is_enabled
 ��������  : ��ѯpmu��32kʱ���Ƿ���
 �������  : clk_id:32kʱ�ӱ��
 �������  : ��
 �� �� ֵ  : ������ر�
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_32k_clk_is_enabled(pmu_clk_e clk_id)
{
    return  pmu_adp_ops.clk_32k_is_enabled(clk_id);
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_version_get
 ��������  : ��ȡusb�Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : usb�����γ�
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool bsp_pmu_usb_state_get(void)
{
    return  pmu_adp_ops.usb_state_get();
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_key_state_get
 ��������  : ��ȡpower�����Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : usb�����γ�
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool bsp_pmu_key_state_get(void)
{
    return  pmu_adp_ops.key_state_get();
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
void bsp_pmu_irq_mask(unsigned int irq)
{
    pmu_adp_ops.irq_mask(irq);
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
void bsp_pmu_irq_unmask(unsigned int irq)
{
    pmu_adp_ops.irq_unmask(irq);
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
int bsp_pmu_irq_is_masked(unsigned int irq)
{
    return  pmu_adp_ops.irq_is_masked(irq);
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
int bsp_pmu_irq_callback_register(unsigned int irq,pmufuncptr routine,void *data)
{
    return  pmu_adp_ops.irq_callback_register(irq,routine,data);
}
/*****************************************************************************
* �� �� ��  : bsp_dr_list_current
* ��������  :��ѯĳ·����Դָ����λ������
* �������  :dr_id:����Դid�ţ�selector��Ҫ��ѯ�ĵ�λ��
* �������  :��
* ����ֵ��   ����ѯ�ĵ���Դָ����λ�ĵ���ֵ����λ��uA��
*
*****************************************************************************/
int bsp_dr_list_current(int dr_id, unsigned selector)
{
    return  pmu_adp_ops.dr_list_current(dr_id,selector);
}
/*****************************************************************************
* �� �� ��  : bsp_pmu_dr_set_mode
* ��������  :����ĳ·����Դģʽ��
* �������  :dr_id:����Դid�ţ�mode�����õ�ģʽ��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_dr_set_mode(int dr_id, dr_mode_e mode)
{
    return  pmu_adp_ops.dr_set_mode(dr_id,mode);
}
/*****************************************************************************
* �� �� ��  : bsp_hi6551_dr_get_mode
* ��������  :��ȡĳ·����Դģʽ��
* �������  :dr_id:����Դid�ţ�
* �������  :��
* ����ֵ��   ����Դ��ǰģʽ
*
*****************************************************************************/
dr_mode_e bsp_dr_get_mode(int dr_id)
{
    return  pmu_adp_ops.dr_get_mode(dr_id);
}
/*****************************************************************************
 �� �� ��  : bsp_dr_fla_time_set
 ��������  : ����dr����˸����ʱ�� �� ����ʱ��
 �������  : dr_fla_time_st:��˸ʱ������ṹ��;��λ:us
 �������  : ��
 �� �� ֵ  : ���óɹ�����ʧ��
 ���ú���  :
*****************************************************************************/
/*����ʱ������dr1/2*/
int bsp_dr_fla_time_set(DR_FLA_TIME *dr_fla_time_st)
{
    return  pmu_adp_ops.dr_fla_time_set(dr_fla_time_st);
}
/*****************************************************************************
 �� �� ��  : bsp_dr_fla_time_set
 ��������  : ��ȡdr����˸����ʱ�� �� ����ʱ��
 �������  : dr_fla_time_st:��˸ʱ������ṹ��;��λ:us
 �������  : ��
 �� �� ֵ  : ���óɹ�����ʧ��
 ���ú���  :
*****************************************************************************/
/*����ʱ������dr1/2*/
int bsp_dr_fla_time_get(DR_FLA_TIME *dr_fla_time_st)
{
    return  pmu_adp_ops.dr_fla_time_get(dr_fla_time_st);
}
/*****************************************************************************
 �� �� ��  : bsp_dr_bre_time_set
 ��������  : ����dr�ĺ���ʱ��(��������������������������ʱ��)
 �������  : dr_id:Ҫ���õĵ���Դ���;dr_bre_time_st:����ʱ������ṹ��;
            û���ҵ����õ�ʱ�䣬������Ϊ����
 �������  : ��
 �� �� ֵ  : ���óɹ�����ʧ��
 ���ú���  :
 ��ע˵��  : ��Ӧ�Ĵ���ֻ������ʱ��Ĺ��ܣ�����Ҫ������
*****************************************************************************/
int bsp_dr_bre_time_set(dr_id_e dr_id, DR_BRE_TIME *dr_bre_time_st)
{
    return  pmu_adp_ops.dr_bre_time_set(dr_id,dr_bre_time_st);
}
/*****************************************************************************
 �� �� ��  : bsp_dr_bre_time_list
 ��������  : ����dr�ĺ���ʱ��(��������������������������ʱ��)����λ��ʱ��ֵ
 �������  : dr_id:Ҫ��ѯ�ĵ���Դ���;bre_time_enum:��Ҫ��ѯ��ʱ������;
             selector��ʱ�䵵λ
 �������  : ��
 �� �� ֵ  : ��λʱ��
 ���ú���  :
 ��ע˵��  :
*****************************************************************************/
unsigned bsp_dr_bre_time_list(dr_id_e dr_id, dr_bre_time_e bre_time_enum ,unsigned selector)
{
    return  pmu_adp_ops.dr_bre_time_list(dr_id,bre_time_enum,selector);
}
/*****************************************************************************
 �� �� ��  : bsp_dr_bre_time_selectors_get
 ��������  : ��ȡdr ����ʱ���ܹ���λֵ
 �������  : dr_id:Ҫ���õĵ���Դ���;bre_time_enum:��Ҫ��ѯ��ʱ������;
 �������  : ��
 �� �� ֵ  : ��λʱ��
 ���ú���  :
 ��ע˵��  :
*****************************************************************************/
unsigned bsp_dr_bre_time_selectors_get(dr_id_e dr_id, dr_bre_time_e bre_time_enum)
{
    return  pmu_adp_ops.dr_bre_time_selectors_get(dr_id,bre_time_enum);
}
/*****************************************************************************
 �� �� ��  : bsp_dr_start_delay_set
 ��������  : ����dr��������ʱʱ��
 �������  : dr_id:Ҫ���õĵ���Դ���;delay_ms:������ʱ��ʱ�䣬��λ:ms
             ���÷�Χ:[0 , 32768]ms
 �������  : ��
 �� �� ֵ  : ���óɹ���ʧ��
 ���ú���  :
 ��ע˵��  : ��Ӧ�Ĵ���ֻ������ʱ��Ĺ��ܣ�����Ҫ��������ֻ��DR3/4/5�д˹���
*****************************************************************************/
int bsp_dr_start_delay_set(dr_id_e dr_id, unsigned delay_ms)
{
    return  pmu_adp_ops.dr_start_delay_set(dr_id,delay_ms);
}
/*****************************************************************************
 �� �� ��  : bsp_pmu_sim_debtime_set
 ��������  : ����sim��ȥ��ʱ��
 �������  : uctime:ȥ��ʱ��
 �������  : ��
 �� �� ֵ  : ���óɹ���ʧ��
 ���ú���  :
 ��ע˵��  :
*****************************************************************************/
int bsp_pmu_sim_debtime_set(u32 uctime)
{
   return  pmu_adp_ops.sim_debtime_set(uctime);
}

void bsp_pmu_ldo22_res_enable(void)
{
   pmu_adp_ops.ldo22_res_enable();
}
void bsp_pmu_ldo22_res_disable(void)
{
   pmu_adp_ops.ldo22_res_disable();
}
#endif

/*���º���ֻ��Ccore\Mcore��FASTBOOT���ṩ*/
#if defined(__VXWORKS__)

/*****************************************************************************
 �� �� ��  : bsp_pmu_init
 ��������  :ϵͳ������ʼ��pmu����ź���
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :ccoreϵͳ��ʼ������
*****************************************************************************/
void bsp_pmu_init(void)
{
    pmu_adp_ops.pmu_init();
}

int bsp_sim_upres_disable(u32 sim_id)
{
    return  pmu_adp_ops.sim_upres_disable(sim_id); 
}
 
/*****************************************************************************
 ����	: bsp_pmu_apt_enable
 ����	: ͨ��ģ��ʹ��APT״̬�ӿ�
 ����	: ��
 ���	: ��
 ����	: 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 bsp_pmu_apt_enable(void)
{
    return pmu_adp_ops.apt_enable();
}

/*****************************************************************************
 ����	: bsp_pmu_apt_enable
 ����	: ͨ��ģ��ʹ��APT״̬�ӿ�
 ����	: ��
 ���	: ��
 ����	: 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 bsp_pmu_apt_disable(void)
{
    return pmu_adp_ops.apt_disable();
}

/*****************************************************************************
 ����	: bsp_pmu_apt_status_get
 ����	: ͨ��ģ���ȡ��ǰAPT״̬�ӿ�
 ����	: ��
 ���	: ��
 ����	: 1  APTʹ��/   0    APTδʹ��/  -1    ��ȡʧ��
*****************************************************************************/
s32 bsp_pmu_apt_status_get(void)
{
    return pmu_adp_ops.apt_status_get();
}

#endif
/*���º�����Acore\Ccore\Mcore\FASTBOOT�о��ṩ*/
/*****************************************************************************
 �� �� ��  : bsp_pmu_version_get
 ��������  : ��ȡpmu�汾��
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ���ú���  :
 ��������  : ����hso��msp����
*****************************************************************************/
u8 bsp_pmu_version_get(void)
{
    return pmu_adp_ops.version_get();
}

