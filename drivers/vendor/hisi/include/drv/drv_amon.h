

#ifndef _DRV_AMON_H
#define _DRV_AMON_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "drv_comm.h"


/* Monitor��ء��ɼ�ID�����Ŀ */
#define AXI_MAX_CONFIG_ID	8
#define AXI_MAX_PORT_CNT    8

/* �Ĵ������� */
typedef struct
{
	BSP_U32 	ulRegOffset;		/* �Ĵ���ƫ�� */
	BSP_U32 	ulRegValue;			/* �Ĵ���ֵ */
} AXI_REG_CONFIG_STRU;

/* �ɼ����ûظ� */
typedef struct 
{
	BSP_U32 			ulRegCnt;	/* �Ĵ���������Ŀ */
	AXI_REG_CONFIG_STRU regConfig[0];/* �Ĵ������� */	
} AXI_DATA_CONFIG_CNF_STRU;

/* ������ûָ� */
typedef AXI_DATA_CONFIG_CNF_STRU AXI_MON_CONFIG_CNF_STRU;

/* ���IDͳ������ */
typedef struct
{
	BSP_U32	    ulIdEn;				/* IDʹ�� */
	BSP_U32	    ulIncr1Cnt;			/* INCR1����ͳ�� */
	BSP_U32	    ulIncr2Cnt;			/* INCR2����ͳ�� */
	BSP_U32	    ulIncr4Cnt;			/* INCR4����ͳ�� */
	BSP_U32	    ulIncr8Cnt;			/* INCR8����ͳ�� */
	BSP_U32	    ulIncr16Cnt;		/* INCR16����ͳ�� */
	BSP_U32	    ulWrapCnt;			/* Wrap����ͳ�� */
	BSP_U32	    ulBurstSendCnt;		/* Burst��������ͳ�� */
	BSP_U32	    ulBurstFinCnt;		/* Burst��ɲ���ͳ�� */
	BSP_U32	    ulRdDelayLow;		/* �������ӳ�ͳ�ƣ���λ */
	BSP_U32     ulRdDelayHigh;		/* �������ӳ�ͳ�ƣ���λ */
	BSP_U32	    ulWrDelayLow;		/* д�����ӳ�ͳ�ƣ���λ */
	BSP_U32	    ulWrDelayHigh;		/* д�����ӳ�ͳ�ƣ���λ */
	BSP_U32	    ulWrRespDelayLow;	/* д��Ӧ�����ӳ�ͳ�ƣ���λ */
	BSP_U32	    ulWrRespDelayHigh;	/* д��Ӧ�����ӳ�ͳ�ƣ���λ */
	BSP_U32	    ulRdMaxWait;		/* �����ȴ� */
	BSP_U32	    ulWrMaxWait;		/* д���ȴ� */
	BSP_U32	    ulWrRespMaxWait;	/* д��Ӧ���ȴ� */
	BSP_U32	    ulRdTotalCntLow;	/* ���������ȴ���byte����λ */
	BSP_U32	    ulRdTotalCntHigh;	/* ���������ȴ���byte����λ */
	BSP_U32	    ulWrTotalCntLow;	/* д�������ȴ���byte����λ */
	BSP_U32	    ulWrTotalCntHigh;	/* д�������ȴ���byte����λ */	
} AXI_MON_ID_STATISTIC_DATA_STRU;

/* �����ֹ�ظ���ֹͣ���������� */
typedef struct
{
	BSP_U32						    ulIdelCnt;					    /* ���м��� */
	BSP_U32	                        ulRdWaitCycle[AXI_MAX_PORT_CNT];/* ͳ�ƴ򿪼�ع��ܵ���ȷ��λ���ȴ�ͳ�ƿ�ʼʱ�����ĵ������� */
	BSP_U32	                        ulWrWaitCycle[AXI_MAX_PORT_CNT];/* ͳ�ƴ򿪼�ع��ܵ���ȷ��λд�ȴ�ͳ�ƿ�ʼʱ�����ĵ������� */    
	AXI_MON_ID_STATISTIC_DATA_STRU	idStat[AXI_MAX_CONFIG_ID];	    /* ���IDͳ������ */
} AXI_MON_TERMINATE_CNF_STRU;

/*****************************************************************************
 �� �� ��  : DRV_AXI_DATA_CONFIG
 ��������  : AXI Monitor�ɼ����ýӿ�
 �������  : pData  : �ɼ��������ݽṹָ��         
 �������  : outLen : �ɼ��Ĵ�������״̬���ݽṹ����
 ע������  : ����ָ��ָ����ڴ����������䣬�������ͷ�
 �� �� ֵ  : ���óɹ�: AXI_DATA_CONFIG_CNF_STRU *  ����ʧ��: NULL
*****************************************************************************/
AXI_DATA_CONFIG_CNF_STRU * DRV_AXI_DATA_CONFIG(BSP_U8 * pData, BSP_U32 * outLen);

/*****************************************************************************
 �� �� ��  : DRV_AXI_REG_CONFIG
 ��������  : AXI Monitor�ɼ�����ؼĴ������ýӿ�
 �������  : pData: �ɼ�����ؼĴ����������ݽṹָ��
 �������  : �ޡ�
 �� �� ֵ  : ���óɹ�:0 ����ʧ��:��0
*****************************************************************************/
BSP_U32 DRV_AXI_REG_CONFIG(BSP_U8 * pData);

/*****************************************************************************
 �� �� ��  : DRV_AXI_DATA_CTRL
 ��������  : AXI Monitor�ɼ���������ӿ�:������ֹͣ������
 �������  : pData: �������ݽṹ�׵�ַ
 �������  : �ޡ�
 �� �� ֵ  : �ɹ�:0 ʧ��:��0
*****************************************************************************/
BSP_U32 DRV_AXI_DATA_CTRL(BSP_U8 * pData);

/*****************************************************************************
 �� �� ��  : DRV_AXI_DATA_CONFIG
 ��������  : AXI Monitor������ýӿ�
 �������  : pData  : ����������ݽṹָ��        
 �������  : outLen : ��ؼĴ�������״̬���ݽṹ����
 ע������  : ����ָ��ָ����ڴ����������䣬�������ͷ�
 �� �� ֵ  : ���óɹ�: AXI_MON_CONFIG_CNF_STRU *  ����ʧ��: NULL
*****************************************************************************/
AXI_MON_CONFIG_CNF_STRU * DRV_AXI_MON_CONFIG(BSP_U8 * pData, BSP_U32 * outLen);

/*****************************************************************************
 �� �� ��  : DRV_AXI_MON_START
 ��������  : AXI Monitor��������ӿ�
 �������  : pData: ����������ݽṹ�׵�ַ
 �������  : �ޡ�
 �� �� ֵ  : �ɹ�:0 ʧ��:��0
*****************************************************************************/
BSP_U32 DRV_AXI_MON_START(BSP_U8 * pData);

/*****************************************************************************
 �� �� ��  : DRV_AXI_MON_TERMINATE
 ��������  : AXI Monitor�����ֹ�ӿ�
 �������  : pData  : �����ֹ���ݽṹָ��          
 �������  : outLen : �����ֹͳ�ƽ�����ݽṹ����
 ע������  : ����ָ��ָ����ڴ����������䣬�������ͷ�
 �� �� ֵ  : ���óɹ�: AXI_MON_TERMINATE_CNF_STRU *  ����ʧ��: NULL
*****************************************************************************/
AXI_MON_TERMINATE_CNF_STRU * DRV_AXI_MON_TERMINATE(BSP_U8 * pData, BSP_U32 * outLen);

#ifdef __cplusplus
}
#endif

#endif /* end of _DRV_AMON_H*/


