#include <stdint.h>

#define SIGNAL_LED_PIN1 GPIO_Pin_0
#define SIGNAL_LED_PIN2 GPIO_Pin_3

void DWT_Init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

