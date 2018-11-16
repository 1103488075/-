#include "STC12C5A60S2.h"
//#include "inter"
#define uint unsigned int
#define uchar unsigned char

sbit weixuan1 = P2^2;
sbit weixuan2  = P2^3;
//uchar duanxuan = P0;

uint SMG_code[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
//uchar number = 123;

void Delay300ms()		//@12.000MHz
{
	unsigned char i, j, k;

	i = 14;
	j = 174;
	k = 224;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


void main()
{
	uchar s ;
    weixuan1 = 0;
	weixuan2 = 0;

	while(1)
    {
		   for(s = 0;s < 10; s++)
		   {
		   	weixuan1 = 0;
			weixuan2= 0;
       		 P0 = SMG_code[s];
        	Delay300ms();
			P0 = 0xff;
			weixuan1 = 1;
			weixuan2 =1;

		}
		
    }

}

