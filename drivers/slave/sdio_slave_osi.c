

/*lint -e826*/
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/ipc.h>
#include <linux/string.h>
#include <linux/spinlock_types.h>
#include <mach/hardware.h>
#include <asm/cacheflush.h>
#include <asm/io.h>
#include <linux/dma-mapping.h>
#include "drv_comm.h"
#include "drv_memory.h"
#include "sdio_slave_cfg.h"
#include "sdio_slave.h"
#include "sdio_slave_osi.h"
#include "sdio_slave_hal.h"
#include "sdio_slave_errcode.h"
#include "bsp_regulator.h"
#include "bsp_clk.h"
/* wait ��Ϊ��װ */
#define SLAVE_BLOCK_T struct semaphore

#define SLAVE_BLOCK_CREATE(block) \
do {\
    sema_init(&(block),0);\
}while(0)

#define SLAVE_BLOCK_DELETE(block) \
do{\
    (block) = NULL;\
}while(0)


static int debug;
module_param(debug, int, 1);
MODULE_PARM_DESC(debug, "sdcc debug, set to >0 for debug (default 0)");

struct arasan_sido_log  arasan_sdio_logs;
#define SLAVE_DEBUG

#ifdef SLAVE_DEBUG
#define DBG(fmt, ...) \
	do { \
		pr_debug("[%s]"fmt, __func__, ##__VA_ARGS__); \
	}while(0)
#else
#define DBG(fmt, ...)	do{}while(0)
#endif

#define ERR(fmt, ...)   pr_err("[%s]"fmt, __func__, ##__VA_ARGS__)
#define INFO(fmt, ...)   pr_info("[%s]"fmt, __func__, ##__VA_ARGS__)
#define SLAVE_BLOCK_ENTER(block) (VOID)down (&(block))
#define SLAVE_BLOCK_LEAVE(block) (VOID)up (&(block))

typedef BSP_S32 (*FnEnumCfg)(BSP_VOID); /*�豸ö��*/
typedef BSP_VOID (*SLAVE_WRITE_DONE_CB_T)();/*д��ʼ�ص�*/
typedef BSP_VOID (*SLAVE_READ_DONE_CB_T)(); /*����ɻص�*/

typedef struct tagSLAVE_RX_PRIV_S
{
    SLAVE_READ_DONE_CB_T readDoneCB;
    struct semaphore       stRdBlockSem;//�������ź���
}SLAVE_RX_PRIV_S;

/* send list ѭ��˫������*/
typedef struct tagSLAVE_ITEM_S
{
    BSP_VOID        *addr;
    BSP_VOID        *addrPhy;
    BSP_U32         dlen;
} SLAVE_ITEM_S;

/* ����ڵ���Ϣ */
typedef struct tagSLAVE_NODE_INFO
{
    struct list_head stList;
    SLAVE_ITEM_S stItem;
}SLAVE_NODE_INFO;

typedef struct tagSLAVE_TX_PRIV_S
{
    SLAVE_NODE_INFO *pNodeInfo;
    SLAVE_NODE_INFO *pCurNode;
    struct list_head free_list;
    struct list_head use_list;
    BSP_U32 u32NodeNo;
    BSP_U32 u32NodeInUse;                  /*ʹ���е�����ڵ���*/
    SLAVE_WRITE_DONE_CB_T writeDoneCB;
    struct semaphore stWrBlockSem;            /*д�����ź���*/
	    unsigned int mount;
    BSP_BOOL bCached;
}SLAVE_TX_PRIV_S;

/*���ݽ���Buffer*/
typedef struct tagSLAVE_RX_SUB_S
{
    BSP_U32    TotalLen;            /*��Ч���ݴ�С*/
    BSP_U32    WrInLen;             /*hostд������ݳ���*/
    BSP_U8     *pWrite;             /*дָ��*/
    BSP_U8     *pRead;              /*��ָ��*/
    BSP_U8     *pStart;             /*buffer����ʼ��ַ*/
    BSP_U8     *pStartPhy;             /*buffer����ʼ��ַ*/
	unsigned int full;
	unsigned int empty;
spinlock_t	lock;
}SLAVE_RX_SUB_S;

/* SLAVE�豸�ṹ�� */
typedef struct tagSLAVE_DEV_S
{
    BSP_U32 intLvl;
    BSP_U32 RegBase;
    BSP_U32 SlaveCatalog;
    FnEnumCfg pFnEnumCfg;
    SLAVE_RX_PRIV_S stReadPrv;
    SLAVE_TX_PRIV_S stWritePrv;
    SLAVE_RX_SUB_S *stReadCntl;       /*����buffer����*/

    BSP_U8 *pCis0DataBuffer;         /*Cis0buffer*/
    BSP_U8 *pCis0DataBuffer_NotAlign;
    dma_addr_t  pCis0DataBufferPhy;
    dma_addr_t  pCis0DataBufferPhy_NotAlign;

    BSP_U8 *pCis1DataBuffer;         /*Cis1������*/
    BSP_U8 *pCis1DataBuffer_NotAlign;
    dma_addr_t  pCis1DataBufferPhy;
    dma_addr_t  pCis1DataBufferPhy_NotAlign;

    BSP_U8 *pCsaDataBuffer;         /*1K csa buffer*/
    BSP_U8 *pCsaDataBuffer_NotAlign;
    dma_addr_t  pCsaDataBufferPhy;
    dma_addr_t  pCsaDataBufferPhy_NotAlign;

    BSP_U8 *pRecvDataBuff;          /*32K data recv buffer*/
    BSP_U8 *pRecvDataBuff_NotAlign;
    dma_addr_t  pRecvDataBuffPhy;
    dma_addr_t  pRecvDataBuffPhy_NotAlign;

    BSP_U32    pCSALast;              /*��һ�ΰ������CSAָ��*/
    ADMA_HANDLE_S *stAdmaInfoHandle;  /*FUN0������*/
    ADMA_HANDLE_S *stAdmaRxHandle;    /*���ݽ���������*/
    ADMA_HANDLE_S *stAdmaSendHandle;  /*���ݷ���������*/
    SLAVE_STAT_S *pstSlaveStat;       /*״̬��Ϣ*/
    BSP_U32     msgCurrent;           /*��ǰ��Ϣֵ*/
	struct regulator *sdcc_regulator;
	struct clk *sdcc_clk;
	
}SLAVE_DEV_S;

/*SLAVE IP REG INFO�ṹ��*/
typedef struct tagSLAVE_RegInfo_S
{
    BSP_U32  u32BlockSize;
    BSP_U32  u32Arg;
    BSP_U32  RegAddr;
    BSP_U32  u32blockCnt;
    BSP_U32  TotalLen;
    BSP_BOOL b_BlockMode;
    BSP_BOOL b_OpMode;
    BSP_BOOL bTranDir;
}SLAVE_RegInfo_S;

/*SLAVE �����Ľṹ��*/
typedef struct tagSLAVE_CTX_S
{
    BSP_BOOL bSlaveInit;
    BSP_S32 task_id;
    SLAVE_DEV_S *pstSlaveDev;
    struct work_struct dsr_work;
	struct tasklet_struct tasklet;
    SLAVE_INTMSG_S IntMsg;
}SLAVE_CTX_S;

/*ȫ�ֱ�������*/

SLAVE_CTX_S g_stSlaveCtx = {0};

BSP_U32 g_u32SlaveBase;
SLAVE_BLOCK_T sem_id;
SLAVE_RX_SUB_S  *stRcv;

/*ö��ָ������*/
FnEnumCfg arrEnumCfg[SLAVE_CATALOG_MAX] =
{
    SLAVE_IOEnumCfg,         /*io only enum function*/
    SLAVE_MEM_EnumCfg,      /*mem only enum function*/
    SLAVE_IOMEM_EnumCfg     /*io mem enum function*/
};

/* Using default values supplied by Arasan for CIS0 and CIS1 */
const BYTE CIS0_Data[] = { 0x21,	// TPL_CODE_CISTPL_FUNCID
						   0x02,	// Link to next tuple
						   0x0C,	// Card function code
						   0x06,	// Not used
						   0x22,	// TPL_CODE_CISTPL_FUNCE
						   0x04,	// Link to next tuple
						   0x00,	// Extended data
						   0x00,	// Only block size function 0 can support (2048 = 0x0800)  // was 0x08
						   0x08,	// Together with previous byte							   // was 0x00
						   0x32,	// Transfer rate (25 Mbit/sec)
						   0x20,	// TPL_CODE_CISTPL_MANFID
						   0x04,	// Link to next tuple
						   0x96,	// SDIO manufacturer code 0x0296
						   0x02,	// Used with previous byte
						   0x47,	// Part number/revision number OEM ID = 0x5347
						   0x53,	// Used with previous byte
						   0xFF};	// End of tuple chain

const BYTE CIS1_Data[] = { 0x21,	// TPL_CODE_CISTPL_FUNCID
						   0x02,	// Link to next tuple
						   0x0C,	// Card function type
						   0x00,	// Not used
						   0x22,	// TPL_CODE_CISTPL_FUNCE

						   //0x28,	// Link to next tuple		// was 0x1c
						   0x2A,	// Link to next tuple		// was 0x1c
						   // Modify end

						   0x01,	// Type of extended data
						   0x01,	// Wakeup support
						   0x11,	// X.Y revision				// was 0x00
						   0x00,	// No serial number
						   0x00,	// No serial number
						   0x00,	// No serial number
						   0x00,	// No serial number
						   0x00,	// Size of the CSA space available for this function in bytes (0)
						   0x00,	// Used with previous
						   0x02,	// Used with previous		// was 0x00
						   0x00,	// Used with previous
						   0x03,	// CSA property: Bit 0 - 0 implies R/W capability in CSA
									// Bit 1 - 0 implies the Host may reformat the file system
						   0x00,	// Maximum block size (256 bytes)		// was 0x80
						   0x08,	// Used with previous					// was 0x00
						   0x00,	// OCR value of the function			// was 0x08
						   0x08,	// Used with previous					// was 0x01
						   0xFF,	// Used with previous					// was 0xff
						   0x00,	// Used with previous
						   0x08,	// Minimum power required by this function (8 mA)
						   0x0a,    // ADDED => Average power required by this function when operating (10 mA)
						   0x0f,    // ADDED => Maximum power required by this function when operating (15 mA)
						   0x01,	// Stand by is not supported		// was 0x00
						   0x01,	// Used with previous				// was 0x00
						   0x01,	// Used with previous				// was 0x00
						   0x00,	// Minimum BW
						   0x00,	// Used with previous
						   0x00,	// Optional BW
						   0x00,	// Used with previous
						   0x00,	// Card required no timeout
						   0x00,
						   0x00,
						   0x00,
						   0x00,	// High power mode - average power
						   0x00,	// High power function is not supported
						   0x00,
						   0x00,
						   0x00,	// High power mode - peak power
						   0x00,	// High power function is not supported
						   0x00,
						   0x00,

						   0x00,
						   0x00,
						   // Modify end

						   0x91,    // TPL_CODE_CISTPL_SDIO_STD

						   //0x00,	// TPL_LINK
						   0x02,	// TPL_LINK
						   // Modify end

						   0x07,	// SDIO Standard I/O device type
						   0x00,	// Format and type of data
						   0xFF};	// End of tuple

BSP_VOID    SLAVE_RegShow(void);
BSP_VOID    SLAVE_Susp(void);
BSP_VOID    SLAVE_Resume(void);
BSP_VOID    SLAVE_SoftRst(void);
BSP_VOID    SLAVE_Abort(void);
BSP_VOID    SLAVE_deinit(void);
irqreturn_t SLAVE_isr(int irq, void* dev);
BSP_VOID    slave_device_delete(SLAVE_DEV_S *pstSlaveDev);
BSP_VOID    SLAVE_ADMA_Deinit(ADMA_HANDLE_S *pstAdmaHandle);
BSP_VOID    handle_fun0_int(SLAVE_CTX_S *pstSlaveCtx, SLAVE_INTMSG_S *pstIntMsg);
BSP_VOID    handle_fun1_int(SLAVE_CTX_S *pstSlaveCtx, SLAVE_INTMSG_S *pstIntMsg);
BSP_VOID    handle_mem_int(SLAVE_CTX_S *pstSlaveCtx,SLAVE_INTMSG_S *pstIntMsg);
BSP_S32     FUN1_MsgIntProcess(SLAVE_CTX_S *pstSlaveCtx);
BSP_S32     FUN1_DataReadTrans(SLAVE_CTX_S *pstSlaveCtx);
BSP_S32     FUN1_DataWriteTrans(SLAVE_CTX_S *pstSlaveCtx);
BSP_S32     FUN1_EndDataTrans(SLAVE_CTX_S *pstSlaveCtx);
BSP_S32     FUN1_DataWriteOver(SLAVE_CTX_S *pstSlaveCtx);
BSP_S32     FUN1_DataReadOver(SLAVE_CTX_S *pstSlaveCtx);
BSP_S32     FUN0_InfoReadTrans(SLAVE_CTX_S *pstSlaveCtx);
BSP_S32     FUN0_CsaWriteTrans(SLAVE_CTX_S *pstSlaveCtx);
BSP_S32     FUN0_InfoReadOver(SLAVE_CTX_S *pstSlaveCtx);
BSP_S32     FUN0_CsaWriteOver(SLAVE_CTX_S *pstSlaveCtx);
BSP_S32     FUN0_EndIntTrans(SLAVE_CTX_S *pstSlaveCtx);
BSP_VOID    SLAVE_task_dsr(void);
BSP_S32     SLAVE_GET_IdleSize(SLAVE_CTX_S *pstSlaveCtx,BSP_U32 *u32IdleSize);
BSP_VOID    SLAVE_GET_DataSize(SLAVE_CTX_S *pstSlaveCtx,BSP_U32 *u32BuffSize);
BSP_BOOL    SLAVE_Buff_IsEmpty(SLAVE_CTX_S *pstSlaveCtx);
BSP_BOOL    SLAVE_Buff_IsFull(SLAVE_CTX_S *pstSlaveCtx);
BSP_VOID    SLAVE_ClrStatCnt(BSP_S32 s32SlaveDevId);
BSP_VOID    SLAVE_RECV_BuffRst(SLAVE_RX_SUB_S *stRcv);
extern BSP_VOID* BSP_SMalloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags);
extern BSP_VOID  BSP_SFree(BSP_VOID* pMem);
SLAVE_NODE_INFO* GetOffNodeFromUseList(SLAVE_CTX_S* stSlaveCtx);
BSP_VOID AddNodeToFreeList(SLAVE_CTX_S* stSlaveCtx, SLAVE_NODE_INFO* pNode);
BSP_U32 GetListNodeNum(SLAVE_CTX_S* stSlaveCtx);
SLAVE_NODE_INFO* GetOffNodeFromFreeList(SLAVE_CTX_S* stSlaveCtx);
BSP_VOID AddNodeToUseList(SLAVE_CTX_S* stSlaveCtx, SLAVE_NODE_INFO* pNode);
BSP_VOID ADMA_Desc_Queue_Config(
    ADMA_HANDLE_S *pstAdmaHandle,
	SLAVE_RX_SUB_S *stReadCntl,
	BSP_U32 u32NodeAddr,
    BSP_U32 u32NodeAddrPhy,
    BSP_U32 u32len,
    BSP_U32 u32NodeCnt,
    unsigned int split,
    BSP_BOOL TrsDirFlg
    );


BSP_S32 OS_task_create(BSP_S8 *tskName, BSP_S32 taskPri, BSP_S32 taskStack,
                                         BSP_VOID *taskDsr, BSP_VOID *taskArg)
{
	return kthread_run(taskDsr,(int)taskArg,(char*)tskName);
}

BSP_VOID OS_task_delete(BSP_S32 task_id)
{
    if(BSP_ERROR != task_id)
    {
        kthread_stop(task_id);
    }
}

ADMA_CACHE_OP_S s_stAdmaCacheOp =
{
#ifdef ADMA_DESC_CACHE
    BSP_TRUE
#else
    BSP_FALSE
#endif
    ,
#ifdef TX_BUF_FLUSH_CACHE
    BSP_TRUE
#else
    BSP_FALSE
#endif
    ,
#ifdef RX_BUF_INVALIDATE_CACHE
    BSP_TRUE
#else
    BSP_FALSE
#endif
};

BSP_VOID ADMA_SetCacheOp(BSP_U32 u32OpIdx,BSP_BOOL bFlag)
{
    if(0 == u32OpIdx)
        s_stAdmaCacheOp.bFlushDesc = bFlag;
    else if(1 == u32OpIdx)
        s_stAdmaCacheOp.bTxBuf = bFlag;
    else if(2 == u32OpIdx)
        s_stAdmaCacheOp.bRxBuf = bFlag;
    else
        return ;
}

BSP_VOID ADMA_ShowCacheOp(BSP_VOID)
{
    printk("bFlushDesc    :%d\n",s_stAdmaCacheOp.bFlushDesc);
    printk("bTxBuf        :%d\n",s_stAdmaCacheOp.bTxBuf);
    printk("bRxBuf        :%d\n",s_stAdmaCacheOp.bRxBuf);
}

BSP_U32 adma_desc_type[ADMA_DESC_TYPE_MAX]=
{
    (ATTRIB_ACT_TRANS|ATTRIB_FLAG_VALID),                         //PARTITION_TYPE_HEAD
    (ATTRIB_ACT_TRANS|ATTRIB_FLAG_VALID),                         //PARTITION_TYPE_MID
    (ATTRIB_ACT_TRANS|ATTRIB_FLAG_VALID|ATTRIB_FLAG_END),         //PARTITION_TYPE_TAIL
    (ATTRIB_ACT_TRANS|ATTRIB_FLAG_VALID|ATTRIB_FLAG_END),         //PARTITION_TYPE_TOTAL
    (ATTRIB_FLAG_NOP|ATTRIB_FLAG_VALID)
};

/* ��ȡ���ݷֶ����� */
ADMA_DESC_TYPE_E ADMA_get_node_type(BSP_U32 i,BSP_U32 cnt)
{
    if(1 == cnt)    return ADMA_DESC_TYPE_TOTAL;
    else if(i == 0) return ADMA_DESC_TYPE_HEAD;
    else if(i == cnt-1) return ADMA_DESC_TYPE_TAIL;
    else    return ADMA_DESC_TYPE_MID;
}

BSP_VOID *SLAVE_memalloc(BSP_U32 align, BSP_U32 size)
{
	//return align?memalign (align,(size_t)size):malloc(size);
	return kmalloc(size,GFP_KERNEL|GFP_DMA);
}

BSP_VOID SLAVE_memfree(BSP_VOID *addr)
{
    kfree(addr);
}

BSP_VOID *SLAVE_desc_memalloc(BSP_U32 align, BSP_U32 size, BSP_U32 *addr)
{
#if defined ADMA_DESC_MEM_NOCACHEABLE
    *addr = (BSP_U32)kmalloc(size,GFP_KERNEL);
#elif defined ADMA_DESC_MEM_CACHEABLE
   	*addr = (BSP_U32)kmalloc(size,GFP_KERNEL|GFP_DMA);
#endif
    return (BSP_VOID*)(*addr);
}

BSP_VOID SLAVE_desc_memfree(BSP_VOID *addr)
{
    kfree(addr);
}

BSP_VOID *SLAVE_alloc_memory(BSP_U32 align_size, BSP_U32 size, BSP_U32 *addr,
                                    MEM_SDIO_POOL_TYPE typeIdx)
{

    if(MEM_SDIO_DDR_CACHE_POOL == typeIdx)
       *addr = (BSP_U32)kmalloc(size,GFP_KERNEL);

    else if(MEM_SDIO_DDR_NOCACHE_POOL == typeIdx)
// *addr = (BSP_U32)cacheDmaMalloc(size);
           *addr = (BSP_U32)kmalloc(size,GFP_KERNEL);
    else if(MEM_SDIO_AXI_POOL == typeIdx)
           *addr = (BSP_U32)kmalloc(size,GFP_KERNEL);
// *addr = (BSP_U32)BSP_SMalloc(DATA_BUF_SIZE,MEM_ICC_AXI_POOL);
    //else if(MEM_SDIO_ACP_APP == typeIdx)
       // *addr = (BSP_U32)BSP_SMalloc(DATA_BUF_SIZE,MEM_ICC_AXI_POOL);  /*Ԥ����ACPʹ��*/
    else
    {
        printk("desc mem macro undefined\n");
        return (BSP_VOID *)BSP_NULL;
    }
    return (BSP_VOID*)(*addr);
}

BSP_VOID SLAVE_free_memory(BSP_VOID *addr,MEM_SDIO_POOL_TYPE typeIdx)
{
    if(MEM_SDIO_DDR_CACHE_POOL == typeIdx)
		kfree(addr);
    else if(MEM_SDIO_ACP_APP == typeIdx)
		kfree(addr);
    else
        //BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SLAVE,"desc mem free undefined\n");
        printk("desc mem free undefined\n");
}

/*****************************************************************************
* �� �� ��  : ADMA_config_desc
*
* ��������  : ����������
*
* �������  : admahandle: �����������ePartType:�������������ͣ�
*             address:��������ַ��,   len:      ������������
* �������  : desc_over:������ָ��
*
* �� �� ֵ  : ����������
*
*****************************************************************************/
BSP_U32 ADMA_config_desc(ADMA_HANDLE_S *admahandle,ADMA_DESC_TYPE_E ePartType,
    BSP_U32 address,BSP_U16 len, ADMA_DESC_S **desc_over)
{
    BSP_U32  next = admahandle->Next;
    ADMA_DESC_S *desc = admahandle->Desc + next;

    desc->BufferLen = len;
    desc->Attribute = (BSP_U16)adma_desc_type[ePartType];
 	desc->NodeAddr = address;

    admahandle->Next = (next + 1 != admahandle->DescCount)?next + 1:0;
    *desc_over = desc;
    return next;
}

/*****************************************************************************
* �� �� ��  : ADMA_alloc_desc_queue
*
* ��������  : ��������������
*
* �������  : admahandle: �����������no_of_desc:����������
* �������  : ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 ADMA_alloc_desc_queue(ADMA_HANDLE_S *admahandle, BSP_U32 no_of_desc)
{
    ADMA_DESC_S *first_desc = BSP_NULL;
    dma_addr_t dma_addr;
    int size;

    admahandle->DescCount = 0;

    DBG("total size required:0x%x\n",sizeof(ADMA_DESC_S) * no_of_desc);

    size = sizeof(ADMA_DESC_S) * no_of_desc + SLAVE_CACHE_ALIGN;
    first_desc = (ADMA_DESC_S *)dma_alloc_coherent(NULL, size, &dma_addr, GFP_DMA|__GFP_WAIT);

    if(!first_desc)
    {
        //BSP_TRACE(BSP_LOG_LEVEL_ERROR,BSP_MODU_SLAVE,"Error in Desc mem alloc\n",1,2,3,4,5,6);
		printk("Error in Desc mem alloc\n");
        return SLAVE_ERROR;
    }

    bzero((BSP_VOID *)first_desc, size);
    admahandle->DescCount = no_of_desc - 1;
    admahandle->Desc = first_desc;
	admahandle->size = size;
	admahandle->Desc_Phy = dma_addr;
    admahandle->DescDma = dma_addr;
    admahandle->Next = 0;
    admahandle->NextDesc = admahandle->Desc;

    DBG("Desc %d: 0x%08x, 0x%08x\n", no_of_desc, admahandle->Desc, admahandle->DescDma);

    /*ˢ������*/
    //ADMA_FLUSH_DESC(admahandle,0,admahandle->Desc,admahandle->DescCount,s_stAdmaCacheOp.bFlushDesc);

    return SLAVE_OK;
}

/*****************************************************************************
* �� �� ��  : ADMA_free_desc_queue
*
* ��������  : �ͷ�����������
*
* �������  : admahandle: ���������
* �������  : ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_VOID ADMA_free_desc_queue(ADMA_HANDLE_S *pstAdmahandle)
{
    //SLAVE_desc_memfree((BSP_VOID*)pstAdmahandle->Desc);

    dma_free_coherent(NULL, pstAdmahandle->size, \
								(void*)pstAdmahandle->Desc, (dma_addr_t)pstAdmahandle->Desc_Phy);

    pstAdmahandle->Desc = BSP_NULL;
	pstAdmahandle->Desc_Phy = 0;
    pstAdmahandle->DescDma = 0;
}

/*****************************************************************************
* �� �� ��  : SLAVE_Adma_Init
*
* ��������  : ADMA��ʼ��
*
* �������  : admahandle: ���������, no_of_desc:Ԥ��������������
* �������  : ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 SLAVE_Adma_Init(ADMA_HANDLE_S *pstAdmahandle,BSP_U32 no_of_desc)
{

    if(!pstAdmahandle)
    {
        printk("ADMA handle null pointer\n");
        return SLAVE_ERR_NULL_POINTER;
    }

    /* ���丨��buf */
    pstAdmahandle->assist_buf_notalign = dma_alloc_coherent(NULL,SLAVE_UNALIGN_ASSIST_BUFF_LEN, &pstAdmahandle->assist_buf_phy_notalign, GFP_DMA|__GFP_WAIT);
    if(!pstAdmahandle->assist_buf_notalign)
    {
        printk("ADMA assist buf malloc failed\n");
        return SLAVE_ERR_MALLOC_FAILED;
    }
	pstAdmahandle->assist_buf_len = SLAVE_UNALIGN_ASSIST_BUFF_LEN;
    pstAdmahandle->assist_buf = ADMA_SKIP_NOALIGN(((int)pstAdmahandle->assist_buf_notalign));
    pstAdmahandle->assist_buf_phy = (dma_addr_t)ADMA_SKIP_NOALIGN(pstAdmahandle->assist_buf_phy_notalign);

    DBG("Assist Buffer: 0x%08x, 0x%08x\n",
                pstAdmahandle->assist_buf,
                pstAdmahandle->assist_buf_phy);

    /* ������������ ��Ϊ�����������ڴ�ռ�*/
    if(SLAVE_OK != ADMA_alloc_desc_queue(pstAdmahandle, no_of_desc))
    {
        dma_free_coherent(NULL,SLAVE_UNALIGN_ASSIST_BUFF_LEN, pstAdmahandle->assist_buf_notalign, pstAdmahandle->assist_buf_phy_notalign);
        pstAdmahandle->assist_buf = BSP_NULL;
        printk("ADMA desc queue malloc failed\n");
        return SLAVE_ERR_MALLOC_FAILED;
    }

    /*����������������ɱ�־*/
    pstAdmahandle->bDescSetupFlag = BSP_TRUE;
    return SLAVE_OK;

}

/*****************************************************************************
* �� �� ��  : SLAVE_Adma_Deinit
*
* ��������  : ADMAȥ��ʼ��
*
* �������  : admahandle: ���������
* �������  : ��
*
* �� �� ֵ  : ��
*
*****************************************************************************/
BSP_VOID SLAVE_ADMA_Deinit(ADMA_HANDLE_S *pstAdmaHandle)
{
    if(BSP_NULL != pstAdmaHandle->Desc)
    {
        ADMA_free_desc_queue(pstAdmaHandle);
    }

    if(BSP_NULL != pstAdmaHandle->assist_buf)
    {
        dma_free_coherent(NULL, SLAVE_UNALIGN_ASSIST_BUFF_LEN,
                                     pstAdmaHandle->assist_buf_notalign,
                                     pstAdmaHandle->assist_buf_phy_notalign);
        //SLAVE_memfree(pstAdmaHandle->assist_buf);
    }

    if(BSP_NULL != pstAdmaHandle)
    {
        SLAVE_memfree((BSP_VOID*)pstAdmaHandle);
    }
}

/*****************************************************************************
* �� �� ��  : ADMA_Desc_Queue_Config
*
* ��������  : SLAVE���ݷ��ͽ���
*
* �������  : ADMA_HANDLE_S *pstAdmaHandle  :���������
*             BSP_U32 u32buf                :���ݻ���
*             BSP_U32 u32len                :���ݳ���
*             BSP_U32 s32NodeCnt            :�ڵ����
*             BSP_BOOL TrsDirFlg            :���䷽���־
* �������  : ��
* ����ֵ    : ��
*****************************************************************************/
BSP_VOID ADMA_Desc_Queue_Config(
    ADMA_HANDLE_S *pstAdmaHandle,
	SLAVE_RX_SUB_S *stReadCntl,
	BSP_U32 u32NodeAddr,
    BSP_U32 u32NodeAddrPhy,
    BSP_U32 u32len,
    BSP_U32 u32NodeCnt,
    unsigned int split,
    BSP_BOOL TrsDirFlg      //1��ʾ��host to slave,0��ʾslave to host
)
{
    BSP_U32 i = 0;
    BSP_U32 u32DescAddr = 0;
    ADMA_DESC_S *desc = BSP_NULL;
    ADMA_DESC_S *descHead = BSP_NULL;
    BSP_U32 u32Desclen = 0;
    BSP_U32 len_remain = u32len;
    ADMA_DESC_TYPE_E eDescType = ADMA_DESC_TYPE_NULL;

	unsigned int remain_align;
	unsigned int remain_align_len;
    BSP_BOOL addr_align_flag = ADMA_CHECK_ALIGN((BSP_U32)u32NodeAddrPhy);
    BSP_U32 buf_skip_noalign_addr = ADMA_SKIP_NOALIGN((BSP_U32)u32NodeAddrPhy);
    BSP_U32 noalign_bytes = ADMA_GET_NOALIGN_BYTES((BSP_U32)u32NodeAddrPhy);
    BSP_U32 align_bytes = ADMA_GET_ALIGN_BYTES((BSP_U32)u32NodeAddrPhy,(BSP_U32)u32len);

	/*always use assit buff unless buff*/
	if (!addr_align_flag && len_remain > pstAdmaHandle->assist_buf_len) {

        dma_free_coherent(NULL,pstAdmaHandle->assist_buf_len, pstAdmaHandle->assist_buf_notalign, pstAdmaHandle->assist_buf_phy_notalign);
	    /* ���丨��buf */

	    pstAdmaHandle->assist_buf_notalign = dma_alloc_coherent(NULL,
	    		max(len_remain, 2*pstAdmaHandle->assist_buf_len),
	    		&pstAdmaHandle->assist_buf_phy_notalign, GFP_DMA|GFP_ATOMIC);

		if(!pstAdmaHandle->assist_buf_notalign)
	    {
	        DBG("alloc a %d ADMA assist buf failed\n", len_remain);
	        return SLAVE_ERR_MALLOC_FAILED;
	    }
		pstAdmaHandle->assist_buf_len *= 2;
	    pstAdmaHandle->assist_buf = ADMA_SKIP_NOALIGN(((int)pstAdmaHandle->assist_buf_notalign));
	    pstAdmaHandle->assist_buf_phy = (dma_addr_t)ADMA_SKIP_NOALIGN(pstAdmaHandle->assist_buf_phy_notalign);

	    DBG("Assist Buffer: 0x%08x, 0x%08x, len: 0x%08x\n",
	                pstAdmaHandle->assist_buf,
	                pstAdmaHandle->assist_buf_phy, len_remain);

	}

	remain_align =0;

	if (split && stReadCntl) {
		remain_align_len = DATA_BUF_SIZE + (unsigned int)(stReadCntl->pStart - stReadCntl->pWrite);
		/*8k align*/
		remain_align = remain_align_len >> 0xd;
		remain_align_len -= (remain_align << 0xd);
	}

    for(i = 0; i < u32NodeCnt; i++)
    {
        /* �����ַ�����룬��һ��������ʹ�ø���buf */
        if((0 == i)&&(!addr_align_flag)&&(!TrsDirFlg))
        {
        	DBG("read use assist buff\n");
            memcpy((BSP_VOID *)pstAdmaHandle->assist_buf,(BSP_U8 *)u32NodeAddr,(BSP_U32)noalign_bytes);
        }

        /* �ж������������� */
        eDescType = ADMA_get_node_type(i,(BSP_U32)u32NodeCnt);
        switch(eDescType)
        {
            case ADMA_DESC_TYPE_TOTAL:
                u32DescAddr =
                (addr_align_flag)?u32NodeAddrPhy:(BSP_U32)pstAdmaHandle->assist_buf_phy;
                u32Desclen = (BSP_U32)BSP_MIN(ADMA_BUF_MAXSIZE,u32len);
                pstAdmaHandle->Next  =  0;
                break;

          case ADMA_DESC_TYPE_HEAD:
				if (!TrsDirFlg) {
			                u32DescAddr =
			                (addr_align_flag)?buf_skip_noalign_addr:(BSP_U32)pstAdmaHandle->assist_buf_phy;
			                u32Desclen = (addr_align_flag)?ADMA_BUF_MAXSIZE: noalign_bytes;
			                pstAdmaHandle->Next  =  0;
						break;
				} else {
			              pstAdmaHandle->Next  =  0;

				}
            case ADMA_DESC_TYPE_MID:
				if (!TrsDirFlg) {
		                u32DescAddr = (addr_align_flag)?(buf_skip_noalign_addr+i*ADMA_BUF_MAXSIZE):(buf_skip_noalign_addr+(i-1)*ADMA_BUF_MAXSIZE);
				} else {
			                u32DescAddr = (addr_align_flag)?(u32NodeAddrPhy
						+ i*ADMA_BUF_MAXSIZE):((BSP_U32)pstAdmaHandle->assist_buf_phy
						+ i*ADMA_BUF_MAXSIZE);
				}
				u32Desclen = ADMA_BUF_MAXSIZE;

                break;

            case ADMA_DESC_TYPE_TAIL:
				if (!TrsDirFlg) {
			                u32DescAddr = (addr_align_flag)?(buf_skip_noalign_addr+i*ADMA_BUF_MAXSIZE):(buf_skip_noalign_addr+(i-1)*ADMA_BUF_MAXSIZE);
				} else {
         			       u32DescAddr = (addr_align_flag)?(u32NodeAddrPhy+i*ADMA_BUF_MAXSIZE):(u32NodeAddrPhy+i*ADMA_BUF_MAXSIZE);
				}
				u32Desclen = (BSP_U32)BSP_MIN(len_remain,ADMA_BUF_MAXSIZE);
                break;

            default:
                break;
        	}


		if (split && remain_align == i) {
			DBG("split at the %d desc, buffer(0x%0x)remain len(%d)\n", remain_align, u32DescAddr, remain_align_len);
			u32Desclen = remain_align_len;
		}
		if (split && stReadCntl && remain_align == i - 1) {
			u32DescAddr = stReadCntl->pStartPhy;
			DBG("set %d desc buffer(0x%0x)\n", i, u32DescAddr);

		}
        /* ��������� */
        (void)ADMA_config_desc(pstAdmaHandle,eDescType,u32DescAddr,(BSP_U16)u32Desclen,&desc);
        if((ADMA_DESC_TYPE_TOTAL == eDescType)||(ADMA_DESC_TYPE_HEAD == eDescType)||(ADMA_DESC_TYPE_NULL == eDescType))
        {
            descHead = desc;
        }

        len_remain -= u32Desclen;
    }
    {
        int j;
	int curr = arasan_sdio_logs.curr;
        for(j=0;j<(int)u32NodeCnt;j++)
        {
		arasan_sdio_logs.desc[curr + j].addr = pstAdmaHandle->Desc[j].NodeAddr;
		arasan_sdio_logs.desc[curr + j].len = pstAdmaHandle->Desc[j].BufferLen;
		arasan_sdio_logs.desc[curr + j].dir = TrsDirFlg;

            DBG("desc[%d]: addr=0x%x, len=%d, type=0x%x\n", j,
				(int)pstAdmaHandle->Desc[j].NodeAddr,
				(int)pstAdmaHandle->Desc[j].BufferLen,
				(int)pstAdmaHandle->Desc[j].Attribute);
        }
	arasan_sdio_logs.curr += u32NodeCnt;

    }

	return;
}

/*****************************************************************************
* �� �� ��  : SlaveDeinitList
*
* ��������  : SDIO SLAVE ȥ��ʼ��д������������
*
* �������  : stSlaveCtx: �豸�ڲ��ṹָ��

* �������  : ��
*
* �� �� ֵ  : ��
*
*****************************************************************************/
 BSP_VOID SlaveDeinitList(SLAVE_CTX_S * stSlaveCtx)
{
    BSP_U32 cnt = 0;

    /* ��ʼ��read���� */
    INIT_LIST_HEAD(&(stSlaveCtx->pstSlaveDev->stWritePrv.free_list));
    INIT_LIST_HEAD(&(stSlaveCtx->pstSlaveDev->stWritePrv.use_list));

    /* ��ʼ��ʱ,���нڵ㶼��FreeList */
    for (cnt = 0; cnt < stSlaveCtx->pstSlaveDev->stWritePrv.u32NodeNo; cnt++)
    {
        stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[cnt].stItem.addr = NULL;
        stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[cnt].stItem.addrPhy = NULL;
        stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[cnt].stItem.dlen = 0;
        stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[cnt].stList.next = NULL;
        stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[cnt].stList.prev= NULL;

    }

    if (NULL != stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo)
    {
	    kfree(stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo);
        stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo = NULL;
    }

    return;
}

/*****************************************************************************
* �� �� ��  : SlaveInitList
*
* ��������  : SDIO SLAVE ��ʼ����������������
*
* �������  : stSlaveCtx: �豸�ṹָ��
*             u32BuffNum: д����Ľڵ����
* �������  : ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
 BSP_S32 SlaveInitList(SLAVE_CTX_S * stSlaveCtx, BSP_U32 u32NodeNum)
{
    BSP_U8* pInfo = NULL;
    struct list_head *pNode = NULL;
    BSP_U32 cnt = 0;

    /* ��ʼ������Ϣ */
	pInfo = kmalloc(u32NodeNum*sizeof(SLAVE_NODE_INFO),GFP_KERNEL);
    if (NULL == pInfo)
    {
        goto SLAVE_INIT_LIST_FAIL;
    }
    memset((BSP_VOID*)pInfo, 0, (u32NodeNum*sizeof(SLAVE_NODE_INFO)));
    stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo = (SLAVE_NODE_INFO*)pInfo;
    stSlaveCtx->pstSlaveDev->stWritePrv.pCurNode = (SLAVE_NODE_INFO*)pInfo;

    /* ��ʼ��read���� */
    INIT_LIST_HEAD(&(stSlaveCtx->pstSlaveDev->stWritePrv.free_list));
    INIT_LIST_HEAD(&(stSlaveCtx->pstSlaveDev->stWritePrv.use_list));

    /* ��ʼ��ʱ,���нڵ㶼��FreeList */
    for (cnt = 0; cnt < u32NodeNum; cnt++)
    {
        stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[cnt].stItem.addr = NULL;
        stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[cnt].stItem.addrPhy = NULL;
        stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[cnt].stItem.dlen = 0;
        stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[cnt].stList.next = NULL;
        stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[cnt].stList.prev= NULL;

        pNode = &(stSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[cnt].stList);
        list_add_tail(pNode, &(stSlaveCtx->pstSlaveDev->stWritePrv.free_list));
    }
    stSlaveCtx->pstSlaveDev->stWritePrv.u32NodeNo = u32NodeNum;
    return SLAVE_OK;

SLAVE_INIT_LIST_FAIL:
    SlaveDeinitList(stSlaveCtx);
    return SLAVE_ERROR;
}

/*****************************************************************************
* �� �� ��  : AddNodeToFreeList
*
* ��������  : ��free_listĩ������һ���ڵ�
*
* �������  : stSlaveCtx: �豸�ṹָ��
*             pNode : �Ѿ�������ռ�Ľڵ�
* �������  : ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_VOID AddNodeToFreeList(SLAVE_CTX_S* stSlaveCtx, SLAVE_NODE_INFO* pNode)
{
    list_add_tail(&pNode->stList, &(stSlaveCtx->pstSlaveDev->stWritePrv.free_list));
    return;
}

/*****************************************************************************
* �� �� ��  : GetOffNodeFromFreeList
*
* ��������  : ��free_listȡ��һ���ڵ�
*
* �������  : stSlaveCtx: �豸�ڲ��ṹָ��
* �������  : ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
SLAVE_NODE_INFO* GetOffNodeFromFreeList(SLAVE_CTX_S* stSlaveCtx)
{
    struct list_head *pFreeHeader = &(stSlaveCtx->pstSlaveDev->stWritePrv.free_list);
    struct list_head *pFreeNode;
    SLAVE_NODE_INFO* pNode;

    if (list_empty(pFreeHeader))
    {
        return NULL;
    }
    pFreeNode = pFreeHeader->next;
    pNode = list_entry(pFreeNode, SLAVE_NODE_INFO, stList);

    list_del_init(pFreeNode);
    return pNode;
}

/*****************************************************************************
* �� �� ��  : AddNodeToUseList
*
* ��������  : ��use_listĩ�����һ���ڵ�
*
* �������  : stSlaveCtx: �豸�ڲ��ṹָ��
*             pNode : �Ѿ�������ռ�Ľڵ�
* �������  : ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_VOID AddNodeToUseList(SLAVE_CTX_S* stSlaveCtx, SLAVE_NODE_INFO* pNode)
{

    list_add_tail(&pNode->stList, &(stSlaveCtx->pstSlaveDev->stWritePrv.use_list));
    /*use_list�ڵ����*/
    stSlaveCtx->pstSlaveDev->stWritePrv.u32NodeInUse++;
}

/*****************************************************************************
* �� �� ��  : GetOffNodeFromUseList
*
* ��������  : ��use_listȡ��һ���ڵ�
*
* �������  : stSlaveCtx: �豸�ڲ��ṹָ��
* �������  : ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
SLAVE_NODE_INFO* GetOffNodeFromUseList(SLAVE_CTX_S* stSlaveCtx)
{
    struct list_head *pFreeHeader = &(stSlaveCtx->pstSlaveDev->stWritePrv.use_list);
    struct list_head *pFreeNode;
    SLAVE_NODE_INFO* pNode;

    if (list_empty(pFreeHeader))
    {
        return NULL;
    }
    pFreeNode = pFreeHeader->next;
    pNode = list_entry(pFreeNode, SLAVE_NODE_INFO, stList);

    list_del_init(pFreeNode);
    stSlaveCtx->pstSlaveDev->stWritePrv.u32NodeInUse--;
    return pNode;
}

/*****************************************************************************
* �� �� ��  : GetListNodeNum
*
* ��������  : ��ȡʹ�������еĽڵ���
* �������  : stSlaveCtx: �豸�ڲ��ṹָ��
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_U32 GetListNodeNum(SLAVE_CTX_S* stSlaveCtx)
{
    return stSlaveCtx ->pstSlaveDev->stWritePrv.u32NodeInUse;
}

/*****************************************************************************
* �� �� ��  : slave_device_create
*
* ��������  : �����豸�ṹ��
*
* �������  : ��
*
* �� �� ֵ  : �豸�ṹ��ָ��
*
*****************************************************************************/
SLAVE_DEV_S *slave_device_create(BSP_VOID)
{
    BSP_VOID *p;
    dma_addr_t phy_addr;

    BSP_U32 Cis0Len = sizeof(CIS0_Data)/sizeof(CIS0_Data[0]);
    BSP_U32 Cis1Len = sizeof(CIS1_Data)/sizeof(CIS1_Data[0]);

    SLAVE_DEV_S *pstSlaveDev = BSP_NULL;

    /* create dev struct*/
    p = SLAVE_memalloc(sizeof(BSP_U32), sizeof(SLAVE_DEV_S));
    if(!p)
    {
        printk("dev obj alloc failed!\n");
        goto exit;
    }
    memset(p,0,sizeof(SLAVE_DEV_S));
    pstSlaveDev = (SLAVE_DEV_S *)p;
   // pstSlaveDev->intLvl  = INT_LVL_SDCC;
    pstSlaveDev->intLvl  =INT_VEC_SDIO_SLAVE;
    pstSlaveDev->RegBase = g_u32SlaveBase;

    /*create Info Adma handle */
    p = SLAVE_memalloc(sizeof(BSP_U32), sizeof(ADMA_HANDLE_S));
    if(!p)
    {
        printk("stAdmaInfoHandle alloc failed!\n");
        goto exit;
    }
    memset(p,0,sizeof(ADMA_HANDLE_S));
    pstSlaveDev->stAdmaInfoHandle = p;

    /*create Rx Adma handle */
    p = SLAVE_memalloc(sizeof(BSP_U32), sizeof(ADMA_HANDLE_S));
    if(!p)
    {
        printk("stAdmaRxHandle alloc failed!\n");
        goto exit;
    }
    memset(p,0,sizeof(ADMA_HANDLE_S));
    pstSlaveDev->stAdmaRxHandle = p;

    /*create Send Adma handle */
    p = SLAVE_memalloc(sizeof(BSP_U32), sizeof(ADMA_HANDLE_S));
    if(!p)
    {
        printk("stAdmaSendHandle alloc failed!\n");
        goto exit;
    }
    memset(p,0,sizeof(ADMA_HANDLE_S));
    pstSlaveDev->stAdmaSendHandle = p;

    /*create rxctl struct */
    p = SLAVE_memalloc(sizeof(BSP_U32), sizeof(SLAVE_RX_SUB_S));
    if(!p)
    {
        printk("rxcnt alloc failed!\n");
        goto exit;
    }
    memset(p,0,sizeof(SLAVE_RX_SUB_S));
    pstSlaveDev->stReadCntl = p;

	pstSlaveDev->stReadCntl->empty = 1;
	pstSlaveDev->stReadCntl->full = 0;

    /* create slave status struct */
    p= SLAVE_memalloc(sizeof(BSP_U32), sizeof(SLAVE_STAT_S));
    if(!p)
    {
        printk("stat alloc failed!\n");
        goto exit;
    }
    memset(p,0,sizeof(SLAVE_STAT_S));
    pstSlaveDev->pstSlaveStat = p;

    /* creat csa buffer */
    p = dma_alloc_coherent(NULL, CSA_BUF_SIZE+SLAVE_CACHE_ALIGN, &phy_addr, GFP_DMA|__GFP_WAIT);
    if(!p)
    {
        printk("csa alloc failed!\n");
        goto exit;
    }
    memset(p, 0, CSA_BUF_SIZE+SLAVE_CACHE_ALIGN);
    pstSlaveDev->pCsaDataBuffer = ADMA_SKIP_NOALIGN(((int)p));
    pstSlaveDev->pCsaDataBufferPhy = ADMA_SKIP_NOALIGN(phy_addr);
    pstSlaveDev->pCsaDataBuffer_NotAlign = p;
    pstSlaveDev->pCsaDataBufferPhy_NotAlign = phy_addr;

    /* create data receive buffer  */
    p = dma_alloc_coherent(NULL, DATA_BUF_SIZE + SLAVE_CACHE_ALIGN, &phy_addr, GFP_DMA|__GFP_WAIT);
    if(!p)
    {
        printk("receive buffer alloc error!\n");
        goto exit;
    }
    memset(p, 0, DATA_BUF_SIZE + SLAVE_CACHE_ALIGN);
    pstSlaveDev->pRecvDataBuff = ADMA_SKIP_NOALIGN(((int)p));
    pstSlaveDev->pRecvDataBuffPhy = ADMA_SKIP_NOALIGN(phy_addr);
    pstSlaveDev->pRecvDataBuff_NotAlign = p;
    pstSlaveDev->pRecvDataBuffPhy_NotAlign = phy_addr;
    pstSlaveDev->stReadCntl->pStartPhy = phy_addr;
    /* create cis0 buffer */
    p = dma_alloc_coherent(NULL, Cis0Len+SLAVE_CACHE_ALIGN, &phy_addr, GFP_DMA|__GFP_WAIT);
    if(!p)
    {
        printk("cis0 alloc error!\n");
        goto exit;
    }
    memset(p, 0, Cis0Len+SLAVE_CACHE_ALIGN);
    pstSlaveDev->pCis0DataBuffer = ADMA_SKIP_NOALIGN(((int)p));
    pstSlaveDev->pCis0DataBufferPhy = ADMA_SKIP_NOALIGN(phy_addr);
    pstSlaveDev->pCis0DataBuffer_NotAlign = p;
    pstSlaveDev->pCis0DataBufferPhy_NotAlign = phy_addr;
#ifndef CONFIG_SDIO_ARASAN_V711
    memcpy(pstSlaveDev->pCis0DataBuffer, CIS0_Data, Cis0Len);
#else
    memcpy(pstSlaveDev->RegBase + 0x80, CIS0_Data, Cis0Len);
#endif

    /* create cis1 buffer */
    p = dma_alloc_coherent(NULL, Cis1Len+SLAVE_CACHE_ALIGN, &phy_addr, GFP_DMA|__GFP_WAIT);
    if(!p)
    {
        printk("cis1 mem alloc error!\n");
        goto exit;
    }
    memset(p, 0, Cis1Len+SLAVE_CACHE_ALIGN);
    pstSlaveDev->pCis1DataBuffer = ADMA_SKIP_NOALIGN(((int)p));
    pstSlaveDev->pCis1DataBufferPhy = ADMA_SKIP_NOALIGN(phy_addr);
    pstSlaveDev->pCis1DataBuffer_NotAlign = p;
    pstSlaveDev->pCis1DataBufferPhy_NotAlign = phy_addr;
#ifndef CONFIG_SDIO_ARASAN_V711
    memcpy(pstSlaveDev->pCis1DataBuffer, CIS1_Data, Cis1Len);
#else
    memcpy(pstSlaveDev->RegBase + 0xa0, CIS1_Data, Cis1Len);
#endif

    DBG("CIS0: 0x%08x,\n",pstSlaveDev->pCis0DataBufferPhy);
    DBG("CIS1: 0x%08x\n",pstSlaveDev->pCis1DataBufferPhy);
    DBG("CSA: 0x%08x\n",pstSlaveDev->pCsaDataBufferPhy);
    DBG("Recv: 0x%08x\n",pstSlaveDev->pRecvDataBuffPhy);

    return pstSlaveDev;

exit:
    slave_device_delete(pstSlaveDev);
    return BSP_NULL;
}

/*****************************************************************************
* �� �� ��  : OS_register_isr
*
* ��������  : ע���ж�
*
* �������  : intLvl:�жϺ�
*             pIsr  :�жϴ��������
*             pArg  :�жϺ�������
* �� �� ֵ  : ��
*
*****************************************************************************/
void OS_register_isr(BSP_U32 intLvl, void *pIsr, void *pArg)
{
	BSP_S32 rt =  SLAVE_OK;

	/*ע���ʹ���ж�*/
	rt = request_irq(intLvl,pIsr,IRQF_SHARED,"slave_isr",NULL);
	if(0!= rt)
	{
		printk("irq register failed\n");
		return rt;
	}
}

/*****************************************************************************
* �� �� ��  : OS_register_isr
*
* ��������  : �ͷ��豸�ṹ��
*
* �������  : pstSlaveDev:�豸�ṹ��ָ��
*
* �� �� ֵ  : ��
*
*****************************************************************************/
BSP_VOID slave_device_delete(SLAVE_DEV_S *pstSlaveDev)
{
    if(NULL == pstSlaveDev)
    {
        printk("SLAVE_DEV_S is NULL!\n");
        goto exit;
    }
    if(pstSlaveDev->pstSlaveStat)
    {
        SLAVE_memfree((BSP_VOID*)pstSlaveDev->pstSlaveStat);
    }

    if(pstSlaveDev->pCsaDataBuffer)
    {
        dma_free_coherent(NULL, CSA_BUF_SIZE+SLAVE_CACHE_ALIGN,
                                         pstSlaveDev->pCsaDataBuffer_NotAlign,
                                         pstSlaveDev->pCsaDataBufferPhy_NotAlign);
    }

    if(pstSlaveDev->pRecvDataBuff)
    {
        dma_free_coherent(NULL, DATA_BUF_SIZE + SLAVE_CACHE_ALIGN,
                                         pstSlaveDev->pRecvDataBuff_NotAlign,
                                         pstSlaveDev->pRecvDataBuffPhy_NotAlign);
    }

    if(pstSlaveDev->stReadCntl)
    {
        SLAVE_memfree((BSP_VOID*)pstSlaveDev->stReadCntl);
    }

    if(pstSlaveDev->pCis0DataBuffer)
    {
        BSP_U32 Cis0Len = sizeof(CIS0_Data)/sizeof(CIS0_Data[0]);
        dma_free_coherent(NULL, Cis0Len+SLAVE_CACHE_ALIGN,
                                         pstSlaveDev->pCis0DataBuffer_NotAlign,
                                         pstSlaveDev->pCis0DataBufferPhy_NotAlign);
    }

    if(pstSlaveDev->pCis1DataBuffer)
    {
        BSP_U32 Cis1Len = sizeof(CIS1_Data)/sizeof(CIS1_Data[0]);
        dma_free_coherent(NULL, Cis1Len+SLAVE_CACHE_ALIGN,
                                         pstSlaveDev->pCis1DataBuffer_NotAlign,
                                         pstSlaveDev->pCis1DataBufferPhy_NotAlign);
    }

	if(pstSlaveDev->stAdmaInfoHandle)
	{
	    SLAVE_ADMA_Deinit(pstSlaveDev->stAdmaInfoHandle);
	}

	if(pstSlaveDev->stAdmaRxHandle)
	{
	    SLAVE_ADMA_Deinit(pstSlaveDev->stAdmaRxHandle);
	}

	if(pstSlaveDev->stAdmaSendHandle)
	{
	    SLAVE_ADMA_Deinit(pstSlaveDev->stAdmaSendHandle);
	}

	if(pstSlaveDev)
	{
	    SLAVE_memfree((BSP_VOID*)pstSlaveDev);
	}
exit:
    return;
}


/*****************************************************************************
* �� �� ��  : SLAVE_RdClr_int
*
* ��������  : ���ж�״̬������ж�״̬
*
* �������  : ��
* �������  : pstIntMsg�ж�״̬�ṹ��
* �� �� ֵ  : ��
*
*****************************************************************************/
BSP_VOID SLAVE_RdClr_int(SLAVE_INTMSG_S *pstIntMsg)
{
    /* read interrupt status */
    pstIntMsg->global = SLAVE_IntStatus_Global()&GLOBAL_INT_MASK;
    pstIntMsg->mem = SLAVE_IntStatus_Mem()&MEM_INT_MASK;
    pstIntMsg->func0 = SLAVE_IntStatus_Fun0()&FUN0_INT_MASK;
    pstIntMsg->func1 = SLAVE_IntStatus_Fun1()&FUN1_INT_MASK;

    /* clear interrupt status */
    SLAVE_IntClr_Global(pstIntMsg->global);
    SLAVE_IntClr_Mem(pstIntMsg->mem);
    SLAVE_IntClr_Fun0(pstIntMsg->func0);
    SLAVE_IntClr_Fun1(pstIntMsg->func1);
}

/*****************************************************************************
* �� �� ��  : SLAVE_isr
*
* ��������  : �ϰ벿�ж�
*
* �������  : pstSlaveCtx:  SLAVE�豸����ṹ��
* �������  : ��
* �� �� ֵ  : ��
*
*****************************************************************************/

extern sdio_notify_change(int state);

irqreturn_t arasan_sdio_irq(int irq, void* dev)
{
    SLAVE_INTMSG_S stIntMsg = {0};
    SLAVE_CTX_S *pstSlaveCtx = &g_stSlaveCtx;

    /* disable global interrupt */
    SLAVE_IntMask_Global(0x0);

    SLAVE_RdClr_int(&stIntMsg);

    DBG("global int: 0x%x,f1 int: 0x%x,f0 int: 0x%x\n",(int)stIntMsg.global,
		(int)stIntMsg.func1,(int)stIntMsg.func0);

    pstSlaveCtx->pstSlaveDev->pstSlaveStat->isr_total++;

    pstSlaveCtx->IntMsg = stIntMsg;

    //schedule_work(&g_stSlaveCtx.dsr_work);
	tasklet_schedule(&g_stSlaveCtx.tasklet);
    return IRQ_HANDLED;
}


void arasan_sdio_tasklet(unsigned long slave)
{
	SLAVE_task_dsr();
}

/*****************************************************************************
* �� �� ��  : SLAVE_Init
*
* ��������  : SDIO SLAVE ��ʼ��
*
* �������  : ��
* �������  : ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 slave_init(void)
{
	BSP_S32 s32retVal = 0;
	BSP_S32 task_id = 0;
	int ret = 0;
	SLAVE_CTX_S *pstSlaveCtx;

	SLAVE_DEV_S *pstSlaveDev = BSP_NULL;

	struct regulator *sdcc_regulator;
	struct clk *sdcc_clk;

	sdcc_regulator = regulator_get(NULL, "sd_mtcmos-vcc");
	if (IS_ERR(sdcc_regulator)) {
		s32retVal = PTR_ERR(sdcc_regulator);
		goto exit;
	}
	
	sdcc_clk = clk_get(NULL, "sdcc_clk");
	if (IS_ERR(sdcc_clk)) {
		s32retVal = PTR_ERR(sdcc_clk);
		goto exit;
	}

	regulator_enable(sdcc_regulator);

	clk_enable(sdcc_clk);

	g_u32SlaveBase =ioremap(SD_DEV_REGBASE_ADR,SLAVE_REG_SIZE);
	SLAVE_fun1_switch(BSP_TRUE);
	/* check if module inited */
	if(g_stSlaveCtx.bSlaveInit)
	{
		printk("slave module has been inited!\n");
		return SLAVE_OK;
	}

	g_stSlaveCtx.bSlaveInit = BSP_TRUE;

	/* create slave device */
	pstSlaveDev = slave_device_create();
	if(!pstSlaveDev)
	{
		printk("slave obj create failed!\n");
		return SLAVE_ERR_MALLOC_FAILED;
	}
	pstSlaveDev->sdcc_clk = sdcc_clk;
	pstSlaveDev->sdcc_regulator = sdcc_regulator;
	g_stSlaveCtx.pstSlaveDev = pstSlaveDev;
	/*set enum mode*/
	g_stSlaveCtx.pstSlaveDev->SlaveCatalog = SLAVE_CFG_CATALOG;
	g_stSlaveCtx.pstSlaveDev->pFnEnumCfg = (FnEnumCfg)(arrEnumCfg[SLAVE_CFG_CATALOG]);
	/*init recv cntl */
	g_stSlaveCtx.pstSlaveDev->stReadCntl->pStart = pstSlaveDev->pRecvDataBuff;
	g_stSlaveCtx.pstSlaveDev->stReadCntl->pRead = pstSlaveDev->pRecvDataBuff;
	g_stSlaveCtx.pstSlaveDev->stReadCntl->pWrite = pstSlaveDev->pRecvDataBuff;
	//g_stSlaveCtx.pstSlaveDev->stReadCntl->TotalLen = 0;
	//g_stSlaveCtx.pstSlaveDev->stReadCntl->WrInLen = 0;
	g_stSlaveCtx.pstSlaveDev->stWritePrv.u32NodeInUse = 0;
#if 1
	g_stSlaveCtx.pstSlaveDev->pstSlaveStat->isr_reset_int = 0;
	g_stSlaveCtx.pstSlaveDev->pstSlaveStat->isr_start1_int = 0;
	g_stSlaveCtx.pstSlaveDev->pstSlaveStat->isr_end1_int = 0;
	g_stSlaveCtx.pstSlaveDev->pstSlaveStat->isr_over1_int= 0;

#endif
	if(BSP_OK != SlaveInitList(&g_stSlaveCtx, LIST_NODE_NUM))
	{
		printk("list init failed!\n");
		goto exit;
	}

#ifdef ADMA_DESC_MEM_CACHEABLE
	g_stSlaveCtx.pstSlaveDev->stWritePrv.bCached = BSP_TRUE;
#else
	g_stSlaveCtx.pstSlaveDev->stWritePrv.bCached = BSP_FALSE;
#endif

	/* adma init */
	s32retVal = SLAVE_Adma_Init(g_stSlaveCtx.pstSlaveDev->stAdmaInfoHandle, ADMA_DESC_FUN0_COUNT);
	if(SLAVE_OK != s32retVal)
	{
		printk("stAdmaInfoHandle init failed!\n");
		goto exit;
	}

	s32retVal = SLAVE_Adma_Init(g_stSlaveCtx.pstSlaveDev->stAdmaSendHandle, ADMA_DESC_LINE_COUNT);
	if(SLAVE_OK != s32retVal)
	{
		printk("stAdmaSendHandle init failed!\n");
		goto exit;
	}

	s32retVal = SLAVE_Adma_Init(g_stSlaveCtx.pstSlaveDev->stAdmaRxHandle, ADMA_DESC_LINE_COUNT);
	if(SLAVE_OK != s32retVal)
	{
		printk("stAdmaRxHandle init failed!\n");
		goto exit;
	}

	/* create semphore*/
	sema_init(&g_stSlaveCtx.pstSlaveDev->stWritePrv.stWrBlockSem, 0);

	// TBD to check the sem
	sema_init(&g_stSlaveCtx.pstSlaveDev->stReadPrv.stRdBlockSem, 0);
	// TBD to check the sem

	INIT_WORK(&g_stSlaveCtx.dsr_work, SLAVE_task_dsr);

	tasklet_init(&g_stSlaveCtx.tasklet, arasan_sdio_tasklet, (unsigned long)(&g_stSlaveCtx));

	spin_lock_init(&pstSlaveDev->stReadCntl->lock);

	if(!g_stSlaveCtx.pstSlaveDev->pFnEnumCfg)
	{
		s32retVal = SLAVE_ERR_INVAL_ENUMCFG;
		goto exit;
	}

	/* enum config init */
	DBG("pFnEnumCfg=%p\n",(BSP_S32)g_stSlaveCtx.pstSlaveDev->pFnEnumCfg);

	s32retVal = g_stSlaveCtx.pstSlaveDev->pFnEnumCfg();
	if(SLAVE_OK != s32retVal)
	{
		printk("device enum failed %p\n",g_stSlaveCtx.pstSlaveDev->pFnEnumCfg);
		goto exit;
	}

	/* disable int */
	SLAVE_int_disable();

	/* register isr */
	ret = request_irq(INT_VEC_SDIO_SLAVE, arasan_sdio_irq, IRQF_SHARED, "arasan-sdio", pstSlaveDev);
	if (ret) {
		DBG("request failed\n");
	}

	/* interrupt init */
	SLAVE_int_init();

	SLAVE_Fun_Ready();
	printk("sdio device ready\n");
   	return SLAVE_OK;
exit:
	SLAVE_deinit();
	return s32retVal;
}

/*****************************************************************************
* �� �� ��  : SLAVE_deinit
*
* ��������  : SDIO SLAVE ȥ��ʼ��
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
*
*****************************************************************************/
BSP_VOID SLAVE_deinit(void)
{
	if(!g_stSlaveCtx.bSlaveInit)
		return;

    SlaveDeinitList(&g_stSlaveCtx);
    /* free memory */
    slave_device_delete(g_stSlaveCtx.pstSlaveDev);

	/* Disable the SDIO function */
	SLAVE_fun1_switch(BSP_FALSE);

	g_stSlaveCtx.bSlaveInit = BSP_FALSE;
}

/*****************************************************************************
* �� �� ��  : SLAVE_task_dsr
*
* ��������  : �жϴ�������
*
* �������  : pstSlaveCtx:  SLAVE�豸����ṹ��
* �������  : ��
* �� �� ֵ  : ��
*
*****************************************************************************/
BSP_VOID SLAVE_task_dsr()
{
        BSP_S32 s32RetVal;
        BSP_U32 HouseKeepCnt = 0;
        SLAVE_INTMSG_S stIntSts = {0,0,0,0};
        SLAVE_CTX_S *pstSlaveCtx = &g_stSlaveCtx;

		do
		{
            stIntSts = pstSlaveCtx->IntMsg;

		    if(!(stIntSts.global & GLOBAL_INT_MASK))
		    {
		        HouseKeepCnt++;
		        if(HouseKeepCnt >= HSKEEP_CNT_MAX)
		        {
		            HouseKeepCnt = 0;
		            /* enable global interrupt */
		            SLAVE_IntMask_Global(GLOBAL_INT_MASK);
		            break;
		        }

		        continue;
		    }
		    HouseKeepCnt = 0;

            /*ʹ��ȫ���ж�*/
	        SLAVE_IntMask_Global(GLOBAL_INT_BITS_ALL);

    		if(stIntSts.global & GLOBAL_INT_FROM_FUN0)
    		{
    			handle_fun0_int(pstSlaveCtx,&stIntSts);
    		}
    		if(stIntSts.global & GLOBAL_INT_FROM_MEM)
    		{
                handle_mem_int(pstSlaveCtx,&stIntSts);
    		}
		    if(stIntSts.global & GLOBAL_INT_FROM_FN1)
		    {
		        handle_fun1_int(pstSlaveCtx,&stIntSts);
		    }
		    stIntSts.func0  = 0;
		    stIntSts.func1  = 0;
		    stIntSts.global = 0;
		    stIntSts.mem    = 0;
            /*ʹ��ȫ���ж�*/
		    SLAVE_IntMask_Global(GLOBAL_INT_BITS_ALL);
		}
	while(0);
}

/*****************************************************************************
* �� �� ��  : handle_fun1_int
*
* ��������  : Function 1�жϴ�����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*             pstIntMsg:   �ж�״̬��Ϣ
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_VOID handle_fun1_int(SLAVE_CTX_S *pstSlaveCtx,SLAVE_INTMSG_S *pstIntMsg)
{
    AHBFun1Int_REG Fun1IntStReg;

	/*read and clear interrupt status*/
    Fun1IntStReg.u32Reg = pstIntMsg->func1;
    SLAVE_IntClr_Fun1(Fun1IntStReg.u32Reg);

    DBG("INT-1: Reg=0x%x\n", Fun1IntStReg.u32Reg);

    if(Fun1IntStReg.Fn1Bits.fn1_sdio_rd_start)
    {
        pstSlaveCtx->pstSlaveDev->pstSlaveStat->isr_start1_int++;
        (void)FUN1_DataReadTrans(pstSlaveCtx);
    }
    if(Fun1IntStReg.Fn1Bits.adma_end_int)
    {
        pstSlaveCtx->pstSlaveDev->pstSlaveStat->isr_end1_int++;

        (void)FUN1_EndDataTrans(pstSlaveCtx);
    }
    if(Fun1IntStReg.Fn1Bits.fn1_rd_over)
    {
        pstSlaveCtx->pstSlaveDev->pstSlaveStat->isr_over1_int++;

        (void)FUN1_DataReadOver(pstSlaveCtx);
    }
    if(Fun1IntStReg.Fn1Bits.fn1_sdio_wr_start)
    {
        pstSlaveCtx->pstSlaveDev->pstSlaveStat->isr_start1_int++;

        (void)FUN1_DataWriteTrans(pstSlaveCtx);
    }
    if(Fun1IntStReg.Fn1Bits.fn_wr_over)
    {
        pstSlaveCtx->pstSlaveDev->pstSlaveStat->isr_over1_int++;
        (void)FUN1_DataWriteOver(pstSlaveCtx);
    }
    if(Fun1IntStReg.Fn1Bits.fn1_rd_error)
    {
        SLAVE_Abort();
    }
    if(Fun1IntStReg.Fn1Bits.resume)
	{
        SLAVE_Resume();
	}
    if(Fun1IntStReg.Fn1Bits.fn1_suspend)
    {
        SLAVE_Susp();
    }
    if(Fun1IntStReg.Fn1Bits.sd_host_fn1_msg_rdy)
    {
        (void)FUN1_MsgIntProcess(pstSlaveCtx);
    }
    if(Fun1IntStReg.Fn1Bits.fun1_en)
    {
        SLAVE_IntClr_Fun1(FUN1_INT_FUN1_EN);
    }
    if(Fun1IntStReg.Fn1Bits.adma_err)
    {
        pstSlaveCtx->pstSlaveDev->pstSlaveStat->dma_err_int++;
        SLAVE_IntClr_Fun1(FUN1_INT_ADMA_ERR);
    }

    /*clear interrupt staus*/
    Fun1IntStReg.u32Reg = 0;

}

/*****************************************************************************
* �� �� ��  : handle_fun0_int
*
* ��������  : Function 0�жϴ�����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*             pstIntMsg:   �ж�״̬��Ϣ
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_VOID handle_fun0_int(SLAVE_CTX_S *pstSlaveCtx,SLAVE_INTMSG_S *pstIntMsg)
{
    AHBFun0Int_REG Fun0IntStReg;
    /*���ж�״̬*/
    Fun0IntStReg.u32Reg = pstIntMsg->func0;
    SLAVE_IntClr_Fun0(Fun0IntStReg.u32Reg);

    DBG("INT-0: Reg=%x\n", Fun0IntStReg.u32Reg);

    if(Fun0IntStReg.Fn0Bits.fn0_rd_start)
    {
        (void)FUN0_InfoReadTrans(pstSlaveCtx);
    }
    if(Fun0IntStReg.Fn0Bits.fn0_adma_end_int)
    {
        (void)FUN0_EndIntTrans(pstSlaveCtx);
    }
    if(Fun0IntStReg.Fn0Bits.fn0_rd_trn_over)
    {
        (void)FUN0_InfoReadOver(pstSlaveCtx);
    }
    if(Fun0IntStReg.Fn0Bits.fn0_wr_start)
    {
        (void)FUN0_CsaWriteTrans(pstSlaveCtx);
    }
	if(Fun0IntStReg.Fn0Bits.fn0_wr_trn_over)
	{
        (void)FUN0_CsaWriteOver(pstSlaveCtx);
	}
	if(Fun0IntStReg.Fn0Bits.fn0_rd_trn_err)
	{
        /*error����*/
        SLAVE_IntClr_Fun0(FUN0_INT_ADMA_ERR);
        pstSlaveCtx->pstSlaveDev->pstSlaveStat->dma_err_int++;
	}
    if(Fun0IntStReg.Fn0Bits.soft_rst)
    {
        printk("slave soft reset");
        //kthread_run(SLAVE_SoftRst,NULL,"tSlaveSoftRstTask");
        SLAVE_SoftRst();
    }
    if(Fun0IntStReg.Fn0Bits.volt_sw_cmd)
    {
        SLAVE_VolSwt();
    }

    Fun0IntStReg.u32Reg = 0;
}

/*****************************************************************************
* �� �� ��  : SLAVE_ReadReg
*
* ��������  : ��blocksize��argument�Ĵ�����������CMD53������Ϣ
*
* �������  : ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
SLAVE_RegInfo_S SLAVE_ReadReg(void)
{
    SLAVE_RegInfo_S stRegInfo;

	/*��block size and argument register*/
    stRegInfo.u32Arg = SLAVE_GetArgument();
    stRegInfo.u32BlockSize = SLAVE_GetBlockSize();

    /*����argument register*/
    stRegInfo.u32blockCnt = SLAVE_GetCount(stRegInfo.u32Arg);
    stRegInfo.b_BlockMode = SLAVE_GetBlkMode(stRegInfo.u32Arg);
    stRegInfo.b_OpMode = SLAVE_GetOpMode(stRegInfo.u32Arg);

    /*direction, 1: host ->slave, 0: slave -> host*/
    stRegInfo.bTranDir = SLAVE_GetRwDir(stRegInfo.u32Arg );
    stRegInfo.RegAddr = SLAVE_GetRegAddr(stRegInfo.u32Arg);

    /*�ֽڷ�ʽ�Ϳ鷽ʽ*/
    stRegInfo.TotalLen = (stRegInfo.b_BlockMode)?stRegInfo.u32BlockSize * stRegInfo.u32blockCnt:stRegInfo.u32blockCnt;

	if (!stRegInfo.b_BlockMode && !stRegInfo.u32blockCnt) {
		stRegInfo.TotalLen = 512;
	}
	DBG("%s: block size(%d) block count(%d) mode(%d)\n",
		stRegInfo.bTranDir ? "HOST-DEV" : "DEV-HOST", stRegInfo.u32BlockSize,
		stRegInfo.u32blockCnt,	stRegInfo.b_BlockMode);

    return stRegInfo;
}

/*****************************************************************************
* �� �� ��  : FUN1_DataReadTrans
*
* ��������  : HOST��SLAVE ���ݶ˿ڵ��жϴ�����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 FUN1_DataReadTrans(SLAVE_CTX_S *pstSlaveCtx)
{
    SLAVE_RegInfo_S stArgRegInfo;

    SLAVE_IntClr_Fun1(FUN0_INT_RD_START);

    stArgRegInfo = SLAVE_ReadReg();

    DBG("blksize:%#x,u32Arg:%#x\n",(int)stArgRegInfo.u32BlockSize,(int)stArgRegInfo.u32Arg);
    sdio_adma_init_desc_base(pstSlaveCtx->pstSlaveDev->stAdmaSendHandle);
    pstSlaveCtx->pstSlaveDev->stWritePrv.mount -= stArgRegInfo.TotalLen;
    pstSlaveCtx->pstSlaveDev->pstSlaveStat->statofCur = DATA_SEND;
    return SLAVE_OK;
}

static unsigned int slave_buff_is_covered(SLAVE_RX_SUB_S *stReadCntl)
{
	unsigned int ret;
	BSP_U32 pstart;
	BSP_U32 pwrite;
	BSP_U32 pread;
	/*transfer over will acess*/

	ret = 0;
	pstart =  (BSP_U32)stReadCntl->pStart;
	pwrite = (BSP_U32)stReadCntl->pWrite;
	pread = (BSP_U32)stReadCntl->pRead;
 	if (pstart + (stReadCntl->pRead - stReadCntl->pWrite
		+  DATA_BUF_SIZE)/DATA_BUF_SIZE > pread) {
		ret = 1;
	}

	return ret;
}
/*****************************************************************************
* �� �� ��  : FUN1_DataWriteTrans
*
* ��������  : HOSTдSLAVE ���ݶ˿ڵ��жϴ�����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 FUN1_DataWriteTrans(SLAVE_CTX_S *pstSlaveCtx)
{
    BSP_U32 desCnt;
    BSP_U32 len;
    BSP_U32 buffLen = 0;
    SLAVE_RegInfo_S stArgRegInfo;
    BSP_U8 *pu8M2SBuff = BSP_NULL, *pu8M2SBuffPhy = BSP_NULL;
    BSP_U32 noalignLen = 0;     /*�ǿ���볤��*/
	SLAVE_RX_SUB_S *stReadCntl;
	stReadCntl = pstSlaveCtx->pstSlaveDev->stReadCntl;

	unsigned int split;
    stArgRegInfo = SLAVE_ReadReg();
    if(stArgRegInfo.RegAddr == FUN1_DATA_PORT_VALUE)
    {
        spin_lock(&stReadCntl->lock);

        pu8M2SBuff = pstSlaveCtx->pstSlaveDev->stReadCntl->pWrite;
	spin_unlock(&stReadCntl->lock);
        pu8M2SBuffPhy = pstSlaveCtx->pstSlaveDev->pRecvDataBuffPhy +
                                (pu8M2SBuff - pstSlaveCtx->pstSlaveDev->pRecvDataBuff);

	DBG("pu8M2SBuff: 0x%x\n", pu8M2SBuff);
	DBG("pRecvDataBuffPhy: 0x%x\n", pstSlaveCtx->pstSlaveDev->pRecvDataBuffPhy);
	DBG("pRecvDataBuff: 0x%x\n", pstSlaveCtx->pstSlaveDev->pRecvDataBuff);
	DBG("pstart: 0x%x\n", pstSlaveCtx->pstSlaveDev->stReadCntl->pStart);
	DBG("pu8M2SBuffPhy: 0x%x\n", pu8M2SBuffPhy);


    }
    else
    {
        ERR("error condition\n");
        return SLAVE_ERR_INVAL_CONDITION;
    }
#if 0
    /* read idle buffer size */
    SLAVE_GET_IdleSize(pstSlaveCtx,&buffLen);
	if (stArgRegInfo.TotalLen >= buffLen) {
	        ERR("buffer will be full, data may be lost\n");
	}

    if(SLAVE_Buff_IsFull(pstSlaveCtx))
    {
        ERR("buffer is full, data may be lost\n");
        /*���buffer����HOST�˼�����SLAVE��������ԭ����buffer����, readָ��Ҳ�ص�buffer��ʼλ��*/
        pstSlaveCtx->pstSlaveDev->stReadCntl->pWrite = pstSlaveCtx->pstSlaveDev->stReadCntl->pStart;
        pstSlaveCtx->pstSlaveDev->stReadCntl->pRead = pstSlaveCtx->pstSlaveDev->stReadCntl->pStart;
        ERR("!!!!!!!!!!!buff full!!!!!!!!!,pWrite:0x%x\n",pstSlaveCtx->pstSlaveDev->stReadCntl->pWrite);
    }


    /*�����������������bufferʣ��ռ��С��ֻ����ʣ��buffer��С������*/
    if(stArgRegInfo.TotalLen < buffLen)
    {
        len = stArgRegInfo.TotalLen;
    }
    else
    {
        if(stArgRegInfo.b_BlockMode)
        {
            /*block mode,idle size�Ƿ�Ϊ�������*/
            noalignLen = (buffLen % (stArgRegInfo.u32BlockSize));
			DBG("buffLen:%#x,noalignLen:%#x\n",(int)buffLen,(int)noalignLen);
            /*ʣ������ȡ������������䣬�����������*/
            len = buffLen - noalignLen;
        }
        else
        {
            /*�ֽڷ�ʽ���ÿ����Ƿ��ǿ��������*/
            len = buffLen;
        }
    }

    DBG("blksize:%#x,u32Arg:%#x\n",(int)stArgRegInfo.u32BlockSize,(int)stArgRegInfo.u32Arg);
len = stArgRegInfo.TotalLen;

desCnt = ADMA_GET_NODE_COUNT(len);


    /*�����32 �ֽڶ��룬����һ���ڵ㣬���͸���buffer����*/

        spin_lock(&stReadCntl->lock);
	if((!ADMA_CHECK_ALIGN((BSP_U32)pstSlaveCtx->pstSlaveDev->stReadCntl->pWrite))&&(len > SLAVE_CACHE_ALIGN))
    {
        desCnt = desCnt + 1;
    }
            spin_unlock(&stReadCntl->lock);

	DBG("pWrite:0x%x,TotalLen:0x%x,pRead:0x%x\n",(int)pstSlaveCtx->pstSlaveDev->stReadCntl->pWrite,
                                    (int)pstSlaveCtx->pstSlaveDev->stReadCntl->TotalLen, (int)pstSlaveCtx->pstSlaveDev->stReadCntl->pRead);
    DBG("bufflen: 0x%x,desCnt:0x%x\n",len,desCnt);
    /*config desc*/

#endif

	if (SLAVE_Buff_IsFull(pstSlaveCtx)) {

	        ERR("buffer  be full, data may be lost\n");
	}
	DBG("pWrite:0x%x,TotalLen:0x%x,pRead:0x%x\n",
		(int)pstSlaveCtx->pstSlaveDev->stReadCntl->pWrite,
		(int)pstSlaveCtx->pstSlaveDev->stReadCntl->TotalLen,
		(int)pstSlaveCtx->pstSlaveDev->stReadCntl->pRead);
	len = stArgRegInfo.TotalLen;

	desCnt = ADMA_GET_NODE_COUNT(len);

	if (!ADMA_CHECK_ALIGN((unsigned int)stReadCntl->pWrite)) {
		DBG("use assit buffer: desCnt:0x%x\n", desCnt);
		split =0;
	} else if (DATA_BUF_SIZE - ((unsigned int)(stReadCntl->pWrite) - (unsigned int)stReadCntl->pStart) >= len) {
		DBG("use rx buffer: desCnt:0x%x\n", desCnt);
		split = 0;
	} else if (DATA_BUF_SIZE - (unsigned int)(stReadCntl->pWrite) + (unsigned int)stReadCntl->pStart == 0) {
		split = 0;
		pu8M2SBuff = stReadCntl->pStart;
		pu8M2SBuffPhy = stReadCntl->pStartPhy;
	} else {
		desCnt++;
		DBG("use rx buffer: but LOOP BUFFER: desCnt:0x%x\n", desCnt);
		if (slave_buff_is_covered(stReadCntl)) {
			DBG("use rx buffer: data is flashed\n");
		}
		split = 1;
	}


	pstSlaveCtx->pstSlaveDev->stAdmaRxHandle->DescCount = desCnt;
    ADMA_Desc_Queue_Config(pstSlaveCtx->pstSlaveDev->stAdmaRxHandle,
		stReadCntl, (BSP_U32)pu8M2SBuff,(BSP_U32)pu8M2SBuffPhy,
		len, desCnt, split, stArgRegInfo.bTranDir);
    sdio_adma_init_desc_base(pstSlaveCtx->pstSlaveDev->stAdmaRxHandle);

    pstSlaveCtx->pstSlaveDev->pstSlaveStat->statofCur = DATA_READ;
    pstSlaveCtx->pstSlaveDev->stReadCntl->WrInLen = len;

    return SLAVE_OK;
}

/*****************************************************************************
* �� �� ��  : FUN1_EndDataTrans
*
* ��������  : end�жϴ�����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 FUN1_EndDataTrans(SLAVE_CTX_S *pstSlaveCtx)
{
    SLAVE_RegInfo_S stRegInfo;
    SLAVE_IntClr_Fun1(FUN1_INT_ADMA_END);

    stRegInfo = SLAVE_ReadReg();
    /*0:slave->host 1:host->slave*/
	DBG("end data trans\n");
    	DBG("%s\n", stRegInfo.bTranDir ? "HOST-DEV" : "DEV-HOST");
    if(stRegInfo.bTranDir)
    {
   #if 0
    	if (pstSlaveCtx->pstSlaveDev->stAdmaRxHandle->NextDesc) {
		BSP_REG_WRITE(g_u32SlaveBase,
			ADMA_SYS_ADDR,pstSlaveCtx->pstSlaveDev->stAdmaRxHandle->NextDesc);
    	} else {

     	   sdio_adma_init_desc_base(pstSlaveCtx->pstSlaveDev->stAdmaRxHandle);
    	}
	#else
     	   sdio_adma_init_desc_base(pstSlaveCtx->pstSlaveDev->stAdmaRxHandle);

	#endif
    }
    else
    {

        sdio_adma_init_desc_base(pstSlaveCtx->pstSlaveDev->stAdmaSendHandle);
    }
    return SLAVE_OK;
}

/*****************************************************************************
* �� �� ��  : FUN1_DataWriteOver
*
* ��������  : HOST��SLAVE ���ݶ˿�д��ɴ���
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 FUN1_DataWriteOver(SLAVE_CTX_S *pstSlaveCtx)
{
    BSP_U32 tmp_total = 0;
    BSP_U8 *tmp_pwrite = BSP_NULL;
    BSP_BOOL bflag = BSP_FALSE;
    SLAVE_RX_SUB_S *pReadCntl = pstSlaveCtx->pstSlaveDev->stReadCntl;
    BSP_U8  *end =  (BSP_U8*)(pReadCntl->pStart + DATA_BUF_SIZE);
    BSP_U32 len = pReadCntl->WrInLen, alignlen=0;
	unsigned int remain;

    SLAVE_IntClr_Fun1(FUN1_INT_WR_OVER);

	static unsigned int times;
	spin_lock(&pReadCntl->lock);
    /*�����봦��*/

		remain = (unsigned int)end - (unsigned int)pReadCntl->pWrite;
		if (remain < len) {
			if(!ADMA_CHECK_ALIGN((BSP_U32)pReadCntl->pWrite)) {

				DBG("memcpy start\n");
				if (remain) {
					memcpy(pReadCntl->pWrite,
						pstSlaveCtx->pstSlaveDev->stAdmaRxHandle->assist_buf, remain);
				}
				memcpy(pReadCntl->pStart,
					pstSlaveCtx->pstSlaveDev->stAdmaRxHandle->assist_buf + remain,
					len - remain);
				DBG("memcpy end\n");

			}
			pReadCntl->pWrite = pReadCntl->pStart + len - remain;
		} else {
			if(!ADMA_CHECK_ALIGN((BSP_U32)pReadCntl->pWrite)) {

				DBG("memcpy start\n");

				memcpy(pReadCntl->pWrite,
					pstSlaveCtx->pstSlaveDev->stAdmaRxHandle->assist_buf, len);
				DBG("memcpy end\n");
			}
			pReadCntl->pWrite += len;
		}
		DBG("write data is not align\n");

    pReadCntl->empty = 0;
    pstSlaveCtx->pstSlaveDev->pstSlaveStat->statofCur = TRANS_IDLE;
    pReadCntl->TotalLen = len;
	DBG("lpWrite:%#x,lTotalLen:%#x,lpRead:%#x\n", (int)pReadCntl->pWrite,
                            (int)pReadCntl->TotalLen, (int)pReadCntl->pRead);

	spin_unlock(&pReadCntl->lock);

    if(pstSlaveCtx->pstSlaveDev->stReadPrv.readDoneCB)
    {
      	DBG("callback func\n");

        /*ִ�лص����ϲ�ʹ��Ҫ����ioctl��ȡbuffer��Ϣ�����黹buffer*/
        pstSlaveCtx->pstSlaveDev->stReadPrv.readDoneCB();
        pstSlaveCtx->pstSlaveDev->pstSlaveStat->readCB_cnt++;
    }
    else
    {
        /*������*/
        up(&pstSlaveCtx->pstSlaveDev->stReadPrv.stRdBlockSem);
	    	DBG("no callback func, up read semaphore (%d) times\n", times++);

    }

    /*����д�볤�ȣ�����*/
    pReadCntl->WrInLen = 0;

    if(SLAVE_Buff_IsFull(pstSlaveCtx))
    {
        DBG("buffer is full\n");
        pstSlaveCtx->pstSlaveDev->pstSlaveStat->statofCur = RECV_BUFF_FULL;
    }
    return SLAVE_OK;
}

/*****************************************************************************
* �� �� ��  : FUN1_DataReadOver
*
* ��������  : host����������жϴ�����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 FUN1_DataReadOver(SLAVE_CTX_S *pstSlaveCtx)
{
    BSP_U32 len = 0;
    BSP_U32 desCnt = 0;
    BSP_BOOL bTranDir = 0;
    SLAVE_NODE_INFO *Get_Node = BSP_NULL;
    SLAVE_NODE_INFO *Cur_Node = BSP_NULL;
    struct list_head *pHeader = &(pstSlaveCtx->pstSlaveDev->stWritePrv.use_list);
    struct list_head *pNode ;
	static unsigned long times = 0;

    SLAVE_IntClr_Fun1(FUN1_INT_RD_OVER);

    pstSlaveCtx->pstSlaveDev->pstSlaveStat->statofCur = TRANS_IDLE;

    if(pstSlaveCtx->pstSlaveDev->stWritePrv.writeDoneCB)
    {
        printk(KERN_DEBUG "writeDoneCB is called\n");

        /*��use_list��ȡ��������Ľڵ�*/

        Get_Node = GetOffNodeFromUseList(pstSlaveCtx);
        /*���ýڵ����free_list��*/
        AddNodeToFreeList(pstSlaveCtx,Get_Node);

        if(0 != GetListNodeNum(pstSlaveCtx))
        {
            pNode = pHeader->next;
            /*��use������ȡ����������һ���ڵ�*/
            Cur_Node = list_entry(pNode, SLAVE_NODE_INFO, stList);

            pstSlaveCtx->pstSlaveDev->stWritePrv.pCurNode = Cur_Node;

            len = Cur_Node->stItem.dlen;
            desCnt = ADMA_GET_NODE_COUNT(len);

            /*���ú�������*/
            ADMA_Desc_Queue_Config(pstSlaveCtx->pstSlaveDev->stAdmaSendHandle, NULL,(BSP_U32)Cur_Node->stItem.addr,
                (BSP_U32)Cur_Node->stItem.addrPhy, len, desCnt,0, bTranDir);

            /*����д������Ϣ*/
            (void)hal_sdio_S2MRdySend(len);
        }
        else
        {
            //BSP_TRACE(BSP_LOG_LEVEL_INFO,BSP_MODU_SLAVE,"List is empty\n");
            printk(KERN_DEBUG "List is empty\n");

            /*���ûص���֪ͨhost����д�������Ѿ�����*/
            pstSlaveCtx->pstSlaveDev->stWritePrv.writeDoneCB();
            pstSlaveCtx->pstSlaveDev->pstSlaveStat->writeCB_cnt++;
            pstSlaveCtx->pstSlaveDev->stWritePrv.pCurNode = NULL;
        }

    }
    else
    {
        DBG("no register writeDoneCB\n");
        /*�ͷ��ź��������������Ѿ����͸�host*/
		if (!pstSlaveCtx->pstSlaveDev->stWritePrv.mount) {

		}
       		 up(&pstSlaveCtx->pstSlaveDev->stWritePrv.stWrBlockSem);
		        DBG("read over up write semaphore (%d)times\n", times++);

    }
    return SLAVE_OK;
}

/*****************************************************************************
* �� �� ��  : FUN1_MsgIntProcess
*
* ��������  : HOST��SLAVE ������Ϣ�Ĵ�����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 FUN1_MsgIntProcess(SLAVE_CTX_S *pstSlaveCtx)
{
    BSP_U32 u32Msg;
    BSP_U32 len = 0;
	unsigned int flags;
	SLAVE_RX_SUB_S *stReadCntl;
	stReadCntl = pstSlaveCtx->pstSlaveDev->stReadCntl;

    SLAVE_IntClr_Fun1(FUN1_INT_HOSTMSG_RDY);

    u32Msg = SLAVE_MsgRead();
    pstSlaveCtx->pstSlaveDev->msgCurrent = u32Msg;

    printk("received message:0x%x\n");

    switch(u32Msg)
    {
    /*��ȡ����buffer��ʣ���С*/
    case MSG_BUFF_SIZE_GET:

	spin_lock(&stReadCntl->lock);

        len =(BSP_U32)(pstSlaveCtx->pstSlaveDev->stReadCntl->pWrite - pstSlaveCtx->pstSlaveDev->stReadCntl->pStart);

	spin_unlock(&stReadCntl->lock);

	(void)SLAVE_MsgWrite(DATA_BUF_SIZE - len);
        break;
    //case MSG_READ_REQUEST:
    case MSG_STATUS_GET:
        SLAVE_MsgWrite(pstSlaveCtx->pstSlaveDev->pstSlaveStat->statofCur);
        break;

    case MSG_ERROR_CODE_GET:
        SLAVE_MsgWrite(pstSlaveCtx->pstSlaveDev->pstSlaveStat->err_code);
        break;

    case MSG_MODE_SWITCH_UHS:
        SLAVE_UHS_Support(TRUE);
        break;

    case MSG_CSA_SUPPORT:
        SLAVE_CSA_Support(TRUE);
        break;
    case RECV_BUFF_RESET:
        SLAVE_RECV_BuffRst(pstSlaveCtx->pstSlaveDev->stReadCntl);
    default:
        break;
    }
    return SLAVE_OK;

}

/*****************************************************************************
* �� �� ��  : FUN0_InfoReadTrans
*
* ��������  : HOST��SLAVE CIS��CSA���жϴ�����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 FUN0_InfoReadTrans(SLAVE_CTX_S *pstSlaveCtx)
{
    BSP_U32 desCnt;
    BSP_U32 len;
    SLAVE_RegInfo_S stArgRegInfo;
    BSP_U8 *pu8S2MBuff = BSP_NULL;
    BSP_U8 *pu8S2MBuffPhy = BSP_NULL;
    BSP_U32 u32RegAddr = 0;
    BSP_U32 u32pCSAReg = 0;

    stArgRegInfo = SLAVE_ReadReg();
    u32RegAddr = stArgRegInfo.RegAddr;

    len = stArgRegInfo.TotalLen;
    desCnt = ADMA_GET_NODE_COUNT(len);

    /*cis0��cis1��csa address*/
    if((u32RegAddr >= CIS0_ADDR_VALUE) && (u32RegAddr < CIS1_ADDR_VALUE))
    {
        pu8S2MBuff = (BSP_U8 *)(pstSlaveCtx->pstSlaveDev->pCis0DataBuffer + u32RegAddr - CIS0_ADDR_VALUE);
        pu8S2MBuffPhy = (BSP_U8 *)(pstSlaveCtx->pstSlaveDev->pCis0DataBufferPhy + u32RegAddr - CIS0_ADDR_VALUE);
    }
    else if((u32RegAddr >= CIS1_ADDR_VALUE) && (u32RegAddr <= 0x2fff))
    {
        pu8S2MBuff = (BSP_U8 *)(pstSlaveCtx->pstSlaveDev->pCis1DataBuffer + u32RegAddr - CIS1_ADDR_VALUE);
        pu8S2MBuffPhy = (BSP_U8 *)(pstSlaveCtx->pstSlaveDev->pCis1DataBufferPhy + u32RegAddr - CIS1_ADDR_VALUE);
    }
    else if(u32RegAddr == CSA_ADDR_VALUE)
    {
        u32pCSAReg = SLAVE_GetCsaPointer();
        pu8S2MBuff =(BSP_U8 *)(pstSlaveCtx->pstSlaveDev->pCsaDataBuffer + u32pCSAReg);
        pu8S2MBuffPhy =(BSP_U8 *)(pstSlaveCtx->pstSlaveDev->pCsaDataBufferPhy + u32pCSAReg);
        pstSlaveCtx->pstSlaveDev->pCSALast = u32pCSAReg;
    }
    else
    {
        //BSP_TRACE(BSP_LOG_LEVEL_ERROR, BSP_MODU_SLAVE, "error condition\n");
        printk("error condition\n");
        pstSlaveCtx->pstSlaveDev->pstSlaveStat->err_code = SLAVE_ERR_INVAL_CONDITION;
        return SLAVE_ERR_INVAL_CONDITION;
    }
    /*�������������һ���ڵ�*/
    if((!ADMA_CHECK_ALIGN((BSP_U32)pu8S2MBuff))&&(len > SLAVE_CACHE_ALIGN))
    {
        desCnt = desCnt + 1;
    }

    ADMA_Desc_Queue_Config(pstSlaveCtx->pstSlaveDev->stAdmaInfoHandle, NULL,(BSP_U32)pu8S2MBuff, (BSP_U32)pu8S2MBuffPhy, len, desCnt, 0,stArgRegInfo.bTranDir);
    sdio_adma_init_desc_base(pstSlaveCtx->pstSlaveDev->stAdmaInfoHandle);
    return SLAVE_OK;

}

/*****************************************************************************
* �� �� ��  : FUN0_InfoReadTrans
*
* ��������  : HOSTдSLAVE CSA�����жϴ�����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 FUN0_CsaWriteTrans(SLAVE_CTX_S *pstSlaveCtx)
{
    BSP_U32 desCnt;
    BSP_U32 len;
    SLAVE_RegInfo_S stArgRegInfo;
    BSP_U8 *pu8M2SBuff = BSP_NULL;
    BSP_U8 *pu8M2SBuffPhy = BSP_NULL;
    BSP_U32 u32RegAddr = 0;
    BSP_U32 u32pCSAReg = 0;

    stArgRegInfo = SLAVE_ReadReg();
    u32RegAddr = stArgRegInfo.RegAddr;

    len = stArgRegInfo.TotalLen;

 	printk("blksize:%#x,u32Arg:%#x,len:%#x\n",(int)stArgRegInfo.u32BlockSize,(int)stArgRegInfo.u32Arg,(int)len);

    desCnt = ADMA_GET_NODE_COUNT(len);

    if(u32RegAddr == CSA_ADDR_VALUE)
    {
        u32pCSAReg = SLAVE_GetCsaPointer();
        pu8M2SBuff =(BSP_U8*)(pstSlaveCtx->pstSlaveDev->pCsaDataBuffer + u32pCSAReg);
        pu8M2SBuffPhy = (BSP_U8*)(pstSlaveCtx->pstSlaveDev->pCsaDataBufferPhy + u32pCSAReg);
        pstSlaveCtx->pstSlaveDev->pCSALast = u32pCSAReg;
    }
    else
    {
        printk("error condition\n");
        pstSlaveCtx->pstSlaveDev->pstSlaveStat->err_code = SLAVE_ERR_INVAL_CONDITION;
        return SLAVE_ERR_INVAL_CONDITION;
    }

    if((!ADMA_CHECK_ALIGN((BSP_U32)pu8M2SBuff))&&(len>SLAVE_CACHE_ALIGN))
    {
        desCnt = desCnt + 1;
    }

    ADMA_Desc_Queue_Config(pstSlaveCtx->pstSlaveDev->stAdmaInfoHandle, NULL,(BSP_U32)pu8M2SBuff, (BSP_U32)pu8M2SBuffPhy, len, desCnt, 0,stArgRegInfo.bTranDir);
    sdio_adma_init_desc_base(pstSlaveCtx->pstSlaveDev->stAdmaInfoHandle);
    return SLAVE_OK;

}

/*****************************************************************************
* �� �� ��  : FUN0_CsaWriteOver
*
* ��������  : CSAд����жϴ�����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 FUN0_CsaWriteOver(SLAVE_CTX_S *pstSlaveCtx)
{
    BSP_U32 u32pCSAReg;
    BSP_U32 u32csaBuff;

    u32csaBuff = (BSP_U32)pstSlaveCtx->pstSlaveDev->pCsaDataBuffer + pstSlaveCtx->pstSlaveDev->pCSALast;
    u32pCSAReg = SLAVE_GetCsaPointer();

    if(!ADMA_CHECK_ALIGN(u32csaBuff))
    {
        /*������buffer�е������Ƶ�CSA������*/
        ADMA_GET_ASSIST_DATA(pstSlaveCtx->pstSlaveDev->stAdmaInfoHandle,u32csaBuff,
                                    ADMA_GET_NOALIGN_BYTES(u32csaBuff));
    }
    /*�����ϴΰ���ʱ��CSAָ��*/
    pstSlaveCtx->pstSlaveDev->pCSALast = u32pCSAReg;

    return SLAVE_OK;
}

/*****************************************************************************
* �� �� ��  : FUN0_CsaWriteOver
*
* ��������  : CIS CSA������жϴ�����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 FUN0_InfoReadOver(SLAVE_CTX_S *pstSlaveCtx)
{
    BSP_U32 u32pCSAReg;
    u32pCSAReg = SLAVE_GetCsaPointer();
    pstSlaveCtx->pstSlaveDev->pCSALast = u32pCSAReg;
    return SLAVE_OK;
}

/*****************************************************************************
* �� �� ��  : FUN0_CsaWriteOver
*
* ��������  : Fun0 end�жϴ���
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*
*****************************************************************************/
BSP_S32 FUN0_EndIntTrans(SLAVE_CTX_S *pstSlaveCtx)
{
    SLAVE_IntClr_Fun1(FUN0_INT_ADMA_END);
    /*��������system address��ַ��ԭ����������*/
    sdio_adma_init_desc_base(pstSlaveCtx->pstSlaveDev->stAdmaInfoHandle);

    /*��������������������Ŀǰû��������Ҫ*/
    return SLAVE_OK;
}

/*****************************************************************************
* �� �� ��  : handle_mem_int
*
* ��������  : mem�жϴ���������ʹ��memģʽ
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*             pstIntMsg:   �ж�״̬��Ϣ
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_VOID handle_mem_int(SLAVE_CTX_S *pstSlaveCtx,SLAVE_INTMSG_S *pstIntMsg)
{
    BSP_U32 u32Temp;
    printk("%s mem int\n",SLAVE_CFG_INT_TASK_NAME);

    u32Temp = pstIntMsg->func0;
    SLAVE_IntClr_Mem(u32Temp);
}/*lint !e715*/

/*****************************************************************************
* �� �� ��  : SLAVE_Buff_IsEmpty
*
* ��������  : �жϽ���buffer�Ƿ����
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_BOOL SLAVE_Buff_IsEmpty(SLAVE_CTX_S *pstSlaveCtx)
{
	SLAVE_RX_SUB_S *stReadCntl = pstSlaveCtx->pstSlaveDev->stReadCntl;
#if 0
	BSP_U32 pread;
	BSP_U32 pwrite;
	unsigned long flags;
	/*transfer over will acess*/
	spin_lock_irqsave(&stReadCntl->lock, flags);

	pread =  (BSP_U32)stReadCntl->pRead;
	pwrite = (BSP_U32)stReadCntl->pWrite;

	spin_unlock_irqrestore(&stReadCntl->lock, flags);
	return (pwrite <= pread);
#else
	return stReadCntl->empty;
#endif
}

/*****************************************************************************
* �� �� ��  : SLAVE_Buff_IsFull
*
* ��������  : �жϽ���buffer�Ƿ�д��
*
* �������  : pstSlaveCtx: �豸����ṹָ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_BOOL SLAVE_Buff_IsFull(SLAVE_CTX_S *pstSlaveCtx)
{
	SLAVE_RX_SUB_S *stReadCntl = pstSlaveCtx->pstSlaveDev->stReadCntl;

#if 0
	BSP_U32 pstart;
	BSP_U32 pwrite;
	/*transfer over will acess*/

	pstart =  (BSP_U32)stReadCntl->pStart;
	pwrite = (BSP_U32)stReadCntl->pWrite;


	return (pwrite >= pstart + DATA_BUF_SIZE);
#else
	return stReadCntl->full;
#endif
}

/*****************************************************************************
* �� �� ��  : SLAVE_GET_DataSize
*
* ��������  : ��ȡBUFFER�е���Ч���ݿռ��С
*
* �������  : pstSlaveCtx: SLAVE�豸����ṹ��
* �������  : u32BuffSize ʣ����Ч���ݿռ�
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_VOID SLAVE_GET_DataSize(SLAVE_CTX_S *pstSlaveCtx,BSP_U32 *u32BuffSize)
{
	BSP_U32 pread;
	BSP_U32 pwrite;
	unsigned int flags;
	SLAVE_RX_SUB_S *stReadCntl;
	stReadCntl = pstSlaveCtx->pstSlaveDev->stReadCntl;

	spin_lock_irqsave(&stReadCntl->lock, flags);

	pread =  (BSP_U32)pstSlaveCtx->pstSlaveDev->stReadCntl->pRead;
	pwrite = (BSP_U32)pstSlaveCtx->pstSlaveDev->stReadCntl->pWrite;

	spin_unlock_irqrestore(&stReadCntl->lock, flags);
#if 1
	if (!stReadCntl->empty) {
        *u32BuffSize = 	(pwrite - pread + DATA_BUF_SIZE ) % DATA_BUF_SIZE;

	} else {
		*u32BuffSize = 0;
	}
#else
	if(pread <= pwrite)
    {
        /* дָ����ڶ�ָ��*/
        *u32BuffSize = (BSP_U32)(pwrite - pread);
     }
    else
    {
        *u32BuffSize = 0;
    }
#endif
   DBG("pread: 0x%x pwrite: 0x%x\n", pread, pwrite);

    return;
}

/*****************************************************************************
* �� �� ��  : SLAVE_GET_IdleSize
*
* ��������  : ��ȡBUFFER�еĿ��пռ��С,writeָ���Ĵ洢�ռ�
*
* �������  : pstSlaveCtx:  SLAVE�豸����ṹ��
* �������  : u32IdleSize: ���пռ��С
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 SLAVE_GET_IdleSize(SLAVE_CTX_S *pstSlaveCtx,BSP_U32 *u32IdleSize)
{
	BSP_U32 pstart;
	BSP_U32 pRead;
	BSP_U32 pwrite;
	unsigned long flags;
	SLAVE_RX_SUB_S *stReadCntl = pstSlaveCtx->pstSlaveDev->stReadCntl;
	/*transfer over will acess*/
#if 0
	spin_lock_irqsave(&stReadCntl->lock, flags);

	pstart =  (BSP_U32)stReadCntl->pStart;
	pwrite = (BSP_U32)stReadCntl->pWrite;

	spin_unlock_irqrestore(&stReadCntl->lock, flags);

	*u32IdleSize = DATA_BUF_SIZE + pstart - pwrite;

	DBG("pstart: 0x%x pwrite: 0x%x idle buffer len: 0x%x\n", pstart, pwrite, *u32IdleSize);
#else
	pRead =  (BSP_U32)stReadCntl->pRead;
	pwrite = (BSP_U32)stReadCntl->pWrite;
	*u32IdleSize = (DATA_BUF_SIZE + pRead - pwrite) / DATA_BUF_SIZE;

#endif
	 return BSP_OK ;
}

/*****************************************************************************
* �� �� ��  : SLAVE_GET_IdleSize
*
* ��������  : ioctl ��������ȡSLAVE�Ĺ���״̬
*
* �������  : pstSlaveCtx:  SLAVE�豸����ṹ��
* �������  : u32SlaveStat: SLAVE����״̬��Ϣ
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 SLAVE_GET_Status(SLAVE_CTX_S *pstSlaveCtx,SLAVE_STAT_S *u32SlaveStat)
{
    u32SlaveStat = pstSlaveCtx->pstSlaveDev->pstSlaveStat;
    return SLAVE_OK;
} /*lint !e550*/

/*****************************************************************************
* �� �� ��  : SLAVE_GET_BuffInfo
*
* ��������  : ioctl ��������ȡSLAVE����buffer��Ϣ
*
* �������  : pstSlaveCtx:  SLAVE�豸����ṹ��
* �������  : stSlaveBuff: SLAVE����buffer��Ϣ
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 SLAVE_GET_BuffInfo(SLAVE_CTX_S *pstSlaveCtx,SLAVE_RX_BUFF_INFO_S *stSlaveBuff)
{
	BSP_U32 u32BuffInfo = 0;
	unsigned int flags;
	SLAVE_RX_SUB_S *stReadCntl;
	stReadCntl = pstSlaveCtx->pstSlaveDev->stReadCntl;

	spin_lock_irqsave(&stReadCntl->lock, flags);

	stSlaveBuff->pBuffer = stReadCntl->pRead;

	spin_lock_irqsave(&stReadCntl->lock, flags);

	SLAVE_GET_DataSize(pstSlaveCtx,&u32BuffInfo);
	stSlaveBuff->u32Size = u32BuffInfo;
	return SLAVE_OK;
}

/*****************************************************************************
* �� �� ��  : SLAVE_RET_BuffInfo
*
* ��������  : ioctl ��������ȡSLAVE�黹ʹ�õ�buffer��Ϣ
*
* �������  : pstSlaveCtx:  SLAVE�豸����ṹ��
              stSlaveBuff: SLAVE����״̬��Ϣ
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 SLAVE_RET_BuffInfo(SLAVE_CTX_S *pstSlaveCtx,SLAVE_RX_BUFF_INFO_S *stSlaveBuff)
{
	SLAVE_RX_SUB_S* pRdCntl = pstSlaveCtx->pstSlaveDev->stReadCntl;
	unsigned int flags;

	spin_lock_irqsave(&pRdCntl->lock, flags);

	pRdCntl->pRead += stSlaveBuff->u32Size;
	pRdCntl->TotalLen -= stSlaveBuff->u32Size;

	if(pRdCntl->pRead >= pRdCntl->pStart+ DATA_BUF_SIZE)
	{
	    printk("llpRead go to the end\n");
	    pRdCntl->pRead = pRdCntl->pStart;
	    pRdCntl->pWrite = pRdCntl->pStart;
	}
	spin_unlock_irqrestore(&pRdCntl->lock, flags);

	return SLAVE_OK;
}

/*****************************************************************************
* �� �� ��  : SLAVE_Ioctl
*
* ��������  : SLAVE ע��ص�����
*
* �������  : u32SlaveDevId: �豸����ṹָ��
*             cmd:    ��������
*             arg: �ص�����ָ��
* �������  : ��
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 SLAVE_Ioctl(BSP_S32 s32SlaveDevId, BSP_U32 cmd, BSP_U32 arg)
{
    SLAVE_CTX_S *pstSlaveCtx = (SLAVE_CTX_S *)s32SlaveDevId;
    BSP_S32 ret = SLAVE_OK;

    if (BSP_NULL == pstSlaveCtx)
    {
        printk("slave dev ctx error, line:%d\n",__LINE__);
        return SLAVE_ERR_MODULE_NOT_INITED;
    }

    switch(cmd)
    {
    case SLAVE_IOCTL_SET_READ_CB:
        pstSlaveCtx->pstSlaveDev->stReadPrv.readDoneCB = (SLAVE_READ_DONE_CB_T)arg;
        break;

    case SLAVE_IOCTL_SET_WRITE_CB:
        pstSlaveCtx->pstSlaveDev->stWritePrv.writeDoneCB = (SLAVE_WRITE_DONE_CB_T)arg;
        break;

    case SLAVE_IOCTL_GET_STATUS:
        if (0 == arg)
        {
			printk("invalid args:0x%x, line:%d\n",arg, __LINE__);
            return SLAVE_ERR_INVALID_PARA;
        }
        /*����SLAVE �Ĺ���״̬*/
        ret = SLAVE_GET_Status(pstSlaveCtx,(SLAVE_STAT_S*)arg);
        break;

    case SLAVE_IOCTL_GET_BUFFINFO:
        if (0 == arg)
        {
			printk("invalid args:0x%x, line:%d\n",arg, __LINE__);
            return SLAVE_ERR_INVALID_PARA;
        }
        /*����SLAVE ����buffer����Ϣ*/
        ret = SLAVE_GET_BuffInfo(pstSlaveCtx,(SLAVE_RX_BUFF_INFO_S*)arg);
        break;

    case SLAVE_IOCTL_RET_BUFF:
        if (0 == arg)
        {
			printk("invalid args:0x%x, line:%d\n",arg, __LINE__);
            return SLAVE_ERR_INVALID_PARA;
        }
        /*�ͷ�SLAVE ����buffer����Ϣ*/
        ret = SLAVE_RET_BuffInfo(pstSlaveCtx,(SLAVE_RX_BUFF_INFO_S*)arg);
        break;

    case SLAVE_CLR_STAT_CNT:
        SLAVE_ClrStatCnt(s32SlaveDevId);
        break;

    default:
        break;
    }

    return ret;
}

/*****************************************************************************
* �� �� ��  : SLAVE_WriteAsync
*
* ��������  : SLAVE ������дʵ��
*
* �������  : u32SlaveDevId: �豸����ṹָ��
*             pBuf:    Դ����buffer���׵�ַ
*             u32Size: Դ���ݵ��ֽ���
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 SLAVE_WriteAsync(BSP_S32 s32SlaveDevId, BSP_U8 *pBuf, BSP_U8 *pBufPhy, BSP_U32 u32Size)
{
    SLAVE_CTX_S *pSlaveCtx = (SLAVE_CTX_S *)s32SlaveDevId;
    BSP_U32 len;
    BSP_U32 desCnt;
    BSP_BOOL bTranDir = 0;
    SLAVE_NODE_INFO *s_node = BSP_NULL;

    /*�������ֻ�ܴ���512K�ֽڣ��������ݵĴ��䣬���ϲ���Ԥ����*/
    if ((NULL == pBuf) || (0 == u32Size) || (SLAVE_TRANS_PKT_SIZE < u32Size))
    {
		printk("buf:0x%x, size:%d\n",pBuf, u32Size);
        return SLAVE_ERR_INVALID_PARA;
    }

    /*��free_list��ȡһ���ڵ�*/
    s_node = GetOffNodeFromFreeList(pSlaveCtx);

    if(0 == GetListNodeNum(pSlaveCtx))
    {
        /*����ǵ�һ���ڵ㣬��host����д����*/
        s_node->stItem.dlen = u32Size;
        s_node->stItem.addr = pBuf;
        s_node->stItem.addrPhy = pBufPhy;

        /*��ӵ�use_list��*/
        AddNodeToUseList(pSlaveCtx, s_node);

        len = u32Size;
        desCnt = ADMA_GET_NODE_COUNT(len);
       	/*�����32�ֽڶ��룬����һ���ڵ㣬���͸���buffer����*/
        if((!ADMA_CHECK_ALIGN((BSP_U32)pBuf))&&(len > SLAVE_CACHE_ALIGN))
        {
            desCnt = desCnt + 1;
        }

        /*���ú�������*/
        ADMA_Desc_Queue_Config(pSlaveCtx->pstSlaveDev->stAdmaSendHandle, NULL, (BSP_U32)pBuf, (BSP_U32)pBufPhy, len, desCnt,0,bTranDir);

        /*����д������Ϣ*/
        (void)hal_sdio_S2MRdySend(u32Size);
    }
    else
    {
        /*������ǵ�һ���ڵ�,�����ݼ��뵽������*/
        s_node->stItem.dlen = u32Size;
        s_node->stItem.addr = pBuf;
        s_node->stItem.addrPhy = pBufPhy;
        if(GetListNodeNum(pSlaveCtx) > LIST_NODE_NUM)
        {
            pSlaveCtx ->pstSlaveDev->stWritePrv.u32NodeInUse = LIST_NODE_NUM;
        }
        else
        {
            AddNodeToUseList(pSlaveCtx, s_node);
        }
    }
    return SLAVE_OK;
}

/*****************************************************************************
* �� �� ��  : SLAVE_Write
*
* ��������  : SLAVE д�ӿ�
*
* �������  : u32SlaveDevId: �豸����ṹָ��
*             pBuf:    Դ����buffer���׵�ַ
*             u32Size: Դ���ݵ��ֽ���
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
 BSP_S32 SLAVE_Write(BSP_S32 s32SlaveDevId, BSP_U8 *pBuf, BSP_U8 *pBufPhy, BSP_U32 u32Size)
{
    SLAVE_CTX_S *pstSlaveCtx = (SLAVE_CTX_S *)s32SlaveDevId;
    BSP_BOOL bTranDir = BSP_FALSE;
    BSP_U32 len = 0;
    BSP_U32 desCnt = 0;

	static unsigned int times;
    if (NULL == pstSlaveCtx || !pstSlaveCtx->bSlaveInit)
    {
		printk("slave dev ctx error or not init, line:%d\n", __LINE__);
        return SLAVE_ERR_MODULE_NOT_INITED;
    }

    if (BSP_NULL == pBuf || 0 == u32Size || u32Size >= SLAVE_TRANS_PKT_SIZE)
    {
		printk("write buf:0x%x, size:%d\n",pBuf, u32Size);
        return SLAVE_ERR_INVALID_PARA;
    }

    /* ���������д�ص��������첽���� */
    if (pstSlaveCtx->pstSlaveDev->stWritePrv.writeDoneCB)
    {
        printk("writeDone defined\n");
        /*���������������Ƚ�������Ϣ�ݴ浽����������*/
        return SLAVE_WriteAsync(s32SlaveDevId, pBuf, pBufPhy, u32Size);
    }

    len = u32Size;

    desCnt = ADMA_GET_NODE_COUNT(len);
    /*�����32�ֽڶ��룬����һ���ڵ㣬���͸���buffer����*/
    if((!ADMA_CHECK_ALIGN((BSP_U32)pBuf))&&(len > SLAVE_CACHE_ALIGN))
    {
        printk("write buffer no aligned\n");
        desCnt = desCnt + 1;
    }

    /*���������������Ͷ�����*/
    ADMA_Desc_Queue_Config(pstSlaveCtx->pstSlaveDev->stAdmaSendHandle, NULL, (BSP_U32)pBuf, (BSP_U32)pBufPhy, len, desCnt,0,bTranDir);
    (BSP_VOID)hal_sdio_S2MRdySend(len);

	pstSlaveCtx->pstSlaveDev->stWritePrv.mount = len;

    /*ͬ��д������ֻ�еȵ�host���Ͷ�����󣬲Ž����ݷ���host*/
    down(&pstSlaveCtx->pstSlaveDev->stWritePrv.stWrBlockSem);
     DBG("down write semaphore (%d) times\n", times++);
    return (BSP_S32)len;
}

/*****************************************************************************
* �� �� ��  : SLAVE_Read
*
* ��������  : SLAVE ������ʵ��
*
* �������  : u32SlaveDevId: �豸����ṹָ��
*             pBuf: Ŀ��buffer���׵�ַ
*             u32Size: ��ȡ�������ֽ���
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 SLAVE_Read(BSP_S32 s32SlaveDevId, BSP_U8 *pBuf, BSP_U32 u32Size)
{
    SLAVE_CTX_S *pstSlaveCtx = (SLAVE_CTX_S *)s32SlaveDevId;
    SLAVE_RX_SUB_S *pRdCntl = pstSlaveCtx->pstSlaveDev->stReadCntl;
    BSP_U8* pstart = pRdCntl->pStart;
    BSP_U32 u32BuffSize = 0;
    BSP_U32 u32TranSize = 0;
	unsigned int flags;
	unsigned int remain;
	unsigned int pread;
	unsigned int pend;
	static unsigned long down_times;
    if (NULL == pstSlaveCtx || !pstSlaveCtx->bSlaveInit)
    {
		printk("slave dev ctx error or not init, line:%d\n",__LINE__);
		return SLAVE_ERR_MODULE_NOT_INITED;
    }

    if (BSP_NULL == pBuf || 0 == u32Size || u32Size > DATA_BUF_SIZE)
    {
		return SLAVE_ERR_INVALID_PARA;
    }
    	DBG("buf:0x%x, size:%d\n",pBuf, u32Size);

	DBG("lpWrite:%#x,lTotalLen:%#x,lpRead:%#x\n",(int)pRdCntl->pWrite,
		(int)pRdCntl->TotalLen,(int)pRdCntl->pRead);


    if(SLAVE_Buff_IsEmpty(pstSlaveCtx))
    {
        pstSlaveCtx ->pstSlaveDev->pstSlaveStat->statofCur = RECV_BUFF_EMPTY;
        /*��������host��slave����*/

    }
	down(&pstSlaveCtx->pstSlaveDev->stReadPrv.stRdBlockSem);
	DBG("buffer is %s empty, down read semaphore (%d) times\n",
		SLAVE_Buff_IsEmpty(pstSlaveCtx) ? "" : "not", down_times++);
#if 0
    /*�������,����host����slave��������*/
    SLAVE_GET_DataSize(pstSlaveCtx,&u32BuffSize);

    u32TranSize = (u32BuffSize < u32Size)?u32BuffSize:u32Size;
#else
	u32TranSize = u32Size;
#endif

   DBG("u32TranSize: %d\n", u32TranSize);
    /*�����ݴӽ���buffer�п������ϲ��ڴ���*/
	spin_lock_irqsave(&pRdCntl->lock, flags);

	pend = pRdCntl->pStart + DATA_BUF_SIZE;
	remain = (unsigned int)pend - (unsigned int)pRdCntl->pRead;
	DBG("memcpy start, u32TranSize(%d) remain(%d)\n", u32TranSize, remain);
	if (remain < u32TranSize) {
		memcpy(pBuf, pRdCntl->pRead, remain);
		memcpy(pBuf + remain, pRdCntl->pStart, u32TranSize - remain);
		pRdCntl->pRead = pRdCntl->pStart + u32TranSize - remain;
	} else {
		memcpy(pBuf, pRdCntl->pRead, u32TranSize);

		pRdCntl->pRead += u32TranSize;
	}
	DBG("memcpy end\n");

	if (pRdCntl->pRead = pRdCntl->pWrite) {
		pRdCntl->empty = 1;
	}
	DBG("pread: 0x%0x pwrite: 0x%0x\n", pRdCntl->pRead, pRdCntl->pWrite);

    spin_unlock_irqrestore(&pRdCntl->lock, flags);
    pstSlaveCtx ->pstSlaveDev->pstSlaveStat->statofCur = TRANS_IDLE;

    if(SLAVE_Buff_IsEmpty(pstSlaveCtx))
    {
        pstSlaveCtx ->pstSlaveDev->pstSlaveStat->statofCur = RECV_BUFF_EMPTY;
    }

    return (BSP_S32)u32TranSize;
}

/*****************************************************************************
* �� �� ��  : SLAVE_Open
*
* ��������  : SLAVE �豸�򿪽ӿ�
*
* �������  : ��
*
* �������  : ��
* �� �� ֵ  : �豸ID
*****************************************************************************/
BSP_S32 SLAVE_Open(void)
{
    return (BSP_S32)&g_stSlaveCtx;
}

/*****************************************************************************
* �� �� ��  : SLAVE_Close
*
* ��������  : SLAVE �豸�رսӿ�
*
* �������  : s32SlaveDevId:�豸ID
*
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID SLAVE_Close(BSP_S32 s32SlaveDevId)
{
    SLAVE_CTX_S *pstSlaveCtx = (SLAVE_CTX_S *)s32SlaveDevId;
    pstSlaveCtx->pstSlaveDev->stReadPrv.readDoneCB = NULL;
    pstSlaveCtx->pstSlaveDev->stWritePrv.writeDoneCB = NULL;
}

/*****************************************************************************
* �� �� ��  : SLAVE_ClrStatCnt
*
* ��������  : ���״̬����
*
* �������  : s32SlaveDevId:�豸ID
*
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID SLAVE_ClrStatCnt(BSP_S32 s32SlaveDevId)
{
    SLAVE_CTX_S *pstSlaveCtx = (SLAVE_CTX_S *)s32SlaveDevId;
    pstSlaveCtx->pstSlaveDev->pstSlaveStat->dma_err_int = 0;
    pstSlaveCtx->pstSlaveDev->pstSlaveStat->msg_receive_fail = 0;
    pstSlaveCtx->pstSlaveDev->pstSlaveStat->readCB_cnt= 0;
    pstSlaveCtx->pstSlaveDev->pstSlaveStat->writeCB_cnt= 0;
    pstSlaveCtx->pstSlaveDev->pstSlaveStat->isr_total = 0;
}

/*****************************************************************************
* �� �� ��  : SLAVE_SoftRst
*
* ��������  : SLAVE�����λ
*
* �������  : ��
*
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID SLAVE_SoftRst(void)
{
    g_stSlaveCtx.pstSlaveDev->pstSlaveStat->isr_reset_int++;
    /*ȫ��ȥ��ʼ��*/
    //SLAVE_deinit();
    /*�����λ*/
	SLAVE_Rst();
	slave_reinit();
    /*���³�ʼ��*/
    //(BSP_VOID)SLAVE_Init();
}

BSP_VOID SLAVE_Abort(void)
{
   printk("TRANS ABORT!\n");
}

BSP_VOID SLAVE_Susp(void)
{
   printk("TRANS SUSPEND!\n");
}

BSP_VOID SLAVE_Resume(void)
{
   printk("TRANS RESUME!\n");
}

/*****************************************************************************
* �� �� ��  : SLAVE_Help
*
* ��������  : debug������Ϣ
*
* �������  : ��
*
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID SLAVE_Help(void)
{
    printk("\r |*************************************|\n");
    printk("\r g_stSlaveCtx:          0x%x\n", &g_stSlaveCtx);
    printk("\r BSP_SlaveDumpNode :     �鿴����ڵ���Ϣ\n");
    printk("\r BSP_SlaveDumpFreeList:  �鿴free������Ϣ\n");
    printk("\r BSP_SlaveDumpUseList:   �鿴use������Ϣ\n");
    printk("\r BSP_SlaveDevDump :      �鿴�豸��Ϣ\n");
    //printk("\r BSP_SlaveDevDump :      �鿴�豸״̬��Ϣ\n");
    //printk("\r BSP_SlaveDevDump :      �鿴����buffer״̬��Ϣ\n");
    printk("\r SLAVE_RegShow :         �Ĵ�����Ϣ\n");
    printk("\r |*************************************|\n");
}

/*****************************************************************************
* �� �� ��  : SLAVE_RegShow
*
* ��������  : show slave IP register info
*
* �������  : ��
*
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID SLAVE_RegShow(void)
{
    SLAVE_RegPrint();
}

/*dump���нڵ���Ϣ*/
BSP_S32 BSP_SlaveDumpNode()
{
    SLAVE_CTX_S *pstSlaveCtx = (SLAVE_CTX_S *)&g_stSlaveCtx;
    BSP_U32 i;

    if(NULL == pstSlaveCtx)
    {
        printk("slave dev is not exist\n");
        return SLAVE_ERR_MODULE_NOT_INITED;
    }

    for (i = 0; i < pstSlaveCtx->pstSlaveDev->stWritePrv.u32NodeNo; i++)
    {
        printk("pNodeInfo[%d].ptr:         0x%x\n", i, (BSP_U32)&(pstSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[i]));
        printk("pNodeInfo[%d].stItem.addr: 0x%x\n", i, (BSP_U32)pstSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[i].stItem.addr);
        printk("pNodeInfo[%d].stItem.phy: 0x%x\n", i, (BSP_U32)pstSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[i].stItem.addrPhy);
        printk("pNodeInfo[%d].stItem.dlen: 0x%x\n", i, pstSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[i].stItem.dlen);
        printk("pNodeInfo[%d].stList.next: 0x%x\n", i, (BSP_U32)pstSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[i].stList.next);
        printk("pNodeInfo[%d].stList.prev: 0x%x\n", i, (BSP_U32)pstSlaveCtx->pstSlaveDev->stWritePrv.pNodeInfo[i].stList.prev);
    }
    return BSP_OK;

}

/*dump free list�Ľڵ���Ϣ*/
BSP_S32 BSP_SlaveDumpFreeList()
{
    BSP_U32 cnt = 0;
    BSP_U32 free_cnt = 0;
    SLAVE_CTX_S *pstSlaveCtx = (SLAVE_CTX_S *)&g_stSlaveCtx;
    if(NULL == pstSlaveCtx)
    {
        printk("slave dev is not exist\n");
        return SLAVE_ERR_MODULE_NOT_INITED;
    }

    if (list_empty(&pstSlaveCtx->pstSlaveDev->stWritePrv.free_list))
    {
        printk("free list is empty\n");
    }
    else
    {
        struct list_head *pNode;
        SLAVE_NODE_INFO* pSlaveNode;
        pNode = pstSlaveCtx->pstSlaveDev->stWritePrv.free_list.next;

        printk("Read Free List Dump:\n");
        printk("FreeList.ptr:            0x%x\n", (int)&pstSlaveCtx->pstSlaveDev->stWritePrv.free_list);
        printk("FreeList.next:           0x%x\n", (int)pstSlaveCtx->pstSlaveDev->stWritePrv.free_list.next);
        printk("FreeList.prev:           0x%x\n", (int)pstSlaveCtx->pstSlaveDev->stWritePrv.free_list.prev);
        printk("\n");
        cnt = 0;
        while(pNode != &pstSlaveCtx->pstSlaveDev->stWritePrv.free_list)
        {
            pSlaveNode = list_entry(pNode, SLAVE_NODE_INFO, stList);
            printk("pNodeInfo ptr:             0x%x\n", (int)pSlaveNode);
            printk("pNodeInfo stItem.addr:     0x%x\n", (int)pSlaveNode->stItem.addr);
            printk("pNodeInfo stItem.phy:     0x%x\n", (int)pSlaveNode->stItem.addrPhy);
            printk("pNodeInfo stItem.dlen:     0x%x\n", (int)pSlaveNode->stItem.dlen);
            printk("pNodeInfo stList.next:     0x%x\n", (int)pSlaveNode->stList.next);
            printk("pNodeInfo stList.prev:     0x%x\n", (int)pSlaveNode->stList.prev);
            printk("\n");
            pNode = pNode->next;
            cnt++;
            if (cnt > pstSlaveCtx->pstSlaveDev->stWritePrv.u32NodeNo)
            {
                printk("Free list error\n");
                break;
            }
        }
        free_cnt = pstSlaveCtx->pstSlaveDev->stWritePrv.u32NodeNo - pstSlaveCtx->pstSlaveDev->stWritePrv.u32NodeInUse;
        printk("Free List Dump Num:%d,free_cnt:%d\n\n", cnt,free_cnt);
    }

    return SLAVE_OK;
}

/*dump use list�е���Ϣ*/
BSP_S32  BSP_SlaveDumpUseList()
{
    BSP_U32 cnt = 0;

    SLAVE_CTX_S *pstSlaveCtx = &g_stSlaveCtx;
    if(NULL == pstSlaveCtx)
    {
        printk("slave dev is not exist\n");
        return SLAVE_ERR_MODULE_NOT_INITED;
    }
    if (list_empty(&pstSlaveCtx->pstSlaveDev->stWritePrv.use_list))
    {
        printk("use list is empty\n");
    }
    else
    {
        struct list_head *pNode;
        SLAVE_NODE_INFO* pSlaveNode;
        pNode = pstSlaveCtx->pstSlaveDev->stWritePrv.use_list.next;

        printk("Read use List Dump:\n");
        printk("use_list.ptr:            0x%x\n", (int)&pstSlaveCtx->pstSlaveDev->stWritePrv.free_list);
        printk("use_list.next:           0x%x\n", (int)pstSlaveCtx->pstSlaveDev->stWritePrv.free_list.next);
        printk("use_list.prev:           0x%x\n", (int)pstSlaveCtx->pstSlaveDev->stWritePrv.free_list.prev);
        printk("\n");
        cnt = 0;
        while(pNode != &pstSlaveCtx->pstSlaveDev->stWritePrv.use_list)
        {
            pSlaveNode = list_entry(pNode, SLAVE_NODE_INFO, stList);
            printk("pNodeInfo ptr:             0x%x\n", (int)pSlaveNode);
            printk("pNodeInfo stItem.addr:     0x%x\n", (int)pSlaveNode->stItem.addr);
            printk("pNodeInfo stItem.phy:     0x%x\n", (int)pSlaveNode->stItem.addrPhy);
            printk("pNodeInfo stItem.dlen:     0x%x\n", (int)pSlaveNode->stItem.dlen);
            printk("pNodeInfo stList.next:     0x%x\n", (int)pSlaveNode->stList.next);
            printk("pNodeInfo stList.prev:     0x%x\n", (int)pSlaveNode->stList.prev);
            printk("\n");
            pNode = pNode->next;
            cnt++;
            if (cnt > pstSlaveCtx->pstSlaveDev->stWritePrv.u32NodeNo)
            {
                printk("use list error\n");
                break;
            }
        }
        printk("use list Dump  Num:%d, pstSlaveCtx->pstSlaveDev->stWritePrv.u32NodeInUse:%d\n\n", cnt,pstSlaveCtx->pstSlaveDev->stWritePrv.u32NodeInUse);

    }

    return SLAVE_OK;
}

BSP_VOID  SLAVE_RECV_BuffRst(SLAVE_RX_SUB_S *stRcv)
{
	unsigned int flags;

	spin_lock_irqsave(&stRcv->lock, flags);
	stRcv->pWrite =  stRcv->pStart;
	stRcv->pRead =  stRcv->pStart;
	stRcv->TotalLen = 0;
	spin_unlock_irqrestore(&stRcv->lock, flags);

	memset(stRcv->pStart,0,DATA_BUF_SIZE);

}

/*dump slave status*/
BSP_S32 BSP_SlaveDevDump()
{
    SLAVE_CTX_S *pstSlaveCtx = &g_stSlaveCtx;
    SLAVE_DEV_S *stSlaveDev = pstSlaveCtx->pstSlaveDev;
    SLAVE_STAT_S *stSlaveStat = stSlaveDev->pstSlaveStat;
    SLAVE_RX_SUB_S *stBuffInfo = stSlaveDev->stReadCntl;
    SLAVE_TX_PRIV_S stWriteInfo = stSlaveDev->stWritePrv;
    SLAVE_RX_PRIV_S stReadInfo = stSlaveDev->stReadPrv;

    if(NULL == pstSlaveCtx)
    {
        printk("slave dev is not exist\n");
        return SLAVE_ERR_MODULE_NOT_INITED;
    }

    printk("status info:\n");
    printk("stSlaveStat->err_code           0x%x\n", stSlaveStat->err_code);
    printk("stSlaveStat->statofCur          0x%x\n", stSlaveStat->statofCur);
    printk("stSlaveStat->isr_total          0x%x\n", stSlaveStat->isr_total);
    printk("stSlaveStat->msg_receive_fail   0x%x\n", stSlaveStat->msg_receive_fail);
    printk("stSlaveStat->readCB_cnt         0x%x\n", stSlaveStat->readCB_cnt);
    printk("stSlaveStat->writeCB_cnt        0x%x\n", stSlaveStat->writeCB_cnt);
    printk("stSlaveStat->dma_err_int        0x%x\n", stSlaveStat->dma_err_int);
    printk("stSlaveStat->isr_start1_int        0x%x\n", stSlaveStat->isr_start1_int);
    printk("stSlaveStat->isr_end1_int        0x%x\n", stSlaveStat->isr_end1_int);
    printk("stSlaveStat->isr_over1_int        0x%x\n", stSlaveStat->isr_over1_int);
    printk("stSlaveStat->isr_reset_int        0x%x\n", stSlaveStat->isr_reset_int);

    printk("recv buff info\n");
    printk("stBuffInfo->pWrite              0x%x\n", (int)stBuffInfo->pWrite);
    printk("stBuffInfo->pRead               0x%x\n", (int)stBuffInfo->pRead);
    printk("stBuffInfo->pStart              0x%x\n", (int)stBuffInfo->pStart);
    printk("stBuffInfo->TotalLen            0x%x\n", (int)stBuffInfo->TotalLen);

    printk("mem info:\n");
    printk("stSlaveDev->pCis0DataBuffer     0x%x\n", (int)stSlaveDev->pCis0DataBuffer);
    printk("stSlaveDev->pCis1DataBuffer     0x%x\n", (int)stSlaveDev->pCis1DataBuffer);
    printk("stSlaveDev->pRecvDataBuff       0x%x\n", (int)stSlaveDev->pRecvDataBuff);
    printk("stSlaveDev->pCsaDataBuffer      0x%x\n", (int)stSlaveDev->pCsaDataBuffer);
    printk("stSlaveDev->msgCurrent          0x%x\n", (int)stSlaveDev->msgCurrent);

    printk("callback info:\n");
    printk("writeCB :0x%x\n",(int)stWriteInfo.writeDoneCB);
    printk("write cacheable:%d\n",(int)stWriteInfo.bCached);
    printk("readCB :0x%x\n",(int)stReadInfo.readDoneCB);

    return SLAVE_OK;
}

BSP_U32 slave_recv_loop_count(void)
{
    BSP_U32 count;
    SLAVE_GET_DataSize(&g_stSlaveCtx, &count);
    return count;
}

int test_compile(unsigned int a, char * state)
{
	*state = a*2+100;
	return 0;
}



static void __exit slave_exit(void)
{
	free_irq(INT_VEC_SDIO_SLAVE, g_stSlaveCtx.pstSlaveDev);
}

/*******************************************************************/
/* Module functions                                                */
/*******************************************************************/


module_init(slave_init);
module_exit(slave_exit);

MODULE_DESCRIPTION("Arasan SDIO Driver");
MODULE_LICENSE("GPL");
