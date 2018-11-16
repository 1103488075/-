char READ_BYTE()//读取一个字节
{
	char abyte = "";
	while(Serial.available()!=0)//循环等待串口收到数值（1为收到数据，0为没有数据）
		abyte = Serial.read();//把串口的一个字节保存下来并清空串口接收区
	return abyte ;//返回收到的字节
}
//=================================================
String READ_DATA()//读取一串字节
{
	String data = "" ;
	while(Serial.available()==0);
	while(Serial.available()!=0)//只要串口接收区还有数据就不断接收
	{
        data += char(Serial.read());//读取一个字节保存下来
		delay(2);//延时2毫秒保存数据
	}
	return data ;//返回接收到的字符串
}
//==================================================
int BYTE_INT()//字节转int
{
	int OUT = int(READ_BYTE());//接收一个字节转换成int
	return OUT ;
}
//==================================================
int DATA_INT()//字符串转int
{
	String a = READ_DATA();//接收一个字符串
	int OUT = a.toInt();//字符串转换成int
	return OUT ;
}
//===================================================
void COM () //PC来指令
{
	char PCCOM = READ_BYTE();
	if (PCCOM == 'T')// T 指令，1302设定时间----------PC发 T
	{
		Serial.print("OK");//反馈OK申请数据传输
		while (Serial.available()==0);
		HandleTime();//1302到串口获取数据----------PC发 年,月,日,小时,分钟,秒,星期
		Serial.print("OK");//反馈OK结束
	}
	//-------------------------------------------------------------------
	else if(PCCOM == 'S')// S 指令，设定各个时间----------PC发 S
	{
		Serial.print("OK");//反馈OK申请数据传输
		//while (Serial.available()==0);
		tis_h = DATA_INT();//获取备忘录小时----------PC发 S
		
		Serial.print("OK");//反馈OK申请数据传输
		//while (Serial.available()==0);
		tis_m = DATA_INT();//获取备忘录分钟----------PC发 S
		
		Serial.print("OK");//反馈OK申请数据传输
		//while (Serial.available()==0);
		wait_water = DATA_INT(); //饮水等待时间----------PC发 S
		
		Serial.print("OK");//反馈OK申请数据传输
		//while (Serial.available()==0);
		wait_sport = DATA_INT(); //运动休息等待时间----------PC发 S
		
		Serial.print("OK");//反馈OK申请数据传输
		//while (Serial.available()==0);
		wait_overtime = DATA_INT();//健康极限等待时间----------PC发 S
		
		Serial.print("OK");//反馈OK
	}
	else if(PCCOM == 'X')//连接测试X
		Serial.print("Y");//返回Y
}