

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_SIO_INTERFACE_H__
#define __SOC_SIO_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) SIO
 ****************************************************************************/
/* �Ĵ���˵�����汾�Ĵ�����������¼SIO�İ汾�źͽ���SIO���Բ��ԡ�
   λ����UNION�ṹ:  SOC_SIO_VERSION_UNION */
#define SOC_SIO_VERSION_ADDR(base)                    ((base) + (0x03C))

/* �Ĵ���˵����ģʽ�Ĵ�����������SIO�����Ļ���ģʽ����ѡ��
            (I)��ģʽ�£�CRG��ʱ�Ӻ�ͬ���źŸ�CODEC��ͬʱ��SIO��
            (I)��ģʽ�£�ʱ�Ӻ�ͬ���ź����ⲿCODEC�͸�SIO��
            I2S��PCM������ģʽѡ����ϵͳ���ƼĴ���SC_PERICLK_CTRL0�趨��
   λ����UNION�ṹ:  SOC_SIO_MODE_UNION */
#define SOC_SIO_MODE_ADDR(base)                       ((base) + (0x040))

/* �Ĵ���˵����SIO���ж�״ָ̬ʾ�Ĵ�����
            ���ڽ����жϣ�������FIFO��������ȴ���FIFO��ֵʱ����һֱ�Ѹߵ�ƽ���浽�ж�״̬�Ĵ����У�һֱ�����жϣ���ʹCPU��һ���жϣ����ж�״̬�Ĵ���������һ��ʱ�������ٴ���λ������ˣ�����CPU�Ĵ�����Ϊ��
            (S)��SIO_CT_CLR[intr_en]д1���ر�ȫ���ж�ʹ�ܡ�
            (S)���ж�״̬�Ĵ���SIO_INTSTATUS��
            (S)�����ж�Դ������Ӧ����
            (S)��SIO_INTCLR����Ӧλд1������жϡ�
            (S)��д�Ĵ���SIO_CT_SET[intr_en]д1����ȫ���ж�ʹ�ܡ�
            (SE)
            �����жϵĲ�����ʽ������жϲ�����ʽ��ͬ����˶��ڷ����жϵĴ�������Ҳ������ͬ�ķ�ʽ��
            ���Ĵ�����ԭʼ�ж�״̬�Ĵ���������Ӧ�ж�λ���ε�����£��ж���������ʱ����Ӧ�ж�״̬λ��Ȼ����λ�������ᴥ���жϡ�
   λ����UNION�ṹ:  SOC_SIO_INTSTATUS_UNION */
#define SOC_SIO_INTSTATUS_ADDR(base)                  ((base) + (0x044))

/* �Ĵ���˵�����ж�����Ĵ��������԰�λ�����BitֵΪ0��ʾ������жϣ�Ϊ1��ʾ����жϡ�
   λ����UNION�ṹ:  SOC_SIO_INTCLR_UNION */
#define SOC_SIO_INTCLR_ADDR(base)                     ((base) + (0x048))

/* �Ĵ���˵����I2Sģʽ�µ����������ݷ��ͼĴ�����
            ��Ĵ���д����ʱ����Ч��������ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
   λ����UNION�ṹ:  SOC_SIO_I2S_LEFT_XD_UNION */
#define SOC_SIO_I2S_LEFT_XD_ADDR(base)                ((base) + (0x04C))

/* �Ĵ���˵����I2Sģʽ�µ����������ݷ��ͼĴ�����PCM���ݷ��ͼĴ�����I2S���������ݷ��ͼĴ����Ǹ��õġ�
            ��Ĵ���д����ʱ����Ч��������ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
   λ����UNION�ṹ:  SOC_SIO_I2S_RIGHT_XD_UNION */
#define SOC_SIO_I2S_RIGHT_XD_ADDR(base)               ((base) + (0x050))

/* �Ĵ���˵����PCMģʽ�µ����ݷ��ͼĴ�����PCM���ݷ��ͼĴ�����I2S���������ݷ��ͼĴ����Ǹ��õġ�
            ��Ĵ���д��Ч����ʱ����Ч��������ڼĴ����ĵ�bit�������磬8bit���ʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݡ�16bit���ʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
   λ����UNION�ṹ:  SOC_SIO_PCM_XD_UNION */
#define SOC_SIO_PCM_XD_ADDR(base)                     ((base) + (0x050))

/* �Ĵ���˵����I2S���������ݽ��ռĴ�����
            SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
   λ����UNION�ṹ:  SOC_SIO_I2S_LEFT_RD_UNION */
#define SOC_SIO_I2S_LEFT_RD_ADDR(base)                ((base) + (0x054))

/* �Ĵ���˵����I2S���������ݽ��ռĴ�����
            SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
   λ����UNION�ṹ:  SOC_SIO_I2S_RIGHT_RD_UNION */
#define SOC_SIO_I2S_RIGHT_RD_ADDR(base)               ((base) + (0x058))

/* �Ĵ���˵����PCM�������ݼĴ���������I2S���������ռĴ����Ǹ��õġ�
            SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
   λ����UNION�ṹ:  SOC_SIO_PCM_RD_UNION */
#define SOC_SIO_PCM_RD_ADDR(base)                     ((base) + (0x058))

/* �Ĵ���˵�������üĴ�����
            Ϊ���ܹ�����Ķ�SIO���ƼĴ�������λ��������SIO�У�ΪSIO���ƼĴ���������2����ַ��0x05C��SIO_CT_SET����0x060��SIO_CT_CLR�������У�
            0x05CΪ���üĴ�����ַ������0x05C�Ĵ�������Ӧλд��1ʱ����Ӧλ����Ϊ1��д0��Ч���üĴ�������Ϊ��д��
   λ����UNION�ṹ:  SOC_SIO_CT_SET_UNION */
#define SOC_SIO_CT_SET_ADDR(base)                     ((base) + (0x05C))

/* �Ĵ���˵��������Ĵ�����
            Ϊ���ܹ�����Ķ�SIO���ƼĴ�������λ��������SIO�У�ΪSIO���ƼĴ���������2����ַ��0x05C��SIO_CT_SET����0x060��SIO_CT_CLR�������У�
            0x060Ϊ����Ĵ�����ַ������Ĵ�������Ӧλд��1ʱ����Ӧλ�������д0��Ч���üĴ�������Ϊֻд��
   λ����UNION�ṹ:  SOC_SIO_CT_CLR_UNION */
#define SOC_SIO_CT_CLR_ADDR(base)                     ((base) + (0x060))

/* �Ĵ���˵����SIO����״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SIO_RX_STA_UNION */
#define SOC_SIO_RX_STA_ADDR(base)                     ((base) + (0x068))

/* �Ĵ���˵����SIO����״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_SIO_TX_STA_UNION */
#define SOC_SIO_TX_STA_ADDR(base)                     ((base) + (0x06C))

/* �Ĵ���˵����I2S/PCMģʽ�µ����ݿ�����üĴ�����
   λ����UNION�ṹ:  SOC_SIO_DATA_WIDTH_SET_UNION */
#define SOC_SIO_DATA_WIDTH_SET_ADDR(base)             ((base) + (0x078))

/* �Ĵ���˵����I2S����������ʼλ�����ÿ��ƼĴ�����
            ��I2Sģʽ�£������������ݲ�����ַ�ϲ�ʹ�ܺ󣬿�����ʼ�����Ǵ���������ʼ���Ǵ���������ʼ��
   λ����UNION�ṹ:  SOC_SIO_I2S_START_POS_UNION */
#define SOC_SIO_I2S_START_POS_ADDR(base)              ((base) + (0x07C))

/* �Ĵ���˵����I2S��������������ǰλ��״̬�Ĵ�����
            ��I2Sģʽ�£������������ݲ�����ַ�ϲ�ʹ�ܺ�ָʾ��һ�η��ʼĴ����Ǵ���������ʼ���Ǵ���������ʼ��
   λ����UNION�ṹ:  SOC_SIO_I2S_POS_FLAG_UNION */
#define SOC_SIO_I2S_POS_FLAG_ADDR(base)               ((base) + (0x080))

/* �Ĵ���˵������λ���ݷ�����չʹ�ܼĴ������ñ�־ֻ�Խ���������Ч���Է���������Ч��PCMģʽ��I2Sģʽ�½��յ������ݶ�֧�ַ�����չ��
            �ڽ�����Ч����λ��Ϊ8/16/18/20/24 bitʱ������ñ�־ʹ�ܣ��ѽ��յ�������ת��Ϊ32bit����ʱ����32bit���ݵĸ�λ��Ч��������Ϊ�������������Чbit��Ӧ��ֵ��Ȼ����д�����FIFO��
            ��16bitλ��Ϊ����
            if (data_rx[15] == 1 ) 
            data_rx[31:16]=0xffff;
            else
            data_rx[31:16]=0x0000;
   λ����UNION�ṹ:  SOC_SIO_SIGNED_EXT_UNION */
#define SOC_SIO_SIGNED_EXT_ADDR(base)                 ((base) + (0x084))

/* �Ĵ���˵����I2Sģʽ�����������ݲ�����ַ�ϲ�ʹ�ܼĴ�����
            ��I2Sģʽ�£���DMA��ʽ��дSIO��FIFO����ʱ����Ϊ�����������ݵ�ַ��ͬ����ҪCPU��������DMA�����ĵ�ַ������CPUЧ�ʵ͡�Ϊ�����CPU��Ч�ʣ��ṩ�����������ݵĶ�д��ͳһ��ַʹ�ܿ��ơ�
            ʹ������£���������������ͳһʹ��SIO_I2S_DUAL_RX_CHN�Ĵ�����д������������ͳһʹ��SIO_I2S_DUAL_TX_CHN�Ĵ�����
   λ����UNION�ṹ:  SOC_SIO_I2S_POS_MERGE_EN_UNION */
#define SOC_SIO_I2S_POS_MERGE_EN_ADDR(base)           ((base) + (0x088))

/* �Ĵ���˵�����ж����μĴ�����
   λ����UNION�ṹ:  SOC_SIO_INTMASK_UNION */
#define SOC_SIO_INTMASK_ADDR(base)                    ((base) + (0x08C))

/* �Ĵ���˵������ȡ�������ݼĴ�����I2S��������������ַ�ϲ�ʹ�ܺ󣬶�ȡ�������ݡ�
   λ����UNION�ṹ:  SOC_SIO_I2S_DUAL_RX_CHN_UNION */
#define SOC_SIO_I2S_DUAL_RX_CHN_ADDR(base)            ((base) + (0x0A0))

/* �Ĵ���˵����д�������ݼĴ�����I2S��������������ַ�ϲ�ʹ�ܺ�д�������ݡ�
   λ����UNION�ṹ:  SOC_SIO_I2S_DUAL_TX_CHN_UNION */
#define SOC_SIO_I2S_DUAL_TX_CHN_ADDR(base)            ((base) + (0x0C0))





/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  6 STRUCT����
*****************************************************************************/



/*****************************************************************************
  7 UNION����
*****************************************************************************/

/****************************************************************************
                     (1/1) SIO
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_SIO_VERSION_UNION
 �ṹ˵��  : VERSION �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000013�����:32
 �Ĵ���˵��: �汾�Ĵ�����������¼SIO�İ汾�źͽ���SIO���Բ��ԡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vesion   : 8;  /* bit[0-7] : SIO�İ汾�š� */
        unsigned int  sio_loop : 1;  /* bit[8]   : 0������ģʽ��
                                                   1��SIO���ͺͽ������ݻ���ģʽ������SIO���Բ��ԡ��ڸ�ģʽ�£���SIO�Ķ���ӿڴ���SIO���մ�����������SIO���ʹ���������ֱ�������� */
        unsigned int  reserved : 23; /* bit[9-31]: ������ */
    } reg;
} SOC_SIO_VERSION_UNION;
#endif
#define SOC_SIO_VERSION_vesion_START    (0)
#define SOC_SIO_VERSION_vesion_END      (7)
#define SOC_SIO_VERSION_sio_loop_START  (8)
#define SOC_SIO_VERSION_sio_loop_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_SIO_MODE_UNION
 �ṹ˵��  : MODE �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģʽ�Ĵ�����������SIO�����Ļ���ģʽ����ѡ��
            (I)��ģʽ�£�CRG��ʱ�Ӻ�ͬ���źŸ�CODEC��ͬʱ��SIO��
            (I)��ģʽ�£�ʱ�Ӻ�ͬ���ź����ⲿCODEC�͸�SIO��
            I2S��PCM������ģʽѡ����ϵͳ���ƼĴ���SC_PERICLK_CTRL0�趨��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sio_mode   : 1;  /* bit[0]   : PCM/I2Sģʽѡ��
                                                     0��I2Sģʽ��
                                                     &#13;1��PCMģʽ�� */
        unsigned int  pcm_mode   : 1;  /* bit[1]   : PCMʱ��ģʽ��
                                                     0����׼ģʽ��
                                                     &#13;1���Զ���ģʽ�� */
        unsigned int  reserved_0 : 1;  /* bit[2]   : ��������������Ϊ0 */
        unsigned int  ext_rec_en : 1;  /* bit[3]   : ��׼ģʽ�£�I2S�����������������ݣ�������������������PCMֻ����һ�����������ݡ�
                                                     ��·����ģʽ�£�����I2S��PCM������ͨ�����������á���ģʽ�£�ͨ�������ݿ�ȱ���Ϊ8bit��16bit��
                                                     0����׼��I2S��PCM����ģʽ��
                                                     1����չ��I2S��PCM��·����ģʽ�� */
        unsigned int  chn_num    : 2;  /* bit[4-5] : ��·���յ�ͨ����ѡ��
                                                     00��2 chn��
                                                     01��4 chn��
                                                     10��8 chn��
                                                     11��16 chn�� */
        unsigned int  clk_edge   : 1;  /* bit[6]   : PCM��·����ģʽ�£���������ʱ�ӱ���ѡ��
                                                     0���½�����Ч��
                                                     1����������Ч�� */
        unsigned int  reserved_1 : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_SIO_MODE_UNION;
#endif
#define SOC_SIO_MODE_sio_mode_START    (0)
#define SOC_SIO_MODE_sio_mode_END      (0)
#define SOC_SIO_MODE_pcm_mode_START    (1)
#define SOC_SIO_MODE_pcm_mode_END      (1)
#define SOC_SIO_MODE_ext_rec_en_START  (3)
#define SOC_SIO_MODE_ext_rec_en_END    (3)
#define SOC_SIO_MODE_chn_num_START     (4)
#define SOC_SIO_MODE_chn_num_END       (5)
#define SOC_SIO_MODE_clk_edge_START    (6)
#define SOC_SIO_MODE_clk_edge_END      (6)


/*****************************************************************************
 �ṹ��    : SOC_SIO_INTSTATUS_UNION
 �ṹ˵��  : INTSTATUS �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO���ж�״ָ̬ʾ�Ĵ�����
            ���ڽ����жϣ�������FIFO��������ȴ���FIFO��ֵʱ����һֱ�Ѹߵ�ƽ���浽�ж�״̬�Ĵ����У�һֱ�����жϣ���ʹCPU��һ���жϣ����ж�״̬�Ĵ���������һ��ʱ�������ٴ���λ������ˣ�����CPU�Ĵ�����Ϊ��
            (S)��SIO_CT_CLR[intr_en]д1���ر�ȫ���ж�ʹ�ܡ�
            (S)���ж�״̬�Ĵ���SIO_INTSTATUS��
            (S)�����ж�Դ������Ӧ����
            (S)��SIO_INTCLR����Ӧλд1������жϡ�
            (S)��д�Ĵ���SIO_CT_SET[intr_en]д1����ȫ���ж�ʹ�ܡ�
            (SE)
            �����жϵĲ�����ʽ������жϲ�����ʽ��ͬ����˶��ڷ����жϵĴ�������Ҳ������ͬ�ķ�ʽ��
            ���Ĵ�����ԭʼ�ж�״̬�Ĵ���������Ӧ�ж�λ���ε�����£��ж���������ʱ����Ӧ�ж�״̬λ��Ȼ����λ�������ᴥ���жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_intr             : 1;  /* bit[0]   : ����FIFO������ֵ�ж�״̬��
                                                              0��δ�����жϣ�
                                                              &#13;1���Ѳ����жϡ� */
        unsigned int  tx_intr             : 1;  /* bit[1]   : ����FIFO������ֵ�ж�״̬��
                                                              0��δ�����жϣ�
                                                              &#13;1���Ѳ����жϡ� */
        unsigned int  rx_right_fifo_over  : 1;  /* bit[2]   : I2Sģʽ�£�����������FIFO�����ж�״̬��PCMģʽ�£�PCM����FIFO�����־��
                                                              0��δ�����жϣ�
                                                              1���Ѳ����жϡ� */
        unsigned int  rx_left_fifo_over   : 1;  /* bit[3]   : I2Sģʽ�£�����������FIFO�����ж�״̬��PCMģʽ����Ч��
                                                              0��δ�����жϣ�
                                                              &#13;1���Ѳ����жϡ� */
        unsigned int  tx_right_fifo_under : 1;  /* bit[4]   : I2Sģʽ�£�����������FIFO�����ж�״̬��PCMģʽ�£�PCM����FIFO�����־��
                                                              0��δ�����жϣ�
                                                              &#13;1���Ѳ����жϡ� */
        unsigned int  tx_left_fifo_under  : 1;  /* bit[5]   : I2Sģʽ�£�����������FIFO�����ж�״̬��PCMģʽ����Ч��
                                                              0��δ�����жϣ�
                                                              &#13;1���Ѳ����жϡ� */
        unsigned int  reserved            : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SIO_INTSTATUS_UNION;
#endif
#define SOC_SIO_INTSTATUS_rx_intr_START              (0)
#define SOC_SIO_INTSTATUS_rx_intr_END                (0)
#define SOC_SIO_INTSTATUS_tx_intr_START              (1)
#define SOC_SIO_INTSTATUS_tx_intr_END                (1)
#define SOC_SIO_INTSTATUS_rx_right_fifo_over_START   (2)
#define SOC_SIO_INTSTATUS_rx_right_fifo_over_END     (2)
#define SOC_SIO_INTSTATUS_rx_left_fifo_over_START    (3)
#define SOC_SIO_INTSTATUS_rx_left_fifo_over_END      (3)
#define SOC_SIO_INTSTATUS_tx_right_fifo_under_START  (4)
#define SOC_SIO_INTSTATUS_tx_right_fifo_under_END    (4)
#define SOC_SIO_INTSTATUS_tx_left_fifo_under_START   (5)
#define SOC_SIO_INTSTATUS_tx_left_fifo_under_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_SIO_INTCLR_UNION
 �ṹ˵��  : INTCLR �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�����Ĵ��������԰�λ�����BitֵΪ0��ʾ������жϣ�Ϊ1��ʾ����жϡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_intr             : 1;  /* bit[0]   : ����FIFO������ֵ�ж������ */
        unsigned int  tx_intr             : 1;  /* bit[1]   : ����FIFO������ֵ�ж������ */
        unsigned int  rx_right_fifo_over  : 1;  /* bit[2]   : I2Sģʽ�£�����������FIFO�����ж������
                                                              PCMģʽ�£�PCM����FIFO�����ж������ */
        unsigned int  rx_left_fifo_over   : 1;  /* bit[3]   : I2Sģʽ�£�����������FIFO�����ж������
                                                              PCMģʽ����Ч�� */
        unsigned int  tx_right_fifo_under : 1;  /* bit[4]   : I2Sģʽ�£�����������FIFO�����ж������
                                                              PCMģʽ�£�PCM����FIFO�����ж������ */
        unsigned int  tx_left_fifo_under  : 1;  /* bit[5]   : I2Sģʽ�£�����������FIFO�����ж������
                                                              PCMģʽ����Ч�� */
        unsigned int  reserved            : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SIO_INTCLR_UNION;
#endif
#define SOC_SIO_INTCLR_rx_intr_START              (0)
#define SOC_SIO_INTCLR_rx_intr_END                (0)
#define SOC_SIO_INTCLR_tx_intr_START              (1)
#define SOC_SIO_INTCLR_tx_intr_END                (1)
#define SOC_SIO_INTCLR_rx_right_fifo_over_START   (2)
#define SOC_SIO_INTCLR_rx_right_fifo_over_END     (2)
#define SOC_SIO_INTCLR_rx_left_fifo_over_START    (3)
#define SOC_SIO_INTCLR_rx_left_fifo_over_END      (3)
#define SOC_SIO_INTCLR_tx_right_fifo_under_START  (4)
#define SOC_SIO_INTCLR_tx_right_fifo_under_END    (4)
#define SOC_SIO_INTCLR_tx_left_fifo_under_START   (5)
#define SOC_SIO_INTCLR_tx_left_fifo_under_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_SIO_I2S_LEFT_XD_UNION
 �ṹ˵��  : I2S_LEFT_XD �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2Sģʽ�µ����������ݷ��ͼĴ�����
            ��Ĵ���д����ʱ����Ч��������ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_left_data : 32; /* bit[0-31]: �������������ݡ� */
    } reg;
} SOC_SIO_I2S_LEFT_XD_UNION;
#endif
#define SOC_SIO_I2S_LEFT_XD_tx_left_data_START  (0)
#define SOC_SIO_I2S_LEFT_XD_tx_left_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SIO_I2S_RIGHT_XD_UNION
 �ṹ˵��  : I2S_RIGHT_XD �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2Sģʽ�µ����������ݷ��ͼĴ�����PCM���ݷ��ͼĴ�����I2S���������ݷ��ͼĴ����Ǹ��õġ�
            ��Ĵ���д����ʱ����Ч��������ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_right_data : 32; /* bit[0-31]: �������������ݡ� */
    } reg;
} SOC_SIO_I2S_RIGHT_XD_UNION;
#endif
#define SOC_SIO_I2S_RIGHT_XD_tx_right_data_START  (0)
#define SOC_SIO_I2S_RIGHT_XD_tx_right_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SIO_PCM_XD_UNION
 �ṹ˵��  : PCM_XD �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCMģʽ�µ����ݷ��ͼĴ�����PCM���ݷ��ͼĴ�����I2S���������ݷ��ͼĴ����Ǹ��õġ�
            ��Ĵ���д��Ч����ʱ����Ч��������ڼĴ����ĵ�bit�������磬8bit���ʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݡ�16bit���ʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_data  : 16; /* bit[0-15] : PCM�������ݡ� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SIO_PCM_XD_UNION;
#endif
#define SOC_SIO_PCM_XD_tx_data_START   (0)
#define SOC_SIO_PCM_XD_tx_data_END     (15)


/*****************************************************************************
 �ṹ��    : SOC_SIO_I2S_LEFT_RD_UNION
 �ṹ˵��  : I2S_LEFT_RD �Ĵ����ṹ���塣��ַƫ����:0x054����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2S���������ݽ��ռĴ�����
            SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_left_data : 32; /* bit[0-31]: I2S�������������ݡ� */
    } reg;
} SOC_SIO_I2S_LEFT_RD_UNION;
#endif
#define SOC_SIO_I2S_LEFT_RD_rx_left_data_START  (0)
#define SOC_SIO_I2S_LEFT_RD_rx_left_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SIO_I2S_RIGHT_RD_UNION
 �ṹ˵��  : I2S_RIGHT_RD �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2S���������ݽ��ռĴ�����
            SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_right_data : 32; /* bit[0-31]: I2S�������������ݡ� */
    } reg;
} SOC_SIO_I2S_RIGHT_RD_UNION;
#endif
#define SOC_SIO_I2S_RIGHT_RD_rx_right_data_START  (0)
#define SOC_SIO_I2S_RIGHT_RD_rx_right_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SIO_PCM_RD_UNION
 �ṹ˵��  : PCM_RD �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: PCM�������ݼĴ���������I2S���������ռĴ����Ǹ��õġ�
            SIOģ��ѽ��յ�����Ч���ݷ��ڼĴ����ĵ�bit�������磬���ݿ��Ϊ8bitʱ��bit[7:0]Ϊ��Ч���ݣ�bit[31:8]Ϊ��Ч���ݣ����ݿ��Ϊ16bitʱ��bit[15:0]Ϊ��Ч���ݣ�bit[31:16]Ϊ��Ч���ݡ�������Ч���ݿ�ȵ�bitλ��SIOģ���Զ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx__data : 16; /* bit[0-15] : PCM�������ݡ� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SIO_PCM_RD_UNION;
#endif
#define SOC_SIO_PCM_RD_rx__data_START  (0)
#define SOC_SIO_PCM_RD_rx__data_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_SIO_CT_SET_UNION
 �ṹ˵��  : CT_SET �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00008000�����:32
 �Ĵ���˵��: ���üĴ�����
            Ϊ���ܹ�����Ķ�SIO���ƼĴ�������λ��������SIO�У�ΪSIO���ƼĴ���������2����ַ��0x05C��SIO_CT_SET����0x060��SIO_CT_CLR�������У�
            0x05CΪ���üĴ�����ַ������0x05C�Ĵ�������Ӧλд��1ʱ����Ӧλ����Ϊ1��д0��Ч���üĴ�������Ϊ��д��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_fifo_threshold : 4;  /* bit[0-3]  : ����FIFO��ֵ��
                                                             ��tx_right_depth < (tx_fifo_threshold + 1)ʱ���������жϺ�DMA���� */
        unsigned int  rx_fifo_threshold : 4;  /* bit[4-7]  : ����FIFO��ֵ��
                                                             ��rx_right_depth 3(rx_fifo_threshold + 1)ʱ���������жϺ�DMA���� */
        unsigned int  tx_data_merge_en  : 1;  /* bit[8]    : ���ݷ��ͺϲ�ʹ�ܣ�ֻ��I2S ģʽ��������λ��Ϊ16bitʱ��Ч��
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ�
                                                             &#13;��λΪ1ʱ��������������ƴ��һ��32bit������FIFO�н��д洢��������16bit����ռ�ݸ�16λ��������16bit����ռ�ݵ�16λ�������������FIFO�������ʣ����ṩ����ʱ��Ļ���������&#13;����������£�CPU����FIFO��д������ʱ����������˳����������FIFOд��һ��32bit���ݣ�����������16bit�ϲ��ɵ�һ��32bit���ݣ�������������FIFOд��һ��32bit���ݣ���˷����� */
        unsigned int  rx_data_merge_en  : 1;  /* bit[9]    : ���ݽ��պϲ�ʹ�ܣ�ֻ��I2Sģʽ��������λ��Ϊ16bitʱ��Ч��
                                                             0����ʹ�ܣ�
                                                             &#13;1��ʹ�ܡ�
                                                             ��λΪ1ʱ��������������ƴ��һ��32bit������FIFO�н��д洢��������16bit����ռ�ݸ�16λ��������16bit����ռ�ݵ�16λ�������������FIFO�������ʣ����ṩ����ʱ��Ļ���������&#13;CPU�ӽ���FIFO�ж�����ʱ����������˳�򣺴�������FIFO����һ��32bit���ݣ�����������16bit�ϲ��ɵ�һ��32bit���ݣ����ٴ�������FIFO����һ��32bit���ݣ���˷����� */
        unsigned int  tx_fifo_disable   : 1;  /* bit[10]   : ����FIFO��ֹ��
                                                             0��ʹ�ܣ�
                                                             &#13;1����ֹ�� */
        unsigned int  rx_fifo_disable   : 1;  /* bit[11]   : ����FIFO��ֹ��
                                                             0��ʹ�ܣ�
                                                             &#13;1����ֹ�� */
        unsigned int  tx_enable         : 1;  /* bit[12]   : ����ͨ��ʹ�ܡ�
                                                             0����ֹ��
                                                             &#13;1��ʹ�ܡ� */
        unsigned int  rx_enable         : 1;  /* bit[13]   : ����ͨ��ʹ�ܡ�
                                                             0����ֹ��
                                                             &#13;1��ʹ�ܡ� */
        unsigned int  intr_en           : 1;  /* bit[14]   : �ж�ȫ��ʹ�ܡ�
                                                             0����ֹ��
                                                             &#13;1��ʹ�ܡ� */
        unsigned int  rst_n             : 1;  /* bit[15]   : I2S/PCMͨ����λ���͵�ƽ��Ч��
                                                             ����I2S/PCM���պͷ���ģ�飨����FIFO�����и�λ����˷��ͺͽ���FIFO״̬�Ĵ������Ϊ0�������ḴλCPU�ӿڼĴ���ģ�顣 */
        unsigned int  reserved          : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SIO_CT_SET_UNION;
#endif
#define SOC_SIO_CT_SET_tx_fifo_threshold_START  (0)
#define SOC_SIO_CT_SET_tx_fifo_threshold_END    (3)
#define SOC_SIO_CT_SET_rx_fifo_threshold_START  (4)
#define SOC_SIO_CT_SET_rx_fifo_threshold_END    (7)
#define SOC_SIO_CT_SET_tx_data_merge_en_START   (8)
#define SOC_SIO_CT_SET_tx_data_merge_en_END     (8)
#define SOC_SIO_CT_SET_rx_data_merge_en_START   (9)
#define SOC_SIO_CT_SET_rx_data_merge_en_END     (9)
#define SOC_SIO_CT_SET_tx_fifo_disable_START    (10)
#define SOC_SIO_CT_SET_tx_fifo_disable_END      (10)
#define SOC_SIO_CT_SET_rx_fifo_disable_START    (11)
#define SOC_SIO_CT_SET_rx_fifo_disable_END      (11)
#define SOC_SIO_CT_SET_tx_enable_START          (12)
#define SOC_SIO_CT_SET_tx_enable_END            (12)
#define SOC_SIO_CT_SET_rx_enable_START          (13)
#define SOC_SIO_CT_SET_rx_enable_END            (13)
#define SOC_SIO_CT_SET_intr_en_START            (14)
#define SOC_SIO_CT_SET_intr_en_END              (14)
#define SOC_SIO_CT_SET_rst_n_START              (15)
#define SOC_SIO_CT_SET_rst_n_END                (15)


/*****************************************************************************
 �ṹ��    : SOC_SIO_CT_CLR_UNION
 �ṹ˵��  : CT_CLR �Ĵ����ṹ���塣��ַƫ����:0x060����ֵ:0x00008000�����:32
 �Ĵ���˵��: ����Ĵ�����
            Ϊ���ܹ�����Ķ�SIO���ƼĴ�������λ��������SIO�У�ΪSIO���ƼĴ���������2����ַ��0x05C��SIO_CT_SET����0x060��SIO_CT_CLR�������У�
            0x060Ϊ����Ĵ�����ַ������Ĵ�������Ӧλд��1ʱ����Ӧλ�������д0��Ч���üĴ�������Ϊֻд��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_fifo_threshold : 4;  /* bit[0-3]  : ����FIFO��ֵ��
                                                             ��tx_right_depth < (tx_fifo_threshold + 1)ʱ���������жϺ�DMA���� */
        unsigned int  rx_fifo_threshold : 4;  /* bit[4-7]  : ����FIFO��ֵ��
                                                             ��rx_right_depth 3(rx_fifo_threshold + 1)ʱ���������жϺ�DMA���� */
        unsigned int  tx_data_merge_en  : 1;  /* bit[8]    : ���ݷ��ͺϲ�ʹ�ܣ�ֻ��I2S ģʽ��������λ��Ϊ16bitʱ��Ч��
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ�
                                                             &#13;��λΪ1ʱ��������������ƴ��һ��32bit������FIFO�н��д洢��������16bit����ռ�ݸ�16λ��������16bit����ռ�ݵ�16λ�������������FIFO�������ʣ����ṩ����ʱ��Ļ���������&#13;����������£�CPU����FIFO��д������ʱ����������˳����������FIFOд��һ��32bit���ݣ�����������16bit�ϲ��ɵ�һ��32bit���ݣ�������������FIFOд��һ��32bit���ݣ���˷����� */
        unsigned int  rx_data_merge_en  : 1;  /* bit[9]    : ���ݽ��պϲ�ʹ�ܣ�ֻ��I2Sģʽ��������λ��Ϊ16bitʱ��Ч��
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ�
                                                             ��λΪ1ʱ��������������ƴ��һ��32bit������FIFO�н��д洢��������16bit����ռ�ݸ�16λ��������16bit����ռ�ݵ�16λ�������������FIFO�������ʣ����ṩ����ʱ��Ļ���������&#13;CPU�ӽ���FIFO�ж�����ʱ����������˳�򣺴�������FIFO����һ��32bit���ݣ�����������16bit�ϲ��ɵ�һ��32bit���ݣ����ٴ�������FIFO����һ��32bit���ݣ���˷����� */
        unsigned int  tx_fifo_disable   : 1;  /* bit[10]   : ����FIFO��ֹ��
                                                             0��ʹ�ܣ�
                                                             &#13;1����ֹ�� */
        unsigned int  rx_fifo_disable   : 1;  /* bit[11]   : ����FIFO��ֹ��
                                                             0��ʹ�ܣ�
                                                             1����ֹ�� */
        unsigned int  tx_enable         : 1;  /* bit[12]   : ����ͨ��ʹ�ܡ�
                                                             0����ֹ��
                                                             &#13;1��ʹ�ܡ� */
        unsigned int  rx_enable         : 1;  /* bit[13]   : ����ͨ��ʹ�ܡ�
                                                             0����ֹ��
                                                             &#13;1��ʹ�ܡ� */
        unsigned int  intr_en           : 1;  /* bit[14]   : �ж�ȫ��ʹ�ܡ�
                                                             0����ֹ��
                                                             &#13;1��ʹ�ܡ� */
        unsigned int  rst_n             : 1;  /* bit[15]   : I2S/PCMͨ����λ���͵�ƽ��Ч��
                                                             ����I2S/PCM���պͷ���ģ�飨����FIFO�����и�λ����˷��ͺͽ���FIFO״̬�Ĵ������Ϊ0�������ḴλCPU�ӿڼĴ���ģ�顣 */
        unsigned int  reserved          : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_SIO_CT_CLR_UNION;
#endif
#define SOC_SIO_CT_CLR_tx_fifo_threshold_START  (0)
#define SOC_SIO_CT_CLR_tx_fifo_threshold_END    (3)
#define SOC_SIO_CT_CLR_rx_fifo_threshold_START  (4)
#define SOC_SIO_CT_CLR_rx_fifo_threshold_END    (7)
#define SOC_SIO_CT_CLR_tx_data_merge_en_START   (8)
#define SOC_SIO_CT_CLR_tx_data_merge_en_END     (8)
#define SOC_SIO_CT_CLR_rx_data_merge_en_START   (9)
#define SOC_SIO_CT_CLR_rx_data_merge_en_END     (9)
#define SOC_SIO_CT_CLR_tx_fifo_disable_START    (10)
#define SOC_SIO_CT_CLR_tx_fifo_disable_END      (10)
#define SOC_SIO_CT_CLR_rx_fifo_disable_START    (11)
#define SOC_SIO_CT_CLR_rx_fifo_disable_END      (11)
#define SOC_SIO_CT_CLR_tx_enable_START          (12)
#define SOC_SIO_CT_CLR_tx_enable_END            (12)
#define SOC_SIO_CT_CLR_rx_enable_START          (13)
#define SOC_SIO_CT_CLR_rx_enable_END            (13)
#define SOC_SIO_CT_CLR_intr_en_START            (14)
#define SOC_SIO_CT_CLR_intr_en_END              (14)
#define SOC_SIO_CT_CLR_rst_n_START              (15)
#define SOC_SIO_CT_CLR_rst_n_END                (15)


/*****************************************************************************
 �ṹ��    : SOC_SIO_RX_STA_UNION
 �ṹ˵��  : RX_STA �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO����״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_right_depth : 5;  /* bit[0-4]  : I2Sģʽ�£�Ϊ����������FIFO���ָʾ��
                                                          PCMģʽ�£�ΪPCM����FIFO���ָʾ�� */
        unsigned int  rx_left_depth  : 5;  /* bit[5-9]  : ����������FIFO���ָʾ��
                                                          ֻ��I2Sģʽ����Ч�� */
        unsigned int  reserved       : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_SIO_RX_STA_UNION;
#endif
#define SOC_SIO_RX_STA_rx_right_depth_START  (0)
#define SOC_SIO_RX_STA_rx_right_depth_END    (4)
#define SOC_SIO_RX_STA_rx_left_depth_START   (5)
#define SOC_SIO_RX_STA_rx_left_depth_END     (9)


/*****************************************************************************
 �ṹ��    : SOC_SIO_TX_STA_UNION
 �ṹ˵��  : TX_STA �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000000�����:32
 �Ĵ���˵��: SIO����״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_right_depth : 5;  /* bit[0-4]  : I2Sģʽ�£�Ϊ����������FIFO���ָʾ��
                                                          PCMģʽ�£�ΪPCM����FIFO���ָʾ�� */
        unsigned int  tx_left_depth  : 5;  /* bit[5-9]  : ����������FIFO���ָʾ��
                                                          ֻ��I2Sģʽ����Ч�� */
        unsigned int  reserved       : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_SIO_TX_STA_UNION;
#endif
#define SOC_SIO_TX_STA_tx_right_depth_START  (0)
#define SOC_SIO_TX_STA_tx_right_depth_END    (4)
#define SOC_SIO_TX_STA_tx_left_depth_START   (5)
#define SOC_SIO_TX_STA_tx_left_depth_END     (9)


/*****************************************************************************
 �ṹ��    : SOC_SIO_DATA_WIDTH_SET_UNION
 �ṹ˵��  : DATA_WIDTH_SET �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000009�����:32
 �Ĵ���˵��: I2S/PCMģʽ�µ����ݿ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_mode  : 3;  /* bit[0-2] : �������ݳ�������λ��
                                                   ����I2Sģʽ
                                                   000��������
                                                   001��16bit��
                                                   010��18bit��
                                                   011��20bit��
                                                   100��24bit��
                                                   101��32bit��
                                                   110��111��������
                                                   000��8bit
                                                   001��16bit��
                                                   010��32bit��
                                                   011��64bit��
                                                   100��128bit��
                                                   101��111������ */
        unsigned int  rx_mode  : 3;  /* bit[3-5] : �������ݳ�������λ��
                                                   000��8bit��
                                                   &#13;001��16bit��
                                                   010��18bit��
                                                   &#13;011��20bit��
                                                   &#13;100��24bit��
                                                   &#13;101��32bit��
                                                   &#13;110��111��������
                                                   &#13;����I2Sģʽ��֧��16/18/20/24/32 bit��&#13;����PCMģʽ��֧��8/16 bit��
                                                   ���ڶ�·���գ�����ģʽֻ֧��8/16bit�� */
        unsigned int  reserved : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SIO_DATA_WIDTH_SET_UNION;
#endif
#define SOC_SIO_DATA_WIDTH_SET_tx_mode_START   (0)
#define SOC_SIO_DATA_WIDTH_SET_tx_mode_END     (2)
#define SOC_SIO_DATA_WIDTH_SET_rx_mode_START   (3)
#define SOC_SIO_DATA_WIDTH_SET_rx_mode_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_SIO_I2S_START_POS_UNION
 �ṹ˵��  : I2S_START_POS �Ĵ����ṹ���塣��ַƫ����:0x07C����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2S����������ʼλ�����ÿ��ƼĴ�����
            ��I2Sģʽ�£������������ݲ�����ַ�ϲ�ʹ�ܺ󣬿�����ʼ�����Ǵ���������ʼ���Ǵ���������ʼ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_pos_read  : 1;  /* bit[0]   : ������FIFOʱ��
                                                          0������������ʼ���ʣ�
                                                          &#13;1������������ʼ���ʡ� */
        unsigned int  start_pos_write : 1;  /* bit[1]   : д����FIFOʱ��
                                                          0������������ʼ���ʣ�
                                                          &#13;1������������ʼ���ʡ� */
        unsigned int  reserved        : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_SIO_I2S_START_POS_UNION;
#endif
#define SOC_SIO_I2S_START_POS_start_pos_read_START   (0)
#define SOC_SIO_I2S_START_POS_start_pos_read_END     (0)
#define SOC_SIO_I2S_START_POS_start_pos_write_START  (1)
#define SOC_SIO_I2S_START_POS_start_pos_write_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SIO_I2S_POS_FLAG_UNION
 �ṹ˵��  : I2S_POS_FLAG �Ĵ����ṹ���塣��ַƫ����:0x080����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2S��������������ǰλ��״̬�Ĵ�����
            ��I2Sģʽ�£������������ݲ�����ַ�ϲ�ʹ�ܺ�ָʾ��һ�η��ʼĴ����Ǵ���������ʼ���Ǵ���������ʼ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  start_pos_read  : 1;  /* bit[0]   : ������FIFOʱ��
                                                          0����һ�δ���������ʼ���ʣ�
                                                          &#13;1����һ�δ���������ʼ���ʡ� */
        unsigned int  start_pos_write : 1;  /* bit[1]   : д����FIFOʱ��
                                                          0����һ�δ���������ʼ���ʣ�
                                                          &#13;1����һ�δ���������ʼ���ʡ� */
        unsigned int  reserved        : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_SIO_I2S_POS_FLAG_UNION;
#endif
#define SOC_SIO_I2S_POS_FLAG_start_pos_read_START   (0)
#define SOC_SIO_I2S_POS_FLAG_start_pos_read_END     (0)
#define SOC_SIO_I2S_POS_FLAG_start_pos_write_START  (1)
#define SOC_SIO_I2S_POS_FLAG_start_pos_write_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_SIO_SIGNED_EXT_UNION
 �ṹ˵��  : SIGNED_EXT �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��λ���ݷ�����չʹ�ܼĴ������ñ�־ֻ�Խ���������Ч���Է���������Ч��PCMģʽ��I2Sģʽ�½��յ������ݶ�֧�ַ�����չ��
            �ڽ�����Ч����λ��Ϊ8/16/18/20/24 bitʱ������ñ�־ʹ�ܣ��ѽ��յ�������ת��Ϊ32bit����ʱ����32bit���ݵĸ�λ��Ч��������Ϊ�������������Чbit��Ӧ��ֵ��Ȼ����д�����FIFO��
            ��16bitλ��Ϊ����
            if (data_rx[15] == 1 ) 
            data_rx[31:16]=0xffff;
            else
            data_rx[31:16]=0x0000;
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  signed_ext_en : 1;  /* bit[0]   : ��λ���ݷ�����չʹ�ܡ�
                                                        0����ʹ�ܣ�
                                                        &#13;1��ʹ�ܡ� */
        unsigned int  reserved      : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SIO_SIGNED_EXT_UNION;
#endif
#define SOC_SIO_SIGNED_EXT_signed_ext_en_START  (0)
#define SOC_SIO_SIGNED_EXT_signed_ext_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SIO_I2S_POS_MERGE_EN_UNION
 �ṹ˵��  : I2S_POS_MERGE_EN �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x00000000�����:32
 �Ĵ���˵��: I2Sģʽ�����������ݲ�����ַ�ϲ�ʹ�ܼĴ�����
            ��I2Sģʽ�£���DMA��ʽ��дSIO��FIFO����ʱ����Ϊ�����������ݵ�ַ��ͬ����ҪCPU��������DMA�����ĵ�ַ������CPUЧ�ʵ͡�Ϊ�����CPU��Ч�ʣ��ṩ�����������ݵĶ�д��ͳһ��ַʹ�ܿ��ơ�
            ʹ������£���������������ͳһʹ��SIO_I2S_DUAL_RX_CHN�Ĵ�����д������������ͳһʹ��SIO_I2S_DUAL_TX_CHN�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  merge_en : 1;  /* bit[0]   : ��I2Sģʽ�£��������������ݵĲ�����ַ�ϲ�ʹ�ܡ�
                                                   0����ʹ�ܣ�
                                                   &#13;1��ʹ�ܡ� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_SIO_I2S_POS_MERGE_EN_UNION;
#endif
#define SOC_SIO_I2S_POS_MERGE_EN_merge_en_START  (0)
#define SOC_SIO_I2S_POS_MERGE_EN_merge_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_SIO_INTMASK_UNION
 �ṹ˵��  : INTMASK �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_intr             : 1;  /* bit[0]   : ����FIFO������ֵ�ж����Ρ�
                                                              0�������θ��жϣ�
                                                              1�����θ��жϡ� */
        unsigned int  tx_intr             : 1;  /* bit[1]   : ����FIFO������ֵ�ж����Ρ�
                                                              0�������θ��жϣ�
                                                              1�����θ��жϡ�  */
        unsigned int  rx_right_fifo_over  : 1;  /* bit[2]   : I2Sģʽ�£�����������FIFO�����ж����Ρ�PCMģʽ�£�PCM����FIFO�����ж����Ρ�
                                                              0�������θ��жϣ�
                                                              &#13;1�����θ��жϡ� */
        unsigned int  rx_left_fifo_over   : 1;  /* bit[3]   : I2Sģʽ�£�����������FIFO�����ж����Ρ�PCMģʽ����Ч��
                                                              0�������θ��жϣ�
                                                              &#13;1�����θ��жϡ� */
        unsigned int  tx_right_fifo_under : 1;  /* bit[4]   : I2Sģʽ�£�����������FIFO�����ж����Ρ�PCMģʽ�£�PCM����FIFO�����ж����Ρ�
                                                              0�������θ��жϣ�
                                                              &#13;1�����θ��жϡ� */
        unsigned int  tx_left_fifo_under  : 1;  /* bit[5]   : I2Sģʽ�£�����������FIFO�����ж����Ρ�PCMģʽ����Ч��
                                                              0�������θ��жϣ�
                                                              &#13;1�����θ��жϡ� */
        unsigned int  reserved            : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_SIO_INTMASK_UNION;
#endif
#define SOC_SIO_INTMASK_rx_intr_START              (0)
#define SOC_SIO_INTMASK_rx_intr_END                (0)
#define SOC_SIO_INTMASK_tx_intr_START              (1)
#define SOC_SIO_INTMASK_tx_intr_END                (1)
#define SOC_SIO_INTMASK_rx_right_fifo_over_START   (2)
#define SOC_SIO_INTMASK_rx_right_fifo_over_END     (2)
#define SOC_SIO_INTMASK_rx_left_fifo_over_START    (3)
#define SOC_SIO_INTMASK_rx_left_fifo_over_END      (3)
#define SOC_SIO_INTMASK_tx_right_fifo_under_START  (4)
#define SOC_SIO_INTMASK_tx_right_fifo_under_END    (4)
#define SOC_SIO_INTMASK_tx_left_fifo_under_START   (5)
#define SOC_SIO_INTMASK_tx_left_fifo_under_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_SIO_I2S_DUAL_RX_CHN_UNION
 �ṹ˵��  : I2S_DUAL_RX_CHN �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ȡ�������ݼĴ�����I2S��������������ַ�ϲ�ʹ�ܺ󣬶�ȡ�������ݡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rx_data : 32; /* bit[0-31]: ���յ������ݡ� */
    } reg;
} SOC_SIO_I2S_DUAL_RX_CHN_UNION;
#endif
#define SOC_SIO_I2S_DUAL_RX_CHN_rx_data_START  (0)
#define SOC_SIO_I2S_DUAL_RX_CHN_rx_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_SIO_I2S_DUAL_TX_CHN_UNION
 �ṹ˵��  : I2S_DUAL_TX_CHN �Ĵ����ṹ���塣��ַƫ����:0x0C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: д�������ݼĴ�����I2S��������������ַ�ϲ�ʹ�ܺ�д�������ݡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  tx_data : 32; /* bit[0-31]: ���͵����ݡ� */
    } reg;
} SOC_SIO_I2S_DUAL_TX_CHN_UNION;
#endif
#define SOC_SIO_I2S_DUAL_TX_CHN_tx_data_START  (0)
#define SOC_SIO_I2S_DUAL_TX_CHN_tx_data_END    (31)






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

#endif /* end of soc_sio_interface.h */
