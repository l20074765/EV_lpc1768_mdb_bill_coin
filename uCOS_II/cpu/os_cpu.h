/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**                                      
**                                 http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               os_cpu.h
** Latest modified Date:    2009-07-24
** Latest Version:          1.0
** Descriptions:            μCOS-II在Cortex-M3上的移植代码CPU配置部分，用realview编译
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
#ifndef __OS_CPU_H
#define __OS_CPU_H

/*********************************************************************************************************
  定义与编译器无关的数据类型
*********************************************************************************************************/
typedef unsigned char  BOOLEAN;                                         /*  布尔变量                    */
typedef unsigned char  INT8U;                                           /*  无符号8位整型变量           */
typedef signed   char  INT8S;                                           /*  有符号8位整型变量           */
typedef unsigned short INT16U;                                          /*  无符号16位整型变量          */
typedef signed   short INT16S;                                          /*  有符号16位整型变量          */
typedef unsigned long  INT32U;                                          /*  无符号32位整型变量          */
typedef signed   long  INT32S;                                          /*  有符号32位整型变量          */
typedef float          FP32;                                            /*  单精度浮点数（32位长度）    */
typedef double         FP64;                                            /*  双精度浮点数（64位长度）    */

typedef INT32U         OS_STK;                                          /*  堆栈是32位宽度              */


/*********************************************************************************************************
  体系结构相关的一些定义
*********************************************************************************************************/
__swi(0x00) void OsSwiHandle1(int Handle);

#define OS_CRITICAL_METHOD      2                                       /*  选择开、关中断的方式        */
#define OS_STK_GROWTH           1                                       /*  堆栈是从上往下长的          */

#define OS_TASK_SW()            OsSwiHandle1(0)                         /*  任务级任务切换函数          */
#define OS_ENTER_CRITICAL()     OsSwiHandle1(2)                         /*  关中断                      */
#define OS_EXIT_CRITICAL()      OsSwiHandle1(3)                         /*  开中断                      */

/*********************************************************************************************************
** Function name:           __s_changeToSYSMode
** Descriptions:            任务切换到系统模式
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
#define changeToSYSMode()       OsSwiHandle1(4)

/*********************************************************************************************************
** Function name:           changeToUSRMode
** Descriptions:            任务切换到用户模式
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern __asm void changeToUSRMode(void);

/*********************************************************************************************************
** Function name:           __s_OSCtxSw
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
extern __asm void __s_OSCtxSw(void);

/*********************************************************************************************************
** Function name:       __sysTickIsr
** Descriptions:        系统节拍中断
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
extern void __sysTickIsr(void);

/*********************************************************************************************************
** Function name:           svcallHandle
** Descriptions:            svcall处理程序
** input parameters:        uiHandle:选择子功能
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
extern __asm void svcallHandle(unsigned int uiHandle);


#endif                                                                  /*  __OS_CPU_H                  */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
