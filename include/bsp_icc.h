

#ifndef __BSP_ICC_H__
#define __BSP_ICC_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include <osl_common.h>
#include <drv_icc.h>
#include <bsp_ipc.h>

#define ICC_BUSY              (0x03 | NOTIFY_STOP_MASK)
#define ICC_OK                (0)
#define ICC_ERR               (-1)

/* CPU ID ���� */
enum CPU_ID
{
	ICC_CPU_MIN = IPC_CORE_ACORE,
	ICC_CPU_APP = IPC_CORE_ACORE,
	ICC_CPU_MODEM = IPC_CORE_CCORE,
	ICC_CPU_MCU = IPC_CORE_MCORE,
	ICC_CPU_TLDSP = IPC_CORE_LDSP,
	ICC_CPU_HIFI = IPC_CORE_HiFi,
	ICC_CPU_MAX
};

/* �����붨�� */
enum ICC_ERR_NO
{
	ICC_CHN_INIT_FAIL = (0x80000000 + (0 << 16)),
	ICC_MALLOC_CHANNEL_FAIL,
	ICC_MALLOC_VECTOR_FAIL,
	ICC_CREATE_TASK_FAIL,
	ICC_DEBUG_INIT_FAIL,
	ICC_CREATE_SEM_FAIL,
	ICC_REGISTER_INT_FAIL,
	ICC_INVALID_PARA,
	ICC_INVALID_NO_FIFO_SPACE,
	ICC_WAIT_SEM_TIMEOUT,
	ICC_SEND_ERR,
	ICC_RECV_ERR,
	ICC_REGISTER_CB_FAIL,
	ICC_REGISTER_DPM_FAIL,
	ICC_MALLOC_MEM_FAIL,
	ICC_NULL_PTR
};

/* ͨ��id���� */
enum ICC_CHN_ID
{
	ICC_CHN_ACORE_CCORE_MIN=0, /* add for modem reset : A/C��ͨ����ʼ��־ */
	ICC_CHN_IFC = 0,     /* acore��ccore֮���IFC������ͨ�� */
	ICC_CHN_RFILE = 1,   /* acore��ccore֮���RFILE������ͨ�� */
	ICC_CHN_NV = 2,      /* acore��ccore֮���NV������ͨ�� */
	ICC_CHN_GUOM0 = 3,  /* acore��ccore֮���GUOM0������ͨ�� */
	ICC_CHN_GUOM1,       /* acore��ccore֮���GUOM1������ͨ�� */
	ICC_CHN_GUOM2,       /* acore��ccore֮���GUOM2������ͨ�� */
	ICC_CHN_GUOM3,       /* acore��ccore֮���GUOM3������ͨ�� */
	ICC_CHN_GUOM4,       /* acore��ccore֮���GUOM4������ͨ�� */
	ICC_CHN_GUOM5,       /* acore��ccore֮���GUOM5������ͨ�� */
	ICC_CHN_CSHELL,      /* acore��ccore֮���CSHELL������ͨ�� */
	ICC_CHN_ACORE_CCORE_MAX, /* add for modem reset : A/C��ͨ��������־ */
	ICC_CHN_MCORE_CCORE, /* mcore��ccore֮���Ψһ������ͨ�� */
	ICC_CHN_MCORE_ACORE, /* mcore��acore֮���Ψһ������ͨ�� */
	ICC_CHN_ID_MAX
};

/* ˵��: ���ջص�����ID,��ͨ�����������, "ͨ������_xxx=0��ͨ������_RECV_FUNC_ID_MAX֮�䣬
 * ��: Ҫ��IFCͨ�����һ����ͨ��������ΪIFC_RECV_ONLY_TEST������Ҫ:
    IFC_RECV_FUNC_RTC_SETTIME = 0,
	IFC_RECV_FUNC_BBE,
	IFC_RECV_ONLY_TEST,
	IFC_RECV_FUNC_ID_MAX
 */
enum ICC_RECV_FUNC_ID{
	IFC_RECV_FUNC_RTC_SETTIME = 0,
	IFC_RECV_FUNC_BBE,
	IFC_RECV_FUNC_ONOFF,
	IFC_RECV_FUNC_ANTEN,
	IFC_RECV_FUNC_EFUSE,
	IFC_RECV_FUNC_GPIO,
	IFC_RECV_FUNC_SIM0,
	IFC_RECV_FUNC_SIM1,
	IFC_RECV_FUNC_CSHELL,
	IFC_RECV_FUNC_UART,
    IFC_RECV_FUNC_LED,
    IFC_RECV_FUNC_RESET,
    FC_RECV_FUNC_GPSCLK,
	IFC_RECV_FUNC_PASTAR,
    IFC_RECV_FUNC_PA_RF,
#if ( FEATURE_ON == MBB_COMMON )
    IFC_RECV_FUNC_USIM_STATUS_GET,/*MMI������USIM��״̬��Ϣ��ȡ*/
    IFC_RECV_FUNC_MLOG,/*������C����Ҫ�ռ���log���䵽A�˵�mlogģ����*/
#endif
#ifdef BSP_CONFIG_BOARD_K5160
    /* win8 ������ STK �� MBIM ֮���ͨ��ID */
    IFC_RECV_FUNC_MBIM_TO_STK,
    IFC_RECV_FUNC_STK_TO_MBIM,
#endif /* BSP_CONFIG_BOARD_K5160 */

#if (FEATURE_ON == MBB_SIMLOCK_FOUR)
    IFC_VERIFY_FUNC_HWLOCK,
    IFC_VERIFY_HWLOCK_RSP,
#endif /*MBB_SIMLOCK_FOUR*/
	/* ��Ҫ��ICC_CHN_IFC����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	IFC_RECV_FUNC_ID_MAX,

	RFILE_RECV_FUNC_ID = 0,
	/* ��Ҫ��ICC_CHN_RFILE����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	RFILE_RECV_FUNC_ID_MAX,

    NV_RECV_FUNC_AC = 0,
	/* ��Ҫ��ICC_CHN_NV����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	NV_RECV_FUNC_ID_MAX,

	GUOM0_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM0����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM0_RECV_FUNC_ID_MAX,

	GUOM1_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM1����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM1_RECV_FUNC_ID_MAX,

	GUOM2_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM1����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM2_RECV_FUNC_ID_MAX,

	GUOM3_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM2����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM3_RECV_FUNC_ID_MAX,

	GUOM4_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM4����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM4_RECV_FUNC_ID_MAX,

	GUOM5_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM5����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM5_RECV_FUNC_ID_MAX,

	CSHELL_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_CSHELL����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	CSHELL_RECV_FUNC_ID_MAX,

	MCORE_CCORE_FUNC_TEST1 = 0,
	MCORE_CCORE_FUNC_TEST2,
	MCORE_CCORE_FUNC_HKADC,
	MCU_CCORE_CPUFREQ,
	MCU_CCORE_WSRC,
	MCORE_CCORE_FUNC_WAKEUP,
	MCORE_CCORE_FUNC_REGULATOR,
	MCORE_CCORE_FUNC_SIM0,
	MCORE_CCORE_FUNC_SIM1,
	MCORE_CCORE_FUNC_SOCP,
	MCORE_CCORE_FUNC_UART,
	/* ��Ҫ��ICC_CHN_MCORE_CCORE����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	MCORE_CCORE_FUNC_ID_MAX,

#if (MBB_SOFT_POWER_OFF == FEATURE_ON)
    MCORE_ACORE_FUNC_POWEROFF_NOTIFY = 0,
#else
	MCORE_ACORE_FUNC_TEST1 = 0,
#endif /* MBB_SOFT_POWER_OFF == FEATURE_ON */
	MCORE_ACORE_FUNC_TEST2,
	MCORE_ACORE_FUNC_HKADC,
	MCU_ACORE_CPUFREQ,
	MCU_ACORE_WSRC,
	NV_RECV_FUNC_AM,
	MCORE_ACORE_FUNC_TEMPERATURE,
	MCU_ACORE_RFILE,    /* for rfile */
	MCORE_ACORE_FUNC_WAKEUP,
	MCORE_ACORE_FUNC_DUMP,
	MCORE_ACORE_FUNC_RESET,
	/* ��Ҫ��ICC_CHN_MCORE_ACORE����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	MCORE_ACORE_FUNC_ID_MAX
};
/* ö�ٶ���end */

struct icc_channel_packet
{
	u32 channel_id;               /* �����ݰ���¼��ͨ��id */
	u32 len;                      /* �����ݰ����� */
	u32 src_cpu_id;               /* �����ݰ��ķ����ߵ�cpu id */
	u32 seq_num;                  /* �����ݰ������к�: ͬ�����͵ĵȴ�������Ҫ�õ� */
	u32 need_responsed:1;         /* �����ݰ��Ƿ���Ҫ�ظ����Է��˱�ʶbitλ */
	u32 is_responsed:1;           /* �����ݰ��Ƿ��ǶԷ��˻ظ������ı�ʶbitλ */
	u32 reserved:30;              /* ����bitλ */
	s32 data;                     /* ���ݰ�ͷ��context */
	u32 timestamp;                /* �����ݰ���ʱ��� */
	u32 task_id;                  /* �����ݰ��ķ����ߵ�����id */
};

#define ICC_CHANNEL_PAYLOAD                        (sizeof(struct icc_channel_packet) + 1)
#define ICC_CHANNEL_ID_MAKEUP(channel_id, func_id) ((channel_id << 16) | (func_id))

typedef s32 (*read_cb_func)(u32 channel_id , u32 len, void* context);
typedef s32 (*write_cb_func)(u32 channel_id , void* context);
/* ����ӿ�����start */
/*****************************************************************************
* �� �� ��  : bsp_icc_send
* ��������  : icc�첽�������ݽӿ�
* �������  : u32 cpuid       ����Ҫ���͵�cpu�ı�ţ�ʹ��Լ��: Ҫʹ��enum CPU_ID�����Ա��ö��ֵ
*             u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                               1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID��ö��ֵ
                               2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧͨ��id��ö��ֵ
*             u8 *buffer      Ҫ���͵�����buffer��ָ��
*             u32 data_len    Ҫ���͵����ݵĴ�С, ʹ��Լ��: ���ֵ < fifo_size - ICC_CHANNEL_PACKET_LEN
* �������  : ��
* �� �� ֵ  : ��ȷ:  ʵ��д��fifo�Ĵ�С;  ����: ��ֵ
* ˵    ��  : 1) ����ͨ��������ʹ�õ�ע���ڶԷ��˵Ļص����������Ҫʹ��bsp_icc_read()���������ݶ���
*            2) ר��ͨ����֧���ڸ�ͨ��ʹ��ģ���������������ʹ��bsp_icc_read()���������ݶ��ߣ������Ͷ˱����з�ѹ��ͨ�����ݷ��ͻ�����������ơ�

*****************************************************************************/
s32 bsp_icc_send(u32 cpuid,u32 channel_id,u8 *buffer,u32 data_len);

/*****************************************************************************
* �� �� ��  : bsp_icc_send_sync
* ��������  : iccͬ���������ݽӿ�
* �������  : u32 cpuid       ����Ҫ���͵�cpu�ı�ţ�ʹ��Լ��: Ҫʹ��enum CPU_ID�����Ա��ö��ֵ
*             u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                               1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID��ö��ֵ
                               2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧ��ͨ��id��ö��ֵ
*             u8 *buffer      Ҫ���͵�����buffer��ָ��
*             u32 data_len    Ҫ���͵����ݵĴ�С, ʹ��Լ��: ���ֵ < fifo_size - ICC_CHANNEL_PACKET_LEN
*             s32 timeout     �Ȼظ���ʱ�䣬ʹ��Լ��: Ҫ���޵���Ҫʹ�ú� MAX_SCHEDULE_TIMEOUT
* �������  : ��
* �� �� ֵ  : ��ȷ: ���պ˻ص������ķ���ֵ;  ����: ��ֵ
* ˵    ��  : 1) ����ʹ�õ�ע���ڶԷ��˵Ļص����������Ҫʹ��bsp_icc_read()���������ݶ���
*             2) ���øýӿڻᵼ�µ���������˯��ֱ����ʱʱ�䵽�����߶Է��˷��غ������ý��
*             3) �ýӿ������ں˼亯������(IFC)�����Σ��˼亯������ֻ�ܷ���ϵͳ�Դ��ļ��������ͣ����ܷ��ؽṹ����û��Զ�������
*             4) �ýӿڲ�����icc�ص���ʹ�ã�������������icc�����ӳٵ����غ��

*****************************************************************************/
s32 bsp_icc_send_sync(u32 cpuid,u32 channel_id,u8 * data,u32 data_len,s32 timeout);

/*****************************************************************************
* �� �� ��  : bsp_icc_read
* ��������  : icc��fifo��ȡ���ݽӿ�
* �������  : u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID
                2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧͨ��id��ö��ֵ
*             u8 *buf        Ҫ��ȡfifo������buffer��ָ��
*             u32 buf_len    ����buffer�Ĵ�С
* �������  : ��
* �� �� ֵ  : ��ȷ:  ʵ�ʴ�ͨ����ȡ���ݴ�С;  ����: ��ֵ
* ˵    ��  : 1) ���ڻص�������ʹ�ã���ʹ�����Լ�������������ʹ�ã������Ͷ˱����з�ѹ��ͨ�����ݷ��ͻ�����������ƣ��Ա��ֺ˼�ͨ����������ͨ
*****************************************************************************/
s32 bsp_icc_read(u32 channel_id,u8 * buf,u32 buf_len);

/*****************************************************************************
* �� �� ��  : bsp_icc_event_register
* ��������  : ʹ��iccͨ��ע��ص������ӿ�
* �������  : u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID
                2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧͨ��id��ö��ֵ
*             read_cb_func read_cb      ���ص�
*             void *read_context        ���������������������Ϣ������չ��
*             write_cb_func write_cb    ���ص�
*             void *write_context       ���������������������Ϣ������չ��
* �������  : ��
* �� �� ֵ  : ��ȷ:  0;  ����: ������
* ˵    ��  : �ص������в������κλ���������������˯�ߵĺ������ã��磺
*             1) taskDelay()
*             2) �ź�����ȡ
*             3) printf()
*             4) malloc()
*             5) bsp_icc_send_sync()
*****************************************************************************/
s32 bsp_icc_event_register(u32 channel_id, read_cb_func read_cb, void *read_context,
                                              write_cb_func write_cb, void *write_context);

/*****************************************************************************
* �� �� ��  : bsp_icc_event_unregister
* ��������  : ʹ��iccͨ��ȥע��ص������ӿ�
* �������  : u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID
                2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧͨ��id��ö��ֵ
* �������  : ��
* �� �� ֵ  : ��ȷ:  0;  ����: ��ֵ
*****************************************************************************/
s32 bsp_icc_event_unregister(u32 channel_id);

/*****************************************************************************
* �� �� ��  : bsp_icc_debug_register
* ��������  : ʹ��iccͨ��ע��ص������ӿ�
* �������  : u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID
                2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧͨ��id��ö��ֵ
*             FUNCPTR_1 debug_routine     ��һ�������ĵ͹��Ļ��ѻص�
*             int param       �����ص������Ĳ���
* �������  : ��
* �� �� ֵ  : ��ȷ:  0;  ����: ������
* ˵    ��  : �ص������в������κλ���������������˯�ߵĺ������ã��磺
*             1) taskDelay()
*             2) �ź�����ȡ
*             3) printf()
*             4) malloc()
*             5) bsp_icc_send_sync()
*****************************************************************************/
s32 bsp_icc_debug_register(u32 channel_id, FUNCPTR_1 debug_routine, int param);

s32 bsp_icc_init(void);
void bsp_icc_release(void);
s32 bsp_icc_suspend(void);
void icc_dump_hook(void);

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __BSP_ICC_H__ */
