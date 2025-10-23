/************************************************
�ļ� : tcs230.c
���� ��TCS320��ɫʶ��
��д : ����
Ŀ��MCU��AT89S52
����11.0592MHZ
************************************************/
#include "uart2.h"
#include "tcs230.h"
#define	LED P1_3 
    
sbit  s0   =   P2^1;     
sbit  s1   =   P2^2;     
sbit  s2   =   P2^3;    
sbit  s3   =   P2^4;
   

long int  green=0,red=0,blue=0;	//RGB��ɫ��ʼ��

/**********************RGB����ϵ��***************************/
/****************ͨ����ƽ��ó���ʱ�����ϵ��*************/
#define pred   76
#define pgreen 73
#define pblue  72

int  disp_tc;  //������־





/***************************led���� ��˸3��****************************/
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
/***************************��������ʼ��****************************/
void t0_init()
{  
	TMOD=0x51;//���ö�ʱ��0Ϊ������ʽһ

	TH0 =0xfc;
	TL0 =0x66;//���������11.0592MHZ�Ļ��������0.00017%
		
	EA=1;
	ET0=1;
	TR0=1;
	TR1=1;
}

/************************10ms�ж��ӳ��� *******************/
void c1ms_out() interrupt 1//��ʱ��0 1ms�ж���Ӧ
{       
        TR0=0;
        TR1=0;
        
		disp_tc=disp_tc+1; //����ֵ��һ
		TH0=0xfc;
	    TL0=0x66+TL0;     //�Ӷ�ʱ������
						
	    TR0=1;
	    TR1=1;
	
}   

/*****************************�����Ƴ���****************************/
int get_color(void)
{
	unsigned char i = 2;
	int color;
	test_led();			//����led
	delay_nms(80);		//��ʱ �ȴ����ڵ��Թ���
	LED=1;				//��led


	s0=1; s1=1;
	t0_init();
	Time2_init(); 
	while(i--)
	{				//ѡ����ɫ�˹�
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

		//ѡ����ɫ�˹�
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

		//ѡ���ɫ�˹�
		s2=0;
		s3=0;
		while(disp_tc!=pred); 
		TR0=0;
		TR1=0;
		red=TH1*256+TL1;
		TL1=0x00;
		TH1=0x00;
		disp_tc=0;
		//�رն�ʱ��������ֻΪ��ʾ��
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
	else
	{
		color = BLUE;
		printf("color = %d\n", color);
	}
	EA = 0;
	ET0 = 0;
	TR0 = 0;
	TR1 = 0;
	return color;
}


