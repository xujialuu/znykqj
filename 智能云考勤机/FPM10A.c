#include "FPM10A.h"
#include "stc8.h"
#include "key.h"
#include "uart.h"
#include "lcd_12864.h"
#include "delay.h"
#include "voice.h"
#include "led.h"

#include "keyboard.h"

volatile unsigned char FPM10A_RECEICE_BUFFER[32];
unsigned int finger_id = 0;
unsigned char count = 0;
extern int key;


//FINGERPRINTͨ��Э�鶨��

code unsigned char FPM10A_Get_Device[10] ={0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};//������֤
code unsigned char FPM10A_Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};  //Э���ͷ
code unsigned char FPM10A_Get_Img[6] = {0x01,0x00,0x03,0x01,0x00,0x05};    //���ָ��ͼ��
code unsigned char FPM10A_Get_Templete_Count[6] ={0x01,0x00,0x03,0x1D,0x00,0x21 }; //���ģ������
code unsigned char FPM10A_Search[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x03,0xE7,0x00,0xF8}; //����ָ��������Χ0 - 999,ʹ��BUFFER1�е�����������
code unsigned char FPM10A_Search_0_9[11]={0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x00,0x13,0x00,0x21}; //����0-9��ָ��
code unsigned char FPM10A_Img_To_Buffer1[7]={0x01,0x00,0x04,0x02,0x01,0x00,0x08}; //��ͼ����뵽BUFFER1
code unsigned char FPM10A_Img_To_Buffer2[7]={0x01,0x00,0x04,0x02,0x02,0x00,0x09}; //��ͼ����뵽BUFFER2
code unsigned char FPM10A_Reg_Model[6]={0x01,0x00,0x03,0x05,0x00,0x09}; //��BUFFER1��BUFFER2�ϳ�����ģ��
code unsigned char FPM10A_Delete_All_Model[6]={0x01,0x00,0x03,0x0d,0x00,0x11};//ɾ��ָ��ģ�������е�ģ��
volatile unsigned char  FPM10A_Save_Finger[9]={0x01,0x00,0x06,0x06,0x01,0x00,0x0B,0x00,0x19};//��BUFFER1�е��������ŵ�ָ����λ��
//volatile:ϵͳ�������´������ڵ��ڴ��ȡ���ݣ���ʹ��ǰ���ָ��ոմӸô���ȡ������
/*------------------ FINGERPRINT������ --------------------------*/
 //���Ͱ�ͷ
void FPM10A_Cmd_Send_Pack_Head(void)
{
	int i;	
	for(i=0;i<6;i++) //��ͷ
   {
     Uart_Send_Byte(FPM10A_Pack_Head[i]);   
    }		
}
//����ָ��
void FPM10A_Cmd_Check(void)
{
	int i=0;
	FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
	for(i=0;i<10;i++)
	 {		
		Uart_Send_Byte(FPM10A_Get_Device[i]);
	  }
}
//���շ������ݻ���
void FPM10A_Receive_Data(unsigned char ucLength)
{
  unsigned char i;

  for (i=0;i<ucLength;i++)
     FPM10A_RECEICE_BUFFER[i] = Uart_Receive_Byte();

}

//FINGERPRINT_���ָ��ͼ������
void FPM10A_Cmd_Get_Img(void)
{
    unsigned char i;
    FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
    for(i=0;i<6;i++) //�������� 0x1d
	{
       Uart_Send_Byte(FPM10A_Get_Img[i]);
	}
}
//��ͼ��ת��������������Buffer1��
void FINGERPRINT_Cmd_Img_To_Buffer1(void)
{
 	unsigned char i;
	FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ      
   	for(i=0;i<7;i++)   //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
     {
      Uart_Send_Byte(FPM10A_Img_To_Buffer1[i]);
   	  }
}
//��ͼ��ת��������������Buffer2��
void FINGERPRINT_Cmd_Img_To_Buffer2(void)
{
     unsigned char i;
     for(i=0;i<6;i++)    //���Ͱ�ͷ
	 {
    	Uart_Send_Byte(FPM10A_Pack_Head[i]);   
   	 }
     for(i=0;i<7;i++)   //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
      {
      	Uart_Send_Byte(FPM10A_Img_To_Buffer2[i]);
   	  }
}
//����ȫ���û�999ö
void FPM10A_Cmd_Search_Finger(void)
{
       unsigned char i;	   	    
			 FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ
       for(i=0;i<11;i++)
           {
    	      Uart_Send_Byte(FPM10A_Search[i]);   
   		   }
}

void FPM10A_Cmd_Reg_Model(void)
{
       unsigned char i;	   
	    
			 FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ

       for(i=0;i<6;i++)
           {
    	      Uart_Send_Byte(FPM10A_Reg_Model[i]);   
   		   }


}
//ɾ��ָ��ģ���������ָ��ģ��
void FINGERPRINT_Cmd_Delete_All_Model(void)
{
     unsigned char i;    
    for(i=0;i<6;i++) //��ͷ
      Uart_Send_Byte(FPM10A_Pack_Head[i]);   
    for(i=0;i<6;i++) //����ϲ�ָ��ģ��
	   {
      Uart_Send_Byte(FPM10A_Delete_All_Model[i]);   
		 }	
}
//����ָ��
void FPM10A_Cmd_Save_Finger( unsigned int storeID )
{
       unsigned long temp = 0;
		   unsigned char i;
       FPM10A_Save_Finger[5] =(storeID&0xFF00)>>8;
       FPM10A_Save_Finger[6] = (storeID&0x00FF);
		   for(i=0;i<7;i++)   //����У���
		   	   temp = temp + FPM10A_Save_Finger[i]; 
		   FPM10A_Save_Finger[7]=(temp & 0x00FF00) >> 8; //���У������
		   FPM10A_Save_Finger[8]= temp & 0x0000FF;		   
       FPM10A_Cmd_Send_Pack_Head(); //����ͨ��Э���ͷ	
       for(i=0;i<9;i++)  
      		Uart_Send_Byte(FPM10A_Save_Finger[i]);      //�������� ��ͼ��ת���� ������ ����� CHAR_buffer1
}

/*���ָ��
void FPM10A_Add_Fingerprint()
{
	unsigned char id_show[]={0,0,0};
	ClrScreen(); //�����ʾ��  
	while(1)
	{
	 LCD_PutString(0,1,"������ָ��ID:");
	 LCD_PutString(0,2,"�ϣ�+ �£�-");
	 //�����ؼ�ֱ�ӻص����˵�
	 if(key == 15) 
		{
		 while(key == 15);
		 break;
		 }
	 //���ϼ�fingerֵ��һ 
	 if(key == 3)
		{
			 while(key == 3);
		   if(finger_id == 999)
			   {
				  finger_id = 0;
				 }
				else
				 {
					finger_id = finger_id + 1;
				 };
		}
		//���ϼ�fingerֵ��һ
	  if(key == 7)
		 {
				 while(key == 7);
				 if(finger_id == 0)
					 {
						finger_id = 999;
					  }
					else
						finger_id = finger_id - 1;
			}
	 //fingerֵ��ʾ���� 
	 id_show[0]=finger_id/100;
	 id_show[1]=finger_id%100/10;
	 id_show[2]=finger_id%100%10;
 	 LCD_PutString(0,3,"ID:");
	 Write_Cmd(0x88+4);
	 Write_Data(0x30+id_show[0]);
	 Write_Cmd(0x88+5);
	 Write_Data(0x30+id_show[1]);
	 Write_Cmd(0x88+6);
	 Write_Data(0x30+id_show[2]);
	 //��ȷ�ϼ���ʼ¼��ָ����Ϣ 		 			
	 if(key == 11)
	  {	
			  while(key == 11);
			  ClrScreen(); //�����ʾ��
			  LCD_PutString(0,1,"������ָ��");
			  do
		   {
			  //���·��ؼ��˳�¼�뷵��fingerID����״̬   
				if(key == 15) 
				 {
				  while(KEY_CANCEL==15);
				  break;
				  }
				FPM10A_Cmd_Get_Img(); //���ָ��ͼ��
				FPM10A_Receive_Data(12);
				//�жϽ��յ���ȷ����,����0ָ�ƻ�ȡ�ɹ�
				if(FPM10A_RECEICE_BUFFER[9]==0)
				 {
					Delay_Ms(100);
					FINGERPRINT_Cmd_Img_To_Buffer1();
				  FPM10A_Receive_Data(12);
					LCD_PutString(0,2,"����ɹ�");
					//Buzz_Times(1);
					Delay_Ms(500);
					LCD_PutString(0,3,"��ȷ�ϣ�����ָ��");
					do
					{
					 FPM10A_Cmd_Get_Img(); //���ָ��ͼ��
					 FPM10A_Receive_Data(12);
					//�жϽ��յ���ȷ����,����0ָ�ƻ�ȡ�ɹ�
					if(FPM10A_RECEICE_BUFFER[9]==0)
					 {
						Delay_Ms(100);
						FINGERPRINT_Cmd_Img_To_Buffer2();
				  	FPM10A_Receive_Data(12);
						FPM10A_Cmd_Reg_Model();//ת����������
	          FPM10A_Receive_Data(12); 
					  FPM10A_Cmd_Save_Finger(finger_id++);                		         
	          FPM10A_Receive_Data(12);
						LCD_PutString(0,4,"ָ��¼��ɹ�");
						//Buzz_Times(1);
						Delay_Ms(1000);
				    break;
				  	}
				   }while(key == 15);
	        break;
					}
				}while(key == 15);
			ClrScreen(); //�����ʾ��
			}
		//	Delay_Ms(500);
		}
}*/

/*����ָ��*/
void FPM10A_Find_Fingerprint()
{
	 unsigned int find_fingerid = 0;
	 unsigned char id_show[]={0,0,0};
	 Delay_Ms(10000);
   ClrScreen(); //�����ʾ��
	 LCD_PutString(0,1,"�밴��ָ ");
	 Delay_Ms(10000);
	 do
	 {  
			Led_Red_On();//**
			FPM10A_Cmd_Get_Img(); //���ָ��ͼ��
		  //Led_Red_On();	 //�����	
			FPM10A_Receive_Data(12);		
			//�жϽ��յ���ȷ����,����0ָ�ƻ�ȡ�ɹ�
			//Led_Red_On();	 //�����	
		 
			if(FPM10A_RECEICE_BUFFER[9]==0)
			{			
				Delay_Ms(100);
				FINGERPRINT_Cmd_Img_To_Buffer1();
				FPM10A_Receive_Data(12);		
				FPM10A_Cmd_Search_Finger();
				FPM10A_Receive_Data(16);			
				if(FPM10A_RECEICE_BUFFER[9] == 0) //������  
				{
					ClrScreen();
					LCD_PutString(0,1,"�밴��ָ ");
					LCD_PutString(0,2,"�����ɹ�");
					Delay_Ms(10000);
					Delay_Ms(10000);
					ClrScreen();
					LCD_PutString(0,2,"  ��ͨ��");
					Delay_Ms(10000);
					Led_Green_On();	 //�̵���
					P61 = 1;
					lock = 0;  //����������
					ISP_Check1();  //���� �� ʶ��ɹ���ͨ��
					//Led_Green_Off;
					//Buzz_Times(1);					
					//ƴ��ָ��ID��
					find_fingerid = FPM10A_RECEICE_BUFFER[10]*256 + FPM10A_RECEICE_BUFFER[11];					
					id_show[0]=find_fingerid/100;
					id_show[1]=find_fingerid%100/10;
					id_show[2]=find_fingerid%100%10;
					LCD_PutString(0,3,"ID:");
					Write_Cmd(0x88+4);
					Write_Data(0x30+id_show[0]);
					Write_Cmd(0x88+5);
					Write_Data(0x30+id_show[1]);
					Write_Cmd(0x88+6);
					Write_Data(0x30+id_show[2]);						
					Delay_Ms(2000);
					//Led_Green_On();
					Delay_Ms(2000);
					break;
				}
				else{ //û���ҵ�
					ClrScreen();
					LCD_PutString(0,1,"������ָ�� ");
					LCD_PutString(0,2,"δ�ҵ�ָ����Ϣ ");
					
					//Buzz_Times(3);
					/*����ط���ӵ�������������*/
					Delay_Ms(30000);
					ClrScreen();
					LCD_PutString(0, 1, "���������룺");
					while (1) {
							key = KeyDown();
							Delay_Ms(500);
							if (key != (-1)){
								KeyScan();
							}
							if (key == 15)
							{
								//Led_Green_On();	 //�̵���
							  break;
							}
					}
					break;
				}

			}
		}	while(key == 14);
}
/*ɾ�����д�����ָ�ƿ�
void FPM10A_Delete_All_Fingerprint()
{
		unsigned char i=0;
		ClrScreen(); //�����ʾ��
		LCD_PutString(1,1,"���ָ�ƿ⣿");
		do
		 {
			if(key == 11)
			{
				while(key == 11);
				LCD_PutString(0,2,"�����");
				Delay_Ms(300);
				for(i=0;i<8;i++)
				 {
					LCD_PutString(i,3,"*");
					Delay_Ms(200);
				 }
				FINGERPRINT_Cmd_Delete_All_Model();
			  FPM10A_Receive_Data(12); 
				LCD_PutString(2,4,"��ճɹ�");
			//	Buzz_Times(3);
				break;
			}
		 }while(key == 15);
}*/
/*�豸���*/
void Device_Check(void)
{
		unsigned char i=0;
		FPM10A_RECEICE_BUFFER[9]=1;
		ClrScreen(); //�����ʾ��
		LCD_PutString(0,1,"�豸������.....");
		Delay_Ms(5000);
		for(i=0;i<8;i++)
		{
			LCD_PutString(i,2,"*");
			Delay_Ms(800);
		}
		LCD_PutString(0,3,"�豸����ʧ��");  // *********
		FPM10A_Cmd_Check();
		FPM10A_Receive_Data(12);
    if(FPM10A_RECEICE_BUFFER[9] == 0)
		//if(1)
		{ 
			ClrScreen();
			LCD_PutString(0,2,"�豸���سɹ�");
		//	Buzz_Times(1);
			Delay_Ms(5000);
			
			ClrScreen();
			LCD_PutString(2,1,"��ӭʹ��");
			LCD_PutString(1,2,"ָ��ʶ��ϵͳ");
			Delay_Ms(5000);
			LCD_PutString(1,3,"ϵͳ��ʼ����");
			Delay_Ms(5000);
			for(i=0;i<8;i++)
		{
			LCD_PutString(i,4,"*");
			Delay_Ms(3000);
		}
	//	Buzz_Times(3);
		  Delay_Ms(1000);
		}
}





