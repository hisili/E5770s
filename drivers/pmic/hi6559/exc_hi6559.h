#ifndef __HI6559_EXC_H
#define __HI6559_EXC_H

#include <linux/workqueue.h>
#include <bsp_om.h>

#define HI6559_OTMP_125_OFFSET                  0
#define HI6559_OTMP_150_OFFSET                  7
#define HI6559_VSYS_UNDER_2P5_OFFSET            2
#define HI6559_VSYS_UNDER_2P85_OFFSET           3
#define HI6559_VSYS_OVER_6P0_OFFSET             4
#define HI6559_POWER_KEY_4S_PRESS_OFFSET        5
#define HI6559_POWER_KEY_20MS_RELEASE_OFFSET    6
#define HI6559_POWER_KEY_20MS_PRESS_OFFSET      7
#define HI6559_NP_SCP_RECORD1_CONT_NUM          3   /* �Ĵ���0x18��Чbit���� */
#define HI6559_NP_OCP_RECORD1_CONT_NUM          5   /* �Ĵ���0x19��Чbit���� */
#define HI6559_NP_OCP_RECORD2_CONT_NUM          5   /* �Ĵ���0x1A��Чbit���� */
#define HI6559_NP_OCP_RECORD3_CONT_NUM          6   /* �Ĵ���0x1B��Чbit���� */
#define HI6559_NP_OCP_RECORD4_CONT_NUM          3   /* �Ĵ���0x1C��Чbit���� */
#define HI6559_LVS07_BIT_OFFSET                 5   /* LVS07����bit�ڼĴ����ڵ�ƫ�� */
#define HI6559_LVS09_BIT_OFFSET                 0   /* LVS07����bit�ڼĴ����ڵ�ƫ�� */
#define PMU_MODULE_ID                           BSP_MODU_PMU

typedef unsigned long hi6559_excflags_t;

struct hi6559_exc_data{
    spinlock_t      lock;
    struct workqueue_struct *hi6559_om_wq;
    struct delayed_work hi6559_om_wk;
};

/* �Ĵ��������� */
struct hi6559_reg_cont{
    u32 bit_ofs;        /* bitλƫ�� */
    u32 volt_id;        /* ��ѹԴID */
    char *cont;           /* bitλ���� */
};

#endif
