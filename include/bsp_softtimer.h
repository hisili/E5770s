#ifndef __BSP_SOFTTIMER_H__
#define __BSP_SOFTTIMER_H__

#include <osl_common.h>
#include <osl_list.h>
#include <product_config.h>
typedef void (*softtimer_func)(u32);
#define TIMER_TRUE 1
#define TIMER_FALSE 0
#define TIMER_INIT_FLAG     0X5A5A5A5A
/*�ṹ���ö�ٶ���*/
enum wakeup
{
    SOFTTIMER_WAKE,
    SOFTTIMER_NOWAKE
};
struct softtimer_list
{
   softtimer_func func;
   u32 para;
   u32 timeout;
   enum wakeup wake_type;
   
   /*ʹ���߲��ù�ע������������Ϣ*/
   struct list_head entry;
   u32 timer_id;
   u32 count_num;/*ԭʼ������ʼ����ʱ��*/
   u32 is_running;
   u32 init_flags;
};

#ifdef CONFIG_MODULE_TIMER
int  bsp_softtimer_init(void);
/*****************************************************************************
* �� �� ��  :bsp_softtimer_create_timer
*
* ��������  : ����һ����timer��������timer id��
*
* �������  :  Ҫsofttimer  ��������timer����Ϣ
* �������  : ��
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  :  2013��2��28��   lixiaojie     
*****************************************************************************/
s32 bsp_softtimer_create(struct softtimer_list *softtimer);
/*****************************************************************************
* �� �� ��  :     bsp_softtimer_delete
*
* ��������  : ����timer����ɾ��һ����û�е���ʱʱ���
                            ����ִ�еĶ�ʱ��
*
* �������  :  timer Ҫɾ����timer 
                             �Ĳ���
* �������  : ��
*
* �� �� ֵ  :     0   ɾ���ɹ�
                             1   Ҫɾ���Ķ�ʱ�����ڳ�ʱ����
                             -1 �����timerָ��Ϊ��
*
* �޸ļ�¼  :  2013��2��28��   lixiaojie     
*****************************************************************************/
s32 bsp_softtimer_delete(struct softtimer_list * softtimer);
/*****************************************************************************
* �� �� ��  :bsp_softtimer_delete_sync
*
* ��������  : ����timer����ɾ��һ���ظ�ִ�е���timer
*
* �������  :  timer Ҫɾ����timer ��Ϊbsp_softtimer_create_timer�����ķ���ֵ
* �������  : ��
*
* �� �� ֵ  : 0   ɾ���ɹ�
                             1   Ҫɾ���Ķ�ʱ�����ڳ�ʱ����
                             -1 �����timerָ��Ϊ��
*
* �޸ļ�¼  :  2013��2��28��   lixiaojie     
*****************************************************************************/

s32 bsp_softtimer_delete_sync(struct softtimer_list * timer);

/*****************************************************************************
* �� �� ��  :bsp_softtimer_modify
*
* ��������  : �޸���timer��ʱʱ�䣬�޸���ɺ���Ҫ����
*                           bsp_softtimer_add������Ӳ���
*
* �������  :  timer: Ҫ�޸ĵ���timer��Ϊbsp_softtimer_create_timer��������
                             �Ĳ���
                             new_expire_time: �³�ʱʱ��
* �������  : ��
*
* �� �� ֵ  : OK&ERROR
*
* �޸ļ�¼  :  2013��2��28��   lixiaojie     
*****************************************************************************/

s32 bsp_softtimer_modify(struct softtimer_list * softtimer,u32 new_expire_time);
/*****************************************************************************
* �� �� ��  :   bsp_softtimer_add
*
* ��������  : ��softtimer���볬ʱ���У������ʱ��ʱ����Ҫ����ظ�ִ�У�
*                           ��Ҫ�ڻص������е��ñ��ӿڽ�����Ӳ���
*
* �������  :  Ҫ������еĶ�ʱ��ָ��
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  :  2013��2��28��   lixiaojie     
*****************************************************************************/

void bsp_softtimer_add(struct softtimer_list * timer);
/*****************************************************************************
* �� �� ��  :bsp_softtimer_free
*
* ��������  : �ͷŶ�ʱ��ռ�õ���Դ
*
* �������  :  Ҫ�ͷŵĶ�ʱ��ָ��
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  :  2013��2��28��   lixiaojie     
*****************************************************************************/

s32 bsp_softtimer_free(struct softtimer_list *timer);
#else
static inline int  bsp_softtimer_init(void) {return 0;}
static inline s32  bsp_softtimer_create(struct softtimer_list *softtimer) {return 0;}
static inline s32 bsp_softtimer_delete(struct softtimer_list * softtimer) {return 0;}
static inline s32 bsp_softtimer_delete_sync(struct softtimer_list * timer) {return 0;}
static inline s32 bsp_softtimer_modify(struct softtimer_list * softtimer,u32 new_expire_time) {return 0;}
static inline void bsp_softtimer_add(struct softtimer_list * timer) {}
static inline s32 bsp_softtimer_free(struct softtimer_list *timer) {return 0;}
#endif
#endif
