#define HandlePin 7 //手柄输出引脚为7号引脚
#define HandleWrite A0 //手柄获取命令引脚为A0
         
//int   value  //手柄的脉冲值与控制舵机的值
//HandleSetting
void setup()//手柄设置
{ 
 pinMode(HandlePin, INPUT_PULLUP); //注意 Z 轴输入一定要上拉，不然电平不稳。
 Serial.begin(9600);
} 
//在这里VRx(x)连的是模拟端口A0，VRy(y)连的是模拟端口A1，SW(z)连接到了数字端口7
//ShipHandle
void  loop() 
{ 
      int  value = analogRead(HandleWrite);// 手柄X轴 ， 控制舵机
       value = map(value, 0, 1023, 1, 5);
       
       //return value;
        Serial.println(value);
       
////       value = analogRead(A1);// 手柄Y轴 ， 控制马达
////       value = map(value, 0, 1023, 0, 10);
////       Serial.print(" | Y:"); 
////       Serial.print(value, DEC);
//        
//       value = digitalRead(7); 
//       Serial.print(" | Z: "); 
//       Serial.println(value, DEC); 
//       delay(1000); 
} 
