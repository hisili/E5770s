/******************************************************************************

  Copyright (C), 2001-2013, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : kerneldev.c
  Version       : Initial Draft
  Created       :
  Description   : kerneldev Init
  Function List :

  History        :
  1.Date         : 2014/01/15
    Author       : ����00249966
    Modification : Created function

******************************************************************************/


#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>

#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/ioctl.h>

#include "led_comm.h"
#include <bsp_softtimer.h>
//#include "led_comm.h"

#ifdef __cplusplus
extern "C" {
#endif


/****************************************************************************
������

*****************************************************************************/
#define  LED_BLINK_TASK_NAME    "tLedAllBlink"

/* LED ���¼�*/
#define APP_LED_SET   (1)
#define LED_TIMER_EVENT (2)

/* LED �Ƶ�ǰ״̬: 1 ������0 ��*/
#define LED_ON   (1)
#define LED_OFF (0)

/* LED �ƶ�ʱ����ʱʱ��*/
#define KERDEV_BLINK_TIME (3000)
#define KERDEV_BLINK_TIME_1500 (1500)
#define KERDEV_BLINK_TIME_3000 (3000)

/*��ɫ�ƶ�Ӧ��GPIO */
#define GPIO_MODE_R_LED GPIO_1_23
#define GPIO_MODE_G_LED GPIO_1_24
#define GPIO_MODE_B_LED GPIO_1_22

/*δ�����led��ʹ�õ���ЧGPIO*/
#define GPIO_INVALID (-1)

#define KERNELDEV_TIMER_CREAT(softtimer_info) \
    bsp_softtimer_create(softtimer_info)

#define KERNELDEV_TIMER_ADD(softtimer_info_list) \
    bsp_softtimer_add(softtimer_info_list)

#define KERNELDEV_TIMER_DELETE(softtimer_info_list) \
    bsp_softtimer_delete(softtimer_info_list)

#define KERNELDEV_TIMER_MODIFY(softtimer_info_list, timeout) \
    bsp_softtimer_modify(softtimer_info_list, timeout)

#define KERNELDEV_TIMER_FREE(softtimer_info_list) \
    bsp_softtimer_free(softtimer_info_list)




/****************************************************************************
 �ⲿ����ԭ��˵��

*****************************************************************************/
int kernel_led_write(LED_IOCTL_ARG stCtrlParms, int next_state);
int kernel_led_read(LED_ID led_id, int *current_state);   
int kernel_led_blink(LED_IOCTL_ARG stCtrlParms);

int resource_release(void);
int resource_get(void);

int ledStateRead(LED_IOCTL_ARG stCtrlParms, int *current_state);
int ledStateWrite(LED_IOCTL_ARG stCtrlParms, int next_state);
int ledStateBlink(LED_IOCTL_ARG stCtrlParms);

static int kerneldevBlinkCallbackFunc(int event_id);
static DEFINE_SPINLOCK(led_event_lock);

int eventSend(int event_id);
int eventReceive(int *get_event_id);

/*LED ��״̬ת��*/
static int kernelDeviceStateSwitch(int led_id, int currentState,
    int *nextState, int *blinkTime);
/*����LED ��״̬���е��*/
int kernelDeviceStateShow(LED_IOCTL_ARG stCtrlParms);
int kernelDeviceIoctl_Test(int index); /*IOCTRL���Ժ���*/

#ifdef __cplusplus
}
#endif

