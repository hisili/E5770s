#ifndef _CIPHER_DRV_SHAONLY_H
#define _CIPHER_DRV_SHAONLY_H

#include <osl_types.h>
#include <soc_memmap.h>
#include <bsp_memmap.h>
#include <hi_cipher.h>

#ifdef __cplusplus
extern "C" {
#endif
 
/* ������ */
#define CIPHER_SUCCESS   0


#define CHN_IV_SEL                 0x0
#define CHN_RDQ_CTRL               0x1
#define CHN_RDQCTRL_BIT            0x2
#define CHN_USRFIELDLEN_BIT        0x5

#define CIPHER_KEY_NUM             0x10
#define CIPHER_KEY_LEN             0x20
#define CIPHER_TIMEOUT_TICKS       100
#define CIPHER_WAIT_THREHLD        20

#define CIPHER_BSWAP32(val) \
        (((val) >> 24) | (((val) >> 8) & 0x0000ff00) | \
        (((val) << 8) & 0x00ff0000) | ((val) << 24))

#define KDF_CHN_NUM            0x4
#define KDF_CHN_USRFIELD_LEN   0x0
#define KDF_SHA_KEY_LENGTH     0x20
#define KDF_SHA_S_LENGTH_MAX   0x200

#define CIPHER_ALIGN_LEN  7

typedef enum tagKDF_SHA_KEY_SOURCE_E
{
    SHA_KEY_SOURCE_DDR,             /*sha_key��Դ��input pointָ���ĵ�ַ�ռ�*/
    SHA_KEY_SOURCE_KEYRAM,          /*sha_key��Դ���ڲ�KeyRam*/
    SHA_KEY_SOURCE_FOLLOW,          /*sha_key��Դ���ϴ�KDF������sha_key*/
    SHA_KEY_SOURCE_RESULT,          /*sha_key��Դ����һ��KDF�����Ľ��*/
    SHA_KEY_SOURCE_MAX
}KDF_SHA_KEY_SOURCE_E;

typedef enum tagKDF_SHA_S_SOURCE_E
{
    SHA_S_SOURCE_DDR,               /*sha_s��Դ��input pointָ���ĵ�ַ�ռ�*/
    SHA_S_SOURCE_KEYRAM,            /*sha_s��Դ���ڲ�KeyRam*/
    SHA_S_SOURCE_MAX
}KDF_SHA_S_SOURCE_E;

/* CIPHER֪ͨ���� */
typedef enum tagCIPHER_NOTIFY_STAT_E
{
    CIPHER_STAT_OK = 0,           /* �ɹ���� */
    CIPHER_STAT_CHECK_ERR = 1,    /* �����Լ����� */
    CIPHER_STAT_BUTTOM
}CIPHER_NOTIFY_STAT_E;

/* KDFʹ�õ�BD�ṹ*/
typedef struct tagKDF_BD_SCPT_S
{
    u32 u32KdfConfig;
    u32 u32Address;
}KDF_BD_SCPT_S;

/* KDFʹ�õ�RD�ṹ*/
typedef struct tagKDF_RD_SCPT_S
{
    u32 u32Address;
    u32 u32KdfConfig;
}KDF_RD_SCPT_S;

typedef struct tagKDF_BDCONFIG_INFO_S
{
    KDF_SHA_KEY_SOURCE_E enShaKeySource;    /*sha_key��Դ*/
    KDF_SHA_S_SOURCE_E   enShaSSource;      /*sha_s��Դ*/
    u32                  u32ShaKeyIndex;    /*sha_key��Դ��KeyRamʱ������keyRam�е�����*/
    u32                  u32ShaSIndex;      /*sha_s��Դ��KeyRamʱ������keyRam�е�����*/
    u32                  u32Length;         /*KDF������Ϊsha_s�ĳ���*/
    u32                  u32DestIndex;      /*sha_result_sn��key_ram�е�λ��*/
    void *               pAddress;          /*Ŀ��(Դ)��ַ*/
}KDF_BDCONFIG_INFO_S;

#define KEY_INDEX    0
#define BD_RD_NUM    2
#define	BDQ_SIZE	 (sizeof(KDF_BD_SCPT_S)* BD_RD_NUM)
#define	RDQ_SIZE	 (sizeof(KDF_RD_SCPT_S)* BD_RD_NUM)

struct kdf_s
{
	u32 bdq_virt_addr;
	u32 bdq_real_addr;
	u32 rdq_virt_addr;
	u32 rdq_real_addr;
	u32 brdq_length;
	u32 sha_s_buff_real_addr;
	u32 sha_s_buff_virt_addr;
	u32 buffer_virt_addr;
	u32 buffer_real_addr;
	struct clk * cifer_clk;
};
 
/**************************************************************************
  �궨��
**************************************************************************/
/* ע��CIPHER������ҪΪ��ֵ */
#define CIPHER_ERROR_BASE               0x10004000

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
    CIPHER_ERR_CODE_KEYLEN_ERROR
}CIPHER_ERR_CODE_E;

#define CIPHER_NULL_PTR      ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NULL_PTR))
#define CIPHER_NO_MEM        ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NO_MEM))
#define CIPHER_NOT_INIT      ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NOT_INIT))
#define CIPHER_FIFO_FULL     ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_FIFO_FULL))
#define CIPHER_INVALID_CHN   ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_CHN))
#define CIPHER_INVALID_OPT   ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_OPT))
#define CIPHER_ALIGN_ERROR   ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_ALIGN_ERROR))
#define CIPHER_PURGING       ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_PURGING))
#define CIPHER_TIME_OUT      ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_TIME_OUT))
#define CIPHER_INVALID_ENUM  ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_ENUM))
#define CIPHER_INVALID_RD    ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_RD))
#define CIPHER_RDQ_NULL      ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_RD_NULL))
#define CIPHER_INVALID_KEY   ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_KEY))
#define CIPHER_CHECK_ERROR   ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_CHECK_ERROR))
#define CIPHER_BDLEN_ERROR   ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_BDLEN_ERROR))
#define CIPHER_INVALID_NUM   ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_INVALID_NUM))
#define CIPHER_NO_KEY        ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_NO_KEY))
#define CIPHER_KEYLEN_ERROR  ((s32)(CIPHER_ERROR_BASE|CIPHER_ERR_CODE_KEYLEN_ERROR))
#define CIPHER_UNKNOWN_ERROR ((s32)(CIPHER_ERROR_BASE|0xff))

#ifdef __cplusplus
}
#endif

#endif
