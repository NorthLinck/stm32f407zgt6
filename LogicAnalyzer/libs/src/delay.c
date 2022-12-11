#include "delay.h"
#include "stm32f4xx.h"

#define    DWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    DWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    SCB_DEMCR     *(volatile unsigned long *)0xE000EDFC
void DWT_Init(void)
{
	// разрешаем использовать счётчик
	SCB_DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	// обнуляем значение счётного регистра
	DWT_CYCCNT  = 0;
	// запускаем счётчик
	DWT_CONTROL |= DWT_CTRL_CYCCNTENA_Msk; 
}
static __inline uint32_t delta(uint32_t t0, uint32_t t1)
{
	return (t1 - t0); 
}
void delay_us(uint32_t us)
{
	uint32_t t0 =  DWT->CYCCNT;
	uint32_t us_count_tic =  us * (SystemCoreClock/1000000);
	while (delta(t0, DWT->CYCCNT) < us_count_tic) ;
}
void delay_ms(uint32_t ms)
{
	uint32_t t0 =  DWT->CYCCNT;
	uint32_t us_count_tic =  ms * 1000 * (SystemCoreClock/1000000);
	while (delta(t0, DWT->CYCCNT) < us_count_tic) ;
}
