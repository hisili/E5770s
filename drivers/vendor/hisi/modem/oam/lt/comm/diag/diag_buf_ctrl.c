
/*lint --e{717}*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
/*lint -save -e537*/
#include  "diag_buf_ctrl.h"
#include  "diag_common.h"
#include  "msp_errno.h"
#include  "diag_debug.h"
#include  "SCMProc.h"
#include  "diag_mem.h"
#include  "SOCPInterface.h"
#include  <diag_debug.h>
/*lint -restore*/

/*lint -save -e767 ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_BUF_CTRL_C
/*lint -restore +e767*/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
DIAG_BUF_CTRL_STRU                        g_stDiagBufCtrl[DIAG_CODER_SRC_TYPE_BUTT] = {{0}};
VOS_SEM g_DiagLogSem =(VOS_SEM)0;

DIAG_TO_HSO_FAIL_STRU g_stDiagToHsoErrRecord = {0};
VOS_UINT32 g_LockBufTimes = 0;
VOS_UINT32 g_UnLockBufTimes = 0;
VOS_INT32 g_UnNeedMaxBuf[2] = {0};
VOS_UINT8* g_DiagMemVirt =0;

VOS_VOID diag_InitSocpChan(VOS_VOID);

/*****************************************************************************
  3 Function
*****************************************************************************/

VOS_VOID diag_GetBufLen(VOS_UINT32 ulLen[DIAG_CODER_SRC_TYPE_BUTT]);
VOS_VOID diag_GetBufLen(VOS_UINT32 ulLen[DIAG_CODER_SRC_TYPE_BUTT])
{
    /*lint -save -e40*/
	ulLen[DIAG_CODER_SRC_TYPE_CNF] = DIAG_CODER_SRC_CNF_BUFFER_SIZE;
	ulLen[DIAG_CODER_SRC_TYPE_IND] = DIAG_CODER_SRC_IND_BUFFER_SIZE;

#if (VOS_LINUX== VOS_OS_VER)
	g_stDiagBufCtrl[DIAG_CODER_SRC_TYPE_CNF].pucRealBuf = (VOS_UINT8*)DIAG_CODER_SRC_CNF_BUF_A_ADDR;
	g_stDiagBufCtrl[DIAG_CODER_SRC_TYPE_IND].pucRealBuf = (VOS_UINT8*)DIAG_CODER_SRC_IND_BUF_A_ADDR;
#else
	g_stDiagBufCtrl[DIAG_CODER_SRC_TYPE_CNF].pucRealBuf = (VOS_UINT8*)DIAG_CODER_SRC_CNF_BUF_C_ADDR;
	g_stDiagBufCtrl[DIAG_CODER_SRC_TYPE_IND].pucRealBuf = (VOS_UINT8*)DIAG_CODER_SRC_IND_BUF_C_ADDR;
#endif
    /*lint -restore*/
}

VOS_UINT32 diag_BufCtrlGlobalInit(VOS_VOID)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 i = 0;
	VOS_INT32 aulLen[DIAG_CODER_SRC_TYPE_BUTT] = {0,};

    /* ���� ����LOG�ϱ����ź���,�ڶ�������1��ʾһ��ʼ��take���ź���������ȴ���0��ʾһ��ʼtake����*/
    ret = VOS_SmBCreate(NULL, 1, VOS_SEMA4_FIFO,&g_DiagLogSem);
    if (ERR_MSP_SUCCESS != ret)
    {
    	diag_printf("[%s]:VOS_SmBCreate fail!\n",__FUNCTION__);
        return ret;
    }
    /*lint -save -e40 -e539*/
#ifdef DIAG_MEMMAP
	g_DiagMemVirt = (VOS_UINT8*)MSP_NOCACHEMAP(DIAG_MEM_ADDR_BASE,DIAG_MEM_TOTAL_SIZE);
#else
	g_DiagMemVirt = (VOS_UINT8*)SOCP_GLOBAL_MEM_ADDR_VIRT;
#endif
    /*lint -restore*/

    diag_GetBufLen((VOS_UINT32 *)aulLen);

    /* ����log���ͻ����� */
    for(i = 0 ; i< DIAG_CODER_SRC_TYPE_BUTT; i++)
    {
        if (VOS_OK != diag_CreateLogBuf(&g_stDiagBufCtrl[i], aulLen[i]))
        {
            diag_printf("diag_BufCtrlGlobalInit:diag_CreateLogBuffer Failed!\n");
            return ERR_MSP_FAILURE;
        }
    }

#if ((VOS_OS_VER == VOS_VXWORKS) || (VOS_OS_VER == VOS_RTOSCK))
    /*lint -save -e539*/
	diag_InitSocpChan();
    /*lint -restore */
#endif
    return ret;
}


VOS_VOID diag_LockCoderSrcBuf(VOS_VOID)
{
    (VOS_VOID)VOS_SmP(g_DiagLogSem,0);

    g_LockBufTimes++;
}


VOS_VOID diag_UnLockCoderSrcBuf(VOS_VOID)
{

    (VOS_VOID)VOS_SmV(g_DiagLogSem);
    g_UnLockBufTimes++;
}


VOS_UINT8* diag_BuffPhyToVirt(VOS_UINT8 *pucCurPhyAddr, VOS_UINT8 *pucPhyStart, VOS_UINT8 *pucVirtStart, VOS_UINT32 ulBufLen)
{
#if (VOS_LINUX == VOS_OS_VER)
	if((pucCurPhyAddr < pucPhyStart) /*|| (pucCurPhyAddr >= (pucPhyStart+ulBufLen))*/)
	{
		vos_printf("\r\n diag_BuffPhyToVirt: The PHY Addr 0x%x, pucPhyStart: 0x%x, pucVirtStart: 0x%x, ulBufLen: 0x%x.\r\n",
					pucCurPhyAddr,
					pucPhyStart,
					pucVirtStart,
					ulBufLen);

		return VOS_NULL;
	}

	return ((pucCurPhyAddr - pucPhyStart) + pucVirtStart);
#else
    return (pucCurPhyAddr);
#endif
}


VOS_UINT8* diag_BuffVirtToPhy(VOS_UINT8 *pucCurVirtAddr, VOS_UINT8 *pucVirtStart, VOS_UINT8 *pucPhyStart, VOS_UINT32 ulBufLen)
{
#if (VOS_LINUX == VOS_OS_VER)
	if((pucCurVirtAddr < pucVirtStart) /*|| (pucCurVirtAddr >= (pucVirtStart+ulBufLen))*/)
	{
		vos_printf("\r\n diag_BuffVirtToPhy: The VIRT Addr 0x%x, pucPhyStart: 0x%x, pucVirtStart: 0x%x, ulBufLen: 0x%x.\r\n",
					pucCurVirtAddr,
					pucPhyStart,
					pucVirtStart,
					ulBufLen);

		return VOS_NULL;
	}

	return ((pucCurVirtAddr - pucVirtStart) + pucPhyStart);
#else
    return (pucCurVirtAddr);
#endif
}


VOS_UINT32 diag_CreateLogBuf(DIAG_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lBufSize)
{
    /* ������� �ⲿ��֤�˲�Ϊ��*/

    pstBufCtrl->lAlloc   = 0;
    pstBufCtrl->lRelease = 0;
    pstBufCtrl->lPadding = 0;
    pstBufCtrl->lBufSize = lBufSize;

    /*����uncache�Ķ�̬�ڴ���*/
    /*lint -save -e40*/
    pstBufCtrl->pucBuf = diag_BuffPhyToVirt(pstBufCtrl->pucRealBuf,(VOS_UINT8*)DIAG_MEM_ADDR_BASE,(VOS_UINT8*)g_DiagMemVirt,(VOS_UINT32)(pstBufCtrl->lBufSize));
    /*lint -restore*/
    /* �����ڴ�ʧ�� */
    if (VOS_NULL_PTR == pstBufCtrl->pucBuf)
    {
        g_stDiagToHsoErrRecord.usNoMemErr++;
        return ERR_MSP_MALLOC_FAILUE;
    }

    diag_printf("diag_CreateLogBuf: real addr=0x%p, virt addr==0x%p\n", pstBufCtrl->pucRealBuf, pstBufCtrl->pucBuf);

    return ERR_MSP_SUCCESS;
}


VOS_UINT8* diag_AllocLogMem(DIAG_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lLen)
{
    VOS_INT32                           lFreeSize;
    VOS_UINT8                          *pucAddr;
    VOS_INT32                           lTmpAlloc;
    VOS_INT32                           lTmpPadding;

    /* ���������� */
    if ((lLen >= pstBufCtrl->lBufSize)|| (0 == lLen))
    {
        diag_printf("diag_AllocLogMem:��β���!,lLen=%d\n",lLen);
        return VOS_NULL_PTR;
    }

    lTmpAlloc       = pstBufCtrl->lAlloc;
    lTmpPadding     = pstBufCtrl->lPadding;

    /* û�лؾ� */
    if (pstBufCtrl->lAlloc >= pstBufCtrl->lRelease)
    {
        /* ��ȡʣ���ڴ��С ����������buffer�պ�������Ҫ-1*/
        if (0 == pstBufCtrl->lRelease)
        {
            lFreeSize = (pstBufCtrl->lBufSize - pstBufCtrl->lAlloc) - 1;
        }
		 /* ��ȡʣ���ڴ��С ����������buffer�պ���������releaseǰ���пռ䣬��дָ�벻����ȣ�����Ҫ-1*/
        else
        {
            lFreeSize = pstBufCtrl->lBufSize - pstBufCtrl->lAlloc;
        }

        /* �����û������ڴ��С�򷵻� */
        if (lFreeSize >= lLen)
        {
            pucAddr = pstBufCtrl->pucBuf + pstBufCtrl->lAlloc;
            pstBufCtrl->lAlloc += lLen;

            return pucAddr;
        }

        lTmpPadding  = lFreeSize;
        lTmpAlloc    = 0;
    }

    /* �ؾ���ȡʣ���ڴ��С ,��������buffer�պ���*/
    lFreeSize = (pstBufCtrl->lRelease - lTmpAlloc)-1;

    if (lFreeSize >= lLen)
    {
        pucAddr = pstBufCtrl->pucBuf + lTmpAlloc;

        pstBufCtrl->lAlloc    = lTmpAlloc + lLen;
        pstBufCtrl->lPadding  = lTmpPadding;

        return pucAddr;
    }

    /* �������ʧ�ܣ����ؿ�ָ�� */
    //diag_printf("diag_AllocLogMem:���ô�С����!\n");
    return VOS_NULL_PTR;
}


VOS_UINT32 diag_ReleaseLogMem(DIAG_BUF_CTRL_STRU *pstBufCtrl,VOS_UINT8 *pAddr, VOS_INT32 lLen)
{
    VOS_INT32                           lUsedSize;
    VOS_INT32                           lTmpRls;

    /* �����ǰ�����ж�������,��λϵͳ,��Ͻӿڲ��������ж���ʹ��*/
    if(VOS_FALSE != VOS_CheckInterrupt())
    {
        DRV_SYSTEM_ERROR(DIAG_CALLED_IN_IRQ, MSP_FILE_ID_DIAG_BUF_CTRL_C, __LINE__, VOS_NULL, 0);/*lint !e569*/
    }
    /* ���������� */
    if ((VOS_NULL_PTR == pstBufCtrl) || (lLen >= pstBufCtrl->lBufSize))
    {
        diag_printf("diag_ReleaseLogMem:��β���,lLen=%d!\n",lLen);
        return ERR_MSP_FAILURE;
    }

    /* �ͷ��ڴ��ַ���м�� */
    if ((pAddr != (pstBufCtrl->pucBuf + pstBufCtrl->lRelease))
        && (pAddr != pstBufCtrl->pucBuf))
    {
        diag_printf("diag_ReleaseLogMem:���ͷŵ�ַ����!pAddr=%p,pstBufCtrl->pucBuf=%p,pstBufCtrl->lRelease=0x%x\n",
                    pAddr,pstBufCtrl->pucBuf,pstBufCtrl->lRelease);
        /*DRV_SYSTEM_ERROR(DIAG_REALSE_POINTER_ERROR, MSP_FILE_ID_DIAG_BUF_CTRL_C, __LINE__, VOS_NULL, 0);*//*lint !e569*/
    }

    /* δ�ؾ� */
    if (pstBufCtrl->lAlloc >= pstBufCtrl->lRelease)
    {
        lUsedSize = pstBufCtrl->lAlloc - pstBufCtrl->lRelease;

        /* ���ȴ��� */
        if (lUsedSize < lLen)
        {
            diag_printf("diag_ReleaseLogMem:ʹ�ó���С�ڴ��ͷų���!lAlloc=0x%x,lRelease=0x%x,lLen=%d!\n",
                        pstBufCtrl->lAlloc,pstBufCtrl->lRelease,lLen);
            return ERR_MSP_FAILURE;
        }

        pstBufCtrl->lRelease = pAddr + lLen - pstBufCtrl->pucBuf;

        return ERR_MSP_SUCCESS;
    }

    if ((pAddr - pstBufCtrl->pucBuf + lLen) > pstBufCtrl->lBufSize)
    {
        lTmpRls = ((pAddr - pstBufCtrl->pucBuf + lLen) + pstBufCtrl->lPadding) % pstBufCtrl->lBufSize;
    }
    else
    {
        lTmpRls = (pAddr - pstBufCtrl->pucBuf + lLen) % pstBufCtrl->lBufSize;
    }

    /* ����ulLen����ȷ */
    if ((lTmpRls > pstBufCtrl->lAlloc) && (lTmpRls < pstBufCtrl->lRelease))
    {
        diag_printf("diag_ReleaseLogMem:�лؾ���������ͷŵ�ַ����!\n");
        return ERR_MSP_FAILURE;
    }

    /* ��������ؾ���Paddingֵ��0 */
    if (lTmpRls <= pstBufCtrl->lAlloc)
    {
        pstBufCtrl->lPadding = 0;
    }

    pstBufCtrl->lRelease = lTmpRls;

    return ERR_MSP_SUCCESS;
}


VOS_UINT32 diag_GetBufIndex(SOCP_CODER_SRC_ENUM_U32 ulChanID)
{
    VOS_UINT32 ulIndex = 0;
    if( SOCP_CODER_SRC_LOM_CNF1 ==  ulChanID)
    {
        ulIndex = DIAG_CODER_SRC_TYPE_CNF;
    }
    else if( SOCP_CODER_SRC_LOM_IND1 ==  ulChanID)
    {
        ulIndex = DIAG_CODER_SRC_TYPE_IND;
    }
    else if( SOCP_CODER_SRC_LOM_IND2 ==  ulChanID)
    {
        ulIndex = DIAG_CODER_SRC_TYPE_CNF;
    }
    else if( SOCP_CODER_SRC_LOM_IND3 ==  ulChanID)
    {
        ulIndex = DIAG_CODER_SRC_TYPE_IND;
    }
    else
    {
        ulIndex = DIAG_CODER_SRC_TYPE_CNF;
    }
    return ulIndex;
}


VOS_UINT32 diag_ReleaseLogBuf(SOCP_CODER_SRC_ENUM_U32 ulSrcChanID)
{
    VOS_UINT32 ulDataLen = 0;
    VOS_UINT_PTR ulDataAddr = 0;
    VOS_UINT32 ulIndex = 0;
    VOS_UINT8  *pucVirtAddr =NULL;

    /* ��������ѷ���RD */
    if (VOS_OK != SCM_RlsSrcRDAll(ulSrcChanID, &ulDataAddr, &ulDataLen))
    {
        g_stDiagToHsoErrRecord.usRlsRdErr++;
        diag_printf("Function:%s error, ulSrcChanID = %d  \n", __FUNCTION__, ulSrcChanID);
        return ERR_MSP_FAILURE;
    }

    /* �Ѿ�û��RD */
    if ((VOS_NULL == ulDataAddr) || (0 == ulDataLen))
    {
        //diag_printf("diag_ReleaseLogBuf:ulDataAddr=0x%x,ulDataLen=%d\n",ulDataAddr,ulDataLen);
        g_stDiagToHsoErrRecord.usNoRdNum++;
        return ERR_MSP_SUCCESS;
    }

    /*����ͨ�����ͻ�ȡҪ�ͷ��ĸ�BUF����*/
    ulIndex = diag_GetBufIndex(ulSrcChanID);
    /*��SOCP�����ĵ�ַΪʵ��ַ����Ҫת�����ַ����*/
    /*lint -save -e40*/
    pucVirtAddr = diag_BuffPhyToVirt((VOS_UINT8*)ulDataAddr,(VOS_UINT8*)DIAG_MEM_ADDR_BASE,(VOS_UINT8*)g_DiagMemVirt,(VOS_UINT32)(g_stDiagBufCtrl[ulIndex].lBufSize));
    /*lint -restore*/
    if (VOS_NULL_PTR == pucVirtAddr)
    {
        g_stDiagToHsoErrRecord.usRlsAddrErr++;
        diag_printf("Function:%s error ulDataAddr = %d \n", __FUNCTION__, ulDataAddr);
        return ERR_MSP_INVALID_OP;
    }

    /* �����ѷ���RD�ܳ����ͷ��ڴ� */
    if (VOS_OK != diag_ReleaseLogMem(&g_stDiagBufCtrl[ulIndex], pucVirtAddr, (VOS_INT32)ulDataLen))
    {
        g_stDiagToHsoErrRecord.usRlsMemErr++;
        diag_printf("Function:%s ulIndex = %d Error\n", __FUNCTION__, ulIndex);
        return ERR_MSP_FAILURE;
    }

    return ERR_MSP_SUCCESS;
}


VOS_UINT8* diag_GetCoderSrcBuf(VOS_UINT32 ulLen,SOCP_CODER_SRC_ENUM_U32 ulChanID)
{
    VOS_UINT8* aucBuf = NULL;
    VOS_UINT32 ulIndex = 0;
    VOS_UINT32 ulRet = 0;

    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_GET_SRC_BUF_START, ulChanID, (VOS_UINT32)ulLen, 0);
#if (VOS_LINUX== VOS_OS_VER)
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    if(g_diagSocpIsEnable == FALSE)
    {
        vos_printf("%s socp is disable\n", __FUNCTION__);
        return NULL;
    }
#endif
#endif

    /*clean ʹ�ù���RD��MEM buffer*/
    ulRet = diag_ReleaseLogBuf(ulChanID);
    if(ERR_MSP_SUCCESS != ulRet)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_GET_SRC_BUF_START_ERROR, ulChanID, (VOS_UINT32)ulRet, 0);
        diag_printf("Function:%s ulRet = %d Error\n", __FUNCTION__, ulRet);
        return NULL;
    }

    if( SCM_CODER_SRC_MAX_LEN  <= ulLen)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_GET_SRC_BUF_START_ERROR, ulChanID, (VOS_UINT32)ulLen, 2);
        return NULL;
    }

    /*����ͨ�����ͻ�ȡҪ�����ĸ�BUF����*/
    ulIndex = diag_GetBufIndex(ulChanID);

    /*��ȡ����Դͨ��Buf*/
    aucBuf = diag_AllocLogMem(&g_stDiagBufCtrl[ulIndex], (VOS_INT32)ulLen);

    if(aucBuf == NULL)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_GET_SRC_BUF_START_ERROR, ulChanID, (VOS_UINT32)ulLen, 1);
        g_stDiagToHsoErrRecord.usAllocMemErr++;
        return NULL;
    }
    else
    {
        return aucBuf;
    }

}


VOS_UINT32 diag_SendCoderSrcToSocp(VOS_UINT8 *pBuf,VOS_UINT32 ulLen, SOCP_CODER_SRC_ENUM_U32 ulCodeSrcId)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT8  *pucRealMemAddr;
    VOS_UINT32 ulIndex = 0;

    DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_CODE_PACKET_START, ulCodeSrcId, (VOS_UINT32)ulLen, 0);

    /*����ͨ�����ͻ�ȡҪ�����ĸ�BUF����*/
    ulIndex = diag_GetBufIndex(ulCodeSrcId);

    /*���SOCP����Ϊʵ��ַ*/
    /*lint -save -e40*/
    pucRealMemAddr = diag_BuffVirtToPhy(pBuf,(VOS_UINT8*)g_DiagMemVirt,(VOS_UINT8*)DIAG_MEM_ADDR_BASE,(VOS_UINT32)(g_stDiagBufCtrl[ulIndex].lBufSize));
    /*lint -restore*/

    if (VOS_NULL_PTR == pucRealMemAddr)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_CODE_PACKET_START_ERROR, ulCodeSrcId, (VOS_UINT32)ulLen, 0);
        /*�������ʧ��,�������buf�黹*/
        g_stDiagBufCtrl[ulIndex].lAlloc -= (VOS_INT32)ulLen;

        g_stDiagToHsoErrRecord.usSendAddrErr++;

        return ERR_MSP_INVALID_OP;
    }

#if((VOS_OS_VER == VOS_VXWORKS) || (VOS_OS_VER == VOS_RTOSCK))
    /*���ݷ���ǰ��ˢcache*/
    SCM_FLUSH_CACHE(pBuf, ulLen);
#endif

    /*�����ݷ���SOCP*/
    ret = SCM_SendCoderSrc(ulCodeSrcId,pucRealMemAddr,ulLen);
    if(ret != ERR_MSP_SUCCESS)
    {
        DIAG_DEBUG_SDM_FUN(EN_DIAG_DEBUG_CODE_PACKET_START_ERROR, ulCodeSrcId, (VOS_UINT32)ulLen, 1);
        /*�������ʧ��,�������buf�黹*/
		g_stDiagBufCtrl[ulIndex].lAlloc -= (VOS_INT32)ulLen;

        g_stDiagToHsoErrRecord.usSendSocpDataErr++;
    }

    return ret;

}

VOS_VOID diag_BufHelp(VOS_VOID)
{
    VOS_UINT32 i =0;

    vos_printf("�ź���������=%x:\n",                            g_LockBufTimes);
    vos_printf("�ź�����������=%x:\n",                          g_UnLockBufTimes);

    vos_printf("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");

    for(i = 0 ;i< 2 ;i++)
    {
        vos_printf("����ԴBUF��ʼ�����ַ=%p:\n",                    g_stDiagBufCtrl[i].pucBuf);
        vos_printf("����ԴBUF��ʼ�����ַ=%p:\n",                    g_stDiagBufCtrl[i].pucRealBuf);
        vos_printf("����ԴBUF�����ַ�������ʼ�����ַƫ��=0x%x:\n",  g_stDiagBufCtrl[i].lAlloc);
        vos_printf("����ԴBUF�ͷŵ�ַ�������ʼ�����ַƫ��=0x%x:\n",  g_stDiagBufCtrl[i].lRelease);
        vos_printf("����ԴBUF����ַ�������ʼ�����ַƫ��=0x%x:\n",  g_stDiagBufCtrl[i].lPadding);
        vos_printf("����ԴBUF��С=%d(K):\n",                           (g_stDiagBufCtrl[i].lBufSize)/1024);

        vos_printf("\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n");
    }

    vos_printf("���� uncache mem�������=%d:\n",                 g_stDiagToHsoErrRecord.usNoMemErr);
    vos_printf("���� BUF�������=%d:\n",                         g_stDiagToHsoErrRecord.usAllocMemErr);
    vos_printf("�ͷ� BUF�������=%d:\n",                         g_stDiagToHsoErrRecord.usRlsMemErr);
    vos_printf("�ͷ� RD�������=%d:\n",                          g_stDiagToHsoErrRecord.usRlsRdErr);
    vos_printf("ʵ��ַת�����ַ�������=%d:\n",                 g_stDiagToHsoErrRecord.usRlsAddrErr);
    vos_printf("���ַת��ʵ��ַ�������=%d:\n",                 g_stDiagToHsoErrRecord.usSendAddrErr);
    vos_printf("д��SOCP�������=%d:\n",                         g_stDiagToHsoErrRecord.usSendSocpDataErr);
	vos_printf("��RD�������=%d:\n",                             g_stDiagToHsoErrRecord.usNoRdNum);
}

VOS_VOID diag_BufDebug(VOS_VOID)
{
    VOS_UINT32 i =0;

    for(i = 0 ;i< 2 ;i++)
    {
		if(g_stDiagBufCtrl[i].lAlloc >= g_stDiagBufCtrl[i].lRelease)
		{
			g_UnNeedMaxBuf[i] = g_stDiagBufCtrl[i].lAlloc - g_stDiagBufCtrl[i].lRelease;
		}
		else
		{
			g_UnNeedMaxBuf[i] = g_stDiagBufCtrl[i].lBufSize - g_stDiagBufCtrl[i].lRelease + g_stDiagBufCtrl[i].lAlloc;
		}
		vos_printf("buf[%d]��Ҫ����󳤶� = %d(k);\n",		i,	g_UnNeedMaxBuf[i]/1024);
    }
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


