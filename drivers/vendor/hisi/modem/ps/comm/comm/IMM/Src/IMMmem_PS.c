

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "IMMmem_Intra.h"
#include "DrvInterface.h"

#if (VOS_WIN32 != VOS_OS_VER)
#include <linux/module.h>
#include <linux/interrupt.h>
#endif



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if 0
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* ���C�˲�ѯA���ڴ��Ԥ����Ŀ�ĵ�ַ */
#define TTF_MEM_ACPU_FREE_MEM_CNT_ADDR  (ECS_TTF_ACPU_FREE_MEM_CNT_ADDR)

/* A ����C���ϱ��ڴ���п����ĵ�ַ */
unsigned long *                         g_pACpuFreeMemBlkCnt;

/* IMM MEM �����ڴ�ص�λ���ƽṹ */
const IMM_MEM_CLUSTER_CFG_INFO_STRU     g_astImmMemSharePoolClusterTableInfo[] =
{
    {IMM_MEM_SHARE_POOL_SIZE_CLUSTER_0,         IMM_MEM_SHARE_POOL_CNT_CLUSTER_0},             /* �ڴ�鳤�ȱ���32�ֽڶ��� */
    {IMM_MEM_SHARE_POOL_SIZE_CLUSTER_1,         IMM_MEM_SHARE_POOL_CNT_CLUSTER_1}
};

const IMM_MEM_CLUSTER_CFG_INFO_STRU     g_astImmMemCtrlPoolClusterTableInfo[] =
{
    {0,                 IMM_MEM_CTRL_MEM_CNT}
};

#if (FEATURE_ON == FEATURE_IMM_MEM_DEBUG)
/* IMM MEM ����ͷ�ڴ��ʹ�õ��ڴ泤�� Byte(ÿ��36B) */
#define IMM_MEM_CTRL_MEM_TOTAL_SIZE     (IMM_MEM_CTRL_MEM_TOTAL_CNT*36)
#else
/* IMM MEM ����ͷ�ڴ��ʹ�õ��ڴ泤�� Byte(ÿ��16B) */
#define IMM_MEM_CTRL_MEM_TOTAL_SIZE     (IMM_MEM_CTRL_MEM_TOTAL_CNT*16)
#endif

/* IMM MEM ����ͷ�ڴ���ڴ����ʹ�õĳ��� */
unsigned long                           g_ulImmMemCtrlMemSuffix = 0;
const  unsigned long * const            g_pulImmMemCtrlMemSuffix = &g_ulImmMemCtrlMemSuffix;

/* IMM MEM ����ͷ�ڴ���ڴ� */
unsigned long                           g_aulImmMemCtrlMemSpace[IMM_MEM_CTRL_MEM_TOTAL_SIZE/4];
const unsigned long * const             g_paulImmMemCtrlMemSpace = &g_aulImmMemCtrlMemSpace[0];


/* IMM MEM �����ڴ�ص�λ���� */
const unsigned char IMM_MEM_SHARE_POOL_CLUSTER_CNT = (sizeof(g_astImmMemSharePoolClusterTableInfo)/sizeof(IMM_MEM_CLUSTER_CFG_INFO_STRU));

/* IMM MEM ����ͷ�ڴ�ص�λ���� */
const unsigned char IMM_MEM_CTRL_POOL_CLUSTER_CNT  = (sizeof(g_astImmMemCtrlPoolClusterTableInfo)/sizeof(IMM_MEM_CLUSTER_CFG_INFO_STRU));

/* IMM MEM ���ƿ�ħ���֣����������Ƿ񱻲� */
const unsigned short IMM_MAGIC_NUM = 0x4E8F;

/* �㿽���ڴ�س�ʼ����־����ֹ�ظ����ó�ʼ������ */
unsigned long                           g_ulImmMemInitFlag  = IMM_FALSE;

/* IMM MEM �����ڴ���ܿ��ƽṹ */
IMM_MEM_POOL_STRU                       g_astImmMemPool[IMM_MEM_POOL_ID_BUTT];

/* IMM MEM �ⲿ�ڴ���ܿ��ƽṹָ�� */
IMM_MEM_POOL_STRU *const                g_pstImmExtMemPool = &g_astImmMemPool[IMM_MEM_POOL_ID_EXT];


/* �ڴ�����ʧ��ָ������ */
unsigned short *const                   g_apusImmAllocFailCnt[IMM_MEM_POOL_ID_BUTT] =
                                        {
                                            &g_astImmMemPool[IMM_MEM_POOL_ID_SHARE].usImmAllocFailCnt,
                                            &g_astImmMemPool[IMM_MEM_POOL_ID_EXT].usImmAllocFailCnt
                                        };


/* �ڴ�����ʧ�ܳ������޴��� */
unsigned short *const                   g_apusImmExcThresholdCnt[IMM_MEM_POOL_ID_BUTT] =
                                        {
                                            &g_astImmMemPool[IMM_MEM_POOL_ID_SHARE].usImmExcThresholdCnt,
                                            &g_astImmMemPool[IMM_MEM_POOL_ID_EXT].usImmExcThresholdCnt
                                        };


/* IMM MEM MNTN�������ȫ�ֱ��� */
IMM_MEM_REG_MNTN_FUNC_STRU              g_stImmRegMntnFuc;
IMM_MEM_REG_MNTN_FUNC_STRU * const      g_pstImmRegMntnFuc = &g_stImmRegMntnFuc;

/* IMM MEM ��ȡ�ó������ڵĵ�λ���� */
#define IMM_GET_LEN_INDEX(pstImmMemPoolInfo, usLen) \
            ((pstImmMemPoolInfo)->aucLenIndexTable[(usLen)])

#if(IMM_DEBUG_TRACE_FUNC == FEATURE_ON)
/* IMM �ڴ����Դ�ӡ���� */
unsigned char                           g_ucImmMemDebugPrint = IMM_FALSE;
#endif

/* ÿ�η����ڴ��ϱ��¼�ʱ��ÿ�������ڴ��¼��������� */
unsigned short                           g_usImmAllocFailCntThreshold = 1000;

/* IMM MEM FREE ��ά�ɲ�ʵ�� */
IMM_MEM_FREE_MNTN_INFO_STRU             g_stImmMemFreeMntnEntity;

VOS_SPINLOCK                      g_astImmSpinLock[IMM_MEM_POOL_ID_BUTT];

VOS_SPINLOCK                      g_stImmFreeMntnSpinLock;


/* �����ڴ��ͷſ�ָ����Ϣ */
#define IMM_MEM_FREE_SAVE_NULL_PTR_INFO(stNullPtrInfo,usFileId,usLineNum,pstSpinLock,ulFlags) \
            do{\
                VOS_SpinLockIntLock(pstSpinLock, ulFlags);\
                (stNullPtrInfo).ulImmMemFreeNullPtrCnt++;\
                (stNullPtrInfo).usImmMemFreeFileId      = (usFileId);\
                (stNullPtrInfo).usImmMemFreeLineNum     = (usLineNum);\
                VOS_SpinUnlockIntUnlock(pstSpinLock , ulFlags);\
            }while(0)

/* �����ڴ��ͷŴ����ڴ���Ϣ */
#define IMM_MEM_FREE_SAVE_INVALID_MEM_INFO(astImmMemFreeInvalidMemInfo,pstTtfMem,ucType,usInvalidvalue,usFileId,usLineNum,pstSpinLock,ulFlags) \
            do{\
                VOS_SpinLockIntLock(pstSpinLock , ulFlags);\
                (astImmMemFreeInvalidMemInfo).ulInvalidImmMemCnt++;\
                (astImmMemFreeInvalidMemInfo).ulInvalidImmMemAddr   = (unsigned long)pstTtfMem;\
                (astImmMemFreeInvalidMemInfo).usImmMemFreeFileId    = (usFileId);\
                (astImmMemFreeInvalidMemInfo).usImmMemFreeLineNum   = (usLineNum);\
                (astImmMemFreeInvalidMemInfo).ucImmMemInvalidType   = (ucType);\
                (astImmMemFreeInvalidMemInfo).usImmMemInvalidValue  = (usInvalidvalue);\
                VOS_SpinUnlockIntUnlock(pstSpinLock , ulFlags);\
            }while(0)


void *IMM_MemCtrlMemAlloc(unsigned long ulSize)
{
    unsigned char                       *pucSpace;
    void                                *pAlloc;


    /* ���볤�ȷ�Χ��� */
    if ( IMM_MEM_CTRL_MEM_TOTAL_SIZE < (g_ulImmMemCtrlMemSuffix + ulSize) )
    {
        /*lint -e718 -e746*/
        panic(" IMM_MemCtrlMemAlloc Fail, Ctrl MEM Over run! \n");
        /*lint +e718 +e746*/
        return VOS_NULL_PTR;
    }

    pucSpace = (unsigned char *)g_aulImmMemCtrlMemSpace;

    pAlloc   = pucSpace + g_ulImmMemCtrlMemSuffix;

    /* ���ֽڶ��룬���ƿ�ʹ�ó���ƫ�� */
    g_ulImmMemCtrlMemSuffix += IMM_GET_4BYTE_ALIGN_VALUE(ulSize);

    return pAlloc;

} /* IMM_MemCtrlMemAlloc */



unsigned long IMM_MemPoolInit
(
    unsigned char                            ucPoolId,
    unsigned char                          **ppucDataMemAddr
)
{
    IMM_MEM_POOL_STRU                  *pstImmMemPool;
    IMM_MEM_STRU                      **ppst1stImmMem;
    IMM_MEM_STRU                       *pstImmMem;
    IMM_MEM_CLUSTER_STRU               *pstImmMemCluster;
    unsigned long                       ulImmMemCnt;
    unsigned char                       ucClusterId;
    IMM_MEM_STRU                      **ppTempMem;

    /*lint -e778*/
    g_pACpuFreeMemBlkCnt = (unsigned long *)DRV_AXI_PHY_TO_VIRT(TTF_MEM_ACPU_FREE_MEM_CNT_ADDR);
    /*lint +e778*/

    pstImmMemPool = IMM_MEM_GET_POOL(ucPoolId);

    /* �����Ӧ�ڴ�صĿ����ڴ�������ÿ��POOL����һ�Σ�����ָ��ÿ��clusterʹ�� */
    ppst1stImmMem = (IMM_MEM_STRU **)IMM_MemCtrlMemAlloc(sizeof(IMM_MEM_STRU *) * pstImmMemPool->usImmMemTotalCnt);

    if (VOS_NULL_PTR == ppst1stImmMem)
    {
        return IMM_FAIL;
    }

    /* �����Ӧ�ڴ�ص�IMM_MEM��ÿ��POOL����һ�Σ�����ָ��ÿ��clusterʹ�� */
    pstImmMem = (IMM_MEM_STRU *)IMM_MemCtrlMemAlloc(sizeof(IMM_MEM_STRU) * pstImmMemPool->usImmMemTotalCnt);

    if (VOS_NULL_PTR == pstImmMem)
    {
        return IMM_FAIL;
    }

    memset(ppst1stImmMem, 0, sizeof(IMM_MEM_STRU *) * pstImmMemPool->usImmMemTotalCnt);
    memset(pstImmMem, 0, sizeof(IMM_MEM_STRU) * pstImmMemPool->usImmMemTotalCnt);

    ppTempMem = ppst1stImmMem;

    /* ��¼���ڴ������IMM_MEMָ�룬����ڴ�й¶ʹ�� */
    pstImmMemPool->pstImmMemStStartAddr = pstImmMem;

    /* ����ÿ��cluster��IMM_MEM */
    for (ucClusterId = 0; ucClusterId < pstImmMemPool->ucClusterCnt; ++ucClusterId )
    {
        pstImmMemCluster    = &(pstImmMemPool->astClusterTable[ucClusterId]);

        /* ��������������Ϳ����ڴ�������Ĺ�ϵ */
        pstImmMemCluster->apstFreeStack = ppTempMem;

        for(ulImmMemCnt = 0;
            ulImmMemCnt < pstImmMemCluster->usFreeCnt;
            ulImmMemCnt ++)
        {
            pstImmMem->usMagicNum   = IMM_MAGIC_NUM;
            pstImmMem->enPoolId     = ucPoolId;
            pstImmMem->ucClusterId  = ucClusterId;

            if ( IMM_MEM_POOL_ID_EXT == pstImmMem->enPoolId )
            {
                pstImmMem->pstMemBlk = VOS_NULL_PTR;
            }
            else
            {
                pstImmMem->pstMemBlk    = *ppucDataMemAddr; /* ����IMM_MEM_STRU�Ͷ�Ӧ���ݵĹ�ϵ */
            }

            /* ���������ڴ��������IMM_MEM_STRU�Ĺ�ϵ */
           *ppTempMem               = pstImmMem;

            pstImmMem++;
            ppTempMem++;

            *ppucDataMemAddr       += pstImmMemCluster->usLen;
        }

    }

    return IMM_SUCC;
} /* IMM_MemPoolInit */



unsigned int IMM_MemPoolCreate
(
    const IMM_MEM_POOL_CFG_INFO_STRU   *pstPoolCfg,
    unsigned char                     **ppucDataMemAddr

)
{
    IMM_MEM_POOL_STRU                  *pstImmMemPool;
    IMM_MEM_CLUSTER_CFG_INFO_STRU      *pstPoolClusterCfgTable;
    IMM_MEM_CLUSTER_CFG_INFO_STRU      *pstClusterCfgInfo;
    IMM_MEM_CLUSTER_STRU               *pstMemCluster;
    unsigned short                      usLastClusterMaxLen;
    unsigned short                      usDataLen;
    unsigned char                       ucPoolId;
    unsigned char                       ucClusterId;
    unsigned char                      *pucDataMemAddr;
    unsigned char                       ucClusterCnt = 0;


    if ( VOS_NULL_PTR == *ppucDataMemAddr )
    {
        /*lint -e718 -e746*/
        panic("IMM_MemPoolCreate Fail, input *ppucDataMemAddr is NULL PRT \n");
        /*lint +e718 +e746*/
        return  IMM_FAIL;
    }

    if ( IMM_MEM_POOL_ID_BUTT <= pstPoolCfg->enPoolId )
    {
        /*lint -e515 -e830*/
        panic("IMM_MemPoolCreate Fail, ulPoolId %d exceed the Ranger \n",
            pstPoolCfg->enPoolId);
        /*lint +e515 +e830*/
        return  IMM_FAIL;
    }


    pucDataMemAddr  = (unsigned char *)(*ppucDataMemAddr);

    ucPoolId        = pstPoolCfg->enPoolId;

    pstImmMemPool   = IMM_MEM_GET_POOL(ucPoolId);

    /* ����ӦID���ڴ���Ƿ��б��ظ����� */
    if ( IMM_TRUE == pstImmMemPool->ucUsedFlag )
    {
        /*lint -e515 -e830*/
        panic("IMM_MemPoolCreate Fail, ulPoolId %d is already used\r\n",
            ucPoolId);
        /*lint +e515 +e830*/
        return IMM_FAIL;
    }


    ucClusterCnt                    = pstPoolCfg->ucClusterCnt;
    pstPoolClusterCfgTable          = pstPoolCfg->pstClusterCfgInfo;

    /* ��ʼ���ڴ�ص�ͨ�ñ��� */
    pstImmMemPool->ucUsedFlag       = IMM_FALSE;
    pstImmMemPool->ucClusterCnt     = ucClusterCnt;
    pstImmMemPool->usImmMemTotalCnt = 0;

    /* ÿ��POOL�����һ��size�������ƫ�Ƶ����һ���������POOL�����size */
    pstClusterCfgInfo               = pstPoolClusterCfgTable + (ucClusterCnt - 1);
    pstImmMemPool->usMaxByteLen     = pstClusterCfgInfo->usSize;


    /* ���볤���������Գ���Ϊ�����±꣬������󳤶�Ҫ���������С1 */
    if (pstImmMemPool->usMaxByteLen > (IMM_MEM_BLK_MAX_BYTE_LEN - 1))
    {
        /*lint -e515 -e830*/
        panic("IMM_MemPoolCreate Fail, MaxByteLen:%d too big! \n",
            pstImmMemPool->usMaxByteLen);
        /*lint +e515 +e830*/
        return IMM_FAIL;
    }

    if (pstImmMemPool->ucClusterCnt > IMM_MEM_BLK_MAX_CLUSTER_NUM)
    {
        /*lint -e515 -e830*/
        panic("IMM_MemPoolCreate Fail, ClusterCnt:%d exceed! \n",
            pstImmMemPool->ucClusterCnt);
        /*lint -e515 -e830*/
        return IMM_FAIL;
    }

    memset(pstImmMemPool->aucLenIndexTable, 0, IMM_MEM_BLK_MAX_BYTE_LEN);

    memset(pstImmMemPool->astClusterTable, 0,
        sizeof(IMM_MEM_CLUSTER_STRU) * IMM_MEM_BLK_MAX_CLUSTER_NUM);

    usLastClusterMaxLen   = 1;

    for (ucClusterId = 0; ucClusterId < ucClusterCnt; ucClusterId++)
    {
        pstClusterCfgInfo               = pstPoolClusterCfgTable + ucClusterId;
        pstMemCluster                   = &(pstImmMemPool->astClusterTable[ucClusterId]);

        pstMemCluster->usTotalCnt       = pstClusterCfgInfo->usCnt;
        pstMemCluster->usFreeCnt        = pstClusterCfgInfo->usCnt;
        pstMemCluster->usLen            = pstClusterCfgInfo->usSize;

       *ppucDataMemAddr                += (pstClusterCfgInfo->usSize) * (pstClusterCfgInfo->usCnt);

        for(usDataLen = usLastClusterMaxLen;
            usDataLen <= pstClusterCfgInfo->usSize;
            usDataLen++)
        {
            pstImmMemPool->aucLenIndexTable[usDataLen]      = ucClusterId;
        }

        usLastClusterMaxLen                 = usDataLen;

        pstImmMemPool->usImmMemTotalCnt    += pstClusterCfgInfo->usCnt;
    }

    if( IMM_SUCC != IMM_MemPoolInit(ucPoolId, &pucDataMemAddr))
    {
        return IMM_FAIL;
    }

    pstImmMemPool->ucUsedFlag = IMM_TRUE;

    return IMM_SUCC;
} /* IMM_MemPoolCreate */

unsigned long IMM_MemGetBaseAddr(void)
{
    BSP_DDR_SECT_QUERY             stQuery;
    BSP_DDR_SECT_INFO              stInfo;
    unsigned long                  ulBaseAddr;

    stQuery.enSectType = BSP_DDR_SECT_TYPE_TTF;
    DRV_GET_FIX_DDR_ADDR(&stQuery, &stInfo);

    ulBaseAddr = stInfo.ulSectVirtAddr;

    return (IMM_MEM_POOL_BASE_ADDR(ulBaseAddr));
}


unsigned long IMM_MemBlkInit(void)
{
    unsigned int                        ulRet1;
    unsigned int                        ulRet2;
    unsigned char                      *pucBaseAddr;
    IMM_MEM_POOL_CFG_INFO_STRU          stSharePoolCfgInfo;
    IMM_MEM_POOL_CFG_INFO_STRU          stExtPoolCfgInfo;
    unsigned long                       ulBaseAddr;

    /*��ʼ������ֻ�ᱻskbuf_init ���� */
    if ( IMM_TRUE == g_ulImmMemInitFlag )
    {
        vos_printf( "IMM_MemBlkInit, Warning, Memory pools were already initialized!\n");

        return IMM_SUCC;
    }

    /* �����ڴ����Ϣ */
    memset(g_astImmMemPool, 0, sizeof(IMM_MEM_POOL_STRU)* IMM_MEM_POOL_ID_BUTT);
    memset(&g_stImmRegMntnFuc, 0, sizeof(IMM_MEM_REG_MNTN_FUNC_STRU));

    /* ��ʼ�� IMM MEM FREE ��ά�ɲ�ʵ�� */
    memset(&g_stImmMemFreeMntnEntity, 0, sizeof(IMM_MEM_FREE_MNTN_INFO_STRU));

    memset(&stSharePoolCfgInfo, 0, sizeof(IMM_MEM_POOL_CFG_INFO_STRU));
    memset(&stExtPoolCfgInfo, 0, sizeof(IMM_MEM_POOL_CFG_INFO_STRU));

    /* ���湲���ڴ�����ò��� */
    stSharePoolCfgInfo.pstClusterCfgInfo       = (IMM_MEM_CLUSTER_CFG_INFO_STRU *)g_astImmMemSharePoolClusterTableInfo;
    stSharePoolCfgInfo.ucClusterCnt            = IMM_MEM_SHARE_POOL_CLUSTER_CNT;
    stSharePoolCfgInfo.enPoolId                = IMM_MEM_POOL_ID_SHARE;

    /* �����ⲿ�ڴ�����ò��� */
    stExtPoolCfgInfo.pstClusterCfgInfo        = (IMM_MEM_CLUSTER_CFG_INFO_STRU *)g_astImmMemCtrlPoolClusterTableInfo;
    stExtPoolCfgInfo.ucClusterCnt             = IMM_MEM_CTRL_POOL_CLUSTER_CNT;
    stExtPoolCfgInfo.enPoolId                 = IMM_MEM_POOL_ID_EXT;

    ulBaseAddr = IMM_MemGetBaseAddr();

    /* �ڴ�����ַ������ʵ��ַת���ַ */
    pucBaseAddr = (unsigned char *)ulBaseAddr;

    /*����IMM_MEM�ڴ���ͷű����ά�ɲ���Ϣ�����������*/
    VOS_SpinLockInit(&g_stImmFreeMntnSpinLock);

    /*���������ڴ�ض�Ӧ��������*/
    VOS_SpinLockInit(&g_astImmSpinLock[IMM_MEM_POOL_ID_SHARE]);

    /* ���������ڴ�� */
    ulRet1 = IMM_MemPoolCreate(&stSharePoolCfgInfo, &pucBaseAddr);

    /*�����ⲿ�ڴ�ض�Ӧ��������*/
    VOS_SpinLockInit(&g_astImmSpinLock[IMM_MEM_POOL_ID_EXT]);

    /* �����ⲿ�ڴ�� */
    ulRet2 = IMM_MemPoolCreate(&stExtPoolCfgInfo, &pucBaseAddr);

    /* �����ѱ���ʼ���ı�־ */
    g_ulImmMemInitFlag = IMM_TRUE;

    if ( ( IMM_FAIL == ulRet1 ) || ( IMM_FAIL == ulRet2 ) )
    {
        /*lint -e515 -e830*/
        panic("Create IMM failed ulRet1 = %d, ulRet2 = %d ! \n", ulRet1, ulRet2);
        /*lint +e515 +e830*/
        return IMM_FAIL;
    }

    return IMM_SUCC;

} /* IMM_MemBlkInit */



unsigned long IMM_MemFreeMemCheck(unsigned short usFileId, unsigned short usLineNum, IMM_MEM_STRU **ppstImm, VOS_SPINLOCK *pstSpinLock, VOS_UINT32 ulFlags)
{
    if ( VOS_NULL_PTR == ppstImm )
    {
        vos_printf( "Error: IMM_MemFreeMemCheck Input pstMem is NULL! FileId=%d,LineNum=%d \n", usFileId, usLineNum);
        /*lint -e717*/
        IMM_MEM_FREE_SAVE_NULL_PTR_INFO(g_stImmMemFreeMntnEntity.astImmMemFreeNullPPtrInfo,usFileId,usLineNum,pstSpinLock,ulFlags);
        /*lint +e717*/
        return IMM_FAIL;
    }

    if ( VOS_NULL_PTR == *ppstImm )
    {
        vos_printf("Error: IMM_MemFreeMemCheck Input *pstMem is NULL! FileId=%d,LineNum=%d \n", usFileId, usLineNum);
        /*lint -e717*/
        IMM_MEM_FREE_SAVE_NULL_PTR_INFO(g_stImmMemFreeMntnEntity.astImmMemFreeNullPtrInfo,usFileId,usLineNum,pstSpinLock,ulFlags);
        /*lint +e717*/
        return IMM_FAIL;
    }

    if ( IMM_MAGIC_NUM != (*ppstImm)->usMagicNum)
    {
        vos_printf("IMM_MemFreeMemCheck, Magic Num %d is invalid! FileId=%d,LineNum=%d \n",
                    (int)(*ppstImm)->usMagicNum, usFileId, usLineNum);
        /*lint -e717*/
        IMM_MEM_FREE_SAVE_INVALID_MEM_INFO(g_stImmMemFreeMntnEntity.astImmMemFreeInvalidMemInfo,*ppstImm,IMM_INVALID_MEM_TYPE_MAGICNUM,(*ppstImm)->usMagicNum,usFileId,usLineNum,pstSpinLock,ulFlags);
        /*lint +e717*/
        return IMM_FAIL;
    }

    if( IMM_MEM_POOL_ID_BUTT <= (*ppstImm)->enPoolId )
    {
        vos_printf("IMM_MemFreeMemCheck, PoolId %d is invalid! FileId=%d,LineNum=%d \n",
                    (int)(*ppstImm)->enPoolId,usFileId, usLineNum );
        /*lint -e717*/
        IMM_MEM_FREE_SAVE_INVALID_MEM_INFO(g_stImmMemFreeMntnEntity.astImmMemFreeInvalidMemInfo,*ppstImm,IMM_INVALID_MEM_TYPE_POOLID,(*ppstImm)->enPoolId,usFileId,usLineNum,pstSpinLock,ulFlags);
        /*lint +e717*/
        return IMM_FAIL;
    }

    return IMM_SUCC;
}


#if (FEATURE_ON == FEATURE_IMM_MEM_DEBUG)

unsigned long IMM_MemGetSlice(void)
{
    if ( VOS_NULL_PTR == g_pstImmRegMntnFuc->pImmOmGetSliceFunc )
    {
        return 0;
    }

    return g_pstImmRegMntnFuc->pImmOmGetSliceFunc();
}/* IMM_MemGetSlice */



void IMM_MemSaveAllocDebugInfo
(
    IMM_MEM_STRU *pstImmMem,
    unsigned short usFileID,
    unsigned short usLineNum
)
{
    IMM_BLK_MEM_DEBUG_STRU             *pstDbgInfo  =  &pstImmMem->stDbgInfo;


    IMM_DEBUG_TRACE_FUNC_ENTER();

    pstDbgInfo->enMemStateFlag  = MEM_BLK_STATE_ALLOC;
    pstDbgInfo->usAllocFileID   = usFileID;
    pstDbgInfo->usAllocLineNum  = usLineNum;
    pstDbgInfo->ulAllocTick     = IMM_MemGetSlice();
    pstDbgInfo->usTraceFileID   = usFileID;
    pstDbgInfo->usTraceLineNum  = usLineNum;

    IMM_DEBUG_TRACE_FUNC_LEAVE();

    return;
}/* IMM_MemSaveAllocDebugInfo */



unsigned char IMM_MemSaveFreeDebugInfo(unsigned short usFileId, unsigned short usLineNum, IMM_MEM_STRU *pstImmMem, VOS_SPINLOCK *pstSpinLock, VOS_UINT32 ulFlags)
{
    unsigned long                ulMemAddr;
    IMM_BLK_MEM_DEBUG_STRU      *pstImmMemDebugInfo = &pstImmMem->stDbgInfo;


    IMM_DEBUG_TRACE_FUNC_ENTER();

    ulMemAddr = (unsigned long)pstImmMem;

    /*pstImmMem ��ַ��Χ���*/
    if (( (unsigned long)g_paulImmMemCtrlMemSpace > ulMemAddr )
        ||(((unsigned long)g_paulImmMemCtrlMemSpace + (*g_pulImmMemCtrlMemSuffix)) < ulMemAddr))
    {
        /*lint -e717*/
        IMM_MEM_FREE_SAVE_INVALID_MEM_INFO(g_stImmMemFreeMntnEntity.astImmMemFreeInvalidMemInfo, pstImmMem,IMM_INVALID_MEM_TYPE_CTRLADDR, 0, usFileId, usLineNum,pstSpinLock,ulFlags);
        /*lint +e717*/
        vos_printf( "Error: IMM_MemFreeSaveDebugInfo, Mem addr %d is invalid! \n", (int)pstImmMem);

        return IMM_FAIL;
    }

    /* �ж��ڴ�ָ��״̬�Ƿ���ȷ */
    if ( MEM_BLK_STATE_ALLOC != pstImmMemDebugInfo->enMemStateFlag )
    {
        /*lint -e717*/
        IMM_MEM_FREE_SAVE_INVALID_MEM_INFO(g_stImmMemFreeMntnEntity.astImmMemFreeInvalidMemInfo, pstImmMem,IMM_INVALID_MEM_TYPE_STUTAS, (unsigned short)pstImmMemDebugInfo->enMemStateFlag, usFileId, usLineNum,pstSpinLock,ulFlags);
        /*lint +e717*/
        vos_printf("Error: IMM_MemFreeSaveDebugInfo, free a free status block is not allowed \n");

        return IMM_FAIL;
    }

    pstImmMemDebugInfo->enMemStateFlag   = MEM_BLK_STATE_FREE;
    pstImmMemDebugInfo->ulAllocTick      = IMM_MemGetSlice();
    pstImmMemDebugInfo->usAllocFileID    = 0;

    IMM_DEBUG_TRACE_FUNC_LEAVE();

    return IMM_SUCC;

}/* IMM_MemFreeSaveDebugInfo */
#endif



IMM_MEM_POOL_STRU *IMM_MemPoolGet(unsigned char ucPoolId)
{
    if ( IMM_MEM_POOL_ID_BUTT > ucPoolId )
    {
        return &g_astImmMemPool[ucPoolId];
    }
    else
    {
        return VOS_NULL_PTR;
    }

} /* IMM_MemPoolGet */



unsigned long IMM_ZcGetLocalFreeMemCnt(void)
{
    IMM_DEBUG_TRACE_FUNC_ENTER();
    IMM_DEBUG_TRACE_FUNC_LEAVE();

    return *g_pACpuFreeMemBlkCnt;
} /* IMM_ZcGetLocalFreeMemCnt */



void IMM_ZcSetLocalFreeMemCnt(unsigned long ulMemValue)
{
    IMM_DEBUG_TRACE_FUNC_ENTER();
    IMM_DEBUG_TRACE_FUNC_LEAVE();

    *g_pACpuFreeMemBlkCnt = ulMemValue;
    return;
}/* IMM_ZcSetLocalFreeMemCnt */



IMM_MEM_STRU *IMM_MemAlloc_Debug(unsigned short usFileID, unsigned short usLineNum,
                        unsigned char ucPoolId, unsigned int ulLen)
{
    IMM_MEM_POOL_STRU              *pstImmMemPool;
    IMM_MEM_CLUSTER_STRU           *pstImmMemCluster;
    IMM_MEM_STRU                   *pMem;
    unsigned long                   ulMaxClusterFreeCnt;
    unsigned char                   ucClusterId;
    unsigned char                   ucMostFitLev;
    unsigned long                   ulSaveFlags  = 0;
    VOS_SPINLOCK                   *pstImmSpinLock;


    IMM_DEBUG_TRACE_FUNC_ENTER();

    if (IMM_MEM_POOL_ID_EXT <= ucPoolId )   /*���ΪEXTֱ���˳�*/
    {
        vos_printf("IMM_MemBlkAlloc_Debug,Poolid %d is invalid,FileId=%d,LineNum=%d!\n", ucPoolId,usFileID,usLineNum);
        return VOS_NULL_PTR;
    }

     /* ��ȡ�ڴ�� */
    pstImmMemPool = IMM_MEM_GET_POOL(ucPoolId);

    /* ��ȡ������ */
    pstImmSpinLock = &g_astImmSpinLock[ucPoolId];

    /* ����ڴ���Ƿ��Ѿ���ʼ�� */
    if ( IMM_TRUE != pstImmMemPool->ucUsedFlag )
    {
        vos_printf("IMM_MemBlkAlloc_Debug,Pool %d is not used,FileId=%d,LineNum=%d!\n", ucPoolId,usFileID,usLineNum);
        return VOS_NULL_PTR;
    }


    if ( (0 == ulLen ) || (ulLen > pstImmMemPool->usMaxByteLen) )
    {
        vos_printf("IMM_MemBlkAlloc_Debug,usLen %d exceed the Pool %d ranger,FileId=%d,LineNum=%d!\n", (int)ulLen, ucPoolId,usFileID,usLineNum);
        return VOS_NULL_PTR;
    }

    /* ���ڴ�صĶ������Ѱ�Һ��ʵ�IMM_MEM */
    ucMostFitLev = IMM_GET_LEN_INDEX(pstImmMemPool, ulLen);

    for(ucClusterId = ucMostFitLev;
        ucClusterId < pstImmMemPool->ucClusterCnt;
         ++ucClusterId )
    {
        pstImmMemCluster  = &(pstImmMemPool->astClusterTable[ucClusterId]);

        VOS_SpinLockIntLock(pstImmSpinLock, ulSaveFlags);

        if (0 != pstImmMemCluster->usFreeCnt)
        {
            /* ��ȡһ��û��ʹ�õ�IMM_MEM_ST��� */
            pMem    = pstImmMemCluster->apstFreeStack[--pstImmMemCluster->usFreeCnt];
            ++pstImmMemPool->usImmMemUsedCnt;
            ulMaxClusterFreeCnt = pstImmMemPool->astClusterTable[pstImmMemPool->ucClusterCnt - 1].usFreeCnt;

            IMM_ZcSetLocalFreeMemCnt(ulMaxClusterFreeCnt);

            VOS_SpinUnlockIntUnlock(pstImmSpinLock ,ulSaveFlags);

            /* ������ģ���ϱ��ڴ������¼� */
            if (VOS_NULL_PTR != pstImmMemPool->pMemAllocEvent)
            {
                pstImmMemPool->pMemAllocEvent( ulMaxClusterFreeCnt );
            }

#if (FEATURE_ON == FEATURE_IMM_MEM_DEBUG)
            IMM_MemSaveAllocDebugInfo( pMem, usFileID, usLineNum );
#endif
            IMM_DEBUG_TRACE_FUNC_LEAVE();

            return pMem;
        }

        VOS_SpinUnlockIntUnlock(pstImmSpinLock ,ulSaveFlags);
    }

    VOS_SpinLockIntLock(pstImmSpinLock, ulSaveFlags);

    (*g_apusImmAllocFailCnt[ucPoolId])++;

    if ( *g_apusImmAllocFailCnt[ucPoolId] < g_usImmAllocFailCntThreshold )
    {
        VOS_SpinUnlockIntUnlock(pstImmSpinLock, ulSaveFlags);
        return VOS_NULL_PTR;
    }

    *g_apusImmAllocFailCnt[ucPoolId] = 0;
    (*g_apusImmExcThresholdCnt[ucPoolId])++;

    VOS_SpinUnlockIntUnlock(pstImmSpinLock, ulSaveFlags);

    /* ��SDT�ϱ��ڴ�����ʧ���¼� */
    if ( VOS_NULL_PTR != g_pstImmRegMntnFuc->pImmMemEventRptFunc)
    {
        g_pstImmRegMntnFuc->pImmMemEventRptFunc(ucPoolId, IMM_MEM_TRIG_TYPE_ALLOC_FAIL);
    }


    return VOS_NULL_PTR;
} /* IMM_MemAlloc_Debug */



void IMM_MemFree_Debug(unsigned short usFileId, unsigned short usLineNum, IMM_MEM_STRU **ppstMem)
{
    IMM_MEM_POOL_STRU                  *pstImmMemPool;
    IMM_MEM_CLUSTER_STRU               *pstImmMemCluster;
    IMM_MEM_STRU                       *pstImmMem;
    unsigned long                       ulMaxClusterFreeCnt;
    unsigned long                       ulSaveFlags  = 0;
    VOS_SPINLOCK                       *pstImmSpinLock;


    IMM_DEBUG_TRACE_FUNC_ENTER();

    /* ���ͷ��ڴ�Ϸ��Լ�� */
    if ( IMM_SUCC != IMM_MemFreeMemCheck(usFileId, usLineNum, ppstMem, &g_stImmFreeMntnSpinLock, ulSaveFlags) )
    {
        vos_printf( "Error: IMM_MemFree_Debug input ppstMem is invalid! FileId=%d,LineNum=%d \n", usFileId, usLineNum);
        return;
    }

    pstImmMem       = *ppstMem;

    pstImmMemPool   = IMM_MEM_GET_POOL(pstImmMem->enPoolId);

    /* ����Ӧ���ڴ��Ƿ�ʹ�� */
    if (IMM_TRUE != pstImmMemPool->ucUsedFlag)
    {
        vos_printf("Error: IMM_MemFree_Debug, Pool %d is not used! \n",
                pstImmMem->enPoolId);
        return ;
    }

#if (FEATURE_ON == FEATURE_IMM_MEM_DEBUG)
    if ( IMM_SUCC != IMM_MemSaveFreeDebugInfo(usFileId, usLineNum, pstImmMem, &g_stImmFreeMntnSpinLock, ulSaveFlags) )
    {
        vos_printf("Error: IMM_MemFree_Debug, free IMM MEM fail! FileId=%d, LineNum=%d \n", usFileId, usLineNum);
        return;
    }
#endif

    /* �ⲿ�ڴ�أ���Ҫ�ͷ��ⲿ�ڴ�� */
    if ( IMM_MEM_POOL_ID_EXT == pstImmMem->enPoolId )
    {
        vos_printf("Error: IMM_MemFree_Debug, Pool ID is IMM_MEM_POOL_ID_EXT! \n");
        return ;
    }

    /* ��ȡ�ڴ�����ڵĵ�λ */
    pstImmMemCluster = &(pstImmMemPool->astClusterTable[pstImmMem->ucClusterId]);

    /* ��ȡ������ */
    pstImmSpinLock  = &g_astImmSpinLock[pstImmMem->enPoolId];

    VOS_SpinLockIntLock(pstImmSpinLock, ulSaveFlags);

    if (pstImmMemCluster->usFreeCnt >= pstImmMemCluster->usTotalCnt)
    {
        VOS_SpinUnlockIntUnlock(pstImmSpinLock ,ulSaveFlags);
        vos_printf("Error: IMM_MemFree_Debug, free cnt error:FreeCnt %d, TotalCnt %d ! \n",
                pstImmMemCluster->usFreeCnt, pstImmMemCluster->usTotalCnt);

        return ;
    }

    /* ���ڴ��ҽӻ��ڴ�� */
    pstImmMemCluster->apstFreeStack[pstImmMemCluster->usFreeCnt] = pstImmMem;
    ++pstImmMemCluster->usFreeCnt;
    --pstImmMemPool->usImmMemUsedCnt;
    /* �����ڴ�����λʣ���ڴ���� */
    ulMaxClusterFreeCnt = pstImmMemPool->astClusterTable[pstImmMemPool->ucClusterCnt - 1].usFreeCnt;

    IMM_ZcSetLocalFreeMemCnt(ulMaxClusterFreeCnt);

    VOS_SpinUnlockIntUnlock(pstImmSpinLock ,ulSaveFlags);


    /* ������ģ���ϱ��ڴ��ͷ��¼� */
    if ( VOS_NULL_PTR != pstImmMemPool->pMemFreeEvent )
    {
        pstImmMemPool->pMemFreeEvent(ulMaxClusterFreeCnt );
    }

    *ppstMem = VOS_NULL_PTR;

    IMM_DEBUG_TRACE_FUNC_LEAVE();

    return ;
} /* IMM_MemFree_Debug */



unsigned long IMM_MemRegExtFreeCallBack
(
    IMM_MEM_EXT_FREE_CALLBACK           pMemExtFreeFunc
)
{
    IMM_MEM_POOL_STRU * const           pstIMMMemPool = g_pstImmExtMemPool;


    if ( VOS_NULL_PTR == pMemExtFreeFunc )
    {
        return IMM_FAIL;
    }

    pstIMMMemPool->pMemExtFreeFunc = pMemExtFreeFunc;

    return IMM_SUCC;
} /* IMM_MemRegExtFreeCallBack */



void IMM_MemRegMntnFuncCallBack
(
    IMM_OM_GET_SLICE_CALLBACK               pImmOmGetSliceFunc,
    IMM_MEM_USED_INFO_EVENT_RPT_CALLBACK    pImmMemEventRptFunc
)
{
    /* ������飬pImmOmGetSliceFunc �����ڷ�DEBUGģʽ��Ϊ�� */
    if ( VOS_NULL_PTR == pImmMemEventRptFunc )
    {
        vos_printf("IMM_MemRegPsFuncCallBack fail: invalid input paras! \n");
        return;
    }

    g_pstImmRegMntnFuc->pImmOmGetSliceFunc    = pImmOmGetSliceFunc;
    g_pstImmRegMntnFuc->pImmMemEventRptFunc   = pImmMemEventRptFunc;

    return;
}



unsigned long IMM_MemRegEventCallBack
(
    IMM_MEM_POOL_ID_ENUM_UINT8          enPoolId,
    IMM_MEM_EVENT_CALLBACK              pMemAllocEvent,
    IMM_MEM_EVENT_CALLBACK              pMemFreeEvent
)
{
    IMM_MEM_POOL_STRU              *pstImmMemPool;
    unsigned long                   ulMaxClusterFreeCnt;

    pstImmMemPool   = IMM_MemPoolGet(enPoolId);

    if ( VOS_NULL_PTR == pstImmMemPool )
    {
        return IMM_FAIL;
    }

    pstImmMemPool->pMemAllocEvent = pMemAllocEvent;
    pstImmMemPool->pMemFreeEvent  = pMemFreeEvent;

    /* ��ȡ���λ�ڴ��ʣ����� */
    ulMaxClusterFreeCnt = pstImmMemPool->astClusterTable[pstImmMemPool->ucClusterCnt - 1].usFreeCnt;
    IMM_ZcSetLocalFreeMemCnt(ulMaxClusterFreeCnt);

    return IMM_SUCC;
} /* IMM_MemRegEventCallBack */



void IMM_MemFreeShowMntnInfo( void )
{
    IMM_MEM_FREE_INVALIED_MEM_INFO_STRU    *pstInvalidMemInfo   = &g_stImmMemFreeMntnEntity.astImmMemFreeInvalidMemInfo;
    IMM_MEM_FREE_NULL_PTR_INFO_STRU        *pstNullPtrInfo      = &g_stImmMemFreeMntnEntity.astImmMemFreeNullPtrInfo;
    IMM_MEM_FREE_NULL_PTR_INFO_STRU        *pstNullPPtrInfo     = &g_stImmMemFreeMntnEntity.astImmMemFreeNullPPtrInfo;


    vos_printf( "IMM MEM FREE ��ά�ɲ���Ϣ :\n");
    vos_printf( "==========================================\n");
    vos_printf( "IMM MEM FREE �Ƿ��ڴ���Ϣ :\n");
    vos_printf( "IMM MEM FREE �յ��ķǷ��ڴ����       : %u \n", (unsigned int)pstInvalidMemInfo->ulInvalidImmMemCnt);
    vos_printf( "IMM MEM FREE �Ƿ�IMM MEM �ڴ��ַ     : 0x%u \n", (unsigned int)pstInvalidMemInfo->ulInvalidImmMemAddr);
    vos_printf( "IMM MEM FREE �Ƿ�IMM MEM �ڴ��ļ�ID   : %d \n", pstInvalidMemInfo->usImmMemFreeFileId);
    vos_printf( "IMM MEM FREE �Ƿ�IMM MEM �ڴ��к���Ϣ : %d \n", pstInvalidMemInfo->usImmMemFreeLineNum);
    vos_printf( "IMM MEM FREE �Ƿ�IMM MEM �ڴ�����     : %d \n", pstInvalidMemInfo->ucImmMemInvalidType);
    vos_printf( "IMM MEM FREE �Ƿ�IMM MEM �ڴ�ֵ       : %d \n", pstInvalidMemInfo->usImmMemInvalidValue);
    vos_printf( "IMM MEM �ڴ����ͷ��ʼ��ַ            : 0x%u ~ 0x%u \n\n", (unsigned int)g_paulImmMemCtrlMemSpace,((unsigned int)((unsigned int)g_paulImmMemCtrlMemSpace + (*g_pulImmMemCtrlMemSuffix))) );


    vos_printf( "==========================================\n");
    vos_printf( "IMM MEM FREE ��ָ����Ϣ :\n");
    vos_printf( "IMM MEM FREE һ��ָ��Ϊ�յĴ���    : %u \n", (unsigned int)pstNullPtrInfo->ulImmMemFreeNullPtrCnt);
    vos_printf( "IMM MEM FREE ����ָ���ļ�ID        : %d \n", pstNullPtrInfo->usImmMemFreeFileId);
    vos_printf( "IMM MEM FREE ����ָ���ڴ��к���Ϣ  : %d \n", pstNullPtrInfo->usImmMemFreeLineNum);

    vos_printf( "IMM MEM FREE ����ָ��Ϊ�յĴ���    : %u \n", (unsigned int)pstNullPPtrInfo->ulImmMemFreeNullPtrCnt);
    vos_printf( "IMM MEM FREE ����ָ���ڴ��ļ�ID    : %d \n", pstNullPPtrInfo->usImmMemFreeFileId);
    vos_printf( "IMM MEM FREE ����ָ���ڴ��к���Ϣ  : %d \n", pstNullPPtrInfo->usImmMemFreeLineNum);

    vos_printf( "IMM MEM Pool Status: IMM_MEM_POOL_ID_DL_SHARE %d\n", g_astImmMemPool[IMM_MEM_POOL_ID_SHARE].ucUsedFlag);
    vos_printf( "                     IMM_MEM_POOL_ID_EXT      %d\n", g_astImmMemPool[IMM_MEM_POOL_ID_EXT].ucUsedFlag);

    vos_printf( "IMM_MEM_POOL_ID_EXT �ͷź���      : 0x%u\n", (unsigned int)g_astImmMemPool[IMM_MEM_POOL_ID_EXT].pMemExtFreeFunc);
    vos_printf( "IMM Ext MEM FREE ʧ�ܴ���         : %u \n", (unsigned int)g_stImmMemFreeMntnEntity.ulImmMemExtFreeFailCnt);

}

#endif

/******************************************************************************/
/*******************************V9R1�汾***************************************/
/******************************************************************************/

unsigned long IMM_MemRegEventCallBack
(
    IMM_MEM_POOL_ID_ENUM_UINT8          enPoolId,
    IMM_MEM_EVENT_CALLBACK              pMemAllocEvent,
    IMM_MEM_EVENT_CALLBACK              pMemFreeEvent
)
{
    return IMM_SUCC;
} /* IMM_MemRegEventCallBack */



unsigned long IMM_ZcGetLocalFreeMemCnt(void)
{
    return  0;
} /* IMM_ZcGetLocalFreeMemCnt */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

