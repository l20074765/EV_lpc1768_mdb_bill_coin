/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           Uart2.h
** Last modified Date:  2013-01-08
** Last Version:         
** Descriptions:        Uart2驱动程序相关函数声明                     
**------------------------------------------------------------------------------------------------------
** Created by:          sunway
** Created date:        2013-01-08
** Version:             V0.1
** Descriptions:        The original version       
********************************************************************************************************/
#ifndef __UART2_H 
#define __UART2_H

#define  UART_IIR_INTID_RLS		((uint32_t)(3<<1)) 	/*!<Interrupt identification: Receive line status*/
#define  UART_IIR_INTID_RDA		((uint32_t)(2<<1)) 	/*!<Interrupt identification: Receive data available*/
#define  UART_IIR_INTID_CTI		((uint32_t)(6<<1)) 	/*!<Interrupt identification: Character time-out indicator*/
#define  UART_IIR_INTID_MASK		((uint32_t)(7<<1))	/*!<Interrupt identification: Interrupt ID mask */
#define  UART_LSR_OE				((uint8_t)(1<<1)) 	/*!<Line status register: Overrun error*/
#define  UART_LSR_PE				((uint8_t)(1<<2)) 	/*!<Line status register: Parity error*/
#define  UART_LSR_FE				((uint8_t)(1<<3)) 	/*!<Line status register: Framing error*/
#define  UART_LSR_BI				((uint8_t)(1<<4)) 	/*!<Line status register: Break interrupt*/
#define  UART_LSR_THRE			((uint8_t)(1<<5)) 	/*!<Line status register: Transmit holding register empty*/
#define  UART_LSR_TEMT			((uint8_t)(1<<6)) 	/*!<Line status register: Transmitter empty*/
#define  UART_LSR_RXFE			((uint8_t)(1<<7)) 	/*!<Error in RX FIFO*/
#define  UART_RBR_MASKBIT   		((uint8_t)0xFF) 	/*!< UART Received Buffer mask bit (8 bits) */
#define  UART_LCR_WLEN8     		((uint8_t)(3<<0))   /*!< UART 8 bit data mode */
#define  UART_LCR_PARITY_EN		((uint8_t)(1<<3))	/*!< UART Parity Enable */
#define  UART_LCR_PARITY_ODD		((uint8_t)(0))      /*!< UART Odd Parity Select */
#define  UART_LCR_PARITY_EVEN	((uint8_t)(1<<4))	/*!< UART Even Parity Select */

#define  UART_LCR_PARITY_F_1		((uint8_t)(2<<4))	/*!< UART force 1 stick parity */
#define  UART_LCR_PARITY_F_0		((uint8_t)(3<<4))	/*!< UART force 0 stick parity */

#define	 UART2_BPS			9600

#define  MDB_MAX_BLOCK_SIZE 36 				//最大数据块
#define  MDB_ACK 		  	0x00			//应答
#define  MDB_RET 		  	0xAA			//重试
#define  MDB_NAK 		  	0xFF			//无应答

#define  MDB_RCV_START     	0x80			//开始接收MDB数据
#define  MDB_RCV_DATA     	0x81			//正在接收MDB数据
#define  MDB_RCV_OK       	0x82			//MDB数据接收正确
#define  MDB_OUT_RANGE    	0x83			//MDB数据接收超界
#define  MDB_CHKSUM_ERR   	0x84			//MDB数据接收校验出错

#define  MDB_ADD          	1			//MDB地址
#define  MDB_DAT          	0			//MDB数据
#define  RS232_GBA			2			//RS232串口模式

#define  UART2MODESELECT0 	(1<<29)			//P1.29 select as GPIO IN LPC1700PinCfg.h
#define  UART2MODESELECT1 	(1<<28)			//P1.28 select as GPIO IN LPC1700PinCfg.h

#define  UART2_MDB_MODE	  	0
#define  UART2_EVB_MODE	  	1
#define  UART2_BUFLEN     	36
#define  UART2_BPS		  	9600

#define  ERR_STX            0x81			//帧头出错
#define  ERR_ETX            0x82			//帧尾出错
#define  ERR_CHKSUM         0x83			//校验出错
#define  ERR_TIMEOUT        0x84			//超时

#define  PARITY_DIS         0
#define  PARITY_ODD         1
#define  PARITY_EVEN        2
#define  PARITY_F_1         3
#define  PARITY_F_0         4

void InitUart2(void);
void ClrUart2Buff(void);
void SetUart2ParityMode(unsigned char mode);
void MdbPutChr(unsigned char dat,unsigned char mode);
void RS232PutChr(unsigned char dat,unsigned char mode);
void Uart2PutCh(unsigned char dat);
void Uart2PutStr(unsigned char *buf,unsigned char lenth);
unsigned char Uart2GetStr(unsigned char *buf, unsigned char len);
unsigned char GetMdbStatus(void);
void SetMdbStartStatus(void);
void SetUart2MdbMode(void);
void SetUart2Evb1Mode(void);
void SetUart2Evb2Mode(void);
void SetUart2Evb3Mode(void);
void Uart2IsrHandler(void);

#endif
/**************************************End Of File*******************************************************/
