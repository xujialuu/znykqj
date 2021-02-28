#include "stc8.h"
#include <intrins.h>
#include "delay.h"
#include "keyboard.h"
#include "lcd_12864.h"
#include "stdio.h"
#include "voice.h"

int KeyValue = 0;			//��4*4����ÿ������һ�����
int a = 0;
long unsigned int password1[2] = {111111,} ;   //�����ʼ����
long unsigned int password2 = 0;         //�����û����������
long unsigned int password3;
long unsigned int password4;
long unsigned int passwordM = 123456;    //����Ա����
unsigned int d = 0;                      //����λ��d��d = 5�Ǿ�����1����λ��
int length,key1,i,m=0,n=0,key2,key3;
//unsigned char str[];
extern int key;

/*********************************************

������ȷ������λ�ú���
���ܣ���16�������

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
	 
		case 1:  //����1
			//ClrScreen();			
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 1;
		  break;
	  case 2:  //����2
			 LCD_PutString(d,2,"*");
	     Delay_Ms(5000);
		   d++;        
		   password2 = password2 * 10 + 2;
		   break;
	  case 3:  //����3
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        
		  password2 = password2 * 10 + 3;
		  break;
	  case 12: break;//��A�Ǹ�����
	  case 4:  //����4
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 4;
		  break;
		case 5:  //����5
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 5;
		  break;
		case 6:  //����6
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 6;
		  break;
		case 13: break;//(B��)
		case 7:  //����7
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
		case 0:    //����0��
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
					LCD_PutString(a,2,'*');     // ����Ļ
				}
		 }*/
			break;
		case 15:   //���أ����������������롱����
			break;
		
				}
		 
		
			
		if(d > 5){    
		
			d = 0;
			length = sizeof (password1)/sizeof(password1[0]);
				for(i=0;i<length;i++)
			{
			if(password2 == password1[i]){
				lock = 1;    //����
				ClrScreen();
				LCD_PutString(0,2,"    ��ͨ��"); 
			  ISP_Check1();  //���� �� ʶ��ɹ���ͨ��
        P61 = 1;
        P60 = 0;				
				lock = 0;
				m=1;
				
				}}
			if(m==0) {
				ClrScreen();
				LCD_PutString(0,1,"�������");
				ISP_Check3();  //���ţ� �������
 				Delay_Ms(1000);
				LCD_PutString(0,2,"��������������");
				Delay_Ms(30000);
				
				ClrScreen();
				LCD_PutString(0, 1, "���������룺");
      				  
			}
			password2 = 0;		
		}
	}

	
	
//����Ա����ʶ��	
void KeyScan_M(){

	switch(key){
	 
		case 1:  //����1
			//ClrScreen();			
			 LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 1;
		  break;
	  case 2:  //����2
			 LCD_PutString(d,3,"*");
	     Delay_Ms(5000);
		   d++;        
		   password2 = password2 * 10 + 2;
		   break;
	  case 3:  //����3
			 LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;        
		  password2 = password2 * 10 + 3;
		  break;
	  case 12: break;//��A�Ǹ�����
	  case 4:  //����4
			 LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 4;
		  break;
		case 5:  //����5
			 LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 5;
		  break;
		case 6:  //����6
			 LCD_PutString(d,3,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password2 = password2 * 10 + 6;
		  break;
		case 13: break;//(B��)
		case 7:  //����7
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
		case 0:    //����0��
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
					LCD_PutString(a,2,'*');     // ����Ļ
				}
		 }*/
			break;
		case 15:   //���أ����������������롱����
			break;
		
				}
		 
		
			
		
	}

	
	void keyscan2()
	{
	

	switch(key){
	 
		case 1:  //����1
			//ClrScreen();			
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password3 = password3 * 10 + 1;
		  break;
	  case 2:  //����2
			 LCD_PutString(d,2,"*");
	     Delay_Ms(5000);
		   d++;        
		   password3 = password3 * 10 + 2;
		   break;
	  case 3:  //����3
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        
		  password3 = password3 * 10 + 3;
		  break;
	  case 12: break;//��A�Ǹ�����
	  case 4:  //����4
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password3 = password3 * 10 + 4;
		  break;
		case 5:  //����5
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password3 = password3 * 10 + 5;
		  break;
		case 6:  //����6
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password3 = password3 * 10 + 6;
		  break;
		case 13: break;//(B��)
		case 7:  //����7
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
		case 0:    //����0��
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
					LCD_PutString(a,2,'*');     // ����Ļ
				}
		 }*/
			break;
		case 15:   //���أ����������������롱����
			break;
		
				}
		 
		
			
		
	}

	void keyscan3(){

	switch(key){
	 
		case 1:  //����1
			//ClrScreen();			
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password4 = password4 * 10 + 1;
		  break;
	  case 2:  //����2
			 LCD_PutString(d,2,"*");
	     Delay_Ms(5000);
		   d++;        
		   password4 = password4 * 10 + 2;
		   break;
	  case 3:  //����3
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        
		  password4 = password4 * 10 + 3;
		  break;
	  case 12: break;//��A�Ǹ�����
	  case 4:  //����4
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password4 = password4 * 10 + 4;
		  break;
		case 5:  //����5
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password4 = password4 * 10 + 5;
		  break;
		case 6:  //����6
			 LCD_PutString(d,2,"*");
		  Delay_Ms(5000);
		  d++;        // d = 0 -->  d = 1
		  password4 = password4 * 10 + 6;
		  break;
		case 13: break;//(B��)
		case 7:  //����7
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
		case 0:    //����0��
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
					LCD_PutString(a,2,'*');     // ����Ļ
				}
		 }*/
			break;
		case 15:   //���أ����������������롱����
			break;
		
				}
		 
		
			
		
					
		}

		
void management()
{
		ClrScreen();
		LCD_PutString(0,1,"�������Աģʽ");
		LCD_PutString(0,2,"�������������: ");
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
								LCD_PutString(0,2,"����Ա��֤�ɹ�"); 
								Delay_Ms(1000);
								break;
						//ISP_Check2();  //���� �� ʶ��ɹ���ͨ��				
						}
						else {
								ClrScreen();
								LCD_PutString(0,1,"�������");
								//ISP_Check1();  //���ţ� �������
								Delay_Ms(1000);
								LCD_PutString(0,2,"��������������");
								Delay_Ms(30000);

								ClrScreen();
								LCD_PutString(0, 1, "���������룺");

						}
						password2 = 0;		
				}					
		}
		length = sizeof (password1)/sizeof(password1[0]);
		ClrScreen();
		LCD_PutString(0,1,"  ����ϵͳ����  ");
		LCD_PutString(0,2,"    1.��������    ");
		LCD_PutString(0,3,"    2.ɾȥ����    ");
		LCD_PutString(0,4,"    3.�޸�����    ");
		while(1)
		{
				key = KeyDown();
				switch(key)
				{
						case 12:
							n=1;
							key=-1;
							ClrScreen();
							LCD_PutString(0,1,"  ��������룺  ");
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
							LCD_PutString(0,1,"  ������ӳɹ�  ");
							Delay_Ms(2000);
							break;

						case 13:
							key=-1;
							n=1;
							ClrScreen();
							LCD_PutString(0,1,"  ��ɾȥ���룺  ");
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
							LCD_PutString(0,1,"  ����ɾȥ�ɹ�  ");
							Delay_Ms(2000);
							break;

						case 14:
								n=1;
								key=-1;
								ClrScreen();
								LCD_PutString(0,1,"  ����ǰ���룺  ");
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
								LCD_PutString(0,1,"  ���ĺ����룺  ");
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
								LCD_PutString(0,1,"  ��������ɹ�  ");
								break;
				}
				if(n==1)
				{
					break;
				}

		}

}










