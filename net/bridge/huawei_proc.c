
#include "huawei_proc.h"

#define MAX_MSG_LENGTH 128      /*�������ݰ���󳤶�*/    
static char msg[MAX_MSG_LENGTH];
int g_ssid2_pdev = -1;   /*��ʼ��Ϊ-1����ȡ�ļ�/proc/wifinet/ssid2�е�ֵ��������g_ssid2_pdev*/

static struct proc_dir_entry *root_entry = NULL;
static struct proc_dir_entry *subroot_entry = NULL;

static int g_wifi_proc_inited = 0;

/*�ַ���������ת��*/
typedef unsigned int dsat_num_item_type;
typedef  unsigned char      byte;  
typedef enum
{                       
  ATOI_OK,              /*  conversion complete             */
  ATOI_NO_ARG,          /*  nothing to convert              */
  ATOI_OUT_OF_RANGE     /*  character or value out of range */
} atoi_enum_type;
#define MAX_VAL_NUM_ITEM 0xFFFFFFFF /*  Max value of a numeric AT parm     */
#define  UPCASE( c ) ( ((c) >= 'a' && (c) <= 'z') ? ((c) - 0x20) : (c) )
#define DEC 10
/*****************************************************************************
 �� �� ��  : huawei_atoi
 ��������  : ʵ���ַ���������ת��Ϊ����
 �������  : val_arg_ptr ----- ָ�����ڴ洢ת�����
             s----- ԭʼ���ַ���
             r------����
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��


�޸�����   : �����ɺ���

*****************************************************************************/
atoi_enum_type huawei_atoi
(
    dsat_num_item_type *val_arg_ptr,     
    const byte *s,     
    unsigned int r    
)
{
    atoi_enum_type err_ret = ATOI_NO_ARG;
    byte c;
    dsat_num_item_type val, val_lim, dig_lim;
    
    val = 0;
    val_lim = (dsat_num_item_type) ((unsigned int)MAX_VAL_NUM_ITEM / r);
    dig_lim = (dsat_num_item_type) ((unsigned int)MAX_VAL_NUM_ITEM % r);

    while ( (c = *s++) != '\0')
    {
        if (c != ' ')
        {
            c = (byte) UPCASE (c);
            if (c >= '0' && c <= '9')
            {
                c -= '0';
            }
            else if (c >= 'A')
            {
                c -= 'A' - DEC;
            }
            else
            {
                err_ret = ATOI_OUT_OF_RANGE;  /*  char code too small */
                break;
            }
        
            if (c >= r || val > val_lim
                    || (val == val_lim && c > dig_lim))
            {
                err_ret = ATOI_OUT_OF_RANGE;  /*  char code too large */
                break;
            }
            else
            {
                err_ret = ATOI_OK;            /*  arg found: OK so far*/
                val = (dsat_num_item_type) (val * r + c);
            }
        }
        *val_arg_ptr =  val;
    }
  
    return err_ret;

}

/*****************************************************************************
 �� �� ��  : wifinet_read
 ��������  : ssid2�ļ����ں˿ռ����ݵ��û��ռ�
 �������  : page ----- ����д���λ��
             start----- 
             off------
             count-----����д�������ֽ���
             eof------�ļ���������
             data------˽������ָ��
 �������  : 
 �� �� ֵ  : 


�޸�����   : �����ɺ���

*****************************************************************************/
static int wifinet_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
    int len = strlen(msg);

    if (off >= len)
    {
        return 0;
    }

    if (count > len - off)
    {
        count = len - off;
    }

    memcpy(page + off, msg + off, count);      /*��ȡ�ں����ݵ��û��ռ�*/
    return off + count;
}
/*****************************************************************************
 �� �� ��  : wifinet_write
 ��������  : ��ssid2д����
 �������  : file ----- �򿪵��ļ��ṹ
             buffer----- ���ݵ��ַ�������
             len------buffer������д��Ķ���
             data------ָ��˽�����ݵ�ָ��
 �������  : 
 �� �� ֵ  : 
 �޸�����   : �����ɺ���
*****************************************************************************/

static int wifinet_write(struct file *file, const char __user *buffer, unsigned long len, void *data)
{

    if (len >= MAX_MSG_LENGTH) 
    {
        //printk("wifinet_write: len(%d) is large!\n",len);
        return -ENOSPC;
    }

    if (copy_from_user(msg, buffer, len ))        
    {
        printk("wifinet_write: copy_from_user error!\n");
        return -EFAULT;
    }

    msg[len] = '\0';

    huawei_atoi(&g_ssid2_pdev, msg, 10);   /*msg��ָ����ַ���ת��Ϊ10����������g_ssid2_pdev��
										��Daemon_Enable_SSID2_Access������SSID2_Ifx��ֵ���Ʊ���һ��*/

    return len;
}
/*****************************************************************************
 �� �� ��  : wifiproc_init
 ��������  : ����/proc/wifinet/ssid2�ļ���ע����ļ���д����
 �������  : ��
 �������  : ��
 �� �� ֵ  : 
 �޸�����  : �����ɺ���
*****************************************************************************/
int wifiproc_init(void)
{
    int error = 0;
    struct path proc_path;

    if(1 == g_wifi_proc_inited)
    {
        return 0;
    }
    g_wifi_proc_inited = 1;
	
    error = kern_path("/proc/wifinet", LOOKUP_FOLLOW, &proc_path);
    if (error)
    {
        printk(KERN_DEBUG "kern_path /proc/wifinet don't exist !\n");
        root_entry = proc_mkdir("wifinet", NULL);
        if (NULL == root_entry) 
        {
            printk(KERN_ERR "Can't create /proc/wifinet !\n");
            return -1;
        }
    }
    else
    {
        printk(KERN_DEBUG "kern_path /proc/wifinet  exist !\n");
    }

    error = kern_path("/proc/wifinet/ssid2", LOOKUP_FOLLOW, &proc_path);
    if (error)
    {
        printk(KERN_DEBUG "kern_path /proc/wifinet/ssid2 don't exist !\n");

        if (NULL != root_entry)
        {
            /*����/proc/wifinet/ssid2�ļ���ʵ���û��ռ���ں˿ռ�����ݽ���*/
            subroot_entry = create_proc_entry("ssid2", 0666, root_entry); 
        }

        if (NULL != subroot_entry) 
        {
            subroot_entry->read_proc = wifinet_read;
            subroot_entry->write_proc = wifinet_write;
            return 0;
        }
        else
        {
            printk(KERN_ERR "Can't create /proc/wifinet/ssid2!\n");
            remove_proc_entry("wifinet", NULL);
            return -1;
        
        }
    }
    else
    {
        printk(KERN_DEBUG "kern_path /proc/wifinet/ssid2  exist !\n");
        return -1;
    }
       
}
/*****************************************************************************
 �� �� ��  : wifiproc_exit
 ��������  : ɾȥ/proc/wifinet/ssid2�ļ���/proc/wifinet/Ŀ¼
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 �޸�����  : �����ɺ���
*****************************************************************************/

void wifiproc_exit(void)
{
    remove_proc_entry("ssid2", root_entry);
    remove_proc_entry("wifinet", NULL);
    g_wifi_proc_inited = 0;
}


