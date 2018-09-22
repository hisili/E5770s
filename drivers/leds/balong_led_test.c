

#ifdef __cplusplus
extern "C"
{
#endif

#include "bsp_leds.h"

#ifdef __KERNEL__
#include <linux/platform_device.h>
#include <linux/delay.h>
#include <linux/regulator/consumer.h>
#include "leds_balong.h"

#define LED_NUMBER 5
#define LED_BLINK_PERIOD_MAX 1968750
#define LED_BLINK_FULLON_MAX 242203
#define LED_BREATH_FADEONOFF_MAX 4000000
#define LED_BREATH_FULLONOFF_MAX_DR12 4000000
#define LED_BREATH_FULLONOFF_MAX_DR345 16000000

#define sleep(s) msleep(s*1000)

extern LED_CONTROL_NV_STRU g_led_state_str_lte[LED_LIGHT_STATE_MAX][LED_CONFIG_MAX_LTE];
extern struct platform_device balong_led_dev;
extern struct nv_led g_nv_led;
extern struct led_tled_arg g_arg;
extern void led_on(unsigned int led_id);
extern void led_off(unsigned int led_id);
extern void led_threecolor_state_switch(unsigned char new_color, unsigned char old_color);

/************************************************************************
 * Name         : led_test_case_001
 * Function     :
 * Arguments
 *      input   : led_id:0~4
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : ����idΪled_id�Ƶ����ȿ��ƹ��ܡ�
 ************************************************************************/
int led_test_case_001(int led_id)
{
    int ret = LED_ERROR;
    enum led_brightness brightness;
	struct balong_led_device *led = NULL;

    led = (struct balong_led_device *)platform_get_drvdata(&balong_led_dev);
    if(!led)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ALWAYS),"get balong led device failed.\n");
        return LED_ERROR;
    }

    /* test every brightness for a certain led, including two illegal brightness*/
    /*lint -save -e685*/ 
    for(brightness = LED_OFF; brightness <= LED_FULL ; brightness++)
    {
        LED_TRACE(LED_DEBUG_LEVEL(INFO),"\n[%s] ===TEST=== led id %d, brightness %d\n",
                __FUNCTION__, led_id, brightness);

        led[led_id].cdev.brightness_set(&(led[led_id].cdev), brightness);   /* set brightness */            
        ret = led[led_id].cdev.brightness_get(&(led[led_id].cdev));
        if(ret != brightness)
        {
            LED_TRACE(LED_DEBUG_LEVEL(ERROR),"\n[%s]ERROR:led id %d, brightness set %d, get %d\n",
                    __FUNCTION__, led_id + 1, brightness, ret);
            return LED_ERROR;
        }
    }
    /*lint -restore*/  

    return LED_OK;
}

/************************************************************************
 * Name         : led_test_case_002
 * Function     :
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : ����ÿ��led�Ƶ���������
 ************************************************************************/
int led_test_case_002(void)
{
    int led_id;
    int ret;
    for(led_id = 0; led_id < LED_ID_MAX; led_id++)
    {
        ret = led_test_case_001(led_id);
        if(ret != LED_OK)
        {
            LED_TRACE(LED_DEBUG_LEVEL(ERROR),"\n[%s]ERROR:led id %d, ret %d\n",
                    __FUNCTION__, led_id + 1, ret);
            return LED_ERROR;
        }
    }
    return LED_OK;
}

/************************************************************************
 * Name         : led_test_case_003
 * Function     :
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : ����led_id�Ƶ���˸ģʽ���ƹ���
 ************************************************************************/
int led_test_case_003(int led_id)
{
    int ret = LED_ERROR;
    unsigned long full_on = LED_BLINK_FULLON_MAX, full_off = LED_BLINK_PERIOD_MAX - LED_BLINK_FULLON_MAX;
	struct balong_led_device *led = NULL;

    led = (struct balong_led_device *)platform_get_drvdata(&balong_led_dev);
    if(!led)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"get balong led device failed.\n");
        return LED_ERROR;
    }

    /* set brightness */
    ret = led[led_id].cdev.blink_set(&(led[led_id].cdev), &full_on, &full_off);
    if(ret)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"\n[%s]ERROR:led id %d, set blink error, ret %d\n",
                __FUNCTION__, led_id + 1, ret);
        return LED_ERROR;
    }

    return LED_OK;
}
/************************************************************************
 * Name         : led_test_case_004
 * Function     :
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : ����ÿ��led�Ƶĺ���ģʽ���ƹ���
 ************************************************************************/
int led_test_case_004(void)
{
    int led_id;
    int ret;
    for(led_id = 0; led_id < LED_ID_MAX; led_id++)
    {
        ret = led_test_case_003(led_id);
        if(ret != LED_OK)
        {
            LED_TRACE(LED_DEBUG_LEVEL(ERROR),"\n[%s]ERROR:led id %d, ret %d\n",
                    __FUNCTION__, led_id + 1, ret);
            return LED_ERROR;
        }
    }
    
    return LED_OK;
}


/************************************************************************
 * Name         : led_test_case_005
 * Function     :
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : ����led_id�Ƶĺ���ģʽ���ƹ���
 ************************************************************************/
int led_test_case_005(int led_id)
{
    int ret = LED_ERROR;
    unsigned long full_onoff, fade_onoff = LED_BREATH_FADEONOFF_MAX;
    
	struct balong_led_device *led = NULL;

    led = (struct balong_led_device *)platform_get_drvdata(&balong_led_dev);
    if(!led)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"get balong led device failed.\n");
        return LED_ERROR;
    }

    /* set brightness */
    if((0 == led_id) || (1 == led_id))
    {
        full_onoff = LED_BREATH_FULLONOFF_MAX_DR12;
    }
    else
    {
        full_onoff = LED_BREATH_FULLONOFF_MAX_DR345;
    }
    
    ret = led[led_id].pdata->led_breath_set(&(led[led_id].cdev), 
        &full_onoff, &full_onoff, &fade_onoff, &fade_onoff);
    if(ret)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"\n[%s]ERROR:led id %d, set blink error, ret %d\n",
                __FUNCTION__, led_id + 1, ret);
        return LED_ERROR;
    }

    return LED_OK;
}

/************************************************************************
 * Name         : led_test_case_006
 * Function     :
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : ����ÿ��led�Ƶĺ���ģʽ���ƹ���
 ************************************************************************/
int led_test_case_006(void)
{
    int led_id;
    int ret;
    for(led_id = 0; led_id < LED_ID_MAX; led_id++)
    {
        ret = led_test_case_005(led_id);
        if(ret != LED_OK)
        {
            LED_TRACE(LED_DEBUG_LEVEL(ERROR),"\n[%s]ERROR:led id %d, ret %d\n",
                    __FUNCTION__, led_id + 1, ret);
            return LED_ERROR;
        }
    }
    
    return LED_OK;
}

/************************************************************************
 * Name         : do_led_tled_test_case
 * Function     : ����A����ɫ����˸����
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : ���漰�˼�ͨ�ţ�ֻ����A����ɫ�����Ʒ���
 ************************************************************************/
int do_led_tled_test_case(unsigned long new_state)
{
    int ret = LED_ERROR;
	struct balong_led_device *led = NULL;
    led = (struct balong_led_device *)platform_get_drvdata(&balong_led_dev);
    if(!led)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ALWAYS),"get balong led device failed.\n");
        goto ERRO;
    }    

    g_arg.new_state = (unsigned char)new_state;
    g_arg.ctl = MNTN_LED_STATUS_FLUSH;    

    ret = do_led_threecolor_flush();
    if(ret)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR), "[%s]three color led flush failed, ret = %d!\n", __FUNCTION__, ret);
        return ret;
    }

    return ret;
    
ERRO:
    return ret;  
}

/************************************************************************
 * Name         : led_tled_test_case_001
 * Function     : ����A����ɫ���̵�˫������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_001(void)
{
    return do_led_tled_test_case(LED_LIGHT_SYSTEM_STARTUP);
}

/************************************************************************
 * Name         : led_tled_test_case_002
 * Function     : ����A����ɫ���̵Ƶ�������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_002(void)
{
    return do_led_tled_test_case(LED_LIGHT_G_REGISTERED);
}

/************************************************************************
 * Name         : led_tled_test_case_003
 * Function     : ����A����ɫ���̵�Ƶ������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_003(void)
{
    return do_led_tled_test_case(LED_LIGHT_FORCE_UPDATING);
}

/************************************************************************
 * Name         : led_tled_test_case_004
 * Function     : ����A����ɫ���̵Ƴ�������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_004(void)
{
    return do_led_tled_test_case(LED_LIGHT_G_CONNECTED);
}

/************************************************************************
 * Name         : led_tled_test_case_005
 * Function     : ����A����ɫ�����Ƶ�������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_005(void)
{
    return do_led_tled_test_case(LED_LIGHT_W_REGISTERED);
}

/************************************************************************
 * Name         : led_tled_test_case_006
 * Function     : ����A����ɫ������Ƶ������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_006(void)
{
    return do_led_tled_test_case(LED_LIGHT_UPDATE_NVFAIL);
}

/************************************************************************
 * Name         : led_tled_test_case_007
 * Function     : ����A����ɫ�����Ƴ�������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_007(void)
{
    return do_led_tled_test_case(LED_LIGHT_W_CONNNECTED);
}

/************************************************************************
 * Name         : led_tled_test_case_008
 * Function     : ����A����ɫ����Ƶ�������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : ����ɫ��nvû���ù���Ƶ������ܣ������g_led_state_str_lte[18]������nv�����Բ���
 ************************************************************************/
int led_tled_test_case_008(void)
{
    memcpy((void *)g_nv_led.g_led_state_str_om[LED_LIGHT_STATE_MAX - 1], (void *)g_led_state_str_lte[18], 
        (unsigned int)(LED_CONFIG_MAX_LTE * sizeof(LED_CONTROL_NV_STRU)));
    
    return do_led_tled_test_case(LED_LIGHT_STATE_MAX - 1);
}

/************************************************************************
 * Name         : led_tled_test_case_009
 * Function     : ����A����ɫ����Ƴ�������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_009(void)
{
    return do_led_tled_test_case(LED_LIGHT_H_CONNNECTED);
}

/************************************************************************
 * Name         : led_tled_test_case_010
 * Function     : ����A����ɫ�����̽�����˸����
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_010(void)
{
    return do_led_tled_test_case(LED_LIGHT_UPDATE_FILEFAIL);
}

/************************************************************************
 * Name         : led_tled_test_case_011
 * Function     : ����A����ɫ�ƺ��˫������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_011(void)
{
    LED_CONTROL_NV_STRU temp[LED_CONFIG_MAX_LTE] = LED_RED_LIGHTING_DOUBLE;

    memcpy((void *)g_nv_led.g_led_state_str_om[LED_LIGHT_STATE_MAX - 1], (void *)temp, 
        (unsigned int)(LED_CONFIG_MAX_LTE * sizeof(LED_CONTROL_NV_STRU)));

    return do_led_tled_test_case(LED_LIGHT_STATE_MAX - 1);
}

/************************************************************************
 * Name         : led_tled_test_case_012
 * Function     : ����A����ɫ�ƺ�Ƶ�������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_012(void)
{
    LED_CONTROL_NV_STRU temp[LED_CONFIG_MAX_LTE] = LED_RED_LIGHTING_SIGNAL;

    memcpy((void *)g_nv_led.g_led_state_str_om[LED_LIGHT_STATE_MAX - 1], (void *)temp, 
        (unsigned int)(LED_CONFIG_MAX_LTE * sizeof(LED_CONTROL_NV_STRU)));

    return do_led_tled_test_case(LED_LIGHT_STATE_MAX - 1);
}

/************************************************************************
 * Name         : led_tled_test_case_013
 * Function     : ����A����ɫ�ƺ�Ƴ�������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_013(void)
{
    LED_CONTROL_NV_STRU temp[LED_CONFIG_MAX_LTE] = LED_RED_LIGHTING_ALWAYS;

    memcpy((void *)g_nv_led.g_led_state_str_om[LED_LIGHT_STATE_MAX - 1], (void *)temp, 
        (unsigned int)(LED_CONFIG_MAX_LTE * sizeof(LED_CONTROL_NV_STRU)));

    return do_led_tled_test_case(LED_LIGHT_STATE_MAX - 1);
}

/************************************************************************
 * Name         : led_tled_test_case_014
 * Function     : ����A����ɫ�Ƴ�������
 * Arguments
 *      input   : new_state - new status
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : 
 ************************************************************************/
int led_tled_test_case_014(void)
{
    return do_led_tled_test_case(LED_LIGHT_SHUTDOWN);
}

/************************************************************************
 * Name         : led_tled_test_case_015
 * Function     : ����NV��ȡʧ��ʱ����ɫ���ܷ���Ĭ�����Ʒ�����˸
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 *                else - fail
 * Decription   : ��Ҫ����nv��ʧ�ܵĳ���
 ************************************************************************/
int led_tled_test_case_015(void)
{
    return do_led_tled_test_case(LED_LIGHT_SYSTEM_STARTUP);
}

/************************************************************************
 * Name         : led_tled_test_case_017
 * Function     : ������ɫ�Ʋ��ֺ�Ƶ�������
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int led_tled_test_case_017(void)
{
    RED_ON;
    return LED_OK;
}

/************************************************************************
 * Name         : led_tled_test_case_018
 * Function     : ������ɫ�Ʋ��ֺ��Ϩ����
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int led_tled_test_case_018(void)
{
    RED_OFF;
    return LED_OK;
}

/************************************************************************
 * Name         : led_tled_test_case_019
 * Function     : ������ɫ�Ʋ����̵Ƶ�������
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int led_tled_test_case_019(void)
{
    GREEN_ON;
    return LED_OK;
}

/************************************************************************
 * Name         : led_tled_test_case_020
 * Function     : ������ɫ�Ʋ����̵�Ϩ����
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int led_tled_test_case_020(void)
{
    GREEN_OFF;
    return LED_OK;
}

/************************************************************************
 * Name         : led_tled_test_case_021
 * Function     : ������ɫ�Ʋ������Ƶ�������
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int led_tled_test_case_021(void)
{
    BLUE_ON;
    return LED_OK;
}

/************************************************************************
 * Name         : led_tled_test_case_022
 * Function     : ������ɫ�Ʋ�������Ϩ����
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int led_tled_test_case_022(void)
{
    BLUE_OFF;
    return LED_OK;
}

/*
 * led_tled_test_case_023��Ϊ4��С�������ɸ�����ɫ�л������г���
 */

/************************************************************************
 * Name         : led_tled_test_case_023_1
 * Function     : ������ɫ�Ʋ�����ɫ�仯���� - �Ӱ�ɫ����
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int led_tled_test_case_023_1(void)
{
    /* power off */
    RED_OFF;
    GREEN_OFF;
    BLUE_OFF;
    led_threecolor_state_switch(LED_WHITE, LED_NULL);
    return LED_OK;
}

/************************************************************************
 * Name         : led_tled_test_case_023_2
 * Function     : ������ɫ�Ʋ�����ɫ�仯���� - ���𵽰�ɫ
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int led_tled_test_case_023_2(void)
{
    /* power on */
    RED_ON;
    GREEN_ON;
    BLUE_ON;
    led_threecolor_state_switch(LED_NULL, LED_WHITE);
    return LED_OK;
}

/************************************************************************
 * Name         : led_tled_test_case_023_3
 * Function     : ������ɫ�Ʋ�����ɫ�仯���� - ������
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int led_tled_test_case_023_3(void)
{
    /* power off */
    RED_OFF;
    GREEN_OFF;
    BLUE_OFF;
    led_threecolor_state_switch(LED_NULL, LED_NULL);
    return LED_OK;
}

/************************************************************************
 * Name         : led_tled_test_case_023_4
 * Function     : ������ɫ�Ʋ�����ɫ�仯���� - �Ӱ�ɫ����ɫ
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int led_tled_test_case_023_4(void)
{
    /* power on */
    RED_ON;
    GREEN_ON;
    BLUE_ON;
    led_threecolor_state_switch(LED_WHITE, LED_WHITE);
    return LED_OK;
}
#else /* __VXWORKS__ */

#include <drv_leds.h>
#include <bsp_om.h>

extern pFUNCPTR p_func_tled_state_get;
extern unsigned char g_new_work_state;

pFUNCPTR g_led_test_state = NULL;


/* ���ϲ�ע��Ĺ��Ӻ�����Ӱ�����Ч��������֮ǰ��ʹ���Ӻ�����Ч����������ɺ��ٻָ���
 * ���Բ���֮ǰҪ�ȵ���led_save_for_test()����������ɺ����led_resume_for_test()
 */
void led_save_for_test(void)
{
    if(g_led_test_state)
    {
        return;
    }

    g_led_test_state = p_func_tled_state_get;
    p_func_tled_state_get = NULL;
    return;
}

void led_resume_for_test(void)
{
    if(p_func_tled_state_get)
    {
        return;
    }
    
    p_func_tled_state_get = g_led_test_state;
    g_led_test_state = NULL;
    return;
}

/************************************************************************
 * Name         : do_led_tled_test_case
 * Function     : 
 * Arguments
 *      input   : @state - ����״̬
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int do_led_tled_test_case(unsigned long state)
{
    if(drv_led_flash(state))
    {
        return LED_ERROR;
    }

    return LED_OK;
}

/************************************************************************
 * Name         : led_tled_test_case_016
 * Function     : ������ɫ�Ʋ�����ɫ�仯���� - �Ӱ�ɫ����ɫ
 * Arguments
 *      input   : @state - ����״̬
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��Ҫ������Ա�۲�Ƶ�״̬���ж��Ƿ����ok
 ************************************************************************/
int led_tled_test_case_016(unsigned long state)
{
    led_save_for_test();
    
    if(state < LED_LIGHT_STATE_MAX)
    {
        return do_led_tled_test_case(state);
    }
    else
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"ERROR: invalid state %d\n", state);
        return LED_ERROR;
    }            
}

/************************************************************************
 * Name         : led_tled_test_case_024
 * Function     : ������ɫ�Ʋ�����ɫ�仯���� - �Ӱ�ɫ����ɫ
 * Arguments
 *      input   : @state - ����״̬
 *      output  : null
 *
 * Return       : 0 - ok
 * Decription   : ��ɫ�Ƶ�״̬Ӧ�ò������仯
 ************************************************************************/
int led_tled_test_case_024(void)
{
    led_save_for_test();
    return do_led_tled_test_case((unsigned long)g_new_work_state);
}


#endif
#ifdef __cplusplus
}
#endif
