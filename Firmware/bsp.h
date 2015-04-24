/****************************************Copyright (c)****************************************************
**                            fuzhou powerorigin Co.,LTD.
**
**                                 http://www.powerorigin.cn
**
**--------------File Info---------------------------------------------------------------------------------
** File name:           bsp.h
** Last modified Date:  2011-07-22
** Last Version:         
** Descriptions:        板级相关定义
**                      
**------------------------------------------------------------------------------------------------------
** Created by:           
** Created date:        2011-07-22
** Version:              
** Descriptions:        The original version
**
**------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:        
**
********************************************************************************************************/
#ifndef __BSP_H 
#define __BSP_H

#include "..\config.h"

#define UART2MODESELECT0 (1<<29)			//P1.29 select as GPIO IN LPC1700PinCfg.h
#define UART2MODESELECT1 (1<<28)			//P1.28 select as GPIO IN LPC1700PinCfg.h
#define MDB_MODE_SET()   		FIO1DIR |= UART2MODESELECT0;\
								FIO1DIR |= UART2MODESELECT1;\
								FIO1CLR |= UART2MODESELECT0;\
								FIO1CLR |= UART2MODESELECT1
#define EVB0_MODE_SET()   		FIO1DIR |= UART2MODESELECT0;\
								FIO1DIR |= UART2MODESELECT1;\
								FIO1SET |= UART2MODESELECT0;\
								FIO1CLR |= UART2MODESELECT1
#define EVB1_MODE_SET()   		FIO1DIR |= UART2MODESELECT0;\
								FIO1DIR |= UART2MODESELECT1;\
 								FIO1CLR |= UART2MODESELECT0;\
								FIO1SET |= UART2MODESELECT1
#define EVB_MODE_SET()   		FIO1DIR |= UART2MODESELECT0;\
								FIO1DIR |= UART2MODESELECT1;\
 								FIO1SET |= UART2MODESELECT0;\
								FIO1SET |= UART2MODESELECT1

//EVB_PWR P2.9	Modfiy & add by chensunwei
#define EVB_PWR        (1ul << 9)
#define EVB_PWRON()    GPIO_SetDir(2, EVB_PWR, 1);  GPIO_ClearValue(2, EVB_PWR)                     
#define EVB_PWROFF()   GPIO_SetDir(2, EVB_PWR, 1);  GPIO_SetValue(2, EVB_PWR)  


//CS-P3.25,MOSI-P1.24,Clk0-P1.25,Clk1-P1.26	LCD_BL_EN-P2.8Modfiy & add by chensunwei
//片选CS是选通整个LCD屏，串行数据MOSI是发送数据，串行时钟CLK0是通过控制时钟线来发送数据下半屏的，CLK1是通过控制时钟线来发送数据上半屏的
//由于新的大屏其实是由两个屏拼接在一起的，所以他上半屏有上半屏的时钟线，下半屏有下半屏的时钟线，控制这个时钟线就能使用屏了
//LCD_BL_EN控制背光的亮和暗
#define CS_SET()     	FIO3DIR |= (1ul << 25); FIO3SET |= (1ul << 25)	   //串行选通
#define CS_CLR()     	FIO3DIR |= (1ul << 25); FIO3CLR |= (1ul << 25)
#define SID_SET()    	FIO1DIR |= (1ul << 24); FIO1SET |= (1ul << 24)    //串行数据
#define SID_CLR()    	FIO1DIR |= (1ul << 24); FIO1CLR |= (1ul << 24) 
#define SCLK_SET_Up()   FIO1DIR |= (1ul << 25); FIO1SET |= (1ul << 25)    //串行时钟,上半屏
#define SCLK_CLR_Up()   FIO1DIR |= (1ul << 25); FIO1CLR |= (1ul << 25)
#define SCLK_SET()   	FIO1DIR |= (1ul << 26);  FIO1SET |= (1ul << 26)    //串行时钟,下半屏
#define SCLK_CLR()   	FIO1DIR |= (1ul << 26);  FIO1CLR |= (1ul << 26)
#define SCLK_BL_SET()   FIO2DIR |= (1ul << 8);  FIO2SET |= (1ul << 8)    //背光控制
#define SCLK_BL_CLR()   FIO2DIR |= (1ul << 8);  FIO2CLR |= (1ul << 8)


//添加品途屏幕的兼容;by gzz 20121025
//用于拼图的屏幕
#define SCL_SET()   FIO3DIR |= (1ul << 25); FIO3SET |= (1ul << 25)	//SCL Clock,P3.25
#define SCL_CLR()   FIO3DIR |= (1ul << 25); FIO3CLR |= (1ul << 25)

#define SDA_SET()   FIO1DIR |= (1ul << 24); FIO1SET |= (1ul << 24) 	//SDL DATA,P1.24
#define SDA_CLR()   FIO1DIR |= (1ul << 24); FIO1CLR |= (1ul << 24) 

#define nCS_SET()   FIO1DIR |= (1ul << 25); FIO1SET |= (1ul << 25) 	//CS ChipSel,P1.25
#define nCS_CLR()   FIO1DIR |= (1ul << 25); FIO1CLR |= (1ul << 25)

#define CD_SET()    FIO1DIR |= (1ul << 26); FIO1SET |= (1ul << 26) 	//CD Data&CMD,P1.26
#define CD_CLR()    FIO1DIR |= (1ul << 26); FIO1CLR |= (1ul << 26)


//游戏按键灯P1.27
#define GAME_LED_ON()   FIO1DIR |= (1ul << 27); FIO1SET |= (1ul << 27)  
#define GAME_LED_OFF()  FIO1DIR |= (1ul << 27); FIO1CLR |= (1ul << 27)  
//游戏按键输入P2.7
#define GAMEKey_SetInput() FIO2DIR &= ~(1ul << 7)//设为输入模式
#define GAMEKey_Get()      ( ((FIO2PIN >> 7) & 0x01) == 0 )

//120821 by cq ReturnCoinKey
//退币按键输入P0.22
#define ReturnCoinKey_SetInput() FIO0DIR &= ~(1ul << 22)//设为输入模式
#define ReturnCoinKey_Get()      ( ((FIO0PIN >> 22) & 0x01) == 0 )




//W_CTL0 P3.26	Modfiy & add by chensunwei
#define WM_POWER        (1ul << 26)
#define WM_POWERON()   GPIO_SetDir(3, GPRS_POWER, 1);  GPIO_ClearValue(3, GPRS_POWER) //GPRS电源开
#define WM_POWEROFF()  GPIO_SetDir(3, GPRS_POWER, 1);  GPIO_SetValue(3, GPRS_POWER)   //GPRS电源关

//Buzzer P1.30	Modfiy & add by chensunwei
#define BEEP         (1ul << 30)                     
#define BEEPON()     GPIO_SetDir(1, BEEP, 1);  GPIO_SetValue(1, BEEP) 
#define BEEPOFF()    GPIO_SetDir(1, BEEP, 1);  GPIO_ClearValue(1, BEEP) 

//外设5.0V电源控制,P0.23电源控制端 Modfiy & add by chensunwei
#define VCC_POWER		 (1ul<<23)		
#define VCC_POWEROFF()	 GPIO_SetDir(0, VCC_POWER, 1);  GPIO_ClearValue(0, VCC_POWER)
#define VCC_POWERON()	 GPIO_SetDir(0, VCC_POWER, 1);  GPIO_SetValue(0, VCC_POWER)

#define MAINTEN_SWITCH()     (FIO4PIN & (1ul << 29))	 //维护开关p4-29


#define CS_GET()     (FIO1PIN & (1ul << 24))
#define SID_GET()    (FIO1PIN & (1ul << 25))
#define SCLK_GET()   (FIO1PIN & (1ul << 26))

/*键盘*/
#if KEY_MODE == KEY_4X6

#define KeyX_SetInput() FIO1DIR &= ~(0x0F	<< 14)
#define KeyY_SetInput() FIO0DIR &= ~(0x3F << 4)
#define KeyX_Set0()     {FIO1DIR |= 0x0F << 14; FIO1CLR |= 0x0F << 14;}
#define KeyY_Set0()     {FIO0DIR |= 0x3F << 4; FIO0CLR |= 0x3F << 4;}
#define KeyX_Get()      ((FIO1PIN >> 14) & 0x0F) 
#define KeyY_Get()      ((FIO0PIN >> 4) & 0x3F)

#elif KEY_MODE == KEY_2X8

#define KeyX	 	(0x03 << 14)												 							//行 对应引脚
#define KeyY	  	(0x3F << 4)													 							//列 对应引脚
#define KeyY0		(0x03 << 16)												 							//列 对应引脚

#define KeyX_SetInput() GPIO_SetDir(1, KeyX, 0)			   													//行设置为输入状态
#define KeyY_SetInput() {GPIO_SetDir(0, KeyY, 0); GPIO_SetDir(1, KeyY0, 0);}   								//列设置为输入状态
#define KeyX_Set0()     {GPIO_SetDir(1, KeyX, 1); GPIO_ClearValue(1, KeyX);}   								//行输出0
#define KeyY_Set0()     {GPIO_SetDir(0, KeyY, 1); GPIO_SetDir(1, KeyY0, 1); GPIO_ClearValue(0, KeyY); GPIO_ClearValue(1, KeyY0);}	//列输出0
#define KeyX_Get()      ((GPIO_ReadValue(1) >> 14) & 0x03) 			 										//获取行值
#define KeyY_Get()      (((GPIO_ReadValue(0) >> 4) & 0x3F) << 2) | ((GPIO_ReadValue(1) >> 16) & 0x03)	 	//获取列值

#endif
/*键盘结束*/
#endif
