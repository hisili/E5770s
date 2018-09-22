


#include <osl_thread.h>
#include <osl_module.h>

#include <bsp_dump.h>


#include <bsp_reset.h>
#include "icc_balong.h"
/* ȫ�ֱ�������start */
struct icc_control g_icc_ctrl = {0};


/* real_channel_id, send_addr, fifo_size, recv_addr, func_size, ipc_irq_id ˵��: ͨ����ű�����ͨ�������ȼ� */
struct icc_init_info g_icc_init_info[] = {
  {ICC_CHN_IFC,         SHARED_MODE, ICC_IFC_SIZE,    0,                0,                IPC_ACPU_INT_SRC_ICC, IPC_CCPU_INT_SRC_ICC, IFC_RECV_FUNC_ID_MAX,   "IFC"   },
  {ICC_CHN_RFILE,       SHARED_MODE, ICC_RFILE_SIZE,  0,                0,                IPC_ACPU_INT_SRC_ICC, IPC_CCPU_INT_SRC_ICC, RFILE_RECV_FUNC_ID_MAX, "RFILE" },
  {ICC_CHN_NV,          SHARED_MODE, ICC_NV_SIZE,     0,                0,                IPC_ACPU_INT_SRC_ICC, IPC_CCPU_INT_SRC_ICC, NV_RECV_FUNC_ID_MAX,    "NV"    },
  {ICC_CHN_GUOM0,       SHARED_MODE, ICC_GUOM0_SIZE,  0,                0,                IPC_ACPU_INT_SRC_ICC, IPC_CCPU_INT_SRC_ICC, GUOM0_RECV_FUNC_ID_MAX, "GUOM0" },
  {ICC_CHN_GUOM1,       SHARED_MODE, ICC_GUOM1_SIZE,  0,                0,                IPC_ACPU_INT_SRC_ICC, IPC_CCPU_INT_SRC_ICC, GUOM1_RECV_FUNC_ID_MAX, "GUOM1" },
  {ICC_CHN_GUOM2,       SHARED_MODE, ICC_GUOM2_SIZE,  0,                0,                IPC_ACPU_INT_SRC_ICC, IPC_CCPU_INT_SRC_ICC, GUOM2_RECV_FUNC_ID_MAX, "GUOM2" },
  {ICC_CHN_GUOM3,       SHARED_MODE, ICC_GUOM3_SIZE,  0,                0,                IPC_ACPU_INT_SRC_ICC, IPC_CCPU_INT_SRC_ICC, GUOM3_RECV_FUNC_ID_MAX, "GUOM3" },
  {ICC_CHN_GUOM4,       SHARED_MODE, ICC_GUOM4_SIZE,  0,                0,                IPC_ACPU_INT_SRC_ICC, IPC_CCPU_INT_SRC_ICC, GUOM4_RECV_FUNC_ID_MAX, "GUOM4" },
  {ICC_CHN_GUOM5,       SHARED_MODE, ICC_GUOM5_SIZE,  0,                0,                IPC_ACPU_INT_SRC_ICC, IPC_CCPU_INT_SRC_ICC, GUOM5_RECV_FUNC_ID_MAX, "GUOM5" },
  {ICC_CHN_CSHELL,      SHARED_MODE, ICC_CSHELL_SIZE, 0,                0,                IPC_ACPU_INT_SRC_ICC, IPC_CCPU_INT_SRC_ICC, CSHELL_RECV_FUNC_ID_MAX,"CSHELL"},
  {ICC_CHN_MCORE_ACORE, SHARED_MODE, ICC_MACORE_SIZE, 0,                0,                IPC_ACPU_INT_SRC_ICC, IPC_MCU_INT_SRC_ICC,  MCORE_ACORE_FUNC_ID_MAX,"A-M"   }
};
/* ȫ�ֱ�������end */

#define icc_reset_debug(fmt, ...) ()

static u32 fifo_skip(struct icc_channel_fifo* fifo,  u32 len);
static s32  icc_task_shared_func(void *obj);

/*lint --e{713}*/
u32 fifo_put_with_header(struct icc_channel_fifo *fifo, u8 *head_buf, u32 head_len, u8 *data_buf, u32 data_len)
{
	s32 tail_idle_size = 0;
	u32 write           = fifo->write;
	u32 read            = fifo->read;
	u32 base_addr       = (u32)fifo + sizeof(struct icc_channel_fifo);
	u32 buf_len         = fifo->size;

	/*���л�������С*/
	if (read > write)
	{
		tail_idle_size = (s32)(read - write);
	}
	else
	{
		tail_idle_size = (s32)(buf_len - write);
	}

	/*�����ͷ��*/
	if (tail_idle_size < (s32)head_len)
	{
		memcpy((void *)(write + base_addr), (void *)head_buf, (u32)tail_idle_size);
		memcpy((void *)base_addr, (void *)(head_buf + tail_idle_size), (head_len - (u32)tail_idle_size));
		write          = head_len - (u32)tail_idle_size;
		tail_idle_size = 0;
	}
	else
	{
		memcpy((void *)(write + base_addr), (void *)head_buf, head_len);
		tail_idle_size = tail_idle_size - (s32)head_len;
		write          = (tail_idle_size == 0) ? 0 : (write + head_len);
	}

	/*����为��*/
	if ( (0 == tail_idle_size) || (tail_idle_size > (s32)data_len) )
	{
		memcpy((void *)(write + base_addr), (void *)data_buf, data_len);
		write += data_len;
	}
	else
	{
		memcpy((void *)(write + base_addr), (void *)data_buf, (u32)tail_idle_size);
		memcpy((void *)base_addr, (void *)(data_buf + tail_idle_size), data_len - (u32)tail_idle_size);
		write = data_len - (u32)tail_idle_size;
	}

	/*ȷ�����д�겻ͣ�ڻ���������λ��*/
	write = (write == buf_len) ? 0 : write;

	/*����дָ��*/
	fifo->write = write;
	cache_sync();

	return data_len + head_len;
}

u32 fifo_get(struct icc_channel_fifo *fifo, u8 *data_buf, u32 data_len, u32 *read)
{
	s32 total_idle_size = 0;
	s32 tail_idle_size  = 0;/*lint !e14 */
	u32 write           = fifo->write;
	u32 base_addr       = (u32)fifo + sizeof(struct icc_channel_fifo);
	u32 buf_len         = fifo->size;
	u32 readed_len      = 0;

	/*���л�������С*/
	if (*read > write)
	{
		total_idle_size = (s32)(buf_len + write - *read);
		tail_idle_size  = (s32)(buf_len - *read);
	}
	else
	{
		total_idle_size = (s32)(write - *read);
		tail_idle_size  = total_idle_size;
	}

	readed_len = (u32)(ICC_MIN((s32)data_len, total_idle_size));
	if(readed_len > data_len)
	{
		(*(unsigned *) (ICC_DBG_MSG_ADDR_IN_DDR + 0x0)) = (base_addr);
		(*(unsigned *) (ICC_DBG_MSG_ADDR_IN_DDR + 0x4)) = (write);
		(*(unsigned *) (ICC_DBG_MSG_ADDR_IN_DDR + 0x8)) = (*read);
		(*(unsigned *) (ICC_DBG_MSG_ADDR_IN_DDR + 0xc)) = (buf_len);
		system_error((u32)DRV_ERRNO_ICC_RING_BUFFER, 0, 0, (char *)ICC_DBG_MSG_ADDR_IN_DDR, (u32)ICC_DBG_MSG_LEN_IN_DDR);
	}

	if ((s32)readed_len <= tail_idle_size)
	{
		memcpy((void *)data_buf, (void *)(*read + base_addr), readed_len);
		*read += readed_len;
	}
	else
	{
		memcpy((void *)data_buf, (void *)(*read + base_addr), (u32)tail_idle_size);
		memcpy((void *)(data_buf + tail_idle_size), (void *)base_addr, readed_len - (u32)tail_idle_size);
		*read = readed_len - (unsigned int)tail_idle_size;
	}

	/*ȷ�������겻ͣ�ڻ���������λ��*/
	*read = (*read >= buf_len) ? (*read - buf_len) : (*read);

	return readed_len;

}

u32 fifo_get_with_header(struct icc_channel_fifo *fifo, u8 *data_buf, u32 data_buf_len)
{
	u32 read_len = 0;
	u32 read     = fifo->read;
	struct icc_channel_packet packet = {0};

	fifo_get(fifo, (u8 *)&packet, sizeof(packet), &read);
	data_buf_len = ICC_MIN(data_buf_len, packet.len);
	read_len = fifo_get(fifo, data_buf, data_buf_len, &read);

	/*���¶�ָ��*/
	fifo->read = read;

	return read_len;
}

static u32 fifo_write_space_get(struct icc_channel_fifo* fifo)
{
    u32 write   = fifo->write;
    u32 read    = fifo->read;
    u32 buf_len = fifo->size;

    /*���л�������С*/
    if (read > write)
    {
        return (read - write);
    }
    else
    {
        return (buf_len - write + read);
    }
}

static u32 fifo_read_space_get(struct icc_channel_fifo* fifo)
{
    u32 write   = fifo->write;
    u32 read    = fifo->read;
    u32 buf_len = fifo->size;

	/*���л�������С*/
    if (read > write)
    {
		return (buf_len + write - read);
    }
    else
    {
		return (write - read);
    }
}

static u32 fifo_skip(struct icc_channel_fifo* fifo,  u32 len)
{
	u32 space    = fifo_read_space_get(fifo);
	u32 data_len = ICC_MIN(len, space);
	u32 read     = fifo->read;
	read        += data_len;
	read         = (read >= fifo->size) ? (read - fifo->size) : (read);
	fifo->read   =read;

	return data_len;
}

static u32 fifo_read_ptr(struct icc_channel_fifo* fifo)
{
	return fifo->read;
}

s32 data_send(u32 cpuid, u32 channel_id, u8* data, u32 data_len, struct icc_channel_packet* packet)
{
	s32 ret = ICC_OK;
	unsigned long flags = 0;
	u32 len = 0;
	struct icc_channel *channel = g_icc_ctrl.channels[GET_CHN_ID(channel_id)];

	struct icc_uni_msg_info msg = {0};

	UNUSED(flags);

	spin_lock_irqsave(&channel->write_lock, flags); /*lint !e123 */

	msg.channel_id = channel_id;
	msg.pos = channel->fifo_send->write;
	msg.recv_task_id = 0; /* �ӷ�����Ϣά��ͳ�Ƶ���Ϣ�����Ľ������� */
	msg.send_task_id = icc_taskid_get();
	msg.duration_prev = bsp_get_slice_value();
	packet->task_id = msg.send_task_id;
	packet->timestamp = msg.duration_prev;

	if((data_len + sizeof(struct icc_channel_packet)) > fifo_write_space_get(channel->fifo_send))/*lint !e574 */
	{
		ret = ICC_INVALID_NO_FIFO_SPACE;
		goto err_fifo_full;
	}

	len = fifo_put_with_header(channel->fifo_send, (u8*)packet, sizeof(struct icc_channel_packet), data, data_len);
	len -=  sizeof(struct icc_channel_packet);
	if(data_len != len)
	{
		ret = ICC_RECV_ERR;
		goto err_read;
	}

	msg.len = len;
	msg.duration_post = bsp_get_slice_value();
	icc_msg_queue_in(&(g_icc_dbg.msg_stat.send), &msg);
	icc_channel_msg_stat(&(g_icc_dbg.channel_stat[channel->id]->send.total), msg.len, msg.send_task_id);
	icc_channel_msg_stat(&(g_icc_dbg.channel_stat[channel->id]->send.sub_chn[GET_FUNC_ID(channel_id)]), msg.len, msg.send_task_id);
	icc_dbg_info_print("fifo_send", channel_id, data, data_len);

	bsp_ipc_int_send((IPC_INT_CORE_E)cpuid, (IPC_INT_LEV_E)channel->ipc_send_irq_id);

	spin_unlock_irqrestore(&channel->write_lock, flags); /*lint !e123 */

	return (s32)len;
err_read:
	/* �Ѿ�����������ϢҲҪ��¼ */
	msg.len = len;
	msg.duration_post = bsp_get_slice_value();
	icc_msg_queue_in(&(g_icc_dbg.msg_stat.send), &msg);
	icc_channel_msg_stat(&(g_icc_dbg.channel_stat[channel->id]->send.total), len, msg.send_task_id);
	icc_channel_msg_stat(&(g_icc_dbg.channel_stat[channel->id]->send.sub_chn[GET_FUNC_ID(channel_id)]), len, msg.send_task_id);
	icc_dbg_info_print("fifo_send", channel_id, data, data_len);
	icc_print_error("errorno: 0x%x(recv len 0x%x!= expected0x%x), channel_id: 0x%x\n", ret, channel_id, len, data_len);
	return ret;
err_fifo_full:
	spin_unlock_irqrestore(&channel->write_lock, flags); /*lint !e123 */
	icc_print_error("errorno: 0x%x(fifo is full), channel_id: 0x%x\n\
		please inspect whether cpu[%d] is working, or read callback is invoked correct\n", ret, channel_id, cpuid);

	return ret;
}

static s32 icc_send_ex(u32 cpuid, u32 channel_id, u8* data, u32 data_len, u32 is_responsed, u32 packet_sn, u32 para)
{
	struct icc_channel_packet packet;

	packet.channel_id = channel_id;
	packet.src_cpu_id = ICC_SRC_CPU;
	packet.seq_num = packet_sn;
	packet.is_responsed= is_responsed;
	packet.need_responsed = ICC_PACKET_NONEED_RESPONSE;
	packet.len = data_len;
	packet.data = (s32)para;

	return data_send(cpuid, channel_id, data,data_len, &packet);
}

void handle_channel_recv_data(struct icc_channel *channel)
{
	struct icc_channel_packet packet = {0};
	struct icc_channel_vector *rector = NULL;
	u32 read_ptr = 0;
	u32 read_len = 0;
	u32 read     = channel->fifo_recv->read;
	unsigned long flags = 0;
	UNUSED(flags);

	spin_lock_irqsave(&(channel->read_lock), flags); /*lint !e123 */
	read_len = fifo_get(channel->fifo_recv, (u8*)&packet, sizeof(packet), &read);
	if(read_len != sizeof(packet))
	{
		goto invalid_packet;
	}

	read_ptr = read;
	icc_channel_packet_dump(&packet);
	g_icc_dbg.recv_task_id = packet.task_id;
	g_icc_dbg.timestamp = packet.timestamp;
	g_icc_dbg.send_cpu_id = packet.src_cpu_id; /* for icc test */

	if(GET_FUNC_ID(packet.channel_id) >= channel->func_size)
	{
		icc_print_error("func_id is out of range!\n");
		goto invalid_packet;
	}

	rector = &channel->rector[GET_FUNC_ID(packet.channel_id)];

	if(!packet.len) /* packet.len = 0������packet */
	{
		channel->fifo_recv->read = read;
	}

	spin_unlock_irqrestore(&(channel->read_lock), flags); /*lint !e123 */

	if(packet.is_responsed) /* �Է��ظ����Լ��İ� */
	{
		rector->return_data = packet.data;
		channel->seq_num_recv = packet.seq_num;
		wake_up(&channel->sen_sync_wq); /*lint !e529 */
	}
	else /* �Է��������İ� */
	{
		if (rector->read_cb)
		{
			icc_print_debug("invoke callback func[0x%x]\n", rector->read_cb);
			rector->return_data = rector->read_cb(packet.channel_id, packet.len, rector->read_context);
			if(packet.need_responsed) /* ��Ҫ�ظ� */
			{
				icc_send_ex(packet.src_cpu_id, packet.channel_id, NULL, 0, 1, packet.seq_num,(u32)rector->return_data);
			}
		}
	}

	return;

invalid_packet:
	/* ��Ч����հ������� */
	if( (read_ptr == fifo_read_ptr(channel->fifo_recv)) && (packet.len > 0) )
	{
		icc_print_error("fifo read skip!\n");
		fifo_skip(channel->fifo_recv, packet.len);
	}
	spin_unlock_irqrestore(&(channel->read_lock), flags); /*lint !e123 */

}


s32 icc_task_shared_func(void *obj)
{
	struct icc_channel *channel = NULL;
	u32 i = 0;
	u32 read = 0;

	/* coverity[INFINITE_LOOP] */
	/* coverity[no_escape] */
	for( ; ;)
	{
		for(i = 0; i < ICC_CHN_ID_MAX; i++)
		{
			channel = g_icc_ctrl.channels[i];
			if(!channel)
			{
				continue;
			}
			if (channel->mode.union_stru.task_shared)
			{
				if(ICC_CHN_MAGIC_SIGN == channel->fifo_recv->magic)
				{
					channel->fifo_recv->magic = ICC_CHN_MAGIC_UNSIGN;
					channel->ready_recv = 1;
				}
				if (channel->ready_recv)
				{
					/* ��fifo����Ϣȫ������ */
					while(fifo_read_space_get(channel->fifo_recv) >= sizeof(struct icc_channel_packet))
					{
						read = channel->fifo_recv->read;
						handle_channel_recv_data(channel);
						if(channel->fifo_recv->read == read)
						{
							break;
						}
					}

					/*д�ص�Ĭ��ʹ����ͨ��0 */
					if(fifo_write_space_get(channel->fifo_send) == channel->fifo_send->size && channel->rector->write_cb)
					{
						(void)channel->rector->write_cb(channel->id, NULL);
					}
				}
			}
		}

		osl_sem_down(&g_icc_ctrl.shared_task_sem);
	}
	return 0; /*lint !e527 */
}

void icc_ipc_isr(u32 data)
{
	u32 channel_id = data;

	g_icc_dbg.ipc_int_cnt++;
	icc_print_debug("ipc_int_cnt:%d\n", g_icc_dbg.ipc_int_cnt);

	if(channel_id == ICC_SHARED_IPC_CHN_IDX)
	{
		osl_sem_up(&g_icc_ctrl.shared_task_sem);
	}
	else
	{
		if(channel_id < ICC_CHN_ID_MAX)
		{
			osl_sem_up(&(g_icc_ctrl.channels[channel_id]->private_task_sem)); /*lint !e661 */
		}
		else
		{
			icc_print_error("invalid paramete, channel id = 0x%x\n",channel_id);
		}
	}
}

void icc_channel_fifo_init(void)
{
	g_icc_init_info[0].send_addr  = ADDR_IFC_RECV   ;
	g_icc_init_info[1].send_addr  = ADDR_RFILE_RECV ;
	g_icc_init_info[2].send_addr  = ADDR_NV_RECV    ;
	g_icc_init_info[3].send_addr  = ADDR_GUOM0_RECV ;
	g_icc_init_info[4].send_addr  = ADDR_GUOM1_RECV ;
	g_icc_init_info[5].send_addr  = ADDR_GUOM2_RECV ;
	g_icc_init_info[6].send_addr  = ADDR_GUOM3_RECV ;
	g_icc_init_info[7].send_addr  = ADDR_GUOM4_RECV ;
	g_icc_init_info[8].send_addr  = ADDR_GUOM5_RECV ;
	g_icc_init_info[9].send_addr  = ADDR_CSHELL_RECV;
	g_icc_init_info[10].send_addr = ADDR_MACORE_RECV;
	g_icc_init_info[0].recv_addr  = ADDR_IFC_SEND   ;
	g_icc_init_info[1].recv_addr  = ADDR_RFILE_SEND ;
	g_icc_init_info[2].recv_addr  = ADDR_NV_SEND    ;
	g_icc_init_info[3].recv_addr  = ADDR_GUOM0_SEND ;
	g_icc_init_info[4].recv_addr  = ADDR_GUOM1_SEND ;
	g_icc_init_info[5].recv_addr  = ADDR_GUOM2_SEND ;
	g_icc_init_info[6].recv_addr  = ADDR_GUOM3_SEND ;
	g_icc_init_info[7].recv_addr  = ADDR_GUOM4_SEND ;
	g_icc_init_info[8].recv_addr  = ADDR_GUOM5_SEND ;
	g_icc_init_info[9].recv_addr  = ADDR_CSHELL_SEND;
	g_icc_init_info[10].recv_addr = ADDR_MACORE_SEND;
}

void icc_restore_recv_channel_flag(struct icc_channel_fifo * channel_fifo)
{
	/* nothing to do */
	return;
}

/*lint --e{578} */
struct icc_channel *icc_channel_init(struct icc_init_info *info, s32 *ret)
{
	struct icc_channel *channel = NULL;
	*ret = ICC_OK;

	channel = (struct icc_channel*)osl_malloc(sizeof(struct icc_channel));
	if (!channel)
	{
		*ret = ICC_MALLOC_CHANNEL_FAIL;
		goto error_channel;
	}
	memset(channel, 0, sizeof(struct icc_channel));

	channel->id       = info->real_channel_id; /* ֱ��ʹ��real channel id */
	channel->name     = info->name;
	channel->mode.val = info->mode;

	/* ����fifo�����ʼ��������fifo�Բ��ʼ�� */
	channel->fifo_send = (struct icc_channel_fifo*)(info->send_addr);
	channel->fifo_recv = (struct icc_channel_fifo*)(info->recv_addr);
	icc_restore_recv_channel_flag(channel->fifo_recv);

	memset(channel->fifo_send, 0, sizeof(struct icc_channel_fifo));
	channel->fifo_send->size  = info->fifo_size;
	channel->fifo_send->magic = ICC_CHN_MAGIC_SIGN; /* ֪ͨ�Է����˵ĸ�fifo�Ƿ��ʼ����� */

	/* ����������ʼ�� */
	channel->func_size = info->func_size;
	channel->rector = (struct icc_channel_vector*)osl_malloc(sizeof(struct icc_channel_vector) * channel->func_size);
	if (!channel->rector)
	{
		*ret = ICC_MALLOC_VECTOR_FAIL;
		goto error_vector;
	}
	memset(channel->rector, 0, sizeof(struct icc_channel_vector) * channel->func_size); /*lint !e665 */

	/* ͬ�����������Դ��ʼ�� */
	init_waitqueue_head(&(channel->sen_sync_wq));

	channel->seq_num_send = 0;
	channel->seq_num_recv = 0xffffffff;

	osl_sem_init(ICC_SEM_FULL, &(channel->seq_num_send_sem));

	spin_lock_init(&channel->write_lock); /*lint !e123 */
	spin_lock_init(&channel->read_lock);  /*lint !e123 */


	/* ���������ʱ��ҲҪʹ��channel->ipc_send_irq_id */
	channel->ipc_send_irq_id = info->ipc_send_irq_id;
	channel->ipc_recv_irq_id = info->ipc_recv_irq_id;

	channel->state           = ICC_CHN_OPENED;
	channel->ready_recv      = 0;
	return channel;

error_vector:
	icc_safe_free(channel);
error_channel:
	icc_print_error("channel init error, errorno=0x%x, channel_id=0x%x\n",ret, info->real_channel_id);
	return NULL;
}

void icc_wakeup_flag_set(void)
{
	g_icc_ctrl.wake_up_flag = 1;
}

s32 icc_channel_has_data(void)
{
	/*lint --e{53, 58, 56 } */
	s32 i = 0;
	u32 read  = 0;
	u32 write = 0;

	for(i = 0; i < (int)ICC_CHN_ID_MAX; i++)
	{
		
		if(NULL == g_icc_ctrl.channels[i])
		{
			continue;
		}
		read  = g_icc_ctrl.channels[i]->fifo_recv->read;
		write = g_icc_ctrl.channels[i]->fifo_recv->write;
		if(read != write) /* has data to be handled */
		{
			icc_print_error("%s[channel-%d] stop S/R flow, and try to read data from channel\n", g_icc_ctrl.channels[i]->name, i);
			osl_sem_up(&g_icc_ctrl.shared_task_sem);
			return ICC_BUSY;
		}
	}

	return ICC_OK;
}

int icc_pm_notify(struct notifier_block *nb, unsigned long event, void *dummy)
{
	if (event == PM_SUSPEND_PREPARE)
	{
		return icc_channel_has_data();
	}

	return ICC_OK;
}

s32 bsp_icc_init(void)
{
	/*lint --e{14, 578, 546 } */
	s32 ret = ICC_OK;
	struct icc_channel *channel = NULL;
	u32 i = 0;

	memset(&g_icc_ctrl, 0, sizeof(struct icc_control));
	g_icc_ctrl.cpu_id = ICC_SRC_CPU;

	/* ����ͨ��ָ���ÿգ�ָ������ȫ�� */
	memset(g_icc_ctrl.channels, 0, (u32)ICC_CHN_ID_MAX * sizeof(struct icc_channel *)); /*lint !e665 */
	g_icc_ctrl.channel_size = ICC_CHN_ID_MAX;

	icc_channel_fifo_init();


	for(i = 0; i < sizeof(g_icc_init_info) / sizeof(g_icc_init_info[0]); i++)
	{
		channel = icc_channel_init(&g_icc_init_info[i], &ret);
		if(NULL == channel)
		{
			ret = ICC_CHN_INIT_FAIL;
			goto error_channel;
		}

		g_icc_ctrl.channels[g_icc_init_info[i].real_channel_id] = channel;
	}

	/* ��ά�ɲ��ʼ�� */
	ret = icc_debug_init(sizeof(g_icc_init_info) / sizeof(g_icc_init_info[0]));
	if(ICC_OK != ret)
	{
		goto error_debug_init;
	}

	/* lowpower handle using pm notify */
	memset(&g_icc_ctrl.pm_notify, 0, sizeof(g_icc_ctrl.pm_notify));
	g_icc_ctrl.pm_notify.notifier_call = icc_pm_notify;
	register_pm_notifier(&g_icc_ctrl.pm_notify);

	osl_sem_init(ICC_SEM_FULL, &g_icc_ctrl.shared_task_sem);

	if(ICC_ERR == osl_task_init("icc_shared", ICC_TASK_SHARED_PRI, ICC_TASK_STK_SIZE ,(void *)icc_task_shared_func, NULL,
		&g_icc_ctrl.shared_task_id))
	{
		ret = ICC_CREATE_TASK_FAIL;
		goto error_task;
	}
	g_icc_ctrl.shared_recv_ipc_irq_id = ICC_RECV_IPC_SHARED;

	if (ICC_ERR == bsp_ipc_int_connect((IPC_INT_LEV_E)g_icc_ctrl.shared_recv_ipc_irq_id, (voidfuncptr)icc_ipc_isr, ICC_SHARED_IPC_CHN_IDX))
	{
		ret = ICC_REGISTER_INT_FAIL;
		goto error_int;
	}
	if (ICC_ERR == bsp_ipc_int_enable((IPC_INT_LEV_E)g_icc_ctrl.shared_recv_ipc_irq_id))
	{
		ret = ICC_REGISTER_INT_FAIL;
		goto error_int;
	}

	icc_print_error("ok\n");

	g_icc_ctrl.state = ICC_INITIALIZED;

	return ICC_OK;

error_int:
	kthread_stop((struct task_struct *)g_icc_ctrl.shared_task_id); /*lint !e64 */
error_task:
	for(i = 0; i < sizeof(g_icc_init_info)/sizeof(g_icc_init_info[0]); i++)
	{
		bsp_icc_channel_uninit(g_icc_init_info[i].real_channel_id);
	}

error_debug_init:
	icc_print_error("*********icc init failed, errono: 0x%x********\n", ret);
error_channel:
	return ret;
}

void bsp_icc_channel_uninit(u32 real_channel_id)
{
	struct icc_channel *channel = NULL;

	channel = g_icc_ctrl.channels[real_channel_id];

	osl_sema_delete(&(channel->seq_num_send_sem));


	icc_safe_free(channel->rector);
	memset(channel->fifo_send, 0, sizeof(struct icc_channel_fifo) + channel->fifo_send->size); /*lint !e665 */
	icc_safe_free(channel);

}
s32 bsp_icc_debug_register(u32 channel_id, FUNCPTR_1 debug_routine, int param)
{
	struct icc_channel_vector *rector = NULL;

	if((GET_CHN_ID(channel_id)  >= ICC_CHN_ID_MAX) ||
	   (GET_FUNC_ID(channel_id) >= g_icc_ctrl.channels[GET_CHN_ID(channel_id)]->func_size))
	{
		icc_print_error("invalide parameter! channel_id=0x%x\n", channel_id);
		return ICC_INVALID_PARA;
	}
	/*lint --e{409} */
	rector = &(g_icc_ctrl.channels[GET_CHN_ID(channel_id)]->rector[GET_FUNC_ID(channel_id)]);
	rector->pm_debug.debug_routine = debug_routine;
	rector->pm_debug.para = param;

	return ICC_OK;
}
void run_icc_pm_debug_callback(void)
{
	u32 i = 0, j = 0;
	struct icc_channel *channel  = NULL;
	struct icc_channel_vector *rector = NULL;
	for(i = 0; i < ICC_CHN_ID_MAX; i++)
	{
		channel = g_icc_ctrl.channels[i];
		if (!channel)
		{
			continue;
		}
		for (j = 0; j < channel->func_size; j++)
		{
			rector =  &(channel->rector[j]);
			if(rector && rector->pm_debug.debug_routine)
			{
				rector->pm_debug.debug_routine(rector->pm_debug.para);
			}
		}
	}
}

s32 bsp_icc_event_register(u32 channel_id, read_cb_func read_cb,   void *read_context,
	                                            write_cb_func write_cb, void *write_context)
{
	struct icc_channel_vector *rector = NULL;

	if((GET_CHN_ID(channel_id)  >= ICC_CHN_ID_MAX) ||
	   (GET_FUNC_ID(channel_id) >= g_icc_ctrl.channels[GET_CHN_ID(channel_id)]->func_size))
	{
		icc_print_error("invalide parameter! channel_id=0x%x\n", channel_id);
		return ICC_INVALID_PARA;
	}
	/*lint --e{409} */
	rector = &(g_icc_ctrl.channels[GET_CHN_ID(channel_id)]->rector[GET_FUNC_ID(channel_id)]);
	if(rector->read_cb != NULL || rector->write_cb != NULL)
	{
		icc_print_error("This fuction has been registered!\n");
		return ICC_REGISTER_CB_FAIL;
	}

	rector->read_cb = read_cb;
	rector->read_context = read_context;
	rector->write_cb = write_cb;
	rector->write_context = write_context;

	osl_sem_up(&g_icc_ctrl.shared_task_sem);

	return ICC_OK;
}

s32 bsp_icc_event_unregister(u32 channel_id)
{
	struct icc_channel_vector *vector = NULL;

	if((GET_CHN_ID(channel_id) >= ICC_CHN_ID_MAX) ||
		(GET_FUNC_ID(channel_id) >= g_icc_ctrl.channels[GET_CHN_ID(channel_id)]->func_size))
	{
		icc_print_error("invalide parameter! channel_id=0x%x\n", channel_id);
		return ICC_INVALID_PARA;
	}

	vector = &(g_icc_ctrl.channels[GET_CHN_ID(channel_id)]->rector[GET_FUNC_ID(channel_id)]);
	if(!vector)
	{
		icc_print_error("vector is null pointer!\n");
		return ICC_NULL_PTR;
	}

	vector->read_cb = NULL;
	vector->read_context = NULL;
	vector->write_cb = NULL;
	vector->write_context = NULL;

	return ICC_OK;
}

s32 bsp_icc_send(u32 cpuid, u32 channel_id, u8* data, u32 data_len)
{
	if(((cpuid >= ICC_CPU_MAX) || (cpuid == ICC_SRC_CPU)) || (GET_CHN_ID(channel_id) >= ICC_CHN_ID_MAX) ||
	   (GET_FUNC_ID(channel_id) >= g_icc_ctrl.channels[GET_CHN_ID(channel_id)]->func_size) || (!data)   ||
	   (data_len + sizeof(struct icc_channel_packet) >= g_icc_ctrl.channels[GET_CHN_ID(channel_id)]->fifo_send->size) )
	{
		icc_print_error("invalid parameter! cpuid=0x%x, channel_id=0x%x, data=0x%x, data_len=0x%x\n", cpuid, channel_id, (s32)data, data_len);
		return ICC_INVALID_PARA;
	}


	return icc_send_ex(cpuid, channel_id, data,data_len, 0, 0, 0);
}

static s32 check_state(void *data)
{
	struct icc_wait_data *wait_data = (struct icc_wait_data*)data;

	icc_print_debug("check_state: %d?=%d\n", g_icc_ctrl.channels[GET_CHN_ID(wait_data->channel_id)]->seq_num_recv,
		wait_data->packet_seq_num);

	return (g_icc_ctrl.channels[GET_CHN_ID(wait_data->channel_id)]->seq_num_recv == wait_data->packet_seq_num);
}

s32 bsp_icc_send_sync(u32 cpuid, u32 channel_id, u8* data, u32 data_len, s32 timeout)
{
	/*lint --e{438} */
	s32 ret = ICC_OK;
	s32 ret_data = 0;
	struct icc_channel *channel = g_icc_ctrl.channels[GET_CHN_ID(channel_id)];
	struct icc_channel_packet packet = {0};
	struct icc_wait_data wait_data ={0};

	if(((cpuid >= ICC_CPU_MAX) || (cpuid == ICC_SRC_CPU)) || (GET_CHN_ID(channel_id) >= ICC_CHN_ID_MAX) ||
	   (GET_FUNC_ID(channel_id) >= g_icc_ctrl.channels[GET_CHN_ID(channel_id)]->func_size) || (!data))
	{
		ret = ICC_INVALID_PARA;
		goto out;
	}

	if(osl_sem_downtimeout(&(channel->seq_num_send_sem), timeout))
	{
		ret =  ICC_WAIT_SEM_TIMEOUT;
		goto out;
	}
	packet.seq_num = channel->seq_num_send++;
	osl_sem_up(&(channel->seq_num_send_sem));

	packet.channel_id = channel_id;
	packet.src_cpu_id = ICC_SRC_CPU;
	packet.need_responsed = ICC_PACKET_NEED_RESPONSE;
	packet.is_responsed = 0;
	packet.len = data_len;
	packet.data = 0;

	ret = data_send(cpuid, channel_id, data, data_len, &packet);
	if((s32)data_len != ret)
	{
		ret = ICC_SEND_ERR;
		goto out;
	}

	wait_data.packet_seq_num = packet.seq_num;
	wait_data.channel_id = channel_id;

	/* �п��ܵ���ʧ��,�޷��жϷ���ֵ,�ú����޷���Ϊ��ֵ */
	wait_event_timeout_func(channel->sen_sync_wq, timeout, check_state, (void*)(&wait_data));

	ret_data = channel->rector[GET_FUNC_ID(channel_id)].return_data;

	return ret_data;

out:
	icc_print_error("errorno=0x%x, cpuid=0x%x, channel_id=0x%x, data=0x%x, data_len=0x%x\n",
		ret, cpuid, channel_id, (u32)data, data_len);

	return ret;
}

s32 bsp_icc_read(u32 channel_id, u8 *buf, u32 buf_len)
{
	u32 read_len = 0;
	s32 ret = ICC_OK;/*lint !e14 */
	unsigned long flags = 0;
	u32 real_channel_id = GET_CHN_ID(channel_id);
	u32 func_id = GET_FUNC_ID(channel_id);

	struct icc_uni_msg_info msg = {0};

	UNUSED(flags);
	if((!buf) || (real_channel_id >= ICC_CHN_ID_MAX) ||(func_id >= g_icc_ctrl.channels[real_channel_id]->func_size))
	{
		ret = ICC_INVALID_PARA;
		goto out;
	}

	if(!(g_icc_ctrl.channels[real_channel_id]->ready_recv))
	{
		return 0;
	}

	spin_lock_irqsave(&(g_icc_ctrl.channels[real_channel_id]->read_lock), flags);

	msg.channel_id = channel_id;
	msg.pos = g_icc_ctrl.channels[real_channel_id]->fifo_recv->read;
	msg.recv_task_id = icc_taskid_get();
	msg.send_task_id = g_icc_dbg.recv_task_id; /* �Է��˵ķ���task */
	msg.duration_prev = g_icc_dbg.timestamp;

	read_len = fifo_get_with_header(g_icc_ctrl.channels[real_channel_id]->fifo_recv, buf, buf_len);

	msg.len = read_len;
	msg.duration_post = bsp_get_slice_value();
	icc_msg_queue_in(&(g_icc_dbg.msg_stat.recv), &msg);
	icc_channel_msg_stat(&(g_icc_dbg.channel_stat[real_channel_id]->recv.total), msg.len, msg.recv_task_id);
	icc_channel_msg_stat(&(g_icc_dbg.channel_stat[real_channel_id]->recv.sub_chn[func_id]), msg.len, msg.recv_task_id);
	icc_dbg_info_print("fifo_recv", channel_id, buf, buf_len);

	spin_unlock_irqrestore(&(g_icc_ctrl.channels[real_channel_id]->read_lock), flags);
	ret = (s32)read_len;

	return ret;

out:
	icc_print_error("errno=0x%x, buffer=0x%x, len%d ?= %dread_len\n", ret, buf, buf_len, read_len);

	return ret;
}

u32 bsp_icc_channel_status_get(u32 real_channel_id, u32 *channel_stat)
{
	struct icc_channel* channel = g_icc_ctrl.channels[real_channel_id];

	if(NULL == channel)
	{
		*channel_stat = ICC_CHN_CLOSED;
		return *channel_stat;
	}

	*channel_stat = channel->state;
	return *channel_stat;

}

u32 bsp_icc_channel_size_get(void)
{
	return sizeof(g_icc_init_info) / sizeof(g_icc_init_info[0]);
}

void bsp_icc_release(void)
{
	u32 i = 0;

	for(i = 0; i < sizeof(g_icc_init_info)/sizeof(g_icc_init_info[0]); i++)
	{
		bsp_icc_channel_uninit(g_icc_init_info[i].real_channel_id);
	}
	kthread_stop((struct task_struct *)g_icc_ctrl.shared_task_id); /*lint !e64 */
	unregister_pm_notifier(&g_icc_ctrl.pm_notify);
	osl_sema_delete(&g_icc_ctrl.shared_task_sem);

	bsp_ipc_int_disconnect((IPC_INT_LEV_E)g_icc_ctrl.shared_recv_ipc_irq_id, (voidfuncptr)icc_ipc_isr, ICC_SHARED_IPC_CHN_IDX);
}


s32 bsp_icc_channel_reset(DRV_RESET_CALLCBFUN_MOMENT stage, int usrdata)
{
	return ICC_OK;
}

EXPORT_SYMBOL(bsp_icc_read);              /*lint !e19 */
EXPORT_SYMBOL(bsp_icc_send);              /*lint !e19 */
EXPORT_SYMBOL(bsp_icc_send_sync);         /*lint !e19 */
EXPORT_SYMBOL(bsp_icc_event_register);    /*lint !e19 */
EXPORT_SYMBOL(bsp_icc_event_unregister);  /*lint !e19 */
arch_initcall(bsp_icc_init);                     /*lint !e19 */
module_exit(bsp_icc_release);                  /*lint !e19 !e132 !e578*/

