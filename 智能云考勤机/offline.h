#ifndef	_W25Q128_H_
#define	_W25Q128_H_

#include "STC8.H"

#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

//------------------------命令段----------------------------
#define WriteEnable                  0x06    //写使能
#define WriteEnableVolatile          0x50    //易失性寄存器写使能
#define WriteDisable                 0x04    //写禁止
#define ReadStatusRegister1          0x05    //读状态寄存器1
#define ReadStatusRegister2          0x35    //读状态寄存器2
#define ReadStatusRegister3          0x15    //读状态寄存器3
#define WriteStatusRegister1         0x01    //写状态寄存器1
#define WriteStatusRegister2         0x31    //写状态寄存器2
#define WriteStatusRegister3         0x11    //写状态寄存器3
#define ReadData                     0x03    //读数据
#define PageProgram                  0x02    //页编程
#define SectorErase64k               0xd8    //扇区擦除
#define ChipErase                    0xc7    //芯片擦除
#define ReadUniqueIDNumber           0x4b    //读取唯一设备号
#define ReadSFDPRegister             0x5a    //读sfpd寄存器
#define EraseSecurityRegisters       0x44    //擦除安全寄存器
#define ProgramSecurityRegisters     0x42    //安全寄存器编程
#define ReadSecurityRegisters        0x48    //读取安全寄存器
#define IndividualBlockSectorLock    0x36    //单个块/扇区锁定
#define IndividualBlockSectorUnlock  0x39    //单个块/扇区解锁
#define ReadBlockSectorLock          0x3d    //读取单个块/扇区锁
#define GlobalBlockSectorLock        0x7e    //全局加锁
#define GlobalBlockSectorUnlock      0x98    //全局解锁
#define EnableReset                  0x66    //复位使能
#define ResetDevice                  0x99    //系统复位
#define FastReadData                 0x3b    //快速读取

//-----------------------------状态----------------------------------
#define BUSY              0x01   //W25Q128工作状态
#define WEL               0X02   //W25Q128写使能位

void ms1(uchar time);

void init_w25q128();  //加载W25Q128
void reset_w25q128();  //复位W25q128

uchar readrs1();
uchar readrs2();
uchar readrs3();

//读取数据
//buf：读出数据缓冲区f
//black_numb：块号
//page_numb：页号
//len:读取长度为 len+1，最多读256个字节
//成功返回 1，失败返回 0
uchar readdata(uchar * buf,uchar block_numb,uchar page_numb,uchar len);
uchar fastreaddata(uchar * buf,uchar block_numb,uchar page_numb,uchar len);

//块擦除命令
//block_numb：块号
//成功返回 1，失败返回 0
uchar eraseblock(uchar block_numb);

//页编程
//buf：要写入数据
//black_numb：块号
//page_numb：页号
//len:编程长度为 len+1，最写入256个字节
//成功返回 1，失败返回 0
uchar pageprogramblock(uchar * buf,uchar block_numb,uchar page_numb,uchar len);

void sendchr(uchar a1);

#endif