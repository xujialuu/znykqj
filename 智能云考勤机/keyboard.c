#include "stc8.h"
#include <intrins.h>
#include "delay.h"
#include "keyboard.h"
#include "lcd_12864.h"
#include "stdio.h"
#include "voice.h"

int KeyValue = 0;			//给4*4键盘每个按键一个序号
int a = 0;
long unsigned int password1[2] = {111111,} ;   //定义初始密码
long unsigned int password2 = 0;         //储存用户输入的密码
long unsigned int password3;
long unsigned int password4;
long unsigned int passwordM = 123456;    //管理员密码
unsigned int d = 0;                      //输入位数d（d = 5是就输入1了六位）
int length,key1,i,m=0,n=0,key2,key3;
//unsigned char str[];
extern int key;

/*********************************************

函数：确定按键位置函数
功能：给16个键编号

**********************************************/


int KeyDown()
{
 int jgtime = 40,KeyValue = -1;
 
 P7 = 0xfe; 
 if((P7 & 0xfe) != 0xfe)               
 {
  Delay_Ms(jgtime);
  if((P7 & 0xfe) != 0xfe)
  {
   switch(P7 & 0xf0)                   
   {
    case 0x70: KeyValue = 10; break;          
    case 0xb0: KeyValue = 7; break;        
    case 0xd0: KeyValue = 4; break;          
    case 0xe0: KeyValue = 1; break;      
   }
  }
 }
  
 P7 = 0xfd; 
 if((P7 & 0xfd) != 0xfd)           
 {
  Delay_Ms(jgtime);
  if((P7 & 0xfd) != 0xfd)
  {
   switch(P7 & 0xf0)                      
   {
    case 0x70: KeyValue = 0; break;            
    case 0xb0: KeyValue = 8; break;						
    case 0xd0: KeyValue = 5; break;            
    case 0xe0: KeyValue = 2; break;						
   }
  }
 }
  
 P7 = 0xfb; 
 if((P7 & 0xfb) != 0xfb)            
 {
  Delay_Ms(jgtime);
  if((P7 & 0xfb) != 0xfb)
  {
   switch(P7 & 0xf0)
   {
    case 0x70: KeyValue = 11; break; 
    case 0xb0: KeyValue = 9; break;
    case 0xd0: KeyValue = 6; break;
    case 0xe0: KeyValue = 3; break;
   }
  }
 }
   
 P7 = 0xf7; 
 if((P7 & 0xf7) != 0xf7)        
 {
  Delay_Ms(jgtime);
  if((P7 & 0xf7) != 0xf7)
  {
   switch(P7 & 0xf0)
   {
    case 0x70: KeyValue = 15; break;
    case 0xb0: KeyValue = 14; break;
    case 0xd0: KeyValue = 13; break;
    case 0xe0: KeyValue = 12; break;
   }
  }
 }
		return 	KeyValue;
}



void KeyScan(){

	switch(key){
	 
		case 1:  //按下1
			//ClrScreen();			
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 1;
		  break;
	  case 2:  //按下2
			 LCD_PutString(d,2,"*");
	     Delay_Ms(5000);
		   d++;        
		   password2 = password2 * 10 + 2;
		   break;
	  case 3:  //按下3
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        
		  password2 = password2 * 10 + 3;
		  break;
	  case 12: break;//（A那个键）
	  case 4:  //按下4
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 4;
		  break;
		case 5:  //按下5
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 5;
		  break;
		case 6:  //按下6
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 6;
		  break;
		case 13: break;//(B键)
		case 7:  //按下7
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 7;
		  break;
		case 8:
			 LCD_PutString(d,2,"*");
		   Delay_Ms(5000);
		   d++;
			 P55 = 0;  			Delay_Ms(50);  P55 = 1;
		   password2 = password2 * 10 + 6;
		case 9:
			 LCD_PutString(d,2,"*");
	   	Delay_Ms(5000);
		  d++;
		  password2 = password2 * 10 + 9;
		case 10: break;
		case 11: break;
		case 0:    //按下0键
			LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;
			P55 = 0;  			Delay_Ms(50);  P55 = 1;
		  password2 = password2 * 10 + 0;  
		case 14: 
			/*if(d > 0){
				password2 = password2/10;
			  for(;a < (d-1); a++){
					Delay_Ms(500);
					LCD_PutString(a,2,'*');     // 对屏幕
				}
		 }*/
			break;
		case 15:   //返回：“请重新输入密码”界面
			break;
		
				}
		 
		
			
		if(d > 5){    
		
			d = 0;
			length = sizeof (password1)/sizeof(password1[0]);
				for(i=0;i<length;i++)
			{
			if(password2 == password1[i]){
				lock = 1;    //开锁
				ClrScreen();
				LCD_PutString(0,2,"    请通行"); 
			  ISP_Check1();  //播放 ： 识别成功请通行
        P61 = 1;
        P60 = 0;				
				lock = 0;
				m=1;
				
				}}
			if(m==0) {
				ClrScreen();
				LCD_PutString(0,1,"密码错误");
				ISP_Check3();  //播放： 密码错误
 				Delay_Ms(1000);
				LCD_PutString(0,2,"请重新输入密码");
				Delay_Ms(30000);
				
				ClrScreen();
				LCD_PutString(0, 1, "请输入密码：");
      				  
			}
			password2 = 0;		
		}
	}

	
	
//管理员密码识别	
void KeyScan_M(){

	switch(key){
	 
		case 1:  //按下1
			//ClrScreen();			
			 LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 1;
		  break;
	  case 2:  //按下2
			 LCD_PutString(d,3,"*");
	     Delay_Ms(5000);
		   d++;        
		   password2 = password2 * 10 + 2;
		   break;
	  case 3:  //按下3
			 LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;        
		  password2 = password2 * 10 + 3;
		  break;
	  case 12: break;//（A那个键）
	  case 4:  //按下4
			 LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 4;
		  break;
		case 5:  //按下5
			 LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 5;
		  break;
		case 6:  //按下6
			 LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 6;
		  break;
		case 13: break;//(B键)
		case 7:  //按下7
			 LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 7;
		  break;
		case 8:
			 LCD_PutString(d,3,"*");
		   Delay_Ms(5000);
		   d++;
			 P55 = 0;  			Delay_Ms(50);  P55 = 1;
		   password2 = password2 * 10 + 6;
		case 9:
			 LCD_PutString(d,3,"*");
	   	Delay_Ms(5000);
		  d++;
		  password2 = password2 * 10 + 9;
		case 10: break;
		case 11: break;
		case 0:    //按下0键
			LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;
			P55 = 0;  			Delay_Ms(50);  P55 = 1;
		  password2 = password2 * 10 + 0;  
		case 14: 
			/*if(d > 0){
				password2 = password2/10;
			  for(;a < (d-1); a++){
					Delay_Ms(500);
					LCD_PutString(a,2,'*');     // 对屏幕
				}
		 }*/
			break;
		case 15:   //返回：“请重新输入密码”界面
			break;
		
				}
		 
		
			
		
	}

	
	void keyscan2()
	{
	

	switch(key){
	 
		case 1:  //按下1
			//ClrScreen();			
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password3 = password3 * 10 + 1;
		  break;
	  case 2:  //按下2
			 LCD_PutString(d,2,"*");
	     Delay_Ms(5000);
		   d++;        
		   password3 = password3 * 10 + 2;
		   break;
	  case 3:  //按下3
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        
		  password3 = password3 * 10 + 3;
		  break;
	  case 12: break;//（A那个键）
	  case 4:  //按下4
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password3 = password3 * 10 + 4;
		  break;
		case 5:  //按下5
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password3 = password3 * 10 + 5;
		  break;
		case 6:  //按下6
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password3 = password3 * 10 + 6;
		  break;
		case 13: break;//(B键)
		case 7:  //按下7
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password3 = password3 * 10 + 7;
		  break;
		case 8:
			 LCD_PutString(d,2,"*");
		   Delay_Ms(5000);
		   d++;
			 P55 = 0;  			Delay_Ms(50);  P55 = 1;
		   password3 = password3 * 10 + 6;
		case 9:
			 LCD_PutString(d,2,"*");
	   	Delay_Ms(5000);
		  d++;
		  password3 = password3 * 10 + 9;
		case 10: break;
		case 11: break;
		case 0:    //按下0键
			LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;
			P55 = 0;  			Delay_Ms(50);  P55 = 1;
		  password3 = password3 * 10 + 0;  
		case 14: 
			/*if(d > 0){
				password2 = password2/10;
			  for(;a < (d-1); a++){
					Delay_Ms(500);
					LCD_PutString(a,2,'*');     // 对屏幕
				}
		 }*/
			break;
		case 15:   //返回：“请重新输入密码”界面
			break;
		
				}
		 
		
			
		
	}

	void keyscan3(){

	switch(key){
	 
		case 1:  //按下1
			//ClrScreen();			
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password4 = password4 * 10 + 1;
		  break;
	  case 2:  //按下2
			 LCD_PutString(d,2,"*");
	     Delay_Ms(5000);
		   d++;        
		   password4 = password4 * 10 + 2;
		   break;
	  case 3:  //按下3
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        
		  password4 = password4 * 10 + 3;
		  break;
	  case 12: break;//（A那个键）
	  case 4:  //按下4
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password4 = password4 * 10 + 4;
		  break;
		case 5:  //按下5
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password4 = password4 * 10 + 5;
		  break;
		case 6:  //按下6
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password4 = password4 * 10 + 6;
		  break;
		case 13: break;//(B键)
		case 7:  //按下7
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password4 = password4 * 10 + 7;
		  break;
		case 8:
			 LCD_PutString(d,2,"*");
		   Delay_Ms(5000);
		   d++;
			 P55 = 0;  			Delay_Ms(50);  P55 = 1;
		   password4 = password4 * 10 + 6;
		case 9:
			 LCD_PutString(d,2,"*");
	   	Delay_Ms(5000);
		  d++;
		  password4 = password4 * 10 + 9;
		case 10: break;
		case 11: break;
		case 0:    //按下0键
			LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;
			P55 = 0;  			Delay_Ms(50);  P55 = 1;
		  password4 = password4 * 10 + 0;  
		case 14: 
			/*if(d > 0){
				password2 = password2/10;
			  for(;a < (d-1); a++){
					Delay_Ms(500);
					LCD_PutString(a,2,'*');     // 对屏幕
				}
		 }*/
			break;
		case 15:   //返回：“请重新输入密码”界面
			break;
		
				}
		 
		
			
		
					
		}

		
void management()
{
		ClrScreen();
		LCD_PutString(0,1,"进入管理员模式");
		LCD_PutString(0,2,"请输入管理密码: ");
		while(1)
		 {
				key = KeyDown();
				Delay_Ms(500);
				KeyScan_M();
//				if (key == 15)
//				{
//						break;
//						
//				}
				if(d > 5){    

						d = 0;

						if(password2 == passwordM){
								ClrScreen();
								LCD_PutString(0,2,"管理员认证成功"); 
								Delay_Ms(1000);
								break;
						//ISP_Check2();  //播放 ： 识别成功请通行				
						}
						else {
								ClrScreen();
								LCD_PutString(0,1,"密码错误");
								//ISP_Check1();  //播放： 密码错误
								Delay_Ms(1000);
								LCD_PutString(0,2,"请重新输入密码");
								Delay_Ms(30000);

								ClrScreen();
								LCD_PutString(0, 1, "请输入密码：");

						}
						password2 = 0;		
				}					
		}
		length = sizeof (password1)/sizeof(password1[0]);
		ClrScreen();
		LCD_PutString(0,1,"  管理系统界面  ");
		LCD_PutString(0,2,"    1.增添密码    ");
		LCD_PutString(0,3,"    2.删去密码    ");
		LCD_PutString(0,4,"    3.修改密码    ");
		while(1)
		{
				key = KeyDown();
				switch(key)
				{
						case 12:
							n=1;
							key=-1;
							ClrScreen();
							LCD_PutString(0,1,"  请添加密码：  ");
							while(1)
							{
									key = KeyDown();
									Delay_Ms(500);
									keyscan2();
									if(d > 5){    			
									d = 0;
									break;
									}
									if(key == 15){
										break;
							}
							}
							password1[length]=password3;
							ClrScreen();
							LCD_PutString(0,1,"  密码添加成功  ");
							Delay_Ms(2000);
							break;

						case 13:
							key=-1;
							n=1;
							ClrScreen();
							LCD_PutString(0,1,"  请删去密码：  ");
							while(1)
							{
									key = KeyDown();
									Delay_Ms(500);
									keyscan2();
									if(d > 5){    

											d = 0;
											break;
						}
						}
							for(i=0;i<length;i++)
							{
									if(password1[i]==password3)
									{
											password1[i]=0;
									}
							}
							ClrScreen();
							LCD_PutString(0,1,"  密码删去成功  ");
							Delay_Ms(2000);
							break;

						case 14:
								n=1;
								key=-1;
								ClrScreen();
								LCD_PutString(0,1,"  更改前密码：  ");
								while(1)
								{

									key = KeyDown();
									Delay_Ms(500);
									keyscan2();
									if(d > 5){    

										d = 0;
										break;
						}
						}
								ClrScreen();
								LCD_PutString(0,1,"  更改后密码：  ");
								key=-1;
								while(1)
								{
								key = KeyDown();
								Delay_Ms(500);
								keyscan3();
								if(d > 5){    

										d = 0;
										break;
								}
								}
								for(i=0;i<length;i++)
								{
										if(password1[i]==password3)
										{
											password1[i]=password4;
										}
								}
								ClrScreen();
								LCD_PutString(0,1,"  更改密码成功  ");
								break;
				}
				if(n==1)
				{
					break;
				}

		}

}










