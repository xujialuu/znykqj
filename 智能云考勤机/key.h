#ifndef _KEY_H_
#define _KEY_H_
#include"stc8.h"

sbit KEY_UP=P3^4;         //定义按键输入端口
sbit KEY_DOWN=P3^5;
sbit KEY_OK=P3^6;
sbit KEY_CANCEL=P3^7;

void Key_Init(void);

#endif
