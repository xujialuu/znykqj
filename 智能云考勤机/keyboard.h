#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_



#define GPIO_Key P7
sbit lock = P4^1;  
int KeyDown();  
void KeyScan();  
void management();

#endif