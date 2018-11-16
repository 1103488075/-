#define SMG P0//P0口连接573寄存器
sbit duanxuan = P2^6 ;
sbit weixuan = P2^7 ;

uint duanxuan_code[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
uint weixuan_code[]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
//*************************************************
void writeduan(uint dataa)//写段选数据
{
	SMG = dataa ;//准备数据
    duanxuan = 1 ;//发送数据
    duanxuan = 0 ;//结束发送
}
//******************************************
void writewei(uint dataa)//写位选数据
{
    SMG = dataa ;//准备数据
    weixuan = 1 ;//发送数据
    weixuan = 0 ;//结束发送
}
//******************************************
void shownext()//消影
{
    writewei(0xff);
    writeduan(0x00);
}
//******************************************
void show(uint wei , uint duan)//位、段
{
	shownext();//消影
    writewei(wei);//更新位选
    writeduan(duan);//更新段选
    delay(5);
}
//******************************************
void fpsshow()
{
		show(weixuan_code[0],duanxuan_code[JD/100]);
		shownext();//消影
		show(weixuan_code[1],duanxuan_code[JD/10%10]);
		shownext();//消影
		show(weixuan_code[2],duanxuan_code[JD%10]);
		shownext();//消影
}
//*************************************************
void T1_DO() interrupt 3 //定时器0初始函数
{
    TH1 = (65536 - 11111) / 256 ;
    TL1 = (65536 - 11111) % 256 ;
}