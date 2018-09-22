

#ifndef __DRV_MEMORY_H__
#define __DRV_MEMORY_H__

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */



#include "drv_comm.h"

/*************************MEMORY START********************************/

/**************************************************************************
  �궨��
**************************************************************************/
/* �ڴ������, Flags����� */
typedef enum tagMEM_POOL_TYPE
{
    MEM_NORM_DDR_POOL = 0,
    MEM_ICC_DDR_POOL,
    MEM_ICC_AXI_POOL,
    MEM_POOL_MAX
}MEM_POOL_TYPE;

/**************************************************************************
  �ӿ�����
**************************************************************************/
BSP_VOID* bsp_malloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags);
BSP_VOID* bsp_malloc_dbg(BSP_U32 u32Size, MEM_POOL_TYPE enFlags, BSP_U8* pFileName, BSP_U32 u32Line);
BSP_VOID  bsp_free(BSP_VOID* pMem);
BSP_VOID  bsp_free_dbg(BSP_VOID* pMem, BSP_U8* pFileName, BSP_U32 u32Line);

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

/*****************************************************************************
* �� �� ��  : BSP_FREE
*
* ��������  : BSP ��̬�ڴ��ͷ�
*
* �������  : ptr: ��̬�ڴ�ָ��
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_FREE(ptr) bsp_free_dbg(ptr, __FILE__, __LINE__)
#else
#define BSP_FREE(ptr) bsp_free(ptr)
#endif

/*****************************************************************************
* �� �� ��  : BSP_SFree
*
* ��������  : BSP ��̬�ڴ��ͷ�(��spin lock����,��˳���ʹ��)
*
* �������  : pMem: ��̬�ڴ�ָ��
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID  bsp_sfree(BSP_VOID* pMem);
#define   BSP_SFree(pMem)       bsp_sfree(pMem)
/*****************************************************************************
* �� �� ��  : BSP_SMalloc
*
* ��������  : BSP ��̬�ڴ����(��spin lock����,��˳���ʹ��)
*
* �������  : u32Size: ����Ĵ�С(byte)
*             enFlags: �ڴ�����(�ݲ�ʹ��,Ԥ��)
* �������  : ��
* �� �� ֵ  : ����������ڴ�ָ��
*****************************************************************************/
BSP_VOID* bsp_smalloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags);
#define  BSP_SMalloc(u32Size, enFlags)  bsp_smalloc(u32Size, enFlags)

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern BSP_VOID* cacheDmaMalloc(BSP_U32  bytes);
#define DRV_CACHEDMAM_ALLOC(bytes) cacheDmaMalloc(bytes)
#else
#define DRV_CACHEDMAM_ALLOC(bytes) kmalloc(bytes, GFP_KERNEL)
#endif

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
extern BSP_S32 cacheDmaFree(BSP_VOID*  pBuf);
#define DRV_CACHEDMAM_FREE(pBuf) cacheDmaFree(pBuf)
#else
#define DRV_CACHEDMAM_FREE(pBuf) kfree(pBuf)
#endif

/************************************************************************
 * FUNCTION
 *       vmEnable
 * DESCRIPTION
 *       �ڴ��д��������ʹ�ܺ���
 * INPUTS
 *       NONE
 * OUTPUTS
 *       NONE
 *************************************************************************/
extern int vmEnable(int enable);
#define DRV_VM_ENABLE(flag)   vmEnable(flag)

/*****************************************************************************
 �� �� ��  : vmStateSet
 ��������  : ���õ�ַ�ռ�״̬
 �������  : ��

 �������  : �ޡ�
 �� �� ֵ  : ��
 ע������  ��
*****************************************************************************/
#define DRV_VM_STATESET(context, virtAdrs, len, stateMask, state) vmStateSet(context, virtAdrs, len, stateMask, state)

/*****************************************************************************
 �� �� ��  : BSP_CACHE_DATA_FLUSH
 ��������  :
 �������  :
 �������  : None
 �� �� ֵ  : void
*****************************************************************************/
extern void BSP_CACHE_DATA_FLUSH(void * addr, int size);

/*************************MEMORY END**********************************/


/*************************�ڴ���� START******************************/

/* DDR�и����ڴ�ε����� */
typedef enum tagBSP_DDR_SECT_TYPE_E
{
    BSP_DDR_SECT_TYPE_TTF = 0x0,
    BSP_DDR_SECT_TYPE_ARMDSP,
    BSP_DDR_SECT_TYPE_UPA,
    BSP_DDR_SECT_TYPE_CQI,
    BSP_DDR_SECT_TYPE_APT,
    BSP_DDR_SECT_TYPE_ET,
    BSP_DDR_SECT_TYPE_BBPMASTER,
    BSP_DDR_SECT_TYPE_NV,
    BSP_DDR_SECT_TYPE_DICC,
    BSP_DDR_SECT_TYPE_WAN,
    BSP_DDR_SECT_TYPE_SHARE_MEM,
    BSP_DDR_SECT_TYPE_EXCP,
    BSP_DDR_SECT_TYPE_HIFI,
    BSP_DDR_SECT_TYPE_ZSP_UP,
    BSP_DDR_SECT_TYPE_BBPSAMPLE,
    BSP_DDR_SECT_TYPE_HARQ,
    BSP_DDR_SECT_TYPE_BUTTOM
}BSP_DDR_SECT_TYPE_E;


/* AXI�и����ڴ�ε����� */
typedef enum tagBSP_AXI_SECT_TYPE_E
{
    BSP_AXI_SECT_TYPE_TEMPERATURE,
    BSP_AXI_SECT_TYPE_DICC,
    BSP_AXI_SECT_TYPE_HIFI,
    BSP_AXI_SECT_TYPE_TTF_BBP,
    BSP_AXI_SECT_TYPE_BUTTOM
}BSP_AXI_SECT_TYPE_E;


/* �ڴ������ */
typedef enum tagBSP_DDR_SECT_ATTR_E
{
    BSP_DDR_SECT_ATTR_CACHEABLE = 0x0,
    BSP_DDR_SECT_ATTR_NONCACHEABLE,
    BSP_DDR_SECT_ATTR_BUTTOM
}BSP_DDR_SECT_ATTR_E;


/* ������ʵ��ַ�Ƿ���ͬ��ö�� */
typedef enum tagBSP_DDR_SECT_PVADDR_E
{
    BSP_DDR_SECT_PVADDR_EQU = 0x0,
    BSP_DDR_SECT_PVADDR_NOT_EQU,
    BSP_DDR_SECT_PVADDR_BUTTOM
}BSP_DDR_SECT_PVADDR_E;


/* DDR�ڴ�εĲ�ѯ�ṹ */
typedef struct tagBSP_DDR_SECT_QUERY
{
    BSP_DDR_SECT_TYPE_E     enSectType;
    BSP_DDR_SECT_ATTR_E     enSectAttr;
    BSP_DDR_SECT_PVADDR_E   enPVAddr;
    BSP_U32                 ulSectSize;
}BSP_DDR_SECT_QUERY;


/* DDR�ڴ�ε���ϸ��Ϣ */
typedef struct tagBSP_DDR_SECT_INFO
{
    BSP_DDR_SECT_TYPE_E    enSectType;
    BSP_DDR_SECT_ATTR_E    enSectAttr;
    BSP_U32                ulSectVirtAddr;
    BSP_U32                ulSectPhysAddr;
    BSP_U32                ulSectSize;
}BSP_DDR_SECT_INFO;


/* AXI�ڴ�ε���ϸ��Ϣ */
typedef struct tagBSP_AXI_SECT_INFO
{
    BSP_AXI_SECT_TYPE_E    enSectType;
    BSP_U32                ulSectVirtAddr;
    BSP_U32                ulSectPhysAddr;
    BSP_U32                ulSectSize;
}BSP_AXI_SECT_INFO;

/*****************************************************************************
 �� �� ��  : BSP_DDR_GetSectInfo
 ��������  : DDR�ڴ�β�ѯ�ӿ�
 �������  : pstSectQuery: ��Ҫ��ѯ���ڴ�����͡�����
 �������  : pstSectInfo:  ��ѯ�����ڴ����Ϣ
 ����ֵ    ��BSP_OK/BSP_ERROR
*****************************************************************************/
BSP_S32 BSP_DDR_GetSectInfo(BSP_DDR_SECT_QUERY *pstSectQuery, BSP_DDR_SECT_INFO *pstSectInfo);
#define DRV_GET_FIX_DDR_ADDR(pstSectQuery, pstSectInfo) BSP_DDR_GetSectInfo(pstSectQuery, pstSectInfo)

/*****************************************************************************
 �� �� ��  : BSP_AXI_GetSectInfo
 ��������  : AXI�ڴ�β�ѯ�ӿ�
 �������  : enSectType: ��Ҫ��ѯ���ڴ������
 �������  : pstSectInfo:  ��ѯ�����ڴ����Ϣ
 ����ֵ    ��BSP_OK/BSP_ERROR
*****************************************************************************/
BSP_S32 BSP_AXI_GetSectInfo(BSP_AXI_SECT_TYPE_E enSectType, BSP_AXI_SECT_INFO *pstSectInfo);
#define DRV_GET_FIX_AXI_ADDR(enSectType, pstSectInfo) BSP_AXI_GetSectInfo(enSectType, pstSectInfo)

/*************************�ڴ���� END********************************/


/*************************��ʵ��ַת�� START**************************/

/*****************************************************************************
 �� �� ��  : DRV_DDR_VIRT_TO_PHY
 ��������  : DDR�ڴ����ַ��ʵ��ַת��
 �������  : ulVAddr�����ַ
 �������  : ��
 ����ֵ    ��ʵ��ַ
*****************************************************************************/
unsigned int DRV_DDR_VIRT_TO_PHY(unsigned int ulVAddr);

/*****************************************************************************
 �� �� ��  : DRV_DDR_PHY_TO_VIRT
 ��������  : DDR�ڴ����ַ��ʵ��ַת��
 �������  : ulPAddr��ʵ��ַ
 �������  : ��
 ����ֵ    �����ַ
*****************************************************************************/
unsigned int DRV_DDR_PHY_TO_VIRT(unsigned int ulPAddr);

/*****************************************************************************
 �� �� ��  : TTF_VIRT_TO_PHY
 ��������  : TTF�ڴ����ַ��ʵ��ַת��
 �������  : ulVAddr�����ַ
 �������  : ��
 ����ֵ    ��ʵ��ַ
*****************************************************************************/
extern unsigned int TTF_VIRT_TO_PHY(unsigned int ulVAddr);

/*****************************************************************************
 �� �� ��  : TTF_PHY_TO_VIRT
 ��������  : TTF�ڴ����ַ��ʵ��ַת��
 �������  : ulPAddr��ʵ��ַ
 �������  : ��
 ����ֵ    �����ַ
*****************************************************************************/
extern unsigned int TTF_PHY_TO_VIRT(unsigned int ulPAddr);

/*****************************************************************************
 �� �� ��  : IPF_VIRT_TO_PHY
 ��������  : IPF�Ĵ������ַ��ʵ��ַת��
 �������  : ulVAddr�����ַ
 �������  : ��
 ����ֵ    ��ʵ��ַ
*****************************************************************************/
extern unsigned int IPF_VIRT_TO_PHY(unsigned int ulVAddr);

/*****************************************************************************
 �� �� ��  : IPF_PHY_TO_VIRT
 ��������  : IPF�Ĵ������ַ��ʵ��ַת��
 �������  : ulPAddr��ʵ��ַ
 �������  : ��
 ����ֵ    �����ַ
*****************************************************************************/
extern unsigned int IPF_PHY_TO_VIRT(unsigned int ulPAddr);
/*****************************************************************************
 �� �� ��  : DRV_AXI_VIRT_TO_PHY
 ��������  : AXI�����ַ��ʵ��ַת��
 �������  : ulVAddr�����ַ
 �������  : ��
 ����ֵ    �����ַ
*****************************************************************************/
extern unsigned int DRV_AXI_VIRT_TO_PHY(unsigned int ulVAddr);

/*****************************************************************************
 �� �� ��  : DRV_AXI_PHY_TO_VIRT
 ��������  : AXI��ʵ��ַ�����ַת��
 �������  : ulVAddr��ʵ��ַ
 �������  : ��
 ����ֵ    �����ַ
*****************************************************************************/
extern unsigned int DRV_AXI_PHY_TO_VIRT(unsigned int ulPAddr);




/*************************��ʵ��ַת�� END****************************/


/*****************************************************************************
* �� �� ��  : BSP_IPM_FreeBspBuf
*
* ��������  : �ͷ��ڴ�ӿ�
*
* �������  : BSP_U8 *pBuf ��Ҫ�ͷŵ�ָ��
*
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  :2011��1��27��   ³��  ����
*****************************************************************************/
BSP_VOID BSP_IPM_FreeBspBuf(BSP_U8 *pBuf);

BSP_VOID DRV_CACHE_SYNC(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

