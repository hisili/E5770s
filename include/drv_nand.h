

#ifndef __DRV_NAND_H__
#define __DRV_NAND_H__

#include "drv_comm.h"


/******************************************************************************
*
  ������:       BSP_S32 nand_get_bad_block (BSP_U32 *len, BSP_U32 **ppBadBlock)
  ��������:     ��ѯ����NAND������FLASH ����
  �������:     ��
  �������:     pNum       : ���ػ������
                ppBadBlock ������ָ�룬�������л����index����
  ����ֵ:       0    : ��ѯ�ɹ�
                ���� : ��ѯʧ��
*******************************************************************************/
static INLINE BSP_S32 NAND_GET_BAD_BLOCK(BSP_U32 *pNum, BSP_U32 **ppBadBlock)
{
    return 0;
}

/******************************************************************************
*
  ������:       BSP_VOID  nand_free_bad_block_mem(BSP_U32* pBadBlock)
  ��������:     ͨ��nand_get_bad_block�ӿ�����Ļ����ڴ��ɵ������룬��Э��ջ����
                �ýӿ��ͷš�
  �������:     pBadBlock
  �������:     ��
  ����ֵ:       BSP_VOID
*******************************************************************************/
static INLINE BSP_VOID NAND_FREE_BAD_BLOCK_MEM(BSP_U32* pBadBlock)
{
}

#define NAND_MFU_NAME_MAX_LEN    16
#define NAND_DEV_SPEC_MAX_LEN    32

typedef struct
{
    BSP_U32           MufId;                                         /* ����ID */
    BSP_U8      aucMufName[NAND_MFU_NAME_MAX_LEN];             /* ���������ַ��� */
    BSP_U32           DevId;                                         /* �豸ID */
    BSP_U8      aucDevSpec[NAND_DEV_SPEC_MAX_LEN];             /* �豸����ַ��� */
}NAND_DEV_INFO_S;

/******************************************************************************
*
  ������:       BSP_S32 nand_get_dev_info (NAND_DEV_INFO_S *pNandDevInfo)
  ��������:     ��ѯNAND�豸�����Ϣ����������ID���������ơ��豸ID���豸���
  �������:     ��
  �������:     pNandDevInfo    �洢NAND�豸�����Ϣ�Ľṹ��
  ����ֵ:       0    : ��ѯ�ɹ�
                ���� : ��ѯʧ��
*******************************************************************************/
static INLINE BSP_S32 NAND_GET_DEV_INFO(NAND_DEV_INFO_S *pNandDevInfo)
{
    return 0;
}

/************************************************************************
 * FUNCTION
 *       max_freeblock_size_get
 * DESCRIPTION
 *       get memory max free block size
 * INPUTS
 *       ��
 * OUTPUTS
 *       max free block size
 *************************************************************************/
static INLINE int DRV_GET_FREE_BLOCK_SIZE(void)
{
	return 0;
}

/********************************************************************************************************
 �� �� ��  : BSP_FS_GetDskspc
 ��������  : �õ��ļ�ϵͳ�ռ䡣
 �������  : path���ļ�ϵͳ·����
 �������  : DskSpc���ܿռ䡣
                           UsdSpc���ù��ռ䡣
                           VldSpc�����пռ䡣
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
********************************************************************************************************/
static INLINE int BSP_FS_GetDskspc(const char *path,unsigned int *DskSpc,unsigned int  *UsdSpc,  unsigned int *VldSpc)
{
	return 0;
}
#define DRV_FILE_GET_DISKSPACE(path,DskSpc,UsdSpc,VldSpc)    BSP_FS_GetDskspc(path,DskSpc,UsdSpc,VldSpc)


/*****************************************************************************
 �� �� ��  : BSP_MNTN_GetFlashSpec
 ��������  : Get flash infomation
 �������  : �ޡ�
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
*****************************************************************************/
static INLINE int BSP_MNTN_GetFlashSpec(unsigned char * pFlashInfo, unsigned int ulLength)
{
	return 0;
}
#define DRV_GET_FLASH_INFO(pFlashInfo, usLength)    BSP_MNTN_GetFlashSpec (pFlashInfo, usLength )
#endif

