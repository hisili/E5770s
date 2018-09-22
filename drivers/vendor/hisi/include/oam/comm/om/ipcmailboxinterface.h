

/*****************************************************************************
  1 ����ͷ�ļ�����

  notice:  ��Ҫ�����κ�����ͷ�ļ�!!!
*****************************************************************************/
#ifndef __IPCMAILBOXINTERFACE_H__
#define __IPCMAILBOXINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*lint -e413*/
#define GET_OFFSET(a,b)                 (unsigned long)((void *)(&(((a*)0)->b)))
/*lint +e413*/

/* ���ͨ�����䳤��(��������ͷ��Ϣ����������), bytes */
#define IPC_MAILBOX_SIZE_HIFI2CARM      (0x00000f98)
#define IPC_MAILBOX_SIZE_CARM2HIFI      (0x000007d8)
#define IPC_MAILBOX_SIZE_HIFI2ZSP       (0x000003c0)
#define IPC_MAILBOX_SIZE_ZSP2HIFI       (0x000003c0)
#define IPC_MAILBOX_SIZE_ZSP2CARM       (0x00004148)
#define IPC_MAILBOX_SIZE_CARM2ZSP       (0x00002510)

/*Build_Opt����*/
#define IPC_MB_HEAD_OFFSET_CARM2HIFI    GET_OFFSET(DRV_CARM_HIFI_MB_STRU, stCarm2HifiHead)
#define IPC_MB_HEAD_OFFSET_HIFI2CARM    GET_OFFSET(DRV_CARM_HIFI_MB_STRU, stHifi2CarmHead)
#define IPC_MB_OFFSET_CARM2HIFI         GET_OFFSET(DRV_CARM_HIFI_MB_STRU, aCarm2Hifi[0])
#define IPC_MB_OFFSET_HIFI2CARM         GET_OFFSET(DRV_CARM_HIFI_MB_STRU, aHifi2Carm[0])
#define PC_VOICE_OM_MED_ADDR_OFFSET     GET_OFFSET(DRV_CARM_HIFI_MB_STRU, stTxRing)
#define PC_VOICE_MED_OM_ADDR_OFFSET     GET_OFFSET(DRV_CARM_HIFI_MB_STRU, stRxRing)

/*DSP״̬��־��λ��SRAM1���µ�������OAM�·��׵�ַ����־HIFI������״̬*/
#define HIFI_STATUS_OFFSET              GET_OFFSET(DSP_DRX_STATUS_STRU, uwHifiStatus)

/* HIFI����C-CPU��IPC�жϸ��ñ�־��ַ���������øñ�־ָʾ���ж���;��Ĭ��Ϊ0(��
            ʾ��������ж�)�����ٷ���IPC�жϣ�������ÿ����Ӧ�жϺ���ָ�Ĭ��ֵ */
#define IPC_MB_STATUS_OFFSET_HIFI2CARM  GET_OFFSET(DSP_DRX_STATUS_STRU, uwIpcMailboxStatusHifi2Carm)

/* C-CPU����HIFI��IPC�жϸ��ñ�־��ַ���������øñ�־ָʾ���ж���;��Ĭ��Ϊ0(��
            ʾ��������ж�)�����ٷ���IPC�жϣ�������ÿ����Ӧ�жϺ���ָ�Ĭ��ֵ */
#define IPC_MB_STATUS_OFFSET_CARM2HIFI  GET_OFFSET(DSP_DRX_STATUS_STRU, uwIpcMailboxStatusCarm2Hifi)

/*DSP״̬��־��λ��SRAM1���µ�������OAM�·��׵�ַ����־ZSP������״̬*/
#define ZSP_STATUS_OFFSET               GET_OFFSET(DSP_DRX_STATUS_STRU, uwZspStatus)

/*��SAR����*/
#define PHY_ARM_SAR_SHARED_OFFSET       GET_OFFSET(CPHY_TEMP_INFO_STRU, usSarAntState)
#define PHY_ARM_SAR_REUCT_OFFSET        GET_OFFSET(CPHY_TEMP_INFO_STRU, usSarReduction)

/* GUL��ģ�͹����ϵ籣����־λ */
#define PHY_ARM_POWER_INIT_OFFSET           GET_OFFSET(CPHY_TEMP_INFO_STRU, ulSlaveLPPowerInit)
#define PHY_ARM_POWER_INIT_SLICE_OFFSET     GET_OFFSET(CPHY_TEMP_INFO_STRU, ulSlaveLPPowerInitSlice)
#define PHY_ARM_POWER_INIT_FLG              (0x12345678)

/* GUL��ģ�͹��ļ��ر�����־λ */
#define PHY_ARM_CODE_LOADING_OFFSET         GET_OFFSET(CPHY_TEMP_INFO_STRU, ulSlaveLPCodeLoading)
#define PHY_ARM_CODE_LOADING_SLICE_OFFSET   GET_OFFSET(CPHY_TEMP_INFO_STRU, ulSlaveLPCodeLoadingSlice)
#define PHY_ARM_CODE_LOADING_FLG	        (0x55AA55AA)

/* ���ͨ������ͷ�׵�ַ */
#define IPC_MAILBOX_HEAD_ADDR_CARM2HIFI     (HIFI_AXI_BASE_ADDR + IPC_MB_HEAD_OFFSET_CARM2HIFI)
#define IPC_MAILBOX_HEAD_ADDR_HIFI2CARM     (HIFI_AXI_BASE_ADDR + IPC_MB_HEAD_OFFSET_HIFI2CARM)
#define IPC_MAILBOX_HEAD_ADDR_ZSP2CARM      (AHB_BASE_ADDR + 0x3c00)
#define IPC_MAILBOX_HEAD_ADDR_CARM2ZSP      (AHB_BASE_ADDR + 0x01d8)

/* ���ͨ�������׵�ַ */
#define IPC_MAILBOX_ADDR_HIFI2ZSP_OFFSET    (0x1F620)
#define IPC_MAILBOX_ADDR_ZSP2HIFI_OFFSET    (0x1F820)
#define IPC_MAILBOX_ADDR_HIFI2CARM          (HIFI_AXI_BASE_ADDR + IPC_MB_OFFSET_HIFI2CARM)
#define IPC_MAILBOX_ADDR_CARM2HIFI          (HIFI_AXI_BASE_ADDR + IPC_MB_OFFSET_CARM2HIFI)
#define IPC_MAILBOX_ADDR_ZSP2CARM           (AHB_BASE_ADDR + 0x3c28)
#define IPC_MAILBOX_ADDR_CARM2ZSP           (AHB_BASE_ADDR + 0x0200)

#define IPC_MAILBOX_STATUS_DSP2ARM          (((unsigned long)AHB_BASE_ADDR)+0x01d0)/* 0x203001d0)
 */
#define IPC_MAILBOX_STATUS_ARM2DSP          (((unsigned long)AHB_BASE_ADDR)+0x01d4)/*(0x203001d4)
 */

/*��0x2ffe2060U��ʼ��16byte��ΪHifi���µ��־ʹ�ã�λ��SRAM1���µ��� */
#define HIFI_STATUS_FLAG_ADDR               (HIFI_STATUS_BASE_ADDR + HIFI_STATUS_OFFSET)/*(0x2ffe2060U)
 */

/* HIFI����C-CPU��IPC�жϸ��ñ�־��ַ���������øñ�־ָʾ���ж���;��Ĭ��Ϊ0(��
            ʾ��������ж�)�����ٷ���IPC�жϣ�������ÿ����Ӧ�жϺ���ָ�Ĭ��ֵ */
#define IPC_MAILBOX_STATUS_HIFI2CARM        (HIFI_STATUS_BASE_ADDR + IPC_MB_STATUS_OFFSET_HIFI2CARM)

/* C-CPU����HIFI��IPC�жϸ��ñ�־��ַ���������øñ�־ָʾ���ж���;��Ĭ��Ϊ0(��
            ʾ��������ж�)�����ٷ���IPC�жϣ�������ÿ����Ӧ�жϺ���ָ�Ĭ��ֵ */
#define IPC_MAILBOX_STATUS_CARM2HIFI        (HIFI_STATUS_BASE_ADDR + IPC_MB_STATUS_OFFSET_CARM2HIFI)

/*��0x2ffe2070U��ʼ��16byte��ΪZSP���µ��־ʹ�ã�λ��SRAM1���µ��� */
#define ZSP_STATUS_FLAG_ADDR                (HIFI_STATUS_BASE_ADDR + ZSP_STATUS_OFFSET)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ʵ �� ��  : IPC_TARGET_CPU_ENUM
 ��������  : ����IPC�ж����Ŀ��CPU, ��SOC����
*****************************************************************************/
enum IPC_TARGET_CPU_ENUM
{
    IPC_TARGET_CPU_APPARM = 0,          /* �ж�APP ARM */
    IPC_TARGET_CPU_COMARM,              /* �ж�COM ARM */
    IPC_TARGET_CPU_LTEDSP,              /* �ж�LTE DSP, balongv3r2���� */
    IPC_TARGET_CPU_MEDDSP,              /* �ж�MED DSP */
    IPC_TARGET_CPU_GUDSP,               /* �ж�GU DSP  */
    IPC_TARGET_CPU_BUTT
};
typedef unsigned short IPC_TARGET_CPU_ENUM_UINT16;

/*****************************************************************************
 ʵ �� ��  : IPC_MEDDSP_INT_SRC_ENUM
 ��������  : ����HiFi IPC�����Ϣ�ж�Դbitλ��
*****************************************************************************/
enum IPC_MEDDSP_INT_SRC_ENUM
{
    IPC_MEDDSP_INT_SRC_CARM_MSG = 4,    /* bit4, CARM�����Ϣ֪ͨ */
    IPC_MEDDSP_INT_SRC_GUDSP_MSG,       /* bit5, GUDSP�����Ϣ֪ͨ */
    IPC_MEDDSP_INT_SRC_BUTT
};
typedef unsigned short IPC_MEDDSP_INT_SRC_ENUM_UINT16;

/*****************************************************************************
 ʵ �� ��  : IPC_GUDSP_INT_SRC_ENUM
 ��������  : ����ZSP IPC�����Ϣ�ж�Դbitλ��
*****************************************************************************/
enum IPC_GUDSP_INT_SRC_ENUM
{
    IPC_GUDSP_INT_SRC_CARM_MSG = 4,     /* bit4, CARM�����Ϣ֪ͨ */
    IPC_GUDSP_INT_SRC_MEDDSP_MSG,       /* bit5, MED-DSP�����Ϣ֪ͨ */
    IPC_GUDSP_INT_SRC_BUTT
};
typedef unsigned short IPC_GUDSP_INT_SRC_ENUM_UINT16;

/*****************************************************************************
 ʵ �� ��  : IPC_CARM_INT_SRC_ENUM
 ��������  : ����CCPU IPC�����Ϣ�ж�Դbitλ��
*****************************************************************************/
enum IPC_CARM_INT_SRC_ENUM
{
    IPC_CARM_INT_SRC_GUDSP_MSG = 4,     /* bit4, GUDSP�����Ϣ֪ͨ */
    IPC_CARM_INT_SRC_MEDDSP_MSG,        /* bit5, MED-DSP�����Ϣ֪ͨ */
    IPC_CARM_INT_SRC_BUTT
};
typedef unsigned short IPC_CARM_INT_SRC_ENUM_UINT16;

/*****************************************************************************
 ö����    : HIFI_STATUS_FLAG_ENUM
 ö��˵��  : HIFI״̬��־����
*****************************************************************************/
enum HIFI_STATUS_FLAG_ENUM
{
    HIFI_STATUS_SLEEP                   = 0,                /*HIFI״̬ΪSLEEP̬*/
    HIFI_STATUS_SLEEP2WAKE              = 1,                /*HIFI״̬ΪSLEEP->WAKE�м�̬*/
    HIFI_STATUS_WAKE                    = 2,                /*HIFI״̬ΪWAKE̬*/
    HIFI_STATUS_WAKE2SLEEP              = 3,                /*HIFI״̬ΪWAKE->SLEEP�м�̬*/
    HIFI_STATUS_BUTT
};
typedef unsigned long HIFI_STATUS_FLAG_ENUM_UINT32;


/*****************************************************************************
 ö����    : ZSP_STATUS_FLAG_ENUM
 ö��˵��  : HIFI��ZSP�ķ���ZSP�Ƿ����˯�߱�־����
*****************************************************************************/
enum ZSP_STATUS_FLAG_ENUM
{
    ZSP_STATUS_WAKE                     = 0,                /* ZSP���ڻ���״̬,HIFI���Է��� */
    ZSP_STATUS_FORBID_SLEEP             = 1,                /* HIFI���ڷ���,ZSP������˯�� */
    ZSP_STATUS_SLEEP                    = 2,                /* ZSP����˯��״̬,HIFI���ɷ��� */
    ZSP_STATUS_BUTT
};
typedef unsigned long ZSP_STATUS_FLAG_ENUM_UINT32;

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

#if 0
/************************************************************************
 �ṹ��    : IPC_MAILBOX_HEAD_STRU
 �ṹ˵��  : �˼���Ϣ����ͷ
 ************************************************************************/
typedef struct
{
    unsigned long      ulProtectWord1;     /*������ 0x55AA55AA*/
    unsigned long      ulProtectWord2;     /*������ 0x5A5A5A5A*/
    unsigned long      ulFront;            /*���д�д��Ԫ�������(����������)ͷ�ĳ��ȣ���λ32bit */
    unsigned long      ulRear;             /*���д�����Ԫ�������(����������)ͷ�ĳ��ȣ���λ32bit */
    unsigned long      ulFrontslice;       /*�������价�ζ��е�ͷָ��ϵͳʱ��*/
    unsigned long      ulRearslice;        /*�������价�ζ��е�βָ��ϵͳʱ��*/
    unsigned short     ausReserve[4];      /*����*/
    unsigned long      ulProtectWord3;     /*������ 0x55AA55AA*/
    unsigned long      ulProtectWord4;     /*������ 0x5A5A5A5A*/
} IPC_MAILBOX_HEAD_STRU;
#endif

/************************************************************************
 �ṹ��    : IPC_MSG_HEADER_STRU
 �ṹ˵��  : �˼���Ϣͷ
 ************************************************************************/
typedef struct
{
    unsigned long      ulPartition;        /*��Ϣ�ָ��� 0xA5A5A5A5*/
    unsigned long      ulWriteSlice;       /*��Ϣд��ϵͳʱ����Ϣ */
    unsigned long      ulReadSlice;        /*��Ϣ����ϵͳʱ����Ϣ */
    unsigned long      ulSeqNum;           /*��Ϣ���к� */
    unsigned long      ulPriority;         /*0-����, 1-��ͨ */
    unsigned short     ausReserve[4];      /*����*/
    unsigned long      ulMsgLength;        /*��ulMsgLength�ֶ�(��������)�������Ϣ����*/
} IPC_MSG_HEADER_STRU;

#if 0
/************************************************************************
 �ṹ��    : IPC_MSG_BLK_STRU
 �ṹ˵��  : �˼���Ϣ��
 ************************************************************************/
typedef struct
{
    IPC_MSG_HEADER_STRU stMsgHead;      /* ��Ϣͷ */
    unsigned long      ulSenderCpuId;      /* ��Ϣ����CPU */
    unsigned long      ulSenderPid;        /* ��Ϣ����PID */
    unsigned long      ulReceiverCpuId;    /* ��Ϣ����CPU */
    unsigned long      ulReceiverPid;      /* ��Ϣ����PID */
    unsigned long      ulLength;           /* ��Ϣ���ĳ���,bytes */
    unsigned char      aucValue[4];        /* ��Ϣ���� */
} IPC_MSG_BLK_STRU;
#endif

/************************************************************************
 �ṹ��    : IPC_MAILBOX_QUEUE_STRU
 �ṹ˵��  : �˼���Ϣ������л���
 ************************************************************************/
/* ����ṹʾ��:
typedef struct
{
    unsigned long      ulProtectWord1;     //������ 0x55aa55aa
    unsigned long      ulProtectWord2;     //������ 0a5a5a5a5a
    unsigned long      aulMsgQueue[���г���-4];//���ζ��д�����ɸ�IPC_MSG_BLK_STRU
    unsigned long      ulProtectWord3;     //������ 0x55aa55aa
    unsigned long      ulProtectWord4;     //������ 0x5a5a5a5a
} IPC_MAILBOX_QUEUE_STRU;
*/


/*****************************************************************************
 �ṹ��    : PS_PHY_DYN_ADDR_SHARE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������PS�Ĺ����ַ��OAM��Ҫ��ȡ������TTF���߳�ʼ������PHY��ȡ
*****************************************************************************/
typedef struct
{
    /*������ʼ��,PSֻ��*/
    unsigned long uwProtectWord1;                      /*0x5a5a5a5a*/
    unsigned long uwPhyGttfShareAddr;                  /* GDSP��GTTF�����ڴ�ӿڵ�ַ,������ʼ��,ʹ���߱���*2+��ַ*/

    /*PS�����ʼ��,PHYֻ��*/
    unsigned long uwProtectWord2;                      /*0x5a5a5a5a��PS��д*/
    unsigned long uwHsupaUpaccMacePduBaseAddr;         /*HSUPA_UPACC_MACE_PDU_BASE_ADDR*/
    unsigned long uwEcsArmDspBufferSize;               /*ECS_ARM_DSP_BUFFER_SIZE*/
    unsigned long uwSocTimeSliceAddr;                  /*ʱ���ȡ��ַ*/

    /*AXI addr*/
    unsigned long uwStatusFlagAddr;                    /*HIFI/DSP STATUS_FLAG_ADDR*/
    unsigned long uwTempratureAddr;                    /*�±���ַ*/

    unsigned long uwHsdpaWttfBufAddr;                  /* HSDPA WTTF����buf��ַ */
    /*��������չ�á��Ժ���԰�ƽ̨��صĵ�ַ�ŵ����ﴫ�ݽ���*/
    unsigned long uwReserved[15];
}PS_PHY_DYN_ADDR_SHARE_STRU;



/*****************************************************************************
 �ṹ��    : PHY_HIFI_DYN_ADDR_SHARE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ������HIFI�Ĺ����ַ��OAM��Ҫ������HIFI��BOOT�����������е���Ӧ�ṹ��
*****************************************************************************/
typedef struct
{
    unsigned long uwProtectWord;           /*0x5a5a5a5a*/
    unsigned long uwZspDtcmBaseAddr;       /*ZSP�Ļ���ַ,32λ��ʽ*/
    unsigned long uwHifiPhyMboxHeadAddr;   /*HIFI��PHY�Ĺ�����ƫ�Ƶ�ַ���壬PHY�����ʼ�����뾲̬��ʼ����,ʹ���߱���*2+��ַ��*/
    unsigned long uwHifiPhyMboxBodyAddr;   /*HIFI��PHY�Ĺ�����ƫ�Ƶ�ַ���壬PHY�����ʼ�����뾲̬��ʼ����,ʹ���߱���*2+��ַ��*/
    unsigned long uwPhyHifiMboxHeadAddr;   /*PHY��HIFI�Ĺ�����ƫ�Ƶ�ַ���壬PHY�����ʼ�����뾲̬��ʼ��  ,ʹ���߱���*2+��ַ��*/
    unsigned long uwPhyHifiMboxBodyAddr;   /*PHY��HIFI�Ĺ�����ƫ�Ƶ�ַ���壬PHY�����ʼ�����뾲̬��ʼ��  ,ʹ���߱���*2+��ַ��*/
    unsigned long uwReserved[2];
}PHY_HIFI_DYN_ADDR_SHARE_STRU;
#if 0
/*****************************************************************************
 �ṹ��    : CARM_HIFI_DYN_ADDR_SHARE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :CARM��HIFI�Ĺ����ַ��OAM��Ҫ��ֵ��������Hifi���������е���Ӧ�ṹ��
*****************************************************************************/
typedef struct
{
    unsigned long uwProtectWord;       /*0x5a5a5a5a*/
    unsigned long uwCarmHifiMBAddr;    /*CARM��HIFI�����乲�������壬CARM�����ʼ�����뾲̬��ʼ����*/
    unsigned long uwNvBaseAddrPhy;     /*DDR��NV�������׵�ַ�������ַ*/
    unsigned long uwNvBaseAddrVirt;    /*DDR��NV�������׵�ַ��ARM�����ַ*/
    unsigned long uwTempratureAddr;    /*�±��ռ��׵�ַ*/
    unsigned long uwStatusFlagAddr;    /*HIFI/DSP STATUS_FLAG_ADDR*/
    unsigned long uwReserved[6];
}CARM_HIFI_DYN_ADDR_SHARE_STRU;
#endif
/*****************************************************************************
 �ṹ��    : PS_PHY_DYN_ADDR_SHARE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DSP�ϵ�ʱOAM��Ҫ��DSP��".dsp_share_addr"��д���½ṹ�����ݣ���ʼ��ַ��DRV����ZSP bin���󴫸�OAM
*****************************************************************************/
typedef struct
{
    PS_PHY_DYN_ADDR_SHARE_STRU      stPsPhyDynAddr;     /*PS��PHY�Ĺ���������*/
    PHY_HIFI_DYN_ADDR_SHARE_STRU    stPhyHifiDynAddr;   /*PHY��HIFI�Ĺ���������*/
}DSP_SHARE_ADDR_STRU;
#if 0
/*****************************************************************************
 �ṹ��    : HIFI_SHARE_ADDR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HIFI�ϵ�ʱOAM��Ҫ��Hifi��".sram1.shareaddr"��д���½ṹ�����ݣ���ʼ
             ��ַΪ��������Hifi��DDR�׵�ַ
*****************************************************************************/
typedef struct
{
    PHY_HIFI_DYN_ADDR_SHARE_STRU    stPhyHifiDynAddr;   /*PHY��HIFI�Ĺ���������*/
    CARM_HIFI_DYN_ADDR_SHARE_STRU   stCarmHifiDynAddr;  /*CARM��HIFI�Ĺ���������*/
}HIFI_SHARE_ADDR_STRU;
#endif
/*****************************************************************************
 �ṹ��    : CPHY_TEMP_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �¶Ȳ���������ݽṹ
*****************************************************************************/
typedef struct
{
    /* ulTempType:
                   bit0 1:PA �¶ȱ仯 0:���仯
                   bit1 1:USIM�¶ȱ仯
                   bit2 1:��ѹ�仯 */

    unsigned long                   ulTempType;
    unsigned short                  usPA1Adc;                   /* PA1 ADCֵ */
    short                           sPA1Temperature;            /* PA1 �¶� */
    unsigned short                  usPA2Adc;                   /* PA2 ADCֵ */
    short                           sPA2Temperature;            /* PA2 �¶� */
    short                           sTProtectTemperature;       /* DSP �±��¶ȣ�stick��USIM���¶ȣ�E5�ǵ���¶� */
    unsigned short                  usDCXOAdcResult;            /* DCXO�¶�ADCֵ */
    unsigned short                  usBatVoltage;               /* ��ص�ѹ���� */
    unsigned short                  usRsv1;
    unsigned short                  usSarAntState;              /*  */
    unsigned short                  usSarReduction;             /*  */
    unsigned long                   ulSlaveLPPowerInit;         /* ��ģ�͹����ϵ籣����־λ */
    unsigned long                   ulSlaveLPPowerInitSlice;    /*  */
    unsigned long                   ulSlaveLPCodeLoading;       /* ��ģ�͹��ļ��ر�����־λ */
    unsigned long                   ulSlaveLPCodeLoadingSlice;  /*  */
    unsigned short                  usRev[30];
} CPHY_TEMP_INFO_STRU;

/*****************************************************************************
 �ṹ��    : OMMED_RING_BUFFER_CONTROL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ring buffer������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    unsigned long                          uwProtectWord1;                         /*������ 0x55AA55AA*/
    unsigned long                          uwProtectWord2;                         /*������ 0x5A5A5A5A*/
    unsigned long                          uwWriteAddr;                            /*��һ��д���������Ե�ַ,��ָ��λΪByte*/
    unsigned long                          uwReadAddr;                             /*��һ����ȡ��������Ե�ַ,��ָ��λΪByte*/
    unsigned long                          uwBufSize;                              /*ring buffer�ĳ���,��λbyte */
    unsigned long                          uwBufAddr;                              /*ring buffer�Ļ�ַ*/
    unsigned long                          uwProtectWord3;                         /*������ 0x55AA55AA*/
    unsigned long                          uwProtectWord4;                         /*������ 0x5A5A5A5A*/
}RING_BUFFER_CONTROL_STRU;
/************************************************************************
 �ṹ��    : IPC_MAILBOX_HEAD_STRU
 �ṹ˵��  : �˼����仺��ͷ
 ************************************************************************/
typedef struct
{
    unsigned long      ulProtectWord1;     /*������ 0x55AA55AA*/
    unsigned long      ulProtectWord2;     /*������ 0x5A5A5A5A*/
    unsigned long      ulFront;            /*���д�д��Ԫ�������(����������)ͷ�ĳ��ȣ���λ32bit */
    unsigned long      ulRear;             /*���д�����Ԫ�������(����������)ͷ�ĳ��ȣ���λ32bit */
    unsigned long      ulFrontslice;       /*�������价�ζ��е�ͷָ��ϵͳʱ��*/
    unsigned long      ulRearslice;        /*�������价�ζ��е�βָ��ϵͳʱ��*/
    unsigned short     ausReserve[4];      /*����*/
    unsigned long      ulProtectWord3;     /*������ 0x55AA55AA*/
    unsigned long      ulProtectWord4;     /*������ 0x5A5A5A5A*/
} IPC_MAILBOX_HEAD_STRU;


/*****************************************************************************
 ʵ������  : DRV_CARM_HIFI_MB_STRU
 ��������  : CARM_HIFI��������ڴ�ṹ����OAMָ������ռ���׵�ַ
*****************************************************************************/
typedef struct
{
    IPC_MAILBOX_HEAD_STRU               stCarm2HifiHead;                        /* CARM��HIFI����������ͷ */
    unsigned char                       aCarm2Hifi[IPC_MAILBOX_SIZE_CARM2HIFI]; /* CARM��HIFI������  */
    IPC_MAILBOX_HEAD_STRU               stHifi2CarmHead;                        /* HIFI��CARM����������ͷ */
    unsigned char                       aHifi2Carm[IPC_MAILBOX_SIZE_HIFI2CARM]; /* HIFI��CARM������ */
    RING_BUFFER_CONTROL_STRU            stTxRing;
    RING_BUFFER_CONTROL_STRU            stRxRing;
}DRV_CARM_HIFI_MB_STRU;

/*****************************************************************************
 ʵ������  : DRV_CARM_HIFI_MB_STRU
 ��������  : CARM_HIFI��������ڴ�ṹ����OAMָ������ռ���׵�ַ
*****************************************************************************/
typedef struct
{
    unsigned long                  uwHifiStatus;
    unsigned long                  uwIpcMailboxStatusHifi2Carm;
    unsigned long                  uwIpcMailboxStatusCarm2Hifi;
    unsigned long                  uwZspStatus;
    unsigned long                  uwRsv[4];
}DSP_DRX_STATUS_STRU;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of IpcMailboxInterface.h */

