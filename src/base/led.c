#include "base/led.h"

void led_init(void)
{

}

void led_switch(bool on)
{
    if(on)
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
    }
}
