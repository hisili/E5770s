
#ifndef    _BSP_IPF_H_
#define    _BSP_IPF_H_

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**************************************************************************
  ͷ�ļ�����
**************************************************************************/
#include <osl_common.h>
#include <osl_spinlock.h>
#include <hi_base.h>
#include <hi_ipf.h>
#include <soc_interrupts.h>
#include <bsp_sram.h>
#include <bsp_shared_ddr.h>
#include <drv_ipf.h>
#include <bsp_om.h>
#include <bsp_memmap.h>
#ifdef CONFIG_BALONG_MODEM_RESET
#include <bsp_reset.h>
#endif
#ifdef CONFIG_MODULE_VIC
#ifndef __CMSIS_RTOS
#include <bsp_vic.h>
#endif
#endif

/**************************************************************************
  �궨��
**************************************************************************/
/* #define __BSP_IPF_DEBUG__*/

#ifdef __VXWORKS__
#define INT_LVL_IPF INT_LVL_IPF0
#endif

#ifdef __KERNEL__
#define INT_LVL_IPF INT_LVL_IPF1
#endif

/*IPF��������ַ����*/

#define IPF_DLBD_MEM_ADDR              SHM_MEM_IPF_ADDR
#define IPF_DLBD_MEM_SIZE               (IPF_DLBD_DESC_SIZE * sizeof(IPF_BD_DESC_S))

#define IPF_DLRD_MEM_ADDR              (IPF_DLBD_MEM_ADDR + IPF_DLBD_MEM_SIZE)
#define IPF_DLRD_MEM_SIZE               (IPF_DLRD_DESC_SIZE * sizeof(IPF_RD_DESC_S))

#define IPF_DLAD0_MEM_ADDR              (IPF_DLRD_MEM_ADDR + IPF_DLRD_MEM_SIZE)
#define IPF_DLAD0_MEM_SIZE               (IPF_DLAD0_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_DLAD1_MEM_ADDR              (IPF_DLAD0_MEM_ADDR + IPF_DLAD0_MEM_SIZE)
#define IPF_DLAD1_MEM_SIZE               (IPF_DLAD1_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_DLCD_MEM_ADDR              (IPF_DLAD1_MEM_ADDR  + IPF_DLAD1_MEM_SIZE)
#define IPF_DLCD_MEM_SIZE               (IPF_DLCD_DESC_SIZE * sizeof(IPF_CD_DESC_S))

#define IPF_ULBD_MEM_ADDR              (IPF_DLCD_MEM_ADDR  + IPF_DLCD_MEM_SIZE)
#define IPF_ULBD_MEM_SIZE               (IPF_ULBD_DESC_SIZE * sizeof(IPF_BD_DESC_S))

#define IPF_ULRD_MEM_ADDR              (IPF_ULBD_MEM_ADDR + IPF_ULBD_MEM_SIZE)
#define IPF_ULRD_MEM_SIZE               (IPF_ULRD_DESC_SIZE * sizeof(IPF_RD_DESC_S))

#define IPF_ULAD0_MEM_ADDR              (IPF_ULRD_MEM_ADDR + IPF_ULRD_MEM_SIZE)
#define IPF_ULAD0_MEM_SIZE               (IPF_ULAD0_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_ULAD1_MEM_ADDR              (IPF_ULAD0_MEM_ADDR + IPF_ULAD0_MEM_SIZE)
#define IPF_ULAD1_MEM_SIZE               (IPF_ULAD1_DESC_SIZE * sizeof(IPF_AD_DESC_S))

#define IPF_PWRCTL_BASIC_FILTER_ADDR		(IPF_ULAD1_MEM_ADDR + IPF_ULAD1_MEM_SIZE)
#define IPF_PWRCTL_BASIC_FILTER_SIZE 		(IPF_BF_NUM * sizeof(IPF_MATCH_INFO_S))

#define IPF_EXT_FILTER_ADDR             (IPF_PWRCTL_BASIC_FILTER_ADDR + IPF_PWRCTL_BASIC_FILTER_SIZE)
#define IPF_EXT_FILTER_SIZE 		     (EXFLITER_NUM * sizeof(IPF_MATCH_INFO_S))

#define IPF_PWRCTL_INFO_ADDR		(IPF_EXT_FILTER_ADDR + IPF_EXT_FILTER_SIZE)
#define IPF_PWRCTL_INFO_SIZE           128

#define IPF_PWRCTL_ADQ_WPTR_INFO_ADDR	(IPF_PWRCTL_INFO_ADDR + IPF_PWRCTL_INFO_SIZE)
#define IPF_PWRCTL_ADQ_WPTR_INFO_SIZE       32

#define IPF_PWRCTL_ADQ_RPTR_CHCTRL_ADDR	(IPF_PWRCTL_ADQ_WPTR_INFO_ADDR + IPF_PWRCTL_ADQ_WPTR_INFO_SIZE)
#define IPF_PWRCTL_ADQ_RPTR_CHCTRL_SIZE       64

#define IPF_INIT_ADDR                        (IPF_PWRCTL_ADQ_RPTR_CHCTRL_ADDR + IPF_PWRCTL_ADQ_RPTR_CHCTRL_SIZE)
#define IPF_INIT_SIZE                          16

#define IPF_ULBD_IDLENUM_ADDR       (IPF_INIT_ADDR + IPF_INIT_SIZE)
#define IPF_ULBD_IDLENUM_SIZE          16

#define IPF_DLCDRPTR_MEM_ADDR                (IPF_ULBD_IDLENUM_ADDR + IPF_ULBD_IDLENUM_SIZE)
#define IPF_DLCDRPTR_MEM_SIZE                sizeof(BSP_U32)

#define IPF_DEBUG_INFO_ADDR           (IPF_DLCDRPTR_MEM_ADDR + IPF_DLCDRPTR_MEM_SIZE)
#define IPF_DEBUG_INFO_SIZE            sizeof(IPF_DEBUG_INFO_S)

#define IPF_DEBUG_DLCD_ADDR           (IPF_DEBUG_INFO_ADDR + IPF_DEBUG_INFO_SIZE)
#define IPF_DEBUG_DLCD_SIZE            (IPF_DLCD_DESC_SIZE * sizeof(IPF_CD_DESC_S))

#define IPF_DEBUG_INFO_END_ADDR    (IPF_DEBUG_DLCD_ADDR + IPF_DEBUG_DLCD_SIZE)

#define IPF_DLDESC_SIZE   (IPF_DLBD_MEM_SIZE + IPF_DLRD_MEM_SIZE + IPF_DLAD0_MEM_SIZE + IPF_DLAD1_MEM_SIZE + IPF_DLCD_MEM_SIZE)

#define IPF_BF_NUM             		       64  /* ������������Ŀ */
#define IPF_TOTAL_FILTER_NUM            256  /* ����������Ŀ��ʹ��һ�� */
#define EXFLITER_NUM                         (IPF_TOTAL_FILTER_NUM-IPF_BF_NUM) /* ��չ��������Ŀ */
#define IPF_TAIL_INDEX                       511  /* filter��ʶ���һ��filter */
#define IPF_DISABLE_FILTER                0  /* filter disable*/
#define IPF_FILTERHEAD                      0  /* filter����ͷ������*/
#define IPF_FILTERTYPE_MASK             0xFFFF/*filter���ͱ�ʾ�ж�λ*/
#define IPF_SET_EXT_FILTER             0x10000/*filter���ͱ�ʾ�ж�λ*/
#define IPF_DQ_DEPTH_MASK              0x1FF/*BD��RD������ȼĴ���MASK*/
#define IPF_DQ_PTR_MASK                  0xFF/*BD��RD����ָ��MASK*/

#define TIME_OUT_ENABLE                   0x10000 /* ��ʱ��ʱ��ʹ��*/
#define TIME_OUT_CFG                        65           /* Ĭ�ϳ�ʱʱ��,ʱ��Ƶ��166MHZ��Ϊ0.1ms */
#define GATE_CFG                         		0x307           /*����ʱ���ſ�Ϊ�Զ�*/
#define IPF_BDWPTR_MUX                    0x100  /*BDдָ�뻥����*/
#define IPF_INT_OPEN0                        0x0C03        /*����ͨ���ж�����*/
#define IPF_INT_OPEN1                        0x0C030000 /*����ͨ���ж�����*/

#define IPF_CHANNEL_STATE_IDLE       0x14 /*ͨ��״̬IDLE*/
#define IPF_ADQ_BUF_EPT_MASK            0x00000004
#define IPF_ADQ_BUF_FULL_MASK           0x00000008
#define IPF_ADQ_BUF_MASK                0xFFFFFFF3
#define IPF_ADQ_THR_MASK                0x0000FFFF
#define IPF_ADQ_EN_MASK                 0xFFFFFFFC
#define IPF_ADQ_DEFAULT_SEETING     (IPF_ULADQ_PLEN_TH<<16)|(IPF_ADSIZE_128<<4)|(IPF_ADSIZE_128<<2)|(IPF_BOTH_ADQ_EN)
#define IPF_ADQ_OFF                          (IPF_ULADQ_PLEN_TH<<16)|(IPF_ADSIZE_128<<4)|(IPF_ADSIZE_128<<2)|(IPF_NO_ADQ)

#define IPF_UL_RPT_INT0                     0x1            /*���н���ϱ��ж�0*/
#define IPF_UL_TIMEOUT_INT0             0x2            /*���н���ϱ���ʱ�ж�0*/
#define IPF_UL_ADQ0_EPTY_INT0         0x400         /*����ADQ0���ж�0*/
#define IPF_UL_ADQ1_EPTY_INT0         0x800         /*����ADQ1���ж�0*/

#define IPF_DL_RPT_INT1                     0x10000       /*���н���ϱ��ж�0*/
#define IPF_DL_TIMEOUT_INT1             0x20000       /*���н���ϱ���ʱ�ж�0*/
#define IPF_DL_ADQ0_EPTY_INT1         0x4000000    /*����ADQ0���ж�0*/
#define IPF_DL_ADQ1_EPTY_INT1         0x8000000    /*����ADQ1���ж�0*/

#define SCH_BD_ONLY    0
#define SCH_ALL_DESC   1

#ifdef __VXWORKS__
#define IPF_PRINT                         printf
#else
#define IPF_PRINT                         printk
#endif

#define IPF_IO_ADDRESS(x)  (((x) - DDR_SHARED_MEM_ADDR) + DDR_SHARED_MEM_VIRT_ADDR)
#define IPF_IO_ADDRESS_PHY(x)  (((x) - DDR_SHARED_MEM_VIRT_ADDR) + DDR_SHARED_MEM_ADDR)


/**************************************************************************
  ö�ٶ���
**************************************************************************/


/**************************************************************************
  STRUCT����
**************************************************************************/
#if 0
typedef unsigned int TTF_BLK_MEM_STATE_ENUM_UINT32;

typedef struct
{
    TTF_BLK_MEM_STATE_ENUM_UINT32   enMemStateFlag;
    unsigned int                    ulAllocTick;        /* CPU tick when alloc or free */
    unsigned short                  usAllocFileId;      /* File ID when alloc or free */
    unsigned short                  usAllocLineNum;     /* File Line when alloc or free */
    unsigned short                  usTraceFileId;      /* File ID when traced */
    unsigned short                  usTraceLineNum;     /* File Line when traced */
    unsigned int                    ulTraceTick;        /* CPU tick when traced */
} TTF_BLK_MEM_DEBUG_ST;

typedef struct _TTF_NODE_ST
{
    struct _TTF_NODE_ST    *pNext;
    struct _TTF_NODE_ST    *pPrev;
} TTF_NODE_ST;

typedef struct _TTF_MEM_ST
{
    TTF_NODE_ST                     stNode;
    unsigned char                   ucPoolId;       /*���ڴ�������һ���ڴ�� */
    unsigned char                   ucClusterId;    /*���ڴ���������һ������*/
    unsigned char                   ucReserve[2];
    struct _TTF_MEM_ST             *pNext;          /* �����ݵ���һ�� */
    unsigned short                  usType;         /* �ڴ����ͣ�DYN��BLK��EXT���� */
    unsigned short                  usLen;          /* �������ݵ��ܳ��ȣ�����һ��ȫ����ʹ�� */
    unsigned short                  usUsed;         /* �Ѿ�ʹ�õ����ݳ���   */
    unsigned short                  usApp;          /* ʹ���߿���ʹ�õ����� */

    TTF_BLK_MEM_DEBUG_ST           *pstDbgInfo;

    unsigned char                  *pOrigData;      /* ��¼���ݵ�ԭʼָ�� */
    unsigned char                  *pData;          /* ������ݵ�ָ�룬������ָ��ṹ��������ڴ� */
    void                           *pExtBuffAddr;   /* ����extern���͵��ڴ��ַ�����ͷ� */
    unsigned long                   ulForCds[1];    /*Ԥ����CDSʹ�ã�GUģ���ó�ʼ��*/

    #if !defined (VERSION_V3R2) && !defined (VERSION_V3R2_C00)
    unsigned long                   ulForLte[6];    /*Ԥ����LTEʹ�ã�GUģ���ó�ʼ��*/
    #endif
}TTF_MEM_ST;
#endif

typedef struct tagIPF_REG_INFO_S
{
	BSP_U32 u32StartAddr; /* ��Ҫ���ݵļĴ�����ַ */
	BSP_U32 u32Length;		/* ��Ҫ���ݵĳ��� */
}IPF_REG_INFO_S;

typedef struct tagIPF_UL_S
{
    IPF_BD_DESC_S* pstIpfBDQ;
    IPF_RD_DESC_S* pstIpfRDQ;
    IPF_AD_DESC_S* pstIpfADQ0;
    IPF_AD_DESC_S* pstIpfADQ1;
    BSP_U32* pu32IdleBd; /* ��¼��һ�λ�ȡ�Ŀ���BD �� */
#ifdef __VXWORKS__
    BSP_IPF_WakeupUlCb pFnUlIntCb; /* �ж��л��ѵ�PS���� */
    BSP_IPF_AdqEmptyUlCb pAdqEmptyUlCb;/*����AD�ջص�C��*/
#endif
}IPF_UL_S;

typedef struct tagIPF_DL_S
{
    IPF_BD_DESC_S* pstIpfBDQ;
    IPF_RD_DESC_S* pstIpfRDQ;
    IPF_AD_DESC_S* pstIpfADQ0;
    IPF_AD_DESC_S* pstIpfADQ1;

    IPF_CD_DESC_S* pstIpfCDQ;
    IPF_CD_DESC_S* pstIpfDebugCDQ;

#ifdef __KERNEL__
    BSP_IPF_WakeupDlCb pFnDlIntCb; /* �ж��л��ѵ�PS���� */
    BSP_IPF_AdqEmptyDlCb pAdqEmptyDlCb;/*����AD�ջص���A����*/

/*ACoreӲ��ʹ�õ������ַ*/
    IPF_BD_DESC_S* pstIpfPhyBDQ;
    IPF_RD_DESC_S* pstIpfPhyRDQ;
    IPF_AD_DESC_S* pstIpfPhyADQ0;
    IPF_AD_DESC_S* pstIpfPhyADQ1;

#endif
    BSP_U32 *u32IpfCdRptr; /* ��ǰ���Զ�����λ�� */
    BSP_U32 u32IpfCdWptr;
    BSP_U32 u32IdleBd; /* ��¼��һ�λ�ȡ�Ŀ���BD �� */
}IPF_DL_S;

typedef struct tagIPF_ID_S
{
    BSP_U32 u32PsID;
    BSP_U32 u32FilterID;
    struct tagIPF_ID_S* pstNext;
}IPF_ID_S;

typedef struct tagIPF_FILTER_INFO_S
{
    IPF_ID_S* pstUseList;
    BSP_U32 u32FilterNum;
}IPF_FILTER_INFO_S;

typedef struct tagIPF_DEBUG_INFO_S
{
#ifdef __BSP_IPF_DEBUG__
    BSP_U32 u32IpfDebug;
#endif
    BSP_U32 u32UlBdqOverflow; /* �ж��ϱ�����BD����������� */
    BSP_U32 u32DlBdqOverflow; /* �ж��ϱ�����BD����������� */

    BSP_U32 ipf_ccore_not_init_count;    /*��ʼ��ʧ�ܻ���ccore������λ�ڼ���ͼ����*/
    BSP_U32 ipf_acore_not_init_count;    /*��ʼ��ʧ�ܻ���ccore������λ�ڼ���ͼ����*/

    BSP_U32 u32UlBdNotEnough;       /* ��������BD,BD�����ô��� */
    BSP_U32 u32UlAd0NotEnough;       /* ��������BD,BD�����ô��� */
    BSP_U32 u32UlAd1NotEnough;       /* ��������BD,BD�����ô��� */
    BSP_U32 u32UlRdNotEnough;       /* ��������BD,BD�����ô��� */
    BSP_U32 u32DlBdNotEnough;       /* ��������BD,BD�����ô��� */
    BSP_U32 u32DlAd0NotEnough;       /* ��������BD,BD�����ô��� */
    BSP_U32 u32DlAd1NotEnough;       /* ��������BD,BD�����ô��� */
    BSP_U32 u32DlRdNotEnough;       /* ��������BD,BD�����ô��� */

    BSP_U32 u32UlAdq0Overflow; /* �ж��ϱ�����BD����������� */
    BSP_U32 u32UlAdq1Overflow; /* �ж��ϱ�����BD����������� */
    BSP_U32 u32DlAdq0Overflow; /* �ж��ϱ�����BD����������� */
    BSP_U32 u32DlAdq1Overflow; /* �ж��ϱ�����BD����������� */
    BSP_U32 u32DlCdNotEnough;       /* ��������CD,CD�����ô��� */
    BSP_U32 u32UlIPFBusyNum;       /* ����IPFæ���� */
    BSP_U32 u32DlIPFBusyNum;       /* ����IPFæ���� */
    BSP_U32 u32UlIPFOccupyNum;       /* ����IPF�˼以����� */
    BSP_U32 u32DlIPFOccupyNum;       /* ����IPF�˼以����� */

    BSP_U32 ipf_ulbd_len_zero_count;
    BSP_U32 ipf_ulad0_error_count;
    BSP_U32 ipf_ulad1_error_count;
    BSP_U32 ipf_dlbd_len_zero_count;
    BSP_U32 ipf_dlad0_error_count;
    BSP_U32 ipf_dlad1_error_count;

    BSP_U32 ipf_timestamp_ul_en;
    BSP_U32 ipf_cfg_ulbd_count;
    BSP_U32 ipf_ulbd_done_count;
    BSP_U32 ipf_get_ulrd_count;
    BSP_U32 ipf_cfg_ulad0_count;
    BSP_U32 ipf_cfg_ulad1_count;
    BSP_U32 ipf_ccore_suspend_count;
    BSP_U32 ipf_ccore_resume_count;

    BSP_U32 ipf_timestamp_dl_en;
    BSP_U32 ipf_cfg_dlbd_count;
    BSP_U32 ipf_dlbd_done_count;
    BSP_U32 ipf_get_dlrd_count;
    BSP_U32 ipf_cfg_dlad0_count;
    BSP_U32 ipf_cfg_dlad1_count;
    BSP_U32 ipf_acore_suspend_count;
    BSP_U32 ipf_acore_resume_count;

}IPF_DEBUG_INFO_S;

#ifdef __VXWORKS__

typedef struct tagIPF_PWRCTL_FILTER_INFO_S
{
	BSP_U32 u32Flag;
	IPF_CHANNEL_TYPE_E eChnType;
	BSP_U32 u32FilterNum;
	IPF_FILTER_CONFIG_S *pstFilterInfo;
}IPF_PWRCTL_FILTER_INFO_S;
#endif

/**************************************************************************
  UNION����
**************************************************************************/

/**************************************************************************
  OTHERS����
**************************************************************************/



/**************************************************************************
  ��������
**************************************************************************/

/*****************************************************************************
* �� �� ��  : ipf_init
*
* ��������  : IPF��ʼ��
*
* �������  : BSP_VOID
* �������  : ��
* �� �� ֵ  : IPF_SUCCESS    ��ʼ���ɹ�
*             IPF_ERROR      ��ʼ��ʧ��
*
* �޸ļ�¼  :2011��1��21��   ³��  ����
*****************************************************************************/
BSP_S32 ipf_init(BSP_VOID);

/*****************************************************************************
* �� �� ��     : IPF_Int_Connect
*
* ��������  : ��IPF�жϴ�����(���˶��ṩ)
*
* �������  : BSP_VOID
* �������  : ��
* �� �� ֵ      : ��
*
* �޸ļ�¼  :2011��12��2��   ³��  ����
*****************************************************************************/
BSP_VOID IPF_Int_Connect(BSP_VOID);

void ipf_write_basic_filter(u32 filter_hw_id, IPF_MATCH_INFO_S* match_infos);

/*****************************************************************************
* �� �� ��  : IPF_IntHandler
*
* ��������  : IPF�жϴ�����
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  :2011��1��24��   ³��  ����
*****************************************************************************/
#ifdef __KERNEL__
irqreturn_t  IPF_IntHandler (int irq, void* dev);
#endif

#ifdef __VXWORKS__
BSP_VOID IPF_IntHandler(BSP_VOID);
#endif

#ifdef __VXWORKS__
/*****************************************************************************
* �� �� ��  : IPF_FilterList_Init
*
* ��������  : IPF�����������ʼ��     �ڲ�ʹ�ã�����Ϊ�ӿں���
*
* �������  : BSP_VOID
* �������  : ��
* �� �� ֵ  : IPF_SUCCESS    �����������ʼ���ɹ�
*             IPF_ERROR      �����������ʼ��ʧ��
*
* �޸ļ�¼  :2011��3��30��   ³��  ����
*****************************************************************************/
BSP_S32 IPF_FilterList_Init(BSP_VOID);

/*****************************************************************************
* �� �� ��  : IPF_DeleteAll
*
* ��������  : ɾ�������е����н��
*
* �������  : IPF_FILTER_CHAIN_TYPE_E eChnType  ������������
*
* �������  : ��

* �� �� ֵ  : ��
*
* �޸ļ�¼  :2011��3��30��   ³��  ����
*****************************************************************************/
BSP_VOID IPF_DeleteAll(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead);

/*****************************************************************************
* �� �� ��  : IPF_MallocOneFilter
*
* ��������  : ��freelist�з���һ�����
*
* �������  : ��
*
* �������  : ��

* �� �� ֵ  : ���ָ��
*
* �޸ļ�¼  : 2011��3��30��   ³��  ����
*
* ˵��      : �ɵ��ú�������֤һ���ܷ��䵽���
*****************************************************************************/
IPF_ID_S* IPF_MallocOneFilter(IPF_ID_S* g_stIPFFreeList);

/*****************************************************************************
* �� �� ��  : IPF_AddTailUsedFilter
*
* ��������  : �����ӵ�uselist�Ľ�β
*
* �������  : IPF_FILTER_CHAIN_TYPE_E eFilterChainhead ������������
*             IPF_ID_S* stNode             ������Ľ��ָ��
*
* �������  : ��

* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2011��3��30��   ³��  ����
*****************************************************************************/
BSP_VOID IPF_AddTailUsedFilter(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, IPF_ID_S* stNode);

/*****************************************************************************
* �� �� ��  : IPF_AddTailFilterChain
*
* ��������  : ���µĹ������������õ��Ĵ��������޸���һ����������nextindex
*
* �������  : BSP_U32 u32LastFilterID  ��һ����������ID
*             BSP_U32 u32FilterID  ��ǰ�����õĹ�����ID
*             IPF_MATCH_INFO_S* pstMatchInfo  ��ǰ�����õĹ����������ṹ��ָ��
*
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  :2011��5��12��   ³��  ����
*****************************************************************************/
BSP_VOID IPF_AddTailFilterChain(BSP_U32 u32LastFilterID, BSP_U32 u32FilterID, IPF_MATCH_INFO_S* pstMatchInfo);

/*****************************************************************************
* �� �� ��     : IPF_FindFilterID
*
* ��������  : ��������������Ѱ����PS ID ƥ���Filter ID
*
* �������  : IPF_FILTER_CHAIN_TYPE_E eFilterChainhead  ������������
*                           BSP_U32 u32PsID                PS ID
*
* �������  : BSP_U32* u32FilterID   ��ѯ����Filter ID

* �� �� ֵ     : IPF_SUCCESS                ��ѯ�ɹ�
*                          IPF_ERROR                  ��ѯʧ��
*
* �޸ļ�¼  :2011��1��11��   ³��  ����
*****************************************************************************/
BSP_S32 IPF_FindFilterID(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, BSP_U32 u32PsID, BSP_U32* u32FilterID);

/*****************************************************************************
* �� �� ��      : IPF_ConfigCD
*
* ��������  : ����CD
*
* �������  : IPF_TTF_MEM_ST *pstTtf, BSP_U16* pu16TotalDataLen, BSP_U32* pu32BdInPtr
* �������  : ��
* �� �� ֵ      :  ��
*
* �޸ļ�¼  :2011��1��24��   ³��  ����
*****************************************************************************/
//BSP_S32 IPF_ConfigCD(TTF_MEM_ST* pstTtf, BSP_U16* pu16TotalDataLen, BSP_U32* pu32BdInPtr);
#endif

#ifdef __CMSIS_RTOS
/*****************************************************************************
* �� �� ��       : ipf_drx_bak_reg
*
* ��������  : �ṩ�ĵ͹��Ľӿڣ�����IPF�����Ϣ
*
* �������  : ��
*
* �������  : ��
* �� �� ֵ     : IPF_SUCCESS     IPF�����µ磬�����Ϣ�Ѿ�����
*                           IPF_ERROR        IPF�������µ�
*
* �޸ļ�¼  : 2011��2��14��   ³��  ����
*****************************************************************************/
s32 ipf_drx_bak_reg(void);

/*****************************************************************************
* �� �� ��       : ipf_drx_restore_reg
*
* ��������  : �ṩ�ĵ͹��Ľӿڣ�����IPF�ϵ�ָ�
*
* �������  : ��
*
* �������  : ��
* �� �� ֵ     : ��
*
* ע��:�ú�����Ҫ�����жϵ�����µ���
* �޸ļ�¼  : 2011��2��14��   ³��  ����
*****************************************************************************/
void ipf_drx_restore_reg(void);

#ifdef CONFIG_BALONG_MODEM_RESET

int bsp_ipf_reset_ccore_lpm3_cb(DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata);
#endif

#endif

#if (defined(BSP_CONFIG_HI3630) && defined(__KERNEL__))
static __inline__ unsigned ipf_readl(u32 addr)
{
    return readl((const volatile void *)(addr));
}
static __inline__ void ipf_writel(u32 val, u32 addr)
{
    writel(val, (volatile void *)addr);
}
#else
static __inline__ unsigned ipf_readl(u32 addr)
{
    return readl(addr);
}
static __inline__ void ipf_writel(u32 val, u32 addr)
{
    writel(val, addr);
}
#endif


/*******************��ά�ɲ⺯��****************************************/
BSP_VOID BSP_IPF_Help(BSP_VOID);
BSP_S32 BSP_IPF_Dump_BDInfo(IPF_CHANNEL_TYPE_E eChnType);
BSP_S32 BSP_IPF_Dump_RDInfo(IPF_CHANNEL_TYPE_E eChnType);
BSP_S32 BSP_IPF_Dump_ADInfo(IPF_CHANNEL_TYPE_E eChnType, BSP_U32 u32AdType);
BSP_S32 BSP_IPF_Info(IPF_CHANNEL_TYPE_E eChnType);
BSP_VOID BSP_IPF_MEM(BSP_VOID);
/*******************��ά�ɲ⺯��****************************************/

#ifdef __cplusplus
} /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif    /* End #define _BSP_DMAC_H_ */

