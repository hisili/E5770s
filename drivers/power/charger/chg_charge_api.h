#ifndef CHG_CHARGE_API_H
#define CHG_CHARGE_API_H




/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/
#include "chg_config.h"

#if defined(BSP_CONFIG_BOARD_E5573S_853)
#define VOLT_NUMBER    3
#endif /* BSP_CONFIG_BOARD_E5573S_853 */

#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
/**********************************************************************
�� �� ��  : chg_tbat_read
��������  : AT���ӿ�
�������  : ������ʽ:��(У׼ǰ/��)��ص������Ƕ���ѹУ׼ֵ
�������  : ��ص���/��ص�ѹУ׼ֵ
�� �� ֵ  : �Ƿ�����ɹ�
ע������  : 
***********************************************************************/
int chg_tbat_read(ENUM_CHG_ATCM_TYPE atID, void *pItem);

/**********************************************************************
�� �� ��  : chg_tbat_write
��������  : ATд�ӿ�:���õ�ص���У׼ֵ
�������  : 4.2V��3.4V��Ӧ��ADC����ֵ
�������  : ��
�� �� ֵ  : �Ƿ�����ɹ�
ע������  : ��
***********************************************************************/
int chg_tbat_write(ENUM_CHG_ATCM_TYPE atID, void *pItem);

/**********************************************************************
�� �� ��  : chg_tbat_charge_mode_set
��������  : ���õ�س����߷ŵ�
�������  : �������
�������  : none
�� �� ֵ  : CHG_OK:success,CHG_ERROR:fail
ע������  : 
***********************************************************************/
int chg_tbat_charge_mode_set(ENUM_CHG_MODE_TYPE cmd, unsigned int arg);

/**********************************************************************
�� �� ��  :  chg_tbat_status_get
��������  :  TBAT AT^TCHRENABLE?�Ƿ���Ҫ����

�������  : ��
�������  : ��
�� �� ֵ      : 1:��Ҫ����
			    0:����Ҫ����
ע������  : ��
***********************************************************************/
int chg_tbat_is_batt_status_ok(void);
/**********************************************************************
�� �� ��  : chg_tbat_get_charging_status
��������  : ��ѯ��ǰ���״̬
�������  : none
�������  : none
�� �� ֵ  : 1:charging,0:no
ע������  : 
***********************************************************************/
int chg_tbat_get_charging_status(void);
/**********************************************************************
�� �� ��  : chg_tbat_get_charging_status
��������  : ��ѯ��ǰ���ģʽ
�������  : none
�������  : none
�� �� ֵ  : 0:�ǳ�磻1��丳䣻2�����
ע������  : 
***********************************************************************/
int chg_tbat_get_charging_mode(void);
/**********************************************************************
�� �� ��  : chg_tbat_get_discharging_status
��������  : ��ѯ��ǰ�Ƿ���suspendģʽ
�������  : none
�������  : none
�� �� ֵ  : 1:yes,0:no
ע������  : 
***********************************************************************/
int chg_tbat_get_discharging_status(void);
/**********************************************************************
�� �� ��  : chg_tbat_sfeature_inquiry_extchg
��������  : ��ѯ�Ƿ�֧�ֶ�����
�������  : none
�������  : none
�� �� ֵ  : 1:yes,0:no
ע������  : 
***********************************************************************/
int chg_tbat_sfeature_inquiry_extchg(void);
/**********************************************************************
�� �� ��  : chg_tbat_sfeature_inquiry_battery
��������  : ��ѯ��ص�ѹ����ֵ
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_tbat_sfeature_inquiry_battery(void);
/**********************************************************************
�� �� ��  : chg_MNTN_get_batt_state
��������  : AT���ӿ�
�������  : ��ѯ�Ƿ��ǿɲ�ж���
�������  : none
�� �� ֵ  : 1:�ɲ�ж��2�����ɲ�ж
ע������  : 
***********************************************************************/
int chg_MNTN_get_batt_state(void);
/**********************************************************************
�� �� ��  : chg_wireless_mmi_test
��������  : AT���ӿڣ����߳���·���
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_wireless_mmi_test(void);
/**********************************************************************
�� �� ��  : chg_extchg_mmi_test
��������  : AT���ӿڣ��������·���
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_extchg_mmi_test(void);
/**********************************************************************
�� �� ��  : chg_extchg_mmi_test
��������  : AT���ӿڣ���ȡAT^TCHRENABLE���õĽ��
�������  : none
�������  : none
�� �� ֵ  : 
ע������  : 
***********************************************************************/
int chg_tbat_get_tchrenable_status(CHG_TCHRENABLE_TYPE *tchrenable_state);
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
int chg_getCbcState(unsigned char  *pucBcs ,unsigned char   *pucBcl);

/************************************************************************  
�� �� ��  : chg_get_coulometer_support
��������  : ��ѯ��ǰ��Ʒ�Ƿ�֧�ֿ��ؼ�
�������  : none
�������  : none
�� �� ֵ  : NO-0 ��֧�֣�YES-1 ֧��
ע������  : 0 Success, -1 failed  
 ***********************************************************************/
int chg_get_coulometer_support(void);

#endif

#if 0 /*ʹ��power supply����ʱ�˺������ڶ�Ӧ�ÿ���,��LINUXϵͳ��Ҫ�򿪴˺�����ͬʱ�ڶ���ĵط�ȥ��static������*/
int app_get_battery_state(BATT_STATE_T *battery_state);
#endif

/**********************************************************************
�� �� ��      : chg_usb_state_callback
��������  : ���ڻ�ȡ�˼���ú���:usb_enum_completed()��usb_charge_type()
                             �ķ���ֵ��
�������  : STA:���ص�״ֵ̬��
�������  : �ޡ�
�� �� ֵ      : �ޡ�
ע������  : �ޡ�
**********************************************************************/
extern int32_t chg_usb_state_callback(int32_t STA, int32_t Msg_Error);
/*****************************************************************************
 �� �� ��  : hw_sys_shut_down
 ��������  : ����GPIO_2_16ʵ��Ӳ���ػ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ȡ�ɹ�: 0
             ��ȡʧ��: -1
*****************************************************************************/
int hw_sys_shut_down(void);
#ifdef BSP_CONFIG_BOARD_E5573S_853
/**********************************************************************
�� �� ��  : chg_get_max_volt
��������  : ��ȡ������ѹֵ�����ֵ
�������  : int volt[]����ȡ���ĵ�ѹֵ��int num����ȡ����ѹֵ�ĸ���
�������  : NA
�� �� ֵ  : max_volt:����ѹֵ
**********************************************************************/
int chg_get_max_volt(int volt[], int num);
/**********************************************************************
�� �� ��  : chg_get_min_volt
��������  : ��ȡ������ѹֵ����Сֵ
�������  : int volt[]����ȡ���ĵ�ѹֵ��int num����ȡ����ѹֵ�ĸ���
�������  : NA
�� �� ֵ  : min_volt:��С��ѹֵ
**********************************************************************/
int chg_get_min_volt(int volt[], int num);
#endif
#endif
