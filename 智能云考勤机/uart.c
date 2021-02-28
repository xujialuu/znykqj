#include "uart.h"
#include "stc8.h"


void Uart_Init(void)
{
    P_SW2|=0X04;
	S4CON = 0x10;		//8位数据,可变波特率
	S4CON &= 0xBF;		//串口4选择定时器2为波特率发生器
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0x8F;		//设定定时初值
	T2H = 0xFD;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
}


void Uart_Send_Byte(unsigned char c)//UART Send a byte
{
	 S4BUF = c;                 //写数据到UART数据寄存器
		while(!(S4CON&S4TI));        //在停止位没有发送时，S4TI为0即一直等待
    S4CON&=~S4TI;                //清除S4CON寄存器对应S4TI位（该位必须软件清零）
}

unsigned char Uart_Receive_Byte()//UART Receive a byteg
{	
	unsigned char dat;
	while(!(S4CON&S4RI));	 //接收完为1 
	S4CON&=~S4RI;
	dat = S4BUF;
	return (dat);
}