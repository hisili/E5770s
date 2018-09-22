
#ifndef _wlan_security_h_
#define _wlan_security_h_

#include <linux/skbuff.h>
#include <linux/netdevice.h>

#ifdef __cplusplus
    #if __cplusplus
    extern "C" {
    #endif
#endif

/*****************************************************************************
 ��������  : wlan_check_arp_spoofing
 ��������  : ���wlan��arp��ƭ
 �������  : port_dev: ���¹��豸, pskb: ��Ҫ�������ݰ�
 �������  : NA
 �� �� ֵ  : 0:����ARP��ƭ���ģ�1: ��ARP��ƭ����
*****************************************************************************/
int wlan_check_arp_spoofing(struct net_device *port_dev, struct sk_buff *pskb);

/*****************************************************************************
 ��������  : wl_chk_pkt_inBSS
 ��������  : �ṩ��BCM43236оƬ����ʹ�ã������ж�STA->STA�ı����Ƿ�����arp��ƭ���ж�
 �������  : *p: �ð���skbָ�� ,*from_device: wlan�ӿڵ�net_device�ṹָ��
 �������  : NA
 �� �� ֵ  : 0:����ARP��ƭ���ģ�1: ��ARP��ƭ����
*****************************************************************************/
int wl_chk_pkt_inBSS(struct net_device *from_device, void *p);

#ifdef __cplusplus
    #if __cplusplus
    }
    #endif
#endif   
#endif /* _wlan_security_h_ */
