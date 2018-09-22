
#include <linux/gfp.h>
#include <osl_module.h>
#include <linux/dma-mapping.h>
#include <osl_bio.h>
#include <bsp_clk.h>
#include "kdf.h"

/*lint --e{550} */

int kdf_start_channel(void);
void kdf_move_bdq_w_pos(void);
void kdf_move_rdq_r_pos(void);

static struct kdf_s ch4_info = {0, 0, 0, 0, BD_RD_NUM, 0, 0, 0, 0, NULL};

/*****************************************************************************
* �� �� ��  : kdf_reg_init
*
* ��������  : A��KDF�Ĵ������ã����ڼ���HASHֵ����C������֮ǰʹ��
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
void kdf_reg_init(void)
{
	u32 reg_val = 0;
	int i = 0;

	/*��λch4*/
	writel(0x7, HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_SOFTRESET_OFFSET);
	i = 1000;
	do
	{
		reg_val = readl(HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_SOFTRESET_OFFSET);
		i--;
	}while((0 != (reg_val & 0x7)) && (i > 0));
	if(i <= 0)
	{
		return;
	}

	/*����BD�Ĵ���*/
	writel(ch4_info.bdq_real_addr, HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_BDQ_BADDR_OFFSET);
	writel(BD_RD_NUM - 1, HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_BDQ_SIZE_OFFSET);

	/*����RD�Ĵ���*/
	writel(ch4_info.rdq_real_addr, HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_RDQ_BADDR_OFFSET);
	writel(BD_RD_NUM - 1, HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_RDQ_SIZE_OFFSET);

    /*ʹ��KDFͨ��*/
	writel(0x1, HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_EN_OFFSET);

    /* ����KDFͨ��config�Ĵ���*/
    reg_val= CHN_IV_SEL| (CHN_RDQ_CTRL << CHN_RDQCTRL_BIT)| KDF_CHN_USRFIELD_LEN << CHN_USRFIELDLEN_BIT;/* [false alarm]:�� */
	writel(reg_val, HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_CONFIG_OFFSET);

    /* KeyRam�е���������Ϊ0��ֻʹ����0������λ��*/
    for(i = 0; i < KDF_SHA_KEY_LENGTH; i += 4)
    {
        writel(0, (volatile void *)(HI_CIPHER_BASE_ADDR_VIRT + HI_KEY_RAM_OFFSET + KEY_INDEX * CIPHER_KEY_LEN + i));/*lint !e737*/
    }

}

/*****************************************************************************
* �� �� ��  : kdf_init
*
* ��������  : A��KDF���пռ������ʼ�������ڼ���HASHֵ����C������֮ǰʹ��
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : 0    : ��ȷ
*             ���� : ����
*****************************************************************************/
int kdf_init(void)
{
	/*����RDQ��BDQ�ռ�*/
	ch4_info.buffer_virt_addr =
		(u32)dma_alloc_coherent(NULL, RDQ_SIZE + BDQ_SIZE + KDF_SHA_S_LENGTH_MAX + CIPHER_ALIGN_LEN, &(ch4_info.buffer_real_addr), GFP_KERNEL);
	if(!ch4_info.buffer_virt_addr || !ch4_info.buffer_real_addr)
	{
		dma_free_coherent(NULL, RDQ_SIZE + BDQ_SIZE + KDF_SHA_S_LENGTH_MAX + CIPHER_ALIGN_LEN, (void*)ch4_info.buffer_virt_addr, ch4_info.buffer_real_addr);
		return CIPHER_NULL_PTR;
	}

	ch4_info.bdq_virt_addr = (ch4_info.buffer_virt_addr + CIPHER_ALIGN_LEN) & ~CIPHER_ALIGN_LEN;
	ch4_info.bdq_real_addr = (ch4_info.buffer_real_addr + CIPHER_ALIGN_LEN) & ~CIPHER_ALIGN_LEN;
	ch4_info.rdq_virt_addr = ch4_info.bdq_virt_addr + BDQ_SIZE;
	ch4_info.rdq_real_addr = ch4_info.bdq_real_addr + BDQ_SIZE;
	ch4_info.sha_s_buff_virt_addr = ch4_info.rdq_virt_addr + RDQ_SIZE;
	ch4_info.sha_s_buff_real_addr = ch4_info.rdq_real_addr + RDQ_SIZE;
	ch4_info.cifer_clk = clk_get(NULL, "cipher_clk");
	if(IS_ERR(ch4_info.cifer_clk))
	{
		return CIPHER_NULL_PTR;
	}

	memset((void*)ch4_info.bdq_virt_addr, 0, BDQ_SIZE);
	memset((void*)ch4_info.rdq_virt_addr, 0, RDQ_SIZE);
	memset((void*)ch4_info.sha_s_buff_virt_addr, 0, KDF_SHA_S_LENGTH_MAX);

    return CIPHER_SUCCESS;
}

int kdf_bd_configure(KDF_BDCONFIG_INFO_S *stKeyCfgInfo)
{
    KDF_BD_SCPT_S *p_w_addr = (KDF_BD_SCPT_S *)(ch4_info.bdq_virt_addr);
	u32 reg_val_bdq_ptr;

	reg_val_bdq_ptr = readl(HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_BDQ_PTR_OFFSET);
	reg_val_bdq_ptr = reg_val_bdq_ptr & 0x3FF;
	p_w_addr += reg_val_bdq_ptr;

    p_w_addr->u32KdfConfig= 0                                           |
		                    (stKeyCfgInfo->enShaKeySource & 0x3) << 0x2 |
                            (stKeyCfgInfo->enShaSSource & 0x1)   << 0x4 |
                            (stKeyCfgInfo->u32ShaKeyIndex & 0xf) << 0x7 |
                            (stKeyCfgInfo->u32ShaSIndex & 0xf)   << 0xb |
                            (stKeyCfgInfo->u32Length & 0x1ff)    << 0xf |
                            (stKeyCfgInfo->u32DestIndex & 0xf)   << 0x18;

    p_w_addr->u32Address = (u32)(stKeyCfgInfo->pAddress);

    return CIPHER_SUCCESS;
}

void kdf_move_rdq_r_pos(void)
{
	u32 reg_val_rdq_rwptr;
	u32 reg_val_rdq_size;

	reg_val_rdq_rwptr = readl(HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_RDQ_PTR_OFFSET);
	reg_val_rdq_size  = readl(HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_RDQ_SIZE_OFFSET);
	reg_val_rdq_rwptr = (reg_val_rdq_rwptr & 0x3FF0000);
	reg_val_rdq_rwptr = reg_val_rdq_rwptr >> 16;
	reg_val_rdq_rwptr += 1;
	reg_val_rdq_size++;
	reg_val_rdq_rwptr = reg_val_rdq_rwptr % reg_val_rdq_size;
	/*reg_val_rdq_rwptr = ((reg_val_rdq_rwptr & 0x3FF0000) >> 16 + 1) % (1 + reg_val_rdq_size);*/
	reg_val_rdq_rwptr = reg_val_rdq_rwptr << 16;/* [false alarm]:�� */
	writel(reg_val_rdq_rwptr, HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_RDQ_PTR_OFFSET);
}

void kdf_move_bdq_w_pos(void)
{
	u32 reg_val_bdq_rwptr;
	u32 reg_val_bdq_size;

	reg_val_bdq_rwptr = readl(HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_BDQ_PTR_OFFSET);
	reg_val_bdq_size  = readl(HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_BDQ_SIZE_OFFSET);
	reg_val_bdq_rwptr = reg_val_bdq_rwptr & 0x3FF;
	reg_val_bdq_rwptr += 1;
	reg_val_bdq_size++;
	reg_val_bdq_rwptr = reg_val_bdq_rwptr % reg_val_bdq_size;/* [false alarm]:�� */
	/*reg_val_bdq_rwptr = (reg_val_bdq_rwptr & 0x3FF + 1) % (1 + reg_val_bdq_size);*/
	writel(reg_val_bdq_rwptr, HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_BDQ_PTR_OFFSET);
}

int kdf_start_channel(void)
{
    u32 reg_val;
    KDF_RD_SCPT_S *pCurRDAddr = NULL;
	s32 delay_loops = 20000;/*ѭ��20000�Σ�ÿ���ӳ�1us�����ӳ�20000us*/

	/* �ƶ��Ĵ���дָ�� */
	kdf_move_bdq_w_pos();

	do
    {
		reg_val = readl(HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_EN_OFFSET);
        delay_loops = delay_loops - 1;
		/*delay(1);˯1us*/
    }
    while((reg_val & 0x80000000) && (delay_loops > 0));
	if(delay_loops <= 0)
	{
		return CIPHER_TIME_OUT;
	}

    /* ��ȡ��ǰ��RD������*/ 
	reg_val = readl((volatile void *)(HI_CIPHER_BASE_ADDR_VIRT + HI_CH4_RDQ_PTR_OFFSET));
	reg_val = (reg_val & 0x3FF0000) >> 16;
    pCurRDAddr = (KDF_RD_SCPT_S *)(ch4_info.rdq_virt_addr) + reg_val;
    /* ���RD��Чλ*/
    pCurRDAddr->u32KdfConfig &= (~0x80000000);
    /* �ж��Ƿ��������Լ�����*/
    if(CIPHER_STAT_CHECK_ERR == ((pCurRDAddr->u32KdfConfig >> 29) & 0x3))
    {
        return CIPHER_CHECK_ERROR;
    }
	/* �ƶ��Ĵ����е�RD����ַ*/
	kdf_move_rdq_r_pos();

    return CIPHER_SUCCESS;
}

int kdf_hash_make(void * sha_s_addr, u32 sha_s_len)
{
    KDF_BDCONFIG_INFO_S stBDCfgInfo;
	u32 i = 0;

    stBDCfgInfo.enShaKeySource  = SHA_KEY_SOURCE_KEYRAM;           /*sha_key����ȥkey ram��ȡ*/ 
    stBDCfgInfo.u32ShaKeyIndex  = KEY_INDEX;                       /*sha_s��key ram�е�λ��*/
    stBDCfgInfo.u32ShaSIndex    = 0;                               /*sha_s������Դ��DDR������λ������ν*/
    stBDCfgInfo.u32Length       = sha_s_len - 1;                   /*Ӧ�ü�1���߼����1*/
    stBDCfgInfo.u32DestIndex    = KEY_INDEX;                       /*���ɵ�HASH����̶�����key ram�ĵ�15��λ��*/
    stBDCfgInfo.pAddress        = (void*)(ch4_info.sha_s_buff_real_addr);   /*sha_s�ڴ��ַ*/
	stBDCfgInfo.enShaSSource    = SHA_S_SOURCE_DDR;                /*sha_s������Դ��DDR*/

	for(i = 0; i < sha_s_len; i++)
	{
		*((u8 *)(ch4_info.sha_s_buff_virt_addr) + i) = *((u8*)sha_s_addr + i);
	}
    kdf_bd_configure(&stBDCfgInfo);
    return kdf_start_channel();
}
int kdf_hash_setkey(void * key_addr)
{
	int i = 0;
    u32 val = 0;
	
	if(!key_addr)
	{
		return CIPHER_NULL_PTR;
	}
	for(i = 0; i < CIPHER_KEY_LEN; i += 4)
	{
        val = (u32)readl((volatile void *)((char*)key_addr + i));
		writel(val, (volatile void *)(HI_CIPHER_BASE_ADDR_VIRT + HI_KEY_RAM_OFFSET + KEY_INDEX * CIPHER_KEY_LEN + i));/*lint !e737*/
	}
	return 0;
}

int kdf_result_hash_get(void * out_hash)
{
	int i = 0;
    u32 val = 0;
	
	if(!out_hash)
		return CIPHER_NULL_PTR;

    for(i = 0; i < CIPHER_KEY_LEN; i += 4)
    {
        val = readl((volatile void *)(HI_CIPHER_BASE_ADDR_VIRT + HI_KEY_RAM_OFFSET + KEY_INDEX * CIPHER_KEY_LEN + i));/*lint !e737*/
        writel(val, (volatile void *)((char*)out_hash + i));
    }
	return 0;
}

int kdf_hash_init(void)
{
	if(kdf_init())
		return -1;
	if(clk_set_rate(ch4_info.cifer_clk, PERIPLL_FOUNTPOST / CONFIG_CIPHER_CLK_DIV))
		return -1;
	if(clk_enable(ch4_info.cifer_clk))
	{
		return -1;
	}
	kdf_reg_init();
	return 0;
}

void kdf_hash_exit(void)
{
	clk_disable(ch4_info.cifer_clk);
	dma_free_coherent(NULL,RDQ_SIZE + BDQ_SIZE + KDF_SHA_S_LENGTH_MAX + CIPHER_ALIGN_LEN,(void*)ch4_info.buffer_virt_addr,ch4_info.buffer_real_addr);
}

