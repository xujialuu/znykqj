#ifndef _OV7670_H_
#define _OV7670_H_
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

#define OV7670_REG_NUM  114

 //===========FIFO PIN============
sbit FIFO_WEN =P3^3;		   //д��FIFOʹ��
sbit FIFO_RCLK=P3^4;		   //������ʱ��
sbit FIFO_WRST=P6^5;		   //дָ�븴λ
sbit FIFO_RRST=P6^6;		   //��ָ�븴λ
sbit FIFO_OE  =P6^7;		   //Ƭѡ�ź�(OE)


extern u8 cur_status;						 //֡��־λ  ��interrupt.c�����е���


u8 wr_Sensor_Reg(u8 regID, u8 regDat);
u8 rd_Sensor_Reg(u8 regID, u8 *regDat);

u8 Ov7670_init(void);						 //OV7670��ʼ��
u8 ov7670_test(void);						 //OV7670�򵥰���Ժ���

void OV7670_Window_Set(unsigned int sx,unsigned int sy,unsigned int width,unsigned int height);	   //ov7670��������
//void OV7670_Light_Mode(unsigned char mode);
//void OV7670_Special_Effects(unsigned char eft);
//void OV7670_Contrast(unsigned char contrast);
//void OV7670_Brightness(unsigned char bright);
//void OV7670_Color_Saturation(unsigned char sat);

#endif


