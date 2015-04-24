/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           Uart1.c
** Last modified Date:  2013-01-04
** Last Version:         
** Descriptions:        Uart1驱动程序                   
**------------------------------------------------------------------------------------------------------
** Created by:          sunway 
** Created date:        2013-01-04
** Version:             V0.1 
** Descriptions:        The original version       
********************************************************************************************************/
#include "..\config.h"

#define	UART1_BPS			9600
#define	UART1BUFFERLEN		64

volatile unsigned char Uart1RevBuff[UART1BUFFERLEN];
volatile unsigned char Uart1RxdHead;
volatile unsigned char Uart1RxdTail;

/*********************************************************************************************************
** Function name:     	InitUart1
** Descriptions:	    串口初始化，设置为8位数据位，1位停止位，无奇偶校验，波特率为9600
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void InitUart1 (void)
{
    unsigned short int ulFdiv;
	PCONP = PCONP | (1<<4);   
    U1LCR  = 0x83;                                                  //允许设置波特率
    ulFdiv = (FPCLK / 16) / UART1_BPS;                              //设置波特率
    U1DLM  = ulFdiv / 256;
    U1DLL  = ulFdiv % 256; 
    U1LCR  = 0x03;                                                  //锁定波特率
    U1FCR  = 0x87;                                                  //使能FIFO，设置8个字节触发点
    U1IER  = 0x01;                                                  //使能接收中断
	Uart1RxdHead  = 0;
	Uart1RxdTail  = 0;
	memset((void *)Uart1RevBuff,0x00,UART1BUFFERLEN);				//初始化缓冲区
	zyIsrSet(NVIC_UART1,(unsigned long)Uart1IsrHandler,PRIO_ONE);	//使能接收中断
}
/*********************************************************************************************************
* Function Name:        Uart1IsrHandler
* Description:          Uart1 中断处理函数
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void Uart1IsrHandler (void)
{
	unsigned char Num;
	unsigned char rxd_head;
	unsigned char rxd_data;
	OSIntEnter();      
    while((U1IIR & 0x01) == 0)                          			//判断是否有中断挂起
	{
        switch(U1IIR & 0x0E) 										//判断中断标志
		{                                         
            case 0x04 : for (Num = 0; Num < 8; Num++)				//接收数据中断
						{
		                	rxd_data = U1RBR;
							rxd_head = (Uart1RxdHead + 1);
					        if( rxd_head >= UART1BUFFERLEN ) 
					           	rxd_head = 0;
					        if( rxd_head != Uart1RxdTail) 
					        {
					           	Uart1RevBuff[Uart1RxdHead] = rxd_data;
					           	Uart1RxdHead = rxd_head;
					        }
		                }
		                break;
            case 0x0C : while((U1LSR & 0x01) == 0x01)				//字符超时中断，判断数据是否接收完毕
						{                         
		                	rxd_data = U1RBR;
							rxd_head = (Uart1RxdHead + 1);
					        if( rxd_head >= UART1BUFFERLEN ) 
					           	rxd_head = 0;
					        if( rxd_head != Uart1RxdTail) 
					        {
					           	Uart1RevBuff[Uart1RxdHead] = rxd_data;
					           	Uart1RxdHead = rxd_head;
					        }
		                }
		                break;
            default	: break;
        }
    }
    OSIntExit();
}
/*********************************************************************************************************
** Function name:	    Uart1PutChar
** Descriptions:	    向串口发送子节数据，并等待数据发送完成，使用查询方式
** input parameters:    ch:要发送的数据
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Uart1PutChar(unsigned char ch)
{
    U1THR = ch;                                                      //写入数据
    while((U1LSR & 0x20) == 0);                                      //等待数据发送完毕
}

/*********************************************************************************************************
** Function name:	    Uart1PutStr
** Descriptions:	    向串口发送字符串
** input parameters:    Str:  要发送的字符串指针
**                      Len:   要发送的数据个数
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Uart1PutStr(unsigned char const *Str, unsigned int Len)
{
    unsigned int i;  
    for (i=0;i<Len;i++) 
	{
        Uart1PutChar(*Str++);
    }
}
/*********************************************************************************************************
** Function name:	    Uart1BuffIsNotEmpty
** Descriptions:	    判断缓冲区是否非空
** input parameters:    无
** output parameters:   无
** Returned value:      1：非空；0：空
*********************************************************************************************************/
unsigned char Uart1BuffIsNotEmpty(void)
{
	if(Uart1RxdHead==Uart1RxdTail) 
		return 0;
	else
		return 1;
}
/*********************************************************************************************************
** Function name:	    Uart1GetCh
** Descriptions:	    从串口缓冲区读取一个字节，读之前需要判断缓冲区非空
** input parameters:    无
** output parameters:   无
** Returned value:      读取到的数据
*********************************************************************************************************/
unsigned char Uart1GetCh(void)
{
    unsigned char ch;
    ch = Uart1RevBuff[Uart1RxdTail];
    Uart1RevBuff[Uart1RxdTail] = 0;
    Uart1RxdTail++;
    if(Uart1RxdTail >= UART1BUFFERLEN)
		Uart1RxdTail = 0;
	return ch;
}

/*********************************************************************************************************
** Function name:     	uart3_clr_buf
** Descriptions:	    清除串口3接收缓冲区
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void uart1ClrBuf(void) 
{
	Uart1RxdTail = 0;
	Uart1RxdHead = 0;
}


/**************************************End Of File*******************************************************/
