

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C" {
  #endif
#endif


/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#if defined(__UT_CENTER__) || defined(_lint)
#include "LinuxStub.h"
#include "skbuff.h"
#else
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <linux/fs.h>
#include <sys/select.h>
#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "NetworkInquire.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/


#define THIS_FILE_ID PS_FILE_ID_NETWORK_INQUIRE

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/
/*lint -e960*/
extern unsigned long OM_Printf(char * pcformat, ... );
/*lint +e960*/
#ifdef __UT_CENTER__
extern int read(int fd, char *p, int len);
#endif
/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/
NETWORK_INQUIRE_ENTITY_STRU  g_stNwInquireEntity = {0};

/* network inquireӳ�俪�ر� */
NW_INQUERY_MASK_FUNC_STRU g_stNwInquireMaskOps[] =
{
    {
        NW_INQUIRE_IFCONFIG_ON_MASK,
        NW_InquireIfconfig
    },
    {
        NW_INQUIRE_ARP_ON_MASK,
        NW_InquireArp
    },
    {
        NW_INQUIRE_ROUTE_ON_MASK,
        NW_InquireRoute
    },
    {
        NW_INQUIRE_NETSTATE_ON_MASK,
        NW_InquireNetstate
    },
    {
        NW_INQUIRE_NAT_ON_MASK,
        NW_InquireNat
    }
};



void NW_ShellExc(char* cmd)
{
    FILE*           fp                  = NULL;
    int             lRet                = 0;
    char            buf[MAX_RST_BUF]    = {0};

    /*lint -e64*/
    fp = popen(cmd, "r");
    /*lint +e64*/

    if ( NULL != fp )
    {
        while ( (lRet = fread(buf, READ_SIZE_PER_TIME, MAX_RST_BUF - 1, fp)) != 0 )
        {
            buf[lRet + 1] = '\0';
            OM_Printf("%s", buf);
        };

        /*lint -e64*/
        pclose(fp);
        /*lint +e64*/
    }

}/* exc */


int NW_DeviceInit(int *fd)
{
    char aucDevPath[DEVICE_PATH_LEN] = {0};
    if ( NULL == fd )
    {
        printf("NW_InquireInit,error, fd is NULL_PTR!\n ");

        return NW_INQUIRE_ERROR;
    }

    /* ���ļ�(�����豸) */
    sprintf(aucDevPath, "/dev/%s", DEVICE_NAME);

    (*fd) = open(aucDevPath, O_RDWR);

    if ( -1 == *fd )
    {
        printf("NW_InquireInit,error, open file failed!\n ");

        close(*fd);

        return NW_INQUIRE_ERROR;
    }

    return NW_INQUIRE_OK;
}


void NW_DeviceRelease(int *fd)
{
    close(*fd);
}


int NW_InquireInit(int *fd)
{
    if ( NW_INQUIRE_ERROR == NW_DeviceInit(fd) )
    {
        return NW_INQUIRE_ERROR;
    }

    return NW_INQUIRE_OK;
}/* NW_InquireInit */


void NW_InquireUnInit(int *fd)
{
    NW_DeviceRelease(fd);
}


void NW_GetConfigPara(int fd)
{
    int readret;

    /* ��ȡ�ļ���������Ϣ ,������g_stNwInquireCfg�� */
    /*lint -e718 -e746*/
    readret = read(fd, (char *)&g_stNwInquireEntity.stInquireCfg, DEV_BUFF_LEN);
    /*lint +e718 +e746*/

    /* ʵ�ʶ�ȡ�ĳ��Ⱥ�Ҫ���ȡ�ĳ��Ȳ���ʱ���������δ��� */
    if ( (int)DEV_BUFF_LEN != readret )
    {
        printf("NW_GetConfigPara,error,read len error!\n");

        return;
    }

    /* ������ùر��ϱ�������ʱ��ͣ��������ֻ������һ�����ᳬʱ�Ķ�ʱ�� */
    if ( (0 == g_stNwInquireEntity.stInquireCfg.ulTimerLen) || (0 == g_stNwInquireEntity.stInquireCfg.ulOnOffMask) )
    {
        g_stNwInquireEntity.stInquireCfg.ulTimerLen = MAX_TIMER_LEN;
    }
}



void NW_ResetTimer(struct timeval  *timeout)
{
    timeout->tv_sec     = (int)g_stNwInquireEntity.stInquireCfg.ulTimerLen;
    timeout->tv_usec    = 0;
}



void NW_InquireProcess(int fd)
{
    int             ret = 0;
    fd_set          fds = {0};
    struct  timeval timeout = {MAX_TIMER_LEN, 0};

    FD_SET((unsigned int)fd, &fds);

#ifdef __UT_CENTER__
/*lint -e506 -e774*/
    if (1)
/*lint +e506 +e774*/
#else
    for(;;)
#endif
    {
        FD_ZERO(&fds);
        FD_SET((unsigned int)fd, &fds);

        /*lint -e64*/
        ret = select(fd + 1, &fds, NULL, NULL, &timeout);
        /*lint +e64*/
        switch ( ret )
        {
            case -1:
                printf("Error occur in NW_InquireProcess");

                break;
            case 0: /* ��ʱ����ʱ���� */
                /* �����ö�ʱ����Ϣ */
                NW_ResetTimer(&timeout);
                /* ��һ�β�ѯ */
                NW_DoInquire();

                break;
            default:
                /* ����ļ��ɶ� */
                if (FD_ISSET((unsigned int)fd, &fds))
                {
                    /* ��ȡ���ò��� */
                    NW_GetConfigPara(fd);
                    /* ��������ʱ����� */
                    NW_ResetTimer(&timeout);
                    /* ��һ�β�ѯ */
                    NW_DoInquire();
                }

                break;
        }
    }

}/* NW_GetConfigPara */



void NW_DoInquire(void)
{
    unsigned int i;
    u_int32_t    ulMask     = g_stNwInquireEntity.stInquireCfg.ulOnOffMask;

    if ( NW_INQUIRE_CFG_ALL_MASK < ulMask )
    {
        printf("NW_DoInquire,error,Mask is invalid!\n");

        return;
    }

    for ( i = 0; i < NW_INQUIRE_ARRAY_SIZE(g_stNwInquireMaskOps); i++ )
    {
        if ( g_stNwInquireMaskOps[i].ulMask == ( ulMask & g_stNwInquireMaskOps[i].ulMask ))
        {
            g_stNwInquireMaskOps[i].pInquireFunc();
        }
    }
}/* NW_DoInquire */



void NW_InquireIfconfig(void)
{
    EXC("ifconfig");

}/* NW_InquireIfconfig */


void NW_InquireArp(void)
{
    EXC("arp");

}/* NW_InquireArp */


void NW_InquireRoute(void)
{
    EXC("route");

}/* NW_InquireRoute */


void NW_InquireNetstate(void)
{
    /* ֻ��ѯtcp,udp,icmp��������Э�鲻��ѯ */
    EXC("netstat -t -u -w -n");

}/* NW_InquireNetstate */


void NW_InquireNat(void)
{
    EXC("cat /proc/net/ip_conntrack");

}/* NW_InquireNat */




#ifndef __UT_CENTER__
int main(void)
{
    int fd;
    int lWaitKoCnt = 0;

    /*===========================================*//* ģ���ʼ�� */
    /* ���豸�ļ���ʧ���򷵻� */
    /* �����ں˼�����Ҫһ��ʱ�䣬�û��������ں˳��򽻻���Ҫ�ȴ��ں˳���������֮�� */
    do
    {
        if ( NW_INQUIRE_OK != NW_InquireInit(&fd) )
        {
            lWaitKoCnt++;

            printf("NW_ProcessConfig,warning, NW_InquireInit fail times %d!\n ", lWaitKoCnt);
        }
        else
        {
            break;
        }

        if ( lWaitKoCnt >= MAX_WAIT_KO_READY_TIMES )
        {
            printf("NW_ProcessConfig,error, NW_InquireInit failed!\n ");

            return NW_INQUIRE_ERROR;
        }

        /*lint -e718 -e746*/
        sleep(WAIT_KO_READY_ONE_TIME_LEN);
        /*lint +e718 +e746*/
    /*lint -e506*/
    }while(1);
    /*lint -e506*/

    /* ��ȡ���õȴ������������һ���߳��� */
    NW_InquireProcess(fd);

    NW_InquireUnInit(&fd);

    return 0;
}
#endif


#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif


