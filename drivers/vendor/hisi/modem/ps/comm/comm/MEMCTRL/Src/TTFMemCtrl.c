


/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "TTFMemCtrl.h"
#include "vos.h"
#include "DrvInterface.h"



#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TTF_MEMCTRL_C


/******************************************************************************
   2 �궨��
******************************************************************************/


/*****************************************************************************
   ��������
*****************************************************************************/


/*****************************************************************************
   ȫ�ֱ�������
*****************************************************************************/
TTF_MEMCTRL_ADDR_STRU              g_stTtfMemCtrlAddr;


/******************************************************************************
   6 ����ʵ��
******************************************************************************/

unsigned long   TTF_MEMCTRL_GetMemTotalLen(void)
{
    BSP_DDR_SECT_QUERY                  stQuery;
    BSP_DDR_SECT_INFO                   stInfo;
    unsigned long                       ulMemTotalLen;
    signed int                          lRslt;


    stQuery.enSectType = BSP_DDR_SECT_TYPE_TTF;
    stInfo.ulSectSize  = TTF_MEMCTRL_INVAILD_SIZE;

    lRslt = DRV_GET_FIX_DDR_ADDR(&stQuery, &stInfo);

    if (BSP_OK != lRslt)
    {
        stInfo.ulSectSize = TTF_MEMCTRL_INVAILD_SIZE;
    }

    ulMemTotalLen    = stInfo.ulSectSize;


    return ulMemTotalLen;
}



unsigned long   TTF_MEMCTRL_AddrInit(void)
{
    unsigned char                       ucTypeLoop;
    unsigned char                       ucTypeLoopOne   = 0;
    unsigned long                       ulTypeOffestLen = 0;
    unsigned long                       ulCCoreTypeLen  = 0;
    unsigned long                       ulMemTotalLen   = 0;


    if (TTF_MEMCTRL_TYPE_INIT_FLG == TTF_MEMCTRL_GET_ADDR_INIT_FLG())
    {
         vos_printf("TTF_MEMCTRL_AddrInit::Addrs were already initialized!\n");

         return 0;
    }

    memset(&g_stTtfMemCtrlAddr, 0, sizeof(TTF_MEMCTRL_ADDR_STRU));

    /* ����TTF �ڴ�������͵��ڴ泤�� */
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE, TTF_HDLC_MASTER_LINK_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_CIPHER_MASTER_ADDR_TYPE, TTF_PARA_MEM_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_BBP_MASTER_ADDR_TYPE, TTF_BBPMST_BUFF_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_ACORE_POOL_ADDR_TYPE, TTF_ACORE_POOL_MEM_TOTAL_LEN);

    ulMemTotalLen   = TTF_MEMCTRL_GetMemTotalLen();

    if (TTF_MEMCTRL_INVAILD_SIZE == ulMemTotalLen)
    {
        vos_printf("TTF_MEMCTRL_AddrInit:ulMemTotalLen is invalid!\n");
        return 0;
    }

    ulCCoreTypeLen  = (ulMemTotalLen - TTF_HDLC_MASTER_LINK_TOTAL_LEN
                        - TTF_PARA_MEM_TOTAL_LEN - TTF_BBPMST_BUFF_TOTAL_LEN - TTF_ACORE_POOL_MEM_TOTAL_LEN);
    TTF_MEMCTRL_SET_TYPE_LEN(TTF_MEMCTRL_CCORE_POOL_ADDR_TYPE, ulCCoreTypeLen);


    for (ucTypeLoop = 0; ucTypeLoop < TTF_MEMCTRL_ADDR_TYPE_BUTT; ucTypeLoop++)
    {
        if (0 != TTF_MEMCTRL_GET_TYPE_LEN(ucTypeLoop))
        {
            TTF_MEMCTRL_SET_TYPE_FLG(ucTypeLoop, TTF_MEMCTRL_TYPE_EXIST_FLG);
        }

        ulTypeOffestLen += TTF_MEMCTRL_GET_TYPE_LEN(ucTypeLoop);
        ucTypeLoopOne   =  ucTypeLoop + 1;
        if (ucTypeLoopOne < TTF_MEMCTRL_ADDR_TYPE_BUTT)
        {
            /* TTF ���������ڴ�����ڻ�ַ��ƫ�Ƴ������� */
            TTF_MEMCTRL_SET_TYPE_OFFSET_BASE_LEN(ucTypeLoopOne, ulTypeOffestLen);
        }
    }

    TTF_MEMCTRL_SET_ADDR_INIT_FLG(TTF_MEMCTRL_TYPE_INIT_FLG);


    return 0;
}



unsigned long   TTF_MEMCTRL_ACORE_AddrInit(void)
{
    TTF_MEMCTRL_AddrInit();

    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_HDLC_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_ACORE_POOL_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);


    return 0;
}



unsigned long   TTF_MEMCTRL_CCORE_AddrInit(void)
{
    TTF_MEMCTRL_AddrInit();

    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_CIPHER_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_BBP_MASTER_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);
    TTF_MEMCTRL_SET_TYPE_FLG(TTF_MEMCTRL_CCORE_POOL_ADDR_TYPE, TTF_MEMCTRL_TYPE_VISIBLE_FLG);


    return 0;
}


unsigned long  TTF_MEMCTRL_GetOffsetBaseLen(unsigned long  ulType)
{
    unsigned long                          ulAttribute;


    if (ulType >= TTF_MEMCTRL_ADDR_TYPE_BUTT)
    {
        vos_printf("TTF_MEMCTRL_GetOffsetBaseLen::ulType:%d is invalid!\n", ulType);

        return 0;
    }

    if (TTF_MEMCTRL_TYPE_INIT_FLG != TTF_MEMCTRL_GET_ADDR_INIT_FLG())
    {
        vos_printf("TTF_MEMCTRL_GetOffsetBaseLen::addr is not init!\n");

        return 0;
    }

    ulAttribute = TTF_MEMCTRL_GET_TYPE_ATTRIBUTE(ulType);
    if ((TTF_MEMCTRL_TYPE_EXIST_FLG == (TTF_MEMCTRL_TYPE_EXIST_FLG & ulAttribute))
            && (TTF_MEMCTRL_TYPE_VISIBLE_FLG == (TTF_MEMCTRL_TYPE_VISIBLE_FLG & ulAttribute)))
    {
        return TTF_MEMCTRL_GET_TYPE_OFFSET_BASE_LEN(ulType);
    }
    else
    {
        vos_printf("TTF_MEMCTRL_GetOffsetBaseLen::ulType:%d, ulAttribute:%d is not exist or not visible!\n",
                    ulType, ulAttribute);

        return 0;
    }

}



unsigned long  TTF_MEMCTRL_GetTypeAddr(unsigned long ulAddr, unsigned long  ulType)
{
    unsigned long                       ulOffsetBaseLen;
    unsigned long                       ulTtfMemCtrlTypeAddr = 0;


    if (ulType >= TTF_MEMCTRL_ADDR_TYPE_BUTT)
    {
        vos_printf("TTF_MEMCTRL_GetTypeAddr::ulType:%d is invalid!\n", ulType);
        return 0;
    }

    ulOffsetBaseLen         = TTF_MEMCTRL_GetOffsetBaseLen(ulType);
    ulTtfMemCtrlTypeAddr    = ulAddr + ulOffsetBaseLen;


    return  ulTtfMemCtrlTypeAddr;
}



void TTF_MEMCTRL_PrintAddrType(void)
{
    unsigned char                       ucTypeLoop;


    vos_printf("TTF Mem Ctrl Addr Init is :%d.\r\n", TTF_MEMCTRL_GET_ADDR_INIT_FLG());
    vos_printf("TTF Mem Ctrl Type Print :\r\n");

    for(ucTypeLoop = 0; ucTypeLoop < TTF_MEMCTRL_ADDR_TYPE_BUTT; ucTypeLoop++)
    {
        vos_printf("TTF Mem Type [%d]: -- ulAttribute [%d] -- ulLen [%d] -- ulOffsetBaseLen[%d]\r\n",
            ucTypeLoop, TTF_MEMCTRL_GET_TYPE_ATTRIBUTE(ucTypeLoop),
            TTF_MEMCTRL_GET_TYPE_LEN(ucTypeLoop), TTF_MEMCTRL_GET_TYPE_OFFSET_BASE_LEN(ucTypeLoop));
    }

    vos_printf("TTF Mem Ctrl Type Print END.\r\n");


    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


