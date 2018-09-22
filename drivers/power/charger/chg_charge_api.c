


/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "chg_config.h"
#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
#include <bsp_nvim.h>
#endif
extern int32_t is_5577cs_falg;    /*FALSE:����5577Cs-321;TRUE:��5577Cs-321*/

/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/

/*Keep ret-code and data of intercore calling.*/
static int32_t chg_intercore_reply_data = 0;
static int32_t chg_intercore_reply_ret  = CHG_ERROR;

/*----------------------------------------------*
 * ģ�鼶����                                   *
 *----------------------------------------------*/

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/

static const chg_hw_param_t chg_pt_chgr_hw_paras[] =
{
    /*0:PT_Enable_Charge Setting*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {

    }

};

static CHG_TCHRENABLE_TYPE g_chg_tchrenable_status = 
{
        -1,
        -1
};

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/


int app_get_battery_state(BATT_STATE_T *battery_state)
{
    boolean power_off_charging_flag = FALSE;
    chg_stm_state_type real_charger_state = CHG_STM_INIT_ST;

    if(NULL == battery_state)
    {
        return CHG_ERROR;
    }

    battery_state->battery_level = chg_get_batt_level();
    battery_state->batt_temp_state = chg_get_batt_temp_state();
    real_charger_state = chg_stm_get_cur_state();
    power_off_charging_flag = chg_is_powdown_charging();

    if(FALSE == power_off_charging_flag)
    {
        /*���ĿǰΪ�ǹػ����ģʽ���Ƿ������ʵ��״̬
        ��ʾ**/
        if((CHG_STM_FAST_CHARGE_ST == real_charger_state) \
            || (CHG_STM_WARMCHG_ST == real_charger_state))
        {
            battery_state->charging_state = CHARGING_UP;
        }
        else
        {
            battery_state->charging_state = NO_CHARGING_UP;
        }
    }
    else
    {
        /* Ŀǰ����ػ������ʼ��״̬Ҳ��Ϊ�ǳ��
        ģʽ��ʱ�Ĺػ���綯���Ѿ�����***/
        if((CHG_STM_FAST_CHARGE_ST == real_charger_state) \
           || (CHG_STM_TRANSIT_ST  == real_charger_state) \
           || (CHG_STM_WARMCHG_ST == real_charger_state))
        {
            battery_state->charging_state = CHARGING_DOWN;
        }
        else
        {
            battery_state->charging_state = NO_CHARGING_DOWN;
        }
    }

    chg_print_level_message(CHG_MSG_DEBUG, "CHG_API: app charging_state =%d !!!\r\n", battery_state->charging_state);
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_API: app battery_level =%d !!!\r\n", battery_state->battery_level);
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_API: app batt_temp_state =%d !!!\r\n", battery_state->batt_temp_state);
    return CHG_OK;
}

#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
/**********************************************************************
�� �� ��  : chg_tbat_read
��������  : AT���ӿ�
�������  : ������ʽ:��(У׼ǰ/��)��ص������Ƕ���ѹУ׼ֵ
�������  : ��ص���/��ص�ѹУ׼ֵ
�� �� ֵ  : �Ƿ�����ɹ�
ע������  : 
***********************************************************************/
int chg_tbat_read(ENUM_CHG_ATCM_TYPE atID, void *pItem)
{
    int32_t ret = 0;
#if defined(BSP_CONFIG_BOARD_E5573S_853)
    int32_t index_i;
    int32_t volt_value[VOLT_NUMBER] = {0};
    int32_t volt_sum = 0;
    int32_t volt_avg = 0;
#endif /* BSP_CONFIG_BOARD_E5573S_853 */

    if(NULL == pItem)
    {
        chg_print_level_message(CHG_MSG_ERR,"invalid parameter!!\n");
        return CHG_ERROR;
    }
    switch(atID)
    {
        case CHG_AT_BATTERY_CHECK:
        {
            /*��ȡ��ص���У׼ֵ*/
            VBAT_CALIBRATION_TYPE * ptr = (VBAT_CALIBRATION_TYPE *)pItem;
            VBAT_CALIBRATION_TYPE tbat_check;

            ret = bsp_nvm_read(NV_BATT_VOLT_CALI_I, &tbat_check, sizeof(VBAT_CALIBRATION_TYPE));
            if(0 == ret)
            {
                ptr->max_value = tbat_check.max_value;
                ptr->min_value = tbat_check.min_value;
            }
            else
            {
                chg_print_level_message(CHG_MSG_ERR,"read chg nv failed when read check value\n");
                return CHG_ERROR;
            }
        }
        break;
        case CHG_AT_BATTERY_LEVEL:
        {
            /*��ȡУ׼��ĵ�ص�ѹ*/
#if defined(BSP_CONFIG_BOARD_E5573S_853)
            for(index_i = 0; index_i < VOLT_NUMBER; index_i++)
            {
                volt_value[index_i] = chg_get_batt_volt_value();
                volt_sum += volt_value[index_i];
            }
            volt_avg = volt_sum - chg_get_max_volt(volt_value, VOLT_NUMBER) \
                - chg_get_min_volt(volt_value, VOLT_NUMBER);
            *(int32_t*)pItem = volt_avg;
#else
            *(int32_t*)pItem = chg_get_batt_volt_value();
#endif /* BSP_CONFIG_BOARD_E5573S_853 */
        }
        break;

        /*У׼����AT�ӿ�*/
        case CHG_AT_BATTERY_ADC:
        {
            /*��ȡ���δУ׼�ĵ�ص�ѹ*/
#if defined(BSP_CONFIG_BOARD_E5573S_853)
            for(index_i = 0; index_i < VOLT_NUMBER; index_i++)
            {
                volt_value[index_i] = chg_get_volt_from_adc(CHG_PARAMETER__BATTERY_VOLT);
                volt_sum += volt_value[index_i];
            }
            volt_avg = volt_sum - chg_get_max_volt(volt_value, VOLT_NUMBER) \
                - chg_get_min_volt(volt_value, VOLT_NUMBER);
            *(int32_t*)pItem = volt_avg;
#else
            *(int32_t*)pItem = chg_get_volt_from_adc( CHG_PARAMETER__BATTERY_VOLT );
#endif /* BSP_CONFIG_BOARD_E5573S_853 */
        }
        break;
        /*��ȡ��ص���*/
        case CHG_AT_BATTERY_CAPACITY:
        {
            /*��ȡ��ص�������δʵ��*/
// *(int32_t*)pItem = chg_get_batt_volt_value();
        }
        break;

        default:
            return CHG_ERROR;
    }
    return  CHG_OK;
}
/**********************************************************************
�� �� ��  : chg_tbat_write
��������  : ATд�ӿ�:���õ�ص���У׼ֵ
�������  : 4.2V��3.4V��Ӧ��ADC����ֵ
�������  : ��
�� �� ֵ  : �Ƿ�����ɹ�
ע������  : ��
***********************************************************************/
int chg_tbat_write(ENUM_CHG_ATCM_TYPE atID, void *pItem)
{
    /*���õ�ص���У׼ֵ*/
    int32_t ret = 0;
    VBAT_CALIBRATION_TYPE * ptr = (VBAT_CALIBRATION_TYPE *)pItem;
    VBAT_CALIBRATION_TYPE tbat_org = {0};

    if(NULL == pItem)
    {
        chg_print_level_message(CHG_MSG_ERR,"invalid parameter!!\n");
        return CHG_ERROR;
    }

    switch(atID)
    {
        case CHG_AT_BATTERY_CHECK:
        {
            ret = bsp_nvm_read(NV_BATT_VOLT_CALI_I, &tbat_org, sizeof(VBAT_CALIBRATION_TYPE));
            if(ret)
            {
                chg_print_level_message(CHG_MSG_ERR,"read chg nv failed!!!\n");
                return CHG_ERROR;
            }
            
            if(TBAT_CHECK_INVALID == ptr->max_value)
            {
                ptr->max_value = tbat_org.max_value;
            }
            if(TBAT_CHECK_INVALID == ptr->min_value)
            {
                ptr->min_value = tbat_org.min_value;
            }
            
            ret = bsp_nvm_write(NV_BATT_VOLT_CALI_I, ptr, sizeof(VBAT_CALIBRATION_TYPE));
            if(ret)
            {
                chg_print_level_message(CHG_MSG_ERR,"write chg nv failed when set check value\n", 0, 0, 0);
                return CHG_ERROR;
            }


        }
        break;

        default:
            return CHG_ERROR;
    }
    return  CHG_OK;
}
/**********************************************************************
�� �� ��  : chg_tbat_charge_mode_set
��������  : ���õ�س����߷ŵ�
�������  : �������
�������  : none
�� �� ֵ  : CHG_OK:success,CHG_ERROR:fail
ע������  : 
***********************************************************************/
int chg_tbat_charge_mode_set(ENUM_CHG_MODE_TYPE cmd, unsigned int arg)
{
    int ret = 0;
    g_chg_tchrenable_status.chg_state = cmd;
    g_chg_tchrenable_status.chg_mode = arg;
    switch(cmd)
    {
        /*PT��λ���򿪳��*/
        case CHG_AT_CHARGE_ENABLE:
        {
            //BQ24192��֧��丳�Ϳ��ģʽ������
            //chg_set_hardware_parameter(&chg_pt_chgr_hw_paras[0]);
            chg_pt_mmi_test_proc();
        }
        break;
        /*�رճ��*/
        case CHG_AT_CHARGE_DISALBE:
        {
            (void)chg_set_charge_enable(FALSE);
        }
        break;
        /*�򿪷ŵ�*/
        case CHG_AT_DISCHARGE_ENABLE:
        {
            (void)chg_set_suspend_mode(TRUE);
        }
        break;
        /*�رշŵ�*/
        case CHG_AT_DISCHARGE_DISALBE:
        {
            (void)chg_set_suspend_mode(FALSE);
        }
        break;
        /*�򿪲���*/
        case CHG_AT_START_CHARGE_SPLY:
        {
            ret = chg_tbat_chg_sply();
            return ret;
        }
        break;

        default:
            return CHG_ERROR;
    }
    return  CHG_OK;
}
/**********************************************************************
�� �� ��  :  chg_tbat_status_get
��������  :  TBAT AT^TCHRENABLE?�Ƿ���Ҫ����

�������  : ��
�������  : ��
�� �� ֵ      : 1:��Ҫ����
			    0:����Ҫ����
ע������  : ��
***********************************************************************/
int chg_tbat_is_batt_status_ok(void)
{
    return chg_tbat_status_get();
}

/**********************************************************************
�� �� ��  : chg_tbat_get_charging_status
��������  : ��ѯ��ǰ���״̬
�������  : none
�������  : none
�� �� ֵ  : 1:charging,0:no
ע������  : 
***********************************************************************/
int chg_tbat_get_charging_status(void)
{
    return chg_is_IC_charging();
}

/**********************************************************************
�� �� ��  : chg_tbat_get_charging_status
��������  : ��ѯ��ǰ���ģʽ
�������  : none
�������  : none
�� �� ֵ  : 0:�ǳ�磻1��丳䣻2�����
ע������  : 
***********************************************************************/
int chg_tbat_get_charging_mode(void)
{
    chg_status_type  chg_stat = {0};
    int op_result = TRUE;

    op_result = chg_get_IC_status(&chg_stat);
    if (FALSE == op_result)
    {
        chg_print_level_message(CHG_MSG_ERR,"get IC status failed!!\n");
        return -1;
    }

    return chg_stat.chg_chrg_stat;
}
/**********************************************************************
�� �� ��  : chg_tbat_get_discharging_status
��������  : ��ѯ��ǰ�Ƿ���suspendģʽ
�������  : none
�������  : none
�� �� ֵ  : 1:yes,0:no
ע������  : 
***********************************************************************/
int chg_tbat_get_discharging_status(void)
{
    return chg_get_suspend_status();
}

/**********************************************************************
�� �� ��  : chg_tbat_sfeature_inquiry_extchg
��������  : ��ѯ�Ƿ�֧�ֶ�����
�������  : none
�������  : none
�� �� ֵ  : 1:yes,0:no
ע������  : 
***********************************************************************/
int chg_tbat_sfeature_inquiry_extchg(void)
{
#if (MBB_CHG_EXTCHG == FEATURE_ON)
    if(TRUE == is_5577cs_falg)
    {
        return FALSE;
    }
    return TRUE;
#else
    return FALSE;
#endif
}
/*****************************************************************************
 �� �� ��  : get_coul_support
 ��������  : ��Ʒ�Ƿ�֧�ֿ��ؼ�
 �������  : none
 �������  : none
 �� �� ֵ  : TRUE:֧�� FALSE:��֧��
 ע������  :
*****************************************************************************/
int get_coul_support(void)
    
{
#if (FEATURE_ON == MBB_CHG_BQ27510)
    return TRUE;
#else
    return FALSE;
#endif   
}
/**********************************************************************
�� �� ��  : chg_tbat_sfeature_inquiry_wireless
��������  : ��ѯ�Ƿ�֧�����߳��
�������  : none
�������  : none
�� �� ֵ  : 1:yes,0:no
ע������  : 
***********************************************************************/
int chg_tbat_sfeature_inquiry_wireless(void)
{
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    return TRUE;
#else
    return FALSE;
#endif
}
/**********************************************************************
�� �� ��  : chg_tbat_sfeature_inquiry_battery
��������  : ��ѯ��ص�ѹ����ֵ
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_tbat_sfeature_inquiry_battery(void)
{
    return -1;
}

/**********************************************************************
�� �� ��  : chg_MNTN_get_batt_state
��������  : AT���ӿ�
�������  : ��ѯ�Ƿ��ǿɲ�ж���
�������  : none
�� �� ֵ  : 1:�ɲ�ж��2�����ɲ�ж
ע������  : 
***********************************************************************/
int chg_MNTN_get_batt_state(void)
{
    /*��Ҫ���ݾ����Ʒ��ȷ���Ƿ��ǿɲ�ж���*/
#if (MBB_CHG_BAT_KNOCK_DOWN == FEATURE_ON)
    return KNOCK_DOWN_BATT_MODE;
#elif (MBB_CHG_BAT_KNOCK_DOWN == FEATURE_OFF)
    return FIX_BATT_MODE;
#else
    return NO_BATT_MODE;
#endif
}
/**********************************************************************
�� �� ��  : chg_wireless_mmi_test
��������  : AT���ӿڣ����߳���·���
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_wireless_mmi_test(void)
{
    return -1;
}
/**********************************************************************
�� �� ��  : chg_extchg_mmi_test
��������  : AT���ӿڣ��������·���
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_extchg_mmi_test(void)
{
    return -1;
}

/**********************************************************************
�� �� ��  : chg_extchg_mmi_test
��������  : AT���ӿڣ���ȡAT^TCHRENABLE���õĽ��
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_tbat_get_tchrenable_status(CHG_TCHRENABLE_TYPE *tchrenable_state)
{
    if(NULL == tchrenable_state)
    {
        return -1;
    }

    *tchrenable_state = g_chg_tchrenable_status;

    return 0;
}
/************************************************************************  
�� �� ��  : chg_getCbcState
��������  : ��������AT^CBC
         pucBcs
            0: ����ڹ���
            1: �������ӵ��δ����
            2: û����������
         pucBcl
            0:���������û����������
             100: ʣ������ٷֱ�
�������  : none
�������  : pucBcs��pucBcl
�� �� ֵ  : 
ע������  : 0 Success, -1 failed  
 ***********************************************************************/
int chg_getCbcState(unsigned char  *pucBcs ,unsigned char   *pucBcl)
{
    return 0;
}


int chg_get_coulometer_support(void)
{
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
    return YES;
#else 
    return NO;
#endif
}

#endif
/**********************************************************************
�� �� ��  : chg_usb_state_callback
��������  : ���ڻ�ȡ�˼���ú���:usb_enum_completed()��usb_charge_type()
            �ķ���ֵ��
�������  : STA:���ص�״ֵ̬��
�������  : �ޡ�
�� �� ֵ  : �ޡ�
ע������  : �ޡ�
**********************************************************************/
int chg_usb_state_callback(int STA, int Msg_Error)
{
    chg_intercore_reply_data = (int32_t)STA;
    chg_intercore_reply_ret =  (int32_t)Msg_Error;

    if (CHG_OK == chg_intercore_reply_ret)
    {
        return STA;
    }
    else
    {
        return Msg_Error;
    }
}
#define GPIO_SHUTDOWN   GPIO_2_16

int hw_sys_shut_down(void)
{
    int ret = -1;
    ret = gpio_direction_output(GPIO_SHUTDOWN, 1);
    return ret;
}
#ifdef BSP_CONFIG_BOARD_E5573S_853
/**********************************************************************
�� �� ��  : chg_get_max_volt
��������  : ��ȡ������ѹֵ�����ֵ
�������  : int volt[]����ȡ���ĵ�ѹֵ��int num����ȡ����ѹֵ�ĸ���
�������  : NA
�� �� ֵ  : max_volt:����ѹֵ
**********************************************************************/
int chg_get_max_volt(int volt[], int num)
{
    int index_i;
    int max_volt;
    max_volt = volt[0];

    for(index_i = 0; index_i < num; index_i++)
    {
        if(max_volt < volt[index_i])
        {
            max_volt = volt[index_i];
        }
    }
    return max_volt;
}
/**********************************************************************
�� �� ��  : chg_get_min_volt
��������  : ��ȡ������ѹֵ����Сֵ
�������  : int volt[]����ȡ���ĵ�ѹֵ��int num����ȡ����ѹֵ�ĸ���
�������  : NA
�� �� ֵ  : min_volt:��С��ѹֵ
**********************************************************************/
int chg_get_min_volt(int volt[], int num)
{
    int index_i;
    int min_volt;
    min_volt = volt[0];

    for(index_i = 0; index_i < num; index_i++)
    {
        if(min_volt > volt[index_i])
        {
            min_volt = volt[index_i];
        }
    }
    return min_volt;
}
#endif