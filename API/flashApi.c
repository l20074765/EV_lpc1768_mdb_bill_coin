#include "flashAPi.h"
#include "../config.h"


static unsigned char buf[512];


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




unsigned char FM_readFromFlash(void)
{
	unsigned short index = 0;
	unsigned char i;
	memset(buf,0,sizeof(buf));
	readFlash(0x00,buf,256);
	if(buf[index++] != 0xE5){
		return 0;
	}
	stMdb.bill_type = buf[index++];
	stMdb.coin_type = buf[index++];
	stMdb.highEnable = buf[index++];
	for(i = 0;i < 16;i++){
		stPcoin.ch[i] = INTEG32(buf[index + 0],buf[index + 1],
									buf[index + 2],buf[index + 3]);
		index += 4;
	}
	
	for(i = 0;i < HP_SUM;i++){
		stHopper[i].ch = INTEG32(buf[index + 0],buf[index + 1],
									buf[index + 2],buf[index + 3]);
		index += 4;
	}
	return 1;
}



unsigned char FM_writeToFlash(void)
{
	unsigned short index = 0;
	unsigned char i;
	buf[index++] = 0xE5; // 校验码
	buf[index++] = stMdb.bill_type;
	buf[index++] = stMdb.coin_type;
	buf[index++] = stMdb.highEnable;
	for(i = 0;i < 16;i++){
		buf[index++] = H0UINT32(stPcoin.ch[i]);
		buf[index++] = H1UINT32(stPcoin.ch[i]);
		buf[index++] = L0UINT32(stPcoin.ch[i]);
		buf[index++] = L1UINT32(stPcoin.ch[i]);
	}
	
	for(i = 0;i < HP_SUM;i++){
		buf[index++] = H0UINT32(stHopper[i].ch);
		buf[index++] = H1UINT32(stHopper[i].ch);
		buf[index++] = L0UINT32(stHopper[i].ch);
		buf[index++] = L1UINT32(stHopper[i].ch);
	}
	
	
	

	saveFlash(0x00,buf,index);
	return 1;
}







