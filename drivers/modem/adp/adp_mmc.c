/**
 * adp_mmc.c - mmc interface
 *
 * Copyright (C), 2011-2013, Hisilicon Technologies Co., Ltd.
 *
 * Authors: jingyong
 *	    
 *
 */

/*lint -save -e18 -e26 -e64 -e115 -e119 -e123 -e529 -e537 -e569 -e570 -e713 -e718 -e732 -e746 -e747 -e958*/

#include <osl_types.h>
#include <linux/scatterlist.h>
#include <linux/mmc/host.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/ioctl.h>
#include <linux/mmc/sd.h>
#include <linux/mmc/card.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/genhd.h>
#include <linux/major.h>
#include <linux/uaccess.h>



#define SDMMC_BLOCK_BYTE 	(512)
#define SDMMC_ONE_BLOCK 	(1)
enum mmc_at_process_status {
	SDMMC_PROCESS_OVER_OR_UNDO = 0,
	SDMMC_PROCESS_IN,
	SDMMC_PROCESS_ERROR,
};

enum mmc_at_process_error { 
	SDMMC_NOT_IN = 0,
	SDMMC_INIT_FAIL,
	SDMMC_PARAMETER_ERROR,
	SDMMC_ADDR_ERROR,
	SDMMC_OTHER_ERROR,
	SDMMC_NO_ERROR_PARA
};
enum mmc_at_process_data {
	SDMMC_DATA0 = 0,
	SDMMC_DATA1,
	SDMMC_DATA2,
	SDMMC_DATA3,
	SDMMC_DATA_BUTT,
};
/*Command*/
enum mmc_at_process_command {
	SDMMC_AT_FORMAT = 0,
	SDMMC_AT_ERASE_ALL,
	SDMMC_AT_ERASE_ADDR,
	SDMMC_AT_WRTIE_ADDR,
	SDMMC_AT_READ,
	SDMMC_AT_BUTT,
};

static unsigned int mmc_at_status;

struct mmc_host* mmc_get_host(void);


int mmc_get_status(void)
{
	struct gendisk *disk;
	int partno = 0;
	disk = get_gendisk(MKDEV(MMC_BLOCK_MAJOR, 0), &partno);
	if (!disk) {
		return 0;
	}
	return 1;
}

int mmc_get_dev_idex(void)
{
	struct gendisk *disk;
	int partno = 0;
	int ret;
	disk = get_gendisk(MKDEV(MMC_BLOCK_MAJOR, 0), &partno);
	if (!disk) {
		return -ENOMEDIUM;
	}
	ret = disk->disk_name[6] - '0';/*lint !e409*/
	return ret;
}
unsigned long mmc_get_capacity(void)
{
	struct gendisk *disk;
	int partno = 0;
	unsigned long ret;
	disk = get_gendisk(MKDEV(MMC_BLOCK_MAJOR, 0), &partno);
	if (!disk) {
		return 0;
	}
	ret = get_capacity(disk);
	return ret;
}

unsigned long mmc_at_prepare(unsigned int tpye, 
	unsigned long addr, char * buf, unsigned long *err, unsigned int *at_status)
{
	int status;
	unsigned int capacity;
	unsigned long ret = -1;/* [false alarm]:fortify disable */

	if (!err || !buf) {
		goto out;
	}
	/*not support */
	if (SDMMC_PROCESS_IN == mmc_at_status) {
		*err = SDMMC_OTHER_ERROR;
		goto out;
	}
	*at_status = SDMMC_PROCESS_IN;
	if (tpye >= SDMMC_AT_BUTT) {
		*err = SDMMC_PARAMETER_ERROR;
		*at_status = SDMMC_PROCESS_ERROR;
		goto out;
	}
	status = mmc_get_status();
	/*sd card not present*/
	if (!status) {
		*err = SDMMC_NOT_IN;
		*at_status = SDMMC_PROCESS_ERROR;
		goto out;
	}
	capacity = mmc_get_capacity();
	switch (tpye) {
		case SDMMC_AT_ERASE_ADDR:
			break;
		case SDMMC_AT_WRTIE_ADDR:
			break;
		case SDMMC_AT_READ:
			if ((addr + SDMMC_ONE_BLOCK) > capacity) {
				*err = SDMMC_ADDR_ERROR;
				*at_status = SDMMC_PROCESS_ERROR;
				goto out;
			}
			break;
		default:
			break;

	}
	return 0;
out:
	return ret;
}

int mmc_at_erase(	struct block_device * blk_dev, unsigned int from, unsigned int to)
{
	struct mmc_ioc_cmd cmd;
	int ret = 0;

	memset(&cmd, 0, sizeof(struct mmc_ioc_cmd));
	cmd.opcode = SD_ERASE_WR_BLK_START;
	cmd.arg = from;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;
	ret = ioctl_by_bdev(blk_dev, MMC_IOC_CMD, (unsigned long)(&cmd));
	if (ret) {
		goto out;
	}
    memset(&cmd, 0, sizeof(struct mmc_ioc_cmd));
	cmd.opcode = SD_ERASE_WR_BLK_END;
	cmd.arg = to;
	cmd.flags = MMC_RSP_SPI_R1 | MMC_RSP_R1 | MMC_CMD_AC;
	ret = ioctl_by_bdev(blk_dev, MMC_IOC_CMD, (unsigned long)(&cmd));
	if (ret) {
		goto out;
	}
    memset(&cmd, 0, sizeof(struct mmc_ioc_cmd));
	cmd.opcode = MMC_ERASE;
	cmd.arg = MMC_ERASE_ARG;
	cmd.flags = MMC_RSP_SPI_R1B | MMC_RSP_R1B | MMC_CMD_AC;
	ret = ioctl_by_bdev(blk_dev, MMC_IOC_CMD, (unsigned long)(&cmd));
out:	
	return ret;
}


int mmc_at_rw(struct block_device * blk_dev, unsigned int from,
	unsigned char *buf, int write, int data)
{
	struct mmc_ioc_cmd cmd;
	int ret = 0;
	unsigned char check_data[5] = {0x00, 0x55, 0xAA, 0xFF, 0x00};
	
	memset(&cmd, 0, sizeof(struct mmc_ioc_cmd));
	if (write) {
		if (data > 4) {
			data = 4;
		}
		memset(buf, check_data[data], SDMMC_BLOCK_BYTE);
		cmd.write_flag = 1;
		cmd.opcode = MMC_WRITE_BLOCK;
	} else {
		cmd.write_flag = 0;
		cmd.opcode = MMC_READ_SINGLE_BLOCK;	
	}
	cmd.blksz = SDMMC_BLOCK_BYTE;
	cmd.flags = MMC_RSP_R1 | MMC_CMD_ADTC;
	cmd.blocks = 1;
	cmd.arg = from;
	mmc_ioc_cmd_set_data(cmd, buf);
	
	ret = ioctl_by_bdev(blk_dev, MMC_IOC_CMD, (unsigned long)(&cmd));
	return ret;
}


/*****************************************************************************
* �� �� ��  : DRV_SD_SG_INIT_TABLE
*
* ��������  : SD������ݴ���sg list��ʼ��
*
* �������  : const void *buf		��������buffer��ַ
				  unsigned int buflen	��������buffer��С��С��32K, ��СΪ512B��������
				  					����32K, ��СΪ32KB�������������bufferΪ128K
* �������  : NA
*
* �� �� ֵ  :  0 : �ɹ�;  ����:ʧ��
* ����˵��  : NA
*
*****************************************************************************/
int DRV_SD_SG_INIT_TABLE(const void *buf,unsigned int buflen)
{
    return 0;
}


int DRV_SD_TRANSFER(struct scatterlist *sg, 
	unsigned dev_addr,unsigned blocks, unsigned blksz, int wrflags)
{
	return 0;
}

/*****************************************************************************
* �� �� ��  : DRV_SD_MULTI_TRANSFER
*
* ��������  : SD������ݴ���
*
* �������  : unsigned dev_addr	��д���SD block��ַ
				  unsigned blocks		��д���block ����
				  unsigned blksz		ÿ��block �Ĵ�С����λ�ֽ�
				  int write			��д��־λ��д:1;	��:0
* �������  : NA
*
* �� �� ֵ  :  0 : �ɹ�;  ����:ʧ��
* ����˵��  : NA
*
*****************************************************************************/
int DRV_SD_MULTI_TRANSFER(unsigned dev_addr, 
	unsigned blocks,unsigned blksz,int write)
{
    return 0;
}

/*****************************************************************************
* �� �� ��  : DRV_SD_GET_CAPACITY
* ��������  : ��������ѯ
* �������  : ��
* �������  : ��
* �� �� ֵ  : 0 : ʧ�ܣ�>0: ������
*****************************************************************************/
unsigned int DRV_SD_GET_CAPACITY(void)
{
	unsigned int ret;
	ret = mmc_get_capacity();
	return ret;
}

/*****************************************************************************
* �� �� ��  : DRV_SD_GET_STATUS
* ��������  : ����λ��ѯ
* �������  : ��
* �������  : ��
* �� �� ֵ  : 0 : ��λ��-1: ����λ
*****************************************************************************/
int DRV_SD_GET_STATUS(void)
{	
	int ret;
	ret= mmc_get_status();
	return ret ? 0 : -1;
}


int DRV_SDMMC_GET_STATUS(void)
{
	int ret;
	ret = mmc_get_status();
	return ret;
}

unsigned long DRV_SDMMC_GET_OPRT_STATUS(void)
{
	return mmc_at_status;
}


/*****************************************************************************
 �� �� ��  : BSP_SDMMC_ATProcess
 ��������  : at^sd,SD��������д����������ʽ������
             0:
 �������  : �������� ulOp:
            0  ��ʽ��SD����
            1  ��������SD�����ݣ�
            2  ����ָ����ַ���ݵĲ���������ָ�����������ݳ���Ϊ512�ֽڡ�������ĵ�ַ��дȫ1
            3  д���ݵ�SD����ָ����ַ�У���Ҫ���ڶ����͵���������
            4  �����ݵ�SD����ָ����ַ��

            ulAddr < address >  ��ַ����512BYTEΪһ����λ��������n��ʾ

            ulData
             < data >            �������ݣ���ʾ512BYTE�����ݣ�ÿ���ֽڵ����ݾ���ͬ��
             0       �ֽ�����Ϊ0x00
             1       �ֽ�����Ϊ0x55
             2       �ֽ�����Ϊ0xAA
             3       �ֽ�����Ϊ0xFF

 �������  : pulErr
 �� �� ֵ  : 0 ��OK  �� 0 ��Error

            ����Ĵ���ֵ�����*pulErr��
            0 ��ʾSD������λ
            1 ��ʾSD����ʼ��ʧ��
            2 ��ʾ<opr>�����Ƿ�����Ӧ������֧��(�ô�����ATʹ��,����Ҫ����ʹ��)
            3 ��ʾ<address>��ַ�Ƿ�������SD����������
            4 ����δ֪����
*****************************************************************************/

unsigned long  DRV_SDMMC_AT_PROCESS(unsigned int type,
                unsigned long addr,  unsigned long data, 
                unsigned char *buf, unsigned long *err)
{
	unsigned long ret = 0;
	int partno = 0;
	struct gendisk *disk = NULL;
	struct block_device * blk_dev = NULL;
	unsigned int capacity = 0;
	unsigned int from = 0;
	unsigned int to = 0;
    unsigned int nr = 0;
    struct mmc_host *host = NULL;
	
	/*parameter check*/
	ret = mmc_at_prepare(type,addr, buf, err, &mmc_at_status);
	if (ret) {
        return ret;
	}

	disk = get_gendisk(MKDEV(MMC_BLOCK_MAJOR, 0), &partno);
	if (!disk) {
		goto out;
	}
	blk_dev = bdget_disk(disk, partno);
	if (!blk_dev) {
		goto out;
	}
    /*�ڽ��������sd������ǰ������Ҫ�򿪸��豸������block_device��gendisk�Ĺ�������ֹΪ����ɵ�������*/
    ret  = blkdev_get(blk_dev, FMODE_WRITE | FMODE_READ, NULL);
    if (ret)
    {
        goto out;
    }
    host = mmc_get_host();
    if (!host || !host->card) {
        printk(KERN_ERR"host = 0x%x  host->card = 0x%x \n", host, host->card);
        ret = (unsigned int)-1;
        goto out;
    }
	capacity = mmc_get_capacity();

	switch (type) {
		/*erase not yet suport*/
		case SDMMC_AT_ERASE_ADDR:
			from = addr;
			nr = 0x1;
			mmc_claim_host(host);
			ret = mmc_erase(host->card, from, nr, 0x0);
			mmc_release_host(host);
			break;
		case SDMMC_AT_FORMAT:
		case SDMMC_AT_ERASE_ALL:
			from = 0x0;
			nr = capacity - from;
			mmc_claim_host(host);
			ret = mmc_erase(host->card, from, nr, 0x0);
			mmc_release_host(host);
			break;
		case SDMMC_AT_WRTIE_ADDR:
			ret = mmc_at_rw(blk_dev, 0x1, buf, 0x1, data);
			break;
		case SDMMC_AT_READ:
			ret = mmc_at_rw(blk_dev, 0x1, buf, 0x0, 0x0);
			break;
		case SDMMC_AT_BUTT:
			break;
		default:
			break;
	}

out:
	if (ret) {
		*err = SDMMC_OTHER_ERROR;
		mmc_at_status= SDMMC_PROCESS_ERROR;
	} else {
		*err = SDMMC_NO_ERROR_PARA;
		mmc_at_status = SDMMC_PROCESS_OVER_OR_UNDO;
        /*��at��������ʱ���رո��豸���ָ�ԭʼ״̬*/
        blkdev_put(blk_dev, FMODE_WRITE | FMODE_READ);
	}
	return ret;
}

unsigned int at_test(unsigned int type, unsigned long addr, unsigned long data)
{
	unsigned char buf[SDMMC_BLOCK_BYTE];
	unsigned long err;
	unsigned int ret;
	ret = DRV_SDMMC_AT_PROCESS(type, addr, data, buf, &err);
	print_hex_dump(KERN_INFO, "", DUMP_PREFIX_OFFSET, 16, 1,
		buf, SDMMC_BLOCK_BYTE, 0);
	return ret;
}
/*lint -restore*/

