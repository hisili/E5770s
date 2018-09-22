
#ifndef __BSP_DSP_H__
#define __BSP_DSP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <bsp_shared_ddr.h>
#ifdef __VXWORKS__
#include <bsp_dpm.h>
#endif



#define DSP_IMAGE_NAME "DSP"
#define DSP_IMAGE_STATE_OK (0x5312ABCD)

#define HIFI_MEM_BEGIN_CHECK32_DATA (0x55AA55AA)
#define HIFI_MEM_END_CHECK32_DATA   (0xAA55AA55)

#define HIFI_SEC_MAX_NUM            (32)
#define HIFI_DYNAMIC_SEC_MAX_NUM    (HIFI_SEC_MAX_NUM)

#define HIFI_SHARE_MEMORY_ADDR      (SHM_MEM_HIFI_ADDR)
#define HIFI_SHARE_MEMORY_SIZE      (SHM_MEM_HIFI_SIZE)


/*****************************************************************************
 ʵ �� ��  : DRV_HIFI_IMAGE_SEC_TYPE_ENUM
 ��������  : ���������
*****************************************************************************/
enum DRV_HIFI_IMAGE_SEC_TYPE_ENUM {
    DRV_HIFI_IMAGE_SEC_TYPE_CODE = 0,        /* ���� */
    DRV_HIFI_IMAGE_SEC_TYPE_DATA,            /* ���� */
    DRV_HIFI_IMAGE_SEC_TYPE_BUTT,
};

/*****************************************************************************
 ʵ �� ��  : DRV_HIFI_IMAGE_SEC_LOAD_ENUM
 ��������  : ����μ�������
*****************************************************************************/
enum DRV_HIFI_IMAGE_SEC_LOAD_ENUM {
    DRV_HIFI_IMAGE_SEC_LOAD_STATIC = 0,      /* ���μ���, ���⸴λǰ���� */
    DRV_HIFI_IMAGE_SEC_LOAD_DYNAMIC,         /* ��μ���, ���������Ƽ��� */
    DRV_HIFI_IMAGE_SEC_UNLOAD,               /* ����Ҫ������� */
    DRV_HIFI_IMAGE_SEC_LOAD_BUTT,
};

/*****************************************************************************
 ʵ �� ��  : DRV_HIFI_IMAGE_SEC_STRU
 ��������  : ����ζ���
*****************************************************************************/
struct drv_hifi_image_sec
{
    unsigned short                      sn;              /* ��� */
    unsigned char                       type;            /* ���� */
    unsigned char                       load_attib;      /* �������� */
    unsigned long                       src_offset;      /* ���ļ��е�ƫ��, bytes */
    unsigned long                       des_addr;        /* ����Ŀ�ĵ�ַ, bytes */
    unsigned long                       size;            /* �γ���, bytes */
};

/*****************************************************************************
 ʵ �� ��  : drv_hifi_image_head
 ��������  : �����ļ�ͷ����
*****************************************************************************/
struct drv_hifi_image_head
{
    char                                time_stamp[24]; /* �������ʱ�� */
    unsigned long                       image_size;     /* �����ļ���С, bytes */
    unsigned int                        sections_num;   /* �ļ���������Ŀ */
    struct drv_hifi_image_sec           sections[HIFI_SEC_MAX_NUM];    /* ����Ϣ, ��sections_num�� */
};

/*****************************************************************************
 ʵ �� ��  : drv_hifi_sec_addr_info
 ��������  : Hifi��̬���ضε�ַ�ṹ
*****************************************************************************/
struct drv_hifi_sec_addr
{
    unsigned int  sec_source_addr;	/*�ε�Դ��ַ*/
    unsigned int  sec_length;	    /*�εĳ���*/
    unsigned int  sec_dest_addr;    /*�ε�Ŀ�ĵ�ַ*/
};

/*****************************************************************************
 ʵ �� ��  : drv_hifi_sec_load_info
 ��������  : Hifi��̬���ضνṹ
*****************************************************************************/
#define HIFI_SEC_DATA_LENGTH (HIFI_SHARE_MEMORY_SIZE \
                               - HIFI_DYNAMIC_SEC_MAX_NUM*sizeof(struct drv_hifi_sec_addr) \
                               - 3*sizeof(unsigned int))

struct drv_hifi_sec_load_info
{
    unsigned int             sec_magic;         /*����Ϣ��ʼ�ı�����*/
    unsigned int             sec_num;           /*�εĸ���*/
    struct drv_hifi_sec_addr sec_addr_info[HIFI_DYNAMIC_SEC_MAX_NUM]; /*�εĵ�ַ��Ϣ*/
    char                     sec_data[HIFI_SEC_DATA_LENGTH];          /*����Ϣ*/
};

int bsp_bbe_load_muti(void);

int bsp_bbe_run(void);

int bsp_bbe_stop(void);

int bsp_bbe_store(void);

int bsp_bbe_wait_store_ok(void);

int bsp_bbe_restore(void);

int bsp_bbe_wait_restore_ok(void);

int bsp_bbe_clock_enable(void);

int bsp_bbe_clock_disable(void);

int bsp_bbe_unreset(void);

int bsp_bbe_reset(void);

int bsp_bbe_power_on(void);

int bsp_bbe_power_off(void);

int bsp_bbe_is_clock_enable(void);

int bsp_bbe_is_power_on(void);

int bsp_bbe_is_tcm_accessible(void);

int bsp_dsp_clock_enable(void);

int bsp_dsp_clock_disable(void);

int bsp_dsp_unreset(void);

int bsp_dsp_reset(void);

int bsp_dsp_pll_status(void);

int bsp_dsp_pll_enable(void);

int bsp_dsp_pll_disable(void);

void bsp_bbe_chose_pll(u32 flag);

int bsp_msp_bbe_store(void);

int bsp_msp_bbe_restore(void);

int bsp_msp_wait_edma_ok(void);

#ifdef __VXWORKS__
int bsp_bbe_dpm_prepare(struct dpm_device *dev);

int bsp_bbe_dpm_suspend_late(struct dpm_device *dev);

int bsp_bbe_dpm_resume_early(struct dpm_device *dev);

int bsp_bbe_dpm_complete(struct dpm_device *dev);
#endif

int bsp_dsp_is_hifi_exist(void);


int bsp_dsp_info(void);



int bsp_hifi_run(void);

int bsp_hifi_stop(void);

int bsp_hifi_restore(void);

int bsp_load_modem(void);
int bsp_load_modem_dsp(void);

/* the interface below is just for myself */

extern void drv_hifi_fill_mb_info(unsigned int addr);
void bsp_dsp_init(void);



#ifdef __cplusplus
}
#endif

#endif

