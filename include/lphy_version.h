

#ifndef __LPHY_VERSION_H__
#define __LPHY_VERSION_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "TLPhyInterface.h"


/*
   ���汾�����һ��32λ��, ��Ҫ����������
    2)����ֱ�����ɰ汾�ŵĺ�:
        MAJOR   : LPHY_HI6920ES(0xE0) or LPHY_HI6930CS(0xC0)
        MINOR   : LPHY_FPGA_P500(0xF0) or LPHY_ASIC(0xA0)
        NUMBER  : B001,B002,.....,B060,.....
    2)����LPHY_HI6920_CS_FPGA_P500�����ֱ�ʾΪ:
        0xC0F0B001----> CS�汾FPGAƽ̨B001�汾
*/

#define PHY_ON		(0x1)
#define PHY_OFF		(0x0)


#define LPHY_VERSION(MAJOR,MINOR,NUMBER)  (((MAJOR)<<24) | ((MINOR)<<16) | NUMBER)
#define LPHY_MAJOR_VERSION(x)             (((x) >> 24) & 0x00FF)
#define LPHY_MINOR_VERSION(x)             (((x) >> 16) & 0x00FF)
#define LPHY_NUMBER_VERSION(x)            (((x) >>  0) & 0xFFFF)

/*оƬ����*/
#if 	defined(LPHY_CHIP_BB_6930ES)
    #define LPHY_HI6930CS           (0xE0)
    #define CHIP_BB_VERSION         LPHY_HI6930CS
#elif 	defined(LPHY_CHIP_BB_6930CS)
    #define LPHY_HI6930CS           (0xC0)
    #define CHIP_BB_VERSION         LPHY_HI6930CS
#else
    #error "sorry, this is not a supported baseband version, please include product_config.h"
#endif

/*��������*/
#if defined(TL_PHY_FPGA_P500)
    #define LPHY_FPGA_P500          		(0xF0)
    #define LPHY_BOARD_VERSION      		(LPHY_FPGA_P500)
	#error "sorry, not support P500 board"
#elif defined(TL_PHY_FPGA_P531)
    #define LPHY_FPGA_P530          		(0xF3)
    #define LPHY_BOARD_VERSION      		(LPHY_FPGA_P530)
	#define LPHY_FEATURE_LCS_SWITCH			PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH		PHY_OFF
	#define LPHY_FEATURE_ONE_XO_SWITCH		PHY_ON
	#define LPHY_FEATURE_MAX_CARRIER_NUM	1	
#elif (defined(TL_PHY_ASIC_HI6930) || defined(BOARD_ASIC_BIGPACK) ||defined(TL_PHY_SFT))
    #define LPHY_ASIC_B720
    #define LPHY_ASIC               		(0xA0)
    #define LPHY_BOARD_VERSION      		(LPHY_ASIC)
	#define LPHY_FEATURE_LCS_SWITCH			PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH		PHY_ON
	#define LPHY_FEATURE_ONE_XO_SWITCH		PHY_OFF
	#define LPHY_FEATURE_MAX_CARRIER_NUM	2	
    #define BALONG_FEATURE_LTE_DT
    #define SG_REPORT
    
	
	#if defined(TL_PHY_ASIC_HI6930)
		#define LPHY_IN_FACT_ASIC_BOARD
	#endif
#elif (defined(TL_PHY_ASIC_K3V3) || defined(TL_PHY_K3V3_SFT))
	#define LPHY_ASIC_K3V3
    #define LPHY_ASIC               		(0xA3)
    #define LPHY_BOARD_VERSION      		(LPHY_ASIC)

	#define LPHY_FEATURE_LCS_SWITCH			PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH		PHY_ON
	#define LPHY_FEATURE_ONE_XO_SWITCH		PHY_OFF
	#define LPHY_FEATURE_MAX_CARRIER_NUM	2	
    #define BALONG_FEATURE_LTE_DT
    #define SG_REPORT
    #if defined(TL_PHY_ASIC_K3V3)
        #define LPHY_IN_FACT_ASIC_BOARD
    #endif
	
#elif (defined(TL_PHY_ASIC_V810) || defined(TL_PHY_V810_SFT))

	#define LPHY_ASIC_V810
    #define LPHY_ASIC               		(0xA8)
    #define LPHY_BOARD_VERSION      		(LPHY_ASIC)

	#define LPHY_FEATURE_LCS_SWITCH			PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH		PHY_OFF
	#define LPHY_FEATURE_ONE_XO_SWITCH		PHY_ON
	#define LPHY_FEATURE_MAX_CARRIER_NUM	1

    #if defined(TL_PHY_ASIC_V810)
		#define LPHY_IN_FACT_ASIC_BOARD
	#endif
	#define SG_REPORT
#elif (defined(TL_PHY_ASIC_V711) || defined(TL_PHY_V711_SFT))

	#define LPHY_ASIC_V711
	#define LPHY_ASIC               		(0xA7)
    #define LPHY_BOARD_VERSION      		(LPHY_ASIC)

	#define LPHY_FEATURE_LCS_SWITCH			PHY_OFF
	#define LPHY_FEATURE_EMBMS_SWITCH		PHY_OFF
	#define LPHY_FEATURE_ONE_XO_SWITCH		PHY_OFF
	#define LPHY_FEATURE_MAX_CARRIER_NUM	1
    #define LPHY_FEATURE_MAX_INTER_EMU_NUM  6
    #if defined(TL_PHY_ASIC_V711)
		#define LPHY_IN_FACT_ASIC_BOARD
	#endif
	#define SG_REPORT
    

#else
    #error "sorry, this is not a supported asic version, please include product_config.h"
#endif

#if (PHY_ON == LPHY_FEATURE_LCS_SWITCH)
	#define BALONGV7_FEATURE_LCS_ENABLE
	#define BALONGV7_FEATURE_LCS
#else
	#define BALONGV7_FEATURE_LCS_DISABLE	
#endif

#if (PHY_ON == LPHY_FEATURE_EMBMS_SWITCH)
	#define BALONGV7_FEATURE_EMBMS_ENABLE
	#define BALONGV7_FEATURE_EMBMS
#else
	#define BALONGV7_FEATURE_EMBMS_DISABLE
#endif

#if (PHY_ON == LPHY_FEATURE_ONE_XO_SWITCH)
	#define LPHY_FEATURE_ONE_XO_ENABLE
	#define LPHY_FEATURE_ONE_XO
#else
	#define LPHY_FEATURE_ONE_XO_DISABLE
#endif

#if   (1 == LPHY_FEATURE_MAX_CARRIER_NUM)
	#define LPHY_FEATURE_CA_DISABLE
#elif (2 <= LPHY_FEATURE_MAX_CARRIER_NUM)
	#define LPHY_FEATURE_CA_ENABLE
#else 
	#error "sorry, error sopport carrier number"
#endif


/*RF���Ͷ���*/

#define LPHY_MAIN_VERSION      LPHY_VERSION(CHIP_BB_VERSION, LPHY_BOARD_VERSION, 0xB001)

/*����CHIP_BB_6920CS porting�汾�ںа��Ĳ���ȫ���������Ҫ���쳣�����ų�һ���ּĴ���������*/

#if (defined(CHIP_BB_6920CS) && defined(BOARD_SFT))
    #define LPHY_HI6930CS_PORTING
#endif


/*
    LPHY�ڲ�ǿ�ƽ�ֹʹ�ö�����Ĳ�Ʒ��
*/
#undef BOARD_FPGA_P500
#undef BOARD_ASIC
#undef BOARD_ASIC_BIGPACK
#undef BOARD_SFT
#undef CHIP_BB_6920CS
#undef CHIP_BB_6920ES
#undef CHIP_RFIC_6360V200
#undef CHIP_RFIC_6360V210
#undef CHIP_RFIC_9361


/*�汾�����ַ���*/
#define LPHY_TIP "Hisilicon balongV7R2 GUTL lphy develop group!"


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __LPHY_VERSION_H__ */
