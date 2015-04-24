/****************************************Copyright (c)****************************************************
**                            Guangzhou ZHIYUAN electronics Co.,LTD.
**                                      
**                                 http://www.embedtools.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               rt_sys_c.c
** Latest modified Date:    2009-06-01
** Latest Version:          1.0
** Descriptions:            目标板部分实时库函数代码
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Chenmingji
** Created date:            2009-06-01
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
#include "..\config.h"
#include <stdlib.h>

/*********************************************************************************************************
  以下为一些与系统相关的库函数的实现
  具体作用请ads的参考编译器与库函数手册
  用户可以根据自己的要求修改
*********************************************************************************************************/
/*********************************************************************************************************
  The implementations for some library functions
  For more details, please refer to the ADS compiler handbook and The library
  function manual
  User could change it as needed
*********************************************************************************************************/

#include <rt_sys.h>
#include <rt_misc.h>
#include <time.h>
#include <stdio.h>

#pragma import(__use_no_semihosting_swi)

/*********************************************************************************************************
  调整半主库相关函数
*********************************************************************************************************/

/*********************************************************************************************************
** Function name:           _sys_exit
** Descriptions:            返回初始堆栈和堆的位置，一般用汇编实现
** input parameters:        手册未作详细说明
** output parameters:       none
** Returned value:          r0: 堆基址
**                          r1: 堆栈基址，即堆栈区中的最高地址
**                          r2: 堆限制
**                          r3: 堆栈限制，即堆栈区中的最低地址
*********************************************************************************************************/
#if 0
__value_in_regs struct __initial_stackheap __user_initial_stackheap (unsigned R0,
                                                                     unsigned SP,
                                                                     unsigned R2)
{
}
#endif                                                                  /*  0                           */

/*********************************************************************************************************
** Function name:           _sys_exit
** Descriptions:            库退出函数。所有从库中的退出最终都会调用_sys_exit()。
** input parameters:        iReturnCode: 退出代码
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void _sys_exit (int iReturnCode)
{
    while (1) {
    }
}

/*********************************************************************************************************
** Function name:           _ttywrch
** Descriptions:            此函数将一个字符写入到控制台中。 控制台可能已被重定向。 除非万不得已，
**                          否则不要将此函数用作错误处理例程。
** input parameters:        iCh: 输出的字符串
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void _ttywrch (int iCh)
{
}

/*********************************************************************************************************
** Function name:           _sys_open
** Descriptions:            此函数打开一个文件。
** input parameters:        pcFileName: 文件名
**                          iOpenMode:  打开模式,是一个位映射,其位通常直接对应于ISO模式规范.
**                                      详细信息请参阅rt_sys.h
** output parameters:       none
** Returned value:          文件句柄
*********************************************************************************************************/
FILEHANDLE _sys_open (const char *pcFileName, int iOpenMode)
{
    return -1;
}

/*********************************************************************************************************
** Function name:           _sys_close
** Descriptions:            此函数关闭以前使用 _sys_open() 打开的文件
** input parameters:        fhHandle: 文件句柄
** output parameters:       none
** Returned value:          文件句柄
*********************************************************************************************************/
int _sys_close (FILEHANDLE fhHandle)
{
    return -1;
}

/*********************************************************************************************************
** Function name:           _sys_read
** Descriptions:            此函数将文件内容读取到缓冲区中
** input parameters:        fhHandle: 文件句柄
**                          iLen:     要读的数据数目
**                          iMode:    没有使用
** output parameters:       puBcuf:   读到的数据
** Returned value:          未读的数据数目
*********************************************************************************************************/
int _sys_read (FILEHANDLE fhHandle, unsigned char *puBcuf, unsigned int iLen, int iMode)
{
    return (int)0x80000000;
}

/*********************************************************************************************************
** Function name:           _sys_write
** Descriptions:            将缓冲区内容写入到以前使用 _sys_open() 打开的文件中
** input parameters:        fhHandle: 文件句柄
**                          puBcuf:   要写的数据
**                          iLen:     要写的数据数目
**                          iMode:    没有使用
** output parameters:       none
** Returned value:          未写的数据数目
*********************************************************************************************************/
int _sys_write (FILEHANDLE fhHandle, const unsigned char *puBcuf, unsigned int iLen, int iMode)
{
    return 0x80000000;
}

/*********************************************************************************************************
** Function name:           _sys_ensure
** Descriptions:            _sys_ensure() 调用将刷新与文件句柄 fh 相关联的任何缓冲区，并且确保将备份
**                          存储介质上的文件保持最新状态。
** input parameters:        fhHandle: 文件句柄
** output parameters:       none
** Returned value:          如果出现错误，则结果为负数。
*********************************************************************************************************/
int _sys_ensure (FILEHANDLE fhHandle)
{
    return 0;
}

/*********************************************************************************************************
** Function name:           _sys_flen
** Descriptions:            此函数返回文件的当前长度。
**                          如果基本系统可以相对于文件末尾进行搜索，则可以定义 fseek()，
**                          这样就不再需要使用 _sys_flen() 了。
** input parameters:        fhHandle: 文件句柄
** output parameters:       none
** Returned value:          如果出现错误，则结果为负数。
*********************************************************************************************************/
long _sys_flen (FILEHANDLE fhHandle)
{
    return -1;
}

/*********************************************************************************************************
** Function name:           _sys_seek
** Descriptions:            此函数将文件指针放在与文件开头之间的偏移为lPos的位置
** input parameters:        fhHandle: 文件句柄
**                          lPos:     偏移量
** output parameters:       none
** Returned value:          如果没有出现错误，结果为非负数；如果出现错误，结果为负数。
*********************************************************************************************************/
int _sys_seek (FILEHANDLE fhHandle, long lPos)
{
    return -1;
}

/*********************************************************************************************************
** Function name:           _sys_istty
** Descriptions:            此函数确定文件句柄是否指定一个终端。
** input parameters:        fhHandle: 文件句柄
** output parameters:       none
** Returned value:          0:    没有交互设备
**                          1:    有交互设备
**                          其他: 出现错误。
*********************************************************************************************************/
int _sys_istty (FILEHANDLE fhHandle)
{
    return -1;
}

/*********************************************************************************************************
** Function name:           _sys_tmpnam
** Descriptions:            此函数将临时文件的文件编号 fileno 转换为唯一的文件名
** input parameters:        iFileNo:  文件编号
**                          uiMaxLen: 文件名最大参数
** output parameters:       pcName:   文件名 
** Returned value:          资料没有明确说明
*********************************************************************************************************/
int _sys_tmpnam (char * pcName, int iFileNo, unsigned int uiMaxLen)
{
    return 0;
}

/*********************************************************************************************************
** Function name:           _sys_command_string
** Descriptions:            此函数从调用当前应用程序的环境中检索用于调用该应用程序的命令行。(未实现)
** input parameters:        pcCmd: 命令缓冲区
**                          iLen:  命令缓冲区长度
** output parameters:       none   
** Returned value:          如果成功，则返回一个指向命令行的指针。
**                          如果失败，则返回 NULL。
*********************************************************************************************************/
char *_sys_command_string (char *pcCmd, int iLen)
{
    return NULL;
}

/*********************************************************************************************************
** Function name:           clock
** Descriptions:            获得当前运行时间
** input parameters:        none
** output parameters:       none   
** Returned value:          以(1/__CLK_TCK)秒为单位的执行时间。
*********************************************************************************************************/
clock_t clock(void)
{
    return 0;
}

/*********************************************************************************************************
** Function name:           _clock_init
** Descriptions:            这是一个用于 clock() 的可选初始化函数
** input parameters:        none
** output parameters:       none   
** Returned value:          none
*********************************************************************************************************/
#if 0
void _clock_init(void)
{
}
#endif                                                                  /*  0                           */

/*********************************************************************************************************
** Function name:           time
** Descriptions:            这是 time.h 中的标准 C 库 time() 函数。(未完全实现)
** input parameters:        none
** output parameters:       none   
** Returned value:          返回值是当前日历时间的近似值。
**                          如果日历时间不可用，则返回值 (time_t)-1。 如果 ptTimer 不是 NULL 指针，则还会
**                          将返回值分配给 time_t*。
*********************************************************************************************************/
time_t time (time_t *ptTimer)
{
    time_t      tRt;                                                        /*  返回值                  */
    struct tm   tmDataTime;                                                 /*  当前日期时间            */ 
    /*
     * 添加获得当前日期时间的代码
     * struct tm定义如下
     * struct tm {
     *   int tm_sec;   // seconds after the minute, 0 to 60
     *                    (0 - 60 allows for the occasional leap second)
     *   int tm_min;   // minutes after the hour, 0 to 59
     *   int tm_hour;  // hours since midnight, 0 to 23
     *   int tm_mday;  // day of the month, 1 to 31
     *   int tm_mon;   // months since January, 0 to 11
     *   int tm_year;  // years since 1900
     *   int tm_wday;  // days since Sunday, 0 to 6
     *   int tm_yday;  // days since January 1, 0 to 365
     *   int tm_isdst; // Daylight Savings Time flag
     * };
     */ 
    tRt = mktime(&tmDataTime);
    
    if (ptTimer != NULL) {
        *ptTimer = tRt;
    }
    return tRt;
}

/*********************************************************************************************************
** Function name:           remove
** Descriptions:            删除一个文件
** input parameters:        pcFileName: 文件名
** output parameters:       none
** Returned value:          如果操作成功，则返回 0；如果失败，则返回非零值。
*********************************************************************************************************/
int remove (const char * pcFileName)
{
    return -1;
}

/*********************************************************************************************************
** Function name:           rename
** Descriptions:            文件改名
** input parameters:        pcOldName:    旧文件名
**                          pcNewName:    新文件名
** output parameters:       none
** Returned value:          如果操作成功，则返回 0；如果失败，则返回非零值。 如果操作返回非零值，并
**                          且该文件以前存在，则该文件仍使用其原始名称。
*********************************************************************************************************/
int rename (const char *pcOldName, const char *pcNewName)
{
    return -1;
}

/*********************************************************************************************************
** Function name:           system
** Descriptions:            将 pcString 所指向的字符串传递到主机环境中，并由命令处理器以实现定
**                          义的方式执行。 string 可以使用空指针以查明命令处理器是否存在。
** input parameters:        pcString: 字符串
** output parameters:       none
** Returned value:          如果自变量是空指针，则仅当命令处理器可用时，此系统函数才会返回非零值。
**                          如果自变量不是空指针，system() 函数将返回由实现定义的值。
*********************************************************************************************************/
int  system (const char *pcString)
{
    return 0;
}

/*********************************************************************************************************
  End File
*********************************************************************************************************/
