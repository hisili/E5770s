

#ifndef __MBB_LEDS_H__
#define __MBB_LEDS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <product_config.h>
#include <hi_gpio.h>
#include <drv_version.h>

#if (FEATURE_ON == MBB_LED)
/**************************************************************************
  ͷ�ļ�����                            
**************************************************************************/

/**************************************************************************
  �궨�� 
**************************************************************************/
#define LEDS_GPIO_DEFSTATE_OFF        0
#define LEDS_GPIO_DEFSTATE_ON        1
#define LEDS_GPIO_DEFSTATE_KEEP        2
#ifndef UNUSED_PARAMETER
/* Suppress unused parameter warning */
#define UNUSED_PARAMETER(x) (void)(x)
#define DR12_BRIGHTNESS_3MA    31       /*DR12���3mA������Ӧ������ֵ*/
#ifdef BSP_CONFIG_BOARD_E8378WS_210
#define DR12_BRIGHTNESS_9MA    95       /*DR12���9mA������Ӧ������ֵ*/
#endif
#define DR345_BRIGHTNESS_3MA    170     /*DR345���3mA������Ӧ������ֵ*/

enum led_brightness {
	LED_OFF		= 0,
	LED_HALF	= 127,
	LED_FULL	= 255,
};

#endif

#define LED_LTE_RED         "lte_led:red"
#define LED_LTE_GREEN       "lte_led:green"
#define LED_LTE_BLUE       "lte_led:blue"
#define LED_BREATH          "breath_led"
#define LED_BATT_RED        "bat_led:red"
#define LED_BATT_GREEN      "bat_led:green"
#define LED_BATT_BLUE       "bat_led:blue"
#define LED_BATT_GPIO_BLUE  "bat_led:blue_power"
#define LED_WIFI_RED        "wifi_led:red"
#define LED_WIFI_GREEN      "wifi_led:green"
#define LED_WIFI_BLUE      "wifi_led:blue"
#define LED_FLOW_RED        "flow_led:red"
#define LED_FLOW_GREEN      "flow_led:green"
#define LED_FLOW_BLUE      "flow_led:blue"
#define LED_BREATH_BLUE     "breath_led:blue"
#define LED_BREATH_RED      "breath_led:red"
#define LED_MSG_GREEN        "msg_led:green"
#define BAT1_LED_WHITE      "bat1_led:white"
#define BAT2_LED_WHITE      "bat2_led:white"
#define BAT3_LED_WHITE      "bat3_led:white"
#define BAT4_LED_WHITE      "bat4_led:white"
#define LED_ROAMING_GREEN   "roaming_led:green"  /*  E5771h-937�����̵� */
#define LED_ROAMING_BLUE    "roaming_led:blue"   /*  E5771h-937�������� */
#define LED_ON     (1)
#define LED_OFF    (0)

/**************************************************************************
  �������ṹ���� 
**************************************************************************/
/*
 * Generic LED platform data for describing LED names and default triggers.
 */
struct led_info {
    const char    *name;
    const char    *default_trigger;
    int        flags;
    int        max_brightness;
#if (FEATURE_ON == MBB_LED_UNIFORM)
    /* ����Ϊname��DR LED������Ӧ��DR �ڵ㣬��1/2/3/4/5 */
    int        dr_node;
    /* dr��Ĭ���������ã�ע��DR1/2��DR3/4/5�������в�� */
    int        dr_led_brightness;
#endif
};

/* For the leds-gpio driver */
struct gpio_led {
    const char *name;
    const char *default_trigger;
    unsigned     gpio;
    unsigned    active_low : 1;
    unsigned    retain_state_suspended : 1;
    unsigned    default_state : 2;
    /* default_state should be one of LEDS_GPIO_DEFSTATE_(ON|OFF|KEEP) */
};
#define NAME_MAX_SIZE 50    /*������������󳤶�*/
#define GPIO_LED_NUMBER  (10)      /* GPIO���ܸ��� */
#define DR_LED_NUMBER    (5)       /* DR���ܸ��� */

/* �Ƶĸ��� */
#define HAVE_NO_LED          (0)
#define HAVE_ONE_LED         (1)
#define HAVE_TWO_LED         (2)
#define HAVE_THREE_LED       (3)
#define HAVE_FOUR_LED        (4)
#define HAVE_FIVE_LED        (5)
#define HAVE_SIX_LED         (6)
#define HAVE_SEVEN_LED       (7)
#define HAVE_EIGHT_LED       (8)
#define HAVE_NINE_LED        (9)
#define HAVE_TEN_LED         (10)

struct support_uniform_config{
    unsigned int board_id;                         /* ֧�ֹ�һ��Ӳ��ID */
    unsigned int total_gpio_led_number;            /* gpio�Ƹ��� */
    struct gpio_led gpio_led[GPIO_LED_NUMBER];     /* gpio������ */
    unsigned int total_dr_led_number;              /* dr�Ƹ��� */
    struct led_info dr_led[DR_LED_NUMBER];         /* dr������ */
};

struct led_kernelset_date    /*led-kernel�ӿڣ�����led������Ϣ*/
{
    char name[NAME_MAX_SIZE];
    int statu;
    int flag;   /*�Ʊ�������־*/
};

#if(FEATURE_ON == MBB_LED_GPIO)
/*GPIO ��Ϣ�Լ��ڵ�������ݲ��õ���̬��Ҫ������*/
#ifdef BSP_CONFIG_BOARD_CPE
#define MODE_RED_EN            GPIO_1_23
#define MODE_BLUE_EN           GPIO_2_10
#define MODE_GREEN_EN          GPIO_2_11
#define WIFI_WHITE_EN          GPIO_NULL
#endif
#if defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5573S_156) \
    || defined(BSP_CONFIG_BOARD_E5573S_856) || defined(BSP_CONFIG_BOARD_E5573S_853) \
    || defined(BSP_CONFIG_BOARD_E5573S_607)
#define LTE_RED_EN             GPIO_2_7
#define LTE_GREEN_EN           GPIO_2_6
#endif
#if defined(BSP_CONFIG_BOARD_401HW) || defined(BSP_CONFIG_BOARD_506HW) \
 || defined(BSP_CONFIG_BOARD_506HW_2)
#define LTE_RED_EN             GPIO_1_5
#define LTE_GREEN_EN           GPIO_1_6
#define LTE_BLUE_EN             GPIO_1_7
#define FLOW_RED_EN           GPIO_1_8
#define FLOW_GREEN_EN         GPIO_1_9
#define FLOW_BLUE_EN          GPIO_1_10
#define BAT_YELLOW_EN         GPIO_NULL
#endif


#ifdef BSP_CONFIG_BOARD_WINGLE
#ifdef BSP_CONFIG_BOARD_E8378WS_210
#define MODE_RED_EN       GPIO_1_5//Net State LED ����״ָ̬ʾ��(Indicate light for net state searching,registering or connecting)
#define MODE_GREEN_EN     GPIO_1_6 
#define MODE_BLUE_EN       GPIO_1_7
#define LTE_RED_EN          GPIO_2_1
#elif defined(BSP_CONFIG_BOARD_WINGLE_MS2172S_818)
#define LTE_LED_GREEN_EN            GPIO_1_21
#define LTE_LED_RED_EN              GPIO_1_29
#define WIFI_LED_GREEN_EN           GPIO_1_19
#define WIFI_LED_RED_EN             GPIO_1_16
#elif defined(BSP_CONFIG_BOARD_WINGLE_E8372h_155)
#define WIFI_LED_EN                 GPIO_0_2
#define MESSAGE_LED_EN              GPIO_0_5
#else

#define WIFI_GREEN_EN          GPIO_0_2
#define MSG_RED_EN             GPIO_0_5
#endif
#endif
#if defined (BSP_CONFIG_BOARD_E5575S_210) || defined (BSP_CONFIG_BOARD_E5575S_320)
#define BREATH_RED_EN          GPIO_2_2
#define LTE_RED_EN             GPIO_2_7
#define LTE_GREEN_EN           GPIO_2_6
#define LTE_BLUE_EN            GPIO_2_16
#define BAT_BLUE_POWER_EN      GPIO_2_4
#endif
#ifdef BSP_CONFIG_BOARD_E5771S_852
#define LTE_BLUE_EN          GPIO_2_7
#define BAT2_LED_EN          GPIO_2_6
#define BAT3_LED_EN          GPIO_2_4
#define BAT4_LED_EN          GPIO_2_5
#endif
#ifdef BSP_CONFIG_BOARD_E5771H_937
#define LTE_RED_EN           GPIO_2_7   /*��������GPIO������*/
#define BAT2_LED_EN          GPIO_2_6   /*���2#����GPIO������*/
#define BAT3_LED_EN          GPIO_1_31  /*���3#����GPIO������*/
#define BAT4_LED_EN          GPIO_2_5   /*���4#����GPIO������*/
#define ROAMING_GREEN_EN     GPIO_2_4   /*�����̵���GPIO_2_4������*/
#define ROAMING_BLUE_EN      GPIO_2_26  /*����������GPIO_2_26������*/
#endif /*BSP_CONFIG_BOARD_E5771H_937*/
#if defined BSP_CONFIG_BOARD_E5573CS
#define MES_GREEN_EN         GPIO_1_17
#define NET_RED_EN           GPIO_2_7
#define NET_GREEN_EN         GPIO_2_6
#define BAT_RED_EN           GPIO_0_5
#define BAT_GREEN_EN         GPIO_2_3
#endif
#if defined BSP_CONFIG_BOARD_E5573BS
#define MES_GREEN_EN         GPIO_1_17
#define NET_RED_EN           GPIO_2_7
#define NET_GREEN_EN         GPIO_2_6
#define BAT_RED_EN           GPIO_0_5
#define BAT_GREEN_EN         GPIO_2_3
#endif

#if defined BSP_CONFIG_BOARD_E5573CS_933
#define MES_RED_EN           GPIO_1_6
#define MES_GREEN_EN         GPIO_1_7
#define NET_RED_EN           GPIO_1_8
#define NET_GREEN_EN         GPIO_1_9
#define BAT_RED_EN           GPIO_2_4
#define BAT_GREEN_EN         GPIO_2_3
#endif


#if (FEATURE_ON == MBB_LED_UNIFORM)
#define DR_NODE_1 (1)             /* DR1 ͨ�� */
#define DR_NODE_2 (2)             /* DR2 ͨ�� */
#define DR_NODE_3 (3)             /* DR3 ͨ�� */
#define DR_NODE_4 (4)             /* DR4 ͨ�� */
#define DR_NODE_5 (5)             /* DR5 ͨ�� */
#endif

/*
��ע�⡿711ƽ̨LED��һ���������÷���ʵ���˵�����������ݻ�ȡ����Ӳ��ID��̬����LED��
�����²�Ʒ����LEDʱ����Ҫ�ڴ˴����LED������Ϣ��
*/
static struct support_uniform_config uniform_led_config[] = {
    {
        .board_id = HW_VER_PRODUCT_E5573CS_509,     /* ����Ӳ��ID */
        .total_gpio_led_number = HAVE_FOUR_LED,     /* ����֧��GPIO LED�Ƹ��� */
        {                                           /* GPIO LED ���� */
            {
                .name = LED_LTE_RED,
                .default_trigger = "timer",
                .gpio = GPIO_1_8,
                .active_low = 0,
                .retain_state_suspended = 0,
                .default_state = LEDS_GPIO_DEFSTATE_OFF,
            },
            {
                .name = LED_LTE_GREEN,
                .default_trigger = "timer",
                .gpio = GPIO_1_9,
                .active_low = 0,
                .retain_state_suspended = 0,
                .default_state = LEDS_GPIO_DEFSTATE_ON,
            },
            {
                .name = LED_BATT_RED,
                .default_trigger = "timer",
                .gpio = GPIO_2_4,
                .active_low = 0,
                .retain_state_suspended = 0,
                .default_state = LEDS_GPIO_DEFSTATE_OFF,
            },
            {
                .name = LED_BATT_GREEN,
                .default_trigger = "timer",
                .gpio = GPIO_2_3,
                .active_low = 0,
                .retain_state_suspended = 0,
                .default_state = LEDS_GPIO_DEFSTATE_ON,
            },
        },
        /* ����֧��DR LED����, ���֧��DR�ƣ���Ҫ����������DR LED���� */
        .total_dr_led_number = HAVE_NO_LED,
    },
    {
        .board_id = HW_VER_PRODUCT_R218h,     /* ����Ӳ��ID */
        .total_gpio_led_number = HAVE_FIVE_LED,     /* ����֧��GPIO LED�Ƹ��� */
        {                                           /* GPIO LED ���� */
            {
                .name = LED_MSG_GREEN,
                .default_trigger = "timer",
                .gpio = GPIO_1_17,
                .active_low = 0,
                .retain_state_suspended = 0,
                .default_state = LEDS_GPIO_DEFSTATE_OFF,
            },
            {
                .name = LED_LTE_RED,
                .default_trigger = "timer",
                .gpio = GPIO_2_7,
                .active_low = 0,
                .retain_state_suspended = 0,
                .default_state = LEDS_GPIO_DEFSTATE_OFF,
            },
            {
                .name = LED_LTE_GREEN,
                .default_trigger = "timer",
                .gpio = GPIO_2_6,
                .active_low = 0,
                .retain_state_suspended = 0,
                .default_state = LEDS_GPIO_DEFSTATE_ON,
            },
            {
                .name = LED_BATT_RED,
                .default_trigger = "timer",
                .gpio = GPIO_0_5,
                .active_low = 0,
                .retain_state_suspended = 0,
                .default_state = LEDS_GPIO_DEFSTATE_OFF,
            },
            {
                .name = LED_BATT_GREEN,
                .default_trigger = "timer",
                .gpio = GPIO_2_3,
                .active_low = 0,
                .retain_state_suspended = 0,
                .default_state = LEDS_GPIO_DEFSTATE_ON,
            },
        },
        /* ����֧��DR LED����, ���֧��DR�ƣ���Ҫ����������DR LED���� */
        .total_dr_led_number = HAVE_NO_LED,
    },
    {
        .board_id = HW_VER_PRODUCT_MS2372H_153,     /* ����Ӳ��ID */
        .total_gpio_led_number = HAVE_NO_LED,     /* ����֧��GPIO LED�Ƹ��� */
 
    /* ����֧��DR LED����, ���֧��DR�ƣ���Ҫ����������DR LED���� */
        .total_dr_led_number = HAVE_THREE_LED,
        {
            {
                .name = LED_LTE_RED,
                .max_brightness = LED_FULL,
#if (FEATURE_ON == MBB_LED_UNIFORM)
                .dr_node = DR_NODE_3,
                .dr_led_brightness = DR345_BRIGHTNESS_3MA,
#endif
            },
            {
                .name = LED_LTE_GREEN,
                .max_brightness = LED_FULL,
#if (FEATURE_ON == MBB_LED_UNIFORM)
                .dr_node = DR_NODE_4,
                .dr_led_brightness = DR345_BRIGHTNESS_3MA,
#endif
            },
            {
                .name = LED_LTE_BLUE,
                .max_brightness = LED_FULL,
#if (FEATURE_ON == MBB_LED_UNIFORM)
                .dr_node = DR_NODE_5,
                .dr_led_brightness = DR345_BRIGHTNESS_3MA,
#endif
            }
        }
    },
    {
        /* ����Ӳ��ID */
        .board_id = HW_VER_PRODUCT_MS2372h_517,
        /* ����֧��GPIO LED�Ƹ��� */
        .total_gpio_led_number = HAVE_NO_LED,
 
        /* ����֧��DR LED����, ���֧��DR�ƣ���Ҫ����������DR LED���� */
        .total_dr_led_number = HAVE_THREE_LED,
        {
            {
                .name = LED_LTE_GREEN,
                .max_brightness = LED_FULL,
#if (FEATURE_ON == MBB_LED_UNIFORM)
                .dr_node = DR_NODE_1,
                .dr_led_brightness = DR12_BRIGHTNESS_3MA,
#endif
            },
            {
                .name = LED_LTE_BLUE,
                .max_brightness = LED_FULL,
#if (FEATURE_ON == MBB_LED_UNIFORM)
                .dr_node = DR_NODE_2,
                .dr_led_brightness = DR12_BRIGHTNESS_3MA,
#endif
            },
            {
                .name = LED_LTE_RED,
                .max_brightness = LED_FULL,
#if (FEATURE_ON == MBB_LED_UNIFORM)
                .dr_node = DR_NODE_3,
                .dr_led_brightness = DR345_BRIGHTNESS_3MA,
#endif
            },
        },
    },
    {
        /* ����Ӳ��ID */
        .board_id = HW_VER_PRODUCT_MS2372h_607,
        /* ����֧��GPIO LED�Ƹ��� */
        .total_gpio_led_number = HAVE_NO_LED,

        /* ����֧��DR LED����, ���֧��DR�ƣ���Ҫ����������DR LED���� */
        .total_dr_led_number = HAVE_THREE_LED,
        {
            {
                .name = LED_LTE_GREEN,
                .max_brightness = LED_FULL,
#if (FEATURE_ON == MBB_LED_UNIFORM)
                .dr_node = DR_NODE_1,
                .dr_led_brightness = DR12_BRIGHTNESS_3MA,
#endif
            },
            {
                .name = LED_LTE_BLUE,
                .max_brightness = LED_FULL,
#if (FEATURE_ON == MBB_LED_UNIFORM)
                .dr_node = DR_NODE_2,
                .dr_led_brightness = DR12_BRIGHTNESS_3MA,
#endif
            },
            {
                .name = LED_LTE_RED,
                .max_brightness = LED_FULL,
#if (FEATURE_ON == MBB_LED_UNIFORM)
                .dr_node = DR_NODE_3,
                .dr_led_brightness = DR345_BRIGHTNESS_3MA,
#endif
            },
        },
    },
};

/*
LED�ƹ�һ��������ʵ�֣������ñ�����Ϊ�˼�����ǰ����Ŀ������Ŀ����ʱ��Ҫ�ڸô�����
*/
static struct gpio_led gpio_exp_leds_config[] = {
#ifdef BSP_CONFIG_BOARD_CPE
    {
        .name = "mode_led:red",
        .default_trigger = "timer",
        .gpio = MODE_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "mode_led:green",
        .default_trigger = "timer",
        .gpio = MODE_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "mode_led:blue",
        .default_trigger = "timer",
        .gpio = MODE_BLUE_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "wifi_led:white",
        .default_trigger = "timer",
        .gpio = WIFI_WHITE_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
#endif
#if defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5573S_156) \
    || defined(BSP_CONFIG_BOARD_E5573S_856) || defined(BSP_CONFIG_BOARD_E5573S_853) \
    || defined(BSP_CONFIG_BOARD_E5573S_607)
    {
        .name = "lte_led:red",
        .default_trigger = "timer",
        .gpio = LTE_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "lte_led:green",
        .default_trigger = "timer",
        .gpio = LTE_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
#endif
#if defined(BSP_CONFIG_BOARD_401HW) || defined(BSP_CONFIG_BOARD_506HW) \
 || defined(BSP_CONFIG_BOARD_506HW_2)
    {
        .name = "lte_led:red",
        .default_trigger = "timer",
        .gpio = LTE_RED_EN,
        .active_low = 1,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "lte_led:green",
        .default_trigger = "timer",
        .gpio = LTE_GREEN_EN,
        .active_low = 1,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "lte_led:blue",
        .default_trigger = "timer",
        .gpio = LTE_BLUE_EN,
        .active_low = 1,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "flow_led:red",
        .default_trigger = "timer",
        .gpio = FLOW_RED_EN,
        .active_low = 1,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "flow_led:green",
        .default_trigger = "timer",
        .gpio = FLOW_GREEN_EN,
        .active_low = 1,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "flow_led:blue",
        .default_trigger = "timer",
        .gpio = FLOW_BLUE_EN,
        .active_low = 1,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "bat_led:yellow",
        .default_trigger = "timer",
        .gpio = BAT_YELLOW_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
#endif
#ifdef BSP_CONFIG_BOARD_WINGLE
#ifdef BSP_CONFIG_BOARD_E8378WS_210
    {
        .name = "mode_led:red",
        .default_trigger = "timer",
        .gpio = MODE_RED_EN,
        .active_low = 1,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "mode_led:green",
        .default_trigger = "timer",
        .gpio = MODE_GREEN_EN,
        .active_low = 1,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "mode_led:blue",
        .default_trigger = "timer",
        .gpio = MODE_BLUE_EN,
        .active_low = 1,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },     
    {
        .name = "lte_led:red",
        .default_trigger = "timer",
        .gpio = LTE_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
#elif defined(BSP_CONFIG_BOARD_WINGLE_MS2172S_818)
    {
        .name = "lte_led:green",
        .default_trigger = "timer",
        .gpio = LTE_LED_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "lte_led:red",
        .default_trigger = "timer",
        .gpio = LTE_LED_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "wifi_led:green",
        .default_trigger = "timer",
        .gpio = WIFI_LED_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "wifi_led:red",
        .default_trigger = "timer",
        .gpio = WIFI_LED_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
#elif defined(BSP_CONFIG_BOARD_WINGLE_E8372h_155)
    {
        .name = "wifi_led:green",
        .default_trigger = "timer",
        .gpio = WIFI_LED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "msg_led:green",
        .default_trigger = "timer",
        .gpio = MESSAGE_LED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },

#else
    {
        .name = "wifi_led:green",
        .default_trigger = "timer",
        .gpio = WIFI_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
#if (FEATURE_ON ==MBB_TELSTRA_CUSTOMSIZE)
        .name = "flow_led:red",
#elif defined (BSP_CONFIG_BOARD_E8372H_608)
        .name = "msg_led:red",
#else
        .name = "msg_led:green",
#endif       
        .default_trigger = "timer",
        .gpio = MSG_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
#endif
#endif
#if defined (BSP_CONFIG_BOARD_E5575S_210) || defined (BSP_CONFIG_BOARD_E5575S_320)
{
        .name = "breath_led:red",
        .default_trigger = "timer",
        .gpio = BREATH_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "lte_led:red",
        .default_trigger = "timer",
        .gpio = LTE_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "lte_led:green",
        .default_trigger = "timer",
        .gpio = LTE_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "lte_led:blue",
        .default_trigger = "timer",
        .gpio = LTE_BLUE_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "bat_led:blue_power",
        .default_trigger = "timer",
        .gpio = BAT_BLUE_POWER_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
#endif
#ifdef BSP_CONFIG_BOARD_E5771S_852
{
        .name = "bat2_led:white",
        .default_trigger = "timer",
        .gpio = BAT2_LED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "bat3_led:white",
        .default_trigger = "timer",
        .gpio = BAT3_LED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "bat4_led:white",
        .default_trigger = "timer",
        .gpio = BAT4_LED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "lte_led:blue",
        .default_trigger = "timer",
        .gpio = LTE_BLUE_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
#endif
#ifdef BSP_CONFIG_BOARD_E5771H_937
    {
        .name = "bat2_led:white",
        .default_trigger = "timer",
        .gpio = BAT2_LED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "bat3_led:white",
        .default_trigger = "timer",
        .gpio = BAT3_LED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "bat4_led:white",
        .default_trigger = "timer",
        .gpio = BAT4_LED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "lte_led:red",
        .default_trigger = "timer",
        .gpio = LTE_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {  /* E5771h-937�������εƣ�name��Ҫ��Ӧ��ȷ��ͳһ,��ɫ�ƣ��̵ơ����ơ��Լ�������ɫ�Ļ��ɫ�� */
        .name = "roaming_led:green",
        .default_trigger = "timer",
        .gpio = ROAMING_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {  /* ���εƵ��̵ƺ����ƶ�����GPIO������  */
        .name = "roaming_led:blue",
        .default_trigger = "timer",
        .gpio = ROAMING_BLUE_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
#endif /*BSP_CONFIG_BOARD_E5771H_937*/
#if defined BSP_CONFIG_BOARD_E5573CS
    {
        .name = "msg_led:green",
        .default_trigger = "timer",
        .gpio = MES_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "lte_led:red",
        .default_trigger = "timer",
        .gpio = NET_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "lte_led:green",
        .default_trigger = "timer",
        .gpio = NET_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "bat_led:red",
        .default_trigger = "timer",
        .gpio = BAT_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "bat_led:green",
        .default_trigger = "timer",
        .gpio = BAT_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
#endif
#if defined BSP_CONFIG_BOARD_E5573BS
    {
        .name = "msg_led:green",
        .default_trigger = "timer",
        .gpio = MES_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
   {
        .name = "lte_led:red",
        .default_trigger = "timer",
        .gpio = NET_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "lte_led:green",
        .default_trigger = "timer",
        .gpio = NET_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "bat_led:red",
        .default_trigger = "timer",
        .gpio = BAT_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "bat_led:green",
        .default_trigger = "timer",
        .gpio = BAT_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
#endif
#if defined BSP_CONFIG_BOARD_E5573CS_933
    {
        .name = "msg_led:green",
        .default_trigger = "timer",
        .gpio = MES_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "msg_led:red",
        .default_trigger = "timer",
        .gpio = MES_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "lte_led:red",
        .default_trigger = "timer",
        .gpio = NET_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "lte_led:green",
        .default_trigger = "timer",
        .gpio = NET_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
    {
        .name = "bat_led:red",
        .default_trigger = "timer",
        .gpio = BAT_RED_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_OFF,
    },
    {
        .name = "bat_led:green",
        .default_trigger = "timer",
        .gpio = BAT_GREEN_EN,
        .active_low = 0,
        .retain_state_suspended = 0,
        .default_state = LEDS_GPIO_DEFSTATE_ON,
    },
#endif


};
#endif

#if(FEATURE_ON == MBB_LED_DR)
/*NODE ���Ʋ��õĲ�Ʒ��Ҫ������*/
#ifdef BSP_CONFIG_BOARD_CPE
#define LED_NODE_1 "signal1_led:white"      
#define LED_NODE_2 "signal2_led:white" 
#define LED_NODE_3 "signal3_led:white" 
#define LED_NODE_4 "lan_led:white" 
#define LED_NODE_5 "5"
#endif 

#ifdef BSP_CONFIG_BOARD_HILINK
#define LED_NODE_1 "1"      
#define LED_NODE_2 "2" 
#define LED_NODE_3 "lte_led:red" 
#define LED_NODE_4 "lte_led:green" 
#define LED_NODE_5 "lte_led:blue"
#endif 

#if defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5573S_156) \
    || defined(BSP_CONFIG_BOARD_E5573S_856) || defined(BSP_CONFIG_BOARD_E5573S_853) \
    || defined(BSP_CONFIG_BOARD_E5573S_607)
#define LED_NODE_1 "1"
#define LED_NODE_2 "2" 
#define LED_NODE_3 "bat_led:red" 
#define LED_NODE_4 "bat_led:green" 
/* E5��̬û��msg_led:green�ƵĲ�Ʒ��led_dr.c�д����ڵ�ʱ����msg_led:green�ڵ� */
#define LED_NODE_5 "msg_led:green"
#endif
#if defined(BSP_CONFIG_BOARD_401HW) || defined(BSP_CONFIG_BOARD_506HW) \
 || defined(BSP_CONFIG_BOARD_506HW_2)
#define LED_NODE_1 "wifi_led:blue"
#define LED_NODE_2 "wifi_led:red" 
#define LED_NODE_3 "bat_led:red"
#define LED_NODE_4 "bat_led:green"
#define LED_NODE_5 "wifi_led:green"
#endif 

#ifdef BSP_CONFIG_BOARD_STICK
#define LED_NODE_1 "1"      
#define LED_NODE_2 "2" 
#define LED_NODE_3 "lte_led:red" 
#define LED_NODE_4 "lte_led:green" 
#define LED_NODE_5 "lte_led:blue"
#endif 

#ifdef BSP_CONFIG_BOARD_WINGLE
#ifdef BSP_CONFIG_BOARD_E8378WS_210
#define LED_NODE_1 "lte_led:green"        //3G/4G LED LTEģʽָʾ��(indicator light for net state 3g or 4g)
#define LED_NODE_2 "signal1_led:blue" //Signal LED  �ź�ǿ��ָʾ��(indicator light for signal strength) 
#define LED_NODE_3 "signal1_led:red"
#define LED_NODE_4 "signal1_led:green"
#define LED_NODE_5 "5"
#elif defined(BSP_CONFIG_BOARD_WINGLE_MS2172S_818)
#define LED_NODE_1 "lte_led:blue"
#define LED_NODE_2 "wifi_led:blue"
#define LED_NODE_3 "3"
#define LED_NODE_4 "4"
#define LED_NODE_5 "5"
#elif defined(BSP_CONFIG_BOARD_WINGLE_E8372h_155)
#define LED_NODE_1 "1" 
#define LED_NODE_2 "2" 
#define LED_NODE_3 "lte_led:red"
#define LED_NODE_4 "lte_led:green"
#define LED_NODE_5 "lte_led:blue"
#else
#if (FEATURE_ON ==MBB_TELSTRA_CUSTOMSIZE)
#define LED_NODE_1 "flow_led:green" 
#elif defined (BSP_CONFIG_BOARD_E8372H_608)
#define LED_NODE_1 "msg_led:green"
#else
#define LED_NODE_1 "1"   
#endif
#define LED_NODE_2 "2" 
#define LED_NODE_3 "lte_led:red" 
#define LED_NODE_4 "lte_led:green" 
#define LED_NODE_5 "lte_led:blue"
#endif
#endif

#if defined (BSP_CONFIG_BOARD_E5575S_210) || defined (BSP_CONFIG_BOARD_E5575S_320)
#define LED_NODE_1 "breath_led:green" 
#define LED_NODE_2 "breath_led:blue" 
#define LED_NODE_3 "bat_led:red" 
#define LED_NODE_4 "bat_led:green" 
#define LED_NODE_5 "bat_led:blue"
#endif

#ifdef BSP_CONFIG_BOARD_E5771S_852
#define LED_NODE_1 "lte_led:red" 
#define LED_NODE_2 "lte_led:green" 
#define LED_NODE_3 "bat1_led:white" 
#define LED_NODE_4 "4"
#define LED_NODE_5 "5"
#endif

#ifdef BSP_CONFIG_BOARD_E5771H_937
#define LED_NODE_1 "lte_led:blue" 
#define LED_NODE_2 "lte_led:green" 
#define LED_NODE_3 "bat1_led:white" 
#endif /*BSP_CONFIG_BOARD_E5771H_937*/



/*ע��Ľڵ��б�����Ҫ������*/
static struct led_info led_dr[] = {
#ifdef BSP_CONFIG_BOARD_CPE   
    [0] = {
        .name = LED_NODE_1,
        .max_brightness = DR12_BRIGHTNESS_3MA,
    },
    [1] = {
        .name = LED_NODE_2,
        .max_brightness = DR12_BRIGHTNESS_3MA,
    },
    [2] = {
        .name = LED_NODE_3,
        .max_brightness = DR345_BRIGHTNESS_3MA,
    },
    [3] = {
        .name = LED_NODE_4,
        .max_brightness = DR345_BRIGHTNESS_3MA,
    }
#endif
#if defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5573S_156) \
    || defined(BSP_CONFIG_BOARD_E5573S_856) || defined(BSP_CONFIG_BOARD_E5573S_853) \
    || defined(BSP_CONFIG_BOARD_E5573S_607)

    [0] = {
        .name = LED_NODE_3,
        .max_brightness = LED_FULL,
    },
    [1] = {
        .name = LED_NODE_4,
        .max_brightness = LED_FULL,
    },
    [2] = {
        .name = LED_NODE_5,
        .max_brightness = LED_FULL,
    }
#endif
#if defined(BSP_CONFIG_BOARD_401HW) || defined(BSP_CONFIG_BOARD_506HW) \
 || defined(BSP_CONFIG_BOARD_506HW_2)
    [0] = {
        .name = LED_NODE_1,
        .max_brightness = LED_FULL,
    },
    [1] = {
        .name = LED_NODE_2,
        .max_brightness = LED_FULL,
    },
    [2] = {
        .name = LED_NODE_3,
        .max_brightness = LED_FULL,
    },
    [3] = {
        .name = LED_NODE_4,
        .max_brightness = LED_FULL,
    },
    [4] = {
        .name = LED_NODE_5,
        .max_brightness = LED_FULL,
    }
#endif
#ifdef BSP_CONFIG_BOARD_WINGLE
#ifdef BSP_CONFIG_BOARD_E8378WS_210
    [0] = {
        .name = LED_NODE_1,
        .max_brightness = DR12_BRIGHTNESS_3MA,
    },
    [1] = {
        .name = LED_NODE_2,
        .max_brightness = DR12_BRIGHTNESS_9MA,
    },
    [2] = {
        .name = LED_NODE_3,
        .max_brightness = LED_FULL,
    },
    [3] = {
        .name = LED_NODE_4,
        .max_brightness = LED_FULL,
    }
#elif defined(BSP_CONFIG_BOARD_WINGLE_MS2172S_818)
    [0] = {
        .name = LED_NODE_1,
        .max_brightness = LED_FULL,
    },
    [1] = {
        .name = LED_NODE_2,
        .max_brightness = LED_FULL,
    }
#elif defined(BSP_CONFIG_BOARD_WINGLE_E8372h_155)
    [0] = {
        .name = LED_NODE_3,
        .max_brightness = LED_FULL,
          },
    [1] = {
        .name = LED_NODE_4,
        .max_brightness = LED_FULL,
          },
    [2] = {
        .name = LED_NODE_5,
        .max_brightness = LED_FULL,
          }


#else       
    [0] = {
        .name = LED_NODE_1,
        .max_brightness = LED_FULL,
    },
    [1] = {
        .name = LED_NODE_3,
        .max_brightness = LED_FULL,    
    },
    [2] = {
        .name = LED_NODE_4,
        .max_brightness = LED_FULL,    
    },
    [3] = {
        .name = LED_NODE_5,
        .max_brightness = LED_FULL,    
    }
#endif
#endif
#if  defined(BSP_CONFIG_BOARD_STICK) || defined (BSP_CONFIG_BOARD_HILINK)
    [0] = {
        .name = LED_NODE_3,
        .max_brightness = LED_FULL,
    },
    [1] = {
        .name = LED_NODE_4,
        .max_brightness = LED_FULL,
    },
    [2] = {
        .name = LED_NODE_5,
        .max_brightness = LED_FULL,
    }
#endif
#if defined (BSP_CONFIG_BOARD_E5575S_210) || defined (BSP_CONFIG_BOARD_E5575S_320)
    [0] = {
        .name = LED_NODE_1,
        .max_brightness = LED_FULL,
    },
    [1] = {
        .name = LED_NODE_2,
        .max_brightness = LED_FULL,
    },
    [2] = {
        .name = LED_NODE_3,
        .max_brightness = LED_FULL,
    },
    [3] = {
        .name = LED_NODE_4,
        .max_brightness = LED_FULL,
    },
    [4] = {
        .name = LED_NODE_5,
        .max_brightness = LED_FULL,
    }
#endif
#if defined (BSP_CONFIG_BOARD_E5771S_852) || defined (BSP_CONFIG_BOARD_E5771H_937)
    [0] = {
        .name = LED_NODE_1,
        .max_brightness = LED_FULL,
    },
    [1] = {
        .name = LED_NODE_2,
        .max_brightness = LED_FULL,
    },
    [2] = {
        .name = LED_NODE_3,
        .max_brightness = LED_FULL,
    }
#endif
};
#endif
/**************************************************************************
  �������� 
**************************************************************************/

int led_kernel_status_set(char* led_name, int onoff);



bool support_uniform_product(u32 product_type, int *match_id);

#endif
#ifdef __cplusplus
}
#endif

#endif

