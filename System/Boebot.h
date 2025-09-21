
#ifndef _BOEBOT_H
#define _BOEBOT_H
#include <at89x52.h>
void delay_nus(unsigned int i);  //延时:i>=12 ,i的最小延时单12 us
void delay_nms(unsigned int n);  //延时n ms
void Frq_delay(unsigned char i);  //最小延时单位2个机器周期,若系统时钟为12M则延时单位2us,若为11.0592M,则延时单位为2.2us

#endif

