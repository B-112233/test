#include <AT89X52.H>     //包含52头文件
#include <Boebot.h>

sbit right_moter=P1^0;//定义右电机端口
sbit left_moter =P1^1;//定义左电机端口

void stop(void)//停止
{
	right_moter=1;
	delay_nus(1500);
	right_moter=0;

	left_moter=1;
	delay_nus(1500);
	left_moter=0;
	
	delay_nms(20);
}
	
void Fast_forward(unsigned char a)	//快速前进
{
	unsigned char i;
	for(i=0;i<a;i++)		   
	{
		right_moter=1;
		delay_nus(1439);
		right_moter=0;

		left_moter=1;
		delay_nus(1561);
		left_moter=0;

		delay_nms(20);
	}
}

void Forward(unsigned int left,unsigned int right,unsigned char a)	//自定义前进
{
	unsigned char i;
	for(i=0;i<a;i++)		   
	{
		right_moter=1;
		delay_nus(right);
		right_moter=0;

		left_moter=1;
		delay_nus(left);
		left_moter=0;

		delay_nms(20);
	}
}
 	
void back(unsigned char a)//后退
{	
	unsigned char i;
	for(i=0;i<a;i++)		   
	{
		right_moter=1;
		delay_nus(1580);
		right_moter=0;

		left_moter=1;
		delay_nus(1420);
		left_moter=0;

		delay_nms(20);
	}
}

/* 输入秒数， 左 右*/
void turn(unsigned int left,unsigned int right) //微转动	  
{
	unsigned char i;
	for(i=0;i<2;i++)
	{
		right_moter=1;
		delay_nus(right);
		right_moter=0;
	
		left_moter=1;
		delay_nus(left);
		left_moter=0;
	
		delay_nms(20);
	}
}

void turn_left_150(void)		   //左转150度 
{
	unsigned char i;
	for(i=0;i<100;i++)		   
	{
		right_moter=1;
		delay_nus(1450);
		right_moter=0;

		left_moter=1;
		delay_nus(1450);
		left_moter=0;

		delay_nms(20);
	}
}

void turn_left_90(void)
{
	unsigned char i;
	for(i=0;i<24;i++)		   //左转90度
	{
		right_moter=1;
		delay_nus(1400);
		right_moter=0;

		left_moter=1;
		delay_nus(1400);
		left_moter=0;

		delay_nms(20);
	}
}

void turn_left_45(void)		   //左转45度 
{
	unsigned char i;
	for(i=0;i<15;i++)		   
	{
		right_moter=1;
		delay_nus(1400);
		right_moter=0;

		left_moter=1;
		delay_nus(1400);
		left_moter=0;

		delay_nms(20);
	}
}

void turn_left_120(void)		   //左转120度 
{
	unsigned char i;
	for(i=0;i<180;i++)		   
	{
		right_moter=1;
		delay_nus(1480);
		right_moter=0;

		left_moter=1;
		delay_nus(1480);
		left_moter=0;

		delay_nms(20);
	}
}

void turn_right_150(void)
{
	unsigned char i;
	for(i=0;i<70;i++)		   //右转150度
	{
		right_moter=1;
		delay_nus(1550);
		right_moter=0;

		left_moter=1;
		delay_nus(1550);
		left_moter=0;

		delay_nms(20);
	}	
}

void turn_right_90(void) 
{
	unsigned char i;
	for(i=0;i<26;i++)		   //右转90度
	{
		right_moter=1;
		delay_nus(1600);
		right_moter=0;

		left_moter=1;
		delay_nus(1600);
		left_moter=0;

		delay_nms(20);
	}
}

void turn_right_45(void)
{
	unsigned char i;
	for(i=0;i<15;i++)		   //右转45度
	{
		right_moter=1;
		delay_nus(1600);
		right_moter=0;

		left_moter=1;
		delay_nus(1600);
		left_moter=0;

		delay_nms(20);
	}	
}

void turn_right_120(void)
{
	unsigned char i;
	for(i=0;i<180;i++)		   //右转120度
	{
		right_moter=1;
		delay_nus(1520);
		right_moter=0;

		left_moter=1;
		delay_nus(1520);
		left_moter=0;

		delay_nms(20);
	}	
}

void fast_turn_right_90(void)
{
	unsigned char i;
	for(i=0;i<26;i++)		   //右转90度
	{
		right_moter=1;
		delay_nus(1600);
		right_moter=0;

		left_moter=1;
		delay_nus(1600);
		left_moter=0;

		delay_nms(20);
	}
}

/* 输入秒数， 左 右*/
void turn_r(unsigned int left,unsigned int right) //转动	  
{
	
	right_moter=1;
	delay_nus(right);
	right_moter=0;

	left_moter=1;
	delay_nus(left);
	left_moter=0;

	delay_nms(20);

}

void turn_back()	//后转 
{
	unsigned int i;
	for(i=0;i<68;i++)		  
	{
		right_moter=1;
		delay_nus(1440);
		right_moter=0;

		left_moter=1;
		delay_nus(1440);
		left_moter=0;

		delay_nms(20);
	}
}