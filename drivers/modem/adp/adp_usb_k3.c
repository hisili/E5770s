/*lint -save -e570 -e537 -e713*/

#include "drv_usb.h"
#include "bsp_usb.h"
#include "usb_vendor.h"
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/module.h>

static unsigned g_usb_enum_done_cur = 0;
static unsigned g_usb_enum_dis_cur = 0;

static struct notifier_block gs_adp_usb_nb;
static struct notifier_block *gs_adp_usb_nb_ptr = NULL;
static int g_usb_enum_done_notify_complete = 0;
static int g_usb_disable_notify_complete = 0;
static USB_CTX_S g_usb_ctx = {{0},{0},{0}};


/*****************************************************************************
 �� �� ��  : BSP_USB_SetPid
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
int BSP_USB_SetPid(unsigned char u2diagValue)
{
    return OK;
}

/*****************************************************************************
��������   BSP_USB_PortTypeQuery
��������:  ��ѯ��ǰ���豸ö�ٵĶ˿���ֵ̬
��������� stDynamicPidType  �˿���̬
��������� stDynamicPidType  �˿���̬
����ֵ��   0:    ��ѯ�ɹ�
           ��������ѯʧ��
*****************************************************************************/
unsigned int BSP_USB_PortTypeQuery(DRV_DYNAMIC_PID_TYPE_STRU *pstDynamicPidType)
{
    return OK;
}

/*****************************************************************************
��������   BSP_USB_PortTypeValidCheck
��������:  �ṩ���ϲ��ѯ�豸�˿���̬���úϷ��Խӿ�
           1���˿�Ϊ��֧�����ͣ�2������PCUI�ڣ�3�����ظ��˿ڣ�4���˵���������16��
           5����һ���豸��ΪMASS��
��������� pucPortType  �˿���̬����
           ulPortNum    �˿���̬����
����ֵ��   0:    �˿���̬�Ϸ�
           �������˿���̬�Ƿ�
*****************************************************************************/
unsigned int BSP_USB_PortTypeValidCheck(unsigned char *pucPortType, unsigned long ulPortNum)
{
    return OK;
}

/*****************************************************************************
��������   BSP_USB_GetAvailabePortType
��������:  �ṩ���ϲ��ѯ��ǰ�豸֧�ֶ˿���̬�б�ӿ�
��������� ulPortMax    Э��ջ֧�����˿���̬����
�������:  pucPortType  ֧�ֵĶ˿���̬�б�
           pulPortNum   ֧�ֵĶ˿���̬����
����ֵ��   0:    ��ȡ�˿���̬�б�ɹ�
           ��������ȡ�˿���̬�б�ʧ��
*****************************************************************************/
unsigned int BSP_USB_GetAvailabePortType(unsigned char *pucPortType,
                            unsigned long *pulPortNum, unsigned long ulPortMax)
{
    return OK;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_ATProcessRewind2Cmd
 ��������  : rewind2 CMD ����
 �������  : pData������
 �������  : ��
 �� �� ֵ  : false(0):����ʧ��
             tool(1):����ɹ�
*****************************************************************************/
int BSP_USB_ATProcessRewind2Cmd(unsigned char *pData)
{
    return OK;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_GetDiagModeValue
 ��������  : ����豸����
 �������  : ��
 �������  : ucDialmode:  0 - ʹ��Modem����; 1 - ʹ��NDIS����; 2 - Modem��NDIS����
              ucCdcSpec:   0 - Modem/NDIS������CDC�淶; 1 - Modem����CDC�淶;
                           2 - NDIS����CDC�淶;         3 - Modem/NDIS������CDC�淶
 �� �� ֵ  : VOS_OK/VOS_ERR
*****************************************************************************/
BSP_S32 BSP_USB_GetDiagModeValue(unsigned char *pucDialmode,
                             unsigned char *pucCdcSpec)
{
    return OK;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_GetPortMode
 ��������  : ��ȡ�˿���̬ģʽ�����ضԽ����󣬴�׮��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
unsigned char BSP_USB_GetPortMode(char*PsBuffer, unsigned long*Length )
{
    return OK;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_GetU2diagDefaultValue
 ��������  : ��ö˿�Ĭ��u2diagֵ
 �������  : ��
 �������  : ��
 ����ֵ��   u2diagֵ

*****************************************************************************/
BSP_U32 BSP_USB_GetU2diagDefaultValue(void)
{
    return 0;
}


void MNTN_ERRLOG_REG_FUNC(MNTN_ERRLOGREGFUN pRegFunc)
{
    return ;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_UdiagValueCheck
 ��������  : ���ӿ����ڼ��NV����USB��ֵ̬�ĺϷ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0��OK
             -1��ERROR
*****************************************************************************/
int BSP_USB_UdiagValueCheck(unsigned long DiagValue)
{
    return OK;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_GetLinuxSysType
 ��������  : ���ӿ����ڼ��PC���Ƿ�ΪLinux���Թ��Linux��̨���β���ʧ�ܵ�����.
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0��Linux��
            -1����Linux��
*****************************************************************************/
int BSP_USB_GetLinuxSysType(void)
{
    return -1;
}

/********************************************************
����˵���� ���ص�ǰ�豸�б���֧��(sel=1)���߲�֧��(sel=0)PCSC���豸��ֵ̬
��������:
���������sel
          0: ͨ������dev_type���ص�ǰ����PCSC���豸��ֵ̬
          1��ͨ������dev_type���ص�ǰ��PCSC���豸��ֵ̬
���������dev_type д����Ҫ���豸��ֵ̬�����û����д��ֵ��
          NV�д洢���豸��ֵ̬
���������pulDevType ��ulCurDevType��Ӧ���豸��ֵ̬�����û�з���ֵ1��
����ֵ��
          0����ѯ����Ӧ���豸��ֵ̬��
          1��û�в�ѯ����Ӧ���豸��ֵ̬��
********************************************************/
int BSP_USB_PcscInfoSet(unsigned int  ulSel, unsigned int  ulCurDevType, unsigned int *pulDevType)
{
    return 0;
}

/********************************************************
����˵����Э��ջע��USBʹ��֪ͨ�ص�����
��������:
���������pFunc: USBʹ�ܻص�����ָ��
�����������
�����������
����ֵ  ��0���ɹ�
          1��ʧ��
********************************************************/
unsigned int BSP_USB_RegUdiEnableCB(USB_UDI_ENABLE_CB_T pFunc)
{
    if (g_usb_enum_done_cur >= USB_ENABLE_CB_MAX)
    {
        printk("BSP_USB_RegUdiEnableCB error:0x%x", (unsigned)pFunc);
        return ERROR;
    }

    g_usb_ctx.udi_enable_cb[g_usb_enum_done_cur] = pFunc;
    g_usb_enum_done_cur++;

	if (g_usb_enum_done_notify_complete)
    {
    	if (pFunc)
        	pFunc();
    }

    return OK;
}

/********************************************************
����˵����Э��ջע��USBȥʹ��֪ͨ�ص�����
��������:
���������pFunc: USBȥʹ�ܻص�����ָ��
�����������
�����������
����ֵ  ��0���ɹ�
          1��ʧ��
********************************************************/
unsigned int BSP_USB_RegUdiDisableCB(USB_UDI_DISABLE_CB_T pFunc)
{
    if (g_usb_enum_dis_cur >= USB_ENABLE_CB_MAX)
    {
        printk("BSP_USB_RegUdiDisableCB error:0x%x", (unsigned)pFunc);
        return ERROR;
    }

    g_usb_ctx.udi_disable_cb[g_usb_enum_dis_cur] = pFunc;
    g_usb_enum_dis_cur++;

    return OK;
}

unsigned int BSP_USB_RegIpsTraceCB(USB_IPS_MNTN_TRACE_CB_T pFunc)
{
    if (!pFunc)
    {
        return 1;
    }

    return 0;
}

/********************************************************
����˵����Э��ջע��HSICʹ��֪ͨ�ص�����
��������:
���������pFunc: HSICʹ�ܻص�����ָ��
�����������
�����������
����ֵ  ��0���ɹ�
          1��ʧ��
********************************************************/
unsigned int BSP_HSIC_RegUdiEnableCB(HSIC_UDI_ENABLE_CB_T pFunc)
{
    return OK;
}

/********************************************************
����˵����Э��ջע��HSICȥʹ��֪ͨ�ص�����
��������:
���������pFunc: HSICȥʹ�ܻص�����ָ��
�����������
�����������
����ֵ��  0���ɹ�
          1��ʧ��
********************************************************/
unsigned int BSP_HSIC_RegUdiDisableCB(HSIC_UDI_DISABLE_CB_T pFunc)
{
    return OK;
}

unsigned long USB_ETH_DrvSetDeviceAssembleParam(
    unsigned long ulEthTxMinNum,
    unsigned long ulEthTxTimeout,
    unsigned long ulEthRxMinNum,
    unsigned long ulEthRxTimeout)
{
    return 0;
}

unsigned long USB_ETH_DrvSetHostAssembleParam(unsigned long ulHostOutTimeout)
{
    return 0;
}

int USB_otg_switch_get(UINT8 *pvalue)
{
    return 0;
}

int USB_otg_switch_set(UINT8 value)
{
    return 0;
}

int USB_otg_switch_signal_set(UINT8 group,UINT8 pin, UINT8 value )
{
    return 0;
}

/********************************************************
����˵����Э��ջ��ѯHSICö��״̬
��������:
�����������
�����������
�����������
����ֵ��  1��ö�����
          0��ö��δ���
********************************************************/
unsigned int BSP_GetHsicEnumStatus(void)
{
    return OK;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_HSIC_SupportNcm
 ��������  : ���ӿ����ڲ�ѯHSIC�Ƿ�֧��NCM
 �������  : NA
 �������  : NA
 �� �� ֵ  : 1-- ֧��NCM
             0--��֧��NCM
*****************************************************************************/
int BSP_USB_HSIC_SupportNcm(void)
{
    return 0;
}

/********************************************************
����˵����TTF��ѯԤ����SKB Num
��������:
�����������
�����������
�����������
����ֵ��  SKB Num
********************************************************/
BSP_U32 BSP_AcmPremallocSkbNum(void)
{
    return 0;
}

/********************************************************
��������   BSP_UDI_FindVcom
���������� ��ѯ��ǰ�豸��̬��ָ����UDI���⴮�ڶ˿��Ƿ����
��������� UDI_DEVICE_IDö��ֵ��������ѯ�����⴮�ڶ˿�ID
��������� ��
����ֵ��
           0����ǰ�豸��̬��֧�ֲ�ѯ�����⴮�ڶ˿ڣ�
           1����ǰ�豸��̬֧�ֲ�ѯ�����⴮�ڶ˿ڡ�
ע����� ��
********************************************************/
int BSP_UDI_FindVcom(UDI_DEVICE_ID enVCOM)
{
    return 0;
}

/*****************************************************************************
* �� �� ��  : DRV_USB_RegEnumDoneForMsp
* ��������  : �ṩ��MSPע��USBö����ɺ�֪ͨ����
* �������  : pFunc:ö����ɻص�����ָ��
* �������  : ��
* �� �� ֵ  : 0: �ɹ�ע��,�ȴ�ö�����֪ͨ;
*             1: USB�Ѿ�ö�����,����ֱ�ӳ�ʼ��USB����;
*             -1: ʧ��, ��USB��̬,û��USB����
*****************************************************************************/
signed int BSP_USB_RegEnumDoneForMsp(void *pFunc)
{
    /* we suggest to use the new interface for usb insert/remove */
    return BSP_USB_RegUdiEnableCB(pFunc);
}

/*****************************************************************************
* �� �� ��  : BSP_USB_RegEnumDoneForPs
* ��������  : �ṩ��PSע��USBö����ɺ�֪ͨ����
* �������  : pFunc:ö����ɻص�����ָ��
* �������  : ��
* �� �� ֵ  : 0: �ɹ�ע��,�ȴ�ö�����֪ͨ;
*             1: USB�Ѿ�ö�����,����ֱ�ӳ�ʼ��USB����;
*             -1: ʧ��,��USB��̬,û��USB����
*****************************************************************************/
signed int BSP_USB_RegEnumDoneForPs(void *pFunc)
{
    /* we suggest to use the new interface for usb insert/remove */
    return BSP_USB_RegUdiEnableCB(pFunc);
}

/*****************************************************************************
 �� �� ��  : BSP_USB_RndisAppEventDispatch
 ��������  : ���ӿ�����֪ͨAPP ��Ӧ��USB����¼�
 �������  : usb�¼�
 �� �� ֵ  : ��
*****************************************************************************/
void BSP_USB_RndisAppEventDispatch(unsigned ulStatus)
{
    return ;
}

/************************************************************************
 * FUNCTION
 *       rndis_app_event_dispatch
 * DESCRIPTION
 *       ���翨�汾����Ӧ�ý��в��Ż�Ͽ���������
 * INPUTS
 *       ���в��Ż�Ͽ�����ָʾ
 * OUTPUTS
 *       NONE
 *************************************************************************/
VOID rndis_app_event_dispatch(unsigned int ulStatus)
{
    return ;
}

/*****************************************************************************
 �� �� ��  : BSP_USB_NASSwitchGatewayRegExtFunc
 ��������  : ���ӿ�����NASע���л�����֪ͨ�ص�����
 �������  : �ص��ӿڡ�
 �������  : �ޡ�
 �� �� ֵ  : 0���ɹ�
             ��:ʧ��
*****************************************************************************/
int BSP_USB_NASSwitchGatewayRegFunc(USB_NET_DEV_SWITCH_GATEWAY switchGwMode)
{
    return OK;
}

/*****************************************************************************
 �� �� ��  : bsp_usb_register_enablecb
 ��������  : ���ӿ�����Cshell֪ͨUSB����ص�����
 �������  : �ص��ӿڡ�
 �������  : �ޡ�
 �� �� ֵ  : 0���ɹ�
             ��:ʧ��
*****************************************************************************/
int bsp_usb_register_enablecb(USB_UDI_ENABLE_CB_T pFunc)
{
    /* we suggest to use the new interface for usb insert/remove */
    return BSP_USB_RegUdiEnableCB(pFunc);
}

/*****************************************************************************
 �� �� ��  : bsp_usb_register_disablecb
 ��������  : ���ӿ�����Cshell֪ͨUSB�γ��ص�����
 �������  : �ص��ӿڡ�
 �������  : �ޡ�
 �� �� ֵ  : 0���ɹ�
             ��:ʧ��
*****************************************************************************/
int bsp_usb_register_disablecb(USB_UDI_DISABLE_CB_T pFunc)
{
    /* we suggest to use the new interface for usb insert/remove */
    return BSP_USB_RegUdiDisableCB(pFunc);
}

unsigned long USB_ETH_DrvSetRxFlowCtrl(unsigned long ulParam1, unsigned long ulParam2)
{
    return 0;
}

unsigned long USB_ETH_DrvClearRxFlowCtrl(unsigned long ulParam1, unsigned long ulParam2)
{
    return 0;
}

/************************************************************************
 * FUNCTION
 *       rndis_app_event_dispatch
 * DESCRIPTION
 *       ���翨�汾����Ӧ�ý��в��Ż�Ͽ���������
 * INPUTS
 *       ���в��Ż�Ͽ�����ָʾ
 * OUTPUTS
 *       NONE
 *************************************************************************/
VOID DRV_AT_SETAPPDAILMODE(unsigned int ulStatus)
{

}

int l2_notify_register(FUNC_USB_LP_NOTIFY pUSBLPFunc)
{
    return 0;
}

static int gs_usb_adp_notifier_cb(struct notifier_block *nb,
            unsigned long event, void *priv)
{
    int loop;

    switch (event) {

    case USB_BALONG_DEVICE_INSERT:
        g_usb_disable_notify_complete = 0;
        break;
    case USB_BALONG_ENUM_DONE:
        /* enum done */
        g_usb_disable_notify_complete = 0;
        if (!g_usb_enum_done_notify_complete) {
            for(loop = 0; loop < USB_ENUM_DONE_CB_BOTTEM; loop++)
            {
                if(g_usb_ctx.enum_done_cbs[loop])
                    g_usb_ctx.enum_done_cbs[loop]();
            }

            for(loop = 0; loop < USB_ENABLE_CB_MAX; loop++)
            {
                if(g_usb_ctx.udi_enable_cb[loop])
                    g_usb_ctx.udi_enable_cb[loop]();
            }
        }
        g_usb_enum_done_notify_complete = 1;
        break;
    case USB_BALONG_DEVICE_DISABLE:
    case USB_BALONG_DEVICE_REMOVE:
        /* notify other cb */
        g_usb_enum_done_notify_complete = 0;
        if (!g_usb_disable_notify_complete) {
            for(loop = 0; loop < USB_ENABLE_CB_MAX; loop++)
            {
                if(g_usb_ctx.udi_disable_cb[loop])
                    g_usb_ctx.udi_disable_cb[loop]();
            }
            g_usb_disable_notify_complete = 1;
        }
        break;
    default:
        break;
    }
    return 0;
}


int __init adp_usb_init(void)
{
    /* we just regist once, and don't unregist any more */
    if (!gs_adp_usb_nb_ptr) {
        gs_adp_usb_nb_ptr = &gs_adp_usb_nb;
        gs_adp_usb_nb.priority = USB_NOTIF_PRIO_ADP;
        gs_adp_usb_nb.notifier_call = gs_usb_adp_notifier_cb;
        bsp_usb_register_notify(gs_adp_usb_nb_ptr);
    }
    return 0;
}
module_init(adp_usb_init);

/*lint -restore*/

