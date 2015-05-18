#ifndef _BILL_API_H
#define _BILL_API_H
#include "..\Drivers\board.h"

#define BILL_BIT_FAULT						(0x01UL) 		  //故障
#define BILL_BIT_DISABLE					(0x01UL << 1) //禁能位
#define BILL_BIT_QUEBI						(0x01UL << 2) //缺币位
#define BILL_BIT_BUSY						(0x01UL << 3) //硬币器忙位
#define BILL_BIT_RESET						(0x01UL << 4)
#define BILL_BIT_PAYBACK					(0x01UL << 7) //退币位




#define BILL_ERR_COM					0x0001UL //通信故障
#define BILL_ERR_SENSOR					0x0002UL //传感器故障
#define BILL_ERR_TUBEJAM				0x0004UL //出币口卡币
#define BILL_ERR_ROM					0x0008UL //rom出错
#define BILL_ERR_ROUTING				0x0010UL //进币通道出错
#define BILL_ERR_JAM					0x0020UL //投币卡币
#define BILL_ERR_REMOVECASH				0x0040UL //移除纸币钞箱
#define BILL_ERR_DISABLE				0x0080UL //禁能
#define BILL_ERR_MOTO					0x0100UL //马达故障
#define BILL_ERR_CASH					0x0200UL //纸币钞箱故障
#define BILL_ERR_UNKNOW					0x8000UL //其他各种故障


#define BILL_POLL_N_A					0x0000 //无动作
#define BILL_POLL_ESCROW_POSITION		0x0001 //押钞
#define BILL_POLL_STACKED				0x0002 //暂存
#define BILL_POLL_RETURNED				0x0004 //纸币被退回
#define BILL_POLL_DISABLED_REJECTED		0x0008 //
#define BILL_POLL_RECYCLER				0x0010 //纸币进入循环斗
#define BILL_POLL_RECYCLER_MANUAL		0x0020 //手动让纸币进入循环斗
#define BILL_POLL_TRANSFERRED			0x0080 //纸币从循环斗转移到钞箱		


typedef struct _bill_poll_{
	uint8 	s;
	uint8  	type; 
	uint16 	err;
	uint16 	routing;	
}BILL_POLL;


typedef struct _bill_id_{
	int8 	manuCode[3];			//厂家代码 ASCII码
	int8 	sn[12];				//ASCII码
	int8 	model[12];				//ASCII码
	int8 	softVer[2];			//软件版本 BCD
	uint32 	feature;
}BILL_ID;


typedef struct _bill_setup_{
	uint8  	level; 			 //纸币器等级
	uint8  	escrowFun;		 //暂存功能
	uint8  	isRecycler;		//是否支持 循环斗
	uint16 	codel;		  	 //国家代码
	uint16 	scale;			 //比例因子
	uint16 	decimal;		     //10^小数位数
	uint16 	rato;
	uint16 	stkCapacity;	    //储币容量
	uint16 	security;		//安全等级
	uint32  ch[16]; 		//通道面值
}BILL_SETUP;


typedef struct _bill_state_{
	// bit0 整状态: 	0-正常 		1-故障  
	// bit1 禁能状态: 	0-使能 		1-禁能 
	uint8 	status;  	//整体状态
	uint16 	errNo; 		//故障码
}BILL_STATE;


typedef struct _bill_amount_{
	uint32 recv_amount;
	uint32 remain_amount;
}BILL_AMOUNT;


#define BILL_DISPENSE_IDLE 		0
#define BILL_DISPENSE_RUNING	1
#define BILL_DISPENSE_FINISH	2


typedef struct _bill_recycler_{
	uint16 	routing;
	uint16  en;
	uint16	full;
	uint16  ch_count[16];
	uint16  pay_num[16];
	uint32  ch[16];
}BILL_RECYCLER;




typedef struct	_st_dev_bill_{
	
	BILL_STATE 	s;
	BILL_AMOUNT amount;
	BILL_SETUP 	setup;
	BILL_ID 	id;
	BILL_RECYCLER recycler; //找零器
	
}ST_DEV_BILL;

extern ST_DEV_BILL xdata stBill;


uint8 	billInit(void);
uint8 	bill_enable(uint8 flag);
uint32 	bill_recycler_payout_by_value(uint32 amount);
uint8 	billTaskPoll(void);
#endif
