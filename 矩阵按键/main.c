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
										 0x39,0x5e,0x79,0x71}; // ����������ܵ�������

void delay(u16 time) 
{ 
	while(time --);
}
// ���ڿ��ƾ���ܶ���ʾ
void display(u16 num)
{
	P0 = smaDUAN[num];
	DUAN = 1;
	DUAN = 0;
}

// ����ɨ�赽�װ���ɨ�谴��
// ԭ���ǽ�8λ��Ϊ��4λ�͵�4λ���ֱ�������У�Ҳ�Ϳ��Ա�ʾ4*4=16����
// Ĭ������¸�4λ�Ǹߵ�ƽ����4λ�ǵ͵�ƽ�����°���֮����ͨ���ߵ���λ��·����0(�����ǲ��Ƕ�·��ɵ���Ҳ�������ѧ�ò��̫����·ͼ)
// �������������4*4=16����������жϾ�������һ��
// ��λ��һ����0�Ļ�����ô���ܵ�ʮ������ֵ���ǣ�7 b d e���������Ϊ�˱�����⣬��������0x77, 0x7b, 0x7d, 0x7e, 0xb7...ö���ж�16��ֵ��̽��..
void scan()
{
	P3 = 0xfe; // 1111 1110
	temp = P3; // ��Ҫֱ�������㣬���������P3��ֵ
	temp = temp&0xf0; // ȡ����λ�� 1111 0000
	if(temp != 0xf0) // �������¿���ʹ�ø�λ��1����λ��0��·��0
	{
		delay(1000);
		if(temp != 0xf0)
		{
			temp = P3; // ���»�ȡP3����ʼ̽�����ĸ���λ��Ϊ��0
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
	// ����Ҳ�����һ�ޣ�e d b 7������ճ��������
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