#include "stc8.h"
#include "voice.h"

char  code  MESSAGE1[6]={0xAA,0x07,0x02,0x00,0x01,0xB4};	//���嵽����ռ���
char  code  MESSAGE2[6]={0xAA,0x07,0x02,0x00,0x02,0xB5};	//���嵽����ռ���
char  code  MESSAGE3[6]={0xAA,0x07,0x02,0x00,0x03,0xB6};	//���嵽����ռ���



void delay(unsigned int m)				//��ʱ����
    {
	  int  a=0,b=0;
	  for(a=0;a<500;a++)
	  for(b=0;b<m;b++);
	
	}


void ISP_Check1()						//���ڷ��͵��ú���(����ʶ��ɹ�)
{
  unsigned char x=0;	 

	  //a=0;
	   //while(MESSAGE[a]!= '\0')
	     for(x=0;x<6;x++)
   	   {
					SBUF = MESSAGE1[x];	        //SUBF����/���ͻ�����(�ֽд���ͨ�����⹦�ܼĴ���)
					while(!TI);				// �������ݴ���	(TI�����жϱ�־)
					TI = 0;					// ������ݴ��ͱ�־
		
		//a++;					    // ��һ���ַ�
       } 
}


void ISP_Check2()						//���ڷ��͵��ú���������ʶ��ʧ�ܣ�
{
  unsigned char x=0;	 

	  //a=0;
	   //while(MESSAGE[a]!= '\0')
	     for(x=0;x<6;x++)
   	   {
		SBUF = MESSAGE2[x];	        //SUBF����/���ͻ�����(�ֽд���ͨ�����⹦�ܼĴ���)
         while(!TI);				// �������ݴ���	(TI�����жϱ�־)
		 TI = 0;					// ������ݴ��ͱ�־
		
		//a++;					    // ��һ���ַ�
       } 
		 }		 
			 
void ISP_Check3()						//���ڷ��͵��ú����������������
{
  unsigned char x=0;	 

	  //a=0;
	   //while(MESSAGE[a]!= '\0')
	     for(x=0;x<6;x++)
   	   {
					SBUF = MESSAGE3[x];	        //SUBF����/���ͻ�����(�ֽд���ͨ�����⹦�ܼĴ���)
					while(!TI);				// �������ݴ���	(TI�����жϱ�־)
					TI = 0;					// ������ݴ��ͱ�־
		
		//a++;					    // ��һ���ַ�
       } 
		 }


void voice_init() 			 //������
{

	
	

		SCON = 0x50;        //REN=1�����н���״̬�����ڹ���ģʽ2     	   
		TMOD = 0x00;       //��ʱ��1Ϊģʽ0��16λ�Զ����أ�                
		AUXR = 0X40;		 //����1Tģʽ
		TL1=(65535-(24000000/4/9600));    //���ò�������װֵ
		TH1=(65535-(24000000/4/9600))>>8;

                         // ���в�������� STC8�ֲ�������ϸ˵�� 	 
      
		TR1  = 1;        //������ʱ��1                                                                      
		EA   = 1;        // �����ж� 
}