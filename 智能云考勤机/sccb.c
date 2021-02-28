//SCCB���� ��I2C���߷ǳ�����  
#include  "stc8.h"
#include "sccb.h"
#include "delay.h"
#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

/*
-----------------------------------------------
   ����: start����,SCCB����ʼ�ź�
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
void startSCCB()
{
	
 SCCB_SID=1;
 SCCB_SIC=1;
 Delay_Us(175); 
 SCCB_SID=0;
  Delay_Us(175); 
 SCCB_SIC=0;
}
/*
-----------------------------------------------
   ����: stop����,SCCB��ֹͣ�ź�
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
void stopSCCB()
{
 SCCB_SID=0;
  Delay_Us(175);
 SCCB_SIC=1;
 Delay_Us(175); 
 SCCB_SID=1;
 Delay_Us(175); 
}

/*
-----------------------------------------------
   ����: noAck,����������ȡ�е����һ����������
   ����: ��
 ����ֵ: ��
-----------------------------------------------
*/
void noAck(void)
{

 Delay_Us(10); 
 SCCB_SID=1;

 SCCB_SIC=1;
  Delay_Us(175);
 SCCB_SIC=0;
  Delay_Us(175); 
 SCCB_SID=0;
 Delay_Us(175);
}

u8 getAck() 
{
 u8  Error;

 SCCB_SID=1;//����SCCB_SIDΪ����
  
 Delay_Us(175); 
 SCCB_SIC=1;
 Delay_Us(175); 
 Error=SCCB_SID;
 Delay_Us(175);
 SCCB_SIC=0; 
 Delay_Us(175);

 SCCB_SID=0;
 return !Error;
}

/*
-----------------------------------------------
   ����: д��һ���ֽڵ����ݵ�SCCB
   ����: д������
 ����ֵ: ���ͳɹ�����1������ʧ�ܷ���0
-----------------------------------------------
*/
u8 SCCBwriteByte(u8 dat)
{
 u8 i;
 for(i=0;i<8;i++)
 {
  SCCB_SID=((dat<<i)&0x80);
   Delay_Us(175);
  SCCB_SIC=1;
   Delay_Us(175); 
  SCCB_SIC=0;
 }
 SCCB_SID=0;
 return getAck();
}

/*
-----------------------------------------------
   ����: һ���ֽ����ݶ�ȡ���ҷ���
   ����: ��
 ����ֵ: ��ȡ��������
-----------------------------------------------
*/
u8 SCCBreadByte(void)
{
 u8 i,rbyte=0;


 SCCB_SID=1;//����SCCB_SIDΪ����

 for(i=0;i<8;i++)
 {
  Delay_Us(175); 
  SCCB_SIC=1;  
  if(SCCB_SID) rbyte|=(0x80>>i);
 Delay_Us(175); 
  SCCB_SIC=0;
   Delay_Us(175);
 } 


 SCCB_SID=0;
 return rbyte;
}
