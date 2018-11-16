void HandleTime() //串口设置DS1302时钟模块的时间    
{                                     
  while (Serial.available() > 0) //在串口设置你想输入的时间
  {
    comdata += char(Serial.read()); //串口有数据的时将数据拼接到变量comdata
    delay(2);
    mark = 1 ;
  }
  //-----------------------------------------------------------
  if (mark == 1)
  {
    for (int i = 0; i < comdata.length(); i++)
    {
      if (comdata[i] == ',' || comdata[i] == 0x10 || comdata[i] == 0x13)// 以逗号分隔分解comdata的字符串，分解结果变成转换成数字到numdata[]数组
        j++;
      else
        numdata[j] = numdata[j] * 10 + (comdata[i] - '0');
    }
	//----------------------------------------------------------------------------------------------------------
    Time t(numdata[0], numdata[1], numdata[2], numdata[3], numdata[4], numdata[5], numdata[6]);/* 将转换好的numdata凑成时间格式，写入DS1302 */
    rtc.time(t);
    mark = 0; j = 0;/* 清空 comdata 变量，以便等待下一次输入 */
    comdata = "";/* 清空 numdata */
    for (int i = 0; i < 7; i++) numdata[i] = 0;
  }
}
//======================================================================================================
void get_time()//时钟获取时间/串口打印              
{
  Time t = rtc.time();// 从 DS1302 获取当前时间 
  Time_hr = t.hr;//对时间进行赋值
  Time_min = t.min;
  //----------------------------------------------------------
  if(human)//在用户工作的时候
	if(t.sec == 0)//每分钟更新一次【工作了多久】
	{
		int ih = Time_hr - swk_h;//计算时间差
		int im = Time_min - swk_m;
		if(im < 0)
		{
			im = 60 +im;//时间60进制转换
			ih--;
		}
		//-------------------------------------------
		howlongtime = ih * 60 + im ;//保存时间差【分钟】
	}
// snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d", day, t.yr, t.mon, t.date, t.hr, t.min, t.sec);//串口更新时间
// Serial.println(buf);
}
//============================================================================================================
void OH()//管家
{
	if(howlongtime < wait_sport)
		ZT = 0 ;
//----------------------------------------------------------------
	if(howlongtime >= wait_water_next)//工作累计时长达到喝水提醒时间
	{
		ZT = 1 ;
		if(pctis_water)
		{
			Serial.print("HS");//串口返回HS,PC提示喝水
			wait_water_next += wait_water ;//计算下次喝水时间
			pctis_water = false ;//关闭串口返回
		}
	}
//----------------------------------------------------------------
	if(howlongtime > (wait_water_next+1))//喝水提醒结束
		ZT = 0 ;
//----------------------------------------------------------------
	if(howlongtime >= wait_sport)//工作累计时长达到运动休息提醒时间
	{
		ZT = 2 ;
		if(pctis_sport)
		{
			Serial.print("XX");//串口返回XX，PC提示休息
			pctis_sport = false ;//关闭串口返回
			RR = 255 ; //变换效果特殊需要更新RGB初值
			GG = 255 ;
			BB = 255 ;
			jia = false ;
		}
	}
//----------------------------------------------------------------
	if(howlongtime >= wait_overtime)//工作累计时长达到健康极限提醒时间
	{	
		ZT = 3 ;
		if(pctis_overtime)
		{
			Serial.print("JX");//串口返回JX，PC提示休息
			pctis_overtime = false ;//关闭串口返回
		}
	}
//----------------------------------------------------------------
	if(Time_hr>=12 && Time_hr<13)//进餐时间
	{
		ZT = 4 ;
		if(pctis_eat)
		{
			Serial.print("JC");//串口返回JC，PC提示进餐
			pctis_eat = false ;//关闭串口返回
		}
	}
//----------------------------------------------------------------
	if(Time_hr>=18 && Time_hr<19)//晚餐时间
	{
		ZT = 4 ;
		if(pctis_eat)
		{
			Serial.print("JC");//串口返回JC，PC提示进餐
			pctis_eat = false ;//关闭串口返回
		}
	}
//----------------------------------------------------------------
	if(Time_hr>=21 && Time_hr<23)//熬夜提醒
	{
		ZT = 6 ;
		if(pctis_night)
		{
			Serial.print("AY");//串口返回AY，PC提示熬夜
			pctis_night = false ;//关闭串口返回
		}
	}
//----------------------------------------------------------------
	if(Time_hr == tis_h && Time_min == tis_m)//备忘录提醒
	{
		ZT = 5 ;
		if(pctis_tis)
		{
			Serial.print("BW");//串口返回BW，PC提示备忘录内容
			pctis_tis = false ;//关闭串口返回
		}
	}
}
