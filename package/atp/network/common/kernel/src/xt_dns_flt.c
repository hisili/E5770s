#include <linux/ipv6.h>
#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <net/checksum.h>
#include <linux/udp.h>
#include <linux/in.h>

#include <linux/netfilter_ipv4.h>
#include <linux/netfilter_ipv6.h>
#include <linux/netfilter/x_tables.h>
#include <linux/netfilter/xt_dns_flt.h>
#include <linux/ctype.h>
MODULE_AUTHOR("Kevert <Kevert@huawei.com>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("iptables dns filter module");
MODULE_ALIAS("ipt_dns_flt");
MODULE_ALIAS("ip6t_dns_flt");


static void dnschangelower(unsigned char* pszUrl, unsigned int ulLen)
{
    int i = 0;

    for (i = 0; i < ulLen; i++)
    {
        pszUrl[i] = tolower(pszUrl[i]);
    }
}

static bool dns_match(const struct sk_buff *skb, struct xt_action_param *par)
{
    // ip ͷ�еĳ��ȱ�ʾ�ײ�ռ32bit�ֵ���Ŀ
    const int ip_header_len_unit = 4;
    
    struct iphdr *iph = ip_hdr(skb);
    struct udphdr  stUdp, *pstUdpHdr = NULL;
    struct stDnsMsgHdr *pstDnsHdr = NULL;
    const  URL_STRING_ST *pstinfo = (URL_STRING_ST *)(par->matchinfo);
    unsigned char *ptr = NULL;
    unsigned int i = 0;
    unsigned char ucStrLen = 0;
    unsigned int ulBuffLen = 0;
    unsigned char acBuff[URL_STRING_LEN] = {0};
    unsigned char acurl[URL_STRING_LEN] = {0};
    if ((NULL == iph) || (iph->protocol != IPPROTO_UDP))
    {
        return false;
    }
    
    pstUdpHdr = ((char*)iph) + (iph->ihl * ip_header_len_unit);    
    //pstUdpHdr = skb_header_pointer(skb, protoff, sizeof(stUdp), &stUdp);
    
    if (NULL == pstUdpHdr)
    {
        DEBUGPC("get udp header failed\n");
        return false;
    }
    /* AU4D02197 atp 2009-9-3 */
    
    if ((ntohs(pstUdpHdr->len) - sizeof(stUdp)) <= sizeof(struct stDnsMsgHdr))
    {
        DEBUGPC("udp size is not correct\n");
        return false;
    }
    
    ptr = (unsigned char *)(pstUdpHdr + 1);
    pstDnsHdr = (struct stDnsMsgHdr *)ptr;
    ptr += sizeof(struct stDnsMsgHdr);
    /* ֻ�����ѯ���� */    
    if ((ntohs(pstDnsHdr->u16Coms) >> 15) != URL_FLT_DNS_QUERY_CODE)
    {
        DEBUGPC("no query packet......");
        return false;
    }    
	memcpy(acurl,pstinfo->acURL,URL_STRING_LEN);
	dnschangelower(acurl,strlen(acurl));
	
    DEBUGPC("begin to lookup %s", pstinfo->acURL);

    for (i = 0; (i < ntohs(pstDnsHdr->u16QDcnt)) && (ptr < skb->tail); i++)
    {
        DEBUGPC("url in packet: %s", acBuff);
        memset(acBuff, 0, URL_STRING_LEN);
        do
        {
            ucStrLen = *ptr;        /* ָ�򳤶� */
            ptr++;                  /* ָ������ */            
            if (0 == ucStrLen)
            {
                ulBuffLen = strlen(acBuff);
                if (ulBuffLen)
                {
                    acBuff[ulBuffLen - 1] = '\0';
                }
	            dnschangelower(acBuff,ulBuffLen);
                DEBUGPC("Get dns name: %s, begin to fund: %s %s", acBuff, pstinfo->acURL,acurl);
                if (strstr(acBuff, acurl))
                {
                    DEBUGPC("found the url: %s\r\n\r\n", acurl);
                    return (((1 ^ pstinfo->u16Inv) > 0)? true : false);
                }
                ptr += (2 * sizeof(uint16_t));    /* ָ����һ����¼ */
                break;
            }
            
            if ((ptr + ucStrLen) > skb->tail)
            {
                DEBUGPC("Get dns name: %s, begin to fund: %s", acBuff, acurl);
				dnschangelower(acBuff,URL_STRING_LEN);
                if (strstr(acBuff, acurl))
                {
                    return (((1 ^ pstinfo->u16Inv) > 0)? true : false);
                }
                return (((0 | pstinfo->u16Inv) > 0)? true : false);
            }

            /* ��ֹ��Ϊ���⹹��DNS��ѯ�����ܳ��ȳ����˻��������ܵ������� */
            if ((URL_STRING_LEN - 1) < (strlen(acBuff) + ucStrLen))
            {
                DEBUGPC("Get dns name: %s, begin to fund: %s", acBuff, acurl);
				dnschangelower(acBuff,URL_STRING_LEN);
                if (strstr(acBuff, acurl))
                {
                    return (((1 ^ pstinfo->u16Inv) > 0)? true : false);
                }
                return (((0 | pstinfo->u16Inv) > 0)? true : false);
            }
            
            strncat(acBuff, ptr, ucStrLen);
            acBuff[strlen(acBuff)] = '.';
            ptr += ucStrLen;
            
        }while (1);
    }

    DEBUGPC("can not found the url: %s", pstinfo->acURL);
	
    return (((0 | pstinfo->u16Inv) > 0)? true : false);
}

static bool dns_match_v6(const struct sk_buff *skb, struct xt_action_param *par)
{
    DEBUGPC("----dns_match_v6\n");
    struct ipv6hdr *ip6h = ipv6_hdr(skb);
    struct udphdr  stUdp, *pstUdpHdr = NULL;
    struct stDnsMsgHdr *pstDnsHdr = NULL;
    const  URL_STRING_ST *pstinfo = (URL_STRING_ST *)(par->matchinfo);
    unsigned char *ptr = NULL;
    unsigned int i = 0;
    unsigned char ucStrLen = 0;
    unsigned int ulBuffLen = 0;
    unsigned char acBuff[URL_STRING_LEN] = {0};
    unsigned char acurl[URL_STRING_LEN] = {0};
    
    if ((NULL == ip6h) || (ip6h->nexthdr != IPPROTO_UDP))
    {
        return false;
    }

    pstUdpHdr = udp_hdr(skb);
    
    if (NULL == pstUdpHdr)
    {
        DEBUGPC("------get udp header failed\n");
        return false;
    }

    
    if ((ntohs(pstUdpHdr->len) - sizeof(stUdp)) <= sizeof(struct stDnsMsgHdr))
    {
        DEBUGPC("udp size is not correct\n");
        return false;
    }
    
    ptr = (unsigned char *)(pstUdpHdr + 1);
    pstDnsHdr = (struct stDnsMsgHdr *)ptr;
    ptr += sizeof(struct stDnsMsgHdr);
    /* ֻ�����ѯ���� */    
    if ((ntohs(pstDnsHdr->u16Coms) >> 15) != URL_FLT_DNS_QUERY_CODE)
    {
        DEBUGPC("no query packet......");
        return false;
    }    
	memcpy(acurl,pstinfo->acURL,URL_STRING_LEN);
	dnschangelower(acurl,strlen(acurl));
    DEBUGPC("begin to lookup %s %s\n", pstinfo->acURL,acurl);
    
    for (i = 0; (i < ntohs(pstDnsHdr->u16QDcnt)) && (ptr < skb->tail); i++)
    {
        DEBUGPC("url in packet: %s", acBuff);
        memset(acBuff, 0, URL_STRING_LEN);
        do
        {
            ucStrLen = *ptr;        /* ָ�򳤶� */
            ptr++;                  /* ָ������ */            
            if (0 == ucStrLen)
            {
                ulBuffLen = strlen(acBuff);
                if (ulBuffLen)
                {
                    acBuff[ulBuffLen - 1] = '\0';
                }
				dnschangelower(acBuff,ulBuffLen);
                DEBUGPC("Get dns name: %s, begin to fund: %s", acBuff, acurl);
                if (strstr(acBuff, acurl))
                {
                    printk("found the url: %s\r\n\r\n", acurl);
                    return (((1 ^ pstinfo->u16Inv) > 0)? true : false);
                }
                ptr += (2 * sizeof(uint16_t));    /* ָ����һ����¼ */
                break;
            }
            
            if ((ptr + ucStrLen) > skb->tail)
            {
                DEBUGPC("Get dns name: %s, begin to fund: %s", acBuff, acurl);
				dnschangelower(acBuff,URL_STRING_LEN);
                if (strstr(acBuff, acurl))
                {
                    return (((1 ^ pstinfo->u16Inv) > 0)? true : false);
                }
                return (((0 | pstinfo->u16Inv) > 0)? true : false);
            }

            /* ��ֹ��Ϊ���⹹��DNS��ѯ�����ܳ��ȳ����˻��������ܵ������� */
            if ((URL_STRING_LEN - 1) < (strlen(acBuff) + ucStrLen))
            {
                DEBUGPC("Get dns name: %s, begin to fund: %s", acBuff, acurl);
				dnschangelower(acBuff,URL_STRING_LEN);
                if (strstr(acBuff, acurl))
                {
                    return (((1 ^ pstinfo->u16Inv) > 0)? true : false);
                }
                return (((0 | pstinfo->u16Inv) > 0)? true : false);
            }
            
            strncat(acBuff, ptr, ucStrLen);
            acBuff[strlen(acBuff)] = '.';
            ptr += ucStrLen;
            
        }while (1);
    }

    DEBUGPC("can not found the url: %s", pstinfo->acURL);
	
    return (((0 | pstinfo->u16Inv) > 0)? true : false);
}


static struct xt_match xt_dns_flt_match[] __read_mostly = 
{
    {
        .name		= "dns_flt",
        .family		= NFPROTO_IPV4,
        .match		= dns_match,
        .matchsize	= sizeof(URL_STRING_ST),
        .proto		= IPPROTO_UDP,
        .me		    = THIS_MODULE,
    },
    {
        .name		= "dns_flt",
        .family		= NFPROTO_IPV6,
        .match		= dns_match_v6,
        .matchsize	= sizeof(URL_STRING_ST),
        .proto		= IPPROTO_UDP,
        .me		    = THIS_MODULE,
    },
};

static int __init xt_dns_flt_init(void)
{
    DEBUGPC("register the dns_flt kernel module.");
    return xt_register_matches(xt_dns_flt_match, ARRAY_SIZE(xt_dns_flt_match));
}

static void __exit xt_dns_flt_fini(void)
{
    xt_unregister_matches(xt_dns_flt_match, ARRAY_SIZE(xt_dns_flt_match));
}

module_init(xt_dns_flt_init);
module_exit(xt_dns_flt_fini);

