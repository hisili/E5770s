

#ifndef __BSP_PA_RF_H__
#define __BSP_PA_RF_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include <osl_types.h>
#include <drv_dpm.h>
#include <drv_pmu.h>

#define PA_RF_ICC_CHN_ID                          ((ICC_CHN_IFC << 16) | IFC_RECV_FUNC_PA_RF)

struct pmu_parf_ops
{
    /* dpm interface */
    s32 (*pmu_pa_power_on)(PWC_COMM_MODEM_E modem_id);
    s32 (*pmu_pa_power_off)(PWC_COMM_MODEM_E modem_id);
    s32 (*pmu_rf_power_on)(PWC_COMM_MODEM_E modem_id);
    s32 (*pmu_rf_power_off)(PWC_COMM_MODEM_E modem_id);
    PWC_COMM_STATUS_E (*pmu_pa_power_status)(PWC_COMM_MODEM_E modem_id);
    PWC_COMM_STATUS_E (*pmu_rf_power_status)(PWC_COMM_MODEM_E modem_id);

    /* DRV interface */
    s32 (*drv_pastar_exc_check)(PWC_COMM_MODEM_E modem_id);
    s32 (*drv_modem_voltage_set)(EM_MODEM_CONSUMER_ID consumer_id, u32 voltage_mv );
    s32 (*drv_modem_voltage_get)(EM_MODEM_CONSUMER_ID consumer_id, u32 *voltage_mv );
    s32 (*drv_modem_voltage_list)(EM_MODEM_CONSUMER_ID consumer_id, u16 **list, u32 *size);
    s32 (*drv_modem_apt_enable)(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);
    s32 (*drv_modem_apt_disable)(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);
    s32 (*drv_modem_apt_status_get)(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);
    s32 (*drv_modem_mode_config)(PWC_COMM_MODEM_E modem_id, PWC_COMM_MODE_E mode_id);    
};

/*****************************************************************************
 �� �� ��  : bsp_pa_rf_init
 ��������  : ��ȡregulator
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0:�ɹ���else - ʧ�ܡ�ʧ��ʱ����ֵ��bit0~bit4��Ӧ��ȡʧ�ܵ�regulator_pmu id
*****************************************************************************/
s32 bsp_pa_rf_init(void);

/*****************************************************************************
 �� �� ��  : bsp_pa_poweron
 ��������  : ��pa�ϵ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_pa_poweron(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : bsp_pa_poweroff
 ��������  : ��pa�µ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_pa_poweroff(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : bsp_get_pa_powerstatus
 ��������  : ��ȡpa���µ�״̬
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
PWC_COMM_STATUS_E bsp_get_pa_powerstatus(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : bsp_rf_poweron
 ��������  : ��rf�ϵ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_rf_poweron(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : bsp_rf_poweroff
 ��������  : ��rf�µ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_rf_poweroff(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : bsp_get_rf_powerstatus
 ��������  : ��ȡrf���µ�״̬
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
PWC_COMM_STATUS_E bsp_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id);

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __BSP_PA_RF_H__ */
