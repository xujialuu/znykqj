
//����ͷģ�� ����OV7670  �ֱ���Ϊ640x480   ��ʵ��Ӧ���в���QVGAģʽ ��240x320 ģʽ
//�����ϲ���240x240����ʾ�� ��ʾ�����Ч��
//ɨ�跽��Ϊ������ ���ϵ���
//��������Ȼ����һ���ֵ���ʾ  ��������ʾ�ٶ����ּӿ��˺ö�
#include  "stc8.h"
#include  "ov7670.h"
#include  "delay.h"
#include  "sccb.h"
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
//OV7670�Ĵ�������
u8 code OV7670_reg[OV7670_REG_NUM][2]=
{	 
    /*����ΪOV7670 QVGA RGB565����    �������� ���Բο������� ov7670���İ�PDF����*/
  	{0x3a, 0x04},//dummy
	{0x40, 0x10},//565
	{0x12, 0x14},//@



	{0x17, 0x16},//��Ƶ��ʼ��8λ       
	{0x18, 0x04},//��Ƶ������8λ
	{0x19, 0x02},//��Ƶ��ʼ��8λ
    {0x1a, 0x7a},//��Ƶ������8λ

	{0x32, 0x80},//��Ƶ��ʼ��3λbit[2:0]	 ��Ƶ������3λbit[5:3]
    {0x03, 0x0a},//λ��3��2����Ƶ������2λ  λ��1��0����Ƶ��ʼ��2λ

	{0x0c, 0x0c},
    {0x15, 0x00},
	{0x3e, 0x00},//10
	{0x70, 0x00},
	{0x71, 0x01},
	{0x72, 0x11},
	{0x73, 0x09},//
        

	{0xa2, 0x02},//15
	  {0x11, 0x00}, //fenpin
	{0x7a, 0x20},
	{0x7b, 0x1c},
	{0x7c, 0x28},
        

	{0x7d, 0x3c},//20
	{0x7e, 0x55},
	{0x7f, 0x68},
	{0x80, 0x76},
	{0x81, 0x80},
        
	{0x82, 0x88},
	{0x83, 0x8f},
	{0x84, 0x96},
	{0x85, 0xa3},
	{0x86, 0xaf},
        
	{0x87, 0xc4},//30
	{0x88, 0xd7},
	{0x89, 0xe8},
	{0x13, 0xe0},
	{0x00, 0x00},//AGC
        
	{0x10, 0x00},
	{0x0d, 0x00},
	{0x14, 0x20},//0x38, limit the max gain
	{0xa5, 0x05},
	{0xab, 0x07},
        
	{0x24, 0x75},//40
	{0x25, 0x63},
	{0x26, 0xA5},
	{0x9f, 0x78},
	{0xa0, 0x68},
        
	{0xa1, 0x03},//0x0b,
	{0xa6, 0xdf},//0xd8,
	{0xa7, 0xdf},//0xd8,
	{0xa8, 0xf0},
	{0xa9, 0x90},
        
	{0xaa, 0x94},//50
	{0x13, 0xe5},
	{0x0e, 0x61},
	{0x0f, 0x4b},
	{0x16, 0x02},
        
	  {0x1e, 0x17},//0x07,	 //ͼ������������.0x07, 0x027    5λ ����   4λ ��ֱ��ת
	{0x21, 0x02},
	{0x22, 0x91},
	{0x29, 0x07},
	{0x33, 0x0b},
        
	{0x35, 0x0b},//60
	{0x37, 0x1d},
	{0x38, 0x71},
	{0x39, 0x2a},
	{0x3c, 0x78},
        
	{0x4d, 0x40},
	{0x4e, 0x20},
	{0x69, 0x5d},
	{0x6b, 0x40},//PLL
	{0x74, 0x19},
	{0x8d, 0x4f},
        
	{0x8e, 0x00},//70
	{0x8f, 0x00},
	{0x90, 0x00},
	{0x91, 0x00},
	{0x92, 0x00},//0x19,//0x66
        
	{0x96, 0x00},
	{0x9a, 0x80},
	{0xb0, 0x84},
	{0xb1, 0x0c},
	{0xb2, 0x0e},
        
	{0xb3, 0x82},//80
	{0xb8, 0x0a},
	{0x43, 0x14},
	{0x44, 0xf0},
	{0x45, 0x34},
        
	{0x46, 0x58},
	{0x47, 0x28},
	{0x48, 0x3a},
	{0x59, 0x88},
	{0x5a, 0x88},
        
	{0x5b, 0x44},//90
	{0x5c, 0x67},
	{0x5d, 0x49},
	{0x5e, 0x0e},
	{0x64, 0x04},
	{0x65, 0x20},
        
	{0x66, 0x05},
	{0x94, 0x04},
	{0x95, 0x08},
	{0x6c, 0x0a},
	{0x6d, 0x55},
        
        
	{0x4f, 0x80},
	{0x50, 0x80},
	{0x51, 0x00},
	{0x52, 0x22},
	{0x53, 0x5e},
	{0x54, 0x80},
        
  //{0x54, 0x40},//110
        
  //{0x09, 0x03},//�����������   
	{0x6e, 0x11},//100
	{0x6f, 0x9f},//0x9e for advance AWB
    {0x55, 0x00},//����
    {0x56, 0x40},//�Աȶ�
    {0x57, 0x80},//0x40,  change according to Jim's request	  
};




//дOV7660�Ĵ���
//���أ�1-�ɹ�	0-ʧ��
//regID	 �Ĵ�����ַ  regDat  ���� 
u8 wr_Sensor_Reg(u8 regID, u8 regDat)
{

 startSCCB(); //����SCCB ���߿�ʼ��������
	 
 if(SCCBwriteByte(0x42)==0)//д��ַ		
 {		  
  stopSCCB();//����SCCB ����ֹͣ��������

  return(0);//���󷵻�
  
 }
  
 if(SCCBwriteByte(regID)==0)//�Ĵ���ID
 {			
  stopSCCB();//����SCCB ����ֹͣ��������
  return(0); //���󷵻�
 }

 if(SCCBwriteByte(regDat)==0)//д���ݵ�������
 {
  stopSCCB();//����SCCB ����ֹͣ��������
  return(0);//���󷵻�
 }

 stopSCCB();//����SCCB ����ֹͣ��������
	 

 return(1);//�ɹ�����
}




//��OV7660�Ĵ���
//���أ�1-�ɹ�	0-ʧ��
//regID	 �Ĵ�����ַ  regDat  ����
u8 rd_Sensor_Reg(u8 regID, u8 *regDat)
{
 //ͨ��д�������üĴ�����ַ

 startSCCB();

 if(0==SCCBwriteByte(0x42))//д��ַ		�ֲ�11ҳ��
 {
  stopSCCB();//����SCCB ����ֹͣ��������
  return(0);//���󷵻�
 }

 if(0==SCCBwriteByte(regID))//������ID
 {
  stopSCCB();//����SCCB ����ֹͣ��������
  return(0);//���󷵻�
 }
 stopSCCB();//����SCCB ����ֹͣ��������
	
 //���üĴ�����ַ�󣬲��Ƕ�
 startSCCB();

 if(0==SCCBwriteByte(0x43))//����ַ		  �ֲ�11ҳ��
 {
  stopSCCB();//����SCCB ����ֹͣ��������
  return(0);//���󷵻�
 }
	
 *regDat=SCCBreadByte();//���ض�����ֵ

 noAck();//����NACK����
 stopSCCB();//����SCCB ����ֹͣ��������

 return(1);//�ɹ�����
}




//Sensor_init()  ����ͷоƬ��ʼ��
//����0�ɹ�������1ʧ��
//=================================================
u8 Ov7670_init(void)
{
 u8  i=0,
     tem1,tem2;

        	
 if(0==wr_Sensor_Reg(0x12,0x80)) //Reset SCCB	��λSCCB
 {	
  return 1 ;//���󷵻�
 }

 if(0==rd_Sensor_Reg(0x0b, &tem1))//��ID	��Ʒ���ֽ�ʶ���
 {
  return 1 ;//���󷵻�
 }
  if(0==rd_Sensor_Reg(0x0a, &tem2))//��ID	��Ʒ���ֽ�ʶ���
 {
  return 1 ;//���󷵻�
 }

 if(tem1==0x73)//OV7670
 {	
  if(tem2==0x76)
  {			
  for(i=0;i<OV7670_REG_NUM;i++)			  //д�Ĵ���ѭ��
  {

   if(0==wr_Sensor_Reg(OV7670_reg[i][0],OV7670_reg[i][1]))
   {  
	return 1;//���󷵻�
   }
  }
  return 0;
 }
 }
return 1;  //���󷵻�
} 


//����ͼ���������
//��QVGA���á�
//sx  sy Ϊ��Ƶ ����Ƶ�ĳ�ʼֵ ���ֵ��ov�����Ҷ��� �ڳ�ʼ�������һ�¾���֪�� ��Ƶ��10  ��Ƶ��176
//width Ϊ��Ƶ����   height Ϊ��Ƶ����	  
//����ͷ�ڳ�ʼ��ʱ�� ���Ѿ����ó�QVGA��ʽ Ҳ����˵��320x240�ķֱ���
//                   //��ô��������ʾ�����ʱ���ܳ���������ֱ��� ����Ҳ�����ж������ʾ ע�⣡
void OV7670_Window_Set(u16 sx,u16 sy,u16 width,u16 height)
{
	u16 endx;
	u16 endy;																	   
	u8 temp; 
	endx=sx+width*2;	//V*2   һ����ɫ�����ֽ�
 	endy=sy+height*2;
	if(endy>784)endy-=784;		//����Ҫ��ʱ��ͼ 784Ϊ��Ƶ��һ������


	rd_Sensor_Reg(0X03,&temp);	//��ȡ��Ƶ���ֽ�
	temp&=0XF0;					//���4λ
	temp|=((endx&0X03)<<2)|(sx&0X03);  //������ĵ��ֽ�����

	wr_Sensor_Reg(0X03,temp);		 //д��
	wr_Sensor_Reg(0X19,sx>>2);
	wr_Sensor_Reg(0X1A,endx>>2);

	rd_Sensor_Reg(0X32,&temp);		 //ͬ��
	temp&=0XC0;
	temp|=((endy&0X07)<<3)|(sy&0X07);

	wr_Sensor_Reg(0X32,temp);	
    wr_Sensor_Reg(0X17,sy>>3);		 //��Ƶ��ʼ��8λ
	wr_Sensor_Reg(0X18,endy>>3);	 //��Ƶ������8λ
}



//	 �������Ϊ������ʾЧ�� ����  �õ�ʱ��ֱ�Ӵ򿪼���  


//////////////////////////////////////////////////////////////////////////////
////OV7670��������
////��ƽ������
////0:�Զ�
////1:̫��sunny
////2,����cloudy
////3,�칫��office
////4,����home
//void OV7670_Light_Mode(unsigned char mode)
//{
//	unsigned char reg13val=0XE7;//Ĭ�Ͼ�������Ϊ�Զ���ƽ��
//	unsigned char reg01val=0;
//	unsigned char reg02val=0;
//	switch(mode)
//	{
//		case 1://sunny
//			reg13val=0XE5;
//			reg01val=0X5A;
//			reg02val=0X5C;
//			break;	
//		case 2://cloudy
//			reg13val=0XE5;
//			reg01val=0X58;
//			reg02val=0X60;
//			break;	
//		case 3://office
//			reg13val=0XE5;
//			reg01val=0X84;
//			reg02val=0X4c;
//			break;	
//		case 4://home
//			reg13val=0XE5;
//			reg01val=0X96;
//			reg02val=0X40;
//			break;	
//	}
//	wr_Sensor_Reg(0X13,reg13val);//COM8���� 
//	wr_Sensor_Reg(0X01,reg01val);//AWB��ɫͨ������ 
//	wr_Sensor_Reg(0X02,reg02val);//AWB��ɫͨ������ 
//}	
//
//
//
////ɫ������
////0:-2
////1:-1
////2,0
////3,1
////4,2
//void OV7670_Color_Saturation(unsigned char sat)
//{
//	unsigned char reg4f5054val=0X80;//Ĭ�Ͼ���sat=2,��������ɫ�ȵ�����
// 	unsigned char reg52val=0X22;
//	unsigned char reg53val=0X5E;
// 	switch(sat)
//	{
//		case 0://-2
//			reg4f5054val=0X40;  	 
//			reg52val=0X11;
//			reg53val=0X2F;	 	 
//			break;	
//		case 1://-1
//			reg4f5054val=0X66;	    
//			reg52val=0X1B;
//			reg53val=0X4B;	  
//			break;	
//		case 3://1
//			reg4f5054val=0X99;	   
//			reg52val=0X28;
//			reg53val=0X71;	   
//			break;	
//		case 4://2
//			reg4f5054val=0XC0;	   
//			reg52val=0X33;
//			reg53val=0X8D;	   
//			break;	
//	}
//	wr_Sensor_Reg(0X4F,reg4f5054val);	//ɫ�ʾ���ϵ��1
//	wr_Sensor_Reg(0X50,reg4f5054val);	//ɫ�ʾ���ϵ��2 
//	wr_Sensor_Reg(0X51,0X00);			//ɫ�ʾ���ϵ��3  
//	wr_Sensor_Reg(0X52,reg52val);		//ɫ�ʾ���ϵ��4 
//	wr_Sensor_Reg(0X53,reg53val);		//ɫ�ʾ���ϵ��5 
//	wr_Sensor_Reg(0X54,reg4f5054val);	//ɫ�ʾ���ϵ��6  
//	wr_Sensor_Reg(0X58,0X9E);			//MTXS 
//}
////��������
////0:-2
////1:-1
////2,0
////3,1
////4,2
//void OV7670_Brightness(unsigned char bright)
//{
//	unsigned char reg55val=0X00;//Ĭ�Ͼ���bright=2
//  	switch(bright)
//	{
//		case 0://-2
//			reg55val=0XB0;	 	 
//			break;	
//		case 1://-1
//			reg55val=0X98;	 	 
//			break;	
//		case 3://1
//			reg55val=0X18;	 	 
//			break;	
//		case 4://2
//			reg55val=0X30;	 	 
//			break;	
//	}
//	wr_Sensor_Reg(0X55,reg55val);	//���ȵ��� 
//}
////�Աȶ�����
////0:-2
////1:-1
////2,0
////3,1
////4,2
//void OV7670_Contrast(unsigned char contrast)
//{
//	unsigned char reg56val=0X40;//Ĭ�Ͼ���contrast=2
//  	switch(contrast)
//	{
//		case 0://-2
//			reg56val=0X30;	 	 
//			break;	
//		case 1://-1
//			reg56val=0X38;	 	 
//			break;	
//		case 3://1
//			reg56val=0X50;	 	 
//			break;	
//		case 4://2
//			reg56val=0X60;	 	 
//			break;	
//	}
//	wr_Sensor_Reg(0X56,reg56val);	//�Աȶȵ��� 
//}
////��Ч����
////0:��ͨģʽ    
////1,��Ƭ
////2,�ڰ�   
////3,ƫ��ɫ
////4,ƫ��ɫ
////5,ƫ��ɫ
////6,����	    
//void OV7670_Special_Effects(unsigned char eft)
//{
//	unsigned char reg3aval=0X04;//Ĭ��Ϊ��ͨģʽ
//	unsigned char reg67val=0XC0;
//	unsigned char reg68val=0X80;
//	switch(eft)
//	{
//		case 1://��Ƭ
//			reg3aval=0X24;
//			reg67val=0X80;
//			reg68val=0X80;
//			break;	
//		case 2://�ڰ�
//			reg3aval=0X14;
//			reg67val=0X80;
//			reg68val=0X80;
//			break;	
//		case 3://ƫ��ɫ
//			reg3aval=0X14;
//			reg67val=0Xc0;
//			reg68val=0X80;
//			break;	
//		case 4://ƫ��ɫ
//			reg3aval=0X14;
//			reg67val=0X40;
//			reg68val=0X40;
//			break;	
//		case 5://ƫ��ɫ
//			reg3aval=0X14;
//			reg67val=0X80;
//			reg68val=0XC0;
//			break;	
//		case 6://����
//			reg3aval=0X14;
//			reg67val=0XA0;
//			reg68val=0X40;
//			break;	 
//	}
//	wr_Sensor_Reg(0X3A,reg3aval);//TSLB���� 
//	wr_Sensor_Reg(0X68,reg67val);//MANU,�ֶ�Uֵ 
//	wr_Sensor_Reg(0X67,reg68val);//MANV,�ֶ�Vֵ 
//}	


u8 cur_status=0;			 //֡��־λ  ��interrupt.c�����е���

u8 ov7670_test(void)
{
// struct TFT_Pointer sp;  //���崥�������ṹ��
 u32  j;					 //��ʱ����
 u8  sign=0;			  //��ʼ��־


//   P1M0=0X00;	  //P1��Ϊ������״̬
//   P1M1=0Xff;

					   //�����ж�Ŀ��Ϊ  �ж�VSYNC Ϊ֡�����ж� ���д�����ʱ�� Ϊ��һ֡  
					                     //�����ʱ��ʼ�� ����оƬ AL422B����һ֡����
										 //�����ڶ�֡ʱ ˵�����ݹ������ ��ʱ��ȡ���� ������ʾ
  IT0=1;			   //���ش���   
  EX0=1;               //�ⲿ�ж�0   P3.2��    
  EA   = 1;            // �����ж� 
	
  
//  Lcd_WriteReg(0x0003,0x1028); //ɨ�跽������Ϊ���ϵ��� ���ҵ���
//  Lcd_WR_Reg(0x0022);			 //��������

//  LCD_scan(6);


//  GUI_sprintf_hzstr16x(240,0,"ov7670    ",White,Red);
//  GUI_sprintf_hzstr16x(240,16,"������԰�",White,Blue);
  //GUI_sprintf_hzstr16x(240,224,  "      ����",White,Blue);
  
  if( Ov7670_init())	 //��ʼ�� ov7670  
  {															 //��ʼ�����ɹ�
   //GUI_sprintf_hzstr16x(60,150,"OV7670 Init Error!",White,Blue);
   Delay_Ms(800);
   EX0=0;			   //�ر��ⲿ�ж�0
   EA=0;			   //�ر����ж�
   sign=1;
  }


//  Lcd_WriteReg(0x0003,0x1030); //�ָ�ɨ�跽�� Ϊ������ ���ϵ���
//  Lcd_WR_Reg(0x0022);			 //��������
//	LCD_scan(6);


  if(sign==1)return 1;		   //��ʼ�� �������� ��û�в�OV7670 ����û��ã� 

  FIFO_OE=0;		   //ʹ������ͷģ��
  				

  //����ͷ �������� 
// 	OV7670_Light_Mode(0);
//	OV7670_Color_Saturation(4);
//	OV7670_Brightness(2);
//	OV7670_Contrast(3);
// 	OV7670_Special_Effects(2);	


  OV7670_Window_Set(10,176,240,320);	//���ô���

   

 //��ʼɨ�� ��ʾ����ͷ�ɼ�����
 while(1)
 {

//  Address_set(0,0,319,239);	  //������ʾ��Χ  ��ʾΪ240*320 	 9341ת������ɨ�跽��ʱ ��ʼ��Ҳ��� ��ôxyҲ������������
  if(cur_status==2)			   //�жϻ������Ƿ�����������
    { 
  
	  FIFO_RRST=0;			   //��ʼ��λ��ָ��	��ȡFIFO����
      FIFO_RCLK=0;
      FIFO_RCLK=1;
      FIFO_RCLK=0;
      FIFO_RRST=1;			   //��λ��ָ�����
      FIFO_RCLK=1;


//	  LCD_RS=1;				   //����TFT д���ݶ� 

	  for(j=0;j<76800;j++)	   //�ֱ���Ϊ240x240   ÿ����ɫ��Ҫ�����ֽ� ���� 240x240x2=57600  ��
	  {		 
		FIFO_RCLK=0;		   //ÿһ��ʱ������ ��һ������		
		S2BUF=P1;				   //ֱ�ӽ����ֽ����ݸ�P0
		FIFO_RCLK=1; 

		FIFO_RCLK=0;
		S2BUF=P1;	           	   //ֱ�ӽ����ֽ����ݸ�P7
		FIFO_RCLK=1; 	
	
	  }  
	  EX0 = 1; 				   //��ʾ��ɿ��ж�
	  cur_status=0;			   //��ʾ������ͼƬ�Ժ� ��	 cur_status��0  ׼��������һ֡
    } 
  }	
  return 0;					   //�ɹ�����
   	
}






 void zhen() interrupt 0 //�ⲿ�ж�0  P3.2  �ж�֡����
 {

 
   if(cur_status==0) //�����ʱ״̬Ϊ0����˵����һ��ͼ��Ŀ�ʼ����ʼ��FIFO��������
    {
     FIFO_WRST=0;	 //д��λ
     FIFO_WRST=1;
     FIFO_WEN=1;	 //дFIFOʹ��
     cur_status=1;   //���Ϊ1
    }
   else 
    if(cur_status==1)	//˵���˴�Ϊͼ��Ľ������༴��һͼ��Ŀ�ʼ
     {
       FIFO_WEN=0;		//дFIFO����
       FIFO_WRST=0;		//д��λ
       FIFO_WRST=1;
       cur_status=2;	//���Ϊ2  ��ʱ˵�����Զ�ȡFIFO�еĻ�������
     }
  }



