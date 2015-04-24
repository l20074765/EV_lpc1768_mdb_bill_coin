;/****************************************Copyright (c)****************************************************
;**                            Guangzhou ZHIYUAN electronics Co.,LTD.
;**                                 http://www.embedtools.com
;**--------------File Info---------------------------------------------------------------------------------
;** File name:               rt_sys.h
;** Latest modified Date:    2009-07-23
;** Latest Version:          1.0
;** Descriptions:            目标板部分实时库函数
;**--------------------------------------------------------------------------------------------------------
;** Created by:              Chenmingji
;** Created date:            2009-07-23
;** Version:                 1.0
;** Descriptions:            The original version
;**--------------------------------------------------------------------------------------------------------
;** Modified by:
;** Modified date:
;** Version:
;** Descriptions:
;**
;*********************************************************************************************************/
         preserve8
    EXPORT  __user_initial_stackheap

    AREA    rt_sys, CODE, READONLY
        ENTRY

__user_initial_stackheap
        LDR   R0, =bottom_of_heap
        BX    LR

        AREA    Heap, DATA, NOINIT
bottom_of_heap

    IMPORT __use_no_semihosting_swi

    END
;/*********************************************************************************************************
;  END FILE
;*********************************************************************************************************/
