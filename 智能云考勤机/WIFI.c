#include<stc8.h>	//51单片机常用的头文件
#include "wifi.h"
#define uchar unsigned char		//宏定义一个无符号的char类型
#define uint unsigned int		//宏定义一个无符号的int类型

uchar Hour[]={0x0a,0x0b,"\0"};
volatile uint Flag=0;
//发送一字节
void sendByte(uchar b)
{
  SBUF = b;
  while(!TI);
  TI=0;
}

//发送字符串
void sendString(uchar *s)
{
  while(*s != '\0')	//字符串默认结尾'\0'，以此来判断字符串的结束
  {
    sendByte(*s);
    s++;
  }
}

//初始化ESP8266WiFi模块
void initEsp()
{
  uint a;
  P_SW2=0x01;
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0x8F;		//设定定时初值
	T2H = 0xFD;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
  IE2 = ES2; //使能串口中断
 EA = 1; 

  for (a=0; a<50000; a++);		//延时几秒，让模块有时间启动
  sendString("AT+CWMODE=2\r\n");	//设置为softAP和station共存模式

  //WiFi热点不能通过代码设置，可使用串口助手进行设置，该设置断电不丢失
  /*
  for (a=0; a<20000; a++);
  sendString("AT+CWSAP='TEST','12345678',1,3\n"); //建立WiFi热点
  */

  for (a=0; a<50000; a++);    
  sendString("AT+CIPMUX=1\r\n"); //启动多连接

  for (a=0; a<20000; a++);
  sendString("AT+CIPSERVER=1,333\r\n");//建立server，端口为333

  for (a=0; a<20000; a++);
  sendString("AT+CIPSTO=50\r\n");     //服务器超时时间设置

  RI=0;
  ES=1;   //初始化完成，串行口中断打开
}


/*//获取数据，数据格式示例：+IPD,0,14:"time":"11:11"
void getData()
{
  uint a,i;
  if(receiveFlag)
  {
    for(i=0; i<2; i++)
    {
      Hour[i]=Buffer[17+i];
    }
    Hour[2]='\0';

    for(i=0; i<2; i++)
    {
      Minute[i]=Buffer[20+i];
    }
    Minute[2]='\0';

    //将获取到的数据发送到串口助手上显示
    for (a=0; a<10000; a++);	//需要延时，负责会造成数据错乱导致丢包
    sendString(Hour);
    for (a=0; a<10000; a++);
    sendString(Minute);

    receiveFlag=0;
    count=0;
    for(i=0; i<22; i++)
    {
      Buffer[i]=0;
    }
  }
}

//主函数
void main()
{
  initEsp();			//初始化WiFi模块
  receiveFlag = 0;		//receiveFlag判断执行getData() 的标志
  count = 0;			//count缓冲区RXDdata[count]的索引  
  while(1)
  { 
    getData();
  }
}

//利用中断接收信息，且舍弃无效信息
void uart() interrupt 4  
{
  if(RI == 1)	
  {
    ES = 0;     //关闭串行中断
    RI = 0;     //清除串口接收标志位
    temp = SBUF; //从串口缓冲区取得数据

    if(count<20)	//满足需接收的信息长度，将数据存入缓冲区
    { 
      Buffer[count]=temp;
      count++;
      if(Buffer[0]=='+')  //判断是否为无效数据，由于WiFi模块会自动加上"+PID.."开头的字符串
      {
        receiveFlag = 1; 
      }
      else
      {
        receiveFlag = 0;
        count = 0;
      }
    } 
    ES = 1; 
  }
}
*/
  
