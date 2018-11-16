#include <STC12C5A60S2.H>

#define uint unsigned int
#define uchar unsigned char

uint shownum = 1024;//显示数值

#include "595.h"//显示相关头文件
#include "ADC.h"//ADC相关头文件

void main()
{
    Timer0Init();//设置数码管T0中断
	P1ASF = 0x01 ;//设置P1^0为模拟引脚，高阻态模式
    while(1)
		shownum = LVBUO();//ADC数据经过滤波
}