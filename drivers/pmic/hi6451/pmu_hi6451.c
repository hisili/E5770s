

#ifdef __KERNEL__
#include <linux/init.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/clk.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <drv_comm.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

#include <linux/spi/spi.h>
#include <linux/spi/spidev.h>

#elif defined( __VXWORKS__)  || defined(__CMSIS_RTOS)
#include <bsp_spi.h>
#endif

#include <pmu_balong.h>
#include <osl_bio.h>
#include <bsp_ipc.h>
#include <hi_pmu.h>
#include <bsp_pmu.h>
#include <bsp_om.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#include "common_hi6451.h"

/*��ѹԴ��ѹ��λ����λ��uv*/
int HI6451_BUCK1_VSET_LIST[] = { 800000, 900000, 1000000, 1050000, 1100000, 1150000, 1300000, 1800000, 1850000};
int HI6451_BUCK2_VSET_LIST[] = { 900000, 950000, 1000000, 1050000, 1100000, 1150000, 1200000, 1300000};
int HI6451_BUCK3_VSET_LIST[] = { 1200000, 1500000, 1750000, 1800000, 1850000, 1900000, 2500000, 2850000};
int HI6451_BUCK4_VSET_LIST[] = { 2900000, 3000000, 3100000, 3200000, 3300000, 3400000, 3500000, 3600000};
int HI6451_BUCK5_VSET_LIST[] = { 1200000, 1300000, 1500000, 1800000, 2200000, 2250000, 2800000, 2850000};
int HI6451_BUCK6_VSET_LIST[] = { 1200000, 1250000, 1300000, 1350000, 1800000, 1850000, 2500000, 2550000, 3000000, 3050000, 3100000, 3150000, 3200000, 3250000, 3300000, 3450000};
int HI6451_LDO01_VSET_LIST[] = {1100000, 1200000, 1800000, 2200000, 2500000, 2600000, 2800000, 2850000};
int HI6451_LDO02_VSET_LIST[] = {1100000, 1200000, 1800000, 2200000, 2500000, 2600000, 2800000, 2850000};
int HI6451_LDO03_VSET_LIST[] = {1100000, 1200000, 1800000, 2200000, 2500000, 2600000, 2800000, 2850000};
int HI6451_LDO04_VSET_LIST[] = {1100000, 1200000, 1800000, 2200000, 2500000, 2600000, 2800000, 2850000};
int HI6451_LDO05_VSET_LIST[] = {1100000, 1200000, 1800000, 1850000, 2200000, 2250000, 2500000, 2600000};
int HI6451_LDO06_VSET_LIST[] = {2200000, 2300000, 2400000, 2500000, 2600000, 2800000, 2850000};
int HI6451_LDO07_VSET_LIST[] = {1200000, 1800000, 2500000, 2800000, 2850000, 3000000, 3300000, 3500000};
int HI6451_LDO08_VSET_LIST[] = {900000, 1000000, 1100000, 1150000, 1200000, 1250000, 1300000, 1500000};
int HI6451_LDO09_VSET_LIST[] = {900000, 1000000, 1100000, 1150000, 1200000, 1250000, 1300000, 1500000};
int HI6451_LDO10_VSET_LIST[] = {1200000, 1800000, 2500000, 2800000, 2850000, 2900000, 3000000, 3300000};
int HI6451_LDO11_VSET_LIST[] = {1200000, 1250000, 1800000, 1850000, 3000000, 3050000};
int HI6451_LDO12_VSET_LIST[] = {3000000};
int HI6451_LDO13_VSET_LIST[] = {1100000, 1200000, 1800000, 2200000, 2500000, 2600000, 2800000, 3000000};
int HI6451_LDO14_VSET_LIST[] = {1100000, 1200000, 1800000, 2200000, 2500000, 2600000, 2800000, 2850000};
int HI6451_LDO15_VSET_LIST[] = {1100000, 1200000, 1800000, 2200000, 2500000, 2600000, 2800000, 2850000};
int HI6451_DR_ISET[] = {3000, 6000, 9000, 12000, 15000, 18000, 21000, 24000};

/*����һ��PMU_VLTGS���͵�ȫ�����飬�洢���е�ѹԴ�����ԡ�*/
const PMIC_HI6451_VLTGS_ATTR    hi6451_volt_attr[PMIC_HI6451_VOLT_MAX + 1]={
{0,0,0,0,0,0,0,0,NULL},
{HI_PMU_ONOFF5_OFFSET     ,7,HI_PMU_SET_BUCK1_OFFSET,0x0f, 0,ARRAY_SIZE(HI6451_BUCK1_VSET_LIST),HI_PMU_BUCK1_ADJ1_OFFSET    ,7,HI6451_BUCK1_VSET_LIST},
{HI_PMU_ONOFF5_OFFSET     ,5,HI_PMU_SET_BUCK2_OFFSET,0x0f, 0,ARRAY_SIZE(HI6451_BUCK2_VSET_LIST),HI_PMU_BUCK2_ADJ1_OFFSET    ,7,HI6451_BUCK2_VSET_LIST},
{HI_PMU_ONOFF5_OFFSET     ,3,HI_PMU_SET_BUCK3_OFFSET,0x0f, 0,ARRAY_SIZE(HI6451_BUCK3_VSET_LIST),HI_PMU_BUCK3_ADJ1_OFFSET    ,7,HI6451_BUCK3_VSET_LIST},
{HI_PMU_ONOFF5_OFFSET     ,1,HI_PMU_SET_BUCK4_OFFSET,0x07, 0,ARRAY_SIZE(HI6451_BUCK4_VSET_LIST),HI_PMU_BUCK1_2_4_ADJ2_OFFSET,3,HI6451_BUCK4_VSET_LIST},
{HI_PMU_ONOFF6_OFFSET     ,7,HI_PMU_SET_BUCK5_OFFSET,0x07, 0,ARRAY_SIZE(HI6451_BUCK5_VSET_LIST),HI_PMU_BUCK5_ADJ_OFFSET     ,1,HI6451_BUCK5_VSET_LIST},
{HI_PMU_ONOFF6_OFFSET     ,5,HI_PMU_SET_BUCK6_OFFSET,0x0f, 0,ARRAY_SIZE(HI6451_BUCK6_VSET_LIST),HI_PMU_BUCK6_ADJ1_OFFSET    ,7,HI6451_BUCK6_VSET_LIST},
{HI_PMU_ONOFF1_OFFSET     ,7,HI_PMU_SET_LDO1_OFFSET ,0x07, 0,ARRAY_SIZE(HI6451_LDO01_VSET_LIST),HI_PMU_ONOFF1_OFFSET        ,6,HI6451_LDO01_VSET_LIST},
{HI_PMU_ONOFF1_OFFSET     ,5,HI_PMU_SET_LDO2_OFFSET ,0x07, 0,ARRAY_SIZE(HI6451_LDO02_VSET_LIST),HI_PMU_ONOFF1_OFFSET        ,4,HI6451_LDO02_VSET_LIST},
{HI_PMU_ONOFF1_OFFSET     ,3,HI_PMU_SET_LDO3_OFFSET ,0x07, 0,ARRAY_SIZE(HI6451_LDO03_VSET_LIST),HI_PMU_ONOFF1_OFFSET        ,2,HI6451_LDO03_VSET_LIST},
{HI_PMU_ONOFF1_OFFSET     ,1,HI_PMU_SET_LDO4_OFFSET ,0x07, 0,ARRAY_SIZE(HI6451_LDO04_VSET_LIST),HI_PMU_ONOFF1_OFFSET        ,0,HI6451_LDO04_VSET_LIST},
{HI_PMU_ONOFF2_OFFSET     ,7,HI_PMU_SET_LDO5_OFFSET ,0x07, 0,ARRAY_SIZE(HI6451_LDO05_VSET_LIST),HI_PMU_ONOFF2_OFFSET        ,6,HI6451_LDO05_VSET_LIST},
{HI_PMU_ONOFF2_OFFSET     ,5,HI_PMU_SET_LDO6_OFFSET ,0x07, 0,ARRAY_SIZE(HI6451_LDO06_VSET_LIST),HI_PMU_ONOFF2_OFFSET        ,4,HI6451_LDO06_VSET_LIST},
{HI_PMU_ONOFF2_OFFSET     ,3,HI_PMU_SET_LDO7_OFFSET ,0x07, 0,ARRAY_SIZE(HI6451_LDO07_VSET_LIST),HI_PMU_ONOFF2_OFFSET        ,2,HI6451_LDO07_VSET_LIST},
{HI_PMU_ONOFF2_OFFSET     ,1,HI_PMU_SET_LDO8_OFFSET ,0x07, 0,ARRAY_SIZE(HI6451_LDO08_VSET_LIST),HI_PMU_ONOFF2_OFFSET        ,0,HI6451_LDO08_VSET_LIST},
{HI_PMU_ONOFF3_OFFSET     ,7,HI_PMU_SET_LDO9_OFFSET ,0x07, 0,ARRAY_SIZE(HI6451_LDO09_VSET_LIST),HI_PMU_ONOFF3_OFFSET        ,6,HI6451_LDO09_VSET_LIST},
{HI_PMU_ONOFF3_OFFSET     ,5,HI_PMU_SET_LDO10_OFFSET,0x07, 0,ARRAY_SIZE(HI6451_LDO10_VSET_LIST),HI_PMU_ONOFF3_OFFSET        ,4,HI6451_LDO10_VSET_LIST},
{HI_PMU_ONOFF3_OFFSET     ,3,HI_PMU_SET_LDO11_OFFSET,0x07, 0,ARRAY_SIZE(HI6451_LDO11_VSET_LIST),HI_PMU_ONOFF3_OFFSET        ,2,HI6451_LDO11_VSET_LIST},
{HI_PMU_ONOFF3_OFFSET     ,1,                      0,   0, 0,ARRAY_SIZE(HI6451_LDO12_VSET_LIST),HI_PMU_ONOFF3_OFFSET        ,0,HI6451_LDO12_VSET_LIST},
{HI_PMU_ONOFF4_OFFSET     ,5,HI_PMU_SET_LDO13_OFFSET,0x07, 0,ARRAY_SIZE(HI6451_LDO13_VSET_LIST),HI_PMU_ONOFF4_OFFSET        ,4,HI6451_LDO13_VSET_LIST},
{HI_PMU_ONOFF4_OFFSET     ,3,HI_PMU_SET_LDO14_OFFSET,0x07, 0,ARRAY_SIZE(HI6451_LDO14_VSET_LIST),HI_PMU_ONOFF4_OFFSET        ,2,HI6451_LDO14_VSET_LIST},
{HI_PMU_ONOFF4_OFFSET     ,1,HI_PMU_SET_LDO15_OFFSET,0x07, 0,ARRAY_SIZE(HI6451_LDO15_VSET_LIST),HI_PMU_ONOFF4_OFFSET        ,0,HI6451_LDO15_VSET_LIST},
{HI_PMU_DR1_MODE_OFFSET,0,HI_PMU_DR1_MODE_OFFSET ,0x07, 0,        ARRAY_SIZE(HI6451_DR_ISET),PMU_INVAILD_ADDR,PMU_INVAILD_OFFSET,        HI6451_DR_ISET},
{HI_PMU_DR2_MODE_OFFSET,0,HI_PMU_DR2_MODE_OFFSET ,0x07, 0,        ARRAY_SIZE(HI6451_DR_ISET),PMU_INVAILD_ADDR,PMU_INVAILD_OFFSET,        HI6451_DR_ISET},
{HI_PMU_DR3_MODE_OFFSET,0,HI_PMU_DR3_MODE_OFFSET ,0x07, 0,        ARRAY_SIZE(HI6451_DR_ISET),PMU_INVAILD_ADDR,PMU_INVAILD_OFFSET,        HI6451_DR_ISET},
};
/*----------------------------ȫ�ֱ���\������---------------------------------------------*/
typedef unsigned long hi6451_pmuflags_t;
spinlock_t  hi6451_pmu_lock;
#if defined(__KERNEL__) || defined(__VXWORKS__)
#define PMIC_HI6451_SEM_FULL    (1)
#define PMIC_HI6451_SEM_EMPTY   (0)
osl_sem_id    pmu_hi6451_lock;

#define pmu_hi6451_core_lock(flags)      \
    do {                            \
        spin_lock_irqsave(&hi6451_pmu_lock,flags);     \
        bsp_ipc_spin_lock(IPC_SEM_PMU_HI6451);   \
    } while (0)
#define pmu_hi6451_core_unlock(flags)        \
    do {                            \
        bsp_ipc_spin_unlock(IPC_SEM_PMU_HI6451);   \
        spin_unlock_irqrestore(&hi6451_pmu_lock,flags);       \
    } while (0)

#elif defined(__CMSIS_RTOS)
#define pmu_hi6451_core_lock(flags)      \
    do {                                \
        bsp_ipc_spin_lock(IPC_SEM_PMU_HI6451);   \
    } while (0)
#define pmu_hi6451_core_unlock()        \
    do {                            \
        bsp_ipc_spin_unlock(IPC_SEM_PMU_HI6451);   \
    } while (0)

#endif

#ifdef __KERNEL__
/*
 * This supports acccess to SPI devices using normal userspace I/O calls.
 * Note that while traditional UNIX/POSIX I/O semantics are half duplex,
 * and often mask message boundaries, full SPI support requires full duplex
 * transfers.  There are several kinds of internal message boundaries to
 * handle chipselect management and other protocol options.
 *
 * SPI has a character major number assigned.  We allocate minor numbers
 * dynamically using a bitmask.  You must use hotplug tools, such as udev
 * (or mdev with busybox) to create and destroy the /dev/pmu6451B.C device
 * nodes, since there is no fixed association of minor numbers with any
 * particular SPI bus or device.
 */
#define DRIVER_NAME         "pmic_hi6451"
#define PMIC_HI6451_MAJOR           153 /* assigned */
#define N_SPI_MINORS            32  /* ... up to 256 */

static DECLARE_BITMAP(minors, N_SPI_MINORS);

static LIST_HEAD(device_list);
static DEFINE_MUTEX(device_list_lock);

static unsigned bufsiz = 4096;
module_param(bufsiz, uint, S_IRUGO);
MODULE_PARM_DESC(bufsiz, "data bytes in biggest supported SPI message");

/* Bit masks for spi_device.mode management.  Note that incorrect
 * settings for some settings can cause *lots* of trouble for other
 * devices on a shared bus:
 *
 *  - CS_HIGH ... this device will be active when it shouldn't be
 *  - 3WIRE ... when active, it won't behave as it should
 *  - NO_CS ... there will be no explicit message boundaries; this
 *  is completely incompatible with the shared bus model
 *  - READY ... transfers may proceed when they shouldn't.
 *
 * REVISIT should changing those flags be privileged?
 */
#define SPI_MODE_MASK       (SPI_CPHA | SPI_CPOL | SPI_CS_HIGH \
                | SPI_LSB_FIRST | SPI_3WIRE | SPI_LOOP \
                | SPI_NO_CS | SPI_READY)

struct hi6451_spidev_data {
    dev_t           devt;
    spinlock_t      spi_lock;
    struct spi_device   *spi;
    struct list_head    device_entry;

    /* buffer is NULL unless this device is open (users > 0) */
    struct mutex        buf_lock;
    unsigned        users;
    u8          *buffer;
};
struct pmic_hi6451_info {
    struct spi_driver   spidrv;
};
static struct class *pmic_hi6451_class;
struct hi6451_spidev_data *g_pmus6451 = NULL;

static int __devinit hi6451_spidev_probe(struct spi_device *spi)
{
    struct hi6451_spidev_data   *pmu6451;
    int status;
    unsigned long       minor;
    u8  save;
    u32  tmp = 0;
    int retval = 0;

    dev_info(&spi->dev, "hi6451_spidev_probe begin!\n");
    /* Allocate driver data */
    pmu6451 = kzalloc(sizeof(*pmu6451), GFP_KERNEL);
    if (!pmu6451)
        return -ENOMEM;
    g_pmus6451 = pmu6451;
    /* Initialize the driver data */
    pmu6451->spi = spi;
    spin_lock_init(&pmu6451->spi_lock);
    mutex_init(&pmu6451->buf_lock);

    INIT_LIST_HEAD(&pmu6451->device_entry);

    /* If we can allocate a minor number, hook up this device.
     * Reusing minors is fine so long as udev or mdev is working.
     */
    mutex_lock(&device_list_lock);
    minor = find_first_zero_bit(minors, N_SPI_MINORS);
    if (minor < N_SPI_MINORS) {
        struct device *dev;

        pmu6451->devt = MKDEV(PMIC_HI6451_MAJOR, minor);
        dev = device_create(pmic_hi6451_class, &spi->dev, pmu6451->devt,
                    pmu6451, "pmic_hi6451%d.%d",
                    spi->master->bus_num, spi->chip_select);
        status = IS_ERR(dev) ? PTR_ERR(dev) : 0;
    } else {
        dev_dbg(&spi->dev, "no minor number available!\n");
        status = -ENODEV;
    }
    if (status == 0) {
        set_bit(minor, minors);
        list_add(&pmu6451->device_entry, &device_list);

        mutex_unlock(&device_list_lock);

        spi_set_drvdata(spi, pmu6451);

        /*����ģʽ*/
        save = spi->mode;

        tmp = SPI_MODE_3;
        tmp |= spi->mode & ~SPI_MODE_MASK;
        spi->mode = (u8)tmp;
        spi->bits_per_word = 16;
        spi->chip_select = 0;
        spi->max_speed_hz = SPI_BAUT_RATE;

        retval = spi_setup(spi);
        if (retval < 0)
        {
            spi->mode = save;
            dev_info(&spi->dev, "set up failed,now spi mode %02x\n", spi->mode);
        }
        /*  else
        {
        dev_info(&spi->dev, "spi mode %02x\n", spi->mode);
        dev_info(&spi->dev, "spi bits_per_word %02x\n", spi->bits_per_word);
        dev_info(&spi->dev, "spi chip_select %02x\n", spi->chip_select);
        dev_info(&spi->dev, "spi max_speed_hz %02x\n", spi->max_speed_hz);}*/

        dev_info(&spi->dev, "hi6451_spidev_probe ok!\n");
    }
    else
    {
        mutex_unlock(&device_list_lock);
        kfree(pmu6451);
        g_pmus6451 = NULL;
    }

    return status;
}

static int __devexit hi6451_spidev_remove(struct spi_device *spi)
{
    struct hi6451_spidev_data   *pmu6451 = spi_get_drvdata(spi);

    /* make sure ops on existing fds can abort cleanly */
    spin_lock_irq(&pmu6451->spi_lock);
    pmu6451->spi = NULL;
    spi_set_drvdata(spi, NULL);
    spin_unlock_irq(&pmu6451->spi_lock);

    /* prevent new opens */
    mutex_lock(&device_list_lock);
    list_del(&pmu6451->device_entry);
    device_destroy(pmic_hi6451_class, pmu6451->devt);
    clear_bit(MINOR(pmu6451->devt), minors);
    if (pmu6451->users == 0)
        kfree(pmu6451);
    mutex_unlock(&device_list_lock);

    return 0;
}
/*****************************************************************************
* �� �� ��  : bsp_hi6451_reg_write
*
* ��������  : ��pmuоƬ�Ĵ�����д����
*
* �������  : u8 u8Addr����д��ļĴ�����ַ
*                    u8 u8Data����д�������
*
* �������  : ��
*
* �� �� ֵ  : ERROR��д��ʧ��
*             OK��д��ɹ�
*****************************************************************************/
int bsp_hi6451_reg_write( u8 addr, u8 value)
{
    u16 frameSend = (u16)((addr << ADDR_BIT_OFFSET) | value);
    int retval = 0;

    struct hi6451_spidev_data   *pmu6451 = g_pmus6451;
    struct spi_device   *spi;

    if (pmu6451 == NULL)
    {
        pmic_print_error("g_pmus6451 -EINVAL,hi6451_spidev_probe maybe have errors!\n");
        return -1;
    }

    spin_lock_irq(&pmu6451->spi_lock);
    spi = spi_dev_get(pmu6451->spi);
    spin_unlock_irq(&pmu6451->spi_lock);

    if (spi == NULL)
        return -ESHUTDOWN;

    mutex_lock(&pmu6451->buf_lock);

    /*����*/
    bsp_ipc_spin_lock(IPC_SEM_SPI0);
    retval = spi_write(spi,&frameSend,2);
    bsp_ipc_spin_unlock(IPC_SEM_SPI0);

    if (retval < 0)
        dev_info(&spi->dev, "spi_write -EINVAL\n");

    mutex_unlock(&pmu6451->buf_lock);
    spi_dev_put(spi);

    return retval;
}

/*****************************************************************************
* �� �� ��  : bsp_hi6451_reg_read
*
* ��������  : ��pmuоƬ�Ĵ����Ķ�����
*
* �������  : u8Addr�� ����ȡ�ļĴ�����ַ
              pu8Data����ȡ�����ݴ�ŵĵ�ַ
*
* �������  : u8 *pu8Data����ȡ�����ݴ�ŵĵ�ַ
*
* �� �� ֵ  : ERROR����ȡʧ��
*             OK����ȡ�ɹ�
*****************************************************************************/
int  bsp_hi6451_reg_read( u8 addr, u8 *pValue)
{
    u16 frameSend = (u16)((addr << ADDR_BIT_OFFSET) | (0x1 << CMD_BIT_OFFSET));/* ���������֣�8bit�������֣����λbit7Ϊ1������� */
    u16 frameRecv = 0;   /* A11�շ�֡��ʽ��Ϊ16bit������Ч����Ϊ8bit */

    int retval = 0;
    struct hi6451_spidev_data   *pmu6451 = g_pmus6451;
    struct spi_device   *spi;

    /*��������Ч��*/
    if(!pValue)
    {
        pmic_print_error("this funciton args have errors!\n");
        return BSP_PMU_ERROR;
    }
    if (pmu6451 == NULL)
    {
        pmic_print_error("g_pmus6451 -EINVAL,hi6451_spidev_probe maybe have errors!\n");
        return BSP_PMU_ERROR;
    }

    spin_lock_irq(&pmu6451->spi_lock);
    spi = spi_dev_get(pmu6451->spi);
    spin_unlock_irq(&pmu6451->spi_lock);

    if (spi == NULL)
    return -ESHUTDOWN;

    mutex_lock(&pmu6451->buf_lock);

    /*����*/
    bsp_ipc_spin_lock(IPC_SEM_SPI0);
    retval = spi_write_then_read(spi,&frameSend, 2,(void *)&frameRecv, 2);
    bsp_ipc_spin_unlock(IPC_SEM_SPI0);

    if(retval < 0)
    {
        dev_info(&spi->dev, "spi_write_then_read failed!\n");
    }
    *pValue = (u8)frameRecv;
    /*dev_info(&spi->dev, "Read addr %02x,data is %02x\n",addr,*pValue);*/
    mutex_unlock(&pmu6451->buf_lock);
    spi_dev_put(spi);
    return retval;
}


#elif defined( __VXWORKS__)  || defined(__CMSIS_RTOS)
/*****************************************************************************
* �� �� ��  : bsp_hi6451_reg_write
*
* ��������  : ��pmuоƬ�Ĵ�����д����
*
* �������  : u8 u8Addr����д��ļĴ�����ַ
*                    u8 u8Data����д�������
*
* �������  : ��
*
* �� �� ֵ  : ERROR��д��ʧ��
*             OK��д��ɹ�
*****************************************************************************/
s32 bsp_hi6451_reg_write(u8 u8Addr, u8 u8Data)
{
    u16 frameSend = (u16)((u8Addr << ADDR_BIT_OFFSET) | u8Data);
    s32 retval = 0;

    /* ͨ��SPI���豸д������ */
    retval = spi_send(SPI_NO_PMU, SPI_CS_PMU, &frameSend, 1);
    return retval;
}

/*****************************************************************************
* �� �� ��  : bsp_hi6451_reg_read
*
* ��������  : ��pmuоƬ�Ĵ����Ķ�����
*
* �������  : u8Addr�� ����ȡ�ļĴ�����ַ
              pu8Data����ȡ�����ݴ�ŵĵ�ַ
*
* �������  : u8 *pu8Data����ȡ�����ݴ�ŵĵ�ַ
*
* �� �� ֵ  : ERROR����ȡʧ��
*             OK����ȡ�ɹ�
*****************************************************************************/
s32 bsp_hi6451_reg_read(u8 u8Addr, u8 *pu8Data)
{
    u16 frameSend = (u16)((u8Addr << ADDR_BIT_OFFSET) | (0x1 << CMD_BIT_OFFSET));
    u16 frameRecv = 0;   /* A11�շ�֡��ʽ��Ϊ16bit������Ч����Ϊ8bit */
    s32 retval = 0;

    /*��������Ч��*/
    if(!pu8Data)
    {
        return BSP_PMU_ERROR;
    }

    /* ͨ��SPI���豸��ȡ���� */
    retval = spi_recv(SPI_NO_PMU, SPI_CS_PMU, &frameRecv, 1, &frameSend, 1);
    *pu8Data = (u8)frameRecv;

    return retval;
}
#endif
/*****************************************************************************
* �� �� ��  : bsp_hi6451_reg_write_mask
*
* ��������  : ��pmuоƬ�Ĵ����Ķ�����
*
* �������  : addr�� �����õļĴ�����ַ
              value����ȡ�����ݴ�ŵĵ�ַ
*
* �������  : ��
*
* �� �� ֵ  : ERROR������ʧ��
*                   OK�����óɹ�
*****************************************************************************/
int bsp_hi6451_reg_write_mask(u8 addr, u8 value, u8 mask)
{
    u8 reg_tmp = 0;

    bsp_hi6451_reg_read(addr, &reg_tmp);

    reg_tmp &= ~mask;
    reg_tmp |= value;

    return bsp_hi6451_reg_write(addr, reg_tmp);
}

/*****************************************************************************
* �� �� ��  : bsp_hi6451_reg_show
*
* ��������  : ��ʾpmu�Ĵ����ڵ�ֵ
*
* �������  : addr ��Ҫ���ļĴ�����ַ
*
* �������  : ��
*
* �� �� ֵ  : OK�����óɹ�
*          ERROR������ʧ��
*****************************************************************************/
int bsp_hi6451_reg_show(u8 addr)
{
    u8 value = 0;

    if(0 != bsp_hi6451_reg_read(addr, &value))
    {
        pmic_print_error("pmuRead FAIL!!\n");
    }
    else
    {
        pmic_print_error("pmuRead addr %02x value is %02x!!\n",addr,value);
    }

    return value;
}

/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_is_enabled
* ��������  :��ѯĳ·��ѹԴ�Ƿ�����
* �������  :volt_id:��ѹԴid��
* �������  :��
* ����ֵ��   ������������0���رգ�����: ����ʧ��
*
*****************************************************************************/
int bsp_hi6451_volt_is_enabled(int volt_id)
{
    s32 iRet = BSP_OK;
    u8 regval = 0;
    PMIC_HI6451_VLTGS_ATTR  *hi6451_volt;
    /* ��Ч�Լ��*/
    if ((PMIC_HI6451_VOLT_MAX < volt_id) || (PMIC_HI6451_VOLT_MIN > volt_id) )
    {
        pmic_print_error( "PMIC doesn't have this volt,or this volt can not be set!\n");
        return BSP_PMU_ERROR;
    }

    hi6451_volt = &hi6451_volt_attr[volt_id];

    iRet = bsp_hi6451_reg_read(hi6451_volt->onoff_reg_addr, &regval);

    if(iRet)
    {
        pmic_print_error( "bsp_hi6451_regulator_is_enabled  %s  failed!\n");
        return BSP_PMU_ERROR;
    }
    else
        return (regval & (0x1 << hi6451_volt->onoff_bit_offset));
}
/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_enable
*
* ��������  : PMU��ĳ·��ѹ
*
* �������  : Vs_ID ����ԴID
*
* �������  : ��
*
* �� �� ֵ  : OK�����óɹ�
*          ERROR������ʧ��
*****************************************************************************/
int bsp_hi6451_volt_enable(int volt_id)
{
    s32 iRet = BSP_OK;
    u8 regval = 0;
    PMIC_HI6451_VLTGS_ATTR  *hi6451_volt;
    hi6451_pmuflags_t flags;
    /* ��Ч�Լ��*/
    if ((PMIC_HI6451_VOLT_MAX < volt_id) || (PMIC_HI6451_VOLT_MIN > volt_id) )
    {
        pmic_print_error( "PMIC doesn't have this volt,or this volt can not be set!\n");
        return BSP_PMU_ERROR;
    }

    hi6451_volt = &hi6451_volt_attr[volt_id];

    /*���ڻ���+�˼以��*/
    pmu_hi6451_core_lock(flags);

    iRet = bsp_hi6451_reg_read(hi6451_volt->onoff_reg_addr, &regval);
    regval |= (0x1 << hi6451_volt->onoff_bit_offset);
    iRet |= bsp_hi6451_reg_write(hi6451_volt->onoff_reg_addr, regval);

    pmu_hi6451_core_unlock(flags);

    return iRet;
}
/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_disable
*
* ��������  : PMU�ر�sim������RF�ĵ�ѹ
*
* �������  : Vs_ID ����ԴID
*
* �������  : ��
*
* �� �� ֵ  : OK�����óɹ�
*          ERROR������ʧ��
*****************************************************************************/
int bsp_hi6451_volt_disable(int volt_id)
{
    s32 iRet = BSP_PMU_OK;
    u8 regval = 0;
    PMIC_HI6451_VLTGS_ATTR  *hi6451_volt;
    hi6451_pmuflags_t flags;

    /* ��Ч�Լ��*/
    if ((PMIC_HI6451_VOLT_MAX < volt_id) || (PMIC_HI6451_VOLT_MIN > volt_id) )
    {
        pmic_print_error("PMIC doesn't have this volt,or this volt can not be disable!\n");
        return BSP_PMU_ERROR;
    }

    hi6451_volt = &hi6451_volt_attr[volt_id];

    /*���ڻ���+�˼以��*/
    pmu_hi6451_core_lock(flags);

    iRet = bsp_hi6451_reg_read(hi6451_volt->onoff_reg_addr, &regval);
    regval &= ~ (0x1 << hi6451_volt->onoff_bit_offset);
    iRet |= bsp_hi6451_reg_write(hi6451_volt->onoff_reg_addr, regval);

    pmu_hi6451_core_unlock(flags);

    return iRet;
}
/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_set_voltage
*
* ��������  : PMU����sim������RF�ĵ�ѹ
*
* �������  : Vs_ID ����ԴID��ֻ����sim������RF�ĵ�Դ��
*             vltg  �����õĵ�ѹ����λ��uv��sim��ֻ����1800000��3000000����
*
* �������  : ��
*
* �� �� ֵ  : OK�����óɹ�
*          ERROR������ʧ��
*****************************************************************************/
int bsp_hi6451_volt_set_voltage(int volt_id, int min_uV, int max_uV, unsigned *selector)
{
    s32 iRet = BSP_PMU_OK;
    PMIC_HI6451_VLTGS_ATTR  *hi6451_volt;
    hi6451_pmuflags_t flags;

    int i = 0;
    int valid = 0;

    /* ��Ч�Լ��*/
    if ((PMIC_HI6451_VOLT_MAX < volt_id) || (PMIC_HI6451_VOLT_MIN > volt_id) )
    {
        pmic_print_error("PMIC doesn't have this volt,or this volt can not be set!\n");
        return BSP_PMU_ERROR;
    }
    /*LDO12 ��ѹ�̶�3V���������õ�ѹ*/
    if(PMIC_HI6451_LDO12 == volt_id)
    {
        if((min_uV <= 300000)&&(max_uV >= 300000))
        {
            pmic_print_info("PMIC HI6451 LDO12 voltage is fixed at 3V,set 0K!\n", 1, 2, 3, 4, 5, 6);
            return BSP_PMU_OK;
        }
        else
        {
            pmic_print_info("PMIC HI6451 LDO12 voltage is fix at 3V, can not be changed!\n", 1, 2, 3, 4, 5, 6);
            return BSP_PMU_ERROR;
        }
    }

    hi6451_volt = &hi6451_volt_attr[volt_id];

    /* �������2: ��� vltg �Ƿ�Ϊ����Ӧ�ĵ�ѹԴ����Чֵ����ת����ѹֵΪ�Ĵ�������ֵ */
    for (i = 0; i < hi6451_volt->voltage_nums; i++)
    {
        if ((min_uV <= hi6451_volt->voltage_list[i])&&(max_uV >= hi6451_volt->voltage_list[i]))
        {
            valid = 1;
            break;
        }
    }
            /* �������ֵ��Ч�����üĴ��� */
    if (valid)
    {
        *selector = i;
        /*���ڻ���+�˼以��*/
        pmu_hi6451_core_lock(flags);
        bsp_hi6451_reg_write_mask(hi6451_volt->voltage_reg_addr, (u8)((u8)i << hi6451_volt->voltage_bit_offset), hi6451_volt->voltage_bit_mask);
        pmu_hi6451_core_unlock(flags);

        pmic_print_info("volt_id %d's voltage is set at %d uV!\n", volt_id,hi6451_volt->voltage_list[i]);
        return BSP_PMU_OK;
    }
    else
    {
        *selector = 0xffffffff;
        pmic_print_error( "this regulator has no voltage needed!\n");
        return BSP_PMU_ERROR;
    }
    return iRet;
}
/*****************************************************************************
* �� �� ��  : bsp_hi6451_volt_get_voltage
*
* ��������  : PMU���õ�ѹ
*
* �������  : Vs_ID ����ԴID
*             vltg  �����õĵ�ѹ����λ��uv
*
* �������  : ��
*
* �� �� ֵ  : �Ǹ�����ǰ�ĵ�ѹ
*          BSP_PMU_ERROR����ȡ��ѹʧ��
*****************************************************************************/
int bsp_hi6451_volt_get_voltage(int volt_id)
{
    s32 iRet = BSP_PMU_OK;
    u8 regval = 0;
    u32 vltg = 0;
    PMIC_HI6451_VLTGS_ATTR  *hi6451_volt;

    /* ��Ч�Լ��*/
    if ((PMIC_HI6451_VOLT_MAX < volt_id) || (PMIC_HI6451_VOLT_MIN > volt_id) )
    {
        pmic_print_error( "PMIC doesn't have this volt,or this volt can not be set!\n");
        return BSP_PMU_ERROR;
    }
    /*LDO12 ��ѹ�̶�3V���������õ�ѹ*/
    if(PMIC_HI6451_LDO12 == volt_id)
    {
        pmic_print_info("voltage is  %d uV!\n", 3000000);
        return 3000000;
    }

    hi6451_volt = &hi6451_volt_attr[volt_id];


    iRet = bsp_hi6451_reg_read(hi6451_volt->voltage_reg_addr, &regval);
    if(iRet)
    {
        /*error*/
        pmic_print_error( "volt_id %d get voltage failed!\n", volt_id);
        return BSP_PMU_ERROR;
    }
    /* ��ȡ��ѹ��λֵ */
    vltg= (regval & hi6451_volt->voltage_bit_mask) >> hi6451_volt->voltage_bit_offset;
    vltg= hi6451_volt->voltage_list[vltg];
    pmic_print_info("volt_id %d's voltage is  %d uV!\n", volt_id,vltg);

    return vltg;
}
/*only Acore need*/
int bsp_hi6451_volt_list_voltage(int volt_id, unsigned selector)
{
    PMIC_HI6451_VLTGS_ATTR  *hi6451_volt;
    int voltage = 0;

    /* ��Ч�Լ��*/
    if ((PMIC_HI6451_VOLT_MAX < volt_id) || (PMIC_HI6451_VOLT_MIN > volt_id))
    {
        pmic_print_error( "PMIC doesn't have this regulators!\n");
        return BSP_PMU_ERROR;
    }

    hi6451_volt = &hi6451_volt_attr[volt_id];

    /*��鵵λ��Ч��*/
    if (selector >= hi6451_volt->voltage_nums) {
        pmic_print_error( "selector is %d,not exist in volt %d,please input new\n", selector,volt_id);
        return BSP_PMU_ERROR;
    }

    voltage =  hi6451_volt->voltage_list[selector];

    pmic_print_info("volt %d selector %d is %d uV!!\n",volt_id,selector,voltage);

    return voltage;

}
pmu_mode_e bsp_hi6451_volt_get_mode(int volt_id)
{
    PMIC_HI6451_VLTGS_ATTR  *hi6451_volt;
    u8 regval = 0;

    /* ��Ч�Լ��*/
    if ((PMIC_HI6451_VOLT_MAX < volt_id) || (PMIC_HI6451_VOLT_MIN > volt_id))
    {
        pmic_print_error( "PMIC doesn't have this regulators!\n");
        return BSP_PMU_ERROR;
    }

    hi6451_volt = &hi6451_volt_attr[volt_id];

    /*�жϸ�·�Ƿ���ecoģʽ*/
    if((hi6451_volt->eco_reg_addr == PMU_INVAILD_ADDR))
        return PMU_MODE_NONE;/*û��ecoģʽ*/

    /*add lock in core and cores*/
    bsp_hi6451_reg_read(hi6451_volt->eco_reg_addr, &regval);

    if(regval & ((u8) (0x1 << hi6451_volt->eco_bit_offset)))
        return PMU_MODE_ECO;/*eco mode*/
    else
        return PMU_MODE_NORMAL;

}

int bsp_hi6451_volt_set_mode(int volt_id, pmu_mode_e mode)
{
    PMIC_HI6451_VLTGS_ATTR  *hi6451_volt;
    u8 regval = 0;
    s32 iRet = BSP_PMU_OK;
    hi6451_pmuflags_t flags;

    /* ��Ч�Լ��*/
    if ((PMIC_HI6451_VOLT_MAX < volt_id) || (PMIC_HI6451_VOLT_MIN > volt_id))
    {
        pmic_print_error( "PMIC doesn't have this regulators!\n");
        return BSP_PMU_ERROR;
    }

    hi6451_volt = &hi6451_volt_attr[volt_id];

    /*�жϸ�·�Ƿ���ecoģʽ*/
    if((hi6451_volt->eco_reg_addr == PMU_INVAILD_ADDR))
    {
        pmic_print_error("PMIC HI6451 this volt doesn't have eco mode!\n");
        return BSP_PMU_ERROR;
    }
    /*add lock in core and cores*/
    pmu_hi6451_core_lock(flags);

    iRet = bsp_hi6451_reg_read(hi6451_volt->eco_reg_addr, &regval);

    if(iRet)
    {
        pmic_print_error( "%s:bsp_hi6451_reg_read error!\n");
        goto out;
    }

    switch(mode){
    case PMU_MODE_NORMAL:
        pmic_print_info("volt_id[%d] will be set normal mode\n", volt_id);
        regval &= ~((u8)(0x1 << hi6451_volt->eco_bit_offset));
        break;

    case PMU_MODE_ECO:
        pmic_print_info("volt_id[%d] will be set eco mode\n", volt_id);
        regval |= (u8) (0x1 << hi6451_volt->eco_bit_offset);
        break;

    default:
        pmic_print_error( "no support the mode\n");
        iRet = BSP_PMU_ERROR;
        goto out;
    }

    iRet = bsp_hi6451_reg_write(hi6451_volt->eco_reg_addr, regval);
    if(iRet)
    {
        pmic_print_error( "%s:bsp_hi6451_reg_read error!\n");
    }
out:
        pmu_hi6451_core_unlock(flags);
    return iRet;

}

#ifdef __KERNEL__

 int  bsp_pmu_hi6451_init(void)
{
    struct pmic_hi6451_info *pmic_hi6451_info;

    int ret, volt_id;
    int i = 0;

    pmic_hi6451_info = kzalloc(sizeof(*pmic_hi6451_info), GFP_KERNEL);
    if (pmic_hi6451_info == NULL) {
        pmic_print_error("hi6451 regulator kzalloc mem fail,please check!\n");
        return -ENOMEM;
    }

    /*ע��spi�豸����*/
    pmic_hi6451_info->spidrv.driver.name = DRIVER_NAME"_spi";
    pmic_hi6451_info->spidrv.probe    = hi6451_spidev_probe;
    pmic_hi6451_info->spidrv.remove   = __devexit_p(hi6451_spidev_remove);
#if 0
    info->spidrv.shutdown = hi6451_spidev_shutdown;
    info->spidrv.suspend  = hi6451_spidev_suspend;
    info->spidrv.resume   = hi6451_spidev_resume;
#endif
    pmic_hi6451_class = class_create(THIS_MODULE, "hi6451");
    if (IS_ERR(pmic_hi6451_class)) {
        return PTR_ERR(pmic_hi6451_class);
    }
    ret = spi_register_driver(&pmic_hi6451_info->spidrv);
    if (ret < 0) {
        pmic_print_error( "PMIC HI6451 couldn't register SPI Interface\n");
        class_destroy(pmic_hi6451_class);
        return ret;
    }

    //osl_sem_init(PMIC_HI6451_SEM_FULL, &pmu_hi6451_lock);
	spin_lock_init(&hi6451_pmu_lock);
    /*��ʼ��commonģ���lock*/
    bsp_hi6451_common_init();

    /*debug��ʼ��*/
#ifdef ENABLE_DEBUG
    bsp_hi6451_debug_init();
#endif

    return 0;
}

/*subsys_initcall(bsp_pmu_hi6451_init);*/
arch_initcall(bsp_pmu_hi6451_init);
static void __exit bsp_pmu_hi6451_exit(void)
{

}
module_exit(bsp_pmu_hi6451_exit);

#elif defined( __VXWORKS__)
void bsp_pmu_hi6451_init(void)
{
    //osl_sem_init(PMIC_HI6451_SEM_FULL, &pmu_hi6451_lock);
    spin_lock_init(&hi6451_pmu_lock);
    /*��ʼ��commonģ���lock*/
    bsp_hi6451_common_init();
    /*debug��ʼ��*/
#ifdef ENABLE_DEBUG
    bsp_hi6451_debug_init();
#endif
}
#elif defined( __CMSIS_RTOS)
void bsp_pmu_hi6451_init(void)
{
}

#endif
