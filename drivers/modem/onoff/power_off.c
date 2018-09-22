 
/*lint --e{537} */
#include <hi_onoff.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <product_config.h>
#include <osl_list.h>
#include <osl_types.h>
#include <osl_spinlock.h>
#include <drv_chg.h>
#include <drv_onoff.h>
#include <bsp_pmu.h>
#include <hi_syssc_interface.h>
#include <power_com.h>
#include "power_inner.h"
#include "power_exchange.h"
#include "../../../reb_V100R001/reb_os/reb_mod/reb_func.h"
#include <bsp_sram.h>
#include <bsp_reset.h>

#include <linux/mlog_lib.h>
static LIST_HEAD(list_callback);
static DEFINE_SPINLOCK(list_spinlock); //lint !e43 !e64 !e120

LOCAL_1 bool is_power_off_charge_in( void );
LOCAL_1 void power_off_set_flag_and_reboot( power_off_reboot_flag enRebootFlag );

extern DRV_START_MODE chg_get_start_mode();/*lint !e10*/

power_off_ctrl_s power_off_ctrl = {DRV_SHUTDOWN_BUTT, {0,0,0,0,0,0,0,0,0}};

/* stub */

void power_off_clear_dump(void)
{
    unsigned long flags;
    struct bsp_onoff_callback *hook = NULL;

    spin_lock_irqsave(&list_spinlock, flags);

    list_for_each_entry(hook, &list_callback, node)
    if ((hook) && (hook->fn))
    {
        hook->fn();
    }
    spin_unlock_irqrestore(&list_spinlock, flags);
}


/*****************************************************************************
 �� �� ��  : power_off_down_operation
 ��������  : pmu hold ϵͳ�µ�
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 void power_off_down_operation( void )
{
    pr_dbg( "system power down!\r\n" );
    /* ������������� */
    power_reboot_cmd_set(POWER_REBOOT_CMD_BUTT);

    *(u32*)SRAM_MBB_PD_CHARGE_ADDR = SRAM_MBB_PD_CHARGE_OFF;
    power_off_clear_dump();
	power_on_wdt_cnt_set();

    if(is_power_off_charge_in())    
    {         
        power_off_set_flag_and_reboot( POWER_OFF_REASON_BY_CHARGE );
    }    
    else    
    {    
        /* shutdown the system. */        
        hi_syssc_pmu_hold_down();
    }
    for(;;) ;
}

/*****************************************************************************
 �� �� ��  : power_off_reboot_operation
 ��������  : pmu rst ϵͳ����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 void power_off_reboot_operation( void )
{
    /* ��������������Ϊ������ */
    power_reboot_cmd_set(POWER_REBOOT_CMD_WARMRESET);

/* p531 FPGA��λ��Ҫͬʱ��λF1/BBP/RF */

    pr_dbg( "system power reboot!\r\n" );

    *(u32*)SRAM_MBB_PD_CHARGE_ADDR = SRAM_MBB_PD_CHARGE_OFF;
    hi_syssc_wdt_reboot();
    for(;;) ;
}

/*****************************************************************************
 �� �� ��  : is_power_key_pressed
 ��������  : �ػ�ʱ�����Ƿ���
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 bool is_power_key_pressed( void )
{
    return bsp_pmu_key_state_get();
}

/*****************************************************************************
 �� �� ��  : is_power_off_charge_in
 ��������  : �ػ�ʱ������Ƿ����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 bool is_power_off_charge_in( void )
{
    bool pmu_usb_state = false;

	pmu_usb_state = bsp_pmu_usb_state_get();
    printk(KERN_INFO "[ ON OFF] pmu_usb_state is %d.\n", pmu_usb_state);

    return pmu_usb_state;
}
/*****************************************************************************
 �� �� ��  : power_off_operation
 ��������  : ִ�йػ�����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 void power_off_operation( void )
{
    /* �������ɿ�����£�������ػ� */
    while( is_power_key_pressed() )
    {
        /* avoid the watchdog reset while polling the power key */
        /* TO DO*/
    }

    pr_dbg("\r\n power_off_operation : the power key is release\r\n" );

    /* shutdown the system. */
    power_off_down_operation();
}

/*****************************************************************************
 �� �� ��  : power_off_set_flag_and_reboot
 ��������  : ִ�йػ�����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 void power_off_set_flag_and_reboot( power_off_reboot_flag enRebootFlag )
{
    /*lint --e{*} */
    unsigned long irq_flags = 0;
    struct bsp_onoff_callback *hook = NULL;

    spin_lock_irqsave(&list_spinlock, irq_flags);
    /*coverity[var_deref_op] */
    list_for_each_entry(hook, &list_callback, node)
        /*coverity[var_compare_op] */
        if ((hook) && (hook->fn))
            hook->fn();
    spin_unlock_irqrestore(&list_spinlock, irq_flags);

    power_on_reboot_flag_set( enRebootFlag );
    power_off_reboot_operation();
}

/*****************************************************************************
 �� �� ��  : power_off_battery_error_handler
 ��������  : ��ش���ػ�����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1  void power_off_battery_error_handler( void )
{
    if( is_power_off_charge_in() )
    {
        power_off_set_flag_and_reboot( POWER_OFF_REASON_BAD_BATTERY );
    }
    else
    {
        power_off_operation();
    }
}

/*****************************************************************************
 �� �� ��  : power_off_battery_low_handler
 ��������  : ��ص͵紦��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 void power_off_battery_low_handler( void )
{
    if( is_power_off_charge_in() )
    {
        power_off_set_flag_and_reboot( POWER_OFF_REASON_LOW_BATTERY );
    }
    else
    {
        power_off_operation();
    }
}

/*****************************************************************************
 �� �� ��  : power_off_temp_protect_handler
 ��������  : �¶ȱ�������
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 void power_off_temp_protect_handler( void )
{
    if( is_power_off_charge_in() )
    {
        /* The charge is in, can't power off, restart and show the warning */
        power_off_set_flag_and_reboot(POWER_OFF_REASON_OVER_TEMP);
    }
    else
    {
        /* No warning message, power off directly */
        power_off_operation();
    }
}

/*****************************************************************************
 �� �� ��  : power_off_power_key_handler
 ��������  : �����ػ�����, �ڹػ����ģʽ�°�����������������ģʽ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 void power_off_power_key_handler( void )
{
    if( DRV_START_MODE_CHARGING == bsp_start_mode_get() )
    {
        /* reboot and enter normal mode; */
        power_off_set_flag_and_reboot( POWER_OFF_REASON_NORMAL );
    }
    else /* normal mode */
    {
        /* if charge is in, will power on again and enter charge mode. */
        power_off_operation();
    }
}

/*****************************************************************************
 �� �� ��  : power_off_update_handler
 ��������  : �����ػ�������λ����recoveryģʽ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 void power_off_update_handler( void )
{
    /* reboot and enter update mode */
    power_off_set_flag_and_reboot( POWER_OFF_REASON_UPDATE );
}

/*****************************************************************************
 �� �� ��  : power_off_charge_remove_handler
 ��������  : ������Ƴ�����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 void power_off_charge_remove_handler( void )
{
    if( DRV_START_MODE_CHARGING == bsp_start_mode_get() )
    {
        power_off_operation();  /* �ػ����ʱ���γ������������ֱ���µ� */
    }
    else
    {
        /* Normal mode, nothing need to do. */
    }
}

/*****************************************************************************
 �� �� ��  : power_off_reset_handler
 ��������  : ϵͳ��λ������ֱ�Ӹ�λ�����ü��charger״̬
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
void power_off_reset_handler( void )
{
    /* Needn't check charge status */
    power_off_set_flag_and_reboot( POWER_OFF_REASON_NORMAL );
}

/*****************************************************************************
 �� �� ��  : power_off_reset_handler
 ��������  : ϵͳ��λ������ֱ�Ӹ�λ�����ü��charger״̬
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
LOCAL_1 void power_off_excecute( DRV_SHUTDOWN_REASON_ENUM enShutdownReason )
{
	unsigned long flags = 0;
    reb_file_sync();

	local_irq_save(flags);

    switch( enShutdownReason )
    {
    case DRV_SHUTDOWN_RESET:
        power_off_set_flag_and_reboot( POWER_OFF_REASON_NORMAL );
        break;
    case DRV_SHUTDOWN_BATTERY_ERROR:
        power_off_battery_error_handler();
        break;
    case DRV_SHUTDOWN_LOW_BATTERY:
        power_off_battery_low_handler();
        break;
    case DRV_SHUTDOWN_TEMPERATURE_PROTECT:
        power_off_temp_protect_handler();
        break;
    case DRV_SHUTDOWN_POWER_KEY:
        power_off_power_key_handler();
        break;
    case DRV_SHUTDOWN_UPDATE:
        power_off_update_handler();
        break;
    case DRV_SHUTDOWN_CHARGE_REMOVE:
        power_off_charge_remove_handler( );
        break;
    default:
        power_off_operation();
        break;
    }

    /* Woulnd't reach here ! */
    local_irq_restore( flags );
}

/*****************************************************************************
 �� �� ��  : power_on_mode_get
 ��������  : ��ȡ����ģʽ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int power_off_reason_get( void )
{
    power_off_reboot_flag reboot_reason = (power_off_reboot_flag)(power_off_ctrl.reason) ;
    DRV_SHUTDOWN_REASON_ENUM rb = DRV_SHUTDOWN_BUTT;

    switch(reboot_reason)
    {
    case POWER_OFF_REASON_NORMAL:
        rb = DRV_SHUTDOWN_POWER_KEY;
        break;
    case POWER_OFF_REASON_BAD_BATTERY:
        rb = DRV_SHUTDOWN_BATTERY_ERROR;
        break;
    case POWER_OFF_REASON_LOW_BATTERY:
        rb = DRV_SHUTDOWN_LOW_BATTERY;
        break;
    case POWER_OFF_REASON_OVER_TEMP:
        rb = DRV_SHUTDOWN_TEMPERATURE_PROTECT;
        break;
    case POWER_OFF_REASON_RM_CHARGE:
        rb = DRV_SHUTDOWN_CHARGE_REMOVE;
        break;
    case POWER_OFF_REASON_UPDATE:
        rb = DRV_SHUTDOWN_UPDATE;
        break;
    case POWER_OFF_REASON_RESET:
        rb = DRV_SHUTDOWN_RESET;
        break;
    default:
        rb = DRV_SHUTDOWN_BUTT;
        break;
    }

    return rb;

}

/******************************************************************************
*  Function:  power_off_log_save
*  Description: save the power off log( reason and battery voltage ).
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :
********************************************************************************/
LOCAL_1 int power_off_log_save( void )
{
    long pos;
    unsigned int pf;
    mm_segment_t old_fs;
    struct rtc_time tm;
    struct timespec ts;
    int     rt;
    char    buf[128];
    char    *reboot_reason[] = {"LOWBATTERY", "BAD BATTERY", "NORMAL", "OVERTEMP", \
                                    "LOWTEMP", "REBOOT", "RM_CHARGER", "UPDATE", "INVALID"};
    BATT_LEVEL_ENUM                 battery_level = chg_get_batt_level();
    DRV_SHUTDOWN_REASON_ENUM        rb;

    getnstimeofday(&ts);

    rtc_time_to_tm((unsigned long)ts.tv_sec, &tm);

    power_off_ctrl.time = tm;
    rb = power_off_ctrl.reason;

    pr_dbg("%4d-%02d-%02d %02d:%02d:%02d\n",tm.tm_year, tm.tm_mon, \
        tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    if( DRV_SHUTDOWN_RESET == power_off_ctrl.reason )
    {
       mlog_print(MLOG_POWER, mlog_lv_info, "system will go to reboot\n" );
       mlog_set_statis_info("reboot_times",1); //normal reboot statistic   
    }
    else
    {
        mlog_print(MLOG_POWER, mlog_lv_info, "SHUTDOWN due to %s\n" , reboot_reason[rb]);
        mlog_set_statis_info("off_times",1);    
    }  
    sys_shutdown_mog_report();


    /* ��¼�ػ���Ϣ(ʱ�䡢�������ػ�ԭ��) */
    snprintf(buf, sizeof(buf) - 1, "system close reason(E5): %s, current battery voltage: %d, current time: %4d-%02d-%02d %02d:%02d:%02d\n", \
        reboot_reason[rb], battery_level, tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    old_fs = get_fs(); //lint !e63

    set_fs(KERNEL_DS);

    /*coverity[check_return] */
    pf = (unsigned int)sys_open(EXCH_RESET_LOG_PATH, O_RDWR | O_CREAT, 0666);
    /*coverity[unchecked_value] */
    if(IS_ERR((const void*)pf))
    {
        pr_dbg( "error occured happened when open file %s, exiting.\n", EXCH_RESET_LOG_PATH);
        return (int)pf;
    }

    /*coverity[unchecked_value] */
    pos = sys_lseek(pf, 0, SEEK_END);
    if(pos > EXCH_ONOFF_LOG_MAX){
        /* �ļ����� 16k,ɾ�����´� */
        sys_rmdir(EXCH_RESET_LOG_PATH);
        /*coverity[check_return] */
        pf = (unsigned int)sys_open(EXCH_RESET_LOG_PATH, O_RDWR | O_CREAT, 0666);
        /*coverity[unchecked_value] */
        if(IS_ERR((const void*)pf))
        {
            pr_dbg( "error occured happened when open file %s, exiting.\n", EXCH_RESET_LOG_PATH);
            return (int)pf;
        }
    }
    else{
        /*coverity[unchecked_value] */
        sys_lseek(pf, pos, SEEK_SET);
    }

    /*coverity[unchecked_value] */
    rt = sys_write(pf, (const char*)buf, strlen(buf));
    if(rt<0)
    {
        pr_dbg("error occured happened when write file %s, exiting.\n", EXCH_RESET_LOG_PATH);
        /*coverity[unchecked_value] */
        sys_close( pf );
        set_fs(old_fs);
        return rt;
    }

    pr_dbg(KERN_DEBUG "power off log save.");

    /*coverity[unchecked_value] */
    sys_close( pf );
    set_fs(old_fs);

    return rt;
}

/******************************************************************************
*  Function:  power_off_timeout_isr
*  Description: ���Ӧ��û��һ��ʱ���ڹػ����ײ�ֱ�ӹػ�
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :
********************************************************************************/
static int power_off_timeout_isr( void )
{
    pr_dbg("power_off_timeout_isr, reason :%d\n ",power_off_ctrl.reason);

    (void)bsp_softtimer_free(&power_off_ctrl.off_timer);

    power_off_excecute(power_off_ctrl.reason);

    return 0;
}

/******************************************************************************
*  Function:  drv_power_off
*  Description: ֱ�ӹػ��ӿڣ�����¼�ػ��¼�
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :
********************************************************************************/
LOCAL_1 void drv_power_off( void )
{
    /*
       If the shutdown reason has been set, do it.
       If not, it is invalid one and will shutdown
    */
    power_off_excecute(power_off_ctrl.reason);
}


void bsp_reboot_callback_register(void (*hook)(void))
{
    /*lint --e{*} */
    unsigned long flags = 0;

    struct bsp_onoff_callback *callback =
        (struct bsp_onoff_callback *)kmalloc(sizeof(struct bsp_onoff_callback), GFP_KERNEL);
    if (NULL == callback)
    {
        pr_dbg("fail to malloc struct bsp_onoff_callback \n");
        return;
    }

    callback->fn = hook;

    spin_lock_irqsave(&list_spinlock, flags);
    list_add(&callback->node, &list_callback);
    spin_unlock_irqrestore(&list_spinlock, flags);
    /*coverity[leaked_storage] */
}

/******************************************************************************
*  Function:  drv_shut_down
*  Description: start the power off process.
*  Input:
*         eReason : shutdown reason.
*  Output:
*         None
*  Return:
*         None
*  Note  : �ײ���ùػ��ӿڣ����ö�ʱ�����ϱ��¼���Ӧ�á�
*          ��ʱʱ����Ӧ�ò��ػ����ɵײ�ǿ�ƹػ���
********************************************************************************/
void drv_shut_down( DRV_SHUTDOWN_REASON_ENUM enReason )
{
    static unsigned long drv_shut_down_set_flag = false;

	power_off_ctrl.off_timer.func = (softtimer_func)power_off_timeout_isr;
    if( DRV_SHUTDOWN_CHARGE_REMOVE == enReason )
    {
        if( DRV_START_MODE_NORMAL == bsp_start_mode_get() )
        {
            /* In normal mode, don't handle the charge remove message */
            return ;
        }
    }
    /*�ػ���������£��±�����֮����Ҫִ�йػ�����*/
    if(DRV_START_MODE_CHARGING == chg_get_start_mode() && DRV_SHUTDOWN_TEMPERATURE_PROTECT == enReason)
    {
        pr_dbg("NOW is poweroff state no need to shutdown.\n");
        return ;
    }

    if( DRV_SHUTDOWN_BUTT == enReason )
    {
        return ; /* the shutdown been handled, ignore this call */
    }

    if( DRV_SHUTDOWN_RESET == enReason )
    {
        pr_dbg("system will go to reboot!! \n");
        bsp_drv_power_reboot();
        return;
    }

    /* save the reason and drv_power_off need it */
    if (false == drv_shut_down_set_flag)
    {
        power_off_ctrl.reason = enReason;

        power_off_ctrl.off_timer.para = (u32)0;
        power_off_ctrl.off_timer.timeout = POWER_OFF_MONOTER_TIMEROUT;
        power_off_ctrl.off_timer.wake_type = SOFTTIMER_WAKE;

        if (bsp_softtimer_create(&power_off_ctrl.off_timer))
        {
            pr_dbg("create softtimer failed \n");
        }

        bsp_softtimer_add(&power_off_ctrl.off_timer);

        /* ����ɵײ��ϱ��ػ��¼�����Ӧ��ִ�йػ��ĳ��� */
        /* TO DO */
        drv_shut_down_set_flag = true;
        power_off_log_save();
    }
    else
    {
        return ;
    }
    /* Notify the monitor task */
}

/******************************************************************************
*  Function:  bsp_drv_power_off
*  Description: same as drv_power_off, the public API
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : Ӧ�õ��ùػ�ʱ���ã�at+cfun=8
********************************************************************************/
void bsp_drv_power_off( void )
{
    if(power_off_ctrl.reason == DRV_SHUTDOWN_BUTT)
    {
        /*Set shutdown reason to Power_key.*/
        power_off_ctrl.reason = DRV_SHUTDOWN_POWER_KEY;

        pr_dbg( "power off process triggered by a-cpu with power_key\n");
    }
    power_off_log_save();
    power_on_wdt_cnt_set();
    drv_power_off();
}

/******************************************************************************
*  Function:  bsp_drv_power_reboot
*  Description: same as drv_power_off, the public API
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : Ӧ�õ�������ʱ���ã�at+cfun=6
********************************************************************************/
void bsp_drv_power_reboot( void )
{
    /*Set shutdown reason to reset.*/
    power_off_ctrl.reason = DRV_SHUTDOWN_RESET;

    pr_dbg( "power reboot process triggered \n");
    power_off_log_save();

    reb_file_sync();
    power_on_wdt_cnt_set();


    power_off_set_flag_and_reboot((power_off_reboot_flag)(power_off_ctrl.reason));
}

/******************************************************************************
*  Function:  bsp_drv_power_reboot_direct
*  Description:
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : ֱ������
********************************************************************************/
void bsp_drv_power_reboot_direct( void )
{
    power_off_reboot_operation();
}

void bsp_drv_set_power_off_reason(DRV_SHUTDOWN_REASON_ENUM reason)
{
    power_off_ctrl.reason = reason;
}


/******************************************************************************
*  Function:  balong_power_restart
*  Description: same as bsp_drv_power_reboot, ϵͳ����ʱʹ��
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :android_reboot(ANDROID_RB_RESTART, 0, 0);
********************************************************************************/
/*lint -save -e958 */
void balong_power_restart(char mode, const char *cmd)
{
    bsp_drv_power_reboot();
}
/*lint -restore */

/******************************************************************************
*  Function:  balong_power_off
*  Description: same as bsp_drv_power_off, ϵͳ����ʱʹ��
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :android_reboot(ANDROID_RB_POWER_OFF, 0, 0);
********************************************************************************/
void balong_power_off( void )
{
	bsp_drv_power_off();
}

/******************************************************************************
*  Function:  debug����
*  Description: �ڲ�����ʱʹ��
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :
********************************************************************************/
void bsp_power_reboot_boot( void )
{
   power_reboot_cmd_set(POWER_REBOOT_CMD_BOOTLOADER);
   power_off_set_flag_and_reboot(POWER_OFF_REASON_RESET);
}

void bsp_power_reboot_recovery( void )
{
   power_reboot_cmd_set(POWER_REBOOT_CMD_RECOVERY);
   power_off_set_flag_and_reboot(POWER_OFF_REASON_RESET);
}

void bsp_power_reboot_warm( void )
{
   power_reboot_cmd_set(POWER_REBOOT_CMD_WARMRESET);
   power_off_set_flag_and_reboot(POWER_OFF_REASON_RESET);
}

