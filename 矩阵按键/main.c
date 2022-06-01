#include "reg52.h"
#include "intrins.h"

typedef unsigned char u8;
typedef unsigned int u16;

#define KEYS P3

sbit DUAN = P2^6;
sbit WEI = P2^7;

u16 index = 0;
u8 temp;
u8 code smaDUAN[] = {0x3f,0x06,0x5b,0x4f,
										 0x66,0x6d,0x7d,0x07,
										 0x7f,0x6f,0x77,0x7c,
										 0x39,0x5e,0x79,0x71}; // 共阴极数码管的字形码

void delay(u16 time) 
{ 
	while(time --);
}
// 用于控制晶体管段显示
void display(u16 num)
{
	P0 = smaDUAN[num];
	DUAN = 1;
	DUAN = 0;
}

// 用于扫描到底按了扫描按键
// 原理是将8位分为高4位和低4位，分别代表行列，也就可以表示4*4=16个键
// 默认情况下高4位是高电平，低4位是低电平，按下按键之后联通，高低两位短路都是0(至于是不是短路造成的我也不清楚，学得差，不太懂电路图)
// 这个函数就是用4*4=16个条件语句判断究竟是哪一个
// 四位中一个变0的话，那么可能的十六进制值就是：7 b d e，所以如果为了便于理解，甚至可以0x77, 0x7b, 0x7d, 0x7e, 0xb7...枚举判断16个值来探测..
void scan()
{
	P3 = 0xfe; // 1111 1110
	temp = P3; // 不要直接与运算，这样会更改P3的值
	temp = temp&0xf0; // 取高四位， 1111 0000
	if(temp != 0xf0) // 按键按下可能使得高位的1被低位的0短路成0
	{
		delay(1000);
		if(temp != 0xf0)
		{
			temp = P3; // 重新获取P3，开始探究是哪个高位变为了0
			switch(temp)
			{
				case(0xee): index = 0;break;
				case(0xde): index = 1;break;
				case(0xbe): index = 2;break;
				case(0x7e): index = 3;break;
			}
		}
		while(temp != 0xf0)
		{
			temp=P3;
      temp=temp&0xf0;
		}	
		display(index);
	}
	// 下面也是如出一辙，e d b 7，复制粘贴就来了
	P3 = 0xfd; 
	temp = P3; 
	temp = temp&0xf0; 
	if(temp != 0xf0) 
	{
		delay(1000);
		if(temp != 0xf0)
		{
			temp = P3; 
			switch(temp)
			{
				case(0xed): index = 4;break;
				case(0xdd): index = 5;break;
				case(0xbd): index = 6;break;
				case(0x7d): index = 7;break;
			}
		}
		while(temp != 0xf0)
		{
			temp=P3;
      temp=temp&0xf0;
		}	
		display(index);
	}
	// b
	P3 = 0xfb; 
	temp = P3; 
	temp = temp&0xf0; 
	if(temp != 0xf0) 
	{
		delay(1000);
		if(temp != 0xf0)
		{
			temp = P3; 
			switch(temp)
			{
				case(0xeb): index = 8;break;
				case(0xdb): index = 9;break;
				case(0xbb): index = 10;break;
				case(0x7b): index = 11;break;
			}
		}
		while(temp != 0xf0)
		{
			temp=P3;
      temp=temp&0xf0;
		}	
		display(index);
	}
	// 7
	P3 = 0xf7; 
	temp = P3; 
	temp = temp&0xf0; 
	if(temp != 0xf0) 
	{
		delay(1000);
		if(temp != 0xf0)
		{
			temp = P3; 
			switch(temp)
			{
				case(0xe7): index = 12;break;
				case(0xd7): index = 13;break;
				case(0xb7): index = 14;break;
				case(0x77): index = 15;break;
			}
		}
		while(temp != 0xf0)
		{
			temp=P3;
      temp=temp&0xf0;
		}	
		display(index);
	}
}

void main()
{
	P0 = 0xfe;
	WEI = 1;
	WEI = 0;
	delay(500000);
	while(1)
	{
		scan();
	}
}