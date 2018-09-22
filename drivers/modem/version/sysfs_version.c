#include <linux/kernel.h>
#include <linux/device.h>
#include "product_config.h"
#include "bsp_version.h"

/*****************************************************************************
* �� �� ��  : show_product_version
*
* ��������  : ʾ��
*
* �������  : ��
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/

static ssize_t show_product_version(struct device *cdev,struct device_attribute *attr,char *buf)
{

	char product[50]="hello world!";
	/* coverity[secure_coding] */
	return sprintf(buf,"%s",product);
}

static DEVICE_ATTR(version, 0400,show_product_version, NULL);

/*****************************************************************************
* �� �� ��  : show_product_name
*
* ��������  : ��ȡdload_info(�����汾��)
*
* �������  : ��
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/

static ssize_t show_product_name(struct device *cdev,struct device_attribute *attr,char *buf)
{
	//char *product_name=bsp_get_dloadid_version();

	/*TODO:������ע�͹���*/
	//return sprintf(buf,"%s",product_name);
	/* coverity[secure_coding] */
	return sprintf(buf,"%s","MPWUDP");
}
static DEVICE_ATTR(product_name, 0400,show_product_name, NULL);

/*****************************************************************************
* �� �� ��  : show_software_ver
*
* ��������  : ��ȡ����汾��(firmware_version)
*
* �������  :
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/

static ssize_t show_software_ver(struct device *cdev,struct device_attribute *attr,char *buf)
{
	/* coverity[secure_coding] */
	return sprintf(buf,"%s",bsp_version_get_firmware());
}
static DEVICE_ATTR(software_ver, 0400,show_software_ver, NULL);




static struct device_attribute *version_attr[]={
	&dev_attr_version,
	&dev_attr_product_name,
	&dev_attr_software_ver,
	NULL
};
struct device version_dev={
		.init_name="version",
};

int __init version_sysfs_init(void)
{
	int ret=0;
	int i=0,j=0;

	ret=device_register(&version_dev);
	if(ret<0){
		printk("Error:register version_dev device fail\n");
		goto err_out;
	}

	for(i=0;version_attr[i];i++)
	{
		ret=device_create_file(&version_dev, version_attr[i]);
		if(ret)
			goto err_out;
	}

	return 0;

err_out:
	for(j=0;j<i;j++)
		device_remove_file(&version_dev,version_attr[j]);
	device_del(&version_dev);
	return -1;
}

void __exit version_sysfs_exit(void)
{
	device_del(&version_dev);
}

module_init(version_sysfs_init);

module_exit(version_sysfs_exit);
