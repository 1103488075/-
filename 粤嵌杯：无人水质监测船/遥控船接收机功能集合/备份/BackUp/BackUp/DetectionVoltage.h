


void Voltage()                                    //在串口里输出锂电池的电压
{	
        Serial.print(analogRead(A3)*5*0.00489);  //锂电池电压测量公式
        Serial.println("V");      
        delay(1000);
}
