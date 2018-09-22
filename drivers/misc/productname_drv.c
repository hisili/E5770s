
/******************************���ⵥ�޸ļ�¼**********************************
    ����           �޸���       ���ⵥ��                 �޸�����

******************************************************************************/
/*lint -save -e7 -e10 -e63 -e64  -e115 -e132 -e533 -e539*/
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <product_config.h>
#include <DrvInterface.h>
#include <asm/uaccess.h>

/*�궨�� �ڵ�����*/
#define DRV_PRODUCTNAME_PROC_FILE "productname"


/*ȫ�ֱ��� �ڵ�ɲ��������ݽṹ*/
static struct proc_dir_entry *g_product_name_proc_file = NULL;

/*************************************************************************
* ������     :  drv_product_name_proc_read
* ��������   :  ��ѯ��Ʒ����
* �������   :  void
* �������   :  buffer : ���ں˽��汾�Ŵ����û�̬
* ����ֵ     :  VER_RET_OK : �����ɹ�
*               VER_RET_ERROR : ����ʧ��
**************************************************************************/
static ssize_t drv_product_name_proc_read(struct file *filp, char *buffer, size_t length, loff_t *offset)
{
    void __user *buf_usr = (void __user *)buffer;
    static size_t  len_left = 0;
    size_t  len;

    int ret = 0;
    /*��Ʒ���Ƴ���*/
    BSP_U32 name_length = 31;
    /*��Ų�Ʒ�����ַ���*/
    char product_name[40] = {0};
    
    /*��ȡ��Ʒ������Ϣ*/
    ret = BSP_GetProductInnerName(product_name, name_length);

    if (0 != ret)
    {
        pr_err("drv_product_name_proc_read : BSP_GetProductInnerName is failed.\n");
        return -1;
    }
    //strcat(product_name, "\n");

    /*��һ�ζ�ȡ*/
    if (0 == *offset)
    {
        len_left = strlen(product_name);
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
        return -1;
    }

    if(copy_to_user(buf_usr, product_name + (strlen(product_name) - len_left), len))
    {
        pr_err("%s: copy_to_user failed, nothing copied\n", __FUNCTION__);
        return -1;
    }

    *offset  += len;
    len_left -= len;

    return len;
}

/*�ڵ�Ĳ����������ݽṹ*/
static struct file_operations drv_product_name_proc_ops = {
    .read  = drv_product_name_proc_read,
};

/*************************************************************************
* ������     :  create_product_name_proc_file
* ��������   :  �����ڵ�
* �������   :  void
* �������   :  void
* ����ֵ     :  void
**************************************************************************/
static void create_product_name_proc_file(void)
{
    g_product_name_proc_file = create_proc_entry(DRV_PRODUCTNAME_PROC_FILE,
                                /*Ȩ������*/0444, NULL);
        
    if(g_product_name_proc_file)
    {
        g_product_name_proc_file->proc_fops = &drv_product_name_proc_ops;
    }
    else
    {
        pr_warning("%s: create proc entry for productname failed\n", __FUNCTION__);
    }
}

/*************************************************************************
* ������     :  remove_drv_version_proc_file
* ��������   :  ɾ���ڵ�
* �������   :  void
* �������   :  void
* ����ֵ     :  void
**************************************************************************/
static void remove_product_name_proc_file(void)
{
    remove_proc_entry(DRV_PRODUCTNAME_PROC_FILE, NULL);
}

static int __init product_name_drv_init(void)
{
    create_product_name_proc_file();
    return 0;
}

static void __exit product_name_drv_exit(void)
{
    remove_product_name_proc_file();
}

module_init(product_name_drv_init);

module_exit(product_name_drv_exit);

/*lint -restore +e7 +e10 +e63 +e64  +e115 +e132 +e533 +e539*/
