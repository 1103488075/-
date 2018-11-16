#ifndef SHIMOTOR_H__
#define SHIMOTOR_H__


#include "Shiphandle.h"    //调用手柄函数

#define MotorPin 10
int Control;                                //控制马达的函数
void UpMotor()                              //设置马达引脚和开关
{
  pinMode (MotorPin , OUTPUT);              //马达引脚为10号引脚
  analogWrite (MotorPin , 240);             //设置为最高功率
  delay (4000);
  analogWrite (MotorPin , 90);              //设置为最低功率
  delay (4000);
  Serial.println("Ship Motor coming soon");//马达即将启动
}
#endif



