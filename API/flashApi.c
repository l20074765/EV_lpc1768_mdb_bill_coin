#include "flashAPi.h"
#include "../config.h"





/*********************************************************************************************************
** Function name:       saveFlash
** Descriptions:        保存数据到flash中
** input parameters:    page：页号；buf：需要保存的数据内容
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
unsigned char saveFlash(unsigned int page,unsigned char *buf,unsigned short len)
{
	if(!buf)
		return 0;
	return I2C0WrNByte(0xa0,2,page,buf,len);
}


/*********************************************************************************************************
** Function name:       readFlash
** Descriptions:        获取指定Flash地址上的数据
** input parameters:    addr：地址一次固定读取256字节
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
unsigned char readFlash(unsigned int page,unsigned char *buf,unsigned short len)
{
	if(!buf)
		return 0;
	
	return I2C0RdNByte(0xa0,2,page,buf,len);
}









