

#include <product_config.h>

#if (FEATURE_SAMPLE_LTE_CHAN == FEATURE_ON)
#include "SOCPInterface.h"
#include "BSP_SOCP_DRV.h"
#include "soc_baseaddr_interface.h"
#if((VOS_OS_VER == VOS_VXWORKS) || (VOS_OS_VER == VOS_RTOSCK))
#include "TLPhyInterface.h"
#endif


#ifndef __SOCP_LFIXCH_H__
#define __SOCP_LFIXCH_H__

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define SOCP_DSPLOG_CHN             (SOCP_CODER_SRC_LDSP1)         // 14
#define SOCP_BBPLOG_CHN             (SOCP_DSPLOG_CHN + 2)         // 16��ʼ����8��
#define SOCP_BBPDS_CHN              (SOCP_BBPLOG_CHN + 8)  // 24
#define SOCP_FIXCHN_BASE            (SOCP_DSPLOG_CHN)
#define SOCP_FIXCHN_END             (SOCP_BBPDS_CHN)

#define DDR_SOCP_ADDR               (GLOBAL_MEM_SOCP_ADDR)
#define DDR_SOCP_SIZE               (GLOBAL_MEM_SOCP_SIZE)

#define SOCP_FIXEDID_BASE           (SOCP_DSPLOG_CHN - SOCP_FIXCHN_BASE)

#define SOCP_DSPLOG_DST_BUFID       ((BSP_S32) 1)
#define SOCP_BBPLOG_DST_BUFID       ((BSP_S32) 1)
#define SOCP_BBPDS_DST_BUFID        ((BSP_S32) 1)

#define BBP_REGISTER_SIZE               (0x500)
#define SOCP_DSPLOG_CHN_SIZE            (0x2000)
#define SOCP_BBPLOG_CHN_SIZE            (0x2000)

#define BBP_MAX_CHN (0x09)
#define BBP_MAX_LOG_CHN (0x08)
#define DSP_MAX_CHN (0x02)
#define RSV_MAX_CHN (0x08)
#define SOCP_FIXED_MAX_CHAN     (BBP_MAX_CHN+DSP_MAX_CHN+RSV_MAX_CHN)

//#define SOCP_REG_BASE                   0x500A9000
#define BBP_REG_ARM_BASEADDR            0xFD200000
#define TENSILICA_CORE0_DRAM_ADDR       LPHY_CORE0_BINARY_LOAD_ADDR /*0xE0FC0000*/


#if((VOS_OS_VER == VOS_VXWORKS) || (VOS_OS_VER == VOS_RTOSCK))
#define BBP_REG_WRITE(reg, data)                COMM_DRV_REG_WRITE(BBP_REG_ARM_BASEADDR,     reg, data)
#define BBP_REG_READ(reg, result)               COMM_DRV_REG_READ(BBP_REG_ARM_BASEADDR,      reg, result)
#define BBP_REG_SETBITS(reg, pos, bits, val)    BSP_REG_SETBITS(BBP_REG_ARM_BASEADDR,   reg, pos, bits, val)
#define BBP_REG_GETBITS(reg, pos, bits)         BSP_REG_GETBITS(BBP_REG_ARM_BASEADDR,   reg, pos, bits)
#elif(VOS_OS_VER == VOS_LINUX)
#define BBP_REG_WRITE(reg, data)                COMM_DRV_REG_WRITE(g_armBaseAddr,    reg, data)
#define BBP_REG_READ(reg, result)               COMM_DRV_REG_READ(g_armBaseAddr,     reg, result)
#define BBP_REG_SETBITS(reg, pos, bits, val)    BSP_REG_SETBITS(g_armBaseAddr,  reg, pos, bits, val)
#define BBP_REG_GETBITS(reg, pos, bits)         BSP_REG_GETBITS(g_armBaseAddr,  reg, pos, bits)
#endif

#if((VOS_OS_VER == VOS_VXWORKS) || (VOS_OS_VER == VOS_WIN32)||(VOS_OS_VER == VOS_RTOSCK))
#define SCM_FLUSH_CACHE(ptr, size)
#define SCM_INVALID_CACHE(ptr, size)
#elif (VOS_OS_VER == VOS_LINUX)
extern unsigned long long g_socp_dma_mask;
#define SCM_FLUSH_CACHE(ptr, size)                      \
    do{                                                 \
        struct device dev;                              \
        memset(&dev,0,sizeof(struct device));           \
        dev.dma_mask = (unsigned long long *)(&g_socp_dma_mask);    \
        dma_map_single(&dev, ptr, size, DMA_TO_DEVICE);  \
    }while(0)
#define SCM_INVALID_CACHE(ptr, size)                    \
    do{                                                 \
        struct device dev;                              \
        memset(&dev,0,sizeof(struct device));           \
        dev.dma_mask = (unsigned long long *)(&g_socp_dma_mask);    \
        dma_map_single(&dev, ptr, size, DMA_FROM_DEVICE);  \
    }while(0)
#endif

/*
* ͨ���򿪺궨�壬�����ڱ���Դͨ���ͽ���Ŀ��ͨ��
*/
#ifndef SOCP_CHN_ALLOCATED
#define SOCP_CHN_ALLOCATED              ((BSP_S32) 1)    /*ͨ���Ѿ�����*/
#define SOCP_CHN_UNALLOCATED            ((BSP_S32) 0)    /*ͨ��û�з���*/
#endif


/*
* ͨ��ʹ�ܺ궨�壬ͬʱ�����ڱ���Դͨ���ͽ���Դͨ��
*/
#ifndef SOCP_CHN_ENABLE
#define SOCP_CHN_ENABLE                 ( (BSP_S32) 1)   /*ͨ����*/
#define SOCP_CHN_DISABLE                ( (BSP_S32) 0)   /*ͨ���ر�*/
#endif


#define SOCP_CHECK_ENCSRC_CHAN_ID(id) \
    do {\
        if ((id >= SOCP_CODER_SRC_BUTT))\
        {\
            vos_printf("the Chan Id is invalid!\n"); \
            return BSP_ERR_SOCP_INVALID_CHAN; \
        } \
    } while (0)
#define SOCP_CHECK_ENCSRC_ALLOC(id) \
    do {\
        if (SOCP_CHN_ALLOCATED != g_stEncSrcFixChan[id].u32AllocStat)\
        {\
            vos_printf("encoder src[%d] not allocated!\n", id); \
            return BSP_ERR_SOCP_INVALID_CHAN; \
        } \
    } while (0)



typedef struct tagSOCP_ENCSRC_FIXCHAN_S
{
    BSP_U32                 u32ChanID;
    BSP_U32                 u32ChanEn;
    BSP_U32                 u32DestChanID;
    BSP_U32                 u32BypassEn;
    BSP_U32                 u32AllocStat;  /* ͨ���Ѿ���û�з���ı�ʶ*/
    BSP_U32                 u32LastRdSize;
    BSP_U32                 u32RdThreshold;
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32   eChnMode;      /* ���ݽṹ���� */
    SOCP_CHAN_PRIORITY_ENUM_UIN32    ePriority;
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eDebugEn;
    SOCP_RING_BUF_STRU      sEncSrcBuf;
    SOCP_RING_BUF_STRU      sRdBuf;
    socp_event_cb           event_cb;
    socp_rd_cb              rd_cb;
}SOCP_ENCSRC_FIXCHAN_S;



BSP_U32  DRV_SOCP_INIT_LTE_DSP(BSP_U32 ulChanId,BSP_U32 ulPhyAddr,BSP_U32 ulSize);

BSP_U32  DRV_SOCP_INIT_LTE_BBP_LOG(BSP_U32 ulChanId,BSP_U32 ulPhyAddr,BSP_U32 ulSize);

BSP_U32  DRV_SOCP_INIT_LTE_BBP_DS(BSP_U32 ulChanId,BSP_U32 ulPhyAddr,BSP_U32 ulSize);

BSP_VOID DRV_SOCP_ENABLE_LTE_BBP_DSP(BSP_U32 ulChanId);

BSP_VOID  DRV_SOCP_DSPCHN_START(BSP_VOID);
BSP_VOID  DRV_SOCP_DSPCHN_STOP(BSP_VOID);

/*****************************************************************************
 �� �� ��  : DRV_SOCP_STOP
 ��������  : �˽ӿ�����Դͨ����ֹͣ������߽��롣
 �������  : u32SrcChanID:Դͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:��������ֹͣ�ɹ���
             SOCP_ERROR:��������ֹͣʧ�ܡ�
*****************************************************************************/
#define DRV_SOCP_STOP(u32SrcChanID)   BSP_SOCP_Stop(u32SrcChanID)

/*****************************************************************************
 �� �� ��  : DRV_SOCP_START
 ��������  : �˽ӿ�����Դͨ��������������߽��롣
 �������  : u32SrcChanID:Դͨ��ID��
 �������  : �ޡ�
 �� �� ֵ  : SOCP_OK:�������������ɹ���
             SOCP_ERROR:������������ʧ�ܡ�
*****************************************************************************/
#define DRV_SOCP_START(u32SrcChanID)   BSP_SOCP_Start(u32SrcChanID)



#endif /*__SOCP_LFIXCH_H__*/

#endif

