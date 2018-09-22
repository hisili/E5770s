

#include "AtCheckFunc.h"

#include "msp_errno.h"

#include "at_common.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/* AT�����ʼ״̬�� */
AT_SUB_STATE_STRU AT_D_CMD_NONE_STATE_TAB[]=
{
    /* �����ǰ״̬��ATCMD_NONE_STATE��atCheckCharD�ɹ��������AT_D_CMD_NAME_STATE */
    {    At_CheckCharD    ,    AT_D_CMD_NAME_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D����������״̬�� */
AT_SUB_STATE_STRU AT_D_CMD_NAME_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_D_CMD_NAME_STATE��At_CheckCharRightArrow�ɹ��������AT_D_CMD_RIGHT_ARROW_STATE */
    {    At_CheckCharRightArrow    ,    AT_D_CMD_RIGHT_ARROW_STATE    },

    /* �����ǰ״̬��AT_D_CMD_NAME_STATE��atCheckDailString�ɹ��������AT_D_CMD_DIALSTRING_STATE */
    {    At_CheckDialNum    ,    AT_D_CMD_DIALSTRING_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D������ַ���״̬�� */
AT_SUB_STATE_STRU AT_D_CMD_DIALSTRING_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_D_CMD_DIALSTRING_STATE��atCheckDailString�ɹ��������AT_D_CMD_DIALSTRING_STATE */
    {    At_CheckDialNum    ,    AT_D_CMD_DIALSTRING_STATE    },

    /* �����ǰ״̬��AT_D_CMD_DIALSTRING_STATE��At_CheckCharI�ɹ��������AT_D_CMD_CHAR_I_STATE */
    {    At_CheckCharI    ,    AT_D_CMD_CHAR_I_STATE    },

    /* �����ǰ״̬��AT_D_CMD_DIALSTRING_STATE��At_CheckCharG�ɹ��������AT_D_CMD_CHAR_G_STATE */
    {    At_CheckCharG    ,    AT_D_CMD_CHAR_G_STATE    },

    /* �����ǰ״̬��AT_D_CMD_DIALSTRING_STATE��At_CheckSemicolon�ɹ��������AT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D�����ַ�I״̬�� */
AT_SUB_STATE_STRU AT_D_CMD_CHAR_I_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_D_CMD_CHAR_I_STATE��At_CheckCharG�ɹ��������AT_D_CMD_CHAR_G_STATE */
    {    At_CheckCharG    ,    AT_D_CMD_CHAR_G_STATE    },

    /* �����ǰ״̬��AT_D_CMD_CHAR_I_STATE��At_CheckSemicolon�ɹ��������AT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D�����ַ�G״̬�� */
AT_SUB_STATE_STRU AT_D_CMD_CHAR_G_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_D_CMD_CHAR_G_STATE��At_CheckSemicolon�ɹ��������AT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D�����Ҽ�ͷ״̬�� */
AT_SUB_STATE_STRU AT_D_CMD_RIGHT_ARROW_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_D_CMD_RIGHT_ARROW_STATE��atCheck_quot�ɹ��������AT_D_CMD_LEFT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_D_CMD_LEFT_QUOT_STATE    },

    /* �����ǰ״̬��AT_D_CMD_RIGHT_ARROW_STATE��atCheck_num�ɹ��������AT_D_CMD_DIGIT_STATE */
    {    At_CheckDigit    ,    AT_D_CMD_DIGIT_STATE    },

    /* �����ǰ״̬��AT_D_CMD_RIGHT_ARROW_STATE��At_CheckUpLetter�ɹ��������AT_D_CMD_CHAR_STATE */
    {    At_CheckUpLetter    ,    AT_D_CMD_CHAR_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D������ĸ״̬�� */
AT_SUB_STATE_STRU AT_D_CMD_CHAR_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_D_CMD_CHAR_STATE��atCheckCharStr�ɹ��������AT_D_CMD_CHAR_STATE */
    {    At_CheckUpLetter    ,    AT_D_CMD_CHAR_STATE    },

    /* �����ǰ״̬��AT_D_CMD_CHAR_STATE��atCheck_quot�ɹ��������AT_D_CMD_RIGHT_QUOT_STATE */
    {    At_CheckDigit    ,    AT_D_CMD_DIGIT_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D����������״̬�� */
AT_SUB_STATE_STRU AT_D_CMD_LEFT_QUOT_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_D_CMD_LEFT_QUOT_STATE��atCheckCharStr�ɹ��������AT_D_CMD_LEFT_QUOT_STATE */
    {    At_CheckNoQuot    ,    AT_D_CMD_LEFT_QUOT_STATE    },

    /* �����ǰ״̬��AT_D_CMD_LEFT_QUOT_STATE��atCheck_quot�ɹ��������AT_D_CMD_RIGHT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_D_CMD_RIGHT_QUOT_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT D����������״̬�� */
AT_SUB_STATE_STRU AT_D_CMD_RIGHT_QUOT_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_D_CMD_RIGHT_ARROW_STATE��atCheck_num�ɹ��������AT_D_CMD_DIGIT_STATE */
    {    At_CheckDigit    ,    AT_D_CMD_DIGIT_STATE    },

    /* �����ǰ״̬��AT_D_CMD_DIALSTRING_STATE��At_CheckCharI�ɹ��������AT_D_CMD_CHAR_I_STATE */
    {    At_CheckCharI    ,    AT_D_CMD_CHAR_I_STATE    },

    /* �����ǰ״̬��AT_D_CMD_DIALSTRING_STATE��At_CheckCharG�ɹ��������AT_D_CMD_CHAR_G_STATE */
    {    At_CheckCharG    ,    AT_D_CMD_CHAR_G_STATE    },

    /* �����ǰ״̬��AT_D_CMD_DIALSTRING_STATE��At_CheckSemicolon�ɹ��������AT_D_CMD_SEMICOLON_STATE */
    {    At_CheckSemicolon    ,    AT_D_CMD_SEMICOLON_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};



/* AT������״̬�� */
AT_MAIN_STATE_STRU AT_D_CMD_MAIN_STATE_TAB[] =
{
    /* �����ǰ״̬��AT_NONE_STATE�������AT_D_CMD_NONE_STATE_TAB��״̬�� */
    {    AT_NONE_STATE    ,    AT_D_CMD_NONE_STATE_TAB    },

    /* �����ǰ״̬��AT_D_CMD_NAME_STATE�������AT_D_CMD_NAME_STATE_TAB��״̬�� */
    {    AT_D_CMD_NAME_STATE    ,    AT_D_CMD_NAME_STATE_TAB    },

    /* �����ǰ״̬��AT_D_CMD_DIALSTRING_STATE�������AT_D_CMD_DIALSTRING_STATE_TAB��״̬�� */
    {    AT_D_CMD_DIALSTRING_STATE    ,    AT_D_CMD_DIALSTRING_STATE_TAB    },

    /* �����ǰ״̬��AT_D_CMD_CHAR_I_STATE�������AT_D_CMD_CHAR_I_STATE_TAB��״̬�� */
    {    AT_D_CMD_CHAR_I_STATE    ,    AT_D_CMD_CHAR_I_STATE_TAB    },

    /* �����ǰ״̬��AT_D_CMD_CHAR_G_STATE�������AT_D_CMD_CHAR_G_STATE_TAB��״̬�� */
    {    AT_D_CMD_CHAR_G_STATE    ,    AT_D_CMD_CHAR_G_STATE_TAB    },

    /* �����ǰ״̬��AT_D_CMD_CHAR_STATE�������AT_D_CMD_CHAR_STATE_TAB��״̬�� */
    {    AT_D_CMD_CHAR_STATE    ,    AT_D_CMD_CHAR_STATE_TAB    },

    /* �����ǰ״̬��AT_D_CMD_RIGHT_ARROW_STATE�������AT_D_CMD_RIGHT_ARROW_STATE_TAB��״̬�� */
    {    AT_D_CMD_RIGHT_ARROW_STATE    ,    AT_D_CMD_RIGHT_ARROW_STATE_TAB    },

    /* �����ǰ״̬��AT_D_CMD_LEFT_QUOT_STATE�������AT_D_CMD_LEFT_QUOT_STATE_TAB��״̬�� */
    {    AT_D_CMD_LEFT_QUOT_STATE    ,    AT_D_CMD_LEFT_QUOT_STATE_TAB    },

    /* �����ǰ״̬��AT_D_CMD_RIGHT_QUOT_STATE�������AT_D_CMD_RIGHT_QUOT_STATE_TAB��״̬�� */
    {    AT_D_CMD_RIGHT_QUOT_STATE    ,    AT_D_CMD_RIGHT_QUOT_STATE_TAB    },

    /* �����ǰ״̬��AT_D_CMD_DIGIT_STATE�������AT_D_CMD_DIGIT_STATE_TAB��״̬�� */
    {    AT_D_CMD_DIGIT_STATE    ,    AT_D_CMD_RIGHT_QUOT_STATE_TAB    },

    /* ��״̬����� */
    {    AT_BUTT_STATE    ,    NULL    },
};



static VOS_UINT32 atParseDCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  ���ó�ʼ״̬ */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  ���ó�ʼ״̬ */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  ָ��ǰ���ڴ�����ַ�*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  �������ݵ���ʼָ�� */
    VOS_UINT16 usLength = 0;                        /*  ��¼��ǰ�Ѿ�������ַ�����*/

    /* ���η����ַ����е�ÿ���ַ�*/
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))                     /* ���αȽ�ÿ���ַ� */
    {
        curr_state = new_state;                  /* ��ǰ״̬����Ϊ��״̬*/

        /* ���ݵ�ǰ������ַ��͵�ǰ״̬���õ���״̬*/
        new_state = atFindNextMainState(AT_D_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch(new_state)                        /* ״̬����*/
        {
        case AT_D_CMD_NAME_STATE:                /* AT D����������״̬ */
            g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;     /* ������������*/
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* ���������������*/
            pucCopyPtr = pucCurrPtr;                 /* ׼������D����������*/
            break;

        case AT_D_CMD_RIGHT_ARROW_STATE:         /* AT D�����Ҽ�ͷ״̬ */
        case AT_D_CMD_DIALSTRING_STATE:          /* AT D������ַ���״̬ */
            if(curr_state != new_state)          /* ��״̬���ֲ����ڵ�ǰ״̬*/
            {
                g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
                if(g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
                {
                    atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /* ���ش��� */
                }
                pucCopyPtr = pucCurrPtr;             /* ׼�����ղ���*/
            }
            break;

        case AT_D_CMD_DIGIT_STATE:               /* AT D��������״̬ */
        case AT_D_CMD_LEFT_QUOT_STATE:           /* AT D����������״̬ */
        case AT_D_CMD_CHAR_STATE:
            if(curr_state != new_state)          /* ��״̬���ֲ����ڵ�ǰ״̬*/
            {
                /* �洢������ȫ�ֱ����� */
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
                {
                    return AT_FAILURE;
                }

                pucCopyPtr = pucCurrPtr;                /* ׼��������һ������*/
            }
            break;

        case AT_D_CMD_CHAR_I_STATE:              /* AT D�����ַ�I״̬ */
        case AT_D_CMD_CHAR_G_STATE:              /* AT D�����ַ�G״̬ */
        case AT_D_CMD_SEMICOLON_STATE:           /* AT D����ֺ�״̬ */
            /* �洢������ȫ�ֱ����� */
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
            {
                return AT_FAILURE;
            }

            pucCopyPtr = pucCurrPtr;                /* ׼��������һ������*/
            break;

        case AT_BUTT_STATE:                     /* ��Ч״̬ */
            return AT_FAILURE;                  /* ���ش��� */

        default:
            break;
        }
        pucCurrPtr++;                             /* ����������һ���ַ�*/
    }

    switch(new_state)                           /* ��������״̬�ж�*/
    {
    case AT_D_CMD_SEMICOLON_STATE:              /* AT D����ֺ�״̬ */
        break;

    case AT_D_CMD_DIALSTRING_STATE:             /* AT D������ַ���״̬ */
    case AT_D_CMD_DIGIT_STATE:                  /* AT D��������״̬ */
    case AT_D_CMD_RIGHT_QUOT_STATE:             /* AT D����������״̬ */
    case AT_D_CMD_CHAR_G_STATE:                 /* AT D�����ַ�G״̬ */
    case AT_D_CMD_CHAR_I_STATE:                 /* AT D�����ַ�I״̬ */
        /* �洢������ȫ�ֱ����� */
        if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
        {
            return AT_FAILURE;
        }

        break;

    default:
        return AT_FAILURE;                      /* ���ش���*/
    }
    return AT_SUCCESS;                          /* ������ȷ*/
}



static VOS_VOID atScanDcmdModifier( VOS_UINT8 *pData, VOS_UINT16 *pLen)
{
    VOS_UINT16 usChkLen  = 0;
    VOS_UINT16 usLen     = 0;
    VOS_UINT8  *pWrite   = pData;
    VOS_UINT8  *pRead    = pData;

    /* ���������� */
    while ( usChkLen++ < *pLen )
    {
        /*ɾ�����η���',','T','P','!','W','@'*/
        if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
            && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }

    *pLen  =  usLen;
    return;
}


static VOS_VOID atScanDmcmdModifier( VOS_UINT8 *pData, VOS_UINT16 *pLen)
{
    VOS_UINT16 usLen     = 0;
    VOS_UINT8  *pWrite   = VOS_NULL_PTR;
    VOS_UINT8  *pRead    = VOS_NULL_PTR;
    VOS_UINT8  *pTmp     = VOS_NULL_PTR;
    VOS_UINT8  *pDataTmp = VOS_NULL_PTR;
    VOS_UINT8  aucStr[]  = "*99**PPP";
    VOS_UINT16 usStrLen  = 0;

    pDataTmp = (VOS_UINT8*)AT_MALLOC(*pLen + 1);
    if (VOS_NULL_PTR == pDataTmp)
    {
        vos_printf("atScanDmcmdModifier(): AT_MALLOC Failed!\n");
        return;
    }

    atRangeCopy(pDataTmp, pData, (pData + *pLen));

    /* ��֤�ַ����н����� */
    pDataTmp[*pLen] = 0;

    pRead   = pDataTmp;
    pWrite  = pDataTmp;

    pTmp = (VOS_UINT8*)AT_STRSTR((VOS_CHAR *)pDataTmp,(VOS_CHAR *)aucStr);
    if(NULL != pTmp)
    {
        usStrLen = (VOS_UINT16)AT_STRLEN((VOS_CHAR *)aucStr);
        /* ���ǰһ����� */
        while ( pRead < pTmp )
        {
            /*ɾ�����η���',','T','P','!','W','@'*/
            if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
                && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
            {
                *pWrite++ = *pRead;
                usLen++;
            }
            pRead++;
        }
        while( pRead < (pTmp+usStrLen) )
        {
            *pWrite++ = *pRead++;
            usLen++;
        }
        while( pRead < (pDataTmp+(*pLen)) )
        {
            /*ɾ�����η���',','T','P','!','W','@'*/
            if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
                && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
            {
                *pWrite++ = *pRead;
                usLen++;
            }
            pRead++;
        }
    }
    else
    {
        /* ���������� */
        while ( pRead < (pDataTmp+(*pLen)) )
        {
            /*ɾ�����η���',','T','P','!','W','@'*/
            if((',' != *pRead) && ('T' != *pRead) && ('P' != *pRead)
                && ('!' != *pRead) && ('W' != *pRead) && ('@' != *pRead))
            {
                *pWrite++ = *pRead;
                usLen++;
            }
            pRead++;
        }
    }

    atRangeCopy(pData, pDataTmp, (pDataTmp + *pLen));

    *pLen = usLen;

    AT_FREE(pDataTmp);
    return;
}


static VOS_UINT32 ScanQuateChar( VOS_UINT8 * pData, VOS_UINT16 * pusLen)
{
    VOS_UINT8 *pWrite = pData;
    VOS_UINT8 *pRead  = pData;
    VOS_UINT16 usChkLen = 0;
    VOS_UINT16 usLen    = 0;

    if(0 == *pusLen)
    {
        return AT_FAILURE;
    }

    while(usChkLen++ < *pusLen)
    {
        /* ȥ������ */
        if('"' != *pRead)
        {
            *pWrite++ = *pRead;
            usLen++;
        }
        pRead++;
    }
    *pusLen = usLen;

    return AT_SUCCESS;
}



VOS_UINT32 ParseDCmdPreProc( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    VOS_UINT16 usTmpLen = usLen;
    VOS_UINT8* pTmp = pData;
    VOS_UINT32 ulResult = AT_FAILURE;

    /* Ϊ�˹��LINUX�²��������д�������(ATDT"*99#")�����⣬������ȥ�� */
    ScanQuateChar(pTmp, &usTmpLen);

#if 0
    if(AT_SUCCESS == atCheckMmiString(pTmp,usTmpLen))              /* ����ҵ���� */
    {
        if(AT_FAILURE == At_CheckCharWell(pTmp[usTmpLen - 1]))      /* ���������#�Ž�β */
        {
            atScanDcmdModifier(pTmp,&usTmpLen);                    /* ɨ�����η� */

            /* ��ΪҪ��������������gstATCmdName.usCmdNameLen���Ա�����ƥ�䣬
            ���ԣ������ݿ����������б�ĵ�һ��������*/
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pTmp, usTmpLen))
            {
                return AT_CME_DIAL_STRING_TOO_LONG;
            }

            g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;                   /* ������������ */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;          /* ��������������� */
            g_stATParseCmd.stCmdName.usCmdNameLen = 1;
            g_stATParseCmd.stCmdName.aucCmdName[0] = 'D';
            ulResult = AT_SUCCESS;
        }
        else
        {
            atScanDmcmdModifier(pTmp,&usTmpLen);                    /* ɨ�����η� */

            /* ��ΪҪ��������������gstATCmdName.usCmdNameLen���Ա�����ƥ�䣬
            ���ԣ������ݿ����������б�ĵ�һ��������*/
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pTmp, usTmpLen))
            {
                return AT_CME_DIAL_STRING_TOO_LONG;
            }

            ulResult = atParseDMCmd(pTmp,usTmpLen);                /* ������ֺ� */
            if(ulResult == AT_FAILURE)
            {
                return AT_ERROR;
            }
        }
    }
    else
#endif    
    {
        if(AT_SUCCESS == At_CheckCharWell(pTmp[usTmpLen - 1]))      /* ���������#�Ž�β */
        {
            atScanDmcmdModifier(pTmp,&usTmpLen);                    /* ɨ�����η� */

            /* ��ΪҪ��������������gstATCmdName.usCmdNameLen���Ա�����ƥ�䣬
            ���ԣ������ݿ����������б�ĵ�һ��������*/
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pTmp, usTmpLen))
            {
                return AT_CME_DIAL_STRING_TOO_LONG;
            }

            ulResult = atParseDMCmd(pTmp,usTmpLen);                /* ������ֺ� */
            if(ulResult == AT_FAILURE)
            {
                return AT_ERROR;
            }
        }
        else
        {
            if(AT_FAILURE == atCheckRightArrowStr(pTmp,usTmpLen))
            {
                atScanDcmdModifier(pTmp,&usTmpLen);                        /* ɨ�����η� */
            }

            /* ��ΪҪ��������������gstATCmdName.usCmdNameLen���Ա�����ƥ�䣬
            ���ԣ������ݿ����������б�ĵ�һ��������*/
            if(ERR_MSP_SUCCESS != atfwParseSaveParam(pTmp, usTmpLen))
            {
                return AT_CME_DIAL_STRING_TOO_LONG;
            }

            ulResult = atParseDCmd(pTmp,usTmpLen);                       /* D���� */

            if(ulResult == AT_FAILURE)
            {
                return AT_ERROR;
            }

        }
    }

    return ulResult;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


