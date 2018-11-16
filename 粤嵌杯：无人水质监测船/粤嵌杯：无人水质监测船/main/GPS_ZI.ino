
void gpsRead() 
{
  while (c.available())
  {
    gpsRxBuffer[ii++] = c.read();            //循环读并保存到数组
    if (ii == gpsRxBufferLength)clrGpsRxBuffer();    //到达600时清零
  }

  char* GPS_BufferHead;
  char* GPS_BufferTail;
                        //gpsRxBuffer是数组，在数组里查找 "$GPRMC," 并赋值给 GPS_BufferHead
  if ((GPS_BufferHead = strstr(gpsRxBuffer, "$GPRMC,")) != NULL || (GPS_BufferHead = strstr(gpsRxBuffer, "$GNRMC,")) != NULL ) 
  {
    //                     在地址 GPS_BufferHead 中 做制表工作
    if (((GPS_BufferTail = strstr(GPS_BufferHead, "\r\n")) != NULL) && (GPS_BufferTail > GPS_BufferHead))
    {
      //（储存                   ，从它开始       ，总
      memcpy(Save_Data.GPS_Buffer, GPS_BufferHead, GPS_BufferTail - GPS_BufferHead); 
      Save_Data.isGetData = true;
      clrGpsRxBuffer();
    }
  }
}

void clrGpsRxBuffer(void)
{
  memset(gpsRxBuffer, 0, gpsRxBufferLength);      //清空
  ii = 0;
}

void parseGpsBuffer()      //分析GPS信息
{
  char *subString;
  char *subStringNext;
  if (Save_Data.isGetData)
  {
    Save_Data.isGetData = false;
    //DebugSerial.println("--------------------------------------");
   // DebugSerial.println(Save_Data.GPS_Buffer);


    for (int i = 0 ; i <= 6 ; i++)
    {
      if (i == 0)
      {
        if ((subString = strstr(Save_Data.GPS_Buffer, ",")) == NULL)
          errorLog(1);  //解析错误
      }
      else
      {
        subString++;
        if ((subStringNext = strstr(subString, ",")) != NULL)
        {
          char usefullBuffer[2];
          switch (i)
          {
            case 1: memcpy(Save_Data.UTCTime, subString, subStringNext - subString); break; //获取UTC时间
            case 2: memcpy(usefullBuffer, subString, subStringNext - subString); break; //获取UTC时间
            case 3: memcpy(Save_Data.latitude, subString, subStringNext - subString); break;  //获取纬度信息
            case 4: memcpy(Save_Data.N_S, subString, subStringNext - subString); break; //获取N/S
            case 5: memcpy(Save_Data.longitude, subString, subStringNext - subString); break; //获取纬度信息
            case 6: memcpy(Save_Data.E_W, subString, subStringNext - subString); break; //获取E/W
            default: break;
          }
          subString = subStringNext;
          Save_Data.isParseData = true;
          if (usefullBuffer[0] == 'A')
            Save_Data.isUsefull = true;
          else if (usefullBuffer[0] == 'V')
            Save_Data.isUsefull = false;

        }
        else
        {
          errorLog(2);  //解析错误
        }
      }
    }
  }
}

void errorLog(int num)                //进入错误信息
{
  DebugSerial.print("ERROR");
  DebugSerial.println(num);
}

void printGpsBuffer()                 //输出解析GPS数据
{
  if (Save_Data.isParseData)
  {
    Save_Data.isParseData = false;

    //DebugSerial.print("Save_Data.UTCTime = ");
    //DebugSerial.println(Save_Data.UTCTime);
    

    if (Save_Data.isUsefull)
    {
      Save_Data.isUsefull = false;
//      DebugSerial.print("Save_Data.latitude = ");
//      DebugSerial.println(Save_Data.latitude);
//      DebugSerial.print("Save_Data.N_S = ");        
//      DebugSerial.println(Save_Data.N_S);                //输出N_S的数据
//      DebugSerial.print("Save_Data.longitude = ");
//      DebugSerial.println(Save_Data.longitude);
//      DebugSerial.print("Save_Data.E_W = ");
//      DebugSerial.println(Save_Data.E_W);
    }
    else
    {
      DebugSerial.println("GPS DATA is not usefull!");
    }

  }
}
