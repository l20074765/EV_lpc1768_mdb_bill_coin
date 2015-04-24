/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           Buzer.c
** Last modified Date:  2013-01-04
** Last Version:         
** Descriptions:        Buzzer驱动程序                   
**------------------------------------------------------------------------------------------------------
** Created by:          sunway 
** Created date:        2013-01-04
** Version:             V0.1 
** Descriptions:        The original version       
********************************************************************************************************/
#include "..\config.h"

#define GPIO_Buzzer	(1ul << 30)	//注意需要在LPC1700PinCfg.c中将P1.30脚设置为GPIO
/*********************************************************************************************************
** Function name:     	InitBuzzer
** Descriptions:	    蜂鸣器IO初始化
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void InitBuzzer(void)
{
	FIO1DIR |= GPIO_Buzzer;
	FIO1CLR |= GPIO_Buzzer;	
}

/*********************************************************************************************************
** Function name:     	Buzzer()
** Descriptions:	    蜂鸣器发一声
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void Buzzer(void)
{
	unsigned int i,j;
	for(j=50;j>0;j--)
	{
		FIO1DIR |= GPIO_Buzzer;
		FIO1SET |= GPIO_Buzzer;
		for(i=0;i<8500;i++);
		FIO1DIR |= GPIO_Buzzer;
		FIO1CLR |= GPIO_Buzzer;
		for(i=0;i<8500;i++);
	}	
}
/**************************************End Of File*******************************************************/
