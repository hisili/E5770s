#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>
#include <asm/system.h>
#include <asm/setup.h>
#include <linux/string.h>
#include <linux/init.h>
#include <mach/io.h>
#include "drv_onoff.h"

#define HEX_STRING_MAX          (10)
#define TRANSFER_BASE           (16)

static unsigned int pd_charge_flag = NORMAL_CHARGING_MODE;
static unsigned int reset_mode_flag = NORMAL_RESET_FLAG;
static unsigned int soft_ver_type = NORMAL_VERTYPE_FLAG;
static unsigned int soft_run_mode = RUN_MODE_NORMAL;

/*****************************************************************************
 �� �� ��  : early_parse_pdcharge_cmdline
 ��������  : parse powerdown charge cmdline which is configured in fastboot
 �������  : char *p
 �������  : ��
 �� �� ֵ  : ok/error
 ���ú���  : pd_charge=0 or 1    1:pw charge 0:normal charge
 ��������  :
*****************************************************************************/
static int __init early_parse_pdcharge_cmdline(char * p)
{
	char pd_charge[HEX_STRING_MAX + 1];
	char *endptr = NULL;

	memset(pd_charge, 0, HEX_STRING_MAX + 1);

	memcpy(pd_charge, p, HEX_STRING_MAX);
	pd_charge[HEX_STRING_MAX] = '\0';

	pd_charge_flag = simple_strtoull(pd_charge, &endptr, TRANSFER_BASE);

	printk("power down charge p:%s, pd_charge_flag :%d\n", p, pd_charge_flag);

	return 0;
}
early_param("pd_charge", early_parse_pdcharge_cmdline);

/*****************************************************************************
 �� �� ��  : get_pd_charge_flag
 ��������  : �Ƿ�Ϊ���������汾
 �������  : ��
 �������  : ��
 �� �� ֵ  : DRV_CHARGING_MODE �汾����
 ���ú���  : 
 ��������  :
*****************************************************************************/	
DRV_CHARGING_MODE get_pd_charge_flag(void)
{
    if(pd_charge_flag >= INVALID_CHARGING_MODE){
        printk("invalid charging mode \n");
        return NORMAL_CHARGING_MODE;
    }
    
	return pd_charge_flag;
}
EXPORT_SYMBOL(get_pd_charge_flag);

/*****************************************************************************
 �� �� ��  : early_parse_softver_cmdline
 ��������  : parse runmode cmdline which is configured in fastboot.
 �������  : char *p
 �������  : ��
 �� �� ֵ  : ok/error
 ���ú���  : swtype=0 or 1  1:factory 0:normal version
 ��������  :
*****************************************************************************/
static int __init early_parse_softver_cmdline(char * p)
{
	if(p){
        if (!strcmp(p,"factory"))
        	soft_ver_type = FACTORY_VERTYPE_FLAG;

        printk("softver is %s, softver_factory = %d\n", p, soft_ver_type);
	}

	return 0;
}
early_param("androidboot.swtype", early_parse_softver_cmdline);

/*****************************************************************************
 �� �� ��  : ver_type_is_factory
 ��������  : �ж��Ƿ�Ϊ�����汾
 �������  : ��
 �������  : ��
 �� �� ֵ  : DRV_SOFT_VER_TYPE �汾����
 ���ú���  : 
 ��������  :
*****************************************************************************/	
DRV_SOFT_VER_TYPE get_version_type(void)
{
    if(soft_ver_type >= INVALID_VERTYPE_FLAG){
        printk("running version is invalid\n");
        return INVALID_VERTYPE_FLAG;
    }
    
	return soft_ver_type;
}
EXPORT_SYMBOL(get_version_type);

/*****************************************************************************
 �� �� ��  : early_parse_reset_cmdline
 ��������  : parse runmode cmdline which is configured in fastboot.
 �������  : char *p
 �������  : ��
 �� �� ֵ  : ok/error
 ���ú���  : reset_type=0 or 1  1:abnormal reset 0:normal reset
 ��������  :
*****************************************************************************/
static int __init early_parse_reset_cmdline(char * p)
{
	if(p){
        if (!strcmp(p,"normal")){
        	reset_mode_flag = NORMAL_RESET_FLAG;
        }
        else if(!strcmp(p,"abnormal")){
        	reset_mode_flag = ABNORMAL_RESET_FLAG;
        }
        
        printk("reset type is %s, reset_mode_flag = %d\n", p, reset_mode_flag);
	}

	return 0;
}
early_param("reset_type", early_parse_reset_cmdline);

/*****************************************************************************
 �� �� ��  : get_reset_reason
 ��������  : �ж��Ƿ�Ϊ�쳣��λ
 �������  : ��
 �������  : ��
 �� �� ֵ  : DRV_RESET_TYPE ��λ����
 ���ú���  : 
 ��������  :
*****************************************************************************/
DRV_RESET_TYPE get_reset_reason(void)
{
    if(reset_mode_flag >= INVALID_RESET_FLAG){
        printk("invalid reset flag\n");
        return NORMAL_RESET_FLAG;
    }
    
	return reset_mode_flag;
}
EXPORT_SYMBOL(get_reset_reason);

/*****************************************************************************
 �� �� ��  : early_parse_pwmode_cmdline
 ��������  : parse runmode cmdline which is configured in fastboot.
 �������  : char *p
 �������  : ��
 �� �� ֵ  : ok/error
 ���ú���  : power_mode=0 or 1  0:normal 1:recovery
 ��������  :
*****************************************************************************/
static int __init early_parse_pwmode_cmdline(char * p)
{
	if(p){
        if (!strcmp(p,"recovery")){
        	soft_run_mode = RUN_MODE_RECOVERY;
        }
        else if(!strcmp(p,"normal")){
        	soft_run_mode = RUN_MODE_NORMAL;
        }
        else{
        	soft_run_mode = RUN_MODE_INVALID;
        }
        
        printk("run mode is %s, soft_run_mode = %d\n", p, soft_run_mode);
	}

	return 0;
}
early_param("power_mode", early_parse_pwmode_cmdline);

/*****************************************************************************
 �� �� ��  : get_run_mode
 ��������  : �ж��Ƿ�Ϊ�쳣��λ
 �������  : ��
 �������  : ��
 �� �� ֵ  : DRV_RESET_TYPE ��λ����
 ���ú���  : 
 ��������  :
*****************************************************************************/
DRV_RUN_MODE get_run_mode(void)
{
    if(soft_run_mode >= RUN_MODE_INVALID){
        printk("invalid reset flag\n");
        return RUN_MODE_NORMAL;
    }
    
	return soft_run_mode;
}
EXPORT_SYMBOL(get_run_mode);


