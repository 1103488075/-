#include <STC12C5A60S2.H>


sbit PWMOUT = P1^7 ;//PWM输出引脚

sbit L_redlight = P1^2;//红外传感器
sbit R_redlight = P1^3;

sbit key1 = P3^0;//独立按键
sbit key2 = P3^1;

sbit zd = P1^5 ; //中断触发测试引脚
int T0NUM = 0 ;//定时器中断次数累加值
int JD = 0 ;//角度

#include "DSQ.H"
//###################################
void delay(int NUM)//延迟函数
{
    int i , j ;
    for(i=0 ; i<NUM ; i++)
        for(j=0 ; j<120 ; j++);
}
//####################################
void keys()//按键扫描
{
	if(key1 == 0)//如果按下
    {
        delay(20);//延时消抖
        if(key1 == 0)//如果仍然按下
        {
            JD = 60;
            T0NUM = 0;
        }
    }
    //---------------------------
    if(key2 == 0)
    {
        delay(20);
        if(key2 == 0)   
        {
            JD = 120;
            T0NUM = 0 ;
        }
    }
}
//####################################
void main()
{
    key1 = 1;//初始化
    key2 = 1;
    zd = 0 ;
    JD = 90 ;
    MN_DSQ_init();//定时器初始化
    while(1)
        keys();
}