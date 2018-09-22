
/*lint --e{537} */
#include <hi_onoff.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/syscalls.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <product_config.h>
#include <drv_onoff.h>
#include <drv_chg.h>
#include <bsp_icc.h>
#include <power_com.h>
#include "power_exchange.h"
#include "power_inner.h"
#include "mbb_config.h" /*����MBB��Ʒ�����ļ�*/
#include "bsp_efuse.h"
#include <hi_efuse.h>
#include <linux/mlog_lib.h>
#include <bsp_sram.h>

#define POWER_SYS_PRIV_RO  (S_IRUSR | S_IRGRP)
#define POWER_SYS_PRIV_WR  (S_IWUSR | S_IRUGO)

static power_on_ctrl_s power_item_info = {0}; //lint !e64

static ssize_t his_boot_store_property(struct device *dev,
                            struct device_attribute *attr,const char *buf,
                            size_t count);
static ssize_t his_boot_show_property(struct device *dev,
                            struct device_attribute *attr, char *buf);

#define POWER_ON_ATTR(_name, _mode)					\
{									            \
	.attr = { .name = #_name, .mode = _mode },					\
	.show = his_boot_show_property,          \
	.store = his_boot_store_property,	        \
}

/* ���ó�ֻ�� */
static struct device_attribute power_on_attrs[] = {
	POWER_ON_ATTR(power_status, POWER_SYS_PRIV_RO),
	POWER_ON_ATTR(power_reason, POWER_SYS_PRIV_RO),
	POWER_ON_ATTR(power_time, POWER_SYS_PRIV_RO),
};

static struct attribute *
his_boot_attributes[ARRAY_SIZE(power_on_attrs) + 1]; //lint !e30 !e84

static const struct attribute_group his_boot_group = {
	.attrs = his_boot_attributes,
};

/*****************************************************************************
 �� �� ��  : power_on_init_attrs
 ��������  : init attributes
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static void power_on_init_attrs(void)
{
	u32 i;

	for (i = 0; i < ARRAY_SIZE(power_on_attrs); i++) //lint !e30 !e84
		his_boot_attributes[i] = &power_on_attrs[i].attr;
}

/*****************************************************************************
 �� �� ��  : power_on_log_save
 ��������  : ���濪��log
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static int power_on_log_save( void )
{
    long pos;
    unsigned int pf;
    mm_segment_t old_fs;
    ssize_t rt = 0;
    char buf[128] = {0};
    struct rtc_time tm;
    char *power_on_reason[4];
    char *power_on_mode[5];
    BATT_LEVEL_ENUM  battery_level;

    tm = power_item_info.time;
    battery_level = chg_get_batt_level();


    power_on_reason[0] = "Charger";
    power_on_reason[1] = "Power Key";
    power_on_reason[2] = "Warm Reset";
    power_on_reason[3] = "Unknown";
    power_on_mode[0] = "EXCEPTION";
    power_on_mode[1] = "NORMAL";
    power_on_mode[2] = "PWN CHARGING";
	power_on_mode[3] = "UPDATE";
    power_on_mode[4] = "INVALID";
    /* ��¼������Ϣ(ʱ�䡢�������ػ�ԭ��) */
    snprintf(buf, sizeof(buf) - 1, "power on reason(E5): %s, power on mode : %s, current battery voltage: %d, current time: %4d-%02d-%02d %02d:%02d:%02d\r\n", \
            power_on_reason[power_item_info.reason], power_on_mode[power_item_info.mode], battery_level, tm.tm_year, tm.tm_mon, \
            tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    mlog_print(MLOG_POWER, mlog_lv_info, "POWERON mode %s\n" ,power_on_mode[power_item_info.mode]);
    mlog_print(MLOG_POWER, mlog_lv_info, "POWERON due to %s\n" ,power_on_reason[power_item_info.reason]);
    mlog_set_statis_info("on_times",1); 
    old_fs = get_fs(); //lint !e63

    set_fs(KERNEL_DS);

    /*coverity[check_return] */
    pf = (unsigned int)sys_open(EXCH_POWER_LOG_PATH, O_RDWR | O_CREAT, 0666);
    /*coverity[unchecked_value] */
    if(IS_ERR((const void*)pf))
    {
        pr_dbg( "error occured happened when open file %s, exiting.\n", EXCH_POWER_LOG_PATH);
        return (int)pf;
    }

    /*coverity[unchecked_value] */
    pos = sys_lseek(pf, 0, SEEK_END);
    if(pos > EXCH_ONOFF_LOG_MAX){
        /* �ļ����� 16k,ɾ�����´� */
        sys_rmdir(EXCH_POWER_LOG_PATH);
        /*coverity[check_return] */
        pf = (unsigned int)sys_open(EXCH_POWER_LOG_PATH, O_RDWR | O_CREAT, 0666);
        /*coverity[unchecked_value] */
        if(IS_ERR((const void*)pf))
        {
            pr_dbg( "error occured happened when open file %s, exiting.\n", EXCH_POWER_LOG_PATH);
            return (int)pf;
        }
    }
    else{
        /*coverity[unchecked_value] */
        sys_lseek(pf, pos, SEEK_SET);
    }

    /*coverity[unchecked_value] */
    rt = sys_write(pf, (const char*)buf, strlen(buf));
    if(rt<0)
    {
        pr_dbg("error occured happened when write file %s, exiting.\n", EXCH_POWER_LOG_PATH);
        /*coverity[unchecked_value] */
        sys_close(pf);
        set_fs(old_fs);
        return (int)rt;
    }

    /*coverity[unchecked_value] */
    sys_close(pf);
    set_fs(old_fs);

    pr_dbg(KERN_DEBUG "power on log save.\n ");

    return (int)rt;
}

/*****************************************************************************
 �� �� ��  : power_on_time_get
 ��������  : ��¼����ʱ��.
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static void power_on_time_get( void )
{
    struct rtc_time tm;
    struct timespec ts;

    getnstimeofday(&ts);

    rtc_time_to_tm((unsigned long)ts.tv_sec, &tm);

    power_item_info.time = tm;

    pr_dbg("system power on time:%4d-%02d-%02d %02d:%02d:%02d\n",tm.tm_year, tm.tm_mon, \
            tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

/*****************************************************************************
 �� �� ��  : power_on_reason_get
 ��������  : ��ȡ����ԭ��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static void power_on_reason_get( void )
{
    DRV_START_REASON reason = DRV_START_REASON_BUTT;
    power_on_start_reason sram_data = POWER_ON_START_REASON_BUTT;

    sram_data = power_on_start_reason_get();
    switch(sram_data)
    {
    case POWER_ON_START_REASON_CHARGE:
        reason = DRV_START_REASON_CHARGE;
        break;
    case POWER_ON_START_REASON_POWER_KEY:
        reason = DRV_START_REASON_POWER_KEY;
        break;
    case POWER_ON_START_REASON_WARM_RESET:
        reason = DRV_START_REASON_WARM_RESET;
        break;
    default:
        reason = DRV_START_REASON_BUTT;
        break;
    }

    power_item_info.reason = reason;
}

/*****************************************************************************
 �� �� ��  : power_on_mode_get
 ��������  : ��ȡ����ģʽ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static void power_on_mode_get( void )
{
    DRV_START_MODE mode = DRV_START_MODE_NORMAL;
    DRV_RUN_MODE boot_mode = get_run_mode();
    DRV_CHARGING_MODE pwd_flag = get_pd_charge_flag();
    if((RUN_MODE_NORMAL == boot_mode) && (POWER_DOWN_CHARGING_MODE != pwd_flag))
    {
        /* ����ģʽ */
        mode = DRV_START_MODE_NORMAL;
    }
    else if((RUN_MODE_NORMAL == boot_mode) && ((POWER_DOWN_CHARGING_MODE == pwd_flag)))
    {
        /* �ػ����ģʽ */
        mode = DRV_START_MODE_CHARGING;
    }
    else if(RUN_MODE_RECOVERY == boot_mode)
    {
        /* ����ģʽ */
        mode = DRV_START_MODE_UPDATE;     
    }
    power_item_info.mode = mode;
}

/*****************************************************************************
 �� �� ��  : power_off_timeout_isr
 ��������  : ������ʱ���������C��״̬
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static int power_on_timeout_isr( void )
{
    c_power_st_e status = POWER_OS_OK;
    DRV_RUN_MODE run_mode = get_run_mode();

    pr_dbg("power_on_timeout_isr, system had been powered one minute ago\n ");
    if(chg_is_powdown_charging())
    {
        pr_dbg("CHG:no need to check c core status!\n ");
        return 0;
    }
    if(RUN_MODE_NORMAL == run_mode)
    {
        /* ��ȡC������״̬ */
        status = power_on_c_status_get();

        if(status < POWER_MSP_OK)
        {
           pr_dbg("c core power on fail!\n ");
           /* ����recoveryģʽ */
           bsp_drv_power_reboot();

           /* coverity[no_escape] */
           for(;;) ;
        }
    }
    else if(RUN_MODE_RECOVERY == run_mode){
        /* for test */
    }

    pr_dbg("system power on ok!\n ");

    /* clear warm boot cnt */
    power_on_wdt_cnt_set();

    (void)bsp_softtimer_free(&power_item_info.on_timer);

    return 0;
}

/*****************************************************************************
 �� �� ��  : power_on_timer_init
 ��������  : ��������timer,���ڿ�����һ��ʱ����ϵͳ�Ƿ���������
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
void power_on_timer_init( void )
{
	s32 ret = 0;

	power_item_info.on_timer.func = (softtimer_func)power_on_timeout_isr;

	power_item_info.on_timer.para = (u32)0;
	power_item_info.on_timer.timeout = POWER_ON_MONITOR_TIMEROUT;
	power_item_info.on_timer.wake_type = SOFTTIMER_WAKE;

	ret = bsp_softtimer_create(&power_item_info.on_timer);
    if (ret)
    {
        pr_dbg("create softtimer failed \n");
    }

    bsp_softtimer_add(&power_item_info.on_timer);
}

/*****************************************************************************
 �� �� ��  : his_boot_store_property
 ��������  : echo sysfs   do nothing
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static ssize_t his_boot_store_property(struct device *dev,
                            struct device_attribute *attr,const char *buf,
                            size_t count)
{
    pr_dbg("his_boot_store\n");

    return 0;
}

/*****************************************************************************
 �� �� ��  : his_boot_show_property
 ��������  : show power on status/reason/time item property.
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static ssize_t his_boot_show_property(struct device *dev,
                            struct device_attribute *attr, char *buf)
{
    struct rtc_time tm = power_item_info.time;

	static char *power_status[] = {
		"Power Down Charging", "Normal", "Update", "Unkown"
	};

	static char *power_reason[] = {
		"Charger", "Power Key", "Warm Reset", "Unknown",
	};

	const ptrdiff_t off = attr - power_on_attrs;

	if (off == POWER_ON_PROP_STATUS)
		return sprintf(buf, "%s\n", power_status[power_item_info.mode]);
	else if (off == POWER_ON_PROP_REASON)
		return sprintf(buf, "%s\n", power_reason[power_item_info.reason]);
	else if (off == POWER_ON_PROP_TIME){
		return sprintf(buf, "%4d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year, tm.tm_mon, \
        tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    }

    /* coverity[secure_coding] */
	return sprintf(buf, "%s\n", "error item");
}
bool mbb_kernel_secboot_id_check(void)
{
    return TRUE;
}
/*****************************************************************************
 �� �� ��  : bsp_start_mode_get
 ��������  : ���ڻ�ȡ����ģʽ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_start_mode_get()
{
    power_on_mode_get();
    return power_item_info.mode;
}


/*****************************************************************************
 �� �� ��  : bsp_power_icc_send_state
 ��������  : C�˺˼�ͨ�ź���
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static void bsp_power_icc_send_state(void)
{
    int ret = 0;
    int mode = 0;
    u32 icc_channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_ONOFF;

    mode = bsp_start_mode_get();

    ret = bsp_icc_send(ICC_CPU_MODEM, icc_channel_id, (u8*)&mode, sizeof(mode));
    if (ret != (int)sizeof(mode))
    {
        pr_dbg("send len(%x) != expected len(%x)\n", ret, sizeof(mode));
    }
}

/*****************************************************************************
 �� �� ��  : bsp_power_ctrl_read_cb
 ��������  : C�˺˼�ص�����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static s32 bsp_power_ctrl_read_cb( void )
{
    int rt = 0;
    int read_len = 0;
    stCtrlMsg msg;
    u32 channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_ONOFF;

	read_len = bsp_icc_read(channel_id, (u8*)&msg, sizeof(stCtrlMsg));
	if(read_len != (int)sizeof(stCtrlMsg))
	{
		pr_dbg("read len(%x) != expected len(%x)\n", read_len, sizeof(stCtrlMsg));
		return -1;
	}

	pr_dbg("bsp_power_ctrl_read_cb 0x%x\n", msg.pwr_type);

    switch(msg.pwr_type)
    {
    case E_POWER_ON_MODE_GET:
        bsp_power_icc_send_state();
        break;
    case E_POWER_SHUT_DOWN:
        drv_shut_down(msg.reason);
        break;
    case E_POWER_POWER_OFF:
        bsp_drv_power_off();
        break;
    case E_POWER_POWER_REBOOT:
        bsp_drv_power_reboot();
        break;
    default:
        pr_dbg("invalid ctrl by ccore\n");
        break;
    }

    return rt;
}

/*****************************************************************************
 �� �� ��  : his_boot_probe
 ��������  : power on
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static int __init his_boot_probe(struct platform_device *pdev)
{
    int rt;
    u32 channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_ONOFF;

    if( FALSE == mbb_kernel_secboot_id_check() )
    {
        /* A��У��ʧ�ܣ��������� */
        bsp_drv_power_reboot();
        for(;;) ;
    }
    if (*(u32*)SRAM_ABNORMAL_REBOOT_ADDR == SRAM_ABNORAL_REBOOT_NUM)
    {
        mlog_print(MLOG_POWER, mlog_lv_info, "reboot flag POWER_OFF_REASON_CRASH\n");       
        mlog_set_statis_info("abnormal_reboot_times",1); 
    }
    *(u32*)SRAM_ABNORMAL_REBOOT_ADDR = SRAM_ABNORAL_REBOOT_CLEAR;


    /* get early param */

    /* ���reboot flag */
    power_on_reboot_flag_set(POWER_OFF_REASON_INVALID);

    /* normalģʽ�� clear misc partition */

    power_on_mode_get();

    /* get power on reason */
    power_on_reason_get();

    /* get power time */
    power_on_time_get();

    /* sysfs create */
    power_on_init_attrs();

    rt = (int)sysfs_create_group(&pdev->dev.kobj, &his_boot_group);
    if (rt < 0)
    {
        pr_dbg("create sys filesystem node failed.\n");
        return rt;
    }

    /* file create and power on info record */
    rt = power_on_log_save();
    if(rt < 0){
        pr_dbg("power on log record failed.\n");
        return rt;
    }
    /* ��������timer */
    power_on_timer_init();
    rt = bsp_icc_event_register(channel_id, (read_cb_func)bsp_power_ctrl_read_cb, NULL, NULL, NULL);
    if(rt != 0){
        pr_dbg("icc event register failed.\n");
    }

    return rt;
}

static struct platform_device his_boot_dev = {
    .name = "his_boot",
    .id = 0,
    .dev = {
    .init_name = "his_boot",
    },
};

static struct platform_driver his_boot_drv = {
    .probe      = his_boot_probe,
	.driver		= {
		.name	= "his_boot",
		.owner	= THIS_MODULE,
	},
};

static int __init his_boot_init(void)
{
    ssize_t ret = 0;

    pr_dbg(KERN_DEBUG "his_boot_init.\r\n");

    ret = platform_device_register(&his_boot_dev);
    if(ret)
    {
        pr_dbg("register his_boot device failed. \r\n");
        return ret;
    }

    ret = platform_driver_register(&his_boot_drv);
    if(ret)
    {
        pr_dbg("register his_boot driver failed. \r\n");
        platform_device_unregister(&his_boot_dev);
    }

    return ret;

}

static void __exit his_boot_exit(void)
{
    platform_driver_unregister(&his_boot_drv);
    platform_device_unregister(&his_boot_dev);
}

late_initcall(his_boot_init);

MODULE_AUTHOR("E5 FEATURE");

