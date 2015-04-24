#include "../config.h"



#define DB_BUF_SIZE		64
static uint8 xdata recvbuf[DB_BUF_SIZE] = {0};//接收缓存区
static uint8 xdata sendbuf[DB_BUF_SIZE] = {0};
static uint8 xdata sn = 0;
static uint8 xdata mdb_addr = 0x31;
ST_MDB xdata stMdb;




/*********************************************************************************************************
** Function name:     	xorCheck
** Descriptions:	    
** input parameters:    
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
static uint8 xorCheck(uint8 *ptr,uint8 len)
{
	uint8  i,crc = 0;
	for(i = 0;i < len;i++)
		crc ^= ptr[i];
		
	return crc;	
}

/*********************************************************************************************************
** Function name:     pcEncodAmount
** Descriptions:      ?32???????????
** input parameters:    
** output parameters:   ?
** Returned value:      
*********************************************************************************************************/
static uint8 pcEncodAmount(uint32 amount)
{

	uint8 i = 0,value;
	if(amount == 0)
		return 0;
	while(!(amount % 10)){
		amount = amount / 10;
		i++;
	}
	switch(amount){
		case 1: 	value = 1;	break;		
		case 2: 	value = 2;	break;	
		case 5: 	value = 5;	break;
		default: 	value = 0;	break;		
	}
	if(value){
		value = (i << 4) | (value & 0x0f);
		return value;
	}
	else
		return 0;

}


#if 0
/*********************************************************************************************************
** Function name:     pcAnalysisAmount
** Descriptions:      ?????????32???
** input parameters:    
** output parameters:   ?
** Returned value:     
*********************************************************************************************************/
static unsigned int pcAnalysisAmount(unsigned char data)
{

	unsigned int amount;
	unsigned char uint;
	if(data == 0)
		return 0;
	uint =  data >> 4;
	amount = data & 0x0f;	
	while(uint)
	{
		amount = amount * 10;
		uint--;
	}
	return amount;
}
#endif


uint32 MDB_payout(uint32 payAmount)
{
	uint32 xdata changedAmount;
	coin_enable(0);
	bill_enable(0);
	msleep(100);
	changedAmount = coinPayout(payAmount);
	msleep(100);
	coin_enable(1);
	bill_enable(1);
	return changedAmount;
}


/*********************************************************************************************************
** Function name:     	DB_package
** Descriptions:	    驱动板数据组包
** input parameters:   mt 发送类型 len 发送数据长度
** output parameters:   无
** Returned value:      1成功  0失败
*********************************************************************************************************/
void DB_package(uint8 mt,uint8 len)
{
	sendbuf[SF] = HEAD_DB;
	sendbuf[LEN] = len;
	sendbuf[ADDR] = mdb_addr;
	sendbuf[SN] = sn;
	sendbuf[MT] = mt;
	sendbuf[len] = xorCheck(sendbuf,len);
}

/*********************************************************************************************************
** Function name:     	DB_uart1Send
** Descriptions:	    驱动板往串口1发送数据接口
** input parameters:    无
** output parameters:   无
** Returned value:      1成功  0失败
*********************************************************************************************************/
void DB_uart1Send(void)
{
	ClrUart0Buff();
	Uart0PutStr(sendbuf,sendbuf[LEN] + 1);
}




/*********************************************************************************************************
** Function name:     	DB_uart1Recv
** Descriptions:	      串口1数据接收函数
** input parameters:    无
** output parameters:   无
** Returned value:      0 无数据接收 1接收正确数据  2接收数据错误 3超时
*********************************************************************************************************/
uint8 DB_uart1Recv(void)
{
	uint8 xdata ch,index = 0,len = MT;
	uint8 xdata crc;
	if(!Uart0BuffIsNotEmpty()){
		return 0;
	}
	
	memset(recvbuf,0,sizeof(recvbuf));
	Timer.db_recv_timeout = 20;
	while(Timer.db_recv_timeout){
		if(Uart0BuffIsNotEmpty()){
			ch = Uart0GetCh();
			recvbuf[index++] = ch;
			if(index == (SF + 1)){
				if(ch != HEAD_PC ) {
					return 0;
				}
			}
			else if(index == (LEN + 1)){
				len = ch;
			}		
			else if(index >= (len + 1)){
				break;
			}
		}
	}
	
	if(!Timer.db_recv_timeout){
		return 3;
	}
	crc = xorCheck(recvbuf,len);
	if(crc != recvbuf[len]){
		return 2;
	}
	else{
		return 1;//正确接收包
	}
	
}




static void DB_addrRpt(void)
{
	sendbuf[MT + 1] = 0x01;
	DB_package(0x75,MT + 2);
	//DB_writeFlash();
	DB_uart1Send();
}


/*********************************************************************************************************
** Function name:     	DB_control_rpt
** Descriptions:	      控制设备
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

static void DB_control_rpt(void)
{
	uint8 temp,temp1;
	sendbuf[MT + 1] = recvbuf[MT + 1];
	sendbuf[MT + 2] = recvbuf[MT + 2];
	temp = recvbuf[MT + 2];
	if(temp & OBJ_BILL){
		temp1 = recvbuf[MT + 3];
		if(temp1 == 1){
			sendbuf[MT + 3] = bill_enable(1);
		}
		else{
			sendbuf[MT + 3] = bill_enable(0);
		}			
	}
	if(temp & OBJ_COIN){
		temp1 = recvbuf[MT + 3];
		if(temp1 == 1){
			sendbuf[MT + 4] = coin_enable(1);
		}
		else{
			sendbuf[MT + 4] = coin_enable(0);
		}	
	}
	DB_package(DB_MT_ACTION_RPT,MT + 5);
	DB_uart1Send();

}


/*********************************************************************************************************
** Function name:     	DB_check_rpt
** Descriptions:	      查询上报
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/

static void DB_check_rpt()
{	
	uint8 index = MT + 1;
	uint16 temp;
	uint32 temp32;
	sendbuf[index++] = MDB_CHECK_RPT;
	sendbuf[index++] = stBill.s.status;
	temp = stBill.s.errNo;
	sendbuf[index++] = HUINT16(temp);
	sendbuf[index++] = LUINT16(temp);

	temp32 = stBill.amount.recvAmount;
	sendbuf[index++] = H0UINT32(temp32);
	sendbuf[index++] = H1UINT32(temp32);
	sendbuf[index++] = L0UINT32(temp32);
	sendbuf[index++] = L1UINT32(temp32);
	
	temp32 = stBill.amount.oneAmount;
	sendbuf[index++] = H0UINT32(temp32);
	sendbuf[index++] = H1UINT32(temp32);
	sendbuf[index++] = L0UINT32(temp32);
	sendbuf[index++] = L1UINT32(temp32);
	
	//硬币器
	sendbuf[index++] = stCoin.state.s;
	temp = stCoin.state.err;
	sendbuf[index++] = HUINT16(temp);
	sendbuf[index++] = LUINT16(temp);
	
	temp32 = stCoin.amount.recvAmount;
	sendbuf[index++] = H0UINT32(temp32);
	sendbuf[index++] = H1UINT32(temp32);
	sendbuf[index++] = L0UINT32(temp32);
	sendbuf[index++] = L1UINT32(temp32);
	
	
	
	temp32 = stCoin.amount.remainAmount;
	sendbuf[index++] = H0UINT32(temp32);
	sendbuf[index++] = H1UINT32(temp32);
	sendbuf[index++] = L0UINT32(temp32);
	sendbuf[index++] = L1UINT32(temp32);
	
	stBill.amount.oneAmount = 0;
	stCoin.amount.oneAmount = 0;
	DB_package(DB_MT_CHECK_RPT,index);
	DB_uart1Send();
	
	
	//上报后清除 退币指令
	stCoin.state.s &= ~COIN_BIT_PAYBACK;
	stBill.s.status &= ~BILL_BIT_PAYBACK;
}

/*********************************************************************************************************
** Function name:     	DB_bill_info_rpt
** Descriptions:	      
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
static void DB_bill_info_rpt()
{	
	uint8 index = MT + 1,i;
	sendbuf[index++] = MDB_BILL_INFO_RPT;
	sendbuf[index++] = stMdb.billType;
	
	for(i = 0;i < 12;i++){
		sendbuf[index++] = (uint8)stBill.identifict.sn[i];
	}
	
	sendbuf[index++] = stBill.identifict.softwareVersion[0];
	sendbuf[index++] = stBill.identifict.softwareVersion[1];
	
	sendbuf[index++] = stBill.setup.escrowFun;
	sendbuf[index++] = HUINT16(stBill.setup.stkCapacity);
	sendbuf[index++] = LUINT16(stBill.setup.stkCapacity);
	
	for(i = 0;i < 16;i++){
		sendbuf[index++] = pcEncodAmount(stBill.setup.channel[i]);
	}
	DB_package(DB_MT_CHECK_RPT,index);
	DB_uart1Send();
}

/*********************************************************************************************************
** Function name:     	DB_coin_info_rpt
** Descriptions:	      
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
static void DB_coin_info_rpt()
{	
	uint8 index = MT + 1,i;
	sendbuf[index++] = MDB_COIN_INFO_RPT;
	sendbuf[index++] = stMdb.coinType;
	
	for(i = 0;i < 12;i++){
		sendbuf[index++] = (uint8)stCoin.identifict.sn[i];
	}	
	sendbuf[index++] = stCoin.identifict.softwareVersion[0];
	sendbuf[index++] = stCoin.identifict.softwareVersion[1];
	for(i = 0;i < 16;i++){
		sendbuf[index++] = pcEncodAmount(stCoin.tube.ch[i]);
	}
	for(i = 0;i < 16;i++){
		sendbuf[index++] = stCoin.tube.num[i];
	}
	DB_package(DB_MT_CHECK_RPT,index);
	DB_uart1Send();
}



/*********************************************************************************************************
** Function name:     	DB_init_rpt
** Descriptions:	      
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
static void DB_init_rpt()
{	
	uint8 temp;
	sendbuf[MT + 1] = recvbuf[MT + 1];
	sendbuf[MT + 2] = recvbuf[MT + 2];
	sendbuf[MT + 3] = 0;
	sendbuf[MT + 4] = 0;
	temp = recvbuf[MT + 2];
	if(temp & OBJ_BILL){
		stMdb.billType = recvbuf[MT + 3];
		if(stMdb.billType == 2){
			sendbuf[MT + 3] = billInit();
		}
		else if(stMdb.billType == 0){ //关纸币器 直接返回成功
			sendbuf[MT + 3] = 1;
		}	
		else{
			sendbuf[MT + 3] = 0;
		}		
	}
	if(temp & OBJ_COIN){
		stMdb.coinType = recvbuf[MT + 4];
		if(stMdb.coinType == 2){
			sendbuf[MT + 4] = coinInit();
		}
		else if(stMdb.coinType == 0){//关硬币器 直接返回成功
			sendbuf[MT + 4] = 1;
		}	
		else{
			sendbuf[MT + 4] = 0;
		}
	}
	
	DB_package(DB_MT_ACTION_RPT,MT + 5);
	DB_uart1Send();
}

static void DB_cost_rpt(void)
{
	uint8 temp;
	uint32 costAmount = 0,temp32;
	memset(sendbuf,0,sizeof(sendbuf));
	sendbuf[MT + 1] = recvbuf[MT + 1];
	sendbuf[MT + 2] = recvbuf[MT + 2];
	
	temp = recvbuf[MT + 2] ;
	temp = temp;
	costAmount = INTEG32(recvbuf[MT + 3],recvbuf[MT + 4],
						recvbuf[MT + 5],recvbuf[MT + 6]);
	if(stBill.amount.recvAmount >= costAmount){
		stBill.amount.recvAmount -= costAmount;
	}
	else{
		costAmount -= stBill.amount.recvAmount;
		if(stCoin.amount.recvAmount >= costAmount){
			stCoin.amount.recvAmount -=  costAmount;
		}
		else{
			stCoin.amount.recvAmount = 0;
		}		
		stBill.amount.recvAmount = 0;
	}
	
	//billamount
	temp32 = stBill.amount.recvAmount;
	sendbuf[MT + 3] = H0UINT32(temp32);
	sendbuf[MT + 4] = H1UINT32(temp32);
	sendbuf[MT + 5] = L0UINT32(temp32);
	sendbuf[MT + 6] = L1UINT32(temp32);
	
	//coinAmount
	temp32 = stCoin.amount.recvAmount;
	sendbuf[MT + 7] = H0UINT32(temp32);
	sendbuf[MT + 8] = H1UINT32(temp32);
	sendbuf[MT + 9] = L0UINT32(temp32);
	sendbuf[MT + 10] = L1UINT32(temp32);
	DB_package(DB_MT_ACTION_RPT,MT + 11);
	DB_uart1Send();
}


static void DB_payback_rpt(void)
{	
	uint8 temp;
	uint32 payAmount = 0,changedAmount;
	memset(sendbuf,0,sizeof(sendbuf));
	sendbuf[MT + 1] = recvbuf[MT + 1];
	sendbuf[MT + 2] = recvbuf[MT + 2];
	
	//billchanged
	sendbuf[MT + 3] = 0;
	sendbuf[MT + 4] = 0;
	sendbuf[MT + 5] = 0;
	sendbuf[MT + 6] = 0;
	
	temp = recvbuf[MT + 2];
	if(temp & OBJ_COIN){
		payAmount = stBill.amount.recvAmount + stCoin.amount.recvAmount;
		changedAmount = MDB_payout(payAmount);
		sendbuf[MT + 7] = H0UINT32(changedAmount);
		sendbuf[MT + 8] = H1UINT32(changedAmount);
		sendbuf[MT + 9] = L0UINT32(changedAmount);
		sendbuf[MT + 10] = L1UINT32(changedAmount);
		
		stBill.amount.recvAmount = 0;
		stCoin.amount.recvAmount = 0;
	}
	DB_package(DB_MT_ACTION_RPT,MT + 11);
	DB_uart1Send();
}

static void DB_payout_rpt(void)
{
	uint8 temp;
	uint32 payAmount = 0,changedAmount,temp32;
	memset(sendbuf,0,sizeof(sendbuf));
	sendbuf[MT + 1] = recvbuf[MT + 1];
	sendbuf[MT + 2] = recvbuf[MT + 2];
	
	//billchanged
	sendbuf[MT + 3] = 0;
	sendbuf[MT + 4] = 0;
	sendbuf[MT + 5] = 0;
	sendbuf[MT + 6] = 0;
	
	
	
	temp = recvbuf[MT + 2];
	if(temp & OBJ_COIN){
		payAmount = INTEG32(recvbuf[MT + 7],recvbuf[MT + 8],
						recvbuf[MT + 9],recvbuf[MT + 10]);
		changedAmount = MDB_payout(payAmount);
		//coinchanged
		sendbuf[MT + 7] = H0UINT32(changedAmount);
		sendbuf[MT + 8] = H1UINT32(changedAmount);
		sendbuf[MT + 9] = L0UINT32(changedAmount);
		sendbuf[MT + 10] = L1UINT32(changedAmount);
	}
	
	//billamount
	temp32 = stBill.amount.recvAmount;
	sendbuf[MT + 11] = H0UINT32(temp32);
	sendbuf[MT + 12] = H1UINT32(temp32);
	sendbuf[MT + 13] = L0UINT32(temp32);
	sendbuf[MT + 14] = L1UINT32(temp32);
	
	//coinAmount
	temp32 = stCoin.amount.recvAmount;
	sendbuf[MT + 15] = H0UINT32(temp32);
	sendbuf[MT + 16] = H1UINT32(temp32);
	sendbuf[MT + 17] = L0UINT32(temp32);
	sendbuf[MT + 18] = L1UINT32(temp32);
	DB_package(DB_MT_ACTION_RPT,MT + 19);
	DB_uart1Send();
}


/*********************************************************************************************************
** Function name:     	DB_info_rpt
** Descriptions:	      
** input parameters:    ?
** output parameters:   ?
** Returned value:      ?
*********************************************************************************************************/
static void DB_info_rpt()
{
	uint8 index = MT + 1,i;
	uint8 xdata id[20];
	//DB_readFlashId(id);
	
	for(i = 0;i < 20;i++){
		sendbuf[index++] = id[i];
	}
	//?????  1001
	sendbuf[index++] = 0x10;
	sendbuf[index++] = 0x01;
	
	sendbuf[index++] = 0;
	sendbuf[index++] = 0;
	sendbuf[index++] = 0;
	sendbuf[index++] = 0;
	
	DB_package(DB_MT_CHECK_RPT,index);
	DB_uart1Send();
}


static void DB_idSetRpt(void)
{
	uint8 index = MT + 1,i;
	uint8 xdata id[20] = {0};
	for(i = 0;i < 20;i++){
		id[i] = recvbuf[index++];
	}
//	DB_writeFlashId(id);
	sendbuf[MT + 1] = 0x01;
	DB_package(0x75,MT + 2);
	DB_uart1Send();

}

/*********************************************************************************************************
** Function name:     	DB_task
** Descriptions:	      通信协议主函数
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 DB_task(void)
{
	uint8 type;
	if(DB_uart1Recv() != 1){
		return 0;
	}
	if(recvbuf[ADDR] == 0xFF){
		if(recvbuf[SN] == sn && sn != 0){
			DB_uart1Send();	
			return 1;
		}
		sn = recvbuf[SN];
		switch(recvbuf[MT]){
			case DB_MT_CON_REQ:	DB_addrRpt();	break;
			case DB_MT_ID_REQ:	DB_idSetRpt();	break;
			default:break;		
		}		
	}
	else if(recvbuf[ADDR] == mdb_addr){
		if(recvbuf[SN] == sn && sn != 0){
			DB_uart1Send();	
			return 1;
		}
		sn = recvbuf[SN];
		type = recvbuf[MT + 1];
		if(recvbuf[MT] == DB_MT_CHECK_REQ)
		{
			switch(type){
				case MDB_CHECK_REQ:		DB_check_rpt();		break;
				case MDB_BILL_INFO_REQ:	DB_bill_info_rpt();	break;
				case MDB_COIN_INFO_REQ:	DB_coin_info_rpt();	break;
				case MDB_INFO_REQ:		DB_info_rpt();		break;
				default:	break;
			}	
		}
		else if(recvbuf[MT] == DB_MT_ACTION_REQ)
		{
			switch(type){
				case MDB_INIT_REQ:		DB_init_rpt();		break;
				case MDB_CONTROL_REQ:	DB_control_rpt();	break;
				case MDB_PAYBACK_REQ:	DB_payback_rpt();	break;
				case MDB_COST_REQ:		DB_cost_rpt();		break;
				case MDB_PAYOUT_REQ:	DB_payout_rpt();	break;
				default:	break;
			}	
		}
		else{
			return 1;
		}
	}
	else{
		return 2;
	}
	return 1;
	
}









