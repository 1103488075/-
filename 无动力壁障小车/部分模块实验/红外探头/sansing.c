#include "STC12C5A60S2.h"
#include"intrins.h"

sbit Buzzer = P2^4;
sbit Sensing1 = P1^3;	 //右红外探测
sbit Sensing2 = P1^2;    //左红外探测

sbit weixuan1 = P2^3;
sbit weixuan2 = P2^2;

void Delay100ms()		//@12.000MHz
{
	unsigned char i, j, k;

	i = 5;
	j = 144;
	k = 71;
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
	
    Sensing1 = 1;
	Sensing2 = 1;
 

    while(1)
    {
        if(Sensing1 == 0)
     	{
           
			
			weixuan1 = 0;
		 	 P0 = 0xc0;
			 Delay100ms();
			 weixuan1 = 1;
        }
        if(Sensing2 == 0)
        {
            weixuan2 = 0;
            P = 0xc0;
            Delay100ms();
            weixuan2 = 1;
        }
	
    }


}																				    

	  