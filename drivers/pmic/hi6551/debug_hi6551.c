
#ifdef __KERNEL__
#include "exc_hi6551.h"
#endif
#include "pmu_balong.h"
#include "common_hi6551.h"

/*��Դ����*/
char* hi6551_volt_name[PMIC_HI6551_VOLT_MAX + 1]={"BUCK0","BUCK1","BUCK2","BUCK3","BUCK4","BUCK5","BUCK6","BOOST", \
"LDO1","LDO2","LDO3","LDO4","LDO5","LDO6","LDO7","LDO8","LDO9","LDO10","LDO11","LDO12","LDO13","LDO14", \
"LDO15","LDO16","LDO17","LDO18","LDO19","LDO20","LDO21","LDO22","LDO23","LDO24",\
"LVS2","LVS3","LVS4","LVS5","LVS6","LVS7","LVS8","LVS9","LVS10"};
char* hi6551_mode_name[PMU_MODE_BUTTOM+1]={"NORMAL","MODE_ECO","FORCE_ECO","FOLLOW_ECO","NONE_MODE","MODE_INVALID"};

/*��������*/
void bsp_hi6551_volt_show(int volt_id);
void bsp_hi6551_volt_state(void);
#ifdef __KERNEL__
void bsp_hi6551_om_data_show(void);
void bsp_hi6551_om_boot_show(void);
void bsp_hi6551_exc_state(void);
#endif
void bsp_hi6551_version_get(void);

/*����ʵ��*/
/*para check func*/
static __inline__ int hi6551_volt_para_check(int volt_id)
{
    /* ��Ч�Լ��*/
    if ((PMIC_HI6551_VOLT_MAX < volt_id) || (PMIC_HI6551_VOLT_MIN > volt_id))
    {
        pmic_print_error("PMIC doesn't have this volt ,the volt you can set is from %d to %d,please check!\n",PMIC_HI6551_VOLT_MIN,PMIC_HI6551_VOLT_MAX);
        return BSP_PMU_ERROR;
    }
    else
        return BSP_PMU_OK;
}

/*****************************************************************************
 �� �� ��  : bsp_hi6551_volt_show
 ��������  : ��ʾ��ǰ����·��Դ��ʹ����Ϣ(�������أ���ѹ��)
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :�쳣��λ
*****************************************************************************/
void bsp_hi6551_volt_show(int volt_id)
{
    int sw;/*����״̬*/
    int voltage;/*��ѹ*/
    pmu_mode_e mode;/*ģʽ*/
    char* onoff;/*��������*/
    char* name;/*��ѹԴ����*/
    char* mod_name;
    int iret;

    iret = hi6551_volt_para_check(volt_id);
    if(iret)
        return;

    sw = bsp_hi6551_volt_is_enabled(volt_id);
    voltage = bsp_hi6551_volt_get_voltage(volt_id);
    mode = bsp_hi6551_volt_get_mode(volt_id);
    #if 0
    if(volt_id <= PMIC_HI6551_BUCK_MAX)
        name = "BUCK"##volt_id;
    else if(PMIC_HI6551_LDO_MIN > volt_id )
        name = "BOOST"��
    else if(PMIC_HI6551_LDO_MAX >= volt_id)
        name = "LDO"##(volt_id - PMIC_HI6551_LDO_MIN + 1);
    else
        name = "LVS"##(volt_id - PMIC_HI6551_LVS_MIN + 1);
    #endif
    name = hi6551_volt_name[volt_id];
    if(!sw)
        onoff = "OFF";
    else
        onoff = "ON";

    mod_name = hi6551_mode_name[mode];

    pmic_print_error("id:%d ,name:%s ,sw:%s ,voltage:%d uV,mode:%s  \n",volt_id,name,onoff,voltage,mod_name);

}
/*****************************************************************************
 �� �� ��  : bsp_hi6551_volt_state
 ��������  : ��ʾ��ǰ����·��Դ��ʹ����Ϣ(�������أ���ѹ��)
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :�쳣��λ
*****************************************************************************/
void bsp_hi6551_volt_state(void)
{
    int i = 0;
    pmic_print_error("***********bsp_hi6551_all_volt_state*****************\n");
    for(i= PMIC_HI6551_VOLT_MIN;i <= PMIC_HI6551_VOLT_MAX;i++)
    {
        bsp_hi6551_volt_show(i);
    }
}
#ifdef __KERNEL__
/*****************************************************************************
 �� �� ��  : bsp_hi6551_om_data_show
 ��������  : ��ʾ�˴����й����е�ǰPMU״̬���쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6551_om_data_show(void)
{
    int i,j = 0;
    /*�����쳣����*/
    /*otp*/
    if(pmu_hi6551_om_data[0] & ((u32)0x01 << HI6551_OTMP_125_OFFSET))
        pmic_print_error("pmu_hi6551:temperature over 125�� flow !\n");
    /*ocp*/
    /*buck��·*/
    for (j = 1; j < 6; j++)
    {
        if (pmu_hi6551_om_data[3] & ((u32)0x1 << j))
            pmic_print_error("pmu_hi6551:BUCK %d short !\n",j+1);
    }
    /*buck����*/
    for (j = 2; j < 8; j++)
    {
        if (pmu_hi6551_om_data[4] & ((u32)0x1 << j))
            pmic_print_error("pmu_hi6551:BUCK %d overflow !\n",j-1);
    }

    /*ldo ocp exc handle*/
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (pmu_hi6551_om_data[i + 5] & ((u32)0x1 << j))
            {
                pmic_print_error("pmu_hi6551:LDO %d overflow !\n" ,(i*8+j+1));
            }
        }
    }
    /*lvs ocp*/
    for(j = 0; j < 7; j++)
    {
        if (pmu_hi6551_om_data[8] & ((u32)0x1 << j))
            pmic_print_error("pmu_hi6551:LVS %d overflow !\n",j+2);/*LVS��LVS2��ʼ���*/
    }
    for(j = 0; j < 1; j++)
    {
        if (pmu_hi6551_om_data[9] & ((u32)0x1 << j))
            pmic_print_error("pmu_hi6551:LVS %d overflow !\n",j+9);
    }
    /*boost,class������*/
}
/*****************************************************************************
 �� �� ��  : bsp_hi6551_boot_om_show
 ��������  : ��ʾ��ǰPMU����ʱ��¼���쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6551_om_boot_show(void)
{
    int i,j = 0;

    for(j = 0; j < 11; j++)
    {
        pmic_print_error("pmu_hi6551:np%d:%x!\n",j+1,pmu_hi6551_om_boot[j]);
    }

    if(pmu_hi6551_om_boot[0] & (0x01 << HI6551_VSYS_UNDER_2P5_OFFSET ) )
        pmic_print_error("pmu_hi6551:vsys under 2.5v last time!\n");
    if(pmu_hi6551_om_boot[0] & (0x01 << HI6551_VSYS_UNDER_2P7_OFFSET ) )
        pmic_print_error("pmu_hi6551:vsys under 2.7/3.0v last time!\n");
    /*��ѹ*/
    if(pmu_hi6551_om_boot[0] & (0x01 << HI6551_VSYS_OVER_6P0_OFFSET ))
        pmic_print_error("pmu_hi6551:vsys over 6.0v last time!\n");
    /*����*/
    if(pmu_hi6551_om_boot[1] & (0x01 << HI6551_OTMP_150_OFFSET ) )
        pmic_print_error("pmu_hi6551:temperature over 150�� last time!\n");
    /*otp*/
    if(pmu_hi6551_om_boot[0] & (0x01 << HI6551_OTMP_125_OFFSET))
        pmic_print_error("pmu_hi6551:temperature over 125�� last time!\n");
    /*ocp*/
    /*buck��·*/
    for (j = 1; j < 6; j++)
    {
        if (pmu_hi6551_om_boot[3] & ((u32)0x1 << j))
            pmic_print_error("pmu_hi6551:Buck %d short last time!\n",j+1);
    }
    /*buck����*/
    for (j = 2; j < 8; j++)
    {
         if (pmu_hi6551_om_boot[4] & ((u32)0x1 << j))
            pmic_print_error("pmu_hi6551:Buck %d overflow last time!\n",j-1);
    }

    /*ldo ocp exc handle*/
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (pmu_hi6551_om_boot[i + 5] & ((u32)0x1 << j))
            {
                pmic_print_error("pmu_hi6551:LDO id %d overflow last time!\n" ,(i*8+j+1));
            }
        }
    }
    /*lvs ocp*/
    for(j = 0; j < 7; j++)
    {
         if (pmu_hi6551_om_boot[8] & ((u32)0x1 << j))
            pmic_print_error("pmu_hi6551:LVS %d overflow last time!\n",j+2);/*LVS��LVS2��ʼ���*/
    }
    for(j = 0; j < 1; j++)
    {
         if (pmu_hi6551_om_boot[9] & ((u32)0x1 << j))
            pmic_print_error("pmu_hi6551:LVS %d overflow last time!\n",j+9);
    }
    /*boost,class������*/
}
/*****************************************************************************
 �� �� ��  : bsp_hi6551_exc_state
 ��������  : ��ʾ��ǰPMU���쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6551_exc_state(void)
{
    bsp_hi6551_om_boot_show();
    bsp_hi6551_om_data_show();

    pmic_print_error("bsp_hi6551_exc_state over!\n");
}
#endif
/*****************************************************************************
 �� �� ��  : bsp_hi6551_version_get
 ��������  : ��ʾ��ǰPMIC�İ汾��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6551_version_get(void)
{
    u8 version = 0;

    version = hi6551_version_get();
    pmic_print_error("PMIC HI6551 version is 0x%x!\n",version);
}

/*****************************************************************************
 �� �� ��  : bsp_hi6551_debug_init
 ��������  : hi6551 debugģ��ĳ�ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6551_debug_init(void)
{
    int iret = BSP_PMU_OK;
    struct pmu_dbg_ops hi6551_dbg_ops;

    memset((void*)&hi6551_dbg_ops, 0, sizeof(struct pmu_dbg_ops));
    hi6551_dbg_ops.pmu_volt_show = bsp_hi6551_volt_show;
    hi6551_dbg_ops.pmu_volt_state = bsp_hi6551_volt_state;
    hi6551_dbg_ops.pmu_pmic_info = bsp_hi6551_version_get;
#ifdef __KERNEL__
    hi6551_dbg_ops.pmu_om_data_show = bsp_hi6551_om_data_show;
    hi6551_dbg_ops.pmu_om_boot_show = bsp_hi6551_om_boot_show;
    hi6551_dbg_ops.pmu_exc_state = bsp_hi6551_exc_state;
#endif

    iret = bsp_pmu_dbg_register(PMIC_HI6551,hi6551_dbg_ops);

    if(BSP_PMU_OK != iret)
        pmic_print_error("bsp_pmu_dbg_register error!\n");
    else
        pmic_print_error("bsp_hi6551_debug_init ok!\n");
}


