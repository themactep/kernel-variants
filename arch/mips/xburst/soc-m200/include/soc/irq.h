/*
 * IRQ number in JZ47xx INTC definition.
 *   Only support 4770 now. 2011-9-23
 *
 * Copyright (C) 2010 Ingenic Semiconductor Co., Ltd.
 */

#ifndef __INTC_IRQ_H__
#define __INTC_IRQ_H__

#include <irq.h>

enum {
// interrupt controller interrupts
	IRQ_DMIC = IRQ_INTC_BASE,
	IRQ_AIC0,
	IRQ_BCH,
	IRQ_DSI,
	IRQ_CSI,
	IRQ_OHCI,
	IRQ_IPU,
	IRQ_SSI1,
	IRQ_SSI0,
	IRQ_RESERVED9,
	IRQ_PDMA,
	IRQ_RESERVED11,
	IRQ_GPIO5,
	IRQ_GPIO4,
	IRQ_GPIO3,
	IRQ_GPIO2,
	IRQ_GPIO1,
	IRQ_GPIO0,
#define IRQ_GPIO_PORT(N) (IRQ_GPIO0 - (N))
	IRQ_SADC,
	IRQ_EPDC,
	IRQ_EHCI,
	IRQ_OTG,
	IRQ_HASH,
	IRQ_AES,
	IRQ_RESERVED24,
	IRQ_TCU2,
	IRQ_TCU1,
	IRQ_TCU0,
	IRQ_RESERVED28,
	IRQ_ISP,
	IRQ_DELAY_LINE,
	IRQ_LCD,

	IRQ_RTC,
	IRQ_RESERVED33,
	IRQ_UART4,
	IRQ_MSC2,
	IRQ_MSC1,
	IRQ_MSC0,
	IRQ_RESERVED38,
	IRQ_NFI,
	IRQ_PCM0,
	IRQ_RESERVED41,
	IRQ_RESERVED42,
	IRQ_RESERVED43,
	IRQ_HARB2,
	IRQ_HARB1,
	IRQ_HARB0,
	IRQ_CPM,
	IRQ_UART3,
	IRQ_UART2,
	IRQ_UART1,
	IRQ_UART0,
	IRQ_DDR,
	IRQ_PFMON,
	IRQ_EFUSE,
	IRQ_GMAC,//ETHC
	IRQ_RESERVED56,
	IRQ_I2C3,
	IRQ_I2C2,
	IRQ_I2C1,
	IRQ_I2C0,
	IRQ_PDMAM,
	IRQ_VPU,
	IRQ_GPU,
#define IRQ_MCU_GPIO_PORT(N) (IRQ_MCU_GPIO0 + (N))
	IRQ_MCU_GPIO0,
	IRQ_MCU_GPIO1,
	IRQ_MCU_GPIO2,
	IRQ_MCU_GPIO3,
	IRQ_MCU_GPIO4,
	IRQ_MCU_GPIO5,

};

enum {
	IRQ_OST = IRQ_OST_BASE,
};

enum {
	IRQ_MCU = IRQ_MCU_BASE,
};

#endif
