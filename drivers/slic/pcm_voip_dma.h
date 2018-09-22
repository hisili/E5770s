

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __DRV_DMA_H__
#define __DRV_DMA_H__

#include <linux/kernel.h>
#include "DrvInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* 2.1 �ⲿֱ�����ö��� */
#define DRV_DMA_LLI_LINK(uwAddr)        (((uwAddr) & 0xffffffe0UL) | (0x2UL))   /* ��������LLI������ */
#define DRV_DMA_LLI_CHAN(uhwChanNo)     (((BSP_U32)(uhwChanNo) << 8)|(0x1UL))/* ͨ������LLI������ */
#define DRV_DMA_LLI_DISABLE             (0x0UL)                                 /* ����ģʽ��ʹ�������� */

#define DRV_DMA_MEM_SIO_CFG             (0x83311057)                            /* ���͵�MEM->SIO��DMA���ã�Դ��ַ������16bitλ��burst4 */
#define DRV_DMA_SIO_MEM_CFG             (0x43311047)                            /* ���͵�SIO->MEM��DMA���ã�Ŀ�ĵ�ַ������16bitλ��burst4 */
#define DRV_DMA_MEM_MEM_CFG             (0xfff33003)                            /* ���͵�MEM->MEM��DMA���ã���ַ˫�������64bitλ��burst1  */

#define SC_DMA_SEL_CTRL_ADDR    (0x900004E0U)
#define DMA_BASE_ADDR_PHY       (0x90024000U)
#define DMA_SIZE                (0x1000)
extern BSP_U32 g_uldmaBaseAddr ;
/* 2.2 �ڲ����ö��� */
#define DRV_DMA_MAX_CHANNEL_NUM         (16)                                    /* ���ͨ����                              */
#define DRV_DMA_INT_NO_HIFI             (120)                                    /* HIFI��EDMA�жϵ��жϱ��                */
#define DRV_DMA_BASE_ADDR               (g_uldmaBaseAddr)

#define DRV_DMA_CPU_NO_HIFI             (1)                                     /* EDMA��HIFI���������                    */
#define DRV_DMA_INT_STAT(i)             (DRV_DMA_BASE_ADDR+(       (0x40*i)))  /* ������i���ж�״̬�Ĵ���                 */
#define DRV_DMA_INT_TC1(i)              (DRV_DMA_BASE_ADDR+(0x0004+(0x40*i)))  /* ������i��ͨ����������ж�״̬�Ĵ���     */
#define DRV_DMA_INT_TC2(i)              (DRV_DMA_BASE_ADDR+(0x0008+(0x40*i)))  /* ������i������ڵ㴫������ж�״̬�Ĵ��� */
#define DRV_DMA_INT_ERR1(i)             (DRV_DMA_BASE_ADDR+(0x000c+(0x40*i)))  /* ������i�����ô����ж�״̬�Ĵ���         */
#define DRV_DMA_INT_ERR2(i)             (DRV_DMA_BASE_ADDR+(0x0010+(0x40*i)))  /* ������i�����ݴ�������ж�״̬�Ĵ���     */
#define DRV_DMA_INT_ERR3(i)             (DRV_DMA_BASE_ADDR+(0x0014+(0x40*i)))  /* ������i�Ķ���������ж�״̬�Ĵ���       */
#define DRV_DMA_INT_TC1_MASK(i)         (DRV_DMA_BASE_ADDR+(0x0018+(0x40*i)))  /* ������i��ͨ����������ж����μĴ���     */
#define DRV_DMA_INT_TC2_MASK(i)         (DRV_DMA_BASE_ADDR+(0x001c+(0x40*i)))  /* ������i������ڵ㴫������ж����μĴ��� */
#define DRV_DMA_INT_ERR1_MASK(i)        (DRV_DMA_BASE_ADDR+(0x0020+(0x40*i)))  /* ������i�����ô����ж����μĴ���         */
#define DRV_DMA_INT_ERR2_MASK(i)        (DRV_DMA_BASE_ADDR+(0x0024+(0x40*i)))  /* ������i�����ݴ�������ж����μĴ���     */
#define DRV_DMA_INT_ERR3_MASK(i)        (DRV_DMA_BASE_ADDR+(0x0028+(0x40*i)))  /* ������i�������ȡ�����ж����μĴ���     */
#define DRV_DMA_INT_TC1_RAW             (DRV_DMA_BASE_ADDR+(0x0600))            /* ԭʼͨ����������ж�״̬�Ĵ���          */
#define DRV_DMA_INT_TC2_RAW             (DRV_DMA_BASE_ADDR+(0x0608))            /* ԭʼ����ڵ㴫������ж�״̬�Ĵ���      */
#define DRV_DMA_INT_ERR1_RAW            (DRV_DMA_BASE_ADDR+(0x0610))            /* ԭʼ���ô����ж�״̬�Ĵ���              */
#define DRV_DMA_INT_ERR2_RAW            (DRV_DMA_BASE_ADDR+(0x0618))            /* ԭʼ���ݴ�������ж�״̬�Ĵ���          */
#define DRV_DMA_INT_ERR3_RAW            (DRV_DMA_BASE_ADDR+(0x0620))            /* ԭʼ�����ȡ�����ж�״̬�Ĵ���          */
#define DRV_DMA_SREQ                    (DRV_DMA_BASE_ADDR+(0x0660))            /* ����������Ĵ���                        */
#define DRV_DMA_LSREQ                   (DRV_DMA_BASE_ADDR+(0x0664))            /* ĩ�ε���������Ĵ���                    */
#define DRV_DMA_BREQ                    (DRV_DMA_BASE_ADDR+(0x0668))            /* ͻ����������Ĵ���                      */
#define DRV_DMA_LBREQ                   (DRV_DMA_BASE_ADDR+(0x066C))            /* ĩ��ͻ����������Ĵ���                  */
#define DRV_DMA_FREQ                    (DRV_DMA_BASE_ADDR+(0x0670))            /* ������������Ĵ���                      */
#define DRV_DMA_LFREQ                   (DRV_DMA_BASE_ADDR+(0x0674))            /* ĩ��������������Ĵ���                  */
#define DRV_DMA_CH_PRI                  (DRV_DMA_BASE_ADDR+(0x0688))            /* ���ȼ����ƼĴ���                        */
#define DRV_DMA_CH_STAT                 (DRV_DMA_BASE_ADDR+(0x0690))            /* ȫ��DMA״̬�Ĵ���                       */
#define DRV_DMA_DMA_CTRL                (DRV_DMA_BASE_ADDR+(0x0698))            /* DMAȫ�ֿ��ƼĴ���                       */
#define DRV_DMA_CX_CURR_CNT1(j)         (DRV_DMA_BASE_ADDR+(0x0700+(0x10*j)))  /* ͨ��j����ά����ʣ��size״̬�Ĵ���       */
#define DRV_DMA_CX_CURR_CNT0(j)         (DRV_DMA_BASE_ADDR+(0x0704+(0x10*j)))  /* ͨ��j��һ����ά����ʣ��size״̬�Ĵ���   */
#define DRV_DMA_CX_CURR_SRC_ADDR(j)     (DRV_DMA_BASE_ADDR+(0x0708+(0x10*j)))  /* ͨ��j��Դ��ַ�Ĵ���                     */
#define DRV_DMA_CX_CURR_DES_ADDR(j)     (DRV_DMA_BASE_ADDR+(0x070C+(0x10*j)))  /* ͨ��j��Ŀ�ĵ�ַ�Ĵ���                   */
#define DRV_DMA_CX_LLI(j)               (DRV_DMA_BASE_ADDR+(0x0800+(0x40*j)))  /* ͨ��j�������ַ�Ĵ���                   */
#define DRV_DMA_CX_BINDX(j)             (DRV_DMA_BASE_ADDR+(0x0804+(0x40*j)))  /* ͨ��j�Ķ�ά��ַƫ�������üĴ���         */
#define DRV_DMA_CX_CINDX(j)             (DRV_DMA_BASE_ADDR+(0x0808+(0x40*j)))  /* ͨ��j����ά��ַƫ�������üĴ���         */
#define DRV_DMA_CX_CNT1(j)              (DRV_DMA_BASE_ADDR+(0x080C+(0x40*j)))  /* ͨ��j�Ĵ��䳤��1���üĴ���              */
#define DRV_DMA_CX_CNT0(j)              (DRV_DMA_BASE_ADDR+(0x0810+(0x40*j)))  /* ͨ��j�Ĵ��䳤�����üĴ���               */
#define DRV_DMA_CX_SRC_ADDR(j)          (DRV_DMA_BASE_ADDR+(0x0814+(0x40*j)))  /* ͨ��j��Դ��ַ�Ĵ���                     */
#define DRV_DMA_CX_DES_ADDR(j)          (DRV_DMA_BASE_ADDR+(0x0818+(0x40*j)))  /* ͨ��j��Ŀ�ĵ�ַ�Ĵ���                   */
#define DRV_DMA_CX_CONFIG(j)            (DRV_DMA_BASE_ADDR+(0x081C+(0x40*j)))  /* ͨ��j�����üĴ���                       */
#define DRV_DMA_CX_AXI_CONF(j)          (DRV_DMA_BASE_ADDR+(0x0820+(0x40*j)))  /* ͨ��j��AXI����������üĴ���            */

#define DRV_DMA_INT_STAT_HIFI           (DRV_DMA_INT_STAT(DRV_DMA_CPU_NO_HIFI))         /* ������HIFI���ж�״̬�Ĵ���                 */
#define DRV_DMA_INT_TC1_HIFI            (DRV_DMA_INT_TC1(DRV_DMA_CPU_NO_HIFI))          /* ������HIFI��ͨ����������ж�״̬�Ĵ���     */
#define DRV_DMA_INT_TC2_HIFI            (DRV_DMA_INT_TC2(DRV_DMA_CPU_NO_HIFI))          /* ������HIFI������ڵ㴫������ж�״̬�Ĵ��� */
#define DRV_DMA_INT_ERR1_HIFI           (DRV_DMA_INT_ERR1(DRV_DMA_CPU_NO_HIFI))         /* ������HIFI�����ô����ж�״̬�Ĵ���         */
#define DRV_DMA_INT_ERR2_HIFI           (DRV_DMA_INT_ERR2(DRV_DMA_CPU_NO_HIFI))         /* ������HIFI�����ݴ�������ж�״̬�Ĵ���     */
#define DRV_DMA_INT_ERR3_HIFI           (DRV_DMA_INT_ERR3(DRV_DMA_CPU_NO_HIFI))         /* ������HIFI�Ķ���������ж�״̬�Ĵ���       */
#define DRV_DMA_INT_TC1_MASK_HIFI       (DRV_DMA_INT_TC1_MASK(DRV_DMA_CPU_NO_HIFI))     /* ������HIFI��ͨ����������ж����μĴ���     */
#define DRV_DMA_INT_TC2_MASK_HIFI       (DRV_DMA_INT_TC2_MASK(DRV_DMA_CPU_NO_HIFI))     /* ������HIFI������ڵ㴫������ж����μĴ��� */
#define DRV_DMA_INT_ERR1_MASK_HIFI      (DRV_DMA_INT_ERR1_MASK(DRV_DMA_CPU_NO_HIFI))    /* ������HIFI�����ô����ж����μĴ���         */
#define DRV_DMA_INT_ERR2_MASK_HIFI      (DRV_DMA_INT_ERR2_MASK(DRV_DMA_CPU_NO_HIFI))    /* ������HIFI�����ݴ�������ж����μĴ���     */
#define DRV_DMA_INT_ERR3_MASK_HIFI      (DRV_DMA_INT_ERR3_MASK( DRV_DMA_CPU_NO_HIFI))   /* ������HIFI�������ȡ�����ж����μĴ���     */

#define DRV_DMA_GetCxIsrPtr()           (&g_astDrvDmaCxIntIsr[0])               /* ��ȡDMA�жϴ�����ȫ�ֱ����׵�ַ */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : DRV_DMA_INT_TYPE_ENUM
 ��������  : DMAͨ���ж�����
*****************************************************************************/
enum DRV_DMA_INT_TYPE_ENUM
{
    DRV_DMA_INT_TYPE_TC1 = 0,           /* ͨ�����     */
    DRV_DMA_INT_TYPE_TC2,               /* ���������(�����һ�����) */
    DRV_DMA_INT_TYPE_ERR1,              /* ���ô���     */
    DRV_DMA_INT_TYPE_ERR2,              /* ���ݴ������ */
    DRV_DMA_INT_TYPE_ERR3,              /* ��ȡ������� */
    DRV_DMA_INT_TYPE_BUTT
};
typedef BSP_U16 DRV_DMA_INT_TYPE_ENUM_UINT16;



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 ʵ������  : DRV_DMA_CXCFG_STRU
 ��������  : EMACͨ������ʵ��

LLI�Ĵ�������:
   b31-5, �����ַb31-5, ��32byte����
   b11-8, ����ͨ����
   b1-0,  ͨ������ʹ��, 00-��ʹ��;01-ͨ������;10-��������;

 config�Ĵ�������:
   b31 b30 b29   b28  b27-24 b23-20 b18-16 b14-12 b9-4   b3-2      b1    b0
   si  di smode dmode   sl     dl    sw     dw    peri flow_ctrl itc_en ch_en
 ����,
   sl/dl, src/dest burst len, ȡֵ0000-1111��ʾ����Ϊ1-16
   sw/dw, src/dest width, ȡֵ000-101��ʾ���Ϊ8/16/32/64/128/256bit
   flow_ctrl, 00-M2M;01-M2P;10-M2P��������
*****************************************************************************/
typedef struct
{
   BSP_U32       uwLli;              /* ͨ��Linked List Item��ַ     */
   BSP_U16       uhwDstBIndex;       /* ͨ���Ķ�άĿ�ĵ�ַƫ�������ã�ռ��16bit */
   BSP_U16       uhwSrcBIndex;       /* ͨ���Ķ�άԴ��ַƫ�������ã�ռ��16bit */
   BSP_U16       uhwDstCIndex;       /* ͨ������άĿ�ĵ�ַƫ�������ã�ռ��16bit */
   BSP_U16       uhwSrcCIndex;       /* ͨ������άԴ��ַƫ�������ã�ռ��16bit */
   BSP_U16       uhwCCount;          /* ��ά���䳤������,��λFrame��ռ��16bit   */
   BSP_U16       uhwRsv;             /* ����λ��ռ��16bit                    */
   BSP_U16       uhwACount;          /* һά���䳤������,��λByte��ռ��16bit */
   BSP_U16       uhwBCount;          /* ��ά���䳤������,��λArray��ռ��16bit  */
   BSP_U32       uwSrcAddr;          /* ͨ��Դ��ַ                   */
   BSP_U32       uwDstAddr;          /* ͨ��Ŀ�ĵ�ַ                 */
   BSP_U32       uwConfig;           /* ͨ�����üĴ���               */

} DRV_DMA_CXCFG_STRU;

/*****************************************************************************
 �� �� ��  : DRV_DMA_INT_FUNC
 ��������  : DMA�жϴ���ص�����
 �������  : enIntType - �ж�����, �μ�DRV_DMA_INT_TYPE_ENUM_UINT16
             uwPara    - �û�����
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
typedef BSP_VOID (*DRV_DMA_INT_FUNC)(
                DRV_DMA_INT_TYPE_ENUM_UINT16 enIntType,
                BSP_U32                   uwPara);

/*****************************************************************************
 ʵ������  : DRV_DMA_CXISR_STRU
 ��������  : ����DMAͨ���ص���������ʵ��
*****************************************************************************/
typedef struct
{
    DRV_DMA_INT_FUNC    pfFunc;         /* �ص�����ָ�� */
    BSP_U32          uwPara;         /* �ص�����     */

} DRV_DMA_CXISR_STRU;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern BSP_VOID DRV_DMA_Init_A( BSP_VOID );

extern BSP_U32 DRV_DMA_StartWithCfg_A(
                       BSP_U16              uhwChannelNo,
                       DRV_DMA_CXCFG_STRU     *pstCfg,
                       DRV_DMA_INT_FUNC        pfIntHandleFunc,
                       BSP_U32              uwPara);
extern BSP_VOID DRV_DMA_Stop_A(BSP_U16 uhwChannelNo);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of drv_dma.h */
