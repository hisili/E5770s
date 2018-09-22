
#ifndef _UTRACE_BALONG_H_
#define _UTRACE_BALONG_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "bsp_memmap.h"
#include "osl_types.h"      

/**************************************************************************
           �Ĵ�������(���¼Ĵ���������ARM CoreSight�Ĵ���)
**************************************************************************/
/* ======================PTM �Ĵ���======================= */
#ifndef BSP_CONFIG_HI3630 /* V7R2 */
#define PTM0_REG_BASE           HI_CORESIGHT_PTM0_BASE_ADDR_VIRT    /* Core0 PTM��ַ */
#endif
#define PTM1_REG_BASE           HI_CORESIGHT_PTM1_BASE_ADDR_VIRT    /* Core1 PTM��ַ */
#define PTM_CTRL                0x000                               /* ���ƼĴ��� */
#define PTM_TRIGGER             0x008                               /* Trigger Event */
#define PTM_STATUS              0x010                               /* ״̬�Ĵ��� */
#define PTM_TEEVR               0x020                               /* Trace Enable Event */
#define PTM_TECR                0x024                               /* Trace Enable Contorl */
#define PTM_ACVR(n)             (0x40 + n*0x4)                      /* Address Comparator Value */
#define PTM_ACTR(n)             (0x80 + n*0x4)                      /* Address Comparator Access Type */
#define PTM_SYNCFR              0x1E0                               /* Sync Frequency */
#define PTM_TSEVR               0x1F8                               /* Timestamp Event */
#define PTM_TRACEID             0x200                               /* Trace ID */
#define PTM_LOCK_ACCESS         0xFB0                               /* Lock�Ĵ�����������0xC5ACCE55 */
#define PTM_LOCK_STATUS         0xFB4                               /* Lock״̬�Ĵ��� */

/* ======================FUNNEL �Ĵ���==================== */
#define FUNNEL_REG_BASE         HI_CORESIGHT_FUNNEL_BASE_ADDR_VIRT  /* FUNNEL��ַ */
#define FUNNEL_CTRL             0x000                               /* FUNNEL���ƼĴ��� */
#define FUNNEL_LOCK_ACCESS      0xFB0                               /* Lock�Ĵ�����������0xC5ACCE55 */
#define FUNNEL_LOCK_STATUS      0xFB4                               /* Lock״̬�Ĵ��� */

#ifndef BSP_CONFIG_HI3630 /* V7R2 */

/* ======================STM �Ĵ���======================= */
#define STM_REG_BASE            HI_CORESIGHT_STM_BASE_ADDR_VIRT     /* STM��ַ */
#define STM_PORT_ENABLE         0xE00                               /* Stimulus Portʹ�ܼĴ��� */
#define STM_PORT_TRIGGER_ENABLE 0xE20                               /* Stimulus Port Triggerʹ�ܼĴ��� */
#define STM_TRIGGER_CTRL        0xE70                               /* Trigger����״̬�Ĵ��� */
#define STM_TRACE_CTRL          0xE80                               /* STM Trace����״̬�Ĵ��� */
#define STM_LOCK_ACCESS         0xFB0                               /* Lock�Ĵ�����������0xC5ACCE55 */
#define STM_LOCK_STATUS         0xFB4                               /* Lock״̬�Ĵ��� */

/* ======================ETF �Ĵ���======================= */
#define ETF_REG_BASE            HI_CORESIGHT_ETF_BASE_ADDR_VIRT     /* ETF��ַ */
#define ETF_RAM_SIZE            0x004                               /* RAM size�Ĵ��� */
#define ETF_STATUS              0x00C                               /* ״̬�Ĵ�����ָʾTMCReady,Empty,Full,MemErr */
#define ETF_RAM_RD_DATA         0x010                               /* FIFO���ݶ��Ĵ��� */
#define ETF_RAM_RD_POINTER      0x014                               /* ��ָ�� */
#define ETF_RAM_WR_POINTER      0x018                               /* дָ�� */
#define ETF_CTRL                0x020                               /* ���ƼĴ���������Traceʹ�� */
#define ETF_RAM_WR_DATA         0x024                               /* ����д�Ĵ��� */
#define ETF_MODE                0x028                               /* Mode�Ĵ�����Circular buffer, Hardware FIFO, Software FIFO */
#define ETF_BUF_WATER_MARK      0x034                               /* FULL�ź��ϱ�ˮ�� */
#define ETF_FORMAT_FLUSH_STATUS 0x300                               /* Formatter, Flush״̬�Ĵ��� */
#define ETF_FORMAT_FLUSH_CTRL   0x304                               /* Formatter, Flush���ƼĴ��� */
#define ETF_LOCK_ACCESS         0xFB0                               /* Lock�Ĵ�����������0xC5ACCE55 */
#define ETF_LOCK_STATUS         0xFB4                               /* Lock״̬�Ĵ��� */

/* ======================ETR �Ĵ���======================= */
#define ETR_REG_BASE            HI_CORESIGHT_ETR_BASE_ADDR_VIRT     /* ETR��ַ */
#define ETR_RAM_SIZE            0x004                               /* RAM size�Ĵ���, ����ΪDDR�ռ��С */
#define ETR_STATUS              0x00C                               /* ״̬�Ĵ�����ָʾTMCReady,Empty,Full,MemErr */
#define ETR_RAM_RD_DATA         0x010                               /* FIFO���ݶ��Ĵ��� */
#define ETR_RAM_RD_POINTER      0x014                               /* ��ָ�� */
#define ETR_RAM_WR_POINTER      0x018                               /* дָ�� */
#define ETR_CTRL                0x020                               /* ���ƼĴ���������Traceʹ�� */
#define ETR_RAM_WR_DATA         0x024                               /* ����д�Ĵ��� */
#define ETR_MODE                0x028                               /* Mode�Ĵ�����Circular buffer, Hardware FIFO, Software FIFO */
#define ETR_BUF_WATER_MARK      0x034                               /* FULL�ź��ϱ�ˮ�� */
#define ETR_DATA_BUF_ADDR       0x118                               /* ϵͳDDR��ַ�Ĵ�����ETR�����ݴ��䵽�õ�ַ */
#define ETR_FORMAT_FLUSH_STATUS 0x300                               /* Formatter, Flush״̬�Ĵ��� */
#define ETR_FORMAT_FLUSH_CTRL   0x304                               /* Formatter, Flush���ƼĴ��� */
#define ETR_LOCK_ACCESS         0xFB0                               /* Lock�Ĵ�����������0xC5ACCE55 */
#define ETR_LOCK_STATUS         0xFB4                               /* Lock״̬�Ĵ��� */
#endif
/**************************************************************************
                                  �궨��
**************************************************************************/
#define UTRACE_DDR_SIZE         0x2000                              /* DDR����ռ��С���ֽ�Ϊ��λ */
#define UTRACE_WATER_MARK       0x3                                 /* ETRˮ�����ã���ʣ��ռ�С��ˮ��ʱ��ETR�ϱ�full�ж� */
#define UTRACE_UNLOCK_CODE      0xC5ACCE55                          /* ������ */
#define UTRACE_LOCK_CODE        0x1                                 /* ����CoreSight�Ĵ��� */
#define MAX_WAIT_CNT            0x2000                              /* ���ȴ����� */
#define UTRACE_ONSTART_BUF_SIZE (8*1024)                            /* ��������ģʽ��ETRʹ�õ�ѭ��buffer�ռ��С */
#define UTRACE_MAGIC_NUM        0x89ABCDEF                          /* ��ά�ɲ���չ��������UTRACE��ʶ�� */

/**************************************************************************
                               ���ݽṹ����
**************************************************************************/
/* ����ģ�鶨�壬SoC Traceͨ·��Ҫ����STM, FUNNEL, ETF, ETR */
enum trace_config_enum
{
    TRACE_STM,
    TRACE_PTM0,
    TRACE_PTM1,
    TRACE_FUNNEL,
    TRACE_ETF,
    TRACE_ETR,
    TRACE_BUTT
};
typedef unsigned int trace_config_enum_u32;

/* ETF, ETRģʽ����(ETF, ETR��TMC�Ĳ�ͬ����) */
enum tmc_mode_enum
{
    TMC_MODE_CIRCULAR_BUFF, /* ѭ��buffer */
    TMC_MODE_SOFTWARE_FIFO, /* ��FIFO */    
    TMC_MODE_HARDWARE_FIFO, /* ӲFIFO */
    TMC_MODE_BUTT           /* ��Чֵ */    
};
typedef unsigned int tmc_mode_enum_u32;

/* FUNNEL�˿ڷ��� */
enum funnel_port_enum
{
#ifndef BSP_CONFIG_HI3630 /* V7R2 */
    FUNNEL_STM_PORT,            /* STM�˿� */
    FUNNEL_PTM_APPA9_PORT,      /* APPA9 PTM�˿� */
    FUNNEL_PTM_MODEMA9_PORT,    /* MODEMA9 PTM�˿� */
    FUNNEL_M3_PORT = 6          /* M3 ITM�˿� */
#else
    FUNNEL_PTM_MODEMA9_PORT = 0,/* MODEMA9 PTM�˿� */
    FUNNEL_PTM_BBE16_PORT       /* BBE16 PTM�˿� */
#endif
};
typedef unsigned int funnel_port_enum_u32;

/* Trace�ɼ����� */
enum capt_ctrl_enum
{
    APPA9_ONLY,             /* ֻ����A core */
    MODEMA9_ONLY,           /* ֻ����C core */
    CAPT_CTRL_BUTT
};
typedef unsigned int capt_ctrl_enum_u32;

/* ETR���� */
typedef struct
{
    tmc_mode_enum_u32   mode;
    u32                 buf_size;
    u32                 buf_addr;
} etr_config_t;

#ifdef __cplusplus
}
#endif

#endif /* _UTRACE_BALONG_H_ */


