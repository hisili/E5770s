

/*******************************************************************************
  1 ͷ�ļ�����
*******************************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/debugfs.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/vmalloc.h>
#include <linux/slab.h>
#include <linux/unistd.h>
#include <linux/syscalls.h>

/*******************************************************************************
  3 ��������
*******************************************************************************/
extern unsigned long HLLT_Agent_GetCovDataSize_drivers();
extern int HLLT_Coverage_GetCoverageData_drivers(unsigned int *pCovData, unsigned long ulLen);

/*******************************************************************************
  4 ����ʵ��
*******************************************************************************/
void ltcov_hutaf_save_acore_data()
{	
	unsigned long len = 0;
	void* k_buffer=NULL;
	struct file *fd = NULL;
	int file_flag = O_RDWR | O_CREAT;
	unsigned long fs;
	int testdata[100]={0};
	int i;
	for(i=0; i<50; i++)
	{
	testdata[i]=i+1;
	}
	len = HLLT_Agent_GetCovDataSize_drivers();
	k_buffer = kmalloc(len, GFP_KERNEL);
	
	if(NULL == k_buffer)
	{
		printk("ltcov_hutaf_save_acore_data:kmalloc error\n");
		goto ERROR;
	}

	/* ������������д��Buffer�� */
	if(1 != HLLT_Coverage_GetCoverageData_drivers(k_buffer, len))
	{
		printk("ltcov_hutaf_save_acore_data:HLLT_Coverage_GetCoverageData error\n");
		goto ERROR;
	}
	
	/* �ı��ڴ�ռ����Ȩ�� */
    fs = get_fs();
    set_fs(KERNEL_DS);

	/* �����ļ� */
	fd = filp_open("/data/ltcov_acore.bin", file_flag, 0666);
    if (IS_ERR(fd))
    {
        printk("ltcov_hutaf_save_acore_data:open ltcov.bin file error\n");
        set_fs(fs);
        goto ERROR;
    }
	
	/* д�ļ� */
	vfs_write(fd, k_buffer, len, &(fd->f_pos));

    kfree(k_buffer);
    filp_close(fd, NULL);
	set_fs(fs);
	return;
	
ERROR:
    if(k_buffer) 
	{
	    kfree(k_buffer);
		k_buffer = NULL;
	}
}

/* ������������ű� */
EXPORT_SYMBOL(ltcov_hutaf_save_acore_data);

