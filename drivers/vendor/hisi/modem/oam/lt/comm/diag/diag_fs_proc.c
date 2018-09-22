


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
/*lint -save -e537*/
#include  "vos.h"
#include  "msp_errno.h"
#include  "diag_fs_proc.h"
#include  "diag_debug.h"
#include  "diag_common.h"
#include  "diag_cmd_id.h"
#include  "diag_cmd_param_plugin.h"
/*lint -restore*/

/*lint -save -e767 ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_FS_PROC_C
/*lint -restore +e767*/
/*lint -save -e718 -e746 -e628*/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
#if(VOS_OS_VER == VOS_LINUX)
const VOS_CHAR g_acDiagRootPath[] = "/";
const VOS_CHAR g_acDiagLockedRootPath[] = "/modem_log"; /* ����״̬�µĸ�Ŀ¼ */
const VOS_CHAR g_acDiagDumpDir[] = "/modem_log";
const VOS_CHAR g_acDiagLogDir[] = "/modem_log";
#else
const VOS_CHAR g_acDiagRootPath[] = "/yaffs0";
const VOS_CHAR g_acDiagDumpDir[] = "/yaffs2/exc";
const VOS_CHAR g_acDiagLogDir[] = "/yaffs2/log";
#endif

DIAG_FILE_INFO_STRU g_stDiagFileInfo = {DIAG_FILE_NULL, DIAG_FS_FOLDER_BUTT, VOS_NULL_PTR};

#if(VOS_OS_VER == VOS_LINUX)
extern VOS_BOOL g_bAtDataLocked;
#endif
/*****************************************************************************
  3 Function
*****************************************************************************/

#if(VOS_OS_VER == VOS_LINUX)
#define diag_fs_log()\
	printk("diag_fs_log: %d\n", __LINE__)
#else
#define diag_fs_log()
#endif
/*lint -save -e40 -e63*/ /* �ں˲����ӿڲ�ʶ��*/


VOS_VOID diag_FsClose(VOS_VOID)
{
#if(VOS_OS_VER == VOS_LINUX)
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);
#endif
    if (DIAG_FILE_NULL != g_stDiagFileInfo.lFile)
    {
#if(VOS_OS_VER == VOS_LINUX)
        DIAG_FS_CLOSE(g_stDiagFileInfo.lFile);
#else
        DIAG_FS_CLOSE((FILE *)g_stDiagFileInfo.lFile);
#endif
        g_stDiagFileInfo.lFile = DIAG_FILE_NULL;
    }
    
#if(VOS_OS_VER == VOS_LINUX)
    (VOS_VOID)DIAG_FS_FILE_SYNC(g_stDiagFileInfo.lFile);
    set_fs(old_fs);
#endif
}


#if(VOS_OS_VER == VOS_LINUX)
VOS_UINT32  diag_FsGetDirInfo(VOS_CHAR *pDirName, VOS_UINT32 *pulTotalNum)
{
    VOS_INT32 				dir_handle =0;
	VOS_INT32				nRead =0;
	VOS_INT32				nCount =0;
	VOS_UINT32				i=0;
	VOS_UINT8*				buf =NULL;

    DIAG_DIRENT_STRU        *pstTmpDirent;
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    /*��Ŀ¼*/
    if((dir_handle = DIAG_FS_OPENDIR((VOS_CHAR*)pDirName,DIAG_FS_RDONLY|DIAG_FS_DIRECTORY,0))< 0)
    {
        set_fs(old_fs);
		printk( "[%s]DIAG_FS_OPENDIR error!",__FUNCTION__);
        return VOS_ERR;
    }

	buf =(VOS_UINT8*)VOS_MemAlloc(diag_GetAgentPid(), DYNAMIC_MEM_PT,MSP_DF_DIR_BUF_LEN);
    if(NULL == buf)
    {
        printk( "[%s]Alloc mem error!",__FUNCTION__);
		DIAG_FS_CLOSEDIR(dir_handle);
		set_fs(old_fs);
        return VOS_ERR;
    }
	nRead = DIAG_FS_GETDENTS(dir_handle, (struct linux_dirent __user *)buf, MSP_DF_DIR_BUF_LEN);

	if(-1 == nRead)
	{
		printk("[%s]dents error,nRead=%d!\n",__FUNCTION__,(VOS_INT)nRead);
		*pulTotalNum =0;
		VOS_MemFree(diag_GetAgentPid(), buf);
		DIAG_FS_CLOSEDIR(dir_handle);
		set_fs(old_fs);
		return VOS_ERR;
	}

	if(0 == nRead)
	{
        /*lint -save -e717*/
		diag_printf("[%s]dents zero!\n",__FUNCTION__);
        /*lint -restore*/
		*pulTotalNum = 0;
		VOS_MemFree(diag_GetAgentPid(), buf);
		DIAG_FS_CLOSEDIR(dir_handle);
		set_fs(old_fs);
		return VOS_OK;
	}

	for(i=0; i<(VOS_UINT32)nRead;)
	{
	    pstTmpDirent = (DIAG_DIRENT_STRU*)(buf + i);
		i += pstTmpDirent->d_reclen;

		if((0 == VOS_StrCmp((char *) pstTmpDirent->d_name, "."))
			||(0 == VOS_StrCmp ((char *) pstTmpDirent->d_name, "..")))
        {
            /*lint -save -e717*/
        	diag_printf("diag_FsGetDirInfo:d_name=%S!\n",pstTmpDirent->d_name);
            /*lint -restore*/
            continue;
        }
#if 0
	    if (nCount>=FILENAME_NUM_MAX)
        {
        	DIAG_FS_CLOSEDIR(dir_handle);
	        set_fs(old_fs);
            return VOS_ERR;
        }
#endif
		nCount++;
	}

	*pulTotalNum = nCount;

     /*�ر�Ŀ¼*/
    if (DIAG_FS_ERROR == DIAG_FS_CLOSEDIR(dir_handle))
    {
        VOS_MemFree(diag_GetAgentPid(), buf);
    	printk("[%s]DIAG_FS_CLOSEDIR zero!\n",__FUNCTION__);
        set_fs(old_fs);
        return VOS_ERR;
    }

    VOS_MemFree(diag_GetAgentPid(), buf);

    set_fs(old_fs);
    return VOS_OK;
}


VOS_UINT32 diag_FsGetItemInfo(VOS_CHAR *pDirectory,DIAG_DIR_FILE_INFO_STRU *pstDirFileInfo)
{
    DIAG_DIRENT_STRU        *pstTmpDirent;
    DIAG_STAT_STRU           stStat;
    VOS_UINT8               ucDirName[MSP_DF_DIR_MAX_LEN];
    VOS_INT32 				dir_handle =0;
	VOS_INT32				nRead =0;
	VOS_INT32				i=0;
	VOS_UINT8*				buf =NULL;
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    /*�ٴδ�Ŀ¼*/
    if((dir_handle = DIAG_FS_OPENDIR(pDirectory,DIAG_FS_RDONLY|DIAG_FS_DIRECTORY,0))< 0)
    {
    	printk( "[%s]DIAG_FS_OPENDIR error!",__FUNCTION__);
        set_fs(old_fs);
        return VOS_ERR;

    }

	buf =(VOS_UINT8*)VOS_MemAlloc(diag_GetAgentPid(), DYNAMIC_MEM_PT,MSP_DF_DIR_BUF_LEN);
    if(NULL == buf)
    {
        printk( "[%s]Alloc mem error!",__FUNCTION__);
		DIAG_FS_CLOSEDIR(dir_handle);
		set_fs(old_fs);
        return VOS_ERR;
    }
	nRead = DIAG_FS_GETDENTS(dir_handle, (struct linux_dirent __user *)buf, MSP_DF_DIR_BUF_LEN);
	if((-1 == nRead)||(0 == nRead))
	{
		printk("[%s]dents error,nRead=%d!\n",__FUNCTION__,(VOS_INT)nRead);
		VOS_MemFree(diag_GetAgentPid(), buf);
		DIAG_FS_CLOSEDIR(dir_handle);
		set_fs(old_fs);
		return VOS_ERR;
	}

	/*��ѯ�ļ��н������ļ���������ȫ�ֱ���*/
	for(i=0; i<nRead; )
	{
		pstTmpDirent = (DIAG_DIRENT_STRU*)(buf + i);
		i += pstTmpDirent->d_reclen;

		if((0 == VOS_StrCmp((char *) pstTmpDirent->d_name, "."))
			||(0 == VOS_StrCmp ((char *) pstTmpDirent->d_name, "..")))
		{
            /*lint -save -e717*/
			diag_printf("[%s]:d_name=%S!\n",__FUNCTION__,pstTmpDirent->d_name);
            /*lint -restore*/
			continue;
		}

		VOS_StrCpy((VOS_CHAR *)ucDirName, pDirectory);
		strncat((VOS_CHAR *)ucDirName, "/",sizeof(VOS_CHAR));
        strncat((VOS_CHAR *)ucDirName, pstTmpDirent->d_name,strlen(pstTmpDirent->d_name));

        /*ͨ��stat��ȡ�ļ����ļ��е���Ϣ*/
        if (DIAG_FS_ERROR == DIAG_FS_STAT((VOS_CHAR *)ucDirName, &stStat))
        {
        	printk("DIAG_FS_STAT: error!\n");
            pstDirFileInfo->ulItemType = DIAG_FS_ITEM_FILE;
            pstDirFileInfo->st_size    = 0;
            pstDirFileInfo->st_mode    = 0;
            pstDirFileInfo->st_atime   = 0;
            pstDirFileInfo->st_mtime   = 0;
            pstDirFileInfo->st_ctime   = 0;
        }
        else
        {
            /*Ŀ¼*/

            if (0 != (DIAG_IF_DIR&stStat.mode))
            {

                pstDirFileInfo->ulItemType = DIAG_FS_ITEM_FOLDER;
            }
            /*�ļ�*/
            else
            {
                pstDirFileInfo->ulItemType = DIAG_FS_ITEM_FILE;
            }
            pstDirFileInfo->st_size   = (stStat.size & 0xFFFFFFFF);/* Ŀǰ�ļ���С���ᳬ��32λ��С */
            pstDirFileInfo->st_atime  = stStat.atime.tv_sec;
            pstDirFileInfo->st_mtime  = stStat.mtime.tv_sec;
            pstDirFileInfo->st_ctime  = stStat.ctime.tv_sec;
            pstDirFileInfo->st_mode   = stStat.mode;
        }

        /*�ļ����ļ�����*/
        VOS_MemSet(pstDirFileInfo->aucDirName, 0,DIAG_CMD_FILE_NAME_LEN);
        VOS_StrCpy(pstDirFileInfo->aucDirName, pstTmpDirent->d_name);

        pstDirFileInfo++;

 	}

    VOS_MemFree(diag_GetAgentPid(), buf);
    DIAG_FS_CLOSEDIR(dir_handle);
    set_fs(old_fs);

    return VOS_OK;

}
#else
VOS_UINT32  diag_FsGetDirInfo(VOS_CHAR *pDirName, VOS_UINT32 *pulTotalNum)
{
    DIAG_DIRENT_STRU	*pstTmpDirent = NULL;
    VOS_UINT32           ulTotalNum = 0;
    VOS_INT32 			 dir_handle =0;
    /*��Ŀ¼*/
    /*lint -save -e628 -e64*/
    dir_handle = (VOS_INT32)DIAG_FS_OPENDIR((VOS_CHAR*)pDirName,DIAG_FS_RDONLY|DIAG_FS_DIRECTORY,0);  /* [false alarm]:����Fortify */
    if(dir_handle < 0)
    {
        return VOS_ERR;
    }

    do
    {
        /*lint -save -e740*/
        pstTmpDirent = (DIAG_DIRENT_STRU *)DIAG_FS_READDIR((VOS_VOID*)dir_handle);
        /*lint -restore*/
        /*readdir�ķ���ֵΪ�գ�����Ŀ¼������*/
        if (VOS_NULL_PTR != pstTmpDirent)
        {
            ulTotalNum++;
        }
    }while (VOS_NULL_PTR != pstTmpDirent);

    *pulTotalNum = ulTotalNum;/* [false alarm]: ����Fortify ���� */

    /*�ر�Ŀ¼*/
    if (DIAG_FS_ERROR == DIAG_FS_CLOSEDIR((VOS_VOID*)dir_handle))
    {
        return VOS_ERR;
    }
    /*lint -restore*/
    return VOS_OK;
}

VOS_UINT32 diag_FsGetItemInfo(VOS_CHAR *pDirectory,DIAG_DIR_FILE_INFO_STRU *pstDirFileInfo)
{
#if 0
    /*lint -save -e958*/
    DIAG_DIRENT_STRU        *pstTmpDirent;
    DIAG_STAT_STRU           stStat;
    VOS_UINT8              *pDirName;
    VOS_UINT16              usDirLen;
    VOS_UINT32              ultemp_len = 0;
    VOS_INT32 				dir_handle =0;
    /*lint -restore*/
    /*�ٴδ�Ŀ¼*/
    /*lint -save -e64*/
    dir_handle = (VOS_INT32)DIAG_FS_OPENDIR(pDirectory,DIAG_FS_RDONLY|DIAG_FS_DIRECTORY,0);  /* [false alarm]:����Fortify */
    if(dir_handle < 0)
    {
        return VOS_ERR;
    }

    /*����ռ���������ļ����ļ��е�·������1����Ϊ������Ҫ���б��*/
    pDirName = (VOS_UINT8*)VOS_MemAlloc(diag_GetAgentPid(), DYNAMIC_MEM_PT,MSP_DF_DIR_MAX_LEN);
    if (VOS_NULL_PTR == pDirName)
    {
        DIAG_FS_CLOSEDIR((VOS_VOID*)dir_handle);
        return VOS_ERR;

    }

    /*��Ŀ¼·���������ļ�·����*/
    usDirLen = (VOS_UINT16)VOS_StrLen((VOS_CHAR*)pDirectory);
    VOS_MemCpy(pDirName, pDirectory, usDirLen);

    /*����Ŀ¼·���ǲ���б�ܽ����������ļ������ʱ����Ҫ���б��*/
    pDirName[usDirLen] = '/';
    usDirLen++;

    do
    {
        /*��������pstDirָ��·���е������ļ����ļ���*/
        pstTmpDirent = (DIAG_DIRENT_STRU *)DIAG_FS_READDIR((VOS_VOID*)dir_handle);
        /*lint -restore*/
        /*readdir�ķ���ֵΪ�գ�����Ŀ¼������*/
        if (VOS_NULL_PTR != pstTmpDirent)
        {
            /*�õ��ļ����ļ������ĳ���*/
            ultemp_len = (VOS_UINT16)VOS_StrLen(pstTmpDirent->d_name);  /* [false alarm]:����Fortify */

            /*�����ļ����ļ���·����Ҫ��'\0'��Ϊ������������Copyʱ�����ȼ�1*/
            VOS_MemCpy(pDirName + usDirLen,pstTmpDirent->d_name, ultemp_len + 1);

            /*ͨ��stat��ȡ�ļ����ļ��е���Ϣ*/
            if (DIAG_FS_ERROR == DIAG_FS_STAT((VOS_CHAR*)pDirName, &stStat))
            {
                pstDirFileInfo->ulItemType = DIAG_FS_ITEM_FILE;
                pstDirFileInfo->st_size    = 0;
                pstDirFileInfo->st_mode    = 0;
                pstDirFileInfo->st_atime   = 0;
                pstDirFileInfo->st_mtime   = 0;
                pstDirFileInfo->st_ctime   = 0;
            }
            else
            {
                /*Ŀ¼*/
                if (0 != (DIAG_IF_DIR&stStat.st_mode))
                {

                    pstDirFileInfo->ulItemType = DIAG_FS_ITEM_FOLDER;
                }
                /*�ļ�*/
                else
                {
                    pstDirFileInfo->ulItemType = DIAG_FS_ITEM_FILE;
                }
                pstDirFileInfo->st_size   = (stStat.st_size & 0xFFFFFFFF);/* Ŀǰ�ļ���С���ᳬ��32λ��С */
                pstDirFileInfo->st_atime  = (VOS_INT32)(stStat.st_atime);
                pstDirFileInfo->st_mtime  = (VOS_INT32)(stStat.st_mtime);
                pstDirFileInfo->st_ctime  = (VOS_INT32)(stStat.st_ctime);
                pstDirFileInfo->st_mode   = stStat.st_mode;
            }

            /*�ļ����ļ�����*/
            VOS_MemCpy(pstDirFileInfo->aucDirName, pstTmpDirent->d_name, ultemp_len +1);
            /* coverity[suspicious_pointer_arithmetic] */
            pstDirFileInfo = pstDirFileInfo + sizeof(DIAG_DIR_FILE_INFO_STRU );
    /*lint -save -e525*/
      }
    }while(VOS_NULL_PTR != pstTmpDirent);
    /*lint -restore*/
    /*lint -save -e50 -e64*/
    VOS_MemFree(diag_GetAgentPid(), pDirName);
    DIAG_FS_CLOSEDIR((VOS_VOID*)dir_handle);
    /*lint -restore*/
#endif
    return VOS_OK;

}

#endif

VOS_INT32 diag_FsOpen(const VOS_CHAR *pcFileName, VOS_INT lFlag)
{
#if((VOS_OS_VER == VOS_VXWORKS) || (VOS_OS_VER == VOS_RTOSCK))
//    VOS_CHAR    *pucMode;
#endif
    VOS_INT32  fp = 0;
#if(VOS_OS_VER == VOS_LINUX)
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);
#endif
#if((VOS_OS_VER == VOS_VXWORKS) || (VOS_OS_VER == VOS_RTOSCK))
#if 0
    switch(lFlag)
    {
        case (DIAG_FS_CREAT|DIAG_FS_APPEND|DIAG_FS_RDWR):
            pucMode = "ab+";
            break;

        case (DIAG_FS_CREAT|DIAG_FS_APPEND|DIAG_FS_WRONLY):
            pucMode = "ab";
            break;

        case (DIAG_FS_CREAT|DIAG_FS_TRUNC|DIAG_FS_RDWR):
            pucMode = "wb+";
            break;

        case (DIAG_FS_CREAT|DIAG_FS_TRUNC|DIAG_FS_WRONLY):
            pucMode = "wb";
            break;

        case DIAG_FS_RDWR:
            pucMode = "rb+";
            break;

        case DIAG_FS_RDONLY:
            pucMode = "rb";
            break;

        default:
            return DIAG_FILE_NULL;
    }
#endif
#endif
#if(VOS_OS_VER == VOS_LINUX)
    fp = DIAG_FS_OPEN(pcFileName, lFlag,0755);
#endif
#if((VOS_OS_VER == VOS_VXWORKS) || (VOS_OS_VER == VOS_RTOSCK))
//    fp = (VOS_INT32)DIAG_FS_OPEN(pcFileName, lFlag, pucMode);
#endif
	diag_fs_log();

#if(VOS_OS_VER == VOS_LINUX)
        set_fs(old_fs);
#endif

    return (VOS_INT32)fp;
}


VOS_UINT32 diag_FsQueryProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_FS_QUERY_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_QUERY_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

    pstFsReq = (DIAG_CMD_FS_QUERY_REQ*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    if (DIAG_FS_ROOT_FOLDER == pstFsReq->ulFolderType)
    {
#if(VOS_OS_VER == VOS_LINUX)
        /* ����״̬�£���Ŀ¼������ */
        if(g_bAtDataLocked)
        {
            stFsCnf.ulLength = VOS_StrLen((VOS_CHAR*)g_acDiagLockedRootPath);
            VOS_MemCpy(stFsCnf.aucDirPath,g_acDiagLockedRootPath, stFsCnf.ulLength);
        }
        else
        {
            stFsCnf.ulLength = VOS_StrLen((VOS_CHAR*)g_acDiagRootPath);
            VOS_MemCpy(stFsCnf.aucDirPath,g_acDiagRootPath, stFsCnf.ulLength);
        }
#else
            stFsCnf.ulLength = VOS_StrLen((VOS_CHAR*)g_acDiagRootPath);
            VOS_MemCpy(stFsCnf.aucDirPath,g_acDiagRootPath, stFsCnf.ulLength);
#endif
        g_stDiagFileInfo.ulFileType = DIAG_FS_ROOT_FOLDER;

    }
    else if (DIAG_FS_LOG_FOLDER == pstFsReq->ulFolderType)
    {
        stFsCnf.ulLength = VOS_StrLen((VOS_CHAR*)g_acDiagLogDir);
        VOS_MemCpy(stFsCnf.aucDirPath,g_acDiagLogDir, stFsCnf.ulLength);
        g_stDiagFileInfo.ulFileType = DIAG_FS_LOG_FOLDER;
    }
    /*���������ļ����ڵ�·��*/
    else if (DIAG_FS_DUMP_FOLDER == pstFsReq->ulFolderType)
    {
        stFsCnf.ulLength = VOS_StrLen((VOS_CHAR*)g_acDiagDumpDir);
        VOS_MemCpy(stFsCnf.aucDirPath, g_acDiagDumpDir, stFsCnf.ulLength);
        g_stDiagFileInfo.ulFileType = DIAG_FS_DUMP_FOLDER;
    }
    else
    {
        ret = ERR_MSP_FAILURE;
    }
    stFsCnf.ulRet = ret;

    /*����ظ���FW*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stFsCnf,ulCmdId,sizeof(DIAG_CMD_FS_QUERY_CNF));
    return ret;

}


VOS_UINT32 diag_FsScanProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_FS_SCAN_DIR_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_SCAN_DIR_CNF* pstFsCnf = NULL;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32              ulTotalNum;
    VOS_UINT32              ulTotalSize;

    pstFsReq = (DIAG_CMD_FS_SCAN_DIR_REQ*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

   /*�õ�Ŀ¼�ڣ��ļ����ļ��е��ܸ������ܵ����ֳ���*/
    if(VOS_OK != diag_FsGetDirInfo(pstFsReq->szDirectory,&ulTotalNum))
    {
        return VOS_ERR;
    }

    /*���㷵�ظ����߲���Ϣ���ĳ���*/
    ulTotalSize = (ulTotalNum* sizeof(DIAG_DIR_FILE_INFO_STRU)+ sizeof(DIAG_CMD_FS_SCAN_DIR_CNF));

    pstFsCnf = (DIAG_CMD_FS_SCAN_DIR_CNF*)VOS_MemAlloc(diag_GetAgentPid(), DYNAMIC_MEM_PT, ulTotalSize);
    if (VOS_NULL_PTR == pstFsCnf)
    {
        return VOS_ERR;
    }

    /*��ȡÿ���ļ����ļ��е���Ϣ*/
    /*lint -save -e539*/
	if(ulTotalNum>0)
	{
    	ret = diag_FsGetItemInfo(pstFsReq->szDirectory,pstFsCnf->stDirInfo);
	}
    /*lint -restore*/

    pstFsCnf->ulRet = ret;
    pstFsCnf->ulDirNum= ulTotalNum;
    pstFsCnf->ulDirInfoLen= ulTotalNum * sizeof(DIAG_DIR_FILE_INFO_STRU);

    /*����ظ���FW*/
    ret = diag_AgentCnfFun((VOS_UINT8*)pstFsCnf,ulCmdId,ulTotalSize);
    /*lint -save -e50*/
    VOS_MemFree(diag_GetAgentPid(), pstFsCnf);
    /*lint -restore*/
    return ret;

}


VOS_UINT32 diag_FsMkdirProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_FS_MAKE_DIR_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_MAKE_DIR_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
#if(VOS_OS_VER == VOS_LINUX)
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);
#endif

    pstFsReq = (DIAG_CMD_FS_MAKE_DIR_REQ*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    ret = (VOS_UINT32)DIAG_FS_MKDIR((VOS_CHAR*)pstFsReq->szDirectory,0755);

    stFsCnf.ulRet = ret;
#if(VOS_OS_VER == VOS_LINUX)
    set_fs(old_fs);
#endif

    /*����ظ���FW*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stFsCnf,ulCmdId,sizeof(DIAG_CMD_FS_MAKE_DIR_CNF));

    return ret;

}


VOS_UINT32 diag_FsOpenProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_FS_OPEN_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_OPEN_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

    pstFsReq = (DIAG_CMD_FS_OPEN_REQ*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    /*��֧�ֲ����ļ����������*/
    if (DIAG_FILE_NULL != g_stDiagFileInfo.lFile)
    {
        return VOS_ERR;
    }
    /*lint -save -e539*/
	diag_fs_log();
    /*lint -restore*/
    g_stDiagFileInfo.lFile = diag_FsOpen(pstFsReq->szDirectory, (VOS_INT)(pstFsReq->ulMode));

    if (g_stDiagFileInfo.lFile < 0)
    {
    	g_stDiagFileInfo.lFile = DIAG_FILE_NULL;
        ret = VOS_ERR;
    }
	else
	{
	    /*������ʱ��*/
	    g_stDiagFileInfo.hTimer = VOS_NULL_PTR;

	    ret = VOS_StartRelTimer(&g_stDiagFileInfo.hTimer, diag_GetAgentPid(), DIAG_CMD_FILE_OPS_TIME_OUT_LEN, 0, DIAG_TMR_FILE_OP_TIMEOUT_PARAM,VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
        if(ret != ERR_MSP_SUCCESS)
        {
            /*lint -save -e717*/
            diag_printf("VOS_StartRelTimer fail [%s]\n",__func__);
            /*lint -restore*/
        }
        diag_fs_log();
	}
    stFsCnf.ulRet = ret;

    /*����ظ���FW*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stFsCnf,ulCmdId,sizeof(DIAG_CMD_FS_OPEN_CNF));
	diag_fs_log();

    return ret;

}

VOS_UINT32 diag_FsImportProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_FS_IMPORT_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_IMPORT_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_INT32 lResult =0;
#if(VOS_OS_VER == VOS_LINUX)
    mm_segment_t old_fs;
#endif

    pstFsReq = (DIAG_CMD_FS_IMPORT_REQ*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    if (DIAG_FILE_NULL == g_stDiagFileInfo.lFile)
    {
        return ERR_MSP_FAILURE;
    }
    /*lint -save -e539*/
	diag_fs_log();
    /*lint -restore*/
    /*ֹͣ��ʱ��*/
    VOS_StopRelTimer(&g_stDiagFileInfo.hTimer);

    /*д�ļ���ϣ��ر��ļ�*/
    if (0 == pstFsReq->ulSize)
    {

		diag_fs_log();
        diag_FsClose();
        /*����ظ���FW*/
        stFsCnf.ulRet = ERR_MSP_SUCCESS;
        ret = diag_AgentCnfFun((VOS_UINT8*)&stFsCnf,ulCmdId,sizeof(DIAG_CMD_FS_IMPORT_CNF));
        return ret;
    }

#if(VOS_OS_VER == VOS_LINUX)
    old_fs = get_fs();
    set_fs(KERNEL_DS);
#endif

#if(VOS_OS_VER == VOS_LINUX)
    lResult = DIAG_FS_WRITE(g_stDiagFileInfo.lFile, pstFsReq->acContent, pstFsReq->ulSize);
#else
    lResult = DIAG_FS_WRITE((FILE *)g_stDiagFileInfo.lFile, pstFsReq->acContent, pstFsReq->ulSize);
#endif

	diag_fs_log();

#if(VOS_OS_VER == VOS_LINUX)
    set_fs(old_fs);
#endif

    if ((DIAG_FS_ERROR == lResult)||(lResult != (VOS_INT32)(pstFsReq->ulSize)))
    {
		diag_fs_log();
        /*lint -save -e717*/
		diag_printf("[%s]!,lResult=%d\n",__FUNCTION__,lResult);
        /*lint -restore*/
		diag_FsClose();
        return VOS_ERR;
    }

    /*������ʱ��*/
    ret = VOS_StartRelTimer(&g_stDiagFileInfo.hTimer, diag_GetAgentPid(),DIAG_CMD_FILE_OPS_TIME_OUT_LEN,0,DIAG_TMR_FILE_OP_TIMEOUT_PARAM,VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
    if(ret != ERR_MSP_SUCCESS)
    {
        /*lint -save -e717*/
        diag_printf("VOS_StartRelTimer fail [%s]\n",__func__);
        /*lint -restore*/
    }

    stFsCnf.ulRet = ret;

    /*����ظ���FW*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stFsCnf,ulCmdId,sizeof(DIAG_CMD_FS_IMPORT_CNF));
    return ret;

}


VOS_UINT32 diag_FsExportProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    //DIAG_CMD_FS_EXPORT_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_EXPORT_CNF *pstFsCnf = NULL;
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    VOS_UINT32 ulReadSize = 0;
#if(VOS_OS_VER == VOS_LINUX)
    mm_segment_t old_fs;
#endif


    if (DIAG_FILE_NULL == g_stDiagFileInfo.lFile)
    {

		diag_fs_log();
         return ERR_MSP_FAILURE;
    }

    /*ֹͣ��ʱ��*/
    VOS_StopRelTimer(&g_stDiagFileInfo.hTimer);
	diag_fs_log();

    pstFsCnf = (DIAG_CMD_FS_EXPORT_CNF*)VOS_MemAlloc(diag_GetAgentPid(), DYNAMIC_MEM_PT, sizeof(DIAG_CMD_FS_EXPORT_CNF)+DIAG_TRANSFER_BLOCK_MAX_SIZE);
    if (VOS_NULL_PTR == pstFsCnf)
    {

		diag_fs_log();
        diag_FsClose();
        return ERR_MSP_FAILURE;

    }

#if(VOS_OS_VER == VOS_LINUX)
    old_fs = get_fs();
    set_fs(KERNEL_DS);
#endif

#if(VOS_OS_VER == VOS_LINUX)
    ulReadSize = (VOS_UINT32)DIAG_FS_READ(g_stDiagFileInfo.lFile,(VOS_CHAR*)pstFsCnf + sizeof(DIAG_CMD_FS_EXPORT_CNF), DIAG_TRANSFER_BLOCK_MAX_SIZE);
#else
    ulReadSize = (VOS_UINT32)DIAG_FS_READ((FILE *)g_stDiagFileInfo.lFile,(VOS_CHAR*)pstFsCnf + sizeof(DIAG_CMD_FS_EXPORT_CNF), DIAG_TRANSFER_BLOCK_MAX_SIZE);
#endif

	diag_fs_log();

#if(VOS_OS_VER == VOS_LINUX)
    set_fs(old_fs);
#endif

    /*��ȡ�ļ����ִ���*/
    if (DIAG_FS_ERROR == (VOS_INT32)ulReadSize)
    {

		diag_fs_log();
        /*lint -save -e50*/
        VOS_MemFree(diag_GetAgentPid(), pstFsCnf);
        /*lint -restore*/
        diag_FsClose();
        return ERR_MSP_FAILURE;

    }

    /*�����Ѿ�û�����ݿ��Զ�ȡ���ļ�����ȫ������*/
    if (0 == ulReadSize)
    {

		diag_fs_log();
        diag_FsClose();
    }
    else
    {

		diag_fs_log();
        /*������ʱ��*/
        g_stDiagFileInfo.hTimer = VOS_NULL_PTR;
        ret = VOS_StartRelTimer(&g_stDiagFileInfo.hTimer, diag_GetAgentPid(), DIAG_CMD_FILE_OPS_TIME_OUT_LEN, 0, DIAG_TMR_FILE_OP_TIMEOUT_PARAM, VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
        if(ret != ERR_MSP_SUCCESS)
        {
            /*lint -save -e717*/
            diag_printf("VOS_StartRelTimer fail [%s]\n", __func__);
            /*lint -restore*/
        }

	}

    pstFsCnf->ulRet = ret;
    pstFsCnf->ulSize = ulReadSize;

    /*����ظ���FW*/
    ret = diag_AgentCnfFun((VOS_UINT8*)pstFsCnf,ulCmdId,sizeof(DIAG_CMD_FS_EXPORT_CNF)+ulReadSize);
    /*lint -save -e50*/
    VOS_MemFree(diag_GetAgentPid(), pstFsCnf);
    /*lint -restore*/
	diag_fs_log();
    return ret;

}


VOS_UINT32 diag_FsDeleteProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_FS_DELETE_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_DELETE_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
#if(VOS_OS_VER == VOS_LINUX)
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);
#endif

    pstFsReq = (DIAG_CMD_FS_DELETE_REQ*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    if (DIAG_FS_ITEM_FOLDER == pstFsReq->ulItemType)
    {
        ret = (VOS_UINT32)DIAG_FS_RMDIR(pstFsReq->szDirectory);
    }
    else if (DIAG_FS_ITEM_FILE == pstFsReq->ulItemType)
    {
        ret = (VOS_UINT32)DIAG_FS_RMFILE(pstFsReq->szDirectory);
    }

#if(VOS_OS_VER == VOS_LINUX)
    set_fs(old_fs);
#endif

    stFsCnf.ulRet = ret;

    /*����ظ���FW*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stFsCnf,ulCmdId,sizeof(DIAG_CMD_FS_DELETE_CNF));


    return ret;

}


VOS_UINT32 diag_FsSpaceProc(VOS_UINT8* pstReq,VOS_UINT32 ulCmdId)
{
    DIAG_CMD_FS_SPACE_REQ* pstFsReq = NULL;
    DIAG_CMD_FS_SPACE_CNF stFsCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
#if(VOS_OS_VER == VOS_LINUX)
   mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);
#endif
    pstFsReq = (DIAG_CMD_FS_SPACE_REQ*)(DIAG_OFFSET_HEAD_GET_DATA(pstReq));

    ret = (VOS_UINT32)DRV_FILE_GET_DISKSPACE((VOS_CHAR*)(pstFsReq->szDirectory),(VOS_UINT*)&stFsCnf.ulDiskSpace,
                    (VOS_UINT*)&stFsCnf.ulUsedSpace,(VOS_UINT*)&stFsCnf.ulValidSpace);

    stFsCnf.ulRet = ret;
#if(VOS_OS_VER == VOS_LINUX)
    set_fs(old_fs);
#endif

    /*����ظ���FW*/
    ret = diag_AgentCnfFun((VOS_UINT8*)&stFsCnf,ulCmdId,sizeof(DIAG_CMD_FS_SPACE_CNF));


    return ret;

}


VOS_UINT32 diag_FsProcEntry (VOS_UINT8* pstReq , VOS_UINT32 ulCmdId)
{
    VOS_UINT32 ret = ERR_MSP_SUCCESS;

    switch(MSP_STRU_ID_0_15_CMD_CATEGORY(ulCmdId))
    {
        case DIAG_CMD_FS_QUERY_DIR:
            ret = diag_FsQueryProc(pstReq,ulCmdId);
            break;
        case DIAG_CMD_FS_SCAN_DIR:
            ret = diag_FsScanProc(pstReq,ulCmdId);
            break;
        case DIAG_CMD_FS_MAKE_DIR:
            ret = diag_FsMkdirProc(pstReq,ulCmdId);
            break;
        case DIAG_CMD_FS_OPEN:
            ret = diag_FsOpenProc(pstReq,ulCmdId);
            break;
        case DIAG_CMD_FS_IMPORT:
            ret = diag_FsImportProc(pstReq,ulCmdId);
            break;
        case DIAG_CMD_FS_EXPORT:
            ret = diag_FsExportProc(pstReq,ulCmdId);
            break;
        case DIAG_CMD_FS_DELETE:
            ret = diag_FsDeleteProc(pstReq,ulCmdId);
            break;
        case DIAG_CMD_FS_SPACE:
            ret = diag_FsSpaceProc(pstReq,ulCmdId);
            break;
        default:
            break;

    }
    return ret;
}
/*lint -restore*/







#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

