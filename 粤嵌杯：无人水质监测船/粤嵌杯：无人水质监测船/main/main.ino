#include <SoftwareSerial.h>
SoftwareSerial FS(4,5); // 无线模块 RX, TX
SoftwareSerial c(6,7); //GPS 6 7 脚
#define DebugSerial Serial    //把GPS数据打印出来

float PPMM ,WENDU ,VV ;

#include "DetectionVoltage.h" //该头文件属于检测电压模块
#include "WaterQuality.h" //该头文件属于测量水质模块
#include "WaterTempberce.h" //该头文件属于测量水温模块
//===========================================================================
struct
{
  char GPS_Buffer[80];
  bool isGetData;    //是否获取到GPS数据
  bool isParseData; //是否解析完成
  char UTCTime[11];   //UTC时间
  char latitude[11];    //纬度
  char N_S[2];    //N/S
  char longitude[12];   //经度
  char E_W[2];    //E/W
  bool isUsefull;   //定位信息是否有效
  
}Save_Data;

const unsigned int gpsRxBufferLength = 600;
char gpsRxBuffer[gpsRxBufferLength];
unsigned int ii = 0;
//===========================================================================
void setup()
{
  FS.begin(9600);
  Serial.begin(9600);
  c.begin(19200);                 //定义GPS波特率
  DebugSerial.begin(9600);       //定义GPS波特率 - 硬串口
  pinMode (TdsSensorPin , INPUT);//水质传感器引脚为A1 获取
  pinMode (DS18S20_Pin , INPUT);//水温传感器引脚为数字引脚2  输入

  Save_Data.isGetData = false;
  Save_Data.isParseData = false;
  Save_Data.isUsefull = false;
  
  while(!Serial);
}
//===========================================================================
void loop()
{
//  Water_GO();
//  Voltage();
//  WaterTemperature();
  gpsRead();  //获取GPS数据
  parseGpsBuffer();//解析GPS数据
  printGpsBuffer();//输出解析后的数据
  DebugSerial.println(Save_Data.UTCTime);
  DebugSerial.print("Save_Data.latitude = ");
      DebugSerial.println(Save_Data.latitude);
      DebugSerial.print("Save_Data.N_S = ");        
      DebugSerial.println(Save_Data.N_S);                //输出N_S的数据
      DebugSerial.print("Save_Data.longitude = ");
      DebugSerial.println(Save_Data.longitude);
      DebugSerial.print("Save_Data.E_W = ");
      DebugSerial.println(Save_Data.E_W);
  while(FS.available()) //接收指令
  {
    char COM = FS.read();//从串口读指令
      
//    //---------------------------------------
//    if(COM =='W')//返回纬度
//      FS.print(Save_Data.longitude);
//    else if(COM == 'J')//返回经度
//      FS.print(Save_Data.latitude);
//    else if(COM == 'E')//返回WE
//      FS.print(Save_Data.E_W);
//    else if(COM == 'N')//返回NS
//      FS.print(Save_Data.N_S);
//    else if(COM == 'U')//返回UTC
//      FS.print(Save_Data.UTCTime);
    //---------------------------------------
    if(COM == 'P')//读取返回PPM
      FS.print(PPMM);
    //---------------------------------------
    else if(COM == 'T')//读取返回温度
      FS.print(WENDU);
    //---------------------------------------
    else if(COM == 'V')//读取返回电压
      FS.print(VV);
    //---------------------------------------
    else if(COM == '0')//停车
    {
      
    }
    //---------------------------------------
    else if(COM == '1')//更新速度
    {
      
    }
    //---------------------------------------
    else if(COM == '2')//更新速度
    {
      
    }
    //---------------------------------------
    else if(COM == 'B')//倒车
    {
      
    }
    //---------------------------------------
    else if(COM == '3')//更新方向
    {
      
    }
    //---------------------------------------
    else if(COM == '4')//更新方向
    {
      
    }
    //---------------------------------------
    else FS.print('O');//心跳检测
    //---------------------------------------
  }
}
