
#ifndef _PCCONAPI_H_
#define _PCCONAPI_H_
#include "..\Drivers\board.h"

//DB --> PC ?
#define     SF          0
#define     LEN         1
#define     ADDR        2
#define     SN          3
#define     MT          4
#define     DATA        5
#define     HEAD_LEN    5
#define     HEAD_PC     0xE5
#define     HEAD_DB     0xE6

#define		DB_CON_ADDR	0xFF

#define 	DB_MT_CON_REQ		0x05
#define 	DB_MT_CON_RPT		0x75

#define 	DB_MT_ID_REQ		0x06
#define 	DB_MT_ID_RPT		0x76


#define		DB_MT_CHECK_REQ		0x21
#define		DB_MT_CHECK_RPT		0x91

#define 	DB_MT_ACTION_REQ	0x22
#define 	DB_MT_ACTION_RPT	0x92

#define 	MDB_CHECK_REQ 		0x01
#define 	MDB_CHECK_RPT 		0x01

#define 	MDB_BILL_INFO_REQ 	0x02
#define 	MDB_BILL_INFO_RPT	0x02

#define 	MDB_COIN_INFO_REQ 	0x03
#define 	MDB_COIN_INFO_RPT	0x03

#define 	MDB_INFO_REQ 		0x04
#define 	MDB_INFO_RPT		0x04


#define 	MDB_INIT_REQ 		0x01
#define 	MDB_INIT_RPT		0x01


#define 	MDB_CONTROL_REQ 	0x02
#define 	MDB_CONTROL_RPT		0x02

#define 	MDB_PAYOUT_REQ 		0x03
#define 	MDB_PAYOUT_RPT		0x03

#define 	MDB_PAYBACK_REQ 	0x04
#define 	MDB_PAYBACK_RPT		0x04

#define 	MDB_COST_REQ 		0x05
#define 	MDB_COST_RPT		0x05

#define 	MDB_COIN_CON_REQ 		0x06
#define 	MDB_COIN_CON_RPT		0x06

#define 	MDB_BILL_CON_REQ 		0x07
#define 	MDB_BILL_CON_RPT		0x07

#define 	MDB_HP_PAYOUT_REQ 		0x08
#define 	MDB_HP_PAYOUT_RPT		0x08


#define 	MDB_FLASH_PAGE_ID	(0x200U) 


#define 	OBJ_BILL		0x01
#define 	OBJ_COIN		0x02

#define     BILL_ACCEPTOR_NONE		0
#define     BILL_ACCEPTOR_MDB		2

#define     BILL_DISPENSER_NONE		0
#define     BILL_DISPENSER_MDB		2	

#define     COIN_ACCEPTOR_NONE		0
#define     COIN_ACCEPTOR_PPLUSE	1
#define     COIN_ACCEPTOR_MDB		2
#define     COIN_ACCEPTOR_SPLUSE	3


#define     COIN_DISPENSER_NONE		0
#define     COIN_DISPENSER_HOPPER	1
#define     COIN_DISPENSER_MDB		2





typedef struct _st_mdb_{
	uint8 bill_type;
	uint8 coin_type;
	uint8 highEnable;
}ST_MDB;

extern ST_MDB xdata stMdb;

uint8 DB_task(void);
uint8 MDB_getCoinAcceptor(void);
uint8 MDB_getCoinDispenser(void);
uint8 MDB_getBillAcceptor(void);
uint8 MDB_getBillDispenser(void);
void MDB_setBillAcceptor(uint8 type);
void MDB_setBillDispenser(uint8 type);
void MDB_setCoinAcceptor(uint8 type);
void MDB_setCoinDispenser(uint8 type);

uint32 MDB_coin_payout(uint32 payAmount);
uint8 MDB_coinInit(void);
uint8 MDB_billInit(void);
#endif
