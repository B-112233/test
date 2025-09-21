#include <AT89X52.H>     //����52ͷ�ļ�
#include <Boebot.h>
#include "motor.h"
#include "uart.h"
#include "ultrasonic.h"

int qtis;
char flag = 0;


void main(void)
{
	unsigned char record=0 + 2,j=0,ji_shu=0,angle=0;
	char ii = 0;
	delay_nms(2000);
	Fast_forward(40);
	while(1)
	{
		P0=0x0f;		//检测黑线															 
		qtis=P0&0x0f;	//读取4个巡线传感器的值
		Fast_forward(1);//前进一小步
		switch(qtis)	//按照4个巡线传感器的值执行移动指令，巡线
		{
			case 1:turn(1550,1550);break;	  //大幅向右转
			case 2: 	 
			case 3:turn(1550,1500);break;	  //小幅向右转

			case 8:turn(1450,1450);break;	  //大幅向左转
			case 4:turn(1500, 1480); break;   //小幅向左转
			case 12:turn(1500,1450);break;	  //小幅向左转

			case 5:
			case 6:
			case 7:
			case 10:
			case 13:
			case 14:
			case 15:Fast_forward(6);break; 	  //向前2小步			
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