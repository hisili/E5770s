

#ifndef __DRV_AUDIO_H__
#define __DRV_AUDIO_H__

#ifdef __cplusplus
extern "C" { /* allow C++ to use these headers */
#endif /* __cplusplus */

#include "drv_comm.h"

/*************************AUDIO START*********************************/

/*AUDIO IOCTL�ӿ�������*/
#define AUDIO_IOCTL_BASE					          (0x30000000)
#define IOCTL_AUDIO_STATUS_GET                     (AUDIO_IOCTL_BASE+0)
#define IOCTL_AUDIO_SAMPLE_RATE_SET                (AUDIO_IOCTL_BASE+1)
#define IOCTL_AUDIO_PLAY_OPEN                      (AUDIO_IOCTL_BASE+2)
#define IOCTL_AUDIO_PLAY_CLOSE                     (AUDIO_IOCTL_BASE+3)
#define IOCTL_AUDIO_RECORD_OPEN                    (AUDIO_IOCTL_BASE+4)
#define IOCTL_AUDIO_RECORD_CLOSE                   (AUDIO_IOCTL_BASE+5)
#define IOCTL_AUDIO_I2S_MODE_SET                   (AUDIO_IOCTL_BASE+6)
#define IOCTL_AUDIO_PCM_MODE_SET                   (AUDIO_IOCTL_BASE+7)
#define IOCTL_AUDIO_RX_VOL_SET                     (AUDIO_IOCTL_BASE+8)
#define	IOCTL_AUDIO_TX_VOL_SET                     (AUDIO_IOCTL_BASE+9)
#define	IOCTL_AUDIO_SIDE_VOL_SET                   (AUDIO_IOCTL_BASE+10)
#define	IOCTL_AUDIO_IN_DEV_SELECT                  (AUDIO_IOCTL_BASE+11)
#define	IOCTL_AUDIO_OUT_DEV_SELECT                 (AUDIO_IOCTL_BASE+12)
#define	IOCTL_AUDIO_OUT_DEV_UNSELECT               (AUDIO_IOCTL_BASE+13)
#define	IOCTL_AUDIO_IN_DEV_UNSELECT               (AUDIO_IOCTL_BASE+14)
/************************A32D07003 Modification begins by G57837******************************************/
/*ִ��ͬ���ɼ��Ͳ���*/
#define	IOCTL_AUDIO_READ_WRITE_SET                 (AUDIO_IOCTL_BASE+15)
/*����ͬ���ɼ��Ͳ���*/
#define	IOCTL_AUDIO_VP_BEGIN                       (AUDIO_IOCTL_BASE+16)
/*����ͬ���ɼ��Ͳ���*/
#define	IOCTL_AUDIO_VP_END                         (AUDIO_IOCTL_BASE+17)
/************************A32D07003 Modification ends by G57837********************************************/
/************************A32D07003 Modification begins by G57837******************************************/
/*�򿪲ɼ��Ͳ���*/
#define	IOCTL_AUDIO_PLAY_RECORD_OPEN               (AUDIO_IOCTL_BASE+20)
/*�رղɼ��Ͳ���*/
#define	IOCTL_AUDIO_PLAY_RECORD_CLOSE              (AUDIO_IOCTL_BASE+21)

#define	IOCTL_AUDIO_VOICE_OPEN                     (AUDIO_IOCTL_BASE+23)
#define	IOCTL_AUDIO_VOICE_CLOSE                    (AUDIO_IOCTL_BASE+24)

#define	IOCTL_AUDIO_BT_VOICE_OPEN                  (AUDIO_IOCTL_BASE+25)
#define	IOCTL_AUDIO_BT_VOICE_CLOSE                 (AUDIO_IOCTL_BASE+26)
/* FM ���� */
#define	IOCTL_AUDIO_FM_RX_OPEN                     (AUDIO_IOCTL_BASE+27)
#define	IOCTL_AUDIO_FM_RX_CLOSE                    (AUDIO_IOCTL_BASE+28)
/* FM ���� */
#define	IOCTL_AUDIO_FM_TX_OPEN                     (AUDIO_IOCTL_BASE+29)
#define	IOCTL_AUDIO_FM_TX_CLOSE                    (AUDIO_IOCTL_BASE+30)

#define IOCTL_AUDIO_SLEEP                          (AUDIO_IOCTL_BASE+31)
#define IOCTL_AUDIO_DFS                            (AUDIO_IOCTL_BASE+32)

/*
#define	IOCTL_AUDIO_NV_WRITE                       (AUDIO_IOCTL_BASE+33)
#define	IOCTL_AUDIO_NV_READ                        (AUDIO_IOCTL_BASE+34)
*/
#define	IOCTL_AUDIO_NV_OP                          (AUDIO_IOCTL_BASE+67)

typedef enum
{
    NODEV=0x00,
    HEADSET=0x01,
    HANDSET=0x02,
    HANDFREE=0x04
}AUDIO_DEV_TYPE;

typedef enum
{
    SAMPLE_RATE_8K=0,
    SAMPLE_RATE_11K025=1,
    SAMPLE_RATE_12K=2,
    SAMPLE_RATE_16K=3,
    SAMPLE_RATE_22K05=4,
    SAMPLE_RATE_24K=5,
    SAMPLE_RATE_32K=6,
    SAMPLE_RATE_44K1=7,
    SAMPLE_RATE_48K=8,
    SAMPLE_RATE_INVALID=0xFFFF
}AUDIO_SAMPLE_RATE;


/********************************************************************************************************
 �� �� ��  : BSP_AUDIO_CodecOpen
 ��������  : ��һ��audio�豸������codec���г�ʼ����
 �������  : devname���ò����̶�Ϊ"/dev/codec0"��
                           flags���ò�����ʾ��д��ʽ���̶�Ϊ0��
                           mode���ò�����ʾ�½��ļ���ʽ���̶�Ϊ0����
  �������  : �ޡ�
 �� �� ֵ  : �Ǹ�ֵ:  �豸�����
             -1������ʧ�ܡ�
********************************************************************************************************/
int codec_open(const char *devname, int flags, int mode);
#define DRV_CODEC_OPEN(devname, flags, mode)    codec_open(devname, flags, mode)

/********************************************************************************************************
 �� �� ��  : BSP_AUDIO_Codec_ioctl
 ��������  : codec�豸�����ֿ��ơ�
 �������  : devid���豸�����
                           cmd�������֡�
                           arg�����������
  �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
int codec_ioctl(int devid, int cmd, int arg);
#define DRV_CODEC_IOCTL(devid, cmd, arg)   codec_ioctl(devid, cmd, arg)

/*************************AUDIO END***********************************/
#ifdef __cplusplus
} /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif

