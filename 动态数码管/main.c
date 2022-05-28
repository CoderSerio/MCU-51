#include "reg52.h"
#include "intrins.h"

typedef unsigned long int u32;
typedef unsigned int u16;
typedef unsigned char u8;

sbit WEI = P2^7;
sbit DUAN = P2^6;

u8 temp = 0x7f;
u32 num = 0;
u32 tempNum = 0;
u32 i = 0;
u8 smaduan[]={0x3f,0x06,0x5b,0x4f,
							0x66,0x6d,0x7d,0x07,
							0x7f,0x6f,0x77,0x7c,
							0x39,0x5e,0x79,0x71};// 字形码

void delay(time)
{
	while(time --);
}

void main()
{
	while(1)
	{
		tempNum = num;
		for(i = 0; i < 8; i ++)
		{
			P0 = temp;
			WEI = 1;
			WEI = 0;
			
			P0 = smaduan[tempNum % 10];
			DUAN = 1;
			DUAN = 0;
			tempNum /= 10;
			
			// 熄灭，不然会有数字重影叠加
			P0 = 0x00;
			DUAN = 1;
			DUAN = 0;
			
			temp = _cror_(temp, 1);
		}
		// 到达最大值（99999999）之后停止
		if(num < 99999999) 
		{
			num ++;
		}		
		
		delay(1000);
	}
}