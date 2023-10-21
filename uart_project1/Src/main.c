
#include "uart.h"

char key;

int main(void)
{
	
	uart_config();
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	while (1)
	{
		key = uart2_read();
		if(key=='1')
		{
			GPIOA->ODR |= GPIO_ODR_OD5;
		}
		else
		{
			GPIOA->ODR &= ~GPIO_ODR_OD5;
		}
	}
}
