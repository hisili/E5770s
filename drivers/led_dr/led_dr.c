

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/syscalls.h>
#include <asm/unistd.h>
#include <asm/uaccess.h>
#include <linux/errno.h>
#include <linux/miscdevice.h>
#include "bsp_nvim.h"
#include "bsp_pmu.h"
#include "led_dr.h"

#include <linux/err.h>
#include <linux/leds.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/types.h>
#include "bsp_leds.h"
#include "bsp_regulator.h"
#include "bsp_icc.h"
#include "bsp_softtimer.h"
#include <../leds/leds_balong.h>
#include "product_config.h"
#include <drv_version.h>
/*******************************���Ͷ�����**********************************/
/* DR��� */

typedef enum
{
    BREATH_DR01 = 1,
    BREATH_DR02 ,
    BREATH_DR03 ,
    BREATH_DR04 ,
    BREATH_DR05 ,
    BREATH_DR_BOTTOM
}breathled_id_e;

/* ������ʹ�ܿ��� */
typedef enum
{
    BREATH_LED_BREATH    = 0,  /* LED�ƺ���ģʽ�� */
    BREATH_LED_TIMER     = 1,  /* LED����˸ģʽ�� */
    BREATH_LED_NONE      = 2,  /* LED�ƹر� */
    BREATH_LED_BOTTOM, 
}breath_led_ctrl;

typedef struct
{
    unsigned char led_enable;        /* LED��ʹ�ܿ��� */
    unsigned char led_dr;            /* LED����ʹ�õ�DR */
    unsigned char led_mode;          /* LED��ģʽ��־ */
    unsigned char led_reserve;        /* LED��ģʽ��־ */
    unsigned int  full_on;           /* LED�ƺ���ģʽ�ȶ����ĳ���ʱ�� */
    unsigned int  full_off;          /* LED�ƺ���ģʽ�ȶ����ĳ���ʱ�� */
    unsigned int  fade_on;           /* LED�ƺ���ģʽ�Ӱ������ĳ���ʱ�� */
    unsigned int  fade_off;          /* LED�ƺ���ģʽ���������ĳ���ʱ�� */
    unsigned int  delay_on;          /* LED����˸ģʽ����ʱ�� */
    unsigned int  delay_period;     /* LED����˸ģʽ����˸����ʱ��*/
    unsigned int  full_long_on;     /* LED�Ƴ����ĳ���ʱ�� */
    unsigned int  full_long_off;    /* LED�Ƴ����ĳ���ʱ�� */
    unsigned int  brightness;       /* LED�����ȵ���ֵ */
}NV_LED_PARA_STRU;

/* ���� */
typedef enum
{
    BRT_ATTR_FULL_ON = 1,    /* LED���ȶ�������ʱ������ */
    BRT_ATTR_FULL_OFF,       /* LED���ȶ������ʱ������ */
    BRT_ATTR_FADE_ON,        /* LED���ɰ���������ʱ������ */
    BRT_ATTR_FADE_OFF,       /* LED�������䰵����ʱ������ */
    BRT_ATTR_DELAY_ON,       /* LED����˸������ʱ������ */
    BRT_ATTR_DELAY_OFF,      /* LED����˸�����ʱ������ */
    BRT_ATTR_BRIGHTNESS,     /* LED��������ֵ���� */
    BRT_ATTR_B0TTOM
}breathled_attr_e;
/*******************************�궨����**********************************/

#define ZERO_TIME  0

/* ������ʹ�� */
#define BREATH_LED_ENABLE   1   /* ������ʹ�� */
#define BREATH_LED_DISABLE  0   /* �����Ʒ�ʹ�� */

/* ������ģʽ */
#define LED_MODE_BREATH     0   /* �����ƺ���ģʽ */

#define LED_MODE_BLINK      1   /* ��������˸ģʽ */

#define NV_ID_LED_PARA  50455
/* �����Ƶ�ǰ״̬ */
PRIVATE breathled_state breath_led_curr_state  = BREATH_LED_STATE_SPARK;

#define ATTR_INFO_LEN 20
#define CONTAINER_LEN 200
#define LED_MAX   32           /*�������ӵ�led �ڵ���*/

/* �����Ƹ��������� */
#define BREATH_TRIGGER_BREATH     "breath"
#define BREATH_TRIGGER_TIMER      "timer"
#define BREATH_TRIGGER_NONE       "none"

#define BREATH_TRIGGER            "trigger"
#define BREATH_FULL_ON            "full_on"
#define BREATH_FULL_OFF           "full_off"
#define BREATH_FADE_ON            "fade_on"
#define BREATH_FADE_OFF           "fade_off"
#define BREATH_DELAY_ON           "delay_on"
#define BREATH_DELAY_OFF          "delay_off"
#define BREATH_BRIGHTNESS         "brightness"
#define LED_LONG_TIME             5000000    /*�����������Ĵ����̶�����ֵ*/

#define DR12_BRIGHTNESS_3MA    31       /*DR12���3mA������Ӧ������ֵ*/
#define DR345_BRIGHTNESS_3MA    170     /*DR345���3mA������Ӧ������ֵ*/

#define DR12_BRIGHTNESS    (3000)    /*��λuA��������Ϊ3mA*/
#define DR345_BRIGHTNESS   (3000)    /*��λuA��������Ϊ3mA*/

#define LED_NAME_1  1      /*��˼�ṩ��Balong_dr1�ڵ�*/
#define LED_NAME_2  2      /*��˼�ṩ��Balong_dr2�ڵ�*/
#define LED_NAME_3  3      /*��˼�ṩ��Balong_dr3�ڵ�*/
#define LED_NAME_4  4      /*��˼�ṩ��Balong_dr4�ڵ�*/
#define LED_NAME_5  5      /*��˼�ṩ��Balong_dr5�ڵ�*/

PRIVATE char path_container[CONTAINER_LEN];
PRIVATE const char* container_format   = "/sys/devices/platform/balong_led/leds/Balong_dr%d/%s";
int  g_dr_name = 0;   
int g_dr_brightness[5] = {-1, -1, -1, -1, -1};     /*��ǰ�����ȱ�ʶ*/
extern struct workqueue_struct *led_workqueue_brightness;    /*������ƶ���*/
/* ����dr led���� */
struct led_info led_dr_uniform[DR_LED_NUMBER] = {{0},{0},{0},{0},{0}};
/* ����dr�������� */

/*******************************����������**********************************/
extern int led_dr_regulator_enable(int led_id);

PUBLIC int breathled_controller(breathled_state led_state);

PRIVATE int breathled_hold(breath_led_ctrl led_ctrl);
PRIVATE int set_breathled_attr(breathled_attr_e br_attr, unsigned long attr_value);
PRIVATE int assemble_container(const char * cmd_obj);
PRIVATE int breathled_breath(void);
PRIVATE int breathled_shine(void);
PRIVATE int breathled_sleep(void);
PRIVATE int breathled_disable(void);
PRIVATE int breathled_nv_init(void);
PRIVATE int breathled_nv_save(void);

/*******************************����������**********************************/

/* �����Ƹ�����ֵ˵�� */
PRIVATE NV_LED_PARA_STRU led_attr_default =
{
    .led_enable    = 1,          /* LED��ʹ�ܿ��� ��Ĭ��ʹ��*/
    .led_dr        = 2,          /* LED����ʹ�õ�DR��Ĭ��Balong_dr2 */
    .led_mode      = 0,          /* LED��ģʽ��־��Ĭ�Ϻ���ģʽ */
    .full_on       = 500000,     /* LED���ȶ����ĳ���ʱ�� */
    .full_off      = 500000,     /* LED���ȶ����ĳ���ʱ�� */
    .fade_on       = 2000000,    /* LED�ƴӰ������ĳ���ʱ�� */
    .fade_off      = 2000000,    /* LED�ƴ��������ĳ���ʱ�� */
    .delay_on      = 101569,     /* LED����˸���ĳ���ʱ�� */
    .delay_period  = 218750,     /* LED����˸����ʱ�� */
    .full_long_on  = 5000000,    /* LED�Ƴ��� */
    .full_long_off = 5000000,    /* LED�Ƴ��� */
    .brightness    = 30,         /* LED�����ȵ���ֵ��������ֵ��Ӧ 3mA */
};

/*lint -e54 -e119 -e30 -e84 -e514 -e18 -e628*/
 struct led_platform_data led_dr_plat_data = {
    .num_leds   = ARRAY_SIZE(led_dr_uniform),
    .leds       = (struct led_info *)led_dr_uniform,
};
/*lint +e54 +e119 +e30 +e84 +e514 -e18 +628*/

static struct platform_device led_dr_dev = {    
    .name      = "led_dr",   
    .id             = -1,    
    .dev ={       
                  .platform_data =  &led_dr_plat_data,
        },
    };

static DEFINE_MUTEX(led_dr_mutex); /* LED������ */

/*******************************����ʵ����**********************************/


PRIVATE int breathled_nv_save(void)
{   
    int ret = 0;

    printk(KERN_DEBUG"[*Breath-Led*] %s: led parameter nv save.\n", __func__);
    
    ret = bsp_nvm_write(NV_ID_LED_PARA, (unsigned char *)(&led_attr_default), sizeof(led_attr_default));
    if(NV_OK != ret)
    {
        printk(KERN_ERR"[*Breath-Led*] %s: led parameter nv write fail.\n", __func__);
        return BR_ERROR;
    }

    return BR_OK;
}


PRIVATE int breathled_nv_init(void)
{   
    int ret = 0;

    printk(KERN_DEBUG"[*Breath-Led*] %s: led parameter nv init.\n", __func__);
    
    ret = bsp_nvm_read(NV_ID_LED_PARA, (unsigned char *)(&led_attr_default), sizeof(led_attr_default));
    if(NV_OK != ret)
    {
        printk(KERN_ERR"[*Breath-Led*] %s: led parameter nv read fail.\n", __func__);
        return BR_ERROR;
    }

    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.led_enable = %d.\n", __func__, led_attr_default.led_enable);
    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.led_dr = %d.\n", __func__, led_attr_default.led_dr);
    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.led_mode = %d.\n", __func__, led_attr_default.led_mode);
    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.full_on = %u.\n", __func__, led_attr_default.full_on);
    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.full_off = %u.\n", __func__, led_attr_default.full_off);
    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.fade_on = %u.\n", __func__, led_attr_default.fade_on);
    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.fade_off = %u.\n", __func__, led_attr_default.fade_off);
    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.delay_on = %u.\n", __func__, led_attr_default.delay_on);
    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.delay_period = %u.\n", __func__, led_attr_default.delay_period);
    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.full_long_on = %u.\n", __func__, led_attr_default.full_long_on);
    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.full_long_off = %u.\n", __func__, led_attr_default.full_long_off);
    printk(KERN_DEBUG"[*Breath-Led*] %s: led_attr_default.brightness = %u.\n", __func__, led_attr_default.brightness);
    
    return BR_OK;
}


PRIVATE int assemble_container(const char * cmd_obj)
{   
    int len = 0;
    
    if(!cmd_obj)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] arguments is NULL\n", __FUNCTION__);
        return BR_ERROR;
    }
    /* �ÿ����� */
    (void)memset(path_container, 0x0, CONTAINER_LEN);/*lint !e506*/

    if(BREATH_DR_BOTTOM <= led_attr_default.led_dr || BREATH_DR01 > led_attr_default.led_dr)
    {
        printk(KERN_ERR"[*Breath-Led*] %s: PMU DR selected %d error.\n", __func__, led_attr_default.led_dr);
        return BR_ERROR;
    }
    
    /* ������� */
    len = snprintf(path_container, CONTAINER_LEN, container_format, led_attr_default.led_dr, cmd_obj);
    if(len < 0)
    {
        printk(KERN_ERR"[*Breath-Led*] %s: assemble %s failed.\n", __func__, cmd_obj);
        return BR_ERROR;
    }

    return BR_OK;
}


PRIVATE int breathled_hold(breath_led_ctrl led_ctrl)
{
    struct file *attr_handle = NULL;
    int ret = BR_ERROR;
    int len = -1;
    mm_segment_t old_fs = get_fs();

    if(BREATH_LED_BOTTOM <= led_ctrl)
    {
        printk(KERN_ERR"[*Breath-Led*] %s: para %d invalid.\n", __func__, led_ctrl);
        return BR_ERROR;
    }
    
    /* ��ʼ������·�� */
    ret = assemble_container(BREATH_TRIGGER);
    if(BR_ERROR == ret)
    {
        return BR_ERROR;
    }

    set_fs(KERNEL_DS);

    /* �������ļ� */
    attr_handle = filp_open(path_container, O_RDWR, S_IRWXU);
    if(IS_ERR(attr_handle))
    {
        printk(KERN_ERR"[*Breath-Led*] %s: sys_open \"%s\" failed.\n", __func__,path_container);
        set_fs(old_fs);
        return BR_ERROR;
    }

    /* д������ֵ */
    switch( led_ctrl )
    {
        case BREATH_LED_BREATH:
            /* ʹ�ܺ����ƺ��� */
            len = attr_handle->f_op->write(attr_handle, 
                                           BREATH_TRIGGER_BREATH, 
                                           sizeof(BREATH_TRIGGER_BREATH), 
                                           &attr_handle->f_pos);
            break;
        case BREATH_LED_TIMER:
            /* ʹ�ܺ�������˸ */
            len = attr_handle->f_op->write(attr_handle, 
                                           BREATH_TRIGGER_TIMER, 
                                           sizeof(BREATH_TRIGGER_TIMER), 
                                           &attr_handle->f_pos);
            break;
        case BREATH_LED_NONE:
            /* �رպ����� */
            len = attr_handle->f_op->write(attr_handle, 
                                           BREATH_TRIGGER_NONE, 
                                           sizeof(BREATH_TRIGGER_NONE), 
                                           &attr_handle->f_pos);
            break;
        default:
            break;
    }
    
    if(len < 0) 
    {
        printk(KERN_ERR"[*Breath-Led*] %s: sys_write \"%s\" failed.\n", __func__,path_container);
        (void)filp_close(attr_handle, NULL);
        set_fs(old_fs);
        return BR_ERROR;
    }
    
    (void)filp_close(attr_handle, NULL);
    set_fs(old_fs);
    
    return BR_OK;
}



PRIVATE int set_breathled_attr(breathled_attr_e br_attr, unsigned long attr_value)
{
    struct file *attr_handle = NULL;
    int ret = BR_ERROR;
    int len = 0;
    /* ��������ֵ���� */
    char value_buf[ATTR_INFO_LEN];
    /* �������������� */
    char attr_buf[ATTR_INFO_LEN];
    mm_segment_t old_fs = get_fs();
    
    (void)memset(value_buf, 0x0, sizeof(value_buf));/*lint !e506*/
    (void)memset(attr_buf, 0x0, sizeof(attr_buf));/*lint !e506*/
    switch(br_attr)
    {
        case BRT_ATTR_FULL_ON:
            /* ������Ϣ��� */
            strncpy(attr_buf, BREATH_FULL_ON, sizeof(BREATH_FULL_ON));
            break;
        case BRT_ATTR_FULL_OFF:
            /* ������Ϣ��� */
            strncpy(attr_buf, BREATH_FULL_OFF, sizeof(BREATH_FULL_OFF));
            break;
        case BRT_ATTR_FADE_ON:
            /* ������Ϣ��� */
            strncpy(attr_buf, BREATH_FADE_ON, sizeof(BREATH_FADE_ON));
            break;
        case BRT_ATTR_FADE_OFF:
            /* ������Ϣ��� */
            strncpy(attr_buf, BREATH_FADE_OFF, sizeof(BREATH_FADE_OFF));
            break;
        case BRT_ATTR_DELAY_ON:
            /* ������Ϣ��� */
            strncpy(attr_buf, BREATH_DELAY_ON, sizeof(BREATH_DELAY_ON));
            break;
        case BRT_ATTR_DELAY_OFF:
            /* ������Ϣ��� */
            strncpy(attr_buf, BREATH_DELAY_OFF, sizeof(BREATH_DELAY_OFF));
            break;
        case BRT_ATTR_BRIGHTNESS:
            /* ������Ϣ��� */
            strncpy(attr_buf, BREATH_BRIGHTNESS, sizeof(BREATH_BRIGHTNESS));
            break;
        default:
            /* �������ô��� */
            printk(KERN_ERR"%s: BREATH ATTR error.\n", __func__);
            return BR_ERROR;
    }

    /* ������Ϣ��װ */
    ret = assemble_container(attr_buf);
    if(BR_ERROR == ret)
    {
        return BR_ERROR;
    }

    /* ����ֵ��� */
    len = snprintf(value_buf, sizeof(value_buf), "%ld", attr_value);
    if(len < 0) 
    {
        printk(KERN_ERR"[*Breath-Led*] %s: fill value buffer failded.\n", __func__);
        set_fs(old_fs);
        return BR_ERROR;
    }

    set_fs(KERNEL_DS);

    /* �������ļ� */
    attr_handle = filp_open(path_container, O_RDWR, S_IRWXU);
    if(IS_ERR(attr_handle))
    {
        printk(KERN_ERR"[*Breath-Led*] %s: sys_open \"%s\" failed.\n", __func__,path_container);
        set_fs(old_fs);
        return BR_ERROR;
    }

    /* д������ֵ */
    len = attr_handle->f_op->write(attr_handle, value_buf, len, &attr_handle->f_pos);
    if(len < 0) 
    {
        printk(KERN_ERR"[*Breath-Led*] %s: sys_write \"%s\" failed.\n", __func__,path_container);
        (void)filp_close(attr_handle, NULL);
        set_fs(old_fs);
        return BR_ERROR;
    }
    
    (void)filp_close(attr_handle, NULL);
    set_fs(old_fs);
    
    return BR_OK;
}


PRIVATE int breathled_breath(void)
{
    int ret = BR_ERROR;
    
    /* ��ʼ���� */
    ret = breathled_hold (BREATH_LED_BREATH);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FULL_ON, led_attr_default.full_on);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FULL_OFF, led_attr_default.full_off);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FADE_ON, led_attr_default.fade_on);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FADE_OFF, led_attr_default.fade_off);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_BRIGHTNESS, led_attr_default.brightness);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    
    return BR_OK;
}

/* �����ӿڣ��������澯 */

PRIVATE int breathled_shine(void)
{
    int ret = BR_ERROR;

    /* ��ʼ���� */
    ret = breathled_hold (BREATH_LED_BREATH);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FULL_ON, led_attr_default.full_long_on);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FULL_OFF, ZERO_TIME);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FADE_ON, ZERO_TIME);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FADE_OFF, ZERO_TIME);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_BRIGHTNESS, led_attr_default.brightness);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    
    return BR_OK;
}


PRIVATE int breathled_sleep(void)
{
    int ret = BR_ERROR;

    /* ��ʼ���� */
    ret = breathled_hold (BREATH_LED_BREATH);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FULL_ON, ZERO_TIME);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FULL_OFF, led_attr_default.full_long_off);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FADE_ON, ZERO_TIME);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_FADE_OFF, ZERO_TIME);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    ret = set_breathled_attr(BRT_ATTR_BRIGHTNESS, led_attr_default.brightness);
    if(BR_ERROR == ret)
    {
        return ret;
    }
    
    return BR_OK;
}


PRIVATE int breathled_disable(void)
{
    int ret = BR_ERROR;

    /* �رպ����� */
    ret = breathled_hold (BREATH_LED_NONE);
    if(BR_ERROR == ret)
    {
        return ret;
    }

    return BR_OK;
}


PUBLIC int breathled_controller(breathled_state led_state)
{
    int ret = BR_ERROR;
    
    printk(KERN_DEBUG"[*Breath-Led*] %s: breathle curr state = %d.\n", __func__, breath_led_curr_state);
    printk(KERN_DEBUG"[*Breath-Led*] %s: breathle next state = %d.\n", __func__, led_state);
    
    switch( led_state )
    {
        case BREATH_LED_STATE_ENABLE:
            /* ������ʹ�� */
            led_attr_default.led_enable = BREATH_LED_ENABLE;
            /* ������ʹ��״̬�̻� */
            ret = breathled_nv_save();
            if(BR_ERROR == ret)
            {
                return ret;
            }
            
            ret = breathled_controller(breath_led_curr_state);
            if(BR_ERROR == ret)
            {
                return ret;
            }
            break;
        case BREATH_LED_STATE_DISABLE:
            /* �����ƹر� */
            led_attr_default.led_enable = BREATH_LED_DISABLE;
            /* ������ʹ��״̬�̻� */
            ret = breathled_nv_save();
            if(BR_ERROR == ret)
            {
                return ret;
            }
            
            ret = breathled_disable();
            if(BR_ERROR == ret)
            {
                return ret;
            }
            break;
        case BREATH_LED_STATE_SPARK:
            /* ����ģʽ */
            if(LED_MODE_BREATH != led_attr_default.led_mode)
            {
                /* ���������÷Ǻ���ģʽֱ�ӷ��� */
                return BR_ERROR;
            }
            
            breath_led_curr_state = BREATH_LED_STATE_SPARK;
            if(BREATH_LED_DISABLE == led_attr_default.led_enable)
            {
                /* �����ƹر�ʱֱ�ӷ��� */
                return BR_OK;
            }
            
            ret = breathled_breath();
            if(BR_ERROR == ret)
            {
                return ret;
            }
            break;
        case BREATH_LED_STATE_LIGHT:
            /* ��ʼ���� */
            breath_led_curr_state = BREATH_LED_STATE_LIGHT;
            if(BREATH_LED_DISABLE == led_attr_default.led_enable)
            {
                /* �����ƹر�ʱֱ�ӷ��� */
                return BR_OK;
            }
            
            ret = breathled_shine();
            if(BR_ERROR == ret)
            {
                return ret;
            }
            break;
        case BREATH_LED_STATE_SLEEP:
            /* ��ʼ���� */
            breath_led_curr_state = BREATH_LED_STATE_SLEEP;
            if(BREATH_LED_DISABLE == led_attr_default.led_enable)
            {
                /* �����ƹر�ʱֱ�ӷ��� */
                return BR_OK;
            }
            
            ret = breathled_sleep();
            if(BR_ERROR == ret)
            {
                return ret;
            }
            break;
        default:
            printk(KERN_ERR"[*Breath-Led*] %s: breathle state cmd is invalid.\n", __func__);
            return BR_ERROR;
            break;
    }

    return BR_OK;
}

EXPORT_SYMBOL (breathled_controller);

PRIVATE int __init breathled_init(void)
{
    int ret = 0;
    
    ret = breathled_nv_init();

    return ret;
}

PRIVATE void __exit breathled_exit(void)
{
    int ret = 0;
    
    ret = breathled_controller (BREATH_LED_STATE_DISABLE);
    if(BR_ERROR == ret)
    {
        printk(KERN_ERR"[*Breath-Led*] %s: breathled_controller failed.\n", __func__);
    }
}


#if (FEATURE_ON == MBB_LED_UNIFORM)
int dr_led_name2dr(struct led_classdev *led_cdev)
{
    int i;
    int led_name_len = 0;
    int dr_name_len = 0;
    int strncmp_len = 0;
    /* reject null */
    if( (NULL == led_cdev) || (NULL == led_cdev->name) )
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] arguments is NULL\n", __FUNCTION__);
        return BR_ERROR;
    }
    else
    {
        /*����name  ���Ҷ�Ӧ���Ƶ�led*/
        led_name_len = strlen(led_cdev->name);
        for (i = 0; i < DR_LED_NUMBER; i++)
        {
            if (NULL == led_dr_uniform[i].name)
            {
                return BR_ERROR;
            }

            dr_name_len = strlen(led_dr_uniform[i].name);
            strncmp_len = (dr_name_len > led_name_len)?dr_name_len:led_name_len;
            if (!strncmp(led_cdev->name , led_dr_uniform[i].name , strncmp_len) )
            {
                printk(KERN_INFO "[leds-dr] Find led named %s in led_dr_uniform!\n", led_cdev->name);
                g_dr_name = led_dr_uniform[i].dr_node;
                return BR_OK;
            }
        }
    }

    printk(KERN_INFO "[leds-dr] Do not find dr led named %s in led_dr_uniform!\n", led_cdev->name);
    return BR_ERROR;
}
#endif


int change_name(struct led_classdev *led_cdev)
{
#if (FEATURE_ON == MBB_LED_UNIFORM)
    int ret = BR_ERROR;
#endif
    /* reject null */
    if(!led_cdev || !led_cdev->name)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] arguments is NULL\n", __FUNCTION__);
        return BR_ERROR;
    }

    LED_TRACE(LED_DEBUG_LEVEL(INFO),"[%s] led name %s\n", __FUNCTION__, led_cdev->name);
#if (FEATURE_ON == MBB_LED_UNIFORM)
    ret = dr_led_name2dr(led_cdev);
    return ret;
#else
    if(!strcmp(led_cdev->name, LED_NODE_1))
    {
        g_dr_name = LED_NAME_1;
        return BR_OK;
    }
    else if(!strcmp(led_cdev->name, LED_NODE_2))
    {
        g_dr_name = LED_NAME_2;
        return BR_OK;
    }
    else if(!strcmp(led_cdev->name, LED_NODE_3))
    {
        g_dr_name = LED_NAME_3;
        return BR_OK;
    }
    else if(!strcmp(led_cdev->name, LED_NODE_4))
    {
        g_dr_name = LED_NAME_4;
        return BR_OK;
    }
    else if(!strcmp(led_cdev->name, LED_NODE_5))
    {
        g_dr_name = LED_NAME_5;
        return BR_OK;
    }
    else
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] match the led name failedn", __FUNCTION__);
        return BR_ERROR;
    }
#endif
}


PRIVATE int assemble_container_dr(const char * cmd_obj)
{   
    int len = 0;

    if(!cmd_obj)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] arguments is NULL\n", __FUNCTION__);
        return BR_ERROR;
    }
    
    /* �ÿ����� */
    (void)memset(path_container,0x0, CONTAINER_LEN);/*lint !e160 !e506*/

    /* ������� */
    len = snprintf(path_container, CONTAINER_LEN, container_format, g_dr_name, cmd_obj);
    if(len < 0)
    {
        printk(KERN_ERR"[*Breath-Led*] %s: assemble %s failed.\n", __func__, cmd_obj);
        return BR_ERROR;
    }

    return BR_OK;
}

PRIVATE int set_led_dr_attr(breathled_attr_e br_attr, unsigned long attr_value)
{
    struct file *attr_handle = NULL;
    int ret = BR_ERROR;
    int len = 0;
   
    char value_buf[ATTR_INFO_LEN];
    
    char attr_buf[ATTR_INFO_LEN];
    mm_segment_t old_fs = get_fs();
    /*lint -e160 -e506*/
    (void)memset(value_buf,0x0, sizeof(value_buf));
    (void)memset(attr_buf,0x0, sizeof(attr_buf));
    /*lint +e160 +e506*/
    switch(br_attr)
    {
        case BRT_ATTR_FULL_ON:
         
            strncpy(attr_buf, BREATH_FULL_ON, sizeof(BREATH_FULL_ON));
            break;
        case BRT_ATTR_FULL_OFF:
          
            strncpy(attr_buf, BREATH_FULL_OFF, sizeof(BREATH_FULL_OFF));
            break;
        case BRT_ATTR_FADE_ON:
          
            strncpy(attr_buf, BREATH_FADE_ON, sizeof(BREATH_FADE_ON));
            break;
        case BRT_ATTR_FADE_OFF:
            
            strncpy(attr_buf, BREATH_FADE_OFF, sizeof(BREATH_FADE_OFF));
            break;
        case BRT_ATTR_DELAY_ON:
           
            strncpy(attr_buf, BREATH_DELAY_ON, sizeof(BREATH_DELAY_ON));
            break;
        case BRT_ATTR_DELAY_OFF:
           
            strncpy(attr_buf, BREATH_DELAY_OFF, sizeof(BREATH_DELAY_OFF));
            break;
        case BRT_ATTR_BRIGHTNESS:
            
            strncpy(attr_buf, BREATH_BRIGHTNESS, sizeof(BREATH_BRIGHTNESS));
            break;
        default:
           
            printk(KERN_ERR"%s: BREATH ATTR error.\n", __func__);
            return BR_ERROR;
    }


    ret = assemble_container_dr(attr_buf);
    if(BR_ERROR == ret)
    {
        return BR_ERROR;
    }

    len = snprintf(value_buf, sizeof(value_buf), "%ld", attr_value);
    if(len < 0) 
    {
        printk(KERN_ERR"[*Breath-Led*] %s: fill value buffer failded.\n", __func__);
        set_fs(old_fs);
        return BR_ERROR;
    }

    set_fs(KERNEL_DS);

    attr_handle = filp_open(path_container, O_RDWR, S_IRWXU);
    if(IS_ERR(attr_handle))
    {
        printk(KERN_ERR"[*Breath-Led*] %s: sys_open \"%s\" failed.\n", __func__,path_container);
        set_fs(old_fs);
        return BR_ERROR;
    }

    len = attr_handle->f_op->write(attr_handle, value_buf, len, &attr_handle->f_pos);
    if(len < 0) 
    {
        printk(KERN_ERR"[*Breath-Led*] %s: sys_write \"%s\" failed.\n", __func__,path_container);
        (void)filp_close(attr_handle, NULL);
        set_fs(old_fs);
        return BR_ERROR;
    }
    
    (void)filp_close(attr_handle, NULL);
    set_fs(old_fs);
    
    return BR_OK;
}

int led_dr_trigger_hold(void)
{
    struct file *attr_handle = NULL;
    int ret = BR_ERROR;
    int len = -1;
    mm_segment_t old_fs = get_fs();

    ret = assemble_container_dr(BREATH_TRIGGER);
    if(BR_ERROR == ret)
    {
        return BR_ERROR;
    }

    set_fs(KERNEL_DS);

     attr_handle = filp_open(path_container, O_RDWR, S_IRWXU);
    if(IS_ERR(attr_handle))
    {
        printk(KERN_ERR"[*Breath-Led*] %s: sys_open \"%s\" failed.\n", __func__,path_container);
        set_fs(old_fs);
        return BR_ERROR;
    }
    len = attr_handle->f_op->write(attr_handle, BREATH_TRIGGER_BREATH, 
                                                sizeof(BREATH_TRIGGER_BREATH), &attr_handle->f_pos);           
    if(len < 0) 
    {
        printk(KERN_ERR"[*Breath-Led*] %s: sys_write \"%s\" failed.\n", __func__,path_container);
        (void)filp_close(attr_handle, NULL);
        set_fs(old_fs);
        return BR_ERROR;
    }
    
    (void)filp_close(attr_handle, NULL);
    set_fs(old_fs);
    
    return BR_OK;
}

int led_dr_breath_set(struct led_classdev *led_cdev, unsigned long *full_on, unsigned long *full_off, unsigned long *fade_on, unsigned long *fade_off)
{   
    int ret = BR_ERROR;
    int brightness = 0;
    int max_brightness = 0;

    /* argument check */
    if((!led_cdev) || (!full_on) || (!full_off) || (!fade_on) || (!fade_off))
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] arguments is NULL\n", __FUNCTION__);
        return BR_ERROR;
    }
    mutex_lock(&led_dr_mutex);
    led_cdev->breath_full_on = *full_on;
    led_cdev->breath_full_off = *full_off;
    led_cdev->breath_fade_on = *fade_on;
    led_cdev->breath_fade_off = *fade_off;
    brightness = led_cdev->brightness;
    max_brightness = led_cdev->max_brightness;
    
    ret = change_name(led_cdev);
    if(BR_ERROR == ret)
    {
        goto out;
    }
    
    g_dr_brightness[g_dr_name - 1] = -1;        /*����ֵ��λ*/
    
    ret = led_dr_trigger_hold();
    if(BR_ERROR == ret)
    {
        goto out;
    }
    /*Ӧ�ò��·���ʱ������Ǻ��뼶�ģ����ײ㶨��Ĳ�����΢�뼶�ģ����û�̬���������ʱ����Ҫת��*/
    ret = set_led_dr_attr(BRT_ATTR_FULL_ON, (led_cdev->breath_full_on)*1000);
    if(BR_ERROR == ret)
    {
        goto out;
    }
    ret = set_led_dr_attr(BRT_ATTR_FULL_OFF, (led_cdev->breath_full_off)*1000);
    if(BR_ERROR == ret)
    {
        goto out;
    }
    ret = set_led_dr_attr(BRT_ATTR_FADE_ON, (led_cdev->breath_fade_on)*1000);
    if(BR_ERROR == ret)
    {
        goto out;
    }
    ret = set_led_dr_attr(BRT_ATTR_FADE_OFF, (led_cdev->breath_fade_off)*1000);
    if(BR_ERROR == ret)
    {
        goto out;
    }
    
     /*ʱ�丳ֵ��Ͻ�����������*/
    if ((led_cdev->breath_full_on)&&(led_cdev->breath_full_off)&&(led_cdev->breath_fade_on)&&(led_cdev->breath_fade_off))
    {
        if ((0 == brightness) || (1 == brightness))
        {               
            ret = set_led_dr_attr(BRT_ATTR_BRIGHTNESS, max_brightness);
        }    
        if(BR_ERROR == ret)
        {
            goto out;
        }
    }
    
 out:
    mutex_unlock(&led_dr_mutex);
    return ret;
}


static void led_dr_work(struct work_struct *work)
{
    int ret = BR_ERROR;
    unsigned long time_local = 0;
    int brightness = 0;
    int max_brightness = 0;
    
    struct balong_led_device	*led_dat = NULL;
    struct led_classdev *led_cdev = NULL;
    
    mutex_lock(&led_dr_mutex);
    led_dat = container_of(work, struct balong_led_device, work);
    led_cdev = &(led_dat->cdev);
    brightness = led_dat->brightness;

    if(!led_cdev)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] arguments is NULL\n", __FUNCTION__);
        goto out;
    }
    max_brightness = led_cdev->max_brightness;
    ret = change_name(led_cdev);    
    if(BR_ERROR == ret)
    {
        goto out;
    }
    
    if (brightness >= LED_FULL)
    {
        brightness = LED_FULL;
    }
    if (brightness >= max_brightness)
    {
        brightness = max_brightness;
    }
      
    if(1 == brightness)
    {
        brightness = max_brightness;
    }
        
    if(g_dr_brightness[g_dr_name - 1] == brightness)    /*�ظ���������*/
    {
        goto out;
    }
    g_dr_brightness[g_dr_name - 1] = brightness;    /*����ֵ����*/

    ret = led_dr_trigger_hold();
    if(BR_ERROR == ret)
    {
        goto out;
    }
    /*���õƵ�״̬Ϊ����*/
    if (LED_OFF == brightness)
    {
        ret = set_led_dr_attr(BRT_ATTR_FULL_ON, time_local);
        if(BR_ERROR == ret)
        {
            printk(KERN_ERR"[*Breath-Led*] %s: set_led_dr_attr(BRT_ATTR_FULL_ON,time_local) failded.\n", __func__);
            goto out;
        }
        ret = set_led_dr_attr(BRT_ATTR_FULL_OFF, LED_LONG_TIME);
        if(BR_ERROR == ret)
        {
            printk(KERN_ERR"[*Breath-Led*] %s: set_led_dr_attr(BRT_ATTR_FULL_OFF, LED_LONG_TIME) failded.\n", __func__);
            goto out;
        }
    }
    /*���õƵ�״̬Ϊ����*/
    else
    {
        ret = set_led_dr_attr(BRT_ATTR_FULL_ON, LED_LONG_TIME);
        if(BR_ERROR == ret)
        {
            printk(KERN_ERR"[*Breath-Led*] %s: set_led_dr_attr(BRT_ATTR_FULL_ON, LED_LONG_TIME) failded.\n", __func__);
            goto out;
        }
        ret = set_led_dr_attr(BRT_ATTR_FULL_OFF, time_local);
        if(BR_ERROR == ret)
        {
            printk(KERN_ERR"[*Breath-Led*] %s: set_led_dr_attr(BRT_ATTR_FULL_OFF, time_local) failded.\n", __func__);
            goto out;
        }
    }
    ret = set_led_dr_attr(BRT_ATTR_FADE_ON, time_local);
    if(BR_ERROR == ret)
    {
        goto out;
    }
    ret = set_led_dr_attr(BRT_ATTR_FADE_OFF, time_local);
    if(BR_ERROR == ret)
    {
        goto out;
    }
    
    ret = set_led_dr_attr(BRT_ATTR_BRIGHTNESS, brightness);
    if(BR_ERROR == ret)
    {
        goto out;
    }

out:
    mutex_unlock(&led_dr_mutex);
}


void led_dr_brightness_set(struct led_classdev *led_cdev, enum led_brightness brightness)
{
    struct balong_led_device    *led_dat =
        container_of(led_cdev, struct balong_led_device, cdev);
    led_dat->brightness = brightness;
    queue_work(led_workqueue_brightness, &(led_dat->work));
}

enum led_brightness led_dr_brightness_get(struct led_classdev *led_cdev)
{
    if(!led_cdev)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] arguments is NULL\n", __FUNCTION__);
        return (enum led_brightness)BR_ERROR;  
    }
    
    return (enum led_brightness)led_cdev->brightness;   
}

int led_dr_led_blink_set(struct led_classdev *led_cdev, unsigned long *delay_on, unsigned long *delay_off)
{
    return BR_OK;
}


static void led_dr_adapt(struct led_platform_data *pdata)
{
    unsigned int board_id = 0xffffffff;
    int i = 0;
    int match_id = 0;
    int dr_led_number = 0;

    if(NULL == pdata)
    {
        return;
    }

    board_id = (unsigned int)bsp_version_get_boardid();    /* ��ȡӲ��ID */

    /* �²�Ʒ֧��LED��һ��ʹ��uniform_led_config������ */
    if ( support_uniform_product(board_id, &match_id) )
    {
        /* dr �Ƹ�����ʼ�� */
        pdata->num_leds = uniform_led_config[match_id].total_dr_led_number;
        for (i = 0; i < uniform_led_config[match_id].total_dr_led_number; i++)
        {
             /* �ж�uniform_led_config��dr led��name�����Ƿ�Ϊ�գ����Ϊ���򷵻� */
            if (NULL == uniform_led_config[match_id].dr_led[i].name)
            {
                printk(KERN_ERR"[*Breath-Led*] %s: invalid dr name, match_id=%d, i=%d\n", __func__, match_id, i);
                return ;
            }

            /* ����ȫ������led_dr_uniform[]��led name�ռ䲢��ʼ��Ϊ0 */
            led_dr_uniform[i].name = (char *)kzalloc(strlen(uniform_led_config[match_id].dr_led[i].name) + 1, GFP_KERNEL);
            if (NULL == led_dr_uniform[i].name)
            {
                 printk(KERN_ERR"[*Breath-Led*] %s: dr name malloc failed\n", __func__);
                 return ;
            }

            /* ����uniform_led_config��DR�Ƶ�name���õ�DR LEDȫ������led_dr_uniform[]��name�����У���������ʹ�ø�ȫ������ */
            memcpy((void *)led_dr_uniform[i].name, uniform_led_config[match_id].dr_led[i].name, strlen(uniform_led_config[match_id].dr_led[i].name));
            /* ������ȳ�ʼ�� */
            led_dr_uniform[i].max_brightness = uniform_led_config[match_id].dr_led[i].max_brightness;
            /* Ĭ�����ȳ�ʼ�����˴���������һ����Ա����ע��DR1/2��DR3/4/5�������� */
#if (FEATURE_ON == MBB_LED_UNIFORM)
            /* Ĭ�����ȳ�ʼ�����˴���������һ����Ա����ע��DR1/2��DR3/4/5�������� */
            led_dr_uniform[i].dr_led_brightness = uniform_led_config[match_id].dr_led[i].dr_led_brightness;
            led_dr_uniform[i].dr_node = uniform_led_config[match_id].dr_led[i].dr_node;
#endif
        }
    }
    else    /* ����ò�Ʒ���Ͽ��Ʒ����ʹ��led_dr�е�LED���ã��˴�Ϊ��������Ŀ */
    {
        dr_led_number = (int)(ARRAY_SIZE(led_dr));
        pdata->num_leds = dr_led_number;   /* dr �Ƹ�����ʼ�� */
        for (i = 0; i < dr_led_number; i++)
        {
            /* �ж�dr_led��name�Ƿ�Ϊ�գ����Ϊ���򷵻� */
            if (NULL == led_dr[i].name)
            {
                printk(KERN_ERR"[*Breath-Led*] %s: invalid dr name\n", __func__);
                return ;
            }

            /* ����ȫ������led_dr_uniform[]��led name�ռ䲢��ʼ��Ϊ0 */
            led_dr_uniform[i].name = (char *)kzalloc(strlen(led_dr[i].name) + 1, GFP_KERNEL);
            if (NULL == led_dr_uniform[i].name)
            {
                 printk(KERN_ERR"[*Breath-Led*] %s: dr name malloc failed\n", __func__);
                 return ;
            }

            /* �����ϲ�Ʒ��DR�Ƶ�name���õ�DR LEDȫ������led_dr_uniform[]��name�����У���������ʹ�ø�ȫ������ */
            memcpy((void *)led_dr_uniform[i].name, led_dr[i].name, strlen(led_dr[i].name));
            /* ������ȳ�ʼ�� */
            led_dr_uniform[i].max_brightness = led_dr[i].max_brightness;
#if (FEATURE_ON == MBB_LED_UNIFORM)
            /* Ĭ�����ȳ�ʼ�����˴�Ϊ�˼����ϲ�Ʒ��ֱ�ӽ��ϲ�Ʒ��Ĭ�����ȵĺ긳ֵ��dr_led_brightness */
            if (i < DR_NODE_2)
            {
                led_dr_uniform[i].dr_led_brightness = DR12_BRIGHTNESS;
            }
            else
            {
                led_dr_uniform[i].dr_led_brightness = DR345_BRIGHTNESS;
            }
#endif
        }
    }
}
    /*lint -e54 -e119 -e30 -e84 -e514 */
static int led_dr_probe(struct platform_device *dev)
{
    int ret = 0;
    unsigned int i = 0; 
    struct led_platform_data *pdata = dev->dev.platform_data;
    struct balong_led_device *led=  NULL;

    /* ����Ӳ��ID����̬����DR LED���ã�ʵ��LED��һ */
    led_dr_adapt(pdata);

#if defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5573S_156) \
    || defined(BSP_CONFIG_BOARD_E5573S_856) || defined(BSP_CONFIG_BOARD_E5573S_853) \
    || defined(BSP_CONFIG_BOARD_E5573S_607) || defined(BSP_CONFIG_BOARD_E8378WS_210)
    unsigned int id = 0xffffffff;
    id = (unsigned int)bsp_version_get_boardid();
#endif

    led = (struct balong_led_device *)kzalloc(sizeof(struct balong_led_device) * pdata->num_leds , GFP_KERNEL);
    if(!led)
    {
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] get buffer failed\n", __FUNCTION__);
        goto ERRO;
    }

    for(i = 0; i < pdata->num_leds; i++)
    {
#if defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5573S_156) \
    || defined(BSP_CONFIG_BOARD_E5573S_856) || defined(BSP_CONFIG_BOARD_E5573S_853) \
    || defined(BSP_CONFIG_BOARD_E5573S_607)
        /* E5573Bs-320��R216����msg_led:green�ƣ���ͨE5û�д˵ƣ�
           ����ͨ��E5�ڴ����ڵ��ʱ����Ҫ����msg_led:green�Ĵ���*/
        if((HW_VER_PRODUCT_E5573Bs_320  != id)&&(HW_VER_PRODUCT_R216 != id)&&(HW_VER_PRODUCT_R216h != id))
        {
            if( 2 == i )//led_dr�б��е�3��ledΪmsg_led:green��
            {
                continue;
            }
        }
#endif
        led[i].pdata =(struct balong_led_platdata*)kzalloc(sizeof(struct balong_led_platdata), GFP_KERNEL);
        if(!led[i].pdata)
        {
            LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] get pdata buffer failed\n", __FUNCTION__);
            goto ERRO;
        }

        led[i].cdev.name = pdata->leds[i].name;
        led[i].cdev.max_brightness = pdata->leds[i].max_brightness;
        led[i].pdata->led_breath_set      = led_dr_breath_set;
        led[i].cdev.brightness_set        = led_dr_brightness_set;
        led[i].cdev.brightness_get        = led_dr_brightness_get;
        led[i].cdev.blink_set             = led_dr_led_blink_set;
              
        led[i].cdev.default_trigger       = pdata->leds[i].default_trigger;
        led[i].cdev.flags                 = 0;
        
        INIT_WORK(&(led[i].work), led_dr_work);

        ret = led_classdev_register(&dev->dev, &(led[i].cdev));
        if(ret)
        {
            LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s]led%d sysfs register failed\n", __FUNCTION__,i + 1);
        }
        
    }

    platform_set_drvdata(dev, led);/*lint !e534*/
    return ret;
    
ERRO:
    for(i = 0; i < pdata->num_leds; i++)
    {
        if(!led)
        {
            continue;
        }
        if(led[i].pdata)
        {
            kfree(led[i].pdata);
            led[i].pdata = NULL;
        }
    }
    if(led)
    {
        kfree(led);
        led = NULL;
    }
    LED_TRACE(LED_DEBUG_LEVEL(ALWAYS),"LED init failed\n");
    return BR_ERROR; 
}

#if defined(BSP_CONFIG_BOARD_401HW) || defined(BSP_CONFIG_BOARD_506HW)
#define BAT_LED_RED     3                 /* ��غ�ƶ�Ӧ��balong drֵ*/
#define BAT_LED_GREEN     4               /* ����̵ƶ�Ӧ��balong drֵ*/

void bat_yellow_led_set(int flag)
{
    unsigned long flags = 0;
    local_irq_save(flags);     
    if (0 == flag)     /* Ϩ���ػƵ���˸ */
    {
        dr_bat_led_switch( BAT_LED_RED , 0); 
        dr_bat_led_switch( BAT_LED_GREEN , 0);
    }
    else if (1 == flag) /*ʹ�ܵ�ػƵ���˸ */
    {
        dr_bat_led_switch( BAT_LED_RED , 1);
        dr_bat_led_switch( BAT_LED_GREEN , 1);
    }
    else
    {
         printk(KERN_ERR "undefined flag = %d", flag);
    }
    local_irq_restore(flags);
}
EXPORT_SYMBOL(bat_yellow_led_set);
#endif 
static int led_dr_remove(struct platform_device *dev)
{

    unsigned int i;
    struct balong_led_device *led = platform_get_drvdata(dev);
    if(!led)
    {
        return BR_ERROR;
    }
    
    if(&led->cdev)
    {
        led_classdev_unregister(&led->cdev);
    }
    for(i = 0; i < DR_LED_NUMBER; i++)
    {
        if(!led[i].pdata)
        {
            continue;
        }
        led_classdev_unregister(&(led[i].cdev));
        if(led[i].pdata)
        {
            kfree(led[i].pdata);
            led[i].pdata = NULL;
        }
    }

    kfree(led);
    led = NULL;

    return BR_OK;
}
    /*lint +e54 +e119 +e30 +e84 +e514 */



static struct platform_driver led_dr_drv = {
    .probe =led_dr_probe,
    .remove = led_dr_remove,
    .driver = {  
        .name  = "led_dr",  
        .owner = THIS_MODULE, 
        .bus        = &platform_bus_type,
        .pm    = NULL,
    },  
};

static int __init led_dr_init(void)
{
    int ret = 0;
#if(FEATURE_ON == MBB_LED_GPIO)
    /* �������δʹ�ñ������� */
    UNUSED_PARAMETER(gpio_exp_leds_config);
#endif
    ret = platform_device_register(&led_dr_dev);
    if (ret < 0)
    {
        printk(KERN_ERR "\r\n [led_dr_init] platform_device_register the led_dr failed.\r\n");
        return ret;
    }

    ret = platform_driver_register(&led_dr_drv);
    if (0 > ret)
    {
        platform_device_unregister(&led_dr_dev);
        printk(KERN_ERR "\r\n [led_dr_init] platform_device_unregister the led_dr failed.\r\n");
        return ret;
    }
    return ret;
}

static void __exit led_dr_exit(void)
{
    platform_driver_unregister(&led_dr_drv);

    platform_device_unregister(&led_dr_dev);
}

/*lint -e629*/
module_init(led_dr_init);
module_exit(led_dr_exit);
late_initcall(breathled_init);
module_exit(breathled_exit);
/*lint +e629*/
MODULE_AUTHOR("MBB.Huawei Device");
MODULE_DESCRIPTION("Breath Led Driver");
MODULE_LICENSE("GPL");
