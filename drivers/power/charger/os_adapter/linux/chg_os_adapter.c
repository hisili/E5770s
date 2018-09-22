


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/

#include "../../chg_config.h"
#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
#include <linux/wakelock.h>
#endif
#include <linux/workqueue.h>

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/
extern struct chargeIC_chip *g_chip;

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/
/*��ӡͨ�����ޣ���ֵ��������޵͵��ܹ���ӡ����*/

//uint32_t chg_print_level = CHG_MSG_DEBUG;
extern int32_t g_huawei_drv_debug;



#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)

/*�����ѯ��ʱ��(������ϵͳ,�лص�)*/
struct softtimer_list g_chg_poll_timer;

/*���ڳ�������ͼ�ⶨʱ��(���������Ƿ���ϵͳ,�лص�)*/
struct softtimer_list g_chg_sta_timer ;

/*����/�͵�ػ���ʱ(���������Ƿ���ϵͳ,�лص�,������)*/
struct softtimer_list g_chg_bat_timer;

/*�����ѯ��ʱ��������֮������״̬(��Ҫ����ϵͳ,�лص�)*/
struct softtimer_list g_chg_sleep_timer ;
#else
/*�����ѯ��ʱ��(���ܻ���ϵͳ,�лص�)*/
struct timer_list g_chg_poll_timer;

/*���ڳ�������ͼ�ⶨʱ��(���ܻ���ϵͳ,�лص�)*/
static struct timer_list g_chg_sta_timer;

/*����/�͵�ػ���ʱ(���ܻ���ϵͳ,�лص�,������)*/
static struct timer_list g_chg_bat_timer;

#endif/*MBB_CHG_PLATFORM_V7R2*/


/*Linux�н��յ����¼���¼*/
static uint32_t g_event_recv = 0;
/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*��������ID*/
struct task_struct *g_chgTaskID = NULL;

struct wake_lock g_sply_lock;

/*���ģ����ѯ���ڼ�¼(ms)*/
uint32_t chg_poll_time_bak = FAST_POLL_CYCLE;
/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
/*�������Ͳ�����������ȼ�*/
#define CHG_TASK_PRI  (150)

/* Ŀǰʹ�õ���ʱʱ�����С����(10ms)*/
#define CHG_DELAY_COUNTER_SIZE (10)
/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/
extern void chg_sleep_batt_check_timer(struct work_struct *work);
/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/
static DEFINE_SPINLOCK(chg_event_lock);

struct workqueue_struct *sleep_batt_check_workqueue = NULL;
struct work_struct sleep_batt_check_work;


void chg_sply_lock(void)
{
    wake_lock(&g_sply_lock);
    chg_print_level_message( CHG_MSG_INFO,"--->Begin keep system wakeup for supply charge!\r\n");
}

void chg_sply_unlock(void)
{
    wake_unlock(&g_sply_lock);
    chg_print_level_message( CHG_MSG_INFO,"--->Release sply wake lock ,supply success!\r\n");
}


asmlinkage int chg_print_level_message(int print_level,const char *fmt,...)
{
    va_list args;
    int rc = 0;

    /*С��chg_print_level�����LOG���Ա���ӡ*/
    if((uint32_t)print_level < g_huawei_drv_debug)
    {
        va_start(args, fmt);
        rc = vprintk(fmt, args);
        va_end(args);
    }
    return rc;
}

/**********************************************************************
�� �� ��: chg_sleep_batt_check_timer_call
��������: ��ʱ���ص�������ʵ�������ж��ϰ벿�ֹ��ܣ���ֹ��ʱ�����������ص�����
�������: None
�������: None
�� �� ֵ: None
***********************************************************************/
void chg_sleep_batt_check_timer_call(void * data)
{
    /*�ڴ˴����ӱ���������ֹ�ڵ��ö�ʱ���ص��Ĺ����У�ϵͳ���ߣ���chg_sleep_batt_check_timer
      �������ͷŴ˱�����*/
    wake_lock(&g_chip->chg_wake_lock);

    /*�������Ӷ�ʱ��*/
    bsp_softtimer_add(&g_chg_sleep_timer);

    /*���ȹ�������*/
    queue_work(sleep_batt_check_workqueue, &sleep_batt_check_work); 

    return;  
}

/**********************************************************************
�� �� ��: chg_task_create
��������: ������һ���������
�������: None
�������: None
�� �� ֵ    : None
ע������: Vxworks��ʵ��
          ��Ϊ��ϵͳ����,���ע�������Ӧ�Ŀ��ļ�
***********************************************************************/
void chg_task_create( void )
{
    /*���������ѵ��ʱ��*/
#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
    s32 ret = 0;

    g_chg_poll_timer.func = chg_send_msg_to_main;
    g_chg_poll_timer.para = CHG_TIMER_EVENT;
    g_chg_poll_timer.timeout = FAST_POLL_CYCLE;
    /* fix HISI Softtimer B170 bug 2013-09-17 */
    g_chg_poll_timer.wake_type = SOFTTIMER_NOWAKE;

    /*������ʼ��һ����������*/
    sleep_batt_check_workqueue = create_workqueue("sleepcheck");
    INIT_WORK(&sleep_batt_check_work, chg_sleep_batt_check_timer);    
    g_chg_sleep_timer.func = chg_sleep_batt_check_timer_call; 
    g_chg_sleep_timer.para = 0;
    g_chg_sleep_timer.timeout = SLEEP_POLL_CYCLE;
    g_chg_sleep_timer.wake_type = SOFTTIMER_WAKE;

    ret = bsp_softtimer_create(&g_chg_poll_timer);
    if(ret)
    {
        chg_print_level_message( CHG_MSG_ERR," %s: g_chg_poll_timer create error!!!\r\n ", __func__);
        return;
    }

    ret = bsp_softtimer_create(&g_chg_sleep_timer);
    if(ret)
    {
        chg_print_level_message( CHG_MSG_ERR," %s: chg_sleep_timer create error!!!\r\n ", __func__);
        return;
    }
#else
    if ( NULL == g_chg_poll_timer.function )
    {
        setup_timer(&g_chg_poll_timer,(void *)chg_send_msg_to_main,CHG_TIMER_EVENT);
    }
#endif/*MBB_CHG_PLATFORM_V7R2*/
    /* ��������߳� */
    g_chgTaskID = kthread_run( chg_main_task, NULL, CHG_TASK_NAME);
    if ( IS_ERR(g_chgTaskID) )
    {
        chg_print_level_message( CHG_MSG_ERR," %s: Thread create error!!!\r\n ", __func__);
    }
    else
    {
        chg_print_level_message( CHG_MSG_ERR," %s: Thread create success!!!\r\n ", __func__);
    }

#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
    /*���������ʱ��*/
    bsp_softtimer_add(&g_chg_poll_timer);
    bsp_softtimer_add(&g_chg_sleep_timer);
#endif/*MBB_CHG_PLATFORM_V7R2*/

    return;
}


/**********************************************************************
�� �� ��: chg_task_delete
��������: ɾ����һ���������
�������: None
�������: None
�� �� ֵ: None
ע������: ������Linux��Vxworks��ʵ��
          ��Ϊ��ϵͳ����,���ע�������Ӧ�Ŀ��ļ�
***********************************************************************/

void chg_task_delete( void )
{
    int32_t ret = 0;

    if (!!g_chgTaskID)
    {
        chg_print_level_message( CHG_MSG_INFO," %s: Thread start to stop!!!\r\n ", __func__);
        ret = kthread_stop(g_chgTaskID);
        chg_print_level_message( CHG_MSG_INFO," %s: Thread stop success ret %d!!!\r\n ", __func__, ret);
    }
}

#if (MBB_CHG_COMPENSATE == FEATURE_ON)
/**********************************************************************
�� �� ��: chg_sply_task_create
��������: ������һ����������
�������: None
�������: None
�� �� ֵ: None
ע������: ������Linux��Vxworks��ʵ��
          ��Ϊ��ϵͳ����,���ע�������Ӧ�Ŀ��ļ�
***********************************************************************/
void chg_sply_task_create( void )
{
    struct task_struct *tsk = NULL;
    static boolean flag_task_init = FALSE;

    wake_lock_init( &g_sply_lock, WAKE_LOCK_SUSPEND, "sply_lock" );
    if (FALSE == flag_task_init)
    {
        /* ���������߳� */
        tsk = kthread_run( chg_batt_supply_proc, NULL, CHG_SPLY_TASK_NAME );

        /*�����������ʧ��*/
        if ( IS_ERR(tsk) )
        {
            chg_print_level_message( CHG_MSG_ERR," %s: Thread create error!!!\r\n ", __func__);
        }
        else
        {
            flag_task_init = TRUE;
            chg_print_level_message( CHG_MSG_ERR," %s: Thread create success!!!\r\n ", __func__);
        }

    }
    else
    {
        chg_print_level_message( CHG_MSG_ERR," %s: Thread already create !!!\r\n ", __func__);
    }

    return;
}
#endif/*MBB_CHG_COMPENSATE*/
/**********************************************************************
�� �� ��: chg_delay_ms
��������: �ȴ���ʱ��ʱ�䣨��λ���룩
�������: ��Ҫ��ʱ��ʱ�䣨��λ���룩
�������: None
�� �� ֵ: None
ע������: vxworks
***********************************************************************/
void chg_delay_ms( uint32_t delay_time_ms )
{
    /*  ��ΪĿǰ��ʱ�䴦����10ms��Ϊ��С��λ
    ��˶�����������������*/
    msleep(delay_time_ms);
}

/*************************************************************
  ��������: chg_poll_timer_set
  ��������: �ṩ�����ѯ��ʱ��
  �������: ��ѯ����(��msΪ��λ)
  �������: None
  �� �� ֵ: None
  ע������:  1\�����ʱ��������Ϊ���ģ�鶨ʱ��ѯ
                          2\ʱ�䵽�������¶�ʱ
*************************************************************/
void chg_poll_timer_set( uint32_t cycle_in_ms )
{
    /*���timer����������*/
    if ( ( cycle_in_ms != chg_poll_time_bak ) )
    {
        /*���³��ģ����ѯ����(ms)*/
        chg_poll_time_bak = cycle_in_ms;
    }
    chg_print_level_message( CHG_MSG_INFO," start poll chg state timer hz=%d!\r\n ",cycle_in_ms);

#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
    (void)bsp_softtimer_delete_sync(&g_chg_poll_timer);
    bsp_softtimer_modify(&g_chg_poll_timer,cycle_in_ms);
    bsp_softtimer_add(&g_chg_poll_timer);
#else
    mod_timer( &g_chg_poll_timer, jiffies + msecs_to_jiffies( cycle_in_ms ) );
#endif/*MBB_CHG_PLATFORM_V7R2*/
}

/*************************************************************
  ��������: chg_poll_timer_get
  ��������: �ṩ�����ѯ��ʱ����ѯ
  �������: None
  �������: None
  �� �� ֵ: -1:����(�����ǻ�û�����ù�),
                      2000/20000:��ѯ����(��msΪ��λ)
  ע������: ��ע��,��ȡ֮ǰһ��Ҫ��֤����chg_poll_timer_set
*************************************************************/
int32_t chg_poll_timer_get( void )
{
    /*���س��ģ�鶨ʱ��ѯ����*/
    if ( ( FAST_POLL_CYCLE == chg_poll_time_bak )
        || ( SLOW_POLL_CYCLE == chg_poll_time_bak ) )
    {
        return ( int32_t )chg_poll_time_bak;
    }
    else
    {
        return ( int32_t )(-1);
    }

}
/*************************************************************
  ��������: chg_sta_timer_set
  ��������: �ṩ��״̬����ѯģ��Ķ�ʱ��,��ʱ����ִ�лص�����
  �������: ��ʱʱ��(��msΪ��λ), �ص�����
  �������: None
  �� �� ֵ: None
  ע������: None
*************************************************************/
void chg_sta_timer_set( uint32_t cycle_in_ms, chg_poll_timer_callback func)
{

#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
    s32 ret = 0;
    g_chg_sta_timer.func = (softtimer_func)func;
    g_chg_sta_timer.para = 0;
    g_chg_sta_timer.timeout = cycle_in_ms;
    /* fix HISI Softtimer B170 bug 2013-09-17 */
    g_chg_sta_timer.wake_type = SOFTTIMER_WAKE;

    if(g_chg_sta_timer.init_flags == TIMER_INIT_FLAG )
    {
        (void)bsp_softtimer_delete(&g_chg_sta_timer);
        bsp_softtimer_modify(&g_chg_sta_timer,cycle_in_ms);
        bsp_softtimer_add(&g_chg_sta_timer);
    }
    else
    {
        ret = bsp_softtimer_create(&g_chg_sta_timer);
        if(ret)
        {
            chg_print_level_message( CHG_MSG_ERR," %s: g_chg_sta_timer create error!!!\r\n ", __func__);
            return;
        }
        bsp_softtimer_add(&g_chg_sta_timer);
    }
#else
    if ( NULL == g_chg_sta_timer.function )
    {
        /*Ϊ��������ͼ���ṩ�Ķ�ʱ��*/
        setup_timer( &g_chg_sta_timer, func, 0 );
    }

    mod_timer( &g_chg_sta_timer, jiffies + msecs_to_jiffies(cycle_in_ms) );
#endif/*MBB_CHG_PLATFORM_V7R2*/
}

/*************************************************************
  ��������: chg_bat_timer_set
  ��������: �ṩ����ص�ѹ/�¶ȼ��ģ��Ķ�ʱ��,��ʱ��ʱִ�лص�����
  �������:
                        cycle_in_ms: ��ʱʱ��(ms)
                        func: �ص�����,�ص����������
                        para: func�����
  �������: None
  �� �� ֵ: None
  ע������: None
*************************************************************/
void chg_bat_timer_set( uint32_t cycle_in_ms, void (*func)(uint32_t), uint32_t para )
{
#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
    drvShutdown(para);

#else
    if ( NULL == g_chg_bat_timer.function )
    {
        /*Ϊ״̬��ģ���ṩ�Ķ�ʱ������Ҫ����*/
        setup_timer( &g_chg_bat_timer, (void *)func, para );
    }
    mod_timer( &g_chg_bat_timer, jiffies + msecs_to_jiffies(cycle_in_ms) );
#endif/*MBB_CHG_PLATFORM_V7R2*/
}

/**********************************************************************
�� �� ��  : chg_send_msg_to_main
��������  : ��ʱ������������������¼�
�������  : param �̶���ʽ����
�������  : �ޡ�
�� �� ֵ  : �ޡ�
ע������  : �ޡ�
***********************************************************************/
void chg_send_msg_to_main(uint32_t event_id)
{
    unsigned long flags = 0;

    if ( 0 == ( CHG_ALL_EVENT & event_id ) )
    {
        chg_print_level_message( CHG_MSG_ERR," Invalid event id!!!\r\n ");
    }
    else
    {
        spin_lock_irqsave(&chg_event_lock, flags);
        g_event_recv |= event_id;
        spin_unlock_irqrestore(&chg_event_lock, flags);
        chg_print_level_message( CHG_MSG_DEBUG,"send_msg_to_main g_event_recv=%x\n ", g_event_recv);
        chg_print_level_message( CHG_MSG_DEBUG,"send_msg_to_main event_id=%x\n ", event_id);
        wake_up_process(g_chgTaskID);
    }
#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
    if(CHG_TIMER_EVENT == event_id)
    {
        bsp_softtimer_modify(&g_chg_poll_timer,chg_poll_time_bak);
        bsp_softtimer_add(&g_chg_poll_timer);
    }
#else
    mod_timer( &g_chg_poll_timer, jiffies + msecs_to_jiffies( chg_poll_time_bak ) );
#endif/*MBB_CHG_PLATFORM_V7R2*/
}

/**********************************************************************
�� �� ��  : this_kthread_should_stop
��������  : When someone calls kthread_stop() on your kthread, it will be woken
and this will return true. You should then return, and your return value will
be passed through to kthread_stop()
�������  : ��
�������  : �ޡ�
�� �� ֵ  : TRUE:��ʾ�е���kthread_stop()��FALSE:��ʾû�У�
ע������  : �ޡ�
***********************************************************************/
boolean this_kthread_should_stop(void)
{
    if (kthread_should_stop())
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
/**********************************************************************
�� �� ��: chg_main_wait_for_msg
��������: �������������״̬���ȴ����¼�����
�������: None
�������: ���յ��¼�
�� �� ֵ: �ޡ�
ע������: Linuxϵͳ�У����øú���ʱ���ж��Ƿ����¼�û�д������
***********************************************************************/
int32_t chg_main_wait_for_msg( uint32_t* get_event_id )
{
    unsigned long flags = 0;
    if ( NULL == get_event_id )
    {
        chg_print_level_message( CHG_MSG_ERR, " Invalid address!!!\n ");
        return -1;
    }

    if (0 == (CHG_ALL_EVENT & g_event_recv))
    {
        /*��������������״̬*/
        set_current_state(TASK_INTERRUPTIBLE);
        schedule();
    }

    chg_print_level_message( CHG_MSG_INFO," ****g_event_recv %d!!!***\n ", g_event_recv);

    spin_lock_irqsave(&chg_event_lock, flags);
    /*���յ��¼��Ժ�ȡ���¼���¼*/
    *get_event_id = g_event_recv;
    g_event_recv = 0;
    spin_unlock_irqrestore(&chg_event_lock, flags);
    return 0;
}


