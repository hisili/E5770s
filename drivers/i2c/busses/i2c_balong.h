

#ifndef I2C_BALONG_H
#define I2C_BALONG_H

#include <linux/i2c.h>
#include "bsp_i2c.h"

/* i2c controller state */
enum balong_i2c_state {
	STATE_IDLE,
	STATE_START,
	STATE_READ,
	STATE_WRITE,
	STATE_STOP
};

struct platform_i2c{
	int bus_num;
	unsigned int flags;
	unsigned int slave_addr;
	unsigned long frequency;
	unsigned int sda_delay;
};

struct balong_i2c {
	spinlock_t		lock;
	wait_queue_head_t	wait;		/*�����ݷ��ͺ���his_doxfer��wait_evnt_timeout,�����ݷ�����ɺ�ͨ�� master_complete���ͻ����ź�*/
	unsigned int		suspended:1;

	struct i2c_msg		*msg;	/*�����շ����ݵĽṹ��*/
	unsigned int		msg_num;
	unsigned int		msg_idx;	/*��ǰ���ڴ����msg��msg_num�е����к�*/
	unsigned int		msg_ptr;	

	unsigned int		tx_setup;/*���ݷ���Ĵ�������Ҫһ�εȴ�ʱ��*/
	unsigned int		irq;

	enum balong_i2c_state	state;	
	unsigned long		clkrate;

	void __iomem		*regs;
	struct clk		*clk;
	struct device		*dev;
	struct resource		*ioarea;
	struct i2c_adapter	adap;

#ifdef CONFIG_CPU_FREQ
	struct notifier_block	freq_transition;
#endif
};

#endif

