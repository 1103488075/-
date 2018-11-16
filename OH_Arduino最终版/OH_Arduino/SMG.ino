void out1bit(int bitin)//输出一位
{
	digitalWrite(SCK595,0);//低电平准备
	digitalWrite(DATA595,bitin);//数据准备
	digitalWrite(SCK595,1);//发送数据1位
}
//====================================================
void out1byte(unsigned char bytein)//输出八位一字节
{
	unsigned char jisuan = 128 ;
	for(unsigned char i=0;i<8;i++)
	{
		out1bit(bytein & jisuan);//输出与计算的结果
		jisuan >>= 1 ;//计算值左移一位
	}
}
//=====================================================
void RSKOUT()//刷新显示
{
	digitalWrite(3,1);//RCK上升沿显示数据
	delay(2);
	digitalWrite(3,0);//恢复
}
//======================================================================================================================
void show(unsigned char h, unsigned char m, unsigned char spd , boolean xsz)//参数【小时/分钟/刷新速度/12.24小时制】
{	
	if(xsz)
		if(h>=12)
			h -= 12 ;//24小时换成12小时制
	//-------------------------------------------------------
	if(human)//监测到用户则开启冒号
	{
		digitalWrite(maohao,0);//冒号开
		delay(spd);
		digitalWrite(maohao,1);//冒号关
	}
	else
		digitalWrite(maohao,1);//冒号关
	//-------------------------------------------------------
	out1byte(codeduan[0]);//送出1位选
	out1byte(codenum[h/10]);//送出数值【段选】
	RSKOUT();//刷新显示
	delay(spd);
	//--------------------------------------------------------
	out1byte(codeduan[1]);//送出2位选
	out1byte(codenum[h%10]);//送出数值【段选】
	RSKOUT();//刷新显示
	delay(spd);
	//--------------------------------------------------------
	out1byte(codeduan[2]);//送出3位选
	out1byte(codenum[m/10]);//送出数值【段选】
	RSKOUT();//刷新显示
	delay(spd);
	//--------------------------------------------------------
	out1byte(codeduan[3]);//送出4位选
	out1byte(codenum[m%10]);//送出数值【段选】
	RSKOUT();//刷新显示
	//delay(spd);
}









