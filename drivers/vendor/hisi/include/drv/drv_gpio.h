

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "drv_comm.h"


/*************************GPIO START**********************************/

typedef unsigned int GPIO_OPRT_ENUM_UINT32;
#define DRV_NOT_START_UMTS (0x55aa5a5a)
#define GPIO_OPRT_ERROR    (0xFFFFFFFF)

#define OUTER_RFSWITCH_ON   1
#define OUTER_RFSWITCH_OFF  0

enum GPIO_OPRT_ENUM
{
    GPIO_OPRT_SET = 0,
    GPIO_OPRT_GET,
    GPIO_OPRT_BUTT
};

typedef enum tagGPIO_ANT_MODESET_E
{
    ANT_LTE     =  0,/*lte�ּ�����*/
    ANT_GSM     =  1,/*GSM��������*/
    ANT_MAX
} GPIO_ANT_MODESET_E;

/*****************************************************************************
 �� �� ��  : BSP_GPIO_Oprt
 ��������  : at^GPIOPL,���úͲ�ѯGPIO�ĵ�ƽ
 �������  : �������� ulOp:
             0  ���ø�GPIO��PLֵ
             1  ��ѯ��ǰ��GPIO��PLֵ

             pucPL ��Ӧ20Byte������,ÿ��BYTE����һ��8���ܽŵ�ֵ

             ���ò���ʱ,pucPLΪ���õ�20��Byte
             ��ѯ����ʱ,pucPLΪ��ǰ��ȡ����PL��ʵ��ֵ��ɵ�16��������
             �����û�����at^GPIOPL = ABCDEF,���ӦpucPL������ֵΪ{A,B,C,D,E,F,0,0,...}

 �������  : ��
 �� �� ֵ  :  0 ��OK  �� 0 ��Error

*****************************************************************************/
extern unsigned long drv_gpio_oprt(unsigned long ulOp, unsigned char *pucPL);
#define DRV_GPIO_OPRT(ulOp, pucPL) drv_gpio_oprt(ulOp, pucPL)


/* from v9r1, ����GPIO ���뿪���ж��Ƿ�����Э��ջ����, V7R2�ȴ�׮ʵ�� */
static INLINE unsigned long DRV_BBP_GPIO_GET(void)
{
	return ~DRV_NOT_START_UMTS;
}



static INLINE int BSP_Modem_OS_Status_Switch(int enable)
{
    return 0;
}
#define DRV_OS_STATUS_SWITCH(enable) BSP_Modem_OS_Status_Switch(enable)


extern int outer_rfswitch_set(unsigned int status);
#define  DRV_OUTER_RFSWITCH_SET(status) outer_rfswitch_set(status)

extern int outer_rfswitch_get(unsigned int *status);
#define  DRV_OUTER_RFSWITCH_GET(status) outer_rfswitch_get(status)


extern int bsp_ant_modem_set(GPIO_ANT_MODESET_E mode);
#define  DRV_ANT_MODE_SET(mode) bsp_ant_modem_set(mode)


extern int bsp_gpio_rf_pin_set(unsigned int mask, unsigned int is_hz, unsigned int value);
#define DRV_RF_PIN_HIGHZ_SET(ulPinMask,ulPinHz,ulPinValue) bsp_gpio_rf_pin_set(ulPinMask,ulPinHz,ulPinValue)




/*************************GPIO END************************************/

#ifdef __cplusplus
}
#endif

#endif

