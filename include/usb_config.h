

#ifndef __USB_CONFIG_H__
#define __USB_CONFIG_H__

#include <product_config.h>
/*===================ƽ̨����� BEGIN==============*/

//#define MBB_USB_UNITARY_Q     /*�����ͨƽ̨�ĺ�*/
#define MBB_USB_UNITARY_B     /*�������ƽ̨�ĺ�*/
/*==================ƽ̨����� END==============*/

/*===================���ܺ�BEGIN==============*/

// #define MBB_USB_DEBUG

#if (FEATURE_ON == MBB_USB_MULTICONFIG)
#define USB_MULTICONFIG
#endif

#if (FEATURE_ON == MBB_USB_SECURITY)
#define USB_SECURITY
#endif

#if (FEATURE_ON == MBB_USB_SD)
#define USB_SD
#endif

#if (FEATURE_ON == MBB_USB_CPE)
#define USB_CPE
#endif

#if (FEATURE_ON == MBB_USB_E5)
#define USB_E5
#endif

#if (FEATURE_ON == MBB_USB_HILINK)
#define USB_HILINK
#endif

#if (FEATURE_ON == MBB_USB_STICK)
#define USB_STICK
#endif

#if (FEATURE_ON == MBB_USB_WINGLE)
#define USB_WINGLE
#endif

#if (FEATURE_ON == MBB_USB_CAPABILITY_THREE)
#define USB_SUPER_SPEED
#endif

#if (FEATURE_ON == MBB_CHARGE)
#define USB_CHARGE

#if (FEATURE_ON == MBB_CHG_EXTCHG)
#define USB_CHARGE_EXT
#endif

#endif

#if (FEATURE_ON == MBB_FAST_ON_OFF)
#define USB_FAST_ON_OFF
#endif

#ifdef CONFIG_BALONG_RNDIS
#define USB_RNDIS
#endif

#if (FEATURE_ON == MBB_DLOAD)
#define USB_DLOAD
#endif/*USB_DLOAD*/

/* ˫оƬCPE��Ʒ,��ʹ�õ��Ķ����ڼ��മ��ģʽ */
/* #define USB_DUAL_CORE_CPE */

/* ����������
#define MBB_CHG_EXTCHG
#define CONFIG_USB_OTG
#define CONFIG_GADGET_SUPPORT_REMOTE_WAKEUP
#define CONFIG_NCM_MBIM_SUPPORT
#define MBB_CHG_WIRELESS
#define MBB_DLOAD
#define NCM_ENCAP_CMD_CID_ENABLED
#define CONFIG_USB_GADGET_SUPERSPEED
#define GNET_SINGLE_INTERFACE
#define GNET_CLASS_TYPE_HUAWEI
#define CONFIG_BUS_PCI
#define CONFIG_GNET_PREALLOC_RX_MEM
#define CONFIG_GNET_PREALLOC_TX_MEM
*/

/*===================���ܺ� END==============*/
#endif
