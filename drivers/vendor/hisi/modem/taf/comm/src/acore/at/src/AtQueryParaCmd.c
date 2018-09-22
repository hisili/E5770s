

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "DrvInterface.h"
#include "PppInterface.h"
#include "TafDrvAgent.h"
#include "Taf_Tafm_Remote.h"
#include "TtfMemAtInterface.h"
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "AtPhyInterface.h"
#include "AtDataProc.h"
#include "AtCmdMsgProc.h"
#include "AtCheckFunc.h"
#include "AtSndMsg.h"
#include "AtRnicInterface.h"
#include "AtCheckFunc.h"
#include "AtInputProc.h"
#include "AtEventReport.h"
#include "AtDeviceCmd.h"
#include "ipcmailboxinterface.h"
#include "om.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "omnvinterface.h"

#include "AtTafAgentInterface.h"
#include "AppVcApi.h"
#include "siappstk.h"


#include "product_nv_def.h"
#if (FEATURE_ON==FEATURE_LTE)
#include "msp_nvim.h"
#include "msp_nv_def.h"
#include "msp_nv_id.h"
#include "at_common.h"
/* ADD by c64416 for V9R1/V7R1 AT, 2013/09/18 begin */
#include "at_lte_common.h"
/* ADD by c64416 for V9R1/V7R1 AT, 2013/09/18 end */
#endif
#include "AtMsgPrint.h"
#if (FEATURE_ON == MBB_WPG_COMMON)
#include "AtTafAgentInterface.h"
#include "MbbAtGuComm.h"
#include "MbbPsCsCommon.h"
#endif
#if (FEATURE_ON == MBB_FEATURE_CAT_MODULE_SET)
#include "LPsNvInterface.h"
#endif
#if(FEATURE_ON == MBB_CHG_BQ27510)
#include "../../../../../../drv/acore/kernel/drivers/power/charger/bq27510/hisi_coul_drv.h"
#endif 
#include <product_config.h>
#if (FEATURE_ON == MBB_COMMON)
#include <drv_temp_cfg.h>
#endif
#if(FEATURE_ON == MBB_FEATURE_ESIM_SWITCH)
#include <hi_gpio.h>
#include <linux/gpio.h>
#endif
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_QUERYPARACMD_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/

/*��¼��ѯ�����������*/
extern TAF_UINT32                       gulErrType;

extern VOS_UINT32                       g_ulWifiFreq;
extern VOS_UINT32                       g_ulWifiMode;
extern VOS_UINT32                       g_ulWifiRate;
extern VOS_UINT32                       g_lWifiPower;
extern VOS_UINT32                       g_ulUcastWifiRxPkts;
extern VOS_UINT32                       g_ulMcastWifiRxPkts;

#if(FEATURE_ON == MBB_FEATURE_ESIM_SWITCH)
extern VOS_UINT8                       TSimSwitchValue;
#endif

#if(FEATURE_ON == MBB_COMMON)
#define USIMM_OPENSPEEDENABLE           0x01000101
#endif

#if(FEATURE_ON == MBB_SIMLOCK_THREE)
#define SIMLOCK_VERSION_THREE      (4)
#endif

#if(FEATURE_ON == MBB_SIMLOCK_FOUR)
#define SIMLOCK_VERSION_FOUR       (5)
#endif /*MBB_SIMLOCK_FOUR*/

/*�޸�wifiУ׼�¶ȷ���ֵ����AT�淶����*/
#if (FEATURE_ON == MBB_COMMON)
#define   WICALTEMPNUM             (1)
#endif
#if(FEATURE_ON == MBB_CHG_BQ27510)
#define FIREMWARE_UPDATA_RET_LEN    (8)
#define COUL_FIRMWARE_UPDATA_MASK   (((uint16)1) << 0)
/*�����Ҫ���ӹ̼�������������Ӷ�Ӧ��MASK�궨��
ͬʱ����Ӧ��flag ����FIRMWARE_UPDATA_MASK*/
uint16   firmware_updata_mask = COUL_FIRMWARE_UPDATA_MASK;
#endif

#ifdef BSP_CONFIG_BOARD_K5160
#define AT_VOX_MODEM_PORT_NUM               (1)
#define AT_VOX_NDIS_PORT_NUM                (1)
#endif/*BSP_CONFIG_BOARD_K5160*/

typedef enum {
    REVERT_FAIL = 0,
    REVERT_SUCCESS = 1
}REVERT_NV_FLAG;

static REVERT_NV_FLAG g_revert_flag = REVERT_FAIL;

/*****************************************************************************
   3 ��������������
*****************************************************************************/
#if (FEATURE_ON == MBB_HWTEST)  
/*�������*/
char *hw_test_option[] =
{
    "ddr",
    "flash",
    "peripheral",
    "all",
     NULL
};
#endif
#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_UINT8 NAS_GetPsRegContainDrx();
#endif
/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/


VOS_UINT32 At_QrySecuBootFeaturePara( VOS_UINT8 ucIndex )
{
    VOS_UINT16                          usNVSecBootEnableFlag;


    usNVSecBootEnableFlag = VOS_FALSE;

    /* ��ȡNV�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_SEC_BOOT_FLAG, &usNVSecBootEnableFlag, sizeof(VOS_UINT16)))
    {
        AT_WARN_LOG("At_QrySecuBootFeaturePara: Read en_NV_Item_SEC_BOOT_FLAG failed");
        return AT_ERROR;
    }

    /* ��ӡ��� */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s: %d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            usNVSecBootEnableFlag);

    return AT_OK;
}


VOS_UINT32 At_QrySecuBootPara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_SECUBOOT_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SECUBOOT_QRY;             /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                            /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryGTimerPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulGTimerLength;


    ulGTimerLength = 0;

    /* ��ȡNV��en_NV_Item_GPRS_ActiveTimerLength��ȡGPRS��ʱ��ʱ�� */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_GPRS_ActiveTimerLength,
                    &ulGTimerLength,
                    sizeof(ulGTimerLength));
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryGTimerPara: Fail to read en_NV_Item_GPRS_ActiveTimerLength");
        return AT_DEVICE_OTHER_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      ulGTimerLength);

    return AT_OK;
}


VOS_UINT32 AT_QryRsimPara(VOS_UINT8 ucIndex)
{
/*MS2172S_818��Ŀ���SIM_DET�ܽţ���Ϊ0������ʾ����SIM������λESIM����λ��^RSIM����0*/
#if(FEATURE_ON == MBB_FEATURE_ESIM_SWITCH)
    u32 sim_detect_level;
    gpio_direction_input(GPIO_0_3); 
    sim_detect_level = gpio_get_value(GPIO_0_3);
    if(0 == sim_detect_level){
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_RSIM_STATUS_USIMM_CARD_ABSENT);
        return AT_OK;
    }
    else {
        //do nothing
    }
#endif
#if(FEATURE_ON == MBB_COMMON)
    VOS_UINT32                          ulRet;
    VOS_UINT32                          fastboot = 0 ;


   ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_FollowOn_OpenSpeed_Flag, &fastboot, sizeof(VOS_UINT32));
    
    if (NV_OK != ulRet)
    {
        fastboot = 0;
    }
   
    if(USIMM_OPENSPEEDENABLE ==  fastboot)
    {
    
        /*get sim statue */
            
        if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                                     gastAtClientTab[ucIndex].opId,
                                                     DRV_AGENT_QRY_SIM_INFO_REQ,
                                                     VOS_NULL_PTR,
                                                     0,
                                                     I0_WUEPS_PID_DRV_AGENT))
        {
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SIM_QRY;           /*���õ�ǰ����ģʽ */
            return AT_WAIT_ASYNC_RETURN;                                       /* �ȴ��첽�¼����� */
        }
        else
        {
            return AT_ERROR;
        }
           
    }
    else
    {
#endif
        VOS_UINT32                           ucCardStatus;
        VOS_UINT32                           ucCardType;
        
        /* Modified by l60609 for DSDA Phase II, 2012-12-24, Begin */
        MODEM_ID_ENUM_UINT16                enModemId;
        VOS_UINT32                          ulGetModemIdRslt;
        /* Modified by l60609 for DSDA Phase III, 2013-3-5, Begin */
        AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

        enModemId = MODEM_ID_0;

        ulGetModemIdRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

        if (VOS_OK != ulGetModemIdRslt)
        {
            AT_ERR_LOG("At_SetCardModePara:Get Modem Id fail!");
            return AT_ERROR;
        }

        pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);
        /* Modified by l60609 for DSDA Phase II, 2012-12-24, End */

        /* ��ȡ SIM �����ͺ�״̬ */
        ucCardType   =  pstUsimInfoCtx->enCardType;
        ucCardStatus =  pstUsimInfoCtx->enCardStatus;
        /* Modified by l60609 for DSDA Phase III, 2013-3-5, End */
        AT_NORM_LOG1("AT_QryRsimPara: ucCardStatus is ", (VOS_INT32)ucCardStatus);
        AT_NORM_LOG1("AT_QryRsimPara: ucCardType is ",   (VOS_INT32)ucCardType);

        if (USIMM_CARD_SERVIC_BUTT == ucCardStatus)
        {
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_RSIM_STATUS_USIMM_CARD_BUSY);
            return AT_OK;
        }

        /* ���������ΪUSIMM_CARD_ROM_SIMָʾ��ǰΪ���ٿ�����Ч���޿� */
        if ((USIMM_CARD_ROM_SIM == ucCardType)
         || (USIMM_CARD_SERVIC_ABSENT == ucCardStatus))
        {
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_RSIM_STATUS_USIMM_CARD_ABSENT);
        }
        else
        {
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              "%s:%d",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              AT_RSIM_STATUS_USIMM_CARD_AVAILABLE);
        }

        return AT_OK;
#if(FEATURE_ON == MBB_COMMON)
    }
#endif

}

#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)

VOS_UINT32 AT_QryUsimstatusPara(VOS_UINT8 ucIndex)
{
        VOS_UINT32                           ucCardStatus;
        VOS_UINT32                           ucCardType;
        
        /* Modified by l60609 for DSDA Phase II, 2012-12-24, Begin */
        MODEM_ID_ENUM_UINT16                enModemId;
        VOS_UINT32                          ulGetModemIdRslt;
        /* Modified by l60609 for DSDA Phase III, 2013-3-5, Begin */
        AT_USIM_INFO_CTX_STRU              *pstUsimInfoCtx = VOS_NULL_PTR;

        enModemId = MODEM_ID_0;

        ulGetModemIdRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

        if (VOS_OK != ulGetModemIdRslt)
        {
            AT_ERR_LOG("At_SetCardModePara:Get Modem Id fail!");
            return AT_ERROR;
        }

        pstUsimInfoCtx = AT_GetUsimInfoCtxFromModemId(enModemId);
        /* Modified by l60609 for DSDA Phase II, 2012-12-24, End */

        /* ��ȡ SIM �����ͺ�״̬ */
        ucCardType   =  pstUsimInfoCtx->enCardType;
        ucCardStatus =  pstUsimInfoCtx->enCardStatus;
        /* Modified by l60609 for DSDA Phase III, 2013-3-5, End */
        AT_NORM_LOG1("AT_QryRsimPara: ucCardStatus is ", (VOS_INT32)ucCardStatus);
        AT_NORM_LOG1("AT_QryRsimPara: ucCardType is ",   (VOS_INT32)ucCardType);


        if (USIMM_CARD_SERVIC_BUTT == ucCardStatus)
        {
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%s",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          "BUSY");
            return AT_OK;
        }

        /* ���������ΪUSIMM_CARD_ROM_SIMָʾ��ǰΪ���ٿ�����Ч���޿� */
        if ((USIMM_CARD_ROM_SIM == ucCardType)
         || (USIMM_CARD_SERVIC_ABSENT == ucCardStatus))
        {
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          "%s:%s",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          "ERROR");
        }
        else
        {
            gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              (VOS_CHAR *)pgucAtSndCodeAddr,
                                              "%s:%s",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              "READY");
        }
        return AT_OK;
}
#endif
#if(FEATURE_ON == MBB_FEATURE_ESIM_SWITCH)

VOS_UINT32 At_QryTSimSwitchPara(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      TSimSwitchValue);
    return AT_OK;
}
#endif

VOS_UINT32 AT_QryBatVolPara(VOS_UINT8 ucIndex)
{

    /*��ȡ ��ص�ѹֵ*/
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                             gastAtClientTab[ucIndex].opId,
                                             DRV_AGENT_TBATVOLT_QRY_REQ,
                                             VOS_NULL_PTR,
                                             0,
                                             I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_TBATVOLT_QRY;           /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                            /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}

/* Added by f62575 for AT Project, 2011/10/20, begin */

VOS_UINT32 AT_DeciDigit2Ascii(
    VOS_UINT8                           aucDeciDigit[],
    VOS_UINT32                          ulLength,
    VOS_UINT8                           aucAscii[]
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulLength; ulLoop++)
    {
        if (aucDeciDigit[ulLoop] > 9)
        {
            return VOS_ERR;
        }

        aucAscii[ulLoop] = aucDeciDigit[ulLoop] + '0';
    }

    return VOS_OK;
}
/* Added by f62575 for AT Project, 2011/10/20, end */
#if (FEATURE_ON == MBB_COMMON)

VOS_UINT32 AT_QryTnetPortPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_FEATURE_ETH)
    VOS_UINT16 usLen = 0; 
    VOS_UINT32 cur_index = 1;
    NET_PORT_ST test_port_para = {0};
    unsigned char port_ip_add[] = {'1','9','2','.','1','6','8','.','8','.','1'}; 
    

    if (-1 == PhyATQryPortPara(&test_port_para))
    {
        return AT_ERROR;
    }

    if(0 == AT_STRLEN(test_port_para.ip_add))
    {
        MSP_MEMCPY(test_port_para.ip_add, port_ip_add, sizeof(port_ip_add));
    }
    
    usLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                            (TAF_CHAR *)pgucAtSndCodeAddr,
                            (TAF_CHAR *)pgucAtSndCodeAddr,
                            "%s:%d%s",
                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                            test_port_para.total_port,gaucAtCrLf); 
 
    for(cur_index = 0; cur_index < test_port_para.total_port; cur_index++) 
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                "%s:%d,%s%s",
                                g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                cur_index,
                                test_port_para.ip_add,gaucAtCrLf); 
    
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                "%s:%d%s",
                                g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                test_port_para.port_rate,
                                gaucAtCrLf); 
     }
    
    gstAtSendData.usBufLen = usLen;
   
    return AT_OK;
#else
    
    return AT_ERROR;
#endif
}

/*******************************************************************************
 ��������  : ether_atoe
 ��������  : Convert Ethernet address string representation to binary data
 �������  : a	string in xx:xx:xx:xx:xx:xx notation
 �������  : e	binary data
 �� �� ֵ  : TRUE if conversion was successful and FALSE otherwise
*******************************************************************************/
int ether_atoe(const char *a, unsigned char *e)
{
	char *str = (char *) a;
	int i = 0;

	memset(e, 0, 6);
    
	for (;;) 
    {
        e[i++] = (unsigned char)simple_strtol(str, &str, 16);
		if (!*str++ || (6 == i))
		{
			break;
        }
	}
    
	return (6 == i);
}

#define ET_MAC_BYTE_MAX     ((char)0xFF)
#define ET_MAC_BYTE_MIN     ((char)0x00)

/*******************************************************************************
 ��������  : et_macAddr_add
 ��������  : MAC + 1������ת���
 �������  : char *macAddr
 �������  : ��
 �� �� ֵ  : ��
*******************************************************************************/
void et_macAddr_add(char *macAddr, int add_val)
{
  
    while (add_val--)
    {
        if (ET_MAC_BYTE_MAX != macAddr[5])
        {
             macAddr[5] = macAddr[5] + 1;
        }
        else if (ET_MAC_BYTE_MAX != macAddr[4])
        {
            macAddr[4] = macAddr[4] + 1;
            macAddr[5] = ET_MAC_BYTE_MIN;
        }
        else if (ET_MAC_BYTE_MAX != macAddr[3])
        {
            macAddr[3] = macAddr[3] + 1;
            macAddr[4] = ET_MAC_BYTE_MIN;
            macAddr[5] = ET_MAC_BYTE_MIN;
        }
        else
        {   
            /*������3���ֽ�ȫΪ0xFF,�����λ���00:00:00���¿�ʼ*/

            macAddr[3] = ET_MAC_BYTE_MIN;
            macAddr[4] = ET_MAC_BYTE_MIN;
            macAddr[5] = ET_MAC_BYTE_MIN;
        }
    }
}

char itoa_mac(char i)
{
    if(i >= 0 && i <= 9)
        return i + '0';
    else if(i >= 0xA && i <= 0xF) 
        return i -0xA + 'A';
    else
        return '0';
}


VOS_UINT32 AT_GetPhynumWlanMac(VOS_UINT8 aucMacWlan[])
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucE5GwMacAddr[AT_MAC_ADDR_LEN + 1]; /* MAC��ַ*/
    VOS_UINT32                          ulE5GwMacAddrOffset;
    VOS_UINT32                          ulMacOffset;
    VOS_UINT8                           aucMacWlan_tmp[6] = {0};
    int                                 i,j;


    PS_MEM_SET(aucE5GwMacAddr, 0x00, sizeof(aucE5GwMacAddr));

    /* ��ȡMAC��ַ�ַ��� */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucE5GwMacAddr, AT_MAC_ADDR_LEN);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_GetPhynumMac: Fail to read en_Nv_Item_Imei_Svn.");
        return AT_ERROR;
    }
    
    /* MAC��ַ��ʽƥ��: 7A:FE:E2:21:11:E4=>7AFEE22111E4 */
    ether_atoe(aucE5GwMacAddr, aucMacWlan_tmp);
    /* MAC��ַ��1,ΪWLANMAC��ַ */
    et_macAddr_add(aucMacWlan_tmp, 1);

    for (i = 0,j = 0; i < (1 + AT_PHYNUM_MAC_COLON_NUM); i++,j=j+2)
    {
        aucMacWlan[j+1] = itoa_mac(aucMacWlan_tmp[i]&0xf);
        aucMacWlan_tmp[i] >>= 4;
        aucMacWlan[j] = itoa_mac(aucMacWlan_tmp[i]&0xf);
    }
 
    aucMacWlan[AT_PHYNUM_MAC_LEN] = '\0';

    return AT_OK;
}
#endif /* (FEATURE_ON == MBB_COMMON)&&(FEATURE_ON == CFG_BSP_CONFIG_BOARD_CPE) */

/* Added by f62575 for SMALL IMAGE, 2012-1-3, begin */

VOS_UINT32 AT_GetPhynumMac(VOS_UINT8 aucMac[])
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucE5GwMacAddr[AT_MAC_ADDR_LEN + 1]; /* MAC��ַ*/
    VOS_UINT32                          ulE5GwMacAddrOffset;
    VOS_UINT32                          ulMacOffset;


    PS_MEM_SET(aucE5GwMacAddr, 0x00, sizeof(aucE5GwMacAddr));

    /* ��ȡMAC��ַ�ַ��� */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucE5GwMacAddr, AT_MAC_ADDR_LEN);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_GetPhynumMac: Fail to read en_Nv_Item_Imei_Svn.");
        return AT_ERROR;
    }

    /* MAC��ַ��ʽƥ��: 7A:FE:E2:21:11:E4=>7AFEE22111E4 */
    ulMacOffset         = 0;
    ulE5GwMacAddrOffset = 0;
    for (ulLoop = 0; ulLoop < (1 + AT_PHYNUM_MAC_COLON_NUM); ulLoop++)
    {
        PS_MEM_CPY(&aucMac[ulMacOffset],
                   &aucE5GwMacAddr[ulE5GwMacAddrOffset],
                   AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS);
        ulMacOffset         += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS;
        ulE5GwMacAddrOffset += AT_WIFIGLOBAL_MAC_LEN_BETWEEN_COLONS + VOS_StrLen(":");
    }

    aucMac[AT_PHYNUM_MAC_LEN] = '\0';

    return AT_OK;
}
/* Added by f62575 for SMALL IMAGE, 2012-1-3, end */


VOS_UINT32 AT_QryPhyNumPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
    VOS_UINT32                          ulRet_wlan;
#endif
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucAsciiImei[TAF_PH_IMEI_LEN + 1];
    TAF_SVN_DATA_STRU                   stSvn;
    VOS_UINT8                           aucAsciiSvn[TAF_SVN_DATA_LENGTH + 1];
    /* Added by f62575 for SMALL IMAGE, 2012-1-3, begin */
    VOS_UINT8                           aucMac[AT_PHYNUM_MAC_LEN + 1]; /* MAC��ַ*/
#if (FEATURE_ON == MBB_COMMON)
    VOS_UINT8                           aucWlanMac[AT_PHYNUM_MAC_LEN + 1]; /* MAC��ַ*/
#endif
    /* Added by f62575 for SMALL IMAGE, 2012-1-3, end */
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */


    PS_MEM_SET(&stSvn, 0x00, sizeof(stSvn));


    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryPhyNumPara: Get modem id fail.");
        return AT_ERROR;
    }

    /* ��ȡNV���ȡIMEI */
    ulRet = AT_GetImeiValue(enModemId, aucAsciiImei);

    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_NV_Item_IMEI.");
        return AT_ERROR;
    }

    /* ��ȡNV���ȡSVN */
    ulRet = NV_ReadEx(enModemId, en_NV_Item_Imei_Svn, &stSvn, sizeof(stSvn));
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_Nv_Item_Imei_Svn.");
        return AT_ERROR;
    }
    else
    {
        if (NV_ITEM_ACTIVE != stSvn.ucActiveFlag)
        {
            PS_MEM_SET(aucAsciiSvn, '0', TAF_SVN_DATA_LENGTH);
        }
        else
        {
            AT_DeciDigit2Ascii(stSvn.aucSvn, TAF_SVN_DATA_LENGTH, aucAsciiSvn);
        }

        aucAsciiSvn[TAF_SVN_DATA_LENGTH] = '\0';
    }

    /* Added by f62575 for SMALL IMAGE, 2012-1-3, begin */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s:IMEI,%s%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      aucAsciiImei, gaucAtCrLf);

#if (FEATURE_ON == MBB_COMMON)
	if(TRUE == get_lan_support())
    {
        ulRet = AT_GetPhynumMac(aucMac);
        if (AT_OK != ulRet)
        {
            AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_NV_Item_IMEI.");
            return AT_ERROR;
        }
        /* MAC��ַ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:MAC,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           aucMac,
                                           gaucAtCrLf);
        
        if (BSP_MODULE_SUPPORT == DRV_GET_WIFI_SUPPORT() )
        {
            ulRet_wlan = AT_GetPhynumWlanMac(aucWlanMac);
            
            if (AT_OK != ulRet_wlan)
            {
                AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_NV_Item_IMEI.");
                return AT_ERROR;
            }
                    
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s:MACWLAN,%s%s%s",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               aucWlanMac,
                                               ",0,3",
                                               gaucAtCrLf);
        }
    }    
    else if (BSP_MODULE_SUPPORT == DRV_GET_WIFI_SUPPORT() )  
    {
        ulRet = AT_GetPhynumMac(aucMac);
        if (AT_OK != ulRet)
        {
            AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_NV_Item_IMEI.");
            return AT_ERROR;
        }
#if defined(BSP_CONFIG_BOARD_401HW) || defined(BSP_CONFIG_BOARD_506HW)\
 || defined(BSP_CONFIG_BOARD_506HW_2)
        /*����Ϊ�յ����,ͬʱ����Ҫ�޸�wifi mac��ַ����Ϊ2,ini�����ļ���Ҫͬ���޸�*/
        if('\0' == aucMac[0]) 
        {
            /* MAC��ַ��� */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:MACWLAN,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           aucMac,
                                           gaucAtCrLf);
	    }
	    else
        {
	        /* MAC��ַ��� */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:MACWLAN,%s,%d,%d%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           aucMac,
                                           0,
                                           1,
                                           gaucAtCrLf);
        }
#elif defined(BSP_CONFIG_BOARD_E5577S_324) || defined(BSP_CONFIG_BOARD_E5573CS_933)\
  || defined(BSP_CONFIG_BOARD_E5577BS_937) || defined(BSP_CONFIG_BOARD_E5573BS)
        /*����Ϊ�յ����,ͬʱ����Ҫ�޸�wifi mac��ַ����Ϊ4,ini�����ļ���Ҫͬ���޸�*/
        if('\0' == aucMac[0]) 
        {
            /* MAC��ַ��� */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:MACWLAN,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           aucMac,
                                           gaucAtCrLf);
        }
        else
        {
           /* MAC��ַ��� */
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:MACWLAN,%s,%d,%d%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           aucMac,
                                           0,
                                           3,
                                           gaucAtCrLf);
        }          
#else
        /* MAC��ַ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:MACWLAN,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           aucMac,
                                           gaucAtCrLf);

#endif
    }
#else
    if (BSP_MODULE_SUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        ulRet = AT_GetPhynumMac(aucMac);
        if (AT_OK != ulRet)
        {
            AT_WARN_LOG("AT_QryPhyNumPara: Fail to read en_NV_Item_IMEI.");
            return AT_ERROR;
        }

        /* MAC��ַ��� */
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s:MACWLAN,%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           aucMac,
                                           gaucAtCrLf);
    }
#endif

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s:SVN,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       aucAsciiSvn);

    /* Added by f62575 for SMALL IMAGE, 2012-1-3, end   */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_WriteActiveMessage(
    MODEM_ID_ENUM_UINT16                enModemId,
    MN_MSG_ACTIVE_MESSAGE_STRU         *pstOrgActiveMessageInfo,
    MN_MSG_ACTIVE_MESSAGE_STRU         *pstActiveMessageInfo
)
{
    VOS_UINT32                          ulRet;
    VOS_INT32                           lRet;
    VOS_UINT8                          *pucActiveMessageInfo;
    VOS_UINT8                          *pucEvaluate;

    /*1.�жϴ�д��ļ�����Ų�����NVIM�еĲ����Ƿ�һ�£�һ������дNVIMֱ���˳�*/
    if (pstOrgActiveMessageInfo->enActiveStatus == pstActiveMessageInfo->enActiveStatus)
    {
        if (pstOrgActiveMessageInfo->stUrl.ulLen == pstActiveMessageInfo->stUrl.ulLen)
        {
            if (pstOrgActiveMessageInfo->enMsgCoding == pstActiveMessageInfo->enMsgCoding)
            {
                lRet = VOS_MemCmp(pstOrgActiveMessageInfo->stUrl.aucUrl,
                                  pstActiveMessageInfo->stUrl.aucUrl,
                                  pstActiveMessageInfo->stUrl.ulLen);
                if (0 == lRet)
                {
                    return MN_ERR_NO_ERROR;
                }
            }
        }
    }

    /*2.д������Ų�����NVIM��*/
    /*2.1 ΪNVIM�洢�������������ڴ�*/
    pucActiveMessageInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT,
                                                     MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    if (VOS_NULL_PTR == pucActiveMessageInfo)
    {
        return MN_ERR_NOMEM;
    }

    /*2.2 ��������Ų������ݽṹת����NVIM�洢��������*/
    pucEvaluate  = pucActiveMessageInfo;
    *pucEvaluate = pstActiveMessageInfo->enActiveStatus;
    pucEvaluate++;

    *pucEvaluate = pstActiveMessageInfo->enMsgCoding;
    pucEvaluate++;

    *pucEvaluate = (VOS_UINT8)(pstActiveMessageInfo->stUrl.ulLen & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 8) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 16) & 0xff);
    pucEvaluate++;
    *pucEvaluate = (VOS_UINT8)((pstActiveMessageInfo->stUrl.ulLen >> 24) & 0xff);
    pucEvaluate++;

    PS_MEM_CPY(pucEvaluate,
               pstActiveMessageInfo->stUrl.aucUrl,
               (VOS_UINT16)pstActiveMessageInfo->stUrl.ulLen);

    /*2.3 д���������Ϣ��NVIM*/
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = NV_WriteEx(enModemId,
                       en_NV_Item_SMS_ActiveMessage_Para,
                       pucActiveMessageInfo,
                       MN_MSG_ACTIVE_MESSAGE_PARA_LEN);
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    if (NV_OK != ulRet)
    {
        ulRet = MN_ERR_CLASS_SMS_NVIM;
    }
    else
    {
        ulRet = MN_ERR_NO_ERROR;
    }

    PS_MEM_FREE(WUEPS_PID_AT, pucActiveMessageInfo);
    return ulRet;
}


TAF_UINT32 AT_QryRstriggerPara(
    TAF_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;
    TAF_UINT16                          usLength;
    MN_MSG_ACTIVE_MESSAGE_STRU          stActiveMessageInfo;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRslt;

    usLength  = 0;
    enModemId = MODEM_ID_0;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_SetRstriggerPara: Get modem id fail.");
        return AT_ERROR;
    }
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /*��ȡNVIM�м�¼�ļ�����Ų���*/
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_ReadActiveMessage(enModemId, &stActiveMessageInfo);
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    if (MN_ERR_NO_ERROR != ulRet)
    {
        AT_LOG1("AT_QryRstriggerPara: fail to get NVIM information, cause is %d",
                ulRet);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: 255,\"\"",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        if (MN_MSG_ACTIVE_MESSAGE_STATUS_ACTIVE != stActiveMessageInfo.enActiveStatus)
        {
            stActiveMessageInfo.enActiveStatus = MN_MSG_ACTIVE_MESSAGE_STATUS_DEACTIVE;
        }

        /*ƴ����Ӧ�ַ���: �����֣�����״̬��URL��Ϣ*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: ",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%d,\"",
                                            stActiveMessageInfo.enActiveStatus);

        usLength += (TAF_UINT16)At_PrintReportData(AT_CMD_MAX_LEN,
                                                   (TAF_INT8 *)pgucAtSndCodeAddr,
                                                   stActiveMessageInfo.enMsgCoding,
                                                   (pgucAtSndCodeAddr + usLength),
                                                   stActiveMessageInfo.stUrl.aucUrl,
                                                   (TAF_UINT16)stActiveMessageInfo.stUrl.ulLen);

        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "\"");
    }

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}


TAF_UINT32 At_QryClipPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /* ��ʼ�� */
    PS_MEM_SET(&para,0x00,sizeof(para));

    /* ����SsCode */
    para.SsCode = TAF_CLIP_SS_CODE;

    if(AT_SUCCESS == TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLIP_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryClirPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /* ��ʼ�� */
    PS_MEM_SET(&para,0x00,sizeof(para));

    /* ����SsCode */
    para.SsCode = TAF_CLIR_SS_CODE;

    if (TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId,
        0, &para) == TAF_SUCCESS)
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLIR_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryColpPara(TAF_UINT8 ucIndex)
{
    TAF_SS_INTERROGATESS_REQ_STRU para;

    /* ��ʼ�� */
    PS_MEM_SET(&para,0x00,sizeof(para));

    /* ����SsCode */
    para.SsCode = TAF_COLP_SS_CODE;

    para.OP_BsService = 0;

    if(AT_SUCCESS == TAF_InterrogateSSReq(gastAtClientTab[ucIndex].usClientId, 0,&para))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COLP_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryS0Para(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
    AT_MODEM_CC_CTX_STRU               *pstCcCtx = VOS_NULL_PTR;

    pstCcCtx = AT_GetModemCcCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen  = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%d",
                                                    pstCcCtx->stS0TimeInfo.ucS0TimerLen);
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, End */
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS3Para
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS3Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS3);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS4Para
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS4Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS4);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS5Para
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS5Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS5);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS6Para
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-05-27
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS6Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS6);
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryS7Para
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-05-27
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryS7Para(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%03d",ucAtS7);
    return AT_OK;
}

TAF_UINT32 At_QryCusdPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CUSD_RPT_TYPE;

    /* ��MTA����+cusd��ѯ���� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}

TAF_UINT32 At_QryCcwaPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->ucCcwaType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, End */
    return AT_OK;
}
/*****************************************************************************
 Prototype      : At_QryCpinPara
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  1.Date        : 2009-08-25
    Author      : h44270
    Modification: ���ⵥ�ţ�AT2D14070
*****************************************************************************/
TAF_UINT32 At_QryCpinPara(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    PS_MEM_SET(&stPinData,0x00,sizeof(stPinData));

    stPinData.CmdType = TAF_PIN_QUERY;

    stPinData.PinType = TAF_SIM_NON;


    if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
 Prototype      : At_QryIccidPara
 Description    : ^ICCID��ѯ
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_WAIT_ASYNC_RETURN
                  AT_ERROR
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-08-27
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryIccidPara(TAF_UINT8 ucIndex)
{
    /* ִ��������� */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_ICC_ID,TAF_NULL_PTR))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ICCID_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

	

TAF_UINT32 At_QryCardTypePara(TAF_UINT8 ucIndex)
{
    VOS_UINT32 ulResult;

    ulResult = SI_PIH_CardTypeQuery(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("SI_PIH_CardTypeQuery: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CARDTYPE_QUERY;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryPNNPara (TAF_UINT8 ucIndex)
{
#if 0
    VOS_UINT32                      ulFileExist;

    ulFileExist = USIMM_IsServiceAvailable(USIM_SVR_PLMN_NTWRK_NAME);
    if (PS_USIM_SERVICE_AVAILIABLE != ulFileExist)
    {
        return AT_ERROR;
    }

    return AT_OK;
#endif

    return AT_OK;
}


TAF_UINT32 At_QryCPNNPara (TAF_UINT8 ucIndex)
{
    /*Modified by l60609 for At Project, 2011-11-3, Begin */
    VOS_UINT32                          ulRst;

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_CPNN_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPNN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
    /*Modified by l60609 for At Project, 2011-11-3, Begin */
}


TAF_UINT32 At_QryOPLPara (TAF_UINT8 ucIndex)
{
#if 0
    VOS_UINT32                      ulFileExist;

    ulFileExist = USIMM_IsServiceAvailable(USIM_SVR_OPLMN_LIST);
    if (PS_USIM_SERVICE_AVAILIABLE != ulFileExist)
    {
        return AT_ERROR;
    }

    return AT_OK;
#endif

    return AT_OK;

}

/*****************************************************************************
 Prototype      : At_QryCpinStatus
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-09-29
    Author      : ---
    Modification: Created function by z100318
*****************************************************************************/
TAF_UINT32 At_QryCpinStatus(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    PS_MEM_SET(&stPinData,0x00,sizeof(stPinData));

    stPinData.CmdType = TAF_PIN_RemainTime;
    stPinData.PinType = TAF_SIM_NON;

    if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_QryCardlockPara
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2007-03-15
    Author      : luojian
    Modification: Created function by z100318
*****************************************************************************/
TAF_UINT32 At_QryCardlockPara(TAF_UINT8 ucIndex)
{
    TAF_ME_PERSONALISATION_DATA_STRU    stMePersonalisationData;

    PS_MEM_SET(&stMePersonalisationData, 0, sizeof(TAF_ME_PERSONALISATION_DATA_STRU));

    /* ��ȫ��������Ϊ��ѯ */
    stMePersonalisationData.CmdType     = TAF_ME_PERSONALISATION_QUERY;
    /* ��������Ϊ������ */
    stMePersonalisationData.MePersonalType = TAF_OPERATOR_PERSONALISATION;
    /* ִ��������� */
    if(AT_SUCCESS == Taf_MePersonalisationHandle(gastAtClientTab[ucIndex].usClientId, 0,&stMePersonalisationData))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CARD_LOCK_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCpin2Para(TAF_UINT8 ucIndex)
{
    TAF_PH_PIN_DATA_STRU stPinData;

    PS_MEM_SET(&stPinData,0x00,sizeof(stPinData));

    /* Modified by L47619 for AP-Modem Personalisation Project, 2012/04/21, begin */
    stPinData.CmdType = TAF_PIN2_QUERY;
    /* Modified by L47619 for AP-Modem Personalisation Project, 2012/04/21, end */

    stPinData.PinType = TAF_SIM_NON;

    if(AT_SUCCESS == Taf_PhonePinHandle(gastAtClientTab[ucIndex].usClientId, 0,&stPinData))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPIN2_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryCpbsPara(TAF_UINT8 ucIndex)
{
    gulPBPrintTag = VOS_TRUE;

    if(AT_SUCCESS == SI_PB_Query(gastAtClientTab[ucIndex].usClientId,0))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPBS_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }

}

TAF_UINT32 At_QryCfunPara(TAF_UINT8 ucIndex)
{
    TAF_PH_OP_MODE_STRU    PhModeSet;


    PS_MEM_SET(&PhModeSet, 0x00, sizeof(PhModeSet));

    PhModeSet.CmdType = TAF_PH_CMD_QUERY;
    if(AT_SUCCESS == Taf_DefPhMode(gastAtClientTab[ucIndex].usClientId, 0,PhModeSet))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFUN_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_QryCpamPara
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryCpamPara(TAF_UINT8 ucIndex)
{
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_ACCESS_MODE_PARA,TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPAM_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryStsfPara(TAF_UINT8 ucIndex)
{
    USIMM_STK_CFG_STRU                  ProfileContent={0};
    TAF_UINT32                          Result ;
    TAF_UINT16                          NVLen = sizeof(USIMM_STK_CFG_STRU);
    TAF_UINT16                          Length = 0;
    MODEM_ID_ENUM_UINT16                usModemId;

    Result = NV_ReadEx(MODEM_ID_0, en_NV_Item_TerminalProfile_Set, &ProfileContent, NVLen);

    if(NV_OK != Result)
    {
        return AT_ERROR;
    }

    if (VOS_OK != AT_GetModemIdFromClient(ucIndex, &usModemId))
    {
        return AT_ERROR;
    }

    Length += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR*)pgucAtSndCodeAddr+Length,
                                                "^STSF:%d,",
                                                ProfileContent.ucFuncEnable);

    if (USIMM_CARD_USIM == AT_GetUsimInfoCtxFromModemId(usModemId)->enCardType)
    {
        Length += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN,
                                                    (TAF_INT8 *)pgucAtSndCodeAddr,
                                                    (TAF_UINT8 *)pgucAtSndCodeAddr+Length,
                                                    ProfileContent.stUsimProfile.aucProfile,
                                                    ProfileContent.stUsimProfile.ucProfileLen);
    }
    else
    {
        Length += (TAF_UINT16)At_HexAlpha2AsciiString(AT_CMD_MAX_LEN,
                                                    (TAF_INT8 *)pgucAtSndCodeAddr,
                                                    (TAF_UINT8 *)pgucAtSndCodeAddr+Length,
                                                    ProfileContent.stSimProfile.aucProfile,
                                                    ProfileContent.stSimProfile.ucProfileLen);

    }

    Length += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr+Length,
                                                    ",%d",
                                                    ProfileContent.ucTimer);

    gstAtSendData.usBufLen = Length;

    return AT_OK;
}

/*****************************************************************************
 Prototype      : At_QryStgiPara
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryStgiPara(TAF_UINT8 ucIndex)
{
    if(TAF_FALSE == g_ulSTKFunctionFlag)
    {
        return AT_ERROR;
    }

    if(AT_SUCCESS == SI_STK_QuerySTKCommand(gastAtClientTab[ucIndex].usClientId,USAT_CMDQRYSTGI))
    {
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryImsichgPara(TAF_UINT8 ucIndex)
{
    /*Modified by l60609 for At Project, 2011-11-3, Begin */
    VOS_UINT32                          ulRst;

    if (VOS_FALSE == SI_STKIsDualImsiSupport())
    {
        return AT_CMD_NOT_SUPPORT;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_IMSICHG_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMSICHG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
    /*Modified by l60609 for At Project, 2011-11-3, Begin */
}


TAF_UINT32 At_QryCgclassPara(TAF_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    VOS_UINT16                          usLength = 0;

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: ",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"\"A\"");

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
}
/*****************************************************************************
 Prototype      : At_QryCopsPara
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryCopsPara(TAF_UINT8 ucIndex)
{
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_NETWORKNAME_PARA,TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 At_QryCgcattPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                           ulRst;
    VOS_UINT8                            ucType;

    ucType = TAF_PH_PS_CS_OPERATE;

    /* AT��MMAģ�鷢��Ϣ��Ҫ��MMA����CS��PS��ע��״̬ */
    ulRst  = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    TAF_MSG_MMA_GET_CURRENT_ATTACH_STATUS,
                                    (VOS_VOID*)&ucType,  /*Ҫ���ѯCS��PS��ע��״̬*/
                                    sizeof(VOS_UINT8),
                                    I0_WUEPS_PID_MMA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

VOS_UINT32 At_QryCgattPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                           ulRst;
    VOS_UINT8                            ucType;

    ucType = TAF_PH_PS_OPERATE;

    /* AT��MMAģ�鷢��Ϣ��Ҫ��MMA����CS��PS��ע��״̬ */
    ulRst  = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                    gastAtClientTab[ucIndex].opId,
                                    TAF_MSG_MMA_GET_CURRENT_ATTACH_STATUS,
                                    (VOS_VOID*)&ucType, /*Ҫ���ѯPS��ע��״̬��*/
                                    sizeof(VOS_UINT8),
                                    I0_WUEPS_PID_MMA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMA_GET_CURRENT_ATTACH_STATUS;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}


TAF_UINT32 AT_QryCgauthPara(TAF_UINT8 ucIndex)
{
    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetPdpAuthInfo(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTH_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_QryCgdnsPara(TAF_UINT8 ucIndex)
{
    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetPdpDnsInfo(WUEPS_PID_AT,
                                        gastAtClientTab[ucIndex].usClientId,
                                        0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDNS_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_QryCgautoPara(TAF_UINT8 ucIndex)
{
    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetAnsModeInfo(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGAUTO_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_QryCgtftPara(TAF_UINT8 ucIndex)
{
    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetTftInfo(WUEPS_PID_AT,
                                     gastAtClientTab[ucIndex].usClientId,
                                     0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGTFT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 AT_QryCgactPara(TAF_UINT8 ucIndex)
{
    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetPdpContextState(WUEPS_PID_AT,
                                             gastAtClientTab[ucIndex].usClientId,
                                             0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGACT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryCgdcontPara(VOS_UINT8 ucIndex)
{
    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetPrimPdpContextInfo(WUEPS_PID_AT,
                                                gastAtClientTab[ucIndex].usClientId,
                                                0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDCONT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryCgeqreqPara(VOS_UINT8 ucIndex)
{
    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetUmtsQosInfo(WUEPS_PID_AT,
                                         gastAtClientTab[ucIndex].usClientId,
                                         0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQREQ_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 At_QryCgeqminPara(VOS_UINT8 ucIndex)
{
    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetUmtsQosMinInfo(WUEPS_PID_AT,
                                            gastAtClientTab[ucIndex].usClientId,
                                            0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGEQMIN_READ;

    return AT_WAIT_ASYNC_RETURN;
}

VOS_UINT32 AT_QryCgdscontPara(VOS_UINT8 ucIndex)
{
    /* ִ��������� */
    if ( VOS_OK != TAF_PS_GetSecPdpContextInfo(WUEPS_PID_AT,
                                               gastAtClientTab[ucIndex].usClientId,
                                               0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGDSCONT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCrcPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->ucCrcType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, End */
    return AT_OK;
}


TAF_UINT32 At_QryCbstPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d,%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->stCbstDataCfg.enSpeed,
                                                    pstSsCtx->stCbstDataCfg.enName,
                                                    pstSsCtx->stCbstDataCfg.enConnElem);
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, End */

    return AT_OK;

}

TAF_UINT32 At_QryCmodPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->enCModType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, End */
    return AT_OK;
}


TAF_UINT32 At_QryCstaPara(TAF_UINT8 ucIndex)
{

    gstAtSendData.usBufLen  = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,g_enAtCstaNumType);

    return AT_OK;
}


TAF_UINT32 At_QryCcugPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength = 0;
    TAF_UINT16                          usIndex;
    TAF_UINT16                          usInfo;
    /* Modified by l60609 for DSDA Phase III, 2013-2-21, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    if (0 == pstSsCtx->stCcugCfg.bIndexPresent)
    {
        usIndex = 10;
    }
    else
    {
        usIndex = (TAF_UINT16)pstSsCtx->stCcugCfg.ulIndex;
    }

    usInfo = (TAF_UINT16)((pstSsCtx->stCcugCfg.bSuppressPrefer << 1) | pstSsCtx->stCcugCfg.bSuppressOA);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,pstSsCtx->stCcugCfg.bEnable);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",usIndex);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,",%d",usInfo);

    /* Modified by l60609 for DSDA Phase III, 2013-2-21, End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


TAF_UINT32 At_QryCssnPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CSSN_RPT_TYPE;

    /* ��MTA����^cssn��ѯ���� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCnmiPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength            = 0;
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,pstSmsCtx->stCnmiType.CnmiModeType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiMtType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiBmType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiDsType);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr + usLength,",%d",pstSmsCtx->stCnmiType.CnmiBfrType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}


TAF_UINT32 At_QryCmgfPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->enCmgfMsgFormat);
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, End */

    return AT_OK;
}

/* Modified by f62575 for AT Project��2011-10-03,  Begin */

VOS_UINT32 At_QryCscaPara(VOS_UINT8 ucIndex)
{
    /* Modified by f62575 for AT Project��2011-10-03,  Begin*/
    VOS_UINT32                          ulRet;
    MN_MSG_READ_COMM_PARAM_STRU         stReadParam;

    /*  ����Ҫ��ѯ�Ķ������ĺ���洢λ�� :
    ATģ���ȡ�������ĺ���Ȳ���Ĭ�ϴ�SIM����EFSMSP�ļ��ĵ�һ����¼�л�ȡ */
    stReadParam.ulIndex     = 0;
    stReadParam.enMemStore  = MN_MSG_MEM_STORE_SIM;
    PS_MEM_SET(stReadParam.aucReserve1, 0x00, sizeof(stReadParam.aucReserve1));

    /* ����Ϣ��C�˻�ȡ�������ĺ��� */
    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = MN_MSG_ReadSrvParam(gastAtClientTab[ucIndex].usClientId,
                                gastAtClientTab[ucIndex].opId,
                                &stReadParam);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSCA_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified by f62575 for AT Project��2011-10-03,  End*/
}
/* Modified by f62575 for AT Project��2011-10-03,  End */


TAF_UINT32 At_QryCsmsPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d,",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->enCsmsMsgVersion);
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */
    At_PrintCsmsInfo(ucIndex);
    return AT_OK;
}


TAF_UINT32 At_QryCsmpPara(TAF_UINT8 ucIndex)
{
    TAF_UINT16                          usLength            = 0;
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;
    MN_MSG_VALID_PERIOD_ENUM_U8         enValidPeriod;                          /*TP Validity Period Format*/

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (TAF_TRUE == pstSmsCtx->stCscaCsmpInfo.bFoUsed)
    {
        /* <fo> */
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                           "%s: %d,",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                           pstSmsCtx->stCscaCsmpInfo.ucFo);

        AT_GET_MSG_TP_VPF(enValidPeriod, pstSmsCtx->stCscaCsmpInfo.ucFo);

        /* <vp> */
        if (enValidPeriod == pstSmsCtx->stCscaCsmpInfo.stVp.enValidPeriod)
        {
            usLength += At_MsgPrintVp(&(pstSmsCtx->stCscaCsmpInfo.stVp), (pgucAtSndCodeAddr + usLength));
        }

    }
    else
    {
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                          "%s: ,",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }

    /* <pid>  <dcs> */
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength,
                                       ",%d,%d",
                                       pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucPid,
                                       pstSmsCtx->stCscaCsmpInfo.stParmInUsim.ucDcs);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

TAF_UINT32 At_QryCpmsPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    if (AT_OK != At_GetSmsStorage(ucIndex,
                                  pstSmsCtx->stCpmsInfo.enMemReadorDelete,
                                  pstSmsCtx->stCpmsInfo.enMemSendorWrite,
                                  pstSmsCtx->stCpmsInfo.stRcvPath.enSmMemStore))
    {
        return AT_ERROR;
    }
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPMS_READ;
    return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
}


TAF_UINT32 At_QryCgsmsPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->stCgsmsSendDomain.enSendDomain);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    return AT_OK;
}



TAF_UINT32 At_QryCmgdPara(TAF_UINT8 ucIndex)
{
    MN_MSG_LIST_PARM_STRU               stListPara;
    /* Added by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);
    /* Added by l60609 for DSDA Phase III, 2013-2-20, End */

    stListPara.bChangeFlag = VOS_FALSE;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    stListPara.enMemStore  = pstSmsCtx->stCpmsInfo.enMemReadorDelete;
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */
    stListPara.enStatus    = MN_MSG_STATUS_NONE;
    PS_MEM_SET(stListPara.aucReserve1, 0x00, sizeof(stListPara.aucReserve1));

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    if (MN_ERR_NO_ERROR == MN_MSG_Delete_Test(gastAtClientTab[ucIndex].usClientId,
                                         gastAtClientTab[ucIndex].opId,
                                         &stListPara))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMGD_TEST;
        g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
        AT_CLIENT_STATUS_PRINT_2(ucIndex, g_stParseContext[ucIndex].ucClientStatus);
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCmmsPara(
    TAF_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;

    gastAtClientTab[ucIndex].opId = At_GetOpId();
    ulRet = MN_MSG_GetLinkCtrl(gastAtClientTab[ucIndex].usClientId,
                               gastAtClientTab[ucIndex].opId);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMMS_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


VOS_UINT32 At_QryCscbPara(
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT32                          ulRet;

    gastAtClientTab[ucIndex].opId = At_GetOpId();

    ulRet = MN_MSG_GetAllCbMids(gastAtClientTab[ucIndex].usClientId,
                             gastAtClientTab[ucIndex].opId);
    if (MN_ERR_NO_ERROR == ulRet)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSCB_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif

/*****************************************************************************
 Prototype      : At_QryCgregPara
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryCgregPara(TAF_UINT8 ucIndex)
{
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_PS_REG_STATE_PARA,TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CGREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if(FEATURE_ON == FEATURE_LTE)

VOS_UINT32 At_QryCeregPara(VOS_UINT8 ucIndex)
{
    if (AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId, 0, TAF_PH_EPS_REG_STATE_PARA, TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CEREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#endif
/*****************************************************************************
 Prototype      : At_QryCregPara
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryCregPara(TAF_UINT8 ucIndex)
{
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,0,TAF_PH_CS_REG_STATE_PARA,TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CREG_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

TAF_UINT32 At_QryCsdhPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->ucCsdhType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    return AT_OK;
}

TAF_UINT32 At_QryCscsPara(TAF_UINT8 ucIndex)
{
    if(AT_CSCS_IRA_CODE == gucAtCscsType)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"IRA\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else if (AT_CSCS_UCS2_CODE == gucAtCscsType)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"UCS2\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: \"GSM\"",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    }
    return AT_OK;
}


TAF_UINT32 At_QryCmeePara(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr,"%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,gucAtCmeeType);
    return AT_OK;
}


TAF_UINT32 At_QryParaCmd(TAF_UINT8 ucIndex)
{
    AT_RRETURN_CODE_ENUM ulResult = AT_FAILURE;

    if(TAF_NULL_PTR != g_stParseContext[ucIndex].pstCmdElement->pfnQryProc)
    {
        ulResult = (AT_RRETURN_CODE_ENUM)g_stParseContext[ucIndex].pstCmdElement->pfnQryProc(ucIndex);

        if(AT_WAIT_ASYNC_RETURN == ulResult)
        {
            /* ����ʱ�� */
            if(AT_SUCCESS != At_StartTimer(g_stParseContext[ucIndex].pstCmdElement->ulQryTimeOut,ucIndex))
            {
                AT_ERR_LOG("At_QryParaCmd:ERROR:Start Timer");
                return AT_ERROR;
            }

            g_stParseContext[ucIndex].ucClientStatus = AT_FW_CLIENT_STATUS_PEND;
            AT_CLIENT_STATUS_PRINT_2(ucIndex, g_stParseContext[ucIndex].ucClientStatus);
        }
        return ulResult;
    }
    else
    {
        return AT_ERROR;
    }
}

/* BEGIN: Added by liuyang id:48197, 2006/8/2   PN:A32D02883*/


TAF_UINT32 At_QryFPlmnPara(TAF_UINT8 ucIndex)
{
    if(AT_SUCCESS ==    Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                      0,
                                      TAF_PH_FPLMN_PARA,
                                      TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CFPLMN_READ;           /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                         /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;                    /* ���󷵻� */

    }
}


VOS_UINT32 At_QryMaxFreelockSizePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡ MFREELOCKSIZE��Ϣ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_MFREELOCKSIZE_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("At_QryMaxFreelockSizePara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MFREELOCKSIZE_READ;
    return AT_WAIT_ASYNC_RETURN;

/* Modified  by f62575 for AT Project, 2011-10-17, end */

}


VOS_UINT32 At_QryCpuLoadPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡ CPULOAD��Ϣ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_CPULOAD_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("At_QryCpuLoadPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPULOAD_READ;
    return AT_WAIT_ASYNC_RETURN;

/* Modified  by f62575 for AT Project, 2011-10-17, end */

}


VOS_UINT32 At_QryLcStartTimePara(VOS_UINT8 ucIndex)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    VOS_UINT8                          *pucSystemAppConfig;

    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();



    if (SYSTEM_APP_WEBUI != *pucSystemAppConfig)
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_ulLcStartTime);
    return AT_OK;

}


TAF_UINT32 At_QryDialModePara(TAF_UINT8 ucIndex)
{
    VOS_UINT8   ucDialmode;
    VOS_UINT8   ucCdcSpec;
    VOS_UINT32  ulRst;

    /* ���õ���ӿڣ����ݵ�ǰ���豸��̬����ȡ��ǰ֧�ֵĲ��ŷ�ʽ */
    /* ucRst:       VOS_OK/VOS_ERR */
    /* ucDialmode:  0 - ʹ��Modem����; 1 - ʹ��NDIS����; 2 - Modem��NDIS���� */
    /* ucCdcSpec:   0 - Modem/NDIS������CDC�淶; 1 - Modem����CDC�淶;
                    2 - NDIS����CDC�淶;         3 - Modem/NDIS������CDC�淶 */


    ucDialmode = 0;
    ucCdcSpec  = 0;

    ulRst = (VOS_UINT32)DRV_GET_DIAG_MODE_VALUE(&ucDialmode, &ucCdcSpec);

    if (VOS_OK != ulRst)
    {
        AT_ERR_LOG("At_QryDialModePara:ERROR:DRV_GET_DIAG_MODE_VALUE Return Err!");
        return AT_ERROR;
    }

#ifdef BSP_CONFIG_BOARD_K5160
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                                   (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d,%d,%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucDialmode, ucCdcSpec, 
                                                    AT_VOX_MODEM_PORT_NUM, 
                                                    AT_VOX_NDIS_PORT_NUM);
#else
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucDialmode, ucCdcSpec);
#endif/*BSP_CONFIG_BOARD_K5160*/

    return AT_OK;
}



TAF_UINT32 At_QryPortSelPara(TAF_UINT8 ucIndex)
{
    gstAtSendData.usBufLen =
        (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                               (TAF_CHAR*)pgucAtSndCodeAddr,
                               (TAF_CHAR*)pgucAtSndCodeAddr,
                               "%s: %d",
                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                               gucAtPortSel);
    return AT_OK;
}


TAF_UINT32 At_QryCurcPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* AT ��MTA ����CURC��ѯ������Ϣ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_CURC_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_QryCurcPara: send Msg fail.");
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CURC_READ;

    return AT_WAIT_ASYNC_RETURN;

}


TAF_UINT32 At_QryTimePara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_TIME_RPT_TYPE;

    /* ��MTA����^time��ѯ���� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


TAF_UINT32 At_QryCtzrPara(TAF_UINT8 ucIndex)
{
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU     stAtCmd;
    VOS_UINT32                              ulResult;

    PS_MEM_SET(&stAtCmd, 0x00, sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU));
    stAtCmd.enReqType       = AT_MTA_QRY_CTZR_RPT_TYPE;

    /* ��MTA����^ctzr��ѯ���� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_UNSOLICITED_RPT_QRY_REQ,
                                   &stAtCmd,
                                   sizeof(AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU),
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_UNSOLICITED_RPT_READ;

    return AT_WAIT_ASYNC_RETURN;
}




VOS_UINT32 At_QryQuickStart(TAF_UINT8 ucIndex)
{
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   TAF_PH_QUICK_START_PARA,
                                   TAF_NULL_PTR))
    {
        /*���õ�ǰ����ģʽ */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CQST_READ;
        /* �ȴ��첽�¼����� */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        /* ���󷵻� */
        return AT_ERROR;
    }
}

VOS_UINT32 At_QryAutoAttach(TAF_UINT8 ucIndex)
{
    if (AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                    0,
                                    TAF_PH_AUTO_ATTACH_PARA,
                                    TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CAATT_READ;             /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                            /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QrySysCfgExPara(VOS_UINT8 ucIndex)
{
    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfgExSetPara;

    VOS_UINT32                          ulRst;


    PS_MEM_SET(&stSysCfgExSetPara, 0x00, sizeof(stSysCfgExSetPara));


    ulRst = Taf_SysCfgHandle(gastAtClientTab[ucIndex].usClientId,
                             0,
                             stSysCfgExSetPara);

    if (AT_SUCCESS == ulRst)
    {
        /* ���õ�ǰ����ģʽΪAT_CMD_SYSCFGEX_READ,�ȴ��첽�¼����� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSCFGEX_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        /* ����ʧ�� */
        return AT_ERROR;
    }

}




TAF_UINT32 At_QrySysCfgPara(TAF_UINT8 ucIndex)
{
    TAF_MMA_SYS_CFG_PARA_STRU           stSysCfgSetPara;


    PS_MEM_SET(&stSysCfgSetPara, 0x00, sizeof(stSysCfgSetPara));


    if (AT_SUCCESS == Taf_SysCfgHandle(gastAtClientTab[ucIndex].usClientId,
                                       0,
                                       stSysCfgSetPara))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SYSCFG_READ;             /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                            /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}


#if(FEATURE_ON == FEATURE_LTE)

TAF_UINT32 At_QryCemode(TAF_UINT8 ucIndex)
{
    if (AT_SUCCESS == TAF_PS_GetCemodeInfo(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {

        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CEMODE_READ;             /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                            /* �ȴ��첽�¼����� */
    }
    else
    {
        vos_printf(" At_QryCemode TAF_PS_GetCemodeInfo fail\n");
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryLtecsInfo(TAF_UINT8 ucIndex)
{

    if(AT_SUCCESS == TAF_PS_GetLteCsInfo(WUEPS_PID_AT, gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LTECS_READ;

        /* ������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
#endif

VOS_UINT32 At_QryClvlPara(VOS_UINT8 ucIndex)
{
    if (VOS_OK == APP_VC_GetVoiceVolume(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLVL_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryVMSETPara(VOS_UINT8 ucIndex)
{
    /* ���ǲ�ѯ����ز������� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*��ȡ��ǰ�����豸ģʽ��0 �ֳ֣�1 �ֳ����᣻2 �������᣻3 ������4 ������5 PC����ģʽ */
    if (VOS_OK == APP_VC_GetVoiceMode(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VMSET_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }

}


TAF_UINT32 At_QryRRCVersion(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* ������ϢID_AT_MTA_WRR_RRC_VERSION_QRY_REQ��AT������ */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_RRC_VERSION_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_RRC_VERSION_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCSNR(TAF_UINT8 ucIndex)
{
    /* ��MMA������Ϣ����ѯ�²�������TAF_PH_CSNR_VALUE_PARA */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   TAF_PH_CSNR_VALUE_PARA,
                                   TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSNR_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

/*****************************************************************************
 Prototype      : At_QryQOSIG
 Description    : �������Ⱥ��ź�ǿ��
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---
 History        : ---
*****************************************************************************/
#if(FEATURE_ON == MBB_FEATURE_BOX_FTEN)
TAF_UINT32 At_QryQOSIG(TAF_UINT8 ucIndex)
{
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   TAF_PH_QOSIG_VALUE_PARA,
                                   TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_QOSIG_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}
/*****************************************************************************
 Prototype      : At_QryERROR
 Description    : ��ȡע��򲦺�ʧ��ԭ��
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---
 History        : ---
*****************************************************************************/
TAF_UINT32 At_QryERROR(TAF_UINT8 ucIndex)
{
    VOS_UINT16                        usLength = 0;
    TAF_ERROR_CAUSE_ENUM_UINT8        cause = TAF_ERROR_CAUSE_DEFAULT;

    switch(AT_GetCsCallErrCause(ucIndex))
    {
        case TAF_CS_CAUSE_SUCCESS:
            cause = TAF_ERROR_CAUSE_SUCCESS;
            break;

        case TAF_CS_CAUSE_SIM_NOT_EXIST:
        case TAF_CS_CAUSE_SIM_PIN_NEED:
            cause = TAF_ERROR_CAUSE_SIM;
            break;

        case TAF_CS_CAUSE_INVALID_PARAMETER:
        case TAF_CS_CAUSE_NO_CALL_ID:
        case TAF_CS_CAUSE_NOT_ALLOW:
        case TAF_CS_CAUSE_STATE_ERROR:
        case TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY :
        case TAF_CS_CAUSE_CALL_CTRL_TIMEOUT:
        case TAF_CS_CAUSE_CALL_CTRL_NOT_ALLOWED:
            cause = TAF_ERROR_CAUSE_ATD;
            break;

        case TAF_CS_CAUSE_CC_NW_UNASSIGNED_CAUSE:
            cause = TAF_ERROR_CAUSE_NWERROR1;
            break;

        case TAF_CS_CAUSE_CC_NW_NO_ROUTE_TO_DEST:
        case TAF_CS_CAUSE_POWER_OFF:
            cause = TAF_ERROR_CAUSE_NWERROR2 ;
            break;

        default:
            cause = TAF_ERROR_CAUSE_DEFAULT;
            break;
    }
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                   "%s: %d,0",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   (TAF_ERROR_CAUSE_ENUM_UINT8)cause);
    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}
#endif

TAF_UINT32 At_QryFreqLock(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* ������ϢID_AT_MTA_WRR_FREQLOCK_QRY_REQ��AT������ */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_WRR_FREQLOCK_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FREQLOCK_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

TAF_UINT32 At_QryU2DiagPara(TAF_UINT8 ucIndex)
{
    AT_USB_ENUM_STATUS_STRU             stUsbEnumStatus;
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;


    stPidEnableType.ulPidEnabled = VOS_FALSE;

    PS_MEM_SET(&stUsbEnumStatus, 0x00, sizeof(stUsbEnumStatus));


    /* ��ȡPIDʹ��NV�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PID_Enable_Type,
                        &stPidEnableType,
                        sizeof(AT_PID_ENABLE_TYPE_STRU)))
    {
        return AT_ERROR;
    }

    /* NV��ȡ�ɹ������PID�Ƿ�ʹ�ܣ���ʹ�ܣ�����ERROR */
    if (VOS_FALSE != stPidEnableType.ulPidEnabled)
    {
        return AT_ERROR;
    }

    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_USB_Enum_Status,
                         &stUsbEnumStatus,
                         sizeof(AT_USB_ENUM_STATUS_STRU)))
    {
        return AT_ERROR;
    }

    if (0 == stUsbEnumStatus.ulStatus)
    {
        /* ��en_NV_Item_USB_Enum_Statusδ���ã�����õ����API����ȡĬ�ϵ�USB�豸��̬ */
        stUsbEnumStatus.ulValue = DRV_GET_U2DIAG_DEFVALUE();
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stUsbEnumStatus.ulValue);
    return AT_OK;
}


VOS_UINT32 At_QryPort(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          i;
    VOS_UINT32                          j;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucCount;
    VOS_UINT32                          ulResult;
    DRV_DYNAMIC_PID_TYPE_STRU           stDynamicPidType;
    /* Modified by f62575 for B050 Project, 2012-2-3, Begin   */
    AT_PID_ENABLE_TYPE_STRU             stPidEnableType;
    /* Modified by f62575 for B050 Project, 2012-2-3, end   */

    usLength = 0;
    ucCount  = 0;


    stPidEnableType.ulPidEnabled = VOS_FALSE;


    PS_MEM_SET(&stDynamicPidType, 0x00, sizeof(DRV_DYNAMIC_PID_TYPE_STRU));

    /* Modified by f62575 for B050 Project, 2012-2-3, Begin   */
    /* ��ȡPIDʹ��NV�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PID_Enable_Type,
                        &stPidEnableType,
                        sizeof(AT_PID_ENABLE_TYPE_STRU)))
    {
        AT_ERR_LOG("At_QryPort:Read NV fail!");
        return AT_ERROR;
    }

    /* NV��ȡ�ɹ������PID�Ƿ�ʹ�ܣ�����ʹ�ܣ�����ERROR */
    if (VOS_TRUE != stPidEnableType.ulPidEnabled)
    {
        AT_WARN_LOG("At_QryPort:The PID is not enabled!");
        return AT_ERROR;
    }
    /* Modified by f62575 for B050 Project, 2012-2-3, end   */

    /* ��ѯ��ǰ�˿���̬ */
    ulResult = DRV_SET_PORT_QUIRY(&stDynamicPidType);
    if (AT_SUCCESS != ulResult)
    {
        AT_ERR_LOG("At_QryPort:Qry the pot type fail!");
        return AT_ERROR;
    }

    /* ^SETPORT: */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s:",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* OLD PORT */
    for (i = 0; i< AT_SETPORT_PARA_MAX_LEN; i++)
    {
        for (j = 0; j < AT_SETPORT_DEV_MAP_LEN; j++)
        {
            if (stDynamicPidType.aucFirstPortStyle[i] == g_astSetPortParaMap[j].ucDrvPara)
            {
                /* ����1����������ʾ��ʽ: */
                if (ucCount > 0)
                {
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                    ",");
                }

                /* ���� */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                g_astSetPortParaMap[j].aucAtSetPara);

                ucCount++;
                break;
            }
        }
    }

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    ";");

    ucCount = 0;

    /* CUR PORT */
    for (i = 0; i< AT_SETPORT_PARA_MAX_LEN; i++)
    {
        for (j = 0; j < AT_SETPORT_DEV_LEN; j++)
        {
            if (stDynamicPidType.aucRewindPortStyle[i] == g_astSetPortParaMap[j].ucDrvPara)
            {
                /* ����1����������ʾ��ʽ: */
                if (ucCount > 0)
                {
                    /* �س����� */
                    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                    ",");
                }

                /* ���� */
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                "%s",
                                                g_astSetPortParaMap[j].aucAtSetPara);

                ucCount++;

                break;
            }
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

#if (FEATURE_ON == MBB_USB)
#define AT_SPEED_NAME_LEN              (16)

VOS_UINT32 At_QrySpeed(VOS_UINT8 ucIndex)
{
    VOS_UINT32          ret;
    VOS_UCHAR            usbspeed[AT_SPEED_NAME_LEN]={'\0'};
    ret = DRV_GET_USB_SPEED(usbspeed);
    printk(KERN_ERR"%s\n",usbspeed);
    if(ret)
    {
        return AT_ERROR;
    }
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "^USBSPEED: %s", usbspeed);
    return AT_OK;
}
#endif


TAF_UINT32 At_QryPcscInfo(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulPortState;

    /*PCSC �ڵĿ���״̬, 0 ��; 1 �ر�*/
    if (VOS_TRUE == AT_ExistSpecificPort(AT_DEV_PCSC))
    {
        ulPortState = VOS_TRUE;
    }
    else
    {
        ulPortState = VOS_FALSE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulPortState);
    return AT_OK;
}


VOS_UINT32 At_QryCellSearch(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ������Ϣ ID_AT_MTA_WRR_CELLSRH_QRY_REQ �� DRV AGENT ���� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_WRR_CELLSRH_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_WAS_MNTN_QRY_CELLSRH;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


/*****************************************************************************
 Prototype      : At_QryGetportmodePara
 Description    :
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   : AT_XXX  --- ATC������
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-07-13
    Author      : S62952
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryGetportmodePara (TAF_UINT8 ucIndex)
{
     /*��������ֱ�ӷ���ERROR*/
     return AT_ERROR;
}


VOS_UINT32 At_QryCvoicePara (VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /*��ȡ��ǰ�����豸ģʽ��0 �ֳ֣�1 �ֳ����᣻2 �������᣻3 ������4 ���� */
    if (VOS_OK == APP_VC_GetVoiceMode(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CVOICE_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }

}



VOS_UINT32 At_QryDdsetexPara(VOS_UINT8 ucIndex)
{
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    if (VOS_OK == APP_VC_GetVoicePort(gastAtClientTab[ucIndex].usClientId, 0))
    {
        /* ���õ�ǰ�������� */
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DDSETEX_READ;
        return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */
    }
    else
    {
        return AT_ERROR;
    }
}


TAF_UINT32 At_QryCmsrPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_SMS_CTX_STRU              *pstSmsCtx = VOS_NULL_PTR;

    pstSmsCtx = AT_GetModemSmsCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSmsCtx->ucParaCmsr);
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */
    return AT_OK;
}



TAF_UINT32 At_QryUssdModePara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, Begin */
    AT_MODEM_SS_CTX_STRU               *pstSsCtx = VOS_NULL_PTR;

    pstSsCtx = AT_GetModemSsCtxAddrFromClientId(ucIndex);

    /* 0��USSD��͸�����������������USSD�ַ�����룩1��USSD͸�������������岻����USSD�ַ�����룬ֻ��͸��)*/
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstSsCtx->usUssdTransMode);
    /* Modified by l60609 for DSDA Phase III, 2013-2-25, End */

    return AT_OK;
}


TAF_UINT32 At_QryAdcTempPara(TAF_UINT8 ucIndex)
{
    SPY_TEMP_PROTECT_NV_STRU stTempProtectNv;


    PS_MEM_SET(&stTempProtectNv, 0x00, sizeof(stTempProtectNv));


    /*��ȡ�ȱ�������ֵ��NV��*/
    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_USIM_TEMP_PROTECT_NEW,
                        (VOS_VOID*)&stTempProtectNv,
                        sizeof(SPY_TEMP_PROTECT_NV_STRU)))
    {
        AT_ERR_LOG("Spy_SetTempPara: NV_ReadEx en_NV_Item_USIM_TEMP_PROTECT Fail!");

        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR*)pgucAtSndCodeAddr,
                                                "^ADCTEMP: %d,%d,%d,%d",
                                                stTempProtectNv.ulIsEnable,
                                                stTempProtectNv.lCloseAdcThreshold,
                                                stTempProtectNv.lAlarmAdcThreshold,
                                                stTempProtectNv.lResumeAdcThreshold);

    return AT_OK;
}


TAF_UINT32 At_QryCommDebugPara(TAF_UINT8 ucIndex)
{
    TAF_AT_NVIM_COMMDEGBUG_CFG_STRU     stDebugFlag;


    stDebugFlag.ulCommDebugFlag = 0;

    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_COMMDEGBUG_CFG,
                        (VOS_VOID*)&(stDebugFlag.ulCommDebugFlag),
                        sizeof(TAF_AT_NVIM_COMMDEGBUG_CFG_STRU)))
    {
        AT_ERR_LOG("At_QryOamDebugPara: NV_ReadEx en_NV_Item_USIM_TEMP_PROTECT Fail!");

        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                "^COMM: 0x%X", stDebugFlag.ulCommDebugFlag);

    return AT_OK;
}


TAF_UINT32 At_QryDwinsPara(TAF_UINT8 ucIndex)
{
    WINS_CONFIG_STRU    stWins;
    VOS_UINT32          ulLength;

    ulLength = 0;


    PS_MEM_SET(&stWins, 0x00, sizeof(stWins));

    NV_GetLength(en_NV_Item_WINS_Config, &ulLength);
    if(NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WINS_Config, &stWins, ulLength))
    {
        return AT_ERROR;
    }

    if (0 == stWins.ucStatus)
    {
        /* ��en_NV_Item_WINSδ���ã���Ĭ��WINS����Ϊʹ�� */
        stWins.ucWins = WINS_CONFIG_ENABLE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stWins.ucWins);
    return AT_OK;
}


TAF_UINT32 At_QryYjcxPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;


    /* ����DRV_AGENT_YJCX_QRY_REQ��Ϣ��AT������ */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   DRV_AGENT_YJCX_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (VOS_OK == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_YJCX_QUERY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 At_QryCplsPara(VOS_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstNetCtx->enPrefPlmnType);
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */

    return AT_OK;

}


TAF_UINT32 At_QryCpolPara(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    TAF_MMA_CPOL_INFO_QUERY_REQ_STRU    stCpolInfo;

    /* ������� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*
    AT��MMA������Ӫ����Ϣ:
    ��Ϊ�˼���Ϣ���ƣ�����һ�λ�ȡ������Ӫ����Ϣ�����ﶨ��Ϊһ�λ�ȡ37����Ӫ����Ϣ
    ��һ��������Ϣ��������0��ʼҪ��������37����Ӫ����Ϣ
    */
    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    PS_MEM_SET(&stCpolInfo, 0, sizeof(stCpolInfo));

    stCpolInfo.enPrefPLMNType   = pstNetCtx->enPrefPlmnType;
    stCpolInfo.ulFromIndex      = 0;
    stCpolInfo.ulPlmnNum        = MAX_PLMN_NAME_LIST;

    /* ��MMA����Ϣ������Ӫ����Ϣ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   TAF_MSG_MMA_CPOL_INFO_QUERY_REQ,
                                   &stCpolInfo,
                                   sizeof(stCpolInfo),
                                   I0_WUEPS_PID_MMA);
    if (TAF_SUCCESS != ulRet)
    {
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CPOL_READ;

    return AT_WAIT_ASYNC_RETURN;

}


TAF_UINT32 AT_QryAuthdataPara(TAF_UINT8 ucIndex)
{
    if ( VOS_OK != TAF_PS_GetAuthDataInfo(WUEPS_PID_AT,
                                          gastAtClientTab[ucIndex].usClientId,
                                          0) )
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHDATA_READ;

    return AT_WAIT_ASYNC_RETURN;
}


#if (FEATURE_ON == FEATURE_IPV6)


VOS_UINT32 AT_QryIpv6CapPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucIpv6Capability;

    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV6_ONLY;
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY
                               + AT_IPV6_CAPABILITY_IPV6_ONLY
                               + AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP;
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY
                               + AT_IPV6_CAPABILITY_IPV6_ONLY
                               + AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP;
            break;

        default:
            ucIpv6Capability = AT_IPV6_CAPABILITY_IPV4_ONLY;
            break;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucIpv6Capability);
    return AT_OK;
}
#endif

/*****************************************************************************
 Prototype      : At_QryCrpnPara
 Description    : ^CRPN?
 Input          : ucIndex --- �û�����
 Output         :
 Return Value   :
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2009-09-01
    Author      : L47619
    Modification: Created function
*****************************************************************************/
TAF_UINT32 At_QryCrpnPara(TAF_UINT8 ucIndex)
{
    return AT_OK;
}


VOS_UINT32 AT_QryAlsPara( TAF_UINT8 ucIndex )
{
    VOS_UINT32                          ulRst;
    MN_CALL_APP_REQ_ENUM_UINT32         usMsg;

    usMsg                           = MN_CALL_APP_QRY_ALS_REQ;
    gastAtClientTab[ucIndex].opId   = At_GetOpId();

    /*����TAF_CS_ALS_LINE_NO_QRY��Ϣ��TAF����TAF���ص�ǰ����·�š�*/
    ulRst = MN_CALL_SendAppRequest(usMsg,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   VOS_NULL_PTR);
    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APP_QRY_ALS_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}


VOS_VOID At_CovertMsInternalRxDivParaToUserSet(
                    VOS_UINT16 usCurBandSwitch,
                    VOS_UINT32 *pulUserDivBandsLow,
                    VOS_UINT32 *pulUserDivBandsHigh
                    )
{
    *pulUserDivBandsLow      = 0;
    *pulUserDivBandsHigh     = 0;

    /*�û����õĽ��շּ���ʽ����:
        0x80000            GSM850
        0x300              GSM900
        0x80               DCS1800
        0x200000           PCS1900
        0x400000           WCDMA2100
        0x800000           WCDMA1900
        0x1000000          WCDMA1800
        0x2000000          WCDMA_AWS
        0x4000000          WCDMA850
        0x2000000000000    WCDMA900
        0x4000000000000    WCDMA1700
      ��MS֧�ֵĽ��շּ���ʽ����:
        2100M/ bit1  1900M/bit2  1800M/bit3  1700M/bit4  1600M/bit5
        1500M/bit6   900M/bit7   850M/bit8   800M/bit9   450M/bit10
      ��Ҫ���û����õĽ��շּ�ת����MS֧�ֵĸ�ʽ
    */
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_900))
    {
        *pulUserDivBandsHigh |= TAF_PH_BAND_WCDMA_VIII_900;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_IX_1700))
    {
        *pulUserDivBandsHigh |= TAF_PH_BAND_WCDMA_IX_1700;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_2100))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_I_IMT_2100;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_1900))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_II_PCS_1900;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_1800))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_III_1800;
    }
    if (0 != (usCurBandSwitch & AT_MS_SUPPORT_RX_DIV_850))
    {
        *pulUserDivBandsLow |= TAF_PH_BAND_WCDMA_V_850;
    }

    return;
}


VOS_UINT32 At_QryFrssiPara(
    VOS_UINT8                           ucIndex
)
{
    AT_HPA_RF_RX_RSSI_REQ_STRU          *pstMsg;
    VOS_UINT32                          ulLength;

#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFRSSIPara(ucIndex);
    }
#endif

#if(FEATURE_UE_MODE_TDS == FEATURE_ON)
    if(AT_RAT_MODE_TDSCDMA == g_stAtDevCmdCtrl.ucDeviceRatMode)
    {
        return atQryFRSSIPara(ucIndex);
    }

#endif

    /*���������ڷ�����ģʽ��ʹ��*/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /*�������������÷������ŵ���ʹ��*/
    if (VOS_FALSE == g_stAtDevCmdCtrl.bDspLoadFlag)
    {
        return AT_CHANNEL_NOT_SET;
    }

    /*��������Ҫ�ڴ򿪽��ջ���ʹ��*/
    if (AT_DSP_RF_SWITCH_OFF == g_stAtDevCmdCtrl.ucRxOnOff)
    {
        return AT_FRSSI_RX_NOT_OPEN;
    }

    /* GDSP LOAD������²�֧�ֽ��ջ��ͷ����ͬʱ�򿪣���Ҫ�ж����һ��ִ�е��Ǵ򿪽��ջ�����
    ���Ǵ򿪷��������������Ǵ򿪷������������ֱ�ӷ��س��������GDSP ���� */
    if ((AT_TXON_OPEN == g_stAtDevCmdCtrl.ucRxonOrTxon)
     && ((AT_RAT_MODE_GSM == g_stAtDevCmdCtrl.ucDeviceRatMode)
      || (AT_RAT_MODE_EDGE == g_stAtDevCmdCtrl.ucDeviceRatMode)))
    {
        return AT_FRSSI_OTHER_ERR;
    }

    /* ����AT_HPA_RF_RX_RSSI_REQ_STRU��Ϣ */
    ulLength = sizeof(AT_HPA_RF_RX_RSSI_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg   = (AT_HPA_RF_RX_RSSI_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_AT, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_QryFrssiPara: alloc msg fail!");
        return AT_FRSSI_OTHER_ERR;
    }

    if ((AT_RAT_MODE_GSM == g_stAtDevCmdCtrl.ucDeviceRatMode)
     || (AT_RAT_MODE_EDGE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        pstMsg->ulReceiverPid = AT_GetDestPid(ucIndex, I0_DSP_PID_GPHY);
        pstMsg->usMsgID       = ID_AT_GHPA_RF_RX_RSSI_REQ;
    }
    else
    {
        pstMsg->ulReceiverPid = DSP_PID_WPHY;
        pstMsg->usMsgID       = ID_AT_HPA_RF_RX_RSSI_REQ;
    }

    pstMsg->usMeasNum  = AT_DSP_RSSI_MEASURE_NUM;
    pstMsg->usInterval = AT_DSP_RSSI_MEASURE_INTERVAL;
    pstMsg->usRsv      = 0;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        AT_WARN_LOG("At_QryFrssiPara: Send msg fail!");
        return AT_FRSSI_OTHER_ERR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_QUERY_RSSI;
    g_stAtDevCmdCtrl.ucIndex               = ucIndex;

    return AT_WAIT_ASYNC_RETURN;    /* ������������״̬ */

}


VOS_UINT32 At_QryRxDiv(TAF_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ������ϢDRV_AGENT_HARDWARE_QRY��DRV AGENT��������Ϣ�޲����ṹ */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_RXDIV_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DRV_AGENT_RXDIV_QRY_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;

}


VOS_UINT32 At_QryCuus1Para(
    VOS_UINT8                           ucIndex
)
{
    VOS_UINT32                          ulRst;
    MN_CALL_APP_REQ_ENUM_UINT32         ucMsg;

    ucMsg = MN_CALL_APP_QRY_UUSINFO_REQ;

    ulRst = MN_CALL_SendAppRequest(ucMsg,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   VOS_NULL_PTR);
    if (MN_ERR_NO_ERROR == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APP_SET_UUSINFO_REQ;
        return AT_WAIT_ASYNC_RETURN;
    }
    return AT_ERROR;
}


VOS_UINT32 At_QryApHplmn( VOS_UINT8  ucIndex )
{
    /* ��MMA�����²�����ѯ��ϢTAF_PH_HOMEPLMN_VALUE_PARA */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   TAF_PH_HOMEPLMN_VALUE_PARA,
                                   TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HOMEPLMN_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 AT_QryAnQuery( VOS_UINT8 ucIndex )
{
    /* ��MMA������Ϣ����ѯ�²�������TAF_PH_ANQUERY_VALUE_PARA */
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   TAF_PH_ANQUERY_VALUE_PARA,
                                   TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ANQUERY_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


AT_CMD_ANTENNA_LEVEL_ENUM_UINT8 AT_CalculateAntennaLevel(
    VOS_INT16                           sRscp,
    VOS_INT16                           sEcio
)
{
    VOS_UINT16                          usRscp;
    VOS_UINT16                          usEcio;
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enRlstAntennaLevel;

/* RSCP and ECIO different Thresholds variables */
   VOS_INT32                            alRscpThreshold[AT_ANTEN_LEV_MAX_NUM] = {125, 108, 102, 96} ;
   VOS_INT32                            alEcioThreshold[AT_ANTEN_LEV_MAX_NUM] = {30, 16, 13, 10};

#if(FEATURE_ON == FEATURE_LTE)

    VOS_UINT8                          *pucSystemAppConfig;
    pucSystemAppConfig                  = AT_GetSystemAppConfigAddr();

    if ( SYSTEM_APP_WEBUI == *pucSystemAppConfig)
    {
        /* ȡ����ֵ */
        usRscp                    = (VOS_UINT16)-sRscp;
        usEcio                    = (VOS_UINT16)-sEcio;

        /* 3 level of Signal */
        if ( (usEcio <= g_stEcioCfg.ssValue[3])
          && (usRscp <= g_stRscpCfg.ssValue[3]))
        {
            enRlstAntennaLevel = AT_CMD_ANTENNA_LEVEL_4;
        }
        /* 2 level of Signal */
        else if (((usEcio <= g_stEcioCfg.ssValue[2]) && (usEcio > g_stEcioCfg.ssValue[3])
               && (usRscp <= g_stRscpCfg.ssValue[2]))
              || ((usRscp <= g_stRscpCfg.ssValue[2]) && (usRscp > g_stRscpCfg.ssValue[3])
               && (usEcio < g_stEcioCfg.ssValue[2])))
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_3;
        }
        /* 1 level of Signal */
        else if (((usEcio <= g_stEcioCfg.ssValue[1]) && (usEcio > g_stEcioCfg.ssValue[2])
               && (usRscp <= g_stRscpCfg.ssValue[1]))
              || ((usRscp <= g_stRscpCfg.ssValue[1]) && (usRscp > g_stRscpCfg.ssValue[2])
               && (usEcio < g_stEcioCfg.ssValue[1])))
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_2;
        }
        else
        {
            enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_1;
        }
        return enRlstAntennaLevel;
    }
#endif

    enRlstAntennaLevel        = 0;

    /* ȡ����ֵ */
    usRscp                    = (VOS_UINT16)-sRscp;
    usEcio                    = (VOS_UINT16)-sEcio;

    /* 3 level of Signal */
    if ( (usEcio <= alEcioThreshold[3])
      && (usRscp <= alRscpThreshold[3]))
    {
        enRlstAntennaLevel = AT_CMD_ANTENNA_LEVEL_4;
    }
    /* 2 level of Signal */
    else if (((usEcio <= alEcioThreshold[2]) && (usEcio > alEcioThreshold[3])
           && (usRscp <= alRscpThreshold[2]))
          || ((usRscp <= alRscpThreshold[2]) && (usRscp > alRscpThreshold[3])
           && (usEcio < alEcioThreshold[2])))
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_3;
    }
    /* 1 level of Signal */
    else if (((usEcio <= alEcioThreshold[1]) && (usEcio > alEcioThreshold[2])
           && (usRscp <= alRscpThreshold[1]))
          || ((usRscp <= alRscpThreshold[1]) && (usRscp > alRscpThreshold[2])
           && (usEcio < alEcioThreshold[1])))
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_2;
    }
    else
    {
        enRlstAntennaLevel  = AT_CMD_ANTENNA_LEVEL_1;
    }

    return enRlstAntennaLevel;

}

VOS_VOID AT_GetSmoothAntennaLevel(
    VOS_UINT8                           ucIndex,
    AT_CMD_ANTENNA_LEVEL_ENUM_UINT8     enLevel
)
{
    VOS_UINT8                               i;
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, Begin */
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromClientId(ucIndex);

    /* ����ʱ ��������  */
    if ( AT_CMD_ANTENNA_LEVEL_0 == enLevel )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        PS_MEM_SET( pstNetCtx->aenAntennaLevel, 0, sizeof(pstNetCtx->aenAntennaLevel) );
        return;
    }

    /* �������з���״̬  ��������  */
    if ( AT_CMD_ANTENNA_LEVEL_0 == pstNetCtx->enCalculateAntennaLevel )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        PS_MEM_SET( pstNetCtx->aenAntennaLevel, 0, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }

    /* ���ϴε��źŸ����Ƚ�, �仯�Ƚϴ�(����1��)���������� */
    if ( enLevel > (pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] + 1) )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        PS_MEM_SET( pstNetCtx->aenAntennaLevel, 0, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }
    else if (( enLevel + 1) < pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] )
    {
        pstNetCtx->enCalculateAntennaLevel = enLevel;

        PS_MEM_SET( pstNetCtx->aenAntennaLevel, 0, sizeof(pstNetCtx->aenAntennaLevel) );
        pstNetCtx->aenAntennaLevel[AT_ANTENNA_LEVEL_MAX_NUM-1] = enLevel;
        return;
    }
    else
    {
      /* Do nothing... */
    }


    /* �Ƚ��ȳ������3�εĲ�ѯ��� */
    for ( i=0; i<AT_ANTENNA_LEVEL_MAX_NUM-1; i++ )
    {
         pstNetCtx->aenAntennaLevel[i] = pstNetCtx->aenAntennaLevel[i+1];
    }
    pstNetCtx->aenAntennaLevel[i] = enLevel;


    /* ���������򲻸��£��Դﵽƽ����Ч�� */
    for ( i=0; i<AT_ANTENNA_LEVEL_MAX_NUM; i++ )
    {
        if ( pstNetCtx->enCalculateAntennaLevel == pstNetCtx->aenAntennaLevel[i] )
        {
            return;
        }
    }

    /* �źŸ����ȶ��� AT_ANTENNA_LEVEL_MAX_NUM ��ʱ�������� */
    pstNetCtx->enCalculateAntennaLevel = enLevel;
    /* Modified by l60609 for DSDA Phase III, 2013-2-22, End */
}

TAF_UINT32 At_QryGlastErrPara( TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    /* ���������ϱ�����̨*/
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                       gulErrType);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


TAF_UINT32  At_QryTModePara(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    /* ��ѯ��ǰTMODE��ִ��״̬ */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                       1);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32  At_QryFpaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /*��ǰ��Ϊ������ģʽ*/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* ��ѯ��ǰ�����PA�ȼ������� */
    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       g_stAtDevCmdCtrl.ucPaLevel);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32  At_QryFlnaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /* ��� LTE ģ�Ľӿڷ�֧ */
#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFLNAPara(ucIndex);
    }
#endif

    /*��ǰ��Ϊ������ģʽ*/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* ��ѯ��ǰ�����PA�ȼ������� */
    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       g_stAtDevCmdCtrl.ucLnaLevel);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


TAF_UINT32  At_QryFChanPara(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFCHANPara(ucIndex);
    }
#endif

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* ��ѯ��ǰFCHAN������ */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                  (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d,%d,%d,%d",
                                   g_stAtDevCmdCtrl.ucDeviceRatMode,
                                   g_stAtDevCmdCtrl.ucDeviceAtBand,
                                   g_stAtDevCmdCtrl.stDspBandArfcn.usUlArfcn,
                                   g_stAtDevCmdCtrl.stDspBandArfcn.usDlArfcn);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32  At_QryFRxonPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /* ���LTE ģ�Ľӿڷ�֧ */
#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFRXONPara(ucIndex);
    }
#endif

    /*��ǰ��Ϊ������ģʽ*/
    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* ��ѯ��ǰ���ջ�����״̬ */
    usLength =  (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       g_stAtDevCmdCtrl.ucRxOnOff);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


TAF_UINT32  At_QryFTxonPara(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    /*��� LTE ģ�Ľӿڷ�֧ */
#if(FEATURE_LTE == FEATURE_ON)
    if ((AT_RAT_MODE_FDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode)
      ||(AT_RAT_MODE_TDD_LTE == g_stAtDevCmdCtrl.ucDeviceRatMode))
    {
        return atQryFTXONPara(ucIndex);
    }
#endif

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }
    /* ��ѯ��ǰDAC������ */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                  (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                   g_stAtDevCmdCtrl.ucTxOnOff);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

TAF_UINT32  AT_QryFDac(TAF_UINT8 ucIndex )
{
    TAF_UINT16                 usLength;

    if (AT_TMODE_FTM != g_stAtDevCmdCtrl.ucCurrentTMode)
    {
        return AT_DEVICE_MODE_ERROR;
    }

    /* ��ѯ��ǰDAC������ */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                       (TAF_CHAR*)pgucAtSndCodeAddr, "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
                                  (TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                   g_stAtDevCmdCtrl.usFDAC);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



TAF_UINT32  At_QryPlatForm(TAF_UINT8 ucIndex )
{
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
    VOS_UINT32                          ulRet;
    NAS_NVIM_PLATFORM_STRU              stPlatform;



    stPlatform.usPlatform = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_SubPlatFormInfo, &stPlatform.usPlatform, sizeof(stPlatform.usPlatform));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d,%d",g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    1,
                                                    stPlatform.usPlatform);

    return AT_OK;

}

VOS_UINT32  At_QryDataLock(VOS_UINT8 ucIndex )
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d", g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_bAtDataLocked);

    return AT_OK;

}

VOS_UINT32  At_QrySD(VOS_UINT8 ucIndex )
{

    VOS_UINT32                          ulCurrentOprtStaus;

#if (FEATURE_ON == MBB_COMMON)
    /* SD�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_SD_SUPPORT())
    {
        return AT_ERROR;
    }
#endif

    ulCurrentOprtStaus = DRV_SDMMC_GET_OPRT_STATUS();

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d", g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulCurrentOprtStaus);
    return AT_OK;
}

VOS_UINT32  At_DelCtlAndBlankCharWithEndPadding(
    VOS_UINT8                               *pucData,
    VOS_UINT16                              *pusCmdLen
)
{

    VOS_UINT16                              usOrigLen;

    usOrigLen = *pusCmdLen;

    /* ɨ����Ʒ� */
    if(AT_FAILURE == At_ScanCtlChar(pucData, pusCmdLen))
    {
        return AT_FAILURE;
    }

    /* ɨ����������Ŀո�� */
    if(AT_FAILURE == At_ScanBlankChar(pucData, pusCmdLen))
    {
        return AT_FAILURE;
    }

    PS_MEM_SET(pucData + (*pusCmdLen),0x00, usOrigLen - (*pusCmdLen));

    return AT_SUCCESS;

}

#if (FEATURE_ON == MBB_COMMON)

void version_info_build(VOS_UINT8 ucIndex, VOS_UINT8  *pucKey, VOS_UINT8  *pucValue)
{
    gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                          "%s:%s:%s%s",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          pucKey,
                                          pucValue,
                                          gaucAtCrLf);
}


void version_info_fill(VOS_UINT8  *pucDes, VOS_UINT8  *pucSrc)
{
    (void)memset(pucDes, 0, TAF_MAX_VERSION_VALUE_LEN);
    (void)strncpy(pucDes, pucSrc, strlen(pucSrc));
}
#endif


VOS_UINT32  At_QryVersion(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
    VOS_UINT16                          ulLen = 0;
    TAF_NVIM_CS_VER_STRU                stCsver = {0};
    VOS_UINT8                           *pInfoTemp = NULL;
    VOS_UINT8                           tempInfoArray[TAF_MAX_VERSION_VALUE_LEN] = {0};
    VOS_UINT8                           iniVersion[AT_VERSION_INI_LEN] = {0};
    
    gstAtSendData.usBufLen = 0;
    
    /* 1. ��ȡ����ʱ�� */
    pInfoTemp = NULL;
    pInfoTemp = (char *)DRV_GET_VERSION_TIME();
    if(NULL == pInfoTemp)
    {
        printk("%s: build time read error.", __func__);
        return AT_ERROR;
    }

    version_info_fill(tempInfoArray, pInfoTemp);
    /*�汾����ʱ���ʽת������ʱ��������������ո�ĺ�һ���ո���0�滻 */
    (void)At_ZeroReplaceBlankInString(tempInfoArray, VOS_StrLen(tempInfoArray));
    version_info_build(ucIndex, "BDT", tempInfoArray);
	
    /* 2. ��ȡ����ⲿ�汾�� */
    pInfoTemp = NULL;
    pInfoTemp = bsp_version_get_firmware();
    if(NULL == pInfoTemp)
    {
        printk("%s: software version read error.", __func__);
        return AT_ERROR;
    }
    version_info_fill(tempInfoArray, pInfoTemp);
    version_info_build(ucIndex, "EXTS", tempInfoArray);
    
    /* 3. ��ȡ����ڲ��汾�� */
    if (VOS_FALSE == g_bAtDataLocked)
    {
        pInfoTemp = NULL;
        pInfoTemp = bsp_version_get_firmware();
        if(NULL == pInfoTemp)
        {
            printk("%s: software version read error.", __func__);
            return AT_ERROR;
        }
        version_info_fill(tempInfoArray, pInfoTemp);
        version_info_build(ucIndex, "INTS", tempInfoArray);
    }
    else
    {
        (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
        version_info_build(ucIndex, "INTS", tempInfoArray);
    }

    /* 4. ��OEM������ȡ�ⲿWEBUI�汾�� */
    (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
    ulLen = TAF_MAX_VERSION_VALUE_LEN;
    if (VOS_OK != DRV_GET_WEBUI_VERSION(tempInfoArray, TAF_MAX_VERSION_VALUE_LEN))
    {
        printk("%s: outer iso ver read error.", __func__);
        return AT_ERROR;
    }
    (void)At_DelCtlAndBlankCharWithEndPadding(tempInfoArray, &ulLen);
    version_info_build(ucIndex, "EXTD", tempInfoArray);
    
    /* 5. ��OEM������ȡ�ڲ�WEBUI�汾�� */
    if (VOS_FALSE == g_bAtDataLocked)
    {
        (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
        ulLen = TAF_MAX_VERSION_VALUE_LEN;
        if (VOS_OK != DRV_GET_WEBUI_VERSION(tempInfoArray, TAF_MAX_VERSION_VALUE_LEN))
        {
            printk("%s: outer iso ver read error.", __func__);
            return AT_ERROR;
        }
        (void)At_DelCtlAndBlankCharWithEndPadding(tempInfoArray, &ulLen);
        version_info_build(ucIndex, "INTD", tempInfoArray);
    }
    else
    {
        (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
        version_info_build(ucIndex, "INTD", tempInfoArray);
    }
    
    /* 6. ��ȡ�ⲿӲ���汾��  */
    (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
    if (VOS_OK != DRV_GET_FULL_HW_VER((char *)tempInfoArray, TAF_MAX_VERSION_VALUE_LEN))
    {
        printk("%s: outer hardware version read error.", __func__);
        return AT_ERROR;
    }
    version_info_build(ucIndex, "EXTH", tempInfoArray);
  
    /* 7. ��ȡ�ڲ�Ӳ���汾��  */
    if (VOS_FALSE == g_bAtDataLocked)
    {
        (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
        if (VOS_OK != DRV_GET_FULL_HW_VER((char *)(tempInfoArray), TAF_MAX_VERSION_VALUE_LEN))
        {
            printk("%s: inner hardware version read error.", __func__);
            return AT_ERROR;
        }
        version_info_build(ucIndex, "INTH", tempInfoArray);
    }
    else
    {
        (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
        version_info_build(ucIndex, "INTH", tempInfoArray);
    }

    /* 8. ��ȡ�ⲿ��Ʒ�� */
    (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
    if (VOS_OK != BSP_GetProductName(tempInfoArray, TAF_MAX_VERSION_VALUE_LEN))
    {
        printk("%s: outer product name read error.", __func__);
        return AT_ERROR;
    }
    version_info_build(ucIndex, "EXTU", tempInfoArray);

    /* 9. ��ȡ�ڲ���Ʒ�� */
    if (VOS_FALSE == g_bAtDataLocked)
    {
        (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
        if (VOS_OK != DRV_GET_PRODUCTID_INTER_VER(tempInfoArray, TAF_MAX_VERSION_VALUE_LEN))
        {
            printk("%s: inner product name read error.", __func__);
            return AT_ERROR;
        }
        version_info_build(ucIndex, "INTU", tempInfoArray);
    }
    else
    {
        (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
        version_info_build(ucIndex, "INTU", tempInfoArray);
    }

    /* 10. ���������ð汾�� */
    (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Csver, &(stCsver.usCsver), sizeof(stCsver.usCsver)))
    {
        printk("%s: en_NV_Item_Csver read error.", __func__);
        return AT_ERROR;
    }
    (void)snprintf(tempInfoArray, TAF_MAX_VERSION_VALUE_LEN, "%d", stCsver.usCsver);
    version_info_build(ucIndex, "CFG", tempInfoArray);
    
    /* 11. PRL�汾�� */
    (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
    version_info_build(ucIndex, "PRL", tempInfoArray);
    
    /* 12. OEM�汾��Ϣ */
    (void)memset(tempInfoArray, 0, TAF_MAX_VERSION_VALUE_LEN);
    version_info_build(ucIndex, "OEM", tempInfoArray);
    
    /* 13. INI�����ļ��汾�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_PRI_VERSION, iniVersion, sizeof(iniVersion)))
    {
        printk("%s: en_NV_Item_PRI_VERSION read error.", __func__);
        return AT_ERROR;
    }
    version_info_fill(tempInfoArray, iniVersion);
    version_info_build(ucIndex, "INI", tempInfoArray);
    
    if(0 < gstAtSendData.usBufLen)
    {
        gstAtSendData.usBufLen = gstAtSendData.usBufLen - (VOS_UINT16)VOS_StrLen((VOS_CHAR *)gaucAtCrLf);
    }
    
    return AT_OK;
#else
    if(TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                            gastAtClientTab[ucIndex].opId,
                                            DRV_AGENT_VERSION_QRY_REQ,
                                            VOS_NULL_PTR,
                                            0,
                                            I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_VERSION_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
#endif
}



VOS_UINT32  At_QryBsn(VOS_UINT8 ucIndex )
{
    /* ���кų���Ϊ16,�ټ����һλ�洢������ */
    VOS_UINT8                            aucBsnSerialNum[17];
    VOS_UINT16                           usLength;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /* ������� */
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    usLength = sizeof(aucBsnSerialNum);

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_SetSDomainPara: Get modem id fail.");
        return AT_ERROR;
    }

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_ManufactureInfo, aucBsnSerialNum, usLength))
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */
    {
        AT_WARN_LOG("At_QryBsn:WARNING:NVIM Read en_NV_Item_Serial_Num falied!");
        return AT_ERROR;
    }
    else
    {
        aucBsnSerialNum[16]=0;/*�����һλ���Խ�������'\0'*/
        usLength = 0;
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s:",g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength,"%s",aucBsnSerialNum);
    }
    gstAtSendData.usBufLen = usLength;
    return AT_OK;

}

VOS_UINT32  At_QryCsVer(VOS_UINT8 ucIndex )
{
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
    VOS_UINT32                          ulRet;
    TAF_NVIM_CS_VER_STRU                stCsver;


    stCsver.usCsver = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_Csver, &stCsver, sizeof(VOS_UINT16));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

   gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   "%s:%d",
                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                   stCsver.usCsver);

    return AT_OK;
}

VOS_UINT32  At_QryQosPara(VOS_UINT8 ucIndex )
{
    AT_TRAFFIC_CLASS_CUSTOMIZE_STRU     stATTrafficClass;
    VOS_UINT16                          usReadLength;
    VOS_UINT16                          usLength;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;

    enModemId = MODEM_ID_0;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */


    stATTrafficClass.ucStatus       = NV_ITEM_DEACTIVE;
    stATTrafficClass.ucTrafficClass = AT_QOS_TRAFFIC_CLASS_SUBSCRIBE;


    /*����״̬���ͼ��*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /*��ȡNV�е�ֵ��stATTrafficClass�ṹ�����*/
    usReadLength = sizeof(stATTrafficClass);

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_QryQosPara: Get modem id fail.");
        return AT_ERROR;
    }

    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_TRAFFIC_CLASS_Type, &stATTrafficClass, usReadLength))
    {
        AT_WARN_LOG("At_QryQosPara:WARNING:NVIM Read en_NV_Item_TRAFFIC_CLASS_Type failed!");
        return AT_DEVICE_OTHER_ERROR;
    }
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /*NV���ڷǼ���̬,ֱ���ϱ�Ĭ��ֵ:AT_QOS_TRAFFIC_CLASS_INTERACTIVE*/
    if (NV_ITEM_DEACTIVE == stATTrafficClass.ucStatus)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          AT_QOS_TRAFFIC_CLASS_SUBSCRIBE);


    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                         (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                         stATTrafficClass.ucTrafficClass);
    }
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

VOS_UINT32   At_QrySDomainPara(VOS_UINT8 ucIndex)
{
    NAS_NVIM_MS_CLASS_STRU              stMsClass;
    VOS_UINT16                          usLength;
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLength;

    enModemId = MODEM_ID_0;
    ulLength  = 0;

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    PS_MEM_SET(&stMsClass, 0x00, sizeof(NAS_NVIM_MS_CLASS_STRU));
    stMsClass.ucMsClass = TAF_PH_MS_CLASS_A;

    /*����״̬���ͼ��*/
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /*��ȡNV*/
    usLength = sizeof(TAF_PH_MS_CLASS_TYPE);

    /* Modified by l60609 for DSDA Phase III, 2013-3-4, Begin */
    ulRet = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("At_QrySDomainPara: Get modem id fail.");
        return AT_ERROR;
    }
    NV_GetLength(en_NV_Item_MMA_MsClass, &ulLength);
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_MMA_MsClass, &stMsClass, ulLength))
    {
        AT_WARN_LOG("At_QrySDomainPara:WARNING:NVIM Read en_NV_Item_MMA_MsClass failed!");
        return AT_DEVICE_OTHER_ERROR;
    }
    /* Modified by l60609 for DSDA Phase III, 2013-3-4, End */

    /*�ϱ���NV�ж�ȡ��MsClassֵ*/
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName, stMsClass.ucMsClass);
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

VOS_UINT32   At_QryGPIOPL(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              DRV_AGENT_GPIOPL_QRY_REQ,
                                              VOS_NULL_PTR,
                                              0,
                                              I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_GPIOPL_QRY;             /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                            /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryMDatePara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usLength;
    TAF_AT_NVIM_MANUFACTURE_DATE_STRU   stManufactrueDate;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_MANUFACTURE_DATE,
                    &stManufactrueDate,
                    AT_MDATE_STRING_LENGTH);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryMDatePara: fail to read NVIM . ");
        return AT_ERROR;
    }
    
#if (FEATURE_ON == MBB_COMMON)
    stManufactrueDate.aucMDate[AT_MDATE_STRING_LENGTH - 1] = '\0';
    
    /*ƴ����Ӧ�ַ���: �����֣�����������Ϣ*/
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s:%s%s%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       gaucAtQuotation,stManufactrueDate.aucMDate,gaucAtQuotation);
    gstAtSendData.usBufLen = usLength;
#else
    /*ƴ����Ӧ�ַ���: �����֣�����������Ϣ*/
    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       "%s:",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    stManufactrueDate.aucMDate[AT_MDATE_STRING_LENGTH - 1] = '\0';
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       stManufactrueDate.aucMDate);

    gstAtSendData.usBufLen = usLength;
#endif

    return AT_OK;
}


VOS_UINT32 AT_QryFacInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           *pucFacInfo = TAF_NULL_PTR;
    VOS_UINT16                          usLength;

    /* ��ȡNV���Ѿ��洢��������Ϣ */
    pucFacInfo = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_AT, AT_FACINFO_STRING_LENGTH);
    if (VOS_NULL_PTR == pucFacInfo)
    {
        AT_WARN_LOG("AT_QryFacInfoPara: fail to alloc memory.");
        return AT_ERROR;
    }

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_FACTORY_INFO,
                    pucFacInfo,
                    AT_FACINFO_STRING_LENGTH);
    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryFacInfoPara: fail to read en_NV_Item_AT_FACTORY_INFO . ");
        PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
        return AT_ERROR;
    }

    /* �ݴ���ǿ�Ƹ�NV��INFO�ֶμӽ�����*/
    *(pucFacInfo + (AT_FACINFO_STRING_LENGTH - 1))     = '\0';
    *(pucFacInfo + AT_FACINFO_INFO1_LENGTH)            = '\0';

    /* ����˫���� */
    /* ƴ����Ӧ�ַ���: �����֣���һ��������Ϣ */
    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                    #if (FEATURE_ON == MBB_COMMON)
                                       "%s:0,%s%s%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       gaucAtQuotation,pucFacInfo,gaucAtQuotation);
                                    #else
                                       "%s:0,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       pucFacInfo);
                                    #endif

    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                       "%s",
                                       gaucAtCrLf);

    /* ƴ����Ӧ�ַ���: �����֣��ڶ���������Ϣ */
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    #if (FEATURE_ON == MBB_COMMON)
                                       "%s:1,%s%s%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       gaucAtQuotation,((pucFacInfo + AT_FACINFO_INFO1_LENGTH) + 1),gaucAtQuotation);
                                    #else
                                       "%s:1,%s",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                       ((pucFacInfo + AT_FACINFO_INFO1_LENGTH) + 1));
                                    #endif
    
    gstAtSendData.usBufLen = usLength;

    PS_MEM_FREE(WUEPS_PID_AT, pucFacInfo);
    return AT_OK;
}


VOS_UINT32  At_ReadDpaCatFromNV(VOS_UINT8 *pucDpaRate)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;
    AT_DPACAT_PARA_STRU                 astDhpaCategory[AT_DPACAT_CATEGORY_TYPE_BUTT] = {
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_6,  PS_FALSE, 0, PS_FALSE},                                                           /* ֧�����ʵȼ�3.6M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_8,  PS_FALSE, 0, PS_FALSE},                                                           /* ֧�����ʵȼ�7.2M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_11, PS_FALSE, 0, PS_FALSE},                                                           /* ֧�����ʵȼ�1.8M  */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_10, PS_FALSE, 0, PS_FALSE},                                                          /*  ֧�����ʵȼ�14.4M */
                {PS_TRUE,   AT_HSDSCH_PHY_CATEGORY_10, PS_TRUE,  AT_HSDSCH_PHY_CATEGORY_14, PS_FALSE}};           /*  ֧�����ʵȼ�21M */
    VOS_UINT8                           ucLoop;


    PS_MEM_SET(&stUECapa, 0x00, sizeof(stUECapa));


    /* ���������ָ����*/
    if ( VOS_NULL_PTR == pucDpaRate )
    {
        AT_WARN_LOG("At_ReadDpaCatFromNV: null PTR.");
        return VOS_ERR;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New, &stUECapa,
                        sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("At_ReadDpaCatFromNV():en_NV_Item_WAS_RadioAccess_Capa NV Read Fail!");
        return VOS_ERR;
    }

    for (ucLoop = 0; ucLoop < AT_DPACAT_CATEGORY_TYPE_BUTT; ucLoop++)
    {
        if ((stUECapa.enHSDSCHSupport        == astDhpaCategory[ucLoop].enHSDSCHSupport)
         && (stUECapa.ucHSDSCHPhyCategory    == astDhpaCategory[ucLoop].ucHSDSCHPhyCategory)
         && (stUECapa.enMacEhsSupport        == astDhpaCategory[ucLoop].enMacEhsSupport)
         && (stUECapa.ucHSDSCHPhyCategoryExt == astDhpaCategory[ucLoop].ucHSDSCHPhyCategoryExt)
         && (stUECapa.enMultiCellSupport     == astDhpaCategory[ucLoop].enMultiCellSupport))
        {
            *pucDpaRate = ucLoop;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}



VOS_UINT32   At_QryDpaCat(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucDpaRate;
    VOS_UINT32                          ulWasResult;
    VOS_UINT16                          usLength;

    /* ������� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ���ö�NV�ӿں���: At_ReadDpaCatFromNV,���ز������ */
    ulWasResult = At_ReadDpaCatFromNV(&ucDpaRate);
    if (VOS_OK == ulWasResult)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                           (VOS_UINT32)ucDpaRate);
        gstAtSendData.usBufLen = usLength;
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("At_QryDpaCat:WARNING:WAS_MNTN_QueryDpaCat failed!");
        return AT_ERROR;
    }
}

VOS_UINT32 AT_ReadRrcVerFromNV(VOS_UINT8 *pucRrcVer)
{
    AT_NVIM_UE_CAPA_STRU                stUECapa;


    PS_MEM_SET(&stUECapa, 0x00, sizeof(stUECapa));


    /* ��������ǿ��Լ�� */
    if (VOS_NULL_PTR == pucRrcVer)
    {
        AT_WARN_LOG("AT_ReadRrcVerFromNV: null PTR.");
        return VOS_ERR;
    }

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WAS_RadioAccess_Capa_New,
                         &stUECapa,
                         sizeof(AT_NVIM_UE_CAPA_STRU)))
    {
        AT_WARN_LOG("AT_ReadRrcVerFromNV: NV_ReadEx en_NV_Item_WAS_RadioAccess_Capa_New fail!");
        return VOS_ERR;
    }

    /* NVδʹ�� */
    if (VOS_FALSE == stUECapa.ulHspaStatus)
    {
        *pucRrcVer = AT_RRC_VERSION_DPA_AND_UPA;
        return VOS_OK;
    }

    /* NVʹ�� */
    /* HSPA+ */
    if ((stUECapa.enAsRelIndicator >= AT_PTL_VER_ENUM_R7)
     && (VOS_TRUE == stUECapa.enEDCHSupport)
     && (VOS_TRUE == stUECapa.enHSDSCHSupport))
    {
        *pucRrcVer = AT_RRC_VERSION_HSPA_PLUNS;
    }
    /* DPA/UPA */
    else if((VOS_TRUE == stUECapa.enEDCHSupport)
         && (VOS_TRUE == stUECapa.enHSDSCHSupport))
    {
        *pucRrcVer = AT_RRC_VERSION_DPA_AND_UPA;
    }
    /* DPA */
    else if(VOS_TRUE == stUECapa.enHSDSCHSupport)
    {
        *pucRrcVer = AT_RRC_VERSION_DPA;
    }
    /* WCDMA */
    else
    {
        *pucRrcVer = AT_RRC_VERSION_WCDMA;
    }


    return VOS_OK;
}



VOS_UINT32   AT_QryHspaSpt(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucRRCVer;
    VOS_UINT32                          ulWasResult;
    VOS_UINT16                          usLength;

    /* ������� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DPAUPA_ERROR;
    }

    ulWasResult = AT_ReadRrcVerFromNV(&ucRRCVer);

    if (VOS_OK == ulWasResult)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR *)pgucAtSndCodeAddr, "%s:",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (TAF_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr + usLength, "%d",
                                           (VOS_UINT32)ucRRCVer);
        gstAtSendData.usBufLen = usLength;
        return  AT_OK;
    }
    else
    {
        AT_WARN_LOG("AT_QryHspaSpt:WARNING:WAS_MNTN_QueryHspaSpt failed!");
        return AT_DPAUPA_ERROR;
    }
}


VOS_UINT32 At_QryCallSrvPara(VOS_UINT8 ucIndex)
{
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU              stCustSrv;
    VOS_UINT16                          usLength;


    stCustSrv.ulStatus           = NV_ITEM_DEACTIVE;
    stCustSrv.ulCustomizeService = 0;


    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeService, &stCustSrv, sizeof(stCustSrv)))
    {
        AT_WARN_LOG("At_QryCallSrvPara():en_NV_Item_CustomizeService NV Read Fail!");
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ���NV��δ������ص���Ĭ��ֵFALSE */
    if (NV_ITEM_DEACTIVE == stCustSrv.ulStatus)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          VOS_FALSE);
    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          stCustSrv.ulCustomizeService);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32 At_ReadCustomizeServiceNV(
    NAS_NVIM_CUSTOMIZE_SERVICE_STRU              *pstCustSrv,
    VOS_UINT16                          *pusValueInfo
)
{
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeService, pstCustSrv,
                         sizeof(NAS_NVIM_CUSTOMIZE_SERVICE_STRU)))
    {
        AT_WARN_LOG("At_ReadCustomizeServiceNV():en_NV_Item_CustomizeService NV Read Fail!");
        return VOS_ERR;
    }

    if (AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED == *pusValueInfo)
    {
        return VOS_OK;
    }

    /*�ж�NV��������Ƿ�ΪĬ��ֵ*/
    if ((pstCustSrv->ulStatus != NV_ITEM_DEACTIVE)
     || (pstCustSrv->ulCustomizeService != VOS_FALSE))
    {
        *pusValueInfo = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
    }

    return VOS_OK;

}


VOS_UINT32 At_ReadGprsActiveTimerLenNV(
    VOS_UINT32                          *pulGprsActiveTimerLen,
    VOS_UINT16                          *pusValueInfo
)
{
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_GPRS_ActiveTimerLength,
                          pulGprsActiveTimerLen, sizeof(VOS_UINT32)))
    {
        AT_WARN_LOG("At_ReadGprsActiveTimerLenNV():en_NV_Item_GPRS_ActiveTimerLength NV Read Fail!");
        return VOS_ERR;
    }

    if (AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED == *pusValueInfo)
    {
        return VOS_OK;
    }

    /*�ж�NV��������Ƿ�ΪĬ��ֵ*/
    if (*pulGprsActiveTimerLen != AT_GPRS_ACT_TIMER_LEN_DEFAULT_VAL)
    {
        *pusValueInfo = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
    }

    return VOS_OK;

}


VOS_UINT32 At_QryCsdfltPara(VOS_UINT8 ucIndex)
{

    /* Added by f62575 for B050 Project, 2012-2-3, Begin   */
    /* ����Ϣ��C�˻�ȡSIMLOCK ״̬��Ϣ */
    if(TAF_SUCCESS != Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                    0,
                                    TAF_PH_SIMLOCK_VALUE_PARA,
                                    TAF_NULL_PTR))
    {
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CSDFLT_READ;

    return AT_WAIT_ASYNC_RETURN;
    /* Added by f62575 for B050 Project, 2012-2-3, end   */
}


VOS_UINT32 AT_JudgeU8ArrayZero(
    VOS_UINT8                           aucValue[],
    VOS_UINT32                          ulLength
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < ulLength; ulLoop++)
    {
        if (0 != aucValue[ulLoop])
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/* Modify by z60575 for multi_ssid, 2012-9-5 begin */

VOS_UINT32 AT_GetWifiNvValue(VOS_UINT16 *pusCsdValue)
{
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiKey;
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulLoop;

    /* ��֧��WIFI�����WIFI��NV���ע��ֱ�ӷ���δ�޸� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT())
    {
        *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE;
        return VOS_OK;
    }

    PS_MEM_SET(&stWifiKey, 0, sizeof(stWifiKey));
    PS_MEM_SET(&stWifiSsid, 0, sizeof(stWifiSsid));

    /* �ж�en_NV_Item_WIFI_KEY�Ƿ�ΪĬ��ֵ����ע�����ֶ��Ƿ�ȫ0:
       aucWifiWpapsk aucWifiWepKey1 aucWifiWepKey2 aucWifiWepKey3 aucWifiWepKey4 */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiKey, sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("AT_GetWifiNvValue:READ NV ERROR");
        return VOS_ERR;
    }

    /* �ж�en_NV_Item_WIFI_STATUS_SSID�Ƿ�ΪĬ��ֵ����ע�����ֶ��Ƿ�ȫ0:
        aucWifiSsid
    */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID, &stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("AT_GetWifiNvValue:READ NV ERROR");
        return VOS_ERR;
    }

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWpapsk[ulLoop], sizeof(stWifiKey.aucWifiWpapsk[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey1[ulLoop], sizeof(stWifiKey.aucWifiWepKey1[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey2[ulLoop], sizeof(stWifiKey.aucWifiWepKey2[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey3[ulLoop], sizeof(stWifiKey.aucWifiWepKey3[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiKey.aucWifiWepKey4[ulLoop], sizeof(stWifiKey.aucWifiWepKey4[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }

        ulRet = AT_JudgeU8ArrayZero(stWifiSsid.aucWifiSsid[ulLoop], sizeof(stWifiSsid.aucWifiSsid[ulLoop]));
        if (VOS_OK != ulRet)
        {
            *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
            return VOS_OK;
        }
    }

    *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE;
    return VOS_OK;

}
/* Modify by z60575 for multi_ssid, 2012-9-5 end */


VOS_UINT32 AT_GetCsdValue(
    VOS_BOOL                            bSimlockEnableFlg,
    VOS_UINT16                         *pusCsdValue)
{
    /* Modified by f62575 for B050 Project, 2012-2-3, Begin   */
    VOS_UINT32                          ulRet;
    /* Modified by f62575 for B050 Project, 2012-2-3, End     */

    /*�ж�SIM LOCK Status������������Ƿ�ΪĬ��ֵDISABLE */
    /*��ȡSIM Lock Status�������ֵ������Ƿ�ΪĬ��ֵ*/
    if (VOS_FALSE != bSimlockEnableFlg)
    {
        *pusCsdValue = AT_CUSTOMIZE_ITEM_DEFAULT_VAL_CHANGED;
        return VOS_OK;
    }

    /* �ж�WIFI��ص�NV���Ƿ�ΪĬ��ֵ */
    ulRet = AT_GetWifiNvValue(pusCsdValue);

    return ulRet;
}

/* Added by f62575 for B050 Project, 2012-2-3, Begin   */

VOS_UINT32 AT_OutputCsdfltDefault(
    VOS_UINT8                           ucIndex,
    VOS_BOOL                            bSimlockEnableFlg
)
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulCsdfltFlg;
    VOS_UINT16                          usCsdfltValue;
    VOS_UINT32                          ulRslt;

    ulCsdfltFlg = VOS_TRUE;

    ulRslt = AT_GetCsdValue(bSimlockEnableFlg, &usCsdfltValue);

    if (VOS_OK != ulRslt)
    {
        return AT_ERROR;
    }

    /* ��ʾ����ֵ��Ϣ��0:��ʾ�������е�ֵΪ�����Զ����Ĭ��ֵ;
                       1:��ʾ�������е�ֵΪ�ǵ����Զ����Ĭ��ֵ */
    if (AT_CUSTOMIZE_ITEM_DEFAULT_VAL_UNCHANGE == usCsdfltValue)
    {
        ulCsdfltFlg = VOS_FALSE;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      ulCsdfltFlg);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}
/* Added by f62575 for B050 Project, 2012-2-3, End   */


VOS_UINT32  At_SimlockPlmnNumToAscii(
    const VOS_UINT8                     *pucPlmnRange,
    VOS_UINT8                           ucPlmnRangeLen,
    VOS_UINT8                            *pucAsciiStr
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;

    if ((VOS_NULL_PTR == pucPlmnRange)
     || (VOS_NULL_PTR == pucAsciiStr))
    {
        AT_WARN_LOG("At_SimlockPlmnNumToAscii: Parameter of the function is null.");
        return AT_FAILURE;
    }

    /*��������ַ�����ȥ����Ч��0XFF����*/
    while (ucPlmnRangeLen > 1)
    {
        if (0xFF == pucPlmnRange[ucPlmnRangeLen - 1])
        {
            ucPlmnRangeLen--;
        }
        else
        {
            break;
        }
    }

    /*�ж�pucPlmnRange��ָ����ַ��������һ���ֽڵĵ�λ�Ƿ�Ϊ1111��
    ����ǣ�˵������λ��Ϊ����������Ϊż��*/
    if ((pucPlmnRange[ucPlmnRangeLen - 1] & 0x0F) == 0x0F)
    {
        ucLen = (VOS_UINT8)((ucPlmnRangeLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucPlmnRangeLen * 2);
    }

    /*��������*/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*�жϵ�ǰ�����������λ���뻹��ż��λ�����0��ʼ��ż��*/
        if (0 == (ucLoop % 2))
        {
            /*�����ż��λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = ((pucPlmnRange[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*���������λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = (pucPlmnRange[(ucLoop / 2)] & 0x0F);
        }

        /*������ת����Ascii����ʽ*/
        if (ucBcdCode <= 9)
        {
            pucAsciiStr[ucLoop] = (ucBcdCode + '0');
        }
        else
        {
            return AT_FAILURE;
        }
    }

    pucAsciiStr[ucLoop] = '\0';      /*�ַ���ĩβΪ0*/

    return AT_SUCCESS;
}


VOS_UINT32 At_QrySimLockPlmnInfo(VOS_UINT8 ucIndex)
{
    TAF_CUSTOM_SIM_LOCK_PLMN_INFO_STRU  stSimLockPlmnInfo;
    VOS_UINT32                          i;
    VOS_UINT16                          usLength;
    VOS_UINT8                           ucMncLen;
    VOS_UINT32                          ulPlmnIdx;
    VOS_UINT32                          ulRsltChkPlmnBegin;
    VOS_UINT32                          ulRsltChkPlmnEnd;
    VOS_UINT32                          ulTotalPlmnNum;
    VOS_BOOL                            abPlmnValidFlg[TAF_MAX_SIM_LOCK_RANGE_NUM] = {VOS_FALSE};
    VOS_UINT8                           aucAsciiNumBegin[(TAF_PH_SIMLOCK_PLMN_STR_LEN * 2) + 1];
    VOS_UINT8                           aucAsciiNumEnd[(TAF_PH_SIMLOCK_PLMN_STR_LEN * 2) + 1];


    PS_MEM_SET(&stSimLockPlmnInfo, 0x00, sizeof(stSimLockPlmnInfo));


    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeSimLockPlmnInfo,
                       &stSimLockPlmnInfo,
                       sizeof(stSimLockPlmnInfo)))
    {
        return AT_ERROR;
    }

    ulTotalPlmnNum = 0;

    if (NV_ITEM_DEACTIVE == stSimLockPlmnInfo.ulStatus)
    {
        /* ״̬�Ǽ���ʱ����ʾPlmn����Ϊ0 */
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,ulTotalPlmnNum);

        gstAtSendData.usBufLen = usLength;
        return AT_OK;
    }

    /*  �ж�Plmn�Ŷ��Ƿ���Ч */
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        ucMncLen = stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum;

        ulRsltChkPlmnBegin = At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumBegin);
        
    #if (FEATURE_ON == MBB_COMMON)
        ulRsltChkPlmnEnd = At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeEnd,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumEnd);
    #else
        ulRsltChkPlmnEnd = At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumEnd);
    #endif
        
        if ((AT_SUCCESS == ulRsltChkPlmnBegin)
         && (AT_SUCCESS == ulRsltChkPlmnEnd)
         && ((ucMncLen <= 3) && (ucMncLen >= 2)))
        {
            abPlmnValidFlg[i] = VOS_TRUE;
            ++ ulTotalPlmnNum;
        }
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                       (VOS_CHAR *)pgucAtSndCodeAddr, "%s:%d",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,ulTotalPlmnNum);


    if (0 == ulTotalPlmnNum)
    {
        gstAtSendData.usBufLen = usLength;
        return AT_OK;
    }
    else
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s", gaucAtCrLf);
    }


    ulPlmnIdx = 0;
    for ( i = 0; i < TAF_MAX_SIM_LOCK_RANGE_NUM; i++ )
    {
        if (VOS_FALSE == abPlmnValidFlg[i])
        {
            continue;
        }

        ++ ulPlmnIdx;

        At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeBegin,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumBegin);

        At_SimlockPlmnNumToAscii(stSimLockPlmnInfo.astSimLockPlmnRange[i].aucRangeEnd,
                                    TAF_PH_SIMLOCK_PLMN_STR_LEN,aucAsciiNumEnd);

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                    (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                    "%s:%d,%d,%s,%s",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                    ulPlmnIdx,
                                    stSimLockPlmnInfo.astSimLockPlmnRange[i].ucMncNum,
                                    aucAsciiNumBegin,
                                    aucAsciiNumEnd);

        if (ulPlmnIdx < ulTotalPlmnNum)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                            "%s", gaucAtCrLf);
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

VOS_UINT32 At_QryMaxLockTimes(VOS_UINT8 ucIndex)
{
    TAF_CUSTOM_SIM_LOCK_MAX_TIMES_STRU          stSimLockMaxTimes;
    VOS_UINT32                                  ulResult;
    VOS_UINT16                                  usLength;


    stSimLockMaxTimes.ulStatus       = NV_ITEM_DEACTIVE;
    stSimLockMaxTimes.ulLockMaxTimes = 0;


    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_CustomizeSimLockMaxTimes,
                       &stSimLockMaxTimes,
                       sizeof(stSimLockMaxTimes));
    if (NV_OK != ulResult)
    {
        AT_WARN_LOG("At_QryMaxLockTimes():en_NV_Item_CustomizeSimLockMaxTimes NV_ReadEx Fail!");
        return AT_DEVICE_OTHER_ERROR;
    }


    /* ���NV��δ������ص���Ĭ��ֵ 10 */
    if (NV_ITEM_DEACTIVE == stSimLockMaxTimes.ulStatus)
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          TAF_PH_CARDLOCK_DEFAULT_MAXTIME);
    }
    else
    {
        usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                          (VOS_CHAR *)pgucAtSndCodeAddr,
                                          (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%d",
                                          g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                          stSimLockMaxTimes.ulLockMaxTimes);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32  At_QryAppWronReg( VOS_UINT8 ucIndex )
{
    /* ������Ϣ��MMA����ѯע��ʱ�� */
    if (TAF_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                    0,
                                    TAF_PH_REGISTER_TIME_VALUE_PARA,
                                    TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_REGISTER_TIME_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryNdisdupPara(
    VOS_UINT8                           ucIndex
)
{
    /* ������PDP TYPE û���������Ŀǰֻ����OK */
    return AT_OK;
}


VOS_UINT32 At_QryNdisConnPara(
    VOS_UINT8                           ucIndex
)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    /*--------------------------------------------------------------
       ���Ų�����ѯ, ֱ�ӷ��ر��ر������Ϣ, �����·���������ѯ,
       PS��ҵ�����ںϺ�, ��ѯ������ͳһ�޸�
    --------------------------------------------------------------*/
    AT_NDISCONN_PARA_STRU              *pstNdisConnDialInfo;
    VOS_UINT16                          usLength;

    /* ��ȡNDISCONN����ʱ�Ĳ��� */
    usLength            = 0;
    pstNdisConnDialInfo = AT_GetNdisConnParaAddr();

    /* ^NDISCONN:  */
    usLength =  (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR*)pgucAtSndCodeAddr, "%s:", "^NDISCONN");

    /*<pdpid>*/
    usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, "%d", pstNdisConnDialInfo->ucCID);


    /*��ǰ���ڼ���״̬ʱ���ϱ�APN����Ϣ*/
    if ( (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv6State)
      && (AT_PDP_STATE_IDLE == g_stAtNdisDhcpPara.enIpv4v6State) )
    {
        /*<connect>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", 0);
    }
    else
    {
        /*<connect>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", pstNdisConnDialInfo->ulConnectState);

        /*<APN>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",\"%s\"", pstNdisConnDialInfo->aucAPN);

        /*<username>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",\"%s\"", pstNdisConnDialInfo->aucUsername);

        /*<passwd>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",\"%s\"", pstNdisConnDialInfo->aucPassword);

        /*<auth>*/
        usLength += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,(TAF_CHAR *)pgucAtSndCodeAddr + usLength, ",%d", pstNdisConnDialInfo->usAuthType);
    }
    gstAtSendData.usBufLen = usLength;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */



    return AT_OK;
}

/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

AT_PDP_STATUS_ENUM_UINT32 AT_NdisGetConnStatus(
    AT_PDP_STATE_ENUM_U8                enPdpState
)
{
    AT_PDP_STATUS_ENUM_UINT32           enConnStatus;

    enConnStatus                        = AT_PDP_STATUS_DEACT;

    if ( (AT_PDP_STATE_ACTED    == enPdpState)
      || (AT_PDP_STATE_DEACTING == enPdpState) )
    {
        enConnStatus = AT_PDP_STATUS_ACT;
    }

    return enConnStatus;
}


VOS_UINT32 AT_ReportNdisStatInfo(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;
    AT_PDP_STATUS_ENUM_UINT32           enIpv4Status;

    /* ��ʼ�� */
    usLength        = 0;
    enIpv4Status    = AT_PDP_STATUS_DEACT;

    /* �ϱ���ѯ��� */
    if (AT_PDP_STATE_ACTED == AT_NdisGetState(TAF_PDP_IPV4))
    {
        enIpv4Status = AT_PDP_STATUS_ACT;
    }

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d",
                                       enIpv4Status);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryNdisStatPara(
    VOS_UINT8                           ucIndex
)
{
#if(FEATURE_ON == MBB_WPG_COMMON)    
    return AT_QryNdisStatParaEx(ucIndex);
#else/*FEATURE_ON == FEATURE_MBIM */

    AT_PDP_STATUS_ENUM_UINT32           enIpv4Status;
#if (FEATURE_ON == FEATURE_IPV6)
    AT_PDP_STATUS_ENUM_UINT32           enIpv6Status;
    AT_PDP_STATUS_ENUM_UINT32           enIpv4v6Status;
#endif
    VOS_UINT16                          usLength;
    VOS_UINT8                           aucAtStrIpv4[] = "IPV4";
#if (FEATURE_ON == FEATURE_IPV6)
    VOS_UINT8                           aucAtStrIpv6[] = "IPV6";
#endif

    usLength                            = 0;
    enIpv4Status                        = AT_PDP_STATUS_DEACT;
#if (FEATURE_ON == FEATURE_IPV6)
    enIpv6Status                        = AT_PDP_STATUS_DEACT;
    enIpv4v6Status                      = AT_PDP_STATUS_DEACT;
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    switch (AT_GetIpv6Capability())
    {
        case AT_IPV6_CAPABILITY_IPV4_ONLY:
            enIpv4Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv4Status,
                                               aucAtStrIpv4);
            break;

        case AT_IPV6_CAPABILITY_IPV6_ONLY:
            enIpv6Status    = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv6Status,
                                               aucAtStrIpv6);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_ONE_PDP:
            enIpv4v6Status  = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4V6));
            if ( AT_PDP_STATUS_ACT != enIpv4v6Status )
            {
                enIpv4Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4));
                enIpv6Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV6));
            }
            else
            {
                enIpv4Status = enIpv4v6Status;
                enIpv6Status = enIpv4v6Status;
            }

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv4Status,
                                               aucAtStrIpv4);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               ",%d,,,\"%s\"",
                                               enIpv6Status,
                                               aucAtStrIpv6);
            break;

        case AT_IPV6_CAPABILITY_IPV4V6_OVER_TWO_PDP:
            enIpv4Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4));
            enIpv6Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV6));

            usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: ",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%d,,,\"%s\"",
                                               enIpv4Status,
                                               aucAtStrIpv4);
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               ",%d,,,\"%s\"",
                                               enIpv6Status,
                                               aucAtStrIpv6);
            break;

        default:
            break;
    }
#else
    enIpv4Status = AT_NdisGetConnStatus(AT_NdisGetState(TAF_PDP_IPV4));

    usLength  = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                       (VOS_CHAR*)pgucAtSndCodeAddr,
                                       (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                       "%d,,,\"%s\"",
                                       enIpv4Status,
                                       aucAtStrIpv4);
#endif
    gstAtSendData.usBufLen = usLength;

    return AT_OK;
#endif/*FEATURE_ON == MBB_FEATURE_MPDP */

}


TAF_UINT32 At_QryNdisAddPara(VOS_UINT8 ucIndex)
{
    return AT_CMD_NOT_SUPPORT;
}
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


VOS_UINT32 At_QryDnsPrim(
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT16                          usLength;
    VOS_UINT32                          ulPdpStateFlag;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    AT_PDP_STATE_ENUM_U8                enState;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    ulPdpStateFlag                      = VOS_FALSE;
    usLength                            = 0;

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        ulPdpStateFlag = AT_AppCheckIpv4PdpState(AT_PDP_STATE_ACTED);
        if (VOS_TRUE != ulPdpStateFlag)
        {
            AT_WARN_LOG("At_QryDnsPrim:WARNING: PDP is not ativated!");
            return AT_CME_NO_CONNECTION_TO_PHONE;
        }

        if (VOS_FALSE == pstAppDialPara->ulPrimIPv4DNSValidFlag)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (VOS_CHAR*)pgucAtSndCodeAddr,
                                   (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                   "%s: %s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   "0.0.0.0");
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: %s",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstAppDialPara->aucPrimIPv4DNSAddr);
        }

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    enState = AT_NdisGetState(TAF_PDP_IPV4);
    if(AT_PDP_STATE_ACTED == enState)
    {
       ulPdpStateFlag = VOS_TRUE;
    }

    if (VOS_FALSE == ulPdpStateFlag)
    {
        AT_WARN_LOG("At_QryDnsPrim AT_NdisGetState:");
        return AT_CME_NO_CONNECTION_TO_PHONE;
    }

    if (VOS_FALSE == gstAtNdisAddParam.ulPrimIPv4DNSValidFlag)
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s",
                                               "^DNSP: 0.0.0.0");
    }
    else
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: %s",
                                               "^DNSP",
                                               gstAtNdisAddParam.aucPrimIPv4DNSAddr);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}


VOS_UINT32 At_QryDnsSnd(
    VOS_UINT8                           ucIndex
)
{
    TAF_UINT16                          usLength;
    VOS_UINT32                          ulPdpStateFlag;
    AT_PDP_STATE_ENUM_U8                enState;
    AT_DIAL_PARAM_STRU                 *pstAppDialPara;

    pstAppDialPara                      = AT_APP_GetDailParaAddr();

    ulPdpStateFlag                      = VOS_FALSE;
    usLength                            = 0;

    if (AT_APP_USER == gastAtClientTab[ucIndex].UserType)
    {
        ulPdpStateFlag = AT_AppCheckIpv4PdpState(AT_PDP_STATE_ACTED);
        if (VOS_TRUE != ulPdpStateFlag)
        {
            AT_WARN_LOG("At_QryDnsPrim:WARNING: PDP is not ativated!");
            return AT_CME_NO_CONNECTION_TO_PHONE;
        }

        if (VOS_FALSE == pstAppDialPara->ulSndIPv4DNSValidFlag)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: %s",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               "0.0.0.0");
        }
        else
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr + usLength,
                                               "%s: %s",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               pstAppDialPara->aucSndIPv4DNSAddr);

        }

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    enState = AT_NdisGetState(TAF_PDP_IPV4);
    if(AT_PDP_STATE_ACTED == enState)
    {
       ulPdpStateFlag = VOS_TRUE;
    }

    if (VOS_FALSE == ulPdpStateFlag)
    {
        AT_WARN_LOG("At_QryDnsPrim AT_NdisGetState:");
        return AT_CME_NO_CONNECTION_TO_PHONE;
    }

    if (VOS_FALSE == gstAtNdisAddParam.ulSndIPv4DNSValidFlag)
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s",
                                               "^DNSS: 0.0.0.0");
    }
    else
    {
        usLength    += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,(VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR*)pgucAtSndCodeAddr,
                                               "%s: %s",
                                               "^DNSS:",
                                               gstAtNdisAddParam.aucSndIPv4DNSAddr);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32  At_QryApDialModePara(
    VOS_UINT8                           ucIndex
)
{
    AT_RNIC_DIAL_MODE_REQ_STRU         *pstMsg;

    /* ����ID_RNIC_AT_DIAL_MODE_REQ��Ϣ */
    pstMsg = (AT_RNIC_DIAL_MODE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            WUEPS_PID_AT,
                            sizeof(AT_RNIC_DIAL_MODE_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        AT_WARN_LOG("At_QryApDialModePara: alloc msg fail!");
        return VOS_ERR;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(AT_RNIC_DIAL_MODE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_RNIC;
    pstMsg->enMsgId         = ID_AT_RNIC_DIAL_MODE_REQ;
    pstMsg->clientId        = gastAtClientTab[ucIndex].usClientId;

    /* ��ID_RNIC_AT_DIAL_MODE_REQ��Ϣ��RNIC��ȡ��ǰ������ */
    if (VOS_OK == PS_SEND_MSG(WUEPS_PID_AT, pstMsg))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APDIALMODE_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        AT_WARN_LOG("At_QryApDialModePara: Send msg failed!");
        return AT_ERROR;
    }
}


VOS_UINT32  AT_QryAppdmverPara ( VOS_UINT8 ucIndex )
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡ PDM�汾�� */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_APPDMVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAppdmverPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_APPDMVER_READ;
    return AT_WAIT_ASYNC_RETURN;

    /* Modified  by f62575 for AT Project, 2011-10-17, end */
}


VOS_UINT32  AT_QryDislogPara ( VOS_UINT8 ucIndex )
{
    AT_DIAG_OPEN_FLAG_ENUM_U32          enDiagPortState;

#if (FEATURE_ON==FEATURE_LTE)
    VOS_UINT32                          ulRetDiag;
    VOS_UINT32                          ulRet3GDiag;
    VOS_UINT32                          ulRetGps;

    ulRet3GDiag   = AT_ExistSpecificPort(AT_DEV_DIAG);
    ulRetDiag     = AT_ExistSpecificPort(AT_DEV_4G_DIAG);
    ulRetGps      = AT_ExistSpecificPort(AT_DEV_4G_GPS);

    if ((VOS_TRUE == ulRet3GDiag)
      &&(VOS_TRUE == ulRetDiag)
      &&(VOS_TRUE == ulRetGps))
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_OPEN;
    }
    else
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_CLOSE;
    }
#else
    /* Added by f62575 for B050 Project, 2012-2-3, Begin   */
    /* ��NV�ж�ȡ DISLOG ���������뼰DIAG�ڵĿ���״̬ */

    /*DIAG �ڵĿ���״̬, 0 ��; 1 �ر�*/
    if (VOS_TRUE != AT_ExistSpecificPort(AT_DEV_DIAG))
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_CLOSE;
    }
    else
    {
        enDiagPortState = AT_DIAG_OPEN_FLAG_OPEN;
    }

    /* Added by f62575 for B050 Project, 2012-2-3, End   */
#endif

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    enDiagPortState);
    return AT_OK;

}

#if (FEATURE_ON == FEATURE_SECURITY_SHELL)

VOS_UINT32 AT_QryShellPara (VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulShellStatus;


    ulShellStatus = AT_SHELL_CLOSE;


    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_AT_SHELL_OPEN_FLAG, &ulShellStatus,
                          sizeof(ulShellStatus)))
    {
        AT_WARN_LOG("AT_QryShellPara:WARNING:NV_ReadEx SHELL_OPEN_FLAG faild!");

        return AT_ERROR;
    }

    /* shell��״ֻ̬��Ϊ0,1,2 */
    if (AT_SHELL_OPEN < ulShellStatus)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR*)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulShellStatus);
    return AT_OK;

}
#endif

/* Added by f62575 for SMALL IMAGE, 2012-1-3, Begin   */

VOS_UINT32 AT_QryWifiGlobalMacPara(VOS_UINT8 ucIndex)
/* Added by f62575 for SMALL IMAGE, 2012-1-3, End   */
{
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulResult;
    /* Added by ��ӳ��/f62575 for E5�꿪�ش򿪺��������, 2011/11/15, begin */
    VOS_UINT8                           aucE5GwMacAddr[AT_MAC_ADDR_LEN+1]; /* MAC��ַ*/

    /* ��ȡ����MAC��ַ*/
    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_WIFI_MAC_ADDR, aucE5GwMacAddr, AT_MAC_ADDR_LEN);
    aucE5GwMacAddr[AT_MAC_ADDR_LEN] = '\0';
    /* Added by ��ӳ��/f62575 for AT Project, 2011/11/15, end */

    if ( NV_OK != ulResult )
    {
        AT_WARN_LOG("AT_QryApMacPara:read en_NV_Item_GWMAC_ADDR failed or no need to updatee");
        return AT_ERROR;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR*)pgucAtSndCodeAddr, "%s:%s",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      aucE5GwMacAddr);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

/* Added by f62575 for AT Project, 2011-10-04,  Begin */


VOS_UINT32 AT_QryDloadInfoPara( VOS_UINT8 ucIndex )
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡ������Ϣ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_DLOADINFO_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryDloadInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_DLOADINFO_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified  by f62575 for AT Project, 2011-10-17, end */
}


VOS_UINT32 AT_QryAuthorityVerPara( VOS_UINT8 ucIndex )
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡ��ȨЭ��汾�� */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHORITYVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAuthorityVerPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHORITYVER_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified  by f62575 for AT Project, 2011-10-17, end */
}


VOS_UINT32 AT_QryAuthorityIdPara( VOS_UINT8 ucIndex )
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡ��Ȩ��ʶ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHORITYID_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAuthorityIdPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHORITYID_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified  by f62575 for AT Project, 2011-10-17, end */
}


VOS_UINT32 AT_QryFlashInfoPara( VOS_UINT8 ucIndex )
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡFLASH��Ϣ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_FLASHINFO_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryFlashInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FLASHINFO_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified  by f62575 for AT Project, 2011-10-17, end */

}


VOS_UINT32 AT_QryAuthverPara(VOS_UINT8 ucIndex)
{
    /* Modified  by f62575 for AT Project, 2011-10-17, begin */
    VOS_UINT32                          ulRet;

#if ((FEATURE_ON == MBB_SIMLOCK_THREE) || (FEATURE_ON == MBB_SIMLOCK_FOUR))
#if (FEATURE_ON == MBB_SIMLOCK_THREE)
    VOS_UINT32       SIMLCOK_VERSION = SIMLOCK_VERSION_THREE;
#else
    VOS_UINT32       SIMLCOK_VERSION = SIMLOCK_VERSION_FOUR;
#endif /*MBB_SIMLOCK_THREE*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     SIMLCOK_VERSION);
    return AT_OK;
#else

    /* ����Ϣ��C�˻�ȡSIMLOCK MANAGER�汾��Ϣ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_AUTHVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryAuthverPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_AUTHVER_READ;
    return AT_WAIT_ASYNC_RETURN;
    /* Modified  by f62575 for AT Project, 2011-10-17, end */
#endif

}


VOS_UINT32 AT_QryWiFiEnablePara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
#if (FEATURE_ON == MBB_WIFI)

    /* ���������ӿڲ�ѯ��ǰWiFi��״̬ */
    WLAN_AT_WIENABLE_TYPE  ulWifiStatus;

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }
    
    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    
    ulWifiStatus = WlanATGetWifiEnable();

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ulWifiStatus);
#endif
    return AT_OK;
#else
    /* ���������ӿڲ�ѯ��ǰWiFi��״̬ */
    VOS_UINT32                          ulWifiStatus;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    ulWifiStatus = (VOS_UINT32)WIFI_GET_STATUS();

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ulWifiStatus);
    return AT_OK;
#endif
}

VOS_UINT32 AT_QryWiFiModePara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
#if (FEATURE_ON == MBB_WIFI)

    WLAN_AT_BUFFER_STRU     strBuf;

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ʼ�� */
    (void)VOS_MemSet((void *)&strBuf, 0, sizeof(strBuf));

    /* ��ȡWIFIģʽ */
    if(AT_RETURN_SUCCESS != WlanATGetWifiMode(&strBuf))
    {
        return AT_ERROR;
    }
    
    /* WIFIģ��ģʽ */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    strBuf.buf);
#endif
    return AT_OK;
#else
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* WIFIģ��ֻ֧��B/G/Nģʽ */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiMode);
    return AT_OK;
#endif
}

VOS_UINT32 AT_QryWiFiBandPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
#if (FEATURE_ON == MBB_WIFI)

    WLAN_AT_BUFFER_STRU     strBuf;

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ʼ�� */
    (void)VOS_MemSet((void *)&strBuf, 0, sizeof(strBuf));
    
    /* ��ȡWIFI���� */
    if(AT_RETURN_SUCCESS != WlanATGetWifiBand(&strBuf))
    {
        return AT_ERROR;
    }
    
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    strBuf.buf);
#endif
    return AT_OK;
#else
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* Ŀǰֻ֧��20M���� */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     AT_WIFI_BAND_20M);
    return AT_OK;
#endif
}

VOS_UINT32 AT_QryWiFiFreqPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
#if (FEATURE_ON == MBB_WIFI)

    WLAN_AT_WIFREQ_STRU wifiReqStru;

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ʼ�� */
    (void)VOS_MemSet((void *)&wifiReqStru, 0, sizeof(wifiReqStru));
    
    if (AT_RETURN_SUCCESS != WlanATGetWifiFreq(&wifiReqStru))
    {
        return AT_ERROR;
    }

    /* ��ѯ����ֵ */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    wifiReqStru.value);
#endif
    return AT_OK;
#else
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */


    /* ��ѯ����ֵ */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiFreq);
    return AT_OK;
#endif
}

VOS_UINT32 AT_QryWiFiRatePara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
#if (FEATURE_ON == MBB_WIFI)

    VOS_UINT32 wifiDataRate;

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ȡWIFI���� */
    wifiDataRate = WlanATGetWifiDataRate();
    
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    wifiDataRate);
#endif
    return AT_OK;
#else
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* ��ѯ����ֵ */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_ulWifiRate);
    return AT_OK;
#endif
}

VOS_UINT32 AT_QryWiFiPowerPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
#if (FEATURE_ON == MBB_WIFI)

    TAF_INT32 lWifiPower;
    
    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ѯWIFI���� */
    lWifiPower = WlanATGetWifiPOW();
    
    /* ��ѯ����ֵ */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    lWifiPower);
#endif
    return AT_OK;
#else
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */



    /* ��ѯ����ֵ */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    g_lWifiPower);
    return AT_OK;
#endif
}

VOS_UINT32 AT_QryWiFiTxPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
#if (FEATURE_ON == MBB_WIFI)

    WLAN_AT_FEATURE_TYPE   ucWifiTxStatus;

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    ucWifiTxStatus = WlanATGetWifiTX();
    
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiTxStatus );
#endif
    return AT_OK;
#else
    VOS_UINT8   ucWifiTxStatus;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* ���������ӿڲ�ѯ��ǰWiFi��ģʽ */
    if (AT_WIFI_TX_MODE == WIFI_GET_TCMD_MODE())
    {
        ucWifiTxStatus = AT_WIFI_TX_ON;
    }
    else
    {
        ucWifiTxStatus = AT_WIFI_TX_OFF;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiTxStatus );
    return AT_OK;
#endif
}

VOS_UINT32 AT_QryWiFiRxPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
#if (FEATURE_ON == MBB_WIFI)

    WLAN_AT_WIRX_STRU   wifiRxStru;
    (void)VOS_MemSet((void *)&wifiRxStru, 0, sizeof(wifiRxStru));

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ȡWIFI RX��Ϣ */
    if(AT_RETURN_SUCCESS != WlanATGetWifiRX(&wifiRxStru))
    {
        return AT_ERROR;
    }
    
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    wifiRxStru.onoff);
#endif
    return AT_OK;
#else
    VOS_UINT8                           ucWifiRxStatus;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */


    /* ���������ӿڲ�ѯ��ǰWiFi��ģʽ */
    if (AT_WIFI_RX_MODE == WIFI_GET_TCMD_MODE())
    {
        ucWifiRxStatus = AT_WIFI_TX_ON;
    }
    else
    {
        ucWifiRxStatus = AT_WIFI_TX_OFF;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiRxStatus );
    return AT_OK;
#endif
}

VOS_UINT32 AT_QryWiFiPacketPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
#if (FEATURE_ON == MBB_WIFI)

    WLAN_AT_WIRPCKG_STRU   wifiPckStru;

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ʼ�� */
    (void)VOS_MemSet((void *)&wifiPckStru, 0, sizeof(wifiPckStru));

    /* ��ȡWIFI���ջ������ */
    if(AT_RETURN_SUCCESS != WlanATGetWifiRPCKG(&wifiPckStru))
    {
        return AT_ERROR;
    }
    
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    wifiPckStru.good_result, wifiPckStru.bad_result);
#endif
    return AT_OK;
#else
    VOS_UINT                                ulUcastWifiRxPkts;
    VOS_UINT                                ulMcastWifiRxPkts;
    VOS_UINT32                              ulWifiRxPkts;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */


    /* �жϽ��ջ��Ƿ�� */
    if (AT_WIFI_RX_MODE != WIFI_GET_TCMD_MODE())
    {
        AT_WARN_LOG("AT_QryWiFiPacketPara: Not Rx Mode.");
        return AT_ERROR;
    }

    /* ���������ӿڲ�ѯ�������� */
    WIFI_GET_RX_PACKET_REPORT(&ulUcastWifiRxPkts,  &ulMcastWifiRxPkts);
    ulWifiRxPkts = (ulUcastWifiRxPkts - g_ulUcastWifiRxPkts);

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulWifiRxPkts,
                                                    0);

    return AT_OK;
#endif
}

/* Modify by z60575 for multi_ssid, 2012-9-5 begin */

VOS_UINT32 AT_QryWiFiSsidPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               ucSsidNum;
    VOS_UINT32                                              ulLoop;
    VOS_UINT8                                               aucSsidLen[AT_WIFI_MAX_SSID_NUM];

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    PS_MEM_SET(&stWifiSsid, 0 ,sizeof(stWifiSsid));

    /*��ȡWIFI SSID��Ӧ��NV��*/
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID,&stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("AT_SetWiFiSsidPara:READ NV ERROR");
        return AT_ERROR;
    }

    ucSsidNum = 0;
    PS_MEM_SET(aucSsidLen, 0, sizeof(aucSsidLen));

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        aucSsidLen[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)stWifiSsid.aucWifiSsid[ulLoop]);

        if (0 != aucSsidLen[ulLoop])
        {
            ucSsidNum++ ;
        }
    }

    usLen = 0;
    usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                    (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                    "%s:%d%s",
                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                    ucSsidNum,
                                    gaucAtCrLf);

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        if (0 != aucSsidLen[ulLoop])
        {
            /* ����˫���� */
            usLen += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        #if (FEATURE_ON == MBB_COMMON)
                                            "%s:%d,%s%s%s%s",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulLoop,
                                            gaucAtQuotation,stWifiSsid.aucWifiSsid[ulLoop],gaucAtQuotation,gaucAtCrLf);
                                        #else
                                            "%s:%d,%s%s",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulLoop,
                                            stWifiSsid.aucWifiSsid[ulLoop],
                                            gaucAtCrLf);
                                        #endif
        }
    }

#if (FEATURE_ON == MBB_COMMON)
    /* ȥ���ַ�����β�س����� */
    gstAtSendData.usBufLen = usLen - (VOS_UINT16)VOS_StrLen((VOS_CHAR *)gaucAtCrLf);
#else
    gstAtSendData.usBufLen = usLen;
#endif

    return AT_OK;
}


VOS_UINT32 AT_QryWiFiLogPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SSID_STRU                             stWifiSsid;
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiSec;
    VOS_UINT16                                              usLen;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    PS_MEM_SET(&stWifiSec, 0, sizeof(stWifiSec));
    PS_MEM_SET(&stWifiSsid, 0, sizeof(stWifiSsid));

    /* ��ȡWIFI SSID��Ӧ��NV�� */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_STATUS_SSID,&stWifiSsid, sizeof(TAF_AT_MULTI_WIFI_SSID_STRU)))
    {
        AT_WARN_LOG("AT_QryWiFiLogPara:READ NV FAIL");
        return AT_ERROR;
    }

    usLen = 0;

    usLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                   "%s:0,%s%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   stWifiSsid.aucWifiSsid[0],
                                   gaucAtCrLf);

    /* ��ȡWIFI key��Ӧ��NV�� */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiSec,sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("AT_QryWiFiLogPara:READ NV FAIL");
        return AT_ERROR;
    }

    /* KEY1��Ӧ��NV���ձ�ʾKEY1��Ч */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey1[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:1,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey1[0],
                                        gaucAtCrLf);
    }

    /* KEY2��Ӧ��NV���ձ�ʾKEY2��Ч */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey2[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:2,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey2[0],
                                        gaucAtCrLf);
    }
    /* KEY3��Ӧ��NV���ձ�ʾKEY3��Ч */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey3[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:3,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey3[0],
                                        gaucAtCrLf);
    }
    /* KEY4��Ӧ��NV���ձ�ʾKEY3��Ч */
    if (0 != VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWepKey4[0]))
    {
        usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                        (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        "%s:4,%s%s",
                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                        stWifiSec.aucWifiWepKey4[0],
                                        gaucAtCrLf);
    }

    gstAtSendData.usBufLen = usLen;

    return AT_OK;
}

VOS_UINT32 AT_QryWiFiKeyPara(VOS_UINT8 ucIndex)
{
    TAF_AT_MULTI_WIFI_SEC_STRU                              stWifiSec;
    VOS_UINT8                                               ucWifiKeyNum;
    VOS_UINT16                                              usLen;
    VOS_UINT8                                               aucWpapskLen[AT_WIFI_MAX_SSID_NUM];
    VOS_UINT32                                              ulLoop;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    PS_MEM_SET(&stWifiSec, 0, sizeof(stWifiSec));

    /* ��ȡWIFI key��Ӧ��NV�� */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_MULTI_WIFI_KEY, &stWifiSec,sizeof(TAF_AT_MULTI_WIFI_SEC_STRU)))
    {
        AT_WARN_LOG("AT_QryWiFiSsidPara:READ NV FAIL");
        return AT_ERROR;
    }


    ucWifiKeyNum = 0;
    PS_MEM_SET(aucWpapskLen, 0, sizeof(aucWpapskLen));

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {

        /* KEY1��Ӧ��NV���ձ�ʾKEY1��Ч */
        aucWpapskLen[ulLoop] = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)stWifiSec.aucWifiWpapsk[ulLoop]);

        if (0 != aucWpapskLen[ulLoop])
        {
            ucWifiKeyNum++ ;
        }
    }

    /* δ����ʱ����Ҫ�����Ѷ���0�� */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        ucWifiKeyNum = 0;
        PS_MEM_SET(aucWpapskLen, 0, sizeof(aucWpapskLen));
    }

    usLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   "%s:%d%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   ucWifiKeyNum,
                                   gaucAtCrLf);

    for (ulLoop = 0; ulLoop < AT_WIFI_MAX_SSID_NUM; ulLoop++)
    {
        if (0 != aucWpapskLen[ulLoop])
        {
            /* ����˫���� */
            usLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                        #if (FEATURE_ON == MBB_COMMON)
                                            "%s:%d,%s%s%s%s",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulLoop,
                                            gaucAtQuotation,stWifiSec.aucWifiWpapsk[ulLoop],gaucAtQuotation,gaucAtCrLf);
                                        #else
                                            "%s:%d,%s%s",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ulLoop,
                                            stWifiSec.aucWifiWpapsk[ulLoop],
                                            gaucAtCrLf);
                                        #endif
        }
    }

#if (FEATURE_ON == MBB_COMMON)
    /* ȥ���ַ�����β�س����� */
    gstAtSendData.usBufLen = usLen - (VOS_UINT16)VOS_StrLen((VOS_CHAR *)gaucAtCrLf);
#else
    gstAtSendData.usBufLen = usLen;

#endif

    return AT_OK;
}
/* Modify by z60575 for multi_ssid, 2012-9-5 end */


VOS_UINT32 AT_QryWifiPaRangePara (VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
#if (FEATURE_ON == MBB_WIFI)

    WLAN_AT_WiPARANGE_TYPE   ucWifiPaType;

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    ucWifiPaType = WlanATGetWifiParange();
    
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%c",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiPaType );
#endif
    return AT_OK;
#else
    AT_WIFI_MODE_ENUM_UINT8             ucCurWifiMode;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */


    /* ���õ����ṩ��ѯ�ӿڻ�ȡ��ǰWIFIģʽ */
    ucCurWifiMode   = (VOS_UINT8)WIFI_GET_PA_CUR_MODE();

    if (AT_WIFI_MODE_ONLY_PA == ucCurWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        "h");
    }
    else if (AT_WIFI_MODE_ONLY_NOPA == ucCurWifiMode)
    {
        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        (VOS_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:%s",
                                                        g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                        "l");
    }
    else
    {
        return AT_ERROR;
    }
    return AT_OK;
#endif
}

 
VOS_UINT32 AT_QryProdTypePara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                              gastAtClientTab[ucIndex].opId,
                                              DRV_AGENT_PRODTYPE_QRY_REQ,
                                              VOS_NULL_PTR,
                                              0,
                                              I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PRODTYPE_QRY;             /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                            /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}

VOS_UINT32 AT_QryTmmiPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucFacInfo[AT_FACTORY_INFO_LEN];
    VOS_UINT8                           ucMmiFlag;
    VOS_UINT32                          ulResult;

    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_Item_Factory_Info,
                       aucFacInfo,
                       AT_FACTORY_INFO_LEN);

    if (NV_OK != ulResult)
    {
        return AT_ERROR;
    }

    if (VOS_OK == VOS_MemCmp(&aucFacInfo[AT_MMI_TEST_FLAG_OFFSET],
                             AT_MMI_TEST_FLAG_SUCC,
                             AT_MMI_TEST_FLAG_LEN))
    {
        ucMmiFlag = VOS_TRUE;
    }
    else
    {
        ucMmiFlag = VOS_FALSE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "%s:%d",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            ucMmiFlag);

    return AT_OK;
}


VOS_UINT32 AT_QryChrgInfoPara(VOS_UINT8 ucIndex)
{

    VOS_UINT32                          ulChargeState;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_BATTERY_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* ���������ӿڻ�ȡ���״̬ */
    ulChargeState = (VOS_UINT32)DRV_CHG_GET_CHARGING_STATUS();

    /* ��ӡ��� */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)(pgucAtSndCodeAddr),
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulChargeState);

    return AT_OK;

}


VOS_UINT32 AT_QryChrgEnablePara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_COMMON)
    CHG_TCHRENABLE_TYPE chrenable_state;
    
    if (BSP_MODULE_UNSUPPORT == DRV_GET_BATTERY_SUPPORT() )
    {
        return AT_ERROR;
    }

    (void)VOS_MemSet((void *)&chrenable_state, 0, sizeof(chrenable_state));
    
    if(CHG_OK != chg_tbat_get_tchrenable_status(&chrenable_state))
    {
        return AT_ERROR;
    }
    
    if(AT_TCHRENABEL_SWITCH_CHARG_OPEN == chrenable_state.chg_state)
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       "%s:%d,%d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       chrenable_state.chg_state,
                                                       chrenable_state.chg_mode);
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       "%s:%d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       chrenable_state.chg_state);
    }

    return AT_OK;
#else
    VOS_UINT32                            ucChargeEnable;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_BATTERY_SUPPORT() )
    {
        return AT_ERROR;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */

    /* ���������ӿڻ�ȡ���״̬ */

    ucChargeEnable = (VOS_UINT32)DRV_CHG_STATE_GET();
    /* ��ӡ��� */
    /* ֻ��TRUE/FLASE�ķ���ֵ����Ч�� */
    if((ucChargeEnable == TRUE)||( ucChargeEnable == FALSE))
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       (TAF_CHAR *)pgucAtSndCodeAddr,
                                                       "%s:%d",
                                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                       ucChargeEnable);

        return AT_OK;
    }
    else
    {
        return AT_ERROR;
    }
#endif
}

VOS_UINT32 AT_QryWebPwdPara(VOS_UINT8 ucIndex)
{
    TAF_AT_NVIM_WEB_ADMIN_PASSWORD_STRU stWebPwd;

    PS_MEM_SET(&stWebPwd, 0x0, sizeof(stWebPwd));

    /* ��ȡWEBPWD��Ӧ��NV�� */
    if (VOS_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_WEB_ADMIN_PASSWORD, &stWebPwd, sizeof(stWebPwd)))
    {
        AT_WARN_LOG("AT_QryWebPwdPara:READ NV FAIL");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s,%s",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stWebPwd.aucWebPwd);
    return AT_OK;
}

VOS_UINT32 AT_GetWcdmaBandStr(
    VOS_UINT8                          *pucGsmBandstr,
    AT_UE_BAND_CAPA_ST                 *pstBandCapa
)
{
    VOS_UINT32                          ulLen;
    ulLen = 0;

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_I_2100)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC1,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_II_1900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC2,");
    }


    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_III_1800)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC3,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_IV_1700)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC4,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_V_850)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC5,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VI_800)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC6,");
    }


    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VII_2600)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC7,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_VIII_900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC8,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_IX_J1700)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC9,");
    }

    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_XI_1500)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "BC11,");
    }
    if (1 == pstBandCapa->unWRFSptBand.BitBand.BandWCDMA_XIX_850)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "BC19,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
 }


VOS_UINT32 AT_GetWcdmaDivBandStr(
    VOS_UINT8                          *pucGsmBandstr
)
{
    VOS_UINT32                                  ulLen;
    VOS_UINT32                                  ulBand;

    AT_WCDMA_PREF_BAND_STRU      *pstBitBand;

    /* ��ȡUMTS֧�ֵķּ�Ƶ������
        V3R2�汾��en_NV_Item_W_RF_DIV_BAND��V3R1��en_NV_Item_ANTENNA_CONFIG */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_W_RF_DIV_BAND, &ulBand, sizeof(ulBand)))
    {
        AT_WARN_LOG("AT_GetWcdmaDivBandStr: Read NVIM Smss Error");
        return 0;
    }

    ulLen = 0;
    pstBitBand = (AT_WCDMA_PREF_BAND_STRU *)&ulBand;

    /* ����ּ�֧�ֵ�BAND ͨ·������Ϊʮ��������ת��Ϊ�����ƺ�
        ������������ΪBand1��2��3������*/

    if (1 == pstBitBand->BandWCDMA_I_2100)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U1,");
    }

    if (1 == pstBitBand->BandWCDMA_II_1900)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U2,");
    }


    if (1 == pstBitBand->BandWCDMA_III_1800)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U3,");
    }

    if (1 == pstBitBand->BandWCDMA_IV_1700)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U4,");
    }

    if (1 == pstBitBand->BandWCDMA_V_850)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U5,");
    }

    if (1 == pstBitBand->BandWCDMA_VI_800)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U6,");
    }


    if (1 == pstBitBand->BandWCDMA_VII_2600)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U7,");
    }

    if (1 == pstBitBand->BandWCDMA_VIII_900)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U8,");
    }

    if (1 == pstBitBand->BandWCDMA_IX_J1700)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U9,");
    }

    if (1 == pstBitBand->BandWCDMA_XI_1500)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U11,");
    }

    if (1 == pstBitBand->BandWCDMA_XIX_850)
    {
        ulLen += (VOS_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pucGsmBandstr,
                                      (VOS_CHAR *)pucGsmBandstr + ulLen,
                                      "U19,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
 }


VOS_UINT32 AT_GetGsmBandStr(
    VOS_UINT8                          *pucGsmBandstr ,
    AT_UE_BAND_CAPA_ST                 *pstBandCapa
)
{
    VOS_UINT32                          ulLen;

    ulLen = 0;

    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm450)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "450,");
    }

    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm480)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "480,");
    }


    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm850)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "850,");
    }


    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsmP900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "P900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsmR900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "R900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsmE900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "E900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm1800)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "1800,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm1900)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "1900,");
    }
    if (1 == pstBandCapa->unGRFSptBand.BitBand.BandGsm700)
    {
        ulLen += (TAF_UINT32)At_sprintf(AT_CMD_MAX_LEN,
                                      (TAF_CHAR *)pucGsmBandstr,
                                      (TAF_CHAR *)pucGsmBandstr + ulLen,
                                      "700,");
    }

    if (ulLen != 0)
    {
        pucGsmBandstr[ulLen - 1] = '\0';
    }

    return ulLen;
}
 
VOS_UINT32 AT_QryFeaturePara(VOS_UINT8 ucIndex)
{
    if (TAF_SUCCESS == AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                             gastAtClientTab[ucIndex].opId,
                                             DRV_AGENT_SFEATURE_QRY_REQ,
                                             VOS_NULL_PTR,
                                             0,
                                             I0_WUEPS_PID_DRV_AGENT))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SFEATURE_QRY;           /*���õ�ǰ����ģʽ */
        return AT_WAIT_ASYNC_RETURN;                                            /* �ȴ��첽�¼����� */
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryProdNamePara(VOS_UINT8 ucIndex)
{
    TAF_AT_PRODUCT_ID_STRU              stProductId;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stProductId,0,sizeof(TAF_AT_PRODUCT_ID_STRU));

    /* ��NV50048�ж�ȡ��Ʒ���� */
    /* ��ȡNV��en_NV_Item_PRODUCT_ID��ȡ��Ʒ���� */
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_PRODUCT_ID,
                    &stProductId,
                    sizeof(stProductId.ulNvStatus) + sizeof(stProductId.aucProductId));

    if (NV_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryProdNamePara: Fail to read en_NV_Item_PRODUCT_ID");
        return AT_ERROR;
    }

    /*��NV�Ƿ�ʹ��*/
    if (VOS_TRUE != stProductId.ulNvStatus)
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stProductId.aucProductId);

    return AT_OK;
}


VOS_UINT32 AT_QryEqverPara(VOS_UINT8 ucIndex)
{
    /*<version>װ����һ�� AT����汾�ţ��汾������λ��ʾ��ÿλΪ0~9�������ַ���
    �ð汾��ȡ���ڵ���ʵ�ֵ�AT����ʱ�ο��ı��ĵ��İ汾�š�
    114 ֧�ֹ�һ��AT����汾��ѯ�ĵ�һ���汾
    balong�̶�����115*/
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, Begin   */
    VOS_UINT32                          ulRet;
    TAF_AT_EQ_VER_STRU                  stEqver;

    stEqver.usEqver = 0;

    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_Eqver, &stEqver.usEqver, sizeof(stEqver.usEqver));
    if (NV_OK != ulRet)
    {
        return AT_ERROR;
    }
    /* Modify by f62575 for V7����ͬ��, 2012-04-07, End   */

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     stEqver.usEqver);

    return AT_OK;
}


/* Added by l60609 for XML, 2011-08-11 Begin */

VOS_UINT32 AT_QryApRptSrvUrlPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucApRptSrvUrl[AT_AP_NVIM_XML_RPT_SRV_URL_LEN + 1];
    VOS_UINT32                          ulRet;
    TAF_AT_NVIM_AP_RPT_SRV_URL_STRU     stApRptSrvUrl;

    PS_MEM_SET(aucApRptSrvUrl, 0, AT_AP_NVIM_XML_RPT_SRV_URL_LEN + 1);

    /* ��NV:en_NV_Item_AP_RPT_SRV_URL*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AP_RPT_SRV_URL,
                    &stApRptSrvUrl,
                    AT_AP_NVIM_XML_RPT_SRV_URL_LEN);

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryApRptSrvUrlPara:Read NV fail");
        return AT_ERROR;
    }
    PS_MEM_CPY(aucApRptSrvUrl, stApRptSrvUrl.aucApRptSrvUrl, AT_AP_NVIM_XML_RPT_SRV_URL_LEN);
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:\"%s\"",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    aucApRptSrvUrl);

    return AT_OK;
}


VOS_UINT32 AT_QryApXmlInfoTypePara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           aucApXmlInfoType[AT_AP_XML_RPT_INFO_TYPE_LEN + 1];
    VOS_UINT32                          ulRet;
    TAF_AT_NVIM_AP_XML_INFO_TYPE_STRU   stApXmlInfoType;

    PS_MEM_SET(aucApXmlInfoType, 0, AT_AP_XML_RPT_INFO_TYPE_LEN + 1);

    /* ��NV:en_NV_Item_AP_XML_INFO_TYPE*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AP_XML_INFO_TYPE,
                    &stApXmlInfoType,
                    AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN);

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryApXmlInfoTypePara:Read NV fail");
        return AT_ERROR;
    }

    PS_MEM_CPY(aucApXmlInfoType, stApXmlInfoType.aucApXmlInfoType, AT_AP_NVIM_XML_RPT_INFO_TYPE_LEN);

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    aucApXmlInfoType);

    return AT_OK;
}


VOS_UINT32 AT_QryApXmlRptFlagPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    TAF_AT_NVIM_AP_XML_RPT_FLG_STRU     stApXmlRptFlg;
    VOS_UINT32                          ulLength;

    ulLength                   = 0;

    NV_GetLength(en_NV_Item_AP_XML_RPT_FLAG, &ulLength);

    stApXmlRptFlg.ucApXmlRptFlg = VOS_FALSE;

    /* ��NV:en_NV_Item_AP_XML_RPT_FLAG*/
    ulRet = NV_ReadEx(MODEM_ID_0, en_NV_Item_AP_XML_RPT_FLAG,
                        &stApXmlRptFlg,
                        ulLength);

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryApXmlRptFlagPara:Read NV fail");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    stApXmlRptFlg.ucApXmlRptFlg);

    return AT_OK;
}

/* Added by l60609 for XML, 2011-08-11 End */

/* Added by h44270 for V7R1 phase III, 2011-10-18, begin */

VOS_UINT32 AT_QryFastDormPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRslt;

    /* ����MN_FillAndSndAppReqMsg()���ȴ�RABM�Ļظ� */
    ulRslt = AT_SndQryFastDorm(gastAtClientTab[ucIndex].usClientId,gastAtClientTab[ucIndex].opId);
    if (AT_SUCCESS == ulRslt)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_FASTDORM_READ;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}
/* Added by h44270 for V7R1 phase III, 2011-10-18, end */


VOS_UINT32 AT_QryAcpuMemInfoPara(TAF_UINT8 ucIndex)
{
    vos_printf("AT_QryAcpuMemInfoPara:at cmd\r\n");

    /*����״̬���ͼ��*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /*������ֻ��Ҫ����TTF�Ľӿڼ��ɣ���TTF��SDT�ϱ��ڴ���Ϣ��AT�������Ҫ��ʾ*/
    IMM_MntnAcpuCheckPoolLeak();

    return AT_OK;

}



VOS_UINT32 AT_QryCcpuMemInfoPara(TAF_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase II, 2012-12-22, Begin */
    VOS_UINT32                          ulRet;

    vos_printf("AT_QryCcpuMemInfoPara:at cmd\r\n");

    /*����״̬���ͼ��*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* ����Ϣ��C�˴���CCPU�ڴ�й©��� */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_QRY_CCPU_MEM_INFO_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryCcpuMemInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* Modified by l60609 for DSDA Phase II, 2012-12-22, End */
    return AT_OK;
}


VOS_UINT32 AT_QryCipherPara(VOS_UINT8 ucIndex)
{
    MN_MMA_CIPHER_QRY_REQ_STRU          stCipherQryReq;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stCipherQryReq, 0, sizeof(stCipherQryReq));

    /* ����Ϣ��MMA��ȡCipher��Ϣ */
    ulResult =  AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                       gastAtClientTab[ucIndex].opId,
                                       TAF_MSG_MMA_CIPHER_INFO,
                                       &stCipherQryReq,
                                       sizeof(MN_MMA_CIPHER_QRY_REQ_STRU),
                                       I0_WUEPS_PID_MMA);

    /* ִ��������� */
    if (AT_SUCCESS == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIPERQRY_READ;

        /* ������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 AT_QryLocinfoPara(VOS_UINT8 ucIndex)
{
    MN_MMA_LOCATION_INFO_REQ_STRU       stLocInfoReq;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stLocInfoReq, 0, sizeof(stLocInfoReq));

    /* ����Ϣ��MMA��ȡ��ǰUE��λ����Ϣ */
    ulResult =  AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                       gastAtClientTab[ucIndex].opId,
                                       TAF_MSG_MMA_LOCATION_INFO,
                                       &stLocInfoReq,
                                       sizeof(MN_MMA_LOCATION_INFO_REQ_STRU),
                                       I0_WUEPS_PID_MMA);

    /* ִ��������� */
    if (AT_SUCCESS == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_LOCINFO_READ;

        /* ������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

/* Added by l60609 for B070 Project, 2012/03/09, begin */

VOS_UINT32 AT_QryNvResumePara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usNvResumeFlag;


    usNvResumeFlag = AT_NV_RESUME_SUCC;


    /* ��ȡen_NV_Resume_Flag */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Resume_Flag, &usNvResumeFlag, sizeof(VOS_UINT16)))
    {
        AT_WARN_LOG("AT_QryNvResumePara:READ NV FAIL");
        return AT_ERROR;
    }

    /* ������ֵֻ��Ϊ0����1 */
    if ((AT_NV_RESUME_SUCC != usNvResumeFlag)
     && (AT_NV_RESUME_FAIL != usNvResumeFlag))
    {
        AT_WARN_LOG("AT_QryNvResumePara:PARA IS INVALID");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     usNvResumeFlag);
    return AT_OK;
}
/* Added by l60609 for B070 Project, 2012/03/09, end */


VOS_UINT32 AT_QryNvBackupStatusPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡ��ǰNV����״̬��Ϣ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NVBACKUPSTAT_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryNvBackupStatusPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NVBACKUPSTAT_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryNandBadBlockPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡNAND FLASH�����л��������б���Ϣ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NANDBBC_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryNandBadBlockPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NANDBBC_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryNandDevInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡNAND FLASH���ͺ���Ϣ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_NANDVER_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryNandDevInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NANDVER_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryChipTempPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡPA��SIM���͵�ص��¶���Ϣ */
    ulRet = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   DRV_AGENT_CHIPTEMP_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);
    if (TAF_SUCCESS != ulRet)
    {
        AT_WARN_LOG("AT_QryChipTempPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CHIPTEMP_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryApRptPortSelectPara(VOS_UINT8 ucIndex)
{
    /* Modified by l60609 for Optimize RIL, 2013-7-11, Begin */
    VOS_UINT32                          ulPortSel1;
    VOS_UINT32                          ulPortSel2;
    VOS_UINT8                           ucClientIndex;
    AT_CLIENT_CTX_STRU                 *pstAtClientCtx = VOS_NULL_PTR;

    ulPortSel1 = 0;
    ulPortSel2 = 0;

    /* ͨ����� */
    /* Modified by L60609 for MUX��2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��2012-08-13,  End */
    {
        return AT_ERROR;
    }

    /* ��ȫ�ֱ����ж�ȡAP���õ������ϱ��˿ں� */
    for (ucClientIndex = 0; ucClientIndex < AT_CLIENT_BUTT; ucClientIndex++)
    {
        /* ��ȫ�ֱ�����ȡ��Ӧ�˿ڵ�����״̬ */
        pstAtClientCtx = AT_GetClientCtxAddr(ucClientIndex);

        /* ������������32bit�Ĳ��� */
        if (ucClientIndex >= 32)
        {
            if (VOS_TRUE == pstAtClientCtx->stClientConfiguration.ucReportFlg)
            {
                ulPortSel2 += 1 << (ucClientIndex - 32);
            }
        }
        else
        {
            if (VOS_TRUE == pstAtClientCtx->stClientConfiguration.ucReportFlg)
            {
                ulPortSel1 += 1 << ucClientIndex;
            }
        }
    }

    /* ���ز�ѯ��� */
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %X, %X",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ulPortSel1, ulPortSel2);

    /* Modified by l60609 for Optimize RIL, 2013-7-11, Begin */

    return AT_OK;
}




VOS_UINT32 At_QryUsbSwitchPara (VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucUsbStatus;
    VOS_UINT32                          ulResult;


    ucUsbStatus = USB_SWITCH_OFF;

    /* ͨ����� */
    /* Modified by L60609 for MUX��2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��2012-08-13,  End */
    {
        return AT_ERROR;
    }

    if (VOS_OK != DRV_USB_PHY_SWITCH_GET(&ucUsbStatus))
    {
        return AT_ERROR;
    }

    ulResult = (ucUsbStatus == USB_SWITCH_ON)?AT_USB_SWITCH_SET_VBUS_VALID:\
                                              AT_USB_SWITCH_SET_VBUS_INVALID;

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            (TAF_CHAR *)pgucAtSndCodeAddr,
                                            "+USBSWITCH: %X", ulResult);

    return AT_OK;
}


VOS_UINT32 AT_QryAntState(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usAntState;

    /* ������� */
    if(AT_CMD_OPT_SET_CMD_NO_PARA != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }


    usAntState = 0;

    ulRet = TAF_AGENT_GetAntState(ucIndex, &usAntState);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QryAntState: TAF_AGENT_GetAntState fail");

        return AT_ERROR;
    }

    /* AT��� */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    usAntState);
    return AT_OK;
}


VOS_UINT32 AT_QrySARReduction(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usUETestMode;
    AT_MODEM_MT_INFO_CTX_STRU          *pstMtInfoCtx = VOS_NULL_PTR;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT16                          usAntState;

    usUETestMode = VOS_FALSE;

    /* ��ȡNV���ж��Ƿ�Ϊ����ģʽ */
    ulRet = NV_ReadEx(MODEM_ID_0,
                      en_NV_Item_RF_SAR_BACKOFF_TESTMODE,
                      &usUETestMode,
                      sizeof(usUETestMode));

    if (NV_OK != ulRet)
    {
        AT_ERR_LOG("AT_QrySARReduction:Read NV fail");
        return AT_ERROR;
    }


    enModemId  = MODEM_ID_0;

    ulRet   = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QrySARReduction:Get modem id fail");
        return AT_ERROR;
    }

    pstMtInfoCtx = AT_GetModemMtInfoCtxAddrFromModemId(enModemId);

    usAntState   = 0;
    ulRet        = TAF_AGENT_GetAntState(ucIndex, &usAntState);
    if (VOS_OK != ulRet)
    {
        AT_ERR_LOG("AT_QrySARReduction:Get modem id fail");
        return AT_ERROR;
    }

    if ((AT_ANT_CONDUCTION_MODE == usAntState) && (VOS_TRUE != usUETestMode))
    {
        AT_ERR_LOG("AT_QrySARReduction: ant state wrong");
        return AT_ERROR;
    }

    /* AT��� */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstMtInfoCtx->usSarReduction);

    return AT_OK;
}

#if (FEATURE_ON==FEATURE_LTE)

VOS_UINT32  AT_QryRsrpCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_RSRP_CFG_STRU stRsrpCfg;
    VOS_UINT32 i =0;

    PS_MEM_SET(&stRsrpCfg, 0, sizeof(stRsrpCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (NV_OK != NVM_Read(EN_NV_ID_RSRP_CFG, &stRsrpCfg,sizeof(stRsrpCfg)))
        {
            vos_printf("read RSRP_CFG NV fail!\n");
            return AT_ERROR;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        "%s:",
                                                         g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

        for (i = 0 ;i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stRsrpCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr + gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stRsrpCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR;
    }


    return AT_OK;
}

VOS_UINT32  AT_QryRscpCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_RSCP_CFG_STRU stRscpCfg;
    VOS_UINT32 i =0;

    PS_MEM_SET(&stRscpCfg, 0, sizeof(stRscpCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (NV_OK != NVM_Read(EN_NV_ID_RSCP_CFG, &stRscpCfg,
                          sizeof(stRscpCfg)))
        {
            return AT_ERROR;
        }


        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                "%s:",
                                                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0; i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stRscpCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stRscpCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR;
    }


    return AT_OK;
}

VOS_UINT32  AT_QryEcioCfgPara ( VOS_UINT8 ucIndex )
{
    NVIM_ECIO_CFG_STRU stEcioCfg;
    VOS_UINT32 i =0;

    PS_MEM_SET(&stEcioCfg, 0, sizeof(stEcioCfg));

    if (g_enATE5RightFlag == AT_E5_RIGHT_FLAG_YES)
    {
        if (NV_OK != NVM_Read(EN_NV_ID_ECIO_CFG, &stEcioCfg,
                          sizeof(stEcioCfg)))
        {
            vos_printf("read ECIO_CFG NV fail!\n");
            return AT_ERROR;
        }

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                  (TAF_CHAR *)pgucAtSndCodeAddr,
                                                                  "%s:",
                                                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName);
        for (i = 0 ;i < 3; i++)
        {
            gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr,
                                                        (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                        "(%d)%d,",
                                                         i+1,
                                                         stEcioCfg.ssValue[i]);
        }

        gstAtSendData.usBufLen += (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr+ gstAtSendData.usBufLen,
                                                    "(4)%d",
                                                     stEcioCfg.ssValue[3]);
    }
    else
    {
        return AT_ERROR; /* ���Ȩ��δ�򿪣�����ERROR */
    }

    return AT_OK;
}

/* ɾ��AT_QryCellRoamPara */


VOS_UINT32 AT_QryPdprofmodPara(VOS_UINT8 ucIndex)
{
    return AT_OK;
}

VOS_UINT32 At_QrySfm(VOS_UINT8 ucIndex)
{
    VOS_UINT32  ulCustomVersion = 0;

#if (FEATURE_ON == MBB_FACTORY)
    /* 1 ��ʾ��Ƭ�汾 */
    ulCustomVersion = 1;
#else
    /* 0 ��ʾ��ʽ�汾 */
    ulCustomVersion = 0;

#endif

        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,(TAF_CHAR *)pgucAtSndCodeAddr,
            (TAF_CHAR *)pgucAtSndCodeAddr,"^SFM: %d", ulCustomVersion);

        return AT_OK;
}
#endif



VOS_UINT32 AT_QryPhoneSimlockInfoPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ͨ����� */
    /* Modified by L60609 for MUX��2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��2012-08-13,  End */
    {
        return AT_ERROR;
    }

    /* ���Ϳ����Ϣ��C��, ��ѯ����������Ϣ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PHONESIMLOCKINFO_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryPhoneSimlockInfoPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PHONESIMLOCKINFO_READ;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QrySimlockDataReadPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ͨ����� */
    /* Modified by L60609 for MUX��2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��2012-08-13,  End */
    {
        return AT_ERROR;
    }

    /* ���Ϳ����Ϣ��C��, ��ѯ����������Ϣ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_SIMLOCKDATAREAD_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QrySimlockDataReadPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_SIMLOCKDATAREAD_READ;
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryPhonePhynumPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ͨ����� */
    /* Modified by L60609 for MUX��2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��2012-08-13,  End */
    {
        return AT_ERROR;
    }

    /* ���Ϳ����Ϣ��C��, ��ѯ����������Ϣ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PHONEPHYNUM_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryPhonePhynumPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PHONEPHYNUM_READ;
    return AT_WAIT_ASYNC_RETURN;
}



VOS_UINT32 AT_QryPortCtrlTmpPara(VOS_UINT8 ucIndex)
{
    OM_HSIC_PORT_STATUS_ENUM_UINT32     enOmHsicPortStatus;

    /* ͨ����� */
    /* Modified by L60609 for MUX��2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��2012-08-13,  End */
    {
        return AT_ERROR;
    }

    /* ����A��OMģ���ṩ�Ľӿ�OM_GetHsicPortStatus()��ȡ�˿�״̬��ȫ�ֱ����������ظ�AP */
    enOmHsicPortStatus = OM_GetHsicPortStatus();

    if ( (OM_HSIC_PORT_STATUS_ON != enOmHsicPortStatus)
       && (OM_HSIC_PORT_STATUS_OFF != enOmHsicPortStatus) )
    {
        return AT_ERROR;
    }

    /* c64416 start in 2012-05-10 for LTE OM */
#if (FEATURE_ON==FEATURE_LTE)
    if(enOmHsicPortStatus != DMS_GetHsicPortStatus())
    {
        return AT_ERROR;
    }
#endif
    /* c64416 end in 2012-05-10 for LTE OM */

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    enOmHsicPortStatus);

    return AT_OK;
}
#ifdef CONFIG_NCM_MBIM_SUPPORT
/*****************************************************************************
 �� �� ��  : At_QryMbimMode
 ��������  : ^SETMODE��ѯ�������
 �������  : TAF_UINT8 ucIndex
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
*****************************************************************************/
TAF_UINT32 At_QryMbimMode(TAF_UINT8 ucIndex)
{
    VOS_UINT32 ulResult = 0;
    ulResult = DRV_USB_MBIM_GET_MODE();
    
    /* 0��NORMALģʽ(����������ģʽ) 1��DEBUGģʽ(������ģʽ)*/
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (TAF_CHAR *)pgucAtSndCodeAddr,
                                              (TAF_CHAR*)pgucAtSndCodeAddr,
                                              "%s: %d",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              ulResult);
    return AT_OK;
}
#endif

VOS_UINT32 AT_QryPortAttribSetPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ͨ����� */
    /* Modified by L60609 for MUX��2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��2012-08-13,  End */
    {
        return AT_ERROR;
    }

    /* ���Ϳ����Ϣ��C�ˣ���ѯ�˿���״̬ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      DRV_AGENT_PORTATTRIBSET_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryPortAttribSetPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PORTATTRIBSET_READ;
    return AT_WAIT_ASYNC_RETURN;
}

#if (VOS_WIN32 == VOS_OS_VER)

VOS_UINT32 At_QryTinTypeStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucTinType;

#if (FEATURE_ON == FEATURE_LTE)
    ucTinType = NAS_GetTinType();
#endif
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucTinType);
    return AT_OK;

}


VOS_UINT32 AT_QryPsRegisterContainDrxStub(VOS_UINT8 ucIndex)
{
    VOS_UINT8                           ucDrx;

    ucDrx = NAS_GetPsRegContainDrx();
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucDrx);
    return AT_OK;

}


#endif



VOS_UINT32 AT_QryCposrPara(VOS_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* ͨ����� */
    /* Modified by L60609 for MUX��2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��2012-08-13,  End */
    {
        return AT_ERROR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ��ӡ+CPOSR�����ϱ����Ƶ�ǰ״̬ */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstAgpsCtx->enCposrReport);
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    return AT_OK;
}


VOS_UINT32 AT_QryXcposrPara(VOS_UINT8 ucIndex)
{
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    AT_MODEM_AGPS_CTX_STRU             *pstAgpsCtx = VOS_NULL_PTR;

    /* ͨ����� */
    /* Modified by L60609 for MUX��2012-08-13,  Begin */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    /* Modified by L60609 for MUX��2012-08-13,  End */
    {
        return AT_ERROR;
    }

    pstAgpsCtx = AT_GetModemAgpsCtxAddrFromClientId(ucIndex);

    /* ��ӡ^XCPOSR�����ϱ����Ƶ�ǰ״̬ */
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    pstAgpsCtx->enXcposrReport);
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    return AT_OK;
}


VOS_UINT32 AT_QryCPsErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /* Modified by l60609 for DSDA Phase III, 2013-2-20, Begin */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_PS_GetPsCallErrCause(ucIndex));
    /* Modified by l60609 for DSDA Phase III, 2013-2-20, End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryCmutPara(VOS_UINT8 ucIndex)
{
    if (VOS_OK != APP_VC_GetMuteStatus(gastAtClientTab[ucIndex].usClientId, 0))
    {
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CMUT_READ;

    /* ������������״̬ */
    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryCCsErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          usLength;

    /* Modified by l60609 for DSDA Phase III, 2013-3-5, Begin */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      AT_GetCsCallErrCause(ucIndex));
    /* Modified by l60609 for DSDA Phase III, 2013-3-5, End */

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_QryCerssiPara(VOS_UINT8 ucIndex)
{
    TAF_MMA_CERSSI_INFO_QUERY_REQ_STRU  stCerssiInfoReq;
    VOS_UINT32                          ulResult;

#if  (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           enRatType;

    TAF_AGENT_SYS_MODE_STRU             stSysMode;

    /* ��C�˻�ȡucRatType��ucSysSubMode */
    ulResult = TAF_AGENT_GetSysMode(ucIndex, &stSysMode);
    if (VOS_OK != ulResult)
    {
        enRatType = TAF_PH_RAT_BUTT;
    }
    else
    {
        enRatType = stSysMode.enRatType;
    }

    PS_MEM_SET(&stCerssiInfoReq, 0, sizeof(stCerssiInfoReq));

    if (TAF_PH_RAT_LTE == enRatType)
    {

        return AtQryLCerssiPara(ucIndex);
    }
#endif
    /* ����Ϣ��MMA��ȡ��ǰ�ź�������Ϣ */
    ulResult =  MN_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                       gastAtClientTab[ucIndex].opId,
                                       TAF_MSG_MMA_CERSSI_INFO_QUERY_REQ,
                                       &stCerssiInfoReq,
                                       sizeof(TAF_MMA_CERSSI_INFO_QUERY_REQ_STRU),
                                       WUEPS_PID_MMA);

    /* ִ��������� */
    if (AT_SUCCESS == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CERSSI_READ;

        /* ������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}

#if(FEATURE_ON == FEATURE_LTE)


VOS_UINT32 At_QryCecellidPara(VOS_UINT8 ucIndex)
{
    /* ����L �ṩ�ӿ� */
    return At_QryCellIdPara(ucIndex);
}
#endif



VOS_UINT32 AT_QryCbgPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* AT ��VC ����ģʽ��ѯ������Ϣ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      APP_VC_MSG_FOREGROUND_QRY,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_WUEPS_PID_VC);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryCbgPara: send Msg fail.");
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CBG_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryAcInfoPara(VOS_UINT8 ucIndex)
{
    TAF_MMA_AC_INFO_QUERY_REQ_STRU      stAcInfoReq;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stAcInfoReq, 0, sizeof(stAcInfoReq));

    /* ����Ϣ��MMA��ȡ��ǰUE��λ����Ϣ */
    ulResult =  MN_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                       gastAtClientTab[ucIndex].opId,
                                       TAF_MSG_MMA_AC_INFO_QUERY_REQ,
                                       &stAcInfoReq,
                                       sizeof(TAF_MMA_AC_INFO_QUERY_REQ_STRU),
                                       WUEPS_PID_MMA);

    /* ִ��������� */
    if (AT_SUCCESS == ulResult)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ACINFO_READ;

        /* ������������״̬ */
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



VOS_UINT32 AT_QryCLteRoamAllowPara(VOS_UINT8 ucIndex)
{
    VOS_UINT8                                       ucLteRoamAllow;
    NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU    stNvimLteRoamAllowedFlg;
    VOS_UINT32                                      ulLength;

    ulLength = 0;


    /* �ֲ�������ʼ�� */
    ucLteRoamAllow          = VOS_FALSE;
    stNvimLteRoamAllowedFlg.ucLteRoamAllowedFlg = VOS_FALSE;

    NV_GetLength(en_NV_Item_Lte_Internation_Roam_Config, &ulLength);

    /* ��ȡNV, ��NV�ĽṹΪ NAS_MMC_NVIM_LTE_INTERNATIONAL_ROAM_CFG_STRU, ֻ��ȡ��1���ֽ� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_Lte_Internation_Roam_Config,
                         &stNvimLteRoamAllowedFlg,
                         ulLength))
    {
        AT_WARN_LOG("AT_QryCLteRoamAllowPara(): en_NV_Item_Lte_Internation_Roam_Config NV_ReadEx Error");
        return AT_ERROR;
    }


    /* �ݴ���, NV��ֵΪVOS_FALSEʱ������������, Ϊ����ֵʱ��Ϊ�������� */
    if (VOS_FALSE == stNvimLteRoamAllowedFlg.ucLteRoamAllowedFlg)
    {
        ucLteRoamAllow = VOS_FALSE;
    }
    else
    {
        ucLteRoamAllow = VOS_TRUE;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     ucLteRoamAllow);
    return AT_OK;
}



VOS_UINT32 At_QryMmPlmnInfoPara(VOS_UINT8 ucIndex)
{
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   TAF_MM_PLMN_INFO_QRY_PARA,
                                   TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MMPLMNINFO_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}


VOS_UINT32 At_QryPlmnPara(VOS_UINT8 ucIndex)
{
    if(AT_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   TAF_PH_PLMN_QRY_PARA,
                                   TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_PLMN_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 At_QryXlemaPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ������Ϣ */
    ulRst = MN_CALL_SendAppRequest(MN_CALL_APP_XLEMA_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   TAF_NULL_PTR);

    if (MN_ERR_NO_ERROR != ulRst)
    {
        AT_WARN_LOG("At_QryXlemaPara: MN_CALL_SendAppRequest fail.");
        return AT_ERROR;
    }

    /* ���ý���ֱ�ӷ���OK */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_XLEMA_QRY;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryBodySarOnPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    (VOS_CHAR *)pgucAtSndCodeAddr,
                                                    "%s: %d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     g_enAtBodySarState);
    return AT_OK;
}


VOS_UINT32 AT_FillBodySarWcdmaQryPara(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara,
    AT_BODYSARWCDMA_SET_PARA_STRU      *pstBodySarWcdmaPara)
{
    VOS_UINT8                           ucLoop1;
    VOS_UINT8                           ucLoop2;
    AT_NV_WG_RF_MAIN_BAND_STRU          stWGBand;
    VOS_UINT32                          ulTmpBand;

    PS_MEM_SET(&stWGBand, 0, sizeof(stWGBand));
    ulTmpBand       = 0;

    /* ��ȡWCDMA Band����ֵ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            en_NV_Item_WG_RF_MAIN_BAND,
                            &stWGBand,
                            sizeof(stWGBand)))
    {
        AT_ERR_LOG("AT_FillBodySarWcdmaQryPara: Read NV fail!");
        return VOS_ERR;
    }

    for (ucLoop1 = 0; ucLoop1 < pstBodySarPara->usWBandNum; ucLoop1++)
    {
        for (ucLoop2 = 0; ucLoop2 < pstBodySarWcdmaPara->ucParaNum; ucLoop2++)
        {
            if (pstBodySarPara->astWBandPara[ucLoop1].sPower == pstBodySarWcdmaPara->asPower[ucLoop2])
            {
                break;
            }
        }

        if (ucLoop2 == pstBodySarWcdmaPara->ucParaNum)
        {
            pstBodySarWcdmaPara->ucParaNum++;
            pstBodySarWcdmaPara->asPower[ucLoop2] =pstBodySarPara->astWBandPara[ucLoop1].sPower;
        }

        pstBodySarWcdmaPara->aulBand[ucLoop2]   |= 0x00000001 << (pstBodySarPara->astWBandPara[ucLoop1].enBand - 1);
        ulTmpBand                               |= pstBodySarWcdmaPara->aulBand[ucLoop2];
    }

    /* ʣ��δ���õ�Ƶ�η���Ĭ��ֵ */
    ulTmpBand = stWGBand.unWcdmaBand.ulBand & (~ulTmpBand);
    if (0 != ulTmpBand)
    {
        pstBodySarWcdmaPara->aulBand[pstBodySarWcdmaPara->ucParaNum] = ulTmpBand;
        pstBodySarWcdmaPara->asPower[pstBodySarWcdmaPara->ucParaNum] = AT_WCDMA_BAND_DEFAULT_POWER;
        pstBodySarWcdmaPara->ucParaNum++;
    }

    return VOS_OK;
}


VOS_UINT32 AT_QryBodySarWcdmaPara(VOS_UINT8 ucIndex)
{
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARWCDMA_SET_PARA_STRU       stBodySarWcdmaPara;
    VOS_UINT8                           ucLoop;
    VOS_UINT16                          usLength;

    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));
    PS_MEM_SET(&stBodySarWcdmaPara, 0, sizeof(stBodySarWcdmaPara));
    usLength        = 0;

    /* ��NV���ж�ȡBody SAR��������ֵ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            en_NV_Item_BODY_SAR_PARA,
                            &stBodySarPara,
                            sizeof(stBodySarPara)))
    {
        AT_ERR_LOG("AT_QryBodySarWcdmaPara: Read NV fail!");
        return AT_ERROR;
    }

    /* ��Body SAR�����ṹ�����^BODYSARWCDMA��������ṹ�� */
    if (VOS_OK != AT_FillBodySarWcdmaQryPara(&stBodySarPara, &stBodySarWcdmaPara))
    {
        AT_ERR_LOG("AT_QryBodySarWcdmaPara: AT_FillBodySarWcdmaQryPara fail!");
        return AT_ERROR;
    }

    /* ��ӡ������ */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ��ӡWCDMAƵ��Body SAR���� */
    if (1 == stBodySarWcdmaPara.ucParaNum)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarWcdmaPara.asPower[0],
                                           AT_RF_BAND_ANY);

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    for (ucLoop = 0; ucLoop < stBodySarWcdmaPara.ucParaNum; ucLoop++)
    {
        if (0 != ucLoop)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               ",");
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarWcdmaPara.asPower[ucLoop],
                                           stBodySarWcdmaPara.aulBand[ucLoop]);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_FillBodySarGsmDefaultPower(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara)
{
    VOS_UINT32                          ulGBandCapa;
    VOS_UINT32                          ulTmpBand;

    ulGBandCapa     = 0;
    ulTmpBand       = 0;

    /* ��ȡGSM Band����ֵ */
    if (VOS_OK != AT_GetGsmBandCapa(&ulGBandCapa))
    {
        AT_ERR_LOG("AT_FillBodySarGsmDefaultPower: AT_GetGsmBandCapa fail!");
        return VOS_ERR;
    }

    ulTmpBand = ulGBandCapa & (~pstBodySarPara->ulGBandMask);

    if (0 != (MTA_BODY_SAR_GBAND_GPRS_850_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_GPRS_850_MASK;
        pstBodySarPara->astGBandPara[MTA_GSM_850].sGPRSPower = AT_GSM_GPRS_850_DEFAULT_POWER;
    }

    if (0 != (MTA_BODY_SAR_GBAND_EDGE_850_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_EDGE_850_MASK;
        pstBodySarPara->astGBandPara[MTA_GSM_850].sEDGEPower = AT_GSM_EDGE_850_DEFAULT_POWER;
    }

    if (0 != (MTA_BODY_SAR_GBAND_GPRS_900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_GPRS_900_MASK;
        pstBodySarPara->astGBandPara[MTA_GSM_900].sGPRSPower = AT_GSM_GPRS_900_DEFAULT_POWER;
    }

    if (0 != (MTA_BODY_SAR_GBAND_EDGE_900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_EDGE_900_MASK;
        pstBodySarPara->astGBandPara[MTA_GSM_900].sEDGEPower = AT_GSM_EDGE_900_DEFAULT_POWER;
    }

    if (0 != (MTA_BODY_SAR_GBAND_GPRS_1800_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_GPRS_1800_MASK;
        pstBodySarPara->astGBandPara[MTA_GSM_1800].sGPRSPower = AT_GSM_GPRS_1800_DEFAULT_POWER;
    }

    if (0 != (MTA_BODY_SAR_GBAND_EDGE_1800_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_EDGE_1800_MASK;
        pstBodySarPara->astGBandPara[MTA_GSM_1800].sEDGEPower = AT_GSM_EDGE_1800_DEFAULT_POWER;
    }

    if (0 != (MTA_BODY_SAR_GBAND_GPRS_1900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_GPRS_1900_MASK;
        pstBodySarPara->astGBandPara[MTA_GSM_1900].sGPRSPower = AT_GSM_GPRS_1900_DEFAULT_POWER;
    }

    if (0 != (MTA_BODY_SAR_GBAND_EDGE_1900_MASK & ulTmpBand))
    {
        pstBodySarPara->ulGBandMask |= MTA_BODY_SAR_GBAND_EDGE_1900_MASK;
        pstBodySarPara->astGBandPara[MTA_GSM_1900].sEDGEPower = AT_GSM_EDGE_1900_DEFAULT_POWER;
    }

    return VOS_OK;
}


VOS_VOID AT_FillBodySarGsmByModulationMode(
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara,
    VOS_UINT8                           ucModulationOffset,
    AT_BODYSARGSM_SET_PARA_STRU        *pstBodySarGsmPara)
{
    VOS_UINT8                           ucLoop1;
    VOS_UINT8                           ucLoop2;

    for (ucLoop1 = MTA_GSM_850; ucLoop1 < MTA_GSM_BAND_BUTT; ucLoop1++)
    {
        for (ucLoop2 = 0; ucLoop2 < pstBodySarGsmPara->ucParaNum; ucLoop2++)
        {
            if (AT_GSM_GPRS_BAND_OFFSET == ucModulationOffset)
            {
                if (pstBodySarPara->astGBandPara[ucLoop1].sGPRSPower == pstBodySarGsmPara->asPower[ucLoop2])
                {
                    break;
                }
            }
            else
            {
                if (pstBodySarPara->astGBandPara[ucLoop1].sEDGEPower == pstBodySarGsmPara->asPower[ucLoop2])
                {
                    break;
                }
            }
        }

        if (ucLoop2 == pstBodySarGsmPara->ucParaNum)
        {
            pstBodySarGsmPara->ucParaNum++;
            if (AT_GSM_GPRS_BAND_OFFSET == ucModulationOffset)
            {
                pstBodySarGsmPara->asPower[ucLoop2] = pstBodySarPara->astGBandPara[ucLoop1].sGPRSPower;
            }
            else
            {
                pstBodySarGsmPara->asPower[ucLoop2] = pstBodySarPara->astGBandPara[ucLoop1].sEDGEPower;
            }
        }

        pstBodySarGsmPara->aulBand[ucLoop2]   |= 0x00000001 << (ucLoop1 + ucModulationOffset);
    }

    return;
}


VOS_UINT32 AT_QryBodySarGsmPara(VOS_UINT8 ucIndex)
{
    MTA_BODY_SAR_PARA_STRU              stBodySarPara;
    AT_BODYSARGSM_SET_PARA_STRU         stBodySarGsmPara;
    VOS_UINT8                           ucLoop;
    VOS_UINT16                          usLength;

    PS_MEM_SET(&stBodySarPara, 0, sizeof(stBodySarPara));
    PS_MEM_SET(&stBodySarGsmPara, 0, sizeof(stBodySarGsmPara));
    usLength        = 0;

    /* ��NV���ж�ȡBody SAR��������ֵ */
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            en_NV_Item_BODY_SAR_PARA,
                            &stBodySarPara,
                            sizeof(stBodySarPara)))
    {
        AT_ERR_LOG("AT_QryBodySarGsmPara: Read NV fail!");
        return AT_ERROR;
    }

    /* ���GSMƵ��Body SAR����Ĭ��ֵ */
    if (VOS_OK != AT_FillBodySarGsmDefaultPower(&stBodySarPara))
    {
        AT_ERR_LOG("AT_QryBodySarGsmPara: AT_FillBodySarGsmDefaultPower fail!");
        return AT_ERROR;
    }

    /* ��Body SAR�����ṹ�����^BODYSARGSM��������ṹ�� */
    /* GPRS���Ʒ�ʽ */
    AT_FillBodySarGsmByModulationMode(&stBodySarPara, AT_GSM_GPRS_BAND_OFFSET, &stBodySarGsmPara);

    /* EDGE���Ʒ�ʽ */
    AT_FillBodySarGsmByModulationMode(&stBodySarPara, AT_GSM_EDGE_BAND_OFFSET, &stBodySarGsmPara);

    /* ��ӡ������ */
    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: ",
                                       g_stParseContext[ucIndex].pstCmdElement->pszCmdName);

    /* ��ӡGSMƵ��Body SAR���� */
    if (1 == stBodySarGsmPara.ucParaNum)
    {
        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarGsmPara.asPower[0],
                                           AT_RF_BAND_ANY);

        gstAtSendData.usBufLen = usLength;

        return AT_OK;
    }

    for (ucLoop = 0; ucLoop < stBodySarGsmPara.ucParaNum; ucLoop++)
    {
        if (0 != ucLoop)
        {
            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                               ",");
        }

        usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "(%d,%08X)",
                                           stBodySarGsmPara.asPower[ucLoop],
                                           stBodySarGsmPara.aulBand[ucLoop]);
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 At_QryIMEIVerifyPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ������Ϣ ID_AT_MTA_IMEI_VERIFY_QRY_REQ �� MTA ���� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_MTA_IMEI_VERIFY_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_IMEI_VERIFY_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 AT_QryNCellMonitorPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ��MTA����^NCELLMONITOR��ѯ���� */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   0,
                                   ID_AT_MTA_NCELL_MONITOR_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        return AT_ERROR;
    }

    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_NCELL_MONITOR_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryUserSrvStatePara(VOS_UINT8 ucIndex)
{
    if(TAF_SUCCESS == Taf_ParaQuery(gastAtClientTab[ucIndex].usClientId,
                                   0, TAF_PH_USER_SRV_STATE_QRY_PARA, TAF_NULL_PTR))
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_USER_SRV_STATE_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



VOS_UINT32 AT_QryRefclkfreqPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* ͨ����� */
    if (VOS_FALSE == AT_IsApPort(ucIndex))
    {
        return AT_ERROR;
    }

    /* ���Ϳ����Ϣ��C��, ��ѯGPS�ο�ʱ��״̬ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_REFCLKFREQ_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("At_QryRefclkfreqPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_REFCLKFREQ_READ;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 At_QryHandleDect(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                          *pucSystemAppConfig;

    /* ��ȡNV���е�ǰ��Ʒ��̬ */
    pucSystemAppConfig = AT_GetSystemAppConfigAddr();

#ifndef DMT
    /* ��ANDROIDϵͳ��֧�� */
    if ( SYSTEM_APP_ANDROID != *pucSystemAppConfig)
    {
        return AT_CMD_NOT_SUPPORT;
    }
#endif

    /* ������� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /* ������Ϣ ID_AT_MTA_HANDLEDECT_QRY_REQ ��MTA���� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   ID_AT_MTA_HANDLEDECT_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_UEPS_PID_MTA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_HANDLEDECT_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }

}


VOS_UINT32 AT_QryLogCfgPara(VOS_UINT8 ucIndex)
{
    NV_SOCP_SDLOG_CFG_STRU              stSocpCfg;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usLength;

    PS_MEM_SET(&stSocpCfg, 0x00, sizeof(stSocpCfg));

    ulResult = NV_ReadEx(MODEM_ID_0, en_NV_ID_SOCP_SDLOG_CFG, (VOS_VOID *)(&stSocpCfg), sizeof(NV_SOCP_SDLOG_CFG_STRU));

    if (VOS_OK != ulResult)
    {
        return AT_ERROR;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d,%d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      stSocpCfg.ulSocpDelayWriteFlg,
                                      stSocpCfg.ulGuSocpLevel,
                                      stSocpCfg.ulLSocpLevel,
                                      stSocpCfg.ulTimeOutValue);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}

#if (FEATURE_ON == FEATURE_IMS)

VOS_UINT32 AT_QryCiregPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ������Ϣ */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_IMSA_CIREG_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   PS_PID_IMSA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_QryCiregPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ��ѯ��������ͨ�� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIREG_QRY;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryCirepPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ������Ϣ */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   ID_AT_IMSA_CIREP_QRY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   PS_PID_IMSA);

    if (TAF_SUCCESS != ulRst)
    {
        AT_WARN_LOG("AT_QryCirepPara: AT_FillAndSndAppReqMsg fail.");
        return AT_ERROR;
    }

    /* ��ѯ��������ͨ�� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CIREP_QRY;
    return AT_WAIT_ASYNC_RETURN;

}


VOS_UINT32 AT_QryClccPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡ��ǰ����ͨ����Ϣ */
    ulRet = MN_CALL_GetCallInfos(gastAtClientTab[ucIndex].usClientId,
                                 gastAtClientTab[ucIndex].opId,
                                 0);
    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryClccPara: MN_CALL_GetCallInfos fail.");
        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCC_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryClccEconfInfo(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRet;

    /* ����Ϣ��C�˻�ȡ��ǰ����ͨ����Ϣ */
    ulRet = MN_CALL_SendAppRequest(TAF_CALL_APP_GET_ECONF_CALLED_INFO_REQ,
                                   gastAtClientTab[ucIndex].usClientId,
                                   gastAtClientTab[ucIndex].opId,
                                   0,
                                   VOS_NULL_PTR);
    if (VOS_OK != ulRet)
    {
        AT_WARN_LOG("AT_QryClccEconfInfo: MN_CALL_SendAppRequest fail.");

        return AT_ERROR;
    }

    /* ����ATģ��ʵ���״̬Ϊ�ȴ��첽���� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_CLCCECONF_QRY;

    return AT_WAIT_ASYNC_RETURN;
}


VOS_UINT32 AT_QryEconfErrPara(VOS_UINT8 ucIndex)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usLength;
    AT_MODEM_CC_CTX_STRU               *pstCcCtx     = VOS_NULL_PTR;
    AT_ECONF_INFO_STRU                 *pstEconfInfo = VOS_NULL_PTR;
    VOS_UINT8                           aucAsciiNum[MN_CALL_MAX_CALLED_ASCII_NUM_LEN + 1];
    VOS_UINT8                           ucNumOfCalls;
    VOS_UINT8                           ucErrNum;

    ucErrNum     = 0;
    usLength     = 0;
    pstCcCtx     = AT_GetModemCcCtxAddrFromClientId(ucIndex);
    pstEconfInfo = &(pstCcCtx->stEconfInfo);
    ucNumOfCalls = pstEconfInfo->ucNumOfCalls;
    PS_MEM_SET(aucAsciiNum, 0, sizeof(aucAsciiNum));

    for (i = 0; ((i < ucNumOfCalls) && (i < TAF_CALL_MAX_ECONF_CALLED_NUM)); i++)
    {
        /* ��ѯ����ԭ��ֵ */
        if ((0 != pstEconfInfo->astCallInfo[i].stCallNumber.ucNumLen)
         && (TAF_CS_CAUSE_SUCCESS != pstEconfInfo->astCallInfo[i].enCause))
        {
            /* <CR><LF> */
            if (0 != ucErrNum)
            {
                usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr,
                                                   (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                                   "%s",
                                                   gaucAtCrLf);
            }

            AT_BcdNumberToAscii(pstEconfInfo->astCallInfo[i].stCallNumber.aucBcdNum,
                                pstEconfInfo->astCallInfo[i].stCallNumber.ucNumLen,
                                (VOS_CHAR *)aucAsciiNum);

            usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucAtSndCodeAddr,
                                               (VOS_CHAR *)pgucAtSndCodeAddr + usLength,
                                               "%s: \"%s\",%d,%d",
                                               g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                               aucAsciiNum,
                                               (pstEconfInfo->astCallInfo[i].stCallNumber.enNumType | AT_NUMBER_TYPE_EXT),
                                               pstEconfInfo->astCallInfo[i].enCause);

            ucErrNum++;
        }
    }

    gstAtSendData.usBufLen = usLength;

    return AT_OK;

}

#endif


VOS_UINT32 AT_QryUserCfgOPlmnPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ������Ϣ ID_AT_MTA_HANDLEDECT_QRY_REQ ��MTA���� */
    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   TAF_MSG_MMA_EOPLMN_QUERY_REQ,
                                   VOS_NULL_PTR,
                                   0,
                                   I0_WUEPS_PID_MMA);

    if (AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_EOPLMN_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}

#if (FEATURE_ON == FEATURE_AT_HSUART)

VOS_UINT32 AT_QryIprPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT16                          usLength;

    /* ��ʼ�� */
    pstUartCtx = AT_GetUartCtxAddr();
    usLength   = 0;

    /* ͨ����� */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return AT_OK;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %u",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstUartCtx->stPhyConfig.enBaudRate);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryIcfPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT16                          usLength;

    /* ��ʼ�� */
    pstUartCtx = AT_GetUartCtxAddr();
    usLength   = 0;

    /* ͨ����� */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return AT_OK;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstUartCtx->stPhyConfig.stFrame.enFormat,
                                      pstUartCtx->stPhyConfig.stFrame.enParity);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}


VOS_UINT32 AT_QryIfcPara(VOS_UINT8 ucIndex)
{
    AT_UART_CTX_STRU                   *pstUartCtx = VOS_NULL_PTR;
    VOS_UINT16                          usLength;

    /* ��ʼ�� */
    pstUartCtx = AT_GetUartCtxAddr();
    usLength   = 0;

    /* ͨ����� */
    if (VOS_TRUE != AT_CheckHsUartUser(ucIndex))
    {
        return AT_OK;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                      (VOS_CHAR *)pgucAtSndCodeAddr,
                                     (VOS_CHAR *)pgucAtSndCodeAddr,
                                      "%s: %d,%d",
                                      g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                      pstUartCtx->stFlowCtrl.enDceByDte,
                                      pstUartCtx->stFlowCtrl.enDteByDce);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}
#endif


VOS_UINT32 AT_QryAntSwitchPara(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulRst;

    /* ������� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    ulRst = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                   At_GetOpId(),
                                   DRV_AGENT_ANTSWITCH_QRY_REQ,
                                   VOS_NULL,
                                   0,
                                   I0_WUEPS_PID_DRV_AGENT);

    if (TAF_SUCCESS == ulRst)
    {
        gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_ANTSWITCH_QRY;
        return AT_WAIT_ASYNC_RETURN;
    }
    else
    {
        return AT_ERROR;
    }
}



VOS_UINT32 AT_QryModemStatusPara(VOS_UINT8 ucIndex)
{
    return AT_OK;
}


VOS_UINT32 AT_QryRATCombinePara(VOS_UINT8 ucIndex)
{
    TAF_NV_LC_CTRL_PARA_STRU            stNVData;
    VOS_UINT16                          usLength;
    VOS_UINT8                           usRatMode;

    PS_MEM_SET(&stNVData, 0x0, sizeof(stNVData));

    if (NV_OK != NV_ReadEx(MODEM_ID_0, en_NV_Item_LC_Ctrl_PARA, &stNVData, sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        return AT_ERROR;
    }

    if (VOS_TRUE != stNVData.ucLCEnableFlg)
    {
        return AT_CME_OPERATION_NOT_ALLOWED;
    }

    if (TAF_NVIM_LC_RAT_COMBINED_CL == stNVData.enRatCombined)
    {
        usRatMode = 0;
    }
    else if (TAF_NVIM_LC_RAT_COMBINED_GUL == stNVData.enRatCombined)
    {
        usRatMode = 1;
    }
    else
    {
        return AT_ERROR;
    }

    usLength = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                  (VOS_CHAR *)pgucAtSndCodeAddr,
                                 (VOS_CHAR *)pgucAtSndCodeAddr,
                                  "%s: %d",
                                  g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                  usRatMode);

    gstAtSendData.usBufLen = usLength;

    return AT_OK;
}



VOS_UINT32 AT_QryMipiClkValue(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult;

    /* AT ��MTA ���Ͳ�ѯ������Ϣ */
    ulResult = AT_FillAndSndAppReqMsg(gastAtClientTab[ucIndex].usClientId,
                                      gastAtClientTab[ucIndex].opId,
                                      ID_AT_MTA_MIPICLK_QRY_REQ,
                                      VOS_NULL_PTR,
                                      0,
                                      I0_UEPS_PID_MTA);

    if (TAF_SUCCESS != ulResult)
    {
        AT_WARN_LOG("AT_QryMipiClkValue: send Msg fail.");
        return AT_ERROR;
    }

    /* ���õ�ǰ�������� */
    gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_MIPI_CLK_QRY;

    return AT_WAIT_ASYNC_RETURN;

}


#if (FEATURE_ON == MBB_COMMON)

VOS_UINT32 At_QryHgmrPara(VOS_UINT8 ucIndex)
{
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                 "%s:%d,%d,%d",
                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                 BASE_SOFTWARE_VERSION,
                                 PLATFORM_SOFTWARE_VERSION,
                                 PRODUCT_SOFTWARE_VERSION);
    return AT_OK;
}

#endif

#if (FEATURE_ON == MBB_COMMON)

VOS_UINT32 At_QryExtChargePara(VOS_UINT8 ucIndex)
{
    VOS_INT8 testRes;
    
    /* ������� */
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    
    testRes = chg_extchg_mmi_test();
    
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                 "%s:%d",
                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                 testRes);
    return AT_OK;
}


VOS_UINT32  AT_QryWebUserPara(VOS_UINT8 ucIndex )
{
    VOS_CHAR     aucWebUsermp[AT_WEBUI_SITE_NV_LEN_MAX + 1];

    /* ������� */
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    /* ���������� */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return AT_ERROR;
    }

    (void)VOS_MemSet((void *)aucWebUsermp, 0, sizeof(aucWebUsermp));
    
    if (NV_OK != NV_Read(NV_ID_WEB_USER_NAME, aucWebUsermp, AT_WIFI_PIN_NV_LEN_MAX))
    {
        AT_WARN_LOG("AT_QryWebUserPara ERROR: NVIM Read NV_ID_WEB_USER_NAME falied!");
        return AT_ERROR;
    }
    
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                 "%s:%s%s%s",
                                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                 gaucAtQuotation,
                                                 aucWebUsermp,
                                                 gaucAtQuotation);

    return AT_OK;
}


VOS_UINT32  AT_QryWiFiPinPara(VOS_UINT8 ucIndex )
{
   VOS_CHAR     aucWebPinTmp[AT_WIFI_PIN_NV_LEN_MAX + 1];

   /* ������� */
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    
    /* ���������� */
    if (VOS_TRUE == g_bAtDataLocked)
    {
        return AT_ERROR;
    }
        
    (void)VOS_MemSet((void *)aucWebPinTmp, 0, sizeof(aucWebPinTmp));

    if (NV_OK != NV_Read(NV_ID_WPS_PIN, aucWebPinTmp, AT_WIFI_PIN_NV_LEN_MAX))
    {
        AT_WARN_LOG("AT_QryWebsite ERROR: NVIM Read en_NV_Item_Web_Site falied!");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                 "%s:%s%s%s",
                                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                 gaucAtQuotation,
                                                 aucWebPinTmp,
                                                 gaucAtQuotation);
    
    return AT_OK;
}


VOS_UINT32  AT_QryWebSitePara(VOS_UINT8 ucIndex )
{
   VOS_CHAR     aucWebSiteTmp[AT_WEBUI_SITE_NV_LEN_MAX + 1];

   /* ������� */
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    (void)VOS_MemSet((void *)aucWebSiteTmp, 0, sizeof(aucWebSiteTmp));

    if (NV_OK != NV_Read(NV_ID_WEB_SITE, aucWebSiteTmp, AT_WEBUI_SITE_NV_LEN_MAX))
    {
        AT_WARN_LOG("AT_QryWebsite ERROR: NVIM Read en_NV_Item_Web_Site falied!");
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                 "%s:%s%s%s",
                                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                 gaucAtQuotation,
                                                 aucWebSiteTmp,
                                                 gaucAtQuotation);
                    
    return AT_OK;
}


#define PORT_LOCKED    (2)
#define PORT_UNLOCKED    (1)
#define PORT_NO_NEED_LOCK    (0)
VOS_UINT32 At_QryPortLockPara(VOS_UINT8 ucIndex)
{
#if defined(BSP_CONFIG_BOARD_CPE)
    CPE_TELNET_SWITCH_NVIM_STRU aucPortLockTmp;
    VOS_CHAR portstate = 0; 
    /* ������� */
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }

    (void)VOS_MemSet((void *)(&aucPortLockTmp), 0, sizeof(aucPortLockTmp));

    if (NV_OK != NV_Read(NV_TELNET_SWITCH_I, (BSP_VOID *)(&aucPortLockTmp), (BSP_U32)sizeof(aucPortLockTmp)))
    {
        AT_WARN_LOG("At_QryPortLockPara ERROR: NVIM Read NV_TELNET_SWITCH_I falied!");
        return AT_ERROR;
    }

    /*��ATĿǰֻ֧��LANAT��������������������*/
    if (0 == aucPortLockTmp.nv_telnet_switch)
    {
        portstate = PORT_LOCKED;
    }
    else
    {
        portstate = PORT_UNLOCKED;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                 (TAF_CHAR *)pgucAtSndCodeAddr,
                                                 "%s:LANAT,%d",
                                                 g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                 portstate);
                    
    return AT_OK;
#else
    return AT_ERROR;
#endif
}


VOS_UINT32 At_QryTbatDataPara(VOS_UINT8 ucIndex)
{
    AT_TBAT_BATTERY_ADC_INFO_STRU stAdcInfo;
    VOS_UINT16 usLen = 0;

    /*����״̬���ͼ��*/
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /*�����ж�:����Ʒ��֧�ֵ�أ���ֱ�ӷ���ERROR*/
    if (BSP_MODULE_UNSUPPORT == DRV_GET_BATTERY_SUPPORT() )
    {
        return AT_ERROR;
    }
    
    (void)VOS_MemSet((void *)&stAdcInfo, 0, sizeof(stAdcInfo));
    
    if (CHG_OK != chg_tbat_read(CHG_AT_BATTERY_CHECK, &stAdcInfo))          
    {              
        return AT_ERROR;         
    }
    
    usLen = (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   "%s:%d,%d%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   VOLT_CALC_NUM_MAX,
                                   CURRENT_CALC_NUM_MAX,
                                   gaucAtCrLf);
    
    usLen += (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                   "%s:%d,%d,%d%s",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   AT_TBATDATA_VOLTAGE,
                                   AT_TBATDATA_INDEX0,
                                   stAdcInfo.usMinAdc,
                                   gaucAtCrLf);
    
    usLen += (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                   "%s:%d,%d,%d",
                                   g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                   AT_TBATDATA_VOLTAGE,
                                   AT_TBATDATA_INDEX1,
                                   stAdcInfo.usMaxAdc);
 
    gstAtSendData.usBufLen = usLen;

    return AT_OK;
}


VOS_UINT32 AT_QryWiFiPlatformPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_WIFI)

    WLAN_AT_WIPLATFORM_TYPE   ucWifiPlatform;

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    ucWifiPlatform = WlanATGetWifiPlatform();
    
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiPlatform);
#endif
    return AT_OK;
}

#if 0
#if ( FEATURE_ON == MBB_COMMON )
/*****************************************************************************
 �� �� ��      : At_QryCsosPara
 ��������  : AT^CSOS��ѯ�������
 �������  : VOS_UINT8 ucIndex  �û�����
 �������  : ��
 �� �� ֵ      : VOS_UINT32         AT������
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 At_QryCsosPara(VOS_UINT8 ucIndex)
{
    SALES_AGENT_RECORD_STRU              CsosRealPara;

    PS_MEM_SET( &CsosRealPara, 0, sizeof(CsosRealPara) );

    CsosRealPara.ucCollected = gastAtParaList[0].ulParaValue;

    /* ��ѯNV :en_NV_Item_CSOS_VALUE*/
    if (NV_OK != NV_ReadEx(MODEM_ID_0,
                            en_NV_Item_CSOS_VALUE,
                            &(CsosRealPara),
                            sizeof(CsosRealPara)))
    {
        AT_ERR_LOG("en_NV_Item_CSOS_VALUE: Read NV fail!");
        return AT_ERROR;
    }
    else
    {
        gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                     g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                     CsosRealPara.ucCollected);
        return AT_OK;
    }
}
#endif
#endif

VOS_UINT32 AT_QryAntennaPara(VOS_UINT8 ucIndex)
{
#if (FEATURE_ON == MBB_ANTENNA)
    int Antenna =0;
    VOS_UINT16 usLen = 0;
    int i = 0;
    
    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }
    
    for(i = 0; i < SUPPORT_RF_BAND_FOR_ANTE; i++)
    {
        if(g_SetTseLrfParValue == ante_switch_array[i].rf_band_for_ante)
        {
            Antenna = anten_switch_get(ante_switch_array[i].ant_type);
            if(-1 ==  Antenna)
            {
                return AT_ERROR;
            }

            
            usLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
            (TAF_CHAR *)pgucAtSndCodeAddr,
            (TAF_CHAR *)pgucAtSndCodeAddr,
            "%s:%d\n",
            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
            Antenna);
            gstAtSendData.usBufLen = usLen;
            
            return AT_OK;
        }
    }

     return AT_ERROR;
#else
    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    0);
    return AT_OK;
#endif
}

#endif



#if (FEATURE_ON == MBB_FEATURE_CAT_MODULE_SET)

VOS_UINT32 At_QryLteCat(VOS_UINT8 ucIndex)
{
    LRRC_NV_UE_EUTRA_CAP_STRU  stUECapability={0};
    VOS_UINT32 ulResult = 0;

    ulResult = NVM_Read(EN_NV_ID_UE_CAPABILITY, &stUECapability,
                        sizeof(LRRC_NV_UE_EUTRA_CAP_STRU));
    if (NV_OK != ulResult)
    {
        vos_printf("At_QryLteCat:Read NVD22C fail!!");
        return AT_ERROR;
    }
    ulResult = stUECapability.enUeCatg + 1;   //NV��0��ʼ���ȼ���1��ʼ������+1
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                              (TAF_CHAR *)pgucAtSndCodeAddr,
                                              (TAF_CHAR*)pgucAtSndCodeAddr,
                                              "%s: %d",
                                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                              ulResult);
    return AT_OK;
}
#endif

#if (FEATURE_ON == MBB_COMMON)

VOS_UINT32 AT_QryWifiCalPara(VOS_UINT8 ucIndex)
{
    VOS_INT32 ucWifiCal = 0;

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ȡWIFI У׼ģʽ��Ϣ */
    ucWifiCal = WlanATGetWifiCal();

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiCal);
    return AT_OK;
}


VOS_UINT32 AT_QryWifiCalDataPara(VOS_UINT8 ucIndex)
{
    WLAN_AT_WICALDATA_STRU ucWifiCalDataTemp;
    (void)VOS_MemSet((void *)(&ucWifiCalDataTemp), 0, sizeof(ucWifiCalDataTemp));

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ȡWIFI У׼������Ϣ */
    if (AT_SUCCESS != WlanATGetWifiCalData(&ucWifiCalDataTemp))
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d,%d,%d,%d,%d,%d,%s%s%s",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiCalDataTemp.type,ucWifiCalDataTemp.group,
                                                    ucWifiCalDataTemp.mode,ucWifiCalDataTemp.band,
                                                    ucWifiCalDataTemp.bandwidth,ucWifiCalDataTemp.freq,
                                                    gaucAtQuotation,ucWifiCalDataTemp.data,gaucAtQuotation);
    return AT_OK;
}


VOS_UINT32 AT_QryWifiCalTempPara(VOS_UINT8 ucIndex)
{
    WLAN_AT_WICALTEMP_STRU ucWifiCalTempTemp;
    (void)VOS_MemSet((void *)(&ucWifiCalTempTemp), 0, sizeof(ucWifiCalTempTemp));

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ȡWIFI У׼������Ϣ */
    if (AT_SUCCESS != WlanATGetWifiCalTemp(&ucWifiCalTempTemp))
    {
        return AT_ERROR;
    }
    /*���չ淶����WIFIУ׼�¶�*/
    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d%s%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    WICALTEMPNUM,
                                                    gaucAtCrLf,
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiCalTempTemp.index,ucWifiCalTempTemp.value);
    return AT_OK;
}


VOS_UINT32 AT_QryWifiCalFreqPara(VOS_UINT8 ucIndex)
{
    WLAN_AT_WICALFREQ_STRU ucWifiCalFreqTemp;
    (void)VOS_MemSet((void *)(&ucWifiCalFreqTemp), 0, sizeof(ucWifiCalFreqTemp));

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ȡWIFI У׼������Ϣ */
    if (AT_SUCCESS != WlanATGetWifiCalFreq(&ucWifiCalFreqTemp))
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiCalFreqTemp.type,ucWifiCalFreqTemp.value);
    return AT_OK;

}


VOS_UINT32 AT_QryWifiCalPowPara(VOS_UINT8 ucIndex)
{
    WLAN_AT_WICALPOW_STRU ucWifiCalPowTemp;
    (void)VOS_MemSet((void *)(&ucWifiCalPowTemp), 0, sizeof(ucWifiCalPowTemp));

    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_DEVICE_OTHER_ERROR;
    }

    /* WIFI�Ƿ�֧�� */
    if (BSP_MODULE_UNSUPPORT == DRV_GET_WIFI_SUPPORT() )
    {
        return AT_ERROR;
    }

    /* ��ȡWIFI У׼������Ϣ */
    if (AT_SUCCESS != WlanATGetWifiCalPOW(&ucWifiCalPowTemp))
    {
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d,%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ucWifiCalPowTemp.type,ucWifiCalPowTemp.value);
    return AT_OK;

}


VOS_UINT32 AT_QryNavTypePara(VOS_UINT8 ucIndex)
{
    return AT_ERROR;
}


VOS_UINT32 AT_QryNavFreqPara(VOS_UINT8 ucIndex)
{
    return AT_ERROR;
}



VOS_UINT32 AT_QryNavRxPara(VOS_UINT8 ucIndex)
{
    return AT_ERROR;
}
#define TEMPERATURE_MAGIC         0x5A5A5A5A
#define TEMPINIT                  (-25)


VOS_UINT32 AT_QryTempInfo(VOS_UINT8 ucIndex)
{

    VOS_UINT16 usLength = 0;
    VOS_INT16    bat_Temp = TEMPINIT;
    VOS_INT16    sim_Temp = TEMPINIT;
    VOS_INT16    PA0_Temp = TEMPINIT;
    DRV_HKADC_DATA_AREA *p_area = (DRV_HKADC_DATA_AREA *)SHM_MEM_TEMPERATURE_ADDR;
    VOS_INT16 *phy_tbl = p_area->phy_tbl;
    VOS_INT16 index_chan = 0;
    VOS_INT16 sim_chan = -1;
    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }
 
    if((TEMPERATURE_MAGIC != p_area->magic_start) || (TEMPERATURE_MAGIC != p_area->magic_end))
    {
        (VOS_VOID)vos_printf("AT_QryTempInfo ERROR:tem mem is writed by others.\n");
        return AT_ERROR;
    }
    /* ���ݶ��ձ��ѯSIM���¶ȶ�Ӧ��CHAN */
    for(index_chan = 0; index_chan < HKADC_CHAN_MAX; index_chan++)
    {
        if(phy_tbl[index_chan] == HKADC_TEMP_SIM_CARD)
        {
            sim_chan = index_chan;
            break;
        }
    }

    if(-1 == sim_chan)
    {
        return AT_ERROR;
    }
 
    bat_Temp = p_area->chan_out[CHG_BATT_TEMP_CHAN].temp_l * 10;
    sim_Temp = p_area->chan_out[sim_chan].temp_l * 10;
    if(BSP_MODULE_SUPPORT == DRV_GET_BATTERY_SUPPORT())
    {
         usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:%s:%d%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,"BAT",bat_Temp, gaucAtCrLf);
    }
    else
    {
         usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,"BAT", gaucAtCrLf);
    }
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:%s:%d%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,"SIM",sim_Temp, gaucAtCrLf);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,"SD", gaucAtCrLf);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,"WPA", gaucAtCrLf);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,"GPA", gaucAtCrLf);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:%s%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,"CPA", gaucAtCrLf);
    usLength += (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN, (VOS_CHAR *)pgucAtSndCodeAddr, (VOS_CHAR *)(pgucAtSndCodeAddr + usLength),
                                           "%s:%s",
                                           g_stParseContext[ucIndex].pstCmdElement->pszCmdName,"LPA");
   
    gstAtSendData.usBufLen = usLength;
    return AT_OK;
}
/*****************************************************************************
 �� �� ��  : AT_QryFtyResetPara
 ��������  : �ָ��������ò���AT^FTYRESET��ѯ�����
 �������  : ucIndex - �û�����
 �������  : ��
 �� �� ֵ  : AT_OK - �ɹ�
             AT_DEVICE_OTHER_ERROR�� AT_DATA_UNLOCK_ERROR - ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :

*****************************************************************************/
VOS_UINT32 AT_QryFtyResetPara(VOS_UINT8 ucIndex)
{
    RESTORE_STATE_TYPE restore_state = RESTORE_FAIL;
    NODE_STATE_TYPE node_state = APP_START_INVALID;
    VOS_UINT32 ulRst = AT_OK;
    /* ���������ж� */
    if (AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_ERROR;
    }

    /*��ȡ�ڵ�״̬*/
    node_state = drv_get_ftyreset_node_state();
    if ( SET_DONE == at_get_ftyreset_set_flag() )
    {
        restore_state = RESTORE_PROCESSING;

        /*����ָ������������*/
        if (APP_RESTORE_OK == node_state)
        {
            restore_state = RESTORE_OK;
        }

        /*���Ӧ������ok���ϱ��ִ�^NORSTFACT�ִ�*/
        if (APP_START_READY == node_state)
        {
            /*���Ӧ������ok���ϱ��ִ�^NORSTFACT�ִ�*/
            if (APP_START_READY == node_state)
            {
                if (REVERT_FAIL == g_revert_flag)
                {
                    ulRst = NVM_RevertFNV();
                    if (ulRst == AT_SUCCESS)
                    {
                        g_revert_flag = REVERT_SUCCESS;
                    }
                    else
                    {
                        return AT_ERROR;
                    }
                }
                AT_PhSendRestoreFactParmNoReset();
            }
        }
    }
    else
    {
        restore_state = RESTORE_FAIL;
    }

    gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    restore_state);
    return AT_OK;
}
#endif/*END FOR MBB_COMMON*/
#if (FEATURE_ON == MBB_HWTEST)  


VOS_UINT32 AT_QryHwTest(VOS_UINT8 ucIndex)
{
    int i = 0;
    VOS_UINT16 usLen = 0;
	usLen = (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   "%s:%d,%s\n",
                                   "^HWTEST", 0, hw_test_option[0]);
    
    usLen += (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                   "%s:%d,%s\n",
                                   "^HWTEST", 1, hw_test_option[1]);
    
    usLen += (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                   "%s:%d,%s\n",
                                   "^HWTEST", 2, hw_test_option[2]);
    usLen += (TAF_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                   (TAF_CHAR *)pgucAtSndCodeAddr,
                                   (TAF_CHAR *)pgucAtSndCodeAddr + usLen,
                                   "%s:%d,%s\n",
                                   "^HWTEST", 3, hw_test_option[3]);
 
    gstAtSendData.usBufLen = usLen;

    return AT_OK;
}
#endif
#if(FEATURE_ON == MBB_OPERATOR_VDF)


VOS_UINT32 At_QrySkuType(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult = NV_READ_UNABLE;
    TAF_UINT8                             SKU[2];
    vos_printf("query sku OK\n");
    PS_MEM_SET(SKU, 0, sizeof(SKU));
    ulResult = NV_Read(NV_ITEM_SKU_TYPE, SKU, sizeof(SKU));
    if ( NV_OK != ulResult )
    {
        vos_printf("At_QrySkuType:Read NV failed!");
        return AT_DEVICE_OTHER_ERROR;
    }
   gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    SKU[0]);
   return AT_OK;
}


VOS_UINT32 At_QryAccountType(VOS_UINT8 ucIndex)
{
    VOS_UINT32                          ulResult = NV_READ_UNABLE;
    TAF_UINT8                             ACCOUNT[2]; /*ACCOUNT������Ԫ�أ�����һ��Ϊ����*/
    vos_printf("query account OK\n");
    PS_MEM_SET(ACCOUNT, 0, sizeof(ACCOUNT));
    ulResult = NV_Read(NV_ITEM_ACCOUNT_TYPE, ACCOUNT, sizeof(ACCOUNT));
    if ( NV_OK != ulResult )
    {
        AT_WARN_LOG("At_QryAccountType:Read NV failed!");
        return AT_DEVICE_OTHER_ERROR;
    }
   gstAtSendData.usBufLen = (TAF_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    (TAF_CHAR *)pgucAtSndCodeAddr,
                                                    "%s:%d",
                                                    g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                                    ACCOUNT[0]);
    return AT_OK;
}

#endif
#if(FEATURE_ON == MBB_CHG_BQ27510)
VOS_UINT32  At_QryBatSn(TAF_UINT8 ucIndex )
{
    nv_huawei_coul_firmware_update_info coul_firmware_update_info;
    (void)VOS_MemSet((void *)(&coul_firmware_update_info), 0,\
                     sizeof(nv_huawei_coul_firmware_update_info));
    /* ������� */
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    //��ȡNV��Ϣ������Ϣ��ֵ��AT���
    /* ��ȡNV�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, NV_HUAWEI_BATTERY_INFO_I,\
                           &coul_firmware_update_info,\
                           sizeof(nv_huawei_coul_firmware_update_info)))
    {
        AT_WARN_LOG("At_QryBatSn: Read NV_HUAWEI_BATTERY_INFO_I failed");
        return AT_ERROR;
    }
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                              (VOS_CHAR *)pgucAtSndCodeAddr,
                              (VOS_CHAR *)pgucAtSndCodeAddr,
                              "%s:%s",
                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                              coul_firmware_update_info.battery_sn);
    
    return AT_OK;
}

VOS_UINT32  At_QryFwUp(TAF_UINT8 ucIndex)
{
    nv_huawei_coul_firmware_update_info coul_firmware_update_info;
    uint16 update_flag = 0;
    unsigned char coul_firmware_mask[FIREMWARE_UPDATA_RET_LEN] = {0x00};
    unsigned char coul_firmware_flag[FIREMWARE_UPDATA_RET_LEN] = {0x00};
    (void)VOS_MemSet((void *)(&coul_firmware_update_info), 0,\
                     sizeof(nv_huawei_coul_firmware_update_info));
    /* ������� */
    if(AT_CMD_OPT_READ_CMD != g_stATParseCmd.ucCmdOptType)
    {
        return AT_CME_INCORRECT_PARAMETERS;
    }
    //��ȡNV��Ϣ������Ϣ��ֵ��AT���
    /* ��ȡNV�� */
    if (NV_OK != NV_ReadEx(MODEM_ID_0, NV_HUAWEI_BATTERY_INFO_I,\
                           &coul_firmware_update_info,\
                           sizeof(nv_huawei_coul_firmware_update_info)))
    {
        AT_WARN_LOG("At_QryFwUp: Read NV_HUAWEI_BATTERY_INFO_I failed");
        return AT_ERROR;
    }
    snprintf(coul_firmware_mask,FIREMWARE_UPDATA_RET_LEN,\
        "%04x",firmware_updata_mask);
    snprintf(coul_firmware_flag,FIREMWARE_UPDATA_RET_LEN,"%04x",\
        coul_firmware_update_info.coul_firmware_update_status);
    if(coul_firmware_update_info.coul_firmware_update_status)
    {
        AT_WARN_LOG("At_QryFwUp: the coul have update!!!");
        update_flag = 1;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                              (VOS_CHAR *)pgucAtSndCodeAddr,
                              (VOS_CHAR *)pgucAtSndCodeAddr,
                              "%s:%d,%s,%s",
                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                              update_flag,
                              coul_firmware_flag,
                              coul_firmware_mask);
    return AT_OK;
}
#endif
#if(FEATURE_ON == MBB_CHG_BQ27510)
VOS_UINT32 At_QryCoulcurrentType(VOS_UINT8 ucIndex)
{
    VOS_INT32                          coul_current = 0;
    coul_current = hisi_battery_current();
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                              (VOS_CHAR *)pgucAtSndCodeAddr,
                              (VOS_CHAR *)pgucAtSndCodeAddr,
                              "%s:%d",
                              g_stParseContext[ucIndex].pstCmdElement->pszCmdName, 
                              coul_current);

    return AT_OK; 
}
#endif

#if(FEATURE_ON == MBB_USB_FTEN_SWITCH)

VOS_UINT32 At_QryUsbSel(VOS_UINT8 ucIndex)
{

    NV_FTEN_USB_SWITCH_SEL_INFO cur_nv_info = {0};

    if (NV_OK != NV_ReadEx(MODEM_ID_0, NV_FTEN_USB_SWITCH_SEL, \
                           &cur_nv_info, \
                           sizeof(NV_FTEN_USB_SWITCH_SEL_INFO)))
    {
        AT_WARN_LOG("At_QryGpsselPara: Read At_QryUsbSel failed");
        return AT_ERROR;
    }
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                             (VOS_CHAR*)pgucAtSndCodeAddr,
                             (VOS_CHAR*)pgucAtSndCodeAddr,
                             "%s:%d",
                             g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                             cur_nv_info.usb_sel_flag);
    return AT_OK;
}
#endif



#if (FEATURE_ON == MBB_FEATURE_VSIM_HUK)
VOS_UINT32 AT_QryDieId(VOS_UINT8 ucIndex)
{
    //do nothing
    return AT_OK;
}
#endif /*FEATURE_ON == MBB_FEATURE_VSIM_HUK*/
VOS_VOID Show_Time(MODEM_ID_ENUM_UINT16 enModemId)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

    vos_printf("\r\nTime:\r\n");
    vos_printf("ucIeFlg: %d\r\n",pstNetCtx->stTimeInfo.ucIeFlg);
    vos_printf("cLocalTimeZone: %d\r\n",pstNetCtx->stTimeInfo.cLocalTimeZone);
    vos_printf("ucDST: %d\r\n",pstNetCtx->stTimeInfo.ucDST);
    vos_printf("ucLSAID: %d\r\n",pstNetCtx->stTimeInfo.ucLSAID);
    vos_printf("cTimeZone: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.cTimeZone);
    vos_printf("ucYear: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucYear);
    vos_printf("ucMonth: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMonth);
    vos_printf("ucDay: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucDay);
    vos_printf("ucHour: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucHour);
    vos_printf("ucMinute: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMinute);
    vos_printf("ucSecond: %d\r\n",pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucSecond);

    return;
}

#if (FEATURE_OFF == MBB_WPG_COMMON)

VOS_UINT32 AT_QryCclkPara(VOS_UINT8 ucIndex)
{
    AT_MODEM_NET_CTX_STRU              *pstNetCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_INT8                            cTimeZone;

    enModemId = MODEM_ID_0;
    cTimeZone = AT_INVALID_TZ_VALUE;

    ulRslt = AT_GetModemIdFromClient(ucIndex, &enModemId);

    if (VOS_OK != ulRslt)
    {
        AT_ERR_LOG("AT_QryCclkPara: Get modem id fail.");
        return AT_ERROR;
    }

    pstNetCtx = AT_GetModemNetCtxAddrFromModemId(enModemId);

    /*ʱ����ʾ��ʽ: +cclk: "yy/mm/dd,hh:mm:ss(+/-)zz" */
    if (NAS_MM_INFO_IE_UTLTZ == (pstNetCtx->stTimeInfo.ucIeFlg & NAS_MM_INFO_IE_UTLTZ))
    {
        /* ���ʱ�� */
        cTimeZone   = pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.cTimeZone;

        /* ���Ѿ���� Local time zone,��ʱ���޸�Ϊ Local time zone */
        if (NAS_MM_INFO_IE_LTZ == (pstNetCtx->stTimeInfo.ucIeFlg & NAS_MM_INFO_IE_LTZ))
        {
            cTimeZone   = pstNetCtx->stTimeInfo.cLocalTimeZone;
        }

        gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf(AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            (VOS_CHAR *)pgucAtSndCodeAddr,
                                            "%s: \"%02d/%02d/%02d,%02d:%02d:%2d%+d\"",
                                            g_stParseContext[ucIndex].pstCmdElement->pszCmdName,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucYear,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMonth,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucDay,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucHour,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucMinute,
                                            pstNetCtx->stTimeInfo.stUniversalTimeandLocalTimeZone.ucSecond,
                                            cTimeZone);
        return AT_OK;
    }

    return AT_CME_NO_NETWORK_SERVICE;
}
#endif


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

