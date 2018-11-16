#ifndef SHIPHANDLE_H__
#define SHIPHANDLE_H__


#define servopin 9                           //定义数字接口9 连接伺服舵机信号线
#include "Shiphandle.h"                      //调用手柄函数里返回的参数

void setServoAngle(int angle);               //该函数设置与记录/输出舵机角度
void servopulse(int myangle);                //该函数将舵机角度转化为脉冲宽度
void Servo_GO();                             //操作舵机函数


int myangle;                                 //定义角度变量0-180
int pulsewidth;                              //定义脉宽变量
int val;                                     //用于舵机判断条件变量

int midServoVal = 60;                        //初始舵机角度
int angleList[7] =                           //储存舵机度数的数组
    {20, 20, 40, 60, 80, 100, 100};          //该数组储存舵机角度

//--------------------------- ---------------//该函数设置与记录/输出舵机角度
void setServoAngle(int angle)
{
    for(int i=0; i<=20; i++)                 //给予舵机足够的时间让它转到指定角度
     {
        servopulse(angle);                   //引用脉冲函数
     }
    Serial.print ("moving servo to");
    Serial.println (angleList[val]);
} 
//-------------------------------------------//该函数将舵机角度转化为脉冲宽度
void servopulse(int myangle)                 //定义一个脉冲函数
{
    pulsewidth = (myangle*11)+500;           //将角度转化为500-2480 的脉宽值

    digitalWrite (servopin,HIGH);            //将舵机接口电平至高

    delayMicroseconds (pulsewidth);          //延时脉宽值的微秒数weimiao

    digitalWrite (servopin,LOW);             //将舵机接口电平至低

    delay (20-pulsewidth/1000);
}
//---------------------------------------------该函数执行舵机
int temp = 0;
void Servo_GO()
{
        val = Handle();                       //从手柄函数里读取返回的值，用于操作舵机                
     //   Serial.println(val);
        if(val != temp)
        { 
            if(val >= 0 && val <= 9)          //设定舵机操作范围
            {
                if(val == 3)
                {
                setServoAngle(midServoVal);   //val等于3，重置舵机度数为60度             
                }
                else
                {   
                 setServoAngle(angleList[val]); //输出从手柄获取的度数地址
                }
            } 
        }
       temp = val;
}
#endif
