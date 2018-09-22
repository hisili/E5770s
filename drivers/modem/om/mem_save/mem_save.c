#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/poll.h>
#include <linux/personality.h>
#include <linux/file.h>
#include <linux/fdtable.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/rcupdate.h>
#include <linux/hrtimer.h>
#include <linux/statfs.h>

#include "bsp_memmap.h"

typedef enum
{
    DDR_TYPE_LPHY_SDR        = 0,
    DDR_TYPE_TLPHY_IMAGE     = 1,
    DDR_TYPE_LCS             = 2,
    DDR_TYPE_MAX             = 3,
}DDR_TYPE_ENUM;

static int is_ioremap[DDR_TYPE_MAX] = {0};
static u32 virt_addr[DDR_TYPE_MAX] = {0};


s32 addr_ioremap(DDR_TYPE_ENUM ddr_type, u32 phy_addr, u32 size)
{
    if(0 == is_ioremap[ddr_type])
    {
        virt_addr[ddr_type] = (u32)ioremap(phy_addr, size);
        if(0 == virt_addr[ddr_type])
        {

		    return -1;
    	}
        is_ioremap[ddr_type] = 1;
    }
    return 0;
    
}

/*****************************************************************************
* �� �� ��  : file_save
*
* ��������  : ��ָ����ַ���ݱ��浽�ļ���
*
* �������  : u32 export_file_name     �����ļ�����
*             u32 export_virt_addr     �������������ַ
*             u32 count                �������ݴ�С
*
* �� �� ֵ  : s32  ����ֵ:0Ϊ�ɹ���-1Ϊʧ�ܡ�
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
long file_save(char* export_file_name, u32 export_virt_addr, u32 count)
{   
    long ret = 0;
    long len = 0;    
    unsigned int  fd = 0;
    
    mm_segment_t old_fs = get_fs();
    set_fs(KERNEL_DS);

    ret = sys_open(export_file_name, O_RDWR | O_CREAT, 0666);

    if(ret < 0)
    {
        printk("open file %s error,ret:%#x\n",  export_file_name, fd);
        
        /*sys_fsync(fd);*/

        set_fs(old_fs);

        return -1;
    }
	
    fd = (unsigned int)ret;
	
    len = sys_write(fd,(char*)export_virt_addr,count);

    if(count != (unsigned long)len)
    {
        ret = -1;
        printk("write err, writlen=0x%x, wantted len=0x%x\n", (u32)len, (u32)count);
    }
    else
    {
        ret = 0;
        printk("save to %s success\n, pls use lsz %s to upload to securecrt\n", export_file_name, export_file_name);
    }

    sys_fsync(fd);

    set_fs(old_fs);

    return ret;

}


/*****************************************************************************
* �� �� ��  : file_save_tlphy_image
*
* ��������  : ���ڴ�tlphy_image���ݱ��浽�ļ���
*
* �������  : u32 offset_addr          ����TLPHT_IMAGE��ַ��ƫ�Ƶ�ַ
*             u32 data_size            TLPHT_IMAGE��С
*
* �� �� ֵ  : s32  ����ֵ:0Ϊ�ɹ���-1Ϊʧ�ܡ�
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
long file_save_tlphy_image(u32 offset_addr, u32 data_size)
{
    unsigned count = 0;
    unsigned export_phy_addr = 0;
    unsigned export_virt_addr = 0;
    char export_file_name[] = "tlphy_image_data.bin"; 
    
    if(offset_addr + data_size > DDR_TLPHY_IMAGE_SIZE)
    {
	    printk("%s: parameter error.\n", __FUNCTION__);
	    return -1;
    }

    if(0 != addr_ioremap(DDR_TYPE_TLPHY_IMAGE, DDR_TLPHY_IMAGE_ADDR, DDR_TLPHY_IMAGE_SIZE))
    {
	    printk("%s: cannot map IO.\n", __FUNCTION__);
        return -1;
    }
    
    count = data_size;
    export_phy_addr = DDR_TLPHY_IMAGE_ADDR + offset_addr;
    printk("export data address is %#x, and the size is %#x.\n", \
        export_phy_addr, data_size);

    export_virt_addr = virt_addr[DDR_TYPE_TLPHY_IMAGE] + offset_addr;    
    printk("DDR_TLPHY_IMAGE_ADDR = %#x, DDR_TLPHY_ADDR_VIRT = %#x, DDR_TLPHY_IMAGE_SIZE = %#x.\n", \
        DDR_TLPHY_IMAGE_ADDR, virt_addr[DDR_TYPE_TLPHY_IMAGE], DDR_TLPHY_IMAGE_SIZE);

    return file_save(export_file_name, export_virt_addr, count);
}


/*****************************************************************************
* �� �� ��  : file_save_lcs
*
* ��������  : ���ڴ�lcs���ݱ��浽�ļ���
*
* �������  : u32 offset_addr          ����TLPHT_IMAGE��ַ��ƫ�Ƶ�ַ
*             u32 data_size            TLPHT_IMAGE��С
*
* �� �� ֵ  : s32  ����ֵ:0Ϊ�ɹ���-1Ϊʧ�ܡ�
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
long file_save_lcs(u32 offset_addr, u32 data_size)
{
    unsigned count = 0;
    unsigned export_phy_addr = 0;
    unsigned export_virt_addr = 0;
    char export_file_name[] = "lcs_data.bin"; 
    
    if(offset_addr + data_size > DDR_LCS_SIZE)
    {
	    printk("%s: parameter error.\n", __FUNCTION__);
	    return -1;
    }

    if(0 != addr_ioremap(DDR_TYPE_LCS, DDR_LCS_ADDR, DDR_LCS_SIZE))
    {
	    printk("%s: cannot map IO.\n", __FUNCTION__);
        return -1;
    }
    
    count = data_size;
    export_phy_addr = DDR_LCS_ADDR + offset_addr;
    printk("export data address is %#x, and the size is %#x.\n", \
        export_phy_addr, data_size);

    export_virt_addr = virt_addr[DDR_TYPE_LCS] + offset_addr;    
    printk("DDR_LCS_ADDR = %#x, DDR_LCS_ADDR_VIRT = %#x, DDR_LCS_SIZE = %#x.\n", \
        DDR_LCS_ADDR, virt_addr[DDR_TYPE_LCS], DDR_LCS_SIZE);

    return file_save(export_file_name, export_virt_addr, count);
}


/*****************************************************************************
* �� �� ��  : file_save_lphy_sdr
*
* ��������  : ��lphy�ڴ����ݱ��浽�ļ���
*
* �������  : u32 offset_addr          ����lphy��ַ��ƫ�Ƶ�ַ
*             u32 data_size            lphy��С
*             u32 anten_num            �������߱��
*
* �� �� ֵ  : s32  ����ֵ:0Ϊ�ɹ���-1Ϊʧ�ܡ�
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
long file_save_lphy_sdr(u32 offset_addr, u32 data_size, u32 anten_num)
{
    unsigned count = 0;
    unsigned export_phy_addr = 0;
    unsigned export_virt_addr = 0;
    char export_file_name[60] = "";
    
    if(offset_addr + data_size > DDR_LPHY_SDR_SIZE)
    {
	    printk("%s: parameter error.\n", __FUNCTION__);
	    return -1;
    }

    if(0 != addr_ioremap(DDR_TYPE_LPHY_SDR, DDR_LPHY_SDR_ADDR, DDR_LPHY_SDR_SIZE))
    {
	    printk("%s: cannot map IO.\n", __FUNCTION__);
        return -1;
    }
    
    count = data_size;
    export_phy_addr = DDR_LPHY_SDR_ADDR + offset_addr;
    snprintf(export_file_name, 60,"lphy_sdr_data_anten%d.bin", anten_num);
    printk("export data address is %#x, and the size is %#x.\n", \
        export_phy_addr, data_size);

    export_virt_addr = virt_addr[DDR_TYPE_LPHY_SDR] + offset_addr;    
    printk("DDR_LPHY_SDR_ADDR = %#x, DDR_LPHY_SDR_ADDR_VIRT = %#x, DDR_LPHY_SDR_SIZE = %#x.\n", \
        DDR_LPHY_SDR_ADDR, virt_addr[DDR_TYPE_LPHY_SDR], DDR_LPHY_SDR_SIZE);

    return file_save(export_file_name, export_virt_addr, count);
}

