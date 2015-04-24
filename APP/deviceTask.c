#include "deviceTask.h"
#include "..\config.h"

//#define DEV_DEBUG
#ifdef DEV_DEBUG

#define print_dev(...)	Trace(__VA_ARGS__)
#else
#define print_dev(...)
#endif

//按键邮箱句柄
OS_EVENT *g_KeyMsg;
void *KeyMsgArray[2]; // 按键队列数组

extern OS_EVENT *g_mdb_event; //声明MDb事件




/*********************************************************************************************************
** Function name:       CreateMBox
** Descriptions:        为任务之间通信创建邮箱和信号量
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void CreateMBox(void)
{
	//创建按键邮箱
	g_KeyMsg = OSQCreate(&KeyMsgArray[0],2);
}

/*********************************************************************************************************
** Function name:       SystemInit
** Descriptions:        系统初始化
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void SystemInit()
{
	InitUart0();
	InitUart1();
	InitUart2();
	InitUart3();
    InitBuzzer();
	InitI2C0();
	InitTimer(0,240000);
	
}





void DEV_task(void *pdata)
{	
	SystemInit();//系统基本接口初始化
	CreateMBox();//建立邮箱、信号量	
	memset((void *)&stBill,0,sizeof(stBill));
	memset((void *)&stCoin,0,sizeof(stCoin));
	memset((void *)&stMdb,0,sizeof(stMdb));
	stMdb.billType = 2;
	stMdb.coinType = 2;
	stBill.s.status |= BILL_BIT_FAULT;
	stBill.s.errNo |= BILL_ERR_COM;
	stCoin.state.s |= COIN_BIT_FAULT;
	stCoin.state.err |= COIN_ERR_COM;
	
	while(1){
		Trace("bill:s=%d,err=%x\r\n",stBill.s.status,stBill.s.errNo);
		Trace("coin:s=%d,err=%x\r\n",stCoin.state.s,stCoin.state.err);
		coinTaskPoll();
		billTaskPoll();
		DB_task();
		msleep(100);
	}
}



