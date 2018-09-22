

/************************************************************
                     ��������ģ���ͷ�ļ�
************************************************************/
/************************************************************
                               �궨��
************************************************************/

/************************************************************
                             ���ݽṹ����
************************************************************/

/************************************************************
                             �ӿں�������
 ************************************************************/

#ifndef __TL_PHY_INTERFACE_H__
#define __TL_PHY_INTERFACE_H__

#include "product_config.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */




#if (defined(MS_VC6_PLATFORM))
    #include "sim.h"

    #define MASTER_TCM_ADDR_OFFSET                  (0x0)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)


    #ifdef COMPILE_PUBLIC_IMAGE
    /*�������鶨��*/
    extern UINT32  gulArrMailxBox[];                /*400k�ֽڴ�С*/

    /*HARQ�����������С*/
    extern UINT32  gulArrHarqBuf[];                 /*400k�ֽڴ�С*/

    /*ģ������*/
    #define LPHY_SHARE_MEM_BASE_ADDR                ((UINT32)&gulArrMailxBox[0])

    /*ģ��HARQ������*/
    #define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           ((UINT32)&gulArrHarqBuf[0])
    #else
    extern REG_BASE_ADDR_STRU gstRegBaseAddr;
    /*ģ������*/
    #define LPHY_SHARE_MEM_BASE_ADDR                gstRegBaseAddr.gulArrMailxBoxAddr//((UINT32)&gulArrMailxBox[0])

    /*ģ��HARQ������*/
    #define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           gstRegBaseAddr.gulArrHarqBufAddr//((UINT32)&gulArrHarqBuf[0])
    #endif

    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)


    #define LPHY_CHIP_BB_6930CS
    #define LPHY_RFIC_HI6361

/* ����ַ����*/
#elif defined(TL_PHY_FPGA_P500)

    #define MASTER_TCM_ADDR_OFFSET  				(0x0 - 0xf000000)
    #define SLAVE_TCM_ADDR_OFFSET   				(0x0 - 0xd000000)

    /*���乲����ض���*/
    #define LPHY_SHARE_MEM_BASE_ADDR                (0xE0FC0000UL)
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x0F000000UL)

    /*HARQ����������ַ����*/
    #define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           (0x52680000UL)
    #define LPHY_LMAC_TIMER_LOCK_ADDR               (0x5270E094UL)
    #define LPHY_LMAC_FRAME_ADDR                    (0x5270E014UL)
    #define LPHY_LMAC_SUB_FRAME_ADDR                (0x5270E018UL)

    /*���ص�ַ����BSP��*/
    #define LPHY_CORE0_PUB_DTCM_LOAD_ADDR           (0xE0FC0000UL) /*P500 bbe16 core0*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_ADDR           (0xE1000000UL) /*P500 bbe16 core0*/
	#define LPHY_CORE1_PUB_DTCM_LOAD_ADDR           (0xE2FC0000UL) /*P500 bbe16 core1*/
    #define LPHY_CORE1_PUB_ITCM_LOAD_ADDR           (0xE3000000UL) /*P500 bbe16 core1*/

    /*ӳ���ַ����vxworks ӳ��ʹ��*/
    #define LPHY_CORE0_TCM_MAP_BASE_ADDR            (LPHY_CORE0_PUB_DTCM_LOAD_ADDR)
	#define LPHY_CORE1_TCM_MAP_BASE_ADDR            (LPHY_CORE1_PUB_DTCM_LOAD_ADDR)
	#define LPHY_CORE0_TCM_MAP_SIZE                 (256*1024 + 256*1024) /*256K + 256K*/
    #define LPHY_CORE1_TCM_MAP_SIZE                 (256*1024 + 256*1024) /*256K + 256K*/

	#define LPHY_CHIP_BB_6930ES
	#define LPHY_RFIC_HI6361

#elif defined(TL_PHY_FPGA_P531)

	#define MASTER_TCM_ADDR_OFFSET  				(0x01000000)
	#define SLAVE_TCM_ADDR_OFFSET   				(0x02000000)

	#define BBE_TCM_IN_SOC_SAPCE(x) 				(MASTER_TCM_ADDR_OFFSET + (x))

	/*���乲����ض���*/
	#define LPHY_SHARE_MEM_BASE_ADDR                BBE_TCM_IN_SOC_SAPCE(LPHY_PUB_DTCM_BASE)
	#define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0xFF000000UL)

	/*HARQ����������ַ����*/
	#define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           (0x20680000UL)
	#define LPHY_LMAC_TIMER_LOCK_ADDR               (0x2070E094UL)
	#define LPHY_LMAC_FRAME_ADDR                    (0x2070E014UL)
	#define LPHY_LMAC_SUB_FRAME_ADDR                (0x2070E018UL)



	/*���ص�ַ����BSP��*/
	#define LPHY_CORE0_UNI_DTCM_LOAD_ADDR           BBE_TCM_IN_SOC_SAPCE(LPHY_PUB_DTCM_BASE) 	/*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_UNI_DTCM_LOAD_SIZE           (LPHY_UNI_DTCM_SIZE) 					 	/*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_UNI_ITCM_LOAD_ADDR			BBE_TCM_IN_SOC_SAPCE(LPHY_PUB_ITCM_BASE) 	/*P530 bbe16 UNIPHY ITCM*/
	#define LPHY_CORE0_UNI_ITCM_LOAD_SIZE			(LPHY_UNI_ITCM_SIZE) 						/*P530 bbe16 UNIPHY DTCM*/


	#define LPHY_CORE0_PUB_DTCM_LOAD_ADDR           BBE_TCM_IN_SOC_SAPCE(LPHY_PUB_DTCM_BASE) 	/*P530 bbe16 UNIPHY DTCM*/ /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_PUB_DTCM_LOAD_SIZE           (LPHY_PUB_DTCM_SIZE) 						/*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_ADDR           BBE_TCM_IN_SOC_SAPCE(LPHY_PUB_ITCM_BASE) 	/*P530 bbe16 PUBPHY ITCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_SIZE           (LPHY_PUB_ITCM_SIZE) 						/*P530 bbe16 PUBPHY DTCM*/

	#define LPHY_CORE0_MOD_DTCM_LOAD_ADDR			BBE_TCM_IN_SOC_SAPCE(LPHY_PRV_DTCM_BASE) 	/*P530 bbe16 MODPHY DTCM*/
	#define LPHY_CORE0_MOD_DTCM_LOAD_SIZE			(LPHY_PRV_DTCM_SIZE) 						/*P530 bbe16 MODPHY DTCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_ADDR           BBE_TCM_IN_SOC_SAPCE(LPHY_PRV_ITCM_BASE) 	/*P530 bbe16 MODPHY ITCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_SIZE           (LPHY_PRV_ITCM_SIZE) 						/*P530 bbe16 MODPHY DTCM*/


	/*ӳ���ַ����vxworks ӳ��ʹ��*/
	#define LPHY_CORE_TCM_MAP_BASE_ADDR             (LPHY_CORE0_PUB_DTCM_LOAD_ADDR)
	#define LPHY_CORE_TCM_MAP_SIZE                  (LPHY_UNI_DTCM_SIZE + LPHY_UNI_ITCM_SIZE)

	#define LPHY_CHIP_BB_6930ES
	#define LPHY_RFIC_HI6361
#elif defined(CHIP_BB_HI6210)

    //#error "goto CHIP_BB_HI6210"

	#define MASTER_TCM_ADDR_OFFSET  				(0x00000000)
	#define SLAVE_TCM_ADDR_OFFSET   				(0x00000000)
   	#define BBE_TCM_IN_SOC_SAPCE(x) 				(MASTER_TCM_ADDR_OFFSET + (x))


	/*���乲����ض���*/
	#define LPHY_SHARE_MEM_BASE_ADDR                BBE_TCM_IN_SOC_SAPCE(LPHY_PUB_DTCM_BASE) //!!!!
	#define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL) //honghuiyong

	/*HARQ����������ַ����*/
	#define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           (0xFD680000UL)
	#define LPHY_LMAC_TIMER_LOCK_ADDR               (0xFD70E094UL)
	#define LPHY_LMAC_FRAME_ADDR                    (0xFD70E014UL)
	#define LPHY_LMAC_SUB_FRAME_ADDR                (0xFD70E018UL)

	#define LPHY_CORE0_UNI_DTCM_LOAD_ADDR           BBE_TCM_IN_SOC_SAPCE(LPHY_PUB_DTCM_BASE) 	/*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_UNI_DTCM_LOAD_SIZE           (LPHY_UNI_DTCM_SIZE) 					 	/*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_UNI_ITCM_LOAD_ADDR			BBE_TCM_IN_SOC_SAPCE(LPHY_PUB_ITCM_BASE) 	/*P530 bbe16 UNIPHY ITCM*/
	#define LPHY_CORE0_UNI_ITCM_LOAD_SIZE			(LPHY_UNI_ITCM_SIZE) 						/*P530 bbe16 UNIPHY DTCM*/


	#define LPHY_CORE0_PUB_DTCM_LOAD_ADDR           BBE_TCM_IN_SOC_SAPCE(LPHY_PUB_DTCM_BASE) 	/*P530 bbe16 UNIPHY DTCM*/ /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_PUB_DTCM_LOAD_SIZE           (LPHY_PUB_DTCM_SIZE) 						/*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_ADDR           BBE_TCM_IN_SOC_SAPCE(LPHY_PUB_ITCM_BASE) 	/*P530 bbe16 PUBPHY ITCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_SIZE           (LPHY_PUB_ITCM_SIZE) 						/*P530 bbe16 PUBPHY DTCM*/

	#define LPHY_CORE0_MOD_DTCM_LOAD_ADDR			BBE_TCM_IN_SOC_SAPCE(LPHY_PRV_DTCM_BASE) 	/*P530 bbe16 MODPHY DTCM*/
	#define LPHY_CORE0_MOD_DTCM_LOAD_SIZE			(LPHY_PRV_DTCM_SIZE) 						/*P530 bbe16 MODPHY DTCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_ADDR           BBE_TCM_IN_SOC_SAPCE(LPHY_PRV_ITCM_BASE) 	/*P530 bbe16 MODPHY ITCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_SIZE           (LPHY_PRV_ITCM_SIZE) 						/*P530 bbe16 MODPHY DTCM*/


	/*ӳ���ַ����vxworks ӳ��ʹ��*/
	#define LPHY_CORE_TCM_MAP_BASE_ADDR             (LPHY_CORE0_PUB_DTCM_LOAD_ADDR)
	#define LPHY_CORE_TCM_MAP_SIZE                  (512*1024 + 512*1024) /*256K + 256K*/

	#define LPHY_CHIP_BB_6930ES
	#define LPHY_RFIC_HI6361
#elif (defined(TL_PHY_ASIC_HI6930) || defined(TL_PHY_ASIC_BIGPACK) ||defined(TL_PHY_SFT))

    #define MASTER_TCM_ADDR_OFFSET                  (0x0)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)

    /*���乲����ض���*/
    #define LPHY_SHARE_MEM_BASE_ADDR                (0x48f80000UL) /*128K+256K*/
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)

    /*HARQ����������ַ����*/
    #define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           (0x20680000UL)
    #define LPHY_LMAC_TIMER_LOCK_ADDR               (0x2070E094UL)
    #define LPHY_LMAC_FRAME_ADDR                    (0x2070E014UL)
    #define LPHY_LMAC_SUB_FRAME_ADDR                (0x2070E018UL)

	/*���ص�ַ����BSP��*/
	#define LPHY_CORE0_UNI_DTCM_LOAD_ADDR           (0x48f80000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_UNI_DTCM_LOAD_SIZE           (0x00080000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_PUB_DTCM_LOAD_ADDR           (0x48f80000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_PUB_DTCM_LOAD_SIZE           (0x0003f000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_MOD_DTCM_LOAD_ADDR           (0x48fbf000UL) /*P530 bbe16 MODPHY DTCM*/
	#define LPHY_CORE0_MOD_DTCM_LOAD_SIZE           (0x00040000UL) /*P530 bbe16 MODPHY DTCM*/

	#define LPHY_CORE0_UNI_ITCM_LOAD_ADDR           (0x49000000UL) /*P530 bbe16 UNIPHY ITCM*/
	#define LPHY_CORE0_UNI_ITCM_LOAD_SIZE           (0x00080000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_ADDR           (0x48fff000UL) /*P530 bbe16 PUBPHY ITCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_SIZE           (0x00041000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_ADDR           (0x49040000UL) /*P530 bbe16 MODPHY ITCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_SIZE           (0x00040000UL) /*P530 bbe16 MODPHY DTCM*/


	/*ӳ���ַ����vxworks ӳ��ʹ��*/
	#define LPHY_CORE_TCM_MAP_BASE_ADDR             (LPHY_CORE0_PUB_DTCM_LOAD_ADDR)
	#define LPHY_CORE_TCM_MAP_SIZE                  (512*1024 + 512*1024) /*256K + 256K*/

	#define LPHY_CHIP_BB_6930CS
	#define LPHY_RFIC_HI6361

#elif (defined(TL_PHY_ASIC_K3V3) || defined(TL_PHY_K3V3_SFT))


    #define MASTER_TCM_ADDR_OFFSET                  (0x0)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)

    /*���乲����ض���*/
    #define LPHY_SHARE_MEM_BASE_ADDR                (0xe2780000UL) /*128K+256K*/
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)

    /*HARQ����������ַ����*/
    #define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           (0xE1680000UL)
    #define LPHY_LMAC_TIMER_LOCK_ADDR               (0xE170E094UL)
    #define LPHY_LMAC_FRAME_ADDR                    (0xE170E014UL)
    #define LPHY_LMAC_SUB_FRAME_ADDR                (0xE170E018UL)

	/*���ص�ַ����BSP��*/
	#define LPHY_CORE0_UNI_DTCM_LOAD_ADDR           (0xe2780000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_UNI_DTCM_LOAD_SIZE           (0x00080000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_PUB_DTCM_LOAD_ADDR           (0xe2780000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_PUB_DTCM_LOAD_SIZE           (0x0003f000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_MOD_DTCM_LOAD_ADDR           (0xe27bf000UL) /*P530 bbe16 MODPHY DTCM*/
	#define LPHY_CORE0_MOD_DTCM_LOAD_SIZE           (0x00040000UL) /*P530 bbe16 MODPHY DTCM*/

	#define LPHY_CORE0_UNI_ITCM_LOAD_ADDR           (0xe2800000UL) /*P530 bbe16 UNIPHY ITCM*/
	#define LPHY_CORE0_UNI_ITCM_LOAD_SIZE           (0x00080000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_ADDR           (0xe27ff000UL) /*P530 bbe16 PUBPHY ITCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_SIZE           (0x00041000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_ADDR           (0xe2840000UL) /*P530 bbe16 MODPHY ITCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_SIZE           (0x00040000UL) /*P530 bbe16 MODPHY DTCM*/


	/*ӳ���ַ����vxworks ӳ��ʹ��*/
	#define LPHY_CORE_TCM_MAP_BASE_ADDR             (LPHY_CORE0_PUB_DTCM_LOAD_ADDR)
	#define LPHY_CORE_TCM_MAP_SIZE                  (512*1024 + 512*1024) /*256K + 256K*/

	#define LPHY_CHIP_BB_6930CS
	#define LPHY_RFIC_HI6361
#elif defined(TL_PHY_ASIC_V711)
    #define MASTER_TCM_ADDR_OFFSET                  (0x0)
    #define SLAVE_TCM_ADDR_OFFSET                   (MASTER_TCM_ADDR_OFFSET)

    /*���乲����ض���*/
    #define LPHY_SHARE_MEM_BASE_ADDR                (0x48f80000UL) /*128K+256K*/
    #define LPHY_DSP_ARM_RAM_BASE_OFFSET            (0x00000000UL)

    /*HARQ����������ַ����*/
    #define LPHY_LMAC_HARQ_BUFF_BASE_ADDR           (0x20680000UL)
    #define LPHY_LMAC_TIMER_LOCK_ADDR               (0x2070E094UL)
    #define LPHY_LMAC_FRAME_ADDR                    (0x2070E014UL)
    #define LPHY_LMAC_SUB_FRAME_ADDR                (0x2070E018UL)

	/*���ص�ַ����BSP��*/
	#define LPHY_CORE0_UNI_DTCM_LOAD_ADDR           (0x48f80000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_UNI_DTCM_LOAD_SIZE           (0x00070000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_PUB_DTCM_LOAD_ADDR           (0x48f80000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_PUB_DTCM_LOAD_SIZE           (0x00040000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_MOD_DTCM_LOAD_ADDR           (0x48fc0000UL) /*P530 bbe16 MODPHY DTCM*/
	#define LPHY_CORE0_MOD_DTCM_LOAD_SIZE           (0x00030000UL) /*P530 bbe16 MODPHY DTCM*/

	#define LPHY_CORE0_UNI_ITCM_LOAD_ADDR           (0x49000000UL) /*P530 bbe16 UNIPHY ITCM*/
	#define LPHY_CORE0_UNI_ITCM_LOAD_SIZE           (0x00070000UL) /*P530 bbe16 UNIPHY DTCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_ADDR           (0x49000000UL) /*P530 bbe16 PUBPHY ITCM*/
	#define LPHY_CORE0_PUB_ITCM_LOAD_SIZE           (0x00038000UL) /*P530 bbe16 PUBPHY DTCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_ADDR           (0x49038000UL) /*P530 bbe16 MODPHY ITCM*/
	#define LPHY_CORE0_MOD_ITCM_LOAD_SIZE           (0x00038000UL) /*P530 bbe16 MODPHY DTCM*/


	/*ӳ���ַ����vxworks ӳ��ʹ��*/
	#define LPHY_CORE_TCM_MAP_BASE_ADDR             (LPHY_CORE0_PUB_DTCM_LOAD_ADDR)
	#define LPHY_CORE_TCM_MAP_SIZE                  (512*1024 + 512*1024) /*256K + 256K*/

	#define LPHY_CHIP_BB_6930CS
	#define LPHY_RFIC_HI6361

#else

    #error "sorry, this is not a supported board version, please include product_config.h"

#endif

typedef enum __LPHY_WORKING_MODE_ENUM__
{
    LPHY_WORKING_MODE_RTT = 0,
    LPHY_WORKING_MODE_SINGLE_MODE  = 1,
    LPHY_WORKING_MODE_MULTI_MODE   = 2,
    LPHY_WORKING_MODE_DUO_SIM_MODE = 3,
}LPHY_WORKING_MODE_ENUM;

typedef enum __LPHY_RTT_LPC_MODE_ENUM__
{
	POWER_SAVING_NULL,
	POWER_SAVING_SNOOZE,
	POWER_SAVING_DEEP_SLEEP
}LPHY_RTT_LPC_MODE_ENUM;


typedef struct __MULTIMODE_BB_STARTUP_MODE_IND_STRU__
{
	unsigned int bLteStartInd	:4;		//0:Inactive,1:Active
	unsigned int bTdsStartInd	:4;		//0:Inactive,1:Active
	unsigned int bReserved		:24;
}MULTIMODE_BB_STARTUP_MODE_IND_STRU;

/*HARQ��������ַ*/
#if (defined(LPHY_CHIP_BB_6930ES) || defined(LPHY_CHIP_BB_6930CS))
    #define LPHY_LMAC_HARQ_BUFF_ADDR_BY_HARQID(ucHarqId) (LPHY_LMAC_HARQ_BUFF_BASE_ADDR + (ucHarqId*0x4000))
#else
    #error "sorry, this is not a supported baseband version, please include product_config.h"
#endif
/*****************************************************************************
 STRU NAME: TLPHY_DDR_ADDR_INFO_STRU
 INTENTION: ps pre-powerup initialized ddr segment base address list for dsp
*****************************************************************************/
typedef struct __OUTER_MEM_IND_STRU__
{
	unsigned long ulBase;
	unsigned long ulSize;
}OUTER_MEM_IND_STRU;
typedef struct __TLPHY_OUTER_MEM_INFO_STRU__
{
	OUTER_MEM_IND_STRU stPhyImagBuff;			//Image buffer
	OUTER_MEM_IND_STRU stSdrDataBuff;			//Sdr buff for csu & emu
	OUTER_MEM_IND_STRU stLcsDataBuff;			//Otdoa carculate buffer
	OUTER_MEM_IND_STRU stLBandNvBuff;			//Lte Band related buffer
	
	OUTER_MEM_IND_STRU stSRamSleepFlag;			//Sleep flag
	OUTER_MEM_IND_STRU stSRamMbxProtect;		//mbx protect flag
	OUTER_MEM_IND_STRU stSRamMntnInfo;			//mbx overflow flag
	OUTER_MEM_IND_STRU stHkADCInfoBuff;			//Get temperature info

	OUTER_MEM_IND_STRU stTimeStampLog;			//timestamp log buffer
	OUTER_MEM_IND_STRU stAfcTraceInfo;			//afc trace information
	
	OUTER_MEM_IND_STRU stHifiMbxULHead;
	OUTER_MEM_IND_STRU stHifiMbxULBody;
	OUTER_MEM_IND_STRU stHifiMbxDLHead;
	OUTER_MEM_IND_STRU stHifiMbxDLBody;
	
	OUTER_MEM_IND_STRU stRsvdBuffInfo[2];		//reserved ddr buffer descriptor
}TLPHY_OUTER_MEM_INFO_STRU;
/*typedef struct __TLPHY_DDR_ADDR_INFO_STRU__
{
    unsigned long ulImageAddr;
    unsigned long ulImageSize;
    unsigned long ulSdrAddr;
    unsigned long ulSdrSize;
    unsigned long ulLcsAddr;
    unsigned long ulLcsSize;
    unsigned long ulBandNvAddr;
    unsigned long ulBandNvSize;
    unsigned long ulSramAddr;
    unsigned long ulSramSize;
    unsigned long ulTempAddr;
    unsigned long ulTempSize;
    unsigned long ulSramSleepFlagAddr;
    unsigned long ulSramSleepFlagSize;
    unsigned long ulTimeAddr;
    unsigned long ulTimeSize;
    unsigned long ulSramMailBoxProtectAddr;
    unsigned long ulSramMailBoxProtectSize;
    unsigned long ulAFCAddr;
    unsigned long ulAFCSize;
    unsigned long ulSramMntnInfoAddr;           //
    unsigned long ulSramMntnInfoSize;
    unsigned long ulSHM_MEM_TEMP_Addr;          //SHM_MEM_TEMPERATURE_ADDR
    unsigned long ulSHM_MEM_TEMP_Size;
    unsigned long ulBBE16ToHifiHeadAddr;
    unsigned long ulBBE16ToHifiHeadSize;
    unsigned long ulHifiToBBE16HeadAddr;
    unsigned long ulHifiToBBE16HeadSize;
    unsigned long ulBBE16ToHifiQueueAddr;
    unsigned long ulBBE16ToHifiQueueSize;
    unsigned long ulHifiToBBE16QueueAddr;
    unsigned long ulHifiToBBE16QueueSize;
    unsigned long ulRsv[2];
}TLPHY_DDR_ADDR_INFO_STRU;*/


/*****************************************************************************
 MARC NAME: MAILBOX DEFINE
 INTENTION: MAILBOX defined List
*****************************************************************************/

/* ���������С����*/
#define LPHY_MAILBOX_SHARE_MEM_SIZE                 (0x00000400UL)  /*1k�ֽڣ�TBD*/
#define LPHY_MAILBOX_HDLC_BUF_SIZE                  (0x00002000UL)  /*8K�ֽ�, TBD*/
#define LPHY_MAILBOX_LHPA_UP_SIZE                   (0x00002000UL)  /*8K�ֽڣ�PS���������С*/
#define LPHY_MAILBOX_LHPA_DOWN_SIZE                 (0x00002000UL)  /*8k�ֽڣ�PS���������С*/
#define LPHY_MAILBOX_OM_DOWN_SIZE                   (0x00000800UL)  /*2k�ֽڣ�OM���������С*/
#define LPHY_MAILBOX_LMAC_UP_SIZE                   (0x00000400UL)  /*1k�ֽڣ�MACר�������С*/
#define LPHY_MAILBOX_LMAC_DOWN_SIZE                 (0x00000400UL)  /*1k�ֽڣ�MACר�������С*/
#define LPHY_MAILBOX_DLTB_QUEUE_SIZE                (0x00000400UL)  /*1k�ֽڣ�MACPHY����TB QUEUE�����С*/
#define LPHY_MAILBOX_LPP_DOWN_SIZE                  (0x00000A00UL)  /*2.5�ֽڣ�LPP ��λ������Ϣ�����С*/
#define LPHY_MAILBOX_TOA_SIZE                       (0x00000600UL)  /*1.5k�ֽڣ�TOA�����С*/
#ifdef FEATURE_TLPHY_SINGLE_XO
#define LTPHY_NV_COMM_CFG_SIZE						(0x00000400UL)  /*1k�ֽڣ�LT PHY ����NV ��С*/
#else
#define LTPHY_NV_COMM_CFG_SIZE						(0x00000000UL)
#endif
//#define LPHY_NV_CFG_SIZE                            (0x00002000UL)  /*8k�ֽڣ�LTE NV����������С*/
#define LPHY_NV_CFG_SIZE                            (0x00002400UL)
#define TPHY_NV_CFG_SIZE                            (0x00002000UL)  /*8k�ֽڣ�TDS NV����������С*/

#if defined(TL_PHY_FPGA_P500)
    #define LPHY_MAILBOX_LCS_BANKA_MEM_SIZE         (0x00000000UL)  /*LPHY_HI6920ES���� fpga����������ڴ�*/
	#define LPHY_MAILBOX_CSU_BANKA_MEM_SIZE         (0x00003000UL)  /*С����������� banka memory 12K*/
	#define LPHY_MAILBOX_STU_BANKA_MEM_SIZE			(0x00000400UL)	/*STU����� banka memory 12K*/
	#define LPHY_MAILBOX_RSV_BANKA_MEM_SIZE			(0x00000000UL)	/*STU����� banka memory 16K*/
#else
    #define LPHY_MAILBOX_LCS_BANKA_MEM_SIZE         (0x00008000UL)  /*24K�ֽ�, ����  pliot�汾lcs����ʹ��*/
	#define LPHY_MAILBOX_CSU_BANKA_MEM_SIZE         (0x00003000UL)  /*LPHY_HI6920ES���� fpga����������ڴ�*/
	//#define LPHY_MAILBOX_STU_BANKA_MEM_SIZE			(0x00000800UL)	/*STU����� banka memory 2K*/
	#define LPHY_MAILBOX_STU_BANKA_MEM_SIZE			(0x00000400UL)
	#define LPHY_MAILBOX_RSV_BANKA_MEM_SIZE			(0x00000000UL)	/*STU����� banka memory 16K*/
#endif



/*�����ܴ�С*/
#define LPHY_TOTAL_RESERVED_MEM_SIZE    ( \
      LPHY_MAILBOX_SHARE_MEM_SIZE \
    + LPHY_MAILBOX_HDLC_BUF_SIZE \
    + LPHY_MAILBOX_LHPA_UP_SIZE   \
    + LPHY_MAILBOX_LHPA_DOWN_SIZE \
    + LPHY_MAILBOX_OM_DOWN_SIZE  \
    + LPHY_MAILBOX_LMAC_UP_SIZE  \
    + LPHY_MAILBOX_LMAC_DOWN_SIZE \
    + LPHY_MAILBOX_DLTB_QUEUE_SIZE\
    + LPHY_MAILBOX_LPP_DOWN_SIZE \
    + LPHY_MAILBOX_TOA_SIZE \
    + LTPHY_NV_COMM_CFG_SIZE\
    + LPHY_NV_CFG_SIZE\
    + TPHY_NV_CFG_SIZE\
    + LPHY_MAILBOX_LCS_BANKA_MEM_SIZE \
    + LPHY_MAILBOX_CSU_BANKA_MEM_SIZE \
    + LPHY_MAILBOX_STU_BANKA_MEM_SIZE)\
    + LPHY_MAILBOX_RSV_BANKA_MEM_SIZE

/*�������ַ����*/
#if (defined(TENSILICA_PLATFORM) || defined(MS_VC6_PLATFORM))
    #define LPHY_MAILBOX_BASE_ADDR                  (LPHY_SHARE_MEM_BASE_ADDR - MASTER_TCM_ADDR_OFFSET)
#else
    #define LPHY_MAILBOX_BASE_ADDR                  (LPHY_SHARE_MEM_BASE_ADDR)
#endif

/*�ⲿϵͳ���ʸ����������ַ*/
#define LPHY_MAILBOX_VERSION_ADDR                   (LPHY_MAILBOX_BASE_ADDR + 0x0200)   /*DSP�汾��ѯ��ַ*/
#define LPHY_MAILBOX_LOAD_MEMORY_ADDR               (LPHY_MAILBOX_BASE_ADDR + 0x020C)   /*������ʼ�����ֵ�ַ*/
#define LPHY_MAILBOX_RFIC_AD9361_VERSIOM_ADDR       (LPHY_MAILBOX_BASE_ADDR + 0x0210)   /*AD9361��ƵоƬ�汾��ѯ��ַ*/
#define TLPHY_DDR_ADDR_INFO							(LPHY_MAILBOX_BASE_ADDR + 0x0214)	/*TL PHY ��DDR��ַ������IMAGE SDR LCS BANDNV��64B*/
#define LPHY_MAILBOX_IPCM_MUTEX_DSP_SEND            (LPHY_MAILBOX_BASE_ADDR + 0x0324)   /*P500��A9IPCͨѶ��������ַ*/
#define LPHY_MAILBOX_IPCM_MUTEX_DSP_RECEIVE         (LPHY_MAILBOX_BASE_ADDR + 0x0328)   /*P500��A9IPCͨѶ��������ַ*/
#define LPHY_MAILBOX_SLAVE_AWAKE_ADDR               (LPHY_MAILBOX_BASE_ADDR + 0x032C)   /*��ģPS IPCM����״̬��ַ*/
#define LPHY_MAILBOX_LPHY_WORKING_MODE_ADDR         (LPHY_MAILBOX_BASE_ADDR + 0x0340)   /*LTE PHY WorkModeInd*/
#define LPHY_MAILBOX_LPHY_CTU_REG_BASE_ADDR         (LPHY_MAILBOX_BASE_ADDR + 0x0344)   /*LTE ����ģʽ*/
#define LPHY_MAILBOX_LPHY_DSP_NV_PARA_SIZE_ADDR     (LPHY_MAILBOX_BASE_ADDR + 0x0348)   /*LTE PHY DSP ����ʱ NV Para_Size*/
#define LPHY_MAILBOX_LPHY_ARM_NV_PARA_SIZE_ADDR     (LPHY_MAILBOX_BASE_ADDR + 0x034C)   /*LTE PHY ARM�·���  NV Para_Size*/
#define LPHY_MAILBOX_MULTIMODE_STARTUP_MODE_ADDR    (LPHY_MAILBOX_BASE_ADDR + 0x0350)   /*��ģ��������ģʽָʾ*/

//#define TL_PHY_MAILBOX_SOC_TEST_ADDR                (LPHY_MAILBOX_BASE_ADDR + 0x4000)   /*DSPѹ�����������������ַ*/

#define LPHY_MAILBOX_HDLC_BUF_BASE_ADDR             (LPHY_MAILBOX_BASE_ADDR 			+ LPHY_MAILBOX_SHARE_MEM_SIZE)
#define LPHY_MAILBOX_LHPA_UP_BASE_ADDR              (LPHY_MAILBOX_HDLC_BUF_BASE_ADDR 	+ LPHY_MAILBOX_HDLC_BUF_SIZE)
#define LPHY_MAILBOX_LHPA_DOWN_BASE_ADDR            (LPHY_MAILBOX_LHPA_UP_BASE_ADDR 	+ LPHY_MAILBOX_LHPA_UP_SIZE)
#define LPHY_MAILBOX_OM_DOWN_BASE_ADDR              (LPHY_MAILBOX_LHPA_DOWN_BASE_ADDR 	+ LPHY_MAILBOX_LHPA_DOWN_SIZE)
#define LPHY_MAILBOX_LMAC_UP_BASE_ADDR              (LPHY_MAILBOX_OM_DOWN_BASE_ADDR 	+ LPHY_MAILBOX_OM_DOWN_SIZE)
#define LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR            (LPHY_MAILBOX_LMAC_UP_BASE_ADDR 	+ LPHY_MAILBOX_LMAC_UP_SIZE)
#define LPHY_MAILBOX_DL_TB_QUEUE_BASE_ADDR          (LPHY_MAILBOX_LMAC_DOWN_BASE_ADDR 	+ LPHY_MAILBOX_LMAC_DOWN_SIZE)
#define LPHY_MAILBOX_LPP_DOWN_BASE_ADDR           	(LPHY_MAILBOX_DL_TB_QUEUE_BASE_ADDR + LPHY_MAILBOX_DLTB_QUEUE_SIZE)
#define LPHY_MAILBOX_TOA_BASE_ADDR                  (LPHY_MAILBOX_LPP_DOWN_BASE_ADDR 	+ LPHY_MAILBOX_LPP_DOWN_SIZE)
#define LPHY_MAILBOX_NV_CFG_BASE_ADDR               (LPHY_MAILBOX_TOA_BASE_ADDR 		+ LPHY_MAILBOX_TOA_SIZE)
#define TPHY_MAILBOX_NV_CFG_BASE_ADDR				(LPHY_MAILBOX_NV_CFG_BASE_ADDR		+ LPHY_NV_CFG_SIZE)
#define LTPHY_MAILBOX_NV_COMM_CFG_BASE_ADDR 		(TPHY_MAILBOX_NV_CFG_BASE_ADDR 		+ TPHY_NV_CFG_SIZE)
//#define LPHY_MAILBOX_LCS_BANKA_BASE_ADDR            (TPHY_MAILBOX_NV_CFG_BASE_ADDR 		+ TPHY_NV_CFG_SIZE)
#define LPHY_MAILBOX_LCS_BANKA_BASE_ADDR            (LTPHY_MAILBOX_NV_COMM_CFG_BASE_ADDR 		+ LTPHY_NV_COMM_CFG_SIZE)
#define LPHY_MAILBOX_CSU_BANKA_BASE_ADDR            (LPHY_MAILBOX_LCS_BANKA_BASE_ADDR  	+ LPHY_MAILBOX_LCS_BANKA_MEM_SIZE)
#define LPHY_MAILBOX_STU_BANKA_BASE_ADDR            (LPHY_MAILBOX_CSU_BANKA_BASE_ADDR  	+ LPHY_MAILBOX_CSU_BANKA_MEM_SIZE)
#define LPHY_MAILBOX_RSV_BANKA_BASE_ADDR			(LPHY_MAILBOX_STU_BANKA_BASE_ADDR  	+ LPHY_MAILBOX_STU_BANKA_MEM_SIZE)

/*	----------------------------------------------------------------------------------
* WARNING: This memory is a reused memory space for LTE[OTDOA in Matser Mode] & TDS
* [CellSrch&EMU in slave Mode]; Since TDS [EMU&Cellsrch] have higher priority than
* OTDOA, SO TDS need backup the content of this buffer before start to use this bufer
* and recover the content of this buffer before TDS task exit.
-------------------------------------------------------------------------------------*/
#define TPHY_RSVD_32K_BUFFER_BASE_ADDR				(LPHY_MAILBOX_LCS_BANKA_BASE_ADDR)


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __MEM_MAP_BASE_H__ */
