#include <AT89X52.H>     //����52ͷ�ļ�
#include <Boebot.h>

sbit right_moter=P1^0;//�����ҵ���˿�
sbit left_moter =P1^1;//���������˿�

void stop(void)//ֹͣ
{
	right_moter=1;
	delay_nus(1500);
	right_moter=0;

	left_moter=1;
	delay_nus(1500);
	left_moter=0;
	
	delay_nms(20);
}
	
void Fast_forward(unsigned char a)	//����ǰ��
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

void Forward(unsigned int left,unsigned int right,unsigned char a)	//�Զ���ǰ��
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
 	
void back(unsigned char a)//����
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

/* ���������� �� ��*/
void turn(unsigned int left,unsigned int right) //΢ת��	  
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

void turn_left_150(void)		   //��ת150�� 
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
	for(i=0;i<24;i++)		   //��ת90��
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

void turn_left_45(void)		   //��ת45�� 
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

void turn_left_120(void)		   //��ת120�� 
{
	unsigned char i;
	for(i=0;i<70;i++)		   
	{
		right_moter=1;
		delay_nus(1460);
		right_moter=0;

		left_moter=1;
		delay_nus(1460);
		left_moter=0;

		delay_nms(20);
	}
}

void turn_right_150(void)
{
	unsigned char i;
	for(i=0;i<70;i++)		   //��ת150��
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
	for(i=0;i<26;i++)		   //��ת90��
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
	for(i=0;i<15;i++)		   //��ת45��
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
	for(i=0;i<70;i++)		   //��ת120��
	{
		right_moter=1;
		delay_nus(1540);
		right_moter=0;

		left_moter=1;
		delay_nus(1540);
		left_moter=0;

		delay_nms(20);
	}	
}

void fast_turn_right_90(void)
{
	unsigned char i;
	for(i=0;i<26;i++)		   //��ת90��
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

/* ���������� �� ��*/
void turn_r(unsigned int left,unsigned int right) //ת��	  
{
	
	right_moter=1;
	delay_nus(right);
	right_moter=0;

	left_moter=1;
	delay_nus(left);
	left_moter=0;

	delay_nms(20);

}

void turn_back()	//��ת 
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

void turn_back_r() // ��ת
{
	unsigned int i;
	for (i = 0; i < 68; i++)
	{
		right_moter = 1;
		delay_nus(1560);
		right_moter = 0;

		left_moter = 1;
		delay_nus(1560);
		left_moter = 0;

		delay_nms(20);
	}
}