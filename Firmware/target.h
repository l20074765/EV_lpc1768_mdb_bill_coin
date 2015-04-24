/****************************************Copyright (c)****************************************************
**                         Guangzhou ZHIYUAN electronics Co.,LTD.                               
**                                     
**                               http://www.embedtools.com
**--------------File Info---------------------------------------------------------------------------------
** File name:           target.h
** Last modified Date:  2009-07-22
** Last Version:        1.0
** Descriptions:        header file of the specific codes for LPC2200 target boards
**                      Every project should include a copy of this file, user may modify it as needed
**--------------------------------------------------------------------------------------------------------
** Created by:          Chenmingji
** Created date:        2009-07-22
** Version:             1.0
** Descriptions:        The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:
** Modified date:
** Version:
** Descriptions:
**
*********************************************************************************************************/
#ifndef __TARGET_H
#define __TARGET_H

#define	__PRJ_TEMPLET_VER	0x10090722                                  /*  工程模板版本为 V1.6         */

#ifdef __cplusplus
extern "C" {
#endif                                                                  /*  __cplusplus                 */


/*********************************************************************************************************
** Function name:           defaultVectorHandle
** Descriptions:            默认异常处理程序
** input parameters:        none
** output parameters:       none
** Returned value:          none
*********************************************************************************************************/
void defaultVectorHandle(void);

/*********************************************************************************************************
** Function name:           targetInit
** Descriptions:            Initialize the target board; it is called in a necessary place, change it as
**                          needed
** input parameters:        None
** output parameters:       None
** Returned value:          None
*********************************************************************************************************/
extern void targetInit(void);

#ifdef __cplusplus
    }
#endif                                                                  /*  __cplusplus                 */

#endif                                                                  /*  _TARGET_H                   */

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
