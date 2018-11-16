#define MotorPin 10

void Motor()                      //设置马达引脚和开关
{
  pinMode (MotorPin , OUTPUT);    //马达引脚为10号引脚
  analogWrite (MotorPin , 240);   //设置为最高功率
  delay (4000);
  analogWrite (MotorPin , 90);    //设置为最低功率
  delay (4000);
}
void concosion()
{
    


}
