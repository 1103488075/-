#include <DS1302.h>//1302时钟库

#define R 9//引脚定义
#define G 10
#define B 11

#define RT 5//人体红外传感器

#define maohao 12//数码管冒号低电平开启
#define DATA595 2
#define RCK595 3
#define SCK595 4

#define CE_PIN 8             //1302_RST接8引脚
#define IO_PIN 7           //1302_IO接7引脚
#define SCLK_PIN 6          //1302_CLK接6引脚

char buf[50];               //储存日期变量
char day[10];               //储存日期变量

String comdata = "";        //缓存串口数据
int numdata[7] = { 0 };     //缓存串口数据
int j = 0;                  //缓存串口数据    
int mark = 0;               //缓存串口数据

DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);   // 创建3个DS1302 对象 

unsigned char Time_hr, Time_min;//获取的小时分钟储存
//-----------------------------------------------ZZZZZZZZZZZ----------------此区间储存数码管变量

unsigned char codenum[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};//0123456789
unsigned char codeduan[4]={0x01,0x02,0x04,0x08};//左数1234位

//---------------------------------------------------------------RGB模块创建变量
boolean jia = false ;
unsigned char ZT = 0 ; //状态数值：0健康，1喝水，2运动，3时间过长，4午餐，5备忘录，6熬夜警告
unsigned char human = 0 , waithm = 0 , swk_h , swk_m ;//【工作.离开标志/不确认状态等待标志】【开始工作的时/分】
boolean jilu = true ;//记录开始工作时间的使能
unsigned char wait_water = 30 , wait_sport = 60 , wait_overtime = 90 ;//饮水提醒等待时间，运动提醒等待时间，健康极限提醒等待时间
unsigned char wait_water_next = wait_water ;//第二次喝水提示
boolean pctis_water = true , pctis_sport = true , pctis_overtime = true , pctis_eat = true , pctis_tis = true , pctis_night = true ;
unsigned char tis_h = 0 , tis_m = 0 ;//备忘录提示小时、分钟
unsigned char howlongtime ;//工作了多久

int waithmtime , timelong = 2000 ;//不确认状态等待20S
unsigned char RR = 255, GG = 255, BB = 255 ;//RGB数值
//=================================================================================
void setup() //初始化
{
	Serial.begin(9600);//一定要【9600】
	//--------------------------------------
	pinMode(R,OUTPUT);//引脚模式
	pinMode(G,OUTPUT);
	pinMode(B,OUTPUT);
	
	pinMode(maohao,OUTPUT);
	pinMode(DATA595,OUTPUT);
	pinMode(RCK595,OUTPUT);
	pinMode(SCK595,OUTPUT);
	
	pinMode(RT,INPUT);
	//--------------------------------------
	analogWrite(R,RR);//引脚初始化
	analogWrite(G,GG);
	analogWrite(B,BB);
	
	digitalWrite(SCK595,0);
	digitalWrite(RCK595,0);
	
	pwmMode(R, PWM_MODE_SOLO, PWM_FREQ_NORMAL);//PWM模式【独立，中频】
	pwmMode(G, PWM_MODE_SOLO, PWM_FREQ_NORMAL);
	pwmMode(B, PWM_MODE_SOLO, PWM_FREQ_NORMAL);
	
	pwmResolution(R, 8);//设置PMW8位输出0-255
	pwmResolution(G, 8);
	pwmResolution(B, 8);
	
	RGB_RST();//初始化RGB
}
//==============================================================================
void loop() //主函数
{
	get_time();//DS1302更新时间
	readhm();//人体红外模块更新用户状态
//----------------------------------------
	COM();//电脑端来数据
//----------------------------------------
	if(human)
		OH();//健康管家
//----------------------------------------
	RGB_SHOW();
	show(Time_hr,Time_min,2,false);//数码管【小时/分钟/刷新速度/12小时制】
}
