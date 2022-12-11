#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include "signal_led.h"

void Signal_LEDs_Init(void)
{
	GPIO_InitTypeDef gpio;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	gpio.GPIO_Mode  = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin   = SIGNAL_LED_2;
	gpio.GPIO_PuPd  = GPIO_PuPd_DOWN;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &gpio);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	gpio.GPIO_Mode  = GPIO_Mode_OUT;
	gpio.GPIO_OType = GPIO_OType_PP;
	gpio.GPIO_Pin   = SIGNAL_LED_1;
	gpio.GPIO_PuPd  = GPIO_PuPd_DOWN;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio);

	GPIO_SetBits(GPIOD, SIGNAL_LED_2);
	GPIO_SetBits(GPIOC, SIGNAL_LED_1);
}

void LED_Switch(uint32_t Signal_LED, bool State)
{
	switch(Signal_LED) {
		case SIGNAL_LED_1:
			GPIO_WriteBit(GPIOC, SIGNAL_LED_1, State);
			break;
		case SIGNAL_LED_2:
			GPIO_WriteBit(GPIOD, SIGNAL_LED_2, State);
			break;
		default:
			break;
	};
}

