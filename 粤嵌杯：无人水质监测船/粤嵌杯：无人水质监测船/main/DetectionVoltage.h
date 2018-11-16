#ifndef DETECTIONVOLTAGE_H__                //防止文件被重复编译
#define DETECTIONVOLTAGE_H__

void Voltage()                                    //在串口里输出锂电池的电压
{	
        VV = analogRead(A0)*5*0.00489+0.2;  //锂电池电压测量公式
}
#endif
