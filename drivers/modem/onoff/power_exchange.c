/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2011, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: power_exchange.c                                                */
/*                                                                           */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2013-5-3                                                            */
/*                                                                           */
/* Description: power on information exchange managerment                    */
/*              with misc and sram                                           */
/*                                                                           */
/* Others:                                                                   */
/*****************************************************************************/
#include <hi_onoff.h>
/*lint --e{537} */
#include <linux/kernel.h>
#include "bsp_sram.h"
#include "drv_onoff.h"
#include "power_com.h"
#include "power_exchange.h"
#include "power_inner.h"
#include "bsp_nandc.h"

/*****************************************************************************
 �� �� ��  : mtd_partation_exist
 ��������  : check mtd partition whether exist,
           
 �������  : ������
 �������  : ��
 �� �� ֵ  : 1:exist   0:not exist
 ���ú���  :
 ��������  :
*****************************************************************************/
int mtd_partation_exist(char *partition_name)
{
    int rt;
    rt = bsp_nand_mtd_partition_exist(partition_name);
    return rt;
}

/*****************************************************************************
 �� �� ��  : clear_misc_message
 ��������  : clear boot message in normal mode,
           : clear misc when exit recovery mode
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int clear_misc_message(void)
{
	char* str_misc = "misc";
	int rt;

    rt = bsp_nand_erase(str_misc, 0);

    return rt;
}

/*****************************************************************************
 �� �� ��  : power_on_normal_status_set
 ��������  : ����A�˿���״̬
 �������  : 
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  : 
 ��������  :
*****************************************************************************/
void power_on_acore_state_set(a_kernel_st_e state)
{
    power_info_s *pw_st = (power_info_s *)(SRAM_REBOOT_ADDR);

    pw_st->a_power_state = state;    
}

/*****************************************************************************
 �� �� ��  : power_on_normal_status_set
 ��������  : ��ȡA�˿���״̬
 �������  : 
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  : 
 ��������  :
*****************************************************************************/
a_kernel_st_e power_on_acore_state_get()
{
    power_info_s *pw_st = (power_info_s *)(SRAM_REBOOT_ADDR);

    return pw_st->a_power_state;    
}

/*****************************************************************************
 �� �� ��  : power_on_wdt_cnt_set
 ��������  : �������λ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
void power_on_wdt_cnt_set( void )
{
    power_info_s * power_info = (power_info_s *)(SRAM_REBOOT_ADDR);
    
    power_info->wdg_rst_cnt = 0;     
    power_on_acore_state_set(POWER_NORMAL);
} 

/*****************************************************************************
 �� �� ��  : power_on_wdt_cnt_get
 ��������  : ��ȡ����λ����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int power_on_wdt_cnt_get( void )
{
    power_info_s * power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    return power_info->wdg_rst_cnt;
}

/*****************************************************************************
 �� �� ��  : power_on_reboot_flag_set
 ��������  : ����������־
 �������  : power_off_reboot_flag ����ԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
void power_on_reboot_flag_set( power_off_reboot_flag enFlag )
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    power_info->last_shut_reason = (unsigned int)(enFlag);

    pr_dbg( "#########  power_on_reboot_flag_set = 0x%08X ######## \r\n", (unsigned int)enFlag);
}

/*****************************************************************************
 �� �� ��  : power_on_reboot_flag_get
 ��������  : ��ȡ����ԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : power_off_reboot_flag ����ԭ��
 ���ú���  :
 ��������  :
*****************************************************************************/
power_off_reboot_flag power_on_reboot_flag_get( void )
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    pr_dbg( "#########  power_on_reboot_flag_get = 0x%08X ######## \r\n", power_info->last_shut_reason );
    return (power_off_reboot_flag)power_info->last_shut_reason;
}

/*****************************************************************************
 �� �� ��  : power_on_start_reason_set
 ��������  : ���ÿ���ԭ��
 �������  : power_on_start_reason ����ԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
void power_on_start_reason_set( power_on_start_reason enReason )
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    power_info->power_on_reason = (unsigned int)(enReason);

    pr_dbg( "#########  power_on_start_reason_set = 0x%08X ######## \r\n", enReason );
}

/*****************************************************************************
 �� �� ��  : power_on_start_reason_get
 ��������  : ��ȡ����ԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : power_on_start_reason ����ԭ��
 ���ú���  :
 ��������  :
*****************************************************************************/
power_on_start_reason power_on_start_reason_get( void )
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    pr_dbg("#########  power_on_start_reason_get = 0x%08X ######## \r\n", power_info->power_on_reason );
    return (power_on_start_reason)(power_info->power_on_reason);
}

/*****************************************************************************
 �� �� ��  : power_on_start_reason_set
 ��������  : ���ÿ���ԭ��
 �������  : power_on_start_reason ����ԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
void power_reboot_cmd_set( power_reboot_cmd cmd )
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    power_info->reboot_cmd = (unsigned int)(cmd);

    pr_dbg( "#########  power_reboot_cmd_set = 0x%08X ######## \r\n", cmd );
}

/*****************************************************************************
 �� �� ��  : power_on_c_status_get
 ��������  : ��ȡC��״̬
 �������  : power_on_c_status_get ����ԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
c_power_st_e power_on_c_status_get(void)
{
    power_info_s *power_info = (power_info_s *)(SRAM_REBOOT_ADDR);

    pr_dbg( "#########  power_on_c_status_get = 0x%08X ######## \r\n", power_info->c_power_state );

    return (c_power_st_e)(power_info->c_power_state);

}

/*****************************************************************************
 �� �� ��  : print_exchange_addr
 ��������  : ��ӡsram������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
void print_exchange_addr( void )
{
    unsigned int * ulPtr = (unsigned int *)(SRAM_REBOOT_ADDR);

    pr_dbg("############ (Linux) Addr = 0x%08X \r\n    0x00 = 0x%08X, 0x04 = 0x%08X, 0x08 = 0x%08X, 0x0C = 0x%08X\r\n",
         SRAM_REBOOT_ADDR, *(ulPtr+0), *(ulPtr+1), *(ulPtr+2), *(ulPtr+3));
}

