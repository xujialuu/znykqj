#include "stc8.h"
#include "1cd_12864.h"
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define BUTTON_ PORT P1 //���尴���˿�
#define passwordBit 6  //�����ʼ����Ϊ��λ
sbit LED=P3^7;         //***���¸�***  ��������led����������ʾ
sbit BUZZER=P2^3;
uchar code table[]={0x30, 0x31 , 0x32, 0x33,0x34 ,0x35,0x36,0x37,0x38,0x39, 'A','B','C','D','E','F'}; //0-9�Լ�abcdef
uchar Original_password[passwordBit]={0x30 ,0x31,0x32,0x33,0x34,0x35} ;                             //��ʼ����Ϊ012345����λ��
uchar code Set_password[]={0x30,0x31 ,0x32 ,0x33,0x34,0x35,0x36,0x37 ,0x38,0x39,'A','B','C','D','E','F'};
/*�����ʾ��*/
uchar code dis[]={"Please selects menu ! Button1 selects normal mode. Button2 selects modify system password! !"} ;  //ѡ��ģʽ������ģʽ / �޸�����
uchar code test1[]={"Password error"};
uchar code test2[]={"Password correct"};
uchar code test3[]={"Please input"} ;
uchar code test4[]={"Check passwor d."};
uchar code test5[]={"Input again!! !"};
uchar code test6[]={"System open����ӭ���٣�"};
uchar code conceal='*';
uchar code menuString1 []={"Operation "};
uchar code menustring2[]={ "Modify Password"} ;
uchar save[16]={0};
uchar operationFlag=0;					//��button1 ���� button2
uchar flag=1 ;
uchar cnt=0;
uchar systemFlag=1 ;            
uchar k1=0;
uchar k2=0;
uchar modify=0;
uchar exitFlag=1;


/***********************************����������**********************************/
void delay_ms(uint i) ;
uchar Scan_Button(void) ;
void Check_Password(void) ; .
void Menu (void) ;
void modify_Password(void) ;
void renew_Password(void) ;
void input_Password(void) ; .
void entry(void) ;
void displayMenu(void) ;



/*****************************************************
��������:��ʱ����
����:��ʱ��
����ֵ:��
******************************************************/

void delay_ ms (uint i){
	uint j=0;
	uint n=0 ;
	for(j=0;j<i;j++)
		for(n=0 ;n<=118 ;n++) ;}

		
/*�������ƣ�����ģʽ����
	���ã�����֮���Զ���Ҫ��ɶ��
	����ֵ����*/		
void entry (void)     
{
	uchar i=0 ;
	LCD_ Clear() ;
	LCD Write_ String(0,0, "Entry SYSTEM") ;
	LCD_ Write_ String(0,1, "KEY1 Exit") ;  //key1���ж�ϵͳ�Ŀ�����ô����ѽ ����ֹ֣�����Ϊ���õģ�
	BUZZER=1 ;
	LED=1 ;
	while (exitFlag)      //����ģʽ�Ǹ���ѭ�� ����Ҫ��?�ⲿ�ж�?�� ���°�ť ��exitFlag = 0 �˳�����ģʽ;
	{
		if(i==100)
		{	
			i=0 ;
			LED=!LED;//����ִ�У�����led�� �÷�������   ***Ҫ���ϵ�����������***
		}
		BUZZER=! BUZZER ;
		i++ ;
		delay_ ms(10) ;
}

}



/*�޸�����*/
void modify_ Password (void)
{
	LCD_ Clear() ;
	LCD_ Write_ String(0,0,test3) ;
	LCD_ Write_ Com(0XC0) ;
	while (modify==0)
		Scan_ Button() ;
}





/*�������ɨ��*/
uchar Scan_ Button (void)
{
	uchar i=0 , count=0 , temp=0 ,LINE[4]={0xef ,0xdf ,0xbf ,0x7f} ;
	
	BUTTON_ PORT=0xff ;   1111 1111 
	
	for(i=0;i<4;i++)							//i = 0,1,2,3
	{
		BUTTON_ PORT = LINE[i] ;    //������̷ֱ�1110 1111/ 1101 1111/ 1011 1111/ 0111 1111
		delay_ ms(20) ; 
		temp = 0x01 ;                // 0000 0001
		for (count=0 ;count<4 ;count++)   //count = 0,1,2,3
		{
			if(! (BUTTON PORT &temp) ){        //1110 1111 &   0000 0001 = 0000 0001  ��if��һ�� = 0���ͽ���ѭ����    
					
				if (systemFlag==1){
					LCD_ Write_ Data (conceal) ;   //������������'*��
					save [k1++]=table [ (count+i*4) ] ;   //�洢���루��ʼ��k1 = 0��

					if(k1== passwordBit){
						kl=0;
						Check_ Password() ;
						}
					}
			else if (systemFlag==2)
			{
				Original_ pas sword [k2++]=table [ (count+i*4) ] ;   //�����޸���ԭʼ�����и��ǵ�
				LCD_ Write_ Data( (count+i*4)+'0') ;
				if (k2 == passwordBit)
				{
					k2=0 ;
					renew_Password() ;     //��������
				}
			}
			else if (0==systemFlag){operationFlag= (count+i*4);}   //ֱ�����ñ���
			while (! (BUTTON_ PORT&temp)) ; //�ɿ�
			return (count+i*4) ;
			}
		temp<<=1;
		}
	}
return 0xff ;
}



/*��������*/
void renew_Password (void){
	LCD_ Clear () ;
	LCD_ Write_ String(0,0 ,menuString2) ;
	LCD_ Write_ String(0,1, "Finished! ! !") ; //��ʾ�������
	systemFlag=0;
	modify=1 ;
	delay_ ms (2000) ;
}







/*��֤����*/
void Check_ Password (void)
{
	uchar i=0 ;
	for(i=0 ;i<passwordBit;i++)
	{
		if (save [i] ! =Original_ password[i])
			break ;
	if (i == passwordBit)
	{
		LCD_ Write_ String(0,l,test2) ;
		cnt=0 ;
		flag=0 ;
		systemFlag=0;
	}
	else
	{
		LCD_ Write_ String(0,1,testl) ;
		cnt++ ;
		flag=1 ;
		delay_ms (2000) ;
		LCD_ Write_ String(0,0,test5) ;
		systemFlag=l;
	}
	delay_ ms (2000) ;
	LCD_ Clear() ;
	LCD_ Write_ Com(0x80) ;
}
	




void displayMenu (void)
{
	
	uchar i=0 ;
	LCD_ Clear() ;
	LCD_ Write_Com (0x80) ;
	for(i=0;i<91 ;i++)
	{
		if(i==16)
			LCD_ Write_ _Com(0xc0) ;
		else if(i==32){
			LCD_ Clear() ;
			LCD_Write_Com(0x80);}
			
		else if(i == 48)
				LCD_Write_Com(0xc0);
		else if(i == 64){
				LCD_Clear();
				LCD_Write_Com(0xc0);
		else if (i == 80)
			LCD_Write_Com(0xc0);
		else;
		LCD_Write_Data(dis[i]);
		delat_ms(300);
			
				}
		}
	}

	
	
	
void Menu(void){
	LED=1;
	modify = 0;
	displayMenu();
	systemFlag = 0;
	while ( (operationFlag!=1) && (operationFlag!=2))
  {
		Scan_ Button();
	}
	if (operationFlag==1)         //����1 ������ģʽ
	{
		exitFlag=1 ;
		entry() ;
		LED=1;			//����ִ��
		delay_ ms (2000);
	}
	else if (operationFlag==2)   //����2 ���޸�����
{

		systemFlag=2 ;
		modify_ Password() ;		//�޸�����
		LCD_ Clear() ;
		LCD_ Write_ String(0,0,"Please input") ;
		LCD_ Write_ String(0,1 , "password...") ;
		delay_ms (2000) ;
		LCD_ Clear() ;
		systemFlag=l;
		flag=1 ;
		LCD_ Write_ Com(0x80) ;
		while (flag==1){
		
			Scan_Button();
		}
		displayMenu();
		delay_ms(2000);
	}
	else{
		systemFlag = 0;  //Ԥ��
	}
}	





int main (void)
{
	LCD_ Init() ;    //lcd��ʼ��
	IT0=1 ;						//��ʼ���ж�
	EX0=1 ;
	EA=1 ;
	LCD_ Clear() ;    //����
	LCD_ Write_ String(0,0,"Please input") ;
	LCD_ Write_ String(0,1, "password.. .") ;
	delay_ ms(2000) ;
	LCD_ Clear() ;
	LCD_ Write_ Com(0x80) ;  // ���� ��ַ��λ
	while (flag==1){
		Scan_ Button();    //����ɨ�� ������ȷ�ٽ�����һ��
	} 
	delay_ ms (2000) ;
	LCD_ Clear() ;
	LCD_ Write_ String(0,0,test6) ;   //lcd��ʾѡ��ģʽ
	delay_ ms (2000) ;
	while(l){
		Menu();                      //ִ��ĳ��ģʽ���
	}  
	return 0 ;
}


/*�ⲿ�ж�ϵͳ����*/

void int0_ Handler (void) interrupt 0
{
		exitFlag=0 ;
}


