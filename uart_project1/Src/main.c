
#include "uart.h"



int main(void)
{
	uart_config();

		while(1)
		{
			printf("Hello my friend!\n\r");
		}
}
