/*----------------------------------------------------------------
                     8051串口中断驱动程序
--------------------------------------------------------------*/
#ifndef _UART_H
#define _UART_H

#include <AT89X52.h>
#include <stdio.h>
#define XTAL 11059200
#define baudrate 9600
#define OLEN 8
#define ILEN 8

void putbuf(char c);
char putchar (char c);
char _getkey(void);
void com_initialize(void);
void uart_Init();
#endif

