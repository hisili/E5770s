/******************************************************************************
  File Name       : loadm.c
  Description     : load modem image(vxworks image),run in ccore
  History         :
******************************************************************************/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/mtd/mtd.h>
#include <linux/dma-mapping.h>
#include <linux/decompress/generic.h>
#include <asm/dma-mapping.h>

#include "product_config.h"
#include "loadm.h"
#include "bsp_memmap.h"
#include "ptable_com.h"
#include "hi_common.h"
#include "bsp_nandc.h"
#include <bsp_ipc.h>
#include <bsp_sec.h>
#include <soc_onchiprom.h>
#include <bsp_shared_ddr.h>


#include "bsp_sram.h"
#include "drv_chg.h"
static u32 g_ccore_entry = 0;


/*****************************************************************************
 �� �� ��  : ����ccore����
 ��������  : load partition image
 �������  : struct ST_PART_TBL *part ��Ӧ�ķ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int his_modem_load_vxworks(char *part_name)
{
    int ret = 0;
    int offset = 0;
    int skip_len = 0;
    u32 image_total_length = 0;
    void *image_load_addr = 0;
    decompress_fn inflate_fn = NULL;

    struct image_head head;

    hi_trace(HI_INFO, ">>loading:%s.....\r\n", part_name);

    ret = bsp_nand_read(part_name, (FSZ)0, &head, sizeof(struct image_head) , &skip_len);
    if (NAND_OK != ret)
    {
        hi_trace(HI_ERR, "fail to read vxworks image head, error code 0x%x\r\n", ret);
        return NAND_ERROR;
    }

    /*coverity[uninit_use_in_call] */
    if (memcmp(head.image_name, CCORE_IMAGE_NAME, sizeof(CCORE_IMAGE_NAME)))
    {
        hi_trace(HI_ERR, "vxworks image error!!.\r\n");
        return NAND_ERROR;
    }

    /*coverity[uninit_use] */
    if (head.image_length + 2 * IDIO_LEN + OEM_CA_LEN > PRODUCT_CFG_FLASH_CCORE_LEN)
    {
        hi_trace(HI_ERR, "loadsize is incorrect, 0x%x!\r\n",
            head.image_length + 2 * IDIO_LEN + OEM_CA_LEN);
        return NAND_ERROR;
    }

    /*coverity[uninit_use_in_call] */
    g_ccore_entry = (u32)ioremap_cached(head.load_addr, DDR_MCORE_SIZE - (MCORE_TEXT_START_ADDR - DDR_MCORE_ADDR));
    if(!g_ccore_entry)
    {
        hi_trace(HI_ERR, "ioremap failed.\r\n");
        return NAND_ERROR;
    }

    offset += sizeof(struct image_head) + skip_len;
    image_total_length = (u32)head.image_length + 2 * IDIO_LEN + OEM_CA_LEN;

    /*coverity[uninit_use] */
    if (head.is_compressed)
    {
        image_load_addr = (void*)g_ccore_entry - (MCORE_TEXT_START_ADDR - DDR_MCORE_ADDR)
            + DDR_MCORE_SIZE - image_total_length;
    }
    else
    {
        image_load_addr = (void*)g_ccore_entry;
    }

    ret = bsp_nand_read(part_name, offset, image_load_addr, image_total_length, &skip_len);
    if(NAND_OK != ret)
    {
        hi_trace(HI_ERR, "fail to read vxworks image, error code 0x%x\r\n", ret);
        goto exit;
    }

    ret = bsp_sec_check((u32)image_load_addr, head.image_length);
    if (ret)
    {
        hi_trace(HI_ERR, "fail to check vxworks image, error code 0x%x\r\n", ret);
        goto exit;
    }

    if (head.is_compressed)
    {
        hi_trace(HI_INFO, ">>start to decompress vxworks image ...\r\n");
        inflate_fn = decompress_method((const unsigned char *)image_load_addr, 2, NULL);
        if (inflate_fn)
        {
            ret = inflate_fn((unsigned char*)image_load_addr,
                head.image_length, NULL, NULL, (unsigned char*)g_ccore_entry,
                NULL, (void(*)(char*))printk);
            if (ret)
            {
                hi_trace(HI_ERR, "fail to decompress vxworks image, error code 0x%x\r\n", ret);
                goto exit;
            }
        }
        else
        {
            hi_trace(HI_ERR, "fail to get decompress method\r\n");
            goto exit;
        }
    }

    /* flush cache */
    __dma_single_cpu_to_dev_noverify((const void *)g_ccore_entry,
                     DDR_MCORE_SIZE - (MCORE_TEXT_START_ADDR - DDR_MCORE_ADDR),
                     CACHE_DMA_TO_DEVICE);

    hi_trace(HI_INFO, ">>load vxworks ok, entey %#x, length %#x\r\n", head.load_addr, head.image_length);

exit:
    iounmap((void volatile *)g_ccore_entry);

    return ret;
}


int g_debug_level = HI_INFO;

static struct platform_device his_modem_device = {
    .name = "his_modem",
    .id = 0,
    .dev = {
    .init_name = "his_modem",
    },
};

static ssize_t log_level_set(struct device *dev, struct device_attribute *attr,
                               const char *buf, size_t count)
{
    int status = count;
    int val = 0;

    if ((kstrtoint(buf, 10, &val) < 0))
        return -EINVAL;

    g_debug_level = val;

    hi_trace(HI_DEBUG, "log_level_set 0x%x \r\n", (unsigned int)val);

    return status;
}

static ssize_t log_level_get(struct device *dev, struct device_attribute *attr,
                               char *buf)
{
    int val = 0;

    val = g_debug_level ;
    hi_trace(HI_DEBUG, "log_level_get \r\n");

    return snprintf(buf, sizeof(val), "%d\n", val);
}

static ssize_t modem_entry_store(struct device *dev, struct device_attribute *attr,
                                       const char *buf, size_t count)
{
    int status = count;
    long val = 0;

    if ((strict_strtol(buf, 10, &val) < 0))
        return -EINVAL;

    /* ccore_entry_addr = val; */
    hi_trace(HI_DEBUG, "modem_entry_store 0x%x \r\n", (unsigned int)val);

    return status;
}

static ssize_t modem_entry_show(struct device *dev, struct device_attribute *attr,
                                        char *buf)
{
    unsigned long val = 0;

    val = g_ccore_entry ;
    hi_trace(HI_DEBUG, "modem_entry_show \r\n");

    return snprintf(buf, sizeof(val), "%lu\n", val);
}

static DEVICE_ATTR(log_level, S_IWUSR | S_IRUGO,
                                    log_level_get,
                                    log_level_set);

static DEVICE_ATTR(entry_addr, S_IWUSR | S_IRUGO,
                                    modem_entry_show,
                                    modem_entry_store);

static struct attribute *his_modem_attributes[] = {
        &dev_attr_log_level.attr,
        &dev_attr_entry_addr.attr,
        NULL
};

static const struct attribute_group his_modem_group = {
    .attrs = his_modem_attributes,
};


int his_modem_ipc_send(void)
{
    int ret = 0;

    ret = bsp_ipc_int_send(IPC_CORE_MCORE, IPC_MCU_INT_SRC_CCPU_START);

    return ret;
}

static int __init his_modem_probe(struct platform_device *pdev)
{
    int ret = 0;
    struct ST_PART_TBL * mc_part = NULL;

    hi_trace(HI_DEBUG, "his_modem_probe.\r\n");

    mc_part = find_partition_by_name(PTABLE_VXWORKS_NM);
    if(NULL == mc_part)
    {
        hi_trace(HI_ERR, "load ccore image succeed\r\n");
        return -EAGAIN;
    }

    if(NAND_OK == his_modem_load_vxworks(mc_part->name))
    {
        hi_trace(HI_DEBUG, "load ccore image succeed\r\n");
    }
    else
    {
        hi_trace(HI_ERR, "load ccore image failed\r\n");
        return -EAGAIN;
    }

    ret = sysfs_create_group(&pdev->dev.kobj, &his_modem_group);
    if (0 != ret)
    {
        hi_trace(HI_ERR,"create his modem sys filesystem node failed.\n");
        return -ENXIO;
    }


    ret = his_modem_ipc_send();
    if (ret)
    {
        hi_trace(HI_ERR, "load ccore image failed, ret=0x%x\r\n", ret);
    }
    else
    {
        hi_trace(HI_ERR, "load ccore image succeed\r\n");
    }

    return ret;

}

static int his_modem_resume(struct platform_device *dev)
{
    return 0;
}

static void his_modem_shutdown(struct platform_device *dev)
{
    return;
}

static int his_modem_suspend(struct platform_device *dev, pm_message_t state)
{
    return 0;
}

static int his_modem_remove(struct platform_device *dev)
{
    return 0;
}

static struct platform_driver his_modem_drv = {
    .probe      = his_modem_probe,
    .remove     = his_modem_remove,
    .suspend    = his_modem_suspend,
    .resume     = his_modem_resume,
    .shutdown   = his_modem_shutdown,
    .driver     = {
        .name     = "his_modem",
        .owner    = THIS_MODULE,
    },
};

static int __init his_modem_init_driver(void)
{
    int ret = 0;
    huawei_smem_info *smem_data = NULL;
    smem_data = (huawei_smem_info *)SRAM_DLOAD_ADDR;
    
    if (NULL == smem_data)
    {
        hi_trace(HI_ERR,"Dload smem_data malloc fail!\n");
        return -1;
    }

    if(SMEM_DLOAD_FLAG_NUM == smem_data->smem_dload_flag)
    {
        return ret;
    }

    hi_trace(HI_DEBUG, "his_modem_init_driver.\r\n");

    ret = platform_device_register(&his_modem_device);
    if(ret)
    {
        hi_trace(HI_ERR, "register his_modem device failed\r\n");
        return ret;
    }

    ret = platform_driver_register(&his_modem_drv);
    if(ret)
    {
        hi_trace(HI_ERR, "register his_modem driver failed\r\n");
        platform_device_unregister(&his_modem_device);
    }


    return ret;

}

static void __exit his_modem_exit_driver(void)
{
    huawei_smem_info *smem_data = NULL;
    smem_data = (huawei_smem_info *)SRAM_DLOAD_ADDR;
    
    if (NULL == smem_data)
    {
        hi_trace(HI_ERR,"Dload smem_data malloc fail!\n");
        return -1;
    }

    if(SMEM_DLOAD_FLAG_NUM != smem_data->smem_dload_flag)
    {
        platform_driver_unregister(&his_modem_drv);
        platform_device_unregister(&his_modem_device);
    }
}

/* arch_initcall(his_modem_init_driver);*/
module_init(his_modem_init_driver);
module_exit(his_modem_exit_driver);

MODULE_AUTHOR("x00181146@huawei.com");
MODULE_DESCRIPTION("HIS Balong V7R2 Modem load ");
MODULE_LICENSE("GPL");

