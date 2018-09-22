#include "pmu_balong.h"
#ifdef __KERNEL__
#include "exc_hi6451.h"
#endif
#include "common_hi6451.h"

/*��Դ����*/
char* hi6451_volt_name[PMIC_HI6451_VOLT_MAX]={"BUCK0","BUCK1","BUCK2","BUCK3","BUCK4","BUCK5","BUCK6", \
"LDO1","LDO2","LDO3","LDO4","LDO5","LDO6","LDO7","LDO8","LDO9","LDO10","LDO11","LDO12","LDO13","LDO14", \
"LDO15","DR1","DR2","DR3"};
char* hi6451_mode_name[PMU_MODE_BUTTOM]={"NORMAL","ECO","","","NONE_MODE"};

/*�쳣״̬��¼*/
extern u8 pmu_hi6451_om_data[6];
extern u8 pmu_hi6451_om_boot[3];

/*para check func*/
static __inline__ int hi6451_volt_para_check(int volt_id)
{
    /* ��Ч�Լ��*/
    if ((PMIC_HI6451_VOLT_MAX < volt_id) || (PMIC_HI6451_VOLT_MIN > volt_id))
    {
        pmic_print_error("PMIC doesn't have this volt ,the volt you can set is from %d to %d,please check!\n",PMIC_HI6451_VOLT_MIN,PMIC_HI6451_VOLT_MAX);
        return BSP_PMU_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : bsp_hi6451_volt_show
 ��������  : ��ʾ��ǰ����·��Դ��ʹ����Ϣ(�������أ���ѹ��)
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :�쳣��λ
*****************************************************************************/
void bsp_hi6451_volt_show(int volt_id)
{
    int sw;/*����״̬*/
    int voltage;/*��ѹ*/
    pmu_mode_e mode;/*ģʽ*/
    char* onoff;/*��������*/
    char* name;/*��ѹԴ����*/
    char* mod_name;

    hi6451_volt_para_check(volt_id);
    sw = bsp_hi6451_volt_is_enabled(volt_id);
    voltage = bsp_hi6451_volt_get_voltage(volt_id);
    mode = bsp_hi6451_volt_get_mode(volt_id);
    #if 0
    if(volt_id <= PMIC_HI6451_BUCK_MAX)
        name = "BUCK"##volt_id;
    else if(PMIC_HI6451_LDO_MAX >= volt_id)
        name = "LDO"##(volt_id - PMIC_HI6451_LDO_MIN + 1);
    #endif

    name = hi6451_volt_name[volt_id];
    if(!sw)
        onoff = "OFF";
    else
        onoff = "ON";

    mod_name = hi6451_mode_name[mode];

    pmic_print_error("id:%d ,name:%s ,sw:%s ,voltage:%d uV,mode:%s  \n",volt_id,name,onoff,voltage,mod_name);

}
/*****************************************************************************
 �� �� ��  : bsp_hi6451_volt_state
 ��������  : ��ʾ��ǰ����·��Դ��ʹ����Ϣ(�������أ���ѹ��)
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :�쳣��λ
*****************************************************************************/
void bsp_hi6451_volt_state(void)
{
    int i = 0;

    pmic_print_error("***********bsp_hi6451_all_volt_state*****************\n");

    for(i= PMIC_HI6451_VOLT_MIN;i <= PMIC_HI6451_VOLT_MAX;i++)
    {
        bsp_hi6451_volt_show(i);
    }
}
#ifdef __KERNEL__
/*****************************************************************************
 �� �� ��  : bsp_hi6451_om_data_show
 ��������  : ��ʾ�˴����й����е�ǰPMU״̬���쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6451_om_data_show(void)
{
    int i,j = 0;

    if(pmu_hi6451_om_data[1] & (0x01 << HI6451_OCP_OFFSET))/*����*/
    {
        /* �������OCP_RECORD�е�״̬,��ȫ���� */
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 8; j++)
            {
                if (pmu_hi6451_om_data[i + 3] & (0x1 << (7-j)))
                {
                    if(i < 2)
                    {
                        pmic_print_error("pmu_hi6451:Volt %d overflow !\n",(i*8+j+1));
                    }
                    else
                    {
                        pmic_print_error("pmu_hi6451:Volt %d overflow !\n",(i*8+j-2));
                    }
                }
            }
        }
    }
    if(pmu_hi6451_om_data[0] & (0x01 << HI6451_OTP_OFFSET))
        pmic_print_error("pmu_hi6451:temperature overflow (>135/125/115/105��)!\n");
    if(pmu_hi6451_om_data[0] & (0x01 << HI6451_OVP_OFFSET))
        pmic_print_error("pmu_hi6451:vsys over 6.0v !\n");
    if(pmu_hi6451_om_data[0] & (0x01 << HI6451_UVP_OFFSET))
        pmic_print_error("pmu_hi6451:vsys under 2.5v !\n");
}
/*****************************************************************************
 �� �� ��  : bsp_hi6451_boot_om_show
 ��������  : ��ʾ��ǰPMU����ʱ��¼���쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6451_boot_om_show(void)
{
    /*Ƿѹ����ѹ*/
    if(pmu_hi6451_om_boot[0] & (0x01 << HI6451_VINI_UNDER_2P7_OFFSET ))
        pmic_print_error("pmu_hi6451:vsys under 2.5v last time!\n");
    if(pmu_hi6451_om_boot[0] & (0x01 << HI6451_VINI_OVER_6P0_OFFSET ))
        pmic_print_error("pmu_hi6451:vsys over 6.0v last time!\n");
    /*����*/
    if(pmu_hi6451_om_boot[1] & (0x01 << HI6451_CORE_OVER_CUR_OFFSET ) )
        pmic_print_error("pmu_hi6451:ldo/buck overflow last time!\n");
    /*����*/
    if(pmu_hi6451_om_boot[2] & (0x01 << HI6451_OTMP_150_OFFSET ) )
        pmic_print_error("pmu_hi6451:temperature over 150�� last time!\n");
}
/*****************************************************************************
 �� �� ��  : bsp_hi6451_exc_state
 ��������  : ��ʾ��ǰPMU���쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6451_exc_state(void)
{
    bsp_hi6451_boot_om_show();
    bsp_hi6451_om_data_show();

    pmic_print_error("bsp_hi6451_exc_state over!\n");
}
#endif
/*****************************************************************************
 �� �� ��  : bsp_hi6451_version_get
 ��������  : ��ʾ��ǰPMIC�İ汾��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6451_version_get(void)
{
    u8 version = 0;

    version = hi6451_version_get();
    pmic_print_error("PMIC HI6451 version is 0x%x!\n",version);
}

/*****************************************************************************
 �� �� ��  : bsp_hi6451_debug_init
 ��������  : hi6451 debugģ��ĳ�ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6451_debug_init(void)
{
    int iret = BSP_PMU_OK;

    struct pmu_dbg_ops hi6451_dbg_ops = {
        .pmu_volt_show = bsp_hi6451_volt_show,
        .pmu_volt_state = bsp_hi6451_volt_state,
        .pmu_pmic_info = bsp_hi6451_version_get,
#ifdef __KERNEL__
        .pmu_om_data_show = bsp_hi6451_om_data_show,
        .pmu_om_data_show = bsp_hi6451_boot_om_show,
        .pmu_exc_state = bsp_hi6451_exc_state,
#endif
    };

    iret = bsp_pmu_dbg_register(PMIC_HI6451,hi6451_dbg_ops);

    if(BSP_PMU_OK != iret)
        pmic_print_error("bsp_pmu_dbg_register error!\n");
    else
        pmic_print_error("bsp_hi6451_debug_init ok!\n");
}
