
#ifndef __KEY_BALONG_H__
#define __KEY_BALONG_H__

#include <product_config.h>

#if (FEATURE_ON == MBB_DLOAD_SDUP)
#define KEY_UP   0  //����̧��
#define KEY_DOWN 1  //��������

#define KEY_DETECT_TIME_2000MS   (2000)  /*SD��������ϼ�����ʱ�䳤��*/
#define KEY_DETECT_TIME_500MS    (500)   /*SD����������ʱ˫�������ʱ��*/
#define DOUBLE_CLK_KEY  (KEY_F24)       /*SD����������ʱ��Ҫ˫���ļ�*/
#endif

typedef enum
{
    INVALID_KEY,
    POWER_KEY,
    MENU_KEY,
    RESET_KEY,
    WIFI_KEY,
    BUTT_KEY
}KEY_ENUM;


void key_int_disable(KEY_ENUM key);


void key_int_enable(KEY_ENUM key);

#endif