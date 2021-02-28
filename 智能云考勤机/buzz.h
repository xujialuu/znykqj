#ifndef _BUZZ_H_
#define _BUZZ_H_
#include"stc8.h"

sbit buzz=P2^3;

void Buzz_Init(void);
void Buzz_Times(unsigned char times);

#endif