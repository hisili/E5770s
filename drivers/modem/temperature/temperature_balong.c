/*
 * temperature_balong.c - hisilicon balong gpio driver
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
/*lint -save -e537*/
#include <linux/errno.h>
#include <linux/spinlock.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/slab.h>
#include <linux/power_supply.h>
#include <bsp_shared_ddr.h>

#include "osl_common.h"

#include "bsp_nvim.h"
#include "drv_nv_id.h"
#include "drv_nv_def.h"
#include "bsp_icc.h"
#include "drv_temp_cfg.h"
#include "bsp_hardtimer.h"
#include "bsp_temperature.h"
/*lint -restore */

#define TEMP_BATT_HIGH                   1
#define TEMP_BATT_LOW                    0

#define DEVICE_ID_TEMP                   10

typedef void (*TEM_FUNCPTR)(unsigned int device_id, unsigned int event_id);

TEM_FUNCPTR p_tem_fun = NULL;

s32 bsp_tem_protect_callback_register(TEM_FUNCPTR p)
{
    if(NULL == p)
    {
        tem_print_error("TEM_FUNCPTR is null.\n");
        return TEMPERATURE_ERROR;
    }

    p_tem_fun = p;

    return TEMPERATURE_OK;
}



s32 bsp_tem_data_receive(void)
{	
    int len = 0;
    unsigned status = 0;
    unsigned region = 0;
    
    struct tem_msg_stru msg = {0};
    u32 channel_id = ICC_CHN_MCORE_ACORE << 16 | MCORE_ACORE_FUNC_TEMPERATURE;

	len = bsp_icc_read(channel_id, (u8*)&msg, sizeof(struct tem_msg_stru));
	if(len != (int)sizeof(struct tem_msg_stru))
	{
		tem_print_error("read len(%x) != expected len(%x).\n", len, sizeof(struct tem_msg_stru));
		return TEMPERATURE_ERROR;
	}

    if(msg.id != channel_id)
    {
		tem_print_error("msg id(%d) != expected channel_id(%d).\n", msg.id, channel_id);
		return TEMPERATURE_ERROR;
    }

	region = msg.region;
	status = msg.status;

    tem_print_info("temperature region = %d, status = %d.\n", region, status);
    
    /*POWER_SUPPLY�����ϱ�*/
    if(HKADC_BATTERY == region && (HIGH_TEMPERATURE == status) && (NULL != p_tem_fun))
    {
        (*p_tem_fun)(DEVICE_ID_TEMP, POWER_SUPPLY_HEALTH_DEAD);
    }
    else if(HKADC_BATTERY == region && (LOW_TEMPERATURE == status) && (NULL != p_tem_fun))
    {
        (*p_tem_fun)(DEVICE_ID_TEMP, POWER_SUPPLY_HEALTH_COLD);
    }

    
    return TEMPERATURE_OK;
}

int tem_protect_nv_config(void)
{   
    unsigned int i = 0;
    unsigned int  ret = 0;
    unsigned int nv_id = 0;
    unsigned int length = 0;
    
    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)TEMPERATURE_VIRT_ADDR;  
    
    p_area->magic_start = TEMPERATURE_MAGIC_DATA;
    
    for(i = 0; i < HKADC_CHAN_MAX; i++)
    {
        nv_id = NV_ID_DRV_TEMP_HKADC_CONFIG;
        if(0 != (ret = bsp_nvm_readpart(nv_id, i*(sizeof(TEMP_HKADC_CHAN_CONFIG)), (u8*)(&(p_area->chan_cfg[i])), sizeof(TEMP_HKADC_CHAN_CONFIG))))
        {
            goto nv_hkadc_error;
        }
        
        length = p_area->chan_cfg[i].temp_data_len;
		/*lint -save -e734 -e571*/
        nv_id  = (unsigned int)(p_area->chan_cfg[i].temp_table[0].temp);
        /*lint -restore*/
        if(0 != nv_id && (0 != length))
        {
            if(0 != (ret = bsp_nvm_read(nv_id, (u8*)(p_area->chan_cfg[i].temp_table), sizeof(TEM_VOLT_TABLE) * length)))
            {
                goto nv_hkadc_error;
            }
        }
    }

    nv_id = NV_ID_DRV_TEMP_BATTERY_CONFIG;
    if(0 != (ret = bsp_nvm_read(nv_id, (u8*)(&(p_area->sys_temp_cfg)), sizeof(DRV_SYS_TEMP_STRU))))
    {
        goto nv_hkadc_error;
    }

    nv_id = NV_ID_DRV_TEMP_TSENS_CONFIG;
    if(0 != (ret = bsp_nvm_read(nv_id, (u8*)(p_area->tens_cfg), sizeof(TEMP_TSENS_REGION_CONFIG) * TSENS_REGION_MAX)))
    {
        goto nv_hkadc_error;
    }

    nv_id = NV_ID_DRV_TEMP_CHAN_MAP;
    if(0 != (ret = bsp_nvm_read(nv_id, (u8*)(p_area->phy_tbl), sizeof(BSP_U16) * HKADC_CHAN_MAX)))
    {
        goto nv_hkadc_error;
    }

    nv_id = NV_ID_DRV_TSENS_TABLE;
    if(0 != (ret = bsp_nvm_read(nv_id, (u8*)(&(p_area->region_cfg)), sizeof(TSENS_REGION_CONFIG))))
    {
        goto nv_hkadc_error;
    }

    p_area->magic_end = TEMPERATURE_MAGIC_DATA;

    return TEMPERATURE_OK;

nv_hkadc_error:
    tem_print_error("nv =0x%x read fail, ret = 0x%x, i = %d.\n", nv_id, ret, i);
    return TEMPERATURE_ERROR;
}


/*****************************************************************************
 * �� �� ��  :bsp_temperature_init
 *
 * ��������  : �¶ȱ����˼�ͨ�ţ�A�˳�ʼ������
 *
 * �������  : ��
 * �������  : ��
 *
 * �� �� ֵ  : TEMPERATURE_OK:    �����ɹ�
 *             TEMPERATURE_ERROR: ����ʧ��
 *
 * ����˵��  : ��
 *
 *****************************************************************************/
static int __init bsp_temperature_init(void)
{
    int ret = 0;
    u32 chan_id = ICC_CHN_MCORE_ACORE << 16 | MCORE_ACORE_FUNC_TEMPERATURE;

    //printk("acore tem time %d.\n", bsp_get_elapse_ms());
    
    /*��NV�����ȡ�±�������Ϣ���浽�����ڴ�*/
    if(0 != tem_protect_nv_config())
    {
        tem_print_error(" tem_protect_nv_config is fail.\n");
		return TEMPERATURE_ERROR;
    }
    
    ret = bsp_icc_event_register(chan_id, (read_cb_func)bsp_tem_data_receive, NULL, NULL, NULL);
    if(0 != ret)
    {
        tem_print_error("register is error, %d.\n", ret);
        return TEMPERATURE_ERROR;
    }
    
    tem_print_info("temperature init is ok.\n");
    
    return TEMPERATURE_OK;
}

static void __exit bsp_temperature_exit(void)
{
    tem_print_info("temperature exit is ok.\n");
}

module_init(bsp_temperature_init);
module_exit(bsp_temperature_exit);
MODULE_AUTHOR("Hisilicon Drive Group");
MODULE_DESCRIPTION("temperature driver for the Hisilicon");
MODULE_LICENSE("GPL");

