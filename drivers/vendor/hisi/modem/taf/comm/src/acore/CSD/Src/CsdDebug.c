

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CsdDebug.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if( FEATURE_ON == FEATURE_CSD )

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
CSD_UL_STATUS_INFO_STRU                 g_stCsdStatusInfo = {0};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_VOID CSD_ShowULStatus(VOS_VOID)
{
    vos_printf("CSD�յ��������ݵĸ���                             %d\n",g_stCsdStatusInfo.ulULRecvPktNum);
    vos_printf("CSD���л��������ݰ��ĸ���                         %d\n",g_stCsdStatusInfo.ulULSaveBuffPktNum);
    vos_printf("CSD�������ʧ�ܵĴ���                             %d\n",g_stCsdStatusInfo.ulULEnQueFail);
    vos_printf("CSD�������л��������                             %d\n",g_stCsdStatusInfo.ulULSendPktNum);
    vos_printf("CSD������������ʱ�Ӷ����л�ȡ����ָ�����Ŀ       %d\n",g_stCsdStatusInfo.ulULQueNullNum);
    vos_printf("CSD������������sk_bufferͷת����IMMͷʧ�ܵİ���Ŀ %d\n",g_stCsdStatusInfo.ulULZcToImmFailNum);
    vos_printf("CSD�����������ݲ���DICCͨ��ʧ�ܵİ���Ŀ           %d\n",g_stCsdStatusInfo.ulULInsertDiccFailNum);
    vos_printf("\r\n");

    return;
}

VOS_VOID CSD_ShowDLStatus(VOS_VOID)
{
    vos_printf("CSD�յ��������ݵĸ���                             %d\n",g_stCsdStatusInfo.ulDLRecvPktNum);
    vos_printf("CSD�������л��������                             %d\n",g_stCsdStatusInfo.ulDLSendPktNum);
    vos_printf("CSD���з���ʧ�ܰ�����Ŀ                           %d\n",g_stCsdStatusInfo.ulDLSendFailNum);
    vos_printf("\r\n");

    return;
}

VOS_VOID CSD_Help(VOS_VOID)
{
    vos_printf("********************CSD�����Ϣ************************\n");
    vos_printf("CSD_ShowULStatus                         ��ʾCSD����ͳ����Ϣ\n");
    vos_printf("CSD_ShowDLStatus                         ��ʾCSD����ͳ����Ϣ\n");

    return;
}









#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
