//SCCB总线 和I2C总线非常相似  
#include  "stc8.h"
#include "sccb.h"
#include "delay.h"
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

/*
-----------------------------------------------
   功能: start命令,SCCB的起始信号
   参数: 无
 返回值: 无
-----------------------------------------------
*/
void startSCCB()
{
	
 SCCB_SID=1;
 SCCB_SIC=1;
 Delay_Us(175); 
 SCCB_SID=0;
  Delay_Us(175); 
 SCCB_SIC=0;
}
/*
-----------------------------------------------
   功能: stop命令,SCCB的停止信号
   参数: 无
 返回值: 无
-----------------------------------------------
*/
void stopSCCB()
{
 SCCB_SID=0;
  Delay_Us(175);
 SCCB_SIC=1;
 Delay_Us(175); 
 SCCB_SID=1;
 Delay_Us(175); 
}

/*
-----------------------------------------------
   功能: noAck,用于连续读取中的最后一个结束周期
   参数: 无
 返回值: 无
-----------------------------------------------
*/
void noAck(void)
{

 Delay_Us(10); 
 SCCB_SID=1;

 SCCB_SIC=1;
  Delay_Us(175);
 SCCB_SIC=0;
  Delay_Us(175); 
 SCCB_SID=0;
 Delay_Us(175);
}

u8 getAck() 
{
 u8  Error;

 SCCB_SID=1;//设置SCCB_SID为输入
  
 Delay_Us(175); 
 SCCB_SIC=1;
 Delay_Us(175); 
 Error=SCCB_SID;
 Delay_Us(175);
 SCCB_SIC=0; 
 Delay_Us(175);

 SCCB_SID=0;
 return !Error;
}

/*
-----------------------------------------------
   功能: 写入一个字节的数据到SCCB
   参数: 写入数据
 返回值: 发送成功返回1，发送失败返回0
-----------------------------------------------
*/
u8 SCCBwriteByte(u8 dat)
{
 u8 i;
 for(i=0;i<8;i++)
 {
  SCCB_SID=((dat<<i)&0x80);
   Delay_Us(175);
  SCCB_SIC=1;
   Delay_Us(175); 
  SCCB_SIC=0;
 }
 SCCB_SID=0;
 return getAck();
}

/*
-----------------------------------------------
   功能: 一个字节数据读取并且返回
   参数: 无
 返回值: 读取到的数据
-----------------------------------------------
*/
u8 SCCBreadByte(void)
{
 u8 i,rbyte=0;


 SCCB_SID=1;//设置SCCB_SID为输入

 for(i=0;i<8;i++)
 {
  Delay_Us(175); 
  SCCB_SIC=1;  
  if(SCCB_SID) rbyte|=(0x80>>i);
 Delay_Us(175); 
  SCCB_SIC=0;
   Delay_Us(175);
 } 


 SCCB_SID=0;
 return rbyte;
}
