

#ifndef _ACPULOAD_
#define _ACPULOAD_

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "product_config.h"


#pragma pack(4)

/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  3 �궨��
*****************************************************************************/

#define CPULOAD_MAX_HOOK_NUM        (2)     /* CPU�����ϱ�������� */

#define CPULOAD_REGULAR_TMR_DEF_LEN (400)   /* CPUͳ��Ĭ�ϼ��ʱ�䣬��λ���� */
#define CPULOAD_REGULAR_TMR_MIN_LEN (100)   /* CPUͳ����С���ʱ�䣬��λ���� */
#define CPULOAD_REGULAR_TMR_MAX_LEN (1000)  /* CPUͳ�������ʱ�䣬��λ���� */

#define CPULOAD_REGULAR_TMR_NAME    (1)

#define CPULOAD_CPU_IDLE            (0)     /* V9R1��OM����CPULOAD_GetCpuLoadʱ���ú�����׮�������ؿ��� */


/*****************************************************************************
  4 STRUCT����
*****************************************************************************/
/*****************************************************************************
�ṹ��    : CPULOAD_STAT_RECORD_STRU
Э����  : ��
ASN.1���� : ��
�ṹ˵��  : ��¼CPUͳ������
*****************************************************************************/
typedef struct
{

    VOS_UINT32                      ulIdleTime;          /* ������������ʱ�� */
    VOS_UINT32                      ulTotalTime;         /* ������ʱ�� */

}CPULOAD_STAT_RECORD_STRU;

/*****************************************************************************
�ṹ��    : CPULOAD_STAT_INFO_STRU
Э����  : ��
ASN.1���� : ��
�ṹ˵��  : ����CPU����������Ϣ
*****************************************************************************/
typedef struct
{
	CPULOAD_STAT_RECORD_STRU    stCurrRecord;   /* ��¼��ǰCPUͳ����Ϣ */
	CPULOAD_STAT_RECORD_STRU    stPrevRecord;   /* ��¼��һ��CPUͳ����Ϣ */

	VOS_UINT8                   ucCpuId;        /* the CPU ID number */
	VOS_UINT8                   aucRsv[3];
	VOS_UINT32                  ulCpuLoad;      /* ��¼��ǰCPU���� */

} CPULOAD_STAT_INFO_STRU;



/******************************************************************************
   5 ��������
******************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* CpuLoad.h */

