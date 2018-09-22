
#ifndef __MACH_CLOCK_H
#define __MACH_CLOCK_H
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef __KERNEL__
#include <linux/list.h>
#include <linux/clkdev.h>
#include <linux/err.h>
#include <linux/mutex.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/clk.h>
#include <linux/ctype.h>
#include <linux/spinlock.h>

#ifndef printf
#define printf(fmt, args...) printk(fmt , ## args)
#endif

#elif defined(__VXWORKS__) /* __VXWORKS__ */
#include <intLib.h>
#include <osl_bio.h>
#include <osl_types.h>
#include <osl_list.h>
#include <osl_sem.h>

struct clk_lookup {
	struct list_head	node;          /*for clock list*/
	const char		    *dev_id;       /*device init_name, can be NULL*/
	const char		    *con_id;       /*clock name strings*/
	struct clk		    *clk;          /*varibility of clock structure*/
};

#ifndef NULL
#define NULL (void *)0
#endif

#endif /*__KERNEL__*/
#include <osl_spinlock.h>
#include <hi_base.h>
#include <hi_syscrg_interface.h>
#include <bsp_memmap.h>
#include <bsp_om.h>
#include <drv_clk.h>
#include <bsp_ipc.h>

#define  clk_printf(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_CLK, "[clk]: <%s> "fmt"", __FUNCTION__, ##__VA_ARGS__))

#define REG_MIN_VALUE    0x1
#define  HAS_ENABLE_REG  1
#define  NO_ENABLE_REG    0

/*define rate*/

#define TCXO                                   (19200000)    /*19.2M*/
#define CLK_32K                                (32768)
#define A9_PLL                                 (1200000000)  /*need modify*/

#define HIFI_PLL                               (1200000000)  /*1200M*/
#ifdef CONFIG_V711_CLK_CRG
#define GMAC_PLL                               (125000000)  /*125M*/
#define DSP_PLL_RATE                           (600000000)  /* 600M */
#endif
#define PERIPLL_FOUNT1                         (480000000)   /*480M*/
#define PERIPLL_FOUNT3                         (160000000)   /*160M*/
#define PERIPLL_FOUNT4                         (120000000)    /*120M*/
#define PERIPLL_FOUNTPOST                      (960000000)   /*960M*/

#define MMC_DIV4                               (120000000)   /*120M*/
#define MMC_DIV6                               (80000000)     /*80M*/
#define MMC_DIV8                               (60000000)     /*60M*/
#define MMC_DIV10                              (48000000)     /*48M*/
#define MMC_DIV20                              (24000000)     /*24M*/
#define PREI_48M                               (PERIPLL_FOUNT1/10)  /*48M*/

/*
*clock_id
*/
#ifdef CONFIG_V711_CLK_CRG
typedef enum
{
    CLK_NO_REG = 0,         /* 0 */

    MST_ACLK_ID,            /* 1 */
    DSP_ACLK_ID,            /* 2 */
    SOC_HCLK_ID,            /* 3 */
    AMON_CPUFAST_CLK_ID,    /* 4 */
    AMON_SOC_CLK,           /* 5 */
    TSENSOR_CLK_ID,         /* 6 */
    IPF_CLK_ID,             /* 7 */
    EDMAC_CHE4_CLK_ID,      /* 8 */
    SOCP_CLK_ID,            /* 9 */
    MIPI_CLK_ID,            /* 10 */
    PMUSSI0_CLK_ID,         /* 11 */
    PMUSSI1_CLK_ID,         /* 12 */
    DW_SSI0_CLK_ID,         /* 13 */
    EFUSE_CLK_ID,           /* 14 */
    NANDC_CLK_ID,           /* 15 */
    HS_UART_CLK_ID,         /* 16 */
    EMI_CLK_ID,             /* 17 */
    EDMAC_CLK_ID,           /* 18 */
    BOOTROM_CLK_ID,         /* 19 */
    PWM1_CLK_ID,            /* 20 */
    PWM0_CLK_ID,            /* 21 */
    DT_CLK_ID,              /* 22 */
    IPCM_CLK_ID,            /* 23 */
    DW_SSI1_CLK_ID,         /* 24 */
    I2C1_CLK_ID,            /* 25 */
    CPIO1_CLK_ID,           /* 26 */
    I2C0_CLK_ID,            /* 27 */
    GPIO3_CLK_ID,           /* 28 */

    UART3_CLK_ID,               /* 29 */    
    UART2_CLK_ID,               /* 30 */
    GPIO2_CLK_ID,               /* 31 */
    CS_CLK_ID ,                 /* 32 */
    APPA9_MBIST_CLK_ID,         /* 33 */
    MONA9_MBIST_CLK_ID,         /* 34 */
    CPU_ACLK_ID,                /* 35 */
    MDDRC_CLK_ID,               /* 36 */
    DDRPHY_CLK_ID,              /* 37 */
    DDRPHY_DDR_CLK_ID,          /* 38 */
    AXI_MEN_CLK_ID,             /* 39 */    
    FUNC_WAKEUP_PD_CLK_ID,      /* 40 */
    SOC_PERI_USB_PD_CLK_ID,     /* 41 */
    USBOTG_CLK_ID,              /* 42 */
    USB_BC_CLK_ID,              /* 43 */
    MMC0_CLK_ID,                /* 44 */
    MMC1_CLK_ID,                /* 45 */
    MMC0_PHASE_CLK_ID,          /* 46 */
    MMC1_PHASE_CLK_ID,          /* 47 */
    MMC0_REFCLK_ID,             /* 48 */
    MMC1_REFCLK_ID,             /* 49 */    
    USBHSIC_CLK_ID,             /* 50 */
    SDCC_CLK_ID,                /* 51 */
    HPM_CLK_ID,                 /* 52 */
    PCIE_CTRL1_CLK_ID,          /* 53 */
    PCIE_CTRL2_CLK_ID,          /* 54 */
    PCIE_PHY_CLK_ID,            /* 55 */
    WDOG_CLK_ID,                /* 56 */

    GPIO0_CLK_ID,               /* 57 */
    UART0_CLK_ID,               /* 58 */
    TM0_CLK_ID,                 /* 59 */
    
    TM1_CLK_ID,                 /* 60 */
    TM2_CLK_ID,                 /* 61 */
    TM3_CLK_ID,                 /* 62 */
    TM4_CLK_ID,                 /* 63 */
    TM5_CLK_ID,                 /* 64 */
    TM6_CLK_ID,                 /* 65 */
    TM7_CLK_ID,                 /* 66 */
    TM8_CLK_ID,                 /* 67 */
    TM9_CLK_ID,                 /* 68 */
    TM10_CLK_ID,                /* 69 */
    
    TM11_CLK_ID,                /* 70 */
    TM12_CLK_ID,                 /* 71 */
    TM13_CLK_ID,                 /* 72 */
    TM14_CLK_ID,                 /* 73 */
    TM15_CLK_ID,                 /* 74 */
    TM16_CLK_ID,                 /* 75 */
    TM17_CLK_ID,                 /* 76 */
    TM18_CLK_ID,                 /* 77 */
    TM19_CLK_ID,                 /* 78 */
    TM20_CLK_ID,                 /* 79 */
    
    TM21_CLK_ID,                 /* 80 */
    TM22_CLK_ID,                 /* 81 */
    TM23_CLK_ID,                 /* 82 */
    APPA9_CLK_ID,                /* 83 */
    MOMA9_CLK_ID,                /* 84 */
    LET_SIO_CLK,                 /* 85 */
    HIFI_DBG_CLK_ID,             /* 86 */
    HIFI_CLK_ID,                 /* 87 */

    DSP0_PD_CLK_ID,              /* 88 */
    DSP0_CORE_CLK_ID,            /* 89 */    
    DSP0_DBG_CLK_ID,             /* 90 */
    GUACC_AXI_CLK_ID,            /* 91 */
    CICOM0_CLK_ID,               /* 92 */
    CICOM1_CLK_ID,               /* 93 */
    HDLC_CLK_ID,                 /* 94 */
    UPACC_CLK_ID,                /* 95 */
    SCI0_CLK_ID,                 /* 96 */
    SCI1_CLK_ID,                 /* 97 */
    UICC_CLK_ID,                 /* 98 */
    UART1_CLK_ID,                /* 99 */    
    DSP_VIC_CLK_ID,              /* 100 */
    CIPEHER_CLK_ID,              /* 101 */
    GMAC_RX_CLK_ID,              /* 102 */
    GMAC_TX_CLK_ID,              /* 103 */
    GMAC_GTX_CLK_ID,             /* 104 */
    GMAC_SWITCH_CLK_ID,          /* 105 */
    GMAC_ACLK_CLK_ID,            /* 106 */
                                 

    BBP_AO_CLK_ID,               /* 107 */
    BBPCOMMON_2A_CLK_ID,         /* 108 */
    LTEBBP_PD_CLK_ID,            /* 109 */
    
    G1BBP_PD_CLK_ID,             /* 110 */
    G2BBP_PD_CLK_ID,             /* 111 */
    TWBBP_PD_CLK_ID,             /* 112 */
    WBBP_PD_CLK_ID,              /* 113 */
    IRM_PD_CLK_ID,               /* 114 */
    LBBP_AXI_CLK_ID,             /* 115 */
    LBBP_PTD_CLK_ID,             /* 116 */
    LBBP_PDF_CLK_ID,             /* 117 */
    LBBP_TDL_CLK_ID,             /* 118 */
    LBBP_VDL_CLK_ID,             /* 119 */
    
    LBBP_TDS_CLK_ID,             /* 120 */
    IRM_TURBO_CLK_ID,            /* 121 */
    IRM_BBP_245M_CLK_ID,         /* 122 */
    IRM_WBBP_122M_CLK_ID,        /* 123 */
    TWBBP_WBBP_122M_CLK_ID,      /* 124 */
    TWBBP_WBBP_61M_CLK_ID,       /* 125 */
    TWBBP_TBBP_122M_CLK_ID,      /* 126 */
    TWBBP_TBBP_245M_CLK_ID,      /* 127 */
    WBBP_61M_CLK_ID,             /* 128 */
    WBBP_122M_CLK_ID,            /* 129 */
    
    WBBP_245M_CLK_ID,            /* 130 */
    WBBP_AXI_CLK_ID,             /* 131 */
    MMC2_CLK_ID,                 /* 132 */
    MMC0_CCLK_ID,                /* 133 */
    MMC1_CCLK_ID,                /* 134 */
    MMC2_CCLK_ID,                /* 135 */
    SIO_BCLK_ID,                 /* 136 */
    SIO_SYNCLK_ID,               /* 137 */
    SIO_OUTER_CLK_ID,            /* 138 */
    BBE16_DFS_PD_ID,             /* 139 */
    
    BBP_DFS_PD_ID,               /* 140 */
    ABB_CH0_LWT_PLL_ID,          /* 141 */
    ABB_CH0_G_PLL_ID,            /* 142 */
    ABB_CH1_LWT_PLL_ID,          /* 143 */
    ABB_CH1_G_PLL_ID             /* 144 */
}clk_id;
#else
typedef enum
{
    CLK_NO_REG = 0,

    /*enable reg 1*/
    MST_ACLK_ID = 1,
    DSP_ACLK_ID = 2,
    SOC_HCLK_ID = 3,
    AMON_CPUFAST_CLK_ID = 4,
    AMON_SOC_CLK = 5,
    TSENSOR_CLK_ID = 6,
    IPF_CLK_ID = 7,
    EDMAC_CHE4_CLK_ID = 8,
    SOCP_CLK_ID = 9,
    MIPI_CLK_ID = 10,
    PMUSSI0_CLK_ID = 11,
    PMUSSI1_CLK_ID = 12,
    DW_SSI0_CLK_ID = 13,
    EFUSE_CLK_ID = 14,
    NANDC_CLK_ID = 15,
    HS_UART_CLK_ID = 16,
    EMI_CLK_ID = 17,
    EDMAC_CLK_ID = 18,
    BOOTROM_CLK_ID = 19,
    PWM1_CLK_ID = 20,
    PWM0_CLK_ID = 21,
    DT_CLK_ID = 22,
    IPCM_CLK_ID,
    DW_SSI1_CLK_ID,
    I2C1_CLK_ID,
    CPIO1_CLK_ID,
    I2C0_CLK_ID,
    GPIO3_CLK_ID,


    /*enable reg 2*/
    UART3_CLK_ID,
    UART2_CLK_ID,
    GPIO2_CLK_ID,
    CS_CLK_ID ,
    APPA9_MBIST_CLK_ID,
    MONA9_MBIST_CLK_ID,
    CPU_ACLK_ID,
    MDDRC_CLK_ID,
    DDRPHY_CLK_ID,
    DDRPHY_DDR_CLK_ID,
    AXI_MEN_CLK_ID,
    FUNC_WAKEUP_PD_CLK_ID,
    SOC_PERI_USB_PD_CLK_ID,
    USBOTG_CLK_ID,
    USB_BC_CLK_ID,
    MMC0_CLK_ID,
    MMC1_CLK_ID,
    MMC0_PHASE_CLK_ID,
    MMC1_PHASE_CLK_ID,
    MMC0_REFCLK_ID,
    MMC1_REFCLK_ID,
    USBHSIC_CLK_ID,
    SDCC_CLK_ID,
    HPM_CLK_ID,
    PCIE_CTRL1_CLK_ID,
    PCIE_CTRL2_CLK_ID,
    PCIE_PHY_CLK_ID,
    WDOG_CLK_ID,

    /*enable reg 3*/
    GPIO0_CLK_ID,
    UART0_CLK_ID,
    TM0_CLK_ID,
    TM1_CLK_ID,
    TM2_CLK_ID,
    TM3_CLK_ID,
    TM4_CLK_ID,
    TM5_CLK_ID,
    TM6_CLK_ID,
    TM7_CLK_ID,
    TM8_CLK_ID,
    TM9_CLK_ID,
    TM10_CLK_ID,
    TM11_CLK_ID,
    TM12_CLK_ID,
    TM13_CLK_ID,
    TM14_CLK_ID,
    TM15_CLK_ID,
    TM16_CLK_ID,
    TM17_CLK_ID,
    TM18_CLK_ID,
    TM19_CLK_ID,
    TM20_CLK_ID,
    TM21_CLK_ID,
    TM22_CLK_ID,
    TM23_CLK_ID,
    APPA9_CLK_ID,
    MOMA9_CLK_ID,
    LET_SIO_CLK,
    HIFI_DBG_CLK_ID,
    HIFI_CLK_ID,

    /*enable reg 4*/
    DSP0_PD_CLK_ID,
    DSP0_CORE_CLK_ID,
    DSP0_DBG_CLK_ID,
    GUACC_AXI_CLK_ID,
    CICOM0_CLK_ID,
    CICOM1_CLK_ID,
    HDLC_CLK_ID,
    UPACC_CLK_ID,
    SCI0_CLK_ID,
    SCI1_CLK_ID,
    UICC_CLK_ID,
    UART1_CLK_ID,
    DSP_VIC_CLK_ID,
    CIPEHER_CLK_ID,

    /*enable reg 5*/
    BBP_AO_CLK_ID,
    BBPCOMMON_2A_CLK_ID,
    LTEBBP_PD_CLK_ID,
    G1BBP_PD_CLK_ID,
    G2BBP_PD_CLK_ID,
    TWBBP_PD_CLK_ID,
    WBBP_PD_CLK_ID,
    IRM_PD_CLK_ID,
    LBBP_AXI_CLK_ID,
    LBBP_PTD_CLK_ID,
    LBBP_PDF_CLK_ID,
    LBBP_TDL_CLK_ID,
    LBBP_VDL_CLK_ID,
    LBBP_TDS_CLK_ID,
    IRM_TURBO_CLK_ID,
    IRM_BBP_245M_CLK_ID,
    IRM_WBBP_122M_CLK_ID,
    TWBBP_WBBP_122M_CLK_ID,
    TWBBP_WBBP_61M_CLK_ID,
    TWBBP_TBBP_122M_CLK_ID,
    TWBBP_TBBP_245M_CLK_ID,
    WBBP_61M_CLK_ID,
    WBBP_122M_CLK_ID,
    WBBP_245M_CLK_ID,
    WBBP_AXI_CLK_ID,

    MMC2_CLK_ID,
    MMC0_CCLK_ID,
    MMC1_CCLK_ID,
    MMC2_CCLK_ID,
    SIO_BCLK_ID,
    SIO_SYNCLK_ID,
    SIO_OUTER_CLK_ID,
    BBE16_DFS_PD_ID,
    BBP_DFS_PD_ID,
    ABB_CH0_LWT_PLL_ID,
    ABB_CH0_G_PLL_ID,
    ABB_CH1_LWT_PLL_ID,
    ABB_CH1_G_PLL_ID
}clk_id;
#endif

/**
 * struct crg_tag - clock register message
 */
struct crg_tag {
    unsigned int                      enable_flag;    /*tag clk has enable reg or not*/
    unsigned int                      enable_reg;     /*enable register offset*/
    unsigned int                      enable_bit;     /*enable bit offset*/
    unsigned int                      gate_reg;       /*clock gate control register offset*/
    unsigned int                      gate_bit;       /*gate control bit  offset*/
    unsigned int                      srst_reg;       /*clock soft resetl register offset*/
    unsigned int                      srst_bit;       /*soft reset  bit  offset*/
    unsigned int                      sel_reg;        /*clock parent select register offset*/
    unsigned int                      sel_bit;        /*select  bit offset*/
    unsigned int                      sel;            /*the value should be set to the registers' sel bits  ,all 1*/
    unsigned int                      div_reg;        /*clock div register offset*/
    unsigned int                      div_bit;        /*div  bit offset*/
    unsigned int                      div;            /*the value should be set to the registers' div bits  ,all 1*/
};

#define define_clock(_clk, _name, _parent, _rate, _sel_parents, _clkid) \
 static struct clk _clk = {         \
    _name,      \
    0,\
    &_parent,    \
    _rate,        \
    &clock_ops,   \
    _sel_parents,\
    _clkid,  \
}

#define define_clock_without_reg(_clk, _name, _rate) \
 static struct clk _clk = {         \
    _name,      \
    0,\
    NULL,    \
    _rate,  \
    NULL,\
    NULL,   \
    CLK_NO_REG,  \
}

#define clk_reg(_enable_flag, _enable_reg, _enable_bit, _gate_reg,\
_gate_bit, _srst_reg, _srst_bit, _sel_reg, _sel_bit, _sel, _div_reg, _div_bit, _div)\
    _enable_flag,\
    _enable_reg,\
    _enable_bit,\
     _gate_reg,\
    _gate_bit,\
    _srst_reg,\
    _srst_bit,\
    _sel_reg,\
    _sel_bit,\
    _sel,\
    _div_reg,\
    _div_bit,\
    _div,

#define regiser_clock(d, n, c) \
        {NULL,NULL},\
		d, \
		n, \
		&c,

extern struct clk_ops clock_ops_div_n;
extern struct clk_ops clock_ops;
extern struct clk_lookup hi6930_clk_lookup[];
extern struct crg_tag reg_message[];

/*This function for clk module init*/
void hi6930_clock_init(void);

#ifdef __KERNEL__

#ifdef CONFIG_DEBUG_FS
int __init clock_debug_init(void);
int __init clock_debug_add(struct clk *clock);
#else
static inline int __init clock_debug_init(void) { return 0; }
static inline int __init clock_debug_add(struct clk *clock) { return 0; }
#endif  /*CONFIG_DEBUG_FS*/

#elif defined(__VXWORKS__) /* __VXWORKS__ */
/***********************************************************************
*����:���ʱ���Ƿ��ȡ�ɹ�
*���:ʱ�ӽṹ��ָ��
*����:
*          ��ȡ�ɹ�0
*          ��ȡʧ��1
************************************************************************/
int  IS_ERR(struct clk *c);
#ifdef CONFIG_K3V3_CLK_CRG /*CONFIG_K3V3_CLK_CRG*/
void gps_refclk_icc_read_cb_init(void);
#endif
#endif  /*__KERNEL__*/

#ifdef __cplusplus
}
#endif

#endif
