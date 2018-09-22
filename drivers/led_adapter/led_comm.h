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

#ifndef _KERNELDEV_H
#define _KERNELDEV_H

#ifdef __cplusplus
extern "C" {
#endif


#define MEM_IOC_MAGIC    'x' //��������
#define MEMDEV_IOC_MAXNR 2
typedef enum _LED_IOCTL_CMD
{
    LED_IOCTL_SET      = _IO(MEM_IOC_MAGIC, 0),  /*����LED�Ƶ�״̬*/
    LED_IOCTL_GET      = _IO(MEM_IOC_MAGIC, 1),  /*��ȡLED�Ƶ�״̬*/
    LED_IOCTL_CMD_MAX = _IO(MEM_IOC_MAGIC, 2)   /*Ŀǰ֧�ֵ��������*/
}LED_IOCTL_CMD;

typedef enum _LED_ID
{
    LED_ID_FIRST = 0,
    LED_ID_WIFI = LED_ID_FIRST,  /* WIFI�� */
    LED_ID_BAT,                  /* ��ص� */
    LED_ID_SMS,                  /* ���ŵ� */
    LED_ID_CIRCLE,               /* װ�ε� */
    LED_ID_SIGNAL1,              /* �źŵ�1 */
    LED_ID_SIGNAL2,              /* �źŵ�2 */
    LED_ID_SIGNAL3,              /* �źŵ�3 */
    LED_ID_SLIC,                 /* ����ָʾ�� */
    LED_ID_MODE,                 /* ������ʽָʾ�� */
    LED_ID_MAX
} LED_ID;

typedef enum _LED_STATE
{
    LED_STATE_ON = 0,
    LED_STATE_OFF,
    LED_STATE_BLINK,
    LED_STATE_COLOR_BLINK,
    LED_STATE_ALL_BLINK,
    LED_STATE_MAX,
}LED_DEV_STATE;

typedef enum _LED_COLOR
{
    LED_COLOR_RED = 0,
    LED_COLOR_GREEN,
    LED_COLOR_YELLOW,
    LED_COLOR_BLUE,
    LED_COLOR_WHITE,
    LED_COLOR_CYAN,
    LED_COLOR_PURPLE,
    LED_COLOR_MAX
}LED_COLOR;

/*ָʾ�Ƶ�����*/
typedef enum
{
    LED_CURRENT_LEVEL0 = 0,
    LED_CURRENT_LEVEL1,
    LED_CURRENT_LEVEL2,
    LED_CURRENT_LEVEL3,
    LED_CURRENT_LEVEL4,
    LED_CURRENT_LEVELMAX
}LED_CURRENT;

/*LED��ģʽ */
typedef enum
{
    LED_MODE_NORMAL = 0,
    LED_MODE_SLEEP,
    LED_MODE_MAX
}LED_MODE;

typedef struct
{
    LED_DEV_STATE led_dev_state;
    LED_ID led_id;
    LED_COLOR led_color;
    LED_COLOR second_led_color;
    unsigned int duration;
    unsigned int second_duration;
    LED_CURRENT led_current;
    LED_MODE sleep_mode;
}LED_IOCTL_ARG;




#ifdef __cplusplus
}
#endif

#endif /* _KERNELDEV_H */