

/*===========================================================================
                       linuxϵͳͷ�ļ�
===========================================================================*/
#include <linux/ctype.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/if_addr.h>
#include <linux/if_arp.h>
#include <linux/if_vlan.h>
#include <linux/if_ether.h>
#include <linux/netdevice.h>
#include <linux/inetdevice.h>
#include <../net/bridge/br_private.h>

/*===========================================================================
                       ƽ̨ͷ�ļ�
===========================================================================*/
#include "wlan_utils.h" /* ����log��ӡ */

/*===========================================================================
                        �ڲ�ʹ�ö�������
===========================================================================*/
/*ϵͳ��ӡ�ӿ�*/
#define WLAN_SEC_PRINTK(leve, fmt, ...) do { \
    if (WLAN_LOG_LEVE >= leve) \
    { \
        (void)pr_err("Wi-Fi <SEC> [%s:%d]: "fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    } \
}while(0)
#define WAN_SEC_INFO(fmt, ...) WLAN_SEC_PRINTK(WLAN_LOG_KERNEL, fmt, ##__VA_ARGS__) /*WLAN_LOG_DRV_HI*/
#define WAN_SEC_ERR(fmt, ...)  WLAN_SEC_PRINTK(WLAN_LOG_KERNEL, fmt, ##__VA_ARGS__)

#if !defined(__KERNEL__) || (LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,35)) /* Linux�ں˰汾���� */
    #define GET_BR_PORT(netdev) ((struct net_bridge_port *)(((struct net_device *)netdev)->br_port))
#else
    #define GET_BR_PORT(netdev) ((struct net_bridge_port *)rcu_dereference(((struct net_device *)netdev)->rx_handler_data))
#endif

// MAC��ַ�Ƚ� d_mac��s_macΪ6�ֽ�MAC��ַ��ָ��  ���ȱȶԵ�ַǰ4�ֽڱȶ� Ȼ��ȶԵ�ַ��4�ֽڱȶ�
#define ARP_SMAC_CMP(d_mac, s_mac)   ( \
    ((unsigned int)(*((unsigned int *)(d_mac))) == (unsigned int)(*((unsigned int *)(s_mac))))  \
    && ((unsigned short)(*(((unsigned short *)(d_mac)) + 2)) == (unsigned short)(*((unsigned short *)(s_mac) + 2))) /*MAC*/ \
)

/*===========================================================================

                        ����ʵ�ֲ���

===========================================================================*/
/*****************************************************************************
 ��������  : wlan_get_br_by_port
 ��������  : ��ȡ�豸��Ӧ�����豸
 �������  : netdev: �豸����
 �������  : NA
 �� �� ֵ  : ָ�����豸��ָ��
*****************************************************************************/
static inline struct net_device *wlan_get_br_by_port(struct net_device *netdev)
{
    struct net_bridge_port *br_port = NULL;

    if (NULL == netdev)
    {
        return (NULL);
    }
    
    br_port = GET_BR_PORT(netdev);
    if ((NULL == br_port) || (NULL == br_port->br))
    {
        return (NULL);
    }

    return (br_port->br->dev);
}

/*****************************************************************************
 ��������  : wlan_get_arphdr
 ��������  : ��ȡarpͷ
 �������  : pskb: ��Ҫ�������ݰ�
 �������  : NA
 �� �� ֵ  : ָ��arpͷ��ָ��
*****************************************************************************/
static inline struct arphdr *wlan_get_arphdr(struct sk_buff *pskb)
{
    struct ethhdr *eth = NULL;
    struct arphdr *arp = NULL;

    if (NULL == pskb)
    {
        return (NULL);
    }

    eth = (struct ethhdr *)(pskb->data);
    if (__constant_htons(ETH_P_ARP) == eth->h_proto)
    {
        arp = (struct arphdr*)(pskb->data + ETH_HLEN);
    }
    else if (__constant_htons(ETH_P_8021Q) == eth->h_proto)
    {
        struct vlan_ethhdr *vhdr = (struct vlan_ethhdr *)eth;
        if (__constant_htons(ETH_P_ARP) == vhdr->h_vlan_encapsulated_proto)
        {
            arp = (struct arphdr *)(vhdr + 1);
        }
    }

    return (arp);
}
/*****************************************************************************
 ��������  : wlan_check_arp_spoofing
 ��������  : ���wlan��arp��ƭ  ����֧��IPV4Э��
 �������  : netdev: Դnetif�ӿ�, pskb: ��Ҫ�������ݰ�
 �������  : NA
 �� �� ֵ  : 0:����ARP��ƭ���ģ�1: ��ARP��ƭ����
*****************************************************************************/
int wlan_check_arp_spoofing(struct net_device *port_dev, struct sk_buff *pskb)
{
    struct arphdr *arp = NULL;
    struct net_device *br_dev = NULL;
    int is_arp_spoofing_pkt = 0;
    unsigned int arp_src_ip = 0;

    /* ����Ƿ�ARP���� */
    arp = wlan_get_arphdr(pskb);
    if (NULL == arp)
    {
        return (0);
    }
    arp_src_ip = *((unsigned int *)((char *)(arp + 1) + arp->ar_hln)); /* ԴIP */
    if (0 == arp_src_ip)
    {
        return (0);
    }

    /* ��ȡ���豸 */
    br_dev = wlan_get_br_by_port(port_dev);
    if ((NULL == br_dev) || (NULL == br_dev->dev_addr))
    {
        return (0);
    }

    /* ����Ƿ�����IP ARP RSP ���� */
    if ((arp_src_ip == (unsigned int)inet_select_addr(br_dev, arp_src_ip, RT_SCOPE_LINK))  //ARP RSP IP��ַΪ����IP
        && !ARP_SMAC_CMP(arp + 1, br_dev->dev_addr)  //ARP RSP ԴMAC��ַΪ����MAC
        )
    {
        WAN_SEC_INFO("(%s)  arp s_ip = %d.%d.%d.%d s_addr = %02X%02X%02X%02X%02X%02X"
            , port_dev->name
            , ((char *)&arp_src_ip)[0], ((char *)&arp_src_ip)[1]
            , ((char *)&arp_src_ip)[2], ((char *)&arp_src_ip)[3] /* ��ӡIP��ַ */
            ,((char *)(arp + 1))[0],((char *)(arp + 1))[1],((char *)(arp + 1))[2] /* MAC */
            ,((char *)(arp + 1))[3],((char *)(arp + 1))[4],((char *)(arp + 1))[5] /* MAC */
            );
        is_arp_spoofing_pkt = 1;
    }
    return (is_arp_spoofing_pkt);
}
EXPORT_SYMBOL(wlan_check_arp_spoofing);

/*****************************************************************************
 ��������  : wl_chk_pkt_inBSS
 ��������  : �ṩ��BCM43236оƬ����ʹ�ã������ж�STA->STA�ı����Ƿ�����arp��ƭ���ж�
 �������  : *p: �ð���skbָ�� ,*from_device: wlan�ӿڵ�net_device�ṹָ��
 �������  : NA
 �� �� ֵ  : 0:����ARP��ƭ���ģ�1: ��ARP��ƭ����
*****************************************************************************/
int wl_chk_pkt_inBSS(struct net_device *from_device, void *p)
{ 
    if ((NULL == from_device) || (NULL == p))
    {
        return 0;
    }
    return wlan_check_arp_spoofing(from_device, (const struct sk_buff*)p);
}
EXPORT_SYMBOL(wl_chk_pkt_inBSS);

