/*
 * kernel/driver/mfd/hi6551_irq.c
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
#include "common_hi6551.h"
#include <hi_smartstar.h>
#include "irq_hi6551.h"

/*
 * HI6551 IRQ
 */
 /*����жϴ���ص�����������*/
 hi6551_irq_st Hi6551IrqInfo[HI6551_IRQ_NR];
 struct hi6551_irq_data  *hi6551_irq_data_st;/*�ж�ȫ�ֽṹ��*/

#ifdef CONFIG_MODULE_VIC
static __inline__ void hi6551_irq_enable(void)
{
    bsp_vic_enable(INT_LVL_SMART);
}
static __inline__ void hi6551_irq_disable(void)
{
    bsp_vic_disable(INT_LVL_SMART);
}

#else
static __inline__ void hi6551_irq_enable(void)
{
    enable_irq(INT_LVL_PMU);
}
static __inline__ void hi6551_irq_disable(void)
{
    disable_irq_nosync(INT_LVL_PMU);
}
#endif
void hi6551_irq_cnt_show(void)
{
    int i = 0;

    for (i = 0; i < HI6551_IRQ_NR; i++)
    {
      pmic_print_error("hi6551 irq %d is %d!\n", i,Hi6551IrqInfo[i].cnt);
    }
}
/*�鿴��ǰ�ж�״̬*/
 void hi6551_irq_mask(unsigned int irq)
{
    hi6551_irqflags_t irq_flags = 0;
    unsigned char reg_temp = 0,offset = 0;

    if (irq > IRQ_HI6551_NR_BASE+HI6551_IRQ_NR) {
        pmic_print_error("hi6551 irq is error,please check irq=%d\n", (int)irq);
        return;
    }
    /*lint --e{746,718}*/
    spin_lock_irqsave(&hi6551_irq_data_st->irq_lock,irq_flags);
    //local_irq_save(flags);/*ֻ��Acore��������Ҫ�Ӻ˼���*/

    if ((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM2_BASE_OFFSET) {
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE);
        bsp_hi6551_reg_read(HI6551_IRQ1_MASK_OFFSET,&reg_temp);
        reg_temp |= (u8)((u32)1 << offset);
        bsp_hi6551_reg_write(HI6551_IRQ1_MASK_OFFSET,reg_temp);
    } else if((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM3_BASE_OFFSET){
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM2_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_IRQ2_MASK_OFFSET,&reg_temp);
        reg_temp |= (u8)((u32)1 << offset);
        bsp_hi6551_reg_write(HI6551_IRQ2_MASK_OFFSET,reg_temp);
    }else if((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM4_BASE_OFFSET){
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM3_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_IRQ3_MASK_OFFSET,&reg_temp);
        reg_temp |= (u8)((u32)1 << offset);
        bsp_hi6551_reg_write(HI6551_IRQ3_MASK_OFFSET,reg_temp);
    }else if((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM5_BASE_OFFSET){
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM4_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_IRQ4_MASK_OFFSET,&reg_temp);
        reg_temp |= (u8)((u32)1 << offset);
        bsp_hi6551_reg_write(HI6551_IRQ4_MASK_OFFSET,reg_temp);
    }else{
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM5_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_COUL_IRQ_MASK_OFFSET,&reg_temp);
        reg_temp |= (u8)((u32)1 << offset);
        bsp_hi6551_reg_write(HI6551_COUL_IRQ_MASK_OFFSET,reg_temp);
    }

    spin_unlock_irqrestore(&hi6551_irq_data_st->irq_lock,irq_flags);
    //local_irq_restore(flags);/*ֻ��Acore��������Ҫ�Ӻ˼���*/
}
void hi6551_irq_unmask(unsigned int irq)
{
    hi6551_irqflags_t irq_flags = 0;
    unsigned char reg_temp = 0,offset = 0;


    if (irq > IRQ_HI6551_NR_BASE+HI6551_IRQ_NR) {
        pmic_print_error("hi6551 irq is error,please check irq=%d\n", (int)irq);
        return ;
    }

    spin_lock_irqsave(&hi6551_irq_data_st->irq_lock,irq_flags);
    //local_irq_save(flags);/*ֻ��Acore��������Ҫ�Ӻ˼���*/

    if ((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM2_BASE_OFFSET) {
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE);
        bsp_hi6551_reg_read(HI6551_IRQ1_MASK_OFFSET,&reg_temp);
        reg_temp &= ~(u8)((u32)1 << offset);
        bsp_hi6551_reg_write(HI6551_IRQ1_MASK_OFFSET,reg_temp);
    } else if((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM3_BASE_OFFSET){
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM2_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_IRQ2_MASK_OFFSET,&reg_temp);
        reg_temp &= ~(u8)((u32)1 << offset);
        bsp_hi6551_reg_write(HI6551_IRQ2_MASK_OFFSET,reg_temp);
    }else if((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM4_BASE_OFFSET){
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM3_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_IRQ3_MASK_OFFSET,&reg_temp);
        reg_temp &= ~(u8)((u32)1 << offset);
        bsp_hi6551_reg_write(HI6551_IRQ3_MASK_OFFSET,reg_temp);
    }else if((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM5_BASE_OFFSET){
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM4_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_IRQ4_MASK_OFFSET,&reg_temp);
        reg_temp &= ~(u8)((u32)1 << offset);
        bsp_hi6551_reg_write(HI6551_IRQ4_MASK_OFFSET,reg_temp);
    }else{
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM5_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_COUL_IRQ_MASK_OFFSET,&reg_temp);
        reg_temp &= ~(u8)((u32)1 << offset);
        bsp_hi6551_reg_write(HI6551_COUL_IRQ_MASK_OFFSET,reg_temp);
    }

    spin_unlock_irqrestore(&hi6551_irq_data_st->irq_lock,irq_flags);
    //local_irq_restore(flags);/*ֻ��Acore��������Ҫ�Ӻ˼���*/
}
int hi6551_irq_is_masked(unsigned int irq)
{
    unsigned char reg_temp = 0,offset = 0;

    if (irq > IRQ_HI6551_NR_BASE+HI6551_IRQ_NR) {
        pmic_print_error("hi6551 irq is error,please check irq=%d\n", (int)irq);
        return HI6551_IRQ_ERROR;
    }

    if ((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM2_BASE_OFFSET) {
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE);
        bsp_hi6551_reg_read(HI6551_IRQ1_MASK_OFFSET,&reg_temp);
    } else if((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM3_BASE_OFFSET){
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM2_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_IRQ2_MASK_OFFSET,&reg_temp);
    }else if((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM4_BASE_OFFSET){
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM3_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_IRQ3_MASK_OFFSET,&reg_temp);
    }else if((irq - IRQ_HI6551_NR_BASE) < HI6551_IRQM5_BASE_OFFSET){
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM4_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_IRQ4_MASK_OFFSET,&reg_temp);
     }else{
        offset = (unsigned char)(irq - IRQ_HI6551_NR_BASE - HI6551_IRQM5_BASE_OFFSET);
        bsp_hi6551_reg_read(HI6551_COUL_IRQ_MASK_OFFSET,&reg_temp);
    }

    return  (reg_temp & (u8)((u32)1 << offset)) ;

}


int hi6551_irq_callback_register(unsigned int irq, hi6551funcptr routine, void *data)
{
    if (irq >= IRQ_HI6551_NR_BASE+HI6551_IRQ_NR) {
        pmic_print_error("hi6551 irq is error,please check irq=%d\n", (int)irq);
        return  HI6551_IRQ_ERROR;
    }

    Hi6551IrqInfo[irq].routine = routine;
    Hi6551IrqInfo[irq].data = data;
    return  HI6551_IRQ_OK;
}
void hi6551_irq_wk_handler(void)
{
    u32 reg = 0;
    u8 i = 0, reg1 = 0, reg2 = 0, reg3 = 0, reg4 = 0, reg5 = 0;    
    u8 flag = 0; /*power �����º�̧���ж�ͬʱ�����ı�־*/
    
    /*clean interrupt*/
    bsp_hi6551_reg_read(HI6551_IRQ1_OFFSET,&reg1);
    if (reg1) {
        bsp_hi6551_reg_write(HI6551_IRQ1_OFFSET, reg1);
    }

    bsp_hi6551_reg_read(HI6551_IRQ2_OFFSET,&reg2);
    if (reg2) {
        if (reg2 & 0x01)
        {
            for(i = 0; i < 8; i++)
            {
                /*�����·/ �����ж�״̬�Ĵ���*/
                bsp_hi6551_reg_write((HI6551_SCP_RECORD1_OFFSET+i), 0xFF);
            }
        }
        bsp_hi6551_reg_write(HI6551_IRQ2_OFFSET, reg2);
    }

    bsp_hi6551_reg_read(HI6551_IRQ3_OFFSET,&reg3);
    if (reg3) {
        bsp_hi6551_reg_write(HI6551_IRQ3_OFFSET, reg3);
    }

    bsp_hi6551_reg_read(HI6551_IRQ4_OFFSET,&reg4);
    if (reg4) {
        /*sim1�γ��жϣ�ʹ�ðγ���������*/
        if(reg4 & 0x04)
        {
          /*  bsp_hi6551_reg_read(HI6551_SIMCARD_EN_OFFSET,&reg_temp);
            reg_temp &= ~0x03;
            bsp_hi6551_reg_write(HI6551_SIMCARD_EN_OFFSET,reg_temp);*/

            /*�ȹرյ�Դ�����жϣ������Ȳ�ι���ʧЧ,�޸�Ϊ������У��ʿ���ʹ����*/
            /*����������Ƿ������������ʱ�䳤��Ӱ���ж���Ӧ*/
            bsp_hi6551_volt_disable(PMIC_HI6551_LDO09);
        }
        if(reg4 & 0x40)
        {
          /*  bsp_hi6551_reg_read(HI6551_SIMCARD_EN_OFFSET,&reg_temp);
            reg_temp &= ~ 0x0c;
            bsp_hi6551_reg_write(HI6551_SIMCARD_EN_OFFSET,reg_temp);*/

            /*�ȹرյ�Դ�����жϣ������Ȳ�ι���ʧЧ,�޸�Ϊ������У��ʿ���ʹ����*/
            /*����������Ƿ������������ʱ�䳤��Ӱ���ж���Ӧ*/
            bsp_hi6551_volt_disable(PMIC_HI6551_LDO11);
        }
        bsp_hi6551_reg_write(HI6551_IRQ4_OFFSET, reg4);
    }

    bsp_hi6551_reg_read(HI6551_COUL_IRQ_OFFSET,&reg5);
    if (reg5) {
        bsp_hi6551_reg_write(HI6551_COUL_IRQ_OFFSET, reg5);
    }

    reg = ((u32)reg1 | ((u32)reg2 << HI6551_IRQM2_BASE_OFFSET) | ((u32)reg3 << HI6551_IRQM3_BASE_OFFSET) | ((u32)reg4 << HI6551_IRQM4_BASE_OFFSET) | ((u32)reg5 << HI6551_IRQM5_BASE_OFFSET));

    /* �����ж�press��release�ж�ͬʱ��������flag��1 */
    if (unlikely(0x60 == (0x60 & reg1))) {  /*lint !e730*/
        flag = 1;
    }

    if (reg) {
        for (i = 0; i < HI6551_IRQ_NR; i++) {
            if ((1 == flag) && (5 == i))
            {
                /* �����ж�press��release�ж�ͬʱ�������ȴ���press�жϣ������������߼� */
                Hi6551IrqInfo[6].cnt++;    
                if (NULL != Hi6551IrqInfo[6].routine)
                    Hi6551IrqInfo[6].routine(Hi6551IrqInfo[6].data);
                Hi6551IrqInfo[5].cnt++;
                if (NULL != Hi6551IrqInfo[5].routine)
                    Hi6551IrqInfo[5].routine(Hi6551IrqInfo[5].data);
                i = i + 2;
            }
            if (reg & ((u32)1 << i)) {
                Hi6551IrqInfo[i].cnt++;
                /* handle interrupt service */
                if (NULL != Hi6551IrqInfo[i].routine)
                    Hi6551IrqInfo[i].routine(Hi6551IrqInfo[i].data);
            }
        }
    }
    pmic_print_info("**********hi6551_irq_wk_handler**********\n");
    hi6551_irq_enable();
}
#ifdef CONFIG_MODULE_VIC
void hi6551_irq_handler(unsigned int irq)
{
    /*struct hi6551_irq_data *hi6551_irq_data = data;*//*�޸�Ϊȫ�ֱ���*/
    /*�ر��ж�,�жϴ���������ɺ��*/
    hi6551_irq_disable();
    pmic_print_info("**********hi6551_irq_handler**********\n");
    queue_work(hi6551_irq_data_st->hi6551_irq_wq, &hi6551_irq_data_st->hi6551_irq_wk);

    return;
}
#else
irqreturn_t hi6551_irq_handler(int irq, void *data)
{
    struct hi6551_irq_data *hi6551_irq_data = data;
    /*�ر��ж�,�жϴ���������ɺ��*/
    hi6551_irq_disable();
    pmic_print_info("**********hi6551_irq_handler**********\n");
    queue_work(hi6551_irq_data->hi6551_irq_wq, &hi6551_irq_data->hi6551_irq_wk);

    return IRQ_HANDLED;
}
#endif


static int __init hi6551_irq_probe(struct platform_device *pdev)
{
    int ret;
    u16 i;
    u8 regvalue;
    /*struct hi6551_irq_data  *hi6551_irq_data;*//*�޸�Ϊȫ�ֱ���*/

    hi6551_irq_data_st = kzalloc(sizeof(*hi6551_irq_data_st), GFP_KERNEL);
    if (hi6551_irq_data_st == NULL) {
        pmic_print_error("hi6551 irq kzalloc is failed,please check!\n");
        return -ENOMEM;
    }
    hi6551_irq_data_st->irq = (unsigned)platform_get_irq(pdev, 0);

    spin_lock_init(&hi6551_irq_data_st->irq_lock);/*�ж�ֻ��Acoreʵ�֣���core*/

    /*��ʼ����������*/
    hi6551_irq_data_st->hi6551_irq_wq = create_singlethread_workqueue("bsp_hi6551_irq");
    INIT_WORK(&hi6551_irq_data_st->hi6551_irq_wk, (void *)hi6551_irq_wk_handler);

    /*����usb�γ���,��usb����λ���౨usb�γ���Ӱ��*/
    bsp_hi6551_reg_read(HI6551_IRQ2_OFFSET, &regvalue);
    if((regvalue & (0x01 << 2)) && hi6551_usb_state_get())
    {
        bsp_hi6551_reg_write(HI6551_IRQ2_OFFSET, 0x04);
    }
    /*��������µ��жϼĴ���*/
    for(i = 0;i < 5;i++)
    {
        bsp_hi6551_reg_read(HI6551_IRQ1_OFFSET + i,&regvalue);
        bsp_hi6551_reg_write(HI6551_IRQ1_OFFSET + i, regvalue);
    }
    /*�����·�����жϼĴ��������������ж�λ��������*/
    for(i = 0; i < 8; i++)
    {
        bsp_hi6551_reg_read(HI6551_SCP_RECORD1_OFFSET+i,&regvalue);
        bsp_hi6551_reg_write(HI6551_SCP_RECORD1_OFFSET+i,regvalue);
    }

    /*mask�����ж�*/
    for(i = 0;i < 5;i++)
    {
        bsp_hi6551_reg_write(HI6551_IRQ1_MASK_OFFSET + i, 0xff);
    }
    /*connect and enable IRQ*/
#ifdef CONFIG_MODULE_VIC
    ret = bsp_vic_connect(hi6551_irq_data_st->irq, hi6551_irq_handler,(s32)(hi6551_irq_data_st->irq));
    if (ret < 0) {
        pmic_print_error("unable to connect PMIC HI6551 IRQ!\n");
        goto out;
    }
    ret = bsp_vic_enable(hi6551_irq_data_st->irq);
    if (ret < 0) {
        pmic_print_error("enable PMIC HI6551 IRQ error!\n");
        goto out;
    }
#else
    ret = request_irq((hi6551_irq_data_st->irq), hi6551_irq_handler, IRQF_DISABLED,
            "hi6551_irq", hi6551_irq_data_st);
    if (ret < 0) {
        pmic_print_error("unable to request PMIC HI6551 IRQ!\n");
        goto out;
    }
#endif

    /*unmask�����ж�*/
    for(i = 0;i < 5;i++)
    {
        bsp_hi6551_reg_write(HI6551_IRQ1_MASK_OFFSET + i, 0x0);
    }
    /*set hi6551_irq_data in order to get at last*/
    platform_set_drvdata(pdev, hi6551_irq_data_st);
    pmic_print_error("hi6551_irq_probe ok !\n");

    return 0;

out:
    kfree(hi6551_irq_data_st);
    return ret;

}
static  int hi6551_irq_remove(struct platform_device *pdev)
{
    struct hi6551_irq_data *hi6551_irq_data_pt;
    /*get hi6551_irq_data*/
    hi6551_irq_data_pt = platform_get_drvdata(pdev);
    if (NULL == hi6551_irq_data_pt) {
        pr_err("%s %d platform_get_drvdata NULL\n", __func__, __LINE__);
        return -1;
    }

    /*release memory*/
    kfree(hi6551_irq_data_pt);
#if 0
    /* cleanup irqchip */
    for (i = IRQ_HI6551_OTMP; i <= IRQ_HI6551_VBAT_INT; i++) {
        irq_set_chip_and_handler(i, NULL, NULL);
    }
#endif
    return 0;
}
/*#ifdef CONFIG_PM*/
#if 0
static int hi6551_irq_suspend(struct platform_device *pdev, pm_message_t state)
{
    struct hi6551_irq_data *hi6551_irq_data;

    printk("hi6551 hi6551 irq entry suspend successfully");

    /*get hi6551_irq_data*/
    hi6551_irq_data = platform_get_drvdata(pdev);
    if (NULL == hi6551_irq_data) {
        pr_err("%s %d platform_get_drvdata NULL\n", __func__, __LINE__);
        return -1;
    }

    return 0;
}
static int hi6551_irq_resume(struct platform_device *pdev)
{
    int ret = 0;
    struct hi6551_irq_data *hi6551_irq_data;

    printk("hi6551 hi6551 irq entry resume successfully");
    /*get hi6551_irq_data*/
    hi6551_irq_data = platform_get_drvdata(pdev);
    if (NULL == hi6551_irq_data) {
        pr_err("%s %d platform_get_drvdata NULL\n", __func__, __LINE__);
        return -1;
    }

    return ret;
}
#endif
/*HI6551 irq �豸ע��*/
static struct resource hi6551_irq_resources[] = {
    [0] = {
    },
    [1] = {
#ifdef CONFIG_MODULE_VIC
        .start =  INT_LVL_SMART   ,
        .end =  INT_LVL_SMART   ,
#else
        .start =  INT_LVL_PMU   ,
        .end =  INT_LVL_PMU    ,
#endif
        .flags   = IORESOURCE_IRQ,
    },
};
static struct platform_device hi6551_irq_device = {
    .name =  "hi6551-irq",
    .id = 0,
    .dev = {
        .platform_data  = NULL,
    },
    .num_resources = ARRAY_SIZE(hi6551_irq_resources),
    .resource = hi6551_irq_resources,
};
static struct platform_driver hi6551_irq_driver = {
    .probe = hi6551_irq_probe,
    .remove = hi6551_irq_remove,
/*    #ifdef CONFIG_PM */
#if 0
    .suspend = hi6551_irq_suspend,
    .resume = hi6551_irq_resume,
#endif
    .driver     = {
        .name   = "hi6551-irq",
    },
};
static int __init hi6551_irq_init(void)
{
    int ret = 0;
    ret = platform_device_register(&hi6551_irq_device);
    ret |= platform_driver_register(&hi6551_irq_driver);
    if (ret != 0)
        printk("Failed to register hi6551_hi6551_irq driver or device: %d\n", ret);
    return ret;
}
static void __exit hi6551_irq_exit(void)
{
    platform_driver_unregister(&hi6551_irq_driver);
    platform_device_unregister(&hi6551_irq_device);
}
module_exit(hi6551_irq_exit);
//late_initcall(hi6551_irq_init);
subsys_initcall(hi6551_irq_init);
MODULE_LICENSE("GPL");
