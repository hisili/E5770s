

#ifndef PLATFORM_API_CPE_H
#define PLATFORM_API_CPE_H

#ifndef O_RDWR
#define O_RDWR		02
#endif

//#include <stdint.h>
//#include <stdbool.h>

/***************��������reboot�ӿ�ͷ�ļ�����************/

#ifdef MBB_FEATRUE_BCMNETLINK

#define NETLINK_SYSWATCH (31)

#else

#define NETLINK_SYSWATCH (20)/*netlink ID*/
#endif





/******************RNDIS�˿��л��ӿ�ͷ�ļ�����*****************/
enum ioctl_type
{
	ENUM_FORCE_SWITCH_PROJECT_MODE = 0,
	ENUM_FORCE_SWITCH_DEBUG_MODE    = 1,
	ENUM_USB_RNDIS_SET_RATE         = 3
};

/******************breathled������ͷ�ļ�����*****************/
typedef enum
{
    LED_STATE_LIGHT = 0, //�����Ƴ���
    LED_STATE_SLEEP = 1, //��������
    LED_STATE_SPARK = 2,  //��������˸
    BREATH_LED_STATE_ENABLE  = 3, //������ʹ��
    BREATH_LED_STATE_DISABLE = 4, //�����Ʋ�ʹ��
    BREATH_LED_STATE_MAX
}LED_STATE;
/********************DRVSTARTMODE�ӿ�ͷ�ļ�����***************/

typedef enum DRV_START_MODE_tag
{
    DRV_START_MODE_EXCEPTION,  /* �쳣����ģʽ����ʱ�󲿷�ҵ�񶼲�����, ����ʾ��Ϣ */
    DRV_START_MODE_NORMAL,   /*��������*/
    DRV_START_MODE_CHARGING,   /* ��翪��ģʽ, ps ��ҵ������  */  
    DRV_START_MODE_NOAPP,      /*SD�������ڶ�������������APP*/
    DRV_START_MODE_BUTT
}DRV_START_MODE_ENUM;
 


/********��ѯ��ص����ͳ��״̬�ӿ�ͷ�ļ�����********/

/*��س��״̬--��ѯ��״̬�Ե���Ϊ׼*/
typedef enum CHARGING_STATE_ENUM_tag
{
    CHARGING_INIT =  -1,
    NO_CHARGING_UP = 0,         /* ����δ���*/
    CHARGING_UP,               /*�������ڳ�� */
    NO_CHARGING_DOWN,          /* �ػ�δ��� */
    CHARGING_DOWN,             /* �ػ����  */
    NO_BATTERY                 /* ��ز����� */
}CHARGING_STATE_ENUM;


/* ��ص���*/
typedef enum BATT_LEVEL_ENUM_tag
{   
    BATT_INIT =  -2,
    BATT_LOW_POWER = -1 ,  /*��ص͵磬*/
    BATT_LEVEL_0,                 /*0���ص���**/
    BATT_LEVEL_1 ,                /*1���ص���*/
    BATT_LEVEL_2 ,                 /*2���ص���*/
    BATT_LEVEL_3 ,               /*3���ص���*/
    BATT_LEVEL_4  ,              /*4���ص���*/
    BATT_LEVEL_MAX
}BATT_LEVEL_ENUM;
/*��ظ����ϱ��¼�*/
typedef enum BATT_TEMP_EVENT_tag
{
   BATT_TEMP_LOW,   /* ��ص����¼� */      
   BATT_TEMP_HIGH,   /* ��ظ����¼� */ 
   BATT_TEMP_NORMAL, /* ��ظ��½���¼� */
   BATT_TEMP_MAX     /* ����¼�ֵ��С�ڴ�ֵ����Ϊ�Ƿ��¼�*/
}BATT_TEMP_EVENT;

/*��س��׶�*/
typedef enum _CHARGE_TYPE
{
    E_CHARGE_NULL = 0,
    E_CHARGE_TRICKLE = 1, /* ��ش���丳�״̬ */      
    E_CHARGE_FAST = 2,   /* ��ش��ڿ��ٳ��״̬ */ 
    E_CHARGE_SUPP = 3, /* ��ش��ڲ����״̬ */
    E_CHARGE_MAINT = 4, /* ��ش�������״̬ */
    GPIO_CHARGE_TYPE_MAX  = 0xFF   /* ����¼�ֵ��С�ڴ�ֵ����Ϊ�Ƿ��¼�*/
} CHARGE_TYPE;

/*��س��״̬��ѯ�ṹ*/
typedef struct BATT_STATE_tag        
{   
    CHARGING_STATE_ENUM  charging_state;
    BATT_LEVEL_ENUM      battery_level;
    BATT_TEMP_EVENT      batt_temp_state;
    /*��ص����ٷֱ�*/
    signed int              battery_percent;  
    /*��س������*/
    CHARGE_TYPE             charge_type;
    /*Ԥ�Ƴ���ʱ��*/
    signed int              charge_remain_time;/*  -2 : ��ʾ���ڼ���  -1�� ��ʾ��֧��ʣ��ʱ�䣬���ڵ���0 ��ʾ���ʣ��ʱ�䣬��λΪ����*/
    /*Ԥ����չ�ֶ�*/
    signed int              rever;
}BATT_STATE_T;
/*AF10��λ״̬ö�ٽṹ*/
typedef enum
{
    AF10_STATE_INIT = -1,
	AF10_STATE_IN = 0,
    AF10_STATE_OUT,
}AF10_STATE_ENUM_LIST;
/*������״̬ö��*/
typedef enum
{
    CHG_EXTCHAGRE_STATE_INIT = -1,
    CHG_EXTCHAGRE_STATE_STOP = 0,
    CHG_EXTCHAGRE_STATE_START,
    CHG_EXTCHAGRE_STATE_TEMP, 
    CHG_EXTCHAGRE_STATE_MAX
}EXTCHAGRE_STATE_ENUM_LIST;

/*��ض�����״̬��ѯ�ṹ*/
typedef struct BATT_EXTSTATE_tag        
{   
    AF10_STATE_ENUM_LIST  extAF10_state;
    EXTCHAGRE_STATE_ENUM_LIST   extcharging_state;    
}EXTCHAGRE_STATE_T;

typedef enum
{
    PRODUCT_TYPE_E5220 = 0,
    PRODUCT_TYPE_E5221,
    PRODUCT_TYPE_E5151,
    PRODUCT_TYPE_E5756,
    PRODUCT_TYPE_E5251,
    PRODUCT_TYPE_MAX,
}PRODUCT_TYPE_ENUM_LIST;

typedef enum CHG_ON_OFF_LINE_STATUS_tag
{
    STATUS_OFFLINE = 0,//�����/usb��λ
    STATUS_ONLINE = 1, //�����/usb����λ
}CHG_ON_OFF_LINE_STATUS;

typedef enum CHARGE_TYPE_ENUM_tag
{
    CHARGE_TYPE_NON_CHECK = -1,          /* ��δ�жϳ������������� */
    CHARGE_TYPE_HW = 0,                      /* ��Ϊ�����             */
    CHARGE_TYPE_USB = 1,                  /* USB������������           */
    
}CHARGE_TYPE_ENUM;

typedef struct CHG_STATUS_STRU
{
    CHARGE_TYPE_ENUM chg_type;//���������
    CHG_ON_OFF_LINE_STATUS chg_on_off_line_flag;//�Ƿ���λ
}CHG_STATUS;
typedef enum CHARGE_STATUS_tag
{
    CHARGE_STATUS_READ_FAIL = -1,  /*�ϲ���ײ�ͨ��ʧ��*/
    CHARGE_STATUS_OFFLINE = 0,          /* ����λ*/
    CHARGE_STATUS_USB_TYPE = 1,                      /* USB           */
    CHARGE_STATUS_WALL_CHG_TYPE = 2,                  /*  ��Ϊ�����          */
}CHARGE_STATUS;

#ifdef FEATURE_HUAWEI_MBB_V7R1
typedef enum        
{   
	BATT_LEVEL_GET       = 0, /*��س�������ѯ*/
	/*1��2�������ֿ�����ϵͳ����cmd��������*/
	USB_CHARGE_STATE_GET = 3, /*USB���߳������λ����ѯ*/
	CHG_STATE_MAX
}CHG_IOCTL_CMD;

typedef enum        
{   
	CHG_USB_NONE   = 0, /*���������λ*/
	CHG_USB_NON_HW = 1, /*�Ǳ�׼�������λ*/
	CHG_USB_HW     = 2, /*��Ϊ��׼�������λ*/
	CHG_USB_MAX
}CHG_USB_STATE;


/*���ٿ��ػ��ýṹ*/
typedef enum        
{   
	PWRCTL_WAKE_LOCK      = 3, /*���岻����*/
	PWRCTL_WAKE_UNLOCK    = 4, /*���������*/
	PWRCTL_SHORT_OFF_MODE = 5, /*����ٹػ�*/
	PWRCTL_SHORT_ON_MODE  = 6, /*�˳��ٹػ�����δ����ٹػ�*/
	PWRCTL_MODE_MAX
}PWRCTL_IOCTL_CMD;
#endif
/******************oled��ʾ��ؽӿ�ͷ�ļ�����************/
enum 
{
    OLED_LIGHT = 3,
    OLED_SLEEP,
    OLED_DIM,
    OLED_RESET,
    OLED_UPDATE,
    OLED_CONTRAST,
    OLED_BRIGHTNESS,
    OLED_POWER_ON,
    OLED_POWER_OFF,
    OLED_DEL_TIMER,
    OLED_SYS_POWER_DOWN,
    OLED_INIT_IMAGE,
    OLED_POWER_OFF_CHARGING_START,/*restart power off charging animation*/
    OLED_POWER_OFF_CHARGING_STOP,/*stop power off charging animation*/
    OLED_GET_FRAME_BUF,
    OLED_WRITE_IMAGE,
    OLED_ALL_WHITE,
    OLED_ALL_BLACK,
    OLED_CMD_MAX
}OLED_IOCTL_CMD;


typedef struct tag_oled_write_data {
	unsigned int x_start;
	unsigned int y_start;
	unsigned int x_offset;
	unsigned int y_offset;
	unsigned char *image;
	unsigned int size;
}oled_write_data;
/*������Ӧ�õĽӿڣ�����ioctl�Ĳ���������*/
typedef enum _LED_IOCTL_CMD
{
    LED_IOCTL_SET = 0,  /*����LED�Ƶ�״̬*/
    LED_IOCTL_GET,      /*��ȡLED�Ƶ�״̬*/
    LED_IOCTL_CMD_MAX   /*Ŀǰ֧�ֵ��������*/
}LED_IOCTL_CMD;
typedef enum _LED_STATE
{
    LED_STATE_ON = 0,
    LED_STATE_OFF,
    LED_STATE_BLINK,
    LED_STATE_COLOR_BLINK,
    LED_STATE_ALL_BLINK,
    LED_STATE_MAX,
}LED_DEV_STATE;
typedef enum _LED_ID
{
    LED_ID_FIRST = 0,
    LED_ID_WIFI = LED_ID_FIRST,  /* WIFI�� */
    LED_ID_BAT,                  /* ��ص� */
    LED_ID_SMS,                  /* ���ŵ� */
    LED_ID_CIRCLE,               /* װ�ε� */
    LED_ID_SIGNAL1,              /* �źŵ�1 */
    LED_ID_SIGNAL2,              /* �źŵ�2 */
    LED_ID_SIGNAL3,              /* �źŵ�3 */
    LED_ID_SLIC,                 /* ����ָʾ�� */
    LED_ID_MODE,                 /* ������ʽָʾ�� */
    LED_ID_MAX
} LED_ID;

typedef enum _LED_COLOR
{
    LED_COLOR_RED = 0,
    LED_COLOR_GREEN,
    LED_COLOR_YELLOW,
    LED_COLOR_BLUE,
    LED_COLOR_WHITE,
    LED_COLOR_CYAN,
    LED_COLOR_PURPLE,
    LED_COLOR_MAX
}LED_COLOR;
typedef enum _LED_CURRENT
{
    LED_CURRENT_LEVEL0 = 0,
    LED_CURRENT_LEVEL1,
    LED_CURRENT_LEVEL2,
    LED_CURRENT_LEVEL3,
    LED_CURRENT_LEVEL4,
    LED_CURRENT_LEVELMAX
}LED_CURRENT;

/*LED��ģʽ */
typedef enum _LED_MODE
{
    LED_MODE_NORMAL = 0,
    LED_MODE_SLEEP,
    LED_MODE_MAX
}LED_MODE;

/*������Ӧ�õĽӿڣ�����ioctl�����úͻ�ȡ��������ʹ�õĲ�������*/
typedef struct _LED_IOCTL_ARG
{
    LED_DEV_STATE led_dev_state;
    LED_ID led_id;
    LED_COLOR led_color;
    LED_COLOR second_led_color;
    unsigned int duration;
    unsigned int second_duration;
    LED_CURRENT led_current;
    LED_MODE sleep_mode;
}LED_IOCTL_ARG;
typedef enum _NET_CRADLE_STATUS
{
    NET_CRADLE_STATUS_ERR = -1,  /*��ȡ������λ����*/
    NET_CRADLE_STATUS_OFF = 0,    /*���߲���λ*/
    NET_CRADLE_STATUS_ON = 1    /*������λ*/
}NET_CRADLE_STATUS;
#ifndef FEATURE_HUAWEI_MBB_V7R1
typedef enum
{
    PWRCTL_WAKE_LOCK = 0,         /*������˯��*/
    PWRCTL_WAKE_UNLOCK = 1,    /*�ɽ���˯��*/
    PWRCTL_SHORT_OFF_MODE = 5, /*����ٹػ�*/
    PWRCTL_SHORT_ON_MODE  = 6, /*�˳��ٹػ�����δ����ٹػ�*/
    PWRCTL_MODE_MAX,                 /*�Ƿ�ֵ*/
}PWRCTL_IOCTL_CMD;
#endif

#define FUNC_RETURN_OK   0
#define FUNC_RETURN_ERR  -1
#define HW_NDIS_PORT     0x16
#define HW_DEV_NONE      0xFF
#define HW_MAX_PORT      17
#define en_NV_Item_Huawei_Dynamic_PID_Type 50091

typedef enum
{
    /*��ǰΪNDIS UP��״̬*/       
    NDIS_DOWN = 0,
    /*��ǰΪNDIS DOWN��״̬*/ 
    NDIS_UP,
    /*����״̬*/
    NDIS_OTHER
}NDIS_STATE_ENUM;

typedef struct
{
    unsigned long   ulNvStatus;
    unsigned char   aucFirstPortStyle[17];   /* �豸�л�ǰ�˿���̬ */
    unsigned char   aucRewindPortStyle[17];  /* �豸�л���˿���̬ */
    unsigned char   aucReserved[22];         /* ���� */
}AT_DYNAMIC_PID_TYPE_STRU;

typedef enum 
{
    USB_CHARGE_INIT = -1, /*��ʼֵ*/
    USB_CHARGE_TETHERING = 0, /*���+ͨ�ţ�Ĭ�Ϸ�ʽ*/
    USB_CHARGE_ONLY = 1, /*����USB���ڽ����״̬*/   
}USB_CHARGE_POLICY;

/*���½ṹ�嶨��Ϊ Samba ��ӡ�������Լ���ӡ��״̬*/
#ifndef PRINTER_NAME_MAX
#define PRINTER_NAME_MAX (64)
#endif
#ifndef PRINTER_NUM_MAX
#define PRINTER_NUM_MAX (8)
#endif
#ifndef PRINTER_CMD_LEN
#define PRINTER_CMD_LEN (256)
#endif
typedef struct tagPlatformSambaPrinterInfo
{
	char  printer_name[PRINTER_NAME_MAX];  /*��ӡ������*/
	int   printer_id;        /*��ӡ����ʶ*/
}PRINTER_INFO_ST;

/*���¶���Smaba ��ӡ����ǰ�����Լ�ÿ̨��ӡ����Ϣ�����֧��8 ̨��ӡ��*/
typedef struct _PRINTER_INFO
{
	int                    printernum;   // ��ӡ������
        PRINTER_INFO_ST  sPrinter[PRINTER_NUM_MAX];   //  ÿ̨��ӡ����Ϣ
}PRINTER_INFO;
#ifdef MBB_PLATFORM_BCM4708
int reboot_router(void);
int reboot_modem(void);
#else
/*V3ƽ̨��V7ƽ̨ͬʱ��֧�ֵĽӿڶ���*/
int reboot(void);
#endif
int update_modem_state(void);
DRV_START_MODE_ENUM drvStartModeGet( void );
int app_get_battery_state(BATT_STATE_T *battery_state);

int oledIoctrl(unsigned int cmd,  unsigned long arg);
void oledRefresh(unsigned int ulXStart, unsigned int ulYStart, unsigned int ulXOffset, unsigned int ulYOffset, unsigned char *pucBuffer);

void uwd_force_switch_project_mode(void);
void uwd_force_switch_debug_mode(void);
int usb_rndis_set_rate(uint32_t ulRate);

int bsp_led_ctrl(LED_STATE state);
int led_dev_ctrl(LED_IOCTL_CMD cmd_id, LED_IOCTL_ARG *led_arg);
int set_special_timer(unsigned char bStart, unsigned int uTime );


int set_wake_lock(bool bLock);
int set_deep_sleep_mode(bool bSleepMode);

int app_get_product_type_state(PRODUCT_TYPE_ENUM_LIST *product_type);

void lan_pm_power_on(unsigned char power_on);
/*NET_CRADLE_STATUS get_net_line_state(void);*/

#ifndef FEATURE_HUAWEI_MBB_V7R1
/******************** ����V3ƽ̨֧�ֵĽӿڶ���*************************/
CHARGE_STATUS get_usb_charge_status(void);
int set_wake_lock_wps(bool bLock);
#endif

#ifdef FEATURE_HUAWEI_MBB_V7R1
/******************** ����V7ƽ̨֧�ֵĽӿڶ���*************************/
int get_usb_charge_status(void);

int set_powersave_mode( int powersavemode );

int get_powersave_mode( void );

/*int app_get_extchg_AF10_state(EXTCHAGRE_STATE_T *extcharging_state);*/

/**********************************************************************
�� �� ��      : sync_before_poweroff
��������  : �ṩ��Ӧ�õĽӿڣ����ڹػ�ǰ�����ļ�ϵͳ��ͬ��
�������  :void
�������  : �ޡ�
�� �� ֵ      : int����:0ִ�гɹ���-1ִ��ʧ�ܡ�
ע������  : ע��ýӿڵ��ã��辡���ܱ�֤�ػ����̵���֮�󣬲��ٽ����ļ�ϵͳд������
***********************************************************************/
int sync_before_poweroff(void);
#endif

/*int get_usb_charge_policy(USB_CHARGE_POLICY* chg_policy);
int set_usb_charge_policy(const USB_CHARGE_POLICY chg_policy);*/

int app_samba_get_printerinfo(PRINTER_INFO  *pSamPrinterinfo);
int app_samba_inform_status(int status);
#endif /* PLATFORM_API_H */

