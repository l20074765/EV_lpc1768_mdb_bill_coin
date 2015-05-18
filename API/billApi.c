#include "..\config.h"
#include "billApi.h"

#define DEBUG_BILL

#ifdef 	DEBUG_BILL
#define print_bill(...)	Trace(__VA_ARGS__)
#else
#define print_bill(...)
#endif

#define MDB_BILL_RESET			0x30   		//复位
#define MDB_BILL_SETUP			0x31   		//初始化
#define MDB_BILL_SECURITY		0x32   		//
#define MDB_BILL_POLL				0x33				//轮训
#define MDB_BILL_BILL_TYPE	0x34   		//
#define MDB_BILL_ESCROW			0x35  		//
#define MDB_BILL_STACKER		0x36  
#define MDB_BILL_EXPANSION 	0x37  		//扩展命令

static uint8 xdata recvbuf[36] = {0};
static uint8 xdata recvlen = 0;

ST_DEV_BILL xdata stBill;
static BILL_POLL xdata poll;

static uint8 xdata isEscrow = 0;

/*********************************************************************************************************
** Function name:       bill_send
** Descriptions:          纸币器命令发送 
** input parameters:    dev:设备号(高5位地址及低三位命令)；
**											*wdata:要发送的数据 wdata：要发送数据的长度
** output parameters:   
** Returned value:      0:通信超时 1通讯成功 2接收错误 
*********************************************************************************************************/
static uint8 bill_send(uint8 dev,uint8 *wdata,uint8 wlen)
{
	uint8  res;
	memset(recvbuf,0,sizeof(recvbuf));
	res = MDB_conversation(dev,wdata,wlen,recvbuf,&recvlen);
	return (res == 1) ?  1 : (res == 0 ? 0 : 2);
}




/*********************************************************************************************************
** Function name:       bill_reset
** Descriptions:        纸币器设备复位操作
** input parameters:    无
** output parameters:   无
** Returned value:      0超时 ,1成功 2数据错误
*********************************************************************************************************/
static uint8 bill_reset()
{
	uint8 res;
	res = bill_send(MDB_BILL_RESET,NULL,0x00); //Reset
	return res;
}


static uint8 bill_setup(BILL_SETUP *setup)
{
	uint8 res,i;
	res = bill_send(MDB_BILL_SETUP,NULL,0x00);
	if(res != 1)
		return res;
	 //level = 1 does not support option bits  level = 2 supports option bits
	setup->level = recvbuf[0];
	setup->codel = INTEG16(recvbuf[1],recvbuf[2]);
	setup->scale = INTEG16(recvbuf[3],recvbuf[4]);
	setup->decimal = recvbuf[5];
	
	setup->rato = setup->scale * 100;//以分为单位
	for(i = 0;i < setup->decimal;i++){
		setup->rato /= 10;
	}
	setup->stkCapacity = INTEG16(recvbuf[6],recvbuf[7]);
	setup->security = INTEG16(recvbuf[8],recvbuf[9]);
	setup->escrowFun = (recvbuf[10] == 0) ?  0 : 1;

	for(i=0;i<16;i++){
		if(recvbuf[11+i] == 0xFF) 
			setup->ch[i] = 0;
		else
			setup->ch[i] = (uint32)recvbuf[11+i] * setup->rato;			
	}
	
	print_bill("bill-setup:level = %d\r\n",setup->level);
	return 1;
}

/*********************************************************************************************************
** Function name:       bill_recycler_enable
** Descriptions:        循环斗使能
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 bill_recycler_enable(uint16 en)
{
	uint8 wdata[20] = {0x00},res,index = 0,i;
	wdata[index++] = 0x04;//type
	
	wdata[index++] = HUINT16(en);
	wdata[index++] = LUINT16(en);
	for(i = 0;i < 16;i++){
		if(en & (0x01U << i)){
			wdata[index++] = 0x03;
		}
		else{
			wdata[index++] = 0x00;
		}
	}
   	res = bill_send(MDB_BILL_EXPANSION,wdata,19);	
	return res;
}


/*********************************************************************************************************
** Function name:       bill_poll
** Descriptions:        纸币器轮询
** input parameters:    无
** output parameters: 
** Returned value:      0超时 ,1成功 2数据错误
*********************************************************************************************************/
uint8 bill_poll(BILL_POLL *poll)
{
	uint8 res,i,temp,z1;
	poll->err = 0;
	poll->s = 0;
	poll->routing = BILL_POLL_N_A;
	res = bill_send(MDB_BILL_POLL,NULL,0x00);	
	if(res != 1)
		return res;	
	if(recvlen == 0){ //ack
		return 1;
	}
	for(i = 0;i < recvlen;){
		z1 = recvbuf[i++];
		if(z1 & 0x80){ //收币
			temp = (z1 >> 4) & 0x07;
			if(temp == 0x00){ //BILL STACKED
				poll->routing = BILL_POLL_STACKED;
			}
			else if(temp == 0x01){ //暂存器
				poll->routing = BILL_POLL_ESCROW_POSITION;
				poll->type = z1 & 0x0F;
			}
			else if(temp == 0x02){ //纸币被退回
				poll->routing = BILL_POLL_RETURNED;
			}
			else if(temp == 0x04){
				poll->routing = BILL_POLL_DISABLED_REJECTED;
			}
			else if(temp == 0x03){
				poll->routing = BILL_POLL_RECYCLER;
			}
			else{
				poll->routing = BILL_POLL_N_A;
			}
		}
		else if(z1 & 0x20){ // 循环斗状态
			temp = z1 & 0x0F;
			switch(temp){
				case 0x06:
					poll->err |= BILL_ERR_MOTO;
					break;
				case 0x08:
					poll->err |= BILL_ERR_ROM;
					break;
				case 0x09: //找零器禁能 需要开启
					msleep(50);
					bill_recycler_enable(stBill.recycler.routing);
					break;
				default:break;
			}
		}
		else{	//状态
			temp = z1 & 0x0F;
			switch(temp)   //validator status
			{
	            case 0x01:			                 //defective motor  
	            	poll->err |= BILL_ERR_MOTO;
			        break;
		        case 0x02:			                 //sensor problem
					poll->err |= BILL_ERR_SENSOR;
			        break;
		        case 0x03:			                 //validator busy
					poll->s |= BILL_BIT_BUSY;
		        	break;
		        case 0x04:			                 //rom chksum err
					poll->err |= BILL_ERR_ROM;
		        	break;
		        case 0x05:			                 //validator jammed
					poll->err |= BILL_ERR_JAM;	       
			        break;
		        case 0x06:			                 //validator was reset
					poll->s |= BILL_BIT_RESET;
					break;
		        case 0x07:			                 //bill removed	
		        	break;
		        case 0x08:			                 //cash box out of position
					poll->err |= BILL_ERR_REMOVECASH;	 
			        break;
		        case 0x09:			                 //validator disabled	
		        	poll->s |= BILL_BIT_DISABLE;	 
					break;
		        case 0x0A:			                 //invalid escrow request
		       		break;
		        case 0x0B:			                 //bill rejected
		        	break;	
		        case 0x0C:			                 //possible credited bill removal
					poll->err |= BILL_ERR_CASH;
			        break;
		        default:	
					break;
	         }
		}
	}
	return 1;
}



/*********************************************************************************************************
** Function name:       bill_enable
** Descriptions:        使能纸币器
** input parameters:    flag 1:使能  0:禁能
** output parameters:   无
** Returned value:      0失败  1成功
*********************************************************************************************************/
uint8 bill_enable(uint8 flag)
{
	uint8 i,wbuf[4] = {0x00,0x00,0xFF,0xFF},res;
	if(flag == 1){
		for(i = 0;i < 8;i++){
			if(stBill.setup.ch[i] != 0){
				wbuf[1] |= (0x01 << i);
			}
			if(stBill.setup.ch[i + 8] != 0){
				wbuf[0] |= (0x01 << i);
			}
		}
	}
	
	for(i = 0;i < 3;i++){
		res = bill_send(MDB_BILL_BILL_TYPE,wbuf,4); //Enable
		if(res == 1){
			if(flag == 1){
				stBill.s.status &=  ~BILL_BIT_DISABLE;
			}
			else{
				stBill.s.status |=  BILL_BIT_DISABLE;
			}
			return 1;
		}
		msleep(150);
	}
    return (res == 1);
}

/*********************************************************************************************************
** Function name:       bill_escrow
** Descriptions:         暂存纸币
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 bill_escrow(void)
{
	uint8 wbuf = 0x01,res;
    res = bill_send(MDB_BILL_ESCROW,&wbuf,1); //Enable
    return (res == 1);
}



/*********************************************************************************************************
** Function name:       bill_reject
** Descriptions:        退币
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 bill_reject(void)
{
	uint8 wdata = 0,res;
   	res = bill_send(MDB_BILL_ESCROW,&wdata,1);	
	return (res == 1);	
}


/*********************************************************************************************************
** Function name:       bill_expansion_id
** Descriptions:        获取level1 纸币器ID
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 bill_expansion_id(BILL_ID *id)
{
	uint8 wdata = 0,res,index = 0,i;
   	res = bill_send(MDB_BILL_EXPANSION,&wdata,1);	
	if(res != 1){
		return res;
	}

	id->manuCode[0] = recvbuf[index++];
	id->manuCode[1] = recvbuf[index++];
	id->manuCode[2] = recvbuf[index++];
	print_bill("bill-id:manCode = %s\r\n",id->manuCode);
	for(i = 0;i < 12;i++){
		id->sn[i] = recvbuf[index++];
	}
	
	print_bill("bill-id:sn = %s\r\n",id->sn);
	for(i = 0;i < 12;i++){
		id->model[i] = recvbuf[index++];
	}
	print_bill("bill-id:model = %s\r\n",id->model);
	id->softVer[0] = recvbuf[index++];
	id->softVer[1] = recvbuf[index++];
	
	return 1;
}



/*********************************************************************************************************
** Function name:       bill_exp_feature_enable
** Descriptions:        启动level2 纸币器扩展属性
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 bill_exp_feature_enable(void)
{
	uint8 wdata[5] = {1,0x00,0x00,0x00,0x02},res;
   	res = bill_send(MDB_BILL_EXPANSION,wdata,5);	
	if(res != 1){
		return res;
	}
	return 1;
}

/*********************************************************************************************************
** Function name:       bill_exp_level2_id
** Descriptions:        查询level2 纸币器扩展属性
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 bill_exp_level2_id(BILL_ID *id)
{
	uint8 wdata = 0x02,res,index = 0,i;
   	res = bill_send(MDB_BILL_EXPANSION,&wdata,1);	
	if(res != 1){
		return res;
	}
	id->manuCode[0] = recvbuf[index++];
	id->manuCode[1] = recvbuf[index++];
	id->manuCode[2] = recvbuf[index++];
	
	
	for(i = 0;i < 12;i++){
		id->sn[i] = recvbuf[index++];
	}
	for(i = 0;i < 12;i++){
		id->model[i] = recvbuf[index++];
	}

	id->softVer[0] = recvbuf[index++];
	id->softVer[1] = recvbuf[index++];
	
	
	id->feature = INTEG32(recvbuf[index + 0],recvbuf[index + 1],
								recvbuf[index + 2],recvbuf[index + 3]);
	
	print_bill("bill-id:manCode = %s\r\n",id->manuCode);
	print_bill("bill-id:sn = %s\r\n",id->sn);
	print_bill("bill-id:model = %s\r\n",id->model);
	print_bill("bill_exp_level2_id:feature = %x\r\n",id->feature);
	return 1;
}

/*********************************************************************************************************
** Function name:       bill_recycler_setup
** Descriptions:        循环斗初始化
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 bill_recycler_setup(BILL_RECYCLER *recycler)
{
	uint8 wdata = 0x03,res,index = 0,i;
   	res = bill_send(MDB_BILL_EXPANSION,&wdata,1);	
	if(res != 1){
		return res;
	}
	recycler->routing = INTEG16(recvbuf[index],recvbuf[index + 1]);
	
	for(i = 0;i < 16;i++){
		if(recycler->routing & (0x01U << i)){
			recycler->ch[i] = stBill.setup.ch[i];
		}
		else{
			recycler->ch[i] = 0;
		}
	}
	print_bill("recycler_setup:rout=%x\r\n",recycler->routing);
	return 1;
}




/*********************************************************************************************************
** Function name:       bill_recycler_status
** Descriptions:        循环斗状态
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 bill_recycler_status(BILL_RECYCLER *recycler)
{
	uint8 wdata[2] = {0x00},res,i;
	wdata[0] = 0x05;//type
   	res = bill_send(MDB_BILL_EXPANSION,wdata,1);	
	if(res != 1)
		return res;
	
	recycler->full = INTEG16(recvbuf[0],recvbuf[1]);
	stBill.amount.remain_amount = 0;
	for(i = 0;i < 16;i++){
		recycler->ch_count[i] = INTEG16(recvbuf[2 + i * 2],recvbuf[2 + i * 2 + 1]);
		if(recycler->ch_count[i] > 0){
			stBill.amount.remain_amount += recycler->ch_count[i] * recycler->ch[i];
		}
	}
	
	return 1;
	
}


/*********************************************************************************************************
** Function name:       bill_recycler_dispense_by_num
** Descriptions:        循环斗找零
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 bill_recycler_dispense_by_num(uint8 type,uint16 num)
{
	uint8 wdata[8] = {0x00},res,index = 0;
	wdata[index++] = 0x06;//type
   
	wdata[index++] = type;
	wdata[index++] = HUINT16(num);
	wdata[index++] = LUINT16(num);
	
	res = bill_send(MDB_BILL_EXPANSION,wdata,4);	
	if(res != 1)
		return res;
	
	
	return 1;
	
}


/*********************************************************************************************************
** Function name:       bill_recycler_dispense_by_value
** Descriptions:        循环斗找零
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 bill_recycler_dispense_by_value(uint16 value)
{
	uint8 wdata[8] = {0x00},res,index = 0;
	wdata[index++] = 0x07;//type
	wdata[index++] = HUINT16(value);
	wdata[index++] = LUINT16(value);
	
	res = bill_send(MDB_BILL_EXPANSION,wdata,3);	
	return res;
}

/*********************************************************************************************************
** Function name:       bill_recycler_dispense_status
** Descriptions:        循环斗状态
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint32 bill_recycler_dispense_status(void)
{
	uint8 wdata[8] = {0x00},res,index = 0,i;
	uint32 value = 0;
	uint16 temp;
	wdata[0] = 0x08;//type
	res = bill_send(MDB_BILL_EXPANSION,wdata,1);	
	if(res == 1){
		for(i = 0;i < 16;i++){
			temp = INTEG16(recvbuf[index + 0],recvbuf[index + 1]);
			index += 2;
			if(temp > 0){
				value += temp * stBill.recycler.ch[i];
			}
		}
	}
	else{
		value = 0;
	}
	
	return value;
	
}



/*********************************************************************************************************
** Function name:       bill_recycler_dispense_status
** Descriptions:        循环斗状态
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 bill_recycler_dispense_poll(uint8 *finished)
{
	uint8 wdata[8] = {0x00},res;
	wdata[0] = 0x09;//type
	res = bill_send(MDB_BILL_EXPANSION,wdata,1);	
	if(res != 1)
		return res;
	
	if(recvlen == 0){ // finished
		*finished = 1;
	}
	else{
		//temp = INTEG16(recvbuf[index + 0],recvbuf[index + 1]);
		*finished = 0;
	}
	return 1;
}





/*********************************************************************************************************
** Function name:       bill_recycler_payout_by_num
** Descriptions:        循环斗状态
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint32 bill_recycler_payout_by_num(uint8 type,uint16 num)
{
	uint8 res,isFinished,i,err = 0;
	uint32 changedAmount  = 0;
	
	for(i = 0;i < 3;i++){
		res = bill_recycler_dispense_by_num(type,num);
		if(res == 1) break;
	}
	if(res != 1){
		return 0;
	}
	
	while(1){
		res = bill_poll(&poll);
		err = (res == 0) ? err + 1 : 0;
		if(err > 10){
			return 0;
		}
		msleep(100);
		res = bill_recycler_dispense_poll(&isFinished);
		if(res == 1 && isFinished == 1){
			msleep(100);
			changedAmount = bill_recycler_dispense_status();
			msleep(100);
			bill_recycler_status(&stBill.recycler);
			return changedAmount;
		}
		else{
			msleep(100);
		}
		
		
		
	}
	
}


/*********************************************************************************************************
** Function name:       bill_recycler_payout_by_value
** Descriptions:        循环斗状态
** input parameters:    无
** output parameters:   无
** Returned value:      返回找零金额
*********************************************************************************************************/
uint32 bill_recycler_payout_by_value(uint32 amount)
{
	uint8 res,isFinished,i,err = 0;
	uint32 changedAmount  = 0;
	
	if(stBill.setup.rato == 0){
		return 0;
	}
	else{
		amount /= stBill.setup.rato;
	}
	
	for(i = 0;i < 3;i++){
		res = bill_recycler_dispense_by_value((uint16)amount);
		if(res == 1) break;
	}
	
	if(res != 1){
		return 0;
	}
	
	while(1){
		res = bill_poll(&poll);
		err = (res == 0) ? err + 1 : 0;
		if(err > 10){
			return 0;
		}
		msleep(100);
		res = bill_recycler_dispense_poll(&isFinished);
		if(res == 1 && isFinished == 1){
			msleep(100);
			changedAmount = bill_recycler_dispense_status();
			msleep(100);
			bill_recycler_status(&stBill.recycler);
			return changedAmount;
		}
		else{
			msleep(100);
		}
	}
}







/*********************************************************************************************************
** Function name:       billInit
** Descriptions:          纸币器设备初始化
** input parameters:    无
** output parameters:   无
** Returned value:      0失败 1成功2超时
*********************************************************************************************************/
uint8 billInit(void)
{
	uint8 res,i;
	res = bill_reset();
	if(res != 1)
		return res;
	for(i = 0;i < 50;i++){ //5s 超时
		msleep(100);
		bill_poll(&poll);
		if(poll.s & BILL_BIT_RESET){ //复位成功继续执行初始化
			break;
		}
	}
	if(i >= 50){
		return 0;
	}
	
	
	msleep(100);
	bill_setup(&stBill.setup);
	msleep(100);
	if(stBill.setup.level == 2){ //纸币器等级2的初始化流程
		bill_exp_feature_enable();
		msleep(100);
		bill_exp_level2_id(&stBill.id);
		if(stBill.id.feature & (0x01U << 1)){
			stBill.setup.isRecycler = 1;
			msleep(100);
			bill_recycler_setup(&stBill.recycler);
			msleep(100);
			bill_recycler_enable(stBill.recycler.routing);
			msleep(100);
			bill_recycler_status(&stBill.recycler);
		}
		else{
			stBill.setup.isRecycler = 0;
		}
	}
	else{
		stBill.setup.isRecycler = 0;
		bill_expansion_id(&stBill.id);
	}
	
	print_bill("IsRecycler=%d\r\n",stBill.setup.isRecycler);
	msleep(100);
	res = bill_enable(0);
	return (res == 1);
}


/*********************************************************************************************************
** Function name:       billTaskPoll
** Descriptions:        纸币器设备轮训
** input parameters:    无
** output parameters: 
** Returned value:      有纸币收入返回1，无返回0
*********************************************************************************************************/
uint8 billTaskPoll(void)
{
	BILL_STATE *state = &stBill.s;
	uint8 res,temp;
	static uint8 comErr = 5;
	
	if((state->status & BILL_BIT_FAULT) && (state->errNo & BILL_ERR_COM)){
		if(Timer.timer_bill_reset == 0){
			res = billInit();
			if(res == 1){
				state->status = 0;
				state->errNo = 0;
				state->status |= BILL_BIT_DISABLE;
			}
			else{
				Timer.timer_bill_reset = 1000;
			}
		}	
	}
	else{
		//轮询 纸币器
		res = bill_poll(&poll);
		comErr = (res == 0) ? (comErr >= 5 ? 5 : comErr + 1) : 0;//超时
		if(res == 1){
			if(poll.s & BILL_BIT_DISABLE){
				//stBill.s.status |= BILL_BIT_DISABLE;
				if(poll.err){
					stBill.s.errNo |= poll.err;
					stBill.s.status |= BILL_BIT_FAULT;
				}
			}
			else{
				//stBill.s.status &= ~BILL_BIT_DISABLE;
				if(poll.err == 0){
					stBill.s.errNo = 0;
					stBill.s.status &= ~BILL_BIT_FAULT;
				}
			}
			
			if(poll.routing == BILL_POLL_N_A){
				if(Timer.bill_escrow_timeout == 0 && isEscrow == 1){ //押钞超时
					isEscrow = 0;
				}
			}
			else if(poll.routing == BILL_POLL_ESCROW_POSITION){
				msleep(100);
				if(bill_escrow() == 1){ //押钞指令发送成功
					isEscrow = 1;
					Timer.bill_escrow_timeout = 3100; //31秒的押钞超时
				}
				else{
					msleep(100);
					bill_reject();
				}
			}
			else if(poll.routing == BILL_POLL_RETURNED){
				isEscrow = 0;
			}
			else if(poll.routing == BILL_POLL_STACKED){
				if(isEscrow == 1){
					isEscrow = 0;
					temp = poll.type % 16;
					stBill.amount.recv_amount += stBill.setup.ch[temp];
				}
			}
			else if(poll.routing == BILL_POLL_RECYCLER){
				if(isEscrow == 1){
					isEscrow = 0;
					temp = poll.type % 16;
					stBill.amount.recv_amount += stBill.setup.ch[temp];
					msleep(100);
					bill_recycler_status(&stBill.recycler);
				}
			}
		}
		
		if(comErr >= 5){
			state->status |= BILL_BIT_FAULT;
			state->errNo |= BILL_ERR_COM;
		}
	}
	return 0;
}












