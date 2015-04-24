#ifndef _BOARD_H_
#define _BOARD_H_

#define xdata 


typedef unsigned char 		uint8;
typedef unsigned short 		uint16;
typedef unsigned int 		uint32;
typedef char 				int8;
typedef short 				int16;
typedef int 				int32;



//=============================================================================
//宏函数及表达式
//=============================================================================

#define HUINT16(n)				(uint8)(((n) >> 8) & 0xFF)//16位数值高8位
#define LUINT16(n)				(uint8)((n) & 0xFF)//16位数值低8位	
#define H0UINT32(n)				(uint8)(((n) >> 24) & 0xFF)//32位数值第一个高8位
#define H1UINT32(n)				(uint8)(((n) >> 16) & 0xFF)//32位数值第二个高8位
#define L0UINT32(n)				(uint8)(((n) >> 8) & 0xFF)//32位数值第一个低8位
#define L1UINT32(n)				(uint8)((n) & 0xff)//32位数值第二个低8位

#define INTEG16(h,l)			(uint16)(((uint16)(h) << 8) | ((l) & 0xFF))
//四个unsigned char 数据整合成unsigned int型数据
#define INTEG32(h0,l0,h1,l1)	(uint32)(((uint32)(h0) << 24) | ((uint32)(l0) << 16) | \
										 ((uint32)(h1) << 8) | ((l1) & 0xFF))






//======================================================================================
unsigned char XorCheck(unsigned char *pstr,unsigned short len);
unsigned short CrcCheck(unsigned char *msg, unsigned short len);
void msleep(unsigned int msec);


#endif


/**************************************End Of File*******************************************************/
