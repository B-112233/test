/************************************************
文件 : tcs230.c
描述 ：TCS320颜色识别
编写 : 朱林
目标MCU：AT89S52
晶振：11.0592MHZ
************************************************/
#include "uart2.h"
#include "tcs230.h"
#define	LED P1_3 
    
sbit  s0   =   P2^1;     
sbit  s1   =   P2^2;     
sbit  s2   =   P2^3;    
sbit  s3   =   P2^4;
   

long int  green=0,red=0,blue=0;	//RGB颜色初始化

/**********************RGB比例系数***************************/
/****************通过白平衡得出的时间比例系数*************/
#define pred   76
#define pgreen 73
#define pblue  72

int  disp_tc;  //计数标志





/***************************led测试 闪烁3次****************************/
void test_led()
{
	uchar i;
	for(i=0;i<3;i++)
	{
		LED=0;
		delay_nms(200);
		LED=1;
		delay_nms(200);
	}
	LED=0;
}
/***************************计数器初始化****************************/
void t0_init()
{  
	TMOD=0x51;//设置定时器0为工作方式一

	TH0 =0xfc;
	TL0 =0x66;//如果晶振是11.0592MHZ的话，误差是0.00017%
		
	EA=1;
	ET0=1;
	TR0=1;
	TR1=1;
}

/************************10ms中断子程序 *******************/
void c1ms_out() interrupt 1//定时器0 1ms中断响应
{       
        TR0=0;
        TR1=0;
        
		disp_tc=disp_tc+1; //计数值加一
		TH0=0xfc;
	    TL0=0x66+TL0;     //加定时器补偿
						
	    TR0=1;
	    TR1=1;
	
}   

/*****************************主控制程序****************************/
int get_color(void)
{
	unsigned char i = 5;
	int color;
	test_led();			//测试led
	delay_nms(80);		//延时 等待串口调试工具
	LED=1;				//打开led


	s0=1; s1=1;
	t0_init();
	Time2_init(); 
	while(i--)
	{				//选择蓝色滤光
		disp_tc=0;
		s2=0;
		s3=1;
		while(disp_tc!=pblue);
		TR0=0;
		TR1=0;
		blue=TH1*256+TL1;
		TL1=0x00;
		TH1=0x00;
		disp_tc=0;
		TR0=1;
		TR1=1;

		//选择绿色滤光
		s2=1;
		s3=1;
		while(disp_tc!=pgreen);
		TR0=0;
		TR1=0;
		green=TH1*256+TL1;
		TL1=0x00;
		TH1=0x00;
		disp_tc=0;
		TR0=1;
		TR1=1;

		//选择红色滤光
		s2=0;
		s3=0;
		while(disp_tc!=pred); 
		TR0=0;
		TR1=0;
		red=TH1*256+TL1;
		TL1=0x00;
		TH1=0x00;
		disp_tc=0;
		//关闭定时计数器，只为显示。
		printf("red=%ld,green=%ld,blue=%ld\n",red,green,blue);
		delay_nms(200);
		TR0=1;
		TR1=1;	
	}

	printf("red=%ld,green=%ld,blue=%ld\n", red, green, blue);
	if(red <= 35 && green <= 35 && blue <= 35){
		color = BLACK;
	}
	else if (red >= 200 && green >= 200 && blue >= 200){
		color = WHITE;
	}
	else if (red >= 150 && green <= 50 && blue <= 50){
		color = RED;
	}
	else if (red >= 200 && green >= 150 && blue <= 100){
		color = YELLOW;
	}
	else{
		color = BLUE;
		printf("color = %d\n", color);
	}
	EA = 0;
	ET0 = 0;
	TR0 = 0;
	TR1 = 0;
	return color;
}


