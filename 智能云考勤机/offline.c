#include<STC8.h>
#include<offline.h>
#define uchar unsigned char
//管脚定义
sbit fwcs   =P1^7;///CS
sbit fwsck  =P5^4;//CLK
sbit fwsi   =P5^5;//DO(IO1)
sbit fwso   =P1^6;//DI(IO0)

//spi模拟写
void w25wspi(uchar dat)
{
	uchar i;
	for(i=0;i<8;i++)
	{
		if(dat & 0x80)
		{
			fwso=1;//用IO口电平表示需要写入的数据
		}
		else
		{
			fwso=0;
		}
		fwsck=1;//标准SPI在时钟信号上升沿写入
		dat=dat<<1;//向左移位，判断各位数据
		fwsck=0;//使下次循环中仍能从上升沿中读取数据
	}
	fwso=1;
	fwsck=0;
}
//spi模拟读
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
		fwsck=1;//在下降沿读出
	}
	fwsck=0;
	return rs;
}
//双倍速读
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


//读取状态寄存器1
uchar readrs1()
{
	uchar rs;
	fwcs=0;
	w25wspi(ReadStatusRegister1);
	rs=w25rspi();
	fwcs=1;
	return rs;
}

//读取状态寄存器2
uchar readrs2()
{
	uchar rs;
	fwcs=0;
	w25wspi(ReadStatusRegister2);
	rs=w25rspi();
	fwcs=1;
	return rs;
}

//读取状态寄存器3
uchar readrs3()
{
	uchar rs;
	fwcs=0;
	w25wspi(ReadStatusRegister3);
	rs=w25rspi();
	fwcs=1;
	return rs;
}
//初始化
void init_w25q128()
{
	int i,j;
	P1M1 = 0xC0;  //开漏 1.6 、1.7   P1口配置寄存器1
	P1M0 = 0xC0;  //开漏             P1口配置寄存器0
	P5M1 = 0x30;  //开漏 5.4 、5.5
	P5M0 = 0x30;  //开漏：开漏输出控制输出低电平为接地，控制输出高电平为高阻态
	fwcs=1;//cs较高进入断电状态 
	fwso=1;
	fwsck=0;
	//fwrst=1;
	for(j=0;j<200;j++)
	{
		for(i=0;i<200;i++);
	}
	reset_w25q128();
}


//复位w25q128
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

//读取数据
//buf：读出数据缓冲区f
//black_numb：块号
//page_numb：页号
//len:读取长度为 len+1，最多读256个字节
//成功返回 1，失败返回 0
uchar readdata(uchar * buf,uchar block_numb,uchar page_numb,uchar len)
{
		uchar i,j;
		uchar rs[4];
		
		i=BUSY;
		j=0;
		//是否忙
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

//双倍速读，
uchar fastreaddata(uchar * buf,uchar block_numb,uchar page_numb,uchar len)
{
		uchar i,j;
		uchar rs[4];

		i=BUSY;
		j=0;
		//是否忙
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

//块擦除命令
//block_numb：块号
//成功返回 1，失败返回 0
uchar eraseblock(uchar block_numb)
{
	uchar i,j;
	
	//是否忙
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

	//写使能
	fwcs=0;
	w25wspi(WriteEnable);
	fwcs=1;
	
	//写使能执行是否完成
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
	
	//执行擦除命令
	fwcs=0;
	w25wspi(SectorErase64k);
	w25wspi(block_numb);
	w25wspi(0);
	w25wspi(0);
	fwcs=1;
	
	//是否完成擦除
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
//页编程
//buf：要写入数据
//black_numb：块号
//page_numb：页号
//len:编程长度为 len+1，最写入256个字节
//成功返回 1，失败返回 0
uchar pageprogramblock(uchar * buf,uchar block_numb,uchar page_numb,uchar len)
{
	uchar i,j;
	i=BUSY;
	j=0;
	//是否忙
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
	
	//写使能
	fwcs=0;
	w25wspi(WriteEnable);
	fwcs=1;

	i=0;
	j=0;
	//写使能执行完成
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

	//执行页编程
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
	
	//是否完成页编程
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