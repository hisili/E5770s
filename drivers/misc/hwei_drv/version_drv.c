

#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <product_config.h>
#include <DrvInterface.h>
#include <asm/uaccess.h>

/*�궨�� �ڵ�����*/
#define DRV_MHWVER_PROC_FILE "mhwver"
#define DRV_MSWVER_PROC_FILE "mswver"

#define VER_RET_OK            0
#define VER_RET_ERROR       - 1

/*ȫ�ֱ��� �ڵ�ɲ��������ݽṹ*/
static struct proc_dir_entry *g_drv_mhwver_proc_file = NULL;
static struct proc_dir_entry *g_drv_mswver_proc_file = NULL;

/*************************************************************************
* ������     :  drv_mhwver_proc_read
* ��������   :  modem��Ӳ���汾�Ų�ѯ
* �������   :  void
* �������   :  buffer : ���ں˽��汾�Ŵ����û�̬
* ����ֵ     :  VER_RET_OK : �����ɹ�
*               VER_RET_ERROR : ����ʧ��
**************************************************************************/
static ssize_t drv_mhwver_proc_read(struct file *filp,
                char *buffer, size_t length, loff_t *offset)
{
    void __user *buf_usr = (void __user *)buffer;
    static size_t  len_left = 0;
    size_t  len;

    int ret = 0;
    /*�汾�ų���*/
    BSP_U32 mhwver_length = 31;
    /*��Ű汾���ַ���*/
    char mhwver_version[40] = {0};
    
    /*��ȡ�汾����Ϣ*/
    ret = BSP_HwGetHwVersion(mhwver_version, mhwver_length);
    if (0 != ret)
    {
        pr_err("drv_mhwver_proc_read : BSP_HwGetHwVersion is failed.\n");
        return VER_RET_ERROR;
    }
    strcat(mhwver_version, "\n");
    
    /*��һ�ζ�ȡ*/
    if (0 == *offset)
    {
        len_left = strlen(mhwver_version);
    }
    len      = (length > len_left) ? (len_left) : length;
    /*��ȡ���*/
    if(len_left == 0)
    {
        return 0;
    }

    if (!access_ok(VERIFY_WRITE, buf_usr, len))
    {
        pr_err("%s: Verify user buffer write fail.\n", __FUNCTION__);
        return - EFAULT;
    }

    if(copy_to_user(buf_usr, mhwver_version + (strlen(mhwver_version) - len_left), len))
    {
        pr_err("%s: copy_to_user failed, nothing copied\n", __FUNCTION__);
        return - EFAULT;
    }

    *offset  += len;
    len_left -= len;
    return len;
}

/*************************************************************************
* ������     :  drv_mswver_proc_read
* ��������   :  router������汾�Ų�ѯ
* �������   :  void
* �������   :  buffer : ���ں˽��汾�Ŵ����û�̬
* ����ֵ     :  VER_RET_OK : �����ɹ�
*               VER_RET_ERROR : ����ʧ��
**************************************************************************/
static ssize_t drv_mswver_proc_read(struct file *filp,
                char *buffer, size_t length, loff_t *offset)
{
    void __user *buf_usr = (void __user *)buffer;
    static size_t  len_left = 0;
    size_t  len;
    /*��Ű汾���ַ���*/
    char mswver_version[25] = {0};
    
    /*�Ӻ궨����ȡ�汾��*/
    strncpy(mswver_version, PRODUCT_CFG_MODEM_SOFTWARE_VER, 15);
    strcat(mswver_version, "\n");
    
    /*��һ�ζ�ȡ*/
    if (0 == *offset)
    {
        len_left = strlen(mswver_version);
    }
    len      = (length > len_left) ? (len_left) : length;
    /*��ȡ���*/
    if(len_left == 0)
    {
        return 0;
    }

    if (!access_ok(VERIFY_WRITE, buf_usr, len))
    {
        pr_err("%s: Verify user buffer write fail.\n", __FUNCTION__);
        return - EFAULT;
    }

    if(copy_to_user(buf_usr, mswver_version + (strlen(mswver_version) - len_left), len))
    {
        pr_err("%s: copy_to_user failed, nothing copied\n", __FUNCTION__);
        return - EFAULT;
    }

    *offset  += len;
    len_left -= len;

    return len;
}

/*�ڵ�Ĳ����������ݽṹ*/
static struct file_operations drv_mhwver_proc_ops = {
    .read  = drv_mhwver_proc_read,
};
static struct file_operations drv_mswver_proc_ops = {
    .read  = drv_mswver_proc_read,
};

/*************************************************************************
* ������     :  create_drv_version_proc_file
* ��������   :  �����ڵ�
* �������   :  void
* �������   :  void
* ����ֵ     :  void
**************************************************************************/
static void create_drv_version_proc_file(void)
{
    g_drv_mhwver_proc_file = create_proc_entry(DRV_MHWVER_PROC_FILE,
                                /*Ȩ������*/0444, NULL);
        
    if(g_drv_mhwver_proc_file)
    {
        g_drv_mhwver_proc_file->proc_fops = &drv_mhwver_proc_ops;
    }
    else
    {
        pr_warning("%s: create proc entry for mhwver_version failed\n",
            DRV_MHWVER_PROC_FILE);
    }
    
    g_drv_mswver_proc_file = create_proc_entry(DRV_MSWVER_PROC_FILE,
                                /*Ȩ������*/0444, NULL);
        
    if(g_drv_mswver_proc_file)
    {
        g_drv_mswver_proc_file->proc_fops = &drv_mswver_proc_ops;
    }
    else
    {
        pr_warning("%s: create proc entry for mswver_version failed\n",
            DRV_MSWVER_PROC_FILE);
    }
}

/*************************************************************************
* ������     :  remove_drv_version_proc_file
* ��������   :  ɾ���ڵ�
* �������   :  void
* �������   :  void
* ����ֵ     :  void
**************************************************************************/
static void remove_drv_version_proc_file(void)
{
#if 0
    extern struct proc_dir_entry proc_root_mhwver;
    extern struct proc_dir_entry proc_root_mswver;
    
    remove_proc_entry(DRV_MHWVER_PROC_FILE, &proc_root_mhwver);
    remove_proc_entry(DRV_MSWVER_PROC_FILE, &proc_root_mswver);
#endif	
}

static int __init version_drv_init(void)
{
    create_drv_version_proc_file();
    return 0;
}

static void __exit version_drv_exit(void)
{
    remove_drv_version_proc_file();
}

module_init(version_drv_init);
module_exit(version_drv_exit);