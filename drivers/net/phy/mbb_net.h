#ifndef __PHY_MBB_NET_H__
#define __PHY_MBB_NET_H__

#define NET_RET_OK      0
#define NET_RET_FAIL    (-1)

#define IP_ADDR_LEN     16

#define _LAN_DEBUG_
#ifdef _LAN_DEBUG_
#define LAN_DEBUG  printk
#else
#define LAN_DEBUG
#endif


/*װ��Ҫ��Ķ˿�״̬�ṹ��*/
typedef struct tagEquipNetPartST
{
    unsigned int total_port;
    unsigned int port_index;
    unsigned int port_rate;
    unsigned char ip_add[IP_ADDR_LEN];
}NET_PORT_ST;

#define RTK8367_ID                            0x83676367   //������Ϊrtk8367������ID��ʶ
#define RTK8367_ID_MASK                 0xffffffff

#define SIOCLINKSTATE                       0x89F8   //ϵͳ��ȡ������״̬
#define SWITCH_LAN_PORT_NUM         3           //��ΪLAN�ڵ���Ŀ

typedef enum
{
    ETH_CHANGE_NONE,      //�ޱ仯
    ETH_LAN_DOWN,           //LAN��down
    ETH_LAN_UP,                 //LAN��up
    ETH_WAN_DOWN,           //WAN��down
    ETH_WAN_UP,                //WAN��up
};

typedef struct tag_LAN_ETH_STATE_INFO_ST
{
    int link_state;     /* link state */ 
    int dpulex;         /* dpulex */ 
    int speed;          /* speed */
} LAN_ETH_STATE_INFO_ST;

/*****************************************************************************
��������   PhyATQryPortPara
��������:  װ����������Ϣ��ȡ�ӿ�
�������:  �˿�����
����ֵ��  NET_RET_OK(0)Ϊok 
*****************************************************************************/
int PhyATQryPortPara(NET_PORT_ST *PortPara);

/*****************************************************************************
��������   mbb_check_net_upgrade
��������:  �жϱ����Ƿ����鲥��������
�������:  skb����
����ֵ��  NET_RET_OK(0)Ϊok 
*****************************************************************************/
int mbb_check_net_upgrade(struct sk_buff *skb);

/*****************************************************************************
��������   mbb_mac_clone_rx_restore
��������:  MAC�����PPP����ʱmac clone
�������:  skb����
����ֵ��  NET_RET_OK(0)Ϊok 
*****************************************************************************/
int mbb_mac_clone_rx_restore(struct sk_buff *skb);

/*****************************************************************************
��������   mbb_mac_clone_tx_save
��������:  MAC�㷢��PPP����ʱmac clone
�������:  skb����
����ֵ��  NET_RET_OK(0)Ϊok 
*****************************************************************************/
int mbb_mac_clone_tx_save(struct sk_buff *skb);

/*****************************************************************************
��������   mbb_get_phy_device
��������:  �ṩ������ģ���ȡphy�豸
��������� ��
����ֵ��   phy�豸
*****************************************************************************/
struct phy_device *mbb_get_phy_device(void);

/*****************************************************************************
��������  hw_net_sysfs_init
��������: lan_usb�ڵ㴴��
�������:  
����ֵ��NET_RET_OK(0)Ϊok 
*****************************************************************************/
int hw_net_sysfs_init(void);

/*****************************************************************************
��������  hw_net_sysfs_init
��������: lan_usb�ڵ�ɾ��
�������:  
����ֵ��NET_RET_OK(0)Ϊok 
*****************************************************************************/
void hw_net_sysfs_uninit(void);

/*****************************************************************************
��������   RNIC_WANMirror
��������:  ��WAN�ھ���
�������:  enableʹ�����
                        port�˿ں�
����ֵ��  NET_RET_OK(0)Ϊok 
*****************************************************************************/
int RNIC_WANMirror(unsigned int enable, unsigned int port);

/*****************************************************************************
��������   RNIC_Map_To_Lan_Forward
��������:  WAN�ھ���
�������:  skb����
����ֵ��  NET_RET_OK(0)Ϊok 
*****************************************************************************/
int RNIC_Map_To_Lan_Forward(struct sk_buff *skb);

/*****************************************************************************
��������   rtk_get_port_status_info
��������:  ΪӦ�ò��ȡ�˿ڵ�״̬
��������� startPort ��ʼ�˿�
                            num �����Ķ˿ڸ���
����������˿�״̬��Ϣ                            
����ֵ��   NET_RET_OK(0)Ϊ��ȡ״̬OK
*****************************************************************************/
void rtk_get_port_status_info(LAN_ETH_STATE_INFO_ST *pEthInfo, int startPort, int num);
#endif
