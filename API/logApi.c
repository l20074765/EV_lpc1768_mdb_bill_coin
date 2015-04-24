
/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           common.h
** Last modified Date:  2013-01-06
** Last Version:        No
** Descriptions:        系统参数定义及通用函数部分                     
**------------------------------------------------------------------------------------------------------
** Created by:          yanbo
** Created date:        20134-02-18
** Version:             V0.1
** Descriptions:        The original version        
********************************************************************************************************/


#include "..\config.h"


#if 0

/*********************************************************************************************************
** Function name:       save_data
** Descriptions:        保存信息
** input parameters:    ptr：写入flash的数据指针，
						len 写入长度 最大长度不超过240字节
						addr写入的起始地址
** output parameters:   无
** Returned value:     0 失败   1成功
*********************************************************************************************************/
static unsigned char  save_data(void *ptr,unsigned short len,unsigned short addr)
{
	unsigned short crc;
	unsigned char buf[256] = {0};//256字节 分8次存储
	if(!ptr || !len || (len > 240))
		return 0;
	
	memcpy(buf,ptr,len);
	crc = CrcCheck(buf,len);
	buf[len + 0] = HUINT16(crc);
	buf[len + 1] = LUINT16(crc);
	len += 2;
	saveFlash(addr,buf,256);	
	return 1;

}

/*********************************************************************************************************
** Function name:       read_data
** Descriptions:        读取信息
** input parameters:    
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
static unsigned char read_data(void *ptr,unsigned short len,unsigned short addr)
{
	unsigned short crc;
	unsigned char buf[256] = {0};
	if(!ptr || !len || (len > 240))
			return 0;
	
	readFlash(addr,buf,256);	
	crc = CrcCheck(buf,len);
	if(crc == INTEG16(buf[len],buf[len + 1]))
	{
		memcpy(ptr,buf,len);
		return 1;
	}	
	return 0;
}




#endif







