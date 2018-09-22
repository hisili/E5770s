
/******************************************************************************
*    Copyright (c) 2009-2011 by  Hisilicon Tech. Co., Ltd.
*    All rights reserved.
* ***
*
******************************************************************************/
#ifndef _NANDC_CTRL_H_
#define _NANDC_CTRL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <osl_sem.h>
#include "nandc_cfg.h"

struct nandc_bit_reg
{
    u32 bits_func ;
    u32 reg_offset ;  /* offset relative to nand controller registers' base address.*/
    struct nandc_bitset*  bitset;
};


/*
*  ���ﶨ����������еļĴ�����������ϼ�����Щ��������������������ȡ��ִ�У�
* �ϼ��е�ÿ����λ����һ���Ĵ�����bitλ�������������еľ���������������ʼ��֮ǰ�ǲ��հ׵ģ�
* �ڳ�ʼ�������л���һϵ�в�����������ͨ���������Ϳ��ƶ���������ԣ�������ı�Ҫ��Ŀ
* ������䣬�����һ�ṹ���ݵĲ��컯���á�
*
*/
struct nandc_bit_cluster
{
    struct nandc_bit_reg cmd;
    struct nandc_bit_reg cmd2;
    struct nandc_bit_reg cmd3;              /* read status command */

    struct nandc_bit_reg bus_width;
    struct nandc_bit_reg addr_high;
    struct nandc_bit_reg addr_low;

    struct nandc_bit_reg addr_cycle;
    struct nandc_bit_reg chip_select;
    struct nandc_bit_reg operate;           /*nandc3_op_read_id*/

    struct nandc_bit_reg op_stauts;         /*nandc_status_op_done*/
    struct nandc_bit_reg int_stauts;        /*nandc_status_int_done*/
    struct nandc_bit_reg data_num;          /*data write to one page ,size in byte*/

    struct nandc_bit_reg ecc_type;          /*nandc3_ecc_none, nandc3_ecc_4smb*/
    struct nandc_bit_reg ecc_select;        /*nandc4_ecc_oob , nandc4_ecc_all*/
#ifdef NANDC_USE_V400
    struct nandc_bit_reg int_enable;
#endif
    struct nandc_bit_reg op_mode;           /*nandc_op_normal or nandc_op_boot*/
    struct nandc_bit_reg page_size;
    struct nandc_bit_reg int_clr;

    struct nandc_bit_reg segment;           /*nandc4_segment_first for nandc4_segment_last*/
    struct nandc_bit_reg ecc_result;
    struct nandc_bit_reg nf_status;         /*nand chip 8 bit status register*/

	struct nandc_bit_reg async_interface_type;
	struct nandc_bit_reg randomizer;
	struct nandc_bit_reg read_id_en;

	struct nandc_bit_reg rw_reg_en;
	struct nandc_bit_reg ecc_class;
	struct nandc_bit_reg randomizer_en;

	struct nandc_bit_reg cs0_done;
	struct nandc_bit_reg ahb_op_err;
	struct nandc_bit_reg wr_lock_err;

	struct nandc_bit_reg dma_done;
	struct nandc_bit_reg dma_err;
	struct nandc_bit_reg dma_start;

	struct nandc_bit_reg dma_rw_enable;
	struct nandc_bit_reg burst_enable;
	struct nandc_bit_reg dma_addr_num;

	struct nandc_bit_reg dma_cs;
	struct nandc_bit_reg dma_wr;
	struct nandc_bit_reg dma_rd_oob;

	struct nandc_bit_reg base_addr_data;
	struct nandc_bit_reg base_addr_oob;
	struct nandc_bit_reg dma_len;

	struct nandc_bit_reg errnum0buf0;
	struct nandc_bit_reg rb_status;

	struct nandc_bit_reg base_addr_d1;
	struct nandc_bit_reg base_addr_d2;
	struct nandc_bit_reg base_addr_d3;
	struct nandc_bit_reg oob_len_sel;

	struct nandc_bit_reg int_op_done;
	struct nandc_bit_reg int_cs_done;
	struct nandc_bit_reg int_err_invalid;
	struct nandc_bit_reg int_err_valid;
	struct nandc_bit_reg int_ahb_op;
	struct nandc_bit_reg int_wr_lock;
	struct nandc_bit_reg int_dma_done;
	struct nandc_bit_reg int_dma_err;

	struct nandc_bit_reg dma_ctrl;

    struct nandc_bit_reg endtable;          /*don't add after this*/

};

struct nandc_spec
{
    char *name;          /* get from nand_flash_ids[] through nandc_native_get_spec*/
    u32 pagesize;        /* get from id[] data through nandc_native_get_spec*/
    u32 pagesum;         /* page total number of the nand flash chip.*/
    u32 offinpage;       /* pagesize - 1 */
    u32 pagealign;       /* ~(pagesize - 1) */
    u32 pageshift;       /* pagesize >> pageshift = 1*/
    u32 pagemask;        /* address & pagemask = page_no.*/
    u32 sparesize;       /* get from id[] data through nandc_native_get_spec*/
    u32 blocksize;       /* get from id[] data through nandc_native_get_spec*/
    u32 blockpages;      /* page number in one block*/
    u32 blockmask;       /* address & blockmask = block_no.*/
    u32 offinblock;      /* blocksize - 1 */
    u32 blockalign;      /* ~(blocksize - 1) */
    u32 blockshift;      /* blocksize >> blockshift = 1*/
    FSZ chipsize;        /* get from nand_flash_ids[] through nandc_native_get_spec*/
    u32 chipshift;       /* chipsize >> chipshift = 1*/
    u32 buswidth;        /* get from id[] data through nandc_native_get_spec*/
    u32 addrcycle;       /* one cycle send 8 bits address,so 4 cycles send 32 bits address
                            and 5 cycles send 40 bits address
                            addr_physics[0],addr_physics[1] :32 bits.
                            nandc_addrcycle_5: 5  for capacity >= 256 M nand flash chip.
                            addr_physics[0] :   page  address  | offset in page
                                             -------------------------------------
                                             |00000000|00000000|00000000|00000000|
                                             -------------------------------------
                            addr_physics[1]:                            |page address
                                             -------------------------------------
                                             |00000000|00000000|00000000|00000000|
                                             -------------------------------------

                            nandc_addrcycle_4: 4 for capacity < 256 M nand flash chip.
                            addr_physics[0]:     page address  | offset in page
                                             -------------------------------------
                                             |00000000|00000000|00000000|00000000|
                                             -------------------------------------
                         */
    u32 options;
};


struct nandc_define
{
    struct mtd_partition*  partition;
    struct usr_feature*    feature;
    u32 nbparts;
};

struct nandc_nand
{
    struct nandc_spec    spec;
    struct nandc_pagemap *datamap;
    u32 ecctype;            /*not used yet, ecc defined in*/
    u32 pageset;
    u32 busset;
    u32 chipnum;
};

struct nandc_distrib
{
    u32 addr;
    u32 lens;
};

struct nandc_pagemap    /*data map in one page*/
{
    struct nandc_distrib  data;
    struct nandc_distrib  oob;
};

struct nandc_dmap    /*data map in one page*/
{
    u32    bad2k;     /* bad block flag location for 2k page*/
    struct nandc_pagemap pmap2k[1];
    u32    bad4k;     /* bad block flag location for 4k page*/
    struct nandc_pagemap pmap4k[2];
    u32    bad8k;     /* bad block flag location for 8k page*/
    struct nandc_pagemap pmap8k[4];
};


/*
*˵�����˻�����������������һ��˽�л����ԣ���ͬ��������ͬecc��ʽ��buffer�������ж��в�ͬ
*      ��ͬʱҲ����������֮��Ĺ�����.
*/
struct nandc_dmap_lookup
{
    struct nandc_dmap   *datamap ;      /*ָ������ecctype��Ӧ��buffer���ݷ��������б�*/
    u32 ecctype;                        /*���������б������Ӧ��ecctype*/
};

struct nandc_bit_cmd
{
    u8  op_read_id;
    u8  op_read_start;
    u8  op_read_continue;
    u8  op_read_end;

    u8  op_write_start;
    u8  op_write_continue;
    u8  op_write_end;
    u8  op_erase;

    u8  op_segment_start;
    u8  op_segment_end;
    u8  op_reset;
    u8  ecc_err_none;

    u8  ecc_err_valid;
    u8  ecc_err_invalid;
    u16 intmask_all;

    u16 intdis_all;
    u16 inten_all;
    u16 intclr_all;

    u16 ecc_oob;
    u16 ecc_all;

	u16 dma_read;
	u16 dma_read_oob_only;
	u16 dma_write;

    u16 ecc_none;
    u16 reserved1;
};

struct nandc_reg_list
{
    u32 address;
    u32 value;
    struct nandc_reg_list *p_next;
};

struct nandc_config_snapshot
{
    struct nandc_reg_list* listreg;
    u32 totalsize;
    u32 onesize;
    u32 eccselect;
};

struct nandc_snapshot
{
    struct nandc_config_snapshot  *config_ecc;
    struct nandc_config_snapshot  *config_raw;
    struct nandc_config_snapshot  *config_oob;
};

/*
* ˵��: ����ģ�������ʵ�����������������е�ǰ���ƶ�����Ϣ��Ϊ�˿��ƶ���������Ŀ�������Ϣ��
*
*/
struct nandc_host
{
    struct nandc_nand               *nandchip;              /* pointer to current select nandc_nand */
    struct nandc_define             *usrdefine;             /* �û������壬�������*/
    struct mtd_partition            *curpart;               /* ��ǰ����ָ�������*/
    struct nandc_bit_cluster        *normal;                /* pointer to nandc_bit_cluster */
    struct nand_buffers             *buffers;               /* ������ʱbuffer��С������page read*/
    struct nandc_ctrl_func          *ctrlfunc;              /* ������˽�г�ʼ������ָ��*/
    struct nandc_ecc_info           *eccinfo;               /* ��������������*/
    struct nandc_dmap_lookup        *dmaplookup;            /* the data map(page + oob)of the controller buffer, nandc_dmap*/
    struct nandc_bit_cmd            bitcmd;                 /* �������Ĵ���λ�������ñ�*/
    struct nandc_snapshot           read_snapshot;          /* ��ϵ�в����Ĵ�������*/
    struct nandc_snapshot           write_snapshot;         /* дϵ�в����Ĵ�������*/
    u32 badoffset;

    u32 command;
    u32 options;        /* ��������nandʹ��DMA/normal��ecc0/��ecc0 */
	u32 bbt_options;    /* �����������ʹ��page0��page1������last page */
    u32 latched;
    
    u32 addr_cycle;
    u32 addr_physics[2];
    FSZ addr_real;
    FSZ addr_logic;
    u32 length;                         /*for no ecc mode*/
    u32 chipselect;
    u32 chipmax;
    u32 probwidth;
    
    u32 addr_to_sel_oob_len;            /* 8bit ecc ģʽ�£�oob length��Ҫ����Ϊ32Byte��
                                            nand��ַ���ڴ�ֵʱ��oob_len_sel��Ҫ���ó�0�������������Ҫ���ó�1 */
    u8 flash_id[NANDC_READID_SIZE];	
	u8* nand_4bitecc_table;
    
    u8* databuf;                  /*if use DMA tramsmit ,this buffer must be coherent*/
    u8* oobbuf;
    void __iomem * regbase;       /* */
    void __iomem * bufbase;       /* */
    u32 regsize;
    u32 bufsize;
    /*��ʹ��ECC��ģʽ��ʱ�������������ECC�Ĳ��ɾ���ʱҲҪ�����ݶ������ı�־*/
    u32 force_readdata;
    /*�����Flash֧��ONFI�Ĺ��ܣ���ô��ONFI���Ĺ����а�ECCTYPE������ں���ָ�*/
    u32 ecctype_onfi;

#ifdef WIN32
    struct reg_debuger *debuger;
#endif

#ifdef __KERNEL__
    struct nand_chip * chip;
    struct mtd_info *   mtd;
    struct clk  *clk; 
    
#ifdef CONFIG_PM  
    u32 *sleep_buffer;  
#endif  

#ifdef FEATURE_NANDC_DMA_USE_INTERRUPT  
    osl_sem_id sem;
	u32 irq_id;
#endif  

    u32 column;
    u32 offset;
    dma_addr_t  dma_addr;
    dma_addr_t  dma_oob_addr;
    /*if nand page size large than NANDC_BUFSIZE_BASIC ,use temp buffer here*/
    u32 IsUseBuffer;
#endif
};

struct nandc_clist
{
    struct nandc_clist  *p_next;
    struct nandc_nand   *chip;
};


struct nandc_bitset
{
    u32 offset;       /* offset in one nand controller register.*/
    u32 length;       /* bit acount from offset.*/
};

 struct nandc_reg_cont
{
    u32 func;                        /* nandc_bits_func */
    struct nandc_bitset   set;       /* nandc_bit_set */
    u16 desc[nandc_reg_desc_max];
};

/*
* ˵�����˽ṹ��������������һ��32λ�Ĵ�����ض��壬�����Ĵ���ƫ�ƣ��Ĵ���Ĭ��ֵ��
*        ��λƫ�ƺ�λ���ȷ����Ĺ�����Ϣ����ÿ���������Ŀ�������Ϣ��
*/
struct nandc_reg_desc
{
    u32 addr_offset;         /* offset relative to nand controller register's base address.*/
    u32 defaultval;
    struct nandc_reg_cont*  content;
};


/*
* ˵��������Կ������������������������Ĵ������ܣ������������ڲ�buffer��Ϣ�����֧��оƬ���ȡ�
*/
struct nandc_ctrl_desc
{
    struct nandc_reg_desc* regdesc;     /* register description */
    char* ctrlname;                     /* NANDC2_NAME,NANDC3_NAME,NANDC4_NAME */
    u32 regbase;                        /* nand controller register base address.*/
    u32 regsize;                        /* nand controller registers' size in bytes(acount * sizeof(int)).*/
    u32 buffbase;                       /* nand controller buffer's base address */
    u32 buffsize;                       /* nand controller buffer's size in bytes.*/
    u32 maxchip;                        /* acount of nand flash chip.*/
};


/*
* ˵��������ǶԿ�����˽�л���ʼ�����̵�����������������˽�еĳ�ʼ�����̣���GPIO������ʱ�����õȷ������
*/
struct nandc_ctrl_func
{
    u32 (*init_cmd)(struct nandc_bit_cmd  *  ctrlcmd,  struct nandc_host *host);
};


/*
* ˵��������ṹ�����Ƕ�һ��������������������һ���ṹ���ݶ���������һ�������������˽�л�����
*/
struct nandc_init_info        /* nandc2_init_info, nandc3_init_info, nandc4_init_info, nandc6_init_info*/
{
    struct nandc_ctrl_desc      *ctrlspec;          /*������˽������������*/
    struct nandc_ctrl_func      *ctrlfunc;          /*������˽�й��ܺ�����*/
    struct nandc_ecc_info       *eccinfo;           /*����������������ñ�*/
    u8                          *bitstbl;           /*�����������������ñ�*/
    struct nandc_dmap_lookup    *dmaplookup;        /*������˽���ڲ�buffer�ֲ���*/
    struct usr_feature          *usrdefine;         /*��չ����ӿ�*/
};

struct data_swap
{
    u32 srcoffset;
    u32 dstoffset;
    u32 length;
};

struct usr_feature
{
    struct data_swap exchange[NANDC_MAX_PAGE_SWAP];
    void (*cb) (struct nandc_host * host,  struct usr_feature *feature);
};

/*
* ˵��������ǿ������Ϳ��ƶ���Ĺ�������壬���������Ժ󣬳�ʼ���������������������ǰ
*       �������Ϳ��ƶ�������Ҫ�Ŀ�����buffer���ݷֲ�������
*/
struct nandc_ecc_info
{
    u32 pagesize;                                   /*nand����page��С*/
    u32 sparesize;                                  /*nand������spare����С*/
    u32 ecctype;                                    /*�������������Ӧ�ı����������ecc�Ĵ�������*/
    struct nand_ecclayout *layout;                  /*�������������Ӧ�ı�������buffer���ݷֲ�����*/
};

#ifdef __cplusplus
}
#endif

#endif  /*_NANDC_CTRL_H_*/
