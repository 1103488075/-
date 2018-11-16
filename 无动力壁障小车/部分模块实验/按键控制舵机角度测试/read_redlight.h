void delay(uint NUM)//延迟函数
{
    uint i , j ;
    for(i=0 ; i<NUM ; i++)
        for(j=0 ; j<120 ; j++);
}
void keys()//红外扫描
{
	if(R_redlight == 0 && L_redlight == 1)//应注释，右红外探头检测
    {
        	delay(20);//延时消抖
        if(R_redlight == 0 && L_redlight == 1)        
           	{
            JD = 40;//左拐
		//	add = 0;//应左拐
             }
    }
    //---------------------------   
    if(L_redlight == 0 && R_redlight == 1)//左红外探头检测到障碍物，往右拐
    {
        	delay(20);
        if(L_redlight == 0 && R_redlight == 1)     
        {
                JD = 90; //右拐90
			//	add = 2;  //应右拐
              //  delay(1000);
         }  
    }		  

    if(L_redlight == 0 && R_redlight == 0)//应注释，两边都检测到物体
    {
        delay(20);
        if(L_redlight == 0 && R_redlight == 0)
           { 
		  // 	if(add == 1)//中间
			//	JD = 63;
			//if(add == 0)
			//	JD = 75;//应左拐
           // if(add == 2)
              //  JD = 40;//应右拐

			}

    }
    if(L_redlight == 1 && R_redlight == 1)//两边都无障碍
	{
        Distance();
    }
}
