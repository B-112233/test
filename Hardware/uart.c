#include "uart.h"

unsigned char ostart;
unsigned char oend;
char idata outbuf[OLEN];

unsigned char istart;
unsigned char iend;
char idata inbuf[ILEN];
bit bdata sendfull;
bit bdata sendactive;

/*串行中断服务程序*/
static void com_isr(void) interrupt 4 using 1        //串口中断
{ 
   //-------------接收数据中断--------------
  char c;
  if(RI)
  { 
    c=SBUF;
    RI=0;
    if(istart+ILEN!=iend)
    { 
      inbuf[iend++&(ILEN-1)]=c; 
    }
  }

  //-------------发送数据中断--------------
  if(TI)
  { 
    TI=0;
    if(ostart!=oend)
    {  
       SBUF=outbuf[ostart++&(OLEN-1)];
       sendfull=0;
     }
     else
     { 
        sendactive=0; 
     }
   }
}   

//PUTBUF: 写字符到SBUF或发送缓冲区
void putbuf(char c)
{ 
    if(!sendfull)
    {
      if(!sendactive)
      { 
          sendactive=1;
          SBUF=c;
      }
      else 
      { 
        ES=0;
        outbuf[oend++&(OLEN-1)]=c;
        if(((oend^ostart)&(OLEN-1))==0)
         { sendfull=1;}
         ES=1;
      }
    }
}

//替换标准库函数putchar程序
//printf函数使用putchar输出一个字符
char putchar (char c)
{ 
  if (c=='\n')
    {
      while(sendfull);
      putbuf(0x0D);
    }
  while(sendfull);
  putbuf(c);
  return(c);
}

//替换标准库函数_getkey程序
//getchar和gets函数使用_getkey
char _getkey(void)
{ 
  char c;
  while(iend==istart)
  {;}
  ES=0;
  c=inbuf[istart++&(ILEN-1)];
  ES=1;
  return(c);
}

/* 初始化串行口和UART波特率函数*/
void com_initialize(void)
{ 
  istart=0;
  iend=0;
  ostart=0;
  oend=0;
  sendactive=0;
  sendfull=0;

  TMOD |=0x20;   //T/C1工作在方式2
  TH1=0xfd;
  TR1=1;         
  SCON=0xd8;
  ES=1;
}    

void uart_Init()
{ 
  com_initialize();
  EA=1;
}

