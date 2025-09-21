#include "uart.h"

unsigned char ostart;
unsigned char oend;
char idata outbuf[OLEN];

unsigned char istart;
unsigned char iend;
char idata inbuf[ILEN];
bit bdata sendfull;
bit bdata sendactive;

/*�����жϷ������*/
static void com_isr(void) interrupt 4 using 1        //�����ж�
{ 
   //-------------���������ж�--------------
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

  //-------------���������ж�--------------
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

//PUTBUF: д�ַ���SBUF���ͻ�����
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

//�滻��׼�⺯��putchar����
//printf����ʹ��putchar���һ���ַ�
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

//�滻��׼�⺯��_getkey����
//getchar��gets����ʹ��_getkey
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

/* ��ʼ�����пں�UART�����ʺ���*/
void com_initialize(void)
{ 
  istart=0;
  iend=0;
  ostart=0;
  oend=0;
  sendactive=0;
  sendfull=0;

  TMOD |=0x20;   //T/C1�����ڷ�ʽ2
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

