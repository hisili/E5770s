




/*----------------------------------------------*
 * ����ͷ�ļ�                                   *
 *----------------------------------------------*/
#include "chg_config.h"
#if ( FEATURE_ON == MBB_MLOG )
#include <linux/mlog_lib.h>
#endif
#include "bsp_coul.h"
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
#include <bsp_hkadc.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/input/key_balong.h>
#include <linux/workqueue.h>
#include <linux/sched.h>
#include "../../usb/mbb_usb_unitary/usb_hotplug.h"
#endif

#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
#include <product_nv_id.h>
#endif
#ifndef CHG_STUB
#include <linux/usb/usb_interface_external.h>
#else
enum chg_current
{
    CHG_CURRENT_HS =0,    /*usb2.0 for 500mA*/
    CHG_CURRENT_SS ,        /*usb3.0 for 900mA */
    CHG_CURRENT_NO,        /*invalid usb for no current*/
};
int usb_speed_work_mode(void)
{
    return 0;
}

#define USB_OTG_CONNECT_DP_DM               (0x0001)
#define USB_OTG_DISCONNECT_DP_DM            (0x0002)  /*ֱ������������HS_ID*/
#define USB_OTG_ID_PULL_OUT                 (0x0003)  /*ֱ������������HS_ID*/
#define USB_OTG_DISABLE_ID_IRQ              (0x0004)
#define USB_OTG_ENABLE_ID_IRQ               (0x0005)
#endif
#if defined(BSP_CONFIG_BOARD_E5771H_937)
#define  HW_VER_DISTINGUISH      950
#define  RSIISTANCE_CENT_COUNT   7
#endif
/*USB�±�*/ 
#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
#define TEMP_INITIAL_VALUE                  (0xFFFF)   /*�¶ȳ�ʼ��ֵ*/
#define USB_TEMP_DETECT_COUNT               (4)        /*USB�¶�����������+1*/
#endif
/*----------------------------------------------*
 * �ⲿ����˵��                                 *
 *----------------------------------------------*/
extern struct chargeIC_chip *g_chip;
extern struct softtimer_list g_chg_sleep_timer;
extern int32_t is_5577cs_falg;    /*FALSE:����5577Cs-321;TRUE:��5577Cs-321*/
uint32_t  mbb_fastonoff_chg_flag = false;

/*----------------------------------------------*
 * �ⲿ����ԭ��˵��                             *
 *----------------------------------------------*/
extern int battery_monitor_blocking_notifier_call_chain(unsigned long val, unsigned long v);

struct chg_hardware_data *g_chg_hardware_data = NULL;

struct chg_batt_data *g_chg_batt_data = NULL;

int32_t is_bat_3000 = FALSE;    /*FALSE:����5577S-321��3000mA���;TRUE:��5577S-321��3000mA���*/
int32_t is_vbus_unkonwn = FALSE;  /*FALSE:���IC��STAT�Ĵ���VBUS��Ϊunkonwn;TRUE:���IC��STAT�Ĵ���VBUSΪunkonwn*/
#if defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5573S_156) \
    || defined(BSP_CONFIG_BOARD_E5573S_856) || defined(BSP_CONFIG_BOARD_E5573S_853) \
    || defined(BSP_CONFIG_BOARD_E5573S_607) || defined(BSP_CONFIG_BOARD_E5577CS_603) \
    || defined(BSP_CONFIG_BOARD_E5575S_320)
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3450,3450,4220,4240,4100,4050,3550,3550,3610,3670,3770,4150,4100},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_xingwangda = {
        .id_voltage_min = 1937,/*batt id volt*/
        .id_voltage_max = 2187,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3638,3638,3721,3805,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA,
};
static struct chg_batt_data chg_batt_data_feimaotui = {
        .id_voltage_min = 887,/*batt id volt*/
        .id_voltage_max = 1137,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3620,3620,3708,3779,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_FEIMAOTUI,
};
static struct chg_batt_data chg_batt_data_lishen = {
        .id_voltage_min = 102,/*batt id volt*/
        .id_voltage_max = 352,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3621,3621,3709,3798,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_LISHEN,
};

static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_xingwangda,
    &chg_batt_data_feimaotui,
    &chg_batt_data_lishen,

};


#elif defined(BSP_CONFIG_BOARD_E5573CS)|| defined(BSP_CONFIG_BOARD_E5573BS) \
    || defined(BSP_CONFIG_BOARD_R218h)
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3450,3450,4220,4240,4100,4050,3550,3550,3610,3670,3770,4150,4100},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_xingwangda = {
        .id_voltage_min = 1937,/*batt id volt*/
        .id_voltage_max = 2187,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4050,3638,3638,3721,3805,3970,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA,
};
static struct chg_batt_data chg_batt_data_feimaotui = {
        .id_voltage_min = 1542,/*batt id volt*/
        .id_voltage_max = 1792,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4050,3620,3620,3708,3779,3970,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_FEIMAOTUI,
};
static struct chg_batt_data chg_batt_data_lishen = {
        .id_voltage_min = 102,/*batt id volt*/
        .id_voltage_max = 352,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4050,3621,3621,3709,3798,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_LISHEN,
};

static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_xingwangda,
    &chg_batt_data_feimaotui,
    &chg_batt_data_lishen,

};

#elif defined(BSP_CONFIG_BOARD_E5573CS_933)
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3450,3450,4220,4240,4100,4050,3550,3550,3610,3670,3770,4150,4100},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_xingwangda = {
        .id_voltage_min = 1937,/*batt id volt*/
        .id_voltage_max = 2187,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4050,3638,3638,3721,3805,3970,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA,
};
static struct chg_batt_data chg_batt_data_feimaotui = {
        .id_voltage_min = 1542,/*batt id volt*/
        .id_voltage_max = 1792,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4050,3620,3620,3708,3779,3970,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_FEIMAOTUI,
};
static struct chg_batt_data chg_batt_data_lishen = {
        .id_voltage_min = 102,/*batt id volt*/
        .id_voltage_max = 352,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4050,3621,3621,3709,3798,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_LISHEN,
};

static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_xingwangda,
    &chg_batt_data_feimaotui,
    &chg_batt_data_lishen,

};

/**E5577S-603 ʹ��3000����*/
#elif defined(BSP_CONFIG_BOARD_E5577S_603)
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3450,3450,4220,4240,4100,4050,3550,3550,3610,3670,3770,4150,4100},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_xingwangda = {
        .id_voltage_min = 1185,  /*batt id volt*/
        .id_voltage_max = 1435,  /*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3606,3606,3669,3752,3836,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA,
};
static struct chg_batt_data chg_batt_data_feimaotui = {
        .id_voltage_min = 1542, /*batt id volt*/
        .id_voltage_max = 1792, /*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3629,3629,3674,3746,3826,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_FEIMAOTUI,
};
static struct chg_batt_data chg_batt_data_lishen = {
        .id_voltage_min = 577, /*batt id volt*/
        .id_voltage_max = 827, /*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3600,3600,3652,3740,3829,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_LISHEN,
};
static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_xingwangda,
    &chg_batt_data_feimaotui,
    &chg_batt_data_lishen,

};
#elif defined(BSP_CONFIG_BOARD_E5577S_321)|| defined(BSP_CONFIG_BOARD_E5577S_324)\
   || defined(BSP_CONFIG_BOARD_E5577BS_937)
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3450,3450,4220,4240,4100,4050,3550,3550,3610,3670,3770,4150,4100},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_xingwangda = {
        .id_voltage_min = 1937,/*batt id volt*/
        .id_voltage_max = 2187,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3638,3638,3721,3805,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA,
};
static struct chg_batt_data chg_batt_data_feimaotui = {
        .id_voltage_min = 887,/*batt id volt*/
        .id_voltage_max = 1137,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3620,3620,3708,3779,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_FEIMAOTUI,
};
static struct chg_batt_data chg_batt_data_lishen = {
        .id_voltage_min = 102,/*batt id volt*/
        .id_voltage_max = 352,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3621,3621,3709,3798,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_LISHEN,
};
static struct chg_batt_data chg_batt_data_xingwangda_3000 = {
        .id_voltage_min = 1185,  /*batt id volt*/
        .id_voltage_max = 1435,  /*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3606,3606,3669,3752,3836,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA_3000,
};
static struct chg_batt_data chg_batt_data_feimaotui_3000 = {
        .id_voltage_min = 1542, /*batt id volt*/
        .id_voltage_max = 1792, /*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3629,3629,3674,3746,3826,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_FEIMAOTUI_3000,
};
static struct chg_batt_data chg_batt_data_lishen_3000 = {
        .id_voltage_min = 577, /*batt id volt*/
        .id_voltage_max = 827, /*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3600,3600,3652,3740,3829,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_LISHEN_3000,
};
static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_xingwangda,
    &chg_batt_data_feimaotui,
    &chg_batt_data_lishen,
    &chg_batt_data_xingwangda_3000,
    &chg_batt_data_feimaotui_3000,
    &chg_batt_data_lishen_3000,

};
#elif defined(BSP_CONFIG_BOARD_E5577S_932)
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3450,3450,4220,4240,4100,4050,3550,3550,3610,3670,3770,4150,4100},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_xingwangda_3000 = {
        .id_voltage_min = 1185, // 1937,/*batt id volt*/
        .id_voltage_max = 1435, // 2187,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3638,3638,3721,3805,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA_3000,
};
static struct chg_batt_data chg_batt_data_feimaotui_3000 = {
        .id_voltage_min = 1542, // 887,/*batt id volt*/
        .id_voltage_max = 1792, // 1137,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3620,3620,3708,3779,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_FEIMAOTUI_3000,
};
static struct chg_batt_data chg_batt_data_lishen_3000 = {
        .id_voltage_min = 577, // 102,/*batt id volt*/
        .id_voltage_max = 827, // 352,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3621,3621,3709,3798,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_LISHEN_3000,
};

static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_xingwangda_3000,
    &chg_batt_data_feimaotui_3000,
    &chg_batt_data_lishen_3000,

};
#elif defined(BSP_CONFIG_BOARD_E5_E5578) 
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3450,3450,4220,4240,4100,4050,3550,3550,3610,3670,3770,4150,4100},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_xingwangda = {
        .id_voltage_min = 1000,/*batt id volt*/
        .id_voltage_max = 1200,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4060,3655,3655,3745,3815,4060,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA,
};
static struct chg_batt_data chg_batt_data_feimaotui = {
        .id_voltage_min = 300,/*batt id volt*/
        .id_voltage_max = 500,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4050,3655,3655,3740,3815,4050,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_FEIMAOTUI,
};

static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_xingwangda,
    &chg_batt_data_feimaotui,

};
#elif defined(BSP_CONFIG_BOARD_E5575S_210)
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3754,3754,3805,4030,4120,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_lishen = {
        .id_voltage_min = 102,/*batt id volt*/
        .id_voltage_max = 352,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3754,3754,3805,4030,4120,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_LISHEN,
};
static struct chg_batt_data chg_batt_data_xingwangda = {
        .id_voltage_min = 1937,/*batt id volt*/
        .id_voltage_max = 2187,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3754,3754,3805,4030,4120,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA,
};
static struct chg_batt_data chg_batt_data_feimaotui = {
        .id_voltage_min = 887,/*batt id volt*/
        .id_voltage_max = 1137,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3754,3754,3805,4030,4120,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_FEIMAOTUI,
};
static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_lishen,
    &chg_batt_data_xingwangda,
    &chg_batt_data_feimaotui,
};
#elif defined(BSP_CONFIG_BOARD_401HW) || defined(BSP_CONFIG_BOARD_506HW) \
   || defined(BSP_CONFIG_BOARD_506HW_2)
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3450,3450,4220,4240,4100,4050,3550,3550,3610,3670,3770,4150,4100},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_xingwangda = {
        .id_voltage_min = 1937,/*batt id volt*/
        .id_voltage_max = 2187,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4150,4030,3630,3630,3720,3800,4030,4250,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA,
};
static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_xingwangda,
};
#elif defined(BSP_CONFIG_BOARD_607HW)
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3450,3450,4220,4240,4100,4000,3550,3550,3610,3670,3770,4150,4100},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_xingwangda = {
        .id_voltage_min = 1937,/*batt id volt*/
        .id_voltage_max = 2187,/*batt id volt*/
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4250,4000,3638,3638,3721,3805,3970,4280,4200},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA,
};
static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_xingwangda,
};
#elif defined(BSP_CONFIG_BOARD_E5771S_852) 
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3300,3100,4220,4240,4100,4050,3336,3336,3500,3650,3900,4200,4050},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_xingwangda = {
        .id_voltage_min = 1000,/*batt id volt*/
        .id_voltage_max = 1200,/*batt id volt*/
        .chg_batt_volt_paras        = {3300,3100,4220,4240,4100,4050,3336,3336,3500,3650,3900,4200,4050},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA,
};
static struct chg_batt_data chg_batt_data_feimaotui = {
        .id_voltage_min = 300,/*batt id volt*/
        .id_voltage_max = 500,/*batt id volt*/
        .chg_batt_volt_paras        = {3300,3100,4220,4240,4100,4050,3336,3336,3500,3650,3900,4200,4050},/*batt data*/
        .batt_id                    = CHG_BATT_ID_FEIMAOTUI,
};
static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_xingwangda,
    &chg_batt_data_feimaotui,
};
#elif defined(BSP_CONFIG_BOARD_E5771H_937) /* E5771h-937�޼ٹػ������ػ�������E5771s-852��һ�� */
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3300,3300,4220,4240,4100,4050,3336,3336,3500,3650,3900,4200,4050},/*batt data*/
        .batt_id                    = CHG_BATT_ID_DEF,
};
static struct chg_batt_data chg_batt_data_xingwangda = {
        .id_voltage_min = 1000,/*batt id volt*/
        .id_voltage_max = 1200,/*batt id volt*/
        .chg_batt_volt_paras        = {3300,3300,4220,4240,4100,4050,3336,3336,3500,3650,3900,4200,4050},/*batt data*/
        .batt_id                    = CHG_BATT_ID_XINGWANGDA,
};
static struct chg_batt_data chg_batt_data_feimaotui = {
        .id_voltage_min = 300,/*batt id volt*/
        .id_voltage_max = 500,/*batt id volt*/
        .chg_batt_volt_paras        = {3300,3300,4220,4240,4100,4050,3336,3336,3500,3650,3900,4200,4050},/*batt data*/
        .batt_id                    = CHG_BATT_ID_FEIMAOTUI,
};
static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,
    &chg_batt_data_xingwangda,
    &chg_batt_data_feimaotui,
};
#else
static struct chg_batt_data chg_batt_data_default = {
        .chg_batt_volt_paras        = {3450,3450,4370,4390,4144,4100,3559,3559,3620,3710,3860,0,0},/*batt data*/
};

static struct chg_batt_data *chg_batt_data_array[] = {
    &chg_batt_data_default,

};
#endif

#define BATTERY_DATA_ARRY_SIZE sizeof(chg_batt_data_array) / sizeof(chg_batt_data_array[0])

#if defined(BSP_CONFIG_BOARD_E5_E5578)
#define CALI_VLOT_FEIMAOTUI     (20)
#define CALI_VLOT_XINGWANGDA    (5)
#endif
#if defined(BSP_CONFIG_BOARD_E5573S_856) || defined(BSP_CONFIG_BOARD_E5573S_853) \
    || defined(BSP_CONFIG_BOARD_E5573S_607) || defined(BSP_CONFIG_BOARD_E5573CS) \
    || defined(BSP_CONFIG_BOARD_E5573BS) || defined(BSP_CONFIG_BOARD_E5573CS_933)\
    || defined(BSP_CONFIG_BOARD_607HW) || defined(BSP_CONFIG_BOARD_E5577BS_937) \
    || defined(BSP_CONFIG_BOARD_R218h)
#define CALI_VLOT_LISHEN        (50)
#define CALI_VLOT_FEIMAOTUI     (20)
#define CALI_VLOT_XINGWANGDA    (5)
#endif
/*----------------------------------------------*
 * �������Ͷ���˵��                             *
 *----------------------------------------------*/
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
#define DEV_OTG_AB            0xBB
#define NUM_OF_LIMIT          (30)
#define BATT_VOLTAGE_3600     (3600)
#define BATT_VOLTAGE_3500     (3500)
#define BATT_VOLTAGE_3350     (3350)
#define BATT_VOLTAGE_3300     (3300)
#define BATT_VOLTAGE_3100     (3100)
#define BATT_VOLTAGE_3000     (3000)
#define BATT_VOLTAGE_2940     (2940)
#define DELAY_TIME_OF_DEBOUNCE (200)
#define DELAY_TIME_20MS        (20)
#if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
#define USB_SWITCH_APORT_LEVEL      (1)
#define USB_SWITCH_MPORT_LEVEL      (0)
#else
#define USB_SWITCH_APORT_LEVEL      (0)
#define USB_SWITCH_MPORT_LEVEL      (1)
#endif
int ext_dev_id = DEV_OTG_AB;
struct work_struct extchg_plug_in_work;//�����빤������
struct work_struct extchg_plug_out_work;//���γ���������
#endif

#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
#define BATTERY_SN (32)
typedef struct
{
    unsigned char  battery_sn[BATTERY_SN];
    unsigned int  coul_firmware_update_status;
}nv_huawei_coul_firmware_update_info;

#define BATT_CURRENT_I_3000            (-3000)
#define BATT_CURRENT_I_2500            (-2500)
#define BATT_CURRENT_I_1500            (-1500)
#endif

/*----------------------------------------------*
 * �ڲ�����ԭ��˵��                             *
 *----------------------------------------------*/

/*0:-Charge Transition State TRIO function.*/
static void chg_transit_state_entry_func(void);
static void chg_transit_state_period_func(void);
static void chg_transit_state_exit_func(void);

/*1:-Fast Charge State TRIO function.*/
static void chg_fastchg_state_entry_func(void);
static void chg_fastchg_state_period_func(void);
static void chg_fastchg_state_exit_func(void);

/*2:-Battery Maintenance State TRIO function.*/
static void chg_maint_state_entry_func(void);
static void chg_maint_state_period_func(void);
static void chg_maint_state_exit_func(void);

/*3:-Invalid Charge Temperature State TRIO function.*/
static void chg_invalid_chg_temp_state_entry_func(void);
static void chg_invalid_chg_temp_state_period_func(void);
static void chg_invalid_chg_temp_state_exit_func(void);

/*4:-Battery Only State TRIO function.*/
static void chg_batt_only_state_entry_func(void);
static void chg_batt_only_state_period_func(void);
static void chg_batt_only_state_exit_func(void);


//static void chg_set_hardware_parameter(const chg_hw_param_t* ptr_hw_param);

static void chg_stm_set_cur_state(chg_stm_state_type new_state);


#if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
/*5:-Warmchg State TRIO function.*/
static void chg_warmchg_state_entry_func(void);
static void chg_warmchg_state_period_func(void);
static void chg_warmchg_state_exit_func(void);
#endif /* MBB_CHG_WARM_CHARGE */

void chg_sleep_batt_check_timer(struct work_struct *work);
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
int32_t chg_batt_temp_revise(int32_t batt_temp);
#endif
/*----------------------------------------------*
 * ȫ�ֱ���                                     *
 *----------------------------------------------*/
static uint32_t g_real_factory_mode; //�Ƿ񹤳�ģʽ
static boolean chg_batt_high_temp_58_flag = FALSE; //����58�ȱ�־
static boolean chg_batt_low_battery_flag = FALSE;  //�͵��־
static boolean chg_batt_condition_error_flag = FALSE;

static boolean chg_limit_supply_current_flag = FALSE; //�±�������ʶ

#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
static int32_t battery_current = 0;
static int32_t battery_current_prev = 0;
int32_t tbatt_supply_volt_threshold = 0;
int32_t tbatt_dischg_volt_threshold = 0;
int32_t tbatt_supply_stop_threshold = 0;
int32_t tbatt_dischg_stop_threshold = 0;
#endif

#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
static int32_t count_for_short_det = 0;
static int32_t poll_round_for_det = 0;
static boolean extchg_short_flag = FALSE;
int32_t extchg_limit_1a_capacity = 0;
int32_t extchg_limit_500ma_capacity = 0;
int32_t extchg_stop_threshold_powon = 0;
int32_t extchg_stop_threshold_powdown = 0;
int32_t extchg_recharge_threshold = 0;
int32_t battery_voltage = 0xFFFF;
int32_t battery_temperature = 0;
boolean g_extchg_shutoff_flag = FALSE;
static boolean usb_set_direction_flag = FALSE;
#if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
static EXTCHG_ILIM ext_chg_status_old = RE_ILIM_NA;
static EXTCHG_ILIM ext_chg_status_new = RE_ILIM_STOP;
static EXTCHG_ILIM ext_chg_status_temp = RE_ILIM_NA;
#else
static EXTCHG_ILIM ext_chg_status_old = RE_ILIM_2A;
static EXTCHG_ILIM ext_chg_status_new = RE_ILIM_2A;
static EXTCHG_ILIM ext_chg_status_temp = RE_ILIM_2A;
#endif
static boolean usb_err_flag = FALSE;
#endif

/*��糬ʱ��־λ*/
static boolean chg_time_expired_flag = FALSE;

#if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
uint32_t up_over_temp_shutoff_falg = FALSE;
uint32_t low_over_temp_shutoff_falg = FALSE;
#endif

#if (FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT)
/*��ر�����ʶ*/
static boolean chg_battery_protect_flag = FALSE;
/*���¹�ѹ������ʶ*/
static boolean g_chg_over_temp_volt_protect_flag = FALSE;
/*����ͣ���Դ��ʱ����λ״̬��ʶ*/
static boolean g_chg_longtime_nocharge_protect_flag = FALSE;
/*������� ����ͣ���ҳ������ʱ����λ״̬ǰ���¸�������*/
static unsigned int g_batt_normal_temp_recherge_threshold = 0;
/*������ͣ�����ͣ��������ʱ����λ�����¸�������Ϊ4.0V��־*/
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
static boolean g_chg_batt_expand_change_normal_rechg_flag = FALSE;
#endif
#endif

/*��ŵ����NV*/
CHG_BATTERY_OVER_TEMP_PROTECT_NV   g_chgBattOverTempPeotect;  //NV50016
CHG_BATTERY_LOW_TEMP_PROTECT_NV    g_chgBattLowTempPeotect;   //NV52005
CHG_SHUTOFF_TEMP_PROTECT_NV_TYPE   g_chgShutOffTempProtect;   //NV50385
CHG_SHUTOFF_VOLT_PROTECT_NV_TYPE   g_chgBattVoltProtect;      //NV50386
POWERUP_MODE_TYPE                  g_real_powerup_mode_value; //NV50364

/***************************begin NV50016 ���ݺ궨�� ************************/
/*SHUTOFF ���¹ػ�ʹ�ܿ���*/
#define SHUTOFF_OVER_TEMP_PROTECT_ENABLE g_chgBattOverTempPeotect.ulIsEnable
/*SHUTOFF ���¹ػ��¶�����*/
#define SHUTOFF_OVER_TEMP_SHUTOFF_THRESHOLD g_chgBattOverTempPeotect.lCloseAdcThreshold
/*SHUTOFF ���¹ػ��¶�����*/
#define SHUTOFF_OVER_TEMP_SHUTOFF_CHECK_TIMES g_chgBattOverTempPeotect.ulTempOverCount
/***************************end   NV50016 ���ݺ궨�� ************************/

/***************************begin NV52005 ���ݺ궨�� ************************/
/*SHUTOFF ���¹ػ�ʹ�ܿ���*/
#define SHUTOFF_LOW_TEMP_PROTECT_ENABLE g_chgBattLowTempPeotect.ulIsEnable
/*SHUTOFF ���¹ػ��¶�����*/
#define SHUTOFF_LOW_TEMP_SHUTOFF_THRESHOLD g_chgBattLowTempPeotect.lCloseAdcThreshold
/*SHUTOFF ���¹ػ��¶�����*/
#define SHUTOFF_LOW_TEMP_SHUTOFF_CHECK_TIMES g_chgBattLowTempPeotect.ulTempLowCount
/***************************end  NV52005 ���ݺ궨�� ************************/


/************************************begin NV50385 ���ݺ궨�� *******************************/
/*CHG ����±���ʹ�ܿ���*/
#define CHG_TEMP_PROTECT_ENABLE g_chgShutOffTempProtect.ulChargeIsEnable
/*CHG ������/���±�������*/
#define CHG_OVER_TEMP_STOP_THRESHOLD g_chgShutOffTempProtect.overTempchgStopThreshold
#define CHG_LOW_TEMP_STOP_THRESHOLD g_chgShutOffTempProtect.lowTempChgStopThreshold
/*CHG ������/���»ָ��¶�����*/
#define CHG_OVER_TEMP_RESUME_THRESHOLD g_chgShutOffTempProtect.overTempChgResumeThreshold
#define CHG_LOW_TEMP_RESUME_THRESHOLD g_chgShutOffTempProtect.lowTempChgResumeThreshold
/*CHG ���ͣ����ѯ����*/
#define CHG_TEMP_PROTECT_CHECK_TIMES g_chgShutOffTempProtect.chgTempProtectCheckTimes
/*CHG ��縴����ѯ����*/
#define CHG_TEMP_RESUME_CHECK_TIMES g_chgShutOffTempProtect.chgTempResumeCheckTimes
#if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
/*������³�����¶�����*/
#define CHG_WARM_CHARGE_ENTER_THRESHOLD g_chgShutOffTempProtect.subTempChgLimitCurrentThreshold
/*�ɸ��³��ָ������³�����¶�����*/
#define CHG_WARM_CHARGE_EXIT_THRESHOLD g_chgShutOffTempProtect.exitWarmChgToNormalChgThreshold
#endif /* HUAWEI_CHG_WARM_CHARGE */
/**********************************end NV50385 ���ݺ궨�� *******************************/


/************************************begin NV50386 ���ݺ궨�� *******************************/
/*������ѹ����*/
#define BATT_VOLT_POWER_ON_THR g_chgBattVoltProtect.battVoltPowerOnThreshold
/*�ػ���ѹ����*/
#define BATT_VOLT_POWER_OFF_THR g_chgBattVoltProtect.battVoltPowerOffThreshold
/*����ѹ��������(ƽ��ֵ)*/
#define BATT_CHG_OVER_VOLT_PROTECT_THR g_chgBattVoltProtect.battOverVoltProtectThreshold
/*����ѹ��������(���βɼ�ֵ)*/
#define BATT_CHG_OVER_VOLT_PROTECT_ONE_THR g_chgBattVoltProtect.battOverVoltProtectOneThreshold
/*���ָ���ͣ�������ͣ����ж�����*/
#define BATT_CHG_TEMP_MAINT_THR g_chgBattVoltProtect.battChgTempMaintThreshold
/*�����θ�������*/
#define BATT_HIGH_TEMP_RECHARGE_THR g_chgBattVoltProtect.battChgRechargeThreshold

/*�͵���������*/
#define BATT_VOLT_LEVELLOW_MAX g_chgBattVoltProtect.VbatLevelLow_MAX
/*0���ѹ��������*/
#define BATT_VOLT_LEVEL0_MAX g_chgBattVoltProtect.VbatLevel0_MAX
/*1���ѹ��������*/
#define BATT_VOLT_LEVEL1_MAX g_chgBattVoltProtect.VbatLevel1_MAX
/*2���ѹ��������*/
#define BATT_VOLT_LEVEL2_MAX g_chgBattVoltProtect.VbatLevel2_MAX
/*3���ѹ�������� */
#define BATT_VOLT_LEVEL3_MAX g_chgBattVoltProtect.VbatLevel3_MAX
/*��ʼ�ж��Ƿ���������ѹ����*/
#define BATT_CHG_FIRST_MAINT_THR g_chgBattVoltProtect.battChgFirstMaintThreshold
/*���¶��θ�������*/
#define BATT_NORMAL_TEMP_RECHARGE_THR g_chgBattVoltProtect.battNormalTempChgRechargeThreshold
/************************************begin NV50386 ���ݺ궨�� *******************************/
/* ��ǰ�Ƿ�Ϊ����ģʽ: true ---����ģʽ ; false ---�ǹ���ģʽ**/
static boolean chg_current_ftm_mode = FALSE;
/*��¼����±�����־,��ʼ��Ϊ�¶�����**/
static uint32_t chg_temp_protect_flag = FALSE;

static uint32_t fact_release_flag = FALSE;

/*��¼����¶�״̬*/
TEMP_EVENT chg_batt_temp_state = TEMP_BATT_NORMAL;

static uint32_t chg_print_flag = FALSE;
static uint32_t coul_print_flag = FALSE;

/*��¼ʵ�ʵĳ��״̬��Ϣ**/
#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
CHG_PROCESS_INFO chg_real_info = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0, 0, BATT_LEVEL_0, 0,0xFFFF, 0xFFFF};
#else
CHG_PROCESS_INFO chg_real_info = {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0, 0, BATT_LEVEL_0, 0,0xFFFF};
#endif
/*��¼USB�˿��¶ȱ�����Ϣ*/
#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
static USB_TEMP_PROTECT_INFO chg_usb_temp_info = {TEMP_INITIAL_VALUE, FALSE, FALSE};
#endif

static chg_stm_type chg_stm_state_machine[CHG_STM_MAX_ST + 1] =
{
    /* 0 Transition State, which is also the default after system boot-up.*/
    {
        (chg_stm_func_type)chg_transit_state_entry_func,
        (chg_stm_func_type)chg_transit_state_period_func,
        (chg_stm_func_type)chg_transit_state_exit_func,
    },

    /* 1 Fast Charge State, battery is charged during this state.*/
    {
        (chg_stm_func_type)chg_fastchg_state_entry_func,
        (chg_stm_func_type)chg_fastchg_state_period_func,
        (chg_stm_func_type)chg_fastchg_state_exit_func,
    },

    /* 2 Maintenance State, battery has been charged to full, system was supplied by
         external charger preferentially.*/
    {
        (chg_stm_func_type)chg_maint_state_entry_func,
        (chg_stm_func_type)chg_maint_state_period_func,
        (chg_stm_func_type)chg_maint_state_exit_func,
    },

    /* 3 Invalid Charge Temperature State, external charger is present, while battery
         is too hot/cold to charge.*/
    {
        (chg_stm_func_type)chg_invalid_chg_temp_state_entry_func,
        (chg_stm_func_type)chg_invalid_chg_temp_state_period_func,
        (chg_stm_func_type)chg_invalid_chg_temp_state_exit_func,
    },

    /* 4 Battery Only State, external charger is absent, or removed, system was supplied
         by battery.*/
    {
        (chg_stm_func_type)chg_batt_only_state_entry_func,
        (chg_stm_func_type)chg_batt_only_state_period_func,
        (chg_stm_func_type)chg_batt_only_state_exit_func,
    },

#if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
    /* 5 warm chg State, battery is charged during this state when the battery temp is in
      warm chg area*/
    {
        (chg_stm_func_type)chg_warmchg_state_entry_func,
        (chg_stm_func_type)chg_warmchg_state_period_func,
        (chg_stm_func_type)chg_warmchg_state_exit_func,
    },
#endif /* MBB_CHG_WARM_CHARGE */


    {
        NULL,NULL,NULL
    }
};
/*----------------------------------------------*
 * ȫ�ֱ���                                   *
 *----------------------------------------------*/
#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
chg_stm_state_info_t chg_stm_state_info = {0,0,0,0,0,0,0,CHG_BAT_ONLY_MODE,0,0,0,0,0
#if ( FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT )
,0
#endif
};
#else
chg_stm_state_info_t chg_stm_state_info = {0,0,0,0,0,0,0,CHG_BAT_ONLY_MODE,0,0,0,0
#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT ) && (FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT)
,0,0
#elif ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
,0
#else ( FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT )
,0
#endif
};
#endif


/* ���ʹ�ܱ�־�ṩ��USB��������������1:ʹ�ܳ�� 0:û��ʹ��*/
int chg_en_flag = 0;
unsigned long chg_en_timestamp = 0;
#define CHG_EN_TIME_SLOT    (50)
#if (MBB_CHG_HIGH_VOLT_BATT == FEATURE_ON)
/* 0 - 10 ������ز����趨�����1900mah��� */
int chg_hw_para_updated = 0;
int chg_sub_low_temp_changed = 0;
#define CHG_SUB_LOW_TEMP_TOP                (10)
#define CHG_TEMP_RESUM                      ( 3)
#if defined(BSP_CONFIG_BOARD_E5_E5578) 
#define CHG_SUB_LOW_TEMP_CURR_WALL               (576)
#define CHG_SUB_LOW_TEMP_CURR_USB2             (576)
#define CHG_SUB_LOW_TEMP_CURR_USB3             (576)
#elif defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5575S_210) \
    ||defined(BSP_CONFIG_BOARD_E5573S_156) || defined(BSP_CONFIG_BOARD_E5573S_856) \
    || defined(BSP_CONFIG_BOARD_E5573S_853) || defined(BSP_CONFIG_BOARD_E5573S_607) \
    || defined(BSP_CONFIG_BOARD_E5577CS_603) || defined(BSP_CONFIG_BOARD_E5575S_320) \
    || defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573BS) \
    || defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_607HW) \
    || defined(BSP_CONFIG_BOARD_R218h)
#define CHG_SUB_LOW_TEMP_CURR_WALL             (448)
#define CHG_SUB_LOW_TEMP_CURR_USB2             (448)
#define CHG_SUB_LOW_TEMP_CURR_USB3             (448)
#elif defined(BSP_CONFIG_BOARD_E5577S_603)
#define CHG_SUB_LOW_TEMP_CURR_WALL             (896)
#define CHG_SUB_LOW_TEMP_CURR_USB2             (576)
#define CHG_SUB_LOW_TEMP_CURR_USB3             (896)
#elif defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577S_932) \
    ||defined(BSP_CONFIG_BOARD_E5577S_324) || defined(BSP_CONFIG_BOARD_E5577BS_937)
#define CHG_SUB_LOW_TEMP_CURR_WALL             (448)
#define CHG_SUB_LOW_TEMP_CURR_USB2             (448)
#define CHG_SUB_LOW_TEMP_CURR_USB3             (448)
#define CHG_SUB_LOW_TEMP_CURR_WALL_H             (896)
#define CHG_SUB_LOW_TEMP_CURR_USB2_H             (576)
#define CHG_SUB_LOW_TEMP_CURR_USB3_H             (896)
#elif defined(BSP_CONFIG_BOARD_401HW) || defined(BSP_CONFIG_BOARD_506HW) \
   || defined(BSP_CONFIG_BOARD_506HW_2)
#define CHG_SUB_LOW_TEMP_CURR_WALL             (448)
#define CHG_SUB_LOW_TEMP_CURR_USB2             (448)
#define CHG_SUB_LOW_TEMP_CURR_USB3             (448)
#elif defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
#define CHG_SUB_LOW_TEMP_CURR_WALL             (2048)
#define CHG_SUB_LOW_TEMP_CURR_USB2             (576)
#define CHG_SUB_LOW_TEMP_CURR_USB3             (1024)
#else
#define CHG_SUB_LOW_TEMP_CURR_WALL             (576)
#define CHG_SUB_LOW_TEMP_CURR_USB2             (576)
#define CHG_SUB_LOW_TEMP_CURR_USB3             (576)
#endif

#endif
#ifdef BSP_CONFIG_BOARD_E5_DCM
static const chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
       1200,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4200,  /*mV, CV Voltage setting.*/
        256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/

    },

    #if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
    /*5:-Warm charge State*/
    {
        500,  /*mA, Power Supply front-end Current limit.*/
        512,  /*mA, Charge Current limit.*/
        4144,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

/*������ͣ����������*/
static const chg_hw_param_t chg_std_chgr_over_temp_hw_paras =  /*lint !e10*/
{
        100,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
};

static const chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if (MBB_CHG_WARM_CHARGE ==FEATURE_ON)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4144,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

/*usb����ͣ����������*/
static const chg_hw_param_t chg_usb_chgr_over_temp_hw_paras =  /*lint !e10*/
{
         100, /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
};
static const chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#elif defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5575S_210) \
    || defined(BSP_CONFIG_BOARD_E5573S_156) || defined(BSP_CONFIG_BOARD_E5573S_856) \
    || defined(BSP_CONFIG_BOARD_E5573S_853) || defined(BSP_CONFIG_BOARD_E5573S_607) \
    || defined(BSP_CONFIG_BOARD_E5577CS_603) || defined(BSP_CONFIG_BOARD_E5575S_320)
static const chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
       1200,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4352,  /*mV, CV Voltage setting.*/
        128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

#elif defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573BS)\
        || defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_R218h)
static const chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
       1200,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4352,  /*mV, CV Voltage setting.*/
        128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        512,  /*mA, Charge Current limit.*/
        4144,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4144,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4144,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#elif defined(BSP_CONFIG_BOARD_E5577S_603)
/* 3000mA��ز��� */
static chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        896,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         896,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#elif defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577BS_937)
//1500mA��ز���
static chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
       1200,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4352,  /*mV, CV Voltage setting.*/
        128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
//3000mA��ز���
static chg_hw_param_t chg_std_chgr_hw_paras_h[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        896,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb_chgr_hw_paras_h[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb3_chgr_hw_paras_h[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         896,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#elif defined(BSP_CONFIG_BOARD_E5577S_324)
//1500mA��ز���
static chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
       1200,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4304,  /*mV, CV Voltage setting.*/
        128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
//3000mA��ز���
static chg_hw_param_t chg_std_chgr_hw_paras_h[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        896,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb_chgr_hw_paras_h[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb3_chgr_hw_paras_h[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4304,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         896,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#elif defined(BSP_CONFIG_BOARD_E5577S_932)
//default��ز���
static chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
       1200,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4352,  /*mV, CV Voltage setting.*/
        128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
//3000mA��ز���
static const chg_hw_param_t chg_std_chgr_hw_paras_h[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
       2000,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4352,  /*mV, CV Voltage setting.*/
        256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        896,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb_chgr_hw_paras_h[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb3_chgr_hw_paras_h[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#elif defined(BSP_CONFIG_BOARD_E5_E5578)
static const chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
       1200,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4352,  /*mV, CV Voltage setting.*/
        128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
        4144,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4144,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4144,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#elif defined(BSP_CONFIG_BOARD_401HW) || defined(BSP_CONFIG_BOARD_506HW) 
static const chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
       1200,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4352,  /*mV, CV Voltage setting.*/
        128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #if defined(MBB_CHG_WARM_CHARGE)
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
static const chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #if defined(MBB_CHG_WARM_CHARGE)
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
static const chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #if defined(MBB_CHG_WARM_CHARGE)
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#elif defined(BSP_CONFIG_BOARD_506HW_2) 
static const chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
       1200,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4352,  /*mV, CV Voltage setting.*/
        128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #if defined(MBB_CHG_WARM_CHARGE)
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
static const chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #if defined(MBB_CHG_WARM_CHARGE)
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
static const chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #if defined(MBB_CHG_WARM_CHARGE)
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4112,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#elif defined(BSP_CONFIG_BOARD_607HW)
static const chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
       1200,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4350,  /*mV, CV Voltage setting.*/
        128,  /*mA, Taper(Terminate) current.*/
       FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        900,  /*mA, Power Supply front-end Current limit.*/
        512,  /*mA, Charge Current limit.*/
       4100,  /*mV, CV Voltage setting.*/
        128,  /*mA, Taper(Terminate) current.*/
       TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4350,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#elif defined(BSP_CONFIG_BOARD_E5_E5770s)
static const chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         704,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4352,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4144,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#elif defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
static const chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
        1500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
        1500,  /*mA, Power Supply front-end Current limit.*/
        1536,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

static const chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
         4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
         4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
         4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
         4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if defined(MBB_CHG_WARM_CHARGE)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
         4100,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#else
static const chg_hw_param_t chg_std_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
        2000,  /*mA, Power Supply front-end Current limit.*/
        2048,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
       1200,  /*mA, Power Supply front-end Current limit.*/
        576,  /*mA, Charge Current limit.*/
       4200,  /*mV, CV Voltage setting.*/
        256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/

    },

    #if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
    /*5:-Warm charge State*/
    {
        1200,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

/*usb2.0��������*/
static const chg_hw_param_t chg_usb_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         704,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};

/*usb3.0��������*/
static const chg_hw_param_t chg_usb3_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         1024,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
         TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         512,  /*mA, Charge Current limit.*/
        4208,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
    /*5:-Warm charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         128,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
#endif


#if (MBB_CHG_WIRELESS == FEATURE_ON)
/*���߳������λ��־���������߳��Ͷ����绥���л�*/
boolean g_wireless_online_flag = OFFLINE;
/*ͨ��BQ24196���������߳���Ƿ�����ǿ������߳��оƬ�Ĺܽ�*/
static const chg_hw_param_t chg_wireless_chgr_hw_paras[CHG_STM_MAX_ST] =
{
    /*0:-Transition State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*1:-Fast Charge State*/
    {
         900,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*2:-Maintenance State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
        1024,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    /*3:-Invalid Charge Temperature State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    /*4:-Battery Only State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4200,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        FALSE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },

    #if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
    /*5:-Warm charge State*/
    {
         500,  /*mA, Power Supply front-end Current limit.*/
         576,  /*mA, Charge Current limit.*/
        4100,  /*mV, CV Voltage setting.*/
         256,  /*mA, Taper(Terminate) current.*/
        TRUE   /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
    },
    #endif /* MBB_CHG_WARM_CHARGE */
};
/*�ػ����߳�����������*/
#if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
static const chg_hw_param_t chg_wireless_poweroff_warmchg_paras =
{
     900,  /*mA, Power Supply front-end Current limit.*/
    1024,  /*mA, Charge Current limit.*/
    4100,  /*mV, CV Voltage setting.*/
     256,  /*mA, Taper(Terminate) current.*/
    TRUE  /*If charge enabled: FALSE:-Disable, TRUE:-Enable.*/
};
#endif /* MBB_CHG_WARM_CHARGE */
#endif /* MBB_CHG_WIRELESS */

/*0:-PwrOff Charging; 1:-Normal Charging.*/
/*0:-USB/NoStd Chgr;  1:-Wall/Standard Chgr.*/
static const uint32_t chg_fastchg_timeout_value_in_sec[2][2] =
{
    /*Power-off charge.*/
    {
        CHG_POWEROFF_FAST_USB_TIMER_VALUE,           /*USB/NoStd Chgr*/
        CHG_POWEROFF_FAST_CHG_TIMER_VALUE,           /*Wall/Standard Chgr*/
    },
    /*Normal charge.*/
    {
        CHG_FAST_USB_TIMER_VALUE,                    /*USB/NoStd Chgr*/
        CHG_FAST_CHG_TIMER_VALUE,                    /*Wall/Standard Chgr*/
    },
};

#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
typedef enum
{
    RE_BATT_ONLY,
    RE_POWER_ON_CHARGE,
    RE_POWER_ON_EXTCHG, 
    RE_POWER_DOWN_CHARGE, 
    RE_POWER_DOWN_EXTCHG,
}BATT_REVISE_STAT;

static const uint32_t chg_batt_revise_table[5][3] =
{
    {2, 2, 2},//�������λ
    {2, 5, 6},//�������ڳ��+���Ⲣ�����
    {2,-2,-2},//������������
    {2, 4, 5},//�ػ����ڳ��+���Ⲣ�����
    {2,-2,-2},//�ػ���������
};
#endif

/*----------------------------------------------*
 * ��������                                     *
 *----------------------------------------------*/
static const char* chg_stm_name_table[CHG_STM_MAX_ST] =
{
    "Transition",                 //����״̬
    "Fast Charge",                //���״̬
    "Maintenance",                //����״̬
    "Invalid Charge Temperature", //����״̬
    "Battery Only",               //��ص�����λ״̬
    "Warm charge"                 //���³��״̬
};

static const char* chg_chgr_type_name_table[CHG_CHGR_INVALID + 1] =
{
    "Unknown",                      //���������δ֪
    "Wall Charger",                 //��׼�����
    "USB HOST PC",                  //USB
    "Non-Standard Chgr",            //�����������
    "wireless chgr"                 //���߳����
    "extchg chgr"                   //��������
    "weak_chgr"                     //����
    "Invalid",                      //�����������
};

/*----------------------------------------------*
 * �궨��                                       *
 *----------------------------------------------*/

/*Lookup charge state machine name from chg_stm_name_table.*/
/*BE CAREFUL: Pls DO make sure "i" MUSTN'T exceed (CHG_STM_INIT_ST, CHG_STM_MAX_ST) range.*/
#define TO_STM_NAME(i)   ((i >= CHG_STM_TRANSIT_ST && i < CHG_STM_MAX_ST) \
                         ? chg_stm_name_table[i] : "NULL")

/*Lookup charger type name from chg_chgr_type_name_table*/
/*BE CAREFUL: Pls DO make sure "i" MUSTN'T exceed [CHG_CHGR_UNKNOWN, CHG_CHGR_INVALID] range.*/
#define TO_CHGR_NAME(i)  ((i <= CHG_CHGR_INVALID) \
                         ? chg_chgr_type_name_table[i] : "NULL")

/*����¶�ƽ���ĳ��ȸ���:����ѯ����Ϊ30������ѯ����Ϊ5*/
#define  CHG_BAT_TEMP_SMOOTH_SAMPLE_FAST   (30)
#define  CHG_BAT_TEMP_SMOOTH_SAMPLE_SLOW   (5)

/*��ص�ѹƽ���ĳ��ȸ���:����ѯ����Ϊ30������ѯ����Ϊ5*/
#define  CHG_BAT_VOLT_SMOOTH_SAMPLE_FAST    (30)
#define  CHG_BAT_VOLT_SMOOTH_SAMPLE_SLOW    (5)


/*���¹ػ��ײ�ȴ�ʱ�䣬��APP�ڸ�ʱ�������δ�ػ�����ײ�ִ�йػ�*/
#define  OVER_TEMP_SHUTOFF_DURATION         (15000)
/*�͵�ػ��ײ�ȴ�ʱ�䣬��APP�ڸ�ʱ�������δ�ػ�����ײ�ִ�йػ�*/
#define  LOW_BATT_SHUTOFF_DURATION          (15000)

/*�������쳣��ؼ��*/
#define CHG_AUTO_CUR_CTRL_DIE_TEMP_MIN      (-30)
/* �����󻵵�ؼ��ĵ�ѹ����***/
#define CHG_SHORT_CIRC_BATTERY_THRES        (2700)

/*���¹ػ����¶ȸ澯���ʹ����ڴﵽ�ػ�����ǰ�ĸ÷�Χ����ʾ����*/
#define SHUTOFF_HIGH_TEMP_WARN_LEN          (2)
/*������ʾ�Ļָ����ʹ������¶Ȼָ����ػ����޵ĸ÷�Χ���£��������¸澯��ʾ*/
#define SHUTOFF_HIGH_TEMP_RESUME_LEN        (5)

#define LIMIT_SUPPLY_CURR_TEMP              (58)
#define LIMIT_SUPPLY_CURR__RESUME_LEN       (1)

/*��ع��º��Ӧ���ϱ������¼��Ĵ���*/
#define BATTERY_EVENT_REPORT_TIMES          (5)

#define CHG_BATT_REVISE    1 
#define CHG_USE_COUL_REVISE    0
static int32_t g_chg_revise_count = 0;

/*USB�±�����ֵ,Ӳ��������ɺ��ṩ*/ 
#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
#define CHG_USB_TEMP_LIMIT      (90)     /*USB�±����ƴ�������*/
#define CHG_USB_TEMP_RESUME     (70)    /*USB�¶Ȼ��ƻָ�����*/
#endif

/*��ʼ���ǰ�ĵ�ص�ѹ�����ڳ��ʱ�ĵ�ѹ��������ת*/
#if (MBB_CHG_HIGH_VOLT_BATT == FEATURE_ON)
//#define CHG_BATT_VOLT_REVISE_LIMIT_UP       (4280)    //����ص�ѹ��������
#define CHG_BATT_VOLT_REVISE_LIMIT_UP       (is_batttemp_in_warm_chg_area()?4080:4280)  //����ص�ѹ��������
#else
//#define CHG_BATT_VOLT_REVISE_LIMIT_UP       (4150)    //����ص�ѹ��������
#define CHG_BATT_VOLT_REVISE_LIMIT_UP       (is_batttemp_in_warm_chg_area()?4080:4150)     //����ص�ѹ��������
#endif
#define CHG_BATT_VOLT_REVISE_LIMIT_DOWN     (3350)    //�ŵ��ص�ѹ��������
#define CHG_BATT_VOLT_REVISE_WINDOW         (35)    //��ѹ��߱仯̫С�򲻲�����
#define CHG_BATT_VOLT_REVISE_LIMIT          (200)    //��߲�������ֵ
#define CHG_BATT_VOLT_REVISE_COUNT          (15)    //�״ν��е�ص�ѹ������ֵ����Ĵ�����30������ѯ��1min

/* ��Ҫ�ϱ��¼���Ӧ��ʱ��ʱ5�����ߣ���֤Ӧ���ܹ��յ��¼�*/
#define ALARM_REPORT_WAKELOCK_TIMEOUT (5000)
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
#define SHUTDOWN_WAKELOCK_TIMEOUT (1000 * 120)
#endif

#if defined(BSP_CONFIG_BOARD_E5_E5770s)
#define CHG_TERMI_VOLT_FOR_COUL             (4192)
#define CHG_TERMI_CURR_FOR_COUL             (120)
#define CHG_BAT_TEMP_REVISE_SAMPLE_FAST     (6)
#define CHG_BAT_TEMP_REVISE_SAMPLE_SLOW     (3)
#define CHG_BAT_TEMP_REVISE_TEM_OF_NOREVISE (5)
#define LG_TBATT_SUPPLY_VOLT                (3580)
#define LG_TBATT_DISCHG_VOLT                (3950)
#define LG_TBATT_SUPPLY_STOP_VOLT           (3625)
#define LG_TBATT_DISCHG_STOP_VOLT           (3915)
#define SY_TBATT_SUPPLY_VOLT                (3750)
#define SY_TBATT_DISCHG_VOLT                (3986)
#define SY_TBATT_SUPPLY_STOP_VOLT           (3785)
#define SY_TBATT_DISCHG_STOP_VOLT           (3956)
#define EXTCHG_STOP_THRESHOLD_POWON         (10)
#define EXTCHG_STOP_THRESHOLD_POWDOWN       (2)
#define EXTCHG_RECHG_THRESHOLD              (20)
#endif

#if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
#define CHG_TERMI_VOLT_FOR_COUL             (4165)
#define CHG_TERMI_WARMCHG_VOLT_FOR_COUL     (4065)
#define CHG_TERMI_CURR_FOR_COUL             (256)
#define CHG_BAT_TEMP_REVISE_SAMPLE_FAST     (6)
#define CHG_BAT_TEMP_REVISE_SAMPLE_SLOW     (3)
#define CHG_BAT_TEMP_REVISE_TEM_OF_NOREVISE (5)
#define LG_TBATT_SUPPLY_VOLT                (3580)
#define LG_TBATT_DISCHG_VOLT                (3950)
#define LG_TBATT_SUPPLY_STOP_VOLT           (3625)
#define LG_TBATT_DISCHG_STOP_VOLT           (3915)
#define SY_TBATT_SUPPLY_VOLT                (3460)
#define SY_TBATT_DISCHG_VOLT                (3900)
#define SY_TBATT_SUPPLY_STOP_VOLT           (3540)
#define SY_TBATT_DISCHG_STOP_VOLT           (3860)
#define EXTCHG_STOP_THRESHOLD_POWON         (10)
#define EXTCHG_STOP_THRESHOLD_POWDOWN       (2)
#define EXTCHG_RECHG_THRESHOLD              (30)
#endif

#if (MBB_CHG_EXTCHG == FEATURE_ON)
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
#if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
/* ��������ĸ������� */
#define EXTCHG_OVER_TEMP_STOP_THRESHOLD     (61)
#define EXTCHG_OVER_TEMP_RESUME_THRESHOLD   (58)
#define EXTCHG_WARM_CHARGE_LIMIT_THRESHOLD  (55)
#define EXTCHG_WARM_CHARGE_RESUME_THRESHOLD (52)
#define EXTCHG_LOW_TEMP_SHUTOFF_THRESHOLD   (-20)
#define EXTCHG_LOW_TEMP_SHUT_RESUM_THRSHOLD (-17)
#define EXTCHG_LOW_TEMP_STOP_THRESHOLD      (0)
#define EXTCHG_LOW_TEMP_RESUME_THRESHOLD    (3)
#define EXTCHG_SHORT_VOLT_THRESHOLD         (2000)
#define TIME_OF_SHORT_DET                   (10)
#define NUM_OF_SHORT_DET_POLL               (3)
#else
#define EXTCHG_EXTREME_HIGH_TEMP            (77)
#define EXTCHG_OVER_TEMP_STOP_THRESHOLD     (61)
#define EXTCHG_OVER_TEMP_RESUME_THRESHOLD   (60)
#define EXTCHG_WARM_CHARGE_LIMIT_THRESHOLD  (55)
#define EXTCHG_WARM_CHARGE_RESUME_THRESHOLD (45)
#define EXTCHG_LOW_VOLTAGE_LIMIT_THRESHOLD  (3600)
#define EXTCHG_LOW_VOLTAGE_STOP_THRESHOLD   (3450)
#define EXTCHG_LOW_TEMP_SHUTOFF_THRESHOLD   (-20)
#define EXTCHG_LOW_TEMP_SHUT_RESUM_THRSHOLD (-17)
#define EXTCHG_LOW_TEMP_STOP_THRESHOLD      (0)
#define EXTCHG_LOW_TEMP_RESUME_THRESHOLD    (3)
#define EXTCHG_LOW_VOLTAGE_RESUME_THRESHOLD (3700)
#define EXTCHG_SHORT_VOLT_THRESHOLD         (2000)
#define TIME_OF_SHORT_DET                   (10)
#define NUM_OF_SHORT_DET_POLL               (3)
#define EXTCHG_STOP_CHG_CAPACITY            (18)
#endif
#else
#define EXTCHG_LOW_TEMP_STOP_THRESHOLD      (0)
#define EXTCHG_LOW_TEMP_RESUME_THRESHOLD    (3)
#define EXTCHG_OVER_TEMP_STOP_THRESHOLD     (55)
#define EXTCHG_OVER_TEMP_RESUME_THRESHOLD   (51)
#define EXTCHG_LOW_VOLTAGE_RESUME_THRESHOLD (3550)
#endif
static boolean is_otg_extchg    = FALSE;
static boolean is_extchg_ovtemp = FALSE;


static int32_t g_extchg_revise_count = 0;
#define EXTCHG_BATT_VOLT_REVISE_LIMIT       (200)
#define EXTCHG_THRESHOLD_PATH   "/data/userdata/extchg_config/extchg_threshold"
#define EXTCHG_DISABLE_PATH     "/data/userdata/extchg_config/extchg_disable_st"
#define EXTCHG_DEFAULT_STOP_THRESHOLD       (5)
#define EXTCHG_STOP_CAPACITY_TEN            (10)

#define EXTCHG_STOP_CAPACITY_FIFTHTEEN      (15)
#define EXTCHG_STOP_CAPACITY_EIGHTEEN       (18)

#define EXTCHG_STOP_CAPACITY_TWENTY         (20)
#define EXTCHG_STOP_CAPACITY_THIRTY         (30)

#define EXTCHG_STOP_CAPACITY_THIRTYSIX      (36)
#define EXTCHG_STOP_CAPACITY_TWENTYFIVE      (25)

#define EXTCHG_STOP_CAPACITY_FORTY          (40)
#define EXTCHG_STOP_CAPACITY_FIFTY          (50)
#define EXTCHG_STOP_CAPACITY_SIXTY          (60)
#define EXTCHG_STOP_CAPACITY_SEVENTY        (70)
#define EXTCHG_STOP_CAPACITY_EIGHTY         (80)
#define EXTCHG_STOP_CAPACITY_NINETY         (90)
#define EXTCHG_STOP_CAPACITY_HUNDRED        (100)

#if defined(BSP_CONFIG_BOARD_E5577S_932)
#define EXTCHG_DEFAULT_STOP_VOLTAGE         (3626)
#define EXTCHG_STOP_VOLTAGE_TEN             (3667)
#define EXTCHG_STOP_VOLTAGE_TWENTY          (3724)
#define EXTCHG_STOP_VOLTAGE_THIRTY          (3757)
#define EXTCHG_STOP_VOLTAGE_FORTY           (3791)
#define EXTCHG_STOP_VOLTAGE_FIFTY           (3838)
#define EXTCHG_STOP_VOLTAGE_SIXTY           (3904)
#define EXTCHG_STOP_VOLTAGE_SEVENTY         (3987)
#define EXTCHG_STOP_VOLTAGE_EIGHTY          (4087)
#define EXTCHG_STOP_VOLTAGE_NINETY          (4201)
#define EXTCHG_STOP_VOLTAGE_HUNDRED         (4353)
#elif defined(BSP_CONFIG_BOARD_E5577S_321)
#define EXTCHG_DEFAULT_STOP_VOLTAGE         (3630)
#define EXTCHG_STOP_VOLTAGE_TEN             (3669)
#define EXTCHG_STOP_VOLTAGE_TWENTY          (3722)
#define EXTCHG_STOP_VOLTAGE_THIRTY          (3752)
#define EXTCHG_STOP_VOLTAGE_FORTY           (3788)
#define EXTCHG_STOP_VOLTAGE_FIFTY           (3836)
#define EXTCHG_STOP_VOLTAGE_SIXTY           (3900)
#define EXTCHG_STOP_VOLTAGE_SEVENTY         (3981)
#define EXTCHG_STOP_VOLTAGE_EIGHTY          (4081)
#define EXTCHG_STOP_VOLTAGE_NINETY          (4191)
#define EXTCHG_STOP_VOLTAGE_HUNDRED         (4347)
#elif defined(BSP_CONFIG_BOARD_E5577S_324)||defined(BSP_CONFIG_BOARD_E5577BS_937)
#define EXTCHG_DEFAULT_STOP_VOLTAGE         (3630)
#define EXTCHG_STOP_VOLTAGE_TEN             (3669)
#define EXTCHG_STOP_VOLTAGE_TWENTY          (3722)
#define EXTCHG_STOP_VOLTAGE_THIRTY          (3752)
#define EXTCHG_STOP_VOLTAGE_FORTY           (3788)
#define EXTCHG_STOP_VOLTAGE_FIFTY           (3836)
#define EXTCHG_STOP_VOLTAGE_SIXTY           (3900)
#define EXTCHG_STOP_VOLTAGE_SEVENTY         (3981)
#define EXTCHG_STOP_VOLTAGE_EIGHTY          (4081)
#define EXTCHG_STOP_VOLTAGE_NINETY          (4191)
#define EXTCHG_STOP_VOLTAGE_HUNDRED         (4347)
#else
#define EXTCHG_DEFAULT_STOP_VOLTAGE         (3470)
#define EXTCHG_STOP_VOLTAGE_TEN             (3579)
#define EXTCHG_STOP_VOLTAGE_TWENTY          (3637)
#define EXTCHG_STOP_VOLTAGE_THIRTY          (3670)
#define EXTCHG_STOP_VOLTAGE_FORTY           (3696)
#define EXTCHG_STOP_VOLTAGE_FIFTY           (3728)
#define EXTCHG_STOP_VOLTAGE_SIXTY           (3769)
#define EXTCHG_STOP_VOLTAGE_SEVENTY         (3830)
#define EXTCHG_STOP_VOLTAGE_EIGHTY          (3902)
#define EXTCHG_STOP_VOLTAGE_NINETY          (3985)
#define EXTCHG_STOP_VOLTAGE_HUNDRED         (4130)
#endif

/*ֹͣ�������ŵ�ص���ֵĬ��Ϊ�͵�5%->3.55V*/
int32_t g_extchg_voltage_threshold = 0;
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
int32_t g_extchg_stop_soc_threshold = 0;
#endif
/*�Ƿ�����ֹͣ�������־1:����ֹͣ 0:���ÿ���*/
int32_t g_extchg_diable_st = 0;
/*��¼�û��ϴ����õ�����ֹͣ�������־1������ֹͣ��0�����ÿ���*/
static int32_t g_last_extchg_diable_st = 0;
#define EXTCHG_TEMP_COMPENSATE_VALUE        (4)
/*�û�ͨ��TOUCH UIѡ��Ķ������ģʽ��1:�������� 2:�����������ҵ��*/
int32_t g_ui_choose_exchg_mode = 0;
boolean g_exchg_enable_flag = FALSE;
/*������USB ID����λ��־�����ڶ���������߳��Ļ����л�*/
boolean g_exchg_online_flag = OFFLINE;
#endif /*MBB_CHG_EXTCHG */

#if ((MBB_CHG_EXTCHG == FEATURE_ON) || (MBB_CHG_WIRELESS == FEATURE_ON))
/*�±ߺ�����ͬƽ̨ʵ�ַ�ʽ��ͬ����Ҫ��������*/

extern void usb_notify_event(unsigned long val, void *v);
#endif/*defined(MBB_CHG_EXTCHG) || defined(MBB_CHG_WIRELESS)*/
#if ( FEATURE_ON == MBB_MLOG )
extern void mlog_set_statis_info(char *item_name,unsigned int item_value);
#endif
/**********************************************************************
�� �� ��  : void load_factory_mode_flag_init(void)
��������  : ��ȡ����ģʽ��־NV����
�������  : none
�������  : �ޡ�
�� �� ֵ  : �ޡ�
ע������  : �ޡ�
***********************************************************************/
void load_ftm_mode_init(void)
{
    if(CHG_OK == chg_config_para_read(NV_FACTORY_MODE_I, (char *) &g_real_factory_mode, sizeof(uint32_t)))
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:read factory mode ok,mode =  %d\n ", g_real_factory_mode);

        if(0 == g_real_factory_mode)
        {
            chg_current_ftm_mode = TRUE;
        }
        else
        {
            chg_current_ftm_mode = FALSE;
        }
    }
    else/*��NV��ʧ�ܣ���Ĭ��Ϊ�����汾*/
    {
#ifndef MBB_FACTORY_FEATURE
        chg_current_ftm_mode = FALSE;
#else
        chg_current_ftm_mode = TRUE;
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM: In ftm mode now \n ");
#endif
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:read factory mode nv fail \n ");
    }
}

/*******************************************************************
Function:      chg_batt_temp_init
Description:   ����¶�����ֵ��ʼ����������ȡNV�����ȡ��ֵ�浽ȫ�ֱ�����
Data Accessed: ��
Data Updated:  ��
Input:         ��
Return:        ��
*******************************************************************/
void chg_batt_temp_init(void)
{
    if(CHG_OK != chg_config_para_read(NV_OVER_TEMP_SHUTOFF_PROTECT,&g_chgBattOverTempPeotect, \
    sizeof(CHG_BATTERY_OVER_TEMP_PROTECT_NV)))
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:NV_OVER_TEMP_SHUTOFF_PROTECT read fail \n ");
        g_chgBattOverTempPeotect.ulIsEnable =  1;
        g_chgBattOverTempPeotect.lCloseAdcThreshold = 61; /*power off temp +1 */
        g_chgBattOverTempPeotect.ulTempOverCount = 1;
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:NV_OVER_TEMP_SHUTOFF_PROTECT read success \n ");
    }

    if(CHG_OK != chg_config_para_read(NV_LOW_TEMP_SHUTOFF_PROTECT,&g_chgBattLowTempPeotect,\
    sizeof(CHG_BATTERY_LOW_TEMP_PROTECT_NV)))
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:NV_LOW_TEMP_SHUTOFF_PROTECT read fail \n ");
        g_chgBattLowTempPeotect.ulIsEnable =  1;
        g_chgBattLowTempPeotect.lCloseAdcThreshold = -20; /* */
        g_chgBattLowTempPeotect.ulTempLowCount = 1;
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:NV_LOW_TEMP_SHUTOFF_PROTECT read success \n ");
    }

    if(CHG_OK != chg_config_para_read(NV_BATT_TEMP_PROTECT_I,&g_chgShutOffTempProtect,\
    sizeof(CHG_SHUTOFF_TEMP_PROTECT_NV_TYPE)))
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:NV_BATT_TEMP_PROTECT_I read fail \n ");
        #if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
        g_chgShutOffTempProtect.ulChargeIsEnable = 1;           //����±���ʹ��
        g_chgShutOffTempProtect.overTempchgStopThreshold = 55;  //�����±�������
        g_chgShutOffTempProtect.subTempChgLimitCurrentThreshold = 45; //���³����ڵ���¶�����
        g_chgShutOffTempProtect.lowTempChgStopThreshold = 0;    //�����±�������
        g_chgShutOffTempProtect.overTempChgResumeThreshold = 52; //�����»ָ��¶�����
        g_chgShutOffTempProtect.lowTempChgResumeThreshold = 3;   //�����»ָ��¶�����
        g_chgShutOffTempProtect.chgTempProtectCheckTimes = 1;    //���ͣ����ѯ����
        g_chgShutOffTempProtect.chgTempResumeCheckTimes = 1;     //��縴����ѯ����
        g_chgShutOffTempProtect.exitWarmChgToNormalChgThreshold = 42; //���³��ָ������³���¶�����
        g_chgShutOffTempProtect.reserved2 = 0;                   //Ԥ��
        #else
        g_chgShutOffTempProtect.ulChargeIsEnable = 1;           //����±���ʹ��
        g_chgShutOffTempProtect.overTempchgStopThreshold = 45;  //�����±�������
        g_chgShutOffTempProtect.subTempChgLimitCurrentThreshold = 38; //2A�����3000mA��ص������������
        g_chgShutOffTempProtect.lowTempChgStopThreshold = 0;    //�����±�������
        g_chgShutOffTempProtect.overTempChgResumeThreshold = 42;//�����»ָ��¶�����
        g_chgShutOffTempProtect.lowTempChgResumeThreshold = 3;  //�����»ָ��¶�����
        g_chgShutOffTempProtect.chgTempProtectCheckTimes = 1;   //���ͣ����ѯ����
        g_chgShutOffTempProtect.chgTempResumeCheckTimes = 1;    //��縴����ѯ����
        g_chgShutOffTempProtect.exitWarmChgToNormalChgThreshold = 0; //���³��ָ������³���¶�����
        g_chgShutOffTempProtect.reserved2 = 0;                  //Ԥ��
        #endif /* MBB_CHG_WARM_CHARGE */
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:NV_BATT_TEMP_PROTECT_I read success \n ");
    }
}

/**********************************************************************
�� �� ��  : void load_on_off_mode_parameter(void)
��������  :  ��ȡӲ�����Կ���ģʽNV
�������  :none
�������  : �ޡ�
�� �� ֵ      : �ޡ�
ע������  : �ޡ�
***********************************************************************/
void load_on_off_mode_parameter(void)
{
    uint32_t ret_val = CHG_ERROR;
    memset( (void *)&g_real_powerup_mode_value, 0, sizeof(POWERUP_MODE_TYPE) );

    /* ��nv�ж�ȡӲ�����Կ���ģʽ��־*/
    /* �����ȡʧ�ܲ����ã�����Ĭ��ֵ*/
    ret_val = chg_config_para_read(NV_POWERUP_MODE,&g_real_powerup_mode_value, \
        sizeof(POWERUP_MODE_TYPE) );
    if ( CHG_OK == ret_val )
    {
        chg_print_level_message(CHG_MSG_INFO,"CHG_STM:\r\nno_battery_powerup_enable=%d,\r\nexception_poweroff_poweron_enable=%d,\
            \r\nlow_battery_poweroff_disable=%d,\r\n ",\
            g_real_powerup_mode_value.no_battery_powerup_enable,
            g_real_powerup_mode_value.exception_poweroff_poweron_enable,
            g_real_powerup_mode_value.low_battery_poweroff_disable);
    }
    else
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:read hw test powerup mode nv error, ret_val = %d \n ", ret_val, 0, 0);

        g_real_powerup_mode_value.no_battery_powerup_enable = FALSE;
        g_real_powerup_mode_value.exception_poweroff_poweron_enable = FALSE;
        g_real_powerup_mode_value.low_battery_poweroff_disable = FALSE;
    }

}

/*******************************************************************
Function:      chg_batt_volt_init
Description:   ��ص�ѹ����ֵ��ʼ����������ȡNV�����ȡ��ֵ�浽ȫ�ֱ�����
Data Accessed: ��
Data Updated:  ��
Input:         ��
Return:        ��
*******************************************************************/
void chg_batt_volt_init(void)
{
#if defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5_E5578) \
    || defined(BSP_CONFIG_BOARD_E5575S_210) || defined(BSP_CONFIG_BOARD_E5577S_321) \
	|| defined(BSP_CONFIG_BOARD_401HW) || defined(BSP_CONFIG_BOARD_E5575S_320) \
    || defined(BSP_CONFIG_BOARD_E5573S_156) || defined(BSP_CONFIG_BOARD_E5577S_932) \
    || defined(BSP_CONFIG_BOARD_E5573S_856) || defined(BSP_CONFIG_BOARD_E5573S_853) \
    || defined(BSP_CONFIG_BOARD_E5573S_607) || defined(BSP_CONFIG_BOARD_E5577CS_603) \
    || defined(BSP_CONFIG_BOARD_E5577S_603) || defined(BSP_CONFIG_BOARD_E5771S_852) \
    || defined(BSP_CONFIG_BOARD_E5771H_937) || defined(BSP_CONFIG_BOARD_E5573CS) \
    || defined(BSP_CONFIG_BOARD_506HW) || defined(BSP_CONFIG_BOARD_506HW_2) \
    || defined(BSP_CONFIG_BOARD_E5573BS) || defined(BSP_CONFIG_BOARD_E5573CS_933)\
    || defined(BSP_CONFIG_BOARD_E5577S_324) || defined(BSP_CONFIG_BOARD_607HW)\
    || defined(BSP_CONFIG_BOARD_E5577BS_937) || defined(BSP_CONFIG_BOARD_R218h)
    /*get volt para by battery id*/
    if(chg_batt_volt_paras_init())
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:batt data init fail!\n");
    }
#else
/*  ��ǰE5771 �ĵ��IDδ�� ����ȡ�����ID���Ƿ�Ҫ�õ��ID���ֲ�ͬ���ҵ������  */
    if(CHG_OK != chg_config_para_read(NV_BATT_VOLT_PROTECT_I,&g_chgBattVoltProtect,\
        sizeof(CHG_SHUTOFF_VOLT_PROTECT_NV_TYPE)))
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:NV_OVER_TEMP_SHUTOFF_PROTECT read fail \n ");
#if defined(BSP_CONFIG_BOARD_E5_E5770s)
        g_chgBattVoltProtect.battVoltPowerOnThreshold = 3300;     //������ѹ����
        g_chgBattVoltProtect.battVoltPowerOffThreshold = 3300;    //�ػ���ѹ����
#else
        g_chgBattVoltProtect.battVoltPowerOnThreshold = 3450;     //������ѹ����
        g_chgBattVoltProtect.battVoltPowerOffThreshold = 3450;    //�ػ���ѹ����
#endif
        g_chgBattVoltProtect.battOverVoltProtectThreshold = 4370; //ƽ������ѹ��������(ƽ��ֵ)
        g_chgBattVoltProtect.battOverVoltProtectOneThreshold = 4390; //���γ���ѹ��������(����ֵ)
        g_chgBattVoltProtect.battChgTempMaintThreshold = 4144;    //���ָ���ͣ�������ͣ����ж�����
        g_chgBattVoltProtect.battChgRechargeThreshold = 4100;     //�����θ�������
        g_chgBattVoltProtect.VbatLevelLow_MAX = 3550;             //�͵���������
        g_chgBattVoltProtect.VbatLevel0_MAX = 3550;               //0���ѹ��������
        g_chgBattVoltProtect.VbatLevel1_MAX = 3610;               //1���ѹ��������
        g_chgBattVoltProtect.VbatLevel2_MAX = 3670;               //2���ѹ��������
        g_chgBattVoltProtect.VbatLevel3_MAX = 3770;               //3���ѹ��������
        g_chgBattVoltProtect.battChgFirstMaintThreshold = 4280;
        g_chgBattVoltProtect.battNormalTempChgRechargeThreshold = 4200;
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:NV_OVER_TEMP_SHUTOFF_PROTECT read success \n ");
    }
#endif
#if (FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT)
    g_batt_normal_temp_recherge_threshold = g_chgBattVoltProtect.battNormalTempChgRechargeThreshold;
    /* �������ͱ����꣬ͳһ����Ʒ���¸������޸�Ϊ4V  */
    g_chgBattVoltProtect.battChgRechargeThreshold = BATT_EXP_HIGH_TEMP_RECHARGE_THR;
#endif
    
}

/**********************************************************************
�� �� ��  : boolean chg_is_no_battery_powerup_enable(void)
��������  : �ж�Ŀǰ�Ƿ�Ϊ�ǹ���ģʽ�µĵ�ز���λ����ʹ��ģʽ
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : Ŀǰ�Ƿ�Ϊ�ǹ���ģʽ��ز���λ����ʹ��
                           TRUE : ʹ��
                           FALSE: ��ʹ��
ע������  : �ޡ�
***********************************************************************/
boolean chg_is_no_battery_powerup_enable(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:is_no_battery_powerup_enable %d !\n",
                            g_real_powerup_mode_value.no_battery_powerup_enable);
    return g_real_powerup_mode_value.no_battery_powerup_enable;
}

/**********************************************************************
�� �� ��  : boolean chg_is_low_battery_poweroff_disable(void)
��������  : �ж�Ŀǰ�Ƿ�Ϊ�͵�ػ���ֹģʽ
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : �Ƿ�Ϊ�͵�ػ���ֹģʽ
           TRUE : �͵�ػ���ʹ��
           FALSE: �͵�ػ�ʹ��
ע������  : �ޡ�
***********************************************************************/
boolean chg_is_low_battery_poweroff_disable(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:is_low_battery_poweroff_disable %d !\n",
                            g_real_powerup_mode_value.low_battery_poweroff_disable);
    return g_real_powerup_mode_value.low_battery_poweroff_disable;
}

/**********************************************************************
�� �� ��  : boolean chg_is_exception_poweroff_poweron_mode(void)
��������  :  �ж�Ŀǰ�Ƿ�Ϊ�쳣�ػ����´β����Դ����뿪��ģʽʹ�ܿ���ʹ��ģʽ
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : �Ƿ�Ϊ�쳣�ػ����´β����Դ����뿪��ģʽʹ��
           TRUE : ��
           FALSE: ��
ע������  : �ޡ�
***********************************************************************/
boolean chg_is_exception_poweroff_poweron_mode(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:is_exception_poweroff_poweron_mode %d !\n",
                            g_real_powerup_mode_value.exception_poweroff_poweron_enable);
    return g_real_powerup_mode_value.exception_poweroff_poweron_enable;
}

/**********************************************************************
�� �� ��  :chg_get_batt_level
��������  : ��ȡ��ǰ��ص��������Ľӿں���
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : ��ص�������
ע������  : �ޡ�
***********************************************************************/
BATT_LEVEL_ENUM chg_get_batt_level(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg_get_batt_level=%d !\n",chg_real_info.bat_volt_lvl);

    return chg_real_info.bat_volt_lvl;
}

/**********************************************************************
�� �� ��  : chg_is_ftm_mode
��������  : �ж�Ŀǰ�Ƿ�Ϊftmģʽ
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : Ŀǰ�Ƿ�Ϊ����ģʽ
           TRUE : ����ģʽ
           FALSE: �ǹ���ģʽ
ע������  : �ޡ�
***********************************************************************/
boolean chg_is_ftm_mode(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:is_ftm_mode=%d !\n",chg_current_ftm_mode);
    return chg_current_ftm_mode;
}


void chg_batt_error_handle(void)
{
    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_batt_error_handle->chg_set_power_off\n");
    chg_set_power_off(DRV_SHUTDOWN_BATTERY_ERROR);
    return;
}

/**********************************************************************
�� �� ��  : chg_get_batt_id_valid
��������  : ��⵱ǰ�ĵ���Ƿ���λ���жϵ�������ntc�¶�
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : TRUE: �����λ
            FALSE: ��ز���λ
ע������  : �ޡ�
***********************************************************************/
boolean chg_get_batt_id_valid(void)
{
    int32_t batt_temp = 0;
    boolean chg_ftm_mode = FALSE;
    boolean chg_no_battery_powerup_mode = FALSE;

    /* ����ģʽ��һֱ��Ϊ���Ϊ�Ϸ����**/
    chg_ftm_mode = chg_is_ftm_mode();
    chg_no_battery_powerup_mode = chg_is_no_battery_powerup_enable();

    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg_ftm_mode=%d ,no_battery_powerup_mode=%d!\n",
                            chg_ftm_mode,chg_no_battery_powerup_mode);

    if( (TRUE == chg_ftm_mode) || (TRUE == chg_no_battery_powerup_mode) )
    {
        return TRUE;
    }

    /* ʹ�õ���¶��ж�Ŀǰ����Ƿ�Ϊ�γ�**/
    batt_temp = chg_get_temp_value(CHG_PARAMETER__BATT_THERM_DEGC);
    if (CHG_AUTO_CUR_CTRL_DIE_TEMP_MIN >= batt_temp)
    {
        batt_temp = chg_get_temp_value(CHG_PARAMETER__BATT_THERM_DEGC);
        if (CHG_AUTO_CUR_CTRL_DIE_TEMP_MIN >=  batt_temp)
        {
            batt_temp = chg_get_temp_value(CHG_PARAMETER__BATT_THERM_DEGC);
            if (CHG_AUTO_CUR_CTRL_DIE_TEMP_MIN >= batt_temp)
            {
                chg_print_level_message(CHG_MSG_ERR,"CHG_STM:batt_temp below 30 degree bat not present!\n");
                return FALSE;
            }
        }
    }

    return TRUE;

}

/**********************************************************************
�� �� ��  : chg_is_emergency_state
��������  : ��ѯ��ǰ�ĵ���Ƿ����쳣״̬���쳣������ظ���(>=58��)����ص͵�
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : TRUE: ��ظ��»��ߵ�ص͵磬�������ѯ
            FALSE: �����������
ע������  : �ޡ�
***********************************************************************/
boolean chg_is_emergency_state(void)
{
    if((chg_batt_high_temp_58_flag == TRUE) || (chg_batt_low_battery_flag == TRUE))
    {
        chg_batt_condition_error_flag = TRUE;
        chg_print_level_message(CHG_MSG_ERR,"CHG_STM:is_emergency_state!\n");
    }
    else
    {
        chg_batt_condition_error_flag = FALSE;
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:is not emergency state!\n");
    }

    return chg_batt_condition_error_flag;
}
/*****************************************************************************
 �� �� ��  : chg_batt_error_detect_temp
 ��������  : ��ز���λ�ػ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 *****************************************************************************/
void chg_batt_error_detect_temp(void)
{
    if(FALSE == chg_get_batt_id_valid())
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:batt invalid system shutdown!\n");
        mlog_print(MLOG_CHG, mlog_lv_fatal, "battery ts error detected.\n");

        chg_batt_error_handle();
    }

    return;
}
/*****************************************************************************
 �� �� ��  : chg_batt_error_detect_volt
 ��������  : ����عػ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
void chg_batt_error_detect_volt(void)
{
    int32_t  batt_volt = 0;
    boolean  batt_err_flag = FALSE;
    boolean  chg_ftm_mode = FALSE;
    boolean  chg_no_battery_powerup_mode = FALSE;

    /* ����ģʽ��һֱ��Ϊ���Ϊ�Ϸ����**/
    chg_ftm_mode = chg_is_ftm_mode();
    chg_no_battery_powerup_mode = chg_is_no_battery_powerup_enable();

    if( (TRUE == chg_ftm_mode) || (TRUE == chg_no_battery_powerup_mode) )
    {
        return;
    }

    /* ��ѯ��ص�ѹ,�����ص�ѹ���ڹ涨ֵ,�ж������*/
    batt_volt = chg_get_batt_volt_value();
    if (CHG_SHORT_CIRC_BATTERY_THRES > batt_volt)
    {
        batt_volt = chg_get_batt_volt_value();

        if (CHG_SHORT_CIRC_BATTERY_THRES > batt_volt)
        {
            batt_volt = chg_get_batt_volt_value();
            if (CHG_SHORT_CIRC_BATTERY_THRES > batt_volt)
            {
                batt_err_flag = TRUE;
            }
        }
    }

    if(TRUE == batt_err_flag)
    {
        chg_print_level_message(CHG_MSG_ERR,"CHG_STM:batt shorted system shutdown!\n");
        mlog_print(MLOG_CHG, mlog_lv_fatal, "battery short error detected.\n");
        chg_batt_error_handle();
    }

    return;
}


/*******************************************************************
Function:      chg_calc_average_temp_value
Description:   ����¶�ƽ��������
Data Accessed: ��
Data Updated:  ��
Input:         �²ɼ����¶�ֵ
Return:        ƽ������¶�ֵ
*******************************************************************/
static int32_t chg_calc_average_temp_value(int32_t new_data)
{
    int32_t    index = 0;
    int32_t    sum = 0;
    int32_t    bat_temp_avg = 0;
    int32_t    new_poll_mode;
    static int32_t  old_poll_mode = FAST_POLL_CYCLE;
    static int32_t record_avg_num_fast = 0;
    static int32_t record_avg_num_slow = 0;
    static int32_t record_value_fast[CHG_BAT_TEMP_SMOOTH_SAMPLE_FAST] = {0};
    static int32_t record_value_slow[CHG_BAT_TEMP_SMOOTH_SAMPLE_SLOW] = {0};

    /*��ѯ��ǰ��ѯģʽ*/
    new_poll_mode = chg_poll_timer_get();

    if(new_poll_mode != old_poll_mode)
    {
        if(FAST_POLL_CYCLE == new_poll_mode)/*������ѯ�л�������ѯ*/
        {
            for(index = 0;index < CHG_BAT_TEMP_SMOOTH_SAMPLE_FAST;index++)
            {
                record_value_fast[index] = chg_real_info.battery_temp;
            }
            record_avg_num_fast = CHG_BAT_TEMP_SMOOTH_SAMPLE_FAST;
        }
        else//�ɿ���ѯ�л�������ѯ
        {
            for(index = 0;index < CHG_BAT_TEMP_SMOOTH_SAMPLE_SLOW;index++)
            {
                record_value_slow[index] = chg_real_info.battery_temp;
            }
            record_avg_num_slow = CHG_BAT_TEMP_SMOOTH_SAMPLE_SLOW;
        }

        old_poll_mode = new_poll_mode;
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:new_poll_mode==old_poll_mode!\n");
    }

    if(FAST_POLL_CYCLE == new_poll_mode)/*����ѯģʽ*/
    {
        /*�����е�ǰԪ�ر��С��30*/
        if(CHG_BAT_TEMP_SMOOTH_SAMPLE_FAST > record_avg_num_fast)
        {
            record_value_fast[record_avg_num_fast] = new_data;
            record_avg_num_fast++;

            for(index = 0;index < record_avg_num_fast; index++)
            {
                sum += record_value_fast[index];
            }

            bat_temp_avg = sum / record_avg_num_fast;
        }
        else/*Ԫ�ظ�����Ŵ��ڵ���30��*/
        {
            record_value_fast[record_avg_num_fast % CHG_BAT_TEMP_SMOOTH_SAMPLE_FAST] = new_data;
            record_avg_num_fast++;

            for(index = 0;index < CHG_BAT_TEMP_SMOOTH_SAMPLE_FAST; index++)
            {
                sum += record_value_fast[index];
            }

            bat_temp_avg = sum / CHG_BAT_TEMP_SMOOTH_SAMPLE_FAST;

            /*���Ԫ�ظ�������Ǿ�̬���鳤�ȵ�����,������Ԫ�ظ�������Ǿ�̬���鳤�ȼ�CHG_BAT_TEMP_SMOOTH_SAMPLE*/
            if(CHG_BAT_TEMP_SMOOTH_SAMPLE_FAST * 2 == record_avg_num_fast)
            {
                record_avg_num_fast = CHG_BAT_TEMP_SMOOTH_SAMPLE_FAST;
            }
        }
    }
    else/*����ѯģʽ*/
    {
        /*�����е�ǰԪ�ر��С��5*/
        if(CHG_BAT_TEMP_SMOOTH_SAMPLE_SLOW > record_avg_num_slow)
        {
            record_value_slow[record_avg_num_slow] = new_data;
            record_avg_num_slow++;

            for(index = 0;index < record_avg_num_slow; index++)
            {
                sum += record_value_slow[index];
            }

            bat_temp_avg = sum / record_avg_num_slow;
        }
        else/*Ԫ�ظ�����Ŵ��ڵ���5��*/
        {
            record_value_slow[record_avg_num_slow % CHG_BAT_TEMP_SMOOTH_SAMPLE_SLOW] = new_data;
            record_avg_num_slow++;

            for(index = 0;index < CHG_BAT_TEMP_SMOOTH_SAMPLE_SLOW; index++)
            {
                sum += record_value_slow[index];
            }

            bat_temp_avg = sum / CHG_BAT_TEMP_SMOOTH_SAMPLE_SLOW;

            /*���Ԫ�ظ�������Ǿ�̬���鳤�ȵ�����,������Ԫ�ظ�������Ǿ�̬���鳤�ȼ�CHG_BAT_TEMP_SMOOTH_SAMPLE*/
            if(CHG_BAT_TEMP_SMOOTH_SAMPLE_SLOW * 2 == record_avg_num_slow)
            {
                record_avg_num_slow = CHG_BAT_TEMP_SMOOTH_SAMPLE_SLOW;
            }
        }
    }

    return bat_temp_avg;

}

/*******************************************************************
Function:      chg_huawei_set_temp
Description:   ����¶Ȳ�������������Ҫ���ݾ���Ĳ��Խ����Ʋ���������
               �˴�ֻ�ṩ�ӿڣ�����ʵ��ȡ���ڲ�Ʒʵ�ʲ��Խ����
Input:         ƽ������¶�ֵ
Return:        ��������¶�ֵ
*******************************************************************/
int32_t chg_huawei_set_temp(int32_t temp)
{
#if defined(BSP_CONFIG_BOARD_E5) || defined(BSP_CONFIG_BOARD_E5575S_210) \
    || defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5573S_156) \
    || defined(BSP_CONFIG_BOARD_E5577S_932) || defined(BSP_CONFIG_BOARD_E5573S_856) \
    || defined(BSP_CONFIG_BOARD_E5573S_853) || defined(BSP_CONFIG_BOARD_E5573S_607) \
    ||defined(BSP_CONFIG_BOARD_E5577CS_603) || defined(BSP_CONFIG_BOARD_E5577S_603) \
    || defined(BSP_CONFIG_BOARD_E5575S_320) || defined(BSP_CONFIG_BOARD_E5573CS) \
    || defined(BSP_CONFIG_BOARD_E5573BS) || defined(BSP_CONFIG_BOARD_E5573CS_933)\
    || defined(BSP_CONFIG_BOARD_E5577S_324) || defined(BSP_CONFIG_BOARD_607HW)\
    || defined(BSP_CONFIG_BOARD_E5577BS_937) || defined(BSP_CONFIG_BOARD_R218h)
    uint32_t batt_id = chg_get_batt_id();

    if(is_chg_charger_removed())/*���������λ*/
    {
#if defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577S_932) \
    || defined(BSP_CONFIG_BOARD_E5577S_324)
        if(ONLINE == g_exchg_online_flag)
        {
            switch(batt_id)
            {
                case CHG_BATT_ID_FEIMAOTUI_3000:
                case CHG_BATT_ID_LISHEN_3000:
                case CHG_BATT_ID_XINGWANGDA_3000:
                {
                    if((35 <= temp) && (temp <= 45))/*[34,45]*/
                    {
                        temp = temp - 2;/*����-2��*/
                    }
                    else if((46 <= temp) && (temp <= 63))/*[46,63]*/
                    {
                        temp = temp - 3;/*����-3��*/
                    }
                    break;
                }
                default:
                    break;
            }
            return temp;
        }
#endif
        switch(batt_id)
        {
            case CHG_BATT_ID_FEIMAOTUI:
            {
                if((35 <= temp) && (temp <= 63))/*[35,63]*/
                {
                    temp = temp - 1;/*����һ��*/
                }
                break;             
            }
            case CHG_BATT_ID_XINGWANGDA:
            case CHG_BATT_ID_LISHEN:
            default:
                break;  
        }              
    }
    else/*�������λ*/
    {
        switch(batt_id)
        {
            case CHG_BATT_ID_FEIMAOTUI:
            {
#if defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573S_156) \
    || defined(BSP_CONFIG_BOARD_E5573BS) || defined(BSP_CONFIG_BOARD_E5573CS_933)
                /* ������[56,63]����+2�Ȼᵼ�µ���c���¶�59��ʱa���¶ȵ���61��ֱ�ӹػ�
                �޵��߶����������޸ķ�ë�Ȳ��������������ﱣ��һ�£�ʵ������ɼ����� */
                if((35 <= temp) && (temp <= 57))/*[35,57]*/
                {
                    temp = temp + 2;/*��������*/
                }
#elif defined(BSP_CONFIG_BOARD_R218h)
                if((35 <= temp) && (temp <= 54))/*[35,54]*/
                {
                    temp = temp + 1;/*����һ��*/
                }
#else
                if((35 <= temp) && (temp <= 55))/*[35,55]*/
                {
                    temp = temp + 1;/*����һ��*/
                }
                else if((56 <= temp) && (temp <= 63))/*[56,63]*/
                {
                    temp = temp + 2;/*��������*/
                }
                else if(63 < temp)/*[63,)*/
                {
                    temp = temp + 1;/*����һ��*/
                }
#endif
                break;
            }
            case CHG_BATT_ID_XINGWANGDA:
            {
                if((35 <= temp) && (temp <= 57))/*[35,57]*/
                {
                    temp = temp + 2;/*��������*/
                }
                break;  
            }
            case CHG_BATT_ID_LISHEN:
            {
                if((35 <= temp) && (temp <= 63))/*[35,63]*/
                {
                    temp = temp + 2;/*��������*/
                }
                break;            
            }
            default:
                break;  
        }        
    }

#endif
    return temp;

}

/*******************************************************************
Function:       chg_temp_is_too_hot_or_too_cold_for_chg
Description:    ����¶��жϣ������¶ȳ�������±�������ʱ�����������±���״̬��ֹͣ��磻
                ���¶ȴ��ڻ��߻ָ��������¶����޷�Χʱ���ָ���硣
Calls:         ��
Data Accessed: ��
Data Updated:  ȫ�ֳ���±�����־
Input:         ��
Output:       ��
Return:       ��
Others:        ��
*******************************************************************/
void chg_temp_is_too_hot_or_too_cold_for_chg ( void )
{
    static uint32_t up_over_temp_flag = FALSE;
    static uint32_t low_over_temp_flag = FALSE;

    /*����±���ʹ�ܹر�*/
    if(0 == CHG_TEMP_PROTECT_ENABLE)
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:CHG_TEMP_PROTECT is disable!\n");
        chg_temp_protect_flag = FALSE;
        return;
    }
    else
    {
         chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:CHG_TEMP_PROTECT is enable!\n");
    }

    /*���¼��:���������λʱ���Գ���¶����쳣�ж�*/
    if (FALSE == chg_is_charger_present())
    {
        up_over_temp_flag = FALSE;
    }
    else if(FALSE == up_over_temp_flag)
    {   /*1�������³�繦�ܲ�Ʒͨ��NV50385������¶���������Ϊ55��
          2���������³�繦�ܲ�Ʒͨ��NV50385������¶���������Ϊ45��*/
        #if defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573BS)\
        ||defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_607HW) \
        || defined(BSP_CONFIG_BOARD_R218h)
        if (CHG_BATT_ID_DEF == chg_get_batt_id())
        {
            if(CHG_DEF_BATT_TEMP_OVER_THRES <= chg_real_info.battery_temp)
            {
                up_over_temp_flag = TRUE;
            }
        }
        else if(CHG_OVER_TEMP_STOP_THRESHOLD <= chg_real_info.battery_temp)
        {
            up_over_temp_flag = TRUE;
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:battery temp don't up_over_temp!\n");
        }
        #else
        if(CHG_OVER_TEMP_STOP_THRESHOLD <= chg_real_info.battery_temp)
        {
            up_over_temp_flag = TRUE;
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:battery temp don't up_over_temp!\n");
        }
        #endif
    }
    else
    {
          /*1�������³�繦�ܲ�Ʒͨ��NV50385������¶���������Ϊ52��
          2���������³�繦�ܲ�Ʒͨ��NV50385������¶���������Ϊ42��*/
        #if defined(BSP_CONFIG_BOARD_E5573CS) ||defined(BSP_CONFIG_BOARD_E5573BS) \
        || defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_607HW) \
        || defined(BSP_CONFIG_BOARD_R218h)
        if (CHG_BATT_ID_DEF == chg_get_batt_id())
        {
            if(CHG_DEF_BATT_TEMP_OVER_RUSUM_THRES > chg_real_info.battery_temp)
            {
                up_over_temp_flag = FALSE;
            }
        }
        else if(CHG_OVER_TEMP_RESUME_THRESHOLD > chg_real_info.battery_temp)
        {
            up_over_temp_flag = FALSE;
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:battery up temp don't resume nomal!\n");
        }
        #else
        if(CHG_OVER_TEMP_RESUME_THRESHOLD > chg_real_info.battery_temp)
        {
            up_over_temp_flag = FALSE;
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:battery up temp don't resume nomal!\n");
        }
        #endif
    }

    /*���¼��:���������λʱ���Գ���¶����쳣�ж�*/
    if (FALSE == chg_is_charger_present())
    {
        low_over_temp_flag = FALSE;
    }
    else if(FALSE == low_over_temp_flag)
    {
        /*��һ��������¶�С��0�ȵ���ͣ��*/
        if(CHG_LOW_TEMP_STOP_THRESHOLD > chg_real_info.battery_temp)
        {
            low_over_temp_flag = TRUE;
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:battery temp don't low_over_temp!\n");
        }
    }
    else
    {
        /*��һ��������¶ȴ��ڵ���3�Ȼָ����³��*/
        if(CHG_LOW_TEMP_RESUME_THRESHOLD <= chg_real_info.battery_temp)
        {
            low_over_temp_flag = FALSE;
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:battery low temp don't resume nomal!\n");
        }
    }

    /*���ݸߵ��¼�����жϳ���±���״̬*/
    if((up_over_temp_flag == TRUE) || (low_over_temp_flag == TRUE))
    {
        chg_temp_protect_flag = TRUE;
    }
    else
    {
        chg_temp_protect_flag = FALSE;
    }
}
/*******************************************************************
Function:      chg_set_supply_current_by_temp
Description:   �±����󣬸����¶�����ǰ������
Data Accessed: none
Data Updated:  none
Input:         none
Return:        noee
*******************************************************************/
void chg_set_supply_current_by_temp(void)
{
    chg_chgr_type_t cur_chgr_type = chg_stm_get_chgr_type();
    chg_stm_state_type curr_state = chg_stm_get_cur_state();
    uint8_t need_resume_supply = 0;
    uint8_t curr_limit;
    /*֧�ֿ�ά�ɲ�*/
    if( TRUE == chg_is_ftm_mode() \
        || TRUE == chg_is_no_battery_powerup_enable() 
        || (0 == CHG_TEMP_PROTECT_ENABLE))
    {
        return;
    }

    if( TRUE == chg_is_powdown_charging())/*�ػ����ģʽ*/
    {
        return;
    }

#if( FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT )
    if( TRUE == chg_battery_protect_flag )
    {
        if(TRUE == chg_limit_supply_current_flag)
        {
            chg_limit_supply_current_flag = FALSE;
        }
        return;
    }
#endif

    if(TRUE == is_chg_charger_removed())
    {
        if(TRUE == chg_limit_supply_current_flag)
        {
            chg_limit_supply_current_flag = FALSE;
        }
        return;
    }
    
    if((chg_real_info.battery_temp >= LIMIT_SUPPLY_CURR_TEMP) 
        && (FALSE == chg_limit_supply_current_flag))
    {
        chg_limit_supply_current_flag = TRUE;
    }
    else if((chg_real_info.battery_temp <= LIMIT_SUPPLY_CURR_TEMP - LIMIT_SUPPLY_CURR__RESUME_LEN) 
        && (TRUE == chg_limit_supply_current_flag))
    {
        chg_limit_supply_current_flag = FALSE;
        need_resume_supply = 1;
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:resume supply current in high temp!\n");
    }

    if(TRUE == chg_limit_supply_current_flag)
    {
        curr_limit = chg_get_supply_limit();
        if(BQ24192_IINLIMIT_100 != curr_limit)
        {
            chg_set_supply_limit(CHG_IINPUT_LIMIT_100MA);
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:set supply current in high temp!\n");
        }

    }
    else
    {
        if(need_resume_supply)
        {
            switch(cur_chgr_type)
            {
                case CHG_WALL_CHGR:
                {
                    chg_set_supply_limit(chg_std_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
                        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:resume supply current:%d\n",
                            chg_std_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
                    break;
                }

                case CHG_USB_HOST_PC:
                {
                    if(CHG_CURRENT_SS == usb_speed_work_mode())
                    {
                        chg_set_supply_limit(chg_usb3_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
                        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:resume supply current:%d\n",
                            chg_usb3_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
                    }
                    else
                    {
                        chg_set_supply_limit(chg_usb_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
                        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:resume supply current:%d\n",
                            chg_usb_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
                    }
                    break;
                }
                case CHG_500MA_WALL_CHGR:
                case CHG_NONSTD_CHGR:
                {
                    chg_set_supply_limit(chg_usb_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
                        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:resume supply current:%d\n",
                            chg_usb_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
                    break;
                }
                default:
                break;
            }
        }
    }
}


boolean chg_temp_protect_eixt_suspend_mode(void)
{
    boolean ret = TRUE;
    /*�Ƿ������˳�suspend����*/
#if ( FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT )
    chg_print_level_message(CHG_MSG_DEBUG, \
        "CHG_STM:chg_temp_protect_eixt_suspend_mode chg_battery_protect_flag is %d!\r\n", chg_battery_protect_flag);
#endif

#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
    chg_print_level_message(CHG_MSG_DEBUG, \
        "CHG_STM:chg_usb_temp_info.usb_temp_protect_cur_stat chg_battery_protect_flag is %d!\r\n",\
        chg_usb_temp_info.usb_temp_protect_cur_stat);
#endif

#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT ) && (FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT )
    if ( (FALSE == chg_battery_protect_flag) && (FALSE == chg_usb_temp_info.usb_temp_protect_cur_stat) )
    {
        ret = chg_set_suspend_mode(FALSE);
    }
#else
    ret = chg_set_suspend_mode(FALSE);
#endif

    return ret;
}

#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )

static void chg_usb_over_temp_protect_enter_process(void)
{
    /*1.���ó��оƬ����suspend��2.����POWER_SUPPLY�ڵ㡣3.mlog��*/
    if ( TRUE != chg_set_suspend_mode(TRUE) )
    {
        chg_usb_temp_info.usb_temp_protect_cur_stat = FALSE;
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Set charge IC to suspend fail in usb high temp!\n");
#if ( FEATURE_ON == MBB_MLOG )
        mlog_print(MLOG_CHG, mlog_lv_error, "CHG_DCM: Set charge IC to suspend fail in usb temp %d.\n",
            chg_usb_temp_info.usb_cur_temp);
#endif
        return;
    }
    chg_usb_temp_info.usb_temp_protect_pre_stat = chg_usb_temp_info.usb_temp_protect_cur_stat;
    chg_stm_state_info.usb_heath_type = POWER_SUPPLY_USB_TEMP_DEAD;
    chg_send_stat_to_app((uint32_t)DEVICE_ID_USB, (uint32_t)USB_TEMP_HIGH);
    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Set charge IC to suspend in usb high temp!\n");
#if ( FEATURE_ON == MBB_MLOG )
    printk(KERN_ERR "CHG_STM:USBPortOverTempCnt\n");
    mlog_set_statis_info("USBPortOverTempCnt",1);/*USB�±�ǰ����������+1*/
    mlog_print(MLOG_CHG, mlog_lv_error, "CHG_DCM: Entry usb temp protect in usb temp %d.\n",
            chg_usb_temp_info.usb_cur_temp);
#endif/*MBB_MLOG*/
    return;
}

static void chg_usb_over_temp_protect_exit_process(void)
{
    /*1.���ó��оƬ�˳�suspend*/
    if ( TRUE != chg_temp_protect_eixt_suspend_mode() )
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Set charge IC to suspend is fail in usb high temp!\n");
#if (FEATURE_ON == MBB_MLOG)
        mlog_print(MLOG_CHG, mlog_lv_error, "CHG_DCM: Set charge IC to suspend is fail in usb temp %d.\n",
            chg_usb_temp_info.usb_cur_temp);
#endif
        return;
    }

    /*1.���ݵ�ǰ״̬�ָ����������2.����POWER_SEPPLY�ڵ㡣3.mlog��*/
    chg_set_supply_limit_by_stm_stat();
    chg_usb_temp_info.usb_temp_protect_pre_stat = chg_usb_temp_info.usb_temp_protect_cur_stat;
    chg_stm_state_info.usb_heath_type = POWER_SUPPLY_USB_TEMP_GOOD;
    chg_send_stat_to_app((uint32_t)DEVICE_ID_USB, (uint32_t)USB_TEMP_NORMAL);
    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Resume charge IC from suspend in usb high temp!\n");
#if (FEATURE_ON == MBB_MLOG)
    mlog_print(MLOG_CHG, mlog_lv_error, "CHG_STM: Resume usb temp protect in usb temp %d.\n",
            chg_usb_temp_info.usb_cur_temp);
#endif
    return;
}

void chg_usb_temp_protect_proc(void)
{
    int32_t         usb_temp = TEMP_INITIAL_VALUE;
    int32_t         usb_temp_detect_count_t = USB_TEMP_DETECT_COUNT;

    /*��ȡ��ǰ�¶�ֵ*/
    usb_temp = chg_get_temp_value(CHG_PARAMETER__USB_PORT_TEMP_DEGC);
    chg_usb_temp_info.usb_cur_temp = usb_temp;

    /*����±���ʹ�ܹر�*/
    if (0 == CHG_TEMP_PROTECT_ENABLE)
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:CHG_TEMP_PROTECT is disable!\n");
        chg_usb_temp_info.usb_temp_protect_cur_stat = FALSE;
        return;
    }

    /*�ж������¶�ֵ�Ƿ���ϴ����ͻָ����ޣ�������Ӧ����.*/
    if ( FALSE == chg_usb_temp_info.usb_temp_protect_cur_stat)
    {
        while ( --usb_temp_detect_count_t )
        {
            if ( CHG_USB_TEMP_LIMIT > usb_temp )
            {
                break;
            }
            usb_temp = chg_get_temp_value(CHG_PARAMETER__USB_PORT_TEMP_DEGC);
        }
        if ( 0 == usb_temp_detect_count_t )
        {
            chg_usb_temp_info.usb_temp_protect_cur_stat = TRUE;
        }
    }
    else
    {
        while ( --usb_temp_detect_count_t )
        {
            if ( CHG_USB_TEMP_RESUME < usb_temp )
            {
                break;
            }
            usb_temp = chg_get_temp_value(CHG_PARAMETER__USB_PORT_TEMP_DEGC);
        }
        if ( 0 == usb_temp_detect_count_t )
        {
            chg_usb_temp_info.usb_temp_protect_cur_stat = FALSE;
        }
    }
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:usb_cur_temp=%d\n",chg_usb_temp_info.usb_cur_temp);
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:usb_temp_protect_stat=%d\n",
            chg_usb_temp_info.usb_temp_protect_cur_stat);
    /*�жϵ�ǰ����״̬,������Ӧ����*/
    if ( chg_usb_temp_info.usb_temp_protect_cur_stat != chg_usb_temp_info.usb_temp_protect_pre_stat )
    {
        if ( TRUE == chg_usb_temp_info.usb_temp_protect_cur_stat )
        {
            chg_usb_over_temp_protect_enter_process();
        }
        else
        {
            chg_usb_over_temp_protect_exit_process();
        }
    }
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:Set usb port stat by temp finish!\n");
}

int32_t chg_get_usb_health(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_health=%d\n",chg_stm_state_info.bat_heath_type);
    return chg_stm_state_info.usb_heath_type;
}

int32_t chg_get_usb_cur_temp(void)
{
    if ( TEMP_INITIAL_VALUE == chg_usb_temp_info.usb_cur_temp )
    {
        chg_usb_temp_info.usb_cur_temp = chg_get_temp_value(CHG_PARAMETER__USB_PORT_TEMP_DEGC);
    }
    return chg_usb_temp_info.usb_cur_temp;
}

boolean chg_get_usb_temp_protect_stat(void)
{
    return chg_usb_temp_info.usb_temp_protect_cur_stat;
}
#endif
#if ( FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT )

static boolean chg_battery_protect_enter_process(void)
{

    /*��֧��suspend��ʹ��ǰ������100MA*/
    if (TRUE != chg_set_supply_limit(CHG_IINPUT_LIMIT_100MA))
    {
        chg_print_level_message(CHG_MSG_ERR,"CHG_STM:Set supply current 100MA is fail in battery protect!\n");
        return FALSE;
    }

    return TRUE;
}


static void chg_battery_protect_exit_process(void)
{
    chg_chgr_type_t cur_chgr_type = CHG_CHGR_INVALID;
    chg_stm_state_type curr_state = chg_stm_get_cur_state();

    /*curr_stateҪ��Ϊ�����±��������������������Ҫ�ж�һ�ºϷ��ԡ�*/
    if (curr_state <= CHG_STM_INIT_ST || curr_state >= CHG_STM_MAX_ST)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Invalid state %d in %s.\n", 
            curr_state, __func__);
        return;
    }

    cur_chgr_type = chg_stm_get_chgr_type();
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:battery protect resume!\n");
    switch(cur_chgr_type)
    {
        case CHG_WALL_CHGR:
        {
            chg_set_hardware_parameter(&chg_std_chgr_hw_paras[curr_state]);
            break;
        }
        case CHG_USB_HOST_PC:
        {
            if(CHG_CURRENT_SS == usb_speed_work_mode())
            {
                chg_set_hardware_parameter(&chg_usb3_chgr_hw_paras[curr_state]);
            }
            else
            {
                chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[curr_state]);
            }
            break;
        }
        case CHG_500MA_WALL_CHGR:
        case CHG_NONSTD_CHGR:
        case CHG_CHGR_UNKNOWN:
        {
            chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[curr_state]);
            break;
        }
        default:
        {
            break;
        }
    }

}


static void chg_poll_volt_temp_protect_state(void)
{
    chg_chgr_type_t cur_chgr_type = CHG_CHGR_INVALID;
    cur_chgr_type = chg_stm_get_chgr_type();

    /*������ͱ���TBAT>=45��and VBAT >=4.1V ״̬��ѯ*/
    if ((FALSE == g_chg_over_temp_volt_protect_flag)
        && (chg_get_sys_batt_temp () >= CHG_BATTERY_PROTECT_TEMP)
        && (chg_get_sys_batt_volt () >= CHG_BATTERY_PROTECT_VOLTAGE))
    {
        g_chg_over_temp_volt_protect_flag = TRUE;
        /*���¸�ѹ����������ͱ���+1*/
        mlog_set_statis_info("BattExpandOverTempVoltCnt",1);
    }
    else if ((TRUE == g_chg_over_temp_volt_protect_flag)
            && ((chg_get_sys_batt_temp () < CHG_BATTERY_PROTECT_RESUME_TEMP)
            || (chg_get_sys_batt_volt () < CHG_BATTERY_PROTECT_RESUME_VOLTAGE)))
    {
        g_chg_over_temp_volt_protect_flag = FALSE;
    }
    else
    {
        /*do nothing*/
    }
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:g_chg_over_temp_volt_protect_flag is %d!\n",
            g_chg_over_temp_volt_protect_flag);
}


uint32_t chg_stm_get_no_charging_charger_lasted_time(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:charger_lasted_without_charging_in_seconds=%u\n",\
                    chg_stm_state_info.charger_lasted_without_charging_in_seconds);
    /*1. Return the current time.*/
    return chg_stm_state_info.charger_lasted_without_charging_in_seconds;
}


void set_long_time_no_charge_protect_recharge_volt(void)
{
    /*��ʱ���Դ��λ�������뱣�����޸ĳ��¸�������Ϊ4.0v*/
    g_chgBattVoltProtect.battNormalTempChgRechargeThreshold = BATT_NORMAL_TEMP_RECHARGE_THR_LONG_TIME_NO_CHARGE;
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
    g_chg_batt_expand_change_normal_rechg_flag = TRUE;
#endif
}


void resume_long_time_no_charge_protect_recharge_volt(void)
{
    /*��Դ�γ��󣬻ָ����¸�������Ϊ4.2v*/
    g_chgBattVoltProtect.battNormalTempChgRechargeThreshold = g_batt_normal_temp_recherge_threshold;
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
    g_chg_batt_expand_change_normal_rechg_flag = FALSE;
#endif
}


static void chg_poll_long_time_no_charge_state(void)
{
    uint32_t charger_lasted_time = 0;
    chg_chgr_type_t cur_chgr_type = CHG_CHGR_INVALID;
    cur_chgr_type = chg_stm_get_chgr_type();
    /*ͣ���ҳ������λ��ʱ��*/
    charger_lasted_time = chg_stm_get_no_charging_charger_lasted_time();

    /*������ͱ����������λ����>=16H�Ҳ����״̬��ѯ*/
    if ((FALSE == g_chg_longtime_nocharge_protect_flag)
        && (charger_lasted_time >= CHG_BATTERY_PROTECT_CHGER_TIME_THRESHOLD_IN_SECONDS)
        && (chg_get_sys_batt_volt () >= CHG_BATTERY_PROTECT_VOLTAGE))
    {
        g_chg_longtime_nocharge_protect_flag = TRUE;
        /*��ʱ���Դ��λ�������뱣�����޸ĳ��¸�������Ϊ4.0v*/
        (void)set_long_time_no_charge_protect_recharge_volt();
        /*USB��ʱ����λ����������ͱ���+1*/
        mlog_set_statis_info("BattExpandLongTimeCnt",1);
    }
    else if ((TRUE == g_chg_longtime_nocharge_protect_flag)
            && (chg_get_sys_batt_volt () < CHG_BATTERY_PROTECT_RESUME_VOLTAGE))
    {
        g_chg_longtime_nocharge_protect_flag = FALSE;
    }
    else
    {
        /*do nothing*/
    }
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:g_chg_longtime_nocharge_protect_flag is %d!\n",
            g_chg_longtime_nocharge_protect_flag);
}


static void chg_battery_protect_proc(void)
{
    chg_chgr_type_t cur_chgr_type = CHG_CHGR_INVALID;
    chg_stm_state_type curr_state = CHG_STM_INIT_ST;
    cur_chgr_type = chg_stm_get_chgr_type();
    curr_state = chg_stm_get_cur_state();
    /*֧�ֿ�ά�ɲ�*/
    if ( (TRUE == chg_is_ftm_mode() ) \
        || (TRUE == chg_is_no_battery_powerup_enable() ) \
        || (0 == CHG_TEMP_PROTECT_ENABLE))
    {
        chg_battery_protect_flag = FALSE;
        g_chg_over_temp_volt_protect_flag = FALSE;
        g_chg_longtime_nocharge_protect_flag = FALSE;
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
        g_chg_batt_expand_change_normal_rechg_flag = FALSE;
#endif
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:In FTM mode or TEMP PROTECT DISABLE do not enable battery protect!\n");
        return;
    }

    /*��Դ�γ����˳�������ͱ���*/
    if (TRUE == is_chg_charger_removed())
    {
        if (TRUE == chg_battery_protect_flag)
        {
            chg_battery_protect_flag = FALSE;
            g_chg_over_temp_volt_protect_flag = FALSE;
            g_chg_longtime_nocharge_protect_flag = FALSE;
            (void)chg_battery_protect_exit_process();
        }
        (void)resume_long_time_no_charge_protect_recharge_volt();

        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:charger remove disenable battery protect!\n");
        return;
    }

    if (FALSE == chg_battery_protect_flag)
    {
        /*����ͣ���Ž���Suspend/��������100mA*/
        if ( (curr_state != CHG_STM_MAINT_ST) || (BATT_CAPACITY_FULL != chg_real_info.bat_capacity) )
        {
                chg_print_level_message(CHG_MSG_INFO,
                    "CHG_STM:battery is not in full state, no need to protect!\n");
                return;
        }
    }
#if (MBB_BATT_EXPAND_HTEMP_DISCHG == FEATURE_ON)
    /*��ѯ����״̬*/
    (void)chg_poll_volt_temp_protect_state();
#endif
#if (MBB_BATT_EXPAND_LTIME_DISCHG == FEATURE_ON)
    (void)chg_poll_long_time_no_charge_state();
#endif

    /*���ֱ�����һ�����������뱣��*/
    if ( (TRUE == g_chg_over_temp_volt_protect_flag)
        || (TRUE == g_chg_longtime_nocharge_protect_flag) )
    {
        if (FALSE == chg_battery_protect_flag)
        {
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:meet battery protect condition do battery protect!\n");
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:g_chg_over_temp_volt_protect_flag is %d!\n",
                g_chg_over_temp_volt_protect_flag);
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:g_chg_longtime_nocharge_protect_flag is %d!\n",
                g_chg_longtime_nocharge_protect_flag);
            if( TRUE != chg_battery_protect_enter_process() )
            {
                return;
            }
            chg_battery_protect_flag = TRUE;
            /*���������ͱ���+1*/
            mlog_set_statis_info("BattExpandProtectCnt",1);
            mlog_print(MLOG_CHG, mlog_lv_error, 
                    "CHG_STM: Entry battery expand protect by OverTempVolt:%d LongTime %d.\n",
                            g_chg_over_temp_volt_protect_flag,g_chg_longtime_nocharge_protect_flag);
        }
    }
    else
    {
        if (TRUE == chg_battery_protect_flag)
        {
            chg_battery_protect_flag = FALSE;
            chg_battery_protect_exit_process();
            chg_print_level_message(CHG_MSG_ERR,"CHG_STM:To resume from battery expand protect.\n");
            mlog_print(MLOG_CHG, mlog_lv_error,"CHG_STM: To resume from battery expand protect.\n");
        }
    }
}
#endif

/*******************************************************************
Function:       Chg_temp_is_too_hot_or_too_cold_for_shutoff
Description:   ����¶��жϣ������¶ȳ����ػ�����ʱ�����ùػ������ӿڣ����ָ��º͵��¡�
Calls:         �ޣ�
Return:        ��
*******************************************************************/
void chg_temp_is_too_hot_or_too_cold_for_shutoff(void)
{
    static uint32_t countNum = 0;
    static uint32_t high_temp_58_flag = FALSE;
    static uint32_t high_timer_flag = FALSE;
    static uint32_t low_timer_flag = FALSE;
#if !defined(BSP_CONFIG_BOARD_E5771S_852) && !defined(BSP_CONFIG_BOARD_E5771H_937)
    static uint32_t up_over_temp_shutoff_falg = FALSE;
    static uint32_t low_over_temp_shutoff_falg = FALSE;
#endif

    /*��Ƭ�汾��������*/
    /*��ά�ɲ�:�޵�ؿ���ʹ��*/
    if( TRUE == chg_is_ftm_mode() \
        || TRUE == chg_is_no_battery_powerup_enable() )
    {
        return;
    }

    /*�������ڿ���״̬�£��¶ȸ��ڵ���(�ػ��¶�-2��)ʱ�ϱ���Ӧ�ã��澯��ʾ*/
    if( FALSE == chg_is_powdown_charging())/*����ģʽ*/
    {
        if(chg_real_info.battery_temp >= (SHUTOFF_OVER_TEMP_SHUTOFF_THRESHOLD - SHUTOFF_HIGH_TEMP_WARN_LEN))
        {
            if(FALSE == high_temp_58_flag)
            {
                chg_batt_high_temp_58_flag = TRUE;
                /*�л���ѯ��ʽ�����½������ѯģʽ*/
                chg_poll_timer_set(FAST_POLL_CYCLE);
                high_temp_58_flag = TRUE;
            }
            else
            {
                chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:TEMP_BATT below 58 degree!\n");
            }

            /*�ϱ�APP�����¸澯��ʾ���ϱ�5�Σ����⿪�������£�APP���������ղ�����Ϣ*/
            if(BATTERY_EVENT_REPORT_TIMES >= countNum)
            {
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:send app msg with TEMP_BATT_HIGH \n ");

                chg_batt_temp_state = TEMP_BATT_HIGH;
                chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_OVERHEAT;
                chg_send_stat_to_app((uint32_t)DEVICE_ID_TEMP, (uint32_t)TEMP_BATT_HIGH);

                mlog_print(MLOG_CHG, mlog_lv_warn, "Battery over-heated WARNING!!\n");
                mlog_print(MLOG_CHG, mlog_lv_info, "Current Battery Info: [vBat]%dmV, " \
                    "[vBat_sys]%dmV, [tBat]%d'C, [tBat_sys]%d'C.\n", 
                    chg_real_info.battery_one_volt, chg_real_info.battery_volt,
                    chg_real_info.battery_one_temp, chg_real_info.battery_temp);
            }
            else
            {
                chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:TEMP_BATT_HIGH event report below 5 times!\n");
            }

            countNum++;
        }
        /*�������ڿ���״̬�£��¶ȵ��ڵ���(�ػ��¶�-5��)ʱ�ϱ���Ӧ�ã�ȡ���澯*/
        else if((chg_real_info.battery_temp <= (SHUTOFF_OVER_TEMP_SHUTOFF_THRESHOLD - SHUTOFF_HIGH_TEMP_RESUME_LEN)))
        {
            if(TRUE == high_temp_58_flag)
            {
                chg_batt_high_temp_58_flag = FALSE;
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:send app msg with TEMP_BATT_NORMAL \n ");
                chg_batt_temp_state = TEMP_BATT_NORMAL;
                chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_GOOD;
                chg_send_stat_to_app((uint32_t)DEVICE_ID_TEMP, (uint32_t)TEMP_BATT_NORMAL);
                high_temp_58_flag = FALSE;
                countNum = 0;
            }
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:TEMP_BATT_HIGH!\n");
        }
    }
    else
    {
        /*�ػ�״̬��������*/
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:System in power down chging do nothing!\n");
    }


    /*�¶ȹػ����------���¼��*/
    if(SHUTOFF_OVER_TEMP_SHUTOFF_THRESHOLD <= chg_real_info.battery_temp)
    {
        if(TRUE == SHUTOFF_OVER_TEMP_PROTECT_ENABLE)
        {
            if( FALSE == chg_is_powdown_charging() )/*����ģʽ*/
            {
                up_over_temp_shutoff_falg = TRUE;

                /*todo �ϱ�APPִ�и��¹ػ��������԰����ػ���ʽ�ϱ�*/
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:send MSG to app for high temp power off  \n ");
                chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_DEAD;
                chg_send_stat_to_app((uint32_t)DEVICE_ID_KEY, (uint32_t)GPIO_KEY_POWER_OFF);

                mlog_print(MLOG_CHG, mlog_lv_warn, "Battery Over-heated, system down!!!\n");
                mlog_print(MLOG_CHG, mlog_lv_info, "Current Battery Info: [vBat]%dmV, " \
                    "[vBat_sys]%dmV, [tBat]%d'C, [tBat_sys]%d'C.\n",
                    chg_real_info.battery_one_volt, chg_real_info.battery_volt,
                    chg_real_info.battery_one_temp, chg_real_info.battery_temp);

                if(FALSE == high_timer_flag)
                {
                    high_timer_flag = TRUE;

                    /*������ʱ�����ص�����Ϊ�ػ���������ʱʱ��Ϊ15�룻*/
                    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:begin 15s timer for high temp power off \n ");
                    chg_bat_timer_set( OVER_TEMP_SHUTOFF_DURATION, \
                    chg_set_power_off, DRV_SHUTDOWN_TEMPERATURE_PROTECT);
                }
                else
                {
                    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:Already start power off timer!\n");
                }
            }
            else //�ػ�ģʽ
            {
                /* �ػ����>=65���ϱ�  */
                #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
                if (FALSE == is_chg_charger_removed())
                {
                    up_over_temp_shutoff_falg = TRUE;
                    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:pd charge send app high temp power off\n ");
                    chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_DEAD;
                    chg_send_stat_to_app((uint32_t)DEVICE_ID_KEY, (uint32_t)GPIO_KEY_POWER_OFF);
                }
                #else
                /*�ػ�ģʽ�µ��¶ȸ��ڹػ����ޣ���������*/
                chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:high temp but power down chging do nothing!\n");
                #endif
            }
        }
        else
        {
             chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Disable high temp protect!\n");
        }
    }
    #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
    /* �ػ���� < 63 ���ϱ�  */
    if(chg_real_info.battery_temp < SHUTOFF_OVER_TEMP_SHUTOFF_THRESHOLD - SHUTOFF_HIGH_TEMP_WARN_LEN )
    {
        if (FALSE == is_chg_charger_removed())
        {
            if( TRUE == chg_is_powdown_charging() && up_over_temp_shutoff_falg == TRUE)
            {   
                up_over_temp_shutoff_falg = FALSE;
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:pdcharge send app hightemp back off\n ");
                chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_GOOD;
                chg_send_stat_to_app((uint32_t)DEVICE_ID_TEMP, (uint32_t)TEMP_BATT_NORMAL);
            }
        }
    }
    #endif

    /*�¶ȹػ����------���¼��*/
    if(SHUTOFF_LOW_TEMP_SHUTOFF_THRESHOLD >= chg_real_info.battery_temp)
    {
        if(TRUE == SHUTOFF_LOW_TEMP_PROTECT_ENABLE)
        {
            if( FALSE == chg_is_powdown_charging() )/*����ģʽ*/
            {
                low_over_temp_shutoff_falg = TRUE;
                /*�ϱ�APPִ�е��¹ػ�����*/
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:send MSG to app for low temp power off  \n ");

                chg_batt_temp_state = TEMP_BATT_LOW;
                chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_COLD;
                chg_send_stat_to_app((uint32_t)DEVICE_ID_TEMP, (uint32_t)TEMP_BATT_LOW);

                mlog_print(MLOG_CHG, mlog_lv_warn, "Battery too Cold, system down!!!\n");
                mlog_print(MLOG_CHG, mlog_lv_info, "Current Battery Info: [vBat]%dmV, " \
                    "[vBat_sys]%dmV, [tBat]%d'C, [tBat_sys]%d'C.\n",
                    chg_real_info.battery_one_volt, chg_real_info.battery_volt,
                    chg_real_info.battery_one_temp, chg_real_info.battery_temp);

                if(FALSE == low_timer_flag )
                {
                    low_timer_flag = TRUE;
                    /*��ʱ����ʱ15�룬��15��ʱ�䵽��APP��δ�ػ�����ײ��Լ�ִ�йػ�������*/
                    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:begin 15s timer for low temp power off \n ");
                    chg_bat_timer_set( OVER_TEMP_SHUTOFF_DURATION, \
                    chg_set_power_off,DRV_SHUTDOWN_LOW_TEMP_PROTECT);
                }
            }
            else
            {
                #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
                if (FALSE == is_chg_charger_removed())
                {
                    low_over_temp_shutoff_falg = TRUE;
                    /* �ػ����<=-20���ϱ�  */
                    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:pdcharge send app lowtemp power off  \n ");
                    chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_COLD;
                    chg_send_stat_to_app((uint32_t)DEVICE_ID_TEMP, (uint32_t)TEMP_BATT_LOW);
                }
                #else
                /*�ػ�ģʽ�µ��¶ȵ��ڹػ����ޣ���������*/
                chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:low temp but power down chging do nothing!\n");
                #endif
            }
        }
        else
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Disable low temp protect!\n");
        }
    }
    #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
    if(chg_real_info.battery_temp > SHUTOFF_LOW_TEMP_SHUTOFF_THRESHOLD + SHUTOFF_HIGH_TEMP_WARN_LEN )
    {    /* �ػ����> -18���ϱ�  */
        if (FALSE == is_chg_charger_removed())
        {
            if( TRUE == chg_is_powdown_charging() && low_over_temp_shutoff_falg == TRUE)
            {
                low_over_temp_shutoff_falg = FALSE;
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:pdcharge send app lowtemp back off\n ");
                chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_GOOD;
                chg_send_stat_to_app((uint32_t)DEVICE_ID_TEMP, (uint32_t)TEMP_BATT_NORMAL);
            }
        }
    }
    #endif
}

/*******************************************************************
Function:      chg_poll_batt_temp
Description:   ����¶�ֵ�ӹ���������̿��ƺ�����
Calls:          chg_get_parameter_level-----------------�ɼ��¶�ֵ�ӿں�����
                chg_calc_average_temp_value-------------ƽ���㷨��������
                chg_huawei_set_temp----------------------�¶Ȳ�������
                chg_temp_is_too_hot_or_too_cold_for_chg ----------����±������¶ȼ�⺯��
                chg_temp_is_too_hot_or_too_code_for_shutoff------�¶ȹػ�������⺯��
Data Accessed: ��
Data Updated:  ȫ�ֱ������¶�ֵ
Input:          ��
Output:         ��
Return:         ��
*******************************************************************/
void chg_poll_batt_temp(void)
{
    int32_t new_one_batt_temp = 0;
    int32_t new_batt_temp = 0;
    static uint32_t init_flag = FALSE;

    /*����ؼ�⴦����*/
    chg_batt_error_detect_temp();

    /*���ò�����ȡ�ӿں�����ȡ��ѹֵ*/
    new_one_batt_temp = chg_get_temp_value(CHG_PARAMETER__BATT_THERM_DEGC);

    #if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    new_one_batt_temp = chg_batt_temp_revise(new_one_batt_temp);//����¶Ȳ���
    #endif

    /*���浥�βɼ����¶�ֵ��ȫ�ֱ�����*/
    chg_real_info.battery_one_temp = new_one_batt_temp;

    /*���ƽ���¶ȳ�ʼ��Ϊ�״βɼ�ֵ*/
    if(FALSE == init_flag)
    {
        chg_real_info.battery_temp = chg_real_info.battery_one_temp;
        init_flag = TRUE;
    }
    /*�����¶Ȳ��������Ե��βɼ����¶Ƚ��в�������ͬƽ̨���¶Ȳ���Ҫ��ͬ
      �е�Ҫ�󲹳�ƽ������¶ȣ��е�Ҫ�󲹳�ƽ��ǰ���¶ȣ�9X25������Ե���
      ����¶Ƚ��в��������ɾ���±ߵ�ƽ���¶Ȳ���*/
    new_one_batt_temp = chg_huawei_set_temp(new_one_batt_temp);

    /*����ƽ���㷨�Ե�ǰ����¶Ƚ���ƽ������*/
    new_batt_temp = chg_calc_average_temp_value(new_one_batt_temp);

    /*�����¶Ȳ����������ж�ƽ������¶Ƚ��в���*/
    //new_batt_temp = chg_huawei_set_temp(new_batt_temp);

#if defined(BSP_CONFIG_BOARD_607HW)
    /*������¶ȷ����仯ʱ����ʱ֪ͨӦ�ò�ѯ����¶�*/
    if ( chg_real_info.battery_temp != new_batt_temp )
    {
        /*������¶ȷ����仯ʱ,���ȱ������»�ȡ���¶�ֵ��ȫ�ֱ�����,ȷ��Ӧ�ò�ѯ����һ�������µ��¶�ֵ*/
        chg_real_info.battery_temp = new_batt_temp;
        chg_send_stat_to_app((uint32_t)DEVICE_ID_TEMP, (uint32_t)CHG_EVENT_NONEED_CARE);
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM: curr_batt_temp=%d\n",new_batt_temp);
    }
#endif

    /*�������ջ�ȡ���¶�ֵ��ȫ�ֱ�����*/
    chg_real_info.battery_temp = new_batt_temp;

    /*���ó���±������¶ȼ�⺯��ִ��*/
    chg_temp_is_too_hot_or_too_cold_for_chg ( );

    /* log��ӡ�ӿڣ���ά�ɲ���������*/
    chg_print_level_message(CHG_MSG_DEBUG, "**********CHG TEMP PARA: chg_poll_batt_temp  begin *********\n");

    /*��ӡ����±���ʹ�ܿ���*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg temp protect enable flag = %d\n", CHG_TEMP_PROTECT_ENABLE);

    /*�ߡ������±������ͣ������*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg_high_thr = %d,chg_low_thr = %d\n", \
        CHG_OVER_TEMP_STOP_THRESHOLD, CHG_LOW_TEMP_STOP_THRESHOLD);

    /*�ߡ������±�����縴������*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:rechg_high_thr = %d,rechg_low_thr = %d\n", \
        CHG_OVER_TEMP_RESUME_THRESHOLD, CHG_LOW_TEMP_RESUME_THRESHOLD);

    /*��ӡ��/���±����ػ�ʹ�ܿ��أ�*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:shutoff over temp protect enable flag = %d\n",
                            SHUTOFF_OVER_TEMP_PROTECT_ENABLE);
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:shutoff low  temp protect enable flag = %d\n",
                            SHUTOFF_LOW_TEMP_PROTECT_ENABLE);

    /*�ߡ������±����ػ�����*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:shutoff_high_thr = %d,shutoff_low_thr = %d\n", \
        SHUTOFF_OVER_TEMP_SHUTOFF_THRESHOLD, SHUTOFF_LOW_TEMP_SHUTOFF_THRESHOLD);

    /*��ӡ���ε���¶Ⱥʹ����ĵ���¶�*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg_real_info.battery_one_temp = %d\n", chg_real_info.battery_one_temp);
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg_real_info.battery_temp = %d\n", chg_real_info.battery_temp);

    /*��ӡ��ǰ���±���״̬chg_temp_protect_flag��ֵ*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg_temp_protect_flag = %d\n", chg_temp_protect_flag);

    chg_print_level_message(CHG_MSG_DEBUG, "**********CHG TEMP PARA: chg_poll_batt_temp  end  *********\n");

    /*�����¶ȹػ��������ִ��*/
    chg_temp_is_too_hot_or_too_cold_for_shutoff( );
#if (FEATURE_ON == MBB_THERMAL_PROTECT)
#if !defined(BSP_CONFIG_BOARD_E5_E5770s) && !defined(BSP_CONFIG_BOARD_E5771S_852) && !defined(BSP_CONFIG_BOARD_E5771H_937) \
    && !defined(BSP_CONFIG_BOARD_E5575S_320) && !defined(BSP_CONFIG_BOARD_E5573CS) && !defined(BSP_CONFIG_BOARD_E5573BS)\
    && ! defined(BSP_CONFIG_BOARD_E5573CS_933) && !defined(BSP_CONFIG_BOARD_607HW) && !defined(BSP_CONFIG_BOARD_R218h)\
    && ! defined(BSP_CONFIG_BOARD_E5577BS_937) && ! defined(BSP_CONFIG_BOARD_E5577S_324)
    chg_set_supply_current_by_temp();
#endif
#endif
    /*������ͱ�������*/
#if ( FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT )
    chg_battery_protect_proc();
#endif
    /*USB�±�*/ 
#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
    chg_usb_temp_protect_proc();
#endif
}

/*******************************************************************
Function:      chg_calc_average_volt_value
Description:   ��ص�ѹƽ��������
Data Accessed: ��
Data Updated:  ��
Input:         �²ɼ����¶�ֵ
Return:        ƽ������¶�ֵ
*******************************************************************/
int32_t chg_calc_average_volt_value(int32_t new_data)
{
    int32_t    index = 0;
    int32_t    sum = 0;
    int32_t    bat_volt_avg = 0;
    int32_t    new_poll_mode;
    static int32_t  old_poll_mode = FAST_POLL_CYCLE;
    static uint32_t record_avg_num_fast = 0;
    static uint32_t record_avg_num_slow = 0;
    static int32_t record_value_fast[CHG_BAT_VOLT_SMOOTH_SAMPLE_FAST] = {0};
    static int32_t record_value_slow[CHG_BAT_VOLT_SMOOTH_SAMPLE_SLOW] = {0};

    /*��ѯ��ѯģʽ*/
    new_poll_mode = chg_poll_timer_get();

    if(new_poll_mode != old_poll_mode)
    {
        if(FAST_POLL_CYCLE == new_poll_mode)/*������ѯ�л�����ǰ�Ŀ���ѯ*/
        {
            for(index = 0;index < CHG_BAT_VOLT_SMOOTH_SAMPLE_FAST;index++)
            {
                record_value_fast[index] = chg_real_info.battery_volt;
            }
            record_avg_num_fast = CHG_BAT_VOLT_SMOOTH_SAMPLE_FAST;
        }
        else//�ɿ���ѯ�л�������ѯ
        {
            for(index = 0;index < CHG_BAT_VOLT_SMOOTH_SAMPLE_SLOW;index++)
            {
                record_value_slow[index] = chg_real_info.battery_volt;
            }
            record_avg_num_slow = CHG_BAT_VOLT_SMOOTH_SAMPLE_SLOW;
        }

        old_poll_mode = new_poll_mode;
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "new_poll_mode = old_poll_mode!\n");
    }

    if(FAST_POLL_CYCLE == new_poll_mode)//����ѯģʽ
    {
        /*�����е�ǰԪ�ر��С��30*/
        if(CHG_BAT_VOLT_SMOOTH_SAMPLE_FAST > record_avg_num_fast)
        {
            record_value_fast[record_avg_num_fast] = new_data;
            record_avg_num_fast++;

            for(index = 0;index < record_avg_num_fast; index++)
            {
                sum += record_value_fast[index];
            }

            bat_volt_avg = sum / record_avg_num_fast;
        }
        else/*Ԫ�ظ�����Ŵ��ڵ���30��*/
        {
            record_value_fast[record_avg_num_fast % CHG_BAT_VOLT_SMOOTH_SAMPLE_FAST] = new_data;
            record_avg_num_fast++;

            for(index = 0;index < CHG_BAT_VOLT_SMOOTH_SAMPLE_FAST; index++)
            {
                sum += record_value_fast[index];
            }

            bat_volt_avg = sum / CHG_BAT_VOLT_SMOOTH_SAMPLE_FAST;

            /*���Ԫ�ظ�������Ǿ�̬���鳤�ȵ�����,������Ԫ�ظ�������Ǿ�̬���鳤�ȼ�CHG_BAT_TEMP_SMOOTH_SAMPLE*/
            if(CHG_BAT_VOLT_SMOOTH_SAMPLE_FAST * 2 == record_avg_num_fast)
            {
                record_avg_num_fast = CHG_BAT_VOLT_SMOOTH_SAMPLE_FAST;
            }
        }
    }
    else//����ѯģʽ
    {
        /*�����е�ǰԪ�ر��С��5*/
        if(CHG_BAT_VOLT_SMOOTH_SAMPLE_SLOW > record_avg_num_slow)
        {
            record_value_slow[record_avg_num_slow] = new_data;
            record_avg_num_slow++;

            for(index = 0;index < record_avg_num_slow; index++)
            {
                sum += record_value_slow[index];
            }

            bat_volt_avg = sum / record_avg_num_slow;
        }
        else/*Ԫ�ظ�����Ŵ��ڵ���5��*/
        {
            record_value_slow[record_avg_num_slow % CHG_BAT_VOLT_SMOOTH_SAMPLE_SLOW] = new_data;
            record_avg_num_slow++;

            for(index = 0;index < CHG_BAT_VOLT_SMOOTH_SAMPLE_SLOW; index++)
            {
                sum += record_value_slow[index];
            }

            bat_volt_avg = sum / CHG_BAT_VOLT_SMOOTH_SAMPLE_SLOW;

            /*���Ԫ�ظ�������Ǿ�̬���鳤�ȵ�����,������Ԫ�ظ�������Ǿ�̬���鳤�ȼ�CHG_BAT_TEMP_SMOOTH_SAMPLE*/
            if(CHG_BAT_VOLT_SMOOTH_SAMPLE_SLOW * 2 == record_avg_num_slow)
            {
                record_avg_num_slow = CHG_BAT_VOLT_SMOOTH_SAMPLE_SLOW;
            }
        }

    }

    return bat_volt_avg;
}

/*******************************************************************
Function:      chg_volt_level_to_capacity
Description:   ��ص���������ٷֱ�ת��
Data Accessed: ��
Data Updated:  ��
Input:         ��
Return:        ��
*******************************************************************/
void chg_volt_level_to_capacity(BATT_LEVEL_ENUM bat_volt_level)
{
    chg_stm_state_type cur_stat = chg_stm_get_cur_state();
    switch(bat_volt_level)
    {
        case BATT_LOW_POWER:
        {
            /*δ��糡����������������Ϊ�͵�͵��������ֹ�ϱ��͵������Ӧ���ڳ�糡�����е͵���ʾ*/
            if(FALSE == chg_get_charging_status())
            {
                chg_set_sys_batt_capacity(BATT_CAPACITY_LEVELLOW);
            }
            break;
        }
        case BATT_LEVEL_1:
        {
            chg_set_sys_batt_capacity(BATT_CAPACITY_LEVEL1);
            break;
        }
        case BATT_LEVEL_2:
        {
            chg_set_sys_batt_capacity(BATT_CAPACITY_LEVEL2);
            break;
        }
        case BATT_LEVEL_3:
        {
            chg_set_sys_batt_capacity(BATT_CAPACITY_LEVEL3);
            break;
        }
        case BATT_LEVEL_4:
        {
            /*����ͣ�����õ�ص���Ϊ100*/
            if(CHG_STM_MAINT_ST == cur_stat)
            {
                chg_set_sys_batt_capacity(BATT_CAPACITY_FULL);
                chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg_volt_level_to_capacity-->CHG_STM_MAINT_ST!\n ");
            }
            else
            {
                /*������ͣ�䵫��ص�ѹ����4.1VҲ���õ�ص���Ϊ100*/
                if(chg_get_sys_batt_volt() >= BATT_CHG_TEMP_MAINT_THR)
                {
                    chg_set_sys_batt_capacity(BATT_CAPACITY_FULL);
                    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg_volt_level_to_capacity VBAT>=4.1V!\n ");
                }
                else
                {
                    chg_set_sys_batt_capacity(BATT_CAPACITY_LEVEL4);
                }
            }

            break;
        }

        default:
            break;
    }

}


#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
/*******************************************************************
Function:      chg_soc2level
Description:   ��ص�������ת��
Data Accessed: ��
Data Updated:  ��
Input:         ��
Return:        ��
*******************************************************************/
BATT_LEVEL_ENUM chg_soc2level(int soc)
{
    BATT_LEVEL_ENUM volt_level;

    if ( (soc > BATT_CAPACITY_FULL) || (soc < 0) )
    {
        chg_print_level_message(CHG_MSG_ERR,\
            "chg_percent2level param %d error!! not in [0 ~ 100]\n ", soc);
    }

    if (soc < BATT_CAPACITY_LEVEL1) 
    {
        volt_level = BATT_LOW_POWER;
    }
    else if (soc < BATT_CAPACITY_LEVEL1)
    {
        volt_level = BATT_LEVEL_0;
    }
    else if (soc < BATT_CAPACITY_LEVEL2)
    {
        volt_level = BATT_LEVEL_1;
    }

    else if (soc < BATT_CAPACITY_LEVEL3)
    {
        volt_level = BATT_LEVEL_2;
    }
    else if (soc < BATT_CAPACITY_LEVEL4)
    {
        volt_level = BATT_LEVEL_3;
    }
    else 
    {
        volt_level = BATT_LEVEL_4;
    }

    return volt_level;
}
/*******************************************************************
Function:      chg_set_battery_level
Description:   ��ص�����������
Data Accessed: ��
Data Updated:  ��
Input:         ��
Return:        ��
*******************************************************************/
void chg_set_battery_level(void)
{
    int soc = 0;
    BATT_LEVEL_ENUM bat_volt_level = BATT_LEVEL_MAX;
    BATT_LEVEL_ENUM pre_bat_level = BATT_LEVEL_MAX;
    soc = chg_get_sys_batt_capacity();
    bat_volt_level = chg_soc2level(soc);
    pre_bat_level = chg_real_info.bat_volt_lvl;
    
   /*�ǳ��״̬���������ص�ѹ��ת*/
    if(FALSE == chg_get_charging_status())
    {
        if(bat_volt_level <= chg_real_info.bat_volt_lvl )
        {
            chg_real_info.bat_volt_lvl = bat_volt_level;
            chg_print_level_message(CHG_MSG_DEBUG,\
            "CHG_STM:NO chargin state volt_lvl decline to %d!\n ",bat_volt_level);
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG,\
            "CHG_STM:NO chargin state only allow volt_lvl decline!\n ");
        }
    }//���״̬
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG,\
        "CHG_STM:chargin state volt_lvl increase to %d!\n ",bat_volt_level);
        chg_real_info.bat_volt_lvl = bat_volt_level;
    }

    if(BATT_LOW_POWER == chg_real_info.bat_volt_lvl) 
    {
        chg_batt_low_battery_flag = TRUE;
        if(FAST_POLL_CYCLE != chg_poll_timer_get())
        {
            chg_poll_timer_set(FAST_POLL_CYCLE);
        }
    }

    if(pre_bat_level != chg_real_info.bat_volt_lvl)
    {
        chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY,\
                            (uint32_t)CHG_EVENT_NONEED_CARE);
    }

}
#endif
/*******************************************************************
Function:      chg_set_battery_volt_level
Description:   ��ص��������ж�����
Data Accessed: ��
Data Updated:  ��
Input:         ��
Return:        ��
*******************************************************************/
void chg_set_battery_volt_level(void)
{
    static uint32_t count = 0;
    BATT_LEVEL_ENUM bat_volt_level = BATT_LEVEL_MAX;
    int32_t batt_volt = chg_real_info.battery_volt;

    if(batt_volt < BATT_VOLT_LEVELLOW_MAX)
    {

#if (MBB_CHG_EXTCHG == FEATURE_ON)
        /*����������λ���û�ѡ���˽���������߶����������ҵ�����ϱ��͵�*/
        if(FALSE == is_5577cs_falg)
        {
            if(g_ui_choose_exchg_mode <= 0)
            {
                bat_volt_level = BATT_LOW_POWER;
            }
            else
            {
                chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:EXTCHG do not report Lowpower!\n");
            }
        }
        else
        {
            bat_volt_level = BATT_LOW_POWER;
        }
#else
        bat_volt_level = BATT_LOW_POWER;
#endif /*defined(MBB_CHG_EXTCHG)*/
    }

    else if(batt_volt < BATT_VOLT_LEVEL1_MAX)
    {
        bat_volt_level = BATT_LEVEL_1;
    }
    else if(batt_volt < BATT_VOLT_LEVEL2_MAX)
    {
        bat_volt_level = BATT_LEVEL_2;
    }
    else if(batt_volt < BATT_VOLT_LEVEL3_MAX)
    {
        bat_volt_level = BATT_LEVEL_3;
    }
    else
    {
        bat_volt_level = BATT_LEVEL_4;
    }

   /*�ǳ��״̬���������ص�ѹ��ת*/
    if(FALSE == chg_get_charging_status())
    {
        if(bat_volt_level <= chg_real_info.bat_volt_lvl )
        {
            chg_real_info.bat_volt_lvl = bat_volt_level;
            chg_volt_level_to_capacity(bat_volt_level);
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:NO chargin state volt_lvl decline to %d!\n ",bat_volt_level);
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:NO chargin state only allow volt_lvl decline!\n ");
        }
    }//���״̬
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chargin state volt_lvl increase to %d!\n ",bat_volt_level);
        chg_real_info.bat_volt_lvl = bat_volt_level;
        chg_volt_level_to_capacity(bat_volt_level);
    }


    /*�͵�ǳ��,�ҷǹػ����״̬�£��ϱ�APP�͵��¼�*/
    if((BATT_LOW_POWER == chg_real_info.bat_volt_lvl) \
       && (FALSE == chg_is_powdown_charging()) \
       && (FALSE == chg_get_charging_status()))
    {
        if(BATTERY_EVENT_REPORT_TIMES > count) /* �ϱ�5�� */
        {
            /*���ýӿں����ϱ�APP�͵��¼�*/
            chg_batt_low_battery_flag = TRUE;
            chg_poll_timer_set(FAST_POLL_CYCLE);
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:send MSG to app for show low power \n ");
            chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY, (uint32_t)BAT_LOW_POWER);
            count++;
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:low power event report less than 5 times!\n");
        }
    }
    else
    {
        count = 0;
    }
}

/*******************************************************************
Function:      chg_detect_batt_volt_for_shutoff
Description:   ��ص��������ж�����
Data Accessed: ��
Data Updated:  ��
Input:         ��
Return:        ��
*******************************************************************/
void chg_detect_batt_volt_for_shutoff(void)
{
    static uint32_t timer_flag = FALSE;

    /*��Ƭ�汾��������*/
    /*��ά�ɲ�:�͵�ػ�/�޵�ؿ���ʹ��*/
    if( TRUE == chg_is_ftm_mode() \
        || TRUE == chg_is_low_battery_poweroff_disable() \
        || TRUE == chg_is_no_battery_powerup_enable() )
    {
        return;
    }
    /*��ص͵�ػ����*/
    if(BATT_VOLT_POWER_OFF_THR > chg_real_info.battery_volt)
    {
        chg_print_level_message(CHG_MSG_INFO,"CHG_STM:PowerOffThreshold=%d\n",BATT_VOLT_POWER_OFF_THR);
#if defined(BSP_CONFIG_BOARD_E5_E5770s)
        /*����ģʽ�ҳ��������λ*/
        if( FALSE == chg_is_powdown_charging() && (TRUE == is_chg_charger_removed()) )
#else
        if( FALSE == chg_is_powdown_charging() )/*����ģʽ*/
#endif
        {
            /*todo �ϱ�APPִ�е͵�ػ�����*/
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:send MSG to app for low battery power off  \n ");
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
            /*����֧�ֿ��ؼƵĲ�Ʒ����Ҫ���ݵ�ѹ�������ػ���ͬʱ��Ҫcoul��socֵƽ����2%*/
            if((FALSE == timer_flag) && (BATT_CAPACITY_SHUTOFF >= chg_get_sys_batt_capacity()))
            {
                timer_flag = TRUE;
                chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY, (uint32_t)BAT_LOW_POWEROFF);
                /*������ʱ�����ص�����Ϊ�ػ���������ʱʱ��Ϊ15�룻*/
                chg_print_level_message(CHG_MSG_ERR, \
                "CHG_STM:begin 15s timer for low battery power off \n ");
                chg_bat_timer_set( LOW_BATT_SHUTOFF_DURATION,\
                chg_set_power_off, DRV_SHUTDOWN_LOW_BATTERY);
            }
#else

            /*����ģʽ��ص�ѹ����3.45V��Ӧ���ϱ�����Ϊ0���ػ����ģʽ���ϱ���ֹ�������ػ�*/
            chg_set_sys_batt_capacity(BATT_CAPACITY_SHUTOFF);
            chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY, (uint32_t)BAT_LOW_POWEROFF);
#if ( FEATURE_ON == MBB_MLOG )
            mlog_print(MLOG_CHG, mlog_lv_warn, "Battery volt too low, report system down message!!!\n");
#endif
            if(FALSE == timer_flag)
            {
                timer_flag = TRUE;
                /*������ʱ�����ص�����Ϊ�ػ���������ʱʱ��Ϊ15�룻*/
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:begin 15s timer for low battery power off \n ");
#if ( FEATURE_ON == MBB_MLOG )
                mlog_print(MLOG_CHG, mlog_lv_warn, "CHG_STM:begin 15s timer for low battery power off!!!\n");
#endif
                chg_bat_timer_set( LOW_BATT_SHUTOFF_DURATION, chg_set_power_off, DRV_SHUTDOWN_LOW_BATTERY);
            }
#endif
        }
        else/*�ػ�ģʽ*/
        {
            /*�ػ�ģʽ�µĵ�ѹ���ڹػ����ޣ�������������Ϊ�ػ�״̬*/
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:power off voltage but in powdown_charging do nothing!\n");
        }
    }
}
/*******************************************************************
Function:      chg_detect_batt_chg_for_shutoff
Description:   �ػ������������Դ�Ƴ������йػ�����
Data Accessed: ��
Data Updated:  ��
Input:         ��
Return:        ��
*******************************************************************/
void chg_detect_batt_chg_for_shutoff(void)
{
    static int32_t charge_remove_check_count = 0;

#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    if(TRUE == chg_is_powdown_charging() && gpio_get_value(EXTCHG_OTG_DET_GPIO))
#else
    if(TRUE == chg_is_powdown_charging())
#endif
    {
#if (MBB_CHG_WIRELESS == FEATURE_ON)
        /*�����߳�繦��ʱ���ػ��������������μ�⵽���߳���������߳����������λ��ػ�*/
        if((FALSE == chg_is_charger_present()) && (FALSE == chg_stm_get_wireless_online_st()))
#else
        /*�����߳�繦��ʱ���ػ��������������μ�⵽���߳������߳����������λ��ػ�*/
        if(FALSE == chg_is_charger_present())
#endif/*MBB_CHG_WIRELESS*/
        {
            if(CHARGE_REMOVE_CHECK_MAX <= charge_remove_check_count)
            {
                chg_print_level_message(CHG_MSG_ERR,"CHG_STM:POWER OFF FOR CHARGER REMOVE !\n ");
                chg_set_power_off(DRV_SHUTDOWN_CHARGE_REMOVE);
            }
            else
            {
                chg_print_level_message(CHG_MSG_INFO,"CHG_STM:charge_remove_check_count = %d\n ",charge_remove_check_count);
                charge_remove_check_count++;
            }
        }
        else
        {
            charge_remove_check_count = 0;
        }
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM: power on chging chgr remove do noting!\n");
    }
}


void chg_set_revise_value(int32_t value)
{
    chg_real_info.volt_revise_value = value;
}

int32_t chg_get_revise_value(void)
{
    return chg_real_info.volt_revise_value;
}

#if (MBB_CHG_EXTCHG == FEATURE_ON)


int32_t chg_get_extchg_revise(void)
{
    int32_t revise_val = 0;

    if(chg_get_revise_value() <= 0)
    {
        return revise_val;
    }
    /*�ŵ�粹������*/
    if(chg_get_revise_value() < EXTCHG_BATT_VOLT_REVISE_LIMIT)
    {
        revise_val = chg_get_revise_value();
    }
    else
    {
        revise_val = EXTCHG_BATT_VOLT_REVISE_LIMIT;
    }

    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:extchg revise_val = %d\n", revise_val);
    return revise_val;
}

boolean is_need_extchg_revise(void)
{
    static boolean is_need_revise = FALSE;
    int32_t tmp_volt_revise_val = 0;
    int32_t batt_volt_average = chg_get_sys_batt_volt();
    int32_t batt_volt = chg_get_batt_volt_value();

    if(TRUE == is_5577cs_falg)
    {
        return FALSE;
    }

    /*��ض˿ڵ�ѹ����3.35v���ٲ���*/
    if(batt_volt < CHG_BATT_VOLT_REVISE_LIMIT_DOWN)
    {
        batt_volt = chg_get_batt_volt_value();
        if(batt_volt < CHG_BATT_VOLT_REVISE_LIMIT_DOWN)
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:batt_volt=%d below 3.35V no need revise!\n", batt_volt);
            g_extchg_revise_count = 0;
            is_need_revise = FALSE;
            return  is_need_revise;
        }
    }
    if((!is_need_revise) || (g_extchg_revise_count < CHG_BATT_VOLT_REVISE_COUNT))
    {
        if(FALSE == g_exchg_enable_flag)
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:stop extchg,no need revise!\n");
            g_extchg_revise_count = 0;
            is_need_revise = FALSE;
            return  is_need_revise;
        }
        if((batt_volt_average - batt_volt) > CHG_BATT_VOLT_REVISE_WINDOW)
        {
            batt_volt = chg_get_batt_volt_value();
            if((batt_volt_average - batt_volt) > CHG_BATT_VOLT_REVISE_WINDOW)
            {
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:batt volt change = %d,start ext revise!\n",
                    (batt_volt_average - batt_volt));
                tmp_volt_revise_val = batt_volt_average - batt_volt;
                chg_set_revise_value(tmp_volt_revise_val);
                is_need_revise = TRUE;
            }
        }
        g_extchg_revise_count++ ;
    }
    else
    {
        if(FALSE == g_exchg_enable_flag)
        {
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:stop extchg,no need revise!\n");
            g_extchg_revise_count = 0;
            is_need_revise = FALSE;
        }
        else
        {
            /*����������λ����û����ӱ�����豸�������*/
            if((batt_volt_average - batt_volt) <= CHG_BATT_VOLT_REVISE_WINDOW)
            {
                batt_volt = chg_get_batt_volt_value();
                if((batt_volt_average - batt_volt) <= CHG_BATT_VOLT_REVISE_WINDOW)
                {
                    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:batt volt change = %d,stop ext revise!\n",
                        (batt_volt - batt_volt_average));
                    g_extchg_revise_count = 0;
                    is_need_revise = FALSE;
                }
            }
            /*��͸���*/
            else
            {
                int32_t temp_revise_val = chg_get_revise_value();
                if(abs((batt_volt_average - batt_volt) - temp_revise_val) > CHG_BATT_VOLT_REVISE_WINDOW)
                {
                    batt_volt = chg_get_batt_volt_value();
                    if(abs((batt_volt_average - batt_volt) - temp_revise_val) > CHG_BATT_VOLT_REVISE_WINDOW)
                    {
                        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:extchg batt volt change=%d,dynamic ext revise!\n",
                            (batt_volt_average - batt_volt));
                        tmp_volt_revise_val = batt_volt_average - batt_volt;
                        chg_set_revise_value(tmp_volt_revise_val);

                    }
                }
            }
        }
    }
    return  is_need_revise;
}

#endif/*defined(MBB_CHG_EXTCHG*/

int32_t chg_get_chg_revise(void)
{
    int32_t revise_val = 0;

    if(chg_get_revise_value() <= 0)
    {
        return revise_val;
    }

    /*��粹������*/
    if(chg_get_revise_value() < CHG_BATT_VOLT_REVISE_LIMIT)
    {
        revise_val = 0 - chg_get_revise_value();
    }
    else
    {
        revise_val = 0 - CHG_BATT_VOLT_REVISE_LIMIT;
    }
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg revise_val = %d\n", revise_val);
    return revise_val;
}


boolean is_need_chg_revise(void)
{
    static boolean is_need_revise = FALSE;
    int32_t tmp_volt_revise_val = 0;
    int32_t batt_volt_average = chg_get_sys_batt_volt();
    int32_t batt_volt = chg_get_batt_volt_value();

    /*��ض˿ڵ�ѹ����4.15v���ٲ���*/
    if(batt_volt > CHG_BATT_VOLT_REVISE_LIMIT_UP)
    {
        batt_volt = chg_get_batt_volt_value();
        if(batt_volt > CHG_BATT_VOLT_REVISE_LIMIT_UP)
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:batt_volt = %d\n", batt_volt);
            g_chg_revise_count = 0;
            is_need_revise = FALSE;
            return  is_need_revise;
        }
    }
    if((!is_need_revise) || (g_chg_revise_count < CHG_BATT_VOLT_REVISE_COUNT))
    {
        if(FALSE == chg_get_charging_status())
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:stop charging,no need revise!\n");
            g_chg_revise_count = 0;
            is_need_revise = FALSE;
            return  is_need_revise;
        }
        if((batt_volt - batt_volt_average) > CHG_BATT_VOLT_REVISE_WINDOW)
        {
            batt_volt = chg_get_batt_volt_value();
            if((batt_volt - batt_volt_average) > CHG_BATT_VOLT_REVISE_WINDOW)
            {
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:batt volt change = %d,start revise!\n",
                    (batt_volt - batt_volt_average));
                tmp_volt_revise_val = batt_volt - batt_volt_average;
                chg_set_revise_value(tmp_volt_revise_val);
                is_need_revise = TRUE;
            }
        }
        g_chg_revise_count++ ;
    }
    else
    {
        if(FALSE == chg_get_charging_status())
        {
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:stop charging ,stop revise!\n",
                (batt_volt - batt_volt_average));
            g_chg_revise_count = 0;
            is_need_revise = FALSE;
        }
        else
        {
            int32_t temp_revise_val = chg_get_revise_value ();
            if(abs((batt_volt - batt_volt_average) - temp_revise_val) > CHG_BATT_VOLT_REVISE_WINDOW)
            {
                batt_volt = chg_get_batt_volt_value();
                if(abs((batt_volt - batt_volt_average) - temp_revise_val) > CHG_BATT_VOLT_REVISE_WINDOW)
                {
                    /*��̬���²���ֵ*/
                    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:batt volt change = %d,dynamic revise!\n",
                    (batt_volt - batt_volt_average));
                    tmp_volt_revise_val = batt_volt - batt_volt_average;
                    chg_set_revise_value(tmp_volt_revise_val);
                }
            }
        }
    }
    return  is_need_revise;
}


int32_t chg_batt_volt_revise(int32_t batt_volt)
{
    int32_t revised_batt_volt = 0;

    if(TRUE == is_need_chg_revise())
    {
        revised_batt_volt = batt_volt + chg_get_chg_revise();
        chg_print_level_message(CHG_MSG_DEBUG, "VOLTAGE_COMPENCATE:need chg revise batt_volt_revised=%d\n",revised_batt_volt);
    }

#if (MBB_CHG_EXTCHG == FEATURE_ON)
    else if(TRUE == is_need_extchg_revise())
    {
        revised_batt_volt = batt_volt + chg_get_extchg_revise();
        chg_print_level_message(CHG_MSG_DEBUG, "VOLTAGE_COMPENCATE:need extchg revise batt_volt_revised=%d\n",revised_batt_volt);
    }
#endif /*defined(MBB_CHG_EXTCHG)*/
    else
    {
        revised_batt_volt = batt_volt;
        chg_set_revise_value(0);

        chg_print_level_message(CHG_MSG_DEBUG, "VOLTAGE_COMPENCATE:no need revise batt_volt_revised=%d\n",revised_batt_volt);
    }
    chg_print_level_message(CHG_MSG_INFO, "VOLTAGE_COMPENCATE:batt_volt=%d,revised_value=%d,batt_volt_revised=%d\n",\
                           batt_volt,chg_get_revise_value(),revised_batt_volt);

    return revised_batt_volt;
}
#ifdef CONFIG_COUL
#define CURRENT_RECORD_NUM    (20)/*�����ɼ�����*/
#define CURRENT_LIMIT_UP_MAX   (2000)/*�����ɼ����ֵ�߽�ֵ*/
#define CURRENT_LIMIT_UP_MIN    (-2000)/*�����ɼ����ֵ�߽�ֵ*/
#define CURRENT_LIMIT_DOWN_MAX    (50)/*�����ɼ���Сֵ�߽�ֵ*/
#define CURRENT_LIMIT_DOWN_MIN    (-50)/*�����ɼ���Сֵ�߽�ֵ*/
#define CURRENT_UNIT_MA2UA    (1000)/*��λ����*/
#define R_BATT    (110)/*�����С��Ҫ���ݵ�������ͳ���������*/

int32_t chg_get_average_batt_current(void)
{
    int32_t i, used, current_ma, totalcur;

    used = 0;
    totalcur = 0;
    current_ma = 0;
    for (i = 0; i < CURRENT_RECORD_NUM; i++)
    {
        current_ma = bsp_coul_current_before(i);
        if((current_ma > CURRENT_LIMIT_UP_MAX) || (current_ma < CURRENT_LIMIT_UP_MIN))
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:invalid current = %d ma\n", current_ma);
            continue;
        }
        totalcur += current_ma;
        used++;
    }
    if(used > 0)
    {
        current_ma = totalcur / used;
    }
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:current_ma = %d\n", current_ma);
    return current_ma;
}

/*������Ϊ��������ߣ��ŵ����Ϊ���������*/
int32_t chg_batt_volt_coul_revise(int32_t batt_volt)
{
    int32_t current_ma = 0,revise_val = 0;
    int32_t revised_batt_volt = 0;

    revised_batt_volt = batt_volt;
    /*��ض˿ڵ�ѹ����4.15v���ٲ���*/
    if(batt_volt > CHG_BATT_VOLT_REVISE_LIMIT_UP)
    {
        batt_volt = chg_get_batt_volt_value();
        if(batt_volt > CHG_BATT_VOLT_REVISE_LIMIT_UP)
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:wired chg revise_val = %d\n", revise_val);
            return revised_batt_volt;
        }
    }
    /*��ض˿ڵ�ѹ����3.35v���ٲ���*/
    if(batt_volt < CHG_BATT_VOLT_REVISE_LIMIT_DOWN)
    {
        batt_volt = chg_get_batt_volt_value();
        if(batt_volt < CHG_BATT_VOLT_REVISE_LIMIT_DOWN)
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:wired chg revise_val = %d\n", revise_val);
            return revised_batt_volt;
        }
    }
    current_ma = chg_get_average_batt_current();
    if((CURRENT_LIMIT_DOWN_MIN < current_ma) && (CURRENT_LIMIT_DOWN_MAX > current_ma))
    {
        return revised_batt_volt;
    }
    revise_val = (current_ma * R_BATT) / CURRENT_UNIT_MA2UA;/*��λת�������ת��ΪmV*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:revise_val = %d\n", revise_val);
    revised_batt_volt = batt_volt - revise_val;
    return revised_batt_volt;
}
#endif
/*******************************************************************
Function:      chg_huawei_se_volt
Description:   ��ص�ѹ��������������Ҫ���ݾ���Ĳ��Խ����Ʋ���������
               �˴�ֻ�ṩ�ӿڣ�����ʵ��ȡ���ڲ�Ʒʵ�ʲ��Խ����
Input:         ƽ����ĵ�ѹֵ
Return:        ������ĵ�ѹֵ
*******************************************************************/
int32_t chg_huawei_set_volt(int32_t bat_volt)
{
#if defined(BSP_CONFIG_BOARD_E5_E5578)
    uint32_t batt_id = chg_get_batt_id();
    switch(batt_id)
    {
        case CHG_BATT_ID_FEIMAOTUI:
        {
            bat_volt = bat_volt + CALI_VLOT_FEIMAOTUI ;
            break;             
        }
        case CHG_BATT_ID_XINGWANGDA:
        {
            bat_volt = bat_volt + CALI_VLOT_XINGWANGDA ;
            break;
        }
        case CHG_BATT_ID_LISHEN:
        default:
            break;
        }
#elif defined(BSP_CONFIG_BOARD_E5573S_856) || defined(BSP_CONFIG_BOARD_E5573S_853) \
    || defined(BSP_CONFIG_BOARD_E5573S_607) || defined(BSP_CONFIG_BOARD_E5573CS) \
    || defined(BSP_CONFIG_BOARD_E5573BS) || defined(BSP_CONFIG_BOARD_E5573CS_933)\
    || defined(BSP_CONFIG_BOARD_E5577BS_937) || defined(BSP_CONFIG_BOARD_R218h)
    uint32_t batt_id = chg_get_batt_id();
    switch(batt_id)
    {
        case CHG_BATT_ID_LISHEN:
        {
            bat_volt = bat_volt + CALI_VLOT_LISHEN ;
            break;
        }
         case CHG_BATT_ID_FEIMAOTUI:
        {
            bat_volt = bat_volt + CALI_VLOT_FEIMAOTUI ;
            break;
        }
        case CHG_BATT_ID_XINGWANGDA:
        {
            bat_volt = bat_volt + CALI_VLOT_XINGWANGDA ;
            break;
        }
        default:
            break;
        }
#endif
    return bat_volt;
}
/*******************************************************************
Function:      chg_poll_bat_level
Description:   ��ص�ѹֵ�ӹ���������̿��ƺ�����
Calls:         chg_get_parameter_level-------------�ɼ���ѹֵֵ�ӿں�����
               chg_calc_average_volt_value--------��ѹƽ���㷨��������
               huawei_set_temp------------------------��ѹ��������
Data Accessed: ��
Data Updated:  ȫ�ֱ������¶�ֵ
Input:         ��
Output:        ��
Return:        ��
*******************************************************************/
void chg_poll_bat_level(void)
{
    int32_t new_one_batt_volt = 0;
    int32_t new_batt_volt = 0;
    static uint32_t init_flag = FALSE;


    /*����ؼ�⴦����*/
    chg_batt_error_detect_volt();

    /*���ú���chg_get_parameter_level����ȡ��ص�ѹ*/
    new_one_batt_volt = chg_get_batt_volt_value();
    /*���ݵ�ص�ѹID����Ե�ص�ѹ���в���*/
    new_one_batt_volt = chg_huawei_set_volt(new_one_batt_volt);
    /*�����߶�����ʱ����Ҫ�Ե�ص�ѹ������߻���Ͳ���*/
#if CHG_BATT_REVISE
#if CHG_USE_COUL_REVISE
#ifdef CONFIG_COUL
    new_one_batt_volt = chg_batt_volt_coul_revise(new_one_batt_volt);
#endif
#else
#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
#else
    new_one_batt_volt = chg_batt_volt_revise(new_one_batt_volt);
#endif
#endif
#endif
    /*�����ص��βɼ���ѹ��ȫ�ֱ���*/
    chg_real_info.battery_one_volt = new_one_batt_volt;

    /*���ƽ����ѹ��ʼ��Ϊ�״βɼ�ֵ*/
    if(FALSE == init_flag)
    {
        chg_real_info.battery_volt = chg_real_info.battery_one_volt;
        chg_real_info.bat_volt_lvl = BATT_LEVEL_MAX;
        init_flag = TRUE;
    }

    /*�Ե�ص�ѹ����ƽ���㷨����*/
    new_batt_volt = chg_calc_average_volt_value(new_one_batt_volt);

    /*�����ص�ѹƽ��ֵ��ȫ�ֱ���*/
    chg_real_info.battery_volt = new_batt_volt;

    /*��ص�����������*/
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
    chg_set_battery_level();
#else
    chg_set_battery_volt_level();
#endif

    /* log��ӡ�ӿڣ���ά�ɲ���������*/
    chg_print_level_message(CHG_MSG_DEBUG, "*********** CHG BAT VOLT PARA: chg_poll_bat_level  begin **********\n");

    /*��ӡ����±���ʹ�ܿ���*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg temp protect enable flag = %d\n", CHG_TEMP_PROTECT_ENABLE);

    /*������ѹ����*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:shutoff_batt_volt_thr= %d\n", BATT_VOLT_POWER_ON_THR);

    /*��ӡ��ص��βɼ���ѹ*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg_real_info.battery_one_volt = %d\n", chg_real_info.battery_one_volt);
    /*��ӡ��ص�ѹƽ��ֵ*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg_real_info.battery_volt = %d\n", chg_real_info.battery_volt);
    /*��ӡ��ӡ��ص�������*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:chg_real_info.bat_volt_level = %d\n", chg_real_info.bat_volt_lvl);
    chg_print_level_message(CHG_MSG_DEBUG, "*********** CHG BAT VOLT PARA: chg_poll_bat_level  end **********\n");

    /*��������Ƴ��ػ�*/
    chg_detect_batt_chg_for_shutoff();
    chg_detect_batt_volt_for_shutoff();
}
#if (MBB_CHG_COULOMETER == FEATURE_ON)
/*******************************************************************
Function:      chg_poll_batt_soc
Description:   update the battery soc,if changed,report to app
Calls:         chg main task
Input:         none
Output:        none
Return:        none
*******************************************************************/
void chg_poll_batt_soc(void)
{
    int32_t input_soc = 0;
    int32_t last_soc = chg_get_sys_batt_capacity();

    input_soc = smartstar_battery_capacity();
    if(input_soc - last_soc >= 1)
    {
        input_soc = last_soc + 1;
    }
    else if(last_soc - input_soc >= 1)
    {
        input_soc = last_soc - 1;
    }
    else
    {
    }
    
    chg_set_sys_batt_capacity(input_soc);
}
#endif

#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
/*******************************************************************
Function:      chg_notify_app_charging_state
Description:   notify the battery charging state
Calls:         chg main task
Input:         batt_state
Output:        none
Return:        success:0 fail:-1
*******************************************************************/
int32_t chg_notify_app_charging_state(int32_t batt_state)
{
    if (NULL == g_chip)
    {
        chg_print_level_message(CHG_MSG_ERR,"CHG:NULL pointer,batt_state=%d\n ",batt_state);        
        return -1;
    }
    g_chip->bat_stat = batt_state;
    power_supply_changed(&g_chip->bat);
    return 0;
}
/*******************************************************************
Function:      chg_poll_batt_charging_state_for_coul
Description:   update the battery charging state,if changed,notify coul
Calls:         chg main task
Input:         none
Output:        none
Return:        none
*******************************************************************/
void chg_poll_batt_charging_state_for_coul(void)
{
    static CHG_COUL_EVENT_TYPE charge_status = VCHRG_STOP_CHARGING_EVENT;
    chg_stm_state_type cur_stm_state;
    chg_print_level_message(CHG_MSG_DEBUG,"CHG:charging old state=%d\n ",charge_status);
    switch (charge_status)
    {
        case VCHRG_NOT_CHARGING_EVENT:
            if (chg_is_IC_charging())
            {
                hisi_coul_charger_event_rcv(VCHRG_START_CHARGING_EVENT);
                charge_status = VCHRG_START_CHARGING_EVENT;
            }
            else
            {            
                if(!is_chg_charger_removed())
                {   /* δ��絫�ǳ������λ */
                    #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
                    if ((CHG_STM_MAINT_ST == chg_stm_get_cur_state()) 
                    || (CHG_STOP_COMPLETE == chg_get_stop_charging_reason()))
                    {
                        hisi_coul_charger_event_rcv(VCHRG_CHARGE_DONE_EVENT);
                        charge_status = VCHRG_CHARGE_DONE_EVENT;
                    }
                    #else
                     /*IC����ͣ�䣬����soc����100%,��Ҫģ��һ�γ�ͣ����*/
                    if ((CHG_STM_MAINT_ST == chg_stm_get_cur_state())
                    && (FALSE == chg_is_batt_full()))
                    {
                        chg_notify_app_charging_state(POWER_SUPPLY_STATUS_CHARGING);
                        hisi_coul_charger_event_rcv(VCHRG_START_CHARGING_EVENT);
                        charge_status = VCHRG_START_CHARGING_EVENT;
                    }
                    #endif
                }
            }
 
            break;
        case VCHRG_START_CHARGING_EVENT:
            if (!chg_is_IC_charging())
            {
                if ((CHG_STM_MAINT_ST == chg_stm_get_cur_state()) 
                || (CHG_STOP_COMPLETE == chg_get_stop_charging_reason()))
                {
                    hisi_coul_charger_event_rcv(VCHRG_CHARGE_DONE_EVENT);
                    charge_status = VCHRG_CHARGE_DONE_EVENT;
                }
                else
                {
                    hisi_coul_charger_event_rcv(VCHRG_STOP_CHARGING_EVENT);
                    charge_status = VCHRG_STOP_CHARGING_EVENT;
                }
            }
            break;
        case VCHRG_STOP_CHARGING_EVENT:
            if (chg_is_IC_charging())
            {
                hisi_coul_charger_event_rcv(VCHRG_START_CHARGING_EVENT);
                charge_status = VCHRG_START_CHARGING_EVENT;
            }
            else
            {
                hisi_coul_charger_event_rcv(VCHRG_NOT_CHARGING_EVENT);
                charge_status = VCHRG_NOT_CHARGING_EVENT;
            }
            break;
        case VCHRG_CHARGE_DONE_EVENT:
            if(is_chg_charger_removed())
            {   /* �����°ε������  */
                hisi_coul_charger_event_rcv(VCHRG_NOT_CHARGING_EVENT);
                charge_status = VCHRG_NOT_CHARGING_EVENT;                
            }
            else
            {
                if (chg_is_IC_charging())
                {   /* ������ų�������г���е����̬��û�б���������̬  */
                    hisi_coul_charger_event_rcv(VCHRG_START_CHARGING_EVENT);
                    charge_status = VCHRG_START_CHARGING_EVENT;
                }
                #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
                #else
                /*IC����ͣ�䣬����soc����100%,��Ҫ��ʾ��綯����ƽ���ٷֱ�*/
                else if ((CHG_STM_MAINT_ST == chg_stm_get_cur_state())
                    && (FALSE == chg_is_batt_full()))
                {
                    chg_notify_app_charging_state(POWER_SUPPLY_STATUS_CHARGING);
                }
                #endif
            }
            break;
        default:
            break;
    }
    chg_print_level_message(CHG_MSG_DEBUG,"CHG:charging new state=%d\n ",charge_status);
}

#endif
#if (MBB_CHG_COMPENSATE == FEATURE_ON)
/**********************************************************************
�� �� ��  :  chg_tbat_status_get
��������  :  TBAT AT^TCHRENABLE?�Ƿ���Ҫ����

�������  : ��
�������  : ��
�� �� ֵ  : 1:��Ҫ����
            0:����Ҫ����
ע������  : ��
***********************************************************************/
int32_t chg_tbat_status_get(void)
{
    int32_t tbat_v = 0;
    int32_t ret = FALSE;
    (void)chg_set_charge_enable(FALSE);
    chg_delay_ms(CHG_DELAY_COUNTER_SIZE);
    if(TRUE == chg_is_IC_charging())
    {
        (void)chg_set_charge_enable(FALSE);
        chg_delay_ms(CHG_DELAY_COUNTER_SIZE);
    }

    /*��ȡ��ص���*/
    tbat_v = chg_get_batt_volt_value();  /* �ýӿ��Լ���������ͨ��ADCͷ�ļ���ȡ */

    /*�ж��Ƿ�����ŵ�򲹵磬������3��*/
#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
    if((tbat_v > tbatt_dischg_volt_threshold) 
        || (tbat_v < tbatt_supply_volt_threshold))
    {
        tbat_v = chg_get_batt_volt_value();
        if((tbat_v > tbatt_dischg_volt_threshold) 
            || (tbat_v < tbatt_supply_volt_threshold))
        {
            tbat_v = chg_get_batt_volt_value();
            if((tbat_v > tbatt_dischg_volt_threshold) 
                || (tbat_v < tbatt_supply_volt_threshold))
            {
                ret = TRUE;
            }
        }
    }
#else
    if((tbat_v > TBAT_DISCHG_VOLT) || (tbat_v < TBAT_SUPPLY_VOLT))
    {
        tbat_v = chg_get_batt_volt_value();
        if((tbat_v > TBAT_DISCHG_VOLT) || (tbat_v < TBAT_SUPPLY_VOLT))
        {
            tbat_v = chg_get_batt_volt_value();
            if((tbat_v > TBAT_DISCHG_VOLT) || (tbat_v < TBAT_SUPPLY_VOLT))
            {
                ret = TRUE;
            }
        }
    }
#endif
    if(TRUE == chg_get_charging_status())
    {
        (void)chg_set_charge_enable(TRUE);
    }
    chg_print_level_message(CHG_MSG_DEBUG,"CHG_SUP:BATTERY SPLY GET VBAT VALUE:%d\n ", tbat_v);
    return ret;
}

/**********************************************************************
�� �� ��  :  chg_is_sply_finish
��������  :  �жϲ����Ƿ����

�������  : ��
�������  : ��
�� �� ֵ  : 1:��ɲ���
            0:����δ���
ע������  : ��
***********************************************************************/
boolean chg_is_sply_finish(void)
{
    uint32_t tbat_v = 0;

    /*��ȡ��ص���*/
    tbat_v = chg_get_batt_volt_value();      /* �ýӿ��Լ���������ͨ��ADCͷ�ļ���ȡ */

    /* log��ӡ�ӿڣ���ά�ɲ��������ݣ��˴��ݶ�Ϊ�ýӿ����������ӿ�ȷ���������޸� */
    chg_print_level_message(CHG_MSG_DEBUG,"CHG_SUP:BATTERY SPLY LEVEL:%d\n ",tbat_v);

    /*�ж��Ƿ�����ŵ�򲹵磬������3��*/
#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
    if((tbat_v < tbatt_dischg_stop_threshold) 
        && (tbat_v > tbatt_supply_stop_threshold))
    {
        tbat_v = chg_get_batt_volt_value();
        if((tbat_v < tbatt_dischg_stop_threshold) 
            && (tbat_v > tbatt_supply_stop_threshold))
        {
            tbat_v = chg_get_batt_volt_value();
            if((tbat_v < tbatt_dischg_stop_threshold) 
                && (tbat_v > tbatt_supply_stop_threshold))
            {
                if( TRUE == fact_release_flag )
                {
                    chg_set_fact_release_mode(FALSE);
                    fact_release_flag = FALSE;
                }
                chg_stm_state_info.bat_stat_type = POWER_SUPPLY_STATUS_SUPPLY_SUCCESS;
                /*֪ͨӦ�ò������*/
                chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY,
                    (uint32_t)CHG_EVENT_NONEED_CARE);

                /* log��ӡ�ӿڣ���ά�ɲ��������ݣ��˴��ݶ�Ϊ�ýӿ����������ӿ�ȷ���������޸� */
                chg_print_level_message(CHG_MSG_DEBUG,
                    "CHG_SUP:BATTERY SPLY FINISH LEVEL:%d\n ", tbat_v);

                chg_sply_unlock();

                return TRUE;
            }
        }
    }
#else
    if((tbat_v < TBAT_DISCHG_STOP_VOLT) && (tbat_v > TBAT_SUPPLY_STOP_VOLT))
    {
        tbat_v = chg_get_batt_volt_value();
        if((tbat_v < TBAT_DISCHG_STOP_VOLT) && (tbat_v > TBAT_SUPPLY_STOP_VOLT))
        {
            tbat_v = chg_get_batt_volt_value();
            if((tbat_v < TBAT_DISCHG_STOP_VOLT) && (tbat_v > TBAT_SUPPLY_STOP_VOLT))
            {
                if( TRUE == fact_release_flag )
                {
                    chg_set_fact_release_mode(FALSE);
                    fact_release_flag = FALSE;
                }
                chg_stm_state_info.bat_stat_type = POWER_SUPPLY_STATUS_SUPPLY_SUCCESS;
                /*֪ͨӦ�ò������*/
                chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY,(uint32_t)CHG_EVENT_NONEED_CARE);

                /* log��ӡ�ӿڣ���ά�ɲ��������ݣ��˴��ݶ�Ϊ�ýӿ����������ӿ�ȷ���������޸� */
                chg_print_level_message(CHG_MSG_DEBUG,"CHG_SUP:BATTERY SPLY FINISH LEVEL:%d\n ", tbat_v);

                chg_sply_unlock();

                return TRUE;
            }
        }
    }
#endif

    return FALSE;
}

/**********************************************************************
�� �� ��  :  chg_batt_suply_proc
��������  :  ��ز�������

�������  : ��
�������  : ��
�� �� ֵ  : 1:����Ҫ����
            0:����ɹ�
ע������  : ��
***********************************************************************/

int32_t chg_batt_supply_proc(void *task_data)
{
    int32_t tbat_v = 0;
    uint32_t wait_idx = 0;
    uint32_t  tc_on = TBAT_SUPLY_DELAY_COUNTER;
    uint32_t  tc_off = TBAT_STOP_DELAY_COUNTER;

    if ( NULL == task_data )
    {
        chg_print_level_message(CHG_MSG_ERR,"CHG_STM:supply_proc task_data is NULL !\n");
    }

    /* log��ӡ�ӿڣ���ά�ɲ��������ݣ��˴��ݶ�Ϊ�ýӿ����������ӿ�ȷ���������޸� */
    chg_print_level_message(CHG_MSG_DEBUG,"CHG_SUP:START DISCHARGE OR CHARGE\n ");

    /* �ŵ�ɾ���������*/
    chg_task_delete();

    chg_sply_lock();
    chg_set_cur_chg_mode(CHG_SUPPLY_MODE);

    chg_stm_set_cur_state(CHG_STM_MAX_ST);

    chg_stm_state_info.bat_stat_type = POWER_SUPPLY_STATUS_NEED_SUPPLY;
    /*֪ͨӦ����Ҫ����*/
    chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY,(uint32_t)CHG_EVENT_NONEED_CARE);

    do{
        tbat_v = chg_get_batt_volt_value();
        /* log��ӡ�ӿڣ���ά�ɲ��������ݣ��˴��ݶ�Ϊ�ýӿ����������ӿ�ȷ���������޸� */
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_SUP:BATTERY CURRENT LEVEL:%d\n ",tbat_v);

        /*�����ص������ڷŵ���ֵ*/
        if(tbat_v > TBAT_DISCHG_STOP_VOLT)
        {
            /* log��ӡ�ӿڣ���ά�ɲ��������ݣ��˴��ݶ�Ϊ�ýӿ����������ӿ�ȷ���������޸� */
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_SUP:BATTERY DISCHARGING BEGIN\n");

            (void)chg_set_charge_enable(FALSE);
            chg_set_suspend_mode(TRUE);
            chg_set_fact_release_mode(TRUE);
            fact_release_flag = TRUE;
            for (wait_idx = 0; wait_idx < tc_on; wait_idx++)
            {
                chg_delay_ms(CHG_DELAY_COUNTER_SIZE);
            }

            /*���巽ʽ*/

            chg_set_suspend_mode(FALSE);

            for (wait_idx = 0; wait_idx < tc_off; wait_idx++)
            {
                chg_delay_ms(CHG_DELAY_COUNTER_SIZE);
            }

            chg_print_level_message(CHG_MSG_DEBUG,"CHG_SUP:BATTERY DISCHARGING END\n");
        }

        else if(tbat_v < TBAT_SUPPLY_STOP_VOLT) /*���*/
        {
            /* log��ӡ�ӿڣ���ά�ɲ��������ݣ��˴��ݶ�Ϊ�ýӿ����������ӿ�ȷ���������޸� */
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_SUP:BATTERY CHARGING BEGIN\n");

            //�����������Ϊfast������
            chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST]);
            (void)chg_set_charge_enable(TRUE);
            for (wait_idx = 0; wait_idx < tc_on; wait_idx++)
            {
                chg_delay_ms(CHG_DELAY_COUNTER_SIZE);
            }

            /*���巽ʽ*/
            (void)chg_set_charge_enable(FALSE);
            for (wait_idx = 0; wait_idx < tc_off; wait_idx++)
            {
                chg_delay_ms(CHG_DELAY_COUNTER_SIZE);
            }
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_SUP:BATTERY CHARGING END\n");

        }
        else
        {
            /* log��ӡ�ӿڣ���ά�ɲ��������ݣ��˴��ݶ�Ϊ�ýӿ����������ӿ�ȷ���������޸� */
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_SUP:BATTERY CHARGING OR DISCHARGING EXIT:%d\n ",tbat_v);
        }
    }while(!chg_is_sply_finish());
    /* ��ʹ�� */
    (void)chg_set_charge_enable(FALSE);

#if (MBB_CHG_POWER_SUPPLY == FEATURE_OFF)
    /*LCD״̬����*/
    chg_display_interface( CHG_DISP_OK );
#endif/*MBB_CHG_POWER_SUPPLY*/
    tbat_v = chg_get_batt_volt_value();
    /* log��ӡ�ӿڣ���ά�ɲ��������ݣ��˴��ݶ�Ϊ�ýӿ����������ӿ�ȷ���������޸� */
    chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:BATTERY EXIT LEVEL:%d\n ",tbat_v);
    chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:BATTERY CHARGE or DISCHARGER FINISH\n ");

    return TBAT_SUPPLY_CURR_SUCCESS;
}

/**********************************************************************
�� �� ��  :  chg_tbat_chg_sply
��������  :  TBAT AT^TCHRENABLE=4����ʵ��
                        ����ɹ�LCD��ʾ�ɹ�ͼ��
�������  : ��
�������  : ��
�� �� ֵ  : 1:TBAT_SUPPLY_CURR_SUCCESS ����ɹ�
            2:TBAT_NO_NEED_SUPPLY_CURR ����Ҫ����
ע������  : ��
***********************************************************************/
int32_t chg_tbat_chg_sply(void)
{
    /* ���ù�һ���ӿ�������������**/
    chg_sply_task_create();
/***************Note:ƽ̨��ش��룬����ƽ̨����Ҫ��ӣ��е�ƽ̨��V7R1��Ҫ
              ��ֲ��Ա������Ҫ����ӻ����Ƴ��±ߺ�������***************************/

#if (MBB_CHG_POWER_SUPPLY == FEATURE_OFF)
    /*���翪ʼ��ʾ����δ���ͼ��*/
    chg_display_interface( CHG_DISP_FAIL );
#endif/*MBB_CHG_POWER_SUPPLY*/
    return TBAT_SUPPLY_CURR_SUCCESS;
}
#endif /* MBB_CHG_COMPENSATE */

void chg_get_bat_temp(void)
{
    printk("bat_sys_temp is %d\r\n",chg_real_info.battery_temp);
}

void chg_get_bat_volt(void)
{
    printk("bat_sys_volt is %d\r\n",chg_real_info.battery_volt);
}
/**********************************************************************
�� �� ��  :chg_get_cur_batt_volt
��������  : ��ȡ��ǰ���ʵʱ��ѹ�Ľӿں���
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : ���ʵʱ��ѹ
ע������  : �ޡ�
***********************************************************************/
static int32_t chg_get_cur_batt_volt(void)
{
    if( 0xFFFF == chg_real_info.battery_one_volt )
    {
        chg_real_info.battery_one_volt = chg_get_batt_volt_value();
    }

    return chg_real_info.battery_one_volt;
}
/**********************************************************************
�� �� ��  :chg_get_sys_batt_volt
��������  : ��ȡ��ǰ���ƽ����ѹ�Ľӿں���
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : ���ƽ����ѹ
ע������  : �ޡ�
***********************************************************************/

int32_t chg_get_sys_batt_volt(void)
{
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    if (FALSE == is_chg_charger_removed())
    {
        if( 0xFFFF == chg_real_info.battery_volt )
        {
            chg_real_info.battery_volt = chg_get_batt_volt_value();
        }
        return chg_real_info.battery_volt;
    }
    else
    {
        if(0xFFFF == battery_voltage)
        {
            battery_voltage = chg_get_batt_volt_value();
        }
        return battery_voltage;
    }
#else
    if( 0xFFFF == chg_real_info.battery_volt )
    {
        chg_real_info.battery_volt = chg_get_batt_volt_value();
    }
    return chg_real_info.battery_volt;
#endif
}
/**********************************************************************
�� �� ��  :chg_get_cur_batt_temp
��������  : ��ȡ��ǰ���ʵʱ�¶ȵĽӿں���
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : ���ʵʱ�¶�
ע������  : �ޡ�
***********************************************************************/
int32_t chg_get_cur_batt_temp(void)
{
    if( 0xFFFF == chg_real_info.battery_one_temp )
    {
        chg_real_info.battery_one_temp = chg_get_temp_value(CHG_PARAMETER__BATT_THERM_DEGC);
    }

    return chg_real_info.battery_one_temp;
}
/**********************************************************************
�� �� ��  :chg_get_sys_batt_temp
��������  : ��ȡ��ǰ���ʵʱ�¶ȵĽӿں���
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : ���ƽ���¶�
ע������  : �ޡ�
***********************************************************************/
int32_t chg_get_sys_batt_temp(void)
{
    if( 0xFFFF == chg_real_info.battery_temp )
    {
        chg_real_info.battery_temp = chg_get_temp_value(CHG_PARAMETER__BATT_THERM_DEGC);
    }

    return chg_real_info.battery_temp;
}

/**********************************************************************
�� �� ��  :chg_set_sys_batt_capacity
��������  : ���õ�ǰ��ص����ٷֱȵĽӿں���
�������  : capacity :��ص����ٷֱ�
�������  : �ޡ�
�� �� ֵ  : ��ص����ٷֱ�
ע������  : �ޡ�
***********************************************************************/
void chg_set_sys_batt_capacity(int32_t capacity)
{
    /*���������仯ʱ�Ž����ϱ�����ϴ��ϱ����������ε�����ͬʱ�Ÿ�Ӧ���ϱ�*/
    if(chg_real_info.bat_capacity != capacity)
    {
        chg_real_info.bat_capacity = capacity;
        /*��ص����ٷֱȷ����仯֪ͨӦ�ò�ѯ*/
        chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY, (uint32_t)CHG_EVENT_NONEED_CARE);
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:set_batt_capacity=%d\n",capacity);
    }
}

/**********************************************************************
�� �� ��  :chg_get_sys_batt_capacity
��������  : ��ȡ��ǰ��ص����ٷֱȵĽӿں���
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : ��ص����ٷֱ�
ע������  : �ޡ�
***********************************************************************/
int32_t chg_get_sys_batt_capacity(void)
{
    if(chg_is_no_battery_powerup_enable())
    {
        return BATT_CAPACITY_FULL;
    }
#if (MBB_CHG_COULOMETER == FEATURE_ON)
    if(0 == chg_real_info.bat_capacity)
    {
        return smartstar_battery_capacity();
    }
#endif
    return chg_real_info.bat_capacity;
}
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
/**********************************************************************
�� �� ��  :chg_is_batt_in_state_of_emergency
��������  : ��ѯ����Ƿ��ڽ�����Ҫ�ػ�״̬
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : TRUE:yes��FALSE:no
ע������  : �ޡ�
***********************************************************************/
boolean chg_is_batt_in_state_of_emergency(void)
{
    //���ڿ���״̬���ж��Ƿ���Ҫ�ػ�
    return (!chg_is_powdown_charging() && BATT_VOLT_POWER_OFF_THR > chg_get_sys_batt_volt());
}
#endif

/**********************************************************************
�� �� ��  :chg_set_batt_time_to_full
��������  : ����Ԥ���ʣ����ʱ��
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : ��ص�����������ж೤ʱ��
ע������  : �ޡ�
***********************************************************************/
void chg_set_batt_time_to_full(int32_t time_to_full)
{
    chg_real_info.bat_time_to_full = time_to_full;
    /*֪ͨӦ��ʣ����ʱ�䷢���仯*/
    chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY, (uint32_t)CHG_EVENT_NONEED_CARE);
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:set_batt_time_to_full=%d\n",time_to_full);
}

/**********************************************************************
�� �� ��  :chg_get_batt_time_to_full
��������  : ��ȡ��ص�����������ж೤ʱ��
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : ��ص�����������ж೤ʱ��
ע������  : �ޡ�
***********************************************************************/
int32_t chg_get_batt_time_to_full(void)
{
    return chg_real_info.bat_time_to_full;
}

#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
/**********************************************************************
�� �� ��  :chg_get_batt_current_average
��������  : ��ȡ���ƽ������
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : ��ص�ƽ������
ע������  : �ޡ�
***********************************************************************/
int32_t chg_get_batt_current_average(void)
{
    return chg_real_info.bat_current_avg;
}
#endif

/**********************************************************************
�� �� ��  : chg_is_batt_full
��������  : �жϵ���Ƿ�����
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : 1:�������

            0:��ط�����
ע������  : �ޡ�
***********************************************************************/
boolean chg_is_batt_full(void)
{
/*֧�ֿ��ؼƵĲ�Ʒ���������޶���Ϊ95%*/
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
    return (BATT_CAPACITY_FULL == chg_get_sys_batt_capacity());
#else
    return (chg_get_sys_batt_volt() >= BATT_CHG_TEMP_MAINT_THR);
#endif
}

/**********************************************************************
�� �� ��  : chg_is_batt_full_for_start
��������  : �жϵ�ص�ѹ�Ƿ����㿪ʼ�������
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : 1:������磬����Ҫ�������
            0:��ط����磬��Ҫ�������
ע������  : �ޡ�
***********************************************************************/
boolean chg_is_batt_full_for_start(void)
{
/*֧�ֿ��ؼƵĲ�Ʒ���������޶���Ϊ95%*/
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
    return (BATT_CAPACITY_FULL == chg_get_sys_batt_capacity());
#else
    return (chg_get_sys_batt_volt() >= BATT_CHG_FIRST_MAINT_THR);
#endif
}
/**********************************************************************
�� �� ��  : chg_is_batt_full
��������  : �жϵ���Ƿ���Ҫ����
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : 1:�����Ҫ����
            0:��ز���Ҫ����
ע������  : �ޡ�
***********************************************************************/
static boolean chg_is_batt_need_rechg(void)
{
/*�������λʱ��ֻҪ�ٷֱȵ���100%�����������*/
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
/*���ʹ�ÿ��ؼƲ�Ʒ*/
#if (FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT)
    /*��ظ���״̬��֧�ֿ��ؼƵ�ʹ�õ�ѹ��Ϊ���������ж�*/
    if(TRUE == is_batttemp_in_warm_chg_area())
    {
        return (chg_get_sys_batt_volt() < BATT_HIGH_TEMP_RECHARGE_THR);
    }
    if (TRUE == g_chg_batt_expand_change_normal_rechg_flag)
    {
        return (chg_get_sys_batt_volt() < BATT_NORMAL_TEMP_RECHARGE_THR);
    }
#endif/*FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT*/
    #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
    if(TRUE == is_batttemp_in_warm_chg_area())
    {
        return (chg_get_sys_batt_capacity() <= BATT_CAPACITY_WARMRECHG);
    }
    else
    {
        return (chg_get_sys_batt_capacity() <= BATT_CAPACITY_RECHG);        
    }
    #else
    return (chg_get_sys_batt_capacity() <= BATT_CAPACITY_RECHG);
    #endif
#else
    if(TRUE == is_batttemp_in_warm_chg_area())
    {
        return (chg_get_sys_batt_volt() < BATT_HIGH_TEMP_RECHARGE_THR);
    }
    else
    {
        #if defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573BS)\
        || defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_607HW)\
        || defined(BSP_CONFIG_BOARD_E5577BS_937) || defined(BSP_CONFIG_BOARD_R218h)
        if (CHG_BATT_ID_DEF == chg_get_batt_id())
        {
            return FALSE;
        }
        #endif
        return (chg_get_sys_batt_volt() < BATT_NORMAL_TEMP_RECHARGE_THR);        
    }
#endif
}

/**********************************************************************
�� �� ��  : chg_is_batt_full
��������  : �жϵ���Ƿ��ѹ
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : 1:��ع�ѹ
            0:���û�й�ѹ
ע������  : �ޡ�
***********************************************************************/
static boolean chg_is_batt_ovp(void)
{
    return (boolean)((chg_get_sys_batt_volt() >= BATT_CHG_OVER_VOLT_PROTECT_THR) 
            || (chg_get_cur_batt_volt() >= BATT_CHG_OVER_VOLT_PROTECT_ONE_THR));
}
/**********************************************************************
�� �� ��  : chg_is_batt_full
��������  : �жϵ���Ƿ����
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : 1:���û�й���
            0:��ع���
ע������  : �ޡ�
***********************************************************************/
static boolean chg_is_batt_temp_valid(void)
{
    return !chg_temp_protect_flag;
}

/**********************************************************************
�� �� ��  : chg_get_batt_temp_state
��������  : ��ȡ��ǰ����¶�״̬
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : ����¶�״̬
ע������  : �ޡ�
***********************************************************************/
TEMP_EVENT chg_get_batt_temp_state(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:batt_temp_state=%d\n",chg_batt_temp_state);
    return chg_batt_temp_state;
}

/*****************************************************************************
 �� �� ��  : chg_stm_set_chgr_type
 ��������  : Update the current type of external charger.
 �������  : chgr_type  The charger type we gonna update to.
 �������  : None
 �� �� ֵ  : VOID.
 WHO-CALL  : chg_check_and_update_hw_param_per_chgr_type.
 CALL-WHOM : None.
 NOTICE    : Helper function.
*****************************************************************************/
void chg_stm_set_chgr_type(chg_chgr_type_t chgr_type)
{
    /*1. Update the current external charger type.*/
    chg_stm_state_info.cur_chgr_type = chgr_type;
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:set_chgr_type=%d\n",chgr_type);
}

/*****************************************************************************
 �� �� ��  : chg_stm_get_chgr_type
 ��������  : Get current external charger type:
             CHG_CHGR_UNKNOWN: Chgr type has not been got from USB module.
             CHG_WALL_CHGR   : Wall standard charger, which D+/D- was short.
             CHG_USB_HOST_PC : USB HOST PC or laptop or pad, etc.
             CHG_NONSTD_CHGR : D+/D- wasn't short and USB enumeration failed.
             CHG_CHGR_INVALID: External Charger invalid or absent.
 �������  : None.
 �������  : None
 �� �� ֵ  : Current external charger type.
 WHO-CALL  : DFT and other sub-modules.
 CALL-WHOM : None.
 NOTICE    : Need exported.
             The real chgr type checking would be done by USB module.
*****************************************************************************/
chg_chgr_type_t chg_stm_get_chgr_type(void)
{
    /*1. Return the current external charger type.*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:get_chgr_type=%d\n",chg_stm_state_info.cur_chgr_type);
    return chg_stm_state_info.cur_chgr_type;

}

boolean is_chg_charger_removed(void)
{
    boolean is_chgr_present      = chg_is_charger_present();
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    boolean is_wireless_online   = chg_stm_get_wireless_online_st();
    if ((FALSE == is_chgr_present) && (FALSE == is_wireless_online))
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:is_chg_charger_removed is_chgr_present=%d, is_wireless_online=%d.\n",
                    is_chgr_present,is_wireless_online);
        return TRUE;
    }
#else
    /*1. External charger removed, swith to battery only state.*/
    if (FALSE == is_chgr_present)
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:is_chg_charger_removed is_chgr_present=%d !\n",is_chgr_present);
        return TRUE;
    }
#endif/*MBB_CHG_WIRELESS*/
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:is_chg_charger_removed charger attached !\n");
        return FALSE;
    }
}

#if (MBB_CHG_WIRELESS == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : chg_stm_set_wireless_online_st
 ��������  : get the wireless online status.
 �������  : ONLINE: ���߳����λ
             OFFLINE:���߳�粻��λ
 �������  : None
 �� �� ֵ  : VOID.
*****************************************************************************/
void chg_stm_set_wireless_online_st(boolean online)
{
    chg_stm_state_info.wireless_online_st = online;
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:set_wireless_online_st=%d\n",online);
}

/*****************************************************************************
 �� �� ��  : chg_stm_get_wireless_online_st
 ��������  : get the wireless online status.
 �������  :
 �������  : ONLINE: ���߳����λ
             OFFLINE:���߳�粻��λ
 �� �� ֵ  : VOID.
*****************************************************************************/
boolean chg_stm_get_wireless_online_st(void)
{
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:get_wireless_online_st=%d\n",\
                chg_stm_state_info.wireless_online_st);

    return chg_stm_state_info.wireless_online_st;
}
#endif/*MBB_CHG_WIRELESS*/

#if (MBB_CHG_EXTCHG == FEATURE_ON)
/*****************************************************************************
�� �� ��  : chg_stm_set_extchg_online_st
��������  : get the extchg online status.
�������  : ONLINE: ���߳����λ
          OFFLINE:���߳�粻��λ
�������  : None
�� �� ֵ  : VOID.
*****************************************************************************/
void chg_stm_set_extchg_online_st(boolean online)
{
    chg_stm_state_info.extchg_online_st = online;
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:set_extchg_online_st=%d\n",online);
}

/*****************************************************************************
�� �� ��  : chg_stm_get_extchg_online_st
��������  : get the extchg online status.
�������  : ONLINE: ���߳����λ
          OFFLINE:���߳�粻��λ
�������  : None
�� �� ֵ  : VOID.
*****************************************************************************/
boolean chg_stm_get_extchg_online_st(void)
{
    if(TRUE == is_5577cs_falg)
    {
        return FALSE;
    }
     chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:get_extchg_online_st=%d\n",\
                            chg_stm_state_info.extchg_online_st);
    return chg_stm_state_info.extchg_online_st;
}
#endif/*MBB_CHG_EXTCHG*/

/*****************************************************************************
 �� �� ��  : chg_stm_set_cur_state
 ��������  : Update the current battery charge state to new state.
 �������  : new_state  The new state we gonna update to.
 �������  : None
 �� �� ֵ  : VOID.
 WHO-CALL  : chg_stm_init
             chg_stm_switch_state
 CALL-WHOM : None.
 NOTICE    : Helper function.
*****************************************************************************/
static void chg_stm_set_cur_state(chg_stm_state_type new_state)
{
    /*1. Update the current state machine state.*/
    chg_stm_state_info.cur_stm_state = new_state;
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:set_cur_state=%d\n",new_state);
}

/*****************************************************************************
 �� �� ��  : chg_stm_get_cur_state
 ��������  : Get current battery charge state: Fast charge, Transitition state, etc.
 �������  : None.
 �������  : None
 �� �� ֵ  : Current battery charge state.
 WHO-CALL  : DFT and other sub-modules.
 CALL-WHOM : None.
 NOTICE    : Need exported.
*****************************************************************************/
chg_stm_state_type chg_stm_get_cur_state(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:get_cur_state=%d\n",\
                    chg_stm_state_info.cur_stm_state);
    /*1. Return the current state.*/
    return chg_stm_state_info.cur_stm_state;
}

/*****************************************************************************
 �� �� ��  : chg_set_cur_chg_mode
 ��������  : set the current  charge mode
 �������  : new_state  The new state we gonna update to.
 �������  : None
 �� �� ֵ  : VOID.
 WHO-CALL  :
 CALL-WHOM : None.
 NOTICE    : Helper function.
*****************************************************************************/
void chg_set_cur_chg_mode(CHG_MODE_ENUM chg_mode)
{
    chg_stm_state_info.cur_chg_mode = chg_mode;
    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:set_cur_chg_mode=%d\n",chg_mode);
}

/*****************************************************************************
 �� �� ��  : chg_stm_get_cur_state
 ��������  : Get current battery charge state: Fast charge, Transitition state, etc.
 �������  : None.
 �������  : None
 �� �� ֵ  : Current battery charge state.
 WHO-CALL  : DFT and other sub-modules.
 CALL-WHOM : None.
 NOTICE    : Need exported.
*****************************************************************************/
CHG_MODE_ENUM chg_get_cur_chg_mode(void)
{

    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:get_cur_chg_mode =%d\n",\
                  chg_stm_state_info.cur_chg_mode);

    /*1. Return the current state.*/
    return chg_stm_state_info.cur_chg_mode;
}

/*****************************************************************************
 �� �� ��  : chg_get_charging_status
 ��������  : ��ȡ��ǰ�Ƿ����ڳ��
 �������  : None.
 �������  : None
 �� �� ֵ  : Current battery charge state.
 WHO-CALL  : DFT and other sub-modules.
 CALL-WHOM : None.
 NOTICE    : Need exported.
*****************************************************************************/
boolean chg_get_charging_status(void)
{
    chg_stm_state_type chg_stm_cur_state = CHG_STM_INIT_ST;
    chg_stm_cur_state = chg_stm_get_cur_state();
    /*1. Return the current state.*/
    if((CHG_STM_FAST_CHARGE_ST == chg_stm_cur_state) \
       || (CHG_STM_WARMCHG_ST == chg_stm_cur_state))
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:get_charging_status is charging!\n");
        return TRUE;
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:get_charging_status is not charging!\n");
        return FALSE;
    }
}


void chg_set_supply_limit_by_stm_stat(void)
{
    chg_chgr_type_t cur_chgr_type = chg_stm_get_chgr_type();
    chg_stm_state_type curr_state = chg_stm_get_cur_state();

    /*curr_stateҪ��Ϊ�����±��������������������Ҫ�ж�һ�ºϷ��ԡ�*/
    if (curr_state <= CHG_STM_INIT_ST || curr_state >= CHG_STM_MAX_ST)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Invalid state %d in %s.\n", 
            curr_state, __func__);
        return;
    }

    switch ( cur_chgr_type )
    {
        case CHG_WALL_CHGR:
        {
            chg_set_supply_limit(chg_std_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:resume supply current:%d\n",
                    chg_std_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
            break;
        }
        case CHG_USB_HOST_PC:
        {
            if ( CHG_CURRENT_SS == usb_speed_work_mode() )
            {
                chg_set_supply_limit(chg_usb3_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
                chg_print_level_message(CHG_MSG_INFO, "CHG_STM:resume supply current:%d\n",
                        chg_usb3_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
            }
            else
            {
                chg_set_supply_limit(chg_usb_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
                chg_print_level_message(CHG_MSG_INFO, "CHG_STM:resume supply current:%d\n",
                        chg_usb_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
            }
            break;
        }
        case CHG_500MA_WALL_CHGR:
        case CHG_NONSTD_CHGR:
        case CHG_CHGR_UNKNOWN:
        {
            chg_set_supply_limit(chg_usb_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:resume supply current:%d\n",
                    chg_usb_chgr_hw_paras[curr_state].pwr_supply_current_limit_in_mA);
            break;
        }
        default:
            break;
    }
}
/*****************************************************************************
 �� �� ��  : chg_set_hardware_parameter
 ��������  : Call the charge IC driver interfaces to config/update the hardware
             parameter according to the given hw_param.
 �������  : Pointer of hw_param struct be set.
 �������  : None
 �� �� ֵ  : VOID.
 WHO-CALL  : chg_check_and_update_hw_param_per_chgr_type.
             Entry function of state machine state.
 CALL-WHOM : None.
 NOTICE    : Some feature would NOT be supported on certain IC, charge IC
             driver will handle this situation.
*****************************************************************************/
void chg_set_hardware_parameter(const chg_hw_param_t* ptr_hw_param)
{
    uint32_t ret_code = 0;

#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    if (TRUE == usb_err_flag)
    {
        return;
    }
#endif

    /* ASSERT(ptr_hw_param != NULL); */
    if (NULL == ptr_hw_param)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:NULL pointer in chg_set_hardware_parameter!!\n");
        return;
    }

#if (FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT)
    if(TRUE == chg_battery_protect_flag)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:In battery protect condition do not update parameter!!\n");
        return;
    }
#endif

    /*Dump all the parameters to set.*/
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:[ILIMIT]: %dmA, [ICHG]: %dmA, [VBATREG]: %dmV.\n",
               ptr_hw_param->pwr_supply_current_limit_in_mA,
               ptr_hw_param->chg_current_limit_in_mA,
               ptr_hw_param->chg_CV_volt_setting_in_mV);

    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:[ITERM]: %dmA, [CHARGE]: %s.\n",
               ptr_hw_param->chg_taper_current_in_mA,
               ptr_hw_param->chg_is_enabled ? "enabled" : "disabled");

    /*1. Set power supply front-end current limit.*/
    if ( FALSE == chg_set_supply_limit(ptr_hw_param->pwr_supply_current_limit_in_mA))
    {
        /*If error occured, set 1st bit of ret_code.*/
        ret_code |= (1 << 1);
    }
    #if defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573BS) \
    || defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_607HW)\
    || defined(BSP_CONFIG_BOARD_E5577BS_937) || defined(BSP_CONFIG_BOARD_R218h)
        if(CHG_BATT_ID_DEF != chg_get_batt_id())
        {
             /*2. Set charge current.*/
            if ( FALSE == chg_set_cur_level(ptr_hw_param->chg_current_limit_in_mA))
            {
                /*If error occured, set 2nd bit of ret_code.*/
                ret_code |= (1 << 2);
            }

            /*3. Set CV voltage, IC type dependent, may not work on some IC, e.g. max8903c.*/
            if ( FALSE == chg_set_vreg_level(ptr_hw_param->chg_CV_volt_setting_in_mV))
            {
                /*If error occured, set 3rd bit of ret_code.*/
                ret_code |= (1 << 3);
            }
        }
        else
        {
            #if (FEATURE_ON == MBB_CHG_BQ24196)
            /*2. Set charge current.*/
            if ( FALSE == chg_set_cur_level(CHG_DEF_BATT_CUR_LEVEL))
            {
                /*If error occured, set 2nd bit of ret_code.*/
                ret_code |= (1 << 2);
            }
            #else /*!MBB_CHG_BQ24196*/
            /*chg_set_current_level���������IC������δ����*/
            #error You need check HOWTO implement this on your charger IC!!
            #endif
            /*3. Set CV voltage, IC type dependent, may not work on some IC, e.g. max8903c.*/
            if ( FALSE == chg_set_vreg_level(CHG_DEF_BATT_VREG_LEVEL))
            {
                /*If error occured, set 3rd bit of ret_code.*/
                ret_code |= (1 << 3);
            }
        }
    #else
        /*2. Set charge current.*/
        if ( FALSE == chg_set_cur_level(ptr_hw_param->chg_current_limit_in_mA))
        {
            /*If error occured, set 2nd bit of ret_code.*/
            ret_code |= (1 << 2);
        }

        /*3. Set CV voltage, IC type dependent, may not work on some IC, e.g. max8903c.*/
        if ( FALSE == chg_set_vreg_level(ptr_hw_param->chg_CV_volt_setting_in_mV))
        {
            /*If error occured, set 3rd bit of ret_code.*/
            ret_code |= (1 << 3);
        }
    #endif
    /*4. Set taper(terminate) current. Also IC type dependent, may not work on
         some IC, e.g. max8903c.*/
    if ( FALSE == chg_set_term_current(ptr_hw_param->chg_taper_current_in_mA))
    {
        /*If error occured, set 4th bit of ret_code.*/
        ret_code |= (1 << 4);
    }

    /*5. Enable/Disable Charge.*/
    if ( FALSE == chg_set_charge_enable(ptr_hw_param->chg_is_enabled))
    {
        /*If error occured, set 5th bit of ret_code.*/
        ret_code |= (1 << 5);
    }

    if (ret_code)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Set charge IC hw parameter error 0x%x.\n", ret_code);
    }

}

/*****************************************************************************
 �� �� ��  : chg_chgr_type_checking_timer_cb
 ��������  : Callback function of charger type checking timer.
             This timer is not autoload, we may re-start it in
             chg_check_and_update_hw_param_per_chgr_type.
 �������  : VOID.
 �������  : None
 �� �� ֵ  : VOID.
 WHO-CALL  : OS timer interrupt or task.
 CALL-WHOM : None.
 NOTICE    : This function run in timer context.
*****************************************************************************/
static void chg_chgr_type_checking_timer_cb(chg_timer_para data)
{
    (void)data;

    /*1. Send CHG_CHGR_TYPE_CHECKING event to main task.*/
    (void)chg_send_msg_to_main(CHG_CHGR_TYPE_CHECKING_EVENT);
     chg_print_level_message(CHG_MSG_INFO, "CHG_STM: chg_send_msg_to_main CHG_CHGR_TYPE_CHECKING_EVENT!\n ");
}
/*****************************************************************************
 �� �� ��  : chg_start_chgr_type_checking
 ��������  : Callback function of charger type checking timer.
             This timer is not autoload, we may re-start it in
             chg_check_and_update_hw_param_per_chgr_type.
 �������  : VOID.
 �������  : None
 �� �� ֵ  : VOID.
 WHO-CALL  : OS timer interrupt or task.
 CALL-WHOM : None.
 NOTICE    : This function run in timer context.
*****************************************************************************/
void chg_start_chgr_type_checking(void)
{
    chg_sta_timer_set(CHG_CHGR_TYPE_CHECK_INTERVAL_IN_MS,chg_chgr_type_checking_timer_cb);
}

/*****************************************************************************
 �� �� ��  : chg_check_and_update_hw_param_per_chgr_type
 ��������  : When chgr_type_checking timer expired, this function would be called
             via charge main task.
             As its name suggests, it will check the chgr type from USB and if got,
             update the charge hardware parameter, or re-fire the timer utils max
             retry time reached.
 �������  : VOID.
 �������  : None
 �� �� ֵ  : VOID.
 WHO-CALL  : Charge Main Task.
 CALL-WHOM : None.
 NOTICE    : If max retry time reached, the chgr type would be set to CHG_NONSTD_CHGR.
             Need exported.
*****************************************************************************/
void chg_check_and_update_hw_param_per_chgr_type(void)
{
    static uint8_t chgr_type_checking_cnter = 0;
    chg_chgr_type_t chgr_type_from_usb = chg_stm_get_chgr_type();
    chg_stm_state_type curr_state = chg_stm_get_cur_state();

    /*1. If charger removal detected, give warning msg, return.*/
    if (FALSE == chg_is_charger_present())
    {
        chgr_type_checking_cnter = 0;
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Chgr has been removed, type checking ignored.\n");
        return;
    }

    /*2. If chgr_type from USB is still CHG_CHGR_UNKNOWN:
       ->Y  a. IF chgr_type_checking_cnter >= CHG_CHGR_TYPE_CHECK_MAX_RETRY_TIMES
                  chg_stm_set_chgr_type(CHG_NONSTD_CHGR); return;
               ELSE
                  chgr_type_checking_cnter++;
                  chgr_type_checking_timer;
       ->N  b. IF chgr_type != CHG_WALL_CHGR
                  chg_stm_set_chgr_type(chgr_type); return;
               ELSE
                  chg_stm_set_chgr_type(CHG_WALL_CHGR);
                  1) IF curr_state == FAST_CHG_STATE || INVALID_CHG_TEMP_STATE || MAINT_STATE
                        chg_set_hardware_parameter(&chg_std_chgr_hw_param[curr_state]);
                     ELSE
                        Give error msg.
     */

    if (CHG_CHGR_UNKNOWN == chgr_type_from_usb)
    {
        if (chgr_type_checking_cnter >= CHG_CHGR_TYPE_CHECK_MAX_RETRY_TIMES)
        {
            chgr_type_checking_cnter = 0;
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Chgr type check timeout failed," \
                       " treat as non-standard.\n");
            mlog_print(MLOG_CHG, mlog_lv_warn, "CHG_STM:Charger type check timeout failed," \
                       " treat as non-standard.\n");
            chg_stm_set_chgr_type(CHG_NONSTD_CHGR);
        }
        else
        {
            chgr_type_checking_cnter++;
            chg_sta_timer_set(CHG_CHGR_TYPE_CHECK_INTERVAL_IN_MS,
                              chg_chgr_type_checking_timer_cb);
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Raise %d time chgr type checking.\n",
                       chgr_type_checking_cnter);
        }

        return;
    }
    else if((CHG_WALL_CHGR == chgr_type_from_usb) || (CHG_USB_HOST_PC == chgr_type_from_usb)
             || (CHG_NONSTD_CHGR == chgr_type_from_usb))
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Chgr type %d attached after %d times polling.\n",
            chgr_type_from_usb, chgr_type_checking_cnter + 1);
        mlog_print(MLOG_CHG, mlog_lv_info, "CHG_STM:Charger type %d attached " \
                   "after %d times polling.\n",
                   chgr_type_from_usb, chgr_type_checking_cnter + 1);
        chgr_type_checking_cnter = 0;
        if (CHG_WALL_CHGR != chgr_type_from_usb)
        {
            if ((CHG_USB_HOST_PC == chgr_type_from_usb) && (CHG_CURRENT_SS == usb_speed_work_mode()))
            {
                chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:[chg_check_and_update_hw_param_per_chgr_type]set usb 3.0 charge parameter\n\r");
                chg_set_hardware_parameter(&chg_usb3_chgr_hw_paras[curr_state]);
            }
            else
            {
                 chg_print_level_message(CHG_MSG_INFO, "CHG_STM:USB/3rd chgr, no need update hw paras.\n");
            }
        }
        else
        {
            if (curr_state == CHG_STM_FAST_CHARGE_ST
                || curr_state == CHG_STM_WARMCHG_ST
                || curr_state == CHG_STM_MAINT_ST
                || curr_state == CHG_STM_INVALID_CHG_TEMP_ST)
            {
                chg_en_flag = 1;
                chg_en_timestamp = jiffies;
                chg_set_hardware_parameter(&chg_std_chgr_hw_paras[curr_state]);
            }
            else
            {
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Invalid stm state %d "    \
                           "during chgr type checking.\n", curr_state);
            }
        }
    }
    else if(CHG_500MA_WALL_CHGR == chgr_type_from_usb)
    {
        chgr_type_checking_cnter = 0;
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[curr_state]);
    }
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    else if(CHG_WIRELESS_CHGR == chgr_type_from_usb)
    {
        chgr_type_checking_cnter = 0;
        chg_set_hardware_parameter(&chg_wireless_chgr_hw_paras[curr_state]);
        mlog_print(MLOG_CHG, mlog_lv_info, "Wireless charger detected in polling check.\n");
    }
#endif/*MBB_CHG_WIRELESS*/
    else
    {
        chgr_type_checking_cnter = 0;
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Invalid chgr_type!\n");
    }
#if (MBB_CHG_HIGH_VOLT_BATT == FEATURE_ON)
    if (CHG_CHGR_UNKNOWN != chgr_type_from_usb)
    {
        chg_hw_para_updated = 1;
    }
#endif
}

/*****************************************************************************
 �� �� ��  : chg_stm_switch_state
 ��������  : Charge State Machine Switch State function. State Machine or other
             Sub-Module call this function change the battery charge state.
 �������  : new_state  The new state we gonna switch to.
 �������  : None
 �� �� ֵ  : VOID
 WHO-CALL  : All states' periodic function.
             Polling timer and charger insertion/removal event(BH)
             from charge task.
 CALL-WHOM : The exit function of current state.
             The entry function of new state.
 NOTICE    : If the new_state is Transition State, its periodic would be called.
*****************************************************************************/
void chg_stm_switch_state(chg_stm_state_type new_state)
{
    /*1. Get the system current state.*/

    /*2. Check the new state validity, or give error msg.*/

    /*3. new_state differ from curr_state
    ->Y  Switching state...
         a. If current state is not default initial state, do exit.
         b. Give info msg that system state switch from curr_state to new_state.
         c. Set the current state to new state.
         d. Do entry of new_state.
         e. If new_state is transition state, do periodic function.
    ->N  Give warning msg.
     */
    chg_stm_state_type cur_state = chg_stm_get_cur_state();
    if((cur_state >= CHG_STM_MAX_ST) || (cur_state <= CHG_STM_INIT_ST))
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_stm_switch_state: cur_state Invalid \n");
        return;
    }

    #if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
    chg_stm_set_pre_state(cur_state);
    #endif /* MBB_CHG_WARM_CHARGE */

    if (new_state >= CHG_STM_MAX_ST || new_state <= CHG_STM_INIT_ST)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_stm_switch_state: Invalid state %d.\n", new_state);
        return;
    }

     chg_stm_set_cur_state(new_state);
    if (cur_state != new_state)
    {
        if (NULL != chg_stm_state_machine[cur_state].chg_stm_exit_func)
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_stm_switch_state exit %d state.\n", cur_state);
            chg_stm_state_machine[cur_state].chg_stm_exit_func();
        }
        else
        {
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Cur_state %d exit func doesN'T exist.\n", cur_state);
        }

        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:Charge state machine switch from %d to %d state.\n",
            cur_state, new_state);
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:Charge state machine switch from %s to %s state.\n",
            (CHG_STM_INIT_ST == cur_state) ? "Init" : TO_STM_NAME(cur_state),
            TO_STM_NAME(new_state));


        if (NULL != chg_stm_state_machine[new_state].chg_stm_entry_func)
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_stm_switch_state entry %d state.\n", new_state);
            chg_stm_state_machine[new_state].chg_stm_entry_func();
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:New_state %d entry func doesN'T exist.\n", new_state);
        }

        /*added by ligang to shorten ui display time*/
        if ((CHG_STM_TRANSIT_ST == new_state)
            && (NULL != chg_stm_state_machine[new_state].chg_stm_period_func))
        {
            /*�л�ǰ����һ�ε�ص�ѹ��ѯ��ѯ**/
            chg_poll_bat_level();
            /* �л�ǰ����һ�ε���¶���ѯ��ѯ**/
            chg_poll_batt_temp();
            chg_stm_state_machine[new_state].chg_stm_period_func();
        }

        if (CHG_STM_INVALID_CHG_TEMP_ST == new_state)
        {
            mlog_print(MLOG_CHG, mlog_lv_warn, "CHG STM switch from %s to invalid chg temp state. "
                "tBat = %d'C, tBat_sys = %d'C.\n",
                (CHG_STM_INIT_ST == cur_state) ? "Init" : TO_STM_NAME(cur_state),
                chg_get_cur_batt_temp(), chg_get_sys_batt_temp());
        }

        mlog_print(MLOG_CHG, mlog_lv_info, "CHG STM switch from %s to %s state.\n",
            (CHG_STM_INIT_ST == cur_state) ? "Init" : TO_STM_NAME(cur_state),
            TO_STM_NAME(new_state));
        (void)chg_dump_ic_hwinfo();
        mlog_print(MLOG_CHG, mlog_lv_info, "Current Battery Info: [vBat]%dmV, [vBat_sys]%dmV, " \
            "[tBat]%d'C, [tBat_sys]%d'C.\n", chg_get_cur_batt_volt(), chg_get_sys_batt_volt(),
            chg_get_cur_batt_temp(), chg_get_sys_batt_temp());
#if ( FEATURE_ON == MBB_MLOG )
        if(((CHG_STM_FAST_CHARGE_ST == new_state) && (CHG_STM_WARMCHG_ST != cur_state)) || 
            ((CHG_STM_WARMCHG_ST == new_state) && (CHG_STM_FAST_CHARGE_ST != cur_state)))
        {
            printk(KERN_ERR, "CHG_STM:charge_count\n");
            mlog_set_statis_info("charge_count",1);//����ܴ��� ��1
        }
        if(CHG_STM_WARMCHG_ST == new_state)
        {
            printk(KERN_ERR,"CHG_STM:overtemp_charge_count\n");
            mlog_set_statis_info("overtemp_charge_count",1);//���³�������1
        }
        if(CHG_STM_INVALID_CHG_TEMP_ST == new_state) 
        {
            printk(KERN_ERR, "CHG_STM:overtemp_charge_stop_count\n");
            mlog_set_statis_info("overtemp_charge_stop_count",1); //����ͣ�������1
        }
#endif        
    }
    else
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_stm_switch_state: charge has already be %s[%d] state, " \
                         "no need switch.\n", TO_STM_NAME(cur_state), cur_state);
    }
}

/*****************************************************************************
 �� �� ��  : chg_stm_periodic_checking_func
 ��������  : Periodic checking function of charge state machine. Charge main
             task would call it periodically once polling timer triggered.
 �������  : None
 �� �� ֵ  : VOID
 WHO-CALL  : chg main task.
 CALL-WHOM : All states' period function.
 NOTICE    : The periodic function of transition state should NOT be called
             here.
             It's better NOT to call this function in timer/interrupt context.
             Need Exported.
*****************************************************************************/
void chg_stm_periodic_checking_func(void)
{
    chg_stm_state_type chg_current_st = CHG_STM_INIT_ST;
    chg_chgr_type_t    chg_cur_chgr   = CHG_CHGR_UNKNOWN;

    uint32_t chg_prt_timer_val = 0;
    int32_t  cur_poll_timer_period  = 0;
    /*0:-PwrOff Charging; 1:-Normal Charging.*/
    uint8_t  is_normal_chg_mode     = !chg_is_powdown_charging();
    /*0:-USB/NoStd Chgr;  1:-Wall/Standard Chgr.*/
    uint8_t  is_std_wall_chgr       = (CHG_WALL_CHGR == chg_stm_get_chgr_type());

    /* Get the current battery charging state */
    chg_current_st = chg_stm_get_cur_state();

    if(1 == chg_en_flag)
    {
        unsigned long time_now = jiffies;
        if((time_now - chg_en_timestamp) > CHG_EN_TIME_SLOT) 
        {
            chg_en_flag = 0;
        }
    }
    else
    {
        //for lint
    }

    /*Make sure that we are within the charger state machine
      configuration table*/
    if (chg_current_st > CHG_STM_INIT_ST && chg_current_st < CHG_STM_MAX_ST)
    {
        /* If we have a valid state function, call it. */
        if (NULL != chg_stm_state_machine[chg_current_st].chg_stm_period_func)
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:stm_periodic_checking_func polling at %d state\n", chg_current_st);
            chg_stm_state_machine[chg_current_st].chg_stm_period_func();
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:State %d haveNOT period func.\n", chg_current_st);
        }

        if (CHG_STM_TRANSIT_ST == chg_current_st)
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Transition state while period checking.\n");
        }
        /*Obtain current_st once again, since chg state may be updated in period_func*/
        chg_current_st = chg_stm_get_cur_state();
        chg_cur_chgr   = chg_stm_get_chgr_type();

        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Charge stay at %s[%d] state now.\n",
            TO_STM_NAME(chg_current_st), chg_current_st);
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:Current chgr is %s[%d].\n",
            TO_CHGR_NAME(chg_cur_chgr), chg_cur_chgr);

        if(TRUE == chg_get_charging_status())
        {
            chg_prt_timer_val = chg_fastchg_timeout_value_in_sec[is_normal_chg_mode][is_std_wall_chgr];
            if (chg_stm_state_info.charging_lasted_in_sconds < chg_prt_timer_val)
            {
                chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System keep staying at charging state.\n");

                cur_poll_timer_period = chg_poll_timer_get();
                if (CHG_ERROR == cur_poll_timer_period)
                {
                    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_poll_timer_get error.\n");

                }
                else
                {
                    /*���δ��ʱ��־λ��Ϊfalse*/
                    chg_time_expired_flag = FALSE;
                    chg_stm_state_info.charging_lasted_in_sconds +=
                                   ((uint32_t)cur_poll_timer_period / MS_IN_SECOND);
                    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:charging has lasted for %d Seconds.\n",
                                            chg_stm_state_info.charging_lasted_in_sconds);
                }
            }
            else
            {
                chg_print_level_message(CHG_MSG_INFO, "CHG_STM:charging SW timer expired, " \
                       "battery voltage(sys) %dmV.\n", chg_get_sys_batt_volt());

                /*If battery is full already, or at pwroff chg mode, goto maint state.*/
                if (TRUE == chg_is_batt_full() || FALSE == is_normal_chg_mode)
                {
                   /*4. Reset fast charge counter.and switch to manit state,disable chg*/
                   /*�ػ�״̬��糬ʱ������־λ��Ϊtrue������ǰ�жϴ˱�־λ*/
                   if (FALSE == is_normal_chg_mode)
                   {
                       chg_time_expired_flag = TRUE;
                   }
                   chg_stm_switch_state(CHG_STM_MAINT_ST);
                   chg_stm_state_info.charging_lasted_in_sconds = 0;
                }
                else
                {
                    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Reset charging counter, " \
                           "continue to charge.\n");
                 /*Reset fast charge counter and continue to charge */
                    chg_stm_state_info.charging_lasted_in_sconds = 0;
                }

                mlog_print(MLOG_CHG, mlog_lv_warn, "Charging SW timer expired, " \
                       "battery voltage(sys) %dmV.\n", chg_get_sys_batt_volt());
                mlog_print(MLOG_CHG, mlog_lv_warn, "current state: %s, current charger:%s.\n",
                    TO_STM_NAME(chg_current_st), TO_CHGR_NAME(chg_cur_chgr));
            }
        }
        else
        {
            chg_stm_state_info.charging_lasted_in_sconds = 0;
        }
        /*���ͣ�䵫�������λ��ʱ��*/
#if ( FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT )
        if ((TRUE ==  chg_is_charger_present())
            && (FALSE == chg_get_charging_status())
            && (BATT_CAPACITY_FULL == chg_real_info.bat_capacity))
        {
            cur_poll_timer_period = chg_poll_timer_get();
            if (CHG_ERROR == cur_poll_timer_period)
            {
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_poll_timer_get error.\n");
            }
            else
            {
                chg_stm_state_info.charger_lasted_without_charging_in_seconds +=
                               ((uint32_t)cur_poll_timer_period / MS_IN_SECOND);
                chg_print_level_message(CHG_MSG_INFO,
                                        "CHG_STM:charger has existed without charging for %d Seconds.\n",
                                        chg_stm_state_info.charging_lasted_in_sconds);
            }
        }
        else
        {
            chg_stm_state_info.charger_lasted_without_charging_in_seconds = 0;
        }
#endif
    }
    else
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Invalid state %d in period checking.\n", chg_current_st);
    }
}

/*****************************************************************************
 �� �� ��  : chg_notify_UI_charging_state
 ��������  : Notify the UI battery charging state changed.
             If the battery charging state didn't changed, this function doesn't
             take effect.
 �������  : bc_state: new battery charging state.
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: Entry function of every states.
 NOTICE    : This function is platform dependent.
*****************************************************************************/
static void chg_notify_UI_charging_state(uint8_t bc_state)
{
    /*Don't display battery charging as default.*/
    uint8_t   new_bc_state         = !!bc_state;
    uint8_t   is_pwr_off_charging  = chg_is_powdown_charging();
    BATTERY_EVENT  event_to_send   = BAT_EVENT_MAX;
    static uint8_t cur_ui_bc_state = 0;

    if (new_bc_state != cur_ui_bc_state)
    {
        if (new_bc_state)
        {
            if (is_pwr_off_charging)
            {
                event_to_send = BAT_CHARGING_OFF_START;
            }
            else
            {
                event_to_send = BAT_CHARGING_ON_START;
            }
        }
        else
        {
            if (is_pwr_off_charging)
            {
                event_to_send = BAT_CHARGING_DOWN_STOP;
            }
            else
            {
                event_to_send = BAT_CHARGING_UP_STOP;
            }
        }
        cur_ui_bc_state = new_bc_state;

        /*Send the event to UI module.*/
        chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY, event_to_send);
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Send battery event %d to APP.\n", event_to_send);
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:UI bc state is already %d.\n", cur_ui_bc_state);
    }
}

/*****************************************************************************
 �� �� ��  : chg_transit_state_entry_func
 ��������  : Charge Transistion State entry function. Initialize all the
             statistic of current state: reset charger type, relevant timers,
             keep the UI battery charging status.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_switch_state
 PREVIOUS  : Initial State(Not REAL state)
             Battery Only State.
 NOTICE    : System can't stay at this state more than ONE polling timer
             period.
*****************************************************************************/
static void chg_transit_state_entry_func(void)
{
    boolean is_chgr_present      = chg_is_charger_present();
    chg_chgr_type_t cur_chgr_type = chg_stm_get_chgr_type();

    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System enter into transition state.\n");

    /*1. Reset charger type to INVALID will be done at:
         a. chg_stm_init() when system just powered up.
         b. Entry function of battery only state when normal running.
     */

    /*2. Don't change UI battery charging state, just KEEP is OK.*/

    /*3. Set poll timer mode, FAST or CHGR_INPUT, will be done:
         a. When system just powered up: chg_stm_init or other module init function.
         b. For CHGR_INPUT: period func.
     */
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:fastchg_state_period is_chgr_present=%d, cur_chgr_type=%d.\n",
                        is_chgr_present,cur_chgr_type);
    chg_poll_timer_set(FAST_POLL_CYCLE);
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:transit_state_entry_func poll_timer_set FAST_POLL_CYCLE.\n");

    /*4. IF chgr_is_present
       ->Y: 1. Read chgr type from USB, Set chgr_type
            IF chgr type still unknown
          ->Y: Raise chgr type checking timer.
            2. Set charging hardware parameter per charger type
     */
    if (TRUE == is_chgr_present)
    {
        if (CHG_CHGR_UNKNOWN == cur_chgr_type)
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:Chgr type unknown, raise checking timer.\n");
            /*chg_sta_timer_set(CHG_CHGR_TYPE_CHECK_INTERVAL_IN_MS,
                              chg_chgr_type_checking_timer_cb);*/
        }
        else
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Chgr_type = %d in transit entry.\n", cur_chgr_type);
        }

        /*Config charge hardware parameter according to chgr_type.*/
        if (CHG_WALL_CHGR == cur_chgr_type)
        {
            chg_set_hardware_parameter(&chg_std_chgr_hw_paras[CHG_STM_TRANSIT_ST]);
        }
        //usb 3.0����
        else if ((CHG_USB_HOST_PC == cur_chgr_type) && CHG_CURRENT_SS == usb_speed_work_mode())
        {
            chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:[chg_transit_state_entry_func]set usb 3.0 charge parameter\n\r");
            chg_set_hardware_parameter(&chg_usb3_chgr_hw_paras[CHG_STM_TRANSIT_ST]);
        }
        else if (CHG_500MA_WALL_CHGR == cur_chgr_type)
        {
            chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_TRANSIT_ST]);
        }
        //usb2.0����
        else
        {
            chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_TRANSIT_ST]);
        }

        mlog_print(MLOG_CHG, mlog_lv_info, "charger type %d insertion detected.\n", cur_chgr_type);
    }
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    else
    {
        if(CHG_WIRELESS_CHGR == cur_chgr_type)
        {
            /*һֱ�����߳��оƬʹ�ܣ����߳������и�״̬��ʹ����BQ24196����*/
            chg_set_wireless_chg_enable(TRUE);
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_transit_state_entry_func disable wireless chg!\n");
            chg_set_hardware_parameter(&chg_wireless_chgr_hw_paras[CHG_STM_TRANSIT_ST]);

            mlog_print(MLOG_CHG, mlog_lv_info, "wireless charger detected.\n", cur_chgr_type);
        }
        else
        {
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_transit_state_entry_func Is not wireless !\n");
        }
    }
#endif/*MBB_CHG_WIRELESS*/
}

/*****************************************************************************
 �� �� ��  : chg_transit_state_period_func
 ��������  : Charge Transistion State periodic polling function, which get called
             when polling timer event triggered.
             This function checks all the system condition, then choose the right
             state to swith.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_switch_state
             chg_main_poll_cb(?)
 NOTICE    : Transition state is transient(unstable), as its name suggests.
             Thus system can't stay at this state more than ONE polling timer
             period.
*****************************************************************************/
static void chg_transit_state_period_func(void)
{
     /*1. IF charger_remove
             Switch to batttery only state.
       */
    if(TRUE == is_chg_charger_removed())
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg not exist force transit_st to batt_only_st!\n");
        chg_stm_switch_state(CHG_STM_BATTERY_ONLY);

    }

    /*2. IF vBat > batt_volt_full_threshold || batt OVP
            Switch to maintenance state.
     */
    else if (TRUE == chg_is_batt_full_for_start() || TRUE == chg_is_batt_ovp())
    
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:Batt full/OVP, vBat = %dmV, vBat_sys = %dmV.\n",
            chg_get_cur_batt_volt(), chg_get_sys_batt_volt());
        mlog_print(MLOG_CHG, mlog_lv_warn, "CHG_STM:Batt full/OVP, vBat = %dmV, vBat_sys = %dmV.\n",
                   chg_get_cur_batt_volt(), chg_get_sys_batt_volt());
        chg_stm_switch_state(CHG_STM_MAINT_ST);
    }

    /*3. IF Battery is too hot or too cold
            Switch to invalid charge battery temperature state.
     */
    else if (FALSE == chg_is_batt_temp_valid())
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Invalid batt-temp, tBat = %d'C, tBat_sys = %d'C.\n",
            chg_get_cur_batt_temp(), chg_get_sys_batt_temp());
        mlog_print(MLOG_CHG, mlog_lv_warn, "CHG_STM:Invalid batt-temp, tBat = %d'C, " \
                   "tBat_sys = %d'C.\n", chg_get_cur_batt_temp(), chg_get_sys_batt_temp());
        chg_stm_switch_state(CHG_STM_INVALID_CHG_TEMP_ST);
    }

#if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
    else if(TRUE == is_batttemp_in_warm_chg_area())
    {
         chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Switch transit state to warmchg state, tBat = %d'C, tBat_sys = %d'C.\n",
         chg_get_cur_batt_temp(), chg_get_sys_batt_temp());
         chg_stm_switch_state(CHG_STM_WARMCHG_ST);
    }
#endif /* MBB_CHG_WARM_CHARGE */

    /*4. ELSE Switch to fast chg state.*/
    else
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:form transit_state to fast_stste!\n");
        chg_stm_switch_state(CHG_STM_FAST_CHARGE_ST);
    }
}

/*****************************************************************************
 �� �� ��  : chg_transit_state_exit_func
 ��������  : Charge Transistion State exit function.
             This function get called when system exit from Transition State,
             to do some clean/destroy stuff.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_switch_state
 NEXT      : All other states except transition state itself.
 NOTICE    : TO BE CHECKED: WHETHER NECESSARY.
             MAY BE REMOVED IN FUTURE.
*****************************************************************************/
static void chg_transit_state_exit_func(void)
{
   chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System exit from transition state.\n");
}
#if (MBB_CHG_HIGH_VOLT_BATT == FEATURE_ON)
/*******************************************************************
Function:      chg_set_high_volt_batt_current
Description:   ����0-10�ȳ�����
Data Accessed: ��
Data Updated:  ��
Input:         ���������
Return:        ��
*******************************************************************/
void chg_set_high_volt_batt_current(chg_chgr_type_t cur_chgr_type )
{
    switch(cur_chgr_type)
    {
        case CHG_WALL_CHGR:
        {
            #if defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577S_932) \
            || defined(BSP_CONFIG_BOARD_E5577S_324) || defined(BSP_CONFIG_BOARD_E5577BS_937)
            if((FALSE == is_5577cs_falg)&&(TRUE == is_bat_3000))
            {
                chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_WALL_H);
            }
            else
            {
                chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_WALL);
            }
            #elif defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573BS)\
            || defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_607HW) \
            || defined(BSP_CONFIG_BOARD_R218h)
            if (CHG_BATT_ID_DEF != chg_get_batt_id())
            {
                chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_WALL);
            }
            else
            {
                #if (FEATURE_ON == MBB_CHG_BQ24196)
                chg_set_cur_level(CHG_DEF_BATT_CUR_LEVEL);
                #else /*!MBB_CHG_BQ24196*/
                /*chg_set_current_level?????IC??????*/
                #error You need check HOWTO implement this on your charger IC!!
                #endif
            }
            #else
            chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_WALL);
            #endif

            break;  
        }
        case CHG_USB_HOST_PC:
        {
            if(CHG_CURRENT_SS == usb_speed_work_mode())
            {
                #if defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577S_932) \
               || defined(BSP_CONFIG_BOARD_E5577S_324) || defined(BSP_CONFIG_BOARD_E5577BS_937)
                if((FALSE == is_5577cs_falg)&&(TRUE == is_bat_3000))
                {
                    chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB3_H); 
                }
                else
                {
                    chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB3); 
                }
                #elif defined(BSP_CONFIG_BOARD_E5573CS) ||defined(BSP_CONFIG_BOARD_E5573BS) \
                || defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_607HW) \
                || defined(BSP_CONFIG_BOARD_R218h)
                if (CHG_BATT_ID_DEF != chg_get_batt_id())
                {
                    chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB3); 
                }
                else
                {
                    #if (FEATURE_ON == MBB_CHG_BQ24196)
                    chg_set_cur_level(CHG_DEF_BATT_CUR_LEVEL);
                    #else /*!MBB_CHG_BQ24196*/
                    /*chg_set_current_level?????IC??????*/
                    #error You need check HOWTO implement this on your charger IC!!
                    #endif
                }
                #else
                chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB3); 
                #endif
                              

            }
            else
            {
                #if defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577S_932) \
              || defined(BSP_CONFIG_BOARD_E5577S_324)|| defined(BSP_CONFIG_BOARD_E5577BS_937)
                if((FALSE == is_5577cs_falg)&&(TRUE == is_bat_3000))
                {
                    chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB2_H); 
                }
                else
                {
                    chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB2);
                }
                #elif defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573BS)\
                || defined(BSP_CONFIG_BOARD_E5573CS_933)|| defined(BSP_CONFIG_BOARD_607HW) \
                || defined(BSP_CONFIG_BOARD_R218h)
                if (CHG_BATT_ID_DEF != chg_get_batt_id())
                {
                    chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB2);
                }
                else
                {
                    #if (FEATURE_ON == MBB_CHG_BQ24196)
                    chg_set_cur_level(CHG_DEF_BATT_CUR_LEVEL);
                    #else /*!MBB_CHG_BQ24196*/
                    /*chg_set_current_level?????IC??????*/
                    #error You need check HOWTO implement this on your charger IC!!
                    #endif
                }
                #else
                chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB2); 
                #endif

            }
            break;
        }
        case CHG_500MA_WALL_CHGR:
        case CHG_NONSTD_CHGR:
        {
            #if defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577S_932) \
           || defined(BSP_CONFIG_BOARD_E5577S_324)|| defined(BSP_CONFIG_BOARD_E5577BS_937)
            if((FALSE == is_5577cs_falg)&&(TRUE == is_bat_3000))
            {
                chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB2_H); 
            }
            else
            {
                chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB2);
            }
            #elif defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573BS)\
            || defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_607HW) \
            || defined(BSP_CONFIG_BOARD_R218h)
            if (CHG_BATT_ID_DEF != chg_get_batt_id())
            {
                chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB2);
            }
            else
            {
                #if (FEATURE_ON == MBB_CHG_BQ24196)
                chg_set_cur_level(CHG_DEF_BATT_CUR_LEVEL);
                #else /*!MBB_CHG_BQ24196*/
                /*chg_set_current_level?????IC??????*/
                #error You need check HOWTO implement this on your charger IC!!
                #endif
            }
            #else
            chg_set_cur_level(CHG_SUB_LOW_TEMP_CURR_USB2); 
            #endif

            break;
        }
        default:
        break;
    }
}
/*******************************************************************
Function:      chg_high_volt_batt_entry_func
Description:   ����0-10�ȳ�����
Data Accessed: ��
Data Updated:  ��
Input:         ��
Return:        ��
*******************************************************************/
void chg_high_volt_batt_entry_func(void)
{
    uint32_t battry_temp = chg_get_sys_batt_temp();
    chg_chgr_type_t cur_chgr_type = chg_stm_get_chgr_type();
    
    chg_sub_low_temp_changed = -1;

    if(0 == chg_hw_para_updated)
    {
        /*��������δ����*/
        return;
    }
#if( FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT )
    if( TRUE == chg_battery_protect_flag )
    {
        if( 0 == chg_sub_low_temp_changed )
        {
            chg_sub_low_temp_changed = -1;
        }
        return;
    }
#endif
    if (battry_temp <= CHG_SUB_LOW_TEMP_TOP)
    {
        chg_sub_low_temp_changed = 0;
        chg_set_high_volt_batt_current(cur_chgr_type);
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:set high batt current in 0-10c!\n");
    }
}
/*******************************************************************
Function:      chg_high_volt_batt_period_func
Description:   ����0-10�ȳ�����
Data Accessed: ��
Data Updated:  ��
Input:         ��
Return:        ��
*******************************************************************/
void chg_high_volt_batt_period_func(void)
{
    uint32_t battry_temp = chg_get_sys_batt_temp();
    chg_chgr_type_t cur_chgr_type = chg_stm_get_chgr_type();
    
    if(0 == chg_hw_para_updated)
    {
        /*��������δ����*/
        return;
    }

#if( FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT )
    if( TRUE == chg_battery_protect_flag )
    {
        if( 0 == chg_sub_low_temp_changed )
        {
            chg_sub_low_temp_changed = -1;
        }
        return;
    }
#endif

    /* �����¶�����ת�����ó����� */
    if (battry_temp <= CHG_SUB_LOW_TEMP_TOP && -1 == chg_sub_low_temp_changed)
    {
        chg_sub_low_temp_changed = 0;
        chg_set_high_volt_batt_current(cur_chgr_type);
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:set high batt current in 0-10c!\n");
    }
    else if (battry_temp >= (CHG_SUB_LOW_TEMP_TOP + CHG_TEMP_RESUM) && 0 == chg_sub_low_temp_changed)
    {
        chg_sub_low_temp_changed = -1;
        #if defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573BS)\
        || defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_607HW)\
        || defined(BSP_CONFIG_BOARD_E5577BS_937) || defined(BSP_CONFIG_BOARD_R218h)
        if (CHG_BATT_ID_DEF != chg_get_batt_id())
        {
            chg_set_cur_level(chg_std_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST].chg_current_limit_in_mA);
        }
        else
        {
            chg_print_level_message(CHG_MSG_INFO, "Unknown batt type, use safer chg paras.\n");
            #if (FEATURE_ON == MBB_CHG_BQ24196)
            chg_set_cur_level(CHG_DEF_BATT_CUR_LEVEL);
            #else /*!MBB_CHG_BQ24196*/
            /*chg_set_current_level���������IC������δ����*/
            #error You need check HOWTO implement this on your charger IC!!
            #endif
        }
        #else
        chg_set_cur_level(chg_std_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST].chg_current_limit_in_mA);
        #endif
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:resume high batt current in 0-10c!\n");
    }
}
#endif

/*****************************************************************************
 �� �� ��  : chg_fastchg_state_entry_func
 ��������  : Charge Fast Charge State entry function. Initialize all the
             statistic of current state: reset fast charge timer, notify the
             UI that battery charging started.
             Set the corresponding charging parameter per charger type.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 PREVIOUS  : Transition State.
             Maintenance State.
             Invalid Charge Temperature State.
 WHO-CALLED: chg_switch_state
 NOTICE    : If charger type unknown, treat it as CHG_NONSTD_CHGR.
*****************************************************************************/
static void chg_fastchg_state_entry_func(void)
{
    chg_chgr_type_t cur_chgr_type = chg_stm_get_chgr_type();
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System enter into fast-charge state.\n");

    /*1. Notify UI that battery charging started.*/
    chg_notify_UI_charging_state(CHG_UI_START_CHARGING);

    /*2. Set charging hardware parameter per charger type.*/
    if (CHG_WALL_CHGR == cur_chgr_type)
    {
        /*ʹ�ܳ�磬���ñ�־*/  
        chg_en_flag = 1;
        chg_en_timestamp = jiffies;
        chg_set_hardware_parameter(&chg_std_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST]);

        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:fastchg_state_entry set std_chgr_hw_paras!\n");

    }
    else if (CHG_500MA_WALL_CHGR == cur_chgr_type)
    {
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST]);
    }
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    else if((CHG_USB_HOST_PC == cur_chgr_type) && CHG_CURRENT_SS == usb_speed_work_mode())
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:[chg_fastchg_state_entry_func]set usb 3.0 charge parameter\n\r");
        chg_set_hardware_parameter(&chg_usb3_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST]);
    }
    else if((CHG_USB_HOST_PC == cur_chgr_type) || (CHG_NONSTD_CHGR == cur_chgr_type)
            || (CHG_CHGR_UNKNOWN == cur_chgr_type))
    {
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST]);
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:fastchg_state_entry set usb_chgr_hw_paras!\n");
    }

    else if(CHG_WIRELESS_CHGR == cur_chgr_type)
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_fastchg_state_entry_func enable wireless chg!\n");
        chg_set_hardware_parameter(&chg_wireless_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST]);
    }
    else
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_fastchg_state_entry_func Is not wireless !\n");
    }
#else
    else if((CHG_USB_HOST_PC == cur_chgr_type) && CHG_CURRENT_SS == usb_speed_work_mode())
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:chg_fastchg_state_entry_funcset usb 3.0 charge parameter\n\r");
        chg_set_hardware_parameter(&chg_usb3_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST]);
    }
    else
    {
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST]);
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:fastchg_state_entry set usb_chgr_hw_paras!\n");
    }
#endif/*MBB_CHG_WIRELESS*/
    /*3. Enable IC Charge function.*/
    /*Already done in chg_set_hardware_parameter.*/
    
#if (MBB_CHG_HIGH_VOLT_BATT == FEATURE_ON)
    chg_high_volt_batt_entry_func();
#endif

}

/*****************************************************************************
 �� �� ��  : chg_fastchg_state_period_func
 ��������  : Charge Fast Charge State periodic polling function, which get called
             when polling timer event triggered.
             This function checks the system condition, choose the right
             state to swith if system state changed, or keep staying at the fast
             charge state.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_stm_periodic_checking_func
 NOTICE    : Battery is charged during this state, which is also the ONLY state
             that battery get charged, otherwise charging is forbidden.
*****************************************************************************/
static void chg_fastchg_state_period_func(void)
{
    chg_stop_reason stp_reas        = CHG_STOP_COMPLETE;
    uint32_t ret_code               = 0;

    /*1. IF charger_remove
            Switch to battery only state.
      */
    if(TRUE == is_chg_charger_removed())
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg removed force fastchg_st to batt_only_st!\n");
        chg_stm_switch_state(CHG_STM_BATTERY_ONLY);
    }
    /*2. If charging stop received from IC, get the stop reason:
         a. Due to charging complete, switch to maintenance state.
         b. Due to charge IC protection timer expired, get the batt-volt(avg.):
            if (vBat > batt_volt_full_threshold)
               switch to maintenance state.
            else
               toggle CE(charge enable) pin, reset protection timer.
         c. Due to SW control(CE pin),
               do nothing, print warning msg.
     */
    else if (FALSE == chg_is_IC_charging())
    {
        stp_reas = chg_get_stop_charging_reason();

        if (CHG_STOP_COMPLETE == stp_reas)
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Charge Completed, vBat = %dmV, vBat_sys = %dmV.\n",
                chg_get_cur_batt_volt(), chg_get_sys_batt_volt());
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)  
            #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
            chg_stm_switch_state(CHG_STM_MAINT_ST);
            #else
            if(TRUE == chg_is_batt_full())
            {
                chg_stm_switch_state(CHG_STM_MAINT_ST);
            }
            else
            {
                chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Charge Completed, but soc not 100, need adjust.\n");
            }
            #endif
#else
            chg_stm_switch_state(CHG_STM_MAINT_ST);
#endif
        }
        else if (CHG_STOP_TIMEOUT == stp_reas)
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Charge timeout from IC.\n");
            if (TRUE == chg_is_batt_full())
            {
                chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Battery is already full, vBat_sys = %dmV.\n",
                    chg_get_sys_batt_volt());
                chg_stm_switch_state(CHG_STM_MAINT_ST);
            }
            else
            {
                chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Toggle CEN, continue to charge.\n");

                /*Toggle CEN, reset charge IC protection timer.*/
                if (FALSE == chg_set_charge_enable(FALSE))
                {
                    /*If error occured, set 1st bit of ret_code.*/
                    ret_code |= (1 << 1);
                }
                chg_delay_ms(CHG_TOGGLE_CEN_INTVAL_IN_MS);
                if (FALSE == chg_set_charge_enable(TRUE))
                {
                    /*If error occured, set 2nd bit of ret_code.*/
                    ret_code |= (1 << 2);
                }

                if (ret_code)
                {
                    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Toggle CEN pin error 0x%x.\n", ret_code);
                }
            }
        }
        else if (CHG_STOP_INVALID_TEMP == stp_reas)
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Charge stopped due to " \
                       "IC invalid temperature detected.\n");
            chg_stm_switch_state(CHG_STM_INVALID_CHG_TEMP_ST);
        }
        else if (CHG_STOP_BY_SW == stp_reas)
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Charge stop due to SW control"   \
                       " in fast charge state.\n");
        }
        else
        {
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Invalid stop reason %d.\n", stp_reas);
        }
    }

    /*3. battery OVP, switch to maint state.*/
    else if (TRUE == chg_is_batt_ovp())
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Batt-OVP while fastchg, vBat = %dmV, vbat_sys = %dmV.\n",
            chg_get_cur_batt_volt(), chg_get_sys_batt_volt());
        chg_stm_switch_state(CHG_STM_MAINT_ST);
    }
    /*4. battery too cold/hot, switch to invalid charge temperature state.*/
    else if (FALSE == chg_is_batt_temp_valid())
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Invalid batt-temp while fastchg, tBat = %d'C, tBat_sys = %d'C.\n",
            chg_get_cur_batt_temp(), chg_get_sys_batt_temp());
        chg_stm_switch_state(CHG_STM_INVALID_CHG_TEMP_ST);
    }
#if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
    else if(TRUE == is_batttemp_in_warm_chg_area())
    {

         chg_print_level_message(CHG_MSG_INFO,"CHG_STM:Switch fastchg state to warmchg state, tBat=%d'C,tBat_sys=%dC.\n",
         chg_get_cur_batt_temp(), chg_get_sys_batt_temp());
         chg_stm_switch_state(CHG_STM_WARMCHG_ST);

    }
#endif /* MBB_CHG_WARM_CHARGE */

    else
    {
        /* �Ǳ�׼��������������׶ξ�һ�� */
        #if (MBB_CHG_HIGH_VOLT_BATT == FEATURE_ON)
        chg_high_volt_batt_period_func();
        #endif
#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
        if ((chg_get_sys_batt_volt() >= CHG_TERMI_VOLT_FOR_COUL) && \
                  (hisi_battery_current() <= CHG_TERMI_CURR_FOR_COUL))
        {
            chg_stm_switch_state(CHG_STM_MAINT_ST);
            chg_stm_state_info.charging_lasted_in_sconds = 0;
        }
#endif
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:System keep staying at fast charging state.\n");
    }
}

/*****************************************************************************
 �� �� ��  : chg_fastchg_state_exit_func
 ��������  : Charge Fast Charge State exit function.
             This function get called when system exit from Fast Charge State,
             do some clean/destroy stuff.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_switch_state
 NEXT      : Charge Maintenance State
             Charge Invalid Charge Temperature State
             Battery Only State.
 NOTICE    : TO BE CHECKED: WHETHER NECESSARY.
             MAY BE REMOVED IN FUTURE.
*****************************************************************************/
static void chg_fastchg_state_exit_func(void)
{
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System exit from fast-charge state.\n");
}


/*****************************************************************************
 �� �� ��  : chg_maint_state_entry_func
 ��������  : Charge Maintenance State entry function. Initialize all the
             statistic of current state: stop/disable battery charge via
             charge IC driver, notify UI that battery charging stopped.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_switch_state
 PREVIOUS  : Charge Transition State
             Charge Fast Charge State.
 NOTICE    : Set maximal power supply current limit as charger type, let the
             system get powered from external charger as much as possible.
             If charger type unknown, treat it as CHG_NONSTD_CHGR.
*****************************************************************************/
static void chg_maint_state_entry_func(void)
{
    chg_chgr_type_t cur_chgr_type = chg_stm_get_chgr_type();
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System enter into maintenance state.\n");

    /*1. Notify UI that battery charging stopped.*/
#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
    if (TRUE == chg_is_batt_full())
    {
        chg_notify_UI_charging_state(CHG_UI_STOP_CHARGING);
    }
#else
    chg_notify_UI_charging_state(CHG_UI_STOP_CHARGING);
#endif

    /*2. Update charge parameter, set maximal PS. current limit.*/
    if (CHG_WALL_CHGR == cur_chgr_type)
    {
        chg_set_hardware_parameter(&chg_std_chgr_hw_paras[CHG_STM_MAINT_ST]);
    }
    else if (CHG_500MA_WALL_CHGR == cur_chgr_type)
    {
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_MAINT_ST]);
    }
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    else if((CHG_USB_HOST_PC == cur_chgr_type) && CHG_CURRENT_SS == usb_speed_work_mode())
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:[chg_maint_state_entry_func]set usb 3.0 charge parameter\n\r");
        chg_set_hardware_parameter(&chg_usb3_chgr_hw_paras[CHG_STM_MAINT_ST]);
    }
    else if((CHG_USB_HOST_PC == cur_chgr_type) || (CHG_NONSTD_CHGR == cur_chgr_type)
            || (CHG_CHGR_UNKNOWN == cur_chgr_type))
    {
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_MAINT_ST]);
    }

    else if(CHG_WIRELESS_CHGR == cur_chgr_type)
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_maint_state_entry_func disable wireless chg!\n");
        chg_set_hardware_parameter(&chg_wireless_chgr_hw_paras[CHG_STM_MAINT_ST]);
    }
    else
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_maint_state_entry_func Is not wireless !\n");
    }
#else
    else if((CHG_USB_HOST_PC == cur_chgr_type) && CHG_CURRENT_SS == usb_speed_work_mode())
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:[chg_maint_state_entry_func]set usb 3.0 charge parameter\n\r");
        chg_set_hardware_parameter(&chg_usb3_chgr_hw_paras[CHG_STM_MAINT_ST]);
    }
    else
    {
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_MAINT_ST]);
    }
#endif/*MBB_CHG_WIRELESS*/
}

/*****************************************************************************
 �� �� ��  : chg_maint_state_period_func
 ��������  : Charge Maintenance State periodic polling function, which get called
             when polling timer event triggered.
             This function checks all the system condition, then choose the right
             state to swith.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_main_poll_cb(?)
 NOTICE    : Battery is charged to full at Maintenance State. System would draw
             power from external charger preferentially, if battery is consumed
             low to recharge threshold, then re-charge raised.
*****************************************************************************/
static void chg_maint_state_period_func(void)
{
    /*1. IF charger_remove
            Switch to battery only state.
      */

    if(TRUE == is_chg_charger_removed())
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg removed force maint_st to batt_only_st!\n");
        chg_stm_switch_state(CHG_STM_BATTERY_ONLY);
    }
    /*2. Get the system battery volt:
         a. If re-charge condition meets?
            Notice: Re-charge is forbidden at pwroff charge, regardless of:
                    a). Battery is already full when system power-up.
                    b). Battery is charged to full.
                    c). Fast charge timeout at pwroff charge.
        ->Y 1) Get system battery temperature,
               a). Battery temperature valid, switch to fast charge state,
                   recharge started.
               b). Battery temperature invalid, switch to invlaid charge
                   temperature.
        ->N 2) Keep staying at maintenance state.
     */
    /*����糬ʱ��־λΪtrue��ֱ���˳������ж��Ƿ���Ҫ����*/
    else if (TRUE == chg_time_expired_flag)
    {
        return;
    }
    else if (TRUE == chg_is_batt_need_rechg())
    {
        if (FALSE == chg_is_batt_temp_valid())
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Battery temperature %d invlaid for charge.\n",  \
                       chg_get_sys_batt_temp());
            chg_stm_switch_state(CHG_STM_INVALID_CHG_TEMP_ST);
        }
        else
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:batt_need_rechg force to TRANSIT_ST.\n");
            chg_stm_switch_state(CHG_STM_TRANSIT_ST);
        }
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:Keep staying at maint_state.\n");
    }
}

/*****************************************************************************
 �� �� ��  : chg_maint_state_exit_func
 ��������  : Charge Maintenance State exit function.
             This function get called when system exit from Maintenance State,
             to do some clean/destroy stuff.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_switch_state
 NEXT      : Charge Fast Charge State(Recharge).
             Battery Only State.
 NOTICE    : TO BE CHECKED: WHETHER NECESSARY.
             MAY BE REMOVED IN FUTURE.
*****************************************************************************/
static void chg_maint_state_exit_func(void)
{
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System exit from maintenance state.\n");
}

/*****************************************************************************
 �� �� ��  : chg_invalid_chg_temp_state_entry_func
 ��������  : Invalid Charge Temperature State entry function. Initialize all the
             statistic of current state: stop/disable battery charge via
             charge IC driver, notify UI that battery charging stopped.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_switch_state
 PREVIOUS  : Charge Transition State
             Charge Fast Charge State.
 NOTICE    : Set maximal power supply current limit as charger type, let the
             system get powered from external charger as much as possible.
             If charger type unknown, treat it as CHG_NONSTD_CHGR.
*****************************************************************************/
static void chg_invalid_chg_temp_state_entry_func(void)
{
    chg_chgr_type_t cur_chgr_type = chg_stm_get_chgr_type();
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System enter into invalid chg temp state.\n");

    /*1. Notify UI that battery charging stopped.*/
    chg_notify_UI_charging_state(CHG_UI_STOP_CHARGING);

    /*2. Update charge parameter, set maximal PS. current limit.*/
    /*3. Stop charging.*/
    if (CHG_WALL_CHGR == cur_chgr_type)
    {
#ifdef BSP_CONFIG_BOARD_E5_DCM
        if(CHG_OVER_TEMP_STOP_THRESHOLD <= chg_real_info.battery_temp)
        {
            chg_set_hardware_parameter(&chg_std_chgr_over_temp_hw_paras);
        }
        else 
        {
            chg_set_hardware_parameter(&chg_std_chgr_hw_paras[CHG_STM_INVALID_CHG_TEMP_ST]);
        }
#else
        chg_set_hardware_parameter(&chg_std_chgr_hw_paras[CHG_STM_INVALID_CHG_TEMP_ST]);
#endif
    }
    else if (CHG_500MA_WALL_CHGR == cur_chgr_type)
    {
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_INVALID_CHG_TEMP_ST]);
    }
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    else if((CHG_USB_HOST_PC == cur_chgr_type) && CHG_CURRENT_SS == usb_speed_work_mode())
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:chg_invalid_chg_temp_state_entry_funcset usb 3.0 parameter\n\r");
        chg_set_hardware_parameter(&chg_usb3_chgr_hw_paras[CHG_STM_INVALID_CHG_TEMP_ST]);
    }
    else if((CHG_USB_HOST_PC == cur_chgr_type) || (CHG_NONSTD_CHGR == cur_chgr_type)
            || (CHG_CHGR_UNKNOWN == cur_chgr_type))
    {
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_INVALID_CHG_TEMP_ST]);
    }
    else if(CHG_WIRELESS_CHGR == cur_chgr_type)
    {
        /*�¶��쳣״̬ʹ�����߳��оƬ�������ó��оƬ������ʹ�ܳ��*/
        //chg_set_wireless_chg_enable(FALSE);
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_invalid_chg_temp_state_entry_func disable wireless chg!\n");
        chg_set_hardware_parameter(&chg_wireless_chgr_hw_paras[CHG_STM_INVALID_CHG_TEMP_ST]);
    }
    else
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_invalid_chg_temp_state_entry_func Is not wireless !\n");
    }
#else
    else if((CHG_USB_HOST_PC == cur_chgr_type) && CHG_CURRENT_SS == usb_speed_work_mode())
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:[chg_invalid_chg_temp_state_entry_func]set usb 3.0 charge parameter\n\r");
        chg_set_hardware_parameter(&chg_usb3_chgr_hw_paras[CHG_STM_INVALID_CHG_TEMP_ST]);
    }
    else
    {
#ifdef BSP_CONFIG_BOARD_E5_DCM
        if(CHG_OVER_TEMP_STOP_THRESHOLD <= chg_real_info.battery_temp)
        {
            chg_set_hardware_parameter(&chg_usb_chgr_over_temp_hw_paras);
        }
        else 
        {
            chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_INVALID_CHG_TEMP_ST]);
        }
#else
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_INVALID_CHG_TEMP_ST]);
#endif
    }
#endif/*MBB_CHG_WIRELESS*/
}

/*****************************************************************************
 �� �� ��  : chg_invalid_chg_temp_state_period_func
 ��������  : Invalid Charge Temperature State periodic polling function, which get called
             when polling timer event triggered.
             This function checks all the system condition, then choose the right
             state to swith.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_stm_periodic_checking_func
 NOTICE    : As its name suggests, during this state, charging is forbidden since
             battery is too hot/cold to charge.
*****************************************************************************/
static void chg_invalid_chg_temp_state_period_func(void)
{

    /*1. IF charger_remove
            Switch to battery only state.
      */
    if(TRUE == is_chg_charger_removed())
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg removed force invalid_chg_st to batt_only_st!\n");
        chg_stm_switch_state(CHG_STM_BATTERY_ONLY);
    }
    /*2. If the battery temperature resumed?
     ->Y a. If battery OVP detected, switch to maintenance state.
            else switch to fast charge state.
     ->N b. Keep staying at invalid charge temperature state.
     */
    else if (TRUE == chg_is_batt_temp_valid())
    {
        if (chg_is_batt_ovp())
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Battery OVP, batt-volt %dmV while temp resume.\n", \
                       chg_get_sys_batt_volt());
            chg_stm_switch_state(CHG_STM_MAINT_ST);
        }
        else
        {
            chg_stm_switch_state(CHG_STM_TRANSIT_ST);
        }
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:Battery temp not resumed, staying at invalid temp.\n");
    }

}

/*****************************************************************************
 �� �� ��  : chg_invalid_chg_temp_state_exit_func
 ��������  : Invalid Charge Temperature State exit function.
             This function get called when system exit from Invalid Charge Temperature State,
             do some clean/destroy stuff.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_switch_state
 NEXT      : Fast Charge State
             Invalid Charge Temperature State
             Battery Only State
 NOTICE    : TO BE CHECKED: WHETHER NECESSARY.
             MAY BE REMOVED IN FUTURE.
*****************************************************************************/
static void chg_invalid_chg_temp_state_exit_func(void)
{
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System exit from invalid chg temp state.\n");
}

/*****************************************************************************
 �� �� ��  : chg_batt_only_state_entry_func
 ��������  : Call when system is going to switch to Battery Only state.
             This phase we should: 1. Switch to fast polling(chgr absent) timer.
             2. Notify UI to stop battery charging display.
             3. Config the charge IC, disable charge, set minimal power supply
                front-end current limit, put IC to LPM(may auto).
             4. Set current chgr type to INVALID.
 �������  : None
 �� �� ֵ  : VOID
 WHO-CALL  : chg_stm_switch_state.
 CALL-WHOM : chg_set_poll_timer_state.
 PREVIOUS  : All other states except Battery Only itself.
 NOTICE    : Leave charge IC config as minimal PS. current limit.
*****************************************************************************/
static void chg_batt_only_state_entry_func(void)
{
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System enter into batt-only state.\n");
    /*clear the temp flag*/
    chg_temp_is_too_hot_or_too_cold_for_chg();
    /*1. Notify UI to stop battery charging display.*/
    chg_notify_UI_charging_state(CHG_UI_STOP_CHARGING);

    chg_set_cur_chg_mode(CHG_BAT_ONLY_MODE);
    /*2. Set current charger type to invalid, means charger absent.*/
    chg_stm_set_chgr_type(CHG_CHGR_INVALID);

    /*����Ѿ����л��������״̬�ˣ���⵽USB���߱�׼�����������ONLINE���ͽ�����ΪOFFLINE*/
    if(TRUE == chg_get_usb_online_status())
    {
        chg_set_usb_online_status(FALSE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_USB, (uint32_t)CHG_EVENT_NONEED_CARE);
    }
    else if(TRUE == chg_get_ac_online_status())
    {
        chg_set_ac_online_status(FALSE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_CHARGER, (uint32_t)CHG_EVENT_NONEED_CARE);
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:System enter batt-only state AC/USB already OFLINE!.\n");
    }

    /*3. Config charge hw parameter, disable charge, PS current limit min.*/
    //chg_set_hardware_parameter(&chg_batt_only_hw_paras);
    chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_BATTERY_ONLY]);
    /*4. Set poll timer state to fast mode(charger absent).*/
}

/*****************************************************************************
 �� �� ��  : chg_batt_only_state_period_func
 ��������  : Battery Only State periodic polling function, which get called
             when polling timer event triggered.
             Since charger attach event would handled via charge main task,
             this function just do nothing.
 �������  : None
 �� �� ֵ  : VOID
 WHO-CALL  : chg_stm_periodic_checking_func.
 CALL-WHOM :
 NOTICE    : Battery only state will stay util charge main task switch it to
             new state once external charger insertion detected.
             MAY-TO-BE-REMOVED or SET TO NULL.
*****************************************************************************/
static void chg_batt_only_state_period_func(void)
{
    static uint32_t chg_poll_timer_switch_cnter = 0;
    int32_t         curr_polling_timer_mode     = chg_poll_timer_get();
    boolean         is_emergency_state          = chg_is_emergency_state();
    boolean is_chgr_present      = chg_is_charger_present();



    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:batt_only_state_period is_chgr_present=%d.\n",
                            is_chgr_present);

    /*Get poll timer period error, do nothing, return.*/
    if (CHG_ERROR == curr_polling_timer_mode)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Get poll timer period error.\n");
        return;
    }

    /*1. If we stay at batt_only state more than CHG_SWITCH_TO_SLOW_POLL_INTERVAL_IN_SEC
         seconds, switch poll timer to slow mode.
         Notice: DON'T switch to slow timer mode if system in emergency state. e.g.,
                 low power, battery hot/cold, etc, supported by sampling sub-module.*/
    if (FAST_POLL_CYCLE == curr_polling_timer_mode && !is_emergency_state)
    {
        if (chg_poll_timer_switch_cnter >= CHG_SWITCH_TO_SLOW_POLL_INTERVAL_IN_SEC)
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System stay at batt-only state" \
                " more than %d seconds, switch to slow timer mode.\n",
                CHG_SWITCH_TO_SLOW_POLL_INTERVAL_IN_SEC);
            /*Clear cnter for next count.*/
            chg_poll_timer_switch_cnter = 0;
            chg_poll_timer_set(SLOW_POLL_CYCLE);
        }
        else
        {
            chg_poll_timer_switch_cnter += ((uint32_t)curr_polling_timer_mode / MS_IN_SECOND);
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:Poll switch cnter = %d.\n", chg_poll_timer_switch_cnter);
        }
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:%s polling mode, system %s at emergency State.\n",
            (curr_polling_timer_mode == FAST_POLL_CYCLE) ? "Fast" : "Slow",
            (is_emergency_state) ? "is" : "isn't");

        /*Clear cnter for next count.*/
        chg_poll_timer_switch_cnter = 0;
    }


#if (MBB_CHG_WIRELESS == FEATURE_ON)
    if(ONLINE == g_wireless_online_flag)
    {
        chg_stm_set_wireless_online_st(TRUE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_WIRELESS, (uint32_t)CHG_EVENT_NONEED_CARE);
        chg_stm_set_chgr_type(CHG_WIRELESS_CHGR);
        chg_set_cur_chg_mode(CHG_WIRELESS_MODE);
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:wireless online change to CHG_WIRELESS_MODE!\n");
        chg_stm_switch_state(CHG_STM_TRANSIT_ST);
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:System staying at batt-only state.\n");
    }
#endif/*MBB_CHG_WIRELESS*/
}

/*****************************************************************************
 �� �� ��  : chg_batt_only_state_exit_func
 ��������  : Charge Battery Only State exit function.
             This function get called when system exit from Battery Only State,
             to do some clean/destroy stuff.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : VOID
 CALL-WHOM :
 WHO-CALLED: chg_switch_state
 NEXT      : Charge Transition State.
 NOTICE    : TO BE CHECKED: WHETHER NECESSARY.
             MAY BE REMOVED IN FUTURE.
*****************************************************************************/
static void chg_batt_only_state_exit_func(void)
{
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System exit from batt-only state.\n");
}

#if (MBB_CHG_WARM_CHARGE == FEATURE_ON)

void chg_stm_set_pre_state(chg_stm_state_type pre_state)
{
    chg_stm_state_info.pre_stm_state = pre_state;
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:set_pre_stm_state=%d\n",pre_state);
}


chg_stm_state_type chg_stm_get_pre_state(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:get_pre_stm_state=%d\n",\
                        chg_stm_state_info.pre_stm_state);
    return chg_stm_state_info.pre_stm_state;
}


boolean is_batttemp_in_warm_chg_area( void )
{
    boolean rtnValue = FALSE;
    static boolean last_rtnValue = FALSE;

    /*���ǰһ��״̬�ǵ�ص�����λ״̬��˵�������˲�����Դ�¼���
       ������״̬��¼�����ָ���Ĭ��ֵ������*/
    if (CHG_STM_BATTERY_ONLY == chg_stm_get_pre_state())
    {
        last_rtnValue = FALSE;
    }
#if defined(BSP_CONFIG_BOARD_E5573CS) || defined(BSP_CONFIG_BOARD_E5573BS) \
    || defined(BSP_CONFIG_BOARD_E5573CS_933) || defined(BSP_CONFIG_BOARD_607HW)\
    || defined(BSP_CONFIG_BOARD_E5577BS_937) || defined(BSP_CONFIG_BOARD_R218h)
        if (CHG_BATT_ID_DEF == chg_get_batt_id())
        {
            return rtnValue;
        }
#endif

    if ( FALSE == last_rtnValue )
    {
        /*����¶ȴ��ڵ���45��С��55��Ϊ���³����*/
        if ( ( CHG_WARM_CHARGE_ENTER_THRESHOLD <= chg_real_info.battery_temp ) \
             && ( CHG_OVER_TEMP_STOP_THRESHOLD > chg_real_info.battery_temp ) )
        {
            rtnValue = TRUE;
        }
        else
        {
            rtnValue = FALSE;
        }
    }
    else
    {
        /*С��42�Ȼ��ߴ���55�ȵ��岻�ڸ��³������ */
        if ( (CHG_WARM_CHARGE_EXIT_THRESHOLD > chg_real_info.battery_temp)\
             || (CHG_OVER_TEMP_STOP_THRESHOLD <= chg_real_info.battery_temp))
        {
            rtnValue = FALSE;
        }
        else
        {
            rtnValue = TRUE;
        }
    }

    last_rtnValue = rtnValue;
    return rtnValue;
}


static void chg_warmchg_state_entry_func(void)
{
    chg_chgr_type_t cur_chgr_type = chg_stm_get_chgr_type();

    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System enter into warm-charge state.\n");

    /*1.If the pre chg state is not CHG_STM_FAST_CHARGE_ST Notify UI
       that battery charging started.*/
    if ( CHG_STM_FAST_CHARGE_ST != chg_stm_get_pre_state())
    {
        chg_notify_UI_charging_state(CHG_UI_START_CHARGING);
    }

    /*2. Set charging hardware parameter per charger type.*/
    if (CHG_WALL_CHGR == cur_chgr_type)
    {
        /*ʹ�ܳ�磬���ñ�־*/
        chg_en_flag = 1;
        chg_en_timestamp = jiffies;

        chg_set_hardware_parameter(&chg_std_chgr_hw_paras[CHG_STM_WARMCHG_ST]);
    }
    else if (CHG_500MA_WALL_CHGR == cur_chgr_type)
    {
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_WARMCHG_ST]);
    }
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    else if((CHG_USB_HOST_PC == cur_chgr_type) && CHG_CURRENT_SS == usb_speed_work_mode())
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:[chg_warmchg_state_entry_func]:set usb 3.0 charge parameter\n\r");
        chg_set_hardware_parameter(&chg_usb3_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST]);
    }
    else if((CHG_USB_HOST_PC == cur_chgr_type) || (CHG_NONSTD_CHGR == cur_chgr_type)
            || (CHG_CHGR_UNKNOWN == cur_chgr_type))
    {
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_WARMCHG_ST]);
    }

    else if(CHG_WIRELESS_CHGR == cur_chgr_type)
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_warmchg_state_entry_func enable wireless chg!\n");
        /*�������߳�����������ĸ��³�����*/
        if(FALSE == chg_is_powdown_charging())
        {
            chg_set_hardware_parameter(&chg_wireless_chgr_hw_paras[CHG_STM_WARMCHG_ST]);
        }
        /*�ػ����߳�����ùػ��ĸ��³�������ǰ������900MA,�������1024MA,��ѹ��ѹ4.1V
            ��ֹ����256MA*/
        else
        {
            chg_set_hardware_parameter(&chg_wireless_poweroff_warmchg_paras);
        }
    }
    else
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_warmchg_state_entry_func Is not wireless !\n");
    }
#else
    else if((CHG_USB_HOST_PC == cur_chgr_type) && CHG_CURRENT_SS == usb_speed_work_mode())
    {
        chg_print_level_message(CHG_MSG_DEBUG,"CHG_STM:[chg_warmchg_state_entry_func]set usb 3.0 charge parameter\n\r");
        chg_set_hardware_parameter(&chg_usb3_chgr_hw_paras[CHG_STM_FAST_CHARGE_ST]);
    }
    else
    {
        chg_set_hardware_parameter(&chg_usb_chgr_hw_paras[CHG_STM_WARMCHG_ST]);
    }

#endif/*MBB_CHG_WIRELESS*/

    /*3. Enable IC Charge function.*/
    /*Already done in chg_set_hardware_parameter.*/

}


static void chg_warmchg_state_period_func(void)
{
    chg_stop_reason stp_reas        = CHG_STOP_COMPLETE;
    uint32_t ret_code               = 0;
    /*1. IF charger_remove
            Switch to battery only state.
      */
    if(TRUE == is_chg_charger_removed())
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg removed force warmchg_st to batt_only_st!\n");
        chg_stm_switch_state(CHG_STM_BATTERY_ONLY);
    }

    /*2. If charging stop received from IC, get the stop reason:
         a. Due to charging complete, switch to maintenance state.
         b. Due to charge IC protection timer expired, get the batt-volt(avg.):
            if (vBat > batt_volt_full_threshold)
               switch to maintenance state.
            else
               toggle CE(charge enable) pin, reset protection timer.
         c. Due to SW control(CE pin),
               do nothing, print warning msg.
     */
    else if (FALSE == chg_is_IC_charging())
    {
        stp_reas = chg_get_stop_charging_reason();

        if (CHG_STOP_COMPLETE == stp_reas)
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:Charge Completed, vBat = %dmV, vBat_sys = %dmV.\n",
            chg_get_cur_batt_volt(), chg_get_sys_batt_volt());
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)  
            #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
            chg_stm_switch_state(CHG_STM_MAINT_ST);
            #else
            if (TRUE == chg_is_batt_full())
            {
                chg_stm_switch_state(CHG_STM_MAINT_ST);
            }
            #endif
#else
            chg_stm_switch_state(CHG_STM_MAINT_ST);
#endif
        }
        else if (CHG_STOP_TIMEOUT == stp_reas)
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Charge timeout from IC.\n");
            if (TRUE == chg_is_batt_full())
            {
                chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Battery is already full, vBat_sys = %dmV.\n",
                    chg_get_sys_batt_volt());
                chg_stm_switch_state(CHG_STM_MAINT_ST);
            }
            else
            {
                chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Toggle CEN, continue to charge.\n");

                /*Toggle CEN, reset charge IC protection timer.*/
                if (FALSE == chg_set_charge_enable(FALSE))
                {
                    /*If error occured, set 1st bit of ret_code.*/
                    ret_code |= (1 << 1);
                }
                chg_delay_ms(CHG_TOGGLE_CEN_INTVAL_IN_MS);
                if (FALSE == chg_set_charge_enable(TRUE))
                {
                    /*If error occured, set 2nd bit of ret_code.*/
                    ret_code |= (1 << 2);
                }

                if (ret_code)
                {
                    chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Toggle CEN pin error 0x%x.\n", ret_code);
                }
            }
        }
        else if (CHG_STOP_INVALID_TEMP == stp_reas)
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Charge stopped due to " \
                       "IC invalid temperature detected.\n");
            chg_stm_switch_state(CHG_STM_INVALID_CHG_TEMP_ST);
        }
        else if (CHG_STOP_BY_SW == stp_reas)
        {
            chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Charge stop due to SW control"   \
                       " in fast charge state.\n");
        }
        else
        {
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Invalid stop reason %d.\n", stp_reas);
        }
    }
    /*3. battery OVP, switch to maint state.*/
    else if (TRUE == chg_is_batt_ovp())
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Batt-OVP while warmchg, vBat = %dmV, vbat_sys = %dmV.\n",
            chg_get_cur_batt_volt(), chg_get_sys_batt_volt());
        chg_stm_switch_state(CHG_STM_MAINT_ST);
    }

    /*4. battery too cold/hot, switch to invalid charge temperature state.*/
    else if (FALSE == chg_is_batt_temp_valid())
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Invalid batt-temp while warmchg, tBat = %d'C, tBat_sys = %d'C.\n",
            chg_get_cur_batt_temp(), chg_get_sys_batt_temp());
        chg_stm_switch_state(CHG_STM_INVALID_CHG_TEMP_ST);
    }
    /*5.battery temp resume switch to fastchg state*/
    else if(FALSE == is_batttemp_in_warm_chg_area())
    {

         chg_print_level_message(CHG_MSG_INFO, "CHG_STM:batt-temp resume form warmchg to fastchg, tBat = %d'C, tBat_sys = %d'C.\n",
         chg_get_cur_batt_temp(), chg_get_sys_batt_temp());
         chg_stm_switch_state(CHG_STM_FAST_CHARGE_ST);
    }
    else
    {
        #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
        if ((chg_get_sys_batt_volt() >= CHG_TERMI_WARMCHG_VOLT_FOR_COUL) && \
                  (hisi_battery_current() <= CHG_TERMI_CURR_FOR_COUL))
        {
            chg_stm_switch_state(CHG_STM_MAINT_ST);
            chg_stm_state_info.charging_lasted_in_sconds = 0;
        }
        #endif
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System keep staying at warmchg state.\n");
    }

}


static void chg_warmchg_state_exit_func(void)
{
     chg_print_level_message(CHG_MSG_INFO, "CHG_STM:System exit from warmchg state.\n");

}
 #endif /* MBB_CHG_WARM_CHARGE */



#if (MBB_CHG_EXTCHG == FEATURE_ON)

void extchg_stop_threshold_to_voltage(int32_t capacity)
{
    switch (capacity)
    {
        case EXTCHG_DEFAULT_STOP_THRESHOLD:
            g_extchg_voltage_threshold = EXTCHG_DEFAULT_STOP_VOLTAGE;
            break;
        case EXTCHG_STOP_CAPACITY_TEN:
            g_extchg_voltage_threshold = EXTCHG_STOP_VOLTAGE_TEN;
            break;
        case EXTCHG_STOP_CAPACITY_TWENTY:
            g_extchg_voltage_threshold = EXTCHG_STOP_VOLTAGE_TWENTY;
            break;
        case EXTCHG_STOP_CAPACITY_THIRTY:
            g_extchg_voltage_threshold = EXTCHG_STOP_VOLTAGE_THIRTY;
            break;
        case EXTCHG_STOP_CAPACITY_FORTY:
            g_extchg_voltage_threshold = EXTCHG_STOP_VOLTAGE_FORTY;
            break;
        case EXTCHG_STOP_CAPACITY_FIFTY:
            g_extchg_voltage_threshold = EXTCHG_STOP_VOLTAGE_FIFTY;
            break;
        case EXTCHG_STOP_CAPACITY_SIXTY:
            g_extchg_voltage_threshold = EXTCHG_STOP_VOLTAGE_SIXTY;
            break;
        case EXTCHG_STOP_CAPACITY_SEVENTY:
            g_extchg_voltage_threshold = EXTCHG_STOP_VOLTAGE_SEVENTY;
            break;
        case EXTCHG_STOP_CAPACITY_EIGHTY:
            g_extchg_voltage_threshold = EXTCHG_STOP_VOLTAGE_EIGHTY;
            break;
        case EXTCHG_STOP_CAPACITY_NINETY:
            g_extchg_voltage_threshold = EXTCHG_STOP_VOLTAGE_NINETY;
            break;
        case EXTCHG_STOP_CAPACITY_HUNDRED:
            g_extchg_voltage_threshold = EXTCHG_STOP_VOLTAGE_HUNDRED;
            break;
        default:
            break;
    }
}


void chg_extchg_config_data_init(void)
{
    int32_t fd    = 0;
    mm_segment_t fs;
    char extchg_threshold_temp = 0;
    char extchg_diable_st_temp = 0;
    int32_t extchg_capacity_threshold = 0;

    fs = get_fs();
    set_fs(KERNEL_DS);
    fd = sys_open(EXTCHG_THRESHOLD_PATH, O_RDWR, 0);
    if(fd >= 0)
    {
        sys_read(fd, &extchg_threshold_temp, 1);
        extchg_capacity_threshold = extchg_threshold_temp;
        chg_print_level_message(CHG_MSG_INFO,"extchg_capacity_threshold=%d.\n", extchg_capacity_threshold);
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
        g_extchg_stop_soc_threshold = extchg_capacity_threshold;
#else
        extchg_stop_threshold_to_voltage(extchg_capacity_threshold);
#endif
        sys_close(fd);
    }
    else
    {
        #if defined(BSP_CONFIG_BOARD_E5577S_932) || defined(BSP_CONFIG_BOARD_E5577S_321) \
       || defined(BSP_CONFIG_BOARD_E5577S_324)|| defined(BSP_CONFIG_BOARD_E5577BS_937)
        extchg_capacity_threshold = EXTCHG_STOP_CAPACITY_TEN;
        #else
        extchg_capacity_threshold = EXTCHG_DEFAULT_STOP_THRESHOLD;
        #endif
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
        g_extchg_stop_soc_threshold = extchg_capacity_threshold;
#else
        extchg_stop_threshold_to_voltage(extchg_capacity_threshold);
#endif
        chg_print_level_message(CHG_MSG_INFO,"UI set extchg_threshold read FAIL use default value 5!\n");
    }


    fd = sys_open(EXTCHG_DISABLE_PATH, O_RDWR, 0);
    if(fd >= 0)
    {
        sys_read(fd, &extchg_diable_st_temp, 1);
        g_extchg_diable_st = extchg_diable_st_temp;
        chg_print_level_message(CHG_MSG_INFO,"g_extchg_diable_st=%d.\n", g_extchg_diable_st);
        sys_close(fd);
    }
    else
    {
        g_extchg_diable_st = 0;
        chg_print_level_message(CHG_MSG_INFO,"UI set extchg_diable_st read FAIL use default value 0!\n");
    }
    set_fs(fs);
}




boolean chg_get_extchg_online_status(void)
{
#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
    return OFFLINE;
#else
    int32_t vbus_volt = 0;

    //TO DO:1:����USB�����ӿڶ̽�D+ ,D-
    usb_notify_event(USB_OTG_CONNECT_DP_DM,NULL);

    /*ʹ�����߳��*/
    chg_set_extchg_chg_enable(TRUE);

    /* ���� E5577s-932 ��ʹ�� vbus �ɼ��������ѹ */
#if defined(BSP_CONFIG_BOARD_E5577S_932)
    return ONLINE;
#endif

    /*��ʱ500MS,��ֹʹ�ܳ�����Ϊ��·�ӳٵ��²ɼ���ص�ѹ�쳣*/
    chg_print_level_message(CHG_MSG_DEBUG,"CHG_PLT:chg_delay_ms 500MS! \n");
    chg_delay_ms(EXTCHG_DELAY_COUNTER_SIZE);
    vbus_volt = chg_get_volt_from_adc(CHG_PARAMETER__VBUS_VOLT);
    chg_print_level_message( CHG_MSG_INFO,"CHG_DRV:get_extchg_online vbus_volt = %d\r\n ",vbus_volt);
    if(vbus_volt > VBUS_JUDGEMENT_THRESHOLD)
    {
        return ONLINE;
    }
    else
    {
        chg_print_level_message( CHG_MSG_ERR,"CHG_PLT: VBUS detect failure extchg is not online\r\n ");
        return OFFLINE;
    }
#endif
}

#endif /* MBB_CHG_EXTCHG */

/**********************************************************************
FUNCTION:    chg_get_batt_id_volt
DESCRIPTION: get batt id volt
INPUT:       None
OUTPUT:      None.
RETURN:      batt id volt
NOTE:        None
***********************************************************************/
int32_t chg_get_batt_id_volt(void)
{
    if(0xFFFF == chg_real_info.battery_id_volt)
    {
        chg_real_info.battery_id_volt = chg_get_volt_from_adc(CHG_PARAMETER__BATTERY_ID_VOLT);
    }
    return chg_real_info.battery_id_volt;
}


int32_t chg_get_bat_status(void)
{
    int32_t bat_stat_t = POWER_SUPPLY_STATUS_UNKNOWN;
    chg_stm_state_type stm_status = CHG_STM_MAX_ST;

    stm_status = chg_stm_get_cur_state();
    if((CHG_STM_INIT_ST == stm_status) || (CHG_STM_TRANSIT_ST == stm_status)
        || (CHG_STM_INVALID_CHG_TEMP_ST == stm_status)
        || (CHG_STM_BATTERY_ONLY == stm_status))
    {
        bat_stat_t = POWER_SUPPLY_STATUS_NOT_CHARGING;
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_status=NOT_CHARGING\n");
    }
    else if ((CHG_STM_FAST_CHARGE_ST == stm_status) || (CHG_STM_WARMCHG_ST == stm_status))
    {
        bat_stat_t = POWER_SUPPLY_STATUS_CHARGING;
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_status=CHARGING\n");
    }
    else if(CHG_STM_MAINT_ST == stm_status)
    {
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
        #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
        bat_stat_t = POWER_SUPPLY_STATUS_FULL;
        #else
        if(BATT_CAPACITY_FULL == chg_get_sys_batt_capacity())
        {
            bat_stat_t = POWER_SUPPLY_STATUS_FULL;
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_status=STATUS_FULL\n");
        }
        #endif
#else
        bat_stat_t = POWER_SUPPLY_STATUS_FULL;
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_status=STATUS_FULL\n");
#endif
    }
    else
    {
#if (MBB_CHG_COMPENSATE == FEATURE_ON)
        if(POWER_SUPPLY_STATUS_NEED_SUPPLY == chg_stm_state_info.bat_stat_type)
        {
            bat_stat_t = POWER_SUPPLY_STATUS_NEED_SUPPLY;
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_status=NEED_SUPPLY\n");
        }
        else if(POWER_SUPPLY_STATUS_SUPPLY_SUCCESS == chg_stm_state_info.bat_stat_type)
        {
            bat_stat_t = POWER_SUPPLY_STATUS_SUPPLY_SUCCESS;
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_status=SUPPLY_SUCCESS\n");
        }
        else
        {
            bat_stat_t = POWER_SUPPLY_STATUS_UNKNOWN;
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_status=STATUS_UNKNOWN\n");
        }
#else
        bat_stat_t = POWER_SUPPLY_STATUS_UNKNOWN;
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_status=STATUS_UNKNOWN\n");
#endif
    }
    return bat_stat_t;
}


int32_t chg_get_bat_health(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_health=%d\n",chg_stm_state_info.bat_heath_type);
    return chg_stm_state_info.bat_heath_type;
}


int32_t chg_get_extchg_status(void)
{
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:extchg_status=%d\n",chg_stm_state_info.extchg_status);
    return chg_stm_state_info.extchg_status;
}
/*****************************************************************************
 �� �� ��  : chg_stm_init
 ��������  : Charge State Machine Sub-Module initialize procedure.
 �������  : VOID
 �������  : VOID
 �� �� ֵ  : CHG_STM_SUCCESS for initialize successful
             CHG_STM_FAILED  for initialize failed
 CALL-WHOM :
 WHO-CALLED: chg_switch_state
             chg_init(?)
 NOTICE    : Export Required.
*****************************************************************************/
int32_t chg_stm_init(void)
{
    static boolean chg_stm_inited = FALSE;
    chg_stm_state_type cur_chg_state = chg_stm_get_cur_state();
    chg_chgr_type_t cur_chg_type = chg_stm_get_chgr_type();
    CHG_MODE_ENUM cur_chg_mode = chg_get_cur_chg_mode();
    chg_stm_state_type pre_chg_state = chg_stm_get_pre_state();
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    boolean is_wireless_online   = chg_stm_get_wireless_online_st();
#endif/*MBB_CHG_WIRELESS*/
#if (MBB_CHG_EXTCHG == FEATURE_ON)
    boolean is_extchg_online   = chg_stm_get_extchg_online_st();
#endif/*MBB_CHG_EXTCHG*/

    if (FALSE == chg_stm_inited)
    {
        /*Clear fast charge sw protection timer(cnter).*/

        chg_stm_state_info.charging_lasted_in_sconds = 0;
#if (FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT)
        chg_stm_state_info.charger_lasted_without_charging_in_seconds = 0;
#endif
        /*Initialize default chgr type and stm state. */
        if((cur_chg_mode <= CHG_MODE_INIT) || (cur_chg_mode >= CHG_MODE_UNKNOW))
        {
            chg_set_cur_chg_mode(CHG_MODE_UNKNOW);
        }
        if((cur_chg_type <= CHG_CHGR_UNKNOWN) || (cur_chg_type >= CHG_CHGR_INVALID))
        {
            chg_stm_set_chgr_type(CHG_CHGR_UNKNOWN);
        }
        if((cur_chg_state <= CHG_STM_INIT_ST) || (cur_chg_state >= CHG_STM_MAX_ST))
        {
            chg_stm_set_cur_state(CHG_STM_TRANSIT_ST);
        }

#if (MBB_CHG_WARM_CHARGE == FEATURE_ON)
        if((pre_chg_state <= CHG_STM_INIT_ST) || (pre_chg_state >= CHG_STM_MAX_ST))
        {
            chg_stm_set_pre_state(CHG_STM_TRANSIT_ST);
        }
#endif /* MBB_CHG_WARM_CHARGE */

#if (MBB_CHG_EXTCHG == FEATURE_ON)
        if(FALSE == is_5577cs_falg)
        {
            if(TRUE != is_extchg_online)
            {
                chg_stm_set_extchg_online_st(FALSE);
            }
        }
        else
        {
            chg_stm_set_extchg_online_st(FALSE);
        }
#endif /* MBB_CHG_EXTCHG */

#if (MBB_CHG_WIRELESS == FEATURE_ON)
        if(TRUE != is_wireless_online)
        {
            chg_stm_set_wireless_online_st(FALSE);
        }
#endif /* MBB_CHG_WIRELESS */

        if(CHG_STM_INIT_ST == cur_chg_state)
        {
        chg_stm_switch_state(CHG_STM_TRANSIT_ST);
        }
        mlog_print(MLOG_CHG, mlog_lv_info, "CHG STM initial state:\n");
        mlog_print(MLOG_CHG, mlog_lv_info, "current charge state: %d, pre-chargestate: %d.\n",
                   cur_chg_state, pre_chg_state);
        mlog_print(MLOG_CHG, mlog_lv_info, "charger type: %d, charge mode: %d.\n",
                   cur_chg_type, cur_chg_mode);

#if (MBB_CHG_EXTCHG == FEATURE_ON)
        mlog_print(MLOG_CHG, mlog_lv_info, "extchg_online: %d.\n", is_extchg_online);
#endif /*MBB_CHG_EXTCHG*/

#if (MBB_CHG_WIRELESS == FEATURE_ON)
        mlog_print(MLOG_CHG, mlog_lv_info, "wireless_online: %d.\n", is_wireless_online);
#endif /*MBB_CHG_WIRELESS*/

        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Charge State Machine init successfully.\n");
        chg_stm_inited = TRUE;
    }
    else
    {
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:Charge STM init be called more than one time.\n");
    }

    return CHG_OK;
}


void chg_set_usb_online_status(boolean online)
{
    chg_stm_state_info.usb_online_st = online;
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_stm_state_info.usb_online_st=%d\n",online);
}


boolean chg_get_usb_online_status(void)
{
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_get_usb_online_status=%d\n",\
                chg_stm_state_info.usb_online_st);
    return chg_stm_state_info.usb_online_st;
}


void chg_set_ac_online_status(boolean online)
{
    chg_stm_state_info.ac_online_st = online;
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_stm_state_info.ac_online_st=%d\n",online);
}

boolean chg_get_ac_online_status(void)
{
    chg_print_level_message(CHG_MSG_INFO, "CHG_STM:chg_get_ac_online_status=%d\n",\
                chg_stm_state_info.ac_online_st);
    return chg_stm_state_info.ac_online_st;
}


boolean chg_get_bat_present_status(void)
{
    if(TRUE == chg_get_batt_id_valid())
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_present_status=PRESENT\n");
        return PRESENT;
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bat_present_status=UNPRESENT\n");
        return UNPRESENT;
    }
    return PRESENT;
}


void chg_update_power_suply_info(void)
{

   if (NULL == g_chip)
   {
       return;
   }
   g_chip->ac_online = chg_get_ac_online_status();
   g_chip->usb_online = chg_get_usb_online_status();
#if (MBB_CHG_WIRELESS == FEATURE_ON)
   g_chip->wireless_online = chg_stm_get_wireless_online_st();
#endif/*MBB_CHG_WIRELESS*/
#if (MBB_CHG_EXTCHG == FEATURE_ON)
   g_chip->extchg_online = chg_stm_get_extchg_online_st();
   g_chip->extchg_status = chg_get_extchg_status();
#endif/*MBB_CHG_EXTCHG*/
   g_chip->bat_present = chg_get_bat_present_status();
   g_chip->bat_stat = chg_get_bat_status();
   g_chip->bat_health = chg_get_bat_health();
   g_chip->bat_technology = POWER_SUPPLY_TECHNOLOGY_LION;
   g_chip->bat_avg_voltage = chg_get_sys_batt_volt();
   g_chip->bat_avg_temp = chg_get_sys_batt_temp();
   g_chip->bat_capacity = chg_get_sys_batt_capacity();
   g_chip->bat_time_to_full = chg_get_batt_time_to_full();
/*USB�±�*/
#if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
   g_chip->usb_health = chg_get_usb_health();
#endif
#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
   g_chip->battery_average_current = chg_get_batt_current_average();
#endif
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:update_power_suply_info successfully!\n");
}

void chg_print_info_on(void)
{
    chg_print_flag = TRUE;
}
void chg_print_info_off(void)
{
    chg_print_flag = FALSE;
}

void coul_print_info_on(void)
{
    coul_print_flag = TRUE;
}
void coul_print_info_off(void)
{
    coul_print_flag = FALSE;
}


void chg_print_test_view_info(void)
{
    static uint8_t count = 0;
    if(count >= 3) /*״̬����ѵ2�μ�6S��ӡһ�γ����Ϣ��ֹ��ӡ��Ϣ̫��*/
    {
        
        count = 0;
        if(FALSE == chg_print_flag)
        {
            return;
        }
        
        chg_print_level_message(CHG_MSG_ERR, "**************CHG Tester View Info Begin**********\n");
        /*��ӡ��ǰ�����ĳ��״̬*/
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:current_stm_state=%d\n",
                             chg_stm_state_info.cur_stm_state);
        /*��ӡ��ǰ���������*/
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:current_charger_type=%d\n",
                            chg_stm_state_info.cur_chgr_type);
        /*��ӡ��ǰ�����ĳ��ģʽ�����ߣ����߻��Ƕ�����*/
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:current_chg_mode=%d\n",
                            chg_stm_state_info.cur_chg_mode);
        /*��ӡ��ǰ������ʱ��*/
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:current_charging_lasted_time=%d\n",
                            chg_stm_state_info.charging_lasted_in_sconds);
        /*��ӡ���ε���¶�*/
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_real_info.battery_one_temp = %d\n",
                            chg_real_info.battery_one_temp);
         /*��ӡƽ����ĵ���¶�*/
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_real_info.battery_temp = %d\n",
                            chg_real_info.battery_temp);

        /*��ӡ��ص��βɼ���ѹ*/
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_real_info.battery_one_volt = %d\n",
                            chg_real_info.battery_one_volt);
        /*��ӡ��ص�ѹƽ��ֵ*/
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_real_info.battery_volt = %d\n",
                            chg_real_info.battery_volt);

        /*��ӡ��ص����ٷֱ�*/
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_real_info.bat_capacity = %d\n",
                            chg_real_info.bat_capacity);
/*��ӡ��ǰ����ͣ���������λʱ��*/
#if ( FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT )
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:charger_lasted_without_charging_in_seconds=%d\n",
                            chg_stm_state_info.charger_lasted_without_charging_in_seconds);
#endif
        /*��ӡUSB��ǰ�¶�*/ 
        #if ( FEATURE_ON == MBB_CHG_USB_TEMPPT_ILIMIT )
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:chg_usb_cur_temp = %d'C.\n",
                                chg_usb_temp_info.usb_cur_temp);
        #endif
        chg_print_level_message(CHG_MSG_ERR, "**************CHG Tester View Info End**********\n");

    }
    else
    {
        count++;
    }
}

#ifdef CONFIG_MBB_FAST_ON_OFF
#if(MBB_REB == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : unsigned int chg_is_bat_only(void)
 ��������  : ����ɿ���-�鿴�Ƿ��ǵ������λ
 �������  : none
 �������  : none
 �� �� ֵ  : 1-�������λ 0-USB/DC/wireless
*****************************************************************************/
unsigned int chg_is_bat_only(void)
{
    return ( CHG_BAT_ONLY_MODE == chg_stm_state_info.cur_chg_mode );
}

/*****************************************************************************
 �� �� ��  : get_low_bat_level
 ��������  : ��ȡ��Ʒ��ص͵��ѹֵ(�ýӿ���ʱ��׮,����Ҫ�ŵ���ŵ�ģ����)
 �������  : none
 �������  : none
 �� �� ֵ  : ��ص�ѹֵ(mv)
*****************************************************************************/
int get_low_bat_level(void)
{
    /*Ҫ�ڳ��ģ���ʼ���Ժ����*/
    return g_chgBattVoltProtect.VbatLevelLow_MAX;
}
#endif/*CONFIG_MBB_REB*/


void chg_get_system_suspend_status(ulong64_t suspend_status)
{
#if (MBB_CHG_EXTCHG == FEATURE_ON)
    if(suspend_status)
    {
        mbb_fastonoff_chg_flag = true;
        /*����ٹػ���ģ��USB ID�γ�*/
        if(TRUE == chg_stm_get_extchg_online_st())
        {
            #ifdef BSP_CONFIG_BOARD_E5771S_852
            #else
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Enter Fastboot extchg online stop extchg!\n");
            /*ģ��USB ID�γ�*/
            (void)battery_monitor_blocking_notifier_call_chain(0, CHG_EXGCHG_CHGR);
            #endif
        }
        else
        {
            chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Enter Fastboot extchg offline do nothing!\n");
        }
    }
    else
    {
        mbb_fastonoff_chg_flag = false;
        /*�˳��ٹػ�����USB�����ϱ� ID�жϣ����ģ�鲻������*/
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:Exit Fastboot extchg offline do nothing!\n");
    }
#endif
}
#endif/*CONFIG_MBB_FAST_ON_OFF*/

/**********************************************************************
�� �� ��: chg_low_battery_event_handler
��������: �յ����ؼƵ͵��¼���Ĵ�����
�������: None
�������: None
�� �� ֵ: �ޡ�
ע������: Linuxϵͳ�У����øú���ʱ���ж��Ƿ����¼�û�д������
***********************************************************************/
#if (MBB_CHG_COULOMETER == FEATURE_ON)
#define LOW_BATT_DET_THRESHOLD    (3450)/*�͵��ж�������*/
void chg_low_battery_event_handler(void)
{
    int32_t batt_volt = chg_get_batt_volt_value();

#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    if(TRUE == chg_is_powdown_charging() && gpio_get_value(EXTCHG_OTG_DET_GPIO))
#else
    if(TRUE == chg_is_powdown_charging())
#endif
    {
        chg_print_level_message(CHG_MSG_ERR,"CHG_STM:no need to care��set bypass!\n");
        return;        
    }
    if(LOW_BATT_DET_THRESHOLD < batt_volt)
    {
        batt_volt = chg_get_batt_volt_value();
        if(LOW_BATT_DET_THRESHOLD < batt_volt)
        {
            chg_print_level_message(CHG_MSG_ERR,"CHG_STM:invalid event��set bypass!\n");
            return;
        }
    }
    chg_print_level_message(CHG_MSG_ERR,"CHG_STM:battery is low power��system will shutdown!\n");
    wake_lock_timeout(&g_chip->alarm_wake_lock,(long)msecs_to_jiffies(ALARM_REPORT_WAKELOCK_TIMEOUT));  
    chg_set_sys_batt_capacity(BATT_CAPACITY_SHUTOFF);
    chg_bat_timer_set( LOW_BATT_SHUTOFF_DURATION, chg_set_power_off, DRV_SHUTDOWN_LOW_BATTERY);  
}
#endif
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
#define BOOST_DELAY_TIMER  50
boolean extchg_monitor_func_in_sleep_mode(int32_t bat_vol, int32_t bat_temp);
int32_t batt_revise_calc_average_volt_value(int32_t new_data);
int32_t batt_revise_calc_average_temp_value(int32_t new_data);
int32_t batt_revise_calc_average_curr_value(int32_t new_data);
#endif
/**********************************************************************
�� �� ��: chg_sleep_batt_check_timer
��������: �������������״̬ʱ��timer���Ѻ����ص�ѹ�¶ȵ�
�������: None
�������: ���յ��¼�
�� �� ֵ: �ޡ�
ע������: Linuxϵͳ�У����øú���ʱ���ж��Ƿ����¼�û�д������
***********************************************************************/
void chg_sleep_batt_check_timer(struct work_struct *work)
{
    int32_t batt_volt = 0;
    int32_t batt_temp = 0;
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    static int32_t init_flag = FALSE;
    int32_t batt_volt_ave = 0;
    boolean low_bat_flag = FALSE;
#if defined(BSP_CONFIG_BOARD_E5771H_937)
    int ret = 0;
    int32_t volt_of_short = 0;
    int32_t batt_soc = 0;
#endif
#endif

    #ifdef CONFIG_COUL
    /*����һ�ο��ؼ�ǿ��У׼*/
    chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:bsp_coul_cail_on COUL_CAIL_ON");
    bsp_coul_cail_on();
    msleep(COUL_READY_DELAY_MS);
    #endif
    batt_volt = (int32_t)chg_get_batt_volt_value();
    batt_temp = (int32_t)chg_get_temp_value(CHG_PARAMETER__BATT_THERM_DEGC);
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    batt_temp = chg_batt_temp_revise(batt_temp);
    batt_volt_ave = chg_get_sys_batt_volt();
#endif

    chg_print_level_message(CHG_MSG_ERR,"CHG_STM:modem_notify_get_batt_info_callback, batt_volt %d,batt_temp %d!\n",
           batt_volt, batt_temp);

#if (MBB_CHG_EXTCHG == FEATURE_ON)
    /*����/����/����������λ�����е͵���߹��´���*/
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    if (FALSE == is_chg_charger_removed())
#else
    if ((FALSE == is_chg_charger_removed()) || (TRUE == chg_stm_get_extchg_online_st()))
#endif
    {
#if defined(BSP_CONFIG_BOARD_E5771H_937)
        /*E5771h-937�ػ����������2.94V��BOOST�رգ�����ػ������ָ�����Ȼ��λ�������ڳ䣬�ﵽsoc 11%�Ļָ����޻ָ����˶�����Ĺ��ܡ�
          �����ڳ����chg_extchg_monitor_func�����м�⵽����·��·һ���������������ʱ����
          ���뵽chg_sleep_batt_check_timer��������ʱ���ڳ������λ������뵽�˷�֧�������Ҫ��������жϣ�11%��ʱ��ǿ�ƴ�BOOST*/
        /*ͨ��HKADC8��ȡ��ѹ*/
        ret = bsp_hkadc_convert(EXTCHG_SHORT_VOLT_CHAN, &volt_of_short);
        if(ret)
        {
            chg_print_level_message(CHG_MSG_ERR, "bsp_hkadc_convert is error!!!\n");
        }

        /*��������ĵ�ѹС�ڵ���0ʱ������boost��⣬���Ƿ���Ҫ�����������ض�ʱ��*/
        if(volt_of_short <= 0)
        {
            chg_print_level_message(CHG_MSG_ERR, "enter test branch!!!\n");

            /*�жϵ����������10%*/
            batt_soc = chg_get_sys_batt_capacity();
            if(batt_soc > EXTCHG_STOP_CAPACITY_TEN)
            {
                /*ǿ�ƴ�boost*/
                gpio_direction_output(RE_ILIM_1A_GPIO, 1);
                extchg_set_charge_enable(TRUE);
                mdelay(BOOST_DELAY_TIMER);

                /*�ٴμ��������Ƿ��·*/
                if(extchg_is_perph_circult_short())  
                {
                    /*�������·����ر�boost*/
                    extchg_set_charge_enable(FALSE);
                    chg_print_level_message(CHG_MSG_ERR, "extchg always short!!!\n");
                }
                else
                {                   
                    extchg_short_flag = FALSE;
                    /*�˴���ext_chg_status_old������ʼ��ΪĬ��ֵ����ֹ�ָ�����Ϊ1A�ĳ���*/
                    ext_chg_status_old = RE_ILIM_NA;

                    /*��������������ļ�ض�ʱ��*/
                    schedule_delayed_work(&g_chip->extchg_monitor_work, msecs_to_jiffies(0));
                    chg_print_level_message(CHG_MSG_ERR, "extchg not short anymore, restart extchg monitor timer!!!\n");
                }
            }
            else
            {
                //do nothing
            }
        }
#endif
        chg_print_level_message(CHG_MSG_INFO,"CHG_STM:modem_notify_get_batt_info_callback charger plug in do nothing!*****\n");
        goto end;
    }
#else
    if (FALSE == is_chg_charger_removed())
    {
        chg_print_level_message(CHG_MSG_INFO,"CHG_STM:modem_notify_get_batt_info_callback charger plug in do nothing!*****\n");
        goto end;
    }
#endif/*defined(MBB_CHG_EXTCHG)*/
#if (MBB_CHG_COULOMETER == FEATURE_ON)
    /*��ѯsoc���Ա�Ӧ�õ͵���ʾ*/
    chg_poll_batt_soc();
    if(batt_volt < BATT_VOLT_POWER_OFF_THR)
    {
        /*�͵�ػ�����״̬��ϵͳ�Ժ�ػ�*/
        wake_lock_timeout(&g_chip->alarm_wake_lock,
            (long)msecs_to_jiffies(SHUTDOWN_WAKELOCK_TIMEOUT));
        chg_print_level_message(CHG_MSG_ERR,\
        "CHG_STM:batt_volt < poweroff voltage threshold report power off*****\n");
    }
#elif (MBB_CHG_BQ27510 == FEATURE_ON)
    /*just monitor batt volt*/
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    #if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771H_937)
    if(((batt_volt < BATT_VOLT_POWER_OFF_THR) || (batt_volt_ave < BATT_VOLTAGE_3350)) \
        && (FALSE == chg_is_powdown_charging()))
    {
            /*�͵�ػ�����״̬��ϵͳ�Ժ�ػ�*/
            wake_lock_timeout(&g_chip->alarm_wake_lock,
            (long)msecs_to_jiffies(SHUTDOWN_WAKELOCK_TIMEOUT));
            low_bat_flag = TRUE;
            chg_print_level_message(CHG_MSG_ERR,\
                "CHG_STM:batt_volt < poweroff voltage threshold report power off*****\n");
    } 
    #else  /* E5771s-852 �мٹػ����Բ��ڹػ����޸����͵�澯�����ߡ�E5771h-937�������ȷ�� */
       /*  do nothing */
    #endif
#else
    if(batt_volt < BATT_VOLT_POWER_OFF_THR)
    {
            /*�͵�ػ�����״̬��ϵͳ�Ժ�ػ�*/
            wake_lock_timeout(&g_chip->alarm_wake_lock,
            (long)msecs_to_jiffies(SHUTDOWN_WAKELOCK_TIMEOUT));
            #if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
            low_bat_flag = TRUE;
            #endif
            chg_print_level_message(CHG_MSG_ERR,\
                "CHG_STM:batt_volt < poweroff voltage threshold report power off*****\n");
    }  
#endif  
#else
    /* �����ص�ѹ���ڵ͵�������ʲô����������������¼��ϱ�Ӧ�� */
    if (BATT_VOLT_LEVELLOW_MAX < batt_volt)
    {
        chg_print_level_message(CHG_MSG_INFO,"CHG_STM:batt_volt > low battery threshold do nothing!*****\n");
    }
    else if ((BATT_VOLT_POWER_OFF_THR < batt_volt) && (BATT_VOLT_LEVELLOW_MAX >= batt_volt))
    {
        chg_print_level_message(CHG_MSG_ERR,"CHG_STM:Batt_volt is in 3450-3550mV report low battery*****\n");
        wake_lock_timeout(&g_chip->alarm_wake_lock,
            (long)msecs_to_jiffies(ALARM_REPORT_WAKELOCK_TIMEOUT));
        chg_set_sys_batt_capacity(BATT_CAPACITY_LEVELLOW);
        chg_print_level_message(CHG_MSG_ERR,"CHG_STM:send MSG to app for show low power! \n ");
    }
    else
    {
        wake_lock_timeout(&g_chip->alarm_wake_lock,
            (long)msecs_to_jiffies(ALARM_REPORT_WAKELOCK_TIMEOUT));
        chg_print_level_message(CHG_MSG_ERR,"CHG_STM:batt_volt < poweroff voltage threshold report power off*****\n");
        chg_set_sys_batt_capacity(BATT_CAPACITY_SHUTOFF);
    }
#endif
    /* ����¶ȱ�����ʹ�� ���� ����¶���������Χ��ʲô����������������¼��ϱ�Ӧ�� */
    #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
    if((FALSE == SHUTOFF_LOW_TEMP_PROTECT_ENABLE) || (FALSE == SHUTOFF_OVER_TEMP_PROTECT_ENABLE))
    {
        chg_print_level_message(CHG_MSG_INFO,"CHG_STM:Batt_temp protect is disable \n");
    }
    else if (((SHUTOFF_OVER_TEMP_SHUTOFF_THRESHOLD - SHUTOFF_HIGH_TEMP_WARN_LEN) > batt_temp) \
        && (SHUTOFF_LOW_TEMP_SHUTOFF_THRESHOLD < batt_temp))
    {
        if(TRUE == chg_is_powdown_charging())
        {    /* �ػ�����ǹ��»ָ��ϱ�  */
            if(batt_temp > SHUTOFF_LOW_TEMP_SHUTOFF_THRESHOLD + SHUTOFF_HIGH_TEMP_WARN_LEN \
                && low_over_temp_shutoff_falg == TRUE)
            {
                low_over_temp_shutoff_falg = FALSE;
                wake_lock_timeout(&g_chip->alarm_wake_lock,
                    (long)msecs_to_jiffies(ALARM_REPORT_WAKELOCK_TIMEOUT));
                chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_GOOD;
                chg_send_stat_to_app((uint32_t)DEVICE_ID_TEMP, (uint32_t)TEMP_BATT_NORMAL);
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:pd charge send app low temp back off\n ");
            }
            else if(up_over_temp_shutoff_falg == TRUE)
            {
                up_over_temp_shutoff_falg = FALSE;
                wake_lock_timeout(&g_chip->alarm_wake_lock,
                    (long)msecs_to_jiffies(ALARM_REPORT_WAKELOCK_TIMEOUT));
                chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_GOOD;
                chg_send_stat_to_app((uint32_t)DEVICE_ID_TEMP, (uint32_t)TEMP_BATT_NORMAL);
                chg_print_level_message(CHG_MSG_ERR, "CHG_STM:pd charge send app high temp back off\n ");
            }
            else
            {
                /* do nothing */
            }
        }
    }
    #else
    if ((((SHUTOFF_OVER_TEMP_SHUTOFF_THRESHOLD - SHUTOFF_HIGH_TEMP_WARN_LEN) > batt_temp)
        && (SHUTOFF_LOW_TEMP_SHUTOFF_THRESHOLD < batt_temp))
        || (FALSE == SHUTOFF_LOW_TEMP_PROTECT_ENABLE) 
            || (FALSE == SHUTOFF_OVER_TEMP_PROTECT_ENABLE))
    {
        chg_print_level_message(CHG_MSG_INFO,"CHG_STM:Batt_temp is in -20-58 deg do nothing*****\n");
    }
    #endif
    else if ((SHUTOFF_OVER_TEMP_SHUTOFF_THRESHOLD - SHUTOFF_HIGH_TEMP_WARN_LEN) <= batt_temp)
    {
        if (SHUTOFF_OVER_TEMP_SHUTOFF_THRESHOLD <= batt_temp)
        {
            wake_lock_timeout(&g_chip->alarm_wake_lock,
                (long)msecs_to_jiffies(ALARM_REPORT_WAKELOCK_TIMEOUT));
            #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
            if(TRUE == chg_is_powdown_charging())
            {   /* �ػ����>=65���ϱ�  */
                up_over_temp_shutoff_falg = TRUE;
            }
            #endif
            chg_print_level_message(CHG_MSG_ERR,"CHG_STM:Batt_temp is more than 60 deg, power off*****\n");
            chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_DEAD;
            chg_send_stat_to_app((uint32_t)DEVICE_ID_KEY, (uint32_t)GPIO_KEY_POWER_OFF);
            
        }
        else
        {
            chg_print_level_message(CHG_MSG_ERR,"CHG_STM:Batt_temp is in 58-60 deg, report overheat*****\n");
            wake_lock_timeout(&g_chip->alarm_wake_lock,
                (long)msecs_to_jiffies(ALARM_REPORT_WAKELOCK_TIMEOUT));
            chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_OVERHEAT;
            chg_send_stat_to_app((uint32_t)DEVICE_ID_TEMP, (uint32_t)TEMP_BATT_HIGH);
            chg_print_level_message(CHG_MSG_ERR,"CHG_STM:send MSG to app for show overheat! \n ");
        }
    }
    else
    {
        wake_lock_timeout(&g_chip->alarm_wake_lock,
            (long)msecs_to_jiffies(ALARM_REPORT_WAKELOCK_TIMEOUT));
        #if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
        if(TRUE == chg_is_powdown_charging())
        {   /* �ػ����<=-20���ϱ�  */
            low_over_temp_shutoff_falg = TRUE;
        }
        #endif
        chg_print_level_message(CHG_MSG_ERR,"CHG_STM:Batt_temp is less than -20 deg, report cold*****\n");
        chg_stm_state_info.bat_heath_type = POWER_SUPPLY_HEALTH_COLD;
        chg_send_stat_to_app((uint32_t)DEVICE_ID_TEMP, (uint32_t)TEMP_BATT_LOW);
    }
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    if(FALSE == init_flag)
    {
        battery_voltage = batt_volt;
        battery_temperature = batt_temp;
#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
        battery_current = hisi_battery_current();
#endif
        init_flag = TRUE;
    }

    battery_voltage = batt_revise_calc_average_volt_value(batt_volt);
    battery_temperature = batt_revise_calc_average_temp_value(batt_temp);
#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
    battery_current = batt_revise_calc_average_curr_value(hisi_battery_current());

    if (battery_current_prev != battery_current)
    {
        battery_current_prev = battery_current;
        chg_real_info.bat_current_avg = battery_current;
        chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY, \
            (uint32_t)CHG_EVENT_NONEED_CARE);
    }
#endif
#endif

#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    if (FALSE == low_bat_flag)
    {
        if (extchg_monitor_func_in_sleep_mode(batt_volt, batt_temp))
        {
            bsp_softtimer_modify(&g_chg_sleep_timer, FAST_POLL_CYCLE_OF_EXTCHG);
            chg_print_level_message(CHG_MSG_ERR, \
                "CHG_STM:bsp_softtimer_modify to FAST_POLL_CYCLE!\n");
        }
        else
        {
            bsp_softtimer_modify(&g_chg_sleep_timer, SLOW_POLL_CYCLE_OF_EXTCHG);
            chg_print_level_message(CHG_MSG_ERR, \
                "CHG_STM:bsp_softtimer_modify to SLOW_POLL_CYCLE!\n");
        }
    }
    else
    {
        bsp_softtimer_modify(&g_chg_sleep_timer, FAST_POLL_CYCLE_OF_EXTCHG);
    }
#endif
    chg_print_level_message(CHG_MSG_INFO,"CHG_STM:wait next modem time expire!\n");

end:
#if (MBB_CHG_PLATFORM_V7R2 == FEATURE_ON)
    wake_unlock(&g_chip->chg_wake_lock);
#endif
}

#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)

int32_t batt_revise_calc_average_curr_value(int32_t new_data)
{
    int32_t    index = 0;
    int32_t    sum = 0;
    int32_t    bat_curr_avg = 0;
    int32_t    new_poll_mode;
    static int32_t  old_poll_mode = FAST_POLL_CYCLE_OF_EXTCHG;
    static uint32_t record_avg_num_fast = 0;
    static uint32_t record_avg_num_slow = 0;
    static int32_t record_value_fast[CHG_BAT_TEMP_REVISE_SAMPLE_FAST] = {0};
    static int32_t record_value_slow[CHG_BAT_TEMP_REVISE_SAMPLE_SLOW] = {0};

    /*��ѯ��ѯģʽ*/
    new_poll_mode = g_chg_sleep_timer.timeout;

    if(new_poll_mode != old_poll_mode)
    {
        if(FAST_POLL_CYCLE_OF_EXTCHG == new_poll_mode)/*������ѯ�л�����ǰ�Ŀ���ѯ*/
        {
            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_FAST;index++)
            {
                record_value_fast[index] = battery_current;
            }
            record_avg_num_fast = CHG_BAT_TEMP_REVISE_SAMPLE_FAST;
        }
        else//�ɿ���ѯ�л�������ѯ
        {
            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;index++)
            {
                record_value_slow[index] = battery_current;
            }
            record_avg_num_slow = CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;
        }

        old_poll_mode = new_poll_mode;
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "new_poll_mode = old_poll_mode!\n");
    }

    if(FAST_POLL_CYCLE_OF_EXTCHG == new_poll_mode)//����ѯģʽ
    {
        /*�����е�ǰԪ�ر��С��6*/
        if(CHG_BAT_TEMP_REVISE_SAMPLE_FAST > record_avg_num_fast)
        {
            record_value_fast[record_avg_num_fast] = new_data;
            record_avg_num_fast++;

            for(index = 0;index < record_avg_num_fast; index++)
            {
                sum += record_value_fast[index];
            }

            bat_curr_avg = sum / record_avg_num_fast;
        }
        else/*Ԫ�ظ�����Ŵ��ڵ���6��*/
        {
            record_value_fast[record_avg_num_fast % CHG_BAT_TEMP_REVISE_SAMPLE_FAST] 
                = new_data;
            record_avg_num_fast++;

            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_FAST; index++)
            {
                sum += record_value_fast[index];
            }

            bat_curr_avg = sum / CHG_BAT_TEMP_REVISE_SAMPLE_FAST;

            if(CHG_BAT_TEMP_REVISE_SAMPLE_FAST * 2 == record_avg_num_fast)
            {
                record_avg_num_fast = CHG_BAT_TEMP_REVISE_SAMPLE_FAST;
            }
        }
    }
    else//����ѯģʽ
    {
        /*�����е�ǰԪ�ر��С��3*/
        if(CHG_BAT_TEMP_REVISE_SAMPLE_SLOW > record_avg_num_slow)
        {
            record_value_slow[record_avg_num_slow] = new_data;
            record_avg_num_slow++;

            for(index = 0;index < record_avg_num_slow; index++)
            {
                sum += record_value_slow[index];
            }

            bat_curr_avg = sum / record_avg_num_slow;
        }
        else/*Ԫ�ظ�����Ŵ��ڵ���3��*/
        {
            record_value_slow[record_avg_num_slow % CHG_BAT_TEMP_REVISE_SAMPLE_SLOW] 
                = new_data;
            record_avg_num_slow++;

            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_SLOW; index++)
            {
                sum += record_value_slow[index];
            }

            bat_curr_avg = sum / CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;

            if(CHG_BAT_TEMP_REVISE_SAMPLE_SLOW * 2 == record_avg_num_slow)
            {
                record_avg_num_slow = CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;
            }
        }

    }

    return bat_curr_avg;
}

int32_t chg_batt_temp_revise(int32_t batt_temp)
{
#if defined(BSP_CONFIG_BOARD_E5771S_852)
    /* E5771s-852�����ֳ����²����¶Ȳ���������ֱ�ӹ��ɣ�ֱ����Ծ����¶Ƚ��в��� */
    if((batt_temp <= 40) || (batt_temp == 52) || (batt_temp == 57) || (batt_temp == 58))
    {
        batt_temp += 5;
    }
    else if(((batt_temp >= 41) && (batt_temp <= 46)) || (batt_temp == 51) || (batt_temp >= 59))
    {
        batt_temp += 4;
    }
    else if(batt_temp == 47)
    {
        batt_temp += 3;
    }
    else if((batt_temp >= 48) && (batt_temp <= 50))
    {
        batt_temp += 2;
    }
    else if(batt_temp == 54)
    {
        batt_temp += 7;
    }
    else if((batt_temp == 55) || (batt_temp == 56) || (batt_temp == 53))
    {
        batt_temp += 6;
    }
    else
    {
    /*  */
    }

    return batt_temp;
#elif defined(BSP_CONFIG_BOARD_E5771H_937)  /*937ʵ�ʲ�����Ҫ���ű���*/

    /*1.���ڳ�糡��*/
    if(FALSE == is_chg_charger_removed())
    {
        if(batt_temp >= 30 && batt_temp <= 34)
        {
            batt_temp += 11;
        }
        else if(batt_temp >= 35 && batt_temp <= 44)
        {
            batt_temp += 10;
        }
        else if(45 == batt_temp)
        {
            batt_temp += 9;
        }
        else if(batt_temp >= 46 && batt_temp <= 54)
        {
            batt_temp += 8;
        }
        else if(batt_temp >= 55 && batt_temp <= 57)
        {
            batt_temp += 7;
        }
        else if(batt_temp >= 58 && batt_temp <= 62)
        {
            batt_temp = 64;
        }
        else if(batt_temp >= 63 && batt_temp <= 65)
        {
            batt_temp += 1;
        }
        else
        {
            //do nothing
        }
    }
    /*2.��������*/
    else
    {
        if(batt_temp >= 30 && batt_temp <= 48)
        {
            batt_temp += 7;
        }
        else if(batt_temp >= 49 && batt_temp <= 52)
        {
            batt_temp += 6;
        }
        else if(batt_temp >= 53 && batt_temp <= 55)
        {
            batt_temp += 7;
        }
        else if(batt_temp >= 56 && batt_temp <= 58)
        {
            batt_temp += 6;
        }
        else if(batt_temp >= 59 && batt_temp <= 62)
        {
            batt_temp = 64;
        }
        else if(batt_temp >= 63 && batt_temp <= 65)
        {
            batt_temp += 2;
        }
    }
    return batt_temp;
#else
    if (batt_temp <= CHG_BAT_TEMP_REVISE_TEM_OF_NOREVISE)
    {
        return batt_temp;
    }

    if ((FALSE == is_chg_charger_removed()) && chg_stm_get_extchg_online_st())
    {
        if (CHG_WALL_CHGR == chg_stm_get_chgr_type())
        {
            batt_temp += 4;
        }
        else
        {
            //do nothing
        }
    }
    else if ((FALSE == is_chg_charger_removed()) && (!chg_stm_get_extchg_online_st()))
    {
        batt_temp += 7;
    }
    else
    {
        if (battery_current <= BATT_CURRENT_I_3000)
        {
            batt_temp = (batt_temp * 2) / 3 + 5;
        }
        else if ((battery_current > BATT_CURRENT_I_3000) && \
            (battery_current <= BATT_CURRENT_I_2500))
        {
            batt_temp -= 8;
        }
        else if ((battery_current > BATT_CURRENT_I_2500) \
            && (battery_current <= BATT_CURRENT_I_1500))
        {
            batt_temp -= 3;
        }
        else//battery_current > -1500
        {
            batt_temp += 2;
        }
    }

    return batt_temp;
#endif
}
#endif
#if (MBB_CHG_EXTCHG == FEATURE_ON)

void chg_extchg_info_dump(void)
{
    if(FALSE == chg_print_flag)
    {
        return;
    }
    chg_print_level_message(CHG_MSG_ERR, "EXTCHG:extchg_diable_st=%d\n",g_extchg_diable_st);    
    chg_print_level_message(CHG_MSG_ERR, "EXTCHG:ui_mode=%d\n",g_ui_choose_exchg_mode);
    chg_print_level_message(CHG_MSG_ERR, "EXTCHG:otg_extchg=%d\n",is_otg_extchg);    
    chg_print_level_message(CHG_MSG_ERR, "EXTCHG:is_extchg_ovtemp=%d\n",is_extchg_ovtemp);        
    chg_print_level_message(CHG_MSG_ERR, "EXTCHG:extchg_status=%d\n",chg_stm_state_info.extchg_status);
    chg_print_level_message(CHG_MSG_ERR, "EXTCHG:extchg_online_st=%d\n",chg_stm_state_info.extchg_online_st);    
    chg_print_level_message(CHG_MSG_ERR, "EXTCHG:exchg_enable=%d\n",g_exchg_enable_flag);     
} 
#if defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577S_932) \
    ||defined(BSP_CONFIG_BOARD_E5577S_324)|| defined(BSP_CONFIG_BOARD_E5577BS_937)
boolean extchg_circult_short_detect(void)
{
    /*���VBUS״̬�Ƿ�λ*/
    chg_status_type  chg_stat = {0};
    boolean op_result = TRUE;
    op_result = chg_get_IC_status(&chg_stat);
    if (FALSE == op_result)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_DRV: chg_get_IC_status error !\n");
    }
    else
    {
        if (CHG_STAT_UNKNOWN == chg_stat.chg_vbus_stat)
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_DRV: chg_get_IC_status IC status VBUS UNKOWN!\n");
            return TRUE;
        }
    }
    return FALSE;
}
#endif
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
void ext_chg_info_dump(void)
{
    if (FALSE == coul_print_flag)
    {
        return;
    }

    chg_print_level_message(CHG_MSG_ERR, "**************BQ27510 Tester \
        Info Begin**********\n");

    chg_print_level_message(CHG_MSG_ERR, \
        "INFO FOR COUL: TEMPERATURE = %d\n", hisi_bq27510_battery_temperature());

    chg_print_level_message(CHG_MSG_ERR, \
        "INFO FOR COUL: VOLTAGE = %d\n", hisi_bq27510_battery_voltage());

    chg_print_level_message(CHG_MSG_ERR, \
        "INFO FOR COUL: CURRENT = %d\n", hisi_bq27510_battery_current());

    chg_print_level_message(CHG_MSG_ERR, \
        "INFO FOR COUL: capacity = %d\n", hisi_bq27510_battery_capacity());

    chg_print_level_message(CHG_MSG_ERR, \
        "INFO FOR COUL: fcc = %d\n", hisi_bq27510_battery_fcc());

    chg_print_level_message(CHG_MSG_ERR, \
        "INFO FOR COUL: rm = %d\n", hisi_bq27510_battery_rm());

    chg_print_level_message(CHG_MSG_ERR, \
        "INFO FOR COUL: Qmax = %d\n", hisi_bq27510_battery_qmax());

    chg_print_level_message(CHG_MSG_ERR, \
        "INFO FOR COUL: is_battery_full = %d\n", hisi_is_bq27510_battery_full());

    chg_print_level_message(CHG_MSG_ERR, "**************BQ27510 Tester \
        Info End**********\n");
}


int32_t batt_revise_calc_average_volt_value(int32_t new_data)
{
    int32_t    index = 0;
    int32_t    sum = 0;
    int32_t    bat_volt_avg = 0;
    int32_t    new_poll_mode;
    static int32_t  old_poll_mode = FAST_POLL_CYCLE_OF_EXTCHG;
    static uint32_t record_avg_num_fast = 0;
    static uint32_t record_avg_num_slow = 0;
    static int32_t record_value_fast[CHG_BAT_TEMP_REVISE_SAMPLE_FAST] = {0};
    static int32_t record_value_slow[CHG_BAT_TEMP_REVISE_SAMPLE_SLOW] = {0};

    /*��ѯ��ѯģʽ*/
    new_poll_mode = g_chg_sleep_timer.timeout;

    if(new_poll_mode != old_poll_mode)
    {
        if(FAST_POLL_CYCLE_OF_EXTCHG == new_poll_mode)/*������ѯ�л�����ǰ�Ŀ���ѯ*/
        {
            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_FAST;index++)
            {
                record_value_fast[index] = battery_voltage;
            }
            record_avg_num_fast = CHG_BAT_TEMP_REVISE_SAMPLE_FAST;
        }
        else//�ɿ���ѯ�л�������ѯ
        {
            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;index++)
            {
                record_value_slow[index] = battery_voltage;
            }
            record_avg_num_slow = CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;
        }

        old_poll_mode = new_poll_mode;
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "new_poll_mode = old_poll_mode!\n");
    }

    if(FAST_POLL_CYCLE_OF_EXTCHG == new_poll_mode)//����ѯģʽ
    {
        /*�����е�ǰԪ�ر��С��6*/
        if(CHG_BAT_TEMP_REVISE_SAMPLE_FAST > record_avg_num_fast)
        {
            record_value_fast[record_avg_num_fast] = new_data;
            record_avg_num_fast++;

            for(index = 0;index < record_avg_num_fast; index++)
            {
                sum += record_value_fast[index];
            }

            bat_volt_avg = sum / record_avg_num_fast;
        }
        else/*Ԫ�ظ�����Ŵ��ڵ���6��*/
        {
            record_value_fast[record_avg_num_fast % CHG_BAT_TEMP_REVISE_SAMPLE_FAST] 
                = new_data;
            record_avg_num_fast++;

            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_FAST; index++)
            {
                sum += record_value_fast[index];
            }

            bat_volt_avg = sum / CHG_BAT_TEMP_REVISE_SAMPLE_FAST;

            if(CHG_BAT_TEMP_REVISE_SAMPLE_FAST * 2 == record_avg_num_fast)
            {
                record_avg_num_fast = CHG_BAT_TEMP_REVISE_SAMPLE_FAST;
            }
        }
    }
    else//����ѯģʽ
    {
        /*�����е�ǰԪ�ر��С��3*/
        if(CHG_BAT_TEMP_REVISE_SAMPLE_SLOW > record_avg_num_slow)
        {
            record_value_slow[record_avg_num_slow] = new_data;
            record_avg_num_slow++;

            for(index = 0;index < record_avg_num_slow; index++)
            {
                sum += record_value_slow[index];
            }

            bat_volt_avg = sum / record_avg_num_slow;
        }
        else/*Ԫ�ظ�����Ŵ��ڵ���3��*/
        {
            record_value_slow[record_avg_num_slow % CHG_BAT_TEMP_REVISE_SAMPLE_SLOW] 
                = new_data;
            record_avg_num_slow++;

            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_SLOW; index++)
            {
                sum += record_value_slow[index];
            }

            bat_volt_avg = sum / CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;

            if(CHG_BAT_TEMP_REVISE_SAMPLE_SLOW * 2 == record_avg_num_slow)
            {
                record_avg_num_slow = CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;
            }
        }

    }

    return bat_volt_avg;
}


int32_t batt_revise_calc_average_temp_value(int32_t new_data)
{
    int32_t    index = 0;
    int32_t    sum = 0;
    int32_t    bat_temp_avg = 0;
    int32_t    new_poll_mode;
    static int32_t  old_poll_mode = FAST_POLL_CYCLE_OF_EXTCHG;
    static uint32_t record_avg_num_fast = 0;
    static uint32_t record_avg_num_slow = 0;
    static int32_t record_value_fast[CHG_BAT_TEMP_REVISE_SAMPLE_FAST] = {0};
    static int32_t record_value_slow[CHG_BAT_TEMP_REVISE_SAMPLE_SLOW] = {0};

    /*��ѯ��ѯģʽ*/
    new_poll_mode = g_chg_sleep_timer.timeout;

    if(new_poll_mode != old_poll_mode)
    {
        if(FAST_POLL_CYCLE_OF_EXTCHG == new_poll_mode)/*������ѯ�л�����ǰ�Ŀ���ѯ*/
        {
            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_FAST;index++)
            {
                record_value_fast[index] = battery_temperature;
            }
            record_avg_num_fast = CHG_BAT_TEMP_REVISE_SAMPLE_FAST;
        }
        else//�ɿ���ѯ�л�������ѯ
        {
            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;index++)
            {
                record_value_slow[index] = battery_temperature;
            }
            record_avg_num_slow = CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;
        }

        old_poll_mode = new_poll_mode;
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "new_poll_mode = old_poll_mode!\n");
    }

    if(FAST_POLL_CYCLE_OF_EXTCHG == new_poll_mode)//����ѯģʽ
    {
        /*�����е�ǰԪ�ر��С��6*/
        if(CHG_BAT_TEMP_REVISE_SAMPLE_FAST > record_avg_num_fast)
        {
            record_value_fast[record_avg_num_fast] = new_data;
            record_avg_num_fast++;

            for(index = 0;index < record_avg_num_fast; index++)
            {
                sum += record_value_fast[index];
            }

            bat_temp_avg = sum / record_avg_num_fast;
        }
        else/*Ԫ�ظ�����Ŵ��ڵ���6��*/
        {
            record_value_fast[record_avg_num_fast % CHG_BAT_TEMP_REVISE_SAMPLE_FAST] 
                = new_data;
            record_avg_num_fast++;

            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_FAST; index++)
            {
                sum += record_value_fast[index];
            }

            bat_temp_avg = sum / CHG_BAT_TEMP_REVISE_SAMPLE_FAST;

            if(CHG_BAT_TEMP_REVISE_SAMPLE_FAST * 2 == record_avg_num_fast)
            {
                record_avg_num_fast = CHG_BAT_TEMP_REVISE_SAMPLE_FAST;
            }
        }
    }
    else//����ѯģʽ
    {
        /*�����е�ǰԪ�ر��С��3*/
        if(CHG_BAT_TEMP_REVISE_SAMPLE_SLOW > record_avg_num_slow)
        {
            record_value_slow[record_avg_num_slow] = new_data;
            record_avg_num_slow++;

            for(index = 0;index < record_avg_num_slow; index++)
            {
                sum += record_value_slow[index];
            }

            bat_temp_avg = sum / record_avg_num_slow;
        }
        else/*Ԫ�ظ�����Ŵ��ڵ��ڸ�*/
        {
            record_value_slow[record_avg_num_slow % CHG_BAT_TEMP_REVISE_SAMPLE_SLOW] 
                = new_data;
            record_avg_num_slow++;

            for(index = 0;index < CHG_BAT_TEMP_REVISE_SAMPLE_SLOW; index++)
            {
                sum += record_value_slow[index];
            }

            bat_temp_avg = sum / CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;

            if(CHG_BAT_TEMP_REVISE_SAMPLE_SLOW * 2 == record_avg_num_slow)
            {
                record_avg_num_slow = CHG_BAT_TEMP_REVISE_SAMPLE_SLOW;
            }
        }

    }

    return bat_temp_avg;
}


int extchg_set_charge_enable(boolean enable)
{
    int ret = 0;
#if defined(BSP_CONFIG_BOARD_E5771H_937)
/* E5771h-937��ƷӲ���°汾�޸Ŀ���BOOST���GPIO_2_08����λΪ��,ͨ��BOOST��ѹ������������Ӳ��*/
    int volt_of_boost = 0;
    bsp_hkadc_convert(EXTCHG_SHORT_VOLT_CHAN, &volt_of_boost);
    if(volt_of_boost > HW_VER_DISTINGUISH)
    {
        ret = gpio_direction_output(EXTCHG_CHG_ENABLE, enable);
    }
    else
    {
        if(FALSE == enable)
        {
            ret = gpio_direction_output(EXTCHG_CHG_ENABLE, 1);
        }
        else
        {
            ret = gpio_direction_output(EXTCHG_CHG_ENABLE, 0);
        }
    }
#else
    ret = gpio_direction_output(EXTCHG_CHG_ENABLE, enable);
#endif

    if(ret)
    {
        chg_print_level_message(CHG_MSG_ERR,"EXTCHG: %s EXTCHG_CHG_ENABLE failed!!\r\n ",\
                                             (enable?"Enable":"Disable"));
        return -1;
    }

    chg_print_level_message(CHG_MSG_DEBUG,"EXTCHG: %s EXTCHG_CHG_ENABLE success!!\r\n ",\
                                           (enable?"Enable":"Disable"));
    return 0;
}

#if defined(BSP_CONFIG_BOARD_E5771S_852)
void extchg_set_cur_level(EXTCHG_ILIM curr)
{
    if (RE_ILIM_500mA == curr)
    {   /*  E5771s-852��Ʒ��500mA��1A��ͬ������ʵ��1A */
        gpio_direction_output(RE_ILIM_1A_GPIO, 1);
        gpio_direction_output(RE_ILIM_2A_GPIO, 0);
        chg_print_level_message( CHG_MSG_DEBUG, \
            "EXTCHG: extcharge current limit to 500mA!!\r\n ");
    }
    else if(RE_ILIM_1A == curr)
    {
        gpio_direction_output(RE_ILIM_1A_GPIO, 1);
        gpio_direction_output(RE_ILIM_2A_GPIO, 0);
        chg_print_level_message( CHG_MSG_DEBUG, \
            "EXTCHG: extcharge current limit to 1000mA!!\r\n ");
    }
    else if(RE_ILIM_2A == curr)
    {
        gpio_direction_output(RE_ILIM_1A_GPIO, 1);
        gpio_direction_output(RE_ILIM_2A_GPIO, 1);
        chg_print_level_message( CHG_MSG_DEBUG, \
            "EXTCHG: extcharge current limit to 2000mA!!\r\n ");
    }
    else
    {
        //do nothing
    }
}
#elif defined(BSP_CONFIG_BOARD_E5_E5770s)  || defined(BSP_CONFIG_BOARD_E5771H_937)
/* E5771h-937����������E5770һ�£���500/1A/2A */
void extchg_set_cur_level(EXTCHG_ILIM curr)
{
    if (RE_ILIM_500mA == curr)
    {
        gpio_direction_output(RE_ILIM_1A_GPIO, 0);
        gpio_direction_output(RE_ILIM_2A_GPIO, 0);
        chg_print_level_message( CHG_MSG_DEBUG, \
            "EXTCHG: extcharge current limit to 500mA!!\r\n ");
    }
    else if(RE_ILIM_1A == curr)
    {
        gpio_direction_output(RE_ILIM_1A_GPIO, 1);
        gpio_direction_output(RE_ILIM_2A_GPIO, 0);
        chg_print_level_message( CHG_MSG_DEBUG, \
            "EXTCHG: extcharge current limit to 1000mA!!\r\n ");
    }
    else if(RE_ILIM_2A == curr)
    {
        gpio_direction_output(RE_ILIM_1A_GPIO, 1);
        gpio_direction_output(RE_ILIM_2A_GPIO, 1);
        chg_print_level_message( CHG_MSG_DEBUG, \
            "EXTCHG: extcharge current limit to 2000mA!!\r\n ");
    }
    else
    {
        //do nothing
    }
}
#else
void extchg_set_cur_level(EXTCHG_ILIM curr)
{
    return; /*  do nothing */
}
#endif

boolean extchg_is_perph_circult_short(void)
{
    int32_t volt_of_short = 0;
    int32_t volt_of_short_original = 0;
    int ret = 0;

    ret = bsp_hkadc_convert(EXTCHG_SHORT_VOLT_CHAN, &volt_of_short);
    if(ret)
    {
        chg_print_level_message( CHG_MSG_ERR,"EXTCHG: detect volt_of_short failed, \
                                              treat as short!!!\r\n ",0,0,0 );
        return TRUE;
    }
    chg_print_level_message( CHG_MSG_DEBUG, \
        "EXTCHG:volt_of_short = %d\n", volt_of_short,0,0);
#if defined(BSP_CONFIG_BOARD_E5771H_937)
    volt_of_short_original = (volt_of_short * RSIISTANCE_CENT_COUNT);//�ɼ��ĵ�ѹΪ��ѹ���ֵ����ԭΪԭʼֵ
#else
    volt_of_short_original = (volt_of_short * 151) / 51;//�ɼ��ĵ�ѹΪ��ѹ���ֵ����ԭΪԭʼֵ
#endif
    if (volt_of_short_original <= EXTCHG_SHORT_VOLT_THRESHOLD)
    {
        chg_print_level_message( CHG_MSG_ERR, \
                "EXTCHG: perph_circult is short!\
                        valtage = %d\n", volt_of_short_original,0,0);
        return TRUE;
    }
    else
    {
        chg_print_level_message( CHG_MSG_DEBUG,"EXTCHG: perph_circult is ok!\\n", 0,0,0);
        return FALSE;
    }
}

int usb_direction_flag_set(boolean flag)
{
    usb_set_direction_flag = flag;
    return flag;
}


void extchg_release_pwr_key(void)
{
    mdelay(500);
    gpio_direction_output(OTG_ON_CTRL_GPIO, 1);
    mdelay(500);
    gpio_direction_output(OTG_ON_CTRL_GPIO, 0);
}

static irqreturn_t extchg_plug_in_out_isr(int ext_dev_id)
{
    if(!gpio_int_state_get(EXTCHG_OTG_DET_GPIO))
    {
        return IRQ_NONE;
    }

    gpio_int_mask_set(EXTCHG_OTG_DET_GPIO);
    gpio_int_state_clear(EXTCHG_OTG_DET_GPIO);

    if(!gpio_get_value(EXTCHG_OTG_DET_GPIO))
    {
        schedule_work(&extchg_plug_in_work);
        gpio_int_trigger_set(EXTCHG_OTG_DET_GPIO, IRQ_TYPE_LEVEL_HIGH);
    }
    else
    {
        schedule_work(&extchg_plug_out_work);
        gpio_int_trigger_set(EXTCHG_OTG_DET_GPIO, IRQ_TYPE_LEVEL_LOW);
    }

    gpio_int_unmask_set(EXTCHG_OTG_DET_GPIO);
    return IRQ_HANDLED;
}

int extchg_gpio_isr_init(void)
{
    //������A��USBĸ�ڵ��豸����������GPIO�ĳ�ʼ��
    int ret = 0;
    nv_huawei_coul_firmware_update_info coul_firmware_update_info = {0x00};
    unsigned char battery_info[3] = {0x00};

#if defined(BSP_CONFIG_BOARD_E5_E5770s) || defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937)
    battery_current = hisi_battery_current();
    chg_real_info.bat_current_avg = battery_current;
#endif

    INIT_WORK(&extchg_plug_in_work, chg_extchg_insert_proc);
    INIT_WORK(&extchg_plug_out_work, chg_extchg_remove_proc);

    ret = gpio_direction_input(EXTCHG_OTG_DET_GPIO);
    if(ret)
    {
        chg_print_level_message( CHG_MSG_ERR, \
            "EXTCHG: EXTCHG_OTG_DET_GPIO gpio_direction_input error!!\r\n ");
        gpio_free(EXTCHG_OTG_DET_GPIO);
        return -1;
    }

    gpio_int_mask_set(EXTCHG_OTG_DET_GPIO);
    gpio_int_trigger_set(EXTCHG_OTG_DET_GPIO, IRQ_TYPE_LEVEL_LOW);
    gpio_set_function(EXTCHG_OTG_DET_GPIO, GPIO_INTERRUPT);

    ret = request_irq((unsigned int)gpio_to_irq(EXTCHG_OTG_DET_GPIO), \
            extchg_plug_in_out_isr,\
                      IRQF_NO_SUSPEND | IRQF_SHARED, "ext_a_chg_gpio_irq", &ext_dev_id);
    if (ret) {
        chg_print_level_message( CHG_MSG_ERR, \
            "EXTCHG: OTG_DET_GPIO request_irq error, errno = %d!!\r\n ", ret);
        free_irq((unsigned int)gpio_to_irq(EXTCHG_OTG_DET_GPIO), NULL);
        gpio_free(EXTCHG_OTG_DET_GPIO);
        return -1;
    }

    gpio_int_state_clear(EXTCHG_OTG_DET_GPIO);
    gpio_int_unmask_set(EXTCHG_OTG_DET_GPIO);
    enable_irq_wake(gpio_to_irq(EXTCHG_OTG_DET_GPIO));

    bsp_nvm_read(NV_HUAWEI_BATTERY_INFO_I,\
                    &coul_firmware_update_info,\
                        sizeof(nv_huawei_coul_firmware_update_info));
    strncpy(&battery_info,&coul_firmware_update_info.battery_sn[4],2);

    extchg_stop_threshold_powon = EXTCHG_STOP_THRESHOLD_POWON;
    extchg_stop_threshold_powdown = EXTCHG_STOP_THRESHOLD_POWDOWN;
    extchg_recharge_threshold = EXTCHG_RECHG_THRESHOLD;

#if defined(BSP_CONFIG_BOARD_E5_E5770s) 
    if(strstr(battery_info,"LC") != NULL)
    {
        extchg_limit_1a_capacity = EXTCHG_STOP_CAPACITY_THIRTYSIX;
        tbatt_supply_volt_threshold = LG_TBATT_SUPPLY_VOLT;
        tbatt_dischg_volt_threshold = LG_TBATT_DISCHG_VOLT;
        tbatt_supply_stop_threshold = LG_TBATT_SUPPLY_STOP_VOLT;
        tbatt_dischg_stop_threshold = LG_TBATT_DISCHG_STOP_VOLT;
    }
    else if(strstr(battery_info,"YI") != NULL)
    {
        extchg_limit_1a_capacity = EXTCHG_STOP_CAPACITY_EIGHTEEN;
        tbatt_supply_volt_threshold = SY_TBATT_SUPPLY_VOLT;
        tbatt_dischg_volt_threshold = SY_TBATT_DISCHG_VOLT;
        tbatt_supply_stop_threshold = SY_TBATT_SUPPLY_STOP_VOLT;
        tbatt_dischg_stop_threshold = SY_TBATT_DISCHG_STOP_VOLT;
    }
    else
    {
        extchg_limit_1a_capacity = EXTCHG_STOP_CAPACITY_THIRTYSIX;
        tbatt_supply_volt_threshold = SY_TBATT_SUPPLY_VOLT;
        tbatt_dischg_volt_threshold = SY_TBATT_DISCHG_VOLT;
        tbatt_supply_stop_threshold = SY_TBATT_SUPPLY_STOP_VOLT;
        tbatt_dischg_stop_threshold = SY_TBATT_DISCHG_STOP_VOLT;
    }
    extchg_limit_500ma_capacity = EXTCHG_STOP_CAPACITY_FIFTHTEEN;
#elif defined(BSP_CONFIG_BOARD_E5771S_852)  || defined(BSP_CONFIG_BOARD_E5771H_937)
/*  E5771 �ĵ�ز������ݣ�ҲҪ���ݵ�س������� ����������ݴ�ˢ�� */
     extchg_limit_1a_capacity = EXTCHG_STOP_CAPACITY_THIRTYSIX;
     tbatt_supply_volt_threshold = SY_TBATT_SUPPLY_VOLT;
     tbatt_dischg_volt_threshold = SY_TBATT_DISCHG_VOLT;
     tbatt_supply_stop_threshold = SY_TBATT_SUPPLY_STOP_VOLT;
     tbatt_dischg_stop_threshold = SY_TBATT_DISCHG_STOP_VOLT;
     extchg_limit_500ma_capacity = EXTCHG_STOP_CAPACITY_TWENTYFIVE;
#else
     extchg_limit_1a_capacity = EXTCHG_STOP_CAPACITY_THIRTYSIX;
     tbatt_supply_volt_threshold = SY_TBATT_SUPPLY_VOLT;
     tbatt_dischg_volt_threshold = SY_TBATT_DISCHG_VOLT;
     tbatt_supply_stop_threshold = SY_TBATT_SUPPLY_STOP_VOLT;
     tbatt_dischg_stop_threshold = SY_TBATT_DISCHG_STOP_VOLT;
     extchg_limit_500ma_capacity = EXTCHG_STOP_CAPACITY_FIFTHTEEN;
#endif
#ifdef BSP_CONFIG_BOARD_E5_E5770s
    if (FALSE == chg_is_powdown_charging())
    {
        if (hisi_battery_capacity() <= extchg_stop_threshold_powon)
        {
            ext_chg_status_new = RE_ILIM_STOP;
        }
        else
        {
            //do nothing
        }
    }
    else
    {
        if (hisi_battery_capacity() <= extchg_stop_threshold_powdown)
        {
            ext_chg_status_new = RE_ILIM_STOP;
            chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_LOWPOWER_STOP_CHARGING;
        }
        else
        {
            //do nothing
        }
    }
#endif
    if(FALSE == chg_is_ftm_mode())
    {
        schedule_delayed_work(&g_chip->extchg_monitor_work, msecs_to_jiffies(0));
    }

    return 0;
}


chg_chgr_type_t extchg_charger_type_detect(void)
{
    int ret = 0;

    gpio_direction_input(USB_GPIO_DM);
    gpio_direction_input(USB_GPIO_DP);
    mdelay(100);

    ret = gpio_get_value(USB_GPIO_DP);
    if (0 == ret)
    {
        chg_stm_set_chgr_type(CHG_USB_HOST_PC);
        return CHG_USB_HOST_PC;
    }
    else
    {
        gpio_direction_output(USB_GPIO_DM, 0);
        ret = gpio_get_value(USB_GPIO_DP);
        if (0 == ret)
        {
            chg_stm_set_chgr_type(CHG_WALL_CHGR);
            return CHG_WALL_CHGR;
        }
        else
        {
            chg_stm_set_chgr_type(CHG_NONSTD_CHGR);
            return CHG_NONSTD_CHGR;
        }
    }
}
#if defined(BSP_CONFIG_BOARD_E5771S_852)  || defined(BSP_CONFIG_BOARD_E5771H_937)

EXTCHG_ILIM ext_chg_limit_current_low_batt(int32_t bat_vol, int32_t batt_soc)
{
    static EXTCHG_ILIM ext_chg_status = RE_ILIM_2A;
    static EXTCHG_ILIM ext_chg_status_prev = RE_ILIM_2A;

    if(batt_soc > EXTCHG_STOP_CAPACITY_FIFTY)
    {
        /*  ��������50����2A���ڳ���λ��1A  */
        if(FALSE == is_chg_charger_removed())
        {
             ext_chg_status = RE_ILIM_1A;
        }
        else
        {
            ext_chg_status = RE_ILIM_2A;
        }   
    }
    else if((batt_soc <= EXTCHG_STOP_CAPACITY_FIFTY) && (batt_soc > EXTCHG_STOP_CAPACITY_TWENTYFIVE))
    {
        /*  ������[50,25),����1A  */
        ext_chg_status = RE_ILIM_1A;
    }
    else
    {  /*  ������[25,0),����500mA  */
        ext_chg_status = RE_ILIM_500mA;
    }

    /*  ��Թػ��ŵ���ͣ��͸��䴦��  */
    if (TRUE == chg_is_powdown_charging())
    {
        chg_print_level_message(CHG_MSG_INFO, "EXTCHG:is in pd charge!\n ");
    #if defined(BSP_CONFIG_BOARD_E5771H_937)  /*937�ػ�����ֹͣ���������޸�Ϊ2.94V����߶�����Ч��*/
        if(bat_vol < BATT_VOLTAGE_2940)
    #else
        if(bat_vol < BATT_VOLTAGE_3100)
    #endif
        {
            ext_chg_status = RE_ILIM_STOP;
        }
        else if((ext_chg_status_prev == RE_ILIM_STOP) && (batt_soc <= EXTCHG_STOP_CAPACITY_TEN))
        {
            ext_chg_status = RE_ILIM_STOP;
        }
        else if((ext_chg_status_prev == RE_ILIM_STOP) && (batt_soc > EXTCHG_STOP_CAPACITY_TEN))
        {
            ext_chg_status = RE_ILIM_500mA;
        } 
        else
        {
            /* nothing */
        }
    }

    ext_chg_status_prev = ext_chg_status;
    chg_print_level_message(CHG_MSG_INFO, "ext_limit_batt ->status = %d,soc=%d,volt=%d\n",\
        ext_chg_status,batt_soc,bat_vol);
    return ext_chg_status;
}


EXTCHG_ILIM ext_chg_limit_current_temp(int32_t bat_temp)
{
    static EXTCHG_TEMP_ILIM ext_chg_status = TEMP_ILIM_2A;
    static EXTCHG_TEMP_ILIM ext_chg_status_pre = TEMP_ILIM_2A;
    if (bat_temp < EXTCHG_LOW_TEMP_SHUTOFF_THRESHOLD)  
    { /*  < -20 */
        ext_chg_status = LOWTEMP_ILIM_STOP;
    }
    else if ((bat_temp >= EXTCHG_LOW_TEMP_SHUTOFF_THRESHOLD) \     
        && (bat_temp < EXTCHG_LOW_TEMP_SHUT_RESUM_THRSHOLD))
    {    /* [-20,-17)*/
        switch(ext_chg_status_pre){
        case LOWTEMP_ILIM_STOP:
        case LOWTEMP_ILIM_1A:
            break;
        case TEMP_ILIM_2A:
        case OVERTEMP_ILIM_STOP:
        case OVERTEMP_ILIM_1A:
            ext_chg_status = LOWTEMP_ILIM_1A;
            break;
        default:
            break;
        }
    }
    else if ((bat_temp >= EXTCHG_LOW_TEMP_SHUT_RESUM_THRSHOLD) \
        && (bat_temp < EXTCHG_LOW_TEMP_STOP_THRESHOLD))
    {  /* [-17,0)*/
        ext_chg_status = LOWTEMP_ILIM_1A;
    }
    else if ((bat_temp >= EXTCHG_LOW_TEMP_STOP_THRESHOLD) \
        && (bat_temp < EXTCHG_LOW_TEMP_RESUME_THRESHOLD))
    {  /* [0,3)*/
        switch(ext_chg_status_pre){
        case LOWTEMP_ILIM_STOP:
        case LOWTEMP_ILIM_1A:
            ext_chg_status = LOWTEMP_ILIM_1A;
            break;
        case TEMP_ILIM_2A:
        case OVERTEMP_ILIM_STOP:
        case OVERTEMP_ILIM_1A:
            ext_chg_status = TEMP_ILIM_2A;
            break;
        default:
            break;
        }
    }
    else if ((bat_temp >= EXTCHG_LOW_TEMP_RESUME_THRESHOLD) \
        && (bat_temp <= EXTCHG_WARM_CHARGE_RESUME_THRESHOLD))
    { /* [3,52] */
        ext_chg_status = TEMP_ILIM_2A;
    }
    else if ((bat_temp >  EXTCHG_WARM_CHARGE_RESUME_THRESHOLD) \
        && (bat_temp < EXTCHG_WARM_CHARGE_LIMIT_THRESHOLD))
    {    /* (52,55)*/ 
        switch(ext_chg_status_pre){
        case LOWTEMP_ILIM_STOP:
        case LOWTEMP_ILIM_1A:
        case TEMP_ILIM_2A:
            ext_chg_status = TEMP_ILIM_2A;
            break;
        case OVERTEMP_ILIM_1A:
            ext_chg_status = OVERTEMP_ILIM_1A;
            break;
        case OVERTEMP_ILIM_STOP:    
            ext_chg_status = OVERTEMP_ILIM_STOP;
            break;
        default:
            break;
        }
    }
    else if ((bat_temp >= EXTCHG_WARM_CHARGE_LIMIT_THRESHOLD) \
        && (bat_temp < EXTCHG_OVER_TEMP_STOP_THRESHOLD))
    {   /* [55,61)*/ 
        switch(ext_chg_status_pre){
        case LOWTEMP_ILIM_STOP:
        case LOWTEMP_ILIM_1A:
        case TEMP_ILIM_2A:
        case OVERTEMP_ILIM_1A:
            ext_chg_status = OVERTEMP_ILIM_1A;
            break;   
        case OVERTEMP_ILIM_STOP:   
            ext_chg_status = OVERTEMP_ILIM_STOP;
            break;
        default:
            break;
        }    
    }
    else if (bat_temp >= EXTCHG_OVER_TEMP_STOP_THRESHOLD)
    {  /* [61,....)*/ 
        ext_chg_status = OVERTEMP_ILIM_STOP;
    }
    ext_chg_status_pre = ext_chg_status;
    if((ext_chg_status == OVERTEMP_ILIM_STOP) || (ext_chg_status == LOWTEMP_ILIM_STOP))
    {
        chg_print_level_message(CHG_MSG_INFO, "ext_limit_temp ->status = %d,temp = %d\n",\
            RE_ILIM_STOP,bat_temp);
        return RE_ILIM_STOP;
    }
    else if((ext_chg_status == OVERTEMP_ILIM_1A) || (ext_chg_status == LOWTEMP_ILIM_1A))
    {
        chg_print_level_message(CHG_MSG_INFO, "ext_limit_temp ->status = %d,temp = %d\n",\
            RE_ILIM_1A,bat_temp);
        return  RE_ILIM_1A;
    }
    else
    {  
        chg_print_level_message(CHG_MSG_INFO, "ext_limit_temp ->status = %d,temp = %d\n",\
            RE_ILIM_2A,bat_temp);
        return  RE_ILIM_2A;
    }   

}
#elif defined(BSP_CONFIG_BOARD_E5_E5770s) 
EXTCHG_ILIM ext_chg_limit_current_low_batt(int32_t bat_vol, int32_t batt_soc)
{
    static EXTCHG_ILIM ext_chg_status = RE_ILIM_2A;
    static EXTCHG_ILIM ext_chg_status_prev = RE_ILIM_2A;
    static boolean is_charging_status = FALSE;
    static boolean limit_flag = FALSE;
    static int32_t num_of_limit = 0;
    ext_chg_status_prev = ext_chg_status;

    if (FALSE == is_chg_charger_removed())
    {
        is_charging_status = TRUE;
        if ((bat_vol < BATT_VOLTAGE_3500) && (bat_vol >= BATT_VOLTAGE_3350))
        {
            if (FALSE == chg_is_powdown_charging())
            {
                ext_chg_status = RE_ILIM_500mA;
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extcharge turn to RE_ILIM_500mA in [3350 3400)!!\n");
            }
            else
            {
                ext_chg_status = RE_ILIM_1A;
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extcharge turn to RE_ILIM_1A in [3350 3400) in pd!!\n");
            }
        }
        else if (bat_vol < BATT_VOLTAGE_3350)
        {
            ext_chg_status = RE_ILIM_500mA;
            chg_print_level_message(CHG_MSG_DEBUG, \
                "EXTCHG: extcharge turn to RE_ILIM_500mA!!\n");
        }

#ifdef BSP_CONFIG_BOARD_E5_E5770s
        if (FALSE == chg_is_powdown_charging())
        {
            if (batt_soc <= extchg_stop_threshold_powon)
            {
                ext_chg_status = RE_ILIM_STOP;
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extcharge turn to RE_ILIM_STOP, SOC<=10!!\n");
            }
        }
        else
        {
            if (batt_soc <= extchg_stop_threshold_powdown)
            {
                ext_chg_status = RE_ILIM_STOP;
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extcharge turn to RE_ILIM_STOP, SOC<=10!!\n");
            }
        }
#endif

        if (ext_chg_status > ext_chg_status_prev)
        {
            ext_chg_status = ext_chg_status_prev;
        }

        if (batt_soc >= extchg_recharge_threshold)
        {
            ext_chg_status = RE_ILIM_1A;
            chg_print_level_message(CHG_MSG_DEBUG, \
                "EXTCHG: extcharge turn to RE_ILIM_1A up to 50%!!\n");
        }
        else
        {
            if (RE_ILIM_2A == ext_chg_status_prev)
            {
                ext_chg_status = RE_ILIM_1A;
            }
            else
            {
                //do nothing
            }
        }
    }
    else
    {
        if (TRUE == chg_is_powdown_charging())
        {
            if (TRUE == is_charging_status)
            {
                ext_chg_status_prev = RE_ILIM_2A;
                is_charging_status = FALSE;
            }
            if (bat_vol >= BATT_VOLTAGE_3350)
            {
                ext_chg_status = RE_ILIM_2A;
            }
            else if ((bat_vol >= BATT_VOLTAGE_3300) && (bat_vol < BATT_VOLTAGE_3350))
            {
                ext_chg_status = RE_ILIM_1A;
            }
            else if (bat_vol < BATT_VOLTAGE_3300)
            {
                ext_chg_status = RE_ILIM_500mA;
            }
        }
        else
        {
            if (TRUE == is_charging_status)
            {
                ext_chg_status_prev = RE_ILIM_2A;
                is_charging_status = FALSE;
            }
            if (bat_vol >= BATT_VOLTAGE_3600)
            {
                limit_flag = FALSE;
                num_of_limit = 0;
                if (RE_ILIM_2A == ext_chg_status_prev)
                {
                    ext_chg_status = RE_ILIM_2A;
                    chg_print_level_message(CHG_MSG_DEBUG, \
                        "EXTCHG: extcharge turn to RE_ILIM_2A in [3600 +00)!!\n");
                }
            }
            else if ((bat_vol < BATT_VOLTAGE_3600) && (bat_vol >= BATT_VOLTAGE_3350))
            {
                limit_flag = FALSE;
                num_of_limit = 0;
                if (batt_soc <= extchg_limit_1a_capacity)
                {
                    if (bat_vol >= BATT_VOLTAGE_3500)
                    {
                        if (RE_ILIM_2A == ext_chg_status_prev)
                        {
                            ext_chg_status = RE_ILIM_1A;
                            chg_print_level_message(CHG_MSG_DEBUG, \
                                "EXTCHG: extcharge turn to RE_ILIM_1A in [3500 +00)!!\n");
                        }
                    }
                    else
                    {
                        if (batt_soc <= extchg_limit_500ma_capacity)
                        {
                            if (ext_chg_status_prev > RE_ILIM_500mA)
                            {
                                ext_chg_status = RE_ILIM_500mA;
                                chg_print_level_message(CHG_MSG_DEBUG, \
                                    "EXTCHG: extcharge turn to RE_ILIM_500mA!!\n");
                            }
                        }
                    }
                }
            }
            else if (bat_vol < BATT_VOLTAGE_3350)
            {
                if (limit_flag != TRUE)
                {
                    limit_flag = TRUE;
                    if (RE_ILIM_2A == ext_chg_status_prev)
                    {
                        ext_chg_status = RE_ILIM_1A;
                        chg_print_level_message(CHG_MSG_DEBUG, \
                            "EXTCHG: extcharge turn to RE_ILIM_1A from RE_ILIM_2A!!\n");
                    }
                    else if (RE_ILIM_1A == ext_chg_status_prev)
                    {
                        ext_chg_status = RE_ILIM_500mA;
                        chg_print_level_message(CHG_MSG_DEBUG, \
                            "EXTCHG: extcharge turn to RE_ILIM_500mA from RE_ILIM_1A!!\n");
                    }
                    else if (RE_ILIM_500mA == ext_chg_status_prev)
                    {
                        if (FALSE == chg_is_powdown_charging())
                        {
#ifdef BSP_CONFIG_BOARD_E5_E5770s
                            if (batt_soc <= extchg_stop_threshold_powon)
                            {
                                ext_chg_status = RE_ILIM_STOP;
                                chg_print_level_message(CHG_MSG_DEBUG, \
                                    "EXTCHG: extcharge turn to RE_ILIM_STOP SOC<=10!!\n");
                            }
#endif
                        }
                    }
                    else
                    {
                        //do nothing
                    }
                }
                else
                {
                    num_of_limit++;

                    if (num_of_limit > NUM_OF_LIMIT)
                    {
                        if (RE_ILIM_1A == ext_chg_status_prev)
                        {
                            ext_chg_status = RE_ILIM_500mA;
                            chg_print_level_message(CHG_MSG_DEBUG, \
                                "EXTCHG: extcharge turn to RE_ILIM_500mA cotinuously!!\n");
                        }
                        else if (RE_ILIM_500mA == ext_chg_status_prev)
                        {
                            if (FALSE == chg_is_powdown_charging())
                            {
#ifdef BSP_CONFIG_BOARD_E5_E5770s
                                if (batt_soc <= extchg_stop_threshold_powon)
                                {
                                    ext_chg_status = RE_ILIM_STOP;
                                    chg_print_level_message(CHG_MSG_DEBUG, \
                                        "EXTCHG: extcharge turn to STOP cotinuously!!\n");
                                }
#endif
                            }
                        }
                        else
                        {
                            //do nothing
                        }
                    }
                }
            }
        }
#ifdef BSP_CONFIG_BOARD_E5_E5770s
        if (FALSE == chg_is_powdown_charging())
        {
            if (batt_soc <= extchg_stop_threshold_powon)
            {
                ext_chg_status = RE_ILIM_STOP;
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extcharge turn to RE_ILIM_STOP SOC<=10!!\n");
            }
        }
        else
        {
            if (batt_soc <= extchg_stop_threshold_powdown)
            {
                ext_chg_status = RE_ILIM_STOP;
                chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_LOWPOWER_STOP_CHARGING;
                chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY, (uint32_t)CHG_EVENT_NONEED_CARE);
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extcharge turn to RE_ILIM_STOP SOC<=2!!\n");
            }
        }
#endif

        if (ext_chg_status > ext_chg_status_prev)
        {
            ext_chg_status = ext_chg_status_prev;
        }
    }
#ifdef BSP_CONFIG_BOARD_E5_E5770s
    if ((RE_ILIM_STOP == ext_chg_status_prev) && (RE_ILIM_STOP != ext_chg_status))
    {
        chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_UNKNOWN;
    }
#endif
    ext_chg_status_prev = ext_chg_status;
    return ext_chg_status;
}


EXTCHG_ILIM ext_chg_limit_current_temp(int32_t bat_temp)
{
    static EXTCHG_ILIM ext_chg_status = RE_ILIM_2A;
    static boolean over_temp_flag = FALSE;

    if (bat_temp <= EXTCHG_LOW_TEMP_SHUTOFF_THRESHOLD)
    {
        ext_chg_status = RE_ILIM_STOP;
        chg_print_level_message(CHG_MSG_DEBUG, \
            "EXTCHG: extcharge turn to RE_ILIM_STOP, bat_temp=%d!!\n", bat_temp);
    }
    else if ((bat_temp >= EXTCHG_LOW_TEMP_SHUTOFF_THRESHOLD) \
        && (bat_temp < EXTCHG_LOW_TEMP_SHUT_RESUM_THRSHOLD))
    {
        chg_print_level_message(CHG_MSG_DEBUG, \
            "EXTCHG: extcharge remaining, bat_temp=%d!!\n", bat_temp);
    }
    else if ((bat_temp >= EXTCHG_LOW_TEMP_SHUT_RESUM_THRSHOLD) \
		&& (bat_temp < EXTCHG_LOW_TEMP_STOP_THRESHOLD))
    {
        ext_chg_status = RE_ILIM_1A;
        chg_print_level_message(CHG_MSG_DEBUG, \
            "EXTCHG: extcharge turn to RE_ILIM_1A, bat_temp=%d!!\n", bat_temp);
    }
    else if ((bat_temp >= EXTCHG_LOW_TEMP_STOP_THRESHOLD) \
        && (bat_temp < EXTCHG_LOW_TEMP_RESUME_THRESHOLD))
    {
        chg_print_level_message(CHG_MSG_DEBUG, \
            "EXTCHG: extcharge remaining, bat_temp=%d!!\n", bat_temp);
    }
    else if ((bat_temp >= EXTCHG_LOW_TEMP_RESUME_THRESHOLD) \
        && (bat_temp < EXTCHG_WARM_CHARGE_RESUME_THRESHOLD))
    {
        if (FALSE == is_chg_charger_removed())
        {
            ext_chg_status = RE_ILIM_1A;
            chg_print_level_message(CHG_MSG_DEBUG, \
                "EXTCHG: extcharge turn to RE_ILIM_1A, \
                    bat_temp=%d!!\n", bat_temp);
        }
        else
        {
            ext_chg_status = RE_ILIM_2A;
            chg_print_level_message(CHG_MSG_DEBUG, \
                "EXTCHG: extcharge turn to RE_ILIM_2A, \
                    bat_temp=%d!!\n", bat_temp);
        }
    }
    else if ((bat_temp >= EXTCHG_WARM_CHARGE_RESUME_THRESHOLD) \
        && (bat_temp < EXTCHG_WARM_CHARGE_LIMIT_THRESHOLD))
    {
        if (TRUE == over_temp_flag)
        {
            ext_chg_status = RE_ILIM_500mA;
            over_temp_flag = FALSE;
            chg_print_level_message(CHG_MSG_DEBUG, \
                "EXTCHG: extcharge turn to EXTCHG_WARM_ST, \
                    bat_temp=%d!!\n", bat_temp);

        }
    }
    else if ((bat_temp >= EXTCHG_WARM_CHARGE_LIMIT_THRESHOLD) \
        && (bat_temp < EXTCHG_OVER_TEMP_STOP_THRESHOLD))
    {
        if (TRUE == over_temp_flag)
        {
            ext_chg_status = RE_ILIM_STOP;
        }
        else
        {
            ext_chg_status = RE_ILIM_500mA;
        }
    }
    else if (bat_temp >= EXTCHG_OVER_TEMP_STOP_THRESHOLD)
    {
        ext_chg_status = RE_ILIM_STOP;
        over_temp_flag = TRUE;
        chg_print_level_message(CHG_MSG_DEBUG, \
            "EXTCHG: extcharge turn to EXTCHG_OVERTEMP_ST, \
                bat_temp=%d!!\n", bat_temp);
    }
    else
    {
        //do nothing
    }

    if ((hisi_battery_temperature() > EXTCHG_EXTREME_HIGH_TEMP) \
        && (RE_ILIM_STOP != ext_chg_status))
    {
        ext_chg_status = RE_ILIM_500mA;
        chg_print_level_message(CHG_MSG_ERR, \
            "EXTCHG: TEMP HIGHER THAN 77, ILIM TO 500MA, \
                bat_temp=%d!!\n", bat_temp);
    }

    return ext_chg_status;
}
#else
EXTCHG_ILIM ext_chg_limit_current_low_batt(int32_t bat_vol, int32_t batt_soc)
{
    static EXTCHG_ILIM ext_chg_status = RE_ILIM_2A;
    return ext_chg_status;
}
EXTCHG_ILIM ext_chg_limit_current_temp(int32_t bat_temp)
{
    static EXTCHG_ILIM ext_chg_status = RE_ILIM_2A;
    return ext_chg_status;
}
#endif

boolean extchg_monitor_func_in_sleep_mode(int32_t bat_vol, int32_t bat_temp)
{
    boolean need_to_change_timer = FALSE;
    int32_t batt_soc = chg_get_sys_batt_capacity();

    count_for_short_det = 0;
    poll_round_for_det = 0;

    if (TRUE == extchg_short_flag)
    {
        return FALSE;
    }
    if ((RE_ILIM_STOP != ext_chg_status_new) && (TRUE != usb_set_direction_flag))
    {
        if (extchg_is_perph_circult_short())
        {
            ext_chg_status_new = RE_ILIM_STOP;
            extchg_short_flag = TRUE;
            extchg_set_charge_enable(FALSE);
            chg_print_level_message(CHG_MSG_ERR, \
                "EXTCHG: extcharge circult is short in sleep mode, \
                    and extcharge is short protected!!\n");
            return FALSE;
        }
    }

    ext_chg_status_new = ext_chg_limit_current_low_batt(battery_voltage, batt_soc);
    ext_chg_status_temp = ext_chg_status_new;
    ext_chg_status_new = ext_chg_limit_current_temp(battery_temperature);
    ext_chg_status_new = (ext_chg_status_temp < ext_chg_status_new) \
        ? ext_chg_status_temp : ext_chg_status_new;

    if (ext_chg_status_old != ext_chg_status_new)
    {
        ext_chg_status_old = ext_chg_status_new;
        switch(ext_chg_status_new)
        {
            case RE_ILIM_STOP:
                extchg_set_charge_enable(FALSE);
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extchg_set_charge_enable(FALSE)!!\n");
                break;
            case RE_ILIM_2A:
                extchg_set_cur_level(RE_ILIM_2A);
                extchg_set_charge_enable(TRUE);
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extchg_set_cur_level(RE_ILIM_2A)!!\n");
                break;
            case RE_ILIM_1A:
                extchg_set_cur_level(RE_ILIM_1A);
                extchg_set_charge_enable(TRUE);
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extchg_set_cur_level(RE_ILIM_1A)!!\n");
                break;
            case RE_ILIM_500mA:
#if defined(BSP_CONFIG_BOARD_E5771H_937)
                gpio_direction_output(RE_ILIM_1A_GPIO, 1);
                extchg_set_charge_enable(TRUE);
                extchg_set_cur_level(RE_ILIM_500mA);
#else
                extchg_set_cur_level(RE_ILIM_500mA);
                extchg_set_charge_enable(TRUE);
#endif
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extchg_set_cur_level(RE_ILIM_500mA)!!\n");
                break;
        }
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, \
            "EXTCHG: extcharge status not change, do nothing!!\n");
    }
    if ((battery_temperature >= EXTCHG_WARM_CHARGE_LIMIT_THRESHOLD) \
        || (batt_soc < EXTCHG_STOP_CAPACITY_TWENTY))
    {
        need_to_change_timer = TRUE;
    }
    else
    {
        need_to_change_timer = FALSE;
    }

    return need_to_change_timer;
}
#endif


void chg_extchg_insert_proc(void)
{
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    wake_lock_timeout(&g_chip->alarm_wake_lock,
        (long)msecs_to_jiffies(ALARM_REPORT_WAKELOCK_TIMEOUT));
    mdelay(DELAY_TIME_OF_DEBOUNCE);
    if (1 == gpio_get_value(EXTCHG_OTG_DET_GPIO))
    {
        return;
    }

    chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:CHG_EXGCHG_CHGR PLUG IN!\n ");

    if ((TRUE == extchg_short_flag) || \
        (chg_stm_state_info.extchg_status == POWER_SUPPLY_EXTCHGSTA_STOP_FAULT))
    {
        extchg_short_flag = FALSE;
        chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_UNKNOWN;
        extchg_set_charge_enable(TRUE);
        schedule_delayed_work(&g_chip->extchg_monitor_work, msecs_to_jiffies(0));
    }
    g_exchg_online_flag = ONLINE;
    chg_stm_set_extchg_online_st(TRUE);
    chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY, (uint32_t)CHG_EVENT_NONEED_CARE);
#else
    if(TRUE == is_5577cs_falg)
    {
        return;
    }
    CHG_MODE_ENUM cur_chg_mode = chg_get_cur_chg_mode();

    chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:CHG_EXGCHG_CHGR PLUG IN!\n ");
    if(OFFLINE == g_exchg_online_flag)
    {
        g_exchg_online_flag = ONLINE;
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:disable extchg,do nothing!\n");
        return;
    }
    /*���UI�������ý�ֹ������˴�����USB ID �����ж�*/
    if(1 == g_extchg_diable_st)
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:disable extchg,do nothing!\n");
        return;
    }
    /*���߳�糡��������������¼�*/
    if(CHG_WIRELESS_MODE == cur_chg_mode)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:chg_mode in CHG_WIRELESS_MODE,do nothing!\n ");
        return;
    }

    chg_stm_set_extchg_online_st(TRUE);
    chg_set_cur_chg_mode(CHG_EXTCHG_MODE);
    //TO DO:1:����USB�����ӿڶ̽�D+ ,D-
    usb_notify_event(USB_OTG_CONNECT_DP_DM,NULL);
    chg_send_stat_to_app((uint32_t)DEVICE_ID_EXTCHG, (uint32_t)CHG_EVENT_NONEED_CARE);
#if ( FEATURE_ON == MBB_MLOG )
    printk(KERN_ERR, "CHG_STM:otg_charge_count\n");
    mlog_set_statis_info("otg_charge_count",1);//�������ܴ��� ��1
#endif        
    /*������������work*/
    //is_vbus_unkonwn����
    is_vbus_unkonwn = FALSE;
    if(NULL != g_chip)
    {
        schedule_delayed_work(&g_chip->extchg_monitor_work, msecs_to_jiffies(0));
    }
#endif
}

void chg_extchg_remove_proc(void)
{
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    int count = 0;
#if defined(BSP_CONFIG_BOARD_E5771S_852) || defined(BSP_CONFIG_BOARD_E5771H_937) 
    wake_lock_timeout(&g_chip->alarm_wake_lock,
        (long)msecs_to_jiffies(ALARM_REPORT_WAKELOCK_TIMEOUT));
#else
    wake_lock_timeout(&g_chip->alarm_wake_lock,
        (long)msecs_to_jiffies(SHUTDOWN_WAKELOCK_TIMEOUT));
#endif
    count_for_short_det = 0;
    poll_round_for_det = 0;
    mdelay(DELAY_TIME_OF_DEBOUNCE);
    if (0 == gpio_get_value(EXTCHG_OTG_DET_GPIO))
    {
        return;
    }

    chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:CHG_EXGCHG_CHGR PLUG OUT!\n ");

    if ((TRUE == extchg_short_flag) || \
        (chg_stm_state_info.extchg_status == POWER_SUPPLY_EXTCHGSTA_STOP_FAULT))
    {
        extchg_short_flag = FALSE;
        chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_UNKNOWN;
        extchg_set_charge_enable(TRUE);
        schedule_delayed_work(&g_chip->extchg_monitor_work, msecs_to_jiffies(0));
    }

    g_exchg_online_flag = OFFLINE;
    chg_stm_set_extchg_online_st(FALSE);
    chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY, (uint32_t)CHG_EVENT_NONEED_CARE);

    if (TRUE == chg_is_powdown_charging())
    {
        for(count = 0; count <= 1; count++)
        {
            chg_detect_batt_chg_for_shutoff();
        }
    }
#else
    if(ONLINE == g_exchg_online_flag)
    {
        g_exchg_online_flag = OFFLINE;
    }
    else
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:disable extchg,do nothing!\n");
        return;
    }
    chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:CHG_EXGCHG_CHGR PLUG OUT!\n ");
    /*��ֹ���е�work*/
    cancel_delayed_work_sync(&g_chip->extchg_monitor_work);

    /*������USB ID�߰γ����¶Ȳ����ı�־λ���*/
    g_ui_choose_exchg_mode = 0;
    g_last_extchg_diable_st = 0;
    is_otg_extchg = FALSE;
    is_extchg_ovtemp = FALSE;
    chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_UNKNOWN;
    chg_set_extchg_chg_enable(FALSE);
    chg_stm_set_extchg_online_st(FALSE);
    chg_send_stat_to_app((uint32_t)DEVICE_ID_EXTCHG,(uint32_t)CHG_EVENT_NONEED_CARE);
#endif
}

void chg_extchg_monitor_func(void)
{
    int32_t bat_temp = chg_get_sys_batt_temp();
    int32_t bat_vol = chg_get_sys_batt_volt();
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
    int32_t batt_soc = chg_get_sys_batt_capacity();
#endif

#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    //��·����
    if (TRUE == extchg_short_flag)
    {
        if (TIME_OF_SHORT_DET == count_for_short_det)
        {
            extchg_set_charge_enable(TRUE);
            mdelay(50);
            if (extchg_is_perph_circult_short())
            {
                extchg_set_charge_enable(FALSE);
                count_for_short_det = 0;
                count_for_short_det++;
                poll_round_for_det++;
            }
            else
            {
                ext_chg_status_new = RE_ILIM_2A;
                extchg_short_flag = FALSE;
                count_for_short_det = 0;
                poll_round_for_det = 0;
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extcharge is not short anymore!\n");
                bsp_softtimer_add(&g_chg_sleep_timer);
                wake_unlock(&g_chip->alarm_wake_lock);
                goto out;
            }
        }
        else
        {
            count_for_short_det++;
        }
        if (NUM_OF_SHORT_DET_POLL == poll_round_for_det)
        {
            poll_round_for_det = 0;
            count_for_short_det = 0;
            count_for_short_det++;
            #if !defined(BSP_CONFIG_BOARD_E5771S_852) && !defined(BSP_CONFIG_BOARD_E5771H_937)
            chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_STOP_FAULT;
            chg_send_stat_to_app((uint32_t)DEVICE_ID_BATTERY, \
                (uint32_t)CHG_EVENT_NONEED_CARE);
            mdelay(ALARM_REPORT_WAKELOCK_TIMEOUT);
            #endif
            chg_print_level_message(CHG_MSG_ERR, \
                "EXTCHG: extcharge is short protected!!!\n");
            bsp_softtimer_add(&g_chg_sleep_timer);
            wake_unlock(&g_chip->alarm_wake_lock);
            return;
        }
        goto out;
    }
    else
    {
        if ((RE_ILIM_STOP != ext_chg_status_new) && (TRUE != usb_set_direction_flag))
        {
            if (extchg_is_perph_circult_short())
            {
                wake_lock(&g_chip->alarm_wake_lock);
                bsp_softtimer_delete(&g_chg_sleep_timer);
                extchg_set_charge_enable(FALSE);
                ext_chg_status_new = RE_ILIM_STOP;
                extchg_short_flag = TRUE;
                count_for_short_det++;
                chg_print_level_message(CHG_MSG_ERR, \
                    "EXTCHG: extcharge circult is short!!\n");
                goto out;
            }
        }
    }

    ext_chg_status_new = ext_chg_limit_current_low_batt(bat_vol, batt_soc);
    ext_chg_status_temp = ext_chg_status_new;
    ext_chg_status_new = ext_chg_limit_current_temp(bat_temp);

    ext_chg_status_new = (ext_chg_status_temp < ext_chg_status_new) \
        ? ext_chg_status_temp : ext_chg_status_new;

    if (ext_chg_status_old != ext_chg_status_new)
    {
        ext_chg_status_old = ext_chg_status_new;
        switch(ext_chg_status_new)
        {
            case RE_ILIM_STOP:
                extchg_set_charge_enable(FALSE);
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extchg_set_charge_enable(FALSE)!!\n");
                break;
            case RE_ILIM_2A:
                extchg_set_cur_level(RE_ILIM_2A);
                extchg_set_charge_enable(TRUE);
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extchg_set_cur_level(RE_ILIM_2A)!!\n");
                break;
            case RE_ILIM_1A:
                extchg_set_cur_level(RE_ILIM_1A);
                extchg_set_charge_enable(TRUE);
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extchg_set_cur_level(RE_ILIM_1A)!!\n");
                break;
            case RE_ILIM_500mA:
                extchg_set_cur_level(RE_ILIM_500mA);
                extchg_set_charge_enable(TRUE);
                chg_print_level_message(CHG_MSG_DEBUG, \
                    "EXTCHG: extchg_set_cur_level(RE_ILIM_500mA)!!\n");
                break;
        }
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, \
            "EXTCHG: extcharge status not change, do nothing!!\n");
    }
out:
    //chg_extchg_info_dump();
    chg_print_test_view_info();
    ext_chg_info_dump();

    schedule_delayed_work(&g_chip->extchg_monitor_work, msecs_to_jiffies(2000));

    return;
#else
    if(OFFLINE == g_exchg_online_flag)
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_PLT:extchg device not exit,do nothing!\n");
        return;
    }
    /*����UI����*/
    chg_extchg_config_data_init();
    /*״̬���*/
#if defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577S_932) \
    || defined(BSP_CONFIG_BOARD_E5577S_324)|| defined(BSP_CONFIG_BOARD_E5577BS_937)
    /*�������·����봦��*/
    if(TRUE == g_exchg_enable_flag)
    {
        if(TRUE == extchg_circult_short_detect())
        {
            if(TRUE == is_vbus_unkonwn)
            {
                chg_set_extchg_chg_enable(FALSE);
                chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_STOP_FAULT;
                is_vbus_unkonwn = FALSE;
                /*֪ͨӦ�ò��������������ֹͣ������*/
                chg_send_stat_to_app((uint32_t)DEVICE_ID_EXTCHG,(uint32_t)CHG_EVENT_NONEED_CARE);
                chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:STOP EXTGHG!\n");
                return;
            }
            else
            {
            is_vbus_unkonwn = TRUE;
            }
        }
        else
        {
            is_vbus_unkonwn = FALSE;
        }
    }
#endif
    /*��������������Ϊ��OTGģʽ����ͨ��5V���µ�reset usbģ��*/
    if(TRUE == chg_extchg_ocp_detect())
    {
        chg_print_level_message(CHG_MSG_ERR, "CHG_STM:EXTCHG OCP happened is_otg_extchg=%d!\n",
            is_otg_extchg);

        if(FALSE == is_otg_extchg)
        {
           /*�����оƬ����Ϊ ��OTGģʽ��5V �µ�*/
           chg_set_charge_otg_enable(FALSE);
           /*��ʱ500MS*/
           chg_delay_ms(EXTCHG_DELAY_COUNTER_SIZE);
           //TO DO:����USB�����ӿ�ֱ������������HS_ID��
           usb_notify_event(USB_OTG_DISCONNECT_DP_DM,NULL);
           /*��ʱ500MS*/
           chg_delay_ms(EXTCHG_DELAY_COUNTER_SIZE);
          /*�����оƬ����ΪOTGģʽ5V�ϵ�*/
           chg_set_charge_otg_enable(TRUE);
           /*���˶������л�ΪOTG 500MA���ģʽ*/
           is_otg_extchg = TRUE;
           chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:1A EXTCHG OCP change to USB OTG 500MA!\n");
            
        }
        /*���ΪOTGģʽ��⵽����ֱ��ֹͣ������*/
        else
        {
            chg_set_extchg_chg_enable(FALSE);
            chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_STOP_FAULT;
            /*֪ͨӦ�ò��������������ֹͣ������*/
            chg_send_stat_to_app((uint32_t)DEVICE_ID_EXTCHG,(uint32_t)CHG_EVENT_NONEED_CARE);
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:USB OTG 500MA EXTCHG OCP STOP EXTGHG!\n");
        }
    }
    /*��ع���ֹͣ������*/    
    #if defined(BSP_CONFIG_BOARD_E5577S_932) || defined(BSP_CONFIG_BOARD_E5577S_321) \
   || defined(BSP_CONFIG_BOARD_E5577S_324)|| defined(BSP_CONFIG_BOARD_E5577BS_937)
     else if((bat_temp >= EXTCHG_OVER_TEMP_STOP_THRESHOLD) || (bat_temp <= EXTCHG_LOW_TEMP_STOP_THRESHOLD))
    #else
     else if(bat_temp >= EXTCHG_OVER_TEMP_STOP_THRESHOLD)
    #endif
    {
        /*����ֹͣ������*/
        chg_set_extchg_chg_enable(FALSE);
        is_extchg_ovtemp = TRUE;

        chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_OVERHEAT_STOP_CHARGING;
        /*֪ͨӦ���¶��쳣ֹͣ������*/
        chg_send_stat_to_app((uint32_t)DEVICE_ID_EXTCHG,(uint32_t)CHG_EVENT_NONEED_CARE);

        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:EXTCHG OVER TEMP STOP EXTGHG!\n");
    }
    /*����¶Ȼָ�ʹ�ܶ�����*/
    #if defined(BSP_CONFIG_BOARD_E5577S_932) || defined(BSP_CONFIG_BOARD_E5577S_321) \
    || defined(BSP_CONFIG_BOARD_E5577S_324) || defined(BSP_CONFIG_BOARD_E5577BS_937)
    else if(((bat_temp <= EXTCHG_OVER_TEMP_RESUME_THRESHOLD) && (bat_temp >= EXTCHG_LOW_TEMP_RESUME_THRESHOLD)) \
            && (TRUE == is_extchg_ovtemp))
    #else
    else if((bat_temp <= EXTCHG_OVER_TEMP_RESUME_THRESHOLD) && (TRUE == is_extchg_ovtemp))
    #endif
    {
        chg_set_extchg_chg_enable(TRUE);
        is_extchg_ovtemp = FALSE;
        chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_START_CHARGING;
        /*�¶Ȼָ�����֪ͨӦ�ÿ�ʼ������*/
        chg_send_stat_to_app((uint32_t)DEVICE_ID_EXTCHG,(uint32_t)CHG_EVENT_NONEED_CARE);
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:EXTCHG TEMP NORMAL RESUME EXTGHG!\n");
    }
   /*��ص͵�ֹͣ������*/
#if (MBB_CHG_COULOMETER == FEATURE_ON || MBB_CHG_BQ27510 == FEATURE_ON)
    else if(batt_soc <= g_extchg_stop_soc_threshold)
#else
    else if(bat_vol <= g_extchg_voltage_threshold)
#endif
    {
        chg_set_extchg_chg_enable(FALSE);
        chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_LOWPOWER_STOP_CHARGING;
        /*֪ͨӦ�õ͵�ֹͣ������*/
        chg_send_stat_to_app((uint32_t)DEVICE_ID_EXTCHG,(uint32_t)CHG_EVENT_NONEED_CARE);
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:EXTCHG LOW VOLTAGE STOP EXTGHG!\n");
    }
    /*���ڶ���������������⵽�û�ͨ��TOUCH UI��������ֹͣ��������ֱ��ֹͣ������*/
    else if((1 == g_extchg_diable_st) && (0 == g_last_extchg_diable_st))
    {
        g_last_extchg_diable_st = 1;
        chg_set_extchg_chg_enable(FALSE);
        chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_STOP_FAULT;
        chg_send_stat_to_app((uint32_t)DEVICE_ID_EXTCHG,(uint32_t)CHG_EVENT_NONEED_CARE);
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:UI set disable extchg permanently!\n");
    }
    /*���ڶ���������������⵽�û�ͨ��TOUCH UI��������ֹͣ��������ֱ��ֹͣ�������
       ����û������ô�*/
    else if((0 == g_extchg_diable_st) && (1 == g_last_extchg_diable_st))
    {
        g_last_extchg_diable_st = 0;
        /*����ʹ�ܺ�STA�ڵ�״̬��ΪUNKNOWN,��ѡ��򵯳������û�ѡ�������Ƿ������*/
        chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_UNKNOWN;
        chg_send_stat_to_app((uint32_t)DEVICE_ID_EXTCHG,(uint32_t)CHG_EVENT_NONEED_CARE);
        chg_print_level_message(CHG_MSG_INFO, "CHG_STM:UI set enable extchg permanently!\n");
    }
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:staying at extchg_state !\n");
    }
    chg_extchg_info_dump();

    schedule_delayed_work(&g_chip->extchg_monitor_work, msecs_to_jiffies(2000));
#endif
}


#endif

/**********************************************************************
FUNCTION:    chg_charger_insert_proc
DESCRIPTION: usb remove process
INPUT:       chg_chgr_type_t chg_type
OUTPUT:      None.
RETURN:      None.
NOTE:        None
***********************************************************************/
void chg_charger_insert_proc(chg_chgr_type_t chg_type)
{
    chg_stm_state_type cur_stat = chg_stm_get_cur_state();
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    chg_chgr_type_t charge_type = CHG_CHGR_UNKNOWN;
#endif
    /*USB����*/
    if(CHG_USB_HOST_PC == chg_type)
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:CHG_USB_HOST_PC PLUG IN force to TRANSIT_ST!\n ");
        if(FALSE == chg_get_usb_online_status())
        {
            chg_set_ac_online_status(FALSE);
            chg_set_usb_online_status(TRUE);
            chg_send_stat_to_app((uint32_t)DEVICE_ID_USB, (uint32_t)CHG_EVENT_NONEED_CARE);
        }
        chg_stm_set_chgr_type(CHG_USB_HOST_PC);
        chg_set_cur_chg_mode(CHG_WIRED_MODE);
        if((CHG_STM_INIT_ST >= cur_stat) || (CHG_STM_MAX_ST <= cur_stat)
            || (CHG_STM_BATTERY_ONLY == cur_stat) || (CHG_STM_TRANSIT_ST == cur_stat))
        {
            chg_stm_switch_state(CHG_STM_TRANSIT_ST);
        }

#if (MBB_CHG_WIRELESS == FEATURE_ON)
        if(TRUE == chg_stm_get_wireless_online_st())
        {
            /*USB��������߳������λ��ONLINE�ڵ���ΪOFFLINE����ֹ���߳��
                �����в��������豸��ONLINE�ڵ�û�������ʾ���߳��ͼ��*/
            chg_stm_set_wireless_online_st(FALSE);
            chg_stm_switch_state(CHG_STM_TRANSIT_ST);
        }
#endif /*defined(MBB_CHG_WIRELESS)*/
#if ( FEATURE_ON == MBB_MLOG )
            chg_print_level_message(CHG_MSG_ERR, "usb2.0 charger insert!\n ");
            /*usb2.0���룬����һ��*/
            mlog_set_statis_info("usb2_charge_insert_count",1);
    
#endif
        return ;
    }
    /*������*/
    else if(CHG_WALL_CHGR == chg_type || CHG_USB_OTG_CRADLE == chg_type)
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:CHG_WALL_CHGR PLUG IN force to TRANSIT_ST!\n ");
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
#if (FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
        if (usb_get_switch_direction())
        {
#endif
            /*��������Ʒ�ϣ�ƻ��������Ե����磬�ᱻʶ����Ի������Ե������λʱ���Ž����Ի��ж�����*/
            if(0 == gpio_get_value(EXTCHG_OTG_DET_GPIO))
            {
                gpio_direction_output(GPIO_USB_SELECT, USB_SWITCH_APORT_LEVEL);
                mdelay(DELAY_TIME_20MS);
                charge_type = extchg_charger_type_detect();
                if (charge_type == CHG_NONSTD_CHGR)
                {
                    if (TRUE == chg_is_charger_present())
                    {
                        if (g_exchg_online_flag == ONLINE)
                        {
                        
                            cancel_delayed_work_sync(&g_chip->extchg_monitor_work);
                            chg_stm_state_info.extchg_status = \
                                POWER_SUPPLY_EXTCHGSTA_STOP_FAULT;
                            chg_send_stat_to_app((uint32_t)DEVICE_ID_CHARGER, \
                                (uint32_t)CHG_EVENT_NONEED_CARE);
                        #if defined(BSP_CONFIG_BOARD_E5771H_937)
                            usb_err_flag = TRUE;
                            chg_set_supply_limit(CHG_IINPUT_LIMIT_100MA);
                       #else
                            extchg_set_charge_enable(FALSE);
                       #endif
                            chg_print_level_message(CHG_MSG_ERR, \
                                "CHG_PLT:CHARGING TO ITSELF, STOP CHARGING!\n ");
                        }
                        else
                        {
                            usb_err_flag = TRUE;
                            chg_stm_set_extchg_online_st(TRUE);
                            chg_set_supply_limit(CHG_IINPUT_LIMIT_100MA);
                            chg_stm_state_info.extchg_status = \
                                POWER_SUPPLY_EXTCHGSTA_STOP_FAULT;
                            chg_send_stat_to_app((uint32_t)DEVICE_ID_CHARGER, \
                                (uint32_t)CHG_EVENT_NONEED_CARE);
                            chg_print_level_message(CHG_MSG_ERR, \
                                "CHG_PLT:CHARGING TO ITSELF, LIMIT CHARGING!\n ");
                        }
                    }
                }
                gpio_direction_output(GPIO_USB_SELECT,USB_SWITCH_MPORT_LEVEL);
            }
#if (FEATURE_ON == MBB_USB_A_TO_MINI_SELECT)
        }
#endif
#endif
        /*AF18 ��������DPM��ѹֵ*/
        if(CHG_USB_OTG_CRADLE == chg_type)
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:AF18 PLUG IN set Dpm.\n ");
            chg_set_dpm_val(CHG_AF18_DPM_VOLT);
        }
        /*�����⵽����������Ǳ��ͽ� USB ����ΪOFFINE,��AC����ΪONLINE*/
        chg_set_usb_online_status(FALSE);

        chg_set_ac_online_status(TRUE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_CHARGER, (uint32_t)CHG_EVENT_NONEED_CARE);
        chg_stm_set_chgr_type(CHG_WALL_CHGR);
        chg_set_cur_chg_mode(CHG_WIRED_MODE);

        if((CHG_STM_INIT_ST >= cur_stat) || (CHG_STM_MAX_ST <= cur_stat)
            || (CHG_STM_BATTERY_ONLY == cur_stat) || (CHG_STM_TRANSIT_ST == cur_stat))
        {
            chg_stm_switch_state(CHG_STM_TRANSIT_ST);
        }
#if (MBB_CHG_WIRELESS == FEATURE_ON)
        if(TRUE == chg_stm_get_wireless_online_st())
        {
            /*����������߳������λ��ONLINE�ڵ���ΪOFFLINE����ֹ���߳��
                 �����в��������豸��ONLINE�ڵ�û�������ʾ���߳��ͼ��*/
            chg_stm_set_wireless_online_st(FALSE);
            chg_stm_switch_state(CHG_STM_TRANSIT_ST);
        }
#endif /*defined(MBB_CHG_WIRELESS)*/
#if ( FEATURE_ON == MBB_MLOG )
            chg_print_level_message(CHG_MSG_ERR, "std charger insert!\n ");
            mlog_set_statis_info("std_charge_insert_count",1);
#endif
        return ;
    }
    /*�������*/
    else if(CHG_500MA_WALL_CHGR == chg_type)
    {
        chg_en_flag = 0;
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:CHG_500MA_WALL_CHGR PLUG IN force to TRANSIT_ST!\n ");
        chg_stm_set_chgr_type(CHG_500MA_WALL_CHGR);
        return ;
    }
    /*���������������*/
    else if(CHG_NONSTD_CHGR == chg_type)
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:CHG_NONSTD_CHGR PLUG IN force to TRANSIT_ST!\n ");
        //���������������ʱ����ΪAC��λ
        if(FALSE == chg_get_ac_online_status())
        {
            chg_set_ac_online_status(TRUE);
            chg_set_usb_online_status(FALSE);
            chg_send_stat_to_app((uint32_t)DEVICE_ID_CHARGER, (uint32_t)CHG_EVENT_NONEED_CARE);
        }
        chg_stm_set_chgr_type(CHG_NONSTD_CHGR);
        chg_set_cur_chg_mode(CHG_WIRED_MODE);

        if((CHG_STM_INIT_ST >= cur_stat) || (CHG_STM_MAX_ST <= cur_stat)
            || (CHG_STM_BATTERY_ONLY == cur_stat) || (CHG_STM_TRANSIT_ST == cur_stat))
        {
            chg_stm_switch_state(CHG_STM_TRANSIT_ST);
        }
#if (MBB_CHG_WIRELESS == FEATURE_ON)
        if(TRUE == chg_stm_get_wireless_online_st())
        {
            /*�����������������߳������λ��ONLINE�ڵ���ΪOFFLINE����ֹ���߳��
                �����в��������豸��ONLINE�ڵ�û�������ʾ���߳��ͼ��*/
            chg_stm_set_wireless_online_st(FALSE);
            chg_stm_switch_state(CHG_STM_TRANSIT_ST);

        }
#endif /*defined(MBB_CHG_WIRELESS)*/
#if ( FEATURE_ON == MBB_MLOG )
            chg_print_level_message(CHG_MSG_ERR, "no_std charger insert!\n ");
            mlog_set_statis_info("no_std_charge_insert_count",1);
#endif
        return ;
    }

    /*���������δ֪���ڴ��ж������߳�绹�����߳���豸����*/
    else if(CHG_CHGR_UNKNOWN == chg_type)
    {
#if (MBB_CHG_WIRELESS == FEATURE_ON)
        chg_stm_set_wireless_online_st(FALSE);
#endif/*MBB_CHG_WIRELESS*/
        /*��������߳��������������AC ONLINE��֤Ӧ�ÿ���Ѹ�ٵ���
              �����⵽�����������usb�������������ͽ�AC ����ΪOFFINE,��USB����ΪONLINE*/
        chg_set_ac_online_status(TRUE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_CHARGER, (uint32_t)CHG_EVENT_NONEED_CARE);
        /*���߳������������߳������λ��ONLINE�ڵ���ΪOFFLINE����ֹ���߳��
        �����в��������豸��ONLINE�ڵ�û�������ʾ���߳��ͼ��*/
        //chg_stm_set_chgr_type(CHG_CHGR_UNKNOWN);
        chg_set_cur_chg_mode(CHG_WIRED_MODE);
        //chg_start_chgr_type_checking();
        chg_print_level_message( CHG_MSG_ERR,"CHG_PLT: wired charger but chg type unknow force to TRANSIT_ST!\n ");
        chg_stm_switch_state(CHG_STM_TRANSIT_ST);
        return ;
    }
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    else if(CHG_WIRELESS_CHGR == chg_type)
    {
        /*֪ͨUSB�������߳��������,��ֹUSB����δ������������͸����ģ��
        �ϱ�����������������³�����̻���*/
        g_wireless_online_flag = ONLINE;
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_STM:notify USB wireless charger!\n");
        usb_notify_event(USB_WIRELESS_CHGR_DET,NULL);
        if(0 == g_ui_choose_exchg_mode)
        {
            (void)chg_set_dpm_val(CHG_WIRELESS_DPM_VOLT);
            chg_stm_set_wireless_online_st(TRUE);
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:CHG_WIRELESS_CHGR PLUG IN force to TRANSIT_ST!\n ");
            /*�����������߳������Ϳ������߳��оƬGPIOʹ�����߳�磬�������е�ͣ������BQ24196����*/
            chg_set_wireless_chg_enable(TRUE);
            chg_stm_set_chgr_type(CHG_WIRELESS_CHGR);
            chg_set_cur_chg_mode(CHG_WIRELESS_MODE);
            chg_stm_switch_state(CHG_STM_TRANSIT_ST);
            chg_send_stat_to_app((uint32_t)DEVICE_ID_WIRELESS, (uint32_t)CHG_EVENT_NONEED_CARE);
            return ;
        }
        else
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:WIRELESS_CHGR PLUG IN but current not CHG_BAT_ONLY_MODE!\n");
            return ;
        }
#if ( FEATURE_ON == MBB_MLOG )        
            chg_print_level_message(CHG_MSG_ERR, "wireless charger insert!\n ");
            mlog_set_statis_info("wireless_charge_insert_count",1);
#endif
    }
#endif/*MBB_CHG_WIRELESS*/
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:PLUG IN CHG TYPE UNKNOW!\n ");
    }
}
/**********************************************************************
FUNCTION:    chg_charger_remove_proc
DESCRIPTION: usb remove process
INPUT:       chg_chgr_type_t chg_type
OUTPUT:      None.
RETURN:      None.
NOTE:        None
***********************************************************************/
void chg_charger_remove_proc(chg_chgr_type_t chg_type)
{
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    CHG_MODE_ENUM cur_chg_mode = chg_get_cur_chg_mode();
#endif
/*������ͷ�ֹ���ٲ�Σ�״̬��ˢ��*/
#if (FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT)
    if (TRUE == chg_battery_protect_flag)
    {
        chg_battery_protect_flag = FALSE;
        g_chg_over_temp_volt_protect_flag = FALSE;
        g_chg_longtime_nocharge_protect_flag = FALSE;
        (void)chg_battery_protect_exit_process();
    }
    (void)resume_long_time_no_charge_protect_recharge_volt();
#endif

#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
    if (TRUE == usb_err_flag)
    {
        usb_err_flag = FALSE;
        chg_stm_state_info.extchg_status = POWER_SUPPLY_EXTCHGSTA_UNKNOWN;
        chg_stm_set_extchg_online_st(FALSE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_CHARGER, \
            (uint32_t)CHG_EVENT_NONEED_CARE);
    }
#endif
    /*USB �γ�*/
    if(CHG_USB_HOST_PC == chg_type)
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:CHG_USB_HOST_PC PLUG OUT force to BATTERY_ONLY_st!\n ");
        chg_set_usb_online_status(FALSE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_USB, (uint32_t)CHG_EVENT_NONEED_CARE);
        chg_set_cur_chg_mode(CHG_BAT_ONLY_MODE);
        chg_stm_switch_state(CHG_STM_BATTERY_ONLY);
        chg_stm_set_chgr_type(CHG_CHGR_INVALID);
        return ;
    }
    /*���γ�*/
    else if(CHG_WALL_CHGR == chg_type || CHG_USB_OTG_CRADLE == chg_type)
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:CHG_WALL_CHGR PLUG OUT force to BATTERY_ONLY_st!\n ");
        //AF18 �γ���ָ�Ĭ��DPM��ѹֵ
        if(CHG_USB_OTG_CRADLE == chg_type)
        {
            chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:AF18 PLUG out set Dpm.\n ");
            chg_set_dpm_val(CHG_DEFAULT_DPM_VOLT);
        }
        chg_set_ac_online_status(FALSE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_CHARGER, (uint32_t)CHG_EVENT_NONEED_CARE);
        chg_set_cur_chg_mode(CHG_BAT_ONLY_MODE);
        chg_stm_switch_state(CHG_STM_BATTERY_ONLY);
        chg_stm_set_chgr_type(CHG_CHGR_INVALID);
        return ;
    }
    /*����γ�*/
    else if(CHG_500MA_WALL_CHGR == chg_type)
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:CHG_500MA_WALL_CHGR PLUG OUT force to BATTERY_ONLY_st!\n ");
        chg_set_ac_online_status(FALSE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_CHARGER, (uint32_t)CHG_EVENT_NONEED_CARE);
        chg_set_cur_chg_mode(CHG_BAT_ONLY_MODE);
        chg_stm_switch_state(CHG_STM_BATTERY_ONLY);
        chg_stm_set_chgr_type(CHG_CHGR_INVALID);
        return ;
    }
    /*������������γ�*/
    else if(CHG_NONSTD_CHGR == chg_type)
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:CHG_NONSTD_CHGR PLUG OUT force to BATTERY_ONLY_st!\n ");
        /*������������γ�����USB�����γ���Ӧ���ϱ�*/
        chg_set_usb_online_status(FALSE);
        chg_send_stat_to_app((uint32_t)DEVICE_ID_USB, (uint32_t)CHG_EVENT_NONEED_CARE);
        chg_set_cur_chg_mode(CHG_BAT_ONLY_MODE);
        chg_stm_switch_state(CHG_STM_BATTERY_ONLY);
        chg_stm_set_chgr_type(CHG_CHGR_INVALID);

        return ;
    }
    else if(CHG_CHGR_UNKNOWN == chg_type)
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:CHG_CHGR_UNKNOWN PLUG OUT force to BATTERY_ONLY_st!\n ");
        if (TRUE == chg_get_usb_online_status())
        {
            chg_set_usb_online_status(FALSE);
            chg_send_stat_to_app((uint32_t)DEVICE_ID_USB, (uint32_t)CHG_EVENT_NONEED_CARE);
        }
        if(TRUE == chg_get_ac_online_status())
        {
            chg_set_ac_online_status(TRUE);
            chg_send_stat_to_app((uint32_t)DEVICE_ID_CHARGER, (uint32_t)CHG_EVENT_NONEED_CARE);
        }
#if (MBB_CHG_WIRELESS == FEATURE_ON)
        if (TRUE == chg_stm_get_wireless_online_st())
        {
            chg_stm_set_wireless_online_st(FALSE);
            chg_send_stat_to_app((uint32_t)DEVICE_ID_WIRELESS, (uint32_t)CHG_EVENT_NONEED_CARE);
        }
#endif/*defined(MBB_CHG_WIRELESS)*/
#if (MBB_CHG_EXTCHG == FEATURE_ON)
#if (FEATURE_ON == MBB_CHG_APORT_EXTCHG)
#else
        if (TRUE == chg_stm_get_extchg_online_st())
        {
            chg_stm_set_extchg_online_st(FALSE);
            chg_send_stat_to_app((uint32_t)DEVICE_ID_WIRELESS, (uint32_t)CHG_EVENT_NONEED_CARE);
        }
#endif
#endif/*defined(MBB_CHG_EXTCHG)*/

        chg_set_cur_chg_mode(CHG_BAT_ONLY_MODE);
        chg_stm_set_chgr_type(CHG_CHGR_INVALID);
        chg_stm_switch_state(CHG_STM_BATTERY_ONLY);
        return ;
    }
#if (MBB_CHG_WIRELESS == FEATURE_ON)
    /*���߳�����γ�*/
    else if(CHG_WIRELESS_CHGR == chg_type)
    {
        /*�����ǰ�����߳��ģʽ�����߳��������λ��Ž���״̬�л�����ֻ�����޳����
            ONLINE�ڵ�����ΪOFFLINE,������״̬�л�*/
        g_wireless_online_flag = OFFLINE;
        if((CHG_WIRELESS_MODE == cur_chg_mode) || (TRUE == chg_is_powdown_charging()))
        {
             chg_stm_set_wireless_online_st(FALSE);
             chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:CHG_WIRELESS_CHGR PLUG OUT force to BATTERY_ONLY_st!\n ");
            (void)chg_set_dpm_val(CHG_DEFAULT_DPM_VOLT);
            chg_set_cur_chg_mode(CHG_BAT_ONLY_MODE);
            chg_stm_switch_state(CHG_STM_BATTERY_ONLY);
            chg_stm_set_chgr_type(CHG_CHGR_INVALID);
            chg_send_stat_to_app((uint32_t)DEVICE_ID_WIRELESS, (uint32_t)CHG_EVENT_NONEED_CARE);
            return ;
        }

    }
#endif/*MBB_CHG_WIRELESS*/
    else
    {
        chg_print_level_message(CHG_MSG_DEBUG, "CHG_PLT:PLUG OUT CHG TYPE UNKNOW!\n ");
    }
}

#define TABLE_NUM    g_chg_hardware_data->adc2temp_map->size

void chg_hardware_paras_dump(void)
{
    int i;

    if(NULL == g_chg_hardware_data)
    {
        chg_print_level_message(CHG_MSG_ERR,"no valid data!!\n");
    }
    chg_print_level_message(CHG_MSG_ERR,"id_voltage_min=%d\n",g_chg_hardware_data->id_voltage_min);  
    chg_print_level_message(CHG_MSG_ERR,"id_voltage_max=%d\n",g_chg_hardware_data->id_voltage_max);  
    chg_print_level_message(CHG_MSG_ERR,"batt_volt_hkadc_id=%d\n",g_chg_hardware_data->batt_volt_hkadc_id);  
    chg_print_level_message(CHG_MSG_ERR,"vbus_volt_hkadc_id=%d\n",g_chg_hardware_data->vbus_volt_hkadc_id);
    chg_print_level_message(CHG_MSG_ERR,"batt_temp_hkadc_id=%d\n",g_chg_hardware_data->batt_temp_hkadc_id);  
    chg_print_level_message(CHG_MSG_ERR,"batt_cali_volt_min=%d\n",g_chg_hardware_data->batt_cali_volt_min);
    chg_print_level_message(CHG_MSG_ERR,"batt_cali_volt_max=%d\n",g_chg_hardware_data->batt_cali_volt_max);  
    chg_print_level_message(CHG_MSG_ERR,"batt_bad_volt=%d\n",g_chg_hardware_data->batt_bad_volt);
    chg_print_level_message(CHG_MSG_ERR,"batt_valid_temp=%d\n",g_chg_hardware_data->batt_valid_temp);  
    chg_print_level_message(CHG_MSG_ERR,"extchg_stop_temp=%d\n",g_chg_hardware_data->extchg_stop_temp);
    chg_print_level_message(CHG_MSG_ERR,"extchg_resume_temp=%d\n",g_chg_hardware_data->extchg_resume_temp);  
    chg_print_level_message(CHG_MSG_ERR,"chg_ic_en_gpio=%d\n",g_chg_hardware_data->chg_ic_en_gpio);
    
    for(i=0;i<CHG_STM_MAX_ST;i++)
    {

        chg_print_level_message(CHG_MSG_ERR,"***********std paras,stm_status=%d*************\n",i); 
        chg_print_level_message(CHG_MSG_ERR,"supply_current_limit=%d\n",g_chg_hardware_data->chg_std_chgr_hw_paras->pwr_supply_current_limit_in_mA);     
        chg_print_level_message(CHG_MSG_ERR,"chg_current_limit=%d\n",g_chg_hardware_data->chg_std_chgr_hw_paras->chg_current_limit_in_mA); 
        chg_print_level_message(CHG_MSG_ERR,"CV_volt=%d\n",g_chg_hardware_data->chg_std_chgr_hw_paras->chg_CV_volt_setting_in_mV);     
        chg_print_level_message(CHG_MSG_ERR,"taper_current=%d\n",g_chg_hardware_data->chg_std_chgr_hw_paras->chg_taper_current_in_mA);
        chg_print_level_message(CHG_MSG_ERR,"chg_is_enabled=%d\n",g_chg_hardware_data->chg_std_chgr_hw_paras->chg_is_enabled);     
    }
    for(i=0;i<CHG_STM_MAX_ST;i++)
    {
        chg_print_level_message(CHG_MSG_ERR,"***********usb2 paras,stm_status=%d*************\n",i); 
        chg_print_level_message(CHG_MSG_ERR,"supply_current_limit=%d\n",g_chg_hardware_data->chg_usb_chgr_hw_paras->pwr_supply_current_limit_in_mA);     
        chg_print_level_message(CHG_MSG_ERR,"chg_current_limit=%d\n",g_chg_hardware_data->chg_usb_chgr_hw_paras->chg_current_limit_in_mA); 
        chg_print_level_message(CHG_MSG_ERR,"CV_volt=%d\n",g_chg_hardware_data->chg_usb_chgr_hw_paras->chg_CV_volt_setting_in_mV);     
        chg_print_level_message(CHG_MSG_ERR,"taper_current=%d\n",g_chg_hardware_data->chg_usb_chgr_hw_paras->chg_taper_current_in_mA);
        chg_print_level_message(CHG_MSG_ERR,"chg_is_enabled=%d\n",g_chg_hardware_data->chg_usb_chgr_hw_paras->chg_is_enabled);     
    }
    for(i=0;i<CHG_STM_MAX_ST;i++)
    {
        chg_print_level_message(CHG_MSG_ERR,"***********usb3 paras,stm_status=%d*************\n",i);
        chg_print_level_message(CHG_MSG_ERR,"supply_current_limit=%d\n",g_chg_hardware_data->chg_usb3_chgr_hw_paras->pwr_supply_current_limit_in_mA);     
        chg_print_level_message(CHG_MSG_ERR,"chg_current_limit=%d\n",g_chg_hardware_data->chg_usb3_chgr_hw_paras->chg_current_limit_in_mA); 
        chg_print_level_message(CHG_MSG_ERR,"CV_volt=%d\n",g_chg_hardware_data->chg_usb3_chgr_hw_paras->chg_CV_volt_setting_in_mV);     
        chg_print_level_message(CHG_MSG_ERR,"taper_current=%d\n",g_chg_hardware_data->chg_usb3_chgr_hw_paras->chg_taper_current_in_mA);
        chg_print_level_message(CHG_MSG_ERR,"chg_is_enabled=%d\n",g_chg_hardware_data->chg_usb3_chgr_hw_paras->chg_is_enabled);     
    }
    
    chg_print_level_message(CHG_MSG_ERR,"***********volt2temp,num=%d*************\n",TABLE_NUM);    
    for(i=0;i<TABLE_NUM;i++)
    {
        chg_print_level_message(CHG_MSG_ERR,"temp:%d  volt:%d\n",g_chg_hardware_data->adc2temp_map->adc_batt_therm_map[i].temperature,g_chg_hardware_data->adc2temp_map->adc_batt_therm_map[i].voltage);        
    }
}

int32_t chg_hardware_paras_init(void)
{
    int32_t hw_id = 0;
    hw_id = chg_get_hardware_data_id();
    g_chg_hardware_data = chg_get_hardware_data(hw_id);
    if(NULL == g_chg_hardware_data)
    {
        chg_print_level_message(CHG_MSG_ERR,"CHG_INIT:get hardware data fail!!\n");    
        return -1;    
    }
    return 0;
}


struct chg_batt_data *chg_get_batt_data(unsigned int id_voltage)
{
    int i;

    for (i = (BATTERY_DATA_ARRY_SIZE - 1); i > 0; i--){
        if ((id_voltage >= chg_batt_data_array[i]->id_voltage_min)
            && (id_voltage <= chg_batt_data_array[i]->id_voltage_max)){
            break;
        }
    }

    return chg_batt_data_array[i];
}


int32_t chg_batt_volt_paras_init(void)
{
    int32_t batt_id = 0;
    batt_id = chg_get_batt_id_volt();
    g_chg_batt_data = chg_get_batt_data(batt_id);
    if(NULL == g_chg_batt_data)
    {
        chg_print_level_message(CHG_MSG_ERR,"CHG_INIT:get batt data fail!!\n");    
        return -1;    
    }
    #if defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577S_932) \
    || defined(BSP_CONFIG_BOARD_E5577S_324)|| defined(BSP_CONFIG_BOARD_E5577BS_937)
    if(FALSE == is_5577cs_falg)
    {
        if((g_chg_batt_data->batt_id == CHG_BATT_ID_XINGWANGDA_3000)
            ||(g_chg_batt_data->batt_id == CHG_BATT_ID_FEIMAOTUI_3000)
            ||(g_chg_batt_data->batt_id == CHG_BATT_ID_LISHEN_3000))
        {
            chg_high_bat_paras_init();//3000mA��س�������ʼ��
            is_bat_3000 = TRUE;

        }
        else
        {
            g_chg_batt_data = chg_batt_data_array[0];
            is_bat_3000 = FALSE;
        }
    }
    #endif
    //init batt para
    memcpy(&g_chgBattVoltProtect, (uint8_t*)&g_chg_batt_data->chg_batt_volt_paras, sizeof(CHG_SHUTOFF_VOLT_PROTECT_NV_TYPE));
    
    return 0;
}
/*get batt brand*/
uint32_t chg_get_batt_id(void)
{
    if(NULL == g_chg_batt_data)
    {
        chg_print_level_message(CHG_MSG_ERR,"CHG_INIT:get batt data fail!!\n");    
        return CHG_BATT_ID_MAX;    
    }
    chg_print_level_message(CHG_MSG_DEBUG,"CHG: batt brand is %d\n",g_chg_batt_data->batt_id); 
    
    return g_chg_batt_data->batt_id;
}

void chg_batt_data_dump(void)
{
    chg_print_level_message(CHG_MSG_ERR,"battVoltPowerOnThreshold=%d\n",
        g_chgBattVoltProtect.battVoltPowerOnThreshold);  
    chg_print_level_message(CHG_MSG_ERR,"battVoltPowerOffThreshold=%d\n",
        g_chgBattVoltProtect.battVoltPowerOffThreshold); 
    chg_print_level_message(CHG_MSG_ERR,"battOverVoltProtectThreshold=%d\n",
        g_chgBattVoltProtect.battOverVoltProtectThreshold);  
    chg_print_level_message(CHG_MSG_ERR,"battOverVoltProtectOneThreshold=%d\n",
        g_chgBattVoltProtect.battOverVoltProtectOneThreshold); 
    chg_print_level_message(CHG_MSG_ERR,"battChgTempMaintThreshold=%d\n",
        g_chgBattVoltProtect.battChgTempMaintThreshold);  
    chg_print_level_message(CHG_MSG_ERR,"battChgRechargeThreshold=%d\n",
        g_chgBattVoltProtect.battChgRechargeThreshold); 
    chg_print_level_message(CHG_MSG_ERR,"VbatLevelLow_MAX=%d\n",g_chgBattVoltProtect.VbatLevelLow_MAX);  
    chg_print_level_message(CHG_MSG_ERR,"VbatLevel0_MAX=%d\n",g_chgBattVoltProtect.VbatLevel0_MAX); 
    chg_print_level_message(CHG_MSG_ERR,"VbatLevel1_MAX=%d\n",g_chgBattVoltProtect.VbatLevel1_MAX);  
    chg_print_level_message(CHG_MSG_ERR,"VbatLevel2_MAX=%d\n",g_chgBattVoltProtect.VbatLevel2_MAX); 
    chg_print_level_message(CHG_MSG_ERR,"VbatLevel3_MAX=%d\n",g_chgBattVoltProtect.VbatLevel3_MAX); 
    chg_print_level_message(CHG_MSG_ERR,"battChgFirstMaintThreshold=%d\n",
        g_chgBattVoltProtect.battChgFirstMaintThreshold);  
    chg_print_level_message(CHG_MSG_ERR,"battNormalTempChgRechargeThreshold=%d\n",
        g_chgBattVoltProtect.battNormalTempChgRechargeThreshold); 
        
    chg_print_level_message(CHG_MSG_ERR,"batt brand is %d\n",g_chg_batt_data->batt_id);    
#if (FEATURE_ON == MBB_CHG_BATT_EXPAND_PROTECT)
    chg_print_level_message(CHG_MSG_ERR,"g_batt_normal_temp_recherge_threshold=%d\n",
        g_batt_normal_temp_recherge_threshold);
#endif
}
#if defined(BSP_CONFIG_BOARD_E5577S_321) || defined(BSP_CONFIG_BOARD_E5577S_932) \
   || defined(BSP_CONFIG_BOARD_E5577S_324)|| defined(BSP_CONFIG_BOARD_E5577BS_937)
void chg_high_bat_paras_init()
{
    int i = 0;
    for(i=0;i<CHG_STM_MAX_ST;i++)
    {
        chg_std_chgr_hw_paras[i] = chg_std_chgr_hw_paras_h[i];
        chg_usb_chgr_hw_paras[i] = chg_usb_chgr_hw_paras_h[i];
        chg_usb3_chgr_hw_paras[i] = chg_usb3_chgr_hw_paras_h[i];
    }
}
#endif

