

#ifndef    _DRV_HSUART_H_
#define    _DRV_HSUART_H_


#ifdef __cplusplus
extern "C" 
{ 
#endif /* __cplusplus */

/**************************************************************************
  ͷ�ļ�����                            
**************************************************************************/

/**************************************************************************
  �궨�� 
**************************************************************************/
#define UART_IOCTL_SET_WRITE_CB      		0x7F001000
#define UART_IOCTL_SET_READ_CB       		0x7F001001
#define UART_IOCTL_SET_EVT_CB        		0x7F001002
#define UART_IOCTL_SET_FREE_CB       		0x7F001003
#define UART_IOCTL_WRITE_ASYNC       		0x7F001010
#define UART_IOCTL_GET_RD_BUFF       		0x7F001011
#define UART_IOCTL_RETURN_BUFF       		0x7F001012
#define UART_IOCTL_RELLOC_READ_BUFF  		0x7F001013
#define UART_IOCTL_SEND_BUFF_CAN_DMA 		0x7F001014
#define UART_IOCTL_SET_WRITE_TIMEOUT 		0x7F001015
#define UART_IOCTL_SET_BAUD           		0X7F001016
#define UART_IOCTL_SET_WLEN           		0X7F001017
#define UART_IOCTL_SET_STP2           		0X7F001018
#define UART_IOCTL_SET_EPS            		0X7F001019
#define UART_IOCTL_IS_IMPORT_DONE    		0x7F001020
#define UDI_UART_IOCTL_SET_READ_CB          UART_IOCTL_SET_READ_CB
#define UDI_UART_IOCTL_GET_READ_BUFFER_CB   UART_IOCTL_GET_RD_BUFF
#define UDI_UART_IOCTL_RETUR_BUFFER_CB      UART_IOCTL_RETURN_BUFF
#define UART_IOCTL_SET_MSC_READ_CB 			0x7F001021
#define UART_IOCTL_MSC_WRITE_CMD 			0x7F001022
#define UART_IOCTL_SWITCH_MODE_CB 			0x7F001023
#define UART_IOCTL_SET_FLOW_CONTROL 		0x7F001024
#define UART_IOCTL_SET_AC_SHELL 			0x7F001025

#define UART_A_SHELL  (0x5A5A5A5A)
#define UART_C_SHELL  (0xA5A5A5A5)
/**************************************************************************
  ö�ٶ���
**************************************************************************/
enum MEM_TYPE_ENUM
{
    MEM_TYPE_SYS_DEFINED = 0,            /* ���ݿ���Linuxϵͳ�ṩ*/
    MEM_TYPE_USER_DEFINED,               /* ���ݿ����û�������ڴ��ṩ*/
    MEM_TYPE_BUTT
 };

/* UART����λ��*/
typedef enum
{
    WLEN_5_BITS,
    WLEN_6_BITS,
    WLEN_7_BITS,
    WLEN_8_BITS,
    WLEN_MAX,
}UART_WLEN_ENUM;

/* UARTֹͣλ��*/
typedef enum
{
    STP2_OFF,
    STP2_ON,
    STP2_MAX,
}uart_stp2_enum;

/* UARTУ�鷽ʽ*/
typedef enum
{
    PARITY_NO_CHECK,
    PARITY_CHECK_ODD,
    PARITY_CHECK_EVEN,
    PARITY_CHECK_MARK,        /*У��λʼ��Ϊ1*/
    PARITY_CHECK_SPACE,       /*У��λʼ��Ϊ0*/
    PARITY_CHECK_MAX,
}uart_parity_enum;


/**************************************************************************
  STRUCT����
**************************************************************************/
typedef void (*hsuart_free_cb_t)(char* pBuff);
typedef void (*hsuart_read_cb_t)(void);
typedef void (*hsuart_msc_read_cb_t)(MODEM_MSC_STRU* pModemMsc);
typedef void (*hsuart_switch_mode_cb_t)(void);

typedef struct tagUART_READ_BUFF_INFO
{
    unsigned int u32BuffSize;
    unsigned int u32BuffNum;
}hsuart_read_buff_info;

/* ���ؿ��ؽṹ */
typedef union
{
   unsigned int      value;
    struct
    {
		unsigned int  reserved1 : 14;/* bit[0-13] : reversed */
		unsigned int  rtsen         : 1;/* bit[14] : rts enable, up stream flow ctrl  */
 		unsigned int  ctsen         : 1;/* bit[15] : cts enable, down stream flow ctrl */
 		unsigned int  reserved2 : 16;/* bit[16-31] : reversed */
    } reg;
}uart_flow_ctrl_union;

typedef int (*UDI_ADP_INIT_CB_T) (VOID);
typedef int (*UDI_GET_CAPABILITY_CB_T)(UDI_DEVICE_ID devId);
typedef int (*UDI_OPEN_CB_T)(UDI_OPEN_PARAM *param, UDI_HANDLE handle);
typedef int (*UDI_CLOSE_CB_T)(VOID* pPrivate);
typedef int (*UDI_WRITE_CB_T)(VOID* pPrivate, void* pMemObj, BSP_U32 u32Size);
typedef int (*UDI_READ_CB_T)(VOID* pPrivate, void* pMemObj, BSP_U32 u32Size);
typedef int (*UDI_IOCTL_CB_T) (VOID* pPrivate, BSP_U32 u32Cmd, VOID* pParam);


/* �������亯��ָ��� */
typedef struct tagUDI_DRV_INTEFACE_TABLE
{
	/* capability */
	UDI_ADP_INIT_CB_T		udi_get_capability_cb;

	/* data interfaces */
	UDI_OPEN_CB_T			udi_open_cb;
	UDI_CLOSE_CB_T			udi_close_cb;
	UDI_WRITE_CB_T			udi_write_cb;
	UDI_READ_CB_T			udi_read_cb;
	UDI_IOCTL_CB_T			udi_ioctl_cb;
}UDI_DRV_INTEFACE_TABLE;

#ifdef __cplusplus
} /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif

