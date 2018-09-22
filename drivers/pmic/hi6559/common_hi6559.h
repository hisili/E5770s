#ifndef __COMMON_HI6559_H
#define __COMMON_HI6559_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "bsp_pmu.h"

typedef unsigned long hi6559_commflags_t;

#define PMU_HI6559_POWER_KEY_MASK                   (1 << 5)   /* Bit 5 for Power key */
#define PMU_HI6559_USB_STATE_MASK                   (1 << 5)
#define PMU_HI6559_HRESET_STATE_MASK                (1 << 1)
#define PMU_HI6559_BACKBAT_CHARGER_ENABLE_OFFSET    2       /* 0x11F�Ĵ���bit2 */
#define PMU_HI6559_BACKBAT_CHARGER_VOLT_NUM         3       /* 0x11F�Ĵ���bit0~bit1 */
#define PMU_HI6559_LONGPOWERKEY_TIME_MAX            11      /* 0x11E�Ĵ���bit2~bit0 */
#define PMU_HI6559_LONGPOWERKEY_TIME_MIN            6       /* 0x11E�Ĵ���bit2~bit0 */
#define PMU_HI6559_LONGPOWERKEY_TIME_MASK           7       /* 0x11E�Ĵ���bit2~bit0 */
#define PMU_HI6559_LONGPOWERKEY_OFF_MASK_OFS        3       /* 0x11E�Ĵ���bit3 */
#define PMU_HI6559_LONGPOWERKEY_REBOOT_MASK_OFS     6       /* 0x11E�Ĵ���bit6 */
#define PMU_HI6559_SIM_DEB_SEL_MASK                 0x1F    /* 0x43�Ĵ���bit0~bit4 */
#define PMU_HI6559_SIM_DEB_TIME_MIN                 120     /* 0x43�Ĵ���bit0~bit4��SIM��ȥ��ʱ����Сֵ����λus */
#define PMU_HI6559_SIM_DEB_TIME_MAX                 600     /* 0x43�Ĵ���bit0~bit4��SIM��ȥ��ʱ�����ֵ����λus */
#define PMU_HI6559_SIM_DEB_TIME_STEP                30      /* SIM��ȥ��ʱ��������λus */

#define HI6559_NP_OCP_SCP_REG_NUM                   7       /* ���µ����/��·��¼�Ĵ����������Ĵ���0x18~0x1E */

/*��������*/
#if defined(__KERNEL__)
s32  hi6559_32k_clk_enable(pmu_clk_e clk_id);
s32  hi6559_32k_clk_disable(pmu_clk_e clk_id);
s32  hi6559_32k_clk_is_enabled(pmu_clk_e clk_id);
bool hi6559_usb_state_get(void);
bool hi6559_power_key_state_get(void);
s32  hi6559_sim_deb_time_set(u32 uctime);
void hi6559_ldo22_res_enable(void);
void hi6559_ldo22_res_disable(void);
#endif

u8 hi6559_version_get(void);
void bsp_hi6559_common_init(void);

#ifdef __cplusplus
}
#endif
#endif
