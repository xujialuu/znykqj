#include "stc8.h"
#include <intrins.h>
#include "led.h"
#include "uart.h"
#include "delay.h"
#include "FPM10A.h"
#include "lcd_12864.h"
#include "keyboard.h"
#include "ov7670.h" 
#include "wifi.h"
int key;


void main()
{	
	initESP();
		Init_ST7920(); 
		voice_init(); 
	  Delay_Ms(500); 
    init_w25q128();
		Uart_Init();
		Device_Check();
Ov7670_init();
		DisplayUpdata();
	  
		Delay_Ms(500); 

		while(1)
		{
				DisplayUpdata();
				Delay_Ms(500); 
				while(1){
						key = KeyDown();
						Delay_Ms(500);
						if(key == 11){  
											
								FPM10A_Find_Fingerprint();
						}
						if (key==12)
						{
						management();
							break;
						}
						if (key==13)
						{
							ClrScreen();
						LCD_PutString(0,1,"Â¼ÈëÖ¸ÎÆÖÐ...");
							Delay_Ms(1000);
							break;
						}
						Led_Red_Off();	
						Delay_Ms(100); 
						if (key == 15){
								break;
						}

				}
		}

}
