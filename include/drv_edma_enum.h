
/*��ͷ�ļ�רΪTLdsp��Hifi�ṩ������ģ��Ӧ����drv_edma.h*/
#ifndef __DRV_EDMA_ENUM_H__
#define __DRV_EDMA_ENUM_H__

#define	EDMA_CH16_0	    0
#define	EDMA_CH16_1	    1
#define	EDMA_CH16_2	    2
#define	EDMA_CH16_3	    3
#define	EDMA_CH16_4	    4
#define	EDMA_CH16_5	    5
#define	EDMA_CH16_6	    6
#define	EDMA_CH16_7	    7
#define	EDMA_CH16_8	    8
#define	EDMA_CH16_9	    9
#define	EDMA_CH16_10	10
#define	EDMA_CH16_11	11
#define	EDMA_CH16_12	12
#define	EDMA_CH16_13	13
#define	EDMA_CH16_14	14
#define	EDMA_CH16_15	15
#ifdef HI_EDMA_CH4_REGBASE_ADDR_VIRT
#define	EDMA_CH4_0	    16
#define	EDMA_CH4_1	    17
#define	EDMA_CH4_2	    18
#define	EDMA_CH4_3	    19
#define	EDMA_CH_END	    20
#else
#define	EDMA_CH4_0	    (0x1000)
#define	EDMA_CH4_1	    (0x1000)
#define	EDMA_CH4_2	    (0x1000)
#define	EDMA_CH4_3	    (0x1000)
#define	EDMA_CH_END	    16
#endif

#define	EDMA_CH_LDSP_API_USED_0 EDMA_CH16_0
#define	EDMA_CH_LDSP_API_USED_1 EDMA_CH16_1
#define	EDMA_CH_LDSP_LCS_SDR    EDMA_CH16_2
#define	EDMA_CH_LDSP_CSU_SDR    EDMA_CH16_3
#define	EDMA_CH_LDSP_EMU_SDR    EDMA_CH16_4
#define	EDMA_CH_LDSP_NV_LOADING EDMA_CH16_5
/****arm��ldsp����****�͹��ı��ݻָ�  m2m */
#define	EDMA_CH_LOAD_LDSP_TCM  EDMA_CH_LDSP_API_USED_0
#define	EDMA_CH_LOAD_TDSP_TCM  EDMA_CH_LDSP_API_USED_1
/****gudsp��ldsp����****GU CQI���� �� LDSP LCS */
#define	EDMA_CH_GUDSP_MEMORY_3  EDMA_CH_LDSP_LCS_SDR

/*EDMA_CH_GUDSP_MEMORY_9  ==  BBP_GRIF_PHY��
GUDSPʵ��BBP����������У׼ ����GU BBP DEBUG��������
����ͨ����Ϊ M2M */
#define	EDMA_CH_GUDSP_MEMORY_9  EDMA_CH16_6
#define	EDMA_CH_GUDSP_MEMORY_7  EDMA_CH16_7
/****gudsp��gudsp����****GU DSP������ GU AHB���� */
#define	EDMA_CH_GUDSP_MEMORY_8  EDMA_CH_GUDSP_MEMORY_7


/* HIFI SIO �շ� */
#define	EDMA_CH_HIFI_SIO_TX     EDMA_CH16_8
#define	EDMA_CH_HIFI_SIO_RX     EDMA_CH16_9

/* SIM��0 ���պͷ��� / SIM��1 ���պͷ��� */
#define	EDMA_CH_DRV_SIM_0       EDMA_CH16_10
#define	EDMA_CH_DRV_SIM_1       EDMA_CH4_0
/*���ٴ��ڷ���/����ʹ��	���������������� */
#define	EDMA_CH_HSUART_TX       EDMA_CH4_1 //EDMA_CH16_12
#define	EDMA_CH_HSUART_RX       EDMA_CH4_2 //EDMA_CH16_13
/* SPI1���ͣ�ˢLCD�� */
#define	EDMA_CH_DRV_LCD           EDMA_CH16_11//EDMA_CH4_0 //EDMA_CH16_14
/* ��������axi_monitor�Ĳɼ����� */
#define	EDMA_CH_DRV_AXIMON      EDMA_CH4_3 //EDMA_CH16_15

#define	EDMA_CH_GUDSP_MEMORY_1  EDMA_CH16_12 //EDMA_CH4_0
#define	EDMA_CH_GUDSP_MEMORY_2  EDMA_CH16_13 //EDMA_CH4_1
#define	EDMA_CH_GUDSP_MEMORY_4  EDMA_CH16_14 //EDMA_CH4_2
#define	EDMA_CH_GUDSP_MEMORY_6  EDMA_CH16_15 //EDMA_CH4_3

#endif

