
#ifndef __TEMPERATURE_BALONG_H__
#define __TEMPERATURE_BALONG_H__

#define TEMPERATURE_OK                   0
#define TEMPERATURE_ERROR                -1

/*****************************************************************************
* �� �� ��  : TEM_FUNCPTR
*
* ��������  : ���ڻص�POWER_SUPPLY�¼��ϱ�����
*
* �������  : u32 device_id        DEVICE_ID_TEMP
*             u32 event_id         POWER_SUPPLY_HEALTH_COLD����POWER_SUPPLY_HEALTH_DEAD
*
* �������  : ��
*
* �� �� ֵ  : 0 �ɹ� -1ʧ��
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
typedef void (*TEM_FUNCPTR)(unsigned int device_id, unsigned int event_id);

s32 bsp_tem_protect_callback_register(TEM_FUNCPTR p);



#endif
