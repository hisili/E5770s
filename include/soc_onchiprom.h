

#ifndef __SOC_ONCHIP_H__
#define __SOC_ONCHIP_H__

#include "soc_memmap.h"

#define FEATURE_RSA_LOCAL   // ��ʾʹ�ñ��ص�RSA�㷨������ԭ���ĺ�SOC_ONCHIPROM_V7R2
/*--------------------------------------------------------------*
 * �궨��                                                    *
 *--------------------------------------------------------------*/

#define M3_TCM_ADDR                    (0x10000000)	 /* TCM��ʼ��ַ */
#define M3_TCM_SIZE                    (64*1024)     /* 64K */

#define SRAM_ADDR                      (0x4FE00000)     /* AXI Memory��ʼ��ַ */
#define SRAM_SIZE                      (128*1024)       /* AXI Memory��С */

/* ��������������TCM����,BootLoader��������Ҫ������ */
#define M3_TCM_SHARE_DATA_SIZE sizeof(tOcrShareData)
#define M3_TCM_SHARE_DATA_ADDR (SRAM_ADDR + SRAM_SIZE - M3_TCM_SHARE_DATA_SIZE)

/* OnChipRom���й���־���Ծٱ�־����tOcrShareData�ṹ���� */
#define OCR_INITED_FLAG_ADDR    (SRAM_ADDR + SRAM_SIZE - 4)
#define OCR_AUTO_ENUM_FLAG_ADDR (SRAM_ADDR + SRAM_SIZE - 8)
#define OCR_INITED_FLAG_VALUE   (0x23456789)
#define OCR_UNINITED_FLAG_VALUE (0xA55A6789)


#define AUTO_ENUM_FLAG_VALUE    0x82822828

/* ֻ��OEM CA�в���OEM ID��HWID,��CA���� */
#define KEY_OEMID_INDEX        sizeof(KEY_STRUCT)
#define KEY_HWID_INDEX         (KEY_OEMID_INDEX+0x04)

#define BL_LEN_INDEX            (144 * 4)    /* bootload.bin�ļ�����(Byte)������bootload.bin�ļ��е�ƫ���ֽ��� */
#define ROOT_CA_INDEX           (BL_LEN_INDEX + 4)   /* ��CA��Image��λ�� */

#define ROOT_CA_LEN            260      /*CA֤��ĳ��� 260 Byte*/
#define OEM_CA_LEN             268      /*CA֤��ĳ��� 268 Byte*/
#define IDIO_LEN               128      /*ǩ���ĳ��� 128 Byte*/

#define MAX_N_LENGTH    32

#define SHA256_HASH_SIZE  8       /*HASHǩ��ռ��word��*/

#define MD5_HASH_SIZE   4       /* MD5ժҪ��ռ��word�� */

#define NAND_ARGS_FULL_AVAIL	0x3a
#define NAND_ARGS_PART_AVAIL	0x45
#define NANDC_USE_ONCHIPROM_PARAM
#define NANDC_OOBLENGTH_8BITECCTYPE
#ifndef __ASSEMBLY__
/*--------------------------------------------------------------*
 * ���ݽṹ                                                     *
 *--------------------------------------------------------------*/

/* ��Կ��ʽ */
typedef struct
{
    unsigned short eLen;    /* E������64bitsΪ��λ��ȡֵ��ΧΪ0~15��0��ʾ16 */
    unsigned short nLen;    /* N������32bitsΪ��λ��ȡֵ��ΧΪ0~31��0��ʾ32 */
    unsigned int   e[MAX_N_LENGTH];       /* ��e(��Կ) */
    unsigned int   n[MAX_N_LENGTH];       /* ģ�� */
}KEY_STRUCT;

/* nand spec info��ÿ��������ȡֵ������ʵ��ֵ����page_size��ȡ2048��4096�ȣ�����b01\b11�� */
struct nand_spec_real
{
	unsigned long page_size;
	unsigned long page_num_per_block;
	unsigned long addr_cycle;
	unsigned long ecc_type;
	unsigned long oob_size;
	unsigned long chip_size;	/* ��MBΪ��λ */
};

/* onchiprom���nand spec info���浽SRAM��һ��32bit��buffer�У�������ÿ���ֶεĺ��� */
struct nand_spec_sram
{
	/* pagesize/ecctype/addrnum/pagenumperblock �⼸��������Ĵ���������ֵһ�� */
    unsigned int    page_size          : 4;  /* [0~3]   */
    unsigned int    ecc_type           : 4;  /* [4~7]   */
    unsigned int    addr_num           : 4;  /* [8~11]  */
    unsigned int    page_num_per_block : 4;  /* [12~15] */

	/* sparesize/chipsize�������������ܻ�ȡ���� */
	unsigned int    spare_size		   : 5;  /* [16~20] */
	unsigned int    chip_size		   : 4;	 /* [21~24] */	

	/* flag */
    unsigned int    flag           	   : 7;  /* [25~31] NAND_ARGS_FULL_AVAIL - ��ȫ��������NAND_ARGS_FULL_AVAIL - ��4��������else - bufferֵ��Ч */
};

/* ǩ��У�麯��ָ�� */
typedef int (*idioIdentifyPtr)(unsigned int dataAddr, unsigned int dataLen, KEY_STRUCT *pKey, unsigned int* pIdio);

/* ����Hashֵ����ָ�� */
typedef int (*SHA256HashPtr)(unsigned int dataAddr, unsigned int dataLen, unsigned int* hash);

/* ����RSA����ָ�� */
typedef int (*RSAPtr)(KEY_STRUCT *pKey, unsigned int* pIndata, unsigned int* pOutdata);

/* ��ȡnand flash���ĺ���ָ�룬������������ */
typedef int (*bsp_nand_get_spec_and_save_ptr)(volatile struct nand_spec_sram *spec_sram);

/* �������ݽṹ��,����AXI����,�������¼�Ԫ��(�������ǰ��) */
typedef struct tagOcrShareData
{
	struct nand_spec_sram nandspec;
	bsp_nand_get_spec_and_save_ptr bsp_nand_get_spec_and_save;	/* ������ָ�� */

    int errNo;

    /* ������ָ�� */
    SHA256HashPtr   SHA256Hash;
    RSAPtr          RSA;
    idioIdentifyPtr idioIdentify;

    /* �������ݶ� */
    int    bSecEn;
    int    bRootCaInited;
    KEY_STRUCT *pRootKey;
    unsigned int  ulEnumFlag;
    unsigned int  ulOcrInitedFlag;
}tOcrShareData;

/* ��������������SRAM����,BootLoader��������Ҫ������ */
#define M3_SRAM_SHARE_DATA_SIZE sizeof(tOcrShareData)
#define M3_SRAM_SHARE_DATA_ADDR (SRAM_ADDR + SRAM_SIZE - M3_SRAM_SHARE_DATA_SIZE)

#endif /* __ASSEMBLY__ */

#endif

