
#ifndef _DRV_NVIM_H_
#define _DRV_NVIM_H_

/*lint -save -e537*/
#include "drv_comm.h"
/*lint -restore +e537*/

#ifdef __cplusplus
extern "C"
{
#endif

/*debug add*/
/*****************************************************************/
/* NV�ָ������� */
enum NV_RESUME_ITEM
{
    NV_MANUFACTURE_ITEM = 0,
    NV_USER_ITEM,
    NV_SECURE_ITEM,
    NV_MBB_DEFUALT_ITEM,
    NV_ITEM_BUTT
};
typedef unsigned long NV_RESUME_ITEM_ENUM_UINT32;

/*****************************************************************/

typedef struct
{
    BSP_U32 ulfilelen;
    BSP_U8 *pdata;
}NVIM_EXPORT_FILE_INFO_STRU;


typedef enum
{
	EN_NVM_HSO_HNV_FILE = 0,      /*HSO�����ɵ��ļ�*/
	EN_NVM_VERSION_FILE = 1,      /*��ǰ�汾ʹ�õ�NV�ļ�*/
    EN_NVM_BACKUP_FILE =2,           /*��������ʱ�����ݵ��ļ�*/
    EN_NVM_VERSION_INIT_FILE=3,     /*���ݵ�ǰ�汾�ĳ�ʼֵ*/
    EN_NVM_FILE_LAST
} NVM_FILE_TYPE_ENUM;

/*****************************************************************************
 �� �� ��  : NVM_Flush
 ��������  : ���ڴ�������ˢ�µ�FLASH��FILE�ӿ�
 �������  : NULL
 �������  :
 �� �� ֵ  :

*****************************************************************************/
BSP_U32 NVM_Flush(BSP_VOID);


/*****************************************************************************
 �� �� ��  : NVM_GetItemLength
 ��������  : ��ȡNV��Ƚӿ�
 �������  :
 �������  :
 �� �� ֵ  :

*****************************************************************************/
BSP_U32 NVM_GetItemLength(BSP_U16 ulid, BSP_U32 * pusitemlength);


/*****************************************************************************
 �� �� ��  : NVM_UpgradeBackup
 ��������  : ����NV�ӿ�
 �������  : NULL
 �������  :
 �� �� ֵ  :

*****************************************************************************/
BSP_U32 NVM_UpgradeBackup(BSP_U32 uloption);


/*****************************************************************************
 �� �� ��  : NVM_UpgradeRestore
 ��������  : �ָ�NV�ӿ�
 �������  : NULL
 �������  :
 �� �� ֵ  :

*****************************************************************************/
BSP_U32 NVM_UpgradeRestore(BSP_VOID);

/*****************************************************************************
 �� �� ��  : NVM_SetFactoryDefault
 ��������  : �ָ�����NV�ӿ�
 �������  : NULL
 �������  :
 �� �� ֵ  :

*****************************************************************************/
BSP_U32 NVM_SetFactoryDefault(BSP_VOID);


/*****************************************************************************
 �� �� ��  : NVM_RevertFNV
 ��������  : �ָ�����NV�ӿ�
 �������  : NULL
 �������  :
 �� �� ֵ  :

*****************************************************************************/
BSP_U32 NVM_RevertFNV(BSP_VOID);
/*****************************************************************************
 �� �� ��  : NVM_BackUpFNV
 ��������  : ���ݳ���nv�ӿ�
 �������  : NULL
 �������  :
 �� �� ֵ  :

*****************************************************************************/
BSP_U32 NVM_BackUpFNV(BSP_VOID);


/*****************************************************************************
 �ṹ��    : NV_LIST_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ȡNV�б���Ϣ
*****************************************************************************/
typedef struct
{
    unsigned short usNvId;                  /*NVIDֵ*/
    unsigned char  ucNvModemNum;            /*NV�Ƿ���ڶ��*/
    unsigned char  ucRsv;
}NV_LIST_INFO_STRU;

BSP_U32 NV_GetNVIdListNum(BSP_VOID);
BSP_U32 NV_GetNVIdList(NV_LIST_INFO_STRU *pstNvIdList);

/*enModemID :0(��1) or 1(��2)*/
BSP_U32 NV_ReadEx(BSP_U16  enModemID, BSP_U16 usID,BSP_VOID *pItem,BSP_U32 ulLength);
BSP_U32 NV_WriteEx(BSP_U16  enModemID,BSP_U16  usID,BSP_VOID   *pItem, BSP_U32  ulLength);
BSP_U32 NV_WritePartEx(BSP_U16   enModemID,BSP_U16   usID,BSP_U32  ulOffset,BSP_VOID *pItem,BSP_U32   ulLength);
BSP_U32 NV_ReadPartEx(BSP_U16 enModemID,BSP_U16 usID,BSP_U32 ulOffset,BSP_VOID *pItem,BSP_U32 ulLength);
BSP_U32 NV_Flush(BSP_VOID);
BSP_U32 NV_GetLength(BSP_U16 usID, BSP_U32 * pulLength);


#if defined (INSTANCE_1)
#define NV_Read(usID,pItem,ulLength)                NV_ReadEx(MODEM_ID_1,(usID),(pItem),(ulLength))

#define NV_ReadPart(usID,ulOffset,pItem,ulLength)   NV_ReadPartEx(MODEM_ID_1,(usID),(ulOffset),(pItem),(ulLength))

#define NV_Write(usID,pItem,ulLength)               NV_WriteEx(MODEM_ID_1,(usID),(pItem),(ulLength))

#define NV_WritePart(usID,ulOffset,pItem,ulLength)  NV_WritePartEx(MODEM_ID_1,(usID),(ulOffset),(pItem),(ulLength))

#define NVM_Read(usID,pItem,ulLength)                NV_ReadEx(MODEM_ID_1,(BSP_U16)(usID),(pItem),(BSP_U32)(ulLength))

#define NVM_Write(usID,pItem,ulLength)               NV_WriteEx(MODEM_ID_1,(BSP_U16)(usID),(pItem),(BSP_U32)(ulLength))

#else
#define NV_Read(usID,pItem,ulLength)                NV_ReadEx(MODEM_ID_0,(usID),(pItem),(ulLength))

#define NV_ReadPart(usID,ulOffset,pItem,ulLength)   NV_ReadPartEx(MODEM_ID_0,(usID),(ulOffset),(pItem),(ulLength))

#define NV_Write(usID,pItem,ulLength)               NV_WriteEx(MODEM_ID_0,(usID),(pItem),(ulLength))

#define NV_WritePart(usID,ulOffset,pItem,ulLength)  NV_WritePartEx(MODEM_ID_0,(usID),(ulOffset),(pItem),(ulLength))

#define NVM_Read(usID,pItem,ulLength)                NV_ReadEx(MODEM_ID_0,(BSP_U16)(usID),(pItem),(BSP_U32)(ulLength))

#define NVM_Write(usID,pItem,ulLength)               NV_WriteEx(MODEM_ID_0,(BSP_U16)(usID),(pItem),(BSP_U32)(ulLength))

#endif


BSP_U32 NV_GetResumeNvIdList(BSP_U32 enNvItem, BSP_U16 * pusNvList, BSP_U32 ulNvNum);
BSP_U32 NV_GetResumeNvIdNum(BSP_U32 enNvItem);

BSP_U32 NV_Backup(BSP_VOID);
BSP_U32 NV_BackupCheck(BSP_VOID);
BSP_U32 NV_RestoreAll(BSP_VOID);
BSP_U32 NV_RestoreManufacture(BSP_VOID);
BSP_U32 NV_RestoreResult(BSP_VOID);
BSP_U32 NV_RestoreManufactureDefault(BSP_VOID);
BSP_U32 NV_QueryRestoreResult(BSP_VOID);
BSP_U32 NV_Init(BSP_VOID);

BSP_U32 NV_SpecialNvIdBackup(BSP_U16 usID,BSP_VOID *pItem,BSP_U32 ulLength);


/* gu nv stub */
int DRV_NV_SEC_CHECK(char* path);
int DRV_COPY_NVUSE_TO_NVBACKUP(void);
int DRV_COPY_NVUPGRADE_TO_NVUSE(void);

static INLINE int DRV_NV_FILE_SEC_CHECK(char * pnvFilePath)
{
    pnvFilePath = pnvFilePath;
    return 0;
}

static INLINE int DRV_UPGRADE_NV_SET_RESULT(int status)
{
    status = status;
    return 0;
}

static INLINE unsigned int NV_RestoreManufactureExt(void)
{
    return 1;/*����1����ǰ��֧�ָù��ܣ�0��ʾ�ɹ�*/
}


#define BSP_NVE_NAME_LENGTH          8       /*NV name maximum length*/
#define BSP_NVE_NV_DATA_SIZE        104     /*NV data maximum length*/

#define BSP_NV_READ                 1       /*NV read  operation*/
#define BSP_NV_WRITE                0       /*NV write operation*/

typedef struct nve_info_stru {
	BSP_U32 nv_operation;              /*0-write,1-read*/
	BSP_U32 nv_number;                 /*NV number you want to visit*/
	BSP_S8 nv_name[BSP_NVE_NAME_LENGTH];
	BSP_U32 valid_size;
	BSP_U8 nv_data[BSP_NVE_NV_DATA_SIZE];
}NVE_INFO_S;


BSP_S32 DRV_NVE_ACCESS(NVE_INFO_S *nve);


#ifdef __cplusplus
}
#endif

#endif  /*_DRV_NVIM_H_*/




