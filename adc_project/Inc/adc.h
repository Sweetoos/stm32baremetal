/*
 * adc.h
 *
 *  Created on: Dec 13, 2023
 *      Author: kacper
 */

#ifndef ADC_H_
#define ADC_H_

#include "main.h"
//ADC1, PA1 ADC123_IN1 12bit

void ADC1_init(void);
void start_adc_conversion(void);
uint32_t adc_read(void);

#endif /* ADC_H_ */
