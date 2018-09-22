#include <bsp_pmu.h>
#ifdef __KERNEL__
#include "exc_hi6559.h"
#endif
#include "pmu_balong.h"
#include "common_hi6559.h"

/*��Դ����*/
char* hi6559_volt_name[PMIC_HI6559_VOLT_MAX + 1] =
{   
    "BUCK0","BUCK3","BUCK4","BUCK5","BUCK6","LDO01","LDO03",
    "LDO06","LDO07","LDO08","LDO09","LDO10","LDO11","LDO12",
    "LDO13","LDO14","LDO22","LDO23","LDO24","LVS07","LVS09"
};
char* hi6559_mode_name[PMU_MODE_BUTTOM+1] =
{   
    "NORMAL",
    "MODE_ECO",
    "FORCE_ECO",
    "FOLLOW_ECO",
    "NONE_MODE",
    "MODE_INVALID"
};

void bsp_hi6559_volt_show(s32  volt_id);
void bsp_hi6559_volt_state(void);
void bsp_hi6559_version_get(void);
extern s32 hi6559_volt_para_check(s32 volt_id);

#ifdef __KERNEL__
void bsp_hi6559_om_data_show(void);
void bsp_hi6559_om_boot_show(void);
void bsp_hi6559_exc_state(void);extern struct hi6559_reg_cont  reg_np_scp_record1_cont[HI6559_NP_SCP_RECORD1_CONT_NUM]; 
extern struct hi6559_reg_cont  reg_np_ocp_record1_cont[HI6559_NP_OCP_RECORD1_CONT_NUM];
extern struct hi6559_reg_cont  reg_np_ocp_record2_cont[HI6559_NP_OCP_RECORD2_CONT_NUM];
#endif

int bsp_hi6559_volt_set_voltage_test(int volt_id, int min_uV, int max_uV)
{
    unsigned selector = 0;
    int iret = BSP_PMU_OK;

    iret = bsp_hi6559_volt_set_voltage(volt_id,min_uV,max_uV,&selector);
    if(iret)
        return iret;
    else
    {
        pmic_print_info("selector value is %d!!",selector);
        return (int)selector;
    }
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_show
 ��������  : ��ʾ��ǰ����·��Դ��ʹ����Ϣ(�������أ���ѹ��)
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void bsp_hi6559_volt_show(s32  volt_id)
{
    pmu_mode_e mode;            /* ģʽ */
    s32  sw;                    /* ����״̬ */
    s32  voltage;               /* ��ѹ */
    s32  iret;
    char* onoff = NULL;         /* �������� */
    char* name = NULL;          /* ��ѹԴ���� */
    char* mod_name = NULL;

    iret = hi6559_volt_para_check(volt_id);
    if(iret)
    {
        return;
    }

    sw = bsp_hi6559_volt_is_enabled(volt_id);
    voltage = bsp_hi6559_volt_get_voltage(volt_id);
    mode = bsp_hi6559_volt_get_mode(volt_id);
    name = hi6559_volt_name[volt_id];
    if(!sw)
    {
        onoff = "OFF";
    }
    else
    {
        onoff = "ON";
    }

    mod_name = hi6559_mode_name[mode];

    pmic_print_error("id:%d, name:%s, sw:%s, voltage:%duV, mode:%s\n",volt_id, name, onoff, voltage, mod_name);

    return;
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_volt_state
 ��������  : ��ʾ��ǰ����·��Դ��ʹ����Ϣ(�������أ���ѹ��)
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void bsp_hi6559_volt_state(void)
{
    s32  i = 0;
    pmic_print_error("***********bsp_hi6559_all_volt_state*****************\n");
    for(i= PMIC_HI6559_VOLT_MIN;i <= PMIC_HI6559_VOLT_MAX;i++)
    {
        bsp_hi6559_volt_show(i);
    }

    return;
}

#ifdef __KERNEL__
/*****************************************************************************
 �� �� ��  : bsp_hi6559_om_data_show
 ��������  : ��ʾ�˴����й����е�ǰPMU״̬���쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void bsp_hi6559_om_data_show(void)
{
    s32 j = 0;
    
    /* ����125�� */
    if(pmu_hi6559_om_data[0] & (u8)((u32)0x01 << HI6559_OTMP_125_OFFSET))  
    {
        pmic_print_error("pmu_hi6559:temperature over 125�� flow !\n");
    }

    /* buck��·���Ĵ���0x18 */
    for (j = 0; j < HI6559_NP_SCP_RECORD1_CONT_NUM; j++)       
    {
        if (pmu_hi6559_om_data[3] & (u8)((u32)0x1 << reg_np_scp_record1_cont[j].bit_ofs))
        {
            pmic_print_error("pmu_hi6559:BUCK %d short !\n",j+1);
        }
    }

    /* buck�������Ĵ���0x19 */
    for (j = 0; j < HI6559_NP_OCP_RECORD1_CONT_NUM; j++)       
    {
        if (pmu_hi6559_om_data[4] & (u8)((u32)0x1 << reg_np_ocp_record1_cont[j].bit_ofs))
        {
            pmic_print_error("pmu_hi6559:BUCK %d overflow !\n",j-1);
        }
    }

    /* ldo1~8�������Ĵ���0x1A */
    for (j = 0; j < HI6559_NP_OCP_RECORD2_CONT_NUM; j++)       
    {
        if (pmu_hi6559_om_data[5] & (u8)((u32)0x1 << reg_np_ocp_record2_cont[j].bit_ofs))
        {
            pmic_print_error("pmu_hi6559:LDO%d overflow !\n" ,reg_np_ocp_record2_cont[j].cont);
        }
    }

    /* ldo9~14�������Ĵ���0x1B */
    for (j = 0; j < HI6559_NP_OCP_RECORD3_CONT_NUM; j++)       
    {
        if (pmu_hi6559_om_data[6] & (u8)((u32)0x1 << j))                       
        {
            pmic_print_error("pmu_hi6559:LDO%d overflow !\n" , j + 9);
        }
    }
    
    /* ldo22~24�������Ĵ���0x1C */
    for(j = 0; j < HI6559_NP_OCP_RECORD4_CONT_NUM; j++)        
    {
        if (pmu_hi6559_om_data[7] & (u8)((u32)0x1 << (j + 5)))                 
        {
            pmic_print_error("pmu_hi6559:LDO%d overflow !\n" , j + 22);
        }
    }
    
    /* lvs7�������Ĵ���0x1D */
    if (pmu_hi6559_om_data[8] & (u8)((u32)0x1 << HI6559_LVS07_BIT_OFFSET))     
    {
        pmic_print_error("pmu_hi6559: LVS7 overflow last time!\n");
    }
    
    /* lvs9�������Ĵ���0x1E */
    if (pmu_hi6559_om_data[9] & (u8)((u32)0x1 << HI6559_LVS09_BIT_OFFSET))     
    {
        pmic_print_error("pmu_hi6559: LVS9 overflow last time!\n");
    } 

    return;
}
/*****************************************************************************
 �� �� ��  : bsp_hi6559_boot_om_show
 ��������  : ��ʾ��ǰPMU����ʱ��¼���쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6559_om_boot_show(void)
{
    s32 j = 0;

    for(j = 0; j < HI6559_NP_RECORD_REG_NUM; j++)
    {
        pmic_print_error("pmu_hi6559:reg_addr: 0x%x, reg_val 0x%x!\n", 0x15 + j, pmu_hi6559_om_boot[j]);
    }

    /* Ƿѹ2.5V */
    if(pmu_hi6559_om_boot[0] & (0x01 << HI6559_VSYS_UNDER_2P5_OFFSET ) )
    {
        pmic_print_error("pmu_hi6559:vsys under 2.5v last time!\n");
    }
    
    /* Ƿѹ2.85V */
    if(pmu_hi6559_om_boot[0] & (0x01 << HI6559_VSYS_UNDER_2P85_OFFSET ) )
    {
        pmic_print_error("pmu_hi6559:vsys under 2.85/3.0v last time!\n");
    }

    /* ��ѹ6.0V */
    if(pmu_hi6559_om_boot[0] & (0x01 << HI6559_VSYS_OVER_6P0_OFFSET ))
    {
        pmic_print_error("pmu_hi6559:vsys over 6.0v last time!\n");
    }

    /* ����125�� */
    if(pmu_hi6559_om_boot[0] & (0x01 << HI6559_OTMP_125_OFFSET))
    {
        pmic_print_error("pmu_hi6559:temperature over 125�� last time!\n");
    }
    
    /* ����150�� */
    if(pmu_hi6559_om_boot[1] & (0x01 << HI6559_OTMP_150_OFFSET ) )
    {
        pmic_print_error("pmu_hi6559:temperature over 150�� last time!\n");
    }

    /* buck��·���Ĵ���0x18 */
    for (j = 0; j < HI6559_NP_SCP_RECORD1_CONT_NUM; j++)       
    {
        if (pmu_hi6559_om_boot[3] & (u8)((u32)0x1 << reg_np_scp_record1_cont[j].bit_ofs))
        {
            pmic_print_error("pmu_hi6559:BUCK %d short !\n",j+1);
        }
    }

    /* buck�������Ĵ���0x19 */
    for (j = 0; j < HI6559_NP_OCP_RECORD1_CONT_NUM; j++)       
    {
        if (pmu_hi6559_om_boot[4] & (u8)((u32)0x1 << reg_np_ocp_record1_cont[j].bit_ofs))
        {
            pmic_print_error("pmu_hi6559:BUCK %d overflow !\n",j-1);
        }
    }

    /* ldo1~8�������Ĵ���0x1A */
    for (j = 0; j < HI6559_NP_OCP_RECORD2_CONT_NUM; j++)       
    {
        if (pmu_hi6559_om_boot[5] & (u8)((u32)0x1 << reg_np_ocp_record2_cont[j].bit_ofs))
        {
            pmic_print_error("pmu_hi6559:LDO%d overflow !\n" ,reg_np_ocp_record2_cont[j].cont);
        }
    }

    /* ldo9~14�������Ĵ���0x1B */
    for (j = 0; j < HI6559_NP_OCP_RECORD3_CONT_NUM; j++)       
    {
        if (pmu_hi6559_om_boot[6] & (u8)((u32)0x1 << j))
        {
            pmic_print_error("pmu_hi6559:LDO%d overflow !\n" , j + 9);
        }
    }
    
    /* ldo22~24�������Ĵ���0x1C */
    for(j = 0; j < HI6559_NP_OCP_RECORD4_CONT_NUM; j++)        
    {
        if (pmu_hi6559_om_boot[7] & (u8)((u32)0x1 << (j + 5)))
        {
            pmic_print_error("pmu_hi6559:LDO%d overflow !\n" , j + 22);
        }
    }
    
    /* lvs7�������Ĵ���0x1D */
    if (pmu_hi6559_om_boot[8] & (u8)((u32)0x1 << HI6559_LVS07_BIT_OFFSET))    
    {
        pmic_print_error("pmu_hi6559: LVS7 overflow last time!\n");
    }
    
    /* lvs9�������Ĵ���0x1E */
    if (pmu_hi6559_om_boot[9] & (u8)((u32)0x1 << HI6559_LVS09_BIT_OFFSET))         
    {
        pmic_print_error("pmu_hi6559: LVS9 overflow last time!\n");
    } 

    return;
}
/*****************************************************************************
 �� �� ��  : bsp_hi6559_exc_state
 ��������  : ��ʾ��ǰPMU���쳣��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6559_exc_state(void)
{
    bsp_hi6559_om_boot_show();
    bsp_hi6559_om_data_show();

    pmic_print_error("bsp_hi6559_exc_state over!\n");
}
#endif
/*****************************************************************************
 �� �� ��  : bsp_hi6559_version_get
 ��������  : ��ʾ��ǰPMIC�İ汾��Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void bsp_hi6559_version_get(void)
{
    u8 version = 0;

    version = hi6559_version_get();
    pmic_print_error("PMIC HI6559 version is 0x%x!\n",version);
}

/*****************************************************************************
 �� �� ��  : bsp_hi6559_debug_init
 ��������  : hi6559 debugģ��ĳ�ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : �쳣��λ
*****************************************************************************/
void bsp_hi6559_debug_init(void)
{
    struct pmu_dbg_ops hi6559_dbg_ops;
    s32  iret = BSP_PMU_OK;

    memset((void*)&hi6559_dbg_ops, 0, sizeof(struct pmu_dbg_ops));
    hi6559_dbg_ops.pmu_volt_show = bsp_hi6559_volt_show;
    hi6559_dbg_ops.pmu_volt_state = bsp_hi6559_volt_state;
    hi6559_dbg_ops.pmu_pmic_info = bsp_hi6559_version_get;
#ifdef __KERNEL__
    hi6559_dbg_ops.pmu_om_data_show = bsp_hi6559_om_data_show;
    hi6559_dbg_ops.pmu_om_boot_show = bsp_hi6559_om_boot_show;
    hi6559_dbg_ops.pmu_exc_state = bsp_hi6559_exc_state;
#endif

    iret = bsp_pmu_dbg_register(PMIC_HI6559, hi6559_dbg_ops);

    if(BSP_PMU_OK != iret)
    {
        pmic_print_error("bsp_pmu_dbg_register error!\n");
    }
    else
    {
        pmic_print_error("bsp_hi6559_debug_init ok!\n");
    }
    
    return;
}


