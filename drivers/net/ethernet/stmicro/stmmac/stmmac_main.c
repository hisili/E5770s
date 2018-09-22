/*******************************************************************************
  This is the driver for the ST MAC 10/100/1000 on-chip Ethernet controllers.
  ST Ethernet IPs are built around a Synopsys IP Core.

	Copyright(C) 2007-2011 STMicroelectronics Ltd

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along with
  this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin St - Fifth Floor, Boston, MA 02110-1301 USA.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

  Author: Giuseppe Cavallaro <peppe.cavallaro@st.com>

  Documentation available at:
	http://www.stlinux.com
  Support available at:
	https://bugzilla.stlinux.com/
*******************************************************************************/

#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/skbuff.h>
#include <linux/ethtool.h>
#include <linux/if_ether.h>
#include <linux/crc32.h>
#include <linux/mii.h>
#include <linux/if.h>
#include <linux/if_vlan.h>
#include <linux/dma-mapping.h>
#include <linux/slab.h>
#include <linux/prefetch.h>
#ifdef CONFIG_STMMAC_DEBUG_FS
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#endif
#include "stmmac.h"
#include "stmmac_debug.h"
#ifdef CONFIG_GMAC_TEST
#include "stmmac_test.h"
#endif
#if (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD)
#include <linux/kthread.h>
#endif
#if (FEATURE_ON == MBB_FEATURE_ETH)
#if (FEATURE_ON == MBB_FEATURE_ETH_SWITCH)
#define   NET_DEVICE_NAME   "et0"
#else
#define   NET_DEVICE_NAME   "eth0"
#endif

extern int mbb_check_net_upgrade(struct sk_buff *skb);
extern int mbb_mac_clone_rx_restore(struct sk_buff *skb);
extern int mbb_mac_clone_tx_save(struct sk_buff *skb);
extern int mbb_get_eth_macAddr(char *eth_macAddr);
#if (FEATURE_ON == MBB_CTF_COMMON)
extern void mbb_ctf_init(struct net_device *net);
extern int mbb_ctf_forward(struct sk_buff *skb,  struct net_device *dev);
extern void mbb_ctf_exit(struct net_device *net);
#endif
#if ((FEATURE_ON == MBB_FEATURE_FASTIP) && (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD))
extern void mbb_fastip_init(struct net_device *net);
extern int mbb_fastip_forward(struct sk_buff *skb,  struct net_device *dev);
extern void mbb_fastip_exit(struct net_device *net);
#endif
#if (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD)
static int stmmac_vendor_tx_thread_init(struct stmmac_priv *stmmac);
static int stmmac_vendor_tx_thread_uninit(struct stmmac_priv *stmmac);
int stmmac_vendor_post_skb(struct sk_buff *skb,   struct net_device *dev);
#endif
#endif

#define STMMAC_ALIGN(x)	L1_CACHE_ALIGN(x)
#define JUMBO_LEN	9000

struct stmmac_extra_stats *gmac_status;

/* Module parameters */
#if (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD)
#define TX_TIMEO 500000 
#else
#define TX_TIMEO 5000 /* default 5 seconds */
#endif
static int watchdog = TX_TIMEO;
module_param(watchdog, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(watchdog, "Transmit timeout in milliseconds");

static int debug = -1;		/* -1: default, 0: no output, 16:  all */
module_param(debug, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Message Level (0: no output, 16: all)");
#if (FEATURE_ON == MBB_FEATURE_ETH)
#ifdef BSP_CONFIG_BOARD_E5_E5770s
#define E5770_PHYADDR    (4)
int phyaddr = E5770_PHYADDR;
#else
int phyaddr = 0;
#endif

#else
int phyaddr = -1;
#endif
module_param(phyaddr, int, S_IRUGO);
MODULE_PARM_DESC(phyaddr, "Physical device address");

#define DMA_TX_SIZE 256
static int dma_txsize = DMA_TX_SIZE;
module_param(dma_txsize, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dma_txsize, "Number of descriptors in the TX list");

#define DMA_RX_SIZE 256
static int dma_rxsize = DMA_RX_SIZE;
module_param(dma_rxsize, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(dma_rxsize, "Number of descriptors in the RX list");

static int flow_ctrl = FLOW_OFF;
module_param(flow_ctrl, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(flow_ctrl, "Flow control ability [on/off]");

static int pause = PAUSE_TIME;
module_param(pause, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(pause, "Flow Control Pause Time");

#define TC_DEFAULT 64
static int tc = TC_DEFAULT;
module_param(tc, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(tc, "DMA threshold control value");

/* Pay attention to tune this parameter; take care of both
 * hardware capability and network stabitily/performance impact.
 * Many tests showed that ~4ms latency seems to be good enough. */
#ifdef CONFIG_STMMAC_TIMER
#define DEFAULT_PERIODIC_RATE	256
static int tmrate = DEFAULT_PERIODIC_RATE;
module_param(tmrate, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(tmrate, "External timer freq. (default: 256Hz)");
#endif

#define DMA_BUFFER_SIZE	BUF_SIZE_2KiB
static int buf_sz = DMA_BUFFER_SIZE;
module_param(buf_sz, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(buf_sz, "DMA buffer size");

static const u32 default_msg_level = (NETIF_MSG_DRV | NETIF_MSG_PROBE |
				      NETIF_MSG_LINK | NETIF_MSG_IFUP |
				      NETIF_MSG_IFDOWN | NETIF_MSG_TIMER);

static irqreturn_t stmmac_interrupt(int irq, void *dev_id);

#ifdef CONFIG_STMMAC_DEBUG_FS
static int stmmac_init_fs(struct net_device *dev);
static void stmmac_exit_fs(void);
#endif

#if (FEATURE_ON == MBB_FEATURE_ETH)
unsigned int gmac_msg_level = GMAC_LEVEL_ERR;
EXPORT_SYMBOL(gmac_msg_level);
#else
#ifdef CONFIG_GMAC_DEBUG
unsigned int gmac_msg_level = GMAC_LEVEL_ERR;
#endif
#endif

#if (FEATURE_ON == MBB_FEATURE_ETH)
int riwt_value = 1;
#else
int riwt_value = MIN_DMA_RIWT;
#endif

int rx_irq_flag = 1;


void set_riwt_value(unsigned int cnt)
{	
	riwt_value = cnt;
}

void set_rx_irq_flag(unsigned int cnt)
{	
	rx_irq_flag = cnt;
}

void set_gmac_msg(unsigned int level)
{
	gmac_msg_level = level;
}
EXPORT_SYMBOL(set_gmac_msg);

unsigned int get_gmac_msg(void)
{
	printk("level : %x\n",gmac_msg_level);
    return gmac_msg_level;
}
EXPORT_SYMBOL(get_gmac_msg);

#if (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD)
uint stmmac_pkt_txthread_flag = true;
uint stmmac_get_txthread_flag(void)
{
    printk("stmmac_pkt_txthread_flag:%d\n", stmmac_pkt_txthread_flag);
    return 0;
}
uint stmmac_set_txthread_flag(uint flag)
{
    stmmac_pkt_txthread_flag = flag;
    return 0;
}
#endif

/**
 * stmmac_verify_args - verify the driver parameters.
 * Description: it verifies if some wrong parameter is passed to the driver.
 * Note that wrong parameters are replaced with the default values.
 */
static void stmmac_verify_args(void)
{
	if (unlikely(watchdog < 0))
		watchdog = TX_TIMEO;
	if (unlikely(dma_rxsize < 0))
		dma_rxsize = DMA_RX_SIZE;
	if (unlikely(dma_txsize < 0))
		dma_txsize = DMA_TX_SIZE;
	if (unlikely((buf_sz < DMA_BUFFER_SIZE) || (buf_sz > BUF_SIZE_16KiB)))
		buf_sz = DMA_BUFFER_SIZE;
	if (unlikely(flow_ctrl > 1))
		flow_ctrl = FLOW_AUTO;
	else if (likely(flow_ctrl < 0))
		flow_ctrl = FLOW_OFF;
	if (unlikely((pause < 0) || (pause > 0xffff)))
		pause = PAUSE_TIME;
}


/* minimum number of free TX descriptors required to wake up TX process */
#define STMMAC_TX_THRESH(x)	(x->dma_tx_size/4)

static inline u32 stmmac_tx_avail(struct stmmac_priv *priv)
{
	return priv->dirty_tx + priv->dma_tx_size - priv->cur_tx - 1;
}

/* On some ST platforms, some HW system configuraton registers have to be
 * set according to the link speed negotiated.
 */
static inline void stmmac_hw_fix_mac_speed(struct stmmac_priv *priv)
{
	struct phy_device *phydev = priv->phydev;

	if (likely(priv->plat->fix_mac_speed))
		priv->plat->fix_mac_speed(priv->plat->bsp_priv,
					  phydev->speed);
}

/**
 * stmmac_adjust_link
 * @dev: net device structure
 * Description: it adjusts the link parameters.
 */
static void stmmac_adjust_link(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;
	unsigned long flags;
	int new_state = 0;
	unsigned int fc = priv->flow_ctrl, pause_time = priv->pause;

	if (phydev == NULL)
		return;

	GMAC_TRACE(("stmmac_adjust_link: called.  address %d link %d\n",
	    phydev->addr, phydev->link));

	spin_lock_irqsave(&priv->lock, flags);
	if (phydev->link) {
		u32 ctrl = readl(priv->ioaddr + MAC_CTRL_REG);

		/* Now we make sure that we can be in full duplex mode.
		 * If not, we operate in half-duplex mode. */
		if (phydev->duplex != priv->oldduplex) {
			new_state = 1;
			if (!(phydev->duplex))
				ctrl &= ~priv->hw->link.duplex;
			else
				ctrl |= priv->hw->link.duplex;
			priv->oldduplex = phydev->duplex;
		}
		/* Flow Control operation */
		if (phydev->pause)
			priv->hw->mac->flow_ctrl(priv->ioaddr, phydev->duplex,
						 fc, pause_time);

		if (phydev->speed != priv->speed) {
			new_state = 1;
			switch (phydev->speed) {
			case 1000:
				if (likely(priv->plat->has_gmac))
					ctrl &= ~priv->hw->link.port;
					stmmac_hw_fix_mac_speed(priv);
				break;
			case 100:
			case 10:
				if (priv->plat->has_gmac) {
					ctrl |= priv->hw->link.port;
					if (phydev->speed == SPEED_100) {
						ctrl |= priv->hw->link.speed;
					} else {
						ctrl &= ~(priv->hw->link.speed);
					}
				} else {
					ctrl &= ~priv->hw->link.port;
				}
				stmmac_hw_fix_mac_speed(priv);
				break;
			default:
				if (netif_msg_link(priv))
					GMAC_WARNING(("%s: Speed (%d) is not 10"
				       " or 100!\n", dev->name, phydev->speed));
				break;
			}

			priv->speed = phydev->speed;
		}

       // ctrl |= priv->hw->link.linkup;
		writel(ctrl, priv->ioaddr + MAC_CTRL_REG);

		if (!priv->oldlink) {
			new_state = 1;
			priv->oldlink = 1;
		}
	} else if (priv->oldlink) {
		new_state = 1;
		priv->oldlink = 0;
		priv->speed = 0;
		priv->oldduplex = -1;
	}
#ifndef CONFIG_EMU_MODE
	if (new_state && netif_msg_link(priv))
		phy_print_status(phydev);
#endif
spin_unlock_irqrestore(&priv->lock, flags);

	GMAC_TRACE(("%s:stmmac_adjust_link: exiting\n",__FUNCTION__));
}
#ifndef CONFIG_EMU_MODE
/**
 * stmmac_init_phy - PHY initialization
 * @dev: net device structure
 * Description: it initializes the driver's PHY state, and attaches the PHY
 * to the mac driver.
 *  Return value:
 *  0 on success
 */
static int stmmac_init_phy(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	struct phy_device *phydev;
	char phy_id[MII_BUS_ID_SIZE + 3];
	char bus_id[MII_BUS_ID_SIZE];
	int interface = priv->plat->interface;
	priv->oldlink = 0;
	priv->speed = 0;
	priv->oldduplex = -1;

	snprintf(bus_id, MII_BUS_ID_SIZE, "stmmac-%x", priv->plat->bus_id);
	snprintf(phy_id, MII_BUS_ID_SIZE + 3, PHY_ID_FMT, bus_id,
		 priv->plat->phy_addr);
	GMAC_DBG(("stmmac_init_phy:  trying to attach to %s\n", phy_id));

	phydev = phy_connect(dev, phy_id, &stmmac_adjust_link, 0, interface);

	if (IS_ERR(phydev)) {
		GMAC_ERR(("%s: Could not attach to PHY\n", dev->name));
		return PTR_ERR(phydev);
	}

	/* Stop Advertising 1000BASE Capability if interface is not GMII */
	if ((interface == PHY_INTERFACE_MODE_MII) ||
	    (interface == PHY_INTERFACE_MODE_RMII))
		phydev->advertising &= ~(SUPPORTED_1000baseT_Half |
					 SUPPORTED_1000baseT_Full);

	/*
	 * Broken HW is sometimes missing the pull-up resistor on the
	 * MDIO line, which results in reads to non-existent devices returning
	 * 0 rather than 0xffff. Catch this here and treat 0 as a non-existent
	 * device as well.
	 * Note: phydev->phy_id is the result of reading the UID PHY registers.
	 */
	if (phydev->phy_id == 0) {
		phy_disconnect(phydev);
		return -ENODEV;
	}
	GMAC_DBG(("stmmac_init_phy:  %s: attached to PHY (UID 0x%x)"
		 " Link = %d\n", dev->name, phydev->phy_id, phydev->link));

	priv->phydev = phydev;

	return 0;
}
#else
#define GMAC_CONTROL_PS		0x00008000 /* Port Select 0:GMI 1:MII */
#define GMAC_CONTROL_FES	0x00004000 /* Speed 0:10 1:100 */
#define GMAC_CONTROL_LM		0x00001000 /* Loop-back mode */
#define GMAC_CONTROL_DM		0x00000800 /* Duplex Mode */
#define GMAC_CONTROL_LUD	0x00000100 /* Link up/down */

void force_gmac_to_loop(struct net_device *dev)
{
	unsigned int ctrl;
	struct stmmac_priv *priv = netdev_priv(dev);
	ctrl = readl(priv->ioaddr + MAC_CTRL_REG);
	ctrl |= GMAC_CONTROL_LM;
	ctrl |= GMAC_CONTROL_LUD;
	ctrl |= GMAC_CONTROL_DM;

	GMAC_WARNING(("force_gmac_to_loop:wirte register value is  0x%x \n", ctrl));

	writel(ctrl, priv->ioaddr + MAC_CTRL_REG);
	
	ctrl = readl(priv->ioaddr + MAC_CTRL_REG);

	GMAC_WARNING(("force_gmac_to_loop:GMAC CTRL register value is  0x%x \n", ctrl));
}


static int stmmac_init_fake_phy(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = NULL;
	char phy_id[MII_BUS_ID_SIZE + 3];
	char bus_id[MII_BUS_ID_SIZE];
	int interface = priv->plat->interface;
	unsigned int ctrl;
	
	priv->oldlink = 0;
	priv->speed = 0;
	priv->oldduplex = -1;

	phydev = kmalloc(sizeof(struct phy_device) ,GFP_ATOMIC);
	if(NULL == phydev){
		return -ENXIO;
	}
	snprintf(bus_id, MII_BUS_ID_SIZE, "stmmac-%x", priv->plat->bus_id);
	snprintf(phy_id, MII_BUS_ID_SIZE + 3, PHY_ID_FMT, bus_id,
		 priv->plat->phy_addr);
	GMAC_DBG(("stmmac_init_phy:  trying to attach to %s\n", phy_id));

	ctrl = readl(priv->ioaddr + MAC_CTRL_REG);
	priv->hw->link.port &= ~GMAC_CONTROL_PS; 	
	priv->hw->link.duplex =GMAC_CONTROL_DM;
	
	phydev->duplex = GMAC_CONTROL_DM;
	priv->oldduplex = phydev->duplex;

	/* Force full duplex mode.*/
	ctrl |= priv->hw->link.duplex;
	ctrl |= priv->hw->link.port;
	
	/*add loopback*/
	ctrl |= GMAC_CONTROL_LM;
	ctrl |= GMAC_CONTROL_LUD;
	
	stmmac_hw_fix_mac_speed(priv);

	writel(ctrl, priv->ioaddr + MAC_CTRL_REG);

	ctrl = readl(priv->ioaddr + MAC_CTRL_REG);
	GMAC_WARNING(("stmmac_init_fake_phy:GMAC CTRL register value is  0x%x \n", ctrl));
	if (!priv->oldlink) {
		priv->oldlink = 1;
	}
	
	priv->phydev = phydev;

	return 0;
}
#endif
/**
 * display_ring
 * @p: pointer to the ring.
 * @size: size of the ring.
 * Description: display all the descriptors within the ring.
 */
static void display_ring(struct dma_desc *p, int size)
{
	struct tmp_s {
		u64 a;
		unsigned int b;
		unsigned int c;
	};
	int i;
	for (i = 0; i < size; i++) {
		struct tmp_s *x = (struct tmp_s *)(p + i);
		GMAC_INFO(("\t%d [0x%x]: DES0=0x%x DES1=0x%x BUF1=0x%x BUF2=0x%x",
		       i, /*(unsigned int)virt_to_phys(*/(unsigned int)&p[i]/*)*/,
		       (unsigned int)(x->a), (unsigned int)((x->a) >> 32),
		       x->b, x->c));
		GMAC_INFO(("\n"));
	}
}

#if 0
static int stmmac_set_bfsize(int mtu, int bufsize)
{
	int ret = bufsize;

	if (mtu >= BUF_SIZE_4KiB)
		ret = BUF_SIZE_8KiB;
	else if (mtu >= BUF_SIZE_2KiB)
		ret = BUF_SIZE_4KiB;
	else if (mtu >= DMA_BUFFER_SIZE)
		ret = BUF_SIZE_2KiB;
	else
		ret = DMA_BUFFER_SIZE;

	return ret;
}
#endif

/**
 * init_dma_desc_rings - init the RX/TX descriptor rings
 * @dev: net device structure
 * Description:  this function initializes the DMA RX/TX descriptors
 * and allocates the socket buffers. It suppors the chained and ring
 * modes.
 */
static void init_dma_desc_rings(struct net_device *dev)
{
	int i;
	struct stmmac_priv *priv = netdev_priv(dev);
	struct sk_buff *skb;
	unsigned int txsize = priv->dma_tx_size;
	unsigned int rxsize = priv->dma_rx_size;
	unsigned int bfsize;
	int dis_ic = rx_irq_flag;
	int des3_as_data_buf = 0;

	/* Set the max buffer size according to the DESC mode
	 * and the MTU. Note that RING mode allows 16KiB bsize. */
	bfsize = priv->hw->ring->set_16kib_bfsize(dev->mtu);

	if (bfsize == BUF_SIZE_16KiB)
		des3_as_data_buf = 1;
	else
        bfsize = BUF_SIZE_1_8kiB;
		//bfsize = stmmac_set_bfsize(dev->mtu, priv->dma_buf_sz);

#ifdef CONFIG_STMMAC_TIMER
	/* Disable interrupts on completion for the reception if timer is on */
	if (likely(priv->tm->enable))
		dis_ic = 1;
#endif

    GMAC_TRACE(("stmmac: txsize %d, rxsize %d, bfsize %d\n",
	    txsize, rxsize, bfsize));

	priv->rx_skbuff_dma = kmalloc(rxsize * sizeof(dma_addr_t), GFP_KERNEL);
	priv->rx_skbuff =
	    kmalloc(sizeof(struct sk_buff *) * rxsize, GFP_KERNEL);
	priv->dma_rx =
	    (struct dma_desc *)dma_alloc_coherent(priv->device,
						  rxsize *
						  sizeof(struct dma_desc),
						  &priv->dma_rx_phy,
						  GFP_KERNEL);
	priv->tx_skbuff = kmalloc(sizeof(struct sk_buff *) * txsize,
				       GFP_KERNEL);
	priv->dma_tx =
	    (struct dma_desc *)dma_alloc_coherent(priv->device,
						  txsize *
						  sizeof(struct dma_desc),
						  &priv->dma_tx_phy,
						  GFP_KERNEL);

	if ((priv->dma_rx == NULL) || (priv->dma_tx == NULL)) {
		GMAC_ERR(("%s:ERROR allocating the DMA Tx/Rx desc\n", __func__));
		return;
	}

    GMAC_TRACE(("stmmac (%s) DMA desc: virt addr (Rx %p, "
	    "Tx %p)\n\tDMA phy addr (Rx 0x%08x, Tx 0x%08x)\n",
	    dev->name, priv->dma_rx, priv->dma_tx,
	    (unsigned int)priv->dma_rx_phy, (unsigned int)priv->dma_tx_phy));

    /* RX INITIALIZATION */
	GMAC_TRACE(("stmmac: SKB addresses:\n"
			 "skb\t\tskb data\tdma data\n"));

	for (i = 0; i < rxsize; i++) {
		struct dma_desc *p = priv->dma_rx + i;

		skb = __netdev_alloc_skb(dev, bfsize + NET_IP_ALIGN,
					 GFP_KERNEL);
		if (unlikely(skb == NULL)) {
			GMAC_ERR(("%s: Rx init fails; skb is NULL\n", __func__));
			break;
		}
		skb_reserve(skb, NET_IP_ALIGN);
		priv->rx_skbuff[i] = skb;
		priv->rx_skbuff_dma[i] = dma_map_single(priv->device, skb->data,
						bfsize, DMA_FROM_DEVICE);

		p->des2 = priv->rx_skbuff_dma[i];

		priv->hw->ring->init_desc3(des3_as_data_buf, p);

        GMAC_TRACE(("[%p]\t[%p]\t[%x]\n", priv->rx_skbuff[i],
			priv->rx_skbuff[i]->data, priv->rx_skbuff_dma[i]));
	}
	priv->cur_rx = 0;
	priv->dirty_rx = (unsigned int)(i - rxsize);
	priv->dma_buf_sz = bfsize;
	buf_sz = bfsize;

	/* TX INITIALIZATION */
	for (i = 0; i < txsize; i++) {
		priv->tx_skbuff[i] = NULL;
		priv->dma_tx[i].des2 = 0;
	}

	/* In case of Chained mode this sets the des3 to the next
	 * element in the chain */
	priv->hw->ring->init_dma_chain(priv->dma_rx, priv->dma_rx_phy, rxsize);
	priv->hw->ring->init_dma_chain(priv->dma_tx, priv->dma_tx_phy, txsize);

	priv->dirty_tx = 0;
	priv->cur_tx = 0;

	/* Clear the Rx/Tx descriptors */
	priv->hw->desc->init_rx_desc(priv->dma_rx, rxsize, dis_ic);
	priv->hw->desc->init_tx_desc(priv->dma_tx, txsize);

	if (netif_msg_hw(priv)) {
		GMAC_INFO(("RX descriptor ring:\n"));
		display_ring(priv->dma_rx, rxsize);
		GMAC_INFO(("TX descriptor ring:\n"));
		display_ring(priv->dma_tx, txsize);
	}
}

static void dma_free_rx_skbufs(struct stmmac_priv *priv)
{
	int i;

	for (i = 0; i < priv->dma_rx_size; i++) {
		if (priv->rx_skbuff[i]) {
			dma_unmap_single(priv->device, priv->rx_skbuff_dma[i],
					 priv->dma_buf_sz, DMA_FROM_DEVICE);
			dev_kfree_skb_any(priv->rx_skbuff[i]);
		}
		priv->rx_skbuff[i] = NULL;
	}
}

static void dma_free_tx_skbufs(struct stmmac_priv *priv)
{
	int i;

	for (i = 0; i < priv->dma_tx_size; i++) {
		if (priv->tx_skbuff[i] != NULL) {
			struct dma_desc *p = priv->dma_tx + i;
			if (p->des2)
				dma_unmap_single(priv->device, p->des2,
						 priv->hw->desc->get_tx_len(p),
						 DMA_TO_DEVICE);
			dev_kfree_skb_any(priv->tx_skbuff[i]);
			priv->tx_skbuff[i] = NULL;
		}
	}
}

static void free_dma_desc_resources(struct stmmac_priv *priv)
{
	/* Release the DMA TX/RX socket buffers */
	dma_free_rx_skbufs(priv);
	dma_free_tx_skbufs(priv);

	/* Free the region of consistent memory previously allocated for
	 * the DMA */
	dma_free_coherent(priv->device,
			  priv->dma_tx_size * sizeof(struct dma_desc),
			  priv->dma_tx, priv->dma_tx_phy);
	dma_free_coherent(priv->device,
			  priv->dma_rx_size * sizeof(struct dma_desc),
			  priv->dma_rx, priv->dma_rx_phy);
	kfree(priv->rx_skbuff_dma);
	kfree(priv->rx_skbuff);
	kfree(priv->tx_skbuff);
}

/**
 *  stmmac_dma_operation_mode - HW DMA operation mode
 *  @priv : pointer to the private device structure.
 *  Description: it sets the DMA operation mode: tx/rx DMA thresholds
 *  or Store-And-Forward capability.
 */
static void stmmac_dma_operation_mode(struct stmmac_priv *priv)
{
	if (likely(priv->plat->force_sf_dma_mode ||
		((priv->plat->tx_coe) && (!priv->no_csum_insertion)))) {
		/*
		 * In case of GMAC, SF mode can be enabled
		 * to perform the TX COE in HW. This depends on:
		 * 1) TX COE if actually supported
		 * 2) There is no bugged Jumbo frame support
		 *    that needs to not insert csum in the TDES.
		 */
		priv->hw->dma->dma_mode(priv->ioaddr,
					SF_DMA_MODE, SF_DMA_MODE);
		tc = SF_DMA_MODE;
	} else
		priv->hw->dma->dma_mode(priv->ioaddr, tc, SF_DMA_MODE);
}

/**
 * stmmac_tx:
 * @priv: private driver structure
 * Description: it reclaims resources after transmission completes.
 */
static void stmmac_tx(struct stmmac_priv *priv)
{
	unsigned int txsize = priv->dma_tx_size;

	spin_lock(&priv->tx_lock);

	while (priv->dirty_tx != priv->cur_tx) {
		int last;
		unsigned int entry = priv->dirty_tx % txsize;
		struct sk_buff *skb = priv->tx_skbuff[entry];
		struct dma_desc *p = priv->dma_tx + entry;

		/* Check if the descriptor is owned by the DMA. */
		if (priv->hw->desc->get_tx_owner(p))
			break;

		/* Verify tx error by looking at the last segment */
		last = priv->hw->desc->get_tx_ls(p);
		if (likely(last)) {
			int tx_error =
				priv->hw->desc->tx_status(&priv->dev->stats,
							  &priv->xstats, p,
							  priv->ioaddr);
			if (likely(tx_error == 0)) {
				priv->dev->stats.tx_packets++;
				priv->xstats.tx_pkt_n++;
			} else{
				priv->dev->stats.tx_errors++;
				GMAC_WARNING(("%s: desc error. \n",__func__));
			}
		}
		GMAC_TX_DBG(("%s: curr %d, dirty %d\n", __func__,
			priv->cur_tx, priv->dirty_tx));
		if (likely(p->des2))
			dma_unmap_single(priv->device, p->des2,
					 priv->hw->desc->get_tx_len(p),
					 DMA_TO_DEVICE);
		priv->hw->ring->clean_desc3(p);

		if (likely(skb != NULL)) {
			/*
			 * If there's room in the queue (limit it to size)
			 * we add this skb back into the pool,
			 * if it's the right size.
			 */
			if ((skb_queue_len(&priv->rx_recycle) <
				priv->dma_rx_size) &&
				skb_recycle_check(skb, priv->dma_buf_sz))
				__skb_queue_head(&priv->rx_recycle, skb);
			else
				dev_kfree_skb(skb);

			priv->tx_skbuff[entry] = NULL;
		}

		priv->hw->desc->release_tx_desc(p);

		entry = (++priv->dirty_tx) % txsize;
	}
	if (unlikely(netif_queue_stopped(priv->dev) &&
		     stmmac_tx_avail(priv) > STMMAC_TX_THRESH(priv))) {
		netif_tx_lock(priv->dev);
		if (netif_queue_stopped(priv->dev) &&
		     stmmac_tx_avail(priv) > STMMAC_TX_THRESH(priv)) {
			GMAC_TX_DBG(("%s: restart transmit\n", __func__));
			netif_wake_queue(priv->dev);
		}
		netif_tx_unlock(priv->dev);
	}
	spin_unlock(&priv->tx_lock);
}

static inline void stmmac_enable_irq(struct stmmac_priv *priv)
{
#ifdef CONFIG_STMMAC_TIMER
	if (likely(priv->tm->enable))
		priv->tm->timer_start(tmrate);
	else
#endif
		priv->hw->dma->enable_dma_irq(priv->ioaddr);
}

static inline void stmmac_disable_irq(struct stmmac_priv *priv)
{
#ifdef CONFIG_STMMAC_TIMER
	if (likely(priv->tm->enable))
		priv->tm->timer_stop();
	else
#endif
		priv->hw->dma->disable_dma_irq(priv->ioaddr);
}

static int stmmac_has_work(struct stmmac_priv *priv)
{
	unsigned int has_work = 0;
	int rxret, tx_work = 0;

	rxret = priv->hw->desc->get_rx_owner(priv->dma_rx +
		(priv->cur_rx % priv->dma_rx_size));

	if (priv->dirty_tx != priv->cur_tx)
		tx_work = 1;

	if (likely(!rxret || tx_work))
		has_work = 1;

	return has_work;
}

static inline void _stmmac_schedule(struct stmmac_priv *priv)
{
	if (likely(stmmac_has_work(priv))) {
		stmmac_disable_irq(priv);
		napi_schedule(&priv->napi);
	}
}

#ifdef CONFIG_STMMAC_TIMER
void stmmac_schedule(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	priv->xstats.sched_timer_n++;

	_stmmac_schedule(priv);
}

static void stmmac_no_timer_started(unsigned int x)
{;
};

static void stmmac_no_timer_stopped(void)
{;
};
#endif

/**
 * stmmac_tx_err:
 * @priv: pointer to the private device structure
 * Description: it cleans the descriptors and restarts the transmission
 * in case of errors.
 */
static void stmmac_tx_err(struct stmmac_priv *priv)
{
	netif_stop_queue(priv->dev);

	priv->hw->dma->stop_tx(priv->ioaddr);
	dma_free_tx_skbufs(priv);
	priv->hw->desc->init_tx_desc(priv->dma_tx, priv->dma_tx_size);
	priv->dirty_tx = 0;
	priv->cur_tx = 0;
	priv->hw->dma->start_tx(priv->ioaddr);

	priv->dev->stats.tx_errors++;
	netif_wake_queue(priv->dev);
}


static void stmmac_dma_interrupt(struct stmmac_priv *priv)
{
	int status;

	status = priv->hw->dma->dma_interrupt(priv->ioaddr, &priv->xstats);
	if (likely(status == handle_tx_rx))
		_stmmac_schedule(priv);

	else if (unlikely(status == tx_hard_error_bump_tc)) {
		/* Try to bump up the dma threshold on this failure */
		if (unlikely(tc != SF_DMA_MODE) && (tc <= 256)) {
			tc += 64;
			priv->hw->dma->dma_mode(priv->ioaddr, tc, SF_DMA_MODE);
			priv->xstats.threshold = tc;
		}
	} else if (unlikely(status == tx_hard_error)){
		stmmac_tx_err(priv);
		GMAC_WARNING(("%s: interrupt hard error. \n",__func__));
	}
}

static void stmmac_mmc_setup(struct stmmac_priv *priv)
{
	unsigned int mode = /*MMC_CNTRL_RESET_ON_READ | */MMC_CNTRL_COUNTER_RESET |
			    MMC_CNTRL_PRESET | MMC_CNTRL_FULL_HALF_PRESET;

	/* Mask MMC irq, counters are managed in SW and registers
	 * are cleared on each READ eventually. */
	dwmac_mmc_intr_all_mask(priv->ioaddr);

	if (priv->dma_cap.rmon) {
		dwmac_mmc_ctrl(priv->ioaddr, mode);
		memset(&priv->mmc, 0, sizeof(struct stmmac_counters));
	} else
		GMAC_INFO((" No MAC Management Counters available\n"));
}

static u32 stmmac_get_synopsys_id(struct stmmac_priv *priv)
{
	u32 hwid = priv->hw->synopsys_uid;

	/* Only check valid Synopsys Id because old MAC chips
	 * have no HW registers where get the ID */
	if (likely(hwid)) {
		u32 uid = ((hwid & 0x0000ff00) >> 8);
		u32 synid = (hwid & 0x000000ff);

		GMAC_INFO(("stmmac - user ID: 0x%x, Synopsys ID: 0x%x\n",
			uid, synid));

		return synid;
	}
	return 0;
}

/**
 * stmmac_selec_desc_mode
 * @dev : device pointer
 * Description: select the Enhanced/Alternate or Normal descriptors */
static void stmmac_selec_desc_mode(struct stmmac_priv *priv)
{
	if (priv->plat->enh_desc) {
		GMAC_INFO((" Enhanced/Alternate descriptors\n"));
		priv->hw->desc = &enh_desc_ops;
	} else {
		GMAC_INFO((" Normal descriptors\n"));
		priv->hw->desc = &ndesc_ops;
	}
}

/**
 * stmmac_get_hw_features
 * @priv : private device pointer
 * Description:
 *  new GMAC chip generations have a new register to indicate the
 *  presence of the optional feature/functions.
 *  This can be also used to override the value passed through the
 *  platform and necessary for old MAC10/100 and GMAC chips.
 */
static int stmmac_get_hw_features(struct stmmac_priv *priv)
{
	u32 hw_cap = 0;

	if (priv->hw->dma->get_hw_feature) {
		hw_cap = priv->hw->dma->get_hw_feature(priv->ioaddr);

		priv->dma_cap.mbps_10_100 = (hw_cap & DMA_HW_FEAT_MIISEL);
		priv->dma_cap.mbps_1000 = (hw_cap & DMA_HW_FEAT_GMIISEL) >> 1;
		priv->dma_cap.half_duplex = (hw_cap & DMA_HW_FEAT_HDSEL) >> 2;
		priv->dma_cap.hash_filter = (hw_cap & DMA_HW_FEAT_HASHSEL) >> 4;
		priv->dma_cap.multi_addr =
			(hw_cap & DMA_HW_FEAT_ADDMACADRSEL) >> 5;
		priv->dma_cap.pcs = (hw_cap & DMA_HW_FEAT_PCSSEL) >> 6;
		priv->dma_cap.sma_mdio = (hw_cap & DMA_HW_FEAT_SMASEL) >> 8;
		priv->dma_cap.pmt_remote_wake_up =
			(hw_cap & DMA_HW_FEAT_RWKSEL) >> 9;
		priv->dma_cap.pmt_magic_frame =
			(hw_cap & DMA_HW_FEAT_MGKSEL) >> 10;
		/* MMC */
		priv->dma_cap.rmon = (hw_cap & DMA_HW_FEAT_MMCSEL) >> 11;
		/* IEEE 1588-2002*/
		priv->dma_cap.time_stamp =
			(hw_cap & DMA_HW_FEAT_TSVER1SEL) >> 12;
		/* IEEE 1588-2008*/
		priv->dma_cap.atime_stamp =
			(hw_cap & DMA_HW_FEAT_TSVER2SEL) >> 13;
		/* 802.3az - Energy-Efficient Ethernet (EEE) */
		priv->dma_cap.eee = (hw_cap & DMA_HW_FEAT_EEESEL) >> 14;
		priv->dma_cap.av = (hw_cap & DMA_HW_FEAT_AVSEL) >> 15;
		/* TX and RX csum */
		priv->dma_cap.tx_coe = (hw_cap & DMA_HW_FEAT_TXCOESEL) >> 16;
		priv->dma_cap.rx_coe_type1 =
			(hw_cap & DMA_HW_FEAT_RXTYP1COE) >> 17;
		priv->dma_cap.rx_coe_type2 =
			(hw_cap & DMA_HW_FEAT_RXTYP2COE) >> 18;
		priv->dma_cap.rxfifo_over_2048 =
			(hw_cap & DMA_HW_FEAT_RXFIFOSIZE) >> 19;
		/* TX and RX number of channels */
		priv->dma_cap.number_rx_channel =
			(hw_cap & DMA_HW_FEAT_RXCHCNT) >> 20;
		priv->dma_cap.number_tx_channel =
			(hw_cap & DMA_HW_FEAT_TXCHCNT) >> 22;
		/* Alternate (enhanced) DESC mode*/
		priv->dma_cap.enh_desc =
			(hw_cap & DMA_HW_FEAT_ENHDESSEL) >> 24;

	}

	return hw_cap;
}

static void stmmac_check_ether_addr(struct stmmac_priv *priv)
{
	/* verify if the MAC address is valid, in case of failures it
	 * generates a random MAC address */
	if (!is_valid_ether_addr(priv->dev->dev_addr)) {
		priv->hw->mac->get_umac_addr((void __iomem *)
					     priv->dev->base_addr,
					     priv->dev->dev_addr, 0);
		if  (!is_valid_ether_addr(priv->dev->dev_addr))
			eth_hw_addr_random(priv->dev);
	}
	GMAC_WARNING(("%s: device MAC address %pM\n", priv->dev->name,
						   priv->dev->dev_addr));
}

#if (FEATURE_ON == MBB_FEATURE_ETH)
static int stmmac_mdio_init(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	int ret;

#ifndef CONFIG_EMU_MODE
    /* MDIO bus Registration */
    ret = stmmac_mdio_register(dev);
    if (ret < 0) {
        GMAC_ERR(("%s: MDIO bus (id: %d) registration failed",
             __func__, priv->plat->bus_id));
        return ret;
    }
#endif
#ifdef CONFIG_STMMAC_TIMER
    priv->tm = kzalloc(sizeof(struct stmmac_timer *), GFP_KERNEL);
    if (unlikely(priv->tm == NULL))
        return -ENOMEM;

    priv->tm->freq = tmrate;

    /* Test if the external timer can be actually used.
     * In case of failure continue without timer. */
    if (unlikely((stmmac_open_ext_timer(dev, priv->tm)) < 0)) {
        GMAC_WARNING(("stmmaceth: cannot attach the external timer.\n"));
        priv->tm->freq = 0;
        priv->tm->timer_start = stmmac_no_timer_started;
        priv->tm->timer_stop = stmmac_no_timer_stopped;
    } else
        priv->tm->enable = 1;
#endif

#ifndef CONFIG_EMU_MODE
    ret = stmmac_init_phy(dev);
    if (unlikely(ret)) {
        GMAC_ERR(("%s: Cannot attach to PHY (error: %d)\n", __func__, ret));
#ifdef CONFIG_STMMAC_TIMER
        kfree(priv->tm);
#endif
        return -ENXIO;
    }
#else
    ret = stmmac_init_fake_phy(dev);
    if(0 != ret){
        GMAC_ERR((" stmmac_init_fake_phy fail. \n"));
        return -ENXIO;
    } 
#endif

#ifndef CONFIG_EMU_MODE
    if (priv->phydev)
        phy_start(priv->phydev);
#else
    priv->phydev->state = PHY_UP;
#endif

    return 0;
}

static int stmmac_mdio_exit(struct net_device *dev)
{
    struct stmmac_priv *priv = netdev_priv(dev);

    /* Stop and disconnect the PHY */
	if (priv->phydev) {
#ifndef CONFIG_EMU_MODE
		phy_stop(priv->phydev);
		phy_disconnect(priv->phydev);
		priv->phydev = NULL;
#endif
	}

#ifdef CONFIG_STMMAC_TIMER
    /* Stop and release the timer */
    stmmac_close_ext_timer();
    if (priv->tm != NULL)
        kfree(priv->tm);
#endif

#ifndef CONFIG_EMU_MODE
    stmmac_mdio_unregister(dev);
#endif

    return 0;
}

static void stmmac_link_init(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	struct phy_device *phydev = priv->phydev;
	unsigned int fc = priv->flow_ctrl, pause_time = priv->pause;

	if (NULL == phydev)
		return;

	if (phydev->link) 
    {
		u32 ctrl = readl(priv->ioaddr + MAC_CTRL_REG);

        if (!(phydev->duplex))
			ctrl &= ~priv->hw->link.duplex;
		else
			ctrl |= priv->hw->link.duplex;
		priv->oldduplex = phydev->duplex;
		
		/* Flow Control operation */
		if (phydev->pause)
			priv->hw->mac->flow_ctrl(priv->ioaddr, phydev->duplex,
						 fc, pause_time);

    	switch (phydev->speed) {
		case 1000:
			if (likely(priv->plat->has_gmac))
				ctrl &= ~priv->hw->link.port;
				stmmac_hw_fix_mac_speed(priv);
			break;
		case 100:
		case 10:
			if (priv->plat->has_gmac) {
				ctrl |= priv->hw->link.port;
				if (phydev->speed == SPEED_100) {
					ctrl |= priv->hw->link.speed;
				} else {
					ctrl &= ~(priv->hw->link.speed);
				}
			} else {
				ctrl &= ~priv->hw->link.port;
			}
			stmmac_hw_fix_mac_speed(priv);
			break;
		default:
			break;
		}

		priv->speed = phydev->speed;
		
		writel(ctrl, priv->ioaddr + MAC_CTRL_REG);

		priv->oldlink = 1;
		
	} 
}
#endif

/**
 *  stmmac_open - open entry point of the driver
 *  @dev : pointer to the device structure.
 *  Description:
 *  This function is the open entry point of the driver.
 *  Return value:
 *  0 on success and an appropriate (-)ve integer as defined in errno.h
 *  file on failure.
 */
static int stmmac_open(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	int ret;

	stmmac_check_ether_addr(priv);

#if (FEATURE_OFF == MBB_FEATURE_ETH)
#ifndef CONFIG_EMU_MODE
	/* MDIO bus Registration */
	ret = stmmac_mdio_register(dev);
	if (ret < 0) {
		GMAC_ERR(("%s: MDIO bus (id: %d) registration failed",
			 __func__, priv->plat->bus_id));
		return ret;
	}
#endif
#ifdef CONFIG_STMMAC_TIMER
	priv->tm = kzalloc(sizeof(struct stmmac_timer *), GFP_KERNEL);
	if (unlikely(priv->tm == NULL))
		return -ENOMEM;

	priv->tm->freq = tmrate;

	/* Test if the external timer can be actually used.
	 * In case of failure continue without timer. */
	if (unlikely((stmmac_open_ext_timer(dev, priv->tm)) < 0)) {
		GMAC_WARNING(("stmmaceth: cannot attach the external timer.\n"));
		priv->tm->freq = 0;
		priv->tm->timer_start = stmmac_no_timer_started;
		priv->tm->timer_stop = stmmac_no_timer_stopped;
	} else
		priv->tm->enable = 1;
#endif

#ifndef CONFIG_EMU_MODE
	ret = stmmac_init_phy(dev);
	if (unlikely(ret)) {
		GMAC_ERR(("%s: Cannot attach to PHY (error: %d)\n", __func__, ret));
		goto open_error;
	}
#else
	ret = stmmac_init_fake_phy(dev);
	if(0 != ret){
		GMAC_ERR((" stmmac_init_fake_phy fail. \n"));
		return -ENXIO;
	}

#endif
#endif

#if (FEATURE_ON == MBB_CTF_COMMON)
    mbb_ctf_init(dev);
#endif

#if (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD)
    stmmac_vendor_tx_thread_init(priv);
#endif
#if ((FEATURE_ON == MBB_FEATURE_FASTIP) && (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD))
    mbb_fastip_init(dev);
#endif

	/* Create and initialize the TX/RX descriptors chains. */
	priv->dma_tx_size = STMMAC_ALIGN(dma_txsize);
	priv->dma_rx_size = STMMAC_ALIGN(dma_rxsize);
	priv->dma_buf_sz = STMMAC_ALIGN(buf_sz);
	init_dma_desc_rings(dev);

	/* DMA initialization and SW reset */
	ret = priv->hw->dma->init(priv->ioaddr, priv->plat->pbl,
				  priv->dma_tx_phy, priv->dma_rx_phy);
	if (ret < 0) {
		GMAC_ERR(("%s: DMA initialization failed\n", __func__));
		goto open_error;
	}

	/* Copy the MAC addr into the HW  */
	priv->hw->mac->set_umac_addr(priv->ioaddr, dev->dev_addr, 0);

	/* If required, perform hw setup of the bus. */
	if (priv->plat->bus_setup)
		priv->plat->bus_setup(priv->ioaddr);

	/* Initialize the MAC Core */
	priv->hw->mac->core_init(priv->ioaddr);

	/* Request the IRQ lines */
	ret = request_irq(dev->irq, stmmac_interrupt,
			 IRQF_SHARED, dev->name, dev);
	if (unlikely(ret < 0)) {
		GMAC_ERR(("%s: ERROR: allocating the IRQ %d (error: %d)\n",
		       __func__, dev->irq, ret));
		goto open_error;
	}

	/* Request the Wake IRQ in case of another line is used for WoL */
	if (priv->wol_irq != dev->irq) {
		ret = request_irq(priv->wol_irq, stmmac_interrupt,
				  IRQF_SHARED, dev->name, dev);
		if (unlikely(ret < 0)) {
			GMAC_ERR(("%s: ERROR: allocating the ext WoL IRQ %d "
			       "(error: %d)\n",	__func__, priv->wol_irq, ret));
			goto open_error_wolirq;
		}
	}

	/* Enable the MAC Rx/Tx */
	stmmac_set_mac(priv->ioaddr, true);

	/* Set the HW DMA mode and the COE */
	stmmac_dma_operation_mode(priv);

	/* Extra statistics */
	memset(&priv->xstats, 0, sizeof(struct stmmac_extra_stats));
	priv->xstats.threshold = tc;
    gmac_status = &priv->xstats;

	stmmac_mmc_setup(priv);

#ifdef CONFIG_STMMAC_DEBUG_FS
	ret = stmmac_init_fs(dev);
	if (ret < 0)
		GMAC_WARNING(("%s: failed debugFS registration\n", __func__));
#endif
	/* Start the ball rolling... */
	GMAC_TRACE(("%s: DMA RX/TX processes started...\n", dev->name));
	priv->hw->dma->start_tx(priv->ioaddr);
	priv->hw->dma->start_rx(priv->ioaddr);
	
	priv->hw->dma->rx_watchdog(priv->ioaddr, riwt_value);

#ifdef CONFIG_STMMAC_TIMER
	priv->tm->timer_start(tmrate);
#endif

	/* Dump DMA/MAC registers */
	if (netif_msg_hw(priv)) {
		priv->hw->mac->dump_regs(priv->ioaddr);
		priv->hw->dma->dump_regs(priv->ioaddr);
	}
#if (FEATURE_ON == MBB_FEATURE_ETH)
    stmmac_link_init(dev);
#endif

#if (FEATURE_OFF == MBB_FEATURE_ETH)
#ifndef CONFIG_EMU_MODE
	if (priv->phydev)
		phy_start(priv->phydev);
#else
	priv->phydev->state = PHY_UP;
#endif
#endif

	napi_enable(&priv->napi);
	skb_queue_head_init(&priv->rx_recycle);
	netif_start_queue(dev);
#ifdef CONFIG_EMU_MODE
	force_gmac_to_loop(dev);
#endif
	return 0;

open_error_wolirq:
	free_irq(dev->irq, dev);

open_error:
#ifdef CONFIG_STMMAC_TIMER
	kfree(priv->tm);
#endif
#if (FEATURE_OFF == MBB_FEATURE_ETH)
#ifndef CONFIG_EMU_MODE

	if (priv->phydev)
		phy_disconnect(priv->phydev);
#endif
#endif
	return ret;
}

/**
 *  stmmac_release - close entry point of the driver
 *  @dev : device pointer.
 *  Description:
 *  This is the stop entry point of the driver.
 */
static int stmmac_release(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	
#if (FEATURE_OFF == MBB_FEATURE_ETH)
	/* Stop and disconnect the PHY */
	if (priv->phydev) {
#ifndef CONFIG_EMU_MODE
		phy_stop(priv->phydev);
		phy_disconnect(priv->phydev);
		priv->phydev = NULL;
#endif
	}
#endif

	netif_stop_queue(dev);
	priv->xstats.gmac_release++;
#if (FEATURE_OFF == MBB_FEATURE_ETH)
#ifdef CONFIG_STMMAC_TIMER
	/* Stop and release the timer */
	stmmac_close_ext_timer();
	if (priv->tm != NULL)
		kfree(priv->tm);
#endif
#endif

	napi_disable(&priv->napi);
	skb_queue_purge(&priv->rx_recycle);

	/* Free the IRQ lines */
	free_irq(dev->irq, dev);
	if (priv->wol_irq != dev->irq)
		free_irq(priv->wol_irq, dev);

	/* Stop TX/RX DMA and clear the descriptors */
	priv->hw->dma->stop_tx(priv->ioaddr);
	priv->hw->dma->stop_rx(priv->ioaddr);

	/* Release and free the Rx/Tx resources */
	free_dma_desc_resources(priv);

	/* Disable the MAC Rx/Tx */
	stmmac_set_mac(priv->ioaddr, false);

	netif_carrier_off(dev);

#ifdef CONFIG_STMMAC_DEBUG_FS
	stmmac_exit_fs();
#endif

#if (FEATURE_ON == MBB_CTF_COMMON)
    mbb_ctf_exit(dev);
#endif

#if (FEATURE_OFF == MBB_FEATURE_ETH)
#ifndef CONFIG_EMU_MODE
	stmmac_mdio_unregister(dev);
#endif
#endif

#if ((FEATURE_ON == MBB_FEATURE_FASTIP) && (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD))
    mbb_fastip_exit(dev);
#endif
#if (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD)
    stmmac_vendor_tx_thread_uninit(priv);
#endif
	return 0;
}

/**
 *  stmmac_xmit:
 *  @skb : the socket buffer
 *  @dev : device pointer
 *  Description : Tx entry point of the driver.
 */
netdev_tx_t stmmac_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	unsigned int txsize = priv->dma_tx_size;
	unsigned int entry;
	static unsigned int pkt_cnt = 0;
	int i, csum_insertion = 0;
	int nfrags = skb_shinfo(skb)->nr_frags;
	struct dma_desc *desc, *first;
	unsigned int nopaged_len = skb_headlen(skb);

	priv->xstats.enter_xmit++;

	if (unlikely(stmmac_tx_avail(priv) < nfrags + 1)) {
		if (!netif_queue_stopped(dev)) {
			netif_stop_queue(dev);
			/* This is a hard error, log it. */
			GMAC_ERR(("%s: BUG! Tx Ring full when queue awake\n",
				__func__));
		}
		priv->xstats.tx_desc_full++;			
		return NETDEV_TX_BUSY;
	}

	spin_lock(&priv->tx_lock);

#if (FEATURE_ON == MBB_FEATURE_ETH)
    mbb_mac_clone_tx_save(skb);
#endif

	entry = priv->cur_tx % txsize;

if (gmac_msg_level & GMAC_LEVEL_TX_DBG) {
	if ((skb->len > ETH_FRAME_LEN) || nfrags)
		GMAC_TX_DBG(("stmmac xmit:\n"
		       "\tskb addr %p - len: %d - nopaged_len: %d\n"
		       "\tn_frags: %d - ip_summed: %d - %s gso\n",
		       skb, skb->len, nopaged_len, nfrags, skb->ip_summed,
		       !skb_is_gso(skb) ? "isn't" : "is"));
}

	csum_insertion = (skb->ip_summed == CHECKSUM_PARTIAL);

	desc = priv->dma_tx + entry;
	first = desc;

if (gmac_msg_level & GMAC_LEVEL_TX_DBG) {
    GMAC_TX_DBG(("----------stmmac xmit:begain----------\n"));
    display_ring(desc, 1);
	if ((nfrags > 0) || (skb->len > ETH_FRAME_LEN))
		GMAC_TX_DBG(("stmmac xmit: skb len: %d, nopaged_len: %d,\n"
		       "\t\tn_frags: %d, ip_summed: %d\n",
		       skb->len, nopaged_len, nfrags, skb->ip_summed));
}

	priv->tx_skbuff[entry] = skb;

	if (priv->hw->ring->is_jumbo_frm(skb->len, priv->plat->enh_desc)) {
		entry = priv->hw->ring->jumbo_frm(priv, skb, csum_insertion);
		desc = priv->dma_tx + entry;
	} else {
		desc->des2 = dma_map_single(priv->device, skb->data,
					nopaged_len, DMA_TO_DEVICE);
		priv->hw->desc->prepare_tx_desc(desc, 1, nopaged_len,
						csum_insertion);
	}

	for (i = 0; i < nfrags; i++) {
		const skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		int len = skb_frag_size(frag);

		entry = (++priv->cur_tx) % txsize;
		desc = priv->dma_tx + entry;

		GMAC_TX_DBG(("[entry %d] segment len: %d\n", entry, len));
		desc->des2 = skb_frag_dma_map(priv->device, frag, 0, len,
					      DMA_TO_DEVICE);
		priv->tx_skbuff[entry] = NULL;
		priv->hw->desc->prepare_tx_desc(desc, 0, len, csum_insertion);
		wmb();
		priv->hw->desc->set_tx_owner(desc);
	}

	/* Interrupt on completition only for the latest segment */
	pkt_cnt++;
	if(pkt_cnt < 32){
        priv->hw->desc->close_tx_desc(desc, 0);
    }
    else
    {
	    pkt_cnt = 0;
        priv->hw->desc->close_tx_desc(desc, 1);
    }
	
#ifdef CONFIG_STMMAC_TIMER
	/* Clean IC while using timer */
	if (likely(priv->tm->enable))
		priv->hw->desc->clear_tx_ic(desc);
#endif

	wmb();

	/* To avoid raise condition */
	priv->hw->desc->set_tx_owner(first);

	priv->cur_tx++;

if (gmac_msg_level & GMAC_LEVEL_TX_DBG) {
	    GMAC_TX_DBG(("stmmac xmit: current=%d, dirty=%d, entry=%d, "
		       "first=%p, nfrags=%d\n",
		       (priv->cur_tx % txsize), (priv->dirty_tx % txsize),
		       entry, first, nfrags));
	//	display_ring(priv->dma_tx, txsize);
	    display_ring(desc, 1);
		GMAC_TX_DBG((">>> frame to be transmitted: "));
		print_pkt(skb->data, skb->len);
        GMAC_TX_DBG(("----------stmmac xmit:end----------\n"));
}

	if (unlikely(stmmac_tx_avail(priv) <= (MAX_SKB_FRAGS + 1))) {
		GMAC_TX_DBG(("%s: stop transmitted packets\n", __func__));
		netif_stop_queue(dev);
		priv->xstats.xmit_td_full++;
		priv->xstats.tx_avail = stmmac_tx_avail(priv);
	}

	dev->stats.tx_bytes += skb->len;

	skb_tx_timestamp(skb);

	priv->hw->dma->enable_dma_transmission(priv->ioaddr);

	spin_unlock(&priv->tx_lock);

	return NETDEV_TX_OK;
}

static inline void stmmac_rx_refill(struct stmmac_priv *priv)
{
	unsigned int rxsize = priv->dma_rx_size;
	int bfsize = priv->dma_buf_sz;
	struct dma_desc *p = priv->dma_rx;

	for (; priv->cur_rx - priv->dirty_rx > 0; priv->dirty_rx++) {
		unsigned int entry = priv->dirty_rx % rxsize;
		if (likely(priv->rx_skbuff[entry] == NULL)) {
			struct sk_buff *skb;

			skb = __skb_dequeue(&priv->rx_recycle);
			if (skb == NULL)
				skb = netdev_alloc_skb_ip_align(priv->dev,
								bfsize);

			if (unlikely(skb == NULL))
				break;

			priv->rx_skbuff[entry] = skb;
			priv->rx_skbuff_dma[entry] =
			    dma_map_single(priv->device, skb->data, bfsize,
					   DMA_FROM_DEVICE);

			(p + entry)->des2 = priv->rx_skbuff_dma[entry];

			if (unlikely(priv->plat->has_gmac))
				priv->hw->ring->refill_desc3(bfsize, p + entry);

			GMAC_RX_DBG(("\trefill entry #%d\n", entry));
		}
		wmb();
		priv->hw->desc->set_rx_owner(p + entry);
		priv->hw->desc->dis_rx_intr_comp(p + entry,rx_irq_flag);
	}
}



int stmmac_rx(struct stmmac_priv *priv, int limit)
{
	unsigned int rxsize = priv->dma_rx_size;
	unsigned int entry = priv->cur_rx % rxsize;
	unsigned int next_entry;
	unsigned int count = 0;
	struct dma_desc *p = priv->dma_rx + entry;
	struct dma_desc *p_next;

if (gmac_msg_level & GMAC_LEVEL_RX_DBG) {
	GMAC_RX_DBG((">>> stmmac_rx: descriptor ring:\n"));
	//display_ring(priv->dma_rx, rxsize);
	display_ring(p, 1);
}
	count = 0;
	while (!priv->hw->desc->get_rx_owner(p)) {
		int status;

		if (count >= limit)
			break;

		count++;

		next_entry = (++priv->cur_rx) % rxsize;
		p_next = priv->dma_rx + next_entry;
		prefetch(p_next);

		/* read the status of the incoming frame */
		status = (priv->hw->desc->rx_status(&priv->dev->stats,
						    &priv->xstats, p));
		if (unlikely(status == discard_frame))
			priv->dev->stats.rx_errors++;
		else {
			struct sk_buff *skb;
			int frame_len;

			frame_len = priv->hw->desc->get_rx_frame_len(p);
			/* ACS is set; GMAC core strips PAD/FCS for IEEE 802.3
			 * Type frames (LLC/LLC-SNAP) */
			if (unlikely(status != llc_snap))
				frame_len -= ETH_FCS_LEN;
if (gmac_msg_level & GMAC_LEVEL_RX_DBG) {
			if (frame_len > ETH_FRAME_LEN)
				GMAC_RX_DBG(("\tRX frame size %d, COE status: %d\n",
					frame_len, status));

			GMAC_RX_DBG(("\tdesc: %p [entry %d] buff=0x%x\n",
					p, entry, p->des2));
}
			skb = priv->rx_skbuff[entry];
			if (unlikely(!skb)) {
				GMAC_ERR(("%s: Inconsistent Rx descriptor chain\n",
					priv->dev->name));
				priv->dev->stats.rx_dropped++;
				break;
			}
			prefetch(skb->data - NET_IP_ALIGN);
			priv->rx_skbuff[entry] = NULL;

			skb_put(skb, frame_len);
			dma_unmap_single(priv->device,
					 priv->rx_skbuff_dma[entry],
					 priv->dma_buf_sz, DMA_FROM_DEVICE);
if (gmac_msg_level & GMAC_LEVEL_RX_DBG) {
		GMAC_RX_DBG((" frame received (%dbytes)", frame_len);
		print_pkt(skb->data, frame_len));
}

#if (FEATURE_ON == MBB_FEATURE_ETH)
            mbb_mac_clone_rx_restore(skb);
            mbb_check_net_upgrade(skb);
#endif

#if (FEATURE_ON == MBB_CTF_COMMON)
            if (0 != mbb_ctf_forward(skb, priv->dev))
#endif
#if ((FEATURE_ON == MBB_FEATURE_FASTIP) && (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD))
            if (0 != mbb_fastip_forward(skb, priv->dev))
#endif
            {
    			skb->protocol = eth_type_trans(skb, priv->dev);

    			if (unlikely(!priv->rx_coe)) {
    				/* No RX COE for old mac10/100 devices */
    				skb_checksum_none_assert(skb);
                    #ifdef CONFIG_GMAC_TEST
                        local_receive_skb(count, skb);

                    #else
    				    netif_receive_skb(skb);
                    #endif
    			} else {
    				skb->ip_summed = CHECKSUM_UNNECESSARY;
                    #ifdef CONFIG_GMAC_TEST
                        local_receive_skb(count, skb);
                    #else
    				    napi_gro_receive(&priv->napi, skb);
                    #endif
    			}
            }

			priv->dev->stats.rx_packets++;
			priv->dev->stats.rx_bytes += frame_len;
		}
		entry = next_entry;
		p = p_next;	/* use prefetched values */
	}

	stmmac_rx_refill(priv);

	priv->xstats.rx_pkt_n += count;

	return count;
}

/**
 *  stmmac_poll - stmmac poll method (NAPI)
 *  @napi : pointer to the napi structure.
 *  @budget : maximum number of packets that the current CPU can receive from
 *	      all interfaces.
 *  Description :
 *   This function implements the the reception process.
 *   Also it runs the TX completion thread
 */
static int stmmac_poll(struct napi_struct *napi, int budget)
{
	struct stmmac_priv *priv = container_of(napi, struct stmmac_priv, napi);
	int work_done = 0;

	priv->xstats.poll_n++;
    GMAC_DBG(("%s:>>>>>>>> POLL BEGAIN,JUMP INTO TX>>>>>>>>>\n", __FUNCTION__));
	stmmac_tx(priv);
    GMAC_DBG(("%s: JUMP INTO RX\n", __FUNCTION__));
	work_done = stmmac_rx(priv, budget);
    GMAC_DBG(("%s: >>>>>>>> POLL END,RX END>>>>>>>>>\n", __FUNCTION__));

	if (work_done < budget) {
		napi_complete(napi);
		stmmac_enable_irq(priv);
	}
	return work_done;
}

/**
 *  stmmac_tx_timeout
 *  @dev : Pointer to net device structure
 *  Description: this function is called when a packet transmission fails to
 *   complete within a reasonable tmrate. The driver will mark the error in the
 *   netdev structure and arrange for the device to be reset to a sane state
 *   in order to transmit a new packet.
 */
static void stmmac_tx_timeout(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	/* Clear Tx resources and restart transmitting again */
	stmmac_tx_err(priv);
	GMAC_WARNING(("stmmac_tx_timeout, napi timeout. \n"));

}

/* Configuration changes (passed on by ifconfig) */
static int stmmac_config(struct net_device *dev, struct ifmap *map)
{
	if (dev->flags & IFF_UP)	/* can't act on a running interface */
		return -EBUSY;

	/* Don't allow changing the I/O address */
	if (map->base_addr != dev->base_addr) {
		GMAC_WARNING(("%s: can't change I/O address\n", dev->name));
		return -EOPNOTSUPP;
	}

	/* Don't allow changing the IRQ */
	if (map->irq != dev->irq) {
		GMAC_WARNING(("%s: can't change IRQ number %d\n",
		       dev->name, dev->irq));
		return -EOPNOTSUPP;
	}

	/* ignore other fields */
	return 0;
}

/**
 *  stmmac_set_rx_mode - entry point for multicast addressing
 *  @dev : pointer to the device structure
 *  Description:
 *  This function is a driver entry point which gets called by the kernel
 *  whenever multicast addresses must be enabled/disabled.
 *  Return value:
 *  void.
 */
static void stmmac_set_rx_mode(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	spin_lock(&priv->lock);
	priv->hw->mac->set_filter(dev);
	spin_unlock(&priv->lock);
}

/**
 *  stmmac_change_mtu - entry point to change MTU size for the device.
 *  @dev : device pointer.
 *  @new_mtu : the new MTU size for the device.
 *  Description: the Maximum Transfer Unit (MTU) is used by the network layer
 *  to drive packet transmission. Ethernet has an MTU of 1500 octets
 *  (ETH_DATA_LEN). This value can be changed with ifconfig.
 *  Return value:
 *  0 on success and an appropriate (-)ve integer as defined in errno.h
 *  file on failure.
 */
static int stmmac_change_mtu(struct net_device *dev, int new_mtu)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	int max_mtu;

	if (netif_running(dev)) {
		GMAC_ERR(("%s: must be stopped to change its MTU\n", dev->name));
		return -EBUSY;
	}

	if (priv->plat->enh_desc)
		max_mtu = JUMBO_LEN;
	else
		max_mtu = SKB_MAX_HEAD(NET_SKB_PAD + NET_IP_ALIGN);

	if ((new_mtu < 46) || (new_mtu > max_mtu)) {
		GMAC_ERR(("%s: invalid MTU, max MTU is: %d\n", dev->name, max_mtu));
		return -EINVAL;
	}

	dev->mtu = new_mtu;
	netdev_update_features(dev);

	return 0;
}

static netdev_features_t stmmac_fix_features(struct net_device *dev,
	netdev_features_t features)
{
	struct stmmac_priv *priv = netdev_priv(dev);

	if (!priv->rx_coe)
		features &= ~NETIF_F_RXCSUM;
	if (!priv->plat->tx_coe)
		features &= ~NETIF_F_ALL_CSUM;

	/* Some GMAC devices have a bugged Jumbo frame support that
	 * needs to have the Tx COE disabled for oversized frames
	 * (due to limited buffer sizes). In this case we disable
	 * the TX csum insertionin the TDES and not use SF. */
	if (priv->plat->bugged_jumbo && (dev->mtu > ETH_DATA_LEN))
		features &= ~NETIF_F_ALL_CSUM;

	return features;
}

static irqreturn_t stmmac_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct stmmac_priv *priv = netdev_priv(dev);

	if (unlikely(!dev)) {
		GMAC_ERR(("%s: invalid dev pointer\n", __func__));
		return IRQ_NONE;
	}

	if (priv->plat->has_gmac)
		/* To handle GMAC own interrupts */
		priv->hw->mac->host_irq_status((void __iomem *) dev->base_addr);

	stmmac_dma_interrupt(priv);

	return IRQ_HANDLED;
}

#ifdef CONFIG_NET_POLL_CONTROLLER
/* Polling receive - used by NETCONSOLE and other diagnostic tools
 * to allow network I/O with interrupts disabled. */
static void stmmac_poll_controller(struct net_device *dev)
{
	disable_irq(dev->irq);
	stmmac_interrupt(dev->irq, dev);
	enable_irq(dev->irq);
}
#endif

/**
 *  stmmac_ioctl - Entry point for the Ioctl
 *  @dev: Device pointer.
 *  @rq: An IOCTL specefic structure, that can contain a pointer to
 *  a proprietary structure used to pass information to the driver.
 *  @cmd: IOCTL command
 *  Description:
 *  Currently there are no special functionality supported in IOCTL, just the
 *  phy_mii_ioctl(...) can be invoked.
 */
static int stmmac_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
#ifndef CONFIG_EMU_MODE
	struct stmmac_priv *priv = netdev_priv(dev);
	int ret;

	if (!netif_running(dev))
		return -EINVAL;

	if (!priv->phydev)
		return -EINVAL;

	ret = phy_mii_ioctl(priv->phydev, rq, cmd);

	return ret;
#else
	return 0;
#endif
}

#ifdef CONFIG_STMMAC_DEBUG_FS
static struct dentry *stmmac_fs_dir;
static struct dentry *stmmac_rings_status;
static struct dentry *stmmac_dma_cap;
static struct dentry *stmmac_phy_stats;
static struct dentry *stmmac_stmmac_stats;


static int stmmac_sysfs_ring_read(struct seq_file *seq, void *v)
{
	struct tmp_s {
		u64 a;
		unsigned int b;
		unsigned int c;
	};
	int i;
	struct net_device *dev = seq->private;
	struct stmmac_priv *priv = netdev_priv(dev);

	seq_printf(seq, "=======================\n");
	seq_printf(seq, " RX descriptor ring\n");
	seq_printf(seq, "=======================\n");

	for (i = 0; i < priv->dma_rx_size; i++) {
		struct tmp_s *x = (struct tmp_s *)(priv->dma_rx + i);
		seq_printf(seq, "[%d] DES0=0x%x DES1=0x%x BUF1=0x%x BUF2=0x%x",
			   i, (unsigned int)(x->a),
			   (unsigned int)((x->a) >> 32), x->b, x->c);
		seq_printf(seq, "\n");
	}

	seq_printf(seq, "\n");
	seq_printf(seq, "=======================\n");
	seq_printf(seq, "  TX descriptor ring\n");
	seq_printf(seq, "=======================\n");

	for (i = 0; i < priv->dma_tx_size; i++) {
		struct tmp_s *x = (struct tmp_s *)(priv->dma_tx + i);
		seq_printf(seq, "[%d] DES0=0x%x DES1=0x%x BUF1=0x%x BUF2=0x%x",
			   i, (unsigned int)(x->a),
			   (unsigned int)((x->a) >> 32), x->b, x->c);
		seq_printf(seq, "\n");
	}

	return 0;
}

static int stmmac_sysfs_ring_open(struct inode *inode, struct file *file)
{
	return single_open(file, stmmac_sysfs_ring_read, inode->i_private);
}

static const struct file_operations stmmac_rings_status_fops = {
	.owner = THIS_MODULE,
	.open = stmmac_sysfs_ring_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release,
};

static int stmmac_sysfs_dma_cap_read(struct seq_file *seq, void *v)
{
	struct net_device *dev = seq->private;
	struct stmmac_priv *priv = netdev_priv(dev);

	if (!priv->hw_cap_support) {
		seq_printf(seq, "DMA HW features not supported\n");
		return 0;
	}

	seq_printf(seq, "==============================\n");
	seq_printf(seq, "\tDMA HW features\n");
	seq_printf(seq, "==============================\n");

	seq_printf(seq, "\t10/100 Mbps %s\n",
		   (priv->dma_cap.mbps_10_100) ? "Y" : "N");
	seq_printf(seq, "\t1000 Mbps %s\n",
		   (priv->dma_cap.mbps_1000) ? "Y" : "N");
	seq_printf(seq, "\tHalf duple %s\n",
		   (priv->dma_cap.half_duplex) ? "Y" : "N");
	seq_printf(seq, "\tHash Filter: %s\n",
		   (priv->dma_cap.hash_filter) ? "Y" : "N");
	seq_printf(seq, "\tMultiple MAC address registers: %s\n",
		   (priv->dma_cap.multi_addr) ? "Y" : "N");
	seq_printf(seq, "\tPCS (TBI/SGMII/RTBI PHY interfatces): %s\n",
		   (priv->dma_cap.pcs) ? "Y" : "N");
	seq_printf(seq, "\tSMA (MDIO) Interface: %s\n",
		   (priv->dma_cap.sma_mdio) ? "Y" : "N");
	seq_printf(seq, "\tPMT Remote wake up: %s\n",
		   (priv->dma_cap.pmt_remote_wake_up) ? "Y" : "N");
	seq_printf(seq, "\tPMT Magic Frame: %s\n",
		   (priv->dma_cap.pmt_magic_frame) ? "Y" : "N");
	seq_printf(seq, "\tRMON module: %s\n",
		   (priv->dma_cap.rmon) ? "Y" : "N");
	seq_printf(seq, "\tIEEE 1588-2002 Time Stamp: %s\n",
		   (priv->dma_cap.time_stamp) ? "Y" : "N");
	seq_printf(seq, "\tIEEE 1588-2008 Advanced Time Stamp:%s\n",
		   (priv->dma_cap.atime_stamp) ? "Y" : "N");
	seq_printf(seq, "\t802.3az - Energy-Efficient Ethernet (EEE) %s\n",
		   (priv->dma_cap.eee) ? "Y" : "N");
	seq_printf(seq, "\tAV features: %s\n", (priv->dma_cap.av) ? "Y" : "N");
	seq_printf(seq, "\tChecksum Offload in TX: %s\n",
		   (priv->dma_cap.tx_coe) ? "Y" : "N");
	seq_printf(seq, "\tIP Checksum Offload (type1) in RX: %s\n",
		   (priv->dma_cap.rx_coe_type1) ? "Y" : "N");
	seq_printf(seq, "\tIP Checksum Offload (type2) in RX: %s\n",
		   (priv->dma_cap.rx_coe_type2) ? "Y" : "N");
	seq_printf(seq, "\tRXFIFO > 2048bytes: %s\n",
		   (priv->dma_cap.rxfifo_over_2048) ? "Y" : "N");
	seq_printf(seq, "\tNumber of Additional RX channel: %d\n",
		   priv->dma_cap.number_rx_channel);
	seq_printf(seq, "\tNumber of Additional TX channel: %d\n",
		   priv->dma_cap.number_tx_channel);
	seq_printf(seq, "\tEnhanced descriptors: %s\n",
		   (priv->dma_cap.enh_desc) ? "Y" : "N");

	return 0;
}


static int stmmac_sysfs_dma_cap_open(struct inode *inode, struct file *file)
{
	return single_open(file, stmmac_sysfs_dma_cap_read, inode->i_private);
}

static const struct file_operations stmmac_dma_cap_fops = {
	.owner = THIS_MODULE,
	.open = stmmac_sysfs_dma_cap_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release,
};

static int stmmac_sysfs_phy_stats_read(struct seq_file *seq, void *v)
{
	struct net_device *dev = seq->private;
	struct stmmac_priv *priv = netdev_priv(dev);

	seq_printf(seq, "==============================\n");
	seq_printf(seq, "\tphydev status\n");
	seq_printf(seq, "==============================\n");

    seq_printf(seq, "\tPHY INTERFACE = %d\n",
            (priv->phydev->interface));
    seq_printf(seq, "\tPHY SPEED = %d\n",
            (priv->phydev->speed));
    seq_printf(seq, "\tPHY LINK: %s\n",
		   (priv->phydev->link) ? "Y" : "N");
    seq_printf(seq, "\tPHY STATE = %d\n",
            (priv->phydev->state));

    seq_printf(seq, "\tPHY DUPLEX %s\n",
            (priv->phydev->duplex) ? "Y" : "N");
    seq_printf(seq, "\toldlink %s\n",
            (priv->oldlink) ? "Y" : "N");
    seq_printf(seq, "\toldduplex %s\n",
            (priv->oldduplex) ? "Y" : "N");
    seq_printf(seq, "\tphyid = %02x\n",
            (priv->phydev->phy_id));

    seq_printf(seq, "==============================\n");
	seq_printf(seq, "\tphydev help\n");
	seq_printf(seq, "==============================\n");
    seq_printf(seq, "=========PHY INTERFACE========\n");
    seq_printf(seq, "\t0:PHY_INTERFACE_MODE_NA\n");
    seq_printf(seq, "\t1:PHY_INTERFACE_MODE_MII\n");
    seq_printf(seq, "\t2:PHY_INTERFACE_MODE_GMII\n");
    seq_printf(seq, "\t3:PHY_INTERFACE_MODE_SGMII\n");
    seq_printf(seq, "\t4:PHY_INTERFACE_MODE_TBI\n");
    seq_printf(seq, "\t5:PHY_INTERFACE_MODE_RMII\n");
    seq_printf(seq, "\t6:PHY_INTERFACE_MODE_RGMII\n");
    seq_printf(seq, "\t7:PHY_INTERFACE_MODE_RGMII_ID\n");
    seq_printf(seq, "\t8:PHY_INTERFACE_MODE_RGMII_RXID\n");
    seq_printf(seq, "\t9:PHY_INTERFACE_MODE_RGMII_TXID\n");
    seq_printf(seq, "\t10:PHY_INTERFACE_MODE_RTBI\n");
    seq_printf(seq, "\t11:PHY_INTERFACE_MODE_SMII\n");
    seq_printf(seq, "=========PHY STATE========\n");
    seq_printf(seq, "\t0:PHY_DOWN\n");
    seq_printf(seq, "\t1:PHY_STARTING\n");
    seq_printf(seq, "\t2:PHY_READY\n");
    seq_printf(seq, "\t3:PHY_PENDING\n");
    seq_printf(seq, "\t4:PHY_UP\n");
    seq_printf(seq, "\t5:PHY_AN\n");
    seq_printf(seq, "\t6:PHY_RUNNING\n");
    seq_printf(seq, "\t7:PHY_NOLINK\n");
    seq_printf(seq, "\t8:PHY_FORCING\n");
    seq_printf(seq, "\t9:PHY_CHANGELINK\n");
    seq_printf(seq, "\t10:PHY_HALTED\n");
    seq_printf(seq, "\t11:PHY_RESUMING\n");

    return 0;
}

static int stmmac_sysfs_phy_stats_open(struct inode *inode, struct file *file)
{
	return single_open(file, stmmac_sysfs_phy_stats_read, inode->i_private);
}

static const struct file_operations stmmac_phy_stats_fops = {
    .owner = THIS_MODULE,
	.open = stmmac_sysfs_phy_stats_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release,
};

static int stmmac_sysfs_stmmac_stats_read(struct seq_file *seq, void *v)
{
	struct net_device *dev = seq->private;
	struct stmmac_priv *priv = netdev_priv(dev);

    seq_printf(seq, "==============================\n");
	seq_printf(seq, "\tstmmac status\n");
	seq_printf(seq, "==============================\n");
    seq_printf(seq, "\tcur_tx = %d\n",
            (priv->cur_tx));
    seq_printf(seq, "\tdirty_tx = %d\n",
            (priv->dirty_tx));
    seq_printf(seq, "\tcur_rx = %d\n",
            (priv->cur_rx));
    seq_printf(seq, "\tdirty_rx = %d\n",
            (priv->dirty_rx));

    return 0;
}
static int stmmac_sysfs_stmmac_stats_open(struct inode *inode, struct file *file)
{
	return single_open(file, stmmac_sysfs_stmmac_stats_read, inode->i_private);
}

static const struct file_operations stmmac_stmmac_stats_fops = {
    .owner = THIS_MODULE,
	.open = stmmac_sysfs_stmmac_stats_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release,
};

static int stmmac_init_fs(struct net_device *dev)
{
	/* Create debugfs entries */
	stmmac_fs_dir = debugfs_create_dir(STMMAC_RESOURCE_NAME, NULL);

	if (!stmmac_fs_dir || IS_ERR(stmmac_fs_dir)) {
		GMAC_ERR(("ERROR %s, debugfs create directory failed\n",
		       STMMAC_RESOURCE_NAME));

		return -ENOMEM;
	}

	/* Entry to report DMA RX/TX rings */
	stmmac_rings_status = debugfs_create_file("descriptors_status",
					   S_IRUGO, stmmac_fs_dir, dev,
					   &stmmac_rings_status_fops);

	if (!stmmac_rings_status || IS_ERR(stmmac_rings_status)) {
		GMAC_INFO(("ERROR creating stmmac ring debugfs file\n"));
		debugfs_remove(stmmac_fs_dir);

		return -ENOMEM;
	}

	/* Entry to report the DMA HW features */
	stmmac_dma_cap = debugfs_create_file("dma_cap", S_IRUGO, stmmac_fs_dir,
					     dev, &stmmac_dma_cap_fops);

	if (!stmmac_dma_cap || IS_ERR(stmmac_dma_cap)) {
		GMAC_INFO(("ERROR creating stmmac MMC debugfs file\n"));
		debugfs_remove(stmmac_rings_status);
		debugfs_remove(stmmac_fs_dir);

		return -ENOMEM;
	}

	/* Entry to report the phydev stats */
	stmmac_phy_stats = debugfs_create_file("phy_stats", S_IRUGO, stmmac_fs_dir,
					     dev, &stmmac_phy_stats_fops);

	if (!stmmac_phy_stats || IS_ERR(stmmac_phy_stats)) {
		GMAC_INFO(("ERROR creating phy stats debugfs file\n"));
        debugfs_remove(stmmac_dma_cap);
        debugfs_remove(stmmac_rings_status);
		debugfs_remove(stmmac_fs_dir);

		return -ENOMEM;
	}

    /* Entry to report the stmmac stats */
	stmmac_stmmac_stats = debugfs_create_file("stmmac_stats", S_IRUGO, stmmac_fs_dir,
					     dev, &stmmac_stmmac_stats_fops);

	if (!stmmac_stmmac_stats || IS_ERR(stmmac_stmmac_stats)) {
		GMAC_INFO(("ERROR creating stmmac stats debugfs file\n"));
        debugfs_remove(stmmac_phy_stats);
        debugfs_remove(stmmac_dma_cap);
        debugfs_remove(stmmac_rings_status);
		debugfs_remove(stmmac_fs_dir);

		return -ENOMEM;
	}
	return 0;
}

static void stmmac_exit_fs(void)
{
    debugfs_remove(stmmac_stmmac_stats);
    debugfs_remove(stmmac_phy_stats);
    debugfs_remove(stmmac_rings_status);
	debugfs_remove(stmmac_dma_cap);
	debugfs_remove(stmmac_fs_dir);
}
#endif /* CONFIG_STMMAC_DEBUG_FS */

static const struct net_device_ops stmmac_netdev_ops = {
	.ndo_open = stmmac_open,
    #if (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD)
    .ndo_start_xmit = stmmac_vendor_post_skb, 
    #else
    .ndo_start_xmit = stmmac_xmit,
    #endif
	.ndo_stop = stmmac_release,
	.ndo_change_mtu = stmmac_change_mtu,
	.ndo_fix_features = stmmac_fix_features,
	.ndo_set_rx_mode = stmmac_set_rx_mode,
    #if (FEATURE_OFF == MBB_ETH_PHY_LOWPOWER)
	.ndo_tx_timeout = stmmac_tx_timeout,
    #endif
	.ndo_do_ioctl = stmmac_ioctl,
	.ndo_set_config = stmmac_config,
#ifdef CONFIG_NET_POLL_CONTROLLER
	.ndo_poll_controller = stmmac_poll_controller,
#endif
	.ndo_set_mac_address = eth_mac_addr,
};

/**
 *  stmmac_hw_init - Init the MAC device
 *  @priv : pointer to the private device structure.
 *  Description: this function detects which MAC device
 *  (GMAC/MAC10-100) has to attached, checks the HW capability
 *  (if supported) and sets the driver's features (for example
 *  to use the ring or chaine mode or support the normal/enh
 *  descriptor structure).
 */
static int stmmac_hw_init(struct stmmac_priv *priv)
{
	int ret = 0;
	struct mac_device_info *mac;

	/* Identify the MAC HW device */
	if (priv->plat->has_gmac) {
		priv->dev->priv_flags |= IFF_UNICAST_FLT;
		mac = dwmac1000_setup(priv->ioaddr);
	} else {
		mac = dwmac100_setup(priv->ioaddr);
	}	
	if (!mac)
		return -ENOMEM;

	priv->hw = mac;

	/* To use the chained or ring mode */
	priv->hw->ring = &ring_mode_ops;

	/* Get and dump the chip ID */
	stmmac_get_synopsys_id(priv);

	/* Get the HW capability (new GMAC newer than 3.50a) */
	priv->hw_cap_support = stmmac_get_hw_features(priv);
	if (priv->hw_cap_support) {
		GMAC_INFO((" DMA HW capability register supported"));

		/* We can override some gmac/dma configuration fields: e.g.
		 * enh_desc, tx_coe (e.g. that are passed through the
		 * platform) with the values from the HW capability
		 * register (if supported).
		 */
		/*set enh_desc the platform data,add by wangweichao*/
		//priv->plat->enh_desc = priv->dma_cap.enh_desc;
		priv->plat->tx_coe = priv->dma_cap.tx_coe;
		priv->plat->pmt = priv->dma_cap.pmt_remote_wake_up;
	} else
		GMAC_INFO((" No HW DMA feature register supported"));

	/* Select the enhnaced/normal descriptor structures */
	stmmac_selec_desc_mode(priv);

	priv->rx_coe = priv->hw->mac->rx_coe(priv->ioaddr);
	if (priv->rx_coe)
		GMAC_INFO((" RX Checksum Offload Engine supported\n"));
	if (priv->plat->tx_coe)
		GMAC_INFO((" TX Checksum insertion supported\n"));

	if (priv->plat->pmt) {
		GMAC_INFO((" Wake-Up On Lan supported\n"));
		device_set_wakeup_capable(priv->device, 1);
	}

	return ret;
}

static int get_gmac_addr(const char *str, u8 *dev_addr)
{
	if (str) {
		unsigned	i;

		for (i = 0; i < 6; i++) {
			unsigned char num;

			if ((*str == '.') || (*str == ':'))
				str++;
			num = hex_to_bin(*str++) << 4;
			num |= hex_to_bin(*str++);
			dev_addr [i] = num;
		}
		if (is_valid_ether_addr(dev_addr))
			return 0;
	}
	random_ether_addr(dev_addr);
	return 1;
}

static char *stmmac_mac = {"00:18:82:0C:0D:66"};
module_param(stmmac_mac, charp, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(stmmac_mac, "stmmac ethernet address ");

/**
 * stmmac_dvr_probe
 * @device: device pointer
 * Description: this is the main probe function used to
 * call the alloc_etherdev, allocate the priv structure.
 */
struct stmmac_priv *stmmac_dvr_probe(struct device *device,
				     struct plat_stmmacenet_data *plat_dat,
				     void __iomem *addr)
{
	int ret = 0;
	struct net_device *ndev = NULL;
	struct stmmac_priv *priv;
    /* this address is invisible to ifconfig--added by wangweichao */

	ndev = alloc_etherdev(sizeof(struct stmmac_priv));
	if (!ndev)
		return NULL;

	SET_NETDEV_DEV(ndev, device);

	priv = netdev_priv(ndev);
	priv->device = device;
	priv->dev = ndev;

	ether_setup(ndev);

	stmmac_set_ethtool_ops(ndev);
	priv->pause = pause;
	priv->plat = plat_dat;
	priv->ioaddr = addr;
	priv->dev->base_addr = (unsigned long)addr;

	/* Verify driver arguments */
	stmmac_verify_args();

	/* Override with kernel parameters if supplied XXX CRS XXX
	 * this needs to have multiple instances */
	if ((phyaddr >= 0) && (phyaddr <= 31))
		priv->plat->phy_addr = phyaddr;

	/* Init MAC and get the capabilities */
	stmmac_hw_init(priv);
	
#if (FEATURE_OFF == MBB_FEATURE_ETH)
    /* Network inteface name--add by wangweichao */
	snprintf(ndev->name, sizeof(ndev->name), "%s%%d", "gmac");
#else	
        snprintf(ndev->name, sizeof(ndev->name), "%s", NET_DEVICE_NAME);
#endif

#if (FEATURE_ON == MBB_FEATURE_ETH)
    if (0 != mbb_get_eth_macAddr(priv->dev->dev_addr))
#endif
    {
        /* Init MAC address --add by wangweichao*/
        if (get_gmac_addr(stmmac_mac, priv->dev->dev_addr)) {
                GMAC_INFO(("%s:using random ethernet address\n", __func__));
        }
    }

	ndev->netdev_ops = &stmmac_netdev_ops;

	ndev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
			    NETIF_F_RXCSUM;
	ndev->features |= ndev->hw_features | NETIF_F_HIGHDMA;


	ndev->watchdog_timeo = msecs_to_jiffies(watchdog);
#ifdef STMMAC_VLAN_TAG_USED
	/* Both mac100 and gmac support receive VLAN tag detection */
	ndev->features |= NETIF_F_HW_VLAN_RX;
#endif
	priv->msg_enable = netif_msg_init(debug, default_msg_level);

	if (flow_ctrl)
		priv->flow_ctrl = FLOW_AUTO;	/* RX/TX pause on */

	netif_napi_add(ndev, &priv->napi, stmmac_poll, 64);

	spin_lock_init(&priv->lock);
	spin_lock_init(&priv->tx_lock);

	ret = register_netdev(ndev);
	if (ret) {
		GMAC_ERR(("%s: ERROR %i registering the device\n", __func__, ret));
		goto error;
	}
	
#if (FEATURE_ON == MBB_FEATURE_ETH)
    stmmac_mdio_init(ndev);
#endif
	return priv;

error:
	netif_napi_del(&priv->napi);

	unregister_netdev(ndev);
	free_netdev(ndev);

	return NULL;
}

/**
 * stmmac_dvr_remove
 * @ndev: net device pointer
 * Description: this function resets the TX/RX processes, disables the MAC RX/TX
 * changes the link status, releases the DMA descriptor rings.
 */
int stmmac_dvr_remove(struct net_device *ndev)
{
	struct stmmac_priv *priv = netdev_priv(ndev);

	GMAC_INFO(("%s:\n\tremoving driver", __func__));

	priv->hw->dma->stop_rx(priv->ioaddr);
	priv->hw->dma->stop_tx(priv->ioaddr);

	stmmac_set_mac(priv->ioaddr, false);
	netif_carrier_off(ndev);
#if (FEATURE_ON == MBB_FEATURE_ETH)
    stmmac_mdio_exit(ndev);
#endif
	unregister_netdev(ndev);
	free_netdev(ndev);

	return 0;
}

void show_gmac_xstats(void)
{

    printk("stmmac_xmit td full:%d\n", (int)gmac_status->tx_desc_full);
    printk("stmmac_xmit td full2:%d\n", (int)gmac_status->xmit_td_full);
    printk("stmmac_release net stopped:%d\n", (int)gmac_status->gmac_release);
    printk("stmmac_suspend net stopped:%d\n", (int)gmac_status->gmac_suspend);
    printk("enter xmit:%d\n", (int)gmac_status->enter_xmit);
    printk("tx avail:%d\n", (int)gmac_status->tx_avail);

}

#ifdef CONFIG_PM
#if (FEATURE_ON == MBB_ETH_PHY_LOWPOWER)
extern int eth_power_down(void);
#endif
int stmmac_suspend(struct net_device *ndev)
{
	struct stmmac_priv *priv = netdev_priv(ndev);
	int dis_ic = 0;

    #if (FEATURE_ON == MBB_ETH_PHY_LOWPOWER)
    if ( eth_power_down() )
    {
        //ʹ��freeze�ӿ��滻�����gmac��˯���жϳ�����������
        return stmmac_freeze(ndev);
    }
    else
    {
        //�������0��˵��phy��ǰ���µ磬��stmmac������ִ��suspend���
        return 0;
    }
    #endif


	if (!ndev || !netif_running(ndev))
		return 0;

	if (priv->phydev)
#ifndef CONFIG_EMU_MODE
		phy_stop(priv->phydev);
#endif
	spin_lock(&priv->lock);

	netif_device_detach(ndev);
	netif_stop_queue(ndev);
	priv->xstats.gmac_suspend++;

#ifdef CONFIG_STMMAC_TIMER
	priv->tm->timer_stop();
	if (likely(priv->tm->enable))
		dis_ic = 1;
#endif
	napi_disable(&priv->napi);

	/* Stop TX/RX DMA */
	priv->hw->dma->stop_tx(priv->ioaddr);
	priv->hw->dma->stop_rx(priv->ioaddr);
	/* Clear the Rx/Tx descriptors */
	priv->hw->desc->init_rx_desc(priv->dma_rx, priv->dma_rx_size,
				     dis_ic);
	priv->hw->desc->init_tx_desc(priv->dma_tx, priv->dma_tx_size);

	/* Enable Power down mode by programming the PMT regs */
	if (device_may_wakeup(priv->device))
		priv->hw->mac->pmt(priv->ioaddr, priv->wolopts);
	else
		stmmac_set_mac(priv->ioaddr, false);

	spin_unlock(&priv->lock);
	return 0;
}

int stmmac_resume(struct net_device *ndev)
{
    #if (FEATURE_ON == MBB_ETH_PHY_LOWPOWER)
    //stmmac_resume��Ϊ��phy�ϵ����ã���ar8035.c�е���stmmac_restore()
    return 0;
    #endif
	struct stmmac_priv *priv = netdev_priv(ndev);

	if (!netif_running(ndev))
		return 0;

	spin_lock(&priv->lock);

	/* Power Down bit, into the PM register, is cleared
	 * automatically as soon as a magic packet or a Wake-up frame
	 * is received. Anyway, it's better to manually clear
	 * this bit because it can generate problems while resuming
	 * from another devices (e.g. serial console). */
	if (device_may_wakeup(priv->device))
		priv->hw->mac->pmt(priv->ioaddr, 0);

	netif_device_attach(ndev);

	/* Enable the MAC and DMA */
	stmmac_set_mac(priv->ioaddr, true);
	priv->hw->dma->start_tx(priv->ioaddr);
	priv->hw->dma->start_rx(priv->ioaddr);

#ifdef CONFIG_STMMAC_TIMER
	if (likely(priv->tm->enable))
		priv->tm->timer_start(tmrate);
#endif
	napi_enable(&priv->napi);

	netif_start_queue(ndev);

	spin_unlock(&priv->lock);
	
#ifndef CONFIG_EMU_MODE
	if (priv->phydev)
		phy_start(priv->phydev);
#endif

	return 0;
}

int stmmac_freeze(struct net_device *ndev)
{
	if (!ndev || !netif_running(ndev))
		return 0;

	return stmmac_release(ndev);
}

int stmmac_restore(struct net_device *ndev)
{
	if (!ndev || !netif_running(ndev))
		return 0;

	return stmmac_open(ndev);
}
#endif /* CONFIG_PM */

#ifndef MODULE
static int __init stmmac_cmdline_opt(char *str)
{
	char *opt;

	if (!str || !*str)
		return -EINVAL;
	while ((opt = strsep(&str, ",")) != NULL) {
		if (!strncmp(opt, "debug:", 6)) {
			if (strict_strtoul(opt + 6, 0, (unsigned long *)&debug))
				goto err;
		} else if (!strncmp(opt, "phyaddr:", 8)) {
			if (strict_strtoul(opt + 8, 0,
					   (unsigned long *)&phyaddr))
				goto err;
		} else if (!strncmp(opt, "dma_txsize:", 11)) {
			if (strict_strtoul(opt + 11, 0,
					   (unsigned long *)&dma_txsize))
				goto err;
		} else if (!strncmp(opt, "dma_rxsize:", 11)) {
			if (strict_strtoul(opt + 11, 0,
					   (unsigned long *)&dma_rxsize))
				goto err;
		} else if (!strncmp(opt, "buf_sz:", 7)) {
			if (strict_strtoul(opt + 7, 0,
					   (unsigned long *)&buf_sz))
				goto err;
		} else if (!strncmp(opt, "tc:", 3)) {
			if (strict_strtoul(opt + 3, 0, (unsigned long *)&tc))
				goto err;
		} else if (!strncmp(opt, "watchdog:", 9)) {
			if (strict_strtoul(opt + 9, 0,
					   (unsigned long *)&watchdog))
				goto err;
		} else if (!strncmp(opt, "flow_ctrl:", 10)) {
			if (strict_strtoul(opt + 10, 0,
					   (unsigned long *)&flow_ctrl))
				goto err;
		} else if (!strncmp(opt, "pause:", 6)) {
			if (strict_strtoul(opt + 6, 0, (unsigned long *)&pause))
				goto err;
#ifdef CONFIG_STMMAC_TIMER
		} else if (!strncmp(opt, "tmrate:", 7)) {
			if (strict_strtoul(opt + 7, 0,
					   (unsigned long *)&tmrate))
				goto err;
#endif
		}
	}
	return 0;

err:
	GMAC_ERR(("%s: ERROR broken module parameter conversion", __func__));
	return -EINVAL;
}

__setup("stmmaceth=", stmmac_cmdline_opt);
#endif

MODULE_DESCRIPTION("STMMAC 10/100/1000 Ethernet device driver");
MODULE_AUTHOR("Giuseppe Cavallaro <peppe.cavallaro@st.com>");
MODULE_LICENSE("GPL");

#if (FEATURE_ON == MBB_FEATURE_ETH)
extern struct net init_net;
void stmmac_debug()
{
    struct net_device *dev = __dev_get_by_name(&init_net, NET_DEVICE_NAME);
    struct stmmac_priv *priv = netdev_priv(dev);

    printk("PHY INFO:\r\n");
    printk("PHY addr:%d, state:%d, autoneg:%d\n", priv->phydev->addr, priv->phydev->state, priv->phydev->autoneg); 
    printk("PHY link:%d, speed:%d, duplex: %d\n", priv->phydev->link, priv->phydev->speed, priv->phydev->duplex);

    printk("MAC INFO:\r\n");
    printk("ioaddr:     0x%x\n", readl(priv->ioaddr));
    printk("cur_rx:     %d\n",   priv->cur_rx);
    printk("dirty_rx:   %d\n",   priv->dirty_rx);
    printk("cur_tx:     %d\n",   priv->cur_tx);
    printk("dirty_tx:   %d\n",   priv->dirty_tx);
}

EXPORT_SYMBOL(stmmac_debug);
#endif
#if (FEATURE_ON == MBB_ETH_STMMAC_TX_THREAD)
int stmmac_vendor_post_skb(struct sk_buff *skb,   struct net_device *dev)
{
    struct stmmac_priv *stmmac = netdev_priv(dev);
    netdev_tx_t  tx_ret = NETDEV_TX_OK;
    if ((!stmmac) || (!skb))
    {
        GMAC_ERR(("%s: skb or stmmac is NULL, return.\n",__FUNCTION__));
        return -EFAULT;
    }

    skb->dev = dev;
    if (!stmmac_pkt_txthread_flag)
    {
        GMAC_TX_DBG(("%s: TX thread is closed, post to stmmac_xmit.\n",__FUNCTION__));
        tx_ret = stmmac_xmit(skb, dev);
        return tx_ret;
    }
    if(false == stmmac->vendor_ctx.tx_task_run)
    {
        GMAC_TX_DBG(("%s: thread task is not run, free skb.\n",__FUNCTION__));
        dev_kfree_skb_any(skb);
        return NETDEV_TX_OK;
    }
    if(skb_queue_len(&stmmac->vendor_ctx.tx_frames) >= 1000)
    {
        GMAC_TX_DBG(("%s: tx_frames is >=1000, free skb.\n",__FUNCTION__));
        dev_kfree_skb_any(skb);
        stmmac->vendor_ctx.stat_tx_drop++;
        return NETDEV_TX_OK;
    }
    skb_queue_tail(&stmmac->vendor_ctx.tx_frames, skb);
    stmmac->vendor_ctx.stat_tx_post++;
    complete(&stmmac->vendor_ctx.tx_kick);

    return NETDEV_TX_OK;
}

netdev_tx_t stmmac_vendor_start_xmit(struct sk_buff *skb,
                    struct net_device *net)
{
    struct stmmac_priv *stmmac = NULL;
    netdev_tx_t  tx_ret = NETDEV_TX_OK;
    unsigned long flags;

    if (!net)
    {
        GMAC_ERR(("%s: net is NULL, free skb.\n",__FUNCTION__));
        dev_kfree_skb_any(skb);
        return NETDEV_TX_OK;
    }
    stmmac = netdev_priv(net);
    if (!stmmac)
    {
        GMAC_ERR(("%s: stmmac is NULL, free skb.\n",__FUNCTION__));
        dev_kfree_skb_any(skb);
        return NETDEV_TX_OK;
    }
    spin_lock_irqsave(&stmmac->vendor_ctx.tx_kick, flags);

    tx_ret = stmmac_xmit(skb, net);
    spin_unlock_irqrestore(&stmmac->vendor_ctx.tx_kick, flags);
    return tx_ret;
}
static int stmmac_vendor_tx_thread(void *param)
{
    struct stmmac_priv *stmmac = (struct stmmac_priv *)param;
    struct sk_buff *skb = NULL;
    netdev_tx_t  tx_ret = NETDEV_TX_OK;
    
    if (!stmmac)
    {
        GMAC_ERR(("stmmac vendor tx thread abnormal quit!\n"));
        return -1;
    }

    stmmac->vendor_ctx.tx_task_run = true;
    while (stmmac->vendor_ctx.tx_task_run)
    {
        next:
        wait_for_completion(&stmmac->vendor_ctx.tx_kick);
        do{
            skb = skb_dequeue(&stmmac->vendor_ctx.tx_frames);
            if(skb)
            {
                stmmac->vendor_ctx.stat_tx_xmit++;
                tx_ret = stmmac_vendor_start_xmit(skb, skb->dev);
                if (NETDEV_TX_OK != tx_ret)
                {
                    stmmac->vendor_ctx.stat_tx_xmit_fail++;
                    dev_kfree_skb_any(skb);
                }
            }
        }while(skb);
    }

    complete(&stmmac->vendor_ctx.tx_task_stop);
    return 0;
}
static int stmmac_vendor_tx_thread_init(struct stmmac_priv *stmmac)
{
    char thread_name[64] = "0";
    struct sched_param param;
  
    GMAC_TX_DBG(("%s:enter.\n",__FUNCTION__));
    param.sched_priority = 80;
    if (!stmmac)
    {
        GMAC_TX_DBG(("%s:enter ENOMEM.\n",__FUNCTION__));
        return -1;
    }


    if (stmmac->vendor_ctx.tx_task)
    {
        GMAC_WARNING(("%s:stmmac->vendor_ctx.tx_task:%x.\n",
                     __FUNCTION__, stmmac->vendor_ctx.tx_task));
        return 0;
    }

    skb_queue_head_init(&stmmac->vendor_ctx.tx_frames);
    init_completion(&stmmac->vendor_ctx.tx_kick);
    init_completion(&stmmac->vendor_ctx.tx_task_stop);
    spin_lock_init(&stmmac->vendor_ctx.tx_lock);

    snprintf(thread_name, sizeof(thread_name), "stmmactxthread");
    stmmac->vendor_ctx.tx_task = kthread_create(stmmac_vendor_tx_thread, stmmac,
                   thread_name);
    if (IS_ERR(stmmac->vendor_ctx.tx_task)) {
        GMAC_ERR(("create kthread stmmac_tx_thread failed!\n"));
        stmmac->vendor_ctx.tx_task_run = false;
        return (int)PTR_ERR(stmmac->vendor_ctx.tx_task);
    }
    GMAC_TX_DBG(("create kthread thread_name :%s, tx_task=%x \n", 
                    thread_name,stmmac->vendor_ctx.tx_task));
    sched_setscheduler(stmmac->vendor_ctx.tx_task , SCHED_FIFO, &param);
    wake_up_process(stmmac->vendor_ctx.tx_task);

    GMAC_TX_DBG(("%s line %d:leave\n",__FUNCTION__,__LINE__));

    return 0;
}
static void stmmac_vendor_tx_thread_stop(struct stmmac_priv *stmmac)
{

    if (!stmmac)
    {
        GMAC_ERR(("stmmac vendor tx thread abnormal quit!\n"));
        return;
    }

    if (stmmac->vendor_ctx.tx_task) {
        GMAC_WARNING(("stmmac tx thread quit %x !\n",
                             stmmac->vendor_ctx.tx_task));
        kthread_stop(stmmac->vendor_ctx.tx_task);
        stmmac->vendor_ctx.tx_task = NULL;
    }
}

static int stmmac_vendor_tx_thread_uninit(struct stmmac_priv *stmmac)
{
    struct sk_buff *skb = NULL;
    GMAC_TX_DBG(("%s in\n",__FUNCTION__));
    if (!stmmac)
    {
        return -1;
    }

    stmmac->vendor_ctx.tx_task_run = false;

    complete(&stmmac->vendor_ctx.tx_kick);
    wait_for_completion(&stmmac->vendor_ctx.tx_task_stop);

    do{
        skb = skb_dequeue(&stmmac->vendor_ctx.tx_frames);
        if(skb)
        {
            kfree_skb(skb);
        }
    }while(skb);
     
    stmmac_vendor_tx_thread_stop(stmmac);

    GMAC_TX_DBG(("%s out\n",__FUNCTION__));
    return 0;
}
#endif
