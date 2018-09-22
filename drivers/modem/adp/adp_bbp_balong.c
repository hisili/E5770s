
/*lint --e{537}*/
#include "drv_comm.h"
#include "bsp_bbp.h"
#include "drv_bbp.h"
#include "product_config.h"

/*****************************************************************************
* ����  : BSP_BBPGetCurTime
* ����  : ��PS���ã�������ȡϵͳ��ȷʱ��
* ����  : void
* ���  : u64 *pcurtime
* ����  : u32
*****************************************************************************/
BSP_U32 BSP_BBPGetCurTime(BSP_U64 *pCurTime)
{
    return bsp_bbp_getcurtime(pCurTime);
}

/*****************************************************************************
* ����  : BSP_BBPGetCurTime
* ����  : ��ȡBBP��ʱ����ֵ������OAM ʱ��
* ����  : void
* ���  :
			pulLow32bitValueָ���������Ϊ�գ�����᷵��ʧ�ܡ�
			pulHigh32bitValue���Ϊ�գ� ��ֻ���ص�32bit��ֵ��
* ����  : int
*****************************************************************************/
int DRV_GET_BBP_TIMER_VALUE(unsigned int  *pulHigh32bitValue,  unsigned int  *pulLow32bitValue)
{
	BSP_U64 CurTime;

	if(BSP_NULL == pulLow32bitValue)
	{
		return -1;
	}

	bsp_bbp_getcurtime(&CurTime);

	if(BSP_NULL != pulHigh32bitValue)
	{
		*pulHigh32bitValue = (CurTime>>32);
	}

	*pulLow32bitValue = CurTime & 0xffffffff;

	return 0;
}
