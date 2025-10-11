#include <AT89X52.h>
#include <uart.h>
#include <stdio.h>
#include <Boebot.h>

#define TrigL P2_6	 //�����������ź�
#define EchoL P2_7	 //������echo�����ź�

#define uchar unsigned char
#define uint  unsigned int

uchar timer_cnt=0;	// ��¼����ʱ���жϴ���
uint sonar_used_time=0;
/***********************************************************************/
// ��ʱ����ʼ��
/***********************************************************************/
void InitTimer(void)
{
	TMOD |= 0x01;
    TH0 = 0x0;
    TL0 = 0x0;
    EA = 1;
    ET0 = 1;
    TR0 = 0;
}
/*
	��ʱ��0����ж�
*/
void Interrupt(void) interrupt 1
{
	TR0 = 0;
}
/***********************************************************************/
// ��ຯ��
// ������posʱΪ������װ��λ��L��F��R�ֱ������ǰ��λ��
/***********************************************************************/

unsigned int GetSonarDis(void)
{
	uint dis=0; 
	uint high, low;
	TrigL=0;EchoL=0;  //��I/O���õ�

	TrigL=1;        //trig�ø� ����10us�ĸߵ�ƽ�ź� 
	delay_nus(25);   
	TrigL=0;
	while(EchoL == 0);
	TR0=1;	  
	//������ʱ����ʼ��ʱ
	while(EchoL == 1 && TR0 == 1);   //�ȴ�echo�õ�
	TR0 = 0;
	high = TH0 * 256;
	low = TL0;
	dis = (high + low) / 58;
	if(dis < 3){
		dis = 0;
	}
	return dis;
}