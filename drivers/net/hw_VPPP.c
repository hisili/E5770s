

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/wakelock.h>
#include <linux/icmp.h>
#include <linux/udp.h>
#include <linux/ip.h>
#include <linux/in.h>

#include <linux/device.h>

#define IPV4_ONLY_MODE    0
#define IPV6_ONLY_MODE    1
#define IPV4_IPV6_MODE     2      /* IPV4IPV6˫ջ*/

#define DEVICE_INACTIVE      0
#define DEVICE_ACTIVE        1
#define RMNET_DATA_LEN 1500
#define HEADROOM_FOR_BAM   8 /* for mux header */
#define HEADROOM_FOR_QOS    8
#define TAILROOM            8 /* for padding by mux layer */
#define MAC_HEAD_LENGTH        14
 /* ��ջ���ݰ�����rmnet0 ,˫ջipv4���ݰ���rmnet0, 
      ipv6���ݰ� ��rmnet1  */
/*����ֻ��ipv4�ӿ�Ϊppp0*/      

#define CRADLE_PPP_IF  "ppp0"
#define RMNET0_NAME     "rmnet0"  
#define RMNET1_NAME     "rmnet1"  

extern netdev_tx_t hw_ppp_xmit(struct sk_buff *skb, struct net_device *dev);

/* IPV4 ���ݰ���MACͷ,ԴMAC��HW_RMNET2��MAC��ַ,Ŀ��MAC��ַ�������*/
char g_ipv4_mac_head[MAC_HEAD_LENGTH] = {0x58, 0x02, 0x03, 0x04, 0x05, 0x18,
                                                                        0x00, 0x11, 0x09, 0x64, 0x01, 0x01,0x08,0x00};
/* IPV6 ���ݰ���MACͷ,ԴMAC��HW_RMNET2��MAC��ַ,Ŀ��MAC��ַ�������*/
char g_ipv6_mac_head[MAC_HEAD_LENGTH] = {0x58, 0x02, 0x03, 0x04, 0x05, 0x16,
                                                                        0x00, 0x11, 0x09, 0x64, 0x01, 0x01,0x86,0xDD};

/* ���浱ǰ���ŵ�IPģʽ */
int g_currentIPMode = IPV4_ONLY_MODE;/*heshoujun debug*/
/* ����ipv4��Ӧ�豸��index*/
int g_ipv4index = 0;
/* ����ipv6��Ӧ�豸��index */
int g_ipv6index = 0;
/* ָ��ipv4��Ӧ�豸��ָ�� */
struct net_device *g_ipv4_dev = NULL;
/* ָ��ipv6��Ӧ�豸��ָ�� */
struct net_device *g_ipv6_dev = NULL;

struct rmnet2_private {
        struct net_device_stats stats;
        uint32_t ch_id;

        struct sk_buff *waiting_for_ul_skb;
        spinlock_t lock;
        spinlock_t tx_queue_lock;
        struct tasklet_struct tsklt;
        u32 operation_mode; /* IOCTL specified mode (protocol, QoS header) */
        uint8_t device_up;
        uint8_t in_reset;
};

#if 0
/*************************************************
  Function:       hw_rmnet2_write_ipmode
  Description:   sysfsд�ļ��ӿں���
  Calls:            
  Called By:     
  Input:           
  Output:         g_currentIPMode ��д���ļ������ݱ�����ȫ�ֱ�����
  Return:         count д���ֽ���      
*************************************************/
static int hw_rmnet2_write_ipmode(struct device *dev, struct device_attribute *attr,
                            char *buf, size_t count)
{
    int ipmode = 0;
    ipmode  = simple_strtoul(buf, NULL, 0);
    if (ipmode >= IPV4_ONLY_MODE && ipmode <= IPV4_IPV6_MODE)
    {
        g_currentIPMode = ipmode;
        //printk("ipv6_ifindex = %d\n",g_currentIPMode);
    }
    return count;      
}

/*************************************************
  Function:       hw_rmnet2_read_ipmode
  Description:   sysfs���ļ��ӿں���
  Calls:            
  Called By:     
  Input:           
  Output:         ��g_currentIPModeȫ�ֱ��������ݷ��ظ��û��ؼ�
  Return:         count д���ֽ���       
*************************************************/
static int hw_rmnet2_read_ipmode(struct device *dev, struct device_attribute *attr,
                                char *buf)
{
    return sprintf(buf, "%d\n", g_currentIPMode);
}

/*************************************************
  Function:       hw_rmnet2_write_ipv4index
  Description:   sysfsд�ļ��ӿں���
  Calls:            
  Called By:     
  Input:           
  Output:        
  Return:         count д���ֽ���      
*************************************************/
static int hw_rmnet2_write_ipv4index(struct device *dev, struct device_attribute *attr,
                            char *buf, size_t count)
{
    int devindex = 0;
    devindex  = simple_strtoul(buf, NULL, 0);
    if (devindex > 0)
    {
        g_ipv4index = devindex;
        g_ipv4_dev = dev_get_by_index(&init_net, g_ipv4index);
    }
    return count;      
}

/*************************************************
  Function:       hw_rmnet2_read_ipv4index
  Description:   sysfs���ļ��ӿں���
  Calls:            
  Called By:     
  Input:           
  Output:         
  Return:         count д���ֽ���       
*************************************************/
static int hw_rmnet2_read_ipv4index(struct device *dev, struct device_attribute *attr,
                                char *buf)
{
    return sprintf(buf, "%d\n", g_ipv4index);
}

/*************************************************
  Function:       hw_rmnet2_write_ipv6_index
  Description:   sysfsд�ļ��ӿں���
  Calls:            
  Called By:     
  Input:           
  Output:         g_currentIPMode ��д���ļ������ݱ�����ȫ�ֱ�����
  Return:         count д���ֽ���      
*************************************************/
static int hw_rmnet2_write_ipv6index(struct device *dev, struct device_attribute *attr,
                            char *buf, size_t count)
{
    int devindex = 0;
    devindex  = simple_strtoul(buf, NULL, 0);
    if (devindex > 0)
    {
        g_ipv6index = devindex;
        g_ipv6_dev = dev_get_by_index(&init_net, g_ipv6index);
    }
    return count;      
}

/*************************************************
  Function:       hw_rmnet2_read_ipv6index
  Description:   sysfs���ļ��ӿں���
  Calls:            
  Called By:     
  Input:           
  Output:         
  Return:         count д���ֽ���       
*************************************************/
static int hw_rmnet2_read_ipv6index(struct device *dev, struct device_attribute *attr,
                                char *buf)
{
    return sprintf(buf, "%d\n", g_ipv6index);
}

static DEVICE_ATTR(ipmode, S_IWUSR | S_IRUSR , hw_rmnet2_read_ipmode, hw_rmnet2_write_ipmode);
static DEVICE_ATTR(ipv4_index, S_IWUSR | S_IRUSR , hw_rmnet2_read_ipv4index, hw_rmnet2_write_ipv4index);
static DEVICE_ATTR(ipv6_index, S_IWUSR | S_IRUSR , hw_rmnet2_read_ipv6index, hw_rmnet2_write_ipv6index);

static struct attribute *hw_rmnet2_attributes[] = {
    &dev_attr_ipmode.attr,
    &dev_attr_ipv4_index.attr,
    &dev_attr_ipv6_index.attr,
    NULL
};

static const struct attribute_group hw_rmnet2_group = {
  .attrs = hw_rmnet2_attributes,
};
#endif

static struct net_device *hw_rmnet2_dev;
static int hw_rmnet2_open(struct net_device *dev)
{
    struct rmnet2_private *p = netdev_priv(dev);
    p->device_up = DEVICE_ACTIVE;
    netif_start_queue(dev);
    return 0;
}

static int hw_rmnet2_stop(struct net_device *dev)
{
    struct rmnet2_private *p = netdev_priv(dev);
    if (p->device_up) 
    {
	/* do not close rmnet port once up,  this causes
	remote side to hang if tried to open again */
        p->device_up = DEVICE_INACTIVE;
    }
    netif_stop_queue(dev);
    return 0;
}

static struct net_device_stats *hw_rmnet2_get_stats(struct net_device *dev)
{
    struct rmnet2_private *p = netdev_priv(dev);
    return &p->stats;
}

static int hw_rmnet2_xmit(struct sk_buff *skb, struct net_device *dev)
{
    struct net_device *dev_rmnet0;
    struct net_device *dev_rmnet1;
    int rc = 0;
    struct rmnet2_private *p = netdev_priv(hw_rmnet2_dev);  

    /* �Ƴ�MACͷ */
    skb_pull(skb, MAC_HEAD_LENGTH);
       
    if (IPV4_ONLY_MODE == g_currentIPMode)
    {
        skb->dev =  dev_get_by_name(&init_net, CRADLE_PPP_IF);//g_ipv4_dev;

	    if(NULL == skb->dev)
	    {
		    printk("skb->dev is NULL!\n");
	    }
        else
        {
            dev_put(skb->dev);
        }
    }
    else if (IPV6_ONLY_MODE == g_currentIPMode)
    {
        skb->dev = g_ipv6_dev;
    }
    else if (IPV4_IPV6_MODE == g_currentIPMode)
    {     
        if (htons(ETH_P_IPV6) == skb->protocol)
        {
            skb->dev = g_ipv6_dev;
        }
        else
        {
            skb->dev = g_ipv4_dev;
        }
    }
    else
    {
        p->stats.tx_dropped++;
        dev_kfree_skb_irq(skb);
        return 0;
    }
    if (NULL == skb->dev)
    {
        p->stats.tx_dropped++;
        dev_kfree_skb_irq(skb);
        return 0;
    }
    p->stats.tx_packets++;
    p->stats.tx_bytes += skb->len;
    rc = hw_ppp_xmit(skb, skb->dev);/*heshoujun debug*/
    return rc;
}

/*************************************************
  Function:       hw_rmnet2_rx
  Description:   hw_rmnet2�豸�������ݰ�����
                      ���յ������ݰ�����MAC ͷ��
                      ����Э��ջ
  Calls:            
  Called By:     bam_recv_notify
  Input:           skb ���ݰ�
  Output:         
  Return:         count д���ֽ���    
*************************************************/
void hw_rmnet2_rx(struct sk_buff *skb)
{
    /*ͳ�����ݰ�*/
    struct rmnet2_private *p = netdev_priv(hw_rmnet2_dev);
    unsigned char *tmpskbdata = NULL;
    skb->dev = hw_rmnet2_dev;
    
    /* ����MACͷ */ 
    if (MAC_HEAD_LENGTH <= skb->data - skb->head)
    {
        tmpskbdata = skb_push(skb, MAC_HEAD_LENGTH);
        if (htons(ETH_P_IPV6) == skb->protocol)
        {
            memcpy(tmpskbdata, g_ipv6_mac_head, MAC_HEAD_LENGTH);
        }
        else if (htons(ETH_P_IP) == skb->protocol)
        {
            memcpy(tmpskbdata, g_ipv4_mac_head, MAC_HEAD_LENGTH);
        }
        else
        {
            p->stats.rx_dropped++;
            dev_kfree_skb_irq(skb);
            return;
        }            
        skb->protocol = eth_type_trans(skb, hw_rmnet2_dev);
                 
        p->stats.rx_packets++;
        p->stats.rx_bytes += skb->len;
        /* Deliver to network stack */                  
        netif_rx(skb);
    }
    else
    {
        p->stats.rx_dropped++;
        dev_kfree_skb_irq(skb);
    }
}

static const struct net_device_ops hw_rmnet2_ops = {
        .ndo_open = hw_rmnet2_open,
        .ndo_stop = hw_rmnet2_stop,
        .ndo_start_xmit = hw_rmnet2_xmit,
        .ndo_get_stats = hw_rmnet2_get_stats,
        .ndo_set_mac_address = eth_mac_addr,
        .ndo_validate_addr = eth_validate_addr,
        .ndo_change_mtu = eth_change_mtu,
};

static void __init hw_rmnet2_setup(struct net_device *dev)
{ 
    /* Using Ethernet mode by default */
    dev->netdev_ops = &hw_rmnet2_ops;
    ether_setup(dev);

    /* set this after calling ether_setup */
    dev->mtu = RMNET_DATA_LEN;
    dev->needed_headroom = HEADROOM_FOR_BAM + HEADROOM_FOR_QOS ;
    dev->needed_tailroom = TAILROOM;
    random_ether_addr(dev->dev_addr);

    dev->watchdog_timeo = 1000; /* 10 seconds? */
}


static int __init hw_rmnet2_init(void)
{
    int ret;
    struct net_device *dev;

    dev = alloc_netdev(sizeof(struct rmnet2_private), "VPPP", hw_rmnet2_setup);

    if (!dev)
    {
        return -ENOMEM;
    }
    
    dev_net_set(dev, &init_net);
    ret = register_netdev(dev);
    if (ret) 
    {
        free_netdev(dev);
        return ret;
    }
    hw_rmnet2_dev = dev;
    //sysfs_create_group(&(dev->dev.kobj), &hw_rmnet2_group);

    return 0;
}

static void __exit hw_rmnet2_cleanup(void)
{
    unregister_netdev(hw_rmnet2_dev);
    free_netdev(hw_rmnet2_dev);
}

module_init(hw_rmnet2_init);
module_exit(hw_rmnet2_cleanup);
EXPORT_SYMBOL(hw_rmnet2_rx);
