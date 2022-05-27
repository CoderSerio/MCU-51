#include<reg52.h>
typedef unsigned char u8;
typedef unsigned int u16;

sbit led = P1^0; // 点个灯看看

void delay(j) 
{
	//u16 i = 110;
	while(j --); 
}


void main () 
{
		while (1) 
		{
			led = 0;
			delay(500000);
			led = 1;
			delay(500000);
		}	
}