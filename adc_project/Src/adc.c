#include "adc.h"
/*
 * adc.c
 *
 *  Created on: Dec 13, 2023
 *      Author: kacper
 */

void ADC1_init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    GPIOA->MODER |= GPIO_MODER_MODE1;
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;

    //conversion sequence start
    ADC1->SQR3 = ADC_SQR3_SQ1_0;
    ADC1->SQR1 = ~(ADC_SQR1_L_0); 
    /* 
    there is just 1 channel, so it would be 0000, I've negated it to just highlight that I
    need to change this if I want more channels, line 22 is unnecessary
    
    */
    ADC1->CR2 |= ADC_CR2_ADON;
}

void start_adc_conversion(void)
{
    ADC1->CR2 |= ADC_CR2_SWSTART;
}

uint32_t adc_read(void)
{
    while(!(ADC1->SR & ADC_SR_EOC));
    return (ADC1->DR);
}
