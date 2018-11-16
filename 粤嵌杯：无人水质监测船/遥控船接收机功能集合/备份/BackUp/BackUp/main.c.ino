#include "DetectionVoltage.h"
#include "WaterQuality.h"
#include "WaterTempberce.h"
#include "ShiMotor.h"

void setup()
{
  Serial.begin(9600);
  pinMode (TdsSensorPin , INPUT);     //水质传感器引脚为A1 获取
  pinMode (DS18S20_Pin , INPUT);      //水温传感器引脚为数字引脚2  输入
  pinMode (MotorPin , OUTPUT);        //马达接口为数字引脚10 输出 

    setServoAngle (midServoVal);      //初始舵机角度
    Motor();                          //启动飞船马达
}

void loop()
{
  
  // int temp = getTemp();                  //获取水温值
  Water_GO();                               //在串口上输出水质值
  Voltage();                                //在串口上输出锂电池的电压
  analogWrite (MotorPin,100);               //控制马达脉冲功率
  
}

