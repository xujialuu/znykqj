#ifndef _OV7670_H_
#define _OV7670_H_
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

#define OV7670_REG_NUM  114

 //===========FIFO PIN============
sbit FIFO_WEN =P3^3;		   //写入FIFO使能
sbit FIFO_RCLK=P3^4;		   //读数据时钟
sbit FIFO_WRST=P6^5;		   //写指针复位
sbit FIFO_RRST=P6^6;		   //读指针复位
sbit FIFO_OE  =P6^7;		   //片选信号(OE)


extern u8 cur_status;						 //帧标志位  在interrupt.c函数中调用


u8 wr_Sensor_Reg(u8 regID, u8 regDat);
u8 rd_Sensor_Reg(u8 regID, u8 *regDat);

u8 Ov7670_init(void);						 //OV7670初始化
u8 ov7670_test(void);						 //OV7670简单版测试函数

void OV7670_Window_Set(unsigned int sx,unsigned int sy,unsigned int width,unsigned int height);	   //ov7670窗体设置
//void OV7670_Light_Mode(unsigned char mode);
//void OV7670_Special_Effects(unsigned char eft);
//void OV7670_Contrast(unsigned char contrast);
//void OV7670_Brightness(unsigned char bright);
//void OV7670_Color_Saturation(unsigned char sat);

#endif


