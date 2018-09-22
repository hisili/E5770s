#ifndef __ATP_KCMSMAIN_MSGTYPES_H__
#define __ATP_KCMSMAIN_MSGTYPES_H__

#ifndef ATP_MSG_CATEGORY_DEF
#define ATP_MSG_CATEGORY_DEF(x)          (((x) & 0xFFF) << 8)
#endif

enum ATP_KCMSMAIN_MSGTYPES_EN
{
    ATP_MSG_KCMSMAIN_START = ATP_MSG_CATEGORY_DEF(165),
    ATP_MSG_MONITOR_EVT_RESET,      /*�ָ��������ð���*/
    ATP_MSG_MONITOR_EVT_REBOOT,      /*�������ذ���*/    
    ATP_MSG_MONITOR_EVT_DSL_UP,         /*dsl line0 link up msg*/
    ATP_MSG_MONITOR_EVT_DSL_DOWN,       /*dsl line0 link down msg*/
    ATP_MSG_MONITOR_EVT_DSL_TRAINING,   /*dsl line0 training msg*/
    ATP_MSG_MONITOR_EVT_DSL_INIT,       /*dsl line0 ini msg*/
    ATP_MSG_MONITOR_EVT_LAN_ETH,
    ATP_MSG_MONITOR_EVT_DATACARD_START,       
    ATP_MSG_MONITOR_EVT_DATACARD_STOP, 
    ATP_MSG_MONITOR_EVT_WLAN,          /*WLAN����*/
    ATP_MSG_MONITOR_EVT_WPS,           /*WPS����*/
    ATP_MSG_MONITOR_EVT_WLAN_5G,       /*WLAN 5G����*/
    ATP_MSG_MONITOR_EVT_WPS_5G,        /*WPS 5G����*/
    ATP_MSG_MONITOR_EVT_DECT_PP,    /*DECT���밴��*/
    ATP_MSG_MONITOR_EVT_DECT_SEARCH,    /*DECT���Ұ���*/
    ATP_MSG_MONITOR_EVT_LOG,
    ATP_MSG_MONITOR_EVT_IPTV_START,    
    ATP_MSG_MONITOR_EVT_IPTV_STOP,  
    ATP_MSG_MONITOR_EVT_RTSP_START,    
    ATP_MSG_MONITOR_EVT_RTSP_STOP,         
    ATP_MSG_MONITOR_EVT_IPP_START,       
    ATP_MSG_MONITOR_EVT_IPP_STOP,   
    ATP_MSG_MONITOR_EVT_DYING_GASP,  /*Dying Gasp�����¼�*/ 	
    ATP_MSG_MONITOR_EVT_USBSTORAGE_PLUGIN,
    ATP_MSG_MONITOR_EVT_USBSTORAGE_PLUGOUT,
    ATP_MSG_MONITOR_EVT_WLANRF,      /*���߲�����д�¼�*/
    ATP_MONITOR_EVT_SERVLED_STOP,    /*Service LED stop*/
    ATP_MSG_MONITOR_EVT_WLAN_BAND_CHG,	   /*WLAN 2.4 G/5G �л�����*/
    ATP_MSG_MONITOR_EVT_WLAN_MODE_CHG,	   /*WLAN ģʽ �л�����*/
    ATP_MSG_MONITOR_EVT_WPS_SUCCESS,       /* WPS �ɹ�֮���ϱ� */
    ATP_MSG_MONITOR_EVT_LAN_DEVICE_UP,     /*ipv6��LAN���豸���ӵ����ط���DAD����*/
    ATP_MSG_MONITOR_EVT_MIDWARE_BUTTONPRESS, /*WPS/WLAN�����¼��ϱ����м��*/
    ATP_MSG_MONITOR_EVT_DSL1_UP,         /*dsl line1 link up msg*/
    ATP_MSG_MONITOR_EVT_DSL1_DOWN,       /*dsl line1 link down msg*/
    ATP_MSG_MONITOR_EVT_DSL1_TRAINING,   /*dsl line1 training msg*/
    ATP_MSG_MONITOR_EVT_DSL1_INIT,       /*dsl line1 ini msg*/
    ATP_MSG_MONITOR_EVT_USBERROR_HANDLE, /*USB������*/
	ATP_MSG_MONITOR_EVT_WM_START, /* ����ģ�鿪�� */
	ATP_MSG_MONITOR_EVT_WM_STOP,  /* ����ģ��Ͽ� */
    ATP_MSG_MONITOR_EVT_RCV_PADT,
    ATP_MSG_MONITOR_EVT_WIFISAFEKEY_ON,       /*wifisafekey on*/
    ATP_MSG_MONITOR_EVT_WIFISAFEKEY_OFF,      /*wifisafekey off*/
    ATP_MSG_MONITOR_EVT_WIFIPOWERSAVE_ON,     /*wifipowersave led on*/
    ATP_MSG_MONITOR_EVT_WIFIPOWERSAVE_OFF,    /*wifipowersave led off*/    
    ATP_MSG_MONITOR_EVT_WIFI_FBT_NOTIFY, /* WIFI FBT notify */
    ATP_MSG_MONITOR_EVT_WIFI_MULTICAST_NOTIFY, /* WIFI multicast notify */
    ATP_MSG_MONITOR_EVT_WIFI_STAMAC_NOTIFY,
    ATP_MSG_MONITOR_EVT_COREDUMP_FINISH, /* ����coredump�ļ� */
    ATP_MSG_MONITOR_EVT_WLAN_LOG,               /*��¼WLAN LOG*/   

    /*netlink module*/
    ATP_KCMSMAIN_NETLINK_ROUTE,    /*Route Balance Module*/
};


enum ATP_KCMSMAIN_NETLINK_MODULE_EN
{
    ATP_KCMSMAIN_NETLINK_NAT = 0xFF01,
    ATP_KCMSMAIN_NETLINK_DPI = 0xFF02,
};


/*�ں˺��û�̬ͨ�ŵ�netlinkЭ������*/
/*�ں˺��û�̬ͨ�ŵ�netlinkЭ������*/
/*ATP ��ǰʹ��20 -21���Ѿ���3.4�ں˳�ͻ�����»���ATPʹ��22 - 26*/
#define NETLINK_SYSWATCH                25
#define NETLINK_ATP_CONSOLE             26 /* send console printk to userspace */

#define SYSWATCH_USERSPACE_GROUP    31
#define KERNEL_PID      0
#define NETLINK_MSG_CMD_LEN         64

// this is the msg struct that being sent between the kernel and userspace
struct  generic_nl_msg
{
    unsigned int len; 		// the length of the "data" field
    unsigned int comm;  	// which kind of msg, referring to 'syswatch_msg_comm'
    unsigned char data[0]; 	// if the 'comm' needs to add more payload, put it here
};

typedef struct 
{
    unsigned int logType;
    unsigned int logLevel;
    unsigned int logNum;
}netlink_log_header;

/*�ں�֪ͨ�û�̬�����¼���Ϣ�ṹ��*/
typedef struct netlink_common_msg_st
{
    unsigned int eventType;
    unsigned int eventResult;
    unsigned int eventPortNum;
    char         acPortName[NETLINK_MSG_CMD_LEN];
}netlink_common_msg;

typedef enum FBT_NOTIFY_TYPE {
	FBT_LINK_WEAK_NOTIFY 		= 0,
    FBT_LINK_STRONG_NOTIFY = 1,
	FBT_STA_ONLINE_NOTIFY 	= 2,
	FBT_STA_OFFLINE_NOTIFY 	= 3, 
	FBT_STA_FOUND_NOTIFY 	= 4
} FBT_NOTIFY_E;

typedef struct  {
    unsigned int FbtWlanInstID;
    unsigned int  FbtChannel;
    unsigned int  FbtRSSI;
    FBT_NOTIFY_E  FbtNotifyType;
    char  FbtNotifyMac[20];
} FBT_NOTIFY_ST;

typedef struct  {
	char  ssid[20];
    char  StaMac[20];
} ASSOCI_NOTIFY_ST;

/*kernel netlink handler*/
typedef int (* PFNetlinkMsgProc)(unsigned short usModuleId, void *pvData, unsigned int ulDataLen);

// Global variable to indicate whether the userspace netlink socket has created,
// and send the monitored processes' names to the kernel
extern struct sock *syswatch_nl_sock;

//extern int syswatch_nl_init(void);
extern int syswatch_nl_send(unsigned int type, unsigned char *buf, unsigned int len);

extern int syswatch_sendLog(unsigned int logType, unsigned int logLevel, unsigned int logNum, unsigned char *str);

extern void dad_skb_send_up(void *pskb, void *phdr);

extern int ATP_Netlink_SendToUserspace(unsigned short usModuleId, void *pvData, unsigned int ulDataLen);

extern int ATP_Netlink_Register(unsigned short ulModuleId, PFNetlinkMsgProc pfMsgProc);

extern int ATP_Netlink_Unregister(unsigned short ulModuleId);

#endif // End of __ATP_KCMSMAIN_MSGTYPES_H__

