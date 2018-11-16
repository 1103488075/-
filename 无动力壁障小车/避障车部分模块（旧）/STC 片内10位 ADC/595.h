sbit SCLK = P0^2 ;
sbit RCLK = P0^1 ;
sbit DIO = P0^0 ;

int i , NUM=0;

uint duanxuan_code[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};
uint weixuan_code[]={0x01,0x02,0x04,0x08};
//*************************************************
void Timer0Init()//1毫秒@11.0592MHz
{
	AUXR |=  0x80 ;//设置定时器1T模式
	TMOD = 0X01 ;// 0000 0001
	
	TL0 = 0xCD;	//设置定时初值
	TH0 = 0xD4;	//设置定时初值
	
	EA = 1 ; //全局中断开关
	ET0 = 1 ;
	TR0 = 1 ; //定时器中断开关
}
//*************************************************
void delay(int x)//延迟函数
{
	int i , j ;
	for(i=x ; i>0 ; i--)
		for(j=120 ; j>0 ; j--);
}
//*************************************************
void while_byte(uint X)
{
	int i ;
	SCLK = 0 ;
	for(i=0;i<8;i++)
	{
		if(X & 0x80)//读取第八位的值
		{
			DIO = 1 ;//准备数据
			SCLK = 1 ;//拉高时钟，送出数据
			SCLK = 0 ;//拉高时钟，送出数据
		}
		else
		{
			DIO = 0 ;
			SCLK = 1 ;
			SCLK = 0 ;
		}
		X <<= 1 ;//数据移位
	}
}
//*************************************************
void SHOW_ONE(uint duan , uint wei)//显示一位
{
	RCLK = 0 ;
	while_byte(duanxuan_code[duan]);//发送段选数据
	while_byte(weixuan_code[wei]);//发送位选数据

	RCLK = 1 ;//更新显示
	delay(5);
	RCLK = 0 ;
}
//************************************************
void CLOSE_SHOW()//关闭显示
{
	RCLK = 0 ;
	while_byte(0xff);//发送段选数据
	while_byte(0x00);//发送位选数据

	RCLK = 1 ;//更新显示
	RCLK = 0 ;
}
//************************************************
void SHOW_ALL()
{
	SHOW_ONE(shownum / 1000,3);//显示千位
	SHOW_ONE(shownum / 100 % 10,2);//显示百位
	SHOW_ONE(shownum / 10 % 10,1);//显示十位
	SHOW_ONE(shownum % 10,0);//显示个位

	CLOSE_SHOW();//关闭显示平衡亮度
}
//*************************************************
void T0_DO() interrupt 1 //定时器0初始函数
{
	TL0 = 0xCD;		//设置定时初值
	TH0 = 0xD4;		//设置定时初值
	
	NUM ++ ;
	if (NUM >= 4)//定时器累加16ms刷新一次，刷新率 60fps
	{
		NUM = 0 ;
		SHOW_ALL();//显示
	}
}