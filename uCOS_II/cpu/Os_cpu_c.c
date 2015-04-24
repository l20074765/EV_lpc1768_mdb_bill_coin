/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**                                      
**                                 http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               os_cpu_c.c
** Latest modified Date:    2009-07-24
** Latest Version:          1.0
** Descriptions:            μCOS-II在Cortex-M3上的移植代码C语言部分，用realview编译
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Chenmingji
** Created date:            2009-07-24
** Version:                 1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             
** Modified date:           
** Version:                 
** Descriptions:            
**
*********************************************************************************************************/
#define  OS_CPU_GLOBALS
#include "..\..\config.h"                                            /*  系统头文件                  */

/*********************************************************************************************************
  全局变量
*********************************************************************************************************/
unsigned int __GuiOsEnterSum;

/*********************************************************************************************************
** Function name:           svcallHandle
** Descriptions:            svcall处理程序
** input parameters:        uiHandle:选择子功能
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
__asm void svcallHandle (unsigned int uiHandle)
{
    CMP     R0, #5
    IT      HS
    BXHS    LR
    LSL     R0, #2
    ADD     R0, PC
    LDR     PC, [R0, #+2]
table
    DCD     __s_OSCtxSw
    DCD     __s_OSStartHighRdy
    DCD     __s_OS_ENTER_CRITICAL
    DCD     __s_OS_EXIT_CRITICAL
    DCD     __s_changeToSYSMode
}
/*********************************************************************************************************
** Function name:           __OSStartHighRdy
** Descriptions:            uC/OS-II启动使用OSStartHighRdy运行第一个任务,OSStartHighRdy直接调用
**                          __OSStartHighRdy
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              chenmingji
** Created Date:            2009-07-24
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
__asm void __OSStartHighRdy (void)
{
    MOV     R0, #1
    MSR     CONTROL, R0
    SWI     0
}

/*********************************************************************************************************
** Function name:           __s_OSStartHighRdy
** Descriptions:            uC/OS-II启动使用OSStartHighRdy运行第一个任务,OSStartHighRdy会调用
**                          __s_OSStartHighRdy
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              chenmingji
** Created Date:            2009-07-24
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
__asm void __s_OSStartHighRdy (void)
{
    IMPORT  __GuiOsEnterSum
    IMPORT  OSRunning
    IMPORT  OSTCBCur
    IMPORT  OSTCBHighRdy
    IMPORT  OSTaskSwHook

         preserve8

    LDR     R4, =OSRunning
    MOV     R5, #1
    STRB    R5, [R4]

    MOV     R7, LR
    BL      OSTaskSwHook
    MOV     LR, R7

    LDR     R6, =OSTCBHighRdy
    LDR     R6, [R6]
    LDR     R4, =OSTCBCur
    STR     R6, [R4]

    LDR     SP, [R6]
    POP     {R0}
    LDR     R1, =__GuiOsEnterSum
    STR     R0, [R1]
    POP     {R4-R11}
    BX      LR
	NOP
}

/*********************************************************************************************************
** Function name:           __s_OSStartHighRdy
** Descriptions:            uC/OS-II任务调度函数
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              chenmingji
** Created Date:            2009-07-24
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
__asm void __s_OSCtxSw (void)
{
    IMPORT  __GuiOsEnterSum
    IMPORT  OSTCBCur
    IMPORT  OSTCBHighRdy
    IMPORT  OSPrioCur
    IMPORT  OSPrioHighRdy
    IMPORT  OSTaskSwHook

         preserve8

    MOV     R2, #OS_ISR_PRIO_ONE
    MSR     BASEPRI, R2

    PUSH    {LR}
    BL      OSTaskSwHook
    POP     {LR}

    PUSH    {R4-R11}
    LDR     R1, =__GuiOsEnterSum
    LDR     R0, [R1]
    PUSH    {R0}

    LDR     R2, =OSTCBCur
    LDR     R2, [R2]
    STR     SP, [R2]
    
    LDR     R4, =OSPrioCur
    LDR     R5, =OSPrioHighRdy
    LDRB    R6, [R5]
    STRB    R6, [R4]

    LDR     R6, =OSTCBHighRdy
    LDR     R6, [R6]
    LDR     R4, =OSTCBCur
    STR     R6, [R4]

    LDR     SP, [R6]
    POP     {R0}
    STR     R0, [R1]

    CMP     R0, #0
    ITE     EQ
    MOVEQ   R2, #0
    MOVNE   R2, #OS_ISR_PRIO_ONE
    MSR     BASEPRI, R2    

    POP     {R4-R11}
    BX      LR
	NOP
}

/*********************************************************************************************************
** Function name:           __s_OS_ENTER_CRITICAL
** Descriptions:            禁止中断
**
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              chenmingji
** Created Date:            2009-07-24
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
__asm void __s_OS_ENTER_CRITICAL (void)
{
    IMPORT  __GuiOsEnterSum

    LDR     R1, =__GuiOsEnterSum
    LDR     R0, [R1]
    ADD     R0, #1

    MOV     R2, #OS_ISR_PRIO_ONE
    MSR     BASEPRI, R2
    
    CMP     R0, #0
    BXEQ    LR
    STR     R0, [R1]
    BX      LR
	NOP
}

/*********************************************************************************************************
** Function name:           __s_OS_EXIT_CRITICAL
** Descriptions:            允许中断
**
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              chenmingji
** Created Date:            2009-07-24
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
__asm void __s_OS_EXIT_CRITICAL (void)
{
    IMPORT  __GuiOsEnterSum

    LDR     R1, =__GuiOsEnterSum
    LDR     R0, [R1]
    CMP     R0, #0
    ITT     NE
    SUBNE   R0, #1
    STRNE   R0, [R1]
    CMP     R0, #0
    BXNE    LR

    MOV     R2, #0
    MSR     BASEPRI, R2

    BX      LR
}

/*********************************************************************************************************
** Function name:           __s_changeToSYSMode
** Descriptions:            任务切换到系统模式
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              chenmingji
** Created Date:            2009-07-24
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
__asm void __s_changeToSYSMode (void)
{
    MOV     R0, #0
    MSR     CONTROL, R0
    BX      LR
}

/*********************************************************************************************************
** Function name:           changeToUSRMode
** Descriptions:            任务切换到用户模式
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              chenmingji
** Created Date:            2009-07-24
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
__asm void changeToUSRMode (void)
{
    MOV     R0, #1
    MSR     CONTROL, R0
    BX      LR
}

/*********************************************************************************************************
** Function name:           taskEntry
** Descriptions:            任务入口
** input parameters:        pdata: 传递给任务的参数
** output parameters:       none
** Returned value:          none
** Created by:              chenmingji
** Created Date:            2009-07-24
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
__asm void taskEntry (void *pvData, void (*task)(void *pd))
{
    IMPORT  OSTaskDel

    BLX     R1
    MVN     R0, #OS_PRIO_SELF
    BL      OSTaskDel
}

/*********************************************************************************************************
** Function name:       __sysTickIsr
** Descriptions:        系统节拍中断
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
void __sysTickIsr (void)
{
    STCTRL;
    
    OSIntEnter();
    OSTimeTick();                                                       /*  系统节拍处理                */
    OSIntExit();
}

/*********************************************************************************************************
** Function name:           OSStartHighRdy
** Descriptions:            uC/OS-II启动使用OSStartHighRdy运行第一个任务
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              chenmingji
** Created Date:            2009-07-24
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void OSStartHighRdy (void)
{
    zyIsrSet(PSI, (unsigned long)__s_OSCtxSw, 0xff);
    zyIsrSet(SVCI, (unsigned long)svcallHandle, 0x00);
    zyIsrSet(STI, (unsigned long)__sysTickIsr, 0x80);
	changeToSYSMode();
    STRELOAD = (STCALIB & 0x3fffffff) * 100 / OS_TICKS_PER_SEC;
    STCTRL   = 0x07;
    __OSStartHighRdy();
}

/*********************************************************************************************************
** Function name:           OSIntCtxSw
** Descriptions:            中断级别调度函数
** input parameters:        none
** output parameters:       none
** Returned value:          none
** Created by:              chenmingji
** Created Date:            2009-07-24
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
void OSIntCtxSw (void)
{
    ICSR = 1ul << 28;
}

/*********************************************************************************************************
** Function name:           OSTaskStkInit
** Descriptions:            任务堆栈初始化代码，本函数调用失败会使系统崩溃
** input parameters:        task:  任务开始执行的地址
**                          pdata: 传递给任务的参数
**                          ptos:  任务的堆栈开始位置
**                          opt:   附加参数,当前版本对于本函数无用,具体意义参见OSTaskCreateExt()的opt参数
** output parameters:       none
** Returned value:          新堆栈位置
** Created by:              chenmingji
** Created Date:            2009-07-24
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
OS_STK *OSTaskStkInit (void (*task)(void *pd), void *pdata, OS_STK *ptos, INT16U opt)
{
    OS_STK *pstk;    

    opt     = opt;                                                      /*  避免编译器警告              */
    pstk    = (OS_STK *)(((unsigned long)ptos) & ~0x07ul);              /*  获取堆栈指针,8字对齐        */
    
    /* 
     *  建立任务环境，ADS1.2使用满递减堆栈
     */
    *pstk   = 0x01000000;                                               /*  xPSR                        */
    *--pstk = (OS_STK) taskEntry;                                       /*  pc，所有任务的入口          */
    *--pstk = 0;                                                        /*  lr                          */

    *--pstk = 0;                                                        /*  r12                         */
    *--pstk = 0;                                                        /*  r3                          */
    *--pstk = 0;                                                        /*  r2                          */
    *--pstk = (OS_STK) task;                                            /*  r1,任务真正的入口           */
    *--pstk = (unsigned int) pdata;                                     /*  r0,第一个参数使用R0传递     */
    *--pstk = 0;                                                        /*  r11                         */
    *--pstk = 0;                                                        /*  r10                         */
    *--pstk = 0;                                                        /*  r9                          */
    *--pstk = 0;                                                        /*  r8                          */
    *--pstk = 0;                                                        /*  r7                          */
    *--pstk = 0;                                                        /*  r6                          */
    *--pstk = 0;                                                        /*  r5                          */
    *--pstk = 0;                                                        /*  r4                          */
    *--pstk = 0;                                                        /*  关中断计数器OsEnterSum;     */

    return (pstk);
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
