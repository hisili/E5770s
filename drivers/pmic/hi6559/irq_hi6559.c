/*
 * kernel/driver/pmic/hi6559/irq_hi6559.c
 *
 * Copyright (C) 2013 Hisilicon
 * License terms: GNU General Public License (GPL) version 2
 *
 */
/*lint --e{537,958}*/
#include <linux/spinlock.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/list.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/bitops.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <mach/irqs.h>
#include <linux/slab.h>
#include <linux/irqnr.h>
#include <linux/err.h>
#include <linux/kernel.h>
#include "osl_spinlock.h"

#ifdef CONFIG_MODULE_VIC
#include "bsp_vic.h"
#endif
#include "pmu_balong.h"
#include "common_hi6559.h"
#include <hi_bbstar.h>
#include "irq_hi6559.h"


/*����жϴ���ص�����������*/
hi6559_irq_st Hi6559IrqInfo[HI6559_IRQ_NR];
struct hi6559_irq_data  *hi6559_irq_data_st;/*�ж�ȫ�ֽṹ��*/

#ifdef CONFIG_MODULE_VIC
static __inline__ void hi6559_irq_enable(void)
{
    bsp_vic_enable(INT_LVL_SMART);
}
static __inline__ void hi6559_irq_disable(void)
{
    bsp_vic_disable(INT_LVL_SMART);
}

#else
static __inline__ void hi6559_irq_enable(void)
{
    enable_irq(INT_LVL_PMU);
}
static __inline__ void hi6559_irq_disable(void)
{
    disable_irq_nosync(INT_LVL_PMU);
}
#endif

/*****************************************************************************
 �� �� ��  : hi6559_irq_cnt_show
 ��������  : ��ʾ�жϺ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_irq_cnt_show(void)
{
    s32 i = 0;

    for (i = 0; i < HI6559_IRQ_NR; i++)
    {
      pmic_print_error("hi6559 irq %d is %d!\n", i, Hi6559IrqInfo[i].cnt);
    }
}

/*****************************************************************************
 �� �� ��  : hi6559_irq_mask
 ��������  : �����ж�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_irq_mask(u32 irq)
{
    hi6559_irqflags_t irq_flags = 0;
    u32 offset = 0;
    u8 reg_temp = 0;

    /* �����Ϸ��Լ�� */
    if (irq > IRQ_HI6559_NR_BASE + HI6559_IRQ_NR) 
    {
        pmic_print_error("hi6559 irq is error,please check irq=%d\n", (s32)irq);
        return;
    }
    
    /*lint --e{746,718}*/
    spin_lock_irqsave(&hi6559_irq_data_st->irq_lock, irq_flags);

    offset = irq - IRQ_HI6559_NR_BASE;
    if (offset < HI6559_IRQM2_BASE_OFFSET) 
    {
        bsp_hi6559_reg_read(HI6559_IRQ1_MASK_OFFSET, &reg_temp);
        reg_temp |= (u8)((u32)1 << offset);
        bsp_hi6559_reg_write(HI6559_IRQ1_MASK_OFFSET, reg_temp);
    } 
    else if(offset < HI6559_IRQM3_BASE_OFFSET)
    {
        offset -= HI6559_IRQM2_BASE_OFFSET;
        bsp_hi6559_reg_read(HI6559_IRQ2_MASK_OFFSET, &reg_temp);
        reg_temp |= (u8)((u32)1 << offset);
        bsp_hi6559_reg_write(HI6559_IRQ2_MASK_OFFSET, reg_temp);
    }
    else if(offset < HI6559_IRQM4_BASE_OFFSET)
    {
        offset -= HI6559_IRQM3_BASE_OFFSET;
        bsp_hi6559_reg_read(HI6559_IRQ3_MASK_OFFSET, &reg_temp);
        reg_temp |= (u8)((u32)1 << offset);
        bsp_hi6559_reg_write(HI6559_IRQ3_MASK_OFFSET, reg_temp);
    }
    else 
    {
        offset -= HI6559_IRQM4_BASE_OFFSET;
        bsp_hi6559_reg_read(HI6559_IRQ4_MASK_OFFSET, &reg_temp);
        reg_temp |= (u8)((u32)1 << offset);
        bsp_hi6559_reg_write(HI6559_IRQ4_MASK_OFFSET, reg_temp);
    }

    spin_unlock_irqrestore(&hi6559_irq_data_st->irq_lock, irq_flags);

    return;
}

/*****************************************************************************
 �� �� ��  : hi6559_irq_unmask
 ��������  : �������ж�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_irq_unmask(u32 irq)
{
    hi6559_irqflags_t irq_flags = 0;
    u32 offset = 0;
    u8 reg_temp = 0;

    /* �����Ϸ��Լ�� */
    if (irq > IRQ_HI6559_NR_BASE + HI6559_IRQ_NR) 
    {
        pmic_print_error("hi6559 irq is error,please check irq=%d\n", (s32)irq);
        return ;
    }
    spin_lock_irqsave(&hi6559_irq_data_st->irq_lock, irq_flags);

    offset = irq - IRQ_HI6559_NR_BASE;
    if (offset < HI6559_IRQM2_BASE_OFFSET) 
    {
        bsp_hi6559_reg_read(HI6559_IRQ1_MASK_OFFSET, &reg_temp);
        reg_temp &= ~(u8)((u32)1 << offset);
        bsp_hi6559_reg_write(HI6559_IRQ1_MASK_OFFSET, reg_temp);
    } 
    else if(offset < HI6559_IRQM3_BASE_OFFSET)
    {
        offset -= HI6559_IRQM2_BASE_OFFSET;
        bsp_hi6559_reg_read(HI6559_IRQ2_MASK_OFFSET, &reg_temp);
        reg_temp &= ~(u8)((u32)1 << offset);
        bsp_hi6559_reg_write(HI6559_IRQ2_MASK_OFFSET, reg_temp);
    }
    else if(offset < HI6559_IRQM4_BASE_OFFSET)
    {
        offset -= HI6559_IRQM3_BASE_OFFSET;
        bsp_hi6559_reg_read(HI6559_IRQ3_MASK_OFFSET, &reg_temp);
        reg_temp &= ~(u8)((u32)1 << offset);
        bsp_hi6559_reg_write(HI6559_IRQ3_MASK_OFFSET, reg_temp);
    }
    else 
    {
        offset -= HI6559_IRQM4_BASE_OFFSET;
        bsp_hi6559_reg_read(HI6559_IRQ4_MASK_OFFSET, &reg_temp);
        reg_temp &= ~(u8)((u32)1 << offset);
        bsp_hi6559_reg_write(HI6559_IRQ4_MASK_OFFSET, reg_temp);
    }

    spin_unlock_irqrestore(&hi6559_irq_data_st->irq_lock,irq_flags);

    return;
}

/*****************************************************************************
 �� �� ��  : hi6559_irq_is_masked
 ��������  : ���ĳ���ж��Ƿ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_irq_is_masked(u32 irq)
{
    u32 offset = 0;
    u8 reg_temp = 0;

    /* �����Ϸ��Լ�� */
    if (irq > IRQ_HI6559_NR_BASE+HI6559_IRQ_NR) 
    {
        pmic_print_error("hi6559 irq is error,please check irq=%d\n", (s32)irq);
        return HI6559_IRQ_ERROR;
    }

    offset = irq - IRQ_HI6559_NR_BASE;
    if (offset < HI6559_IRQM2_BASE_OFFSET) 
    {
        bsp_hi6559_reg_read(HI6559_IRQ1_MASK_OFFSET, &reg_temp);
    } 
    else if(offset < HI6559_IRQM3_BASE_OFFSET)
    {
        offset -= HI6559_IRQM2_BASE_OFFSET;
        bsp_hi6559_reg_read(HI6559_IRQ2_MASK_OFFSET, &reg_temp);
    }
    else if(offset < HI6559_IRQM4_BASE_OFFSET)
    {
        offset = HI6559_IRQM3_BASE_OFFSET;
        bsp_hi6559_reg_read(HI6559_IRQ3_MASK_OFFSET, &reg_temp);
    }
    else 
    {
        offset = HI6559_IRQM4_BASE_OFFSET;
        bsp_hi6559_reg_read(HI6559_IRQ4_MASK_OFFSET, &reg_temp);
    }    

    return  (reg_temp & ((u32)1 << offset)) ;
}

/*****************************************************************************
 �� �� ��  : hi6559_irq_callback_register
 ��������  : �ص�����ע��
 �������  : @irq: �жϺ�
             @routine: �ص�����
             @data: �ص������Ĳ���
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
s32 hi6559_irq_callback_register(u32 irq, hi6559funcptr routine, void *data)
{
    /* �����Ϸ��Լ�� */
    if (irq >= IRQ_HI6559_NR_BASE + HI6559_IRQ_NR) 
    {
        pmic_print_error("hi6559 irq is error,please check irq=%d\n", (s32)irq);
        return  HI6559_IRQ_ERROR;
    }

    Hi6559IrqInfo[irq].routine = routine;
    Hi6559IrqInfo[irq].data = data;
    return  HI6559_IRQ_OK;
}

/*****************************************************************************
 �� �� ��  : hi6559_irq_wk_handler
 ��������  : 
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_irq_wk_handler(void)
{
    u32 reg = 0;
    u8 i = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg_tmp = 0;
    u8 flag = 0; /*power �����º�̧���ж�ͬʱ�����ı�־*/

    /* �������ж� */
    bsp_hi6559_reg_read(HI6559_IRQ1_OFFSET, &reg1);
    bsp_hi6559_reg_read(HI6559_IRQ2_OFFSET, &reg2);
    bsp_hi6559_reg_read(HI6559_IRQ3_OFFSET, &reg3);
    bsp_hi6559_reg_read(HI6559_IRQ4_OFFSET, &reg4);
    reg = ((u32)reg1 | 
          ((u32)reg2 << HI6559_IRQM2_BASE_OFFSET) | 
          ((u32)reg3 << HI6559_IRQM3_BASE_OFFSET) | 
          ((u32)reg4 << HI6559_IRQM4_BASE_OFFSET));

    /* �����ж�press��release�ж�ͬʱ��������flag��1 */
    if (unlikely(0x60 == (0x60 & reg1))) {  /*lint !e730*/
        flag = 1;
    }

    
    /* ����Ĵ������ж� */
    if (reg1) 
    {
        bsp_hi6559_reg_write(HI6559_IRQ1_OFFSET, reg1);
    }

    if (reg2) 
    {
        if (reg2 & 0x01)    /* �����˹���/��·�ж� */
        {
            for(i = 0; i < HI6559_NP_OCP_SCP_REG_NUM; i++)
            {
                /* �����·/�����ж�״̬�Ĵ��� */
                bsp_hi6559_reg_read(HI6559_IRQ2_OFFSET, &reg_tmp);
                if(reg_tmp)
                {
                    bsp_hi6559_reg_write((HI6559_SCP_RECORD1_OFFSET + i), 0xFF);
                }
            }
        }
        bsp_hi6559_reg_write(HI6559_IRQ2_OFFSET, reg2);
    }

    if (reg3) 
    {
        bsp_hi6559_reg_write(HI6559_IRQ3_OFFSET, reg3);
    }

    if (reg4)
    {
        /* sim�γ��жϣ�ʹ�ðγ��������� */
        if(reg4 & 0x04)
        {
            /* �ȹرյ�Դ�����жϣ������Ȳ�ι���ʧЧ,�޸�Ϊ������У��ʿ���ʹ���� */
            /* ����������Ƿ������������ʱ�䳤��Ӱ���ж���Ӧ */
            bsp_hi6559_volt_disable(PMIC_HI6559_LDO09);
        }

        bsp_hi6559_reg_write(HI6559_IRQ4_OFFSET, reg4);
    }


    if (reg) 
    {
        for (i = 0; i < HI6559_IRQ_NR; i++) 
        {
            if ((1 == flag) && (5 == i))
            {
                /* �����ж�press��release�ж�ͬʱ�������ȴ���press�жϣ������������߼� */
                Hi6559IrqInfo[6].cnt++;    
                if (NULL != Hi6559IrqInfo[6].routine)
                    Hi6559IrqInfo[6].routine(Hi6559IrqInfo[6].data);
                Hi6559IrqInfo[5].cnt++;
                if (NULL != Hi6559IrqInfo[5].routine)
                    Hi6559IrqInfo[5].routine(Hi6559IrqInfo[5].data);
                i = i + 2;
            }
            
            if (reg & ((u32)1 << i)) 
            {
                Hi6559IrqInfo[i].cnt++;
                /* �жϴ��� */
                if (NULL != Hi6559IrqInfo[i].routine)
                {
                    Hi6559IrqInfo[i].routine(Hi6559IrqInfo[i].data);
                }
            }
        }
    }
    pmic_print_info("**********hi6559_irq_wk_handler**********\n");
    hi6559_irq_enable();

    return;
}

#ifdef CONFIG_MODULE_VIC

/*****************************************************************************
 �� �� ��  : hi6559_irq_handler
 ��������  : �жϴ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
void hi6559_irq_handler(u32 irq)
{
    /* �ر��ж�,�жϴ���������ɺ�� */
    hi6559_irq_disable();
    pmic_print_info("**********hi6559_irq_handler**********\n");
    queue_work(hi6559_irq_data_st->hi6559_irq_wq, &hi6559_irq_data_st->hi6559_irq_wk);

    return;
}
#else
/*****************************************************************************
 �� �� ��  : hi6559_irq_handler
 ��������  : �жϴ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
irqreturn_t hi6559_irq_handler(s32 irq, void *data)
{
    struct hi6559_irq_data *hi6559_irq_data = data;
    
    /* �ر��ж�,�жϴ���������ɺ�� */
    hi6559_irq_disable();
    pmic_print_info("**********hi6559_irq_handler**********\n");
    queue_work(hi6559_irq_data->hi6559_irq_wq, &hi6559_irq_data->hi6559_irq_wk);

    return IRQ_HANDLED;
}
#endif


/*****************************************************************************
 �� �� ��  : hi6559_irq_probe
 ��������  : 
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static s32 __init hi6559_irq_probe(struct platform_device *pdev)
{
    s32 ret = BSP_PMU_OK;
    u16 i = 0;
    u8 regvalue = 0;

    hi6559_irq_data_st = kzalloc(sizeof(*hi6559_irq_data_st), GFP_KERNEL);
    if (hi6559_irq_data_st == NULL) 
    {
        pmic_print_error("hi6559 irq kzalloc is failed,please check!\n");
        return -ENOMEM;
    }
    hi6559_irq_data_st->irq = (unsigned)platform_get_irq(pdev, 0);

    spin_lock_init(&hi6559_irq_data_st->irq_lock);/*�ж�ֻ��Acoreʵ�֣���core*/

    /* ��ʼ���������� */
    hi6559_irq_data_st->hi6559_irq_wq = create_singlethread_workqueue("bsp_hi6559_irq");
    INIT_WORK(&hi6559_irq_data_st->hi6559_irq_wk, (void *)hi6559_irq_wk_handler);

    /* ����usb�γ���,��usb����λ���౨usb�γ���Ӱ�� */
    bsp_hi6559_reg_read(HI6559_IRQ2_OFFSET, &regvalue);
    if((regvalue & (0x01 << 2)) && hi6559_usb_state_get())
    {
        bsp_hi6559_reg_write(HI6559_IRQ2_OFFSET, 0x04);
    }
    /* ��������µ��жϼĴ��� */
    for(i = 0;i < HI6559_IRQ_REG_NUM; i++)
    {
        bsp_hi6559_reg_read(HI6559_IRQ1_OFFSET + i,&regvalue);
        bsp_hi6559_reg_write(HI6559_IRQ1_OFFSET + i, regvalue);
    }
    /* �����·�����жϼĴ��������������ж�λ�������� */
    for(i = 0; i < HI6559_NP_OCP_SCP_REG_NUM; i++)
    {
        bsp_hi6559_reg_read(HI6559_SCP_RECORD1_OFFSET + i, &regvalue);
        bsp_hi6559_reg_write(HI6559_SCP_RECORD1_OFFSET + i, regvalue);
    }

    /* ���������ж� */
    for(i = 0;i < HI6559_IRQ_REG_NUM;i++)
    {
        bsp_hi6559_reg_write(HI6559_IRQ1_MASK_OFFSET + i, 0xff);
    }
    
    /* �ж�ע�� */
#ifdef CONFIG_MODULE_VIC
    ret = bsp_vic_connect(hi6559_irq_data_st->irq, hi6559_irq_handler,(s32)(hi6559_irq_data_st->irq));
    if (ret < 0) 
    {
        pmic_print_error("unable to connect PMIC HI6559 IRQ!\n");
        goto out;
    }
    ret = bsp_vic_enable(hi6559_irq_data_st->irq);
    if (ret < 0) {
        pmic_print_error("enable PMIC HI6559 IRQ error!\n");
        goto out;
    }
#else
    ret = request_irq((hi6559_irq_data_st->irq), hi6559_irq_handler, IRQF_DISABLED,
            "hi6559_irq", hi6559_irq_data_st);
    if (ret < 0) 
    {
        pmic_print_error("unable to request PMIC HI6559 IRQ!\n");
        goto out;
    }
#endif

    /* �������ж� */
    for(i = 0; i < HI6559_IRQ_REG_NUM; i++)
    {
        bsp_hi6559_reg_write(HI6559_IRQ1_MASK_OFFSET + i, 0x0);
    }
    
    platform_set_drvdata(pdev, hi6559_irq_data_st);
    pmic_print_error("hi6559_irq_probe ok !\n");

    return ret;

out:
    kfree(hi6559_irq_data_st);
    return ret;

}

/*****************************************************************************
 �� �� ��  : hi6559_irq_remove
 ��������  : 
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static  s32 hi6559_irq_remove(struct platform_device *pdev)
{
    struct hi6559_irq_data *hi6559_irq_data_pt;
     
    /* get hi6559_irq_data */
    hi6559_irq_data_pt = platform_get_drvdata(pdev);
    if (NULL == hi6559_irq_data_pt) {
        pr_err("%s %d platform_get_drvdata NULL\n", __func__, __LINE__);
        return BSP_PMU_ERROR;
    }

    /*release memory*/
    kfree(hi6559_irq_data_pt);
    return BSP_PMU_OK;
}

/*HI6559 irq �豸ע��*/
static struct resource hi6559_irq_resources[] = {
    [0] = {
    },
    [1] = {
#ifdef CONFIG_MODULE_VIC
        .start  =   INT_LVL_SMART   ,
        .end    =   INT_LVL_SMART   ,
#else
        .start  =   INT_LVL_PMU   ,
        .end    =   INT_LVL_PMU    ,
#endif
        .flags  =   IORESOURCE_IRQ,
    },
};

static struct platform_device hi6559_irq_device = {
    .name =  "hi6559-irq",
    .id = 0,
    .dev = 
    {
        .platform_data  = NULL,
    },
    .num_resources = ARRAY_SIZE(hi6559_irq_resources),
    .resource = hi6559_irq_resources,
};

static struct platform_driver hi6559_irq_driver = {
    .probe = hi6559_irq_probe,
    .remove = hi6559_irq_remove,
    .driver     = 
    {
        .name   = "hi6559-irq",
    },
};

/*****************************************************************************
 �� �� ��  : hi6559_irq_init
 ��������  : ��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static s32 __init hi6559_irq_init(void)
{
    s32 ret = 0;
    ret = platform_device_register(&hi6559_irq_device);
    ret |= platform_driver_register(&hi6559_irq_driver);
    if (ret != 0)
    {
        pmic_print_error("Failed to register hi6559_hi6559_irq driver or device: %d\n", ret);
    }
    return ret;
}

/*****************************************************************************
 �� �� ��  : hi6559_irq_exit
 ��������  : ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static void __exit hi6559_irq_exit(void)
{
    platform_driver_unregister(&hi6559_irq_driver);
    platform_device_unregister(&hi6559_irq_device);
}

module_exit(hi6559_irq_exit);
subsys_initcall(hi6559_irq_init);
MODULE_LICENSE("GPL");
