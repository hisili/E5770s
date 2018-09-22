
/******************************************************************************
*    Copyright (c) 2013-2016 by  Hisilicon Tech. Co., Ltd.
*
*    All rights reserved.
*
******************************************************************************/
#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __FASTBOOT__
#include "nandc_balong.h"
#include "nandc_cfg.h"
#include "nandc_mco.h"

typedef unsigned char u8 ;
typedef unsigned int  u32;

extern u32 nandc_native_reset_chip(struct nandc_host* host , u32 chipselect);
extern u32 nandc_native_get_id(struct nandc_host* host, u8* id_data, u32 length);
extern void cprintf(const char *fmt, ...);

#define PRINT_DATAS(buffer, x, i); \
    cprintf("\n"); \
    for(i = 1; i <= x; i++) \
    { \
       cprintf("%x ", *buffer); \
       buffer++; \
       if(i % 6 == 0) \
       {  \
            cprintf("\n"); \
       } \
    } \
    cprintf("\n");


#else  /* __KERNEL__ */
#include <linux/mtd/mtd.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <drv_nand.h>
#include <bsp_hardtimer.h>
#include <bsp_nandc.h>

#endif /* #ifdef __FASTBOOT__ */

#include "ptable_com.h"
#include "nandc_cfg.h"

#define PAGESPERBLOCK   64

/*************************************** BEGIN: test nandc ********************************************/
#ifdef __FASTBOOT__

/******************************************************************************
* �� �� ��: nandc_test_case_001
* ��������: ����fastboot��nandc����read flash id����
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ��
*******************************************************************************/
void nandc_test_case_001(void)
{
    u8 id_data[NANDC_READID_SIZE];
    u32 ret, i;
    struct nandc_host* host = NANDC_NULL;

    /* nand init clear */
    nand_init_clear();

    /*use "nandc_init_seed" to initialize host*/
    ret = nandc_nand_create_host(&host);
    if(NANDC_OK != ret)
    {
        goto fail;
    }

    /* reset chip */
    nandc_native_reset_chip(host, host->chipselect);

    /* get id */
    ret = nandc_native_get_id(host, id_data, sizeof(id_data));
    if(NANDC_OK != ret)
    {
        goto fail;
    }

    /* nandc command init */
    if(host->ctrlfunc->init_cmd)
    {
        (void)host->ctrlfunc->init_cmd(&host->bitcmd,  host);
    }

    /* output id */
    cprintf("Nand flash id: ");
    for(i = 0; i < NANDC_READID_SIZE; i++)
    {
        cprintf("0x%2x ",id_data[i]);
    }
    cprintf("\n");

    /* successful */
    cprintf("SUCCESS: nandc_test_case_001\n");
    return;

fail:
    if(host)
        hifree((void*)host);
	cprintf("FAIL: nandc_test_case_001, ret = %d\n", ret);
	return;
}

/******************************************************************************
* �� �� ��: nandc_test_case_002
* ��������: ����fastboot��nandc������������
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: 1�������������nand��ʼ����read��write�ͻ����ѯ����ǹ���
*           2����������:
*               1 - find a good block from block 8, beyond fastboot partition
*               2 - get two buffers named "buffer" and "buffer_value".
*               3 - write "buffer" which is initialied with 0x00000000 to the block
*               4 - erase the block
*               5 - read the data back from the block to "buffer", which should be 0xFFFFFFFF
*               6 - compare "buffer" with "buffer_value", which is initialied with 0xFFFFFFFF
*******************************************************************************/
void nandc_test_case_002(void)
{
	u32 block_id;
	u32 ret = NANDC_ERROR;
	u32 flash_addr;
    u32 bad_flag;
	u32* buffer = NULL;
    u32* buffer_value = NULL;
	struct nand_spec * spec = NULL;

	/* nand init */
    ret = nand_init();
    if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* get flash spec */
	spec = (struct nand_spec *)himalloc(sizeof(struct nand_spec));
    if(!spec)
    {
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	ret = nand_get_spec(spec);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    /* find a good block */
    block_id = 8;
    while(1)
    {
        ret = nand_isbad(block_id, &bad_flag);
    	if(ret)
    	{
	        cprintf(" Line %d\n", (int)__LINE__);
    		goto fail;
    	}
        /* good block, break */
    	if(bad_flag != NANDC_BAD_BLOCK)
    	{
    		break;
    	}
        block_id++;
    }
    cprintf("good block found, block id = %d\n", block_id);

	/* get buffer */
	buffer = (u32*)himalloc(spec->blocksize);
    buffer_value = (u32*)himalloc(spec->blocksize);
	if((!buffer) || (!buffer_value))
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* write */
	flash_addr = block_id * spec->blocksize;
	memset(buffer, 0, spec->blocksize);
	ret = nand_write(flash_addr, (u32)buffer, spec->blocksize, 0);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* erase */
	ret = nand_erase(block_id);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* read */
	ret = nand_read(flash_addr, (u32)buffer, spec->blocksize, 0);
	if(ret)
	{
		goto fail;
	}

	/* compare data with "0xFF" */
    memset(buffer_value, 0xFF, spec->blocksize);
	ret = memcmp(buffer, buffer_value, spec->blocksize);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    hifree((void*)buffer);
    hifree((void*)buffer_value);
    hifree((void*)spec);
    cprintf("SUCCESS: nandc_test_case_002\n\n");
    return;

fail:
	cprintf("FAIL:nandc_test_case_002, ret = %d\n\n", ret);
	if(buffer)
		hifree((void*)buffer);
    if(buffer_value)
		hifree((void*)buffer_value);
	if(spec)
		hifree((void*)spec);

	return ;

}

/******************************************************************************
* �� �� ��: nandc_test_case_003
* ��������: ����fastboot��nandc����bus��ʽ��ecc��дdata
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: 1�������ڳ�ʼ���������ѯ�ͱ�ǹ���
*           2��step as follow
*               1 - find a good block form block 8;
*               2 - write "buffer" which is initialized with 0x00000000 to flash
*               3 - read back from flash to "readbuffer" which is initialized with 0xFFFFFFFF
*               4 - compare "buffer" and "readbuffer"
*******************************************************************************/
void nandc_test_case_003(void)
{
	u32 block_id;
	u32 ret = NANDC_ERROR;
	u32 flash_addr;
    u32 bad_flag;
	u32* buffer	= NULL;
	u32* readbuffer = NULL;
	u32 length;
	struct nand_spec *spec = NULL;

	/* nand isinit */
    ret = nand_init();
    if(ret)
    {
	    cprintf(" Line %d\n", (int)__LINE__);
        goto fail;
    }

	/* get flash spec */
	spec = (struct nand_spec *)himalloc(sizeof(struct nand_spec));
    if(!spec)
    {
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}
	ret = nand_get_spec(spec);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    /* find a good block */
    block_id = 8;
    while(1)
    {
        ret = nand_isbad(block_id, &bad_flag);
    	if(ret)
    	{
	        cprintf(" Line %d\n", (int)__LINE__);
    		goto fail;
    	}
        /* good block, break */
    	if(bad_flag != NANDC_BAD_BLOCK)
    	{
    		break;
    	}
        block_id++;
    }
    cprintf("good block found, block id = %d\n", block_id);

	/* erase  */
	ret = nand_erase(block_id);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* get buffer */
	length = spec->blocksize;
	buffer = (u32*)himalloc(length);
	if(!buffer)
	{
		goto fail;
	}

	/* get read buffer */
	readbuffer = (u32*)himalloc(length);
	if(!readbuffer)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* write */
	flash_addr = block_id * spec->blocksize;
	memset(buffer, 0, length);
	ret = nand_write(flash_addr, (u32)buffer, length, 0);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* read */
	memset(readbuffer, 0xff, length);
	ret = nand_read(flash_addr, (u32)readbuffer, length, 0);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* compare two buffer */
	ret = memcmp(buffer, readbuffer, length);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    /* erase */
	ret = nand_erase(block_id);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}


    hifree((void*)buffer);
    hifree((void*)spec);
    cprintf("SUCCESS: nandc_test_case_003\n\n");
	return;

fail:
	cprintf("FAIL:nandc_test_case_003, ret = %d\n\n", ret);

	if(spec)
		hifree((void*)spec);
	if(buffer)
		hifree((void*)buffer);
	if(readbuffer)
		hifree((void*)readbuffer);

	return;
}

/******************************************************************************
* �� �� ��: nandc_test_case_004
* ��������: ����fastboot��nandc����bus��ʽ��ecc��дdata+oob
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: 1�������ڳ�ʼ���������ѯ�ͱ�ǹ���
*           2��step as follow
*               1 - find a good block form block 8;
*               2 - write "buffer" which is initialized with 0x00000000 to flash
*               3 - read back from flash to "readbuffer" which is initialized with 0xFFFFFFFF
*               4 - compare "buffer" and "readbuffer"
*******************************************************************************/
void nandc_test_case_004(void)
{
	u32 block_id;
	u32 ret = NANDC_ERROR;
	u32 flash_addr;
    u32 bad_flag;
	u32* buffer	= NULL;
	u32* readbuffer = NULL;
	u32 length;
	struct nand_spec *spec = NULL;

	/* nand isinit */
    ret = nand_init();
    if(ret)
    {
	    cprintf(" Line %d\n", (int)__LINE__);
        goto fail;
    }

	/* get flash spec */
	spec = (struct nand_spec *)himalloc(sizeof(struct nand_spec));
    if(!spec)
    {
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}
	ret = nand_get_spec(spec);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    /* find a good block */
    block_id = 8;
    while(1)
    {
        ret = nand_isbad(block_id, &bad_flag);
    	if(ret)
    	{
	        cprintf(" Line %d\n", (int)__LINE__);
    		goto fail;
    	}
        /* good block, break */
    	if(bad_flag != NANDC_BAD_BLOCK)
    	{
    		break;
    	}
        block_id++;
    }
    cprintf("good block found, block id = %d\n", block_id);

	/* get buffer */
	length = (spec->pagesize + YAFFS_BYTES_PER_SPARE) * (spec->blocksize / spec->pagesize);
	buffer = (u32*)himalloc(length);
	readbuffer = (u32*)himalloc(length);
	if((!buffer) || (!readbuffer))
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* write */
	flash_addr = block_id * spec->blocksize;
	memset(buffer, 0, length);
	ret = nand_write_oob(flash_addr, (u32)buffer, length, YAFFS_BYTES_PER_SPARE, 0);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* read */
	memset(readbuffer, 0xFF, length);
	ret = nand_read_oob(flash_addr, (u32)readbuffer, length, YAFFS_BYTES_PER_SPARE, 0);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* compare two buffer */
	ret = memcmp(buffer, readbuffer, length);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    /* erase. because write 0 to the first page of a block equals mark it bad */
    ret = nand_erase(block_id);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    hifree((void*)buffer);
    hifree((void*)readbuffer);
    hifree((void*)spec);
    cprintf("SUCCESS: nandc_test_case_004\n\n");
	return ;

fail:
	cprintf("FAIL:nandc_test_case_004, ret = %d\n\n", ret);

	if(spec)
		hifree((void*)spec);
	if(buffer)
		hifree((void*)buffer);
	if(readbuffer)
		hifree((void*)readbuffer);
	return ;

}

/******************************************************************************
* �� �� ��: nandc_test_case_005
* ��������: ����fastboot��nandc����bus��ʽ����ecc��дdata
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: 1�������ڳ�ʼ���������ѯ�ͱ�ǹ���
*           2��step as follow
*               1 - find a good block form block 8;
*               2 - write "buffer" which is initialized with 0x00000000 to flash
*               3 - read back from flash to "readbuffer" which is initialized with 0xFFFFFFFF
*               4 - compare "buffer" and "readbuffer"
*******************************************************************************/
void nandc_test_case_005(void)
{
	u32 block_id;
	u32 ret = NANDC_ERROR;
    u32 bad_flag;
	u32* buffer	= NULL;
	u32* readbuffer = NULL;
	u32 length;
	struct nand_spec *spec = NULL;

	/* nand isinit */
	ret = nand_init();
    if(ret)
    {
	    cprintf(" Line %d\n", (int)__LINE__);
        goto fail;
    }

	/* get flash spec */
	spec = (struct nand_spec *)himalloc(sizeof(struct nand_spec));
    if(!spec)
    {
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}
	ret = nand_get_spec(spec);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    /* find a good block */
    block_id = 8;
    while(1)
    {
        ret = nand_isbad(block_id, &bad_flag);
    	if(ret)
    	{
	        cprintf(" Line %d\n", (int)__LINE__);
    		goto fail;
    	}
        /* good block, break */
    	if(bad_flag != NANDC_BAD_BLOCK)
    	{
    		break;
    	}
        block_id++;
    }
    cprintf("good block found, block id = %d\n", block_id);

	/* get buffer */
	length = (spec->pagesize + spec->sparesize);
	buffer = (u32*)himalloc(length);
    if(!buffer)
    {
        cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
    }

	readbuffer = (u32*)himalloc(length);
	if(!readbuffer)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    /* erase the block, it's needed, because nand_write_raw() doesn't contain "erase" operation */
    ret = nand_erase(block_id);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* write */
	memset(buffer, 0, length);
	ret = nand_write_raw(block_id * (spec->blocksize / spec->pagesize), 0, (u32)buffer, length, 0);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* read */
 	memset(readbuffer, 0xFF, length);
	ret = nand_read_raw(block_id * (spec->blocksize / spec->pagesize), 0, (u32)readbuffer, length, 0);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* compare two buffer */
	ret = memcmp(buffer, readbuffer, length);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    /* erase. because write 0 to the first page of a block equals mark it bad */
	ret = nand_erase(block_id);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    hifree((void*)buffer);
    hifree((void*)spec);
    cprintf("SUCCESS: nandc_test_case_005\n\n");
	return ;

fail:
	cprintf("FAIL:nandc_test_case_005, ret = %d\n\n", ret);

	if(spec)
		hifree((void*)spec);
	if(buffer)
		hifree((void*)buffer);
	if(readbuffer)
		hifree((void*)readbuffer);
	return ;
}

/******************************************************************************
* �� �� ��: nandc_test_case_006
* ��������: ����fastboot��nandc����bus��ʽ��ǻ��鹦��
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: 1������ı�ǺͲ�ѯ���ܲ��Ի�������������case_06��case_07һ��
*           2��step as follow
*               1 - find a good block form block 8;
*               2 - mark it bad
*               3 - check whether it bad. if bad, success; else, fail.
*******************************************************************************/
void nandc_test_case_006(void)
{
	u32 block_id;
	u32 ret;
	u32 bad_flag;

    /* nand isinit */
	ret = nand_init();
    if(ret)
    {
	    cprintf(" Line %d\n", (int)__LINE__);
        goto fail;
    }

    /* find a good block */
    block_id = 8;
    while(1)
    {
        ret = nand_isbad(block_id, &bad_flag);
    	if(ret)
    	{
	        cprintf(" Line %d\n", (int)__LINE__);
    		goto fail;
    	}
        /* good block, break */
    	if(bad_flag != NANDC_BAD_BLOCK)
    	{
    		break;
    	}
        block_id++;
    }
    cprintf("good block found, block id = %d\n", block_id);

    /* erase the block, it's needed, because nand_write_raw() doesn't contain "erase" operation */
    ret = nand_erase(block_id);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* mark bad */
	ret = nand_bad(block_id);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* test if bad again */
	ret = nand_isbad(block_id, &bad_flag);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* bad, success */
	if(bad_flag != NANDC_BAD_BLOCK)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    /* erase the block to make it good */
    ret = nand_erase(block_id);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    cprintf("SUCCESS: nandc_test_case_006\n\n");
	return ;
fail:
	cprintf("FAIL:nandc_test_case_006, ret = %d\n\n", ret);
	return ;
}

/******************************************************************************
* �� �� ��: nandc_test_case_007
* ��������: ����fastboot��nandc����bus��ʽ��ѯ���鹦��
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ��case��case_06һ���������ظ�ʵ��
*******************************************************************************/
void nandc_test_case_007(void)
{
    nandc_test_case_006();
    return;
}

/******************************************************************************
* �� �� ��: nandc_test_case_008
* ��������: ����fastboot��nandc����DMA��ʽ��ecc��дdata
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ��case��case_03һ���������ظ�ʵ��
*******************************************************************************/
void nandc_test_case_008(void)
{
    /* DMA ��ʽ����nand���Ʋ�ʵ�֣����ϲ㲻�ɼ� */
	nandc_test_case_003();
	return ;
}

/******************************************************************************
* �� �� ��: nandc_test_case_009
* ��������: ����fastboot��nandc����DMA��ʽ��ecc��дdata+oob
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ��case��case_04һ���������ظ�ʵ��
*******************************************************************************/
void nandc_test_case_009(void)
{
    /* DMA ��ʽ����nand���Ʋ�ʵ�֣����ϲ㲻�ɼ� */
	nandc_test_case_004();
	return ;

}

/******************************************************************************
* �� �� ��: nandc_test_case_010
* ��������: ����fastboot��nandc����DMA��ʽ��eccֻ��oob��
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ��
*******************************************************************************/
void nandc_test_case_010(void)
{
    /* ֻ��oobֻ���ڲ�ѯ����ʱ�õ�������ֻ��oob�������������û���ã�
     * ��ѯ�����ʱ��ʹ�õ��ǲ���ecc�Ľӿڣ����Ҫ�������������Ҫ�޸��������롣
     * �޸���ɺ������������Ӧ����case_06һ�� */
    /*nandc_test_case_006(); */
}

/******************************************************************************
* �� �� ��: nandc_test_case_011
* ��������: ����fastboot��nandc����DMA��ʽ����ecc��дdata
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ��
*******************************************************************************/
void nandc_test_case_011(void)
{
	/* ����ecc��ʱ�򣬲�����data��oob�����case��case_12һ�� */
	return ;
}

/******************************************************************************
* �� �� ��: nandc_test_case_012
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����fastboot��nandc����DMA��ʽ����ecc��дdata+oob
*******************************************************************************/
void nandc_test_case_012(void)
{
	u32 block_id;
	u32 ret = NANDC_OK;
    u32 bad_flag;
	u32* buffer	= NULL;
	u32* readbuffer = NULL;
	u32 length;
	struct nand_spec *spec = NULL;

	/* nand isinit */
	ret = nand_init();
    if(ret)
    {
        goto fail;
    }

	/* get flash spec */
	spec = (struct nand_spec *)himalloc(sizeof(struct nand_spec));
    if(!spec)
    {
		goto fail;
	}
	ret = nand_get_spec(spec);
	if(ret)
	{
		goto fail;
	}

    /* find a good block */
    block_id = 0x8;
    while(1)
    {
        ret = nand_isbad(block_id, &bad_flag);
    	if(ret)
    	{
	        cprintf(" Line %d\n", (int)__LINE__);
    		goto fail;
    	}
        /* good block, break */
    	if(bad_flag != NANDC_BAD_BLOCK)
    	{
    		break;
    	}
        block_id++;
    }
    cprintf("good block found, block id = %d\n", block_id);

	/* erase  */
	ret = nand_erase(block_id);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* get buffer */
	length = (spec->pagesize + spec->sparesize);
	buffer = (u32*)himalloc(length);
	if(!buffer)
	{
		goto fail;
	}

	/* get read buffer */
	readbuffer = (u32*)himalloc(length);
	if(!readbuffer)
	{
		goto fail;
	}

	/* write */
	memset(buffer, 0, length);
	ret = nand_write_raw(block_id * (spec->blocksize / spec->pagesize), 0, (u32)buffer, length, 0);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* read */
	memset(readbuffer, 0xFF, length);
	ret = nand_read_raw(block_id * (spec->blocksize / spec->pagesize), 0, (u32)readbuffer, length, 0);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

	/* compare two buffer */
	ret = memcmp(buffer, readbuffer, length);
	if(ret)
	{
		goto fail;
	}

    /* erase the block to mark it good */
    ret = nand_erase(block_id);
	if(ret)
	{
	    cprintf(" Line %d\n", (int)__LINE__);
		goto fail;
	}

    hifree((void*)buffer);
    hifree((void*)readbuffer);
    hifree((void*)spec);
    cprintf("SUCCESS: nandc_test_case_012\n\n");
	return ;

fail:
	cprintf("FAIL:nandc_test_case_012, ret = %d\n\n", ret);

	if(spec)
		hifree((void*)spec);
	if(buffer)
		hifree((void*)buffer);
	if(readbuffer)
		hifree((void*)readbuffer);
	return ;
}

/******************************************************************************
* �� �� ��: nandc_test_case_013
* ��������: ����fastboot��nandc����DMA��ʽ��ǻ��鹦��
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��:
*******************************************************************************/
void nandc_test_case_013(void)
{
	nandc_test_case_006();
	return ;
}

/******************************************************************************
* �� �� ��: nandc_test_case_014
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����fastboot��nandc����DMA��ʽ��ѯ���鹦��
*******************************************************************************/
void nandc_test_case_014(void)
{
	nandc_test_case_013();
    return;
}

/******************************************************************************
* �� �� ��: nandc_test_case_029
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����nandc ecc type = 1��ʱ��ľ�������. ecc type = 1ʱ��nandc�ڲ���
*           ת��Ϊecc type = 4������ʵ����ʹ�õ���4 bit ecc������������������
*           ��8bit / 1024 Bytesʱ��nandcӦ�ö��ܹ�����
*******************************************************************************/
void nandc_test_case_029(void)
{
    u32 block_id = 0x18, size = 0x800+0x40, nand_page_size = 0x800;
	u32 ret, i, j;
    u32 flash_addr = block_id * nand_page_size * 64;
    u32* src_buffer = NULL;
    u32* temp_buffer = NULL;
    u32* buffer = NULL;

    /* nand isinit */
	ret = nand_init();
    if(ret)
    {
        goto erro;
    }

    /* get buffer */
    src_buffer = (u32 *)himalloc(size);
    temp_buffer = (u32 *)himalloc(size);
    if((!src_buffer) || (!temp_buffer))
    {
	    cprintf("ERROR: get buffer failed, Line %d\n", (int)__LINE__);
		goto erro;
	}

    /* memory init */
    memset((void *)src_buffer, 0, size);

    /* make error from 0 bit to 9 bits per 1024 bytes */
    for(i = 1; i <= 9; i++)
    {
        cprintf("Error bits = %d\n", i);
        /* write to flash with ecc type = 1(4) */
        ret = nand_write(flash_addr, (u32)src_buffer, size, 0);
        if(ret)
        {
    	    cprintf("ERROR: nand write error, Line %d\n", (int)__LINE__);
    		goto erro;
    	}

        cprintf("Before nand_write\n");
        buffer =  src_buffer;
        PRINT_DATAS(buffer, 24, j);

        /* read from flash with ecc type = 0 */
        ret = nand_read_raw(flash_addr / nand_page_size, 0, (u32)temp_buffer, size, 0);
        if(ret)
        {
    	    cprintf("ERROR: nand read raw error, Line %d\n", (int)__LINE__);
    		goto erro;
    	}

        cprintf("After nand_read_raw\n");
        buffer =  temp_buffer;
        PRINT_DATAS(buffer, 24, j);

        /* erase */
        ret = nand_erase(block_id);
        if(ret)
        {
    	    cprintf("ERROR: nand erase error, Line %d\n", (int)__LINE__);
    		goto erro;
        }

        buffer =  temp_buffer;
        for(j = 1; j <= i; j++)
        {
            *buffer = 1;
            buffer++;
        }

        /* write to flash with ecc type = 0 */
        ret = nand_write_raw(flash_addr / nand_page_size, 0, (u32)temp_buffer, size, 0);
        if(ret)
        {
    	    cprintf("ERROR: nand write raw error, Line %d\n", (int)__LINE__);
    		goto erro;
    	}

        cprintf("After nand_write_raw\n");
        buffer =  temp_buffer;
        PRINT_DATAS(buffer, 24, j);

        /* read from flash with ecc type = 0 */
        ret = nand_read_raw(flash_addr / nand_page_size, 0, (u32)temp_buffer, size, 0);
        if(ret)
        {
    	    cprintf("ERROR: nand read raw error, Line %d\n", (int)__LINE__);
    		goto erro;
    	}

        cprintf("After nand_read_raw\n");
        buffer =  temp_buffer;
        PRINT_DATAS(buffer, 24, j);

        /* read from flash with ecc type = 1(4) */
        ret = nand_read(flash_addr, (u32)temp_buffer, size, 0);
        if(ret)
        {
    	    cprintf("ERROR: nand read error, Line %d\n", (int)__LINE__);
    		goto erro;
    	}

        cprintf("After nand_read\n");
        buffer =  temp_buffer;
        PRINT_DATAS(buffer, 24, j);

    }

    /* exit */
    cprintf("\nnandc_test_case_029 sueecss\n");
    return;

erro:
    if(src_buffer)
    {
	    hifree((void *)src_buffer);
	}
    if(temp_buffer)
    {
        hifree((void *)temp_buffer);
    }
    cprintf("\nnandc_test_case_029 failed, ret = %d\n", ret);
}

/******************************************************************************
* �� �� ��: nandc_test_case_030
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����nandc ecc type = 4��ʱ��ľ�������. ecc type = 1ʱ��nandc�ڲ���
*           ת��Ϊecc type = 4������ʵ����ʹ�õ���4 bit ecc������������������
*           ��8bit / 1024 Bytesʱ��nandcӦ�ö��ܹ�������
*           �������������case 29һ��
*******************************************************************************/
void nandc_test_case_030(void)
{
    nandc_test_case_029();
}


/******************************************************************************
* �� �� ��: nandc_test_case_031
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����nandc ecc type = 8��ʱ��ľ�������. ����������������16bit / 1024 Bytes
*           ʱ��nandcӦ�ö��ܹ�����
*******************************************************************************/
void nandc_test_case_031(void)
{
    u32 size = 0x800, nand_page_size = 0x800;
	u32 ret, i, j, wrong_value;
    u32 flash_addr = 0x100000;
    u32* src_buffer = NULL;
    u32* temp_buffer = NULL;

    /* nand isinit */
	ret = nand_init();
    if(ret)
    {
        goto erro;
    }

    /* get buffer */
    src_buffer = (u32 *)himalloc(size);
    temp_buffer = (u32 *)himalloc(size);
    if((!src_buffer) || (!temp_buffer))
    {
	    cprintf("ERROR: get buffer failed, Line %d\n", (int)__LINE__);
		goto erro;
	}

    /* memory init */
    memset((void *)src_buffer, 0, size);

    /* write to flash with ecc type = 8 */
    ret = nand_write(flash_addr, (u32)src_buffer, size, 0);
    if(ret)
    {
	    cprintf("ERROR: nand write error, Line %d\n", (int)__LINE__);
		goto erro;
	}

    /* read from flash with ecc type = 0 */
    ret = nand_read_raw(flash_addr / nand_page_size, 0, (u32)temp_buffer, size, 0);
    if(ret)
    {
	    cprintf("ERROR: nand read raw error, Line %d\n", (int)__LINE__);
		goto erro;
	}

    /* make error from 0 bit to 17 bits per 1024 bytes */
    for(i = 1; i <= 17; i++)
    {
        cprintf("\terror bits = %d\n", i);
        wrong_value = 0;

        /* make a wrong value contains error bits */
        for(j = 1; j <= i; j++)
        {
            wrong_value |= (1 << (j - 1));
        }

        cprintf("\twrong_value = 0x%x\n", wrong_value);
        memset((void *)temp_buffer, wrong_value, sizeof(u32));

        /* write to flash with ecc type = 0 */
        ret = nand_write_raw(flash_addr / nand_page_size, 0, (u32)temp_buffer, size, 0);
        if(ret)
        {
    	    cprintf("ERROR: nand write raw error, Line %d\n", (int)__LINE__);
    		goto erro;
    	}

        /* read from flash with ecc type = 8 */
        ret = nand_read(flash_addr, (u32)temp_buffer, size, 0);
        if(ret)
        {
    	    cprintf("ERROR: nand read error, Line %d\n", (int)__LINE__);
    		goto erro;
    	}
    }

    /* exit */
    cprintf("\nnandc_test_case_031 sueecss\n");
    return;

erro:
    if(src_buffer)
    {
	    hifree((void *)src_buffer);
	}
    if(temp_buffer)
    {
        hifree((void *)temp_buffer);
    }
    cprintf("\nnandc_test_case_031 failed, ret = %d\n", ret);
}

/******************************************************************************
* �� �� ��: nandc_test_case_032
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����bootģʽ��nandc�����������Ĺ��ܣ���������ʶ��1-6������
*******************************************************************************/
void nandc_test_case_032(void)
{
    /*
     * ���Գ���:
     * 1. block 0 - block 5���Ϊbad block
     * 2. ��bootloader(m3boot)�յ�block 6��ʼ��ַ��block 6����Ϊbad
     * ��������������bootloader�ܹ���������(�������Ϊ�����ܹ���ӡ123).
     *
     * ��ע��ļ���:
     * 1.mark block bad�Ĺ�����Ҫ��u32 nand_bad(u32 block_id)ʵ�֣�������ӿ�Ĭ��
     * ������block 0 bad�������Ҫ���ýӿ����ж�block_idΪ0�Ĵ���ע����
     * 2.��bootloader�յ�block 6��ʹ�÷��������صķ���ʵ�ֵģ���������:
     * d.load.elf fastboot.img.elf  // load burn tool, whose start address is axi
     * d.load ucos.bin 0x50000000   // load to DDR
     * r.s pc nand_write            // set pc pointer to nand_write
     * r.s r0 0xc0000               // set flash addr = block_size * 6, as block size is 0x20000
     * r.s r1 0x50000000            // set DDR addr
     * r.s r2 0x1000                // set write size two pages, actually one page is enough
     * r.s r3 0                     // set *skip_length NULL
     * set a breakpoint in the end of nand_write
     */
}
#else /* __KERNEL__ */

/******************************************************************************
* �� �� ��: nandc_test_case_015
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����A����nandc����read flash id����
*******************************************************************************/
void nandc_test_case_015(void)
{

}

/******************************************************************************
* �� �� ��: nandc_test_case_016
* ��������: ����A����nandc������������
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: 1�������������nand��ʼ����read��write�ͻ����ѯ����ǹ���
*           2����������:
*               1 - find a good block in "cdromiso"
*               2 - get two buffers named "buffer" and "buffer_value".
*               3 - write "buffer" which is initialied with 0x00000000 to the block
*               4 - erase the block
*               5 - read the data back from the block to "buffer", which should be 0xFFFFFFFF
*               6 - compare "buffer" with "buffer_value", which is initialied with 0xFFFFFFFF
*******************************************************************************/
int nandc_test_case_016(void)
{
    unsigned char *src_buffer = NULL;
    unsigned char *read_buffer = NULL;
    struct erase_info instr;
    struct mtd_info *mtd = NULL;
    char *partition_name = PTABLE_RECOVERYB_NM;
    unsigned long long partition_offset = 0;
    int ret = 0;
    unsigned int retlength, length;

    /* get mtd device */
	mtd = get_mtd_device_nm(partition_name);
	if (IS_ERR(mtd))
    {
		printk(KERN_ERR"get_mtd_device_nm error\n");
		ret = PTR_ERR(mtd);
		goto erro;
	}

    /* get ram buffer */
    length = mtd->erasesize;
	src_buffer = (unsigned char *)kmalloc(length, GFP_KERNEL);
    read_buffer = (unsigned char *)kmalloc(length, GFP_KERNEL);
	if(!src_buffer || !read_buffer)
	{
		printk(KERN_ERR"get ram buffer failed!\n");
		goto erro;
	}

    /* find a good block */
    while(partition_offset <= mtd->size)
    {
        ret = mtd_block_isbad(mtd, (long long)partition_offset);  
        if(!ret)
        {
            break;
        }
        else
        {
            partition_offset += mtd->erasesize;
        }
    }
    if(partition_offset == mtd->size)
    {
        printk(KERN_ERR"get good block failed!\n");
        goto erro;
    }

    /* erase */
    instr.mtd = mtd;
	instr.addr = partition_offset;
	instr.len = mtd->erasesize;
	instr.time = 1000;
	instr.retries = 2;
	instr.callback = NULL;
	instr.priv = 0;
    ret = mtd_erase(mtd, &instr);
	if (0 != ret)
	{
		printk(KERN_ERR"mtd nand_erase error, ret = %d.\n", ret);
		goto erro;
	}

    /* read */  
    ret = mtd_read(mtd, (long long)partition_offset, mtd->erasesize, &retlength, (unsigned char*)read_buffer);
    if(ret)
    {
        printk(KERN_ERR"mtd read error.\n");
        goto erro;
    }

    /* compare with 0xFF */
    memset(src_buffer, 0xFF, mtd->erasesize);
    ret = memcmp(read_buffer, src_buffer, mtd->erasesize);
    if(ret)
    {
        printk(KERN_ERR"mem compare error.\n");
        goto erro;
    }

    kfree(src_buffer);
    kfree(read_buffer);

    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }

    printk(KERN_ERR"SUCCESS: nandc_test_case_016 successful\n");
    return OK;

erro:
    if(src_buffer)
        kfree(src_buffer);
    if(read_buffer)
        kfree(read_buffer);

    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }
    printk(KERN_ERR"ERROR: nandc_test_case_016 error, ret = %d\n\n", ret);
    return ERROR;
}

/******************************************************************************
* �� �� ��: nandc_test_case_017
* ��������: ����A����nandc����bus��ʽ��ecc��дdata
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: 1�������ڳ�ʼ���������ѯ�ͱ�ǹ���
*           2��step as follow
*               1 - find a good block "cdromiso";
*               2 - write "src_buffer" which is initialized with 0x00000000 to flash
*               3 - read back from flash to "read_buffer" which is initialized with 0xAAAAAAAA
*               4 - compare "src_buffer" and "read_buffer"
*******************************************************************************/
void nandc_test_case_017(void)
{
    unsigned char *src_buffer = NULL;
    unsigned char *read_buffer = NULL;
    struct erase_info instr;
    struct mtd_info *mtd = NULL;
    char *partition_name = PTABLE_RECOVERYB_NM;    /* good block, no need to check bad */
    unsigned long long partition_offset = 0;
    int ret = 0;
    unsigned int retlength, length;

    /* get mtd device */
	mtd = get_mtd_device_nm(partition_name);
	if (IS_ERR(mtd))
    {
		printk(KERN_ERR"get_mtd_device_nm error\n");
		ret = PTR_ERR(mtd);
		goto erro;
	}

    /* get ram buffer */
    length = mtd->erasesize;
	src_buffer  = (unsigned char *)kmalloc(length, GFP_KERNEL);                        ///////////
	read_buffer = (unsigned char *)kmalloc(length, GFP_KERNEL);
	if(!src_buffer || !read_buffer)
	{
		printk(KERN_ERR"get ram buffer failed!\n");
		goto erro;
	}

    /* buffer init */
    memset((u32 *)src_buffer,  0x00, length);
    memset((u32 *)read_buffer, 0xAA, length);

    /* erase */
	instr.mtd      = mtd;
	instr.addr     = partition_offset;
	instr.len      = length;
	instr.time     = 1000;
	instr.retries  = 2;
	instr.callback = NULL;
	instr.priv     = 0;

	ret = mtd_erase(mtd, &instr);
	if(ret)
    {
        printk(KERN_ERR"mtd erase error, ret = %d.\n", ret);
        goto erro;
    }

    /* write */
    partition_offset = 0;
	if(partition_offset & (mtd->writesize - 1)) /* partition_offset must be page align */
	{
		printk(KERN_ERR"partition_offset is not page align.\n");
		goto erro;
	}
    ret = mtd_write(mtd, (long long)partition_offset, mtd->erasesize, &retlength, (unsigned char*)src_buffer);
	if(ret)
    {
        printk(KERN_ERR"mtd write error, ret = %d.\n", ret);
        goto erro;
    }

    /* read */
    ret = mtd_read(mtd, (long long)partition_offset, length, &retlength, (unsigned char*)read_buffer);
	if(ret)
    {
        printk(KERN_ERR"mtd read error, ret = %d.\n", ret);
        goto erro;
    }

    /* compare */
    ret = memcmp(src_buffer, read_buffer, length);
    if(ret)
    {
        printk(KERN_ERR"memcmp error, ret = %d.\n", ret);
        goto erro;
    }

    /* erase, to make block clean */
    instr.mtd = mtd;
	instr.addr = partition_offset;
	instr.len = mtd->erasesize;
	instr.time = 1000;
	instr.retries = 2;
	instr.callback = NULL;
	instr.priv = 0;
    ret = mtd_erase(mtd, &instr);
	if (0 != ret)
	{
		printk(KERN_ERR"mtd nand_erase error, ret = %d.\n", ret);
		goto erro;
	}

    kfree(src_buffer);
    kfree(read_buffer);

    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }
    printk(KERN_NOTICE"SUCCESS: nandc_test_case_017 success\n");

erro:
    if(src_buffer)
        kfree(src_buffer);
    if(read_buffer)
        kfree(read_buffer);

    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }

    printk(KERN_ERR"ERROR: nandc_test_case_017 error\n");
}

/******************************************************************************
* �� �� ��: nandc_test_case_018
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����A����nandc����bus��ʽ��ecc��дdata+oob
*******************************************************************************/
void nandc_test_case_018(void)
{
    /* ��������case_23һ�������ٵ���ʵ�� */
}

/******************************************************************************
* �� �� ��: nandc_test_case_019
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����A����nandc����bus��ʽ����ecc��дdata
*******************************************************************************/
void nandc_test_case_019(void)
{
    /* ��������case_24һ�������ٵ���ʵ�� */
}

/******************************************************************************
* �� �� ��: nandc_test_case_020
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����A����nandc����bus��ʽ��ǻ��鹦��
*******************************************************************************/
void nandc_test_case_020(void)
{
    /* ��������case_27һ�� */
}

/******************************************************************************
* �� �� ��: nandc_test_case_021
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����A����nandc����bus��ʽ��ѯ���鹦��
*******************************************************************************/
void nandc_test_case_021(void)
{
    /* ��������case_28һ�� */
}

/******************************************************************************
* �� �� ��: nandc_test_case_022
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����A����nandc����DMA��ʽ��ecc��дdata
*******************************************************************************/
int nandc_test_case_022(void)
{
    unsigned char *src_buffer = NULL;
    unsigned char *read_buffer = NULL;
    struct erase_info instr;
    struct mtd_info *mtd = NULL;
    char *partition_name = PTABLE_RECOVERYB_NM;    /* good block, no need to check bad */
    unsigned long long partition_offset = 0;    
    int ret = 0;
    unsigned int retlength, length;

    /* get mtd device */
	mtd = get_mtd_device_nm(partition_name);
	if (IS_ERR(mtd))
    {
		printk(KERN_ERR"get_mtd_device_nm error\n");
		ret = PTR_ERR(mtd);
		goto erro;
	}

    /* get ram buffer */
    length = mtd->erasesize;
	src_buffer  = (unsigned char *)kmalloc(length, GFP_KERNEL);                        ///////////
	read_buffer = (unsigned char *)kmalloc(length, GFP_KERNEL);
	if(!src_buffer || !read_buffer)
	{
		printk(KERN_ERR"get ram buffer failed!\n");
		goto erro;
	}

    /* buffer init */
    memset((u32 *)src_buffer,  0xAA, length);
    memset((u32 *)read_buffer, 0x00, length);

    /* find a good block */
    while(partition_offset <= mtd->size)
    {
        ret = mtd_block_isbad(mtd, partition_offset);
        if(!ret)
        {
            break;
        }
        else
        {
            partition_offset += mtd->erasesize;
        }
    }
    if(partition_offset == mtd->size)
    {
        printk(KERN_ERR"get good block failed!\n");
        goto erro;
    }
    printk("good block found, partition_offset = 0x%x\n", partition_offset);

    /* erase */
	instr.mtd      = mtd;
	instr.addr     = partition_offset;
	instr.len      = length;
	instr.time     = 1000;
	instr.retries  = 2;
	instr.callback = NULL;
	instr.priv     = 0;

	ret = mtd_erase(mtd, &instr);
	if(ret)
    {
        printk(KERN_ERR"mtd erase error, ret = %d.\n", ret);
        goto erro;
    }

    /* write */
	if(partition_offset & (mtd->writesize - 1)) /* partition_offset must be page align */
	{
		printk(KERN_ERR"partition_offset is not page align.\n");
		goto erro;
	}
    ret = mtd_write(mtd, (long long)partition_offset, length, &retlength, (unsigned char*)src_buffer);
	if(ret)
    {
        printk(KERN_ERR"mtd write error, ret = %d.\n", ret);
        goto erro;
    }

    /* read */
    ret = mtd_read(mtd, (long long)partition_offset, length, &retlength, (unsigned char*)read_buffer);
	if(ret)
    {
        printk(KERN_ERR"mtd read error, ret = %d.\n", ret);
        goto erro;
    }

    /* compare */
    ret = memcmp(src_buffer, read_buffer, length);
    if(ret)
    {
        printk(KERN_ERR"memcmp error, ret = %d.\n", ret);
        goto erro;
    }

    /* erase, to make block clean */
    instr.mtd = mtd;
	instr.addr = partition_offset;
	instr.len = mtd->erasesize;
	instr.time = 1000;
	instr.retries = 2;
	instr.callback = NULL;
	instr.priv = 0;
    ret = mtd_erase(mtd, &instr);
	if (0 != ret)
	{
		printk(KERN_ERR"mtd nand_erase error, ret = %d.\n", ret);
		goto erro;
	}

    kfree(src_buffer);
    kfree(read_buffer);

    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }

    printk(KERN_NOTICE"SUCCESS: nandc_test_case_022 successful\n\n");
    return OK;

erro:
    if(src_buffer)
        kfree(src_buffer);
    if(read_buffer)
        kfree(read_buffer);

    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }

    printk(KERN_ERR"ERROR: nandc_test_case_022 error\n\n");
    return ERROR;
}

/******************************************************************************
* �� �� ��: nandc_test_case_023
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����A����nandc����DMA��ʽ��ecc��дdata+oob
*******************************************************************************/
int nandc_test_case_023(void)
{
    unsigned char *src_buffer = NULL;
    unsigned char *read_buffer = NULL;
    struct erase_info instr;
    struct mtd_oob_ops ops;
    struct mtd_info *mtd = NULL;
    char *partition_name = PTABLE_RECOVERYB_NM;    /* good block, no need to check bad */
    unsigned long long partition_offset = 0;    
    int ret = 0;
    unsigned int length;

    /* get mtd device */
	mtd = get_mtd_device_nm(partition_name);
	if (IS_ERR(mtd))
    {
		printk(KERN_ERR"get_mtd_device_nm error\n");
		ret = PTR_ERR(mtd);
		goto erro;
	}

    /* get ram buffer */
    length = mtd->writesize + mtd->oobsize;
	src_buffer  = (unsigned char *)kmalloc(length, GFP_KERNEL);
	read_buffer = (unsigned char *)kmalloc(length, GFP_KERNEL);
	if(!src_buffer || !read_buffer)
	{
		printk(KERN_ERR"get ram buffer failed!\n");
		goto erro;
	}

    /* buffer init */
    memset((void *)src_buffer,  0xAA, length);
    memset((void *)read_buffer, 0xBB, length);

    /* find a good block */
    while(partition_offset <= mtd->size)
    {
        ret = mtd_block_isbad(mtd, partition_offset);
        if(!ret)
        {
            break;
        }
        else
        {
            partition_offset += mtd->erasesize;
        }
    }
    if(partition_offset == mtd->size)
    {
        printk(KERN_ERR"get good block failed!\n");
        goto erro;
    }

    /* erase */
	instr.mtd      = mtd;
	instr.addr     = partition_offset;
	instr.len      = mtd->erasesize;
	instr.time     = 1000;
	instr.retries  = 2;
	instr.callback = NULL;
	instr.priv     = 0;

	ret = mtd_erase(mtd, &instr);
	if(ret)
    {
        printk(KERN_ERR"mtd erase error, ret = %d.\n", ret);
        goto erro;
    }

    /* write */
	if(partition_offset & (mtd->writesize - 1)) /* partition_offset must be page align */
	{
		printk(KERN_ERR"partition_offset is not page align.\n");
		goto erro;
	}

    ops.mode = MTD_OPS_AUTO_OOB;
	ops.len = mtd->writesize;
	ops.ooblen = YAFFS_BYTES_PER_SPARE;
    ops.ooboffs = 0;
	ops.datbuf = (u8 *) src_buffer;
	ops.oobbuf = (u8 *) (src_buffer + mtd->writesize);

    ret = mtd->_write_oob(mtd, partition_offset, &ops);
	if(ret)
    {
        printk(KERN_ERR"mtd write oob error, ret = %d.\n", ret);
        goto erro;
    }

    /* read */
    ops.mode = MTD_OPS_AUTO_OOB;
	ops.len = mtd->writesize;
	ops.ooblen = YAFFS_BYTES_PER_SPARE;
    ops.ooboffs = 0;
	ops.datbuf = (u8 *) read_buffer;
	ops.oobbuf = (u8 *) (read_buffer + mtd->writesize);

    ret = mtd->_read_oob(mtd, partition_offset, &ops);
	if(ret)
    {
        printk(KERN_ERR"mtd write error, ret = %d.\n", ret);
        goto erro;
    }

    /* compare */
    ret = memcmp(src_buffer, read_buffer, mtd->writesize + YAFFS_BYTES_PER_SPARE);
    if(ret)
    {
        printk(KERN_ERR"memcmp error, ret = %d.\n", ret);
        goto erro;
    }
    
    /* erase, to make block clean */
    instr.mtd = mtd;
	instr.addr = partition_offset;
	instr.len = mtd->erasesize;
	instr.time = 1000;
	instr.retries = 2;
	instr.callback = NULL;
	instr.priv = 0;
    ret = mtd_erase(mtd, &instr);
	if (0 != ret)
	{
		printk(KERN_ERR"mtd nand_erase error, ret = %d.\n", ret);
		goto erro;
	}
    
    kfree(src_buffer);
    kfree(read_buffer);

    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }
    
    printk(KERN_NOTICE"SUCCESS: nandc_test_case_023 successful\n\n");
    return OK;

erro:
    if(src_buffer)
        kfree(src_buffer);
    if(read_buffer)
        kfree(read_buffer);

    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }
    
    printk(KERN_ERR"ERROR: nandc_test_case_023 error\n\n");
    return ERROR;
}

/******************************************************************************
* �� �� ��: nandc_test_case_024
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����A����nandc����DMA��ʽ��eccֻ��oob
*******************************************************************************/
void nandc_test_case_024(void)
{
    /* �������Ŀǰû��ʹ�ã���ʱ��ʵ��
     * DMA��eccֻ��oob�Ĺ������ڲ�ѯ�����ʱ���õģ����������ͳһʹ��ecc0 mode��
     * ���Ըù�����Ҫ����������
     */
}

/******************************************************************************
* �� �� ��: nandc_test_case_025
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����A����nandc����DMA��ʽ����ecc��дdata
*******************************************************************************/
void nandc_test_case_025(void)
{
    /* ����NANDC��˵��DMA��ʽ��data�Ķ�д���Ƕ�data+oob�Ķ�д��������nandc����eccֻ��дdata�Ĳ�����
     * ��������˵����ʹ�ò���ecc��дdata�Ĳ�������������ʵ�� */
}

/******************************************************************************
* �� �� ��: nandc_test_case_026
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����A����nandc����DMA��ʽ����ecc��дdata+oob
*******************************************************************************/
void nandc_test_case_026(void)
{
    /* A�����ѯ����ʹ�õ��ǲ���ecc��data+oob����ǻ���ʹ�õ��ǲ���eccдdata+oob��case 27��case 28��ʵ�ִ˹��ܣ��˴�
     * ���ٵ����ṩ
     */
}

/******************************************************************************
* �� �� ��: nandc_test_case_027
* ��������: ����A����nandc����DMA��ʽ��ǻ��鹦��
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: 1������ı�ǺͲ�ѯ���ܲ��Ի�������������case_28��case_27һ��
*           2��step as follow
*               1 - find a good block form "cdromiso";
*               2 - mark it bad
*               3 - check whether it bad. if bad, success; else, fail.
*******************************************************************************/
void nandc_test_case_027(void)
{
    struct mtd_info *mtd = NULL;
    struct erase_info instr;
    char *partition_name = PTABLE_RECOVERYB_NM;
    unsigned int partition_offset = 0;    
    int ret;

    /* get mtd device */
	mtd = get_mtd_device_nm(partition_name);
	if (IS_ERR(mtd))
    {
		printk(KERN_ERR"get_mtd_device_nm error\n");
		ret = PTR_ERR(mtd);
		goto erro;
	}

    /* find a good block */
    while(partition_offset <= mtd->size)
    {
        ret = mtd_block_isbad(mtd, partition_offset);
        if(!ret)
        {
            break;
        }
        else
        {
            partition_offset += mtd->erasesize;
        }
    }
    if(partition_offset == mtd->size)
    {
        printk(KERN_ERR"get good block failed!\n");
        goto erro;
    }

    /* erase */
    instr.mtd = mtd;
	instr.addr = partition_offset;
	instr.len = mtd->erasesize;
	instr.time = 1000;
	instr.retries = 2;
	instr.callback = NULL;
	instr.priv = 0;
    ret = mtd_erase(mtd, &instr);
	if (0 != ret)
	{
		printk(KERN_ERR"mtd nand_erase error, ret = %d.\n", ret);
		goto erro;
	}

    /* mark bad */
    ret = mtd_block_markbad(mtd, partition_offset);
    if(ret)
	{
		printk(KERN_ERR"mtd mark block bad failed!\n");
		goto erro;
	}

    /* check bad */
    ret = mtd_block_isbad(mtd, partition_offset - partition_offset % mtd->erasesize);
    if (!ret)
    {
        /* bad block, skip */
    	printk(KERN_ERR"mtd block isbad error, partition offset is 0x%x\n", partition_offset);
        goto erro;
    }

    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }
    
    printk(KERN_ERR"SUCCESS: nandc_test_case_027 successful\n\n");
    return;
erro:

    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }
    
    printk(KERN_ERR"ERROR: nandc_test_case_027 failed, ret = %d\n\n",ret);
    return;
}

/******************************************************************************
* �� �� ��: nandc_test_case_028
* ��������: ����A����nandc����DMA��ʽ��ѯ���鹦��
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: 1������ı�ǺͲ�ѯ���ܲ��Ի�������������case_28��case_27һ��
*           2��step as follow
*               1 - find a good block form block 8;
*               2 - mark it bad
*               3 - check whether it bad. if bad, success; else, fail.
*******************************************************************************/
void nandc_test_case_028(void)
{
    /* ��������case 27ʵ��һ�����˴����ٵ���ʵ�� */
}

/******************************************************************************  
* �� �� ��: nandc_test_case_033  
* ��������: ����A����nandc����д���ٶ�  
* �������: ��  
* �������: ��  
* �� �� ֵ: 0 - �ɹ������� - ʧ��  
* ����˵��:   
*******************************************************************************/  
int nandc_test_case_033(void)  
{  
    char *partition_name = PTABLE_RECOVERYB_NM;  
    unsigned long long partition_offset = 0;    
    int flash_addr;
    unsigned int *src_buffer = NULL;
    unsigned int *temp = NULL;
    unsigned int buffer_size = 256 * 1024;
    unsigned int i, j, time, time_test = 100;
    signed int start_time, end_time, time_cost;

    /* get buffer */
    src_buffer = kmalloc(buffer_size, GFP_KERNEL);
    if(!src_buffer)
    {
        printk("malloc write buffer error.\n");
        return -1;
    }

    /* buffer init */
    temp = src_buffer;
    for(i = 0; i < buffer_size / sizeof(int); i++)
    {
        *temp = i;
        temp++;
    }

    /* write time_test times, for 1MB data written per time */
    time = 1024 * 1024 /buffer_size;
    start_time = bsp_get_slice_value();
    for(i = 0; i < time_test; i++)
    {
        flash_addr = partition_offset;
        for(j = 0; j < time; j++)
        {
            if(bsp_nand_write(partition_name, flash_addr, src_buffer, buffer_size))
            {
                printk("write error, partition = %s, offset = 0x%x, i = %d, j = %d\n", partition_name, flash_addr, i, j);
                goto erro;
            }
            flash_addr += buffer_size;
        }
        partition_offset += 4096;
    }
    end_time = bsp_get_slice_value();

    /* calculate speed */
    time_cost = end_time - start_time;
    if(time_cost < 0)
    {
        printk("invalid time stamp, start_time = %d, end_time = %d\n", start_time, end_time);
        goto erro;
    }

    /* printk("write speed: %fMB/s", (time_test * 32 * 1024 / time_cost)); */ /* no support for float division */
    printk("Dividend: %d\n", time_test * 32 * 1024); /* the frequency of the timer is 32K */
    printk("Divisor : %d\n", time_cost);

    /* free buffer */
    kfree(src_buffer);

    /* success */
    return 0;
erro:
    if(src_buffer)
    {
        kfree(src_buffer);
    }
    return -1;

}

#endif /* #ifdef __FASTBOOT__ */

/******************************************************************************
* �� �� ��: test_nandc
* ��������: ���Ժ������
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ��
*******************************************************************************/
void test_nandc(void)
{
#ifdef __FASTBOOT__
/*
    nandc_test_case_001();
*/
	nandc_test_case_006();
	nandc_test_case_002();
	nandc_test_case_003();
	nandc_test_case_004();
	nandc_test_case_005();

/*
	nandc_test_case_007();
	nandc_test_case_008();
	nandc_test_case_009();
	nandc_test_case_010();
	nandc_test_case_011();
	nandc_test_case_012();
	nandc_test_case_013();
	nandc_test_case_014();
	nandc_test_case_029();
	nandc_test_case_030();
	nandc_test_case_031();
*/
#else  /* kernel */

    printk("\nBegin testing nandc in kernel...\n");

    nandc_test_case_016();
    nandc_test_case_022();
	nandc_test_case_023();
	nandc_test_case_027();

#endif /* #ifdef __FASTBOOT__ */
}
/*************************************** END: test nandc ********************************************/


/*************************************** BEGIN: test nandc "bsp" interface ********************************************/
#ifdef __FASTBOOT__
#define PRINT_INFO cprintf
#define MALLOC(x) alloc(x)
#define KFREE(x)
#else /* kernel */
#define PRINT_INFO printk
#define MALLOC(x) kmalloc(x, GFP_KERNEL)
#define KFREE(x) kfree(x)
#endif

void test_bsp_nand_read_write(char *partition_name, unsigned int partition_offset, int length)
{
    unsigned char *src_buffer = NULL;
    unsigned char *read_buffer = NULL;
    int ret;

    /* get ram buffer */
	src_buffer = (unsigned char *)MALLOC(length);                        ///////////
	read_buffer = (unsigned char *)MALLOC(length);
	if(!src_buffer || !read_buffer)
	{
		PRINT_INFO("get ram buffer failed!\n");
		goto erro;
	}

    memset(src_buffer, 0xAA, length);
    ret = bsp_nand_write(partition_name, partition_offset, src_buffer, length);
    if(ret)
    {
        PRINT_INFO("ERROR: bsp_nand_write error, ret = %d.\n", ret);
        goto erro;
    }
    else
    {
        PRINT_INFO("SUCCESS: bsp_nand_write success.\n");
    }

    ret = bsp_nand_read(partition_name, partition_offset, read_buffer, length, NULL);
    if(ret)
    {
        PRINT_INFO("ERROR: bsp_nand_read error, ret = %d.\n", ret);
        goto erro;
    }
    else
    {
        PRINT_INFO("SUCCESS: bsp_nand_read success.\n");
    }

    ret = memcmp(src_buffer, read_buffer, length);
    if(ret)
    {
        PRINT_INFO("ERROR: mem_compare error, ret = %d.\n", ret);
        goto erro;
    }
    else
    {
        PRINT_INFO("SUCCESS: mem_compare success.\n");
    }

    KFREE(src_buffer);
    KFREE(read_buffer);
    PRINT_INFO("SUCCESS: bsp_nand_read_write success.\n");
    return ;

erro:
    if(src_buffer)
    {
        KFREE(src_buffer);
    }
    if(read_buffer)
    {
        KFREE(read_buffer);
    }
   PRINT_INFO("ERROR: bsp_nand_read_write failed.\n");
    return ;
}

void test_bsp_bad_block_mangement(char *partition_name, unsigned int partition_offset)
{
#ifdef __FASTBOOT__
    int error_code;
    int block_id;
	struct nandc_host  * host   = NULL;
    ptentry *p = NULL;

    p = flash_find_ptn(partition_name);

    if(p == 0)
    {
        PRINT_INFO("ERROR: test_bsp_bad_block_mangement can't find partition %s\n", partition_name);
        return;
    }

    host = nandc_nand_host;
    if(!host)
    {
        error_code = -2;
        goto erro;
    }

    /* find a block good */
    while(1)
    {
        error_code = bsp_nand_isbad(partition_name, partition_offset);
        if(!error_code) /* good block, break */
        {
            PRINT_INFO("good block found, offset: 0x%x\n", partition_offset);
            break;
        }
        else if(error_code == 1) /* bad block, skip */
        {
            partition_offset += host->nandchip->spec.blocksize;
            continue;
        }
        else /* error */
        {
            PRINT_INFO("ERROR: test_bsp_bad_block_mangement check bad error\n");
            goto erro;
        }
    }

    /* get the block id */
    block_id = (p->start + partition_offset) / host->nandchip->spec.blocksize;

    /* mark bad */
    error_code = nand_bad(block_id);
    if(error_code)
    {
        PRINT_INFO("ERROR: test_bsp_bad_block_mangement mark bad error\n");
        goto erro;
    }

    /* quary bad again */
    error_code = bsp_nand_isbad(partition_name, partition_offset);
    if(1 != error_code) /* should be bad block */
    {
        PRINT_INFO("ERROR: test_bsp_bad_block_mangement check bad error, again\n");
        goto erro;
    }

    cprintf("SUCCESS: test_bsp_bad_block_mangement successful.\n");
    return;

erro:
    cprintf("ERROR: bsp_nand_isbad failed, error_code = %d.\n", error_code);
#else /* __KERNEL__ */

    int error_code;
    struct mtd_info *mtd = NULL;

    mtd = get_mtd_device_nm(partition_name);
	if (IS_ERR(mtd))
    {
		printk(KERN_ERR"get_mtd_device_nm error\n");
		error_code = PTR_ERR(mtd);
		goto ERRO;
	}

    /* find a block good */
    while(1)
    {
        error_code = bsp_nand_isbad(partition_name, partition_offset);
        if(!error_code) /* good block, break */
        {
            break;
        }
        else if(error_code == 1) /* bad block, skip */
        {
            partition_offset += mtd->erasesize;
            continue;
        }
        else /* error */
        {
            PRINT_INFO("ERROR: test_bsp_bad_block_mangement check bad error\n");
            goto ERRO;
        }
    }

    /* mark bad */
    /*lint -save -e647*/
    error_code = mtd_block_markbad(mtd, (long long)(partition_offset / mtd->erasesize * mtd->erasesize));
    /*lint -restore */
    if(error_code)
	{
		printk(KERN_ERR"mtd mark block bad failed as reading!\n");
		goto ERRO;
	}

    /* check if bad, should be bad */
    error_code = bsp_nand_isbad(partition_name, partition_offset);
    if(1 != error_code) /* should be bad block */
    {
        PRINT_INFO("ERROR: test_bsp_bad_block_mangement check bad error, again, partition name: %s, offset: 0x%x\n", partition_name, partition_offset);
        goto ERRO;
    }

    /* END */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }
    PRINT_INFO("SUCCESS: test_bsp_bad_block_mangement successful.\n");
    return;

ERRO:
    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }
    PRINT_INFO("ERROR: bsp_nand_isbad failed, error_code = %d.\n", error_code);
#endif
}
#if 0
#ifdef __FASTBOOT__

/******************************************************************************
* �� �� ��: test_bsp_nv_flag
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����NV flag�Ķ�д.д������A������fastboot��ֻ���������ӿ�Ҫ��A�˵�test_bsp_nv_flag���ʹ��
*
*******************************************************************************/
void test_bsp_nv_flag(void)
{
    unsigned char flag; 
    int ret = NANDC_ERROR;
    char *partition_name = PTABLE_RECOVERYB_NM;
    unsigned int partition_offset;
    struct nand_spec spec;

    ret = bsp_get_nand_info(&spec);
    if(ret)
    {
		cprintf("get nand spec error\n");
        goto erro;
    }

    /* д����block */
    partition_offset = 0;
    cprintf("\n[1] partition offset 0x%x\n", partition_offset);
    ret = bsp_nand_read_flag_nv(partition_name, partition_offset, &flag);
    if(ret)
    {
		cprintf("read nv flag error, offset = 0x%x, ret = %d.\n", partition_offset, ret);
		goto erro;
    }
    if(flag != NV_WRITE_SUCCESS)
    {
		cprintf("flag value error, offset = 0x%x, flag = %d.\n", partition_offset, flag);
    }
    else
    {
        cprintf("[%s] SUCCESS: test read nv flag success, offset = 0x%x.\n", __FUNCTION__, partition_offset);
    }

    /* ��д���һ��page */
    partition_offset += spec.blocksize;
    cprintf("\n[2] partition offset 0x%x\n", partition_offset);
    ret = bsp_nand_read_flag_nv(partition_name, partition_offset, &flag);
    if(ret)
    {
		cprintf("read nv flag error, offset = 0x%x, ret = %d.\n", partition_offset, ret);
		goto erro;
    }
    if(flag != NV_WRITE_SUCCESS)
    {
		cprintf("flag value error, offset = 0x%x, flag = %d.\n", partition_offset, flag);
    }
    else
    {
        cprintf("[%s] SUCCESS: test read nv flag success, offset = 0x%x.\n", __FUNCTION__, partition_offset);
    }

    /* ���һ��pageдһ���� */
    partition_offset += spec.blocksize;
    cprintf("\n[3] partition offset 0x%x\n", partition_offset);
    ret = bsp_nand_read_flag_nv(partition_name, partition_offset, &flag);
    if(ret)
    {
		cprintf("read nv flag error, offset = 0x%x, ret = %d.\n", partition_offset, ret);
		goto erro;
    }
    if(flag != NV_WRITE_SUCCESS)
    {
		cprintf("flag value error, offset = 0x%x, flag = %d.\n", partition_offset, flag);
    }
    else
    {
        cprintf("[%s] SUCCESS: test read nv flag success, offset = 0x%x.\n", __FUNCTION__, partition_offset);
    }

    /* ûд��flagӦ�ò���NV_FLAG */
    partition_offset += spec.blocksize;
    cprintf("\n[4] partition offset 0x%x\n", partition_offset);
    ret = bsp_nand_read_flag_nv(partition_name, partition_offset, &flag);
    if(ret)
    {
		cprintf("read nv flag error, offset = 0x%x, ret = %d.\n", partition_offset, ret);
		goto erro;
    }
    if(flag == NV_WRITE_SUCCESS)
    {
		cprintf("flag value error, offset = 0x%x, flag = %d.\n", partition_offset, flag);
    }
    else
    {
        cprintf("[%s] SUCCESS: test read nv flag success, offset = 0x%x.\n", __FUNCTION__, partition_offset);
    }

    return;
erro:
    return;
}

#else /* __KERNEL__ */
/******************************************************************************
* �� �� ��: do_test_bsp_nv_flag
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����nandc��bsp��ͷ�Ľӿڣ�����ǰ��Ҫ��֤nvimgû�л���
*           ����:
*           1. ��һ���������flag����ȡ��ֵӦ�ò���NV_WRITE_SUCCESS��
*           2. ��һ����дdata��flag��
*           3. �ٶ�flag����ȡ��ֵӦ����NV_WRITE_SUCCESS��
*           4. END.
*******************************************************************************/
void do_test_bsp_nv_flag(struct mtd_info *mtd, unsigned int partition_offset, int length)
{
    unsigned char *src_buffer = NULL;
    struct erase_info instr;
    int ret = ERROR;
    uint8_t flag;

    /* get buffer */
    src_buffer = (unsigned char *)kmalloc(length, GFP_KERNEL);
	if(!src_buffer)
	{
		printk(KERN_ERR"get ram buffer failed!\n");
		goto erro;
	}

    /* find a good block */
    while(partition_offset <= mtd->size)
    {
        ret = mtd_block_isbad(mtd, partition_offset);
        if(!ret)
        {
            break;
        }
        partition_offset += mtd->erasesize;
    }
    if(partition_offset == mtd->size)
    {
        printk(KERN_ERR"get good block failed!\n");
        goto erro;
    }
    printk("[%s] good block found, partition_offset = 0x%x\n", __FUNCTION__, partition_offset);

    /* erase */
    instr.mtd = mtd;
	instr.addr = partition_offset;
	instr.len = mtd->erasesize;
	instr.time = 1000;
	instr.retries = 2;
	instr.callback = NULL;
	instr.priv = 0;
    ret = mtd_erase(mtd, &instr);
	if (ret)
	{
		printk(KERN_ERR"mtd nand_erase error, ret = %d.\n", ret);
		goto erro;
	}

    /* 1. ��һ���������flag����ȡ��ֵӦ�ò���NV_WRITE_SUCCESS��*/
    ret = bsp_nand_read_flag_nv((char *)mtd->name, partition_offset, &flag);
    if(ret)
    {
		printk(KERN_ERR"read nv flag first time error, ret = %d.\n", ret);
		goto erro;
    }
    if(flag == NV_WRITE_SUCCESS)
    {
		printk(KERN_ERR"flag value first time error, flag = %d.\n", flag);
		goto erro;
    }

    /* 2. ��һ����дdata��flag��*/
    ret = bsp_nand_blk_write_nv(mtd, partition_offset, length, src_buffer);
    if(ret)
    {
		printk(KERN_ERR"write nv flag error, ret = %d, length = 0x%x.\n", ret, length);
		goto erro;
    }

    /* 3. �ٶ�flag����ȡ��ֵӦ����NV_WRITE_SUCCESS��*/
    ret = bsp_nand_read_flag_nv((char *)mtd->name, partition_offset, &flag);
    if(ret)
    {
		printk(KERN_ERR"read nv flag second time error, ret = %d.\n", ret);
		goto erro;
    }
    if(flag != NV_WRITE_SUCCESS)
    {
		printk(KERN_ERR"flag value second time error, flag = %d.\n", flag);
		goto erro;
    }

    /* 4. END. */
    kfree(src_buffer);
    printk(KERN_ERR"[%s]SUCCESS: test_bsp_nv_flag success. \n\n", __FUNCTION__);
    return;

erro:
    if(src_buffer)
        kfree(src_buffer);
    printk(KERN_ERR"[%s]ERROR: test_bsp_nv_flag error, ret = %d\n\n", __FUNCTION__, ret);
    return;

}

void test_bsp_nv_flag(void)
{
    /* nvдֻ��A�˷���������������A�˺�fastboot�����У��˴�ֻ������A�˵Ķ�д��ͬʱҲҪ��fastboot����һ�¶� */
    unsigned int partition_offset;
    int length, ret;
    struct mtd_info *mtd = NULL;
    char *partition_name = PTABLE_RECOVERYB_NM;
    unsigned char flag;

    /* get mtd device */
	mtd = get_mtd_device_nm(partition_name);
	if (IS_ERR(mtd))
    {
		printk(KERN_ERR"get_mtd_device_nm error\n");
		ret = PTR_ERR(mtd);
		goto erro;
	}

    /* д����block */
    partition_offset = 0;
    length = mtd->erasesize;
    printk("[1] partition offset 0x%x, length 0x%x\n", partition_offset, length);
    do_test_bsp_nv_flag(mtd, partition_offset, length);

    /* ��д���һ��page */
    partition_offset += mtd->erasesize;
    length = mtd->erasesize - mtd->writesize;
    printk("[2] partition offset 0x%x, length 0x%x\n", partition_offset, length);
    do_test_bsp_nv_flag(mtd, partition_offset, length);

    /* ���һ��pageдһ���� */
    partition_offset += mtd->erasesize;
    length = mtd->erasesize - mtd->writesize + mtd->writesize / 2;
    printk("[3] partition offset 0x%x, length 0x%x\n", partition_offset, length);
    do_test_bsp_nv_flag(mtd, partition_offset, length);

    /* ûдflag����ȡ��ֵӦ�ò���NV_WRITE_SUCCESS��*/
    partition_offset += mtd->erasesize;
    printk("[4] partition offset 0x%x, length 0x%x\n", partition_offset, length);
    ret = bsp_nand_erase(partition_name, partition_offset);
    if(ret)
    {
		printk(KERN_ERR"erase error, ret = %d.\n", ret);
		goto erro;
    }
    ret = bsp_nand_read_flag_nv(partition_name, partition_offset, &flag);
    if(ret)
    {
		printk(KERN_ERR"read nv flag first time error, ret = %d.\n", ret);
		goto erro;
    }
    if(flag == NV_WRITE_SUCCESS)
    {
		printk(KERN_ERR"flag value first time error, flag = %d.\n", flag);
		goto erro;
    }

    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }
    
    printk("[%s] SUCCESS: test nv flag OK.\n", __FUNCTION__);

    return;
erro:
 
    /* release mtd device */
    if (!IS_ERR(mtd))
    {
        put_mtd_device(mtd);
    }
    
   return;
}
#endif /* ifdef __KERNEL__ */
#endif
/******************************************************************************
* �� �� ��: test_bsp
* ��������:
* �������: ��
* �������: ��
* �� �� ֵ: ��
* ����˵��: ����nandc��bsp��ͷ�Ľӿ�
*******************************************************************************/
void test_bsp(void)
{
    char *partition_name = PTABLE_RECOVERYB_NM;
    unsigned int partition_offset;
    int i = 1;
    unsigned int length, page_size = 4096;

    /* just one block */
    PRINT_INFO("\nTest case %d:\n", i++);
    partition_offset = 0;
    length = page_size * PAGESPERBLOCK;
    PRINT_INFO("partition = %s, offset = 0x%x, length = 0x%x\n", partition_name, partition_offset, length);
    test_bsp_nand_read_write(partition_name, partition_offset, length);

    /* half block + one block + half block */
    PRINT_INFO("\nTest case %d:\n", i++);
    partition_offset = PAGESPERBLOCK * page_size / 2;
    length = page_size * (PAGESPERBLOCK * 2);
    PRINT_INFO("partition = %s, offset = 0x%x, length = 0x%x\n", partition_name, partition_offset, length);
    test_bsp_nand_read_write(partition_name, partition_offset, length);

    /* one page */
    PRINT_INFO("\nTest case %d:\n", i++);
    partition_offset = 0;
    length = page_size;
    PRINT_INFO("partition = %s, offset = 0x%x, length = 0x%x\n", partition_name, partition_offset, length);
    test_bsp_nand_read_write(partition_name, partition_offset, length);

    /* beyond one page */
    PRINT_INFO("\nTest case %d:\n", i++);
    partition_offset = page_size / 2;
    length = page_size;
    PRINT_INFO("partition = %s, offset = 0x%x, length = 0x%x\n", partition_name, partition_offset, length);
    test_bsp_nand_read_write(partition_name, partition_offset, length);

    /* in a page */
    PRINT_INFO("\nTest case %d:\n", i++);
    partition_offset = page_size / 2;
    length = 1024;
    PRINT_INFO("partition = %s, offset = 0x%x, length = 0x%x\n", partition_name, partition_offset, length);
    test_bsp_nand_read_write(partition_name, partition_offset, length);

    /* test bad block mangement */
    PRINT_INFO("\nTest case %d:\n", i++);
    partition_offset = 0;
    PRINT_INFO("partition = %s, offset = 0x%x\n", partition_name, partition_offset);
    test_bsp_bad_block_mangement(partition_name, partition_offset);

#if 0
#ifdef __KERNEL__
    /* test nv flag write/read  */
    test_bsp_nv_flag();
#endif
#endif
}

/*************************************** END: test nandc "bsp" interface ********************************************/

#ifdef __cplusplus
}
#endif
