
#include "main.h"



int main(void)
{
	uart_config();
    ADC1_init();
    
    uint32_t sensor_value=0;
    while (1)
    {
        start_adc_conversion();
        sensor_value = adc_read();
        printf("Sensor value: %d \n\r", (int)sensor_value);
    }
}
