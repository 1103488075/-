#include <STC12C5A60S2.H>


#define uint unsigned int
#define uchar unsigned char

uint shownum = 1024;//显示数值

uint JD = 1024;

#include "595.h"//显示相关头文件
#include "ADC.h"//ADC相关头文件

void main()
{
    Timer0Init();//设置数码管T0中断
	P1ASF = 0x01 ;//设置0x01，P1^0为模拟引脚s，高阻态模式
    while(1)
    {
    JD = (LVBUO()/1024.0) * 180;//转化为cm
	//shownum = JD;
    }
}