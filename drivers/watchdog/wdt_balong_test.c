
/*A core test*/
#include <bsp_wdt.h>
#include <hi_wdt.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <osl_spinlock.h>

s32 hi6930_wdt_case01(void);
s32 hi6930_wdt_case02(void);
s32 hi6930_wdt_case03(void);
s32 hi6930_wdt_case04(void);
s32 hi6930_wdt_case05(void);
void bsp_wdt_print_debug(void);
void bsp_wdt_test(void);

/*��ʼ��WDT��ʹ��WDT��ȥʹ��WDT*/
s32 hi6930_wdt_case01(void)
{
	u32 timeout = 0;
	/* ʹ�ܸ�λ���ж� */
	bsp_wdt_start();
	/*���ó�ʱʱ��*/
	bsp_wdt_set_timeout(30);	
	/* ��ȡ���Ź�ʣ�೬ʱʱ�� */
	bsp_wdt_get_timeleft(&timeout);
	printk("TIMEOUT = %d\n", timeout);  
	/*stop watchdog*/
	if (0 == bsp_wdt_stop())
	{
  	  printk("***************hi6930_wdt_case01 pass*******************\n");   
   	}
   else
   	{
	  printk("***************hi6930_wdt_case01 fail*******************\n");
	  return WDT_ERROR;
   	}
	return WDT_OK;
}

/*��ʼ��WDT��ʹ��WDT��WDTһֱ����*/
s32 hi6930_wdt_case02(void)
{
	u32 timeout = 0;
	/* ʹ�ܸ�λ���ж� */
	bsp_wdt_start();
	/*���ó�ʱʱ��*/
	bsp_wdt_set_timeout(30);	
	/* ��ȡ���Ź�ʣ�೬ʱʱ�� */
	bsp_wdt_get_timeleft(&timeout);
	printk("TIMEOUT = %d\n", timeout);  
	/*watchdog running*/
	printk("***************hi6930_wdt_case02 pass*******************\n"); 
	return WDT_OK;
}

/*ʹ��WDT�������ж�(A��)����λ*/
s32 hi6930_wdt_case03(void)
{
	/* ��ʹ�ܸ�λ���ж� */
	bsp_wdt_start();
	/*���ó�ʱ���*/
	bsp_wdt_set_timeout(5);

	 printk("***************hi6930_wdt_case03 pass*******************\n"); 
	 return WDT_OK;
}

/*���Իص�����*/
s32 hi6930_wdt_case04(void)
{
   	wdt_timeout_cb wdt_hook = (void*)1;
   	bsp_wdt_register_hook(wdt_hook);
   	bsp_wdt_unregister_hook();
   	printk("***************hi6930_wdt_case04 pass*******************\n"); 
   	return WDT_OK;
}

/*�͹��Ľӿ�*/
s32 hi6930_wdt_case05(void)
{
	bsp_wdt_start();
	/*���ü���ʱ��60s*/
	bsp_wdt_suspend(60);
	/*����ʱ��ָ�Ϊ30s*/
	bsp_wdt_resume();
	bsp_wdt_stop();
	printk("***************hi6930_wdt_case05 pass*******************\n"); 
	return WDT_OK;
}




void bsp_wdt_test(void)
{
	 spinlock_t lock;
    wdt_err("enter wdt test\n");
    spin_lock_init(&lock);
    spin_lock(&lock);
    spin_lock(&lock);
    
}


/*************************************wdt auto test start********************************************/
/* wdt nv must be enable*/
int bsp_wdt_start_test001(void)
{
	int timeleft = 0;
	bsp_wdt_start();

	bsp_wdt_get_timeleft(&timeleft);
	if (timeleft <= 30)
	{
		return BSP_OK;
	}
	else
	{
		return BSP_ERROR;
	}
}

int bsp_wdt_stop_test002(void)
{
	int timeleft = 0;
	bsp_wdt_start();
	bsp_wdt_stop();
	bsp_wdt_get_timeleft(&timeleft);
	if ((timeleft < 30) && (timeleft > 0))
	{
		wdt_err("%d\n", timeleft);
		return BSP_ERROR;
	}
	else
	{
		return BSP_OK;
	}
}

int bsp_wdt_keeplive_test003(void)
{
	int timeleft = 0;
	bsp_wdt_start();
	bsp_wdt_keepalive();
	bsp_wdt_get_timeleft(&timeleft);
	if ((timeleft > 20) && (timeleft <=30))
	{
		return BSP_OK;
	}
	else
	{
		return BSP_ERROR;
	}
}

int bsp_wdt_set_timeout_test004(void)
{
	int timeleft = 0;
	bsp_wdt_start();
	bsp_wdt_set_timeout(60);
	bsp_wdt_get_timeleft(&timeleft);
	if ((timeleft > 30) && (timeleft <=60))
	{
		return BSP_OK;
	}
	else
	{
		return BSP_ERROR;
	}
}

int bsp_wdt_register_hook_test005(void)
{
	int timeleft = 0;
	bsp_wdt_register_hook(&timeleft);
	bsp_wdt_reboot_register_hook(&timeleft);
	return BSP_OK;
}

int bsp_wdt_unregister_hook_test006(void)
{
	bsp_wdt_unregister_hook();
	bsp_wdt_reboot_unregister_hook();
	return BSP_OK;
}
/*************************************wdt auto test end********************************************/
