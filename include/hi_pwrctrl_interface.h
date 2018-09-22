/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_syssc_interface.h */
/* Version       : 2.0 */
/* Created       : 2013-04-18*/
/* Last Modified : */
/* Description   : */
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/
#ifndef __HI_PWRCTRL_INTER_H__
#define __HI_PWRCTRL_INTER_H__

#include "hi_base.h"
#include "hi_pwrctrl.h"
#include "hi_syscrg.h"
#include "soc_timer.h"

#define REGULATOR_V711_MTCMOS
#ifndef REGULATOR_FASTBOOT_MTCMOS_CTRL
#define REGULATOR_FASTBOOT_MTCMOS_CTRL
#endif
/********************************************************************************/
/*    pwrctrl ������hi_pwrctrl_ģ����_����)        */
/********************************************************************************/
/*���½ӿ�����regulator��mtcmos���µ������en��ʾ�ϵ磬dis��ʾ�µ� ,stat��ʾ״̬*/
/****************************V7R2 start*********************************/
/*sd_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_sdmtcmos_en(void)
{
    /* stub */
}
static __inline__ void hi_pwrctrl_regu_sdmtcmos_dis(void)
{
    /* stub */
}
static __inline__ unsigned int hi_pwrctrl_regu_sdmtcmos_stat(void)
{
    /* stub */
	return 0;
}

/*usb_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_usbmtcmos_en(void)
{
	set_hi_pwr_ctrl6_usb_mtcmos_en(1);
	while(!get_hi_pwr_stat1_usb_mtcmos_rdy())
	{
		;
	}
	__udelay_soc(30);
	set_hi_crg_srstdis2_soc_peri_usb_pd_srst_dis(1);
	set_hi_pwr_ctrl5_usb_iso_dis(1);
	set_hi_crg_clken2_soc_peri_usb_pd_clk_en(1);
}
static __inline__ void hi_pwrctrl_regu_usbmtcmos_dis(void)
{
	set_hi_crg_clkdis2_soc_usb_pd_clk_dis(1);
	set_hi_pwr_ctrl4_usb_iso_en(1);
	set_hi_crg_srsten2_soc_peri_usb_pd_srst_en(1);
	set_hi_pwr_ctrl7_usb_mtcmos_dis(1);
  
}
static __inline__ unsigned int hi_pwrctrl_regu_usbmtcmos_stat(void)
{
	return get_hi_pwr_stat1_usb_mtcmos_rdy();
}
/*irm_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_irmmtcmos_en(void)
{
	set_hi_pwr_ctrl6_irm_mtcmos_en(1);
	while(!get_hi_pwr_stat1_irm_mtcmos_rdy())
	{
		;
	}
	__udelay_soc(30);
	set_hi_crg_srstdis3_irm_pd_srst_dis(1);
	set_hi_pwr_ctrl5_irm_iso_dis(1);
	set_hi_crg_clken5_irm_pd_clk_en(1);
}
static __inline__ void hi_pwrctrl_regu_irmmtcmos_dis(void)
{
	set_hi_crg_clkdis5_irm_pd_clk_dis(1);
	set_hi_pwr_ctrl4_irm_iso_en(1);
	set_hi_crg_srsten3_irm_pd_srst_en(1);
	set_hi_pwr_ctrl7_irm_mtcmos_dis(1);
}
static __inline__ unsigned int hi_pwrctrl_regu_irmmtcmos_stat(void)
{
	return get_hi_pwr_stat1_irm_mtcmos_rdy();
}
/*g2bbp_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_g2bbpmtcmos_en(void)
{
	/*����G2BBP�ϵ�(���üĴ���PWR_CTRL6(0x90000c18)=(0x1<<10))*/
	set_hi_pwr_ctrl6_g2bbp_mtcmos_en(1);
	
   	 /*�ȴ��ϵ����*/
   	while(!get_hi_pwr_stat1_g2bbp_mtcmos_rdy())
   	{;}
   	__udelay_soc(30);
	/*����G2BBP��ʱ��ʹ��(���üĴ���CRG_CLKEN5(��ַ0x90000030)=(0x1<<4)*/
	set_hi_crg_clken5_g2bbp_pd_clk_en(1);

	/*����G2BBP�Ľ⸴λ(���üĴ���CRG_SRSTDIS3(0x9000007C)=(0x1<<4)*/
	set_hi_crg_srstdis3_g2bbp_pd_srst_dis(1);

	/*����G1BBP��Ƕλ��ʹ��(���üĴ���PWR_CTRL5(0x90000c14)=(0x1<<10))*/
	set_hi_pwr_ctrl5_g2bbp_iso_dis(1);
}
static __inline__ void hi_pwrctrl_regu_g2bbpmtcmos_dis(void)
{
	/*����G2BBP��Ƕλʹ��(���üĴ���PWR_CTRL4(0x90000c10)=(0x1<<10))*/
	set_hi_pwr_ctrl4_g2bbp_iso_en(1);

	/*����G2BBP�ĸ�λ(���üĴ���CRG_SRSTEN3(0x90000078)=(0x1<<4)*/
	set_hi_crg_srsten3_g2bbp_pd_srst_en(1);
	
	/*����G2BBP��ʱ�Ӳ�ʹ��(��ַ0x90000034)=(0x1<<4)*/
	set_hi_crg_clkdis5_g2bbp_pd_clk_dis(1);

	/*����G2BBP����(���üĴ���PWR_CTRL7(0x90000c1c)=(0x1<<10))*/
	set_hi_pwr_ctrl7_g2bbp_mtcmos_dis(1);
}
static __inline__ unsigned int hi_pwrctrl_regu_g2bbpmtcmos_stat(void)
{
	return get_hi_pwr_stat1_g2bbp_mtcmos_rdy();
}
/*g1bbp_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_g1bbpmtcmos_en(void)
{
	/*����G1BBP�ϵ�(���üĴ���PWR_CTRL6(0x90000c18)=(0x1<<9))*/
	set_hi_pwr_ctrl6_g1bbp_mtcmos_en(1);
	
    	/*�ȴ��ϵ����*/
   	while(!get_hi_pwr_stat1_g1bbp_mtcmos_rdy())
   	{
		;
   	}
	__udelay_soc(30);
	/*����G1BBP��ʱ��ʹ��(���üĴ���CRG_CLKEN5(��ַ0x90000030)=(0x1<<3)*/
	set_hi_crg_clken5_g1bbp_pd_clk_en(1);

	/*����G1BBP�Ľ⸴λ(���üĴ���CRG_SRSTDIS3(0x9000007C)=(0x1<<3)*/
	set_hi_crg_srstdis3_g1bbp_pd_srst_dis(1);

	/*����G1BBP��Ƕλ��ʹ��(���üĴ���PWR_CTRL5(0x90000c14)=(0x1<<9))*/
	set_hi_pwr_ctrl5_g1bbp_iso_dis(1);
}
static __inline__ void hi_pwrctrl_regu_g1bbpmtcmos_dis(void)
{	
	/*����G1BBP��Ƕλʹ��(���üĴ���PWR_CTRL4(0x90000c10)=(0x1<<9))*/
	set_hi_pwr_ctrl4_g1bbp_iso_en(1);
	
	/*����G1BBP�ĸ�λ(���üĴ���CRG_SRSTEN3(0x90000078)=(0x1<<3)*/
	set_hi_crg_srsten3_g1bbp_pd_srst_en(1);
		
	/*����G1BBP��ʱ�Ӳ�ʹ��(��ַ0x90000034)=(0x1<<3)*/
	set_hi_crg_clkdis5_g1bbp_pd_clk_dis(1);
	
	/*����G1BBP����(���üĴ���PWR_CTRL7(0x90000c1c)=(0x1<<9))*/
	set_hi_pwr_ctrl7_g1bbp_mtcmos_dis(1);
}
static __inline__ unsigned int hi_pwrctrl_regu_g1bbpmtcmos_stat(void)
{
	return get_hi_pwr_stat1_g1bbp_mtcmos_rdy();
}
/*wbbp_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_wbbpmtcmos_en(void)
{
	
	/*����WBBP�ϵ�(���üĴ���PWR_CTRL6(0x90000c18)=(0x1<<8))*/
	set_hi_pwr_ctrl6_wbbp_mtcmos_en(1);
	
	/*�ȴ��ϵ����*/
	while(!get_hi_pwr_stat1_wbbp_mtcmos_rdy())
	{
		;
	}
	__udelay_soc(30);
	/*����WBBP��ʱ��ʹ��(���üĴ���CRG_CLKEN5(��ַ0x90000030)=(0x1<<6)*/
	set_hi_crg_clken5_wbbp_pd_clk_en(1);

	/*����WBBP�Ľ⸴λ(���üĴ���CRG_SRSTDIS3(0x9000007C)=(0x1<<6)*/
	set_hi_crg_srstdis3_wbbp_pd_srst_dis(1);

	/*����WBBP��Ƕλ��ʹ��(���üĴ���PWR_CTRL5(0x90000c14)=(0x1<<8))*/
	set_hi_pwr_ctrl5_wbbp_iso_dis(1);

}
static __inline__ void hi_pwrctrl_regu_wbbpmtcmos_dis(void)
{
	/*����WBBP��Ƕλʹ��(���üĴ���PWR_CTRL4(0x90000c10)=(0x1<<8))*/
	set_hi_pwr_ctrl4_wbbp_iso_en(1);

	/*����WBBP�ĸ�λ(���üĴ���CRG_SRSTEN3(0x90000078)=(0x1<<6)*/
	set_hi_crg_srsten3_wbbp_pd_srst_en(1);
	
	/*����WBBP��ʱ�Ӳ�ʹ��(��ַ0x90000034)=(0x1<<6)*/
	set_hi_crg_clkdis5_wbbp_pd_clk_dis(1);

	/*����WBBP����(���üĴ���PWR_CTRL7(0x90000c1c)=(0x1<<8))*/
	set_hi_pwr_ctrl7_wbbp_mtcmos_dis(1);
}
static __inline__ unsigned int hi_pwrctrl_regu_wbbpmtcmos_stat(void)
{
	return get_hi_pwr_stat1_wbbp_mtcmos_rdy();
}
/*twbbp_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_twbbpmtcmos_en(void)
{
	/*����TWBBP�ϵ�(���üĴ���PWR_CTRL6(0x90000c18)=(0x1<<7))*/
	set_hi_pwr_ctrl6_twbbp_mtcmos_en(1);

	/*�ȴ��ϵ����*/
  	 while(!get_hi_pwr_stat1_twbbp_mtcmos_rdy())
   	{
		;
   	}
   __udelay_soc(30);
	/*����TWBBP��ʱ��ʹ��(���üĴ���CRG_CLKEN5(��ַ0x90000030)=(0x1<<5)*/
	set_hi_crg_clken5_twbbp_pd_clk_en(1);

	/*����TWBBP�Ľ⸴λ(���üĴ���CRG_SRSTDIS3(0x9000007C)=(0x1<<5)*/
	set_hi_crg_srstdis3_twbbp_pd_srst_dis(1);

	/*����TBBP��Ƕλ��ʹ��(���üĴ���PWR_CTRL5(0x90000c14)=(0x1<<7))*/
	set_hi_pwr_ctrl5_twbbp_iso_dis(1);
}
static __inline__ void hi_pwrctrl_regu_twbbpmtcmos_dis(void)
{
	/*����G2BBP��Ƕλʹ��(���üĴ���PWR_CTRL4(0x90000c10)=(0x1<<7))*/
	set_hi_pwr_ctrl4_twbbp_iso_en(1);

	/*����G2BBP�ĸ�λ(���üĴ���CRG_SRSTEN3(0x90000078)=(0x1<<5)*/
	set_hi_crg_srsten3_twbbp_pd_srst_en(1);
	
	/*����G2BBP��ʱ�Ӳ�ʹ��(��ַ0x90000034)=(0x1<<5)*/
	set_hi_crg_clkdis5_twbbp_pd_clk_dis(1);

	/*����G2BBP����(���üĴ���PWR_CTRL7(0x90000c1c)=(0x1<<7))*/
	set_hi_pwr_ctrl7_twbbp_mtcmos_dis(1);
}
static __inline__ unsigned int hi_pwrctrl_regu_twbbpmtcmos_stat(void)
{
	return get_hi_pwr_stat1_twbbp_mtcmos_rdy();
}
/*lbbp_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_lbbpmtcmos_en(void)
{
	set_hi_pwr_ctrl6_lbbp_mtcmos_en(1);
	/*�ж�������Ҫ�����ٴ�ȷ��20131023*/
	//while((!get_hi_pwr_stat1_lbbp_mtcmos_rdy()) || (!(get_hi_pwr_stat1_reserved() & 0x1)))
	/*V711��û��lbbp0״̬�޷���ȡ*/
	while(!get_hi_pwr_stat1_lbbp_mtcmos_rdy()) 
	{
		;
	}
	__udelay_soc(30);
	set_hi_crg_srstdis3_lbbp_pd_srst_dis(1);
	set_hi_pwr_ctrl5_lbbp_iso_dis(1);
	set_hi_crg_clken5_ltebbp_pd_clk_en(1);
}
static __inline__ void hi_pwrctrl_regu_lbbpmtcmos_dis(void)
{
	/*����LTE BBP��Ƕλʹ��(���üĴ���PWR_CTRL4(0x90000c10)=(0x1<<6))*/
	set_hi_pwr_ctrl4_lbbp_iso_en(1);

	/*����LTE BBP�ĸ�λ(���üĴ���CRG_SRSTEN3(0x90000078)=(0x1<<2)*/
	set_hi_crg_srsten3_lbbp_pd_srst_en(1);
	
	/*����LTE BBP��ʱ�Ӳ�ʹ��(��ַ0x90000034)=(0x1<<2)*/
	set_hi_crg_clkdis5_ltebbp_pd_clk_dis(1);

	/*����LTE BBP����(���üĴ���PWR_CTRL7(0x90000c1c)=(0x1<<6))*/
	set_hi_pwr_ctrl7_lbbp_mtcmos_dis(1);
}
static __inline__ unsigned int hi_pwrctrl_regu_lbbpmtcmos_stat(void)
{
	return get_hi_pwr_stat1_lbbp_mtcmos_rdy();
}
/*hifi_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_hifimtcmos_en(void)
{
	set_hi_pwr_ctrl6_hifi_mtcmos_en(1);
	while(!get_hi_pwr_stat1_hifi_mtcmos_rdy())
	{
		;
	}
	__udelay_soc(30);
	set_hi_crg_srstdis2_hifi_dbg_srst_dis(1);
	set_hi_crg_srstdis2_hifi_pd_srst_dis(1);
	set_hi_pwr_ctrl5_hifi_iso_dis(1);
	set_hi_crg_clken3_hifi_clk_en(1);
}
static __inline__ void hi_pwrctrl_regu_hifimtcmos_dis(void)
{
	set_hi_crg_clkdis3_hifi_clk_dis(1);
	set_hi_pwr_ctrl4_hifi_iso_en(1);
	set_hi_crg_srsten2_hifi_pd_srst_en(1);
	set_hi_crg_srsten2_hifi_dbg_srst_en(1);
	set_hi_pwr_ctrl7_hifi_mtcmos_dis(1);
}
static __inline__ unsigned int hi_pwrctrl_regu_hifimtcmos_stat(void)
{
	return get_hi_pwr_stat1_hifi_mtcmos_rdy();
}
/*dsp0_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_dsp0mtcmos_en(void)
{
}
static __inline__ void hi_pwrctrl_regu_dsp0mtcmos_dis(void)
{	
}
static __inline__ unsigned int hi_pwrctrl_regu_dsp0mtcmos_stat(void)
{
	return get_hi_pwr_stat1_dsp0_mtcmos_rdy();
}
/*hisc_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_hiscmtcmos_en(void)
{
    /* stub */
}
static __inline__ void hi_pwrctrl_regu_hiscmtcmos_dis(void)
{	 
    /* stub */
}
static __inline__ unsigned int hi_pwrctrl_regu_hiscmtcmos_stat(void)
{
    /* stub */
    return 0;
}
/*moda9_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_moda9mtcmos_en(void)
{
	/*
	set_hi_pwr_ctrl6_moda9_mtcmos_en(1);
	while(!get_hi_pwr_stat1_moda9_mtcmos_rdy())
	{
		;
	}
	set_hi_crg_clken3_mdma9_clk_en(1);
	set_hi_pwr_ctrl5_moda9_iso_dis(1);
	set_hi_crg_srstdis1_mdma9_srst_dis(1);
	*/
}
static __inline__ void hi_pwrctrl_regu_moda9mtcmos_dis(void)
{
	/*
	set_hi_crg_clkdis3_mdma9_clk_dis(1);
	set_hi_pwr_ctrl4_moda9_iso_en(1);
	set_hi_crg_srsten1_mdma9_srst_en(1);
	set_hi_pwr_ctrl7_moda9_mtcmos_dis(1);
	*/
}
static __inline__ unsigned int hi_pwrctrl_regu_moda9mtcmos_stat(void)
{
	return get_hi_pwr_stat1_moda9_mtcmos_rdy();
}
/*appa9_mtcmos���µ�*/
static __inline__ void hi_pwrctrl_regu_appa9mtcmos_en(void)
{
	/*
	set_hi_pwr_ctrl6_appa9_mtcmos_en(1);
	while(!get_hi_pwr_stat1_appa9_mtcmos_rdy())
	{
		;
	}
	set_hi_crg_clken3_appa9_clk_en(1);
	set_hi_pwr_ctrl5_appa9_iso_dis(1);
	set_hi_crg_srstdis1_appa9_srst_dis(1);
	*/
}
static __inline__ void hi_pwrctrl_regu_appa9mtcmos_dis(void)
{
	/*
	set_hi_crg_clkdis3_appa9_clk_dis(1);
	set_hi_pwr_ctrl4_appa9_iso_en(1);
	set_hi_crg_srsten1_appa9_srst_en(1);
	set_hi_pwr_ctrl7_appa9_mtcmos_dis(1);
	*/
}
static __inline__ unsigned int hi_pwrctrl_regu_appa9mtcmos_stat(void)
{
	return get_hi_pwr_stat1_appa9_mtcmos_rdy();
}
/****************************V7R2 end*********************************/
/****************************p531 start*******************************/
/*tcsdrv1���µ�*/
static __inline__ void hi_pwrctrl_regu_tcsdrv1_en(void)
{

}
static __inline__ void hi_pwrctrl_regu_tcsdrv1_dis(void)
{

}
static __inline__ unsigned int hi_pwrctrl_regu_tcsdrv1_stat(void)
{
	return 0;
}
/*fpgaif���µ�*/
static __inline__ void hi_pwrctrl_regu_fpgaif_en(void)
{

}
static __inline__ void hi_pwrctrl_regu_fpgaif_dis(void)
{

}
static __inline__ unsigned int hi_pwrctrl_regu_fpgaif_stat(void)
{
	return 0;
}
/*t570t���µ�*/
static __inline__ void hi_pwrctrl_regu_t570t_en(void)
{

}
static __inline__ void hi_pwrctrl_regu_t570t_dis(void)
{

}
static __inline__ unsigned int hi_pwrctrl_regu_t570t_stat(void)
{
	return 0;
}
/*a15���µ�*/
static __inline__ void hi_pwrctrl_regu_a15_en(void)
{

}
static __inline__ void hi_pwrctrl_regu_a15_dis(void)
{

}
static __inline__ unsigned int hi_pwrctrl_regu_a15_stat(void)
{
	return 0;
}
/*hsicphy���µ�*/
static __inline__ void hi_pwrctrl_regu_hsicphy_en(void)
{

}
static __inline__ void hi_pwrctrl_regu_hsicphy_dis(void)
{

}
static __inline__ unsigned int hi_pwrctrl_regu_hsicphy_stat(void)
{
	return 0;
}
/*usbphy���µ�*/
static __inline__ void hi_pwrctrl_regu_usbphy_en(void)
{

}
static __inline__ void hi_pwrctrl_regu_usbphy_dis(void)
{

}
static __inline__ unsigned int hi_pwrctrl_regu_usbphy_stat(void)
{
	return 0;
}
/*appa9���µ�*/
static __inline__ void hi_pwrctrl_regu_appa9_en(void)
{

}
static __inline__ void hi_pwrctrl_regu_appa9_dis(void)
{

}
static __inline__ unsigned int hi_pwrctrl_regu_appa9_stat(void)
{
	return 0;
}
/*hifi���µ�*/
static __inline__ void hi_pwrctrl_regu_hifi_en(void)
{

}
static __inline__ void hi_pwrctrl_regu_hifi_dis(void)
{

}
static __inline__ unsigned int hi_pwrctrl_regu_hifi_stat(void)
{
	return 0;
}
/*bbe16���µ�*/
static __inline__ void hi_pwrctrl_regu_bbe16_en(void)
{

}
static __inline__ void hi_pwrctrl_regu_bbe16_dis(void)
{

}
static __inline__ unsigned int hi_pwrctrl_regu_bbe16_stat(void)
{
	return 0;
}
/*moda9���µ�*/
static __inline__ void hi_pwrctrl_regu_moda9_en(void)
{

}
static __inline__ void hi_pwrctrl_regu_moda9_dis(void)
{

}
static __inline__ unsigned int hi_pwrctrl_regu_moda9_stat(void)
{
	return 0;
}

/*TCXO1���µ�*/
static __inline__ void hi_pwrctrl_tcxo1_pmu_en_enable(void)
{
	set_hi_pwr_ctrl2_pmu_ch1_tcxo_en(1);
}
static __inline__ void hi_pwrctrl_tcxo1_pmu_en_disable(void)
{
	set_hi_pwr_ctrl2_pmu_ch1_tcxo_en(0);
}
static __inline__ void hi_pwrctrl_tcxo1_abb_en_enable(void)
{
	set_hi_pwr_ctrl2_abb_ch1_tcxo_en(1);
}
static __inline__ void hi_pwrctrl_tcxo1_abb_en_disable(void)
{
	set_hi_pwr_ctrl2_abb_ch1_tcxo_en(0);
}


/****************************p531 end*********************************/

/* for pm */
static __inline__ unsigned int hi_pwrctrl_get_pwr_ctrl2_abb_ch1_tcxo_en()
{
    return get_hi_pwr_ctrl2_abb_ch1_tcxo_en();
}
static __inline__ unsigned int hi_pwrctrl_get_pwr_ctrl2_pmu_ch1_tcxo_en()
{
    return get_hi_pwr_ctrl2_pmu_ch1_tcxo_en();
}
static __inline__ void hi_pwrctrl_set_pwr_ctrl2_abb_ch1_tcxo_en(unsigned int val)
{
	set_hi_pwr_ctrl2_abb_ch1_tcxo_en(val);
}
static __inline__ void hi_pwrctrl_set_pwr_ctrl2_pmu_ch1_tcxo_en(unsigned int val)
{
	set_hi_pwr_ctrl2_pmu_ch1_tcxo_en(val);
}

static __inline__ unsigned int get_hi_pwr_stat1(void)
{
#if defined(__KERNEL__)
	return readl((const volatile void *)(HI_SYSCRG_BASE_ADDR+HI_PWR_STAT1_OFFSET));
#else
	return readl((HI_SYSCRG_BASE_ADDR+HI_PWR_STAT1_OFFSET));
#endif
}

static __inline__ unsigned int get_hi_pwr_stat1_ltebbp0_mtcmos_rdy_stat(void)
{

	//return (get_hi_pwr_stat1_reserved() & 0x1);
	return 1;
}
/* for pm --end */

#endif

