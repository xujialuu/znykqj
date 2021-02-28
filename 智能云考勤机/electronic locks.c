#include "stc8.h"
#include "1cd_12864.h"
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
#define BUTTON_ PORT P1 //定义按键端口
#define passwordBit 6  //定义初始密码为六位
sbit LED=P3^7;         //***等下改***  蜂鸣器和led灯相关配合显示
sbit BUZZER=P2^3;
uchar code table[]={0x30, 0x31 , 0x32, 0x33,0x34 ,0x35,0x36,0x37,0x38,0x39, 'A','B','C','D','E','F'}; //0-9以及abcdef
uchar Original_password[passwordBit]={0x30 ,0x31,0x32,0x33,0x34,0x35} ;                             //初始密码为012345（六位）
uchar code Set_password[]={0x30,0x31 ,0x32 ,0x33,0x34,0x35,0x36,0x37 ,0x38,0x39,'A','B','C','D','E','F'};
/*相关提示语*/
uchar code dis[]={"Please selects menu ! Button1 selects normal mode. Button2 selects modify system password! !"} ;  //选择模式：正常模式 / 修改密码
uchar code test1[]={"Password error"};
uchar code test2[]={"Password correct"};
uchar code test3[]={"Please input"} ;
uchar code test4[]={"Check passwor d."};
uchar code test5[]={"Input again!! !"};
uchar code test6[]={"System open（欢迎光临）"};
uchar code conceal='*';
uchar code menuString1 []={"Operation "};
uchar code menustring2[]={ "Modify Password"} ;
uchar save[16]={0};
uchar operationFlag=0;					//按button1 或者 button2
uchar flag=1 ;
uchar cnt=0;
uchar systemFlag=1 ;            
uchar k1=0;
uchar k2=0;
uchar modify=0;
uchar exitFlag=1;


/***********************************函数声明区**********************************/
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
函数名称:延时函数
参数:延时数
返回值:无
******************************************************/

void delay_ ms (uint i){
	uint j=0;
	uint n=0 ;
	for(j=0;j<i;j++)
		for(n=0 ;n<=118 ;n++) ;}

		
/*函数名称：正常模式函数
	作用：进入之后自定义要干啥子
	返回值：无*/		
void entry (void)     
{
	uchar i=0 ;
	LCD_ Clear() ;
	LCD Write_ String(0,0, "Entry SYSTEM") ;
	LCD_ Write_ String(0,1, "KEY1 Exit") ;  //key1是中断系统的开关怎么定义呀 奇奇怪怪（窃以为不用的）
	BUZZER=1 ;
	LED=1 ;
	while (exitFlag)      //正常模式是个死循环 必须要（?外部中断?） 按下按钮 让exitFlag = 0 退出正常模式;
	{
		if(i==100)
		{	
			i=0 ;
			LED=!LED;//正常执行：点亮led灯 让蜂鸣器响   ***要加上电子锁在这里***
		}
		BUZZER=! BUZZER ;
		i++ ;
		delay_ ms(10) ;
}

}



/*修改密码*/
void modify_ Password (void)
{
	LCD_ Clear() ;
	LCD_ Write_ String(0,0,test3) ;
	LCD_ Write_ Com(0XC0) ;
	while (modify==0)
		Scan_ Button() ;
}





/*矩阵键盘扫描*/
uchar Scan_ Button (void)
{
	uchar i=0 , count=0 , temp=0 ,LINE[4]={0xef ,0xdf ,0xbf ,0x7f} ;
	
	BUTTON_ PORT=0xff ;   1111 1111 
	
	for(i=0;i<4;i++)							//i = 0,1,2,3
	{
		BUTTON_ PORT = LINE[i] ;    //矩阵键盘分别1110 1111/ 1101 1111/ 1011 1111/ 0111 1111
		delay_ ms(20) ; 
		temp = 0x01 ;                // 0000 0001
		for (count=0 ;count<4 ;count++)   //count = 0,1,2,3
		{
			if(! (BUTTON PORT &temp) ){        //1110 1111 &   0000 0001 = 0000 0001  （if（一坨 = 0）就进入循环）    
					
				if (systemFlag==1){
					LCD_ Write_ Data (conceal) ;   //可以屏蔽密码'*‘
					save [k1++]=table [ (count+i*4) ] ;   //存储密码（初始化k1 = 0）

					if(k1== passwordBit){
						kl=0;
						Check_ Password() ;
						}
					}
			else if (systemFlag==2)
			{
				Original_ pas sword [k2++]=table [ (count+i*4) ] ;   //密码修改在原始密码中覆盖掉
				LCD_ Write_ Data( (count+i*4)+'0') ;
				if (k2 == passwordBit)
				{
					k2=0 ;
					renew_Password() ;     //更新密码
				}
			}
			else if (0==systemFlag){operationFlag= (count+i*4);}   //直接设置变量
			while (! (BUTTON_ PORT&temp)) ; //松开
			return (count+i*4) ;
			}
		temp<<=1;
		}
	}
return 0xff ;
}



/*更新密码*/
void renew_Password (void){
	LCD_ Clear () ;
	LCD_ Write_ String(0,0 ,menuString2) ;
	LCD_ Write_ String(0,1, "Finished! ! !") ; //提示密码完成
	systemFlag=0;
	modify=1 ;
	delay_ ms (2000) ;
}







/*验证密码*/
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
	if (operationFlag==1)         //按下1 是正常模式
	{
		exitFlag=1 ;
		entry() ;
		LED=1;			//正常执行
		delay_ ms (2000);
	}
	else if (operationFlag==2)   //按下2 是修改密码
{

		systemFlag=2 ;
		modify_ Password() ;		//修改密码
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
		systemFlag = 0;  //预留
	}
}	





int main (void)
{
	LCD_ Init() ;    //lcd初始化
	IT0=1 ;						//初始化中断
	EX0=1 ;
	EA=1 ;
	LCD_ Clear() ;    //清屏
	LCD_ Write_ String(0,0,"Please input") ;
	LCD_ Write_ String(0,1, "password.. .") ;
	delay_ ms(2000) ;
	LCD_ Clear() ;
	LCD_ Write_ Com(0x80) ;  // ？？ 地址归位
	while (flag==1){
		Scan_ Button();    //按键扫描 密码正确再进行下一步
	} 
	delay_ ms (2000) ;
	LCD_ Clear() ;
	LCD_ Write_ String(0,0,test6) ;   //lcd提示选择模式
	delay_ ms (2000) ;
	while(l){
		Menu();                      //执行某个模式入口
	}  
	return 0 ;
}


/*外部中断系统函数*/

void int0_ Handler (void) interrupt 0
{
		exitFlag=0 ;
}


