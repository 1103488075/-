
#define VREF 5.0                                // 模拟参考电压（伏特）的ADC
#define SCOUNT  30                              // 样点的总和
#define TdsSensorPin A1                         //A1设置为TDS的输出引脚
int analogBuffer[SCOUNT];                       // 将模拟值存储在阵列中，从ADC读取
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0,copyIndex = 0;
float averageVoltage = 0,tdsValue = 0,temperature = 25;


int getMedianNum(int bArray[], int iFilterLen)  //中值滤波算法
{
  int bTab[iFilterLen];
  for (byte i = 0; i<iFilterLen; i++)
     bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) 
  {
    for (i = 0; i < iFilterLen - j - 1; i++) 
    {
      if (bTab[i] > bTab[i + 1]) 
      {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0)
    bTemp = bTab[(iFilterLen - 1) / 2];
  else
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  return bTemp;
}

void Water_GO()                                                   // 输出TDS
{
  static unsigned long analogSampleTimepoint = millis();
   if(millis()-analogSampleTimepoint > 40U)                       //每40毫秒读取一次ADC的模拟值
   {
     analogSampleTimepoint = millis();
     analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);  //读取模拟值并存入缓冲区
     analogBufferIndex++;
     if(analogBufferIndex == SCOUNT) 
         analogBufferIndex = 0;
   }   
   static unsigned long printTimepoint = millis();
   if(millis()-printTimepoint > 800U)                              //每八百毫秒读取一次ADC的模拟值
   {
      printTimepoint = millis();
      for(copyIndex=0;copyIndex<SCOUNT;copyIndex++)
       analogBufferTemp[copyIndex]= analogBuffer[copyIndex];
      averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0; // 通过中值滤波算法读取更稳定的模拟值，并转换为电压值
      float compensationCoefficient=1.0+0.02*(temperature-25.0);                     //温度补偿公式：fFinalResult（25 ^ C）= fFinalResult（current）/（1.0 + 0.02 *（fTP-25.0））;
      float compensationVolatge=averageVoltage/compensationCoefficient;              //温度补偿
      tdsValue=(133.42*compensationVolatge*compensationVolatge*compensationVolatge - 255.86*compensationVolatge*compensationVolatge + 857.39*compensationVolatge)*0.5; //将电压值转换为TDS值
      //Serial.print("voltage:");
      //Serial.print(averageVoltage,2);
      //Serial.print("V   ");
      Serial.print("TDS Value:");
      Serial.print(tdsValue , 0);
      Serial.println("ppm");                        //单位浓度
   }
}

