/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           MDB.h
** Last modified Date:  2013-01-10
** Last Version:         
** Descriptions:        2*8键盘驱动                     
**------------------------------------------------------------------------------------------------------
** Created by:          sunway
** Created date:        2013-01-08
** Version:             V0.1
** Descriptions:        The original version       
********************************************************************************************************/
#include "..\config.h"

#define	KEYINTERRUPUT	(1ul<<2)

#define KEYROW0	(1ul<<14)		//行0
#define KEYROW1	(1ul<<15)		//行1

#define	KEYCOL0	(1ul<<16)
#define	KEYCOL1	(1ul<<17)
#define	KEYCOL2	(1ul<<4)
#define	KEYCOL3	(1ul<<5)
#define	KEYCOL4	(1ul<<6)
#define	KEYCOL5	(1ul<<7)
#define	KEYCOL6	(1ul<<8)
#define	KEYCOL7	(1ul<<9)

#define KEY_QUEUE_SIZE 5
void *KeyValueQ[KEY_QUEUE_SIZE];
OS_EVENT *QKey;
volatile unsigned char PostValue[5];
unsigned char keyIndex = 0;

void ScanDelayTime(unsigned int ms);
void SetKeyColOutput(void);
void SetKeyColInput(void);
void SetKeyRowOutput(void);
void SetKeyRowInput(void);
unsigned char ReadColValue(void);
unsigned char ReadRowValue(void);
unsigned char ScanKeyBoard(void);

const unsigned char KEY_ROW0_TABLE[8] = {'5','4','8','7','1','2','3','6'};
const unsigned char KEY_ROW1_TABLE[8] = {'>','C','E','D','9','.','0','<'};
/*********************************************************************************************************
* Function Name:        InitKeyboard
* Description:          P2.12中断输入
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void InitKeyboard(void)
{


	DisabaleKeyBoard();
	zyIsrSet(NVIC_EINT2,(unsigned long)EINT2_IsrHandler,PRIO_TEN);	
	EXTINT   = 0x00000007;		//清中断
	EXTMODE	 = KEYINTERRUPUT;	//边沿触发
	EXTPOLAR = 0x00000000;
	SetKeyColOutput();
	SetKeyRowInput();
	
}
/*********************************************************************************************************
* Function Name:        ScanKeyBoard
* Description:          键盘扫描
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void EINT2_IsrHandler(void)
{
	unsigned char err;
	unsigned int i = 5000;
	OSIntEnter();
	PostValue[keyIndex] = ScanKeyBoard();
	if(PostValue[keyIndex] != 0x00)
	{
		err = OSQPost(QKey,(void *)&PostValue[keyIndex]);
		keyIndex = (++keyIndex) %5;
		if(err != OS_NO_ERR)
		{
			while(--i);
			err = OSQPost(QKey,(void *)&PostValue[keyIndex]);
			keyIndex = (++keyIndex) %5;
		}
	}
	SetKeyColOutput();
	SetKeyRowInput();
	EXTINT   = 0x00000007;
    OSIntExit();	
}
/*********************************************************************************************************
* Function Name:        ReadKeyValue
* Description:          键盘API函数：从键盘消息队列中取出案件值并返回该按键值
* Input:                None
* Output:               None
* Return:               按键值
*********************************************************************************************************/
unsigned char ReadKeyValue(void)
{
	unsigned char err;
	unsigned char *PendKey;
	PendKey = (unsigned char *)OSQPend(QKey,10,&err);
	if(err == OS_NO_ERR)
	{
		return *PendKey;
	}
	else
		return 0x00;	
}
/*********************************************************************************************************
* Function Name:        DisabaleKeyBoard
* Description:          P2.12中断输入
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void DisabaleKeyBoard(void)
{
	PINSEL4 |= (P2_12_GPIO<<24);
}
/*********************************************************************************************************
* Function Name:        InitKeyboard
* Description:          P2.12中断输入
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void EnableKeyBoard(void)
{

	QKey = OSQCreate(&KeyValueQ[0],KEY_QUEUE_SIZE);
	PINSEL4 |= (P2_12_EINT2<<24);
	EXTINT   = 0x00000007;	
	EXTMODE	 = KEYINTERRUPUT;
	EXTPOLAR = 0x00000000;
	SetKeyColOutput();
	SetKeyRowInput();
}
/*********************************************************************************************************
* Function Name:        ScanDelayTime
* Description:          软件延时,n个ms
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void ScanDelayTime(unsigned int ms)
{
	unsigned long i,j;
	for(i=0;i<ms;i++)
	{
		for(j=0;j<16500;j++)
		{
			__nop();
		}	
	}
}
/*********************************************************************************************************
* Function Name:        SetKeyColOutput
* Description:          设置列为输出
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void SetKeyColOutput(void)
{
	FIO1DIR |= KEYCOL0; FIO1CLR |= KEYCOL0; 
	FIO1DIR |= KEYCOL1;	FIO1CLR |= KEYCOL1; 
	FIO0DIR |= KEYCOL2; FIO0CLR |= KEYCOL2; 
	FIO0DIR |= KEYCOL3; FIO0CLR |= KEYCOL3; 	
	FIO0DIR |= KEYCOL4; FIO0CLR |= KEYCOL4; 
	FIO0DIR |= KEYCOL5; FIO0CLR |= KEYCOL5; 
	FIO0DIR |= KEYCOL6; FIO0CLR |= KEYCOL6; 
	FIO0DIR |= KEYCOL7; FIO0CLR |= KEYCOL7;
}
/*********************************************************************************************************
* Function Name:        SetKeyColInput
* Description:          设置列为输入
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void SetKeyColInput(void)
{
	unsigned char i;
	FIO1DIR &= (~KEYCOL0); 
	FIO1DIR &= (~KEYCOL1); 
	FIO0DIR &= (~KEYCOL2); 
	FIO0DIR &= (~KEYCOL3); 
	FIO0DIR &= (~KEYCOL4); 
	FIO0DIR &= (~KEYCOL5); 
	FIO0DIR &= (~KEYCOL6); 
	FIO0DIR &= (~KEYCOL7);
	for(i=0;i<100;i++)
	{
		__nop();
	}
}
/*********************************************************************************************************
* Function Name:        SetKeyRowOutput
* Description:          设置行为输出
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void SetKeyRowOutput(void)
{
	FIO1DIR |= KEYROW0; FIO1CLR |= KEYROW0;
	FIO1DIR |= KEYROW1;	FIO1CLR |= KEYROW1;
}
/*********************************************************************************************************
* Function Name:        SetKeyRowInput
* Description:          设置行为输入
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
void SetKeyRowInput(void)
{
	unsigned char i;
	FIO1DIR &= (~KEYROW0);
	FIO1DIR &= (~KEYROW1);
	for(i=0;i<100;i++)
	{
		__nop();
	}
}
/*********************************************************************************************************
* Function Name:        ReadColumVale
* Description:          读取列值
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
unsigned char ReadColValue(void)
{
	unsigned char ColValue;
	unsigned int col,col0,col1;
	col0 = (FIO1PIN & KEYCOL0) | (FIO1PIN & KEYCOL1);
	col0 = (col0>>16);
	col1 = (FIO0PIN & (0x3F<<4));
	col1 = (col1>>2);
	col  = col0|col1;
	ColValue = (unsigned char)col;
	return ColValue;	
}
/*********************************************************************************************************
* Function Name:        ReadRowumVale
* Description:          读取行值
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
unsigned char ReadRowValue(void)
{
	unsigned char RowValue;
	unsigned int Rda;
	Rda = (FIO1PIN & (0x00000003<<14));
	Rda = Rda>>14;
	RowValue = (unsigned char)Rda;
	return RowValue;
}
/*********************************************************************************************************
* Function Name:        ScanKeyBoard
* Description:          键盘扫描
* Input:                None
* Output:               None
* Return:               None
*********************************************************************************************************/
unsigned char ScanKeyBoard(void)
{
	unsigned char i,comp = 0;
	unsigned char RowValue,ColValue;
	ScanDelayTime(5);
	if(((FIO1PIN & KEYROW0) ==0)||((FIO1PIN & KEYROW1) == 0))
	{
		ScanDelayTime(3);
		if(((FIO1PIN & KEYROW0) ==0)||((FIO1PIN & KEYROW1) == 0))
		{
			SetKeyRowOutput();
			SetKeyColInput();
			ColValue = ReadColValue();
			ColValue = (~ColValue);
			SetKeyColOutput();
			SetKeyRowInput();
			RowValue = ReadRowValue();
			if((RowValue >= 0x03)||(RowValue == 0x00))
				return 0x00;
			else
			{
				if(RowValue == 0x01)
				{
					for(i=0;i<8;i++)
					{
						if(ColValue == (1<<i))
						{
							comp = 1;
							break;
						}
						else
							comp = 0;
					}
					if(comp == 1)
					{
						Buzzer();
						return KEY_ROW0_TABLE[i];
					}
					else
						return 0x00;
				}
				if(RowValue == 0x02)
				{
					for(i=0;i<8;i++)
					{
						if(ColValue == (1<<i))
						{
							comp = 1;
							break;
						}
						else
							comp = 0;
					}
					if(comp == 1)
					{
						Buzzer();
						return KEY_ROW1_TABLE[i];
					}
					else
						return 0x00;
				}		
			}	
		}
		else
			return 0x00;
	}
	return 0x00;
}
/*********************************************************************************************************
**				COL0	COL1	COL2	COL3	COL4	COL5	COL6	COL7
**			-----------------------------------------------------------------
** 	ROW0	|	6	  |	  3   |   2   |   1   |	  7	 |   8   |  4    |   5   |
**			-----------------------------------------------------------------
**	ROW1	|	<	  |	  0   |   .   |   9   |	 Clr | Enter |Cancel |   >   |
**			-----------------------------------------------------------------
*********************************************************************************************************/
/**************************************End Of File*******************************************************/
