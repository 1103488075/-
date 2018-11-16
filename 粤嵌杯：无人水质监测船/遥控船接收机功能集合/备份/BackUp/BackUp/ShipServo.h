#define servopin 9                          //定义数字接口9 连接伺服舵机信号线

void setServoAngle(int angle);              //声明子函数
void Servolegality();
void servopulse(int myangle);
void Servo_GO();
void ServoSerial();
void OffsetAngle();

int myangle;                                 //定义角度变量0-180
int pulsewidth;                              //定义脉宽变量
int val;                                     //0-9

int midServoVal = 60;                        //初始舵机角度
int currServoVal = 60;                       //记录当前舵机角度

int ServoMaxAngle = 150;                     //舵机偏移最大角度
int ServoMinAngle = 0;                       //舵机偏移最小角度
int vary;                                    //舵机偏移的值

//--------------------------- -----------------该函数设置与记录/输出舵机角度
void setServoAngle(int angle)
{
    for(int i=0; i<=20; i++)                 //给予舵机足够的时间让它转到指定角度
     {
        servopulse(angle);                   //引用脉冲函数
     }
      currServoVal = angle;                  //串口输入角度赋予当前角度
      Serial.print ("moving servo to");
      Serial.println (midServoVal);
} 

//---------------------------------------------该函数判断当前舵机角度是否合法
void Servolegality()
{
            if(currServoVal <= ServoMinAngle)
            currServoVal = ServoMinAngle;     //当不合法时设置为最小值   
            if(currServoVal >= ServoMaxAngle)
            currServoVal = ServoMaxAngle;     //当不合法时设置为最小值
}

//----------------------------------------------该函数将舵机角度转化为脉冲宽度
void servopulse(int myangle)                  //定义一个脉冲函数
{
    pulsewidth = (myangle*11)+500;            //将角度转化为500-2480 的脉宽值

    digitalWrite (servopin,HIGH);             //将舵机接口电平至高

    delayMicroseconds (pulsewidth);           //延时脉宽值的微秒数weimiao

    digitalWrite (servopin,LOW);              //将舵机接口电平至低

    delay (20-pulsewidth/1000);
}

//----------------------------------------- ----该函数控制舵机偏移方向和角度
void OffsetAngle()
{
            vary = 0;//偏移的值
            if(val == '1')
            vary = -20;//向左偏移20度       
            else if(val == '3')
            vary = 20;//向右偏移20度
}

//-------------------------------------- --------观察舵机当前串口情况
void ServoSerial()
{
            Serial.print ("moving servo to ");
            Serial.print (currServoVal,DEC);    //DEC:十进制形式输出 b 的 ASCII 编码值
            Serial.println ();
}
//----------------------------------------------启动飞船马达的函数


void Servo_GO()
{
      val = Serial.read();                    //读取串行端口的值 
      if(val > '0' && val <= '9')
      {
            if(val == '2')
            {
             setServoAngle(midServoVal);    
            }
            else
            {   
                  OffsetAngle();                 //该函数判断舵机向左向右偏移读书  
                  currServoVal += vary;          //计算偏移后的角度
                  
                  Servolegality ();              //该函数判断舵机角度是否合法
                  ServoSerial ();                //观察舵机当前串口情况
                  
                 for(int i = 0; i <= 20; i++)    //给予舵机足够的时间让它转到指定角度
                  {
                  servopulse(currServoVal);      //引用脉冲函数
                  }
            }
      }
}

