
#ifndef __DRV_MAILBOX_GUT_H__
#define __DRV_MAILBOX_GUT_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "drv_mailbox_platform.h"
#include "drv_mailbox_debug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*����ID����ɺͻ�ȡ��ϵ��ת����*/
#define MAILBOX_SINGLE_ID_MASK                      (0xFF)  /*����ŵĵ���Ԫ�غ�(8bit)����λ*/
#define mailbox_get_channel_id(id)                    ((id) & (~MAILBOX_SINGLE_ID_MASK))    /*���ʼ�ID�������ID*/

/*���ʼ�ID���ԴCPUID*/
#define mailbox_get_src_id(id)  (unsigned char)(((id) >> MAILBOX_ID_SRC_CPU_OFFSET) & MAILBOX_SINGLE_ID_MASK)

/*���ʼ�ID���Ŀ��CPUID*/
#define mailbox_get_dst_id(id)  (unsigned char)(((id) >> MAILBOX_ID_DST_CPU_OFFSET) & MAILBOX_SINGLE_ID_MASK)

/*���ʼ�ID���ͨ������������ID*/
#define mailbox_get_carrier_id(id)  (unsigned char)(((id) >> MAILBOX_ID_CHANNEL_OFFSET) & MAILBOX_SINGLE_ID_MASK)

/*���ʼ�ID����ʼ�Ӧ��ID*/
#define mailbox_get_use_id(id)  (unsigned char)((id) & MAILBOX_SINGLE_ID_MASK )

/*��ʾ�����Ѿ���ʼ����ħ������*/
#define MAILBOX_INIT_MAGIC                          (0x87654312)

/*a��p�ֽڶ���*/
#define MAILBOX_ALIGN                                sizeof(unsigned long)
#define mailbox_align_size(a,p)                     (((a)+((p)-1)) & ~((p)-1))

/*д�����ַ*/
#define mailbox_write_reg(Addr, Value)                  (*((volatile unsigned long *)(Addr)) = Value)

/* ����CPU���� */
#define MAILBOX_CPU_NUM                             (MAILBOX_CPUID_BUTT)

/* ����channel���� */
#define MAILBOX_CHANNEL_BUTT(src, dst)  (MAILBOX_CHANNEL_##src##2##dst##_BUTT  & 0xff) /*& 0xff ��pclint*/

/* ����user id������ֵ */
#define MAILBOX_USER_BUTT(src, dst, channel)    \
    ((unsigned long)MAILBOX_MAILCODE_ITEM_END(src, dst, channel) & 0xff)

/*�������ݽṹ struct mb_cfg �е�Ԫ��*/
#define MAILBOX_CHANNEL_COMPOSE(src, dst, ch)                   \
    /*channel*/                                                 \
    {(unsigned long)MAILBOX_MAILCODE_ITEM_END(src, dst, ch),    \
    /*DataSize*/                                                \
    (unsigned long)MAILBOX_QUEUE_SIZE(src, dst, ch),            \
    /*SingleMax*/                                               \
    (unsigned long)MAILBOX_MAILSIZE_MAX(src, dst, ch),          \
    /*HeadAddr*/                                                \
    (unsigned long)MEM_CORE_SHARE_PHY2VIRT(MAILBOX_HEAD_ADDR(src, dst, ch)), \
    /*DataAddr*/                                                \
    (unsigned long)MEM_CORE_SHARE_PHY2VIRT(MAILBOX_QUEUE_ADDR(src, dst, ch)),\
    /*IPC INT NUMBER*/                                          \
    (unsigned long)MAILBOX_IPC_INT_NUM(src, dst, ch)}


#define MAILBOX_USER_QUEUE(mbuf)   (&((struct mb_buff *)(mbuf))->usr_queue)

/*��������ʣ��ռ䣬Ϊ�˷�ֹ����ͷβ�ص�ȥ����4byte�ռ�δʹ�ã���λbyte*/
#define mailbox_queue_left(Rear, Front, Length) \
           (((Rear) > (Front)) ? ((Rear) - (Front) - sizeof(unsigned long)): \
           ((Length) - ((Front) - (Rear)) - sizeof(unsigned long)))

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
typedef struct mb_queue
{
    unsigned long               base;            /* ���л���ַ       */
    unsigned long               length;          /* �����ܳ��ȣ���λbyte */
    unsigned long               front;           /* ����дָ��, ���Ե�ַ��in   */
    unsigned long               rear;            /* ���ж�ָ��, ���Ե�ַ��out  */
    unsigned long               size;        /* �˶��е��ζ�ȡ�ĳ���, ����Ӧ�ò�ص�֪ͨ��ȡ����*/
}mailbox_queue_stru ;

/*****************************************************************************
 �ṹ��    : DRV_MAILBOX_ID_ST
 �ṹ˵��  : �����ʼ�ID�ŵ����ݽṹ���� MAILBOX_MAIL_ID_E
 ****************************************************************************/
struct mailbox_id_stru
{
    signed char                 UseId;
    signed char                 Channel;
    signed char                 DstCpu;
    signed char                 SrcCpu;
};

/*****************************************************************************
  ����ͨ������use id �켣���ݽṹ
*****************************************************************************/

struct mb_cb
{
    void (*func)(void *mbuf, void *handle, void *data);
    void                *handle;         /*�����û�����*/
    void                *data;           /*�����û�����*/
};

/*****************************************************************************
 ʵ������  : struct mb_cfg
 ��������  : Mailbox ĳ����������ͨ����Ӳ����Դ����
*****************************************************************************/
typedef struct mb_cfg
{
    unsigned long               butt_id;     /*����ID�Ľ����ţ��������ǰ��������ID��Ϣ  */
    unsigned long               data_size;   /*�������ݴ�С*/
    unsigned long               single_max;  /*�����ʼ���������С*/
    unsigned long               head_addr;   /*����ͷ�ڴ��ַ  */
    unsigned long               data_addr;   /*���������ڴ��ַ*/
    unsigned long               int_src;     /*��������ͨ��ID��Ӧ�ĺ˼��ж���Դ��*/
}MAILBOX_CHANNEL_CFG_STRU;

/*****************************************************************************
  ����ͨ���Ĳ�����Դ����
*****************************************************************************/
struct mb_buff
{
    unsigned long               channel_id;  /*����ͨ��ID��������������֮�����·����·���򣬺�����ͨ��������ȷ��*/
    unsigned long               mailcode;    /*�ʼ�ID��������������֮�����·����·��������ͨ���ţ���Ӧ�ú��ĸ�����ȷ��*/
    unsigned long               seq_num;     /*������Ϣ���к�(SN��)��¼ȫ�ֱ���*/
    void                       *mutex;       /*������ƣ���ֹ����߳�ͬʱ�������ݵ���ͬ����*/
    struct mb                  *mb;
    struct mb_cb               *read_cb;    /*������ͨ���Ĺ��ܻص���������*/
    struct mb_cfg              *config;     /*������Ĺ����ڴ�ͨ����Ϣ*/
#ifdef MAILBOX_OPEN_MNTN
    struct mb_mntn              mntn;       /*������ͨ���Ŀ�ά�ɲ�����*/
#endif
    struct mb_queue             mail_queue; /*���ڴ˹����ڴ��������ݴ���Ļ��ζ��в������*/
    struct mb_queue             usr_queue;  /*���û�ʹ�õ����ݣ��������ʼ�ͷ��С��mail_queue*/
};

/*****************************************************************************
  ��������ͨ�����ñ���
*****************************************************************************/
typedef struct mb_link
{
    unsigned long          carrier_butt;    /*��ǰCPU�����ж��ٸ�����ͨ��*/
    struct mb_buff        *channel_buff;    /*������Ŀ�����Դ����*/
}MAILBOX_LINK_STRU ;

/*****************************************************************************
  ����ģ���������ƾ�����ݽṹ,����Ⱥ�Ŀ��ƾ������
*****************************************************************************/
typedef struct mb
{
    unsigned long               local_id;                           /*��ǰCPU��ID*/
    unsigned long               init_flag;                          /*��ʼ����־*/
    unsigned long               log_prob;                           /*ָ����һ�������¼*/
    struct mb_log               log_array[MAILBOX_ERRO_ARRAY_NUM];  /*��¼����ļ��δ�����Ϣ*/
    struct mb_link              send_tbl[MAILBOX_CPUID_BUTT];       /*���䷢��ͨ��������Դ�б�*/
    struct mb_link              recv_tbl[MAILBOX_CPUID_BUTT];       /*�������ͨ��������Դ�б�*/
}MAILBOX_STRU;

/*****************************************************************************
  7 UNION����
*****************************************************************************/

/*****************************************************************************
  8 OTHERS����
*****************************************************************************/

/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/

/*���������Ѵ��ڵĹ����ڴ�ͨ���������ڴ漰Ӳ����Դ���ã�ȫ�ֶ���*/
extern MAILBOX_EXTERN struct mb_cfg g_mailbox_global_cfg_tbl[];

/*ƽ̨����ͨ��������ڴ�ؿռ�*/
extern MAILBOX_EXTERN struct mb_buff  g_mailbox_channel_handle_pool[MAILBOX_CHANNEL_NUM];

/*ƽ̨�����û��ص�������ڴ�ؿռ�*/
extern MAILBOX_EXTERN struct mb_cb    g_mailbox_user_cb_pool[MAILBOX_USER_NUM];

/*����ģ���ܿ��ƾ��*/
extern MAILBOX_EXTERN struct mb g_mailbox_handle;
/*****************************************************************************
  10 ��������
*****************************************************************************/
MAILBOX_EXTERN struct mb *mailbox_get_mb(void);

MAILBOX_EXTERN struct mb_buff *mailbox_get_channel_handle(struct mb *mb, unsigned long mailcode);

MAILBOX_EXTERN long mailbox_register_cb( 
                unsigned long  mail_code,
                void (*cb)(void *mbuf, void *handle, void *data),
                void *usr_handle,
                void *usr_data);
                
MAILBOX_EXTERN  long mailbox_request_buff(unsigned long mailcode,  struct mb_buff ** mbuf);

MAILBOX_EXTERN long mailbox_sealup_buff(struct mb_buff * mb_buf , unsigned long usr_size);

MAILBOX_EXTERN long mailbox_flush_buff( struct mb_buff *mbuff);

MAILBOX_EXTERN long mailbox_send_buff(struct mb_buff * mb_buf);

MAILBOX_EXTERN long mailbox_release_buff(struct mb_buff * mb_buf);

MAILBOX_EXTERN  long mailbox_write_buff(
                struct mb_queue      *queue,
                 char                *data,
                unsigned long         size);

MAILBOX_EXTERN long mailbox_read_buff(
                struct mb_queue      *queue,
                 char                *data,
                unsigned long         size);

MAILBOX_EXTERN long mailbox_virt_to_phy(unsigned long  virt_addr);

MAILBOX_EXTERN long mailbox_phy_to_virt(unsigned long  phy_addr);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of drv_mailbox.h */

