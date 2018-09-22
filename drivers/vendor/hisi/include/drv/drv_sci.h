
#ifndef __DRV_SCI_H__
#define __DRV_SCI_H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include "drv_comm.h"

typedef enum tagSCI_CLK_STOP_TYPE_E
{
    SCI_CLK_STATE_LOW = 0,        /* Э���ָʾͣ��*/
    SCI_CLK_STATE_HIGH = 1,       /*Э���ָʾͣ��*/
    SCI_CLK_STATE_UNSUPPORTED = 2,/*Э���ָʾ��֧��*/
    SCI_CLK_STATE_BUTT
}SCI_CLK_STOP_TYPE_E;


/*  SIM  state*/
typedef enum tagSCI_CARD_STATE_E
{
    SCI_CARD_STATE_READY = 0,           	/* Ready */
    SCI_CARD_STATE_NOCARD,                	/* No card */
    SCI_CARD_STATE_BUSY,               		/* In initialization*/
	SCI_CARD_STATE_BUTT               		/* Butt*/
} SCI_CARD_STATE_E;

/* card in out status */
typedef enum
{
    SIM_CARD_OUT = 0,
    SIM_CARD_IN  = 1,
} SCI_DETECT_STATE;

/* T=1 add Begin:*/
/*for reset mode*/
typedef enum
{
    WARM_RESET = 0,     /* warm reset */
    COLD_RESET = 1,     /* cold reset */
    RESET_MODE_BUTTOM
}RESET_MODE;

/*for protocol mode*/
typedef enum
{
    T0_PROTOCOL_MODE = 0,          /*T=0*/
    T1_PROTOCOL_MODE = 1,          /*T=1*/
    PROTOCOL_MODE_BUTTOM
}PROTOCOL_MODE;

/*for EDC mode*/
typedef enum
{
    T1_ERR_DETECT_MODE_LRC = 0,     /*LRC*/
    T1_ERR_DETECT_MODE_CRC = 1,     /*CRC*/
    T1_ERR_DETECT_MODE_BUTTOM
}T1_ERR_DETECT_MODE;


/*for ATR info*/
typedef struct 
{
    PROTOCOL_MODE      Tbyte;   
    BSP_U32            valIFSC;
    BSP_U32            valIFSD;
    T1_ERR_DETECT_MODE errDetectMode;
}SCI_ATRInfo;

#define SCI_RECORD_ATR_LEN      (40)
#define SCI_RECORD_REG_LEN      (36)
#define SCI_RECORD_DATA_LEN     (72)
#define SCI_RECORD_EVENT_LEN    (32)
#define SCI_RECORD_TOTAL_LEN    (388)

typedef struct  stSciRecordInfo
{
    unsigned short  cardClass;   /*����ѹ���ͣ�1800��3000*/
    unsigned short  ATRlen;      /*ART����ʵ�ʳ���*/
    unsigned char   ATRData[SCI_RECORD_ATR_LEN];  /*ART���ݼ�¼,������40���ֽ�*/
    unsigned int    SciRegData[SCI_RECORD_REG_LEN];/*SCI���мĴ�����¼*/
    unsigned char   SciRecordData[SCI_RECORD_DATA_LEN];/*���ټ�¼�Ϳ����������8�����ݣ�ÿ��������9���ֽ�*/
    unsigned int    SciEvent[SCI_RECORD_EVENT_LEN];/*SCI �ײ��¼����8����¼*/
}SCI_RECORD_INFO;

/* T=1 add End */


typedef void (*OMSCIFUNCPTR)(unsigned int ulVal);

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_RST
*
* ��������  : ���ӿ����ڸ�λSCI��Smart Card Interface��������USIM��Universal
*           Subscriber Identity Module����
*
* �������  : BSP_VOID
* �������  : ��
*
* �� �� ֵ  : OK  ��λ�ɹ�
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
BSP_S32 DRV_USIMMSCI_RST(RESET_MODE rstMode);

/********************************************************************************************************************
 �� �� ��  : DRV_USIMMSCI_GET_CARD_STAU
 ��������  : ���ӿ����ڻ�ÿ���ǰ��״̬��ĿǰLTE�ṩ�ӿڲ������Ͳ�һ��
 �������  : �ޡ�
 �������  :
 �� �� ֵ  : 0:  ������Ready��
             -1����δ����Ready��
 ע������  ����Ч����BSP_SCI_Reset()�������ٵ��ô˺�����
********************************************************************************************************************/
BSP_U32 DRV_USIMMSCI_GET_CARD_STAU(BSP_VOID);

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_SND_DATA
*
* ��������  : ���ӿ����ڷ���һ�����ݵ�USIM��
*
* �������  : BSP_U32 u32DataLength �������ݵ���Ч���ȡ�ȡֵ��Χ1��256����λΪ�ֽ�
*             BSP_U8 *pu8DataBuffer �������������ڴ���׵�ַ�����Ƕ�̬���䣬���ýӿ�
*                                   ���������ͷţ�������Ӳ����������
* �������  : ��
*
* �� �� ֵ  : OK
*           BSP_ERR_SCI_NOTINIT
*           BSP_ERR_SCI_INVALIDPARA
*           BSP_ERR_SCI_DISABLED
*           BSP_ERR_SCI_NOCARD
*           BSP_ERR_SCI_NODATA
*
* �޸ļ�¼  : 
*
*****************************************************************************/
BSP_S32 DRV_USIMMSCI_SND_DATA(BSP_U32 u32DataLength,BSP_U8 * pu8DataBuffer);
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_RCV
*
* ��������  : ���ӿ�����USIM Manager��ȡ����SCI Driver�Ŀ���������
*             �ýӿ�Ϊ�����ӿڣ�ֻ��SCI���յ��㹻����������Ż᷵�أ�
*             �ýӿڵĳ�ʱ����Ϊ1s
*
* �������  : BSP_U32 u32DataLength USIM Manager����SCI Driver��ȡ�����ݳ��ȡ�
* �������  : BSP_U8 *pu8DataBuffer USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer��
* �� �� ֵ  : OK
*             BSP_ERR_SCI_NOTINIT
*             BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
BSP_S32 DRV_USIMMSCI_RCV(BSP_U32 u32DataLength,BSP_U8 * pu8DataBuffer);

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_RCV_ALL
*
* ��������  : ���ӿ�����USIM Manager�ڶ�����ʱ��ʱ�򣬵��ñ���������ȡ�������ݻ����е���������
*
* �������  : ��  
* �������  : u32 *u32DataLength Driver��ȡ�����ݳ��ȣ����ظ�USIM Manager��ȡֵ��Χ1��256����λ���ֽ�
*           u8 * pu8DataBuffer USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer
*
* �� �� ֵ  : OK
*          BSP_ERR_SCI_NOTINIT
*          BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
BSP_U32 DRV_USIMMSCI_RCV_ALL(BSP_U32 *u32DataLength,BSP_U8 * pu8DataBuffer);


BSP_S32 DRV_USIMMSCI_GET_ATR(unsigned long * u32DataLength, BSP_U8 * pu8ATR,SCI_ATRInfo* stSCIATRInfo);

BSP_S32  DRV_USIMMSCI_CLASS_SWITCH(BSP_VOID);
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_SHOW_VLT
*
* ��������  : ���ӿ�������ʾ��ǰSIM���ӿڵ�ѹ
*
* �������  : ��  
* �������  :u32 * pu32Vltgval ��ǰ��ѹ
*
* �� �� ֵ  : OK
*          BSP_ERR_SCI_NOTINIT
*          BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
BSP_U32  DRV_USIMMSCI_SHOW_VLT(BSP_U32* pu32Vltgval);
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_TM_STOP
*
* ��������  : ���ӿ�����֧��PS�ر�SIM��ʱ��
*
* �������  :
*           SCI_CLK_STOP_TYPE_E enTimeStopCfg ʱ��ֹͣģʽ
*
* �������  : ��
*
* �� �� ֵ  : OK - successful completion
*               ERROR - failed
*               BSP_ERR_SCI_NOTINIT
*               BSP_ERR_SCI_INVALIDPARA - invalid mode specified
*               BSP_ERR_SCI_UNSUPPORTED - not support such a operation
* �޸ļ�¼  : 
*
*****************************************************************************/
BSP_S32 DRV_USIMMSCI_TM_STOP(SCI_CLK_STOP_TYPE_E enTimeStopCfg); 

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_DEACT
*
* ��������  : ���ӿ����ڶ�SIM����ȥ�������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : OK
*             BSP_ERR_SCI_NOTINIT
* �޸ļ�¼  : 
*
*****************************************************************************/
BSP_U32 DRV_USIMMSCI_DEACT(BSP_VOID);
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_GET_CLK_STAU
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��״̬
*
* �������  : BSP_U32 *pu32SciClkStatus   ����ָ�룬���ڷ���SIM��ʱ��״̬��
*                                       0��ʱ���Ѵ򿪣�
*                                       1��ʱ��ֹͣ
* �������  : ��
*
* �� �� ֵ  : OK    �����ɹ�
*          BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 
*
*****************************************************************************/
BSP_U32 DRV_USIMMSCI_GET_CLK_STAU(BSP_U32 * pu32SciClkStatus);
/*****************************************************************************
* �� �� ��  : DRV_PCSC_GET_CLK_FREQ
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��Ƶ��
*
* �������  : ��
*
* �������  : unsigned long *pLen   ʱ��Ƶ�����ݵĳ���
*             BSP_U8 *pBuf    ʱ��Ƶ������
* �� �� ֵ  : OK    �����ɹ�
*             BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 
*
*****************************************************************************/
BSP_U32 DRV_PCSC_GET_CLK_FREQ(unsigned long * pLen,BSP_U8 * pBuf); 
/*****************************************************************************
* �� �� ��  : DRV_PCSC_GET_BAUD_RATE
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM��ʱ��Ƶ��
*
* �������  : ��
*
* �������  : unsigned long *pLen   ���������ݵĳ���
*             BSP_U8 *pBuf    ����������
*
* �� �� ֵ  : OK    �����ɹ�
*             BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 
*
*****************************************************************************/
BSP_U32 DRV_PCSC_GET_BAUD_RATE(unsigned long * pLen, BSP_U8 * pBuf);

/*****************************************************************************
* �� �� ��  : DRV_PCSC_GET_SCI_PARA
*
* ��������  : ���ӿ����ڻ�ȡ��ǰSIM����PCSC��ز���
*
* �������  : ��
*
* �������  : BSP_U8 *pBuf    PCSC��ز���
*
* �� �� ֵ  : OK    �����ɹ�
*             BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 
*
*****************************************************************************/
BSP_U32 DRV_PCSC_GET_SCI_PARA(BSP_U8 * pBuf); 

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_FUNC_REGISTER
*
* ��������  : ���ӿ�����ע��OAM�Ļص�����
*
* �������  : omSciFuncPtr
* �������  : ��
*
* �� �� ֵ  : NA
*
* �޸ļ�¼  : 
*
*****************************************************************************/
void DRV_USIMMSCI_FUNC_REGISTER(OMSCIFUNCPTR omSciFuncPtr);

/*****************************************************************************
 �� �� ��  : DRV_USIMMSCI_RECORD_DATA_SAVE
 ��������  : ���ӿ����ڻ�ȡ��ǰSIM���������ݡ������쳣����ģ�飬V7�ȴ�׮
 �������  : �ޡ�
 �������  : ��
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܣ�ָ�����Ϊ�ա�
 ע������  ��
*****************************************************************************/
BSP_U32 DRV_USIMMSCI_RECORD_DATA_SAVE(BSP_VOID);  

/* T=1 add Begin:*/
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_SETBWT
*
* ��������  : ���ӿ��������ÿ�ȴ�ʱ��
*
* �������  : BSP_U32 nBWT :���ó�ʱʱ��ΪBWT��nBWT��
*
* �������  : ��
*
* �� �� ֵ  : OK/ERROR
* �޸ļ�¼  : 2013��10��15��   liuyi  creat
*
*****************************************************************************/
BSP_S32 DRV_USIMMSCI_SETBWT(BSP_U32 nBWT);

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_PROTOCOL_SWITCH
*
* ��������  : ���ӿ�����֪ͨ�������T=0��T=1Э�������л�
*
* �������  : RESET_MODE enSIMProtocolMode:��Ҫ�л�Ϊ��Э������
*
* �������  : ��
*
* �� �� ֵ  : OK/ERROR
* �޸ļ�¼  : 2013��10��15��   liuyi  creat
*
*****************************************************************************/
BSP_S32 DRV_USIMMSCI_PROTOCOL_SWITCH(PROTOCOL_MODE enSIMProtocolMode);

/*****************************************************************************
* �� �� ��  : BSP_SCI_BLK_Receive
* ��������  : ���ӿ�������T=1ʱUSIM Manager��ȡ����SCI Driver�Ŀ��������ݣ�
*             �������BWT��ʱ�������ݶ�ȡʱ����һ����ʱ��ֵSCI_TIMEOUT
*
* �������  : ��
* �������  : BSP_U8 *pu8Data USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer��
              BSP_U32 *pulLength SCI Driver���յ������ݳ��ȡ�

* �� �� ֵ  : OK : 0
              ERROR : -1
              SCI_TIMEOUT : 1
*
* �޸ļ�¼  : 2013��10��15��   liuyi  creat
*
*****************************************************************************/
BSP_S32 DRV_USIMMSCI_BLK_RCV(BSP_U8 *pu8Data,BSP_U32 *pulLength);

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_RECORDLOG_READ
*
* ��������  : ���ӿڻ�ȡsim���쳣ʱ��λ��Ϣ
* �������  : pucDataBuff: ��ȡ��λ��Ϣ��buffer
              ulMaxLength: ���ֵ���ж�ʹ��
*
* �� �� ֵ  : pulLength: ��ȡ���ݳ���

*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 
*
*****************************************************************************/
BSP_S32  DRV_USIMMSCI_RECORDLOG_READ(unsigned char *pucDataBuff, unsigned int * pulLength, unsigned int ulMaxLength);
/* T=1 add End */

// sync V9R1; 2013-05-02
/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_GET_ERRNO
*
* ��������  : ���ӿڻ�ȡ�ӿڵ��÷��صĴ�����
* �������  :  ��
* �������  :  ��
*
* �� �� ֵ  : ������
*
* �޸ļ�¼  : 
*
*****************************************************************************/
BSP_S32 DRV_USIMMSCI_GET_ERRNO(BSP_VOID);

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_POWER_ON
*
* ��������  : ���ӿڴ�SIM �������ѹ
* �������  : �� 
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 
*
*****************************************************************************/
BSP_VOID DRV_USIMMSCI_POWER_ON(BSP_VOID);

/*****************************************************************************
* �� �� ��  : DRV_USIMMSCI_POWER_OFF
*
* ��������  : ���ӿڹر�SIM �������ѹ
* �������  : ��
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 
*
*****************************************************************************/
BSP_VOID DRV_USIMMSCI_POWER_OFF(BSP_VOID);

#ifdef __cplusplus
}
#endif

#endif

