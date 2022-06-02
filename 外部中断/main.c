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

// ��ʼ���ж�
void int0Init()
{
	// INT0,�����ⲿ�жϴ�����ʽ,1���ǵ͵�ƽ������0�Ǹߵ�ƽ����
	// P32��ӦINT0, P33��ӦINT1, interrupt�ֱ�д0��1
	// �����Ҫ���յ�·ͼ
	IT0 = 1;
	// �����ⲿ�ж�0��������0�ж�
	EX0 = 1;
	// �����жϿ��أ��������ж�
	EA = 1;
}


void main()
{
	led = 0;
	// ��д��ѭ�����棬��ʼ�����֮��ϵͳ���Զ������ж��¼��ķ�����ǰ���˵ı�����
	int0Init();
	while(1);
}


// ������жϲ���д��main���棬������ĳ����д�淶��...

// �жϺ�������ֱ�ӵ��ã��������жϴ���ʱ�Զ�ִ��
// 0���жϺ�
// 0---�ⲿ�ж�0
// 1---��ʱ��0
// 2---�ⲿ�ж�1
// 3---��ʱ��1
// 4---���п��ж�
void int0() interrupt 0
{
	// ��Ϊ�õ��˰���������һ��Ҫ ����
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

