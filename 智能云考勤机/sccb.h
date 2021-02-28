#ifndef _SCCB_H_
#define _SCCB_H_


sbit SCCB_SIC=P2^1;		  //ʱ��
sbit SCCB_SID=P2^0;		  //����

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long
#define DELAYTIME 200

void startSCCB(void);
void stopSCCB(void);
void noAck(void);
unsigned char getAck();
unsigned char SCCBwriteByte(unsigned char dat);
unsigned char SCCBreadByte(void);

#endif