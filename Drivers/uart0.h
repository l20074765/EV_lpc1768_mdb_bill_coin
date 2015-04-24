/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           uart0.h
** Last modified Date:  2013-01-04
** Last Version:         
** Descriptions:        uart0驱动程序相关函数声明                      
**------------------------------------------------------------------------------------------------------
** Created by:          sunway
** Created date:        2013-01-04
** Version:             V0.1 
** Descriptions:        The original version
**------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:        
********************************************************************************************************/
#ifndef __UART0_H 
#define __UART0_H

void InitUart0(void);
void Uart0IsrHandler(void);
void Uart0PutChar(unsigned char ch);
void Uart0PutStr(unsigned char const *Str, unsigned int Len);
unsigned char Uart0BuffIsNotEmpty(void);
unsigned char Uart0GetCh(void);
void ClrUart0Buff(void) ;
//以下两函数做Uart0的调试输出
void PrintLog(unsigned char *str);
void Trace(unsigned char *format,...);

#endif
/**************************************End Of File*******************************************************/
