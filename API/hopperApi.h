#ifndef _HOPPER_API_H_
#define _HOPPER_API_H_
#include "..\Drivers\board.h"

//当前只做Hopper得指令，后续还有货道的操作指令等
#define HP_QUERY				(0x51)				//Hopper的查询操作指令
#define HP_PAYOUT				(0x50)				//Hopper的出币操作指令


#define HP_SUM              	8  		//定义hopper个数 最大支持8个

#define HP_PAYFAIL_NUM         	1   	//允许hopper斗出现的找零失败次数


#define HP_STATE_NORMAL			0		//hopper正常
#define HP_STATE_QUEBI			1   	//hopper缺币
#define HP_STATE_FAULT			2		//hopper故障
#define HP_STATE_COM			3 		//hopper 通信故障








//定义hopper斗 结构体
typedef struct __st_hopper_{
    uint8 addr;			//hopper 物理地址
    uint8 no;			//hopper编号
    uint8 state;		//hopper状态  0 正常 1 缺币 2 故障
	
	uint8 level;		//级别分配标志
	uint8 isCycle;		//循环斗标志
	uint8 lastPayFail;	//上次找零失败
	uint8 err_com;			//通信错误次数
	uint16 lastCount;	//上次操作出币数量
	uint32 ch;			//通道面值
	
}ST_HOPPER;
extern ST_HOPPER stHopper[HP_SUM];

//定义hopper级别 结构体数组 按数组依次划分级别 1 > 2 > 3
//例如 hopper1 hopper2 通道面值 1元 hopper3 通道面值为 5毛 则 hopper1 hopper2
//划分在级别1中,hopper3 划分在级别2中  级别3为空  即
typedef struct _st_hopper_level_{
    uint8 		num;//本级别hopper个数
    uint32 		ch;//本级别通道面值
	ST_HOPPER 	*hopper[HP_SUM];//定义hopper斗结构体指针数组
}ST_HOPPER_LEVEL;



void HP_task(void);
uint32 HP_payout(uint32 payAmount);
void HP_init(void);
uint8 HP_setCh(uint8 no,uint32 value);
uint16 HP_payout_by_no(uint8 addr,uint16 num);
#endif


/**************************************End Of File*******************************************************/
