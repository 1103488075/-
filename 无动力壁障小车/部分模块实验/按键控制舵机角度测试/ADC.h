uint SMG_code [] = {0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};

void ADC_init()//ADC初始化
{
    uint ADC_POWER = 0x80 ;//打开 adc 电源
    uint ADC_SPEED = 0x00 ;// 90时钟转换一次
    uint ADC_FlAG = 0x00 ;//转换结束标志
    uint ADC_START = 0x08 ;//转换开始标志
    uint ADC_CHS = 0x00 ;//选择P0.0位作为ADC输入
    ADC_CONTR = ADC_POWER|ADC_SPEED|ADC_FlAG|ADC_START|ADC_CHS;
    AUXR1 = 0x00 ;//数据输出高低位格式调整 高8位RES , 低8位RESL
    ADC_CONTR|=0x00; //这句没有设置作用，只是用作延时；
}
//**********************************
uint ADC_get()
{
    uint ADC_vol;
    //-----------------------------
    ADC_vol = ADC_RES ;//获取高八位
    ADC_vol <<= 2 ; //高八位数据左移 2 位，为低 2 位腾出空间
    ADC_vol |= ADC_RESL ;//用或运算补充低2位
    //-----------------------------
	ADC_RES = 0x00 ;//清零ADC转换结果寄存器
	ADC_RESL = 0x00 ;
    return ADC_vol;//返回获取的数值
}
//**********************************************
uint LVBUO()//平均值滤波算法
{
    int i , PJ = 0;
    for(i=0;i<30;i++)//累加30次，计算平均值
    {
        ADC_init();//初始化ADC
        while(!(ADC_CONTR&0x10)); //检测AD是否转换完成
        PJ += ADC_get(); //累加 新的ADC结果
    }
    PJ /= 50 ;//求平均值7
//	PJ = (PJ/1024.0)*180;
    return PJ ;//返回滤波后的结果
}
void SMG_SHOW(int shownum)//ADC值显示
{
  // shownum = (LVBUO()/1024.0)*180;
    SMG_1 = 0 ;							   	
    SMG_2 = 1 ;
    P0 = SMG_code[shownum / 100]; //�ֽ�ʮλ
    delay(10);

    SMG_1 = 0 ;
    SMG_2 = 0 ;
	P0 = 0xff ;
	
	SMG_1 = 1 ; 
    SMG_2 = 0 ;
	P0 = SMG_code[shownum  / 10%10];   //�ֽ��λ
    delay(10);

	SMG_1 = 0 ;
    SMG_2 = 0 ;
	P0 = 0xff ;
}
