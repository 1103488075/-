#include <STC12C5A60S2.H>
//#include "reg52.h"

	   void Distance();
#define uint unsigned int 
#define uchar unsigned char
//================================Servo_PWM
sbit PWMOUT = P1^1 ;    //PWM输出引脚

sbit L_redlight = P1^2; //左红外探头，低电平检测
sbit R_redlight = P1^3; //右红外探头
uint T0NUM = 0 ;        //定时器中断次数累加值
uint JD = 0 ;           //角度
uchar median = 60;      //65度偏右     //舵机
uchar angle = 5;        //舵机每次积累�
//==================================A   DC
uint shownum = 1024;    //读取ADC数�
//=================================数�
sbit SMG_1 = P2^3;
sbit SMG_2 = P2^2;
uchar add = 1;
#include "DSQ.H"         //中断函数
#include "read_redlight.h"//读取红外信号
#include "ADC.h"         //片内ADC的获取

void Distance()//距离
{
    if(LVBUO()>=105)  //90,阈值应再调小，LVBUO = 105
     	JD = 35;//30
	if(LVBUO()<105)
	 	JD = 63;
}

void main()
{
    P1ASF = 0x01 ;      //设置0x01，P1^0为模拟引脚s，高阻态模式
    JD = median;        //给初始角度赋予中间值
    MN_DSQ_init();      //定时器初始化
	delay(5000);
    while(1)
    {
    keys();
    SMG_SHOW(LVBUO());//数码管显
    }
}