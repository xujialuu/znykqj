#include "uart.h"
#include "stc8.h"


void Uart_Init(void)
{
    P_SW2|=0X04;
	S4CON = 0x10;		//8λ����,�ɱ䲨����
	S4CON &= 0xBF;		//����4ѡ��ʱ��2Ϊ�����ʷ�����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0x8F;		//�趨��ʱ��ֵ
	T2H = 0xFD;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
}


void Uart_Send_Byte(unsigned char c)//UART Send a byte
{
	 S4BUF = c;                 //д���ݵ�UART���ݼĴ���
		while(!(S4CON&S4TI));        //��ֹͣλû�з���ʱ��S4TIΪ0��һֱ�ȴ�
    S4CON&=~S4TI;                //���S4CON�Ĵ�����ӦS4TIλ����λ����������㣩
}

unsigned char Uart_Receive_Byte()//UART Receive a byteg
{	
	unsigned char dat;
	while(!(S4CON&S4RI));	 //������Ϊ1 
	S4CON&=~S4RI;
	dat = S4BUF;
	return (dat);
}