

/*****************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include <linux/dma-mapping.h>
//#include "edmacIP.h"
//#include "edmacDrv.h"
#include <linux/kernel.h>
#include "DrvInterface.h"
#include "pcm_voip_dma.h"
#include "pcm_voip_sio.h"
#include "pcm_voip_ctrl.h"
#include <linux/miscdevice.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/delay.h>

#include <linux/string.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/earlysuspend.h>
#include <linux/miscdevice.h>
#include <linux/clk.h>
#include <linux/jiffies.h>
#include <asm/irq.h>
#include <mach/irqs.h>
#include <linux/spi/spi.h>
#include <linux/platform_device.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>
#include "drv_edma.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif



BSP_S16                              *g_psMedCtrlPcmMicIn;                    /*ָ��ǰMic�����PCM����Buffer��ָ��*/
BSP_S16                              *g_psMedCtrlPcmSpkOut;                   /*ָ��ǰ�����Speaker��PCM����Buffer��ָ��*/
BSP_S16                               g_shwMedCtrlPcmFrameLength;             /* PCM����֡���� */
/* DMAͨ�����ò����ṹ��ȫ�ֱ��� */
UCOM_ALIGN(32)
DRV_DMA_CXCFG_STRU * g_pPcmInDmaPara[2];
UCOM_ALIGN(32)
DRV_DMA_CXCFG_STRU * g_pPcmOutDmaPara[2];
BSP_U32 g_ulPcmInDmaParaPhy[2];
BSP_U32 g_ulPcmOutDmaParaPhy[2];

BSP_U32 g_ulMicIn_BuffPhyA;
BSP_U32 g_ulMicIn_BuffPhyB;
BSP_U32 g_ulSpkOut_BuffPhyA;
BSP_U32 g_ulSpkOut_BuffPhyB;


MED_CTRL_PCM_BUFFER_STRU             *g_stMedCtrlPcmBuff;

MED_CTRL_PCM_DMA_FLAG_STRU             g_DMA_Ctrl_Flag ;

extern int slic_pcm_spkout(char *dma_buf,int limit);
extern int slic_pcm_micin(char *dma_buf,int limit);

/*****************************************************************************
   3 �ⲿ��������
******************************************************************************/


/*****************************************************************************
   4 ����ʵ��
******************************************************************************/

BSP_VOID MED_CTRL_PcmInit(BSP_VOID)
{
    BSP_U32 ulInDmaCfgPhy = 0;
    BSP_U32 ulOutDmaCfgPhy = 0;
    DRV_DMA_CXCFG_STRU *pstInDmaCfg = BSP_NULL;
    DRV_DMA_CXCFG_STRU *pstOutDmaCfg = BSP_NULL;
    MED_CTRL_PCM_BUFFER_STRU *pstPcmBuff = BSP_NULL;
    BSP_U32 ulPcmBuffAddrPhy = 0;
	
    //printk("enter MED_CTRL_PcmInit\n");

	pstInDmaCfg = (DRV_DMA_CXCFG_STRU *)dma_alloc_coherent(BSP_NULL,
                                    (2 * sizeof(DRV_DMA_CXCFG_STRU)),
                                    &ulInDmaCfgPhy,
                                    GFP_DMA|__GFP_WAIT);

    g_pPcmInDmaPara[0] = pstInDmaCfg;
    g_pPcmInDmaPara[1] = pstInDmaCfg + 1;
    g_ulPcmInDmaParaPhy[0] = ulInDmaCfgPhy;
    g_ulPcmInDmaParaPhy[1] = ulInDmaCfgPhy + sizeof(DRV_DMA_CXCFG_STRU);

    /*
    printk("1, g_pastPcmInDmaPara[0]=%p\n, g_pastPcmInDmaPara[1]=%p\n, g_aulPcmInDmaParaPhy[0]=0x%x\n, g_aulPcmInDmaParaPhy[1]=0x%x\n",
                    g_pPcmInDmaPara[0],
                    g_pPcmInDmaPara[1],
                    g_ulPcmInDmaParaPhy[0],
                    g_ulPcmInDmaParaPhy[1]);
                    */


    pstOutDmaCfg = (DRV_DMA_CXCFG_STRU *)dma_alloc_coherent(BSP_NULL,
                                    (2 * sizeof(DRV_DMA_CXCFG_STRU)),
                                    &ulOutDmaCfgPhy,
                                    GFP_DMA|__GFP_WAIT);

    g_pPcmOutDmaPara[0] = pstOutDmaCfg;
    g_pPcmOutDmaPara[1] = pstOutDmaCfg + 1;
    g_ulPcmOutDmaParaPhy[0] = ulOutDmaCfgPhy;
    g_ulPcmOutDmaParaPhy[1] = ulOutDmaCfgPhy + sizeof(DRV_DMA_CXCFG_STRU);

    /*
    printk("2, g_pastPcmOutDmaPara[0]=%p\n, g_pastPcmOutDmaPara[1]=%p\n, g_aulPcmOutDmaParaPhy[0]=0x%x\n, g_aulPcmOutDmaParaPhy[1]=0x%x\n",
                    g_pPcmOutDmaPara[0],
                    g_pPcmOutDmaPara[1],
                    g_ulPcmOutDmaParaPhy[0],
                    g_ulPcmOutDmaParaPhy[1]);
                    */

    pstPcmBuff = (MED_CTRL_PCM_BUFFER_STRU *)dma_alloc_coherent(BSP_NULL,
                                    sizeof(MED_CTRL_PCM_BUFFER_STRU),
                                    &ulPcmBuffAddrPhy,
                                    GFP_DMA|__GFP_WAIT);

    g_stMedCtrlPcmBuff = pstPcmBuff;
    g_ulMicIn_BuffPhyA = ulPcmBuffAddrPhy;
    g_ulMicIn_BuffPhyB = g_ulMicIn_BuffPhyA   + MED_CTRL_PCM_MAX_FRAME_LENGTH * sizeof(BSP_S16);
    g_ulSpkOut_BuffPhyA = g_ulMicIn_BuffPhyB  + MED_CTRL_PCM_MAX_FRAME_LENGTH * sizeof(BSP_S16);
    g_ulSpkOut_BuffPhyB = g_ulSpkOut_BuffPhyA + MED_CTRL_PCM_MAX_FRAME_LENGTH * sizeof(BSP_S16);

    /*
    printk("3, g_stMedCtrlPcmBuff=ox%p\n, g_ulMicIn_BuffPhyA=0x%p\n, g_ulMicIn_BuffPhyB=0x%p\n, g_ulSpkOut_BuffPhyA=0x%p\n,g_ulSpkOut_BuffPhyB=0x%p\n",
	                 g_stMedCtrlPcmBuff,
	                 g_ulMicIn_BuffPhyA,
                    g_ulMicIn_BuffPhyB,
                    g_ulSpkOut_BuffPhyA,
                    g_ulSpkOut_BuffPhyB);
                    */
    g_psMedCtrlPcmMicIn  = g_stMedCtrlPcmBuff->asMicInBuffA;
    g_psMedCtrlPcmSpkOut = g_stMedCtrlPcmBuff->asSpkOutBuffA;
	

   
     //printk("exit MED_CTRL_PcmInit\n ");

}

BSP_VOID MED_CTRL_PcmSwitchMicBuff(BSP_VOID)
{
    BSP_U32      ulOffset = 0;
    BSP_U32      ulDestAddr = 0;
	BSP_U32      ulDestAddrB = 0;   /* MIC�ɼ���DMAͨ����Ŀ�ĵ�ַ */

   
    ulOffset = ((BSP_S32)MED_CTRL_PCM_FRAME_LENGTH * sizeof(BSP_S16)) - sizeof(BSP_U32);

    ulDestAddrB = (BSP_S32)g_ulMicIn_BuffPhyB;

    /*��ȡͨ��0Ŀ�ĵ�ַ�Ĵ���*/
     BSP_REG_READ(DRV_DMA_CX_DES_ADDR(MED_CTRL_MC_DMAC_CHN_MIC),0,ulDestAddr);

	/*��Ŀ�ĵ�ַ�Ѿ�ΪBufferB��Χ��(LOOPģʽ)��Ŀ�ĵ�ַΪBufferA�����һ��λ��(��LOOPģʽ)*/
    /*���߼�������BufferA��BufferB��ַ��������BufferA��ǰ*/
    if ( (ulDestAddr >= (ulDestAddrB - sizeof(BSP_U32)))
        &&(ulDestAddr < (ulDestAddrB + ulOffset)) )
    {
        g_psMedCtrlPcmMicIn = g_stMedCtrlPcmBuff->asMicInBuffA;
    }
    else
    {
        g_psMedCtrlPcmMicIn = g_stMedCtrlPcmBuff->asMicInBuffB;
    }
}
BSP_S16* MED_CTRL_PcmGetWritableSpkBuffPtr(BSP_VOID)
{
    BSP_U32      ulOffset   = 0;
    BSP_U32      ulSrcAddr  = 0;
	BSP_U32      ulSrcAddrB = 0;   /* SPK���ŵ�DMAͨ����Դ��ַ */

   
    ulOffset = ((BSP_S32)MED_CTRL_PCM_FRAME_LENGTH * sizeof(BSP_S16)) - sizeof(BSP_U32);


    ulSrcAddrB  = (BSP_S32)g_ulSpkOut_BuffPhyB;
  
    /*��ȡͨ��1Դ��ַ�Ĵ���*/
    BSP_REG_READ(DRV_DMA_CX_SRC_ADDR(MED_CTRL_MC_DMAC_CHN_SPK),0,ulSrcAddr);

	/*��Դ��ַ�Ѿ�ΪBufferB��Χ��(LOOPģʽ)��Դ��ַΪBufferA�����һ��λ��(��LOOPģʽ)*/
    /*���߼�������BufferA��BufferB��ַ��������BufferA��ǰ*/
    if((ulSrcAddr >= (ulSrcAddrB - sizeof(BSP_U32)))
        &&(ulSrcAddr < (ulSrcAddrB + ulOffset)) )
    {
        return g_stMedCtrlPcmBuff->asSpkOutBuffA;
    }
    else
    {
        return g_stMedCtrlPcmBuff->asSpkOutBuffB;
    }
}
	
BSP_VOID MED_CTRL_PcmSwitchSpkBuff(BSP_VOID)
{   
   g_psMedCtrlPcmSpkOut = MED_CTRL_PcmGetWritableSpkBuffPtr();   

}

BSP_VOID MED_CTRL_PcmClrLastSpkBuff(BSP_VOID)
{

    BSP_U16 usBufLen = (BSP_U16)MED_CTRL_PCM_FRAME_LENGTH * sizeof(BSP_U16);

    memset(MED_CTRL_PcmGetWritableSpkBuffPtr(),
                0,
                usBufLen);
}


BSP_U32 MED_CTRL_PcmMicInStartLoopDMA(BSP_U16 usChNum)
{
    BSP_U32              uwRet= BSP_ERROR;
    BSP_U32              uwDestAddrA, uwDestAddrB;   /* MIC�ɼ���DMAͨ����Ŀ�ĵ�ַ */
 
    DRV_DMA_CXCFG_STRU *pstLLiAddrA = BSP_NULL;
    DRV_DMA_CXCFG_STRU *pstLLiAddrB = BSP_NULL;
    if (usChNum >= DRV_DMA_MAX_CHANNEL_NUM)
    {
        
        return BSP_ERROR;
    }
    
    /* ��ֹMIC�ɼ���DMA */
    DRV_DMA_Stop_A(usChNum);
   
    /*�л�buffer������DestAddr��ֵ*/
    if ( g_psMedCtrlPcmMicIn == g_stMedCtrlPcmBuff->asMicInBuffA)
    {      
		uwDestAddrA = (BSP_U32)g_ulMicIn_BuffPhyB;
        uwDestAddrB = (BSP_U32)g_ulMicIn_BuffPhyA;			
    }
    else
    {
       
		 uwDestAddrA = (BSP_U32)g_ulMicIn_BuffPhyA;
         uwDestAddrB = (BSP_U32)g_ulMicIn_BuffPhyB;		 
    }
	
    pstLLiAddrA = (DRV_DMA_CXCFG_STRU *)g_pPcmInDmaPara[0];
    pstLLiAddrB = (DRV_DMA_CXCFG_STRU *)g_pPcmInDmaPara[1];
	
    memset(g_pPcmInDmaPara[0], 0, sizeof(DRV_DMA_CXCFG_STRU));
	memset(g_pPcmInDmaPara[1], 0, sizeof(DRV_DMA_CXCFG_STRU));
  
    /*����DMA���ò���,����Ϊ�������ӣ�ʹ��MICͨ��LOOP���ã�ÿ���ڵ��ϱ�һ���ж�*/
    pstLLiAddrA->uwLli            = DRV_DMA_LLI_LINK((BSP_U32)g_ulPcmInDmaParaPhy[1]);
    pstLLiAddrA->uhwACount        = (BSP_U16)MED_CTRL_PCM_MAX_FRAME_LENGTH;
    pstLLiAddrA->uwSrcAddr        = SIO_BASE_ADDR_PHY+0x58;//DRV_SIO_PCM_RD;
    pstLLiAddrA->uwDstAddr        = uwDestAddrA;
    pstLLiAddrA->uwConfig         = DRV_DMA_SIO_MEM_CFG;

    pstLLiAddrB->uwLli            = DRV_DMA_LLI_LINK((BSP_U32)g_ulPcmInDmaParaPhy[0]);
    pstLLiAddrB->uhwACount        = (BSP_U16)MED_CTRL_PCM_MAX_FRAME_LENGTH;
    pstLLiAddrB->uwSrcAddr        = SIO_BASE_ADDR_PHY+0x58;
    pstLLiAddrB->uwDstAddr        = uwDestAddrB;
    pstLLiAddrB->uwConfig         = DRV_DMA_SIO_MEM_CFG;

    /*����MIC�ɼ�DMAͨ���������ݰ��ˣ���ע��MIC��DMA�жϴ�����*/
    uwRet = DRV_DMA_StartWithCfg_A(usChNum,
                                 g_pPcmInDmaPara[0],
                                 MED_CTRL_MicDmaIsr,
                                 0);

    return uwRet;
}

BSP_U32 MED_CTRL_PcmSpkOutStartLoopDMA(BSP_U16 usChNum)
{
    BSP_U32              uwRet = BSP_ERROR;
    BSP_U32              uwSrcAddrA, uwSrcAddrB;   /* SPK���ŵ�DMAͨ����Դ��ַ */
    DRV_DMA_CXCFG_STRU *pstLLiAddrA = BSP_NULL;
    DRV_DMA_CXCFG_STRU *pstLLiAddrB = BSP_NULL;
    /* �������Ƿ�Ƿ�,ͨ����0-15 */
    if (usChNum >= DRV_DMA_MAX_CHANNEL_NUM)
    {
        
        return BSP_ERROR;
    }

    /* ��ֹSPK���ŵ�DMA */
    DRV_DMA_Stop_A(usChNum);
 

    /*�л�buffer������DestAddr��ֵ*/
    if (g_psMedCtrlPcmSpkOut == g_stMedCtrlPcmBuff->asSpkOutBuffA)
    {
        uwSrcAddrA = (BSP_U32)g_ulSpkOut_BuffPhyB;
        uwSrcAddrB = (BSP_U32)g_ulSpkOut_BuffPhyA;
    }
    else
    {
        uwSrcAddrA = (BSP_U32)g_ulSpkOut_BuffPhyA;
        uwSrcAddrB = (BSP_U32)g_ulSpkOut_BuffPhyB;
    }

	pstLLiAddrA = (DRV_DMA_CXCFG_STRU *)g_pPcmOutDmaPara[0];
    pstLLiAddrB = (DRV_DMA_CXCFG_STRU *)g_pPcmOutDmaPara[1];	

    memset(g_pPcmOutDmaPara[0], 0, sizeof(DRV_DMA_CXCFG_STRU));
	memset(g_pPcmOutDmaPara[1], 0, sizeof(DRV_DMA_CXCFG_STRU)); 
    /*����DMA���ò���,����Ϊ�������ӣ�ʹ��SPKͨ��LOOP���ã�ÿ���ڵ��ϱ�һ���ж�*/
    pstLLiAddrA->uwLli     = DRV_DMA_LLI_LINK((BSP_U32)g_ulPcmOutDmaParaPhy[1]);
    pstLLiAddrA->uhwACount = (BSP_U16)MED_CTRL_PCM_MAX_FRAME_LENGTH;
    pstLLiAddrA->uwSrcAddr = uwSrcAddrA;
    pstLLiAddrA->uwDstAddr = SIO_BASE_ADDR_PHY+0x50;//DRV_SIO_PCM_XD;
    pstLLiAddrA->uwConfig  = DRV_DMA_MEM_SIO_CFG;

    pstLLiAddrB->uwLli     = DRV_DMA_LLI_LINK((BSP_U32)g_ulPcmOutDmaParaPhy[0]);
    pstLLiAddrB->uhwACount = (BSP_U16)MED_CTRL_PCM_MAX_FRAME_LENGTH;
    pstLLiAddrB->uwSrcAddr = uwSrcAddrB;
    pstLLiAddrB->uwDstAddr = SIO_BASE_ADDR_PHY+0x50;
    pstLLiAddrB->uwConfig  = DRV_DMA_MEM_SIO_CFG;

  
    /*����SPEAKER����DMAͨ�����в��ŵ����е����ݰ���, ��ע��MIC/SPK��DMA�жϴ�����*/
    uwRet = DRV_DMA_StartWithCfg_A(usChNum,
                                 g_pPcmOutDmaPara[0],
                                 MED_CTRL_SpkDmaIsr,                               
                                 0);

    return uwRet;
}


BSP_VOID MED_CTRL_PcmChkSpkConflick(BSP_VOID)
{
        /* ��SpkOut��DMA�ж�ʱ�̼�⵽��δ���յ��µ��������ݣ�����Ϊ����ʱ���ͻ */
        if (MED_SWITCH_OFF == g_DMA_Ctrl_Flag.usSpkOutSwEnable)
        {
          // MED_CTRL_PcmSpkOutStartLoopDMA();
        }
        /* ��δ���ֳ�ͻ,���־��֡����������ʹ�� */
        else
        {
            g_DMA_Ctrl_Flag.usSpkOutSwEnable = MED_SWITCH_OFF;
        }
   
}

BSP_VOID MED_CTRL_MicDmaIsr(
                DRV_DMA_INT_TYPE_ENUM_UINT16 enIntType,
                BSP_U32 uwPara)
{   
    /* ���ж�����ΪTC�ж�,ΪMic��DMA�����жϴ������� */
    if ((DRV_DMA_INT_TYPE_TC1 == enIntType)
        ||(DRV_DMA_INT_TYPE_TC2 == enIntType))
    {
       
           if (MED_SWITCH_ON == g_DMA_Ctrl_Flag.usMicInSwEnable)
           {
                /* �л����л����� */
                MED_CTRL_PcmSwitchMicBuff();

				g_DMA_Ctrl_Flag.usMicInSwEnable = MED_SWITCH_OFF ;
               //֪ͨ�ϲ�ȡ���� ���ýӿڿ�����������                
                slic_pcm_micin((char *)g_psMedCtrlPcmMicIn,MED_CTRL_PCM_MAX_FRAME_LENGTH);
                memset(g_psMedCtrlPcmMicIn,0,MED_CTRL_PCM_MAX_FRAME_LENGTH*2);
                g_DMA_Ctrl_Flag.usMicInSwEnable = MED_SWITCH_ON ;
            }
		    else
		    {
		        printk("MicIn a frame data will be lost\n");
		    }
          
  
    }
    /* ���ж�����ΪERROR�ж�,��¼�쳣 */
    else
    {
        /*��¼�쳣������DMA Error�ж�*/      
        printk("MED_CTRL_MicDmaIsr ,ISQ failed\n");
    }   
 
}

BSP_VOID MED_CTRL_SpkDmaIsr(
                DRV_DMA_INT_TYPE_ENUM_UINT16 enIntType,
                BSP_U32 uwPara)
{
     /* ���ж�����ΪTC�ж�,ΪSPK��DMA�����жϴ������� */
    if ((DRV_DMA_INT_TYPE_TC1 == enIntType)
        ||(DRV_DMA_INT_TYPE_TC2 == enIntType))
    {
            if (MED_SWITCH_ON == g_DMA_Ctrl_Flag.usSpkOutSwEnable)
            {
                /* �л����л����� */
                MED_CTRL_PcmSwitchSpkBuff();

				g_DMA_Ctrl_Flag.usSpkOutSwEnable = MED_SWITCH_OFF;
				slic_pcm_spkout((char *)g_psMedCtrlPcmSpkOut,MED_CTRL_PCM_MAX_FRAME_LENGTH);
				g_DMA_Ctrl_Flag.usSpkOutSwEnable = MED_SWITCH_ON;
            }
            else
            {
               printk("SpkOut can not get a frame data \n");
                /* �����һ֡�������� */
               MED_CTRL_PcmClrLastSpkBuff();
				
            }

            /* ����ʱ���� */
           // MED_CTRL_PcmChkSpkConflick();
            
     
    }
    /* ���ж�����ΪERROR�ж�,��¼�쳣 */
    else
    {
        /*��¼�쳣������DMA Error�ж�*/
		printk("MED_CTRL_SpkDmaIsr,ISQ failed\n");       
    }

}

BSP_VOID MED_PCM_Ctrl_Init(BSP_VOID)
{
     DRV_DMA_Init_A();
     #if 0
     DRV_SIO_Init_A();
     #endif
     MED_CTRL_PcmInit();
}
BSP_VOID MED_PCM_Ctrl_UnInit(BSP_VOID)
{
    	 
	dma_free_coherent(BSP_NULL,(2 * sizeof(DRV_DMA_CXCFG_STRU)),g_pPcmInDmaPara[0],g_ulPcmInDmaParaPhy[0]);
	dma_free_coherent(BSP_NULL,(2 * sizeof(DRV_DMA_CXCFG_STRU)),g_pPcmOutDmaPara[0],g_ulPcmOutDmaParaPhy[0]);
	dma_free_coherent(BSP_NULL,(2 * sizeof(DRV_DMA_CXCFG_STRU)),g_stMedCtrlPcmBuff,g_ulMicIn_BuffPhyA);
}

BSP_VOID MED_PCM_Ctrl_Start(BSP_VOID)
{
    /* ���ò�����ģʽ��һ֡PCM�������� */
       memset(&g_DMA_Ctrl_Flag,0,sizeof(MED_CTRL_PCM_DMA_FLAG_STRU));
      g_DMA_Ctrl_Flag.usMicInSwEnable =  MED_SWITCH_ON;
	  g_DMA_Ctrl_Flag.usSpkOutSwEnable = MED_SWITCH_ON;
      #if 0
        /* ����DRV_SIO_Open�ӿڣ���SIO�豸 */
      DRV_SIO_Open_A((enMask | DRV_SIO_INT_MASK_TX_RIGHT_FIFO_UNDER),
                     NULL,
                     0);
      #endif
    MED_CTRL_PcmMicInStartLoopDMA(MED_CTRL_MC_DMAC_CHN_MIC); 
    msleep(2);
    MED_CTRL_PcmSpkOutStartLoopDMA(MED_CTRL_MC_DMAC_CHN_SPK);
}

BSP_VOID MED_PCM_Ctrl_Stop(BSP_VOID)
{
    DRV_DMA_Stop_A(MED_CTRL_MC_DMAC_CHN_MIC);
    DRV_DMA_Stop_A(MED_CTRL_MC_DMAC_CHN_SPK);
    #if 0 
    DRV_SIO_Close_A();
    #endif
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

