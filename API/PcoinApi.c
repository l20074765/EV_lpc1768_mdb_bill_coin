#include "..\config.h"

#define	PARALLCOIN_CTL		(1ul<<29)				//P1.20并行脉冲硬币器使能线,低电平使能、高电平禁能
#define SERIALCOIN_CTL 		(1ul<<30)				//P1.21串行脉冲硬币器使能线,低电平使能、高电平禁能

#define PARALLCHL_IN		0x0000000000070103		//并行硬币器通道
#define GETPPCOIN_CHL1()	((FIO1PIN >> 10)& 0x01)	//通道1
#define GETPPCOIN_CHL2()	((FIO1PIN >> 9) & 0x01)	//通道2
#define GETPPCOIN_CHL3()	((FIO1PIN >> 8) & 0x01)	//通道3
#define GETPPCOIN_CHL4()	((FIO1PIN >> 4) & 0x01)	//通道4
#define GETPPCOIN_CHL5()	((FIO1PIN >> 1) & 0x01)	//通道5
#define GETPPCOIN_CHL6()	((FIO1PIN >> 0) & 0x01)	//通道6

#define SERIALCOIN_IN		(1ul<<11)				//串行硬币器通道P2.11
#define GETSERIALCON_CHL()	((FIO2PIN >>11) & 0x01)	//串行通道



static uint8 highEnabled = 0;
static volatile uint32 recvAmount = 0;

ST_PCOIN stPcoin;

uint8 PCOIN_setCh(uint8 no,uint32 value)
{
	if(no > 16 || no == 0){
		return 0;
	}
	stPcoin.ch[no - 1] = value;
	return 1;
	
}



uint8 PCOIN_initParallelPluse(uint8 high)
{
	FIO1DIR &= (~PARALLCHL_IN);				//设置通道为输入模式
	InitTimer(1,480000);					//20ms扫描一次并行硬币器	
	highEnabled = high;
	PCOIN_disableParallelPluse();
	return 1;
}



/*********************************************************************************************************
** Function name:       EnableParallelPluseCoinAcceptor
** Descriptions:        使能并行硬币器
** input parameters:    设置全局变量PARALLELPULSECOINACCEPTORDEVICESTATUS
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 PCOIN_enableParallelPluse(void)
{
	FIO0DIR |= (SERIALCOIN_CTL|PARALLCOIN_CTL);//P0.30 PLS_MASK
	if(highEnabled == 1){ 
		FIO0SET |= (SERIALCOIN_CTL|PARALLCOIN_CTL);
	}
	else{
		FIO0CLR |= (SERIALCOIN_CTL|PARALLCOIN_CTL);
	}
	stPcoin.isEnable = 1;
	return 1;
	
	
}
/*********************************************************************************************************
** Function name:       DisableParallelPluseCoinAcceptor
** Descriptions:        禁能并行硬币器
** input parameters:    无
** output parameters:   设置全局变量PARALLELPULSECOINACCEPTORDEVICESTATUS
** Returned value:      无
*********************************************************************************************************/
uint8 PCOIN_disableParallelPluse(void)
{
	FIO0DIR |= (SERIALCOIN_CTL|PARALLCOIN_CTL);//P0.30 PLS_MASK
	if(highEnabled == 1){
		FIO0CLR |= (SERIALCOIN_CTL|PARALLCOIN_CTL);
	}
	else{
		FIO0SET |= (SERIALCOIN_CTL|PARALLCOIN_CTL);
	}
	stPcoin.isEnable = 0;
	return 1;
}



/*********************************************************************************************************
** Function name:       PCOIN_scanParallelPluse
** Descriptions:        扫描并行硬币器通道，注意只能在Time1定时中断中扫描
** input parameters:    无
** output parameters:   
** Returned value:      无
*********************************************************************************************************/
void PCOIN_scanParallelPluse(void)
{
	uint32 Rchannel;
	uint8 CurChannel,Temp;
	static uint8 PreChannel;
	static uint8 PreStatus ;
	Rchannel  = GETPPCOIN_CHL1()<<0;
	Rchannel |= GETPPCOIN_CHL2()<<1;
	Rchannel |= GETPPCOIN_CHL3()<<2;
	Rchannel |= GETPPCOIN_CHL4()<<3;
	Rchannel |= GETPPCOIN_CHL5()<<4;
	Rchannel |= GETPPCOIN_CHL6()<<5;
	Temp = (uint8)(~Rchannel);
	Temp &= 0x3F;
	switch(Temp)
	{
		case 0x00 : if(PreStatus == 0x01){
						PreStatus = 0x00;
						Trace("PreChannel=%d recvAmount=%d\r\n",
								PreChannel,recvAmount);
						recvAmount += stPcoin.ch[PreChannel - 1];
					}
					PreChannel = 0x00;
					CurChannel = 0x00;
					break;
		case 0x01 : CurChannel = 0x06;
					break;
		case 0x02 : CurChannel = 0x05;
					break;
		case 0x04 : CurChannel = 0x04;
					break;
		case 0x08 : CurChannel = 0x03;
					break;
		case 0x10 : CurChannel = 0x02;
					break;
		case 0x20 : CurChannel = 0x01;
					break;
		default  :  CurChannel = 0x00;
					break;					
	}
	if(PreStatus == 0x00){
		if((PreChannel > 0x00)&(PreChannel == CurChannel))
			PreStatus = 0x01;
		else
			PreChannel = CurChannel;
	}
}


/*****************************************串行硬币器API**************************************************/

/*********************************************************************************************************
** Function name:       PCOIN_initSerialPluse
** Descriptions:        初始化串行行硬币器
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 PCOIN_initSerialPluse(uint8 high)
{
	FIO2DIR &= (~SERIALCOIN_IN);			//设置通道为输入模式
	InitTimer(1,480000);					//20ms扫描一次并行硬币器
	highEnabled = high;
	PCOIN_disableSerialPluse();
	return 1;
}
/*********************************************************************************************************
** Function name:       PCOIN_enableSerialPluse
** Descriptions:        使能串行硬币器
** input parameters:    设置全局变量SERIALPULSECOINACCEPTORDEVICESTATUS
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 PCOIN_enableSerialPluse(void)
{
	FIO0DIR |= (SERIALCOIN_CTL|PARALLCOIN_CTL);//P0.30 PLS_MASK
	if(highEnabled == 1){
		FIO0SET |= (SERIALCOIN_CTL|PARALLCOIN_CTL);
	}
	else{
		FIO0CLR |= (SERIALCOIN_CTL|PARALLCOIN_CTL);
	}
	stPcoin.isEnable = 1;
	return 1;
}


/*********************************************************************************************************
** Function name:       PCOIN_disableSerialPluse
** Descriptions:        使能串行硬币器
** input parameters:    设置全局变量SERIALPULSECOINACCEPTORDEVICESTATUS
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 PCOIN_disableSerialPluse(void)
{
	FIO0DIR |= (SERIALCOIN_CTL|PARALLCOIN_CTL);//P0.30 PLS_MASK
	if(highEnabled == 1){
		FIO0CLR |= (SERIALCOIN_CTL|PARALLCOIN_CTL);
	}
	else{
		FIO0SET |= (SERIALCOIN_CTL|PARALLCOIN_CTL);
	}
	stPcoin.isEnable = 1;
	return 1;
}



/*********************************************************************************************************
** Function name:       PCOIN_scanSerialPluse
** Descriptions:        扫描串行硬币器通道，注意只能在Time1定时中断中扫描
** input parameters:    无
** output parameters:   将扫描到的值送入串行脉冲硬币器专用消息队列
** Returned value:      无
*********************************************************************************************************/
void PCOIN_scanSerialPluse(void)
{
	uint8 CurStatus;
	static uint8 PreStatus ;

	FIO2DIR &= (~SERIALCOIN_IN);
	CurStatus  = (uint8)GETSERIALCON_CHL();
	switch(CurStatus)
	{					
		case 0x00 :	if(PreStatus == 0x01){
						recvAmount += stPcoin.ch[0];
					}
					PreStatus = CurStatus;
					break;
		case 0x01 : PreStatus = CurStatus;
					break;	
		default   : break;
	}
}



uint32 PCOIN_recvAmount(void)
{
	return recvAmount;
}

uint32 PCOIN_costAmount(uint32 amount)
{
	uint32 remainAmount;
	if(amount <= recvAmount){
		recvAmount -= amount;
		remainAmount = 0;
	}
	else{
		remainAmount = amount - recvAmount;
		recvAmount = 0;
	}
	return  remainAmount;

}




uint8 PCOIN_isEnable(void)
{
	return stPcoin.isEnable;
}




/**************************************End Of File*******************************************************/


