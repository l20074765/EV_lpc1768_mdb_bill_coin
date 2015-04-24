/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           key.h
** Last modified Date:  2013-01-08
** Last Version:         
** Descriptions:        2*8键盘驱动头文件                     
**------------------------------------------------------------------------------------------------------
** Created by:          sunway
** Created date:        2013-01-10
** Version:             V0.1
** Descriptions:        The original version       
********************************************************************************************************/
#ifndef __KEY_H 
#define __KEY_H

void InitKeyboard(void);
void EINT2_IsrHandler(void);
unsigned char ReadKeyValue(void);
void DisabaleKeyBoard(void);
void EnableKeyBoard(void);

 #endif
/**************************************End Of File*******************************************************/
