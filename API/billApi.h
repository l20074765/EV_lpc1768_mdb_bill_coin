#ifndef _BILL_API_H
#define _BILL_API_H


#define BILL_BIT_FAULT						0x01UL 	//故障
#define BILL_BIT_DISABLE					(0x01UL << 1) //禁能位
#define BILL_BIT_QUEBI						(0x01UL << 2) //缺币位
#define BILL_BIT_BUSY						(0x01UL << 3) //硬币器忙位

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



typedef struct _bill_poll_{
	uint8 	s;
	uint8  	type; 
	uint16 	err;
	uint16 	routing;	
}BILL_POLL;



typedef struct _bill_identifict_{
	char manufacturerCode[3];	//厂家代码 ASCII码
	char sn[12];				//ASCII码
	char model[12];				//ASCII码
	char softwareVersion[2];	//BCD
}BILL_IDENTIFICT;


typedef struct _bill_setup_{
	uint8  level; 			 //纸币器等级
	uint8  escrowFun;		 //暂存功能
	uint16 codel;		  	 //国家代码
	uint16 scale;			 //比例因子
	uint16 decimal;		     //10^小数位数
	uint16 rato;
	uint16 stkCapacity;	    //储币容量
	uint16 security;		//安全等级
	uint32 channel[16];
}BILL_SETUP;


typedef struct _bill_state_{
	// bit0 整状态: 	0-正常 		1-故障  
	// bit1 禁能状态: 	0-使能 		1-禁能 
	uint8 	status;  	//整体状态
	uint16 	errNo; 		//故障码
}BILL_STATE;


typedef struct _bill_amount_{
	uint32 recvAmount;
	uint32 oneAmount;
}BILL_AMOUNT;

typedef struct	_st_dev_bill_{
	BILL_IDENTIFICT identifict;
	BILL_POLL poll;
	BILL_STATE s;
	BILL_AMOUNT amount;
	BILL_SETUP setup;
	
}ST_DEV_BILL;

extern ST_DEV_BILL xdata stBill;


uint8 billInit(void);
uint8 bill_enable(uint8 flag);
uint8 billTaskPoll(void);
#endif
