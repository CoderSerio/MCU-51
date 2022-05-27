#include "reg52.h"
#include "intrins.h" // 包含循环函数的头文件
typedef unsigned char u8;
typedef unsigned int u16;

u8 led = 0xfe;

void delay(u8 metaTime) 
{
		u8 i = 110;
		while(i --) 
		{
			while(metaTime --);
		}
}

void walking()
{
	// 向左循环，和位运算的区别是字面意思——循环
	led = _crol_(led, 1);
	P1 = led;
}


void main ()
{
	while(1)
	{
		walking();
	  delay(1);
	}
}