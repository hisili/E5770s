

/*lint --e{537}*/


#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/mtd/flash_huawei_dload.h>

#include <product_config.h>
#include <hi_syssc_interface.h>
#include <osl_types.h>
#include <bsp_sram.h>
#include <drv_nv_id.h>
#include <drv_nv_def.h>
#include <comm_nv_def.h>
#include <bsp_version.h>
#include <bsp_nvim.h>


#include "SysNvId.h"

/*
*--------------------------------------------------------------*
* �궨��                                                       *
*--------------------------------------------------------------*
*/


#define HUAWEI_DLOAD_CDROM_VERSION_LEN           128
#define HUAWEI_DLOAD_NAME_MAX_LEN    256
/* iso_info_flag_type�ṹ����sizeof()����ռ���ʵ����ռ�ռ�Ĳ�ֵ */
#define DIFFERENCE 3 


/*ȫ�ֱ����������Ʒ��Ϣ,version ��ʼ������nvֵ*/
PRODUCT_INFO_NV_STRU huawei_product_info =
{
	0
};



/*lint -save -e958*/
static __inline__ int bsp_version_default_set(void)
{
    u32 iret;
	u32 hw_ver;/*Ӳ���汾��*/

	hw_ver=*(u32 *)HW_VERSION_ADDR;/*get hardware version*/

    /*read nv,get the exc protect setting*/
    /*lint -save -e26 -e119*/
    iret = bsp_nvm_read(NV_ID_DRV_NV_VERSION_INIT,(u8*)&huawei_product_info,sizeof(PRODUCT_INFO_NV_STRU));
	/*lint -restore*/

    if(NV_OK != iret)
    {
        ver_print_error("version init read nv error,not set,use the default config!\n");
        return VER_ERROR;
    }

	/*δ���ҵ�hwVer*/
	if(hw_ver!=huawei_product_info.index){
		ver_print_error("product info is not defined, pls check product_info_tbl!HKADC read:0x%x,nv read:0x%x\n",hw_ver,huawei_product_info.index);
		huawei_product_info.index = hw_ver;
		return VER_ERROR;
	}

	return VER_OK;

}


int bsp_productinfo_init(void)
{
	int iret=0;

	/*TODO:����������Ӱ汾�ţ���Ҫ����*/

    /*����ֲ��ṹ�������ڴ棬����ʼ��Ϊȫ0*/
    memset((void *)(&huawei_product_info), 0, sizeof(PRODUCT_INFO_NV_STRU));
	iret = bsp_version_default_set();
	if(VER_ERROR==iret){
		ver_print_error("bsp version version_default_set fail!\n");
	}

	ver_print_error("bsp version init OK!\n");
	return iret;
}


char * bsp_version_get_hardware(void)
{
	unsigned int len;
	static bool b_geted=false;
	static char hardware_version[VERSION_MAX_LEN];
	char hardware_sub_ver = 0;
	/*����ΪӲ�ˣ���ˣ�����UDP*/
	if((HW_VER_INVALID == huawei_product_info.index))
	{
		ver_print_error("init error\n");
    	return NULL;
	}

	if(!b_geted){
        /*v711ƽֻ̨��һ��Ӳ���汾�ŵĲ�Ʒ��Ҫ�ڴ����Ӳ��id���жϣ�Ver.A���ֶ���Ҫ��NV 0XD115�����*/
        if(( HW_VER_PRODUCT_E5771S_856 == huawei_product_info.index) || (HW_VER_PRODUCT_506HW == huawei_product_info.index) \
        || ( HW_VER_PRODUCT_E5573CS_609 == huawei_product_info.index) || ( HW_VER_PRODUCT_E5573CS_322 == huawei_product_info.index) \
        || ( HW_VER_PRODUCT_E5573CS_931 == huawei_product_info.index) || ( HW_VER_PRODUCT_E5673S_609 == huawei_product_info.index) \
        || ( HW_VER_PRODUCT_E5573CS_609_B == huawei_product_info.index) || ( HW_VER_PRODUCT_E5573CS_322_B == huawei_product_info.index) \
        || ( HW_VER_PRODUCT_E5573CS_931_B == huawei_product_info.index) || ( HW_VER_PRODUCT_E5673S_609_B == huawei_product_info.index) \
        || (HW_VER_PRODUCT_E5577DS_156 == huawei_product_info.index) || ( HW_VER_PRODUCT_E5577BS_932 == huawei_product_info.index ) \
        || ( HW_VER_PRODUCT_E5573CS_323_B == huawei_product_info.index) || ( HW_VER_PRODUCT_506HW_2 == huawei_product_info.index) \
        || ( HW_VER_PRODUCT_E5573BS_322 == huawei_product_info.index) || ( HW_VER_PRODUCT_E5573CS_933 == huawei_product_info.index)\
        || ( HW_VER_PRODUCT_E5573CS_509 == huawei_product_info.index)|| ( HW_VER_PRODUCT_E5577BS_937 == huawei_product_info.index)\
        || ( HW_VER_PRODUCT_607HW == huawei_product_info.index) || ( HW_VER_PRODUCT_R218h == huawei_product_info.index))
        {
            strncat(hardware_version, huawei_product_info.hwVer, strlen(huawei_product_info.hwVer));
        }
        else
        {
            /*lint -save -e18 -e718 -e746*/
            len = (unsigned int)(strlen(huawei_product_info.hwVer) + strlen(" Ver.X"));
            /*lint -restore*/

            hardware_sub_ver = ((char)huawei_product_info.hwIdSub % 3)+'A';

            (void)memset((void *)hardware_version, 0, MemparamType(len));
            /* coverity[secure_coding] */
            strncat(strncat(hardware_version, huawei_product_info.hwVer, strlen(huawei_product_info.hwVer)), " Ver.", strlen(" Ver."));
            *((hardware_version + len) - 1) = hardware_sub_ver;
            *(hardware_version + len) = 0;
        }
		b_geted=true;
	}
	/*�Ӱ汾�Ŵ�ȷ��*/
        return (char *)hardware_version;
}

char * bsp_version_get_hardware_no_subver(void)
{
    int len;
    static bool b_geted = false;
    static char hardware_version_no_subver[VERSION_MAX_LEN];
    //char hardware_sub_ver = 0;

    /*����ΪӲ�ˣ���ˣ�����UDP*/
    if((HW_VER_INVALID == huawei_product_info.index))/*lint !e10*/
    {
            ver_print_error("init error\n");
            return NULL;
    }
    /*���û�ж�ȡ���汾��*/
    if(!b_geted)
    {
        /*ͳ���ַ����*/
        len = strlen(huawei_product_info.hwVer);/*lint !e10*/

        memset((void *)hardware_version_no_subver, 0, len);/*lint !e160 !e506*/
        /* coverity[secure_coding] */
        strncat(hardware_version_no_subver, huawei_product_info.hwVer, strlen(huawei_product_info.hwVer));/*lint !e10*/
        *(hardware_version_no_subver + len) = 0;
        /*��ȡ�汾�ű����Ϊtrue*/
        b_geted = true;
    }
    /*����Ӳ���汾�ţ������Ӱ汾��*/
    return (char *)hardware_version_no_subver;

}

char * bsp_version_get_product_inner_name(void)
{
	unsigned int len;
	static bool b_geted=false;
	static char product_inner_name[VERSION_MAX_LEN];

	if( HW_VER_INVALID == huawei_product_info.index)
	{
		return NULL;
	}

	if(!b_geted){
		len = (unsigned int)(strlen(huawei_product_info.name)+ strlen(huawei_product_info.namePlus));

		(void)memset((void*)product_inner_name, 0, MemparamType(len));

		/* coverity[secure_coding] */
		strncat(strncat(product_inner_name,huawei_product_info.name, strlen(huawei_product_info.name)), huawei_product_info.namePlus, strlen(huawei_product_info.namePlus));

		*(product_inner_name+len) = 0;
		b_geted=true;
	}

	return  (char*)product_inner_name;

}


char * bsp_version_get_product_out_name(void)
{
	if(HW_VER_INVALID == huawei_product_info.index)
	{
		return NULL;
	}

	return (char *)huawei_product_info.productId;
}


char * bsp_version_get_pcb(void)
{
	if(HW_VER_INVALID == huawei_product_info.index)
	{
		return NULL;
	}

	return (char *)huawei_product_info.hwVer;
}


char * bsp_version_get_dloadid(void)
{
	if(HW_VER_INVALID == huawei_product_info.index)
	{
		return NULL;
	}

	return (char *)huawei_product_info.dloadId;
}


char * bsp_version_get_build_date_time(void)
{
	static char * build_date   = __DATE__ ", " __TIME__;
	return build_date;
}


char * bsp_version_get_chip(void)
{
	return (char *)PRODUCT_CFG_CHIP_SOLUTION_NAME;
}


char * bsp_version_get_firmware(void)
{
	u32 iret = VER_OK;
	static NV_SW_VER_STRU nv_sw_ver={0};

	/*��ȡNV���е�����汾��*/
    /*lint -save -e26 -e119*/
	iret=bsp_nvm_read(NV_ID_DRV_NV_DRV_VERSION_REPLACE_I, \
				(u8 *)&nv_sw_ver,
				sizeof(NV_SW_VER_STRU));
    /*lint -restore*/

    if(NV_OK != iret){/*�����ȡʧ�ܣ��򷵻�Ĭ�ϰ汾��*/
		ver_print_info("get NV_SW_VERSION_REPLACE failed!\n");
		return (char*)PRODUCT_DLOAD_SOFTWARE_VER;
	}
	else{
		if(0 == nv_sw_ver.nvStatus){
			ver_print_info("nv_sw_ver.nvStatus :%d\n",nv_sw_ver.nvStatus);
			return (char*)PRODUCT_DLOAD_SOFTWARE_VER;
		}
	}

	return (char *)nv_sw_ver.nv_version_info;
}


char * bsp_version_get_hash(void)
{
	return CFG_PRODUCT_TAG_ID;
}


char * bsp_version_get_iso(void)
{
	/**TODO:  ��ʱ�ȷ��������ֵ,������isover��δ洢*/

	#define ISO_VER "00.000.00.000.00"
	return (char *)ISO_VER;
}

#define PAGE_SIZE_MAX 4096
s32 huawei_get_spec_num_upinfo(char* str, s32 str_len, s32 num)
{
    rec_updinfo_st rec_info = {0};
    char *format_str = "%s%s\r\n\r\n%s%s\r\n\r\n%s%s\r\n\r\n%s%d\r\n\r\n%s%d";
    
    if(NULL == str)
    {
        return VER_ERROR;
    }
    /* get update info from oeminfo area */
    (void)flash_get_share_region_info( RGN_RECORD_UPINFO_FLAG, 
                        (void *)(&rec_info), sizeof(rec_updinfo_st));

    if(DLOAD_RECORD_UPDATE_MAGIC != rec_info.magic_num)
    {
        /* oeminfo is empty, return */
        return VER_ERROR;
    }
    if(num > rec_info.upinfo_record_times)
    {
        /* para err */
        return VER_ERROR;
    }
    snprintf(str, str_len, format_str, 
                "bswver: ", 
                rec_info.upswver_info[num - 1].bswver,
                "aswver: ",
                rec_info.upswver_info[num - 1].aswver,
                "uptime: ",
                rec_info.upswver_info[num - 1].uptime,
                "uptype: ",
                rec_info.upswver_info[num - 1].uptype,
                "upstatus: ",
                rec_info.upswver_info[num - 1].upstatus
            );
    return VER_OK;
    
}

void huawei_get_update_info_times(s32* times)
{
    rec_updinfo_st rec_info = {0};
    if(NULL == times)
    {
        return;
    }

    /* get update info from oeminfo area */
    (void)flash_get_share_region_info(RGN_RECORD_UPINFO_FLAG, 
                        (void *)(&rec_info), sizeof(rec_updinfo_st));
    if(DLOAD_RECORD_UPDATE_MAGIC != rec_info.magic_num)
    {
        /* oeminfo is empty, return 0 */
        *times = 0;
    }
    else
    {
        *times = rec_info.upinfo_record_times;
    }
    return;
}

void huawei_set_update_info(char* str)
{
    rec_updinfo_st rec_info = {0};
    update_info_st update_info = {{0}, {0}, 0};
    uint8 i = 0;
    uint32 cur_times = 0;
    int8* firmware_ver = NULL;
    int8 ret_buf[PAGE_SIZE_MAX] = {0};
    if(NULL == str)
    {
        ver_print_error("str is null\n");
        return;
    }
    memcpy(&update_info, str, sizeof(update_info_st));
    /* get update info from oeminfo area */
    (void)flash_get_share_region_info( RGN_RECORD_UPINFO_FLAG, 
                        (void *)(&rec_info), sizeof(rec_updinfo_st));

    /* check the magic */
    if(DLOAD_RECORD_UPDATE_MAGIC != rec_info.magic_num)
    {
        rec_info.total_times = 1;
        rec_info.upinfo_record_times = 1;
        cur_times = rec_info.upinfo_record_times - 1;
        ver_print_error("rec_info.magic_num is not magic\n");
    }
    else
    {
        /* if the current update status is 1, update this struct */
        if(UPDATE_BEGIN_STATUS == rec_info.upswver_info[rec_info.upinfo_record_times - 1].upstatus)
        {
            cur_times = rec_info.upinfo_record_times - 1;  // 4 = 5 - 1
            ver_print_error("repeat at ,times is %d\n", rec_info.upinfo_record_times);
        }
        else
        {
            if(RECORD_MAX_TIMES <= rec_info.upinfo_record_times)
            {
                /* << ,set the back info to front */
                for(i = 0; i < RECORD_MAX_TIMES - 1; i++)
                {
                    rec_info.upswver_info[i] = rec_info.upswver_info[i + 1];
                }
                (void)memset(&rec_info.upswver_info[RECORD_MAX_TIMES - 1], 0, sizeof(updswver_info_st));
                rec_info.upinfo_record_times = RECORD_MAX_TIMES;
                cur_times = RECORD_MAX_TIMES - 1;   /* set cur_times -> 10 - 1 */
            }
            else
            {
                cur_times = rec_info.upinfo_record_times;
                rec_info.upinfo_record_times++;
                ver_print_error("update at ,times is %d\n", rec_info.upinfo_record_times);
            }
        }
    }

    /* update the target software version */
    (void)strncpy(rec_info.upswver_info[cur_times].aswver, update_info.ver_info, VERSION_LENGTH - 1);

    /* update the current software version */
    firmware_ver = bsp_version_get_firmware();
    if(NULL != firmware_ver)
    {
        ver_print_error("the before version :%s\n", rec_info.upswver_info[cur_times].bswver);
        (void)memset(rec_info.upswver_info[cur_times].bswver, 0, VERSION_LENGTH);
        (void)strncpy(rec_info.upswver_info[cur_times].bswver, firmware_ver, strlen(firmware_ver));
        ver_print_error("the current version :%s\n", rec_info.upswver_info[cur_times].bswver);
    }

    /* update the current upgrade UTC time */
    (void)strncpy(rec_info.upswver_info[cur_times].uptime, update_info.time_info, VERSION_LENGTH - 1);
    
    /* update the tools type */
    rec_info.upswver_info[cur_times].uptype = update_info.tooltype;

    /* update the record times */
    rec_info.upswver_info[cur_times].upstatus = UPDATE_BEGIN_STATUS;
    
    /* update the magic number */
    rec_info.magic_num = DLOAD_RECORD_UPDATE_MAGIC;
    memcpy(ret_buf, &rec_info, sizeof(rec_updinfo_st));

    (void)flash_update_share_region_info(RGN_RECORD_UPINFO_FLAG, (void *)ret_buf, sizeof(rec_updinfo_st));
    return;
}


/*****************************************************************************
* �� �� : bsp_get_webui_version
* �� �� : ��ȡwebui_version
* �� �� : 
str:����webui�汾��
           len:��Ҫ��ȡ��webui�汾�ų���
* �� �� : ��
* �� �� : ��
* ˵ �� :��ȡ����ָ�벻�����ͷ�
*****************************************************************************/
void bsp_get_web_version(char *str,int len)
{
    unsigned int   verLen = 0;
    unsigned char   bufTmp[WEBUI_VER_BUF_LEN] = {0};
    webver_buffer_s  *webver_info = NULL;
    char  webui_ver[WEBUI_VER_BUF_LEN] = "WEBUI_00.00.00.000.03";

    /*����ж�*/
    if(NULL == str || len < WEBUI_VER_BUF_LEN)
    {
        ver_print_error("Input parameter error!.\r\n");
        return ;
    }
    
    /*��ȡ��������汾��Ϣ�ַ�����Ϣ*/ 
    verLen = WEBUI_VER_BUF_LEN;
    memset(bufTmp, 0, WEBUI_VER_BUF_LEN);

    /* ��ȡISO�汾�� */
    /*lint -e429*/
    if (true == flash_get_share_region_info(RGN_WEBHD_FLAG,bufTmp,verLen))
    {
        webver_info = (webver_buffer_s*)bufTmp;
        if (webver_info->magic_number == WEBUI_VER_FLAG_MAGIC)
        {
            memset(str, 0, len);
            snprintf((char*)str, WEBUI_VER_BUF_LEN, "%s", webver_info->version_buffer);
            ver_print_error("flash_get_share_region_info ture. \r\n");
        }
        else
        {
            memset(str, 0, len);
            snprintf((char*)str, WEBUI_VER_BUF_LEN, "%s", webui_ver);
            ver_print_error("flash_get_share_region_info ture iso null.\r\n");
        }
    }
    else
    {
        memset(str, 0, len);
        snprintf((char*)str, WEBUI_VER_BUF_LEN, "%s", webui_ver);
        ver_print_error("flash_get_share_region_info false.\r\n");
    }
    return;    
}



void bsp_get_iso_version(char *str,int len)
{
    unsigned int   verLen = 0;
    unsigned char   bufTmp[HUAWEI_DLOAD_CDROM_VERSION_LEN] = {0};
    iso_info_flag_type  *iso_version_info = NULL;
    char  iso_ver[HUAWEI_DLOAD_CDROM_VERSION_LEN] = "00.00.00.000.00";

    /*����ж�*/
    if(NULL == str || len < HUAWEI_DLOAD_CDROM_VERSION_LEN)
    {
        ver_print_error("Input parameter error!.\r\n");
        return ;
    }
    
    /*��ȡ��������汾��Ϣ�ַ�����Ϣ*/ 
    verLen = HUAWEI_DLOAD_CDROM_VERSION_LEN;
    memset(bufTmp, 0, HUAWEI_DLOAD_CDROM_VERSION_LEN);

    /* ��ȡISO�汾�� */
    /*lint -e429*/
    if (true == flash_get_share_region_info(RGN_ISOHD_FLAG,bufTmp,verLen))
    {
        iso_version_info = (iso_info_flag_type*)bufTmp;
        if (iso_version_info->in_use_flag == FLASH_OEM_REGION_IN_USE_FLAG 
            && iso_version_info->iso_info_magic == DLOAD_ISO_VERSION_MAGIC)
        {
            memset(str, 0, len);
            /*  �˴�Ϊ3�Ǹ���iso_info_flag_type�ṹ��ԭ������*/
            snprintf((char*)str, HUAWEI_DLOAD_CDROM_VERSION_LEN, "%s", \
                    bufTmp + sizeof(iso_info_flag_type) - DIFFERENCE);
             ver_print_error("flash_get_share_region_info ture. \r\n");
        }
        else
        {
            memset(str, 0, len);
            snprintf((char*)str, HUAWEI_DLOAD_CDROM_VERSION_LEN, "%s", iso_ver);
            ver_print_error("flash_get_share_region_info ture iso null.\r\n");
        }
    }
    else
    {
        memset(str, 0, len);
        snprintf((char*)str, HUAWEI_DLOAD_CDROM_VERSION_LEN, "%s", iso_ver);
        ver_print_error("flash_get_share_region_info false.\r\n");
    }
    return ;
}


char * bsp_version_get_webui(void)
{
	/**TODO:  ͬisover*/
	return NULL;
}


char * bsp_version_get_release(void)
{
	/**TODO:  */
	return PRODUCT_VERSION_STR;
}


int bsp_version_get_boardid(void)
{
    int hw_ver=0;
	hw_ver=*(int *)HW_VERSION_ADDR;/*get hardware version*/

	return hw_ver;
}
/*****************************************************************************
* ����	: bsp_get_board_chip_type
* ����	: get board type and chip type
* ����	: void
* ���	: void
* ����	: BOARD_TYPE_E
*****************************************************************************/
u32 bsp_version_get_board_type(void)
{
    unsigned int type = 0xffffffff;
	type = (u32)bsp_version_get_boardid();

	if(HW_VER_INVALID==type){
		ver_print_error("[bsp_get_board_chip_type]:get hw version failed!hw_ver:0x%x\n",type);
		return type;
	}

	/*��Ϊudp��ֻ����UDPӲ���汾�ţ�������Ƶ�۰���Ϣ*/
	if(HW_VER_UDP_MASK==(type & HW_VER_UDP_MASK)){
		return HW_VER_PRODUCT_UDP;
	}

	/*��Ϊk3v3UDP,ֻ����UDPӲ���汾��*/
	if(HW_VER_K3V3_UDP_MASK == (type & HW_VER_K3V3_UDP_MASK)){
		return HW_VER_K3V3_UDP;
	}

	/*��Ϊk3v3FPGA,ֻ����FPGAӲ���汾��*/
	if(HW_VER_K3V3_FPGA_MASK == (type & HW_VER_K3V3_FPGA_MASK)){
		return HW_VER_K3V3_FPGA;
	}

	if(HW_VER_V711_UDP_MASK == (type & HW_VER_V711_UDP_MASK)){
		return HW_VER_V711_UDP;
	}

	return type;
}
u32 bsp_version_get_chip_type(void)
{
	return get_hi_version_id_version_id();
}


/*****************************************************************************
* �� �� ��  : bsp_version_get_baseline
*
* ��������  : ��ȡ��˼���߰汾��
*
* �������  : ��
* �������  :
*
 �� �� ֵ  : ����汾���ַ���ָ��
* �޸ļ�¼  :
*
*****************************************************************************/
char * bsp_version_get_baseline(void)
{
      /* ����V7R2���߰汾 */
    return (char*)PRODUCT_VERSION_STR;
}


int bsp_get_factory_mode(void)
{
    #define FACTORY_MODE_MAGIC_STR  "+=+=+==factory_mode+=+=+==\n"
    int ret = -1;
    FACTORY_MODE_TYPE  real_factory_mode;

    /* ��������Ϊ������ģʽ */
    ret = NVM_Read(en_NV_Item_SW_VERSION_FLAG, &real_factory_mode, sizeof(FACTORY_MODE_TYPE));/*lint !e18*/
    if(0 != ret)        
    {
        printk("DR_NV_Read error, default to normal mode\n");
        return 1;
    }

    if(1 == real_factory_mode.ulFactoryMode)
    {
        printk("normal mode\n");
        return 1;
    }
    else
    {
        printk(FACTORY_MODE_MAGIC_STR);
        return 0;
    }
}



char* bsp_dload_get_dload_version(void)
{
	return (char *)DLOAD_VERSION;
}


int bsp_dload_get_dload_info(struct dload_info_type* dload_info)
{
	char *dload_iso = NULL;
	char *product_name = NULL;
	char *firmware = NULL;

	/*��ȡiso version*/
	dload_iso = bsp_version_get_iso();
	if(NULL == dload_iso){
		ver_print_error("get iso ver is null!\n");
		return VER_ERROR;
	}
	/* coverity[secure_coding] */
	strncat(dload_info->iso_ver,dload_iso,strlen(dload_iso));

	/*��ȡdload id(������ʹ�õĲ�Ʒ��)*/
	product_name = bsp_version_get_dloadid();
	if(NULL == product_name){
		ver_print_error("get product name is null\n");
		return VER_ERROR;
	}
	/* coverity[secure_coding] */
	strncat(dload_info->product_name,product_name,strlen(product_name));

	/*��ȡsoftware_version*/
	firmware = bsp_version_get_firmware();
	if(NULL == firmware){
		ver_print_error("get firmware version is null\n");
		return VER_ERROR;
	}
	/* coverity[secure_coding] */
	strncat(dload_info->software_ver,firmware,strlen(firmware));

	return VER_OK;

}
/*��Ҫ��֤��nvģ���ʼ��֮��*/
module_init(bsp_productinfo_init);

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
BOARD_ACTUAL_TYPE_E bsp_get_board_actual_type(void)
{
	u32 chip_ver = 0;

	chip_ver = bsp_version_get_chip_type();

	switch(chip_ver){
		case CHIP_VER_P531_ASIC:
		case CHIP_VER_P532_ASIC:
			return BOARD_TYPE_BBIT;

		case CHIP_VER_HI6950_ASIC:			
		case CHIP_VER_HI3630_ASIC:
		case CHIP_VER_HI6921_ASIC:
		case CHIP_VER_HI6930_ASIC:
			return BOARD_TYPE_ASIC;

		case CHIP_VER_HI6950_SFT:
			return BOARD_TYPE_SFT;

		default:
			return BOARD_TYPE_MAX;		
	}
}


int bsp_version_debug(void)
{
	int ret=0;
	struct dload_info_type info={"\0","\0","\0"};

	/*�ж�version��ʼ���Ƿ�ɹ�*/
    if(huawei_product_info.index == HW_VER_INVALID){
		ver_print_error("huawei_product_info init failed!HW_VERSION_ADDR:0x%x\n",*(u32 *)HW_VERSION_ADDR);
		return VER_ERROR;
	}
	ver_print_error("\n***************************************************\n");
	ver_print_error("\n*************huawei_product_info*******************\n");
	ver_print_error("\n***************************************************\n");
	ver_print_error("Hardware index	:0x%x\n",huawei_product_info.index);
	ver_print_error("hw_Sub_ver		:0x%x\n",huawei_product_info.hwIdSub);
	ver_print_error("Inner name 	:%s\n",huawei_product_info.name);
	ver_print_error("name plus 		:%s\n",huawei_product_info.namePlus);
	ver_print_error("HardWare ver	:%s\n",huawei_product_info.hwVer);
	ver_print_error("DLOAD_ID		:%s\n",huawei_product_info.dloadId);
	ver_print_error("Out name		:%s\n",huawei_product_info.productId);

	ver_print_error("\n***************************************************\n");
	ver_print_error("\n*************from func get*******************\n");
	ver_print_error("\n***************************************************\n");
	ver_print_error("Board ID   	:0x%x\n",bsp_version_get_boardid());
	ver_print_error("Chip Type   	:0x%x\n",bsp_version_get_chip_type());
	ver_print_error("HardWare ver	:%s\n",bsp_version_get_hardware());
	ver_print_error("Inner name		:%s\n",bsp_version_get_product_inner_name());
	ver_print_error("Out name		:%s\n",bsp_version_get_product_out_name());
	ver_print_error("PCB_ver		:%s\n",bsp_version_get_pcb());
	ver_print_error("DLOAD_ID		:%s\n",bsp_version_get_dloadid());
	ver_print_error("Build_time		:%s\n",bsp_version_get_build_date_time());
	ver_print_error("Chip_ver		:%s\n",bsp_version_get_chip());
	ver_print_error("Firmware		:%s\n",bsp_version_get_firmware());
	ver_print_error("CommitID		:%s\n",bsp_version_get_hash());
	ver_print_error("ISO_ver		:%s\n",bsp_version_get_iso());
	ver_print_error("WebUI			:%s\n",bsp_version_get_webui());
	ver_print_error("Release_ver	:%s\n",bsp_version_get_release());


	ver_print_error("dload_version	:%s\n",bsp_dload_get_dload_version());
	ret=bsp_dload_get_dload_info(&info);
	return VER_OK|ret;
}
/*lint -restore*/

/**********************************************************************
�� �� ��  :bsp_get_product_hw_board_type
��������  : ����E5770s ��Ʒ����
�������  : �ޡ�
�������  : �ޡ�
�� �� ֵ  : 0��E5770s-923 ���� 1��E5770s-320����
ע������  : �ޡ�
***********************************************************************/
