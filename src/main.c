#include <AT89X52.H>     
#include <Boebot.h>
#include "motor.h"
#include "uart.h"
#include "ultrasonic.h"
#include "tcs230.h"

int qtis;
char flag = 0, flag_t = 1, flag_color = 1, flag_back = 1;


void main(void)
{
	unsigned char record=0, j=0,ji_shu=0,angle=0;
	int color;
	char ii = 0;
	unsigned int dis;

	unsigned char white_count = 0;

	//开始时向前走一段
	// delay_nms(2000);
	// Fast_forward(40);

	/*第一阶段 把物块搬回缓冲区*/
// 	while(1)
// 	{
// 		P0=0x0f;		//检测黑线															 
// 		qtis=P0&0x0f;	//读取4个巡线传感器的值
// 		Fast_forward(1);//前进一小步
// 		switch(qtis)	//按照4个巡线传感器的值执行移动指令，巡线
// 		{
// 			case 1:turn(1550,1550);break;	  //大幅向右转
// 			case 2: 	 
// 			case 3:turn(1550,1500);break;	  //小幅向右转
// 			case 8:turn(1450,1450);break;	  //大幅向左转
// 			case 4:
// 			case 12:turn(1500,1450);break;	  //小幅向左转
// 			case 5:
// 			case 6:
// 			case 7:
// 			case 10:
// 			case 13:
// 			case 14:
// 			case 15:Fast_forward(6);break; 	  //向前2小步			
// 		}

// //		/*测试搬运*/
// //		if(dis <= 3 && flag_t == 1)
// //		{
// //			turn_back();
// //			flag_t = 0;
// //		}

// //		if (flag_t == 0)
// //		{
// //		 	ii++;	 
// //		 	if(ii>30-j*6) 
// //		 	{
// //		 		back(30);//32
// //		 		turn_back();
// //		 		flag=1;
// //		 		ii=0;
// //		 		j=j+1;
// //				flag_t = 1;
// //		 	}
// //			
// //		}

// 		//测试qti	
// //		if(qtis == 0)
// //		{
// //			ii++;
// //		}
// //		if(ii > 1 && qtis==0)
// //		{
// //			turn_back();
// //			flag = 0;
// //			ii = 0;
// //		}

// 		if(qtis==15)					  
// 		{
// 			flag_t = 1;					  
// 			record++;					
// 			if(record%2==0 && record>0)
// 				flag=0;
// 			switch(record)				
// 			{
// 				case 1:Fast_forward(12);turn_left_90();break;		//第一次到中心点左转90
// 				case 2:Fast_forward(15);turn_right_90();break;
// 				case 3:Fast_forward(15);turn_left_45();break;
// 				case 4:Fast_forward(20);turn_right_45();break;	
// 				case 5:Fast_forward(15);break;
// 				case 6:Fast_forward(15);break;
// 				case 7:Fast_forward(15);turn_right_45();break;   	   
// 				case 8:Fast_forward(18);turn_left_45();break;
// 				case 9:Fast_forward(15);turn_right_90();break;		 
// 				case 10:Fast_forward(12);turn_left_90();break;
// 			}
// 			ii=0;
// 		}
		
// 		if(record%2==0 && record>0 && flag == 0)
// 		{
// 			ii++;	 
// 			if(ii > (20 - j * 2)) 
// 			{
// 				back(30);//32
// 				turn_back();
// 				flag=1;
// 				ii=0;
// 				j++;
// 			}
// 		}
		
// 		if(record%2==1)		
// 		{
// 			if(qtis==0)
// 				ii++;	 
// 			if(ii > 2 && (qtis==0 || qtis == 10 || qtis == 5 || qtis == 9) && flag_t == 1)
// 			{
// 				flag_t = 0;
// 				Fast_forward(40);
// 				turn_back();
// 				ii=0;
// 			}															   
// 		}
		
// 		if(record==10)				
// 		{
//			record = 0;
//			flag = 0;
// 			Fast_forward(40);
// 			//turn_right_90();
// 			//stop();
// 			break;	
// 		}
// 	}
	
	/* 第二部分 判断颜色 搬到指定地点*/
	while(1)
	{
		ii = 0;
		uart_Init();		// 初始化超声波
		InitTimer();		//给超声波计时
		dis = GetSonarDis();

		// 测试超声波
		//		printf("ultrasonic = %d\n", dis);
		//		delay_nms(1000);


		// 循迹
		P0 = 0x0f;		  // 检测黑线
		qtis = P0 & 0x0f; // 读取4个巡线传感器的值
		Fast_forward(1);  // 前进一小步
		switch (qtis)	  // 按照4个巡线传感器的值执行移动指令，巡线
		{
			case 1:turn(1550, 1550);break; // 大幅向右转
			case 2:
			case 3:turn(1550, 1500);break; // 小幅向右转
			case 8:turn(1450, 1450);break; // 大幅向左转
			case 4:
			case 12:turn(1500, 1450);break; // 小幅向左转
			case 5:
			case 6:
			case 7:
			case 10:
			case 13:
			case 14:
			case 15:Fast_forward(6);break; // 向前2小步
		}

		//dis <= 3时判断颜色，获取颜色
		if(dis <= 3 && flag_color == 1)
		{
			stop();
			color = get_color();
			turn_back();
			flag_color = 0;
			flag_back = 0;
		}

		if (qtis == 15 && flag_back == 0)
		{
			switch (color)
			{
				case YELLOW:Fast_forward(12);turn_left_90();break;
				case WHITE:Fast_forward(15);turn_left_45();break;
				case RED:Fast_forward(15);break;
				case BLACK:Fast_forward(15);turn_right_45();break;
				case BLUE:Fast_forward(15);turn_right_90();break;
			}
		}

		//放到对应位置，flag_back置1
		if(qtis==0){
			white_count++;
			ii++;
		}
		if(ii > 2 && (qtis==0 || qtis == 10 || qtis == 5 || qtis == 9) && white_count == 2)
		{
			back(30);
			turn_back();
			flag_back = 1;
			ii = 0;
		}

		if (qtis == 15 && flag_back == 1)
		{
			white_count = 0;
			switch (color)
			{
				case YELLOW:Fast_forward(12);turn_right_90();break;
				case WHITE:Fast_forward(20);turn_right_45();break;
				case RED:Fast_forward(15);break;
				case BLACK:Fast_forward(18);turn_left_45();break;
				case BLUE:Fast_forward(12);turn_left_90();break;
			}
		}
	}
}