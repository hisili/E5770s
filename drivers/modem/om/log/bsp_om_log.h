

#ifndef __BSP_OM_LOG_H__
#define __BSP_OM_LOG_H__


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "bsp_om.h"
#include "bsp_om_api.h"
#include "bsp_om_server.h"
#include "drv_comm.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define  BSP_PRINT_BUF_LEN  256

#define  BSP_DIAG_IND_DATA_MAX_LEN         (4096)


/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  2 �ṹ��
*****************************************************************************/

typedef struct
{
    u32     mod_id;     /* ��ӡ��Ϣ���ڵ�ģ��ID*/
    u32     level;      /* �������*/
    u32     log_sn;     /* IND���*/
    char     text[0];    /* ���д�ӡ�ı����ݣ����ܰ����ļ����к�,��'\0'��β */
} bsp_trace_txt_s;

typedef struct
{
    bsp_socp_head_s      socp_header;
    bsp_om_head_s        om_header;
    bsp_trace_txt_s         print_stu;
} bsp_trace_s;

typedef struct
{
    u32                     addr;
    u16                     is_edle;
    u16                     is_valible;
}bsp_log_node_ctrl_s;

typedef struct
{
    u32                     start_ptr;      /*  ��ʼ��ַ*/
    u32                     start_phy_ptr;
    u32                     node_num;    /* buf ������*/
    u32                     buys_node_num;   /* ��ռ�õĽڵ���Ŀ*/
    u32                     valible_node_num;   /* д�����ݵĽڵ���Ŀ*/
    u32                     init_state;
    bsp_log_node_ctrl_s  stnode[BSP_OM_LOG_BUF_SIZE/BSP_PRINT_BUF_LEN];
}bsp_om_log_buf_ctrl_s;


u32 bsp_log_module_cfg_get(bsp_module_e mod_id);


/*****************************************************************************
  5 �����붨��
*****************************************************************************/
#define BSP_ERR_LOG_BASE                (int)(0x80000000 | (BSP_DEF_ERR(BSP_MODU_LOG, 0)))
#define BSP_ERR_LOG_INVALID_MODULE      (BSP_ERR_LOG_BASE + 0x1)
#define BSP_ERR_LOG_INVALID_LEVEL       (BSP_ERR_LOG_BASE + 0x2)
#define BSP_ERR_LOG_INVALID_PARAM       (BSP_ERR_LOG_BASE + 0x3)
#define BSP_ERR_LOG_NO_BUF              (BSP_ERR_LOG_BASE + 0x4)
#define BSP_ERR_LOG_SOCP_ERR            (BSP_ERR_LOG_BASE + 0x5)


#endif

