/*
 * ============================== DRV_RHPC.H ===================================
 * Header file of Remote Host Procedure Call Intefaces.
 * This is the header file of remote host procedure call proxy layer.
 *
 * Copyright (c) 2013-2014 Huawei Device Co.,LTD
 * Author(s): Jasper.Han <HanJiuping@huawei.com>
 * Created At: 19/06/2013
 *
 *
 */



#ifndef __DRV_RHPC_H__
#define __DRV_RHPC_H__


#include <linux/chip_comm_api.h>
#include "drv_comm.h"

typedef enum drv_rhpc_req_cmd_t
{
    /*R2M, start form 0x00*/
    DRV_RHPC_REQ_R2M_CMD_BEGIN_IDX = 0,
    DRV_RHPC_REQ_GPIO_DIR_SET_CMD = DRV_RHPC_REQ_R2M_CMD_BEGIN_IDX,
    DRV_RHPC_REQ_GPIO_INPUT_LEVEL_GET_CMD,
    DRV_RHPC_REQ_GPIO_OUTPUT_LEVEL_SET_CMD,
    DRV_RHPC_REQ_ONLINEUPDATE_REBOOT_CMD,
    DRV_RHPC_REQ_ROUTER_HWVER_GET_CMD,
    DRV_RHPC_REQ_MMI_USIM_STATUS_GET_CMD,
    /*Add your commands here.*/
    DRV_RHPC_REQ_R2M_CMD_GET_DATALOCK_STATUS_CMD,
    DRV_RHPC_REQ_R2M_CMD_SET_CUSTOMIZE_ITEM_TO_DEFAULT_CMD,
    DRV_RHPC_REQ_R2M_CMD_WRITE_MMI_NV_FLAG_CMD,
    DRV_RHPC_REQ_R2M_CMD_CLEAR_MMI_NV_CMD,

    DRV_RHPC_REQ_R2M_CMD_GET_UPG_STATUS,
    
	DRV_RHPC_REQ_R2M_CMD_QUERY_TEMP_CMD,
    
    DRV_RHPC_REQ_MODEM_LED_SET,

    DRV_RHPC_REQ_R2M_CMD_MAX_IDX,
    DRV_RHPC_REQ_R2M_CMD_END_IDX = 0x7F, 
    
    /*M2R, start form 0x80*/
    DRV_RHPC_REQ_M2R_CMD_BEGIN_IDX = 0x80,
    DRV_RHPC_REQ_DFU_NOTIFY_STATUS_CMD = DRV_RHPC_REQ_M2R_CMD_BEGIN_IDX,
    /*Add your commands here.*/
    DRV_RHPC_REQ_M2R_CM_SET_UPG_STATUS = 0x81,
    DRV_RHPC_REQ_M2R_CMD_GET_NV_VALUE = 0x82,
    DRV_RHPC_REQ_M2R_CMD_WRITE_NV_VALUE = 0x83,
    DRV_RHPC_REQ_M2R_CMD_MAX_IDX,
    DRV_RHPC_REQ_M2R_CMD_END_IDX = 0xFF,
    DRV_RHPC_REQ_CMD_RESERVED = 0xFFFFFFFF, /*We take 4bytes.*/
}drv_rhpc_req_cmd_t;

typedef struct drv_rhpc_data_t
{
    drv_rhpc_req_cmd_t cmd;
    uint32_t           idx;
    int32_t            val;
    uint32_t           len;
    char               data[0];
}drv_rhpc_data_t;

#define UPDATE_INFO_FILE_PATH_NAME           ("/online/update_info.bin")

#define UPDATE_COMPONENTS_NUM     (1)

#pragma pack(4)
typedef enum
{
    UPG_STATUS_NONE = 0,        
    UPG_STATUS_NV_RESTORE_FAIL,         
    UPG_STATUS_NV_RESTORE_SUCCESS, 
    UPG_STATUS_MAX
} MODEM_UPG_STATUS;

typedef enum _COMPONENT_TYPE
{
    FIRMWARE1,
    FIRMWARE2,
    ISO,
    WEB_UI,
    UPDATE_INFO,
    COMPONENT_COUNT
}COMPONENT_TYPE;

typedef enum _UPDATE_TYPE
{
    HUAWEI_PRIVATE,
    OMA_FOTA,      
    UPDATE_TYPE_COUNT
}UPDATE_TYPE;

typedef enum _COMPRESS_TYPE
{
    NO_COMPRESS,
    LZMA,      /*����LZMA�㷨ѹ��*/
    ZIP,        /*Ŀǰ��֧��*/
    COMPRESS_TYPE_COUNT
}COMPRESS_TYPE;

typedef enum _UPDATE_MESSAGE_TYPE
{
    IDLEUP = 10,
    QUERYING = 11,
    NEWVERSIONFOUND = 12,
    DOWNLOAD_FAILED = 20,
    DOWNLOAD_PROGRESSING = 30,
    DOWNLOADPENDING = 31,
    DOWNLOAD_COMPLETE = 40,
    READY_TO_UPDATE = 50,
    UPDATE_PROGRESSING = 60,
    UPDATE_FAILED_HAVE_DATA = 70,
    UPDATE_FAILED_NO_DATA = 80,
    UPDATE_SUCCESSFUL_HAVE_DATA = 90,
    UPDATE_SUCCESSFUL_NO_DATA = 100,
    UPDATE_MESSAGE_TYPE_COUNT
}UPDATE_MESSAGE_TYPE, UPDATE_STATUS;

typedef enum
{
    UPGRADE_USB = 0,        /* USBһ������ */
    UPGRADE_ONLINE,         /* �������� */
    UPGRADE_NET_LOCAL,      /* �������� */
    UPGRADE_NET_MULTI,      /* �鲥���� */
    UPGRADE_MODE_COUNT
} UPGRADE_MODE;

typedef struct _UPDATE_INFOMATION
{
    UINT32 m_update_info_length;
    UPDATE_TYPE m_update_type;                /*������������*/
    COMPONENT_TYPE m_component_type;          /*�������*/
    COMPRESS_TYPE m_compress_type;            /*ѹ������*/
    UINT8 m_total_components;             /*���ΰ汾��⹲��⵽�����°汾���������*/
    UINT8 m_current_component_index;      /*��ǰ����������ڱ��������е����*/
    UPDATE_STATUS m_current_component_status; /*��ǰ�����������״̬*/
    UINT8 m_full;                         /*webuiɾ����־λ��1:ɾ�� 0:��ɾ*/
    UINT8 m_upgrade_mode;                 /* ����ģʽ */
    UINT8 m_reserved3;
    UINT8 m_reserved4;
    UINT32 m_component_length;
}UPDATE_INFOMATION;

#pragma pack()


typedef int (*drv_rhpc_msg_hdlr_func)(drv_rhpc_data_t*, void*, int*);

#endif /*__DRV_RHPC_H__*/

