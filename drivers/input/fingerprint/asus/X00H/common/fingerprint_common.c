#include <linux/init.h>
#include <linux/module.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/list.h>
#include <linux/errno.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/compat.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/ktime.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/platform_device.h>

#include "fingerprint_common.h"

#define DEV_NAME "common,fingerprint"

static struct fp_common_resource fp_g;

static struct of_device_id fp_common_table[] = {
	{ .compatible = "common,fingerprint" },
	{ .compatible = "commonfp" },
	{},
};


/*it has been checked in the probe follow
	so if ust it,the value is right
*/
int get_irq_gpio_number(void)
{
	return fp_g.irq_gpio;
}

int get_reset_gpio_number(void)
{
	return fp_g.rst_gpio;
}

static int fp_common_probe(struct platform_device *pdev)
{	
	int ret ;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;

	printk(KERN_INFO"fp_common_probe start;");

	fp_g.pdev = pdev;

	fp_g.irq_gpio = of_get_named_gpio(np,"common,gpio_irq",0);
	fp_g.rst_gpio = of_get_named_gpio(np,"common,gpio_reset",0);

	if (!gpio_is_valid(fp_g.rst_gpio))
	{
		printk(KERN_ERR"commonfp:get reset gpio is invaild!\n");
		return -1;
	}

	if (!gpio_is_valid(fp_g.rst_gpio))
	{
		printk(KERN_ERR"commonfp:get irq gpio is invaild!\n");
		return -1;
	}

	ret = devm_gpio_request(dev, fp_g.irq_gpio, "commonfp,gpio_irq");
	if (ret) {
		printk(KERN_ERR"failed to request irq gpio %d\n", fp_g.irq_gpio);
		return -1;
	}

	ret = devm_gpio_request(dev, fp_g.rst_gpio, "commonfp,gpio_rst");
	if (ret) {
		printk(KERN_ERR"failed to request rst gpio %d\n", fp_g.rst_gpio);
		goto error;
	}
	
	printk(KERN_ERR"fp_common_probe probe OK,irq_gpio:%d,rst_gpio:%d\n",fp_g.irq_gpio,fp_g.rst_gpio);

	return 0;

error:
	devm_gpio_free(dev,fp_g.irq_gpio);
	return -1;
}

static int fp_common_remove(struct platform_device *pdev)
{

	struct device *dev = &pdev->dev;
	if (gpio_is_valid(fp_g.irq_gpio))
	{
		devm_gpio_free(dev,fp_g.irq_gpio);
        dev_err(dev,"remove irq_gpio success\n");
	}
	
	if (gpio_is_valid(fp_g.rst_gpio))
	{
		devm_gpio_free(dev,fp_g.rst_gpio);
        dev_err(dev,"remove irq_gpio success\n");
	}
	
	dev_err(dev,"fp_common_remove release all gpio suscess!!!");

	return 0;
}

static struct platform_driver fingerprint_common = {
	.driver = {
		.name = "common_fp",
		.owner = THIS_MODULE,
		.of_match_table = fp_common_table,
	},
	.probe = fp_common_probe,
	.remove = fp_common_remove,
};

static int __init fingerprint_resource_init(void)
{
	int ret;
	ret = platform_driver_register(&fingerprint_common);
	if(ret){
		printk(KERN_ERR"commonfp:register common fingerprint platform driver failed:%d\n",ret);
		return ret;
	}
	printk(KERN_INFO"commonfp fingerpint init OK!!!,ret = %d\n",ret);

	return ret;
}

module_init(fingerprint_resource_init);


static void __exit fingerprint_resource_exit(void)
{
	platform_driver_unregister(&fingerprint_common);
}

module_exit(fingerprint_resource_exit);

MODULE_LICENSE("GPL");
