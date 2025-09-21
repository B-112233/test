#include <AT89X52.H>     //����52ͷ�ļ�
#include <Boebot.h>
#include "motor.h"
#include "uart.h"
#include "ultrasonic.h"

int qtis;
char flag = 0;

typedef enum {
	CARRY_IDLE = 0,
	CARRY_FIND_OBJECT,
	CARRY_PICKED,
	CARRY_RETURNING,
	CARRY_DROPPING,
	CARRY_DONE
} CarryState;

void main(void)
{
	unsigned char record=0 + 2,j=0,ji_shu=0,angle=0;	 //recordָСתj,ji_shuڼangleڼ¼Ƕȡ
	char ii = 0;
	unsigned int dis = 0;
	CarryState carry = CARRY_IDLE;

	uart_Init();
	InitTimer();
	delay_nms(2000);   //ʱ2
	Fast_forward(40);
	while(1)
	{
		// 简易搬运流程状态机
		if(carry != CARRY_DONE)
		{
			dis = GetSonarDis();
			// 目标阈值按HC-SR04约每cm≈58计数，阈值20cm
			if(carry == CARRY_IDLE)
			{
				if(dis > 0 && dis < 20)
				{
					stop();
					// 模拟抓取（实际应控制夹爪IO）
					delay_nms(500);
					turn_back();
					carry = CARRY_RETURNING;
					continue;
				}
			}
			else if(carry == CARRY_RETURNING)
			{
				// 返回过程中，检测到新的障碍物作为放置点
				if(dis > 0 && dis < 25)
				{
					stop();
					// 模拟放置
					delay_nms(500);
					carry = CARRY_DONE;
					stop();
					break;
				}
			}
		}

		P0=0x0f;		//								 
		qtis=P0&0x0f;	//ȡ4Ѳߴֵ
		Fast_forward(1);//ǰһС
		switch(qtis)	//4ѲߴִֵƶָѲ
		{
			case 1:turn(1550,1550);break;	  //ת
			case 2:	 
			case 3:turn(1550,1500);break;	  //Сת

			case 8:turn(1450,1450);break;	  //ת
			case 4:turn(1500, 1480); break;   //Сת
			case 12:turn(1500,1450);break;	  //Сת

			case 5:
			case 6:
			case 7:
			case 10:
			case 13:
			case 14:
			case 15:Fast_forward(6);break;	  //ǰ2С			
		}
		
		if(qtis==15)					  //4Ѳߴĺ,ĵ
		{						  
			record++;					//ָӱ
			if(record%2==0 && record>0)
				flag=0;
			switch(record)				  //ձִֵƶ
			{
				case 1:Fast_forward(12);turn_left_90();break;  //ת90
				case 2:Fast_forward(15);turn_right_90();break; //ת90
				case 3:Fast_forward(15);turn_left_45();break;  //ǰ20ת45
				case 4:Fast_forward(20);turn_right_45();break;	//ǰ30ת45ȣǰ15
				case 5:Fast_forward(15);break;
				case 6:Fast_forward(15);break;
				case 7:Fast_forward(15);turn_right_45();break;	   	   //ǰ20ת45ȡ
				case 8:Fast_forward(18);turn_left_45();break; //ǰ20ת45ȣǰ13
				case 9:Fast_forward(15);turn_right_90();break;		 //ת90
				case 10:Fast_forward(15);turn_left_90();break;		 //ת90
			}
			ii=0;				//ii
		}
		
		if(record%2==0 && record>0 && flag==0)//ָӱֵΪżҷʱִ䡣
		{
			ii++;	 
			if(ii>30-j*5)				//62С鰲ŵλһļ? 
			{
				back(30);//32
				turn_back();
				flag=1;
				ii=0;
				j=j+1;
			}
		}
		
		if(record%2==1)		//С⵽׵㣬ȡת
		{
			if(qtis==0)
				ii++;	 
			if(ii>1 && (qtis==0 || qtis ==4 ||qtis == 2||qtis == 5||qtis ==10 || qtis == 9 || qtis == 14 || qtis == 7))
			{
				 turn_back();
				 ii=0;
			}															   
		}
		if(record==10)					 //ھŴ4Ѳߴ⵽ߣǰ26ת90ȡ
		{
			//		Fast_forward(10);
			//		turn_right_90();
			stop();break;	
		}
		
	}	
}