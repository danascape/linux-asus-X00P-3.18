/*
 * driver definition for sensor driver
 *
 * Coypright (c) 2017 huaqin
 */

#define USE_COMMON_FP 1

struct fp_common_resource{
	int rst_gpio;	//reset gpio number
	int irq_gpio;	//irq gpio number
	int pwr_gpio;	//power gpio number
	struct platform_device *pdev;	//platform handle
};


int get_reset_gpio_number(void);
int get_irq_gpio_number(void);
