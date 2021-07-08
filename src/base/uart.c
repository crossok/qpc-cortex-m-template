#include "base/uart.h"
#include "hal/usart.h"

void uart_init(void)
{
    MX_USART1_UART_Init();
}


/* this function is used by C lib's printf() function, should enable MicroLib in Arm Keil option page*/

int fputc(int ch, FILE *f)
{
    uint8_t data = ch; 
    HAL_UART_Transmit(&huart1, &data, 1, 20);

    return (ch);
}