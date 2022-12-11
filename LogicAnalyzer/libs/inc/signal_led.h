#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

/* My board with stm32f407zgt has pull up LEDs,
 * which light when pin pulled down.
*/
#define SW_ON 0x0
#define SW_OFF 0x1

#define SIGNAL_LED_1 GPIO_Pin_0
#define SIGNAL_LED_2 GPIO_Pin_3

void Signal_LEDs_Init(void);
void LED_Switch(uint32_t Signal_LED, bool State);

