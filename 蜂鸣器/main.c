#include "reg52.h"
#include "intrins.h"

sbit beep = P2^3;
void delay(time)
{
	while(time --);
}


// 蜂鸣器，设置为低电频就一直响，这里设置为间断性的
void main ()
{
	while(1)
	{
		beep = 0x00;
		delay(500000);
		beep = 0x77;
		delay(500000);
		beep = 0xff;
	}
}