

#ifndef __OMSDLOG_H__
#define __OMSDLOG_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "omringbuffer.h"
#include "omprivate.h"

#pragma pack(4)

#if (VOS_OS_VER == VOS_LINUX)
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* �����ж�SD���Ƿ�Ϊ�¿� */
#define OM_SD_MAGIC_NUMBER            (0xAAAA5555)
#define OM_SD_OPPOSITE_MAGIC_NUMBER   (0x5555AAAA)

/* SD��ͷ������ */
#define OM_READ_SD_HEAD_LEN           (12)

/* SD������trace��buffer���� */
#define OM_SD_BUFFER_LEN              (64*1024)

/* SD����ÿ��cluster���ݴ�С����λΪKB */
#define OM_SD_CLUSTER_DATA_LEN        (64)

/* SD������trace��buffer��data�ֶ���ĳ��� */
#define OM_SD_BUFFER_INFO_LEN         (12 + OM_APP_MSG_EX_LEN + OM_READ_SD_HEAD_LEN)

/* SD������trace��buffer��data�ֶε���󳤶� */
#define OM_SD_BUFFER_MAX_DATA_LEN     (OM_SD_BUFFER_LEN - OM_SD_BUFFER_INFO_LEN)

/* SD����ÿ��block���ֽڴ�С */
#define OM_SD_BLOCK_SIZE              (512)

/* SD����ÿ��cluster������block�� */
#define OM_SD_BLOCK_NUM_ONE_CLUSTER   (128)

/* ����1KB����ֵ */
#define OM_SD_KB                      (1024)

/* SD���е�0��block����ͷ��������Ϣ���ʣ���ֽ� */
#define OM_SD_REMAIN_DATA_LEN         (492)

/* ��PC��һ�α�SD����cluster���ݵĸ��� */
#define OM_SD_IND_INTERVAL            (10)

/* дSD��ʱ�����ݳ��ȵ��ٽ糤��,����debug */
#define OM_SD_MAX_DATA_LENTH          (0x7FFFFFFF)

#define DRV_SDMMC_USB_SEC_READ(ulAddr, ulBlocks, pucBuffer)  (0)
/*        sd_transfer(g_pstScList, ulAddr, ulBlocks, OM_SD_BLOCK_SIZE, OM_READ_SD); \
 */
/*        VOS_MemCpy(pucBuffer, g_pucBuffer, ulBlocks*OM_SD_BLOCK_SIZE); \
 */

#define DRV_SDMMC_USB_SEC_WRITE(ulAddr, ulBlocks, pucBuffer) (0)
/*        VOS_MemCpy(g_pucBuffer, pucBuffer, ulBlocks*OM_SD_BLOCK_SIZE); \
 */
/*        sd_transfer(g_pstScList, ulAddr, ulBlocks, OM_SD_BLOCK_SIZE, OM_WRITE_SD); \
 */

#define DRV_SDMMC_GET_CAPACITY() sd_get_capacity()

#if (VOS_OS_VER == VOS_LINUX)
#define SD_FS_OPEN(filename,flags,mode)         sys_open(filename,flags,mode)
#define SD_FS_OPENDIR(dirname,flags,mode)       sys_open(dirname,flags,mode)
#define SD_FS_CLOSE(fd)                         sys_close(fd)
#define SD_FS_CLOSEDIR(dir_handle)              sys_close(dir_handle)
#define SD_FS_READ(fd,buffer,count)             sys_read(fd,buffer,count)
#define SD_FS_GETDENTS(fd, buf, count)          sys_getdents(fd, buf, count)
#define SD_FS_WRITE(fd,buffer,count)            sys_write(fd,buffer,count)
#define SD_FS_MKDIR(dirname,mode)               sys_mkdir(dirname,mode)
#define SD_FS_RMDIR(dirname)                    sys_rmdir(dirname )
#define SD_FS_RMFILE(filename)                  sys_unlink(filename)
#define SD_FS_LSEEK(fd,offset,origin)           sys_lseek(fd,offset,origin)
#define SD_FS_STAT(path,buf)                    vfs_stat(path,buf)
#define SD_FS_ACCESS(path,mode)                 sys_access(path,mode)
#define SD_FS_SYNC()                            sys_sync()
#define SD_FS_FILE_SYNC(fd)                     sys_fsync(fd)

#define SD_FS_GETFS()                           get_fs()
#define SD_FS_SETFS(fs)                         set_fs(fs)
#else
#define SD_FS_OPEN(filename,flags,mode)
#define SD_FS_OPENDIR(dirname,flags,mode)
#define SD_FS_CLOSE(fd)
#define SD_FS_CLOSEDIR(dir_handle)
#define SD_FS_READ(fd,buffer,count)
#define SD_FS_READDIR(dir_handle)
#define SD_FS_WRITE(fd,buffer,count)
#define SD_FS_MKDIR(dirname,mode)
#define SD_FS_RMDIR(dirname)
#define SD_FS_RMFILE(filename)
#define SD_FS_LSEEK(fd,offset,origin)
#define SD_FS_FTELL(fp)
#define SD_FS_STAT(path,pStat)
#define SD_FS_SYNC()
#define SD_FS_FILE_SYNC(fd)

#define SD_FS_GETFS()
#define SD_FS_SETFS(fs)
#endif

/*FLASH����Log�ļ�Ĭ�ϴ�С*/
#define OM_FLASH_DEFAULT_FILE_SIZE              (1024*1024)

/*�ļ�������*/
#define OM_SD_FILE_MODE                         (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

/*FALSH��󱣴�ռ�*/
#define OM_FLASH_MAX_SIZE                       (50)

#define OM_FLASH_DEFALUT_FILE_NUM               (20)

#define OM_SD_LOG_DIR_LEN                       (2048)

#define OM_SD_LOG_PATH_MAX_LENGTH               (128)

/* ��־�ļ�д������������ */
#define LOG_WRITE_MAX_COUNT                     (200)

#if (FEATURE_ON == FEATURE_COMPRESS_WRITE_LOG_FILE)
/* ѹ���ļ�ͷ��� */
#define UCMX_FILE_HEAD_TAG                      (0xAAAA)

/* ѹ���ļ����ݱ�� */
#define UCMX_DATA_TAG                           (0xA6A6A6A6)

/* ѹ����������󳤶�*/
#define OM_MAX_COMPRESS_DATA_LEN                (20*1024)

/* ����������,�յ���������������ݣ�ֱ��ѹ�� */
#define OM_MAX_PACK_DATA_LEN                    (10*1024)
#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
enum OM_SD_ERRNO
{
     OM_SD_OK                 = 0,
     OM_ERR_NOCARD,
     OM_ERR_NEWSDCARD,
     OM_ERR_VALIDPARA,
     OM_ERR_DRVAPI,
     OM_ERR_DATAERR,
     OM_ERR_MALLOCSPACE,
     OM_ERR_NOENOUGHDATA,
     OM_ERR_EMPTY,
     OM_SD_BUTT
};

typedef VOS_UINT32  OM_READSD_ERRNO_ENUM_UINT32;

/* ָʾSD�Ĳ�����ʽ */
enum
{
    OM_READ_SD = 0,
    OM_WRITE_SD,
};

#if (FEATURE_ON == FEATURE_COMPRESS_WRITE_LOG_FILE)
/* �ļ�ͷ��Ϣ������ö�� */
enum OM_LOG_HEAD_SEG_ENUM
{
    OM_LOG_HEAD_SEG_TIMER    = 0x01, /* ������ǰʱ�� */
    OM_LOG_HEAD_SEG_UE_INFO  = 0x02, /* UE��Ϣ */

    OM_LOG_HEAD_SEG_BUTT
};
typedef VOS_UINT8 OM_LOG_HEAD_SEG_ENUM_UINT8;


/* ѹ���㷨 */
enum OM_COMPRESS_TYPE_ENUM
{
    OM_COMPRESS_FASTLZ = 0x01, /* fastlz ѹ���㷨 */

    OM_COMPRESS_BUTT
};
typedef VOS_UINT16 OM_COMPRESS_TYPE_ENUM_UINT16;

/* ѹ���㷨�汾 */
enum OM_COMPRESS_VERSION_ENUM
{
    OM_COMPRESS_VERSION_1 = 0x01, /* fastlz ѹ���㷨 */

    OM_COMPRESS_VERSION_BUTT
};
typedef VOS_UINT16 OM_COMPRESS_VERSION_ENUM_UINT16;
#endif

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct
{
    VOS_UINT32             ulResult;   /*0: ok 1: error*/
    VOS_UINT32             ulReportCNum;   /*��Ҫ��ȡ��64KB��*/
    VOS_UINT32             ulHaveCNum;   /*ʵ���е�cluster��*/
}OM_APP_READ_SD_CNF_STRU;

/*���߲��������ô�ӡ����Ľṹ*/
typedef struct
{
    VOS_UINT32             ulTotalSize;
    VOS_UINT32             ulOffsetSize;

}APP_OM_READ_SD_REQ_STRU;

typedef struct
{
    VOS_UINT32  ulClusterId;
    VOS_UINT32  ulErrCode;                          /*0 ������ȷ�� 1 ����ʧ�ܡ���ǰulClusterIdΪ����ʱ����ֵΪ1*/
    VOS_UINT32  ulSn;                               /*64kB���ݰ����,��Ŵ�0��ʼ*/
    VOS_UINT8   aucDataContent[4];
}OM_APP_READ_SD_STRU;

typedef struct
{
    VOS_UINT32  ulMagicNum;                        /* �����ж��Ƿ�Ϊ�¿� */
    VOS_UINT32  ulOppositeMagicNum;                /* ulMagicNum��ȡ�� */
    VOS_UINT32  ulTotalCNum;                      /* SD����ClusterNum��һ��ClusterΪ64KB */
    VOS_UINT32  ulNextCid;                         /* ��¼��һ����д���Cluster ID */
    VOS_UINT32  ulLoopOutFlag;                     /* ��־SD�������Ƿ�����ת */
    VOS_UINT8   aucReserved[OM_SD_REMAIN_DATA_LEN];
}OM_SD_HEAD_STRU;

typedef struct
{
    VOS_UINT32 ulTotalNeedCNum;
    VOS_UINT32 ulCurNeedCNum;
    VOS_UINT32 ulStartCID;
}OM_SD_READ_INFO_STRU;

typedef struct
{
    VOS_UINT32  ulClusterId;                           /* ��ǰcluster ID */
    VOS_UINT32  ulDataLen;                             /* buffer�����ݳ��� */
    VOS_UINT8   aucReserved[OM_APP_MSG_EX_LEN + OM_READ_SD_HEAD_LEN]; /* �����ֶΣ����ڵ�������ʱ��� */
    VOS_UINT8   aucBuffer[OM_SD_BUFFER_MAX_DATA_LEN];  /* �������� */
    VOS_UINT32  ulOppositeClusterId;                   /* cluster IDȡ���������ж����������� */
}OM_SD_BUFFER_INNER_DATA_STRU;

typedef struct
{
    VOS_UINT32 ulTatalBlock;        /* ��¼д����ʱ������Block�� */
    VOS_UINT32 ulOverNum;           /* ��¼���ݳ��ȳ���OM_SD_MAX_DATA_LENTH �Ĵ���*/
    VOS_UINT32 ulDataLenth;         /* ulVoerNum��ʣ�µ����� */
    VOS_UINT32 ulRemainLenth;       /* ����buffer�У���δд��SD���� */
    VOS_UINT32 ulReadHeadErrLenth;  /*��ȡͷ���󣬶��������ݳ��� */
}OM_SD_DEBUG_INFO;

/*****************************************************************************
 �ṹ��    : OM_FLASH_CFG_INFO_STRU
 �ṹ˵��  : FLASH����TRACE�ļ���¼��Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulFileMinId;
    VOS_UINT32              ulFileMaxId;
}OM_FLASH_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : OM_FLASH_DEBUG_INFO
 �ṹ˵��  : FLASH����TRACE�ļ���Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_BOOL                bIsWritten;             /* Log�ļ���д��־ */
    VOS_INT                 lFileHandle;
    VOS_UINT32              ulRemainCount;
    VOS_UINT32              ulFileSize;             /* Log�ļ�ʵ�ʴ�С */
    VOS_UINT32              ulFileMaxSize;          /* Log�ļ���С���� */
    VOS_UINT32              ulSem;                  /* Log�ļ��ź������� */
    VOS_UINT32              ulErrLog;
    VOS_UINT32              ulWriteFailNum;
    VOS_CHAR                acName[64];             /* Log�ļ�ƹ���ļ��� */
}OM_FLASH_DEBUG_INFO_STRU;

#if (FEATURE_ON == FEATURE_COMPRESS_WRITE_LOG_FILE)

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#pragma pack(1)
/*****************************************************************************
 �ṹ��    : OM_UCMX_HEAD_INFO_STRU
 �ṹ˵��  : UCMX�ļ�ͷ,�����ֽڶ���
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFileTag;         /* �ļ���ǩ */
    VOS_UINT8                           ucFileVersion;     /* �ļ�����汾�� */
    VOS_UINT32                          ulSn;              /* �ļ�����ʱ���ļ���� */

    VOS_UINT8                           ucHeadSegNum;      /* �ļ�ͷ���� */

#if 0
    OM_LOG_HEAD_SEG_ENUM_UINT8          enSEGtype1;
    VOS_UINT8                           ucHeadLength1;     /* ��һ���ļ�ͷ�����ݳ��ȣ�����̶�Ϊ3 */
    OM_COMPRESS_TYPE_ENUM_UINT16        enSuport;          /* ѹ���㷢ö�� */
    OM_COMPRESS_VERSION_ENUM_UINT16     enCompressVersion; /* ѹ���㷨�汾�� */

    OM_LOG_HEAD_SEG_ENUM_UINT8          enSEGtype2;
    VOS_UINT8                           ucHeadLength2;     /* �ڶ����ļ�ͷ�����ݳ���, ����̶�Ϊ19 */
#endif

    OM_LOG_HEAD_SEG_ENUM_UINT8          enSEGType3;
    VOS_UINT8                           ucHeadLength3;     /* �������ļ�ͷ�����ݳ��ȣ�����Ϊ48 */
    VOS_UINT8                           aucImei[16];       /* imei�� */
    VOS_UINT8                           ucUEBoardType;     /* UE�汾���� */
    VOS_UINT8                           aucUEVersion[31];  /* UE�汾�� */

}OM_UCMX_HEAD_INFO_STRU;

/*****************************************************************************
 �ṹ��    : OM_UCMX_DATA_INFO_STRU
 �ṹ˵��  : UCMX�ļ����ݸ�ʽ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataTag;       /* ����У���ֶΣ��̶�Ϊ UCMX_DATA_TAG  */
    VOS_UINT32                          ulDataLength;    /* ����һ���ֽڿ�ʼ�����ݵĳ��ȡ� */
    VOS_UINT8                           aucData[OM_MAX_COMPRESS_DATA_LEN];       /* ���ݲ��� */
}OM_UCMX_DATA_INFO_STRU;


/*****************************************************************************
 �ṹ��    : OM_COMPRESS_DEBUG_OG_STRU
 �ṹ˵��  : ���ڼ�¼ѹ���ļ���ά�ɲ���Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRcvLen;
    VOS_UINT32                          ulRcvNum;
    VOS_UINT32                          ulCompressLen;
}OM_COMPRESS_DEBUG_OG_STRU;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#pragma pack(4)
#endif

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 OM_SDWriteCard(VOS_UINT8* pucData, VOS_UINT16 usLen);


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

#endif /* end of OmSDLog.h */

