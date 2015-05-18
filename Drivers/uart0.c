/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           uart0.c
** Last modified Date:  2013-01-04
** Last Version:         
** Descriptions:        Uart0驱动程序                   
**------------------------------------------------------------------------------------------------------
** Created by:          sunway 
** Created date:        2013-01-04
** Version:             V0.1 
** Descriptions:        The original version       
********************************************************************************************************/
#include "..\config.h"
#include <stdarg.h>

//#define	_DEBUG_TRACE


#define	UART0_BPS			9600
#define	UART0BUFFERLEN		128

volatile unsigned char Uart0RevBuff[UART0BUFFERLEN];
volatile unsigned char Uart0RxdHead;
volatile unsigned char Uart0RxdTail;

/*********************************************************************************************************
** Function name:     	InitUart0
** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为9600
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void InitUart0 (void)
{
    unsigned short int ulFdiv;   
    U0LCR  = 0x83;                                                  //允许设置波特率
    ulFdiv = (FPCLK / 16) / UART0_BPS;                              //设置波特率
    U0DLM  = ulFdiv / 256;
    U0DLL  = ulFdiv % 256; 
    U0LCR  = 0x03;                                                  //锁定波特率
    U0FCR  = 0x87;                                                  //使能FIFO，设置8个字节触发点
    U0IER  = 0x01;                                                  //使能接收中断
	Uart0RxdHead  = 0;
	Uart0RxdTail  = 0;
	memset((void *)Uart0RevBuff,0x00,UART0BUFFERLEN);				//初始化缓冲区
	zyIsrSet(NVIC_UART0,(unsigned long)Uart0IsrHandler,PRIO_TEN);	//使能接收中断
}
/*********************************************************************************************************
* Function Name:        Uart0IsrHandler
* Description:          UART0 中断处理函数
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void Uart0IsrHandler (void)
{
	unsigned char Num;
	unsigned char rxd_head;
	unsigned char rxd_data;
	//OS_ENTER_CRITICAL();
	OSIntEnter();      
    while((U0IIR & 0x01) == 0)                          			//判断是否有中断挂起
	{
        switch(U0IIR & 0x0E) 										//判断中断标志
		{                                         
            case 0x04 : for (Num = 0; Num < 8; Num++)				//接收数据中断
						{
		                	rxd_data = U0RBR;
							rxd_head = (Uart0RxdHead + 1);
					        if( rxd_head >= UART0BUFFERLEN ) 
					           	rxd_head = 0;
					        if( rxd_head != Uart0RxdTail) 
					        {
					           	Uart0RevBuff[Uart0RxdHead] = rxd_data;
					           	Uart0RxdHead = rxd_head;
					        }
		                }
		                break;
            case 0x0C : while((U0LSR & 0x01) == 0x01)				//字符超时中断，判断数据是否接收完毕
						{                         
		                	rxd_data = U0RBR;
							rxd_head = (Uart0RxdHead + 1);
					        if( rxd_head >= UART0BUFFERLEN ) 
					           	rxd_head = 0;
					        if( rxd_head != Uart0RxdTail) 
					        {
					           	Uart0RevBuff[Uart0RxdHead] = rxd_data;
					           	Uart0RxdHead = rxd_head;
					        }
		                }
		                break;
            default	: break;
        }
    }
    OSIntExit();
    //OS_EXIT_CRITICAL();
}
/*********************************************************************************************************
** Function name:	    Uart0PutChar
** Descriptions:	    向串口发送子节数据，并等待数据发送完成，使用查询方式
** input parameters:    ch:要发送的数据
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Uart0PutChar(unsigned char ch)
{
    U0THR = ch;                                                      //写入数据
    while((U0LSR & 0x20) == 0);                                      //等待数据发送完毕
}

/*********************************************************************************************************
** Function name:	    Uart0PutStr
** Descriptions:	    向串口发送字符串
** input parameters:    Str:  要发送的字符串指针
**                      Len:   要发送的数据个数
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Uart0PutStr(unsigned char const *Str, unsigned int Len)
{
    unsigned int i;  
    for (i=0;i<Len;i++) 
	{
        Uart0PutChar(*Str++);
    }
}
/*********************************************************************************************************
** Function name:	    Uart0BuffIsNotEmpty
** Descriptions:	    判断缓冲区是否非空
** input parameters:    无
** output parameters:   无
** Returned value:      1：非空；0：空
*********************************************************************************************************/
unsigned char Uart0BuffIsNotEmpty(void)
{
	if(Uart0RxdHead==Uart0RxdTail) 
		return 0;
	else
		return 1;
}


/*********************************************************************************************************
** Function name:     	Uart0_ClrBuf
** Descriptions:	    清除串口2接收缓冲区
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void ClrUart0Buff(void) 
{
	Uart0RxdTail = 0;
	Uart0RxdHead = 0;
}	



/*********************************************************************************************************
** Function name:	    Uart0GetCh
** Descriptions:	    从串口缓冲区读取一个字节，读之前需要判断缓冲区非空
** input parameters:    无
** output parameters:   无
** Returned value:      读取到的数据
*********************************************************************************************************/
unsigned char Uart0GetCh(void)
{
    unsigned char ch;
    ch = Uart0RevBuff[Uart0RxdTail];
    Uart0RevBuff[Uart0RxdTail] = 0;
    Uart0RxdTail++;
    if(Uart0RxdTail >= UART0BUFFERLEN)
		Uart0RxdTail = 0;
	return ch;
}
/*********************************************************************************************************
** Function name:	    PrintLog
** Descriptions:	    向串口发送字符串
** input parameters:    pucStr:  要发送的字符串指针
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void PrintLog(unsigned char *str)
{
	while(*str!='\0')
	{
		Uart0PutChar(*str);
		str++;
	}
}
/*********************************************************************************************************
** Function name:	    Trace
** Descriptions:	    调试Trace
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Trace(unsigned char *format,...)
{
 	#ifdef _DEBUG_TRACE
	va_list arg_ptr;
	unsigned char StringTemp[256];
	unsigned int i;
	unsigned int len;
	va_start(arg_ptr, format);
	len = vsprintf((char *)StringTemp,(const char *)format,arg_ptr);
	va_end(arg_ptr);
	for(i=0;i<len;i++)
	{
		Uart0PutChar(StringTemp[i]);
	}
	#endif	
}
/**************************************End Of File*******************************************************/
