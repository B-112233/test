
#ifndef _BOEBOT_H
#define _BOEBOT_H
#include <at89x52.h>
void delay_nus(unsigned int i);  //��ʱ:i>=12 ,i����С��ʱ��12 us
void delay_nms(unsigned int n);  //��ʱn ms
void Frq_delay(unsigned char i);  //��С��ʱ��λ2����������,��ϵͳʱ��Ϊ12M����ʱ��λ2us,��Ϊ11.0592M,����ʱ��λΪ2.2us

#endif

