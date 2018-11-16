#include <STC12C5A60S2.H>

#define uint unsigned int 
#define uchar unsigned char 

uint JD = 90;

sbit PWM1 = P1^0 ;
sbit key1 = P3^0 ;
sbit key2 = P3^1 ;

//**************************************************
void delay(int x)
{
	int i , j ;
	for(i=x ; i>0 ; i--)
		for(j=120 ; j>0 ; j--);
}
//***********************************************
#include "PWM.h"
#include "573.h"
//**************************************************
void Init()//PWM用T1，初始化函数
{
    AUXR |= 0x80 ; //不分频，12倍速
    TMOD = 0x12 ; //定时器0模式2：八位重载

    TH0 = 256-122 ;//11us
    TL0 = 256-122 ;
    TH1 = (65536 - 11111) / 256 ;
    TL1 = (65536 - 11111) % 256 ;

    EA = 1 ; //全局中断开关
    ET0 = 1 ;
    ET1 = 1 ;
    TR0 = 1 ; //定时器中断开关
    TR1 = 1 ;
}
//*************************************************
void main()
{
    Init();
	while(1)
    {
        if(key1 == 0)
        {
            delay(10);
            if(key1 == 0)
            {
                JD ++ ;
                while(key1 == 0);
            }
        }
        //----------------------------
        if(key2 == 0)
        {
            delay(10);
            if(key2 == 0)
            {
                JD -- ;
                while(key2 == 0);
            }
        }
        //------------------------------
				if(JD > 180)
					JD = 180 ;
				if(JD < 1)
					JD = 1 ;
				//------------------------------
        fpsshow();
    }
}

