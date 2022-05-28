#include "reg52.h"
#include "intrins.h"

typedef int u16;
typedef unsigned char u8;

u8  code smaduan[]={0x3f,0x06,0x5b,0x4f,
										0x66,0x6d,0x7d,0x07,
										0x7f,0x6f,0x77,0x7c,
										0x39,0x5e,0x79,0x71};// 字形码
u16 temp = 1;
sbit DUAN = P2^6;
sbit WEI = P2^7;										
										
void delay(time)
{
	while(time --);
}

void main()
{

		P0 = 0xfe;	
		WEI = 1; // 开启位锁存，将保存P0当前的值，决定8个灯中哪些亮
		WEI = 0; // 关闭位锁存
		
		P0=0x06; 
 		DUAN = 1; // 开启段锁存，将保存P0当前的值，决定灯的8个段中哪些亮
		DUAN = 0;	// 关闭段锁存
		while(1)	
		{
				delay(500000);
				// P0 = _crol_(P0, 1);
				// WEI = 1;
				// WEI = 0;
				
				P0 = smaduan[temp ++ % 16];
				DUAN = 1;
				DUAN = 0;
				
		}
	
}