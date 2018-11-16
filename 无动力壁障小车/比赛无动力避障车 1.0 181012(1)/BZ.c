#include <STC12C5A60S2.H>

#define uint unsigned int
#define uchar unsigned char

// bit bizhan_mode ;//避障模式
// bit guizhong_mode ;//归中模式

sbit PWMOUT = P1^1 ;//PWM输出引脚

sbit L_redlight = P1^2;//红外传感器
sbit R_redlight = P1^3;

sbit SMG_1 = P2^3;//数码管使能脚
sbit SMG_2 = P2^2;

int T0NUM ;//定时器中断次数累加值
int JD ;//角度

void delay(int NUM);

#include "DUOJI.H"
#include "ADC.H"
#include "REDLIGHT.H"
//###################################
void delay(int NUM)//延迟函数
{
    int i , j ;
    for(i=0 ; i<NUM ; i++)
        for(j=0 ; j<120 ; j++);
}
//####################################
void init()//全局初始化
{
    key1 = 1;//按键电位置高
    key2 = 1;

    // guizhong_mode = 1 ;
    // guizhong_mode = 1 ;
	
    JD = 90 ;//默认角度归中

    SMG_1 = 1 ;//关闭两个数码管使能
    SMG_2 = 1 ;

    L_redlight = 1 ;//没有上拉电阻后需要手动置高电平
    R_redlight = 1 ;

    P1ASF = 0x01 ;// ADC需要将P10设置为模拟输入模式

    MN_DSQ_init();//舵机用定时器初始化
}
//####################################
void main()
{
    init();//全局初始化
    while(1)
    {
        REDLIGHT();//红外_转向
        // JD = (LVBUO()/1024.0) * 180 ;
        // SMG_SHOW(LVBUO());//数码管显示ADC转换结果
		//DJ_test();//舵机测试
    }
}
/*
版本 1.0

使用定时器T0产生周期20ms，脉宽0.5ms-2.5ms的方波控制舵机转向

小车在下滑和无障碍滑行的时候：
由于前方无障碍物触发左右两个红外传感器，所以进入测距归中模式，
红外测距朝右边，距离大于110cm小车偏左，车轮右偏，距离大于90cm小车偏右，
车轮左偏，保持在110和90范围内则车轮直行

如果前方有障碍物：根据左右探头调节车轮偏向
探头监测不到障碍物后说明避障成功，执行归中模式，将小车移回理想的中线上

由此循环下去

*/

