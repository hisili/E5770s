

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/input.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/suspend.h>
#include <asm/irq.h>
#include "bsp_icc.h"
#include "osl_common.h"


#define M_WAKEUP_AP_PORT	202
#define AP_WAKEUP_M_PROT	17
#define GPIO_SET_HIGH		1
#define GPIO_SET_LOW		0

u8 respon_flag = 0;
struct workqueue_struct *suspend_gpio_work_queue;
/*****************************************************************************
 �� �� ��  : wakeup_v3modem_gpio
 ��������  : �������У�����gpio
 �������  : 
 �������  : ��
 �� �� ֵ  : void
*****************************************************************************/
static void wakeup_v3modem_gpio(struct work_struct *work)
{

	gpio_set_value(AP_WAKEUP_M_PROT,GPIO_SET_LOW);
	mdelay(5);
	gpio_set_value(AP_WAKEUP_M_PROT,GPIO_SET_HIGH);
	mdelay(5);
	gpio_set_value(AP_WAKEUP_M_PROT,GPIO_SET_LOW);
	
}

static DECLARE_WORK(suspend_gpio_work, wakeup_v3modem_gpio);

/*****************************************************************************
 �� �� ��  : ap_wakeup_modem
 ��������  : modem����icc��ap�����gpio���ѶԷ�modem
 �������  : 
 �������  : ��
 �� �� ֵ  : void
*****************************************************************************/
int ap_wakeup_modem(u32 chan_id, u32 len, void* context)
{
	
	s32 read_size = 0;
	u8 flag = 0;
	context = context;		//��ֹ����澯
 	read_size = bsp_icc_read((ICC_CHN_IFC << 16)|IFC_RECV_FUNC_UART, &flag, len); 
	if ((read_size > (s32)len) && (read_size <= 0))
    {
        return 1;
    }
	if(flag == 0x1)
		respon_flag = 1;
	
	queue_work(suspend_gpio_work_queue, &suspend_gpio_work);	
	return 0;
}
/*****************************************************************************
 �� �� ��  : ap_wakeup_modemhandler
 ��������  : gpio�жϴ�����������icc��modem
 �������  : 
 �������  : 
 �� �� ֵ  : void
*****************************************************************************/
void ap_wakeup_modemhandler(int tem,void *dev)
{
	u8 flag = 0;

	tem = tem;		//��ֹ����澯
	dev = dev;		//��ֹ����澯
	if(respon_flag == 0)
		flag = 0x1; //�Է����ѣ�����ȷ���ź�
	else 
	{
		flag = 0x2;
		respon_flag = 0;
	}
	bsp_icc_send((u32)ICC_CPU_MODEM,(ICC_CHN_IFC << 16)|IFC_RECV_FUNC_UART,&flag,sizeof(flag));
	//��һ����ʼ����ɱ�־
}
/*****************************************************************************
 �� �� ��  : wakeup_modem_init
 ��������  : ap��gpio��ʼ��
 �������  : 
 �������  : 
 �� �� ֵ  : 0:�ɹ���-1:ʧ��
*****************************************************************************/
int wakeup_modem_init(void)
{
	int ret = 0;
	int irq_id = 0;
	
	ret = gpio_request(M_WAKEUP_AP_PORT,"wakeup modem");
	if(ret <0)
	{
		printk("wakeup modem gpio request failed!\r\n");
		goto err_wakeup_modem_gpio_req;
	}
	gpio_direction_input(M_WAKEUP_AP_PORT);
	irq_id = gpio_to_irq(M_WAKEUP_AP_PORT);
	ret = request_irq(irq_id,(irq_handler_t)ap_wakeup_modemhandler,IRQF_NO_SUSPEND|IRQF_TRIGGER_FALLING,"ap_wakeup_modem",NULL);
	if(ret)
	{
		printk("gpio irq register failed!\n");
		goto err_irq_req;
	}
	
	ret = gpio_request(AP_WAKEUP_M_PROT,"wakeup v3");
	if(ret <0)
	{
		printk("wakeup v3 gpio request failed!\r\n");
		goto err_wakeup_v3_gpio_req;
	}
	
	gpio_direction_output(AP_WAKEUP_M_PROT,GPIO_SET_LOW);
		
	suspend_gpio_work_queue = create_singlethread_workqueue("wakeup v3 modem");
		
	/* ע��ICC��д�ص� */
    if(OK !=bsp_icc_event_register((ICC_CHN_IFC << 16)|IFC_RECV_FUNC_UART,ap_wakeup_modem , NULL, NULL, NULL))
    {
        printk("register icc callback fail!\n");
    }
	
	enable_irq(irq_id);
	return 0;
	
err_wakeup_v3_gpio_req:
	gpio_free(AP_WAKEUP_M_PROT);	
err_irq_req:	
	free_irq(irq_id, NULL);

err_wakeup_modem_gpio_req:
	gpio_free(M_WAKEUP_AP_PORT);
	printk("wakeup modem init .......ERROR!\n");

	return -1;
}


module_init(wakeup_modem_init);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon Drive Group");
