

#ifndef __OMPRINTF_H__
#define __OMPRINTF_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "omringbuffer.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define OM_ALIGNMENT                  (0x03)

#define OM_PRINTF_OFFSET              (2*sizeof(VOS_UINT32))

/*֧��DRV��APP�����ģ����*/
#define OM_PRINTF_MODULE_MAX_NUM      (LOG_MAX_MODULE_ID_APP - LOG_MIN_MODULE_ID_ACPU_DRV + 1)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum OM_PRINTF_ERRNO
{
     OM_OK                 = 0,
     OM_ERR_NOBUF,
     OM_ERR_FAILTAKESEM,
     OM_ERR_FAILPUTDATA,
     OM_ERR_FAILTAKETASKSEM,
     OM_ERR_DATADESTROY,
     OM_ERR_WRITEFLASH,
     OM_ERR_NOOMSNDBUF,
     OM_ERR_MALLOC,
     OM_ERR_SENDTOOMBUF,
     OM_ERR_LOWLEVEL,
     OM_ERR_UNVALIDPARA,
     OM_ERR_RUNINIRQ,
     OM_BUTT
};

typedef VOS_UINT32  OM_PRINTF_ERRNO_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern   OM_RING_ID                          g_RlOmSndBufId;


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/* ��¼������buffer������ݶ�ʧ�Ķ�λ��Ϣ�ṹ�� */
typedef struct
{
    VOS_UINT32  ulOmPrintfRecvLen;                /* OM Printfת�������ַ��������ܳ��� */
    VOS_UINT32  ulOmPrintfNoPrintfBufferLostLen;  /* ����û��OM Printf buffer��ʧ�����ݳ��� */

    VOS_UINT16  usOmPrintfRecvCount;              /* OM Printfת�������ַ��������ܴ��� */
    VOS_UINT16  usOmPrintfNoPrintfBufferLostCount;/* ����û��OM Printf buffer��ʧ�����ݴ��� */
}OM_PRINTF_ERROR_RECORD_STRU;


typedef struct
{
    VOS_UINT32  ulModuleId;
    VOS_UINT32  ulPrintLev;
    VOS_UINT32  ulStrLen;
    VOS_CHAR    aucStr[4];
}OMPRITNF_MODULE_APP_STRU;


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern LOG_LEVEL_EN                     g_astOmPrintfOutPutLev[];

/*****************************************************************************
  10 ��������
*****************************************************************************/
/*lint -e960 */
extern unsigned long OM_Printf(char * pcformat, ... );
extern unsigned long OM_PrintfWithModule(unsigned long ulModuleId,
                                   unsigned long ulLevel, char * pcformat, ... );

/*lint +e960 */

extern unsigned long OM_PrintfSetModuleIdLev(unsigned long ulModuleId, unsigned long ulLev);

#if (VOS_OS_VER == VOS_LINUX)
EXPORT_SYMBOL(OM_Printf);
#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif /* end of OmPrintf.h */

