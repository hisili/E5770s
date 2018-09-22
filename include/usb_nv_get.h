
#ifndef __USB_NV_GET_H__
#define __USB_NV_GET_H__

#include "usb_platform_comm.h"
#include "usb_debug.h"
#include "hw_pnp.h"

#define MODE_NUM   16


typedef enum
{
    /*|==================================|*/
#ifdef MBB_USB_UNITARY_Q                /*|                                  |*/
    USB_NV_SERIAL_NUM_ID      = 50049,  /*|��ͨƽ̨����SN�̶����            |*/
#else                                   /*|                                  |*/
    USB_NV_SERIAL_NUM_ID      = 26,     /*|balongƽ̨����SN�̶����          |*/
#endif                                  /*|                                  |*/
    USB_NV_ITEM_AT_SHELL_OPEN = 33,     /*|balongƽ̨ shell �˿ڿ���         |*/
    USB_NV_FACTORY_MODE_I     = 36,     /*|balongƽ̨ ��������ģʽ           |*/
    USB_NV_SD_WORKMODE        = 51,     /*|balongƽ̨ ��¼SD������ģʽ       |*/
    USB_NV_PID_UNIFICATION_ID = 50071,  /*|PID�ɶ�����                       |*/
    USB_NV_PORT_INFO_ID       = 50091,  /*|�˿ڿ�����                        |*/
    USB_NV_MASS_DYNAMIC_NAME  = 50108,  /*|�������ƿɶ���                    |*/
    USB_NV_DYNAMIC_INFO_NAME  = 50109,  /*|�豸���ƿɶ���                    |*/
    USB_NV_PROT_OFFSET_ID     = 50110,  /*|VDF���ƶ˿�                       |*/
    /*|--�ض�����VDF�˿�Э���ֶ�(����)   |*/
    USB_NV_FEATURE_WWAN       = 50151,  /*|WWAN���ܿɶ���                    |*/
    USB_NV_WINBLUE_PRF_ID     = 50424,  /*|MBIM���ܿɶ���                    |*/
    USB_NV_NET_SPEED_ID       = 50456,  /*|�����ϱ���PC����������            |*/
    /*|--Ŀǰ�����������ϱ�          |*/
    USB_NV_USB_PRIVATE_INFO   = 50498,   /*|USB log�ɿ���                     |*/
    USB_NV_SECURITY_FLAG      = 50577,    /*|USB����ģʽ�˿�ʹ������       |*/
#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
    USB_NV_FTEN_SWITCH_SEL    = 50607,    /*|����˫usb�л�����             |*/
#endif
} usb_nv_item;                          /*|==================================|*/


typedef struct COMMON_NV_TYPE
{
    USB_UINT nv_status;
    USB_UINT8 reserved;
} nv_huawei_common_type;

/*NV 26*/
typedef struct tagUSB_NV_SERIAL_NUM_T
{
    USB_UINT usbSnNvStatus;
    USB_UINT usbSnNvSucFlag;
} USB_NV_SERIAL_NUM_T;


/* NV 50049 SN enable */
typedef struct NV_HUAWEI_SN_REPORT_ENABLE_I
{
    USB_UINT    nv_status;
    USB_UINT8   sn_enable;
} nv_huawei_sn_report_enable;

/* �Զ��� PIDʹ�� */
typedef struct PID_ENABLE
{
    USB_UINT pid_enabled;
} nv_pid_enable_type;

/* NV 50067 SD enable */
typedef struct NV_HUAWEI_FIRST_REPORT_PORT_I
{
    USB_UINT    nv_status;
    USB_UINT8   sd_enable;
} nv_huawei_first_report_port;

/* 50071 PID */
typedef struct PRODUCT_PID
{
    USB_UINT nv_status;
    USB_UINT16 cust_first_pid;
    USB_UINT16 cust_rewind_pid;
} nv_cust_pid_type;

/* NV 50080 CD enable */
typedef struct NV_HUAWEI_DISABLE_CDROM_I
{
    USB_UINT nv_status;
    USB_UINT8     cd_enable;
} nv_huawei_disable_cdrom;

/* 50091 �˿���̬ */
typedef struct PACKED_POST
{
    USB_UINT nv_status;
    USB_UINT8 first_port_style[DYNAMIC_PID_MAX_PORT_NUM];
    USB_UINT8 rewind_port_style[DYNAMIC_PID_MAX_PORT_NUM];
    USB_UINT8 reserved[USB_NUM_22];
} nv_huawei_dynamic_pid_type;

/* NV 50108 CD/SD name*/
typedef struct NV_HUAWEI_DYNAMIC_NAME_I
{
    USB_UINT nv_status;
    USB_UINT8 huawei_cdrom_dynamic_name[DYNAMIC_CD_NAME_CHAR_NUM];
    USB_UINT8 huawei_sd_dynamic_name[DYNAMIC_CD_NAME_CHAR_NUM];
    USB_UINT8 reserved[USB_NUM_32];
} nv_huawei_dynamic_name;

/* NV 50109 ports name*/
typedef struct NV_HUAWEI_DYNAMIC_INFO_NAME_I
{
    USB_UINT nv_status;
    USB_UINT8 huawei_product_dynamic_name[DYNAMIC_INFO_NAME_CHAR_NUM];
    USB_UINT8 huawei_manufacturer_dynamic_name[DYNAMIC_INFO_NAME_CHAR_NUM];
    USB_UINT8 huawei_configuration_dynamic_name[DYNAMIC_INFO_NAME_CHAR_NUM];
    USB_UINT8 reserved[USB_NUM_8];
} nv_huawei_dynamic_info_name;
#ifndef MBB_USB_UNITARY_Q
/* 50110 �ӿ�Э����� */
typedef struct PROTOCOL_BASE
{
    USB_UINT nv_status;
    USB_UINT protocol_base;
} nv_protocol_base_type;
#else
typedef struct PROTOCOL_BASE
{
    USB_UINT nv_status;
    USB_UINT8 protocol_base;
    USB_UINT8 reserved[USB_NUM_20];
} nv_protocol_base_type;

#endif
/* 50115 WIN7 wwan���� */
typedef struct NV_HUAWEI_WWAN_CUSTOMIZATION
{
    USB_UINT  nv_status;
    USB_UINT8 wwan_work_flag;
} nv_feature_wwan;

/*50424*/
typedef struct DRV_WINBLUE_PROFILE_TYPE
{
    USB_UINT8  InterfaceName[32];
    USB_UINT8  MBIMEnable;
    USB_UINT8  CdRom;
    USB_UINT8  TCard;
    USB_UINT8  MaxPDPSession;
    USB_UINT16 IPV4MTU;
    USB_UINT16 IPV6MTU;
    USB_UINT32 Reserved1;
    USB_UINT32 Reserved2;
} nv_winblue_profile_type;

/*50456*/
typedef struct USB_CDC_NET_SPEED_TYPE
{
    USB_UINT32  nv_status;
    USB_UINT32  net_speed;  //��λΪbps(����300Mbps=300*1000*1000 bps),ע�ⵥλ����1024
    USB_UINT32  reserve1;
    USB_UINT32  reserve2;
    USB_UINT32  reserve3;
} usb_cdc_net_speed_type;

/*50498*/
typedef struct USB_PRIVATE_NV_INFO
{
    USB_UINT   nv_status;
    USB_UINT8  debug_mode[MBB_LAST];
    USB_UINT32 reserve[10];
} usb_private_nv_info;

#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
/* 50607 */
typedef struct
{
    unsigned char nv_status;
    unsigned char usb_sel_flag;
    unsigned char reserve1;
    unsigned char reserve2;
}nv_ften_usb_switch_sel;
#endif

/*50577*/
typedef struct
{
unsigned char nv_status;    /*��nv�Ƿ񼤻�*/
unsigned char diag_enable;  /*diag�˿��Ƿ�ʹ��*/
unsigned char shell_enable; /*shell�˿��Ƿ�ʹ��*/
unsigned char adb_enable;   /*adb�˿��Ƿ�ʹ��*/
unsigned char om_enable;   /*om�˿��Ƿ�ʹ��*/
unsigned char ucReserved_0; /*�����ֶ�*/
unsigned char ucReserved_1; /*�����ֶ�*/
unsigned char ucReserved_2; /*�����ֶ�*/
}nv_huawei_usb_security_flag;

/*define struct ,list all correlative usb nv*/
typedef struct mbb_usb_nv_info
{
    nv_cust_pid_type               pid_info ;              //USB_NV_PID_UNIFICATION_ID
    nv_huawei_dynamic_pid_type     dev_profile_info ; //USB_NV_PORT_INFO_ID
#ifdef MBB_USB_UNITARY_Q
    nv_huawei_sn_report_enable     stUSBNvSnSupp ; //USB_NV_SERIAL_NUM_ID
#else
    USB_NV_SERIAL_NUM_T            stUSBNvSnSupp ; //USB_NV_SERIAL_NUM_ID
#endif
    nv_feature_wwan                feature_wwan;  //USB_NV_FEATURE_WWAN
    USB_UINT                       factory_mode ;    //USB_NV_FACTORY_MODE_I
    USB_UINT                       ulSDWorkMode;     //USB_NV_SD_WORKMODE
    USB_UINT                       shell_lock;       //USB_NV_ITEM_AT_SHELL_OPEN
    nv_huawei_dynamic_name         mass_dynamic_name; //USB_NV_MASS_DYNAMIC_NAME
    nv_huawei_dynamic_info_name    port_dynamic_name;   //USB_NV_DYNAMIC_INFO_NAME
    nv_protocol_base_type          stDevProtOfsInfo;  //USB_NV_PROT_OFFSET_ID
    nv_winblue_profile_type        winblue_profile;
    usb_cdc_net_speed_type         net_speed_info;
    usb_private_nv_info            usb_log_ctl;
#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)
    nv_ften_usb_switch_sel       usb_ften_switch_sel;    //USB_NV_FTEN_SWITCH_SEL
#endif
    nv_huawei_usb_security_flag    usb_security_flag;   //USB_NV_SECURITY_FLAG
} mbb_usb_nv_info_st;

/*==============================================================================
 *===============================API����=================================
 *============================================================================*/
/****************************************************************
 �� �� ��  : debug_init
 ��������  : debug��ʼ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : NA
*****************************************************************/
USB_VOID    usb_nv_init(USB_VOID);
/****************************************************************
 �� �� ��  : debug_init
 ��������  : debug��ʼ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : NA
*****************************************************************/
/*��ȡNV�ļ��ӿ�*/
USB_INT     usb_nv_get(USB_VOID);
/****************************************************************
 �� �� ��  : debug_init
 ��������  : debug��ʼ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : NA
*****************************************************************/
USB_INT     get_shell_lock(USB_VOID);
/****************************************************************
 �� �� ��  : debug_init
 ��������  : debug��ʼ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : NA
*****************************************************************/
/*��ģ���ȡNVֵ�ӿ�*/
mbb_usb_nv_info_st*  usb_nv_get_ctx(USB_VOID);
/****************************************************************
 �� �� ��  : debug_init
 ��������  : debug��ʼ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : NA
*****************************************************************/
USB_VOID usb_nv_dump(USB_VOID);

#endif