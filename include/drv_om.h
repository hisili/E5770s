

#ifndef __DRV_OM_H__
#define __DRV_OM_H__


#ifdef __cplusplus
extern "C" {
#endif

#include "drv_comm.h"


/*************************OM START**********************************/

#define PS_L2_UL_TRACE           (0)
#define PS_L2_DL_TRACE           (1)

#define PROCESS_ENTER(pADDRESS)  do { } while (0)
#define PROCESS_EXIT(pADDRESS)   do { } while (0)

typedef enum{
     ADDRTYPE8BIT,
     ADDRTYPE16BIT,
     ADDRTYPE32BIT
}ENADDRTYPE;

typedef enum{
     BSP_MODEM_CORE         = 0,
     BSP_APP_CORE
}BSP_CORE_TYPE_E;


/*****************************************************************************
  ���������ϱ�������������
*****************************************************************************/
typedef BSP_S32 (*log_bin_ind_cb)(BSP_S32 str_id, BSP_VOID* ind_data, BSP_U32 ind_data_size);

/******************************************************************************
* Function     :   BSP_OM_RegRead
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_RegRead(BSP_U32 u32RegAddr, ENADDRTYPE enAddrType, BSP_U32 *pu32Value);


/******************************************************************************
* Function     :   BSP_OM_RegWrite
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_S32 BSP_OM_RegWrite(BSP_U32 u32RegAddr, ENADDRTYPE enAddrType, BSP_U32 u32Value);

/*****************************************************************************
* �� �� ��  : ddmPhaseScoreBoot
*
* ��������  : �ϲ���õĴ���ʱ����
*
* �������  : phaseName:��㺯������
*             param:    ��㺯�������к�
* �������  : ��
*
* �� �� ֵ  : 0 �ɹ�;���� ʧ��
*****************************************************************************/
#define ddmPhaseScoreBoot ddm_phase_boot_score
extern int ddm_phase_boot_score(const char * phaseName, unsigned int param);

/*****************************************************************************
* �� �� ��  : DRV_OM_SET_HSO_CONN_FLAG
*
* ��������  : flag :���ӱ�־��1��ʾ���ӣ�0��ʾ�Ͽ�
*
* �������  :��
*
*
* �������  :��
*
* �� �� ֵ  :��
*****************************************************************************/
BSP_VOID DRV_OM_SET_HSO_CONN_FLAG(BSP_U32 flag);

/*****************************************************************************
* �� �� ��  : DRV_SYSVIEW_SWT_SET
*
* ��������  :sysview�ϱ��������ã���װ�������ṩ��MSPʹ��
*
* �������  :tarce_type :trace����
*                        set_swt  :����ֵ
*                       period  :�ϱ�����
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK
*****************************************************************************/

BSP_U32 DRV_SYSVIEW_SWT_SET(BSP_U32 set_type,BSP_U32 set_swt,BSP_U32 period);

/*****************************************************************************
* �� �� ��  : DRV_GET_ALL_TASK_ID_NAME
*
* ��������  :��ȡ��ǰ���������ID������
*
* �������  :p_task_stru:�������ƺ�ID����Ľṹ��
*                       param_len:����1�ĳ��ȣ���λ�ֽ�
*
*
* �������  : ��
*
* �� �� ֵ  : BSP_OK
*****************************************************************************/
BSP_U32 DRV_GET_ALL_TASK_ID_NAME(BSP_VOID *p_task_stru,BSP_U32 param_len);

/*****************************************************************************
* �� �� ��  : DRV_INT_LOCK
*
* ��������  :���жϽӿڣ��������ж�ͳ��
*
* �������  :��
*
* �������  : ��
*
* �� �� ֵ  : ���жϺ��õ�key
*****************************************************************************/
BSP_S32 DRV_INT_LOCK(BSP_VOID);

/*****************************************************************************
* �� �� ��  : DRV_INT_UNLOCK
*
* ��������  : �����жϽӿڣ��������ж�ͳ��
*
* �������  : LockKey ���жϺ��õ�key
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
BSP_VOID DRV_INT_UNLOCK(BSP_S32 LockKey);

/*****************************************************************************
* �� �� ��  : DRV_SOCP_CHAN_ENABLE
*
* ��������  : ����SOCPͨ��ʹ�ܲ���
*
* �������  : ��
*
*
* �������  :��
*
* �� �� ֵ  :��
*****************************************************************************/

BSP_VOID DRV_SOCP_CHAN_ENABLE(BSP_VOID);

/******************************************************************************
* Function     :   BSP_OM_SoftReboot
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
BSP_VOID BSP_OM_SoftReboot(void);

/*****************************************************************************
* �� �� ��  : BSP_GetHostCore
*
* ��������  : ��ѯ��ǰCPU���Ӻ�����
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : CPU���Ӻ�����
*
* ����˵��  : ��
*
*****************************************************************************/
BSP_CORE_TYPE_E BSP_GetHostCore(BSP_VOID);

typedef struct tagBSP_OM_NET_S
{
    BSP_U32 u32NetRxStatOverFlow;       /* ����FIFO���ͳ�Ƽ��� */
    BSP_U32 u32NetRxStatPktErr;         /* �����ܴ������ */
    BSP_U32 u32NetRxStatCrcErr;         /* ����CRC������� */
    BSP_U32 u32NetRxStatLenErr;         /* ������Ч���Ȱ����� */
    BSP_U32 u32NetRxNoBufInt;           /* ����û��BUFFER�жϼ��� */
    BSP_U32 u32NetRxStopInt;            /* ����ֹͣ�жϼ��� */
    BSP_U32 u32NetRxDescErr;            /* �������������� */

    BSP_U32 u32NetTxStatUnderFlow;      /* ����FIFO����ͳ�Ƽ��� */
    BSP_U32 u32NetTxUnderFlowInt;       /* ����FIFO�����жϼ��� */
    BSP_U32 u32NetTxStopInt;            /* ����ֹͣ�жϼ��� */
    BSP_U32 u32NetTxDescErrPs;          /* ��������������(Ps) */
    BSP_U32 u32NetTxDescErrOs;          /* ��������������(Os) */
    BSP_U32 u32NetTxDescErrMsp;         /* ��������������(Msp) */

    BSP_U32 u32NetFatalBusErrInt;      /* ���ߴ���*/
}BSP_OM_NET_S;

/******************************************************************************
* Function     :   BSP_OM_NET
*
* Description  :
*
* Input        :
*
* Output       :   ��
*
* return       :
******************************************************************************/
static INLINE BSP_VOID BSP_OM_NET(BSP_OM_NET_S *pstNetOm)
{
	pstNetOm = pstNetOm;
}

/*****************************************************************************
* �� �� ��  : BSP_GetMacAddr
*
* ��������  : ��ȡps mac��ַ
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : VOID
*
* �޸ļ�¼  : 2009��9��2��   lvhui  creat
*****************************************************************************/
static INLINE BSP_U8* BSP_GetMacAddr(void)  //clean warning
{
    /* LTEЭ��ջMAC��ַ */
    static BSP_U8  g_mac_address_pstable[] =
    {
        //0x00,0x1a,0x2b,0x3c,0x4d,0x5f
        0x4c,0x54,0x99,0x45,0xe5,0xd5
    };

    return g_mac_address_pstable;
}

#define DRV_MSP_PROC_REG(eFuncID, pFunc)


int DRV_GET_FS_ROOT_DIRECTORY(char * data, unsigned int len);


/*************************OM END  **********************************/


#ifdef __cplusplus
}
#endif

#endif

