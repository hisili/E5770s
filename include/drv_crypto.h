

#ifndef __DRV_CYPTO_H__
#define __DRV_CYPTO_H__

#include "drv_comm.h"


/*************************MD5��� START*******************************/
/*Ϊ�˼�����ǰ�İ汾����ģ���ʹ��*/
#if (FEATURE_ON == MBB_SIMLOCK_THREE)
/*****************************************************************************
 �� �� ��  : VerifySIMLock
 ��������  : �жϵ�ǰ�������Ƿ���ȷ .
 �������  : imei       - ����IMEI��
             unlockcode - ������
 �������  : �ޡ�
 �� �� ֵ  : 1��   �����ɹ�
             0:    ����ʧ��
*****************************************************************************/
#define DRV_CARDLOCK_MD5_VERIFY(unlockcode, imei)  VerifySL(unlockcode, imei)
extern int VerifySL(char* UnlockCode, char* Key);

/*****************************************************************************
 �� �� ��  : VerifyCARDLock
 ��������  : �жϵ�ǰ�������Ƿ���ȷ .
 �������  : imei       - ����IMEI��
             unlockcode - ������
 �������  : �ޡ�
 �� �� ֵ  : 1��   �����ɹ�
             0:    ����ʧ��
*****************************************************************************/
#define DRV_SIMLOCK_MD5_VERIFY(unlockcode, imei)  VerifyCL(unlockcode, imei)
extern int VerifyCL(char* UnlockCode, char* Key);



extern int GetAuthVer(void);
#define DRV_GET_AUTH_VER()  GetAuthVer()

extern BSP_U32 combine_two_str_get_hash(BSP_U8* str1, BSP_U32 str1_len, \
    BSP_U8* str2, BSP_U32 str2_len, BSP_U8* result_hash, BSP_U32 result_hash_len);
#define DRV_COMBINE_TWO_STR_GET_HASH(str1, str1_len, str2, str2_len, result_hash, result_hash_len) \
    combine_two_str_get_hash(str1, str1_len, str2, str2_len, result_hash, result_hash_len)

extern BSP_U32 check_hash_invalid(BSP_U8* hash_buf);
#define DRV_CHECK_HASH_INVALID(hash_buf) check_hash_invalid(hash_buf)

#endif

#if (FEATURE_ON == MBB_SIMLOCK_FOUR)
extern int VerifyCL(char* UnlockCode, char* Key);
extern int VerifySL(char* UnlockCode, char* Key);
extern int GetAuthVer(void);
extern void drv_hwlock_init( void );
#define DRV_GET_AUTH_VER()                                  GetAuthVer()
#define DRV_CARDLOCK_MD5_VERIFY(unlockcode, imei)           VerifySL(unlockcode, imei)
#define DRV_SIMLOCK_MD5_VERIFY(unlockcode, imei)            VerifyCL(unlockcode, imei)
#define DRV_HW_LOCK_VERIFY_PROC(lock_para, para_len, type)  hwlock_verify_request(lock_para, para_len, type)
#endif/*FEATURE_ON == MBB_SIMLOCK_FOUR*/

/*************************MD5��� END*********************************/
/*for create_crypto_key,hash algorithm enum*/
typedef enum 
{
    CREATE_CRYPTO_KEY_ALGORITHM_MD5 = 0x0,
    CREATE_CRYPTO_KEY_ALGORITHM_SHA1,
    CREATE_CRYPTO_KEY_ALGORITHM_SHA256,
    CREATE_CRYPTO_KEY_ALGORITHM_MAX
}CREATE_CRYPTO_KEY_ALGORITHM;

/*for crypto_hash,hash algorithm enum*/
typedef enum 
{
    CRYPTO_ALGORITHM_MD5 = 0x0,
    CRYPTO_ALGORITHM_SHA1,
    CRYPTO_ALGORITHM_SHA256,
    CRYPTO_ALGORITHM_MAX
}CRYPTO_HASH_ALGORITHM;

/*for crypto_encrypt,aes algorithm enum*/
typedef enum 
{
    CRYPTO_ENCRYPT_ALGORITHM_AES_ECB = 0x0,
#if(FEATURE_ON == MBB_WPG_LTE_ATTACH_APN_LIST)
    CRYPTO_ENCRYPT_ALGORITHM_AES_CBC = 0x1,/*8fix IV,8 input IV*/
    CRYPTO_ENCRYPT_ALGORITHM_AES_CBC_ORI = 0x2, /* ori 10bytes IV*/
#endif
    CRYPTO_ENCRYPT_ALGORITHM_MAX
}CRYPTO_ENCRYPT_ALGORITHM;

#if (FEATURE_ON == MBB_WPG_LTE_ATTACH_APN_LIST)
int FOTA_AES_Crypto_Decrypt (
    char *cipher_data,
    int cipher_len,
    CRYPTO_ENCRYPT_ALGORITHM algorithm,
    char *key,
    int klen,
    char *data,
    int *len,
    unsigned char *iv);

int wb_aes_decrypt_cbc(
        const unsigned char* iv,
        const unsigned char* input, unsigned int in_len,
        unsigned char* output, unsigned int* out_len);
#endif


int create_crypto_key(char *data, int len, CREATE_CRYPTO_KEY_ALGORITHM algorithm, char *key, int *klen);
#define CREATE_CRYPTO_KEY(data,len,algorithm,key,klen)  create_crypto_key(data,len,algorithm,key,klen)


int crypto_hash(char *data, int len, CRYPTO_HASH_ALGORITHM algorithm, char *hash, int *hlen);
#define CRYPTO_HASH(data,len,algorithm,hash,hlen)  crypto_hash(data,len,algorithm,hash,hlen)


int crypto_encrypt (char *data, int len, CRYPTO_ENCRYPT_ALGORITHM algorithm, char *key, int klen, char *cipher_data, int *cipher_len);
#define CRYPTO_ENCRYPT(data,len,algorithm,key,klen,cipher_data,cipher_len)  \
crypto_encrypt(data,len,algorithm,key,klen,cipher_data,cipher_len)

/*****************************************************************************
* �� �� ��  : crypto_decrypt
*
* ��������  : ʹ��ָ������Կ��ָ�����㷨����������ݽ��ܣ�������ܺ�����ݡ�
*             ��ǰ֧��AES-ECB�㷨��
*
* �������  : 
*             cipher_data: ���ܵ����ݵĴ��buffer��
*             cipher_len:  �����ܵ����ݵ�ʵ�ʳ��ȡ�(byte)
*             algorithm:   ���ý����㷨����ֻ�ṩAES-ECB��
*             key:         ��Կbuffer��
*             klen:        ��Կbuffer���ȡ�(byte)
*             len:  ���ܺ�����ݵĴ��buffer��buffer size��(byte)(û�м��)
*
* �������  : 
*             data:        ���ܺ�����ݡ�
*             len:         ���ܺ�����ݳ��ȡ�(byte)
*
* �� �� ֵ  : BSP_OK:      ���ܳɹ���
*             BSP_ERROR:   ����ʧ�ܡ�
*
* ����˵��  : lenΪ����/��������������len���������ڴ�����д�ء�
*             ���Ա���ֱ�Ӵ�������sizeof()�ĺ������ý����
*
*****************************************************************************/
extern int crypto_decrypt (char *cipher_data,int cipher_len,CRYPTO_ENCRYPT_ALGORITHM algorithm, char *key, int klen, char *data, int *len);
#define CRYPTO_DECRYPT(cipher_data,cipher_len,algorithm, key, klen, data, len)  \
crypto_decrypt(cipher_data,cipher_len,algorithm, key, klen, data, len)



int crypto_rsa_encrypt (char *data, int len, char *rsa_key, int rsa_klen, char *cipher_data, int *cipher_len);
#define CRYPTO_RSA_ENCRYT(data,len,rsa_key,rsa_klen,cipher_data,cihper_len) \
crypto_rsa_encrypt(data,len,rsa_key,rsa_klen,cipher_data,cihper_len)


int crypto_rsa_decrypt (char *cipher_data, int cipher_len, char *rsa_key, int rsa_klen, char *data, int *len);
#define CRYPTO_RSA_DECRYPT(cipher_data,cihper_len,rsa_key,rsa_klen,data,len) \
crypto_rsa_decrypt(cipher_data,cihper_len,rsa_key,rsa_klen,data,len)

/*****************************************************************************
* �� �� ��  : crypto_rand
*
* ��������  : ��������ɽӿ�
* �������  : rand_data:��������buffer
*                           len:�����õ���������ֽ���
*
* �������  : 
*
* �� �� ֵ  :  BSP_OK--��ȡ������ɹ�;BSP_ERROR--��ȡʧ��
*
* ����˵��  : �ڴ��ɵ���������
*
*****************************************************************************/
int crypto_rand (char *rand_data, int len);
#define CRYPTO_RAND(rand_data,len)  crypto_rand(rand_data,len)


void _Clarinet_MD5Init(void *mdContext);
void _Clarinet_MD5Update(void *mdContext, unsigned char *inBuf, unsigned int inLen);
void _Clarinet_MD5Final(unsigned char *hash, void *mdContext);

#endif

