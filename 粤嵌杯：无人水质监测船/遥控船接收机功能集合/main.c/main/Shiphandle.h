#ifndef SHIPHANDLE_H__
#define SHIPHANDLE_H__

#define HandlePin 7         //手柄高低电平输出引脚为7号引脚
#define HandleServo A0      //手柄连接舵机模块获取命令引脚为A0
#define HandleMotor A1      //手柄连接马达模块获取命令引脚为A1
//在这里VRx(x)连的是模拟端口A0，VRy(y)连的是模拟端口A1，SW(z)连接到了数字端口

int Handle() 
{ 
       return map(analogRead(HandleServo), 0, 1000, 1, 5);
}

#endif
