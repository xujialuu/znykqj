#include<STC8.h>
#include<offline.h>
#define uchar unsigned char
//�ܽŶ���
sbit fwcs   =P1^7;///CS
sbit fwsck  =P5^4;//CLK
sbit fwsi   =P5^5;//DO(IO1)
sbit fwso   =P1^6;//DI(IO0)

//spiģ��д
void w25wspi(uchar dat)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		if(dat & 0x80)
		{
			fwso=1;//��IO�ڵ�ƽ��ʾ��Ҫд�������
		}
		else
		{
			fwso=0;
		}
		fwsck=1;//��׼SPI��ʱ���ź�������д��
		dat=dat<<1;//������λ���жϸ�λ����
		fwsck=0;//ʹ�´�ѭ�������ܴ��������ж�ȡ����
	}
	fwso=1;
	fwsck=0;
}
//spiģ���
uchar w25rspi()
{
	uchar i;
	uchar rs;
	
	for(i=0;i<8;i++)
	{
		fwsck=0;
		rs=rs<<1;
		if(fwsi)
			rs=rs | 1;
		fwsck=1;//���½��ض���
	}
	fwsck=0;
	return rs;
}
//˫���ٶ�
uchar w25frspi()
{
	uchar i;
	uchar rs;
	for(i=0;i<4;i++)
	{
		rs=rs<<2;
		fwsck=0;
		if(fwsi)
			rs=rs | 0x02;
		if(fwso)
			rs=rs | 0x01;
		fwsck=1;
	}
	fwso=1;
	fwsck=0;
	return rs;
}


//��ȡ״̬�Ĵ���1
uchar readrs1()
{
	uchar rs;
	fwcs=0;
	w25wspi(ReadStatusRegister1);
	rs=w25rspi();
	fwcs=1;
	return rs;
}

//��ȡ״̬�Ĵ���2
uchar readrs2()
{
	uchar rs;
	fwcs=0;
	w25wspi(ReadStatusRegister2);
	rs=w25rspi();
	fwcs=1;
	return rs;
}

//��ȡ״̬�Ĵ���3
uchar readrs3()
{
	uchar rs;
	fwcs=0;
	w25wspi(ReadStatusRegister3);
	rs=w25rspi();
	fwcs=1;
	return rs;
}
//��ʼ��
void init_w25q128()
{
	int i,j;
	P1M1 = 0xC0;  //��© 1.6 ��1.7   P1�����üĴ���1
	P1M0 = 0xC0;  //��©             P1�����üĴ���0
	P5M1 = 0x30;  //��© 5.4 ��5.5
	P5M0 = 0x30;  //��©����©�����������͵�ƽΪ�ӵأ���������ߵ�ƽΪ����̬
	fwcs=1;//cs�ϸ߽���ϵ�״̬ 
	fwso=1;
	fwsck=0;
	//fwrst=1;
	for(j=0;j<200;j++)
	{
		for(i=0;i<200;i++);
	}
	reset_w25q128();
}


//��λw25q128
void reset_w25q128()
{
	uchar i;
	fwcs=0;
	w25wspi(EnableReset);
	fwcs=1;
	for(i=0;i<100;i++);
	fwcs=0;
	w25wspi(ResetDevice);
	fwcs=1;
	for(i=0;i<240;i++);
}

//��ȡ����
//buf���������ݻ�����f
//black_numb�����
//page_numb��ҳ��
//len:��ȡ����Ϊ len+1������256���ֽ�
//�ɹ����� 1��ʧ�ܷ��� 0
uchar readdata(uchar * buf,uchar block_numb,uchar page_numb,uchar len)
{
		uchar i,j;
		uchar rs[4];
		
		i=BUSY;
		j=0;
		//�Ƿ�æ
		while(i==BUSY)
		{
			fwcs=0;
			w25wspi(ReadStatusRegister1);
			i=w25rspi();
			fwcs=1;
			i=i & BUSY;
			ms1(1);
			j++;
			if(j==128)
				return 0;
		}
		
		rs[0]=ReadData;
		rs[1]=block_numb;
		rs[2]=page_numb;
		rs[3]=0;
		
		fwcs=0;
		for(i=0;i<4;i++)
		{
			w25wspi(rs[i]);
		}
		for(i=0;i<len;i++)
		{
			buf[i]=w25rspi();
		}
		buf[len]=w25rspi();
		fwcs=1;
		return 1;
}

//˫���ٶ���
uchar fastreaddata(uchar * buf,uchar block_numb,uchar page_numb,uchar len)
{
		uchar i,j;
		uchar rs[4];

		i=BUSY;
		j=0;
		//�Ƿ�æ
		while(i==BUSY)
		{
			fwcs=0;
			w25wspi(ReadStatusRegister1);
			i=w25rspi();
			fwcs=1;
			i=i & BUSY;
			ms1(1);
			j++;
			if(j==128)
				return 0;
		}

		rs[0]=FastReadData;
		rs[1]=block_numb;
		rs[2]=page_numb;
		rs[3]=0;

		fwcs=0;
		for(i=0;i<4;i++)
		{
			w25wspi(rs[i]);
		}
		P1M1 = 0xC0;
		P1M0 = 0x80;
		w25wspi(0x00);
		for(i=0;i<len;i++)
		{
			buf[i]=w25frspi();
		}
		buf[len]=w25frspi();
		P1M1 = 0xC0;
		P1M0 = 0xC0;
		fwcs=1;
		return 1;
}

//���������
//block_numb�����
//�ɹ����� 1��ʧ�ܷ��� 0
uchar eraseblock(uchar block_numb)
{
	uchar i,j;
	
	//�Ƿ�æ
	i=BUSY;
	j=0;
	while(i==BUSY)
	{
		ms1(1);
		fwcs=0;
		w25wspi(ReadStatusRegister1);
		i=w25rspi();
		fwcs=1;
		i=i & BUSY;
		j++;
		if(j==128)
			return 0;
	}

	//дʹ��
	fwcs=0;
	w25wspi(WriteEnable);
	fwcs=1;
	
	//дʹ��ִ���Ƿ����
	i=0;
	j=0;
	while(i!=WEL)
	{
		ms1(1);
		fwcs=0;
		w25wspi(ReadStatusRegister1);
		i=w25rspi();
		fwcs=1;
		i=i & WEL;
		j++;
		if(j==254)
			return 0;
	}
	
	//ִ�в�������
	fwcs=0;
	w25wspi(SectorErase64k);
	w25wspi(block_numb);
	w25wspi(0);
	w25wspi(0);
	fwcs=1;
	
	//�Ƿ���ɲ���
	i=BUSY;
	j=0;
	while(i==BUSY)
	{
		ms1(1);
		fwcs=0;
		w25wspi(ReadStatusRegister1);
		i=w25rspi();
		fwcs=1;
		i=i & BUSY;
		j++;
		if(j==254)
			return 0;
	}
	i=WEL;
	j=0;
	while(i==WEL)
	{
		ms1(1);
		fwcs=0;
		w25wspi(ReadStatusRegister1);
		i=w25rspi();
		fwcs=1;
		i=i & WEL;
		j++;
		if(j==254)
			return 0;
	}
	return 1;
}
//ҳ���
//buf��Ҫд������
//black_numb�����
//page_numb��ҳ��
//len:��̳���Ϊ len+1����д��256���ֽ�
//�ɹ����� 1��ʧ�ܷ��� 0
uchar pageprogramblock(uchar * buf,uchar block_numb,uchar page_numb,uchar len)
{
	uchar i,j;
	i=BUSY;
	j=0;
	//�Ƿ�æ
	while(i==BUSY)
	{
		ms1(1);
		fwcs=0;
		w25wspi(ReadStatusRegister1);
		i=w25rspi();
		fwcs=1;
		i=i & BUSY;
		j++;
		if(j==128)
			return 0;
	}
	
	//дʹ��
	fwcs=0;
	w25wspi(WriteEnable);
	fwcs=1;

	i=0;
	j=0;
	//дʹ��ִ�����
	while(i!=WEL)
	{
		ms1(1);
		fwcs=0;
		w25wspi(ReadStatusRegister1);
		i=w25rspi();
		fwcs=1;
		i=i & WEL;
		j++;
		if(j==254)
			return 0;
	}

	//ִ��ҳ���
	fwcs=0;
	w25wspi(PageProgram);
	w25wspi(block_numb);
	w25wspi(page_numb);
	w25wspi(0);
	for(i=0;i<len;i++)
	{
		w25wspi(buf[i]);
	}
	w25wspi(buf[len]);
	fwcs=1;
	
	//�Ƿ����ҳ���
	i=BUSY;
	j=0;
	while(i==BUSY)
	{
		ms1(1);
		fwcs=0;
		w25wspi(ReadStatusRegister1);
		i=w25rspi();
		fwcs=1;
		i=i & BUSY;
		j++;
		if(j==254)
			return 0;
	}
	i=WEL;
	j=0;
	while(i==WEL)
	{
		ms1(1);
		fwcs=0;
		w25wspi(ReadStatusRegister1);
		i=w25rspi();
		fwcs=1;
		i=i & WEL;
		j++;
		if(j==254)
			return 0;
	}
	return 1;
}

void ms1(uchar time)		//@22.1184MHz
{
	uchar i, j, m;
	for(m=0;m<time;m++)
	{
		i = 29;
		j = 183;
		do
		{
			while (--j);
		} while (--i);
	}
}