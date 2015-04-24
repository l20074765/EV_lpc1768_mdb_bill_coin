/****************************************Copyright (c)*************************************************
**                      Fujian Junpeng Communicaiton Technology Co.,Ltd.
**                               http://www.easivend.com.cn
**--------------File Info------------------------------------------------------------------------------
** File name:           main.c
** Last modified Date:  2013-01-06
** Last Version:        No
** Descriptions:        主程序文件                     
**------------------------------------------------------------------------------------------------------
** Created by:          sunway
** Created date:        2013-01-06
** Version:             V0.1
** Descriptions:        The original version        
********************************************************************************************************/
#include "..\config.h"
#include "deviceTask.h"



/*********************************************************************************************************
  定义全局变量
*********************************************************************************************************/






/*********************************************************************************************************
  设备 任务ID、优先级、堆栈设置及函数声明                                
*********************************************************************************************************/   
#define TASK_Device_ID                          5                             /* 任务ID                       */
#define TASK_Device_PRIO                        TASK_Device_ID                      /* 任务优先级                   */
#define TASK_Device_STACK_SIZE                  512                           /* 定义用户堆栈长度             */
OS_STK  TASK_Device_STACK[TASK_Device_STACK_SIZE];                                  /* 定义任务C 堆栈               */








/*********************************************************************************************************
** Function name:       main
** Descriptions:          用户程序入口函数
** input parameters:    无
** output parameters:   无
** Returned value:      无
*********************************************************************************************************/
int main(void)
{
    targetInit();																//初始化目标板
    pinInit();      															//IO初始化                                                                     
    OSInit();                                                                                                       
	//建立设备任务
	OSTaskCreateExt(DEV_task, 
				(void *)0,
				&TASK_Device_STACK[TASK_Device_STACK_SIZE-1],
				TASK_Device_PRIO, 
				TASK_Device_ID, 
				&TASK_Device_STACK[0], 
				TASK_Device_STACK_SIZE, 
				(void *)0,
				OS_TASK_OPT_STK_CHK);
	OSStart();																	//启动多任务
}
/**************************************End Of File*******************************************************/
