

#ifndef __DRV_EDMA_H__
#define __DRV_EDMA_H__

#include "drv_comm.h"
#include "drv_edma_enum.h"

/* v7r1 */
typedef struct tagAXI_DMA_TASK_HANDLE_S
{
	unsigned int u32SrcAddr;
	unsigned int u32DstAddr;
	unsigned int ulLength;
	unsigned int ulChIdx;
}AXI_DMA_TASK_HANDLE_S;
BSP_S32 EDMA_NormTaskLaunch(AXI_DMA_TASK_HANDLE_S * pstDMAHandle);
BSP_S32 EDMA_2VecTaskLaunch(AXI_DMA_TASK_HANDLE_S * pstDMAHandle);
BSP_S32 EDMA_QueryCHNLState(BSP_U32 u32ChIdx);
BSP_S32 EDMA_QueryCHNsLState(BSP_U32 u32ChIdxMap);

/*�����붨��*/
#ifndef OK
#define OK     0
#endif
#ifndef ERROR
#define ERROR (-1)
#endif
/*�����붨��*/

#define DMAC_SUCCESS                       0
#define DMA_FAIL                          (-1)

#define DMA_ERROR_BASE                          -100
#define DMA_CHANNEL_INVALID                     (DMA_ERROR_BASE-1)
#define DMA_TRXFERSIZE_INVALID                  (DMA_ERROR_BASE-2)
#define DMA_SOURCE_ADDRESS_INVALID              (DMA_ERROR_BASE-3)
#define DMA_DESTINATION_ADDRESS_INVALID         (DMA_ERROR_BASE-4)
#define DMA_MEMORY_ADDRESS_INVALID              (DMA_ERROR_BASE-5)
#define DMA_PERIPHERAL_ID_INVALID               (DMA_ERROR_BASE-6)
#define DMA_DIRECTION_ERROR                     (DMA_ERROR_BASE-7)
#define DMA_TRXFER_ERROR                        (DMA_ERROR_BASE-8)
#define DMA_LLIHEAD_ERROR                       (DMA_ERROR_BASE-9)
#define DMA_SWIDTH_ERROR                        (DMA_ERROR_BASE-0xa)
#define DMA_LLI_ADDRESS_INVALID                 (DMA_ERROR_BASE-0xb)
#define DMA_TRANS_CONTROL_INVALID               (DMA_ERROR_BASE-0xc)
#define DMA_MEMORY_ALLOCATE_ERROR               (DMA_ERROR_BASE-0xd)
#define DMA_NOT_FINISHED                        (DMA_ERROR_BASE-0xe)
#define DMA_CONFIG_ERROR                        (DMA_ERROR_BASE-0xf)

/* v9r1 */

typedef void (*channel_isr)(unsigned int channel_arg, unsigned int int_status);

/*�������������*/
enum edma_req_id
{
    EDMA_SPI0_RX = 0,
    EDMA_SPI0_TX,
    EDMA_SPI1_RX,
    EDMA_SPI1_TX,   /* Acore drv lcd ˢ��           ʵ�ʷ���ͨ�� edma ch16 - 14 */
    EDMA_LTESIO_RX, /* HIFI                         ʵ�ʷ���ͨ�� edma ch16 - 8  */
    EDMA_LTESIO_TX, /* HIFI                         ʵ�ʷ���ͨ�� edma ch16 - 9  */
    RESERVE_0,
    RESERVE_1,
    EDMA_HSUART_RX = 8, /* Acore drv ������������   ʵ�ʷ���ͨ�� edma ch16 - 12 */
    EDMA_HSUART_TX,     /* Acore drv ������������   ʵ�ʷ���ͨ�� edma ch16 - 13 */
    EDMA_UART0_RX,
    EDMA_UART0_TX,
    EDMA_UART1_RX,
    EDMA_UART1_TX,
    EDMA_UART2_RX,
    EDMA_UART2_TX,
    EDMA_SCI0_RX = 0x10,    /* Acore drv SIM��1��   ʵ�ʷ���ͨ�� edma ch16 - 10 */
	EDMA_SCI_RX  = 0x10,
    EDMA_SCI0_TX,           /* Acore drv SIM��1��   ʵ�ʷ���ͨ�� edma ch16 - 10 */
    EDMA_SCI1_RX,           /* Acore drv SIM��2��   ʵ�ʷ���ͨ�� edma ch16 - 11 */
    EDMA_SCI1_TX,           /* Acore drv SIM��2��   ʵ�ʷ���ͨ�� edma ch16 - 11 */

    EDMA_GBBP0_DBG = 0x14,
    EDMA_BBP_DBG   = 0x14, /* gudsp ������ bbp����  ʵ�ʷ���ͨ�� edma ch16 - 6  */
    EDMA_GBBP1_GRIF = 0x15,
    EDMA_BBP_GRIF   = 0x15,/* gudsp ������ bbp����  ʵ�ʷ���ͨ�� edma ch16 - 6  */

    EDMA_AMON_SOC = 0x16,     /* Acore drv AXIMON   ʵ�ʷ���ͨ�� edma ch16 - 15 */
    EDMA_AMON_CPUFAST = 0x17, /* Acore drv AXIMON   ʵ�ʷ���ͨ�� edma ch16 - 15 */
    EDMA_I2C0_RX,                   /*711����v7r2û��*/
    EDMA_I2C0_TX,                   /*711����v7r2û��*/
    EDMA_I2C1_RX,                   /*711����v7r2û��*/
    EDMA_I2C2_TX,                   /*711����v7r2û��*/
    EDMA_EMI_TRANS,            /*711����v7r2û��,edma_ch16��֧��,edma_ch4��֧��*/


    /* gudsp ������ M2M */
    /* EDMA_GBBP0_DBG      gudspʹ�� EDMA_BBP_DBG   ʵ�ʷ���ͨ�� edma ch16 - 6  */
    EDMA_MEMORY_DSP_1 = 0x20,   /* ����turbo����    ʵ�ʷ���ͨ�� edma ch4  - 0  */
    EDMA_MEMORY_DSP_2,          /* ����viterb����   ʵ�ʷ���ͨ�� edma ch4  - 1  */
    /*TL��GU���� ch16 - 2��Ϊ����ÿ������ǰ��鵱ǰͨ���Ƿ����***/
    EDMA_MEMORY_DSP_3,          /* ����CQI�����    ʵ�ʷ���ͨ�� edma ch16 - 2  */
    EDMA_MEMORY_DSP_4,          /* �������б���     ʵ�ʷ���ͨ�� edma ch4  - 2  */
    EDMA_MEMORY_DSP_5,          /* ����APT�����    ʵ�ʷ���ͨ�� edma ch4  - 3  */
    EDMA_MEMORY_DSP_6 = 0x25,   /* GUDSP/AHB����    ʵ�ʷ���ͨ�� edma ch16 - 7  */

    EDMA_PWC_LDSP_TCM  ,        /* Mcore  drv   ʵ�ʷ���ͨ�� edma ch16 - 0  */
    EDMA_PWC_TDSP_TCM ,         /* Mcore  drv   ʵ�ʷ���ͨ�� edma ch16 - 1  */


    /* TLDSP  �������壬û��ʵ����; �ŵ�MAXǰ�����ڲ���0ͨ�� */
    EDMA_LDSP_API_USED_0,       /* LDSP����ר�о��� ʵ�ʷ���ͨ�� edma ch16 - 0  */

    EDMA_REQ_MAX,               /*����豸����С�ڴ�ֵ����Ϊ�Ƿ�����*/

    /* TLDSP  �������壬û��ʵ����; */
    EDMA_LDSP_API_USED_1,       /* LDSP����ר�о��� ʵ�ʷ���ͨ�� edma ch16 - 1  */
    /*TL��GU���� ch16 - 2��Ϊ����ÿ������ǰ��鵱ǰͨ���Ƿ����***/
    EDMA_LDSP_LCS_SDR,          /* TLDSP LCS        ʵ�ʷ���ͨ�� edma ch16 - 2  */
    EDMA_LDSP_CSU_SDR,          /* LDSPС������     ʵ�ʷ���ͨ�� edma ch16 - 3  */
    EDMA_LDSP_EMU_SDR,          /* LDSP��������     ʵ�ʷ���ͨ�� edma ch16 - 4  */
    EDMA_LDSP_NV_LOADING,       /* LDSP��̬����NV   ʵ�ʷ���ͨ�� edma ch16 - 5  */

    EDMA_BUTT

} ;

typedef enum edma_req_id BALONG_DMA_REQ; /*adapt*/
/* adapt for v9r1 */
#define EDMA_MEMORY_DSP EDMA_MEMORY_DSP_1

/*for test*/
#define EDMA_MEMORY  EDMA_LDSP_API_USED_0 /* use ldsp's channel ch16- 0 when testing busstress */




/* ����void (*channel_isr)(BSP_U32 channel_arg, BSP_U32 int_status)�Ĳ���int_status��
    ����int balong_dma_channel_init (BALONG_DMA_REQ req,  channel_isr pFunc,
                     UINT32 channel_arg, UINT32 int_flag)�Ĳ���int_flag
    Ϊ���¼����ж����ͣ������       */
#define BALONG_DMA_INT_DONE           1          /*DMA��������ж�*/
#define BALONG_DMA_INT_LLT_DONE       2          /*��ʽDMA�ڵ㴫������ж�*/
#define BALONG_DMA_INT_CONFIG_ERR     4          /*DMA���ô����µ��ж�*/
#define BALONG_DMA_INT_TRANSFER_ERR   8          /*DMA��������µ��ж�*/
#define BALONG_DMA_INT_READ_ERR       16         /*DMA����������µ��ж�*/

/* EDMAC���䷽����*/
#define BALONG_DMA_P2M      1
#define BALONG_DMA_M2P      2
#define BALONG_DMA_M2M      3

/* EDMAC�������봫������*/
typedef enum tagEDMA_TRANS_TYPE
{
    MEM_MEM_DMA = 0x00,    /* �ڴ浽�ڴ棬DMA����*/
    MEM_PRF_DMA = 0x01,        /* �ڴ������裬DMA����*/
    MEM_PRF_PRF = 0x02        /* �ڴ������裬��������*/
} EDMA_TRANS_TYPE;

/* ͨ��״̬ */

#define   EDMA_CHN_FREE          1   /* ͨ������ */
#define   EDMA_CHN_BUSY          0   /* ͨ��æ */


/* EDMA����λ��Դ��Ŀ�ĵ�ַԼ��Ϊһ�µ�ֵ */
#define   EDMA_TRANS_WIDTH_8       0x0   /* 8bitλ��*/
#define   EDMA_TRANS_WIDTH_16      0x1   /* 16bitλ��*/
#define   EDMA_TRANS_WIDTH_32      0x2   /* 32bitλ��*/
#define   EDMA_TRANS_WIDTH_64      0x3   /* 64bitλ��*/

/*  EDMA burst length, ȡֵ��Χ0~15����ʾ��burst����Ϊ1~16*/
#define   EDMA_BUR_LEN_1    0x0    /* burst���ȣ���һ�δ���ĸ���Ϊ1��*/
#define   EDMA_BUR_LEN_2    0x1    /* burst���ȣ���һ�δ���ĸ���Ϊ2��*/
#define   EDMA_BUR_LEN_3    0x2   /* burst���ȣ���һ�δ���ĸ���Ϊ3��*/
#define   EDMA_BUR_LEN_4    0x3   /* burst���ȣ���һ�δ���ĸ���Ϊ4��*/
#define   EDMA_BUR_LEN_5    0x4   /* burst���ȣ���һ�δ���ĸ���Ϊ5��*/
#define   EDMA_BUR_LEN_6    0x5   /* burst���ȣ���һ�δ���ĸ���Ϊ6��*/
#define   EDMA_BUR_LEN_7    0x6   /* burst���ȣ���һ�δ���ĸ���Ϊ7��*/
#define   EDMA_BUR_LEN_8    0x7   /* burst���ȣ���һ�δ���ĸ���Ϊ8��*/
#define   EDMA_BUR_LEN_9    0x8   /* burst���ȣ���һ�δ���ĸ���Ϊ9��*/
#define   EDMA_BUR_LEN_10   0x9   /* burst���ȣ���һ�δ���ĸ���Ϊ10��*/
#define   EDMA_BUR_LEN_11   0xa   /* burst���ȣ���һ�δ���ĸ���Ϊ11��*/
#define   EDMA_BUR_LEN_12   0xb   /* burst���ȣ���һ�δ���ĸ���Ϊ12��*/
#define   EDMA_BUR_LEN_13   0xc   /* burst���ȣ���һ�δ���ĸ���Ϊ13��*/
#define   EDMA_BUR_LEN_14   0xd   /* burst���ȣ���һ�δ���ĸ���Ϊ14��*/
#define   EDMA_BUR_LEN_15   0xe   /* burst���ȣ���һ�δ���ĸ���Ϊ15��*/
#define   EDMA_BUR_LEN_16   0xf   /* burst���ȣ���һ�δ���ĸ���Ϊ16��*/


/* EDMA ��Ӧ�ľ���λ����EDMA  �Ĵ������ú�
       EDMAC_BASIC_CONFIG��BALONG_DMA_SET_LLI��BALONG_DMA_SET_CONFIG ʹ��*/
/*config------Bit 31*/
#define EDMAC_TRANSFER_CONFIG_SOUR_INC      (0X80000000)
/*Bit 30*/
#define EDMAC_TRANSFER_CONFIG_DEST_INC      (0X40000000)
#define EDMAC_TRANSFER_CONFIG_BOTH_INC      (0XC0000000)

/*Bit 27-24*/
#define EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH_MASK     (0xF000000)
#define EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH( _len )  ((unsigned int)((_len)<<24))
/*Bit 23-20*/
#define EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH_MASK     (0xF00000)
#define EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH( _len )  ((unsigned int)((_len)<<20))

/*Bit18-16*/
#define EDMAC_TRANSFER_CONFIG_SOUR_WIDTH_MASK     (0x70000)
#define EDMAC_TRANSFER_CONFIG_SOUR_WIDTH( _len )  ((unsigned int)((_len)<<16))
/*Bit14-12*/
#define EDMAC_TRANSFER_CONFIG_DEST_WIDTH_MASK     (0x7000)
#define EDMAC_TRANSFER_CONFIG_DEST_WIDTH( _len )  ((unsigned int)((_len)<<12))

/*Bit9-4*/
#define EDMAC_TRANSFER_CONFIG_REQUEST( _ulReg )    ( (_ulReg ) << 4)
/*Bit3-2*/
#define EDMAC_TRANSFER_CONFIG_FLOW_DMAC( _len )    ((unsigned int)((_len)<<2))

#define EDMAC_TRANSFER_CONFIG_INT_TC_ENABLE            ( 0x2 )
#define EDMAC_TRANSFER_CONFIG_INT_TC_DISABLE           ( 0x0 )

#define EDMAC_TRANSFER_CONFIG_CHANNEL_ENABLE           ( 0x1 )
#define EDMAC_TRANSFER_CONFIG_CHANNEL_DISABLE          ( 0x0 )
#define EDMAC_NEXT_LLI_ENABLE       0x2           /* Bit 1 */
/*Bit 15*/
#define EDMAC_TRANSFER_CONFIG_EXIT_ADD_MODE_A_SYNC     ( 0UL )
#define EDMAC_TRANSFER_CONFIG_EXIT_ADD_MODE_AB_SYNC    ( 0x00008000 )

/*��ʽ����ʱ�Ľڵ���Ϣ*/
typedef struct edma_cb
{
    volatile unsigned int lli;     /*ָ���¸�LLI*/
    volatile unsigned int bindx;
    volatile unsigned int cindx;
    volatile unsigned int cnt1;
    volatile unsigned int cnt0;   /*�鴫�����LLI�����ÿ���ڵ����ݳ��� <= 65535�ֽ�*/
    volatile unsigned int src_addr; /*�����ַ*/
    volatile unsigned int des_addr; /*�����ַ*/
    volatile unsigned int config;
} BALONG_DMA_CB __attribute__((aligned(32)));

#define P2M_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_PRF_DMA) | EDMAC_TRANSFER_CONFIG_DEST_INC)
#define M2P_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_PRF_DMA) | EDMAC_TRANSFER_CONFIG_SOUR_INC)
#define M2M_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_MEM_DMA) | EDMAC_TRANSFER_CONFIG_SOUR_INC | EDMAC_TRANSFER_CONFIG_DEST_INC)

#define EDMAC_BASIC_CONFIG(burst_width, burst_len) \
               ( EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH(burst_len) | EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH(burst_len) \
               | EDMAC_TRANSFER_CONFIG_SOUR_WIDTH(burst_width) | EDMAC_TRANSFER_CONFIG_DEST_WIDTH(burst_width) )

/*addr:�����ַ*/
#define BALONG_DMA_SET_LLI(addr, last)   ((last)?0:(EDMAC_MAKE_LLI_ADDR(addr) | EDMAC_NEXT_LLI_ENABLE))

#define BALONG_DMA_SET_CONFIG(req, direction, burst_width, burst_len) \
                 ( EDMAC_BASIC_CONFIG(burst_width, burst_len) | EDMAC_TRANSFER_CONFIG_REQUEST(req) \
                 | EDMAC_TRANSFER_CONFIG_INT_TC_ENABLE | EDMAC_TRANSFER_CONFIG_CHANNEL_ENABLE \
                 | ((direction == BALONG_DMA_M2M)?M2M_CONFIG:((direction == BALONG_DMA_P2M)?P2M_CONFIG:M2P_CONFIG)))

/**************************************************************************
  �궨��
**************************************************************************/



/*******************************************************************************
  ������:      BSP_S32 balong_dma_init(void)
  ��������:    DMA��ʼ�����򣬹ҽ��ж�
  �������:    ��
  �������:    ��
  ����ֵ:      0
*******************************************************************************/
extern BSP_S32 balong_dma_init(void);

/*******************************************************************************
  ������:       int balong_dma_current_transfer_address(UINT32 channel_id)
  ��������:     ���ĳͨ����ǰ������ڴ��ַ
  �������:     channel_id : ͨ��ID������balong_dma_channel_init�����ķ���ֵ
  �������:     ��
  ����ֵ:       �ɹ���ͨ����ǰ������ڴ��ַ
                ʧ�ܣ�����
*******************************************************************************/
extern int balong_dma_current_transfer_address(BSP_U32 channel_id);
#define DRV_EDMA_CURR_TRANS_ADDR(channel_id)  balong_dma_current_transfer_address(channel_id)

/*******************************************************************************
  ������:       int balong_dma_channel_stop(UINT32 channel_id)
  ��������:     ָֹͣ����DMAͨ��
  �������:     channel_id : ͨ��ID������balong_dma_channel_init�����ķ���ֵ
  �������:     ��
  ����ֵ:       �ɹ���ͨ����ǰ������ڴ��ַ
                ʧ�ܣ�����
*******************************************************************************/
extern BSP_S32 balong_dma_channel_stop(BSP_U32 channel_id);
#define DRV_EDMA_CHANNEL_STOP(channel_id)  balong_dma_channel_stop(channel_id)


/*******************************************************************************
  ������:      BALONG_DMA_CB *balong_dma_channel_get_lli_addr(UINT32 channel_id)
  ��������:    ��ȡָ��DMAͨ����������ƿ����ʼ��ַ
  �������:    channel_id��ͨ��ID,����balong_dma_channel_init�����ķ���ֵ
  �������:    ��
  ����ֵ:      �ɹ���0
               ʧ�ܣ�����
*******************************************************************************/
extern BALONG_DMA_CB *balong_dma_channel_get_lli_addr (BSP_U32 channel_id);
#define DRV_EDMA_CHAN_GET_LLI_ADDR(channel_id)  balong_dma_channel_get_lli_addr(channel_id)


/******************************************************************************
  ������:      int balong_dma_channel_init (BALONG_DMA_REQ req,
                  channel_isr pFunc, UINT32 channel_arg, UINT32 int_flag)
  ��������:    ��������ŷ���ͨ����ע��ͨ���жϻص���������ʼ����������ź�����
               �������д��config�Ĵ���
  �������:    req : ���������
               pFunc : �ϲ�ģ��ע���DMAͨ���жϴ�������NULLʱ������ע��
               channel_arg : pFunc�����1��
                             pFuncΪNULL������Ҫ�����������
               int_flag : pFunc�����2, �������ж����ͣ�ȡֵ��ΧΪ
                        BALONG_DMA_INT_DONE��BALONG_DMA_INT_LLT_DONE��
                      �BALONG_DMA_INT_CONFIG_ERR��BALONG_DMA_INT_TRANSFER_ERR��
                        BALONG_DMA_INT_READ_ERR֮һ��������ϡ�
                        pFuncΪNULL������Ҫ�����������
  �������:    ��
  ����ֵ:      �ɹ���ͨ����
               ʧ�ܣ�����
*******************************************************************************/
extern BSP_S32 balong_dma_channel_init (BALONG_DMA_REQ req, channel_isr pFunc, BSP_U32 channel_arg, BSP_U32 int_flag);
#define DRV_EDMA_CHANNEL_INIT(req, pFunc,channel_arg,int_flag) balong_dma_channel_init(req, pFunc,channel_arg,int_flag)

/*******************************************************************************
  ������:      int balong_dma_channel_set_config (UINT32 channel_id,
                       UINT32 direction, UINT32 burst_width, UINT32 burst_len)
  ��������:    ����ʽDMA����ʱ�����ñ���������ͨ������
               ��ʽDMA����ʱ������Ҫʹ�ñ�������
  �������:    channel_id : ͨ��ID������balong_dma_channel_init�����ķ���ֵ
               direction : DMA���䷽��, ȡֵΪBALONG_DMA_P2M��BALONG_DMA_M2P��
                           BALONG_DMA_M2M֮һ
               burst_width��ȡֵΪ0��1��2��3����ʾ��burstλ��Ϊ8��16��32��64bit
               burst_len��ȡֵ��Χ0~15����ʾ��burst����Ϊ1~16
  �������:    ��
  ����ֵ:      �ɹ���0
               ʧ�ܣ�����
*******************************************************************************/
extern BSP_S32 balong_dma_channel_set_config (BSP_U32 channel_id, BSP_U32 direction,BSP_U32 burst_width, BSP_U32 burst_len);
#define DRV_EDMA_CHANNEL_CONFIG(channel_id, direction,burst_width,burst_len)  balong_dma_channel_set_config(channel_id, direction,burst_width,burst_len)

/*******************************************************************************
  ������:      int balong_dma_channel_dest_set_config (UINT32 channel_id,
                       UINT32 burst_width, UINT32 burst_len)
  ��������:    BBP GRIF��Ҫ��������Ŀ������λ��ͳ��ȣ����ñ��������������β�ʹ�á�
               ʹ��ʱ���ýӿ���balong_dma_channel_set_config֮����á�
  �������:    channel_id��ͨ��ID������balong_dma_channel_init�����ķ���ֵ
               burst_width��ȡֵΪ0��1��2��3����ʾ��burstλ��Ϊ8��16��32��64bit
               burst_len��ȡֵ��Χ0~15����ʾ��burst����Ϊ1~16
  �������:    ��
  ����ֵ:      �ɹ���0
               ʧ�ܣ�����
*******************************************************************************/
extern BSP_S32 balong_dma_channel_dest_set_config (BSP_U32 channel_id, BSP_U32 burst_width, BSP_U32 burst_len);
#define DRV_EDMA_CHANNEL_DEST_CONFIG(channel_id, dest_width, dest_len)  balong_dma_channel_dest_set_config(channel_id, dest_width, dest_len)

/*******************************************************************************
  ������:      int balong_dma_channel_start (UINT32 channel_id, UINT32 src_addr,
                       UINT32 des_addr, UINT32 len)
  ��������:    ����һ��ͬ��DMA����, DMA������ɺ󣬲ŷ���
               ʹ�ñ�����ʱ������Ҫע���жϴ�����
  �������:    channel_id��ͨ��ID,����balong_dma_channel_init�����ķ���ֵ
               src_addr�����ݴ���Դ��ַ�������������ַ
               des_addr�����ݴ���Ŀ�ĵ�ַ�������������ַ
               len�����ݴ��䳤�ȣ���λ���ֽڣ�һ�δ������ݵ���󳤶���65535�ֽ�
  �������:    ��
  ����ֵ:      �ɹ���0
               ʧ�ܣ�����
*******************************************************************************/
extern BSP_S32 balong_dma_channel_start (BSP_U32 channel_id, BSP_U32 src_addr, BSP_U32 des_addr, BSP_U32 len);
#define DRV_EDMA_CHANNEL_START(channel_id,src_addr,des_addr,len)  balong_dma_channel_start(channel_id,src_addr,des_addr,len)


/*******************************************************************************
  ������:      int balong_dma_channel_async_start (UINT32 channel_id,
                unsigned int src_addr, unsigned int des_addr, unsigned int len)
  ��������:    ����һ���첽DMA���䡣����DMA����󣬾ͷ��ء����ȴ�DMA������ɡ�
               ʹ�ñ�����ʱ��ע���жϴ��������жϴ������д���DMA
��������¼�
               ���ߣ���ע���жϴ�������ʹ��balong_dma_channel_is_idle������ѯ
               DMA�����Ƿ����
  �������:    channel_id��ͨ��ID,����balong_dma_channel_init�����ķ���ֵ
               src_addr�����ݴ���Դ��ַ�������������ַ
               des_addr�����ݴ���Ŀ�ĵ�ַ�������������ַ
               len�����ݴ��䳤�ȣ���λ���ֽڣ�һ�δ������ݵ���󳤶���65535�ֽ�
  �������:    ��
  ����ֵ:      �ɹ���0
               ʧ�ܣ�����
*******************************************************************************/
extern BSP_S32 balong_dma_channel_async_start (BSP_U32 channel_id, BSP_U32 src_addr, BSP_U32 des_addr, BSP_U32 len);
#define DRV_EDMA_CHANNEL_ASYNC_START(channel_id,src_addr,des_addr,len) balong_dma_channel_async_start(channel_id,src_addr,des_addr,len)


/*******************************************************************************
  ������:      int balong_dma_channel_lli_start (UINT32 channel_id)
  ��������:    ������ʽDMA���䡣����ʽDMA�����нڵ㴫�䶼ȫ����ɺ�ŷ��ء�
               ��ʽDMA��ÿ���ڵ����������䳤��Ϊ65535�ֽڡ�
               ע�⣺���ô˺���ǰ���������ú�������ƿ顣
  �������:    channel_id��ͨ��ID,����balong_dma_channel_init�����ķ���ֵ
  �������:    ��
  ����ֵ:      �ɹ���0
               ʧ�ܣ�����
*******************************************************************************/
extern BSP_S32 balong_dma_channel_lli_start (BSP_U32 channel_id);
#define DRV_EDMA_CHANNEL_lli_START(channel_id)   balong_dma_channel_lli_start(channel_id)

/*******************************************************************************
  ������:      int balong_dma_channel_lli_start (UINT32 channel_id)
  ��������:    ������ʽDMA���䣬Ȼ���������أ����ȴ�DMA������ɡ�
               ��ʽDMA��ÿ���ڵ����������䳤��Ϊ65535�ֽڡ�
               ע�⣺���ô˺���ǰ���������ú�������ƿ顣
  �������:    channel_id��ͨ��ID,����balong_dma_channel_init�����ķ���ֵ
  �������:    ��
  ����ֵ:      �ɹ���0
               ʧ�ܣ�����
*******************************************************************************/
extern BSP_S32 balong_dma_channel_lli_async_start (BSP_U32 channel_id);
#define DRV_EDMA_CHANNEL_lli_ASYNC_START(channel_id)   balong_dma_channel_lli_async_start(channel_id)


/******************************************************************************
*
  ������:       int balong_dma_channel_is_idle (UINT32 channel_id)
  ��������:     ��ѯDMAͨ���Ƿ����
  �������:     channel_id : ͨ��ID������balong_dma_channel_init�����ķ���ֵ
  �������:     ��
  ����ֵ:       0 : ͨ��æµ
                1 : ͨ������
                ���� : ʧ��
*******************************************************************************/
extern BSP_S32 balong_dma_channel_is_idle (BSP_U32 channel_id);
#define DRV_EDMA_CHANNEL_IS_IDLE(chanel_id) balong_dma_channel_is_idle(chanel_id)

/*****************************************************************************
 �� �� ��  : DRV_EDMA_BBP_SAMPLE_REBOOT
 ��������  : BBP����ʹ�������ӿڣ�������ϵͳ��ͣ����fastboot�׶Σ��Ա㵼���ɼ����ݣ�
             SFTƽ̨A��ʹ�ã�����ֱ�ӷ���-1
 �������  : NA
 �������  : ��
 �� �� ֵ  : OK-ִ��������ERROR-��ִ������
 ���ú���  : NA
 ��������  : NA



*****************************************************************************/
static INLINE BSP_S32 DRV_EDMA_BBP_SAMPLE_REBOOT(BSP_VOID)
{
    return -1;
}

#endif

