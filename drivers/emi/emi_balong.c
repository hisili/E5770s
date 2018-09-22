/*lint --e{537,958,64,734}*/
#include <osl_types.h>
#include <linux/clk.h>
#include <linux/slab.h>
#include <linux/pm.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <bsp_memmap.h>
#include <hi_syscrg_interface.h>
#include <hi_syssc.h>
#include <bsp_om.h>
#include <linux/semaphore.h>
#include <osl_sem.h>
#include <linux/emi/emi_balong.h>
#include <hi_emi.h>
#include <linux/delay.h>

#define EMI_OK 0
#define EMI_ERROR 1
#define  hiemi_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_EMI, "[emi]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))
#define  hiemi_trace(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_EMI, "[emi]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))
struct clk * emi_clk = NULL;
emi_reg_t * g_emi_reg_bak = NULL;
struct st_emi {
	struct semaphore    edmatx_semmux;
	u32 edmatx_ok_cnt;
	u32 edmatx_err_cnt;
};
struct st_emi g_emi_st;

void emi_trace_level_set(u32 level)
{
    bsp_mod_level_set(BSP_MODU_EMI, level);
    printk("bsp_mod_level_set(BSP_MODU_EMI=%d, %d)\n",BSP_MODU_EMI,level);
}
void emi_enable_clk(void)
{
    int ret = 0;
    ret = clk_enable(emi_clk);
    if(ret)
    {
        hiemi_error("clk enable failed !\n");
    }
    return;
}
/*lint --e{737}*/
void emi_disable_clk(void)
{
    
    unsigned int cnt;
    unsigned int fifo_max_delay = 64;
    cnt = hi_emi_fifo_cnt();
    do
    {
        while(0 != cnt)
        {
            udelay(1);
            fifo_max_delay --;
            cnt = hi_emi_fifo_cnt();        
            if(0 == fifo_max_delay)
            {
                hiemi_error("clear fifo time out! \n");
                break;
            }
        }
        if(0 == cnt)
        {
            udelay(1);
            fifo_max_delay--;
            cnt = hi_emi_fifo_cnt();
            if(0 == cnt)
            {
                clk_disable(emi_clk);
                break;
            }
            if(0 == fifo_max_delay)
            {
                hiemi_error("clear fifo time out! \n");
                break;
            }
        }
    }while(0 != cnt); 
    
    
}
void emi_is_clk_enabled(void)
{

}

void emi_reg_read(u32 reg, u32* value)
{
    //emi_enable_clk();
    *value = readl(HI_EMI_REGBASE_ADDR_VIRT + reg);
    //emi_disable_clk();
}
void emi_reg_write(u32 reg, u32 value)
{
    //emi_enable_clk();
    writel(value , HI_EMI_REGBASE_ADDR_VIRT + reg);
    //emi_disable_clk();
}
void emi_reg_show(u32 reg)
{
    u32 value = 0;

    //emi_enable_clk();
    emi_reg_read(reg,&value);
    //emi_disable_clk();
    hiemi_error("reg %d value is %d .\n",reg,value);
}

 s32 emi_config(emi_scdul_mode_e EMI_MODE)
{
    s32 iRet = EMI_OK;

    //emi_enable_clk();
    /*8-bit ��16-bit ����*/
    if(EMI_TFT_9BIT == EMI_MODE)
    {
        set_hi_emi_smbcr0_mw(1);
        set_hi_emi_smbcr0_addr_cnt(1);

    }
    else
    {
        set_hi_emi_smbcr0_mw(0);
        set_hi_emi_smbcr0_addr_cnt(0);
    }

    switch(EMI_MODE)
    {
        case EMI_TFT_8BIT:
        case EMI_TFT_9BIT:
        {

            /* ���ö�����ʱ��*/
            set_hi_emi_smbwst1r0_wst1(24); /* ���߶����ʵȴ�ʱ��*/
            set_hi_emi_smbwst2r0_wst3(1);/* ���ζ�д����֮����*/
            set_hi_emi_smbwstoenr0_wstoen(2);/* CS��Ч�����ź���Ч�ӳ�*/
            set_hi_emi_smbwstoenr0_oendly(2); /* ���ź���Ч��Ƭѡ��Чʱ���ӳ�*/

            /* ����д����ʱ��*/
            set_hi_emi_smbwst2r0_wst2(3);/* ����д���ʵȴ�ʱ��*/
            set_hi_emi_smbwst2r0_wst3(1);/* ���ζ�д����֮����*/
            set_hi_emi_smbwstoenr0_wstoen(1);/* CS��Ч��д�ź���Ч�ӳ�*/
            set_hi_emi_smbwstwenr0_wendly(0);/* д�ź���Ч��Ƭѡ��Чʱ���ӳ�*/

        }
            break;
        case EMI_STN_8BIT_M6800:
        case EMI_STN_8BIT_I8080:
        {


            u32 u32UpDlyrSave   = 0;
            u32 u32DwnDlyrSave  = 0;
            u32 u32UpDlywSave   = 0;
            u32 u32DwnDlywSave  = 0;
            u32 u32UpDlyrTmp    = 0;
            u32 u32DwnDlyrTmp   = 0;
            u32 u32UpDlywTmp    = 0;
            u32 u32DwnDlywTmp   = 0;

            /* ������� */
            u32UpDlyrSave   = 1;
            u32DwnDlyrSave  = 9;
            u32UpDlywSave   = 2;
            u32DwnDlywSave  = 7;

             /* ���ö�����ʱ��*/
            set_hi_emi_smbwst1r0_wst1(10);/* ���߶����ʵȴ�ʱ��*/

            u32UpDlyrTmp = (u32UpDlyrSave & 0x007f);
            set_hi_emi_smbidcyr0_updlyr_l(u32UpDlyrTmp);/* PREB�ź��������CS��Ч�źŵ��ӳ�ʱ�䣬��7λ*/

            u32UpDlyrTmp = ((u32UpDlyrSave >> 7) & 0x0007);
            set_hi_emi_smbwst1r0_updlyr_h(u32UpDlyrTmp);/* PREB�ź��������CS��Ч�źŵ��ӳ�ʱ�䣬��3λ*/

            u32DwnDlyrTmp = (u32DwnDlyrSave & 0x007f);
            set_hi_emi_smbidcyr0_dwndlyr_l(u32DwnDlyrTmp); /* PREB�ź��������CS��Ч�źŵ��ӳ�ʱ�䣬��7λ*/


            u32DwnDlyrTmp = ((u32DwnDlyrSave >> 7) & 0x0007);
            set_hi_emi_smbwst1r0_dwndlyr_h(u32DwnDlyrTmp);/* PREB�ź��������CS��Ч�źŵ��ӳ�ʱ�䣬��3λ*/


            /* ���ö�����ʱ��*/
            set_hi_emi_smbwst2r0_wst2(10);/* ����д���ʵȴ�ʱ��*/
            set_hi_emi_smbwst2r0_wst3(3); /* ���߶�д���ʵȴ�ʱ��*/



            u32UpDlywTmp = (u32UpDlywSave & 0x007f);
            set_hi_emi_smbidcyr0_updlyw_l(u32UpDlywTmp);/* PREB�ź��������CS��Ч�źŵ��ӳ�ʱ�䣬��7λ*/

            u32UpDlywTmp = ((u32UpDlywSave >> 7) & 0x0007);
            set_hi_emi_smbwst1r0_updlyw_h(u32UpDlywTmp);/* PREB�ź��������CS��Ч�źŵ��ӳ�ʱ�䣬��3λ*/


            u32DwnDlywTmp = (u32DwnDlywSave & 0x007f);
            set_hi_emi_smbidcyr0_dwndlyw_l(u32DwnDlywTmp); /* PREB�ź��������CS��Ч�źŵ��ӳ�ʱ�䣬��7λ*/

            u32DwnDlywTmp = ((u32DwnDlywSave >> 7) & 0x0007);
            set_hi_emi_smbwst1r0_dwndlyw_h(u32DwnDlywTmp);/* PREB�ź��������CS��Ч�źŵ��ӳ�ʱ�䣬��3λ*/

            set_hi_emi_smbwstwenr0_wstwen(0); /* CS��Ч��д�ź���Ч�ӳ�*/
            set_hi_emi_smbwstwenr0_wendly(0);/* д�ź���Ч��Ƭѡ��Чʱ���ӳ�*/


        }
            break;
        case EMI_LCD_8BIT:
        default:
            hiemi_error("EMI SCHDULING MODE IS NOT SUPPORTED. \n");
            iRet = EMI_ERROR;
    }
    //emi_disable_clk();
    return iRet;
}

void emiCmdOut8(u8 cmd)
{
    //emi_enable_clk();
    //writel((u32)cmd, (HI_EMIMEM_REGBASE_ADDR_VIRT + EMI_BUF_WRT_CMD));
    iowrite8(cmd, HI_EMIMEM_REGBASE_ADDR_VIRT + EMI_BUF_WRT_CMD);
    //emi_disable_clk();
}
void emiDataOut8(u8 data)
{
    //emi_enable_clk();
    //writel((u32)data, HI_EMIMEM_REGBASE_ADDR_VIRT + EMI_WRT_DATA_8BIT);
    iowrite8(data, HI_EMIMEM_REGBASE_ADDR_VIRT + EMI_WRT_DATA_8BIT);
    //emi_disable_clk();
}
u8 emiCmdIn8(void)
{
    u8 value = 0;

    //emi_enable_clk();
    //value= (u8)readl(HI_EMIMEM_REGBASE_ADDR_VIRT + EMI_BUF_WRT_CMD);
    value= ioread8(HI_EMIMEM_REGBASE_ADDR_VIRT + EMI_BUF_WRT_CMD);
    //emi_disable_clk();

    return value;
}
u8 emiDataIn8(void)
{
    u8 value = 0;

    //emi_enable_clk();
    //value= (u8)readl(HI_EMIMEM_REGBASE_ADDR_VIRT + EMI_WRT_DATA_8BIT);
    value= ioread8(HI_EMIMEM_REGBASE_ADDR_VIRT + EMI_WRT_DATA_8BIT);
    //emi_disable_clk();

    return value;
}
void emi_edma_isr(u32 para1,u32 int_flag)
{
    if(int_flag&EDMA_INT_DONE)
        g_emi_st.edmatx_ok_cnt++;
    else
        g_emi_st.edmatx_err_cnt++;

    osl_sem_up(&g_emi_st.edmatx_semmux);
}
u32 emi_edma_node_size = (0x10000 - 1);/*����ڵ��С*/
u32 set_emi_edma_node_size(u32 size)
{
    if(0!=size)
    {
        emi_edma_node_size = size;
    }
    return emi_edma_node_size;
}
s32 emi_edma_transfer(dma_addr_t src,unsigned long len)
{
    edma_addr_t  edma_addr    = 0;
    s32         channel_id          = 0;
    u32      i            = 0;
    u32 ilinum;
    u32 ililast;
    u32 last_len;
    s32 ret = 0;
    s32 edma_ret = 0;
    struct edma_cb *pstNode   = NULL;
    struct edma_cb *psttemp   = NULL;
    struct edma_cb *FirstNode   = NULL;
    if(len == 0)
    {
        hiemi_error("balong SPI: balong_edma_transfer  failed��lens is wrong!\n");
        return EMI_ERROR;
    }

    channel_id = bsp_edma_channel_init(EDMA_EMI_TRANS,emi_edma_isr,0,EDMA_INT_DONE|EDMA_INT_TRANSFER_ERR|EDMA_INT_CONFIG_ERR|EDMA_INT_READ_ERR);
    if(channel_id<0)
    {
        hiemi_error("balong SPI: bsp_edma_channel_init failed!\n");
        return channel_id;
    }


    last_len = (len) % (emi_edma_node_size);/*���һ���ڵ㴫�䳤��*/

    if(last_len)/*���һ���ڵ������*/
    {
        ilinum = (len) / (emi_edma_node_size) + 1;/*����ڵ���Ŀ*/
        ililast = last_len;/*���һ���ڵ㴫�䳤��*/
    }
    else
    {
        ilinum = (len) / (emi_edma_node_size);/*����ڵ���Ŀ*/
        ililast = emi_edma_node_size;
    }

    /*��������*/
    pstNode = (struct edma_cb *)dma_alloc_coherent(NULL,(ilinum * sizeof(struct edma_cb)),
                                                             &edma_addr, GFP_DMA|__GFP_WAIT);
    if (NULL == pstNode)
    {
        ret = EMI_ERROR;
        goto early_exit;
    }

    FirstNode = pstNode;
    psttemp = pstNode;
    for (i = 0; i <= ilinum - 1; i++)
    {
        psttemp->lli = EDMA_SET_LLI(edma_addr + (i+1) * sizeof(struct edma_cb), ((i < ilinum - 1)?0:1));
        psttemp->config = EDMA_SET_CONFIG( EDMA_EMI_TRANS,   EDMA_M2P,  EDMA_TRANS_WIDTH_8 , EDMA_BUR_LEN_1 ) & (~(EDMAC_TRANSFER_CONFIG_INT_TC_ENABLE));
        /* changer src_busrt_len to 16 */
        psttemp->config &= 0xF0FFFFFF;
		psttemp->config |= EDMA_BUR_LEN_16<<24;

        /*& ~bit30*/
        psttemp->src_addr = src + i * (emi_edma_node_size);
        psttemp->des_addr = HI_EMIMEM_REGBASE_ADDR+EMI_WRT_DATA_8BIT;
        psttemp->cnt0 = ((i < ilinum - 1)?(emi_edma_node_size) : ililast);
        psttemp->bindx = 0;
        psttemp->cindx = 0;
        psttemp->cnt1  = 0;
        psttemp++;

    }

    /*��ȡ�׽ڵ�Ĵ�����ַ*/
    psttemp = bsp_edma_channel_get_lli_addr((u32)channel_id);
    if (NULL == psttemp)
    {
        ret = EMI_ERROR;
        goto early_exit0;

    }

        /*�����׽ڵ�Ĵ���*/
        psttemp->lli = FirstNode->lli;
        psttemp->config = FirstNode->config & 0xFFFFFFFE;
        psttemp->src_addr = FirstNode->src_addr;  /*�����ַ*/
        psttemp->des_addr = FirstNode->des_addr;  /*�����ַ*/
        psttemp->cnt0 = FirstNode->cnt0;
        psttemp->bindx = 0;
        psttemp->cindx = 0;
        psttemp->cnt1  = 0;

        //emi_enable_clk();

        /*����EDMA����󼴷��أ�ͨ����ѯͨ���Ƿ�busy��ȷ�������Ƿ����*/
        if (bsp_edma_channel_lli_async_start((u32)channel_id))
        {
            ret = EMI_ERROR;
            goto early_exit0;

        }
        /*�����жϷ�ʽ,��ѯ��ʽռ��cpu̫��*/
        osl_sem_down(&g_emi_st.edmatx_semmux);
#if 0
        while(EDMA_CHN_BUSY == bsp_edma_channel_is_idle(channel_id))
        {
            ;
        }
#endif
early_exit0:
        dma_free_coherent(NULL,(ilinum * sizeof(struct edma_cb)),
                              (void*)pstNode, edma_addr);
early_exit:
        //emi_disable_clk();
        edma_ret = bsp_edma_channel_free((u32)channel_id);
        if(edma_ret)
        {
            ret = EMI_ERROR;
            hiemi_error("failed to free edma channel!\n");
        }

        return ret;
}

s32 emi_probe(struct platform_device *dev)
{
    hi_syscrg_emi_soft_reset_en();
    hi_syscrg_emi_soft_reset_dis();
    hiemi_trace("************emi_reset");

    /*����Ϊnormalģʽ*/
    set_hi_sc_ctrl32_ebi_normal_mode(1);
    /* �����ź�*/
    /* ��������*/
    emi_clk = clk_get(NULL,"emi_clk");

    emi_enable_clk();
    //clk_enable(emi_clk);
    set_hi_emi_smbcr0_cspol(0);/*Ƭѡ�źŵ���Ч*/
    
#if defined(CONFIG_EMI_DMA)
    hi_emi_support_dma();
    hi_emi_dma_enable();    /* dma enable, just for v711 */
    hi_emi_gateclock_enable();
#else
    hi_emi_set_bypass();    /* ����ͬv7r2 */
#endif

    //emi_disable_clk();

    /*��ʼ��emiedma�����ź���*/
    osl_sem_init(SEM_EMPTY, &g_emi_st.edmatx_semmux);
    g_emi_st.edmatx_ok_cnt = 0;
   g_emi_st.edmatx_err_cnt = 0;

    /*g_emi_reg_bak = (struct emi_reg_t*)malloc(sizeof(struct emi_reg_t));*/
    g_emi_reg_bak = kzalloc(sizeof(emi_reg_t), GFP_KERNEL);
    if (!g_emi_reg_bak)
        return -ENOMEM;
    else
        return 0;
}
s32  emi_remove(struct platform_device *dev)
{
    clk_disable(emi_clk);
    clk_put(emi_clk);
    emi_clk = NULL;

    kfree(g_emi_reg_bak);
    g_emi_reg_bak = NULL;

    return 0;
}
void emi_reg_backup(void)
{
    emi_reg_read(HI_EMI_SMBIDCYR0_OFFSET, &(g_emi_reg_bak->smbidcyr0));
    emi_reg_read(HI_EMI_SMBWST1R0_OFFSET, &(g_emi_reg_bak->smbwst1r0));
    emi_reg_read(HI_EMI_SMBWST2R0_OFFSET, &(g_emi_reg_bak->smbwst2r0));
    emi_reg_read(HI_EMI_SMBWSTOENR0_OFFSET, &(g_emi_reg_bak->smbwstoenr0));
    emi_reg_read(HI_EMI_SMBWSTWENR0_OFFSET, &(g_emi_reg_bak->smbwstwenr0));
    emi_reg_read(HI_EMI_SMBCR0_OFFSET, &(g_emi_reg_bak->smbcr0));
    emi_reg_read(HI_EMI_SMBSR0_OFFSET, &(g_emi_reg_bak->smbsr0));
}
void emi_reg_restore(void)
{
    emi_reg_write(HI_EMI_SMBIDCYR0_OFFSET , g_emi_reg_bak->smbidcyr0);
    emi_reg_write(HI_EMI_SMBWST1R0_OFFSET , g_emi_reg_bak->smbwst1r0);
    emi_reg_write(HI_EMI_SMBWST2R0_OFFSET , g_emi_reg_bak->smbwst2r0);
    emi_reg_write(HI_EMI_SMBWSTOENR0_OFFSET , g_emi_reg_bak->smbwstoenr0);
    emi_reg_write(HI_EMI_SMBWSTWENR0_OFFSET , g_emi_reg_bak->smbwstwenr0);
    emi_reg_write(HI_EMI_SMBCR0_OFFSET , g_emi_reg_bak->smbcr0);
    //emi_reg_write(HI_EMI_SMBSR0_OFFSET , g_emi_reg_bak->smbsr0);
}
void emi_reg_bak_info(void)
{
    hiemi_error("g_emi_reg_bak->smbidcyr0 is %d \n", g_emi_reg_bak->smbidcyr0 );
    hiemi_error("g_emi_reg_bak->smbwst1r0 is %d \n", g_emi_reg_bak->smbwst1r0 );
    hiemi_error("g_emi_reg_bak->smbwst2r0 is %d \n", g_emi_reg_bak->smbwst2r0 );
    hiemi_error("g_emi_reg_bak->smbwstoenr0 is %d \n", g_emi_reg_bak->smbwstoenr0);
    hiemi_error("g_emi_reg_bak->smbwstwenr0 is %d \n", g_emi_reg_bak->smbwstwenr0);
    hiemi_error("g_emi_reg_bak->smbcr0 is %d \n", g_emi_reg_bak->smbcr0);
    hiemi_error("g_emi_reg_bak->smbsr0 is %d \n", g_emi_reg_bak->smbsr0);
}
#ifdef CONFIG_PM
int emi_resume (struct device *dev)
{
    emi_enable_clk();
    emi_reg_restore();
    emi_disable_clk();
    hiemi_trace("emi_resume ok!\n");

    return 0;
}

int emi_suspend (struct device *dev)
{
    emi_enable_clk();
    emi_reg_backup();
    emi_disable_clk();
    hiemi_trace("emi_suspend ok!\n");

    return 0;
}
static const struct dev_pm_ops emi_pm_ops ={
    .suspend = emi_suspend,
    .resume = emi_resume,
};

#define BALONG_DEV_PM_OPS (&emi_pm_ops)
#else
#define BALONG_DEV_PM_OPS NULL
#endif

static struct platform_driver balong_emi_driver = {
    .probe = emi_probe,
    .remove = emi_remove,
    .driver = {
        .name = "balong_emi",
        .owner  = THIS_MODULE,
        .pm     = BALONG_DEV_PM_OPS,
    },
};
static struct platform_device balong_emi_device =
{
    .name = "balong_emi",
    .id       = -1,
    .num_resources = 0,
};
static int __init emi_init(void)
{
    int ret = 0;

    ret = platform_device_register(&balong_emi_device);
    if(ret)
    {
        hiemi_error("Platform ipc device register is failed!\n");
        return ret;
    }
    ret = platform_driver_register(&balong_emi_driver);
    if (ret)
    {
        hiemi_error("Platform ipc deriver register is failed!\n");
        platform_device_unregister(&balong_emi_device);
        return ret;
    }
    return ret;
}
static void __exit emi_exit(void)
{
    platform_driver_unregister(&balong_emi_driver);
    platform_device_unregister(&balong_emi_device);
}

arch_initcall(emi_init);
module_exit(emi_exit);

