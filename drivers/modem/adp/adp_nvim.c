


/*lint -save -e537*/
#include "bsp_nvim.h"
#include "drv_comm.h"
#include "nv_comm.h"
#include "NVIM_ResumeId.h"
/*lint -restore +e537*/

/*lint -save -e958 -e438*/


#define  NV_RESULT_CODE            0xffff



BSP_U32 NVM_Flush(BSP_VOID)
{
    return bsp_nvm_flush() & NV_RESULT_CODE;
}



BSP_U32 NVM_UpgradeBackup(BSP_U32 uloption)
{
    return bsp_nvm_backup();
}


BSP_U32 NVM_UpgradeRestore(BSP_VOID)
{
    return bsp_nvm_revert();
}


BSP_U32 NVM_GetItemLength(BSP_U16 ulid, BSP_U32 * pusitemlength)
{
    BSP_U32 len = 0;
    BSP_U32 ret = 0;
    ret = bsp_nvm_get_len(ulid,&len);
    if(ret)
    {
        return NV_ERROR;
    }
    *pusitemlength = len;
    return 0;
}


BSP_U32 NVM_SetFactoryDefault(BSP_VOID)
{
    return bsp_nvm_revert_default() & NV_RESULT_CODE;
}

BSP_U32 NVM_BackUpFNV(BSP_VOID)
{
    return bsp_nvm_update_default();
}

BSP_U32 NVM_RevertFNV(BSP_VOID)
{
    return bsp_nvm_revert_default();
}


BSP_U32 NV_Flush(BSP_VOID)
{
    return bsp_nvm_flush() & NV_RESULT_CODE;
}

BSP_U32 NV_GetLength(BSP_U16 usID, BSP_U32 *pulLength)
{
    BSP_U32 len = 0;
    BSP_U32 ret = 0;
    ret = bsp_nvm_get_len(usID,&len);
    if(ret)
    {
        return NV_ERROR;
    }
    *pulLength = len;
    return 0;
}
BSP_U32 NV_Backup(BSP_VOID)
{
    return bsp_nvm_backup() & NV_RESULT_CODE;
}
BSP_U32 NV_BackupCheck(BSP_VOID)
{
    return 0;/*TO DO*/
}
BSP_U32 NV_RestoreAll(BSP_VOID)
{
    return bsp_nvm_revert() & NV_RESULT_CODE;
}
BSP_U32 NV_RestoreManufactureDefault(BSP_VOID)
{
    return bsp_nvm_revert_default() & NV_RESULT_CODE;
}
BSP_U32 NV_RestoreManufacture(BSP_VOID)
{
    return bsp_nvm_revert_manufacture() & NV_RESULT_CODE;
}
BSP_U32 NV_RestoreResult(BSP_VOID)
{
    BSP_U32 ret = NV_ERROR;
    BSP_U16 resume_flag = 0;

    ret = bsp_nvm_read(NV_ID_DRV_RESUME_FLAG,(BSP_U8*)&resume_flag,sizeof(BSP_U16)); /*to do*/
    if(ret)
    {
        return ret;
    }
    if(0 != resume_flag)
    {
        return NV_ERROR;
    }
    return 0;
}
BSP_U32 NV_QueryRestoreResult(BSP_VOID)
{
    BSP_U32 ret = NV_ERROR;
    BSP_U16 resume_flag = 0;

    ret = bsp_nvm_read(NV_ID_DRV_RESUME_FLAG,(BSP_U8*)&resume_flag,sizeof(BSP_U16)); /*to do*/
    if(ret)
    {
        return ret;
    }
    if(0 != resume_flag)
    {
        return NV_ERROR;
    }
    return 0;
}

BSP_U32 NV_Open_ALL_NV_File(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_Close_ALL_NV_File(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_GetResumeNvIdNum(BSP_U32 enNvItem)
{
    return bsp_nvm_getRevertNum( enNvItem);
}
BSP_U32 NV_GetResumeNvIdList(BSP_U32 enNvItem, BSP_U16 *pusNvList, BSP_U32 ulNvNum)
{
    if (NULL == pusNvList)
    {
        return NV_ERROR;
    }

    if (ulNvNum < NV_GetResumeNvIdNum(enNvItem))
    {
        return NV_ERROR;
    }

    if (NV_MANUFACTURE_ITEM == enNvItem)
    {
        memcpy(pusNvList, g_ausNvResumeManufactureIdList,NV_GetResumeNvIdNum(enNvItem)*((BSP_U32)sizeof(BSP_U16)));/*lint !e713*/
        return NV_OK;
    }

    if (NV_USER_ITEM == enNvItem)
    {
        memcpy(pusNvList, g_ausNvResumeUserIdList,NV_GetResumeNvIdNum(enNvItem)*((BSP_U32)sizeof(BSP_U16)));/*lint !e713*/
        return NV_OK;
    }

    if (NV_SECURE_ITEM == enNvItem)
    {
        memcpy(pusNvList, g_ausNvResumeSecureIdList,NV_GetResumeNvIdNum(enNvItem)*((BSP_U32)sizeof(BSP_U16)));/*lint !e713*/
        return NV_OK;
    }

    return NV_OK;
}



int DRV_NV_SEC_CHECK(char* path)
{
    return 0;
}
int DRV_COPY_NVUSE_TO_NVBACKUP(void)
{
    return 0;
}
int DRV_COPY_NVUPGRADE_TO_NVUSE(void)
{
    return 0;
}
BSP_U32 NV_Init(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_SpecialNvIdBackup(BSP_U16 usID,BSP_VOID *pItem,BSP_U32 ulLength)
{
    return 0;
}
BSP_U32 NV_GetNVIdListNum(BSP_VOID)
{
    return bsp_nvm_get_nv_num();
}
BSP_U32 NV_GetNVIdList(NV_LIST_INFO_STRU *pusNvIdList)
{
    if(pusNvIdList == NULL)
    {
        return NV_ERROR;
    }
    return bsp_nvm_get_nvidlist(pusNvIdList);
}

BSP_U32 NV_ReadEx(BSP_U16  enModemID, BSP_U16 usID,BSP_VOID *pItem,BSP_U32 ulLength)
{
    BSP_U32 card_id = 0;
    if(enModemID == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(enModemID == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else
        return BSP_ERR_NV_INVALID_PARAM;
    return bsp_nvm_dcread(card_id, usID,(BSP_U8*)pItem,ulLength);
}

BSP_U32 NV_WriteEx(BSP_U16  enModemID,BSP_U16  usID,BSP_VOID   *pItem, BSP_U32  ulLength)
{
    BSP_U32 card_id = 0;
    if(enModemID == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(enModemID == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else
        return BSP_ERR_NV_INVALID_PARAM;

    return bsp_nvm_dcwrite(card_id, usID,(BSP_U8*)pItem,ulLength);
}
BSP_U32 NV_ReadPartEx(BSP_U16 enModemID,BSP_U16 usID,BSP_U32 ulOffset,BSP_VOID *pItem,BSP_U32 ulLength)
{
    BSP_U32 card_id = 0;
    if(enModemID == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(enModemID == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else
        return BSP_ERR_NV_INVALID_PARAM;

    return bsp_nvm_dcreadpart(card_id,usID,ulOffset,(BSP_U8*)pItem,ulLength);
}
BSP_U32 NV_WritePartEx(BSP_U16   enModemID,BSP_U16   usID,BSP_U32  ulOffset,BSP_VOID *pItem,BSP_U32    ulLength)
{
    BSP_U32 card_id = 0;
    if(enModemID == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(enModemID == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else
        return BSP_ERR_NV_INVALID_PARAM;
    return bsp_nvm_dcwritepart(card_id,usID,ulOffset,(BSP_U8*)pItem,ulLength);
}
BSP_S32 DRV_NVE_ACCESS(NVE_INFO_S *nve)
{
    return 0;
}

/*lint -restore*/

