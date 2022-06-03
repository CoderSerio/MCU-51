#include "reg51.h"
#include "intrins.h"

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long int u32;

void delay(u32 time)
{
	while(time --);
}

void initSerial()
{
	
	// 依然是四步走，和定时器中断类似 
	// 1. 确定TMOD中T1的工作方式(T1的工作方式2, 10: 8位自动重装计时器)
	TMOD |= 0x20;
	// 2. 计算T1的初值（晶振取12MHZ，波特率9600，通过其他软件（比如那个ISP）辅助计算得值为F3，八位重装载两个写一样）
	TH1 = 0xFE;
	TH0 = 0xFE;
	// 3. 启动T1
	TR1 = 1; 
	// 4. 确定串行口控制。PCON第一位是关联SMOD，波特率倍增位的，设置为1就是倍增，0不倍增。
	//（PCON这个其实我也没搞懂这个是什么意思，这个好像会决定第二步中TH的取值，但是看样子只需要调整第一位就行了，这里取1）
	// （SCON会决定工作方式、接收/发送控制等等，其6 7位为SM1和SM0—— 
	// 		00： 移位寄存器； 01: 10位异步收发器(8位数据，波特率可变)； 10: 11位异步收发器; 11:11位异步收发器(波特率可变)）
	PCON = 0x80;
	SCON = 0x50;
	ES = 1;	// 开启串口中断
	EA = 1;
}

void main()
{
	initSerial();
	while(1);
}


// 这里可能因为波特率的缘故导致部分数据接收发送前后不统一...
// 不过确实是能够实现接收和发送的
void serial() interrupt 4
{
	// 接收（String Buffer？）数据
	// SBUF是一个用于c存储串口通信数据的寄存器。
	u8 res = SBUF;
	// 接收完成后，硬件会将RI（接收中断控制位）置为1，表示接收完毕，需要软件置0
	RI = 0;
	
	
	// 发送数据(没什么好发的就原话发回去吧...)
	// 塞到SBUF中，进行发送
	SBUF = res;
	// 发送完成后，硬件会将TI（发送中断控制位）置为1，表示发送完毕，需要软件置0
	while(!TI);
	TI = 0;
}