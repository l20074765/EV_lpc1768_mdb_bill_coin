/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           MDB.h
** Last modified Date:  2013-01-08
** Last Version:         
** Descriptions:        MDB通讯协议                     
**------------------------------------------------------------------------------------------------------
** Created by:          sunway
** Created date:        2013-01-08
** Version:             V0.1
** Descriptions:        The original version       
********************************************************************************************************/
#include "..\config.h"


#define  DEBUG_MDB
#ifdef 	 DEBUG_MDB
#define  print_mdb(...)       Trace(__VA_ARGS__)
#else
#define  print_mdb(...) 
#endif




/*********************************************************************************************************
** Function name:     	MdbBusHardwareReset
** Descriptions:	    MDB总线复位：将MDB总线TXD线拉低200ms;注意该函数为硬件复位，总线上所有设备都复位
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
/*void MdbBusHardwareReset(void)
{
	PINSEL0 &=(~(0x03<<20));	//P0.10改为GPIO
	FIO0DIR |= (1ul<<10);		//设置为输出
	FIO0CLR |= (1ul<<10);		//输出0
	OSTimeDly(40);				//延时200ms
	PINSEL0 |= (0x03<<20);		//设置为TXD功能
	InitUart2();
	return;
}*/


/*********************************************************************************************************
** Function name:     	MdbBusHardwareReset
** Descriptions:	    MDB总线复位：将MDB总线TXD线拉低200ms;注意该函数为硬件复位，总线上所有设备都复位
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void MdbBusHardwareReset(void)
{
	SetUart2MdbMode();
	PINSEL0 &= (~(0x03<<20));	//P0.10改为GPIO模式
	FIO0DIR |= (1ul<<10);		//设置为输出
	FIO0CLR |= (1ul<<10);		//输出0
	OSTimeDly(40);				//延时200ms
	PINSEL0 |= (0x01<<20);		//设置为TXD功能
	InitUart2();
	return;
}



/*********************************************************************************************************
** Function name:     	MdbConversation
** Descriptions:	    MDB设备通讯
** input parameters:    Dev:设备号(高5位地址及低三位命令)；
**						*SeDat:要发送的数据；
**						SenDatLen：要发送数据的长度
** output parameters:   *RevDat:接收到的数据；RevLen:接收到数据的长度；
** Returned value:      0；通讯超时 1：通讯成功： 2 接收越界 3校验错误
*********************************************************************************************************/
uint8_t MDB_conversation(uint8_t dev,uint8_t *sdata,uint8_t slen,uint8_t *rdata,uint8_t *rlen)
{
	unsigned char i,check = 0,err = 0,temp;	

	check = dev;
	ClrUart2Buff();
	OSIntEnter();
	MdbPutChr(dev,MDB_ADD);					//送出MDB地址及命令
	for(i=0;i< slen;i++)				//送出数据
	{
		MdbPutChr(sdata[i],MDB_DAT);
		check += sdata[i];	
	}
	MdbPutChr(check,MDB_DAT);				//送出校验和
	OSIntExit();
#ifdef DEBUG_MDB
	print_mdb("MDB-SEND[%d]:",slen + 1);
	print_mdb("%02x ",dev);
	for(i = 0;i < slen;i++){
		print_mdb("%02x ",sdata[i]);
	}
	print_mdb("\r\n");
#endif
	Timer.mdb_timeout = 200;	//进入ACK等待，超时1000ms
	while(Timer.mdb_timeout)
	{
		temp = GetMdbStatus();
		if(temp > MDB_RCV_DATA)
		{
			switch(temp)
			{
				case MDB_RCV_OK		: 
					*rlen = Uart2GetStr(rdata,MDB_MAX_BLOCK_SIZE);
					err = 1;
				  #ifdef DEBUG_MDB
				  print_mdb("MDB-RECV[%d]:",*rlen);
				  for(i = 0;i < *rlen;i++){
					print_mdb("%02x ",rdata[i]);		
				  }
				  print_mdb("\r\n");
				  #endif
									  break;	
				case MDB_OUT_RANGE	: err = 2;
									  break;
				case MDB_CHKSUM_ERR	: err = 3;
									  break;
				default:break;
			}
			break;	
		}
		OSTimeDly(2);//10ms 延时
			
	}
	return err;	
}



/*********************************************************************************************************
** Function name:     	MdbConversation
** Descriptions:	    MDB设备通讯
** input parameters:    Dev:设备号(高5位地址及低三位命令)；
**						*SeDat:要发送的数据；
**						SenDatLen：要发送数据的长度
** output parameters:   *RevDat:接收到的数据；RevLen:接收到数据的长度；
** Returned value:      1：通讯成功：0；通讯失败；
*********************************************************************************************************/
uint8_t MdbConversation(uint8_t Dev,uint8_t *SeDat,uint8_t SenDatLen,uint8_t *RevDat,uint8_t *RevLen)
{
	unsigned char i,check = 0,err = 0;	
	unsigned char Temp;
	check = Dev;
	ClrUart2Buff();
	OSSchedLock();
	MdbPutChr(Dev,MDB_ADD);					//送出MDB地址及命令
	for(i=0;i<SenDatLen;i++)				//送出数据
	{
		MdbPutChr(SeDat[i],MDB_DAT);
		check += SeDat[i];	
	}
	MdbPutChr(check,MDB_DAT);				//送出校验和
	OSSchedUnlock();
	OSTimeDly(3);
	Timer.mdb_timeout = 100;	//进入ACK等待，超时1000ms
	while(Timer.mdb_timeout)
	{
		Temp = GetMdbStatus();
		if(Temp > MDB_RCV_DATA)
		{
			switch(Temp)
			{
				case MDB_RCV_OK		: *RevLen = Uart2GetStr(RevDat,MDB_MAX_BLOCK_SIZE);
									  err = 1;
									  break;	
				case MDB_OUT_RANGE	: err = 2;
									  break;
				case MDB_CHKSUM_ERR	: err = 3;
									  break;
				default:break;
			}
			break;	
		}
		OSTimeDly(2);
			
	}
	return err;	
}




/**************************************End Of File*******************************************************/
