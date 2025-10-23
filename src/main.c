#include <AT89X52.H>     
#include <Boebot.h>
#include "motor.h"
#include "uart.h"
#include "ultrasonic.h"
#include "tcs230.h"

void tracking(void);
void put_color(void);

int qtis, qtis_color, step = 0, color, turn_r_i = 0;
unsigned char flag = 0, flag_color = 1, flag_put_color = 0,
			  flag_back = 1, flag_dis = 1, 
			  flag_black = 0, flag_obj = 0, flag_obj_t = 0,
			  flag_test_color = 0, flag_turn_r = 0,
			  flag_right = 0, flag_left = 0,
			  flag_black_white_take = 1, flag_take_back = 0, flag_con = 0,
			  flag_bw_back = 0, flag_bw_color = 0, flag_track = 1, flag_interval = 0,
			  flag_interval_step = 0, flag_put = 0, flag_turn = 0, flag_dis_low = 0, flag_stage = 0;
			  
unsigned char obj_count = 0, put_obj_count = 0, take_obj_count = 0;

void main(void)
{
	unsigned char record = 0, j = 0, black_white_count = 0;
	int i, turn_r_count = 0;
	char ii = 0;
	unsigned int dis;
	uart_Init();	//初始化超声波

	//开始时向前走一段
 	delay_nms(2000);
 	Fast_forward(40);

 	/*第一阶段 把物块搬回缓冲区或搬到指定位置*/
 	while(1)
 	{
		if(flag_track == 1)
		{
			tracking();
		}

		if(flag_interval_step == 0)
		{
			if(qtis == 15 && flag_turn == 0)					  
			{
				step = 0;
				record++;
				switch(record)				
				{
					case 1:Fast_forward(12);turn_left_90();break;
					case 2:Fast_forward(12);turn_right_90();break;
					case 3:Fast_forward(12);turn_left_45();break;
					case 4:Fast_forward(15);turn_right_45();break;	
					case 5:Fast_forward(15);break;
					case 6:Fast_forward(15);break;
					case 7:Fast_forward(15);turn_right_45();break;   	   
					case 8:Fast_forward(15);turn_left_45();break;
					case 9:Fast_forward(10);turn_right_90();break;		 
					case 10:Fast_forward(12);turn_left_90();break;
				}
				
				if (record % 2 == 1 && record > 0)
				{
					flag_dis = 1;
				}
				else
				{
					flag_interval = 1;
					flag_interval_step = 1;
					flag = 0;
					flag_dis = 0;
				}
				ii=0;
			}
		}

		if (flag_dis == 1)
		{
			InitTimer(); // 给超声波计时
			dis = GetSonarDis();
		}

		if (dis < 5 && flag_dis == 1)
		{
			take_obj_count++;
			Fast_forward(12);
			stop();
			if(take_obj_count == 3)
			{
				record++;
				flag_turn = 2;
			}
			color = get_color();
			Fast_forward(50);
			flag_test_color = 1;
			flag_dis = 0;
			flag_obj = 1;
		}

		/* 放黄、红、蓝物块 */
		if (flag_test_color)
		{
			if ((color == YELLOW && record == 1) ||
				(color == WHITE && record == 3) ||
				(color == RED && record == 5) ||
				(color == BLACK && record == 7) ||
				(color == BLUE && record == 9))
			{
				flag_put_color = 1;
				flag_turn = 1;

				if(color == WHITE || color == RED || color == BLACK)
				{
					if ((qtis_color == 48 || qtis_color == 16 || qtis_color == 32) && color != 0 && flag_put_color == 1)
					{
						flag_track = 0;
						Fast_forward(6);
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						flag_put_color = 0;
						flag_test_color = 0;
						color = 0;
						record++;
						ii = 0;
					}
				}
				if(color == YELLOW)
				{
					if (qtis_color == 32 && color != 0 && flag_put_color == 1)
					{
						flag_track = 0;
						Fast_forward(20);
						for(turn_r_i = 0; turn_r_i < 3; turn_r_i++)
						{
						turn_r(1510, 1510);
						}
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						flag_put_color = 0;
						flag_test_color = 0;
						color = 0;
						record++;
					}

					/*防止冲出地图*/
					if (qtis_color == 16 && qtis == 0 && color != 0 && flag_put_color == 1)
					{
						flag_track = 0;
						for (turn_r_i = 0; turn_r_i < 3; turn_r_i++)
						{
							turn_r(1510, 1510);
						}
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						flag_put_color = 0;
						flag_test_color = 0;
						color = 0;
						record++;
					}
				}

				if(color == BLUE)
				{
					if (qtis_color == 16 && color != 0 && flag_put_color == 1)
					{
						
						flag_track = 0;
						Fast_forward(18);
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						flag_put_color = 0;
						flag_test_color = 0;
						color = 0;
						record++;
					}
					/*防止冲出地图*/
					if (qtis_color == 32 && qtis == 0 && color != 0 && flag_put_color == 1)
					{

						flag_track = 0;
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						flag_put_color = 0;
						flag_test_color = 0;
						color = 0;
						record++;
					}
				}
				
				/* 4 qtis */
				// if (qtis == 0)
				// 	ii++;
				// if (ii > 2 && qtis == 0 && color != 0)
				// {
				// 	back(30);
				// 	turn_back();
				// 	obj_count++;
				// 	flag_test_color = 0;
				// 	color = 0;
				// 	ii = 0;
				// }
			}
			else
			{
				Fast_forward(20);
				turn_back();
				flag_test_color = 0;
			}
		}
		
		if (record % 2 == 1 && flag_obj == 0)
		{
			if (qtis == 0)
				ii++;
			if (ii > 2 && (qtis == 0 || qtis == 10 || qtis == 5 || qtis == 9 || qtis == 11 || qtis == 13))
			{
				flag_turn = 1;
				Fast_forward(65);
				turn_back();
				record++;
				ii = 0;
			}
		}

		/*把物体间隔放到缓冲区*/
		if(record % 2 == 0 && record > 0 && flag_obj == 1 && flag_interval == 1)
 		{
 			if(step > (180 - j * 45)) 
 			{
 				back(30);
 				turn_back();
				flag_obj = 0;
 				flag = 1;
 				step = 0;
				flag_interval = 0;
 				j++;
 			}
			flag_dis = 0;
		}
		else if(record % 2 == 0 && record > 0 && flag_turn == 1)
		{
			if(qtis == 15)
			{
				step = 0;
				flag_obj = 0;
				switch(record)				
				{
					case 2:Fast_forward(15);turn_left_90();turn_left_45();break;
					case 4:Fast_forward(15);turn_left_45();turn_left_90();break;	
					case 6:Fast_forward(15);turn_back();turn_right_45();break;
					case 8:Fast_forward(15);turn_left_45();turn_left_90();break;
					case 10:Fast_forward(15);turn_left_90();break;
				}
				record++;
				if (record % 2 == 1 && record > 0)
				{
					flag_dis = 1;
				}
				else
				{
					flag_interval_step = 1;
					flag = 0;
					flag_dis = 0;
				}
				ii = 0;
				flag_turn = 0;
			}
			// if(step > 120)
			// {
			// 	step = 0;
			// 	turn_back();
			// 	flag_interval_step = 0;
			// 	flag_obj = 0;
			// 	flag = 1;
			// 	flag_dis = 0;
			// }
		}

		if (step > 80 && flag == 1 && flag_obj == 0)
		{
			step = 0;
			flag_interval_step = 0;
		}

		if(take_obj_count == 3)
		{
			flag_stage = 3;
			if(qtis == 15 && flag_turn == 2)
			{
				step = 0;
				switch(record)				
				{
					case 2:Fast_forward(12);turn_left_90();break;
					case 4:Fast_forward(15);turn_left_90();turn_left_45();break;	
					case 6:Fast_forward(15);turn_back();break;
					case 8:Fast_forward(15);turn_right_45();turn_right_90();break;
					case 10:Fast_forward(12);turn_right_90();break;
				}
				break;
			}
		}
 	}

	/* 第二部分 前置*/
	flag_back = 0;
	if(take_obj_count == 3)
	{
		while (1)
		{
			if(flag_track == 1)
			{
				tracking();
			}

			if(take_obj_count == 3 && color != 0)
			{
				step = 0;
				take_obj_count = 0;
				flag_put_color = 1;
				switch (color)
				{
					case YELLOW:turn_left_90();break;
					case WHITE:turn_left_45();break;
					case RED:Fast_forward(10);break;
					case BLACK:turn_right_45();break;
					case BLUE:turn_right_90();break;
				}
			}

			if (step >= 30)
			{
				if (color == WHITE || color == RED || color == BLACK)
				{
					if ((qtis_color == 48 || qtis_color == 16 || qtis_color == 32) && color != 0 && flag_put_color == 1)
					{
						flag_track = 0;
						Fast_forward(6);
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						step = 0;
						flag_obj = 0;
						flag_back = 1;
						flag_put_color = 0;
					}
				}

				if (color == YELLOW)
				{
					if (qtis_color == 32 && color != 0 && flag_put_color == 1)
					{
						flag_track = 0;
						Fast_forward(20);
						for (turn_r_i = 0; turn_r_i < 3; turn_r_i++)
						{
							turn_r(1510, 1510);
						}
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						step = 0;
						flag_obj = 0;
						flag_back = 1;
						flag_put_color = 0;
					}

					/*防止冲出地图*/
					if (qtis_color == 16 && qtis == 0 && color != 0 && flag_put_color == 1)
					{
						flag_track = 0;
						for (turn_r_i = 0; turn_r_i < 3; turn_r_i++)
						{
							turn_r(1510, 1510);
						}
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						step = 0;
						flag_obj = 0;
						flag_back = 1;
						flag_put_color = 0;
					}
				}

				if (color == BLUE)
				{
					if (qtis_color == 16 && color != 0 && flag_put_color == 1)
					{

						flag_track = 0;
						Fast_forward(18);
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						step = 0;
						flag_obj = 0;
						flag_back = 1;
						flag_put_color = 0;
					}
					/*防止冲出地图*/
					if (qtis_color == 32 && qtis == 0 && color != 0 && flag_put_color == 1)
					{

						flag_track = 0;
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						step = 0;
						flag_obj = 0;
						flag_back = 1;
						flag_put_color = 0;
						flag_test_color = 0;
					}
				}
			}

			if (qtis == 15 && flag_back == 1)
			{
				step = 0;
				switch (color)
				{
					case YELLOW:Fast_forward(12);turn_right_90();break;
					case WHITE:Fast_forward(20);turn_right_45();break;
					case RED:Fast_forward(15);break;
					case BLACK:Fast_forward(18);turn_left_45();break;
					case BLUE:Fast_forward(12);turn_left_90();break;
				}
				color = 0;
				break;
			}
		}
	}
	

	/* 第二部分 判断颜色 搬到指定地点*/
	flag_dis = 1;	// 测距离标志位
	flag_black = 0; // 黑色物块标志位
	flag_color = 1; // 颜色检查标志位
	flag_put_color = 0;		//放置物块标志位
	flag_track = 1;		//循迹标志位
	flag_interval_step = 1;
	ii = 0;
	if(obj_count != 3)
	{
		while(1)
		{
			// 循迹
			if(flag_track == 1)
			{
				tracking();
			}

			if (flag_dis == 1)
			{
				InitTimer(); // 给超声波计时
				dis = GetSonarDis();
			}

			// dis <= 5时判断颜色，获取颜色
			if(dis < 5 && flag_dis == 1)
			{
				Fast_forward(12);
				stop();
				color = get_color();
				turn_back();
				Fast_forward(20);
				flag_color = 0;
				flag_back = 0;
				flag_dis = 0;
				flag_interval_step = 1;
			}

			if (step > 80 && flag_interval_step == 1)
			{
				step = 0;
				flag_interval_step = 0;
			}

			if(flag_interval_step == 0)
			{
				if (qtis == 15 && flag_back == 0)
				{
					step = 0;
					ii = 0;
					switch (color)
					{
						case YELLOW:Fast_forward(12);turn_left_90();break;
						case WHITE:Fast_forward(15);turn_left_45();break;
						case RED:Fast_forward(15);break;
						case BLACK:Fast_forward(15);turn_right_45();break;
						case BLUE:Fast_forward(15);turn_right_90();break;
					}
					flag_put_color = 1;
				}
			}
			
			//放到对应位置，flag_back置1
			// if(flag_black == 1)
			// {
			// 	if (step >= 55)
			// 	{
			// 		back(30);
			// 		turn_back();
			// 		step = 0;
			// 		flag_back = 1;
			// 		flag_black = 0;
			// 	}
			// }
			

			if(step > 30)
			{
				if (color == WHITE || color == RED || color == BLACK)
				{
					if ((qtis_color == 48 || qtis_color == 16 || qtis_color == 32) && color != 0 && flag_put_color == 1)
					{
						flag_track = 0;
						Fast_forward(5);
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						step = 0;
						flag_back = 1;
						flag_put_color = 0;
					}
				}

				if (color == YELLOW)
				{
					if (qtis_color == 32 && color != 0 && flag_put_color == 1)
					{
						flag_track = 0;
						Fast_forward(20);
						for (turn_r_i = 0; turn_r_i < 3; turn_r_i++)
						{
							turn_r(1510, 1510);
						}
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						step = 0;
						flag_back = 1;
						flag_put_color = 0;
					}

					/*防止冲出地图*/
					if (qtis_color == 16 && qtis == 0 && color != 0 && flag_put_color == 1)
					{
						flag_track = 0;
						for (turn_r_i = 0; turn_r_i < 3; turn_r_i++)
						{
							turn_r(1510, 1510);
						}
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						step = 0;
						flag_back = 1;
						flag_put_color = 0;
					}
				}

				if (color == BLUE)
				{
					if (qtis_color == 16 && color != 0 && flag_put_color == 1)
					{

						flag_track = 0;
						Fast_forward(18);
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						step = 0;
						flag_back = 1;
						flag_put_color = 0;
					}
					/*防止冲出地图*/
					if (qtis_color == 32 && qtis == 0 && color != 0 && flag_put_color == 1)
					{

						flag_track = 0;
						stop();
						back(30);
						turn_back();
						flag_track = 1;
						obj_count++;
						step = 0;
						flag_back = 1;
						flag_put_color = 0;
						flag_test_color = 0;
					}
				}
			}
			
			if(flag_interval_step == 0)
			{
				if (qtis == 15 && flag_back == 1)
				{
					flag_dis = 1;
					flag_color = 1;
					step = 0;
					switch (color)
					{
						case YELLOW:Fast_forward(12);turn_right_90();break;
						case WHITE:Fast_forward(20);turn_right_45();break;
						case RED:Fast_forward(15);break;
						case BLACK:Fast_forward(18);turn_left_45();break;
						case BLUE:Fast_forward(12);turn_left_90();break;
					}
					color = 0;
				}
			}
		}
	}
	

	/*第三阶段 搬运黑白物块*/
	// flag_dis = 0;	// 测距离标志位
	// flag_black = 0; // 黑色物块标志位
	// flag_color = 0; // 颜色检查标志位
	// flag_obj = 0;	// 是否有物块
	// flag_black_white_take = 1;	//标志取到黑白物块
	// flag_back = 0;		//返回标志位
	// flag_track = 1;
	// obj_count = 0;
	// color = 0;
	// dis = 100;
	// ii = 0;
	// step = 0;
	// if(flag_stage = 3)
	// {
	// 	turn_back();
	// }
	// while(1)
	// {
	// 	// 循迹
	// 	if(flag_track == 1)
	// 	{
	// 		tracking();
	// 	}

	// 	if(qtis == 15 && flag_black_white_take == 1)
	// 	{
	// 		Fast_forward(12);
	// 		turn_right_90();
	// 		flag_turn_r = 1;
	// 	}
		
	// 	if(flag_turn_r == 1)
	// 	{
	// 		turn_r_count = 0;
	// 		for(i=0; i < 200; i++)		     //利用超声波搜索第五个物块500
	// 		{			
	// 			InitTimer();  //定时器初始化
	// 			dis = GetSonarDis(); //启动超声波
	// 			//printf("m = : %d\n",m);
	// 			//delay_nms(100);
	// 			turn_r(1530,1530); //微转动
				
	// 			if(dis >= 10 && dis < 20)
	// 			{
	// 				turn_r_count = i;
	// 				if(black_white_count > 5)  //有几次次检测到物块，则前进80步，取下物块。
	// 				{
	// 					stop();
	// 					Fast_forward(98);
	// 					flag_black_white_take = 0;
	// 					flag_bw_back = 1;
	// 					break;
	// 				}
	// 				black_white_count++;
	// 			}
	// 		}
	// 		flag_turn_r = 0;
	// 	}
	// 	if (turn_r_count > 40)
	// 	{
	// 		flag_left = 1;
	// 		flag_right = 0;
	// 	}
	// 	else
	// 	{
	// 		flag_right = 1;
	// 		flag_left = 0;
	// 	}

	// 	if(qtis == 15 && flag_bw_back == 1)
	// 	{
	// 		step = 0;
	// 		flag_bw_color = 1;
	// 		if (flag_right == 1)
	// 		{
	// 			Fast_forward(12);
	// 			turn_right_90();
	// 		}
	// 		else if (flag_left == 1)
	// 		{
	// 			Fast_forward(12);
	// 			turn_left_90();
	// 		}
	// 		flag_bw_back = 0;
	// 	}

	// 	if (qtis == 15 && flag_bw_color == 1 && step > 10)
	// 	{
	// 		step = 0;
	// 		if (flag_right == 1)
	// 		{
	// 			Fast_forward(20);
	// 			turn_right_120();
	// 			Fast_forward(40);
	// 			stop();
	// 			back(30);
	// 			flag_con = 1;
	// 			flag_dis = 1;
	// 			flag_color = 1;
	// 		}
	// 		else if (flag_left == 1)
	// 		{
	// 			Fast_forward(20);
	// 			turn_left_120();
	// 			Fast_forward(40);
	// 			stop();
	// 			back(30);
	// 			flag_con = 1;
	// 			flag_dis = 1;
	// 			flag_color = 1;
	// 		}
	// 		flag_bw_color = 0;
	// 	}
	// 	if (flag_dis == 1 && flag_bw_color == 0)
	// 	{
	// 		InitTimer(); // 给超声波计时
	// 		dis = GetSonarDis();
	// 		if (dis > 5 && dis < 20)
	// 		{
	// 			flag_obj = 1;
	// 		}
	// 	}

	// 	//判断颜色，获取颜色
	// 	if(dis < 5  && flag_color == 1 && flag_dis == 1 && flag_con == 1)
	// 	{
	// 		Fast_forward(10);
	// 		stop();
	// 		color = get_color();
	// 		if(color == BLACK)
	// 		{
	// 			flag_black = 1;
	// 		}
	// 		flag_con = 0;
	// 		flag_obj = 1;
	// 		flag_color = 0;
	// 		flag_back = 0;
	// 		flag_dis = 0;
	// 	}

	// 	if (qtis == 15 && flag_back == 0 && flag_black_white_take == 0 && color != 0)
	// 	{
	// 		step = 0;
	// 		ii = 0;
	// 		switch (color)
	// 		{
	// 			case YELLOW:Fast_forward(12);turn_left_90();break;
	// 			case WHITE:Fast_forward(15);turn_left_45();break;
	// 			case RED:Fast_forward(15);break;
	// 			case BLACK:Fast_forward(15);turn_right_45();break;
	// 			case BLUE:Fast_forward(15);turn_right_90();break;
	// 		}
	// 		flag_put_color = 1;
	// 	}

		
	// 	if (color == WHITE || color == RED || color == BLACK)
	// 	{
	// 		if ((qtis_color == 48 || qtis_color == 16 || qtis_color == 32) && color != 0 && flag_put_color == 1)
	// 		{
	// 			flag_track = 0;
	// 			Fast_forward(5);
	// 			stop();
	// 			back(30);
	// 			turn_back();
	// 			flag_track = 1;
	// 			obj_count++;
	// 			step = 0;
	// 			flag_put_color = 0;
	// 			flag_obj = 0;
	// 			flag_back = 1;
	// 			ii = 0;
	// 		}
	// 	}
	// 	if (color == YELLOW)
	// 	{
	// 		if (qtis_color == 32 && color != 0 && flag_put_color == 1)
	// 		{
	// 			flag_track = 0;
	// 			Fast_forward(18);
	// 			for (turn_r_i = 0; turn_r_i < 3; turn_r_i++)
	// 			{
	// 				turn_r(1510, 1510);
	// 			}
	// 			stop();
	// 			back(30);
	// 			turn_back();
	// 			flag_track = 1;
	// 			obj_count++;
	// 			step = 0;
	// 			flag_put_color = 0;
	// 			flag_obj = 0;
	// 			flag_back = 1;
	// 			ii = 0;
	// 		}

	// 		/*防止冲出地图*/
	// 		if (qtis_color == 16 && qtis == 0 && color != 0 && flag_put_color == 1)
	// 		{
	// 			flag_track = 0;
	// 			for (turn_r_i = 0; turn_r_i < 3; turn_r_i++)
	// 			{
	// 				turn_r(1510, 1510);
	// 			}
	// 			stop();
	// 			back(30);
	// 			turn_back();
	// 			flag_track = 1;
	// 			obj_count++;
	// 			step = 0;
	// 			flag_put_color = 0;
	// 			flag_obj = 0;
	// 			flag_back = 1;
	// 			ii = 0;
	// 		}
	// 	}

	// 	if (color == BLUE)
	// 	{
	// 		if (qtis_color == 16 && color != 0 && flag_put_color == 1)
	// 		{

	// 			flag_track = 0;
	// 			Fast_forward(18);
	// 			stop();
	// 			back(30);
	// 			turn_back();
	// 			flag_track = 1;
	// 			obj_count++;
	// 			step = 0;
	// 			flag_put_color = 0;
	// 			flag_obj = 0;
	// 			flag_back = 1;
	// 			ii = 0;
	// 		}
	// 		/*防止冲出地图*/
	// 		if (qtis_color == 32 && qtis == 0 && color != 0 && flag_put_color == 1)
	// 		{

	// 			flag_track = 0;
	// 			stop();
	// 			back(30);
	// 			turn_back();
	// 			flag_track = 1;
	// 			obj_count++;
	// 			step = 0;
	// 			flag_put_color = 0;
	// 			flag_obj = 0;
	// 			flag_back = 1;
	// 			ii = 0;
	// 		}
	// 	}

	// 	/* 4qits */
	// 	// 黑色物块放到对应位置，flag_back置1
	// 	//  if(flag_black == 1)
	// 	//  {
	// 	//  	if (step >= 45)
	// 	//  	{
	// 	//  		stop();
	// 	//  		back(30);
	// 	//  		turn_back();
	// 	//  		flag_black = 0;
	// 	// 		obj_count++;
	// 	// 		step = 0;
	// 	// 		flag_put_color = 0;
	// 	// 		flag_obj = 0;
	// 	// 		flag_back = 1;
	// 	// 		ii = 0;
	// 	// 	}
	// 	//  }

	// 	// if(step >= 30)
	// 	// {
	// 	// 	if (qtis == 0)
	// 	// 		ii++;
	// 	// 	if (ii > 2 && qtis == 0 && flag_black == 0)
	// 	// 	{
	// 	// 		stop();
	// 	// 		back(30);
	// 	// 		turn_back();
	// 	// 		obj_count++;
	// 	// 		step = 0;
	// 	// 		flag_obj = 0;
	// 	// 		flag_back = 1;
	// 	// 		ii = 0;
	// 	// 	}
	// 	// }

	// 	//  if ((qtis_color == 16 || qtis_color == 32 || qtis_color == 48) && flag_put_color == 1)
	// 	//  {
	// 	//  	stop();
	// 	//  	Fast_forward(15);
	// 	//  	back(30);
	// 	//  	turn_back();
	// 	//  	obj_count++;
	// 	//  	step = 0;
	// 	//  	flag_put_color = 0;
	// 	//  	flag_obj = 0;
	// 	//  	flag_back = 1;
	// 	//  	ii = 0;
	// 	//  }

	// 	if (qtis == 15 && flag_back == 1 && color != 0)
	// 	{
	// 		flag_color = 1;
	// 		flag_back = 0;
	// 		step = 0;
	// 		switch (color)
	// 		{
	// 			case YELLOW:Fast_forward(12);turn_right_90();break;
	// 			case WHITE:Fast_forward(20);turn_right_45();break;
	// 			case RED:Fast_forward(15);break;
	// 			case BLACK:Fast_forward(18);turn_left_45();break;
	// 			case BLUE:Fast_forward(12);turn_left_90();break;
	// 			default:break;
	// 		}
	// 		color = 0;
	// 		Fast_forward(40);
	// 		if(obj_count != 2)
	// 		{
	// 			turn_back();
	// 		}
	// 		flag_black_white_take = 1;
	// 	}

	// 	if(obj_count == 2 && step > 180)
	// 	{
	// 		step = 0;
	// 		stop();
	// 		break;
			
	// 	}
	// }
	// while(1)
	// {
	// 	stop();
	// }
}

void tracking(void)
{
	P0 = 0xff;		//检测黑线															 
	qtis = P0 & 0x0f;	//读取4个巡线传感器的值
	qtis_color = P0 & 0x30;		//两个qti放物块
	Fast_forward(1);//前进一小步
	switch(qtis)	//按照4个巡线传感器的值执行移动指令，巡线
	{
		case 1:step++;turn(1550,1550);break;	  //大幅向右转
		case 2:step++;break; 	 
		case 3:step++;turn(1550,1500);break;	  //小幅向右转
		case 8:step++;turn(1450,1450);break;	  //大幅向左转
		case 4:step++;break;
		case 12:step++;turn(1500,1450);break;	  //小幅向左转
		case 5:step++;break;
		case 6:step++;break;
		case 7:step++;break;
		case 10:step++;break;
		case 13:step++;break;
		case 14:step++;break;
		case 15:Fast_forward(6);break; 	  //向前2小步			
	}
}

