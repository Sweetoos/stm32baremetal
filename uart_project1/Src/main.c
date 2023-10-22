
#include "uart.h"



int main(void)
{
	char key;
	uart_config();
	led_config();
	while (1)
	{
		key = uart2_read();
		if (key == '1')
		{
			LD2_ON;
		}
		if (key == '2')
		{
			LD2_OFF;
		}
	}
}
