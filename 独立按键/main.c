// ������������λ�á���С
#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;
typedef unsigned char u8;

// ����������P3^0��P3^3���ĸ�
// ǰ�����������¡�������С
// �������������ҡ�����λ��
sbit indeKeys0 = P3^0;
sbit indeKeys1 = P3^1;
sbit indeKeys2 = P3^2;
sbit indeKeys3 = P3^3;
// �����ţ�λ����
sbit DUAN = P2^6;
sbit WEI = P2^7;

u8 tempWEI = 0xfe;
u16 tempDUAN = 0;
u8 code smaDUAN[] = {0x3f,0x06,0x5b,0x4f,
										 0x66,0x6d,0x7d,0x07,
										 0x7f,0x6f,0x77,0x7c,
										 0x39,0x5e,0x79,0x71};// ������

										 
void delay(time)
{
	while(time --);
}

void handleKey()
{
	// ����
	if(indeKeys0 == 0)
	{
		delay(1000);
		if(indeKeys0 == 0)
		{
			tempWEI = _cror_(tempWEI, 1);
			P0 = tempWEI;
			WEI = 1;
			WEI = 0;
			/*P0 = ~P0;
			DUAN = 1;
			DUAN = 0;
			P1 = ~P1;*/
		}
		while(!indeKeys0);	
	}
	// ����
	else if (indeKeys1 == 0) 
	{
		delay(1000);
		if(indeKeys1 == 0)
		{
			tempWEI = _crol_(tempWEI, 1);
			P0 = tempWEI;
			WEI = 1;
			WEI = 0;
		}
		while(!indeKeys1);	
	
	}
	// ����
	else if (indeKeys2 == 0) 
	{
		delay(1000);
		if(indeKeys2 == 0)
		{
			P0 = smaDUAN[++ tempDUAN % 10];
			DUAN = 1;
			DUAN = 0;
		}
		while(!indeKeys2);
	}
	// ��С
	else 
	{
		delay(1000);
		if(indeKeys3 == 0)
		{
			P0 = smaDUAN[-- tempDUAN % 10];
			DUAN = 1;
			DUAN = 0;
		}
		while(!indeKeys3);
	}
}

void main()
{
	P0 = tempWEI;
	WEI = 1;
	WEI = 0;
	
	P0 = smaDUAN[tempDUAN % 10];
	DUAN = 1;
	DUAN = 0;
	
	while(1)
	{
			handleKey();
	}

}