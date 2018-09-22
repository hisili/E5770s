/*-
 * Copyright (c) 1999 Brian Somers <brian@Awfulhak.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $FreeBSD: src/usr.sbin/ppp/acf.c,v 1.5 2000/07/19 02:10:30 brian Exp $
 */
#if 0/*fanzhibin f49086 delete it*/
#include <sys/types.h>

#include <stdio.h>
#include <termios.h>
#include "pslog.h"
#include "defs.h"
#include "layer.h"
#include "timer.h"
#include "ppp_fsm.h"
#include "log.h"
#include "ppp_mbuf.h"
#include "acf.h"
#include "proto.h"
#include "throughput.h"
#include "lqr.h"
#include "hdlc.h"
#include "lcp.h"
#include "ccp.h"
#include "link.h"
#include "descriptor.h"
#include "async.h"
#include "physical.h"
#endif
/*fanzhibin f49086 add it begin*/
#include "PppInterface.h"
#include "ppp_public.h"
#include "layer.h"
#include "ppp_fsm.h"
#include "ppp_mbuf.h"
#include "acf.h"
#include "proto.h"
#include "throughput.h"
#include "hdlc.h"
#include "lcp.h"
#include "async.h"
#include "auth.h"
#include "ipcp.h"
#include "pppid.h"
#include "link.h"
/*fanzhibin f49086 add it end*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767  �޸���: z57034; ������: g45205 ԭ�����: �����־�ļ���ID���� */
#define    THIS_FILE_ID        PS_FILE_ID_ACF_C
/*lint +e767  �޸���: z57034; ������: g45205 */


#if(FEATURE_ON == FEATURE_PPP)

VOS_INT32
acf_WrapperOctets(struct lcp *lcp, VOS_UINT16 proto)
{
  return ( (proto == PROTO_LCP) || (lcp->his_acfcomp == 0)) ? 2 : 0;
}

struct ppp_mbuf *
acf_LayerPush(/*struct bundle *b, */struct link *l, struct ppp_mbuf *bp,
              VOS_INT32 pri, VOS_UINT16 *proto)
{
  const VOS_UCHAR cp[2] = { HDLC_ADDR, HDLC_UI };

  if ( (*proto == PROTO_LCP) || (l->lcp.his_acfcomp == 0) ) {
    bp = ppp_m_prepend(bp, cp, 2, 0);
  }

  return bp;
}

PPP_ZC_STRU *acf_LayerPull(/*struct bundle *b, */struct link *l, PPP_ZC_STRU *pstMem, VOS_UINT16 *pusProto)
{
    VOS_UINT32  ulRst;
    VOS_UCHAR   cp[2];


    ulRst = PPP_MemGet(pstMem, 0, cp, 2);

    if (PS_SUCC == ulRst)
    {
        if (!l->lcp.want_acfcomp)
        {
            /* We expect the packet not to be compressed */
            PPP_MemCutHeadData(&pstMem, cp, 2);

            if (cp[0] != HDLC_ADDR)
            {
                l->hdlc.lqm.SaveInErrors++;
                l->hdlc.stats.badaddr++;
                PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "acf_LayerPull: addr:%c ", cp[0]);
                PPP_MemFree(pstMem);

                return VOS_NULL_PTR;
            }

            if (cp[1] != HDLC_UI)
            {
                l->hdlc.lqm.SaveInErrors++;
                l->hdlc.stats.badcommand++;
                PPP_MNTN_LOG1(PS_PID_APP_PPP, 0, PS_PRINT_NORMAL, "acf_LayerPull: control :%d", cp[1]);
                PPP_MemFree(pstMem);

                return VOS_NULL_PTR;
            }
        }
        else if ( (cp[0] == HDLC_ADDR) && (cp[1] == HDLC_UI) )
        {
            /*
            * We can receive compressed packets, but the peer still sends
            * uncompressed packets (or maybe this is a PROTO_LCP packet) !
            */
            PPP_MemCutHeadData(&pstMem, cp, 2);
        }
        else
        {
            ;
        }
    }

    return pstMem;
} /* acf_LayerPull */


struct layer acflayer = { LAYER_ACF, "acf", acf_LayerPush, acf_LayerPull };

#endif /* #if(FEATURE_ON == FEATURE_PPP) */

