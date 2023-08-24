#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/mmc.h>
#include <linux/mmc/sd.h>
#include <linux/mmc/sdio.h>
#include <linux/scatterlist.h>
#include <linux/dma-mapping.h>

#include <linux/fs.h>
#include <asm/uaccess.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include <linux/err.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/stat.h>

#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include "ingenic_mmc.h"

struct wifi_data {
	int sdio_index;
	/* struct wake_lock                wifi_wake_lock; */
	/* struct regulator                *wifi_vbat; */
	/* struct regulator                *wifi_vddio; */
	uint         wifi_reset;
	uint         wifi_irq;
	uint         wifi_irq_flags;
	struct pinctrl *pctrl;
	atomic_t rtc32k_ref;
};

#define RESET  0
#define NORMAL 1

struct wifi_data wifi_data;
static void rtc32k_init(struct device *dev, struct wifi_data *wdata)
{
	atomic_set(&wdata->rtc32k_ref, 0);
	wdata->pctrl = devm_pinctrl_get(dev);
}
void rtc32k_enable(void)
{
	struct pinctrl_state *state = NULL;
	struct pinctrl *p = wifi_data.pctrl;

	if (atomic_inc_return(&wifi_data.rtc32k_ref) == 1) {
		state = pinctrl_lookup_state(p, "enable");
		if (!IS_ERR_OR_NULL(state)) {
			pinctrl_select_state(p, state);
		}
	}
}
EXPORT_SYMBOL(rtc32k_enable);
void rtc32k_disable(void)
{
	struct pinctrl_state *state = NULL;
	struct pinctrl *p = wifi_data.pctrl;

	if (atomic_inc_return(&wifi_data.rtc32k_ref) == 0) {
		state = pinctrl_lookup_state(p, "disable");
		if (!IS_ERR_OR_NULL(state)) {
			pinctrl_select_state(p, state);
		}
	}
}
EXPORT_SYMBOL(rtc32k_disable);

static const struct of_device_id wlan_ingenic_of_match[] = {
	{.compatible = "android,bcmdhd_wlan",},
	{},
};
int ingenic_sdio_wlan_init(struct device *dev, int index)
{
	struct device_node *np = dev->of_node, *cnp;
	unsigned int flags, gpio;

	rtc32k_init(dev, &wifi_data);
	for_each_child_of_node(np, cnp) {
		if (of_device_is_compatible(cnp, wlan_ingenic_of_match[0].compatible)) {
			wifi_data.wifi_reset = of_get_named_gpio_flags(cnp, "ingenic,sdio-reset", 0, &flags);
			wifi_data.wifi_irq = of_get_named_gpio_flags(cnp, "ingenic,sdio-irq", 0, &flags);
			wifi_data.wifi_irq_flags = flags;
		}
	}

	gpio = wifi_data.wifi_reset;
	if (devm_gpio_request(dev, gpio, "wifi_reset")) {
		printk("ERROR: no wifi_reset pin available !!\n");
		return -EINVAL;
	} else {
		gpio_direction_output(gpio, 1);
	}
	wifi_data.wifi_reset = gpio;
	wifi_data.sdio_index = index;

	return 0;
}
EXPORT_SYMBOL(ingenic_sdio_wlan_init);
int ingenic_sdio_wlan_get_irq(unsigned long *flag)
{
	*flag = wifi_data.wifi_irq_flags;
	return wifi_data.wifi_irq;
}
EXPORT_SYMBOL(ingenic_sdio_wlan_get_irq);
int ingenic_sdio_wlan_power_onoff(int onoff, int flag)
{
	int reset = wifi_data.wifi_reset;
	if(!reset)
		return -EINVAL;
	if(onoff) {
		/* printk("reset %d wlan power on:%d\n", reset, flag); */
		rtc32k_enable();
		switch(flag) {
		case RESET:
			ingenic_mmc_clk_ctrl(wifi_data.sdio_index, 1);
			gpio_set_value(reset, 0);
			msleep(10);
			gpio_set_value(reset, 1);
			break;
		case NORMAL:
			gpio_set_value(reset, 0);
			msleep(10);
			gpio_set_value(reset, 1);
			ingenic_mmc_manual_detect(wifi_data.sdio_index, 1);
			break;
		}
	} else {
		/* printk("wlan power off:%d\n", flag); */
		switch(flag) {
		case RESET:
			gpio_set_value(reset, 0);
			break;
		case NORMAL:
			gpio_set_value(reset, 0);
			break;
		}
		rtc32k_disable();
	}
	return 0;

}
EXPORT_SYMBOL(ingenic_sdio_wlan_power_onoff);
