#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_


/* A��KeyValue = 3��B��KeyValue = 7��
   C��KeyValue = 11��D��KeyValue = 15��
	 ��*ָ��ģ��*����ʹ�����ã��ݶ����� A : ��   B�� ��
	                      C ��OKȷ�� D��cancelȡ��

	 ��*���������*����ʹ�����ã��ݶ�����ABC������   D�൱����һ��delet����*/




#define GPIO_Key P7	//���尴������˿�  

sbit lock = P2^7;  //����������Ĺܽź� ���͵�ƽ�������ߵ�ƽ������
void KeyDown();  //��������һ��ֵ
void KeyScan();  //��ʾ��lcd��Ļ��


#endif