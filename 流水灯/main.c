#include "reg52.h"
#include "intrins.h" // ����ѭ��������ͷ�ļ�
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
	// ����ѭ������λ�����������������˼����ѭ��
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