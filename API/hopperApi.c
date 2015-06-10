#include "..\config.h"


#define DEBUG_HOPPER

#ifdef 	DEBUG_HOPPER
#define print_hopper(...)	Trace(__VA_ARGS__)
#else
#define print_hopper(...)
#endif



ST_HOPPER stHopper[HP_SUM];//定义8个hopper斗 结构体数组
//定义hopper级别 结构体数组 按数组依次划分级别 1 > 2 > 3
//例如 hopper1 hopper2 通道面值 1元 hopper3 通道面值为 5毛 则 hopper1 hopper2
//划分在级别1中,hopper3 划分在级别2中  级别3为空  即
ST_HOPPER_LEVEL stHopperLevel[HP_SUM];

static volatile uint8 sendbuf[64] = {0};
static volatile uint8 recvbuf[64] = {0};
static uint8 sn[HP_SUM] = {0};


/*********************************************************************************************************
** Function name:     	HP_send
** Descriptions:	    EVB通讯
** input parameters:    Chl:选择通道；Head:包头；Sn：序列号；Type:消息类别；Addr:设备地址;Data：数据；
** output parameters:   *ACK：应答包
** Returned value:      1：收到应答；0：未收到应答即通讯失败
*********************************************************************************************************/
uint8 HP_send(uint8 addr,uint8 cmd,uint16 data)
{
	uint8 index = 0,i,ch,len,crc;
	memset((void *)recvbuf,0,sizeof(recvbuf));
	
	sn[addr] = (cmd == HP_PAYOUT) ? sn[addr] + 1: sn[addr]; //更新sn
	
	sendbuf[index++] = 0xED;
	sendbuf[index++] = 0x08; //len
	sendbuf[index++] = sn[addr];
	sendbuf[index++] = cmd;
	sendbuf[index++] = addr;
	sendbuf[index++] = LUINT16(data);
	sendbuf[index++] = HUINT16(data);
	sendbuf[index++] = XorCheck((uint8 *)sendbuf,7);
	
	uart3_clr_buf();
	//发送数据禁止切换任务
	OSSchedLock();
	Uart3PutStr((uint8 *)sendbuf,8);
	OSSchedUnlock();
	
	#ifdef DEBUG_HOPPER
	print_hopper("HP-SEND[%d]:",index);
	for(i = 0;i < index;i++){
		print_hopper("%02x ",sendbuf[i]);
	}
	print_hopper("\r\n");
	#endif
	
	index = 0;
	Timer.hopper_recv_timeout = 100;
	while(Timer.hopper_recv_timeout){ //1000ms内收到ACK,否则超时
		if(Uart3BuffIsNotEmpty() == 1){
			ch = Uart3GetCh();
			if(index == 0){
				if(ch == 0xFD){
					recvbuf[index++] = ch;
				}
			}
			else if(index == 1){
				len = ch;
				recvbuf[index++] = ch;
			}
			else if(index >= (len - 1)){
				recvbuf[index++] = ch;
				crc = XorCheck((uint8 *)recvbuf,len - 1);
				if(crc == ch){
#ifdef DEBUG_HOPPER
					print_hopper("HP-RECV[%d]:",recvbuf[1]);
					for(i = 0;i < recvbuf[1];i++){
						print_hopper("%02x ",recvbuf[i]);
					}
					print_hopper("\r\n");
#endif
					return 1;
				}
			}
			else{
				recvbuf[index++] = ch;
			}
		}
		else{
			msleep(20);
		}
	}
	return 0;
}



/*********************************************************************************************************
** Function name:     	HP_check
** Descriptions:	    hopper设备操作控制函数
** input parameters:    addr:设备的硬件物理地址				
** output parameters:   无
** Returned value:      1：收到应答；0：应答超时  2 忙
*********************************************************************************************************/
uint8 HP_send_check(ST_HOPPER *hopper)
{
	uint8 res,s;
	res = HP_send(hopper->addr,HP_QUERY,0x00);
	if(res == 1){
		if(recvbuf[1] == 0x08 && hopper->addr == recvbuf[4]) {
			s = recvbuf[3];
			print_hopper("HP_state=%x\r\n",s);
			
			if(s & (0x01U << 1)){ //hopper忙
				return 3;
			}
			
			if((s & (0x01U << 2)) || (s & (0x01U << 7))){ //指令错误
				return 3;
			}
			
			if(s == 0){ //hopper 正常
				hopper->state = HP_STATE_NORMAL;
			}
			else{
				if((s & (0x01U << 3)) || (s & (0x01U << 5))){ //hopper 缺币
					hopper->state = HP_STATE_QUEBI;
				}
				
				if((s & (0x01U << 4)) || (s & (0x01U << 6))){ //hopper 故障
					hopper->state = HP_STATE_FAULT;
				}
			}
			hopper->lastCount = INTEG16(recvbuf[6], recvbuf[5]);
			return 1;
		}
		return 99;			
	}
	
	return 0;	
}


/*********************************************************************************************************
** Function name:     	HP_send_output
** Descriptions:	    EVBhopper设备操作控制函数
** input parameters:    addr:设备的硬件物理地址		
						num:Hopper出币操作的出币数量
** output parameters:   无
** Returned value:      1：收到应答；0：未收到应答即通讯失败
*********************************************************************************************************/
uint8 HP_send_output(ST_HOPPER *hopper,uint16 num)
{
	uint8 i,res;
	for(i = 0;i < 3;i++){
		res = HP_send(hopper->addr,HP_PAYOUT,num);
		if(res == 1 && recvbuf[1] == 0x06){
			return 1;
		}
		else{
			msleep(100);
		}
	}
	return 0;
}



/*********************************************************************************************************
** Function name:     	HP_init
** Descriptions:	    hopper设备初始化函数
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void HP_init(void)
{
	uint8 i,j,levelNum = 0;
	uint32 value;
	for(i = 0; i < HP_SUM;i++){
		value = stHopper[i].ch;
		memset((void *)&stHopper[i],0,sizeof(ST_HOPPER));
		memset((void *)&stHopperLevel[i],0,sizeof(ST_HOPPER_LEVEL));
		stHopper[i].ch = value;
		stHopper[i].addr = i;
	}
	
	//级别分配
	for(i = 0;i < HP_SUM;i++){
		value = 0;
		for(j = 0;j < HP_SUM;j++){ //查询未分配级别中的最大斗
			if(!stHopper[j].level && value < stHopper[j].ch){
				value = stHopper[j].ch;
			}
		}
		stHopperLevel[i].ch = value;
		if(value){
			for(j = 0;j < HP_SUM;j++){   //查询相同 面值的斗 进行分配
				if(value == stHopper[j].ch){
					levelNum = stHopperLevel[i].num++;
					stHopperLevel[i].hopper[levelNum] = &stHopper[j];
					stHopper[j].level = 1;//级别分配标志
				}
			}
		}
		
		print_hopper("Level=%d num =%d value = %d\r\n",
			i,stHopperLevel[i].num,stHopperLevel[i].ch);
	}
	

	print_hopper("hopperInit over..\r\n");
}




uint8 HP_setCh(uint8 no,uint32 value)
{
	if(no > HP_SUM || no == 0){
		return 0;
	}
	stHopper[no - 1].ch = value;
	return 1;
	
}

/*********************************************************************************************************
** Function name:     	HP_payout_by_addr
** Descriptions:	    hopper按地址找零
** input parameters:    num 需要找币数量
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint8 HP_payout_by_addr(ST_HOPPER *hopper,uint16 num)
{
	uint8 res;
	res = HP_send_output(hopper,num);
	if(res != 1){
		return 0;
	}
	
	msleep(1000); //等待1s
	Timer.hopper_payout_timeout = 5000 + num * 250;
	while(Timer.hopper_payout_timeout){
		res = HP_send_check(hopper);
		if(res == 1){ //找零完成
			if(num == hopper->lastCount){
				return 1;
			}
			else{
				return 0;
			}
		}
		msleep(100);
	}
	return 0;
	
}

/*********************************************************************************************************
** Function name:     	HP_payout_by_addr
** Descriptions:	    hopper按地址找零
** input parameters:    num 需要找币数量
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
uint16 HP_payout_by_no(uint8 addr,uint16 num)
{
	uint8 res;
	ST_HOPPER *hopper;
	if(addr <= 0 || addr > HP_SUM || num == 0){
		return 0;
	}
	
	hopper = &stHopper[addr - 1];
	res = HP_send_output(hopper,num);
	if(res != 1){
		return 0;
	}
	
	msleep(1000); //等待1s
	Timer.hopper_payout_timeout = 5000 + num * 250;
	while(Timer.hopper_payout_timeout){
		res = HP_send_check(hopper);
		if(res == 1){ //找零完成
			return hopper->lastCount;
		}
		msleep(100);
	}
	return 0;
	
}


/*********************************************************************************************************
** Function name:     	HP_payout_by_level
** Descriptions:	    hopper设备兑零操作函数
** input parameters:    changeCount——需要兑零的数量
** output parameters:   remainCount——兑零失败后剩余的数量
						levelNo :选择哪个级别斗 找零
** Returned value:      1：兑币成功；0：失败
*********************************************************************************************************/
uint8  HP_payout_by_level(uint8 l,uint16 payCount,uint16 *changedCount)
{
	uint8 i,cycleFlag = 0,res;
	uint16 payCountTemp = 0;
	
	ST_HOPPER *hopper;
	
	*changedCount = 0;
	if(payCount == 0){
		*changedCount = 0;
		return 1;
	}
	
	//断言 hopper斗号是否符合
	if(l >= HP_SUM){
		*changedCount = 0;
		print_hopper("The level = %d > %d(max) \r\n",l,HP_SUM);
		return 0;
	}
	
	if(stHopperLevel[l].num  == 0) { //没有可用的斗
		print_hopper("The level = %d useableNum = is 0 \r\n",l);
		*changedCount = 0;
		return 0;
	}
	
	//查询是否有循环斗
	for(i = 0; i < stHopperLevel[l].num;i++){
		hopper = stHopperLevel[l].hopper[i];
		if(hopper->isCycle && hopper->state == HP_STATE_NORMAL){
			cycleFlag = 1;
			break;
		}		
	}
	
	if(cycleFlag){	//有循环斗 优先让循环斗出币
		hopper = stHopperLevel[l].hopper[i];
		res = HP_payout_by_addr(hopper,payCount);
		if(res == 1){
			*changedCount  += payCount;
			return 1;
		}
		else{
			*changedCount += hopper->lastCount;	//循环斗找零失败 再找其他斗	
		}
	}
	
	//没有循环斗 则随便选择一个可用的斗 出币
	for(i = 0; i < stHopperLevel[l].num;i++)
	{	
		hopper = stHopperLevel[l].hopper[i];
		if(hopper->lastPayFail >= HP_PAYFAIL_NUM)//检查设备上次找零失败
			continue;
		payCountTemp = payCount - *changedCount;
		res = HP_payout_by_addr(hopper,payCountTemp);
		print_hopper("Select--level = %d addr= %d res =%d\r\n",l,hopper->addr,res);
		if(res == 1){
			*changedCount  += payCountTemp;
			hopper->lastPayFail =  0;//故障清除
			return 1;
		}
		else{
			*changedCount += hopper->lastCount;
			print_hopper("PayCount = %d,hopper[%d]->lastCount =%d,changedCount =%d\r\n",
					payCount,i,hopper->lastCount,*changedCount);
			//到此表示该斗 已经无法找币 置特殊故障并标记		
			hopper->lastPayFail++;//故障+1
		}				
	}
	return 0;
}



/*********************************************************************************************************
** Function name:     	HP_payout
** Descriptions:	    硬币兑零算法 面值从大到小找币
** input parameters:   
** output parameters:   
** Returned value:      1：兑币成功；0：失败
*********************************************************************************************************/
uint32 HP_payout(uint32 payAmount)
{
	uint8 i,res;
	uint16 changedCount = 0,payCount = 0;
	uint32 changedAmount;
	
	changedAmount = 0;
	//硬币器找零算法
	for(i = 0;i < HP_SUM;i++){
		if(stHopperLevel[i].ch > 0){
			payCount = payAmount / stHopperLevel[i].ch; //计算找币数量
			print_hopper("Coin level[%d].payCount = %d \r\n",i,payCount);
			res = HP_payout_by_level(i,payCount,&changedCount);
			changedAmount += changedCount * stHopperLevel[i].ch;
			if(changedAmount <= payAmount)
				payAmount = payAmount - changedAmount;
			else
				payAmount = 0;
			//找零成功
			if(res == 1 && payAmount == 0){
					return changedAmount;		
			}
		}
	}
	//找零不成功
	return changedAmount;	
}


static uint8 HP_getCheckNo(void)
{
	static uint8 no = 0;
	uint8 i ;
	for(i = no;i < HP_SUM;i++){
		if(stHopper[i].ch > 0){
			no = i + 1;
			return i;
		}
	}
	
	for(i = 0;i < no;i++){
		if(stHopper[i].ch > 0){
			no = i + 1;
			return i;
		}
	}
	
	return 0xFF;
}

static uint16 HP_getCheckTimer(void)
{
	uint16 time;
	uint8 i;
	time = 120;
	for(i = 0;i < HP_SUM;i++){
		if(stHopper[i].ch > 0){
			time = (time <= 50) ? 50 : time - 10;
		}
	}
	return time;
}

uint8 HP_allHopperCheck(void){
	uint8 i = 0;
	if(Timer.hopper_check_timeout == 0){
		i = HP_getCheckNo();
		if(i != 0xFF){
			if(HP_send_check(&stHopper[i]) == 0){
				stHopper[i].err_com = (stHopper[i].err_com < 100) ? stHopper[i].err_com + 1: 100;
			}
			else{
				stHopper[i].err_com = 0;
			}
			if(stHopper[i].err_com >= 5){
				stHopper[i].state = HP_STATE_COM; //通信失败
			}
		}
		Timer.hopper_check_timeout = HP_getCheckTimer();//3秒检测一个斗
	}
	return 1;
}




void HP_task(void)
{
	HP_allHopperCheck();
}




/**************************************End Of File*******************************************************/
