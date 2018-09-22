
#ifndef _BSP_LOWPOWER_MNTN_H_
#define _BSP_LOWPOWER_MNTN_H_
#include <product_config.h>
#include <bsp_hardtimer.h>
#include <bsp_om.h>
#include <bsp_nvim.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include <osl_irq.h>
#include <hi_syscrg_interface.h>
#include <hi_pwrctrl.h>
#include <bsp_dump.h>
#include <osl_spinlock.h>
#include <bsp_memmap.h>
#include <soc_interrupts_comm.h>


#if (FEATURE_ON == MBB_COMMON)
/*each core has lock numbers --MAX_LOCK_NUM_CORE */
#if defined(__KERNEL__)
#define MAX_LOCK_NUM_CORE    38
#else
#define MAX_LOCK_NUM_CORE    32
#endif
#else
#define MAX_LOCK_NUM_CORE    32
#endif /*(FEATURE_ON == MBB_COMMON) && defined(__KERNEL__)*/

/*max lock name*/
#define MAX_LOCK_LEN   32

/*This structure is used for saving Msg from all wakelocks and opposing sleep IP*/
struct lock_status{
	char  name[MAX_LOCK_LEN];
	unsigned int status;                                 /*1: means oppose sleep*/
};

struct lock_info{
	struct lock_status lock_lookup[MAX_LOCK_NUM_CORE];
};

/* ��¼�����DUMP�ڴ���Ϣ�Ľṹ�� */
struct lp_dump_mem_info
{
    unsigned int lp_dump_base_addr;
    unsigned int lp_dump_base_addr_legth;
    unsigned int lp_current_legth;
#if defined(__KERNEL__)||defined(__VXWORKS__)
    spinlock_t	spinlock;
#endif
};

/*
*�˽ṹ������HSO��ʾ��Ϣʹ��
*[0]for earlysuspend
*[1]for dpm,the others for wakelock
*/
extern struct lock_info hi6930_lockinfo;
/*******************************************************
*��¼�͹���NVȫ�ֱ���
********************************************************/
extern ST_PWC_SWITCH_STRU g_nv_pwc_switch;

/*��¼�͹��Ĺ����ַ*/
extern unsigned int g_lowpower_shared_addr;

/*******************************************************
*�˺����ṩ���ڻ�ȡNV������
********************************************************/
void bsp_lowpower_mntn_init(void);

/*******************************************************
*�˺����ṩ����adp_dpm.c ��ȡNV������Ϣ
********************************************************/
void  bsp_adp_dpm_debug_init(void);

/*******************************************************
*�˺����ṩ����adp_dpm.c ��ʾdebug��Ϣ
********************************************************/
void debug_adp_dpm(void);
void debug_pastar_dpm(void);

/*******************************************************
*�˺����ṩ���ڳ�ʼ���͸������ŵ�ʱ���
********************************************************/
void update_awake_time_stamp(void);

/*******************************************************
*�˺��������ж�������ʱ���Ƿ�ʱ�����ϱ�
********************************************************/
void check_awake_time_limit(void);

/***********************************************************************
*����:������ҳΪ��λ�Ŀռ�
*���:
*bytes: ��Ҫ���ֽ���,
*refcount:������ü���
*����:�ɹ�Ϊ�׵�ַ��ʧ��ΪNULL
************************************************************************/
void* dmem_malloc(unsigned int bytes, unsigned int *refcount);

/***********************************************************************
*����:�ͷſռ�
*���:�ռ��ַָ��
*����:��
************************************************************************/
void dmem_free(void* p);

/***********************************************************************
*����:������ҳΪ��λ�Ŀռ䣬���޸�ҳ������ΪNO CACHE
*���:
*bytes: ��Ҫ���ֽ���,
*refcount:������ü���
*����:�ɹ�Ϊ�׵�ַ��ʧ��ΪNULL
************************************************************************/
void* dmem_cache_dma_malloc(unsigned int bytes, unsigned int *refcount);

/***********************************************************************
*����:�ͷſռ䣬���޸�ҳ������
*���:
*����:�޸����Գɹ�Ϊ0  ʧ��Ϊ1
************************************************************************/
STATUS dmem_cache_dma_free(void* p);

/***********************************************************************
*����:�޸�ҳ������Ϊֻ��
*���:
*p:�ռ��ַָ��
*refcount:������ü���
*����:�ɹ�Ϊ0 ʧ��Ϊ-1
************************************************************************/
STATUS dmem_lock(void* p, unsigned int *refcount);

/***********************************************************************
*����:�޸�ҳ������Ϊ��д
*���:
*p:�ռ��ַָ��
*refcount:������ü���
*����:�ɹ�Ϊ0 ʧ��Ϊ-1
************************************************************************/
STATUS dmem_unlock(void* p, unsigned int *refcount);

/***********************************************************************
*����:DRV�ڲ��������ڴ�BBP PLL(for cipher K3V3)
*���:����ģ���벻Ҫ���ô˺���
*����:�ɹ�Ϊ0 ʧ��Ϊ1
************************************************************************/
int bsp_bbp_pll_enable(void);

/***********************************************************************
*����:DRV�ڲ��������ڹر�BBP PLL(for cipher K3V3)
*���:����ģ���벻Ҫ���ô˺���
*����:�ɹ�Ϊ0 ʧ��Ϊ1
************************************************************************/
int bsp_bbp_pll_disable(void);

/***********************************************************************
*����:���ڱ���SOC�ĵ͹��ļĴ�����PMU\PASTAR�ļĴ���ֵ
*��dump�ڴ���
*���:��
*����:��
************************************************************************/
void bsp_save_lowpower_status(void);

/***********************************************************************
*����:���ڵ������һ�α����SOC�ĵ͹��ļĴ�����
*PMU\PASTAR�ļĴ���ֵ
*���:��
*����:��
************************************************************************/
void bsp_dump_lowpower_status(void);

/***********************************************************************
*����:���ڵ���ʵʱ��SOC�ĵ͹��ļĴ�����
*PMU\PASTAR�ļĴ���ֵ
*���:��
*����:��
************************************************************************/
void bsp_show_lowpower_status(void);

/***********************************************************************
*����:������¼�����һ�α���Ĺ�����Ϣ
*���:��
*����:��
************************************************************************/
void bsp_dump_bus_error_status(void);
#endif

