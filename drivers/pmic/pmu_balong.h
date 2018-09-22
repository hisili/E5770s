
#ifndef _PMU_H_
#define _PMU_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <bsp_pmu.h>

struct pmu_dbg_ops{
    void (*pmu_volt_show)(int volt_id);/*����PMICͳһ����*/
    void (*pmu_volt_state)(void);
    void (*pmu_om_data_show)(void);
    void (*pmu_om_boot_show)(void);
    void (*pmu_exc_state)(void);
    void (*pmu_pmic_info)(void);
};
struct pmu_dbg
{
    u32 info_print_sw;
    struct pmu_dbg_ops dbg_ops[PMIC_BUTTOM];
};
extern struct pmu_dbg g_pmu_dbg;


/*test*/
struct pmu_test_ops{
    int (*pmu_volt_onoff_test)(u32 uctimes);/*��ѹԴ���ز���*/
    int (*pmu_volt_setget_test)(u32 uctimes);/*��ѹԴ���õ�ѹ����*/
    int (*pmu_volt_mode_test)(u32 uctimes);/*��ѹԴ����ecoģʽ����*/
    int (*pmu_mutex_onecore_test)(u32 uctimes);/*���ڻ������*/
    int (*pmu_mutex_cores_test)(u32 uctimes);/*�˼以�����*/
    int (*pmu_volt_table_test)(u32 uctimes);/*ddr��ѹ��ȫ�Բ���*/
    int (*pmu_dr_onoff_test)(u32 uctimes);/*����Դ���ز���*/
    int (*pmu_dr_setget_test)(u32 uctimes);/*����Դ���õ�������*/
    int (*pmu_dr_mode_test)(u32 uctimes);/*����Դ����ģʽ����*/
};
struct pmu_test
{
    u32 test_sw;
    struct pmu_test_ops test_ops[PMIC_BUTTOM];
};

/*print*/
#if defined(__KERNEL__) || defined(__VXWORKS__)
#define  pmic_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PMU, "[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
/*#define  pmic_print_info(fmt, ...)      (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_PMU, "[pmu]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))*/

#elif defined(__CMSIS_RTOS)
extern void printk(const char *fmt, ...);
#define  pmic_print_error(fmt, ...)    (printk("[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
/*#define  pmic_print_info(fmt, ...)      (printk("[pmu]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))*/
#elif defined(__FASTBOOT__)
/*#define  pmic_print_error(fmt, ...)    (cprintf(fmt"\n", ...))*/
#define  pmic_print_error(fmt, ...)    (cprintf("[pmu]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#endif

#if defined(__FASTBOOT__)
#define  pmic_print_info(fmt, ...) \
do {                               \
    /*    pmic_print_error(fmt, ##__VA_ARGS__);*/\
} while (0)
#else
#define  pmic_print_info(fmt, ...) \
do {                               \
    if (g_pmu_dbg.info_print_sw)    \
        pmic_print_error(fmt, ##__VA_ARGS__);\
} while (0)
#endif

/*��������*/
/*****************************************************************************
 �� �� ��  : bsp_pmu_dbg_register
 ��������  : pmuģ��dbg��Ϣע��
 �������  : void
 �������  : ��
 �� �� ֵ  : ע��ɹ���ʧ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_pmu_dbg_register(pmic_id_e pmic_id,struct pmu_dbg_ops ops_func);
/*****************************************************************************
 �� �� ��  : bsp_pmu_test_register
 ��������  : pmuģ��test��Ϣע��
 �������  : void
 �������  : ��
 �� �� ֵ  : ע��ɹ���ʧ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_pmu_test_register(pmic_id_e pmic_id,struct pmu_test_ops ops_func);

#ifdef CONFIG_PMIC_HI6451
/*****************************************************************************
 �� �� ��  : bsp_hi6451_debug_init
 ��������  : hi6451 debugģ��ĳ�ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6451_debug_init(void);
/*****************************************************************************
 �� �� ��  : bsp_hi6451_test_init
 ��������  : hi6451 testģ��ĳ�ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ����
*****************************************************************************/
int bsp_hi6451_test_init(void);
#if defined(__KERNEL__)
extern int hi6451_get_boot_state(void);
#endif
#endif
#ifdef CONFIG_PMIC_HI6551
/*�쳣�洢����*/
extern  u8 pmu_hi6551_om_boot[];
extern  u8 pmu_hi6551_om_data[];
/*****************************************************************************
 �� �� ��  : bsp_hi6551_debug_init
 ��������  : hi6551 debugģ��ĳ�ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6551_debug_init(void);
/*****************************************************************************
 �� �� ��  : bsp_hi6551_test_init
 ��������  : hi6551 testģ��ĳ�ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
int bsp_hi6551_test_init(void);
//void bsp_hi6551_sim_volt_disable(u32 sim_id);
int hi6551_sim_upres_disable(u32 sim_id);


#if defined(__KERNEL__)
extern int hi6551_get_boot_state(void);
#endif
#endif

#ifdef CONFIG_PMIC_HI6559
/* �쳣�洢���� */
extern  u8 pmu_hi6559_om_boot[];
extern  u8 pmu_hi6559_om_data[];
/*****************************************************************************
 �� �� ��  : bsp_hi6559_debug_init
 ��������  : hi6559 debugģ��ĳ�ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void bsp_hi6559_debug_init(void);

/*****************************************************************************
 �� �� ��  : bsp_hi6559_test_init
 ��������  : hi6559 testģ��ĳ�ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 bsp_hi6559_test_init(void);

/*****************************************************************************
 �� �� ��  : hi6559_sim_upres_disable
 ��������  : 
 �������  : @sim_id:sim��ID
 �������  : ��
 �� �� ֵ  : 
*****************************************************************************/
s32 hi6559_sim_upres_disable(u32 sim_id);


#if defined(__KERNEL__)
extern int hi6559_get_boot_state(void);
#endif
#endif


#if (defined(CONFIG_PASTAR) && defined(__VXWORKS__))
/*****************************************************************************
 �� �� ��  : bsp_hi6561_test_init
 ��������  : hi6561 testģ��ĳ�ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6561_test_init(void);
#endif
#ifdef __cplusplus
}
#endif

#endif /* end #define _PMU_TEST_H_*/

