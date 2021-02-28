#include "stc8.h"
#include <intrins.h>
#include "delay2.h"
#include "keyboard2.h"
#include "lcd_128642.h"
#include "stdio.h"

//#define uint unsigned int 
//#define uchar unsigned char

int KeyValue = 0;			//给4*4键盘每个按键一个序号
int a = 0;
long unsigned int password1 = 308308 ;   //定义初始密码
long unsigned int password2 = 0;         //储存用户输入的密码
unsigned int d = 0;                      //输入位数d（d = 5是就输入了六位）
unsigned char str[];

void KeyDown(){                  //先确定列 再确定行 
	GPIO_Key = 0xf0;								//1111 0000（高位置高）
	if (GPIO_Key != 0xf0){
			Delay_Ms(100);            //软件消抖
			if (GPIO_Key != 0xf0){
					GPIO_Key = 0xf0;		//重新赋值一次
					switch (GPIO_Key){      //扫描确定在哪一列
						case 0xe0:
							KeyValue = 0;
							break;
						case 0xd0:
							KeyValue = 1;
							break;
						case 0xb0:         
							KeyValue = 2;
							break;
						case 0x70:
							KeyValue = 3;
							break;
			
					}
			}
	GPIO_Key	 = 0x0f;   // 0000 1111（低位置高）
	if (GPIO_Key != 0x0f){
			Delay_Ms(100);            //软件消抖
			if (GPIO_Key != 0x0f){     
					switch (GPIO_Key){      //扫描确定在哪一行
						case 0x0e:
							KeyValue = KeyValue;
							break;
						case 0x0d:
							KeyValue = KeyValue + 4;
							break;
						case 0x0b:
							KeyValue = KeyValue + 8;
							break;
						case 0x07:
							KeyValue = KeyValue + 12;
							break;
			
					}
			}
		while ((a < 50)&&(GPIO_Key != 0x0f)){   //等待释放按键
			Delay_Ms(1000);
			a++;
		}
	 }
	}

}




void KeyScan(){

	switch(KeyValue){
	 
		case 0:  //按下1
			LCD_PutString(d,2,'1');
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 1;
		  break;
	  case 1:  //按下2
			LCD_PutString(d,2,'2');
		  d++;        
		  password2 = password2 * 10 + 2;
		  break;
	  case 2:  //按下3
			LCD_PutString(d,2,'3');
		  d++;        
		  password2 = password2 * 10 + 3;
		  break;
	  case 3: break;//（A那个键）
	  case 4:  //按下4
			LCD_PutString(d,2,'4');
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 4;
		  break;
		case 5:  //按下5
			LCD_PutString(d,2,'5');
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 5;
		  break;
		case 6:  //按下6
			LCD_PutString(d,2,'6');
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 6;
		  break;
		case 7: break;//(B键)
		case 8:  //按下7
			LCD_PutString(d,2,'7');
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 7;
		  break;
		case 9:
			LCD_PutString(d,2,'8');
		  d++;
		  password2 = password2 * 10 + 8;
		case 10:
			LCD_PutString(d,2,'9');
		  d++;
		  password2 = password2 * 10 + 9;
		case 11: break;
		case 12: break;
		case 13:    //按下0键
			LCD_PutString(d,2,'0');
		  d++;
		  password2 = password2 * 10 + 0;  
		case 14: break;
		case 15:  
			// 功能：删除（*not sure）
		
			if(d>0){
				password2 = password2/10;  // 删除最末位 然后lcd直接显示
				sprintf(str,"%d",password2);
				LCD_PutString(0,2,str); } //只能接受字符串 sprintf（）属于个人操作 ***not sure****
				
		}
			
		if(d > 5){     //输入完毕
		
			d = 0;
			if(password2 == password1){
				lock = 1;    //开锁
				}
			else {
				LCD_PutString(0,1,"密码错误");
				Delay_Ms(1000);
				LCD_PutString(0,2,"请重新输入密码");	
			}
			password2 = 0;		
		}
			
	}
