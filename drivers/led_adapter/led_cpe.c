/******************************************************************************

  Copyright (C), 2001-2013, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : kerneldev.h
  Version       : 
  Created       :
  Description   : 
  Function List :

  History        :
  1.Date         : 2013/11/26
    Author       : ����00249966
    Modification : Created

******************************************************************************/

#include <linux/init.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <asm/uaccess.h>

#include "drv_comm.h"
#include "led_comm.h"
#include "led_cpe.h"
#include <bsp_softtimer.h>

#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************
 ȫ�ֱ�������

*****************************************************************************/
/*����LED ����ID */
struct task_struct *g_ledTaskID = NULL;
/*����LED ��˸��������˸�¼����ź���*/
struct semaphore g_ledAllBlinkTaskSemId;
/*����LED �¼�*/
int g_event_recv = 0;
/*��¼9 ���ƶ�Ӧ�Ķ�ʱ��*/
struct softtimer_list g_kerdevTimer ;
/*��¼9 ���ƶ�Ӧ��GPIO λ*/
unsigned int LED_GPIO[LED_ID_MAX] =
    {GPIO_INVALID,GPIO_INVALID,GPIO_INVALID,GPIO_INVALID,
    GPIO_3_0,GPIO_3_1,GPIO_3_2,GPIO_2_31,
    GPIO_INVALID};
/*��¼9 ��LED �Ƶĵ�ǰʱ����״̬: ��������*/
/* ״̬������g_current_kerdev_state[] ��Ӧ*/
unsigned int g_led_current_state[LED_ID_MAX] = 
    {LED_OFF, LED_OFF, LED_OFF, LED_OFF,
    LED_OFF, LED_OFF, LED_OFF, LED_OFF,
    LED_OFF};
/* LED �Ƴ�ʼ״̬������ ��¼8 ���Ƶĵ�ǰ״̬*/
LED_IOCTL_ARG g_current_kerdev_state[LED_ID_MAX] = 
{ 
    {
        LED_STATE_OFF,
        LED_ID_WIFI,
        LED_COLOR_GREEN,
        LED_COLOR_GREEN,
        KERDEV_BLINK_TIME,
        KERDEV_BLINK_TIME,
        LED_CURRENT_LEVEL3,
        LED_MODE_NORMAL
    },
    {
        LED_STATE_OFF,
        LED_ID_BAT,
        LED_COLOR_GREEN,
        LED_COLOR_GREEN,
        KERDEV_BLINK_TIME,
        KERDEV_BLINK_TIME,
        LED_CURRENT_LEVEL3,
        LED_MODE_NORMAL
    },
    {
        LED_STATE_OFF,
        LED_ID_SMS,
        LED_COLOR_GREEN,
        LED_COLOR_GREEN,
        KERDEV_BLINK_TIME,
        KERDEV_BLINK_TIME,
        LED_CURRENT_LEVEL3,
        LED_MODE_NORMAL
    },
    {
        LED_STATE_OFF,
        LED_ID_CIRCLE,
        LED_COLOR_GREEN,
        LED_COLOR_GREEN,
        KERDEV_BLINK_TIME,
        KERDEV_BLINK_TIME,
        LED_CURRENT_LEVEL3,
        LED_MODE_NORMAL
    },
    {
        LED_STATE_OFF,
        LED_ID_SIGNAL1,
        LED_COLOR_GREEN,
        LED_COLOR_GREEN,
        KERDEV_BLINK_TIME,
        KERDEV_BLINK_TIME,
        LED_CURRENT_LEVEL3,
        LED_MODE_NORMAL
    },
    {
        LED_STATE_OFF,
        LED_ID_SIGNAL2,
        LED_COLOR_GREEN,
        LED_COLOR_GREEN,
        KERDEV_BLINK_TIME,
        KERDEV_BLINK_TIME,
        LED_CURRENT_LEVEL3,
        LED_MODE_NORMAL
    },
    {
        LED_STATE_OFF,
        LED_ID_SIGNAL3,
        LED_COLOR_GREEN,
        LED_COLOR_GREEN,
        KERDEV_BLINK_TIME_1500,
        KERDEV_BLINK_TIME_3000,
        LED_CURRENT_LEVEL3,
        LED_MODE_NORMAL
    },
    {
        LED_STATE_OFF,
        LED_ID_SLIC,
        LED_COLOR_YELLOW,
        LED_COLOR_YELLOW,
        KERDEV_BLINK_TIME,
        KERDEV_BLINK_TIME,
        LED_CURRENT_LEVEL3,
        LED_MODE_NORMAL
    },
    {
        LED_STATE_OFF,
        LED_ID_MODE,
        LED_COLOR_RED,
        LED_COLOR_RED,
        KERDEV_BLINK_TIME,
        KERDEV_BLINK_TIME,
        LED_CURRENT_LEVEL3,
        LED_MODE_NORMAL
    }
};


/****************************************************************************
 �ڲ�����ԭ��˵��

*****************************************************************************/


/****************************************************************************
 �ⲿ����ԭ��˵��

*****************************************************************************/
extern int kernelDeviceIoctl(struct file *file, unsigned int cmd, unsigned long arg);


/****************************************************************************
 ��������

*****************************************************************************/

int kernelDeviceStateShow(LED_IOCTL_ARG stCtrlParms)
{
    int ret = BSP_ERROR;
    
    /*����LED �Ƶ�״̬��*/
    memcpy((LED_IOCTL_ARG *)&g_current_kerdev_state[stCtrlParms.led_id],
        &stCtrlParms,sizeof(LED_IOCTL_ARG));  
    
    switch (stCtrlParms.led_dev_state)
    {
        case LED_STATE_ON:
        {
            printk(KERN_ERR "[LED] kernelDeviceStateShow: LED_STATE_ON\n");
             
            g_led_current_state[stCtrlParms.led_id] = LED_ON;
            ret = ledStateWrite(stCtrlParms, LED_ON);
            
            break;
        }
        case LED_STATE_OFF:
        {
            printk(KERN_ERR "[LED] kernelDeviceStateShow: LED_STATE_OFF\n");
            g_led_current_state[stCtrlParms.led_id] = LED_OFF;
            ret = ledStateWrite(stCtrlParms, LED_OFF);
            
            break;
        }
        case LED_STATE_BLINK:
        {

            printk(KERN_ERR "[LED] kernelDeviceStateShow: LED_STATE_BLINK\n");
            ret = ledStateBlink(stCtrlParms);
            
            break;
        }
        default:
        {
            printk(KERN_ERR "[LED] kernelDeviceStateShow: LED state ERROR!\n");
            break;
        }
    }

    return ret;
}




int kernelDeviceIoctl_Test(int index)
{
    int ret = BSP_ERROR;
    /* ʵ��1234 ΪIOCTL ���β��ļ������������ã����ȡֵ */
    int pf = NULL;
    LED_IOCTL_ARG stCtrlParms;
    memset((void *)&stCtrlParms,0,sizeof(LED_IOCTL_ARG));

    stCtrlParms.led_id = LED_ID_MODE;  /* ������8 ��LED ��*/
    stCtrlParms.led_dev_state = LED_STATE_BLINK; /* LED ��״̬*/
    stCtrlParms.led_color = LED_COLOR_YELLOW;
    stCtrlParms.second_led_color = LED_COLOR_RED;
    stCtrlParms.duration = KERDEV_BLINK_TIME_1500;
    stCtrlParms.second_duration = KERDEV_BLINK_TIME_3000;
    stCtrlParms.led_current = LED_CURRENT_LEVEL3;
    stCtrlParms.sleep_mode = LED_MODE_NORMAL;

    switch (index)
    {
        /* LED_DEV_READ ����: ��ȡLED �Ƶ�ǰ״̬*/
        case 1:
            ret = kernelDeviceIoctl(pf, LED_IOCTL_SET, &stCtrlParms);
            break;
        /* LED_DEV_WRITE ����: ʹLED ����*/
        case 2:
            stCtrlParms.led_dev_state = LED_STATE_ON;
            ret = kernelDeviceIoctl(pf, LED_IOCTL_SET, &stCtrlParms);
            break;
        /* LED_DEV_BLINK ����: ʹLED ����˸*/
        case 3:
            stCtrlParms.led_dev_state = LED_STATE_BLINK;
            ret = kernelDeviceIoctl(pf, LED_IOCTL_SET, &stCtrlParms);
            break;
        default:
            printk(KERN_ERR "[LED] kernelDeviceIoctl_Test: CMD ERROR!\n");
            break;
    }

    if (BSP_OK != ret)
    {
        printk(KERN_ERR "[LED] kernelDeviceIoctl_Test: FAIL!\n");
        return BSP_ERROR;
    }

    printk(KERN_INFO "[LED] kernelDeviceIoctl_Test: SUCCESS!\n");
    return BSP_OK;
}




int eventSend(int event_id)
{    
    unsigned long flags = 0;
    
    spin_lock_irqsave(&led_event_lock, flags);
    g_event_recv = event_id;
    spin_unlock_irqrestore(&led_event_lock, flags);

    /*�ͷ��ź�����ֹͣ��˸�������*/
    up(&g_ledAllBlinkTaskSemId);

    return BSP_OK;
}


int eventReceive(int *get_event_id)
{    
    /*��ȡ�ź���������˸�������*/
    down(&g_ledAllBlinkTaskSemId);

    unsigned long flags = 0;
    spin_lock_irqsave(&led_event_lock, flags);
    /*���յ��¼��Ժ�ȡ���¼���¼*/
    *get_event_id = g_event_recv;
    g_event_recv = BSP_ERROR;
    spin_unlock_irqrestore(&led_event_lock, flags);

    return BSP_OK;
}


static int kernelDeviceBlinkTask(void)
{
    printk(KERN_INFO "[LED] kernelDeviceBlinkTask() IN\n");

    int eventRec = BSP_ERROR;
    int led_id = GPIO_INVALID;
    int blinkTime = 0;
    int currentState = LED_OFF;    /*����Ƴ�ʼ״̬Ϊ�𣬿��ܽ�����ĵط�*/
    int nextState = LED_STATE_MAX;

    for ( ; ; )
    {  
        /*���յ���¼�eventReceive*/
        eventReceive(&eventRec);
        
        if (BSP_ERROR == eventRec)
        {
            continue;
        }

        printk(KERN_INFO "[LED] kernelDeviceBlinkTask: eventRec = %d\n", eventRec);

        if ((LED_TIMER_EVENT == eventRec) || (APP_LED_SET == eventRec))
        {
            printk(KERN_INFO "[LED] kernelDeviceBlinkTask: 1\n");
            /*�������һ��led �Ʒ��͵��¼�*/
            for (led_id = LED_ID_SIGNAL1; led_id <= LED_ID_MODE; led_id++)
            {
                printk(KERN_INFO "[LED] kernelDeviceBlinkTask: 2\n");
                printk(KERN_INFO "[LED] kernelDeviceBlinkTask: global led_state = %d\n", 
                    led_id,g_current_kerdev_state[led_id].led_dev_state);
                
                if (LED_STATE_BLINK == g_current_kerdev_state[led_id].led_dev_state)
                {  
                    /*��ȫ�ֱ����ж�ȡLED �Ƶ�ǰʱ���״̬*/
                    if (BSP_OK != ledStateRead(g_current_kerdev_state[led_id], &currentState))  /*����д*/
                    {
                        printk(KERN_ERR "[LED] kernel_led_read FAIL!\n");
                    }
                    printk(KERN_INFO "[LED] kernelDeviceBlinkTask: currentState = %d\n", 
                        currentState);

                    /* LED ��״̬ת���ٲ�*/
                    if (BSP_OK != kernelDeviceStateSwitch(led_id, currentState,
                        &nextState, &blinkTime))
                    {
                        printk(KERN_ERR "[LED] kernelDeviceStateSwitch FAIL!\n");
                    }

                     /*��¼��ǰʱ���LED ��״̬*/
                    g_led_current_state[led_id] = nextState;
                    
                    /*д��ת��״̬��led ��GPIO*/
                    if (BSP_OK != ledStateWrite(g_current_kerdev_state[led_id], nextState))
                    {
                        printk(KERN_ERR "[LED] kernel_led_write fail!\n");
                    }
                    printk(KERN_INFO "[LED] kernelDeviceBlinkTask: nextState=%d\n", 
                        nextState);

                    /*��ʼ����ָ��LED �ƵĶ�ʱ�������߸��¶�ʱ��ʱ��*/
                    if (APP_LED_SET == eventRec)
                    {
                        /*��һ�δ�����������˸��ʱ��*/                      
                        //struct softtimer_info kerdevTime;
                        g_kerdevTimer.func = kerneldevBlinkCallbackFunc;
                        g_kerdevTimer.para = LED_TIMER_EVENT;
                        g_kerdevTimer.timeout = blinkTime; /*��˸��ʱ��*/
                        g_kerdevTimer.wake_type = SOFTTIMER_WAKE;
                        KERNELDEV_TIMER_CREAT(&g_kerdevTimer);

                        printk(KERN_INFO "[LED] g_kerdevTimer ID = %d\n", led_id,
                            g_kerdevTimer.timer_id);
                    }
                    else if (LED_TIMER_EVENT == eventRec)
                    {
                        /*������ʱ��������˸ʱ�����*/
                        KERNELDEV_TIMER_MODIFY(&g_kerdevTimer, blinkTime);
                        printk(KERN_INFO "[LED] bsp_softtimer_modify EXECUTE!\n");
                    }
                    else
                    {
                        //do nothing    
                    }
                    KERNELDEV_TIMER_ADD(&g_kerdevTimer);
                    printk(KERN_INFO "[LED] bsp_softtimer_add EXECUTE!\n");                 
                }
                else
                {
                     //do nothing
                }
            }     
        }
        else
        {
            //do nothing
        }
    }
}


static int kernelDeviceStateSwitch(int led_id, int currentState, int *nextState,
    int *blinkTime)
{
    /*�жϵ������ߵ���*/
    if (LED_ON == currentState)
    {
        *nextState = LED_OFF;
        *blinkTime = g_current_kerdev_state[led_id].second_duration;
        printk("[LED] led state is changed from ON to OFF!\n");
    }
    else if (LED_OFF == currentState)
    {
        *nextState = LED_ON;
        *blinkTime = g_current_kerdev_state[led_id].duration;
        printk( "[LED] led state is changed from OFF to ON!\n");
    }
    else
    {
        printk(KERN_ERR "[LED]led state ERROR!\n");
        return BSP_ERROR;
    }    
    
    return BSP_OK;
}



static int kerneldevBlinkCallbackFunc(int event_id)
{
    if (BSP_OK != eventSend(event_id))
    {
        printk(KERN_ERR "[LED] kerneldevBlinkCallbackFunc: Send event FAIL!\n");
        return BSP_ERROR;
    }
    return BSP_OK;
}


int ledStateRead(LED_IOCTL_ARG stCtrlParms, int *current_state)
{
    printk(KERN_INFO "ledStateRead IN\n");
    
    if((LED_ID_SIGNAL1 > stCtrlParms.led_id) || (LED_ID_MODE < stCtrlParms.led_id))
    {
        printk(KERN_ERR "Led type error,LED ID=%d\n", stCtrlParms.led_id);
        return BSP_ERROR;
    }
    
    if (current_state == NULL)
    {
        printk(KERN_ERR "[LED] current_state is NULL!\n");
        return BSP_ERROR;
    }

    *current_state = g_led_current_state[stCtrlParms.led_id];
    
    return BSP_OK;
}


int kernel_led_read(LED_ID led_id, int *current_state)
{
    if((LED_ID_SIGNAL1 > led_id) || (LED_ID_MODE < led_id))
    {
        printk(KERN_ERR "[LED] kernel_led_read: Led ID error,LED ID=%d\n",led_id);
        return BSP_ERROR;
    }
    
    if (current_state == NULL)
    {
        printk(KERN_ERR "[LED] kernel_led_read: current_state is NULL!\n");
        return BSP_ERROR;
    }

    if (BSP_OK != ledStateRead(g_current_kerdev_state[led_id], current_state))
    {
        printk(KERN_ERR "[LED] kernel_led_read:FAIL!\n");
        return BSP_ERROR;
    }

    return BSP_OK;
}


int ledStateWrite(LED_IOCTL_ARG stCtrlParms, int next_state)
{
    printk(KERN_INFO "[LED] ledStateWrite: IN,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
        stCtrlParms.led_dev_state,stCtrlParms.led_id,stCtrlParms.led_color,
        stCtrlParms.second_led_color,stCtrlParms.duration,stCtrlParms.second_duration,
        stCtrlParms.led_current,stCtrlParms.sleep_mode,next_state);
    
    if((LED_ID_SIGNAL1 > stCtrlParms.led_id) || (LED_ID_MODE < stCtrlParms.led_id))
    {
        printk(KERN_ERR "[LED] Led type error,LED ID=%d\n",stCtrlParms.led_id);
        return BSP_ERROR;
    }

    if ((next_state != LED_ON) && (next_state != LED_OFF))
    {
        printk(KERN_ERR "[LED] Led state error,LED state=%d\n",next_state);
        return BSP_ERROR;
    }

    /*��ͨ�Ƶ�����������*/
    if (LED_ID_MODE != stCtrlParms.led_id)
    {
        if (GPIO_INVALID == LED_GPIO[stCtrlParms.led_id])
        {
            printk(KERN_ERR "[LED] Led GPIO ERROR\r\n");
            return BSP_ERROR;
        }

        gpio_direction_output(LED_GPIO[stCtrlParms.led_id],next_state);
    }
    /*ģʽ�Ƶ�����������: ��Ҫ��ɫ*/
    else
    {
        switch (stCtrlParms.led_color)
        {
                case LED_COLOR_RED:
                {
                    gpio_direction_output(GPIO_MODE_R_LED, next_state);
                    gpio_direction_output(GPIO_MODE_G_LED, LED_OFF);
                    gpio_direction_output(GPIO_MODE_B_LED, LED_OFF);
                    break;
                }
                case LED_COLOR_GREEN:
                {
                    gpio_direction_output(GPIO_MODE_G_LED, next_state);
                    gpio_direction_output(GPIO_MODE_R_LED, LED_OFF);
                    gpio_direction_output(GPIO_MODE_B_LED, LED_OFF);
                    break;
                }
                case LED_COLOR_YELLOW:
                {
                    gpio_direction_output(GPIO_MODE_R_LED, next_state);
                    gpio_direction_output(GPIO_MODE_G_LED, next_state);
                    gpio_direction_output(GPIO_MODE_B_LED, LED_OFF);
                    break;
                }
                case LED_COLOR_BLUE:
                {
                    gpio_direction_output(GPIO_MODE_B_LED, next_state);
                    gpio_direction_output(GPIO_MODE_R_LED, LED_OFF);
                    gpio_direction_output(GPIO_MODE_G_LED, LED_OFF);
                    break;
                }
                case LED_COLOR_WHITE:
                {
                    gpio_direction_output(GPIO_MODE_R_LED, next_state);
                    gpio_direction_output(GPIO_MODE_G_LED, next_state);
                    gpio_direction_output(GPIO_MODE_B_LED, next_state);
                    break;
                }
                case LED_COLOR_CYAN:
                {
                    gpio_direction_output(GPIO_MODE_G_LED, next_state);
                    gpio_direction_output(GPIO_MODE_B_LED, next_state);
                    gpio_direction_output(GPIO_MODE_R_LED, LED_OFF);
                    break;
                }
                case LED_COLOR_PURPLE:
                {
                    gpio_direction_output(GPIO_MODE_R_LED, next_state);
                    gpio_direction_output(GPIO_MODE_B_LED, next_state);
                    gpio_direction_output(GPIO_MODE_G_LED, LED_OFF);
                    break;
                }
                default:
                {
                    printk(KERN_ERR "[LED] ledStateWrite: LED color ERROR!\n");
                    return BSP_ERROR;
                }
        }
    }
    
    printk(KERN_INFO "[LED] ledStateWrite: OUT, LED_GPIO[%d] = %d, next_state= %d\n",
        stCtrlParms.led_id,LED_GPIO[stCtrlParms.led_id], next_state);

    return BSP_OK;
}


int kernel_led_write(LED_IOCTL_ARG stCtrlParms, int next_state)
{
    if((LED_ID_SIGNAL1 > stCtrlParms.led_id) || (LED_ID_MODE < stCtrlParms.led_id))
    {
        printk(KERN_ERR "[LED] kernel_led_write: Led type error,LED ID=%d\n",stCtrlParms.led_id);
        return BSP_ERROR;
    }

    if ((next_state != LED_ON) && (next_state != LED_OFF))
    {
        printk(KERN_ERR "[LED] kernel_led_write: Led state error,LED state=%d\n",
            next_state);
        return BSP_ERROR;
    }

    /*����LED ��ȫ�ֱ���״̬*/
    memcpy((LED_IOCTL_ARG *)&g_current_kerdev_state[stCtrlParms.led_id],
        &stCtrlParms,sizeof(LED_IOCTL_ARG));   
    
    g_led_current_state[stCtrlParms.led_id] = next_state;
    
    if (BSP_OK != ledStateWrite(g_current_kerdev_state[stCtrlParms.led_id], next_state))
    {
        printk(KERN_ERR "[LED] kernel_led_write: ERROR, LED ID=%d, LED state=%d\n",
            stCtrlParms.led_id, next_state);
        return BSP_ERROR;
    }

    return BSP_OK;
}


int ledStateBlink(LED_IOCTL_ARG stCtrlParms)
{
    printk(KERN_INFO "ledStateBlink IN\n");

    int event_id = APP_LED_SET;
    
    if((LED_ID_SIGNAL1 > stCtrlParms.led_id) || (LED_ID_MODE < stCtrlParms.led_id))
    {
        printk(KERN_ERR "[LED] ledStateBlink: Led type error,LED ID=%d\n",stCtrlParms.led_id);
        return BSP_ERROR;
    }

    /*�����¼�����������*/
    if (BSP_OK != eventSend(event_id)) /*ʱ�䷢�ͺ������޸�*/
    {
        printk(KERN_ERR "[LED] ledStateBlink: Send event FAIL!\n");
        return BSP_ERROR;
    }

    return BSP_OK;
}



int kernel_led_blink(LED_IOCTL_ARG stCtrlParms)
{
    if((LED_ID_SIGNAL1 > stCtrlParms.led_id) || (LED_ID_MODE < stCtrlParms.led_id))
    {
        printk(KERN_ERR "[LED] kernel_led_blink: Led type error,LED ID=%d\n",stCtrlParms.led_id);
        return BSP_ERROR;
    }

    if ((stCtrlParms.duration < 0) || (stCtrlParms.second_duration < 0))
    {
        printk(KERN_ERR "[LED] kernel_led_blink: Timeout ERROR\n");
        return BSP_ERROR;
    }

    /*����LED ��ȫ�ֱ���״̬*/
    memcpy((LED_IOCTL_ARG *)&g_current_kerdev_state[stCtrlParms.led_id],
        &stCtrlParms,sizeof(LED_IOCTL_ARG));      


    if (BSP_OK != ledStateBlink(g_current_kerdev_state[stCtrlParms.led_id]))
    {
        printk(KERN_ERR "[LED] kernel_led_blink: ERROR\n");
        return BSP_ERROR;
    }

    return BSP_OK;
}


int resource_release(void)
{
    int ret = BSP_ERROR;
    ret = kthread_stop(g_ledTaskID);
    KERNELDEV_TIMER_FREE(&g_kerdevTimer);

    return ret;
}


int resource_get(void)
{   
    printk(KERN_ERR "[LED] %s: IN\r\n", __func__);
    int i = 0;
    int j = 0;
    int ret = BSP_OK;

    /*LED GPIO ����(��ģʽ��)*/
    for (i = LED_ID_SIGNAL1; i <= LED_ID_SLIC; i++)
    {
        if(gpio_request(LED_GPIO[i], ""))
        {
            printk(KERN_ERR "[LED] %s: request gpio%d FAIL!\n", __func__, LED_GPIO[i]);
            ret = BSP_ERROR;
        }
    }

    /*����ģʽ�̵�GPIO */
    if (gpio_request(GPIO_MODE_G_LED,""))
    {
        printk(KERN_ERR "[LED] %s: request gpio%d FAIL!\n", __func__, GPIO_MODE_G_LED);
        ret = BSP_ERROR;
    }

    /*����ģʽ���GPIO */
    if (gpio_request(GPIO_MODE_R_LED,""))
    {
        printk(KERN_ERR "[LED] %s: request gpio%d FAIL!\n", __func__,GPIO_MODE_R_LED);
        ret = BSP_ERROR;
    }

    /*����ģʽ����GPIO */
    if (gpio_request(GPIO_MODE_B_LED,""))
    {
        printk(KERN_ERR "[LED] resource_get: request gpio%d FAIL!\n", GPIO_MODE_B_LED);
        ret = BSP_ERROR;
    }


    /* ����ʵ�ʵ�������ʼ��LED ��״̬*/ 
    for (j = LED_ID_SIGNAL1; j < LED_ID_MAX; j++)
    {
        if (BSP_OK != kernel_led_write(g_current_kerdev_state[j],LED_OFF))
        {
            ret = BSP_ERROR;
        }
    }

    /*��ʼ��ʹ����˸���������ź���*/
    sema_init(&g_ledAllBlinkTaskSemId, 0);
    g_ledTaskID = kthread_run(kernelDeviceBlinkTask, NULL, LED_BLINK_TASK_NAME);
    
    printk(KERN_ERR "[LED] %s: OUT!\r\n", __func__);
    return ret;
}


#ifdef __cplusplus
}
#endif

