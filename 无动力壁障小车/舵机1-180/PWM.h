uint T0NUM = 0 ;
//******************************************
void PWMOUT(uint jiaodu)
{
    if (T0NUM <= jiaodu + 45)
        PWM1 = 1 ;
    else PWM1 = 0 ;
    //---------------------------
    if(T0NUM >= 1818)//结束周期
        T0NUM = 0 ;
}
//******************************************
void OUT() interrupt 1 //每11us执行一次
{
    T0NUM++;
    PWMOUT(JD);
}
