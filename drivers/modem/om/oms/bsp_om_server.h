

#ifndef __BSP_OM_SERVER_H__
#define __BSP_OM_SERVER_H__


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "bsp_om.h"
#include "drv_socp.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BSP_OM_SOCP_CHAN_INIT_SUCC      1
#define BSP_OM_SOCP_CHAN_INIT_FAIL        0

#define BSP_OM_BUF_INIT_SUCC        1
#define BSP_OM_BUF_INIT_FAIL          0

#define BSP_OM_ACPU_CODER_SRC_CHAN    SOCP_CODER_SRC_HDLCAT_CNF
#define BSP_OM_CCPU_CODER_SRC_CHAN    SOCP_CODER_SRC_RFU

#define BSP_OM_CODE_SRC_BD_NUM         (4096)        /* ��ʽͨ��BD�ĸ��� */
#define BSP_OM_CODE_SRC_RD_NUM         (4096)        /* ��ʽͨ��RD�ĸ��� */
#define BSP_OM_LOG_BUF_SIZE                  (64*1024)       /* BSP OM����LOG����SOCP����Դ�˵Ļ����С*/
#define BSP_OM_SOCP_BUF_SIZE                (96*1024)        /* BSP OM������������SOCP����Դ�˵Ļ����С*/

#define BSP_OM_CODER_SRC_BDSIZE        (sizeof(SOCP_BD_DATA_STRU)*BSP_OM_CODE_SRC_BD_NUM)   /* ��ʽͨ����BD�ռ� */
#define BSP_OM_CODER_SRC_RDSIZE        (sizeof(SOCP_RD_DATA_STRU)*BSP_OM_CODE_SRC_RD_NUM)   /* ��ʽͨ����RD�ռ� */

#define OM_MALLOC_MAX_SIZE          0x100000
#define OM_MALLOC_MAX_INDEX       8           /*page_size Ϊ4K*/
#define MEMORY_PAGE_SIZE               0x1000

#define PACKET_BSP_SOCP_HEAD(head_buf)  \
{\
   ( (bsp_socp_head_s *)head_buf)->service_id = BSP_SOCP_SID_DIAG_SERVER;\
    ( (bsp_socp_head_s *)head_buf)->s_service_id =(BSP_SOCP_HIGH4BIT_SSID_ACPU << 4);\
    ( (bsp_socp_head_s *)head_buf)->service_session_id = BSP_SOCP_SERVER_SESSION_ID;\
   ( (bsp_socp_head_s *)head_buf)->msg_type = BSP_SOCP_MSG_TYPE_IND;\
    bsp_bbp_getcurtime((u64 *)((bsp_socp_head_s *)head_buf)->time_stamp);\
}

/*****************************************************************************
  2 �ṹ��
*****************************************************************************/

typedef struct
{
    u32                     init_state;         /* ͨ����ʼ��״̬����ʼ�����Զ��޸� */
    SOCP_CODER_SRC_ENUM_U32     en_src_chan_id;     /* ����Դͨ��ID���̶����� */
    SOCP_CODER_DST_ENUM_U32     en_dst_chan_id;     /* ����Ŀ��ͨ��ID */
    SOCP_DATA_TYPE_E            en_data_type;       /* ������Դ���� */
    SOCP_ENCSRC_CHNMODE_E       en_chan_mode;       /* ͨ������ */
    SOCP_CHAN_PRIORITY_E        en_chan_level;      /* ͨ�����ȼ� */
    u32                     bd_buf;             /* ����Դͨ��BD���ݿռ��ڴ�ָ�� */
    u32                     bd_buf_phy;         /* ����Դͨ��BD���ݿռ��ڴ�ָ�������ַ */
    u32                     bd_buf_len;         /* ����Դͨ��BD���ݿռ��С */
    u32                     rd_buf;             /* ����Դͨ��RD���ݿռ��ڴ�ָ�� */
    u32                     rd_buf_phy;         /* ����Դͨ��RD���ݿռ��ڴ�ָ�������ַ */
    u32                     rd_buf_len;         /* ����Դͨ��RD���ݿռ��С */
}bsp_om_socp_coder_src_cfg_s;

typedef struct
{
    u32                     start_ptr;      /*  ��ʼ��ַ*/
    u32                     start_phy_ptr;
    u32                     write_ptr;   /* log���ݱ���дָ��*/
    u32                     read_ptr;   /* buf �ռ��ͷŵ�д��ַ*/
    u32                     send_ptr;   /* buf���ݷ��͵�SOCP�Ķ���ַ*/
    u32                     buf_len;    /* buf ��С*/
    u32                     buf_size;   /* ��������ݳ���*/
    u32                     last_pading_len;  /* buf β��δ��ʹ�õĿռ�*/
    u32                     init_state;
}bsp_om_socp_buf_ctrl_s;



typedef struct  _bsp_om_list
{
    u32                     buf_addr;
    u32                     buf_len;
    struct _bsp_om_list      *pnext;
    struct _bsp_om_list      *ptail;
}bsp_om_list_s;

typedef struct
{
    u32 list_in;
    u32 list_get;
    u32 list_del;
}bsp_om_list_debug_s;


/*****************************************************************************
  5 �����붨��
*****************************************************************************/
#define BSP_ERR_OMS_BASE                (int)(0x80000000 | (BSP_DEF_ERR(BSP_MODU_OMS, 0)))
#define BSP_ERR_OMS_INVALID_MODULE      (BSP_ERR_OMS_BASE + 0x1)
#define BSP_ERR_OMS_MALLOC_FAIL         (BSP_ERR_OMS_BASE + 0x2)
#define BSP_ERR_OMS_INVALID_PARAM       (BSP_ERR_OMS_BASE + 0x3)
#define BSP_ERR_OMS_NO_BUF              (BSP_ERR_OMS_BASE + 0x4)
#define BSP_ERR_OMS_SOCP_INIT_ERR       (BSP_ERR_OMS_BASE + 0x5)
#define BSP_ERR_OMS_SOCP_GET_BD_ERR     (BSP_ERR_OMS_BASE + 0x6)
#define BSP_ERR_OMS_SOCP_GET_BD_NUM_ERR     (BSP_ERR_OMS_BASE + 0x7)
#define BSP_ERR_OMS_SOCP_BD_ADDR_ERR     (BSP_ERR_OMS_BASE + 0x8)
#define BSP_ERR_OMS_SOCP_WR_BD_ERR      (BSP_ERR_OMS_BASE + 0x9)
#define BSP_ERR_OMS_SOCP_GET_RD_ERR     (BSP_ERR_OMS_BASE + 0xA)
#define BSP_ERR_OMS_SOCP_CLEAN_RD_ERR   (BSP_ERR_OMS_BASE + 0xB)
#define BSP_ERR_OMS_BUF_CLEAN_ERR       (BSP_ERR_OMS_BASE + 0xC)
#define BSP_ERR_OMS_SOCP_START_ERR       (BSP_ERR_OMS_BASE + 0xD)
#define BSP_ERR_OMS_INIT_ERR            (BSP_ERR_OMS_BASE + 0xE)



void* bsp_om_alloc(u32 size, u32 *phy_real_addr);

u32 sys_view_init(void);

u32  bsp_om_get_hso_conn_flag(void);




#endif

