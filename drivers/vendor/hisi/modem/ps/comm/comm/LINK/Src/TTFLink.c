/******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : TTFLink.c
  Author       : g45205
  Version      : V100R001
  Date         : 2006-11-07
  Description  :
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2006-11-07
     Author: g45205
     Modification:Create

  2. Data:2008-11-04
     Author: h62119
     Modification: Ring Queue Function
******************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "pslog.h"
#include "TTFLink.h"
/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(760)*/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_TTF_LINK_C
/*lint +e767*/


/******************************************************************************
   2 �ⲿ������������
******************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/******************************************************************************
 Prototype      : TTF_NodeInit
 Description    : ��ʼ������ڵ�ڵ㣬��ʹ�øýڵ�֮ǰ��������øú�����ʼ��
                  ע��: �����߱�֤pNodeΪ�ǿ�ָ��
 Input          : pNode -- ����ڵ�
 Output         : NULL
 Return Value   : None
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-08-31
    Author      : g45205
    Modification: Created function
******************************************************************************/
VOS_VOID TTF_NodeInit(TTF_NODE_ST *pNode)
{
    pNode->pPrev    = VOS_NULL_PTR;
    pNode->pNext    = VOS_NULL_PTR;
} /* TTF_NodeInit */


/******************************************************************************
 Prototype       : TTF_LinkInit
 Description     : ��ʼ������
 Input           : pLink   -- ����ָ��
 Output          : None
 Return Value    : VOS_VOID
 History         :
  1.Date         : 2006-08-31
    Author       : g45205
    Modification : Created function
******************************************************************************/
VOS_VOID TTF_LinkInit(VOS_UINT32 ulPid, TTF_LINK_ST *pLink)
{
    if (VOS_NULL_PTR == pLink)
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is Null!");
        return;
    }

    pLink->stHead.pNext = &pLink->stHead;
    pLink->stHead.pPrev = &pLink->stHead;
    pLink->ulCnt        = 0;

} /* TTF_LinkInit */

#ifdef WTTF_PC_ST_SWITCH
/******************************************************************************
 Prototype       : TTF_LinkFree
 Description     : ���Ҹýڵ��Ƿ��ڵ�ǰ��������
                   ע��:��Ϊ���쳣ʱҲ����PS_FALSE�����ܻ���ɵ����ߵ���⣬���
                     �������豣֤pLink��pCurr����Ч
 Input           : pLink   -- ����ָ��
                   pCurr   -- ����ڵ�ָ��
 Output          : NONE
 Return Value    : PS_TRUE  -- �ýڵ��ڵ�ǰ��������
                   PS_FALSE -- �ýڵ㲻�ڵ�ǰ��������
 History         :
  1.Date         : 2006-12-25
    Author       : j62118
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_LinkCheckNodeInLink(VOS_UINT32 ulPid, TTF_LINK_ST *pLink, TTF_NODE_ST *pCurr)
{
    TTF_NODE_ST *pNode;

    pNode = pLink->stHead.pNext;

    while ((&pLink->stHead) != pNode)
    {
        if (pCurr == pNode)
        {
            return PS_TRUE;
        }

        pNode = pNode->pNext;
    }

    /*��������δ���ҵ���Ӧ�Ľ��*/
    return PS_FALSE;
}
#endif



#ifndef _lint
/******************************************************************************
 Prototype       : TTF_LinkInsertHead
 Description     : �����������ͷ��
 Input           : pLink   -- ����ָ��
                   pNode   -- ����ڵ�
 Output          : NONE
 Return Value    : PS_SUCC  -- �ɹ�
                   PS_FAIL -- ʧ��
 History         :
  1.Date         : 2006-08-31
    Author       : g45205,j62118
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_LinkInsertHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert)
{

    if ( (VOS_NULL_PTR == pLink) || (VOS_NULL_PTR == pInsert ))
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink Or pInsert is Null!");
        return PS_FAIL;
    }

#ifdef WTTF_PC_ST_SWITCH
    /*���ڵ�pInsert�Ƿ�������pLink��*/
    if ( PS_TRUE == TTF_LinkCheckNodeInLink(ulPid, pLink, pInsert) )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pInsert has Existed in pLink!");
        return PS_FAIL;
    }
#endif

    pInsert->pPrev              = (TTF_NODE_ST *)(&pLink->stHead);
    pLink->stHead.pNext->pPrev  = pInsert;
    pInsert->pNext              = pLink->stHead.pNext;
    pLink->stHead.pNext         = pInsert;

    pLink->ulCnt++;

    return PS_SUCC;
} /*TTF_LinkInsertHead*/
#endif


#ifndef _lint
/******************************************************************************
 Prototype       : TTF_LinkInsertNext
 Description     : �����������ָ��λ�õ���һ����㡣
                   ע��:������PS_FAIL���ú���������pInsert���ͷš�
 Input           : pLink   -- ����ָ��
                   pCurr   -- ����ڵ�
                   pInsert
 Output          : NONE
 Return Value    : PS_SUCC  -- �ɹ�
                   PS_FAIL -- ʧ��
 History         :
  1.Date         : 2006-12-25
    Author       : j62118
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_LinkInsertNext(VOS_UINT32 ulPid, TTF_LINK_ST * pLink,
                TTF_NODE_ST *pCurr, TTF_NODE_ST *pInsert)
{

    if ( (VOS_NULL_PTR == pLink) || (VOS_NULL_PTR == pCurr) || (VOS_NULL_PTR == pInsert))
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink��pCurr Or pInsert is Null!");
        return PS_FAIL;
    }

    /*�����ýڵ��Ƿ��������ڣ����ޣ�����ʧ��*/





#ifdef WTTF_PC_ST_SWITCH
    /*���ڵ�pInsert�Ƿ�������pLink��*/
    if ( PS_TRUE == TTF_LinkCheckNodeInLink(ulPid, pLink, pInsert) )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pInsert has Existed in pLink!");
        return PS_FAIL;
    }
#endif

    pInsert->pPrev              = pCurr;
    pCurr->pNext->pPrev         = pInsert;
    pInsert->pNext              = pCurr->pNext;
    pCurr->pNext                = pInsert;

    pLink->ulCnt++;

    return PS_SUCC;
}
#endif




/******************************************************************************
 Prototype       : TTF_LinkRemoveTail
 Description     : �������β���Ƴ�һ���ڵ㣬�������Ƴ��Ľ��
 Input           : pLink  -- ����ָ��
 Output          : NONE
 Return Value    : ������Ľڵ��ָ��
 History         :
  1.Date         : 2006-08-31
    Author       : g45205,j62118
    Modification : Created function
******************************************************************************/
TTF_NODE_ST* TTF_LinkRemoveTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink)
{
    TTF_NODE_ST    *pNode;

    if (VOS_NULL_PTR == pLink)
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is Null!");
        return VOS_NULL_PTR;
    }

    if (0 == pLink->ulCnt)
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink Cnt is 0!");
        return VOS_NULL_PTR;
    }

    /*�쳣:��������������һ��ʱ, �ݴ���*/
    if ( pLink->stHead.pNext == &pLink->stHead )
    {
        PS_LOG1(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is null, but Cnt is <1>!", (VOS_INT32)pLink->ulCnt);
        pLink->ulCnt = 0;
        return VOS_NULL_PTR;
    }

    pNode               = pLink->stHead.pPrev;
    pLink->stHead.pPrev = pNode->pPrev;
    pNode->pPrev->pNext = &pLink->stHead;
    pNode->pNext        = VOS_NULL_PTR;
    pNode->pPrev        = VOS_NULL_PTR;

    pLink->ulCnt--;
    return  pNode;

} /* TTF_LinkRemoveTail */

/******************************************************************************
 Prototype       : TTF_LinkRemoveNode
 Description     : ���������Ƴ�ָ���Ľڵ㣬�������Ƿ��Ƴ��ɹ���
                   ǰ��:�ú����������κ��쳣���ɵ���������֤�Ƴ��ڵ��ڵ�ǰ�������С�
                        ��ͨ��TTF_LinkCheckNodeInLink()������Ӧ�ļ��
 Input           : pLink        -- ����ָ��
                   pRemoveNode  -- ���Ƴ��Ľ��
 Output          : NONE
 Return Value    : PS_SUCC  -- �ɹ�
                   PS_FAIL -- ʧ��
 History         :
  1.Date         : 2006-12-14
    Author       : z44034,j62118
    Modification : Created function
******************************************************************************/
VOS_VOID TTF_LinkRemoveNode(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pRemoveNode)
{

    pRemoveNode->pNext->pPrev = pRemoveNode->pPrev;
    pRemoveNode->pPrev->pNext = pRemoveNode->pNext;
    pRemoveNode->pPrev        = VOS_NULL_PTR;
    pRemoveNode->pNext        = VOS_NULL_PTR;

    pLink->ulCnt--;
    return;

}


TTF_NODE_ST* TTF_LinkPeekTail(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink)
{
    if ( VOS_NULL_PTR == pLink )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is Null!");
        return VOS_NULL_PTR;
    }

    if ( 0 == pLink->ulCnt )
    {
        PS_LOG(ulPid, 0, PS_PRINT_INFO, "Info: Tail Node is Null!");
        return VOS_NULL_PTR;
    }

    return pLink->stHead.pPrev;
}


VOS_UINT32 TTF_LinkPeekNext(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink,
        TTF_NODE_ST *pCurr, TTF_NODE_ST **ppCurrNext)
{
    TTF_NODE_ST*    pNode;

    if (( VOS_NULL_PTR == pLink ) || ( VOS_NULL_PTR == pCurr ) || ( VOS_NULL_PTR == ppCurrNext ))
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink��pInsert Or ppCurrNext is Null!");
        return PS_FAIL;
    }

    if ( 0 == pLink->ulCnt )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink Cnt is 0!");
        return PS_FAIL;
    }

    if ( (TTF_NODE_ST*)pLink == pCurr )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: Node Address == Link Address!");
        return PS_FAIL;
    }

#ifdef WTTF_PC_ST_SWITCH
    pNode = pLink->stHead.pNext;
    while (pCurr != pNode)
    {
        /*��������δ���ҵ���Ӧ�Ľڵ�*/
        if (&(pLink->stHead) == pNode)
        {
            PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: Not Find The Node In the Link!");
            return PS_FAIL;
        }

        pNode = pNode->pNext;
    }
#else
    pNode = pCurr;
#endif

    /*����ǰ�ڵ���β�ڵ㣬�򷵻�VOS_NULL_PTR�����򣬷�����һ����ַ*/
    if ( &(pLink->stHead) == pNode->pNext )
    {
        *ppCurrNext = VOS_NULL_PTR;
    }
    else
    {
        *ppCurrNext = pNode->pNext;
    }

    return PS_SUCC;

}


VOS_UINT32 TTF_LinkPeekPrev(VOS_UINT32 ulPid, TTF_LINK_ST * pLink,
    TTF_NODE_ST *pCurr, TTF_NODE_ST **ppCurrPrev)
{
    TTF_NODE_ST*    pNode;

    if (( VOS_NULL_PTR == pLink ) || ( VOS_NULL_PTR == pCurr ) || ( VOS_NULL_PTR == ppCurrPrev ))
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "\n Warning: pLink��pInsert Or ppCurrPrev is Null!\n");
        return PS_FAIL;
    }

    if ( 0 == pLink->ulCnt )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "\n Warning: pLink Cnt is 0!\n");
        return PS_FAIL;
    }

    if ( (TTF_NODE_ST*)pLink == pCurr )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "\n Warning: Node Address == Link Address!\n");
        return PS_FAIL;
    }

#ifdef WTTF_PC_ST_SWITCH
    pNode = pLink->stHead.pNext;
    while (pCurr != pNode)
    {
        /*��������δ���ҵ���Ӧ�Ľڵ�*/
        if ( &(pLink->stHead) == pNode )
        {
            PS_LOG(ulPid, 0, PS_PRINT_WARNING, "\n Warning: Not Find The Node In the Link!\n");
            return PS_FAIL;
        }

        pNode = pNode->pNext;
    }
#else
    pNode = pCurr;
#endif

    /*����ǰ�ڵ���ͷ�ڵ㣬�򷵻�VOS_NULL_PTR�����򣬷���ǰһ����ַ*/
    if ( &(pLink->stHead) == pNode->pPrev )
    {
        *ppCurrPrev = VOS_NULL_PTR;
    }
    else
    {
        *ppCurrPrev = pNode->pPrev;
    }

    return PS_SUCC;

}

/*****************************************************************************
 Prototype       : TTF_LinkStick
 Description     : ������2�ĳ�Աȫ�����ӵ�����1�У������ڶ���������Ϊ������
                   ע��:���ô˺����󣬵ڶ�����������Ϊ������
 Input           : ulPid   -- ���ô˺�����ģ���Pid
                   pLink1  -- ����1
                   pLink2  -- ����2
 Output          : NONE
 Return Value    : VOS_OK  -- �ɹ�
                   VOS_ERR -- ʧ��
 History         :
    Date         : 2007-02-21
    Author       : z47725
    Modification : Created function
*****************************************************************************/
VOS_UINT32 TTF_LinkStick(VOS_UINT32 ulPid, TTF_LINK_ST *pLink1,
    TTF_LINK_ST *pLink2)
{
    if (VOS_NULL_PTR == pLink1)
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING,
            "TTFCOMM, TTF_LinkStick, ERROR, pLink1 is null\n");
        return VOS_ERR;
    }

    if (VOS_NULL_PTR == pLink2)
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING,
            "TTFCOMM, TTF_LinkStick, ERROR, pLink2 is null\n");
        return VOS_ERR;
    }

    if (TTF_LINK_IS_EMPTY(pLink2))
    {
        return VOS_OK;
    }

    pLink1->stHead.pPrev->pNext = pLink2->stHead.pNext;
    pLink2->stHead.pNext->pPrev = pLink1->stHead.pPrev;
    pLink1->stHead.pPrev        = pLink2->stHead.pPrev;
    pLink2->stHead.pPrev->pNext = (TTF_NODE_ST *)&(pLink1->stHead);

    /*���³���*/
    pLink1->ulCnt       += pLink2->ulCnt;

    TTF_LINK_INIT(pLink2);

    return VOS_OK;
}


/******************************************************************************
 Prototype       : TTF_LinkSafeInsertTail
 Description     : �����������β��
 Input           : pLink   -- ����ָ��
                   pNode   -- ����ڵ�
 Output          : NONE
 Return Value    : PS_SUCC  -- �ɹ�
                   PS_FAIL -- ʧ��
 History         :
  1.Date         : 2006-08-31
    Author       : g45205
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_LinkSafeInsertTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert, VOS_UINT32 *pulNonEmptyEvent)
{
    VOS_INT32       lLockKey;


    *pulNonEmptyEvent    = PS_FALSE;

    lLockKey    = VOS_SplIMP();

    if ( (VOS_NULL_PTR == pLink) || (VOS_NULL_PTR == pInsert) )
    {
        VOS_Splx(lLockKey);
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink Or pInsert is Null!");
        return PS_FAIL;
    }

#ifdef WTTF_PC_ST_SWITCH
    /*���ڵ�pInsert�Ƿ�������pLink��*/
    if ( PS_TRUE == TTF_LinkCheckNodeInLink(ulPid, pLink, pInsert) )
    {
        VOS_Splx(lLockKey);
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pInsert has Existed in pLink!");
        return PS_FAIL;
    }
#endif

    if (0 == TTF_LINK_CNT(pLink))
    {
        *pulNonEmptyEvent  = PS_TRUE;
    }

    pInsert->pNext              = (TTF_NODE_ST *)(&pLink->stHead);
    pInsert->pPrev              = pLink->stHead.pPrev;

    pLink->stHead.pPrev->pNext  = pInsert;
    pLink->stHead.pPrev         = pInsert;

    pLink->ulCnt++;

    VOS_Splx(lLockKey);

    return PS_SUCC;
} /* TTF_LinkSafeInsertTail */


/******************************************************************************
 Prototype       : TTF_LinkSafeRemoveHead
 Description     : �������ͷ���Ƴ�һ����㣬�������Ƴ��Ľ��
 Input           : pLink  -- ����ָ��
 Output          : NONE
 Return Value    : ������Ľڵ��ָ��
 History         :
  1.Date         : 2006-08-31
    Author       : g45205,j62118
    Modification : Created function
******************************************************************************/
TTF_NODE_ST* TTF_LinkSafeRemoveHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, VOS_UINT32 *pulRemainCnt)
{
    TTF_NODE_ST    *pNode;
    VOS_INT32       lLockKey;


    lLockKey    = VOS_SplIMP();

    *pulRemainCnt   = 0;

    if (VOS_NULL_PTR == pLink)
    {
        VOS_Splx(lLockKey);
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is Null!");
        return VOS_NULL_PTR;
    }

    if (0 == pLink->ulCnt)
    {
        VOS_Splx(lLockKey);
        PS_LOG(ulPid, 0, PS_PRINT_INFO, "Warning: pLink Cnt is 0!");
        return VOS_NULL_PTR;
    }

    /*�쳣:��������������һ��ʱ, �ݴ���*/
    if ( pLink->stHead.pNext == &pLink->stHead )
    {
        pLink->ulCnt = 0;
        VOS_Splx(lLockKey);
        PS_LOG1(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is null, but Cnt is <1>!", (VOS_INT32)pLink->ulCnt);
        return VOS_NULL_PTR;
    }

    pNode               = pLink->stHead.pNext;
    pLink->stHead.pNext = pNode->pNext;
    pNode->pNext->pPrev = &pLink->stHead;
    pNode->pNext        = VOS_NULL_PTR;
    pNode->pPrev        = VOS_NULL_PTR;

    pLink->ulCnt--;

    /* ��ȡ������ʣ��Ԫ�ظ��� */
    *pulRemainCnt   = pLink->ulCnt;

    VOS_Splx(lLockKey);

    return pNode;

} /* TTF_LinkSafeRemoveHead */

#ifndef _lint
/******************************************************************************
 Prototype       : TTF_LinkInsertTail
 Description     : �����������β��
 Input           : pLink   -- ����ָ��
                   pNode   -- ����ڵ�
 Output          : NONE
 Return Value    : PS_SUCC  -- �ɹ�
                   PS_FAIL -- ʧ��
 History         :
  1.Date         : 2006-08-31
    Author       : g45205
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_LinkInsertTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert)
{
    if ( (VOS_NULL_PTR == pLink) || (VOS_NULL_PTR == pInsert) )
    {
        /*PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink Or pInsert is Null!");
 */
        return PS_FAIL;
    }

    pInsert->pNext              = (TTF_NODE_ST *)(&pLink->stHead);
    pInsert->pPrev              = pLink->stHead.pPrev;

    pLink->stHead.pPrev->pNext  = pInsert;
    pLink->stHead.pPrev         = pInsert;

    pLink->ulCnt++;

    return PS_SUCC;
} /* TTF_LinkInsertTail */

#endif

/******************************************************************************
 Prototype       : TTF_LinkRemoveHead
 Description     : �������ͷ���Ƴ�һ���ڵ㣬�������Ƴ��Ľ��
 Input           : pLink  -- ����ָ��
 Output          : NONE
 Return Value    : ������Ľڵ��ָ��
 History         :
  1.Date         : 2006-08-31
    Author       : g45205,j62118
    Modification : Created function
******************************************************************************/
/*lint -esym( 528, TTF_LinkRemoveHead )*/
TTF_NODE_ST* TTF_LinkRemoveHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink)
{
    TTF_NODE_ST    *pNode;

    if (VOS_NULL_PTR == pLink)
    {
        /*PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is Null!");
 */
        return VOS_NULL_PTR;
    }

    if (0 == pLink->ulCnt)
    {
        /*PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink Cnt is 0!");
 */
        return VOS_NULL_PTR;
    }

    /*�쳣:��������������һ��ʱ, �ݴ���*/
    if ( pLink->stHead.pNext == &pLink->stHead )
    {
        /*PS_LOG1(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is null, but Cnt is <1>!", (VOS_INT32)pLink->ulCnt);
 */
        pLink->ulCnt = 0;
        return VOS_NULL_PTR;
    }

    pNode               = pLink->stHead.pNext;
    pLink->stHead.pNext = pNode->pNext;
    pNode->pNext->pPrev = &pLink->stHead;
    pNode->pNext        = VOS_NULL_PTR;
    pNode->pPrev        = VOS_NULL_PTR;

    pLink->ulCnt--;

    return pNode;

} /* TTF_LinkRemoveHead */

/******************************************************************************
 Prototype       : TTF_LinkCnt
 Description     : �������еĽڵ�����������
 Input           : pLink   -- ����ָ��
 Output          : NONE
 Return Value    :  -- �����еĽڵ���
 History         :
  1.Date         : 2006-08-31
    Author       : g45205
    Modification : Created function
******************************************************************************/
/*lint -esym( 528, TTF_LinkCnt )*/
VOS_UINT32 TTF_LinkCnt(VOS_UINT32 ulPid, const TTF_LINK_ST *pLink)
{
    if (VOS_NULL_PTR == pLink)
    {
        /*PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is Null!");
 */
        return 0;
    }
    return (pLink->ulCnt);
} /* TTF_LinkCnt */


/******************************************************************************
 Prototype       : TTF_LinkIsEmpty
 Description     : �ж������Ƿ�Ϊ��
                   ע��:����������ʱ���˺�������Ϊ�����ǿյ�
 Input           : pLink   -- ����ָ��
 Output          : NONE
 Return Value    : PS_TRUE   -- �����
                   PS_FALSE  -- ����ǿ�
 History         :
  1.Date         : 2006-08-31
    Author       : g45205
    Modification : Created function
******************************************************************************/
/*lint -esym( 528, TTF_LinkIsEmpty )*/
VOS_UINT32 TTF_LinkIsEmpty(VOS_UINT32 ulPid, const TTF_LINK_ST *pLink)
{
    if (VOS_NULL_PTR == pLink)
    {
        /*PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is Null!");
 */
        return PS_TRUE;
    }

    if (0 == pLink->ulCnt)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
} /* TTF_LinkIsEmpty */



/*lint -esym( 528, TTF_LinkPeekHead )*/
TTF_NODE_ST* TTF_LinkPeekHead(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink)
{
    if ( VOS_NULL_PTR == pLink )
    {
        /*PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pLink is Null!");
 */
        return VOS_NULL_PTR;
    }

    if ( 0 == pLink->ulCnt )
    {
        return VOS_NULL_PTR;
    }
    return pLink->stHead.pNext;
}

/******************************************************************************
 Prototype       : TTF_RING_Q_Init
 Description     : ��ʼ�����ζ���
 Input           :
 Output          :
 Return Value    :
 History         :
  1.Date         : 2008-11-04
    Author       : h62119
    Modification : Created function
******************************************************************************/
VOS_UINT32  TTF_RING_Q_Init(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ, VOS_UINT32 ulMaxSize )
{
    VOS_VOID **ppNode;


    if (VOS_NULL_PTR == pstRingQ )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return PS_FAIL;
    }

    if ( 2 > ulMaxSize)
    {
        PS_LOG1(ulPid, 0, PS_PRINT_WARNING, "Warning: RingQ  ulMaxSize<1> less than 2 !",(VOS_INT32)ulMaxSize);
        return PS_FAIL;
    }

    #if( VOS_OS_VER == VOS_WIN32 )
    ppNode  = (VOS_VOID **)malloc(sizeof(VOS_VOID *) * ulMaxSize);
    #else
    ppNode  = (VOS_VOID **)VOS_MemAlloc(ulPid, (STATIC_MEM_PT), (sizeof(VOS_VOID *) * ulMaxSize));
    #endif

    if(VOS_NULL_PTR == ppNode )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: RingQ Init Malloc Fail!");
        return PS_FAIL;
    }

    pstRingQ->ppNode       = ppNode;
    pstRingQ->ulFront      = 0;
    pstRingQ->ulRear       = 0;
    pstRingQ->ulMaxSize    = ulMaxSize;
    return PS_SUCC;

} /* TTF_RING_Q_Init */



VOS_UINT32  TTF_RING_Q_NodeAddrInit(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ, VOS_VOID **ppNodeAddr,VOS_UINT32 ulNodeCnt,VOS_UINT8 ucSize)
{
    VOS_UINT32      ulNodeLoop;

    if ( VOS_NULL_PTR == pstRingQ )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return PS_FAIL;
    }

    if ( VOS_NULL_PTR == pstRingQ->ppNode )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: ppNode is Null !");
        return PS_FAIL;
    }

    if ( VOS_NULL_PTR == ppNodeAddr )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: ppNodeAddr is Null !");
        return PS_FAIL;
    }

    if ( 2 > ulNodeCnt)
    {
        PS_LOG1(ulPid, 0, PS_PRINT_WARNING, "Warning: ppNodeAddr  ulNodeCnt<1> less than 2 !",(VOS_INT32)ulNodeCnt);
        return PS_FAIL;
    }


    if ( ulNodeCnt != pstRingQ->ulMaxSize )
    {
        PS_LOG2(ulPid, 0, PS_PRINT_WARNING, "Warning: RingQ MaxSize<1> is not matched NodeCnt<2>!", (VOS_INT32)pstRingQ->ulMaxSize, (VOS_INT32)ulNodeCnt);
        return PS_FAIL;
    }

    for (ulNodeLoop = 0; ulNodeLoop < pstRingQ->ulMaxSize; ulNodeLoop++)
    {
        /* �˼乲����ĵ�ַ */
/*      ppNodeAddr = ppNodeAddr + ulNodeLoop*ucSize;
 */
        pstRingQ->ppNode[ulNodeLoop] = (VOS_VOID *)ppNodeAddr;
        ppNodeAddr = ppNodeAddr + ucSize;
    }
    return PS_SUCC;
}



/*Linux add begin������� 00178567 */

VOS_UINT32  TTF_RING_Q_InitAndNodeAddrSet(VOS_UINT32 ulPid,
                                                        TTF_RING_Q_ST *pstRingQ,
                                                        VOS_VOID **ppNode,
                                                        VOS_VOID *pQueueNode,
                                                        VOS_UINT32 ulBlkSize,
                                                        VOS_UINT32 ulBlkCnt )
{
    VOS_UINT32      ulNodeNoLoop        = 0;
    VOS_UINT8      *pucQueueNodeAddr      = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pstRingQ )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return PS_FAIL;
    }

    if ( 2 > ulBlkCnt)
    {
        PS_LOG1(ulPid, 0, PS_PRINT_WARNING, "Warning: RingQ  ulMaxSize<1> less than 2 !",(VOS_INT32)ulBlkCnt);
        return PS_FAIL;
    }

    if(VOS_NULL_PTR == ppNode )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: RingQ Init Malloc Fail!");
        return PS_FAIL;
    }

    pstRingQ->ppNode       = ppNode;
    pstRingQ->ulFront      = 0;
    pstRingQ->ulRear       = 0;
    pstRingQ->ulMaxSize    = ulBlkCnt;          /* TTF_RING_Q_ST��ulMaxSize����������ݿ��� */
    pucQueueNodeAddr         = (VOS_UINT8 *)pQueueNode;

    for(ulNodeNoLoop = 0; ulNodeNoLoop < pstRingQ->ulMaxSize; ulNodeNoLoop ++)
    {
        pstRingQ->ppNode[ulNodeNoLoop] = (pucQueueNodeAddr + ulBlkSize * ulNodeNoLoop);
    }

    return PS_SUCC;
} /* TTF_RING_Q_InitAndNodeAddrSet */

/*Linux end begin������� 00178567 */
/******************************************************************************
 Prototype       : TTF_RING_Q_NodeAddrSet
 Description     : ��ʵ�����ݺͻ��ζ��н��а󶨡����ζ������Ԫ�ش洢����ָ��ʵ�����ݵ�ָ�룬
                   ����ppNodeAddr�Ǵ洢ָ��ʵ�����ݵ�ָ�����顣
 Input           :
 Output          :
 Return Value    :
 History         :
  1.Date         : 2008-11-04
    Author       : h62119
    Modification : Created function
******************************************************************************/
VOS_UINT32  TTF_RING_Q_NodeAddrSet(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ,
                                    VOS_VOID **ppNodeAddr,VOS_UINT32 ulNodeCnt)
{
    VOS_UINT32      ulNodeNoLoop;


    if (VOS_NULL_PTR == pstRingQ )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return PS_FAIL;
    }

    if ( VOS_NULL_PTR == pstRingQ->ppNode )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: ppNode is Null !");
        return PS_FAIL;
    }

    if ( VOS_NULL_PTR == ppNodeAddr )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: ppNodeAddr is Null !");
        return PS_FAIL;
    }

    if ( 2 > ulNodeCnt)
    {
        PS_LOG1(ulPid, 0, PS_PRINT_WARNING, "Warning: ppNodeAddr  ulNodeCnt<1> less than 2 !",(VOS_INT32)ulNodeCnt);
        return PS_FAIL;
    }


    if ( ulNodeCnt != pstRingQ->ulMaxSize )
    {
        PS_LOG2(ulPid, 0, PS_PRINT_WARNING, "Warning: RingQ MaxSize<1> is not matched NodeCnt<2>!", (VOS_INT32)pstRingQ->ulMaxSize, (VOS_INT32)ulNodeCnt);
        return PS_FAIL;
    }


    for(ulNodeNoLoop = 0; ulNodeNoLoop < pstRingQ->ulMaxSize; ulNodeNoLoop ++)
    {
        pstRingQ->ppNode[ulNodeNoLoop] = ppNodeAddr[ulNodeNoLoop];
    }
    return PS_SUCC;

} /* TTF_RING_Q_NodeAddrSet */

/******************************************************************************
 Prototype       : TTF_RING_Q_Rear
 Description     : �۲컷�ζ����Ƿ�Ϊ�գ������Ϊ�գ��򷵻ض�βָ���Դ����ݵĲ���
                   �˺����ᱻ�жϷ��������ã���˲����д�ӡ
 Input           :
 Output          :
 Return Value    :
 History         :
  1.Date         : 2008-11-04
    Author       : h62119
    Modification : Created function
******************************************************************************/
VOS_VOID* TTF_RING_Q_Rear(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{
    VOS_VOID    *pNode;


    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null ! */
    {
        return VOS_NULL_PTR;
    }

    if ( VOS_NULL_PTR == pstRingQ->ppNode) /* pstRingQ is not Initialized ! */
    {
        return VOS_NULL_PTR;
    }

    if ( pstRingQ->ulFront == PS_MOD_ADD(pstRingQ->ulRear, 1, pstRingQ->ulMaxSize) ) /*  RingQ is Full ! */
    {
        return VOS_NULL_PTR;
    }

    pNode = pstRingQ->ppNode[pstRingQ->ulRear];
    return pNode;

} /* TTF_RING_Q_Rear */


/******************************************************************************
 Prototype       : TTF_RING_Q_In
 Description     : �뻷�ζ���.�ڴ�֮ǰԪ�����ݸ����Ѿ���ɣ����������ƶ���βָ��֮ǰ��
                   �ȵ���TTF_RING_Q_Rear���õ��������ݵĵ�ַ��Ԫ�ز�������ٽ��д˺����ĵ��á�
                   �˺����ᱻ�жϷ��������ã���˲����д�ӡ
 Input           :
 Output          :
 Return Value    :
 History         :
  1.Date         : 2008-11-04
    Author       : h62119
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_RING_Q_In(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ )
{

    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null ! */
    {
        return PS_FAIL;
    }

    if ( pstRingQ->ulFront == PS_MOD_ADD(pstRingQ->ulRear, 1, pstRingQ->ulMaxSize) ) /* RingQ is Full ! */
    {
        return PS_FAIL;
    }

    pstRingQ->ulRear  = PS_MOD_ADD(pstRingQ->ulRear, 1, pstRingQ->ulMaxSize);
    return PS_SUCC;

} /* TTF_RING_Q_In */


/******************************************************************************
 Prototype       : TTF_RING_Q_Front
 Description     : �鿴���ζ��ж�ͷԪ�أ�����������
 Input           :
 Output          :
 Return Value    :
 History         :
  1.Date         : 2008-11-04
    Author       : h62119
    Modification : Created function
******************************************************************************/
VOS_VOID* TTF_RING_Q_Front(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{
    VOS_VOID    *pNode;

    if (VOS_NULL_PTR == pstRingQ )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return VOS_NULL_PTR;
    }

    if ( VOS_NULL_PTR == pstRingQ->ppNode) /* pstRingQ is not Initialized ! */
    {
        return VOS_NULL_PTR;
    }

    if ( pstRingQ->ulRear == pstRingQ->ulFront)
    {
        PS_LOG(ulPid, 0, PS_PRINT_INFO, "Info: RingQ is Empty !");
        return VOS_NULL_PTR;
    }

    pNode = pstRingQ->ppNode[pstRingQ->ulFront];

    return pNode;

} /* TTF_RING_Q_Rear */


/******************************************************************************
 Prototype       : TTF_RING_Q_Out
 Description     : �����ζ���
 Input           :
 Output          :
 Return Value    :
 History         :
  1.Date         : 2008-11-04
    Author       : h62119
    Modification : Created function
******************************************************************************/
VOS_VOID* TTF_RING_Q_Out(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{
    VOS_VOID    *pNode;


    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null */
    {
        return VOS_NULL_PTR;
    }

    if ( VOS_NULL_PTR == pstRingQ->ppNode) /* pstRingQ is not Initialized ! */
    {
        return VOS_NULL_PTR;
    }

    if ( pstRingQ->ulRear == pstRingQ->ulFront) /* RingQ is Empty */
    {
        return VOS_NULL_PTR;
    }

    pNode               = pstRingQ->ppNode[pstRingQ->ulFront];
    pstRingQ->ulFront   = PS_MOD_ADD(pstRingQ->ulFront, 1, pstRingQ->ulMaxSize);
    return pNode;

} /* TTF_RING_Q_Out */


/******************************************************************************
 Prototype       : TTF_RING_Q_IsFull
 Description     : ���ζ����Ƿ���
 Input           :
 Output          :
 Return Value    :
 History         :
  1.Date         : 2008-11-04
    Author       : h62119
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_RING_Q_IsFull(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{

    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null */
    {
        return PS_TRUE;
    }

    if ( pstRingQ->ulFront == PS_MOD_ADD(pstRingQ->ulRear, 1, pstRingQ->ulMaxSize) )
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }

} /* TTF_RING_Q_IsFull */

/******************************************************************************
 Prototype       : TTF_RING_Q_IsEmpty
 Description     : ���ζ���Ԫ�ظ����Ƿ�Ϊ��
 Input           :
 Output          :
 Return Value    :
 History         :
  1.Date         : 2008-11-04
    Author       : h62119
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_RING_Q_IsEmpty(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{

    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null */
    {
        return PS_TRUE;
    }

    if ( pstRingQ->ulRear == pstRingQ->ulFront)
    {
        return PS_TRUE;
    }
    else
    {
        return PS_FALSE;
    }

} /* TTF_RING_Q_IsEmpty */

/******************************************************************************
 Prototype       : TTF_RING_Q_Flush
 Description     : �����ζ����������Ԫ�ض�����
 Input           :
 Output          :
 Return Value    :
 History         :
  1.Date         : 2008-11-04
    Author       : h62119
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_RING_Q_Flush(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{

    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null ! */
    {
        return PS_FAIL;
    }

    pstRingQ->ulFront = pstRingQ->ulRear;/* ��ͷ׷�϶�β */
    return PS_SUCC;

} /* TTF_RING_Q_GetCnt */


/******************************************************************************
 Prototype       : TTF_RING_Q_GetCnt
 Description     : ��ȡ���ζ���Ԫ�ظ���
 Input           :
 Output          :
 Return Value    :
 History         :
  1.Date         : 2008-11-04
    Author       : h62119
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_RING_Q_GetCnt(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{
    VOS_UINT32 ulCnt;

    if (VOS_NULL_PTR == pstRingQ ) /* pstRingQ is Null ! */
    {
        return 0;
    }

    ulCnt   = PS_MOD_SUB( pstRingQ->ulRear, pstRingQ->ulFront, pstRingQ->ulMaxSize);
    return ulCnt;

} /* TTF_RING_Q_GetCnt */


/******************************************************************************
 Prototype       : TTF_RING_Q_Free
 Description     : �ͷ�Ϊ���ζ��з�����ڴ�
 Input           :
 Output          :
 Return Value    :
 History         :
  1.Date         : 2008-11-04
    Author       : h62119
    Modification : Created function
******************************************************************************/
VOS_UINT32  TTF_RING_Q_Free(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ)
{

    if (VOS_NULL_PTR == pstRingQ )
    {
        PS_LOG(ulPid, 0, PS_PRINT_WARNING, "Warning: pstRingQ is Null !");
        return PS_FAIL;
    }

    if ( VOS_NULL_PTR != pstRingQ->ppNode )
    {
        #if( VOS_OS_VER == VOS_WIN32 )
        free(pstRingQ->ppNode);
        #else
        VOS_MemFree(ulPid, pstRingQ->ppNode);
        #endif

        pstRingQ->ppNode = VOS_NULL_PTR;
    }

    pstRingQ->ulFront   =0;
    pstRingQ->ulRear    =0;
    pstRingQ->ulMaxSize =0;

    return PS_SUCC;

} /* TTF_RING_Q_Free */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

