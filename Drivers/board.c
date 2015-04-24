/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           board.c
** Last modified Date:  2013-01-06
** Last Version:        No
** Descriptions:        系统参数定义及通用函数部分                     
**------------------------------------------------------------------------------------------------------
** Created by:          yoc
** Created date:        2015-04-20
** Version:             V0.1
** Descriptions:        The original version        
********************************************************************************************************/

#include "board.h"
#include "..\config.h"








/*********************************************************************************************************
** Function name:     	XorCheck
** Descriptions:	    累加校验和
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
unsigned char XorCheck(unsigned char *pstr,unsigned short len)
{
	unsigned char xor_check = 0;
	unsigned short i;
	for(i=0;i<len;i++) 
	{
       	xor_check = xor_check^pstr[i];
   	}
	return xor_check;
}
/*********************************************************************************************************
** Function name:     	CrcCheck
** Descriptions:	    CRC校验和
** input parameters:    msg需要检验的数据;len数据长度
** output parameters:   无
** Returned value:      CRC检验结果
*********************************************************************************************************/
unsigned short CrcCheck(unsigned char *msg, unsigned short len) 
{
    unsigned short i, j;
    unsigned short crc = 0;
    unsigned short current = 0;
    for(i=0;i<len;i++) 
    {
        current = msg[i] << 8;
        for(j=0;j<8;j++) 
        {
            if((short)(crc^current)<0)
                crc = (crc<<1)^0x1021;
            else 
                crc <<= 1; 
            current <<= 1; 
        }
    }
    return crc;
}






/*********************************************************************************************************
** Function name:     	msleep
** Descriptions:	    毫秒睡眠函数  比较
** input parameters:    msg需要检验的数据;len数据长度
** output parameters:   无
** Returned value:      CRC检验结果
*********************************************************************************************************/

void msleep(unsigned int msec)
{
	unsigned int temp;
	temp = (msec > 10) ? msec/5 : 2;
	OSTimeDly(temp);
}



/**************************************End Of File*******************************************************/
