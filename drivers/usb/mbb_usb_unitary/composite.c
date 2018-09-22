/*
 * composite.c - infrastructure for Composite USB Gadgets
 *
 * Copyright (C) 2006-2008 David Brownell
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

/* #define VERBOSE_DEBUG */

#include <linux/kallsyms.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/utsname.h>

#include <linux/usb/composite.h>
#include <asm/unaligned.h>
#include <mbb_config.h>
#include "usb_charger_manager.h"
#include "usb_notify.h"
#include "hw_pnp.h"
#include "mbb_usb_adp.h"
/*
 * The code in this file is utility code, used to build a gadget driver
 * from one or more "function" drivers, one or more "configuration"
 * objects, and a "usb_composite_driver" by gluing them together along
 * with the relevant device-wide data.
 */

/* big enough to hold our biggest descriptor */
#define USB_BUFSIZ	1024

static struct usb_composite_driver* composite;
static USB_INT (*composite_gadget_bind)(struct usb_composite_dev* cdev);

/* Some systems will need runtime overrides for the  product identifiers
 * published in the device descriptor, either numbers or strings or both.
 * String parameters are in UTF-8 (superset of ASCII's 7 bit characters).
 */

static ushort idVendor;
module_param(idVendor, ushort, 0);
MODULE_PARM_DESC(idVendor, "USB Vendor ID");

static ushort idProduct;
module_param(idProduct, ushort, 0);
MODULE_PARM_DESC(idProduct, "USB Product ID");

static ushort bcdDevice;
module_param(bcdDevice, ushort, 0);
MODULE_PARM_DESC(bcdDevice, "USB Device version (BCD)");

static char* iManufacturer;
module_param(iManufacturer, charp, 0);
MODULE_PARM_DESC(iManufacturer, "USB Manufacturer string");

static char* iProduct;
module_param(iProduct, charp, 0);
MODULE_PARM_DESC(iProduct, "USB Product string");

static char* iSerialNumber;
module_param(iSerialNumber, charp, 0);
MODULE_PARM_DESC(iSerialNumber, "SerialNumber string");

static char composite_manufacturer[50];


/*-------------------------------------------------------------------------*/
/**
 * next_ep_desc() - advance to the next EP descriptor
 * @t: currect pointer within descriptor array
 *
 * Return: next EP descriptor or NULL
 *
 * Iterate over @t until either EP descriptor found or
 * NULL (that indicates end of list) encountered
 */
static struct usb_descriptor_header**
next_ep_desc(struct usb_descriptor_header** t)
{
    for (; *t; t++)
    {
        if ((*t)->bDescriptorType == USB_DT_ENDPOINT)
        { return t; }
    }
    return NULL;
}

/*
 * for_each_ep_desc()- iterate over endpoint descriptors in the
 *		descriptors list
 * @start:	pointer within descriptor array.
 * @ep_desc:	endpoint descriptor to use as the loop cursor
 */
#define for_each_ep_desc(start, ep_desc) \
    for (ep_desc = next_ep_desc(start); \
         ep_desc; ep_desc = next_ep_desc(ep_desc+1))

/**
 * config_ep_by_speed() - configures the given endpoint
 * according to gadget speed.
 * @g: pointer to the gadget
 * @f: usb function
 * @_ep: the endpoint to configure
 *
 * Return: error code, 0 on success
 *
 * This function chooses the right descriptors for a given
 * endpoint according to gadget speed and saves it in the
 * endpoint desc field. If the endpoint already has a descriptor
 * assigned to it - overwrites it with currently corresponding
 * descriptor. The endpoint maxpacket field is updated according
 * to the chosen descriptor.
 * Note: the supplied function should hold all the descriptors
 * for supported speeds
 */
USB_INT config_ep_by_speed(struct usb_gadget* g,
                           struct usb_function* f,
                           struct usb_ep* _ep)
{
    struct usb_endpoint_descriptor* chosen_desc = NULL;
    struct usb_descriptor_header** speed_desc = NULL;

    struct usb_ss_ep_comp_descriptor* comp_desc = NULL;
    USB_INT want_comp_desc = 0;

    struct usb_descriptor_header** d_spd; /* cursor for speed desc */

    if (!g || !f || !_ep)
    { return -EIO; }

    /* select desired speed */
    switch (g->speed)
    {
        case USB_SPEED_SUPER:
            if (gadget_is_superspeed(g))
            {
                speed_desc = f->ss_descriptors;
                want_comp_desc = 1;
                break;
            }
            /* else: Fall trough */
        case USB_SPEED_HIGH:
            if (gadget_is_dualspeed(g))
            {
                speed_desc = f->hs_descriptors;
                break;
            }
            /* else: fall through */
        default:
            speed_desc = f->descriptors;
    }
    /* find descriptors */
    for_each_ep_desc(speed_desc, d_spd)
    {
        chosen_desc = (struct usb_endpoint_descriptor*)*d_spd;
        if (chosen_desc->bEndpointAddress == _ep->address)
        { goto ep_found; }
    }
    return -EIO;

ep_found:
    /* commit results */
    _ep->maxpacket = usb_endpoint_maxp(chosen_desc);
    _ep->desc = chosen_desc;
    _ep->comp_desc = NULL;
    _ep->maxburst = 0;
    _ep->mult = 0;
    if (!want_comp_desc)
    { return 0; }

    /*
     * Companion descriptor should follow EP descriptor
     * USB 3.0 spec, #9.6.7
     */
    comp_desc = (struct usb_ss_ep_comp_descriptor*) * (++d_spd);
    if (!comp_desc ||
        (comp_desc->bDescriptorType != USB_DT_SS_ENDPOINT_COMP))
    { return -EIO; }
    _ep->comp_desc = comp_desc;
    if (g->speed == USB_SPEED_SUPER)
    {
        switch (usb_endpoint_type(_ep->desc))
        {
            case USB_ENDPOINT_XFER_ISOC:
                /* mult: bits 1:0 of bmAttributes */
                _ep->mult = comp_desc->bmAttributes & 0x3;
            case USB_ENDPOINT_XFER_BULK:
            case USB_ENDPOINT_XFER_INT:
                _ep->maxburst = comp_desc->bMaxBurst;
                break;
            default:
                /* Do nothing for control endpoints */
                break;
        }
    }
    return 0;
}

/**
 * usb_add_function() - add a function to a configuration
 * @config: the configuration
 * @function: the function being added
 * Context: single threaded during gadget setup
 *
 * After initialization, each configuration must have one or more
 * functions added to it.  Adding a function involves calling its @bind()
 * method to allocate resources such as interface and string identifiers
 * and endpoints.
 *
 * This function returns the value of the function's bind(), which is
 * zero for success else a negative errno value.
 */
USB_INT usb_add_function(struct usb_configuration* config,
                         struct usb_function* function)
{
    USB_INT	value = -EINVAL;

    DBG_E(MBB_PNP, "adding '%s'/%p to config '%s'/%p\n",
          function->name, function,
          config->label, config);

    if (!function->set_alt || !function->disable)
    { goto done; }

    function->config = config;
    list_add_tail(&function->list, &config->functions);

    /* REVISIT *require* function->bind? */
    if (function->bind)
    {
        value = function->bind(config, function);
        if (value < 0)
        {
            list_del(&function->list);
            function->config = NULL;
        }
    }
    else
    { value = 0; }

    /* We allow configurations that don't work at both speeds.
     * If we run into a lowspeed Linux system, treat it the same
     * as full speed ... it's the function drivers that will need
     * to avoid bulk and ISO transfers.
     */
    if (!config->fullspeed && function->descriptors)
    { config->fullspeed = true; }
    if (!config->highspeed && function->hs_descriptors)
    { config->highspeed = true; }
    if (!config->superspeed && function->ss_descriptors)
    { config->superspeed = true; }

done:
    if (value)
        DBG_E(MBB_PNP, "adding '%s'/%p --> %d\n",
              function->name, function, value);
    return value;
}

/**
 * usb_function_deactivate - prevent function and gadget enumeration
 * @function: the function that isn't yet ready to respond
 *
 * Blocks response of the gadget driver to host enumeration by
 * preventing the data line pullup from being activated.  This is
 * normally called during @bind() processing to change from the
 * initial "ready to respond" state, or when a required resource
 * becomes available.
 *
 * For example, drivers that serve as a passthrough to a userspace
 * daemon can block enumeration unless that daemon (such as an OBEX,
 * MTP, or print server) is ready to handle host requests.
 *
 * Not all systems support software control of their USB peripheral
 * data pullups.
 *
 * Returns zero on success, else negative errno.
 */
USB_INT usb_function_deactivate(struct usb_function* function)
{
    struct usb_composite_dev*	cdev = function->config->cdev;
    USB_ULONG			flags;
    USB_INT				status = 0;

    spin_lock_irqsave(&cdev->lock, flags);

    if (cdev->deactivations == 0)
    { status = usb_gadget_disconnect(cdev->gadget); }
    if (status == 0)
    { cdev->deactivations++; }

    spin_unlock_irqrestore(&cdev->lock, flags);
    return status;
}

/**
 * usb_function_activate - allow function and gadget enumeration
 * @function: function on which usb_function_activate() was called
 *
 * Reverses effect of usb_function_deactivate().  If no more functions
 * are delaying their activation, the gadget driver will respond to
 * host enumeration procedures.
 *
 * Returns zero on success, else negative errno.
 */
USB_INT usb_function_activate(struct usb_function* function)
{
    struct usb_composite_dev*	cdev = function->config->cdev;
    USB_INT				status = 0;

    spin_lock(&cdev->lock);

    if (WARN_ON(cdev->deactivations == 0))
    { status = -EINVAL; }
    else
    {
        cdev->deactivations--;
        if (cdev->deactivations == 0)
        { status = usb_gadget_connect(cdev->gadget); }
    }

    spin_unlock(&cdev->lock);
    return status;
}

/**
 * usb_interface_id() - allocate an unused interface ID
 * @config: configuration associated with the interface
 * @function: function handling the interface
 * Context: single threaded during gadget setup
 *
 * usb_interface_id() is called from usb_function.bind() callbacks to
 * allocate new interface IDs.  The function driver will then store that
 * ID in interface, association, CDC union, and other descriptors.  It
 * will also handle any control requests targeted at that interface,
 * particularly changing its altsetting via set_alt().  There may
 * also be class-specific or vendor-specific requests to handle.
 *
 * All interface identifier should be allocated using this routine, to
 * ensure that for example different functions don't wrongly assign
 * different meanings to the same identifier.  Note that since interface
 * identifiers are configuration-specific, functions used in more than
 * one configuration (or more than once in a given configuration) need
 * multiple versions of the relevant descriptors.
 *
 * Returns the interface ID which was allocated; or -ENODEV if no
 * more interface IDs can be allocated.
 */
USB_INT usb_interface_id(struct usb_configuration* config,
                         struct usb_function* function)
{
    USB_INT id = config->next_interface_id;

    if (id < MAX_CONFIG_INTERFACES)
    {
        config->interface[id] = function;
        config->next_interface_id = id + 1;
        return id;
    }
    return -ENODEV;
}

static USB_INT config_buf(struct usb_configuration* config,
                          enum usb_device_speed speed, void* buf, USB_UCHAR type)
{
    struct usb_config_descriptor*	c = buf;
    USB_PVOID next = buf + USB_DT_CONFIG_SIZE;
    USB_INT				len = USB_BUFSIZ - USB_DT_CONFIG_SIZE;
    struct usb_function*		f;
    USB_INT				status;

    /* write the config descriptor */
    c = buf;
    c->bLength = USB_DT_CONFIG_SIZE;
    c->bDescriptorType = type;
    /* wTotalLength is written later */
    c->bNumInterfaces = config->next_interface_id;
    c->bConfigurationValue = config->bConfigurationValue;
    c->bmAttributes = USB_CONFIG_ATT_ONE | config->bmAttributes;
#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
    if (FTEN_USB_DESC_FTEN == get_ften_desc_flag())
    {
        c->iConfiguration = 0x01;
        c->bMaxPower = 0xFA;
    }
    else
    {
        c->iConfiguration = config->iConfiguration;
        c->bMaxPower = config->bMaxPower ? : (CONFIG_USB_GADGET_VBUS_DRAW / 2);
    }
#else
    c->iConfiguration = config->iConfiguration;
    c->bMaxPower = config->bMaxPower ? : (CONFIG_USB_GADGET_VBUS_DRAW / 2);
#endif

    /* There may be e.g. OTG descriptors */
    if (config->descriptors)
    {
        status = usb_descriptor_fillbuf(next, len,
                                        config->descriptors);
        if (status < 0)
        { return status; }
        len -= status;
        next += status;
    }

    /* add each function's descriptors */
    list_for_each_entry(f, &config->functions, list)
    {
        struct usb_descriptor_header** descriptors;

        switch (speed)
        {
            case USB_SPEED_SUPER:
                descriptors = f->ss_descriptors;
                break;
            case USB_SPEED_HIGH:
                descriptors = f->hs_descriptors;
                break;
            default:
                descriptors = f->descriptors;
        }

        if (!descriptors)
        { continue; }
        status = usb_descriptor_fillbuf(next, len,
                                        (const struct usb_descriptor_header**) descriptors);
        if (status < 0)
        { return status; }
        len -= status;
        next += status;
    }

    len = next - buf;
    c->wTotalLength = cpu_to_le16(len);
    return len;
}

static USB_INT config_desc(struct usb_composite_dev* cdev, USB_UINT w_value)
{
    struct usb_gadget*		gadget = cdev->gadget;
    struct usb_configuration*	c;
    USB_UCHAR				type = w_value >> 8;
    enum usb_device_speed		speed = USB_SPEED_UNKNOWN;

    if (gadget->speed == USB_SPEED_SUPER)
    { speed = gadget->speed; }
    else if (gadget_is_dualspeed(gadget))
    {
        USB_INT	hs = 0;
        if (gadget->speed == USB_SPEED_HIGH)
        { hs = 1; }
        if (type == USB_DT_OTHER_SPEED_CONFIG)
        { hs = !hs; }
        if (hs)
        { speed = USB_SPEED_HIGH; }

    }

    /* This is a lookup by config *INDEX* */
    w_value &= 0xff;
    list_for_each_entry(c, &cdev->configs, list)
    {
        /* ignore configs that won't work at this speed */
        switch (speed)
        {
            case USB_SPEED_SUPER:
                if (!c->superspeed)
                { continue; }
                break;
            case USB_SPEED_HIGH:
                if (!c->highspeed)
                { continue; }
                break;
            default:
                if (!c->fullspeed)
                { continue; }
        }

        if (w_value == 0)
        { return config_buf(c, speed, cdev->req->buf, type); }
        w_value--;
    }
    return -EINVAL;
}

static USB_INT count_configs(struct usb_composite_dev* cdev, USB_UINT type)
{
    struct usb_gadget*		gadget = cdev->gadget;
    struct usb_configuration*	c;
    USB_UINT			count = 0;
    USB_INT				hs = 0;
    USB_INT				ss = 0;

    if (gadget_is_dualspeed(gadget))
    {
        if (gadget->speed == USB_SPEED_HIGH)
        { hs = 1; }
        if (gadget->speed == USB_SPEED_SUPER)
        { ss = 1; }
        if (type == USB_DT_DEVICE_QUALIFIER)
        { hs = !hs; }
    }
    list_for_each_entry(c, &cdev->configs, list)
    {
        /* ignore configs that won't work at this speed */
        if (ss)
        {
            if (!c->superspeed)
            { continue; }
        }
        else if (hs)
        {
            if (!c->highspeed)
            { continue; }
        }
        else
        {
            if (!c->fullspeed)
            { continue; }
        }
        count++;
    }
    return count;
}

/**
 * bos_desc() - prepares the BOS descriptor.
 * @cdev: pointer to usb_composite device to generate the bos
 *	descriptor for
 *
 * This function generates the BOS (Binary Device Object)
 * descriptor and its device capabilities descriptors. The BOS
 * descriptor should be supported by a SuperSpeed device.
 */
static USB_INT bos_desc(struct usb_composite_dev* cdev)
{
    struct usb_ext_cap_descriptor*	usb_ext;
    struct usb_ss_cap_descriptor*	ss_cap;
    struct usb_dcd_config_params	dcd_config_params;
    struct usb_bos_descriptor*	bos = cdev->req->buf;

    bos->bLength = USB_DT_BOS_SIZE;
    bos->bDescriptorType = USB_DT_BOS;

    bos->wTotalLength = cpu_to_le16(USB_DT_BOS_SIZE);
    bos->bNumDeviceCaps = 0;

    /*
     * A SuperSpeed device shall include the USB2.0 extension descriptor
     * and shall support LPM when operating in USB2.0 HS mode.
     */
    usb_ext = cdev->req->buf + le16_to_cpu(bos->wTotalLength);
    bos->bNumDeviceCaps++;
    le16_add_cpu(&bos->wTotalLength, USB_DT_USB_EXT_CAP_SIZE);
    usb_ext->bLength = USB_DT_USB_EXT_CAP_SIZE;
    usb_ext->bDescriptorType = USB_DT_DEVICE_CAPABILITY;
    usb_ext->bDevCapabilityType = USB_CAP_TYPE_EXT;
    usb_ext->bmAttributes = cpu_to_le32(USB_LPM_SUPPORT);

    /*
     * The Superspeed USB Capability descriptor shall be implemented by all
     * SuperSpeed devices.
     */
    ss_cap = cdev->req->buf + le16_to_cpu(bos->wTotalLength);
    bos->bNumDeviceCaps++;
    le16_add_cpu(&bos->wTotalLength, USB_DT_USB_SS_CAP_SIZE);
    ss_cap->bLength = USB_DT_USB_SS_CAP_SIZE;
    ss_cap->bDescriptorType = USB_DT_DEVICE_CAPABILITY;
    ss_cap->bDevCapabilityType = USB_SS_CAP_TYPE;
    ss_cap->bmAttributes = 0; /* LTM is not supported yet */
    ss_cap->wSpeedSupported = cpu_to_le16(USB_LOW_SPEED_OPERATION |
                                          USB_FULL_SPEED_OPERATION |
                                          USB_HIGH_SPEED_OPERATION |
                                          USB_5GBPS_OPERATION);
    ss_cap->bFunctionalitySupport = USB_LOW_SPEED_OPERATION;

    /* Get Controller configuration */
    if (cdev->gadget->ops->get_config_params)
    { cdev->gadget->ops->get_config_params(&dcd_config_params); }
    else
    {
        dcd_config_params.bU1devExitLat = USB_DEFAULT_U1_DEV_EXIT_LAT;
        dcd_config_params.bU2DevExitLat =
            cpu_to_le16(USB_DEFAULT_U2_DEV_EXIT_LAT);
    }
    ss_cap->bU1devExitLat = dcd_config_params.bU1devExitLat;
    ss_cap->bU2DevExitLat = dcd_config_params.bU2DevExitLat;

    return le16_to_cpu(bos->wTotalLength);
}

static USB_VOID device_qual(struct usb_composite_dev* cdev)
{
    struct usb_qualifier_descriptor*	qual = cdev->req->buf;

    qual->bLength = sizeof(*qual);
    qual->bDescriptorType = USB_DT_DEVICE_QUALIFIER;
    /* POLICY: same bcdUSB and device type info at both speeds */
    qual->bcdUSB = cdev->desc.bcdUSB;
    qual->bDeviceClass = cdev->desc.bDeviceClass;
    qual->bDeviceSubClass = cdev->desc.bDeviceSubClass;
    qual->bDeviceProtocol = cdev->desc.bDeviceProtocol;
    /* ASSUME same EP0 fifo size at both speeds */
    qual->bMaxPacketSize0 = cdev->gadget->ep0->maxpacket;
    qual->bNumConfigurations = count_configs(cdev, USB_DT_DEVICE_QUALIFIER);
    qual->bRESERVED = 0;
}

#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
/*��ȡ�����豸�޶�������*/
static USB_VOID device_qual_ften(struct usb_composite_dev* cdev)
{
    struct usb_qualifier_descriptor*	qual = cdev->req->buf;

    qual->bLength = sizeof(*qual);
    qual->bDescriptorType = USB_DT_DEVICE_QUALIFIER;

    qual->bcdUSB = 0x0200;
    qual->bDeviceClass = 0x02;
    qual->bDeviceSubClass = 0x00;
    qual->bDeviceProtocol = 0x00;

    qual->bMaxPacketSize0 = 0x40;
    qual->bNumConfigurations = 0x01;
    qual->bRESERVED = 0;
}
#endif
/*-------------------------------------------------------------------------*/

static USB_VOID reset_config(struct usb_composite_dev* cdev)
{
    struct usb_function*		f;

    DBG_E(MBB_PNP, "reset config\n");

    list_for_each_entry(f, &cdev->config->functions, list)
    {
        if (f->disable)
        { f->disable(f); }

        bitmap_zero(f->endpoints, 32);
    }
    cdev->config = NULL;
}

static USB_INT set_config(struct usb_composite_dev* cdev,
                          const struct usb_ctrlrequest* ctrl, USB_UINT number)
{
    struct usb_gadget*	gadget = cdev->gadget;
    struct usb_configuration* c = NULL;
    usb_adp_ctx_t* UsbCtx = NULL;
    USB_INT			result = -EINVAL;
    USB_UINT		power = gadget_is_otg(gadget) ? 8 : 100;
    USB_INT			tmp;
    USB_INT charger_type;

    UsbCtx = usb_get_adp_ctx();
#ifdef CONFIG_NCM_MBIM_SUPPORT
    if ((USB_CONFIG_MBIM == number) && (UsbCtx->usb_switch_gatway_mode_cb))
    {
        UsbCtx->gatway_work_mode = 1; // �Ͽ�����
        adp_usb_queue_delay_work(&(UsbCtx->gatway_disconnect_work), 0);
    }
#endif

    huawei_set_usb_enum_state(USB_ENUM_DONE);
    huawei_set_adress_flag(SET_ADD_NONE);
    if (number)
    {
        list_for_each_entry(c, &cdev->configs, list)
        {
            if (c->bConfigurationValue == number)
            {
                /*
                 * We disable the FDs of the previous
                 * configuration only if the new configuration
                 * is a valid one
                 */
                if (cdev->config)
                { reset_config(cdev); }
                result = 0;
                break;
            }
        }
        if (result < 0)
        { goto done; }
    }
    else     /* Zero configuration value - need to reset the config */
    {
        if (cdev->config)
        { reset_config(cdev); }
        result = 0;
    }

    DBG_E(MBB_PNP, "%s config #%d: %s\n",
          usb_speed_string(gadget->speed),
          number, c ? c->label : "unconfigured");

    if (!c)
    { goto done; }

    cdev->config = c;
#ifdef BSP_CONFIG_BOARD_K5160
    if (USB_CONFIG_MBIM == number)
    {
        need_open_opensrc_cdrom(1);
    }
    else
    {
        need_open_opensrc_cdrom(0);
    }
#endif

    /* Initialize all interfaces by setting them to altsetting zero. */
    for (tmp = 0; tmp < MAX_CONFIG_INTERFACES; tmp++)
    {
        struct usb_function*	f = c->interface[tmp];
        struct usb_descriptor_header** descriptors;

        if (!f)
        { break; }

        /*
         * Record which endpoints are used by the function. This is used
         * to dispatch control requests targeted at that endpoint to the
         * function's setup callback instead of the current
         * configuration's setup callback.
         */
        switch (gadget->speed)
        {
            case USB_SPEED_SUPER:
                descriptors = f->ss_descriptors;
                break;
            case USB_SPEED_HIGH:
                descriptors = f->hs_descriptors;
                break;
            default:
                descriptors = f->descriptors;
        }

        for (; *descriptors; ++descriptors)
        {
            struct usb_endpoint_descriptor* ep;
            USB_INT addr;

            if ((*descriptors)->bDescriptorType != USB_DT_ENDPOINT)
            { continue; }

            ep = (struct usb_endpoint_descriptor*)*descriptors;
            addr = ((ep->bEndpointAddress & 0x80) >> 3)
                   |  (ep->bEndpointAddress & 0x0f);
            set_bit(addr, f->endpoints);
        }

        result = f->set_alt(f, tmp, 0);
        if (result < 0)
        {
            DBG_E(MBB_PNP, "interface %d (%s/%p) alt 0 --> %d\n",
                  tmp, f->name, f, result);

            reset_config(cdev);
            goto done;
        }

        if (result == USB_GADGET_DELAYED_STATUS)
        {
            DBG_I(MBB_PNP, "%s: interface %d (%s) requested delayed status\n",
                  __func__, tmp, f->name);
            cdev->delayed_status++;
            DBG_I(MBB_PNP, "delayed_status count %d\n",
                  cdev->delayed_status);
        }
    }
#ifdef USB_CHARGE
    charger_type = MBB_USB_CHARGER_TYPE_PC;
    usb_charger_type_detect_event(NULL, MBB_USB_DEVICE_IDEN, &charger_type);
#endif /*MBB_CHARGER*/
    usb_notify_syswatch(DEVICE_ID_USB, USB_ATTACH_NOTIFY);
    /* when we return, be sure our power usage is valid */
    power = c->bMaxPower ? (2 * c->bMaxPower) : CONFIG_USB_GADGET_VBUS_DRAW;
done:
    usb_gadget_vbus_draw(gadget, power);
    if (result >= 0 && cdev->delayed_status)
    { result = USB_GADGET_DELAYED_STATUS; }
    return result;
}

/**
 * usb_add_config() - add a configuration to a device.
 * @cdev: wraps the USB gadget
 * @config: the configuration, with bConfigurationValue assigned
 * @bind: the configuration's bind function
 * Context: single threaded during gadget setup
 *
 * One of the main tasks of a composite @bind() routine is to
 * add each of the configurations it supports, using this routine.
 *
 * This function returns the value of the configuration's @bind(), which
 * is zero for success else a negative errno value.  Binding configurations
 * assigns global resources including string IDs, and per-configuration
 * resources such as interface IDs and endpoints.
 */
USB_INT usb_add_config(struct usb_composite_dev* cdev,
                       struct usb_configuration* config,
                       USB_INT (*bind)(struct usb_configuration*))
{
    USB_INT				status = -EINVAL;
    struct usb_configuration*	c;

    DBG_E(MBB_PNP, "adding config #%u '%s'/%p\n",
          config->bConfigurationValue,
          config->label, config);

    if (!config->bConfigurationValue || !bind)
    { goto done; }

    /* Prevent duplicate configuration identifiers */
    list_for_each_entry(c, &cdev->configs, list)
    {
        if (c->bConfigurationValue == config->bConfigurationValue)
        {
            status = -EBUSY;
            goto done;
        }
    }

    config->cdev = cdev;
    list_add_tail(&config->list, &cdev->configs);

    INIT_LIST_HEAD(&config->functions);
    INIT_LIST_HEAD(&config->android_functions);
    config->next_interface_id = 0;
    memset(config->interface, 0, sizeof(config->interface));

    status = bind(config);
    if (status < 0)
    {
        while (!list_empty(&config->functions))
        {
            struct usb_function*		f;

            f = list_first_entry(&config->functions,
                                 struct usb_function, list);
            list_del(&f->list);
            if (f->unbind)
            {
                DBG(cdev, "unbind function '%s'/%p\n",
                    f->name, f);
                f->unbind(config, f);
                /* may free memory for "f" */
            }
        }

        list_del(&config->list);
        config->cdev = NULL;
    }
    else
    {
        USB_UINT	i = 0;

        DBG_E(MBB_PNP, "cfg %d/%p support speeds:%s%s%s\n",
              config->bConfigurationValue, config,
              config->superspeed ? " super" : "",
              config->highspeed ? " high" : "",
              config->fullspeed
              ? (gadget_is_dualspeed(cdev->gadget)
                 ? " full"
                 : " full/low")
                  : "");
        struct android_usb_function* androidfun;
        struct usb_function*	f = config->interface[0];
        list_for_each_entry(androidfun, &config->android_functions, enabled_list)
        {
            if (i < MAX_CONFIG_INTERFACES)
            {
                if (!f)
                {
                    i++;
                    continue;
                }
                f = config->interface[i];
                DBG_E(MBB_PNP, "interface%d name = %-10s type:%-25s /%p\n",
                      i, androidfun->name, f->name, f);
                i++;
            }
        }

        /*for (i = 0; i < MAX_CONFIG_INTERFACES; i++) {
        	struct usb_function	*f = config->interface[i];
        	if (!f)
        		continue;
        	DBG_I(MBB_PNP, ("  interface %d = %s/%p\n",
        		i, f->name, f));
        }*/
    }

    /* set_alt(), or next bind(), sets up
     * ep->driver_data as needed.
     */
    usb_ep_autoconfig_reset(cdev->gadget);

done:
    if (status)
        DBG_E(MBB_PNP, "added config '%s'/%u --> %d\n", config->label,
              config->bConfigurationValue, status);
    return status;
}

static USB_INT unbind_config(struct usb_composite_dev* cdev,
                             struct usb_configuration* config)
{
    while (!list_empty(&config->functions))
    {
        struct usb_function*		f;

        f = list_first_entry(&config->functions,
                             struct usb_function, list);
        list_del(&f->list);
        if (f->unbind)
        {
            DBG_E(MBB_PNP, "unbind function '%s'/%p\n", f->name, f);
            f->unbind(config, f);
            /* may free memory for "f" */
        }
    }
    if (config->unbind)
    {
        DBG_E(MBB_PNP, "unbind config '%s'/%p\n", config->label, config);
        config->unbind(config);
        /* may free memory for "c" */
    }
    return 0;
}

/**
 * usb_remove_config() - remove a configuration from a device.
 * @cdev: wraps the USB gadget
 * @config: the configuration
 *
 * Drivers must call usb_gadget_disconnect before calling this function
 * to disconnect the device from the host and make sure the host will not
 * try to enumerate the device while we are changing the config list.
 */
USB_INT usb_remove_config(struct usb_composite_dev* cdev,
                          struct usb_configuration* config)
{
    USB_ULONG flags;
#ifdef MBB_FAST_ON_OFF
    USB_INT faston_off = false;
#endif/*MBB_FAST_ON_OFF*/
    spin_lock_irqsave(&cdev->lock, flags);

    if (cdev->config == config)
    { reset_config(cdev); }

    list_del(&config->list);

    spin_unlock_irqrestore(&cdev->lock, flags);
#ifdef MBB_FAST_ON_OFF
    faston_off = usb_fast_on_off_stat();
    if(true == faston_off)
    {
        cdev->next_string_id = 0;
    }
#endif/*MBB_FAST_ON_OFF*/

    return unbind_config(cdev, config);
}

/*-------------------------------------------------------------------------*/

/* We support strings in multiple languages ... string descriptor zero
 * says which languages are supported.  The typical case will be that
 * only one language (probably English) is used, with I18N handled on
 * the host side.
 */

static USB_VOID collect_langs(struct usb_gadget_strings** sp, __le16* buf)
{
    const struct usb_gadget_strings*	s;
    USB_UINT16				language;
    __le16*				tmp;

    while (*sp)
    {
        s = *sp;
        language = cpu_to_le16(s->language);
        for (tmp = buf; *tmp && tmp < &buf[126]; tmp++)
        {
            if (*tmp == language)
            { goto repeat; }
        }
        *tmp++ = language;
    repeat:
        sp++;
    }
}

static USB_INT lookup_string(
    struct usb_gadget_strings**	sp,
    USB_PVOID               buf,
    USB_UINT16				language,
    USB_INT				id
)
{
    struct usb_gadget_strings*	s;
    USB_INT				value;

    while (*sp)
    {
        s = *sp++;
        if ((s->language != language) && (0 < language))
        { continue; }
        value = usb_gadget_get_string(s, id, buf);
        if (value > 0)
        { return value; }
    }
    return -EINVAL;
}

static USB_INT get_string(struct usb_composite_dev* cdev,
                          void* buf, USB_UINT16 language, USB_INT id)
{
    struct usb_configuration*	c;
    struct usb_function*		f;
    USB_INT				len;
    const USB_CHAR*			str;

    /* Yes, not only is USB's I18N support probably more than most
     * folk will ever care about ... also, it's all supported here.
     * (Except for UTF8 support for Unicode's "Astral Planes".)
     */

    /* 0 == report all available language codes */
    /* MSOS C0 EE����� */
    /* ע�ʹ������������ */
    if (id == MSOS_STRING_INDEX)
    {
        USB_CHAR* ss = buf;
        DBG_E(MBB_PNP, "MBB--->get_string id is[0x%x]-->\n", id);
        ss[0] = MSOS_DESC_SIZE;
        ss[1] = USB_DT_STRING;
        memcpy(&ss[USB_NUM_2], MSOS_SIGNATURE, USB_NUM_14);
        ss[USB_NUM_16] = MS_HUAWEI_VENDOR_CODE;
        ss[USB_NUM_17] = 0x00;  /* Padding */
        return ss[0];
    }
    if (id == 0)
    {
        struct usb_string_descriptor*	s = buf;
        struct usb_gadget_strings**	sp;

        memset(s, 0, 256);
        s->bDescriptorType = USB_DT_STRING;

        sp = composite->strings;
        if (sp)
        { collect_langs(sp, s->wData); }

        list_for_each_entry(c, &cdev->configs, list)
        {
            sp = c->strings;
            if (sp)
            { collect_langs(sp, s->wData); }

            list_for_each_entry(f, &c->functions, list)
            {
                sp = f->strings;
                if (sp)
                { collect_langs(sp, s->wData); }
            }
        }

        for (len = 0; len <= 126 && s->wData[len]; len++)
        { continue; }
        if (!len)
        { return -EINVAL; }

        s->bLength = 2 * (len + 1);
        return s->bLength;
    }

    /* Otherwise, look up and return a specified string.  First
     * check if the string has not been overridden.
     */
    if (cdev->manufacturer_override == id)
        str = iManufacturer ? : composite->iManufacturer ? :
              composite_manufacturer;
    else if (cdev->product_override == id)
    { str = iProduct ? : composite->iProduct; }
    else if (cdev->serial_override == id)
    { str = iSerialNumber; }
    else
    { str = NULL; }
    if (str)
    {
        struct usb_string gadgetString[] = {{ 0xff, str }, {}};
        struct usb_gadget_strings strings =
        {
            .language = language,
            .strings  = gadgetString
        };
        return usb_gadget_get_string(&strings, 0xff, buf);
    }

    /* String IDs are device-scoped, so we look up each string
    * table we're told about.  These lookups are infrequent;
    * simpler-is-better here.
    */
    if (composite->strings)
    {
        len = lookup_string(composite->strings, buf, language, id);
        if (len > 0)
        { return len; }
    }
    list_for_each_entry(c, &cdev->configs, list)
    {
        if (c->strings)
        {
            len = lookup_string(c->strings, buf, language, id);
            if (len > 0)
            { return len; }
        }
        list_for_each_entry(f, &c->functions, list)
        {
            if (!f->strings)
            { continue; }
            len = lookup_string(f->strings, buf, language, id);
            if (len > 0)
            { return len; }
        }
    }
    return -EINVAL;
}

/**
 * usb_string_id() - allocate an unused string ID
 * @cdev: the device whose string descriptor IDs are being allocated
 * Context: single threaded during gadget setup
 *
 * @usb_string_id() is called from bind() callbacks to allocate
 * string IDs.  Drivers for functions, configurations, or gadgets will
 * then store that ID in the appropriate descriptors and string table.
 *
 * All string identifier should be allocated using this,
 * @usb_string_ids_tab() or @usb_string_ids_n() routine, to ensure
 * that for example different functions don't wrongly assign different
 * meanings to the same identifier.
 */
USB_INT usb_string_id(struct usb_composite_dev* cdev)
{
    if (cdev->next_string_id < 254)
    {
        /* string id 0 is reserved by USB spec for list of
         * supported languages */
        /* 255 reserved as well? -- mina86 */
        cdev->next_string_id++;
        return cdev->next_string_id;
    }
    return -ENODEV;
}

/**
 * usb_string_ids() - allocate unused string IDs in batch
 * @cdev: the device whose string descriptor IDs are being allocated
 * @str: an array of usb_string objects to assign numbers to
 * Context: single threaded during gadget setup
 *
 * @usb_string_ids() is called from bind() callbacks to allocate
 * string IDs.  Drivers for functions, configurations, or gadgets will
 * then copy IDs from the string table to the appropriate descriptors
 * and string table for other languages.
 *
 * All string identifier should be allocated using this,
 * @usb_string_id() or @usb_string_ids_n() routine, to ensure that for
 * example different functions don't wrongly assign different meanings
 * to the same identifier.
 */
USB_INT usb_string_ids_tab(struct usb_composite_dev* cdev, struct usb_string* str)
{
    USB_INT next = cdev->next_string_id;

    for (; str->s; ++str)
    {
        if (unlikely(next >= 254))
        { return -ENODEV; }
        str->id = ++next;
    }

    cdev->next_string_id = next;

    return 0;
}

/**
 * usb_string_ids_n() - allocate unused string IDs in batch
 * @c: the device whose string descriptor IDs are being allocated
 * @n: number of string IDs to allocate
 * Context: single threaded during gadget setup
 *
 * Returns the first requested ID.  This ID and next @n-1 IDs are now
 * valid IDs.  At least provided that @n is non-zero because if it
 * is, returns last requested ID which is now very useful information.
 *
 * @usb_string_ids_n() is called from bind() callbacks to allocate
 * string IDs.  Drivers for functions, configurations, or gadgets will
 * then store that ID in the appropriate descriptors and string table.
 *
 * All string identifier should be allocated using this,
 * @usb_string_id() or @usb_string_ids_n() routine, to ensure that for
 * example different functions don't wrongly assign different meanings
 * to the same identifier.
 */
int usb_string_ids_n(struct usb_composite_dev* c, unsigned n)
{
    USB_UINT next = c->next_string_id;
    if (unlikely(n > 254 || (USB_UINT)next + n > 254))
    { return -ENODEV; }
    c->next_string_id += n;
    return next + 1;
}


/*-------------------------------------------------------------------------*/

static void composite_setup_complete(struct usb_ep* ep, struct usb_request* req)
{
    if (req->status || req->actual != req->length)
        DBG_E(MBB_PNP, "setup complete --> %d, %d/%d\n",
              req->status, req->actual, req->length);
}

/*
 * The setup() callback implements all the ep0 functionality that's
 * not handled lower down, in hardware or the hardware driver(like
 * device and endpoint feature flags, and their status).  It's all
 * housekeeping for the gadget function we're implementing.  Most of
 * the work is in config and function specific setup.
 */
static USB_INT
composite_setup(struct usb_gadget* gadget, const struct usb_ctrlrequest* ctrl)
{
    struct usb_composite_dev*	cdev = get_gadget_data(gadget);
    struct usb_request*		req = NULL;
    USB_INT				value = -EOPNOTSUPP;
    USB_INT				status = 0;
    USB_UINT16				w_index = le16_to_cpu(ctrl->wIndex);
    USB_UCHAR				intf = w_index & 0xFF;
    USB_UINT16				w_value = le16_to_cpu(ctrl->wValue);
    USB_UINT16				w_length = le16_to_cpu(ctrl->wLength);
    struct usb_function*		f = NULL;
    USB_UCHAR				endp;
    usb_enum_state  enum_state = USB_ENUM_NONE;

    /* partial re-init of the response message; the function or the
     * gadget might need to intercept e.g. a control-OUT completion
     * when we delegate to it.
     */
    if (NULL  == cdev)
    {
        DBG_E(MBB_PNP, "%s get_gadget_data return null, error!\n");
        return -EOPNOTSUPP;
    }

    /*composite_driver handle request first*/
    value = cdev->driver->setup(gadget, ctrl);
    if (value >= 0 && (USB_GADGET_DELAYED_STATUS != value) )
    {
        return value;
    }

    req = cdev->req;
    req->zero = 0;
    req->complete = composite_setup_complete;
    req->length = 0;
    gadget->ep0->driver_data = cdev;

    switch (ctrl->bRequest)
    {

            /* we handle all standard USB descriptors */
        case USB_REQ_GET_DESCRIPTOR:
            if (ctrl->bRequestType != USB_DIR_IN)
            { goto unknown; }
            switch (w_value >> 8)
            {

                case USB_DT_DEVICE:
#if ( FEATURE_ON == MBB_MLOG )
                    mlog_print("USB", mlog_lv_info, "get device desc\n");   /* SW reliability */
#endif
                    cdev->desc.bNumConfigurations =
                        count_configs(cdev, USB_DT_DEVICE);
                    cdev->desc.bMaxPacketSize0 =
                        cdev->gadget->ep0->maxpacket;
                    if (gadget_is_superspeed(gadget))
                    {
                        if (gadget->speed >= USB_SPEED_SUPER)
                        {
                            cdev->desc.bcdUSB = cpu_to_le16(0x0300);
                            cdev->desc.bMaxPacketSize0 = 9;
                        }
                        else
                        {
                            cdev->desc.bcdUSB = cpu_to_le16(0x0210);
                        }
                    }
#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
                    DBG_E(MBB_PNP, "receive enum request!\n");
                    set_ften_enum_flag(FTEN_USB_ENUM_DONE);
                    if (FTEN_USB_DESC_FTEN == get_ften_desc_flag())
                    {
                        cdev->desc.bcdUSB = cpu_to_le16(0x0200);
                        cdev->desc.bcdDevice = 0x00;
                    }
#endif
                    value = min(w_length, (USB_UINT16) sizeof cdev->desc);
                    memcpy(req->buf, &cdev->desc, value);
                    break;
                case USB_DT_DEVICE_QUALIFIER:
                    if (!gadget_is_dualspeed(gadget) ||
                        gadget->speed >= USB_SPEED_SUPER)
                    { break; }
#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
                    if (FTEN_USB_DESC_FTEN == get_ften_desc_flag())
                    {
                        device_qual_ften(cdev);
                    }
                    else
                    {
                        device_qual(cdev);
                    }
#else
                    device_qual(cdev);
#endif
                    value = min_t(USB_INT, w_length,
                                  sizeof(struct usb_qualifier_descriptor));
                    break;
                case USB_DT_OTHER_SPEED_CONFIG:
                    if (!gadget_is_dualspeed(gadget) ||
                        gadget->speed >= USB_SPEED_SUPER)
                    { break; }
                    /* FALLTHROUGH */
                case USB_DT_CONFIG:
#if ( FEATURE_ON == MBB_MLOG )
                    mlog_print("USB", mlog_lv_info, "get config %u desc\n", w_value);   /* SW reliability */
#endif
                    value = config_desc(cdev, w_value);
                    if (value >= 0)
                    { value = min(w_length, (USB_UINT16) value); }
                    break;
                case USB_DT_STRING:
                    value = get_string(cdev, req->buf,
                                       w_index, w_value & 0xff);
                    if (value >= 0)
                    { value = min(w_length, (USB_UINT16) value); }
                    break;
                case USB_DT_BOS:
                    if (gadget_is_superspeed(gadget))
                    {
                        value = bos_desc(cdev);
                        value = min(w_length, (USB_UINT16) value);
                    }
                    break;
            }
            break;

            /* any number of configs can work */
        case USB_REQ_SET_CONFIGURATION:
            if (ctrl->bRequestType != 0)
            { goto unknown; }
            if (gadget_is_otg(gadget))
            {
                if (gadget->a_hnp_support)
                { DBG_E(MBB_PNP, "HNP available\n"); }
                else if (gadget->a_alt_hnp_support)
                { DBG_E(MBB_PNP, "HNP on another port\n"); }
                else
                { DBG_E(MBB_PNP, "HNP inactive\n"); }
            }
            /*### mlog���PID*/
            mlog_print("USB", mlog_lv_info, "Enumeration end, PID:0x%4x,VID:0x12D1\n", cdev->desc.idProduct);
#if ( FEATURE_ON == MBB_MLOG )
            mlog_print("USB", mlog_lv_info, "set config %u\n", w_value);   /* SW reliability */
#endif
            spin_lock(&cdev->lock);
            value = set_config(cdev, ctrl, w_value);
            spin_unlock(&cdev->lock);
            break;
        case USB_REQ_GET_CONFIGURATION:
            if (ctrl->bRequestType != USB_DIR_IN)
            { goto unknown; }
            if (cdev->config)
            { *(USB_UCHAR*)req->buf = cdev->config->bConfigurationValue; }
            else
            { *(USB_UCHAR*)req->buf = 0; }
            value = min(w_length, (USB_UINT16) 1);
            break;

            /* function drivers must handle get/set altsetting; if there's
             * no get() method, we know only altsetting zero works.
             */
        case USB_REQ_SET_INTERFACE:
            if (ctrl->bRequestType != USB_RECIP_INTERFACE)
            { goto unknown; }
            if (!cdev->config || intf >= MAX_CONFIG_INTERFACES)
            { break; }
            f = cdev->config->interface[intf];
            if (!f)
            { break; }
            if (w_value && !f->set_alt)
            { break; }
            value = f->set_alt(f, w_index, w_value);
            if (value == USB_GADGET_DELAYED_STATUS)
            {
                DBG_E(MBB_PNP, "%s: interface %d (%s) requested delayed status\n",
                      __func__, intf, f->name);
                cdev->delayed_status++;
                DBG_E(MBB_PNP, "delayed_status count %d\n",
                      cdev->delayed_status);
            }
            break;
        case USB_REQ_GET_INTERFACE:
            if (ctrl->bRequestType != (USB_DIR_IN | USB_RECIP_INTERFACE))
            { goto unknown; }
            if (!cdev->config || intf >= MAX_CONFIG_INTERFACES)
            { break; }
            f = cdev->config->interface[intf];
            if (!f)
            { break; }
            /* lots of interfaces only need altsetting zero... */
            value = f->get_alt ? f->get_alt(f, w_index) : 0;
            if (value < 0)
            { break; }
            *((USB_UCHAR*)req->buf) = value;
            value = min(w_length, (USB_UINT16) 1);
            break;

            /*
             * USB 3.0 additions:
             * Function driver should handle get_status request. If such cb
             * wasn't supplied we respond with default value = 0
             * Note: function driver should supply such cb only for the first
             * interface of the function
             */
        case USB_REQ_GET_STATUS:
            if (!gadget_is_superspeed(gadget))
            { goto unknown; }
            if (ctrl->bRequestType != (USB_DIR_IN | USB_RECIP_INTERFACE))
            { goto unknown; }
            value = 2;	/* This is the length of the get_status reply */
            put_unaligned_le16(0, req->buf);
            if (!cdev->config || intf >= MAX_CONFIG_INTERFACES)
            { break; }
            f = cdev->config->interface[intf];
            if (!f)
            { break; }
            status = f->get_status ? f->get_status(f) : 0;
            if (status < 0)
            { break; }
            put_unaligned_le16(status & 0x0000ffff, req->buf);
            break;
            /*
             * Function drivers should handle SetFeature/ClearFeature
             * (FUNCTION_SUSPEND) request. function_suspend cb should be supplied
             * only for the first interface of the function
             */
        case USB_REQ_CLEAR_FEATURE:
        case USB_REQ_SET_FEATURE:
            if (!gadget_is_superspeed(gadget))
            { goto unknown; }
            if (ctrl->bRequestType != (USB_DIR_OUT | USB_RECIP_INTERFACE))
            { goto unknown; }
            switch (w_value)
            {
                case USB_INTRF_FUNC_SUSPEND:
                    if (!cdev->config || intf >= MAX_CONFIG_INTERFACES)
                    { break; }
                    f = cdev->config->interface[intf];
                    if (!f)
                    { break; }
                    value = 0;
                    if (f->func_suspend)
                    { value = f->func_suspend(f, w_index >> 8); }
                    if (value < 0)
                    {
                        DBG_E(MBB_PNP, "func_suspend() returned error %d\n",
                              value);
                        value = 0;
                    }
                    break;
            }
            break;
        default:
        unknown:
            DBG_I(MBB_PNP, "non-core control req%02x.%02x v%04x i%04x l%d\n",
                  ctrl->bRequestType, ctrl->bRequest,
                  w_value, w_index, w_length);

            /* functions always handle their interfaces and endpoints...
             * punt other recipients (other, WUSB, ...) to the current
             * configuration code.
             *
             * REVISIT it could make sense to let the composite device
             * take such requests too, if that's ever needed:  to work
             * in config 0, etc.
             */
            switch (ctrl->bRequestType & USB_RECIP_MASK)
            {
                case USB_RECIP_INTERFACE:
                    if (!cdev->config || intf >= MAX_CONFIG_INTERFACES)
                    { break; }
                    f = cdev->config->interface[intf];
                    break;

                case USB_RECIP_ENDPOINT:
                    endp = ((w_index & 0x80) >> 3) | (w_index & 0x0f);
                    list_for_each_entry(f, &cdev->config->functions, list)
                    {
                        if (test_bit(endp, f->endpoints))
                        { break; }
                    }
                    if (&f->list == &cdev->config->functions)
                    { f = NULL; }
                    break;
            }

            if (f && f->setup)
            { value = f->setup(f, ctrl); }
            else
            {
                struct usb_configuration*	c;

                c = cdev->config;
                if (c && c->setup)
                { value = c->setup(c, ctrl); }
            }

            goto done;
    }

    /* respond with data transfer before status phase? */
    if (value >= 0 && value != USB_GADGET_DELAYED_STATUS)
    {
        req->length = value;
        req->zero = value < w_length;
        value = usb_ep_queue(gadget->ep0, req, GFP_ATOMIC);
        if (value < 0)
        {
            DBG_E(MBB_PNP, "ep_queue --> %d\n", value);
            req->status = 0;
            composite_setup_complete(gadget->ep0, req);
        }
    }
    else if (value == USB_GADGET_DELAYED_STATUS && w_length != 0)
    {
        DBG_E(MBB_PNP, "%s: Delayed status not supported for w_length != 0",
              __func__);
    }

done:
    /* device either stalls (value < 0) or reports success */
    return value;
}

static void composite_disconnect(struct usb_gadget* gadget)
{
    struct usb_composite_dev*	cdev = get_gadget_data(gadget);
    USB_ULONG			flags;

    /* REVISIT:  should we have config and device level
     * disconnect callbacks?
     */
    if (NULL  == cdev)
    {
        DBG_E(MBB_PNP, "%s get_gadget_data return null, error!\n", __FUNCTION__);
        return;
    }
    spin_lock_irqsave(&cdev->lock, flags);
    if (cdev->config)
    { reset_config(cdev); }
    if (composite->disconnect)
    { composite->disconnect(cdev); }
    spin_unlock_irqrestore(&cdev->lock, flags);
}

/*-------------------------------------------------------------------------*/

static ssize_t composite_show_suspended(struct device* dev,
                                        struct device_attribute* attr,
                                        USB_CHAR* buf)
{
    struct usb_gadget* gadget = dev_to_usb_gadget(dev);
    struct usb_composite_dev* cdev = get_gadget_data(gadget);
    if (NULL != cdev)
    {
        return snprintf(buf, 1, "%d\n", cdev->suspended);
    }
    else
    {
        return snprintf(buf, 1, "%d\n", 0);
    }
}

static DEVICE_ATTR(suspended, 0444, composite_show_suspended, NULL);

static void
composite_unbind(struct usb_gadget* gadget)
{
    struct usb_composite_dev*	cdev = get_gadget_data(gadget);

    /* composite_disconnect() must already have been called
     * by the underlying peripheral controller driver!
     * so there's no i/o concurrency that could affect the
     * state protected by cdev->lock.
     */
    if (NULL  == cdev)
    {
        DBG_E(MBB_PNP, "%s get_gadget_data return null, error!\n", __FUNCTION__);
        return;
    }
    WARN_ON(cdev->config);

    while (!list_empty(&cdev->configs))
    {
        struct usb_configuration*	c;
        c = list_first_entry(&cdev->configs,
                             struct usb_configuration, list);
        list_del(&c->list);
        unbind_config(cdev, c);
    }
    if (composite->unbind)
    { composite->unbind(cdev); }

    if (cdev->req)
    {
        kfree(cdev->req->buf);
        usb_ep_free_request(gadget->ep0, cdev->req);
    }
    device_remove_file(&gadget->dev, &dev_attr_suspended);
    kfree(cdev);
    set_gadget_data(gadget, NULL);
    composite = NULL;
}

static USB_UCHAR override_id(struct usb_composite_dev* cdev, USB_UCHAR* desc)
{
    if (!*desc)
    {
        USB_INT ret = usb_string_id(cdev);
        if (unlikely(ret < 0))
        { DBG_E(MBB_PNP, "failed to override string ID\n"); }
        else
        { *desc = ret; }
    }

    return *desc;
}

static USB_INT composite_bind(struct usb_gadget* gadget)
{
    struct usb_composite_dev*	cdev;
    USB_INT				status = -ENOMEM;

    cdev = kzalloc(sizeof * cdev, GFP_KERNEL);
    if (!cdev)
    { return status; }

    spin_lock_init(&cdev->lock);
    cdev->gadget = gadget;
    set_gadget_data(gadget, cdev);
    INIT_LIST_HEAD(&cdev->configs);

    /* preallocate control response and buffer */
    cdev->req = usb_ep_alloc_request(gadget->ep0, GFP_KERNEL);
    if (!cdev->req)
    { goto fail; }
    cdev->req->buf = kmalloc(USB_BUFSIZ, GFP_KERNEL);
    if (!cdev->req->buf)
    { goto fail; }
    cdev->req->complete = composite_setup_complete;
    gadget->ep0->driver_data = cdev;

    cdev->bufsiz = USB_BUFSIZ;
    cdev->driver = composite;

    /*
     * As per USB compliance update, a device that is actively drawing
     * more than 100mA from USB must report itself as bus-powered in
     * the GetStatus(DEVICE) call.
     */
    if (CONFIG_USB_GADGET_VBUS_DRAW <= USB_SELF_POWER_VBUS_MAX_DRAW)
    { usb_gadget_set_selfpowered(gadget); }

    /* interface and string IDs start at zero via kzalloc.
     * we force endpoints to start unassigned; few controller
     * drivers will zero ep->driver_data.
     */
    usb_ep_autoconfig_reset(cdev->gadget);

    /* composite gadget needs to assign strings for whole device (like
     * serial number), register function drivers, potentially update
     * power state and consumption, etc
     */
    status = cdev->driver->bind(cdev);
    if (status < 0)
    { goto fail; }

    cdev->desc = *composite->dev;

    /* standardized runtime overrides for device ID data */
    if (idVendor)
    { cdev->desc.idVendor = cpu_to_le16(idVendor); }
    if (idProduct)
    { cdev->desc.idProduct = cpu_to_le16(idProduct); }
    if (bcdDevice)
    { cdev->desc.bcdDevice = cpu_to_le16(bcdDevice); }

    /* string overrides */
    if (iManufacturer || !cdev->desc.iManufacturer)
    {
        if (!iManufacturer && !composite->iManufacturer &&
            !*composite_manufacturer)
            snprintf(composite_manufacturer,
                     sizeof composite_manufacturer,
                     "%s %s with %s",
                     init_utsname()->sysname,
                     init_utsname()->release,
                     gadget->name);

        cdev->manufacturer_override =
            override_id(cdev, &cdev->desc.iManufacturer);
    }

    if (iProduct || (!cdev->desc.iProduct && composite->iProduct))
        cdev->product_override =
            override_id(cdev, &cdev->desc.iProduct);

    if (iSerialNumber)
        cdev->serial_override =
            override_id(cdev, &cdev->desc.iSerialNumber);

    /* has userspace failed to provide a serial number? */
    if (composite->needs_serial && !cdev->desc.iSerialNumber)
    { DBG_E(MBB_PNP, "userspace failed to provide iSerialNumber\n"); }

    /* finish up */
    status = device_create_file(&gadget->dev, &dev_attr_suspended);
    if (status)
    { goto fail; }

    DBG_E(MBB_PNP, "%s ready\n", composite->name);
    return 0;

fail:
    composite_unbind(gadget);
    return status;
}

/*-------------------------------------------------------------------------*/

static void
composite_suspend(struct usb_gadget* gadget)
{
    struct usb_composite_dev*	cdev = get_gadget_data(gadget);
    struct usb_function*		f;

    /* REVISIT:  should we have config level
     * suspend/resume callbacks?
     */
    DBG_T(MBB_PNP, "suspend\n");
#if ( FEATURE_ON == MBB_MLOG )
    mlog_print("USB", mlog_lv_info, "bus suspend\n");   /* SW reliability */
#endif
    if (NULL  == cdev)
    {
        DBG_E(MBB_PNP, "%s get_gadget_data return null, error!\n", __FUNCTION__);
        return;
    }
    if (cdev->config)
    {
        list_for_each_entry(f, &cdev->config->functions, list)
        {
            if (f->suspend)
            { f->suspend(f); }
        }
    }
    if (composite->suspend)
    { composite->suspend(cdev); }

    cdev->suspended = 1;

    usb_gadget_vbus_draw(gadget, 2);
}

static void
composite_resume(struct usb_gadget* gadget)
{
    struct usb_composite_dev*	cdev = get_gadget_data(gadget);
    struct usb_function*		f;
    USB_UCHAR				maxpower;

    /* REVISIT:  should we have config level
     * suspend/resume callbacks?
     */
    DBG_E(MBB_PNP, "resume\n");
#if ( FEATURE_ON == MBB_MLOG )
    mlog_print("USB", mlog_lv_info, "bus resume\n");   /* SW reliability */
#endif
    if (NULL  == cdev)
    {
        DBG_E(MBB_PNP, "%s get_gadget_data return null, error!\n", __FUNCTION__);
        return;
    }
    if (composite->resume)
    { composite->resume(cdev); }
    if (cdev->config)
    {
        list_for_each_entry(f, &cdev->config->functions, list)
        {
            if (f->resume)
            { f->resume(f); }
        }

        maxpower = cdev->config->bMaxPower;

        usb_gadget_vbus_draw(gadget, maxpower ?
                             (2 * maxpower) : CONFIG_USB_GADGET_VBUS_DRAW);
    }

    cdev->suspended = 0;
}

/*-------------------------------------------------------------------------*/

static struct usb_gadget_driver composite_driver =
{
#ifdef CONFIG_USB_GADGET_SUPERSPEED
    .max_speed	= USB_SPEED_SUPER,
#else
    .max_speed	= USB_SPEED_HIGH,
#endif

    .unbind		= composite_unbind,

    .setup		= composite_setup,
    .disconnect	= composite_disconnect,

    .suspend	= composite_suspend,
    .resume		= composite_resume,

    .driver	= {
        .owner		= THIS_MODULE,
    },
};

/**
 * usb_composite_probe() - register a composite driver
 * @driver: the driver to register
 * @bind: the callback used to allocate resources that are shared across the
 *	whole device, such as string IDs, and add its configurations using
 *	@usb_add_config().  This may fail by returning a negative errno
 *	value; it should return zero on successful initialization.
 * Context: single threaded during gadget setup
 *
 * This function is used to register drivers using the composite driver
 * framework.  The return value is zero, or a negative errno value.
 * Those values normally come from the driver's @bind method, which does
 * all the work of setting up the driver to match the hardware.
 *
 * On successful return, the gadget is ready to respond to requests from
 * the host, unless one of its components invokes usb_gadget_disconnect()
 * while it was binding.  That would usually be done in order to wait for
 * some userspace participation.
 */
USB_INT usb_composite_probe(struct usb_composite_driver* driver,
                            USB_INT (*bind)(struct usb_composite_dev* cdev))
{
    if (!driver || !driver->dev || !bind || composite)
    { return -EINVAL; }

    if (!driver->name)
    { driver->name = "composite"; }
    if (!driver->iProduct)
    { driver->iProduct = driver->name; }
    composite_driver.function =  (USB_PCHAR) driver->name;
    composite_driver.driver.name = driver->name;
    composite_driver.max_speed =
        min_t(USB_UCHAR, composite_driver.max_speed, driver->max_speed);
    composite = driver;
    composite_gadget_bind = bind;

    return usb_gadget_probe_driver(&composite_driver, composite_bind);
}

/**
 * usb_composite_unregister() - unregister a composite driver
 * @driver: the driver to unregister
 *
 * This function is used to unregister drivers using the composite
 * driver framework.
 */
void usb_composite_unregister(struct usb_composite_driver* driver)
{
    if (composite != driver)
    { return; }
    usb_gadget_unregister_driver(&composite_driver);
}

/**
 * usb_composite_setup_continue() - Continue with the control transfer
 * @cdev: the composite device who's control transfer was kept waiting
 *
 * This function must be called by the USB function driver to continue
 * with the control transfer's data/status stage in case it had requested to
 * delay the data/status stages. A USB function's setup handler (e.g. set_alt())
 * can request the composite framework to delay the setup request's data/status
 * stages by returning USB_GADGET_DELAYED_STATUS.
 */
void usb_composite_setup_continue(struct usb_composite_dev* cdev)
{
    USB_INT			value;
    struct usb_request*	req = cdev->req;
    USB_ULONG		flags;

    DBG_E(MBB_PNP, "%s\n", __func__);
    spin_lock_irqsave(&cdev->lock, flags);

    if (cdev->delayed_status == 0)
    {
        DBG_E(MBB_PNP, "%s: Unexpected call\n", __func__);

    }
    else if (--cdev->delayed_status == 0)
    {
        DBG_E(MBB_PNP, "%s: Completing delayed status\n", __func__);
        req->length = 0;
        value = usb_ep_queue(cdev->gadget->ep0, req, GFP_ATOMIC);
        if (value < 0)
        {
            DBG_E(MBB_PNP, "ep_queue --> %d\n", value);
            req->status = 0;
            composite_setup_complete(cdev->gadget->ep0, req);
        }
    }

    spin_unlock_irqrestore(&cdev->lock, flags);
}

