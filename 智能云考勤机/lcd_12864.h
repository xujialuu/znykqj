#ifndef __LCD__
#define __LCD__

#define DataPort P0

extern char local_date,base_date;
extern unsigned char code *Main_Menu[];

sbit RS = P3^5;
sbit RW = P3^6;
sbit E  = P3^7;
sbit PSB   = P4^6;
sbit RES   = P4^7;

void DisplayUpdata(void);
void ClrScreen();
void LCD_PutString(unsigned char x,unsigned char y,unsigned char code *s);
void DisplayCGRAM(unsigned char x,unsigned char y);
void CGRAM();
void Init_ST7920();
void Write_Data(unsigned char Data);
void Write_Cmd(unsigned char Cmd);
void Check_Busy();

#endif
