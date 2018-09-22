


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/

//���������ڴ�ͷ�ļ�������ֲ��Ա����
#include "chg_config.h"
#include "bsp_coul.h"
#include <bsp_version.h>
#include "chg_charge_stm.h"
#include <bsp_sram.h>
/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG && FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
extern int usb_get_switch_direction(void);
#endif

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/
 /*���ʱ��ͳ��*/
int chg_time_in_second = 0;
/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/
#define MS_ONE_SECOND  (1000)
#define SECOND_ONE_MIN  (60)
#if (MBB_CHG_COULOMETER == FEATURE_ON)
#define POLL_SOC_CYCLE    (SLOW_POLL_CYCLE/FAST_POLL_CYCLE)    
#endif
extern int32_t is_5577cs_falg = FALSE;    /*FALSE:����5577Cs-321;TRUE:��5577Cs-321*/
/**********************************************************************
�� �� ��: chg_charge_time_static
��������:��ʱ���¼�����ʱ��,��¼���ʱ��
�������: None
�������: None
�� �� ֵ: None
ע������: ��¼���ʱ��,�����ֹͣ
***********************************************************************/
void chg_charge_time_static (void)
{
    chg_stm_state_type tmp_sta = chg_stm_get_cur_state();
    int ret_val = chg_poll_timer_get();

    if ( -1 == ret_val )
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_TASK:Chg poll time NOT correct!!!\r\n");
        return;
    }
    else
    {
        ret_val /= MS_ONE_SECOND; /*�ɺ���ת������*/

        /*��ӡ��ʱʱ��*/
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_TASK:Chg poll time is %d s!!!\r\n", ret_val);
    }

    if ( -1 != chg_time_in_second )
    {
        //��ǰ���ڿ����߸��³��״̬
        if ((CHG_STM_FAST_CHARGE_ST == tmp_sta) || (CHG_STM_WARMCHG_ST == tmp_sta) )
        {
            chg_time_in_second += ret_val;
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_TASK:charging last %d minute and %d second!!!\r\n", \
                (chg_time_in_second / SECOND_ONE_MIN),  (chg_time_in_second % SECOND_ONE_MIN));
        }
        else if ( CHG_STM_MAINT_ST == tmp_sta )
        {
            chg_time_in_second = -1;
            chg_print_level_message(CHG_MSG_ERR, "CHG_TASK:Maint charge happen, static will STOP!!!\r\n");
        }
        else
        {
            //for lint
        }
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_TASK:maint charge has happened clean the chg_time_in_second!\r\n");
    }
}

/**********************************************************************
�� �� ��: chg_main_task
��������: ��һ���������
�������: None
�������: None
�� �� ֵ: None
ע������: ������Linux��Vxworks��ʵ��
          ��Ϊ��ϵͳ����,���ע�������Ӧ�Ŀ��ļ�
***********************************************************************/
int32_t  chg_main_task( void  *task_para )
{
    uint32_t event_recv = 0;
    int32_t  ulResult2;
#if (MBB_CHG_COULOMETER == FEATURE_ON)
    uint32_t poll_count = 0;    
#endif

    chg_print_level_message(CHG_MSG_DEBUG, "CHG_TASK:chg_main_task->start_creart!!!\r\n");

    if ( NULL == task_para )
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_TASK:chg_main_task->start_creart!!!\r\n");
    }

    /*����һ�ο��ؼ�ǿ��У׼*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_TASK:COUL_CAIL_ON");
    //bsp_coul_cail_on();
    msleep(COUL_READY_DELAY_MS);
#if (MBB_CHG_COULOMETER == FEATURE_ON)
    /*update the SOC*/
    chg_poll_batt_soc();
#endif
    /* ��һ�ε��״̬����ѯ��ѯ**/
    chg_poll_bat_level();

    /*��ֹ���������£���������/USB��2s���ҵĳ�����*/
    chg_poll_batt_temp();
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_TASK:Init chg_poll_timer 2S!!!\r\n");
    /*��ʼ�����������ѯ*/
    chg_poll_timer_set( FAST_POLL_CYCLE );

#if (MBB_CHG_EXTCHG == FEATURE_ON)
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
#else
    chg_extchg_config_data_init();
#endif
#endif /*defined(MBB_CHG_EXTCHG)*/
    ulResult2 = chg_stm_init();
    if(CHG_OK != ulResult2)
    {
        //��ӡ��ʼ��ʧ��log
        return -1;
    }

    while(FALSE == this_kthread_should_stop())
    {
        /*�ȴ��¼�,����ᱻ����*/
        if ( -1 == chg_main_wait_for_msg( &event_recv ) )
        {
            continue;
        }


        /*�鿴�����ź��Ƿ���Ч*/
        if ( CHG_ALL_EVENT & event_recv )
        {
            /* ������ѯ��ʱ���¼��ϱ�*/
            if ( CHG_TIMER_EVENT & event_recv )
            {
                chg_print_level_message(CHG_MSG_INFO, "CHG_TASK:CHG_TIMER_EVENT detected!!!\n");

                event_recv &= ( ~CHG_TIMER_EVENT );

                /*Feed the WDT of charge IC.*/
                if (FALSE == chg_set_tmr_rst())
                {
                    chg_print_level_message(CHG_MSG_ERR, "CHG_TASK:Feed IC WDT error!\n");
                }
#if (MBB_CHG_COULOMETER == FEATURE_ON)
                if(FAST_POLL_CYCLE == chg_poll_timer_get())
                {
                    poll_count++; 
                }
                else if(SLOW_POLL_CYCLE == chg_poll_timer_get())
                {
                    poll_count = POLL_SOC_CYCLE; 
                }
                else
                {
                    poll_count = POLL_SOC_CYCLE; 
                }
                if(POLL_SOC_CYCLE == poll_count)
                {
                    /*update the SOC*/
                    chg_poll_batt_soc();
                    poll_count = 0; 
                }
#endif
                /* ��ʱ��ص�ѹ��ѯ��ѯ**/
                chg_poll_bat_level();

                /* ��ʱ����¶���ѯ��ѯ**/
                chg_poll_batt_temp();

                /*����power supply ���ڵ��״̬��Ϣ*/
                chg_update_power_suply_info();

                /*Call STM periodic checking function.*/
                chg_stm_periodic_checking_func();
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
                /*update charge state,if change,notify coul*/
                chg_poll_batt_charging_state_for_coul();
#endif

                /*��ά�ɲ�:ͳ�ƿ��ʱ��*/
                chg_charge_time_static();
                chg_print_test_view_info();
            }

            /*��Դ�����¼��ϱ�*/
            if (CHG_CHARGER_IN_EVENT & event_recv )
            {
                event_recv &= ( ~CHG_CHARGER_IN_EVENT );
                chg_print_level_message(CHG_MSG_ERR, "CHG_TASK:chg_main_task->charger_input!!!\r\n ");

                /*If chgr input event received during start-up phase, doNOT switch to
                  transit state again, since we have done already in chg_stm_init.*/
                if(is_chg_charger_removed())
                {
                    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:charger is not online,do nothing!\n");
                }
                else
                {
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG && FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
                    if (!usb_get_switch_direction())
                    {
                        chg_charger_insert_proc(extchg_charger_type_detect());
                    }
                    else
                    {
                        chg_charger_insert_proc(chg_stm_get_chgr_type());
                    }
#else
                    chg_charger_insert_proc(chg_stm_get_chgr_type());
#endif
                }
            }

            /*��Դ�γ��¼��ϱ�*/
            if ( CHG_CHARGER_OUT_EVENT & event_recv )
            {
                event_recv &= ( ~CHG_CHARGER_OUT_EVENT );
                chg_print_level_message(CHG_MSG_ERR, "CHG_TASK:chg_main_task->charger_output!!!\r\n ");

                if(is_chg_charger_removed())
                {
                    chg_charger_remove_proc(chg_stm_get_chgr_type());
                }
                else
                {
                    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:charger is online,do nothing!\n");
                }
            }

            /* ������ʱ��ʱ���л�����*/
            if( CHG_POLL_TIMER_CHANGE & event_recv )
            {
                event_recv &= ( ~CHG_POLL_TIMER_CHANGE );
                chg_print_level_message(CHG_MSG_DEBUG, "CHG_TASK:chg_main_task->CHG_POLL_TIMER_CHANGE!!!\r\n ");

            }

            /*��Դ���ͼ���¼�*/
            if( CHG_CHGR_TYPE_CHECKING_EVENT & event_recv )
            {
                event_recv &= ( ~CHG_CHGR_TYPE_CHECKING_EVENT );
                chg_print_level_message( CHG_MSG_DEBUG,"CHG_TASK:chg_main_task->CHG_CHGR_TYPE_CHECKING_EVENT!!!\r\n ");

                /*Call STM try to check chgr type and update hw parameters.*/
                chg_check_and_update_hw_param_per_chgr_type();
            }
        }
    }
    return 0;
}
/**********************************************************************
�� �� ��      : chg_basic_init
��������  :  ������ʼ��:
                          ���оƬ+˫��ͨ��
�������  : ��
�������  : ��
�� �� ֵ      : ��
ע������  : ��Ԥ��粿�ֵ���
                         �ɸ��ݾ���ƽ̨���ɾ��
***********************************************************************/
void chg_basic_init( void )
{
    static int32_t s_chg_basic_init_flag = FALSE;
    chg_print_level_message(CHG_MSG_DEBUG,"CHG_TASK:chg_basic_init \n ");

    if( FALSE == s_chg_basic_init_flag )
    {
        s_chg_basic_init_flag = TRUE;

/***************Note:ƽ̨��ش��룬����ƽ̨����Ҫ��ӣ��е�ƽ̨��V7R1��Ҫ
              ��ֲ��Ա������Ҫ����ӻ����Ƴ��±ߺ�������***************************/
        /* �˼�ͨ�ų�ʼ��*/
        //BSP_CHGC_Init();

        /* ���оƬ��ʼ��*/
        chg_chip_init();
#if (MBB_CHG_EXTCHG == FEATURE_ON)
        extchg_gpio_init();
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
        extchg_gpio_isr_init();

#endif
#endif/*MBB_CHG_EXTCHG*/

#if (MBB_CHG_WIRELESS == FEATURE_ON)
        wireless_gpio_init();
#endif/*MBB_CHG_WIRELESS*/
    }
}
/**********************************************************************
�� �� ��      : chg_task_init
��������  :  ������ʼ��,��������е�charger�Ļ�������
                            ����������񼰶�ʱ��
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ      : �ޡ�
ע������  : �ޡ�
***********************************************************************/
void chg_task_init(void)
{
    huawei_smem_info *smem_data = NULL;
    smem_data = (huawei_smem_info *)SRAM_DLOAD_ADDR;
    /*�ж��Ƿ���5577Cs-321,��Ϊ5577Cs-321��5577s-321�����ƹ�һ�������ǲ�֧�ֶ�����*/
    unsigned int id = 0xffffffff;
    id = (unsigned int)bsp_version_get_boardid();//��ȡ����Ӳ��ID
	/* E5577Ds-156ΪE5577Cs-321������Ŀ�汾��E5577Cs-321��E5577s-321���ж����ƹ�һ�����͵�ص�������E5577Cs-321һ��*/
    if((id == HW_VER_PRODUCT_E5577CS_321) || (id == HW_VER_PRODUCT_E5577DS_156))
    {
        is_5577cs_falg = TRUE;
    }
    else
    {
        is_5577cs_falg = FALSE;
    }
    /*Ӳ����ز�����ʼ��*/
    //chg_hardware_paras_init();
    /*������ģʽ�Ž��г����ز�����ʼ���������������*/
    if(FALSE == is_in_update_mode())
    {
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
        if (TRUE == chg_is_powdown_charging() && FALSE == chg_is_charger_present() \
            && gpio_get_value(EXTCHG_OTG_DET_GPIO))
#else
        if (TRUE == chg_is_powdown_charging() && FALSE == chg_is_charger_present())
#endif
        {
           chg_print_level_message(CHG_MSG_ERR,"CHG_TASK:POWER OFF FOR CHARGER REMOVE !\n ");
           chg_set_power_off(DRV_SHUTDOWN_CHARGE_REMOVE);
        }
        load_ftm_mode_init();
        chg_basic_init();

        load_on_off_mode_parameter();

        chg_batt_volt_init();
        chg_batt_temp_init();

        chg_batt_volt_calib_init();

        chg_print_level_message(CHG_MSG_DEBUG,"CHG_TASK:task init success!\n");
        /*�ǹ���ģʽ�����������*/
        if(FALSE == chg_is_ftm_mode())
        {
            /*�����������*/
            chg_task_create();
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_TASK:task creat success!\n");
        }
        /*����ģʽ�������������*/
        else
        {
            //��Ƭ�汾�޸�����Ϊ1200mA
            if(FALSE == chg_set_supply_limit(CHG_IINPUT_LIMIT_2000MA))
            {
                 chg_print_level_message(CHG_MSG_ERR,"chg_set_supply_limit:chg_set_supply_limit failed!\n");
            }

            chg_set_sys_batt_capacity(BATT_CAPACITY_FULL);
            chg_print_level_message(CHG_MSG_ERR,"CHG_TASK:chg task does not creat in FTM!\n");
        }
    }
    /*����ģʽ�����е�ص�ѹУ׼��ʼ������������������Է�ֹӰ�������ȶ���*/
    else
    {
#if (FEATURE_ON == MBB_DLOAD_SDUP)
        if((smem_data != NULL) && (smem_data->smem_sd_upgrade == SMEM_SDUP_FLAG_NUM))
        {
             chg_batt_volt_init();
        }
#endif
        chg_batt_volt_calib_init();
        chg_print_level_message(CHG_MSG_INFO,"CHG_TASK:Dload mode do not creat chg task!\n");
        return;
    }
}

/***************Note:ƽ̨��ش��룬����ƽ̨����Ҫ��ӣ��е�ƽ̨��9x25 Linuxϵͳ��Ҫ
              ��ֲ��Ա������Ҫ����ӻ����Ƴ��±ߺ�������***************************/
static int __init charger_init(void)
{
    //charge init
    chg_task_init();
    return 0;
}
module_init(charger_init);

static void __exit charger_exit(void)
{
    //ready to add exit code
    return;
}
module_exit(charger_exit);

MODULE_DESCRIPTION("Charger driver");

MODULE_LICENSE("GPL v2");

