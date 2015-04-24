#ifndef _FLASH_API_H
#define _FLASH_API_H

//=======================flash页号==============================

//flash页号最大不超过 0x1FFF = 8191 否则 flash会翻转地址为0x0000
//系统参数写入flash  add by yoc 2014.2.19
#define ADD_SYSTEM_PARA     (256)  //预留256bytes空间存储
//#define ADD_SYSTEM_PARA_LEN (2) // 32 * 8

//用户级数据 写入flash地址
#define ADD_USER_DATA		(512)
//#define ADD_USER_LEN        (2)//用户级存储长度 256字节

//货道信息存储
#define ADD_HUODAO_INFO     (768)  //预留512bytes空间存储
//#define ADD_HUODAO_LEN		(2) //货道存储长度 512字节

//交易记录存储区间
#define ADD_TRADE_INFO      (1280)
#define ADD_TRADE_PAGE_LEN  (64)//每笔交易记录长度 64 字节


//=======================货道类型存储==============================
#define TYPE_HUODAO_ADDR			0x0001
#define TYPE_HUODAO_PRICE			0x0002
#define TYPE_HUODAO_STATE		    0x0004
#define TYPE_HUODAO_OPEN_FLAG		0x0008
#define TYPE_HUODAO_REMAIN			0x0010
#define TYPE_HUODAO_TRADE_COUNT		0x0020
#define TYPE_HUODAO_MAX_COUNT		0x0040
#define TYPE_HUODAO_PHYSIC_NO		0x0080
#define TYPE_HUODAO_LEVEL_OPEN      0x0100
#define TYPE_HUODAO_LOGIC      		0x0200

#define TYPE_HUODAO_ALL				0xFFFF

//=====================================================================

unsigned char saveFlash(unsigned int addr,unsigned char *buf,unsigned short len);
unsigned char readFlash(unsigned int addr,unsigned char *buf,unsigned short len);


#endif
