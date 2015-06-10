#include "../config.h"


#define DEBUG_PC

#ifdef 	DEBUG_PC
#define print_pc(...)	Trace(__VA_ARGS__)
#else
#define print_pc(...)
#endif


#define DB_BUF_SIZE		128
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


/*********************************************************************************************************
** Function name:     pcAnalysisAmount
** Descriptions:      ?????????32???
** input parameters:    
** output parameters:   ?
** Returned value:     
*********************************************************************************************************/
static uint32 pcAnalysisAmount(uint8 data)
{

	uint32 amount;
	uint8 uint;
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



void MDB_setBillAcceptor(uint8 type)
{
	stMdb.bill_type &= ~0x0F;
	stMdb.bill_type |= (type & 0x0F);
}


void MDB_setBillDispenser(uint8 type)
{
	stMdb.bill_type &= ~(0x0F << 4);
	stMdb.bill_type |= ((type & 0x0F) << 4);
}


void MDB_setCoinAcceptor(uint8 type)
{
	stMdb.coin_type &= ~0x0F;
	stMdb.coin_type |= (type & 0x0F);
}


void MDB_setCoinDispenser(uint8 type)
{
	stMdb.coin_type &= ~(0x0F << 4);
	stMdb.coin_type |= ((type & 0x0F) << 4);
}

	

uint8 MDB_getBillAcceptor(void)
{
	return (stMdb.bill_type & 0x0F);
}


uint8 MDB_getBillDispenser(void)
{
	return ((stMdb.bill_type >> 4) & 0x0F);
}

uint8 MDB_getCoinAcceptor(void)
{
	return (stMdb.coin_type & 0x0F);
}


uint8 MDB_getCoinDispenser(void)
{
	return ((stMdb.coin_type >> 4) & 0x0F);
}



uint8 MDB_billEnable(uint8 en)
{
	if(MDB_getBillAcceptor() == BILL_ACCEPTOR_MDB){
		return bill_enable(en);
	}
	
	return 1;
}


uint8 MDB_coinEnable(uint8 en)
{
	uint8 res;
	if(MDB_getCoinAcceptor() == COIN_ACCEPTOR_MDB){
		res = coin_enable(en);
	}
	else if(MDB_getCoinAcceptor() == COIN_ACCEPTOR_PPLUSE){
		if(en == 1){
			res = PCOIN_enableParallelPluse();
		}
		else{
			res = PCOIN_disableParallelPluse();
		}
	}
	else if(MDB_getCoinAcceptor() == COIN_ACCEPTOR_SPLUSE){
		if(en == 1){
			res = PCOIN_enableSerialPluse();
		}
		else{
			res = PCOIN_disableSerialPluse();
		}
	}
	
	return res;
	
}

uint8 MDB_billInit(void)
{
	uint8 type,res = 0;
	type = MDB_getBillAcceptor();
	if(type == BILL_ACCEPTOR_MDB){
		stBill.s.status |= BILL_BIT_FAULT;
		stBill.s.errNo |= BILL_ERR_COM;
		res = billInit();
		if(res == 1){
			stBill.s.status &= ~BILL_BIT_FAULT;
			stBill.s.errNo = 0;
		}
	}
	else{
		res = 0;
	}
	return res;	
}

uint8 MDB_coinInit(void)
{
	uint8 type,res = 0;
	type = MDB_getCoinAcceptor();
	if(type == COIN_ACCEPTOR_MDB){
		stCoin.state.s |= COIN_BIT_FAULT;
		stCoin.state.err |= COIN_ERR_COM;
		res = coinInit();
		if(res == 1){
			stCoin.state.s &= ~COIN_BIT_FAULT;
			stCoin.state.err = 0;
		}
	}
	else if(type == COIN_ACCEPTOR_PPLUSE){
		PCOIN_initParallelPluse(stMdb.highEnable);
		res = 1;
	}
	else if(type == COIN_ACCEPTOR_SPLUSE){
		PCOIN_initSerialPluse(stMdb.highEnable);
		res = 1;
	}
	
	type = MDB_getCoinDispenser();
	if(type == COIN_DISPENSER_HOPPER){
		HP_init();
		res = 1;
	}
	
	
	
	return res;
}



//硬币找零
uint32 MDB_coin_payout(uint32 payAmount)
{
	uint8 type,c_enable,b_enable;
	uint32 xdata changedAmount;
	if(payAmount == 0){
		return 0;
	}

	changedAmount = 0;
	
	if(stBill.s.status & BILL_BIT_DISABLE){
		b_enable = 0;
	}
	else{
		b_enable = 1;
		MDB_billEnable(0);
	}
	
	if(stCoin.state.s & COIN_BIT_DISABLE){
		c_enable = 0;
	}
	else{
		c_enable = 1;
		MDB_coinEnable(0);
	}
	
	msleep(100);
	
	type = MDB_getCoinDispenser();
	if(type == COIN_DISPENSER_MDB){
		changedAmount = coinPayout(payAmount);
	}
	else if(type == COIN_DISPENSER_HOPPER){
		changedAmount = HP_payout(payAmount);
	}
	else{
		changedAmount = 0;
	}
	
	msleep(100);
	
	if(c_enable == 1){
		MDB_coinEnable(1);
	}
	
	if(b_enable == 1){
		MDB_billEnable(1);
	}

	return changedAmount;
}



uint32 MDB_bill_payout(uint32 payAmount)
{
	uint32 xdata changedAmount,payout_amount;
	uint8 i,b_enable = 0,c_enable = 0;
	uint16 j,count;
	uint32 ch;
	if(payAmount == 0){
		return 0;
	}
	
	if(stBill.setup.isRecycler == 0){
		return 0;
	}
	
	//校正找零金额
	payout_amount = 0;
	for(i = 0;i < 16;i++){
		ch = stBill.recycler.ch[i];
		count = stBill.recycler.ch_count[i];
		if(ch > 0 && count > 0){
			//该通道可以找零
			for(j = 0;j < count;j++){
				payout_amount += ch;
				if(payout_amount > payAmount){ //已经超出找零金额					
					break;
				}
			}
			if(payout_amount > payAmount){
				payout_amount -= ch;
				break;
			}
		}
	}
	
	if(payout_amount == 0){
		return 0;
	}
	
	if(stBill.s.status & BILL_BIT_DISABLE){
		b_enable = 0;
	}
	else{
		b_enable = 1;
		MDB_billEnable(0);
	}
	
	if(stCoin.state.s & COIN_BIT_DISABLE){
		c_enable = 0;
	}
	else{
		c_enable = 1;
		MDB_coinEnable(0);
	}
	
	msleep(100);
	changedAmount = bill_recycler_payout_by_value(payout_amount);
	msleep(100);
	if(c_enable == 1){
		MDB_coinEnable(1);
	}
	
	if(b_enable == 1){
		MDB_billEnable(1);
	}
	
	
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
	//ClrUart0Buff();
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
	return uart0_getCmd(recvbuf);
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
			sendbuf[MT + 3] = MDB_billEnable(1);
		}
		else{
			sendbuf[MT + 3] = MDB_billEnable(0);
		}			
	}
	if(temp & OBJ_COIN){
		temp1 = recvbuf[MT + 3];
		if(temp1 == 1){
			sendbuf[MT + 4] = MDB_coinEnable(1);
		}
		else{
			sendbuf[MT + 4] = MDB_coinEnable(0);
		}	
	}
	DB_package(DB_MT_ACTION_RPT,MT + 5);
	DB_uart1Send();

}


static uint8 MDB_getBillStatus(void)
{
	uint8 s;
	uint8 temp = MDB_getBillAcceptor();
	if(temp == BILL_ACCEPTOR_MDB){
		s = stBill.s.status;
		stBill.s.status &= ~BILL_BIT_PAYBACK;//上报后清除 退币指令
		return s;
	}
	else{
		return 0;
	}
}

static uint16 MDB_getBillErrNo(void)
{
	uint8 temp = MDB_getBillAcceptor();
	if(temp == BILL_ACCEPTOR_MDB){
		return stBill.s.errNo;
	}
	else{
		return 0;
	}
}


static uint8 MDB_getCoinStatus(void)
{
	uint8 s = 0;
	uint8 temp = MDB_getCoinAcceptor();
	if(temp == COIN_ACCEPTOR_MDB){
		s = stCoin.state.s;
		stCoin.state.s &= ~COIN_BIT_PAYBACK;//上报后清除 退币指令
	}
	else{
		temp = MDB_getCoinAcceptor();
		if(temp == COIN_ACCEPTOR_PPLUSE || temp == COIN_ACCEPTOR_SPLUSE){
			if(PCOIN_isEnable() == 1){
				s &= ~COIN_BIT_DISABLE;
			}
			else{
				s |= COIN_BIT_DISABLE;
			}
		}
		
		temp = MDB_getCoinDispenser();
		if(temp == COIN_DISPENSER_HOPPER){ //hopper标志
			s |= COIN_BIT_HOPPER;
		}

	}
	return s;
}

static uint16 MDB_getCoinErrNo(void)
{
	uint8 temp = MDB_getCoinAcceptor();
	uint8 i;
	uint16 errNo = 0;
	if(temp == COIN_ACCEPTOR_MDB){
		errNo = stCoin.state.err;	 
	}
	else{
		temp = MDB_getCoinDispenser();
		if(temp == COIN_DISPENSER_HOPPER){
			errNo = 0;
			for(i = 0;i < HP_SUM;i++){
				errNo |= (stHopper[i].state << i*2);
			}
		}
		else{
			errNo = 0;
		}
	}
	return errNo;
}

static uint32 MDB_getBillRecvAmount(void)
{
	uint8 temp = MDB_getBillAcceptor();
	if(temp == BILL_ACCEPTOR_MDB){
		return stBill.amount.recv_amount;
	}
	else{
		return 0;
	}
}

static uint32 MDB_getBillRemainAmount(void)
{
	uint8 temp = MDB_getBillDispenser();
	if(temp == BILL_DISPENSER_MDB){
		return stBill.amount.remain_amount;
	}
	else{
		return 0;
	}
}


static uint32 MDB_getCoinRecvAmount(void)
{
	uint8 temp = MDB_getCoinAcceptor();
	if(temp == COIN_ACCEPTOR_MDB){
		return stCoin.amount.recv_amount;
	}
	else if(temp == COIN_ACCEPTOR_PPLUSE){
		return PCOIN_recvAmount();
	}
	else if(temp == COIN_ACCEPTOR_SPLUSE){
		return PCOIN_recvAmount();
	}
	else{
		return 0;
	}
}

static uint32 MDB_getCoinRemainAmount(void)
{
	uint8 temp = MDB_getCoinDispenser();
	if(temp == COIN_DISPENSER_MDB){
		return stCoin.amount.remain_amount;	
	}
	else{
		return 0;
	}
}


static uint32 MDB_coinCost(uint32 amount)
{
	uint8 temp = MDB_getCoinAcceptor();
	uint32 reaminAmount = 0;
	if(temp == COIN_ACCEPTOR_MDB){
		if(amount <= stCoin.amount.recv_amount){
			stCoin.amount.recv_amount -= amount;
			reaminAmount = 0;
		}
		else{
			reaminAmount = amount - stCoin.amount.recv_amount;
			stCoin.amount.recv_amount = 0;
		}
	}
	else if(temp == COIN_ACCEPTOR_PPLUSE){
		reaminAmount = PCOIN_costAmount(amount);
	}
	else if(temp == COIN_ACCEPTOR_SPLUSE){
		reaminAmount = PCOIN_costAmount(amount);
	}
	else{
		reaminAmount = amount;
	}
	
	return reaminAmount;
}

static uint32 MDB_billCost(uint32 amount)
{
	uint8 temp = MDB_getBillAcceptor();
	uint32 remainAmount = 0;
	if(temp == BILL_ACCEPTOR_MDB){
		if(amount <= stBill.amount.recv_amount){
			stBill.amount.recv_amount -= amount;
			remainAmount = 0;
		}	
		else{
			remainAmount = amount - stBill.amount.recv_amount;
			stBill.amount.recv_amount = 0;
		}
			
	}
	else{
		remainAmount = amount;
	}
	
	return remainAmount;
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
	sendbuf[index++] = MDB_getBillStatus();
	temp = MDB_getBillErrNo();
	sendbuf[index++] = HUINT16(temp);
	sendbuf[index++] = LUINT16(temp);

	temp32 = MDB_getBillRecvAmount();
	sendbuf[index++] = H0UINT32(temp32);
	sendbuf[index++] = H1UINT32(temp32);
	sendbuf[index++] = L0UINT32(temp32);
	sendbuf[index++] = L1UINT32(temp32);
	
	temp32 = MDB_getBillRemainAmount();
	sendbuf[index++] = H0UINT32(temp32);
	sendbuf[index++] = H1UINT32(temp32);
	sendbuf[index++] = L0UINT32(temp32);
	sendbuf[index++] = L1UINT32(temp32);
	
	//硬币器
	sendbuf[index++] = MDB_getCoinStatus();
	temp = MDB_getCoinErrNo();
	sendbuf[index++] = HUINT16(temp);
	sendbuf[index++] = LUINT16(temp);
	
	temp32 = MDB_getCoinRecvAmount();
	sendbuf[index++] = H0UINT32(temp32);
	sendbuf[index++] = H1UINT32(temp32);
	sendbuf[index++] = L0UINT32(temp32);
	sendbuf[index++] = L1UINT32(temp32);
	
	temp32 = MDB_getCoinRemainAmount();
	sendbuf[index++] = H0UINT32(temp32);
	sendbuf[index++] = H1UINT32(temp32);
	sendbuf[index++] = L0UINT32(temp32);
	sendbuf[index++] = L1UINT32(temp32);
	
	
	DB_package(DB_MT_CHECK_RPT,index);
	DB_uart1Send();
	
	
	
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
	sendbuf[index++] = stMdb.bill_type;
	
	if(MDB_getBillAcceptor() == BILL_ACCEPTOR_MDB){
		//code
		for(i = 0;i < 3;i++){
			sendbuf[index++] = (uint8)stBill.id.manuCode[i];
		}
		//sn
		for(i = 0;i < 12;i++){
			sendbuf[index++] = (uint8)stBill.id.sn[i];
		}
		//mode
		for(i = 0;i < 12;i++){
			sendbuf[index++] = (uint8)stBill.id.model[i];
		}
		//ver
		sendbuf[index++] = stBill.id.softVer[0];
		sendbuf[index++] = stBill.id.softVer[1];
		//capacity
		sendbuf[index++] = HUINT16(stBill.setup.stkCapacity);
		sendbuf[index++] = LUINT16(stBill.setup.stkCapacity);
		//ch_r
		for(i = 0;i < 16;i++){
			sendbuf[index++] = pcEncodAmount(stBill.setup.ch[i]);
		}
		//ch_d
		for(i = 0;i < 16;i++){
			sendbuf[index++] = pcEncodAmount(stBill.recycler.ch[i]);
		}
	}
	else{
		//code
		for(i = 0;i < 3;i++){
			sendbuf[index++] = 0;
		}
		//sn
		for(i = 0;i < 12;i++){
			sendbuf[index++] = 0;
		}
		//mode
		for(i = 0;i < 12;i++){
			sendbuf[index++] = 0;
		}
		//ver
		sendbuf[index++] = 0;
		sendbuf[index++] = 0;
		//capacity
		sendbuf[index++] = 0;
		sendbuf[index++] = 0;
		//ch_r
		for(i = 0;i < 16;i++){
			sendbuf[index++] = 0;
		}
		//ch_d
		for(i = 0;i < 16;i++){
			sendbuf[index++] = 0;
		}
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
	sendbuf[index++] = stMdb.coin_type;
	
	if(MDB_getCoinAcceptor() == COIN_ACCEPTOR_MDB){
		//code
		for(i = 0;i < 3;i++){
			sendbuf[index++] = (uint8)stCoin.identifict.manufacturerCode[i];
		}
		//sn
		for(i = 0;i < 12;i++){
			sendbuf[index++] = (uint8)stCoin.identifict.sn[i];
		}
		//model
		for(i = 0;i < 12;i++){
			sendbuf[index++] = (uint8)stCoin.identifict.model[i];
		}	
		//ver
		sendbuf[index++] = stCoin.identifict.softwareVersion[0];
		sendbuf[index++] = stCoin.identifict.softwareVersion[1];
		//cap
		sendbuf[index++] = 0;
		sendbuf[index++] = 0;
		//ch_r
		for(i = 0;i < 16;i++){
			sendbuf[index++] = pcEncodAmount(stCoin.tube.ch[i]);
		}
		
		//ch_d
		for(i = 0;i < 16;i++){
			sendbuf[index++] = pcEncodAmount(stCoin.tube.ch[i]);
		}
	}
	else{
		//code
		for(i = 0;i < 3;i++){
			sendbuf[index++] = 0;
		}
		//sn
		for(i = 0;i < 12;i++){
			sendbuf[index++] = 0;
		}
		//model	
		for(i = 0;i < 12;i++){
			sendbuf[index++] = 0;
		}	
		//ver
		sendbuf[index++] = 0;
		sendbuf[index++] = 0;
		//cap
		sendbuf[index++] = 0;
		sendbuf[index++] = 0;
		//ch_r
		if(MDB_getCoinAcceptor() == COIN_ACCEPTOR_PPLUSE ||
			MDB_getCoinAcceptor() == COIN_ACCEPTOR_SPLUSE){
			for(i = 0;i < 16;i++){
				sendbuf[index++] = pcEncodAmount(stPcoin.ch[i]);
			}
		}
		else{
			for(i = 0;i < 16;i++){
				sendbuf[index++] = 0;
			}
		}
		
		//ch_d
		if(MDB_getCoinDispenser() == COIN_DISPENSER_HOPPER){
			for(i = 0;i < HP_SUM;i++){
				sendbuf[index++] = pcEncodAmount(stHopper[i].ch);
			}
			
			for(i = HP_SUM;i < 16;i++){
				sendbuf[index++] = 0;
			}
		}
		else{
			for(i = 0;i < 16;i++){
				sendbuf[index++] = 0;
			}
		}
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
		sendbuf[MT + 3] = MDB_billInit();
	}
	if(temp & OBJ_COIN){
		sendbuf[MT + 4] = MDB_coinInit();	
	}
	//FM_writeToFlash();
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
	
	
	
	costAmount = MDB_billCost(costAmount); //先扣纸币器
	costAmount = MDB_coinCost(costAmount);// 再扣硬币器
	
	//billamount
	temp32 = MDB_getBillRecvAmount();
	sendbuf[MT + 3] = H0UINT32(temp32);
	sendbuf[MT + 4] = H1UINT32(temp32);
	sendbuf[MT + 5] = L0UINT32(temp32);
	sendbuf[MT + 6] = L1UINT32(temp32);
	
	//coinAmount
	temp32 = MDB_getCoinRecvAmount();
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
	uint32 payAmount = 0,changedAmount,costAmount;
	memset(sendbuf,0,sizeof(sendbuf));
	sendbuf[MT + 1] = recvbuf[MT + 1];
	sendbuf[MT + 2] = recvbuf[MT + 2];
	temp = recvbuf[MT + 2];
	
	payAmount = MDB_getBillRecvAmount() + MDB_getCoinRecvAmount();
	costAmount = payAmount;
	
	if(temp & OBJ_BILL){
		//1100
		changedAmount = MDB_bill_payout(payAmount);
		sendbuf[MT + 3] = H0UINT32(changedAmount);
		sendbuf[MT + 4] = H1UINT32(changedAmount);
		sendbuf[MT + 5] = L0UINT32(changedAmount);
		sendbuf[MT + 6] = L1UINT32(changedAmount);
		if(payAmount >= changedAmount){
			payAmount = payAmount - changedAmount;
		}
		else{
			payAmount = 0;
		}
	}
	
	
	if(temp & OBJ_COIN){
		changedAmount = MDB_coin_payout(payAmount);
		sendbuf[MT + 7] = H0UINT32(changedAmount);
		sendbuf[MT + 8] = H1UINT32(changedAmount);
		sendbuf[MT + 9] = L0UINT32(changedAmount);
		sendbuf[MT + 10] = L1UINT32(changedAmount);
	}
	
	costAmount = MDB_billCost(costAmount);
	costAmount = MDB_coinCost(costAmount);

	
	DB_package(DB_MT_ACTION_RPT,MT + 11);
	DB_uart1Send();
}

static void DB_payout_rpt(void)
{
	uint8 temp;
	uint32 changedAmount,temp32;
	uint32 billPayAmount;
	uint32 coinPayAmount = 0;
	memset(sendbuf,0,sizeof(sendbuf));
	sendbuf[MT + 1] = recvbuf[MT + 1];
	sendbuf[MT + 2] = recvbuf[MT + 2];
	temp = recvbuf[MT + 2];
	
	billPayAmount = INTEG32(recvbuf[MT + 3],recvbuf[MT + 4],
						recvbuf[MT + 5],recvbuf[MT + 6]);
	coinPayAmount = INTEG32(recvbuf[MT + 7],recvbuf[MT + 8],
						recvbuf[MT + 9],recvbuf[MT + 10]);
	
	if(temp & OBJ_BILL){
		changedAmount = MDB_bill_payout(billPayAmount);
		sendbuf[MT + 3] = H0UINT32(changedAmount);
		sendbuf[MT + 4] = H1UINT32(changedAmount);
		sendbuf[MT + 5] = L0UINT32(changedAmount);
		sendbuf[MT + 6] = L1UINT32(changedAmount);
	}

	
	if(temp & OBJ_COIN){
		
		changedAmount = MDB_coin_payout(coinPayAmount);
		//coinchanged
		sendbuf[MT + 7] = H0UINT32(changedAmount);
		sendbuf[MT + 8] = H1UINT32(changedAmount);
		sendbuf[MT + 9] = L0UINT32(changedAmount);
		sendbuf[MT + 10] = L1UINT32(changedAmount);
	}
	
	//billamount
	temp32 = MDB_getBillRecvAmount();
	sendbuf[MT + 11] = H0UINT32(temp32);
	sendbuf[MT + 12] = H1UINT32(temp32);
	sendbuf[MT + 13] = L0UINT32(temp32);
	sendbuf[MT + 14] = L1UINT32(temp32);
	
	//coinAmount
	temp32 = MDB_getCoinRecvAmount();
	sendbuf[MT + 15] = H0UINT32(temp32);
	sendbuf[MT + 16] = H1UINT32(temp32);
	sendbuf[MT + 17] = L0UINT32(temp32);
	sendbuf[MT + 18] = L1UINT32(temp32);
	DB_package(DB_MT_ACTION_RPT,MT + 19);
	DB_uart1Send();
}


static void DB_bill_con_rpt(void)
{
	uint8 in = MT + 1,out = MT + 2;
	stMdb.bill_type = recvbuf[out++];
	FM_writeToFlash();
	sendbuf[in++] = MDB_BILL_CON_RPT;
	sendbuf[in++] = 1;	
	DB_package(DB_MT_ACTION_RPT,in);
	DB_uart1Send();
	FM_readFromFlash();
}


//配置硬币设备
static void DB_coin_con_rpt(void)
{
	uint8 in = MT + 1,out = MT + 2,i;
	stMdb.coin_type = recvbuf[out++];
	stMdb.highEnable = recvbuf[out++];
	if(MDB_getCoinAcceptor() == COIN_ACCEPTOR_PPLUSE ||
		MDB_getCoinAcceptor() == COIN_ACCEPTOR_SPLUSE){
		for(i = 0;i < 16;i++){
			stPcoin.ch[i] = pcAnalysisAmount(recvbuf[out++]);
		}	
	}
	else{
		out += 16;
	}
	
	if(MDB_getCoinDispenser() == COIN_DISPENSER_HOPPER){
		for(i = 0;i < HP_SUM;i++){
			stHopper[i].ch = pcAnalysisAmount(recvbuf[out++]);
		}
	}
	else{
		out += 16;
	}
	FM_writeToFlash();
	
	sendbuf[in++] = MDB_COIN_CON_RPT;
	sendbuf[in++] = 1;
	DB_package(DB_MT_ACTION_RPT,in);
	DB_uart1Send();
	FM_readFromFlash();
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
	sendbuf[index++] = 0x03;
	
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
		id[i] = id[i];
		id[i] = recvbuf[index++];
	}
//	DB_writeFlashId(id);
	sendbuf[MT + 1] = 0x01;
	DB_package(0x75,MT + 2);
	DB_uart1Send();

}



static void DB_hp_payout_rpt(void)
{
	uint8 in = MT + 1,out = MT + 2,i;
	uint8 addr,res;
	uint16 nums,changed = 0;
	
	addr = recvbuf[out++];
	nums = INTEG16(recvbuf[out+0],recvbuf[out+1]);
	
	if(MDB_getCoinDispenser() == COIN_DISPENSER_HOPPER){
		changed = HP_payout_by_no(addr,nums);
	}
	else{
		changed = 0;
	}
	
	sendbuf[in++] = MDB_HP_PAYOUT_RPT;
	sendbuf[in++] = addr;
	sendbuf[in++] =	changed;
	DB_package(DB_MT_ACTION_RPT,in);
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
				case MDB_COIN_CON_REQ:	DB_coin_con_rpt();	break;
				case MDB_BILL_CON_REQ:	DB_bill_con_rpt();	break;
				case MDB_HP_PAYOUT_REQ: DB_hp_payout_rpt();break;
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









