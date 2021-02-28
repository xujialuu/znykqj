#include"stc8.h"
#include <intrins.h>
#include "delay.h"
#include"lcd_12864.h"

char local_date=0,base_date=0;//全局变量，当前箭头位置


unsigned char code *Main_Menu[]=
{
{"  指纹识别系统"},
{"  是否验证指纹?"}
};
/*------------------------------------------------
                    检测忙位
------------------------------------------------*/
void Check_Busy()
{  
    RS=0;
    RW=1;
    E=1;
    DataPort=0xff;
    while((DataPort&0x80)==0x80);//忙则等待
    E=0;
}
/*------------------------------------------------
                   写命令
------------------------------------------------*/
void Write_Cmd(unsigned char Cmd)
{
	Check_Busy();
	RS=0;
	RW=0;
	E=1;
	DataPort=Cmd;
	Delay_Us(20);    // _nop_();函数也可以达到短暂延时的效果
	E=0;
	Delay_Us(20);
}
/*------------------------------------------------
                    写数据
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
                   液晶屏初始化
------------------------------------------------*/
void Init_ST7920()
{  
   Delay_Ms(40);           //大于40MS的延时程序
   PSB=1;                 //设置为8BIT并口工作模式
   Delay_Ms(1);            //延时
   RES=0;                 //复位
   Delay_Ms(1);            //延时
   RES=1;                 //复位置高
   Delay_Ms(10);
   Write_Cmd(0x30);       //选择基本指令集
   Delay_Us(120);         //延时大于100us
   Write_Cmd(0x30);       //选择8bit数据流
   Delay_Us(50);         //延时大于37us
   Write_Cmd(0x0c);       //开显示(无游标、不反白)
   Delay_Us(120);         //延时大于100us
   Write_Cmd(0x01);       //清除显示，并且设定地址指针为00H
   Delay_Ms(10);           //延时大于10ms
   Write_Cmd(0x06);       //指定在资料的读取及写入时，设定游标的移动方向及指定显示的移位，光标从右向左加1位移动
   Delay_Us(120);         //延时大于100us
}
/*------------------------------------------------
                   用户自定义字符
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
                   显示用户自定义字符
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
                   显示字符串
x:横坐标值，范围0~8
y:纵坐标值，范围1~4
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
                      清屏
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
	  LCD_PutString(0,3,Main_Menu[1]);   //windows环境下可以直接写汉字
	
}