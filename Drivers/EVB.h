/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           EVB.h
** Last modified Date:  2013-01-07
** Last Version:        V0.1 
** Descriptions:        EVB通讯协议相关函数声明                     
**------------------------------------------------------------------------------------------------------
** Created by:          sunway
** Created date:        2013-01-07
** Version:             V0.1
** Descriptions:        The original version      
********************************************************************************************************/
#ifndef __EVB_H 
#define __EVB_H

uint8_t EvbConversation(uint8_t Chl,uint8_t Head,uint8_t Sn,uint8_t Type,uint8_t Addr,uint16_t Data,uint8_t *Ack);

#endif
/**************************************End Of File*******************************************************/
