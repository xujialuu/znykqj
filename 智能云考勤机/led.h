#ifndef _LED_H
#define _LED_H
#include"stc8.h"

sbit led_green=P6^0;
sbit led_red=P6^1;

void Led_Init(void);
void Led_Green_On(void);// ¼��ָʾ�� 
void Led_Green_Off(void);
void Led_Red_On(void);// declare
void Led_Red_Off(void);// declare
void Led_Yellow_On(void);	 //	ʶ��ָʾ�� 
void Led_Yellow_Off(void);

#endif
