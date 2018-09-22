#include <asm/mach/irq.h>
#include <linux/interrupt.h>
#include "bsp_pmu.h"
#include "hi_smartstar.h"
#include "irq_hi6551.h"
#include "coul_hi6551.h"

extern unsigned short coul_voltage(void);
extern unsigned short coul_current(void);
extern unsigned int coul_capacity(void);

/*****************************************************************************
 �� �� ��  : coul_battery_voltage
 ��������  : ��ǰ��ѹ��ȡ����λ:uV/1000
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned long long
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned long long coul_battery_voltage_test(void)
{
    unsigned short  val = 0;
    unsigned long long voltage = 0;

    val = coul_voltage();

    voltage = val * 225120;

    coul_dbg("coul_battery_voltage is %lld\n",voltage);

    return voltage;
}

/*****************************************************************************
 �� �� ��  : coul_battery_current
 ��������  : ��ǰ������ȡ,��λ:uA/1000
 �������  : void
 �������  : ��
 �� �� ֵ  : long long
 ���ú���  :
 ��������  :
*****************************************************************************/
signed long long  coul_battery_current_test(void)
{
    unsigned int  val = 0;
    signed long long  bat_current = 0;

    val = coul_current();

    bat_current = val * 468999;

    coul_dbg("coul_battery_current is %lld\n",bat_current);

    return bat_current;
}

/*****************************************************************************
 �� �� ��  : coul_battery_capacity
 ��������  : ��ص�����ȡ,��λ:uAh/1000
 �������  : void
 �������  : ��
 �� �� ֵ  : long long
 ���ú���  :
 ��������  :
*****************************************************************************/
signed long long coul_battery_in_capacity_test(void)
{
    unsigned int  val = 0;
    signed long long capacity = 0;

    val = coul_in_capacity();

    capacity = val * 14330;

    coul_dbg("coul_battery_capacity is %lld\n",capacity);

    return capacity;
}
/*****************************************************************************
 �� �� ��  : coul_battery_capacity
 ��������  : ��ص�����ȡ,��λ:uAh/1000
 �������  : void
 �������  : ��
 �� �� ֵ  : long long
 ���ú���  :
 ��������  :
*****************************************************************************/
signed long long coul_battery_out_capacity_test(void)
{
    unsigned int  val = 0;
    signed long long capacity = 0;

    val = coul_out_capacity();

    capacity = val * 14330;

    coul_dbg("coul_battery_capacity is %lld\n",capacity);

    return capacity;
}

