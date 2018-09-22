


#ifndef    _BSP_EDMA_H_
#define    _BSP_EDMA_H_

#include "soc_interrupts.h"
#include "osl_types.h"
#include "bsp_memmap.h"
#include "drv_edma.h"
#include "bsp_om.h"
/*p531 ���� ʹ�� gu�ڲ��߼� edma ��vic*/
#ifdef  CONFIG_MODULE_VIC
#include "bsp_vic.h"
#endif

#define hiedmac_trace(level, fmt, ...)      (bsp_trace(level, BSP_MODU_EDMA, "[edma]:<%s> <%d> "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__))

typedef u32 edma_addr_t;
#define EDMA_CX_LLI (0x800)
#define EDMA_CX_CONFIG (0x81C)

/*�����붨��*/

#define EDMA_SUCCESS         DMAC_SUCCESS
#define EDMA_FAIL            DMA_FAIL

#define EDMA_ERROR_BASE                          DMA_ERROR_BASE
#define EDMA_CHANNEL_INVALID                     DMA_CHANNEL_INVALID
#define EDMA_TRXFERSIZE_INVALID                  DMA_TRXFERSIZE_INVALID
#define EDMA_SOURCE_ADDRESS_INVALID              DMA_SOURCE_ADDRESS_INVALID
#define EDMA_DESTINATION_ADDRESS_INVALID         DMA_DESTINATION_ADDRESS_INVALID
#define EDMA_MEMORY_ADDRESS_INVALID              DMA_MEMORY_ADDRESS_INVALID
#define EDMA_PERIPHERAL_ID_INVALID               DMA_PERIPHERAL_ID_INVALID
#define EDMA_DIRECTION_ERROR                     DMA_DIRECTION_ERROR
#define EDMA_TRXFER_ERROR                        DMA_TRXFER_ERROR
#define EDMA_LLIHEAD_ERROR                       DMA_LLIHEAD_ERROR
#define EDMA_SWIDTH_ERROR                        DMA_SWIDTH_ERROR
#define EDMA_LLI_ADDRESS_INVALID                 DMA_LLI_ADDRESS_INVALID
#define EDMA_TRANS_CONTROL_INVALID               DMA_TRANS_CONTROL_INVALID
#define EDMA_MEMORY_ALLOCATE_ERROR               DMA_MEMORY_ALLOCATE_ERROR
#define EDMA_NOT_FINISHED                        DMA_NOT_FINISHED
#define EDMA_CONFIG_ERROR                        DMA_CONFIG_ERROR

/*  ����void (*channel_isr)(u32 channel_arg, u32 int_status)�Ĳ���int_status��
    ����s32 bsp_edma_channel_init (enum edma_req_id req,  channel_isr pFunc,
    u32 channel_arg, u32 int_flag)�Ĳ���int_flag Ϊ���¼����ж����ͣ������  */
#define EDMA_INT_DONE           BALONG_DMA_INT_DONE                /*EDMA��������ж�*/
#define EDMA_INT_LLT_DONE       BALONG_DMA_INT_LLT_DONE            /*��ʽEDMA�ڵ㴫������ж�*/
#define EDMA_INT_CONFIG_ERR     BALONG_DMA_INT_CONFIG_ERR          /*EDMA���ô����µ��ж�*/
#define EDMA_INT_TRANSFER_ERR   BALONG_DMA_INT_TRANSFER_ERR        /*EDMA��������µ��ж�*/
#define EDMA_INT_READ_ERR       BALONG_DMA_INT_READ_ERR            /*EDMA����������µ��ж�*/
#define EDMA_INT_ALL            0x1F

/* EDMAC���䷽����*/
#define EDMA_P2M      BALONG_DMA_P2M
#define EDMA_M2P      BALONG_DMA_M2P
#define EDMA_M2M      BALONG_DMA_M2M

#define EDMA_GET_DEST_ADDR       0
#define EDMA_GET_SOUR_ADDR       1

#ifdef __KERNEL__
#define EDMA_DATA_TIMEOUT      10 /* 10*5=50ms */
#elif defined (__VXWORKS__)
#define EDMA_DATA_TIMEOUT      10
#else
#endif

/* EDMAC�������봫������*/

#define MEM_MEM_EDMA    MEM_MEM_DMA   /* �ڴ浽�ڴ棬DMA����*/
#define MEM_PRF_EDMA    MEM_PRF_DMA   /* �ڴ������裬DMA����*/

#define EDMAC_MAX_CHANNEL        (16)

#define EDMAC_DT_NUM       (16)
   /*ACPU=0,CCPU=1  */
#ifdef __KERNEL__
#define EDMAC_DT_ARM       (1)
#define INT_LVL_EDMAC       INT_LVL_EDMAC1
#define INT_LVL_EDMAC_CH4   INT_LVL_EDMAC_CH4_1
#elif defined (__VXWORKS__)
#define EDMAC_DT_ARM       (0)
#define INT_LVL_EDMAC       INT_LVL_EDMAC0
#define INT_LVL_EDMAC_CH4   INT_LVL_EDMAC_CH4_0
#else
#endif

#define EDMA_CH16_ID        0
#define EDMA_CH4_ID         1
#define EDMA_NUMBER         2

#define EDMA_ID(channel_id) ((channel_id<EDMA_CH16_NUM) ? EDMA_CH16_ID : EDMA_CH4_ID)
#define EDMA_ID_CHAN_ID(channel_id) \
        ((channel_id<EDMA_CH16_NUM) ? channel_id : (channel_id - EDMA_CH16_NUM))


#define EDMA_CHANNEL_START  0
#define EDMA_CH16_NUM       16
#ifdef HI_EDMA_CH4_REGBASE_ADDR_VIRT
#define EDMA_CH4_NUM        4
#define EDMA_CHANNEL_END    (EDMA_CHANNEL_START+EDMA_CH16_NUM+EDMA_CH4_NUM)
#else
#define EDMA_CHANNEL_END    (EDMA_CHANNEL_START+EDMA_CH16_NUM)
#endif

/* EDMA ��Ӧ�ľ���λ   ��EDMA �Ĵ������ú�
       EDMAC_BASIC_CONFIG��EDMA_SET_LLI��EDMA_SET_CONFIG ʹ��*/

/*Bit3-2*/
#define EDMAC_TRANSFER_CONFIG_FLOW_EDMAC( _len )  EDMAC_TRANSFER_CONFIG_FLOW_DMAC( _len )

/*addr:�����ַ*/
#define EDMA_SET_LLI(addr, last)   BALONG_DMA_SET_LLI(addr, last)

#define EDMA_SET_CONFIG(req, direction, burst_width, burst_len) \
					BALONG_DMA_SET_CONFIG(req, direction, burst_width, burst_len)

#define EDMA_CHANNEL_DISABLE       EDMAC_TRANSFER_CONFIG_CHANNEL_DISABLE
#define EDMA_CHANNEL_ENABLE        EDMAC_TRANSFER_CONFIG_CHANNEL_ENABLE
#define EDMA_NEXT_LLI_ENABLE       EDMAC_NEXT_LLI_ENABLE


struct chan_int_service
{
   channel_isr chan_isr;
   u32 chan_arg;
   u32 int_status;
};

struct EDMAC_FREE_NODE_HEADER_STRU
{
    u32  ulInitFlag;
    u32  ulFirstFreeNode;
};

struct EDMA_LLI_ALLOC_ADDRESS_STRU
{
	u32 s_alloc_virt_address;
	u32 s_alloc_phys_address;
};

struct EDMA_SIMPLE_LLI_STRU
{
    u32 ulSourAddr;
    u32 ulDestAddr;
    u32 ulLength;
    u32 ulConfig;
};

struct EDMAC_TRANSFER_CONFIG_STRU
{
    struct edma_cb    lli_node_info;
	volatile u32   ulPad10[8];
};

struct EDMAC_CURR_STATUS_REG_STRU
{
	volatile u32 ulCxCurrCnt1;
	volatile u32 ulCxCurrCnt0;
	volatile u32 ulCxCurrSrcAddr;
	volatile u32 ulCxCurrDesAddr;
};

/*EDMA �Ĵ����ṹ��*/
typedef struct
{
	/*0x0000---*/
	volatile u32 ulIntState;
	/*0x0004---*/
	volatile u32 ulIntTC1;
	/*0x0008---*/
	volatile u32 ulIntTC2;
	/*0x000C---*/
	volatile u32 ulIntErr1;
	/*0x0010---*/
	volatile u32 ulIntErr2;
	/*0x0014---*/
	volatile u32 ulIntErr3;
	/*0x0018---*/
	volatile u32 ulIntTC1Mask;
	/*0x001C---*/
	volatile u32 ulIntTC2Mask;
	/*0x0020---*/
	volatile u32 ulIntErr1Mask;
	/*0x0024---*/
	volatile u32 ulIntErr2Mask;
	/*0x0028---*/
	volatile u32 ulIntErr3Mask;
	volatile u32 ulPad[(0x40-0x28)/4-1];
}EDMAC_CPU_REG_STRU;

struct edma_reg_struct
{
	volatile EDMAC_CPU_REG_STRU stCpuXReg[EDMAC_DT_NUM];

	volatile u32 ulPad0[(0x600-0x400)/4];
	/*0x0600-- */
	volatile u32 ulIntTC1Raw;
	volatile u32 ulPad1;
	/*0x0608-- */
	volatile u32 ulIntTC2Raw;
	volatile u32 ulPad2;
	/*0x0610-- */
	volatile u32 ulIntERR1Raw;
	volatile u32 ulPad3;
	/*0x0618-- */
	volatile u32 ulIntERR2Raw;
	volatile u32 ulPad4;
	/*0x0620-- */
	volatile u32 ulIntERR3Raw;
	volatile u32 ulPad5[(0x660-0x620)/4-1];
	/*0x0660--*/
	volatile u32 ulSingleReq;
    volatile u32 ulLastSingleReq;
    volatile u32 ulBurstReq;
    volatile u32 ulLastBurstReq;
    volatile u32 ulFlushReq;
    volatile u32 ulLastFlushReq;
	volatile u32 ulPad6[(0x688-0x674)/4-1];
	/*0x0688--*/
	volatile u32 ulChannelPrioritySet;
	volatile u32 ulPad7;
	/*0x0690--*/
    volatile u32 ulChannelState;
    volatile u32 ulPad8;
	/* 0x0698 -- */
    volatile u32 ulDmaCtrl;
    volatile u32 ulPad9[(0x0700-0x698)/4-1];
    /* 0x0700 -- */
	volatile struct EDMAC_CURR_STATUS_REG_STRU stCurrStatusReg[EDMAC_MAX_CHANNEL];
	/* 0x0800 -- */
	volatile struct EDMAC_TRANSFER_CONFIG_STRU stTransferConfig[EDMAC_MAX_CHANNEL];
};

#define EDMAC_MAKE_LLI_ADDR( _p )   (u32)( (u32)(_p) & 0xFFFFFFE0 )
#define EDMAC_CHANNEL_CB(x)   (g_edma_drv_info.edma_reg_str->stTransferConfig[x].lli_node_info)

#ifdef CONFIG_BALONG_EDMA

#ifdef __KERNEL__
#elif  defined(__VXWORKS__)
s32  bsp_edma_init(void);
#else
#endif
s32 bsp_edma_channel_init (enum edma_req_id request, channel_isr pFunc, u32 channel_arg, u32 int_flag);
s32 bsp_edma_current_transfer_address(u32 channel_id);
u64 bsp_edma_current_cnt(u32 channel_id);
s32 bsp_edma_channel_stop(u32 channel_id);
s32 bsp_edma_channel_is_idle (u32 channel_id);
s32 bsp_edma_chanmap_is_idle (u32 channel_map);
void bsp_edma_channel_obtainable( void );
s32 bsp_edma_channel_set_config (u32 channel_id, u32 direction, u32 burst_width, u32 burst_len);
s32 bsp_edma_channel_dest_set_config(u32 channel_id, u32 dest_width, u32 dest_len);
s32 bsp_edma_channel_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len);
s32 bsp_edma_channel_2vec_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len, u32 size_align);
s32 bsp_edma_channel_async_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len);
struct edma_cb *bsp_edma_channel_get_lli_addr (u32 channel_id);
s32 bsp_edma_channel_lli_start (u32 channel_id);
s32 bsp_edma_channel_lli_async_start (u32 channel_id);
s32 bsp_edma_channel_free (u32 channel_id);
#else
static inline s32  bsp_edma_init(void){return -1;}
static inline s32 bsp_edma_channel_init (enum edma_req_id request, channel_isr pFunc, u32 channel_arg, u32 int_flag){return -1;}
static inline s32 bsp_edma_current_transfer_address(u32 channel_id){return -1;}
static inline u64 bsp_edma_current_cnt(u32 channel_id){return (u64)-1;}
static inline s32 bsp_edma_channel_stop(u32 channel_id){return -1;}
static inline s32 bsp_edma_channel_is_idle (u32 channel_id){return -1;}
static inline s32 bsp_edma_chanmap_is_idle (u32 channel_map){return -1;}
static inline void bsp_edma_channel_obtainable( void ){}
static inline s32 bsp_edma_channel_set_config (u32 channel_id, u32 direction, u32 burst_width, u32 burst_len){return -1;}
static inline s32 bsp_edma_channel_dest_set_config(u32 channel_id, u32 dest_width, u32 dest_len){return -1;}
static inline s32 bsp_edma_channel_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len){return -1;}
static inline s32 bsp_edma_channel_2vec_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len, u32 size_align){return -1;}
static inline s32 bsp_edma_channel_async_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len){return -1;}
static inline struct edma_cb *bsp_edma_channel_get_lli_addr (u32 channel_id){return (struct edma_cb *)0;}
static inline s32 bsp_edma_channel_lli_start (u32 channel_id){return -1;}
static inline s32 bsp_edma_channel_lli_async_start (u32 channel_id){return -1;}
static inline s32 bsp_edma_channel_free (u32 channel_id){return -1;}
#endif

#endif    /* End of DMADRV_H */

