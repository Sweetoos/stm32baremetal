#include "main.h"

int main(void)
{
    UART2_Config();
    while (1)
    {
        printf("Hello from STM32\n\r");
    }
}
