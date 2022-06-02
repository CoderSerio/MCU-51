#include "reg52.h"
#include "intrins.h"

typedef unsigned long int u32;
typedef unsigned int u16;
typedef unsigned char u8;

sbit DUAN = P2^6;
sbit WEI = P2^7;
sbit key0 = P3^2; // 对应INT0, interrupt0（外部中断0）
sbit key1 = P3^3; // 对应INT1, 	interrupt2（外部中断1）


u8 smaDUAN[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 tempP0; // 作为P0的备份，用于维护P0的值；
u16 i = 0; // 循环用的
u32 num = 1; // 从1开始累加到9999 9999
u32 keyFlag = 1; // 用于处理当前状态： 1--进行， 0--停止

void delay(u16 time)
{
	while(time --);
}

// 初始化INT0和INT1外部中断
void initINT01()
{
	// 三步走
	// 1. 开启中断系统总开关
	EA = 1;
	// 2. 开启外部中断 （外部中断0和1）
	EX0 = 1; EX1 = 1;
	// 3.设置电平触发方式
	IT0 = 1;
	
	// 1、2可以简写为 IE = 0x85; IE是中断允许寄存器，其每一位相当于EX0 EX1等等
	// 不过这里为了熟悉流程，就不采用简写了
}

void display(u32 n)
{
	for(i = 0, tempP0 = 0x7f; i < 8; i ++)
	{	
		P0 = tempP0;
		WEI = 1;
		WEI = 0;
		
		P0 = smaDUAN[n % 10];
		DUAN = 1;
		DUAN = 0;
		n /= 10;
		
		// 熄灭，防止重影	
		P0 = 0x00;
		DUAN = 1;
		DUAN = 0;
		
		tempP0 = _cror_(tempP0, 1);
	}
	
}


void main()
{	
	// 初始化为 0000 0001
	initINT01();
	while(1)
	{

		display(num);
		delay(500);
		// keyFlag == 0表示当前暂停计数, keyFlag == 1则是进行计数
		if(num < 99999999 && keyFlag == 1)
		{
			num ++;
		}
	}
}

// 按下key0，使得计数在【进行】 和【暂停】两种状态间切换
void int0() interrupt 0
{
	if(key0 == 0)
	{
		delay(1000);
		if(key0 == 0)
		{
			keyFlag = !keyFlag;
		}
		while(key0 == 0);
	}
} 

// 按下key1归零复位
void int1() interrupt 2
{
	if(key1 == 0)
	{
		delay(1000);
		if(key1 == 0)
		{
			num = 0;
			keyFlag = 0;
		}
		while(key1 == 0);
	}
} 
