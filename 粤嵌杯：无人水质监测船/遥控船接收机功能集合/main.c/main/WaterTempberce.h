#ifndef WATERTEMPBERCE_H__
#define WATERTEMPBERCE_H__

#include <OneWire.h>
#define DS18S20_Pin 2                 //DS18S20的数字输出引脚2
OneWire ds(DS18S20_Pin);             //在数字引脚2上

void WaterTemperature();             //声明子函数
float getTemp();
//===================================================== 
void WaterTemperature()
{
  Serial.print("The water temperature here is");
  Serial.println(getTemp());
  delay (1000);
}

float getTemp()                       //将数字信号转换为摄氏度
{
  //

  byte data[12];
  byte addr[8];

  if ( !ds.search(addr)) 
  {
      //
      ds.reset_search();              //没有发现传感器，重置收索
      return -1000;
     // Serial.println("No access to water temperature");
  }

  if ( OneWire::crc8( addr, 7) != addr[7]) 
  {
      Serial.println("CRC is not valid!");
      return -1000;
  }

  if ( addr[0] != 0x10 && addr[0] != 0x28) 
  {
      Serial.print("Device is not recognized");
      return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44,1);                    // 开始转换，最后寄生效力
  byte present = ds.reset();
  ds.select(addr);    
  ds.write(0xBE);                      // Read Scratchpad
  
  
  for (int i = 0; i < 9; i++) 
  {                                    // 需要9个字节
    data[i] = ds.read();
  }
  
  ds.reset_search();
  
  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB); //使用二进制补码
  float TemperatureSum = tempRead / 16;
  
  return TemperatureSum;
  
}
#endif
