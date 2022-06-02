#include "reg52.h"
#include "intrins.h"

typedef unsigned char u8;
typedef unsigned int u16;

sbit led = P1^0;
sbit k1 = P3^2;

void delay (u16 time)
{
	while(time --);
}

// 初始化中断
void int0Init()
{
	// INT0,设置外部中断触发方式,1就是低电平触发，0是高电平触发
	// P32对应INT0, P33对应INT1, interrupt分别写0和1
	// 这个需要参照电路图
	IT0 = 1;
	// 开启外部中断0，允许发生0中断
	EX0 = 1;
	// 打开总中断开关，允许发生中断
	EA = 1;
}


void main()
{
	led = 0;
	// 不写到循环里面，初始化完成之后，系统会自动监听中断事件的发生（前端人的表述）
	int0Init();
	while(1);
}


// 具体的中断操作写到main后面，可能是某种书写规范吧...

// 中断函数不能直接调用，而是在中断触发时自动执行
// 0是中断号
// 0---外部中断0
// 1---定时器0
// 2---外部中断1
// 3---定时器1
// 4---串行口中断
void int0() interrupt 0
{
	// 因为用到了按键，所以一样要 防抖
	delay(1000);
	if(k1 == 0) 
	{
		delay(1000);
		if(k1 == 0)
		{
			led = ~led;		
		}
		while(k1 == 0);
	}
}	

