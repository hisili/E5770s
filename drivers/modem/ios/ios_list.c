/******************************************************************
* Copyright (C), 2005-2007, HISILICON Tech. Co., Ltd.             *
*                                                                 *
* File name: ios_list.c                                           *
*                                                                 *
* Description:                                                    *
*      driver debug module source file                            *
*                                                                 *
* Author:                                                         *
*                                                                 *
* Version: v0.1                                                   *
*                                                                 *
* Function List:                                                  *
*                                                                 *
* Date:                                                           *
*                                                                 *
* History:                                                        *
*                                                                 *
*******************************************************************/
/*lint -save -e537*/
#include <osl_types.h>
#include <osl_bio.h>

#include "bsp_shared_ddr.h"
#include "bsp_memmap.h"
#include "ios_list.h"
/*lint -restore */
#define IOS_FALSE   (0)
#define IOS_TRUE    (1)

#include "bsp_om.h"
#define  ios_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_IOS, "[ios]: <%s> <%d> "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  ios_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR,  BSP_MODU_IOS, "[ios]: "fmt, ##__VA_ARGS__))

#define VIRT_TO_PHY_ADREE(reg) (reg - HI_IOS_REGBASE_ADDR_VIRT + HI_IOS_REGBASE_ADDR)
#define PHY_TO_VIRT_ADREE(reg) (reg -  HI_IOS_REGBASE_ADDR+ HI_IOS_REGBASE_ADDR_VIRT)


typedef struct 
{
    unsigned int           addr;         /*register address*/
    unsigned int           value;        /*register value*/
}IOS_REG_DATA;

typedef struct
{
   IOS_REG_DATA*           start;      /*start address of ios data array*/
   IOS_REG_DATA*           cur;        /*current postion of ios data array*/
   IOS_REG_DATA*           end;        /*last address of ios data array*/
}IOS_POOL_CTRL;

/*����SHARE-MEMORY�ڴ�,�������fastboot�ܽ����õļĴ�����Ϣ*/
#define IOS_POOL_ADDR	((SHM_MEM_IOS_ADDR) + sizeof(IOS_POOL_CTRL))
#define IOS_POOL_SIZE   ((SHM_MEM_IOS_SIZE - sizeof(IOS_POOL_CTRL)) / sizeof(IOS_REG_DATA) * sizeof(IOS_REG_DATA))
static IOS_POOL_CTRL* const p_ios_ctrl = (IOS_POOL_CTRL *)((SHM_MEM_IOS_ADDR));

static void phy_virt_ctrl_convert(IOS_POOL_CTRL* pool_ctrl, IOS_POOL_CTRL* p_ctrl)
{
    pool_ctrl->start  = (IOS_REG_DATA*)SHD_DDR_P2V((char*)(p_ctrl->start));
    pool_ctrl->cur    = (IOS_REG_DATA*)SHD_DDR_P2V((char*)(p_ctrl->cur));
    pool_ctrl->end    = (IOS_REG_DATA*)SHD_DDR_P2V((char*)(p_ctrl->end));    
    

}

static void virt_phy_addr_convert(unsigned int *phy_addr, unsigned int addr)
{
    *phy_addr = (unsigned int)VIRT_TO_PHY_ADREE((char*)addr);


}

static void phy_virt_addr_convert(unsigned int *virt_addr, unsigned int addr)
{
    *virt_addr = (unsigned int)PHY_TO_VIRT_ADREE((char*)addr);


}


/*******************************************************************
 name       : add_list
 
 input      : IOS_POOL_CTRL* pScoreCtrl: phase handle
              const char* phaseName    : phase name string to store
              int param                : phase param to store       
              
 output      : N/A
 
 return      :  IOS_OK :     phase store successfully
                IOS_ERROR:    phase store failed
                
 history     :
 date        : 2011��02��21��
 creator     : 
 modified    : new create
 description.   : 
        
**********************************************************************/
static int add_list(IOS_POOL_CTRL* p_ctrl, unsigned int addr)
{   
    unsigned int value = 0;
    unsigned int phy_addr = 0;
    
    IOS_POOL_CTRL pool_ctrl = {0,0,0};
    IOS_REG_DATA* p_data = NULL;

    phy_virt_ctrl_convert(&pool_ctrl, p_ctrl);
    virt_phy_addr_convert(&phy_addr, addr);

    value = readl(addr);
    p_data = pool_ctrl.start;

    while(p_data != pool_ctrl.cur)
    {
        if(phy_addr == p_data->addr)
        {
			p_data->value = value;
            return IOS_TRUE;
        }
        ++p_data;
    }

    if(pool_ctrl.cur == pool_ctrl.end)
    {
        ios_print_error("the ios list is full.\n");
        return IOS_ERROR;
    }
    
    pool_ctrl.cur->addr = phy_addr;
    pool_ctrl.cur->value = readl(addr);
    ++(p_ctrl->cur);
    
   return IOS_OK;
}


int add_ios_list(unsigned int addr)
{
    IOS_POOL_CTRL* p_ctrl = p_ios_ctrl;

    return add_list(p_ctrl, addr);
}

/*�ӹ����ڴ��лָ�IOS���üĴ���*/
int ios_config_resume(void)
{
    unsigned int virt_addr = 0;
    
    IOS_REG_DATA *p_data = NULL;
    IOS_POOL_CTRL pool_ctrl = {0,0,0};
    IOS_POOL_CTRL *p_ctrl = p_ios_ctrl;

    phy_virt_ctrl_convert(&pool_ctrl, p_ctrl);    
    
    p_data = pool_ctrl.start;

    while(p_data != pool_ctrl.cur)
    {
        phy_virt_addr_convert(&virt_addr, p_data->addr);
        writel(p_data->value, virt_addr);
        ++p_data;
    }
    
    return IOS_OK;
}

static int ios_echo(IOS_POOL_CTRL* p_ctrl)
{   
    int i = 0;
    
    IOS_REG_DATA *p_data = NULL;
    IOS_POOL_CTRL pool_ctrl = {0,0,0};

    phy_virt_ctrl_convert(&pool_ctrl, p_ctrl);    
    
    p_data = pool_ctrl.start;

    while(p_data != pool_ctrl.cur)
    {
        ios_print_info("%d\ta=0x%x\tv=0x%x\n",++i, p_data->addr, p_data->value);
        ++p_data;
    }

    ios_print_info("%d left.\n", pool_ctrl.end - pool_ctrl.cur);

    return IOS_OK;
}

void ios_list_echo(void)
{
    IOS_POOL_CTRL* p_ctrl = p_ios_ctrl;
    
	ios_print_info("start...\n");
    
    ios_echo(p_ctrl);
	
	ios_print_info("end...\n");
    
}

void ios_addr_show(void)
{
    IOS_POOL_CTRL pool_ctrl = {0,0,0};

    IOS_POOL_CTRL* p_ctrl = p_ios_ctrl;

    phy_virt_ctrl_convert(&pool_ctrl, p_ctrl);
    
    ios_print_info("IOS_POOL_CTRL is 0x%x.\n", p_ctrl);
    
    ios_print_info("p_ios_ctrl->start is 0x%x.\n", p_ctrl->start);
    
    ios_print_info("p_ios_ctrl->cur is 0x%x.\n", p_ctrl->cur);
    
    ios_print_info("p_ios_ctrl->end is 0x%x.\n", p_ctrl->end);

    ios_print_info("virt p_ios_ctrl->start is 0x%x.\n", pool_ctrl.start);
    
    ios_print_info("virt p_ios_ctrl->cur is 0x%x.\n", pool_ctrl.cur);
    
    ios_print_info("virt p_ios_ctrl->end is 0x%x.\n", pool_ctrl.end); 
    
}

