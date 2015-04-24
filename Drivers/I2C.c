/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:                  I2C0.c
** Latest modified Date:       2013-01-04
** Latest Version:
** Descriptions:
**--------------------------------------------------------------------------------------------------------
** Modified by:                sunway
** Modified date:              2013-01-04
** Version:					   V0.1
** Descriptions:               I2C0驱动程序
*********************************************************************************************************/
#include "..\config.h"
/*********************************************************************************************************/
#define ONE_BYTE_SUBA   1
#define TWO_BYTE_SUBA   2
#define X_ADD_8_SUBA    3
/*********************************************************************************************************/
volatile unsigned char I2C0_sla;             //I2C器件从地址
volatile unsigned int  I2C0_suba;            //I2C器件内部子地址
volatile unsigned char I2C0_suba_num;        //I2C子地址字节数
volatile unsigned char *I2C0_buf;            //数据缓冲区指针
volatile unsigned int  I2C0_num;             //要读取/写入的数据个数
volatile unsigned char I2C0_end;             //I2C总线结束标志：结束总线是置1
volatile unsigned char I2C0_suba_en;     	 //子地址控制:0--子地址已经处理或者不需要子地址 1--读取操作 2--写操作
/*********************************************************************************************************/
unsigned char Wait_I2C0_End(unsigned int dly);
unsigned char I2C0RecvByte(unsigned char sla,unsigned char *dat);
unsigned char I2C0SendByte(unsigned char sla,unsigned char  dat);
/*********************************************************************************************************
** Function name:       InitI2C0
** Descriptions:        主模式I2C初始化及向量IRQ中断
** input parameters:    Freq:初始化I2C总线速率，最大值为400K
** Output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void InitI2C0(void)
{
    I2C0SCLH = (FPCLK/400000+1)/2; 			//设置I2C时钟
    I2C0SCLL = (FPCLK/400000)/2;
    I2C0CONCLR = 0x2C;
    I2C0CONSET = 0x40;                  	//使能主I2C 
	zyIsrSet(NVIC_I2C0,(unsigned long)I2C0_IRQHandler,PRIO_THREE);   
}
/*********************************************************************************************************
** Function name:           Wait_I2C0_End
** Descriptions:            软件延时，提供给I2C总线等待超时使用
** input parameters:        dly:延时参数，值越大，延时越久
** Output parameters:       NONE
** Returned value:          NONE
*********************************************************************************************************/
unsigned char Wait_I2C0_End(unsigned int dly)
{  
	unsigned int i;
    if(I2C0_end == 1)
		return(1);
    for(;dly>0;dly--)
	{
	    for(i=0;i<5000;i++)
	    {
	        if(I2C0_end == 1)
				return(1);
	    }
	}
    return(0);
}
/*********************************************************************************************************
** Function name:       I2C0SendByte
** Descriptions:        向无子地址器件发送1字节数据。
** input parameters:    sla:器件地址
**                      dat:要发送的数据
** Output parameters:   返回值为0时表示出错，为1时表示操作正确。
** Returned value:      NONE
*********************************************************************************************************/
unsigned char I2C0SendByte(unsigned char sla, unsigned char dat)
{   
    I2C0_sla     = sla;           //写操作的器件地址
    I2C0_buf     = &dat;          //待发送的数据 
    I2C0_num     = 1;             //发送1字节数据 
    I2C0_suba_en = 0;             //无子地址  
    I2C0_end     = 0;
    I2C0CONCLR   = 0x2C;
    I2C0CONSET   = 0x60;          //设置为主机，并启动总线
    return(Wait_I2C0_End(20));
}
/*********************************************************************************************************
** Function name:       I2C0RcvByte
** Descriptions:        向无子地址器件读取1字节数据。
** input parameters:    sla:器件地址
**                      dat:要发送的数据
** Output parameters:   返回值为0时表示出错，为1时表示操作正确。
** Returned value:      NONE
*********************************************************************************************************/
unsigned char I2C0RecvByte(unsigned char sla, unsigned char *dat)
{                          
    I2C0_sla     = sla+1;         //读操作的器件地址 
    I2C0_buf     = dat;
    I2C0_num     = 1;
    I2C0_suba_en = 0;             //无子地址
    I2C0_end     = 0;

    I2C0CONCLR   = 0x2C;	
    I2C0CONSET   = 0x60;          //设置为主机，并启动总线

    return(Wait_I2C0_End(20));
}
/*********************************************************************************************************
** Function name:       I2C0_ReadNByte
** Descriptions:        从有子地址器件任意地址开始读取N字节数据
** input parameters:    sla         :器件地址
**                      suba_type   :子地址结构    1－单字节地址    3－8+X结构    2－双字节地址
**                      suba        :器件子地址
**                      s           :数据接收缓冲区指针
**                      num         :读取的个数
** Output parameters:   返回值为0时表示出错，为1时表示操作正确。
** Returned value:      NONE
*********************************************************************************************************/
unsigned char I2C0RdNByte(unsigned char sla,unsigned int suba_type,unsigned int suba,unsigned char *s,unsigned int num)
{
    if(num > 0)                                         //判断num个数的合法性   
    {                                                   //参数设置              
        if(suba_type == 1)
        {                                               //子地址为单字节        
            I2C0_sla         = sla + 1;                 //读器件的从地址，R=1   
            I2C0_suba        = suba;                    //器件子地址            
            I2C0_suba_num    = 1;                       //器件子地址为1字节     
        }
        if(suba_type == 2)
        {                                               //子地址为2字节         
            I2C0_sla         = sla + 1;                 //读器件的从地址，R=1   
            I2C0_suba        = suba;                    //器件子地址            
            I2C0_suba_num    = 2;                       //器件子地址为2字节     
        }
        if(suba_type == 3)
        {                                               //子地址结构为8+X       
            I2C0_sla   = sla + ((suba >> 7 )& 0x0e) + 1;//读器件的从地址，R=1   
            I2C0_suba        = suba & 0x0ff;            //器件子地址            
            I2C0_suba_num    = 1;                       //器件子地址为8+x       
        }
        I2C0_buf     = s;                               //数据接收缓冲区指针    
        I2C0_num     = num;                             //要读取的个数          
        I2C0_suba_en = 1;                               //有子地址读            
        I2C0_end     = 0;
        I2C0CONCLR = (1 << 2)|(1 << 3)|(1 << 5);        //清除STA,SI,AA标志位                
        I2C0CONSET = (1 << 5)|(1 << 6);                 //置位STA,启动I2C总线       
        return(Wait_I2C0_End(20));
    }
    return(FALSE);
}
/*********************************************************************************************************
** Function name:       I2C0_WriteNByte
** Descriptions:        向有子地址器件写入N字节数据
** input parameters:    sla         :器件地址
**                      suba_type   :子地址结构    1－单字节地址    3－8+X结构    2－双字节地址
**                      suba        :器件子地址
**                      s           :将要写入的数据的指针
**                      num         :将要写入的数据的个数
** Output parameters:   返回值为0时表示出错，为1时表示操作正确。
** Returned value:      NONE
*********************************************************************************************************/
unsigned char I2C0WrNByte(unsigned char sla,unsigned char suba_type,unsigned int suba,unsigned char *s,unsigned int num)
{
    if(num > 0)                                         //如果读取的个数为0，则返回错 
    {                                                   //设置参数                    
        if(suba_type == 1)
        {                                               //子地址为单字节              
            I2C0_sla         = sla;                     //读器件的从地址              
            I2C0_suba        = suba;                    //器件子地址                  
            I2C0_suba_num    = 1;                       //器件子地址为1字节           
        }
        if(suba_type == 2)
        {                                               //子地址为2字节               
            I2C0_sla         = sla;                     //读器件的从地址              
            I2C0_suba        = suba;                    //器件子地址                  
            I2C0_suba_num    = 2;                       //器件子地址为2字节           
        }
        if(suba_type == 3)
        {                                               //子地址结构为8+X             
            I2C0_sla       = sla + ((suba >> 7 )& 0x0e);//读器件的从地址              
            I2C0_suba        = suba & 0x0ff;            //器件子地址                  
            I2C0_suba_num    = 1;                       //器件子地址为8+X             
        }
        I2C0_buf     = s;                               //数据                        
        I2C0_num     = num;                             //数据个数                    
        I2C0_suba_en = 2;                               //有子地址，写操作            
        I2C0_end     = 0;
        I2C0CONCLR = (1 << 2)|(1 << 3)|(1 << 5);        //清除STA,SI,AA标志位                                       
        I2C0CONSET = (1 << 5)|(1 << 6);                 //置位STA,启动I2C总线                            
        return(Wait_I2C0_End(20));						//等待I2C操作完成
    }
    return(FALSE);
}
/*********************************************************************************************************
** Function name:       I2C0_IRQHandler
** Descriptions:        硬件I2C中断服务程序。
** input parameters:    无
** Output parameters:   无
** Returned value:      注意处理子地址为2字节的情况。
*********************************************************************************************************/
void I2C0_IRQHandler(void)
{   
	//读取I2C状态寄存器I2DAT,按照全局变量的设置进行操作及设置软件标志,清除中断逻辑,中断返回
	//根据状态码进行相应的处理
	OSIntEnter();
    switch(I2C0STAT & 0xF8)
    {   
        case 0x08:	//已发送起始条件,主发送和主接收都有,装入SLA+W或者SLA+R 
					if(I2C0_suba_en == 1)				//SLA+R 指定子地址读
						I2C0DAT = I2C0_sla & 0xFE;      //先写入地址
					else                                //SLA+W
						I2C0DAT = I2C0_sla;             //否则直接发送从机地址
					I2C0CONCLR = (1<<3)|(1<<5);  		//SI,STA
					break;
        case 0x10:	//已发送重复起始条件,主发送和主接收都有
        			I2C0DAT = I2C0_sla;					//装入SLA+W或者SLA+R,重起总线后，重发从地址                                              
        			I2C0CONCLR = 0x28;    				// 清零SI,STA
        			break;
        case 0x18:
        case 0x28:  if(I2C0_suba_en == 0)				//已发送I2DAT中的数据,已接收ACK
					{
						if(I2C0_num > 0)
						{    
							I2C0DAT = *I2C0_buf++;
							I2C0CONCLR = 0x28;          //清零SI,STA
							I2C0_num--;
						}
						else                            //没有数据发送了
						{                               //停止总线
							I2C0CONSET = (1<<4);	    // STO
							I2C0CONCLR = 0x28;          //清零SI,STA
							I2C0_end = 1;               //总线已经停止
						}
					}
					if(I2C0_suba_en == 1)               //若是指定地址读,则重新启动总线
					{
					    if(I2C0_suba_num == 2)
					    {   
							I2C0DAT = ((I2C0_suba >> 8) & 0xff);
					        I2C0CONCLR = 0x28;          //清零SI,STA
					        I2C0_suba_num--;
					        break;
					    }
					    if(I2C0_suba_num == 1)
					    {   
							I2C0DAT = (I2C0_suba & 0xff);
					        I2C0CONCLR = 0x28;          //清零SI,STA
					        I2C0_suba_num--;
					        break;
					    }
					    if(I2C0_suba_num == 0)
					    {
					        I2C0CONCLR = 0x08;
					        I2C0CONSET = 0x20;
								
					        I2C0_suba_en = 0;           //子地址己处理
					        break;
					    }
					}
					if(I2C0_suba_en == 2)               //指定子地址写,子地址尚未指定, 则发送子地址 
					{
					    if(I2C0_suba_num > 0)
					    {    
							if (I2C0_suba_num == 2)
					        {    
								I2C0DAT = ((I2C0_suba >> 8) & 0xff);
					            I2C0CONCLR = 0x28;
					            I2C0_suba_num--;
					            break;
					        }
					        if (I2C0_suba_num == 1)
					        {   
								I2C0DAT    = (I2C0_suba & 0xff);
					            I2C0CONCLR = 0x28;
					            I2C0_suba_num--;
					            I2C0_suba_en  = 0;
					            break;
					        }
					    }
					}
					break;
        case 0x40:  if (I2C0_num <= 1)                  //已发送SLA+R,已接收ACK，如果是最后一个字节           
						I2C0CONCLR = 1 << 2;            //下次发送非应答信号           
			        else								
						I2C0CONSET = 1 << 2;            //下次发送应答信号             
			        I2C0CONCLR = 0x28;                  //清零SI,STA                   
			        break;

        case 0x20:                                      //已发送SLA+W,已接收非应答     
        case 0x30:                                      //已发送I2DAT中的数据，已接收，非应答  
        case 0x38:                                      //在SLA+R/W或数据字节中丢失仲  
        case 0x48:  I2C0CONCLR = 0x28;					//已发送SLA+R,已接收非应答
			        I2C0_end = 0xFF;
			        break;

        case 0x50:  *I2C0_buf++ = I2C0DAT;				//已接收数据字节，已返回ACK
			        I2C0_num--;
			        if(I2C0_num == 1)                   //接收最后一个字节             
						I2C0CONCLR = 0x2C;              //STA,SI,AA = 0                
			        else
			        {   
						I2C0CONSET = 0x04;              //AA=1                         
			            I2C0CONCLR = 0x28;
			        }
			        break;
        case 0x58:  *I2C0_buf++ = I2C0DAT;              //已接收数据字节，已返回非应答/读取最后一字节数据      
			        I2C0CONSET = 0x10;                  //结束总线                    
			        I2C0CONCLR = 0x28;
			        I2C0_end = 1;
			        break;
        default:	break;
    }
	OSIntExit();
}
/**************************************End Of File*******************************************************/
