#ifndef __PTABLE_COM_H__
#define __PTABLE_COM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <bsp_shared_ddr.h>

#ifndef __ASSEMBLY__
#include "bsp_sram.h"

/* ptable */
#define FSZ                             long unsigned int
#define NAND_OK                         0
#define NAND_ERROR                      1

/* �������� */
#if (FEATURE_ON == MBB_DLOAD)
/*��Ʒ�߷���IMAGE_ID ����*/
typedef enum IMAGE_TYPE
{
    IMAGE_SFS_START            = 0x0,        /*��̬�ļ� ��ʼ */
    /*flash����ӳ������ , �����������������Ҫ����������ӳ���־ */
    IMAGE_PTABLE               = 0x100,     /* ������ �����־*/
    IMAGE_M3BOOT               = 0x101,     /* M3 BOOT */
    IMAGE_FASTBOOT             = 0x102,     /* FASTBOOT���� �� */
    IMAGE_NVBACKLTE               = 0x103,     /* NV ���� ������*/ 
    IMAGE_NVIMG                = 0x104,     /* ����NV �� */
    IMAGE_NVDLD                = 0x105,     /* ����NV �� */
    IMAGE_NVFACTORY            = 0x106,     /* ����NV �� */
    IMAGE_KERNER               = 0x107,     /* Kernel ���� */
    IMAGE_KERNELBK             = 0x108,     /* Kernel ���ݷ���*/ 
    IMAGE_M3IMAGE              = 0x109,     /*M3 FIRMWARE ����*/
    IMAGE_CCORE                = 0x10A,     /* MCORE VWXORKS �� */
    IMAGE_DSP                  = 0x10B,     /* DSP ���� �� */
    IMAGE_LOGO                 = 0x10C,     /* LOGO ���� */
    IMAGE_OEMINFO              = 0x10D,     /* OEMONFO ���� �� */
    IMAGE_SYSTEM               = 0x10E,     /* SYSTEM.IMG ���� �� */
    IMAGE_OM                   = 0x10F,     /* ��ſ�ά�ɲ����� */
    IMAGE_WEBSDK               = 0x110,     /* APP.IMG ���� �� */
    IMAGE_WEBUI                = 0x111,     /* WEBUI ���� �� */
    IMAGE_RESERVE1             = 0x112,     /* Ԥ��1 ���� �� */
    IMAGE_RESERVE2             = 0x113,     /* Ԥ��2 ���� �� */
    IMAGE_RESERVE3             = 0x114,     /* Ԥ��3 ���� �� */
    IMAGE_USERDATA             = 0x115,     /* userdata ���� �� */
    IMAGE_BBOU                 = 0x116,     /* BBOU �������� ���� �� */
    IMAGE_MMC                  = 0x117,     /* MMC ��̨ ������*/ 
    IMAGE_CACHE                = 0x118,     /* CACHE ���� �� */
    IMAGE_RECOVERY_A           = 0x119,     /* RECOVERY���� ��  */
    IMAGE_RECOVERY_B           = 0x11A,     /* RECOVERY���� ��  */
    IMAGE_MISC                 = 0x11B,     /* MISC ���� �� */
#if(MBB_FEATURE_VSIM_HUK == FEATURE_ON)
    IMAGE_OEM                  = 0x11C,     /* OEM ���� ,VSIM������������Ų���Ԥ������*/
#endif /*MBB_FEATURE_VSIM_HUK*/
#ifdef BSP_CONFIG_BOARD_K5160
    IMAGE_OPENSRC              = 0x11D,     /* OPENSRC ��̨ ������*/ 
#endif
    IMAGE_M3IMAGEBK            = 0x11E,     /*M3 FIRMWARE ���ݷ���*/    
    IMAGE_PART_TOP             = 0x200      /*���������� ����*/
}IMAGE_TYPE_E;
#else
typedef enum IMAGE_TYPE
{
    /*һ����Ʒ�߾�̬�ļ����ط�ʽ���漰��Ʒ���޸ģ��ݱ�����̬���ط�ʽ*/
    IMAGE_SFS_START            = 0x0,        /*��̬�ļ� ��ʼ */
    IMAGE_CDROMISOVER          = 0x1,
    IMAGE_WEBUIVER             = 0x2,
    IMAGE_CFDNVTable           = 0x3,
    ZSP_FILE_ADDR              = 0x4,       /*[����ֵ],ƹ��Bootrom���룬������BOOTROM_BACKö�٣�
                                                Ϊ����֮ǰ�Ĵ�����߶����ZSP�ļ�ͷ��ַ*/
    ISO_FILE_ADDR              = 0x5,       /*[����ֵ],ƹ��Bootrom���룬������BOOTROM_BACKö�٣�
                                                Ϊ����֮ǰ�Ĵ�����߶����ZSP�ļ�ͷ��ַ*/
    IMAGE_SFS_TOP              = 0x50,      /*��̬�ļ�����*/

    /* ������̬�ļ�����ӳ�� */
    IMAGE_DFS_START            = 0x64,      /*100*//*��̬�ļ���ʼ*/

    IMAGE_DYN_WEBUI            = 0x65,      /*101*//*��Ʒ�߶�̬�ļ�����ӳ��*/
    IMAGE_DYN_FS               = 0x66,      /*102*//*����̬�ļ�����ӳ��*/

    IMAGE_DFS_TOP              = 0xfe,      /*��̬�ļ�����*/

    /* �� ��flash����ӳ������ , �����������������Ҫ����������ӳ���־ */
    IMAGE_PART_START           = 0xFF,      /*��̬�ļ� ��ʼ */

    IMAGE_PTABLE               = 0x100,     /* ������ �����־*/
    IMAGE_M3BOOT               = 0x101,     /* M3 BOOT */
    IMAGE_FASTBOOT             = 0x102,     /* FASTBOOT���� �� */
    IMAGE_NVBACKLTE            = 0x103,     /* NV ���� ������*/
    IMAGE_NVIMG                = 0x104,     /* ����NV �� */
    IMAGE_NVDLD                = 0x105,     /* ����NV �� */
    IMAGE_NVFACTORY            = 0x106,     /* ����NV �� */
    IMAGE_KERNEL               = 0x107,     /* Kernel ���� */
    IMAGE_KERNELBK             = 0x108,     /* Kernel ���ݷ���*/
    IMAGE_M3IMAGE              = 0x109,     /* M3 FIRMWARE ����*/
    IMAGE_CCORE                = 0x10A,     /* MCORE VWXORKS �� */
    IMAGE_DSP                  = 0x10B,     /* DSP ���� �� */
    IMAGE_LOGO                 = 0x10C,     /* LOGO ���� */
    IMAGE_OEMINFO              = 0x10D,     /* OEMONFO ���� �� */
    IMAGE_SYSTEM               = 0x10E,     /* SYSTEM.IMG ���� �� */
    IMAGE_OM                   = 0x10F,     /* ��ſ�ά�ɲ����� */
    IMAGE_APP                  = 0x110,     /* APP.IMG ���� �� */
    IMAGE_WEBUI                = 0x111,     /* WEBUI ���� �� */
    IMAGE_RESERVE1             = 0x112,     /* Ԥ��1 ���� �� */
    IMAGE_RESERVE2             = 0x113,     /* Ԥ��2 ���� �� */
    IMAGE_RESERVE3             = 0x114,     /* Ԥ��3 ���� �� */
    IMAGE_USERDATA             = 0x115,     /* userdata ���� �� */
    IMAGE_ONLINE               = 0x116,     /* ONLINE �������� ���� �� */
    IMAGE_CDROMISO             = 0x117,     /* CDROMISO ��̨ ������*/
    IMAGE_CACHE                = 0x118,     /* CACHE ���� �� */
    IMAGE_RECOVERY_A           = 0x119,     /* RECOVERY���� ��  */
    IMAGE_RECOVERY_B           = 0x11A,     /* RECOVERY���� ��  */
    IMAGE_MISC                 = 0x11B,     /* MISC ���� �� */
#if(MBB_FEATURE_VSIM_HUK == FEATURE_ON)
    IMAGE_OEM                  = 0x11C,     /* OEM ���� ,VSIM������������Ų���Ԥ������*/
#endif /*MBB_FEATURE_VSIM_HUK*/
    IMAGE_PART_TOP             = 0x200      /* ���������� ����*/

}IMAGE_TYPE_E;
#endif


#define PTABLE_IMAGE_TYPE_MASK          (0x7)

typedef enum FALSH_DATA_TYPE
{
    DATA_NORMAL                 = 0,    /*��ʾ�˷���ӳ��Ϊ��ͨ����������,��ռ��sp*/
    DATA_YAFFS                  = 1     /*��ʾ�˷���ӳ��Ϊyaffsӳ��,ռ��spare��*/
}FLASH_DATA_TYPE_E;

#define PTABLE_VALIDITY_OFFSET          (0x3)
#define PTABLE_VALIDITY_MASK            (0x1)

typedef enum FALSH_DATA_VALIDITY
{
    DATA_VALID                 = 0,    /*��ʾ�˷���ӳ������������Ч,����ʹ��(Ĭ��)*/
    DATA_INVALID               = 1     /*��ʾ�˷���ӳ�����ݿ��ܲ�����,������ʹ��*/
}FALSH_DATA_VALIDITY_E;

/*----------------------- |  0 byte
 |"pTableHead"            |
 *----------------------- | 12 byte (partition head flag string)
 | the property of table  |
 *----------------------- | 16 byte (partition table property)
 | bootrom version        |
 *----------------------- | 32 byte (partition bootrom ver string)
 | ptable version         |
 *----------------------- | 48 byte (partition ptable ver string)
ptabe head define 48 bytess*/
typedef struct ST_PTABLE_HEAD
{
	char 			head_str[12];
	unsigned int 	property;
	char 			product_ver_id[16];
	char 			ver_name[16];
}ST_PTABLE_HEAD_ST;

#define PTABLE_HEAD_STR                "pTableHead"

typedef struct ST_PART_TBL
{
    char             name[16];            /*name of this partition, uniquely*/
    unsigned int     offset;             /*offset in flash of this partition*/
    unsigned int     loadsize;           /*real data size of this partition, must smaller than "capacity"*/
    unsigned int     capacity;           /*total size of this partition*/
    unsigned int     loadaddr;           /*ram address of this this partition*/
    unsigned int     entry;              /*if the partition is executable,this is entry address of this partition*/
    unsigned int     image;              /*enum IMAGE_TYPE */
    unsigned int     property;           /*property of this partition, eg. exe, yaffs, fat, ram image ...*/
    unsigned int     count;              /*count for partition download or write*/
}ST_PART_TBL_ST;

#define PTABLE_HEAD_SIZE                sizeof(struct ST_PTABLE_HEAD)

/*ptabe TAIL define */
#define PTABLE_END_STR          "T" /*"pTableTail"*/

/*should move table head space*/
#define  PTABLE_PARTITION_MAX ((SHM_MEM_PTABLE_SIZE - PTABLE_HEAD_SIZE) / sizeof(struct ST_PART_TBL))

/*β��������ݣ�ʹ�ñ�������ľ�������ռ��DDRPTABLE_RAM_TABLE_SIZE��ʣ��ռ�*/
#define PTABLE_TAIL_SIZE   (SHM_MEM_PTABLE_SIZE - (PTABLE_PARTITION_MAX) * sizeof(struct ST_PART_TBL) - PTABLE_HEAD_SIZE)
#define PTABLE_TAIL_STR     "pTableTail"

typedef void (*funcptr)(void);

extern struct ST_PTABLE_HEAD ptable_head;
extern struct ST_PART_TBL ptable_product[];
extern unsigned int ptable_get_validity(struct ST_PART_TBL * ptable);
extern struct ST_PART_TBL * ptable_get_ram_data(void);

#define PART_TABLE_NAND_OFFSET      (FLASH_PTABLE_OFFSET)   /*��������flash�洢�ռ��ƫ��ֵ*/

#endif /* __ASSEMBLY__ */

#include "product_config.h"

/*entry define */
#define PTABLE_FASTBOOT_ENTRY           (FASTBOOT_ENTRY)
#define PTABLE_VXWORKS_CCORE_ENTRY      (MCORE_TEXT_START_ADDR)

#define PTABLE_FLASH_SIZE                (PRODUCT_CFG_FLASH_TOTAL_SIZE)
#define PTABLE_VER_STR                   PRODUCT_CFG_PTABLE_VER_NAME
#define PTABLE_VER_ID_STR      	         PRODUCT_CFG_PTABLE_VER_ID


/***********************************************************************
 * FLASH�ռ����
 ***********************************************************************/

/* M3boot */
#define PTABLE_M3_BOOT_START            (0)
#define PTABLE_M3_BOOT_LEN              (PRODUCT_CFG_FLASH_M3BOOT_LEN)
#define PTABLE_M3_BOOT_END              (PTABLE_M3_BOOT_START + PTABLE_M3_BOOT_LEN)

/* Fastboot */
#define PTABLE_FASTBOOT_START           PTABLE_M3_BOOT_END
#define PTABLE_FASTBOOT_LEN             (PRODUCT_CFG_FLASH_FASTBOOT_LEN)
#define PTABLE_FASTBOOT_END             (PTABLE_FASTBOOT_START + PTABLE_FASTBOOT_LEN)

/* NV LTE */
#define PTABLE_NV_LTE_START             PTABLE_FASTBOOT_END
#define PTABLE_NV_LTE_LEN               (PRODUCT_CFG_FLASH_NV_LTE_LEN)
#define PTABLE_NV_LTE_END               (PTABLE_NV_LTE_START + PTABLE_NV_LTE_LEN)

/* NvImg */
#define PTABLE_NVIMG_START              PTABLE_NV_LTE_END
#define PTABLE_NVIMG_LEN                (PRODUCT_CFG_FLASH_NV_IMG_LEN)
#define PTABLE_NVIMG_END                (PTABLE_NVIMG_START + PTABLE_NVIMG_LEN)

/* NvDload */
#define PTABLE_NVDLD_START              PTABLE_NVIMG_END
#define PTABLE_NVDLD_LEN                (PRODUCT_CFG_FLASH_NV_DLD_LEN)
#define PTABLE_NVDLD_END                (PTABLE_NVDLD_START + PTABLE_NVDLD_LEN)

/* NvDefault */
#define PTABLE_NVFACTORY_START          PTABLE_NVDLD_END
#define PTABLE_NVFACTORY_LEN            (PRODUCT_CFG_FLASH_NV_FACTORY_LEN)
#define PTABLE_NVFACTORY_END            (PTABLE_NVFACTORY_START + PTABLE_NVFACTORY_LEN)

/* OEM info */
#define PTABLE_OEMINFO_START            PTABLE_NVFACTORY_END
#define PTABLE_OEMINFO_LEN              (PRODUCT_CFG_FLASH_OEMINFO_LEN)
#define PTABLE_OEMINFO_END              (PTABLE_OEMINFO_START + PTABLE_OEMINFO_LEN)

/* YAFFS USER DATA */
#define PTABLE_YAFFS_USERDATA_START     PTABLE_OEMINFO_END
#define PTABLE_YAFFS_USERDATA_LEN       (PRODUCT_CFG_FLASH_YAFFS_USERDATA_LEN)
#define PTABLE_YAFFS_USERDATA_END       (PTABLE_YAFFS_USERDATA_START+PTABLE_YAFFS_USERDATA_LEN)

/* YAFFS ONLINE */
#define PTABLE_YAFFS_ONLINE_START       PTABLE_YAFFS_USERDATA_END
#define PTABLE_YAFFS_ONLINE_LEN         (PRODUCT_CFG_FLASH_YAFFS_ONLINE_LEN)
#define PTABLE_YAFFS_ONLINE_END         (PTABLE_YAFFS_ONLINE_START + PTABLE_YAFFS_ONLINE_LEN)

/* kernel */
#define PTABLE_BOOTIMAGE_START          PTABLE_YAFFS_ONLINE_END
#define PTABLE_BOOTIMAGE_LEN            (PRODUCT_CFG_FLASH_BOOTIMG_LEN)
#define PTABLE_BOOTIMAGE_END            (PTABLE_BOOTIMAGE_START + PTABLE_BOOTIMAGE_LEN)

/* kernelbak */
#define PTABLE_BOOTIMAGEBAK_START       PTABLE_BOOTIMAGE_END
#define PTABLE_BOOTIMAGEBAK_LEN         (PRODUCT_CFG_FLASH_BOOTIMGBAK_LEN)
#define PTABLE_BOOTIMAGEBAK_END         (PTABLE_BOOTIMAGEBAK_START + PRODUCT_CFG_FLASH_BOOTIMGBAK_LEN)

/* logo */
#define PTABLE_LOGO_START               PTABLE_BOOTIMAGEBAK_END
#define PTABLE_LOGO_LEN                 (PRODUCT_CFG_FLASH_LOGO_LEN)
#define PTABLE_LOGO_END                 (PTABLE_LOGO_START + PRODUCT_CFG_FLASH_LOGO_LEN)

/* m3image */
#define PTABLE_M3IMAGE_START            PTABLE_LOGO_END
#define PTABLE_M3IMAGE_LEN              (PRODUCT_CFG_FLASH_M3IMAGE_LEN)
#define PTABLE_M3IMAGE_END              (PTABLE_M3IMAGE_START + PTABLE_M3IMAGE_LEN)

/* Dsp */
#define PTABLE_DSP_START                PTABLE_M3IMAGE_END
#define PTABLE_DSP_LEN                  (PRODUCT_CFG_FLASH_DSP_LEN)
#define PTABLE_DSP_END                  (PTABLE_DSP_START + PTABLE_DSP_LEN)

/* misc */
#define PTABLE_MISC_START               PTABLE_DSP_END
#define PTABLE_MISC_LEN                 (PRODUCT_CFG_FLASH_MISC_LEN)
#define PTABLE_MISC_END                 (PTABLE_MISC_START + PTABLE_MISC_LEN)

/* VxWorks */
#define PTABLE_CCORE_START              PTABLE_MISC_END
#define PTABLE_CCORE_LEN                (PRODUCT_CFG_FLASH_CCORE_LEN)
#define PTABLE_CCORE_END                (PTABLE_CCORE_START + PTABLE_CCORE_LEN)

/* Reserve1 */
#define PTABLE_RESERVE1_START           PTABLE_CCORE_END
#define PTABLE_RESERVE1_LEN             (PRODUCT_CFG_FLASH_RESERVE1_LEN)
#define PTABLE_RESERVE1_END             (PTABLE_RESERVE1_START + PTABLE_RESERVE1_LEN)

/* Reserve2 */
#define PTABLE_RESERVE2_START           PTABLE_RESERVE1_END
#define PTABLE_RESERVE2_LEN             (PRODUCT_CFG_FLASH_RESERVE2_LEN)
#define PTABLE_RESERVE2_END             (PTABLE_RESERVE2_START + PRODUCT_CFG_FLASH_RESERVE2_LEN)

/* Reserve3 */
#define PTABLE_RESERVE3_START           PTABLE_RESERVE2_END
#define PTABLE_RESERVE3_LEN             (PRODUCT_CFG_FLASH_RESERVE3_LEN)
#define PTABLE_RESERVE3_END             (PTABLE_RESERVE3_START + PRODUCT_CFG_FLASH_RESERVE3_LEN)

/* OM */
#define PTABLE_OM_START                 PTABLE_RESERVE3_END
#define PTABLE_OM_LEN                   (PRODUCT_CFG_FLASH_OM_LEN)
#define PTABLE_OM_END                   (PTABLE_OM_START + PTABLE_OM_LEN)

/* YAFFS APP */
#define PTABLE_YAFFS_APP_START          PTABLE_OM_END
#define PTABLE_YAFFS_APP_LEN            (PRODUCT_CFG_FLASH_YAFFS_APP_LEN)
#define PTABLE_YAFFS_APP_END            (PTABLE_YAFFS_APP_START+PTABLE_YAFFS_APP_LEN)

/* YAFFS WEBUI */
#define PTABLE_YAFFS_WEBUI_START        PTABLE_YAFFS_APP_END
#define PTABLE_YAFFS_WEBUI_LEN          (PRODUCT_CFG_FLASH_YAFFS_WEBUI_LEN)
#define PTABLE_YAFFS_WEBUI_END          (PTABLE_YAFFS_WEBUI_START+PTABLE_YAFFS_WEBUI_LEN)

/* system */
#define PTABLE_YAFFS_SYSIMG_START       PTABLE_YAFFS_WEBUI_END
#define PTABLE_YAFFS_SYSIMG_LEN         (PRODUCT_CFG_FLASH_SYSIMG_LEN)
#define PTABLE_YAFFS_SYSIMG_END         (PTABLE_YAFFS_SYSIMG_START + PTABLE_YAFFS_SYSIMG_LEN)

/* cache */
#define PTABLE_CACHE_START               PTABLE_YAFFS_SYSIMG_END
#define PTABLE_CACHE_LEN                 (PRODUCT_CFG_FLASH_CACHE_LEN)
#define PTABLE_CACHE_END                 (PTABLE_CACHE_START + PTABLE_CACHE_LEN)

/* Recovery-A */
#define PTABLE_RECOVERY_A_START         PTABLE_CACHE_END
#define PTABLE_RECOVERY_A_LEN           (PRODUCT_CFG_FLASH_RECOVERY_LEN)
#define PTABLE_RECOVERY_A_END           (PTABLE_RECOVERY_A_START + PTABLE_RECOVERY_A_LEN)

/* Recovery-B */
#define PTABLE_RECOVERY_B_START         PTABLE_RECOVERY_A_END
#define PTABLE_RECOVERY_B_LEN           (PRODUCT_CFG_FLASH_RECOVERY_LEN)
#define PTABLE_RECOVERY_B_END           (PTABLE_RECOVERY_B_START + PTABLE_RECOVERY_B_LEN)

/* ISO  */
#define PTABLE_ISO_START                (PTABLE_RECOVERY_B_END)
#define PTABLE_ISO_LEN                  (PRODUCT_CFG_FLASH_ISO_LEN)
#define PTABLE_ISO_END                  (PTABLE_ISO_START + PTABLE_ISO_LEN)

/* partition name define, must be less than 16 characters */
#define PTABLE_M3BOOT_NM    "m3boot"
#define PTABLE_FASTBOOT_NM  "fastboot"
#define PTABLE_NVBACK_NM    "nvbacklte"
#define PTABLE_NVIMG_NM     "nvimg"
#define PTABLE_NVDLOAD_NM   "nvdload"
#define PTABLE_NVDEFAULT_NM "nvdefault"
#define PTABLE_OEMINFO_NM   "oeminfo"
#define PTABLE_USERDATA_NM  "userdata"
#define PTABLE_ONLINE_NM    "online"
#define PTABLE_KERNEL_NM    "kernel"
#define PTABLE_KERNELBK_NM  "kernelbk"
#define PTABLE_LOGO_NM      "logo"
#define PTABLE_M3IMG_NM     "m3image"
#define PTABLE_DSP_NM       "dsp"
#define PTABLE_MISC_NM      "misc"
#define PTABLE_VXWORKS_NM   "vxworks"
#define PTABLE_RESERVE1_NM  "reserve1"
#define PTABLE_RESERVE2_NM  "reserve2"
#define PTABLE_RESERVE3_NM  "reserve3"
#define PTABLE_OM_NM        "om"
#define PTABLE_APP_NM       "app"
#define PTABLE_WEBUI_NM     "webui"
#define PTABLE_SYSTEM_NM    "system"
#define PTABLE_CDROMISO_NM  "cdromiso"
#define PTABLE_CACHE_NM     "cache"
#define PTABLE_RECOVERYA_NM "recovery-a"
#define PTABLE_RECOVERYB_NM "recovery-b"
#ifdef __cplusplus
}
#endif

#if (FEATURE_ON == MBB_COMMON)
/*nand mtd initialization will register partition number*/
#define MAX_PARTITIONS_NUM      32
#endif
#endif
