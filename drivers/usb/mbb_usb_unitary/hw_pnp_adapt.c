

#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/syscalls.h>

#include "f_mass_storage_api.h"

static USB_PCHAR config_funcs_win8[CONFIG_TWO_MAX_PORT_NUM] = {USB_MBIM_FUNC_NAME, NULL};

/*�ӿ�Э���ֶ�*/
huawei_interface_info g_huawei_interface_vector[] =
{
    /*ͨ�ð�Protocol*/
    {USB_IF_PROTOCOL_VOID,        "mass"},    //����
    {USB_IF_PROTOCOL_3G_MODEM,    "3g_modem"},//modem
    {USB_IF_PROTOCOL_3G_PCUI,        "pcui"}, //PCUI
    {USB_IF_PROTOCOL_3G_DIAG,     "3g_diag"}, //diag
    {USB_IF_PROTOCOL_PCSC,        "pcsc"},    //���ܿ�
    {USB_IF_PROTOCOL_3G_GPS,      "a_shell"}, //shell��
    {USB_IF_PROTOCOL_CTRL,        "gps_ctl"}, //
    {USB_IF_PROTOCOL_3G_NDIS,     "ndis"},    //������
    {USB_IF_PROTOCOL_NDISDATA,    "ndisData"},//������
    {USB_IF_PROTOCOL_NDISCTRL,    "ndisCtrl"},//������
    {USB_IF_PROTOCOL_BLUETOOTH,   "c_shell"}, //chsell
    {USB_IF_PROTOCOL_FINGERPRINT, "finger"},  //ָ��
    {USB_IF_PROTOCOL_ACMCTRL,     "acmCtrl"}, //�ɴ���
    {USB_IF_PROTOCOL_MMS,         "mms"},     //���ſ�
    {USB_IF_PROTOCOL_3G_PCVOICE,  "3g_voice"},//pc����
    {USB_IF_PROTOCOL_DVB,         "dvb"},     //���ӿ�
    {USB_IF_PROTOCOL_MODEM,       "modem"},   //modem��
    {USB_IF_PROTOCOL_NDIS,        "ndis"},    //������
    {USB_IF_PROTOCOL_PCUI,        "pcui"},    //AT��
    {USB_IF_PROTOCOL_DIAG,        "4g_diag"}, //��Ͽ�
    {USB_IF_PROTOCOL_GPS,         "gps"},     //
    {USB_IF_PROTOCOL_PCVOICE,     "voice"},   //pc����
    {USB_IF_PROTOCOL_NCM,         "ncm"},     //��������
    {USB_IF_PROTOCOL_CDROM,       "mass"},    //����
    {USB_IF_PROTOCOL_SDRAM,       "mass_two"}, //SD
    {USB_IF_PROTOCOL_RNDIS,       "rndis"},   //RNDIS����
    /*VDF���ư�Protocol*/
    {VDF_USB_IF_PROTOCOL_MODEM,         "3g_modem"},//modem
    {VDF_USB_IF_PROTOCOL_PCUI,          "pcui"}, //PCUI
    {VDF_USB_IF_PROTOCOL_DIAG,          "3g_diag"}, //diag
    {VDF_USB_IF_PROTOCOL_PCSC,          "pcsc"},    //���ܿ�
    {VDF_USB_IF_PROTOCOL_GPS,           "a_shell"}, //shell��
    {VDF_USB_IF_PROTOCOL_CTRL,          "gps_ctl"}, //
    {VDF_USB_IF_PROTOCOL_NDIS,          "ndis"},    //������
    {VDF_USB_IF_PROTOCOL_NDISDATA,      "ndisData"},//������
    {VDF_USB_IF_PROTOCOL_NDISCTRL,      "ndisCtrl"},//������
    {VDF_USB_IF_PROTOCOL_BLUETOOTH,     "c_shell"}, //chsell
    {VDF_USB_IF_PROTOCOL_FINGERPRINT,   "finger"},  //ָ��
    {VDF_USB_IF_PROTOCOL_ACMCTRL,       "acmCtrl"}, //�ɴ���
    {VDF_USB_IF_PROTOCOL_MMS,           "mms"},     //���ſ�
    {VDF_USB_IF_PROTOCOL_PCVOICE,       "voice"},//pc����
    {VDF_USB_IF_PROTOCOL_DVB,           "dvb"},     //���ӿ�
    {VDF_USB_IF_PROTOCOL_NCM,           "ncm"},     //��������
    {VDF_USB_IF_PROTOCOL_SHEEL_A,       "a_shell"},     //a shell ��
    {VDF_USB_IF_PROTOCOL_SHEEL_B,       "c_shell"},     //a shell ��
    {VDF_USB_IF_PROTOCOL_COMM_A,        "comm_a"},     //ͨ�ô���A
    {VDF_USB_IF_PROTOCOL_COMM_B,        "comm_b"},     //ͨ�ô���B
    {VDF_USB_IF_PROTOCOL_COMM_C,        "comm_c"},     //ͨ�ô���C
    {VDF_USB_IF_PROTOCOL_COMM_GNSS,     "gnss"},     //GNSS�˿ڣ���ԭ��GPS�˿ڣ�

    /*��Huawei ����*/
    {NO_HW_USB_IF_PROTOCOL_MODEM,          "modem"},   //modem��
    {NO_HW_USB_IF_PROTOCOL_PCUI,           "pcui"}, //PCUI
    {NO_HW_USB_IF_PROTOCOL_DIAG,           "3g_diag"}, //diag
    {NO_HW_USB_IF_PROTOCOL_PCSC,           "pcsc"},    //���ܿ�
    {NO_HW_USB_IF_PROTOCOL_GPS,            "a_shell"}, //shell��
    {NO_HW_USB_IF_PROTOCOL_CTRL,           "gps_ctl"}, //
    {NO_HW_USB_IF_PROTOCOL_NDIS,           "ndis"},    //������
    {NO_HW_USB_IF_PROTOCOL_NDISDATA,       "ndisData"},//������
    {NO_HW_USB_IF_PROTOCOL_NDISCTRL,       "ndisCtrl"},//������
    {NO_HW_USB_IF_PROTOCOL_BLUETOOTH,      "c_shell"}, //chsell
    {NO_HW_USB_IF_PROTOCOL_FINGERPRINT,    "finger"},  //ָ��
    {NO_HW_USB_IF_PROTOCOL_ACMCTRL,        "acmCtrl"}, //�ɴ���
    {NO_HW_USB_IF_PROTOCOL_MMS,            "mms"},     //���ſ�
    {NO_HW_USB_IF_PROTOCOL_PCVOICE,        "voice"},//pc����
    {NO_HW_USB_IF_PROTOCOL_DVB,            "dvb"},     //���ӿ�
    /*�����˿����ƴ�3G  ���һ�Ϊ����*/
    {NO_HW_USB_IF_PROTOCOL_3G_PCUI ,       "pcui"},   //modem��
    {NO_HW_USB_IF_PROTOCOL_3G_DIAG,        "3g_diag"},    //������
    {NO_HW_USB_IF_PROTOCOL_3G_GPS,         "a_shell"},    //AT��
    {NO_HW_USB_IF_PROTOCOL_3G_PCVOICE,     "voice"}, //��Ͽ�
    {NO_HW_USB_IF_PROTOCOL_NCM,            "ncm"},     // ����
    {NO_HW_USB_IF_PROTOCOL_SHEEL_A,        "a_shell"},   //a shell ��
    {NO_HW_USB_IF_PROTOCOL_SHEEL_B,        "c_cshell"},     //c shell ��
    {NO_HW_USB_IF_PROTOCOL_COMM_A,         "comm_a"},   //ͨ�ô���A
    {NO_HW_USB_IF_PROTOCOL_COMM_B,         "comm_b"},   //ͨ�ô���A
    {NO_HW_USB_IF_PROTOCOL_COMM_C,         "comm_c"},   //ͨ�ô���C
    {NO_HW_USB_IF_PROTOCOL_COMM_GNSS,      "gnss"},   //GNSS�˿ڣ���ԭ��GPS�˿ڣ�

};

/*��PNP �̶��˿���̬����������չ��Ҫ��ports_enum_mode����һ��*/
/*��д�˿����ʱע���ַ���,�Լ��˿�˳��*/
hw_usb_mode g_usb_port_mode_info[] =
{
    {
        CDROM_MODE,
        {"mass"},
        CDROM_SCENE_PID,    USB_CLASS_PER_INTERFACE,
        EXISTS,     NON_EXISTS
    },

    {
        RNDIS_DEBUG_MODE,
        {"rndis", "pcui", "c_shell", "a_shell", "3g_diag", "gps", "4g_diag"},
        RNDIS_DEBUG_PID,    USB_CLASS_PER_INTERFACE,    NON_EXISTS, NON_EXISTS
    },
    {
        RNDIS_DEBUG_MODE_SD,
        {"rndis", "pcui", "c_shell", "a_shell", "3g_diag", "gps", "4g_diag", "mass_two"},
        RNDIS_DEBUG_PID,    USB_CLASS_PER_INTERFACE,    NON_EXISTS, EXISTS
    },
    {
        ECM_DEBUG_MODE,
        {"ecm", "pcui", "c_shell", "a_shell", "3g_diag", "gps", "4g_diag"},
        RNDIS_DEBUG_PID,    USB_CLASS_COMM,             NON_EXISTS, NON_EXISTS
    },

    {
        ECM_DEBUG_MODE_SD,
        {"ecm", "pcui", "c_shell", "a_shell", "3g_diag", "gps", "4g_diag", "mass_two"},
        RNDIS_DEBUG_PID,    USB_CLASS_COMM,             NON_EXISTS, EXISTS
    },
    {/*RNDIS DOWNLOAD*/
        PCUI_DIAG_MODE,
        {"pcui", "mass"},
        DOWNLOAD_SCENE_PID, USB_CLASS_PER_INTERFACE,    EXISTS, NON_EXISTS
    },

    {/*e5/stick DOWNLOAD*/
        DIAG_PCUI_MODE_EX,
        {"a_shell", "mass", "pcui"},
        DOWNLOAD_SCENE_PID_E5, USB_CLASS_PER_INTERFACE,  EXISTS, NON_EXISTS
    },

    {/*MBIM DOWNLOAD*/
        MBIM_DOWNLOAD_MODE,
        {"pcui", "mass"},
        MBIM_DOWNLOAD_PID, USB_CLASS_PER_INTERFACE,     NON_EXISTS, NON_EXISTS
    },

    {
        PCUI_DIAG_MODE_FACTORY,
        {"a_shell", "3g_diag", "pcui"},
        DOWNLOAD_SCENE_PID_E5, USB_CLASS_PER_INTERFACE,  NON_EXISTS, NON_EXISTS
    },
    {
        MBIM_SWITCH_DEBUG_MODE,
        {"ncm", "pcui", "c_shell", "a_shell", "3g_diag", "gps", "4g_diag"},
        MBIM_DEBUG_MODE_PID, USB_CLASS_PER_INTERFACE,   NON_EXISTS, NON_EXISTS
    },

    {
        MBIM_SWITCH_NORMAL_MODE,
        {"ncm"},
        PRODUCT_ID,         USB_CLASS_PER_INTERFACE,    NON_EXISTS, NON_EXISTS
    },
    {
        NCM_PCUI_GPS_4GDIAG_3GDIAG_CPE,
        {"ncm", "pcui", "gps", "3g_diag", "4g_diag"},
        PID_USER,           USB_CLASS_PER_INTERFACE,    NON_EXISTS, NON_EXISTS
    },
    {
        MODEM_DIAG_PCUI_GATEWAY,
        {"3g_modem", "3g_diag", "pcui"},
        LOW_LINUX_PID,      USB_CLASS_PER_INTERFACE,    NON_EXISTS, NON_EXISTS
    },
    {
        MODEM_DIAG_PCUI_NCM_GATEWAY,
        {"3g_modem", "3g_diag", "pcui", "ncm"},
        GATEWAY_NDIS_PID,   USB_CLASS_COMM,             NON_EXISTS, EXISTS
    },

    {
        POWER_OFF_MODE,
        {"mass"},
        POWER_OFF_CDROM_PID, USB_CLASS_PER_INTERFACE,
        EXISTS,     NON_EXISTS
    },
    
#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
    {
        FTEN_USB_SWITCH_MODE,
        {"pcui", "3g_modem"},
        FTEN_MODE_PID, USB_CLASS_COMM,    NON_EXISTS, NON_EXISTS
    },
#endif
};

static void android_cleanup_functions(struct android_usb_function** functions)
{
    struct android_usb_function* f;
    struct device_attribute** attrs;
    struct device_attribute* attr;

    while (*functions)
    {
        f = *functions++;

        if (f->dev)
        {
            attrs = f->attributes;

            if (attrs)
            {
                while ((attr = *attrs++))
                { device_remove_file(f->dev, attr); }
            }
            device_destroy(android_class, f->dev->devt);
            kfree(f->dev_name);
        }
        else
        { continue; }

        if (f->cleanup)
        { f->cleanup(f); }
    }
#ifdef MBB_USB_UNITARY_Q
#else
    gether_cleanup();
    gacm_cleanup();
#endif
}


static void android_work(struct work_struct* data)
{
    struct android_dev* dev = container_of(data, struct android_dev, work);
    struct usb_composite_dev* cdev = dev->cdev;
    char* disconnected[2] = { "USB_STATE=DISCONNECTED", NULL };
    char* connected[2]    = { "USB_STATE=CONNECTED", NULL };
    char* configured[2]   = { "USB_STATE=CONFIGURED", NULL };
    char* suspended[2]   = { "USB_STATE=SUSPENDED", NULL };
    char* resumed[2]   = { "USB_STATE=RESUMED", NULL };
    char** uevent_envp = NULL;
    static enum android_device_state last_uevent, next_state;
    unsigned long flags;
    int pm_qos_vote = -1;
    spin_lock_irqsave(&cdev->lock, flags);

    if (dev->suspended != dev->sw_suspended && cdev->config)
    {
        if (strncmp(dev->pm_qos, "low", 3))
        { pm_qos_vote = dev->suspended ? 0 : 1; }

        next_state = dev->suspended ? USB_SUSPENDED : USB_RESUMED;
        uevent_envp = dev->suspended ? suspended : resumed;
    }
    else if (cdev->config)
    {
        uevent_envp = configured;
        next_state = USB_CONFIGURED;
    }
    else if (dev->connected != dev->sw_connected)
    {
        uevent_envp = dev->connected ? connected : disconnected;
        next_state = dev->connected ? USB_CONNECTED : USB_DISCONNECTED;

        if (dev->connected && strncmp(dev->pm_qos, "low", 3))
        { pm_qos_vote = 1; }
        else if (!dev->connected || !strncmp(dev->pm_qos, "low", 3))
        { pm_qos_vote = 0; }
    }

    dev->sw_connected = dev->connected;
    dev->sw_suspended = dev->suspended;
    spin_unlock_irqrestore(&cdev->lock, flags);
#ifdef MBB_USB_UNITARY_Q
    if (pm_qos_vote != -1)
    { android_pm_qos_update_latency(dev, pm_qos_vote); }
#else
    DBG_I(MBB_PNP, "pm_qos_vote: %d\n", pm_qos_vote);
#endif

    if (uevent_envp)
    {
        /*
         * Some userspace modules, e.g. MTP, work correctly only if
         * CONFIGURED uevent is preceded by DISCONNECT uevent.
         * Check if we missed sending out a DISCONNECT uevent. This can
         * happen if host PC resets and configures device really quick.
         */
        if (((uevent_envp == connected) &&
             (last_uevent != USB_DISCONNECTED)) ||
            ((uevent_envp == configured) &&
             (last_uevent == USB_CONFIGURED)))
        {
            pr_info("%s: sent missed DISCONNECT event\n", __func__);
            kobject_uevent_env(&dev->dev->kobj, KOBJ_CHANGE,
                               disconnected);
            msleep(20);
        }

        /*
         * Before sending out CONFIGURED uevent give function drivers
         * a chance to wakeup userspace threads and notify disconnect
         */
        if (uevent_envp == configured)
        { msleep(50); }

        /* Do not notify on suspend / resume */
        if (next_state != USB_SUSPENDED && next_state != USB_RESUMED)
        {

            kobject_uevent_env(&dev->dev->kobj, KOBJ_CHANGE,
                               uevent_envp);
            last_uevent = next_state;
        }

        pr_info("%s: sent uevent %s\n", __func__, uevent_envp[0]);
    }
    else
    {
        pr_info("%s: did not send uevent (%d %d %p)\n", __func__,
                dev->connected, dev->sw_connected, cdev->config);
    }

}

static int android_enable(struct android_dev* dev);
static void android_disable(struct android_dev* dev);

static ssize_t enable_store(struct device* pdev, struct device_attribute* attr,
                            const char* buff, size_t size)
{
    struct android_dev* dev = dev_get_drvdata(pdev);
    struct usb_composite_dev* cdev = dev->cdev;
    struct android_usb_function* f;
    struct android_configuration* conf;
    USB_INT vbus_status = usb_get_hotplug_status();
    int enabled = 0;
    bool audio_enabled = false;
#ifdef MBB_USB_UNITARY_Q
    static DEFINE_RATELIMIT_STATE(rl, 10 * HZ, 1);
#endif
    //int err = 0;

    if (!cdev)
    { return -ENODEV; }

    mutex_lock(&dev->mutex);
    sscanf(buff, "%d", &enabled);

    if (enabled && !dev->enabled)
    {
        list_for_each_entry(conf, &dev->android_configs, list_item)
        list_for_each_entry(f, &conf->enabled_functions,
                            enabled_list)
        {
            if (f->enable)
            { f->enable(f); }

            if (!strncmp(f->name,
                         "audio_source", 12))
            { audio_enabled = true; }
        }

        if (audio_enabled)
        { msleep(100); }

        mutex_unlock(&dev->mutex);

        dev->irq_ctl_port = 1;

        if (vbus_status)
        {
            pnp_probe();
        }

        mutex_lock(&dev->mutex);
    }
    else if (!enabled && dev->enabled)
    {
        android_disable(dev);
        list_for_each_entry(conf, &dev->android_configs, list_item)
        list_for_each_entry(f, &conf->enabled_functions,
                            enabled_list)
        {
            if (f->disable)
            { f->disable(f); }
        }
        dev->enabled = false;
    }

#ifdef MBB_USB_UNITARY_Q
    else if (__ratelimit(&rl))
#else
    else
#endif
    {
        pr_err("android_usb: already %s\n",
               dev->enabled ? "enabled" : "disabled");
    }

    mutex_unlock(&dev->mutex);

    return size;
}

USB_VOID pnp_check_daynamic_sn_flag(USB_VOID)
{
    mbb_usb_nv_info_st* usb_nv_info = usb_nv_get_ctx();
#ifdef MBB_USB_UNITARY_Q
    /* �л�ǰSN �̶�. NV�����л���SN*/
    if (( 0 == usb_nv_info->stUSBNvSnSupp.sn_enable))
    {
        //null sn win8 unknown device
        DBG_I(MBB_PNP, " auto sn\n");
        g_pnp_info.is_daynamic_sn = 0x01;
    }
#else
    /* �л�ǰSN �̶�. NV�����л���SN*/
    if (( 0 == usb_nv_info->stUSBNvSnSupp.usbSnNvStatus))
    {
        //null sn win8 unknown device
        DBG_T(MBB_PNP, " auto sn\n");
        g_pnp_info.is_daynamic_sn = 0x01;
    }
#endif
}


USB_VOID pnp_accessory_disconnect(USB_VOID)
{
#ifdef MBB_USB_UNITARY_Q
    /* accessory HID support can be active while the
       accessory function is not actually enabled,
       so we need to inform it when we are disconnected.
     */
    acc_disconnect();
#endif
}

USB_INT pnp_status_check_factory(USB_VOID)
{
    DBG_I(MBB_PNP, "\n");
#ifdef MBB_USB_UNITARY_Q
#ifdef MBB_FACTORY_FEATURE
    /*��Ƭ�汾ֱ���ϱ���˿�*/
    g_pnp_info.current_port_style   = factory_port_style;
    g_pnp_info.portModeIndex        = PCUI_DIAG_MODE_FACTORY;
    DBG_T(MBB_PNP, " COMPLETE\n");
    return PNP_CHECK_DEVICE_STATUS_COMPLETE;
#else
    DBG_I(MBB_PNP, "return CONTINUE\n");
    return PNP_CHECK_DEVICE_STATUS_CONTINUE;
#endif/*MBB_FACTORY_FEATURE*/
#else
    mbb_usb_nv_info_st* usb_nv_info = usb_nv_get_ctx();

    if (0 == usb_nv_info->factory_mode)
    {
        /*���CPE�걻�򿪣��򷵻�CPE�˿�����*/
#ifdef USB_CPE
        g_pnp_info.portModeIndex        = NCM_PCUI_GPS_4GDIAG_3GDIAG_CPE;
#else
        g_pnp_info.current_port_style   = factory_port_style;
        g_pnp_info.portModeIndex        = PCUI_DIAG_MODE_FACTORY;
        // g_pnp_info.app_start_mode   = CTL_APP_DISABLE;
#endif/*USB_CPE*/
        DBG_T(MBB_PNP, " COMPLETE\n");
        return PNP_CHECK_DEVICE_STATUS_COMPLETE;
    }
    DBG_I(MBB_PNP, "return CONTINUE\n");
    return PNP_CHECK_DEVICE_STATUS_CONTINUE;
#endif/*MBB_USB_UNITARY_Q*/
}

#ifdef USB_HILINK_MODEM_SWITCH
USB_VOID pnp_read_hilink_modem_flag(USB_VOID)
{
    USB_INT fd    = 0;
    mm_segment_t fs;
    USB_CHAR hilink_mode ;

    fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_open(USB_CONFIG_HILINK_MODEM_PATH, O_RDONLY, 0);
    if (fd >= 0)
    {
        sys_read(fd, &hilink_mode, 1);
    }
    else
    {
        DBG_I(MBB_PNP, "no flag path\n");
    }
    sys_close(fd);
    set_fs(fs);

    if (HILINK_MODEM_MODE_FALG == hilink_mode)
    {
        DBG_T(MBB_PNP, "MODEM_MODE\n");
        g_pnp_info.hilink_mode = HILINK_MODEM_MODE;
    }
    else if (HILINK_MODEM_DEBUG_MODE_FALG == hilink_mode)
    {
        DBG_T(MBB_PNP, "MODEM_DEBUG_MODE\n");
        g_pnp_info.hilink_mode  = HILINK_MODEM_DEBUG_MODE;
    }
}
#endif

static ssize_t smode_show(struct device* pdev, struct device_attribute* attr,
                          char* buf)
{
    int fd    = 0;
    mm_segment_t fs;
    char modem_mode   = '1';

    fs = get_fs();
    set_fs(KERNEL_DS);
    fd = sys_open(USB_CONFIG_HILINK_MODEM_PATH, O_RDONLY, 0);
    if (fd >= 0)
    {
        sys_read(fd, &modem_mode, 1);
    }
    else
    {
        DBG_I(MBB_PNP, " mode %c\n", modem_mode);
    }
    sys_close(fd);
    set_fs(fs);
    DBG_T(MBB_PNP, " mode %c\n", modem_mode);
    return 0;
}

static ssize_t
smode_store(struct device* pdev, struct device_attribute* attr,
            const char* buff, size_t size)
{
    int value;
    if (1 == sscanf(buff, "%4d", &value))
    {
        DBG_T(MBB_PNP, "smode_store %d\n", value);
    }
    return -1;
}


USB_VOID pnp_init_device_descriptor(struct usb_composite_dev* cdev)
{
    /*config cdev desc*/
    cdev->desc.bLength          = sizeof(struct usb_device_descriptor);
    cdev->desc.bDescriptorType  = USB_DT_DEVICE;
    cdev->desc.bcdUSB           = __constant_cpu_to_le16(0x0200);
#ifdef MBB_USB_UNITARY_Q
    cdev->desc.bcdDevice        = USB_BCDDEVICE_GAOTONG;
#else
    cdev->desc.bcdDevice        = USB_BCDDEVICE_BALONG;
#endif
    cdev->desc.idVendor         = __constant_cpu_to_le16(VENDOR_ID_HUAWEI);

    cdev->desc.bDeviceSubClass  = 0;

    /*��������Ĭ��ֵPNP��������*/
    cdev->desc.idProduct        = __constant_cpu_to_le16(PRODUCT_ID);
    cdev->desc.bDeviceClass     = USB_CLASS_PER_INTERFACE;
    cdev->desc.bDeviceProtocol  = 0;

#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
    if (FTEN_USB_DESC_FTEN == get_ften_desc_flag())
    {
        cdev->desc.bcdDevice        = __constant_cpu_to_le16(0x0000);
        cdev->desc.idVendor         = __constant_cpu_to_le16(FTEN_VENDOR_ID);
        cdev->desc.idProduct = __constant_cpu_to_le16(FTEN_MODE_PID);
        cdev->desc.bDeviceClass     = 0x02;
        cdev->desc.bDeviceSubClass  = 0;
        cdev->desc.bDeviceProtocol  = 0;
    }
#endif
}

USB_VOID pnp_usb_init_enum_stat(USB_VOID)
{

#ifdef MBB_USB_UNITARY_Q
#else
    bsp_usb_init_enum_stat();
#endif
    setmode_state = -1;
}

/*****************************************************************
Parameters    :  ��Ҫʹ�ܶ˿ڵ�����
Return        : 0:δʹ��1:ʹ��
Description   :  ��ѯ�˿��Ƿ�ʹ�ܣ��ⲿֱ�ӵ���
*****************************************************************/
#ifdef USB_SECURITY
int usb_port_enable(char *name)
{
    mbb_usb_nv_info_st *usb_nv_ctx = usb_nv_get_ctx();

    if (NULL == name)
    {
        DBG_E(MBB_PNP, " name is null\n");
        return 0;
    }
    else if (0 == strcmp(name, "diag"))
    {
        return usb_nv_ctx->usb_security_flag.diag_enable;
    }
    else if (0 == strcmp(name, "shell"))
    {
        return usb_nv_ctx->usb_security_flag.shell_enable;
    }
    else if (0 == strcmp(name, "adb"))
    {
        return usb_nv_ctx->usb_security_flag.adb_enable;
    }
    else if (0 == strcmp(name, "om"))
    {
#if (FEATURE_ON == MBB_PCVOICE)
        return 1;
#else
        return usb_nv_ctx->usb_security_flag.om_enable;
#endif
    }
    else
    {
        return 0;
    }   
}
#else
int usb_port_enable(char *name)
{
    DBG_I(MBB_PNP, "no lock\n");
    return 0;
}
#endif /* MBB_USB_UNITARY_Q */


USB_VOID pnp_usb_queue_delay_work(struct delayed_work* dwork, unsigned long delay)
{
    //queue_delayed_work(system_nrt_wq, dwork, delay);
    adp_usb_queue_delay_work(dwork, delay);
}

USB_INT pnp_set_gateway_mode(USB_VOID)
{
    USB_INT ret = MBB_USB_ERROR;
    switch (g_pnp_info.rewind_param.bProFile)
    {
        case GATEWAT_MODEM_MODE:
            DBG_T(MBB_PNP, "gateway GATEWAT_MODEM_MODE\n");
            g_pnp_info.portModeIndex = MODEM_DIAG_PCUI_GATEWAY;
#if (FEATURE_ON == MBB_FEATURE_GATEWAY)
            SetGatewayWorkMode(CONFIG_GATEWAY_MODEM);
#endif
            ret = MBB_USB_OK;
            break;
        case GATEWAY_NDIS_MODE:
            DBG_T(MBB_PNP, "gateway GATEWAY_NDIS_MODE\n");
            g_pnp_info.portModeIndex = MODEM_DIAG_PCUI_NCM_GATEWAY;
#if (FEATURE_ON == MBB_FEATURE_GATEWAY)
            SetGatewayWorkMode(CONFIG_GATEWAY_NDIS);
#endif
            ret = MBB_USB_OK;
            break;
        default:
            DBG_E(MBB_PNP, "unknown gateway rewind command\n");
            break;
    }
    return ret;
}

#ifdef USB_DLOAD
/******************************************************************************
*Function:           dload_report_port_status
*Description:        ��usbģ���ϱ��˿�״ֵ̬
*Calls:              
*Input:              
*Output:             NA
*Return:             0: normal, 1: ����pcui�� 2: ����ģʽ����, 3: nv�ָ�ģʽ����
*Others:             NA
******************************************************************************/

extern int dload_report_port_status(void);
#else
static int dload_report_port_status(void)
{
    DBG_T(MBB_PNP, "no USB_DLOAD normal mode\n");
    return 0;
}
#endif


USB_INT pnp_get_dload_flag(USB_VOID)
{
    int dload_flag = PORT_NORMAL;
    struct android_dev* dev = android_get_android_dev();
    
    dload_flag = dload_report_port_status();
    /*һ������NV���ݻָ��׶���Ҫ����PCUI�ڣ���Q�˶Խ�*/
    if ( PORT_NV_RES == dload_flag)
    {
        DBG_T(MBB_PNP, "PORT_NV_RES MODE\n");
#ifdef MBB_USB_UNITARY_Q
        memset(serial_transports, 0, 32);
        strncpy(serial_transports, "smd", 32 - 1);
#endif
    }
    /*һ��������Ҫ����PCUI�ڣ���A7Ӧ�öԽ�*/
    if ( PORT_DLOAD == dload_flag)
    {
        is_in_dload = 1;
        DBG_T(MBB_PNP, "PORT_DLOAD MODE\n");
#ifdef MBB_USB_UNITARY_Q
        memset(serial_transports, 0, 32);
        strncpy(serial_transports, "tty", 32 - 1);
        dwc3_gadget_set_timeout(USB_NUM_1);
        dev->irq_ctl_port = MBB_USB_ENABLE;
#endif
    }

    return dload_flag;

}

#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
USB_INT pnp_get_dload_flag_ften(USB_VOID)
{
    int dload_flag = PORT_NORMAL;
    struct android_dev* dev = android_get_android_dev();
    dload_flag = dload_report_port_status();
  
    return dload_flag;
}
#endif

/*****************************************************************
Parameters    :  ��
Return        :    1: �ػ�  0:����ػ�
Description   :  ��ȡ��ػ�״̬
*****************************************************************/
USB_INT usb_power_off_chg_stat(USB_VOID)
{
    return (DRV_START_MODE_CHARGING == bsp_start_mode_get());
}

pnp_dynamic_mode* pnp_dynamic_port_get_mode(USB_UCHAR port_index);


/*************************************************
  Function:    Query_USB_PortType
  Description: AT^dialmode����ֵ
  Calls:       list_for_each_entry
  Called By:   BSP_USB_GetDiagModeValue
  Input:       pucDialmode ���ŷ�ʽ
               pucCdcSpec  CDC�淶
  Output:      ucDialmode:  0: Modem����; 1: NDIS����; 2: Modem��NDIS����
               ucCdcSpec:   0: Modem/NDIS��������CDC�淶;
                            1: Modem����CDC�淶;
                            2: NDIS����CDC�淶;
                            3: Modem/NDIS������CDC��
  Return:        �ɹ�����0��ʧ�ܷ���1
*************************************************/
USB_INT Query_USB_PortType(USB_UINT* pucDialmode, USB_UINT* pucCdcSpec)
{
    struct android_dev* dev = android_get_android_dev();
    struct usb_composite_dev* cdev = dev->cdev;
    struct usb_configuration*   c = cdev->config;
    struct android_configuration* conf =
        container_of(c, struct android_configuration, usb_config);
    struct android_usb_function* f = NULL;

    USB_INT   dail_modem = 0;
    USB_INT   dail_ndis = 0;

    if (NULL == pucDialmode || NULL == pucCdcSpec)
    {
        DBG_E(MBB_DEBUG, "NULL point\n");
        return 1;
    }

    list_for_each_entry(f, &conf->enabled_functions, enabled_list)   //������ѯ��ǰ�ϱ��Ķ˿���Ϣ
    {
        if ((!strcmp("modem", f->name))
            || (!strcmp("3g_modem", f->name)) )            //�ж��Ƿ��ϱ���MODEM�˿�
        {
            dail_modem = 1;
        }

        if ((!strcmp("rmnet", f->name))     
            || (!strcmp("ncm", f->name)))                //�ж��Ƿ��ϱ���Ndis�˿�
        {
            dail_ndis = 1;
        }
    }

    if ((1 == dail_modem) && (1 == dail_ndis))
    {
        *pucDialmode = DIAL_MODE_MODEM_N_NDIS;   //MODEM ��NDIS���ŷ�ʽ����
        *pucCdcSpec =  CDC_SPEC_MODEM_N_NDIS;    //Modem/NDIS������CDC��
    }
    else if (1 == dail_ndis)
    {
        *pucDialmode = DIAL_MODE_NDIS;  //����NDIS���ŷ�ʽ
        *pucCdcSpec =  CDC_SPEC_NDIS;   //NDIS����CDC�淶
    }
    else if (1 == dail_modem)
    {
        *pucDialmode = DIAL_MODE_MODEM;  //����MODEM���ŷ�ʽ
        *pucCdcSpec =  CDC_SPEC_MODEM;   //Modem����CDC�淶
    }
    else
    {
        *pucCdcSpec = CDC_SPEC_NONE;    // Modem/NDIS��������CDC�淶;
    }
    return 0;
}

void  str_upper(char* str)
{
    unsigned int i = 0;

    if ( NULL == str)
    {
        return ;
    }
    for (i = 0; i < strlen(str); i++)
    {
        if ((str[i] >= 'a') && (str[i] <= 'z'))
        {
            str[i] -= 32; /*32Ϊ��д��Сд֮��Ĳ�ֵ*/
        }
    }
    return ;
}

/*************************************************
  Function:         Check_EnablePortName
  Description:     ��ѯ��ǰ�����ϱ��Ķ˿�
  Calls:              list_for_each_entry
  Called By:        BSP_USB_GetPortMode(char*PsBuffer, unsigned long*Length )
  Input:             PsBuffer   �����ѯ���Ķ˿����Ƽ��˿��ϱ���˳��
                        Length     ��¼*PsBuffer���ַ����ĳ���
  Output:
  Return:         �ɹ�����0��ʧ�ܷ���1
*************************************************/
USB_INT Check_EnablePortName(USB_CHAR* PsBuffer, USB_ULONG* Length)
{
    struct android_dev* dev = android_get_android_dev();
    struct usb_composite_dev* cdev = dev->cdev;
    struct usb_configuration* c = cdev->config;
    struct android_configuration* conf =
        container_of(c, struct android_configuration, usb_config);
    struct android_usb_function* f = NULL;
    USB_UCHAR   PortCount = 0;
    static USB_CHAR* PortSerialNumber[] =
    {
        "0", "1", "2", "3", "4",
        "5", "6", "7", "8", "9",
        "10", "11", "12", "13",
        "14", "15", "16", "17"
    };

    if ( NULL == PsBuffer || NULL == Length )
    {
        return 1;
    }

    list_for_each_entry(f, &conf->enabled_functions, enabled_list)
    {
        //str_upper(f->name);

        strncat(PsBuffer, ",", strlen(","));
        strncat(PsBuffer, f->name, strlen(f->name) );  //�����ѯ���Ķ˿�����
        strncat(PsBuffer, ":", strlen(":"));
        strncat(PsBuffer, PortSerialNumber[PortCount], strlen(PortSerialNumber[PortCount])); //����˿�˳���
        PortCount += 1;   //��¼�ϱ��Ķ˿���
    }

    if ( 0 == PortCount || 0 == strlen(PsBuffer) )
    {
        return 1;
    }

    *Length = strlen(PsBuffer) + 1;  //����PsBuffer �ַ�������
    return 0;
}
/*****************************************************************
 ����Ϊusb��������
*****************************************************************/

USB_INT pnp_status_check_charge_only(USB_VOID)
{
#ifdef MBB_USB_UNITARY_Q
    USB_INT fd = 0;
    mm_segment_t fs;
    char charge_mode = USER_MODE;
    DBG_I(MBB_PNP, "pnp_status_check_charge_only\n");
    fs = get_fs();
    set_fs(KERNEL_DS);
    fd = sys_open(ONLY_CHARGE_PATH, O_RDWR, 0);
    if (fd >= 0)
    {
        sys_read(fd, &charge_mode, 1);
        DBG_I(MBB_PNP, "only_charge_mode %c.\n", charge_mode);
    }
    sys_close(fd);
    set_fs(fs);
    DBG_T(MBB_PNP, " only_charge_mode = %c.\n", charge_mode);
    if (ONLY_CHARGE_MODE == charge_mode)
    {
        g_pnp_info.current_port_style   = charge_port_style;
        /*����籨�ػ����ڣ����̿ɶ�*/
        g_pnp_info.portModeIndex   = POWER_OFF_MODE;
        DBG_T(MBB_PNP, " COMPLETE\n");
        return PNP_CHECK_DEVICE_STATUS_COMPLETE;
    }
#endif
    DBG_I(MBB_PNP, "return CONTINUE\n");
    return PNP_CHECK_DEVICE_STATUS_CONTINUE;
}

/*****************************************************************************
�� �� ��  : pnp_usb_state_get
 ��������  :��ȡUSB��λ״̬
 �������  : ��
 �������  :
 �� �� ֵ  : USB_BOOL
 ���ú���  :
 ��������  :

*****************************************************************************/
USB_INT pnp_usb_state_get(USB_VOID)
{
    USB_INT usb_state = MBB_USB_FALSE;

#ifdef MBB_USB_UNITARY_Q
    usb_state = MBB_USB_TRUE;
#else
    if (bsp_usb_is_support_pmu_detect())
    {
        usb_state = bsp_pmu_usb_state_get();
    }
    else
    {
        usb_state = MBB_USB_TRUE;
    }
#endif

    DBG_I(MBB_PNP, "state %d\n", usb_state);

    return usb_state;
}

/**
   �����setconfig2��ֱ�ӵ��������صĺ������ȶ����������ᵼ�º˼�ͨ��ʧ��
   ���ܳɹ��Ͽ����磬��work�ص����������ػص���
*/
USB_VOID gatway_data_disconnect (struct work_struct* w)
{
    usb_adp_ctx_t* UsbCtx = NULL;

    UsbCtx = usb_get_adp_ctx();
    UsbCtx->usb_switch_gatway_mode_cb(UsbCtx->gatway_work_mode);
    DBG_T(MBB_PNP, "gatway_data_disconnect %d \n", UsbCtx->gatway_work_mode);
}
/*PNP��ά�ɲ⺯��*/
USB_VOID pnp_dump(USB_VOID)
{
    USB_INT i = 0;
    struct usb_gadget*   gadget = _android_dev->cdev->gadget;
    USB_INT speed = (USB_INT)gadget->speed;
    pnp_dynamic_mode* dynamic_port_mode = NULL;

    DBG_T(MBB_DEBUG, "|-------------------------------------------------------\n");
    DBG_T(MBB_DEBUG, "|gadget of '%s' info\n", gadget->name);

    switch (speed)
    {
        case USB_SPEED_SUPER:
            DBG_T(MBB_DEBUG, "|gadget speed------- = superspeed\n");
            break;

        case USB_SPEED_HIGH:
            DBG_T(MBB_DEBUG, "|gadget speed------- = highspeed\n");
            break;

        case USB_SPEED_FULL:
        case USB_SPEED_LOW:
            DBG_T(MBB_DEBUG, "|gadget speed------- = fullspeed\n");
            break;

    }

    DBG_T(MBB_DEBUG, "|sg_supported------- = %d\n", gadget->sg_supported);
    DBG_T(MBB_DEBUG, "|is_otg------------- = %d\n", gadget->is_otg);
    DBG_T(MBB_DEBUG, "|is_a_peripheral---- = %d\n", gadget->is_a_peripheral);
    DBG_T(MBB_DEBUG, "|a_hnp_support------ = %d\n", gadget->a_hnp_support);
    DBG_T(MBB_DEBUG, "|b_hnp_enable------- = %d\n", gadget->b_hnp_enable);
    DBG_T(MBB_DEBUG, "|a_alt_hnp_support-- = %d\n", gadget->a_alt_hnp_support);
#ifdef MBB_USB_UNITARY_Q
    DBG_T(MBB_DEBUG, "|host_request------- = %d\n", gadget->host_request);
    DBG_T(MBB_DEBUG, "|remote_wakeup------ = %d\n", gadget->remote_wakeup);
#else
    DBG_T(MBB_DEBUG, "|is_suspend--------- = %d\n", gadget->is_suspend);
    DBG_T(MBB_DEBUG, "|rwakeup------------ = %d\n", gadget->rwakeup);
#endif
    DBG_T(MBB_DEBUG, "|-------------------------------------------------------\n");

    /*�豸��Ϣ������*/
    if ((NULL != _android_dev) && (NULL != _android_dev->cdev))
    {
        DBG_T(MBB_DEBUG, "|bLength------------ = 0x%X\n", _android_dev->cdev->desc.bLength);
        DBG_T(MBB_DEBUG, "|bDescriptorType---- = 0x%X\n", _android_dev->cdev->desc.bDescriptorType);
        DBG_T(MBB_DEBUG, "|bcdUSB------------- = 0x%4X\n", _android_dev->cdev->desc.bcdUSB);
        DBG_T(MBB_DEBUG, "|bDeviceClass------- = 0x%X\n", _android_dev->cdev->desc.bDeviceClass);
        DBG_T(MBB_DEBUG, "|bDeviceSubClass---- = 0x%X\n", _android_dev->cdev->desc.bDeviceSubClass);
        DBG_T(MBB_DEBUG, "|bDeviceProtocol---- = 0x%X\n", _android_dev->cdev->desc.bDeviceProtocol);
        DBG_T(MBB_DEBUG, "|bMaxPacketSize0---- = 0x%X\n", _android_dev->cdev->desc.bMaxPacketSize0);
        DBG_T(MBB_DEBUG, "|idVendor----------- = 0x%X\n", _android_dev->cdev->desc.idVendor);
        DBG_T(MBB_DEBUG, "|idProduct---------- = 0x%X\n", _android_dev->cdev->desc.idProduct);
        DBG_T(MBB_DEBUG, "|bcdDevice---------- = 0x%X\n", _android_dev->cdev->desc.bcdDevice);
        DBG_T(MBB_DEBUG, "|iManufacturer------ = 0x%X\n", _android_dev->cdev->desc.iManufacturer);
        DBG_T(MBB_DEBUG, "|iProduct----------- = 0x%X\n", _android_dev->cdev->desc.iProduct);
        DBG_T(MBB_DEBUG, "|iSerialNumber------ = 0x%X\n", _android_dev->cdev->desc.iSerialNumber);
        DBG_T(MBB_DEBUG, "|bNumConfigurations- = 0x%X\n", _android_dev->cdev->desc.bNumConfigurations);
    }

    /*PNP������Ϣ*/
    DBG_T(MBB_DEBUG, "|-------------------------------------------------------\n");
    DBG_T(MBB_DEBUG, "|is_in_dload-------- = %d\n", is_in_dload);
    DBG_T(MBB_DEBUG, "|portModeIndex------ = %d\n", g_pnp_info.portModeIndex);
    DBG_T(MBB_DEBUG, "|rewind_sn_daynamic- = %d\n", g_pnp_info.is_daynamic_sn);
    DBG_T(MBB_DEBUG, "|current_port_style- = %d\n", g_pnp_info.current_port_style);
    DBG_T(MBB_DEBUG, "|is_service_switch-- = %d\n", g_pnp_info.is_service_switch);
    DBG_T(MBB_DEBUG, "|app_start_mode----- = %d\n", g_pnp_info.app_start_mode);
    DBG_T(MBB_DEBUG, "|-------------------------------------------------------\n");
    DBG_T(MBB_DEBUG, "|bCmdReserved------- = %X\n", g_pnp_info.rewind_param.bCmdReserved);
    DBG_T(MBB_DEBUG, "|bPcType------------ = %X\n", g_pnp_info.rewind_param.bPcType);
    DBG_T(MBB_DEBUG, "|bTimeOut----------- = %X\n", g_pnp_info.rewind_param.bTimeOut);
    DBG_T(MBB_DEBUG, "|bPID--------------- = %X\n", g_pnp_info.rewind_param.bPID);
    DBG_T(MBB_DEBUG, "|bNewPID------------ = %X\n", g_pnp_info.rewind_param.bNewPID);
    DBG_T(MBB_DEBUG, "|bSupportCD--------- = %X\n", g_pnp_info.rewind_param.bSupportCD);
    DBG_T(MBB_DEBUG, "|bProFile----------- = %X\n", g_pnp_info.rewind_param.bProFile);
    DBG_T(MBB_DEBUG, "|bGreenMode--------- = %X\n", g_pnp_info.rewind_param.bGreenMode);
    DBG_T(MBB_DEBUG, "|-------------------------------------------------------\n");
    DBG_T(MBB_DEBUG, "|manufact_string---- = %s\n", manufacturer_string);
    DBG_T(MBB_DEBUG, "|product_string----- = %s\n", product_string);
    DBG_T(MBB_DEBUG, "|serial_string------ = %s\n", serial_string);
    /*PNP�˿���Ϣ*/
    DBG_T(MBB_DEBUG, "|-------------------------------------------------------\n");
    dynamic_port_mode = pnp_dynamic_port_get_mode(DYNAMIC_REWIND_BEFORE_MODE);
    DBG_T(MBB_DEBUG, "|rewind_before PID---------- = 0x%X\n", dynamic_port_mode->PID);
    DBG_T(MBB_DEBUG, "|rewind_before port_index--- = %d\n", dynamic_port_mode->port_index);

    for (i = 0; i < DYNAMIC_PID_MAX_PORT_NUM; i++)
    {
        if (dynamic_port_mode->mode_buf[i])
        {
            DBG_T(MBB_DEBUG, "|rewind_before_port----[%2d]- = %s \n",
                  i, dynamic_port_mode->mode_buf[i]);
            DBG_T(MBB_DEBUG, "|rewind_before_protocol[%2d]- = 0x%X \n",
                  i, dynamic_port_mode->port_protocol[i]);
        }
        else
        {
            break;
        }
    }

    DBG_T(MBB_DEBUG, "|-------------------------------------------------------\n");
    dynamic_port_mode = pnp_dynamic_port_get_mode(DYNAMIC_REWIND_AFTER_MODE);
    DBG_T(MBB_DEBUG, "|rewind_after PID---------- = 0x%X\n", dynamic_port_mode->PID);
    DBG_T(MBB_DEBUG, "|rewind_after port_index--- = %d\n", dynamic_port_mode->port_index);

    for (i = 0; i < DYNAMIC_PID_MAX_PORT_NUM; i++)
    {
        if (dynamic_port_mode->mode_buf[i])
        {
            DBG_T(MBB_DEBUG, "|rewind_after_port----[%2d]- = %s\n",
                  i, dynamic_port_mode->mode_buf[i]);
            DBG_T(MBB_DEBUG, "|rewind_after_protocol[%2d]- = 0x%X \n",
                  i, dynamic_port_mode->port_protocol[i]);
        }
        else
        {
            break;
        }
    }

    DBG_T(MBB_DEBUG, "|-------------------------------------------------------\n");

}


