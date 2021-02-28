#include "led.h"
#include "delay.h"

void Led_Init(void)
{
	led_green=1;
	led_red=1;
}
void Led_Green_On(void)
{
	 led_green=0;
}
void Led_Green_Off(void)
{
	 led_green=1;
}

void Led_Red_On(void)
{
		led_red=0;
}
void Led_Red_Off(void)
{
		led_red=1;
}
