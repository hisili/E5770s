#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include "drv_pcsc.h"



/*****************************************************************************
* �� �� ��  : pcsc_usim_ctrl_cmd
*
* ��������  : USIMMģ�鴦��PCSC�·������ɺ󣬵��˺���֪ͨPCSC
*
* �������  : cmd_type:USIMM��������
*             status:  ����Ĵ��������Ƿ�ɹ�
*             buf:   ������Ļ�Ӧ����
*             length:��Ӧ���ݵĳ���
* �������  : ��
* �� �� ֵ  : 0:��������; <0:��������
*****************************************************************************/
unsigned long pcsc_usim_ctrl_cmd(unsigned long cmd_type, unsigned long status, 
                unsigned char *buf, unsigned long length)
{
    int ret;
    ret = gusim_ctrl_cmd(0, (u32)cmd_type, (u32)status, (u8*)buf, (u32)length);

    return (unsigned long)ret;
}


/*****************************************************************************
* �� �� ��  : pcsc_usim_int
*
* ��������  : USIMģ��ע��ص������ӿ�
*
* �������  : pFun: USIMMģ�鴦����ָ��
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
void pcsc_usim_int(pFunAPDUProcess pFun1, GetCardStatus pFun2)
{
    gusim_reg_cb(0, pFun1, pFun2);
}


