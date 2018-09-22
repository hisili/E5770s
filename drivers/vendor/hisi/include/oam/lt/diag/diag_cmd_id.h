

#ifndef __DIAG_CMD_ID_H__
#define __DIAG_CMD_ID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
/******************************************************************************/
/*******************************1 ����ID����BEGIN****************************/
/******************************************************************************/
#define DIAG_CMD_DSP_TRANS_BASE_ID      (0x00000000) // DSP
#define DIAG_CMD_PS_BASE_ID             (0x00001000) // PS
#define DIAG_CMD_BSP_BASE_ID            (0x00003000) // BSP
#define DIAG_CMD_MSP_BASE_ID            (0x00005000) // MSP
#define DIAG_CMD_DSP_CT_BASE_ID         (0x00010000)
#define DIAG_CMD_APP_BASE_ID            (0x00010F00) // DSP
#define DIAG_CMD_END                    (0xFFFFFFFF)

#define DIAG_IS_DSP_CMD(x)              (((x)>=DIAG_CMD_DSP_TRANS_BASE_ID) && ((x)<DIAG_CMD_PS_BASE_ID))
#define DIAG_IS_PS_CMD(x)               (((x)>=DIAG_CMD_PS_BASE_ID)  && ((x)<DIAG_CMD_BSP_BASE_ID))
#define DIAG_IS_BSP_CMD(x)              (((x)>=DIAG_CMD_BSP_BASE_ID) && ((x)<DIAG_CMD_MSP_BASE_ID))
#define DIAG_IS_MSP_CMD(x)              (((x)>=DIAG_CMD_MSP_BASE_ID) && ((x)<DIAG_CMD_DSP_CT_BASE_ID))
#define DIAG_IS_CT_DSP_CMD(x)           (((x)>=DIAG_CMD_DSP_CT_BASE_ID) && ((x)<DIAG_CMD_APP_BASE_ID))

/*1.	HSO���ӹ����ࣨ0x5000-0x50ff��*/
#define DIAG_CMD_HOST_CONNECT                   (0x5000)
#define DIAG_CMD_HOST_DISCONNECT                (0x5001)
#define DIAG_CMD_MODEM_WILL_RESET               (0x5002)
#define DIAG_CMD_SET_LOG_MODE                   (0x5057)
#define DIAG_CMD_GET_TIMESTAMP_INIT_VALUE       (0x7000)
/*2.	��ʱ�ࣨ0x5100-0x51ff��*/
#define DIAG_CMD_TIMER_OUT_IND                  (0x5100)
#define DIAG_CMD_PS_REPLAY_SET                  (0x5101)

/*3.	���ɲ����ࣨ0x5200-0x52ff��*/
#define DIAG_CMD_REG_RD				            (0x5205)
#define DIAG_CMD_REG_WR                         (0x5206)
#define DIAG_CMD_DRX_DATA_SAMPLE_REG_WR         (0x5214)
#define DIAG_CMD_DRX_LOG_SAMPLE_REG_WR          (0x5215)
#define DIAG_CMD_DRX_REG_WR_SAMPLE_IND          (0x5216)
#define DIAG_CMD_DRX_REG_WR_LOG_IND             (0x5217)

/* �͹�������ͨ������*/
#define DIAG_CMD_DRX_SAMPLE_GEN_REQ             (0x521B)
/* �͹�������Hids ��ȡ����ַ*/
#define DIAG_CMD_DRX_SAMPLE_ADDR_REQ            (0x521C)

/* �͹������ɻ�ȡͨ����С*/
#define DIAG_CMD_DRX_SAMPLE_CHNSIZE_REQ         (0x521D)

/* �͹������ɻ�ȡ�汾��Ϣ*/
#define DIAG_CMD_DRX_SAMPLE_GET_VERSION_REQ     (0x521E)

/* �͹���������������ͨ����ַ*/
#define DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ       	(0x521F)
/*4.	���������ࣨ0x5300-0x53ff��*/
#define DIAG_CMD_LOG_CAT_PRINT                   (0x5310)
#define DIAG_CMD_LOG_CAT_LAYER                   (0x5311)
#define DIAG_CMD_LOG_CAT_AIR                     (0x5312)
#define DIAG_CMD_LOG_CAT_USERPLANE               (0x5313)
#define DIAG_CMD_LOG_CAT_L1                      (0x5314)
#define DIAG_CMD_LOG_CAT_EVENT                   (0x5315)
#define DIAG_CMD_LOG_CAT_CMD                     (0x5316)
#define DIAG_CMD_LOG_CAT_MSG                     (0x5317)


/* BSP CFG BEGIN*/
#define DIAG_CMD_DRX_BSP_SLEEP_IND               (0x5220)					//�͹��Ŀ�ά�ɲ��ϱ�IND
#define DIAG_CMD_DRX_CHIP_TEMP_IND               (0x5221)					//�͹��Ŀ�άоƬ�¶��ϱ�IND
#define DIAG_CMD_DRX_BATTERIES_TEMP_IND          (0x5222)					//�͹��Ŀ�ά����¶��ϱ�IND

#define DIAG_CMD_BSP_LOG_SET_ACORE               (0x5308)
#define DIAG_CMD_BSP_LOG_SET_CCORE               (0x5309)

#define DIAG_CMD_BSP_SYSVIEW_SWT_ACORE           (0x530A)
#define DIAG_CMD_BSP_SYSVIEW_SWT_CCORE           (0x530B)

#define DIAG_CMD_BSP_SYSVIEW_IND_ACORE           (0x5310)
#define DIAG_CMD_BSP_SYSVIEW_IND_CCORE           (0x5311)

#define DIAG_CMD_BSP_AXI_DATA_SAMPLE             (0x530C)
#define DIAG_CMD_BSP_AXI_DATA_EXPORT             (0x530D)
#define DIAG_CMD_BSP_AXI_DATA_MONITOR            (0x530F)
#define DIAG_CMD_AXI_DATA_CONFIG                 (0x5318)
#define DIAG_CMD_AXI_REG_CONFIG                  (0x5319)
#define DIAG_CMD_AXI_DATA_CTRL                   (0x531A)
#define DIAG_CMD_AXI_MON_CONFIG                  (0x531B)
#define DIAG_CMD_AXI_MON_START                   (0x531C)
#define DIAG_CMD_AXI_MON_TERMINATE               (0x531D)

#define DIAG_CMD_UTRACE_START                    (0x531E)
#define DIAG_CMD_UTRACE_TERMINATE                (0x531F)

#define DIAG_CMD_BSP_CPU_SWT_ACORE           (0x5320)
#define DIAG_CMD_BSP_CPU_SWT_CCORE           (0x5321)


/*5.	�Զ����ࣨ0x5400-0x54ff��*/
#define DIAG_CMD_GTR_SET                         (0x5454)

/*6.	NV�����ࣨ0x5500-0x55ff��*/
#define DIAG_CMD_NV_WR                           (0x5501)
#define DIAG_CMD_NV_RD                           (0x5503)
#define DIAG_CMD_NV_IMPORT                       (0x5508)
#define DIAG_CMD_NV_EXPORT                       (0x550A)

/*7.	�ļ������ࣨ0x5600-0x56ff��*/
#define DIAG_CMD_FS_QUERY_DIR                    (0x5601)
#define DIAG_CMD_FS_SCAN_DIR                     (0x5602)
#define DIAG_CMD_FS_MAKE_DIR                     (0x5603)
#define DIAG_CMD_FS_OPEN                         (0x5604)
#define DIAG_CMD_FS_IMPORT                       (0x5605)
#define DIAG_CMD_FS_EXPORT                       (0x5606)
#define DIAG_CMD_FS_DELETE                       (0x5607)
#define DIAG_CMD_FS_SPACE                        (0x5608)
/******************************************************************************/
/*******************************1 ����ID����END******************************/
/******************************************************************************/


/******************************************************************************/
/*******************************2 ����궨�嶨��BEGIN*********************/
/******************************************************************************/

/* �����Ϣģ�����Ͷ���*/
#define DIAG_CMD_LAYER_MOD_SRC                      (0)
#define DIAG_CMD_LAYER_MOD_DST                      (1)

/* NV�������Ͷ���*/
#define DIAG_CMD_EXPORT_FILE_TYPE_INITIAL           (0)
#define DIAG_CMD_EXPORT_FILE_TYPE_CURRENT           (1)
#define DIAG_TRANSFER_BLOCK_MAX_SIZE                (2*1024)

/* ��־���Ͷ���*/
#define DIAG_CMD_LOG_CATETORY_PRINT_ID              (1<<15)
#define DIAG_CMD_LOG_CATETORY_EVENT_ID              (1<<14)
#define DIAG_CMD_LOG_CATETORY_AIR_ID                (1<<13)
#define DIAG_CMD_LOG_CATETORY_LAYER_ID              (1<<12)
#define DIAG_CMD_LOG_CATETORY_MSG_ID                (1<<10)
#define DIAG_CMD_LOG_CATETORY_USERPLANE_ID          (1<<9)


#define DIAG_CFG_USER_PLANE_ID_NUM                    8
#define DIAG_CFG_CAT_CFG_NUM                          50

/* MSP ��HSO���ӡ������,ע����U32�ĳ�U8*/
#define DIAG_CMD_LOG_CFG_PRINT_LEVEL_NONE                             (0x80000000)
#define DIAG_CMD_LOG_CFG_PRINT_LEVEL_ERROR                            (0x40000000)
#define DIAG_CMD_LOG_CFG_PRINT_LEVEL_WARNING                          (0x20000000)
#define DIAG_CMD_LOG_CFG_PRINT_LEVEL_NORMAL                           (0x10000000)
#define DIAG_CMD_LOG_CFG_PRINT_LEVEL_INFO                             (0x08000000)

#define DIAG_CMD_REQ_LOG_CFG_FILTER_SWT_CLOSE                         (0x00000000)
#define DIAG_CMD_REQ_LOG_CFG_FILTER_SWT_OPEN                          (0x80000000)
#define GU_DIAG_CMD_REQ_LOG_CFG_FILTER_SWT_OPEN                       (0x00000001)

#define DIAG_CFG_PRINT_TOTAL_MODULE_SWT_NOT_USE       (0xFFFFFFFF)
#define DIAG_CFG_PRINT_TOTAL_MODULE                   (0xFFFFFFFF)
/******************************************************************************/
/*******************************2 ����궨�嶨��END***********************/
/******************************************************************************/

/*SOCPͷSID:����HiStudio�����Modem������״̬*/
#define MSP_SOCP_SID_DEFAULT              (0x0)
#define MSP_SOCP_SID_AT_SERVER            (0x1) /* AT Service*/
#define MSP_SOCP_SID_DIAG_SERVER          (0x2) /* DIAG Service�����������Ϣ���*/
#define MSP_SOCP_SID_DATA_SERVER          (0x3) /* DATA Service�������������*/
#define MSP_SOCP_SID_NV_SERVER            (0x4) /* NV Service��NV�����*/

/*SOCPͷ usSSId:����λ����,����λ;SSIDָ��App CPU*/
#define MSP_SOCP_HIGH4BIT_SSID_ACPU       (0x1)
#define MSP_SOCP_HIGH4BIT_SSID_MCPU       (0x2)
#define MSP_SOCP_HIGH4BIT_SSID_LTE_DSP    (0x3)
#define MSP_SOCP_HIGH4BIT_SSID_LTE_BBP    (0x4)
#define MSP_SOCP_HIGH4BIT_SSID_GU_DSP     (0x5)
#define MSP_SOCP_HIGH4BIT_SSID_HIFI       (0x6)
#define MSP_SOCP_HIGH4BIT_SSID_TDS_DSP    (0x7)
#define MSP_SOCP_HIGH4BIT_SSID_TDS_BBP    (0x8)
#define MSP_SOCP_HIGH4BIT_SSID_MCU        (0x9)
#define MSP_SOCP_HIGH4BIT_SSID_GPU        (0xA)
#define MSP_SOCP_HIGH4BIT_SSID_GU_BBP     (0xB)

/*SOCPͷ ucServiceSessionId:��ʶService��Client֮�������*/
#define MSP_SOCP_SERVER_SESSION_ID        (0x1) /* Service Session ID�̶�Ϊ1*/

/*SOCPͷ ucMsgType: ��ʾ��Ϣ���ͣ���6���ر�������Ϊ0����2����ȡֵ����*/
#define MSP_SOCP_MSG_TYPE_REQ             (0x1) /* ����*/
#define MSP_SOCP_MSG_TYPE_CNF             (0x2) /* ��Ӧ*/
#define MSP_SOCP_MSG_TYPE_IND             (0x3) /* �ϱ�*/


/* �ṹ��ID�����һ��������λ(28~31)���ֶ�*/
#define MSP_STRU_ID_28_31_GROUP_MSP       (0x1)
#define MSP_STRU_ID_28_31_GROUP_PS        (0x2)
#define MSP_STRU_ID_28_31_GROUP_LTE_DSP   (0x3)
#define MSP_STRU_ID_28_31_GROUP_LTE_BBP   (0x4)
#define MSP_STRU_ID_28_31_GROUP_HSO       (0x5)
#define MSP_STRU_ID_28_31_GROUP_TDS_BBP   (0x6)
#define MSP_STRU_ID_28_31_GROUP_TDS_DSP   (0x7)
#define MSP_STRU_ID_28_31_GROUP_GU_PS     (0x8)
#define MSP_STRU_ID_28_31_GROUP_BSP    	  (0x9)

/* �ṹ��ID����Ķ���������λ(16_23)���ֶ�,��Ӧ��һ���ֶ���MSP_STRU_ID_28_31_GROUP_PS*/
#define MSP_STRU_ID_16_23_TYPE_AIR        (0x1) /* �տ�*/
#define MSP_STRU_ID_16_23_TYPE_LAYER      (0x2) /* ���*/
#define MSP_STRU_ID_16_23_TYPE_PRINT      (0x3) /* ��ӡ*/
#define MSP_STRU_ID_16_23_TYPE_EVENT      (0x4) /* �¼�*/
#define MSP_STRU_ID_16_23_TYPE_USER       (0x5) /* �û���*/
#define MSP_STRU_ID_16_23_VoLTE           (0x6)
#define MSP_STRU_ID_16_23_TYPE_DOT        (0x7) /* ����ӡ*/

/* �ṹ��ID����Ķ���������λ(16_23)���ֶ�,��Ӧ��һ���ֶ���MSP_STRU_ID_28_31_GROUP_MSP*/
#define MSP_STRU_ID_16_23_MSP_CMD         (0x1) /* HSO���ø�����Ŀ������������[0x5000,0x6FFF]*/
#define MSP_STRU_ID_16_23_PS_TRANS        (0x2) /* PS ͸�����������[0x1000,0x2FFF]*/
#define MSP_STRU_ID_16_23_BSP_PMU         (0x3) /* BSP ͸�����������[0x3000,0x4FFF]*/
#define MSP_STRU_ID_16_23_IND_MSP         (0x5) /* MSP �ڲ������ϱ���IND����[0x5000,0x6FFF]*/
#define MSP_STRU_ID_16_23_SYS_CMD         (0x6) /* ���� ��HSO���ӵ�ϵͳ����[0x5000,0x6FFF]*/

/* �ṹ��ID����Ķ���������λ(16_23)���ֶ�,��Ӧ��һ���ֶ���MSP_STRU_ID_28_31_GROUP_BSP*/
#define MSP_STRU_ID_16_23_BSP_CMD         (0x1) /* BSP�ڲ�������*/


/*FILE OPEN MODE*/
#define DIAG_FS_RDONLY            (00000000)          /* +1 == FREAD */
#define DIAG_FS_WRONLY            (00000001)          /* +1 == FWRITE */
#define DIAG_FS_RDWR              (00000002)          /* +1 == FREAD|FWRITE */
#define DIAG_FS_CREAT             (00000100)          /* open with file create */
#define DIAG_FS_EXCL              (00000200)          /* error on open if file exists */
#define DIAG_FS_TRUNC             (00001000)          /* open with truncation */
#define DIAG_FS_APPEND            (00002000)          /* append (writes guaranteed at the end) */
#define DIAG_FS_DIRECTORY         (00040000)

#define DIAG_CMD_FILE_NAME_LEN    (64)
#define MSP_DF_DIR_MAX_LEN        (256)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum DIAG_FOLDER_TYPE_ENUM
{
    DIAG_FS_ROOT_FOLDER = 0,
    DIAG_FS_LOG_FOLDER,
    DIAG_FS_DUMP_FOLDER,
    DIAG_FS_FOLDER_BUTT
};

/*Ŀ¼�и��������*/
typedef enum
{
    DIAG_FS_ITEM_FOLDER = 0,
    DIAG_FS_ITEM_FILE,
    DIAG_FS_ITEM_BUTT
}OM_ITEM_TYPE_ENUM;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of diag_cmd_id.h */
