#ifndef _LED_H
#define _LED_H
#include"stc8.h"

sbit led_green=P6^0;
sbit led_red=P6^1;

void Led_Init(void);
void Led_Green_On(void);// 录入指示灯 
void Led_Green_Off(void);
void Led_Red_On(void);// declare
void Led_Red_Off(void);// declare
void Led_Yellow_On(void);	 //	识别指示灯 
void Led_Yellow_Off(void);

#endif
