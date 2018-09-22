

#ifndef __HE_PNP_ADAPT_H__
#define __HE_PNP_ADAPT_H__

#ifdef MBB_USB_UNITARY_Q
#include <soc/qcom/smem.h>
#include <mach/huawei_smem.h>
#include <linux/huawei_feature.h>
#include <linux/qcom/diag_dload.h>

#define USB_SUBCLASS_CODE   USB_SUBCLASS_GAOTONG
#define USB_MBIM_FUNC_NAME  "usb_mbim"

#else
#include "usb_vendor.h"
#include "bsp_sram.h"
#include "usb_platform_comm.h"
#include "bsp_pmu.h"

#define USB_SUBCLASS_CODE   USB_SUBCLASS_BALONG
#define USB_MBIM_FUNC_NAME  "ncm"

#endif

#endif
