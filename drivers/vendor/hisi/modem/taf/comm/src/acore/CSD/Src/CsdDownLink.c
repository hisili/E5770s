

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CsdDownLink.h"
#include "CsdDebug.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_CSD_DOWN_LINK_C
/*lint -e767 */

#if( FEATURE_ON == FEATURE_CSD )
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern VOS_UINT32 AT_SendCsdZcDataToModem(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                        *pstDataBuf
);


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_VOID CSD_DL_ProcIsr(VOS_VOID)
{
    VOS_UINT32                         *pDLDataSem;

    pDLDataSem  = CSD_GetDownLinkDataSem();

#if 0
    /*DICC�ر��ж�*/
    DICC_DisableIsr(ACPU_PID_CSD, DICC_SERVICE_TYPE_CSD_DATA, DICC_CPU_ID_ACPU);
#endif
    /*�ͷ�����ȡ�����ź���*/
    VOS_SmV(*pDLDataSem);
}


VOS_VOID CSD_DL_SendData(VOS_VOID)
{
    IMM_ZC_STRU                        *pstCsdDLMem;
    CST_CSD_DATA_IND_STRU               stDLData;
    VOS_UINT32                          ulDICCNodeCnt;
    VOS_UINT32                          ulRslt;
    VOS_CHAR                           *ImmZcData;


    for ( ; ; )
    {
        /*��ȡDICCͨ�����������ݵĸ���*/
        ulDICCNodeCnt = DICC_GetChannelCurrDataCnt(ACPU_PID_CSD,
                                                   DICC_CHAN_ID_DL_CSD_DATA_CHAN,
                                                   DICC_CPU_ID_ACPU);

        if ( DICC_INVALID_VALUE == ulDICCNodeCnt )
        {
            CSD_ERROR_LOG1(ACPU_PID_CSD,
                           "CSD_DL_SendData :: DICC_GetChannelCurrDataCnt is Wrong",
                           ulDICCNodeCnt);
            break;
        }

        if (0 != ulDICCNodeCnt )
        {
           /*��DICCͨ�����Ƴ�����*/
            ulRslt      = DICC_RemoveChannelData(ACPU_PID_CSD,
                                                 DICC_CHAN_ID_DL_CSD_DATA_CHAN,
                                                 (VOS_UINT8 *)(&stDLData),
                                                 DICC_CPU_ID_ACPU);

            if (DICC_OK != ulRslt)
            {
                CSD_ERROR_LOG1(ACPU_PID_CSD,
                              "CSD_DL_SendData:: enMsgId Illage",
                              ulRslt);
                break;
            }

            if (VOS_NULL_PTR == stDLData.pGarbage)
            {
                CSD_ERROR_LOG(ACPU_PID_CSD,
                              "CSD_DL_SendData:: stDLData.pGarbage Is Null");
                break;
            }

            CSD_DBG_DL_RECV_PKT_NUM(1);

            /*����sk_buffer�ڴ�*/
            pstCsdDLMem = IMM_ZcStaticAlloc(stDLData.usLen);

            if (VOS_NULL_PTR == pstCsdDLMem)
            {
                CSD_ERROR_LOG1(ACPU_PID_CSD,
                              "CSD_DL_SendData:: pstCsdDLMem Is Null IMM_ZcStaticAlloc Fail",
                              pstCsdDLMem);

                /*֪ͨcCpu�ͷ�TTFmem*/
                IMM_RemoteFreeTtfMem(stDLData.pGarbage);

                /*�˴���continue���ܵ�����ѭ��*/
                break;

            }

            /*�˲��費��������ƫ������βָ��*/
            /* Modified by l60609 for AP������Ŀ ��2012-08-31 Begin */
            ImmZcData = (VOS_CHAR *)IMM_ZcPut(pstCsdDLMem, stDLData.usLen);
            /* Modified by l60609 for AP������Ŀ ��2012-08-31 End */

            PS_MEM_CPY(ImmZcData, (VOS_UINT8 *)TTF_PHY_TO_VIRT((VOS_UINT32)stDLData.pucData), stDLData.usLen);

            /*�������ݵ�����,��һ������ΪpppidĿǰ��ʹ�ã�����ʧ��AT���ͷ��ڴ棬
            ���Դ˴�����Ҫ�����ͷ�a���ڴ�*/
            ulRslt      = AT_SendCsdZcDataToModem(CSD_UL_GetAtClientIndex(), pstCsdDLMem);

            if (VOS_OK != ulRslt)
            {
                CSD_DBG_DL_SEND_FAIL_NUM(1);

                CSD_ERROR_LOG(ACPU_PID_CSD,
                              "CSD_DL_SendData:: AT_SendZcDataToModem  Fail");

                /*֪ͨcCpu�ͷ�TTFmem*/
                IMM_RemoteFreeTtfMem(stDLData.pGarbage);

                /*�˴���continue���ܵ�����ѭ��*/
                break;
            }
            CSD_DBG_DL_SEND_PKT_NUM(1);

            /*֪ͨcCpu�ͷ�TTFmem*/
            IMM_RemoteFreeTtfMem(stDLData.pGarbage);

        }
        else
        {

            /*ͨ�������ݷ�����*/
            CSD_NORMAL_LOG1(ACPU_PID_CSD,
                            "CSD_DL_SendData Queue is Null",
                            ulDICCNodeCnt);

            break;
        }

        CSD_NORMAL_LOG1(ACPU_PID_CSD,
                        "CSD_DL_SendData Done",
                        ulDICCNodeCnt);

    }

}

VOS_VOID CSD_DL_ClearData(VOS_VOID)
{
    VOS_UINT32                          ulDICCNodeCnt;
    VOS_UINT32                          ulRslt;
    CST_CSD_DATA_IND_STRU               stDLData;


    /*��ȡDICCͨ�����������ݵĸ���*/
    ulDICCNodeCnt   = DICC_GetChannelCurrDataCnt(ACPU_PID_CSD,
                                                 DICC_CHAN_ID_DL_CSD_DATA_CHAN,
                                                 DICC_CPU_ID_ACPU);
    if ( DICC_INVALID_VALUE == ulDICCNodeCnt )
    {
        CSD_ERROR_LOG1(ACPU_PID_CSD,
                       "CSD_DL_ClearData :: DICC_GetChannelCurrDataCnt is Wrong",
                       ulDICCNodeCnt);
        return;
    }

    while ((0 != ulDICCNodeCnt))
    {

        /*��DICCͨ�����Ƴ�����*/
        ulRslt      = DICC_RemoveChannelData(ACPU_PID_CSD,
                                             DICC_CHAN_ID_DL_CSD_DATA_CHAN,
                                             (VOS_UINT8 *)(&stDLData),
                                             DICC_CPU_ID_ACPU);

        if (DICC_OK != ulRslt)
        {
            CSD_ERROR_LOG1(ACPU_PID_CSD,
                          "CSD_DL_ClearData:: DICC_RemoveChannelData Fail",
                          ulRslt);
            break;
        }

        ulDICCNodeCnt-- ;

        /*֪ͨcCpu�ͷ�TTFmem*/
        IMM_RemoteFreeTtfMem(stDLData.pGarbage);
    }

    CSD_NORMAL_LOG(ACPU_PID_CSD,"CSD_DL_ClearData Done");
}

VOS_VOID CSD_DL_ProcDataTask(VOS_VOID)
{
    VOS_UINT32                         *pulDownLinkSem;

    pulDownLinkSem = CSD_GetDownLinkDataSem();

    for ( ; ; )
    {

        /* ��ȡ����ȡ�����ź��� */
        if (VOS_OK != VOS_SmP( *pulDownLinkSem, 0 ))
        {
            CSD_NORMAL_LOG(ACPU_PID_CSD,
                "CSD_DL_ProcDataTask:: VOS_SmP pulDownLinkSem then continue !");


#ifdef __PC_UT__
            break;
#else
            continue;
#endif
        }

        /*��ȡ��ǰ�Ƿ�Ҷϵ绰*/
        if (AT_CSD_CALL_STATE_ON != CSD_GetCallState())
        {
            /*�ͷ�����*/
            CSD_DL_ClearData();
#if 0
            /*ʹ���ж�*/
            DICC_EnableIsr(ACPU_PID_CSD,
                           DICC_SERVICE_TYPE_CSD_DATA,
                           DICC_CPU_ID_ACPU);
#endif

            CSD_ERROR_LOG(ACPU_PID_CSD,
                          "CSD_DL_ProcDataTask:: AT_CSD_CALL_STATE_OFF Receive ISR");


#ifdef __PC_UT__
            break;
#else
            continue;
#endif

        }

        CSD_DL_SendData();
#if 0
        /* ʹ���ж� */
        DICC_EnableIsr(ACPU_PID_CSD,
                       DICC_SERVICE_TYPE_CSD_DATA,
                       DICC_CPU_ID_ACPU);
#endif
#ifdef __PC_UT__
            break;
#endif
    }
}

#endif /*FEATURE_CSD*/






#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
