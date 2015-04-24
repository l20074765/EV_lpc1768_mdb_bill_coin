/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           lcd.h
** Last modified Date:  2012-07-22
** Last Version:         
** Descriptions:        LCD驱动程序相关函数声明                     
**------------------------------------------------------------------------------------------------------
** Created by:          sunway
** Created date:        2011-07-22
** Version:             V2.0
** Descriptions:        The original version
**------------------------------------------------------------------------------------------------------
** Modified by:         
** Modified date:       
** Version:             
** Descriptions:        
********************************************************************************************************/
#include "..\config.h"

volatile unsigned int  EVBCONVERSATIONWAITACKTIMEOUT;	//EVB通讯接收ACK超时时间
volatile unsigned int  UART3RECVACKMSGTIMEOUT;			//接收ACK数据包超时时间
volatile unsigned char EvbAckFromDevice[8];				//EVB ACK数据缓冲
/*********************************************************************************************************
** Function name:     	Uart3RecvEvbAckFromDevice
** Descriptions:	    EVB通讯，接收ACK包
** input parameters:    无
** output parameters:   无
** Returned value:      1：接收成功；0：接收失败
*********************************************************************************************************/
unsigned char Uart3RecvEvbAckFromDevice(void)
{
	unsigned char RecvData,AckIndex;
	if(Uart3BuffIsNotEmpty() == 1)
	{
		RecvData = Uart3GetCh();
		//Trace("GetCh====%x\r\n",RecvData);
		if((RecvData == 0xFD)||(RecvData == 0xEF))
		{
			AckIndex = 0;
			EvbAckFromDevice[AckIndex++] = RecvData;	
			UART3RECVACKMSGTIMEOUT = 20; 				//接收剩余字节超时时间，100ms
			while(UART3RECVACKMSGTIMEOUT)
			{
				if(Uart3BuffIsNotEmpty()==1)
				{
					EvbAckFromDevice[AckIndex++] = Uart3GetCh();
					if((AckIndex == 2)&&(EvbAckFromDevice[0]==0xfd))
					{
						if(EvbAckFromDevice[1] > 0x08)
							break;
					}
					//if((AckIndex == 0x08)||((EvbAckFromDevice[0]==0xfd)&&(AckIndex == 0x06)))
					if((AckIndex == EvbAckFromDevice[1])||((EvbAckFromDevice[0]==0xef)&&(AckIndex==0x08)))	//处理6/8字节的ACK
					{
						if(EvbAckFromDevice[0]==0xfd)
						{
							if(EvbAckFromDevice[AckIndex-1] == XorCheck((unsigned char *)EvbAckFromDevice,(EvbAckFromDevice[1]-1)))
								return 1;
							else
								break;
						}
						else
						{
							if(EvbAckFromDevice[AckIndex-1] == XorCheck((unsigned char *)EvbAckFromDevice,7))
							{
								return 1;
							}
							else
							{
								break;
							}	
						}
					}
				}
			}
		}
		return 0;
	}
	return 0;
}


/*********************************************************************************************************
** Function name:     	EvbConversation
** Descriptions:	    EVB通讯
** input parameters:    Chl:选择通道；Head:包头；Sn：序列号；Type:消息类别；Addr:设备地址;Data：数据；
** output parameters:   *ACK：应答包
** Returned value:      1：收到应答；0：未收到应答即通讯失败
*********************************************************************************************************/
uint8_t EvbConversation(uint8_t Chl,uint8_t Head,uint8_t Sn,uint8_t Type,uint8_t Addr,uint16_t Data,uint8_t *Ack)
{
	unsigned char i,EvbSendBuff[8];

	i = Chl;//目前未用，防警告
	EvbSendBuff[0] = Head;
	EvbSendBuff[1] = 0x08;
	if((Chl==1)&&(Type==0x71))
		Sn = 0x00;
	EvbSendBuff[2] = Sn;
	EvbSendBuff[3] = Type;
	EvbSendBuff[4] = Addr;
	if(Chl == 1)
	{
		EvbSendBuff[5] = (unsigned char)(Data>>8);//0x07;
		EvbSendBuff[6] = (unsigned char)Data;//0x00;
	}
	else
	{
		EvbSendBuff[5] = (unsigned char)Data;//0x08;
		EvbSendBuff[6] = (unsigned char)(Data>>8);//0x00;
	}	
	EvbSendBuff[7] = XorCheck(EvbSendBuff,7);

	//发送数据禁止切换任务
	OSSchedLock();
	Uart3PutStr(EvbSendBuff,8);
	OSSchedUnlock();
	
	if(Type>=0x70)
		Trace("Send=%02x %02x %02x %02x %02x %02x %02x %02x\r\n",EvbSendBuff[0],EvbSendBuff[1],EvbSendBuff[2],EvbSendBuff[3],EvbSendBuff[4],EvbSendBuff[5],EvbSendBuff[6],EvbSendBuff[7]);
	if(Type>=0x70)
		EVBCONVERSATIONWAITACKTIMEOUT = 500;
	else
		EVBCONVERSATIONWAITACKTIMEOUT = 100;
	while(EVBCONVERSATIONWAITACKTIMEOUT)			//1000ms内收到ACK,否则超时
	{
		//Trace("TimeOut...%d\r\n",EVBCONVERSATIONWAITACKTIMEOUT);
		if(Uart3RecvEvbAckFromDevice() == 1)
		{
			if(Type>=0x70)
				Trace("Recv1=%02x %02x %02x %02x %02x %02x %02x %02x\r\n",EvbAckFromDevice[0],EvbAckFromDevice[1],EvbAckFromDevice[2],EvbAckFromDevice[3],EvbAckFromDevice[4],EvbAckFromDevice[5],EvbAckFromDevice[6],EvbAckFromDevice[7]);
			
			for(i=0;i<8;i++)
			{
				*Ack++ = EvbAckFromDevice[i];
			}
			
			//SetUart2MdbMode();
			return 1;
		}

		OSTimeDly(2);
	}
	//Trace("Fail..\r\n");
	//SetUart2MdbMode();
	return 0;
}
/**************************************End Of File*******************************************************/
