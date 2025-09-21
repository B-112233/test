#include <AT89X52.h>
#include <uart.h>
#include <stdio.h>
#include <Boebot.h>

#define TrigL P2_6	 //左超声波触发信号
#define EchoL P2_7	 //左超声波echo引脚信号

#define uchar unsigned char
#define uint  unsigned int

uchar timer_cnt=0;	// 记录进定时器中断次数
uint sonar_used_time=0;
/***********************************************************************/
// 定时器初始化
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
	定时器0溢出中断
*/
void Interrupt(void) interrupt 1
{
	TR0 = 0;
}
/***********************************************************************/
// 测距函数
// 参数：pos时为超声波装置位置L、F、R分别代表左前右位置
/***********************************************************************/

unsigned int GetSonarDis(void)
{
	uint dis=0; 
	uint high, low;
	TrigL=0;EchoL=0;  //各I/O口置低

	TrigL=1;        //trig置高 发出10us的高电平信号 
	delay_nus(25);   
	TrigL=0;
	while(EchoL == 0);
	TR0=1;	  
	//开启定时器开始计时
	while(EchoL == 1 && TR0 == 1);   //等待echo置低
	TR0 = 0;
	high = TH0 * 256;
	low = TL0;
	dis = (high + low) / 58;

	return dis;
}