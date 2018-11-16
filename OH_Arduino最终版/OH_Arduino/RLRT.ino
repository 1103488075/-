void readhm()//读取用户状态
{
	if(human == 0 && waithm == 0)//确认【人类不在】
	{
		//--------------------------------------------------------
		if(digitalRead(RT)==1)
		{
			waithm = 1 ;//受到触发，打开确认延时
			waithmtime = timelong ;//每次检查延时10ms，共40S
		}
	}
	//----------------------------------------------------------------
	else if(human == 0 && waithm == 1)//人类可能来
	{
		delay(2);
		waithmtime--;
		if(waithmtime<=0)//30秒过去
		{
			if(digitalRead(RT)==1)//仍然能监测到人体
			{
				human = 1 ;//确认【人类在】
				waithm = 0 ;//【等待人类】关闭
			}
			else
				waithm = 0 ;
		}
	}
	//-----------------------------------------------------------------
	else if(human == 1 && waithm == 0)//确认人类在
	{
		if(jilu)
		{
			swk_h = Time_hr ;//记录工作开始时间
			swk_m = Time_min ;
			jilu = false ;//关闭时间记录
		}
		if(digitalRead(RT)==0)//人类可能刚离开
		{
			waithm = 1 ;//受到触发，打开确认延时
			waithmtime = timelong ;
		}
	}
	//----------------------------------------------------------------
	else if(human == 1 && waithm == 1)//人类可能离开
	{
		delay(2);
		waithmtime--;
		if(digitalRead(RT)==1)//收到触发
			waithm = 0 ;//返回确认状态(增强有人的情况下的灵敏度)
		if(waithmtime<=0)//30秒过去
		{
			if(digitalRead(RT)==0)//监测不到到人体
			{
				human = 0 ;//确认【人类不在】
				waithm = 0 ;//【等待人类】关闭
				ALL_RST();//变量复位
			}
			else
				waithm = 0 ;
		}
	}
}
//============================================================================================
void RT_tiaosi()//人体红外状态调试显示函数
{
	Serial.print("CGQ: ");
	Serial.print(digitalRead(RT));
	
	Serial.print("   human: ");
	Serial.print(human);
	
	Serial.print("   waithm: ");
	Serial.print(waithm);
	
	Serial.print("   waithmtime: ");
	Serial.println(waithmtime);
}
//==========================================================================
void ALL_RST()//变量初始化
{
	jilu = true ;//打开记录开关以保存下一次工作开始时间
	ZT = 0 ;//状态恢复健康
	howlongtime = 0 ;//工作时间为0
	wait_water_next = wait_water ; //喝水时间复位
	swk_h = 0 ;
	swk_m = 0 ;
	RR = 255 ;//RGB复位
	GG = 255 ;
	BB = 255 ;
	jia = false ;
	pctis_water = true ;
	pctis_sport = true ;
	pctis_overtime = true ;
	pctis_eat = true ;
	pctis_tis = true ;
	pctis_night = true ;
}





