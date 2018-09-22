

#ifndef __DRV_CIPHER_H__
#define __DRV_CIPHER_H__

#include "drv_comm.h"

/*************************CIPHER START**********************************/

/* ������ */
#define CIPHER_SUCCESS                  0

#define CHN_BUSY                    0
#define CHN_FREE                    1

/* CIPHER֧�ֵ��㷨����,ע��ö��ֵ��Ĵ�������ֵһ�� */
typedef enum tagCIPHER_ALGORITHM_E
{
	CIPHER_ALG_NULL = 0,        /*���㷨*/
    CIPHER_ALG_SNOW3G  = 1,     /* SNOW3G�㷨 */
    CIPHER_ALG_AES_128 = 2,     /* AES128�㷨 */
    CIPHER_ALG_AES_192 = 3,     /* AES192�㷨 */
    CIPHER_ALG_AES_256 = 4,     /* AES256�㷨 */
    CIPHER_ALG_ZUC = 5,	        /* ZUC�㷨 */
    CIPHER_ALG_BUTTOM
}CIPHER_ALGORITHM_E;

typedef enum tagKDF_SHA_KEY_SOURCE_E
{
    SHA_KEY_SOURCE_DDR,             /*  sha_key��Դ��input pointָ���ĵ�ַ�ռ� */
    SHA_KEY_SOURCE_KEYRAM,       /*  sha_key��Դ���ڲ�KeyRam */
    SHA_KEY_SOURCE_FOLLOW,       /*  sha_key��Դ���ϴ�KDF������sha_key */ 
    SHA_KEY_SOURCE_RESULT,        /*  sha_key��Դ����һ��KDF�����Ľ��*/
    SHA_KEY_SOURCE_MAX
}KDF_SHA_KEY_SOURCE_E;

typedef enum tagKDF_SHA_S_SOURCE_E
{
    SHA_S_SOURCE_DDR,              /*  sha_s��Դ��input pointָ���ĵ�ַ�ռ�*/
    SHA_S_SOURCE_KEYRAM,        /*  sha_s��Դ���ڲ�KeyRam */
    SHA_S_SOURCE_MAX
}KDF_SHA_S_SOURCE_E;

/**************************************************************************
  ö�ٶ���
**************************************************************************/
enum CIPHER_SECURITY_CHANNEL_ENUM
{
    CIPHER_SECURITY_CHANNEL_0            = 0,                /*ͨ��0*/
    CIPHER_SECURITY_CHANNEL_1            = 1,                /*ͨ��1*/
    CIPHER_SECURITY_CHANNEL_2            = 2,                /*ͨ��2*/
    CIPHER_SECURITY_CHANNEL_3            = 3,                /*ͨ��3*/

    CIPHER_SECURITY_CHANNEL_BUTT
};

/* ͨ����*/
#define LTE_SECURITY_CHANNEL_NAS    CIPHER_SECURITY_CHANNEL_2
#define LTE_SECURITY_CHANNEL_RRC    CIPHER_SECURITY_CHANNEL_2
#define LTE_SECURITY_CHANNEL_UL_SRB CIPHER_SECURITY_CHANNEL_1
#define LTE_SECURITY_CHANNEL_DL_SRB CIPHER_SECURITY_CHANNEL_1
#define LTE_SECURITY_CHANNEL_UL_DRB CIPHER_SECURITY_CHANNEL_0
#define LTE_SECURITY_CHANNEL_DL_DRB CIPHER_SECURITY_CHANNEL_3

/* CIPHER������������ */
typedef enum tagCIPHER_SINGLE_OPT_E
{
    /* ������������,����ö��ֵ��Ĵ�������ֵһ�� */
    CIPHER_OPT_ENCRYPT = 0x0,   /* ���� */
    CIPHER_OPT_DECRYPT = 0x1,   /* ���� */
    CIPHER_OPT_PROTECT_SMAC = 0x2,   /* �������������MAC����Ϊ2Byte */
    CIPHER_OPT_PROTECT_LMAC = 0x3,   /* �������������MAC����Ϊ4Byte */
    CIPHER_OPT_CHECK_PRE_SMAC  = 0x4,   /* ��������MAC����Ϊ2Byte��λ��������ǰ�� */
    CIPHER_OPT_CHECK_POST_SMAC = 0x5,   /* ��������MAC����Ϊ2Byte��λ�������ݺ��� */
    CIPHER_OPT_CHECK_PRE_LMAC  = 0x6,   /* ��������MAC����Ϊ4Byte��λ��������ǰ�� */
    CIPHER_OPT_CHECK_POST_LMAC = 0x7,   /* ��������MAC����Ϊ4Byte��λ�������ݺ��� */
    CIPHER_SINGLE_OPT_BUTTOM
}CIPHER_SINGLE_OPT_E;


/* CIPHER������������ */     /* PDCP ���������������*/
typedef enum tagCHPHER_RELA_OPT_E
{
    /*  ������������ */
    CIPHER_PDCP_PRTCT_ENCY,     /*PDCP��������(����)*/
    CIPHER_PDCP_DECY_CHCK,      /*PDCP���ܼ��(����)*/

    CIPHER_NAS_ENCY_PRTCT,      /* NAS����ܱ���(����) */
    CIPHER_NAS_CHCK_DECY,       /* NAS�������(����) */

	CIPHER_RELA_OPT_BUTTOM
}CIPHER_RELA_OPT_E;


/* CIPHER��Կ����, ע��ö��ֵ��Ĵ�������ֵһ�� */
typedef enum tagCIPHER_KEY_LEN_E
{
    CIPHER_KEY_L128 = 0,        /* ��Կ����128 bit */
    CIPHER_KEY_L192 = 1,        /* ��Կ����192 bit */
    CIPHER_KEY_L256 = 2,        /* ��Կ����256 bit */
    CIPHER_KEY_LEN_BUTTOM
}CIPHER_KEY_LEN_E;


/* CIPHER�����ύ���� */
typedef enum tagCIPHER_SUBMIT_TYPE_E
{
    CIPHER_SUBM_NONE = 0,           /* �����κ�֪ͨ */
    CIPHER_SUBM_BLK_HOLD = 1,       /* ѭ����ѯ�ȴ���� */
    CIPHER_SUBM_CALLBACK = 2,       /* �ص�����֪ͨ */
    CIPHER_SUBM_BUTTOM
}CIPHER_SUBMIT_TYPE_E;

/* CIPHER֪ͨ���� */
typedef enum tagCIPHER_NOTIFY_STAT_E
{
    CIPHER_STAT_OK = 0,           /* �ɹ���� */
    CIPHER_STAT_CHECK_ERR = 1,    /* �����Լ����� */
    CIPHER_STAT_BUTTOM
}CIPHER_NOTIFY_STAT_E;

typedef enum CIPHER_HDR_BIT_ENUM
{
    CIPHER_HDR_BIT_TYPE_0              = 0,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ0�����������˹���*/
    CIPHER_HDR_BIT_TYPE_5              = 1,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�5λ�����뱣��*/
    CIPHER_HDR_BIT_TYPE_7              = 2,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�7λ�����뱣��*/
    CIPHER_HDR_BIT_TYPE_12             = 3,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ2���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�12λ�����뱣��*/

    CIPHER_APPEND_HDR_BIT_TYPE_5       = 4,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�5λ�������뱣����ֻ����*/
    CIPHER_APPEND_HDR_BIT_TYPE_7       = 5,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ1���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�7λ�������뱣����ֻ����*/
    CIPHER_APPEND_HDR_BIT_TYPE_12      = 6,     /*��Ӧ��ͷ�򸽼�ͷ�ֽڳ���Ϊ2���������˹��ܣ���Ӧ����ͷ��������Countֵ�ĵ�12λ�������뱣����ֻ����*/

    CIPHER_HDR_BIT_TYPE_BUTT
}CIPHER_HDR_E;

/* �㷨������Ϣ */
typedef struct tagCIHPER_ALG_INFO_S
{
    BSP_U32 u32KeyIndexSec;
    BSP_U32 u32KeyIndexInt;
    CIPHER_ALGORITHM_E enAlgSecurity;          /* ��ȫ�����㷨ѡ��AEC�㷨����SNOW3G�㷨 */
    CIPHER_ALGORITHM_E enAlgIntegrity;         /* �����Բ����㷨ѡ��AEC�㷨����SNOW3G�㷨 */
}CIHPER_ALGKEY_INFO_S;


/*�������������Ϣ*/
typedef struct tagACC_SINGLE_CFG_S
{
    BSP_U32 u32BearId;
    BSP_U32 u32AppdHeaderLen;
    BSP_U32 u32HeaderLen;
    BSP_U32 u32Count;
    BSP_BOOL bMemBlock;                 /* �Ƿ��ǵ��ڴ�� */
    BSP_U32 u32BlockLen;                /* ����ǵ����ڴ棬��Ҫ֪������*/
    BSP_U32 u32Offset;                  /* ʹ�����ݾ������ݰ���ʼ��ַƫ��*/
    BSP_U32 u32OutLen;                  /* ʹ�õ������ݳ���*/
    BSP_U32 u32Aph;                      /*���Ӱ�ͷ��*/
    CIHPER_ALGKEY_INFO_S stAlgKeyInfo;  /* �����������㷨��Կ������Ϣ */
} ACC_SINGLE_CFG_S;

/* CIPHER������Ϣ���� */
typedef struct tagCIHPER_SINGLE_CFG_S
{
    /*CIPHER_SINGLE_OPT_E*/BSP_U32 enOpt;          /* ������������(��DMA��������������㷨����) */
    BSP_U8 u8BearId;
    BSP_U8 u8Direction;
    CIPHER_HDR_E enAppdHeaderLen;
    CIPHER_HDR_E enHeaderLen;
    BSP_U32 u32Count;
    BSP_BOOL bMemBlock;                 /* �Ƿ��ǵ��ڴ�飬����Ϊ������Ϊ������ */
	BSP_U32 u32BlockLen;                /* ����ǵ����ڴ棬��Ҫ֪������*/
    CIHPER_ALGKEY_INFO_S stAlgKeyInfo;  /* �����������㷨��Կ������Ϣ */
} CIHPER_SINGLE_CFG_S;

typedef struct tagCIHPER_RELA_CFG_S
{
    /*CIPHER_RELA_OPT_E*/BSP_U32 enOpt;             /* ������������(��DMA��������������㷨����) */
    BSP_U8 u8BearId;
    BSP_U8 u8Direction;
    CIPHER_HDR_E enAppdHeaderLen;
    CIPHER_HDR_E enHeaderLen;
    BSP_U32 u32Count;
    BSP_BOOL bMemBlock;                 /* �Ƿ��ǵ��ڴ�� */
	BSP_U32 u32BlockLen;                /* ����ǵ����ڴ棬��Ҫ֪������*/
    CIHPER_ALGKEY_INFO_S stAlgKeyInfo;  /* ����������һ�����㷨��Կ������Ϣ */

} CIHPER_RELA_CFG_S;


typedef struct tagS_CONFIG_INFO_S
{
    KDF_SHA_S_SOURCE_E   enShaSSource;      /* sha_s��Դ*/
    BSP_U32              u32ShaSIndex;                /* sha_s��Դ��KeyRamʱ������keyRam�е�����*/
    BSP_U32              u32ShaSLength;              /* sha_s�ĳ���*/
    BSP_VOID             *pSAddr;           
}S_CONFIG_INFO_S;

typedef enum tagCIPHER_KEY_OUTPUT_E
{
    CIPHER_KEY_NOT_OUTPUT,    /*�������Կ*/
    CIPHER_KEY_OUTPUT,        /*�����Կ*/
    CIPHER_KEY_OUTPUT_BUTTOM
}CIPHER_KEY_OUTPUT_E;

typedef BSP_U32 CIPHER_KEY_LEN_E_U32;
typedef BSP_U32 CIPHER_KEY_OUTPUT_E_U32;

/* ��ȡKey���Ⱥ�Key���ݵĽṹ��*/
typedef struct
{
    CIPHER_KEY_LEN_E_U32    enKeyLen; /* Ҫ��ȡ��Key�ĳ��ȣ����ϲ㴫��*/
    BSP_VOID                *pKeyAddr; /*Keyֵ��ŵ�ַ */
    CIPHER_KEY_LEN_E_U32    *penOutKeyLen;/*�õ�ַ���ڴ��ʵ�ʷ��ص�Key�ĳ���*/
}KEY_GET_S;

/* KeyMakeʱ����ȡKey�ĳ��Ⱥ�Keyֵ*/
typedef struct
{
    CIPHER_KEY_OUTPUT_E_U32 enKeyOutput; /*ָʾ�Ƿ����Key��stKeyGet��*/
    KEY_GET_S stKeyGet;
}KEY_MAKE_S;


/* ��ɻص��������Ͷ��� */
/*
u32ChNum   :  ͨ����;
u32SourAddr:  Դ��ַ
u32DestAddr:  Ŀ�ĵ�ַ
enStatus   :  ֪ͨ��״̬,����: ��� / ���ݴ������ / ��������Լ�����
u32Private   :  �û�˽������;
*/
typedef BSP_VOID (*CIPHER_NOTIFY_CB_T)(BSP_U32 u32ChNum, BSP_U32 u32SourAddr,
              BSP_U32 u32DestAddr, CIPHER_NOTIFY_STAT_E enStatus, BSP_U32 u32Private);

typedef BSP_VOID (*CIPHER_FREEMEM_CB_T)(BSP_VOID* pMemAddr);

/**************************************************************************
  KDF���
**************************************************************************/

typedef struct tagKEY_CONFIG_INFO_S
{
    KDF_SHA_KEY_SOURCE_E enShaKeySource;    /* sha_key��Դ*/
    BSP_U32              u32ShaKeyIndex;       /* sha_key��Դ��KeyRamʱ������keyRam�е�����8 */
    BSP_VOID             *pKeySourceAddr;   /* */
}KEY_CONFIG_INFO_S;


/*****************************************************************************
* �� �� ��  : BSP_Accelerator_DMA
*
* ��������  : Ϊָ��ͨ�����������������ڵ�����DMA����
*
* �������  : u32BdFifoAddr: BDFIFO�׵�ַ
*             pInMemMgr    : ����buffer�׵�ַ
*             pOutMemMgr   : ���buffer�׵�ַ
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_Accelerator_DMA(BSP_U32 u32BdFifoAddr, const BSP_VOID* pInMemMgr, const BSP_VOID* pOutMemMgr,ACC_SINGLE_CFG_S *pstCfg);

/*****************************************************************************
* �� �� ��  : BSP_Accelerator_Cipher
*
* ��������  : Ϊָ��ͨ��������������������ҪCipher���м��ܵĲ���
*
* �������  : u32BdFifoAddr: BDFIFO�׵�ַ
*             pInMemMgr    : ����buffer�׵�ַ
*             pOutMemMgr   : ���buffer�׵�ַ
*             pstCfg       : Cipher������Ϣ
* �������   : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_Accelerator_Cipher(BSP_U32 u32BdFifoAddr, const BSP_VOID* pInMemMgr, const BSP_VOID* pOutMemMgr,
               ACC_SINGLE_CFG_S *pstCfg);


/**************************************************************************
 ��������
**************************************************************************/

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_RegistNotifyCB
*
* ��������  : ע��֪ͨ�ص�����
*
* �������  : pFunNotifyCb: ֪ͨ�ص�����
*
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*****************************************************************************/
BSP_S32 BSP_CIPHER_RegistNotifyCB(CIPHER_NOTIFY_CB_T pFunNotifyCb);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_FreeMemCB
*
* ��������  : ע��Memory�ͷŻص�����
*
* �������  : u32Chn: ͨ����
*             bSrc:   0:����Buffer / 1:���Bufffer
*             pFunFreeMemCb: Memory�ͷŻص�����
*
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*****************************************************************************/
BSP_S32 BSP_CIPHER_RegistFreeMemCB(BSP_U32 u32Chn, BSP_BOOL bSrc, CIPHER_FREEMEM_CB_T pFunFreeMemCb);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_Purge
*
* ��������  : ������е�ǰָ��ͨ����CIPHER����(�����ӿ�,���purge�󷵻�)
*
* �������  : u32Chn: Ҫ�����ͨ����
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*           :      CIPHER_TIME_OUT
*****************************************************************************/
BSP_S32 BSP_CIPHER_Purge(BSP_U32 u32Chn);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_SingleSubmitTask
*
* ��������  : ��ʼCIPHER ָ��ͨ���Ĺ��������ڵ���������
*
* �������  : u32Chn: ͨ����
*             pInMemMgr: ����buffer�ڴ����ṹָ��
*             pOutMemMgr:���buffer�ڴ����ṹָ��
*             pstCfg: Cipher������������
*             pstSubmAttr:�ύ������
*             u32Private:˽������
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*             ʧ��:CIPHER_NOT_INIT
*             CIPHER_INVALID_CHN
*             CIPHER_NULL_PTR
*             CIPHER_ALIGN_ERROR
*             CIPHER_INVALID_ENUM
*             CIPHER_PURGING
*             CIPHER_FIFO_FULL
*             CIPHER_TIME_OUT
*****************************************************************************/
BSP_S32 BSP_CIPHER_SingleSubmitTask(BSP_U32 u32Chn, const BSP_VOID* pInMemMgr, const BSP_VOID* pOutMemMgr,
                   CIHPER_SINGLE_CFG_S *pstCfg, CIPHER_SUBMIT_TYPE_E enSubmAttr, BSP_U32 u32Private);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_RelaSubmitTask
*
* ��������  : ��ʼCIPHER ָ��ͨ���Ĺ��������ڹ���������
*
* �������  : u32Chn: ͨ����
*             pInMemMgr: ����buffer�ڴ����ṹָ��
*             pOutMemMgr:���buffer�ڴ����ṹָ��
*             pstCfg: Cipher������������
*             enSubmAttr:�ύ������
*             u32Private:˽������
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*             ʧ��:CIPHER_NOT_INIT
*             CIPHER_INVALID_CHN
*             CIPHER_NULL_PTR
*             CIPHER_ALIGN_ERROR
*             CIPHER_INVALID_ENUM
*             CIPHER_PURGING
*             CIPHER_FIFO_FULL
*             CIPHER_TIME_OUT
*****************************************************************************/
BSP_S32 BSP_CIPHER_RelaSubmitTask(BSP_U32 u32Chn, const BSP_VOID* pInMemMgr, const BSP_VOID* pOutMemMgr,
                   CIHPER_RELA_CFG_S *pstCfg, CIPHER_SUBMIT_TYPE_E enSubmAttr, BSP_U32 u32Private);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_SetKeyIndex
*
* ��������  : ������Կֵ
*
* �������  : pKeyAddr   : ��Կ��ַ
*             enKeyLen   : ��Կ����
*             u32KeyIndex: ��Կ����
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_NULL_PTR
*           :      CIPHER_INVALID_ENUM
*           :      CIPHER_INVALID_KEY
*****************************************************************************/
BSP_S32 BSP_CIPHER_SetKey(const BSP_VOID* pKeyAddr,CIPHER_KEY_LEN_E enKeyLen,BSP_U32 u32KeyIndex);

/*****************************************************************************
* �� �� ��  : BSP_CIPHER_GetKey
*
* ��������  : ����KeyIndex��ȡKey�ĵ�ַ
*
* �������  : u32KeyIndex: ��Կ����
* �������  : ��
* �� �� ֵ  : �ɹ�:����KeyIndex�õ���Key�ĵ�ַ
*           : ʧ��:��ȡKeyֵ���ڵ�ַʧ��,����0
*****************************************************************************/
BSP_S32 BSP_CIPHER_GetKey(BSP_U32 u32KeyIndex, KEY_GET_S *pstKeyGet);

/*****************************************************************************
* �� �� ��  : CIPHER_DataBuffPara
*
* ��������  : ��ȡ�ϲ�������Ϣ��������Ϣ
*
* �������  : u32Chn        : ͨ����
*             bSrc          : TRUE:Դ��ַ���������� / FALSE:Ŀ�ĵ�ַ��������
*             u32BufOft     : ����bufferָ��ƫ��
*             u32LenOft     : Buffer����ƫ��
*             NextOft       : ��һ�ڵ�ƫ��
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*****************************************************************************/
BSP_S32 BSP_CIPHER_SetDataBufPara(BSP_U32 u32Chn, BSP_BOOL bSrc, BSP_U32 u32BufOft,
                                 BSP_U32 u32LenOft, BSP_U32 u32NextOft);

/*****************************************************************************
* �� �� ��  : CIPHER_GetCmplSrcBuff
*
* ��������  : ��ȡ�Ѿ�������ɵ�Դ���ݵ�ַ
*
* �������  : u32ChNum     : ͨ����
* �������  : pu32SourAddr : ������ɵ�Դ��ַ;
*             pu32DestAddr : ������ɵ�Ŀ�ĵ�ַ
*             penStatus    : ������ɵ�״̬
*             pu32Private  : ���ص�˽������
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*           :      CIPHER_NULL_PTR
*           :      CIPHER_INVALID_RD
*****************************************************************************/
BSP_S32 BSP_CIPHER_GetCmplSrcBuff(BSP_U32 u32Chn, BSP_U32 *pu32SourAddr,
             BSP_U32 *pu32DestAddr, CIPHER_NOTIFY_STAT_E *penStatus, BSP_U32 *pu32Private);

/*****************************************************************************
* �� �� ��  : BSP_Accelerator_GetBdFifoAddr
*
* ��������  : ���ڻ�ȡ��ǰ���õ�BDFIFO�׵�ַ
*
* �������  : ��
*
* �������  : ��
* �� �� ֵ  : BDFIFO�׵�ַ
*****************************************************************************/
BSP_U32 BSP_Accelerator_GetBdFifoAddr(void);

/*****************************************************************************
* �� �� ��  : BSP_Accelerator_GetStatus
*
* ��������  : ��ȡ��ǰͨ��״̬
*
* �������  :  ��
* �������   : ��
* �� �� ֵ  : ͨ��æ/����
*****************************************************************************/
BSP_S32 BSP_Accelerator_GetStatus(void);

/*****************************************************************************
* �� �� ��  : BSP_Accelerator_Enable
*
* ��������  : ʹ���������
*
* �������  : u32BdFifoAddr: BDFIFO�׵�ַ
*
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_Accelerator_Enable(BSP_U32 u32BdFifoAddr);

/*****************************************************************************
* �� �� ��  : BSP_KDF_KeyRamRead()
*
* ��������  : ��Key Ram�ж�ȡ����
*
* �������  : enKeyIndex: Key�������Ӹ���������ʼ��ȡ����
*             u32Length : ��ȡ���ݳ��ȣ���ByteΪ��λ
* �������  : pDestAddr : Ŀ�ĵ�ַ������KeyRam�ж�ȡ�����ݴ洢����λ��
* �� �� ֵ  : �ɹ�: BSP_OK
*           : ʧ��: BSP_ERROR
*****************************************************************************/
BSP_S32 BSP_KDF_KeyRamRead(BSP_VOID *pDestAddr, BSP_U32 u32KeyIndex ,BSP_U32 u32ReadLength);

/*****************************************************************************
* �� �� ��  : BSP_KDF_KeyRamWrite
*
* ��������  : ��KeyRam��д������
*
* �������  : enKeyIndex: Key�������Ӹ���������ʼд������
*             pSourAddr : Դ��ַ��д�뵽KeyRam�е����ݵ�ַ
*             u32Length : ���ݳ���
*
* �������  : ��
* �� �� ֵ  : �ɹ�: BSP_OK
*           : ʧ��: BSP_ERROR
*****************************************************************************/
BSP_S32 BSP_KDF_KeyRamWrite(BSP_U32 u32KeyIndex, BSP_VOID *pSourAddr, BSP_U32 u32Length);


/*****************************************************************************
* �� �� ��  : BSP_KDF_KeyMake
*
* ��������  : KDF���㣬���ڲ����µ�Key
*
* �������  : stKeyCfgInfo: KDF����ʱ����sha_key��������
            : stKeyCfgInfo: KDF����ʱ����sha_s��������
            : enDestIndex : KDF���������Key������KeyRam�е�λ��
* �������  : ��
* �� �� ֵ  : �ɹ�:BSP_OK
*           : ʧ��:BSP_ERROR
*****************************************************************************/
BSP_S32 BSP_KDF_KeyMake(KEY_CONFIG_INFO_S *pstKeyCfgInfo, S_CONFIG_INFO_S *pstSCfgInfo,
                        BSP_U32 u32DestIndex, KEY_MAKE_S *pstKeyMake);


BSP_S32 BSP_CIPHER_Disable(void);
BSP_S32 BSP_CIPHER_Enable(void);

/**************************************************************************
  �궨��
**************************************************************************/

/* ע��CIPHER������ҪΪ��ֵ */
#define CIPHER_ERROR_BASE               0x80000800

typedef enum tagCIPHER_ERR_CODE_E
{
    CIPHER_ERR_CODE_NULL_PTR = 1,
    CIPHER_ERR_CODE_NO_MEM ,
    CIPHER_ERR_CODE_NOT_INIT ,
    CIPHER_ERR_CODE_FIFO_FULL ,
    CIPHER_ERR_CODE_INVALID_CHN ,
    CIPHER_ERR_CODE_INVALID_OPT ,
    CIPHER_ERR_CODE_ALIGN_ERROR ,
    CIPHER_ERR_CODE_PURGING ,
    CIPHER_ERR_CODE_TIME_OUT,
    CIPHER_ERR_CODE_INVALID_ENUM,
    CIPHER_ERR_CODE_INVALID_RD,
    CIPHER_ERR_CODE_RD_NULL,
    CIPHER_ERR_CODE_INVALID_KEY,
    CIPHER_ERR_CODE_CHECK_ERROR,
    CIPHER_ERR_CODE_BDLEN_ERROR,
    CIPHER_ERR_CODE_INVALID_NUM,
    CIPHER_ERR_CODE_NO_KEY,
    CIPHER_ERR_CODE_KEYLEN_ERROR,
    ACC_FIFOS_WORK,
    CIPHER_ENABLE_FAIL
}CIPHER_ERR_CODE_E;

#define CIPHER_NULL_PTR      ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NULL_PTR))
#define CIPHER_NO_MEM        ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NO_MEM))
#define CIPHER_NOT_INIT      ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NOT_INIT))
#define CIPHER_FIFO_FULL     ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_FIFO_FULL))
#define CIPHER_INVALID_CHN   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_CHN))
#define CIPHER_INVALID_OPT   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_OPT))
#define CIPHER_ALIGN_ERROR   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_ALIGN_ERROR))
#define CIPHER_PURGING       ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_PURGING))
#define CIPHER_TIME_OUT      ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_TIME_OUT))
#define CIPHER_INVALID_ENUM  ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_ENUM))
#define CIPHER_INVALID_RD    ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_RD))
#define CIPHER_RDQ_NULL      ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_RD_NULL))
#define CIPHER_INVALID_KEY   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_KEY))
#define CIPHER_CHECK_ERROR   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_CHECK_ERROR))
#define CIPHER_BDLEN_ERROR   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_BDLEN_ERROR))
#define CIPHER_INVALID_NUM   ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_NUM))
#define CIPHER_NO_KEY        ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NO_KEY))
#define CIPHER_KEYLEN_ERROR  ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_KEYLEN_ERROR))
#define ACC_ALL_FIFO_WORK    ((BSP_S32)(CIPHER_ERROR_BASE|ACC_FIFOS_WORK))
#define CIPHER_ENABLE_FAILED ((BSP_S32)(CIPHER_ERROR_BASE|CIPHER_ENABLE_FAIL))
#define CIPHER_UNKNOWN_ERROR ((BSP_S32)(CIPHER_ERROR_BASE|0xff))



/*************************CIPHER END **********************************/

#endif

