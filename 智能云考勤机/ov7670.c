
//摄像头模块 采用OV7670  分辨率为640x480   在实际应用中采用QVGA模式 即240x320 模式
//程序上采用240x240的显示框 显示正向的效果
//扫描方向为从左到右 从上到下
//这样做虽然少了一部分的显示  但是在显示速度上又加快了好多
#include  "stc8.h"
#include  "ov7670.h"
#include  "delay.h"
#include  "sccb.h"
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
//OV7670寄存器配置
u8 code OV7670_reg[OV7670_REG_NUM][2]=
{	 
    /*以下为OV7670 QVGA RGB565参数    具体内容 可以参考资料里 ov7670中文版PDF资料*/
  	{0x3a, 0x04},//dummy
	{0x40, 0x10},//565
	{0x12, 0x14},//@



	{0x17, 0x16},//行频开始高8位       
	{0x18, 0x04},//行频结束高8位
	{0x19, 0x02},//场频开始高8位
    {0x1a, 0x7a},//场频结束高8位

	{0x32, 0x80},//行频开始低3位bit[2:0]	 行频结束低3位bit[5:3]
    {0x03, 0x0a},//位【3：2】场频结束低2位  位【1：0】场频开始低2位

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
        
	  {0x1e, 0x17},//0x07,	 //图像输出镜像控制.0x07, 0x027    5位 镜像   4位 竖直翻转
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
        
  //{0x09, 0x03},//驱动能力最大   
	{0x6e, 0x11},//100
	{0x6f, 0x9f},//0x9e for advance AWB
    {0x55, 0x00},//亮度
    {0x56, 0x40},//对比度
    {0x57, 0x80},//0x40,  change according to Jim's request	  
};




//写OV7660寄存器
//返回：1-成功	0-失败
//regID	 寄存器地址  regDat  数据 
u8 wr_Sensor_Reg(u8 regID, u8 regDat)
{

 startSCCB(); //发送SCCB 总线开始传输命令
	 
 if(SCCBwriteByte(0x42)==0)//写地址		
 {		  
  stopSCCB();//发送SCCB 总线停止传输命令

  return(0);//错误返回
  
 }
  
 if(SCCBwriteByte(regID)==0)//寄存器ID
 {			
  stopSCCB();//发送SCCB 总线停止传输命令
  return(0); //错误返回
 }

 if(SCCBwriteByte(regDat)==0)//写数据到积存器
 {
  stopSCCB();//发送SCCB 总线停止传输命令
  return(0);//错误返回
 }

 stopSCCB();//发送SCCB 总线停止传输命令
	 

 return(1);//成功返回
}




//读OV7660寄存器
//返回：1-成功	0-失败
//regID	 寄存器地址  regDat  数据
u8 rd_Sensor_Reg(u8 regID, u8 *regDat)
{
 //通过写操作设置寄存器地址

 startSCCB();

 if(0==SCCBwriteByte(0x42))//写地址		手册11页上
 {
  stopSCCB();//发送SCCB 总线停止传输命令
  return(0);//错误返回
 }

 if(0==SCCBwriteByte(regID))//积存器ID
 {
  stopSCCB();//发送SCCB 总线停止传输命令
  return(0);//错误返回
 }
 stopSCCB();//发送SCCB 总线停止传输命令
	
 //设置寄存器地址后，才是读
 startSCCB();

 if(0==SCCBwriteByte(0x43))//读地址		  手册11页上
 {
  stopSCCB();//发送SCCB 总线停止传输命令
  return(0);//错误返回
 }
	
 *regDat=SCCBreadByte();//返回读到的值

 noAck();//发送NACK命令
 stopSCCB();//发送SCCB 总线停止传输命令

 return(1);//成功返回
}




//Sensor_init()  摄像头芯片初始化
//返回0成功，返回1失败
//=================================================
u8 Ov7670_init(void)
{
 u8  i=0,
     tem1,tem2;

        	
 if(0==wr_Sensor_Reg(0x12,0x80)) //Reset SCCB	复位SCCB
 {	
  return 1 ;//错误返回
 }

 if(0==rd_Sensor_Reg(0x0b, &tem1))//读ID	产品低字节识别号
 {
  return 1 ;//错误返回
 }
  if(0==rd_Sensor_Reg(0x0a, &tem2))//读ID	产品高字节识别号
 {
  return 1 ;//错误返回
 }

 if(tem1==0x73)//OV7670
 {	
  if(tem2==0x76)
  {			
  for(i=0;i<OV7670_REG_NUM;i++)			  //写寄存器循环
  {

   if(0==wr_Sensor_Reg(OV7670_reg[i][0],OV7670_reg[i][1]))
   {  
	return 1;//错误返回
   }
  }
  return 0;
 }
 }
return 1;  //错误返回
} 


//设置图像输出窗口
//对QVGA设置。
//sx  sy 为场频 和行频的初始值 这个值是ov本身厂家定的 在初始化里计数一下就能知道 场频是10  行频是176
//width 为场频方向   height 为行频方向	  
//摄像头在初始的时候 就已经设置成QVGA格式 也就是说是320x240的分辨率
//                   //那么在设置显示区域的时候不能超过这个个分辨率 否则也不会有多余的显示 注意！
void OV7670_Window_Set(u16 sx,u16 sy,u16 width,u16 height)
{
	u16 endx;
	u16 endy;																	   
	u8 temp; 
	endx=sx+width*2;	//V*2   一个颜色两个字节
 	endy=sy+height*2;
	if(endy>784)endy-=784;		//这里要看时序图 784为行频的一个周期


	rd_Sensor_Reg(0X03,&temp);	//读取场频低字节
	temp&=0XF0;					//清低4位
	temp|=((endx&0X03)<<2)|(sx&0X03);  //将计算的低字节移入

	wr_Sensor_Reg(0X03,temp);		 //写入
	wr_Sensor_Reg(0X19,sx>>2);
	wr_Sensor_Reg(0X1A,endx>>2);

	rd_Sensor_Reg(0X32,&temp);		 //同上
	temp&=0XC0;
	temp|=((endy&0X07)<<3)|(sy&0X07);

	wr_Sensor_Reg(0X32,temp);	
    wr_Sensor_Reg(0X17,sy>>3);		 //行频开始高8位
	wr_Sensor_Reg(0X18,endy>>3);	 //行频结束高8位
}



//	 以下语句为设置显示效果 函数  用的时候直接打开即可  


//////////////////////////////////////////////////////////////////////////////
////OV7670功能设置
////白平衡设置
////0:自动
////1:太阳sunny
////2,阴天cloudy
////3,办公室office
////4,家里home
//void OV7670_Light_Mode(unsigned char mode)
//{
//	unsigned char reg13val=0XE7;//默认就是设置为自动白平衡
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
//	wr_Sensor_Reg(0X13,reg13val);//COM8设置 
//	wr_Sensor_Reg(0X01,reg01val);//AWB蓝色通道增益 
//	wr_Sensor_Reg(0X02,reg02val);//AWB红色通道增益 
//}	
//
//
//
////色度设置
////0:-2
////1:-1
////2,0
////3,1
////4,2
//void OV7670_Color_Saturation(unsigned char sat)
//{
//	unsigned char reg4f5054val=0X80;//默认就是sat=2,即不调节色度的设置
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
//	wr_Sensor_Reg(0X4F,reg4f5054val);	//色彩矩阵系数1
//	wr_Sensor_Reg(0X50,reg4f5054val);	//色彩矩阵系数2 
//	wr_Sensor_Reg(0X51,0X00);			//色彩矩阵系数3  
//	wr_Sensor_Reg(0X52,reg52val);		//色彩矩阵系数4 
//	wr_Sensor_Reg(0X53,reg53val);		//色彩矩阵系数5 
//	wr_Sensor_Reg(0X54,reg4f5054val);	//色彩矩阵系数6  
//	wr_Sensor_Reg(0X58,0X9E);			//MTXS 
//}
////亮度设置
////0:-2
////1:-1
////2,0
////3,1
////4,2
//void OV7670_Brightness(unsigned char bright)
//{
//	unsigned char reg55val=0X00;//默认就是bright=2
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
//	wr_Sensor_Reg(0X55,reg55val);	//亮度调节 
//}
////对比度设置
////0:-2
////1:-1
////2,0
////3,1
////4,2
//void OV7670_Contrast(unsigned char contrast)
//{
//	unsigned char reg56val=0X40;//默认就是contrast=2
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
//	wr_Sensor_Reg(0X56,reg56val);	//对比度调节 
//}
////特效设置
////0:普通模式    
////1,负片
////2,黑白   
////3,偏红色
////4,偏绿色
////5,偏蓝色
////6,复古	    
//void OV7670_Special_Effects(unsigned char eft)
//{
//	unsigned char reg3aval=0X04;//默认为普通模式
//	unsigned char reg67val=0XC0;
//	unsigned char reg68val=0X80;
//	switch(eft)
//	{
//		case 1://负片
//			reg3aval=0X24;
//			reg67val=0X80;
//			reg68val=0X80;
//			break;	
//		case 2://黑白
//			reg3aval=0X14;
//			reg67val=0X80;
//			reg68val=0X80;
//			break;	
//		case 3://偏红色
//			reg3aval=0X14;
//			reg67val=0Xc0;
//			reg68val=0X80;
//			break;	
//		case 4://偏绿色
//			reg3aval=0X14;
//			reg67val=0X40;
//			reg68val=0X40;
//			break;	
//		case 5://偏蓝色
//			reg3aval=0X14;
//			reg67val=0X80;
//			reg68val=0XC0;
//			break;	
//		case 6://复古
//			reg3aval=0X14;
//			reg67val=0XA0;
//			reg68val=0X40;
//			break;	 
//	}
//	wr_Sensor_Reg(0X3A,reg3aval);//TSLB设置 
//	wr_Sensor_Reg(0X68,reg67val);//MANU,手动U值 
//	wr_Sensor_Reg(0X67,reg68val);//MANV,手动V值 
//}	


u8 cur_status=0;			 //帧标志位  在interrupt.c函数中调用

u8 ov7670_test(void)
{
// struct TFT_Pointer sp;  //定义触摸变量结构体
 u32  j;					 //临时变量
 u8  sign=0;			  //初始标志


//   P1M0=0X00;	  //P1口为仅输入状态
//   P1M1=0Xff;

					   //开启中断目的为  判断VSYNC 为帧数据判断 当有触发的时候 为来一帧  
					                     //这个是时候开始往 缓存芯片 AL422B灌入一帧数据
										 //当来第二帧时 说明数据灌入完成 此时提取数据 进行显示
  IT0=1;			   //边沿触发   
  EX0=1;               //外部中断0   P3.2口    
  EA   = 1;            // 开总中断 
	
  
//  Lcd_WriteReg(0x0003,0x1028); //扫描方向设置为从上到下 从右到左
//  Lcd_WR_Reg(0x0022);			 //发送设置

//  LCD_scan(6);


//  GUI_sprintf_hzstr16x(240,0,"ov7670    ",White,Red);
//  GUI_sprintf_hzstr16x(240,16,"摄像测试版",White,Blue);
  //GUI_sprintf_hzstr16x(240,224,  "      返回",White,Blue);
  
  if( Ov7670_init())	 //初始化 ov7670  
  {															 //初始化不成功
   //GUI_sprintf_hzstr16x(60,150,"OV7670 Init Error!",White,Blue);
   Delay_Ms(800);
   EX0=0;			   //关闭外部中断0
   EA=0;			   //关闭总中断
   sign=1;
  }


//  Lcd_WriteReg(0x0003,0x1030); //恢复扫描方向 为从左到右 从上到下
//  Lcd_WR_Reg(0x0022);			 //发送设置
//	LCD_scan(6);


  if(sign==1)return 1;		   //初始化 跳出函数 （没有插OV7670 或者没插好） 

  FIFO_OE=0;		   //使能摄像头模块
  				

  //摄像头 参数设置 
// 	OV7670_Light_Mode(0);
//	OV7670_Color_Saturation(4);
//	OV7670_Brightness(2);
//	OV7670_Contrast(3);
// 	OV7670_Special_Effects(2);	


  OV7670_Window_Set(10,176,240,320);	//设置窗口

   

 //开始扫描 显示摄像头采集数据
 while(1)
 {

//  Address_set(0,0,319,239);	  //设置显示范围  显示为240*320 	 9341转换屏的扫描方向时 起始点也会变 那么xy也会有所调换的
  if(cur_status==2)			   //判断缓存区是否存好摄像数据
    { 
  
	  FIFO_RRST=0;			   //开始复位读指针	读取FIFO数据
      FIFO_RCLK=0;
      FIFO_RCLK=1;
      FIFO_RCLK=0;
      FIFO_RRST=1;			   //复位读指针结束
      FIFO_RCLK=1;


//	  LCD_RS=1;				   //拉高TFT 写数据端 

	  for(j=0;j<76800;j++)	   //分辨率为240x240   每个颜色点要两个字节 所以 240x240x2=57600  次
	  {		 
		FIFO_RCLK=0;		   //每一次时钟跳变 读一次数据		
		S2BUF=P1;				   //直接将高字节数据给P0
		FIFO_RCLK=1; 

		FIFO_RCLK=0;
		S2BUF=P1;	           	   //直接将低字节数据给P7
		FIFO_RCLK=1; 	
	
	  }  
	  EX0 = 1; 				   //显示完成开中断
	  cur_status=0;			   //显示完整个图片以后 将	 cur_status置0  准备接收下一帧
    } 
  }	
  return 0;					   //成功跳出
   	
}






 void zhen() interrupt 0 //外部中断0  P3.2  判断帧数据
 {

 
   if(cur_status==0) //如果此时状态为0，则说明是一个图像的开始，开始向FIFO罐入数据
    {
     FIFO_WRST=0;	 //写复位
     FIFO_WRST=1;
     FIFO_WEN=1;	 //写FIFO使能
     cur_status=1;   //标记为1
    }
   else 
    if(cur_status==1)	//说明此处为图像的结束，亦即下一图像的开始
     {
       FIFO_WEN=0;		//写FIFO禁能
       FIFO_WRST=0;		//写复位
       FIFO_WRST=1;
       cur_status=2;	//标记为2  此时说明可以读取FIFO中的缓存数据
     }
  }



