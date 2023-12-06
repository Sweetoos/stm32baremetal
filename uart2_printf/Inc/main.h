/*
 * main.h
 *
 *  Created on: Sep 19, 2023
 *      Author: kacper
 */

#ifndef MAIN_H_
#define MAIN_H_

#include<stdio.h>
#include <stdint.h>
#include "stm32f429xx.h"
#include "stm32f4xx.h"

// usart2 USART2_TX -> PA2, USART2_RX -> PA3     AF7     APB1



#define CR1_TE					(1U<<3)   
#define CR1_UE					(1U<<0)
#define GPIOAEN                 (1U<<0)
#define SR_TXE                  (1U<<7)
#define SYS_FREQ                16000000



static uint16_t compute_uart_div(uint32_t PeriphClk, uint32_t BaudRate)
{
	return ((PeriphClk + (BaudRate/2U))/BaudRate);
}

static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
{
	USARTx->BRR = compute_uart_div(PeriphClk, BaudRate);
}

static void uart2_write(int ch)
{
   //czekaj na transmisję aby rejestr był pusty
   while (!(USART2->SR & SR_TXE)){}
   //transmisja
   USART2->DR =(ch & 0xFF);  // transmit data register
}
void UART2_Config()
{
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    RCC->APB1ENR |= GPIOAEN;

    GPIOA->MODER &= ~(1U << 4);
    GPIOA->MODER |= (1U << 5);

    GPIOA->AFR[0] |= (1U << 8) | (1U << 9) | (1U << 10);
    GPIOA->AFR[0] &= ~(1U << 11);
    USART2->CR1 = CR1_TE;
    USART2->CR1 |= CR1_UE;
    uart_set_baudrate(USART2, SYS_FREQ, 115200);
}

int __io_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}
// #define GPIOAEN (1U << 0)  // enabling GPIOD
// // USART2_TX -> PD5 AF7             APB1
// #define SYS_FREQ 16000000
// #define APB2_CLK SYS_FREQ

// #define UART_BAUDRATE 115200
// #define CR1_TE (1U<<3)
// #define CR1_UE (1U<<13)
// #define SR_TXE (1U<<7)

// static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate);
// static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate);
// void uart1_write(int ch);

// void UART1_Config(void)
// {
//     //**************configure uart gpio pin
//     RCC->AHB2ENR |= GPIOAEN; // enable clk access to gpioa

//     GPIOA->MODER &= ~(GPIO_MODER_MODE9_0);
//     GPIOA->AFR[1] |= (1U << 4);
//     GPIOA->AFR[1] |= (1U << 5);
//     GPIOA->AFR[1] |= (1U << 6);
//     GPIOA->AFR[1] &= ~(1U << 7);

//     //**************configure uart gpio module
//     // enable clk acces to uart1
//     RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
//     // configure baudrate
//     uart_set_baudrate(USART1, APB2_CLK, UART_BAUDRATE);
//     // configure the transfer direction
//     USART1->CR1 = CR1_TE;
//     // enable uart module
//     USART1->CR1 |= CR1_UE;
// }

// void UART1_write(int ch)
// {
//     //make sure transmit data register is empty
//     while(!(USART1->SR & SR_TXE)){};
//     // write to transmit data register
//     USART1->DR = (ch & 0xFF);
// }

// static void uart_set_baudrate(USART_TypeDef *USARTx, uint32_t PeriphClk, uint32_t BaudRate)
// {
//     USARTx->BRR = compute_uart_bd(PeriphClk, BaudRate);
// }
// static uint16_t compute_uart_bd(uint32_t PeriphClk, uint32_t BaudRate)
// {
//     return ((PeriphClk + (BaudRate / 2U)) / BaudRate);
// }

#endif /* MAIN_H_ */
