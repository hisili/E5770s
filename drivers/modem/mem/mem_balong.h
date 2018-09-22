
#ifndef    _BSP_MEM_H_
#define    _BSP_MEM_H_

#include <bsp_sram.h>
#include <drv_comm.h>
#include <asm/cacheflush.h>
#include <asm/cache.h>
#include <asm/tlbflush.h>
#include <asm/system.h>
#include <linux/module.h>
#include <bsp_shared_ddr.h>
#include <bsp_om.h>
#include <drv_ipc_enum.h>
#include <bsp_ipc.h>
#include <drv_memory.h>
#include <bsp_memmap.h>
#include "mem_balong_drv.h"
#include <osl_spinlock.h>
#include <bsp_reset.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**************************************************************************
  �궨��
**************************************************************************/
#if defined (VERSION_V3R2)

#else
#define PBXA9_DRAM_SHARE_VIRT            IO_ADDRESS(PBXA9_DRAM_SHARE_PHYS)
#define PBXA9_DRAM_SHARE_SIZE            SZ_1M
#endif

#define VX_PBXA9_DRAM_SHARE_VIRT            IO_ADDRESS(VX_PBXA9_DRAM_SHARE_PHYS)
#define VX_PBXA9_DRAM_SHARE_SIZE            SZ_64M


#define  mem_print_error(fmt,...)      (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM, "[mem]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  mem_print_dbg(fmt,...)		       (bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_MEM, "[mem]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))

/**************************************************************************
  ��������
**************************************************************************/
s32 bsp_mem_init(void);
s32 bsp_mem_ccore_reset_cb(DRV_RESET_CALLCBFUN_MOMENT enParam, int userdata);
s32 bsp_set_most_used_size(u32 u32Size, u32 u32PoolType);

void* bsp_malloc(u32 u32Size, MEM_POOL_TYPE enFlags);
void* bsp_malloc_dbg(u32 u32Size, MEM_POOL_TYPE enFlags, u8* pFileName, u32 u32Line);
void  bsp_free(void* pMem);
void  bsp_free_dbg(void* pMem, u8* pFileName, u32 u32Line);

void* bsp_smalloc(u32 u32Size, MEM_POOL_TYPE enFlags);
void* bsp_smalloc_dbg(u32 u32Size, MEM_POOL_TYPE enFlags, u8* pFileName, u32 u32Line);
void  bsp_sfree(void* pMem);
void  bsp_sfree_dbg(void* pMem, u8* pFileName, u32 u32Line);


/**************************************************************************
  �ӿ�����
**************************************************************************/
/*****************************************************************************
* �� �� ��  : BSP_MALLOC
*
* ��������  : BSP ��̬�ڴ����
*
* �������  : sz: ����Ĵ�С(byte)
*             flags: �ڴ�����(�ݲ�ʹ��,Ԥ��)
* �������  : ��
* �� �� ֵ  : ����������ڴ�ָ��
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_MALLOC(sz, flags) bsp_malloc_dbg(sz, flags, __FILE__, __LINE__)
#else
#define BSP_MALLOC(sz, flags) bsp_malloc(sz, flags)
#endif


/**************************************************************************
  �ӿ�����
**************************************************************************/

/*****************************************************************************
* �� �� ��  : BSP_SMALLOC
*
* ��������  : BSP ��̬�ڴ����(��spin lock����,��˳���ʹ��)
*
* �������  : sz: ����Ĵ�С(byte)
*             flags: �ڴ�����(ʹ��DDR / AXI)
* �������  : ��
* �� �� ֵ  : ����������ڴ�ָ��
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_SMALLOC(sz, flags) bsp_smalloc_dbg(sz, (MEM_POOL_TYPE)flags, (u8*)__FILE__, __LINE__)
#else
#define BSP_SMALLOC(sz, flags) bsp_smalloc(sz, flags)
#endif

/*****************************************************************************
* �� �� ��  : BSP_SFREE
*
* ��������  : BSP ��̬�ڴ��ͷ�(��spin lock����,��˳���ʹ��)
*
* �������  : ptr: ��̬�ڴ�ָ��
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_SFREE(ptr) bsp_sfree_dbg(ptr, (u8*)__FILE__, __LINE__)
#else
#define BSP_SFREE(ptr) bsp_sfree(ptr)
#endif



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BSP_MEM_H_ */

