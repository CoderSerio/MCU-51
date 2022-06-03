#include "reg52.h"
#include "intrins.h"

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long int u32;

u8 leds = 0xfe;


// 原理
// 定时/计数器（两个功能集于一体）,分为高8位和低8位 ：高8位THx，低8位TLx（这里x为0或1）
//  TMOD是定时/计数器的工作方式寄存器；
// 	TCON是其控制寄存器
//
//  TMOD分为高4位T0和低4位T1，对于T0和T1，它们的4位都是GATE、C/T、M1、M0：
//			GATE为0代表定时器受外部中断源信号的影响，此时将TCON的TR0或者TR1设置为1，则可启动定时器
// 			GATE为1，将TR0或者TR1设置为1之外，还要将INT0或者INT1设置为1才可启动
// 			C/T 选择定时还是计数，0为定时
// 			M1、M0配置四种工作方式 ———— 00：13位定时计数；01:16位定时计数；10:8位自动重装定时计数；11：独立的8位定时计数
//	TCON分为高4位TH，低4位TL，分别控制定时/计数器启动和中断申请 和 外部中断（没错就是之前写的那个）

void initTimer0()
{
	// 四步走
	// 1. 对TMOD赋值确定T0 T1工作方式（16位定时计数）
	//  用或运算避免影响其他控制位
	TMOD |= 0x01; 
	// 2. 计算初值写入TH0 TL0或者TH1 TL1
	// 对于晶振频率12Mhz的芯片，设定1ms需要将值设置为FC18——这个值是固定的（毕竟没有测试工具只能相信这个值了）
	TH0 = 0xFC;
	TL0 = 0x18;
	// 3. 开启中断
	ET0 = 1;
	EA = 1;
	// 4. 设置TR0或TR1，启动定时或计数
	TR0 = 1;
}

void main()
{
	initTimer0();
	while(1);
}

void timer0() interrupt 1
{
	// 在函数内部声明一个不被重置的变量i（能懂那个意思，但是不会表达...）
	static u16 i = 0;
	// 因为我们设置的工作方式是16位定时计数，工作一次后并不会自动重装，需要手动重新设置
	// 重装之后又产生中断，然后又重装...这样就形成了循环计数
	TH0 = 0xFC;
	TL0 = 0x18;
	
	i++;
	// 忽略其他运算耗费的时间，1ms的定时器执行1000次的时候就是1s
	if(i == 1000) 
	{
		i = 0;
		P1 = leds;
		leds = _crol_(leds, 1);
	}
}