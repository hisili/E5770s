/*
 *  HIFI MISC TRANS MSG
 *  Copyright (c) 1994-2013 by HISI
 *
 *   This program is distributed in the hope that we can send msg and
 *   data to hifi
 *
 */

#ifndef _AUDIO_HIFI_H
#define _AUDIO_HIFI_H

#include <linux/types.h>


typedef enum
{
    HIFI_CHN_SYNC_CMD = 0,
    HIFI_CHN_READNOTICE_CMD,
    HIFI_CHN_INVAILD_CMD
} HIFI_CHN_CMD_TYPE;

typedef struct HIFI_CHN_CMD_STRUCT
{
    HIFI_CHN_CMD_TYPE cmd_type;
    unsigned int           sn;
} HIFI_CHN_CMD;


/*
    ��Σ�͸����HIFI�Ĳ���
    ���Σ�HIFI���صģ�͸����AP�Ĳ���
*/
struct misc_io_async_param {
    void *                  para_in;        /*���buffer*/
    unsigned int            para_size_in;   /*���buffer����*/
};

/* misc_io_sync_cmd */
struct misc_io_sync_param {
    void *                  para_in;            /*���buffer*/
    unsigned int            para_size_in;       /*���buffer����*/
    void *                  para_out;           /*����buffer*/
    unsigned int            para_size_out;      /*����buffer����*/
};

/* misc_io_senddata_cmd */
struct misc_io_senddata_async_param {
    void *                  para_in;            /*���buffer*/
    unsigned int            para_size_in;       /*���buffer����*/
    void *                  data_src;           /*������Դ��ַ*/
    unsigned int            data_src_size;      /*������Դ����*/
};

/* misc_io_send_recv_data_sync_cmd */
struct misc_io_senddata_sync_param {
    void *                  para_in;            /*���buffer*/
    unsigned int            para_size_in;       /*���buffer����*/
    void *                  src;                /*����Դ��ַ*/
    unsigned int            src_size;           /*����Դ����*/
    void *                  dst;                /*��ַ*/
    unsigned int            dst_size;           /*����*/
    void *                  para_out;           /*����buffer*/
    unsigned int            para_size_out;      /*����buffer����*/
};

struct misc_io_get_phys_param {
    unsigned int            flag;               /**/
    unsigned long           phys_addr;          /*��ȡ�������ַ*/
};

struct misc_io_dump_buf_param {
    void *                  user_buf;           /*�û��ռ������ڴ��ַ*/
    unsigned int            buf_size;           /*�û��ռ������ڴ泤��*/
};

//������AP����HiFi Misc�豸��ioctl�����ҪHiFi Misc�豸������Ӧ
#define HIFI_MISC_IOCTL_ASYNCMSG        _IOWR('A', 0x70, struct misc_io_async_param)          //AP��HiFi�����첽��Ϣ
#define HIFI_MISC_IOCTL_SYNCMSG         _IOW('A', 0x71, struct misc_io_sync_param)            //AP��HiFi����ͬ����Ϣ
#define HIFI_MISC_IOCTL_SENDDATA_SYNC   _IOW('A', 0x72, struct misc_io_senddata_sync_param)    //AP��HiFiͬ����������
#define HIFI_MISC_IOCTL_GET_PHYS        _IOWR('A', 0x73, struct misc_io_get_phys_param)        //AP��ȡ�����ַ
#define HIFI_MISC_IOCTL_TEST            _IOWR('A', 0x74, struct misc_io_senddata_sync_param)   //AP������Ϣ
#define HIFI_MISC_IOCTL_WRITE_PARAMS    _IOWR('A', 0x75, struct misc_io_sync_param)            //д�㷨������HIFI

#define HIFI_MISC_IOCTL_DUMP_HIFI       _IOWR('A', 0x75, struct misc_io_dump_buf_param)        //��ȡHIFI��DDR�ϵ����ݲ��������û��ռ�
#define HIFI_MISC_IOCTL_DUMP_CODEC      _IOWR('A', 0x76, struct misc_io_dump_buf_param)        //��ȡCODEC�Ĵ������������û��ռ�

#endif // _AUDIO_HIFI_H

