#include <intrins.h>
void delay_nus(unsigned int i)
{ 
  i=i/10;
  while(--i);
}   
void delay_nms(unsigned int n)  //延时n ms
{ 
  n=n+1;
  while(--n)  
  delay_nus(900);         //延时 1ms,同时进行补偿
}   
 
void Frq_delay(unsigned char i)  //最小延时单位2个机器周期,若系统时钟为12M则延时单位2us,若为11.0592M,则延时单位为2.2us
{
    while(--i);
}