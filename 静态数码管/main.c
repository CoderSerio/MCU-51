#include "reg52.h"
#include "intrins.h"

typedef int u16;
typedef unsigned char u8;

u8  code smaduan[]={0x3f,0x06,0x5b,0x4f,
										0x66,0x6d,0x7d,0x07,
										0x7f,0x6f,0x77,0x7c,
										0x39,0x5e,0x79,0x71};// ������
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
		WEI = 1; // ����λ���棬������P0��ǰ��ֵ������8��������Щ��
		WEI = 0; // �ر�λ����
		
		P0=0x06; 
 		DUAN = 1; // ���������棬������P0��ǰ��ֵ�������Ƶ�8��������Щ��
		DUAN = 0;	// �رն�����
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