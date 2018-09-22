


#include "bsp_dump.h"
#include "bsp_nvim.h"
#include "bsp_clk.h"
#include "utrace_balong.h"

/* ��ʼ����־ */
u32 g_ul_init_flag = false;
/* ���������־ */
u32 g_ul_capt_start_flag = false;
/* ETB���ݵ�����ַ */
u32 g_ul_etb_data_base = 0;
/* ETB���ݷ���ռ䳤�� */
u32 g_ul_etb_data_len = 0;
/* ETB���ݳ��� */
u32 g_ul_etb_len = 0;



void utrace_reg_read(trace_config_enum_u32 config, u32 reg, u32 * value)
{
    /* ��������Ŀ���ȡ��Ӧ�Ĵ��� */
    switch(config)
    {
        case TRACE_STM:
            *value = readl(STM_REG_BASE + reg);
            break;

        case TRACE_PTM0:
            *value = readl(PTM0_REG_BASE + reg);
            break;

        case TRACE_PTM1:
            *value = readl(PTM1_REG_BASE + reg);
            break;

        case TRACE_FUNNEL:
            *value = readl(FUNNEL_REG_BASE + reg);
            break;

        case TRACE_ETF:
            *value = readl(ETF_REG_BASE + reg);
            break;

        case TRACE_ETR:
            *value = readl(ETR_REG_BASE + reg);
            break;

        default:
            break;
    }
}


void utrace_reg_write(trace_config_enum_u32 config, u32 reg, u32 value)
{
    /* ��������Ŀ��д����Ӧ�Ĵ��� */
    switch(config)
    {
        case TRACE_STM:
            writel(value, STM_REG_BASE + reg);
            break;

        case TRACE_PTM0:
            writel(value, PTM0_REG_BASE + reg);
            break;

        case TRACE_PTM1:
            writel(value, PTM1_REG_BASE + reg);
            break;

        case TRACE_FUNNEL:
            writel(value, FUNNEL_REG_BASE + reg);
            break;

        case TRACE_ETF:
            writel(value, ETF_REG_BASE + reg);
            break;

        case TRACE_ETR:
            writel(value, ETR_REG_BASE + reg);
            break;

        default:
            break;
    }
}


void utrace_reg_getbits(trace_config_enum_u32 config, u32 reg, u32 pos, u32 bits, u32 * value)
{
    u32 reg_value = 0;

    /* ��������Ŀ���ȡ��Ӧ�Ĵ��� */
    utrace_reg_read(config, reg, &reg_value);
    /* ���ݼĴ���ֵȡ��Ӧλ */
    *value = (reg_value >> pos) & (((u32)1 << (bits)) - 1);
}


void utrace_reg_setbits(trace_config_enum_u32 config, u32 reg, u32 pos, u32 bits, u32 value)
{
    u32 reg_value = 0;

    /* ��������Ŀ���ȡ��Ӧ�Ĵ��� */
    utrace_reg_read(config, reg, &reg_value);
    /* ����д��Ĵ�����Ŀ��ֵ */
    reg_value = (reg_value & (~((((u32)1 << (bits)) - 1) << (pos)))) | ((u32)((value) & (((u32)1 << (bits)) - 1)) << (pos));
    /* д��Ŀ�ļĴ��� */
    utrace_reg_write(config, reg, reg_value);
}



void utrace_funnel_config(funnel_port_enum_u32 port)
{
    /* ʹ��funnel��Ӧ�˿� */
    utrace_reg_setbits(TRACE_FUNNEL, FUNNEL_CTRL, port, 1, 1);
}


void utrace_ptm_config(trace_config_enum_u32 index)
{
    /* ���PowerDown */
    utrace_reg_setbits(index, PTM_CTRL, 0, 1, 0x0);
    /* ����Program Bit, bit10 */
    utrace_reg_setbits(index, PTM_CTRL, 10, 1, 0x1);
    /* ����Trace ID */
    utrace_reg_write(index, PTM_TRACEID, index + 1);
    /* ���õ�ַ�������� */
    utrace_reg_write(index, PTM_ACTR(0), 0x1);
    utrace_reg_write(index, PTM_ACTR(1), 0x1);
    /* ����TraceEnable Event(�������) */
    utrace_reg_write(index, PTM_TEEVR, 0x376f);
    /* ����TraceEnable������(�������) */
    utrace_reg_write(index, PTM_TECR, 0x01000000);
    /* ����Trigger Event */
    utrace_reg_write(index, PTM_TRIGGER, 0x406F);
    /* ����Timestamp Event */
    utrace_reg_write(index, PTM_TSEVR, 0x406F);
    /* ȥʹ��Timestamp */
    utrace_reg_setbits(index, PTM_CTRL, 28, 1, 0x0);
    /* ����Context ID, Bit14:15 */
    utrace_reg_setbits(index, PTM_CTRL, 14, 2, 0x3);
    /* ����Sync Frequency�Ĵ��� */
    utrace_reg_write(index, PTM_SYNCFR, 0x400);
}


void utrace_ptm_enable(trace_config_enum_u32 index)
{
    utrace_reg_setbits(index, PTM_CTRL, 10, 1, 0x0);
}


void utrace_ptm_disable(trace_config_enum_u32 index)
{
    utrace_reg_setbits(index, PTM_CTRL, 10, 1, 0x1);
}



void utrace_reg_unlock(void)
{
    /* PTM0���� */
    utrace_reg_write(TRACE_PTM0, PTM_LOCK_ACCESS, UTRACE_UNLOCK_CODE);
    /* FUNNEL���� */
    utrace_reg_write(TRACE_FUNNEL, FUNNEL_LOCK_ACCESS, UTRACE_UNLOCK_CODE);
    /* ETF���� */
    utrace_reg_write(TRACE_ETF, ETF_LOCK_ACCESS, UTRACE_UNLOCK_CODE);
    /* ETR���� */
    utrace_reg_write(TRACE_ETR, ETR_LOCK_ACCESS, UTRACE_UNLOCK_CODE);
}


void utrace_reg_lock(void)
{
    /* PTM0���� */
    utrace_reg_write(TRACE_PTM0, PTM_LOCK_ACCESS, UTRACE_LOCK_CODE);
    /* FUNNEL���� */
    utrace_reg_write(TRACE_FUNNEL, FUNNEL_LOCK_ACCESS, UTRACE_LOCK_CODE);
    /* ETF���� */
    utrace_reg_write(TRACE_ETF, ETF_LOCK_ACCESS, UTRACE_LOCK_CODE);
    /* ETR���� */
    utrace_reg_write(TRACE_ETR, ETR_LOCK_ACCESS, UTRACE_LOCK_CODE);
}


void utrace_stm_config(u32 port)
{
    /* ATB Triggerʹ�� */
    utrace_reg_write(TRACE_STM, STM_TRIGGER_CTRL, 0x8);
    /* stimulus portʹ�� */
    utrace_reg_setbits(TRACE_STM, STM_PORT_ENABLE, port, 1, (u32)1 << port);
    /* stimulus trigger portʹ�� */
    utrace_reg_setbits(TRACE_STM, STM_PORT_TRIGGER_ENABLE, port, 1, (u32)1 << port);
    /* Trace ID���� */
    utrace_reg_setbits(TRACE_STM, STM_TRACE_CTRL, 16, 7, TRACE_STM + 1);
}


void utrace_stm_enable(void)
{
    utrace_reg_setbits(TRACE_STM, STM_TRACE_CTRL, 0, 1, 1);
}


void utrace_stm_disable(void)
{
    utrace_reg_setbits(TRACE_STM, STM_TRACE_CTRL, 0, 1, 0);
}


void utrace_etb_config(void)
{
    /* ����ΪETF��ӲFIFOģʽ */
    //utrace_reg_setbits(TRACE_ETF, ETF_MODE, 0, 2, TMC_MODE_HARDWARE_FIFO);
    /* ����ΪETB��ѭ��buffer */
    utrace_reg_setbits(TRACE_ETF, ETF_MODE, 0, 2, TMC_MODE_CIRCULAR_BUFF);
    /* ����FFCR EnTl(bit1), EnFt(bit0) */
    utrace_reg_setbits(TRACE_ETF, ETR_FORMAT_FLUSH_CTRL, 0, 2, 0x3);
    /* ����ˮ�� */
    utrace_reg_write(TRACE_ETF, ETF_BUF_WATER_MARK, 0x3);
}


void utrace_etr_config(etr_config_t * config)
{
    /* ����ETR DDR����ռ��С */
    utrace_reg_write(TRACE_ETR, ETR_RAM_SIZE, (config->buf_size)/4);
    /* ����ETR����ģʽ */
    utrace_reg_setbits(TRACE_ETR, ETF_MODE, 0, 2, config->mode);
    /* ����FFCR EnTl(bit1), EnFt(bit0) */
    utrace_reg_setbits(TRACE_ETR, ETR_FORMAT_FLUSH_CTRL, 0, 2, 0x3);
    /* ����ˮ�� */
    utrace_reg_write(TRACE_ETR, ETF_BUF_WATER_MARK, UTRACE_WATER_MARK);
    /* ����DDR��ַ */
    utrace_reg_write(TRACE_ETR, ETR_DATA_BUF_ADDR, config->buf_addr);
}


void utrace_etb_enable(void)
{
    utrace_reg_write(TRACE_ETF, ETR_CTRL, 0x1);
}


s32 utrace_etb_stop(void)
{
    int i;
    u32 reg_value;

    /* FFCR StopOnFl */
    utrace_reg_setbits(TRACE_ETF, ETF_FORMAT_FLUSH_CTRL, 12, 1, 1);
    /* FFCR FlushMem */
    utrace_reg_setbits(TRACE_ETF, ETF_FORMAT_FLUSH_CTRL, 6, 1, 1);

    /* �ȴ�TMCReady */
    for(i=0; i<MAX_WAIT_CNT; i++)
    {
        utrace_reg_read(TRACE_ETF, ETF_STATUS, &reg_value);
        /* bit2ΪTMCReadyָʾλ */
        if(0 != (reg_value & 0x4))
        {
            break;
        }
    }

    /* ��ʱ�ж� */
    if(i >= MAX_WAIT_CNT)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UTRACE, "%s: stop etb timeout\n", __FUNCTION__);
        return BSP_ERROR;
    }

    return BSP_OK;
}


void utrace_etb_disable(void)
{
    /* ȥʹ��ETB */
    utrace_reg_write(TRACE_ETF, ETF_CTRL, 0);
}


void utrace_etr_enable(void)
{
    utrace_reg_write(TRACE_ETR, ETR_CTRL, 0x1);
}


s32 utrace_etr_disable(void)
{
    int i;
    u32 reg_value;

    /* FFCR StopOnFl */
    utrace_reg_setbits(TRACE_ETR, ETR_FORMAT_FLUSH_CTRL, 12, 1, 1);
    /* FFCR FlushMem */
    utrace_reg_setbits(TRACE_ETR, ETR_FORMAT_FLUSH_CTRL, 6, 1, 1);
    /* �ȴ�TMCReady */
    for(i=0; i<MAX_WAIT_CNT; i++)
    {
        utrace_reg_read(TRACE_ETR, ETR_STATUS, &reg_value);
        /* bit2ΪTMCReadyָʾλ */
        if(0 != (reg_value & 0x4))
        {
            break;
        }
    }

    /* ��ʱ�ж� */
    if(i >= MAX_WAIT_CNT)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UTRACE, "%s: stop etr timeout\n", __FUNCTION__);
        return BSP_ERROR;
    }

    /* ȥʹ��ETR */
    utrace_reg_write(TRACE_ETR, ETR_CTRL, 0);

    return BSP_OK;
}



s32 utrace_dump_etb(void)
{
    u32     reg_value;
    u32     i;
    u32  *  data;

    utrace_reg_unlock();
    
    /* ֹͣETB */
    if(BSP_OK != utrace_etb_stop())
    {
        utrace_reg_lock();
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UTRACE, "%s: stop etb fail\n", __FUNCTION__);
        return BSP_ERROR;
    }
    memset((void *)g_ul_etb_data_base, 0x0, g_ul_etb_data_len);
    data = (u32 *)(g_ul_etb_data_base + 8);
    for(i=0; i<UTRACE_ONSTART_BUF_SIZE/4; i++)
    {
        utrace_reg_read(TRACE_ETF, ETF_RAM_RD_DATA, &reg_value);
        *data = reg_value;
        data++;
        if(reg_value == 0xffffffff)
        {
            break;
        }          
    }

    /* 0-3�ֽڴ�ű�ʶ�� */
    *((u32 *)g_ul_etb_data_base) = (u32)UTRACE_MAGIC_NUM;
    /* 4-7���ֽڴ��ETB���ݳ��� */
    *((u32 *)g_ul_etb_data_base + 1) = i*4; /* [false alarm]:����Fortify���� */

    printk("%s: dump etb data ok(dst_buf addr: 0x%x)\n", __FUNCTION__, g_ul_etb_data_base);
    
    utrace_reg_lock();

    return BSP_OK;
}


void utrace_capt_config(void)
{
    utrace_reg_unlock();
    utrace_etb_disable();
    utrace_etb_config();
    utrace_etb_enable();
    utrace_funnel_config(FUNNEL_PTM_APPA9_PORT);
    utrace_ptm_disable(TRACE_PTM0);
    utrace_ptm_config(TRACE_PTM0);
    utrace_ptm_enable(TRACE_PTM0);
    utrace_reg_lock();
}


s32 bsp_utrace_init(void)
{
    dump_nv_s    dump_nv;
    char *       dst_buf;
    u32          len;
    struct clk * cs_clk;

    if(true == g_ul_init_flag)
    {
        return BSP_OK;
    }
    
    /*lint -save -e539*/
	cs_clk = clk_get(NULL, "cs_clk");
	if(BSP_OK != clk_enable(cs_clk))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UTRACE, "%s: CoreSight clk open failed.\n", __FUNCTION__);
		return BSP_ERROR;
	}
    /*lint -restore +e539*/

    /* ��ȡ�쳣������ */
    if(BSP_OK != bsp_dump_get_buffer(DUMP_SAVE_MOD_UTRACE, &dst_buf, &len))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UTRACE, "%s:  get dump buffer fail\n", __FUNCTION__);
        return BSP_ERROR;
    }
    if(len < UTRACE_ONSTART_BUF_SIZE)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UTRACE, "%s:  dump buffer(0x%x) less than data buffer(0x%x)\n", __FUNCTION__, len, UTRACE_ONSTART_BUF_SIZE);
        return BSP_ERROR;
    }
    g_ul_etb_data_base = (u32)dst_buf;
    g_ul_etb_data_len  = len;

    /* ͨ��NV���Ƽ���Ƿ����� */
    if(BSP_OK != bsp_nvm_read(NVID_DUMP, (u8 *)&dump_nv, sizeof(dump_nv_s)))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UTRACE, "%s:  read nv %d fail\n", __FUNCTION__, NVID_DUMP);
        return BSP_ERROR;
    }

    /* ���APP A9 */
    if((1 == dump_nv.traceOnstartFlag) && (APPA9_ONLY == dump_nv.traceCoreSet))
    {
        g_ul_capt_start_flag = true;
        utrace_capt_config();
    }
    else
    {
        g_ul_init_flag = true;
        return BSP_OK;
    }

    /* EXC DUMPע�� */
    if(bsp_dump_register_hook(DUMP_SAVE_MOD_UTRACE, (dump_save_hook)utrace_dump_etb) != BSP_OK)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_UTRACE, "%s:  dump register fail\n", __FUNCTION__);
        return BSP_ERROR;
    }
    
    g_ul_init_flag = true;

    printk("utrace init ok\n");
    return BSP_OK;
}


void bsp_utrace_stop(void)
{
    if(true == g_ul_capt_start_flag)
    {
        utrace_reg_unlock();
        utrace_ptm_disable(TRACE_PTM0);
        utrace_reg_lock();
    }
}


void utrace_show_etb_base(void)
{   
    printk("etb base addr: 0x%x len: 0x%x\n", g_ul_etb_data_base, g_ul_etb_data_len);
}


void bsp_utrace_suspend(void)
{
    if(false == g_ul_capt_start_flag)
    {
        return;
    }

    utrace_reg_unlock();
    utrace_ptm_disable(TRACE_PTM0);   
    utrace_etb_stop();
    utrace_etb_disable();
    utrace_reg_lock();   
}


void bsp_utrace_resume(void)
{
    if(false == g_ul_capt_start_flag)
    {
        return;
    }
    
    utrace_reg_unlock();
    utrace_etb_disable();
    utrace_etb_config();

    utrace_etb_enable();
    utrace_funnel_config(FUNNEL_PTM_APPA9_PORT);
    utrace_ptm_disable(TRACE_PTM0);
    utrace_ptm_config(TRACE_PTM0);
    utrace_ptm_enable(TRACE_PTM0);

    utrace_reg_lock();
}


/*lint -save -e19*/
module_init(bsp_utrace_init);
/*lint -restore +e19*/


