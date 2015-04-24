/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           Uart3.c
** Last modified Date:  2013-01-04
** Last Version:         
** Descriptions:        Uart3驱动程序                   
**------------------------------------------------------------------------------------------------------
** Created by:          sunway 
** Created date:        2013-01-04
** Version:             V0.1 
** Descriptions:        The original version       
********************************************************************************************************/
#include "..\config.h"

#define	UART3_BPS			9600
#define	UART3BUFFERLEN		64

volatile unsigned char Uart3RevBuff[UART3BUFFERLEN];
volatile unsigned char Uart3RxdHead;
volatile unsigned char Uart3RxdTail;

/*********************************************************************************************************
** Function name:     	InitUart3
** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为9600
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void InitUart3 (void)
{
    unsigned short int ulFdiv;
	PCONP = PCONP | (1<<25);   
    U3LCR  = 0x83;                                                  //允许设置波特率
    ulFdiv = (FPCLK / 16) / UART3_BPS;                              //设置波特率
    U3DLM  = ulFdiv / 256;
    U3DLL  = ulFdiv % 256; 
    U3LCR  = 0x03;                                                  //锁定波特率
    U3FCR  = 0x87;                                                  //使能FIFO，设置8个字节触发点
    U3IER  = 0x01;                                                  //使能接收中断
	Uart3RxdHead  = 0;
	Uart3RxdTail  = 0;
	memset((void *)Uart3RevBuff,0x00,UART3BUFFERLEN);				//初始化缓冲区
	zyIsrSet(NVIC_UART3,(unsigned long)Uart3IsrHandler,PRIO_FIVE);	//使能接收中断
}
/*********************************************************************************************************
* Function Name:        Uart3IsrHandler
* Description:          Uart3 中断处理函数
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void Uart3IsrHandler (void)
{
	unsigned char Num;
	unsigned char rxd_head;
	unsigned char rxd_data;
	OSIntEnter();      
    while((U3IIR & 0x01) == 0)                          			//判断是否有中断挂起
	{
        switch(U3IIR & 0x0E) 										//判断中断标志
		{                                         
            case 0x04 : for (Num = 0; Num < 8; Num++)				//接收数据中断
						{
		                	rxd_data = U3RBR;
							rxd_head = (Uart3RxdHead + 1);
					        if( rxd_head >= UART3BUFFERLEN ) 
					           	rxd_head = 0;
					        if( rxd_head != Uart3RxdTail) 
					        {
					           	Uart3RevBuff[Uart3RxdHead] = rxd_data;
					           	Uart3RxdHead = rxd_head;
					        }
		                }
		                break;
            case 0x0C : while((U3LSR & 0x01) == 0x01)				//字符超时中断，判断数据是否接收完毕
						{                         
		                	rxd_data = U3RBR;
							rxd_head = (Uart3RxdHead + 1);
					        if( rxd_head >= UART3BUFFERLEN ) 
					           	rxd_head = 0;
					        if( rxd_head != Uart3RxdTail) 
					        {
					           	Uart3RevBuff[Uart3RxdHead] = rxd_data;
					           	Uart3RxdHead = rxd_head;
					        }
		                }
		                break;
            default	: break;
        }
    }
    OSIntExit();
}
/*********************************************************************************************************
** Function name:	    Uart3PutChar
** Descriptions:	    向串口发送子节数据，并等待数据发送完成，使用查询方式
** input parameters:    ch:要发送的数据
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Uart3PutChar(unsigned char ch)
{
    U3THR = ch;                                                      //写入数据
    while((U3LSR & 0x20) == 0);                                      //等待数据发送完毕
}

/*********************************************************************************************************
** Function name:	    Uart3PutStr
** Descriptions:	    向串口发送字符串
** input parameters:    Str:  要发送的字符串指针
**                      Len:   要发送的数据个数
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Uart3PutStr(unsigned char const *Str, unsigned int Len)
{
    unsigned int i;  
    for (i=0;i<Len;i++) 
	{
        Uart3PutChar(*Str++);
    }
}
/*********************************************************************************************************
** Function name:	    Uart3BuffIsNotEmpty
** Descriptions:	    判断缓冲区是否非空
** input parameters:    无
** output parameters:   无
** Returned value:      1：非空；0：空
*********************************************************************************************************/
unsigned char Uart3BuffIsNotEmpty(void)
{
	if(Uart3RxdHead==Uart3RxdTail) 
		return 0;
	else
		return 1;
}


/*********************************************************************************************************
** Function name:     	uart3_clr_buf
** Descriptions:	    清除串口3接收缓冲区
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void uart3_clr_buf(void) 
{
	Uart3RxdHead = 0;
	Uart3RxdTail = 0;
}




/*********************************************************************************************************
** Function name:	    Uart3GetCh
** Descriptions:	    从串口缓冲区读取一个字节，读之前需要判断缓冲区非空
** input parameters:    无
** output parameters:   无
** Returned value:      读取到的数据
*********************************************************************************************************/
unsigned char Uart3GetCh(void)
{
    unsigned char ch;
    ch = Uart3RevBuff[Uart3RxdTail];
    Uart3RevBuff[Uart3RxdTail] = 0;
    Uart3RxdTail++;
    if(Uart3RxdTail >= UART3BUFFERLEN)
		Uart3RxdTail = 0;
	return ch;
}


/*********************************************************************************************************
** Function name:	    Trace
** Descriptions:	    调试Trace
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Trace3(unsigned char *format,...)
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
		Uart3PutChar(StringTemp[i]);
	}
	#endif	
}


/**************************************End Of File*******************************************************/
