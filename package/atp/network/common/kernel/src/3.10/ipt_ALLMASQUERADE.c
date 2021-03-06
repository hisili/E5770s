/* Masquerade.  Simple mapping which alters range to a local IP address
   (depending on route). */

/* (C) 1999-2001 Paul `Rusty' Russell
 * (C) 2002-2006 Netfilter Core Team <coreteam@netfilter.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/types.h>
#include <linux/inetdevice.h>
#include <linux/ip.h>
#include <linux/timer.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <net/protocol.h>
#include <net/ip.h>
#include <net/checksum.h>
#include <net/route.h>
#include <net/netfilter/nf_nat.h>
#include <linux/netfilter_ipv4.h>
#include <linux/netfilter/x_tables.h>

//#ifdef CONFIG_MIPS_BRCM
#include <net/netfilter/nf_conntrack.h>
#include <net/netfilter/nf_conntrack_core.h>
#include <net/netfilter/nf_conntrack_zones.h>
#include <net/netfilter/nf_conntrack_helper.h>
#include <net/netfilter/nf_nat.h>
//#include <net/netfilter/nf_nat_rule.h>
#include <net/netfilter/nf_nat_helper.h>
#include <linux/netfilter_ipv4/ipt_allconenat.h>
//#endif /* CONFIG_MIPS_BRCM */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Netfilter Core Team <coreteam@netfilter.org>");
MODULE_DESCRIPTION("Xtables: automatic-address SNAT");

/* Lock protects masq region inside conntrack */
static DEFINE_RWLOCK(masq_lock);

#if 1 //form CONFIG_MIPS_BRCM

typedef int (*pfn_exp_match)(struct nf_conntrack_expect * i, 
                    struct nf_conntrack_tuple * tp);

/****************************************************************************/
static void bcm_nat_expect(struct nf_conn *ct,
			   struct nf_conntrack_expect *exp)
{
	struct nf_nat_range range;

	/* This must be a fresh one. */
	BUG_ON(ct->status & IPS_NAT_DONE_MASK);

	/* Change src to where new ct comes from */
	range.flags = IP_NAT_RANGE_MAP_IPS;
	range.min_addr.ip = range.max_addr.ip =
		ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip;
	nf_nat_setup_info(ct, &range, IP_NAT_MANIP_SRC);
	 
	/* For DST manip, map port here to where it's expected. */
	range.flags = (IP_NAT_RANGE_MAP_IPS | IP_NAT_RANGE_PROTO_SPECIFIED);
	range.min_proto = range.max_proto = exp->saved_proto;
	range.min_addr = range.max_addr = exp->saved_addr;
	nf_nat_setup_info(ct, &range, IP_NAT_MANIP_DST);
}

/****************************************************************************/
static int bcm_nat_help(struct sk_buff *skb, unsigned int protoff,
			struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{
	int dir = CTINFO2DIR(ctinfo);
	struct nf_conn_help *help = nfct_help(ct);
	struct nf_conntrack_expect *exp;
	
	if (dir != IP_CT_DIR_ORIGINAL ||
	    help->expecting[NF_CT_EXPECT_CLASS_DEFAULT])
		return NF_ACCEPT;

	pr_debug("bcm_nat: packet[%d bytes] ", skb->len);
	nf_ct_dump_tuple(&ct->tuplehash[dir].tuple);
	pr_debug("reply: ");
	nf_ct_dump_tuple(&ct->tuplehash[!dir].tuple);
	
	/* Create expect */
	if ((exp = nf_ct_expect_alloc(ct)) == NULL)
		return NF_ACCEPT;

	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, AF_INET, NULL,
			  &ct->tuplehash[!dir].tuple.dst.u3, IPPROTO_UDP,
			  NULL, &ct->tuplehash[!dir].tuple.dst.u.udp.port);
	exp->flags = NF_CT_EXPECT_PERMANENT;
	exp->saved_addr.ip= ct->tuplehash[dir].tuple.src.u3.ip;
	exp->saved_proto.udp.port = ct->tuplehash[dir].tuple.src.u.udp.port;
	exp->dir = !dir;
	exp->expectfn = bcm_nat_expect;
#if defined(CONFIG_NF_CONNTRACK_RTCP) || (defined(CONFIG_NF_CONNTRACK_RTCP_MODULE) && defined(CONFIG_MODULES))   
    extern struct nf_conntrack_helper nf_conntrack_rtcp_helper;
    if (htons(8027) == ct->tuplehash[dir].tuple.dst.u.udp.port)
        exp->helper = &nf_conntrack_rtcp_helper;
#endif

	/* Setup expect */
	nf_ct_expect_related(exp);
	nf_ct_expect_put(exp);
	pr_debug("bcm_nat: expect setup\n");

	return NF_ACCEPT;
}

static int bcm_addr_restricted_nat_help(struct sk_buff *skb, unsigned int protoff,
			struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{
	int dir = CTINFO2DIR(ctinfo);
	struct nf_conn_help *help = nfct_help(ct);
	struct nf_conntrack_expect *exp;
	
	if (dir != IP_CT_DIR_ORIGINAL ||
	    help->expecting[NF_CT_EXPECT_CLASS_DEFAULT])
		return NF_ACCEPT;

	pr_debug("bcm_nat: packet[%d bytes] ", skb->len);
	nf_ct_dump_tuple(&ct->tuplehash[dir].tuple);
	pr_debug("reply: ");
	nf_ct_dump_tuple(&ct->tuplehash[!dir].tuple);
	
	/* Create expect */
	if ((exp = nf_ct_expect_alloc(ct)) == NULL)
		return NF_ACCEPT;

	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, AF_INET, 
              &ct->tuplehash[!dir].tuple.src.u3,
			  &ct->tuplehash[!dir].tuple.dst.u3, IPPROTO_UDP,
			  NULL, &ct->tuplehash[!dir].tuple.dst.u.udp.port);
	exp->flags = NF_CT_EXPECT_PERMANENT;
	exp->saved_addr.ip = ct->tuplehash[dir].tuple.src.u3.ip;
	exp->saved_proto.udp.port = ct->tuplehash[dir].tuple.src.u.udp.port;
	exp->dir = !dir;
	exp->expectfn = bcm_nat_expect;

	/* Setup expect */
	nf_ct_expect_related(exp);
	nf_ct_expect_put(exp);
	pr_debug("bcm_nat: expect setup\n");

	return NF_ACCEPT;
}


static int bcm_port_restricted_nat_help(struct sk_buff *skb, unsigned int protoff,
			struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{
	int dir = CTINFO2DIR(ctinfo);
	struct nf_conn_help *help = nfct_help(ct);
	struct nf_conntrack_expect *exp;
	
	if (dir != IP_CT_DIR_ORIGINAL ||
	    help->expecting[NF_CT_EXPECT_CLASS_DEFAULT])
		return NF_ACCEPT;

	pr_debug("bcm_nat: packet[%d bytes] ", skb->len);
	nf_ct_dump_tuple(&ct->tuplehash[dir].tuple);
	pr_debug("reply: ");
	nf_ct_dump_tuple(&ct->tuplehash[!dir].tuple);
	
	/* Create expect */
	if ((exp = nf_ct_expect_alloc(ct)) == NULL)
		return NF_ACCEPT;

	nf_ct_expect_init(exp, NF_CT_EXPECT_CLASS_DEFAULT, AF_INET, NULL,
			  &ct->tuplehash[!dir].tuple.dst.u3, IPPROTO_UDP,
			  &ct->tuplehash[!dir].tuple.src.u.udp.port, 
			  &ct->tuplehash[!dir].tuple.dst.u.udp.port);
	exp->flags = NF_CT_EXPECT_PERMANENT;
	exp->saved_addr.ip = ct->tuplehash[dir].tuple.src.u3.ip;
	exp->saved_proto.udp.port = ct->tuplehash[dir].tuple.src.u.udp.port;
	exp->dir = !dir;
	exp->expectfn = bcm_nat_expect;

	/* Setup expect */
	nf_ct_expect_related(exp);
	nf_ct_expect_put(exp);
	pr_debug("bcm_nat: expect setup\n");

	return NF_ACCEPT;
}


/****************************************************************************/
static struct nf_conntrack_expect_policy bcm_nat_exp_policy __read_mostly = {
	.max_expected 	= 1000,
	.timeout	= 240,
};

/****************************************************************************/
#if defined(CONFIG_NF_CONNTRACK_RTCP) || (defined(CONFIG_NF_CONNTRACK_RTCP_MODULE) && defined(CONFIG_MODULES))
int (*bcm_nat_rtcp_help_hook)(struct sk_buff *skb,
                unsigned int protoff,
                struct nf_conn *ct,
                enum ip_conntrack_info ctinfo) __read_mostly;
EXPORT_SYMBOL_GPL(bcm_nat_rtcp_help_hook);

static int bcm_core_nat_help(struct sk_buff *skb, unsigned int protoff,
			struct nf_conn *ct, enum ip_conntrack_info ctinfo)
{
    bcm_nat_help(skb, protoff, ct, ctinfo);
    
    typeof(bcm_nat_rtcp_help_hook) nf_set_rtcp_help; 
    nf_set_rtcp_help = rcu_dereference (bcm_nat_rtcp_help_hook);
    if (nf_set_rtcp_help && ct->status & IPS_NAT_MASK)
    {
        nf_set_rtcp_help(skb, protoff, ct, ctinfo);
        printk("bcm_core_nat_help: rtcp_help\n\n\n\n\n");         
    }

    return NF_ACCEPT;
}

static struct nf_conntrack_expect_policy bcm_core_nat_exp_policy[2] __read_mostly = {
	[NF_CT_EXPECT_CLASS_DEFAULT] = {
		.max_expected	= 1000,
		.timeout	= 240,
	},
	[NF_CT_EXPECT_CLASS_DEFAULT + 1] = {//for rtcp
		.max_expected	= 1000,
		.timeout	= 3 * 60,
	},  
};

static struct nf_conntrack_helper nf_conntrack_helper_bcm_nat __read_mostly = {
	.name = "BCM-NAT",
	.me = THIS_MODULE,
	.tuple.src.l3num = AF_INET,
	.tuple.dst.protonum = IPPROTO_UDP,
	.expect_policy = bcm_core_nat_exp_policy,
	.expect_class_max = 2,
	.help = bcm_core_nat_help,
};
#else 
static struct nf_conntrack_helper nf_conntrack_helper_bcm_nat __read_mostly = {
	.name = "BCM-NAT",
	.me = THIS_MODULE,
	.tuple.src.l3num = AF_INET,
	.tuple.dst.protonum = IPPROTO_UDP,
	.expect_policy = &bcm_nat_exp_policy,
	.expect_class_max = 1,
	.help = bcm_nat_help,
};
#endif  

static struct nf_conntrack_helper nf_conntrack_helper_addr_restricted_nat __read_mostly = {
	.name = "ADDRCONE-NAT",
	.me = THIS_MODULE,
	.tuple.src.l3num = AF_INET,
	.tuple.dst.protonum = IPPROTO_UDP,
	.expect_policy = &bcm_nat_exp_policy,
	.expect_class_max = 1,
	.help = bcm_addr_restricted_nat_help,
};

static struct nf_conntrack_helper nf_conntrack_helper_port_restricted_nat __read_mostly = {
	.name = "PORTCONE-NAT",
	.me = THIS_MODULE,
	.tuple.src.l3num = AF_INET,
	.tuple.dst.protonum = IPPROTO_UDP,
	.expect_policy = &bcm_nat_exp_policy,
	.expect_class_max = 1,
	.help = bcm_port_restricted_nat_help,
};


/****************************************************************************/
static inline int find_exp(__be32 ip, __be16 port, struct nf_conn *ct)
{
	struct nf_conntrack_tuple tuple;
	struct nf_conntrack_expect *i = NULL;

	
	memset(&tuple, 0, sizeof(tuple));
	tuple.src.l3num = AF_INET;
	tuple.dst.protonum = IPPROTO_UDP;
	tuple.dst.u3.ip = ip;
	tuple.dst.u.udp.port = port;

	rcu_read_lock();
	i = __nf_ct_expect_find(nf_ct_net(ct),nf_ct_zone(ct),&tuple);
	rcu_read_unlock();

	return i != NULL;
}


static inline int fullcone_exp_match(struct nf_conntrack_expect * i, 
                    struct nf_conntrack_tuple * tp)
{
    return (i->saved_addr.ip == tp->src.u3.ip &&
        	    i->saved_proto.all == tp->src.u.all &&
        	    i->tuple.dst.protonum == tp->dst.protonum &&
        	    i->tuple.src.u3.ip == 0 &&
        	    i->tuple.src.u.udp.port == 0);
}

static inline int addr_cone_exp_match(struct nf_conntrack_expect * i, 
                    struct nf_conntrack_tuple * tp)
{
    return (i->saved_addr.ip == tp->src.u3.ip &&
        	    i->saved_proto.all == tp->src.u.all &&
        	    i->tuple.dst.protonum == tp->dst.protonum &&
        	    i->tuple.src.u3.ip == tp->src.u3.ip &&
        	    i->tuple.src.u.udp.port == 0);
}

static inline int port_cone_exp_match(struct nf_conntrack_expect * i, 
                    struct nf_conntrack_tuple * tp)
{
    return (i->saved_addr.ip == tp->src.u3.ip &&
        	    i->saved_proto.all == tp->src.u.all &&
        	    i->tuple.dst.protonum == tp->dst.protonum &&
        	    i->tuple.src.u3.ip == 0 &&
        	    i->tuple.src.u.udp.port == tp->src.u.udp.port);
}

static pfn_exp_match exp_match_func_array[CONE_NAT_TYPE_MAX] =
{
    fullcone_exp_match,        
    addr_cone_exp_match,
    port_cone_exp_match,
};

static struct nf_conntrack_helper *cone_nat_helper_array[CONE_NAT_TYPE_MAX] =
{
    &nf_conntrack_helper_bcm_nat,
    &nf_conntrack_helper_addr_restricted_nat,
    &nf_conntrack_helper_port_restricted_nat,
};

/****************************************************************************/
static inline struct nf_conntrack_expect *find_cone_exp(struct nf_conn *ct, int nattype)
{
	struct nf_conntrack_tuple * tp =
		&ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple;
	struct net *net = nf_ct_net(ct);
	struct nf_conntrack_expect * exp = NULL;
	struct nf_conntrack_expect * i;
	unsigned int h;
    pfn_exp_match match;

    match = exp_match_func_array[nattype];

	rcu_read_lock();
	for (h = 0; h < nf_ct_expect_hsize; h++) {
		hlist_for_each_entry_rcu(i, &net->ct.expect_hash[h], hnode) {
			if (match(i, tp)) {
				exp = i;
				break;
			}
		}
	}
	rcu_read_unlock();

	return exp;
}

#endif /* CONFIG_MIPS_BRCM */

/* FIXME: Multiple targets. --RR */
static int masquerade_tg_check(const struct xt_tgchk_param *par)
{
    struct ip_cone_nat_data *p = NULL;
	struct nf_nat_multi_range_compat *mr = NULL;
    p = par->targinfo;;
    mr = &p->data;
    
	if (mr->range[0].flags & IP_NAT_RANGE_MAP_IPS) {
		pr_debug("masquerade_check: bad MAP_IPS.\n");
		return -EINVAL;
	}
	if (mr->rangesize != 1) {
		pr_debug("masquerade_check: bad rangesize %u\n", mr->rangesize);
		return -EINVAL;
	}

    if ((FULL_CONE_TYPE != p->cone_nat_type) && (ADDR_CONE_TYPE != p->cone_nat_type)
        && (PORT_CONE_TYPE != p->cone_nat_type))
    {
        pr_debug("cone nat type error\r\n");
        return -EINVAL;
    }
    
	return 0;
}

static unsigned int
masquerade_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	struct nf_conn *ct;
	struct nf_conn_nat *nat;
	enum ip_conntrack_info ctinfo;
	struct nf_nat_range newrange;
	const struct nf_nat_multi_range_compat *mr;
	const struct rtable *rt;
	__be32 newsrc;
    struct ip_cone_nat_data *p = NULL;

	NF_CT_ASSERT(par->hooknum == NF_INET_POST_ROUTING);

	ct = nf_ct_get(skb, &ctinfo);
	nat = nfct_nat(ct);

	NF_CT_ASSERT(ct && (ctinfo == IP_CT_NEW || ctinfo == IP_CT_RELATED
			    || ctinfo == IP_CT_RELATED + IP_CT_IS_REPLY));

	/* Source address is 0.0.0.0 - locally generated packet that is
	 * probably not supposed to be masqueraded.
	 */
	if (ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.u3.ip == 0)
		return NF_ACCEPT;

    p = (struct ip_cone_nat_data *)par->targinfo;
	mr = &p->data;
	rt = skb_rtable(skb);
	newsrc = inet_select_addr(par->out, rt->rt_gateway, RT_SCOPE_UNIVERSE);
	if (!newsrc) {
		printk("MASQUERADE: %s ate my IP address\n", par->out->name);
		return NF_DROP;
	}

	write_lock_bh(&masq_lock);
	nat->masq_index = par->out->ifindex;
	write_unlock_bh(&masq_lock);
	
#if 1 //from CONFIG_MIPS_BRCM
/*这里默认fullcone 的标记min_addr为1，不去判断 mr->range[0].min_addr != 0  nat_mode == full cone */ 
	if ((nfct_help(ct) == NULL || nfct_help(ct)->helper == NULL)
	    && nf_ct_protonum(ct) == IPPROTO_UDP) {
		unsigned int ret;
		u_int16_t minport;
		u_int16_t maxport;
		struct nf_conntrack_expect *exp;

		pr_debug("bcm_nat: need full cone NAT\n");

		/* Choose port */
		spin_lock_bh(&nf_conntrack_lock);
		/* Look for existing expectation */
		exp = find_cone_exp(ct, p->cone_nat_type);
		if (exp) {
    		minport = maxport = exp->tuple.dst.u.udp.port;
			pr_debug("bcm_nat: existing mapped port = %hu\n",
			       	 ntohs(minport));
		} else { /* no previous expect */
			u_int16_t newport, tmpport;
			
			minport = mr->range[0].min_proto.all == 0? 
				ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple.src.
				u.udp.port : mr->range[0].min_proto.all;
			maxport = mr->range[0].max_proto.all == 0? 
				htons(65535) : mr->range[0].max_proto.all;
			for (newport = ntohs(minport),tmpport = ntohs(maxport); 
			     newport <= tmpport; newport++) {
			     	if (!find_exp(newsrc, htons(newport), ct)) {
					pr_debug("bcm_nat: new mapped port = "
					       	 "%hu\n", newport);
					minport = maxport = htons(newport);
					break;
				}
			}
		}
		spin_unlock_bh(&nf_conntrack_lock);

		/*
		newrange = ((struct nf_nat_range)
			{ mr->range[0].flags | IP_NAT_RANGE_MAP_IPS |
			  IP_NAT_RANGE_PROTO_SPECIFIED, newsrc, newsrc,
		  	  mr->range[0].min, mr->range[0].max });
		*/
		newrange.flags = mr->range[0].flags | IP_NAT_RANGE_MAP_IPS |
			IP_NAT_RANGE_PROTO_SPECIFIED;
		newrange.max_addr.ip = newrange.min_addr.ip = newsrc;
		newrange.min_proto.udp.port = newrange.max_proto.udp.port = minport;
	
		/* Set ct helper */
		ret = nf_nat_setup_info(ct, &newrange, IP_NAT_MANIP_SRC);
		if (ret == NF_ACCEPT) {
			struct nf_conn_help *help = nfct_help(ct);
			if (help == NULL)
			{
				if (exp != NULL) 
				{
				    if(exp->helper != NULL)
				        help = nf_ct_helper_ext_add(ct, exp->helper, GFP_ATOMIC);
				}
			}
			if (help != NULL) {
				help->helper = cone_nat_helper_array[p->cone_nat_type];//&nf_conntrack_helper_bcm_nat;
				pr_debug("bcm_nat: helper set\n");
			}
		}
		return ret;
	}
#endif /* CONFIG_MIPS_BRCM */

	/* Transfer from original range. */
#if 0
	newrange = ((struct nf_nat_range)
		{ mr->range[0].flags | IP_NAT_RANGE_MAP_IPS,
		  newsrc, newsrc,
		  mr->range[0].min_proto, mr->range[0].max_proto});
#endif

	newrange.flags = mr->range[0].flags | IP_NAT_RANGE_MAP_IPS;
	newrange.min_addr.ip = newsrc;
	newrange.max_addr.ip = newsrc;
	newrange.min_proto = mr->range[0].min_proto;
	newrange.max_proto = mr->range[0].max_proto;
	/* Hand modified range to generic setup. */
	return nf_nat_setup_info(ct, &newrange, IP_NAT_MANIP_SRC);
}


static int device_cmp_with_master(struct nf_conn *ct, void *ifindex)
{
	struct nf_conn_nat *nat = NULL;
	struct nf_conn *ct_master = NULL;

	if (NULL == ct)
	{
		return 0;
	}

	ct_master = master_ct(ct);
	if (NULL == ct_master)
	{
		return 0;
	}

	nat = nfct_nat(ct_master);

	if (NULL == nat)
	{
		return 0;
	}

	return (nat->masq_index == (int)(long)ifindex);
}


static int
device_cmp(struct nf_conn *i, void *ifindex)
{
	const struct nf_conn_nat *nat = nfct_nat(i);
	int ret;

	if (!nat)
		return 0;

	read_lock_bh(&masq_lock);
	ret = (nat->masq_index == (int)(long)ifindex) || device_cmp_with_master(i, ifindex);
	read_unlock_bh(&masq_lock);

	return ret;
}

static int masq_device_event(struct notifier_block *this,
			     unsigned long event,
			     void *ptr)
{
	const struct net_device *dev = ptr;
	struct net *net = dev_net(dev);

	if (event == NETDEV_DOWN) {
		/* Device was downed.  Search entire table for
		   conntracks which were associated with that device,
		   and forget them. */
		NF_CT_ASSERT(dev->ifindex != 0);

		nf_ct_iterate_cleanup(net, device_cmp,
				      (void *)(long)dev->ifindex);
	}

	return NOTIFY_DONE;
}

static int masq_inet_event(struct notifier_block *this,
			   unsigned long event,
			   void *ptr)
{
	struct net_device *dev = ((struct in_ifaddr *)ptr)->ifa_dev->dev;
	return masq_device_event(this, event, dev);
}

static struct notifier_block masq_dev_notifier = {
	.notifier_call	= masq_device_event,
};

static struct notifier_block masq_inet_notifier = {
	.notifier_call	= masq_inet_event,
};

static struct xt_target masquerade_tg_reg __read_mostly = {
	.name		= "ALLCONE_NAT",
	.family		= NFPROTO_IPV4,
	.target		= masquerade_tg,
	.targetsize	= sizeof(struct ip_cone_nat_data),
	.table		= "nat",
	.hooks		= 1 << NF_INET_POST_ROUTING,
	.checkentry	= masquerade_tg_check,
	.me		= THIS_MODULE,
};

static int __init masquerade_tg_init(void)
{
	int ret;

	ret = xt_register_target(&masquerade_tg_reg);

	if (ret == 0) {
		/* Register for device down reports */
		register_netdevice_notifier(&masq_dev_notifier);
		/* Register IP address change reports */
		register_inetaddr_notifier(&masq_inet_notifier);
	}

	return ret;
}

static void __exit masquerade_tg_exit(void)
{
#if 1 //from CONFIG_MIPS_BRCM
	nf_conntrack_helper_unregister(&nf_conntrack_helper_bcm_nat);
    nf_conntrack_helper_unregister(&nf_conntrack_helper_addr_restricted_nat);
    nf_conntrack_helper_unregister(&nf_conntrack_helper_port_restricted_nat);
#endif /* CONFIG_MIPS_BRCM */
	xt_unregister_target(&masquerade_tg_reg);
	unregister_netdevice_notifier(&masq_dev_notifier);
	unregister_inetaddr_notifier(&masq_inet_notifier);
}

module_init(masquerade_tg_init);
module_exit(masquerade_tg_exit);
