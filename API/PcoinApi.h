#ifndef _P_COIN_API_H_
#define _P_COIN_API_H_
#include "..\Drivers\board.h"


typedef struct _st_pcoin_{
	uint8 isEnable;
	uint32 ch[16];
}ST_PCOIN;

extern ST_PCOIN stPcoin;
uint8 PCOIN_setCh(uint8 no,uint32 value);
void PCOIN_scanSerialPluse(void);
void PCOIN_scanParallelPluse(void);

uint32 PCOIN_costAmount(uint32 amount);
uint32 PCOIN_recvAmount(void);
uint8 PCOIN_initSerialPluse(uint8 high);
uint8 PCOIN_initParallelPluse(uint8 high);
uint8 PCOIN_enableParallelPluse(void);
uint8 PCOIN_disableParallelPluse(void);
uint8 PCOIN_enableSerialPluse(void);
uint8 PCOIN_disableSerialPluse(void);
uint8 PCOIN_isEnable(void);
#endif


/**************************************End Of File*******************************************************/
