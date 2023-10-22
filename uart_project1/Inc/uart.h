/*
 * uart.h
 *
 *  Created on: Oct 21, 2023
 *      Author: kacper
 */

#ifndef UART_H_
#define UART_H_

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "stm32f446xx.h"

#define LD2_ON GPIOA->ODR |= GPIO_ODR_OD5
#define LD2_OFF GPIOA->ODR &= ~(GPIO_ODR_OD5)

void uart_config(void);
char uart2_read(void);
void uart2_write(int ch);
void led_config(void);


#endif /* UART_H_ */
