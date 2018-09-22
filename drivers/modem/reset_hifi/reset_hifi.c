#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/kmod.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/sysctl.h>
#include <linux/uaccess.h>
#include <linux/delay.h>
#include <linux/huawei/rdr.h>
#include <product_config.h>
#include <drv_reset.h>
#include <bsp_reset.h>
#ifdef CONFIG_HIFI_RESET
#ifndef RESET_CBFUNC_PRIO_LEVEL_LOWT
#define RESET_CBFUNC_PRIO_LEVEL_LOWT    (0)
#endif

#ifndef RESET_CBFUNC_PRIO_LEVEL_HIGH
#define RESET_CBFUNC_PRIO_LEVEL_HIGH    (49)
#endif

#define RESET_CBFUN_IGNORE_NAME         "NONAME"
#define BSP_RESET_OK                    0
#define BSP_RESET_ERROR                 (-1)

typedef int (*pdrv_reset_cbfun)(DRV_RESET_CALLCBFUN_MOMENT eparam, int userdata);
/*Record information of callback functions*/
typedef struct
{
    char                name[9 + 1];
    int                         priolevel;
    pdrv_reset_cbfun    cbfun;
    int         userdata;
} sreset_mgr_callbackfunc;

/*Link list unit of managing all callback functions*/
typedef struct _sreset_mgr_LLI
{
    sreset_mgr_callbackfunc cbfuninfo;
    struct _sreset_mgr_LLI      *pnext;
} sreset_mgr_LLI;

/*Link used for hifi reset*/
sreset_mgr_LLI  *g_pmgr_hifireset_data = NULL;

/*****************************************************************************
 �� �� ��  : reset_link_insert
 ��������  : �����ݲ�������
 �������  : sreset_mgr_LLI *plink, ����ָ��
             sreset_mgr_LLI *punit��������Ľڵ�ָ��
 �������  : ��
 �� �� ֵ  : int
*****************************************************************************/
sreset_mgr_LLI * reset_link_insert(sreset_mgr_LLI *plink, sreset_mgr_LLI *punit)
{
    sreset_mgr_LLI    *phead = plink;
    sreset_mgr_LLI    *ppose = plink;
    sreset_mgr_LLI    *ptail = plink;

    if (NULL == plink || NULL == punit)
    {
        return NULL;
    }
    while (NULL != ppose)
    {
        /*�������ȼ����뵽������*/
        if (ppose->cbfuninfo.priolevel > punit->cbfuninfo.priolevel)
        {
            if (phead == ppose)
            {
                punit->pnext = ppose;
                phead = punit;
            }
            else
            {
                ptail->pnext = punit;
                punit->pnext = ppose;
            }
            break;
        }
        ptail = ppose;
        ppose = ppose->pnext;
    }
    if (NULL == ppose)
    {
        ptail->pnext = punit;
    }
    return phead;
}

/*****************************************************************************
 �� �� ��  : reset_do_regcbfunc
 ��������  : �����������ע��ص�����������Modem��λǰ��������ݡ�
 �������  :
         sreset_mgr_LLI *plink,��������ע�⣬����Ϊ��.
            const char *pname, ���ע�������
         pdrv_reset_cbfun cbfun,    ���ע��Ļص�����
         int userdata,�����˽������
         Int Priolevel, �ص������������ȼ� 0-49������0-9 ������
 �������  : ��
 �� �� ֵ  : int
*****************************************************************************/
sreset_mgr_LLI * reset_do_regcbfunc(sreset_mgr_LLI *plink, const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel)
{
    sreset_mgr_LLI  *phead = plink;
    sreset_mgr_LLI  *pmgr_unit = NULL;

    /*�ж�����Ƿ�Ϸ������Ϸ����ش���*/
    if (NULL == pname
        || NULL == pcbfun
        || (priolevel < RESET_CBFUNC_PRIO_LEVEL_LOWT || priolevel > RESET_CBFUNC_PRIO_LEVEL_HIGH))
    {
        printk(KERN_ERR "%s: fail in ccore reset regcb,fail, name 0x%x, cbfun 0x%x, prio %d\n", __FUNCTION__, \
                        (unsigned int)pname, (unsigned int)pcbfun, priolevel);
        return NULL;
    }

    /*����ռ�*/
    pmgr_unit = (sreset_mgr_LLI*)kmalloc(sizeof(sreset_mgr_LLI), GFP_KERNEL);
    if (NULL != pmgr_unit)
    {
        memset((void*)pmgr_unit, 0, (sizeof(sreset_mgr_LLI)));
        /*��ֵ*/
        strncpy(pmgr_unit->cbfuninfo.name, pname, 9);
        pmgr_unit->cbfuninfo.priolevel = priolevel;
        pmgr_unit->cbfuninfo.userdata = userdata;
        pmgr_unit->cbfuninfo.cbfun = pcbfun;
    }

    /*��һ�ε��øú���������Ϊ��*/
    if (NULL == phead)
    {
        phead = pmgr_unit;
    }
    else
    {
    /*�������ȼ���������*/
        phead = reset_link_insert(phead, pmgr_unit);
    }
    return phead;
}

/*****************************************************************************
 �� �� ��  : hifireset_regcbfunc
 ��������  : �����������ע��ص�����������HIFI��λǰ��������ݡ�
 �������  : const char *pname, ���ע�������
         pdrv_reset_cbfun cbfun,    ���ע��Ļص�����
         int userdata,�����˽������
         Int Priolevel, �ص������������ȼ� 0-49������0-9 ������
 �������  : ��
 �� �� ֵ  : int
*****************************************************************************/
int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel)
{
    g_pmgr_hifireset_data = reset_do_regcbfunc(g_pmgr_hifireset_data, pname, pcbfun, userdata, priolevel);
    printk(KERN_INFO "%s: %s registered a cbfun for hifi reset\n", __FUNCTION__, pname);
    return 0;
}

/*****************************************************************************
 �� �� ��  :  hifireset_doruncbfun
 ��������  : HIFI��λǰ����ûص������ĺ���������Ȧ���Ӷȳ��꣬���������װ����
 �������  : DRV_RESET_CALLCBFUN_MOMENT eparam, 0 ��ʾHIFI��λǰ�������ʾ��λ��

 �������  : ��
 �� �� ֵ  : int
        0, �ɹ�����0��ʧ��
*****************************************************************************/
int hifireset_doruncbfun (const char *pname, DRV_RESET_CALLCBFUN_MOMENT eparam)
{
    int  iresult = BSP_RESET_OK;

    sreset_mgr_LLI  *phead = g_pmgr_hifireset_data;
    BUG_ON(NULL == pname);
    /*���ж�ģ������,��˳��ִ��*/
    if (strcmp(pname, RESET_CBFUN_IGNORE_NAME) == 0)
    {
        while (NULL != phead)
        {
            if (NULL != phead->cbfuninfo.cbfun)
            {
                iresult = phead->cbfuninfo.cbfun(eparam, phead->cbfuninfo.userdata);
                if (BSP_RESET_OK != iresult)
                {
                    /*�������ʧ�ܣ���¼���������,����ֵ*/
                    printk(KERN_ERR "%s: fail to run cbfun of %s, at %d return %d\n", __FUNCTION__, phead->cbfuninfo.name, eparam, iresult);
                    break;
                }
                printk(KERN_INFO "%s: run %s cb function 0x%x\n", __FUNCTION__, phead->cbfuninfo.name, (unsigned int)phead->cbfuninfo.cbfun);
            }
            phead = phead->pnext;
        }
    }
    else/*��Ҫ�ж�ģ�����֣�ִ��ָ���Ļص�����*/
    {
        while (NULL != phead)
        {
            if (strcmp(pname, phead->cbfuninfo.name) == 0
                && NULL != phead->cbfuninfo.cbfun)
            {
                iresult  = phead->cbfuninfo.cbfun(eparam, phead->cbfuninfo.userdata);
                printk(KERN_INFO "%s: run %s cb function 0x%x\n", __FUNCTION__, phead->cbfuninfo.name, (unsigned int)phead->cbfuninfo.cbfun);
                break;
            }
            phead = phead->pnext;
        }
    }

    if (BSP_RESET_OK != iresult)
    {
        if (NULL != phead)
        {
            printk(KERN_ERR "%s: fail to run cbfun of %s, at %d, return %d\n", __FUNCTION__, phead->cbfuninfo.name, eparam ,iresult);

        }
        else
        {
            printk(KERN_ERR "%s: fail to run cbfun, but phead or pname is null\n", __FUNCTION__);
        }
    }
    return iresult;
}

/*****************************************************************************
 �� �� ��  :  hifireset _runcbfun
 ��������  : HIFI��λǰ����ûص������ĺ�����
 �������  : DRV_RESET_CALLCBFUN_MOMENT eparam, 0 ��ʾHIFI��λǰ�������ʾ��λ��

 �������  : ��
 �� �� ֵ  : int
        0, �ɹ�����0��ʧ��
*****************************************************************************/
int hifireset_runcbfun (DRV_RESET_CALLCBFUN_MOMENT eparam)
{
    int  iresult = 0;

    if (DRV_RESET_CALLCBFUN_RESET_BEFORE == eparam)
    {
        /*�����ص�������������NAS�Ļص�*/
        iresult = hifireset_doruncbfun("NAS_AT", eparam);
        if (BSP_RESET_OK != iresult)
        {
        /*�������ʧ�ܣ���¼���齨name, ����ֵ�����浽�ļ�*/
            goto return_error;
        }
    }
    else
    {
        /*�����ص������������ûص�����*/
        iresult = hifireset_doruncbfun(RESET_CBFUN_IGNORE_NAME, eparam);
        if (BSP_RESET_OK != iresult)
        {
            goto return_error;
        }
    }
    printk(KERN_INFO "%s: end of run cb functions for hifi reset at %d, %d\n", __FUNCTION__, eparam, iresult);
    return BSP_RESET_OK;
return_error:
    return BSP_RESET_ERROR;
}
#endif

