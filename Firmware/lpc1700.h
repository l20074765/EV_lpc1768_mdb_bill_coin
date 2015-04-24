/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**
**                                 http://www.embedtools.com
**--------------File Info---------------------------------------------------------------------------------
** File name:			LPC1700.H
** Last modified Date:  2009-05-12
** Last Version:		V1.01
** Descriptions:		lpc1700寄存器地址定义
**
**--------------------------------------------------------------------------------------------------------
** Created by:			Liangbaoqiong
** Created date:		2009-05-12
** Version:				V1.00
** Descriptions:		
**--------------------------------------------------------------------------------------------------------
** Modified by:			Liangbaoqiong
** Modified date:		2009-05-12
** Version:				
** Descriptions:		对程序的风格以及注释略作调整，并检查代码。
*********************************************************************************************************/

#ifndef __IOLPC1700_H
#define __IOLPC1700_H

/*********************************************************************************************************
**  System control block 系统控制模块
*********************************************************************************************************/
#define MEMMAP                  (*(volatile unsigned long *)0x400FC040)
#define EXTINT                  (*(volatile unsigned long *)0x400FC140)
#define EXTMODE                 (*(volatile unsigned long *)0x400FC148)
#define EXTPOLAR                (*(volatile unsigned long *)0x400FC14C)
#define RSID                    (*(volatile unsigned long *)0x400FC180)
#define SCS                     (*(volatile unsigned long *)0x400FC1A0)
#define CLKSRCSEL               (*(volatile unsigned long *)0x400FC10C)
#define PLL0CON                 (*(volatile unsigned long *)0x400FC080)
#define PLL0CFG                 (*(volatile unsigned long *)0x400FC084)
#define PLL0STAT                (*(volatile unsigned long *)0x400FC088)
#define PLL0FEED                (*(volatile unsigned long *)0x400FC08C)
#define PLL1CON                 (*(volatile unsigned long *)0x400FC0A0)
#define PLL1CFG                 (*(volatile unsigned long *)0x400FC0A4)
#define PLL1STAT                (*(volatile unsigned long *)0x400FC0A8)
#define PLL1FEED                (*(volatile unsigned long *)0x400FC0AC)
#define CCLKCFG                 (*(volatile unsigned long *)0x400FC104)
#define USBCLKCFG               (*(volatile unsigned long *)0x400FC108)
#define IRCTRIM                 (*(volatile unsigned long *)0x400FC1A4)
#define PCLKSEL0                (*(volatile unsigned long *)0x400FC1A8)
#define PCLKSEL1                (*(volatile unsigned long *)0x400FC1AC)
#define PCON                    (*(volatile unsigned long *)0x400FC0C0)
#define PCONP                   (*(volatile unsigned long *)0x400FC0C4)
#define CLKOUTCFG               (*(volatile unsigned long *)0x400FC1C8)

/*********************************************************************************************************
**  Flash Accelerator Flash加速器
*********************************************************************************************************/
#define FLASHCFG                (*(volatile unsigned long *)0x400FC000)

/*********************************************************************************************************
**  NVIC嵌套向量中断控制器
*********************************************************************************************************/
#define NVIC                    (*(volatile unsigned long *)0xE000E004)
#define STCTRL                  (*(volatile unsigned long *)0xE000E010)
#define STRELOAD                (*(volatile unsigned long *)0xE000E014)
#define STCURR                  (*(volatile unsigned long *)0xE000E018)
#define STCALIB                 (*(volatile unsigned long *)0xE000E01C)
#define SETENA0                 (*(volatile unsigned long *)0xE000E100)
#define SETENA1                 (*(volatile unsigned long *)0xE000E104)
#define CLRENA0                 (*(volatile unsigned long *)0xE000E180)
#define CLRENA1                 (*(volatile unsigned long *)0xE000E184)
#define SETPEND0                (*(volatile unsigned long *)0xE000E200)
#define SETPEND1                (*(volatile unsigned long *)0xE000E204)
#define CLRPEND0                (*(volatile unsigned long *)0xE000E280)
#define CLRPEND1                (*(volatile unsigned long *)0xE000E284)
#define ACTIVE0                 (*(volatile unsigned long *)0xE000E300)
#define ACTIVE1                 (*(volatile unsigned long *)0xE000E304)
#define IP0                     (*(volatile unsigned long *)0xE000E400)
#define IP1                     (*(volatile unsigned long *)0xE000E404)
#define IP2                     (*(volatile unsigned long *)0xE000E408)
#define IP3                     (*(volatile unsigned long *)0xE000E40C)
#define IP4                     (*(volatile unsigned long *)0xE000E410)
#define IP5                     (*(volatile unsigned long *)0xE000E414)
#define IP6                     (*(volatile unsigned long *)0xE000E418)
#define IP7                     (*(volatile unsigned long *)0xE000E41C)
#define IP8                     (*(volatile unsigned long *)0xE000E420)
#define IP9                     (*(volatile unsigned long *)0xE000E424)
#define IP10                    (*(volatile unsigned long *)0xE000E428)
#define IP11                    (*(volatile unsigned long *)0xE000E42C)
#define IP12                    (*(volatile unsigned long *)0xE000E430)
#define IP13                    (*(volatile unsigned long *)0xE000E434)
#define IP14                    (*(volatile unsigned long *)0xE000E438)
#define IP15                    (*(volatile unsigned long *)0xE000E43C)
#define CPUIDBR                 (*(volatile unsigned long *)0xE000ED00)
#define ICSR                    (*(volatile unsigned long *)0xE000ED04)
#define VTOR                    (*(volatile unsigned long *)0xE000ED08)
#define AITCR                   (*(volatile unsigned long *)0xE000ED0C)
#define SCR                     (*(volatile unsigned long *)0xE000ED10)
#define CCR                     (*(volatile unsigned long *)0xE000ED14)
#define SHPR0                   (*(volatile unsigned long *)0xE000ED18)
#define SHPR1                   (*(volatile unsigned long *)0xE000ED1C)
#define SHPR2                   (*(volatile unsigned long *)0xE000ED20)
#define SHCSR                   (*(volatile unsigned long *)0xE000ED24)
#define CFSR                    (*(volatile unsigned long *)0xE000ED28)
#define HFSR                    (*(volatile unsigned long *)0xE000ED2C)
#define DFSR                    (*(volatile unsigned long *)0xE000ED30)
#define MMFAR                   (*(volatile unsigned long *)0xE000ED34)
#define BFAR                    (*(volatile unsigned long *)0xE000ED38)
#define STIR                    (*(volatile unsigned long *)0xE000EF00)

/*********************************************************************************************************
**  Pin connect block 引脚连接模块
*********************************************************************************************************/
#define PINSEL0                 (*(volatile unsigned long *)0x4002C000)
#define PINSEL1                 (*(volatile unsigned long *)0x4002C004)
#define PINSEL2                 (*(volatile unsigned long *)0x4002C008)
#define PINSEL3                 (*(volatile unsigned long *)0x4002C00C)
#define PINSEL4                 (*(volatile unsigned long *)0x4002C010)
#define PINSEL5                 (*(volatile unsigned long *)0x4002C014)
#define PINSEL6                 (*(volatile unsigned long *)0x4002C018)
#define PINSEL7                 (*(volatile unsigned long *)0x4002C01C)
#define PINSEL8                 (*(volatile unsigned long *)0x4002C020)
#define PINSEL9                 (*(volatile unsigned long *)0x4002C024)
#define PINSEL10                (*(volatile unsigned long *)0x4002C028)
#define PINMODE0                (*(volatile unsigned long *)0x4002C040)
#define PINMODE1                (*(volatile unsigned long *)0x4002C044)
#define PINMODE2                (*(volatile unsigned long *)0x4002C048)
#define PINMODE3                (*(volatile unsigned long *)0x4002C04C)
#define PINMODE4                (*(volatile unsigned long *)0x4002C050)
#define PINMODE5                (*(volatile unsigned long *)0x4002C054)
#define PINMODE6                (*(volatile unsigned long *)0x4002C058)
#define PINMODE7                (*(volatile unsigned long *)0x4002C05C)
#define PINMODE8                (*(volatile unsigned long *)0x4002C060)
#define PINMODE9                (*(volatile unsigned long *)0x4002C064)
#define PINMODE_OD0             (*(volatile unsigned long *)0x4002C068)
#define PINMODE_OD1             (*(volatile unsigned long *)0x4002C06C)
#define PINMODE_OD2             (*(volatile unsigned long *)0x4002C070)
#define PINMODE_OD3             (*(volatile unsigned long *)0x4002C074)
#define PINMODE_OD4             (*(volatile unsigned long *)0x4002C078)
#define I2CPADCFG               (*(volatile unsigned long *)0x4002C07C)

/*********************************************************************************************************
**  GPIO
*********************************************************************************************************/
#define FIO0DIR                 (*(volatile unsigned long *)0x2009c000)
#define FIO0DIR0                (*(volatile unsigned long *)0x2009c000)
#define FIO0DIR1                (*(volatile unsigned long *)0x2009c001)
#define FIO0DIR2                (*(volatile unsigned long *)0x2009c002)
#define FIO0DIR3                (*(volatile unsigned long *)0x2009c003)
#define FIO0DIRL                (*(volatile unsigned long *)0x2009c000)
#define FIO0DIRU                (*(volatile unsigned long *)0x2009c002)

#define FIO0MASK                (*(volatile unsigned long *)0x2009c010)
#define FIO0MASK0               (*(volatile unsigned long *)0x2009c010)
#define FIO0MASK1               (*(volatile unsigned long *)0x2009c011)
#define FIO0MASK2               (*(volatile unsigned long *)0x2009c012)
#define FIO0MASK3               (*(volatile unsigned long *)0x2009c013)
#define FIO0MASKL               (*(volatile unsigned long *)0x2009c010)
#define FIO0MASKU               (*(volatile unsigned long *)0x2009c012)

#define FIO0PIN                 (*(volatile unsigned long *)0x2009c014)
#define FIO0PIN0                (*(volatile unsigned long *)0x2009c014)
#define FIO0PIN1                (*(volatile unsigned long *)0x2009c015)
#define FIO0PIN2                (*(volatile unsigned long *)0x2009c016)
#define FIO0PIN3                (*(volatile unsigned long *)0x2009c017)
#define FIO0PINL                (*(volatile unsigned long *)0x2009c014)
#define FIO0PINU                (*(volatile unsigned long *)0x2009c016)

#define FIO0SET                 (*(volatile unsigned long *)0x2009c018)
#define FIO0SET0                (*(volatile unsigned long *)0x2009c018)
#define FIO0SET1                (*(volatile unsigned long *)0x2009c019)
#define FIO0SET2                (*(volatile unsigned long *)0x2009c01A)
#define FIO0SET3                (*(volatile unsigned long *)0x2009c01B)
#define FIO0SETL                (*(volatile unsigned long *)0x2009c018)
#define FIO0SETU                (*(volatile unsigned long *)0x2009c01A)

#define FIO0CLR                 (*(volatile unsigned long *)0x2009c01c)
#define FIO0CLR0                (*(volatile unsigned long *)0x2009c01c)
#define FIO0CLR1                (*(volatile unsigned long *)0x2009c01D)
#define FIO0CLR2                (*(volatile unsigned long *)0x2009c01E)
#define FIO0CLR3                (*(volatile unsigned long *)0x2009c01F)
#define FIO0CLRL                (*(volatile unsigned long *)0x2009c01c)
#define FIO0CLRU                (*(volatile unsigned long *)0x2009c01E)

#define FIO1DIR                 (*(volatile unsigned long *)0x2009c020)
#define FIO1DIR0                (*(volatile unsigned long *)0x2009c020)
#define FIO1DIR1                (*(volatile unsigned long *)0x2009c021)
#define FIO1DIR2                (*(volatile unsigned long *)0x2009c022)
#define FIO1DIR3                (*(volatile unsigned long *)0x2009c023)
#define FIO1DIRL                (*(volatile unsigned long *)0x2009c020)
#define FIO1DIRU                (*(volatile unsigned long *)0x2009c022)

#define FIO1MASK                (*(volatile unsigned long *)0x2009c030)
#define FIO1MASK0               (*(volatile unsigned long *)0x2009c030)
#define FIO1MASK1               (*(volatile unsigned long *)0x2009c031)
#define FIO1MASK2               (*(volatile unsigned long *)0x2009c032)
#define FIO1MASK3               (*(volatile unsigned long *)0x2009c033)
#define FIO1MASKL               (*(volatile unsigned long *)0x2009c030)
#define FIO1MASKU               (*(volatile unsigned long *)0x2009c032)

#define FIO1PIN                 (*(volatile unsigned long *)0x2009c034)
#define FIO1PIN0                (*(volatile unsigned long *)0x2009c034)
#define FIO1PIN1                (*(volatile unsigned long *)0x2009c035)
#define FIO1PIN2                (*(volatile unsigned long *)0x2009c036)
#define FIO1PIN3                (*(volatile unsigned long *)0x2009c037)
#define FIO1PINL                (*(volatile unsigned long *)0x2009c034)
#define FIO1PINU                (*(volatile unsigned long *)0x2009c036)

#define FIO1SET                 (*(volatile unsigned long *)0x2009c038)
#define FIO1SET0                (*(volatile unsigned long *)0x2009c038)
#define FIO1SET1                (*(volatile unsigned long *)0x2009c039)
#define FIO1SET2                (*(volatile unsigned long *)0x2009c03A)
#define FIO1SET3                (*(volatile unsigned long *)0x2009c03B)
#define FIO1SETL                (*(volatile unsigned long *)0x2009c038)
#define FIO1SETU                (*(volatile unsigned long *)0x2009c03A)

#define FIO1CLR                 (*(volatile unsigned long *)0x2009c03c)
#define FIO1CLR0                (*(volatile unsigned long *)0x2009c03c)
#define FIO1CLR1                (*(volatile unsigned long *)0x2009c03D)
#define FIO1CLR2                (*(volatile unsigned long *)0x2009c03E)
#define FIO1CLR3                (*(volatile unsigned long *)0x2009c03F)
#define FIO1CLRL                (*(volatile unsigned long *)0x2009c03c)
#define FIO1CLRU                (*(volatile unsigned long *)0x2009c03E)

#define FIO2DIR                 (*(volatile unsigned long *)0x2009c040)
#define FIO2DIR0                (*(volatile unsigned long *)0x2009c040)
#define FIO2DIR1                (*(volatile unsigned long *)0x2009c041)
#define FIO2DIR2                (*(volatile unsigned long *)0x2009c042)
#define FIO2DIR3                (*(volatile unsigned long *)0x2009c043)
#define FIO2DIRL                (*(volatile unsigned long *)0x2009c040)
#define FIO2DIRU                (*(volatile unsigned long *)0x2009c042)

#define FIO2MASK                (*(volatile unsigned long *)0x2009c050)
#define FIO2MASK0               (*(volatile unsigned long *)0x2009c050)
#define FIO2MASK1               (*(volatile unsigned long *)0x2009c051)
#define FIO2MASK2               (*(volatile unsigned long *)0x2009c052)
#define FIO2MASK3               (*(volatile unsigned long *)0x2009c053)
#define FIO2MASKL               (*(volatile unsigned long *)0x2009c050)
#define FIO2MASKU               (*(volatile unsigned long *)0x2009c052)

#define FIO2PIN                 (*(volatile unsigned long *)0x2009c054)
#define FIO2PIN0                (*(volatile unsigned long *)0x2009c054)
#define FIO2PIN1                (*(volatile unsigned long *)0x2009c055)
#define FIO2PIN2                (*(volatile unsigned long *)0x2009c056)
#define FIO2PIN3                (*(volatile unsigned long *)0x2009c057)
#define FIO2PINL                (*(volatile unsigned long *)0x2009c054)
#define FIO2PINU                (*(volatile unsigned long *)0x2009c056)

#define FIO2SET                 (*(volatile unsigned long *)0x2009c058)
#define FIO2SET0                (*(volatile unsigned long *)0x2009c058)
#define FIO2SET1                (*(volatile unsigned long *)0x2009c059)
#define FIO2SET2                (*(volatile unsigned long *)0x2009c05A)
#define FIO2SET3                (*(volatile unsigned long *)0x2009c05B)
#define FIO2SETL                (*(volatile unsigned long *)0x2009c058)
#define FIO2SETU                (*(volatile unsigned long *)0x2009c05A)

#define FIO2CLR                 (*(volatile unsigned long *)0x2009c05c)
#define FIO2CLR0                (*(volatile unsigned long *)0x2009c05c)
#define FIO2CLR1                (*(volatile unsigned long *)0x2009c05D)
#define FIO2CLR2                (*(volatile unsigned long *)0x2009c05E)
#define FIO2CLR3                (*(volatile unsigned long *)0x2009c05F)
#define FIO2CLRL                (*(volatile unsigned long *)0x2009c05c)
#define FIO2CLRU                (*(volatile unsigned long *)0x2009c05E)

#define FIO3DIR                 (*(volatile unsigned long *)0x2009c060)
#define FIO3DIR0                (*(volatile unsigned long *)0x2009c060)
#define FIO3DIR1                (*(volatile unsigned long *)0x2009c061)
#define FIO3DIR2                (*(volatile unsigned long *)0x2009c062)
#define FIO3DIR3                (*(volatile unsigned long *)0x2009c063)
#define FIO3DIRL                (*(volatile unsigned long *)0x2009c060)
#define FIO3DIRU                (*(volatile unsigned long *)0x2009c062)
                          
#define FIO3MASK                (*(volatile unsigned long *)0x2009c070)
#define FIO3MASK0               (*(volatile unsigned long *)0x2009c070)
#define FIO3MASK1               (*(volatile unsigned long *)0x2009c071)
#define FIO3MASK2               (*(volatile unsigned long *)0x2009c072)
#define FIO3MASK3               (*(volatile unsigned long *)0x2009c073)
#define FIO3MASKL               (*(volatile unsigned long *)0x2009c070)
#define FIO3MASKU               (*(volatile unsigned long *)0x2009c072)

#define FIO3PIN                 (*(volatile unsigned long *)0x2009c074)
#define FIO3PIN0                (*(volatile unsigned long *)0x2009c074)
#define FIO3PIN1                (*(volatile unsigned long *)0x2009c075)
#define FIO3PIN2                (*(volatile unsigned long *)0x2009c076)
#define FIO3PIN3                (*(volatile unsigned long *)0x2009c077)
#define FIO3PINL                (*(volatile unsigned long *)0x2009c074)
#define FIO3PINU                (*(volatile unsigned long *)0x2009c076)

#define FIO3SET                 (*(volatile unsigned long *)0x2009c078)
#define FIO3SET0                (*(volatile unsigned long *)0x2009c078)
#define FIO3SET1                (*(volatile unsigned long *)0x2009c079)
#define FIO3SET2                (*(volatile unsigned long *)0x2009c07A)
#define FIO3SET3                (*(volatile unsigned long *)0x2009c07B)
#define FIO3SETL                (*(volatile unsigned long *)0x2009c078)
#define FIO3SETU                (*(volatile unsigned long *)0x2009c07A)

#define FIO3CLR                 (*(volatile unsigned long *)0x2009c07c)
#define FIO3CLR0                (*(volatile unsigned long *)0x2009c07c)
#define FIO3CLR1                (*(volatile unsigned long *)0x2009c07D)
#define FIO3CLR2                (*(volatile unsigned long *)0x2009c07E)
#define FIO3CLR3                (*(volatile unsigned long *)0x2009c07F)
#define FIO3CLRL                (*(volatile unsigned long *)0x2009c07c)
#define FIO3CLRU                (*(volatile unsigned long *)0x2009c07E)

#define FIO4DIR                 (*(volatile unsigned long *)0x2009c080)
#define FIO4DIR0                (*(volatile unsigned long *)0x2009c080)
#define FIO4DIR1                (*(volatile unsigned long *)0x2009c081)
#define FIO4DIR2                (*(volatile unsigned long *)0x2009c082)
#define FIO4DIR3                (*(volatile unsigned long *)0x2009c083)
#define FIO4DIRL                (*(volatile unsigned long *)0x2009c080)
#define FIO4DIRU                (*(volatile unsigned long *)0x2009c082)

#define FIO4MASK                (*(volatile unsigned long *)0x2009c090)
#define FIO4MASK0               (*(volatile unsigned long *)0x2009c090)
#define FIO4MASK1               (*(volatile unsigned long *)0x2009c091)
#define FIO4MASK2               (*(volatile unsigned long *)0x2009c092)
#define FIO4MASK3               (*(volatile unsigned long *)0x2009c093)
#define FIO4MASKL               (*(volatile unsigned long *)0x2009c090)
#define FIO4MASKU               (*(volatile unsigned long *)0x2009c092)

#define FIO4PIN                 (*(volatile unsigned long *)0x2009c094)
#define FIO4PIN0                (*(volatile unsigned long *)0x2009c094)
#define FIO4PIN1                (*(volatile unsigned long *)0x2009c095)
#define FIO4PIN2                (*(volatile unsigned long *)0x2009c096)
#define FIO4PIN3                (*(volatile unsigned long *)0x2009c097)
#define FIO4PINL                (*(volatile unsigned long *)0x2009c094)
#define FIO4PINU                (*(volatile unsigned long *)0x2009c096)

#define FIO4SET                 (*(volatile unsigned long *)0x2009c098)
#define FIO4SET0                (*(volatile unsigned long *)0x2009c098)
#define FIO4SET1                (*(volatile unsigned long *)0x2009c099)
#define FIO4SET2                (*(volatile unsigned long *)0x2009c09A)
#define FIO4SET3                (*(volatile unsigned long *)0x2009c09B)
#define FIO4SETL                (*(volatile unsigned long *)0x2009c098)
#define FIO4SETU                (*(volatile unsigned long *)0x2009c09A)

#define FIO4CLR                 (*(volatile unsigned long *)0x2009c09c)
#define FIO4CLR0                (*(volatile unsigned long *)0x2009c09c)
#define FIO4CLR1                (*(volatile unsigned long *)0x2009c09D)
#define FIO4CLR2                (*(volatile unsigned long *)0x2009c09E)
#define FIO4CLR3                (*(volatile unsigned long *)0x2009c09F)
#define FIO4CLRL                (*(volatile unsigned long *)0x2009c09c)
#define FIO4CLRU                (*(volatile unsigned long *)0x2009c09E)

#define IO0IntEnr               (*(volatile unsigned long *)0x40028090)
#define IO0IntEnf               (*(volatile unsigned long *)0x40028094)
#define IO0IntStatr             (*(volatile unsigned long *)0x40028084)
#define IO0IntStatf             (*(volatile unsigned long *)0x40028088)
#define IO0IntClr               (*(volatile unsigned long *)0x4002808C)
#define IO2IntEnr               (*(volatile unsigned long *)0x400280B0)
#define IO2IntEnF               (*(volatile unsigned long *)0x400280B4)
#define IO2IntStatr             (*(volatile unsigned long *)0x400280A4)
#define IO2IntStatF             (*(volatile unsigned long *)0x400280A8)
#define IO2IntClr               (*(volatile unsigned long *)0x400280AC)
#define IOIntStatus             (*(volatile unsigned long *)0x40028080)

/*********************************************************************************************************
**  ETHERNET
*********************************************************************************************************/
#define MAC_MAC1                (*(volatile unsigned long *)0x50000000)
#define MAC_MAC2                (*(volatile unsigned long *)0x50000004)
#define MAC_IPGT                (*(volatile unsigned long *)0x50000008)
#define MAC_IPGR                (*(volatile unsigned long *)0x5000000C)
#define MAC_CLRT                (*(volatile unsigned long *)0x50000010)
#define MAC_MAXF                (*(volatile unsigned long *)0x50000014)
#define MAC_SUPP                (*(volatile unsigned long *)0x50000018)
#define MAC_TEST                (*(volatile unsigned long *)0x5000001C)
#define MAC_MCFG                (*(volatile unsigned long *)0x50000020)
#define MAC_MCMD                (*(volatile unsigned long *)0x50000024)
#define MAC_MADR                (*(volatile unsigned long *)0x50000028)
#define MAC_MWTD                (*(volatile unsigned long *)0x5000002C)
#define MAC_MRDD                (*(volatile unsigned long *)0x50000030)
#define MAC_MIND                (*(volatile unsigned long *)0x50000034)
#define MAC_SA0                 (*(volatile unsigned long *)0x50000040)
#define MAC_SA1                 (*(volatile unsigned long *)0x50000044)
#define MAC_SA2                 (*(volatile unsigned long *)0x50000048)
#define MAC_COMMAND             (*(volatile unsigned long *)0x50000100)
#define MAC_Status              (*(volatile unsigned long *)0x50000104)
#define MAC_RXDESCRIPTOR        (*(volatile unsigned long *)0x50000108)
#define MAC_RXSTATUS            (*(volatile unsigned long *)0x5000010C)
#define MAC_RXDESCRIPTORNUM     (*(volatile unsigned long *)0x50000110)
#define MAC_RXPRODUCEINDEX      (*(volatile unsigned long *)0x50000114)
#define MAC_RXCONSUMEINDEX      (*(volatile unsigned long *)0x50000118)
#define MAC_TXDESCRIPTOR        (*(volatile unsigned long *)0x5000011C)
#define MAC_TXSTATUS            (*(volatile unsigned long *)0x50000120)
#define MAC_TXDESCRIPTORNUM     (*(volatile unsigned long *)0x50000124)
#define MAC_TXPRODUCEINDEX      (*(volatile unsigned long *)0x50000128)
#define MAC_TXCONSUMEINDEX      (*(volatile unsigned long *)0x5000012C)
#define MAC_TSV0                (*(volatile unsigned long *)0x50000158)
#define MAC_TSV1                (*(volatile unsigned long *)0x5000015C)
#define MAC_RSV                 (*(volatile unsigned long *)0x50000160)
#define MAC_FlowControlCounter  (*(volatile unsigned long *)0x50000170)
#define MAC_FlowControlStatus   (*(volatile unsigned long *)0x50000174)
#define MAC_RXFILTERCTRL        (*(volatile unsigned long *)0x50000200)
#define MAC_RxFilterWoLStatus   (*(volatile unsigned long *)0x50000204)
#define MAC_RxFilterWoLClear    (*(volatile unsigned long *)0x50000208)
#define MAC_HashFilterL         (*(volatile unsigned long *)0x50000210)
#define MAC_HashFilterH         (*(volatile unsigned long *)0x50000214)
#define MAC_INTSTATUS           (*(volatile unsigned long *)0x50000FE0)
#define MAC_INTENABLE           (*(volatile unsigned long *)0x50000FE4)
#define MAC_INTCLEAR            (*(volatile unsigned long *)0x50000FE8)
#define MAC_IntSet              (*(volatile unsigned long *)0x50000FEC)
#define MAC_PowerDown           (*(volatile unsigned long *)0x50000FF4)

/*********************************************************************************************************
**  USB
*********************************************************************************************************/
#define USBClkCtrl              (*(volatile unsigned long *)0x5000CFF4)
#define USBClkSt                (*(volatile unsigned long *)0x5000CFF8)
#define USBIntSt                (*(volatile unsigned long *)0x400FC1C0)
#define USBDevIntSt             (*(volatile unsigned long *)0x5000C200)
#define USBDevIntEn             (*(volatile unsigned long *)0x5000C204)
#define USBDevIntClr            (*(volatile unsigned long *)0x5000C208)
#define USBDevIntSet            (*(volatile unsigned long *)0x5000C20C)
#define USBDevIntPri            (*(volatile unsigned long *)0x5000C22C)
#define USBEpIntSt              (*(volatile unsigned long *)0x5000C230)
#define USBEpIntEn              (*(volatile unsigned long *)0x5000C234)
#define USBEpIntClr             (*(volatile unsigned long *)0x5000C238)
#define USBEpIntSet             (*(volatile unsigned long *)0x5000C23C)
#define USBEpIntPri             (*(volatile unsigned long *)0x5000C240)
#define USBReEp                 (*(volatile unsigned long *)0x5000C244)
#define USBEpInd                (*(volatile unsigned long *)0x5000C248)
#define USBMaxPSize             (*(volatile unsigned long *)0x5000C24C)
#define USBRxData               (*(volatile unsigned long *)0x5000C218)
#define USBRxPLen               (*(volatile unsigned long *)0x5000C220)
#define USBTxData               (*(volatile unsigned long *)0x5000C21C)
#define USBTxPLen               (*(volatile unsigned long *)0x5000C224)
#define USBCtrl                 (*(volatile unsigned long *)0x5000C228)
#define USBCmdCode              (*(volatile unsigned long *)0x5000C210)
#define USBCmdData              (*(volatile unsigned long *)0x5000C214)
#define USBDMARSt               (*(volatile unsigned long *)0x5000C250)
#define USBDMARClr              (*(volatile unsigned long *)0x5000C254)
#define USBDMARSet              (*(volatile unsigned long *)0x5000C258)
#define USBUDCAH                (*(volatile unsigned long *)0x5000C280)
#define USBEpDMASt              (*(volatile unsigned long *)0x5000C284)
#define USBEpDMAEn              (*(volatile unsigned long *)0x5000C288)
#define USBEpDMADis             (*(volatile unsigned long *)0x5000C28C)
#define USBDMAIntSt             (*(volatile unsigned long *)0x5000C290)
#define USBDMAIntEn             (*(volatile unsigned long *)0x5000C294)
#define USBEoTIntSt             (*(volatile unsigned long *)0x5000C2A0)
#define USBEoTIntClr            (*(volatile unsigned long *)0x5000C2A4)
#define USBEoTIntSet            (*(volatile unsigned long *)0x5000C2A8)
#define USBNDDRIntSt            (*(volatile unsigned long *)0x5000C2AC)
#define USBNDDRIntClr           (*(volatile unsigned long *)0x5000C2B0)
#define USBNDDRIntSet           (*(volatile unsigned long *)0x5000C2B4)
#define USBSysErrIntSt          (*(volatile unsigned long *)0x5000C2B8)
#define USBSysErrIntClr         (*(volatile unsigned long *)0x5000C2BC)
#define USBSysErrIntSet         (*(volatile unsigned long *)0x5000C2C0)

/*********************************************************************************************************
**  USB HOST (OHCI) CONTROLLER
*********************************************************************************************************/
#define HcRevision              (*(volatile unsigned long *)0x5000C000)
#define HcControl               (*(volatile unsigned long *)0x5000C004)
#define HcCommandStatus         (*(volatile unsigned long *)0x5000C008)
#define HcInterruptStatus       (*(volatile unsigned long *)0x5000C00C)
#define HcInterruptEnable       (*(volatile unsigned long *)0x5000C010)
#define HcInterruptDisable      (*(volatile unsigned long *)0x5000C014)
#define HcHCCA                  (*(volatile unsigned long *)0x5000C018)
#define HcPeriodCurrentED       (*(volatile unsigned long *)0x5000C01C)
#define HcControlHeadED         (*(volatile unsigned long *)0x5000C020)
#define HcControlCurrentED      (*(volatile unsigned long *)0x5000C024)
#define HcBulkHeadED            (*(volatile unsigned long *)0x5000C028)
#define HcBulkCurrentED         (*(volatile unsigned long *)0x5000C02C)
#define HcDoneHead              (*(volatile unsigned long *)0x5000C030)
#define HcFmInterval            (*(volatile unsigned long *)0x5000C034)
#define HcFmRemaining           (*(volatile unsigned long *)0x5000C038)
#define HcFmNumber              (*(volatile unsigned long *)0x5000C03C)
#define HcPeriodicStart         (*(volatile unsigned long *)0x5000C040)
#define HcLSThreshold           (*(volatile unsigned long *)0x5000C044)
#define HcRhDescriptorA         (*(volatile unsigned long *)0x5000C048)
#define HcRhDescriptorB         (*(volatile unsigned long *)0x5000C04C)
#define HcRhStatus              (*(volatile unsigned long *)0x5000C050)
#define HcRhPortStatus1         (*(volatile unsigned long *)0x5000C054)
#define HcRhPortStatus2         (*(volatile unsigned long *)0x5000C058)
#define Module_ID               (*(volatile unsigned long *)0x5000C0FC)

/*********************************************************************************************************
**  USB OTG Controller
*********************************************************************************************************/
#define OTGIntSt                (*(volatile unsigned long *)0x5000C100)
#define OTGIntEn                (*(volatile unsigned long *)0x5000C104)
#define OTGIntSet               (*(volatile unsigned long *)0x5000C108)
#define OTGIntClr               (*(volatile unsigned long *)0x5000C10C)
#define OTGStCtrl               (*(volatile unsigned long *)0x5000C110)
#define OTGTmr                  (*(volatile unsigned long *)0x5000C114)
#define I2C_RX                  (*(volatile unsigned long *)0x5000C300)
#define I2C_TX                  I2C_RX
#define I2C_STS                 (*(volatile unsigned long *)0x5000C304)
#define I2C_CTL                 (*(volatile unsigned long *)0x5000C308)
#define I2C_CLKHI               (*(volatile unsigned long *)0x5000C30C)
#define I2C_CLKLO               (*(volatile unsigned long *)0x5000C310)
#define OTGClkCtrl              USBClkCtrl
#define OTGClkSt                USBClkSt

/*********************************************************************************************************
**  UART0
*********************************************************************************************************/
#define U0RBRTHR                (*(volatile unsigned long *)0x4000C000) /* U0DLL, U0RBR and U0THR       */
#define U0DLL                   U0RBRTHR                                /* share the same address       */
#define U0RBR                   U0RBRTHR
#define U0THR                   U0RBRTHR

#define U0IER                   (*(volatile unsigned long *)0x4000C004) /* U0DLM and U0IER              */
#define U0DLM                   U0IER                                   /* share the same address       */

#define U0FCR                   (*(volatile unsigned long *)0x4000C008) /* U0FCR and U0IIR              */
#define U0IIR                   U0FCR                                   /* share the same address       */

#define U0LCR                   (*(volatile unsigned long *)0x4000C00C)
#define U0LSR                   (*(volatile unsigned long *)0x4000C014)
#define U0SCR                   (*(volatile unsigned long *)0x4000C01C)
#define U0ACR                   (*(volatile unsigned long *)0x4000C020)
#define U0FDR                   (*(volatile unsigned long *)0x4000C028)
#define U0TER                   (*(volatile unsigned long *)0x4000C030)
#define U0FIFOLVL               (*(volatile unsigned long *)0x4000C058)

/*********************************************************************************************************
**  UART1
*********************************************************************************************************/
#define U1RBRTHR                (*(volatile unsigned long *)0x40010000) /* U1DLL, U1RBR and U1THR       */
#define U1DLL                   U1RBRTHR                                /* share the same address       */
#define U1RBR                   U1RBRTHR
#define U1THR                   U1RBRTHR

#define U1IER                   (*(volatile unsigned long *)0x40010004) /* U1DLM and U1IER              */
#define U1DLM                   U1IER                                   /* share the same address       */


#define U1FCR                   (*(volatile unsigned long *)0x40010008) /* U1FCR and U1IIR              */
#define U1IIR                   U1FCR                                   /* share the same address       */

#define U1LCR                   (*(volatile unsigned long *)0x4001000C)
#define U1MCR                   (*(volatile unsigned long *)0x40010010)
#define U1LSR                   (*(volatile unsigned long *)0x40010014)
#define U1MSR                   (*(volatile unsigned long *)0x40010018)
#define U1SCR                   (*(volatile unsigned long *)0x4001001C)
#define U1ACR                   (*(volatile unsigned long *)0x40010020)
#define U1FDR                   (*(volatile unsigned long *)0x40010028)
#define U1TER                   (*(volatile unsigned long *)0x40010030)
#define U1RS485CTRL             (*(volatile unsigned long *)0x4001004C)
#define U1ADRMATCH              (*(volatile unsigned long *)0x40010050)
#define U1RS485DLY              (*(volatile unsigned long *)0x40010054)
#define U1FIFOLVL               (*(volatile unsigned long *)0x40010058)

/*********************************************************************************************************
**  UART2
*********************************************************************************************************/
#define U2RBRTHR                (*(volatile unsigned long *)0x40098000) /* U2DLL, U2RBR and U2THR       */
#define U2DLL                   U2RBRTHR                                /* share the same address       */
#define U2RBR                   U2RBRTHR
#define U2THR                   U2RBRTHR

#define U2IER                   (*(volatile unsigned long *)0x40098004) /* U2DLM and U2IER              */
#define U2DLM                   U2IER                                   /* share the same address       */

#define U2FCR                   (*(volatile unsigned long *)0x40098008) /* U2FCR and U2IIR              */
#define U2IIR                   U2FCR                                   /* share the same address       */

#define U2LCR                   (*(volatile unsigned long *)0x4009800C)
#define U2LSR                   (*(volatile unsigned long *)0x40098014)
#define U2SCR                   (*(volatile unsigned long *)0x4009801C)
#define U2ACR                   (*(volatile unsigned long *)0x40098020)
#define U2FDR                   (*(volatile unsigned long *)0x40098028)
#define U2TER                   (*(volatile unsigned long *)0x40098030)
#define U2FIFOLVL               (*(volatile unsigned long *)0x40098058)

/*********************************************************************************************************
**  UART3
*********************************************************************************************************/
#define U3RBRTHR                (*(volatile unsigned long *)0x4009C000) /* U3DLL, U3RBR and U3THR       */
#define U3DLL                   U3RBRTHR                                /* share the same address       */
#define U3RBR                   U3RBRTHR
#define U3THR                   U3RBRTHR

#define U3IER                   (*(volatile unsigned long *)0x4009C004) /* U3DLM and U3IER              */
#define U3DLM                   U3IER                                   /* share the same address       */
    
#define U3FCR                   (*(volatile unsigned long *)0x4009C008) /* U3FCR and U3IIR              */
#define U3IIR                   U3FCR                                   /* share the same address       */

#define U3LCR                   (*(volatile unsigned long *)0x4009C00C)
#define U3LSR                   (*(volatile unsigned long *)0x4009C014)
#define U3SCR                   (*(volatile unsigned long *)0x4009C01C)
#define U3ACR                   (*(volatile unsigned long *)0x4009C020)
#define U3ICR                   (*(volatile unsigned long *)0x4009C024)
#define U3FDR                   (*(volatile unsigned long *)0x4009C028)
#define U3TER                   (*(volatile unsigned long *)0x4009C030)
#define U3FIFOLVL               (*(volatile unsigned long *)0x4009C058)

/*********************************************************************************************************
**  CAN控制器
*********************************************************************************************************/
#define AFMR                    (*(volatile unsigned long *)0x4003C000)
#define SFF_SA                  (*(volatile unsigned long *)0x4003C004)
#define SFF_GRP_SA              (*(volatile unsigned long *)0x4003C008)
#define EFF_SA                  (*(volatile unsigned long *)0x4003C00C)
#define EFF_GRP_SA              (*(volatile unsigned long *)0x4003C010)
#define ENDOFTABLE              (*(volatile unsigned long *)0x4003C014)
#define LUTERRAD                (*(volatile unsigned long *)0x4003C018)
#define LUTERR                  (*(volatile unsigned long *)0x4003C01C)
#define FCANIE                  (*(volatile unsigned long *)0x4003C020)
#define FCANIC0                 (*(volatile unsigned long *)0x4003C024)
#define FCANIC1                 (*(volatile unsigned long *)0x4003C028)
#define CANTXSR                 (*(volatile unsigned long *)0x40040000)
#define CANRXSR                 (*(volatile unsigned long *)0x40040004)
#define CANMSR                  (*(volatile unsigned long *)0x40040008)
#define CAN1MOD                 (*(volatile unsigned long *)0x40044000)
#define CAN1CMR                 (*(volatile unsigned long *)0x40044004)
#define CAN1GSR                 (*(volatile unsigned long *)0x40044008)
#define CAN1ICR                 (*(volatile unsigned long *)0x4004400C)
#define CAN1IER                 (*(volatile unsigned long *)0x40044010)
#define CAN1BTR                 (*(volatile unsigned long *)0x40044014)
#define CAN1EWL                 (*(volatile unsigned long *)0x40044018)
#define CAN1SR                  (*(volatile unsigned long *)0x4004401C)
#define CAN1RFS                 (*(volatile unsigned long *)0x40044020)
#define CAN1RID                 (*(volatile unsigned long *)0x40044024)
#define CAN1RDA                 (*(volatile unsigned long *)0x40044028)
#define CAN1RDB                 (*(volatile unsigned long *)0x4004402C)
#define CAN1TFI1                (*(volatile unsigned long *)0x40044030)
#define CAN1TID1                (*(volatile unsigned long *)0x40044034)
#define CAN1TDA1                (*(volatile unsigned long *)0x40044038)
#define CAN1TDB1                (*(volatile unsigned long *)0x4004403C)
#define CAN1TFI2                (*(volatile unsigned long *)0x40044040)
#define CAN1TID2                (*(volatile unsigned long *)0x40044044)
#define CAN1TDA2                (*(volatile unsigned long *)0x40044048)
#define CAN1TDB2                (*(volatile unsigned long *)0x4004404C)
#define CAN1TFI3                (*(volatile unsigned long *)0x40044050)
#define CAN1TID3                (*(volatile unsigned long *)0x40044054)
#define CAN1TDA3                (*(volatile unsigned long *)0x40044058)
#define CAN1TDB3                (*(volatile unsigned long *)0x4004405C)
#define CAN2MOD                 (*(volatile unsigned long *)0x40048000)
#define CAN2CMR                 (*(volatile unsigned long *)0x40048004)
#define CAN2GSR                 (*(volatile unsigned long *)0x40048008)
#define CAN2ICR                 (*(volatile unsigned long *)0x4004800C)
#define CAN2IER                 (*(volatile unsigned long *)0x40048010)
#define CAN2BTR                 (*(volatile unsigned long *)0x40048014)
#define CAN2EWL                 (*(volatile unsigned long *)0x40048018)
#define CAN2SR                  (*(volatile unsigned long *)0x4004801C)
#define CAN2RFS                 (*(volatile unsigned long *)0x40048020)
#define CAN2RID                 (*(volatile unsigned long *)0x40048024)
#define CAN2RDA                 (*(volatile unsigned long *)0x40048028)
#define CAN2RDB                 (*(volatile unsigned long *)0x4004802C)
#define CAN2TFI1                (*(volatile unsigned long *)0x40048030)
#define CAN2TID1                (*(volatile unsigned long *)0x40048034)
#define CAN2TDA1                (*(volatile unsigned long *)0x40048038)
#define CAN2TDB1                (*(volatile unsigned long *)0x4004803C)
#define CAN2TFI2                (*(volatile unsigned long *)0x40048040)
#define CAN2TID2                (*(volatile unsigned long *)0x40048044)
#define CAN2TDA2                (*(volatile unsigned long *)0x40048048)
#define CAN2TDB2                (*(volatile unsigned long *)0x4004804C)
#define CAN2TFI3                (*(volatile unsigned long *)0x40048050)
#define AN2TID3                 (*(volatile unsigned long *)0x40048054)
#define CAN2TDA3                (*(volatile unsigned long *)0x40048058)
#define CAN2TDB3                (*(volatile unsigned long *)0x4004805C)

/*********************************************************************************************************
**  SPI
*********************************************************************************************************/
#define S0SPCR                  (*(volatile unsigned long *)0x40020000)
#define S0SPSR                  (*(volatile unsigned long *)0x40020004)
#define S0SPDR                  (*(volatile unsigned long *)0x40020008)
#define S0SPCCR                 (*(volatile unsigned long *)0x4002000C)
#define SPTCR                   (*(volatile unsigned long *)0x40020010)
#define SPTSR                   (*(volatile unsigned long *)0x40020014)
#define S0SPINT                 (*(volatile unsigned long *)0x4002001C)

/*********************************************************************************************************
**  SSP0
*********************************************************************************************************/
#define SSP0CR0                 (*(volatile unsigned long *)0x40088000)
#define SSP0CR1                 (*(volatile unsigned long *)0x40088004)
#define SSP0DR                  (*(volatile unsigned long *)0x40088008)
#define SSP0SR                  (*(volatile unsigned long *)0x4008800C)
#define SSP0CPSR                (*(volatile unsigned long *)0x40088010)
#define SSP0IMSC                (*(volatile unsigned long *)0x40088014)
#define SSP0RIS                 (*(volatile unsigned long *)0x40088018)
#define SSP0MIS                 (*(volatile unsigned long *)0x4008801C)
#define SSP0ICR                 (*(volatile unsigned long *)0x40088020)
#define SSP0DMACR               (*(volatile unsigned long *)0x40088024)

/*********************************************************************************************************
**  SSP1
*********************************************************************************************************/
#define SSP1CR0                 (*(volatile unsigned long *)0x40030000)
#define SSP1CR1                 (*(volatile unsigned long *)0x40030004)
#define SSP1DR                  (*(volatile unsigned long *)0x40030008)
#define SSP1SR                  (*(volatile unsigned long *)0x4003000C)
#define SSP1CPSR                (*(volatile unsigned long *)0x40030010)
#define SSP1IMSC                (*(volatile unsigned long *)0x40030014)
#define SSP1RIS                 (*(volatile unsigned long *)0x40030018)
#define SSP1MIS                 (*(volatile unsigned long *)0x4003001C)
#define SSP1ICR                 (*(volatile unsigned long *)0x40030020)
#define SSP1DMACR               (*(volatile unsigned long *)0x40030024)

/*********************************************************************************************************
**  I2C0
*********************************************************************************************************/
#define I2C0CONSET              (*(volatile unsigned long *)0x4001C000)
#define I2C0STAT                (*(volatile unsigned long *)0x4001C004)
#define I2C0DAT                 (*(volatile unsigned long *)0x4001C008)
#define I2C0ADR                 (*(volatile unsigned long *)0x4001C00C)
#define I2C0SCLH                (*(volatile unsigned long *)0x4001C010)
#define I2C0SCLL                (*(volatile unsigned long *)0x4001C014)
#define I2C0CONCLR              (*(volatile unsigned long *)0x4001C018)
#define I2C0MMCTRL              (*(volatile unsigned long *)0x4001C01C)
#define I2C0ADR1                (*(volatile unsigned long *)0x4001C020)
#define I2C0ADR2                (*(volatile unsigned long *)0x4001C024)
#define I2C0ADR3                (*(volatile unsigned long *)0x4001C028)
#define I2C0DATABUFFER          (*(volatile unsigned long *)0x4001C02C)
#define I2C0MASK0               (*(volatile unsigned long *)0x4001C030)
#define I2C0MASK1               (*(volatile unsigned long *)0x4001C034)
#define I2C0MASK2               (*(volatile unsigned long *)0x4001C038)
#define I2C0MASK3               (*(volatile unsigned long *)0x4001C03C)

/*********************************************************************************************************
**  I2C1
*********************************************************************************************************/
#define I2C1CONSET              (*(volatile unsigned long *)0x4005C000)
#define I2C1STAT                (*(volatile unsigned long *)0x4005C004)
#define I2C1DAT                 (*(volatile unsigned long *)0x4005C008)
#define I2C1ADR                 (*(volatile unsigned long *)0x4005C00C)
#define I2C1SCLH                (*(volatile unsigned long *)0x4005C010)
#define I2C1SCLL                (*(volatile unsigned long *)0x4005C014)
#define I2C1CONCLR              (*(volatile unsigned long *)0x4005C018)
#define I2C1MMCTRL              (*(volatile unsigned long *)0x4005C01C)
#define I2C1ADR1                (*(volatile unsigned long *)0x4005C020)
#define I2C1ADR2                (*(volatile unsigned long *)0x4005C024)
#define I2C1ADR3                (*(volatile unsigned long *)0x4005C028)
#define I2C1DATABUFFER          (*(volatile unsigned long *)0x4005C02C)
#define I2C1MASK0               (*(volatile unsigned long *)0x4005C030)
#define I2C1MASK1               (*(volatile unsigned long *)0x4005C034)
#define I2C1MASK2               (*(volatile unsigned long *)0x4005C038)
#define I2C1MASK3               (*(volatile unsigned long *)0x4005C03C)

/*********************************************************************************************************
**  I2C2
*********************************************************************************************************/
#define I2C2CONSET              (*(volatile unsigned long *)0x400A0000)
#define I2C2STAT                (*(volatile unsigned long *)0x400A0004)
#define I2C2DAT                 (*(volatile unsigned long *)0x400A0008)
#define I2C2ADR                 (*(volatile unsigned long *)0x400A000C)
#define I2C2SCLH                (*(volatile unsigned long *)0x400A0010)
#define I2C2SCLL                (*(volatile unsigned long *)0x400A0014)
#define I2C2CONCLR              (*(volatile unsigned long *)0x400A0018)
#define I2C2MMCTRL              (*(volatile unsigned long *)0x400A001C)
#define I2C2ADR1                (*(volatile unsigned long *)0x400A0020)
#define I2C2ADR2                (*(volatile unsigned long *)0x400A0024)
#define I2C2ADR3                (*(volatile unsigned long *)0x400A0028)
#define I2C2DATABUFFER          (*(volatile unsigned long *)0x400A002C)
#define I2C2MASK0               (*(volatile unsigned long *)0x400A0030)
#define I2C2MASK1               (*(volatile unsigned long *)0x400A0034)
#define I2C2MASK2               (*(volatile unsigned long *)0x400A0038)
#define I2C2MASK3               (*(volatile unsigned long *)0x400A003C)

/*********************************************************************************************************
**  I2S
*********************************************************************************************************/
#define I2SDAO                  (*(volatile unsigned long *)0x400A8000)
#define I2SDAI                  (*(volatile unsigned long *)0x400A8004)
#define I2STXFIFO               (*(volatile unsigned long *)0x400A8008)
#define I2SRXFIFO               (*(volatile unsigned long *)0x400A800C)
#define I2SSTATE                (*(volatile unsigned long *)0x400A8010)
#define I2SDMA1                 (*(volatile unsigned long *)0x400A8014)
#define I2SDMA2                 (*(volatile unsigned long *)0x400A8018)
#define I2SIRQ                  (*(volatile unsigned long *)0x400A801C)
#define I2STXRATE               (*(volatile unsigned long *)0x400A8020)
#define I2SRXRATE               (*(volatile unsigned long *)0x400A8024)
#define I2STXBITRATE            (*(volatile unsigned long *)0x400A8028)
#define I2SRXBITRATE            (*(volatile unsigned long *)0x400A802C)
#define I2STXMODE               (*(volatile unsigned long *)0x400A8030)
#define I2SRXMODE               (*(volatile unsigned long *)0x400A8034)

/*********************************************************************************************************
**  TIMER0
*********************************************************************************************************/
#define T0IR                    (*(volatile unsigned long *)0x40004000)
#define T0TCR                   (*(volatile unsigned long *)0x40004004)
#define T0TC                    (*(volatile unsigned long *)0x40004008)
#define T0PR                    (*(volatile unsigned long *)0x4000400C)
#define T0PC                    (*(volatile unsigned long *)0x40004010)
#define T0MCR                   (*(volatile unsigned long *)0x40004014)
#define T0MR0                   (*(volatile unsigned long *)0x40004018)
#define T0MR1                   (*(volatile unsigned long *)0x4000401C)
#define T0MR2                   (*(volatile unsigned long *)0x40004020)
#define T0MR3                   (*(volatile unsigned long *)0x40004024)
#define T0CCR                   (*(volatile unsigned long *)0x40004028)
#define T0CR0                   (*(volatile unsigned long *)0x4000402C)
#define T0CR1                   (*(volatile unsigned long *)0x40004030)
#define T0EMR                   (*(volatile unsigned long *)0x4000403C)
#define T0CTCR                  (*(volatile unsigned long *)0x40004070)

/*********************************************************************************************************
**  TIMER1
*********************************************************************************************************/
#define T1IR                    (*(volatile unsigned long *)0x40008000)
#define T1TCR                   (*(volatile unsigned long *)0x40008004)
#define T1TC                    (*(volatile unsigned long *)0x40008008)
#define T1PR                    (*(volatile unsigned long *)0x4000800C)
#define T1PC                    (*(volatile unsigned long *)0x40008010)
#define T1MCR                   (*(volatile unsigned long *)0x40008014)
#define T1MR0                   (*(volatile unsigned long *)0x40008018)
#define T1MR1                   (*(volatile unsigned long *)0x4000801C)
#define T1MR2                   (*(volatile unsigned long *)0x40008020)
#define T1MR3                   (*(volatile unsigned long *)0x40008024)
#define T1CCR                   (*(volatile unsigned long *)0x40008028)
#define T1CR0                   (*(volatile unsigned long *)0x4000802C)
#define T1CR1                   (*(volatile unsigned long *)0x40008030)
#define T1EMR                   (*(volatile unsigned long *)0x4000803C)
#define T1CTCR                  (*(volatile unsigned long *)0x40008070)

/*********************************************************************************************************
**  TIMER2
*********************************************************************************************************/
#define T2IR                    (*(volatile unsigned long *)0x40090000)
#define T2TCR                   (*(volatile unsigned long *)0x40090004)
#define T2TC                    (*(volatile unsigned long *)0x40090008)
#define T2PR                    (*(volatile unsigned long *)0x4009000C)
#define T2PC                    (*(volatile unsigned long *)0x40090010)
#define T2MCR                   (*(volatile unsigned long *)0x40090014)
#define T2MR0                   (*(volatile unsigned long *)0x40090018)
#define T2MR1                   (*(volatile unsigned long *)0x4009001C)
#define T2MR2                   (*(volatile unsigned long *)0x40090020)
#define T2MR3                   (*(volatile unsigned long *)0x40090024)
#define T2CCR                   (*(volatile unsigned long *)0x40090028)
#define T2CR0                   (*(volatile unsigned long *)0x4009002C)
#define T2CR1                   (*(volatile unsigned long *)0x40090030)
#define T2EMR                   (*(volatile unsigned long *)0x4009003C)
#define T2CTCR                  (*(volatile unsigned long *)0x40090070)

/*********************************************************************************************************
**  TIMER3
*********************************************************************************************************/
#define T3IR                    (*(volatile unsigned long *)0x40094000)
#define T3TCR                   (*(volatile unsigned long *)0x40094004)
#define T3TC                    (*(volatile unsigned long *)0x40094008)
#define T3PR                    (*(volatile unsigned long *)0x4009400C)
#define T3PC                    (*(volatile unsigned long *)0x40094010)
#define T3MCR                   (*(volatile unsigned long *)0x40094014)
#define T3MR0                   (*(volatile unsigned long *)0x40094018)
#define T3MR1                   (*(volatile unsigned long *)0x4009401C)
#define T3MR2                   (*(volatile unsigned long *)0x40094020)
#define T3MR3                   (*(volatile unsigned long *)0x40094024)
#define T3CCR                   (*(volatile unsigned long *)0x40094028)
#define T3CR0                   (*(volatile unsigned long *)0x4009402C)
#define T3CR1                   (*(volatile unsigned long *)0x40094030)
#define T3EMR                   (*(volatile unsigned long *)0x4009403C)
#define T3CTCR                  (*(volatile unsigned long *)0x40094070)
                        
/*********************************************************************************************************
**  Repetitive Interrupt Timer 可重复性中断控制器
*********************************************************************************************************/
#define RICOMPVAL               (*(volatile unsigned long *)0x400B0000)
#define RIMASK                  (*(volatile unsigned long *)0x400B0004)
#define RICTRL                  (*(volatile unsigned long *)0x400B0008)
#define RICOUNTER               (*(volatile unsigned long *)0x400B000C)
                         
/*********************************************************************************************************
**  PWM1
*********************************************************************************************************/
#define PWM1IR                  (*(volatile unsigned long *)0x40018000)
#define PWM1TCR                 (*(volatile unsigned long *)0x40018004)
#define PWM1TC                  (*(volatile unsigned long *)0x40018008)
#define PWM1PR                  (*(volatile unsigned long *)0x4001800C)
#define PWM1PC                  (*(volatile unsigned long *)0x40018010)
#define PWM1MCR                 (*(volatile unsigned long *)0x40018014)
#define PWM1MR0                 (*(volatile unsigned long *)0x40018018)
#define PWM1MR1                 (*(volatile unsigned long *)0x4001801C)
#define PWM1MR2                 (*(volatile unsigned long *)0x40018020)
#define PWM1MR3                 (*(volatile unsigned long *)0x40018024)
#define PWM1CCR                 (*(volatile unsigned long *)0x40018028)
#define PWM1CR0                 (*(volatile unsigned long *)0x4001802C)
#define PWM1CR1                 (*(volatile unsigned long *)0x40018030)
#define PWM1MR4                 (*(volatile unsigned long *)0x40018040)
#define PWM1MR5                 (*(volatile unsigned long *)0x40018044)
#define PWM1MR6                 (*(volatile unsigned long *)0x40018048)
#define PWM1PCR                 (*(volatile unsigned long *)0x4001804C)
#define PWM1LER                 (*(volatile unsigned long *)0x40018050)
#define PWM1CTCR                (*(volatile unsigned long *)0x40018070)

/*********************************************************************************************************
**  Motor control PWM
*********************************************************************************************************/
#define MCCON                   (*(volatile unsigned long *)0x400B8000)
#define MCCON_SET               (*(volatile unsigned long *)0x400B8004)
#define MCCON_CLR               (*(volatile unsigned long *)0x400B8008)
#define MCCAPCON                (*(volatile unsigned long *)0x400B800C)
#define MCCAPCON_SET            (*(volatile unsigned long *)0x400B8010)
#define MCCAPCON_CLR            (*(volatile unsigned long *)0x400B8014)
#define MCTC0                   (*(volatile unsigned long *)0x400B8018)
#define MCTC1                   (*(volatile unsigned long *)0x400B801C)
#define MCTC2                   (*(volatile unsigned long *)0x400B8020)
#define MCLIM0                  (*(volatile unsigned long *)0x400B8024)
#define MCLIM1                  (*(volatile unsigned long *)0x400B8028)
#define MCLIM2                  (*(volatile unsigned long *)0x400B802C)
#define MCMAT0                  (*(volatile unsigned long *)0x400B8030)
#define MCMAT1                  (*(volatile unsigned long *)0x400B8034)
#define MCMAT2                  (*(volatile unsigned long *)0x400B8038)
#define MCDT                    (*(volatile unsigned long *)0x400B803C)
#define MCCP                    (*(volatile unsigned long *)0x400B8040)
#define MCCR0                   (*(volatile unsigned long *)0x400B8044)
#define MCCR1                   (*(volatile unsigned long *)0x400B8048)
#define CCR2                    (*(volatile unsigned long *)0x400B804C)
#define MCINTEN                 (*(volatile unsigned long *)0x400B8050)
#define MCINTEN_SET             (*(volatile unsigned long *)0x400B8054)
#define MCINTEN_CLR             (*(volatile unsigned long *)0x400B8058)
#define MCCNTCON                (*(volatile unsigned long *)0x400B805C)
#define MCCNTCON_SET            (*(volatile unsigned long *)0x400B8060)
#define MCCNTCON_CLR            (*(volatile unsigned long *)0x400B8064)
#define MCINTFLAG               (*(volatile unsigned long *)0x400B8068)
#define MCINTFLAG_SET           (*(volatile unsigned long *)0x400B806C)
#define MCINTFLAG_CLR           (*(volatile unsigned long *)0x400B8070)
#define MCCAP_CLR               (*(volatile unsigned long *)0x400B8074)

/*********************************************************************************************************
**  Quadrature Encoder Interface
*********************************************************************************************************/
#define QEICON                  (*(volatile unsigned long *)0x400BC000)
#define QEISTAT                 (*(volatile unsigned long *)0x400BC004)
#define QEICONF                 (*(volatile unsigned long *)0x400BC008)
#define QEIPOS                  (*(volatile unsigned long *)0x400BC00C)
#define QEIMAXPSOS              (*(volatile unsigned long *)0x400BC010)
#define CMPOS0                  (*(volatile unsigned long *)0x400BC014)
#define CMPOS1                  (*(volatile unsigned long *)0x400BC018)
#define CMPOS2                  (*(volatile unsigned long *)0x400BC01C)
#define INXCNT                  (*(volatile unsigned long *)0x400BC020)
#define INXCMP                  (*(volatile unsigned long *)0x400BC024)
#define QEILOAD                 (*(volatile unsigned long *)0x400BC028)
#define QEITIME                 (*(volatile unsigned long *)0x400BC02C)
#define QEIVEL                  (*(volatile unsigned long *)0x400BC030)
#define QEICAP                  (*(volatile unsigned long *)0x400BC034)
#define VELCOMP                 (*(volatile unsigned long *)0x400BC038)
#define FILTER                  (*(volatile unsigned long *)0x400BC03C)
#define QEIIES                  (*(volatile unsigned long *)0x400BCFDC)
#define QEIIEC                  (*(volatile unsigned long *)0x400BCFD8)
#define QEIINTSTAT              (*(volatile unsigned long *)0x400BCFE0)
#define QEIIE                   (*(volatile unsigned long *)0x400BCFE4)
#define QEICLR                  (*(volatile unsigned long *)0x400BCFE8)
#define QEISET                  (*(volatile unsigned long *)0x400BCFEC)

/*********************************************************************************************************
**  RTC
*********************************************************************************************************/
#define RTCILR                  (*(volatile unsigned long *)0x40024000)
#define RTCCCR                  (*(volatile unsigned long *)0x40024008)
#define RTCCIIR                 (*(volatile unsigned long *)0x4002400C)
#define RTCAMR                  (*(volatile unsigned long *)0x40024010)
#define RTCCTIME0               (*(volatile unsigned long *)0x40024014)
#define RTCCTIME1               (*(volatile unsigned long *)0x40024018)
#define RTCCTIME2               (*(volatile unsigned long *)0x4002401C)
#define RTCSEC                  (*(volatile unsigned long *)0x40024020)
#define RTCMIN                  (*(volatile unsigned long *)0x40024024)
#define RTCHOUR                 (*(volatile unsigned long *)0x40024028)
#define RTCDOM                  (*(volatile unsigned long *)0x4002402C)
#define RTCDOW                  (*(volatile unsigned long *)0x40024030)
#define RTCDOY                  (*(volatile unsigned long *)0x40024034)
#define RTCMONTH                (*(volatile unsigned long *)0x40024038)
#define RTCYEAR                 (*(volatile unsigned long *)0x4002403C)
#define RTCCALIBRATION          (*(volatile unsigned long *)0x40024040)
#define RTCGPREG0               (*(volatile unsigned long *)0x40024044)
#define RTCGPREG1               (*(volatile unsigned long *)0x40024048)
#define RTCGPREG2               (*(volatile unsigned long *)0x4002404C)
#define RTCGPREG3               (*(volatile unsigned long *)0x40024050)
#define RTCGPREG4               (*(volatile unsigned long *)0x40024054)
#define RTCALSEC                (*(volatile unsigned long *)0x40024060)
#define RTCALMIN                (*(volatile unsigned long *)0x40024064)
#define RTCALHOUR               (*(volatile unsigned long *)0x40024068)
#define RTCALDOM                (*(volatile unsigned long *)0x4002406C)
#define RTCALDOW                (*(volatile unsigned long *)0x40024070)
#define RTCALDOY                (*(volatile unsigned long *)0x40024074)
#define RTCALMON                (*(volatile unsigned long *)0x40024078)
#define RTCALYEAR               (*(volatile unsigned long *)0x4002407C)
#define RTC_AUX                 (*(volatile unsigned long *)0x4002405c)
#define RTC_AUXEN               (*(volatile unsigned long *)0x40024058)

/*********************************************************************************************************
**  Watchdog
*********************************************************************************************************/
#define WDMOD                   (*(volatile unsigned long *)0x40000000)
#define WDTC                    (*(volatile unsigned long *)0x40000004)
#define WDFEED                  (*(volatile unsigned long *)0x40000008)
#define WDTV                    (*(volatile unsigned long *)0x4000000C)
#define WDCLKSEL                (*(volatile unsigned long *)0x40000010)

/*********************************************************************************************************
**  A/D Converters
*********************************************************************************************************/
#define AD0CR                   (*(volatile unsigned long *)0x40034000)
#define AD0GDR                  (*(volatile unsigned long *)0x40034004)
#define ADINTEN                 (*(volatile unsigned long *)0x4003400C)
#define ADDR0                   (*(volatile unsigned long *)0x40034010)
#define ADDR1                   (*(volatile unsigned long *)0x40034014)
#define ADDR2                   (*(volatile unsigned long *)0x40034018)
#define ADDR3                   (*(volatile unsigned long *)0x4003401C)
#define ADDR4                   (*(volatile unsigned long *)0x40034020)
#define ADDR5                   (*(volatile unsigned long *)0x40034024)
#define ADDR6                   (*(volatile unsigned long *)0x40034028)
#define ADDR7                   (*(volatile unsigned long *)0x4003402C)
#define ADSTAT                  (*(volatile unsigned long *)0x40034030)
#define ADTRM                   (*(volatile unsigned long *)0x40034034)

/*********************************************************************************************************
**  D/A Converter
*********************************************************************************************************/
#define DACR                    (*(volatile unsigned long *)0x4008C000)
#define DACCTRL                 (*(volatile unsigned long *)0x4008C004)
#define DACCNTVAL               (*(volatile unsigned long *)0x4008C008)

/*********************************************************************************************************
**  GPDMA
*********************************************************************************************************/
#define DMACIntStat             (*(volatile unsigned long *)0x50004000)
#define DMACIntTCStat           (*(volatile unsigned long *)0x50004004)
#define DMACIntTCClear          (*(volatile unsigned long *)0x50004008)
#define DMACIntErrStat          (*(volatile unsigned long *)0x5000400C)
#define DMACIntErrClr           (*(volatile unsigned long *)0x50004010)
#define DMACRawIntTCStat        (*(volatile unsigned long *)0x50004014)
#define DMACRawIntErrStat       (*(volatile unsigned long *)0x50004018)
#define DMACEnbldChns           (*(volatile unsigned long *)0x5000401C)
#define DMACSoftBReq            (*(volatile unsigned long *)0x50004020)
#define DMACSoftSReq            (*(volatile unsigned long *)0x50004024)
#define DMACSoftLBReq           (*(volatile unsigned long *)0x50004028)
#define DMACSoftLSReq           (*(volatile unsigned long *)0x5000402C)
#define DMACConfig              (*(volatile unsigned long *)0x50004030)
#define DMACSync                (*(volatile unsigned long *)0x50004034)
#define DMACC0SrcAddr           (*(volatile unsigned long *)0x50004100)
#define DMACC0DestAddr          (*(volatile unsigned long *)0x50004104)
#define DMACC0LLI               (*(volatile unsigned long *)0x50004108)
#define DMACC0Control           (*(volatile unsigned long *)0x5000410C)
#define DMACC0Config            (*(volatile unsigned long *)0x50004110)
#define DMACC1SrcAddr           (*(volatile unsigned long *)0x50004120)
#define DMACC1DestAddr          (*(volatile unsigned long *)0x50004124)
#define DMACC1LLI               (*(volatile unsigned long *)0x50004128)
#define DMACC1Control           (*(volatile unsigned long *)0x5000412C)
#define DMACC1Config            (*(volatile unsigned long *)0x50004130)
#define DMACC2SrcAddr           (*(volatile unsigned long *)0x50004140)
#define DMACC2DestAddr          (*(volatile unsigned long *)0x50004144)
#define DMACC2LLI               (*(volatile unsigned long *)0x50004148)
#define DMACC2Control           (*(volatile unsigned long *)0x5000414C)
#define DMACC2Config            (*(volatile unsigned long *)0x50004150)
#define DMACC3SrcAddr           (*(volatile unsigned long *)0x50004160)
#define DMACC3DestAddr          (*(volatile unsigned long *)0x50004164)
#define MACC3LLI                (*(volatile unsigned long *)0x50004168)
#define DMACC3Control           (*(volatile unsigned long *)0x5000416C)
#define DMACC3Config            (*(volatile unsigned long *)0x50004170)
#define DMACC4SrcAddr           (*(volatile unsigned long *)0x50004180)
#define DMACC4DestAddr          (*(volatile unsigned long *)0x50004184)
#define DMACC4LLI               (*(volatile unsigned long *)0x50004188)
#define DMACC4Control           (*(volatile unsigned long *)0x5000418C)
#define DMACC4Config            (*(volatile unsigned long *)0x50004190)
#define DMACC5SrcAddr           (*(volatile unsigned long *)0x500041A0)
#define MACC5DestAddr           (*(volatile unsigned long *)0x500041A4)
#define DMACC5LLI               (*(volatile unsigned long *)0x500041A8)
#define DMACC5Control           (*(volatile unsigned long *)0x500041AC)
#define DMACC5Config            (*(volatile unsigned long *)0x500041B0)
#define DMACC6SrcAddr           (*(volatile unsigned long *)0x500041C0)
#define DMACC6DestAddr          (*(volatile unsigned long *)0x500041C4)
#define DMACC6LLI               (*(volatile unsigned long *)0x500041C8)
#define DMACC6Control           (*(volatile unsigned long *)0x500041CC)
#define DMACC6Config            (*(volatile unsigned long *)0x500041D0)
#define DMACC7SrcAddr           (*(volatile unsigned long *)0x500041E0)
#define DMACC7DestAddr          (*(volatile unsigned long *)0x500041E4)
#define DMACC7LLI               (*(volatile unsigned long *)0x500041E8)
#define DMACC7Control           (*(volatile unsigned long *)0x500041EC)
#define DMACC7Config            (*(volatile unsigned long *)0x500041F0)

/*********************************************************************************************************
**  GPDMA Controller peripheral devices lines GPDMA 外围设备控制通道号
*********************************************************************************************************/
#define GPDMA_SSP0TX            0                                       /* SPI0 Tx                      */
#define GPDMA_SSP0RX            1                                       /* SPI0 Rx                      */
#define GPDMA_SSP1TX            2                                       /* SPI1 Tx                      */
#define GPDMA_SSP1RX            3                                       /* SPI1 Rx                      */
#define GPDMA_ADC               4                                       /* ADC                          */
#define GPDMA_I2S0              5                                       /* I2S Channel 0                */
#define GPDMA_I2S1              6                                       /* I2S Channel 1                */
#define GPDMA_DAC               7                                       /* ADC                          */
#define GPDMA_U0TX_MAT0_0       8                                       /* UART 0 Tx/MAT0.0             */
#define GPDMA_U0RX_MAT0_1       9                                       /* UART 0 Rx/MAT0.1             */
#define GPDMA_U1TX_MAT1_0      10                                       /* UART 1 Tx/MAT1.0             */
#define GPDMA_U1RX_MAT1_1      11                                       /* UART 1 Rx/MAT1.1             */
#define GPDMA_U2TX_MAT2_0      12                                       /* UART 2 Tx/MAT2.0             */
#define GPDMA_U2RX_MAT2_1      13                                       /* UART 2 Rx/MAT2.1             */
#define GPDMA_U3TX_MAT3_0      14                                       /* UART 3 Tx/MAT3.0             */
#define GPDMA_U3RX_MAT3_1      15                                       /* UART 3 Rx/MAT3.1             */

/*********************************************************************************************************
**  NVIC Interrupt channels  NVIC中断控制通道号
*********************************************************************************************************/
#define MAIN_STACK             0                                        /* Main Stack                   */
#define RESETI                 1                                        /* Reset                                                  */
#define NMII                   2                                        /* Non-maskable Interrupt       */
#define HFI                    3                                        /* Hard Fault                                             */
#define MMI                    4                                        /* Memory Management            */
#define BFI                    5                                        /* Bus Fault                                              */
#define UFI                    6                                        /* Usage Fault                  */
#define SVCI                  11                                        /* SVCall                       */
#define DMI                   12                                        /* Debug Monitor                */
#define PSI                   14                                        /* PendSV                       */
#define STI                   15                                        /* SysTick                      */
#define NVIC_WDT              16                                        /* Watchdog Interrupt (WDINT)   */
#define NVIC_TIMER0           17                                        /* Match 0-1(MR0, MR1),         */
                                                                        /* Capture 0-1(CR0, CR1)        */
#define NVIC_TIMER1           18                                        /* Match 0 - 2 (MR0, MR1, MR2), */
                                                                        /* Capture 0 - 1 (CR0, CR1)     */
#define NVIC_TIMER2           19                                        /* Match 0-3, Capture 0-1       */
#define NVIC_TIMER3           20                                        /* Match 0-3, Capture 0-1       */
#define NVIC_UART0            21                                        /* UART0                        */
#define NVIC_UART1            22                                        /* UART1                        */
#define NVIC_UART2            23                                        /* UART2                        */
#define NVIC_UART3            24                                        /* UART3                        */
#define NVIC_PWM1             25                                        /* Match 0 - 6 of PWM1,         */
                                                                        /* Capture 0-1 of PWM1          */
#define NVIC_I2C0             26                                        /* SI (state change)            */
#define NVIC_I2C1             27                                        /* SI (state change)            */
#define NVIC_I2C2             28                                        /* SI (state change)            */
#define NVIC_SPI              29                                        /* SPI Interrupt Flag (SPIF),   */
                                                                        /* Mode Fault (MODF)            */
#define NVIC_SSP0             30                                        /* SSP0                         */
#define NVIC_SSP1             31                                        /* SSP1                         */
#define NVIC_PLL0             32                                        /* PLL0 Lock                    */
#define NVIC_RTC              33                                        /* Counter Increment (RTCCIF),  */
                                                                        /* Alarm (RTCALF)               */
#define NVIC_EINT0            34                                        /* External Interrupt 0 (EINT0) */
#define NVIC_EINT1            35                                        /* External Interrupt 1 (EINT1) */
#define NVIC_EINT2            36                                        /* External Interrupt 2 (EINT2) */
#define NVIC_EINT3            37                                        /* External Interrupt 3 (EINT3) */
#define NVIC_ADC              38                                        /* A/D Converter                */
#define NVIC_BOD              39                                        /* Brown Out detect             */
#define NVIC_USB              40                                        /* USB                          */
#define NVIC_CAN              41                                        /* CAN Common, CAN 0 Tx,        */
                                                                        /* CAN 0 Rx, CAN 1 Tx, CAN 1 Rx */
#define NVIC_GP_DMA           42                                        /* IntStatus of DMA channel 0,  */
                                                                        /* IntStatus of DMA channel 1   */
#define NVIC_I2S              43                                        /* irq, dmareq1, dmareq2        */
#define NVIC_ETHR             44                                        /* Ethernet                     */
#define NVIC_RIT              45                                        /* Repetitive Interrupt Timer   */
#define NVIC_MC               46                                        /* Motor Control PWM            */
#define NVIC_QE               47                                        /* Quadrature Encoder           */
#define NVIC_PLL1             48                                        /* PLL1 Lock                    */

/*********************************************************************************************************
**  NVIC Interrupt Priority   NVIC中断优先级
*********************************************************************************************************/
#define PRIO_ZERO            (0x00)                                     /* 优先级为0                    */
#define PRIO_ONE             (0x01 << 3)                                /* 优先级为1                    */
#define PRIO_TWO             (0x02 << 3)                                /* 优先级为2                    */
#define PRIO_THREE           (0x03 << 3)                                /* 优先级为3                    */
#define PRIO_FOUR            (0x04 << 3)                                /* 优先级为4                    */
#define PRIO_FIVE            (0x05 << 3)                                /* 优先级为5                    */
#define PRIO_SIX             (0x06 << 3)                                /* 优先级为6                    */
#define PRIO_SEVEN           (0x07 << 3)                                /* 优先级为7                    */
#define PRIO_EIGHT           (0x08 << 3)                                /* 优先级为8                    */
#define PRIO_NINE            (0x09 << 3)                                /* 优先级为9                    */
#define PRIO_TEN             (0x0A << 3)                                /* 优先级为11                   */
#define PRIO_ELEVEN          (0x0B << 3)                                /* 优先级为11                   */
#define PRIO_TWELVE    	     (0x0C << 3)                                /* 优先级为12                   */
#define PRIO_THIRTEEN   	 (0x0D << 3)                                /* 优先级为13                   */
#define PRIO_FOURTEEN   	 (0x0E << 3)                                /* 优先级为14                   */
#define PRIO_FIFTEEN       	 (0x0F << 3)                                /* 优先级为15                   */
#define PRIO_SIXTEEN         (0x10 << 3)                                /* 优先级为16                   */
#define PRIO_SEVENTEEN  	 (0x11 << 3)                                /* 优先级为17                   */
#define PRIO_EIGHTEEN   	 (0x12 << 3)                                /* 优先级为18                   */
#define PRIO_NINETEEN    	 (0x13 << 3)                                /* 优先级为19                   */
#define PRIO_TWENTY      	 (0x14 << 3)                                /* 优先级为20                   */
#define PRIO_TWENTY_ONE  	 (0x15 << 3)                                /* 优先级为21                   */
#define PRIO_TWENTY_TWO   	 (0x16 << 3)                                /* 优先级为22                   */
#define PRIO_TWENTY_THREE    (0x17 << 3)                                /* 优先级为23                   */
#define PRIO_TWENTY_FOUR     (0x18 << 3)                                /* 优先级为24                   */
#define PRIO_TWENTY_FIVE     (0x19 << 3)                                /* 优先级为25                   */
#define PRIO_TWENTY_SIX      (0x1A << 3)                                /* 优先级为26                   */
#define PRIO_TWENTY_SEVEV    (0x1B << 3)                                /* 优先级为27                   */
#define PRIO_TWENTY_EIGHT    (0x1C << 3)                                /* 优先级为28                   */
#define PRIO_TWENTY_NINE     (0x1D << 3)                                /* 优先级为29                   */
#define PRIO_THIRTY          (0x1E << 3)                                /* 优先级为30                   */
#define PRIO_THIRTY_ONE      (0x1F << 3)                                /* 优先级为31                   */

#endif                                                                  /* __IOLPC1700_H                */
/*********************************************************************************************************
**  End Of File
*********************************************************************************************************/

