/*
#include <vxWorks.h>
#include <logLib.h>
#include <usrLib.h>
#include <string.h>
#include <stdio.h>
#include "BSP_UDI.h"
#include "BSP_UDI_DRV.h"
*/

#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/semaphore.h>

#include "udi_balong.h"



#define UDI_MAX_MAIN_DEV_NUM UDI_DEV_MAX
#define UDI_MAX_DEV_TYPE_NUM 32
#define UDI_MAX_OPEN_NODE_NUM 64
//#define UDI_MAX_INIT_FUNC_NUM UDI_TYPE_MAX
#define UDI_OPEN_NODE_HEADER  0x5A0000

/* Mutex ��Ϊ��װ */

#define UDI_DEBUG

/**************************************************************************
  ���Ͷ���
**************************************************************************/
/* �豸�򿪽ڵ� */
typedef struct tagUDI_OPEN_NODE
{
	BSP_BOOL bOpen;
	VOID* pPrivate;
	UDI_DRV_INTEFACE_TABLE *pstDrvTable;
}UDI_OPEN_NODE;

/* �豸ʵ������ */
typedef struct tagUDI_DEV_INSTANCE
{
	//BSP_U32 u32MagicNum;				/* ����� */
	//BSP_U32 u32DevId;					/* �豸ID */
	BSP_U32 u32Capability;					/* �豸���� */
	//BSP_U8* strDevName;					/* �豸��,��������ϵͳ��׼�豸 */
	UDI_DRV_INTEFACE_TABLE *pDrvInterface;  /* �ӿڻص��б� */
	BSP_VOID* pPrivate;					/* ÿ������˽��ȫ�� */
}UDI_DEV_INSTANCE;


/**************************************************************************
  ȫ�ֱ���
**************************************************************************/
UDI_OPEN_NODE			g_openNodeTable[UDI_MAX_OPEN_NODE_NUM];
BSP_U32					g_openNodeCurPos = 0;
UDI_DEV_INSTANCE			g_deviceTable[UDI_MAX_MAIN_DEV_NUM][UDI_MAX_DEV_TYPE_NUM];
extern UDI_ADP_INIT_CB_T	g_udiInitFuncTable[UDI_DEV_MAX+1];
/*UDI_MUTEX_T g_udiMtxOpen;*/
struct semaphore			g_udiMtxOpen;

/**************************************************************************
  ��ʵ��
**************************************************************************/
#define UDI_OFFSET_OF(type, member) ((BSP_U32) (&((type *)0)->member))
#define UDI_IDX_TO_HANDLE(idx) ((UDI_HANDLE)(UDI_OPEN_NODE_HEADER | (idx)))
#define UDI_HANDLE_TO_IDX(hdl) ((BSP_U32)((hdl) & 0xFFFF))

#define UDI_IS_INVALID_TABLE(pstDrvTable) \
    (0 == (BSP_U32)(pstDrvTable) || (BSP_U32)(-1) == (BSP_U32)(pstDrvTable))

#define UDI_PARSE_DEV_ID(devId, mainId, devType) \
do{\
	mainId = UDI_GET_MAIN_DEV_ID(devId);\
	devType = UDI_GET_DEV_TYPE(devId);\
	\
	bsp_assert(mainId < UDI_MAX_MAIN_DEV_NUM);\
	bsp_assert(devType < UDI_MAX_DEV_TYPE_NUM);\
}while(0)

#define UDI_CALL_OPT_FUNC_SAFELY(handle, param1, param2, functionCB, ret) \
do{\
	BSP_U32 u32Idx;\
	UDI_DRV_INTEFACE_TABLE *pstDrvTable;\
	VOID* pPrivate;\
	\
	UDI_CHECK_HANDLE(handle);\
	u32Idx = UDI_HANDLE_TO_IDX(handle);\
	\
	if (u32Idx >= UDI_MAX_OPEN_NODE_NUM)\
	{\
		/*printk(KERN_ERR "BSP_MODU_UDI invalid handle:0x%x, line:%d\n",*/ \
		/*	handle, __LINE__);*/\
		return ERROR;\
	}\
	/* ȡ������ָ�뼰���� */\
	pstDrvTable = g_openNodeTable[u32Idx].pstDrvTable;\
	if (UDI_IS_INVALID_TABLE(pstDrvTable))\
    {\
        /*printk(KERN_ERR "pstDrvTable is Invalid, line:%d\n",*/ \
		/*	__LINE__);*/\
        return ERROR;\
    }\
	if (NULL == pstDrvTable->functionCB)\
	{\
		/*printk(KERN_ERR "BSP_MODU_UDI %s callback is NULL, line:%d\n", */\
		/*	#functionCB, __LINE__);*/\
		return ERROR;\
	}\
	pPrivate = g_openNodeTable[u32Idx].pPrivate;\
	\
	/* �����û��Ļص����� */\
	ret = pstDrvTable->functionCB(pPrivate, param1, param2);\
}while(0)

#ifdef UDI_DEBUG
#define UDI_CHECK_HANDLE(handle) \
do{\
	if ((handle & 0xFF0000) != UDI_OPEN_NODE_HEADER || \
	UDI_HANDLE_TO_IDX(handle) >= UDI_MAX_OPEN_NODE_NUM)\
	{\
		/*printk(KERN_ERR "BSP_MODU_UDI invalid handle:0x%x, line:%d\n",*/ \
		/*	handle, __LINE__);*/\
		return ERROR;\
	}\
}while(0)
#else
#define UDI_CHECK_HANDLE(handle)
#endif

/**************************************************************************
  �ڲ�����
**************************************************************************/
static UDI_HANDLE udiGetOutOpenNode(VOID)
{
	BSP_U32 u32Cnt;
	UDI_HANDLE handle = UDI_INVALID_HANDLE;

	down(&g_udiMtxOpen);
	/* ���ȴӵ�ǰλ���� */
	for (u32Cnt = g_openNodeCurPos; u32Cnt < UDI_MAX_OPEN_NODE_NUM; u32Cnt++)
	{
		if (FALSE == g_openNodeTable[u32Cnt].bOpen)
		{
			handle = UDI_IDX_TO_HANDLE(u32Cnt);
			break;
		}
	}

	/* ����, �ٴ�ͷ�� */
	if(UDI_INVALID_HANDLE == handle)
	{
		for (u32Cnt = 0; u32Cnt < g_openNodeCurPos; u32Cnt++)
		{
			if (FALSE == g_openNodeTable[u32Cnt].bOpen)
			{
				handle = UDI_IDX_TO_HANDLE(u32Cnt);
				break;
			}
		}
	}

	/* �ҵ�һ�����õ�handle */
	if (UDI_INVALID_HANDLE != handle)
	{
		g_openNodeCurPos = (u32Cnt+1) % UDI_MAX_OPEN_NODE_NUM;
		g_openNodeTable[u32Cnt].bOpen = TRUE;
	}
	up(&g_udiMtxOpen);

	return handle;
}

static BSP_S32 udiReturnOpenNode(BSP_U32 u32Idx)
{
	bsp_assert(u32Idx < UDI_MAX_OPEN_NODE_NUM);
    /*lint 661*/
	if( u32Idx >=UDI_MAX_OPEN_NODE_NUM )
	{
		printk("BSP_UDI_SetCapability para error: u32Idx=%u\n", u32Idx);
		return ERROR;
	}
	down(&g_udiMtxOpen);
	g_openNodeTable[u32Idx].bOpen = FALSE;
	g_openNodeTable[u32Idx].pstDrvTable = (UDI_DRV_INTEFACE_TABLE*)(-1);
	up(&g_udiMtxOpen);

	return OK;
}

/**************************************************************************
  �ӿ�ʵ��
**************************************************************************/

/*****************************************************************************
* �� �� ��  : BSP_UDI_SetPrivate
*
* ��������  : ���������ڲ�˽������
*
* �������  : devId: �豸ID
*             pPrivate: ˽������
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_UDI_SetPrivate(UDI_DEVICE_ID devId, VOID* pPrivate)
{
	BSP_U32 u32MainId;
	BSP_U32 u32DevType;
    /*lint  e661 e662*/
	UDI_PARSE_DEV_ID(devId, u32MainId, u32DevType);
	if((u32MainId >= UDI_MAX_MAIN_DEV_NUM)||(u32DevType >= UDI_MAX_DEV_TYPE_NUM))
	{
      printk("BSP_UDI_SetCapability para error: u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);
	  return ERROR;
	}
	g_deviceTable[u32MainId][u32DevType].pPrivate = pPrivate;

	return OK;
}

/*****************************************************************************
* �� �� ��  : BSP_UDI_SetCapability
*
* ��������  : �����豸����ֵ
*
* �������  : devId: �豸ID
*             u32Capability: �豸����ֵ
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_UDI_SetCapability(UDI_DEVICE_ID devId, BSP_U32 u32Capability)
{
	BSP_U32 u32MainId;
	BSP_U32 u32DevType;

    /*lint e662 e661*/
	UDI_PARSE_DEV_ID(devId, u32MainId, u32DevType);
	if((u32MainId >= UDI_MAX_MAIN_DEV_NUM)||(u32DevType >= UDI_MAX_DEV_TYPE_NUM))
	{
      printk("BSP_UDI_SetCapability para error: u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);
	  return ERROR;
	}
	g_deviceTable[u32MainId][u32DevType].u32Capability = u32Capability;
	//printk("BSP_UDI_SetCapability **********************  u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);


	return OK;
}

/*****************************************************************************
* �� �� ��  : BSP_UDI_SetInterfaceTable
*
* ��������  : �����豸�ص������б�(����������)
*
* �������  : devId: �豸ID
*             pDrvInterface: ������Ļص������б�
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_UDI_SetInterfaceTable(UDI_DEVICE_ID devId, UDI_DRV_INTEFACE_TABLE *pDrvInterface)
{
	BSP_U32 u32MainId;
	BSP_U32 u32DevType;
    /*lint e661 e662*/
	UDI_PARSE_DEV_ID(devId, u32MainId, u32DevType);
	if((u32MainId >= UDI_MAX_MAIN_DEV_NUM)||(u32DevType >= UDI_MAX_DEV_TYPE_NUM))
	{
      printk("BSP_UDI_SetInterfaceTable para error: u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);
	  return ERROR;
	}
	g_deviceTable[u32MainId][u32DevType].pDrvInterface = pDrvInterface;
	//printk("BSP_UDI_SetInterfaceTable  **********************  u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);

	return OK;
}

/*****************************************************************************
* �� �� ��  : BSP_UDI_Init
*
* ��������  : UDI ģ���ʼ��
*
* �������  : ��
* �������  : ��
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 BSP_UDI_Init(void)
{
	UDI_ADP_INIT_CB_T initCB;
	BSP_U32 u32Cnt;

	memset(g_deviceTable, 0, sizeof(g_deviceTable));
	memset(g_openNodeTable, 0, sizeof(g_openNodeTable));

	sema_init(&g_udiMtxOpen, SEM_FULL);

	/* ���ó�ʼ������ */
	for (u32Cnt = 0; u32Cnt < (BSP_U32)UDI_DEV_MAX; u32Cnt++)
	{
		initCB = g_udiInitFuncTable[u32Cnt];
		if (initCB)
		{
			if (initCB() != OK)
			{
				printk(KERN_ERR "BSP_MODU_UDI usr initCB fail, line:%d\n", __LINE__);
				return ERROR;
			}
		}
	}
	return OK;
}

/*****************************************************************************
* �� �� ��  : udi_get_capability
*
* ��������  : �����豸ID��ȡ��ǰ�豸֧�ֵ�����
*
* �������  : devId: �豸ID
* �������  : ��
* �� �� ֵ  : ֧�ֵ�����ֵ
*****************************************************************************/
BSP_S32 udi_get_capability(UDI_DEVICE_ID devId)
{
	BSP_U32 u32MainId;
	BSP_U32 u32DevType;

	UDI_PARSE_DEV_ID(devId, u32MainId, u32DevType);
	/* lint e661 e662*/
	if((u32MainId >= UDI_MAX_MAIN_DEV_NUM)||(u32DevType >= UDI_MAX_DEV_TYPE_NUM))
	{
      printk("udi_get_capability para error: u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);
	  return ERROR;
	}
	return (BSP_S32)g_deviceTable[u32MainId][u32DevType].u32Capability;
}

/*****************************************************************************
* �� �� ��  : BSP_UDI_GetPrivate
*
* ��������  : �õ��豸 �����ڲ�˽������
*
* �������  : handle: �豸��handle
* �������  : ��
* �� �� ֵ  : �豸�ڲ�˽������
*****************************************************************************/
BSP_S32 BSP_UDI_GetPrivate(UDI_HANDLE handle)
{
	BSP_U32 u32Idx = 0;

	if (UDI_INVALID_HANDLE == handle)
	{
		printk(KERN_ERR "BSP_MODU_UDI can't find open node, line:%d\n", __LINE__);
		return (BSP_S32)NULL;
	}

	u32Idx = UDI_HANDLE_TO_IDX(handle);

	return (BSP_S32)g_openNodeTable[u32Idx].pPrivate;
}

/*****************************************************************************
* �� �� ��  : udi_open
*
* ��������  : ���豸(����ͨ��)
*
* �������  : pParam: �豸�Ĵ����ò���
* �������  : ��
* �� �� ֵ  : -1:ʧ�� / ����:�ɹ�
*****************************************************************************/
UDI_HANDLE udi_open(UDI_OPEN_PARAM *pParam)
{
	BSP_U32 u32MainId = 0;
	BSP_U32 u32DevType = 0;
	BSP_U32 u32Idx = 0;
	UDI_HANDLE handle;
	UDI_DRV_INTEFACE_TABLE *pstDrvTable;

	if (NULL == pParam)
	{
		goto UDI_OPEN_ERR;
	}
	/*lint e662 e661*/
	UDI_PARSE_DEV_ID(pParam->devid, u32MainId, u32DevType);
   if((u32MainId >= UDI_MAX_MAIN_DEV_NUM)||(u32DevType >= UDI_MAX_DEV_TYPE_NUM))
	{
      /*printk("udi_open para error: u32MainId=%u u32DevType=%u\n", u32MainId, u32DevType);*/
	  goto UDI_OPEN_ERR;
	}
	/* ����һ�����õĽڵ� */
	handle = udiGetOutOpenNode();
	if (UDI_INVALID_HANDLE == handle)
	{
		/*printk(KERN_ERR "BSP_MODU_UDI can't find open node, line:%d\n", __LINE__);*/
		goto UDI_OPEN_ERR;
	}
	u32Idx = UDI_HANDLE_TO_IDX(handle);

	/* �����û��ص����� */
	pstDrvTable = g_deviceTable[u32MainId][u32DevType].pDrvInterface;
	if (NULL == pstDrvTable || NULL == pstDrvTable->udi_open_cb)
	{
		/*printk(KERN_ERR "BSP_MODU_UDI usr open cb is NULL, line:%d\n", __LINE__);*/
		goto UDI_OPEN_ERR_RET_NODE;
	}
	if (pstDrvTable->udi_open_cb(pParam, handle))
	{
		/*printk(KERN_ERR "BSP_MODU_UDI usr open fail, line:%d\n", __LINE__);*/
		goto UDI_OPEN_ERR_RET_NODE;
	}

	/* ��������˽������ */
	g_openNodeTable[u32Idx].pstDrvTable =
	g_deviceTable[u32MainId][u32DevType].pDrvInterface;
	g_openNodeTable[u32Idx].pPrivate =
	g_deviceTable[u32MainId][u32DevType].pPrivate;

	return handle;

UDI_OPEN_ERR_RET_NODE:
	(BSP_VOID)udiReturnOpenNode(u32Idx);
UDI_OPEN_ERR:
	return UDI_INVALID_HANDLE;
}

/*****************************************************************************
* �� �� ��  : udi_close
*
* ��������  : �ر��豸(����ͨ��)
*
* �������  : handle: �豸��handle
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
BSP_S32 udi_close(UDI_HANDLE handle)
{
	BSP_S32 s32Ret = -1;
	BSP_U32 u32Idx;
	UDI_DRV_INTEFACE_TABLE *pstDrvTable;

	UDI_CHECK_HANDLE(handle);

	u32Idx = UDI_HANDLE_TO_IDX(handle);

	if (u32Idx >= UDI_MAX_OPEN_NODE_NUM)
	{
		/*printk(KERN_ERR "BSP_MODU_UDI invalid handle:0x%x, line:%d\n", handle, __LINE__);*/
		return ERROR;
	}
	/* �����û��Ļص����� */
	pstDrvTable = g_openNodeTable[u32Idx].pstDrvTable;
	if (UDI_IS_INVALID_TABLE(pstDrvTable))/*lint !e58*/
    {
        /*printk(KERN_ERR "pstDrvTable is Invalid, line:%d\n", __LINE__);*/
        return ERROR;
    }
	if (NULL == pstDrvTable->udi_close_cb)
	{
		/*printk(KERN_ERR "BSP_MODU_UDI udi_close_cb is NULL, line:%d\n", __LINE__);*/
		return ERROR;
	}
	s32Ret = pstDrvTable->udi_close_cb(g_openNodeTable[u32Idx].pPrivate);

	/* �ͷ� Open Node */
	(BSP_VOID)udiReturnOpenNode(u32Idx);

	return s32Ret;
}

/*****************************************************************************
* �� �� ��  : udi_write
*
* ��������  : ����д
*
* �������  : handle:  �豸��handle
*             pMemObj: buffer�ڴ� �� �ڴ��������
*             u32Size: ����д�ߴ� �� �ڴ��������ɲ�����
* �������  :
*
* �� �� ֵ  : ����ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_write(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size)
{
	BSP_S32 s32Ret = -1;
    /*lint -e58*/
	UDI_CALL_OPT_FUNC_SAFELY(handle, pMemObj, u32Size, udi_write_cb, s32Ret);
    /*lint +e58*/
	return s32Ret;
}

/*****************************************************************************
* �� �� ��  : udi_read
*
* ��������  : ���ݶ�
*
* �������  : handle:  �豸��handle
*             pMemObj: buffer�ڴ� �� �ڴ��������
*             u32Size: ���ݶ��ߴ� �� �ڴ��������ɲ�����
* �������  :
*
* �� �� ֵ  : ����ֽ��� �� �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_read(UDI_HANDLE handle, void* pMemObj, BSP_U32 u32Size)
{
	BSP_S32 s32Ret = -1;
    /*lint -e58*/
	UDI_CALL_OPT_FUNC_SAFELY(handle, pMemObj, u32Size, udi_read_cb, s32Ret);
    /*lint +e58*/
	return s32Ret;
}

/*****************************************************************************
* �� �� ��  : udi_ioctl
*
* ��������  : ����ͨ����������
*
* �������  : handle: �豸��handle
*             u32Cmd: IOCTL������
*             pParam: ��������
* �������  :
*
* �� �� ֵ  : �ɹ�/ʧ��
*****************************************************************************/
BSP_S32 udi_ioctl(UDI_HANDLE handle, BSP_U32 u32Cmd, VOID* pParam)
{
	BSP_S32 s32Ret = -1;
    /*lint -e58*/
	UDI_CALL_OPT_FUNC_SAFELY(handle, u32Cmd, pParam, udi_ioctl_cb, s32Ret);
    /*lint +e58*/
	return s32Ret;
}


arch_initcall(BSP_UDI_Init);




