

#ifndef __DRV_PMU_H__
#define __DRV_PMU_H__

#include "drv_comm.h"
#include "drv_dpm.h"

/*ͨ��ģ�鹩��� CONSUMER��idö��*/
typedef enum EM_MODEM_CONSUMER_ID_E
{
    MODEM_PA0,
    MODEM_RFIC0_ANALOG0,
    MODEM_RFIC0_ANALOG1,
    MODEM_FEM0,
    MODEM_PA_VBIAS0,
    MODEM_PA1,
    MODEM_RFIC1_ANALOG0,
    MODEM_RFIC1_ANALOG1,
    MODEM_FEM1,
    MODEM_PA_VBIAS1,
    MODEM_CONSUMER_ID_BUTT
}EM_MODEM_CONSUMER_ID;

/*PA��̬��ѹö��*/
typedef enum EM_MODEM_PA_DYNAMIC_VOLTAGE_ID_E
{
    MODEM_PA_LOW_POWER_VOLTAGE,
}EM_MODEM_PA_DYNAMIC_VOLTAGE_ID;


/*************************PMU BEGIN***********************************/

/*****************************************************************************
 �� �� ��  : DRV_GET_PMU_STATE
 ��������  : ��ȡPMUģ�鿪����ʽ�����״̬����ص����������λ״̬��
 �������  : �ޡ�
 �������  : Pmu_State :������ʽ�����״̬����ص����������λ״̬��
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע��������ýӿڽ���PS��PC������ʹ�ã�Ŀǰû��Ӧ�ã��ݱ�����
*****************************************************************************/
static INLINE unsigned int DRV_GET_PMU_STATE(void*  Pmu_State)
{
	return 0;
}

/*****************************************************************************
 �� �� ��  : BSP_PMU_UsbEndRegActionFunc
 ��������  : ���ӿ���USB����/�γ��ص�ע�ắ����
 �������  : srcFunc��ע���USB�����γ���������ʱ�Ļص�����ָ�롣
             actionIndex������ָʾ��
                          0������srcFunc��ע���USB���붯���Ļص�������
                          1������srcFunc��ע���USB�γ������Ļص�������

 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
 ע������  �����ô˽ӿڣ�����Ҫִ�еĺ���ָ�봫�룬����USB�����γ�ʱ������Ҫִ�еĺ�����
*****************************************************************************/
extern int BSP_PMU_UsbEndRegActionFunc(pFUNCPTR srcFunc, unsigned char actionIndex);
#define DRV_USB_ENDREGACTION_FUNC(srcFunc,actionIndex) \
                BSP_PMU_UsbEndRegActionFunc(srcFunc,actionIndex)


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
unsigned int BSP_USB_PortTypeValidCheck(unsigned char *pucPortType, unsigned long ulPortNum);
#define DRV_USB_PORT_TYPE_VALID_CHECK(pucPortType, ulPortNum)  \
                    BSP_USB_PortTypeValidCheck(pucPortType, ulPortNum)

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
                            unsigned long *pulPortNum, unsigned long ulPortMax);
#define DRV_USB_GET_AVAILABLE_PORT_TYPE(pucPortType, pulPortNum, ulPortMax)  \
                BSP_USB_GetAvailabePortType(pucPortType, pulPortNum, ulPortMax)


/************************************
�� �� ��  : BSP_PMU_AptEnable
��������  : ʹ��PMU��APT����
�������  : ��
�������  : ��������״̬
�� �� ֵ  : BSP_OK�����óɹ�
		����ֵ������ʧ��
**************************************/
static INLINE BSP_S32 BSP_PMU_AptEnable(BSP_VOID)
{
	return 0;
}
#define DRV_PMU_APT_ENABLE()    BSP_PMU_AptEnable()

/************************************
�� �� ��  : BSP_PMU_AptDisable
��������  : ȥʹ��PMU��APT����
�������  : ��
�������  : ��������״̬
�� �� ֵ  : BSP_OK�����óɹ�
		����ֵ������ʧ��
**************************************/
static INLINE BSP_S32 BSP_PMU_AptDisable(BSP_VOID)
{
	return 0;
}
#define DRV_PMU_APT_DISABLE()    BSP_PMU_AptDisable()

/************************************
�� �� ��  : BSP_PMU_AptIsEnable
��������  : ��ѯPMU��APT�����Ƿ�ʹ��
�������  : ��
�������  : ��������״̬
�� �� ֵ  : BSP_TURE��ʹ��APT
		    BSP_FALSE,δʹ��APT
**************************************/
static INLINE BSP_BOOL  BSP_PMU_AptIsEnable(BSP_VOID)
{
	return 1;
}
#define DRV_PMU_APT_ISENABLE()    BSP_PMU_AptIsEnable()

/*****************************************************************************
 �� �� ��  : BSP_MNTN_PmuSelfCheck
 ��������  : PMU�Լ졣
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
static INLINE int BSP_MNTN_PmuSelfCheck(void)
{
	return 0;
}
#define DRV_PMU_SELFCHECK()    BSP_MNTN_PmuSelfCheck()


/*for dsda*/
typedef enum
{
    RF_ID0 = 0,
    RF_ID1 = 1,
    RF_ID_BUTTOM
}RF_ID;

/*****************************************************************************
 �� �� ��  : BSP_GUSYS_RFLdoDown
 ��������  : ���ӿ�ʵ��WCDMA��GSM RF LDO�µ硣
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
static INLINE void DRV_RF_LDODOWN(RF_ID rfId)
{
    return;     /* ��׮ */
}

#define WCDMA_MODE      0
#define GSM_MODE        1
#define LTE_MODE        2
#define TDS_MODE        3
/*****************************************************************************
 �� �� ��  : BSP_GUSYS_ModeSwitchs
 ��������  : ���ӿ�ʵ��WCDMA/GSMϵͳģʽ�л���
 �������  : uiSysMode��0���л���WCDMAģʽ��1���л���GSMģʽ��
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
static INLINE int  DRV_SYSMODE_SWITCH (unsigned int uiSysMode)
{
    if(WCDMA_MODE == uiSysMode)
    {
        return OK;
    }
    else if(GSM_MODE == uiSysMode)
    {
        return OK;
    }
    else if(LTE_MODE == uiSysMode || TDS_MODE == uiSysMode)
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

/*************************PMU END*************************************/
/*****************************************************************************
 �� �� ��  : DRV_PASTAR_EXC_CHECK
 ��������  : ͨ��ģ����PASTAR�Ƿ����쳣�ӿ�
 �������  : modem_id       ����
 �������  : ��
 �� �� ֵ  : 0          û���쳣
             -1       �����쳣
*****************************************************************************/
extern BSP_S32 DRV_PASTAR_EXC_CHECK(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : DRV_MODEM_VOLTAGE_SET
 ��������  : ͨ��ģ�����õ�ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ���õĵ�ѹֵ����
 �������  : ��
 �� �� ֵ  : 0          ���óɹ�
             -1       ����ʧ��
*****************************************************************************/
extern BSP_S32 DRV_MODEM_VOLTAGE_SET( EM_MODEM_CONSUMER_ID consumer_id, BSP_U32 voltage_mv );

/*****************************************************************************
 �� �� ��  : DRV_MODEM_VOLTAGE_GET
 ��������  : ͨ��ģ���ȡ��ѹ�ӿ�
 �������  : consumer_id     �û�id
             voltage_mv      ��õĵ�ѹֵ����
 �������  : ��
 �� �� ֵ  : 0          ��ȡ�ɹ�
             -1       ��ȡʧ��
*****************************************************************************/
extern BSP_S32 DRV_MODEM_VOLTAGE_GET( EM_MODEM_CONSUMER_ID consumer_id, BSP_U32 *voltage_mv );

/*****************************************************************************
 �� �� ��  : DRV_MODEM_VOLTAGE_LIST
 ��������  : ͨ��ģ���ȡ��ѹ���÷�Χ�ӿ�
 �������  : consumer_id     �û�id
             list            ��ѹ��Χ����
             size            �����С
 �������  : ��
 �� �� ֵ  : 0          ��ȡ�ɹ�
             -1       ��ȡʧ��
*****************************************************************************/
extern BSP_S32 DRV_MODEM_VOLTAGE_LIST(EM_MODEM_CONSUMER_ID consumer_id,BSP_U16 **list, BSP_U32 *size);

/*****************************************************************************
 �� �� ��  : DRV_MODEM_APT_ENABLE
 ��������  : ͨ��ģ��ʹ��APT�ӿ�
 �������  : modem_id       ����
             mode_id        ͨ��ģʽ
 �������  : ��
 �� �� ֵ  : 0         ���óɹ�
             -1      ����ʧ��
*****************************************************************************/
extern BSP_S32 DRV_MODEM_APT_ENABLE(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 �� �� ��  : DRV_MODEM_APT_DISABLE
 ��������  : ͨ��ģ��ȥʹ��APT�ӿ�
 �������  : modem_id       ����
             mode_id        ͨ��ģʽ
 �������  : ��
 �� �� ֵ  : 0         ���óɹ�
             -1      ����ʧ��
*****************************************************************************/
extern BSP_S32 DRV_MODEM_APT_DISABLE(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 �� �� ��  : DRV_MODEM_APT_STATUS_GET
 ��������  : ͨ��ģ���ȡ��ǰAPT״̬�ӿ�
 �������  : modem_id       ����
             mode_id        ͨ��ģʽ
 �������  : ��
 �� �� ֵ  : PWRCTRL_COMM_ON     APTʹ��
             PWRCTRL_COMM_OFF    APTδʹ��
             -1           ��ȡʧ��
*****************************************************************************/
extern BSP_S32 DRV_MODEM_APT_STATUS_GET(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);

/*****************************************************************************
 �� �� ��  : DRV_MODEM_MODE_CONFIG
 ��������  : ͨ��ģ������Gģ��Wģ�ӿ�
 �������  : modem_id       ����
             mode_id        ͨ��ģʽ
 �������  : ��
 �� �� ֵ  : 0         ���óɹ�
             -1      ����ʧ��
*****************************************************************************/
extern BSP_S32 DRV_MODEM_MODE_CONFIG(PWC_COMM_MODEM_E modem_id,PWC_COMM_MODE_E mode_id);



#endif

