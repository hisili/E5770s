

/* ͷ�ļ����� */
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <product_config.h>
#include <DrvInterface.h>
#include <asm/uaccess.h>
#include "vsim.h"

/*ȫ�ֱ��� �ڵ�ɲ��������ݽṹ*/
static struct proc_dir_entry *g_vsim_proc_file = NULL;

/*************************************************************************
* ��������   :  drv_vsim_proc_read
* ��������   :  ��ȡ�����ڴ�vsim����
* �������   :  filp--�ļ�ָ�룬buffer--��������
                                length--��ȡ�ĳ��ȣ�offset--��ȡƫ����
* �������   :  buffer : ���ں˽�����״̬�����û�̬
* ����ֵ         :  0 | len : �����ɹ�
*                              -1: ����ʧ��
**************************************************************************/
static ssize_t drv_vsim_proc_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    void __user *buf_usr = (void __user *)buffer;

    int ret = -1,mode = 0;
    TAF_VSIM_DATA_AREA *p_area = (TAF_VSIM_DATA_AREA *)SHM_MEM_VSIM_DATA_ADDR;

    printk(KERN_ERR "vsim ddr data:\n");
    printk(KERN_ERR "p_area->magic_start = 0x%x\n", p_area->magic_start);
    printk(KERN_ERR "p_area->EventType = 0x%x\n", p_area->EventType);
    printk(KERN_ERR "sizeof(p_area) = %d\n", sizeof(TAF_VSIM_DATA_AREA));


    ret = copy_to_user(buf_usr, (void *)p_area, sizeof(TAF_VSIM_DATA_AREA));

    if(0 != ret)
    {
        printk(KERN_ERR "\r\n [drv_vsim_proc_read]copy_to_user fail!\r\n");
    }

    memset(p_area, 0x0, sizeof(TAF_VSIM_DATA_AREA));

    return ret;
}

/* vsim�����ڴ�ڵ�Ĳ����������ݽṹ*/
static struct file_operations drv_vsim_proc_ops = 
{
    .read  = drv_vsim_proc_read,
};

/*************************************************************************
* ������         :  create_vsim_proc_file
* ��������   :  �����ڵ�
* �������   :  void
* �������   :  void
* ����ֵ         :  void
**************************************************************************/
static void create_vsim_proc_file(void)
{
    /* ����Ȩ�� */
    g_vsim_proc_file = create_proc_entry(DRV_VSIM_PROC_FILE, 0444, NULL);
        
    if(g_vsim_proc_file)
    {
        g_vsim_proc_file->proc_fops = &drv_vsim_proc_ops;
    }
    else
    {
        pr_warning("%s: create proc entry for vsim failed\n", __FUNCTION__);
    }
}

/*************************************************************************
* ������         :  remove_vsim_proc_file
* ��������   :  ɾ���ڵ�
* �������   :  void
* �������   :  void
* ����ֵ        :  void
**************************************************************************/
static void remove_vsim_proc_file(void)
{
    remove_proc_entry(DRV_VSIM_PROC_FILE, NULL);
}

static int __init vsim_drv_init(void)
{
    create_vsim_proc_file();
    return 0;
}

static void __exit vsim_drv_exit(void)
{
    remove_vsim_proc_file();
}

module_init(vsim_drv_init);

module_exit(vsim_drv_exit);
