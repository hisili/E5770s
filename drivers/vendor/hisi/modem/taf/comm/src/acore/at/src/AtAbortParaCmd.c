

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AtParse.h"
#include "ATCmdProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID        PS_FILE_ID_AT_ABORTPARACMD_C
/*lint +e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_UINT32 At_AbortCopsPara(
    VOS_UINT8                           ucIndex
)
{
    /* ��ǰֻ�ܴ����б��ѵĴ��, ���������򲻽��д�ϲ��� */
    if ( AT_CMD_COPS_TEST == gastAtClientTab[ucIndex].CmdCurrentOpt )
    {
        /* AT��MMA���ʹ���б��ѵ����� */
        if ( AT_SUCCESS == TAF_AbortPlmnListReq(gastAtClientTab[ucIndex].usClientId, 0) )
        {
            /* ֹͣ�б���AT�ı�����ʱ�� */
            AT_StopRelTimer(ucIndex, &gastAtClientTab[ucIndex].hTimer);
            
            /* ���µ�ǰ�������� */
            gastAtClientTab[ucIndex].CmdCurrentOpt = AT_CMD_COPS_ABORT_PLMN_LIST;

            return AT_WAIT_ASYNC_RETURN;
        }
        else
        {
            return AT_FAILURE;
        }
    }
    else
    {
        return AT_FAILURE;
    }

}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

