#include "reg52.h"
#include "intrins.h"

sbit beep = P2^3;
void delay(time)
{
	while(time --);
}


// ������������Ϊ�͵�Ƶ��һֱ�죬��������Ϊ����Ե�
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