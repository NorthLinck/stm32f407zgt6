/*
clear && st-flash erase && st-flash --reset write build/1st_tstPrj.bin 0x8000000
*/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "main.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "delay.h"
#include "signal_led.h"

int HSE_168MHz(uint32_t Signal_LED)
{
	if (!Signal_LED) return -1;
	unsigned wait_count = 5;

	#define PLL_M	8
	#define PLL_N	336
	#define PLL_P	2
	#define PLL_Q	7

	ErrorStatus HSEStartUpStatus;
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	HSEStartUpStatus=RCC_WaitForHSEStartUp();
	while(HSEStartUpStatus == ERROR && wait_count)
	{
		LED_Switch(Signal_LED, SW_ON);
		delay_ms(50);
		LED_Switch(Signal_LED, SW_OFF);
		delay_ms(50);
		if (!(--wait_count)) return -1;
	}
	wait_count += 10;
	RCC_HCLKConfig(RCC_SYSCLK_Div1);    //(HCLK=SYSCLK)=168MHz
	RCC_PCLK1Config(RCC_HCLK_Div4);     //(PCLK1=SYSCLK/4)=42MHz
	RCC_PCLK2Config(RCC_HCLK_Div2);     //(PCLK2=SYSCLK/2)=84MHz
	RCC_PLLConfig(RCC_PLLSource_HSE,PLL_M ,PLL_N ,PLL_P,PLL_Q);
	RCC_PLLCmd(ENABLE); 
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET && wait_count)
	{
		LED_Switch(Signal_LED, SW_ON);
		delay_ms(100);
		LED_Switch(Signal_LED, SW_OFF);
		delay_ms(100);
		if (!(--wait_count)) return -1;
	}
	wait_count += 15;
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
	while(RCC_GetSYSCLKSource() != 0x08 && wait_count)
	{
		LED_Switch(Signal_LED, SW_ON);
		delay_ms(100);
		LED_Switch(Signal_LED, SW_OFF);
		delay_ms(100);
		if (!(--wait_count)) return -1;
	}
	
	RCC_HSICmd(DISABLE);
	LED_Switch(Signal_LED, SW_ON);
	return 0;
}

void Startup_BOARD(void)
{
	DWT_Init();
	Signal_LEDs_Init();
	HSE_168MHz(SIGNAL_LED_1);
}

int main(void)
{
	Startup_BOARD();

	while(1)
	{
	}
}
