

#ifndef __DRV_OTHERS_H__
#define __DRV_OTHERS_H__

#include "drv_comm.h"
#include "drv_others.h"


/*************************Build�Ż� START*****************************/




/*************************OAM��������ӿ� START***********************/













/*���߰汾дSDT��Ϣ���ļ�ϵͳ�ķ�����*/
#define MANUFACTURE_ROOT_PATH "/manufacture"






/*************************OAM��������ӿ� END*************************/

/************************ Build�Ż� END*******************************/


#if defined(BSP_CORE_MODEM)
/*****************************************************************************
 �� �� ��  : BSP_DMB_INSTRUCTION
 ��������  : DMB�ӿڣ�DSP����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
#define BSP_DMB_INSTRUCTION \
{\
    __asm("STMFD r13!, {r0}");\
    __asm("MOV r0, #0");\
    __asm("MCR p15, 0, r0, c7, c10, 5");\
    __asm("LDMIA r13!, {r0}");\
}
#define DRV_DMB_INSTRUCTION() BSP_DMB_INSTRUCTION
#endif

#endif

