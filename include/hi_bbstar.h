/******************************************************************************/
/*  Copyright (C), 2007-2014, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_bbstar.h */
/* Version       : 2.0 */
/* Created       : 2014-05-09*/
/* Last Modified : */
/* Description   :  The C union definition file for the module bbstar*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/

#ifndef __HI_BBSTAR_H__
#define __HI_BBSTAR_H__

/*
 * Project: hi
 * Module : bbstar
 */

/********************************************************************************/
/*    bbstar �Ĵ���ƫ�ƶ��壨��Ŀ��_ģ����_�Ĵ�����_OFFSET)        */
/********************************************************************************/
#define    HI6559_STATUS1_OFFSET                                 (0x1) /* ״̬��־1�Ĵ����� */
#define    HI6559_STATUS2_OFFSET                                 (0x2) /* ״̬��־2�Ĵ����� */
#define    HI6559_IRQ1_OFFSET                                    (0x3) /* �ж�1�Ĵ����� */
#define    HI6559_IRQ2_OFFSET                                    (0x4) /* �ж�2�Ĵ����� */
#define    HI6559_IRQ3_OFFSET                                    (0x5) /* �ж�3�Ĵ����� */
#define    HI6559_IRQ4_OFFSET                                    (0x6) /* �ж�4�Ĵ����� */
#define    HI6559_IRQ1_MASK_OFFSET                               (0x8) /* �ж�����1�Ĵ����� */
#define    HI6559_IRQ2_MASK_OFFSET                               (0x9) /* �ж�����2�Ĵ����� */
#define    HI6559_IRQ3_MASK_OFFSET                               (0xA) /* �ж�����3�Ĵ����� */
#define    HI6559_IRQ4_MASK_OFFSET                               (0xB) /* �ж�����4�Ĵ����� */
#define    HI6559_SCP_RECORD1_OFFSET                             (0xD) /* ��·������¼1�Ĵ����� */
#define    HI6559_OCP_RECORD1_OFFSET                             (0xE) /* ����������¼1�Ĵ����� */
#define    HI6559_OCP_RECORD2_OFFSET                             (0xF) /* ����������¼2�Ĵ����� */
#define    HI6559_OCP_RECORD3_OFFSET                             (0x10) /* ����������¼3�Ĵ����� */
#define    HI6559_OCP_RECORD4_OFFSET                             (0x11) /* ����������¼4�Ĵ����� */
#define    HI6559_OCP_RECORD5_OFFSET                             (0x12) /* ����������¼5�Ĵ����� */
#define    HI6559_OCP_RECORD6_OFFSET                             (0x13) /* ����������¼6�Ĵ����� */
#define    HI6559_NP_IRQ1_RECORD_OFFSET                          (0x15) /* �ж�1���µ��¼�Ĵ����� */
#define    HI6559_NP_IRQ2_RECORD_OFFSET                          (0x16) /* �ж�2���µ��¼�Ĵ����� */
#define    HI6559_NP_IRQ3_RECORD_OFFSET                          (0x17) /* �ж�3���µ��¼�Ĵ����� */
#define    HI6559_NP_SCP_RECORD1_OFFSET                          (0x18) /* ��·�������µ��¼1�Ĵ����� */
#define    HI6559_NP_OCP_RECORD1_OFFSET                          (0x19) /* �����������µ��¼1�Ĵ����� */
#define    HI6559_NP_OCP_RECORD2_OFFSET                          (0x1A) /* �����������µ��¼2�Ĵ����� */
#define    HI6559_NP_OCP_RECORD3_OFFSET                          (0x1B) /* �����������µ��¼3�Ĵ����� */
#define    HI6559_NP_OCP_RECORD4_OFFSET                          (0x1C) /* �����������µ��¼4�Ĵ����� */
#define    HI6559_NP_OCP_RECORD5_OFFSET                          (0x1D) /* �����������µ��¼5�Ĵ����� */
#define    HI6559_NP_OCP_RECORD6_OFFSET                          (0x1E) /* �����������µ��¼6�Ĵ����� */
#define    HI6559_OCP_DEB_OFFSET                                 (0x20) /* OCPȥ�������ڼĴ����� */
#define    HI6559_ONOFF8_OFFSET                                  (0x21) /* ���ؿ���8�Ĵ����� */
#define    HI6559_OCP_SCP_MOD_CTRL1_OFFSET                       (0x22) /* BUCK0-3�����Ͷ�·����ģʽ���ƼĴ����� */
#define    HI6559_OCP_SCP_MOD_CTRL2_OFFSET                       (0x23) /* BUCK4-7�����Ͷ�·����ģʽ���ƼĴ����� */
#define    HI6559_OCP_MOD_CTRL3_OFFSET                           (0x24) /* LDO1-4��������ģʽ���ƼĴ����� */
#define    HI6559_OCP_MOD_CTRL4_OFFSET                           (0x25) /* LDO5-8��������ģʽ���ƼĴ����� */
#define    HI6559_OCP_MOD_CTRL5_OFFSET                           (0x26) /* LDO9-12��������ģʽ���ƼĴ����� */
#define    HI6559_OCP_MOD_CTRL6_OFFSET                           (0x27) /* LDO13-16��������ģʽ���ƼĴ����� */
#define    HI6559_OCP_MOD_CTRL7_OFFSET                           (0x29) /* LDO21-ldo23��������ģʽ���ƼĴ����� */
#define    HI6559_OCP_MOD_CTRL8_OFFSET                           (0x2B) /* LVS7-9��������ģʽ���ƼĴ����� */
#define    HI6559_ENABLE1_OFFSET                                 (0x2D) /* ��Դģ��ʹ��1�Ĵ����� */
#define    HI6559_DISABLE1_OFFSET                                (0x2E) /* ��Դģ��ر�1�Ĵ����� */
#define    HI6559_ONOFF_STATUS1_OFFSET                           (0x2F) /* ��Դģ�鿪��״̬1�Ĵ����� */
#define    HI6559_ENABLE2_OFFSET                                 (0x30) /* ��Դģ��ʹ��2�Ĵ����� */
#define    HI6559_DISABLE2_OFFSET                                (0x31) /* ��Դģ��ر�2�Ĵ����� */
#define    HI6559_ONOFF_STATUS2_OFFSET                           (0x32) /* ��Դģ�鿪��״̬2�Ĵ����� */
#define    HI6559_ENABLE3_OFFSET                                 (0x33) /* ��Դģ��ʹ��3�Ĵ����� */
#define    HI6559_DISABLE3_OFFSET                                (0x34) /* ��Դģ��ر�3�Ĵ����� */
#define    HI6559_ONOFF_STATUS3_OFFSET                           (0x35) /* ��Դģ�鿪��״̬3�Ĵ����� */
#define    HI6559_ENABLE4_OFFSET                                 (0x36) /* ��Դģ��ʹ��4�Ĵ����� */
#define    HI6559_DISABLE4_OFFSET                                (0x37) /* ��Դģ��ر�4�Ĵ����� */
#define    HI6559_ONOFF_STATUS4_OFFSET                           (0x38) /* ��Դģ�鿪��״̬4�Ĵ����� */
#define    HI6559_ENABLE5_OFFSET                                 (0x39) /* ��Դģ��ʹ��5�Ĵ����� */
#define    HI6559_DISABLE5_OFFSET                                (0x3A) /* ��Դģ��ر�5�Ĵ����� */
#define    HI6559_ONOFF_STATUS5_OFFSET                           (0x3B) /* ��Դģ�鿪��״̬5�Ĵ����� */
#define    HI6559_SIM_LDO9_LDO11_EN_OFFSET                       (0x40) /* SIM��/LDO9/LDO11ʹ�ܼĴ����� */
#define    HI6559_SIM_CFG_OFFSET                                 (0x41) /* SIM�����üĴ����� */
#define    HI6559_SIM_DEB_OFFSET                                 (0x43) /* SIM���ж�ȥ���ĵ��ڼĴ����� */
#define    HI6559_ECO_MOD_CFG1_OFFSET                            (0x44) /* ��Դģ���Ƿ����PMU����ECOģʽ����1�Ĵ����� */
#define    HI6559_ECO_MOD_CFG2_OFFSET                            (0x45) /* ��Դģ���Ƿ����PMU����ECOģʽ����2�Ĵ����� */
#define    HI6559_ECO_MOD_CFG3_OFFSET                            (0x46) /* ��Դ�Ƿ�ǿ����PMU����ECOģʽ����3�Ĵ����� */
#define    HI6559_ECO_MOD_CFG4_OFFSET                            (0x47) /* ��Դ�Ƿ�ǿ����PMU����ECOģʽ����4�Ĵ����� */
#define    HI6559_ENB3_ECO_MARK_OFFSET                           (0x48) /* ��ENB3Ӳ�ߺ�ECO������ص������źżĴ����� */
#define    HI6559_BUCK0_REG1_ADJ_OFFSET                          (0x4A) /* BUCK0����1�Ĵ����� */
#define    HI6559_BUCK0_REG2_ADJ_OFFSET                          (0x52) /* BUCK0����2�Ĵ����� */
#define    HI6559_BUCK0_REG3_ADJ_OFFSET                          (0x56) /* BUCK0����3�Ĵ����� */
#define    HI6559_BUCK0_REG4_ADJ_OFFSET                          (0x57) /* BUCK0����4�Ĵ����� */
#define    HI6559_BUCK0_REG5_ADJ_OFFSET                          (0x58) /* BUCK0����5�Ĵ����� */
#define    HI6559_BUCK0_REG6_ADJ_OFFSET                          (0x59) /* BUCK0����6�Ĵ����� */
#define    HI6559_BUCK0_REG7_ADJ_OFFSET                          (0x5A) /* BUCK0����7�Ĵ����� */
#define    HI6559_BUCK0_REG8_ADJ_OFFSET                          (0x5C) /* BUCK0����8�Ĵ����� */
#define    HI6559_BUCK0_REG9_ADJ_OFFSET                          (0x5D) /* BUCK0����9�Ĵ����� */
#define    HI6559_BUCK0_REG10_ADJ_OFFSET                         (0x5E) /* BUCK0����10�Ĵ����� */
#define    HI6559_BUCK0_REG11_ADJ_OFFSET                         (0x5F) /* BUCK0����11�Ĵ����� */
#define    HI6559_BUCK0_REG12_ADJ_OFFSET                         (0x60) /* BUCK0����12�Ĵ����� */
#define    HI6559_BUCK0_REG13_ADJ_OFFSET                         (0x61) /* BUCK0����13�Ĵ����� */
#define    HI6559_BUCK0_REG14_ADJ_OFFSET                         (0x62) /* BUCK0����14�Ĵ����� */
#define    HI6559_BUCK0_REG15_ADJ_OFFSET                         (0x63) /* BUCK0����15�Ĵ����� */
#define    HI6559_BUCK0_REG16_ADJ_OFFSET                         (0x65) /* BUCK0����16�Ĵ����� */
#define    HI6559_BUCK3_REG1_ADJ_OFFSET                          (0x66) /* BUCK3����1�Ĵ����� */
#define    HI6559_BUCK3_REG2_ADJ_OFFSET                          (0x67) /* BUCK3����2�Ĵ����� */
#define    HI6559_BUCK3_REG3_ADJ_OFFSET                          (0x68) /* BUCK3����3�Ĵ����� */
#define    HI6559_BUCK3_REG4_ADJ_OFFSET                          (0x69) /* BUCK3����4�Ĵ����� */
#define    HI6559_BUCK3_REG5_ADJ_OFFSET                          (0x6A) /* BUCK3����5�Ĵ����� */
#define    HI6559_BUCK3_REG6_ADJ_OFFSET                          (0x6B) /* BUCK3����6�Ĵ����� */
#define    HI6559_BUCK3_REG7_ADJ_OFFSET                          (0x6C) /* BUCK3����7�Ĵ����� */
#define    HI6559_BUCK3_REG8_ADJ_OFFSET                          (0x6D) /* BUCK3����8�Ĵ����� */
#define    HI6559_BUCK3_REG9_ADJ_OFFSET                          (0x6E) /* BUCK3����9�Ĵ����� */
#define    HI6559_BUCK3_REG10_ADJ_OFFSET                         (0x6F) /* BUCK3����10�Ĵ����� */
#define    HI6559_BUCK5_REG0_ADJ_OFFSET                          (0x71) /* BUCK3����12�Ĵ����� */
#define    HI6559_BUCK4_REG1_ADJ_OFFSET                          (0x72) /* BUCK4����1�Ĵ����� */
#define    HI6559_BUCK4_REG2_ADJ_OFFSET                          (0x73) /* BUCK4����2�Ĵ����� */
#define    HI6559_BUCK4_REG3_ADJ_OFFSET                          (0x74) /* BUCK4����3�Ĵ����� */
#define    HI6559_BUCK4_REG4_ADJ_OFFSET                          (0x75) /* BUCK4����4�Ĵ����� */
#define    HI6559_BUCK4_REG5_ADJ_OFFSET                          (0x76) /* BUCK4����5�Ĵ����� */
#define    HI6559_BUCK4_REG6_ADJ_OFFSET                          (0x77) /* BUCK4����6�Ĵ����� */
#define    HI6559_BUCK4_REG7_ADJ_OFFSET                          (0x78) /* BUCK4����7�Ĵ����� */
#define    HI6559_BUCK4_REG8_ADJ_OFFSET                          (0x79) /* BUCK4����8�Ĵ����� */
#define    HI6559_BUCK4_REG9_ADJ_OFFSET                          (0x7A) /* BUCK4����9�Ĵ����� */
#define    HI6559_BUCK4_REG10_ADJ_OFFSET                         (0x7B) /* BUCK4����10�Ĵ����� */
#define    HI6559_BUCK4_REG12_ADJ_OFFSET                         (0x7C) /* BUCK4����12�Ĵ����� */
#define    HI6559_BUCK5_REG1_ADJ_OFFSET                          (0x7D) /* BUCK5����1�Ĵ����� */
#define    HI6559_BUCK5_REG2_ADJ_OFFSET                          (0x7E) /* BUCK5����2�Ĵ����� */
#define    HI6559_BUCK5_REG3_ADJ_OFFSET                          (0x7F) /* BUCK5����3�Ĵ����� */
#define    HI6559_BUCK5_REG4_ADJ_OFFSET                          (0x80) /* BUCK5����4�Ĵ����� */
#define    HI6559_BUCK5_REG5_ADJ_OFFSET                          (0x81) /* BUCK5����5�Ĵ����� */
#define    HI6559_BUCK5_REG6_ADJ_OFFSET                          (0x83) /* BUCK5����6�Ĵ����� */
#define    HI6559_BUCK5_REG7_ADJ_OFFSET                          (0x84) /* BUCK5����7�Ĵ����� */
#define    HI6559_BUCK5_REG8_ADJ_OFFSET                          (0x85) /* BUCK5����8�Ĵ����� */
#define    HI6559_BUCK5_REG9_ADJ_OFFSET                          (0x87) /* BUCK5����9�Ĵ����� */
#define    HI6559_BUCK5_REG10_ADJ_OFFSET                         (0x88) /* BUCK5����10�Ĵ����� */
#define    HI6559_BUCK6_REG1_ADJ_OFFSET                          (0x8A) /* BUCK6����1�Ĵ����� */
#define    HI6559_BUCK6_REG2_ADJ_OFFSET                          (0x8B) /* BUCK6����2�Ĵ����� */
#define    HI6559_BUCK6_REG3_ADJ_OFFSET                          (0x8C) /* BUCK6����3�Ĵ����� */
#define    HI6559_BUCK6_REG4_ADJ_OFFSET                          (0x8D) /* BUCK6����4�Ĵ����� */
#define    HI6559_BUCK6_REG5_ADJ_OFFSET                          (0x8E) /* BUCK6����5�Ĵ����� */
#define    HI6559_BUCK6_REG6_ADJ_OFFSET                          (0x8F) /* BUCK6����6�Ĵ����� */
#define    HI6559_BUCK6_REG7_ADJ_OFFSET                          (0x90) /* BUCK6����7�Ĵ����� */
#define    HI6559_BUCK6_REG8_ADJ_OFFSET                          (0x91) /* BUCK6����8�Ĵ����� */
#define    HI6559_BUCK6_REG9_ADJ_OFFSET                          (0x92) /* BUCK6����9�Ĵ����� */
#define    HI6559_BUCK6_REG10_ADJ_OFFSET                         (0x93) /* BUCK6����10�Ĵ����� */
#define    HI6559_BUCK6_REG12_ADJ_OFFSET                         (0x95) /* BUCK6����12�Ĵ����� */
#define    HI6559_VSET_BUCK0_ADJ_OFFSET                          (0x98) /* BUCK0��ѹ���ڼĴ����� */
#define    HI6559_VSET_BUCK3_ADJ_OFFSET                          (0x99) /* BUCK3��ѹ���ڼĴ����� */
#define    HI6559_VSET_BUCK4_ADJ_OFFSET                          (0x9A) /* BUCK4��ѹ���ڼĴ����� */
#define    HI6559_VSET_BUCK5_ADJ_OFFSET                          (0x9B) /* BUCK5��ѹ���ڼĴ����� */
#define    HI6559_VSET_BUCK6_ADJ_OFFSET                          (0x9C) /* BUCK6��ѹ���ڼĴ����� */
#define    HI6559_LDO1_REG_ADJ_OFFSET                            (0x9D) /* LDO1���ڼĴ����� */
#define    HI6559_LDO3_REG_ADJ_OFFSET                            (0x9F) /* LDO3���ڼĴ����� */
#define    HI6559_LDO6_REG_ADJ_OFFSET                            (0xA2) /* LDO6���ڼĴ����� */
#define    HI6559_LDO7_REG_ADJ_OFFSET                            (0xA3) /* LDO7���ڼĴ����� */
#define    HI6559_LDO8_REG_ADJ_OFFSET                            (0xA4) /* LDO8���ڼĴ����� */
#define    HI6559_LDO9_REG_ADJ_OFFSET                            (0xA5) /* LDO9���ڼĴ����� */
#define    HI6559_LDO10_REG_ADJ_OFFSET                           (0xA6) /* LDO10���ڼĴ����� */
#define    HI6559_LDO11_REG_ADJ_OFFSET                           (0xA7) /* LDO11���ڼĴ����� */
#define    HI6559_LDO12_REG_ADJ_OFFSET                           (0xA8) /* LDO12���ڼĴ����� */
#define    HI6559_LDO13_REG_ADJ_OFFSET                           (0xA9) /* LDO13���ڼĴ����� */
#define    HI6559_LDO14_REG_ADJ_OFFSET                           (0xAA) /* LDO14���ڼĴ����� */
#define    HI6559_LDO22_REG_ADJ_OFFSET                           (0xB2) /* LDO22���ڼĴ����� */
#define    HI6559_LDO23_REG_ADJ_OFFSET                           (0xB3) /* LDO23���ڼĴ����� */
#define    HI6559_LDO24_REG_ADJ_OFFSET                           (0xB4) /* LDO24���ڼĴ����� */
#define    HI6559_PMUA_REG_ADJ_OFFSET                            (0xB5) /* PMUA���ڼĴ����� */
#define    HI6559_LVS_ADJ1_OFFSET                                (0xB7) /* LVS����1�Ĵ����� */
#define    HI6559_BANDGAP_THSD_ADJ1_OFFSET                       (0xC8) /* BANDGAP��THSD����1�Ĵ����� */
#define    HI6559_BANDGAP_THSD_ADJ2_OFFSET                       (0xC9) /* BANDGAP��THSD����2�Ĵ����� */
#define    HI6559_DR_FLA_CTRL1_OFFSET                            (0xCA) /* DR��˸ģʽ����1�Ĵ����� */
#define    HI6559_DR_FLA_CTRL2_OFFSET                            (0xCB) /* DR��˸ģʽ����2�Ĵ����� */
#define    HI6559_FLASH_PERIOD_OFFSET                            (0xCC) /* DR��˸ģʽ���ڵ��ڼĴ����� */
#define    HI6559_FLASH_ON_OFFSET                                (0xCD) /* DR��˸ģʽ����ʱ����ڼĴ����� */
#define    HI6559_DR_MODE_SEL_OFFSET                             (0xCE) /* DR��ģʽѡ��Ĵ����� */
#define    HI6559_DR_BRE_CTRL_OFFSET                             (0xCF) /* DR1/2����ģʽ���ƼĴ����� */
#define    HI6559_DR1_TIM_CONF0_OFFSET                           (0xD0) /* DR1��������ʱ�����üĴ����� */
#define    HI6559_DR1_TIM_CONF1_OFFSET                           (0xD1) /* DR1��������ʱ�����üĴ����� */
#define    HI6559_DR1_ISET_OFFSET                                (0xD2) /* DR1����ѡ��Ĵ����� */
#define    HI6559_DR2_TIM_CONF0_OFFSET                           (0xD3) /* DR2��������ʱ�����üĴ����� */
#define    HI6559_DR2_TIM_CONF1_OFFSET                           (0xD4) /* DR2��������ʱ�����üĴ����� */
#define    HI6559_DR2_ISET_OFFSET                                (0xD5) /* DR2����ѡ��Ĵ����� */
#define    HI6559_DR_LED_CTRL_OFFSET                             (0xD6) /* DR3/4/5���ƼĴ����� */
#define    HI6559_DR_OUT_CTRL_OFFSET                             (0xD7) /* DR3/4/5������ƼĴ����� */
#define    HI6559_DR3_ISET_OFFSET                                (0xD8) /* DR3����ѡ��Ĵ����� */
#define    HI6559_DR3_START_DEL_OFFSET                           (0xD9) /* DR3������ʱ���üĴ����� */
#define    HI6559_DR3_TIM_CONF0_OFFSET                           (0xDA) /* DR3��������ʱ�����üĴ����� */
#define    HI6559_DR3_TIM_CONF1_OFFSET                           (0xDB) /* DR3��������ʱ�����üĴ����� */
#define    HI6559_DR4_ISET_OFFSET                                (0xDC) /* DR4����ѡ��Ĵ����� */
#define    HI6559_DR4_START_DEL_OFFSET                           (0xDD) /* DR4������ʱ���üĴ��� */
#define    HI6559_DR4_TIM_CONF0_OFFSET                           (0xDE) /* DR4��������ʱ�����üĴ����� */
#define    HI6559_DR4_TIM_CONF1_OFFSET                           (0xDF) /* DR4��������ʱ�����üĴ����� */
#define    HI6559_DR5_ISET_OFFSET                                (0xE0) /* DR5����ѡ��Ĵ����� */
#define    HI6559_DR5_START_DEL_OFFSET                           (0xE1) /* DR5������ʱ���üĴ����� */
#define    HI6559_DR5_TIM_CONF0_OFFSET                           (0xE2) /* DR5��������ʱ�����üĴ����� */
#define    HI6559_DR5_TIM_CONF1_OFFSET                           (0xE3) /* DR5��������ʱ�����üĴ����� */
#define    HI6559_OTP_CTRL1_OFFSET                               (0xE4) /* OTP����1�źżĴ����� */
#define    HI6559_OTP_CTRL2_OFFSET                               (0xE5) /* OTP����2�źżĴ����� */
#define    HI6559_OTP_PDIN_OFFSET                                (0xE6) /* OTPд��ֵ�Ĵ����� */
#define    HI6559_OTP_PDOB0_OFFSET                               (0xE7) /* OTP����ֵ0�Ĵ����� */
#define    HI6559_OTP_PDOB1_OFFSET                               (0xE8) /* OTP����ֵ1�Ĵ����� */
#define    HI6559_OTP_PDOB2_OFFSET                               (0xE9) /* OTP����ֵ2�Ĵ����� */
#define    HI6559_OTP_PDOB3_OFFSET                               (0xEA) /* OTP����ֵ3�Ĵ����� */
#define    HI6559_RTCCR_A0_OFFSET                                (0xEB) /* RTC_A����0�Ĵ����� */
#define    HI6559_RTCCR_A1_OFFSET                                (0xEC) /* RTC_A����1�Ĵ����� */
#define    HI6559_RTCCR_A2_OFFSET                                (0xED) /* RTC_A����2�Ĵ����� */
#define    HI6559_RTCCR_A3_OFFSET                                (0xEE) /* RTC_A����3�Ĵ����� */
#define    HI6559_RTCLR_A0_OFFSET                                (0xEF) /* RTCLR_A����0�Ĵ����� */
#define    HI6559_RTCLR_A1_OFFSET                                (0xF0) /* RTCLR_A����1�Ĵ����� */
#define    HI6559_RTCLR_A2_OFFSET                                (0xF1) /* RTCLR_A����2�Ĵ����� */
#define    HI6559_RTCLR_A3_OFFSET                                (0xF2) /* RTCLR_A����3�Ĵ����� */
#define    HI6559_RTCCTRL_A_OFFSET                               (0xF3) /* RTCCTRL_A���ƼĴ����� */
#define    HI6559_RTCMR_A_A0_OFFSET                              (0xF4) /* RTC_A_A�Ƚ�0�Ĵ����� */
#define    HI6559_RTCMR_A_A1_OFFSET                              (0xF5) /* RTC_A_A�Ƚ�1�Ĵ����� */
#define    HI6559_RTCMR_A_A2_OFFSET                              (0xF6) /* RTC_A_A�Ƚ�2�Ĵ����� */
#define    HI6559_RTCMR_A_A3_OFFSET                              (0xF7) /* RTC_A_A�Ƚ�3�Ĵ����� */
#define    HI6559_RTCMR_A_B0_OFFSET                              (0xF8) /* RTC_A_B�Ƚ�0�Ĵ����� */
#define    HI6559_RTCMR_A_B1_OFFSET                              (0xF9) /* RTC_A_B�Ƚ�1�Ĵ����� */
#define    HI6559_RTCMR_A_B2_OFFSET                              (0xFA) /* RTC_A_B�Ƚ�2�Ĵ����� */
#define    HI6559_RTCMR_A_B3_OFFSET                              (0xFB) /* RTC_A_B�Ƚ�3�Ĵ����� */
#define    HI6559_RTCMR_A_C0_OFFSET                              (0xFC) /* RTC_A_C�Ƚ�0�Ĵ����� */
#define    HI6559_RTCMR_A_C1_OFFSET                              (0xFD) /* RTC_A_C�Ƚ�1�Ĵ����� */
#define    HI6559_RTCMR_A_C2_OFFSET                              (0xFE) /* RTC_A_C�Ƚ�2�Ĵ����� */
#define    HI6559_RTCMR_A_C3_OFFSET                              (0xFF) /* RTC_A_C�Ƚ�3�Ĵ����� */
#define    HI6559_RTCMR_A_D0_OFFSET                              (0x100) /* RTC_A_D�Ƚ�0�Ĵ����� */
#define    HI6559_RTCMR_A_D1_OFFSET                              (0x101) /* RTC_A_D�Ƚ�1�Ĵ����� */
#define    HI6559_RTCMR_A_D2_OFFSET                              (0x102) /* RTC_A_D�Ƚ�2�Ĵ����� */
#define    HI6559_RTCMR_A_D3_OFFSET                              (0x103) /* RTC_A_D�Ƚ�3�Ĵ����� */
#define    HI6559_RTCMR_A_E0_OFFSET                              (0x104) /* RTC_A_E�Ƚ�0�Ĵ����� */
#define    HI6559_RTCMR_A_E1_OFFSET                              (0x105) /* RTC_A_E�Ƚ�1�Ĵ����� */
#define    HI6559_RTCMR_A_E2_OFFSET                              (0x106) /* RTC_A_E�Ƚ�2�Ĵ����� */
#define    HI6559_RTCMR_A_E3_OFFSET                              (0x107) /* RTC_A_E�Ƚ�3�Ĵ����� */
#define    HI6559_RTCMR_A_F0_OFFSET                              (0x108) /* RTC_A_F�Ƚ�0�Ĵ����� */
#define    HI6559_RTCMR_A_F1_OFFSET                              (0x109) /* RTC_A_F�Ƚ�1�Ĵ����� */
#define    HI6559_RTCMR_A_F2_OFFSET                              (0x10A) /* RTC_A_F�Ƚ�2�Ĵ����� */
#define    HI6559_RTCMR_A_F3_OFFSET                              (0x10B) /* RTC_A_F�Ƚ�3�Ĵ����� */
#define    HI6559_RTCCR_NA0_OFFSET                               (0x10C) /* RTC_NA����0�Ĵ����� */
#define    HI6559_RTCCR_NA1_OFFSET                               (0x10D) /* RTC_NA����1�Ĵ����� */
#define    HI6559_RTCCR_NA2_OFFSET                               (0x10E) /* RTC_NA����2�Ĵ����� */
#define    HI6559_RTCCR_NA3_OFFSET                               (0x10F) /* RTC_NA����3�Ĵ����� */
#define    HI6559_RTCLR_NA0_OFFSET                               (0x110) /* RTCLR_NA����0�Ĵ����� */
#define    HI6559_RTCLR_NA1_OFFSET                               (0x111) /* RTCLR_NA����1�Ĵ����� */
#define    HI6559_RTCLR_NA2_OFFSET                               (0x112) /* RTCLR_NA����2�Ĵ����� */
#define    HI6559_RTCLR_NA3_OFFSET                               (0x113) /* RTCLR_NA����3�Ĵ����� */
#define    HI6559_RTCCTRL_NA_OFFSET                              (0x114) /* RTCCTRL_NA���ƼĴ����� */
#define    HI6559_VERSION_OFFSET                                 (0x115) /* �汾�Ĵ����� */
#define    HI6559_RESERVED0_OFFSET                               (0x116) /* ����0�Ĵ����� */
#define    HI6559_RESERVED1_OFFSET                               (0x117) /* ����1�Ĵ����� */
#define    HI6559_RESERVED2_OFFSET                               (0x118) /* ����2�Ĵ����� */
#define    HI6559_RESERVED3_OFFSET                               (0x119) /* ����3�Ĵ����� */
#define    HI6559_RESERVED4_OFFSET                               (0x11A) /* ����4�Ĵ����� */
#define    HI6559_HTOL_MODE_OFFSET                               (0x11B) /* �ϻ�����ģʽ���üĴ����� */
#define    HI6559_DAC_CTRL_OFFSET                                (0x11C) /* DAC���ƼĴ��� */
#define    HI6559_NP_REG_ADJ_OFFSET                              (0x11E) /* ���µ���ڼĴ����� */
#define    HI6559_NP_REG_CHG_OFFSET                              (0x11F) /* ���õ�ط��µ���ڼĴ����� */
#define    HI6559_NP_RSVED1_OFFSET                               (0x120) /* ���µ籣��1�Ĵ����� */
#define    HI6559_NP_RSVED2_OFFSET                               (0x121) /* ���µ籣��2�Ĵ����� */
#define    HI6559_NP_RSVED3_OFFSET                               (0x122) /* ���µ籣��3�Ĵ����� */
#define    HI6559_NP_RSVED4_OFFSET                               (0x123) /* ���µ籣��4�Ĵ����� */
#define    HI6559_RTC_ADJ1_OFFSET                                (0x124) /* rtc_adj[7:0]�Ĵ����� */
#define    HI6559_RTC_ADJ2_OFFSET                                (0x125) /* rtc_adj[15:8]�Ĵ����� */

/********************************************************************************/
/*    bbstar �Ĵ������壨��Ŀ��_ģ����_�Ĵ�����_T)        */
/********************************************************************************/
typedef union
{
    struct
    {
        unsigned int    otmp_d1r                   : 1; /* [0..0] 0�� ��ǰ�¶ȵ����趨��ֵ��Ĭ��125�棩��1�� ��ǰ�¶ȸ����趨��ֵ�� */
        unsigned int    otmp150_d1r                : 1; /* [1..1] 0�� ��ǰ�¶ȵ���150�棻1�� ��ǰ�¶ȸ���150�档 */
        unsigned int    osc_state                  : 1; /* [2..2] 0��OSC����ʱ���Ѿ�������ʱ���л����;1��OSC����ʱ��û�о����� */
        unsigned int    vsys_uv_d2f                : 1; /* [3..3] 0��vsys<2.85V/3.0V��1��vsys>2.85V/3.0V�� */
        unsigned int    vsys_6p0_d200ur            : 1; /* [4..4] ��ǰvsys��ѹ��0��vsys<6.0V��1��vsys>6.0V�� */
        unsigned int    pwron_d20r                 : 1; /* [5..5] 0��PWRON����ǰû�б����£�1:PWRON����ǰ������(pwronΪpwron_n�ķ���)�� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_STATUS1_T;    /* ״̬��־1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    alarm_on_a                 : 1; /* [0..0] ����A:0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    alarm_on_b                 : 1; /* [1..1] ����B:0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    alarm_on_c                 : 1; /* [2..2] ����C:0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    alarm_on_d                 : 1; /* [3..3] ����D:0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    alarm_on_e                 : 1; /* [4..4] ����E:0:����ʱ��û����1������ʱ�䵽�� */
        unsigned int    vbus_det_0p9_d3r           : 1; /* [5..5] vbus_det_0p9��0: û�в��룻1�����롣 */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_STATUS2_T;    /* ״̬��־2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otmp_d1r                   : 1; /* [0..0] 0:�޴��жϣ�1��otmp ���¶ȳ����趨��ֵ��Ĭ��125�ȣ��жϡ� */
        unsigned int    vsys_2p5_f                 : 1; /* [1..1] 0:�޴��жϣ�1:vsys��ѹ����2.5V�жϡ� */
        unsigned int    vsys_uv_d2f                : 1; /* [2..2] 0:�޴��жϣ�1:vsys��ѹ����2.85V/3.0V 2ms�жϡ�(Ĭ��2.85V�����µ�Ĵ���vsys_uv_adj�ɵ�) */
        unsigned int    vsys_6p0_d200ur            : 1; /* [3..3] 0���޴��жϣ�1:vsys����ѹ����6.0V 200us�жϡ� */
        unsigned int    pwron_d4sr                 : 1; /* [4..4] 0:�޴��жϣ�1:PWRON��������4s�ж�(���ж�ֻ����������ʱ���²��ϱ�) �� */
        unsigned int    pwron_d20f                 : 1; /* [5..5] 0:�޴��жϣ�1:PWRON�����ͷ�20ms�ж� �� */
        unsigned int    pwron_d20r                 : 1; /* [6..6] 0:�޴��жϣ�1:PWRON��������20ms�жϡ� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6559_IRQ1_T;    /* �ж�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_scp_r                  : 1; /* [0..0] 0:�޴��жϣ�1:��ʾ������һ��BUCK���������������߶�·����������LDO/LVS��������������CPU��ѯ����Ҫȥ�鿴����Ĺ�������Ĵ����鿴����һ������������������д1����ж������� */
        unsigned int    vbus_det_1p375_d90ur       : 1; /* [1..1] 0:�޴��жϣ�1:vbus_det>1.375V 90us�ж� �� */
        unsigned int    vbus_det_0p9_d3f           : 1; /* [2..2] 0:�޴��жϣ�1:vbus_det<0.9 V 3ms�ж� �� */
        unsigned int    vbus_det_0p9_d3r           : 1; /* [3..3] 0:�޴��жϣ�1:vbus_det>0.9 V 3ms�ж� �� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_IRQ2_T;    /* �ж�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    alarm_on_a                 : 1; /* [0..0] ALARM_ON_A�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_b                 : 1; /* [1..1] ALARM_ON_B�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_c                 : 1; /* [2..2] ALARM_ON_C�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_d                 : 1; /* [3..3] ALARM_ON_D�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_e                 : 1; /* [4..4] ALARM_ON_E�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    alarm_on_f                 : 1; /* [5..5] ALARM_ON_F�жϣ�0:�޴��жϣ�1����RTCʱ����alarmʱ����ͬʱ,�ϱ��жϡ� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_IRQ3_T;    /* �ж�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    sim_hpd_out_f              : 1; /* [0..0] SIM������λ����SIM_HPD�жϣ�0�� �޴��ж� ��  1�� �����½�������  �� */
        unsigned int    sim_hpd_out_r              : 1; /* [1..1] SIM������λ����SIM_HPD�жϣ�0�� �޴��ж� ��  1�� ��������������  �� */
        unsigned int    sim_hpd_in_f               : 1; /* [2..2] SIM����λ����SIM_HPD�жϣ�0�� �޴��ж� ��  1�� �����½�������  �� */
        unsigned int    sim_hpd_in_r               : 1; /* [3..3] SIM����λ����SIM_HPD�жϣ�0�� �޴��ж� ��  1�� ��������������  �� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_IRQ4_T;    /* �ж�4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otmp_d1r_mk                : 1; /* [0..0] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vsys_2p5_f_mk              : 1; /* [1..1] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vsys_uv_d2f_mk             : 1; /* [2..2] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vsys_6p0_d200ur_mk         : 1; /* [3..3] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    pwron_d4sr_mk              : 1; /* [4..4] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    pwron_d20f_mk              : 1; /* [5..5] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    pwron_d20r_mk              : 1; /* [6..6] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    reserved                   : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6559_IRQ1_MASK_T;    /* �ж�����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_scp_r_mk               : 1; /* [0..0] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vbus_det_1p375_mk          : 1; /* [1..1] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vbus_det_0p9_d3f_mk        : 1; /* [2..2] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    vbus_det_0p9_d3r_mk        : 1; /* [3..3] 0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_IRQ2_MASK_T;    /* �ж�����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    alarm_on_a_mk              : 1; /* [0..0] ALARM_ON_A�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    alarm_on_b_mk              : 1; /* [1..1] ALARM_ON_B�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    alarm_on_c_mk              : 1; /* [2..2] ALARM_ON_C�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    alarm_on_d_mk              : 1; /* [3..3] ALARM_ON_D�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    alarm_on_e_mk              : 1; /* [4..4] ALARM_ON_E�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    alarm_on_f_mk              : 1; /* [5..5] ALARM_ON_F�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_IRQ3_MASK_T;    /* �ж�����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    sim_hpd_out_f_mk           : 1; /* [0..0] SIM������λ����SIM_HPD�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    sim_hpd_out_r_mk           : 1; /* [1..1] SIM������λ����SIM_HPD�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    sim_hpd_in_f_mk            : 1; /* [2..2] SIM����λ����SIM_HPD�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    sim_hpd_in_r_mk            : 1; /* [3..3] SIM����λ����SIM_HPD�жϣ�0:ʹ�ܸ��жϣ�1�����θ��жϡ� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_IRQ4_MASK_T;    /* �ж�����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_2                 : 2; /* [1..0] ������ */
        unsigned int    scp_buck3                  : 1; /* [2..2] 0��BUCK3�������·��1: BUCK3�����·�� */
        unsigned int    scp_buck4                  : 1; /* [3..3] 0��BUCK4�������·��1: BUCK4�����·�� */
        unsigned int    reserved_1                 : 1; /* [4..4] ������ */
        unsigned int    scp_buck6                  : 1; /* [5..5] 0��BUCK6�������·��1: BUCK6�����·�� */
        unsigned int    reserved_0                 : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_SCP_RECORD1_T;    /* ��·������¼1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 1; /* [0..0] ������ */
        unsigned int    ocp_buck0                  : 1; /* [1..1] 0��BUCK0��������أ�1: BUCK0������ء� */
        unsigned int    ocp_buck3                  : 1; /* [2..2] 0��BUCK3��������أ�1: BUCK3������ء� */
        unsigned int    ocp_buck4                  : 1; /* [3..3] 0��BUCK4��������أ�1: BUCK4������ء� */
        unsigned int    ocp_buck5                  : 1; /* [4..4] 0��BUCK5��������أ�1: BUCK5������ء� */
        unsigned int    ocp_buck6                  : 1; /* [5..5] 0��BUCK6��������أ�1: BUCK6������ء� */
        unsigned int    reserved_0                 : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_OCP_RECORD1_T;    /* ����������¼1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ldo1                   : 1; /* [0..0] 0��LDO1��������أ�1: LDO1������ء� */
        unsigned int    reserved_1                 : 1; /* [1..1] ������ */
        unsigned int    ocp_ldo3                   : 1; /* [2..2] 0��LDO3��������أ�1: LDO3������ء� */
        unsigned int    reserved_0                 : 2; /* [4..3] ������ */
        unsigned int    ocp_ldo6                   : 1; /* [5..5] 0��LDO6��������أ�1: LDO6������ء� */
        unsigned int    ocp_ldo7                   : 1; /* [6..6] 0��LDO7��������أ�1: LDO7������ء� */
        unsigned int    ocp_ldo8                   : 1; /* [7..7] 0��LDO8��������أ�1: LDO8������ء� */
    } bits;
    unsigned int    u32;
}HI6559_OCP_RECORD2_T;    /* ����������¼2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ldo9                   : 1; /* [0..0] 0��LDO9��������أ�1: LDO9������ء� */
        unsigned int    ocp_ldo10                  : 1; /* [1..1] 0��LDO10��������أ�1: LDO10������ء� */
        unsigned int    ocp_ldo11                  : 1; /* [2..2] 0��LDO11��������أ�1: LDO11������ء� */
        unsigned int    ocp_ldo12                  : 1; /* [3..3] 0��LDO12��������أ�1: LDO12������ء� */
        unsigned int    ocp_ldo13                  : 1; /* [4..4] 0��LDO13��������أ�1: LDO13������ء� */
        unsigned int    ocp_ldo14                  : 1; /* [5..5] 0��LDO14��������أ�1: LDO14������ء� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_OCP_RECORD3_T;    /* ����������¼3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 5; /* [4..0] ������ */
        unsigned int    ocp_ldo22                  : 1; /* [5..5] 0��LDO22��������أ�1: LDO22������ء� */
        unsigned int    ocp_ldo23                  : 1; /* [6..6] 0��LDO23��������أ�1: LDO23������ء� */
        unsigned int    ocp_ldo24                  : 1; /* [7..7] 0��LDO24��������أ�1: LDO24������ء� */
    } bits;
    unsigned int    u32;
}HI6559_OCP_RECORD4_T;    /* ����������¼4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 5; /* [4..0] ������ */
        unsigned int    ocp_lvs7                   : 1; /* [5..5] 0��LVS7��������أ�1: LVS7������ء� */
        unsigned int    reserved_0                 : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_OCP_RECORD5_T;    /* ����������¼5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_lvs9                   : 1; /* [0..0] 0��LVS9��������أ�1: LVS9������ء� */
        unsigned int    reserved                   : 7; /* [7..1] ������ */
    } bits;
    unsigned int    u32;
}HI6559_OCP_RECORD6_T;    /* ����������¼6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_otmp_d1r                : 1; /* [0..0] �¶ȱ���(Ĭ��125��)��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_hreset_n_f              : 1; /* [1..1] �ȸ�λ��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vsys_2p5_f              : 1; /* [2..2] vsys < 2.5V��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vsys_uv_d2f             : 1; /* [3..3] vsys < 2.85V/3.0V 2ms:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vsys_6p0_d200ur         : 1; /* [4..4] vsys> 6.0V 200us:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_d4sr              : 1; /* [5..5] ����������״̬��PWRON����4s:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_d20f              : 1; /* [6..6] PWRON�����ͷ�20ms��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_d20r              : 1; /* [7..7] PWRON��������20ms��0:û�з��������¼���1:�������¼��� */
    } bits;
    unsigned int    u32;
}HI6559_NP_IRQ1_RECORD_T;    /* �ж�1���µ��¼�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_vbus_det_0p9_d150r      : 1; /* [0..0] vbus_det> 0.9V 150ms��     0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vbus_det_1p375          : 1; /* [1..1] vbus_det>1.375V 90us��     0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vbus_det_0p9_d3f        : 1; /* [2..2] vbus_det< 0.9V 3ms�� 0:û�з��������¼���1:�������¼��� */
        unsigned int    np_vbus_det_0p9_d3r        : 1; /* [3..3] vbus_det> 0.9V 3ms�� 0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_restart           : 1; /* [4..4] ͨ��pwron����N+5S����:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_dnsr              : 1; /* [5..5] ������������pwron����Ns�ػ�:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_pwron_d500r             : 1; /* [6..6] �ػ�״̬��PWRON����500ms:0:û�з��������¼���1:�������¼��� */
        unsigned int    np_otmp150_d1r             : 1; /* [7..7] �¶� > 150�棺0:û�з��������¼���1:�������¼��� */
    } bits;
    unsigned int    u32;
}HI6559_NP_IRQ2_RECORD_T;    /* �ж�2���µ��¼�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_alarm_on_a              : 1; /* [0..0] ��������a��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_alarm_on_b              : 1; /* [1..1] ��������b��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_alarm_on_c              : 1; /* [2..2] ��������c��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_alarm_on_d              : 1; /* [3..3] ��������d��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_alarm_on_e              : 1; /* [4..4] ��������e��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_alarm_on_f              : 1; /* [5..5] ��������f��0:û�з��������¼���1:�������¼��� */
        unsigned int    np_hold_pwron_r            : 1; /* [6..6] pwr_hold�ϵ��¼��0��û�з������¼���1���������¼��� */
        unsigned int    np_hold_pwrdw_r            : 1; /* [7..7] pwr_hold�µ��¼��0��û�з������¼���1���������¼��� */
    } bits;
    unsigned int    u32;
}HI6559_NP_IRQ3_RECORD_T;    /* �ж�3���µ��¼�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_2                 : 2; /* [1..0] ���� */
        unsigned int    np_scp_buck3               : 1; /* [2..2] 0������¼BUCK3�������·��1: ����¼BUCK3�����·�� */
        unsigned int    np_scp_buck4               : 1; /* [3..3] 0������¼BUCK4�������·��1: ����¼BUCK4�����·�� */
        unsigned int    reserved_1                 : 1; /* [4..4] ���� */
        unsigned int    np_scp_buck6               : 1; /* [5..5] 0������¼BUCK6�������·��1: ����¼BUCK6�����·�� */
        unsigned int    reserved_0                 : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_NP_SCP_RECORD1_T;    /* ��·�������µ��¼1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 3; /* [2..0] ���� */
        unsigned int    np_ocp_buck0               : 1; /* [3..3] 0������¼BUCK0��������أ�1: ����¼BUCK0������ء� */
        unsigned int    np_ocp_buck3               : 1; /* [4..4] 0������¼BUCK3��������أ�1: ����¼BUCK3������ء� */
        unsigned int    np_ocp_buck4               : 1; /* [5..5] 0������¼BUCK4��������أ�1: ����¼BUCK4������ء� */
        unsigned int    np_ocp_buck5               : 1; /* [6..6] 0������¼BUCK5��������أ�1: ����¼BUCK5������ء� */
        unsigned int    np_ocp_buck6               : 1; /* [7..7] 0������¼BUCK6��������أ�1: ����¼BUCK6������ء� */
    } bits;
    unsigned int    u32;
}HI6559_NP_OCP_RECORD1_T;    /* �����������µ��¼1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_ocp_ldo1                : 1; /* [0..0] 0������¼LDO1��������أ�1: ����¼LDO1������ء� */
        unsigned int    reserved_1                 : 1; /* [1..1] ���� */
        unsigned int    np_ocp_ldo3                : 1; /* [2..2] 0������¼LDO3��������أ�1: ����¼LDO3������� �� */
        unsigned int    reserved_0                 : 2; /* [4..3] ���� */
        unsigned int    np_ocp_ldo6                : 1; /* [5..5] 0������¼LDO6��������أ�1: ����¼LDO6������ء� */
        unsigned int    np_ocp_ldo7                : 1; /* [6..6] 0������¼LDO7��������أ�1: ����¼LDO7������ء� */
        unsigned int    np_ocp_ldo8                : 1; /* [7..7] 0������¼LDO8��������أ�1: ����¼LDO8������ء� */
    } bits;
    unsigned int    u32;
}HI6559_NP_OCP_RECORD2_T;    /* �����������µ��¼2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_ocp_ldo9                : 1; /* [0..0] 0������¼LDO9��������أ�1: ����¼LDO9������ء� */
        unsigned int    np_ocp_ldo10               : 1; /* [1..1] 0������¼LDO10��������أ�1: ����¼LDO10������ء� */
        unsigned int    np_ocp_ldo11               : 1; /* [2..2] 0������¼LDO11��������أ�1: ����¼LDO11������ء� */
        unsigned int    np_ocp_ldo12               : 1; /* [3..3] 0������¼LDO12��������أ�1: ����¼LDO12������ء� */
        unsigned int    np_ocp_ldo13               : 1; /* [4..4] 0������¼LDO13��������أ�1: ����¼LDO13������ء� */
        unsigned int    np_ocp_ldo14               : 1; /* [5..5] 0������¼LDO14��������أ�1: ����¼LDO14������ء� */
        unsigned int    reserved                   : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_NP_OCP_RECORD3_T;    /* �����������µ��¼3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 5; /* [4..0] ���� */
        unsigned int    np_ocp_ldo22               : 1; /* [5..5] 0������¼LDO22��������أ�1: ����¼LDO22������ء� */
        unsigned int    np_ocp_ldo23               : 1; /* [6..6] 0������¼LDO23��������أ�1: ����¼LDO23������ء� */
        unsigned int    np_ocp_ldo24               : 1; /* [7..7] 0������¼LDO24��������أ�1: ����¼LDO24������ء� */
    } bits;
    unsigned int    u32;
}HI6559_NP_OCP_RECORD4_T;    /* �����������µ��¼4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 5; /* [4..0] ���� */
        unsigned int    np_ocp_lvs7                : 1; /* [5..5] 0������¼LVS7��������أ�1: ����¼LVS7������ء� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_NP_OCP_RECORD5_T;    /* �����������µ��¼5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    np_ocp_lvs9                : 1; /* [0..0] 0������¼LVS9��������أ�1: ����¼LVS9������ء� */
        unsigned int    reserved                   : 7; /* [7..1] ���� */
    } bits;
    unsigned int    u32;
}HI6559_NP_OCP_RECORD6_T;    /* �����������µ��¼6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ldo_deb_sel            : 2; /* [1..0] ocpȥ��ʱ�䣺00��500us��01��1ms��10��2ms��11��4ms�� */
        unsigned int    en_ldo_ocp_deb             : 1; /* [2..2] 0��LDO OCP�����ز�ȥ����1��LDO OCP������ȥ����ע��LDO��LVS���á� */
        unsigned int    ocp_buck_deb_sel           : 2; /* [4..3] BUCK ��ocp��scpȥ��ʱ�䣺00��500us��01��1ms��10��2ms��11��4ms�� */
        unsigned int    en_buck_ocp_deb            : 1; /* [5..5] 0��BUCK OCP�����ز�ȥ����1��BUCK OCP������ȥ���� */
        unsigned int    en_buck_scp_deb            : 1; /* [6..6] 0��BUCK SCP�����ز�ȥ����1��BUCK SCP������ȥ���� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_OCP_DEB_T;    /* OCPȥ�������ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vbus_det_0p9_ctrl          : 1; /* [0..0] 0������vbus_det<0.9V��⣻1:������vbus_det<0.9V��⡣ */
        unsigned int    vsys_2p5_ctrl              : 1; /* [1..1] 0������vsys< 2.5V��⣻1:������vsys<2.5V��⡣ */
        unsigned int    vsys_uv_ctrl               : 1; /* [2..2] 0������vsys< 2.85V/3.0V��⣻1:������vsys<2.85V/3.0V��⡣ */
        unsigned int    vsys_6p0_ctrl              : 1; /* [3..3] 0������vsys>6.0V��⣻1:������vsys>6.0��⡣ */
        unsigned int    otmp150_ctrl               : 1; /* [4..4] 0�����£�150�棩���ػ���1������(150��)�ػ��� */
        unsigned int    reserved                   : 1; /* [5..5] ���� */
        unsigned int    en_32kb                    : 1; /* [6..6] 0�� �ر� CLK_32B ʱ�������1��  CLK_32B ʱ�����ʹ�ܡ� */
        unsigned int    en_32ka                    : 1; /* [7..7] 0�� �ر� CLK_32A ʱ�������1��  CLK_32A ʱ�����ʹ�ܡ� */
    } bits;
    unsigned int    u32;
}HI6559_ONOFF8_T;    /* ���ؿ���8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 2; /* [1..0] ���� */
        unsigned int    ocp_scp_ctrl_buck0         : 1; /* [2..2] ocp_scp_off_buck0����Ϊ1ʱ��ocp_scp_ctrl_buck0:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_scp_off_buck0          : 1; /* [3..3] 0���������·��֧��BUCK0ģ���Զ��رգ�1���������·��֧��BUCK0ģ���Զ��ر� �� */
        unsigned int    ocp_scp_ctrl_buck3         : 1; /* [4..4] ocp_scp_off_buck3����Ϊ1ʱ��ocp_scp_ctrl_buck3:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_scp_off_buck3          : 1; /* [5..5] 0���������·��֧��BUCK3ģ���Զ��رգ�1���������·��֧��BUCK3ģ���Զ��ر� �� */
        unsigned int    ocp_scp_ctrl_buck4         : 1; /* [6..6] ocp_scp_off_buck4����Ϊ1ʱ��ocp_scp_ctrl_buck4:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_scp_off_buck4          : 1; /* [7..7] 0���������·��֧��BUCK4ģ���Զ��رգ�1���������·��֧��BUCK4ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6559_OCP_SCP_MOD_CTRL1_T;    /* BUCK0-3�����Ͷ�·����ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_scp_ctrl_buck5         : 1; /* [0..0] ocp_scp_off_buck5����Ϊ1ʱ��ocp_scp_ctrl_buck5:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_scp_off_buck5          : 1; /* [1..1] 0���������·��֧��BUCK5ģ���Զ��رգ�1���������·��֧��BUCK5ģ���Զ��ر� �� */
        unsigned int    ocp_scp_ctrl_buck6         : 1; /* [2..2] ocp_scp_off_buck6����Ϊ1ʱ��ocp_scp_ctrl_buck6:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_scp_off_buck6          : 1; /* [3..3] 0���������·��֧��BUCK6ģ���Զ��رգ�1���������·��֧��BUCK6ģ���Զ��ر� �� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_OCP_SCP_MOD_CTRL2_T;    /* BUCK4-7�����Ͷ�·����ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_ldo1              : 1; /* [0..0] ocp_off_ldo1����Ϊ1ʱ��ocp_ctrl_ldo1:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo1               : 1; /* [1..1] 0��������֧��LDO1ģ���Զ��رգ�1��������֧��LDO1ģ���Զ��ر� �� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    ocp_ctrl_ldo3              : 1; /* [4..4] ocp_off_ldo3����Ϊ1ʱ��ocp_ctrl_ldo3:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_ldo3               : 1; /* [5..5] 0��������֧��LDO3ģ���Զ��رգ�1��������֧��LDO3ģ���Զ��ر� �� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_OCP_MOD_CTRL3_T;    /* LDO1-4��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 2; /* [1..0] ���� */
        unsigned int    ocp_ctrl_ldo6              : 1; /* [2..2] ocp_off_ldo6����Ϊ1ʱ��ocp_ctrl_ldo6:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo6               : 1; /* [3..3] 0��������֧��LDO6ģ���Զ��رգ�1��������֧��LDO6ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo7              : 1; /* [4..4] ocp_off_ldo7����Ϊ1ʱ��ocp_ctrl_ldo7:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo7               : 1; /* [5..5] 0��������֧��LDO7ģ���Զ��رգ�1��������֧��LDO7ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo8              : 1; /* [6..6] ocp_off_ldo8����Ϊ1ʱ��ocp_ctrl_ldo8:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo8               : 1; /* [7..7] 0��������֧��LDO8ģ���Զ��رգ�1��������֧��LDO8ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6559_OCP_MOD_CTRL4_T;    /* LDO5-8��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_ldo9              : 1; /* [0..0] ocp_off_ldo9����Ϊ1ʱ��ocp_ctrl_ldo9:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo9               : 1; /* [1..1] 0��������֧��LDO9ģ���Զ��رգ�1��������֧��LDO9ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo10             : 1; /* [2..2] ocp_off_ldo10����Ϊ1ʱ��ocp_ctrl_ldo10:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo10              : 1; /* [3..3] 0��������֧��LDO10ģ���Զ��رգ�1��������֧��LDO10ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo11             : 1; /* [4..4] ocp_off_ldo11����Ϊ1ʱ��ocp_ctrl_ldo11:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo11              : 1; /* [5..5] 0��������֧��LDO11ģ���Զ��رգ�1��������֧��LDO11ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo12             : 1; /* [6..6] ocp_off_ldo12����Ϊ1ʱ��ocp_ctrl_ldo12:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo12              : 1; /* [7..7] 0��������֧��LDO12ģ���Զ��رգ�1��������֧��LDO12ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6559_OCP_MOD_CTRL5_T;    /* LDO9-12��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    ocp_ctrl_ldo13             : 1; /* [0..0] ocp_off_ldo13����Ϊ1ʱ��ocp_ctrl_ldo13:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo13              : 1; /* [1..1] 0��������֧��LDO13ģ���Զ��رգ�1��������֧��LDO13ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo14             : 1; /* [2..2] ocp_off_ldo14����Ϊ1ʱ��ocp_ctrl_ldo14:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo14              : 1; /* [3..3] 0��������֧��LDO14ģ���Զ��رգ�1��������֧��LDO14ģ���Զ��ر� �� */
        unsigned int    reserved                   : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6559_OCP_MOD_CTRL6_T;    /* LDO13-16��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 2; /* [1..0] ���� */
        unsigned int    ocp_ctrl_ldo22             : 1; /* [2..2] ocp_off_ldo22����Ϊ1ʱ��ocp_ctrl_ldo22:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo22              : 1; /* [3..3] 0��������֧��LDO22ģ���Զ��رգ�1��������֧��LDO22ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo23             : 1; /* [4..4] ocp_off_ldo23����Ϊ1ʱ��ocp_ctrl_ldo23:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo23              : 1; /* [5..5] 0��������֧��LDO23ģ���Զ��رգ�1��������֧��LDO23ģ���Զ��ر� �� */
        unsigned int    ocp_ctrl_ldo24             : 1; /* [6..6] ocp_off_ldo24����Ϊ1ʱ��ocp_ctrl_ldo24:0:�����ڹ���ģʽ2��1:�����ڹ���ģʽ3�� */
        unsigned int    ocp_off_ldo24              : 1; /* [7..7] 0��������֧��LDO24ģ���Զ��رգ�1��������֧��LDO24ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6559_OCP_MOD_CTRL7_T;    /* LDO21-ldo23��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 2; /* [1..0] ���� */
        unsigned int    ocp_ctrl_lvs7              : 1; /* [2..2] ocp_off_lvs7����Ϊ1ʱ��ocp_ctrl_lvs7:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_lvs7               : 1; /* [3..3] 0��������֧��lvs7ģ���Զ��رգ�1��������֧��lvs7ģ���Զ��ر� �� */
        unsigned int    reserved_0                 : 2; /* [5..4] ���� */
        unsigned int    ocp_ctrl_lvs9              : 1; /* [6..6] ocp_off_lvs9����Ϊ1ʱ��ocp_ctrl_lvs9:0������ģʽΪģʽ2��1������ģʽΪģʽ3�� */
        unsigned int    ocp_off_lvs9               : 1; /* [7..7] 0��������֧��LVS9ģ���Զ��رգ�1��������֧��LVS9ģ���Զ��ر� �� */
    } bits;
    unsigned int    u32;
}HI6559_OCP_MOD_CTRL8_T;    /* LVS7-9��������ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 2; /* [1..0] ���� */
        unsigned int    en_buck0_int               : 1; /* [2..2] BUCK0����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_buck3_int               : 1; /* [3..3] BUCK3����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_buck4_int               : 1; /* [4..4] BUCK4����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_buck5_int               : 1; /* [5..5] BUCK5����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_buck6_int               : 1; /* [6..6] BUCK6����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6559_ENABLE1_T;    /* ��Դģ��ʹ��1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 2; /* [1..0] ���� */
        unsigned int    dis_buck0_int              : 1; /* [2..2] BUCK0���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_buck3_int              : 1; /* [3..3] BUCK3���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_buck4_int              : 1; /* [4..4] BUCK4���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_buck5_int              : 1; /* [5..5] BUCK5���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_buck6_int              : 1; /* [6..6] BUCK6���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DISABLE1_T;    /* ��Դģ��ر�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 2; /* [1..0] ���� */
        unsigned int    st_buck0_int               : 1; /* [2..2] BUCK0����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_buck3_int               : 1; /* [3..3] BUCK3����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_buck4_int               : 1; /* [4..4] BUCK4����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_buck5_int               : 1; /* [5..5] BUCK5����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_buck6_int               : 1; /* [6..6] BUCK6����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6559_ONOFF_STATUS1_T;    /* ��Դģ�鿪��״̬1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_ldo1_int                : 1; /* [0..0] LDO1����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    reserved_1                 : 1; /* [1..1] ���� */
        unsigned int    en_ldo3_buck_int           : 1; /* [2..2] BUCK��LDO3ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    reserved_0                 : 2; /* [4..3] ���� */
        unsigned int    en_ldo6_int                : 1; /* [5..5] LDO6����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo7_int                : 1; /* [6..6] LDO7����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo8_int                : 1; /* [7..7] LDO8����ʹ�ܣ�д1�������Զ����㡣 */
    } bits;
    unsigned int    u32;
}HI6559_ENABLE2_T;    /* ��Դģ��ʹ��2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dis_ldo1_int               : 1; /* [0..0] LDO1���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    reserved_1                 : 1; /* [1..1] ���� */
        unsigned int    dis_ldo3_buck_int          : 1; /* [2..2] BUCK��LDO3��ֹ��д1�رգ��Զ����㡣 */
        unsigned int    reserved_0                 : 2; /* [4..3] ���� */
        unsigned int    dis_ldo6_int               : 1; /* [5..5] LDO6���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo7_int               : 1; /* [6..6] LDO7���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo8_int               : 1; /* [7..7] LDO8���ؽ�ֹ��д1�رգ��Զ����㡣 */
    } bits;
    unsigned int    u32;
}HI6559_DISABLE2_T;    /* ��Դģ��ر�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    st_ldo1_int                : 1; /* [0..0] LDO1����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    reserved_1                 : 1; /* [1..1] ���� */
        unsigned int    st_ldo3_buck_int           : 1; /* [2..2] BUCK��LDO3ʱ�ܿ���״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    reserved_0                 : 2; /* [4..3] ���� */
        unsigned int    st_ldo6_int                : 1; /* [5..5] LDO6����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo7_int                : 1; /* [6..6] LDO7����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo8_int                : 1; /* [7..7] LDO8����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
    } bits;
    unsigned int    u32;
}HI6559_ONOFF_STATUS2_T;    /* ��Դģ�鿪��״̬2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_ldo10_int               : 1; /* [0..0] LDO10����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo12_int               : 1; /* [1..1] LDO12����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo13_int               : 1; /* [2..2] LDO13����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo14_int               : 1; /* [3..3] LDO14����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_ENABLE3_T;    /* ��Դģ��ʹ��3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dis_ldo10_int              : 1; /* [0..0] LDO10���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo12_int              : 1; /* [1..1] LDO12���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo13_int              : 1; /* [2..2] LDO13���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo14_int              : 1; /* [3..3] LDO14���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DISABLE3_T;    /* ��Դģ��ر�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    st_ldo10_int               : 1; /* [0..0] LDO10����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo12_int               : 1; /* [1..1] LDO12����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo13_int               : 1; /* [2..2] LDO13����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo14_int               : 1; /* [3..3] LDO14����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_ONOFF_STATUS3_T;    /* ��Դģ�鿪��״̬3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 3; /* [2..0] ���� */
        unsigned int    en_ldo22_int               : 1; /* [3..3] LDO22����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo23_int               : 1; /* [4..4] LDO23����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo24_int               : 1; /* [5..5] LDO24����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    en_ldo3_batt_int           : 1; /* [6..6] BATT��LDO3ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6559_ENABLE4_T;    /* ��Դģ��ʹ��4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 3; /* [2..0] ���� */
        unsigned int    dis_ldo22_int              : 1; /* [3..3] LDO22���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo23_int              : 1; /* [4..4] LDO23���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo24_int              : 1; /* [5..5] LDO24���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    dis_ldo3_batt_int          : 1; /* [6..6] BATT��LDO3��ֹ��д1�رգ��Զ����㡣 */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DISABLE4_T;    /* ��Դģ��ر�4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 3; /* [2..0] ���� */
        unsigned int    st_ldo22_int               : 1; /* [3..3] LDO22����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo23_int               : 1; /* [4..4] LDO23����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo24_int               : 1; /* [5..5] LDO24����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    st_ldo3_batt_int           : 1; /* [6..6] BATT��LDO3����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6559_ONOFF_STATUS4_T;    /* ��Դģ�鿪��״̬4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 5; /* [4..0] ���� */
        unsigned int    en_lvs7_int                : 1; /* [5..5] LVS7����ʹ�ܣ�д1�������Զ����㡣 */
        unsigned int    reserved_0                 : 1; /* [6..6] ���� */
        unsigned int    en_lvs9_int                : 1; /* [7..7] LVS9����ʹ�ܣ�д1�������Զ����㡣 */
    } bits;
    unsigned int    u32;
}HI6559_ENABLE5_T;    /* ��Դģ��ʹ��5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 5; /* [4..0] ���� */
        unsigned int    dis_lvs7_int               : 1; /* [5..5] LVS7���ؽ�ֹ��д1�رգ��Զ����㡣 */
        unsigned int    reserved_0                 : 1; /* [6..6] ���� */
        unsigned int    dis_lvs9_int               : 1; /* [7..7] LVS9���ؽ�ֹ��д1�رգ��Զ����㡣 */
    } bits;
    unsigned int    u32;
}HI6559_DISABLE5_T;    /* ��Դģ��ر�5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 5; /* [4..0] ���� */
        unsigned int    st_lvs7_int                : 1; /* [5..5] LVS7����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
        unsigned int    reserved_0                 : 1; /* [6..6] ���� */
        unsigned int    st_lvs9_int                : 1; /* [7..7] LVS9����״̬��0��ͨ���Ĵ����رգ� 1��ͨ���Ĵ��������� */
    } bits;
    unsigned int    u32;
}HI6559_ONOFF_STATUS5_T;    /* ��Դģ�鿪��״̬5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_ldo9_int                : 1; /* [0..0] 0���ر�LDO9 ��1������LDO9 �� */
        unsigned int    sim_en_int                 : 1; /* [1..1] simcardת����·��ʹ���źţ�0���ر�simcardת����· ��1������simcardת����· �� */
        unsigned int    en_ldo11_int               : 1; /* [2..2] 0���ر�LDO11 ��1������LDO11 �� */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI6559_SIM_LDO9_LDO11_EN_T;    /* SIM��/LDO9/LDO11ʹ�ܼĴ����� */

typedef union
{
    struct
    {
        unsigned int    simcard_resv               : 2; /* [1..0] ����CLK�����������������simcard_resv[1]����P�ܵ�����������simcard_resv[0]����N�ܵ�����������0������������������1���������������� */
        unsigned int    simcard_bbrp               : 1; /* [2..2] simcard��DATAIO BB����������ʹ���źţ�0�������������裻1���ر��������� �� */
        unsigned int    simcard_simrp              : 1; /* [3..3] simcard��DATAIO SIM������������ʹ���źţ�0�������������裻1���ر��������� �� */
        unsigned int    simcard_200ns_en           : 1; /* [4..4] simcard 200ns��������ʱ���ʹ���źţ�0���رտ����������� ��1����ʼ������������ �� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI6559_SIM_CFG_T;    /* SIM�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    simcard_deb_sel            : 5; /* [4..0] SIMCARD������ȥ��ʱ��ɵ���0x3 : 120us0x4 : 150us0x5 : 180us0x6 : 210us0x7 : 240us0x8 : 270us0x9 : 300us0xa : 330us0xb : 360us0xc : 390us0xd : 420us0xe : 450us0xf : 480us0x10: 510us0x11: 540us0x12: 570us0x13: 600us */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI6559_SIM_DEB_T;    /* SIM���ж�ȥ���ĵ��ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    en_eco_buck3_int           : 1; /* [0..0] ����BUCK3�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_buck4_int           : 1; /* [1..1] ����BUCK4�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    reserved_1                 : 1; /* [2..2] ���� */
        unsigned int    en_eco_buck6_int           : 1; /* [3..3] ����BUCK6�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    reserved_0                 : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_ECO_MOD_CFG1_T;    /* ��Դģ���Ƿ����PMU����ECOģʽ����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_eco_ldo3_int            : 1; /* [0..0] ����LDO3�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo7_int            : 1; /* [1..1] ����LDO7�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo9_int            : 1; /* [2..2] ����LDO9�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo10_int           : 1; /* [3..3] ����LDO10�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    reserved                   : 1; /* [4..4] ���� */
        unsigned int    en_eco_ldo12_int           : 1; /* [5..5] ����LDO12�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo22_int           : 1; /* [6..6] ����LDO22�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
        unsigned int    en_eco_ldo24_int           : 1; /* [7..7] ����LDO24�Ƿ���PMU����ECOģʽ:0:�����棻1�����档 */
    } bits;
    unsigned int    u32;
}HI6559_ECO_MOD_CFG2_T;    /* ��Դģ���Ƿ����PMU����ECOģʽ����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    force_eco_buck3_int        : 1; /* [0..0] �����Ƿ�ǿ��ʹBUCK3����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_buck4_int        : 1; /* [1..1] �����Ƿ�ǿ��ʹBUCK4����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    reserved_1                 : 1; /* [2..2] ���� */
        unsigned int    force_eco_buck6_int        : 1; /* [3..3] �����Ƿ�ǿ��ʹBUCK6����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    reserved_0                 : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_ECO_MOD_CFG3_T;    /* ��Դ�Ƿ�ǿ����PMU����ECOģʽ����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    force_eco_ldo3_int         : 1; /* [0..0] �����Ƿ�ǿ��ʹLDO3����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo7_int         : 1; /* [1..1] �����Ƿ�ǿ��ʹLDO7����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo9_int         : 1; /* [2..2] �����Ƿ�ǿ��ʹLDO9����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo10_int        : 1; /* [3..3] �����Ƿ�ǿ��ʹLDO10����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    reserved                   : 1; /* [4..4] ���� */
        unsigned int    force_eco_ldo12_int        : 1; /* [5..5] �����Ƿ�ǿ��ʹLDO12����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo22_int        : 1; /* [6..6] �����Ƿ�ǿ��ʹLDO22����ECOģʽ��0:�����룻1�����롣 */
        unsigned int    force_eco_ldo24_int        : 1; /* [7..7] �����Ƿ�ǿ��ʹLDO24����ECOģʽ��0:�����룻1�����롣 */
    } bits;
    unsigned int    u32;
}HI6559_ECO_MOD_CFG4_T;    /* ��Դ�Ƿ�ǿ����PMU����ECOģʽ����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    eco_pwrsel                 : 2; /* [1..0] PMU�����͹���ʱ��ѡ��00��PMU�����͹���ʱ��ͼ���1��01��PMU�����͹���ʱ��ͼ���2��10��PMU�����͹���ʱ��ͼ���1��11��PMU�����͹���ʱ��ͼ���1�� */
        unsigned int    peri_en_ctrl_ldo12         : 1; /* [2..2] LDO12�Ƿ���PERI_EN�������µ�:0�� ���ܿ� ��1�� �ܿ� �� */
        unsigned int    peri_en_ctrl_lvs9          : 1; /* [3..3] LVS9�Ƿ���PERI_EN�������µ�:0�� ���ܿ� ��1�� �ܿ� �� */
        unsigned int    peri_en_ctrl_ldo8          : 1; /* [4..4] LDO8�Ƿ���PERI_EN�������µ�:0�� ���ܿ� ��1�� �ܿ� �� */
        unsigned int    peri_en_ctrl_buck3         : 1; /* [5..5] BUCK3�Ƿ���PERI_EN�������µ�:0�� ���ܿ� ��1�� �ܿ� �� */
        unsigned int    reserved                   : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_ENB3_ECO_MARK_T;    /* ��ENB3Ӳ�ߺ�ECO������ص������źżĴ����� */

typedef union
{
    struct
    {
        unsigned int    reserved                   : 5; /* [4..0] ���� */
        unsigned int    buck0_nmos_ocp_sel         : 1; /* [5..5] buck0 nmos ocpѡ���ź�                                                                   0��ѡ��nmos ocp                                                                               1������nmos ocp */
        unsigned int    buck0_ocp_tran_enhance     : 1; /* [6..6] buck0 ocp ��ر�ʱ�����                                                               0��Ĭ��                                                                                             1���ɻ�·���� */
        unsigned int    buck0_apt_leak_sel         : 1; /* [7..7] buck0 apt��ѹ������������ѡ��                                                   0������                                                                                                1���ر� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG1_ADJ_T;    /* BUCK0����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck_osc                   : 5; /* [4..0] ����buckƵ��,Ĭ��Ƶ��Ϊ2.5MHz */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG2_ADJ_T;    /* BUCK0����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 3; /* [2..0] ���� */
        unsigned int    buck0_leak_off_sel         : 1; /* [3..3] buck0���������Ƿ�ǿ�ƹر�P��ѡ��                                                     0����ǿ�ƹر�                                                                                     1��ǿ�ƹر� */
        unsigned int    reserved_0                 : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG3_ADJ_T;    /* BUCK0����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_comp_adj             : 8; /* [7..0] BUCK0�ȶ��͵��ڼĴ���<7>: OCP�¾ɷ���ѡ��Ĵ���0���Ϸ���1���·���<6��0>�����ڵ���EA�Ŀ絼�������ĵ��� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG4_ADJ_T;    /* BUCK0����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_pdm_sel              : 8; /* [7..0] ʹ��APT�����ź�00000000��APT������Ч00000001��APT������Ч */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG5_ADJ_T;    /* BUCK0����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck_osc_random            : 8; /* [7..0] <7>:buck0 ocp�رտ���  0�����ر�ocpģ��  1���ر�ocpģ��<6>:buck5 ocp�رտ���  0�����ر�ocpģ��  1���ر�ocpģ��<5>:�����������  0��Ĭ������  1�������С��<4>:�����Ƚ���ѡ��  0��1.8V�Ƚ�����  1��5V�Ƚ�����<3:2>:buck5 p����������<1:0>:buck5 n���������� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG6_ADJ_T;    /* BUCK0����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_ocp_adj_old          : 4; /* [3..0] ��ocp����ڼĴ��� */
        unsigned int    buck0_ocp_n_sel            : 4; /* [7..4] buck0 nocp����� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG7_ADJ_T;    /* BUCK0����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_dt_sel               : 2; /* [1..0] BUCK0����ʱ�����<0>0����������ʱ��1����С����ʱ��<1>0����С����ʱ��1����������ʱ�� */
        unsigned int    buck0_apt_ss               : 1; /* [2..2] buck0ʹ����ʱ���ڼĴ��� */
        unsigned int    buck0_sl_sel               : 1; /* [3..3] buck0б�µ�ѹб�ʵ��ڼĴ���                                                               0��Ĭ��                                                                                                    1���Ӵ�б�� */
        unsigned int    buck0_cs_os_sel            : 1; /* [4..4] buck0 W/Lģ�µ�������offset���ڼĴ��� */
        unsigned int    buck0_ocp_mode_sel         : 1; /* [5..5] buck0 ocpģʽѡ��                                                                             0��p�ܺ�n��ͬʱ���                                                                           1�����p�ܣ���ʱ600ns */
        unsigned int    buck0_vodet_en             : 1; /* [6..6] vo��⹦�ܣ�1��Ĭ�ϣ���vo��⣻0����vo��⣻ */
        unsigned int    buck0_dmd_sHI6559eld           : 1; /* [7..7] ����dmd��0�������Σ�1������ */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG8_ADJ_T;    /* BUCK0����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_eacap_sel            : 2; /* [1..0] ����EA����Թܴ��ĵ���                                                                      10: defaut  2.8pf */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck0_dmd_sel              : 3; /* [6..4] buck0 dmd��ѡ��Ĵ��� */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG9_ADJ_T;    /* BUCK0����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_ocp_sel_old          : 1; /* [0..0] buck0��ocp������1�����������0����������� */
        unsigned int    reserved_1                 : 1; /* [1..1] ���� */
        unsigned int    buck0_sft_sel              : 1; /* [2..2] buck0������ʱ��ѡ�� */
        unsigned int    buck0_ocp_delay_sel        : 1; /* [3..3] buck0 ocp�˲�ʱ��ѡ��                                                                       0��Ĭ��                                                                                               1����ʱ����һ�� */
        unsigned int    reserved_0                 : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG10_ADJ_T;    /* BUCK0����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_sc_sel               : 2; /* [1..0] б�²���������� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck0_mod_sel              : 2; /* [5..4] buck0ģʽѡ��X1:PWMģʽ��10:PFMģʽ��00:freed�� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG11_ADJ_T;    /* BUCK0����11�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_leak_mos_sel         : 2; /* [1..0] buck0���������ܳߴ�ѡ��                                                                    00~11������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck0_sg_sel               : 2; /* [5..4] б�²�������������00~11:������������ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG12_ADJ_T;    /* BUCK0����12�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_2                 : 2; /* [1..0] ���� */
        unsigned int    buck0_ocp_sHI6559eld           : 1; /* [2..2] buck0 ocp������������0���й�����������1���޹����������� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    buck0_ton                  : 2; /* [5..4] buck0��Сtonʱ����ڣ�00��5ns��01��15ns��10��25ns default��11��35ns�� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG13_ADJ_T;    /* BUCK0����13�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_ccm_ctrl             : 1; /* [0..0] buck0��ǿ������ģʽ����1��ǿ������ģʽ���ܹر�0��ǿ������ģʽ���ܿ����� */
        unsigned int    buck0_cmp_i_sel            : 1; /* [1..1] PWM�Ƚ���ƫ�õ������ڼĴ���                                                       0:1uA                                                                                                     1:2uA */
        unsigned int    buck0_shortn               : 1; /* [2..2] buck0�Ķ�·���������ź�0���ж�·����1���޶�·���� */
        unsigned int    buck0_pfm_sleep            : 1; /* [3..3] pwmģʽ���μĴ���                                                                               0��������                                                                                             1������ */
        unsigned int    buck0_drv_adj              : 2; /* [5..4] ��ͬģʽ�������͵�������offset���ڼĴ���                                    <1>: ��������                                                                                            <0>: ��������offset���� */
        unsigned int    buck0_clamp_en             : 1; /* [6..6] VZ��λ���ܿ���0���ر���λ����1��������λ���� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG14_ADJ_T;    /* BUCK0����14�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_ocp_sel              : 3; /* [2..0] buck0 ocp����ڼĴ��� */
        unsigned int    buck0_apt_res              : 1; /* [3..3] EA��������ǯλʹ�ܼĴ���                                                               <0>:                                                                                               0���������費��VO�仯                                                                         1�����������Ƿ���VO�仯��APT���� */
        unsigned int    buck0_hyctrl               : 1; /* [4..4] APT����ʱ�������Ƚ������Ϳ���0��Ĭ�ϣ�1���Ӵ���ͣ� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG15_ADJ_T;    /* BUCK0����15�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_reserve              : 8; /* [7..0] <7:6>:����APT����ʱ����ο���ѹ��RC����00��Ĭ��<5>:��������delayֵcs_sel1��Ĭ��0���Ӵ�delay<4>:APT����ʱ�������ֿ�device_sel1��Ĭ�ϣ����ֿ�0���ֿ�<3>:PMOS��������ʱ�����PR1:Ĭ��0���Ӵ�����ʱ��<2>:PMOS�����½�ʱ�����PF0:Ĭ��1���Ӵ��½�ʱ��<1>:NMOS��������ʱ�����NR1:Ĭ��0���Ӵ�����ʱ��<0>:NMOS�����½�ʱ�����NF0:Ĭ��1���Ӵ��½�ʱ�� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK0_REG16_ADJ_T;    /* BUCK0����16�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_adj_rlx              : 4; /* [3..0] buck3 LX�����˲�������ڣ�ÿbit�������ƣ�:1�����費���� ��0��������롣 */
        unsigned int    buck3_dbias                : 4; /* [7..4] buck3 <1:0>�Ƚ���ƫ�õ������ڣ�00~11���� buck3<3:2> �Ƚ�����ƫ�õ������ڣ�00~11���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK3_REG1_ADJ_T;    /* BUCK3����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_dmd_sel              : 5; /* [4..0] buck3 dmd��ѡ��000~111���� */
        unsigned int    buck3_ocp_sel              : 2; /* [6..5] buck3 OCP������� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK3_REG2_ADJ_T;    /* BUCK3����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_ocp_toff             : 2; /* [1..0] buck3����ocpʱ��С�ض�ʱ���� ��00~11���� */
        unsigned int    buck3_regop_clamp          : 1; /* [2..2] regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܣ�0����ʹ�ܡ� */
        unsigned int    buck3_dmd_clamp            : 1; /* [3..3] ��dmdǶλʹ���źţ�0�����ϣ�1�������ϡ� */
        unsigned int    buck3_ocp_delay            : 1; /* [4..4] ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned int    buck3_cmp_filter           : 1; /* [5..5] �Ƚ�����ë�̹��ܣ�0������ë�̣�1����ë�̣��� */
        unsigned int    buck3_sleep_dmd            : 1; /* [6..6] ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ơ� */
        unsigned int    buck3_ton_dmd              : 1; /* [7..7] buck3����dmdʱ���ο�����С��ͨʱ�� ��0�������Σ� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK3_REG3_ADJ_T;    /* BUCK3����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_ng_dt_sel            : 1; /* [0..0] buck3 P�ܵ�N������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck3_pg_dt_sel            : 1; /* [1..1] buck3 N�ܵ�P������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck3_nmos_switch          : 1; /* [2..2] buck3 sleep��normal�л�ʱNMOS�����л���ʽ����0����dmdͬʱ�л���1����dmd֮���л��� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK3_REG4_ADJ_T;    /* BUCK3����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_pg_n_sel             : 2; /* [1..0] buck3 P power��������ӦNMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck3_pg_p_sel             : 2; /* [5..4] buck3 P power��������ӦPMOS�����������ڣ�0x0~0x3�������������� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK3_REG5_ADJ_T;    /* BUCK3����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_ng_n_sel             : 2; /* [1..0] buck3 N power��������ӦNMOS�����������ڣ�00~11�������������� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck3_ng_p_sel             : 2; /* [5..4] buck3 N power��������ӦPMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK3_REG6_ADJ_T;    /* BUCK3����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_adj_clx              : 2; /* [1..0] buck3 LX�����˲����ݵ��ڣ�11������ȫ���룬00������ȫ�����룩 */
        unsigned int    buck3_ocp_dis              : 1; /* [2..2] buck3 �ڲ�OCP��·�����źţ�0�������Σ�1������ �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    buck3_ton                  : 2; /* [5..4] buck3��С��ͨʱ�䡣 */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK3_REG7_ADJ_T;    /* BUCK3����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_sleep_ng             : 1; /* [0..0] buck3���ڹر�NMOS power�ܡ�0����ǿ�ƹرգ�1��ǿ�ƹر� */
        unsigned int    buck3_bias_reg             : 1; /* [1..1] buck3�ڲ�regulator�������ڣ�0:0.5uA��1:1uA�� */
        unsigned int    buck3_short_pdp            : 1; /* [2..2] ��·�������μĴ�����0:ʹ�ܶ�·������1:��ʹ�ܶ�·������ */
        unsigned int    buck3_reg_ss               : 1; /* [3..3] buck3������ʱ�ڲ�regulator״̬��0������״̬��1����λ���淴���� */
        unsigned int    buck3_dt_sel               : 2; /* [5..4] buck3����ʱ����ڣ�ÿbit�������ƣ���1���������ӳ� ��0�������ӳ�5ns �� */
        unsigned int    buck3_regop_c              : 1; /* [6..6] buck3�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate�� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK3_REG8_ADJ_T;    /* BUCK3����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_reg_dr               : 3; /* [2..0] buck3�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    buck3_en_reg               : 1; /* [3..3] buck3�ڲ����ȵ�����ʹ���źţ�0��ʹ�ܣ�1����ʹ�ܡ� */
        unsigned int    buck3_dmd_ton              : 3; /* [6..4] buck3����dmdʱ�ļ��뵼ͨʱ������000~111���� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK3_REG9_ADJ_T;    /* BUCK3����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_filter_ton           : 2; /* [1..0] �Ƚ�����ë�̣�00~11���� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck3_reg_r                : 2; /* [5..4] buck3�ڲ�regulator���裬���ڵ���regulator���� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK3_REG10_ADJ_T;    /* BUCK3����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_ocp_tran_enhance     : 8; /* [7..0] buck5 ocp ��ر�ʱ�����                                                               00000000��Ĭ��                                                                                             00000001���ɻ�·���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK5_REG0_ADJ_T;    /* BUCK3����12�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_adj_rlx              : 4; /* [3..0] buck4 LX�����˲�������ڣ�ÿbit�������ƣ�:1�����費���� ��0��������롣 */
        unsigned int    buck4_dbias                : 4; /* [7..4] buck4 <1:0>�Ƚ���ƫ�õ������ڣ�00~11���� buck4<3:2> �Ƚ�����ƫ�õ������ڣ�00~11���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK4_REG1_ADJ_T;    /* BUCK4����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_dmd_sel              : 5; /* [4..0] buck4 dmd��ѡ��000~111���� */
        unsigned int    buck4_ocp_sel              : 2; /* [6..5] buck4 OCP����� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK4_REG2_ADJ_T;    /* BUCK4����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_ocp_toff             : 2; /* [1..0] buck4����ocpʱ��С�ض�ʱ���� ��00~11���� */
        unsigned int    buck4_regop_clamp          : 1; /* [2..2] regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܣ�0����ʹ�ܡ� */
        unsigned int    buck4_dmd_clamp            : 1; /* [3..3] ��dmdǶλʹ���źţ�0�����ϣ�1�������ϡ� */
        unsigned int    buck4_ocp_delay            : 1; /* [4..4] ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned int    buck4_cmp_filter           : 1; /* [5..5] �Ƚ�����ë�̹��ܣ�0������ë�̣�1����ë�̣� */
        unsigned int    buck4_sleep_dmd            : 1; /* [6..6] ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ơ� */
        unsigned int    buck4_ton_dmd              : 1; /* [7..7] buck4����dmdʱ���ο�����С��ͨʱ�� ��0�������Σ� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK4_REG3_ADJ_T;    /* BUCK4����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_ng_dt_sel            : 1; /* [0..0] buck4 P�ܵ�N������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck4_pg_dt_sel            : 1; /* [1..1] buck4 N�ܵ�P������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck4_nmos_switch          : 1; /* [2..2] buck4 sleep��normal�л�ʱNMOS�����л���ʽ����0����dmdͬʱ�л���1����dmd֮���л��� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK4_REG4_ADJ_T;    /* BUCK4����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_pg_n_sel             : 2; /* [1..0] buck4 P power��������ӦNMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck4_pg_p_sel             : 2; /* [5..4] buck4 P power��������ӦPMOS�����������ڣ�0x0~0x3�������������� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK4_REG5_ADJ_T;    /* BUCK4����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_ng_n_sel             : 2; /* [1..0] buck4 N power��������ӦNMOS�����������ڣ�0x0~0x3������������)�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck4_ng_p_sel             : 2; /* [5..4] buck4 N power��������ӦPMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK4_REG6_ADJ_T;    /* BUCK4����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_adj_clx              : 2; /* [1..0] buck4 LX�����˲����ݵ��ڣ�11������ȫ���룬00������ȫ�����룩 */
        unsigned int    buck4_ocp_dis              : 1; /* [2..2] buck4 �ڲ�OCP��·�����źţ�0�������Σ�1������ �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    buck4_ton                  : 2; /* [5..4] buck4��С��ͨʱ�䡣 */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK4_REG7_ADJ_T;    /* BUCK4����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_sleep_ng             : 1; /* [0..0] buck4���ڹر�NMOS power�ܡ�0����ǿ�ƹرգ�1��ǿ�ƹر� */
        unsigned int    buck4_bias_reg             : 1; /* [1..1] buck4�ڲ�regulator�������ڣ�0:0.5uA��1:1uA�� */
        unsigned int    buck4_short_pdp            : 1; /* [2..2] ��·�������μĴ�����0:ʹ�ܶ�·������1:��ʹ�ܶ�·������ */
        unsigned int    buck4_reg_ss               : 1; /* [3..3] buck4������ʱ�ڲ�regulator״̬��0������״̬��1����λ���淴���� */
        unsigned int    buck4_dt_sel               : 2; /* [5..4] buck4����ʱ����ڣ�ÿbit�������ƣ���1���������ӳ� ��0�������ӳ�5ns �� */
        unsigned int    buck4_regop_c              : 1; /* [6..6] buck4�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate�� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK4_REG8_ADJ_T;    /* BUCK4����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_reg_dr               : 3; /* [2..0] buck4�ڲ�regulator���裬���ڵ���regulator�������ȷ�Χ�� */
        unsigned int    buck4_en_reg               : 1; /* [3..3] buck4�ڲ����ȵ�����ʹ���źţ�0��ʹ�ܣ�1����ʹ�ܡ� */
        unsigned int    buck4_dmd_ton              : 3; /* [6..4] buck4����dmdʱ�ļ��뵼ͨʱ������000~111���� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK4_REG9_ADJ_T;    /* BUCK4����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_filter_ton           : 2; /* [1..0] �Ƚ�����ë�̣�00~11���� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck4_reg_r                : 2; /* [5..4] buck4�ڲ�regulator���裬���ڵ���regulator���� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK4_REG10_ADJ_T;    /* BUCK4����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_reserve              : 8; /* [7..0] buck4���üĴ��� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK4_REG12_ADJ_T;    /* BUCK4����12�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_ocp_n_sel            : 4; /* [3..0] buck5 nocp����� */
        unsigned int    reserved                   : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK5_REG1_ADJ_T;    /* BUCK5����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 5; /* [4..0] ���� */
        unsigned int    buck5_ocp_sel              : 2; /* [6..5] buck5 ��ocp��λ���ڼĴ��� */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK5_REG2_ADJ_T;    /* BUCK5����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_dmd_sel              : 2; /* [1..0] 00:67mA01:101mA10:-50mA11:34mA  Defaut */
        unsigned int    reserved                   : 6; /* [7..2] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK5_REG3_ADJ_T;    /* BUCK5����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_vz_sel               : 1; /* [0..0] EA���ǯλ��ѹ���ڼĴ��� */
        unsigned int    buck5_ocp_sHI6559eld           : 1; /* [1..1] buck5 ocp������������0���й�����������1���޹����������� */
        unsigned int    buck5_sft_sel              : 1; /* [2..2] buck5������ʱ��ѡ��Ĵ��� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK5_REG4_ADJ_T;    /* BUCK5����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_sg_sel               : 2; /* [1..0] б�²�������������00~11:������������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck5_sc_sel               : 2; /* [5..4] б�²���������� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK5_REG5_ADJ_T;    /* BUCK5����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved_1                 : 2; /* [1..0] ���� */
        unsigned int    buck5_shortn               : 1; /* [2..2] buck5�Ķ�·���������ź�0���ж�·����1���޶�·���� */
        unsigned int    reserved_0                 : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK5_REG6_ADJ_T;    /* BUCK5����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_ccm_ctrl             : 1; /* [0..0] buck5��ǿ������ģʽ����1��ǿ������ģʽ���ܹر�0��ǿ������ģʽ���ܿ��� */
        unsigned int    buck5_ocp_delay_sel        : 1; /* [1..1] buck5 ocp�˲�ʱ��ѡ��                                                                       0��Ĭ��                                                                                               1����ʱ����һ�� */
        unsigned int    buck5_ocp_mode_sel         : 1; /* [2..2] buck5 ocpģʽѡ��                                                                             0��p�ܺ�n��ͬʱ���                                                                           1�����p�ܣ���ʱ600ns */
        unsigned int    buck5_ocp_set              : 1; /* [3..3] buck5 ocp���Ϸ���ѡ��                                                                     0���Ϸ���                                                                                             1���·��� */
        unsigned int    reserved_1                 : 2; /* [5..4] ���� */
        unsigned int    buck5_cs_lxb               : 1; /* [6..6] current sense�����ź�ѡ��Ĵ���                                                      0��LX�����ؿ���current sense                                                         1������LX�����ؿ���current sense */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK5_REG7_ADJ_T;    /* BUCK5����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_ocp_p_sel            : 3; /* [2..0] buck5 pocp����� */
        unsigned int    buck5_dt_sel               : 1; /* [3..3] BUCK5����ʱ�����0��Ĭ��1����������ʱ�䣨5ns�� */
        unsigned int    buck5_nmos_ocp_sel         : 1; /* [4..4] buck5 nmos ocpѡ���ź�                                                                   0��ѡ��nmos ocp                                                                               1������nmos ocp */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK5_REG8_ADJ_T;    /* BUCK5����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_comp_adj             : 8; /* [7..0] BUCK5�ȶ��Ե��ڼĴ���<7>: ��������GATE_DRV1������0����ǿ<6>: EA���ǯλʹ��                                                                0���ر�ǯλ����                                                                             1������ǯλ���� <5>: ������������OCP�Ƿ��ϱ�                                                            0�������ϱ�                                                                            1���������ϱ�<4��0>�����ڵ���EA�Ŀ絼�������ĵ��� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK5_REG9_ADJ_T;    /* BUCK5����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_reserve1             : 6; /* [5..0] <7> : VO�������                                                                                      д1�������Ϊ1.2V                                                                              <6>��isens ���������Ĵ���                                                             0������                                                                                                      1���ر�                                                                                              <5>��PWM�Ƚ����������ڼĴ���                                                        0��1uA                                                                                                 1��2uA                                                                                                         <4>����ocp��λ���ڼĴ���                                                                      0��Ĭ��ֵ                                                                                              1������350mA                                                                                         <3>��current sense�˷Ų������ڼĴ���                                                0�����Ⱥ��ٶ���ǿ                                                                               1���������                                                                                      <2>��isens����˲�����ѡ��Ĵ���                                                             0�����˲�����                                                                                    1�����˲�����                                                                                         <1>��current sense �˷�դ���˲�����ѡ��Ĵ���                          0��Ĭ���˲�����                                                                                    1�������˲�����                                                                                      <0>��current sense ��ʱѡ��Ĵ���                                                  0������ʱ                                                                                                1������5ns��ʱ */
        unsigned int    reserved                   : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK5_REG10_ADJ_T;    /* BUCK5����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_adj_rlx              : 4; /* [3..0] buck6 LX�����˲�������ڣ�ÿbit�������ƣ�:1�����費���� ��0��������롣 */
        unsigned int    buck6_dbias                : 4; /* [7..4] buck6 <1:0>�Ƚ���ƫ�õ������ڣ�00~11���� buck6<3:2> �Ƚ�����ƫ�õ������ڣ�00~11���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK6_REG1_ADJ_T;    /* BUCK6����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_dmd_sel              : 5; /* [4..0] buck6 dmd��ѡ��000~111���� */
        unsigned int    buck6_ocp_sel              : 2; /* [6..5] buck6 OCP����� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK6_REG2_ADJ_T;    /* BUCK6����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_ocp_toff             : 2; /* [1..0] buck6����ocpʱ��С�ض�ʱ���� ��00~11���� */
        unsigned int    buck6_regop_clamp          : 1; /* [2..2] regulator Ƕλ��·ʹ�ܣ�1��ʹ�ܣ�0����ʹ�ܡ� */
        unsigned int    buck6_dmd_clamp            : 1; /* [3..3] dmdǶλʹ���źţ�0�����ϣ�1�������ϣ� */
        unsigned int    buck6_ocp_delay            : 1; /* [4..4] ocp����ʱ���ӳ�20ns�źţ�0�����ӳ���1���ӳ��� */
        unsigned int    buck6_cmp_filter           : 1; /* [5..5] �Ƚ�����ë�̹��ܣ�0������ë�̣�1����ë�̣� */
        unsigned int    buck6_sleep_dmd            : 1; /* [6..6] ������ģʽ��ǿ��NMOS�ܹرգ�0����ǿ�ƣ�1��ǿ�ơ� */
        unsigned int    buck6_ton_dmd              : 1; /* [7..7] buck6����dmdʱ���ο�����С��ͨʱ�� ��0�������Σ� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK6_REG3_ADJ_T;    /* BUCK6����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_ng_dt_sel            : 1; /* [0..0] buck6 P�ܵ�N������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck6_pg_dt_sel            : 1; /* [1..1] buck6 N�ܵ�P������ģʽѡ��ÿbit�������ƣ���0������������������ģʽ��1����������������ģʽ�� */
        unsigned int    buck6_nmos_switch          : 1; /* [2..2] buck6 sleep��normal�л�ʱNMOS�����л���ʽ����0����dmdͬʱ�л���1����dmd֮���л��� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK6_REG4_ADJ_T;    /* BUCK6����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_pg_n_sel             : 2; /* [1..0] buck6 P power��������ӦNMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck6_pg_p_sel             : 2; /* [5..4] buck6 P power��������ӦPMOS�����������ڣ�0x0~0x3�������������� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK6_REG5_ADJ_T;    /* BUCK6����5�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_ng_n_sel             : 2; /* [1..0] buck6 N power��������ӦNMOS�����������ڣ�0x0~0x3������������)�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck6_ng_p_sel             : 2; /* [5..4] buck6 N power��������ӦPMOS�����������ڣ�0x0~0x3��С������������ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK6_REG6_ADJ_T;    /* BUCK6����6�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_adj_clx              : 2; /* [1..0] buck6 LX�����˲����ݵ��ڣ�11������ȫ���룬00������ȫ�����룩 */
        unsigned int    buck6_ocp_dis              : 1; /* [2..2] buck6 �ڲ�OCP��·�����źţ�0�������Σ�1������ �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    buck6_ton                  : 2; /* [5..4] buck6��С��ͨʱ�䡣 */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK6_REG7_ADJ_T;    /* BUCK6����7�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_sleep_ng             : 1; /* [0..0] buck6���ڹر�NMOS power�ܡ�0����ǿ�ƹرգ�1��ǿ�ƹر� */
        unsigned int    buck6_bias_reg             : 1; /* [1..1] buck6�ڲ�regulator�������ڣ�0:0.5uA��1:1uA�� */
        unsigned int    buck6_short_pdp            : 1; /* [2..2] ��·�������μĴ�����0:ʹ�ܶ�·������1:��ʹ�ܶ�·������ */
        unsigned int    buck6_reg_ss               : 1; /* [3..3] buck6������ʱ�ڲ�regulator״̬��0������״̬��1����λ���淴���� */
        unsigned int    buck6_dt_sel               : 2; /* [5..4] buck6����ʱ����ڣ�ÿbit�������ƣ���1���������ӳ� ��0�������ӳ�5ns �� */
        unsigned int    buck6_regop_c              : 1; /* [6..6] buck6�ڲ�regulator OP������ݣ����ڵ���OP��slew-rate�� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK6_REG8_ADJ_T;    /* BUCK6����8�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_reg_dr               : 3; /* [2..0] buck6�ڲ�regulator���裬���ڵ���regulator���� */
        unsigned int    buck6_en_reg               : 1; /* [3..3] buck6�ڲ����ȵ�����ʹ���źţ�0��ʹ�ܣ�1����ʹ�ܡ� */
        unsigned int    buck6_dmd_ton              : 3; /* [6..4] buck6����dmdʱ�ļ��뵼ͨʱ������000~111���� */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK6_REG9_ADJ_T;    /* BUCK6����9�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_filter_ton           : 2; /* [1..0] �Ƚ�����ë�̣�00~11���� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    buck6_reg_r                : 2; /* [5..4] buck6�ڲ�regulator���裬���ڵ���regulator���� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK6_REG10_ADJ_T;    /* BUCK6����10�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_reserve              : 8; /* [7..0] buck6���üĴ��� */
    } bits;
    unsigned int    u32;
}HI6559_BUCK6_REG12_ADJ_T;    /* BUCK6����12�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    buck0_dv                   : 8; /* [7..0] BUCK0�����ѹ����                                                                              Ĭ�����1.5V  00001100                    00000000��001111110.9V~4.05V64steps��50mV/Step  */
    } bits;
    unsigned int    u32;
}HI6559_VSET_BUCK0_ADJ_T;    /* BUCK0��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck3_dv                   : 6; /* [5..0] buck3�����ѹ����Ĭ�����0.9V  011001   000000��111111��Ӧ0.7V��1.204V64steps��8mV/Step011001 (OTP=0)100110 (OTP=1) */
        unsigned int    reserved                   : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_VSET_BUCK3_ADJ_T;    /* BUCK3��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck4_dv                   : 4; /* [3..0] buck4�����ѹ����:    Ĭ�����1.225V  0001                    0000��1111��Ӧ1.2V��1.575V16steps��25mV/Step */
        unsigned int    reserved                   : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6559_VSET_BUCK4_ADJ_T;    /* BUCK3��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck5_dv                   : 8; /* [7..0] BUCK5�����ѹ����                                                                              Ĭ�����2.2V  00001000                    00000000��00001111��Ӧ1.5/1.6/1.7/1.8/1.85/1.9/2.0/2.12.2/2.25/2.3/2.35/2.5/2.8/2.85/3.3 */
    } bits;
    unsigned int    u32;
}HI6559_VSET_BUCK5_ADJ_T;    /* BUCK5��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    buck6_dv                   : 4; /* [3..0] buck6�����ѹ����:Ĭ�����1.825V  00010000��1111��Ӧ1.8V~2.175V16steps��25mV/Step */
        unsigned int    reserved                   : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6559_VSET_BUCK6_ADJ_T;    /* BUCK6��ѹ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo1                  : 3; /* [2..0] LDO1��ѹ���ڣ�0x0: 1.80V ��0x1: 2.50V ��0x2: 2.60V ��0x3: 2.70V ��0x4: 2.80V ��0x5: 2.85V �� 0x6: 2.90V ��0x7: 3.00V�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO1_REG_ADJ_T;    /* LDO1���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo3                  : 3; /* [2..0] LDO3�����ѹ����0.825/0.85/0.875/0.9/0.925/0.95/0.975/1.0 */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo3                 : 3; /* [6..4] LDO3���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO3_REG_ADJ_T;    /* LDO3���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo6                  : 3; /* [2..0] LDO6��ѹ���ڣ�0x0: 1.50V ��0x1: 1.80V ��0x2: 1.85V ��0x3: 2.20V ��0x4: 2.50V ��0x5: 2.80V �� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO6_REG_ADJ_T;    /* LDO6���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo7                  : 3; /* [2..0] LDO7�����ѹ����1.8/1.85/2.8/2.85/2.9/2.95/3.0/3.3 */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO7_REG_ADJ_T;    /* LDO7���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo8                  : 3; /* [2..0] LDO8��ѹ���ڣ�0x0: 1.10V ��0x1: 1.20V ��0x2: 1.25V ��0x3: 1.275V ��0x4: 1.30V ��0x5: 1.325V ��0x6: 1.35V ��0x7��1.375V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo8                 : 3; /* [6..4] LDO8���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO8_REG_ADJ_T;    /* LDO8���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo9                  : 3; /* [2..0] LDO9��ѹ���ڣ�0x0: 1.80V ��0x1: 1.85V ��0x2: 2.80V ��0x3: 2.85V ��0x4: 2.90V ��0x5: 2.95V ��0x6: 3.00V ��0x7: 3.05V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo9                 : 3; /* [6..4] LDO9���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO9_REG_ADJ_T;    /* LDO9���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo10                 : 3; /* [2..0] LDO10�����ѹ����2.8/2.85/2.9/2.95/3.0/3.05/3.1/3.3 */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo10                : 3; /* [6..4] LDO10���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO10_REG_ADJ_T;    /* LDO10���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo11                 : 3; /* [2..0] LDO11�����ѹ����1.8/1.85/2.2/2.8/2.85/2.9/3.0/3.3�� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo11                : 3; /* [6..4] LDO11���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO11_REG_ADJ_T;    /* LDO11���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo12                 : 3; /* [2..0] LDO12��ѹ���ڣ�0x0: 3.00V ��0x1: 3.05V ��0x2: 3.10V ��0x3: 3.15V ��0x4: 3.20V ��0x5: 3.25V ��0x6: 3.30V ��0x7: 3.35V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo12                : 3; /* [6..4] LDO12���ص����ʲ��������� */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO12_REG_ADJ_T;    /* LDO12���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo13                 : 3; /* [2..0] LDO13��ѹ���ڣ�0x0: 1.80V ��0x1: 2.50V ��0x2: 2.60V ��0x3: 2.70V ��0x4: 2.80V ��0x5: 2.85V �� 0x6: 2.90V ��0x7: 3.00V�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO13_REG_ADJ_T;    /* LDO13���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo14                 : 3; /* [2..0] LDO14��ѹ���ڣ�0x0: 1.80V ��0x1: 2.20V ��0x2: 2.60V ��0x3: 2.70V ��0x4: 2.80V ��0x5: 2.85V �� 0x6: 2.90V ��0x7: 3.00V�� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo14                : 3; /* [6..4] LDO14���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO14_REG_ADJ_T;    /* LDO14���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo22                 : 3; /* [2..0] LDO22�����ѹ����1.2/1.225/1.25/1.3/1.425/1.5 */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO22_REG_ADJ_T;    /* LDO22���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo23                 : 3; /* [2..0] LDO23��ѹ���ڣ�0x0: 1.50V ��0x1: 1.80V ��0x2: 1.85V ��0x3: 1.90V ��0x4: 1.95V �� 0x5: 2.50V ��0x6: 2.80V ��0x7: 2.85V �� */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    vrset_ldo23                : 3; /* [6..4] LDO23���ص����ʲ���������5mV / Step */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO23_REG_ADJ_T;    /* LDO23���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_ldo24                 : 3; /* [2..0] LDO24��ѹ���ڣ�0x0: 2.80V ��0x1: 2.85V ��0x2: 2.90V ��0x3: 2.95V ��0x4: 3.00V ��0x5: 3.05V ��0x6: 3.10V ��0x7: 3.15V �� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LDO24_REG_ADJ_T;    /* LDO24���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    vset_pmua                  : 3; /* [2..0] PMUA��ѹ���ڣ�0x0: 2.90V ��0x1: 3.00V ��0x2: 3.05V ��0x3: 3.10V ��0x4: 3.15V �� 0x5: 3.20V ��0x6: 3.25V ��0x7: 3.30V�� */
        unsigned int    eco_pmua                   : 1; /* [3..3] PMUA����ECOģʽ�����ź�:0������normalģʽ��1������ecoģʽ�� */
        unsigned int    reserved                   : 4; /* [7..4] ���� */
    } bits;
    unsigned int    u32;
}HI6559_PMUA_REG_ADJ_T;    /* PMUA���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    sstset_lvs9                : 2; /* [1..0] LVS9�����ٶȵ��ڣ�11��죬00���� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    sstset_lvs7                : 2; /* [5..4] LVS7�����ٶȵ��ڣ�11��죬00���� */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_LVS_ADJ1_T;    /* LVS����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    bg_test                    : 4; /* [3..0] ��׼����ģʽԤ�� */
        unsigned int    bg_sleep                   : 1; /* [4..4] 0��ref_top�������� ��1��ref_top����sleepģʽ�� */
        unsigned int    reserved                   : 3; /* [7..5] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BANDGAP_THSD_ADJ1_T;    /* BANDGAP��THSD����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_tmp_int                 : 2; /* [1..0] 0x:THSD���±���ģ��رգ�10:THSD���±���ģ�鿪����11:THSD�ĵ͹���ģʽ���ߵ�ƽΪ10ms,����Ϊ1s�������ź� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    thsd_set_tmp               : 2; /* [5..4] �¶ȱ���ģ�鱨���¶����á�00:  105�棻01:  115�棻10:  125�棻 11:   135�棻                     Ĭ������Ϊ125�档 */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_BANDGAP_THSD_ADJ2_T;    /* BANDGAP��THSD����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_dr3_int                 : 1; /* [0..0] 0:  �ر�DR3��1: ����DR3�� */
        unsigned int    dr3_mode                   : 1; /* [1..1] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR3����ģʽ��    */
        unsigned int    en_dr4_int                 : 1; /* [2..2] 0:  �ر�DR4��1: ����DR4�� */
        unsigned int    dr4_mode                   : 1; /* [3..3] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR4����ģʽ��    */
        unsigned int    en_dr5_int                 : 1; /* [4..4] 0:  �ر�DR5��1: ����DR5�� */
        unsigned int    dr5_mode                   : 1; /* [5..5] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR5����ģʽ��    */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DR_FLA_CTRL1_T;    /* DR��˸ģʽ����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    en_dr1_int                 : 1; /* [0..0] 0:  �ر�DR1��1: ����DR1  �� */
        unsigned int    dr1_mode                   : 1; /* [1..1] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR1����ģʽ�� */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    en_dr2_int                 : 1; /* [4..4] 0:  �ر�DR2��1: ����DR2�� */
        unsigned int    dr2_mode                   : 1; /* [5..5] 0: �ر�����ģʽ(��ʱ����Ϊ�������)��1:  ����DR2����ģʽ��    */
        unsigned int    reserved_0                 : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DR_FLA_CTRL2_T;    /* DR��˸ģʽ����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    flash_period               : 8; /* [7..0] ��˸����T = ����ֵ *31.25ms�� */
    } bits;
    unsigned int    u32;
}HI6559_FLASH_PERIOD_T;    /* DR��˸ģʽ���ڵ��ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    flash_on                   : 8; /* [7..0] ����ʱ��t =����ֵ *7.8125ms�� */
    } bits;
    unsigned int    u32;
}HI6559_FLASH_ON_T;    /* DR��˸ģʽ����ʱ����ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr1_mode_sel               : 1; /* [0..0] 0: DR1�����ں�������ģʽ��1��DR1��������˸ģʽ�� */
        unsigned int    dr2_mode_sel               : 1; /* [1..1] 0: DR2�����ں�������ģʽ��1��DR2��������˸ģʽ�� */
        unsigned int    dr3_mode_sel               : 1; /* [2..2] 0: DR3�����ں�������ģʽ��1��DR3��������˸ģʽ�� */
        unsigned int    dr4_mode_sel               : 1; /* [3..3] 0: DR4�����ں�������ģʽ��1��DR4��������˸ģʽ�� */
        unsigned int    dr5_mode_sel               : 1; /* [4..4] 0: DR5�����ں�������ģʽ��1��DR5��������˸ģʽ�� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DR_MODE_SEL_T;    /* DR��ģʽѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr1_en                     : 1; /* [0..0] 0��dr1�ر� �� 1��dr1ʹ�ܣ�dr1_flash_en = 1,��˸ ��dr1_flash_en = 0,���� �� */
        unsigned int    dr1_flash_en               : 1; /* [1..1] 0��dr1����˸��1��dr1��˸ */
        unsigned int    reserved_1                 : 2; /* [3..2] ���� */
        unsigned int    dr2_en                     : 1; /* [4..4] 0��dr2�ر� �� 1��dr2ʹ�ܣ�dr2_flash_en = 1,��˸ ��dr2_flash_en = 0,���� �� */
        unsigned int    dr2_flash_en               : 1; /* [5..5] 0��dr2����˸��1��dr2��˸ */
        unsigned int    reserved_0                 : 2; /* [7..6] ���� */
    } bits;
    unsigned int    u32;
}HI6559_DR_BRE_CTRL_T;    /* DR1/2����ģʽ���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr1_t_off                  : 3; /* [2..0] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    dr1_t_on                   : 3; /* [6..4] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_DR1_TIM_CONF0_T;    /* DR1��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr1_t_rise                 : 3; /* [2..0] 000��0s001��0.25s010��0.5s011��1s100��2s101��2.5s110��3s111��4s */
        unsigned int    reserved_1                 : 1; /* [3..3]  */
        unsigned int    dr1_t_fall                 : 3; /* [6..4] 000��0s001��0.25s010��0.5s011��1s100��2s101��2.5s110��3s111��4s */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_DR1_TIM_CONF1_T;    /* DR1��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr1                   : 3; /* [2..0] DR1�������ڡ�                                    000: 3  mA��001: 6  mA��010: 9  mA��011: 12 mA��100: 15 mA��101: 18 mA��110: 21 mA��111: 24 mA�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_DR1_ISET_T;    /* DR1����ѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr2_t_off                  : 3; /* [2..0] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_1                 : 1; /* [3..3] ���� */
        unsigned int    dr2_t_on                   : 3; /* [6..4] 000��1ms001��0.25s010��0.5s011��1s100��2s101��4s110��4s111������ */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_DR2_TIM_CONF0_T;    /* DR2��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr2_t_rise                 : 3; /* [2..0] 000��0s001��0.25s010��0.5s011��1s100��2s101��2.5s110��3s111��4s */
        unsigned int    reserved_1                 : 1; /* [3..3]  */
        unsigned int    dr2_t_fall                 : 3; /* [6..4] 000��0s001��0.25s010��0.5s011��1s100��2s101��2.5s110��3s111��4s */
        unsigned int    reserved_0                 : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_DR2_TIM_CONF1_T;    /* DR2��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr2                   : 3; /* [2..0] DR2�������ڡ�                                    000: 3  mA��001: 6  mA��010: 9  mA��011: 12 mA��100: 15 mA��101: 18 mA��110: 21 mA��111: 24 mA�� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_DR2_ISET_T;    /* DR2����ѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr3_en                     : 1; /* [0..0] DR3ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    dr4_en                     : 1; /* [1..1] DR4ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    dr5_en                     : 1; /* [2..2] DR5ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    dr_eco_en                  : 1; /* [3..3] ���ƺ����Ƴ�������ʱ�Զ��ر�ʹ�ܡ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DR_LED_CTRL_T;    /* DR3/4/5���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr3_out_ctrl               : 2; /* [1..0] DR3������ơ�00��DR3�������������DR3�ܽţ�01��DR3��DR4����������������DR3�ܽţ�10��DR3��DR4��DR5����������������DR3�ܽţ�11��DR4��DR5����������������DR3�ܽš� */
        unsigned int    dr4_out_ctrl               : 2; /* [3..2] DR4������ơ�00��DR4�������������DR4�ܽţ�01��DR3��DR4����������������DR4�ܽţ�10��DR3��DR4��DR5����������������DR4�ܽţ�11��DR4��DR5����������������DR4�ܽš� */
        unsigned int    dr5_out_ctrl               : 2; /* [5..4] DR5������ơ�00��DR5�������������DR5�ܽţ�01��DR3��DR4����������������DR5�ܽţ�10��DR3��DR4��DR5����������������DR5�ܽţ�11��DR4��DR5����������������DR5�ܽš� */
        unsigned int    reserved                   : 2; /* [7..6] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DR_OUT_CTRL_T;    /* DR3/4/5������ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr3                   : 3; /* [2..0] R3����������ڣ�mA����0x0 : 1.0��0x1 : 1.5��0x2 : 2.0��0x3 : 2.5��0x4 : 3.0��0x5 : 3.5��0x6 : 4.0��0x7 : 4.5�� */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DR3_ISET_T;    /* DR3����ѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr3_start_delay            : 8; /* [7..0] DR3������ʱ��Χ��0��32768 ms��step��256ms�� */
    } bits;
    unsigned int    u32;
}HI6559_DR3_START_DEL_T;    /* DR3������ʱ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr3_t_off                  : 4; /* [3..0] DR3����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    dr3_t_on                   : 4; /* [7..4] DR3����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
    } bits;
    unsigned int    u32;
}HI6559_DR3_TIM_CONF0_T;    /* DR3��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr3_t_rise                 : 3; /* [2..0] DR3����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_1                 : 1; /* [3..3] ������ */
        unsigned int    dr3_t_fall                 : 3; /* [6..4] DR3����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DR3_TIM_CONF1_T;    /* DR3��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr4                   : 3; /* [2..0] DR4����������ڣ�mA����0x0 : 1.0��0x1 : 1.5��0x2 : 2.0��0x3 : 2.5��0x4 : 3.0��0x5 : 3.5��0x6 : 4.0��0x7 : 4.5�� */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DR4_ISET_T;    /* DR4����ѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr4_start_delay            : 8; /* [7..0] DR4������ʱ��Χ��0��32768 ms��step��256ms�� */
    } bits;
    unsigned int    u32;
}HI6559_DR4_START_DEL_T;    /* DR4������ʱ���üĴ��� */

typedef union
{
    struct
    {
        unsigned int    dr4_t_off                  : 4; /* [3..0] DR4����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    dr4_t_on                   : 4; /* [7..4] DR4����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
    } bits;
    unsigned int    u32;
}HI6559_DR4_TIM_CONF0_T;    /* DR4��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr4_t_rise                 : 3; /* [2..0] DR4����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_1                 : 1; /* [3..3] ������ */
        unsigned int    dr4_t_fall                 : 3; /* [6..4] DR4����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DR4_TIM_CONF1_T;    /* DR4��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    iset_dr5                   : 3; /* [2..0] DR5����������ڣ�mA����0x0 : 1.0��0x1 : 1.5��0x2 : 2.0��0x3 : 2.5��0x4 : 3.0��0x5 : 3.5��0x6 : 4.0��0x7 : 4.5�� */
        unsigned int    reserved                   : 5; /* [7..3] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DR5_ISET_T;    /* DR5����ѡ��Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    dr5_start_delay            : 8; /* [7..0] DR5������ʱ��Χ��0��32768 ms��step��256ms�� */
    } bits;
    unsigned int    u32;
}HI6559_DR5_START_DEL_T;    /* DR5������ʱ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr5_t_off                  : 4; /* [3..0] DR5����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    dr5_t_on                   : 4; /* [7..4] DR5����ʱ�����á�0000��0s��0001��0.5s��0010��1s��0011��2s��0100��4s��0101��6s��0110��8s��0111��12s��1000��14s��1001��16s��1111������������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
    } bits;
    unsigned int    u32;
}HI6559_DR5_TIM_CONF0_T;    /* DR5��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dr5_t_rise                 : 3; /* [2..0] DR5����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_1                 : 1; /* [3..3] ������ */
        unsigned int    dr5_t_fall                 : 3; /* [6..4] DR5����ʱ�����á�000��0s��001��0.25s��010��0.5s��011��1s��100��2s��101��4s������ֵ���������÷���ʱ�̵�LED���ȣ����������䡣 */
        unsigned int    reserved_0                 : 1; /* [7..7] ������ */
    } bits;
    unsigned int    u32;
}HI6559_DR5_TIM_CONF1_T;    /* DR5��������ʱ�����üĴ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pwe_int                : 1; /* [0..0] OTPд�����źš� */
        unsigned int    otp_pwe_pulse              : 1; /* [1..1] 0�����������壻1����otp_write_mask=1ʱ������һ��310us�ĸߵ�ƽ���塣 */
        unsigned int    otp_write_mask             : 1; /* [2..2] 0:��otp_pwe�źſ���OTP��д������1:��otp_pwe_pulse�źſ���OTP��д������ */
        unsigned int    otp_por_int                : 1; /* [3..3] OTP�������źš�0: otp������1���Զ���32bits otpֵ���ص����µ�Ĵ������档 */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_OTP_CTRL1_T;    /* OTP����1�źżĴ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pa                     : 2; /* [1..0] OTP�ĵ�ַ�źš� */
        unsigned int    otp_ptm                    : 2; /* [3..2] ����ģʽʹ���źš� */
        unsigned int    otp_pprog                  : 1; /* [4..4] ���ģʽʹ���źš� */
        unsigned int    reserved                   : 3; /* [7..5] ������ */
    } bits;
    unsigned int    u32;
}HI6559_OTP_CTRL2_T;    /* OTP����2�źżĴ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdin                   : 8; /* [7..0] OTP������ֵ�Ĵ����� */
    } bits;
    unsigned int    u32;
}HI6559_OTP_PDIN_T;    /* OTPд��ֵ�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob0                  : 8; /* [7..0] OTP_PDOB[7:0] */
    } bits;
    unsigned int    u32;
}HI6559_OTP_PDOB0_T;    /* OTP����ֵ0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob1                  : 8; /* [7..0] OTP_PDOB[15:8] */
    } bits;
    unsigned int    u32;
}HI6559_OTP_PDOB1_T;    /* OTP����ֵ1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob2                  : 8; /* [7..0] OTP_PDOB[23:16] */
    } bits;
    unsigned int    u32;
}HI6559_OTP_PDOB2_T;    /* OTP����ֵ2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    otp_pdob3                  : 8; /* [7..0] OTP_PDOB[31:24] */
    } bits;
    unsigned int    u32;
}HI6559_OTP_PDOB3_T;    /* OTP����ֵ3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_a0                   : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCCR_A0_T;    /* RTC_A����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_a1                   : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCCR_A1_T;    /* RTC_A����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_a2                   : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCCR_A2_T;    /* RTC_A����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_a3                   : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCCR_A3_T;    /* RTC_A����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_a0                   : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCLR_A0_T;    /* RTCLR_A����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_a1                   : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCLR_A1_T;    /* RTCLR_A����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_a2                   : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCLR_A2_T;    /* RTCLR_A����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_a3                   : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCLR_A3_T;    /* RTCLR_A����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_a                    : 1; /* [0..0] ��RTC����λ0����RTC��ǰֵ������ֵȫ��Ϊ0��1����RTC��ǰֵ������ֵΪʵ�ʵ�ǰֵ�� */
        unsigned int    reserved                   : 7; /* [7..1] ������ */
    } bits;
    unsigned int    u32;
}HI6559_RTCCTRL_A_T;    /* RTCCTRL_A���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_a0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_A0_T;    /* RTC_A_A�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_a1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_A1_T;    /* RTC_A_A�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_a2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_A2_T;    /* RTC_A_A�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_a3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_A3_T;    /* RTC_A_A�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_b0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_B0_T;    /* RTC_A_B�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_b1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_B1_T;    /* RTC_A_B�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_b2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_B2_T;    /* RTC_A_B�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_b3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_B3_T;    /* RTC_A_B�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_c0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_C0_T;    /* RTC_A_C�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_c1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_C1_T;    /* RTC_A_C�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_c2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_C2_T;    /* RTC_A_C�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_c3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_C3_T;    /* RTC_A_C�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_d0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_D0_T;    /* RTC_A_D�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_d1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_D1_T;    /* RTC_A_D�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_d2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_D2_T;    /* RTC_A_D�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_d3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_D3_T;    /* RTC_A_D�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_e0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_E0_T;    /* RTC_A_E�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_e1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_E1_T;    /* RTC_A_E�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_e2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_E2_T;    /* RTC_A_E�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_e3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_E3_T;    /* RTC_A_E�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_f0                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ������ʱ������ֵ��bit[7:0]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_F0_T;    /* RTC_A_F�Ƚ�0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_f1                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ������ʱ������ֵ��bit[15:8]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_F1_T;    /* RTC_A_F�Ƚ�1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_f2                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ������ʱ������ֵ��bit[23:16]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_F2_T;    /* RTC_A_F�Ƚ�2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtcmr_a_f3                 : 8; /* [7..0] ����������ʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ������ʱ������ֵ��bit[31:24]�� */
    } bits;
    unsigned int    u32;
}HI6559_RTCMR_A_F3_T;    /* RTC_A_F�Ƚ�3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_na0                  : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[7:0]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6559_RTCCR_NA0_T;    /* RTC_NA����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_na1                  : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[15:8]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6559_RTCCR_NA1_T;    /* RTC_NA����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_na2                  : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[23:16]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6559_RTCCR_NA2_T;    /* RTC_NA����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_na3                  : 8; /* [7..0] ���˼Ĵ��������ص�ǰRTCֵ��32bit���е�bit[31:24]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6559_RTCCR_NA3_T;    /* RTC_NA����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_na0                  : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[7:0]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[7:0]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6559_RTCLR_NA0_T;    /* RTCLR_NA����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_na1                  : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[15:8]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[15:8]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6559_RTCLR_NA1_T;    /* RTCLR_NA����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_na2                  : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[23:16]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[23:16]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6559_RTCLR_NA2_T;    /* RTCLR_NA����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtclr_na3                  : 8; /* [7..0] �����õ�ǰʱ��ֵ��32bit���е�bit[31:24]�����˼Ĵ������������һ�ε�ǰʱ������ֵ��bit[31:24]��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
    } bits;
    unsigned int    u32;
}HI6559_RTCLR_NA3_T;    /* RTCLR_NA����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtccr_na                   : 1; /* [0..0] ��RTC����λ0����RTC��ǰֵ������ֵȫ��Ϊ0��1����RTC��ǰֵ������ֵΪʵ�ʵ�ǰֵ��ע�� ����RTC���������ã���ALARM���ܣ������û����š� */
        unsigned int    reserved                   : 7; /* [7..1] ������ */
    } bits;
    unsigned int    u32;
}HI6559_RTCCTRL_NA_T;    /* RTCCTRL_NA���ƼĴ����� */

typedef union
{
    struct
    {
        unsigned int    version                    : 8; /* [7..0] �汾�Ĵ�������ʾ�汾ΪV100�� */
    } bits;
    unsigned int    u32;
}HI6559_VERSION_T;    /* �汾�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved0                  : 8; /* [7..0] reserved0<7>HKADCǿ�Ƹ�λreserved0<6:0>��׼�޵��Ĵ��� */
    } bits;
    unsigned int    u32;
}HI6559_RESERVED0_T;    /* ����0�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved1                  : 8; /* [7..0] reserved1<7:0>:������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI6559_RESERVED1_T;    /* ����1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved2                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI6559_RESERVED2_T;    /* ����2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved3                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI6559_RESERVED3_T;    /* ����3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    reserved4                  : 8; /* [7..0] ������ ������δ���� */
    } bits;
    unsigned int    u32;
}HI6559_RESERVED4_T;    /* ����4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    htol_mode                  : 4; /* [3..0] 0101���������ϻ�ģʽ ��1010�������ϻ�����ģʽ ����������Ч ��ע���ϻ�����ר�á� */
        unsigned int    reserved                   : 4; /* [7..4] ������ */
    } bits;
    unsigned int    u32;
}HI6559_HTOL_MODE_T;    /* �ϻ�����ģʽ���üĴ����� */

typedef union
{
    struct
    {
        unsigned int    dac_on_sel                 : 1; /* [0..0] 1: DAC�Ŀ�����DAC_SSI�ռ��dac_reg_onoff���ƣ�0������DAC�رա� */
        unsigned int    aux_ibias_cfg              : 2; /* [2..1] AUXDACƫ�õ������ڣ�11���00��С */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_DAC_CTRL_T;    /* DAC���ƼĴ��� */

typedef union
{
    struct
    {
        unsigned int    pdns_sel                   : 3; /* [2..0] ������Ns�ػ�����Ĵ�����000:6s;001:7s;010:8s;011:9s;100:10s;101:11s;110:8s;111:9s�� */
        unsigned int    pdns_mk                    : 1; /* [3..3] �������ػ����μĴ�����0�������γ������ػ���1�����γ������ػ���ע�������������У�һֱ����pwron_n ����ʱ�ſ���ͨ��SSI���������ػ�����λ��һ����pwron_n�ɿ�20ms���λ�Զ������ */
        unsigned int    vsys_uv_adj                : 1; /* [4..4] 0��vsys��ѹ������Ϊ2.85V��1��vsys��ѹ������Ϊ3.0V�� */
        unsigned int    nopwr_rc_off               : 1; /* [5..5] �ر��ڲ�256K RCʱ��:0:ʹ��;1:�رա� */
        unsigned int    pdns_restar_mk             : 1; /* [6..6] �������ػ����������μĴ�����0�������γ������ػ���N+5S������1�����γ������ػ���N+5S������ */
        unsigned int    reserved                   : 1; /* [7..7] ���� */
    } bits;
    unsigned int    u32;
}HI6559_NP_REG_ADJ_T;    /* ���µ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    nopwr_vcoinsl              : 2; /* [1..0] ���õ�س���ѹѡ��00��2.5V��01��3.0V��1X��3.3V�� */
        unsigned int    nopwr_en_backup_chg        : 1; /* [2..2] ���õ�س��ʹ�ܣ�0����ʹ�ܣ�1��ʹ�ܡ� */
        unsigned int    reserved                   : 5; /* [7..3] ���� */
    } bits;
    unsigned int    u32;
}HI6559_NP_REG_CHG_T;    /* ���õ�ط��µ���ڼĴ����� */

typedef union
{
    struct
    {
        unsigned int    no_pwr_resved1             : 8; /* [7..0] ������ ������δ�� */
    } bits;
    unsigned int    u32;
}HI6559_NP_RSVED1_T;    /* ���µ籣��1�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    no_pwr_resved2             : 8; /* [7..0] no_pwr_resved2<7:4>: ������ ������δ��no_pwr_resved2<3:0>: LVS offset�޵��Ĵ����� */
    } bits;
    unsigned int    u32;
}HI6559_NP_RSVED2_T;    /* ���µ籣��2�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    no_pwr_resved3             : 8; /* [7..0] ��ƷԤ���������ü����ã�����PMU�ڲ�����״̬�����κ����ã������ڼ�¼��Ϣ�� */
    } bits;
    unsigned int    u32;
}HI6559_NP_RSVED3_T;    /* ���µ籣��3�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    no_pwr_resved4             : 8; /* [7..0] ��ƷԤ���������ü����ã�����PMU�ڲ�����״̬�����κ����ã������ڼ�¼��Ϣ�� */
    } bits;
    unsigned int    u32;
}HI6559_NP_RSVED4_T;    /* ���µ籣��4�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtc_clk_step_adj1          : 8; /* [7..0] ��ʱ���ȿ��Ե��ڣ����ڷ�Χ+/-192ppm��63��ʱ�ӣ������ڲ���3.05ppm��1��ʱ�ӣ���Ĭ��Ϊ0�� */
    } bits;
    unsigned int    u32;
}HI6559_RTC_ADJ1_T;    /* rtc_adj[7:0]�Ĵ����� */

typedef union
{
    struct
    {
        unsigned int    rtc_clk_step_adj2          : 8; /* [7..0] ��ʱ���ȿ��Ե��ڣ����ڷ�Χ+/-192ppm��63��ʱ�ӣ������ڲ���3.05ppm��1��ʱ�ӣ���Ĭ��Ϊ0�� */
    } bits;
    unsigned int    u32;
}HI6559_RTC_ADJ2_T;    /* rtc_adj[15:8]�Ĵ����� */

#endif // __HI_BBSTAR_H__

