#include "stc8.h"
#include "voice.h"

char  code  MESSAGE1[6]={0xAA,0x07,0x02,0x00,0x01,0xB4};	//定义到程序空间中
char  code  MESSAGE2[6]={0xAA,0x07,0x02,0x00,0x02,0xB5};	//定义到程序空间中
char  code  MESSAGE3[6]={0xAA,0x07,0x02,0x00,0x03,0xB6};	//定义到程序空间中



void delay(unsigned int m)				//延时函数
    {
	  int  a=0,b=0;
	  for(a=0;a<500;a++)
	  for(b=0;b<m;b++);
	
	}


void ISP_Check1()						//串口发送调用函数(播放识别成功)
{
  unsigned char x=0;	 

	  //a=0;
	   //while(MESSAGE[a]!= '\0')
	     for(x=0;x<6;x++)
   	   {
					SBUF = MESSAGE1[x];	        //SUBF接受/发送缓冲器(又叫串行通信特殊功能寄存器)
					while(!TI);				// 等特数据传送	(TI发送中断标志)
					TI = 0;					// 清除数据传送标志
		
		//a++;					    // 下一个字符
       } 
}


void ISP_Check2()						//串口发送调用函数（播放识别失败）
{
  unsigned char x=0;	 

	  //a=0;
	   //while(MESSAGE[a]!= '\0')
	     for(x=0;x<6;x++)
   	   {
		SBUF = MESSAGE2[x];	        //SUBF接受/发送缓冲器(又叫串行通信特殊功能寄存器)
         while(!TI);				// 等特数据传送	(TI发送中断标志)
		 TI = 0;					// 清除数据传送标志
		
		//a++;					    // 下一个字符
       } 
		 }		 
			 
void ISP_Check3()						//串口发送调用函数（播放密码错误）
{
  unsigned char x=0;	 

	  //a=0;
	   //while(MESSAGE[a]!= '\0')
	     for(x=0;x<6;x++)
   	   {
					SBUF = MESSAGE3[x];	        //SUBF接受/发送缓冲器(又叫串行通信特殊功能寄存器)
					while(!TI);				// 等特数据传送	(TI发送中断标志)
					TI = 0;					// 清除数据传送标志
		
		//a++;					    // 下一个字符
       } 
		 }


void voice_init() 			 //主函数
{

	
	

		SCON = 0x50;        //REN=1允许串行接受状态，串口工作模式2     	   
		TMOD = 0x00;       //定时器1为模式0（16位自动重载）                
		AUXR = 0X40;		 //开启1T模式
		TL1=(65535-(24000000/4/9600));    //设置波特率重装值
		TH1=(65535-(24000000/4/9600))>>8;

                         // 如有不明白请查 STC8手册上有详细说明 	 
      
		TR1  = 1;        //开启定时器1                                                                      
		EA   = 1;        // 开总中断 
}