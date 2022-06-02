#include "reg52.h"
#include "intrins.h"

typedef unsigned long int u32;
typedef unsigned int u16;
typedef unsigned char u8;

sbit DUAN = P2^6;
sbit WEI = P2^7;
sbit key0 = P3^2; // ��ӦINT0, interrupt0���ⲿ�ж�0��
sbit key1 = P3^3; // ��ӦINT1, 	interrupt2���ⲿ�ж�1��


u8 smaDUAN[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
u8 tempP0; // ��ΪP0�ı��ݣ�����ά��P0��ֵ��
u16 i = 0; // ѭ���õ�
u32 num = 1; // ��1��ʼ�ۼӵ�9999 9999
u32 keyFlag = 1; // ���ڴ���ǰ״̬�� 1--���У� 0--ֹͣ

void delay(u16 time)
{
	while(time --);
}

// ��ʼ��INT0��INT1�ⲿ�ж�
void initINT01()
{
	// ������
	// 1. �����ж�ϵͳ�ܿ���
	EA = 1;
	// 2. �����ⲿ�ж� ���ⲿ�ж�0��1��
	EX0 = 1; EX1 = 1;
	// 3.���õ�ƽ������ʽ
	IT0 = 1;
	
	// 1��2���Լ�дΪ IE = 0x85; IE���ж�����Ĵ�������ÿһλ�൱��EX0 EX1�ȵ�
	// ��������Ϊ����Ϥ���̣��Ͳ����ü�д��
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
		
		// Ϩ�𣬷�ֹ��Ӱ	
		P0 = 0x00;
		DUAN = 1;
		DUAN = 0;
		
		tempP0 = _cror_(tempP0, 1);
	}
	
}


void main()
{	
	// ��ʼ��Ϊ 0000 0001
	initINT01();
	while(1)
	{

		display(num);
		delay(500);
		// keyFlag == 0��ʾ��ǰ��ͣ����, keyFlag == 1���ǽ��м���
		if(num < 99999999 && keyFlag == 1)
		{
			num ++;
		}
	}
}

// ����key0��ʹ�ü����ڡ����С� �͡���ͣ������״̬���л�
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

// ����key1���㸴λ
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
