


#ifndef __PSLOG_H__
#define __PSLOG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "PsLogdef.h"
#include "errorlog.h"

/*****************************************************************************
  2 �궨��
******************************************************************************/
#define LOG_INVALID             0xFFFF

#define LOG_MAX_FILENAME_LEN    25

#define LOG_MAX_PARA_CNT        4
#define LOG_MAX_PARA_LEN        8

#define LOG_MAX_FLASH_SIZE      0x20000

#if (FEATURE_ON == FEATURE_MULTI_FS_PARTITION) /* SFT board*/
#define LOG_FILE_NAME           "/data/modemlog/OmLogFile.dat"
#else
#define LOG_FILE_NAME           "/yaffs0/OmLogFile.dat"
#endif

/*ȫ·���ļ��������֧�ֳ���*/
#define LOG_FILE_PATH_MAX_LENGTH      (30)

/*��־�ļ�֧�ֵĴ�С���� */
#define LOG_FILE_MAX_SIZE             (64*1024)

/* �ź������ֳ��� */
#define LOG_SEM_NAME_LEN              (6)

/* PS_LOG��־�ļ�������־ */
#define PS_LOG_FILE_PROTECT           (0)

#define LOG_MAX_COLUMN_VAL                  1024

/*���ڷ��͸����߲��LOG��Ҫ���ģ��ID,��ӡ����, �����ڷ����ڴ�ʱ��Ҫ��8*/
#define LOG_MODULE_ID_LEN                   8

#define LOG_MAX_COLUMN_VAL_EX               (LOG_MAX_COLUMN_VAL + LOG_MODULE_ID_LEN)

/* ���ڻ�����ʵ�ʴ�СΪ���볤�ȼ� 1 ,Ϊ��֤���ݴ���ڻ������е�ż��ַ,��߶�дЧ��,�˴��� 3 */
/* OM_Printf���λ�������С */
#define OM_PRINTF_BUFFER_SIZE               ((32*1024)+3)


#ifdef __LOG_BBIT__
#define LOG_MAX_ROW_VAL                     128
#else
#define LOG_MAX_ROW_VAL                     8
#endif

#define LOG_BUF_VOLUMN                      (LOG_MAX_COLUMN_VAL_EX * LOG_MAX_ROW_VAL)

/* ȷ��c���������ĺ꣬����������򷵻� */
#define LOG_AFFIRM(c) \
    if(!(c)) \
    { \
        vos_printf("LOG_ASSERT\n" ); \
        return; \
    }



/* Э��ջ��㷽ʽ������ */
#define PsLogId( FILEID, LINE ) \
            ( ( ( FILEID & 0x0000FFFF ) << 16 ) | ( LINE & 0x0000FFFF ) )

/* PS��װ�Ĵ�ӡ������ */
#define PS_PRINT_OFF        LOG_LEVEL_OFF        /* �رմ�ӡ     */
#define PS_PRINT_ERROR      LOG_LEVEL_ERROR      /* Error����    */
#define PS_PRINT_WARNING    LOG_LEVEL_WARNING    /* Warning����  */
#define PS_PRINT_NORMAL     LOG_LEVEL_NORMAL     /* Normal����   */
#define PS_PRINT_INFO       LOG_LEVEL_INFO       /* Info����     */
#define PS_PRINT_BUTT       LOG_LEVEL_BUTT       /* ��������     */

/*******************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 STRUCT����
*****************************************************************************/


/*****************************************************************************
  5 �ⲿ�ӿڶ���
*****************************************************************************/
/* BBIT�汾�ṩ���ⲿ�ӿ� */
#ifdef __LOG_BBIT__
extern void OM_Log(char             *cFileName,  unsigned long      ulLineNum,
                   LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN   enSubModId,
                   LOG_LEVEL_EN      enLevel,    char              *pcString);
extern void OM_Log1(char             *cFileName,  unsigned long      ulLineNum,
                    LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN   enSubModId,
                    LOG_LEVEL_EN      enLevel,    char              *pcString,
                    long              lPara1);
extern void OM_Log2(char             *cFileName,  unsigned long      ulLineNum,
                    LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN   enSubModId,
                    LOG_LEVEL_EN      enLevel,    char              *pcString,
                    long              lPara1,     long               lPara2);
extern void OM_Log3(char             *cFileName,  unsigned long      ulLineNum,
                    LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN   enSubModId,
                    LOG_LEVEL_EN      enLevel,    char              *pcString,
                    long              lPara1,     long               lPara2,
                    long              lPara3);
extern void OM_Log4(char             *cFileName,  unsigned long      ulLineNum,
                    LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN   enSubModId,
                    LOG_LEVEL_EN      enLevel,    char              *pcString,
                    long              lPara1,     long               lPara2,
                    long              lPara3,     long               lPara4);
#endif

/* Release�汾�ṩ���ⲿ�ӿ� */
#ifdef __LOG_RELEASE__
extern void OM_LogId(LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN  enSubModId,
                     LOG_LEVEL_EN      enLevel,    unsigned long     ulLogId);
extern void OM_LogId1(LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN  enSubModId,
                      LOG_LEVEL_EN      enLevel,    unsigned long     ulLogId,
                      long              lPara1);
extern void OM_LogId2(LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN  enSubModId,
                      LOG_LEVEL_EN      enLevel,    unsigned long     ulLogId,
                      long              lPara1,     long              lPara2);
extern void OM_LogId3(LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN  enSubModId,
                      LOG_LEVEL_EN      enLevel,    unsigned long     ulLogId,
                      long              lPara1,     long              lPara2,
                      long              lPara3);
extern void OM_LogId4(LOG_MODULE_ID_EN  enModuleId, LOG_SUBMOD_ID_EN  enSubModId,
                      LOG_LEVEL_EN      enLevel,    unsigned long     ulLogId,
                      long              lPara1,     long              lPara2,
                      long              lPara3,     long              lPara4);
#endif



/*****************************************************************************
  6 PS��װ���ⲿ�ӿں�������
*****************************************************************************/
#ifdef __LOG_BBIT__
#define PS_LOG(ModulePID, SubMod, Level, String) \
     OM_Log(__FILE__, __LINE__, (LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, String)

#define PS_LOG1(ModulePID, SubMod, Level, String, Para1) \
    OM_Log1(__FILE__, __LINE__, (LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, String, Para1)

#define PS_LOG2(ModulePID, SubMod, Level, String, Para1, Para2) \
    OM_Log2(__FILE__, __LINE__, (LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, String,\
               Para1, Para2)

#define PS_LOG3(ModulePID, SubMod, Level, String,\
            Para1, Para2, Para3) \
    OM_Log3(__FILE__, __LINE__, (LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, String,\
            Para1, Para2, Para3)

#define PS_LOG4(ModulePID, SubMod, Level, String, \
            Para1, Para2, Para3, Para4) \
    OM_Log4(__FILE__, __LINE__, (LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, String,\
            Para1, Para2, Para3, Para4)

#endif

#ifdef __LOG_RELEASE__

#define PS_LOG(ModulePID, SubMod, Level, String) \
     OM_LogId((LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, \
            PsLogId(THIS_FILE_ID, __LINE__))

#define PS_LOG1(ModulePID, SubMod, Level, String, Para1) \
     OM_LogId1((LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, \
            PsLogId(THIS_FILE_ID, __LINE__), Para1)

#define PS_LOG2(ModulePID, SubMod, Level, String, Para1, Para2) \
     OM_LogId2((LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, \
            PsLogId(THIS_FILE_ID, __LINE__), Para1, Para2)

#define PS_LOG3(ModulePID, SubMod, Level, String, \
            Para1, Para2, Para3) \
     OM_LogId3((LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, \
            PsLogId(THIS_FILE_ID, __LINE__), Para1, Para2, Para3)

#define PS_LOG4(ModulePID, SubMod, Level, String,\
            Para1, Para2, Para3, Para4) \
     OM_LogId4((LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, \
            PsLogId(THIS_FILE_ID, __LINE__), Para1, Para2, Para3, Para4)
#endif

/*****************************************************************************
  �ṩ���ⲿģ��ʹ�õ�LOG�ӿڣ�����DRV��MEDIA
*****************************************************************************/

#ifdef __LOG_BBIT__
#define OM_LOG(ModulePID, SubMod, Level, String) \
     OM_Log(__FILE__, __LINE__, (LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, String)

#define OM_LOG1(ModulePID, SubMod, Level, String, Para1) \
     OM_Log1(__FILE__, __LINE__, (LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, String, Para1)

#define OM_LOG2(ModulePID, SubMod, Level, String, Para1, Para2) \
    OM_Log2(__FILE__, __LINE__, (LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, String,\
               Para1, Para2)

#define OM_LOG3(ModulePID, SubMod, Level, String,\
            Para1, Para2, Para3) \
    OM_Log3(__FILE__, __LINE__, (LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, String,\
            Para1, Para2, Para3)

#define OM_LOG4(ModulePID, SubMod, Level, String, \
            Para1, Para2, Para3, Para4) \
    OM_Log4(__FILE__, __LINE__, (LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, String,\
            Para1, Para2, Para3, Para4)

#endif

#ifdef __LOG_RELEASE__

#define OM_LOG(ModulePID, SubMod, Level, String) \
     OM_LogId((LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, \
            PsLogId(THIS_FILE_ID, __LINE__))

#define OM_LOG1(ModulePID, SubMod, Level, String, Para1) \
     OM_LogId1((LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, \
            PsLogId(THIS_FILE_ID, __LINE__), Para1)

#define OM_LOG2(ModulePID, SubMod, Level, String, Para1, Para2) \
     OM_LogId2((LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, \
            PsLogId(THIS_FILE_ID, __LINE__), Para1, Para2)

#define OM_LOG3(ModulePID, SubMod, Level, String, \
            Para1, Para2, Para3) \
     OM_LogId3((LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, \
            PsLogId(THIS_FILE_ID, __LINE__), Para1, Para2, Para3)

#define OM_LOG4(ModulePID, SubMod, Level, String,\
            Para1, Para2, Para3, Para4) \
     OM_LogId4((LOG_MODULE_ID_EN)ModulePID, (LOG_SUBMOD_ID_EN)SubMod, Level, \
            PsLogId(THIS_FILE_ID, __LINE__), Para1, Para2, Para3, Para4)
#endif

unsigned long LOG_GetTick(void);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __PSLOG_H__ */

