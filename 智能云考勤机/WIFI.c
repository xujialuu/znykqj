#include<stc8.h>	//51��Ƭ�����õ�ͷ�ļ�
#include "wifi.h"
#define uchar unsigned char		//�궨��һ���޷��ŵ�char����
#define uint unsigned int		//�궨��һ���޷��ŵ�int����

uchar Hour[]={0x0a,0x0b,"\0"};
volatile uint Flag=0;
//����һ�ֽ�
void sendByte(uchar b)
{
  SBUF = b;
  while(!TI);
  TI=0;
}

//�����ַ���
void sendString(uchar *s)
{
  while(*s != '\0')	//�ַ���Ĭ�Ͻ�β'\0'���Դ����ж��ַ����Ľ���
  {
    sendByte(*s);
    s++;
  }
}

//��ʼ��ESP8266WiFiģ��
void initEsp()
{
  uint a;
  P_SW2=0x01;
	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0x8F;		//�趨��ʱ��ֵ
	T2H = 0xFD;		//�趨��ʱ��ֵ
	AUXR |= 0x10;		//������ʱ��2
  IE2 = ES2; //ʹ�ܴ����ж�
 EA = 1; 

  for (a=0; a<50000; a++);		//��ʱ���룬��ģ����ʱ������
  sendString("AT+CWMODE=2\r\n");	//����ΪsoftAP��station����ģʽ

  //WiFi�ȵ㲻��ͨ���������ã���ʹ�ô������ֽ������ã������öϵ粻��ʧ
  /*
  for (a=0; a<20000; a++);
  sendString("AT+CWSAP='TEST','12345678',1,3\n"); //����WiFi�ȵ�
  */

  for (a=0; a<50000; a++);    
  sendString("AT+CIPMUX=1\r\n"); //����������

  for (a=0; a<20000; a++);
  sendString("AT+CIPSERVER=1,333\r\n");//����server���˿�Ϊ333

  for (a=0; a<20000; a++);
  sendString("AT+CIPSTO=50\r\n");     //��������ʱʱ������

  RI=0;
  ES=1;   //��ʼ����ɣ����п��жϴ�
}


/*//��ȡ���ݣ����ݸ�ʽʾ����+IPD,0,14:"time":"11:11"
void getData()
{
  uint a,i;
  if(receiveFlag)
  {
    for(i=0; i<2; i++)
    {
      Hour[i]=Buffer[17+i];
    }
    Hour[2]='\0';

    for(i=0; i<2; i++)
    {
      Minute[i]=Buffer[20+i];
    }
    Minute[2]='\0';

    //����ȡ�������ݷ��͵�������������ʾ
    for (a=0; a<10000; a++);	//��Ҫ��ʱ�������������ݴ��ҵ��¶���
    sendString(Hour);
    for (a=0; a<10000; a++);
    sendString(Minute);

    receiveFlag=0;
    count=0;
    for(i=0; i<22; i++)
    {
      Buffer[i]=0;
    }
  }
}

//������
void main()
{
  initEsp();			//��ʼ��WiFiģ��
  receiveFlag = 0;		//receiveFlag�ж�ִ��getData() �ı�־
  count = 0;			//count������RXDdata[count]������  
  while(1)
  { 
    getData();
  }
}

//�����жϽ�����Ϣ����������Ч��Ϣ
void uart() interrupt 4  
{
  if(RI == 1)	
  {
    ES = 0;     //�رմ����ж�
    RI = 0;     //������ڽ��ձ�־λ
    temp = SBUF; //�Ӵ��ڻ�����ȡ������

    if(count<20)	//��������յ���Ϣ���ȣ������ݴ��뻺����
    { 
      Buffer[count]=temp;
      count++;
      if(Buffer[0]=='+')  //�ж��Ƿ�Ϊ��Ч���ݣ�����WiFiģ����Զ�����"+PID.."��ͷ���ַ���
      {
        receiveFlag = 1; 
      }
      else
      {
        receiveFlag = 0;
        count = 0;
      }
    } 
    ES = 1; 
  }
}
*/
  
