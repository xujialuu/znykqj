#include"stc8.h"
#include <intrins.h>
#include "delay.h"
#include"lcd_12864.h"

char local_date=0,base_date=0;//ȫ�ֱ�������ǰ��ͷλ��


unsigned char code *Main_Menu[]=
{
{"  ָ��ʶ��ϵͳ"},
{"  �Ƿ���ָ֤��?"}
};
/*------------------------------------------------
                    ���æλ
------------------------------------------------*/
void Check_Busy()
{  
    RS=0;
    RW=1;
    E=1;
    DataPort=0xff;
    while((DataPort&0x80)==0x80);//æ��ȴ�
    E=0;
}
/*------------------------------------------------
                   д����
------------------------------------------------*/
void Write_Cmd(unsigned char Cmd)
{
	Check_Busy();
	RS=0;
	RW=0;
	E=1;
	DataPort=Cmd;
	Delay_Us(20);    // _nop_();����Ҳ���Դﵽ������ʱ��Ч��
	E=0;
	Delay_Us(20);
}
/*------------------------------------------------
                    д����
------------------------------------------------*/
void Write_Data(unsigned char Data)
{
	Check_Busy();
	RS=1;
	RW=0;
	E=1;
	DataPort=Data;
	Delay_Us(20);
	E=0;
	Delay_Us(20);
}
/*------------------------------------------------
                   Һ������ʼ��
------------------------------------------------*/
void Init_ST7920()
{  
   Delay_Ms(40);           //����40MS����ʱ����
   PSB=1;                 //����Ϊ8BIT���ڹ���ģʽ
   Delay_Ms(1);            //��ʱ
   RES=0;                 //��λ
   Delay_Ms(1);            //��ʱ
   RES=1;                 //��λ�ø�
   Delay_Ms(10);
   Write_Cmd(0x30);       //ѡ�����ָ�
   Delay_Us(120);         //��ʱ����100us
   Write_Cmd(0x30);       //ѡ��8bit������
   Delay_Us(50);         //��ʱ����37us
   Write_Cmd(0x0c);       //����ʾ(���αꡢ������)
   Delay_Us(120);         //��ʱ����100us
   Write_Cmd(0x01);       //�����ʾ�������趨��ַָ��Ϊ00H
   Delay_Ms(10);           //��ʱ����10ms
   Write_Cmd(0x06);       //ָ�������ϵĶ�ȡ��д��ʱ���趨�α���ƶ�����ָ����ʾ����λ�������������1λ�ƶ�
   Delay_Us(120);         //��ʱ����100us
}
/*------------------------------------------------
                   �û��Զ����ַ�
------------------------------------------------*/
/*void CGRAM()
{ 
     int i;
     Write_Cmd(0x30); 
     Write_Cmd(0x40);
     for(i=0;i<16;i++)
       {
	    Write_Data(user16x16[i*2]);
        Write_Data(user16x16[i*2+1]);
      }
}   */
/*------------------------------------------------
                   ��ʾ�û��Զ����ַ�
------------------------------------------------*/
void DisplayCGRAM(unsigned char x,unsigned char y)     
{ 
 switch(y)
     {
	  case 1: Write_Cmd(0x80+x);break;
	  case 2: Write_Cmd(0x90+x);break;
	  case 3: Write_Cmd(0x88+x);break;
	  case 4: Write_Cmd(0x98+x);break;
      default:break;
	 }
    Write_Data(00);
    Write_Data(00);

}         
/*------------------------------------------------
                   ��ʾ�ַ���
x:������ֵ����Χ0~8
y:������ֵ����Χ1~4
------------------------------------------------*/
void LCD_PutString(unsigned char x,unsigned char y,unsigned char code *s)
{ 
 switch(y)
     {
	  case 1: Write_Cmd(0x80+x);break;
	  case 2: Write_Cmd(0x90+x);break;
	  case 3: Write_Cmd(0x88+x);break;
	  case 4: Write_Cmd(0x98+x);break;
      default:break;
	 }
 while(*s>0)
   { 
      Write_Data(*s);
      s++;
     Delay_Us(120);
   }
}
/*------------------------------------------------
                      ����
------------------------------------------------*/
void ClrScreen()
{ 
   Write_Cmd(0x01);
   Delay_Ms(20);
}
   	
void DisplayUpdata(void)
{   
 	ClrScreen();
    LCD_PutString(0,1,Main_Menu[0]);    
	  LCD_PutString(0,3,Main_Menu[1]);   //windows�����¿���ֱ��д����
	
}