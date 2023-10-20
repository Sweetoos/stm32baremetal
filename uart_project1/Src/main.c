
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f446xx.h"


#define SYS_FREQ 16000000U
#define APB1_CLK SYS_FREQ
#define USART_BAUDRATE 115200

static uint16_t compute_uart_baudrate(uint32_t PeriphClk, uint32_t baudrate)
{
	return((PeriphClk + (baudrate/2))/baudrate);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t baudrate)
{
	USART2->BRR |= compute_uart_baudrate(APB1_CLK, USART_BAUDRATE);
}

void uart_config(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	GPIOA->MODER |= (GPIO_MODER_MODE2_1);
	GPIOA->AFR[0] |= ~(GPIO_AFRL_AFRL2_3);
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	uart_set_baudrate(USART2, SYS_FREQ, USART_BAUDRATE);
	USART2->CR1 = USART_CR1_TE;
	USART2->CR1 |= USART_CR1_UE;
}

void uart2_write(int ch)
{
	while(!((USART2->SR)&(1U<<7)));
	USART2->DR=(ch&0xFF);
}

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}
int main(void)
{
	uart_config();

		while(1)
		{
			printf("Hello my friend!\n\r");
		}
}
