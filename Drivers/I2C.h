/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:                  I2C0.h
** Latest modified Date:       2013-01-04
** Latest Version:
** Descriptions:
**--------------------------------------------------------------------------------------------------------
** Modified by:                sunway
** Modified date:              2013-01-04
** Version:					   V0.1
** Descriptions:               I2C0驱动程序头文件
*********************************************************************************************************/
#ifndef __I2C_H
#define __I2C_H

void InitI2C0(void);
void I2C0_IRQHandler(void);
unsigned char I2C0RdNByte(unsigned char sla,unsigned int  suba_type,unsigned int suba,unsigned char *s,unsigned int num);
unsigned char I2C0WrNByte(unsigned char sla,unsigned char suba_type,unsigned int suba,unsigned char *s,unsigned int num);

#endif
/**************************************End Of File*******************************************************/
