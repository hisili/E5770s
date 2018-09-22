#ifndef __DRV_LEDS_H__
#define __DRV_LEDS_H__

#include "drv_comm.h"


/* ��ɫ��״̬���*/
enum
{
    LED_LIGHT_SYSTEM_STARTUP,
    LED_LIGHT_POWER_ON,
    LED_LIGHT_G_REGISTERED,
    LED_LIGHT_W_REGISTERED,
    LED_LIGHT_G_CONNECTED,
    LED_LIGHT_W_CONNNECTED,
    LED_LIGHT_H_CONNNECTED,
    LED_LIGHT_OFFLINE,
    LED_LIGHT_BURN_UPDATING,
    LED_LIGHT_FORCE_UPDATING,
    LED_LIGHT_NORMAL_UPDATING,
    LED_LIGHT_UPDATE_FAIL,
    LED_LIGHT_UPDATE_SUCCESS,
    LED_LIGHT_UPDATE_FILEFAIL,
    LED_LIGHT_UPDATE_NVFAIL,
    LED_LIGHT_SIM_ABSENT,
    LED_LIGHT_SHUTDOWN,
    LED_LIGHT_G_PLMN_SEARCH,
    LED_LIGHT_W_PLMN_SEARCH,
    LED_LIGHT_L_REGISTERED,
#if (FEATURE_ON == MBB_COMMON)
    LED_LIGHT_L_CONNECTED,    /*����H connect̬��LTE connect̬*/
    LED_LIGHT_SIM_LOCK,       /*SIM LOCK״̬*/
#endif
    LED_LIGHT_STATE_MAX = 32
};/*the state of LED */


/****************************************************************************
 �� �� ��  : drv_led_state_func_reg
 ��������  : ���ӿ�Ϊ�ṩ��Э��ջ�Ĺ��Ӻ��������ڻ�ȡЭ��ջ�ĵ��״̬��
 �������  : Э��ջ��ȡ���״̬������ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
 ע������  : �ޡ�

******************************************************************************/
void drv_led_state_func_reg (pFUNCPTR p);

#define DRV_LED_STATE_FUNREG(p)  drv_led_state_func_reg(p)

/*****************************************************************************
 �� �� ��  : drv_led_flash
 ��������  : ��ɫ�����á�
 �������  : status����ɫ�Ƶ�״̬
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
int drv_led_flash(unsigned long state);

#define DRV_LED_FLUSH(state)  drv_led_flash(state)  

/*****************************************************************************
 �� �� ��  : BSP_MNTN_LedControlAddressGet
 ��������  : �õ����Ƶĵ������
 �������  : ��
 �������  : �ޡ�
 �� �� ֵ  : ��ƿ������ݵ�ȫ�ֱ�����ַ
*****************************************************************************/
static INLINE unsigned int BSP_MNTN_LedControlAddressGet(void)
{
    return 0;
}
#define DRV_LED_GET_ADDRESS()   BSP_MNTN_LedControlAddressGet()

#endif /* #ifndef __DRV_LEDS_H__ */
