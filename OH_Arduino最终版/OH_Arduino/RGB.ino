void RGB_RST()//初始化RGB
{
	pwmWrite(R,255);
	pwmWrite(G,255);
	pwmWrite(B,255);
	RR = 255 ;
	GG = 255 ;
	BB = 255 ;
	jia = false ;
}
void RGB_TEST()//三色显示测试
{
	RR = 0;
	digitalWrite(R,RR);
	delay(500);
	RR = 1;
	digitalWrite(R,RR);
	delay(500);
	//------------------------------------
	GG = 0;
	digitalWrite(G,GG);
	delay(500);
	GG = 1;
	digitalWrite(G,GG);
	delay(500);
	//-----------------------------------
	BB = 0;
	digitalWrite(B,BB);
	delay(500);
	BB = 1;
	digitalWrite(B,BB);
	delay(500);
}
//==============================
void RGB_GOOD()//健康，绿慢闪
{
	if(jia)
		GG++;
	else GG--;
	//------------------
	if(GG>=255)
		jia = false ;
	if(GG<=20)
		jia = true ;
	//---------------------	
	pwmWrite(G,GG);
	pwmWrite(R,255);
	pwmWrite(B,255);
}
//==============================
void RGB_WATER()//水，蓝色慢闪
{
	BB++;
	if(BB>=254)
		BB = 20 ;
	//---------------------	
	pwmWrite(G,255);
	pwmWrite(R,255);
	pwmWrite(B,BB);
}
//==============================
void RGB_SBORT()//运动，橙绿效果
{
	if(jia)
	{
		RR += 6 ;
		GG += 2 ;
	}
	else
	{
		RR -= 6 ;
		GG -= 2 ;
	}
	//-------------------
	if(GG <= 150)
		jia = true ;
	if(GG >= 250)
		jia = false ;
	//-------------------	
	pwmWrite(G,GG);
	pwmWrite(R,RR);
	pwmWrite(B,255);
}
//==============================
void RGB_EAT()//进餐时间
{
	pwmWrite(G,100);
	pwmWrite(R,80);
	pwmWrite(B,255);
}
//==============================
void RGB_TOPTIME()//工作时间过长
{
	pwmWrite(G,255);
	pwmWrite(R,20);
	pwmWrite(B,255);
}
//==============================
void RGB_night()//熬夜加班警告
{
	if(RR>=255)
		jia = false ;
	if(RR<=20)
		jia = true ;
	//------------------
	if(jia)
		RR += 4 ;
	else RR -= 4 ;
	//---------------------	
	pwmWrite(G,255);
	pwmWrite(R,RR);
	pwmWrite(B,255);
}
//==============================
void RGB_TIP()//
{
	pwmWrite(G,255);
	pwmWrite(R,20);
	pwmWrite(B,50);
}
//=============================
void LIGHT()
{
	pwmWrite(G,20);
	pwmWrite(R,30);
	pwmWrite(B,30);
}
//==============================
void RGB_SHOW()
{
	if(human)//有人在开启RGB
		switch(ZT)
		{
			case 0 : RGB_GOOD() ; break ;
			case 1 : RGB_WATER() ; break ;
			case 2 : RGB_SBORT() ; break ;
			case 3 : RGB_TOPTIME(); break ;
			case 4 : RGB_EAT(); break ;
			case 5 : RGB_TIP() ; break ;
			case 6 : RGB_night() ; break ;
		}
	else//无人为白灯
		LIGHT();
}
