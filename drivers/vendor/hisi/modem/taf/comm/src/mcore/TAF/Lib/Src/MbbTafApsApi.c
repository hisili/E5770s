/*
* Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
* foss@huawei.com
*
* If distributed as part of the Linux kernel, the following license terms
* apply:
*
* * This program is free software; you can redistribute it and/or modify
* * it under the terms of the GNU General Public License version 2 and 
* * only version 2 as published by the Free Software Foundation.
* *
* * This program is distributed in the hope that it will be useful,
* * but WITHOUT ANY WARRANTY; without even the implied warranty of
* * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* * GNU General Public License for more details.
* *
* * You should have received a copy of the GNU General Public License
* * along with this program; if not, write to the Free Software
* * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
*
* Otherwise, the following license terms apply:
*
* * Redistribution and use in source and binary forms, with or without
* * modification, are permitted provided that the following conditions
* * are met:
* * 1) Redistributions of source code must retain the above copyright
* *    notice, this list of conditions and the following disclaimer.
* * 2) Redistributions in binary form must reproduce the above copyright
* *    notice, this list of conditions and the following disclaimer in the
* *    documentation and/or other materials provided with the distribution.
* * 3) Neither the name of Huawei nor the names of its contributors may 
* *    be used to endorse or promote products derived from this software 
* *    without specific prior written permission.
* 
* * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
*/



/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/


#include "PsCommonDef.h"
#include "MbbTafApsApi.h"

#ifdef  __cplusplus
    #if  __cplusplus
    extern "C"{
    #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_API_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/

#if (FEATURE_ON == MBB_WPG_LTE_ATTACH_APN_LIST)

VOS_UINT32 TAF_PS_SetCustomAttachApnReq(
        VOS_UINT32                          ulModuleId,
        VOS_UINT16                          usClientId,
        VOS_UINT8                           ucOpId,
        TAF_CUSTOM_ATTACH_APN_INFO       *pstCustomAttachApn
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CUSTOM_ATTACH_APN_INFO_SET_REQ_STRU            stCustomAttachApnInfoReq;

    ulResult = VOS_ERR;
    PS_MEM_SET(&stCustomAttachApnInfoReq, 0x00, sizeof(TAF_PS_CUSTOM_ATTACH_APN_INFO_SET_REQ_STRU));

    /* �������Ϊ�գ�������첽��ʽ��ȡSDF��Ϣ */
    if (VOS_NULL_PTR == pstCustomAttachApn)
    {
        return VOS_ERR;
    }
    
    /* ����ID_MSG_TAF_PS_SET_CUSTOM_ATTACH_APN_REQ��Ϣ */
    stCustomAttachApnInfoReq.stCtrl.ulModuleId = ulModuleId;
    stCustomAttachApnInfoReq.stCtrl.usClientId = usClientId;
    stCustomAttachApnInfoReq.stCtrl.ucOpId     = ucOpId;

    PS_MEM_CPY(&stCustomAttachApnInfoReq.stCustomAttachApn, pstCustomAttachApn, sizeof(TAF_CUSTOM_ATTACH_APN_INFO));

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_CUSTOM_ATTACH_APN_REQ,
                             &stCustomAttachApnInfoReq,
                             sizeof(TAF_PS_CUSTOM_ATTACH_APN_INFO_SET_REQ_STRU));

    return ulResult;
}


VOS_UINT32 TAF_PS_GetCustomAttachApnReq(
        VOS_UINT32                          ulModuleId,
        VOS_UINT16                          usClientId,
        VOS_UINT8                           ucOpId,
        TAF_PS_CUSTOM_ATTACH_APN_INFO_EXT_STRU       *pstCustomGetInfo
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CUSTOM_ATTACH_APN_INFO_GET_REQ_STRU            stCustomAttachApnInfoReq;

    ulResult = VOS_ERR;
    PS_MEM_SET(&stCustomAttachApnInfoReq, 0x00, sizeof(TAF_PS_CUSTOM_ATTACH_APN_INFO_GET_REQ_STRU));

    /* �������Ϊ�գ�������첽��ʽ��ȡSDF��Ϣ */
    if (VOS_NULL_PTR == pstCustomGetInfo)
    {
        return VOS_ERR;
    }
    
    /* ����ID_MSG_TAF_PS_GET_CUSTOM_ATTACH_APN_REQ��Ϣ */
    stCustomAttachApnInfoReq.stCtrl.ulModuleId = ulModuleId;
    stCustomAttachApnInfoReq.stCtrl.usClientId = usClientId;
    stCustomAttachApnInfoReq.stCtrl.ucOpId     = ucOpId;

    PS_MEM_CPY(&stCustomAttachApnInfoReq.stExInfo, pstCustomGetInfo, sizeof(TAF_PS_CUSTOM_ATTACH_APN_INFO_EXT_STRU));

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_CUSTOM_ATTACH_APN_REQ,
                             &stCustomAttachApnInfoReq,
                             sizeof(TAF_PS_CUSTOM_ATTACH_APN_INFO_GET_REQ_STRU));

    return ulResult;
}


VOS_UINT32 TAF_PS_TestCustomAttachApnReq(
        VOS_UINT32                          ulModuleId,
        VOS_UINT16                          usClientId,
        VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulResult;
    TAF_PS_CUSTOM_ATTACH_APN_INFO_GET_REQ_STRU            stCustomAttachApnInfoReq;

    ulResult = VOS_ERR;
    PS_MEM_SET(&stCustomAttachApnInfoReq, 0x00, sizeof(TAF_PS_CUSTOM_ATTACH_APN_INFO_GET_REQ_STRU));
    
    /* ����ID_MSG_TAF_PS_GET_CUSTOM_ATTACH_APN_REQ��Ϣ */
    stCustomAttachApnInfoReq.stCtrl.ulModuleId = ulModuleId;
    stCustomAttachApnInfoReq.stCtrl.usClientId = usClientId;
    stCustomAttachApnInfoReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_TEST_CUSTOM_ATTACH_APN_REQ,
                             &stCustomAttachApnInfoReq,
                             sizeof(TAF_PS_CUSTOM_ATTACH_APN_INFO_GET_REQ_STRU));

    return ulResult;
}


VOS_UINT32 TAF_PS_SetLteApnAttachReq(
        VOS_UINT32                          ulModuleId,
        VOS_UINT16                          usClientId,
        VOS_UINT8                           ucOpId,
        AT_MTA_ATTACH_SWITCH_INFO_STRU      *pstApnOnOff
)
{
    VOS_UINT32     ulResult= VOS_ERR;
    TAF_PS_APN_ATTACH_SWITCH_SET_REQ_STRU   stApnAttachSwitchReq = {0};

    PS_MEM_SET(&stApnAttachSwitchReq, 0x00, sizeof(TAF_PS_APN_ATTACH_SWITCH_SET_REQ_STRU));

    /* �������Ϊ�գ�������첽��ʽ��ȡSDF��Ϣ */
    if (VOS_NULL_PTR == pstApnOnOff)
    {
        return VOS_ERR;
    }

    /* ����ID_MSG_TAF_PS_SET_APN_ATTACH_SWITCH_REQ��Ϣ */
    stApnAttachSwitchReq.stCtrl.ulModuleId = ulModuleId;
    stApnAttachSwitchReq.stCtrl.usClientId = usClientId;
    stApnAttachSwitchReq.stCtrl.ucOpId     = ucOpId;

    PS_MEM_CPY(&stApnAttachSwitchReq.stSwitchFlag, pstApnOnOff, sizeof(AT_MTA_ATTACH_SWITCH_INFO_STRU));

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_SET_APN_ATTACH_SWITCH_REQ,
                             &stApnAttachSwitchReq,
                             sizeof(TAF_PS_APN_ATTACH_SWITCH_SET_REQ_STRU));

    return ulResult;
}


VOS_UINT32 TAF_PS_GetApnAttachStatusReq(
        VOS_UINT32                          ulModuleId,
        VOS_UINT16                          usClientId,
        VOS_UINT8                           ucOpId)
{
    VOS_UINT32   ulResult = VOS_ERR;
    TAF_PS_APN_ATTACH_STAUTS_GET_REQ_STRU            stApnAttachStatusReq = {0};

    PS_MEM_SET(&stApnAttachStatusReq, 0x00, sizeof(TAF_PS_APN_ATTACH_STAUTS_GET_REQ_STRU));

    /* ����ID_MSG_TAF_PS_GET_APN_ATTACH_STATE_REQ��Ϣ */
    stApnAttachStatusReq.stCtrl.ulModuleId = ulModuleId;
    stApnAttachStatusReq.stCtrl.usClientId = usClientId;
    stApnAttachStatusReq.stCtrl.ucOpId     = ucOpId;

    /* ������Ϣ */
    ulResult = TAF_PS_SndMsg(I0_WUEPS_PID_TAF,
                             ID_MSG_TAF_PS_GET_APN_ATTACH_STATE_REQ,
                             &stApnAttachStatusReq,
                             sizeof(TAF_PS_APN_ATTACH_STAUTS_GET_REQ_STRU));

    return ulResult;
}

#endif

/*lint +e958*/

#ifdef  __cplusplus
    #if  __cplusplus
    }
    #endif
#endif
