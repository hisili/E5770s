

#ifndef __DRV_MNTN_H__
#define __DRV_MNTN_H__

#include "drv_comm.h"
#include "drv_usb.h"
#include "drv_sd.h"
#include "product_config.h"

/*************************MNTN START**********************************/

#define OM_SAVE_EXCHFILE_ING            0
#define OM_SAVE_EXCHFILE_END            1

enum SECURE_SUPPORT_STATUS_I
{
    SECURE_NOT_SUPPORT = 0,
    SECURE_SUPPORT = 1
};

enum SECURE_ENABLE_STATUS_I
{
    SECURE_DISABLE = 0,
    SECURE_ENABLE = 1
};

typedef enum                /* CACHE_TYPE */
{
    PS_OSAL_INSTRUCTION_CACHE ,
    PS_OSAL_DATA_CACHE
} PS_OSAL_CACHE_TYPE_I;


#ifndef __SUPPORT_MAX_HSPA_CAPA_STRU
#define __SUPPORT_MAX_HSPA_CAPA_STRU
typedef struct
{
    unsigned char enHSDSCHSupport;          /*Ӳ���Ƿ�֧��HSDPA*/
    unsigned char ucHSDSCHPhyCategory;      /*Ӳ��֧�ֵ����HSDPA�����ȼ�*/
    unsigned char enEDCHSupport;            /*Ӳ���Ƿ�֧��HSUPA*/
    unsigned char ucEDCHPhyCategory;        /*Ӳ��֧�ֵ����HSUPA�����ȼ�*/
    unsigned int  reserved;                 /*Ԥ��*/
}SUPPORT_MAX_HSPA_CAPA_STRU;
#endif
/*****************************BSP_MspProcReg  begin******************************/
typedef enum tagMSP_PROC_ID_E
{
    OM_REQUEST_PROC = 0,
    OM_ADDSNTIME_PROC = 1,
    OM_PRINTF_WITH_MODULE = 2,
    OM_PRINTF = 3,

    OM_PRINTF_GET_MODULE_IDLEV = 4,
    OM_READ_NV_PROC = 5,
    OM_WRITE_NV_PROC = 6,
    OM_MNTN_ERRLOG = 7,

    MSP_PROC_REG_ID_MAX
}MSP_PROC_ID_E;

typedef void (*BSP_MspProc)(void);
/*****************************************************************************
* �� �� ��  : DRV_MSP_PROC_REG
*
* ��������  : DRV�ṩ��OM��ע�ắ��
*
* �������  : MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc
* �������  : NA
*
* �� �� ֵ  : NA
*
* ����˵��  : ��ά�ɲ�ӿں���
*
*****************************************************************************/
extern void DRV_MSP_PROC_REG(MSP_PROC_ID_E eFuncID, BSP_MspProc pFunc);


/*****************************************************************************
 �� �� ��  : BSP_MNTN_UartRecvCallbackRegister
 ��������  : �ṩ�ϲ�Ӧ�ó���ע�����ݽ��ջص�����ָ���API�ӿں�����
 �������  : uPortNo������ʵ���š�
             pCallback���ص�����ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/



static INLINE int BSP_MNTN_GetMaxFreeblockSize(void)
{

	return 0;
}


/*****************************************************************************
* �� �� ��  : BSP_HwIsSupportWifi
* ��������  : ��ӡӲ���汾��Ϣ,��׮
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
* ����˵��  : ��
*****************************************************************************/
BSP_BOOL BSP_HwIsSupportWifi(BSP_VOID);


/*****************************************************************************
 �� �� ��  : BSP_PMU_LDOOFF
 ��������  : ���ӿ����ڹر�ĳ·LDO�ĵ�ѹ�����
 �������  : ucLDO��ָʾĳ·LDO��ѹ��ȡֵ��ΧΪ1��12��
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
 ע�������LDO6��Ӳ�����ƣ������֧�ֶ�LDO6�Ĳ����������LDO1�رգ���ϵͳ��ػ���
*****************************************************************************/
extern void BSP_PMU_LDOOFF(BSP_U8 u8LDO);
#define DRV_PM_LDO_OFF(u8LDO)                 BSP_PMU_LDOOFF(u8LDO)

/*****************************************************************************
 �� �� ��  : BSP_PMU_LDOON
 ��������  : ���ӿ��������ô�ĳ·LDO�ĵ�ѹ�����
 �������  : ucLDO��ָʾĳ·LDO��ѹ��ȡֵ��ΧΪ2��12��
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
 ע���������֧�ֶ�LDO1��LDO6�Ĳ�����LDO1����ϵͳ����ʱ�Զ��򿪣�һ���ر�������ϵͳ���µ磻LDO6����Ӳ���ܽſ��ơ�
*****************************************************************************/
extern void BSP_PMU_LDOON(BSP_U8 u8LDO);
#define DRV_PM_LDO_ON(u8LDO)                  BSP_PMU_LDOON(u8LDO)




/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetGsmPATemperature
 ��������  : ��ȡGSM PA�¶�
 �������  : Temprature
             hkAdcTalble
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_GetGsmPATemperature(int *temperature, unsigned short *hkAdcTable);
#define DRV_GET_PA_GTEMP(temperature, hkAdcTable)   \
                BSP_MNTN_GetGsmPATemperature(temperature, hkAdcTable)

/*****************************************************************************
 �� �� ��  : getWcdmaPATemperature
 ��������  : ��ȡWCDMA PA�¶�
 �������  : Temprature
             hkAdcTalble
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_GetWcdmaPATemperature (int *temperature, unsigned short *hkAdcTable);
#define  DRV_GET_PA_WTEMP(temperature, hkAdcTable)  \
              BSP_MNTN_GetWcdmaPATemperature(temperature, hkAdcTable)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetSIMTemperature
 ��������  : ��ȡSIM���¶�
 �������  : pusHkAdcTable����ŵ�ѹ��
 �������  : pTemp��        ָ��SIM���¶ȵ�ָ�롣
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int BSP_MNTN_GetSIMTemperature(int *plTemp, unsigned short *pusHkAdcTable);
#define DRV_GET_SIM_TEMP(plTemp, pusHkAdcTable)   \
               BSP_MNTN_GetSIMTemperature(plTemp, pusHkAdcTable)




/*****************************************************************************
 �� �� ��  : BSP_MNTN_I2cSelfCheck
 ��������  : ����I2c�Լ���
 �������  : None
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע��������ýӿڽ���PS��PC������ʹ�ã�Ŀǰû��Ӧ�ã��ݱ�����
*****************************************************************************/
static INLINE int BSP_MNTN_I2cSelfCheck(void)
{
	return 0;
}
#define DRV_I2C_SELFCHECK()    BSP_MNTN_I2cSelfCheck()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_SpiSelfCheck
 ��������  : ����spi�Լ���
 �������  : None
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע��������ýӿڽ���PS��PC������ʹ�ã�Ŀǰû��Ӧ�ã��ݱ�����
*****************************************************************************/
static INLINE int BSP_MNTN_SpiSelfCheck(void)
{
	return 0;
}

#define DRV_SPI_SELFCHECK()    BSP_MNTN_SpiSelfCheck()

/*****************************************************************************
 �� �� ��  : MNTN_RFGLockStateGet
 ��������  : ��ȡGSM RF����״̬��
 �������  : �ޡ�
 �������  : Status���������״̬�����ֵ��
                        0��TX����RX��������
                        1��TX��RX��û�б�������

 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
static INLINE int BSP_MNTN_RFGLockStateGet(unsigned int *Status)
{
	return 0;
}
#define DRV_GET_RF_GLOCKSTATE(Status)    BSP_MNTN_RFGLockStateGet(Status)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_BootForceloadModeCheck
 ��������  : ǿ�Ƽ���ģʽ��ѯ��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0��ǿ�Ƽ��أ�
             1����ǿ�Ƽ��ء�
*****************************************************************************/
static INLINE unsigned int BSP_MNTN_BootForceloadModeCheck(void)
{
    return 0;
}
#define DRV_BOOT_FORCELOAD_MODE_CHECK()    BSP_MNTN_BootForceloadModeCheck()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_BootFlagConfig
 ��������  : ����Bootline�����е�������־Ϊ����������������ʱ7�����������ֶ�������
 �������  : ulBootFlag����δ���塣
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
static INLINE  int BSP_MNTN_BootFlagConfig(unsigned int ulBootFlag)
{
	return 0;
}

#define DRV_BOOTFLAG_CFG(ulBootFlag)    BSP_MNTN_BootFlagConfig(ulBootFlag)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_CheckArmTCM
 ��������  : TCM���
 �������  : �ޡ�
 �������  : �ޡ�
 ����ֵ��   0xffff0000�����ɹ���TCM����
            ��ַ��������ĵ�ַ��0��0x5fff��
            0xffffffff:���ʧ��

*****************************************************************************/
static INLINE unsigned int BSP_MNTN_CheckArmTCM(void)
{
    return 0;
}
#define DRV_CHECK_ARM_TCM()    BSP_MNTN_CheckArmTCM()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_Int4ToString
 ��������  : ���Ĵ�����ֵת��ΪASCII�ַ�
 �������  : �Ĵ�����ֵ����ת���ַ��Ĵ洢�ռ�,���ռ䲻����30byte
 �������  : ת���ַ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
static INLINE int BSP_MNTN_Int4ToString(unsigned int value, char * string)
{
    return 0;
}
#define DRV_MEM_VERCONVERT(value,string)    BSP_MNTN_Int4ToString(value, string)

/*****************************************************************************
 �� �� ��  : BSP_MNTN_HeapInfoGet
 ��������  : ��ȡ�������ڴ���Ϣ��
 �������  : allocSize: �Ѿ�����Ķ��ڴ��С����λbyte��
             totalSize: ���ڴ��ܳߴ磬��λbyte��
 �������  : None
 �� �� ֵ  : 0: �����ɹ���
             -1��  ����ʧ�ܡ�
*****************************************************************************/
static INLINE int BSP_MNTN_HeapInfoGet(unsigned int *allocSize, unsigned int *totalSize)
{
	return 0;
}
#define DRV_GET_HEAPINFO(allocSize, totalSize)    BSP_MNTN_HeapInfoGet(allocSize, totalSize)

/********************************************************************************************************
 �� �� ��  : BSP_MNTN_WriteSysBackupFile
 ��������  : ��FLASH����ZSP��NV����
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
static INLINE int BSP_MNTN_WriteSysBackupFile(void)
{
	return 0;
}
#define DRV_BACKUP_SYS_FILE()    BSP_MNTN_WriteSysBackupFile()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_TFUPIfNeedNvBackup
 ��������  : ʹ��TF������ǰͨ���ýӿ��ж��Ƿ���Ҫ����NV��.
 �������  : None
 �������  : None
 �� �� ֵ  : 1:��Ҫ����
             0:���豸��
*****************************************************************************/
static INLINE int BSP_MNTN_TFUPIfNeedNvBackup(void)
{
    return 0;
}
#define DRV_TF_NVBACKUP_FLAG()    BSP_MNTN_TFUPIfNeedNvBackup()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetSDDevName
 ��������  : ��ȡ�豸�б��е�SD�豸��
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : SD_DEV_TYPE_STR�ṹָ�롣
*****************************************************************************/
static INLINE SD_DEV_TYPE_STR * BSP_MNTN_GetSDDevName(void)
{
	return 0;
}

#define DRV_GET_SD_PATH()     BSP_MNTN_GetSDDevName()

/*****************************************************************************
 �� �� ��  : BSP_PROD_GetRecoverNvInfo
 ��������  : �ӵ����õ�ǰ��Ҫ���ǵ�NV��Ϣ
 �������  : N/A

 �������  : ppNvInfo  - ָ��NV��Ϣ�ṹ�������
             pulNvNum  - �������

 �� �� ֵ  : 0����ȷ����0: ʧ��
*****************************************************************************/
extern  int BSP_PROD_GetRecoverNvInfo(void **ppNvInfo, unsigned long *pulNvNum);
#define  DRV_GET_RECOVER_NV_INFO(ppNvInfo, pulNvNum)  \
                BSP_PROD_GetRecoverNvInfo(ppNvInfo, pulNvNum)


/*****************************************************************************
 �� �� ��  : SDIO_read_write_blkdata
 ��������  : SD����д�ӿ�
 �������  :    nCardNo     SD����
                dwBlkNo     ����
                nBlkCount   ��д��С
                pbDataBuff  ��д������
                nFlags      ��/д
 �������  : �ޡ�
 ����ֵ��   0:  ��д�ɹ�
            ��0:������
*****************************************************************************/
static INLINE int BSP_MNTN_SDRWBlkData(int nCardNo,unsigned int dwBlkNo,
                   unsigned int nBlkCount, unsigned char *pbDataBuff,int nFlags)
{
    return 0;
}
#define DRV_SDMMC_BLK_DATA_RW(nCardNo,dwBlkNo,nBlkCount,pbDataBuff,nFlags)   \
             BSP_MNTN_SDRWBlkData(nCardNo,dwBlkNo,nBlkCount,pbDataBuff, nFlags)


/***********************************�ڴ濽���Ż�*****************************************/
/*****************************************************************************
 �� �� ��  : __rt_memcpy
 ��������  : ���汾��memcpy����
 �������  : Dest :Ŀ�ĵ�ַ
             Src :Դ��ַ
             Count:�������ݵĴ�С
 �������  : �ޡ�
 �� �� ֵ  : Ŀ�ĵ�ַ��
*****************************************************************************/
#define DRV_RT_MEMCPY(Dest,Src,Count)       memcpy(Dest,Src,Count)

/*****************************************************************************
 �� �� ��  : bsp_memcpy_align32
 ��������  : ���汾��32λ���ݶ���memcpy����
 �������  : Dest :Ŀ�ĵ�ַ
             Src :Դ��ַ
             Count:�������ݵĴ�С
 �������  : �ޡ�
 �� �� ֵ  : Ŀ�ĵ�ַ��
*****************************************************************************/
extern void bsp_memcpy_align32(UINT32 *pDstBuf,  UINT32 *pSrcBuf, UINT32 ulSize);
#define DRV_MEMCPY_ALIGN32(Dest,Src,Count)       bsp_memcpy_align32(Dest,Src,Count)

/*****************************************************************************
 �� �� ��  : bsp_memcpy_auto_align64
 ��������  : �Զ���64λ����汾��memcpy����
 �������  : Dest :Ŀ�ĵ�ַ
             Src :Դ��ַ
             Count:�������ݵĴ�С
 �������  : �ޡ�
 �� �� ֵ  : Ŀ�ĵ�ַ��
*****************************************************************************/
extern void bsp_memcpy_auto_align(void *pDstBuf,  void *pSrcBuf, UINT32 ulLen, UINT32 ulAlignSize);
#define DRV_MEMCPY_AUTO_ALIGN64(Dest,Src,Count) bsp_memcpy_auto_align(Dest,Src,Count,8);


/************************************����궨��Ϊ�յĺ���******************************************/
/*****************************************************************************
 �� �� ��  : UsbStatusCallbackRegister
 ��������  : ��¼pCallBack��ȫ�ֱ����С�SD��������ؽӿڣ�V7�ȴ�׮
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
 /*extern int  UsbStatusCallbackRegister(pUsbState pCallBack);*/
#define DRV_USB_STATUS_CALLBACK_REGI(pCallBack)              DRV_OK

/*****************************************************************************
 �� �� ��  : CicomClkEnable
 ��������  : This routine enable CICOM IP clock gating.�͹�����أ�V7��׮
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/*extern void CicomClkEnable(void);*/
#define DRV_CICOM_CLK_ENABLE()

/*****************************************************************************
 �� �� ��  : CicomClkDisable
 ��������  : This routine disable CICOM IP clock gating.�͹�����أ�V7��׮
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/*extern void CicomClkDisable(void);*/
#define DRV_CICOM_CLK_DISABLE()

/*****************************************************************************
 �� �� ��  : HdlcClkEnable
 ��������  : This routine enable HDLC IP clock gating.�͹�����أ�V7��׮
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/*extern void HdlcClkEnable(void);*/
#define DRV_HDLC_CLK_ENABLE()

/*****************************************************************************
 �� �� ��  : HdlcClkDisable
 ��������  : This routine disable HDLC IP clock gating.�͹�����أ�V7��׮
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
/*extern void HdlcClkDisable(void);*/
#define DRV_HDLC_CLK_DISABLE()

/*****************************************************************************
 �� �� ��  : DRV_MEM_READ
 ��������  : ��32λ��Ȳ�ѯ�ڴ棬���4�ֽ����ݡ���ά�ɲ⣬V7�ȴ�׮
 �������  : ulAddress����ѯ��ַ�ռ��ַ����ַ�����ڴ淶Χ�ڣ����򷵻�-1��
 �������  : pulData��ָ���ѯ���ݵ�ָ�롣
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
static INLINE int DRV_MEM_READ(unsigned int ulAddress, unsigned int* pulData)
{
	return 0;
}

/*****************************************************************************
 �� �� ��  : DrvLogInstall
 ��������  : ��ӡ����ע�ᡣ��ά�ɲ⣬V7�ȴ�׮
 �������  : fptr ע��ĺ���ָ��
 �������  : None
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
/*extern int DrvLogInstall(PVOIDFUNC fptr, PVOIDFUNC fptr1, PVOIDFUNC fptr2, PVOIDFUNC fptr3, PVOIDFUNC fptr4);*/
#define DRV_LOG_INSTALL(fptr, fptr1, fptr2, fptr3, fptr4)     DRV_OK

/*****************************************************************************
 �� �� ��  : pwrctrl_wpa_pwr_up
 ��������  : RF�µ�
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
extern void pwrctrl_wpa_pwr_up(void);
#define DRV_WPA_POWERUP()


/*****************************************************************************
 �� �� ��  : BSP_DMR_ATAnalyze
 ��������  : ��NAS��ѯ��̬�ڴ�ռ����Ϣ��ͨ��AT�����ѯ
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ɹ�0��ʧ��-1
*****************************************************************************/
extern int BSP_DMR_ATANALYZE(void * pstMem,unsigned int uiSize, unsigned int * puiModIdSum);

static INLINE void * GET_SYSTEM_RESET_INFO(void)
{
    return 0;
}

#define EXCH_CB_NAME_SIZE           (32)
typedef struct
{
    char   aucName[EXCH_CB_NAME_SIZE];
    unsigned char *pucData;
    unsigned int  ulDataLen;
}cb_buf_t;

typedef int  (*exchCBReg)(cb_buf_t *);
static INLINE int DRV_EXCH_CUST_FUNC_REG(exchCBReg cb)
{
    return 0;
}
/*****************************************************************
Function: free_mem_size_get
Description:
    get mem size
Input:
    N/A
Output:
    N/A
Return:
    free mem size
*******************************************************************/
static INLINE unsigned long free_mem_size_get(void)
{
    return 0;
}
#define FREE_MEM_SIZE_GET() free_mem_size_get()

static INLINE BSP_U32 BSP_CPU_GetTotalUtilize(void)
{
    return 0;
}

static INLINE void BSP_ONOFF_DrvPowerOff(void)
{
    return;/*��׮*/
}

static INLINE unsigned short * BSP_MNTN_MemCheck16(void *pStartAddr, void *pEndAddr)
{
    return 0;
}

static INLINE void BSP_MNTN_StartTimeStamp(void)
{
    return ;
}

static INLINE void BSP_MNTN_VersionAndTimeForm(UINT8 * string, UINT8 length)
{
    return;
}

/*************************MNTN END************************************/

#endif


