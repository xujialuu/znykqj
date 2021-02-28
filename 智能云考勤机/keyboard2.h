#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_


/* A的KeyValue = 3；B的KeyValue = 7；
   C的KeyValue = 11；D的KeyValue = 15；
	 在*指纹模块*中行使的作用（暂定）： A : ↑   B； ↓
	                      C ：OK确认 D：cancel取消

	 在*密码电子锁*中行使的作用（暂定）：ABC无作用   D相当于是一个delet键：*/




#define GPIO_Key P7	//定义按键输入端口  

sbit lock = P2^7;  //定义电子锁的管脚号 （低电平上锁，高电平解锁）
void KeyDown();  //按键返回一个值
void KeyScan();  //显示在lcd屏幕上


#endif