

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "pslog.h"
#include "RnicDemandDialFileIO.h"
#include "RnicCtx.h"
#include "RnicLog.h"
#include "RnicProcMsg.h"
#include "PsLib.h"

#if (VOS_OS_VER == VOS_LINUX)
#include <linux/namei.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/kallsyms.h>
#include <asm/uaccess.h>
#include <asm-generic/errno-base.h>
#include <linux/kernel.h>
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_RNIC_DEMAND_DIAL_FILE_IO_C
#define WLAN_DEV_NAME_LEN   64

/*Ŀǰ��¼4��*/
char g_wlan1_name[IFNAMSIZ] = {0};
char g_wlan2_name[IFNAMSIZ] = {0};
char g_wlan3_name[IFNAMSIZ] = {0};
char g_wlan4_name[IFNAMSIZ] = {0};

/*��¼eth0�Ƿ�Ϊlan�豸*/
char g_eth_is_lan[IFNAMSIZ] = {0};

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*��¼��ǰ�Ĳ���ģʽ*/
int g_atp_redirect_dailmode = 0;

#if (VOS_OS_VER == VOS_LINUX)

static const struct file_operations g_stOnDemandFileOps        =
{
    .owner      = THIS_MODULE,
    .write      = RNIC_WriteOnDemandFile,
    .read       = RNIC_ReadOnDemandFile,
};

static const struct file_operations g_stIdleTimerOutFileOps    =
{
    .owner      = THIS_MODULE,
    .write      = RNIC_WriteIdleTimerOutFile,
    .read       = RNIC_ReadIdleTimerOutFile,
};

static const struct file_operations g_stDialEventReportFileOps =
{
    .owner      = THIS_MODULE,
    .write      = RNIC_WriteDialEventReportFile,
    .read       = RNIC_ReadDialEventReportFile,
};

#else
static const struct file_operations g_stOnDemandFileOps ;
static const struct file_operations g_stIdleTimerOutFileOps ;
static const struct file_operations g_stDialEventReportFileOps;
#endif
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : RNIC_PraseWlanDevName
 ��������  : ����wlan���豸��
 �������  : char* namebuf, int len
 �������  : ��
 �� �� ֵ  : 
*****************************************************************************/
void RNIC_PraseWlanDevName(char* namebuf)
{
    char* file_name = NULL;
    char* file_list = NULL;
    char temp_buf[WLAN_DEV_NAME_LEN] = {0};
    PS_MEM_SET(g_wlan1_name, 0x00, IFNAMSIZ);
    PS_MEM_SET(g_wlan2_name, 0x00, IFNAMSIZ);
    PS_MEM_SET(g_wlan3_name, 0x00, IFNAMSIZ);
    PS_MEM_SET(g_wlan4_name, 0x00, IFNAMSIZ);
    if (NULL  == namebuf)
    {
        return;
    }

    VOS_sprintf(temp_buf, "%s", namebuf);
    file_list =  temp_buf;
    file_name = file_list;
    if (file_list = strstr(file_list, ","))
    {
        *file_list++ = 0;
         VOS_sprintf(g_wlan1_name, "%s", file_name);
    }
    else
    {
        VOS_sprintf(g_wlan1_name, "%s", file_name);
        return;
    }
    file_name = file_list;

    if (file_list = strstr(file_list, ","))
    {
        *file_list++ = 0;
        VOS_sprintf(g_wlan2_name, "%s", file_name);

    }
    else
    {
        VOS_sprintf(g_wlan2_name, "%s", file_name);
        return;
    }
    file_name = file_list;
    if (file_list = strstr(file_list, ","))
    {
        *file_list++ = 0;
        VOS_sprintf(g_wlan3_name, "%s", file_name);
    }
    else
    {
        VOS_sprintf(g_wlan3_name, "%s", file_name);
        return;
    }
    file_name = file_list;
    VOS_sprintf(g_wlan4_name, "%s", file_name);
    return;
}


VOS_UINT32 RNIC_TransferStringToInt(VOS_CHAR *pcString)
{
    VOS_UINT32                          ulStrLen;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRst;

    ulStrLen                            = 0;
    ulRst                               = 0;

    ulStrLen = VOS_StrLen(pcString);


    for ( i = 0; i < ulStrLen; i++ )
    {
        if ( (pcString[i] >= '0') && (pcString[i] <= '9') )
        {
            ulRst = (ulRst * 10) + (pcString[i] - '0');
        }
    }

    return ulRst;
}


ssize_t RNIC_ReadOnDemandFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_CHAR                            acModeTemp[RNIC_ONDEMAND_FILE_LEN];
    VOS_INT32                           lRlst;

    if (*ppos > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadOnDemandFile:ppos is err!");
        return 0;
    }

    PS_MEM_SET(acModeTemp, 0x00, RNIC_ONDEMAND_FILE_LEN);

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    VOS_sprintf((VOS_CHAR *)acModeTemp, "%d", pstDialMode->enDialMode);

    len             = PS_MIN(len, VOS_StrLen(acModeTemp));

    /*�����ں˿ռ����ݵ��û��ռ�����*/
    lRlst           = copy_to_user(buf,(VOS_VOID *)acModeTemp, len);

    if (lRlst < 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadOnDemandFile:copy_to_user fail!");
        return -EPERM;
    }

    *ppos += len;

    return len;
}



ssize_t RNIC_WriteOnDemandFile(
    struct file                        *file,
    const char __user                  *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_DIAL_MODE_STRU                 stDialMode;
    VOS_CHAR                            acModeTemp[RNIC_ONDEMAND_FILE_LEN];
    VOS_INT32                           lRlst;

    PS_MEM_SET(acModeTemp, 0x00, RNIC_ONDEMAND_FILE_LEN);

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    vos_printf("RNIC_WriteOnDemandFile:buf%x len %d \n", *buf, len);

    if (len >= RNIC_ONDEMAND_FILE_LEN)
    {
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_WriteOnDemandFile:len is!", len);
        return -ENOSPC;
    }


    /*�����û��ռ����ݵ��ں˿ռ�����*/
    lRlst = copy_from_user((VOS_VOID *)acModeTemp, (VOS_VOID *)buf, len);

    if (lRlst > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteOnDemandFile:copy_from_user ERR!");
        return -EFAULT;
    }

    acModeTemp[len] = '\0';

    vos_printf("RNIC_WriteOnDemandFile:acModeTemp %s len is %d\r\n", acModeTemp, len);

    stDialMode.enDialMode = RNIC_TransferStringToInt(acModeTemp);

    /* ���貦�� */
    if (AT_RNIC_DIAL_MODE_DEMAND_CONNECT == stDialMode.enDialMode)
    {
        RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);
    }
    else
    {
        RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
    }

    /* ���沦��ģʽ�������� */
    pstDialMode->enDialMode             = stDialMode.enDialMode;
    /*��������ģʽ��ȫ�ֱ�����*/
    g_atp_redirect_dailmode  = (int)pstDialMode->enDialMode;

    RNIC_SendDialInfoMsg(ID_RNIC_MNTN_DIAL_MODE_INFO);

    return len;
}


VOS_UINT32 RNIC_InitOnDemandFile(struct proc_dir_entry *pstParentFileDirEntry)
{
    struct proc_dir_entry              *pstOnDemandEntry;

    if (VOS_NULL_PTR == pstParentFileDirEntry)
    {
        /*����OnDemand�����ļ�*/
        pstOnDemandEntry                   = proc_create("dial/ondemand",
                                                        RNIC_VFILE_CRT_LEVEL,
                                                        pstParentFileDirEntry,
                                                        &g_stOnDemandFileOps);

        if (VOS_NULL_PTR == pstOnDemandEntry)
        {
            RNIC_WARNING_LOG(ACPU_PID_RNIC,
                            "RNIC_OnDemandVf_Init: proc_create Return NULL");

            return VOS_ERR;
        }
    }
    else
    {
        /*����OnDemand�����ļ�*/
        pstOnDemandEntry                   = proc_create("ondemand",
                                                        RNIC_VFILE_CRT_LEVEL,
                                                        pstParentFileDirEntry,
                                                        &g_stOnDemandFileOps);

        if (VOS_NULL_PTR == pstOnDemandEntry)
        {
            RNIC_WARNING_LOG(ACPU_PID_RNIC,
                            "RNIC_OnDemandVf_Init: proc_create Return NULL");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}


ssize_t RNIC_ReadIdleTimerOutFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_CHAR                            acIdleTimeTemp[RNIC_IDLETIMEROUT_FILE_LEN];
    VOS_INT32                           lRlst;

    if (*ppos > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadIdleTimerOutFile:ppos ERR!");
        return 0;
    }

    PS_MEM_SET(acIdleTimeTemp, 0x00, RNIC_IDLETIMEROUT_FILE_LEN);


    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    VOS_sprintf(acIdleTimeTemp, "%d", pstDialMode->ulIdleTime);

    len             = PS_MIN(len, VOS_StrLen(acIdleTimeTemp));

    /*�����ں˿ռ����ݵ��û��ռ�����*/
    lRlst          = copy_to_user(buf,(VOS_VOID *)acIdleTimeTemp, len);

    if (lRlst < 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadIdleTimerOutFile:copy_to_user ERR!");
        return -EPERM;
    }

    *ppos += len;

    return len;
}



ssize_t RNIC_WriteIdleTimerOutFile(
    struct file                        *file,
    const char __user                  *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_DIAL_MODE_STRU                 stDialMode;
    VOS_CHAR                            acIdleTimeTemp[RNIC_IDLETIMEROUT_FILE_LEN];
    VOS_INT32                           lRlst;

    PS_MEM_SET(acIdleTimeTemp, 0x00, RNIC_IDLETIMEROUT_FILE_LEN);

    if (len >= RNIC_IDLETIMEROUT_FILE_LEN)
    {
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_WriteIdleTimerOutFile:len is!", len);
        return -ENOSPC;
    }

    /*�����û��ռ����ݵ��ں˿ռ�����*/
    lRlst = copy_from_user((VOS_VOID *)acIdleTimeTemp, (VOS_VOID *)buf, len);

    if (lRlst > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteIdleTimerOutFile:copy_from_user ERR!");
        return -EFAULT;
    }

    acIdleTimeTemp[len]= '\0';



    stDialMode.ulIdleTime = RNIC_TransferStringToInt(acIdleTimeTemp);


    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    if (AT_RNIC_DIAL_MODE_DEMAND_DISCONNECT == pstDialMode->enDialMode)
    {

        /* PDP��������ϴ����õ�ʱ����һ�£���Ҫ�������ŶϿ���ʱ�� */
        if ( pstDialMode->ulIdleTime != stDialMode.ulIdleTime)
        {
            RNIC_StopTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT);
            RNIC_StartTimer(TI_RNIC_DEMAND_DIAL_DISCONNECT, TI_RNIC_DEMAND_DIAL_DISCONNECT_LEN);
        }
    }

    pstDialMode->ulIdleTime             = stDialMode.ulIdleTime;


    RNIC_SendDialInfoMsg(ID_RNIC_MNTN_IDLE_TIMEOUT_INFO);

    return len;
}


VOS_UINT32 RNIC_InitIdleTimerOutFile(struct proc_dir_entry *pstParentFileDirEntry)
{
    struct proc_dir_entry              *pstIdleTimeOutEntry;

    if (VOS_NULL_PTR == pstParentFileDirEntry )
    {
        /*����IdleTimeOut�����ļ�*/
        pstIdleTimeOutEntry                 = proc_create("dial/idle_timeout",
                                                         RNIC_VFILE_CRT_LEVEL,
                                                         pstParentFileDirEntry,
                                                         &g_stIdleTimerOutFileOps);

        if (VOS_NULL_PTR == pstIdleTimeOutEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitIdleTimerOutFile:pstIdleTimeOutEntry is null!");

            return VOS_ERR;
        }
    }
    else
    {
        /*����IdleTimeOut�����ļ�*/
        pstIdleTimeOutEntry                 = proc_create("idle_timeout",
                                                         RNIC_VFILE_CRT_LEVEL,
                                                         pstParentFileDirEntry,
                                                         &g_stIdleTimerOutFileOps);

        if (VOS_NULL_PTR == pstIdleTimeOutEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitIdleTimerOutFile:pstIdleTimeOutEntry is null!");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}


ssize_t RNIC_ReadDialEventReportFile(
    struct file                        *file,
    char __user                        *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    VOS_CHAR                            acDialEventTemp[RNIC_EVENTFLAG_FILE_LEN];
    VOS_INT32                           lRlst;

    if (*ppos > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadDialEventReportFile:ppos err!");
        return 0;
    }

    PS_MEM_SET(acDialEventTemp, 0x00, RNIC_EVENTFLAG_FILE_LEN);


    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    VOS_sprintf(acDialEventTemp, "%d", pstDialMode->enEventReportFlag);


    len             = PS_MIN(len, VOS_StrLen(acDialEventTemp));

    /*�����ں˿ռ����ݵ��û��ռ�����*/
    lRlst          = copy_to_user(buf, (VOS_VOID *)acDialEventTemp, len);


    if (lRlst < 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_ReadDialEventReportFile:copy_to_user err!");
        return -EPERM;
    }

    *ppos += len;

    return len;
}



ssize_t RNIC_WriteDialEventReportFile(
    struct file                        *file,
    const char __user                  *buf,
    size_t                              len,
    loff_t                             *ppos
)
{
    RNIC_DIAL_MODE_STRU                *pstDialMode;
    RNIC_DIAL_MODE_STRU                 stDialMode;
    VOS_CHAR                            acDialEventTemp[RNIC_EVENTFLAG_FILE_LEN];
    VOS_INT32                           lRlst;

    PS_MEM_SET(acDialEventTemp, 0x00, RNIC_EVENTFLAG_FILE_LEN);

    if (len >= RNIC_EVENTFLAG_FILE_LEN)
    {
        RNIC_ERROR_LOG1(ACPU_PID_RNIC, "RNIC_WriteDialEventReportFile:len is!",len);
        return -ENOSPC;
    }

    /*�����û��ռ����ݵ��ں˿ռ�����*/
    lRlst = copy_from_user((VOS_VOID *)acDialEventTemp, (VOS_VOID *)buf, len);

    if (lRlst > 0)
    {
        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_WriteDialEventReportFile:copy_from_user ERR!");
        return -EFAULT;
    }

    acDialEventTemp[len] = '\0';

    vos_printf("RNIC_WriteDialEventReportFile:acDialEventTemp %s len is %d\r\n", acDialEventTemp, len);

    stDialMode.enEventReportFlag    = RNIC_TransferStringToInt(acDialEventTemp);

    /* ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ */
    pstDialMode                         = RNIC_GetDialModeAddr();

    /* ���沦��ģʽ���������� */
    pstDialMode->enEventReportFlag      = stDialMode.enEventReportFlag;

    RNIC_SendDialInfoMsg(ID_RNIC_MNTN_EVENT_REPORT_INFO);

    return len;
}

VOS_UINT32 RNIC_InitDialEventReportFile(struct proc_dir_entry *pstParentFileDirEntry)
{
    struct proc_dir_entry              *pstDialEventReportEntry;

    if (VOS_NULL_PTR == pstParentFileDirEntry)
    {
        /*����dial_event_report�����ļ�*/
        pstDialEventReportEntry             = proc_create("dial/dial_event_report",
                                                          RNIC_VFILE_CRT_LEVEL,
                                                          pstParentFileDirEntry,
                                                          &g_stDialEventReportFileOps);

        if (VOS_NULL_PTR == pstDialEventReportEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:pstDialEventReportEntry is null!");

            return VOS_ERR;
        }

    }
    else
    {

        /*����dial_event_report�����ļ�*/
        pstDialEventReportEntry             = proc_create("dial_event_report",
                                                          RNIC_VFILE_CRT_LEVEL,
                                                          pstParentFileDirEntry,
                                                          &g_stDialEventReportFileOps);

        if (VOS_NULL_PTR == pstDialEventReportEntry)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:pstDialEventReportEntry is null!");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_UINT32 RNIC_InitDemandDialFile(VOS_VOID)
{
    struct proc_dir_entry              *stProcDemandDialDir;
    VOS_UINT32                          ulRlst;
    struct path                         path;
    int                                 error = 0;

    error = kern_path("/proc/dial", LOOKUP_FOLLOW, &path);
    if (error)
    {

        stProcDemandDialDir = proc_mkdir("dial", VOS_NULL_PTR);
        if (VOS_NULL_PTR == stProcDemandDialDir)
        {
            RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDemandDialFile:proc_mkdir Fail!");
            return VOS_ERR;
        }
    }
    else
    {
        stProcDemandDialDir = VOS_NULL_PTR;
        RNIC_NORMAL_LOG(ACPU_PID_RNIC, "RNIC_InitDemandDialFile:kern_path proc/dial is exist!");
    }

    ulRlst                              = RNIC_InitOnDemandFile(stProcDemandDialDir);

    if (VOS_ERR == ulRlst)
    {

        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:RNIC_InitOnDemandFile err!");

        return VOS_ERR;
    }

    ulRlst                              = RNIC_InitIdleTimerOutFile(stProcDemandDialDir);

    if (VOS_ERR == ulRlst)
    {


        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:RNIC_InitIdleTimerOutFile err!");

        return VOS_ERR;
    }

    ulRlst                              = RNIC_InitDialEventReportFile(stProcDemandDialDir);

    if (VOS_ERR == ulRlst)
    {

        RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialEventReportFile:RNIC_InitDialEventReportFile err!");

        return VOS_ERR;
    }

    return VOS_OK;
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
