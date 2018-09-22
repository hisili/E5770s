
#ifndef __BSP_VERSION_H__
#define __BSP_VERSION_H__
#ifdef __cplusplus
extern "C" {
#endif

#include <bsp_shared_ddr.h>
#include <drv_version.h>

#include <bsp_om.h>

#define CFG_PRODUCT_TAG_ID "193c25990102eeb27f5ed9243d9a01e144e3efc4"
#define DLOAD_VERSION               "2.0"                   /* ����Э��汾 */
#define VERSION_MAX_LEN 32
#define VERSION_ISO_MAX_LEN  128
#define VERSION_WEBUI_MAX_LEN  128

#define HW_VERSION_ADDR SHM_MEM_HW_VER_ADDR

#ifndef VER_ERROR
#define VER_ERROR (-1)
#endif

#ifndef VER_OK
#define VER_OK 0
#endif

#ifdef __VXWORKS__
#define StrParamType (unsigned int)
#define MemparamType (int)
#else
#define StrParamType (int)
#define MemparamType (unsigned int)
#endif

/*log*/
#define  ver_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_VERSION, "[version]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  ver_print_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_VERSION, "[version]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(a) (sizeof(a)/(sizeof((a)[0])))
#endif

struct dload_info_type{
	char software_ver[VERSION_MAX_LEN];
	char product_name[VERSION_MAX_LEN];
	char iso_ver[VERSION_MAX_LEN];
};

/*****************************************************************************
* �� �� ��  	: bsp_get_hardware_version
*
* ��������  	: ��ȡӲ���汾��
*
* �������  	: ��
* �������  	: Ӳ���汾���ַ���ָ��
*
* �� �� ֵ  	: 0��ȡ�ɹ�
			-1��ȡʧ��
*
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_hardware(void);
#if (FEATURE_ON == MBB_COMMON)
/*****************************************************************************
* �� �� ��   : bsp_version_get_hardware_no_subver
*
* ��������   : ��ȡӲ���汾��
*
* �������   : ��
* �������   : Ӳ���汾���ַ���ָ��
*
* �� �� ֵ   : 0��ȡ�ɹ�
             -1��ȡʧ��
*
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_hardware_no_subver(void);
#endif

/*****************************************************************************
* �� �� ��  : bsp_get_product_inner_name
*
* ��������  : ��ȡ�ڲ���Ʒ����
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : �ڲ���Ʒ�����ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_product_inner_name(void);

/*****************************************************************************
* �� �� ��  : bsp_get_product_out_name
*
* ��������  : ��ȡ�ڲ���Ʒ����
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : �ⲿ��Ʒ�����ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_product_out_name(void);

/*****************************************************************************
* �� �� ��  : bsp_get_pcb_version
*
* ��������  : ��ȡPCB
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : PCB�ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_pcb(void);

/*****************************************************************************
* �� �� ��  : bsp_get_dloadid_version
*
* ��������  : ��ȡdloadid
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : dloadid�ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_dloadid(void);

/*****************************************************************************
* �� �� ��  : bsp_get_build_date_time
*
* ��������  : ��ȡ�������ں�ʱ��
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : ����汾���ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_build_date_time(void);

/*****************************************************************************
* �� �� ��  : bsp_get_chip_version
*
* ��������  : ��ȡоƬ�汾��
*
* �������  : ��
* �������  :
*
 �� �� ֵ  :оƬ�汾���ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_chip(void);

/*****************************************************************************
* �� �� ��  : bsp_get_firmware_version
*
* ��������  : ��ȡ����汾��
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : ����汾���ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_firmware(void);

/*****************************************************************************
* �� �� ��  : bsp_get_version_hash
*
* ��������  : ��ȡ������Ŀ��hashֵ
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : ������Ŀ�hashֵ�ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_hash(void);

/*****************************************************************************
* �� �� ��  : bsp_get_iso_version
*
* ��������  : ��ȡiso_version
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : iso_version�ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_iso(void);


void bsp_get_iso_version(char *str,int len);

#if (FEATURE_ON == MBB_DLOAD)
/*****************************************************************************
* �� �� ��  : bsp_get_web_version
*
* ��������  : ��ȡwebui_version
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : webui_version�ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
void bsp_get_web_version(char *str,int len);
#endif /* MBB_DLOAD */

/*****************************************************************************
* �� �� ��  : bsp_get_webui_version
*
* ��������  : ��ȡwebui_version
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : webui_version�ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_get_webui_version(void);

/*****************************************************************************
* �� �� ��  : bsp_get_release_version
*
* ��������  : ��ȡrelease_version
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : release_version�ַ�����ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_release(void);

int bsp_version_get_boardid(void);

/*****************************************************************************
* ����	: bsp_get_board_chip_type
* ����	: get board type and chip type
* ����	: void
* ���	: void
* ����	: BOARD_TYPE_E
*****************************************************************************/
u32 bsp_version_get_board_type(void);

int bsp_dload_get_dload_info(struct dload_info_type* dload_info);

bool bsp_board_type_is_gutl(void);


int bsp_version_debug(void);


void bsp_version_init(void);


int bsp_productinfo_init(void);

/*****************************************************************************
* ����	: bsp_get_board_actual_type
* ����	: get board actual type 
* ����	: void
* ���	: void
* ����	: BOARD_ACTUAL_TYPE_E       BBIT/SFT/ASIC
*
* ����       : ��
*
*****************************************************************************/
BOARD_ACTUAL_TYPE_E bsp_get_board_actual_type(void);

#if (FEATURE_ON == MBB_DLOAD)
/*****************************************************************************
* ����	: huawei_set_update_info
* ����	: set update info 
* ����	: void
* ���	: void
* ����	: void
*
* ����       : ��
*
*****************************************************************************/
void huawei_set_update_info(char* str);

/*****************************************************************************
* ����	: huawei_get_update_info_times
* ����	: get update info times
* ����	: NA 
* ���	: times: num of upgrade 
* ����	: void 
*
* ����       : ��
*
*****************************************************************************/
void huawei_get_update_info_times(s32* times);

/*****************************************************************************
* ����	: huawei_get_spec_num_upinfo
* ����	: get info of once update 
* ����	: num : index of upgrade
* ���	: void
* ����	: 0��ȡ�ɹ�/-1��ȡʧ��
*
* ����       : ��
*
*****************************************************************************/
s32 huawei_get_spec_num_upinfo(char* str, s32 str_len, s32 num);
#endif
#ifdef __cplusplus
}
#endif

#endif

