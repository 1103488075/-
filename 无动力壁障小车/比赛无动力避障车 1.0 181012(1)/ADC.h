uint SMG_code[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0x88,0x83,0xC6,0xA1,0x86,0x8E};

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
//#############################################
uint ADC_get()
{
    uint ADC_vol;//ADC结果保存变量
    //-----------------------------
    ADC_vol = ADC_RES ;
    ADC_vol <<= 2 ; //高八位数据左移 2 位，为低 2 位腾出空间
    ADC_vol |= ADC_RESL ;
    //-----------------------------
	ADC_RES = 0x00 ;//清空缓存
	ADC_RESL = 0x00 ;
    return ADC_vol;
}
//#############################################
uint LVBUO()//平均值滤波算法
{
    int i , PJ = 0;
    for(i=0;i<20;i++)
    {
        ADC_init();
        while(!(ADC_CONTR&0x10)); //检测AD是否转换完成
        PJ += ADC_get();
    }
    PJ /= 30 ;
    return PJ ;
}
//#############################################
void guizhong()//归中
{
    if (LVBUO() > 143+25)//传感器在右，距离边缘小于90CM时
        JD = 75 ;
    else if (LVBUO() < 143-25)//传感器在右，距离边缘大于110CM时
        JD = 105 ;
    else 
        JD = 90 ;//执行
}
//############################################
void SMG_SHOW(int shownum)//ADC结果显示
{
    SMG_1 = 0 ;
    SMG_2 = 1 ;
    P0 = SMG_code[shownum / 100 % 10];
    delay(5);

    SMG_1 = 0 ;
    SMG_2 = 0 ;
	P0 = 0xff ;
	
	SMG_1 = 1 ;
    SMG_2 = 0 ;
	P0 = SMG_code[shownum / 10 % 10];
    delay(5);

	SMG_1 = 0 ;
    SMG_2 = 0 ;
	P0 = 0xff ;
}