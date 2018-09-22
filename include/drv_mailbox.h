

#ifndef __DRV_MAILBOX_H__
#define __DRV_MAILBOX_H__

#ifdef __cplusplus
extern "C" 
{
#endif

#include "product_config.h"

#include "drv_comm.h"
#include "drv_ipc_enum.h"


/* TDS&LTE mailbox driver begin */

typedef enum tagMAILBOX_SLEEP_PROC_E
{
    EN_MAILBOX_SLEEP_WAKEUP = 0,        /* ǿ�ƻ���DSP�������� */
    EN_MAILBOX_SLEEP_WAIT,              /* DSP�Զ����Ѻ������� */
    EN_MAILBOX_SLEEP_LOST,              /* DSP����˯��ģʽʱ���������� */
    EN_MAILBOX_SLEEP_BUTT
}MAILBOX_SLEEP_PROC_E;

typedef enum tagMAILBOX_SERVICE_TYPE_E
{
    EN_MAILBOX_SERVICE_LTE_PS = 0,      /* LTE PS���� */
    EN_MAILBOX_SERVICE_LTE_CT,          /* LTE CT���� */
    EN_MAILBOX_SERVICE_LTE_BT,          /* LTE BT���� */
    EN_MAILBOX_SERVICE_LTE_OM,          /* LTE OM�������� */
    EN_MAILBOX_SERVICE_LTE_COEX,        /* LTE WIFI coex */
    EN_MAILBOX_SERVICE_LTE_HS_DIAG,     /* LTE ��ά�ɲ�͹����������� */

    EN_MAILBOX_SERVICE_TDS_PS,          /* TDS PS���� */
    EN_MAILBOX_SERVICE_TDS_CT,          /* TDS CT���� */
    EN_MAILBOX_SERVICE_TDS_BT,          /* TDS BT���� */
    EN_MAILBOX_SERVICE_TDS_OM,          /* TDS OM�������� */
    EN_MAILBOX_SERVICE_TDS_HS_DIAG,     /* TDS ��ά�ɲ�͹����������� */

    EN_MAILBOX_SERVICE_RTT_SYS_CTRL,    /* DSP��ά�ɲ����ҵ�� */

    EN_MAILBOX_SERVICE_BUTT
}MAILBOX_SERVICE_TYPE_E;


typedef enum tagMAILBOX_INT_TYPE_E
{
    EN_MAILBOX_INT_SUBFRAME = 0,        /* ��֡�ж� */
    EN_MAILBOX_INT_COM_IPC,             /* IPC�ж� */
    EN_MAILBOX_INT_SP_IPC,              /* ר������IPC�ж� */
    EN_MAILBOX_INT_BUTT
}MAILBOX_INT_TYPE_E;


typedef enum tagMAILBOX_ERRORCODE_E
{
    ERR_MAILBOX_NOT_INIT = 1,           /* δ��ʼ�� */
    ERR_MAILBOX_PARAM_INCORRECT,        /* �������� */
    ERR_MAILBOX_MEMORY_NOTENOUGH,       /* �ռ䲻�� */
    ERR_MAILBOX_TIMEOUT,                /* ��ʱ */
    ERR_MAILBOX_COVER,                  /* ר������д����ʱԭ��δ���ߣ�ִ�и��ǲ��� */
    ERR_MAILBOX_WRITE_FAILED,           /* ����дʧ�� */
    ERR_MAILBOX_READ_FAILED,            /* �����ʧ�� */
    ERR_MAILBOX_READ_NULL,              /* �����������Ϣ */
    ERR_MAILBOX_DSP_POWERDOWN,          /* DSP���ڵ͹���״̬ */
    ERR_MAILBOX_OTHER,                  /* �������� */
    ERR_MAILBOX_ERRORCODE_BUTT
}MAILBOX_ERRORCODE_E;


/*****************************************************************************
 Prototype      : BSP_MailBox_ComMsgInit
 Description    : ͨ������ĳ�ʼ��(�ṩ��Э��ջ���ã�
                  �ӿ��ڲ�ʵ����DSP������Ϣ�ĳ�ʼ��)
 Input          : None
 Return Value   : None
*****************************************************************************/
BSP_VOID BSP_MailBox_ComMsgInit(BSP_U32 ulworkingmode);


/*****************************************************************************
 Prototype      : BSP_MailBox_IsDspOk
 Description    : ��DSP�����ֺ������ж�DSP�Ƿ��ʼ������
                  (�ṩ��Э��ջ���ã�������ֲ��ɹ���Э��ջ��Ҫѭ����ε���)
 Input          : None
 Return Value   : BSP_TRUE: DSP��ʼ�����������ֳɹ�
                  BSP_FALSE:DSPû�г�ʼ�����������ֲ��ɹ�
*****************************************************************************/
BSP_BOOL BSP_MailBox_IsDspOk(BSP_VOID);

/*****************************************************************************
 Prototype       : BSP_MailBox_ComMsgWrite
 Description     : ����д�ӿ�(ÿ��ֻ֧��дһ��ԭ��)
 Input           : enMbxType    �����ҵ������
                   pData        ����ָ��
                   ulLen        ���ݳ���(���ֽ�Ϊ��λ)
                   enProcType   DSP˯��ʱ�Ĵ�������
 Output          : None.
 Return Value    : BSP_OK: �ɹ�
                   ����: ʧ��
*****************************************************************************/
BSP_U32 BSP_MailBox_ComMsgWrite(MAILBOX_SERVICE_TYPE_E enMbxType,
                               BSP_VOID* pData,
                               BSP_U32 ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType);

typedef BSP_VOID (*BSP_MBX_NOTIFY_FUNC)(MAILBOX_INT_TYPE_E enIntType);

/*****************************************************************************
 Prototype       : BSP_MailBox_ComNotifyReg
 Description     : �������ݵ���֪ͨע��ӿڣ���֡�жϼ�ʹû����ҲҪ�ص���
 param           : enMbxType        �����ҵ������
                   pFun             �������ݵ��ﴦ����
 Return Value    : BSP_OK: �ɹ�
                   ERR_MAILBOX_NOT_INIT
                   ERR_MAILBOX_PARAM_INCORRECT
*****************************************************************************/
BSP_U32 BSP_MailBox_ComNotifyReg(MAILBOX_SERVICE_TYPE_E enMbxType,
                                BSP_MBX_NOTIFY_FUNC pFun);

/*****************************************************************************
 Prototype       : BSP_MailBox_IntTypeSet
 Description     : ����PS�����ж�Դ�ӿ�(Ĭ��IPC�жϷ�ʽ)
                   ֻ����PS���䣬OM�������ж��ϱ�
 param           : None
 Return Value    : 0: �ɹ�; ����: ���õ�type�Ƿ�
*****************************************************************************/
BSP_U32 BSP_MailBox_IntTypeSet(MAILBOX_INT_TYPE_E enIntType);

/*****************************************************************************
 Prototype       : BSP_MailBox_ComMsgSize
 Description     : ��ȡͨ�������е�һ��ԭ��ĳ���
                   (�ṩ���ϲ���ã��������ṩ������ԭ�������ӿڣ���Ҫ�ϲ�ѭ��
                   �����Ա����ϲ�©���ж�֪ͨʱ���������ԭ�ﻺ��)
 param           : enMbxType        �����ҵ������
 Return Value    : 0:  û�л�ȡԭ�����Ϊ�գ������������͵�ԭ��δ���ߣ�
                   ����ֵ: �����һ��ԭ��ĳ���
*****************************************************************************/
BSP_U32 BSP_MailBox_ComMsgSize(MAILBOX_SERVICE_TYPE_E enMbxType);

/*****************************************************************************
 Prototype       : BSP_MailBox_ComMsgRead
 Description     : ������ӿ�
                   (�˽ӿڻỽ��DSP����ҪBSP_MailBox_ComMsgSize���طǿ�ʱ����)
 param           : enMbxType    �����ҵ������
                   pData        ���յ����ݻ�����ָ��(�洢ԭ����Ϣ��������ԭ�ﳤ��)
                   ulLen        pData��������size(���ֽ�Ϊ��λ)
                   enProcType   DSP˯��ʱ�Ĵ�������
 Return Value    : 0 : �ɹ�
                   ���� : ʧ��
*****************************************************************************/
BSP_U32 BSP_MailBox_ComMsgRead(MAILBOX_SERVICE_TYPE_E enMbxType,
                              BSP_VOID* pData,
                              BSP_U32 ulLen,
                               MAILBOX_SLEEP_PROC_E enProcType);


/*****************************************************************************
 Prototype      : BSP_MailBox_SpULMsgHeadInit
 Description    : ר�У�Special Mailbox�������������Ϣͷ��ʼ���ӿ�
                  (��ʼ����������ÿ��ԭ�����Ϣͷ���ṩ��Э��ջ����Ҫ���ö��
                  �ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          :
                ulAddr : ר������ĵ�ַ
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                ucData : ��ʼֵ
 Return Value   None
*****************************************************************************/
BSP_VOID BSP_MailBox_SpULMsgHeadInit(BSP_U32 ulAddr,
                                 BSP_U32 ulSize,
                                 BSP_U8 ucData);

/*****************************************************************************
 Prototype      : BSP_MailBox_SpDLMsgHeadInit
 Description    : ר�У�Special Mailbox�������������Ϣͷ��ʼ���ӿ�
                  (��ʼ����������ÿ��ԭ�����Ϣͷ���ṩ��Э��ջ����Ҫ���ö��
                  �ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          :
                ulAddr : ר������ĵ�ַ
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                ucData : ��ʼֵ
 Return Value   None
*****************************************************************************/
BSP_VOID BSP_MailBox_SpDLMsgHeadInit(BSP_U32 ulAddr,
                                 BSP_U32 ulSize,
                                 BSP_U8 ucData);

/*****************************************************************************
 Prototype      : BSP_MailBox_SpMsgWrite
 Description    : ר�����䣨Special Mailbox����д�ӿ�
                  (�ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          :
                ulAddr : ר�������ƫ�Ƶ�ַ������Ϣͷ��ʼ�ĵ�ַ��
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                pData  : ������Ϣ(��������Ϣͷ��Ϣ)
 Return Value   :
                BSP_OK: ��ʾ�����ɹ�
                ERR_MAILBOX_COVER: ��ʾǰһ��ԭ��δ�����ߣ�����
                ERR_MAILBOX_WRITE_FAILED: дʧ��
                ERR_MAILBOX_NOT_INIT: ����δ��ʼ��
                ERR_MAILBOX_PARAM_INCORRECT: ��������
*****************************************************************************/
BSP_U32 BSP_MailBox_SpMsgWrite(BSP_U32 ulAddr,
                               BSP_U32 ulSize,
                               BSP_VOID* pData);

/*****************************************************************************
 Prototype      : BSP_MailBox_SpMsgRead
 Description    : ר�����䣨Special Mailbox���Ķ��ӿ�
                  (�ɵ����߱�֤���ýӿ�ʱDSP���ڷ�˯��״̬)
 Input          :
                ulAddr : ר�������ƫ�Ƶ�ַ������Ϣͷ��ʼ�ĵ�ַ��
                ulSize : ��ʼֵ�Ĵ�С(���ֽ�Ϊ��λ)
                pData  : ������Ϣ(��������Ϣͷ��Ϣ)
 Return Value   :
                BSP_OK: ��ȡ�ɹ�
                ERR_MAILBOX_READ_NULL: ������
                ERR_MAILBOX_NOT_INIT: ����δ��ʼ��
                ERR_MAILBOX_PARAM_INCORRECT: ��������
*****************************************************************************/
BSP_U32 BSP_MailBox_SpMsgRead(BSP_U32 ulAddr,
                              BSP_U32 ulSize,
                              BSP_VOID* pData);

/*****************************************************************************
 Prototype       : BSP_MailBox_SpNotifyReg
 Description     : ר���������ݵ���֪ͨע��ӿ�
 param           : pFun             �������ݵ��ﴦ����
 Return Value    : BSP_OK: �ɹ�
                   ����: ʧ��
*****************************************************************************/
BSP_U32 BSP_MailBox_SpNotifyReg(BSP_MBX_NOTIFY_FUNC pFun);

/*****************************************************************************
 Prototype       : BSP_MailBox_SpNotifyEnable
 Description     : ר���������ݵ���֪ͨ�ж�ʹ�ܽӿ�
 param           : None
 Return Value    : void
*****************************************************************************/
BSP_VOID BSP_MailBox_SpNotifyEnable(BSP_VOID);

/*****************************************************************************
 Prototype       : BSP_MailBox_SpNotifyDisable
 Description     : ר���������ݵ���֪ͨ�ж�ȥʹ�ܽӿ�
 param           : None
 Return Value    : void
*****************************************************************************/
BSP_VOID BSP_MailBox_SpNotifyDisable(BSP_VOID);


/*****************************************************************************
 Prototype       : BSP_Mailbox_ForbidDspSleep
 Description     : ��ֹDSP˯�߽ӿ�
 Input           : enProcType     DSP˯��ʱ�Ĵ�������
                    EN_MAILBOX_SLEEP_WAKEUP : ǿ�ƻ���ʱ���еȴ�����
                                              �������жϻص�������˲���
                                              ֻ��������������˲���
                    EN_MAILBOX_SLEEP_LOST   : �жϻص��������ж�������˲���

 Return Value    : BSP_OK: �ɹ�,DSP��ǰû˯�ߣ��������ý�ֹDSP����˯��
                   ERR_MAILBOX_DSP_POWERDOWN : ������ΪEN_MAILBOX_SLEEP_LOST,
                                               DSP��ǰ���ڵ͹���״̬,����ʧ��
                   ERR_MAILBOX_TIMEOUT       : ������ΪEN_MAILBOX_SLEEP_WAKEUP,
                                               ����DSP��ʱ(10s)
*****************************************************************************/
BSP_U32 BSP_Mailbox_ForbidDspSleep(MAILBOX_SLEEP_PROC_E enProcType);


/*****************************************************************************
 Prototype       : BSP_Mailbox_AllowDspSleep
 Description     : ����DSP˯�߽ӿ�
 Input           : None
 Return Value    : None
*****************************************************************************/
BSP_VOID BSP_Mailbox_AllowDspSleep(BSP_VOID);



typedef BSP_BOOL (*BSP_MBX_GET_STATUS_FUNC)(BSP_VOID);

/*****************************************************************************
 Prototype       : BSP_MailBox_GetDspStatusReg
 Description     : ��ȡDSP˯��״̬�ص�����ע��ӿڣ��͹���ģ�����
 param           : pFun             ��ȡDSP˯��״̬������
 Return Value    : BSP_VOID
*****************************************************************************/
BSP_VOID BSP_MailBox_GetDspStatusReg(BSP_MBX_GET_STATUS_FUNC pFun);


typedef BSP_VOID (*BSP_MBX_DSP_AWAKE_FUNC)(BSP_VOID);

/*****************************************************************************
 Prototype       : BSP_MailBox_DspForceAwakeReg
 Description     : DSPǿ�ƻ��ѻص�����ע��ӿڣ��͹���ģ�����
 param           : pFun             DSPǿ�ƻ��Ѵ�����
 Return Value    : BSP_VOID
*****************************************************************************/
BSP_VOID BSP_MailBox_DspForceAwakeReg(BSP_MBX_DSP_AWAKE_FUNC pFun);


/*****************************************************************************
 Prototype       : BSP_MailBox_GetSpMsgStatusReg
 Description     : ��ȡר����������DSP˯��״̬�ص�����ע��ӿڣ�PS����
 param           : pFun             ��ȡDSP˯��״̬������
 Return Value    : BSP_VOID
*****************************************************************************/
BSP_VOID BSP_MailBox_GetSpMsgStatusReg(BSP_MBX_GET_STATUS_FUNC pFun);


/*****************************************************************************
 Prototype       : BSP_MailBox_DspAwakeProc
 Description     : DSP���Ѻ�����䴦��ӿڣ��͹���ģ�����
 param           : BSP_VOID
 Return Value    : BSP_VOID
*****************************************************************************/
BSP_VOID BSP_MailBox_DspAwakeProc(BSP_VOID);

/*****************************************************************************
 Prototype       : BSP_MailBox_IsAllowDspSleep
 Description     : ��ѯ�Ƿ�����DSP˯�ߵĴ���ӿڣ��͹���ģ�����
                    ���ô˽ӿ�ʱ�͹���ģ�鱣֤DSPδ˯��
                    �˽ӿ�ֻ���PS�����ר�����䣬�����OM����(OMԭ����ʱ��Ҫ��)
 param           : BSP_VOID
 Return Value    : BSP_BOOL: TRUE-allow;FALSE-forbid
*****************************************************************************/
BSP_BOOL BSP_MailBox_IsAllowDspSleep(BSP_VOID);


/*****************************************************************************
 Prototype       : BSP_UniMailboxWrite
 Description     : �����ͨ��д�ӿ�(�ɵ����߱�֤����ĵ�ַ�ĺϷ���)
                   ���ӿ�ʵ������memcpy����������
                   �ӿ��ڲ���֤DSP�Ļ��Ѳ������������ʧ�ܣ�����ERR_MAILBOX_TIMEOUT
 Return Value    :
                   BSP_OK
                   ERR_MAILBOX_PARAM_INCORRECT
                   ERR_MAILBOX_TIMEOUT
*****************************************************************************/
BSP_U32 BSP_UniMailboxWrite(BSP_VOID *pDst, BSP_VOID *pSrc, BSP_U32 ulLen);

/*****************************************************************************
 Prototype       : BSP_MailboxAbnormalProc
 Description     : �����쳣����
                   Э��ջ������Ϣ��ʱ����ô˽ӿڱ������������Ϣ
                   ��Э��ջ�̶���ǰ0.5K����Э��ջ��Ϣ����3.5K����������Ϣ
 Input           : ucData       �����׵�ַ
 Return Value    : NONE
*****************************************************************************/
BSP_VOID BSP_MailboxAbnormalProc(BSP_U8 *ucData);

/* TDS&LTE mailbox driver end */

#ifdef __cplusplus
}
#endif

#endif

