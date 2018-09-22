/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileNmae: v_nsprintf.c                                                    */
/*                                                                           */
/* Author:Tong ChaoZhu                                                       */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date:  2001-12-26                                                         */
/*                                                                           */
/* Description: copy this file from Dopra                                    */
/*                                                                           */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification:                                                          */
/*                                                                           */
/*****************************************************************************/

/*lint --e{958,445,830,616,48,530,813,438,64}*/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "v_IO.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_V_NSPRINTF_C
/*lint +e767 modify:x51137; review:h59254; */


/*****************************************************************************
 Function   : ANSI_nvsprintf
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT32 ANSI_nvsprintf(VOS_CHAR *out_buf, VOS_UINT32 ulStrLen, const VOS_CHAR *fmt0, va_list argp)
{
    VOS_UINT32 		ulLong;          	
    VOS_INT			lBase;        			
    VOS_INT 		lDprec;        			
    VOS_INT 		lFieldSize;        		
    VOS_INT 		lFlags;        			
    VOS_INT 		lFpprec;        		
    VOS_INT 		lPrec;        			
    VOS_INT 		lRealSize;        		
    VOS_INT 		lConverSize;        	
    VOS_INT 		lFormatWidth;       	
	VOS_INT			lChar;            		
    VOS_INT			ltemp; 
	
	VOS_UCHAR		*pucFmt;            	
    VOS_CHAR		*pcBuf;        			
	VOS_CHAR 		ucPrefixSign;      		
    VOS_CHAR 		*pucDigs;        		
    VOS_CHAR 		ucBuf[BUF];        		
    VOS_CHAR 		*pucOutBuf=out_buf;
#ifdef FLOAT_SUPPORT
    VOS_CHAR 		ucSoftSign;       		
#endif
    VOS_UINT32 		ulWriteLen = ulStrLen;

    pucFmt 	= (VOS_UCHAR*)fmt0;
    pucDigs = "0123456789abcdef";


    for (;; ++pucFmt)
    {
            for (; ((lChar = *pucFmt)!=0) && lChar != '%'; ++pucFmt)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++ = (VOS_CHAR)lChar;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }
            if (!lChar)
            {
				goto    lvspret;
            }

            lFlags 			= 0; 
			lDprec 			= 0; 
			lFpprec 		= 0; 
			lFormatWidth 	= 0;
            lPrec 			= -1;
            ucPrefixSign = '\0';

rflag: switch (*++pucFmt) {
        case ' ':
            /* ���ո�ͼӺ�ͬʱ���֣�����Կո� -- ANSI X3J11  */
            if (!ucPrefixSign)
            {
                ucPrefixSign = ' ';
            }
            goto rflag;
        case '#':
            lFlags |= ALT;
            goto rflag;
        /* coverity[unterminated_case] */
        case '*':
            if ((lFormatWidth = va_arg(argp, VOS_INT)) >= 0)
            {
                goto rflag;
            }
            lFormatWidth = -lFormatWidth;
        case '-':
            lFlags |= LADJUST; /* ����� */
            goto rflag;
        case '+':
            ucPrefixSign = '+';
            goto rflag;
        case '.':
            if (*++pucFmt == '*')
            {
                ltemp = va_arg(argp, VOS_INT);
            }
            else 
			{
                ltemp = 0;
                while (isascii(*pucFmt) && isdigit(*pucFmt))
                {
                    ltemp = 10 * ltemp + todigit(*pucFmt++);
                }
                --pucFmt;
            }
            lPrec = ltemp < 0 ? -1 : ltemp;
            goto rflag;
        case '0':
            lFlags |= ZEROPAD;
            goto rflag;
        case '1': 
		case '2': 
		case '3': 
		case '4':
        case '5': 
		case '6': 
		case '7': 
		case '8': 
		case '9':
            ltemp = 0;
            do 
			{
                ltemp = 10 * ltemp + todigit(*pucFmt);
            } while (isascii(*++pucFmt) && isdigit(*pucFmt));
            lFormatWidth = ltemp;
            --pucFmt;
            goto rflag;
        case 'L':
            lFlags |= LONGDBL;
            goto rflag;
        case 'h':
            lFlags |= SHORTINT;
            goto rflag;
        case 'l':
            lFlags |= LONGINT;
            goto rflag;
        case 'c':
            *(pcBuf = ucBuf) = (VOS_CHAR)va_arg(argp, VOS_INT);
            lConverSize = 1;
            ucPrefixSign = '\0';
            goto pforw;
        case 'D':
            lFlags |= LONGINT;
            /*lint -save -e732 -e501 -e737 -e713*/
        case 'd':
        case 'i':
            ARG(int);
            if ((VOS_INT32)ulLong < 0) 
			{
                ulLong = -ulLong;
                ucPrefixSign = '-';
            }
            lBase = 10;
            goto number;
#ifdef FLOAT_SUPPORT
        case 'e':
        case 'E':
        case 'f':
        case 'g':
        case 'G':

        {
            VOS_DOUBLE udDouble;        /* ˫���ȸ����� */ 
            udDouble = va_arg(argp, VOS_DOUBLE);

            if (lPrec > MAXFRACT) 
			{
                if ((*pucFmt != 'g' && *pucFmt != 'G') || (lFlags&ALT))
                {
                    lFpprec = lPrec - MAXFRACT;
                }
                lPrec = MAXFRACT;
            }
            else if (lPrec == -1)
            {
                if (lFlags&LONGINT)
                {
                    lPrec = DEFLPREC;
                }
                else
                {
                    lPrec = DEFPREC;
                }
            }

            if (udDouble < 0) 
			{
                ucSoftSign = '-';
                udDouble = -udDouble;
            }
            else
            {
                ucSoftSign = 0;
            }

            *ucBuf = 0;
            lConverSize = cvt(udDouble, lPrec, lFlags,*pucFmt, &ucSoftSign, ucBuf,
            ucBuf + sizeof(ucBuf));

            if (ucSoftSign)
            {
                ucPrefixSign = '-';
            }
            pcBuf = *ucBuf ? ucBuf : ucBuf + 1;
            goto pforw;
        }
#endif
        case 'n':
            if (lFlags & LONGINT)
            {
				*va_arg(argp, VOS_INT32*) = (VOS_INT32)(pucOutBuf-out_buf);
            }
            else if (lFlags & SHORTINT)
            {
				*va_arg(argp, VOS_INT16*) = (VOS_INT16)(pucOutBuf-out_buf);
            }
            else
            {
				*va_arg(argp, VOS_INT*) = (VOS_INT)(pucOutBuf-out_buf);
            }
            break;
        case 'O':
            lFlags |= LONGINT;
        case 'o':
            ARG(unsigned);
            lBase = 8;
            goto nosign;
        case 'p':
            ulLong = (VOS_UINT32)va_arg(argp, VOS_VOID *);
            lBase = 16;
            goto nosign;
        case 's':
            if ( (pcBuf = va_arg(argp, VOS_CHAR*))==0 )
            {
                pcBuf = "(null)";
            }
            if (lPrec >= 0) 
			{
				VOS_CHAR *p;

                if ((p = (VOS_CHAR *)VOS_MemChr((const VOS_CHAR *)pcBuf, 0, lPrec))!=0) 
				{
                    lConverSize = p - pcBuf;
                    if (lConverSize > lPrec)
                    {
                        lConverSize = lPrec;
                    }
                 }
                 else
                 {
                    lConverSize = lPrec;
                 }
            } 
			else
			{
                lConverSize = VOS_StrLen(pcBuf);
			}
            ucPrefixSign = '\0';
            goto pforw;
        case 'U':
            lFlags |= LONGINT;
        case 'u':
            ARG(unsigned);
            lBase = 10;
            goto nosign;
        case 'X':
            pucDigs = "0123456789ABCDEF";
        case 'x':
            ARG(unsigned);
            lBase = 16;
            if (lFlags & ALT && ulLong != 0)
            {
                lFlags |= HEXPREFIX;
            }

            /* �޷�����ת�� */
nosign:    ucPrefixSign = '\0';

number:    	if ((lDprec = lPrec) >= 0)
			{
				lFlags &= ~ZEROPAD;
			}

            pcBuf = ucBuf + BUF;
            /*lint -save -e727 -e728 -e729 -e732 -e713 -e573 -e529*/
            if (ulLong != 0 || lPrec != 0) 
			{
                do {
                    *--pcBuf = pucDigs[ulLong % lBase];
                    ulLong /= lBase;
                } while (ulLong);
                pucDigs = "0123456789abcdef";
                if (lFlags & ALT && lBase == 8 && *pcBuf != '0')
                {
                    *--pcBuf = '0'; /* 8���Ʊ�־ */
                }
            }
            lConverSize = ucBuf + BUF - pcBuf;

pforw:
			lFieldSize = lConverSize + lFpprec;
            if (ucPrefixSign)
            {
                lFieldSize++;
            }
            if (lFlags & HEXPREFIX)
            {
                lFieldSize += 2;
            }
            lRealSize = lDprec > lFieldSize ? lDprec : lFieldSize;

            if ((lFlags & (LADJUST|ZEROPAD)) == 0 && lFormatWidth)
            {
                for (ltemp = lRealSize; ltemp < lFormatWidth; ltemp++)
                {
                    if(ulWriteLen--)
                    {
                        *pucOutBuf++=' ';
                    }
                    else
                    {
                        return (VOS_INT32)ulStrLen;
                    }
                }
            }

            if (ucPrefixSign)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++=ucPrefixSign;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            if (lFlags & HEXPREFIX)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++='0';
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
                if(ulWriteLen--)
                {
                    *pucOutBuf++=(VOS_CHAR)*pucFmt;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            if ((lFlags & (LADJUST|ZEROPAD)) == ZEROPAD)
            {
                for (ltemp = lRealSize; ltemp < lFormatWidth; ltemp++)
                {
                    if(ulWriteLen--)
                    {
                        *pucOutBuf++='0';
                    }
                    else
                    {
                        return (VOS_INT32)ulStrLen;
                    }
                }
            }

            for (ltemp = lFieldSize; ltemp < lDprec; ltemp++)
            {
               if(ulWriteLen--)
               {
                  *pucOutBuf++='0';
               }
               else
               {
                   return (VOS_INT32)ulStrLen;
               }
            }

            ltemp = lConverSize;
            while (--ltemp >= 0)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++=*pcBuf++;
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            while (--lFpprec >= 0)
            {
                if(ulWriteLen--)
                {
                    *pucOutBuf++='0';
                }
                else
                {
                    return (VOS_INT32)ulStrLen;
                }
            }

            if (lFlags & LADJUST)
            {
                for (ltemp = lRealSize; ltemp < lFormatWidth; ltemp++)
                {
                    if(ulWriteLen--)
                    {
                        *pucOutBuf++=' ';
                    }
                    else
                    {
                        return (VOS_INT32)ulStrLen;
                    }
                }
            }

            break;
        case '\0':    
                        goto    lvspret;
        default:
                        if(ulWriteLen--)
                        {
                            *pucOutBuf++=(VOS_CHAR)*pucFmt;
                        }
                        else
                        {
                            return (VOS_INT32)ulStrLen;
                        }

            }
        }
lvspret:
        if(ulWriteLen--)
        {
            *pucOutBuf=0;
        }
        else
        {
            return (VOS_INT32)ulStrLen;
        }
        return (VOS_INT)(pucOutBuf-out_buf);
}/*lint -restore*/

/*****************************************************************************
 Function   : VOS_nvsprintf
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT32 VOS_nvsprintf(VOS_CHAR * str, VOS_UINT32 ulMaxStrLen, const VOS_CHAR *format, va_list arguments)
{
    VOS_INT32 nc;

    if (( NULL == str ) || ( NULL == format ) || (ulMaxStrLen == 0))
    {
        return -1;
    }
    else
    {
        VOS_MemSet(str, 0, ulMaxStrLen);
    }

    nc = ANSI_nvsprintf(str, ulMaxStrLen - 1, (const VOS_CHAR *) format, arguments);

    return nc;
}


/*****************************************************************************
 Function   : VOS_nsprintf
 Description:
 Input      :
            :
 Return     :
 Other      :
 *****************************************************************************/
VOS_INT32 VOS_nsprintf(VOS_CHAR *str, VOS_UINT32 ulMaxStrLen, const VOS_CHAR *fmt, ...)
{
    va_list arg;
    register VOS_INT32 nc;


    if (( NULL == str ) || ( NULL == fmt ) || (ulMaxStrLen == 0))
    {
        return -1;
    }
    else
    {
        VOS_MemSet(str, 0, ulMaxStrLen);
    }

    va_start(arg, fmt);
    nc = ANSI_nvsprintf(str, ulMaxStrLen - 1, (const VOS_CHAR *) fmt, arg);
    va_end(arg);
    return (nc);
}

VOS_PRINT_HOOK g_pfnPrintHook = VOS_NULL_PTR;

/*****************************************************************************
 Function   : VOS_HookPrint
 Description: Register the redirect funciton for vos_printf
 Input      : newHook -- New print hook
 Output     : None
 Return     : Old print hook
 Other      : 1) The print hook might be re-enterred.
              2) The print hook should be call in Interrupt level and task
                 context.
 *****************************************************************************/
VOS_PRINT_HOOK VOS_HookPrint( VOS_PRINT_HOOK newHook )
{
    VOS_PRINT_HOOK oldHook = g_pfnPrintHook;

    g_pfnPrintHook = newHook;

    return oldHook;
}

#if (VOS_WIN32 == VOS_OS_VER)
/* which comes from MFC of WIN32 */
extern void zprint(char *str);
#endif


#if (VOS_VXWORKS == VOS_OS_VER)
#define VOS_VXWORKS_INT_LOCK_FLAG       (0xc0)
extern int intLock (VOS_VOID);
extern VOS_VOID intUnlock( int lockKey );
#endif

/*****************************************************************************
 Function   : vos_printf
 Description: Print function
 Input      : format -- Format string to print
 Output     : None
 Return     : VOS_OK on success and VOS_ERROR on error
 *****************************************************************************/
VOS_INT32 vos_printf( VOS_CHAR * format, ... )
{
    VOS_INT32  rc;
    VOS_UINT32 ulReturn = VOS_OK;
    va_list    argument;
    VOS_CHAR   output_info[VOS_MAX_PRINT_LEN + 4];
#if (VOS_VXWORKS == VOS_OS_VER)
    int flag;
#endif

    va_start( argument, format );
    rc = VOS_nvsprintf( output_info, VOS_MAX_PRINT_LEN, format, argument );
    va_end( argument );

    output_info[VOS_MAX_PRINT_LEN - 1] = '\0';

    if( rc >= VOS_MAX_PRINT_LEN - 1 )
    {
        VOS_UINT32  ulTempLen;
        VOS_CHAR *  pcWarning = " [!!!Warning: Print too long!!!]\r\n";
        ulTempLen = VOS_StrLen( pcWarning );
        VOS_StrNCpy( output_info + ( VOS_MAX_PRINT_LEN - ulTempLen - 1 ), pcWarning, ulTempLen );
        rc = VOS_MAX_PRINT_LEN - 1; /* [false alarm]: ����Fortify���� */

        VOS_SetErrorNo( VOS_ERRNO_LIB_PRINTF_INPUTFORMATTOOLONG );
        ulReturn = VOS_ERRNO_LIB_PRINTF_INPUTFORMATTOOLONG;
    }
    else if( rc < 0 )
    {
        VOS_CHAR *  pcWarning = "\r\n### vos printf error: unknown internal error. ###\r\n";
        VOS_StrCpy( output_info, pcWarning );
        rc = VOS_StrLen( pcWarning ); /* [false alarm]: ����Fortify���� */

        VOS_SetErrorNo( VOS_ERRNO_LIB_PRINTF_UNKNOWNINTERERROR );
        ulReturn = VOS_ERRNO_LIB_PRINTF_UNKNOWNINTERERROR;
    }

    if( g_pfnPrintHook != VOS_NULL_PTR )
    {
        ulReturn = (VOS_UINT32)(*g_pfnPrintHook)( output_info );
        if( ulReturn != (VOS_UINT32)VOS_ERROR )
        {
            return (VOS_INT32)VOS_OK;
        }
    }

#if (VOS_NUCLEUS == VOS_OS_VER)
    printf( "%s",output_info );
#endif

#if (VOS_VXWORKS == VOS_OS_VER)
    flag = intLock();
     /* �����ǰ�������жϻ������ж������ģ����ⱻ������������ӡ��Ϣ */
    if(!(VOS_VXWORKS_INT_LOCK_FLAG & flag))
    {
        logMsg((char*)output_info, 0,0,0,0,0,0);
    }
    
    intUnlock(flag);
#endif

#if (VOS_WIN32 == VOS_OS_VER)
    zprint(output_info );
#endif

#if (VOS_LINUX == VOS_OS_VER)
    printk( "%s",output_info );
#endif

#if (VOS_RTOSCK == VOS_OS_VER)
    SRE_Printf( "%s",output_info );
#endif

    return (VOS_INT32)ulReturn;
}

#if (FEATURE_ON == MBB_WPG_COMMON) 
#define LEN_PRINT_STR   (250) /*Print u8 type string length...*/
/*****************************************************************************
 Function   : vos_printf_dump
 Description: Print function
 Input      : format -- Format U8 string to print
 Output     : None
 Return     : VOS_OK on success and VOS_ERROR on error
 *****************************************************************************/
VOS_INT32 vos_printf_dump(VOS_UINT16 ulLen,VOS_UINT8 *pStr) 
{
    VOS_UINT16  loop = 0;
    if (VOS_NULL == ulLen || VOS_NULL_PTR == pStr)
    {
        (VOS_VOID)vos_printf("vos_printf_dump()");
        return ulLen;
    }
    (VOS_VOID)vos_printf("%s-%d\n",__FUNCTION__,__LINE__);
    ulLen = (ulLen > LEN_PRINT_STR) ? LEN_PRINT_STR : (ulLen);
    for (loop = 0; pStr && loop < ulLen; loop++,pStr++)
    {
        (ulLen - 1 == loop)?
        (VOS_VOID)vos_printf("0x%x\n",*pStr) : (VOS_VOID)vos_printf("0x%x,",*pStr);
    }
    return ulLen;
}
#endif
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




