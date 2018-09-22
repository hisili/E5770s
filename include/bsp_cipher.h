
#ifndef __BSP_CIPHER_H__
#define __BSP_CIPHER_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "osl_types.h"
#include "drv_cipher.h"


/*****************************************************************************
* �� �� ��  : bsp_acc_dma
*
* ��������  : Ϊָ��ͨ�����������������ڵ�����DMA����
*
* �������  : bd_fifo_addr: BDFIFO�׵�ַ
*             in_mem_mgr    : ����buffer�׵�ַ
*             out_mem_mgr   : ���buffer�׵�ַ
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 bsp_acc_dma(u32 bd_fifo_addr, const void* in_mem_mgr, const void* out_mem_mgr, ACC_SINGLE_CFG_S *cfg);

/*****************************************************************************
* �� �� ��  : bsp_acc_cipher
*
* ��������  : Ϊָ��ͨ��������������������ҪCipher���м��ܵĲ���
*
* �������  : bd_fifo_addr: BDFIFO�׵�ַ
*             in_mem_mgr    : ����buffer�׵�ַ
*             out_mem_mgr   : ���buffer�׵�ַ
*             cfg       : Cipher������Ϣ
* �������   : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 bsp_acc_cipher(u32 bd_fifo_addr, const void* in_mem_mgr, const void* out_mem_mgr,
               ACC_SINGLE_CFG_S *cfg);

/**************************************************************************
 ��������
**************************************************************************/

/*****************************************************************************
* �� �� ��  : bsp_cipher_regist_notify_func
*
* ��������  : ע��֪ͨ�ص�����
*
* �������  : fun_notify_func: ֪ͨ�ص�����
*
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*****************************************************************************/
s32 bsp_cipher_regist_notify_func(CIPHER_NOTIFY_CB_T fun_notify_func);

/*****************************************************************************
* �� �� ��  : bsp_cipher_regist_freemem_func
*
* ��������  : ע��Memory�ͷŻص�����
*
* �������  : chx: ͨ����
*             b_src:   0:����Buffer / 1:���Bufffer
*             func_freemem_func: Memory�ͷŻص�����
*
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*****************************************************************************/
s32 bsp_cipher_regist_freemem_func(u32 chx, s32 b_src, CIPHER_FREEMEM_CB_T func_freemem_func);

/*****************************************************************************
* �� �� ��  : bsp_cipher_purge
*
* ��������  : ������е�ǰָ��ͨ����CIPHER����(�����ӿ�,���purge�󷵻�)
*
* �������  : chx: Ҫ�����ͨ����
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*           :      CIPHER_TIME_OUT
*****************************************************************************/
s32 bsp_cipher_purge(u32 chx);

/*****************************************************************************
* �� �� ��  : bsp_cipher_single_submit_task
*
* ��������  : ��ʼCIPHER ָ��ͨ���Ĺ��������ڵ���������
*
* �������  : chx: ͨ����
*             in_mem_mgr: ����buffer�ڴ����ṹָ��
*             out_mem_mgr:���buffer�ڴ����ṹָ��
*             cfg: Cipher������������
*             subm_attr:�ύ������
*             Private:˽������
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
s32 bsp_cipher_single_submit_task(u32 chx, const void* in_mem_mgr, const void* out_mem_mgr,
                   CIHPER_SINGLE_CFG_S *cfg, CIPHER_SUBMIT_TYPE_E subm_attr, u32 Private);

/*****************************************************************************
* �� �� ��  : bsp_cipher_rela_submit_task
*
* ��������  : ��ʼCIPHER ָ��ͨ���Ĺ��������ڹ���������
*
* �������  : chx: ͨ����
*             in_mem_mgr: ����buffer�ڴ����ṹָ��
*             out_mem_mgr:���buffer�ڴ����ṹָ��
*             p_cfg: Cipher������������
*             subm_attr:�ύ������
*             Private:˽������
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
s32 bsp_cipher_rela_submit_task(u32 chx, const void* in_mem_mgr, const void* out_mem_mgr,
                   CIHPER_RELA_CFG_S *p_cfg, CIPHER_SUBMIT_TYPE_E subm_attr, u32 Private);

/*****************************************************************************
* �� �� ��  : bsp_cipher_setkey
*
* ��������  : ������Կֵ
*
* �������  : key_addr   : ��Կ��ַ
*             key_len   : ��Կ����
*             key_index: ��Կ����
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_NULL_PTR
*           :      CIPHER_INVALID_ENUM
*           :      CIPHER_INVALID_KEY
*****************************************************************************/
s32 bsp_cipher_setkey(const void* key_addr,CIPHER_KEY_LEN_E key_len,u32 key_index);

/*****************************************************************************
* �� �� ��  : bsp_cipher_getkey
*
* ��������  : ����key_index��ȡKey�ĵ�ַ
*
* �������  : key_index: ��Կ����
* �������  : ��
* �� �� ֵ  : �ɹ�:����KeyIndex�õ���Key�ĵ�ַ
*           : ʧ��:��ȡKeyֵ���ڵ�ַʧ��,����0
*****************************************************************************/
s32 bsp_cipher_getkey(u32 key_index, KEY_GET_S *key_get);

/*****************************************************************************
* �� �� ��  : bsp_cipher_set_data_buf_para
*
* ��������  : ��ȡ�ϲ�������Ϣ��������Ϣ
*
* �������  : chx        : ͨ����
*             b_src          : TRUE:Դ��ַ���������� / FALSE:Ŀ�ĵ�ַ��������
*             buf_oft     : ����bufferָ��ƫ��
*             len_oft     : Buffer����ƫ��
*             next_oft       : ��һ�ڵ�ƫ��
* �������  : ��
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*****************************************************************************/
s32 bsp_cipher_set_data_buf_para(u32 chx, s32 b_src, u32 buf_oft, u32 len_oft, u32 next_oft);

/*****************************************************************************
* �� �� ��  : bsp_cipher_get_cmpl_src_buff
*
* ��������  : ��ȡ�Ѿ�������ɵ�Դ���ݵ�ַ
*
* �������  : chx     : ͨ����
* �������  : src_addr : ������ɵ�Դ��ַ;
*             dest_addr : ������ɵ�Ŀ�ĵ�ַ
*             status    : ������ɵ�״̬
*             Private  : ���ص�˽������
* �� �� ֵ  : �ɹ�:CIPHER_SUCCESS
*           : ʧ��:CIPHER_NOT_INIT
*           :      CIPHER_INVALID_CHN
*           :      CIPHER_NULL_PTR
*           :      CIPHER_INVALID_RD
*****************************************************************************/
s32 bsp_cipher_get_cmpl_src_buff(u32 chx, u32 *src_addr,u32 *dest_addr, CIPHER_NOTIFY_STAT_E *status, u32 *Private);

/*****************************************************************************
* �� �� ��  : bsp_acc_get_bdfifo_addr
*
* ��������  : ���ڻ�ȡ��ǰ���õ�BDFIFO�׵�ַ
*
* �������  : ��
*
* �������  : ��
* �� �� ֵ  : BDFIFO�׵�ַ
*****************************************************************************/
u32 bsp_acc_get_bdfifo_addr(void);

/*****************************************************************************
* �� �� ��  : bsp_acc_get_status
*
* ��������  : ��ȡ��ǰͨ��״̬
*
* �������  :  ��
* �������   : ��
* �� �� ֵ  : ͨ��æ/����
*****************************************************************************/
s32 bsp_acc_get_status(void);

/*****************************************************************************
* �� �� ��  : bsp_acc_enable
*
* ��������  : ʹ���������
*
* �������  : u32BdFifoAddr: BDFIFO�׵�ַ
*
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
s32 bsp_acc_enable(u32 bd_fifo_addr);

/*****************************************************************************
* �� �� ��  : bsp_kdf_key_ram_read()
*
* ��������  : ��Key Ram�ж�ȡ����
*
* �������  : key_index: Key�������Ӹ���������ʼ��ȡ����
*             read_length : ��ȡ���ݳ��ȣ���ByteΪ��λ
* �������  : dest_addr : Ŀ�ĵ�ַ������KeyRam�ж�ȡ�����ݴ洢����λ��
* �� �� ֵ  : �ɹ�: BSP_OK
*           : ʧ��: BSP_ERROR
*****************************************************************************/
s32 bsp_kdf_key_ram_read(void *dest_addr, u32 key_index ,u32 read_length);

/*****************************************************************************
* �� �� ��  : bsp_kdf_key_ram_write
*
* ��������  : ��KeyRam��д������
*
* �������  : key_index: Key�������Ӹ���������ʼд������
*             src_addr : Դ��ַ��д�뵽KeyRam�е����ݵ�ַ
*             length : ���ݳ���
*
* �������  : ��
* �� �� ֵ  : �ɹ�: BSP_OK
*           : ʧ��: BSP_ERROR
*****************************************************************************/
s32 bsp_kdf_key_ram_write(u32 key_index, void *src_addr, u32 length);

/*****************************************************************************
* �� �� ��  : bsp_kdf_key_make
*
* ��������  : KDF���㣬���ڲ����µ�Key
*
* �������  : key_cfg_info: KDF����ʱ����sha_key��������
            : s_cfg_info: KDF����ʱ����sha_s��������
            : dest_index : KDF���������Key������KeyRam�е�λ��
* �������  : ��
* �� �� ֵ  : �ɹ�:BSP_OK
*           : ʧ��:BSP_ERROR
*****************************************************************************/
s32 bsp_kdf_key_make(KEY_CONFIG_INFO_S *key_cfg_info, S_CONFIG_INFO_S *s_cfg_info,
                        u32 dest_index, KEY_MAKE_S *key_make);

int cipher_close_clk(void);
int cipher_open_clk(void);

/*************************CIPHER END **********************************/

/*************************KDF HASH START **********************************/
/*****************************************************************************
* �� �� ��  : kdf_init
*
* ��������  : A��KDF���пռ������ʼ�������ڼ���HASHֵ����C������֮ǰʹ��
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : 0    : ��ȷ
*             ���� : ����
*****************************************************************************/
int kdf_init(void);

int kdf_hash_init(void);
int kdfdev_init(void);
void kdfdev_exit(void);
/*****************************************************************************
* �� �� ��  : kdf_reg_init
*
* ��������  : A��KDF�Ĵ������ã����ڼ���HASHֵ����C������֮ǰʹ��
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
void kdf_reg_init(void);
/*****************************************************************************
* �� �� ��  : kdf_hash_setkey
*
* ��������  : A��KDF��������key�����ڼ���HASHֵ����C������֮ǰʹ��
*
* �������  : ����key���׵�ַ��Ĭ��key�ĳ��ȹ̶�Ϊ32�ֽ�
* �������  : ��
* �� �� ֵ  : 0    : ��ȷ
*             ���� : ����
*****************************************************************************/
int kdf_hash_setkey(void * key_addr);
/*****************************************************************************
* �� �� ��  : kdf_result_hash_get
*
* ��������  : A��KDF������ȡ���HASH����C������֮ǰʹ��
*
* �������  : ��
* �������  : out_hash : ���ڽ��ս��HASH���ڴ�ռ��׵�ַ��Ĭ������32�ֽ�
* �� �� ֵ  : 0    : ��ȷ
*             ���� : ����
*****************************************************************************/
int kdf_result_hash_get(void * out_hash);
/*****************************************************************************
* �� �� ��  : kdf_hash_make
*
* ��������  : A��KDF��������HASH����C������֮ǰʹ��
*
* �������  : sha_s_addr : �������ݵ��׵�ַ��������󳤶Ȳ��ܳ���512�ֽ�
*             sha_s_len  : �������ݵ�ʵ�ʳ��ȣ����ֽ�Ϊ��λ
* �������  : ��
* �� �� ֵ  : 0    : ��ȷ
*             ���� : ����
*****************************************************************************/
int kdf_hash_make(void * sha_s_addr, u32 sha_s_len);
/*************************KDF HASH END **********************************/

#endif /* end of __BSP_CIPHER_H__ */


