

#ifndef __CHIP_COMM_API_H__
#define __CHIP_COMM_API_H__

/*�������豸*/
#define CHIP_COMM_BCM_DEV           "usbcomm0"
#define CHIP_COMM_ACORE_DEV         "usb3"

/**************************************************
                ENUM DEFINITION
**************************************************/
typedef enum
{
    CHIP_COMM_SUCC,
    CHIP_COMM_FAIL,
} CHIP_COMM_ERR_EN;

/*��Ϣ����ģʽ: ͬ�����첽*/
typedef enum
{
    CHIP_COMM_ASYNC,
    CHIP_COMM_SYNC,
} CHIP_COMM_MSG_MODE_EN;

/*��Ϣ����: ��BCM����A�ˡ���A�˷���BCM*/
typedef enum
{
    CHIP_COMM_BCM2ACORE,
    CHIP_COMM_ACORE2BCM,
} CHIP_COMM_MSG_FLOW_EN;


/* ע�����Ϣ�����ڴ���ӣ��벻Ҫ�ڴ�ע��ͬһ����ģ��Ķ��id��
   �˴����ַ�����������ģ�飬ͬһģ��Ĳ�ͬ��Ϣid���Էŵ�buffer�У�
   ��ģ���ڲ��ٽ���*/
   
/*id����: 0x@@##$$$$
          @@  ��ʾȥ��: 01 ��ʾ��BCM���͵�balong A��
                        10 ��ʾ��balong A�˷��͵�BCM
          ##  ��ʾ�������
          $$$$��ʾ��Ϣ����*/
typedef enum
{
    /***********  ��ģ���ڲ�ʹ��  **********/
    DECT_SERVER_STATUS          = 0x01000000,   /*����ͨ·���ԣ����˾����Է���*/
    
    /*************  voip���  **************/
    EQUIP_TEST_SLIC             = 0x01010001,   /*SLIC���߲���*/


    DRV_RHPC_R2M_REQUEST        = 0x01020001,  /* Driver RHPC request Router->Modem*/
    DRV_RHPC_M2R_REQUEST        = 0x10020001,  /* Driver RHPC request Modem->Router*/

    /***********  BCM��ȡA��NV  ***********/
    
    
} CHIP_COMM_MSG_TYPE_EN;

/*message process call-back function*/
/*���ڸ�ģ���ע�ắ����˵:
  void *req_buf -- ��Σ����յ���Ϣ��
  int  req_len  -- ��Σ����յ���Ϣ����
  void *rsp_buf -- ���Σ���Ӧ����Ϣ��
  int  *rsp_len -- ���Σ���Ӧ����Ϣ����*/
typedef int (*CHIP_COMM_MSG_PROC)(void *req_buf, int req_len, void *rsp_buf, int *rsp_len);


typedef struct
{
    /*��Ϣ����*/
    CHIP_COMM_MSG_FLOW_EN msg_flow;

    /*��Ϣ����*/
    CHIP_COMM_MSG_TYPE_EN msg_type;

    /*����ģʽ*/
    CHIP_COMM_MSG_MODE_EN msg_mode;
} CHIP_COMM_INFO_ST;

typedef struct
{
    CHIP_COMM_MSG_TYPE_EN msg_type;
    CHIP_COMM_MSG_PROC    msg_proc_func;
} CHIP_COMM_PROC_ST;


/**************************************************
                FUNCTION DEFINITION
**************************************************/

/******************************************************************************
  ��������  : chip_comm_send_msg
  ��������  : ������Ϣ���Զ�оƬ
  �������  : CHIP_COMM_INFO_ST *msg_info ���͵���Ϣ��һЩ������Ϣ
              void *send_buf      ���͵���Ϣ�壬
              int send_len        ���͵���Ϣ����
              int recv_len        ���յ���Ӧ����Ϣ���ȣ�������첽��Ϣ����0

  ���ú���  :
  ��������  : 
  �������  : void *recv_buf      �Զ���Ӧ����Ϣ��,������첽��Ϣ,��NULL
  �� �� ֵ  : CHIP_COMM_SUCC, CHIP_COMM_FAIL
  
  �޸���ʷ  :

******************************************************************************/
extern int chip_comm_send_msg
(
    CHIP_COMM_INFO_ST *msg_info,
    void *send_buf, int send_len,
    void *recv_buf, int recv_len    
);

/******************************************************************************
  ��������  : chip_comm_detect_peer
  ��������  : ����Զ�server�Ƿ�OK���˽ӿ��������1��, �˺�������ϵͳ����ʱʹ��
  �������  : CHIP_COMM_MSG_FLOW_EN msg_flow  ��Ϣ���򣬸�֪����Ǹ�server

  ���ú���  :
  ��������  : 
  �������  : ��
  �� �� ֵ  : CHIP_COMM_SUCC, CHIP_COMM_FAIL
  
  �޸���ʷ  :

******************************************************************************/
extern int chip_comm_detect_peer(CHIP_COMM_MSG_FLOW_EN msg_flow);

/******************************************************************************
  ��������  : chip_comm_server_stop
  ��������  : ֹͣ˫��ͨ�ŵ�server��, ע��: �˺�����������������
              CHIP_COMM_SRV_BLOCK_TIMEOUT��
  �������  : ��

  ���ú���  :
  ��������  : 
  �������  : ��
  �� �� ֵ  : CHIP_COMM_SUCC, CHIP_COMM_FAIL
  
  �޸���ʷ  :

******************************************************************************/
extern int chip_comm_server_stop(void);

/******************************************************************************
  ��������  : chip_comm_BCM_server_start
  ��������  : BCMоƬ���ô˺�������˫��ͨ�ŵ�router���server��
  �������  : ��

  ���ú���  :
  ��������  : �˺�����usb0ע�����ʱ����
  �������  : ��
  �� �� ֵ  : CHIP_COMM_SUCC, CHIP_COMM_FAIL
  
  �޸���ʷ  :

******************************************************************************/
extern int chip_comm_BCM_server_start(void);

/******************************************************************************
  ��������  : chip_comm_Acore_server_start
  ��������  : BalongоƬA�˵��ô˺�������˫��ͨ�ŵ�modem���server��
  �������  : ��

  ���ú���  :
  ��������  : �˺�����usb0ע�����ʱ����
  �������  : ��
  �� �� ֵ  : CHIP_COMM_SUCC, CHIP_COMM_FAIL
  
  �޸���ʷ  :

******************************************************************************/
extern int chip_comm_Acore_server_start(void);


#endif //end of __CHIP_COMM_API_H__
