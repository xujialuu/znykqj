#include "stc8.h"
#include <intrins.h>
#include "delay2.h"
#include "keyboard2.h"
#include "lcd_128642.h"
#include "stdio.h"

//#define uint unsigned int 
//#define uchar unsigned char

int KeyValue = 0;			//��4*4����ÿ������һ�����
int a = 0;
long unsigned int password1 = 308308 ;   //�����ʼ����
long unsigned int password2 = 0;         //�����û����������
unsigned int d = 0;                      //����λ��d��d = 5�Ǿ���������λ��
unsigned char str[];

void KeyDown(){                  //��ȷ���� ��ȷ���� 
	GPIO_Key = 0xf0;								//1111 0000����λ�øߣ�
	if (GPIO_Key != 0xf0){
			Delay_Ms(100);            //�������
			if (GPIO_Key != 0xf0){
					GPIO_Key = 0xf0;		//���¸�ֵһ��
					switch (GPIO_Key){      //ɨ��ȷ������һ��
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
	GPIO_Key	 = 0x0f;   // 0000 1111����λ�øߣ�
	if (GPIO_Key != 0x0f){
			Delay_Ms(100);            //�������
			if (GPIO_Key != 0x0f){     
					switch (GPIO_Key){      //ɨ��ȷ������һ��
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
		while ((a < 50)&&(GPIO_Key != 0x0f)){   //�ȴ��ͷŰ���
			Delay_Ms(1000);
			a++;
		}
	 }
	}

}




void KeyScan(){

	switch(KeyValue){
	 
		case 0:  //����1
			LCD_PutString(d,2,'1');
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 1;
		  break;
	  case 1:  //����2
			LCD_PutString(d,2,'2');
		  d++;        
		  password2 = password2 * 10 + 2;
		  break;
	  case 2:  //����3
			LCD_PutString(d,2,'3');
		  d++;        
		  password2 = password2 * 10 + 3;
		  break;
	  case 3: break;//��A�Ǹ�����
	  case 4:  //����4
			LCD_PutString(d,2,'4');
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 4;
		  break;
		case 5:  //����5
			LCD_PutString(d,2,'5');
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 5;
		  break;
		case 6:  //����6
			LCD_PutString(d,2,'6');
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 6;
		  break;
		case 7: break;//(B��)
		case 8:  //����7
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
		case 13:    //����0��
			LCD_PutString(d,2,'0');
		  d++;
		  password2 = password2 * 10 + 0;  
		case 14: break;
		case 15:  
			// ���ܣ�ɾ����*not sure��
		
			if(d>0){
				password2 = password2/10;  // ɾ����ĩλ Ȼ��lcdֱ����ʾ
				sprintf(str,"%d",password2);
				LCD_PutString(0,2,str); } //ֻ�ܽ����ַ��� sprintf�������ڸ��˲��� ***not sure****
				
		}
			
		if(d > 5){     //�������
		
			d = 0;
			if(password2 == password1){
				lock = 1;    //����
				}
			else {
				LCD_PutString(0,1,"�������");
				Delay_Ms(1000);
				LCD_PutString(0,2,"��������������");	
			}
			password2 = 0;		
		}
			
	}
