#ifndef	_W25Q128_H_
#define	_W25Q128_H_

#include "STC8.H"

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

//------------------------�����----------------------------
#define WriteEnable                  0x06    //дʹ��
#define WriteEnableVolatile          0x50    //��ʧ�ԼĴ���дʹ��
#define WriteDisable                 0x04    //д��ֹ
#define ReadStatusRegister1          0x05    //��״̬�Ĵ���1
#define ReadStatusRegister2          0x35    //��״̬�Ĵ���2
#define ReadStatusRegister3          0x15    //��״̬�Ĵ���3
#define WriteStatusRegister1         0x01    //д״̬�Ĵ���1
#define WriteStatusRegister2         0x31    //д״̬�Ĵ���2
#define WriteStatusRegister3         0x11    //д״̬�Ĵ���3
#define ReadData                     0x03    //������
#define PageProgram                  0x02    //ҳ���
#define SectorErase64k               0xd8    //��������
#define ChipErase                    0xc7    //оƬ����
#define ReadUniqueIDNumber           0x4b    //��ȡΨһ�豸��
#define ReadSFDPRegister             0x5a    //��sfpd�Ĵ���
#define EraseSecurityRegisters       0x44    //������ȫ�Ĵ���
#define ProgramSecurityRegisters     0x42    //��ȫ�Ĵ������
#define ReadSecurityRegisters        0x48    //��ȡ��ȫ�Ĵ���
#define IndividualBlockSectorLock    0x36    //������/��������
#define IndividualBlockSectorUnlock  0x39    //������/��������
#define ReadBlockSectorLock          0x3d    //��ȡ������/������
#define GlobalBlockSectorLock        0x7e    //ȫ�ּ���
#define GlobalBlockSectorUnlock      0x98    //ȫ�ֽ���
#define EnableReset                  0x66    //��λʹ��
#define ResetDevice                  0x99    //ϵͳ��λ
#define FastReadData                 0x3b    //���ٶ�ȡ

//-----------------------------״̬----------------------------------
#define BUSY              0x01   //W25Q128����״̬
#define WEL               0X02   //W25Q128дʹ��λ

void ms1(uchar time);

void init_w25q128();  //����W25Q128
void reset_w25q128();  //��λW25q128

uchar readrs1();
uchar readrs2();
uchar readrs3();

//��ȡ����
//buf���������ݻ�����f
//black_numb�����
//page_numb��ҳ��
//len:��ȡ����Ϊ len+1������256���ֽ�
//�ɹ����� 1��ʧ�ܷ��� 0
uchar readdata(uchar * buf,uchar block_numb,uchar page_numb,uchar len);
uchar fastreaddata(uchar * buf,uchar block_numb,uchar page_numb,uchar len);

//���������
//block_numb�����
//�ɹ����� 1��ʧ�ܷ��� 0
uchar eraseblock(uchar block_numb);

//ҳ���
//buf��Ҫд������
//black_numb�����
//page_numb��ҳ��
//len:��̳���Ϊ len+1����д��256���ֽ�
//�ɹ����� 1��ʧ�ܷ��� 0
uchar pageprogramblock(uchar * buf,uchar block_numb,uchar page_numb,uchar len);

void sendchr(uchar a1);

#endif