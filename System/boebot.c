#include <intrins.h>
void delay_nus(unsigned int i)
{ 
  i=i/10;
  while(--i);
}   
void delay_nms(unsigned int n)  //��ʱn ms
{ 
  n=n+1;
  while(--n)  
  delay_nus(900);         //��ʱ 1ms,ͬʱ���в���
}   
 
void Frq_delay(unsigned char i)  //��С��ʱ��λ2����������,��ϵͳʱ��Ϊ12M����ʱ��λ2us,��Ϊ11.0592M,����ʱ��λΪ2.2us
{
    while(--i);
}