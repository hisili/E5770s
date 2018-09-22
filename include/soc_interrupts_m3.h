
#ifndef __SOC_INTERRUPTS_M3_H__
#define __SOC_INTERRUPTS_M3_H__

#ifdef __cplusplus
extern "C" {
#endif


#define  M3_IPCM_INT0_2                 16  /* IPCM��M3�ĺ˼�ͨ�ţ���ӦIPCM�ж�0[2] */
#define  M3_IPCM_INT1_2                 17  /* IPCM��M3�ĺ˼�ͨ�ţ���ӦIPCM�ж�1[2] */
#define  M3_APPA9_EVENTO_INT            18  /* APP A9 EVENTO�ź� */
#define  M3_MDMA9_EVENTO_INT            19  /* MDM A9 EVENTO�ź� */
#define  M3_RTC_INT                     20  /* RTCģ������ж� */
#define  M3_WDT_INT                     21  /* WatchDogģ������ж� */
#define  M3_TSENSOR_INT                 22  /* Tsensor�ж� */
#define  M3_LTE_ARM_CLK_SWITCH_INT      23  /* LTE_BBP_ON��ARM�ж� */
#define  M3_LTE_ARM_WAKEUP_INT          24  /* LTE_BBP_ON��ARM�ж� */
#define  M3_LTE_ARM_PUB_INT             25  /* LTE_BBP_ON��ARM�ж� */
#define  M3_G1_INT_BBP_TO_CPU           26  /* GBBP1_ON��ARM�ж� */
#define  M3_G1_INT_BBP_TO_DSP           27  /* GBBP1_ON��ARM�ж� */
#define  M3_G1_INT_BBP_TO_CPU_32K       28  /* GBBP1_ON��ARM�ж� */
#define  M3_G1_INT_BBP_TO_DSP_32K       29  /* GBBP1_ON��ARM�ж� */
#define  M3_G2_INT_BBP_TO_CPU           30  /* GBBP2_ON��ARM�ж� */
#define  M3_G2_INT_BBP_TO_DSP           31  /* GBBP2_ON��ARM�ж� */
#define  M3_G2_INT_BBP_TO_CPU_32K       32  /* GBBP2_ON��ARM�ж� */
#define  M3_G2_INT_BBP_TO_DSP_32K       33  /* GBBP2_ON��ARM�ж� */
#define  M3_IPCM_INT0_4                 34  /* IPCM��M3�ĺ˼�ͨ�ţ���ӦIPCM�ж�0[4] */
#define  M3_TIMER0_INT                  35  /* TIMER0�ж� */
#define  M3_TIMER1_INT                  36  /* TIMER1�ж� */
#define  M3_TIMER2_INT                  37  /* TIMER2�ж� */
#define  M3_TIMER3_INT                  38  /* TIMER3�ж� */
#define  M3_TIMER4_INT                  39  /* TIMER4�ж� */
#define  M3_TIMER5_INT                  40  /* TIMER5�ж� */
#define  M3_TIMER6_INT                  41  /* TIMER6�ж� */
#define  M3_TIMER7_INT                  42  /* TIMER7�ж� */
#define  M3_TIMER8_INT                  43  /* TIMER8�ж� */
#define  M3_TIMER9_INT                  44  /* TIMER9�ж� */
#define  M3_TIMER10_INT                 45  /* TIMER10�ж� */
#define  M3_TIMER11_INT                 46  /* TIMER11�ж� */
#define  M3_TIMER12_INT                 47  /* TIMER12�ж� */
#define  M3_TIMER13_INT                 48  /* TIMER13�ж� */
#define  M3_TIMER14_INT                 49  /* TIMER14�ж� */
#define  M3_TIMER15_INT                 50  /* TIMER15�ж� */
#define  M3_SCI0_INT                    51  /* SIM��0�ж� */
#define  M3_SCI1_INT                    52  /* SIM��1�ж� */
#define  M3_DW_SSI0_INT                 53  /* SPI0�ж� */
#define  M3_DW_SSI1_INT                 54  /* SPI1�ж� */
#define  M3_RESERVE2                    55  /* ���� */
#define  M3_TCSSI1_INT                  56  /* ���ߴ���ssi1�ж� */
#define  M3_USB3_PME_INT                57  /* USB3_PD_PME_INT | USB3_PMU_PME_INT ,USB3��power management event */
#define  M3_MIPI_INT                    58  /* MIPI�ж� */
#define  M3_HS_UART_INT                 59  /* ���ٴ���0�ж� */
#define  M3_UART0_INT                   60  /* ����0�ж� */
#define  M3_UART1_INT                   61  /* ����1�ж� */
#define  M3_UART2_INT                   62  /* ����2�ж� */
#define  M3_UART3_INT                   63  /* ����3�ж� */
#define  M3_NANDC_INT                   64  /* Nandflash�������ж� */
#define  M3_MMC0_INT                    65  /* MobileStorageController0�ж� */
#define  M3_MMC1_INT                    66  /* MobileStorageController1�ж� */
#define  M3_RESERVE3                    67  /* ���� */
#define  M3_SDCC_INT                    68  /* SDIO slave�ж� */
#define  M3_I2C0_INT                    69  /* I2C0�ж� */
#define  M3_GPIO_GROUP0_INT             70  /* M3 GPIO group 0 �����ж�,��ϵͳ������m3_gpio0_en����ʹ��GPIO0��32������ж� */
#define  M3_GPIO_GROUP1_INT             71  /* M3 GPIO group 1 �����ж�,��ϵͳ������m3_gpio1_en����ʹ��GPIO1��32������ж� */
#define  M3_GPIO_GROUP2_INT             72  /* M3 GPIO group 2 �����ж�,��ϵͳ������m3_gpio2_en����ʹ��GPIO2��32������ж� */
#define  M3_GPIO_GROUP3_INT             73  /* M3 GPIO group 3 �����ж�,��ϵͳ������m3_gpio3_en����ʹ��GPIO3��32������ж� */
#define  M3_I2C1_INT                    74  /* I2C1�ж� */
#define  M3_IPCM_APP_INT0               75  /* IPC APP�ж� 0*/
#define  M3_IPCM_APP_INT1               76  /* IPC APP�ж� 1*/
#define  M3_EDMAC_INT0                  77  /* EDMAC�ж�0 */
#define  M3_EDMAC_INT1                  78  /* EDMAC�ж�1 */
#define  M3_AMON_INT                    79  /* AMON_FAST_INT|AMON_SOC_INT */
#define  M3_HSIC_INT                    80  /* HSIC�ж� */
#define  M3_APPA9_PMUIREQ_INT           81  /* APPA9 PMU �ж� */
#define  M3_MDMA9_PMUIREQ_INT           82  /* MDMA9 PMU �ж� */
#define  M3_HiFi_GPIO2_INT              83  /* HIFI GPIO[2] */
#define  M3_DSP0_GPIO2_INT              84  /* DSP0 GPIO[2] */
#define  M3_PMU_INT                     85  /* PMU�жϣ����Կ���ϵͳ����������ȡ�� */
#define  M3_USB3_OTG_INT                86  /* USB3 OTG �ж� */
#define  M3_X2H_X2P_ERR                 87  /* dw_axi_x2h��dw_axi_x2p�ⲿ��ַ��������ж� */
#define  M3_AXI_ERR                     88  /* dw_axi_cpu/glb/bbphy/dsp�ŵĵ�ַ��������ж� */
#define  M3_USBOTG_BC_INT               89  /* bc_ctrl�ж� */
#define  M3_SYS_CONTROL_INT4            90  /* ���ж�4��ϵͳ���������� */
#define  M3_SYS_CONTROL_INT5            91  /* ���ж�5��ϵͳ���������� */
#define  M3_TIMER16_INT                 92  /* TIMER16�ж� */
#define  M3_TIMER17_INT                 93  /* TIMER17�ж� */
#define  M3_TIMER18_INT                 94  /* TIMER18�ж� */
#define  M3_TIMER19_INT                 95  /* TIMER19�ж� */
#define  M3_TIMER20_INT                 96  /* TIMER20�ж� */
#define  M3_TIMER21_INT                 97  /* TIMER21�ж� */
#define  M3_TIMER22_INT                 98  /* TIMER22�ж� */
#define  M3_TIMER23_INT                 99  /* TIMER23�ж� */
#define  M3_RESERVE6                    100 /* ���� */
#define  M3_CPU_AXI_DLOCK_INT           101 /* dw_axi_cpu���������ж� */
#define  M3_GLb_AXI_DLOCK_INT           102 /* dw_axi_glb���������ж� */
#define  M3_MST_AXI_DLOCK_INT           103 /* dw_axi_mst���������ж� */
#define  M3_AMON_AXI_DLOCK_INT          104 /* dw_axi_amon���������ж� */
#define  M3_BBPHY_AXI_DLOCK_INT         105 /* dw_axi_bbphy���������ж� */
#define  M3_SDCC_HCLK_WKUP_INT          106 /* SDIO slave�����ж�,�����ش���������Ҫ���ж�Դ��IP�Զ����ߺ����ͣ� */
#define  M3_TDS_STU_ARM_INT             107 /* TDS_BBP_OFF��ARM�ж� */
#define  M3_RESERVE7                    108 /* ���� */
#define  M3_TDS_DRX_ARM_CLKSWITCH_INT   109 /* TDS_BBP_ON��ARM�ж� */
#define  M3_TDS_DRX_ARM_WAKEUP_INT      110 /* TDS_BBP_ON��ARM�ж� */
#define  M3_WAKEUP_INT                  111 /* ��ϻ����жϣ��ж����͡��������ͺ��Ƿ���Ҫ����ж�Դ��Ҫ��Դ���ж����͡�����ο���M3�����ж�Դ�������� */
#define  M3_USBOTG_PHY_INT              112 /* ��M3��USBOTG_PHY_INT */
#define  M3_APPA9_L2CC_INT              113 /* APPA9 L2����ж� */
#define  M3_IPCM_MDM_INT0               114 /* IPC MDM�ж� 0*/
#define  M3_SDCC_PULL_INT               115 /* sdcc data3�����жϣ��ж�Դ���ж�״̬��ϵͳ���������� */
#define  M3_USB3_INT                    116 /* USB3�ж� */
#define  M3_IPCM_MDM_INT1               117 /* IPC MDM�ж� 1*/
#define  M3_APPA9_ARM_WD_SRST_REQ       118 /* APP A9��λ���� */
#define  M3_MODA9_ARM_WD_SRST_REQ       119 /* Modem A9��λ���� */
#define  M3_W_ARM_INT_02                120 /* WBBP_ON��ARM�ж� */
#define  M3_W_ARM_INT_03                121 /* WBBP_ON��ARM�ж� */
#define  M3_OTDOA_INT                   122 /* WBBP_OFF��ARM�ж� */
#define  M3_CTU_INT_W                   123 /* CTU BBP_OFF��ARM�ж� */
#define  M3_CTU_INT_G1                  124 /* CTU BBP_OFF��ARM�ж� */
#define  M3_CTU_INT_G2                  125 /* CTU BBP_OFF��ARM�ж� */
#define  M3_CTU_INT_LTE                 126 /* CTU BBP_OFF��BBE16�ж� */
#define  M3_CTU_INT_TDS                 127 /* CTU BBP_OFF��BBE16�ж� */
#define  M3_PCIE0_LINK_DOWN_INT         128 /* PCIE ������ LINK DOWN �ж� */
#define  M3_PCIE0_EDMA_INT              129 /* PCIE ������ EDMA �ж� */
#define  M3_PCIE0_PM_INT                130 /* PCIE ������ PM �ж� */
#define  M3_PCIE0_RADM_INTA             131 /* PCIE ������ RADM �ж� A */
#define  M3_PCIE0_RADM_INTB             132 /* PCIE ������ RADM �ж� B */
#define  M3_PCIE0_RADM_INTC             133 /* PCIE ������ RADM �ж� C */
#define  M3_PCIE0_RADM_INTD             134 /* PCIE ������ RADM �ж� D */
#define  M3_RESERVE9                    135 /* ���� */
#define  M3_RESERVE10                   136 /* ���� */
#define  M3_EDMAC_CH4_INT0              137 /* 4ͨ��EDMAC�ж�0 */
#define  M3_EDMAC_CH4_INT1              138 /* 4ͨ��EDMAC�ж�1 */
#define  M3_EDMAC_CH4_INT2              139 /* 4ͨ��EDMAC�ж�2 */
#define  M3_IPF_INT0                    140 /* ���� */
#define  M3_IPF_INT1                    141 /* ���� */
#define  M3_SOCP_INT0                   142 /* SOCP Core0�ж�*/
#define  M3_SOCP_INT1                   143 /* SOCP Core1�ж� */

/* for setting wake_src in acore/ccore */
#define M3_DRX_TIMER_INT M3_TIMER23_INT

#ifdef __cplusplus
}
#endif

#endif /* __SOC_INTERRUPTS_M3_H__ */

