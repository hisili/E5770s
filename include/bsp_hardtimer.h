#ifndef __BSP_HARDTIMER_H__
#define __BSP_HARDTIMER_H__
#include <hi_base.h>
#include <bsp_memmap.h>
#include <hi_timer.h>
#include <hi_syscrg.h>
#include <hi_bbp_systime.h>

#ifdef CONFIG_USE_TIMER_STAMP
#define TIMER_STAMP_ADDR        (HI_TIMER_05_REGBASE_ADDR_VIRT+HI_TIMER_CURRENTVALUE_OFFSET)
#define TIMER_STAMP_ADDR_PHY    (HI_TIMER_05_REGBASE_ADDR+HI_TIMER_CURRENTVALUE_OFFSET)
#else
#define TIMER_STAMP_ADDR        (HI_BBP_SYSTIME_BASE_ADDR_VIRT+HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET)
#define TIMER_STAMP_ADDR_PHY    (HI_BBP_SYSTIME_BASE_ADDR +HI_BBP_SYSTIME_ABS_TIMER_L_OFFSET)
#endif

#define TIMER_STAMP_FREQ        (0x8000)

#ifndef __ASSEMBLY__
#include <osl_common.h>
#include <osl_math64.h>
#include <drv_timer.h>
#include <soc_clk.h>
#include <product_config.h>
#include <soc_timer.h>
#ifdef __KERNEL__
#define timer_func irq_handler_t
#elif defined(__VXWORKS__)
#define timer_func VOIDFUNCPTR
#endif
#define  hardtimer_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HARDTIMER, "[hardtimer]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))
#if defined(__KERNEL__)||defined(__VXWORKS__)
struct bsp_hardtimer_control
{
	u32 timerId;
	u32 mode;
	u32 timeout;
	timer_func func;
	u32 para;
	DRV_TIMER_UNIT unit; /*������λ*/
};
#endif
/*****************************************************************************
* �� �� ��  :bsp_get_slice_value
*
* ��������  : ��ȡʱ���
*
* �������  :  ��
* �������  : ��
*
* �� �� ֵ  : ʱ�����ʱ������ֵ��ֻ��p531 asic�Ϸ���timerʱ�����
*                        ��������ϵͳ������32k ʱ���������
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

static inline u32 bsp_get_slice_value(void)
{
#ifdef CONFIG_USE_TIMER_STAMP
	return 0xFFFFFFFF-readl((const volatile void *)TIMER_STAMP_ADDR);
#else
#ifdef __KERNEL__
	return readl((const volatile void *)TIMER_STAMP_ADDR);
#else
	return readl(TIMER_STAMP_ADDR);
#endif
#endif
}
/*****************************************************************************
* �� �� ��  :bsp_get_slice_value_hrt
*
* ��������  : ��ȡ19.2M �߾���ʱ���
*
* �������  :  ��
* �������  : ��
*
* �� �� ֵ  : 19.2M ʱ���������
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

static inline u32 bsp_get_slice_value_hrt(void)
{
	return __bsp_get_slice_value_hrt();
}

/*****************************************************************************
* �� �� ��  :get_timer_slice_delta
*
* ��������  : ����ʱ��ֱ�ӻ�ȡʱ���ǰ���ֵ
*
* �������  :  begin:��ʼʱ���
					     end  :����ʱ���
* �������  : ��
*
* �� �� ֵ  : ʱ���ǰ���ֵ����λΪ1
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

#define get_timer_slice_delta(begin,end) ((end>=begin)?(end-begin):(0xFFFFFFFF-begin+end))

/*****************************************************************************
* �� �� ��  :bsp_get_elapse_ms
*
* ��������  : ����ʱ���Ժ���Ϊ��λ����ϵͳ��������ǰʱ��
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ  : �Ժ���Ϊ��λ�Ĵ�ϵͳ��������ǰ�����ŵ�ʱ��
*
* �޸ļ�¼  :  2013��6��20��   lixiaojie
*****************************************************************************/

static inline u32 bsp_get_elapse_ms(void)
{
	u64 tmp=0;
	unsigned long timer_get = 0;
	timer_get = bsp_get_slice_value();
	tmp = (u64)(timer_get & 0xFFFFFFFF);
	tmp = tmp*1000;
	tmp = div_u64(tmp,HI_TIMER_STAMP_CLK);
	return (u32)tmp;
}
/*****************************************************************************
* �� �� ��  :udelay
*
* ��������  : ΢����ʱ
*
* �������  : delay_us
* �������  : ��
*
* �� �� ֵ  :
* �޸ļ�¼  :  2013��6��20��   lixiaojie
*****************************************************************************/
/*K3 LPM3���Դ���udelay*/
#ifdef OS_K3V3_USE_LPM3_API
#if defined(__VXWORKS__)
static inline void udelay(u32 delay_us )
{
	u32 begin = 0,end=0,delta = 0;
	delta = delay_us*(UDELAY_TIMER_CLK/1000000);
	begin = readl(UDELAY_CURTIME_ADDR);
	begin = readl(UDELAY_CURTIME_ADDR);
	do{
		end = readl(UDELAY_CURTIME_ADDR);
	}while(get_timer_slice_delta(begin,end)<delta);
	return;
}
#endif
#else
#if defined(__VXWORKS__)||defined(__CMSIS_RTOS)
static inline void udelay(u32 delay_us )
{
	u32 begin = 0,end=0,delta = 0;
	delta = delay_us*(UDELAY_TIMER_CLK/1000000);
	begin = readl(UDELAY_CURTIME_ADDR);
	do{
		end = readl(UDELAY_CURTIME_ADDR);
	}while(get_timer_slice_delta(end,begin)<delta);
	return;
}
#endif
#endif
#ifdef CONFIG_MODULE_TIMER
/*****************************************************************************
* �� �� ��  :bsp_hardtimer_load_value
*
* ��������  : ����timer������ʼֵ
*
*�������  :  timer_id,
						value:����ֵ
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  :  2013��9��16��   lixiaojie
*****************************************************************************/


void bsp_hardtimer_load_value(u32 timer_id, u32 value);
void bsp_hardtimer_load_value_k3(u32 timer_id, u32 value);
#ifndef __CMSIS_RTOS

/*****************************************************************************
* �� �� ��  :bsp_hardtimer_alloc
*
* ��������  : ����timer����ģʽ��������ʼֵ���ҽ��û��ص�����
*
*�������  :  struct bsp_hardtimer_control *my_hardtimer
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

s32 bsp_hardtimer_alloc(struct bsp_hardtimer_control *my_hardtimer);
s32 bsp_hardtimer_alloc_k3(struct bsp_hardtimer_control *my_hardtimer);
/*****************************************************************************
* �� �� ��  :bsp_hardtimer_start
*
* ��������  : ����timer����ģʽ��������ʼֵ���ҽ��û��ص�����
					   ͬʱʹ�ܶ�ʱ����ʼ������
*�������  :  struct bsp_hardtimer_control *my_hardtimer  ��ʱ�����ò����ṹ��
                             unit  ��λ:0 ���룬
                                                 1΢�� ��
                                                 2��λΪ1����ֱ�Ӳ����Ĵ���
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

s32 bsp_hardtimer_start(struct bsp_hardtimer_control  *timer_ctrl);
#endif
/*****************************************************************************
* �� �� ��  :bsp_hardtimer_enable
*
* ��������  : ʹ��ĳhardtimer��ʼ����
*
* �������  :  timer_id
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

s32 bsp_hardtimer_enable(u32 timer_id);
s32 bsp_hardtimer_enable_k3(u32 timer_id);
/*****************************************************************************
* �� �� ��  :bsp_hardtimer_disable
*
* ��������  : ȥʹ��ĳhardtimer��ʼ����
*
* �������  :  timer_id
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

s32 bsp_hardtimer_disable(u32 timer_id);
s32 bsp_hardtimer_disable_k3(u32 timer_id);
/*****************************************************************************
* �� �� ��  :bsp_hardtimer_free
*
* ��������  : disable��Ӳtimer��ȡ��ע��Ļص�����
*
* �������  :  timer_id
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

s32 bsp_hardtimer_free(u32 timer_id);
s32 bsp_hardtimer_free_k3(u32 timer_id);
/*****************************************************************************
* �� �� ��  :bsp_hardtimer_clear
*
* ��������  : ��ʱ������һ���жϣ�����������������β���
*                           ���ж�
*
* �������  :  timer_id
* �������  : ��
*
* �� �� ֵ  :
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

void bsp_hardtimer_int_clear(u32 timer_id);
void bsp_hardtimer_int_clear_k3(u32 timer_id);
/*****************************************************************************
* �� �� ��  :bsp_hardtimer_mask
*
* ��������  : �����ж�
*
* �������  :  timer_id
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

void bsp_hardtimer_int_mask(u32 timer_id);
/*****************************************************************************
* �� �� ��  :bsp_hardtimer_unmask
*
* ��������  : �������ж�
*
* �������  :  timer_id
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

void bsp_hardtimer_int_unmask(u32 timer_id);
/*****************************************************************************
* �� �� ��  :bsp_hardtimer_int_status
*
* ��������  : ��ѯ�ж�״̬
*
* �������  :  timer_id
* �������  : ��
*
* �� �� ֵ  : �Ĵ����ж�״̬
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/

u32 bsp_hardtimer_int_status(u32 timer_id);
u32 bsp_hardtimer_int_status_k3(u32 timer_id);
/*****************************************************************************
* �� �� ��  :bsp_get_timer_current_value
*
* ��������  : ��ȡ��ʱ�������Ĵ�����ǰֵ
*
* �������  :  timer_id
* �������  : ��
*
* �� �� ֵ  : �����Ĵ�����ǰֵ
*
* �޸ļ�¼  :  2013��1��8��   lixiaojie
*****************************************************************************/
u32 bsp_get_timer_current_value(u32 timer_id);
u32 bsp_get_timer_current_value_k3(u32 timer_id);

/*****************************************************************************
* �� �� ��  :bsp_get_timer_rest_time
*
* ��������  : ���ݴ����������ȡָ����ʱ����ָ����λΪ��λ��
*                           ʣ��ʱ��
*
* �������  : timer_id:��ʱ��id
*                           unit:��ȡʣ��ʱ�䵥λ
* �������  : ��
*
* �� �� ֵ  : ʣ��ʱ��
*
* �޸ļ�¼  :  2013��6��20��   lixiaojie
*****************************************************************************/

u32 bsp_get_timer_rest_time(u32 timer_id, DRV_TIMER_UNIT unit);
u32 bsp_get_timer_rest_time_k3(u32 timer_id, DRV_TIMER_UNIT unit);


/*****************************************************************************
* �� �� ��  :get_next_schedule_time
*
* ��������  : �͹���ʹ�ã����ڼ��㻽��Դ����жϵ���ʱ��
*
* �������  :  ��
* �������  : ��
*
* �� �� ֵ  : ����
*
* �޸ļ�¼  :  2013��3��21��   lixiaojie
*****************************************************************************/

u32 get_next_schedule_time(void);
void timer_dpm_init(void);

#else
static inline void bsp_hardtimer_load_value(u32 timer_id, u32 value){}
static inline void bsp_hardtimer_load_value_k3(u32 timer_id, u32 value){}
static inline s32 bsp_hardtimer_alloc(struct bsp_hardtimer_control *my_hardtimer) {return 0;}
static inline s32 bsp_hardtimer_alloc_k3(struct bsp_hardtimer_control *my_hardtimer) {return 0;}
static inline s32 bsp_hardtimer_start(struct bsp_hardtimer_control  *timer_ctrl) {return 0;}
static inline s32 bsp_hardtimer_enable(u32 timer_id) {return 0;}
static inline s32 bsp_hardtimer_enable_k3(u32 timer_id) {return 0;}
static inline s32 bsp_hardtimer_disable(u32 timer_id) {return 0;}
static inline s32 bsp_hardtimer_disable_k3(u32 timer_id) {return 0;}
static inline s32 bsp_hardtimer_free(u32 timer_id) {return 0;}
static inline s32 bsp_hardtimer_free_k3(u32 timer_id) {return 0;}
static inline void bsp_hardtimer_int_clear(u32 timer_id) {}
static inline void bsp_hardtimer_int_clear_k3(u32 timer_id) {}
static inline void bsp_hardtimer_int_mask(u32 timer_id) {}
static inline void bsp_hardtimer_int_unmask(u32 timer_id) {}
static inline u32 bsp_hardtimer_int_status(u32 timer_id) {return 0;}
static inline u32 bsp_hardtimer_int_status_k3(u32 timer_id) {return 0;}
static inline u32 bsp_get_timer_current_value(u32 timer_id) {return 0;}
static inline u32 bsp_get_timer_current_value_k3(u32 timer_id) {return 0;}
static inline u32 bsp_get_timer_rest_time(u32 timer_id, DRV_TIMER_UNIT unit) {return 0;}
static inline u32 bsp_get_timer_rest_time_k3(u32 timer_id, DRV_TIMER_UNIT unit) {return 0;}
static inline u32 get_next_schedule_time(void) {return 0;}
static inline void timer_dpm_init(void){}
#endif

#endif /*__ASSEMBLY__*/

#endif /*__BSP_HARDTIMER_H__*/


